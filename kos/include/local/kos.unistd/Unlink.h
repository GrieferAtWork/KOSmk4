/* HASH CRC-32:0x6d4d4359 */
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
#ifndef __local_Unlink_defined
#define __local_Unlink_defined 1
#include <__crt.h>
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_UnlinkAt)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: UnlinkAt from kos.unistd */
#if !defined(__local___localdep_UnlinkAt_defined) && defined(__CRT_HAVE_UnlinkAt)
#define __local___localdep_UnlinkAt_defined 1
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CREDIRECT_VOID(__ATTR_NONNULL((2)),__THROWING,__localdep_UnlinkAt,(__fd_t __dfd, char const *__name, __atflag_t __flags),UnlinkAt,(__dfd,__name,__flags))
#endif /* !__local___localdep_UnlinkAt_defined && __CRT_HAVE_UnlinkAt */
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__LOCAL_LIBC(Unlink) __ATTR_NONNULL((1)) void
(__LIBCCALL __LIBC_LOCAL_NAME(Unlink))(char const *__file) __THROWS(...) {
	__localdep_UnlinkAt(__CRT_AT_FDCWD, __file, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_Unlink_defined
#define __local___localdep_Unlink_defined 1
#define __localdep_Unlink __LIBC_LOCAL_NAME(Unlink)
#endif /* !__local___localdep_Unlink_defined */
#else /* __CRT_AT_FDCWD && __CRT_HAVE_UnlinkAt */
#undef __local_Unlink_defined
#endif /* !__CRT_AT_FDCWD || !__CRT_HAVE_UnlinkAt */
#endif /* !__local_Unlink_defined */
