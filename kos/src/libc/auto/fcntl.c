/* HASH CRC-32:0xd5d75ac1 */
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
#ifndef GUARD_LIBC_AUTO_FCNTL_C
#define GUARD_LIBC_AUTO_FCNTL_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/fcntl.h"
#include "../user/sys.ioctl.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/os/file-ioctls.h>
/* >> directio(3)
 * Enable or disable optional direct-I/O for  `fd'. Optional direct I/O behaves  the
 * same as mandatory direct I/O (s.a. `O_DIRECT'), but those cases where the  buffer
 * or file position/length provided in a call to `read(2)' or `write(2)' don't match
 * the requirements imposed by the  backing hardware (s.a. `FILE_IOC_BLKSHIFT')  are
 * handled  not by throwing an `E_INVALID_ARGUMENT_CONTEXT_O_DIRECT_BAD*' exception,
 * but by falling back to doing non-direct I/O (as if `O_DIRECT') hasn't been set.
 *
 * Note that when optional direct-I/O is enabled, the O_DIRECT bit will also be set
 * for  the  given  `fd'  (in   addition  to  the  internal  `IO_OPTDIRECT'   bit).
 *
 * PORTABILITY WARNING: On OpenSolaris, this optional direct  I/O isn't used for file  ranges
 *                      of the given `fd' that have been mmap'd. This is NOT the case on KOS,
 *                      where direct I/O is always use if possible.
 *
 * @param: fd:   The file for which direct-I/O should be enabled/disabled
 * @param: mode: One of `DIRECTIO_*' from `<sys/fcntl.h>'
 * @return:  0: Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.solaris.io") int
NOTHROW_NCX(LIBCCALL libc_directio)(fd_t fd,
                                    int mode) {
	return libc_ioctl(fd, __FIODIRECTIO, mode);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(directio, libc_directio);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_FCNTL_C */
