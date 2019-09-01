/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_PRINTK_H
#define GUARD_KERNEL_INCLUDE_KERNEL_PRINTK_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>

DECL_BEGIN

#define KERN_EMERG   "\001" "0"
#define KERN_ALERT   "\001" "1"
#define KERN_CRIT    "\001" "2"
#define KERN_ERR     "\001" "3"
#define KERN_WARNING "\001" "4"
#define KERN_NOTICE  "\001" "5"
#define KERN_INFO    "\001" "6"
#define KERN_TRACE   "\001" "7"
#define KERN_DEBUG   "\001" "8"
#define KERN_DEFAULT "\001" "d"
#define KERN_RAW     "\001" "r"

FUNDEF NOBLOCK void (VCALL printk)(char const *__restrict format, ...);
FUNDEF NOBLOCK void (KCALL vprintk)(char const *__restrict format, __builtin_va_list args);

/* @param: level: [0..1] The print level (One of `KERN_*'). */
FUNDEF NOBLOCK ssize_t (KCALL kprinter)(void *level, char const *__restrict data, size_t datalen);


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_PRINTK_H */
