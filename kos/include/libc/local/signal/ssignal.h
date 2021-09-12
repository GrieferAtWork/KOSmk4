/* HASH CRC-32:0x6cdf244f */
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
#ifndef __local_ssignal_defined
#define __local_ssignal_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_bsd_signal
#include <bits/types.h>
#include <bits/os/sigaction.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bsd_signal_defined
#define __local___localdep_bsd_signal_defined 1
__CREDIRECT(,__sighandler_t,__NOTHROW_NCX,__localdep_bsd_signal,(__signo_t __signo, __sighandler_t __handler),bsd_signal,(__signo,__handler))
#endif /* !__local___localdep_bsd_signal_defined */
__LOCAL_LIBC(ssignal) __sighandler_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ssignal))(__signo_t __signo, __sighandler_t __handler) {
	return (__NAMESPACE_LOCAL_SYM __localdep_bsd_signal)(__signo, __handler);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ssignal_defined
#define __local___localdep_ssignal_defined 1
#define __localdep_ssignal __LIBC_LOCAL_NAME(ssignal)
#endif /* !__local___localdep_ssignal_defined */
#else /* __CRT_HAVE_bsd_signal */
#undef __local_ssignal_defined
#endif /* !__CRT_HAVE_bsd_signal */
#endif /* !__local_ssignal_defined */
