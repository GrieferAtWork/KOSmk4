/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_ENUM_H
#define GUARD_KERNEL_INCLUDE_SCHED_ENUM_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

/* Helper functions for enumerating KOS system threads. */

DECL_BEGIN

#ifdef __CC__
struct taskpid;
struct task;
struct pidns;
struct cpu;
struct mman;

/* Callback prototype for task enumeration functions.
 * @param: thread: The actual thread (or `NULL' if `pid' is non-NULL,
 *                 and the thread has become a zombie)
 * @param: pid:    The PID of the thread (or `NULL' if there is none)
 * @return: >= 0: Add this value to the to-be returned value of the enumerator.
 * @return: <  0: Stop enumeration and immediately re-return this value. */
typedef ssize_t (KCALL *task_enum_cb_t)(void *arg,
                                        struct task *thread,
                                        struct taskpid *pid);

/* Enumerate  all  threads  found  anywhere  on  the  system.
 * This is the same as calling `task_enum_cpu()' for all CPUs
 * @throws: E_BADALLOC: Failed to allocate memory for intermediate buffers. */
FUNDEF NONNULL((1)) ssize_t KCALL
task_enum_all(task_enum_cb_t cb, void *arg)
		THROWS(E_BADALLOC, ...);

/* Enumerate all user-space threads.
 * @throws: E_BADALLOC: Failed to allocate memory for intermediate buffers. */
FUNDEF NONNULL((1)) ssize_t KCALL
task_enum_user(task_enum_cb_t cb, void *arg)
		THROWS(E_BADALLOC, ...);

/* Enumerate all kernel-space threads.
 * @throws: E_BADALLOC: Failed to allocate memory for intermediate buffers. */
FUNDEF NONNULL((1)) ssize_t KCALL
task_enum_kernel(task_enum_cb_t cb, void *arg)
		THROWS(E_BADALLOC, ...);

/* Enumerate all  threads  apart  of the  same  process  as  `proc'
 * If `proc' is a kernel-space thread, same as `task_enum_kernel()'
 * @throws: E_BADALLOC: Failed to allocate memory for intermediate buffers. */
FUNDEF NONNULL((1, 3)) ssize_t KCALL
task_enum_process_threads(task_enum_cb_t cb, void *arg,
                          struct task *__restrict proc)
		THROWS(E_BADALLOC, ...);

/* Same as `task_enum_process_threads()', but don't enumerate `task_getprocess_of(proc)'
 * @throws: E_BADALLOC: Failed to allocate memory for intermediate buffers. */
FUNDEF NONNULL((1, 3)) ssize_t KCALL
task_enum_process_worker_threads(task_enum_cb_t cb, void *arg,
                                 struct task *__restrict proc)
		THROWS(E_BADALLOC, ...);

/* Enumerate  all children  of the  given `proc'.  (i.e. the threads
 * that `proc' can `wait(2)' for).  This also includes threads  that
 * could  also  be  enumerated  using  `task_enum_process_threads()'
 * Note however that this function will not enumerate `proc' itself,
 * and when `proc' is a  kernel-thread, nothing will be  enumerated.
 * @throws: E_BADALLOC: Failed to allocate memory for intermediate buffers. */
FUNDEF NONNULL((1, 3)) ssize_t KCALL
task_enum_process_children(task_enum_cb_t cb, void *arg,
                           struct task *__restrict proc)
		THROWS(E_BADALLOC, ...);

/* Enumerate the leaders of all processes that are apart of the
 * same process group as `proc_group'
 * @throws: E_BADALLOC: Failed to allocate memory for intermediate buffers. */
FUNDEF NONNULL((1, 3)) ssize_t KCALL
task_enum_procgroup_processes(task_enum_cb_t cb, void *arg,
                              struct task *__restrict proc_group)
		THROWS(E_BADALLOC, ...);

/* Similar  to `task_enum_user()': Enumerate the leaders of running
 * user-space processes, as visible by `ns'. These are identical to
 * what will show up under `/proc'
 * @throws: E_BADALLOC: Failed to allocate memory for intermediate buffers. */
FUNDEF NONNULL((1, 3)) ssize_t KCALL
task_enum_processes(task_enum_cb_t cb, void *arg,
                    struct pidns *__restrict ns)
		THROWS(E_BADALLOC, ...);

/* Similar to `task_enum_processes()', but don't just enumerate
 * threads that are process leaders, but all threads from  `ns'
 * @throws: E_BADALLOC: Failed to allocate memory for intermediate buffers. */
FUNDEF NONNULL((1, 3)) ssize_t KCALL
task_enum_namespace(task_enum_cb_t cb, void *arg,
                    struct pidns *__restrict ns)
		THROWS(E_BADALLOC, ...);

/* Enumerate all threads  running, sleeping, or  pending on  `c'
 * Threads that have terminated, or haven't been started are not
 * enumerated by this function.
 * @throws: E_BADALLOC: Failed to allocate memory for intermediate buffers. */
FUNDEF NONNULL((1, 3)) ssize_t KCALL
task_enum_cpu(task_enum_cb_t cb, void *arg,
              struct cpu *__restrict c)
		THROWS(E_BADALLOC, ...);

/* Enumerate all threads that are using `v' as their active VM.
 * @throws: E_BADALLOC: Failed to allocate memory for intermediate buffers. */
FUNDEF NONNULL((1, 3)) ssize_t KCALL
task_enum_mman(task_enum_cb_t cb, void *arg,
               struct mman *__restrict mm)
		THROWS(E_BADALLOC, ...);



/* These functions are the same as those above, however these may only be used
 * when `cb' is NOBLOCK+NOEXCEPT, as these may invoke said function while non-
 * reentrant, internal locks are held. */
FUNDEF NOBLOCK NONNULL((1)) ssize_t NOTHROW(KCALL task_enum_all_nb)(task_enum_cb_t cb, void *arg);
FUNDEF NOBLOCK NONNULL((1)) ssize_t NOTHROW(KCALL task_enum_user_nb)(task_enum_cb_t cb, void *arg);
FUNDEF NOBLOCK NONNULL((1)) ssize_t NOTHROW(KCALL task_enum_kernel_nb)(task_enum_cb_t cb, void *arg);
FUNDEF NOBLOCK NONNULL((1, 3)) ssize_t NOTHROW(KCALL task_enum_process_threads_nb)(task_enum_cb_t cb, void *arg, struct task *__restrict proc);
FUNDEF NOBLOCK NONNULL((1, 3)) ssize_t NOTHROW(KCALL task_enum_process_worker_threads_nb)(task_enum_cb_t cb, void *arg, struct task *__restrict proc);
FUNDEF NOBLOCK NONNULL((1, 3)) ssize_t NOTHROW(KCALL task_enum_process_children_nb)(task_enum_cb_t cb, void *arg, struct task *__restrict proc);
FUNDEF NOBLOCK NONNULL((1, 3)) ssize_t NOTHROW(KCALL task_enum_procgroup_processes_nb)(task_enum_cb_t cb, void *arg, struct task *__restrict proc);
FUNDEF NOBLOCK NONNULL((1, 3)) ssize_t NOTHROW(KCALL task_enum_processes_nb)(task_enum_cb_t cb, void *arg, struct pidns *__restrict ns);
FUNDEF NOBLOCK NONNULL((1, 3)) ssize_t NOTHROW(KCALL task_enum_namespace_nb)(task_enum_cb_t cb, void *arg, struct pidns *__restrict ns);
FUNDEF NOBLOCK NONNULL((1, 3)) ssize_t NOTHROW(KCALL task_enum_cpu_nb)(task_enum_cb_t cb, void *arg, struct cpu *__restrict c);
FUNDEF NOBLOCK NONNULL((1, 3)) ssize_t NOTHROW(KCALL task_enum_mman_nb)(task_enum_cb_t cb, void *arg, struct mman *__restrict mm);

/* Same as `task_enum_all_nb()', but directly access the structures of other CPUs,
 * rather  than sending IPIs  and letting those CPUs  access their own structures.
 * Doing it this  way must  be done when  the caller  knows that no  other CPU  is
 * actively running. */
FUNDEF NONNULL((1)) ssize_t
NOTHROW(KCALL task_enum_all_noipi_nb)(task_enum_cb_t cb, void *arg)
#ifdef CONFIG_NO_SMP
		ASMNAME("task_enum_all_nb")
#endif /* CONFIG_NO_SMP */
		;


struct task_list_buffer {
	REF struct task    **tlb_task_buf;    /* [1..1][out:ref][0..tlb_task_len] Output buffer for threads. */
	size_t               tlb_task_len;    /* in:  Available buffer length.
	                                       * out: [success] Used buffer length.
	                                       * out: [failure] Required buffer length. */
	REF struct taskpid **tlb_taskpid_buf; /* [1..1][out:ref][0..tlb_taskpid_len] Output buffer for zombie-threads. */
	size_t               tlb_taskpid_len; /* in:  Available buffer length.
	                                       * out: [success] Used buffer length.
	                                       * out: [failure] Required buffer length. */
};

/* These functions are  also the  same as  those above,  however these  will yield  a
 * list of references, rather than invoke some callback for every thread encountered.
 * @return: true:  Success: References  to  enumerated  components are  stored  in `*buf'
 *                          The actual number of returned task/taskpid objects is written
 *                          back to the buffer length fields.
 * @return: false: Failure: The given buffers were too  small. In this case, the  contents
 *                          of the pointed-to buffers are undefined, however no references
 *                          were actually stored inside of any of them.
 *                          The caller should resize their buffers to have sufficient  space
 *                          for at least the same # of task/taskpid elements as written back
 *                          to the buffer length fields by this function. */
FUNDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL task_list_all)(struct task_list_buffer *__restrict buf);
FUNDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL task_list_user)(struct task_list_buffer *__restrict buf);
FUNDEF NOBLOCK NONNULL((1, 2)) __BOOL NOTHROW(FCALL task_list_process_threads)(struct task_list_buffer *__restrict buf, struct task *__restrict proc);
FUNDEF NOBLOCK NONNULL((1, 2)) __BOOL NOTHROW(FCALL task_list_process_worker_threads)(struct task_list_buffer *__restrict buf, struct task *__restrict proc);
FUNDEF NOBLOCK NONNULL((1, 2)) __BOOL NOTHROW(FCALL task_list_process_children)(struct task_list_buffer *__restrict buf, struct task *__restrict proc);
FUNDEF NOBLOCK NONNULL((1, 2)) __BOOL NOTHROW(FCALL task_list_procgroup_processes)(struct task_list_buffer *__restrict buf, struct task *__restrict proc);
FUNDEF NOBLOCK NONNULL((1, 2)) __BOOL NOTHROW(FCALL task_list_processes)(struct task_list_buffer *__restrict buf, struct pidns *__restrict ns);
FUNDEF NOBLOCK NONNULL((1, 2)) __BOOL NOTHROW(FCALL task_list_namespace)(struct task_list_buffer *__restrict buf, struct pidns *__restrict ns);

/* @return: <= buflen: Success: `buf[0..return-1]' now contain references to enumerated threads.
 * @return: > buflen:  Error:   Insufficient buffer space. (Try again with more buffer memory).
 *                              The contents of `buf[*]' are undefined, but no references  will
 *                              be contained inside. */
FUNDEF NOBLOCK NONNULL((1)) size_t NOTHROW(FCALL task_list_kernel)(/*out*/ REF struct task **buf, size_t buflen);
FUNDEF NOBLOCK NONNULL((1, 3)) size_t NOTHROW(FCALL task_list_cpu)(/*out*/ REF struct task **buf, size_t buflen, struct cpu *__restrict c);
FUNDEF NOBLOCK NONNULL((1, 3)) size_t NOTHROW(FCALL task_list_mman)(/*out*/ REF struct task **buf, size_t buflen, struct mman *__restrict mm);



#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_ENUM_H */
