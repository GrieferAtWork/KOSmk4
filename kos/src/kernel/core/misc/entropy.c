/* Copyright (c) 2019-2023 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_ENTROPY_C
#define GUARD_KERNEL_INCLUDE_KERNEL_ENTROPY_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/debugger.h>
#include <kernel/entropy.h>
#include <kernel/rand.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/sig.h>

#include <hybrid/atomic.h>
#include <hybrid/bit.h>
#include <hybrid/byteorder.h>
#include <hybrid/overflow.h>
#include <hybrid/sched/preemption.h>
#include <hybrid/unaligned.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/io.h>
#include <sys/param.h>
#include <sys/random.h>

#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

#ifndef CONFIG_NO_SMP
#include <hybrid/sched/atomic-lock.h>
#endif /* !CONFIG_NO_SMP */

#define ENTROPY_BITS (CONFIG_KERNEL_ENTROPY_BUFFER_SIZE * NBBY)

DECL_BEGIN

#ifndef CONFIG_NO_SMP
/* SMP-lock for direct access to the entropy buffer. */
PUBLIC struct atomic_lock entropy_lock = ATOMIC_LOCK_INIT;
#define entropy_lock_acquire_nopr() atomic_lock_acquire_nopr(&entropy_lock)
#define entropy_lock_release_nopr() atomic_lock_release(&entropy_lock)
#else /* !CONFIG_NO_SMP */
#define entropy_lock_acquire_nopr() (void)0
#define entropy_lock_release_nopr() (void)0
#endif /* CONFIG_NO_SMP */

/* [lock(!PREEMPTION && entropy_lock)][entropy_bits/8]
 * Raw entropy data. The contents  of this buffer are  undefined,
 * but  may only  be considered  true-random within  the range of
 * the first `entropy_bits' bits (iow: the first `entropy_bits/8'
 * bytes,  as well as  bits masked by `(1 << (entropy_bits&7))-1'
 * within the last byte) */
PUBLIC byte_t entropy_data[CONFIG_KERNEL_ENTROPY_BUFFER_SIZE] = { 0 };

/* [lock(!PREEMPTION && entropy_lock)] # of bits in `entropy_data' */
PUBLIC size_t entropy_bits = 0;

/* [lock(!PREEMPTION && entropy_lock)] Bit position in `entropy_data'
 * when the entropy buffer is  completely filled, in which case  this
 * position is used to cycle through  the buffer and keep on  xor-ing
 * its contents  with new  randomness (thus  hopefully improving  the
 * overall entropy even after the buffer was filled)
 * So long as the buffer isn't full, this variable isn't altered. */
PUBLIC size_t entropy_overflow = 0;


/* [lock(ATOMIC)] Once at least this many bits of entropy
 * are  available, set this variable to (size_t)-1 before
 * broadcasting `entropy_request_sig'.
 * If you wish to wait for entropy to arrive, you should
 * make use of `entropy_connect()' */
PUBLIC size_t entropy_request_bits    = (size_t)-1;
PUBLIC struct sig entropy_request_sig = SIG_INIT;


/* Check if at least `num_bits' of entropy are current available.
 * When this is the case,  return `false'. Otherwise, connect  to
 * `entropy_request_sig' and ATOMIC_CMPXCH `entropy_request_bits'
 * such that its value is not larger than `num_bits'. Afterwards,
 * do another check  if sufficient entropy  is available, and  if
 * that is  the  case  then,  disconnected  and  return  `false'.
 * Otherwise, return `true', following  which the caller may  now
 * do a call to `task_waitfor()', after which they may repeat the
 * check for additional entropy. */
PUBLIC WUNUSED bool FCALL
entropy_connect(size_t num_bits)
		THROWS(E_BADALLOC) {
	size_t oldreq;
	if (ATOMIC_READ(entropy_bits) >= num_bits)
		return false; /* Enough bits are available. */
	task_connect_for_poll(&entropy_request_sig);
	for (;;) {
		oldreq = ATOMIC_READ(entropy_request_bits);
		if (oldreq < num_bits)
			break; /* Someone already wants less that we need. */
		if (ATOMIC_CMPXCH_WEAK(entropy_request_bits,
		                       oldreq, num_bits))
			break;
	}

	/* Do another check for available entropy. */
	if unlikely(ATOMIC_READ(entropy_bits) >= num_bits) {
		task_disconnect(&entropy_request_sig);
		return false; /* Enough bits are available. */
	}

	/* Caller needs to blocking-wait! */
	return true;
}


/* Try to retrieve up to `num_bits' of randomness from the entropy
 * buffer. If an insufficient amount of entropy is available, then
 * `false' is returned. Otherwise (and only then), copy randomness
 * into `buf', consume the random bytes, and return `true'
 * NOTE: The given `buf' must _NOT_ point into user-space and should
 *       preferably point to locked memory (hint: kernel stacks  are
 *       composed of locked memory) */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL entropy_take)(void *buf, size_t num_bits) {
	bool result;
	preemption_flag_t was;
	preemption_pushoff(&was);
	result = entropy_take_nopr(buf, num_bits);
	preemption_pop(&was);
	return result;
}

PUBLIC NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) bool
NOTHROW(FCALL entropy_take_nopr)(void *buf, size_t num_bits) {
	bool result = false;
	entropy_lock_acquire_nopr();
	if (entropy_bits >= num_bits) {
		entropy_bits -= num_bits;
		bitcpy(buf, 0, entropy_data, entropy_bits, num_bits);
		result = true;
	}
	entropy_lock_release_nopr();
	return result;
}


/* Give data to the entropy buffer.
 * WARNING: ONLY CALL THIS FUNCTION IF YOU KNOW YOUR DATA IS TRUELY
 *          RANDOM! NO PRNG ALLOWED! And  also make sure that  it's
 *          not predictable. (e.g.: if the source of randomness  is
 *          timing, only feed the least  significant few bits of  a
 *          nano-second counter!)
 * Also: Don't feed security-critical data (such as which buttons a
 *       user is pressing)  to this function,  as this  information
 *       may otherwise be reverse-engineered by a malicious entity! */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL entropy_give)(void const *buf, size_t num_bits) {
	preemption_flag_t was;
	preemption_pushoff(&was);
	entropy_give_nopr(buf, num_bits);
	preemption_pop(&was);
}


/* Same as `bitcpy(3)', but xor bits from `src*' with those already present in `dst*' */
PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(KCALL bitxor)(void *__restrict dst_base, size_t dst_bit_offset,
                      void const *__restrict src_base, size_t src_bit_offset,
                      size_t num_bits) {
	while (num_bits) {
		byte_t remaining, src_value, remaining_temp;
		src_base = (byte_t const *)src_base + (src_bit_offset / NBBY);
		src_bit_offset %= NBBY;
		remaining = NBBY - src_bit_offset;
		if (remaining > num_bits)
			remaining = num_bits;
		src_value      = *(byte_t const *)src_base >> src_bit_offset;
		remaining_temp = remaining;
		while (remaining_temp) {
			byte_t avail;
			dst_base = (byte_t *)dst_base + (dst_bit_offset / NBBY);
			dst_bit_offset %= NBBY;
			avail = NBBY - dst_bit_offset;
			if (avail > remaining_temp)
				avail = remaining_temp;
			*(byte_t *)dst_base ^= (src_value & ((1 << avail) - 1)) << dst_bit_offset;
			dst_bit_offset += avail;
			remaining_temp -= avail;
			src_value >>= avail;
		}
		src_bit_offset += remaining;
		num_bits -= remaining;
	}
}


PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL entropy_give_nopr)(void const *buf, size_t num_bits) {
	size_t new_entropy_bits;
	entropy_lock_acquire_nopr();
	if (OVERFLOW_UADD(entropy_bits, num_bits, &new_entropy_bits) ||
	    new_entropy_bits > ENTROPY_BITS) {
		size_t buf_offset = 0;
		if (entropy_bits < ENTROPY_BITS) {
			/* Fill remaining entropy bits. */
			size_t remain = ENTROPY_BITS - entropy_bits;
			assert(num_bits > remain);
			bitcpy(entropy_data, entropy_bits, buf, 0, remain);
			entropy_bits += remain;
			buf_offset = remain;
			num_bits -= remain;
		}
		/* Keep on xor-ing entropy data with new bits. */
		do {
			size_t num_xor;
			num_xor = ENTROPY_BITS - entropy_overflow;
			if (num_xor > num_bits)
				num_xor = num_bits;
			bitxor(entropy_data, entropy_overflow,
			       buf, buf_offset, num_xor);
			entropy_overflow += num_xor;
			entropy_overflow %= ENTROPY_BITS;
			buf_offset += num_xor;
			num_bits -= num_xor;
		} while (num_bits);
	} else {
		bitcpy(entropy_data, entropy_bits, buf, 0, num_bits);
		entropy_bits = new_entropy_bits;
	}
	/* Check if we should broadcast the entropy-available signal. */
	if (entropy_bits >= ATOMIC_READ(entropy_request_bits)) {
		entropy_lock_release_nopr();
		ATOMIC_WRITE(entropy_request_bits, (size_t)-1);
		sig_broadcast(&entropy_request_sig);
	} else {
		entropy_lock_release_nopr();
	}
}


/* Implementation for `read(2)' from `/dev/random', as well
 * as the  `getrandom(2)' system  call with  `GRND_RANDOM'.
 *
 * This function will directly read from the entropy buffer,
 * returning the number of bytes read. When nothing has  yet
 * to be read, and nothing can  be read at the moment,  then
 * either wait for data to become available, throw an  error
 * `E_WOULDBLOCK', or return `0' (under `IO_NODATAZERO') */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) size_t FCALL
entropy_read(USER CHECKED void *buf, size_t num_bytes, iomode_t mode)
		THROWS(E_WOULDBLOCK, E_SEGFAULT) {
	size_t result = 0;
	byte_t temp_buf[64];
	while (num_bytes) {
		size_t take_bytes = num_bytes;
		if (take_bytes > sizeof(temp_buf))
			take_bytes = sizeof(temp_buf);
		/* Try to take as much as possible. */
		if (!entropy_take(temp_buf, take_bytes * NBBY)) {
			/* Try to take only a single byte (that's as low as we can go) */
			take_bytes = 1;
			if (!entropy_take(temp_buf, NBBY)) {
				/* No more entropy. If we already managed to
				 * copy ~something~, return without blocking */
				if (result != 0)
					break;

				/* Check if we're allowed to block. */
				if (mode & IO_NONBLOCK) {
					if (mode & IO_NODATAZERO)
						break;
					THROW(E_WOULDBLOCK);
				}

				/* Wait for data to become available. */
				if (entropy_connect(NBBY))
					task_waitfor();
				continue;
			}
		}

		/* Copy data into userspace. */
		buf = (USER CHECKED byte_t *)mempcpy(buf, temp_buf, take_bytes);
		num_bytes -= take_bytes;
		result += take_bytes;
	}
	return result;
}


/* Same as `entropy_read()', but always fill the entire buffer,
 * potentially  waiting until enough entropy has been generated
 * before returning. */
PUBLIC NOBLOCK NONNULL((1)) void FCALL
entropy_readall(USER CHECKED void *buf, size_t num_bytes)
		THROWS(E_WOULDBLOCK, E_INTERRUPT, E_SEGFAULT) {
	while (num_bytes) {
		size_t ok;
		ok = entropy_read(buf, num_bytes, IO_RDONLY);
		assert(ok != 0);
		assert(ok <= num_bytes);
		buf = (byte_t *)buf + ok;
		num_bytes -= ok;
	}
}


/* Similar to `entropy_read()', but implements reads from /dev/urandom.
 * This function uses a  PRNG which may be  seeded at random points  in
 * time (but at least once during boot) to generate numbers. */
PUBLIC NOBLOCK NONNULL((1)) void FCALL
urandom_read(USER CHECKED void *buf, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	while (num_bytes >= 4) {
		u32 val = krand32();
		UNALIGNED_SET32(buf, val);
		buf = (byte_t *)buf + 4;
		num_bytes -= 4;
	}
	if (num_bytes) {
		union {
			u32 r;
			u8 b[4];
		} x;
		x.r = krand32();
		while (num_bytes--)
			((u8 *)buf)[num_bytes] = x.b[num_bytes];
	}
}



/* Define the primary entropy-related system call. */
DEFINE_SYSCALL3(ssize_t, getrandom,
                USER UNCHECKED void *, buf, size_t, num_bytes,
                syscall_ulong_t, flags) {
	ssize_t result;

	/* Validate arguments. */
	validate_writable(buf, num_bytes);
	if unlikely(flags & ~(GRND_NONBLOCK | GRND_RANDOM)) {
		THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG,
		      E_INVALID_ARGUMENT_CONTEXT_GETRANDOM_FLAGS,
		      flags);
	}
	if (flags & GRND_RANDOM) {
#if GRND_NONBLOCK == IO_NONBLOCK
		iomode_t mode = IO_RDONLY | (flags & GRND_NONBLOCK);
#else /* GRND_NONBLOCK == IO_NONBLOCK */
		iomode_t mode = IO_RDONLY;
		if (flags & GRND_NONBLOCK)
			mode |= IO_NONBLOCK;
#endif /* GRND_NONBLOCK != IO_NONBLOCK */
		result = (ssize_t)entropy_read(buf, num_bytes, mode);
	} else {
		urandom_read(buf, num_bytes);
		result = (ssize_t)num_bytes;
	}
	return result;
}






#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
/* Debugger functions to display  entropy information (including a  representation
 * of how well entropy bits are distributed, as in: count how often any given byte
 * appears within the entropy  buffer and check if  some bytes exist that  deviate
 * from the expected norm) */

DBG_COMMAND(entropy,
            "entropy\n"
            "\tDisplay information on entropy collected by the kernel\n") {
	size_t i, j;
	uint8_t bytevalues[256];
	size_t onebits;
	size_t zerobits;

	/* Collect statistical information on which bytes appear how often. */
	bzero(bytevalues, sizeof(bytevalues));
	onebits = 0;
	for (i = 0; i < entropy_bits / NBBY; ++i) {
		byte_t val = entropy_data[i];
		if (bytevalues[val] != 0xff)
			++bytevalues[val];
		onebits += POPCOUNT(val);
	}
	{
		shift_t tail_bits = entropy_bits % NBBY;
		if (tail_bits) {
			byte_t tail_byte = entropy_data[entropy_bits / NBBY];
			tail_byte &= (1 << tail_bits) - 1;
			onebits += POPCOUNT(tail_byte);
		}
	}
	zerobits = entropy_bits - onebits;

	dbg_printf(DBGSTR("entropy_bits: " AC_WHITE("%" PRIuSIZ) "/" AC_WHITE("%u")
	                  " bits (" AC_WHITE("%u") "%%, " AC_WHITE("%" PRIuSIZ)
	                  "+" AC_WHITE("%u") "/" AC_WHITE("8") ")%s\n"),
	           entropy_bits, (size_t)ENTROPY_BITS,
	           (unsigned int)((entropy_bits * 100) / ENTROPY_BITS),
	           entropy_bits / NBBY, (unsigned int)(entropy_bits % NBBY),
	           entropy_bits == ENTROPY_BITS ? DBGSTR(" (" AC_GREEN("full") ")") : DBGSTR(""));
	dbg_printf(DBGSTR("bits: [0=" AC_WHITE("%" PRIuSIZ) " (%u%%),1=" AC_WHITE("%" PRIuSIZ) " (%u%%)]\n"),
	           zerobits, !entropy_bits ? 0 : (zerobits * 100) / entropy_bits,
	           onebits, !entropy_bits ? 0 : (onebits * 100) / entropy_bits);
	if (onebits * 3 >= entropy_bits * 2)
		dbg_print(DBGSTR(AC_YELLOW("WARNING: More than 2/3 are 1-bits") "\n"));
	if (zerobits * 3 >= entropy_bits * 2)
		dbg_print(DBGSTR(AC_YELLOW("WARNING: More than 2/3 are 0-bits") "\n"));

	dbg_print(DBGSTR("   "));
	for (i = 0; i < 16; ++i)
		dbg_printf(DBGSTR(" x%x"), i);
	dbg_putc('\n');
	for (i = 0; i < 16; ++i) {
		dbg_printf(DBGSTR("%xx "), i);
		dbg_savecolor();
		for (j = 0; j < 16; ++j) {
			byte_t b = (i * 16) + j;
			uint8_t count = bytevalues[b];
			if (count == 0) {
				dbg_print(DBGSTR("   "));
			} else {
				if (count == 1) {
					dbg_setfgcolor(ANSITTY_CL_DARK_GRAY);
				} else if (count == 2) {
					dbg_setfgcolor(ANSITTY_CL_LIGHT_GRAY);
				} else {
					dbg_setfgcolor(ANSITTY_CL_WHITE);
				}
				dbg_printf(DBGSTR("%3" PRIu8), count);
			}
		}
		dbg_loadcolor();
		dbg_putc('\n');
	}
	return 0;
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_ENTROPY_C */
