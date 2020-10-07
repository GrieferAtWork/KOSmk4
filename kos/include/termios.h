/* HASH CRC-32:0x9011702d */
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
#ifndef _TERMIOS_H
#define _TERMIOS_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <sys/ioctl.h>
#include <bits/os/termios.h>

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#include <bits/types.h>
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

#if defined(__USE_MISC) || defined(__USE_KOS) || defined(__USE_BSD)
#include <sys/ttydefaults.h>
#endif /* __USE_MISC || __USE_KOS || __USE_BSD */

__SYSDECL_BEGIN

#ifdef __CC__

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

#ifdef __CRT_HAVE_cfgetospeed
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),speed_t,__NOTHROW_NCX,cfgetospeed,(struct termios const *__restrict __termios_p),(__termios_p))
#else /* __CRT_HAVE_cfgetospeed */
#include <libc/local/termios/cfgetospeed.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(cfgetospeed, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) speed_t __NOTHROW_NCX(__LIBCCALL cfgetospeed)(struct termios const *__restrict __termios_p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cfgetospeed))(__termios_p); })
#endif /* !__CRT_HAVE_cfgetospeed */
#ifdef __CRT_HAVE_cfgetispeed
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),speed_t,__NOTHROW_NCX,cfgetispeed,(struct termios const *__restrict __termios_p),(__termios_p))
#else /* __CRT_HAVE_cfgetispeed */
#include <libc/local/termios/cfgetispeed.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(cfgetispeed, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) speed_t __NOTHROW_NCX(__LIBCCALL cfgetispeed)(struct termios const *__restrict __termios_p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cfgetispeed))(__termios_p); })
#endif /* !__CRT_HAVE_cfgetispeed */
#ifdef __CRT_HAVE_cfsetospeed
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,cfsetospeed,(struct termios *__restrict __termios_p, speed_t __speed),(__termios_p,__speed))
#else /* __CRT_HAVE_cfsetospeed */
#include <libc/local/termios/cfsetospeed.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(cfsetospeed, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL cfsetospeed)(struct termios *__restrict __termios_p, speed_t __speed) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cfsetospeed))(__termios_p, __speed); })
#endif /* !__CRT_HAVE_cfsetospeed */
#ifdef __CRT_HAVE_cfsetispeed
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,cfsetispeed,(struct termios *__restrict __termios_p, speed_t __speed),(__termios_p,__speed))
#else /* __CRT_HAVE_cfsetispeed */
#include <libc/local/termios/cfsetispeed.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(cfsetispeed, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL cfsetispeed)(struct termios *__restrict __termios_p, speed_t __speed) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cfsetispeed))(__termios_p, __speed); })
#endif /* !__CRT_HAVE_cfsetispeed */
/* Get terminal attributes */
__CDECLARE_OPT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,tcgetattr,(__fd_t __fd, struct termios *__restrict __termios_p),(__fd,__termios_p))
/* Set terminal attributes
 * @param: optional_actions: One of `TCSANOW', `TCSADRAIN' or `TCSAFLUSH' */
__CDECLARE_OPT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,tcsetattr,(__fd_t __fd, __STDC_INT_AS_UINT_T __optional_actions, struct termios const *__restrict __termios_p),(__fd,__optional_actions,__termios_p))
__CDECLARE_OPT(,int,__NOTHROW_NCX,tcsendbreak,(__fd_t __fd, int __duration),(__fd,__duration))
__CDECLARE_OPT(,int,__NOTHROW_RPC,tcdrain,(__fd_t __fd),(__fd))
/* @param: queue_selector: One of `TCIFLUSH', `TCOFLUSH' or `TCIOFLUSH' */
__CDECLARE_OPT(,int,__NOTHROW_NCX,tcflush,(__fd_t __fd, __STDC_INT_AS_UINT_T __queue_selector),(__fd,__queue_selector))
/* @param: action: One of `TCOOFF', `TCOON', `TCIOFF', `TCION' */
__CDECLARE_OPT(,int,__NOTHROW_NCX,tcflow,(__fd_t __fd, __STDC_INT_AS_UINT_T __action),(__fd,__action))

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
__CDECLARE_OPT(,__pid_t,__NOTHROW_NCX,tcgetsid,(__fd_t __fd),(__fd))
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

#if defined(__USE_BSD)
__CDECLARE_OPT(,int,__NOTHROW_NCX,tcsetsid,(__fd_t __fd, __pid_t __pid),(__fd,__pid))
#endif /* __USE_BSD */

#ifdef __USE_MISC
#ifdef __CRT_HAVE_cfsetspeed
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,cfsetspeed,(struct termios *__restrict __termios_p, speed_t __speed),(__termios_p,__speed))
#else /* __CRT_HAVE_cfsetspeed */
#include <libc/local/termios/cfsetspeed.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(cfsetspeed, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL cfsetspeed)(struct termios *__restrict __termios_p, speed_t __speed) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cfsetspeed))(__termios_p, __speed); })
#endif /* !__CRT_HAVE_cfsetspeed */
#ifdef __CRT_HAVE_cfmakeraw
/* Set ~raw~ mode for the given `termios_p' (in/out; meaning that `termios_p' must already be initialized)
 * This entails the CANON and all control characters being disabled, as well as
 * any sort of input/output text processing no longer taking place. */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,cfmakeraw,(struct termios *__restrict __termios_p),(__termios_p))
#else /* __CRT_HAVE_cfmakeraw */
#include <libc/local/termios/cfmakeraw.h>
/* Set ~raw~ mode for the given `termios_p' (in/out; meaning that `termios_p' must already be initialized)
 * This entails the CANON and all control characters being disabled, as well as
 * any sort of input/output text processing no longer taking place. */
__NAMESPACE_LOCAL_USING_OR_IMPL(cfmakeraw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL cfmakeraw)(struct termios *__restrict __termios_p) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cfmakeraw))(__termios_p); })
#endif /* !__CRT_HAVE_cfmakeraw */
#endif /* __USE_MISC */

#if defined(__USE_KOS) || defined(__USE_BSD)
#ifdef __CRT_HAVE_cfmakesane
/* Set ~sane~ mode for the given `termios_p' (out-only; meaning that `termios_p' gets initialized by this function)
 * Sane here refers to setting all values to their defaults, as they are defined in <sys/ttydefaults.h> */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,cfmakesane,(struct termios *__restrict __termios_p),(__termios_p))
#else /* __CRT_HAVE_cfmakesane */
#include <libc/local/termios/cfmakesane.h>
/* Set ~sane~ mode for the given `termios_p' (out-only; meaning that `termios_p' gets initialized by this function)
 * Sane here refers to setting all values to their defaults, as they are defined in <sys/ttydefaults.h> */
__NAMESPACE_LOCAL_USING_OR_IMPL(cfmakesane, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL cfmakesane)(struct termios *__restrict __termios_p) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cfmakesane))(__termios_p); })
#endif /* !__CRT_HAVE_cfmakesane */
#endif /* __USE_KOS || __USE_BSD */
#endif /* __CC__ */

#ifdef __USE_MISC
#define CCEQ(val, c) ((c) == (val) && (val) != _POSIX_VDISABLE)
#endif /* __USE_MISC */

__SYSDECL_END

#endif /* !_TERMIOS_H */
