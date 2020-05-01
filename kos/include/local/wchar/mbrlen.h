/* HASH CRC-32:0x8879af9 */
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
#ifndef __local_mbrlen_defined
#define __local_mbrlen_defined 1
#include <__crt.h>
/* Dependency: "mbrtowc" from "wchar" */
#ifndef ____localdep_mbrtowc_defined
#define ____localdep_mbrtowc_defined 1
#ifdef __CRT_HAVE_mbrtowc
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbrtowc,(__WCHAR_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__mbs),mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrtowc)
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbrtowc,(__WCHAR_TYPE__ *__pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__mbs),__mbrtowc,(__pwc,__str,__maxlen,__mbs))
#else /* LIBC: mbrtowc */
#include <local/wchar/mbrtowc.h>
#define __localdep_mbrtowc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrtowc))
#endif /* mbrtowc... */
#endif /* !____localdep_mbrtowc_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(mbrlen) __ATTR_WUNUSED __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mbrlen))(char const *__restrict __str,
                                                    __SIZE_TYPE__ __maxlen,
                                                    __mbstate_t *__mbs) {
#line 305 "kos/src/libc/magic/wchar.c"
	__WCHAR_TYPE__ __wc;
	return __localdep_mbrtowc(&__wc, __str, __maxlen, __mbs);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_mbrlen_defined */
