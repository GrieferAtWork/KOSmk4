/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _PARTS_MALLOCA_H
#define _PARTS_MALLOCA_H 1

#include <__stdinc.h>
#include <__crt.h>
#include <hybrid/typecore.h>
#include <hybrid/__alloca.h>
#include <libc/malloc.h>
#include <libc/string.h>

__SYSDECL_BEGIN

#ifdef __CC__

/* A hybrid between alloca and malloc, using alloca for
 * small allocations, but malloc() for larger ones.
 * NOTE: In all cases, 'afree()' should be used to clean up a
 *       pointer previously allocated using 'amalloc()' and
 *       friends. */
#if ((defined(__CRT_HAVE_malloc) && defined(__CRT_HAVE_free)) || \
     (defined(__KOS__) && defined(__KERNEL__))) && defined(__hybrid_alloca)
/* Best case: Both heap & stack allocation is possible. */
#ifndef __MALLOCA_ALIGN
#define __MALLOCA_ALIGN __SIZEOF_POINTER__
#endif /* !__MALLOCA_ALIGN */
#ifdef __KERNEL__
#define __MALLOCA_MAX   256 /* Without guard pages, don't be excessive */
#else /* __KERNEL__ */
#include <asm/pagesize.h>
#ifdef __ARCH_PAGESIZE
#define __MALLOCA_MAX __ARCH_PAGESIZE
#else /* __ARCH_PAGESIZE */
#define __MALLOCA_MAX 256
#endif /* !__ARCH_PAGESIZE */
#endif /* !__KERNEL__ */
#ifdef NDEBUG
#define __MALLOCA_KEY_ALLOCA        0
#define __MALLOCA_KEY_MALLOC        1
#define __MALLOCA_SKEW_ALLOCA(p,s) (p)
#define __MALLOCA_GETKEY(p)       ((__BYTE_TYPE__ *)(p))[-__MALLOCA_ALIGN]
#define __MALLOCA_MUSTFREE(p)      (__MALLOCA_GETKEY(p) != __MALLOCA_KEY_ALLOCA)
#else /* NDEBUG */
#include <hybrid/__assert.h>
#define __MALLOCA_KEY_ALLOCA        0x7c
#define __MALLOCA_KEY_MALLOC        0xb3
#define __MALLOCA_GETKEY(p)       ((__BYTE_TYPE__ *)(p))[-__MALLOCA_ALIGN]
#define __MALLOCA_MUSTFREE(p) \
   (__hybrid_assert(__MALLOCA_GETKEY(p) == __MALLOCA_KEY_ALLOCA || \
                    __MALLOCA_GETKEY(p) == __MALLOCA_KEY_MALLOC), \
                    __MALLOCA_GETKEY(p) == __MALLOCA_KEY_MALLOC)
#define __MALLOCA_SKEW_ALLOCA(p,s)  __libc_memset(p,0xcd,s)
#endif /* !NDEBUG */


#ifndef __NO_XBLOCK
#define __malloca_stack(s) \
 __XBLOCK({ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
            __BYTE_TYPE__ *__res = (__BYTE_TYPE__ *)__hybrid_alloca(__s); \
           *__res = __MALLOCA_KEY_ALLOCA,__res += __MALLOCA_ALIGN; \
           (void)__MALLOCA_SKEW_ALLOCA(__res,__s-__MALLOCA_ALIGN); \
            __XRETURN (void *)__res; })
#define __calloca_stack(s) \
 __XBLOCK({ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
            __BYTE_TYPE__ *__res = (__BYTE_TYPE__ *)__hybrid_alloca(__s); \
           *__res = __MALLOCA_KEY_ALLOCA,__res += __MALLOCA_ALIGN; \
            __libc_memset(__res,0,__s-__MALLOCA_ALIGN); \
            __XRETURN (void *)__res; })
#if defined(__KOS__) && defined(__KERNEL__)
#include <kernel/malloc.h>
#ifdef __OMIT_KMALLOC_CONSTANT_P_WRAPPERS
#define __malloca_heap(s) \
 __XBLOCK({ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
            __BYTE_TYPE__ *__res = (__BYTE_TYPE__ *)kmalloc(__s,GFP_NORMAL); \
            *__res = __MALLOCA_KEY_MALLOC,__res += __MALLOCA_ALIGN; \
            __XRETURN (void *)__res; })
#define __malloca(s) \
 __XBLOCK({ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
            __BYTE_TYPE__ *__res; \
            if (__s > __MALLOCA_MAX) { \
              __res = (__BYTE_TYPE__ *)kmalloc(__s,GFP_NORMAL); \
              *__res = __MALLOCA_KEY_MALLOC,__res += __MALLOCA_ALIGN; \
            } else { \
              __res = (__BYTE_TYPE__ *)__hybrid_alloca(__s); \
             *__res = __MALLOCA_KEY_ALLOCA,__res += __MALLOCA_ALIGN; \
             (void)__MALLOCA_SKEW_ALLOCA(__res,__s-__MALLOCA_ALIGN); \
            } \
            __XRETURN (void *)__res; })
#define __calloca_heap(s) \
 __XBLOCK({ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
            __BYTE_TYPE__ *__res = (__BYTE_TYPE__ *)kmalloc(__s,GFP_CALLOC); \
            *__res = __MALLOCA_KEY_MALLOC; __res += __MALLOCA_ALIGN; \
            __XRETURN (void *)__res; })
#define __calloca(s) \
 __XBLOCK({ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
            __BYTE_TYPE__ *__res; \
            if (__s > __MALLOCA_MAX) { \
              __res = (__BYTE_TYPE__ *)kmalloc(__s,GFP_CALLOC); \
              *__res = __MALLOCA_KEY_MALLOC,__res += __MALLOCA_ALIGN; \
            } else { \
              __res = (__BYTE_TYPE__ *)__hybrid_alloca(__s); \
             *__res = __MALLOCA_KEY_ALLOCA,__res += __MALLOCA_ALIGN; \
              __libc_memset(__res,0,__s-__MALLOCA_ALIGN); \
            } \
            __XRETURN (void *)__res; })
#define __freea(p) \
 __XBLOCK({ void *const __p = (p); \
            if (__MALLOCA_MUSTFREE(__p)) \
                __os_free((void *)((__BYTE_TYPE__ *)__p-__MALLOCA_ALIGN)); \
           (void)0; })
#else /* __OMIT_KMALLOC_CONSTANT_P_WRAPPERS */
#define __malloca_heap(s) \
 __XBLOCK({ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
            __BYTE_TYPE__ *__res = (__BYTE_TYPE__ *)kmalloc(__s,GFP_NORMAL); \
            *__res = __MALLOCA_KEY_MALLOC,__res += __MALLOCA_ALIGN; \
            __XRETURN (void *)__res; })
#define __malloca(s) \
 __XBLOCK({ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
            __BYTE_TYPE__ *__res; \
            if (__s > __MALLOCA_MAX) { \
              __res = (__BYTE_TYPE__ *)kmalloc(__s,GFP_NORMAL); \
              *__res = __MALLOCA_KEY_MALLOC,__res += __MALLOCA_ALIGN; \
            } else { \
              __res = (__BYTE_TYPE__ *)__hybrid_alloca(__s); \
             *__res = __MALLOCA_KEY_ALLOCA,__res += __MALLOCA_ALIGN; \
             (void)__MALLOCA_SKEW_ALLOCA(__res,__s-__MALLOCA_ALIGN); \
            } \
            __XRETURN (void *)__res; })
#define __calloca_heap(s) \
 __XBLOCK({ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
            __BYTE_TYPE__ *__res = (__BYTE_TYPE__ *)kmalloc(__s,GFP_CALLOC); \
            *__res = __MALLOCA_KEY_MALLOC; __res += __MALLOCA_ALIGN; \
            __XRETURN (void *)__res; })
#define __calloca(s) \
 __XBLOCK({ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
            __BYTE_TYPE__ *__res; \
            if (__s > __MALLOCA_MAX) { \
              __res = (__BYTE_TYPE__ *)kmalloc(__s,GFP_CALLOC); \
              *__res = __MALLOCA_KEY_MALLOC,__res += __MALLOCA_ALIGN; \
            } else { \
              __res = (__BYTE_TYPE__ *)__hybrid_alloca(__s); \
             *__res = __MALLOCA_KEY_ALLOCA,__res += __MALLOCA_ALIGN; \
              __libc_memset(__res,0,__s-__MALLOCA_ALIGN); \
            } \
            __XRETURN (void *)__res; })
#define __freea(p) \
 __XBLOCK({ void *const __p = (p); \
            if (__MALLOCA_MUSTFREE(__p)) \
                kfree((void *)((__BYTE_TYPE__ *)__p-__MALLOCA_ALIGN)); \
           (void)0; })
#endif /* !__OMIT_KMALLOC_CONSTANT_P_WRAPPERS */
#else /* __KOS__ && __KERNEL__ */
#define __malloca_heap(s) \
 __XBLOCK({ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
            __BYTE_TYPE__ *__res = (__BYTE_TYPE__ *)__libc_malloc(__s); \
            if (__res) *__res = __MALLOCA_KEY_MALLOC,__res += __MALLOCA_ALIGN; \
            __XRETURN (void *)__res; })
#define __malloca(s) \
 __XBLOCK({ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
            __BYTE_TYPE__ *__res; \
            if (__s > __MALLOCA_MAX) { \
              __res = (__BYTE_TYPE__ *)__libc_malloc(__s); \
              if (__res) *__res = __MALLOCA_KEY_MALLOC,__res += __MALLOCA_ALIGN; \
            } else { \
              __res = (__BYTE_TYPE__ *)__hybrid_alloca(__s); \
             *__res = __MALLOCA_KEY_ALLOCA,__res += __MALLOCA_ALIGN; \
             (void)__MALLOCA_SKEW_ALLOCA(__res,__s-__MALLOCA_ALIGN); \
            } \
            __XRETURN (void *)__res; })
#define __calloca_heap(s) \
 __XBLOCK({ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
            __BYTE_TYPE__ *__res = (__BYTE_TYPE__ *)__libc_calloc(1,__s); \
            if (__res) { *__res = __MALLOCA_KEY_MALLOC; __res += __MALLOCA_ALIGN; } \
            __XRETURN (void *)__res; })
#define __calloca(s) \
 __XBLOCK({ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
            __BYTE_TYPE__ *__res; \
            if (__s > __MALLOCA_MAX) { \
              __res = (__BYTE_TYPE__ *)__libc_calloc(1,__s); \
              if (__res) *__res = __MALLOCA_KEY_MALLOC,__res += __MALLOCA_ALIGN; \
            } else { \
              __res = (__BYTE_TYPE__ *)__hybrid_alloca(__s); \
             *__res = __MALLOCA_KEY_ALLOCA,__res += __MALLOCA_ALIGN; \
              __libc_memset(__res,0,__s-__MALLOCA_ALIGN); \
            } \
            __XRETURN (void *)__res; })
#define __freea(p) \
 __XBLOCK({ void *const __p = (p); \
            if (__MALLOCA_MUSTFREE(__p)) \
                __libc_free((void *)((__BYTE_TYPE__ *)__p-__MALLOCA_ALIGN)); \
           (void)0; })
#endif /* !__KOS__ || !__KERNEL__ */
#else /* !__NO_XBLOCK */
__NAMESPACE_INT_BEGIN
#if defined(__KOS__) && defined(__KERNEL__)
#ifdef __OMIT_KMALLOC_CONSTANT_P_WRAPPERS
__LOCAL void *(__LIBCCALL __local_malloca_heap)(__SIZE_TYPE__ __s) {
 __BYTE_TYPE__ *__res;
 __res = (__BYTE_TYPE__ *)kmalloc(__s+__MALLOCA_ALIGN,GFP_NORMAL);
 *__res = __MALLOCA_KEY_MALLOC;
 __res += __MALLOCA_ALIGN;
 return (void *)__res;
}
__LOCAL void *(__LIBCCALL __local_calloca_heap)(__SIZE_TYPE__ __s) {
 __BYTE_TYPE__ *__res;
 __res = (__BYTE_TYPE__ *)kmalloc(__s+__MALLOCA_ALIGN,GFP_CALLOC);
 *__res = __MALLOCA_KEY_MALLOC;
 __res += __MALLOCA_ALIGN;
 return (void *)__res;
}
__LOCAL void (__LIBCCALL __local_afree)(void *__p) {
 if (__MALLOCA_MUSTFREE(__p))
     __os_free((void *)((__BYTE_TYPE__ *)__p-__MALLOCA_ALIGN));
}
#else /* __OMIT_KMALLOC_CONSTANT_P_WRAPPERS */
__LOCAL void *(__LIBCCALL __local_malloca_heap)(__SIZE_TYPE__ __s) {
 __BYTE_TYPE__ *__res;
 __res = (__BYTE_TYPE__ *)kmalloc(__s+__MALLOCA_ALIGN,GFP_NORMAL);
 *__res = __MALLOCA_KEY_MALLOC;
 __res += __MALLOCA_ALIGN;
 return (void *)__res;
}
__LOCAL void *(__LIBCCALL __local_calloca_heap)(__SIZE_TYPE__ __s) {
 __BYTE_TYPE__ *__res;
 __res = (__BYTE_TYPE__ *)kmalloc(__s+__MALLOCA_ALIGN,GFP_CALLOC);
 *__res = __MALLOCA_KEY_MALLOC;
 __res += __MALLOCA_ALIGN;
 return (void *)__res;
}
__LOCAL void (__LIBCCALL __local_afree)(void *__p) {
 if (__MALLOCA_MUSTFREE(__p))
     kfree((void *)((__BYTE_TYPE__ *)__p-__MALLOCA_ALIGN));
}
#endif /* !__OMIT_KMALLOC_CONSTANT_P_WRAPPERS */
#else /* __KOS__ && __KERNEL__ */
__LOCAL void *(__LIBCCALL __local_malloca_heap)(__SIZE_TYPE__ __s) {
 __BYTE_TYPE__ *__res;
 __res = (__BYTE_TYPE__ *)__libc_malloc(__s+__MALLOCA_ALIGN);
 if (__res) { *__res = __MALLOCA_KEY_MALLOC; __res += __MALLOCA_ALIGN; }
 return (void *)__res;
}
__LOCAL void *(__LIBCCALL __local_calloca_heap)(__SIZE_TYPE__ __s) {
 __BYTE_TYPE__ *__res;
 __res = (__BYTE_TYPE__ *)__libc_calloc(1,__s+__MALLOCA_ALIGN);
 if (__res) { *__res = __MALLOCA_KEY_MALLOC; __res += __MALLOCA_ALIGN; }
 return (void *)__res;
}
__LOCAL void (__LIBCCALL __local_afree)(void *__p) {
 if (__MALLOCA_MUSTFREE(__p))
     __libc_free((void *)((__BYTE_TYPE__ *)__p-__MALLOCA_ALIGN));
}
#endif /* !__KOS__ || !__KERNEL__ */
__LOCAL void *(__LIBCCALL __local_minita_stack)(void *__p, __SIZE_TYPE__ __s) {
 *(__BYTE_TYPE__ *)__p = __MALLOCA_KEY_ALLOCA;
 return __MALLOCA_SKEW_ALLOCA((__BYTE_TYPE__ *)__p+__MALLOCA_ALIGN,__s);
}
__LOCAL void *(__LIBCCALL __local_cinita_stack)(void *__p, __SIZE_TYPE__ __s) {
 *(__BYTE_TYPE__ *)__p = __MALLOCA_KEY_ALLOCA;
 return __libc_memset((__BYTE_TYPE__ *)__p+__MALLOCA_ALIGN,0,__s);
}
__NAMESPACE_INT_END

/* Implementation that doesn't make use of X-blocks. */
#define __malloca_stack(s) (__NAMESPACE_INT_SYM __local_minita_stack(__hybrid_alloca((s)+__MALLOCA_ALIGN),(s)))
#define __malloca_heap(s)  (__NAMESPACE_INT_SYM __local_malloca_heap(s))
#define __malloca(s) \
  ((s) > __MALLOCA_MAX-__MALLOCA_ALIGN ? __NAMESPACE_INT_SYM __local_malloca_heap(s) : \
         __NAMESPACE_INT_SYM __local_minita_stack(__hybrid_alloca((s)+__MALLOCA_ALIGN),(s)))
#define __calloca_stack(s) (__NAMESPACE_INT_SYM __local_cinita_stack(__hybrid_alloca((s)+__MALLOCA_ALIGN),(s)))
#define __calloca_heap(s)  (__NAMESPACE_INT_SYM __local_calloca_heap(s))
#define __calloca(s) \
  ((s) > __MALLOCA_MAX-__MALLOCA_ALIGN ? __NAMESPACE_INT_SYM __local_calloca_heap(s) : \
         __NAMESPACE_INT_SYM __local_cinita_stack(__hybrid_alloca((s)+__MALLOCA_ALIGN),(s)))
#define __freea(p) (__NAMESPACE_INT_SYM __local_afree(p))
#endif /* __NO_XBLOCK */
#if defined(__KOS__) && defined(__KERNEL__)
#ifdef __OMIT_KMALLOC_CONSTANT_P_WRAPPERS
#define __malloca_tryhard(result,s) \
do{ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
    __BYTE_TYPE__ *__res; \
    if (__s > __MALLOCA_MAX && (__res = (__BYTE_TYPE__ *)__os_malloc_nx(__s,GFP_NORMAL)) != NULL) { \
     *__res = __MALLOCA_KEY_MALLOC,__res += __MALLOCA_ALIGN; \
    } else { \
      __res = (__BYTE_TYPE__ *)__hybrid_alloca(__s); \
     *__res = __MALLOCA_KEY_ALLOCA,__res += __MALLOCA_ALIGN; \
     (void)__MALLOCA_SKEW_ALLOCA(__res,__s-__MALLOCA_ALIGN); \
    } \
    *(void **)&(result) = __res; \
}__WHILE0
#define __calloca_tryhard(result,s) \
do{ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
    __BYTE_TYPE__ *__res; \
    if (__s > __MALLOCA_MAX && (__res = (__BYTE_TYPE__ *)__os_malloc_nx(GFP_CALLOC)) != NULL) { \
     *__res = __MALLOCA_KEY_MALLOC,__res += __MALLOCA_ALIGN; \
    } else { \
      __res = (__BYTE_TYPE__ *)__hybrid_alloca(__s); \
     *__res = __MALLOCA_KEY_ALLOCA,__res += __MALLOCA_ALIGN; \
      __libc_memset(__res,0,__s-__MALLOCA_ALIGN); \
    } \
    *(void **)&(result) = __res; \
}__WHILE0
#else /* __OMIT_KMALLOC_CONSTANT_P_WRAPPERS */
#define __malloca_tryhard(result,s) \
do{ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
    __BYTE_TYPE__ *__res; \
    if (__s > __MALLOCA_MAX && (__res = (__BYTE_TYPE__ *)kmalloc_nx(__s,GFP_NORMAL)) != NULL) { \
     *__res = __MALLOCA_KEY_MALLOC,__res += __MALLOCA_ALIGN; \
    } else { \
      __res = (__BYTE_TYPE__ *)__hybrid_alloca(__s); \
     *__res = __MALLOCA_KEY_ALLOCA,__res += __MALLOCA_ALIGN; \
     (void)__MALLOCA_SKEW_ALLOCA(__res,__s-__MALLOCA_ALIGN); \
    } \
    *(void **)&(result) = __res; \
}__WHILE0
#define __calloca_tryhard(result,s) \
do{ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
    __BYTE_TYPE__ *__res; \
    if (__s > __MALLOCA_MAX && (__res = (__BYTE_TYPE__ *)kmalloc_nx(GFP_CALLOC)) != NULL) { \
     *__res = __MALLOCA_KEY_MALLOC,__res += __MALLOCA_ALIGN; \
    } else { \
      __res = (__BYTE_TYPE__ *)__hybrid_alloca(__s); \
     *__res = __MALLOCA_KEY_ALLOCA,__res += __MALLOCA_ALIGN; \
      __libc_memset(__res,0,__s-__MALLOCA_ALIGN); \
    } \
    *(void **)&(result) = __res; \
}__WHILE0
#endif /* !__OMIT_KMALLOC_CONSTANT_P_WRAPPERS */
#else /* __KOS__ && __KERNEL__ */
#define __malloca_tryhard(result,s) \
do{ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
    __BYTE_TYPE__ *__res; \
    if (__s > __MALLOCA_MAX && (__res = (__BYTE_TYPE__ *)__libc_malloc(__s)) != NULL) { \
     *__res = __MALLOCA_KEY_MALLOC,__res += __MALLOCA_ALIGN; \
    } else { \
      __res = (__BYTE_TYPE__ *)__hybrid_alloca(__s); \
     *__res = __MALLOCA_KEY_ALLOCA,__res += __MALLOCA_ALIGN; \
     (void)__MALLOCA_SKEW_ALLOCA(__res,__s-__MALLOCA_ALIGN); \
    } \
    *(void **)&(result) = __res; \
}__WHILE0
#define __calloca_tryhard(result,s) \
do{ __SIZE_TYPE__ const __s = (s)+__MALLOCA_ALIGN; \
    __BYTE_TYPE__ *__res; \
    if (__s > __MALLOCA_MAX && (__res = (__BYTE_TYPE__ *)__libc_calloc(1,__s)) != NULL) { \
     *__res = __MALLOCA_KEY_MALLOC,__res += __MALLOCA_ALIGN; \
    } else { \
      __res = (__BYTE_TYPE__ *)__hybrid_alloca(__s); \
     *__res = __MALLOCA_KEY_ALLOCA,__res += __MALLOCA_ALIGN; \
      __libc_memset(__res,0,__s-__MALLOCA_ALIGN); \
    } \
    *(void **)&(result) = __res; \
}__WHILE0
#endif /* !__KOS__ || !__KERNEL__ */
#elif defined(__hybrid_alloca)
/* Fallback: Only stack allocation is possible. */
#define __malloca(num_bytes)         __hybrid_alloca(num_bytes)
#ifndef __NO_XBLOCK
#define __calloca(num_bytes) \
        __XBLOCK({ __SIZE_TYPE__ const __calloca_num_bytes = (num_bytes); \
                   __XRETURN __libc_memset(__hybrid_alloca(__calloca_num_bytes),0,__calloca_num_bytes); })
#else /* !__NO_XBLOCK */
#define __calloca(num_bytes) __libc_memset(__hybrid_alloca(num_bytes),0,(num_bytes))
#endif /* __NO_XBLOCK */
#define __malloca_stack(num_bytes)   __malloca(num_bytes)
#define __calloca_stack(num_bytes)   __calloca(num_bytes)
#define __freea(ptr)         (void)(ptr)
#define __malloca_tryhard(result,num_bytes) (void)(*(void **)&(result) = __hybrid_alloca(num_bytes))
#define __calloca_tryhard(result,num_bytes) \
do{ __SIZE_TYPE__ const __calloca_num_bytes = (num_bytes); \
    *(void **)&(result) = __libc_memset(__hybrid_alloca(num_bytes),0,__calloca_num_bytes); \
}__WHILE0
#elif defined(__CRT_HAVE_malloc) && defined(__CRT_HAVE_free)
/* Fallback: Only heap allocation is possible. */
#define __malloca(num_bytes)         __libc_malloc(num_bytes)
#define __calloca(num_bytes)         __libc_calloc(1,num_bytes)
#define __malloca_heap(num_bytes)    __libc_malloc(num_bytes)
#define __calloca_heap(num_bytes)    __libc_calloc(1,num_bytes)
#define __freea(ptr)                 __libc_free(ptr)
#define __malloca_tryhard_mayfail 1
#define __malloca_tryhard(result,num_bytes) (void)(*(void **)&(result)=__libc_malloc(num_bytes))
#define __calloca_tryhard(result,num_bytes) (void)(*(void **)&(result)=__libc_calloc(1,num_bytes))
#else
/* Fallback: No dynamic allocation is possible at all (behave as allocation-failure in all cases). */
#define __NO_MALLOCA 1
#define __malloca(num_bytes) ((void)(num_bytes),(void *)0)
#define __calloca(num_bytes) ((void)(num_bytes),(void *)0)
#define __freea(ptr)         (void)(ptr)
#define __malloca_tryhard_mayfail 1
#define __malloca_tryhard(result,num_bytes) (void)(*(void **)&(result)=NULL)
#define __calloca_tryhard(result,num_bytes) (void)(*(void **)&(result)=NULL)
#endif

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_MALLOCA_H */
