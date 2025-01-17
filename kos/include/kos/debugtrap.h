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
#ifndef _KOS_DEBUGTRAP_H
#define _KOS_DEBUGTRAP_H 1

#include <__stdinc.h>

#include <kos/bits/debugtrap.h>

/* NOTE: Use of trap reasons require special permissions, with the exception of:
 *  -  DEBUGTRAP_REASON_NONE
 *  -  DEBUGTRAP_REASON_LIBRARY
 *  -  DEBUGTRAP_REASON_WATCHW
 *  -  DEBUGTRAP_REASON_WATCHR
 *  -  DEBUGTRAP_REASON_WATCHRW
 *  -  DEBUGTRAP_REASON_MESSAGE */
#define DEBUGTRAP_REASON_NONE      0x0000 /* No special reason */
#define DEBUGTRAP_REASON_WATCHW    0x0001 /* [dtr_ptrarg = (void *)watch_addr] write watchpoint */
#define DEBUGTRAP_REASON_WATCHR    0x0002 /* [dtr_ptrarg = (void *)watch_addr] read watchpoint */
#define DEBUGTRAP_REASON_WATCHRW   0x0003 /* [dtr_ptrarg = (void *)watch_addr] read/write watchpoint */
#define DEBUGTRAP_REASON_SC_ENTRY  0x0004 /* [dtr_intarg = sysno] System call entry */
#define DEBUGTRAP_REASON_SC_EXIT   0x0005 /* [dtr_intarg = sysno] System call exit */
#define DEBUGTRAP_REASON_LIBRARY   0x0006 /* Set of loaded libraries has changed. */
#define DEBUGTRAP_REASON_FORK      0x0007 /* [USER(dtr_intarg = (pid_t)CHILD)]
                                           * [KERNEL(dtr_ptrarg = (struct task *)CHILD)]
                                           * New process created  (invoked by  the parent  process,
                                           * with the child already available, but not yet started) */
#define DEBUGTRAP_REASON_VFORK     0x0008 /* [USER(dtr_intarg = (pid_t)CHILD)]
                                           * [KERNEL(dtr_ptrarg = (struct task *)CHILD)]
                                           * Same as `DEBUGTRAP_REASON_FORK' */
#define DEBUGTRAP_REASON_VFORKDONE 0x0009 /* A vfork() child process has executed exec() or exit() */
#define DEBUGTRAP_REASON_EXEC      0x000a /* [dtr_strarg = exec_path] Executing a new program. */
#define DEBUGTRAP_REASON_CLONE     0x000b /* New thread created (invoked in by the child thread itself) */
#define DEBUGTRAP_REASON_TEXITED   0x000c /* [USER(dtr_intarg = (pid_t)thread_tid)]
                                           * [KERNEL(dtr_ptrarg = (struct task *)thread)]
                                           * [dtr_signo = (int)$?] A thread has exited */
#define DEBUGTRAP_REASON_PEXITED   0x000d /* [USER(dtr_intarg = (pid_t)proc_pid)]
                                           * [KERNEL(dtr_ptrarg = (struct task *)some_thread_of_process)]
                                           * [dtr_signo = (union wait)status] A process has exited */
#define DEBUGTRAP_REASON_SWBREAK   0x000e /* Software breakpoint */
#define DEBUGTRAP_REASON_HWBREAK   0x000f /* Hardware breakpoint */
#define DEBUGTRAP_REASON_MESSAGE   0x0010 /* [dtr_strarg = message, dtr_signo = length]
                                           * Output a human-readable message to the debugger.
                                           * NOTE: This command is special, in that (on output), it will
                                           *       store the number of characters written in `dtr_signo' */
#define DEBUGTRAP_REASON_MAX DEBUGTRAP_REASON_MESSAGE

#endif /* !_KOS_DEBUGTRAP_H */
