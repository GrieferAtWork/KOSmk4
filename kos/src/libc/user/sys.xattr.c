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
#ifndef GUARD_LIBC_USER_SYS_XATTR_C
#define GUARD_LIBC_USER_SYS_XATTR_C 1

#include "../api.h"
#include "sys.xattr.h"
#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:setxattr,hash:0x7d07f8ca]]]*/
/* Set the attribute NAME of the file pointed to by PATH to VALUE
 * (which is SIZE bytes long). Return 0 on success, -1 for errors
 * @param: flags: 0, or a one of `XATTR_*' */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.setxattr") int
NOTHROW_RPC(LIBCCALL libc_setxattr)(char const *path,
                                    char const *name,
                                    void const *buf,
                                    size_t bufsize,
                                    int flags)
/*[[[body:setxattr]]]*/
{
	errno_t result;
	result = sys_setxattr(path, name, buf, bufsize, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:setxattr]]]*/

/*[[[head:lsetxattr,hash:0x77e35ad5]]]*/
/* Set the attribute NAME of the file pointed to by PATH to VALUE (which is
 * SIZE bytes long), not following symlinks for the last pathname component.
 * Return 0 on success, -1 for errors
 * @param: flags: 0, or a one of `XATTR_*' */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.lsetxattr") int
NOTHROW_RPC(LIBCCALL libc_lsetxattr)(char const *path,
                                     char const *name,
                                     void const *buf,
                                     size_t bufsize,
                                     int flags)
/*[[[body:lsetxattr]]]*/
{
	errno_t result;
	result = sys_lsetxattr(path, name, buf, bufsize, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:lsetxattr]]]*/

/*[[[head:fsetxattr,hash:0xf796f6b8]]]*/
/* Set the attribute NAME of the file descriptor FD to VALUE
 * (which is SIZE bytes long). Return 0 on success, -1 for errors
 * @param: flags: 0, or a one of `XATTR_*' */
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.fsetxattr") int
NOTHROW_RPC(LIBCCALL libc_fsetxattr)(fd_t fd,
                                     char const *name,
                                     void const *buf,
                                     size_t bufsize,
                                     int flags)
/*[[[body:fsetxattr]]]*/
{
	errno_t result;
	result = sys_fsetxattr(fd, name, buf, bufsize, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:fsetxattr]]]*/

/*[[[head:getxattr,hash:0xd008a986]]]*/
/* Get the attribute NAME of the file pointed to by PATH to VALUE
 * (which is SIZE bytes long). Return 0 on success, -1 for errors */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.getxattr") ssize_t
NOTHROW_RPC(LIBCCALL libc_getxattr)(char const *path,
                                    char const *name,
                                    void *buf,
                                    size_t bufsize)
/*[[[body:getxattr]]]*/
{
	ssize_t result;
	result = sys_getxattr(path, name, buf, bufsize);
	return libc_seterrno_syserr(result);
}
/*[[[end:getxattr]]]*/

/*[[[head:lgetxattr,hash:0xbf417ba3]]]*/
/* Get the attribute NAME of the file pointed to by PATH to VALUE (which is
 * SIZE bytes long), not following symlinks for the last pathname component.
 * Return 0 on success, -1 for errors */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.lgetxattr") ssize_t
NOTHROW_RPC(LIBCCALL libc_lgetxattr)(char const *path,
                                     char const *name,
                                     void *buf,
                                     size_t bufsize)
/*[[[body:lgetxattr]]]*/
{
	ssize_t result;
	result = sys_lgetxattr(path, name, buf, bufsize);
	return libc_seterrno_syserr(result);
}
/*[[[end:lgetxattr]]]*/

/*[[[head:fgetxattr,hash:0x8167180d]]]*/
/* Get the attribute NAME of the file descriptor FD to VALUE
 * (which is SIZE bytes long). Return 0 on success, -1 for errors */
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.fgetxattr") ssize_t
NOTHROW_RPC(LIBCCALL libc_fgetxattr)(fd_t fd,
                                     char const *name,
                                     void *buf,
                                     size_t bufsize)
/*[[[body:fgetxattr]]]*/
{
	ssize_t result;
	result = sys_fgetxattr(fd, name, buf, bufsize);
	return libc_seterrno_syserr(result);
}
/*[[[end:fgetxattr]]]*/

/*[[[head:listxattr,hash:0x9ecc74cd]]]*/
/* List attributes of the file pointed to by PATH into the
 * user-supplied buffer LIST (which is SIZE bytes big).
 * Return 0 on success, -1 for errors */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.listxattr") ssize_t
NOTHROW_RPC(LIBCCALL libc_listxattr)(char const *path,
                                     char *listbuf,
                                     size_t listbufsize)
/*[[[body:listxattr]]]*/
{
	ssize_t result;
	result = sys_listxattr(path, listbuf, listbufsize);
	return libc_seterrno_syserr(result);
}
/*[[[end:listxattr]]]*/

/*[[[head:llistxattr,hash:0xf806365c]]]*/
/* List attributes of the file pointed to by PATH into the user-supplied
 * buffer LIST (which is SIZE bytes big), not following symlinks for the
 * last pathname component. Return 0 on success, -1 for errors */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.llistxattr") ssize_t
NOTHROW_RPC(LIBCCALL libc_llistxattr)(char const *path,
                                      char *listbuf,
                                      size_t listbufsize)
/*[[[body:llistxattr]]]*/
{
	ssize_t result;
	result = sys_llistxattr(path, listbuf, listbufsize);
	return libc_seterrno_syserr(result);
}
/*[[[end:llistxattr]]]*/

/*[[[head:flistxattr,hash:0xcee2b00a]]]*/
/* List attributes of the file descriptor FD into the user-supplied buffer
 * LIST (which is SIZE bytes big). Return 0 on success, -1 for errors */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.flistxattr") ssize_t
NOTHROW_RPC(LIBCCALL libc_flistxattr)(fd_t fd,
                                      char *listbuf,
                                      size_t listbufsize)
/*[[[body:flistxattr]]]*/
{
	ssize_t result;
	result = sys_flistxattr(fd, listbuf, listbufsize);
	return libc_seterrno_syserr(result);
}
/*[[[end:flistxattr]]]*/

/*[[[head:removexattr,hash:0xe2c1f20f]]]*/
/* Remove the attribute NAME from the file pointed to by PATH.
 * Return 0 on success, -1 for errors */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.removexattr") int
NOTHROW_RPC(LIBCCALL libc_removexattr)(char const *path,
                                       char const *name)
/*[[[body:removexattr]]]*/
{
	ssize_t result;
	result = sys_removexattr(path, name);
	return libc_seterrno_syserr(result);
}
/*[[[end:removexattr]]]*/

/*[[[head:lremovexattr,hash:0x61407f52]]]*/
/* Remove the attribute NAME from the file pointed to by PATH, not
 * following symlinks for the last pathname component.
 * Return 0 on success, -1 for errors */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.lremovexattr") int
NOTHROW_RPC(LIBCCALL libc_lremovexattr)(char const *path,
                                        char const *name)
/*[[[body:lremovexattr]]]*/
{
	ssize_t result;
	result = sys_lremovexattr(path, name);
	return libc_seterrno_syserr(result);
}
/*[[[end:lremovexattr]]]*/

/*[[[head:fremovexattr,hash:0xbcca7651]]]*/
/* Remove the attribute NAME from the file descriptor FD.
 * Return 0 on success, -1 for errors */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.fremovexattr") int
NOTHROW_RPC(LIBCCALL libc_fremovexattr)(fd_t fd,
                                        char const *name)
/*[[[body:fremovexattr]]]*/
{
	ssize_t result;
	result = sys_fremovexattr(fd, name);
	return libc_seterrno_syserr(result);
}
/*[[[end:fremovexattr]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0xd1b88ad5]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(setxattr, libc_setxattr);
DEFINE_PUBLIC_WEAK_ALIAS(lsetxattr, libc_lsetxattr);
DEFINE_PUBLIC_WEAK_ALIAS(fsetxattr, libc_fsetxattr);
DEFINE_PUBLIC_WEAK_ALIAS(getxattr, libc_getxattr);
DEFINE_PUBLIC_WEAK_ALIAS(lgetxattr, libc_lgetxattr);
DEFINE_PUBLIC_WEAK_ALIAS(fgetxattr, libc_fgetxattr);
DEFINE_PUBLIC_WEAK_ALIAS(listxattr, libc_listxattr);
DEFINE_PUBLIC_WEAK_ALIAS(llistxattr, libc_llistxattr);
DEFINE_PUBLIC_WEAK_ALIAS(flistxattr, libc_flistxattr);
DEFINE_PUBLIC_WEAK_ALIAS(removexattr, libc_removexattr);
DEFINE_PUBLIC_WEAK_ALIAS(lremovexattr, libc_lremovexattr);
DEFINE_PUBLIC_WEAK_ALIAS(fremovexattr, libc_fremovexattr);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_XATTR_C */
