/* HASH CRC-32:0xa607220 */
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
#ifndef __local_sigcodedesc_np_defined
#define __local_sigcodedesc_np_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_sigcodename_np_defined
#define __local___localdep_sigcodename_np_defined
#ifdef __CRT_HAVE_sigcodename_np
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW_NCX,__localdep_sigcodename_np,(__signo_t __signo, int __code),sigcodename_np,(__signo,__code))
#else /* __CRT_HAVE_sigcodename_np */
__NAMESPACE_LOCAL_END
#include <libc/local/signal/sigcodename_np.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sigcodename_np __LIBC_LOCAL_NAME(sigcodename_np)
#endif /* !__CRT_HAVE_sigcodename_np */
#endif /* !__local___localdep_sigcodename_np_defined */
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined
#ifdef __CRT_HAVE_strend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
__LOCAL_LIBC(sigcodedesc_np) __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sigcodedesc_np))(__signo_t __signo, int __code) {
	char const *__result = (__NAMESPACE_LOCAL_SYM __localdep_sigcodename_np)(__signo, __code);
	if (__result)
		__result = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__result) + 1;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigcodedesc_np_defined
#define __local___localdep_sigcodedesc_np_defined
#define __localdep_sigcodedesc_np __LIBC_LOCAL_NAME(sigcodedesc_np)
#endif /* !__local___localdep_sigcodedesc_np_defined */
#endif /* !__local_sigcodedesc_np_defined */
