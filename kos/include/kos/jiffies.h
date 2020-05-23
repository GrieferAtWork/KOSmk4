/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_JIFFIES_H
#define _KOS_JIFFIES_H 1

/* TODO: Get rid of this header */

#include <__stdinc.h>
#include <bits/types.h>
#include <features.h>
#include <asm/param.h>

#if defined(__cplusplus) && defined(__USE_KOS)
#include <kos/anno.h>
#endif /* __cplusplus && __USE_KOS */

#ifndef __KOS__
#error "KOS-only system header"
#endif /* !__KOS__ */

#define JIFFIES_PER_SECOND         HZ
#define JIFFIES_PER_MINUTE        (HZ*60)
#define JIFFIES_PER_HOUR          (HZ*3600)
#define JIFFIES_FROM_HOURS(x)    ((x)*JIFFIES_PER_HOUR)
#define JIFFIES_FROM_MINUTES(x)  ((x)*JIFFIES_PER_MINUTE)
#define JIFFIES_FROM_SECONDS(x)  ((x)*JIFFIES_PER_SECOND)
#define JIFFIES_FROM_MILLI(x)    ((x)/(1000ul/JIFFIES_PER_SECOND))
#define JIFFIES_FROM_MICRO(x)    ((x)/(1000000ul/JIFFIES_PER_SECOND))
#define JIFFIES_FROM_NANO(x)     ((x)/(1000000000ul/JIFFIES_PER_SECOND))

__DECL_BEGIN

#ifdef __CC__
#ifndef __jtime_t_defined
#define __jtime_t_defined 1
typedef __jtime_t jtime_t;
#endif /* !__jtime_t_defined */

#ifndef __quantum_diff_t_defined
#define __quantum_diff_t_defined 1
typedef __quantum_diff_t quantum_diff_t; /* Sub-quantum quantum_diff difference */
#endif /* !__quantum_diff_t_defined */
#endif /* __CC__ */


#define __OFFSET_QTIME_JTIME   0
#define __OFFSET_QTIME_QTIME   __SIZEOF_JTIME_T__
#define __OFFSET_QTIME_QSIZE  (__SIZEOF_JTIME_T__ + __SIZEOF_QUANTUM_DIFF_T__)
#define __SIZEOF_QTIME_T__    (__SIZEOF_JTIME_T__ + __SIZEOF_QUANTUM_DIFF_T__ * 2)

#ifdef __CC__
#ifndef __qtime_t_defined
#define __qtime_t_defined 1
#if defined(__cplusplus) && defined(__USE_KOS)
__DECL_END
#include <hybrid/__overflow.h>
__DECL_BEGIN
#endif /* __cplusplus && __USE_KOS */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("q_jtime")
#pragma push_macro("q_qtime")
#pragma push_macro("q_qsize")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef q_jtime
#undef q_qtime
#undef q_qsize

typedef struct __qtime {
	jtime_t        q_jtime; /* Starting time (in jiffies) */
	quantum_diff_t q_qtime; /* Quantum offset */
	quantum_diff_t q_qsize; /* [!0] Length of the quantum described by `q_qtime' */
#if defined(__cplusplus) && defined(__USE_KOS)

	__CXX_CLASSMEMBER __NOBLOCK void
	add_quantum(quantum_diff_t __diff) __THROWS(E_DIVIDE_BY_ZERO) {
		if (__hybrid_overflow_uadd(this->q_qtime, __diff, &this->q_qtime)) {
			this->q_jtime += ((quantum_diff_t)-1) / this->q_qsize;
			this->q_qtime += __diff;
			this->q_qtime -= (quantum_diff_t)-1;
		}
		if (this->q_qtime >= this->q_qsize) {
			this->q_jtime += this->q_qtime / this->q_qsize;
			this->q_qtime  = this->q_qtime % this->q_qsize;
		}
	}

	__CXX_CLASSMEMBER __NOBLOCK void
	sub_quantum(quantum_diff_t __diff) __THROWS(E_DIVIDE_BY_ZERO) {
		if (__hybrid_overflow_usub(this->q_qtime, __diff, &this->q_qtime)) {
			this->q_jtime -= ((quantum_diff_t)-1) / this->q_qsize;
			this->q_qtime -= __diff;
			this->q_qtime += (quantum_diff_t)-1;
		}
		if (this->q_qtime >= this->q_qsize) {
			this->q_jtime += this->q_qtime / this->q_qsize;
			this->q_qtime  = this->q_qtime % this->q_qsize;
		}
	}

	__CXX_CLASSMEMBER __NOBLOCK void
	add_quantum(quantum_diff_t __diff, quantum_diff_t __size) __THROWS(E_DIVIDE_BY_ZERO) {
		quantum_diff_t __common_size;
		__uint64_t __new_qtime;
		__common_size = this->q_qsize + (((__size - this->q_qsize) + 1) / 2);
		__new_qtime = (((__uint64_t)q_qtime * __common_size) / q_qsize) +
		              (((__uint64_t)__diff * __common_size) / __size);
		if (__new_qtime > __common_size) {
			++this->q_jtime;
			__new_qtime -= __common_size;
			if __unlikely(__new_qtime > __common_size) {
				this->q_jtime += __new_qtime / __common_size;
				__new_qtime %= __common_size;
			}
		}
		q_qtime = (quantum_diff_t)__new_qtime;
		q_qsize = __common_size;
	}

	__CXX_CLASSMEMBER __NOBLOCK void
	sub_quantum(quantum_diff_t __diff, quantum_diff_t __size) __THROWS(E_DIVIDE_BY_ZERO) {
		quantum_diff_t __common_size;
		__uint64_t __adj_lhs, __adj_rhs;
		__common_size = this->q_qsize + (((__size - this->q_qsize) + 1) / 2);
		__adj_lhs = ((__uint64_t)q_qtime * __common_size) / q_qsize;
		__adj_rhs = ((__uint64_t)__diff * __common_size) / __size;
		if (__adj_lhs < __adj_rhs) {
			--q_jtime;
			__adj_lhs += __common_size;
			if __unlikely(__adj_lhs < __adj_rhs) {
				unsigned int __n = (unsigned int)(((__adj_rhs - __adj_lhs) + (__common_size - 1)) / __common_size);
				q_jtime -= __n;
				__adj_lhs += __n * __common_size;
			}
		}
		q_qtime = (quantum_diff_t)(__adj_lhs - __adj_rhs);
		q_qsize = __common_size;
	}

	/* Add seconds */
	__CXX_CLASSMEMBER __NOBLOCK void add_seconds(__uintptr_t __n) __THROWS(E_DIVIDE_BY_ZERO) {
		this->q_jtime += (__uint64_t)__n * HZ;
	}
	__CXX_CLASSMEMBER __NOBLOCK void add_seconds64(__uint64_t __n) __THROWS(E_DIVIDE_BY_ZERO) {
		this->q_jtime += (__uint64_t)__n * HZ;
	}
	__CXX_CLASSMEMBER __NOBLOCK void sub_seconds(__uintptr_t __n) __THROWS(E_DIVIDE_BY_ZERO) {
		this->q_jtime -= (__uint64_t)__n * HZ;
	}
	__CXX_CLASSMEMBER __NOBLOCK void sub_seconds64(__uint64_t __n) __THROWS(E_DIVIDE_BY_ZERO) {
		this->q_jtime -= (__uint64_t)__n * HZ;
	}

	/* Add milliseconds (1/1_000 seconds) */
	__CXX_CLASSMEMBER __NOBLOCK void add_milliseconds(__uintptr_t __n) __THROWS(E_DIVIDE_BY_ZERO) {
		__uint64_t __hz_adjusted = (__uint64_t)__n * HZ;
		this->q_jtime += __hz_adjusted / 1000;
		__hz_adjusted %= 1000;
		this->add_quantum((quantum_diff_t)(__hz_adjusted * this->q_qsize) / 1000);
	}
	__CXX_CLASSMEMBER __NOBLOCK void sub_milliseconds(__uintptr_t __n) __THROWS(E_DIVIDE_BY_ZERO) {
		__uint64_t __hz_adjusted = (__uint64_t)__n * HZ;
		this->q_jtime -= __hz_adjusted / 1000;
		__hz_adjusted %= 1000;
		this->sub_quantum((quantum_diff_t)(__hz_adjusted * this->q_qsize) / 1000);
	}

	/* Add microseconds (1/1_000_000 seconds) */
	__CXX_CLASSMEMBER __NOBLOCK void add_microseconds(__uintptr_t __n) __THROWS(E_DIVIDE_BY_ZERO) {
		__uint64_t __hz_adjusted = (__uint64_t)__n * HZ;
		this->q_jtime += __hz_adjusted / 1000000;
		__hz_adjusted %= 1000000;
		this->add_quantum((quantum_diff_t)(__hz_adjusted * this->q_qsize) / 1000000);
	}
	__CXX_CLASSMEMBER __NOBLOCK void sub_microseconds(__uintptr_t __n) __THROWS(E_DIVIDE_BY_ZERO) {
		__uint64_t __hz_adjusted = (__uint64_t)__n * HZ;
		this->q_jtime -= __hz_adjusted / 1000000;
		__hz_adjusted %= 1000000;
		this->sub_quantum((quantum_diff_t)(__hz_adjusted * this->q_qsize) / 1000000);
	}

	/* Add nanoseconds (1/1_000_000_000 seconds) */
	__CXX_CLASSMEMBER __NOBLOCK void add_nanoseconds(__uintptr_t __n) __THROWS(E_DIVIDE_BY_ZERO) {
		__uint64_t __hz_adjusted = (__uint64_t)__n * HZ;
		this->q_jtime += __hz_adjusted / 1000000000;
		__hz_adjusted %= 1000000000;
		this->add_quantum((quantum_diff_t)(__hz_adjusted * this->q_qsize) / 1000000000);
	}
	__CXX_CLASSMEMBER __NOBLOCK void sub_nanoseconds(__uintptr_t __n) __THROWS(E_DIVIDE_BY_ZERO) {
		__uint64_t __hz_adjusted = (__uint64_t)__n * HZ;
		this->q_jtime -= __hz_adjusted / 1000000000;
		__hz_adjusted %= 1000000000;
		this->sub_quantum((quantum_diff_t)(__hz_adjusted * this->q_qsize) / 1000000000);
	}

	__CXX_CLASSMEMBER __NOBLOCK __qtime &operator+=(__qtime const &__other) __CXX_NOEXCEPT {
		this->q_jtime += __other.q_jtime;
		add_quantum(__other.q_qtime, __other.q_qsize);
		return *this;
	}
	__CXX_CLASSMEMBER __NOBLOCK __qtime &operator-=(__qtime const &__other) __CXX_NOEXCEPT {
		this->q_jtime -= __other.q_jtime;
		sub_quantum(__other.q_qtime, __other.q_qsize);
		return *this;
	}
	__CXX_CLASSMEMBER __NOBLOCK __qtime operator+(__qtime const &__other) __CXX_NOEXCEPT {
		__qtime __res = *this;
		__res.q_jtime += __other.q_jtime;
		__res.add_quantum(__other.q_qtime, __other.q_qsize);
		return __res;
	}
	__CXX_CLASSMEMBER __NOBLOCK __qtime operator-(__qtime const &__other) __CXX_NOEXCEPT {
		__qtime __res = *this;
		__res.q_jtime -= __other.q_jtime;
		__res.sub_quantum(__other.q_qtime, __other.q_qsize);
		return __res;
	}
	__CXX_CLASSMEMBER __NOBLOCK bool operator==(__qtime const &__other) __CXX_NOEXCEPT {
		return (this->q_jtime == __other.q_jtime) &&
		       (((__uint64_t)this->q_qtime * this->q_qsize) ==
		        ((__uint64_t)__other.q_qtime * __other.q_qsize));
	}
	__CXX_CLASSMEMBER __NOBLOCK bool operator!=(__qtime const &__other) __CXX_NOEXCEPT {
		return (this->q_jtime != __other.q_jtime) ||
		       (((__uint64_t)this->q_qtime * this->q_qsize) !=
		        ((__uint64_t)__other.q_qtime * __other.q_qsize));
	}
	__CXX_CLASSMEMBER __NOBLOCK bool operator<(__qtime const &__other) __CXX_NOEXCEPT {
		return (this->q_jtime < __other.q_jtime) ||
		       ((this->q_jtime == __other.q_jtime) &&
		        (((__uint64_t)this->q_qtime * this->q_qsize) <
		         ((__uint64_t)__other.q_qtime * __other.q_qsize)));
	}
	__CXX_CLASSMEMBER __NOBLOCK bool operator<=(__qtime const &__other) __CXX_NOEXCEPT {
		return (this->q_jtime < __other.q_jtime) ||
		       ((this->q_jtime == __other.q_jtime) &&
		        (((__uint64_t)this->q_qtime * this->q_qsize) <=
		         ((__uint64_t)__other.q_qtime * __other.q_qsize)));
	}
	__CXX_CLASSMEMBER __NOBLOCK bool operator>(__qtime const &__other) __CXX_NOEXCEPT {
		return (this->q_jtime > __other.q_jtime) ||
		       ((this->q_jtime == __other.q_jtime) &&
		        (((__uint64_t)this->q_qtime * this->q_qsize) >
		         ((__uint64_t)__other.q_qtime * __other.q_qsize)));
	}
	__CXX_CLASSMEMBER __NOBLOCK bool operator>=(__qtime const &__other) __CXX_NOEXCEPT {
		return (this->q_jtime > __other.q_jtime) ||
		       ((this->q_jtime == __other.q_jtime) &&
		        (((__uint64_t)this->q_qtime * this->q_qsize) >=
		         ((__uint64_t)__other.q_qtime * __other.q_qsize)));
	}
#endif /* __cplusplus && __USE_KOS */
} qtime_t;

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("q_qsize")
#pragma pop_macro("q_qtime")
#pragma pop_macro("q_jtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* !__qtime_t_defined */
#endif /* __CC__ */

__DECL_END

#endif /* !_KOS_JIFFIES_H */
