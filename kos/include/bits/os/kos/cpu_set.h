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
#ifndef _BITS_OS_KOS_CPU_SET_H
#define _BITS_OS_KOS_CPU_SET_H 1

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

#include <hybrid/__bit.h>

#include <asm/os/sched.h> /* __CPU_SETSIZE */
#include <bits/types.h>

#include <libc/malloc.h>
#include <libc/string.h>

#ifndef __CPU_SETSIZE
#define __CPU_SETSIZE 256
#endif /* !__CPU_SETSIZE */

#define __SIZEOF_CPU_SET_T__  (__CPU_SETSIZE / 8)
#define __NCPUBITS            (8 * sizeof(__cpu_mask_t))
#define __SIZEOF_CPU_MASK__   4
#define __CPUELT(cpuno)       ((cpuno)/__NCPUBITS)
#define __CPUMASK(cpuno)      ((__cpu_mask_t)1 << ((cpuno)%__NCPUBITS))

#ifdef __CC__
__DECL_BEGIN
typedef __UINT32_TYPE__ __cpu_mask_t;
struct __cpu_set_struct {
	__cpu_mask_t __bits[__CPU_SETSIZE / __NCPUBITS];
};
__DECL_END

#define __CPU_SETNONE   { { [0 ... __CPUELT(__CPU_SETSIZE) - 1] = 0 } }
#define __CPU_SETALL    { { [0 ... __CPUELT(__CPU_SETSIZE) - 1] = (__cpu_mask_t)-1 } }
#if defined(__GNUC__) && 0
#define __CPU_SETONE(i)                                                               \
	_Pragma("GCC diagnostic push")                                                    \
	_Pragma("GCC diagnostic ignored \"-Woverride-init\"")                             \
		{ { [0 ... __CPUELT(__CPU_SETSIZE) - 1] = 0, [__CPUELT(i)] = __CPUMASK(i) } } \
	_Pragma("GCC diagnostic pop")
#elif 1
#define __CPU_SETONE(i)                                                                                          \
	{                                                                                                            \
		{                                                                                                        \
			[0 ... ((i) < __NCPUBITS ? 0 : __CPUELT(i) - 1)] = (i) < __NCPUBITS ? __CPUMASK(i) : 0,              \
			[((i) < __NCPUBITS ? 1 : __CPUELT(i)) ... (((i) < __NCPUBITS || (i) >= (__CPU_SETSIZE - __NCPUBITS)) \
			                                           ? __CPUELT(__CPU_SETSIZE) - 2                             \
			                                           : __CPUELT(i))] =                                         \
				((i) < __NCPUBITS || (i) >= (__CPU_SETSIZE - __NCPUBITS)) ? 0 : __CPUMASK(i),                    \
			[(((i) < __NCPUBITS || (i) >= (__CPU_SETSIZE - __NCPUBITS))                                          \
			  ? __CPUELT(__CPU_SETSIZE) - 1                                                                      \
			  : __CPUELT(i) + 1) ...  __CPUELT(__CPU_SETSIZE) - 1] =                                             \
				(i) >= (__CPU_SETSIZE - __NCPUBITS) ? __CPUMASK(i) : 0                                           \
		}                                                                                                        \
	}
#else /* ... */
#define __CPU_SETONE(i) \
	{{[0 ... __CPUELT(__CPU_SETSIZE)-1] = 0, [__CPUELT(i)] = __CPUMASK(i)}}
#endif /* !... */

#if __SIZEOF_CPU_MASK__ <= 1
#define __CPUMASK_POPCOUNT __hybrid_popcount8
#elif __SIZEOF_CPU_MASK__ <= 2
#define __CPUMASK_POPCOUNT __hybrid_popcount16
#elif __SIZEOF_CPU_MASK__ <= 4
#define __CPUMASK_POPCOUNT __hybrid_popcount32
#elif __SIZEOF_CPU_MASK__ <= 8
#define __CPUMASK_POPCOUNT __hybrid_popcount64
#else /* ... */
#error "Unsupported __SIZEOF_CPU_MASK__"
#endif /* !... */

#define __CPU_FILL_S(setsize, cpusetp) __libc_memset(cpusetp, 0xff, setsize)
#define __CPU_ZERO_S(setsize, cpusetp) __libc_memset(cpusetp, 0x00, setsize)
#ifndef __NO_XBLOCK
#define __CPU_SET_S(cpuno, setsize, cpusetp)                                           \
	__XBLOCK({                                                                         \
		__size_t const __cs_cpuno = (cpuno);                                           \
		__XRETURN((__cs_cpuno / 8 < (setsize))                                         \
		          ? ((cpusetp)->__bits[__CPUELT(__cs_cpuno)] |= __CPUMASK(__cs_cpuno)) \
		          : 0);                                                                \
	})
#define __CPU_CLR_S(cpuno, setsize, cpusetp)                                            \
	__XBLOCK({                                                                          \
		__size_t const __cs_cpuno = (cpuno);                                            \
		__XRETURN((__cs_cpuno / 8 < (setsize))                                          \
		          ? ((cpusetp)->__bits[__CPUELT(__cs_cpuno)] &= ~__CPUMASK(__cs_cpuno)) \
		          : 0);                                                                 \
	})
#define __CPU_ISSET_S(cpuno, setsize, cpusetp)                                        \
	__XBLOCK({                                                                        \
		__size_t const __cs_cpuno = (cpuno);                                          \
		__XRETURN((__cs_cpuno / 8 < (setsize)) &&                                     \
		          ((cpusetp)->__bits[__CPUELT(__cs_cpuno)] & __CPUMASK(__cs_cpuno))); \
	})
#define __CPU_COUNT_S(setsize, cpusetp)                                            \
	__XBLOCK({                                                                     \
		__STDC_INT_AS_SIZE_T __res = 0;                                            \
		__cpu_mask_t const *__iter, *__end;                                        \
		__end = (__iter = (cpusetp)->__bits) + ((setsize) / sizeof(__cpu_mask_t)); \
		for (; __iter < __end; ++__iter)                                           \
			__res += __CPUMASK_POPCOUNT(*__iter);                                  \
		__XRETURN __res;                                                           \
	})
#define __CPU_ISEMPTY_S(setsize, cpusetp)                                          \
	__XBLOCK({                                                                     \
		int __res = 1;                                                             \
		__cpu_mask_t const *__iter, *__end;                                        \
		__end = (__iter = (cpusetp)->__bits) + ((setsize) / sizeof(__cpu_mask_t)); \
		for (; __iter < __end; ++__iter)                                           \
			if (*__iter) {                                                         \
				__res = 0;                                                         \
				break;                                                             \
			}                                                                      \
		__XRETURN __res;                                                           \
	})

#define __PRIVATE_CPU_OP_S(setsize, destset, srcset1, srcset2, op)  \
	__XBLOCK({                                                      \
		struct __cpu_set_struct *const __dest = (destset);          \
		__cpu_mask_t const *const __arr1 = (srcset1)->__bits;         \
		__cpu_mask_t const *const __arr2 = (srcset2)->__bits;         \
		__SIZE_TYPE__ __i, __imax = (setsize) / sizeof(__cpu_mask_t); \
		for (__i = 0; __i < __imax; ++__i)                          \
			__dest->__bits[__i] = __arr1[__i] op __arr2[__i];       \
		__XRETURN __dest;                                           \
	})
#define __CPU_AND_S(setsize, destset, srcset1, srcset2) __PRIVATE_CPU_OP_S(setsize, destset, srcset1, srcset2, &)
#define __CPU_OR_S(setsize, destset, srcset1, srcset2)  __PRIVATE_CPU_OP_S(setsize, destset, srcset1, srcset2, |)
#define __CPU_XOR_S(setsize, destset, srcset1, srcset2) __PRIVATE_CPU_OP_S(setsize, destset, srcset1, srcset2, ^)
#else /* !__NO_XBLOCK */
#define __CPU_SET_S(cpuno, setsize, cpusetp)                    \
	(((cpuno) / 8 < (setsize))                                  \
	 ? ((cpusetp)->__bits[__CPUELT(cpuno)] |= __CPUMASK(cpuno)) \
	 : 0)
#define __CPU_CLR_S(cpuno, setsize, cpusetp)                     \
	(((cpuno) / 8 < (setsize))                                   \
	 ? ((cpusetp)->__bits[__CPUELT(cpuno)] &= ~__CPUMASK(cpuno)) \
	 : 0)
#define __CPU_ISSET_S(cpuno, setsize, cpusetp) \
	(((cpuno) / 8 < (setsize)) && ((cpusetp)->__bits[__CPUELT(cpuno)] & __CPUMASK(cpuno)))

#define __CPU_COUNT_S(setsize, cpusetp) \
	__cpu_count_s_impl((__SIZE_TYPE__)(setsize), (cpusetp)->__bits)
__LOCAL __ATTR_PURE __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__cpu_count_s_impl)(__SIZE_TYPE__ __count, __cpu_mask_t const *__cpusetp) {
	__STDC_INT_AS_SIZE_T __res = 0;
	__cpu_mask_t const *__iter, *__end;
	__end = (__iter = __cpusetp) + (__count / sizeof(__cpu_mask_t));
	for (; __iter < __end; ++__iter)
		__res += __CPUMASK_POPCOUNT(*__iter);
	return __res;
}

#define __CPU_ISEMPTY_S(setsize, cpusetp) \
	__cpu_isempty_s_impl((__SIZE_TYPE__)(setsize), (cpusetp)->__bits)
__LOCAL __ATTR_PURE int
__NOTHROW_NCX(__cpu_isempty_s_impl)(__SIZE_TYPE__ __count, __cpu_mask_t const *__cpusetp) {
	__cpu_mask_t const *__iter, *__end;
	__end = (__iter = __cpusetp) + (__count / sizeof(__cpu_mask_t));
	for (; __iter < __end; ++__iter) {
		if (*__iter)
			return 0;
	}
	return 1;
}

#define __PRIVATE_DEFINE_CPU_OP_S(name, op)                                       \
	__LOCAL struct __cpu_set_struct *                                             \
	__NOTHROW_NCX(name)(__SIZE_TYPE__ __count, struct __cpu_set_struct *__dest,   \
	                    __cpu_mask_t const *__arr1, __cpu_mask_t const *__arr2) { \
		__SIZE_TYPE__ __i, __imax = __count / sizeof(__cpu_mask_t);               \
		for (__i = 0; __i < __imax; ++__i)                                        \
			__dest->__bits[__i] = __arr1[__i] op __arr2[__i];                     \
		return __dest;                                                            \
	}
#define __CPU_AND_S(setsize, destset, srcset1, srcset2) \
	__cpu_and_s_impl((__SIZE_TYPE__)(setsize), destset, (srcset1)->__bits, (srcset2)->__bits)
#define __CPU_OR_S(setsize, destset, srcset1, srcset2) \
	__cpu_or_s_impl((__SIZE_TYPE__)(setsize), destset, (srcset1)->__bits, (srcset2)->__bits)
#define __CPU_XOR_S(setsize, destset, srcset1, srcset2) \
	__cpu_xor_s_impl((__SIZE_TYPE__)(setsize), destset, (srcset1)->__bits, (srcset2)->__bits)
__PRIVATE_DEFINE_CPU_OP_S(__cpu_and_s_impl, &)
__PRIVATE_DEFINE_CPU_OP_S(__cpu_or_s_impl, |)
__PRIVATE_DEFINE_CPU_OP_S(__cpu_xor_s_impl, ^)
#undef __PRIVATE_DEFINE_CPU_OP_S
#endif /* __NO_XBLOCK */

#define __CPU_EQUAL_S(setsize, cpusetp1, cpusetp2) \
	(__libc_bcmp(cpusetp1, cpusetp2, setsize) == 0)
#define __CPU_ALLOC_SIZE(count) \
	((((count) + __NCPUBITS - 1) / __NCPUBITS) * sizeof(__cpu_mask_t))
#ifdef ____libc_calloc_defined
#define __CPU_ALLOC(count) \
	((struct __cpu_set_struct *)__libc_calloc(((count) + __NCPUBITS - 1) / __NCPUBITS, sizeof(__cpu_mask_t)))
#endif /* ____libc_calloc_defined */

#ifdef ____libc_free_defined
#define __CPU_FREE(cpuset) __libc_free(cpuset)
#else /* ____libc_free_defined */
#define __CPU_FREE(cpuset) (void)0
#endif /* !____libc_free_defined */
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_CPU_SET_H */
