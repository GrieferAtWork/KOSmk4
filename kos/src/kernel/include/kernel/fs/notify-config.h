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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_NOTIFY_CONFIG_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_NOTIFY_CONFIG_H 1

#include <kernel/compiler.h>

/*[[[config CONFIG_HAVE_KERNEL_FS_NOTIFY = true]]]*/
#ifdef CONFIG_NO_KERNEL_FS_NOTIFY
#undef CONFIG_HAVE_KERNEL_FS_NOTIFY
#elif !defined(CONFIG_HAVE_KERNEL_FS_NOTIFY)
#define CONFIG_HAVE_KERNEL_FS_NOTIFY
#elif (-CONFIG_HAVE_KERNEL_FS_NOTIFY - 1) == -1
#undef CONFIG_HAVE_KERNEL_FS_NOTIFY
#define CONFIG_NO_KERNEL_FS_NOTIFY
#endif /* ... */
/*[[[end]]]*/

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_NOTIFY_CONFIG_H */
