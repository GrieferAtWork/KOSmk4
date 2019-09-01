/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_DEBUGTRAP_H
#define _KOS_DEBUGTRAP_H 1

/* Helper structures for triggering debug events. */

#include <__crt.h>
#include <__stdinc.h>

#include <bits/types.h>
#include <kos/bits/debugtrap.h> /* struct debug_trap_register */

__SYSDECL_BEGIN

#ifndef DEBUG_TRAP_REGISTER_MAXSIZE
#define DEBUG_TRAP_REGISTER_MAXSIZE 512 /* Max total size of the trap register data string. */
#endif /* !DEBUG_TRAP_REGISTER_MAXSIZE */

/* From: https://sourceware.org/gdb/onlinedocs/gdb/Stop-Reply-Packets.html#Stop-Reply-Packets
 * Registers are written as `NAME:VALUE;NAME:VALUE;...' */
#define DEBUG_TRAP_REGISTER_WATCH          "watch"          /* Value: "DATA_ADDRESS_HEX"  (write watchpoint) */
#define DEBUG_TRAP_REGISTER_RWATCH         "rwatch"         /* Value: "DATA_ADDRESS_HEX"  (read watchpoint) */
#define DEBUG_TRAP_REGISTER_AWATCH         "awatch"         /* Value: "DATA_ADDRESS_HEX"  (read/write watchpoint) */
#define DEBUG_TRAP_REGISTER_SYSCALL_ENTRY  "syscall_entry"  /* Value: "SYSCALL_HEX"  (Trigger when entering a system call) */
#define DEBUG_TRAP_REGISTER_SYSCALL_RETURN "syscall_return" /* Value: "SYSCALL_HEX"  (Trigger when leaving a system call) */
#define DEBUG_TRAP_REGISTER_LIBRARY        "library"        /* Value: ""  (Trigger when loading/unloading libraries) */
#define DEBUG_TRAP_REGISTER_SWBREAK        "swbreak"        /* Value: ""  (Trigger when hitting a software breakpoint) */
#define DEBUG_TRAP_REGISTER_HWBREAK        "hwbreak"        /* Value: ""  (Trigger when hitting a hardware breakpoint) */
#define DEBUG_TRAP_REGISTER_FORK           "fork"           /* Value: "THREAD_ID_OF_NEW_PROCESS"  (Trigger after fork() or clone()) */
#define DEBUG_TRAP_REGISTER_VFORK          "vfork"          /* Value: "THREAD_ID_OF_NEW_PROCESS"  (Trigger after vfork() or clone(CLONE_VFORK)) */
#define DEBUG_TRAP_REGISTER_VFORKDONE      "vforkdone"      /* Value: ""  (Trigger when a vfork client calls exec() or exit(), thus unsharing the original process's address space) */
#define DEBUG_TRAP_REGISTER_EXEC           "exec"           /* Value: "FULL_PATH_OF_EXEC_FILE_HEX"  (Trigger when exec() is called) */
#define DEBUG_TRAP_REGISTER_CREATE         "create"         /* Value: ""  (Trigger when creating a new thread (using the initial context of the new thread)) */

__SYSDECL_END

#endif /* !_KOS_DEBUGTRAP_H */
