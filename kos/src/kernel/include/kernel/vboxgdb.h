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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VBOXGDB_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VBOXGDB_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <hybrid/host.h>

#ifdef CONFIG_NO_VBOXGDB
#undef CONFIG_VBOXGDB
#elif (defined(CONFIG_VBOXGDB) && !(CONFIG_VBOXGDB + 0))
#undef CONFIG_VBOXGDB
#define CONFIG_NO_VBOXGDB 1
#elif defined(__i386__) || defined(__x86_64__)
/* VirtualBox can only emulate x86 machines, so there's no point
 * in trying to  support vboxgdb when  targeting anything  else! */
#define CONFIG_VBOXGDB 1
#else /* ... */
#define CONFIG_NO_VBOXGDB 1
#endif /* !... */

/* Known VBox GDB traps. */
#define VBOXGDB_TRAP_STARTUP "startup" /* Invoked during kernel startup (starts the GDB stub & sets initial breakpoints) */
#define VBOXGDB_TRAP_LIBRARY "library" /* Invoked when a driver is loaded/unloaded. */

#ifdef __CC__
DECL_BEGIN

#ifdef CONFIG_VBOXGDB

/* Trap into the vboxgdb sub-system by sending a command "%{vboxgdb:<name>}",
 * and entering the  vbox step-loop  until the vbox  debugger indicates  that
 * execution should be resumed.
 * This function returns once vboxgdb tells it to do so.
 * @param: name: The name of the trap. (one of `VBOXGDB_TRAP_*') */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL vboxgdb_trap)(char const *__restrict name);

#else /* CONFIG_VBOXGDB */
#define vboxgdb_trap(name) (void)0
#endif /* !CONFIG_VBOXGDB */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VBOXGDB_H */
