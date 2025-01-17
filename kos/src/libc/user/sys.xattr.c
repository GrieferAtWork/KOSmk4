/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_XATTR_C
#define GUARD_LIBC_USER_SYS_XATTR_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include "sys.xattr.h"

DECL_BEGIN

/*[[[head:libc_setxattr,hash:CRC-32=0x35606a7d]]]*/
/* >> setxattr(2)
 * @param: flags: One of `XATTR_*', or `0' */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_IN(1) ATTR_IN(2) ATTR_INS(3, 4) int
NOTHROW_RPC(LIBCCALL libc_setxattr)(char const *path,
                                    char const *name,
                                    void const *buf,
                                    size_t bufsize,
                                    __STDC_INT_AS_UINT_T flags)
/*[[[body:libc_setxattr]]]*/
{
	errno_t result;
	result = sys_setxattr(path, name, buf, bufsize, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setxattr]]]*/

/*[[[head:libc_lsetxattr,hash:CRC-32=0x8f2c71a5]]]*/
/* >> lsetxattr(2)
 * @param: flags: One of `XATTR_*', or `0' */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_IN(1) ATTR_IN(2) ATTR_INS(3, 4) int
NOTHROW_RPC(LIBCCALL libc_lsetxattr)(char const *path,
                                     char const *name,
                                     void const *buf,
                                     size_t bufsize,
                                     __STDC_INT_AS_UINT_T flags)
/*[[[body:libc_lsetxattr]]]*/
{
	errno_t result;
	result = sys_lsetxattr(path, name, buf, bufsize, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_lsetxattr]]]*/

/*[[[head:libc_fsetxattr,hash:CRC-32=0xc8c0521]]]*/
/* >> fsetxattr(2)
 * @param: flags: One of `XATTR_*', or `0' */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_FDARG(1) ATTR_IN(2) ATTR_INS(3, 4) int
NOTHROW_RPC(LIBCCALL libc_fsetxattr)(fd_t fd,
                                     char const *name,
                                     void const *buf,
                                     size_t bufsize,
                                     __STDC_INT_AS_UINT_T flags)
/*[[[body:libc_fsetxattr]]]*/
{
	errno_t result;
	result = sys_fsetxattr(fd, name, buf, bufsize, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fsetxattr]]]*/

/*[[[head:libc_getxattr,hash:CRC-32=0xe7b9b9be]]]*/
/* >> getxattr(2) */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_IN(1) ATTR_IN(2) ATTR_OUTS(3, 4) ssize_t
NOTHROW_RPC(LIBCCALL libc_getxattr)(char const *path,
                                    char const *name,
                                    void *buf,
                                    size_t bufsize)
/*[[[body:libc_getxattr]]]*/
{
	ssize_t result;
	result = sys_getxattr(path, name, buf, bufsize);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getxattr]]]*/

/*[[[head:libc_lgetxattr,hash:CRC-32=0x4f5fe4be]]]*/
/* >> lgetxattr(2) */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_IN(1) ATTR_IN(2) ATTR_OUTS(3, 4) ssize_t
NOTHROW_RPC(LIBCCALL libc_lgetxattr)(char const *path,
                                     char const *name,
                                     void *buf,
                                     size_t bufsize)
/*[[[body:libc_lgetxattr]]]*/
{
	ssize_t result;
	result = sys_lgetxattr(path, name, buf, bufsize);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_lgetxattr]]]*/

/*[[[head:libc_fgetxattr,hash:CRC-32=0x489244f1]]]*/
/* >> fgetxattr(2) */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_FDARG(1) ATTR_IN(2) ATTR_OUTS(3, 4) ssize_t
NOTHROW_RPC(LIBCCALL libc_fgetxattr)(fd_t fd,
                                     char const *name,
                                     void *buf,
                                     size_t bufsize)
/*[[[body:libc_fgetxattr]]]*/
{
	ssize_t result;
	result = sys_fgetxattr(fd, name, buf, bufsize);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fgetxattr]]]*/

/*[[[head:libc_listxattr,hash:CRC-32=0x51636bba]]]*/
/* >> listxattr(2) */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_IN(1) ATTR_OUTS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_listxattr)(char const *path,
                                     char *listbuf,
                                     size_t listbufsize)
/*[[[body:libc_listxattr]]]*/
{
	ssize_t result;
	result = sys_listxattr(path, listbuf, listbufsize);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_listxattr]]]*/

/*[[[head:libc_llistxattr,hash:CRC-32=0xdb9e0b5a]]]*/
/* >> llistxattr(2) */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_IN(1) ATTR_OUTS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_llistxattr)(char const *path,
                                      char *listbuf,
                                      size_t listbufsize)
/*[[[body:libc_llistxattr]]]*/
{
	ssize_t result;
	result = sys_llistxattr(path, listbuf, listbufsize);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_llistxattr]]]*/

/*[[[head:libc_flistxattr,hash:CRC-32=0xb95b8f19]]]*/
/* >> flistxattr(2) */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_FDARG(1) ATTR_OUTS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_flistxattr)(fd_t fd,
                                      char *listbuf,
                                      size_t listbufsize)
/*[[[body:libc_flistxattr]]]*/
{
	ssize_t result;
	result = sys_flistxattr(fd, listbuf, listbufsize);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_flistxattr]]]*/

/*[[[head:libc_removexattr,hash:CRC-32=0xeabaab1e]]]*/
/* >> removexattr(2) */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_IN(1) ATTR_IN(2) int
NOTHROW_RPC(LIBCCALL libc_removexattr)(char const *path,
                                       char const *name)
/*[[[body:libc_removexattr]]]*/
{
	ssize_t result;
	result = sys_removexattr(path, name);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_removexattr]]]*/

/*[[[head:libc_lremovexattr,hash:CRC-32=0x95b22a6b]]]*/
/* >> lremovexattr(2) */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_IN(1) ATTR_IN(2) int
NOTHROW_RPC(LIBCCALL libc_lremovexattr)(char const *path,
                                        char const *name)
/*[[[body:libc_lremovexattr]]]*/
{
	ssize_t result;
	result = sys_lremovexattr(path, name);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_lremovexattr]]]*/

/*[[[head:libc_fremovexattr,hash:CRC-32=0x650a48fe]]]*/
/* >> fremovexattr(2) */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_FDARG(1) ATTR_IN(2) int
NOTHROW_RPC(LIBCCALL libc_fremovexattr)(fd_t fd,
                                        char const *name)
/*[[[body:libc_fremovexattr]]]*/
{
	ssize_t result;
	result = sys_fremovexattr(fd, name);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fremovexattr]]]*/



/*[[[start:exports,hash:CRC-32=0xf9ce52a4]]]*/
DEFINE_PUBLIC_ALIAS_P(setxattr,libc_setxattr,ATTR_IN(1) ATTR_IN(2) ATTR_INS(3, 4),int,NOTHROW_RPC,LIBCCALL,(char const *path, char const *name, void const *buf, size_t bufsize, __STDC_INT_AS_UINT_T flags),(path,name,buf,bufsize,flags));
DEFINE_PUBLIC_ALIAS_P(lsetxattr,libc_lsetxattr,ATTR_IN(1) ATTR_IN(2) ATTR_INS(3, 4),int,NOTHROW_RPC,LIBCCALL,(char const *path, char const *name, void const *buf, size_t bufsize, __STDC_INT_AS_UINT_T flags),(path,name,buf,bufsize,flags));
DEFINE_PUBLIC_ALIAS_P(fsetxattr,libc_fsetxattr,ATTR_FDARG(1) ATTR_IN(2) ATTR_INS(3, 4),int,NOTHROW_RPC,LIBCCALL,(fd_t fd, char const *name, void const *buf, size_t bufsize, __STDC_INT_AS_UINT_T flags),(fd,name,buf,bufsize,flags));
DEFINE_PUBLIC_ALIAS_P(getxattr,libc_getxattr,ATTR_IN(1) ATTR_IN(2) ATTR_OUTS(3, 4),ssize_t,NOTHROW_RPC,LIBCCALL,(char const *path, char const *name, void *buf, size_t bufsize),(path,name,buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(lgetxattr,libc_lgetxattr,ATTR_IN(1) ATTR_IN(2) ATTR_OUTS(3, 4),ssize_t,NOTHROW_RPC,LIBCCALL,(char const *path, char const *name, void *buf, size_t bufsize),(path,name,buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(fgetxattr,libc_fgetxattr,ATTR_FDARG(1) ATTR_IN(2) ATTR_OUTS(3, 4),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, char const *name, void *buf, size_t bufsize),(fd,name,buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(listxattr,libc_listxattr,ATTR_IN(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(char const *path, char *listbuf, size_t listbufsize),(path,listbuf,listbufsize));
DEFINE_PUBLIC_ALIAS_P(llistxattr,libc_llistxattr,ATTR_IN(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(char const *path, char *listbuf, size_t listbufsize),(path,listbuf,listbufsize));
DEFINE_PUBLIC_ALIAS_P(flistxattr,libc_flistxattr,ATTR_FDARG(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, char *listbuf, size_t listbufsize),(fd,listbuf,listbufsize));
DEFINE_PUBLIC_ALIAS_P(removexattr,libc_removexattr,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBCCALL,(char const *path, char const *name),(path,name));
DEFINE_PUBLIC_ALIAS_P(lremovexattr,libc_lremovexattr,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBCCALL,(char const *path, char const *name),(path,name));
DEFINE_PUBLIC_ALIAS_P(fremovexattr,libc_fremovexattr,ATTR_FDARG(1) ATTR_IN(2),int,NOTHROW_RPC,LIBCCALL,(fd_t fd, char const *name),(fd,name));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_XATTR_C */
