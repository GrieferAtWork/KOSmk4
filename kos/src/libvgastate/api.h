/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBVGASTATE_API_H
#define GUARD_LIBVGASTATE_API_H 1
#define LIBVM86_WANT_PROTOTYPES 1

#include <libvgastate/api.h>
/**/

#include <kos/anno.h>
#include <hybrid/compiler.h>

#define CC LIBVGASTATE_CC

#ifndef NOBLOCK
#define NOBLOCK __NOBLOCK
#endif /* !NOBLOCK */

#ifndef NOTHROW_KERNEL
#define NOTHROW_KERNEL __NOTHROW_KERNEL
#endif /* !NOTHROW_KERNEL */

#endif /* !GUARD_LIBVGASTATE_API_H */
