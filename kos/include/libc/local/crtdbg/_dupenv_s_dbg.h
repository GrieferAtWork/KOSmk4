/* HASH CRC-32:0xa5a26d1d */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__dupenv_s_dbg_defined
#define __local__dupenv_s_dbg_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE__dupenv_s
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__dupenv_s_defined
#define __local___localdep__dupenv_s_defined 1
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_NCX,__localdep__dupenv_s,(char **__restrict __pbuf, __SIZE_TYPE__ *__pbuflen, char const *__varname),_dupenv_s,(__pbuf,__pbuflen,__varname))
#endif /* !__local___localdep__dupenv_s_defined */
__LOCAL_LIBC(_dupenv_s_dbg) _Check_return_wat_ __ATTR_NONNULL((3)) __errno_t
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_dupenv_s_dbg))(char **__pbuf, __SIZE_TYPE__ *__pbufsize, char const *__varname, int __block_type, char const *__filename, int __line) {
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return (__NAMESPACE_LOCAL_SYM __localdep__dupenv_s)(__pbuf, __pbufsize, __varname);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__dupenv_s_dbg_defined
#define __local___localdep__dupenv_s_dbg_defined 1
#define __localdep__dupenv_s_dbg __LIBC_LOCAL_NAME(_dupenv_s_dbg)
#endif /* !__local___localdep__dupenv_s_dbg_defined */
#else /* __CRT_HAVE__dupenv_s */
#undef __local__dupenv_s_dbg_defined
#endif /* !__CRT_HAVE__dupenv_s */
#endif /* !__local__dupenv_s_dbg_defined */
