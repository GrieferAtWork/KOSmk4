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
#ifndef GUARD_LIBC_USER_SYS_SENDFILE_C
#define GUARD_LIBC_USER_SYS_SENDFILE_C 1

#include "../api.h"
#include "sys.sendfile.h"
#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:sendfile,hash:CRC-32=0xec68991c]]]*/
/* Send up to COUNT bytes from file associated with IN_FD starting at *OFFSET
 * to descriptor OUT_FD. Set *OFFSET to the IN_FD's file position following the
 * read bytes. If OFFSET is a null pointer, use the normal file position instead.
 * Return the number of written bytes, or -1 in case of error */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.fs.statfs.statfs.sendfile") ssize_t
NOTHROW_NCX(LIBCCALL libc_sendfile)(fd_t out_fd,
                                    fd_t in_fd,
                                    off_t *offset,
                                    size_t count)
/*[[[body:sendfile]]]*/
{
	ssize_t result;
	result = sys_sendfile(out_fd, in_fd, (syscall_ulong_t *)offset, count);
	return libc_seterrno_syserr(result);
}
/*[[[end:sendfile]]]*/

/*[[[head:sendfile64,hash:CRC-32=0xc3e39e4c]]]*/
/* Send up to COUNT bytes from file associated with IN_FD starting at *OFFSET
 * to descriptor OUT_FD. Set *OFFSET to the IN_FD's file position following the
 * read bytes. If OFFSET is a null pointer, use the normal file position instead.
 * Return the number of written bytes, or -1 in case of error */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_sendfile64, libc_sendfile);
#else
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.fs.statfs.statfs.sendfile64") ssize_t
NOTHROW_NCX(LIBCCALL libc_sendfile64)(fd_t out_fd,
                                      fd_t in_fd,
                                      off64_t *offset,
                                      size_t count)
/*[[[body:sendfile64]]]*/
{
	ssize_t result;
	result = sys_sendfile64(out_fd, in_fd, (uint64_t *)offset, count);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:sendfile64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x4253a57b]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(sendfile, libc_sendfile);
DEFINE_PUBLIC_WEAK_ALIAS(sendfile64, libc_sendfile64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SENDFILE_C */
