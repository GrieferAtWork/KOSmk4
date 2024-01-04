/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODRTM_MEMORY_H
#define GUARD_MODRTM_MEMORY_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/group.h>
#include <sched/rpc.h>

#include <hybrid/__assert.h>

#include "rtm.h"

/*[[[config CONFIG_MODRTM_FAR_REGIONS = true
 * >> Config option: CONFIG_MODRTM_FAR_REGIONS
 * When enabled, so-called far regions can be made use of that
 * can alias the data parts of adjacent memory regions without
 * having to load all memory in-between accessed locations.
 * ]]]*/
#ifdef CONFIG_NO_MODRTM_FAR_REGIONS
#undef CONFIG_MODRTM_FAR_REGIONS
#elif !defined(CONFIG_MODRTM_FAR_REGIONS)
#define CONFIG_MODRTM_FAR_REGIONS
#elif (-CONFIG_MODRTM_FAR_REGIONS - 1) == -1
#undef CONFIG_MODRTM_FAR_REGIONS
#define CONFIG_NO_MODRTM_FAR_REGIONS
#endif /* ... */
/*[[[end]]]*/


#ifdef CONFIG_MODRTM_FAR_REGIONS
/*[[[config CONFIG_MODRTM_FAR_REGION_CREATION_THRESHOLD! = 64
 * Threshold: Create far regions if the alternative require at  least
 *            this  many bytes  of memory  to be  loaded, that hadn't
 *            actually been required by the user up until this point.
 * ]]]*/
#ifndef CONFIG_MODRTM_FAR_REGION_CREATION_THRESHOLD
#define CONFIG_MODRTM_FAR_REGION_CREATION_THRESHOLD 64
#endif /* !CONFIG_MODRTM_FAR_REGION_CREATION_THRESHOLD */
/*[[[end]]]*/

/*[[[config CONFIG_MODRTM_FAR_REGION_REMERGE: bool = !defined(__OPTIMIZE_SIZE__)
 * When defined as non-zero, re-merge far regions
 * if/when they end up running into each other.
 * ]]]*/
#ifdef CONFIG_NO_MODRTM_FAR_REGION_REMERGE
#undef CONFIG_MODRTM_FAR_REGION_REMERGE
#elif !defined(CONFIG_MODRTM_FAR_REGION_REMERGE)
#ifndef __OPTIMIZE_SIZE__
#define CONFIG_MODRTM_FAR_REGION_REMERGE
#else /* !__OPTIMIZE_SIZE__ */
#define CONFIG_NO_MODRTM_FAR_REGION_REMERGE
#endif /* __OPTIMIZE_SIZE__ */
#elif (-CONFIG_MODRTM_FAR_REGION_REMERGE - 1) == -1
#undef CONFIG_MODRTM_FAR_REGION_REMERGE
#define CONFIG_NO_MODRTM_FAR_REGION_REMERGE
#endif /* ... */
/*[[[end]]]*/
#endif /* CONFIG_MODRTM_FAR_REGIONS */


DECL_BEGIN

struct rtm_memory_region {
	void                           *mr_addrlo; /* Lowest region address. (1-byte granularity) */
	void                           *mr_addrhi; /* Greatest region address. */
	REF /*struct mpart*/void       *mr_part;   /* [1..1] The mpart used for backing this region.
	                                            * NOTE: The least significant 2 bits has special use. */
	uintptr_t                       mr_vers;   /* Region RTM version before the initial read. */
	COMPILER_FLEXIBLE_ARRAY(byte_t, mr_data);  /* [rtm_memory_region_getsize(self)] Cached RTM region data. */
};
#define rtm_memory_region_getsize(self)     ((size_t)((byte_t *)(self)->mr_addrhi - (byte_t *)(self)->mr_addrlo) + 1)
#define rtm_memory_region_getpart(self)     ((struct mpart *)((uintptr_t)(self)->mr_part & ~3))
#define RTM_MEMORY_REGION_CHANGED_FLAG      1 /* Flag for `mr_part': was changed */
#define rtm_memory_region_waschanged(self)  (((uintptr_t)(self)->mr_part & 1) != 0)
#define rtm_memory_region_setchanged(self)  (void)((self)->mr_part = (void *)((uintptr_t)(self)->mr_part | 1))
#ifdef CONFIG_MODRTM_FAR_REGIONS
/* Far regions can be used to describe holes between RTM memory regions that don't have to
 * be  loaded  into  memory  when  data  from  both  ends  has  been  accessed.   However,
 * NOTE: Far  regions can only be marked as changed when the adjacent base region has also
 *       been marked as changed. Alternatively, when the far region is the first one to be
 *       modified,  then the base region can be turned into the far region, and what would
 *       originally have been a far region can become a base region.
 * NOTE: The `mr_vers' value of a far region must be equal to the `mr_vers' of the adjacent
 *       base region. */
#define RTM_MEMORY_REGION_ISFARREGION_FLAG  2 /* Flag for `mr_part': far region */
#define rtm_memory_region_isfarregion(self) (((uintptr_t)(self)->mr_part & 2) != 0)
#define rtm_memory_region_waschanged_and_no_farregion(self) (((uintptr_t)(self)->mr_part & 3) == 1)
#else /* CONFIG_MODRTM_FAR_REGIONS */
#define rtm_memory_region_waschanged_and_no_farregion(self) rtm_memory_region_waschanged(self)
#endif /* !CONFIG_MODRTM_FAR_REGIONS */



#ifdef CONFIG_MODRTM_PENDING_SYSTEM_CALLS
#define RTM_PENDING_SYSCALL_NONE   0x0000 /* No system call (never used) */
#define RTM_PENDING_SYSCALL_SYSLOG 0x0001 /* Pending call to `sys_syslog()' (`rps_data' is the syslog level) */

struct rtm_pending_syscall {
	uintptr_half_t rps_kind; /* System call kind (one of `RTM_PENDING_SYSCALL_*') */
	uintptr_half_t rps_data; /* System-call-kind-specific data. */
	union {
		struct {
			char   *rps_text;  /* [1..rps_size][owned] The text that's supposed to be printed. */
			size_t  rps_size;  /* [!0] Length of `rps_text' (in characters) */
		} rps_syslog; /* RTM_PENDING_SYSCALL_SYSLOG */
	};
};
#endif /* CONFIG_MODRTM_PENDING_SYSTEM_CALLS */



struct rtm_memory {
	size_t                      rm_mem_avl; /* Amount of heap memory that is still available */
	size_t                      rm_regionc; /* # of elements from `rm_regionv' that are currently in use. */
	struct rtm_memory_region  **rm_regionv; /* [1..1][owned][0..rm_regionc][owned]  Vector  of  in-use  memory   regions.
	                                         * Sorted  ascendingly by `mr_addrlo',  meaning that an  bsearch with a worst
	                                         * case  lookup time of  O(log2(n)) can be used  for locating specific memory
	                                         * regions. (though in practice, most programs will only ever use 2  regions:
	                                         * one for the calling program's stack, and the other for the parts of memory
	                                         * that the program is actually intending to modify) */
#ifdef CONFIG_MODRTM_PENDING_SYSTEM_CALLS
	size_t                      rm_sysc;    /* # of pending system calls. */
	struct rtm_pending_syscall *rm_sysv;    /* [0..rm_sysc][owned] Vector of pending system calls. */
#endif /* CONFIG_MODRTM_PENDING_SYSTEM_CALLS */
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
	bool                        rm_chkuser; /* [const] When true, verify  that `addr' doesn't  point into  kernel-space
	                                         * as part of the execution of `rtm_memory_read()' and `rtm_memory_write()'
	                                         * before constructing a new, or  extending an existing RTM memory  region. */
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
};

/* Max  amount of kernel heap memory that may be used by
 * a single instance of a `struct rtm_memory' structure. */
INTDEF size_t rtm_memory_limit;


#ifdef CONFIG_MODRTM_PENDING_SYSTEM_CALLS
#define _RTM_MEMBER_INIT_SYSV , 0, __NULLPTR
#define _rtm_member_init_sysv(self) \
	, (self)->rm_sysc = 0,          \
	  (self)->rm_sysv = __NULLPTR
#define _rtm_member_cinit_sysv(self)         \
	, __hybrid_assert((self)->rm_sysc == 0), \
	__hybrid_assert((self)->rm_sysv == __NULLPTR)
#else /* CONFIG_MODRTM_PENDING_SYSTEM_CALLS */
#define _RTM_MEMBER_INIT_SYSV        /* nothing */
#define _rtm_member_init_sysv(self)  /* nothing */
#define _rtm_member_cinit_sysv(self) /* nothing */
#endif /* !CONFIG_MODRTM_PENDING_SYSTEM_CALLS */


/* Initialize a given `struct rtm_memory' */
#ifndef CONFIG_MODRTM_USERSPACE_ONLY
#define RTM_MEMORY_INIT(chkuser) { rtm_memory_limit, 0, __NULLPTR _RTM_MEMBER_INIT_SYSV, chkuser }
#define rtm_memory_init(self, chkuser)      \
	((self)->rm_mem_avl = rtm_memory_limit, \
	 (self)->rm_regionc = 0,                \
	 (self)->rm_regionv = __NULLPTR         \
	 _rtm_member_init_sysv(self),           \
	 (self)->rm_chkuser = (chkuser))
#define rtm_memory_cinit(self, chkuser)               \
	(__hybrid_assert((self)->rm_mem_avl == 0),        \
	 __hybrid_assert((self)->rm_regionc == 0),        \
	 __hybrid_assert((self)->rm_regionv == __NULLPTR) \
	 _rtm_member_cinit_sysv(self),                    \
	 (self)->rm_mem_avl = rtm_memory_limit,           \
	 (self)->rm_chkuser = (chkuser))
#else /* !CONFIG_MODRTM_USERSPACE_ONLY */
#define RTM_MEMORY_INIT(chkuser) { rtm_memory_limit, 0, __NULLPTR _RTM_MEMBER_INIT_SYSV }
#define rtm_memory_init(self, chkuser)      \
	((self)->rm_mem_avl = rtm_memory_limit, \
	 (self)->rm_regionc = 0,                \
	 (self)->rm_regionv = __NULLPTR         \
	 _rtm_member_init_sysv(self))
#define rtm_memory_cinit(self, chkuser)               \
	(__hybrid_assert((self)->rm_mem_avl == 0),        \
	 __hybrid_assert((self)->rm_regionc == 0),        \
	 __hybrid_assert((self)->rm_regionv == __NULLPTR) \
	 _rtm_member_cinit_sysv(self),                    \
	 (self)->rm_mem_avl = rtm_memory_limit)
#endif /* CONFIG_MODRTM_USERSPACE_ONLY */

/* Finalize a given `struct rtm_memory' */
INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL rtm_memory_fini)(struct rtm_memory *__restrict self);

/* Read RTM memory.
 * @throw: E_SEGFAULT: Faulty `addr', or `addr' points into a VIO mapping.
 * @throw: E_BADALLOC: Not enough memory, or `rtm_memory_limit' has been reached. */
INTDEF NONNULL((1, 3)) void FCALL
rtm_memory_read(struct rtm_memory *__restrict self, NCX void const *addr,
                void *__restrict buf, size_t num_bytes)
		THROWS(E_BADALLOC, E_SEGFAULT);

/* Write RTM memory.
 * @throw: E_SEGFAULT: Faulty `addr', or `addr' points into a VIO mapping.
 * @throw: E_BADALLOC: Not enough memory, or `rtm_memory_limit' has been reached. */
INTDEF NONNULL((1, 3)) void FCALL
rtm_memory_write(struct rtm_memory *__restrict self, NCX void *addr,
                 void const *__restrict buf, size_t num_bytes)
		THROWS(E_BADALLOC, E_SEGFAULT);

/* Atomically verify RTM version integrity, as well as apply RTM memory modifications.
 * @return: true:  Memory successfully applied
 * @return: false: Version of memory inconsistency detected (try again) */
INTDEF NONNULL((1)) bool FCALL
rtm_memory_apply(struct rtm_memory const *__restrict self);



/* A certain (small) set of system calls can actually be performed whilst in RTM mode:
 *
 *  - sys_rtm_begin: Nested RTM  block (simply  increments a  counter, such  that  +1
 *                   additional `sys_rtm_end()' are needed in order to exit RTM mode)
 *  - sys_rtm_end:   Exit RTM mode with a success status
 *  - sys_rtm_abort: Abort RTM with an error code
 *  - sys_rtm_test:  Always returns `1'
 *
 * Additionally, the following system calls can be used, though some with somewhat
 * altered  behavior to  prevent any  possible modifications  from being performed
 * immediately, instead causing them to be done at a later point in time.
 *
 * #ifdef CONFIG_MODRTM_PENDING_SYSTEM_CALLS
 *  - sys_syslog:      Remember  arguments,  and copy  the  to-be printed  string  into a
 *                     buffer for pending system call operations that is stored alongside
 *                     the current `struct rtm_memory', to-be printed (in order) after  a
 *                     successful completion of RTM emulation.
 *                     The return value always indicates success (any error is instead
 *                     handled as an RTM abort reason)
 * #endif // CONFIG_MODRTM_PENDING_SYSTEM_CALLS
 *  - sys_rpc_service: Normal behavior
 *  - sys_gettid:      Normal behavior
 *  - sys_getpid:      Normal behavior
 *  - sys_sched_yield: Normal behavior
 *
 * XXX:
 *  - sys_sigprocmask() - Allow for atomic signal mask modifications (needed by `sys_sigreturn()')
 *  - sys_sigreturn()   - Allow RTM to be entered in signal handlers,
 *                        and left after the signal handler returns.
 *                        Only allowed with a NULL-sc_info  argument
 */
#ifdef CONFIG_MODRTM_PENDING_SYSTEM_CALLS

/* Schedule   a  pending  call  to  `sys_syslog()',  to-be  executed
 * unconditionally just before a true-return of `rtm_memory_apply()' */
INTDEF NONNULL((1)) void FCALL
rtm_memory_schedule_sys_syslog(struct rtm_memory *__restrict self,
                               syscall_ulong_t level,
                               NCX char const *str, size_t len);
#define rtm_sys_syslog(mem, level, str, len) \
	(rtm_memory_schedule_sys_syslog(mem, level, str, len), (ssize_t)(len))
#endif /* CONFIG_MODRTM_PENDING_SYSTEM_CALLS */
#define rtm_sys_rpc_serve(mem) (task_serve() ? 1 : 0)
#define rtm_sys_gettid(mem)    task_gettid()
#define rtm_sys_getpid(mem)    task_getpid()


/* This  ~could~  be  emulated,  but  that's  actually  not  a  good  idea:
 * If the RTM code decides to call some sub-system that makes use of atomic
 * locks, then we might end up emulating code like this:
 * >> while (!try_lock())
 * >>     sched_yield();
 * The problem here is that if try_lock() failed the first time around, then
 * it will most definitely keep on failing since during the second time, the
 * memory  that is used  for backing the lock's  is-acquired state will have
 * been cached in the  RTM memory controller, such  that even if some  other
 * thread  ends up releasing the lock while our thread is still in RTM mode,
 * we may not  necessarily get  to see  this when  it happens  since RTM  is
 * designed  to only read from any memory  location once, in order to ensure
 * a consistent memory view (such that  any modifications made to memory  by
 * other threads are hidden until the very end when memory is synced)
 *
 * As such, sys_sched_yield() is actually a very important marker to indicate
 * that RTM _should_ be aborted!
 */
#if 0
#define rtm_sys_sched_yield(mem) (task_yield(), 0)
#endif




DECL_END

#endif /* !GUARD_MODRTM_MEMORY_H */
