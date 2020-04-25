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
#ifndef _ASM_SCHED_H
#define _ASM_SCHED_H 1

#include <__crt.h>
#include <__stdinc.h>

#if defined(__KOS__) || defined(__linux__) || defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL) || defined(__CRT_GLC)

#define __CSIGNAL              0x000000ff /* Signal mask to be sent at exit. */
#define __CLONE_VM             0x00000100 /* Set if VM shared between processes. */
#define __CLONE_FS             0x00000200 /* Set if fs info shared between processes. */
#define __CLONE_FILES          0x00000400 /* Set if open files shared between processes. */
#define __CLONE_SIGHAND        0x00000800 /* Set if signal handlers shared. */
/*      __CLONE_               0x00001000  * ... */
#define __CLONE_PTRACE         0x00002000 /* Set if tracing continues on the child. */
#define __CLONE_VFORK          0x00004000 /* Set if the parent wants the child to wake it up on mm_release. */
#define __CLONE_PARENT         0x00008000 /* Set if we want to have the same parent as the cloner. */
#define __CLONE_THREAD         0x00010000 /* Set to add to same thread group. */
#define __CLONE_NEWNS          0x00020000 /* Set to create new namespace. */
#define __CLONE_SYSVSEM        0x00040000 /* Set to shared SVID SEM_UNDO semantics. */
#define __CLONE_SETTLS         0x00080000 /* Set TLS info. */
#define __CLONE_PARENT_SETTID  0x00100000 /* Store TID in userlevel buffer before MM copy. */
#define __CLONE_CHILD_CLEARTID 0x00200000 /* Register exit futex and memory location to clear. */
#define __CLONE_DETACHED       0x00400000 /* Create clone detached. */
#define __CLONE_UNTRACED       0x00800000 /* Set if the tracing process can't force CLONE_PTRACE on this clone. */
#define __CLONE_CHILD_SETTID   0x01000000 /* Store TID in userlevel buffer in the child. */
/*      __CLONE_               0x02000000  * ... */
#define __CLONE_NEWUTS         0x04000000 /* New utsname group. */
#define __CLONE_NEWIPC         0x08000000 /* New ipcs. */
#define __CLONE_NEWUSER        0x10000000 /* New user namespace. */
#define __CLONE_NEWPID         0x20000000 /* New pid namespace. */
#define __CLONE_NEWNET         0x40000000 /* New network namespace. */
#define __CLONE_IO             0x80000000 /* Clone I/O context. */

#endif /* ... */

#endif /* !_ASM_SCHED_H */
