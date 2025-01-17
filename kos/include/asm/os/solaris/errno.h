/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_OS_SOLARIS_ERRNO_H
#define _ASM_OS_SOLARIS_ERRNO_H 1

#include <__stdinc.h>

/************************************************************************/
/* Solaris                                                              */
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
#define __EAGAIN          11
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
#define __ENOMSG          35
#define __EIDRM           36
#define __ECHRNG          37
#define __EL2NSYNC        38
#define __EL3HLT          39
#define __EL3RST          40
#define __ELNRNG          41
#define __EUNATCH         42
#define __ENOCSI          43
#define __EL2HLT          44
#define __EDEADLK         45
#define __ENOLCK          46
#define __ECANCELED       47
#define __ENOTSUP         48
#define __EDQUOT          49
#define __EBADE           50
#define __EBADR           51
#define __EXFULL          52
#define __ENOANO          53
#define __EBADRQC         54
#define __EBADSLT         55
#define __EDEADLOCK       56
#define __EBFONT          57
#define __EOWNERDEAD      58
#define __ENOTRECOVERABLE 59
#define __ENOSTR          60
#define __ENODATA         61
#define __ETIME           62
#define __ENOSR           63
#define __ENONET          64
#define __ENOPKG          65
#define __EREMOTE         66
#define __ENOLINK         67
#define __EADV            68
#define __ESRMNT          69
#define __ECOMM           70
#define __EPROTO          71
#define __ELOCKUNMAPPED   72
#define __ENOTACTIVE      73
#define __EMULTIHOP       74
#define __EBADMSG         77
#define __ENAMETOOLONG    78
#define __EOVERFLOW       79
#define __ENOTUNIQ        80
#define __EBADFD          81
#define __EREMCHG         82
#define __ELIBACC         83
#define __ELIBBAD         84
#define __ELIBSCN         85
#define __ELIBMAX         86
#define __ELIBEXEC        87
#define __EILSEQ          88
#define __ENOSYS          89
#define __ELOOP           90
#define __ERESTART        91
#define __ESTRPIPE        92
#define __ENOTEMPTY       93
#define __EUSERS          94
#define __ENOTSOCK        95
#define __EDESTADDRREQ    96
#define __EMSGSIZE        97
#define __EPROTOTYPE      98
#define __ENOPROTOOPT     99
#define __EPROTONOSUPPORT 120
#define __ESOCKTNOSUPPORT 121
#define __EOPNOTSUPP      122
#define __EPFNOSUPPORT    123
#define __EAFNOSUPPORT    124
#define __EADDRINUSE      125
#define __EADDRNOTAVAIL   126
#define __ENETDOWN        127
#define __ENETUNREACH     128
#define __ENETRESET       129
#define __ECONNABORTED    130
#define __ECONNRESET      131
#define __ENOBUFS         132
#define __EISCONN         133
#define __ENOTCONN        134
#define __ESHUTDOWN       143
#define __ETOOMANYREFS    144
#define __ETIMEDOUT       145
#define __ECONNREFUSED    146
#define __EHOSTDOWN       147
#define __EHOSTUNREACH    148
#define __EALREADY        149
#define __EINPROGRESS     150
#define __ESTALE          151
/*[[[end]]]*/

#define __EMAX   151 /* Max errno */
#define __ECOUNT 152 /* Max errno + 1 */

#endif /* !_ASM_OS_SOLARIS_ERRNO_H */
