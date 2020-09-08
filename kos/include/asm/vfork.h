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
#ifndef _ASM_VFORK_H
#define _ASM_VFORK_H 1

#include <__stdinc.h>

/* 
 * #define __ARCH_HAVE_VFORK_SHARED_VM
 *
 * >> Defined when the system implements the vfork(2) system call such
 *    that it isn't a shallow alias for fork(2), but rather executes
 *    the child process within the same VM as the parent process, only
 *    that the parent will not resume execution before the child exits,
 *    or invokes one the exec(2) system calls.
 *
 * >> Knowing this at compile-time allows for some trickery where the
 *    child process will be able to write back extended exec status
 *    information (such as the exec-errno upon failure) back to main
 *    memory, such that once `vfork(2)' returns to the parent process,
 *    that parent can assume that (among everything else that is memory),
 *    its `errno' was shared with the child process, such that (assuming
 *    that the error was caused by exec(2)->errno=ENOENT), the vfork(2)
 *    system call will (seemingly) return with `errno=ENOENT'
 *
 * -> Knowing this, it becomes significantly easier to implement error
 *    propagation as the result of a failed exec() in situations such as
 *    system(3) or the spawn(3) family of functions (both POSIX and DOS)
 *
 */


#if defined(__linux__)
#define __ARCH_HAVE_SHARED_VM_VFORK 1
#elif defined(__KOS__)
//#define __ARCH_HAVE_SHARED_VM_VFORK 1 /* XXX: Implement vfork() proper on KOS */
#endif /* ... */

#endif /* !_ASM_VFORK_H */
