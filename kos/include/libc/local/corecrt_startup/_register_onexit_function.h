/* HASH CRC-32:0x76537148 */
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
#ifndef __local__register_onexit_function_defined
#define __local__register_onexit_function_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
#include <bits/crt/dos/corecrt_startup.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_malloc_usable_size_defined
#define __local___localdep_malloc_usable_size_defined
#ifdef __CRT_HAVE_malloc_usable_size
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_malloc_usable_size,(void *__restrict __mallptr),malloc_usable_size,(__mallptr))
#elif defined(__CRT_HAVE__msize)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_malloc_usable_size,(void *__restrict __mallptr),_msize,(__mallptr))
#else /* ... */
#undef __local___localdep_malloc_usable_size_defined
#endif /* !... */
#endif /* !__local___localdep_malloc_usable_size_defined */
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),__libc_realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_register_onexit_function) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_register_onexit_function))(struct _onexit_table_t *__self, _onexit_t __function) {
	if __unlikely(!__self)
		return -1;
	if (__self->_last >= __self->_end) {
		_onexit_t *__newtab;
		__SIZE_TYPE__ __newcnt;
		__newcnt = (__SIZE_TYPE__)(__self->_last - __self->_first) + 1;
		__newtab = (_onexit_t *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__self->_first, (__newcnt + 1) * sizeof(_onexit_t));
		if __unlikely(!__newtab)
			return -1;
		__newcnt = (__NAMESPACE_LOCAL_SYM __localdep_malloc_usable_size)(__newtab) / sizeof(_onexit_t);
		__self->_last  = (_PVFV *)__newtab + (__SIZE_TYPE__)(__self->_last - __self->_first);
		__self->_end   = (_PVFV *)__newtab + __newcnt;
		__self->_first = (_PVFV *)__newtab;
	}
	*__self->_last++ = (_PVFV)__function;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__register_onexit_function_defined
#define __local___localdep__register_onexit_function_defined
#define __localdep__register_onexit_function __LIBC_LOCAL_NAME(_register_onexit_function)
#endif /* !__local___localdep__register_onexit_function_defined */
#else /* (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize) */
#undef __local__register_onexit_function_defined
#endif /* (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_malloc_usable_size && !__CRT_HAVE__msize) */
#endif /* !__local__register_onexit_function_defined */
