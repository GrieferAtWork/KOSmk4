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
#ifndef GUARD_LIBC_LIBC_SIGRETURN_H
#define GUARD_LIBC_LIBC_SIGRETURN_H 1

/* Keep this one the first */
#include "../api.h"
/**/

#ifndef __KERNEL__
#ifndef LIBC_ARCH_HAVE_LIBC_SYS_SIGRETURN
#include <kos/syscalls.h>
#ifdef __NR_ksigreturn
#define libc_sys_sigreturn sys_ksigreturn
#else /* ... */
#error "No way to implement libc_sys_sigreturn"
#endif /* !... */
#endif /* !LIBC_ARCH_HAVE_LIBC_SYS_SIGRETURN */
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_LIBC_SIGRETURN_H */
