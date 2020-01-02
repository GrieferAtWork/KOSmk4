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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _COMPAT_SIGNAL_H
#define _COMPAT_SIGNAL_H 1

#include <__stdinc.h>
#include <compat/config.h>
#ifdef __ARCH_HAVE_COMPAT
#include <features.h>
#include <compat/bits/types.h>
#include <compat/bits/sigset.h>
#include <compat/bits/sigaction-struct.h>

#ifdef __USE_POSIX199309
#include <compat/bits/timespec.h>
#endif /* __USE_POSIX199309 */

#if defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS)
#include <compat/bits/siginfo-struct.h>
#endif /* __USE_POSIX199309 || __USE_XOPEN_EXTENDED || __USE_KOS */

#ifdef __CC__
__DECL_BEGIN

#ifdef __USE_POSIX
#ifndef __compat_sigset_t_defined
#define __compat_sigset_t_defined 1
typedef __compat_sigset_t compat_sigset_t;
#endif /* !__compat_sigset_t_defined */
#endif /* __USE_POSIX */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __compat_pid_t_defined
#define __compat_pid_t_defined 1
typedef __compat_pid_t compat_pid_t;
#endif /* !__compat_pid_t_defined */
#ifndef __compat_uid_t_defined
#define __compat_uid_t_defined 1
typedef __compat_uid_t compat_uid_t;
#endif /* !__compat_uid_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifdef __USE_GNU
#ifndef __compat_sighandler_t_defined
#define __compat_sighandler_t_defined 1
typedef __compat_sighandler_t compat_sighandler_t;
#endif /* !__compat_sighandler_t_defined */
#endif /* __USE_GNU */

#ifdef __USE_MISC
typedef __compat_sighandler_t compat_sig_t;
#endif /* __USE_MISC */

#ifndef __compat_size_t_defined
#define __compat_size_t_defined 1
typedef __compat_size_t compat_size_t;
#endif /* !__compat_size_t_defined */


__DECL_END
#endif /* __CC__ */
#endif /* __ARCH_HAVE_COMPAT */

#endif /* !_COMPAT_SIGNAL_H */
