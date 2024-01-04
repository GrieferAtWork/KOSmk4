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
#ifndef _KOS_KERNEL_PRINTK_H
#define _KOS_KERNEL_PRINTK_H 1

#include <__stdinc.h>

#ifdef __KERNEL__
#include <kernel/printk.h>
#else /* __KERNEL__ */
#include <sys/syslog.h>

#define KERN_EMERG   LOG_EMERG,
#define KERN_ALERT   LOG_ALERT,
#define KERN_CRIT    LOG_CRIT,
#define KERN_ERR     LOG_ERR,
#define KERN_WARNING LOG_WARNING,
#define KERN_NOTICE  LOG_NOTICE,
#define KERN_INFO    LOG_INFO,
#define KERN_TRACE   LOG_DEBUG,
#define KERN_DEBUG   LOG_DEBUG,
#define KERN_DEFAULT LOG_DEBUG,
#define KERN_RAW     LOG_DEBUG,
#define printk       syslog
#endif /* !__KERNEL__ */

#endif /* !_KOS_KERNEL_PRINTK_H */
