/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_ENTROPY_C
#define GUARD_KERNEL_INCLUDE_KERNEL_ENTROPY_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/entropy.h>
#include <kernel/types.h>
#include <sched/signal.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/byteorder.h>
#include <hybrid/overflow.h>

#include <sys/param.h>

#include <assert.h>
#include <stdbool.h>
#include <string.h>

#ifndef CONFIG_NO_SMP
#include <hybrid/sync/atomic-lock.h>
#endif /* !CONFIG_NO_SMP */

#define ENTROPY_BITS (CONFIG_ENTROPY_BUFFER_SIZE * NBBY)

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
PUBLIC byte_t entropy_data[CONFIG_ENTROPY_BUFFER_SIZE] = { 0 };

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
 * When this is  the case, return  `true'. Otherwise, connect  to
 * `entropy_request_sig' and ATOMIC_CMPXCH `entropy_request_bits'
 * such that its value is not larger than `num_bits'. Afterwards,
 * do another check  if sufficient entropy  is available, and  if
 * that  is  the  case  then,  disconnected  and  return  `true'.
 * Otherwise, return `false', following which the caller may  now
 * do a call to `task_waitfor()', after which they may repeat the
 * check for additional entropy. */
PUBLIC WUNUSED bool FCALL
entropy_connect(size_t num_bits)
		THROWS(E_BADALLOC) {
	size_t oldreq;
	if (ATOMIC_READ(entropy_bits) >= num_bits)
		return true; /* Enough bits are available. */
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
		return true; /* Enough bits are available. */
	}

	/* Caller needs to blocking-wait! */
	return false;
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
	pflag_t was;
	was    = PREEMPTION_PUSHOFF();
	result = entropy_take_nopr(buf, num_bits);
	PREEMPTION_POP(was);
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
 *          nano-second counter!) */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL entropy_give)(void const *buf, size_t num_bits) {
	pflag_t was;
	was = PREEMPTION_PUSHOFF();
	entropy_give_nopr(buf, num_bits);
	PREEMPTION_POP(was);
}


/* Same as `bitcpy(3)', but xor bits from `src*' with those already present in `dst*' */
PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(KCALL bitxor)(void *__restrict dst_base, size_t dst_bit_offset,
                      void const *__restrict src_base, size_t src_bit_offset,
                      size_t num_bits) {
	while (num_bits) {
		byte_t remaining, src_value, remaining_temp;
		src_base = (byte_t const *)src_base + (src_bit_offset / __CHAR_BIT__);
		src_bit_offset %= __CHAR_BIT__;
		remaining = __CHAR_BIT__ - src_bit_offset;
		if (remaining > num_bits)
			remaining = num_bits;
		src_value      = *(byte_t const *)src_base >> src_bit_offset;
		remaining_temp = remaining;
		while (remaining_temp) {
			byte_t avail;
			dst_base = (byte_t *)dst_base + (dst_bit_offset / __CHAR_BIT__);
			dst_bit_offset %= __CHAR_BIT__;
			avail = __CHAR_BIT__ - dst_bit_offset;
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
	    new_entropy_bits > CONFIG_ENTROPY_BUFFER_SIZE) {
		size_t buf_offset = 0;
		if (entropy_bits < CONFIG_ENTROPY_BUFFER_SIZE) {
			/* Fill remaining entropy bits. */
			size_t remain = CONFIG_ENTROPY_BUFFER_SIZE - entropy_bits;
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




/* TODO: Debugger functions to display entropy information (including a representation
 *       of how well entropy bits are distributed, as in: count how often any given byte
 *       appears within the entropy buffer and check if some bytes exist that deviate
 *       from the expected norm) */



DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_ENTROPY_C */
