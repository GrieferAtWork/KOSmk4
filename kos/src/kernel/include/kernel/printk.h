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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_PRINTK_H
#define GUARD_KERNEL_INCLUDE_KERNEL_PRINTK_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>

/* Level prefix strings for use with `printk()' */
#define KERN_EMERG   "\001" "0" /* s.a. `SYSLOG_LEVEL_EMERG' */
#define KERN_ALERT   "\001" "1" /* s.a. `SYSLOG_LEVEL_ALERT' */
#define KERN_CRIT    "\001" "2" /* s.a. `SYSLOG_LEVEL_CRIT' */
#define KERN_ERR     "\001" "3" /* s.a. `SYSLOG_LEVEL_ERR' */
#define KERN_WARNING "\001" "4" /* s.a. `SYSLOG_LEVEL_WARNING' */
#define KERN_NOTICE  "\001" "5" /* s.a. `SYSLOG_LEVEL_NOTICE' */
#define KERN_INFO    "\001" "6" /* s.a. `SYSLOG_LEVEL_INFO' */
#define KERN_TRACE   "\001" "7" /* s.a. `SYSLOG_LEVEL_TRACE' */
#define KERN_DEBUG   "\001" "8" /* s.a. `SYSLOG_LEVEL_DEBUG' */
#define KERN_DEFAULT "\001" "9" /* s.a. `SYSLOG_LEVEL_DEFAULT' */
#define KERN_RAW     "\001" ":" /* s.a. `SYSLOG_LEVEL_RAW' */

#ifdef __CC__
DECL_BEGIN

/* Print formatted system log message:
 * >> printk(KERN_DEBUG "Hello %s!\n", "World");
 * Same as:
 * >> format_printf(&syslog_printer, SYSLOG_LEVEL_DEBUG, "Hello %s!\n", "World");
 * HINT:  These   functions   can   safely  be   called   from   _any_   context! */
FUNDEF NOBLOCK ssize_t (VCALL printk)(char const *__restrict format, ...);
FUNDEF NOBLOCK ssize_t (KCALL vprintk)(char const *__restrict format, __builtin_va_list args);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_PRINTK_H */
