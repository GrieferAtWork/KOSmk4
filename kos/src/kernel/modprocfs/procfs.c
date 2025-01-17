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
#ifndef GUARD_MODPROCFS_PROCFS_C
#define GUARD_MODPROCFS_PROCFS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver-callbacks.h>
#include <kernel/fs/constdir.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/notify.h>
#include <kernel/fs/super.h>
#include <kernel/printk.h>
#include <kernel/user.h>
#include <sched/group.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <kos/except.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <kos/except/reason/io.h>
#include <linux/magic.h>

#include <assert.h>
#include <atomic.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unicode.h>

#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
#include <sched/sig-completion.h>
#include <sched/sig.h>
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */


/**/
#include "procfs.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/************************************************************************/
/* Helpers for printing/parsing user-space values.                      */
/************************************************************************/

/* Print a string "0\n" or "1\n" depending on `value' */
INTERN NONNULL((1)) ssize_t FCALL
ProcFS_PrintBool(pformatprinter printer, void *arg, bool value) {
	char buf[2];
	buf[0] = value ? '1' : '0';
	buf[1] = '\n';
	return (*printer)(arg, buf, 2);
}

INTERN NONNULL((1)) ssize_t FCALL
ProcFS_PrintU32(pformatprinter printer, void *arg, u32 value) {
	return format_printf(printer, arg, "%" PRIu32 "\n", value);
}

INTERN NONNULL((1)) ssize_t FCALL
ProcFS_PrintU64(pformatprinter printer, void *arg, u64 value) {
	return format_printf(printer, arg, "%" PRIu64 "\n", value);
}


/* Parse  a given user-space buffer from being  a string `0' or `1', which
 * may optionally be surrounded by space characters that are automatically
 * stripped prior to being parsed.
 * If the buffer  contains anything other  than `[SPC]0|1[SPC]', then  a
 * `E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_INTEGER'
 * exception is thrown. */
INTERN NONNULL((1)) bool FCALL
ProcFS_ParseBool(NCX void const *buf, size_t bufsize)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE, E_BUFFER_TOO_SMALL) {
	NCX char const *endp;
	bool result;
	char mode;
	endp = (NCX char const *)buf + bufsize;
	while (endp > (NCX char const *)buf &&
	       unicode_isspace(endp[-1]))
		--endp;
	while ((NCX char const *)buf < endp &&
	       unicode_isspace(((char const *)buf)[0]))
		buf = (NCX char const *)buf + 1;
	bufsize = (size_t)(endp - (NCX char const *)buf);
	if (bufsize != 1)
		THROW(E_BUFFER_TOO_SMALL, 1, bufsize);
	mode = atomic_read((NCX char *)buf);
	if (mode == '0') {
		result = false;
	} else if (mode == '1') {
		result = true;
	} else {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_BAD_INTEGER,
		      (uintptr_t)(mode - '0')); /* This may underflow, but that's user-space problem! */
	}
	return result;
}

INTERN NONNULL((1)) u32 FCALL
ProcFS_ParseU32(NCX void const *buf, size_t bufsize, u32 minval, u32 maxval)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE, E_BUFFER_TOO_SMALL) {
	char intbuf[lengthof(PRIMAXu32) + 1];
	NCX char const *endp;
	NCX char *real_endp;
	u32 result;
	bufsize /= sizeof(char);
	endp = (NCX char const *)buf + bufsize;
	while (endp > (NCX char const *)buf &&
	       unicode_isspace(endp[-1]))
		--endp;
	while ((NCX char const *)buf < endp &&
	       unicode_isspace(((NCX char const *)buf)[0]))
		buf = (NCX char const *)buf + 1;
	bufsize = (size_t)(endp - (NCX char const *)buf);
	if unlikely(bufsize < 1)
		THROW(E_BUFFER_TOO_SMALL, sizeof(char), bufsize * sizeof(char));
	if unlikely(bufsize >= lengthof(intbuf) - 1)
		THROW(E_BUFFER_TOO_SMALL, sizeof(intbuf) - sizeof(char), bufsize * sizeof(char));
	COMPILER_READ_BARRIER();
	memcpy(intbuf, buf, bufsize, sizeof(char));
	COMPILER_READ_BARRIER();
	intbuf[bufsize] = 0;
	result = strtou32(intbuf, &real_endp, 10);
	if (real_endp != intbuf + bufsize)
		THROW(E_BUFFER_TOO_SMALL, (size_t)(real_endp - intbuf), bufsize);
	if (result < minval || result > maxval) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_BAD_INTEGER,
		      (uintptr_t)result);
	}
	return result;
}

INTERN NONNULL((1)) u64 FCALL
ProcFS_ParseU64(NCX void const *buf, size_t bufsize, u64 minval, u64 maxval)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE, E_BUFFER_TOO_SMALL) {
	char intbuf[lengthof(PRIMAXu64) + 1];
	NCX char const *endp;
	NCX char *real_endp;
	u64 result;
	bufsize /= sizeof(char);
	endp = (NCX char const *)buf + bufsize;
	while (endp > (NCX char const *)buf &&
	       unicode_isspace(endp[-1]))
		--endp;
	while ((NCX char const *)buf < endp &&
	       unicode_isspace(((NCX char const *)buf)[0]))
		buf = (NCX char const *)buf + 1;
	bufsize = (size_t)(endp - (NCX char const *)buf);
	if unlikely(bufsize < 1)
		THROW(E_BUFFER_TOO_SMALL, sizeof(char), bufsize * sizeof(char));
	if unlikely(bufsize >= lengthof(intbuf) - 1)
		THROW(E_BUFFER_TOO_SMALL, sizeof(intbuf) - sizeof(char), bufsize * sizeof(char));
	COMPILER_READ_BARRIER();
	memcpy(intbuf, buf, bufsize, sizeof(char));
	COMPILER_READ_BARRIER();
	intbuf[bufsize] = 0;
	result = strtou64(intbuf, &real_endp, 10);
	if (real_endp != intbuf + bufsize)
		THROW(E_BUFFER_TOO_SMALL, (size_t)(real_endp - intbuf), bufsize);
	if (result < minval || result > maxval) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_BAD_INTEGER,
		      (uintptr_t)result); /* XXX: This may cause the value to be truncated... */
	}
	return result;
}

INTERN NONNULL((1)) NCX UNCHECKED void *FCALL
ProcFS_ParsePtr(NCX void const *buf, size_t bufsize)
		THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_BAD_VALUE, E_BUFFER_TOO_SMALL) {
	char intbuf[lengthof(PRIMAXxPTR)];
	NCX char const *endp;
	NCX char *real_endp;
	NCX UNCHECKED void *result;
	bufsize /= sizeof(char);
	endp = (NCX char const *)buf + bufsize;
	while (endp > (NCX char const *)buf &&
	       unicode_isspace(endp[-1]))
		--endp;
	while ((NCX char const *)buf < endp &&
	       unicode_isspace(((NCX char const *)buf)[0]))
		buf = (NCX char const *)buf + 1;
	if ((NCX char const *)buf < endp && ((NCX char const *)buf)[0] == '0') {
		char ch;
		buf = (NCX char const *)buf + 1;
		if ((NCX char const *)buf >= endp)
			return (void *)0;
		ch = ((NCX char const *)buf)[0];
		if (ch == 'x' || ch == 'X') {
			buf = (NCX char const *)buf + 1;
			if unlikely((NCX char const *)buf >= endp) {
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_BAD_POINTER_STRING);
			}
skip_leading_zeroes:
			while ((NCX char const *)buf < endp &&
			       ((NCX char const *)buf)[0] == '0')
				buf = (NCX char const *)buf + 1;
		} else if (ch == '0') {
			goto skip_leading_zeroes;
		}
	}
	bufsize = (size_t)(endp - (NCX char const *)buf);
	if unlikely(bufsize < 1)
		THROW(E_BUFFER_TOO_SMALL, sizeof(char), bufsize * sizeof(char));
	if unlikely(bufsize >= lengthof(intbuf) - 1)
		THROW(E_BUFFER_TOO_SMALL, sizeof(intbuf) - sizeof(char), bufsize * sizeof(char));
	COMPILER_READ_BARRIER();
	memcpy(intbuf, buf, bufsize, sizeof(char));
	COMPILER_READ_BARRIER();
	intbuf[bufsize] = 0;
#if __SIZEOF_POINTER__ >= 8
	result = (NCX UNCHECKED void *)strtou64(intbuf, &real_endp, 16);
#else /* __SIZEOF_POINTER__ >= 8 */
	result = (NCX UNCHECKED void *)strtou32(intbuf, &real_endp, 16);
#endif /* __SIZEOF_POINTER__ < 8 */
	if (real_endp != intbuf + bufsize)
		THROW(E_BUFFER_TOO_SMALL, (size_t)(real_endp - intbuf), bufsize);
	return result;
}






/************************************************************************/
/* Static file operator wrappers                                        */
/************************************************************************/
PRIVATE NONNULL((1, 2)) void KCALL
procfs_regfile_v_print(struct printnode *__restrict self,
                       pformatprinter printer, void *arg,
                       pos_t offset_hint) {
	struct procfs_regfile *me = (struct procfs_regfile *)self;
	(*me->prf_print)(printer, arg, offset_hint);
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
procfs_regfile_v_pwrite(struct mfile *__restrict self, NCX void const *src,
                        size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	struct procfs_regfile *me = (struct procfs_regfile *)mfile_asprintnode(self);
	/* Need write operator. */
	if (!me->prf_write) {
		THROW(E_FSERROR_UNSUPPORTED_OPERATION,
		      E_FILESYSTEM_OPERATION_WRITE);
	}

	/* Can only write at addr=0 */
	if (addr != 0)
		THROW(E_IOERROR_BADBOUNDS, E_IOERROR_SUBSYSTEM_FILE);

	/* Invoke write. */
	(*me->prf_write)(src, num_bytes);

	/* Always indicate a full write (if wrong, `prf_write' throws an error) */
	return num_bytes;
}

#define procfs_regfile_v_pread  printnode_v_pread
#define procfs_regfile_v_preadv printnode_v_preadv
#define procfs_regfile_v_stat   printnode_v_stat
#define procfs_regfile_v_ioctl  printnode_v_ioctl
PRIVATE struct mfile_stream_ops const procfs_regfile_v_stream_ops = {
	.mso_pread  = &procfs_regfile_v_pread,
	.mso_preadv = &procfs_regfile_v_preadv,
	.mso_pwrite = &procfs_regfile_v_pwrite,
	.mso_stat   = &procfs_regfile_v_stat,
	.mso_ioctl  = &procfs_regfile_v_ioctl,
};
INTERN_CONST struct printnode_ops const procfs_regfile_ops = {
	.pno_reg = {{
		.no_file = {
			.mo_destroy    = (typeof_field(struct mfile_ops, mo_destroy))(void *)-1,
			.mo_loadblocks = &printnode_v_loadblocks,
			.mo_changed    = &printnode_v_changed,
			.mo_stream     = &procfs_regfile_v_stream_ops,
		},
		.no_free   = (typeof_field(struct fnode_ops, no_free))(void *)-1,
		.no_wrattr = &printnode_v_wrattr,
	}},
	.pno_print = &procfs_regfile_v_print,
};

PRIVATE NONNULL((1, 2)) void KCALL
procfs_txtfile_v_print(struct printnode *__restrict self,
                       pformatprinter printer, void *arg,
                       pos_t UNUSED(offset_hint)) {
	struct procfs_txtfile *me = (struct procfs_txtfile *)self;
	(*printer)(arg, me->ptf_string, strlen(me->ptf_string));
	(*printer)(arg, "\n", 1);
}

INTERN_CONST struct printnode_ops const procfs_txtfile_ops = {
	.pno_reg = {{
		.no_file = {
			.mo_destroy = (typeof_field(struct mfile_ops, mo_destroy))(void *)-1,
			.mo_changed = &printnode_v_changed,
			.mo_stream  = &printnode_v_stream_ops,
		},
		.no_free   = (typeof_field(struct fnode_ops, no_free))(void *)-1,
		.no_wrattr = &printnode_v_wrattr,
	}},
	.pno_print = &procfs_txtfile_v_print,
};




/* Define entries for the root directory. */
#define ROOTENT(name, type, nodeptr, hash) \
	INTDEF struct constdirent PP_CAT2(procfs_root_dirent_, __LINE__);
#include "procfs.def"

/* NOTE: Files in this are sorted as lexicographically ascending. */
#define PROCFS_ROOT_COUNT lengthof(procfs_root_files)
PRIVATE struct fdirent *const procfs_root_files[] = {
#define ROOTENT(name, type, nodeptr, hash) \
	constdirent_asent(&PP_CAT2(procfs_root_dirent_, __LINE__)),
#include "procfs.def"
};

PRIVATE WUNUSED NONNULL((1)) REF struct fdirent *FCALL
procfs_root_find_static_file(struct flookup_info *__restrict info) {
	size_t lo, hi;
	lo = 0;
	hi = PROCFS_ROOT_COUNT;
	while (lo < hi) {
		struct fdirent *entry;
		size_t i;
		int cmp;
		i     = (lo + hi) / 2;
		entry = procfs_root_files[i];
		cmp   = strcmpz(entry->fd_name, info->flu_name, info->flu_namelen);
		if (cmp > 0) {
			hi = i;
		} else if (cmp < 0) {
			lo = i + 1;
		} else {
			/* Found it! */
			return incref(entry);
		}
	}
	/* If requested, also do another case-insensitive search. */
	if (info->flu_flags & AT_DOSPATH) {
		size_t i;
		for (i = 0; i < PROCFS_ROOT_COUNT; ++i) {
			struct fdirent *entry;
			entry = procfs_root_files[i];
			if (entry->fd_namelen != info->flu_namelen)
				continue;
			if (memcasecmp(entry->fd_name, info->flu_name,
			               info->flu_namelen * sizeof(char)) != 0)
				continue;
			/* Found it! */
			return incref(entry);
		}
	}
	return NULL;
}

PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
procfs_root_v_lookup(struct fdirnode *__restrict UNUSED(self),
                     struct flookup_info *__restrict info) {
	char ch;

	/* Evaluate running process PIDs */
	if unlikely(info->flu_namelen == 0)
		goto notapid;
	ch = atomic_read(&info->flu_name[0]);
	if (ch >= '1' && ch <= '9') {
		REF struct taskpid *pid;
		pid_t pidno = ch - '0';
		size_t i;
		for (i = 1; i < info->flu_namelen; ++i) {
			ch = atomic_read(&info->flu_name[i]);
			if unlikely(!(ch >= '0' && ch <= '9'))
				goto notapid;
			pidno *= 10;
			pidno += ch - '0';
		}
		pid = pidns_lookup(THIS_PIDNS, pidno);
		if likely(pid) {
			REF struct procfs_perproc_root_dirent *result;
			result = (REF struct procfs_perproc_root_dirent *)kmalloc(offsetof(struct procfs_perproc_root_dirent,
			                                                                   pprd_ent.fd_name) +
			                                                          (info->flu_namelen + 1) * sizeof(char),
			                                                          GFP_NORMAL);

			/* Fill in the directory entry. */
			result->pprd_pid            = pid; /* Inherit reference */
			result->pprd_ent.fd_namelen = (u16)sprintf(result->pprd_ent.fd_name, "%" PRIuN(__SIZEOF_PID_T__), (upid_t)pidno);
			assert(result->pprd_ent.fd_namelen == info->flu_namelen);
			if (info->flu_hash == FLOOKUP_INFO_HASH_UNSET || ADDR_ISUSER(info->flu_name))
				info->flu_hash = fdirent_hash(result->pprd_ent.fd_name, result->pprd_ent.fd_namelen);
			result->pprd_ent.fd_hash   = info->flu_hash;
			result->pprd_ent.fd_refcnt = 1; /* +1: return */
			result->pprd_ent.fd_ops    = &procfs_perproc_root_dirent_ops;
			if (!taskpid_isaprocess(pid)) /* Threads have an alternate directory layout (no "task" sub-directory). */
				result->pprd_ent.fd_ops = &procfs_pertask_root_dirent_ops;
//			result->pprd_ent.fd_ino    = procfs_perproc_ino(pid, &procfs_perproc_root_ops); /* Not needed; we've got `fdo_getino()' */
			DBG_memset(&result->pprd_ent.fd_ino, 0xcc, sizeof(result->pprd_ent.fd_ino));
			result->pprd_ent.fd_type   = DT_DIR;
			return &result->pprd_ent;
		}
	}
notapid:
	return procfs_root_find_static_file(info);
}



struct procfs_root_direnum
#ifdef __cplusplus
    : fdirenum                 /* Underlying enumerator */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct fdirenum prd_enum;  /* Underlying enumerator */
#endif /* !__cplusplus */
	uintptr_t       prd_index; /* [lock(ATOMIC)] Enumeration index.
	                            * For entries `< PROCFS_ROOT_COUNT', index into `procfs_root_files'.
	                            * Otherwise, `- PROCFS_ROOT_COUNT' is a lower bound for the UPID  of
	                            * the next thread that should be enumerated. */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL procfs_root_direnum_v_fini)(struct fdirenum *__restrict UNUSED(self)) {
	(void)0; /* no-op */
}

PRIVATE WUNUSED NONNULL((1)) REF struct taskpid *KCALL
find_first_taskpid_greater_or_equal(struct pidns *__restrict ns,
                                    pid_t pid) {
	REF struct taskpid *result;
	if unlikely(pid < 0)
		return NULL;
	pidns_read(ns);
	result = pidns_lookupnextproc_locked(ns, (pid_t)pid);
	pidns_endread(ns);
	return result;
}

PRIVATE NONNULL((1)) size_t KCALL
procfs_root_direnum_ops_v_readdir(struct fdirenum *__restrict self, NCX struct dirent *buf,
                                  size_t bufsize, readdir_mode_t readdir_mode, iomode_t UNUSED(mode))
		THROWS(...) {
	size_t index, newindex;
	ssize_t result;
	struct procfs_root_direnum *me;
	me = (struct procfs_root_direnum *)self;

again:
	/* Read current index. */
	index = atomic_read(&me->prd_index);

	/* Check for EOF */
	if (index < PROCFS_ROOT_COUNT) {
		/* Static files. */
		struct fdirent *ent;
		ent    = procfs_root_files[index];
		result = fdirenum_feedent_fast(buf, bufsize, readdir_mode, ent);
		if (result < 0)
			return (size_t)~result; /* Don't advance directory position. */
		newindex = index + 1;
	} else {
		REF struct taskpid *pid;
		struct pidns *ns = THIS_PIDNS;
		upid_t pid_id;
		u16 namelen;
		char namebuf[lengthof(PRIMAXuN(__SIZEOF_PID_T__))];

		/* Lookup next taskpid entry. */
		pid = find_first_taskpid_greater_or_equal(ns, (pid_t)(index - PROCFS_ROOT_COUNT));
		if (!pid)
			return 0; /* End-of-directory */
		FINALLY_DECREF_UNLIKELY(pid);
		pid_id  = (upid_t)_taskpid_slot_getpidno(pid->tp_pids[ns->pn_ind]);
		namelen = (u16)sprintf(namebuf, "%" PRIuN(__SIZEOF_PID_T__), pid_id);

		/* Feed directory entry. */
		result = fdirenum_feedent_ex(buf, bufsize, readdir_mode,
		                             procfs_perproc_ino(pid, &procfs_perproc_root_ops),
		                             DT_DIR, namelen, namebuf);
		if (result < 0)
			return (size_t)~result; /* Don't advance directory position. */

		/* Next time around, yield a process with a greater PID */
		newindex = PROCFS_ROOT_COUNT + pid_id + 1;
	}

	/* Advance directory position. */
	if (!atomic_cmpxch(&me->prd_index, index, newindex))
		goto again;
	return (size_t)result;
}


PRIVATE WUNUSED pid_t FCALL find_greatest_inuse_pid(void) {
	pid_t result = 0;
	struct taskpid *tpid;
	struct pidns *ns;
	size_t ind;
	ns  = THIS_PIDNS;
	ind = ns->pn_ind;
	pidns_read(ns);
	tpid = ns->pn_tree;
	if likely(tpid) {
		while (tpid->tp_pids[ind].tps_link.rb_rhs)
			tpid = tpid->tp_pids[ind].tps_link.rb_rhs;
		result = _taskpid_slot_getpidno(tpid->tp_pids[ind]);
	}
	pidns_endread(ns);
	return result;
}

PRIVATE NONNULL((1)) pos_t KCALL
procfs_root_direnum_ops_v_seekdir(struct fdirenum *__restrict self,
                                  off_t offset, unsigned int whence)
		THROWS(...) {
	uintptr_t newpos;
	struct procfs_root_direnum *me = (struct procfs_root_direnum *)self;
	switch (whence) {

	case SEEK_SET:
#if __SIZEOF_POS_T__ > __SIZEOF_SIZE_T__
		if unlikely((pos_t)offset > (pos_t)(size_t)-1)
			THROW(E_OVERFLOW);
#endif /* __SIZEOF_POS_T__ > __SIZEOF_SIZE_T__ */
		newpos = (uintptr_t)(pos_t)offset;
		atomic_write(&me->prd_index, newpos);
		break;

	case SEEK_CUR: {
		uintptr_t oldpos;
		do {
			oldpos = atomic_read(&me->prd_index);
			newpos = oldpos + (intptr_t)offset;
			if unlikely(offset < 0 ? newpos > oldpos
			                       : newpos < oldpos)
				THROW(E_OVERFLOW);
		} while (!atomic_cmpxch_weak(&me->prd_index, oldpos, newpos));
	}	break;

	case SEEK_END: {
		uintptr_t dirsiz;
		/* The end of the directory is relative to the largest in-use PID */
		dirsiz = (uintptr_t)find_greatest_inuse_pid() + 1;
		dirsiz += PROCFS_ROOT_COUNT;
		newpos = dirsiz + (intptr_t)offset;
		if unlikely(offset < 0 ? newpos > dirsiz
		                       : newpos < dirsiz)
			THROW(E_OVERFLOW);
		atomic_write(&me->prd_index, newpos);
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,
		      whence);
	}
	return (pos_t)newpos;
}


PRIVATE struct fdirenum_ops const procfs_root_direnum_ops = {
	.deo_fini    = &procfs_root_direnum_v_fini,
	.deo_readdir = &procfs_root_direnum_ops_v_readdir,
	.deo_seekdir = &procfs_root_direnum_ops_v_seekdir,
};

#define procfs_root_v_enumsz sizeof(struct procfs_root_direnum)
PRIVATE NONNULL((1)) void KCALL
procfs_root_v_enum(struct fdirenum *__restrict result) {
	struct procfs_root_direnum *rt;
	rt = (struct procfs_root_direnum *)result;
	rt->de_ops    = &procfs_root_direnum_ops;
	rt->prd_index = 0;
}


#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL procfs_notify_startstop)(struct taskpid *__restrict tpid, uint32_t mask) {
	notifyfd_event_name_t name;
	/* FIXME: Don't unconditionally use the root namespace PID (the  PID
	 * used should differ for each inotify receiver, and be based on the
	 * receiver's  canonical PID namespace. Additionally, omit the event
	 * if the receiver isn't supposed to see the process) */
	name = NOTIFYFD_EVENT_NAME_DECIMAL(taskpid_getroottid(tpid));
	_mfile_postfsfilevent_ex(&procfs_super.fs_root, mask, 0, name);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL procfs_root_addproc_postcompletion)(struct sig_completion_context *__restrict context,
                                                  void *buf) {
	struct taskpid *tpid;
	tpid = PIDNS_PROCSIG_DECODE(context->scc_sender);
	procfs_notify_startstop(tpid, IN_CREATE | IN_ISDIR);
	(void)buf;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL procfs_root_delproc_postcompletion)(struct sig_completion_context *__restrict context,
                                                  void *buf) {
	struct taskpid *tpid;
	tpid = PIDNS_PROCSIG_DECODE(context->scc_sender);
	procfs_notify_startstop(tpid, IN_DELETE | IN_ISDIR);
	(void)buf;
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL procfs_root_addproc_completion)(struct sig_completion *__restrict self,
                                              struct sig_completion_context *__restrict context,
                                              void *buf, size_t bufsize) {
	(void)buf;
	(void)bufsize;
	sig_completion_reprime(self, true);
	context->scc_post = &procfs_root_addproc_postcompletion;
	return 0;
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL procfs_root_delproc_completion)(struct sig_completion *__restrict self,
                                              struct sig_completion_context *__restrict context,
                                              void *buf, size_t bufsize) {
	(void)buf;
	(void)bufsize;
	sig_completion_reprime(self, true);
	context->scc_post = &procfs_root_delproc_postcompletion;
	return 0;
}


struct procfs_root_notify_controller {
	struct sig_completion pfrnc_addproc_completion; /* Hook for `pidns_root.pn_addproc' */
	struct sig_completion pfrnc_delproc_completion; /* Hook for `pidns_root.pn_delproc' */
};

PRIVATE BLOCKING NONNULL((1)) void *KCALL
procfs_root_v_notify_attach(struct mfile *__restrict self)
		THROWS(E_BADALLOC, ...) {
	struct procfs_root_notify_controller *result;
	assert(self == &procfs_super.fs_root);
	(void)self;
	result = (REF struct procfs_root_notify_controller *)kmalloc(sizeof(struct procfs_root_notify_controller),
	                                                             GFP_NORMAL);
	sig_completion_init(&result->pfrnc_addproc_completion, &procfs_root_addproc_completion);
	sig_completion_init(&result->pfrnc_delproc_completion, &procfs_root_delproc_completion);
	sig_connect_completion_for_poll(&pidns_root.pn_addproc, &result->pfrnc_addproc_completion);
	sig_connect_completion_for_poll(&pidns_root.pn_delproc, &result->pfrnc_delproc_completion);
	printk(KERN_INFO "[procfs] Notify object attached to '/proc' [cookie:%p]\n", result);
	return result; /* This will be destroyed by `procfs_root_v_notify_detach' */
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL procfs_root_v_notify_detach)(struct mfile *__restrict self, void *cookie) {
	struct procfs_root_notify_controller *controller;
	printk(KERN_INFO "[procfs] Notify object detached from '/proc' [cookie:%p]\n", cookie);
	assert(self == &procfs_super.fs_root);
	(void)self;
	controller = (struct procfs_root_notify_controller *)cookie;

	/* Disconnect signal completion callbacks and free the controller. */
	sig_completion_disconnect(&controller->pfrnc_addproc_completion);
	sig_completion_disconnect(&controller->pfrnc_delproc_completion);
	kfree(controller);
}

PRIVATE struct mfile_stream_ops const procfs_root_v_stream_ops = {
	.mso_open          = &fsuper_v_open,
	.mso_stat          = &fsuper_v_stat,
	.mso_ioctl         = &fsuper_v_ioctl,
	.mso_notify_attach = &procfs_root_v_notify_attach,
	.mso_notify_detach = &procfs_root_v_notify_detach,
};
#else /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
#define procfs_root_v_stream_ops fsuper_v_stream_ops
#endif /* !CONFIG_HAVE_KERNEL_FS_NOTIFY */

INTERN_CONST struct fsuper_ops const procfs_super_ops = {
	.so_fdir = {
		.dno_node = {
			.no_file = {
				.mo_destroy = (typeof_field(struct mfile_ops, mo_destroy))(void *)-1,
				.mo_changed = &fsuper_v_changed,
				.mo_stream  = &procfs_root_v_stream_ops,
			},
			.no_free   = (typeof_field(struct fnode_ops, no_free))(void *)-1,
			.no_wrattr = &fnode_v_wrattr_noop,
		},
		.dno_lookup = &procfs_root_v_lookup,
		.dno_enumsz = procfs_root_v_enumsz,
		.dno_enum   = &procfs_root_v_enum,
	},
};


/* Assign `tms' for timestamps. */
PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(FCALL initialize_timestamps)(struct fdirent *const *__restrict files, size_t count,
                                     struct timespec const *__restrict tms) {
	size_t i;
	for (i = 0; i < count; ++i) {
		struct fnode *node;
		struct constdirent *ent = fdirent_asconst(files[i]);
		assert(ent->cd_ops == &constdirent_ops);
		node = ent->cd_node;

		/* Assign timestamps. */
		node->mf_atime = *tms;
		node->mf_mtime = *tms;
		node->mf_ctime = *tms;
		node->mf_btime = *tms;

		/* Assign Inode number */
		node->fn_ino = (ino_t)skew_kernel_pointer(node);

		/* Recurse on directories */
		if (node->mf_ops == &constdir_ops.dno_node.no_file) {
			struct constdir *dir = fnode_asconstdir(node);
			initialize_timestamps(dir->cd_entv, dir->cd_entc, tms);
		}
	}
}

/* Procfs driver initialization. */
PRIVATE DRIVER_INIT void KCALL procfs_init(void) {
	struct timespec now = realtime();

	/* Assign the current time as timestamp value to all statically allocated files. */
	initialize_timestamps(procfs_root_files,
	                      PROCFS_ROOT_COUNT,
	                      &now);

	/* Fill in the inode value for the procfs root. */
	procfs_super.fs_root.fn_ino   = (ino_t)skew_kernel_pointer(&procfs_super.fs_root);
	procfs_super.fs_root.mf_atime = now;
	procfs_super.fs_root.mf_mtime = now;
	procfs_super.fs_root.mf_ctime = now;
	procfs_super.fs_root.mf_btime = now;

	/* Register the filesystem type. */
	ffilesys_register(&procfs_filesys);
}

/* Procfs driver finalization. */
PRIVATE DRIVER_FINI void KCALL procfs_fini(void) {
	ffilesys_unregister(&procfs_filesys);
}


DECL_END

#endif /* !GUARD_MODPROCFS_PROCFS_C */
