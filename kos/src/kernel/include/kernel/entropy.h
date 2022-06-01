/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_ENTROPY_H
#define GUARD_KERNEL_INCLUDE_KERNEL_ENTROPY_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/__assert.h>
#include <hybrid/byteorder.h>

#ifndef CONFIG_NO_SMP
#include <hybrid/sched/atomic-lock.h>
#endif /* !CONFIG_NO_SMP */

/************************************************************************/
/* Entropy (aka. true random) management                                */
/************************************************************************/

/* Max # of bytes which may be stored in the entropy buffer.
 * Note that all other entropy  APIs (usually) operate on  a
 * bit-basis! */
#ifndef CONFIG_ENTROPY_BUFFER_SIZE
#define CONFIG_ENTROPY_BUFFER_SIZE 4096
#endif /* !CONFIG_ENTROPY_BUFFER_SIZE */


#ifdef __CC__
DECL_BEGIN

#ifndef CONFIG_NO_SMP
/* SMP-lock for direct access to the entropy buffer. */
DATDEF struct atomic_lock entropy_lock;
#endif /* !CONFIG_NO_SMP */

/* [lock(!PREEMPTION && entropy_lock)][entropy_bits/8]
 * Raw entropy data. The contents  of this buffer are  undefined,
 * but  may only  be considered  true-random within  the range of
 * the first `entropy_bits' bits (iow: the first `entropy_bits/8'
 * bytes,  as well as  bits masked by `(1 << (entropy_bits&7))-1'
 * within the last byte) */
DATDEF byte_t entropy_data[CONFIG_ENTROPY_BUFFER_SIZE];

/* [lock(!PREEMPTION && entropy_lock)] # of bits in `entropy_data' */
DATDEF size_t entropy_bits;

/* [lock(!PREEMPTION && entropy_lock)] Bit position in `entropy_data'
 * when the entropy buffer is  completely filled, in which case  this
 * position is used to cycle through  the buffer and keep on  xor-ing
 * its contents  with new  randomness (thus  hopefully improving  the
 * overall entropy even after the buffer was filled)
 * So long as the buffer isn't full, this variable isn't altered. */
DATDEF size_t entropy_overflow;


/* [lock(ATOMIC)] Once at least this many bits of entropy
 * are  available, set this variable to (size_t)-1 before
 * broadcasting `entropy_request_sig'.
 * If you wish to wait for entropy to arrive, you should
 * make use of `entropy_connect()' */
DATDEF size_t entropy_request_bits;
DATDEF struct sig entropy_request_sig;


/* Check if at least `num_bits' of entropy are current available.
 * When this is the case,  return `false'. Otherwise, connect  to
 * `entropy_request_sig' and ATOMIC_CMPXCH `entropy_request_bits'
 * such that its value is not larger than `num_bits'. Afterwards,
 * do another check  if sufficient entropy  is available, and  if
 * that is  the  case  then,  disconnected  and  return  `false'.
 * Otherwise, return `true', following  which the caller may  now
 * do a call to `task_waitfor()', after which they may repeat the
 * check for additional entropy. */
FUNDEF WUNUSED __BOOL FCALL
entropy_connect(size_t num_bits)
		THROWS(E_BADALLOC);


/* Try to retrieve up to `num_bits' of randomness from the entropy
 * buffer. If an insufficient amount of entropy is available, then
 * `false' is returned. Otherwise (and only then), copy randomness
 * into `buf', consume the random bytes, and return `true'
 * NOTE: The given `buf' must _NOT_ point into user-space and should
 *       preferably point to locked memory (hint: kernel stacks  are
 *       composed of locked memory) */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL entropy_take)(void *buf, size_t num_bits);
FUNDEF NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL entropy_take_nopr)(void *buf, size_t num_bits);

/* Give data to the entropy buffer.
 * WARNING: ONLY CALL THIS FUNCTION IF YOU KNOW YOUR DATA IS TRUELY
 *          RANDOM! NO PRNG ALLOWED! And  also make sure that  it's
 *          not predictable. (e.g.: if the source of randomness  is
 *          timing, only feed the least  significant few bits of  a
 *          nano-second counter!)
 * Also: Don't feed security-critical data (such as which buttons a
 *       user is pressing)  to this function,  as this  information
 *       may otherwise be reverse-engineered by a malicious entity! */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL entropy_give)(void const *buf, size_t num_bits);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL entropy_give_nopr)(void const *buf, size_t num_bits);


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
		THROWS(E_WOULDBLOCK, E_SEGFAULT);

/* Same as `entropy_read()', but always fill the entire buffer,
 * potentially  waiting until enough entropy has been generated
 * before returning. */
FUNDEF NOBLOCK NONNULL((1)) void FCALL
entropy_readall(USER CHECKED void *buf, size_t num_bytes)
		THROWS(E_WOULDBLOCK, E_INTERRUPT, E_SEGFAULT);


/* Similar to `entropy_read()', but implements reads from /dev/urandom.
 * This function uses a  PRNG which may be  seeded at random points  in
 * time (but at least once during boot) to generate numbers. */
FUNDEF NOBLOCK NONNULL((1)) void FCALL
urandom_read(USER CHECKED void *buf, size_t num_bytes)
		THROWS(E_SEGFAULT);



/* TODO: `entropy_give' needs to be expanded with a wrapper  API
 *       for automatic de-biasing  of input data.  While I  have
 *       no idea how to do this properly, one idea I have is to:
 * - Enforce fixed-bit-count input chunks and have counters
 *   for each bit to track how often that was 1, as well as
 *   an overall counter to track how often data was fed.
 * - When the overall counter would overflow, divide it by
 *   2, alongside all other counters.
 * - With this, we generate a mean of randomness over time.
 * - Entropy bits are passed to the overall pool one bit at
 *   a time, using the following code:
 *   >> size_t num_chunks;     // Total # of chunks
 *   >>
 *   >> size_t perbit_num1;    // # of times this bit was 1
 *   >> bool   perbit_saved;   // Accumulated entropy of this bit
 *   >> double perbit_worth;   // Accumulated worth of `perbit_saved'
 *   >>
 *   >> void handle_bit(bool b) {
 *   >>     perbit_saved ^= b; // Combine entropy
 *   >>     if (b != false)
 *   >>         ++perbit_num1; // Can't possibly overflow
 *   >>     ++num_chunks;      // Overflow handling is to divide this and perbit_num1 by 2
 *   >>     double mean  = (double)perbit_num1 / num_chunks; // Average tendency over time
 *   >>     double error = 2.0 * fabs(0.5 - mean);           // How close is the mean to the perfect mean of 0.5
 *   >>     double worth = 1.0 - error;                      // How much worth to assign to the given `b'
 *   >>     // The value appears to be truly random <worth*100>% of the time
 *   >>     perbit_worth += worth;                           // Accumulate worth over time
 *   >>     if (perbit_worth >= 1.0) {                       // With enough worth to approximate
 *   >>                                                      // the mean, post combined bit entropy
 *   >>         ADD_TO_GLOBAL_POOL(perbit_saved);
 *   >>         perbit_worth -= 1.0;
 *   >>     }
 *   >> }
 */





#ifdef __cplusplus
extern "C++" {

/* Fill the least significant `num_bits' bits of `value' with randomness. */
template<class T> FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) __BOOL
NOTHROW(entropy_takeint)(T *buf, unsigned int num_bits = sizeof(T) * __CHAR_BIT__) {
	__hybrid_assert(num_bits <= sizeof(T) * __CHAR_BIT__);
	*buf = 0;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	return entropy_take(buf, num_bits);
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	return entropy_take((byte_t *)buf + (sizeof(T) - ((num_bits + __CHAR_BIT__ - 1) / __CHAR_BIT__)),
	                    num_bits);
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
}
template<class T> FORCELOCAL NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) __BOOL
NOTHROW(entropy_takeint_nopr)(T *buf, unsigned int num_bits = sizeof(T) * __CHAR_BIT__) {
	__hybrid_assert(num_bits <= sizeof(T) * __CHAR_BIT__);
	*buf = 0;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	return entropy_take_nopr(buf, num_bits);
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	return entropy_take_nopr((byte_t *)buf + (sizeof(T) - ((num_bits + __CHAR_BIT__ - 1) / __CHAR_BIT__)),
	                         num_bits);
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
}

/* Give the least significant `num_bits' bits of `value' as randomness. */
template<class T> FORCELOCAL NOBLOCK void
NOTHROW(entropy_giveint)(T value, unsigned int num_bits = sizeof(T) * __CHAR_BIT__) {
	__hybrid_assert(num_bits <= sizeof(T) * __CHAR_BIT__);
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	return entropy_give(&value, num_bits);
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	return entropy_give((byte_t *)&value + (sizeof(T) - ((num_bits + __CHAR_BIT__ - 1) / __CHAR_BIT__)),
	                    num_bits);
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
}
template<class T> FORCELOCAL NOBLOCK NOPREEMPT void
NOTHROW(entropy_giveint_nopr)(T value, unsigned int num_bits = sizeof(T) * __CHAR_BIT__) {
	__hybrid_assert(num_bits <= sizeof(T) * __CHAR_BIT__);
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	return entropy_give_nopr(&value, num_bits);
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	return entropy_give_nopr((byte_t *)&value + (sizeof(T) - ((num_bits + __CHAR_BIT__ - 1) / __CHAR_BIT__)),
	                         num_bits);
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
}

} /* extern "C++" */
#endif /* __cplusplus */


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_ENTROPY_H */
