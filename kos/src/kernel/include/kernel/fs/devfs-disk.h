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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_DEVFS_DISK_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_DEVFS_DISK_H 1

#include <kernel/compiler.h>

#include <kernel/fs/devfs.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>

#include <bits/crt/format-printer.h>
#include <kos/lockop.h>
#include <kos/sched/shared-rwlock.h>

/* API for defining rules by which disk-devices can be  identified.
 * The rules defined by this API form the /dev/disk/by-xxx folders. */

#ifdef __CC__
DECL_BEGIN

struct blkdev;
struct devdiskruledir;

/* Lookup a block-device for this rule, given its name (Used to implement `dno_lookup')
 * @return: NULL: No known block device is being named. */
typedef WUNUSED_T NONNULL_T((1, 2)) REF struct blkdev *
(KCALL *devdiskruledir_byname_t)(struct devdiskruledir *__restrict self,
                                 struct flookup_info *__restrict info);

/* Print the name for a given device (Used to implement `dno_enum')
 * When `dev' shouldn't appear in the directory `self', return `0'.
 * @param: variant: When a device is listed with multiple names,  the
 *                  `variant' number (which  starts at  `0') is  used
 *                  to enumerate the different names. Enumation stops
 *                  on the first variant that returns `0'. */
typedef WUNUSED_T NONNULL_T((1, 2, 4)) ssize_t
(KCALL *devdiskruledir_toname_t)(struct devdiskruledir *__restrict self,
                                 __pformatprinter printer, void *arg,
                                 struct blkdev *__restrict dev,
                                 uintptr_t variant);



/* Directory object for /dev/disk/by-xxx folders.
 * This is the main controller for disk rules, and defines callback
 * for converting between  block-devices and the  filenames of  the
 * symbolic links that should appear in the relevant by-xxx folder. */
struct devdiskruledir
#ifndef __WANT_FS_INLINE_STRUCTURES
    : fdirnode
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct fdirnode         ddrd_dir;       /* Underlying directory. */
#endif /* __WANT_FS_INLINE_STRUCTURES */
	char                   _ddrd_prefix[8]; /* [const] The string "../../\0" */
	devdiskruledir_byname_t ddrd_byname;    /* [1..1][const] Lookup a block-device for this rule, given its name. */
	devdiskruledir_toname_t ddrd_toname;    /* [1..1][const] Print the name of a given device. */
	REF struct driver      *ddrd_drv;       /* [1..1][const] Associated driver. */
};

/* Directory entry type for /dev/disk/by-xxx folders themself. */
struct devdiskrule {
	REF struct devdiskruledir *ddre_rule; /* [1..1][const] Associated rule directory. */
	union {
		struct lockop         _ddre_lop;  /* Used internally by `devdiskrule_delete()' */
		struct postlockop     _ddre_plop; /* Used internally by `devdiskrule_delete()' */
	};
#ifndef __WANT_FS_INLINE_STRUCTURES
	struct fdirent             ddre_ent;  /* Underlying directory entry. */
#else /* !__WANT_FS_INLINE_STRUCTURES */
	/* Work-around because g++ can't init nested flexible arrays. */
	WEAK refcnt_t                           fd_refcnt;   /* ... */
	struct fdirent_ops const               *fd_ops;      /* ... */
	ino_t                                   fd_ino;      /* ... */
	uintptr_t                               fd_hash;     /* ... */
	u16                                     fd_namelen;  /* ... */
	unsigned char                           fd_type;     /* ... */
	COMPILER_FLEXIBLE_ARRAY(/*utf-8*/ char, fd_name);    /* ... */
#endif /* __WANT_FS_INLINE_STRUCTURES */
};

#define __devdiskrule_destroy(self) fdirent_destroy(devdiskrule_asdirent(self))
#ifdef __WANT_FS_INLINE_STRUCTURES
#define devdiskrule_asdirent(self)   ((struct fdirent *)&(self)->fd_refcnt)
#define devdiskrule_fromdirent(self) COMPILER_CONTAINER_OF(&(self)->fd_refcnt, struct devdiskrule, fd_refcnt)
DEFINE_REFCNT_FUNCTIONS(struct devdiskrule, fd_refcnt, __devdiskrule_destroy)
#else /* __WANT_FS_INLINE_STRUCTURES */
#define devdiskrule_asdirent(self) (&(self)->ddre_ent)
#define devdiskrule_fromdirent(self) COMPILER_CONTAINER_OF(self, struct devdiskrule, ddre_ent)
DEFINE_REFCNT_FUNCTIONS(struct devdiskrule, ddre_ent.fd_refcnt, __devdiskrule_destroy)
#endif /* !__WANT_FS_INLINE_STRUCTURES */


/* Default operators used for `devdiskrule' and `devdiskruledir'
 * WARNING: Sub-classes are allowed to override any of these! */
DATDEF struct fdirent_ops const devdiskrule_ops;
DATDEF struct fdirnode_ops const devdiskruledir_ops;

/* Default operators for `devdiskruledir_ops' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL devdiskruledir_v_destroy)(struct mfile *__restrict self);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
devdiskruledir_v_lookup(struct fdirnode *__restrict self,
                        struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT, E_IOERROR, ...);
FUNDEF BLOCKING NONNULL((1)) void KCALL
devdiskruledir_v_enum(struct fdirenum *__restrict result)
		THROWS(E_IOERROR, ...);
DATDEF byte_t __devdiskruledir_v_enumsz[] ASMNAME("devdiskruledir_v_enumsz");
#define devdiskruledir_v_enumsz ((size_t)__devdiskruledir_v_enumsz)


/* Default list of /dev/disk/by-xxx rules.
 * These rules must always be included in the current list of rules. */
DATDEF REF struct devdiskrule *const devdiskrules_default_list[];
DATDEF byte_t __devdiskrules_default_size[] ASMNAME("devdiskrules_default_size");
#define devdiskrules_default_size ((size_t)__devdiskrules_default_size)

/* [1..1][0..devdiskrules_size][owned_if(!= devdiskrules_default_list)][lock(devdiskrules_lock)]
 * List of device disk rules. Always sorted lexicographically ascendingly, based on rule  names. */
DATDEF REF struct devdiskrule **devdiskrules_list;
DATDEF size_t /*             */ devdiskrules_size;

/* Lock for `devdiskrules_list' and `devdiskrules_size' */
DATDEF struct shared_rwlock devdiskrules_lock;

/* Lock operators for `devdiskrules_lock' */
DATDEF struct lockop_slist devdiskrules_lops;

/* Helpers for accessing `devdiskrules_lock' */
#define /*        */ _devdiskrules_reap()        _lockop_reap_shared_rwlock(&devdiskrules_lops, &devdiskrules_lock)
#define /*        */ devdiskrules_reap()         lockop_reap_shared_rwlock(&devdiskrules_lops, &devdiskrules_lock)
#define /*        */ devdiskrules_mustreap()     lockop_mustreap(&devdiskrules_lops)
#define /*BLOCKING*/ devdiskrules_write()        shared_rwlock_write(&devdiskrules_lock)
#define /*BLOCKING*/ devdiskrules_write_nx()     shared_rwlock_write_nx(&devdiskrules_lock)
#define /*        */ devdiskrules_trywrite()     shared_rwlock_trywrite(&devdiskrules_lock)
#define /*        */ devdiskrules_endwrite()     (shared_rwlock_endwrite(&devdiskrules_lock), devdiskrules_reap())
#define /*        */ _devdiskrules_endwrite()    shared_rwlock_endwrite(&devdiskrules_lock)
#define /*BLOCKING*/ devdiskrules_read()         shared_rwlock_read(&devdiskrules_lock)
#define /*BLOCKING*/ devdiskrules_read_nx()      shared_rwlock_read_nx(&devdiskrules_lock)
#define /*        */ devdiskrules_tryread()      shared_rwlock_tryread(&devdiskrules_lock)
#define /*        */ _devdiskrules_endread()     shared_rwlock_endread(&devdiskrules_lock)
#define /*        */ devdiskrules_endread()      (void)(shared_rwlock_endread(&devdiskrules_lock) && (devdiskrules_reap(), 0))
#define /*        */ _devdiskrules_end()         shared_rwlock_end(&devdiskrules_lock)
#define /*        */ devdiskrules_end()          (void)(shared_rwlock_end(&devdiskrules_lock) && (devdiskrules_reap(), 0))
#define /*BLOCKING*/ devdiskrules_upgrade()      shared_rwlock_upgrade(&devdiskrules_lock)
#define /*        */ devdiskrules_tryupgrade()   shared_rwlock_tryupgrade(&devdiskrules_lock)
#define /*        */ devdiskrules_downgrade()    shared_rwlock_downgrade(&devdiskrules_lock)
#define /*        */ devdiskrules_reading()      shared_rwlock_reading(&devdiskrules_lock)
#define /*        */ devdiskrules_writing()      shared_rwlock_writing(&devdiskrules_lock)
#define /*        */ devdiskrules_canread()      shared_rwlock_canread(&devdiskrules_lock)
#define /*        */ devdiskrules_canwrite()     shared_rwlock_canwrite(&devdiskrules_lock)
#define /*BLOCKING*/ devdiskrules_waitread()     shared_rwlock_waitread(&devdiskrules_lock)
#define /*BLOCKING*/ devdiskrules_waitwrite()    shared_rwlock_waitwrite(&devdiskrules_lock)
#define /*BLOCKING*/ devdiskrules_waitread_nx()  shared_rwlock_waitread_nx(&devdiskrules_lock)
#define /*BLOCKING*/ devdiskrules_waitwrite_nx() shared_rwlock_waitwrite_nx(&devdiskrules_lock)





/************************************************************************/
/* High-level /dev/disk rule API                                        */
/************************************************************************/

/* Allocate a new disk rule object. The caller must still initialize:
 * - return->ddre_rule->ddrd_drv    = incref(&drv_self); # Must _always_ be done!
 * - return->ddre_rule->ddrd_byname = ...;               # Only mandatory if `devdiskrule_register()' is called
 * - return->ddre_rule->ddrd_toname = ...;               # Only mandatory if `devdiskrule_register()' is called
 * - return->ddre_rule->...;                             # Sub-class specific fields
 * @param: sizeof_devdiskruledir: sizeof(struct MY_SUBCLASS_FOR_devdiskruledir)
 * @param: namef: The name of the rule.  Should probably include the "by-"  prefix.
 *                Note that this string is interpreted as a printf-format argument.
 * HINT: Those cases where the returned object should be destroyed can simply  be
 *       handled by filling in `ddre_rule->ddrd_drv' and doing `destroy(return)'. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) REF struct devdiskrule *VCALL
devdiskrule_allocf(size_t sizeof_devdiskruledir,
                   char const *__restrict namef, ...)
		THROWS(E_BADALLOC, E_FSERROR_ILLEGAL_PATH);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) REF struct devdiskrule *FCALL
devdiskrule_vallocf(size_t sizeof_devdiskruledir,
                    char const *__restrict namef,
                    __builtin_va_list args)
		THROWS(E_BADALLOC, E_FSERROR_ILLEGAL_PATH);


/* Register a  fully initialized  /dev/disk/by-xxx rule  object.
 * Once registered, the object can be unregistered exactly  once
 * via `devdiskrule_delete()'. Once that has been done, you must
 * _NOT_ try to register it once again!
 * @throws: E_FSERROR_FILE_ALREADY_EXISTS: `self->ddre_ent.fd_name' has already been defined */
FUNDEF BLOCKING NONNULL((1)) void FCALL
devdiskrule_register(struct devdiskrule *__restrict self)
		THROWS(E_WOULDBLOCK, E_FSERROR_FILE_ALREADY_EXISTS);

/* Delete  a given disk rule object from  the list of known disk rules.
 * If necessary, this function operates asynchronously to remove `self'
 * from  the  list of  known  rules, before  decref()-ing  `self'. This
 * function may only be called once for any given `self'. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL devdiskrule_delete)(struct devdiskrule *__restrict self);


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_DEVFS_DISK_H */
