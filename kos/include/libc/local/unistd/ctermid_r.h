/* HASH CRC-32:0xda24abfe */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ctermid_r_defined
#define __local_ctermid_r_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ctermid_defined
#define __local___localdep_ctermid_defined
#ifdef __CRT_HAVE_ctermid
__CREDIRECT(__ATTR_RETNONNULL,char *,__NOTHROW_NCX,__localdep_ctermid,(char *__s),ctermid,(__s))
#else /* __CRT_HAVE_ctermid */
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/ctermid.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ctermid __LIBC_LOCAL_NAME(ctermid)
#endif /* !__CRT_HAVE_ctermid */
#endif /* !__local___localdep_ctermid_defined */
__LOCAL_LIBC(ctermid_r) __ATTR_OUT_OPT(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ctermid_r))(char *__s) {
	return __s ? (__NAMESPACE_LOCAL_SYM __localdep_ctermid)(__s) : __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ctermid_r_defined
#define __local___localdep_ctermid_r_defined
#define __localdep_ctermid_r __LIBC_LOCAL_NAME(ctermid_r)
#endif /* !__local___localdep_ctermid_r_defined */
#endif /* !__local_ctermid_r_defined */
