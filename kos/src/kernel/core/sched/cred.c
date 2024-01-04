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
#ifndef GUARD_KERNEL_SRC_SCHED_CRED_C
#define GUARD_KERNEL_SRC_SCHED_CRED_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

/* Credential checking. */

#include <kernel/compiler.h>

#include <debugger/hook.h> /* DEFINE_DBG_BZERO_OBJECT */
#include <kernel/driver-param.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/fs/node.h>
#include <kernel/fs/super.h>
#include <kernel/malloc.h>
#include <kernel/mman/mfile.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cpu.h> /* CONFIG_NO_SMP */
#include <sched/cred.h>
#include <sched/task.h>

#include <hybrid/byteorder.h>
#include <hybrid/sched/atomic-lock.h>
#include <hybrid/sequence/bsearch.h>

#include <compat/config.h>
#include <sys/stat.h>

#include <assert.h>
#include <atomic.h>
#include <errno.h>
#include <sched.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#include <asm/syscalls32_d.h>
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
#include <asm/syscalls64_d.h>
#else /* __ARCH_COMPAT_SIZEOF_POINTER == ... */
#error "Unsupported `__ARCH_COMPAT_SIZEOF_POINTER'"
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != ... */
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

#ifndef CONFIG_KERNEL_EVERYONE_IS_ROOT

/* Default, empty set of supplementary groups. */
PUBLIC struct cred_groups cred_groups_empty = {
	.cg_refcnt = 2, /* +1: cred_groups_empty, +1: cred_kernel.c_groups */
	.cg_count  = 0, /* No additional groups. */
};



/* Check if `self' contains `gid' */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL cred_groups_contains)(struct cred_groups const *__restrict self,
                                    gid_t gid) {
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
}

/* Check if the groups from `subset' are a sub-set of those from `superset' */
PUBLIC ATTR_PURE WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL cred_groups_issubset)(struct cred_groups const *__restrict subset,
                                    struct cred_groups const *__restrict superset) {
	size_t i, j;
	if (subset->cg_count > superset->cg_count)
		return false; /* There are more groups, so it can't be a sub-set. */
	for (i = 0, j = 0;;) {
		gid_t subset_group;
		if (i >= subset->cg_count)
			return true; /* No additional groups found! */
		subset_group = subset->cg_groups[i];
		/* Check if we can find `subset_group' within the superset */
		for (;;) {
			gid_t superset_group;
			if (j >= superset->cg_count)
				return false; /* No in here... */
			superset_group = superset->cg_groups[j];
			if (superset_group == subset_group)
				break;
			if (superset_group > subset_group)
				return false; /* Because they're sorted, we won't find `subset_group' in `superset' */
			++j;
		}
		++i;
	}
}








/* Destroy the given credentials controller. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL cred_destroy)(struct cred *__restrict self) {
	arref_fini(&self->c_groups);
	kfree(self);
}

/* Clone the given credentials controller `self' and return the copy */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct cred *FCALL
cred_clone(struct cred *__restrict self) THROWS(E_BADALLOC) {
	REF struct cred *result;
	REF struct cred_groups *groups;
	result = (REF struct cred *)kmalloc(sizeof(struct cred),
	                                    GFP_NORMAL);
	TRY {
		cred_read(self);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}

	/* Copy static credentials data. */
	memcpy((byte_t *)result + offsetafter(struct cred, c_lock),
	       (byte_t *)self + offsetafter(struct cred, c_lock),
	       sizeof(struct cred) - offsetafter(struct cred, c_lock));

	/* Copy supplementary groups. */
	groups = arref_get(&self->c_groups);
	arref_init(&result->c_groups, groups);
	cred_endread(self);
	result->c_refcnt = 1;
	atomic_rwlock_init(&result->c_lock);
	return result;
}




/* Generic kernel credentials / credentials for /bin/init */
PUBLIC struct cred cred_kernel = {
	.c_refcnt          = 2, /* +1: `cred_kernel', +1: FORTASK(&boottask, this_cred) */
	.c_groups          = ARREF_INIT(&cred_groups_empty),
	.c_lock            = ATOMIC_RWLOCK_INIT,
	.c_ruid            = (uid_t)0,
	.c_rgid            = (gid_t)0,
	.c_euid            = (uid_t)0,
	.c_egid            = (gid_t)0,
	.c_suid            = (uid_t)0,
	.c_sgid            = (gid_t)0,
	.c_fsuid           = (uid_t)0,
	.c_fsgid           = (gid_t)0,
	.c_cap_permitted   = CREDCAP_INIT_FULL,
	.c_cap_inheritable = CREDCAP_INIT_FULL,
	.c_cap_effective   = CREDCAP_INIT_FULL,
	.c_cap_bounding    = CREDCAP_INIT_FULL,
	.c_cap_ambient     = CREDCAP_INIT_FULL,
};

/* [1..1][lock(read(THIS_TASK || INTERN(lock)), write(THIS_TASK && INTERN(lock)))]
 * Per-thread credentials controller.
 * NOTE: Initialize changed to `NULL' in `kernel_initialize_scheduler_after_smp()' */
PUBLIC ATTR_PERTASK ATTR_ALIGN(REF struct cred *) this_cred = &cred_kernel;

DEFINE_PERTASK_FINI(fini_this_cred);
PRIVATE ATTR_USED NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fini_this_cred)(struct task *__restrict self) {
	xdecref(FORTASK(self, this_cred));
}


/* Check if the calling thread has a given capability
 * `capno' (one of  `CAP_*' from  <kos/capability.h>) */
PUBLIC NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL capable)(syscall_slong_t capno) {
	return credcap_capable(&THIS_CRED->c_cap_effective, capno);
}

/* Ensure that the calling thread is `capable(capno)'
 * If the calling thread isn't, throw an `E_INSUFFICIENT_RIGHTS' exception */
PUBLIC NOBLOCK void FCALL
require(syscall_slong_t capno)
		THROWS(E_INSUFFICIENT_RIGHTS) {
	if (!capable(capno))
		THROW(E_INSUFFICIENT_RIGHTS, capno);
}

/* Lock for accessing any remote thread's this_cred field */
#ifndef CONFIG_NO_SMP
PRIVATE struct atomic_lock cred_change_lock = ATOMIC_LOCK_INIT;
#endif /* !CONFIG_NO_SMP */
#define cred_change_lock_acquire() atomic_lock_acquire_smp(&cred_change_lock)
#define cred_change_lock_release() atomic_lock_release_smp(&cred_change_lock)

/* Return the credentials controller of the given thread. */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct cred *
NOTHROW(FCALL task_getcred)(struct task *__restrict thread) {
	REF struct cred *result;
	cred_change_lock_acquire();
	result = incref(FORTASK(thread, this_cred));
	cred_change_lock_release();
	return result;
}

/* Exchange the credentials controller of the calling thread. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct cred *
NOTHROW(FCALL task_setcred_inherit)(/*inherit(always)*/ REF struct cred *__restrict newcred) {
	REF struct cred *result;
	cred_change_lock_acquire();
	result = PERTASK_GET(this_cred); /* Inherit reference */
	PERTASK_SET(this_cred, newcred); /* Inherit reference */
	cred_change_lock_release();
	return result;
}





/* Get the calling thread's real user ID */
PUBLIC NOBLOCK ATTR_PURE WUNUSED uid_t
NOTHROW(FCALL cred_getruid)(void) {
	return atomic_read(&THIS_CRED->c_ruid);
}

/* Get the calling thread's real group ID */
PUBLIC NOBLOCK ATTR_PURE WUNUSED gid_t
NOTHROW(FCALL cred_getrgid)(void) {
	return atomic_read(&THIS_CRED->c_rgid);
}

/* Get the calling thread's effective user ID */
PUBLIC NOBLOCK ATTR_PURE WUNUSED uid_t
NOTHROW(FCALL cred_geteuid)(void) {
	return atomic_read(&THIS_CRED->c_euid);
}

/* Get the calling thread's effective group ID */
PUBLIC NOBLOCK ATTR_PURE WUNUSED gid_t
NOTHROW(FCALL cred_getegid)(void) {
	return atomic_read(&THIS_CRED->c_egid);
}


/* Get the calling thread's saved user ID */
PUBLIC NOBLOCK ATTR_PURE WUNUSED uid_t
NOTHROW(FCALL cred_getsuid)(void) {
	return atomic_read(&THIS_CRED->c_suid);
}

/* Get the calling thread's saved group ID */
PUBLIC NOBLOCK ATTR_PURE WUNUSED gid_t
NOTHROW(FCALL cred_getsgid)(void) {
	return atomic_read(&THIS_CRED->c_sgid);
}

/* Get the calling thread's filesystem user ID */
PUBLIC NOBLOCK ATTR_PURE WUNUSED uid_t
NOTHROW(FCALL cred_getfsuid)(void) {
	return atomic_read(&THIS_CRED->c_fsuid);
}

/* Get the calling thread's filesystem group ID */
PUBLIC NOBLOCK ATTR_PURE WUNUSED gid_t
NOTHROW(FCALL cred_getfsgid)(void) {
	return atomic_read(&THIS_CRED->c_fsgid);
}


/* Check if the calling thread is considered to be apart of the given group `gid' */
PUBLIC NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL cred_isfsgroupmember)(gid_t gid) {
	bool result;
	struct cred *self = THIS_CRED;
	REF struct cred_groups *groups;

	/* Check for simple case: `gid' is the actual, current filesystem group ID */
	if (atomic_read(&self->c_fsgid) == gid)
		return true;

	/* Check supplementary groups. */
	groups = arref_get(&self->c_groups);
	result = cred_groups_contains(groups, gid);
	decref_unlikely(groups);
	return result;
}


struct file_creds {
	struct credcap fc_permitted;   /* ... */
	struct credcap fc_inheritable; /* ... */
	bool           fc_effective;   /* ... */
};

/* Try to load file credentials from `program_file' */
PRIVATE WUNUSED NONNULL((1, 2)) bool KCALL
inode_get_file_creds(struct mfile *__restrict program_file,
                     struct file_creds *__restrict result) {
	(void)program_file;
	(void)result;
	COMPILER_IMPURE();
	/* TODO */
	/* TODO: Once this function gets implemented, `libc_saved_AT_SECURE_init()'
	 *       also  has to be updated to perform the same checks as done here in
	 *       order to determine if additional capabilities should be added. */
	return false;
}


/* Invoke `cb()' for each of the special fsuid capabilities */
#define _FOREACH_SPECIAL_FSUID_CAPS(cb) \
	cb(CAP_CHOWN)                       \
	cb(CAP_DAC_OVERRIDE)                \
	cb(CAP_DAC_READ_SEARCH)             \
	cb(CAP_FOWNER)                      \
	cb(CAP_FSETID)                      \
	cb(CAP_LINUX_IMMUTABLE)             \
	cb(CAP_MAC_OVERRIDE)                \
	cb(CAP_MKNOD)
#if (CAP_CHOWN + 1 == CAP_DAC_OVERRIDE &&    \
     CAP_CHOWN + 2 == CAP_DAC_READ_SEARCH && \
     CAP_CHOWN + 3 == CAP_FOWNER &&          \
     CAP_CHOWN + 4 == CAP_FSETID)
#define FOREACH_SPECIAL_FSUID_CAPS(cb)                         \
	{                                                          \
		syscall_slong_t _cap;                                  \
		for (_cap = CAP_CHOWN; _cap != CAP_FSETID + 1; ++_cap) \
			cb(_cap)                                           \
	}                                                          \
	cb(CAP_LINUX_IMMUTABLE)                                    \
	cb(CAP_MAC_OVERRIDE)                                       \
	cb(CAP_MKNOD)
#else /* ... */
#define FOREACH_SPECIAL_FSUID_CAPS(cb) \
	_FOREACH_SPECIAL_FSUID_CAPS(cb)
#endif /* !... */


/* Remove from the set of effective caps */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL cred_turn_off_special_fsuid_caps)(struct cred *__restrict self) {
#define CLEAR_FROM_EFFECTIVE(cap) \
	credcap_turnoff(&self->c_cap_effective, cap);
	FOREACH_SPECIAL_FSUID_CAPS(CLEAR_FROM_EFFECTIVE);
#undef CLEAR_FROM_EFFECTIVE
}

/* Copy from permitted to effective caps */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL cred_restore_special_fsuid_caps)(struct cred *__restrict self) {
#define COPY_FROM_PERMITTED_INTO_EFFECTIVE(cap) \
	credcap_copyfrom(&self->c_cap_effective, &self->c_cap_permitted, cap);
	FOREACH_SPECIAL_FSUID_CAPS(COPY_FROM_PERMITTED_INTO_EFFECTIVE);
#undef COPY_FROM_PERMITTED_INTO_EFFECTIVE
}



/* Boot option: `no_file_caps' */
DEFINE_CMDLINE_FLAG_VAR(boot_no_file_caps, "no_file_caps");

/* Update program credentials as has to be done as part of an exec() system call. */
INTERN void FCALL
cred_onexec(struct mfile *__restrict program_file)
		THROWS(E_BADALLOC) {
	uid_t new_euid;
	struct cred *self = THIS_CRED;

	/* Unshare credentials if more the reference counter indicates that we must do so. */
	if (isshared(self)) {
		REF struct cred *copy;
		copy = cred_clone(self);
		PERTASK_SET(this_cred, copy); /* Inherit reference */
		decref_unlikely(self);        /* Drop the reference from the old  */
		assert(!isshared(copy));
		self = copy;
	}
	COMPILER_READ_BARRIER();

	/* NOTE: Because we've unshared `self', we don't have to acquire a lock,
	 *       since we  already  know  that no-one  can  modify  it  anymore! */
	new_euid = self->c_euid;
	if (!self->c_no_new_privs && mfile_isnode(program_file) &&
	    !(mfile_asnode(program_file)->fn_super->fs_root.mf_flags & MFILE_FS_NOSUID)) {
		/* Check for set-user-id/set-group-id */
		mode_t program_mode;
		uid_t program_uid;
		gid_t program_gid;
		struct fnode *node;
		struct fnode_perm_ops const *perm_ops;
		node     = mfile_asnode(program_file);
		perm_ops = fnode_getops(node)->no_perm;
		if (perm_ops && perm_ops->npo_getown) {
			(*perm_ops->npo_getown)(node, &program_uid, &program_gid);
			mfile_tslock_acquire(node);
			program_mode = node->fn_mode;
			mfile_tslock_release(node);
		} else {
			mfile_tslock_acquire(node);
			program_mode = node->fn_mode;
			program_uid  = node->fn_uid;
			program_gid  = node->fn_gid;
			mfile_tslock_release(node);
		}

		if (program_mode & S_ISUID) {
			new_euid = program_uid;
			/* Handle special credentials transitions that happen as part of UID changes. */
			if (!(self->c_securebits & SECBIT_NO_SETUID_FIXUP)) {
				/* Check for transition to/from root-mode */
				if ((self->c_ruid != 0) &&
				    (self->c_euid == 0) && (new_euid != 0) &&
				    (self->c_suid != 0)) {
					if (!(self->c_securebits & SECBIT_KEEP_CAPS))
						bzero(&self->c_cap_permitted, sizeof(self->c_cap_permitted));
					bzero(&self->c_cap_effective, sizeof(self->c_cap_effective));
					bzero(&self->c_cap_ambient, sizeof(self->c_cap_ambient));
				} else {
					if (self->c_euid == 0 && new_euid != 0) {
						bzero(&self->c_cap_effective, sizeof(self->c_cap_effective));
					} else if (self->c_euid != 0 && new_euid == 0) {
						memcpy(&self->c_cap_effective,
						       &self->c_cap_permitted,
						       sizeof(self->c_cap_effective));
					}
				}
				if (self->c_fsuid == 0 && new_euid != 0) {
					/* Remove from the set of effective caps */
					cred_turn_off_special_fsuid_caps(self);
				} else if (self->c_fsuid != 0 && new_euid == 0) {
					/* Copy from permitted to effective caps */
					cred_restore_special_fsuid_caps(self);
				}
			}
			self->c_euid  = new_euid;
			self->c_fsuid = new_euid;
			bzero(&self->c_cap_ambient, sizeof(self->c_cap_ambient));
		}
		if ((program_mode & (S_ISGID | S_IXGRP)) == (S_ISGID | S_IXGRP)) {
			self->c_egid  = program_gid;
			self->c_fsgid = program_gid;
			bzero(&self->c_cap_ambient, sizeof(self->c_cap_ambient));
		}
	}

	/* Check for exec-as-root */
	if ((self->c_ruid == 0 || new_euid == 0) && !(self->c_securebits & SECBIT_NOROOT)) {
		credcap_orset(&self->c_cap_permitted,
		              &self->c_cap_inheritable,
		              &self->c_cap_bounding);
		memcpy(&self->c_cap_effective,
		       &self->c_cap_permitted,
		       sizeof(self->c_cap_effective));
	} else if (boot_no_file_caps) {
normal_program_without_caps:
		/* Normal program without any special capabilities. */
		memcpy(&self->c_cap_permitted, &self->c_cap_ambient, sizeof(self->c_cap_permitted));
		memcpy(&self->c_cap_effective, &self->c_cap_ambient, sizeof(self->c_cap_effective));
	} else {
		struct file_creds fcreds;
		/* Try to load credentials from the given `program_file' */
		if (!inode_get_file_creds(program_file, &fcreds))
			goto normal_program_without_caps;
		/* Transform thread credentials by use of the program's file credentials. */
		bzero(&self->c_cap_ambient, sizeof(self->c_cap_ambient));
		credcap_andset(&fcreds.fc_inheritable, &fcreds.fc_inheritable, &self->c_cap_inheritable);
		credcap_andset(&fcreds.fc_permitted, &fcreds.fc_permitted, &self->c_cap_bounding);
		credcap_orset(&self->c_cap_permitted, &fcreds.fc_inheritable, &fcreds.fc_permitted);
		credcap_orset(&self->c_cap_permitted, &self->c_cap_permitted, &self->c_cap_ambient);
		memcpy(&self->c_cap_effective,
		       fcreds.fc_effective ? &self->c_cap_permitted
		                           : &self->c_cap_ambient,
		       sizeof(self->c_cap_effective));
	}
}



/* Set user IDs. IDs that should not be set may be passed as `(uid_t)-1'.
 * @param: chk_rights: When true, check if the calling thread has the right to do this. */
PUBLIC void FCALL
cred_setuid(uid_t ruid, uid_t euid,
            uid_t suid, uid_t fsuid,
            bool chk_rights)
		THROWS(E_INSUFFICIENT_RIGHTS) {
	struct cred *self = THIS_CRED;
	cred_write(self);
	/* Load old values for UIDs that shouldn't be modified */
	if (ruid == (uid_t)-1)
		ruid = self->c_ruid;
	if (euid == (uid_t)-1)
		euid = self->c_euid;
	if (suid == (uid_t)-1)
		suid = self->c_suid;
	if (fsuid == (uid_t)-1)
		fsuid = self->c_fsuid;
	if (chk_rights && !credcap_capable(&self->c_cap_effective, CAP_SETUID)) {
		/* Check for special case: Nothing would have actually changed. */
		bool is_a_noop;
		is_a_noop = ruid == self->c_ruid &&
		            euid == self->c_euid &&
		            suid == self->c_suid &&
		            fsuid == self->c_fsuid;
		cred_endwrite(self);
		/* Only throw an insufficient-rights exception
		 * if  the  call  wouldn't have  been  a no-op */
		if (!is_a_noop)
			THROW(E_INSUFFICIENT_RIGHTS, CAP_SETUID);
		return;
	}
	if (!(self->c_securebits & SECBIT_NO_SETUID_FIXUP)) {
		/* Check for transition to/from root-mode */
		if (((self->c_ruid == 0) ||
		     (self->c_euid == 0) ||
		     (self->c_suid == 0)) &&
		    ((ruid != 0) && (euid != 0) && (suid != 0))) {
			if (!(self->c_securebits & SECBIT_KEEP_CAPS))
				bzero(&self->c_cap_permitted, sizeof(self->c_cap_permitted));
			bzero(&self->c_cap_effective, sizeof(self->c_cap_effective));
			bzero(&self->c_cap_ambient, sizeof(self->c_cap_ambient));
		} else {
			if (self->c_euid == 0 && euid != 0) {
				bzero(&self->c_cap_effective, sizeof(self->c_cap_effective));
			} else if (self->c_euid != 0 && euid == 0) {
				memcpy(&self->c_cap_effective,
				       &self->c_cap_permitted,
				       sizeof(self->c_cap_effective));
			}
		}
		if (self->c_fsuid == 0 && fsuid != 0) {
			/* Remove from the set of effective caps */
			cred_turn_off_special_fsuid_caps(self);
		} else if (self->c_fsuid != 0 && fsuid == 0) {
			/* Copy from permitted to effective caps */
			cred_restore_special_fsuid_caps(self);
		}

	}
	/* Fill in the new user IDs. */
	self->c_ruid  = ruid;
	self->c_euid  = euid;
	self->c_suid  = suid;
	self->c_fsuid = fsuid;
	cred_endwrite(self);
}

PUBLIC void FCALL
cred_setgid(gid_t rgid, gid_t egid,
            gid_t sgid, gid_t fsgid,
            bool chk_rights)
		THROWS(E_INSUFFICIENT_RIGHTS) {
	struct cred *self = THIS_CRED;
	cred_write(self);
	/* Load old values for GIDs that shouldn't be modified */
	if (rgid == (gid_t)-1)
		rgid = self->c_rgid;
	if (egid == (gid_t)-1)
		egid = self->c_egid;
	if (sgid == (gid_t)-1)
		sgid = self->c_sgid;
	if (fsgid == (gid_t)-1)
		fsgid = self->c_fsgid;
	if (chk_rights && !credcap_capable(&self->c_cap_effective, CAP_SETGID)) {
		/* Check for special case: Nothing would have actually changed. */
		bool is_a_noop;
		is_a_noop = rgid == self->c_rgid &&
		            egid == self->c_egid &&
		            sgid == self->c_sgid &&
		            fsgid == self->c_fsgid;
		cred_endwrite(self);
		/* Only throw an insufficient-rights exception
		 * if  the  call  wouldn't have  been  a no-op */
		if (!is_a_noop)
			THROW(E_INSUFFICIENT_RIGHTS, CAP_SETGID);
		return;
	}
	/* Fill in the new user IDs. */
	self->c_rgid  = rgid;
	self->c_egid  = egid;
	self->c_sgid  = sgid;
	self->c_fsgid = fsgid;
	cred_endwrite(self);
}


/* Set the list of supplementary group ids of the calling thread. */
PUBLIC void FCALL
cred_setgroups(/*inherit(on_success)*/ REF struct cred_groups *__restrict new_groups)
		THROWS(E_INSUFFICIENT_RIGHTS) {
	struct cred *self = THIS_CRED;
	/* Groups can only be added if the caller has CAP_SETGID */
	if (capable(CAP_SETGID)) {
		arref_set_inherit(&self->c_groups, new_groups);
	} else {
		REF struct cred_groups *old_groups;
again:
		old_groups = arref_get(&self->c_groups);

		/* Without `CAP_SETGID', we can only  set the new set  of
		 * groups if it doesn't try to add any additional groups! */
		if (!cred_groups_issubset(new_groups, old_groups)) {
			decref_unlikely(old_groups);
			THROW(E_INSUFFICIENT_RIGHTS, CAP_SETGID);
		}

		/* The new set of groups is a subset, so we're always allowed to set it! */
		if (!arref_cmpxch_inherit_new(&self->c_groups, old_groups, new_groups)) {
			/* The old set of groups has changed in the mean time. */
			decref_unlikely(old_groups);
			goto again;
		}
	}
}
#endif /* !CONFIG_KERNEL_EVERYONE_IS_ROOT */


#define SYSCALL_RETURN_TYPE_OF3(a, b) b
#define SYSCALL_RETURN_TYPE_OF2(x)    SYSCALL_RETURN_TYPE_OF3 x
#define SYSCALL_RETURN_TYPE_OF(name)  SYSCALL_RETURN_TYPE_OF2(__NRRT_##name)

#define SYSCALL_ARG_TYPE_OF3(a, b)      b
#define SYSCALL_ARG_TYPE_OF2(x)         SYSCALL_ARG_TYPE_OF3 x
#define SYSCALL_ARG_TYPE_OF(name, argi) SYSCALL_ARG_TYPE_OF2(__NRAT##argi##_##name)

#ifdef __ARCH_HAVE_COMPAT
#define COMPAT_SYSCALL_ARG_TYPE_OF3(a, b) b
#define COMPAT_SYSCALL_ARG_TYPE_OF2(x)    COMPAT_SYSCALL_ARG_TYPE_OF3 x
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#define COMPAT_SYSCALL_ARG_TYPE_OF(name, argi) COMPAT_SYSCALL_ARG_TYPE_OF2(__NR32AT##argi##_##name)
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
#define COMPAT_SYSCALL_ARG_TYPE_OF(name, argi) COMPAT_SYSCALL_ARG_TYPE_OF2(__NR64AT##argi##_##name)
#else /* __ARCH_COMPAT_SIZEOF_POINTER == ... */
#error "Unsupported `__ARCH_COMPAT_SIZEOF_POINTER'"
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != ... */
#endif /* __ARCH_HAVE_COMPAT */

#define TYPEOF_DEREF(T) __typeof__(**(__typeof__(T) *)0)

#ifdef CONFIG_KERNEL_EVERYONE_IS_ROOT
#define SUPPRESS_EVERYONE_IS_ROOT_WARNINGS0()        COMPILER_IMPURE();
#define SUPPRESS_EVERYONE_IS_ROOT_WARNINGS1(a)       COMPILER_IMPURE(); (void)a;
#define SUPPRESS_EVERYONE_IS_ROOT_WARNINGS2(a, b)    COMPILER_IMPURE(); (void)a; (void)b;
#define SUPPRESS_EVERYONE_IS_ROOT_WARNINGS3(a, b, c) COMPILER_IMPURE(); (void)a; (void)b; (void)c;
#else /* CONFIG_KERNEL_EVERYONE_IS_ROOT */
#define SUPPRESS_EVERYONE_IS_ROOT_WARNINGS0()        /* nothing */
#define SUPPRESS_EVERYONE_IS_ROOT_WARNINGS1(a)       /* nothing */
#define SUPPRESS_EVERYONE_IS_ROOT_WARNINGS2(a, b)    /* nothing */
#define SUPPRESS_EVERYONE_IS_ROOT_WARNINGS3(a, b, c) /* nothing */
#endif /* !CONFIG_KERNEL_EVERYONE_IS_ROOT */






/************************************************************************/
/* getuid()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_GETUID
DEFINE_SYSCALL0(SYSCALL_RETURN_TYPE_OF(getuid), getuid) {
	uid_t result;
	COMPILER_IMPURE();
	result = cred_getruid();
	return (SYSCALL_RETURN_TYPE_OF(getuid))result;
}
#endif /* __ARCH_WANT_SYSCALL_GETUID */
#ifdef __ARCH_WANT_SYSCALL_GETUID32
DEFINE_SYSCALL0(SYSCALL_RETURN_TYPE_OF(getuid32), getuid32) {
	uid_t result;
	COMPILER_IMPURE();
	result = cred_getruid();
	return (SYSCALL_RETURN_TYPE_OF(getuid32))result;
}
#endif /* __ARCH_WANT_SYSCALL_GETUID32 */


/************************************************************************/
/* setuid()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SETUID
DEFINE_SYSCALL1(errno_t, setuid, SYSCALL_ARG_TYPE_OF(setuid, 0), uid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS1(uid);
	cred_setruid((uid_t)uid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETUID */
#ifdef __ARCH_WANT_SYSCALL_SETUID32
DEFINE_SYSCALL1(errno_t, setuid32, SYSCALL_ARG_TYPE_OF(setuid32, 0), uid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS1(uid);
	cred_setruid((uid_t)uid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETUID32 */


/************************************************************************/
/* getgid()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_GETGID
DEFINE_SYSCALL0(SYSCALL_RETURN_TYPE_OF(getgid), getgid) {
	gid_t result;
	COMPILER_IMPURE();
	result = cred_getrgid();
	return (SYSCALL_RETURN_TYPE_OF(getgid))result;
}
#endif /* __ARCH_WANT_SYSCALL_GETGID */
#ifdef __ARCH_WANT_SYSCALL_GETGID32
DEFINE_SYSCALL0(SYSCALL_RETURN_TYPE_OF(getgid32), getgid32) {
	gid_t result;
	COMPILER_IMPURE();
	result = cred_getrgid();
	return (SYSCALL_RETURN_TYPE_OF(getgid32))result;
}
#endif /* __ARCH_WANT_SYSCALL_GETGID32 */


/************************************************************************/
/* setgid()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SETGID
DEFINE_SYSCALL1(errno_t, setgid, SYSCALL_ARG_TYPE_OF(setgid, 0), gid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS1(gid);
	cred_setrgid((gid_t)gid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETGID */
#ifdef __ARCH_WANT_SYSCALL_SETGID32
DEFINE_SYSCALL1(errno_t, setgid32, SYSCALL_ARG_TYPE_OF(setgid32, 0), gid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS1(gid);
	cred_setrgid((gid_t)gid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETGID32 */


/************************************************************************/
/* geteuid()                                                            */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_GETEUID
DEFINE_SYSCALL0(SYSCALL_RETURN_TYPE_OF(geteuid), geteuid) {
	uid_t result;
	COMPILER_IMPURE();
	result = cred_geteuid();
	return (SYSCALL_RETURN_TYPE_OF(geteuid))result;
}
#endif /* __ARCH_WANT_SYSCALL_GETEUID */
#ifdef __ARCH_WANT_SYSCALL_GETEUID32
DEFINE_SYSCALL0(SYSCALL_RETURN_TYPE_OF(geteuid32), geteuid32) {
	uid_t result;
	COMPILER_IMPURE();
	result = cred_geteuid();
	return (SYSCALL_RETURN_TYPE_OF(geteuid32))result;
}
#endif /* __ARCH_WANT_SYSCALL_GETEUID32 */


/************************************************************************/
/* seteuid()                                                            */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SETEUID
DEFINE_SYSCALL1(errno_t, seteuid, SYSCALL_ARG_TYPE_OF(seteuid, 0), euid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS1(euid);
	cred_seteuid((uid_t)euid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETEUID */
#ifdef __ARCH_WANT_SYSCALL_SETEUID32
DEFINE_SYSCALL1(errno_t, seteuid32, SYSCALL_ARG_TYPE_OF(seteuid32, 0), euid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS1(euid);
	cred_seteuid((uid_t)euid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETEUID32 */


/************************************************************************/
/* getegid()                                                            */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_GETEGID
DEFINE_SYSCALL0(SYSCALL_RETURN_TYPE_OF(getegid), getegid) {
	gid_t result;
	COMPILER_IMPURE();
	result = cred_getegid();
	return (SYSCALL_RETURN_TYPE_OF(getegid))result;
}
#endif /* __ARCH_WANT_SYSCALL_GETEGID */
#ifdef __ARCH_WANT_SYSCALL_GETEGID32
DEFINE_SYSCALL0(SYSCALL_RETURN_TYPE_OF(getegid32), getegid32) {
	gid_t result;
	COMPILER_IMPURE();
	result = cred_getegid();
	return (SYSCALL_RETURN_TYPE_OF(getegid32))result;
}
#endif /* __ARCH_WANT_SYSCALL_GETEGID32 */


/************************************************************************/
/* setegid()                                                            */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SETEGID
DEFINE_SYSCALL1(errno_t, setegid, SYSCALL_ARG_TYPE_OF(setegid, 0), egid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS1(egid);
	cred_setegid((gid_t)egid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETEGID */
#ifdef __ARCH_WANT_SYSCALL_SETEGID32
DEFINE_SYSCALL1(errno_t, setegid32, SYSCALL_ARG_TYPE_OF(setegid32, 0), egid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS1(egid);
	cred_setegid((gid_t)egid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETEGID32 */


/************************************************************************/
/* getfsuid()                                                           */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_GETFSUID
DEFINE_SYSCALL0(SYSCALL_RETURN_TYPE_OF(getfsuid), getfsuid) {
	uid_t result;
	COMPILER_IMPURE();
	result = cred_getfsuid();
	return (SYSCALL_RETURN_TYPE_OF(getfsuid))result;
}
#endif /* __ARCH_WANT_SYSCALL_GETFSUID */
#ifdef __ARCH_WANT_SYSCALL_GETFSUID32
DEFINE_SYSCALL0(SYSCALL_RETURN_TYPE_OF(getfsuid32), getfsuid32) {
	uid_t result;
	COMPILER_IMPURE();
	result = cred_getfsuid();
	return (SYSCALL_RETURN_TYPE_OF(getfsuid32))result;
}
#endif /* __ARCH_WANT_SYSCALL_GETFSUID32 */


/************************************************************************/
/* setfsuid()                                                           */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SETFSUID
DEFINE_SYSCALL1(errno_t, setfsuid, SYSCALL_ARG_TYPE_OF(setfsuid, 0), fsuid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS1(fsuid);
	cred_setfsuid((uid_t)fsuid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETFSUID */
#ifdef __ARCH_WANT_SYSCALL_SETFSUID32
DEFINE_SYSCALL1(errno_t, setfsuid32, SYSCALL_ARG_TYPE_OF(setfsuid32, 0), fsuid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS1(fsuid);
	cred_setfsuid((uid_t)fsuid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETFSUID32 */


/************************************************************************/
/* getfsgid()                                                           */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_GETFSGID
DEFINE_SYSCALL0(SYSCALL_RETURN_TYPE_OF(getfsgid), getfsgid) {
	gid_t result;
	COMPILER_IMPURE();
	result = cred_getfsgid();
	return (SYSCALL_RETURN_TYPE_OF(getfsgid))result;
}
#endif /* __ARCH_WANT_SYSCALL_GETFSGID */
#ifdef __ARCH_WANT_SYSCALL_GETFSGID32
DEFINE_SYSCALL0(SYSCALL_RETURN_TYPE_OF(getfsgid32), getfsgid32) {
	gid_t result;
	COMPILER_IMPURE();
	result = cred_getfsgid();
	return (SYSCALL_RETURN_TYPE_OF(getfsgid32))result;
}
#endif /* __ARCH_WANT_SYSCALL_GETFSGID32 */


/************************************************************************/
/* setfsgid()                                                           */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SETFSGID
DEFINE_SYSCALL1(errno_t, setfsgid, SYSCALL_ARG_TYPE_OF(setfsgid, 0), fsgid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS1(fsgid);
	cred_setfsgid((gid_t)fsgid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETFSGID */
#ifdef __ARCH_WANT_SYSCALL_SETFSGID32
DEFINE_SYSCALL1(errno_t, setfsgid32, SYSCALL_ARG_TYPE_OF(setfsgid32, 0), fsgid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS1(fsgid);
	cred_setfsgid((gid_t)fsgid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETFSGID32 */






/************************************************************************/
/* setreuid()                                                           */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SETREUID
DEFINE_SYSCALL2(errno_t, setreuid,
                SYSCALL_ARG_TYPE_OF(setreuid, 0), ruid,
                SYSCALL_ARG_TYPE_OF(setreuid, 1), euid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS2(ruid, euid);
	cred_setreuid((uid_t)ruid,
	              (uid_t)euid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETREUID */
#ifdef __ARCH_WANT_SYSCALL_SETREUID32
DEFINE_SYSCALL2(errno_t, setreuid32,
                SYSCALL_ARG_TYPE_OF(setreuid32, 0), ruid,
                SYSCALL_ARG_TYPE_OF(setreuid32, 1), euid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS2(ruid, euid);
	cred_setreuid((uid_t)ruid,
	              (uid_t)euid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETREUID32 */


/************************************************************************/
/* setregid()                                                           */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SETREGID
DEFINE_SYSCALL2(errno_t, setregid,
                SYSCALL_ARG_TYPE_OF(setregid, 0), rgid,
                SYSCALL_ARG_TYPE_OF(setregid, 1), egid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS2(rgid, egid);
	cred_setregid((gid_t)rgid,
	              (gid_t)egid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETREGID */
#ifdef __ARCH_WANT_SYSCALL_SETREGID32
DEFINE_SYSCALL2(errno_t, setregid32,
                SYSCALL_ARG_TYPE_OF(setregid32, 0), rgid,
                SYSCALL_ARG_TYPE_OF(setregid32, 1), egid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS2(rgid, egid);
	cred_setregid((gid_t)rgid,
	              (gid_t)egid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETREGID32 */


/************************************************************************/
/* setresuid()                                                           */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SETRESUID
DEFINE_SYSCALL3(errno_t, setresuid,
                SYSCALL_ARG_TYPE_OF(setresuid, 0), ruid,
                SYSCALL_ARG_TYPE_OF(setresuid, 1), euid,
                SYSCALL_ARG_TYPE_OF(setresuid, 2), suid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS3(ruid, euid, suid);
	cred_setresuid((uid_t)ruid,
	               (uid_t)euid,
	               (uid_t)suid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETRESUID */
#ifdef __ARCH_WANT_SYSCALL_SETRESUID32
DEFINE_SYSCALL3(errno_t, setresuid32,
                SYSCALL_ARG_TYPE_OF(setresuid32, 0), ruid,
                SYSCALL_ARG_TYPE_OF(setresuid32, 1), euid,
                SYSCALL_ARG_TYPE_OF(setresuid32, 2), suid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS3(ruid, euid, suid);
	cred_setresuid((uid_t)ruid,
	               (uid_t)euid,
	               (uid_t)suid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETRESUID32 */


/************************************************************************/
/* setresgid()                                                           */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SETRESGID
DEFINE_SYSCALL3(errno_t, setresgid,
                SYSCALL_ARG_TYPE_OF(setresgid, 0), rgid,
                SYSCALL_ARG_TYPE_OF(setresgid, 1), egid,
                SYSCALL_ARG_TYPE_OF(setresgid, 2), sgid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS3(rgid, egid, sgid);
	cred_setresgid((gid_t)rgid,
	               (gid_t)egid,
	               (gid_t)sgid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETRESGID */
#ifdef __ARCH_WANT_SYSCALL_SETRESGID32
DEFINE_SYSCALL3(errno_t, setresgid32,
                SYSCALL_ARG_TYPE_OF(setresgid32, 0), rgid,
                SYSCALL_ARG_TYPE_OF(setresgid32, 1), egid,
                SYSCALL_ARG_TYPE_OF(setresgid32, 2), sgid) {
	SUPPRESS_EVERYONE_IS_ROOT_WARNINGS3(rgid, egid, sgid);
	cred_setresgid((gid_t)rgid,
	               (gid_t)egid,
	               (gid_t)sgid);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SETRESGID32 */






/************************************************************************/
/* getresuid()                                                          */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_GETRESUID
typedef TYPEOF_DEREF(SYSCALL_ARG_TYPE_OF(getresuid, 0)) getresuid_id_t;
DEFINE_SYSCALL3(errno_t, getresuid,
                NCX UNCHECKED getresuid_id_t *, pruid,
                NCX UNCHECKED getresuid_id_t *, peuid,
                NCX UNCHECKED getresuid_id_t *, psuid) {
#ifdef CONFIG_KERNEL_EVERYONE_IS_ROOT
	enum {
		ruid = 0,
		euid = 0,
		suid = 0
	};
#else /* CONFIG_KERNEL_EVERYONE_IS_ROOT */
	getresuid_id_t ruid, euid, suid;
	struct cred *self = THIS_CRED;
	cred_read(self);
	ruid = (getresuid_id_t)self->c_ruid;
	euid = (getresuid_id_t)self->c_euid;
	suid = (getresuid_id_t)self->c_suid;
	cred_endread(self);
#endif /* !CONFIG_KERNEL_EVERYONE_IS_ROOT */
	COMPILER_WRITE_BARRIER();
	/* Write back results to user-space. */
	if (pruid) {
		validate_writable(pruid, sizeof(*pruid));
		*pruid = ruid;
	}
	if (peuid) {
		validate_writable(peuid, sizeof(*peuid));
		*peuid = euid;
	}
	if (psuid) {
		validate_writable(psuid, sizeof(*psuid));
		*psuid = suid;
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_GETRESUID */

#ifdef __ARCH_WANT_SYSCALL_GETRESUID32
typedef TYPEOF_DEREF(SYSCALL_ARG_TYPE_OF(getresuid32, 0)) getresuid32_id_t;
DEFINE_SYSCALL3(errno_t, getresuid32,
                NCX UNCHECKED getresuid32_id_t *, pruid,
                NCX UNCHECKED getresuid32_id_t *, peuid,
                NCX UNCHECKED getresuid32_id_t *, psuid) {
#ifdef CONFIG_KERNEL_EVERYONE_IS_ROOT
	enum {
		ruid = 0,
		euid = 0,
		suid = 0
	};
#else /* CONFIG_KERNEL_EVERYONE_IS_ROOT */
	getresuid32_id_t ruid, euid, suid;
	struct cred *self = THIS_CRED;
	cred_read(self);
	ruid = (getresuid32_id_t)self->c_ruid;
	euid = (getresuid32_id_t)self->c_euid;
	suid = (getresuid32_id_t)self->c_suid;
	cred_endread(self);
#endif /* !CONFIG_KERNEL_EVERYONE_IS_ROOT */
	COMPILER_WRITE_BARRIER();
	/* Write back results to user-space. */
	if (pruid) {
		validate_writable(pruid, sizeof(*pruid));
		*pruid = ruid;
	}
	if (peuid) {
		validate_writable(peuid, sizeof(*peuid));
		*peuid = euid;
	}
	if (psuid) {
		validate_writable(psuid, sizeof(*psuid));
		*psuid = suid;
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_GETRESUID32 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_GETRESUID
typedef TYPEOF_DEREF(COMPAT_SYSCALL_ARG_TYPE_OF(getresuid, 0)) compat_getresuid_id_t;
DEFINE_COMPAT_SYSCALL3(errno_t, getresuid,
                       NCX UNCHECKED compat_getresuid_id_t *, pruid,
                       NCX UNCHECKED compat_getresuid_id_t *, peuid,
                       NCX UNCHECKED compat_getresuid_id_t *, psuid) {
#ifdef CONFIG_KERNEL_EVERYONE_IS_ROOT
	enum {
		ruid = 0,
		euid = 0,
		suid = 0
	};
#else /* CONFIG_KERNEL_EVERYONE_IS_ROOT */
	compat_getresuid_id_t ruid, euid, suid;
	struct cred *self = THIS_CRED;
	cred_read(self);
	ruid = (compat_getresuid_id_t)self->c_ruid;
	euid = (compat_getresuid_id_t)self->c_euid;
	suid = (compat_getresuid_id_t)self->c_suid;
	cred_endread(self);
#endif /* !CONFIG_KERNEL_EVERYONE_IS_ROOT */
	COMPILER_WRITE_BARRIER();
	/* Write back results to user-space. */
	if (pruid) {
		validate_writable(pruid, sizeof(*pruid));
		*pruid = ruid;
	}
	if (peuid) {
		validate_writable(peuid, sizeof(*peuid));
		*peuid = euid;
	}
	if (psuid) {
		validate_writable(psuid, sizeof(*psuid));
		*psuid = suid;
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_GETRESUID */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_GETRESUID32
typedef TYPEOF_DEREF(COMPAT_SYSCALL_ARG_TYPE_OF(getresuid32, 0)) compat_getresuid32_id_t;
DEFINE_COMPAT_SYSCALL3(errno_t, getresuid32,
                       NCX UNCHECKED compat_getresuid32_id_t *, pruid,
                       NCX UNCHECKED compat_getresuid32_id_t *, peuid,
                       NCX UNCHECKED compat_getresuid32_id_t *, psuid) {
#ifdef CONFIG_KERNEL_EVERYONE_IS_ROOT
	enum {
		ruid = 0,
		euid = 0,
		suid = 0
	};
#else /* CONFIG_KERNEL_EVERYONE_IS_ROOT */
	compat_getresuid32_id_t ruid, euid, suid;
	struct cred *self = THIS_CRED;
	cred_read(self);
	ruid = (compat_getresuid32_id_t)self->c_ruid;
	euid = (compat_getresuid32_id_t)self->c_euid;
	suid = (compat_getresuid32_id_t)self->c_suid;
	cred_endread(self);
#endif /* !CONFIG_KERNEL_EVERYONE_IS_ROOT */
	COMPILER_WRITE_BARRIER();
	/* Write back results to user-space. */
	if (pruid) {
		validate_writable(pruid, sizeof(*pruid));
		*pruid = ruid;
	}
	if (peuid) {
		validate_writable(peuid, sizeof(*peuid));
		*peuid = euid;
	}
	if (psuid) {
		validate_writable(psuid, sizeof(*psuid));
		*psuid = suid;
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_GETRESUID32 */


/************************************************************************/
/* getresgid()                                                          */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_GETRESGID
typedef TYPEOF_DEREF(SYSCALL_ARG_TYPE_OF(getresgid, 0)) getresgid_id_t;
DEFINE_SYSCALL3(errno_t, getresgid,
                NCX UNCHECKED getresgid_id_t *, prgid,
                NCX UNCHECKED getresgid_id_t *, pegid,
                NCX UNCHECKED getresgid_id_t *, psgid) {
#ifdef CONFIG_KERNEL_EVERYONE_IS_ROOT
	enum {
		rgid = 0,
		egid = 0,
		sgid = 0
	};
#else /* CONFIG_KERNEL_EVERYONE_IS_ROOT */
	getresgid_id_t rgid, egid, sgid;
	struct cred *self = THIS_CRED;
	cred_read(self);
	rgid = (getresgid_id_t)self->c_rgid;
	egid = (getresgid_id_t)self->c_egid;
	sgid = (getresgid_id_t)self->c_sgid;
	cred_endread(self);
#endif /* !CONFIG_KERNEL_EVERYONE_IS_ROOT */
	COMPILER_WRITE_BARRIER();
	/* Write back results to user-space. */
	if (prgid) {
		validate_writable(prgid, sizeof(*prgid));
		*prgid = rgid;
	}
	if (pegid) {
		validate_writable(pegid, sizeof(*pegid));
		*pegid = egid;
	}
	if (psgid) {
		validate_writable(psgid, sizeof(*psgid));
		*psgid = sgid;
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_GETRESGID */

#ifdef __ARCH_WANT_SYSCALL_GETRESGID32
typedef TYPEOF_DEREF(SYSCALL_ARG_TYPE_OF(getresgid32, 0)) getresgid32_id_t;
DEFINE_SYSCALL3(errno_t, getresgid32,
                NCX UNCHECKED getresgid32_id_t *, prgid,
                NCX UNCHECKED getresgid32_id_t *, pegid,
                NCX UNCHECKED getresgid32_id_t *, psgid) {
#ifdef CONFIG_KERNEL_EVERYONE_IS_ROOT
	enum {
		rgid = 0,
		egid = 0,
		sgid = 0
	};
#else /* CONFIG_KERNEL_EVERYONE_IS_ROOT */
	getresgid32_id_t rgid, egid, sgid;
	struct cred *self = THIS_CRED;
	cred_read(self);
	rgid = (getresgid32_id_t)self->c_rgid;
	egid = (getresgid32_id_t)self->c_egid;
	sgid = (getresgid32_id_t)self->c_sgid;
	cred_endread(self);
#endif /* !CONFIG_KERNEL_EVERYONE_IS_ROOT */
	COMPILER_WRITE_BARRIER();
	/* Write back results to user-space. */
	if (prgid) {
		validate_writable(prgid, sizeof(*prgid));
		*prgid = rgid;
	}
	if (pegid) {
		validate_writable(pegid, sizeof(*pegid));
		*pegid = egid;
	}
	if (psgid) {
		validate_writable(psgid, sizeof(*psgid));
		*psgid = sgid;
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_GETRESGID32 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_GETRESGID
typedef TYPEOF_DEREF(COMPAT_SYSCALL_ARG_TYPE_OF(getresgid, 0)) compat_getresgid_id_t;
DEFINE_COMPAT_SYSCALL3(errno_t, getresgid,
                       NCX UNCHECKED compat_getresgid_id_t *, prgid,
                       NCX UNCHECKED compat_getresgid_id_t *, pegid,
                       NCX UNCHECKED compat_getresgid_id_t *, psgid) {
#ifdef CONFIG_KERNEL_EVERYONE_IS_ROOT
	enum {
		rgid = 0,
		egid = 0,
		sgid = 0
	};
#else /* CONFIG_KERNEL_EVERYONE_IS_ROOT */
	compat_getresgid_id_t rgid, egid, sgid;
	struct cred *self = THIS_CRED;
	cred_read(self);
	rgid = (compat_getresgid_id_t)self->c_rgid;
	egid = (compat_getresgid_id_t)self->c_egid;
	sgid = (compat_getresgid_id_t)self->c_sgid;
	cred_endread(self);
#endif /* !CONFIG_KERNEL_EVERYONE_IS_ROOT */
	COMPILER_WRITE_BARRIER();
	/* Write back results to user-space. */
	if (prgid) {
		validate_writable(prgid, sizeof(*prgid));
		*prgid = rgid;
	}
	if (pegid) {
		validate_writable(pegid, sizeof(*pegid));
		*pegid = egid;
	}
	if (psgid) {
		validate_writable(psgid, sizeof(*psgid));
		*psgid = sgid;
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_GETRESGID */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_GETRESGID32
typedef TYPEOF_DEREF(COMPAT_SYSCALL_ARG_TYPE_OF(getresgid32, 0)) compat_getresgid32_id_t;
DEFINE_COMPAT_SYSCALL3(errno_t, getresgid32,
                       NCX UNCHECKED compat_getresgid32_id_t *, prgid,
                       NCX UNCHECKED compat_getresgid32_id_t *, pegid,
                       NCX UNCHECKED compat_getresgid32_id_t *, psgid) {
	compat_getresgid32_id_t rgid, egid, sgid;
	struct cred *self = THIS_CRED;
	cred_read(self);
	rgid = (compat_getresgid32_id_t)self->c_rgid;
	egid = (compat_getresgid32_id_t)self->c_egid;
	sgid = (compat_getresgid32_id_t)self->c_sgid;
	cred_endread(self);
	COMPILER_WRITE_BARRIER();
	/* Write back results to user-space. */
	if (prgid) {
		validate_writable(prgid, sizeof(*prgid));
		*prgid = rgid;
	}
	if (pegid) {
		validate_writable(pegid, sizeof(*pegid));
		*pegid = egid;
	}
	if (psgid) {
		validate_writable(psgid, sizeof(*psgid));
		*psgid = sgid;
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_GETRESGID32 */






/************************************************************************/
/* getgroups()                                                          */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_GETGROUPS) ||        \
     defined(__ARCH_WANT_SYSCALL_GETGROUPS32) ||      \
     defined(__ARCH_WANT_COMPAT_SYSCALL_GETGROUPS) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_GETGROUPS32))

extern "C++" {
template<class GID_T>
PRIVATE ssize_t KCALL
sys_getgroups_impl(size_t count, NCX UNCHECKED GID_T *list) {
#ifdef CONFIG_KERNEL_EVERYONE_IS_ROOT
	validate_writablem(list, count, sizeof(GID_T));
	return 0;
#else /* CONFIG_KERNEL_EVERYONE_IS_ROOT */
	size_t result;
	REF struct cred_groups *groups;
	validate_writablem(list, count, sizeof(GID_T));
	groups = arref_get(&THIS_CRED->c_groups);
	FINALLY_DECREF_UNLIKELY(groups);

	/* Deal with the buffer size, as well as the -EINVAL return case. */
	result = groups->cg_count;
	if (result > count) {
		if (count != 0)
			result = (size_t)-EINVAL;
	} else if (sizeof(GID_T) == sizeof(gid_t)) {
		/* Copy to user-space. */
		memcpy(list, groups->cg_groups, result, sizeof(GID_T));
	} else {
		size_t i;
		for (i = 0; i < result; ++i)
			list[i] = (GID_T)groups->cg_groups[i];
	}
	return (ssize_t)result;
#endif /* !CONFIG_KERNEL_EVERYONE_IS_ROOT */
}
#endif /* __ARCH_WANT_SYSCALL_GETGROUPS */

} /* extern "C++" */

#ifdef __ARCH_WANT_SYSCALL_GETGROUPS
DEFINE_SYSCALL2(ssize_t, getgroups, size_t, count,
                NCX UNCHECKED SYSCALL_ARG_TYPE_OF(getgroups, 1), list) {
	return sys_getgroups_impl(count, list);
}
#endif /* __ARCH_WANT_SYSCALL_GETGROUPS */

#ifdef __ARCH_WANT_SYSCALL_GETGROUPS32
DEFINE_SYSCALL2(ssize_t, getgroups32, size_t, count,
                NCX UNCHECKED SYSCALL_ARG_TYPE_OF(getgroups32, 1), list) {
	return sys_getgroups_impl(count, list);
}
#endif /* __ARCH_WANT_SYSCALL_GETGROUPS32 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_GETGROUPS
DEFINE_COMPAT_SYSCALL2(ssize_t, getgroups, size_t, count,
                       NCX UNCHECKED COMPAT_SYSCALL_ARG_TYPE_OF(getgroups, 1), list) {
	return sys_getgroups_impl(count, list);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_GETGROUPS */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_GETGROUPS32
DEFINE_COMPAT_SYSCALL2(ssize_t, getgroups32, size_t, count,
                       NCX UNCHECKED COMPAT_SYSCALL_ARG_TYPE_OF(getgroups32, 1), list) {
	return sys_getgroups_impl(count, list);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_GETGROUPS32 */






/************************************************************************/
/* setgroups()                                                          */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_SETGROUPS) ||        \
     defined(__ARCH_WANT_SYSCALL_SETGROUPS32) ||      \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SETGROUPS) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SETGROUPS32))

extern "C++" {

#ifndef CONFIG_KERNEL_EVERYONE_IS_ROOT
/* Create a new set of groups that may consist of at most `max_ngroups'
 * groups (duplicate groups  are ignored). If  more than  `max_ngroups'
 * unique groups are given, and  the caller doesn't have  `CAP_SETGID',
 * an `E_INSUFFICIENT_RIGHTS' exception is thrown. */
template<class GID_T>
PRIVATE ATTR_RETNONNULL WUNUSED REF struct cred_groups *KCALL
cred_groups_new(NCX UNCHECKED GID_T const *groups,
                size_t ngroups, size_t max_ngroups)
		THROWS(E_SEGFAULT, E_BADALLOC, E_INSUFFICIENT_RIGHTS) {
	size_t count;
	REF struct cred_groups *result;
	validate_readablem(groups, ngroups, sizeof(GID_T));
	if (max_ngroups > ngroups)
		max_ngroups = ngroups;

	/* Allocate the new groups controller. */
	result = (REF struct cred_groups *)kmalloc(offsetof(struct cred_groups, cg_groups) +
	                                           max_ngroups * sizeof(gid_t),
	                                           GFP_NORMAL);
	TRY {
		size_t i;
		count = 0;
		for (i = 0; i < ngroups; ++i) {
			size_t lo, hi;
			gid_t newgid = atomic_read(&groups[i]);
			/* Sorted-insert into the new list, ignoring duplicates. When exceeding
			 * `max_ngroups' during this, require that the caller has `CAP_SETGID'. */
			lo = 0;
			hi = count;
			while (lo < hi) {
				size_t j = (lo + hi) / 2;
				if (newgid < result->cg_groups[j]) {
					hi = j;
				} else if (newgid > result->cg_groups[j]) {
					lo = j + 1;
				} else {
					goto next_gid;
				}
			}
			/* Insert into `lo' */
			if (count > max_ngroups) {
				require(CAP_SETGID);
				result = (REF struct cred_groups *)krealloc(result,
				                                            offsetof(struct cred_groups, cg_groups) +
				                                            (count + 1) * sizeof(gid_t),
				                                            GFP_NORMAL);
				/* Remember available space. */
				max_ngroups = (kmalloc_usable_size(result) -
				               offsetof(struct cred_groups, cg_groups)) /
				              sizeof(gid_t);
				assert(max_ngroups > count);
			}

			/* Do the insert at the proper position. */
			memmoveup(&result->cg_groups[lo + 1],
			          &result->cg_groups[lo],
			          count - lo, sizeof(gid_t));
			result->cg_groups[lo] = newgid;
			++count;
next_gid:
			;
		}
	} EXCEPT {
		kfree(result);
		RETHROW();
	}

	/* Try to free unused memory. */
	if (count < max_ngroups) {
		REF struct cred_groups *new_result;
		new_result = (REF struct cred_groups *)krealloc_nx(result,
		                                                   offsetof(struct cred_groups, cg_groups) +
		                                                   max_ngroups * sizeof(gid_t),
		                                                   GFP_NORMAL);
		if likely(new_result)
			result = new_result;
	}

	/* Fill in missing fields. */
	result->cg_count  = count;
	result->cg_refcnt = 1;
	return result;
}
#endif /* !CONFIG_KERNEL_EVERYONE_IS_ROOT */

template<class GID_T>
PRIVATE errno_t KCALL
sys_setgroups_impl(size_t count, NCX UNCHECKED GID_T const *groups) {
	REF struct cred_groups *set;
	size_t max;
	set = arref_get(&THIS_CRED->c_groups);
	max = set->cg_count;
	decref_unlikely(set);
	set = cred_groups_new(groups, count, max);
	TRY {
		cred_setgroups(set);
	} EXCEPT {
		destroy(set);
		RETHROW();
	}
	return -EOK;
}

} /* extern "C++" */

#ifdef __ARCH_WANT_SYSCALL_SETGROUPS
DEFINE_SYSCALL2(errno_t, setgroups, size_t, count,
                NCX UNCHECKED SYSCALL_ARG_TYPE_OF(setgroups, 1), list) {
	return sys_setgroups_impl(count, list);
}
#endif /* __ARCH_WANT_SYSCALL_SETGROUPS */

#ifdef __ARCH_WANT_SYSCALL_SETGROUPS32
DEFINE_SYSCALL2(errno_t, setgroups32, size_t, count,
                NCX UNCHECKED SYSCALL_ARG_TYPE_OF(setgroups32, 1), list) {
	return sys_setgroups_impl(count, list);
}
#endif /* __ARCH_WANT_SYSCALL_SETGROUPS32 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SETGROUPS
DEFINE_COMPAT_SYSCALL2(errno_t, setgroups, size_t, count,
                       NCX UNCHECKED COMPAT_SYSCALL_ARG_TYPE_OF(setgroups, 1), list) {
	return sys_setgroups_impl(count, list);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SETGROUPS */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SETGROUPS32
DEFINE_COMPAT_SYSCALL2(errno_t, setgroups32, size_t, count,
                       NCX UNCHECKED COMPAT_SYSCALL_ARG_TYPE_OF(setgroups32, 1), list) {
	return sys_setgroups_impl(count, list);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SETGROUPS32 */
#endif /* ... */






/* TODO: __ARCH_WANT_SYSCALL_CAPGET */
/* TODO: __ARCH_WANT_SYSCALL_CAPSET */


DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_CRED_C */
