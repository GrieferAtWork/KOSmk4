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
#ifndef _PATHS_H
#define _PATHS_H 1

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

__SYSDECL_BEGIN

/*
 * Copyright (c) 1989, 1993
 * The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *    @(#)paths.h    8.1 (Berkeley) 6/2/93
 */

#ifdef __CRT_CYG
#define _PATH_DEFPATH "/bin"                 /* Default search path. */
#define _PATH_STDPATH "/bin:/usr/sbin:/sbin" /* All standard utilities path. */
#define _PATH_MAILDIR "/var/spool/mail/"
#define _PATH_VI      "/bin/vi"
#elif defined(__KOS__)
#define _PATH_DEFPATH "/bin:/usr/bin"                 /* Default search path. */
#define _PATH_STDPATH "/bin:/usr/bin:/usr/sbin:/sbin" /* All standard utilities path. */
#define _PATH_MAILDIR "/var/mail"
#define _PATH_VI      "/bin/vi"
#else /* ... */
#define _PATH_DEFPATH "/usr/bin:/bin"                 /* Default search path. */
#define _PATH_STDPATH "/usr/bin:/bin:/usr/sbin:/sbin" /* All standard utilities path. */
#define _PATH_MAILDIR "/var/mail"
#define _PATH_VI      "/usr/bin/vi"
#endif /* !... */

#define _PATH_BSHELL  "/bin/sh"
#define _PATH_CSHELL  "/bin/csh"
#define _PATH_DEVNULL "/dev/null"
#define _PATH_LASTLOG "/var/log/lastlog"
#define _PATH_MAN     "/usr/share/man"
#define _PATH_MEM     "/dev/mem"
#define _PATH_MNTTAB  "/etc/fstab"
#define _PATH_MOUNTED "/etc/mtab"
#define _PATH_SHELLS  "/etc/shells"
#define _PATH_TTY     "/dev/tty"
#define _PATH_UTMP    "/var/run/utmp"
#define _PATH_WTMP    "/var/log/wtmp"

/* Provide trailing slash, since mostly used for building pathnames. */
#define _PATH_DEV    "/dev/"
#define _PATH_TMP    "/tmp/"
#define _PATH_VARRUN "/var/run/"
#define _PATH_VARTMP "/var/tmp/"

#ifdef __USE_KOS
#define _PATH_PASSWD "/etc/passwd"
#define _PATH_GROUP  "/etc/group"
#endif /* __USE_KOS */

#ifdef __CRT_GLC
#define _PATH_CONSOLE  "/dev/console"
#define _PATH_DEVDB    "/var/run/dev.db"
#define _PATH_DRUM     "/dev/drum"
#define _PATH_GSHADOW  "/etc/gshadow"
#define _PATH_KLOG     "/proc/kmsg"
#define _PATH_KMEM     "/dev/kmem"
#define _PATH_NOLOGIN  "/etc/nologin"
#define _PATH_PRESERVE "/var/lib"
#define _PATH_RWHODIR  "/var/spool/rwho"
#define _PATH_SENDMAIL "/usr/sbin/sendmail"
#define _PATH_SHADOW   "/etc/shadow"
#define _PATH_UNIX     "/boot/vmlinux"
#define _PATH_VARDB    "/var/lib/misc/"
#if defined(__USE_PORTABLE) && \
defined(__COMPILER_HAVE_PRAGMA_DEPRECATED)
/* Mark non-portable GLibc paths as deprecated. */
#pragma deprecated(_PATH_CONSOLE)
#pragma deprecated(_PATH_DEVDB)
#pragma deprecated(_PATH_DRUM)
#pragma deprecated(_PATH_GSHADOW)
#pragma deprecated(_PATH_KLOG)
#pragma deprecated(_PATH_KMEM)
#pragma deprecated(_PATH_NOLOGIN)
#pragma deprecated(_PATH_PRESERVE)
#pragma deprecated(_PATH_RWHODIR)
#pragma deprecated(_PATH_SENDMAIL)
#pragma deprecated(_PATH_SHADOW)
#pragma deprecated(_PATH_UNIX)
#pragma deprecated(_PATH_VARDB)
#endif
#endif /* __CRT_GLC */

__SYSDECL_END

#endif /* !_PATHS_H */
