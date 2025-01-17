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
#ifndef _ASM_OS_KOS_SYSLOG_H
#define _ASM_OS_KOS_SYSLOG_H 1

#include <__stdinc.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

#define __LOG_EMERG   0    /* system is unusable */
#define __LOG_ALERT   1    /* action must be taken immediately */
#define __LOG_CRIT    2    /* critical conditions */
#define __LOG_ERR     3    /* error conditions */
#define __LOG_WARNING 4    /* warning conditions */
#define __LOG_NOTICE  5    /* normal but significant condition */
#define __LOG_INFO    6    /* informational */
#define __LOG_DEBUG   7    /* debug-level messages */
#define __LOG_PRIMASK 0x07 /* mask to extract priority part (internal) */

#endif /* !_ASM_OS_KOS_SYSLOG_H */
