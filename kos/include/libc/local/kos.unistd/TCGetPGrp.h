/* HASH CRC-32:0x3c8598e0 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_TCGetPGrp_defined
#define __local_TCGetPGrp_defined
#include <__crt.h>
#include <asm/os/tty.h>
#if defined(__CRT_HAVE_Ioctl) && defined(__TIOCGPGRP)
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_Ioctl_defined
#define __local___localdep_Ioctl_defined
__CVREDIRECT(,__SSIZE_TYPE__,__THROWING,__localdep_Ioctl,(__fd_t __fd, unsigned long int __request),Ioctl,(__fd,__request),__request,1,(void *))
#endif /* !__local___localdep_Ioctl_defined */
__LOCAL_LIBC(TCGetPGrp) __ATTR_WUNUSED __pid_t
(__LIBCCALL __LIBC_LOCAL_NAME(TCGetPGrp))(__fd_t __fd) __THROWS(...) {
	__pid_t __result;
	(__NAMESPACE_LOCAL_SYM __localdep_Ioctl)(__fd, __TIOCGPGRP, &__result);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_TCGetPGrp_defined
#define __local___localdep_TCGetPGrp_defined
#define __localdep_TCGetPGrp __LIBC_LOCAL_NAME(TCGetPGrp)
#endif /* !__local___localdep_TCGetPGrp_defined */
#else /* __CRT_HAVE_Ioctl && __TIOCGPGRP */
#undef __local_TCGetPGrp_defined
#endif /* !__CRT_HAVE_Ioctl || !__TIOCGPGRP */
#endif /* !__local_TCGetPGrp_defined */
