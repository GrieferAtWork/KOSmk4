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
#ifndef GUARD_LIBDL_ARCH_I386_UCALL_H
#define GUARD_LIBDL_ARCH_I386_UCALL_H 1

#include "../../api.h"
/**/

#include <hybrid/host.h>

#ifdef __x86_64__
DECL_BEGIN

/* Need special call  wrappers on x86_64  since libdl is  compiled
 * with  "-mpreferred-stack-boundary=3"  (8-byte  aligned),  which
 * may break externally defined function (init / resolve handlers)
 * which probably expect the ABI mandated 16 bytes. */
typedef void *(ATTR_SYSVABI *libdl_ucall0_amd64_t)(void);
typedef void *(ATTR_SYSVABI *libdl_ucall3_amd64_t)(void *, void *, void *);
INTDEF void *ATTR_SYSVABI libdl_ucall0_amd64(libdl_ucall0_amd64_t func);
INTDEF void *ATTR_SYSVABI libdl_ucall3_amd64(void *a, void *b, void *c, libdl_ucall3_amd64_t func);

#define libdl_ucall0(ptr)          libdl_ucall0_amd64((libdl_ucall0_amd64_t)(void *)(ptr))
#define libdl_ucall3(ptr, a, b, c) libdl_ucall3_amd64(a, b, c, (libdl_ucall3_amd64_t)(void *)(ptr))

DECL_END
#endif /* __x86_64__ */

#endif /* !GUARD_LIBDL_ARCH_I386_UCALL_H */
