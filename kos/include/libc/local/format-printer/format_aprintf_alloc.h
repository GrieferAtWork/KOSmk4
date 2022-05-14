/* HASH CRC-32:0x8701d749 */
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
#ifndef __local_format_aprintf_alloc_defined
#define __local_format_aprintf_alloc_defined
#include <__crt.h>
#if defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
struct format_aprintf_data;
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE___libc_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),__libc_realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/__assert.h>
#ifndef __format_aprintf_data_defined
#define __format_aprintf_data_defined
struct format_aprintf_data {
	char         *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_aprintf_data_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(format_aprintf_alloc) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(format_aprintf_alloc))(struct format_aprintf_data *__restrict __self, __SIZE_TYPE__ __num_chars) {
	char *__result;
	if (__self->ap_avail < __num_chars) {
		char *__newbuf;
		__SIZE_TYPE__ __min_alloc = __self->ap_used + __num_chars;
		__SIZE_TYPE__ __new_alloc = __self->ap_used + __self->ap_avail;
		if (!__new_alloc)
			__new_alloc = 8;
		while (__new_alloc < __min_alloc)
			__new_alloc *= 2;
		__newbuf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__self->ap_base, (__new_alloc + 1) * sizeof(char));
		if __unlikely(!__newbuf) {
			__new_alloc = __min_alloc;
			__newbuf    = (char *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__self->ap_base, (__new_alloc + 1) * sizeof(char));
			if __unlikely(!__newbuf)
				goto __err;
		}
		__hybrid_assert(__new_alloc >= __self->ap_used + __num_chars);
		__self->ap_base  = __newbuf;
		__self->ap_avail = __new_alloc - __self->ap_used;
	}
	__result = __self->ap_base + __self->ap_used;
	__self->ap_avail -= __num_chars;
	__self->ap_used  += __num_chars;
	return __result;
__err:
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_format_aprintf_alloc_defined
#define __local___localdep_format_aprintf_alloc_defined
#define __localdep_format_aprintf_alloc __LIBC_LOCAL_NAME(format_aprintf_alloc)
#endif /* !__local___localdep_format_aprintf_alloc_defined */
#else /* __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc */
#undef __local_format_aprintf_alloc_defined
#endif /* !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc */
#endif /* !__local_format_aprintf_alloc_defined */
