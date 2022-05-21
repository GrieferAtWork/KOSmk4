/* HASH CRC-32:0x60897cd8 */
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
#ifndef __local_readdir_defined
#define __local_readdir_defined
#include <__crt.h>
#include <bits/os/dirent.h>
#ifdef __USE_DOS_DIRENT
struct __dirstream;
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(readdir) __ATTR_ACCESS_RW(1) struct dirent *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(readdir))(struct __dirstream *__restrict __dirp) {
	return (struct dirent *)__dos_dirent_readdir(__dirp);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_readdir_defined
#define __local___localdep_readdir_defined
#define __localdep_readdir __LIBC_LOCAL_NAME(readdir)
#endif /* !__local___localdep_readdir_defined */
#else /* __USE_DOS_DIRENT */
#undef __local_readdir_defined
#endif /* !__USE_DOS_DIRENT */
#endif /* !__local_readdir_defined */
