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
#ifndef _KOS_PARTS_MALLOCA_H
#define _KOS_PARTS_MALLOCA_H 1

#include <__stdinc.h>

#include <parts/malloca.h>

#ifdef __clang_tidy__
#define __MallocaHeap __malloca_heap
#define __CallocaHeap __calloca_heap
#define __Malloca     __malloca
#define __Calloca     __calloca
#elif defined(__INTELLISENSE__)
#define __MallocaHeap __malloca_heap
#define __CallocaHeap __calloca_heap
#define __Malloca     __malloca
#define __Calloca     __calloca
#elif defined(__KOS__) && defined(__KERNEL__)
/* In this case, the regular malloca() is already exception-enabled! */
#ifdef __malloca_heap
#define __MallocaHeap __malloca_heap
#endif /* __malloca_heap */
#ifdef __calloca_heap
#define __CallocaHeap __calloca_heap
#endif /* __calloca_heap */
#ifdef __malloca
#define __Malloca __malloca
#endif /* __malloca */
#ifdef __calloca
#define __Calloca __calloca
#endif /* __calloca */
#else /* __KOS__ && __KERNEL__ */
#include <hybrid/__alloca.h>
#include <hybrid/typecore.h>

#include <libc/kos.malloc.h>
#include <libc/string.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef ____libc_Malloc_defined
#ifndef __NO_XBLOCK
#define __MallocaHeap(s)                                                                  \
	__XBLOCK({                                                                            \
		__BYTE_TYPE__ *__mah_res = (__BYTE_TYPE__ *)__libc_Malloc((s) + __MALLOCA_ALIGN); \
		*__mah_res = __MALLOCA_KEY_MALLOC;                                                \
		__XRETURN (void *)(__mah_res + __MALLOCA_ALIGN);                                  \
	})
#define __CallocaHeap(s)                                                                     \
	__XBLOCK({                                                                               \
		__BYTE_TYPE__ *__cah_res = (__BYTE_TYPE__ *)__libc_Calloc(1, (s) + __MALLOCA_ALIGN); \
		*__cah_res = __MALLOCA_KEY_MALLOC;                                                   \
		__XRETURN (void *)(__cah_res + __MALLOCA_ALIGN);                                     \
	})
#define __Malloca(s)                                                \
	__XBLOCK({                                                      \
		__SIZE_TYPE__ const __ma_s = (s) + __MALLOCA_ALIGN;         \
		__BYTE_TYPE__ *__ma_res;                                    \
		if (__ma_s > __MALLOCA_MAX) {                               \
			__ma_res = (__BYTE_TYPE__ *)__libc_Malloc(__ma_s);      \
			*__ma_res = __MALLOCA_KEY_MALLOC;                       \
			__ma_res += __MALLOCA_ALIGN;                            \
		} else {                                                    \
			__ma_res  = (__BYTE_TYPE__ *)__hybrid_alloca(__ma_s);   \
			*__ma_res = __MALLOCA_KEY_ALLOCA;                       \
			(void)__MALLOCA_SKEW_ALLOCA(__ma_res + __MALLOCA_ALIGN, \
			                            __ma_s - __MALLOCA_ALIGN);  \
		}                                                           \
		__XRETURN (void *)(__ma_res + __MALLOCA_ALIGN);             \
	})
#define __Calloca(s)                                              \
	__XBLOCK({                                                    \
		__SIZE_TYPE__ const __ca_s = (s) + __MALLOCA_ALIGN;       \
		__BYTE_TYPE__ *__ca_res;                                  \
		if (__ca_s > __MALLOCA_MAX) {                             \
			__ca_res = (__BYTE_TYPE__ *)__libc_Calloc(1, __ca_s); \
			*__ca_res = __MALLOCA_KEY_MALLOC;                     \
		} else {                                                  \
			__ca_res  = (__BYTE_TYPE__ *)__hybrid_alloca(__ca_s); \
			*__ca_res = __MALLOCA_KEY_ALLOCA;                     \
			__ca_res += __MALLOCA_ALIGN;                          \
			__libc_memset(__ca_res + __MALLOCA_ALIGN, 0,          \
			              __ca_s - __MALLOCA_ALIGN);              \
		}                                                         \
		__XRETURN (void *)(__ca_res + __MALLOCA_ALIGN);           \
	})
#else /* !__NO_XBLOCK */
__NAMESPACE_INT_BEGIN
#define __malloca_mayfail 1
__LOCAL void *(__local_MallocaHeap)(__SIZE_TYPE__ __s) {
	__BYTE_TYPE__ *__res;
	__res  = (__BYTE_TYPE__ *)__libc_Malloc(__s + __MALLOCA_ALIGN);
	*__res = __MALLOCA_KEY_MALLOC;
	return (void *)(__res + __MALLOCA_ALIGN);
}
__LOCAL void *(__local_CallocaHeap)(__SIZE_TYPE__ __s) {
	__BYTE_TYPE__ *__res;
	__res  = (__BYTE_TYPE__ *)__libc_Calloc(1, __s + __MALLOCA_ALIGN);
	*__res = __MALLOCA_KEY_MALLOC;
	return (void *)(__res + __MALLOCA_ALIGN);
}
__NAMESPACE_INT_END

/* Implementation that doesn't make use of X-blocks. */
#define __MallocaHeap(s)  (__NAMESPACE_INT_SYM __local_MallocaHeap(s))
#define __calloca_heap(s) (__NAMESPACE_INT_SYM __local_CallocaHeap(s))
#define __Malloca(s) ((s) > __MALLOCA_MAX - __MALLOCA_ALIGN ? __NAMESPACE_INT_SYM __local_MallocaHeap(s) : __malloca_stack(s))
#define __calloca(s) ((s) > __MALLOCA_MAX - __MALLOCA_ALIGN ? __NAMESPACE_INT_SYM __local_CallocaHeap(s) : __calloca_stack(s))
#endif /* __NO_XBLOCK */
#endif /* !____libc_Malloc_defined */

#if !defined(__Malloca) && defined(__malloca_stack)
#define __Malloca(num_bytes) __malloca_stack(num_bytes)
#endif /* !__Malloca && __malloca_stack */
#if !defined(__Calloca) && defined(__calloca_stack)
#define __Calloca(num_bytes) __calloca_stack(num_bytes)
#endif /* !__Calloca && __calloca_stack */

__SYSDECL_END
#endif /* __CC__ */
#endif /* !__KOS__ || !__KERNEL__ */

#endif /* !_KOS_PARTS_MALLOCA_H */
