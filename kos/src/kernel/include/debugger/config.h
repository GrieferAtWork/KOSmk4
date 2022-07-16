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
#ifndef GUARD_KERNEL_INCLUDE_DEBUGGER_CONFIG_H
#define GUARD_KERNEL_INCLUDE_DEBUGGER_CONFIG_H 1

#include <kernel/compiler.h>

/*[[[config CONFIG_HAVE_KERNEL_DEBUGGER = true
 * Enable the builtin kernel debugger:
 *  - Activated upon kernel panic
 *  - Activated when pressing F12 4 times in a row
 *  - Activated when a user-space program faults (configurable)
 * ]]]*/
#ifdef CONFIG_NO_KERNEL_DEBUGGER
#undef CONFIG_HAVE_KERNEL_DEBUGGER
#elif !defined(CONFIG_HAVE_KERNEL_DEBUGGER)
#define CONFIG_HAVE_KERNEL_DEBUGGER
#elif (-CONFIG_HAVE_KERNEL_DEBUGGER - 1) == -1
#undef CONFIG_HAVE_KERNEL_DEBUGGER
#define CONFIG_NO_KERNEL_DEBUGGER
#endif /* ... */
/*[[[end]]]*/

#endif /* !GUARD_KERNEL_INCLUDE_DEBUGGER_CONFIG_H */
