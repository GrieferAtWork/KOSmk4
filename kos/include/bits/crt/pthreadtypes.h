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
/*!included_by <pthread.h>*/
#ifndef _BITS_CRT_PTHREADTYPES_H
#define _BITS_CRT_PTHREADTYPES_H 1

#include <__stdinc.h>

#include <hybrid/byteorder.h>
#include <hybrid/typecore.h>

#include <asm/crt/pthreadvalues.h>
#include <bits/crt/pthreadtypesizes.h>

#undef __USE_PTHREAD_INTERNALS
#if defined(__KOS__) && (defined(__BUILDING_LIBC) || defined(_LIBC_SOURCE))
#define __USE_PTHREAD_INTERNALS 1
#endif /* __KOS__ && (__BUILDING_LIBC || _LIBC_SOURCE) */

#ifdef __USE_PTHREAD_INTERNALS
#include <asm/unistd.h>              /* __NR_set_userprocmask_address */
#include <bits/os/sched.h>           /* `struct sched_param' */
#include <bits/types.h>              /* __pid_t, etc... */
#include <kos/anno.h>                /* __WEAK */
#include <kos/bits/exception_info.h> /* `struct exception_info' */
#undef __LIBC_CONFIG_HAVE_USERPROCMASK
#ifdef __NR_set_userprocmask_address
#define __LIBC_CONFIG_HAVE_USERPROCMASK 1
#endif /* __NR_set_userprocmask_address */
#ifdef __LIBC_CONFIG_HAVE_USERPROCMASK
#include <kos/bits/userprocmask.h>
#endif /* __LIBC_CONFIG_HAVE_USERPROCMASK */

#endif /* __USE_PTHREAD_INTERNALS */

__DECL_BEGIN

#ifdef __CC__
typedef __TYPEFOR_UINTIB(__SIZEOF_PTHREAD_KEY_T) __pthread_key_t;
typedef __TYPEFOR_INTIB(__SIZEOF_PTHREAD_ONCE_T) __pthread_once_t;
#endif /* __CC__ */

#ifdef __USE_PTHREAD_INTERNALS
#ifdef __KOS__
#ifdef __LIBC_CONFIG_HAVE_USERPROCMASK
#define __OFFSET_PTHREAD_PMASK     0
#define __OFFSET_PTHREAD_TID       (__OFFSET_PTHREAD_PMASK + __OFFSET_USERPROCMASK_MYTID)
#define __OFFSET_PTHREAD_REFCNT    (__SIZEOF_USERPROCMASK + (__SIZEOF_SIGSET_T__ * 2))
#else /* __LIBC_CONFIG_HAVE_USERPROCMASK */
#define __OFFSET_PTHREAD_TID       0
#define __OFFSET_PTHREAD_REFCNT    ((__SIZEOF_POINTER__ * 2) + __SIZEOF_SIGSET_T__)
#endif /* !__LIBC_CONFIG_HAVE_USERPROCMASK */
#define __OFFSET_PTHREAD_RETVAL    (__OFFSET_PTHREAD_REFCNT + __SIZEOF_POINTER__)
#define __OFFSET_PTHREAD_TLS       (__OFFSET_PTHREAD_REFCNT + __SIZEOF_POINTER__ * 2)
#define __OFFSET_PTHREAD_STACKADDR (__OFFSET_PTHREAD_REFCNT + __SIZEOF_POINTER__ * 3)
#define __OFFSET_PTHREAD_STACKSIZE (__OFFSET_PTHREAD_REFCNT + __SIZEOF_POINTER__ * 4)
#define __OFFSET_PTHREAD_FLAGS     (__OFFSET_PTHREAD_REFCNT + __SIZEOF_POINTER__ * 5)

#define PTHREAD_FNORMAL    0x0000 /* Normal pthread flags. */
#define PTHREAD_FUSERSTACK 0x0001 /* [const] The thread's stack was provided by the
                                   * user and should not be unmapped automatically. */
#define PTHREAD_FNOSTACK   0x0002 /* [const] The thread's stack area is unknown (this is the case
                                   * for the main thread, and  any thread created by  `clone()'). */
#define PTHREAD_FTIDSET    0x8000 /* [lock(WRITE_ONCE)] Internal flag: `set_tid_address(2)' has been called. */

/* The different kinds of errno codes known to libc */
#define LIBC_ERRNO_KIND_KOS 0 /* E* */
#define LIBC_ERRNO_KIND_DOS 1 /* DOS_E* */
#define LIBC_ERRNO_KIND_CYG 2 /* CYG_E* */
#define LIBC_ERRNO_KIND_NT  3 /* NT error codes */

#ifdef __CC__
struct __cpu_set_struct;
#ifdef __LIBC_CONFIG_HAVE_USERPROCMASK
struct libc_userprocmask {
	struct userprocmask    lpm_pmask;    /* The underlying userprocmask controller. */
	struct __sigset_struct lpm_masks[2]; /* Static signal masks buffers that sigprocmask() will cycle between. */
};
#endif /* !__LIBC_CONFIG_HAVE_USERPROCMASK */

struct libc_tlsglobals;
struct pthread {
#ifdef __LIBC_CONFIG_HAVE_USERPROCMASK
#define _pthread_tid(self) (self)->pt_pmask.lpm_pmask.pm_mytid
	struct libc_userprocmask pt_pmask;       /* User-space sigprocmask address */
#else /* __LIBC_CONFIG_HAVE_USERPROCMASK */
#define _pthread_tid(self) (self)->pt_tid
	__pid_t                  pt_tid;         /* Thread TID (filled  in by  the kernel  as the  PTID and  CTID)
	                                          * Cleared to ZERO(0) (by the kernel) when the thread terminates.
	                                          * s.a. `set_tid_address(2)' */
#if __SIZEOF_PID_T__ < __SIZEOF_POINTER__
	__byte_t               __pt_pad[__SIZEOF_POINTER__ - __SIZEOF_PID_T__];
#endif /* __SIZEOF_PID_T__ < __SIZEOF_POINTER__ */
	struct __sigset_struct  *pt_emumaskptr;  /* Address of the current, emulated userprocmask */
	struct __sigset_struct   pt_emumask;     /* TLS buffer for the initial, emulated userprocmask */
#endif /* !__LIBC_CONFIG_HAVE_USERPROCMASK */
	__WEAK __uintptr_t       pt_refcnt;      /* Reference counter for this control structure.
	                                          * When this hits ZERO, you must call `dltlsfreeseg(pt_tls)',
	                                          * which will also delete our structure, since we're embedded
	                                          * within the associated thread's TLS segment. */
	void                    *pt_retval;      /* [lock(WRITE_ONCE)] Thread return value (as passed to `pthread_exit(3)') (also used as argument for `pt_start') */
	void                    *pt_tls;         /* [const] TLS segment base address (allocated by `dltlsallocseg(3D)', freed in `pthread_exit(3)')
	                                          *         (or NULL if not lazily initialized within the main() thread). */
	void                    *pt_stackaddr;   /* [const] Thread stack address (or NULL if not lazily initialized within the main() thread) */
	__size_t                 pt_stacksize;   /* [const] Thread stack size (or 0 if not lazily initialized within the main() thread) */
	unsigned int             pt_flags;       /* [lock(...)] Flags (Set of `PTHREAD_F*') */
	__fd_t                   pt_pidfd;       /* [lock(WRITE_ONCE)][valid_if(PTHREAD_FHASPIDFD)] Thread PID file descriptor (s.a. `CLONE_PIDFD', `sys_pidfd_open(2)') */
	__uint32_t               pt_suspended;   /* [lock(READ(ATOMIC), WRITE(ATOMIC && INTERN(:pthread_suspend_lock)))] Suspend recursion of this thread, (when this drops to 0, must futex-wake on this address) */
	/* TODO: Get rid of the following 2 members. - They're only used during `libc_pthread_main()'! */
	struct __cpu_set_struct *pt_cpuset;      /* [0..pt_cpusetsize] Initial affinity cpuset. */
	__size_t                 pt_cpusetsize;  /* Initial affinity cpuset size. */
	struct exception_info    pt_except;      /* Exception information */
	unsigned int             pt_errno_kind;  /* Errno kind (one of `LIBC_ERRNO_KIND_*') */
	__errno_t                pt_errno_value; /* Errno value */
	struct libc_tlsglobals  *pt_tglobals;    /* [0..1] TLS globals (stuff like `strtok(3)'s internal buffer) */
};
typedef struct pthread *__pthread_t;
#endif /* __CC__ */
#else /* __KOS__ */
#ifdef __CC__
struct pthread;
typedef struct pthread *__pthread_t;
#endif /* __CC__ */
#endif /* !__KOS__ */
#else /* __USE_PTHREAD_INTERNALS */
#ifdef __CC__
typedef __TYPEFOR_UINTIB(__SIZEOF_PTHREAD_T) __pthread_t;
#endif /* __CC__ */
#endif /* !__USE_PTHREAD_INTERNALS */

#ifdef __USE_PTHREAD_INTERNALS
#define PTHREAD_ATTR_FLAG_DETACHSTATE     0x0001 /* set:PTHREAD_CREATE_DETACHED; unset:PTHREAD_CREATE_JOINABLE */
#define PTHREAD_ATTR_FLAG_NOTINHERITSCHED 0x0002 /* set:PTHREAD_EXPLICIT_SCHED; unset:PTHREAD_INHERIT_SCHED */
#define PTHREAD_ATTR_FLAG_SCOPEPROCESS    0x0004 /* set:PTHREAD_SCOPE_PROCESS; unset:PTHREAD_SCOPE_SYSTEM */
#define PTHREAD_ATTR_FLAG_STACKADDR       0x0008 /* `pa_stackaddr' and `pa_stacksize' are valid */
#define PTHREAD_ATTR_FLAG_OLDATTR         0x0010 /* Don't `free(pa_cpuset)' */
#define PTHREAD_ATTR_FLAG_SCHED_SET       0x0020 /* `pa_schedparam' is valid */
#define PTHREAD_ATTR_FLAG_POLICY_SET      0x0040 /* `pa_schedpolicy' is valid */
#define PTHREAD_ATTR_FLAG_WANT_PIDFD      0x1000 /* Allocate a PIDfd for the thread as part of its creation */
#define PTHREAD_ATTR_FLAG_START_SUSPENDED 0x8000 /* The thread should start in a suspended state (requiring an initial call to `pthread_resume_np(3)'/`pthread_unsuspend_np(3)'/`pthread_continue_np(3)') */

#define __OFFSET_PTHREAD_ATTR_SCHEDPARAM  0
#define __OFFSET_PTHREAD_ATTR_SCHEDPOLICY __SIZEOF_SCHED_PARAM
#define __OFFSET_PTHREAD_ATTR_FLAGS       (__SIZEOF_SCHED_PARAM + 4)
#if ((__SIZEOF_SCHED_PARAM + 8) & (__SIZEOF_SIZE_T__ - 1)) != 0
#define __OFFSET_PTHREAD_ATTR_GUARDSIZE   (__SIZEOF_SCHED_PARAM + 8 + (__SIZEOF_SIZE_T__ - ((__SIZEOF_SCHED_PARAM + 8) & (__SIZEOF_SIZE_T__ - 1))))
#else /* ((__SIZEOF_SCHED_PARAM + 8) & (__SIZEOF_SIZE_T__ - 1)) != 0 */
#define __OFFSET_PTHREAD_ATTR_GUARDSIZE   (__SIZEOF_SCHED_PARAM + 8)
#endif /* ((__SIZEOF_SCHED_PARAM + 8) & (__SIZEOF_SIZE_T__ - 1)) == 0 */
#define __OFFSET_PTHREAD_ATTR_STACKADDR   (__OFFSET_PTHREAD_ATTR_GUARDSIZE + __SIZEOF_SIZE_T__)
#define __OFFSET_PTHREAD_ATTR_STACKSIZE   (__OFFSET_PTHREAD_ATTR_GUARDSIZE + __SIZEOF_SIZE_T__ + __SIZEOF_POINTER__)
#define __OFFSET_PTHREAD_ATTR_CPUSET      (__OFFSET_PTHREAD_ATTR_GUARDSIZE + __SIZEOF_SIZE_T__ * 2 + __SIZEOF_POINTER__)
#define __OFFSET_PTHREAD_ATTR_CPUSETSIZE  (__OFFSET_PTHREAD_ATTR_GUARDSIZE + __SIZEOF_SIZE_T__ * 2 + __SIZEOF_POINTER__ * 2)
#ifdef __CC__
struct __cpu_set_struct;
typedef struct __pthread_attr_s {
	/* NOTE: This  structure shares binary compatibility with Glibc (for the most part)
	 *       The  only difference is that we allow  the re-use of `pa_cpusetsize' as an
	 *       in-line 32/64-bit cpuset, thus preventing the need to dynamically allocate
	 *       small cpu sets on the  heap when most of  the time those structures  would
	 *       only be a couple of bytes large. */
	struct sched_param       pa_schedparam;  /* [valid_if(PTHREAD_ATTR_FLAG_SCHED_SET)] Scheduler parameters and priority. */
	__INT32_TYPE__           pa_schedpolicy; /* [valid_if(PTHREAD_ATTR_FLAG_POLICY_SET)] Scheduler policy */
	__INT32_TYPE__           pa_flags;       /* Various flags like detachstate, scope, etc (Set of `PTHREAD_ATTR_FLAG_*'). */
#if ((__SIZEOF_SCHED_PARAM + 8) & (__SIZEOF_SIZE_T__ - 1)) != 0
	__BYTE_TYPE__           _pa_pad[__SIZEOF_SIZE_T__ - ((__SIZEOF_SCHED_PARAM + 8) & (__SIZEOF_SIZE_T__ - 1))];
#endif /* ((__SIZEOF_SCHED_PARAM + 8) & (__SIZEOF_SIZE_T__ - 1)) != 0 */
	__SIZE_TYPE__            pa_guardsize;   /* Size of the stack-overflow guard area. */
	void                    *pa_stackaddr;   /* [valid_if(PTHREAD_ATTR_FLAG_STACKADDR)] Stack start address. */
	__SIZE_TYPE__            pa_stacksize;   /* [valid_if(PTHREAD_ATTR_FLAG_STACKADDR)] Stack size. */
	struct __cpu_set_struct *pa_cpuset;      /* [0..pa_cpusetsize] Thread affinity set. */
	__SIZE_TYPE__            pa_cpusetsize;  /* Thread affinity set size (in bytes). */
} __pthread_attr_t;
#endif /* __CC__ */
#else /* __USE_PTHREAD_INTERNALS */
#ifdef __CC__
typedef union __pthread_attr {
	__BYTE_TYPE__   __size[__SIZEOF_PTHREAD_ATTR_T];
	__INTPTR_TYPE__ __align;
} __pthread_attr_t;
#endif /* __CC__ */
#endif /* !__USE_PTHREAD_INTERNALS */





/************************************************************************/
/* pthread_mutex_t                                                      */
/************************************************************************/
#ifdef __USE_PTHREAD_INTERNALS
#define __OFFSET_PTHREAD_MUTEXATTR_KIND 0
#define PTHREAD_MUTEXATTR_KIND_MASK          0x00000fff /* Mask for the mutex kind (one of `PTHREAD_MUTEX_*') */
#define PTHREAD_MUTEXATTR_PRIO_CEILING_SHIFT 12         /* Shift for `PTHREAD_MUTEXATTR_PRIO_CEILING_MASK' */
#define PTHREAD_MUTEXATTR_PRIO_CEILING_MASK  0x00fff000 /* Priority ceiling (unused on KOS) */
#define PTHREAD_MUTEXATTR_PROTOCOL_SHIFT     28         /* Shift for `PTHREAD_MUTEXATTR_PROTOCOL_MASK' */
#define PTHREAD_MUTEXATTR_PROTOCOL_MASK      0x30000000 /* One of `PTHREAD_PRIO_*' */
#define PTHREAD_MUTEXATTR_FLAG_ROBUST        0x40000000 /* `pthread_mutexattr_getrobust' / `pthread_mutexattr_setrobust' */
#define PTHREAD_MUTEXATTR_FLAG_PSHARED       0x80000000 /* `pthread_mutexattr_getpshared' / `pthread_mutexattr_setpshared' */
#ifdef __CC__
typedef struct __pthread_mutexattr_s {
	__UINT32_TYPE__ ma_kind; /* Mutex kind/flags (set of `PTHREAD_MUTEXATTR_*'). */
} __pthread_mutexattr_t;
#endif /* __CC__ */
#else /* __USE_PTHREAD_INTERNALS */
#ifdef __CC__
typedef union __pthread_mutexattr {
	__BYTE_TYPE__  __size[__SIZEOF_PTHREAD_MUTEXATTR_T];
	__INT32_TYPE__ __align;
} __pthread_mutexattr_t;
#endif /* __CC__ */
#endif /* !__USE_PTHREAD_INTERNALS */

#ifdef __CC__
#ifdef __PTHREAD_MUTEX_HAVE_PREV
struct __pthread_internal_list {
#ifdef __USE_PTHREAD_INTERNALS
	struct __pthread_internal_list *_l_prev; /* Unused (on KOS) */
	struct __pthread_internal_list *_l_next; /* Unused (on KOS) */
#else /* __USE_PTHREAD_INTERNALS */
	struct __pthread_internal_list *__prev;
	struct __pthread_internal_list *__next;
#endif /* !__USE_PTHREAD_INTERNALS */
};
#else /* __PTHREAD_MUTEX_HAVE_PREV */
struct __pthread_internal_slist {
#ifdef __USE_PTHREAD_INTERNALS
	struct __pthread_internal_slist *_l_next; /* Unused (on KOS) */
#else /* __USE_PTHREAD_INTERNALS */
	struct __pthread_internal_slist *__next;
#endif /* !__USE_PTHREAD_INTERNALS */
};
#endif /* !__PTHREAD_MUTEX_HAVE_PREV */

#ifdef __USE_GLIBC_BLOAT
#ifdef __PTHREAD_MUTEX_HAVE_PREV
struct __pthread_internal_list __pthread_list_t;
#else /* __PTHREAD_MUTEX_HAVE_PREV */
struct __pthread_internal_slist __pthread_slist_t;
#endif /* !__PTHREAD_MUTEX_HAVE_PREV */
#endif /* __USE_GLIBC_BLOAT */
#endif /* __CC__ */

#define __OFFSET_PTHREAD_MUTEX_LOCK      0
#define __OFFSET_PTHREAD_MUTEX_COUNT     4
#define __OFFSET_PTHREAD_MUTEX_OWNER     8
#ifdef __PTHREAD_MUTEX_HAVE_NUSERS_BEFORE_KIND
#define __OFFSET_PTHREAD_MUTEX_NUSERS    12
#define __OFFSET_PTHREAD_MUTEX_KIND      16
#else /* __PTHREAD_MUTEX_HAVE_NUSERS_BEFORE_KIND */
#define __OFFSET_PTHREAD_MUTEX_KIND      12
#define __OFFSET_PTHREAD_MUTEX_NUSERS    16
#endif /* !__PTHREAD_MUTEX_HAVE_NUSERS_BEFORE_KIND */
#define __OFFSET_PTHREAD_MUTEX_SPINS     20
#define __OFFSET_PTHREAD_MUTEX_ELISION   22
#ifdef __PTHREAD_MUTEX_HAVE_DISTINCT_LIST_AND_SPIN
#define __OFFSET_PTHREAD_MUTEX_LIST      24
#else /* __PTHREAD_MUTEX_HAVE_DISTINCT_LIST_AND_SPIN */
#define __OFFSET_PTHREAD_MUTEX_LIST      20
#endif /* !__PTHREAD_MUTEX_HAVE_DISTINCT_LIST_AND_SPIN */
#ifdef __PTHREAD_MUTEX_HAVE_PREV
#define __OFFSET_PTHREAD_MUTEX_LIST_PREV __OFFSET_PTHREAD_MUTEX_LIST
#define __OFFSET_PTHREAD_MUTEX_LIST_NEXT (__OFFSET_PTHREAD_MUTEX_LIST + __SIZEOF_POINTER__)
#else /* __PTHREAD_MUTEX_HAVE_PREV */
#define __OFFSET_PTHREAD_MUTEX_LIST_NEXT __OFFSET_PTHREAD_MUTEX_LIST
#endif /* !__PTHREAD_MUTEX_HAVE_PREV */

/* Internal mutex kind values (for `m_kind').
 * These are compatible with Glibc */
#define PTHREAD_MUTEX_KIND_MASK_NP     0x003 /* Mask for `PTHREAD_MUTEX_TIMED', `PTHREAD_MUTEX_RECURSIVE', ... */
#define PTHREAD_MUTEX_ROBUST_NORMAL_NP 0x010 /* Unused (on KOS) */
#define PTHREAD_MUTEX_PRIO_INHERIT_NP  0x020 /* Unused (on KOS) */
#define PTHREAD_MUTEX_PRIO_PROTECT_NP  0x040 /* Unused (on KOS) */
#define PTHREAD_MUTEX_PSHARED_BIT      0x080 /* Unused (on KOS) */
#define PTHREAD_MUTEX_ELISION_NP       0x100 /* Unused (on KOS) */
#define PTHREAD_MUTEX_NO_ELISION_NP    0x200 /* Unused (on KOS) */
#ifdef __CC__
struct __pthread_mutex_s {
#ifdef __USE_PTHREAD_INTERNALS
	__INT32_TYPE__   m_lock;    /* Futex control word for this mutex. (set of `FUTEX_WAITERS | FUTEX_OWNER_DIED | FUTEX_TID_MASK') */
	__UINT32_TYPE__  m_count;   /* [valid_if(PTHREAD_MUTEX_RECURSIVE)] # of (additional) recursive locks */
	__INT32_TYPE__  _m_owner;   /* Unused (on KOS) */
#ifdef __PTHREAD_MUTEX_HAVE_NUSERS_BEFORE_KIND
	__UINT32_TYPE__  _m_nusers; /* Unused (on KOS) */
#endif /* __PTHREAD_MUTEX_HAVE_NUSERS_BEFORE_KIND */
	__INT32_TYPE__   m_kind;    /* [const] The kind of this futex (set of `PTHREAD_MUTEX_*'; see above). */
#ifndef __PTHREAD_MUTEX_HAVE_NUSERS_BEFORE_KIND
	__UINT32_TYPE__  _m_nusers; /* Unused (on KOS) */
#endif /* !__PTHREAD_MUTEX_HAVE_NUSERS_BEFORE_KIND */
#ifdef __PTHREAD_MUTEX_HAVE_DISTINCT_LIST_AND_SPIN
	__INT16_TYPE__    _m_spins;   /* Unused (on KOS) */
	__INT16_TYPE__    _m_elision; /* Unused (on KOS) */
#ifdef __PTHREAD_MUTEX_HAVE_PREV
	struct __pthread_internal_list  _m_list; /* Unused (on KOS) */
#else /* __PTHREAD_MUTEX_HAVE_PREV */
	struct __pthread_internal_slist _m_list; /* Unused (on KOS) */
#endif /* !__PTHREAD_MUTEX_HAVE_PREV */
#else /* __PTHREAD_MUTEX_HAVE_DISTINCT_LIST_AND_SPIN */
	union {
#ifdef __PTHREAD_MUTEX_HAVE_PREV
		struct __pthread_internal_list  _m_list; /* Unused (on KOS) */
#else /* __PTHREAD_MUTEX_HAVE_PREV */
		struct __pthread_internal_slist _m_list; /* Unused (on KOS) */
#endif /* !__PTHREAD_MUTEX_HAVE_PREV */
		struct {
			__INT16_TYPE__ _m_spins;   /* Unused (on KOS) */
			__INT16_TYPE__ _m_elision; /* Unused (on KOS) */
		}
#ifdef __COMPILER_HAVE_TRANSPARENT_STRUCT
		;
#else /* __COMPILER_HAVE_TRANSPARENT_STRUCT */
#define _m_spins   __elision_data._m_spins   /* Unused (on KOS) */
#define _m_elision __elision_data._m_elision /* Unused (on KOS) */
		__elision_data;
#endif /* !__COMPILER_HAVE_TRANSPARENT_STRUCT */
	};
#endif /* !__PTHREAD_MUTEX_HAVE_DISTINCT_LIST_AND_SPIN */
#else /* __USE_PTHREAD_INTERNALS */
	__INT32_TYPE__   __lock;
	__UINT32_TYPE__  __count;
	__INT32_TYPE__   __owner;
#ifdef __PTHREAD_MUTEX_HAVE_NUSERS_BEFORE_KIND
	__UINT32_TYPE__  __nusers;
#endif /* __PTHREAD_MUTEX_HAVE_NUSERS_BEFORE_KIND */
	__INT32_TYPE__   __kind;
#ifndef __PTHREAD_MUTEX_HAVE_NUSERS_BEFORE_KIND
	__UINT32_TYPE__  __nusers;
#endif /* !__PTHREAD_MUTEX_HAVE_NUSERS_BEFORE_KIND */
#ifdef __PTHREAD_MUTEX_HAVE_DISTINCT_LIST_AND_SPIN
	__INT16_TYPE__    __spins;
	__INT16_TYPE__    __elision;
#ifdef __PTHREAD_MUTEX_HAVE_PREV
	struct __pthread_internal_list __list;
#else /* __PTHREAD_MUTEX_HAVE_PREV */
	struct __pthread_internal_slist __list;
#endif /* !__PTHREAD_MUTEX_HAVE_PREV */
#else /* __PTHREAD_MUTEX_HAVE_DISTINCT_LIST_AND_SPIN */
	union {
#ifdef __PTHREAD_MUTEX_HAVE_PREV
		struct __pthread_internal_list __list;
#else /* __PTHREAD_MUTEX_HAVE_PREV */
		struct __pthread_internal_slist __list;
#endif /* !__PTHREAD_MUTEX_HAVE_PREV */
		struct {
			__INT16_TYPE__ __spins;
			__INT16_TYPE__ __elision;
		}
#ifdef __COMPILER_HAVE_TRANSPARENT_STRUCT
		;
#else /* __COMPILER_HAVE_TRANSPARENT_STRUCT */
#define __spins   __elision_data.__spins
#define __elision __elision_data.__elision
		__elision_data;
#endif /* !__COMPILER_HAVE_TRANSPARENT_STRUCT */
	};
#endif /* !__PTHREAD_MUTEX_HAVE_DISTINCT_LIST_AND_SPIN */
#endif /* !__USE_PTHREAD_INTERNALS */
};

#ifdef __PTHREAD_MUTEX_HAVE_NUSERS_BEFORE_KIND
#define __PTHREAD_MUTEX_INIT_NUSERS_AND_KIND(kind) 0, kind
#else /* __PTHREAD_MUTEX_HAVE_NUSERS_BEFORE_KIND */
#define __PTHREAD_MUTEX_INIT_NUSERS_AND_KIND(kind) kind, 0
#endif /* !__PTHREAD_MUTEX_HAVE_NUSERS_BEFORE_KIND */

#ifdef __PTHREAD_MUTEX_HAVE_DISTINCT_LIST_AND_SPIN
#ifdef __PTHREAD_MUTEX_HAVE_PREV
#define __PTHREAD_MUTEX_INIT_LIST_AND_SPIN 0, 0, { __NULLPTR, __NULLPTR }
#else /* __PTHREAD_MUTEX_HAVE_PREV */
#define __PTHREAD_MUTEX_INIT_LIST_AND_SPIN 0, 0, { __NULLPTR }
#endif /* !__PTHREAD_MUTEX_HAVE_PREV */
#else /* __PTHREAD_MUTEX_HAVE_DISTINCT_LIST_AND_SPIN */
#ifdef __PTHREAD_MUTEX_HAVE_PREV
#define __PTHREAD_MUTEX_INIT_LIST_AND_SPIN { { __NULLPTR, __NULLPTR } }
#else /* __PTHREAD_MUTEX_HAVE_PREV */
#define __PTHREAD_MUTEX_INIT_LIST_AND_SPIN { { __NULLPTR } }
#endif /* !__PTHREAD_MUTEX_HAVE_PREV */
#endif /* !__PTHREAD_MUTEX_HAVE_DISTINCT_LIST_AND_SPIN */

#define __PTHREAD_MUTEX_S_INITIALIZER_EX(kind)      \
	{                                               \
		/* .__lock   = */ 0,                        \
		/* .__count  = */ 0,                        \
		/* .__owner  = */ 0,                        \
		__PTHREAD_MUTEX_INIT_NUSERS_AND_KIND(kind), \
		__PTHREAD_MUTEX_INIT_LIST_AND_SPIN          \
	}

#ifdef __USE_PTHREAD_INTERNALS
#define __PTHREAD_MUTEX_INITIALIZER_EX(kind) \
	__PTHREAD_MUTEX_S_INITIALIZER_EX(kind)
typedef struct __pthread_mutex_s __pthread_mutex_t;
#else /* __USE_PTHREAD_INTERNALS */
#define __PTHREAD_MUTEX_INITIALIZER_EX(kind) \
	{ __PTHREAD_MUTEX_S_INITIALIZER_EX(kind) }
typedef union __pthread_mutex {
	struct __pthread_mutex_s __data;
	__BYTE_TYPE__            __size[__SIZEOF_PTHREAD_MUTEX_T];
	__INTPTR_TYPE__          __align;
} __pthread_mutex_t;
#endif /* !__USE_PTHREAD_INTERNALS */

/* Static pthread_mutex_t initializers. */
#define __PTHREAD_MUTEX_INITIALIZER            __PTHREAD_MUTEX_INITIALIZER_EX(0)
#define __PTHREAD_RECURSIVE_MUTEX_INITIALIZER  __PTHREAD_MUTEX_INITIALIZER_EX(__PTHREAD_MUTEX_RECURSIVE)
#define __PTHREAD_ERRORCHECK_MUTEX_INITIALIZER __PTHREAD_MUTEX_INITIALIZER_EX(__PTHREAD_MUTEX_ERRORCHECK)
#define __PTHREAD_ADAPTIVE_MUTEX_INITIALIZER   __PTHREAD_MUTEX_INITIALIZER_EX(__PTHREAD_MUTEX_ADAPTIVE)
#endif /* __CC__ */




/************************************************************************/
/* pthread_cond_t                                                       */
/************************************************************************/
#ifdef __USE_PTHREAD_INTERNALS
#define __OFFSET_PTHREAD_CONDATTR_VALUE 0
#define PTHREAD_CONDATTR_FLAG_PSHARED  0x0001 /* Cond is shared */
#define PTHREAD_CONDATTR_CLOCKID_SHIFT 1      /* Shift for `PTHREAD_CONDATTR_CLOCKID_MASK' */
#define PTHREAD_CONDATTR_CLOCKID_MASK  0xfffe /* The clock id */
#ifdef __CC__
typedef struct __pthread_condattr_s {
	__UINT32_TYPE__ ca_value; /* Set of `PTHREAD_CONDATTR_*' */
} __pthread_condattr_t;
#endif /* __CC__ */
#else /* __USE_PTHREAD_INTERNALS */
#ifdef __CC__
typedef union __pthread_condattr {
	__BYTE_TYPE__  __size[__SIZEOF_PTHREAD_CONDATTR_T];
	__INT32_TYPE__ __align;
} __pthread_condattr_t;
#endif /* __CC__ */
#endif /* !__USE_PTHREAD_INTERNALS */

#define __OFFSET_PTHREAD_COND_LOCK          0
#define __OFFSET_PTHREAD_COND_FUTEX         4
#define __OFFSET_PTHREAD_COND_TOTAL_SEQ     8
#define __OFFSET_PTHREAD_COND_WAKEUP_SEQ    16
#define __OFFSET_PTHREAD_COND_WOKEN_SEQ     24
#define __OFFSET_PTHREAD_COND_MUTEX         32
#define __OFFSET_PTHREAD_COND_NWAITERS      (32 + __SIZEOF_POINTER__)
#define __OFFSET_PTHREAD_COND_BROADCAST_SEQ (36 + __SIZEOF_POINTER__)
#ifdef __CC__
struct __pthread_cond_s {
#ifdef __USE_PTHREAD_INTERNALS
	__INT32_TYPE__            _c_lock;          /* Unused (on KOS) */
	__UINT32_TYPE__            c_futex;         /* Futex control word & condition-version counter. */
	__UINT64_TYPE__           _c_total_seq;     /* Unused (on KOS) */
	__UINT64_TYPE__           _c_wakeup_seq;    /* Unused (on KOS) */
	__UINT64_TYPE__           _c_woken_seq;     /* Unused (on KOS) */
	struct __pthread_mutex_s *_c_mutex;         /* Unused (on KOS) */
	__UINT32_TYPE__           _c_nwaiters;      /* Unused (on KOS) */
	__UINT32_TYPE__           _c_broadcast_seq; /* Unused (on KOS) */
#else /* __USE_PTHREAD_INTERNALS */
	__INT32_TYPE__  __lock;
	__UINT32_TYPE__ __futex;
	__UINT64_TYPE__ __total_seq;
	__UINT64_TYPE__ __wakeup_seq;
	__UINT64_TYPE__ __woken_seq;
	void           *__mutex;
	__UINT32_TYPE__ __nwaiters;
	__UINT32_TYPE__ __broadcast_seq;
#endif /* !__USE_PTHREAD_INTERNALS */
};
#define __PTHREAD_COND_S_INITIALIZER \
	{ 0, 0, 0, 0, 0, (void *)0, 0, 0 }

/* Static pthread_cond_t initializers. */
#ifdef __USE_PTHREAD_INTERNALS
#define __PTHREAD_COND_INITIALIZER __PTHREAD_COND_S_INITIALIZER
typedef struct __pthread_cond_s __pthread_cond_t;
#else /* __USE_PTHREAD_INTERNALS */
#define __PTHREAD_COND_INITIALIZER { __PTHREAD_COND_S_INITIALIZER }
typedef union __pthread_cond {
	struct __pthread_cond_s __data;
	__BYTE_TYPE__           __size[__SIZEOF_PTHREAD_COND_T];
	__INT64_TYPE__          __align;
} __pthread_cond_t;
#endif /* !__USE_PTHREAD_INTERNALS */
#endif /* __CC__ */



/************************************************************************/
/* pthread_rwlock_t                                                     */
/************************************************************************/
#ifdef __USE_PTHREAD_INTERNALS
#define __OFFSET_PTHREAD_RWLOCKATTR_KIND   0
#define __OFFSET_PTHREAD_RWLOCKATTR_SHARED 4
#ifdef __CC__
typedef struct __pthread_rwlockattr_s {
	__UINT32_TYPE__ rwa_kind;   /* What will eventually become the r/w-lock's flags */
	__UINT32_TYPE__ rwa_shared; /* Non-zero if the r/w-lock is shared */
} __pthread_rwlockattr_t;
#endif /* __CC__ */
#else /* __USE_PTHREAD_INTERNALS */
#ifdef __CC__
typedef union __pthread_rwlockattr {
	__BYTE_TYPE__   __size[__SIZEOF_PTHREAD_RWLOCKATTR_T];
	__INTPTR_TYPE__ __align;
} __pthread_rwlockattr_t;
#endif /* __CC__ */
#endif /* !__USE_PTHREAD_INTERNALS */

#ifdef __USE_PTHREAD_INTERNALS
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define __OFFSET_PTHREAD_RWLOCK_LOCK              0
#define __OFFSET_PTHREAD_RWLOCK_NR_READERS        4
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#define __OFFSET_PTHREAD_RWLOCK_LOCK              4
#define __OFFSET_PTHREAD_RWLOCK_NR_READERS        0
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
#define __OFFSET_PTHREAD_RWLOCK_READERS_WAKEUP    8
#define __OFFSET_PTHREAD_RWLOCK_WRITER_WAKEUP     12
#define __OFFSET_PTHREAD_RWLOCK_NR_WRITERS        16
#define __OFFSET_PTHREAD_RWLOCK_NR_WRITERS_QUEUED 20

#ifndef __OFFSET_PTHREAD_RWLOCK_FLAGS
#define __OFFSET_PTHREAD_RWLOCK_FLAGS 24
#endif /* !__OFFSET_PTHREAD_RWLOCK_FLAGS */
#ifndef __OFFSET_PTHREAD_RWLOCK_SHARED
#define __OFFSET_PTHREAD_RWLOCK_SHARED 25
#endif /* !__OFFSET_PTHREAD_RWLOCK_SHARED */
#ifndef __OFFSET_PTHREAD_RWLOCK_RWELISION
#define __OFFSET_PTHREAD_RWLOCK_RWELISION 26
#endif /* !__OFFSET_PTHREAD_RWLOCK_RWELISION */
#ifndef __OFFSET_PTHREAD_RWLOCK_WRITER
#define __OFFSET_PTHREAD_RWLOCK_WRITER 28
#endif /* !__OFFSET_PTHREAD_RWLOCK_WRITER */
#endif /* __USE_PTHREAD_INTERNALS */

#ifdef __CC__
struct __pthread_rwlock_s {
#ifdef __USE_PTHREAD_INTERNALS
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	__INT32_TYPE__   rw_lock;              /* s.a. `struct shared_rwlock::sl_lock' */
	__UINT32_TYPE__ _rw_nr_readers;        /* Unused (on KOS) */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	__UINT32_TYPE__ _rw_nr_readers;        /* Unused (on KOS) */
	__INT32_TYPE__   rw_lock;              /* s.a. `struct shared_rwlock::sl_lock' */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
	__UINT32_TYPE__  rw_readers_wakeup;    /* s.a. `struct shared_rwlock::sl_rdwait' */
	__UINT32_TYPE__  rw_writer_wakeup;     /* s.a. `struct shared_rwlock::sl_wrwait' */
	__UINT32_TYPE__  rw_nr_writers;        /* Write-lock recursion under `PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP' */
	__UINT32_TYPE__ _rw_nr_writers_queued; /* Unused (on KOS) */
#else /* __USE_PTHREAD_INTERNALS */
	__INT32_TYPE__   __lock;
	__UINT32_TYPE__  __nr_readers;
	__UINT32_TYPE__  __readers_wakeup;
	__UINT32_TYPE__  __writer_wakeup;
	__UINT32_TYPE__  __nr_readers_queued;
	__UINT32_TYPE__  __nr_writers_queued;
#endif /* !__USE_PTHREAD_INTERNALS */
#if __OFFSET_PTHREAD_RWLOCK_WRITER == __OFFSET_PTHREAD_RWLOCK_NR_WRITERS_QUEUED + 4
#define __PTHREAD_RWLOCK_S_INITIALIZER_EX(flags) \
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, { 0 }, flags }
#ifdef __USE_PTHREAD_INTERNALS
	__INT32_TYPE__   rw_writer;    /* TID of the writing thread */
	__INT32_TYPE__  _rw_shared;    /* Unused (on KOS) */
	__INT8_TYPE__   _rw_rwelision; /* Unused (on KOS) */
	__UINT8_TYPE__  _rw_pad1[__OFFSET_PTHREAD_RWLOCK_FLAGS - (__OFFSET_PTHREAD_RWLOCK_RWELISION + 1)];
	__UINT32_TYPE__  rw_flags;     /* One of `PTHREAD_RWLOCK_PREFER_*' */
#else /* __USE_PTHREAD_INTERNALS */
	__INT32_TYPE__   __writer;
	__INT32_TYPE__   __shared;
	__INT8_TYPE__    __rwelision;
	__UINT8_TYPE__   __pad1[__OFFSET_PTHREAD_RWLOCK_FLAGS - (__OFFSET_PTHREAD_RWLOCK_RWELISION + 1)];
	__UINT32_TYPE__  __flags;
#endif /* !__USE_PTHREAD_INTERNALS */
#else /* __OFFSET_PTHREAD_RWLOCK_WRITER == __OFFSET_PTHREAD_RWLOCK_NR_WRITERS_QUEUED + 4 */
#define __PTHREAD_RWLOCK_S_INITIALIZER_EX(flags) \
	{ 0, 0, 0, 0, 0, 0, flags, 0, 0, 0, 0 }
#ifdef __USE_PTHREAD_INTERNALS
	__UINT8_TYPE__   rw_flags;     /* [const] Non-zero if `PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP' */
	__UINT8_TYPE__  _rw_shared;    /* Unused (on KOS) */
	__INT8_TYPE__   _rw_rwelision; /* Unused (on KOS) */
	__UINT8_TYPE__  _rw_pad1;      /* ... */
	__INT32_TYPE__   rw_writer;    /* [valid_if(rw_lock == UINT32_MAX)] TID of the writing thread */
#else /* __USE_PTHREAD_INTERNALS */
	__UINT8_TYPE__  __flags;
	__UINT8_TYPE__  __shared;
	__INT8_TYPE__   __rwelision;
	__UINT8_TYPE__  __pad1;
	__INT32_TYPE__  __writer;
#endif /* !__USE_PTHREAD_INTERNALS */
#endif /* __OFFSET_PTHREAD_RWLOCK_WRITER != __OFFSET_PTHREAD_RWLOCK_NR_WRITERS_QUEUED + 4 */
};

#ifdef __USE_PTHREAD_INTERNALS
#define __PTHREAD_RWLOCK_INITIALIZER_EX(flags) __PTHREAD_RWLOCK_S_INITIALIZER_EX(flags)
typedef struct __pthread_rwlock_s __pthread_rwlock_t;
#else /* __USE_PTHREAD_INTERNALS */
#define __PTHREAD_RWLOCK_INITIALIZER_EX(flags) \
	{ __PTHREAD_RWLOCK_S_INITIALIZER_EX(flags) }
typedef union __pthread_rwlock {
	struct __pthread_rwlock_s __data;
	__BYTE_TYPE__             __size[__SIZEOF_PTHREAD_RWLOCK_T];
	__INTPTR_TYPE__           __align;
} __pthread_rwlock_t;
#endif /* !__USE_PTHREAD_INTERNALS */

/* Static pthread_rwlock_t initializers. */
#define __PTHREAD_RWLOCK_INITIALIZER \
	__PTHREAD_RWLOCK_INITIALIZER_EX(0)
#define __PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER \
	__PTHREAD_RWLOCK_INITIALIZER_EX(__PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE)
#endif /* __CC__ */



/************************************************************************/
/* pthread_spinlock_t                                                   */
/************************************************************************/
#ifdef __CC__
typedef __TYPEFOR_INTIB(__SIZEOF_PTHREAD_SPINLOCK_T) volatile __pthread_spinlock_t;
#endif /* __CC__ */



/************************************************************************/
/* pthread_marrier_t                                                    */
/************************************************************************/
#ifdef __USE_PTHREAD_INTERNALS
#define __OFFSET_PTHREAD_BARRIERATTR_PSHARED 0
#ifdef __CC__
typedef struct __pthread_barrierattr_s {
	__UINT32_TYPE__ ba_pshared; /* One of `PTHREAD_PROCESS_PRIVATE', `PTHREAD_PROCESS_SHARED' */
} __pthread_barrierattr_t;
#endif /* __CC__ */
#else /* __USE_PTHREAD_INTERNALS */
#ifdef __CC__
typedef union __pthread_barrierattr {
	__BYTE_TYPE__  __size[__SIZEOF_PTHREAD_BARRIERATTR_T];
	__INT32_TYPE__ __align;
} __pthread_barrierattr_t;
#endif /* __CC__ */
#endif /* !__USE_PTHREAD_INTERNALS */

#ifdef __USE_PTHREAD_INTERNALS
#define __OFFSET_PTHREAD_BARRIER_IN            0
#define __OFFSET_PTHREAD_BARRIER_CURRENT_ROUND 4
#define __OFFSET_PTHREAD_BARRIER_COUNT         8
#define __OFFSET_PTHREAD_BARRIER_SHARED        12
#define __OFFSET_PTHREAD_BARRIER_OUT           16
#ifdef __CC__
typedef struct __pthread_barrier_s {
	__UINT32_TYPE__ b_in;            /* # of threads currently waiting at the barrier */
	__UINT32_TYPE__ b_current_round; /* Incremented every time `b_in' is broadcast (also the futex broadcast for wake-up) */
	__UINT32_TYPE__ b_count;         /* [const] # of threads that have to reach the barrier */
	__UINT32_TYPE__ b_shared;        /* [const] Non-zero if shared */
	__UINT32_TYPE__ b_out;           /* ??? */
} __pthread_barrier_t;
#endif /* __CC__ */
#else /* __USE_PTHREAD_INTERNALS */
#ifdef __CC__
typedef union __pthread_barrier {
	__BYTE_TYPE__   __size[__SIZEOF_PTHREAD_BARRIER_T];
	__INTPTR_TYPE__ __align;
} __pthread_barrier_t;
#endif /* __CC__ */
#endif /* !__USE_PTHREAD_INTERNALS */

__DECL_END

#endif /* !_BITS_CRT_PTHREADTYPES_H */
