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
/* (#) Portability: Cygwin    (/newlib/libc/include/machine/types.h) */
/* (#) Portability: EMX kLIBC (/libc/include/machine/types.h) */
/* (#) Portability: Newlib    (/newlib/libc/include/machine/types.h) */
#ifndef _MACHINE_TYPES_H
#define _MACHINE_TYPES_H 1

#include <__stdinc.h>

#include <bits/os/flock.h>
#include <bits/os/timespec.h>
#include <bits/types.h>
#include <sys/sysmacros.h>

__DECL_BEGIN

#ifdef __CC__

#ifndef __timespec_t_defined
#define __timespec_t_defined
typedef struct timespec timespec_t;
#endif /* !__timespec_t_defined */

#ifndef __timestruc_t_defined
#define __timestruc_t_defined
typedef struct timespec timestruc_t;
#endif /* !__timestruc_t_defined */

#ifndef __loff_t_defined
#define __loff_t_defined
typedef __loff_t loff_t;
#endif /* !__loff_t_defined */

#ifndef __vm_offset_t_defined
#define __vm_offset_t_defined
typedef __ULONGPTR_TYPE__ vm_offset_t;
#endif /* !__vm_offset_t_defined */

#ifndef __vm_size_t_defined
#define __vm_size_t_defined
typedef __ULONGPTR_TYPE__ vm_size_t;
#endif /* !__vm_size_t_defined */

#ifndef __vm_object_t_defined
#define __vm_object_t_defined
typedef void *vm_object_t;
#endif /* !__vm_object_t_defined */

#ifndef __addr_t_defined
#define __addr_t_defined
typedef char *addr_t;
#endif /* !__addr_t_defined */

#endif /* __CC__ */

__DECL_END

#endif /* !_MACHINE_TYPES_H */
