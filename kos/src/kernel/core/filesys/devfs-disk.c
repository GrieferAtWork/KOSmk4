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
#ifndef GUARD_KERNEL_CORE_FILESYS_DEVFS_DISK_C
#define GUARD_KERNEL_CORE_FILESYS_DEVFS_DISK_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/fs/blkdev.h>
#include <kernel/fs/devfs-disk.h>
#include <kernel/fs/devfs-spec.h>
#include <kernel/fs/devfs.h>
#include <kernel/malloc.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/overflow.h>
#include <hybrid/sched/atomic-lock.h>

#include <asm/defsym.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**/
#include "devfs-spec.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL devdiskrule_v_destroy)(struct fdirent *__restrict self) {
	struct devdiskrule *me = devdiskrule_fromdirent(self);
	decref_likely(me->ddre_rule);
	kfree(me);
}

PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
devdiskrule_v_opennode(struct fdirent *__restrict self,
                       struct fdirnode *__restrict UNUSED(dir))
		THROWS(E_BADALLOC, E_IOERROR, ...) {
	struct devdiskrule *me = devdiskrule_fromdirent(self);
	return mfile_asnode(incref(me->ddre_rule));
}

/* Default operators used for `devdiskrule' and `devdiskruledir'
 * WARNING: Sub-classes are allowed to override any of these! */
PUBLIC_CONST struct fdirent_ops const devdiskrule_ops = {
	.fdo_destroy  = &devdiskrule_v_destroy,
	.fdo_opennode = &devdiskrule_v_opennode,
};

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL devdiskruledir_v_destroy)(struct mfile *__restrict self) {
	struct devdiskruledir *me;
	me = (struct devdiskruledir *)mfile_asdir(self);
	decref_unlikely(me->ddrd_drv);
	kfree(me);
}

#define devdiskrule_mustescape(ch) \
	(!isalnum(ch) && !strchr("_-.,+", ch))



/* Unescape the filename encoded in `info', or return `NULL' if `info' is invalid.
 * Of the returned  directory entry,  only the following  fields are  initialized:
 *  - dld_ent.fd_namelen
 *  - dld_ent.fd_name     # Including a trailing NUL! */
PRIVATE WUNUSED NONNULL((1)) struct devicelink_dirent *FCALL
devdiskruledir_unescape(struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT, E_BADALLOC) {
	struct devicelink_dirent *result;
	NCX char const *src, *end;
	char *dst;
	if unlikely(!info->flu_namelen)
		return NULL;
	result = (struct devicelink_dirent *)kmalloc_nx(offsetof(struct devicelink_dirent, dld_ent.fd_name) +
	                                                (info->flu_namelen + 1) * sizeof(char),
	                                                GFP_NORMAL);

	/* Setup pointers */
	dst = result->dld_ent.fd_name;
	src = info->flu_name;
	end = src + info->flu_namelen;
	TRY {
		while (src < end) {
			char ch = *src++;
			COMPILER_READ_BARRIER();
			if (ch == '\\') {
				uint8_t b;
				if unlikely(src >= end)
					goto err_r;
				ch = *src++;
				if unlikely(!(ch == 'x' || (ch == 'X' && (info->flu_flags & AT_DOSPATH))))
					goto err_r;
				if unlikely(src >= end)
					goto err_r;
				ch = *src++;
				if (info->flu_flags & AT_DOSPATH)
					ch = tolower(ch);
				if (isdigit(ch)) {
					b = ch - '0';
				} else if (ch >= 'a' && ch <= 'f') {
					b = 10 + ch - 'a';
				} else {
					goto err_r;
				}
				if unlikely(src >= end)
					goto err_r;
				ch = *src++;
				b <<= 4;
				if (info->flu_flags & AT_DOSPATH)
					ch = tolower(ch);
				if (isdigit(ch)) {
					b |= ch - '0';
				} else if (ch >= 'a' && ch <= 'f') {
					b |= 10 + ch - 'a';
				} else {
					goto err_r;
				}
				if (b == 0 || !devdiskrule_mustescape(b))
					goto err_r;
				*dst++ = b;
			} else {
				if (devdiskrule_mustescape(ch))
					goto err_r;
				*dst++ = ch;
			}
		}
	} EXCEPT {
		kfree(result);
		RETHROW();
	}

	/* Finalize the filename. */
	*dst = '\0';
	result->dld_ent.fd_namelen = (u16)(size_t)(dst - result->dld_ent.fd_name);

	/* Free unused data. */
	if unlikely(result->dld_ent.fd_namelen < info->flu_namelen) {
		struct devicelink_dirent *newent;
		newent = (struct devicelink_dirent *)krealloc_nx(result,
		                                                 offsetof(struct devicelink_dirent, dld_ent.fd_name) +
		                                                 (result->dld_ent.fd_namelen + 1) * sizeof(char),
		                                                 GFP_NORMAL);
		if likely(newent)
			result = newent;
	}
	return result;
err_r:
	kfree(result);
	return NULL;
}




PUBLIC BLOCKING WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
devdiskruledir_v_lookup(struct fdirnode *__restrict self,
                        struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	REF struct blkdev *result_dev;
	struct devicelink_dirent *result;
	struct devdiskruledir *me;
	me = (struct devdiskruledir *)mfile_asdir(self);

	/* Unescape the given filename. */
	result = devdiskruledir_unescape(info);
	if unlikely(!result)
		return NULL;
	TRY {
		struct flookup_info newinfo;
		newinfo.flu_name    = result->dld_ent.fd_name;
		newinfo.flu_hash    = FLOOKUP_INFO_HASH_UNSET;
		newinfo.flu_namelen = result->dld_ent.fd_namelen;
		newinfo.flu_flags   = info->flu_flags;

		/* Query block device by name. */
		result_dev = (*me->ddrd_byname)(me, &newinfo);
		if (!result_dev) {
			kfree(result);
			return NULL;
		}

		/* XXX: Technically, we'd need to re-escape the `result' filename here... */

		/* Fill in the resulting of `result' */
		assert(newinfo.flu_name == result->dld_ent.fd_name);
		assert(newinfo.flu_namelen == result->dld_ent.fd_namelen);
		if likely(newinfo.flu_hash == FLOOKUP_INFO_HASH_UNSET)
			newinfo.flu_hash = fdirent_hash(newinfo.flu_name, newinfo.flu_namelen);
		result->dld_ent.fd_hash   = newinfo.flu_hash;
		result->dld_ent.fd_ops    = &devicelink_dirent_ops;
		result->dld_ent.fd_refcnt = 1;
		result->dld_ent.fd_type   = DT_LNK;
		result->dld_dev           = result_dev; /* Inherit reference */
		result->dld_pfx           = me->_ddrd_prefix;
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	return &result->dld_ent;
}



struct devruleenum: fdirenum {
#ifndef CONFIG_NO_SMP
	struct atomic_lock dre_lock;    /* SMP lock */
#endif /* !CONFIG_NO_SMP */
	REF struct fnode  *dre_nextfil; /* [0..1][lock(SMP(dre_lock))] Next file to enumerate. */
	uintptr_t          dre_nextvar; /* [lock(SMP(dre_lock))] Next variant to enumerate. */
};
#define devruleenum_break(self)   atomic_lock_release_smp_b(&(self)->dre_lock)
#define devruleenum_acquire(self) atomic_lock_acquire_smp(&(self)->dre_lock)
#define devruleenum_release(self) atomic_lock_release_smp(&(self)->dre_lock)

#ifdef CONFIG_NO_SMP
#define SIZEOF_DEVRULEENUM (SIZEOF_FDIRENUM + (__SIZEOF_POINTER__ * 2))
#else /* CONFIG_NO_SMP */
#define SIZEOF_DEVRULEENUM (SIZEOF_FDIRENUM + (__SIZEOF_POINTER__ * 3))
#endif /* !CONFIG_NO_SMP */

static_assert(sizeof(struct devruleenum) == SIZEOF_DEVRULEENUM);

#undef devdiskruledir_v_enumsz
DEFINE_PUBLIC_SYMBOL(devdiskruledir_v_enumsz, SIZEOF_DEVRULEENUM, 0);
#define devdiskruledir_v_enumsz sizeof(struct devruleenum)



struct devdiskruledir_readdata {
	NCX char *rd_buf;     /* File name buffer */
	size_t    rd_bufsize; /* File name buffer size */
	size_t    rd_reqsize; /* Required name size */
};


PRIVATE ssize_t FORMATPRINTER_CC
escape_printer(void *arg, /*utf-8*/ char const *__restrict data, size_t datalen) {
	size_t i;
	struct devdiskruledir_readdata *info;
	info = (struct devdiskruledir_readdata *)arg;
#define putc(ch)                                       \
	(++info->rd_reqsize,                               \
	 info->rd_bufsize ? (void)(*info->rd_buf++ = (ch), \
	                           --info->rd_bufsize)     \
	                  : (void)0)
	for (i = 0; i < datalen; ++i) {
		unsigned char ch = (unsigned char)data[i];
		if (devdiskrule_mustescape(ch)) {
			putc('\\');
			putc('x');
			putc(_itoa_lower_digits[ch >> 4]);
			putc(_itoa_lower_digits[ch & 0xf]);
		} else {
			putc(ch);
		}
	}
#undef putc
	return (ssize_t)datalen;
}


PRIVATE BLOCKING NONNULL((1)) size_t KCALL
devruleenum_v_readdir(struct fdirenum *__restrict self, NCX struct dirent *buf,
                      size_t bufsize, readdir_mode_t readdir_mode, iomode_t UNUSED(mode))
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	bool should_yield;
	struct devdiskruledir_readdata rdat;
	struct devdiskruledir *dir;
	struct devruleenum *me = (struct devruleenum *)self;
	REF struct fnode *olddev, *mydev;
	uintptr_t oldvar, myvar;
	dir = (struct devdiskruledir *)mfile_asdir(me->de_dir);
again:
	devruleenum_acquire(me);
	olddev = me->dre_nextfil;
	if unlikely(!olddev) {
		devruleenum_break(me);
		return 0; /* EOF */
	}
	incref(olddev);
	oldvar = me->dre_nextvar;
	devruleenum_release(me);
	FINALLY_DECREF_UNLIKELY(olddev);

	rdat.rd_buf     = buf->d_name;
	rdat.rd_bufsize = bufsize;
	if (OVERFLOW_USUB(rdat.rd_bufsize,
	                  offsetof(struct dirent, d_name),
	                  &rdat.rd_bufsize))
		rdat.rd_bufsize = 0;
	rdat.rd_reqsize = 0;

	/* Find the next device to enumerate. */
	mydev = mfile_asnode(incref(olddev));
	myvar = oldvar;
	for (;;) {
		ssize_t status;
		FINALLY_DECREF_UNLIKELY(mydev);
		status = 0;
		if (fnode_isblkdev(mydev)) {
			status = (*dir->ddrd_toname)(dir, &escape_printer, &rdat,
			                             mfile_asblkdev(mydev), myvar);
		}
		if (status > 0) {
			incref(mydev);
			break;
		}
		myvar = 0;
		mydev = fsuper_nodeafter(&devfs, mydev);
		if (!mydev)
			return 0; /* EOF */
	}
	FINALLY_DECREF_UNLIKELY(mydev);

	/* Write-back additional data to the user-provided directory entry buffer. */
	should_yield = true;
	if (bufsize >= offsetof(struct dirent, d_name)) {
		buf->d_ino    = (typeof(buf->d_ino))DEVFS_INO_DYN((uintptr_t)mydev ^ (uintptr_t)dir->_ddrd_prefix);
		buf->d_type   = (typeof(buf->d_type))DT_LNK;
		buf->d_namlen = (typeof(buf->d_namlen))rdat.rd_reqsize;
		if (bufsize >= (offsetof(struct dirent, d_name) + rdat.rd_reqsize + 1)) {
			/* Add trailing NUL */
			buf->d_name[rdat.rd_reqsize] = '\0';
		} else {
			if ((readdir_mode & READDIR_MODEMASK) == READDIR_DEFAULT)
				should_yield = false; /* Don't yield */
		}
		if ((readdir_mode & READDIR_MODEMASK) == READDIR_PEEK)
			should_yield = false; /* Don't yield */
	} else {
		if ((readdir_mode & READDIR_MODEMASK) != READDIR_CONTINUE)
			should_yield = false; /* Don't yield */
	}

	/* If requested, advance to the next entry. */
	if (should_yield) {
		devruleenum_acquire(me);
		if (olddev != me->dre_nextfil ||
		    oldvar != me->dre_nextvar) {
			devruleenum_break(me);
			goto again;
		}
		me->dre_nextfil = mfile_asnode(incref(mydev)); /* Inherit reference (x2) */
		me->dre_nextvar = myvar + 1;
		devruleenum_release(me);
		decref_unlikely(olddev);
	}

	return ((offsetof(struct dirent, d_name)) +
	        (rdat.rd_reqsize + 1) * sizeof(char));
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL devruleenum_v_fini)(struct fdirenum *__restrict self) {
	struct devruleenum *me = (struct devruleenum *)self;
	decref_unlikely(me->dre_nextfil);
}

PRIVATE BLOCKING NONNULL((1)) pos_t KCALL
devruleenum_v_seekdir(struct fdirenum *__restrict self,
                      off_t offset, unsigned int whence)
		THROWS(E_OVERFLOW, E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_IOERROR, ...) {
	pos_t result;
	struct devruleenum *me = (struct devruleenum *)self;
	switch (whence) {

	case SEEK_SET: {
		REF struct fnode *olddev;
		REF struct fnode *newdev;
		if (offset != 0)
			goto invarg;
		newdev = fsuper_nodeafter(&devfs, NULL);
		devruleenum_acquire(me);
		olddev = me->dre_nextfil;
		me->dre_nextfil = newdev;
		me->dre_nextvar = 0;
		devruleenum_release(me);
		xdecref_unlikely(olddev);
		result = 0;
	}	break;

	default:
invarg:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,
		      whence);
		break;
	}
	return result;
}


PRIVATE struct fdirenum_ops const devdiskruledir_enum_ops = {
	.deo_fini    = &devruleenum_v_fini,
	.deo_readdir = &devruleenum_v_readdir,
	.deo_seekdir = &devruleenum_v_seekdir,
};

PUBLIC BLOCKING NONNULL((1)) void KCALL
devdiskruledir_v_enum(struct fdirenum *__restrict result)
		THROWS(E_IOERROR, ...) {
	struct devruleenum *me;
	me         = (struct devruleenum *)result;
	me->de_ops = &devdiskruledir_enum_ops;
#ifndef CONFIG_NO_SMP
	atomic_lock_init(&me->dre_lock);
#endif /* !CONFIG_NO_SMP */
	me->dre_nextfil = fsuper_nodeafter(&devfs, NULL);
	me->dre_nextvar = 0;
}

PUBLIC_CONST struct fdirnode_ops const devdiskruledir_ops = {
	.dno_node = {
		.no_file = {
			.mo_destroy = &devdiskruledir_v_destroy,
			.mo_changed = &fdirnode_v_changed,
			.mo_stream  = &fdirnode_v_stream_ops,
		},
		.no_free   = (typeof_field(struct fnode_ops, no_free))(void *)-1,
		.no_wrattr = &fnode_v_wrattr_noop,
	},
	.dno_lookup = &devdiskruledir_v_lookup,
	.dno_enumsz = devdiskruledir_v_enumsz,
	.dno_enum   = &devdiskruledir_v_enum,
};

/* Same  as  `devdiskruledir_ops', but  used for  default rules.
 * Unlike `devdiskruledir_ops', these return `boottime' in stat. */
INTERN_CONST struct fdirnode_ops const _devdiskruledir_default_ops = {
	.dno_node = {
		.no_file = {
			.mo_destroy = (typeof_field(struct mfile_ops, mo_destroy))(void *)-1,
			.mo_changed = &fdirnode_v_changed,
			.mo_stream  = &devfs_spec_v_stream_ops_with_boottime,
		},
		.no_free   = (typeof_field(struct fnode_ops, no_free))(void *)-1,
		.no_wrattr = &fnode_v_wrattr_noop,
	},
	.dno_lookup = &devdiskruledir_v_lookup,
	.dno_enumsz = devdiskruledir_v_enumsz,
	.dno_enum   = &devdiskruledir_v_enum,
};


/* Default rules. (defined in "./devfs-defs.c"; implemented in "./devfs-diskrules.c") */
INTDEF struct devdiskrule _devdisk_defrule_byid;
INTDEF struct devdiskrule _devdisk_defrule_bylabel;
INTDEF struct devdiskrule _devdisk_defrule_bypartlabel;
INTDEF struct devdiskrule _devdisk_defrule_bypartuuid;
INTDEF struct devdiskrule _devdisk_defrule_bypath;
INTDEF struct devdiskrule _devdisk_defrule_byuuid;

/* Default list of /dev/disk/by-xxx rules.
 * These rules must always be included in the current list of rules. */
PUBLIC_CONST REF struct devdiskrule *const devdiskrules_default_list[] = {
	/* /dev/disk/by-id        */ &_devdisk_defrule_byid,
	/* /dev/disk/by-label     */ &_devdisk_defrule_bylabel,
	/* /dev/disk/by-partlabel */ &_devdisk_defrule_bypartlabel,
	/* /dev/disk/by-partuuid  */ &_devdisk_defrule_bypartuuid,
	/* /dev/disk/by-path      */ &_devdisk_defrule_bypath,
	/* /dev/disk/by-uuid      */ &_devdisk_defrule_byuuid,
};

#undef devdiskrules_default_size
#define _devdiskrules_default_size 6
static_assert(lengthof(devdiskrules_default_list) == _devdiskrules_default_size);
DEFINE_PUBLIC_SYMBOL(devdiskrules_default_size, _devdiskrules_default_size, 0);
#define devdiskrules_default_size _devdiskrules_default_size


/* [1..1][0..devdiskrules_size][owned_if(!= devdiskrules_default_list)][lock(devdiskrules_lock)]
 * List of device disk rules. Always sorted lexicographically ascendingly, based on rule  names. */
PUBLIC REF struct devdiskrule **devdiskrules_list = (REF struct devdiskrule **)devdiskrules_default_list;
PUBLIC size_t /*             */ devdiskrules_size = devdiskrules_default_size;

/* Lock for `devdiskrules_list' and `devdiskrules_size' */
PUBLIC struct shared_rwlock devdiskrules_lock = SHARED_RWLOCK_INIT;

/* Lock operators for `devdiskrules_lock' */
PUBLIC struct lockop_slist devdiskrules_lops = SLIST_HEAD_INITIALIZER(devdiskrules_lops);




/************************************************************************/
/* /dev/disk                                                            */
/************************************************************************/
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
devfs_disk_v_lookup(struct fdirnode *__restrict UNUSED(self),
                    struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	size_t lo, hi;
	devdiskrules_read();
	RAII_FINALLY { devdiskrules_endread(); };
	lo = 0;
	hi = devdiskrules_size;
	while (lo < hi) {
		struct devdiskrule *rule;
		int cmp;
		size_t i;
		i    = (lo + hi) / 2;
		rule = devdiskrules_list[i];
		cmp  = strcmpz(rule->ddre_ent.fd_name, info->flu_name, info->flu_namelen);
		if (cmp > 0) {
			hi = i;
		} else if (cmp < 0) {
			lo = i + 1;
		} else {
			/* Found it! */
			return incref(&rule->ddre_ent);
		}
	}

	/* If necessary, do another case-insensitive search. */
	if (info->flu_flags & AT_DOSPATH) {
		size_t i;
		for (i = 0; i < devdiskrules_size; ++i) {
			struct devdiskrule *rule;
			rule = devdiskrules_list[i];
			if (rule->ddre_ent.fd_namelen != info->flu_namelen)
				continue;
			if (memcasecmp(rule->ddre_ent.fd_name, info->flu_name,
			               info->flu_namelen * sizeof(char)) != 0)
				continue;
			/* Found it! */
			return incref(&rule->ddre_ent);
		}
	}
	return NULL;
}


#ifndef __devdiskrule_axref_defined
#define __devdiskrule_axref_defined
AXREF(devdiskrule_axref, devdiskrule);
#endif /* !__devdiskrule_axref_defined */

struct disk_enum: fdirenum {
	struct devdiskrule_axref de_nrule; /* [0..1] Next rule to enumerate. */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL disk_enum_v_fini)(struct fdirenum *__restrict self) {
	struct disk_enum *me = (struct disk_enum *)self;
	axref_fini(&me->de_nrule);
}

PRIVATE BLOCKING NONNULL((1)) size_t KCALL
disk_enum_v_readdir(struct fdirenum *__restrict self, NCX struct dirent *buf,
                    size_t bufsize, readdir_mode_t readdir_mode, iomode_t UNUSED(mode))
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	size_t lo, hi;
	ssize_t result;
	struct disk_enum *me = (struct disk_enum *)self;
	REF struct devdiskrule *oldrule, *newrule;
again:
	oldrule = axref_get(&me->de_nrule);
	if (!oldrule)
		return 0; /* EOF */
	FINALLY_DECREF_UNLIKELY(oldrule);

	/* Yield directory entry. */
	result = fdirenum_feedent_fast(buf, bufsize, readdir_mode, &oldrule->ddre_ent);
	if (result < 0)
		return (size_t)~result; /* Don't advance directory position. */

	/* Load next rule. */
	devdiskrules_read();
	lo = 0;
	hi = devdiskrules_size;
	while (lo < hi) {
		struct devdiskrule *rule;
		int cmp;
		size_t i;
		i    = (lo + hi) / 2;
		rule = devdiskrules_list[i];
		if (rule == oldrule) {
			lo = i;
			break;
		}
		cmp  = strcmp(rule->ddre_ent.fd_name, oldrule->ddre_ent.fd_name);
		if (cmp > 0) {
			hi = i;
		} else if (cmp < 0) {
			lo = i + 1;
		} else {
			lo = i;
			break;
		}
	}

	/* Advance to next slot. */
	++lo;

	/* Load next rule. */
	newrule = NULL;
	if (lo < devdiskrules_size)
		newrule = incref(devdiskrules_list[lo]);
	devdiskrules_endread();

	/* Remember the next rule. */
	if (!axref_cmpxch_inherit_new(&me->de_nrule, oldrule, newrule)) {
		xdecref_unlikely(newrule);
		goto again;
	}

	return (size_t)result;
}

PRIVATE BLOCKING NONNULL((1)) pos_t KCALL
disk_enum_v_seekdir(struct fdirenum *__restrict self,
                    off_t offset, unsigned int whence)
		THROWS(E_OVERFLOW, E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_IOERROR, ...) {
	pos_t result;
	struct disk_enum *me = (struct disk_enum *)self;
	switch (whence) {

	case SEEK_SET: {
		REF struct devdiskrule *newrule;
		devdiskrules_read();
		if ((pos_t)offset >= (pos_t)devdiskrules_size) {
			newrule = NULL;
			result  = (pos_t)devdiskrules_size;
		} else {
			result  = (pos_t)offset;
			newrule = incref(devdiskrules_list[(size_t)offset]);
		}
		devdiskrules_endread();
		axref_set_inherit(&me->de_nrule, newrule);
	}	break;

	case SEEK_CUR: {
		size_t curidx;
		REF struct devdiskrule *oldrule;
		REF struct devdiskrule *newrule;
again_seek_cur:
		oldrule = axref_get(&me->de_nrule);
		FINALLY_XDECREF_UNLIKELY(oldrule);
		devdiskrules_read();
		if (oldrule == NULL) {
			curidx = devdiskrules_size;
		} else {
			for (curidx = 0; curidx < devdiskrules_size; ++curidx) {
				if (devdiskrules_list[curidx] == oldrule)
					break;
			}
			if (curidx >= devdiskrules_size) {
				/* Currently selected rule was deleted. -> Find the next-greater. */
				size_t lo, hi;
				lo = 0;
				hi = devdiskrules_size;
				while (lo < hi) {
					struct devdiskrule *rule;
					int cmp;
					curidx = (lo + hi) / 2;
					rule   = devdiskrules_list[curidx];
					cmp    = strcmp(rule->ddre_ent.fd_name, oldrule->ddre_ent.fd_name);
					if (cmp > 0) {
						hi = curidx;
					} else if (cmp < 0) {
						lo = curidx + 1;
					} else {
						lo = curidx;
						break;
					}
				}
				curidx = lo;
			}
		}
		if ((offset >= 0 ? OVERFLOW_UADD(curidx, (pos_t)+offset, &result)
		                 : OVERFLOW_USUB(curidx, (pos_t)-offset, &result)) ||
		    (result > (pos_t)devdiskrules_size)) {
			devdiskrules_endread();
			THROW(E_OVERFLOW);
		}

		/* Select new rule. */
		newrule = NULL;
		if ((size_t)result < devdiskrules_size)
			newrule = incref(devdiskrules_list[(size_t)result]);
		devdiskrules_endread();

		/* Load new rule. */
		if (!axref_cmpxch_inherit_new(&me->de_nrule, oldrule, newrule)) {
			xdecref_unlikely(newrule);
			goto again_seek_cur;
		}
	}	break;

	case SEEK_END: {
		REF struct devdiskrule *newrule;
		devdiskrules_read();
		if ((pos_t)offset >= 0) {
			newrule = NULL;
			result  = (pos_t)devdiskrules_size;
		} else {
			if (OVERFLOW_USUB((pos_t)devdiskrules_size, (pos_t)-offset, &result)) {
				devdiskrules_endread();
				THROW(E_OVERFLOW);
			}
			newrule = incref(devdiskrules_list[(size_t)result]);
		}
		devdiskrules_endread();
		axref_set_inherit(&me->de_nrule, newrule);
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,
		      whence);
		break;
	}
	return result;
}

PRIVATE struct fdirenum_ops const disk_enum_ops = {
	.deo_fini    = &disk_enum_v_fini,
	.deo_readdir = &disk_enum_v_readdir,
	.deo_seekdir = &disk_enum_v_seekdir,
};

PRIVATE BLOCKING NONNULL((1)) void KCALL
devfs_disk_v_enum(struct fdirenum *__restrict result)
		THROWS(E_IOERROR, ...) {
	struct disk_enum *me;
	REF struct devdiskrule *firstrule;
	me = (struct disk_enum *)result;
	me->de_ops = &disk_enum_ops;

	/* Load the first rule. */
	firstrule = NULL;
	devdiskrules_read();
	if likely(devdiskrules_size != 0)
		firstrule = incref(devdiskrules_list[0]);
	devdiskrules_endread();

	/* Start enumeration with the first rule. */
	axref_init(&me->de_nrule, firstrule);
}

INTERN_CONST struct fdirnode_ops const devfs_disk_ops = {
	.dno_node = {
		.no_file = {
			.mo_destroy = (typeof_field(struct mfile_ops, mo_destroy))(void *)-1,
			.mo_changed = &fdirnode_v_changed,
			.mo_stream  = &devfs_spec_v_stream_ops_with_boottime,
		},
		.no_free   = (typeof_field(struct fnode_ops, no_free))(void *)-1,
		.no_wrattr = &fnode_v_wrattr_noop,
	},
	.dno_lookup = &devfs_disk_v_lookup,
	.dno_enumsz = sizeof(struct disk_enum),
	.dno_enum   = &devfs_disk_v_enum,
};


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
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((2)) REF struct devdiskrule *VCALL
devdiskrule_allocf(size_t sizeof_devdiskruledir,
                   char const *__restrict namef, ...)
		THROWS(E_BADALLOC, E_FSERROR_ILLEGAL_PATH) {
	REF struct devdiskrule *result;
	va_list args;
	va_start(args, namef);
	RAII_FINALLY { va_end(args); };
	result = devdiskrule_vallocf(sizeof_devdiskruledir, namef, args);
	return result;
}


struct devdiskrule_printer_data {
	struct devdiskrule *ddp_base; /* [1..ddp_used|ALLOC(ddp_used+ddp_aval)][owned] Buffer */
	size_t              ddp_aval; /* Unused filename buffer size */
	size_t              ddp_used; /* Used filename buffer size */
};

PRIVATE WUNUSED NONNULL((1, 2)) ssize_t KCALL
devdiskrule_printer(/*struct devdiskrule_printer_data **/ void *arg,
                    /*utf-8*/ char const *__restrict data,
                    size_t datalen) {
	struct devdiskrule_printer_data *info;
	info = (struct devdiskrule_printer_data *)arg;
	if (info->ddp_aval < datalen) {
		struct devdiskrule *newbuf;
		size_t min_alloc = info->ddp_used + datalen;
		size_t new_alloc = info->ddp_used + info->ddp_aval;
		if (!new_alloc)
			new_alloc = 8;
		while (new_alloc < min_alloc)
			new_alloc *= 2;
		newbuf = (struct devdiskrule *)krealloc_nx(info->ddp_base,
		                                           offsetof(struct devdiskrule, ddre_ent.fd_name) +
		                                           (new_alloc + 1) * sizeof(char),
		                                           GFP_NORMAL);
		if unlikely(!newbuf) {
			newbuf = (struct devdiskrule *)krealloc(info->ddp_base,
			                                        offsetof(struct devdiskrule, ddre_ent.fd_name) +
			                                        (min_alloc + 1) * sizeof(char),
			                                        GFP_NORMAL);
		}
		info->ddp_base = newbuf;
		info->ddp_aval = kmalloc_usable_size(newbuf);
		info->ddp_aval -= (info->ddp_used + 1) * sizeof(char);
		info->ddp_aval -= offsetof(struct devdiskrule, ddre_ent.fd_name);
	}
	memcpy(info->ddp_base->ddre_ent.fd_name + info->ddp_used, data, datalen, sizeof(char));
	info->ddp_aval -= datalen;
	info->ddp_used  += datalen;
	return (ssize_t)datalen;
}


PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((2)) REF struct devdiskrule *FCALL
devdiskrule_vallocf(size_t sizeof_devdiskruledir,
                    char const *__restrict namef,
                    va_list args)
		THROWS(E_BADALLOC, E_FSERROR_ILLEGAL_PATH) {
	struct devdiskrule_printer_data pdat;
	struct devdiskruledir *dir;
	assert(sizeof_devdiskruledir >= sizeof(struct devdiskruledir));

	/* Allocate directory entry. */
	pdat.ddp_used = 0;
	pdat.ddp_aval = 128;
	pdat.ddp_base = (struct devdiskrule *)kmalloc_nx(offsetof(struct devdiskrule, ddre_ent.fd_name) +
	                                                 (128 + 1) * sizeof(char),
	                                                 GFP_NORMAL);
	if (!pdat.ddp_base) {
		pdat.ddp_aval = 1;
		pdat.ddp_base = (struct devdiskrule *)kmalloc(offsetof(struct devdiskrule, ddre_ent.fd_name) +
		                                              (1 + 1) * sizeof(char),
		                                              GFP_NORMAL);
	}

	TRY {
		/* Print rule name. */
		format_vprintf(&devdiskrule_printer, &pdat, namef, args);
		if unlikely(pdat.ddp_used > (u16)-1)
			THROW(E_FSERROR_ILLEGAL_PATH);

		/* Allocate rule directory. */
		dir = (struct devdiskruledir *)kmalloc(sizeof_devdiskruledir, GFP_NORMAL);
	} EXCEPT {
		kfree(pdat.ddp_base);
		RETHROW();
	}

	/* Free unused data. */
	if likely(pdat.ddp_aval != 0) {
		struct devdiskrule *newent;
		newent = (struct devdiskrule *)krealloc_nx(pdat.ddp_base,
		                                           offsetof(struct devdiskrule, ddre_ent.fd_name) +
		                                           (pdat.ddp_used + 1) * sizeof(char),
		                                           GFP_NORMAL);
		if likely(newent)
			pdat.ddp_base = newent;
	}

	/* Finalize name. */
	pdat.ddp_base->ddre_ent.fd_name[(u16)pdat.ddp_used] = '\0';
	pdat.ddp_base->ddre_ent.fd_namelen = (u16)pdat.ddp_used;

	/* Fill in remaining fields. */
	pdat.ddp_base->ddre_ent.fd_type   = DT_DIR;
	pdat.ddp_base->ddre_ent.fd_hash   = fdirent_hash(pdat.ddp_base->ddre_ent.fd_name, (u16)pdat.ddp_used);
	pdat.ddp_base->ddre_ent.fd_ino    = DEVFS_INO_DYN(dir);
	pdat.ddp_base->ddre_ent.fd_ops    = &devdiskrule_ops;
	pdat.ddp_base->ddre_ent.fd_refcnt = 1;
	pdat.ddp_base->ddre_rule          = dir; /* Inherit reference */
	DBG_memset(&pdat.ddp_base->_ddre_lop, 0xcc, sizeof(pdat.ddp_base->_ddre_lop));

	/* Initialize the rule directory. */
	DBG_memset(&dir->ddrd_byname, 0xcc, sizeof(dir->ddrd_byname)); /* Filled by the caller */
	DBG_memset(&dir->ddrd_toname, 0xcc, sizeof(dir->ddrd_toname)); /* Filled by the caller */
	DBG_memset(&dir->ddrd_drv, 0xcc, sizeof(dir->ddrd_drv));       /* Filled by the caller */
	memcpy(dir->_ddrd_prefix, "../../\0", 8, sizeof(char));
	dir->fn_nlink = 1;
	dir->fn_mode  = S_IFDIR | 0555;
	dir->fn_uid   = 0;
	dir->fn_gid   = 0;
	dir->fn_ino   = pdat.ddp_base->ddre_ent.fd_ino;
	dir->fn_super = &devfs; /* !!! NOT A REFERENCE !!! */
	LIST_ENTRY_UNBOUND_INIT(&dir->fn_changed);
	DBG_memset(&dir->fn_supent, 0xcc, sizeof(dir->fn_supent));
	dir->fn_supent.rb_rhs = FSUPER_NODES_DELETED;
	LIST_ENTRY_UNBOUND_INIT(&dir->fn_allnodes);
	DBG_memset(&dir->fn_fsdata, 0xcc, sizeof(dir->fn_fsdata));

	_mfile_init_common(dir);
	_mfile_init_blockshift(dir, PAGESHIFT, PAGESHIFT);
	dir->mf_ops               = &devdiskruledir_ops.dno_node.no_file;
	dir->mf_parts             = MFILE_PARTS_ANONYMOUS;
	dir->mf_changed.slh_first = MFILE_PARTS_ANONYMOUS;
	dir->mf_flags             = MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_NOATIME |
	                            MFILE_F_NOMTIME | MFILE_F_READONLY |
	                            MFILE_F_FIXEDFILESIZE | MFILE_FN_FLEETING;
	atomic64_init(&dir->mf_filesize, (uint64_t)-1);
	dir->mf_atime = realtime();
	dir->mf_mtime = dir->mf_atime;
	dir->mf_ctime = dir->mf_atime;
	dir->mf_btime = dir->mf_atime;

	/* Return the newly constructed rule. */
	return pdat.ddp_base;
}


/* Register a  fully initialized  /dev/disk/by-xxx rule  object.
 * Once registered, the object can be unregistered exactly  once
 * via `devdiskrule_delete()'. Once that has been done, you must
 * _NOT_ try to register it once again!
 * @throws: E_FSERROR_FILE_ALREADY_EXISTS: `self->ddre_ent.fd_name' has already been defined */
PUBLIC BLOCKING NONNULL((1)) void FCALL
devdiskrule_register(struct devdiskrule *__restrict self)
		THROWS(E_WOULDBLOCK, E_FSERROR_FILE_ALREADY_EXISTS) {
	size_t lo, hi;
	REF struct devdiskrule **new_rules;
	assert(!wasdestroyed(self->ddre_rule->ddrd_drv));
	devdiskrules_write();
	RAII_FINALLY { devdiskrules_endwrite(); };
	lo = 0;
	hi = devdiskrules_size;
	while (lo < hi) {
		struct devdiskrule *rule;
		int cmp;
		size_t i;
		i    = (lo + hi) / 2;
		rule = devdiskrules_list[i];
		cmp  = strcmp(rule->ddre_ent.fd_name, self->ddre_ent.fd_name);
		if (cmp > 0) {
			hi = i;
		} else if (cmp < 0) {
			lo = i + 1;
		} else {
			THROW(E_FSERROR_FILE_ALREADY_EXISTS);
		}
	}

	/* Insert the new rule at index `lo' */
	new_rules = devdiskrules_list;
	if (new_rules == devdiskrules_default_list) {
		assert(devdiskrules_size == devdiskrules_default_size);
		new_rules = NULL;
	}
	new_rules = (REF struct devdiskrule **)krealloc(new_rules,
	                                                (devdiskrules_size + 1) *
	                                                sizeof(REF struct devdiskrule *),
	                                                GFP_NORMAL);
	if (devdiskrules_list == devdiskrules_default_list) {
		memcpy(new_rules, devdiskrules_default_list,
		       devdiskrules_default_size,
		       sizeof(REF struct devdiskrule *));
	}

	/* Make space for the new rule. */
	memmoveup(&new_rules[lo + 1], &new_rules[lo],
	          devdiskrules_size - lo,
	          sizeof(REF struct devdiskrule *));

	/* Insert the new rule. */
	new_rules[lo] = incref(self);

	/* Write-back the updated rules list. */
	devdiskrules_list = new_rules;
	devdiskrules_size += 1;
}




PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL do_remove_diskrule)(/*out*/ REF struct devdiskrule *__restrict self) {
	size_t lo, hi;
	REF struct devdiskrule **list;
	lo   = 0;
	hi   = devdiskrules_size;
	list = devdiskrules_list;
	for (;;) {
		struct devdiskrule *rule;
		int cmp;
		size_t i;
		assert(lo < hi);
		i    = (lo + hi) / 2;
		rule = list[i];
		cmp  = strcmp(rule->ddre_ent.fd_name, self->ddre_ent.fd_name);
		if (cmp > 0) {
			hi = i;
		} else if (cmp < 0) {
			lo = i + 1;
		} else {
			/* Found it! */
			break;
		}
	}
	assert(list != devdiskrules_default_list);
	assert(devdiskrules_size > devdiskrules_default_size);
	if (devdiskrules_size == devdiskrules_default_size + 1) {
		/* Special case: go back to the default list of rules. */
		devdiskrules_list = (REF struct devdiskrule **)devdiskrules_default_list;
		kfree(list);
	} else {
		/* Shift list elements. */
		memmovedown(&list[lo], &list[lo + 1],
		            (devdiskrules_size - 1) - lo,
		            sizeof(REF struct devdiskrule *));
		/* Try to release unused memory. */
		list = (REF struct devdiskrule **)krealloc_nx(list,
		                                              (devdiskrules_size - 1) *
		                                              sizeof(REF struct devdiskrule *),
		                                              GFP_ATOMIC);
		if likely(list != NULL)
			devdiskrules_list = list;
	}

	/* Update the # of rules being kept track of. */
	--devdiskrules_size;
}



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC devdiskrule_delete_plop)(struct postlockop *__restrict self) {
	REF struct devdiskrule *me;
	me = container_of(self, struct devdiskrule, _ddre_plop);
	decref(me);
}

PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC devdiskrule_delete_lop)(struct lockop *__restrict self) {
	struct devdiskrule *me;
	me = container_of(self, struct devdiskrule, _ddre_lop);
	do_remove_diskrule(me);                             /* Inherit reference */
	me->_ddre_plop.plo_func = &devdiskrule_delete_plop; /* Inherit reference */
	return &me->_ddre_plop;
}


/* Delete  a given disk rule object from  the list of known disk rules.
 * If necessary, this function operates asynchronously to remove `self'
 * from  the  list of  known  rules, before  decref()-ing  `self'. This
 * function may only be called once for any given `self'. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL devdiskrule_delete)(struct devdiskrule *__restrict self) {
	if (devdiskrules_trywrite()) {
		do_remove_diskrule(self);
		devdiskrules_endwrite();
		decref_nokill(self); /* nokill because caller still got a reference! */
	} else {
		/* Must use a lock operation */
		self->_ddre_lop.lo_func = &devdiskrule_delete_lop;
		lockop_enqueue(&devdiskrules_lops, &self->_ddre_lop);
		_devdiskrules_reap();
	}
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DEVFS_DISK_C */
