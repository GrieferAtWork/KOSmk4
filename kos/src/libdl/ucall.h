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
#ifndef GUARD_LIBDL_UCALL_H
#define GUARD_LIBDL_UCALL_H 1

#include "api.h"
/**/

#include <hybrid/host.h>

#if defined(__x86_64__) || defined(__i386__)
#include "arch/i386/ucall.h"
#elif defined(__arm__)
#include "arch/arm/ucall.h"
#endif /* ... */

#ifndef libdl_ucall0
#define libdl_ucall0(ptr) ((*(void *(LIBCCALL *)(void))(void *)(ptr))())
#endif /* !libdl_ucall0 */
#ifndef libdl_ucall3
#define libdl_ucall3(ptr, a, b, c) ((*(void *(LIBCCALL *)(void *, void *, void *))(void *)(ptr))(a, b, c))
#endif /* !libdl_ucall3 */


#endif /* !GUARD_LIBDL_UCALL_H */
