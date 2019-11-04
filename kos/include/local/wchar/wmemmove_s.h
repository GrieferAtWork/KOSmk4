/* HASH CRC-32:0xb4ffcefe */
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
#ifndef __local_wmemmove_s_defined
#define __local_wmemmove_s_defined 1
#include <parts/errno.h>
/* Dependency: "wmemmove" from "wchar" */
#ifndef ____localdep_wmemmove_defined
#define ____localdep_wmemmove_defined 1
#ifdef __CRT_HAVE_wmemmove
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemmove,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ const *__src, __SIZE_TYPE__ __num_chars),wmemmove,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memmovew) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemmove,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ const *__src, __SIZE_TYPE__ __num_chars),memmovew,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memmovel) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemmove,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ const *__src, __SIZE_TYPE__ __num_chars),memmovel,(__dst,__src,__num_chars))
#else /* LIBC: wmemmove */
#include <local/wchar/wmemmove.h>
#define __localdep_wmemmove (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemmove))
#endif /* wmemmove... */
#endif /* !____localdep_wmemmove_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wmemmove_s) __ATTR_NONNULL((1, 3)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wmemmove_s))(__WCHAR_TYPE__ *__dst,
                                                        __SIZE_TYPE__ __dstlength,
                                                        __WCHAR_TYPE__ const *__src,
                                                        __SIZE_TYPE__ __srclength) {
#line 4454 "kos/src/libc/magic/string.c"

	if (!__srclength)
		return 0;
	if (!__dst || !__src)
		return __EINVAL;
	if (__dstlength < __srclength)
		return __ERANGE;
	__localdep_wmemmove(__dst, __src, __srclength);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wmemmove_s_defined */
