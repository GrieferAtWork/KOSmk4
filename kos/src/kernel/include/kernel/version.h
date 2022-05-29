/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VERSION_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VERSION_H 1

/* IMPORTANT: This header must not be removed or renamed!
 *
 * It was already there in earlier revisions of KOS,  and
 * could thus be used to write kernel drivers that can be
 * made portable to both KOSmk4 and KOSmk3 (and  possibly
 * even earlier)
 */

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <kernel/uname.h>

#define KERNEL_VERSION(maj, min, pat) ((maj) << 20 | (min) << 10 | (pat))

/* Expanded kernel version numbers. */
#define KOS_VERSION_MAJOR 4 /* KOS Mk4 */
#define KOS_VERSION_MINOR 0
#define KOS_VERSION_PATCH 0

#define KOS_VERSION_CODE KERNEL_VERSION(KOS_VERSION_MAJOR, KOS_VERSION_MINOR, KOS_VERSION_PATCH)
#define KOS_VERSION_NAME "yakal"

#ifdef __CC__
DECL_BEGIN

/* Effective kernel version.
 * Usually the same as `KOS_VERSION_CODE', but can be used  by
 * modules  to  detect version  differences between  what they
 * were compiled for and what they are actually running under. */
DATDEF u32 const kernel_version;

#define ushare_utsname kernel_uname /* Mk3-name */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VERSION_H */
