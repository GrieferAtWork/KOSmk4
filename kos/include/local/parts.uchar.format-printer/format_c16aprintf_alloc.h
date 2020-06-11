/* HASH CRC-32:0x5306f6e7 */
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
#ifndef __local_format_c16aprintf_alloc_defined
#define __local_format_c16aprintf_alloc_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_realloc
#ifndef __format_waprintf_data_defined
#define __format_waprintf_data_defined 1
struct format_waprintf_data {
	__WCHAR_TYPE__      *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif
__NAMESPACE_LOCAL_BEGIN
/* Dependency: realloc from stdlib */
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined 1
#ifdef __realloc_defined
__NAMESPACE_GLB_USING(realloc)
#define __localdep_realloc realloc
#elif defined(__std_realloc_defined)
__NAMESPACE_STD_USING(realloc)
#define __localdep_realloc realloc
#elif __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/__assert.h>
__NAMESPACE_LOCAL_BEGIN
/* Allocate a buffer of `num_wchars' wide-characters at the end of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized, or some other function is used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory */
__LOCAL_LIBC(format_c16aprintf_alloc) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_WUNUSED __ATTR_NONNULL((1)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(format_c16aprintf_alloc))(struct format_c16aprintf_data *__restrict __self, __SIZE_TYPE__ __num_wchars) {
	__CHAR16_TYPE__ *__result;
	if (__self->ap_avail < __num_wchars) {
		__CHAR16_TYPE__ *__newbuf;
		__SIZE_TYPE__ __min_alloc = __self->ap_used + __num_wchars;
		__SIZE_TYPE__ __new_alloc = __self->ap_used + __self->ap_avail;
		if (!__new_alloc)
			__new_alloc = 8;
		while (__new_alloc < __min_alloc)
			__new_alloc *= 2;
		__newbuf = (__CHAR16_TYPE__ *)__localdep_realloc(__self->ap_base, (__new_alloc + 1) * sizeof(__CHAR16_TYPE__));
		if __unlikely(!__newbuf) {
			__new_alloc = __min_alloc;
			__newbuf    = (__CHAR16_TYPE__ *)__localdep_realloc(__self->ap_base, (__new_alloc + 1) * sizeof(__CHAR16_TYPE__));
			if __unlikely(!__newbuf)
				return __NULLPTR;
		}
		__hybrid_assert(__new_alloc >= __self->ap_used + __num_wchars);
		__self->ap_base  = __newbuf;
		__self->ap_avail = __new_alloc - __self->ap_used;
	}
	__result = __self->ap_base + __self->ap_used;
	__self->ap_avail -= __num_wchars;
	__self->ap_used  += __num_wchars;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_format_c16aprintf_alloc_defined
#define __local___localdep_format_c16aprintf_alloc_defined 1
#define __localdep_format_c16aprintf_alloc __LIBC_LOCAL_NAME(format_c16aprintf_alloc)
#endif /* !__local___localdep_format_c16aprintf_alloc_defined */
#else /* __CRT_HAVE_realloc */
#undef __local_format_c16aprintf_alloc_defined
#endif /* !__CRT_HAVE_realloc */
#endif /* !__local_format_c16aprintf_alloc_defined */
