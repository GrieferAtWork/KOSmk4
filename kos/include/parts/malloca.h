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
#ifndef _PARTS_MALLOCA_H
#define _PARTS_MALLOCA_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/__alloca.h>
#include <hybrid/typecore.h>

#include <libc/malloc.h>
#include <libc/string.h>

#ifdef __CC__
__SYSDECL_BEGIN

/* A hybrid between alloca and malloc, using alloca for
 * small  allocations,  but malloc()  for  larger ones.
 * NOTE: In all cases, 'freea()' should be used to clean up a
 *       pointer previously allocated  using 'malloca()'  and
 *       friends. */
#if (((defined(____libc_malloc_defined) && defined(____libc_free_defined)) || \
      (defined(__KOS__) && defined(__KERNEL__))) &&                           \
     defined(__hybrid_alloca))
/* Best case: Both heap & stack allocation is possible. */
#ifndef __MALLOCA_ALIGN
#define __MALLOCA_ALIGN __SIZEOF_POINTER__
#endif /* !__MALLOCA_ALIGN */
#ifndef __MALLOCA_MAX
#ifdef __KERNEL__
#define __MALLOCA_MAX 256 /* Without guard pages, don't be excessive */
#else /* __KERNEL__ */
#include <asm/pagesize.h>
#ifdef __ARCH_PAGESIZE
#define __MALLOCA_MAX __ARCH_PAGESIZE
#else /* __ARCH_PAGESIZE */
#define __MALLOCA_MAX 256
#endif /* !__ARCH_PAGESIZE */
#endif /* !__KERNEL__ */
#endif /* !__MALLOCA_MAX */
#ifndef __MALLOCA_MUSTFREE
#if defined(NDEBUG) || defined(NDEBUG_INIT)
#define __MALLOCA_KEY_ALLOCA        0
#define __MALLOCA_KEY_MALLOC        1
#define __MALLOCA_SKEW_ALLOCA(p, s) (p)
#define __MALLOCA_GETKEY(p)         ((__BYTE_TYPE__ *)(p))[-__MALLOCA_ALIGN]
#define __MALLOCA_MUSTFREE(p)       (__MALLOCA_GETKEY(p) != __MALLOCA_KEY_ALLOCA)
#else /* NDEBUG || NDEBUG_INIT */
#include <hybrid/__assert.h>
#define __MALLOCA_KEY_ALLOCA 0x7c
#define __MALLOCA_KEY_MALLOC 0xb3
#define __MALLOCA_GETKEY(p)  ((__BYTE_TYPE__ *)(p))[-__MALLOCA_ALIGN]
#define __MALLOCA_MUSTFREE(p)                                       \
	(__hybrid_assert(__MALLOCA_GETKEY(p) == __MALLOCA_KEY_ALLOCA || \
	                 __MALLOCA_GETKEY(p) == __MALLOCA_KEY_MALLOC),  \
	 __MALLOCA_GETKEY(p) == __MALLOCA_KEY_MALLOC)
#define __MALLOCA_SKEW_ALLOCA(p, s) __libc_memset(p, 0xcd, s)
#endif /* !NDEBUG && !NDEBUG_INIT */
#endif /* !__MALLOCA_MUSTFREE */


#ifndef __NO_XBLOCK
#define __malloca_stack(s)                                                   \
	__XBLOCK({                                                               \
		__SIZE_TYPE__ const __ma_s = (s) + __MALLOCA_ALIGN;                  \
		__BYTE_TYPE__ *__ma_res = (__BYTE_TYPE__ *)__hybrid_alloca(__ma_s);  \
		*__ma_res = __MALLOCA_KEY_ALLOCA;                                    \
		__ma_res += __MALLOCA_ALIGN;                                         \
		__XRETURN __MALLOCA_SKEW_ALLOCA(__ma_res, __ma_s - __MALLOCA_ALIGN); \
	})
#define __calloca_stack(s)                                                  \
	__XBLOCK({                                                              \
		__SIZE_TYPE__ const __ca_s = (s) + __MALLOCA_ALIGN;                 \
		__BYTE_TYPE__ *__ca_res = (__BYTE_TYPE__ *)__hybrid_alloca(__ca_s); \
		*__ca_res = __MALLOCA_KEY_ALLOCA;                                   \
		__ca_res += __MALLOCA_ALIGN;                                        \
		__XRETURN __libc_memset(__ca_res, 0, __ca_s - __MALLOCA_ALIGN);     \
	})
#if defined(__KOS__) && defined(__KERNEL__)
#include <kernel/malloc.h>
#if defined(__clang_tidy__) && !defined(NO_INSTRUMENT_KMALLOC)
#undef __malloca_stack
#undef __calloca_stack
#define __malloca_heap(s)  malloc(s)
#define __calloca_heap(s)  calloc(s, 1)
#define __malloca_stack(s) malloc(s)
#define __calloca_stack(s) calloc(s, 1)
#define __malloca(s)       malloc(s)
#define __calloca(s)       calloc(s, 1)
#define __freea(p)         free(p)
#elif defined(__OMIT_KMALLOC_CONSTANT_P_WRAPPERS)
#define __malloca_heap(s)                                                                       \
	__XBLOCK({                                                                                  \
		__BYTE_TYPE__ *__mah_res = (__BYTE_TYPE__ *)kmalloc((s) + __MALLOCA_ALIGN, GFP_NORMAL); \
		*__mah_res = __MALLOCA_KEY_MALLOC;                                                      \
		__mah_res += __MALLOCA_ALIGN;                                                           \
		__XRETURN (void *)__mah_res;                                                            \
	})
#undef __malloca_mayfail
#define __malloca(s)                                                         \
	__XBLOCK({                                                               \
		__SIZE_TYPE__ const __ma_s = (s) + __MALLOCA_ALIGN;                  \
		__BYTE_TYPE__ *__ma_res;                                             \
		if (__ma_s > __MALLOCA_MAX) {                                        \
			__ma_res  = (__BYTE_TYPE__ *)kmalloc(__ma_s, GFP_NORMAL);        \
			*__ma_res = __MALLOCA_KEY_MALLOC;                                \
			__ma_res += __MALLOCA_ALIGN;                                     \
		} else {                                                             \
			__ma_res  = (__BYTE_TYPE__ *)__hybrid_alloca(__ma_s);            \
			*__ma_res = __MALLOCA_KEY_ALLOCA;                                \
			__ma_res += __MALLOCA_ALIGN;                                     \
			(void)__MALLOCA_SKEW_ALLOCA(__ma_res, __ma_s - __MALLOCA_ALIGN); \
		}                                                                    \
		__XRETURN (void *)__ma_res;                                          \
	})
#define __calloca_heap(s)                                                                       \
	__XBLOCK({                                                                                  \
		__BYTE_TYPE__ *__cah_res = (__BYTE_TYPE__ *)kmalloc((s) + __MALLOCA_ALIGN, GFP_CALLOC); \
		*__cah_res = __MALLOCA_KEY_MALLOC;                                                      \
		__cah_res += __MALLOCA_ALIGN;                                                           \
		__XRETURN (void *)__cah_res;                                                            \
	})
#define __calloca(s)                                                       \
	__XBLOCK({                                                             \
		__SIZE_TYPE__ const __ca_s = (s) + __MALLOCA_ALIGN;                \
		__BYTE_TYPE__ *__ca_res;                                           \
		if (__ca_s > __MALLOCA_MAX) {                                      \
			__ca_res  = (__BYTE_TYPE__ *)kmalloc(__ca_s, GFP_CALLOC);      \
			*__ca_res = __MALLOCA_KEY_MALLOC, __ca_res += __MALLOCA_ALIGN; \
		} else {                                                           \
			__ca_res  = (__BYTE_TYPE__ *)__hybrid_alloca(__ca_s);          \
			*__ca_res = __MALLOCA_KEY_ALLOCA, __ca_res += __MALLOCA_ALIGN; \
			__libc_memset(__ca_res, 0, __ca_s - __MALLOCA_ALIGN);          \
		}                                                                  \
		__XRETURN (void *)__ca_res;                                        \
	})
#define __freea(p)                                                          \
	__XBLOCK({                                                              \
		void *const __fa_p = (p);                                           \
		if (__MALLOCA_MUSTFREE(__fa_p))                                     \
			__os_free((void *)((__BYTE_TYPE__ *)__fa_p - __MALLOCA_ALIGN)); \
		(void)0;                                                            \
	})
#else /* __OMIT_KMALLOC_CONSTANT_P_WRAPPERS */
#define __malloca_heap(s)                                                                       \
	__XBLOCK({                                                                                  \
		__BYTE_TYPE__ *__mah_res = (__BYTE_TYPE__ *)kmalloc((s) + __MALLOCA_ALIGN, GFP_NORMAL); \
		*__mah_res = __MALLOCA_KEY_MALLOC;                                                      \
		__mah_res += __MALLOCA_ALIGN;                                                           \
		__XRETURN (void *)__mah_res;                                                            \
	})
#undef __malloca_mayfail
#define __malloca(s)                                                         \
	__XBLOCK({                                                               \
		__SIZE_TYPE__ const __ma_s = (s) + __MALLOCA_ALIGN;                  \
		__BYTE_TYPE__ *__ma_res;                                             \
		if (__ma_s > __MALLOCA_MAX) {                                        \
			__ma_res  = (__BYTE_TYPE__ *)kmalloc(__ma_s, GFP_NORMAL);        \
			*__ma_res = __MALLOCA_KEY_MALLOC, __ma_res += __MALLOCA_ALIGN;   \
		} else {                                                             \
			__ma_res  = (__BYTE_TYPE__ *)__hybrid_alloca(__ma_s);            \
			*__ma_res = __MALLOCA_KEY_ALLOCA, __ma_res += __MALLOCA_ALIGN;   \
			(void)__MALLOCA_SKEW_ALLOCA(__ma_res, __ma_s - __MALLOCA_ALIGN); \
		}                                                                    \
		__XRETURN (void *)__ma_res;                                          \
	})
#define __calloca_heap(s)                                                                       \
	__XBLOCK({                                                                                  \
		__BYTE_TYPE__ *__cah_res = (__BYTE_TYPE__ *)kmalloc((s) + __MALLOCA_ALIGN, GFP_CALLOC); \
		*__cah_res = __MALLOCA_KEY_MALLOC;                                                      \
		__cah_res += __MALLOCA_ALIGN;                                                           \
		__XRETURN (void *)__cah_res;                                                            \
	})
#define __calloca(s)                                                       \
	__XBLOCK({                                                             \
		__SIZE_TYPE__ const __ca_s = (s) + __MALLOCA_ALIGN;                \
		__BYTE_TYPE__ *__ca_res;                                           \
		if (__ca_s > __MALLOCA_MAX) {                                      \
			__ca_res  = (__BYTE_TYPE__ *)kmalloc(__ca_s, GFP_CALLOC);      \
			*__ca_res = __MALLOCA_KEY_MALLOC, __ca_res += __MALLOCA_ALIGN; \
		} else {                                                           \
			__ca_res  = (__BYTE_TYPE__ *)__hybrid_alloca(__ca_s);          \
			*__ca_res = __MALLOCA_KEY_ALLOCA, __ca_res += __MALLOCA_ALIGN; \
			__libc_memset(__ca_res, 0, __ca_s - __MALLOCA_ALIGN);          \
		}                                                                  \
		__XRETURN (void *)__ca_res;                                        \
	})
#define __freea(p)                                                      \
	__XBLOCK({                                                          \
		void *const __fa_p = (p);                                       \
		if (__MALLOCA_MUSTFREE(__fa_p))                                 \
			kfree((void *)((__BYTE_TYPE__ *)__fa_p - __MALLOCA_ALIGN)); \
		(void)0;                                                        \
	})
#endif /* !__OMIT_KMALLOC_CONSTANT_P_WRAPPERS */
#else /* __KOS__ && __KERNEL__ */
#define __malloca_heap(s)                                                                 \
	__XBLOCK({                                                                            \
		__BYTE_TYPE__ *__mah_res = (__BYTE_TYPE__ *)__libc_malloc((s) + __MALLOCA_ALIGN); \
		if __likely(__mah_res)                                                            \
			*__mah_res = __MALLOCA_KEY_MALLOC, __mah_res += __MALLOCA_ALIGN;              \
		__XRETURN (void *)__mah_res;                                                      \
	})
#define __malloca_mayfail 1
#define __malloca(s)                                                         \
	__XBLOCK({                                                               \
		__SIZE_TYPE__ const __ma_s = (s) + __MALLOCA_ALIGN;                  \
		__BYTE_TYPE__ *__ma_res;                                             \
		if (__ma_s > __MALLOCA_MAX) {                                        \
			__ma_res = (__BYTE_TYPE__ *)__libc_malloc(__ma_s);               \
			if __likely(__ma_res) {                                          \
				*__ma_res = __MALLOCA_KEY_MALLOC;                            \
				__ma_res += __MALLOCA_ALIGN;                                 \
			}                                                                \
		} else {                                                             \
			__ma_res  = (__BYTE_TYPE__ *)__hybrid_alloca(__ma_s);            \
			*__ma_res = __MALLOCA_KEY_ALLOCA;                                \
			__ma_res += __MALLOCA_ALIGN;                                     \
			(void)__MALLOCA_SKEW_ALLOCA(__ma_res, __ma_s - __MALLOCA_ALIGN); \
		}                                                                    \
		__XRETURN (void *)__ma_res;                                          \
	})
#define __calloca_heap(s)                                                                    \
	__XBLOCK({                                                                               \
		__BYTE_TYPE__ *__cah_res = (__BYTE_TYPE__ *)__libc_calloc(1, (s) + __MALLOCA_ALIGN); \
		if __likely(__cah_res) {                                                             \
			*__cah_res = __MALLOCA_KEY_MALLOC;                                               \
			__cah_res += __MALLOCA_ALIGN;                                                    \
		}                                                                                    \
		__XRETURN (void *)__cah_res;                                                         \
	})
#define __calloca(s)                                              \
	__XBLOCK({                                                    \
		__SIZE_TYPE__ const __ca_s = (s) + __MALLOCA_ALIGN;       \
		__BYTE_TYPE__ *__ca_res;                                  \
		if (__ca_s > __MALLOCA_MAX) {                             \
			__ca_res = (__BYTE_TYPE__ *)__libc_calloc(1, __ca_s); \
			if __likely(__ca_res) {                               \
				*__ca_res = __MALLOCA_KEY_MALLOC;                 \
				__ca_res += __MALLOCA_ALIGN;                      \
			}                                                     \
		} else {                                                  \
			__ca_res  = (__BYTE_TYPE__ *)__hybrid_alloca(__ca_s); \
			*__ca_res = __MALLOCA_KEY_ALLOCA;                     \
			__ca_res += __MALLOCA_ALIGN;                          \
			__libc_memset(__ca_res, 0, __ca_s - __MALLOCA_ALIGN); \
		}                                                         \
		__XRETURN (void *)__ca_res;                               \
	})
#define __freea(p)                                                            \
	__XBLOCK({                                                                \
		void *const __fa_p = (p);                                             \
		if (__MALLOCA_MUSTFREE(__fa_p))                                       \
			__libc_free((void *)((__BYTE_TYPE__ *)__fa_p - __MALLOCA_ALIGN)); \
		(void)0;                                                              \
	})
#endif /* !__KOS__ || !__KERNEL__ */
#else /* !__NO_XBLOCK */
__NAMESPACE_INT_BEGIN
#if defined(__KOS__) && defined(__KERNEL__)
#ifdef __OMIT_KMALLOC_CONSTANT_P_WRAPPERS
#undef __malloca_mayfail
__LOCAL void *(__local_malloca_heap)(__SIZE_TYPE__ __s) {
	__BYTE_TYPE__ *__res;
	__res  = (__BYTE_TYPE__ *)kmalloc(__s + __MALLOCA_ALIGN, GFP_NORMAL);
	*__res = __MALLOCA_KEY_MALLOC;
	__res += __MALLOCA_ALIGN;
	return (void *)__res;
}
__LOCAL void *(__local_calloca_heap)(__SIZE_TYPE__ __s) {
	__BYTE_TYPE__ *__res;
	__res  = (__BYTE_TYPE__ *)kmalloc(__s + __MALLOCA_ALIGN, GFP_CALLOC);
	*__res = __MALLOCA_KEY_MALLOC;
	__res += __MALLOCA_ALIGN;
	return (void *)__res;
}
__LOCAL void __NOTHROW(__local_freea)(void *__p) {
	if (__MALLOCA_MUSTFREE(__p))
		__os_free((void *)((__BYTE_TYPE__ *)__p - __MALLOCA_ALIGN));
}
#else  /* __OMIT_KMALLOC_CONSTANT_P_WRAPPERS */
#undef __malloca_mayfail
__LOCAL void *(__local_malloca_heap)(__SIZE_TYPE__ __s) {
	__BYTE_TYPE__ *__res;
	__res  = (__BYTE_TYPE__ *)kmalloc(__s + __MALLOCA_ALIGN, GFP_NORMAL);
	*__res = __MALLOCA_KEY_MALLOC;
	__res += __MALLOCA_ALIGN;
	return (void *)__res;
}
__LOCAL void *(__local_calloca_heap)(__SIZE_TYPE__ __s) {
	__BYTE_TYPE__ *__res;
	__res  = (__BYTE_TYPE__ *)kmalloc(__s + __MALLOCA_ALIGN, GFP_CALLOC);
	*__res = __MALLOCA_KEY_MALLOC;
	__res += __MALLOCA_ALIGN;
	return (void *)__res;
}
__LOCAL void __NOTHROW(__local_freea)(void *__p) {
	if (__MALLOCA_MUSTFREE(__p))
		kfree((void *)((__BYTE_TYPE__ *)__p - __MALLOCA_ALIGN));
}
#endif /* !__OMIT_KMALLOC_CONSTANT_P_WRAPPERS */
#else  /* __KOS__ && __KERNEL__ */
#define __malloca_mayfail 1
__LOCAL void *__NOTHROW_NCX(__local_malloca_heap)(__SIZE_TYPE__ __s) {
	__BYTE_TYPE__ *__res;
	__res = (__BYTE_TYPE__ *)__libc_malloc(__s + __MALLOCA_ALIGN);
	if (__res) {
		*__res = __MALLOCA_KEY_MALLOC;
		__res += __MALLOCA_ALIGN;
	}
	return (void *)__res;
}
__LOCAL void *__NOTHROW_NCX(__local_calloca_heap)(__SIZE_TYPE__ __s) {
	__BYTE_TYPE__ *__res;
	__res = (__BYTE_TYPE__ *)__libc_calloc(1, __s + __MALLOCA_ALIGN);
	if (__res) {
		*__res = __MALLOCA_KEY_MALLOC;
		__res += __MALLOCA_ALIGN;
	}
	return (void *)__res;
}
__LOCAL void __NOTHROW_NCX(__local_freea)(void *__p) {
	if (__MALLOCA_MUSTFREE(__p))
		__libc_free((void *)((__BYTE_TYPE__ *)__p - __MALLOCA_ALIGN));
}
#endif /* !__KOS__ || !__KERNEL__ */
__LOCAL void *__NOTHROW_NCX(__local_minita_stack)(void *__p, __SIZE_TYPE__ __s) {
	*(__BYTE_TYPE__ *)__p = __MALLOCA_KEY_ALLOCA;
	return __MALLOCA_SKEW_ALLOCA((__BYTE_TYPE__ *)__p + __MALLOCA_ALIGN, __s);
}
__LOCAL void *__NOTHROW_NCX(__local_cinita_stack)(void *__p, __SIZE_TYPE__ __s) {
	*(__BYTE_TYPE__ *)__p = __MALLOCA_KEY_ALLOCA;
	return __libc_memset((__BYTE_TYPE__ *)__p + __MALLOCA_ALIGN, 0, __s);
}
__NAMESPACE_INT_END

/* Implementation that doesn't make use of X-blocks. */
#define __malloca_stack(s) \
	(__NAMESPACE_INT_SYM __local_minita_stack(__hybrid_alloca((s) + __MALLOCA_ALIGN), (s)))
#define __malloca_heap(s) \
	(__NAMESPACE_INT_SYM __local_malloca_heap(s))
#define __malloca(s)                               \
	((s) > __MALLOCA_MAX - __MALLOCA_ALIGN         \
	 ? __NAMESPACE_INT_SYM __local_malloca_heap(s) \
	 : __NAMESPACE_INT_SYM __local_minita_stack(__hybrid_alloca((s) + __MALLOCA_ALIGN), (s)))
#define __calloca_stack(s) \
	(__NAMESPACE_INT_SYM __local_cinita_stack(__hybrid_alloca((s) + __MALLOCA_ALIGN), (s)))
#define __calloca_heap(s) \
	(__NAMESPACE_INT_SYM __local_calloca_heap(s))
#define __calloca(s)                               \
	((s) > __MALLOCA_MAX - __MALLOCA_ALIGN         \
	 ? __NAMESPACE_INT_SYM __local_calloca_heap(s) \
	 : __NAMESPACE_INT_SYM __local_cinita_stack(__hybrid_alloca((s) + __MALLOCA_ALIGN), (s)))
#define __freea(p) (__NAMESPACE_INT_SYM __local_freea(p))
#endif /* __NO_XBLOCK */
#if defined(__KOS__) && defined(__KERNEL__)
#if defined(__clang_tidy__) && !defined(NO_INSTRUMENT_KMALLOC)
#define __malloca_tryhard(result, s) (*(void **)&(result) = malloc(s))
#define __calloca_tryhard(result, s) (*(void **)&(result) = calloc(s, 1))
#elif defined(__OMIT_KMALLOC_CONSTANT_P_WRAPPERS)
#define __malloca_tryhard(result, s)                                                                                         \
	do {                                                                                                                     \
		__SIZE_TYPE__ const __math_s = (s) + __MALLOCA_ALIGN;                                                                \
		__BYTE_TYPE__ *__math_res;                                                                                           \
		if (__math_s > __MALLOCA_MAX && (__math_res = (__BYTE_TYPE__ *)__os_malloc_nx(__math_s, GFP_NORMAL)) != __NULLPTR) { \
			*__math_res = __MALLOCA_KEY_MALLOC;                                                                              \
			__math_res += __MALLOCA_ALIGN;                                                                                   \
		} else {                                                                                                             \
			__math_res  = (__BYTE_TYPE__ *)__hybrid_alloca(__math_s);                                                        \
			*__math_res = __MALLOCA_KEY_ALLOCA;                                                                              \
			__math_res += __MALLOCA_ALIGN;                                                                                   \
			(void)__MALLOCA_SKEW_ALLOCA(__math_res, __math_s - __MALLOCA_ALIGN);                                             \
		}                                                                                                                    \
		*(void **)&(result) = __math_res;                                                                                    \
	}	__WHILE0
#define __calloca_tryhard(result, s)                                                                               \
	do {                                                                                                           \
		__SIZE_TYPE__ const __cath_s = (s) + __MALLOCA_ALIGN;                                                      \
		__BYTE_TYPE__ *__cath_res;                                                                                 \
		if (__cath_s > __MALLOCA_MAX && (__cath_res = (__BYTE_TYPE__ *)__os_malloc_nx(GFP_CALLOC)) != __NULLPTR) { \
			*__cath_res = __MALLOCA_KEY_MALLOC;                                                                    \
			__cath_res += __MALLOCA_ALIGN;                                                                         \
		} else {                                                                                                   \
			__cath_res  = (__BYTE_TYPE__ *)__hybrid_alloca(__cath_s);                                              \
			*__cath_res = __MALLOCA_KEY_ALLOCA;                                                                    \
			__cath_res += __MALLOCA_ALIGN;                                                                         \
			__libc_memset(__cath_res, 0, __cath_s - __MALLOCA_ALIGN);                                              \
		}                                                                                                          \
		*(void **)&(result) = __cath_res;                                                                          \
	}	__WHILE0
#else /* __OMIT_KMALLOC_CONSTANT_P_WRAPPERS */
#define __malloca_tryhard(result, s)                                                                                     \
	do {                                                                                                                 \
		__SIZE_TYPE__ const __math_s = (s) + __MALLOCA_ALIGN;                                                            \
		__BYTE_TYPE__ *__math_res;                                                                                       \
		if (__math_s > __MALLOCA_MAX && (__math_res = (__BYTE_TYPE__ *)kmalloc_nx(__math_s, GFP_NORMAL)) != __NULLPTR) { \
			*__math_res = __MALLOCA_KEY_MALLOC;                                                                          \
			__math_res += __MALLOCA_ALIGN;                                                                               \
		} else {                                                                                                         \
			__math_res  = (__BYTE_TYPE__ *)__hybrid_alloca(__math_s);                                                    \
			*__math_res = __MALLOCA_KEY_ALLOCA;                                                                          \
			__math_res += __MALLOCA_ALIGN;                                                                               \
			(void)__MALLOCA_SKEW_ALLOCA(__math_res, __math_s - __MALLOCA_ALIGN);                                         \
		}                                                                                                                \
		*(void **)&(result) = __math_res;                                                                                \
	}	__WHILE0
#define __calloca_tryhard(result, s)                                                                           \
	do {                                                                                                       \
		__SIZE_TYPE__ const __cath_s = (s) + __MALLOCA_ALIGN;                                                  \
		__BYTE_TYPE__ *__cath_res;                                                                             \
		if (__cath_s > __MALLOCA_MAX && (__cath_res = (__BYTE_TYPE__ *)kmalloc_nx(GFP_CALLOC)) != __NULLPTR) { \
			*__cath_res = __MALLOCA_KEY_MALLOC;                                                                \
			__cath_res += __MALLOCA_ALIGN;                                                                     \
		} else {                                                                                               \
			__cath_res  = (__BYTE_TYPE__ *)__hybrid_alloca(__cath_s);                                          \
			*__cath_res = __MALLOCA_KEY_ALLOCA;                                                                \
			__cath_res += __MALLOCA_ALIGN;                                                                     \
			__libc_memset(__cath_res, 0, __cath_s - __MALLOCA_ALIGN);                                          \
		}                                                                                                      \
		*(void **)&(result) = __cath_res;                                                                      \
	}	__WHILE0
#endif /* !__OMIT_KMALLOC_CONSTANT_P_WRAPPERS */
#else  /* __KOS__ && __KERNEL__ */
#define __malloca_tryhard(result, s)                                                                            \
	do {                                                                                                        \
		__SIZE_TYPE__ const __math_s = (s) + __MALLOCA_ALIGN;                                                   \
		__BYTE_TYPE__ *__math_res;                                                                              \
		if (__math_s > __MALLOCA_MAX && (__math_res = (__BYTE_TYPE__ *)__libc_malloc(__math_s)) != __NULLPTR) { \
			*__math_res = __MALLOCA_KEY_MALLOC;                                                                 \
			__math_res += __MALLOCA_ALIGN;                                                                      \
		} else {                                                                                                \
			__math_res  = (__BYTE_TYPE__ *)__hybrid_alloca(__math_s);                                           \
			*__math_res = __MALLOCA_KEY_ALLOCA;                                                                 \
			__math_res += __MALLOCA_ALIGN;                                                                      \
			(void)__MALLOCA_SKEW_ALLOCA(__math_res, __math_s - __MALLOCA_ALIGN);                                \
		}                                                                                                       \
		*(void **)&(result) = __math_res;                                                                       \
	}	__WHILE0
#define __calloca_tryhard(result, s)                                                                               \
	do {                                                                                                           \
		__SIZE_TYPE__ const __cath_s = (s) + __MALLOCA_ALIGN;                                                      \
		__BYTE_TYPE__ *__cath_res;                                                                                 \
		if (__cath_s > __MALLOCA_MAX && (__cath_res = (__BYTE_TYPE__ *)__libc_calloc(1, __cath_s)) != __NULLPTR) { \
			*__cath_res = __MALLOCA_KEY_MALLOC;                                                                    \
			__cath_res += __MALLOCA_ALIGN;                                                                         \
		} else {                                                                                                   \
			__cath_res  = (__BYTE_TYPE__ *)__hybrid_alloca(__cath_s);                                              \
			*__cath_res = __MALLOCA_KEY_ALLOCA;                                                                    \
			__cath_res += __MALLOCA_ALIGN;                                                                         \
			__libc_memset(__cath_res, 0, __cath_s - __MALLOCA_ALIGN);                                              \
		}                                                                                                          \
		*(void **)&(result) = __cath_res;                                                                          \
	}	__WHILE0
#endif /* !__KOS__ || !__KERNEL__ */
#elif defined(__hybrid_alloca)
/* Fallback: Only stack allocation is possible. */
#undef __malloca_mayfail
#define __malloca(num_bytes) \
	__hybrid_alloca(num_bytes)
#ifndef __NO_XBLOCK
#define __calloca(num_bytes)                                                                   \
	__XBLOCK({                                                                                 \
		__SIZE_TYPE__ const __calloca_num_bytes = (num_bytes);                                 \
		__XRETURN __libc_memset(__hybrid_alloca(__calloca_num_bytes), 0, __calloca_num_bytes); \
	})
#else /* !__NO_XBLOCK */
#define __calloca(num_bytes) \
	__libc_memset(__hybrid_alloca(num_bytes), 0, num_bytes)
#endif /* __NO_XBLOCK */
#define __malloca_stack(num_bytes) __malloca(num_bytes)
#define __calloca_stack(num_bytes) __calloca(num_bytes)
#define __freea(ptr)               (void)(ptr)
#define __malloca_tryhard(result, num_bytes) \
	(void)(*(void **)&(result) = __hybrid_alloca(num_bytes))
#define __calloca_tryhard(result, num_bytes)                                                     \
	do {                                                                                         \
		__SIZE_TYPE__ const __calloca_num_bytes = (num_bytes);                                   \
		*(void **)&(result) = __libc_memset(__hybrid_alloca(num_bytes), 0, __calloca_num_bytes); \
	}	__WHILE0
#elif defined(____libc_malloc_defined) && defined(____libc_free_defined)
/* Fallback: Only heap allocation is possible. */
#define __malloca_mayfail                    1
#define __malloca(num_bytes)                 __libc_malloc(num_bytes)
#define __calloca(num_bytes)                 __libc_calloc(1, num_bytes)
#define __malloca_heap(num_bytes)            __libc_malloc(num_bytes)
#define __calloca_heap(num_bytes)            __libc_calloc(1, num_bytes)
#define __freea(ptr)                         __libc_free(ptr)
#define __malloca_tryhard_mayfail            1
#define __malloca_tryhard(result, num_bytes) (void)(*(void **)&(result) = __libc_malloc(num_bytes))
#define __calloca_tryhard(result, num_bytes) (void)(*(void **)&(result) = __libc_calloc(1, num_bytes))
#else /* ... */
/* Fallback: No dynamic allocation is possible at all (behave as allocation-failure in all cases). */
#define __NO_MALLOCA                         1
#define __malloca_mayfail                    1
#define __malloca(num_bytes)                 ((void)(num_bytes), (void *)0)
#define __calloca(num_bytes)                 ((void)(num_bytes), (void *)0)
#define __freea(ptr)                         (void)(ptr)
#define __malloca_tryhard_mayfail            1
#define __malloca_tryhard(result, num_bytes) (void)(*(void **)&(result) = __NULLPTR)
#define __calloca_tryhard(result, num_bytes) (void)(*(void **)&(result) = __NULLPTR)
#endif /* !... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PARTS_MALLOCA_H */
