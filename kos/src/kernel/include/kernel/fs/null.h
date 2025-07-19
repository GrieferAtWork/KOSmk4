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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_NULL_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_NULL_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#ifdef __CC__
DECL_BEGIN

/* Device files for special devices from /dev/ */
struct device;

DATDEF struct device dev_mem;     /* /dev/mem     (aka. `mfile_phys') */
DATDEF struct device dev_kmem;    /* /dev/kmem */
DATDEF struct device dev_null;    /* /dev/null */
DATDEF struct device dev_port;    /* /dev/port */
DATDEF struct device dev_zero;    /* /dev/zero    (aka. `mfile_zero') */
DATDEF struct device dev_full;    /* /dev/full */
DATDEF struct device dev_random;  /* /dev/random */
DATDEF struct device dev_urandom; /* /dev/urandom */
DATDEF struct device dev_kmsg;    /* /dev/kmsg */
DATDEF struct device dev_void;    /* /dev/void    (KOS-specific: writes are no-ops, reads return undefined data) */
DATDEF struct device dev_tty;     /* /dev/tty */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_NULL_H */
