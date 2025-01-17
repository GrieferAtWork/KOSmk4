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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_COMM_H
#define GUARD_KERNEL_INCLUDE_SCHED_COMM_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/pertask.h>

/*[[[config CONFIG_HAVE_KERNEL_TASK_COMM = true]]]*/
#ifdef CONFIG_NO_KERNEL_TASK_COMM
#undef CONFIG_HAVE_KERNEL_TASK_COMM
#elif !defined(CONFIG_HAVE_KERNEL_TASK_COMM)
#define CONFIG_HAVE_KERNEL_TASK_COMM
#elif (-CONFIG_HAVE_KERNEL_TASK_COMM - 1) == -1
#undef CONFIG_HAVE_KERNEL_TASK_COMM
#define CONFIG_NO_KERNEL_TASK_COMM
#endif /* ... */
/*[[[end]]]*/

/* The max length of the task command name (including the trailing NUL) */
#ifndef TASK_COMM_LEN
#include <linux/prctl.h> /* __TASK_COMM_LEN */
#ifndef TASK_COMM_LEN
#ifndef __TASK_COMM_LEN
#error "This should have been defined in `<linux/prctl.h>'"
#endif /* !__TASK_COMM_LEN */
#define TASK_COMM_LEN __TASK_COMM_LEN
#endif /* !TASK_COMM_LEN */
#endif /* !TASK_COMM_LEN */

#ifdef __CC__
DECL_BEGIN

#ifdef CONFIG_HAVE_KERNEL_TASK_COMM

/* [lock(PRIVATE(THIS_TASK))]
 * Task command name.
 * - Set to the basename() of the executable during exec()
 * - Inherited during clone()
 * - Read/write using /proc/[pid]/comm
 * - Guarantied to be NUL-terminated */
DATDEF ATTR_PERTASK char this_comm[TASK_COMM_LEN];

/* Return a pointer to the calling thread's command name.
 *
 * A thread's command name may only change during `task_serve()',
 * or while in user-space. -- iow: the pointed-to string  remains
 * valid until  you do  something that  blocks, and  the  pointer
 * itself is thread-local and doesn't change, even when the  name
 * is altered (only the pointed-to string changes) */
#define task_getcomm() ((char const *)PERTASK(this_comm))

/* Get the command name of an arbitrary thread */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL task_getcomm_of)(struct task const *__restrict self,
                               char buf[TASK_COMM_LEN]);

/* Set the command name of an arbitrary thread
 * NOTES:
 *  - `name' must be NUL-terminated and not longer than `TASK_COMM_LEN'!
 *    When `name[TASK_COMM_LEN-1]' isn't NUL,  it will be replaced  with
 *    that character in `this_comm'
 *  - `name' must not contain any 0xff bytes. If any byte with that value
 *    is encountered, it will be replaced by `0x00'
 * @return: true:  Success
 * @return: false: Thread has already exited */
FUNDEF BLOCKING NONNULL((1, 2)) __BOOL FCALL
task_setcomm_of(struct task *__restrict self, char const *__restrict name)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_INTERRUPT_USER_RPC);

/* Same as `task_setcomm_of()', but set for the calling thread. */
FUNDEF NONNULL((1)) void
NOTHROW(FCALL task_setcomm)(char const *__restrict name);

#else /* CONFIG_HAVE_KERNEL_TASK_COMM */

#define task_getcomm()              ""
#define task_setcomm(name)          (void)0
#define task_getcomm_of(self, buf)  (void)((buf)[0] = '\0')
#define task_setcomm_of(self, name) 1

#endif /* !CONFIG_HAVE_KERNEL_TASK_COMM */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_COMM_H */
