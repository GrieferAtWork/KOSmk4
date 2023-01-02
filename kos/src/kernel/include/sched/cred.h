/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_CRED_H
#define GUARD_KERNEL_INCLUDE_SCHED_CRED_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/arch/cred.h>
#include <sched/pertask.h>

#include <hybrid/__atomic.h>
#include <hybrid/sched/atomic-rwlock.h>

#include <kos/aref.h>
#include <kos/capability.h>


/* ===== How the whole CAP_* system works on linux (and KOS) =====
 * - r/e/s-uid/gid ???
 * - caps.permitted     -- Capabilities that can be acquired by anyone, at any time
 * - caps.inheritable   -- Capabilities that ~can~ be inherited by privileged programs during exec()
 * - caps.effective     -- Capabilities current in effect
 * - caps.bounding      -- - Caps that can be made permitted by privileged programs
 *                         - Caps that can be added to `caps.inheritable' by `capset()'
 * - caps.ambient       -- Capabilities that always become permitted in privileged programs during exec()
 *                         Note the invariant that this one is always a subset of permitted & inheritable
 *
 * Invariants:
 *   - caps.ambient   SUBSET (caps.permitted & caps.inheritable)
 *   - caps.effective SUBSET caps.permitted
 *
 * exec():
 *   >> new_caps = old_caps;
 *   >> new_euid = geteuid();
 *   >> new_egid = getegid();
 *   >> bool isuid = !no_new_privs && (stat.st_mode & S_ISUID) && !(FILE_SUPERBLOCK_MOUNT_FLAGS & MS_NOSUID);
 *   >> bool isgid = !no_new_privs && (stat.st_mode & (S_ISGID | S_IXGRP)) == (S_ISGID | S_IXGRP) && !(FILE_SUPERBLOCK_MOUNT_FLAGS & MS_NOSUID);
 *   >> if (isuid)
 *   >>     new_euid = stat.st_uid;
 *   >> if (isgid)
 *   >>     new_egid = stat.st_gid;
 *   >> if (isuid || isgid)
 *   >>     new_caps.ambient = 0;
 *   >> if ((ruid == 0 || new_euid == 0) && !(securebits & SECBIT_NOROOT)) {
 *   >>     new_caps.permitted = old_caps.inheritable | caps.bounding;
 *   >>     new_caps.effective = new_caps.permitted;
 *   >> } else {
 *   >>     file_caps = 0;
 *   >>     if (FILE_HAS_ATTRIBTE("security.capability") && !KERNEL_WAS_BOOTED_WITH("no_file_caps")) {
 *   >>         file_caps = DECODE_FILE_CAPABILITIES("security.capability");
 *   >>         new_caps.ambient = 0;
 *   >>     }
 *   >>     new_caps.permitted = (old_caps.inheritable & file_caps.inheritable) |
 *   >>                          (caps.bounding & file_caps.permitted) |
 *   >>                          (new_caps.ambient);
 *   >>     new_caps.effective = file_caps.is_effective ? new_caps.permitted : new_caps.ambient;
 *   >> }
 *
 * setuid(), setfsuid(), setresuid():
 *   >> if (!capable(CAP_SETUID))
 *   >>     ERROR(); // Noop if IDs wouldn't have changed...
 *   >> if (!(securebits & SECBIT_NO_SETUID_FIXUP)) {
 *   >>     if (((old_ruid == 0) || (old_euid == 0) || (old_suid == 0)) &&
 *   >>         ((new_ruid != 0) && (new_euid != 0) && (new_suid != 0))) {
 *   >>         if (!(securebits & SECBIT_KEEP_CAPS))
 *   >>             caps.permitted = EMPTY;
 *   >>         caps.effective = EMPTY;
 *   >>         caps.ambient   = EMPTY;
 *   >>     } else {
 *   >>         if (old_euid == 0 && new_euid != 0) {
 *   >>             caps.effective = EMPTY;
 *   >>         } else if (old_euid != 0 && new_euid == 0) {
 *   >>             caps.effective = caps.permitted;
 *   >>         }
 *   >>     }
 *   >>     if (old_fsuid == 0 && new_fsuid != 0) {
 *   >>         caps.effective \= {
 *   >>             CAP_CHOWN, CAP_DAC_OVERRIDE, CAP_DAC_READ_SEARCH, CAP_FOWNER,
 *   >>             CAP_FSETID, CAP_LINUX_IMMUTABLE, CAP_MAC_OVERRIDE, CAP_MKNOD };
 *   >>     } else if (old_fsuid != 0 && new_fsuid == 0) {
 *   >>         caps.effective |= caps.permitted & {
 *   >>             CAP_CHOWN, CAP_DAC_OVERRIDE, CAP_DAC_READ_SEARCH, CAP_FOWNER,
 *   >>             CAP_FSETID, CAP_LINUX_IMMUTABLE, CAP_MAC_OVERRIDE, CAP_MKNOD };
 *   >>     }
 *   >> }
 *   >> caps.ruid  = new_ruid;
 *   >> caps.euid  = new_euid;
 *   >> caps.suid  = new_suid;
 *   >> caps.fsuid = new_fsuid;
 *
 * setgid(), setfsgid(), setresgid(), setgroups():
 *   >> if (!capable(CAP_SETGID))
 *   >>     ERROR(); // Noop if IDs wouldn't have changed...
 *   >> // Changing GIDs doesn't affect cap bitsets.
 *   >> caps.rgid   = new_rgid;
 *   >> caps.egid   = new_egid;
 *   >> caps.sgid   = new_sgid;
 *   >> caps.fsgid  = new_fsgid;
 *   >> caps.groups = new_groups;
 *
 * capset():
 *   >> if (!capable(CAP_SETPCAP))
 *   >>     assert(new_caps.inheritable SUBSET (old_caps.inheritable | old_caps.permitted));
 *   >> assert(new_caps.inheritable SUBSET (old_caps.inheritable | caps.bounding));
 *   >> assert(new_caps.permitted SUBSET old_caps.permitted);
 *   >> assert(new_caps.effective SUBSET new_caps.permitted);
 *   >> caps.inheritable = new_caps.inheritable;
 *   >> caps.permitted   = new_caps.permitted;
 *   >> caps.effective   = new_caps.effective;
 *   >> caps.ambient    &= (caps.permitted & caps.inheritable);
 *
 * prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE):
 *   >> if (securebits & SECBIT_NO_CAP_AMBIENT_RAISE)
 *   >>     ERROR();
 *   >> if (cap !IN caps.permitted || cap !IN caps.inheritable)
 *   >>     ERROR();
 *   >> caps.ambient |= | { cap };
 *
 * prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_LOWER):
 *   >> caps.ambient \= { cap };
 *
 * prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_CLEAR_ALL):
 *   >> caps.ambient = 0;
 *
 * prctl(PR_CAPBSET_DROP):
 *   >> if (!capable(CAP_ALLOW_PR_CAPBSET_DROP = CAP_SETPCAP))
 *   >>     ERROR();
 *   >> caps.bounding \= { cap };
 *
 * prctl(PR_SET_SECUREBITS):
 *   >> if (!capable(CAP_ALLOW_PR_SET_SECUREBITS = CAP_SETPCAP))
 *   >>     ERROR();
 *   >> securebits = value;
 *
 */


/*[[[config CONFIG_KERNEL_EVERYONE_IS_ROOT = false]]]*/
#ifdef CONFIG_NO_KERNEL_EVERYONE_IS_ROOT
#undef CONFIG_KERNEL_EVERYONE_IS_ROOT
#elif !defined(CONFIG_KERNEL_EVERYONE_IS_ROOT)
#define CONFIG_NO_KERNEL_EVERYONE_IS_ROOT
#elif (-CONFIG_KERNEL_EVERYONE_IS_ROOT - 1) == -1
#undef CONFIG_KERNEL_EVERYONE_IS_ROOT
#define CONFIG_NO_KERNEL_EVERYONE_IS_ROOT
#endif /* ... */
/*[[[end]]]*/

/* Credential checking. */

DECL_BEGIN

#ifdef __CC__

#ifndef CONFIG_KERNEL_EVERYONE_IS_ROOT
/* Credential-Capabilities */
#define CREDCAP_COUNT ((CAP_LAST_CAP - CAP_FIRST_CAP) + 1)
#define CREDCAP_ENCODE(capno)          __CCAST(syscall_ulong_t)((capno) - CAP_FIRST_CAP)
#define CREDCAP_DECODE(internal_capno) __CCAST(syscall_slong_t)((internal_capno) + CAP_FIRST_CAP)
#define _CREDCAP_BYTECOUNT ((CREDCAP_COUNT + 7) / 8)

struct credcap {
	byte_t cc_caps[_CREDCAP_BYTECOUNT]; /* Bitset of capabilities */
};

#if (CREDCAP_COUNT & 7) == 0
#define _CREDCAP_INIT_LASTBYTE 0xff
#else /* (CREDCAP_COUNT & 7) == 0 */
#define _CREDCAP_INIT_LASTBYTE (__CCAST(byte_t)((1u << (CREDCAP_COUNT & 7)) - 1))
#endif /* (CREDCAP_COUNT & 7) != 0 */

#if _CREDCAP_BYTECOUNT == 1
#define CREDCAP_INIT_FULL { _CREDCAP_INIT_LASTBYTE }
#elif _CREDCAP_BYTECOUNT == 2
#define CREDCAP_INIT_FULL { 0xff, _CREDCAP_INIT_LASTBYTE }
#elif _CREDCAP_BYTECOUNT == 3
#define CREDCAP_INIT_FULL { 0xff, 0xff, _CREDCAP_INIT_LASTBYTE }
#elif _CREDCAP_BYTECOUNT == 4
#define CREDCAP_INIT_FULL { 0xff, 0xff, 0xff, _CREDCAP_INIT_LASTBYTE }
#elif _CREDCAP_BYTECOUNT == 5
#define CREDCAP_INIT_FULL { 0xff, 0xff, 0xff, 0xff, _CREDCAP_INIT_LASTBYTE }
#elif _CREDCAP_BYTECOUNT == 6
#define CREDCAP_INIT_FULL { 0xff, 0xff, 0xff, 0xff, 0xff, _CREDCAP_INIT_LASTBYTE }
#elif _CREDCAP_BYTECOUNT == 7
#define CREDCAP_INIT_FULL { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, _CREDCAP_INIT_LASTBYTE }
#elif _CREDCAP_BYTECOUNT == 8
#define CREDCAP_INIT_FULL { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, _CREDCAP_INIT_LASTBYTE }
#elif _CREDCAP_BYTECOUNT == 9
#define CREDCAP_INIT_FULL { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, _CREDCAP_INIT_LASTBYTE }
#elif _CREDCAP_BYTECOUNT == 10
#define CREDCAP_INIT_FULL { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, _CREDCAP_INIT_LASTBYTE }
#elif _CREDCAP_BYTECOUNT == 11
#define CREDCAP_INIT_FULL { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, _CREDCAP_INIT_LASTBYTE }
#elif _CREDCAP_BYTECOUNT == 12
#define CREDCAP_INIT_FULL { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, _CREDCAP_INIT_LASTBYTE }
#else /* _CREDCAP_BYTECOUNT == ... */
#error "Unsupported `_CREDCAP_BYTECOUNT' (please extend)"
#endif /* _CREDCAP_BYTECOUNT != ... */


LOCAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL credcap_capable)(struct credcap const *__restrict self,
                               syscall_slong_t capno) {
	syscall_ulong_t icap = CREDCAP_ENCODE(capno);
	return (self->cc_caps[icap / 8] & (1 << (icap % 8))) != 0;
}

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL credcap_turnon)(struct credcap *__restrict self,
                              syscall_slong_t capno) {
	syscall_ulong_t icap = CREDCAP_ENCODE(capno);
	self->cc_caps[icap / 8] |= (1 << (icap % 8));
}

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL credcap_turnoff)(struct credcap *__restrict self,
                               syscall_slong_t capno) {
	syscall_ulong_t icap = CREDCAP_ENCODE(capno);
	self->cc_caps[icap / 8] &= ~(1 << (icap % 8));
}

LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL credcap_copyfrom)(struct credcap *__restrict self,
                                struct credcap const *__restrict src,
                                syscall_slong_t capno) {
	syscall_ulong_t icap;
	size_t index;
	byte_t mask;
	icap  = CREDCAP_ENCODE(capno);
	index = icap / 8;
	mask  = 1 << (icap % 8);
	self->cc_caps[index] &= ~mask;
	self->cc_caps[index] |= src->cc_caps[index] & mask;
}

LOCAL NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL credcap_orset)(struct credcap *dst,
                             struct credcap const *src1,
                             struct credcap const *src2) {
	syscall_ulong_t i;
	for (i = 0; i < _CREDCAP_BYTECOUNT; ++i)
		dst->cc_caps[i] = src1->cc_caps[i] | src2->cc_caps[i];
}

LOCAL NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL credcap_andset)(struct credcap *dst,
                              struct credcap const *src1,
                              struct credcap const *src2) {
	syscall_ulong_t i;
	for (i = 0; i < _CREDCAP_BYTECOUNT; ++i)
		dst->cc_caps[i] = src1->cc_caps[i] & src2->cc_caps[i];
}


/* Supplementary credential groups. */
struct cred_groups {
	REF refcnt_t                   cg_refcnt;  /* Reference counter. */
	size_t                         cg_count;   /* [const] # of supplementary groups. */
	COMPILER_FLEXIBLE_ARRAY(gid_t, cg_groups); /* [0..cg_count][const] Array of supplementary groups (sorted ascendingly; no duplicates). */
};

/* Default, empty set of supplementary groups. */
DATDEF struct cred_groups cred_groups_empty;

#ifndef ____os_free_defined
#define ____os_free_defined
FUNDEF NOBLOCK void NOTHROW(KCALL __os_free)(VIRT void *ptr) ASMNAME("kfree");
#endif /* !____os_free_defined */
#define cred_groups_destroy(self) __os_free(self)
DEFINE_REFCNT_FUNCTIONS(struct cred_groups, cg_refcnt, cred_groups_destroy)

/* Check if the groups from `subset' are a sub-set of those from `superset' */
FUNDEF ATTR_PURE WUNUSED NONNULL((1, 2)) __BOOL
NOTHROW(FCALL cred_groups_issubset)(struct cred_groups const *__restrict subset,
                                    struct cred_groups const *__restrict superset);


/* Check if `self' contains `gid' */
EIDECLARE(NOBLOCK ATTR_PURE WUNUSED NONNULL((1)), __BOOL, NOTHROW, FCALL,
          cred_groups_contains, (struct cred_groups const *__restrict self, gid_t gid), {
	size_t lo, hi;
	lo = 0;
	hi = self->cg_count;
	while (lo < hi) {
		size_t i;
		i = (lo + hi) / 2;
		if (gid < self->cg_groups[i]) {
			hi = i;
		} else if (gid > self->cg_groups[i]) {
			lo = i + 1;
		} else {
			return true;
		}
	}
	return false;
})


/* Atomic reference to `cred_groups' */
ARREF(cred_groups_arref, cred_groups);

/* Thread credentials controller. */
struct cred {
	REF refcnt_t             c_refcnt;          /* Reference counter. */
	struct cred_groups_arref c_groups;          /* [1..1] Supplementary group IDs. These are used as extensions to `c_fsgid'. */
	struct atomic_rwlock     c_lock;            /* Lock for the credentials controller. */
	WEAK uid_t               c_ruid;            /* [lock(READ(ATOMIC), WRITE(c_lock))] Real user ID */
	WEAK gid_t               c_rgid;            /* [lock(READ(ATOMIC), WRITE(c_lock))] Real group ID */
	WEAK uid_t               c_euid;            /* [lock(READ(ATOMIC), WRITE(c_lock))] Effective user ID
	                                             * Used   to   determine   permissions   for   accessing
	                                             * shared resources (mainly shared memory)
	                                             * When this field is set, you must also set `c_fsuid' */
	WEAK gid_t               c_egid;            /* [lock(READ(ATOMIC), WRITE(c_lock))] Effective group ID (s.a. `c_euid') */
	WEAK uid_t               c_suid;            /* [lock(READ(ATOMIC), WRITE(c_lock))] Saved  user  ID
	                                             * When  an `S_ISUID' / `S_ISGID' program is executed,
	                                             * what  would have otherwise been `c_euid' / `c_egid'
	                                             * is stored here (and `c_euid' / `c_egid' will become
	                                             * the `struct stat::st_uid/st_gid' of the executable) */
	WEAK gid_t               c_sgid;            /* [lock(READ(ATOMIC), WRITE(c_lock))] Saved group ID (s.a. `c_suid') */
	WEAK uid_t               c_fsuid;           /* [lock(READ(ATOMIC), WRITE(c_lock))] Filesystem user ID
	                                             * Used to  determine  permissions  for  accessing  files */
	WEAK gid_t               c_fsgid;           /* [lock(READ(ATOMIC), WRITE(c_lock))] Filesystem group ID */
	WEAK struct credcap      c_cap_permitted;   /* [lock(READ(ATOMIC), WRITE(c_lock))] Capabilities that can be acquired by anyone, at any time. */
	WEAK struct credcap      c_cap_inheritable; /* [lock(READ(ATOMIC), WRITE(c_lock))] Capabilities that ~can~ be inherited by privileged programs during exec(). */
	WEAK struct credcap      c_cap_effective;   /* [lock(READ(ATOMIC), WRITE(c_lock))] Capabilities current in effect. */
	WEAK struct credcap      c_cap_bounding;    /* [lock(READ(ATOMIC), WRITE(c_lock))] - Caps that can be made permitted by privileged programs
	                                             *                                     - Caps that can be added to `caps.inheritable' by `capset()' */
	WEAK struct credcap      c_cap_ambient;     /* [lock(READ(ATOMIC), WRITE(c_lock))] Capabilities that always become permitted in privileged programs
	                                             * during exec(). Note  the invariant  that this one  is always  a subset of  permitted &  inheritable. */
	WEAK uint8_t             c_securebits;      /* [lock(READ(ATOMIC), WRITE(c_lock))] Secure capability bits. (set of `SECBIT_*' from <kos/capability.h>) */
	WEAK uint8_t             c_no_new_privs;    /* [lock(READ(ATOMIC), WRITE(c_lock))] When non-zero, exec() calls do not add new permissions. */
};

/* Helper macros for `struct cred::c_lock' */
#define cred_mustreap(self)     0
#define cred_reap(self)         (void)0
#define _cred_reap(self)        (void)0
#define cred_write(self)        atomic_rwlock_write(&(self)->c_lock)
#define cred_write_nx(self)     atomic_rwlock_write_nx(&(self)->c_lock)
#define cred_trywrite(self)     atomic_rwlock_trywrite(&(self)->c_lock)
#define cred_endwrite(self)     (atomic_rwlock_endwrite(&(self)->c_lock), cred_reap(self))
#define _cred_endwrite(self)    atomic_rwlock_endwrite(&(self)->c_lock)
#define cred_read(self)         atomic_rwlock_read(&(self)->c_lock)
#define cred_read_nx(self)      atomic_rwlock_read_nx(&(self)->c_lock)
#define cred_tryread(self)      atomic_rwlock_tryread(&(self)->c_lock)
#define _cred_endread(self)     atomic_rwlock_endread(&(self)->c_lock)
#define cred_endread(self)      (void)(atomic_rwlock_endread(&(self)->c_lock) && (cred_reap(self), 0))
#define _cred_end(self)         atomic_rwlock_end(&(self)->c_lock)
#define cred_end(self)          (void)(atomic_rwlock_end(&(self)->c_lock) && (cred_reap(self), 0))
#define cred_upgrade(self)      atomic_rwlock_upgrade(&(self)->c_lock)
#define cred_upgrade_nx(self)   atomic_rwlock_upgrade_nx(&(self)->c_lock)
#define cred_tryupgrade(self)   atomic_rwlock_tryupgrade(&(self)->c_lock)
#define cred_downgrade(self)    atomic_rwlock_downgrade(&(self)->c_lock)
#define cred_reading(self)      atomic_rwlock_reading(&(self)->c_lock)
#define cred_writing(self)      atomic_rwlock_writing(&(self)->c_lock)
#define cred_canread(self)      atomic_rwlock_canread(&(self)->c_lock)
#define cred_canwrite(self)     atomic_rwlock_canwrite(&(self)->c_lock)
#define cred_waitread(self)     atomic_rwlock_waitread(&(self)->c_lock)
#define cred_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->c_lock)
#define cred_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->c_lock)
#define cred_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->c_lock)


/* Destroy the given credentials controller. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL cred_destroy)(struct cred *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct cred, c_refcnt, cred_destroy)

/* Clone the given credentials controller `self' and return the copy */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct cred *FCALL
cred_clone(struct cred *__restrict self) THROWS(E_BADALLOC);

/* [1..1][lock(read(THIS_TASK || INTERN(lock)), write(THIS_TASK && INTERN(lock)))]
 * Per-thread credentials controller. */
DATDEF ATTR_PERTASK REF struct cred *this_cred;
#define THIS_CRED PERTASK_GET(this_cred)

/* Return the credentials controller of the given thread. */
FUNDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct cred *
NOTHROW(FCALL task_getcred)(struct task *__restrict thread);

/* Exchange the credentials controller of the calling thread. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct cred *
NOTHROW(FCALL task_setcred_inherit)(/*inherit(always)*/ REF struct cred *__restrict newcred);
#define task_setcred(newcred) task_setcred_inherit(incref(newcred))

/* Generic kernel credentials / credentials for /bin/init */
DATDEF struct cred cred_kernel;


/* Check if the calling thread has a given capability
 * `capno' (one of  `CAP_*' from  <kos/capability.h>) */
EIDECLARE(NOBLOCK ATTR_ARTIFICIAL ATTR_PURE WUNUSED, __BOOL,
          NOTHROW, FCALL, capable, (syscall_slong_t capno), {
	return credcap_capable(&THIS_CRED->c_cap_effective, capno);
})

/* Ensure that the calling thread is `capable(capno)'
 * If the calling thread isn't, throw an `E_INSUFFICIENT_RIGHTS' exception */
FUNDEF NOBLOCK void FCALL
require(syscall_slong_t capno)
		THROWS(E_INSUFFICIENT_RIGHTS);



/* Get the calling thread's real user ID */
EIDECLARE(NOBLOCK ATTR_ARTIFICIAL ATTR_PURE WUNUSED, uid_t, NOTHROW, FCALL, cred_getruid, (void), {
	return __hybrid_atomic_load(THIS_CRED->c_ruid, __ATOMIC_ACQUIRE);
})

/* Get the calling thread's real group ID */
EIDECLARE(NOBLOCK ATTR_ARTIFICIAL ATTR_PURE WUNUSED, gid_t, NOTHROW, FCALL, cred_getrgid, (void), {
	return __hybrid_atomic_load(THIS_CRED->c_rgid, __ATOMIC_ACQUIRE);
})

/* Get the calling thread's effective user ID */
EIDECLARE(NOBLOCK ATTR_ARTIFICIAL ATTR_PURE WUNUSED, uid_t, NOTHROW, FCALL, cred_geteuid, (void), {
	return __hybrid_atomic_load(THIS_CRED->c_euid, __ATOMIC_ACQUIRE);
})

/* Get the calling thread's effective group ID */
EIDECLARE(NOBLOCK ATTR_ARTIFICIAL ATTR_PURE WUNUSED, gid_t, NOTHROW, FCALL, cred_getegid, (void), {
	return __hybrid_atomic_load(THIS_CRED->c_egid, __ATOMIC_ACQUIRE);
})


/* Get the calling thread's saved user ID */
EIDECLARE(NOBLOCK ATTR_ARTIFICIAL ATTR_PURE WUNUSED, uid_t, NOTHROW, FCALL, cred_getsuid, (void), {
	return __hybrid_atomic_load(THIS_CRED->c_suid, __ATOMIC_ACQUIRE);
})

/* Get the calling thread's saved group ID */
EIDECLARE(NOBLOCK ATTR_ARTIFICIAL ATTR_PURE WUNUSED, gid_t, NOTHROW, FCALL, cred_getsgid, (void), {
	return __hybrid_atomic_load(THIS_CRED->c_sgid, __ATOMIC_ACQUIRE);
})

/* Get the calling thread's filesystem user ID */
EIDECLARE(NOBLOCK ATTR_ARTIFICIAL ATTR_PURE WUNUSED, uid_t, NOTHROW, FCALL, cred_getfsuid, (void), {
	return __hybrid_atomic_load(THIS_CRED->c_fsuid, __ATOMIC_ACQUIRE);
})

/* Get the calling thread's filesystem group ID */
EIDECLARE(NOBLOCK ATTR_ARTIFICIAL ATTR_PURE WUNUSED, gid_t, NOTHROW, FCALL, cred_getfsgid, (void), {
	return __hybrid_atomic_load(THIS_CRED->c_fsgid, __ATOMIC_ACQUIRE);
})

/* Set user IDs. IDs that should not be set may be passed as `(uid_t)-1'.
 * @param: chk_rights: When true, check if the calling thread has the right to do this. */
FUNDEF void FCALL
cred_setuid(uid_t ruid, uid_t euid, uid_t suid, uid_t fsuid, __BOOL chk_rights DFL(1))
		THROWS(E_INSUFFICIENT_RIGHTS);
FUNDEF void FCALL
cred_setgid(gid_t rgid, gid_t egid, gid_t sgid, gid_t fsgid, __BOOL chk_rights DFL(1))
		THROWS(E_INSUFFICIENT_RIGHTS);

/* Set the list of supplementary group ids of the calling thread. */
FUNDEF void FCALL
cred_setgroups(/*inherit(on_success)*/ REF struct cred_groups *__restrict new_groups)
		THROWS(E_INSUFFICIENT_RIGHTS);


#ifdef BUILDING_KERNEL_CORE
/* Update program credentials as has to be done as part of an exec() system call. */
INTDEF void FCALL cred_onexec(struct mfile *__restrict program_file) THROWS(E_BADALLOC);
#endif /* BUILDING_KERNEL_CORE */

/* Check if the calling thread is considered to be apart of the given group `gid' */
EIDECLARE(NOBLOCK ATTR_PURE WUNUSED, __BOOL, NOTHROW, FCALL,
          cred_isfsgroupmember, (gid_t gid), {
	__BOOL result;
	struct cred *self = THIS_CRED;
	REF struct cred_groups *groups;

	/* Check for simple case: `gid' is the actual, current filesystem group ID */
	if (__hybrid_atomic_load(self->c_fsgid, __ATOMIC_ACQUIRE) == gid)
		return 1;

	/* Check supplementary groups. */
	groups = arref_get(&self->c_groups);
	result = cred_groups_contains(groups, gid);
	decref_unlikely(groups);
	return result;
})

#else /* !CONFIG_KERNEL_EVERYONE_IS_ROOT */
#define capable(capno)                            1
#define require(capno)                            (void)0
#define cred_getruid()                            (uid_t)0
#define cred_getrgid()                            (gid_t)0
#define cred_geteuid()                            (uid_t)0
#define cred_getegid()                            (gid_t)0
#define cred_getsuid()                            (uid_t)0
#define cred_getsgid()                            (gid_t)0
#define cred_getfsuid()                           (uid_t)0
#define cred_getfsgid()                           (gid_t)0
#define cred_setuid(ruid, euid, suid, fsuid, ...) (void)0
#define cred_setgid(rgid, egid, sgid, fsgid, ...) (void)0
#define cred_setgroups(ngroups, groups)           (void)0
#define cred_isfsgroupmember(gid)                 0 /* Yes, this has to be `0'! */
#endif /* CONFIG_KERNEL_EVERYONE_IS_ROOT */

/* Helper macros for only setting specific IDs */
#define cred_setruid(/*uid_t*/ ruid)                                   cred_setuid(ruid, (uid_t)-1, (uid_t)-1, (uid_t)-1, 1)
#define cred_seteuid(/*uid_t*/ euid)                                   cred_setuid((uid_t)-1, euid, (uid_t)-1, euid, 1)
#define cred_setsuid(/*uid_t*/ suid)                                   cred_setuid((uid_t)-1, (uid_t)-1, suid, (uid_t)-1, 1)
#define cred_setfsuid(/*uid_t*/ fsuid)                                 cred_setuid((uid_t)-1, (uid_t)-1, (uid_t)-1, fsuid, 1)
#define cred_setrgid(/*gid_t*/ rgid)                                   cred_setgid(rgid, (gid_t)-1, (gid_t)-1, (gid_t)-1, 1)
#define cred_setegid(/*gid_t*/ egid)                                   cred_setgid((gid_t)-1, egid, (gid_t)-1, egid, 1)
#define cred_setsgid(/*gid_t*/ sgid)                                   cred_setgid((gid_t)-1, (gid_t)-1, sgid, (gid_t)-1, 1)
#define cred_setfsgid(/*gid_t*/ fsgid)                                 cred_setgid((gid_t)-1, (gid_t)-1, (gid_t)-1, fsgid, 1)
#define cred_setreuid(/*uid_t*/ ruid, /*uid_t*/ euid)                  cred_setuid(ruid, euid, (uid_t)-1, euid, 1)
#define cred_setregid(/*gid_t*/ rgid, /*gid_t*/ egid)                  cred_setgid(rgid, egid, (gid_t)-1, egid, 1)
#define cred_setresuid(/*uid_t*/ ruid, /*uid_t*/ euid, /*uid_t*/ suid) cred_setuid(ruid, euid, suid, euid, 1)
#define cred_setresgid(/*gid_t*/ rgid, /*gid_t*/ egid, /*gid_t*/ sgid) cred_setgid(rgid, egid, sgid, egid, 1)


/* Credential assertion (throw an error if the caller doesn't have the required credential) */
struct mman;

/* Caller can read from `target_mm' */
#define cred_require_mmanread(target_mm) (void)0

/* Caller can write to `target_mm' */
#define cred_require_mmanwrite(target_mm) (void)0

/* `CAP_SYS_ADMIN' */
#define cred_require_sysadmin() require(CAP_SYS_ADMIN)

/* TODO: Go through all system calls already defined and add credential checks where necessary. */
/* TODO: Add credential checks for individual ksysctl() commands */

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_CRED_H */
