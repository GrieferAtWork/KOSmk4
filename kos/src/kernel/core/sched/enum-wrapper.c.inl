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
#ifdef __INTELLISENSE__
#include "enum.c"
//#define DEFINE_task_enum_all  1
//#define DEFINE_task_enum_user 1
//#define    DEFINE_task_enum_process_threads     1
//#define DEFINE_task_enum_process_worker_threads 1
//#define    DEFINE_task_enum_process_children    1
//#define  DEFINE_task_enum_procgroup_processes   1
//#define       DEFINE_task_enum_processes        1
//#define       DEFINE_task_enum_namespace        1
//#define         DEFINE_task_enum_kernel         1
//#define DEFINE_task_enum_cpu 1
#define DEFINE_task_enum_mman 1
#endif /* __INTELLISENSE__ */

#if defined(DEFINE_task_enum_all)

/* Enumerate all threads found anywhere on the system. */
#define LOCAL_task_enum_onstck task_enum_all_onstck
#define LOCAL_task_enum_onheap task_enum_all_onheap
#define LOCAL_task_enum        task_enum_all
#define LOCAL_task_enum_nb     task_enum_all_nb
#define LOCAL_task_list        task_list_all
#define LOCAL_EXTRA__PARAM     /* nothing */
#define LOCAL_EXTRA__ARGS      /* nothing */

#elif defined(DEFINE_task_enum_user)

/* Enumerate all user-space threads. */
#define LOCAL_task_enum_onstck task_enum_user_onstck
#define LOCAL_task_enum_onheap task_enum_user_onheap
#define LOCAL_task_enum        task_enum_user
#define LOCAL_task_enum_nb     task_enum_user_nb
#define LOCAL_task_list        task_list_user
#define LOCAL_EXTRA__PARAM     /* nothing */
#define LOCAL_EXTRA__ARGS      /* nothing */

#elif defined(DEFINE_task_enum_process_threads)

/* Enumerate all  threads  apart  of the  same  process  as  `proc'
 * If `proc' is a kernel-space thread, same as `task_enum_kernel()' */
#define LOCAL_task_enum_onstck task_enum_process_threads_onstck
#define LOCAL_task_enum_onheap task_enum_process_threads_onheap
#define LOCAL_task_enum        task_enum_process_threads
#define LOCAL_task_enum_nb     task_enum_process_threads_nb
#define LOCAL_task_list        task_list_process_threads
#define LOCAL_EXTRA__PARAM     , struct task *__restrict proc
#define LOCAL_EXTRA__ARGS      , proc

#elif defined(DEFINE_task_enum_process_worker_threads)

/* Same as `task_enum_process_threads()', but don't enumerate `task_getprocess_of(proc)' */
#define LOCAL_task_enum_onstck task_enum_process_worker_threads_onstck
#define LOCAL_task_enum_onheap task_enum_process_worker_threads_onheap
#define LOCAL_task_enum        task_enum_process_worker_threads
#define LOCAL_task_enum_nb     task_enum_process_worker_threads_nb
#define LOCAL_task_list        task_list_process_worker_threads
#define LOCAL_EXTRA__PARAM     , struct task *__restrict proc
#define LOCAL_EXTRA__ARGS      , proc

#elif defined(DEFINE_task_enum_process_children)

/* Enumerate  all children  of the  given `proc'.  (i.e. the threads
 * that `proc' can `wait(2)' for).  This also includes threads  that
 * could  also  be  enumerated  using  `task_enum_process_threads()'
 * Note however that this function will not enumerate `proc' itself,
 * and when `proc' is a  kernel-thread, nothing will be  enumerated. */
#define LOCAL_task_enum_onstck task_enum_process_children_onstck
#define LOCAL_task_enum_onheap task_enum_process_children_onheap
#define LOCAL_task_enum        task_enum_process_children
#define LOCAL_task_enum_nb     task_enum_process_children_nb
#define LOCAL_task_list        task_list_process_children
#define LOCAL_EXTRA__PARAM     , struct task *__restrict proc
#define LOCAL_EXTRA__ARGS      , proc

#elif defined(DEFINE_task_enum_procgroup_processes)

/* Enumerate the leaders of all processes that are apart of the
 * same process group as `proc_group' */
#define LOCAL_task_enum_onstck task_enum_procgroup_processes_onstck
#define LOCAL_task_enum_onheap task_enum_procgroup_processes_onheap
#define LOCAL_task_enum        task_enum_procgroup_processes
#define LOCAL_task_enum_nb     task_enum_procgroup_processes_nb
#define LOCAL_task_list        task_list_procgroup_processes
#define LOCAL_EXTRA__PARAM     , struct task *__restrict proc_group
#define LOCAL_EXTRA__ARGS      , proc_group

#elif defined(DEFINE_task_enum_processes)

/* Similar  to `task_enum_user()': Enumerate the leaders of running
 * user-space processes, as visible by `ns'. These are identical to
 * what will show up under `/proc' */
#define LOCAL_task_enum_onstck task_enum_processes_onstck
#define LOCAL_task_enum_onheap task_enum_processes_onheap
#define LOCAL_task_enum        task_enum_processes
#define LOCAL_task_enum_nb     task_enum_processes_nb
#define LOCAL_task_list        task_list_processes
#define LOCAL_EXTRA__PARAM     , struct pidns *__restrict ns
#define LOCAL_EXTRA__ARGS      , ns

#elif defined(DEFINE_task_enum_namespace)

/* Similar to `task_enum_processes()', but don't just enumerate
 * threads that are process leaders, but all threads from  `ns' */
#define LOCAL_task_enum_onstck task_enum_namespace_onstck
#define LOCAL_task_enum_onheap task_enum_namespace_onheap
#define LOCAL_task_enum        task_enum_namespace
#define LOCAL_task_enum_nb     task_enum_namespace_nb
#define LOCAL_task_list        task_list_namespace
#define LOCAL_EXTRA__PARAM     , struct pidns *__restrict ns
#define LOCAL_EXTRA__ARGS      , ns

#elif defined(DEFINE_task_enum_kernel)
#define NO_TASKPID_BUFFER 1

/* Enumerate all kernel-space threads. */
#define LOCAL_task_enum_onstck task_enum_kernel_onstck
#define LOCAL_task_enum_onheap task_enum_kernel_onheap
#define LOCAL_task_enum        task_enum_kernel
#define LOCAL_task_enum_nb     task_enum_kernel_nb
#define LOCAL_task_list        task_list_kernel
#define LOCAL_EXTRA__PARAM     /* nothing */
#define LOCAL_EXTRA__ARGS      /* nothing */

#elif defined(DEFINE_task_enum_cpu)
#define NO_TASKPID_BUFFER 1

/* Enumerate all kernel-space threads. */
#define LOCAL_task_enum_onstck task_enum_cpu_onstck
#define LOCAL_task_enum_onheap task_enum_cpu_onheap
#define LOCAL_task_enum        task_enum_cpu
#define LOCAL_task_enum_nb     task_enum_cpu_nb
#define LOCAL_task_list        task_list_cpu
#define LOCAL_EXTRA__PARAM     , struct cpu *__restrict c
#define LOCAL_EXTRA__ARGS      , c

#elif defined(DEFINE_task_enum_mman)
#define NO_TASKPID_BUFFER 1

/* Enumerate all threads that are using `mm' as their active MMan. */
#define LOCAL_task_enum_onstck task_enum_vm_onstck
#define LOCAL_task_enum_onheap task_enum_vm_onheap
#define LOCAL_task_enum        task_enum_mman
#define LOCAL_task_enum_nb     task_enum_mman_nb
#define LOCAL_task_list        task_list_mman
#define LOCAL_EXTRA__PARAM     , struct mman *__restrict mm
#define LOCAL_EXTRA__ARGS      , mm

#else /* DEFINE_... */
#error "Bad configuration"
#endif /* !DEFINE_... */


DECL_BEGIN

/* Enumerate tasks on-stack. */
#ifdef NO_TASKPID_BUFFER
PRIVATE ATTR_NOINLINE NONNULL((1)) size_t KCALL
LOCAL_task_enum_onstck(task_enum_cb_t cb, void *arg,
                       size_t buflen,
                       ssize_t *__restrict retval
                       LOCAL_EXTRA__PARAM)
		THROWS(E_WOULDBLOCK, ...) {
	size_t result;
	REF struct task **buf;
	buf = (REF struct task **)alloca(buflen * sizeof(REF struct task *));
	result = LOCAL_task_list(buf, buflen LOCAL_EXTRA__ARGS);
	if (result <= buflen) {
		/* Got it! -> Now to actually enumerate threads! */
		*retval = enum_task_list_and_decref(buf, buflen, cb, arg);
	}
	return result;
}

PRIVATE NONNULL((1)) ssize_t KCALL
LOCAL_task_enum_onheap(task_enum_cb_t cb, void *arg,
                       size_t buflen
                       LOCAL_EXTRA__PARAM)
		THROWS(E_BADALLOC, E_WOULDBLOCK, ...) {
	ssize_t result;
	REF struct task **buf;
	buf = (REF struct task **)kmalloc(buflen * sizeof(REF struct task *),
	                                  GFP_NORMAL);
	TRY {
		/* Enumerate threads, and keep on increasing the
		 * buffer size if the buffer continues to be too
		 * small. */
		size_t new_buflen;
		for (;;) {
			new_buflen = LOCAL_task_list(buf, buflen LOCAL_EXTRA__ARGS);
			if (new_buflen <= buflen)
				break; /* Got it! */
			/* Allocate a larger buffer. */
			buf = (REF struct task **)krealloc(buf,
			                                   new_buflen *
			                                   sizeof(REF struct task *),
			                                   GFP_NORMAL);
			/* Use the new (larger) buffer length. */
			buflen = new_buflen;
		}
		/* Enumerate threads, and inherit all of the references we've been given. */
		result = enum_task_list_and_decref(buf, buflen, cb, arg);
	} EXCEPT {
		kfree(buf);
		RETHROW();
	}
	kfree(buf);
	return result;
}
#else /* NO_TASKPID_BUFFER */
PRIVATE ATTR_NOINLINE NONNULL((1, 3)) bool KCALL
LOCAL_task_enum_onstck(task_enum_cb_t cb, void *arg,
                       struct task_list_buffer *__restrict buf,
                       ssize_t *__restrict retval
                       LOCAL_EXTRA__PARAM)
		THROWS(E_WOULDBLOCK, ...) {
	buf->tlb_task_buf = (REF struct task **)alloca(buf->tlb_task_len *
	                                               sizeof(REF struct task *));
	buf->tlb_taskpid_buf = (REF struct taskpid **)alloca(buf->tlb_taskpid_len *
	                                                     sizeof(REF struct taskpid *));
	if (!LOCAL_task_list(buf LOCAL_EXTRA__ARGS))
		return false; /* Still too small. */
	/* Got it! -> Now to actually enumerate threads! */
	*retval = task_list_buffer_enum_and_decref(buf, cb, arg);
	return true;
}

PRIVATE NONNULL((1)) ssize_t KCALL
LOCAL_task_enum_onheap(task_enum_cb_t cb, void *arg,
                       struct task_list_buffer *__restrict buf
                       LOCAL_EXTRA__PARAM)
		THROWS(E_BADALLOC, E_WOULDBLOCK, ...) {
	ssize_t result;
	task_list_buffer_alloc_heap_buffers(buf);
	TRY {
		/* Enumerate threads, and keep on increasing the
		 * buffer size if the buffer continues to be too
		 * small. */
		while (!LOCAL_task_list(buf LOCAL_EXTRA__ARGS))
			task_list_buffer_realloc_heap_buffers(buf);
		/* Enumerate threads, and inherit all of the references we've been given. */
		result = task_list_buffer_enum_and_decref(buf, cb, arg);
	} EXCEPT {
		task_list_buffer_free_heap_buffers(buf);
		RETHROW();
	}
	task_list_buffer_free_heap_buffers(buf);
	return result;
}
#endif /* !NO_TASKPID_BUFFER */

/* Enumerate threads.
 * @throws: E_BADALLOC: Only outside of debugger-mode: Failed  to
 *                      allocate memory for intermediate buffers. */
PUBLIC NONNULL((1)) ssize_t KCALL
LOCAL_task_enum(task_enum_cb_t cb, void *arg
                LOCAL_EXTRA__PARAM)
		THROWS(E_BADALLOC, E_WOULDBLOCK, ...) {
	ssize_t result;
#ifdef NO_TASKPID_BUFFER
	size_t buflen;
	buflen = INITIAL_TASK_STACK_BUFSIZE;
	for (;;) {
		size_t new_buflen;
		new_buflen = LOCAL_task_enum_onstck(cb, arg, buflen, &result LOCAL_EXTRA__ARGS);
		if (new_buflen <= buflen)
			goto done;
		buflen = new_buflen;
		/* Need to more space. */
		if (buflen > MAX_STACK_BUFELEM)
			break;
	}
	result = LOCAL_task_enum_onheap(cb, arg, buflen LOCAL_EXTRA__ARGS);
#else /* NO_TASKPID_BUFFER */
	struct task_list_buffer buf;
	buf.tlb_task_len    = INITIAL_TASK_STACK_BUFSIZE;
	buf.tlb_taskpid_len = INITIAL_TASKPID_STACK_BUFSIZE;
	for (;;) {
		size_t total_elem;
		if (LOCAL_task_enum_onstck(cb, arg, &buf, &result LOCAL_EXTRA__ARGS))
			goto done;
		/* Need to more space. */
		if (unlikely(OVERFLOW_UADD(buf.tlb_task_len,
		                           buf.tlb_taskpid_len,
		                           &total_elem)) ||
		    total_elem > MAX_STACK_BUFELEM)
			break;
	}
	result = LOCAL_task_enum_onheap(cb, arg, &buf LOCAL_EXTRA__ARGS);
#endif /* !NO_TASKPID_BUFFER */
done:
	return result;
}


/* List threads. */
#ifdef NO_TASKPID_BUFFER
/* @return: <= buflen: Success: `buf[0..return-1]' now contain references to enumerated threads.
 * @return: > buflen:  Error:   Insufficient buffer space. (Try again with more buffer memory).
 *                              The contents of `buf[*]' are undefined, but no references  will
 *                              be contained inside. */
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL LOCAL_task_list)(/*out*/ REF struct task **buf,
                               size_t buflen LOCAL_EXTRA__PARAM) {
	struct task_enum_list_taskonly_cb_data data;
	data.el_buf  = buf;
	data.el_size = buflen;
	data.el_used = 0;
	LOCAL_task_enum_nb(&task_enum_list_taskonly_cb,
	                   &data LOCAL_EXTRA__ARGS);
	__builtin_assume(data.el_buf == buf);
	__builtin_assume(data.el_size == buflen);
	if (data.el_used > buflen) {
		/* Don't return any references in this case! */
		decref_task_list(buf, buflen);
	}
	return data.el_used;
}
#else /* NO_TASKPID_BUFFER */

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
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL LOCAL_task_list)(struct task_list_buffer *__restrict buf
                               LOCAL_EXTRA__PARAM) {
	struct task_enum_list_cb_data data;
	data.el_buf          = buf;
	data.el_used_task    = 0;
	data.el_used_taskpid = 0;
	LOCAL_task_enum_nb(&task_enum_list_cb,
	                   &data LOCAL_EXTRA__ARGS);
	__builtin_assume(data.el_buf == buf);
	if likely(data.el_used_task <= buf->tlb_task_len &&
	          data.el_used_taskpid <= buf->tlb_taskpid_len) {
		buf->tlb_task_len    = data.el_used_task;
		buf->tlb_taskpid_len = data.el_used_taskpid;
		return true;
	}
	/* Don't return any references in this case! */
	decref_task_list(buf->tlb_task_buf, buf->tlb_task_len);
	decref_taskpid_list(buf->tlb_taskpid_buf, buf->tlb_taskpid_len);
	buf->tlb_task_len    = data.el_used_task;
	buf->tlb_taskpid_len = data.el_used_taskpid;
	return false;
}
#endif /* !NO_TASKPID_BUFFER */


#undef NO_TASKPID_BUFFER

#undef LOCAL_task_enum_onstck
#undef LOCAL_task_enum_onheap
#undef LOCAL_task_enum
#undef LOCAL_task_enum_nb
#undef LOCAL_task_list
#undef LOCAL_EXTRA__PARAM
#undef LOCAL_EXTRA__ARGS

DECL_END

#undef DEFINE_task_enum_all
#undef DEFINE_task_enum_user
#undef DEFINE_task_enum_process_threads
#undef DEFINE_task_enum_process_worker_threads
#undef DEFINE_task_enum_process_children
#undef DEFINE_task_enum_procgroup_processes
#undef DEFINE_task_enum_processes
#undef DEFINE_task_enum_namespace
#undef DEFINE_task_enum_kernel
#undef DEFINE_task_enum_cpu
#undef DEFINE_task_enum_mman
