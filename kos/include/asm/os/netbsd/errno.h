/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_OS_NETBSD_ERRNO_H
#define _ASM_OS_NETBSD_ERRNO_H 1

#include <__stdinc.h>

/************************************************************************/
/* NetBSD                                                               */
/************************************************************************/

/*[[[begin]]]*/
#define __EPERM           1
#define __ENOENT          2
#define __ESRCH           3
#define __EINTR           4
#define __EIO             5
#define __ENXIO           6
#define __E2BIG           7
#define __ENOEXEC         8
#define __EBADF           9
#define __ECHILD          10
#define __EDEADLK         11
#define __ENOMEM          12
#define __EACCES          13
#define __EFAULT          14
#define __ENOTBLK         15
#define __EBUSY           16
#define __EEXIST          17
#define __EXDEV           18
#define __ENODEV          19
#define __ENOTDIR         20
#define __EISDIR          21
#define __EINVAL          22
#define __ENFILE          23
#define __EMFILE          24
#define __ENOTTY          25
#define __ETXTBSY         26
#define __EFBIG           27
#define __ENOSPC          28
#define __ESPIPE          29
#define __EROFS           30
#define __EMLINK          31
#define __EPIPE           32
#define __EDOM            33
#define __ERANGE          34
#define __EAGAIN          35
#define __EINPROGRESS     36
#define __EALREADY        37
#define __ENOTSOCK        38
#define __EDESTADDRREQ    39
#define __EMSGSIZE        40
#define __EPROTOTYPE      41
#define __ENOPROTOOPT     42
#define __EPROTONOSUPPORT 43
#define __ESOCKTNOSUPPORT 44
#define __EOPNOTSUPP      45
#define __EPFNOSUPPORT    46
#define __EAFNOSUPPORT    47
#define __EADDRINUSE      48
#define __EADDRNOTAVAIL   49
#define __ENETDOWN        50
#define __ENETUNREACH     51
#define __ENETRESET       52
#define __ECONNABORTED    53
#define __ECONNRESET      54
#define __ENOBUFS         55
#define __EISCONN         56
#define __ENOTCONN        57
#define __ESHUTDOWN       58
#define __ETOOMANYREFS    59
#define __ETIMEDOUT       60
#define __ECONNREFUSED    61
#define __ELOOP           62
#define __ENAMETOOLONG    63
#define __EHOSTDOWN       64
#define __EHOSTUNREACH    65
#define __ENOTEMPTY       66
#define __EPROCLIM        67
#define __EUSERS          68
#define __EDQUOT          69
#define __ESTALE          70
#define __EREMOTE         71
#define __EBADRPC         72
#define __ERPCMISMATCH    73
#define __EPROGUNAVAIL    74
#define __EPROGMISMATCH   75
#define __EPROCUNAVAIL    76
#define __ENOLCK          77
#define __ENOSYS          78
#define __EFTYPE          79
#define __EAUTH           80
#define __ENEEDAUTH       81
#define __EIDRM           82
#define __ENOMSG          83
#define __EOVERFLOW       84
#define __EILSEQ          85
#define __ENOTSUP         86
#define __ECANCELED       87
#define __EBADMSG         88
#define __ENODATA         89
#define __ENOSR           90
#define __ENOSTR          91
#define __ETIME           92
#define __ENOATTR         93
#define __EMULTIHOP       94
#define __ENOLINK         95
#define __EPROTO          96
/*[[[end]]]*/

#define __EMAX   96 /* Max errno */
#define __ECOUNT 97 /* Max errno + 1 */

#endif /* !_ASM_OS_NETBSD_ERRNO_H */
