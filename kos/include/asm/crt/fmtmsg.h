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
/*!included_by <fmtmsg.h>*/
#ifndef _ASM_CRT_FMTMSG_H
#define _ASM_CRT_FMTMSG_H 1

#include <__crt.h>

/* Possible flags for `fmtmsg(3)::classification' */
#define __MM_HARD    0x001 /* Caused by hardware */
#define __MM_SOFT    0x002 /* Caused by software */
#define __MM_FIRM    0x004 /* Caused by firmware */
#define __MM_APPL    0x008 /* Detected by application */
#define __MM_UTIL    0x010 /* Detected by utility */
#define __MM_OPSYS   0x020 /* Detected by operating system */
#define __MM_RECOVER 0x040 /* Error is recoverable */
#define __MM_NRECOV  0x080 /* Error is non-recoverable */
#define __MM_PRINT   0x100 /* Print to `stderr(3)' */
#define __MM_CONSOLE 0x200 /* Print to `syslog(3)' */

/* Pre-defined values for `fmtmsg(3)::severity' */
#define __MM_NOSEV   0 /* No severity level */
#define __MM_HALT    1 /* Application will halt as a result */
#define __MM_ERROR   2 /* Non-fatal error encountered */
#define __MM_WARNING 3 /* Unusual non-error condition (== warning) */
#define __MM_INFO    4 /* General information */

/* Return values for `fmtmsg(3)' */
#define __MM_NOTOK (-1) /* Arguments are bad */
#define __MM_OK    0    /* Success */
#define __MM_NOMSG 1    /* Failed to print message to `stderr(3)' */
#define __MM_NOCON 4    /* Failed to print message to `syslog(3)' (never returned since syslog has no error-condition) */

#endif /* !_ASM_CRT_FMTMSG_H */
