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
/* (#) Portability: Cygwin        (/newlib/libc/include/paths.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/paths.h) */
/* (#) Portability: FreeBSD       (/include/paths.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/paths.h) */
/* (#) Portability: NetBSD        (/include/paths.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/paths.h) */
/* (#) Portability: OpenBSD       (/include/paths.h) */
/* (#) Portability: diet libc     (/include/paths.h) */
/* (#) Portability: libc4/5       (/include/paths.h) */
/* (#) Portability: libc6         (/include/paths.h) */
/* (#) Portability: mintlib       (/include/paths.h) */
/* (#) Portability: musl libc     (/include/paths.h) */
/* (#) Portability: uClibc        (/include/paths.h) */
#ifndef _PATHS_H
#define _PATHS_H 1

#include <__crt.h>
#include <__stdinc.h>

/* NOTES:
 *  - _PATH_STDPATH: Standard system utility paths (for root login)
 *  - _PATH_DEFPATH: Standard system utility paths (for normal login)
 */

#ifdef __CRT_CYG
#define _PATH_DEFPATH "/bin"
#define _PATH_STDPATH "/bin:/usr/sbin:/sbin"
#define _PATH_MAILDIR "/var/spool/mail/"
#define _PATH_VI      "/bin/vi"
#elif defined(__KOS__)
#define _PATH_DEFPATH "/bin:/usr/bin"
#define _PATH_STDPATH "/bin:/usr/bin:/usr/sbin:/sbin"
#define _PATH_MAILDIR "/var/mail"
#define _PATH_MOUNTED "/proc/self/mounts"
#define _PATH_VI      "/bin/busybox"
#else /* ... */
#define _PATH_MAILDIR "/var/mail"
#define _PATH_VI      "/usr/bin/vi"
#define _PATH_MOUNTED "/etc/mtab"
#define _PATH_SHELLS  "/etc/shells"
#endif /* !... */

#ifdef __KOS__
#define _PATH_BSHELL "/bin/busybox"
#define _PATH_CSHELL "/bin/busybox"
#else /* __KOS__ */
#define _PATH_BSHELL "/bin/sh"
#define _PATH_CSHELL "/bin/csh"
#endif /* !__KOS__ */

#if defined(__KOS__) || defined(__linux__)
#define _PATH_KMEM "/dev/kmem"
#endif /* __KOS__ || __linux__ */

#ifdef __linux__
#define _PATH_UNIX     "/boot/vmlinux"
#define _PATH_DRUM     "/dev/drum"
#define _PATH_GSHADOW  "/etc/gshadow"
#define _PATH_NOLOGIN  "/etc/nologin"
#define _PATH_SHADOW   "/etc/shadow"
#define _PATH_KLOG     "/proc/kmsg"
#define _PATH_SENDMAIL "/usr/sbin/sendmail"
#define _PATH_PRESERVE "/var/lib"
#define _PATH_VARDB    "/var/lib/misc/"
#define _PATH_RWHODIR  "/var/spool/rwho"
#define _PATH_DEVDB    "/var/run/dev.db"
#endif /* __linux__ */

#define _PATH_DEV     "/dev/"
#define _PATH_CONSOLE "/dev/console"
#define _PATH_MEM     "/dev/mem"
#define _PATH_DEVNULL "/dev/null"
#define _PATH_TTY     "/dev/tty"
#define _PATH_DEVZERO "/dev/zero"

#define _PATH_PASSWD  "/etc/passwd"
#define _PATH_GROUP   "/etc/group"
#define _PATH_MNTTAB  "/etc/fstab"
#define _PATH_MAN     "/usr/share/man"
#define _PATH_LASTLOG "/var/log/lastlog"
#define _PATH_WTMP    "/var/log/wtmp"
#define _PATH_VARRUN  "/var/run/"
#define _PATH_UTMP    "/var/run/utmp"
#define _PATH_VARTMP  "/var/tmp/"

#define _PATH_TMP "/tmp/"

#define _PATH_TEXTDOMAIN "/usr/share/locale"

#ifndef _PATH_DEFPATH
#define _PATH_DEFPATH "/usr/bin:/bin"
#endif /* !_PATH_DEFPATH */

#ifndef _PATH_STDPATH
#define _PATH_STDPATH "/usr/bin:/bin:/usr/sbin:/sbin"
#endif /* !_PATH_STDPATH */

#endif /* !_PATHS_H */
