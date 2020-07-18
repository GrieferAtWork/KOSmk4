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
#ifndef GUARD_KERNEL_SRC_SCHED_CRED_C
#define GUARD_KERNEL_SRC_SCHED_CRED_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

/* Credential checking. */

#include <kernel/compiler.h>

#include <sched/cred.h>
#ifndef CONFIG_EVERYONE_IS_ROOT

#include <fs/node.h>
#include <kernel/driver-param.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/types.h>
#include <kernel/vm.h>

#include <hybrid/atomic.h>
#include <hybrid/sequence/bsearch.h>

#include <sys/stat.h>

#include <assert.h>
#include <sched.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

DECL_BEGIN


/* Destroy the given credentials controller. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL cred_destroy)(struct cred *__restrict self) {
	kfree(self->c_groups);
	kfree(self);
}

/* Clone the given credentials controller `self' and return the copy */
PUBLIC WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct cred *FCALL
cred_clone(struct cred *__restrict self) THROWS(E_BADALLOC) {
	REF struct cred *result;
	result = (REF struct cred *)kmalloc(sizeof(struct cred),
	                                    GFP_NORMAL);
	TRY {
		sync_read(&self->c_lock);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
again:
	/* Copy static credentials data. */
	memcpy((byte_t *)result + offsetafter(struct cred, c_lock),
	       (byte_t *)self + offsetafter(struct cred, c_lock),
	       sizeof(struct cred) - offsetafter(struct cred, c_lock));
	/* Check if we need to duplicate the supplemental GID vector. */
	if (result->c_ngroups) {
		gid_t *groupvec;
		assert(self->c_groups);
		groupvec = (gid_t *)kmalloc_nx(result->c_ngroups *
		                               sizeof(gid_t),
		                               GFP_ATOMIC);
		if unlikely(!groupvec) {
			sync_endread(&self->c_lock);
			TRY {
				groupvec = (gid_t *)kmalloc(result->c_ngroups *
				                            sizeof(gid_t),
				                            GFP_NORMAL);
				TRY {
					sync_read(&self->c_lock);
				} EXCEPT {
					kfree(groupvec);
					RETHROW();
				}
			} EXCEPT {
				kfree(result);
				RETHROW();
			}
			if unlikely(self->c_ngroups != result->c_ngroups) {
				kfree(groupvec);
				goto again;
			}
		}
		result->c_groups = groupvec;
		memcpy(groupvec,
		       self->c_groups,
		       result->c_ngroups,
		       sizeof(gid_t));
	} else {
		result->c_groups = NULL;
	}
	sync_endread(&self->c_lock);
	result->c_refcnt = 1;
	atomic_rwlock_init(&result->c_lock);
	return result;
}




/* Generic kernel credentials / credentials for /bin/init */
PUBLIC struct cred cred_kernel = {
	/* .c_refcnt          = */ 2, /* +1: `cred_kernel', +1: FORTASK(&_boottask, this_cred) */
	/* .c_lock            = */ ATOMIC_RWLOCK_INIT,
	/* .c_ruid            = */ (uid_t)0,
	/* .c_rgid            = */ (gid_t)0,
	/* .c_euid            = */ (uid_t)0,
	/* .c_egid            = */ (gid_t)0,
	/* .c_suid            = */ (uid_t)0,
	/* .c_sgid            = */ (gid_t)0,
	/* .c_fsuid           = */ (uid_t)0,
	/* .c_fsgid           = */ (gid_t)0,
	/* .c_ngroups         = */ 0,
	/* .c_groups          = */ NULL,
	/* .c_cap_permitted   = */ CREDCAP_INIT_FULL,
	/* .c_cap_inheritable = */ CREDCAP_INIT_FULL,
	/* .c_cap_effective   = */ CREDCAP_INIT_FULL,
	/* .c_cap_bounding    = */ CREDCAP_INIT_FULL,
	/* .c_cap_ambient     = */ CREDCAP_INIT_FULL,
};

/* [1..1] Per-thread filesystem information.
 * NOTE: Initialized to NULL. - Must be initialized before the task is started. */
PUBLIC ATTR_PERTASK REF struct cred *this_cred = NULL;

DEFINE_PERTASK_FINI(fini_this_cred);
PRIVATE ATTR_USED NONNULL((1)) NOBLOCK void
NOTHROW(KCALL fini_this_cred)(struct task *__restrict self) {
	xdecref(FORTASK(self, this_cred));
}

DEFINE_PERTASK_CLONE(clone_this_cred);
INTERN NONNULL((1)) void KCALL
clone_this_cred(struct task *__restrict new_thread, uintptr_t flags) {
	struct cred *self;
	self = THIS_CRED;
	if (flags & CLONE_CRED) {
		incref(self); /* Re-use the same credentials. */
	} else {
		/* Clone the old credentials, as they appear in their current state. */
		self = cred_clone(self);
	}
	assert(!FORTASK(new_thread, this_cred));
	FORTASK(new_thread, this_cred) = self; /* Inherit reference */
}


/* Check if the calling thread has a given capability
 * `capno' (one of `CAP_*' from <kos/capability.h>) */
PUBLIC NOBLOCK ATTR_PURE __BOOL
NOTHROW(FCALL capable)(syscall_slong_t capno) {
	return credcap_capable(&THIS_CRED->c_cap_effective, capno);
}

/* Ensure that the calling thread is `capable(capno)'
 * If the calling thread isn't, throw an `E_INSUFFICIENT_RIGHTS' exception */
PUBLIC void FCALL require(syscall_slong_t capno)
		THROWS(E_INSUFFICIENT_RIGHTS) {
	if (!capable(capno))
		THROW(E_INSUFFICIENT_RIGHTS, capno);
}



/* Get the calling thread's real user ID */
PUBLIC NOBLOCK uid_t NOTHROW(FCALL cred_getruid)(void) {
	return ATOMIC_READ(THIS_CRED->c_ruid);
}

/* Get the calling thread's real group ID */
PUBLIC NOBLOCK gid_t NOTHROW(FCALL cred_getrgid)(void) {
	return ATOMIC_READ(THIS_CRED->c_rgid);
}

/* Get the calling thread's effective user ID */
PUBLIC NOBLOCK uid_t NOTHROW(FCALL cred_geteuid)(void) {
	return ATOMIC_READ(THIS_CRED->c_euid);
}

/* Get the calling thread's effective group ID */
PUBLIC NOBLOCK gid_t NOTHROW(FCALL cred_getegid)(void) {
	return ATOMIC_READ(THIS_CRED->c_egid);
}


/* Get the calling thread's saved user ID */
PUBLIC NOBLOCK uid_t NOTHROW(FCALL cred_getsuid)(void) {
	return ATOMIC_READ(THIS_CRED->c_suid);
}

/* Get the calling thread's saved group ID */
PUBLIC NOBLOCK gid_t NOTHROW(FCALL cred_getsgid)(void) {
	return ATOMIC_READ(THIS_CRED->c_sgid);
}

/* Get the calling thread's filesystem user ID */
PUBLIC NOBLOCK uid_t NOTHROW(FCALL cred_getfsuid)(void) {
	return ATOMIC_READ(THIS_CRED->c_fsuid);
}

/* Get the calling thread's filesystem group ID */
PUBLIC NOBLOCK gid_t NOTHROW(FCALL cred_getfsgid)(void) {
	return ATOMIC_READ(THIS_CRED->c_fsgid);
}


/* Check if the calling thread is considered to be apart of the given group `gid' */
PUBLIC WUNUSED __BOOL FCALL cred_isfsgroupmember(gid_t gid) {
	size_t i;
	struct cred *self = THIS_CRED;
	__BOOL result;
	if (ATOMIC_READ(THIS_CRED->c_fsgid) == gid)
		return 1;
	result = 0;
	sync_read(&self->c_lock);
	BSEARCH(i, self->c_groups, self->c_ngroups, , gid) {
		result = 1;
	}
	sync_endread(&self->c_lock);
	return result;
}


struct file_creds {
	struct credcap fc_permitted;   /* ... */
	struct credcap fc_inheritable; /* ... */
	bool           fc_effective;   /* ... */
};

/* Try to load file credentials from `program_inode' */
PRIVATE WUNUSED NONNULL((1, 2)) bool KCALL
inode_get_file_creds(struct inode *__restrict program_inode,
                     struct file_creds *__restrict result) {
	(void)program_inode;
	(void)result;
	COMPILER_IMPURE();
	/* TODO */
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
NOTHROW(FCALL cred_turnoff_special_fsuid_caps)(struct cred *__restrict self) {
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
cred_onexec(struct inode *__restrict program_inode)
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
	 *       since we already know that no-one can modify it anymore! */
	new_euid = self->c_euid;
	if (!self->c_no_new_privs &&
	    !(program_inode->i_super->s_flags & SUPERBLOCK_FNOSUID)) {
		/* Check for set-user-id/set-group-id */
		inode_loadattr(program_inode);
		if (program_inode->i_filemode & S_ISUID) {
			new_euid = program_inode->i_fileuid;
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
					cred_turnoff_special_fsuid_caps(self);
				} else if (self->c_fsuid != 0 && new_euid == 0) {
					/* Copy from permitted to effective caps */
					cred_restore_special_fsuid_caps(self);
				}
			}
			self->c_euid  = new_euid;
			self->c_fsuid = new_euid;
			bzero(&self->c_cap_ambient, sizeof(self->c_cap_ambient));
		}
		if ((program_inode->i_filemode & (S_ISGID | S_IXGRP)) == (S_ISGID | S_IXGRP)) {
			self->c_egid  = program_inode->i_filegid;
			self->c_fsgid = program_inode->i_filegid;
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
		/* Try to load credentials from the given `program_inode' */
		if (!inode_get_file_creds(program_inode, &fcreds))
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
	sync_write(&self->c_lock);
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
		sync_endwrite(&self->c_lock);
		/* Only throw an insufficient-rights exception
		 * if the call wouldn't have been a no-op */
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
			cred_turnoff_special_fsuid_caps(self);
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
	sync_endwrite(&self->c_lock);
}

PUBLIC void FCALL
cred_setgid(gid_t rgid, gid_t egid,
            gid_t sgid, gid_t fsgid,
            bool chk_rights)
		THROWS(E_INSUFFICIENT_RIGHTS) {
	struct cred *self = THIS_CRED;
	sync_write(&self->c_lock);
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
		sync_endwrite(&self->c_lock);
		/* Only throw an insufficient-rights exception
		 * if the call wouldn't have been a no-op */
		if (!is_a_noop)
			THROW(E_INSUFFICIENT_RIGHTS, CAP_SETGID);
		return;
	}
	/* Fill in the new user IDs. */
	self->c_rgid  = rgid;
	self->c_egid  = egid;
	self->c_sgid  = sgid;
	self->c_fsgid = fsgid;
	sync_endwrite(&self->c_lock);
}


PRIVATE ATTR_PURE int __LIBCCALL
compare_gid(void const *a, void const *b) {
	typedef __CRT_PRIVATE_SINT(__SIZEOF_GID_T__) sgid_t;
	return *(sgid_t *)a - *(sgid_t *)b;

}

/* Sort `vec', remove duplicate, and return the new (possibly lower) # of entries. */
PRIVATE NONNULL((1)) size_t FCALL
sort_groups_and_remove_duplicates(gid_t *__restrict vec,
                                  size_t cnt) {
	size_t i;
	/* Sort the vector. */
	qsort(vec, cnt, sizeof(gid_t), &compare_gid);
	/* Remove duplicates. */
	for (i = 0; i + 1 < cnt; ++i) {
		gid_t cur = vec[i];
		if (vec[i + 1] == cur) {
			size_t dups = 1;
			while (i + dups + 1 < cnt &&
			       vec[i + dups + 1] == cur)
				++dups;
			/* Remove duplicates */
			cnt -= dups;
			memmovedown(&vec[i + 1],
			            &vec[i + 2],
			            cnt - (i + 1),
			            sizeof(gid_t));
		}
	}
	return cnt;
}


/* Set the list of supplementary group ids of the calling thread. */
PUBLIC void FCALL
cred_setgroups(size_t ngroups,
               USER CHECKED gid_t const *groups,
               bool chk_rights)
		THROWS(E_INSUFFICIENT_RIGHTS, E_SEGFAULT) {
	size_t i;
	gid_t *old_groups;
	gid_t *new_groups;
	struct cred *self = THIS_CRED;
	if (ngroups > ATOMIC_READ(self->c_ngroups)) {
		/* NOTE: Technically, `groups[]' may contain duplicate entries,
		 *       such that the effective group sets are actually identical,
		 *       however we also have to keep in mind that `ngroups' might
		 *       be a maliciously big value that could result in the kernel
		 *       running out of heap memory. As such, a non-malicious user
		 *       program that wants to rely on setting the same set of groups
		 *       as had already been set before, should also take tare to
		 *       ensure that their list of groups doesn't contain any duplicate
		 *       entires! */
		if (chk_rights)
			require(CAP_SETGID);
	}
	/* Allocate a new set of groups. */
	new_groups = (gid_t *)kmalloc(ngroups * sizeof(gid_t),
	                              GFP_NORMAL);
	TRY {
		/* Copy groups from user-space. */
		memcpy(new_groups, groups, ngroups, sizeof(gid_t));
	} EXCEPT {
		kfree(new_groups);
		RETHROW();
	}
	/* Sort the user-provided list of groups and remove duplicates. */
	i = sort_groups_and_remove_duplicates(new_groups, ngroups);
	assert(i <= ngroups);
	if (i < ngroups) {
		/* Try to release unused memory. */
		gid_t *new_groups_trunc;
		ngroups          = i;
		new_groups_trunc = (gid_t *)krealloc_nx(new_groups,
		                                        ngroups *
		                                        sizeof(gid_t),
		                                        GFP_NORMAL);
		if likely(new_groups_trunc)
			new_groups = new_groups_trunc;
	}
	/* Get down to the meat: Check for differences (there are any,
	 * then we have to `require(CAP_SETGID)') */
	sync_write(&self->c_lock);
	old_groups = self->c_groups;
	if (ngroups != self->c_ngroups) {
do_set_new_group:
		if unlikely(chk_rights && !credcap_capable(&self->c_cap_effective, CAP_SETGID)) {
			/* Not allowed! */
			sync_endwrite(&self->c_lock);
			kfree(new_groups);
			THROW(E_INSUFFICIENT_RIGHTS, CAP_SETGID);
		}
		self->c_groups  = new_groups;
		self->c_ngroups = ngroups;
		sync_endwrite(&self->c_lock);
		kfree(old_groups);
		return;
	}
	/* Check if any of the groups has changed.
	 * Since we can assume that both group lists are sorted,
	 * as well as not contain any duplicate entires, we can
	 * simply use memcmp() for this! */
#if __SIZEOF_GID_T__ == 4
	if (memcmpl(old_groups, new_groups, ngroups) != 0)
		goto do_set_new_group;
#elif __SIZEOF_GID_T__ == 2
	if (memcmpw(old_groups, new_groups, ngroups) != 0)
		goto do_set_new_group;
#elif __SIZEOF_GID_T__ == 8
	if (memcmpq(old_groups, new_groups, ngroups) != 0)
		goto do_set_new_group;
#else /* __SIZEOF_GID_T__ == ... */
	if (memcmp(old_groups, new_groups, ngroups * sizeof(gid_t)) != 0)
		goto do_set_new_group;
#endif /* __SIZEOF_GID_T__ != ... */
	sync_endwrite(&self->c_lock);
	/* Groups have remained unchanged. -> Nothing to do here! */
	kfree(new_groups);
}





PUBLIC void KCALL
cred_require_hwio(void) THROWS(E_INSUFFICIENT_RIGHTS) {
	/* TODO */
}

PUBLIC void KCALL
cred_require_hwio_r(port_t from, port_t num)
		THROWS(E_INSUFFICIENT_RIGHTS) {
	(void)from;
	(void)num;
	/* TODO */
}

DECL_END
#endif /* !CONFIG_EVERYONE_IS_ROOT */

#endif /* !GUARD_KERNEL_SRC_SCHED_CRED_C */
