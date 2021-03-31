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
#ifndef GUARD_MODPROCFS_FILES_PERPROC_MAP_FILES_C
#define GUARD_MODPROCFS_FILES_PERPROC_MAP_FILES_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/vfs.h>
#include <kernel/mman.h>
#include <kernel/vm.h>
#include <sched/pid.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>

#include "../procfs.h"

DECL_BEGIN

PRIVATE bool KCALL
parse_mapfiles_filename(CHECKED USER /*utf-8*/ char const *name,
                        u16 namelen, fsmode_t mode,
                        void UNCHECKED **__restrict pminaddr,
                        void UNCHECKED **__restrict pmaxaddr) {
	u16 i;
	uintptr_t minaddr, maxaddr, temp;
	minaddr = maxaddr = 0;
	if (namelen < 3)
		goto err; /* Smallest (syntax-)valid filename would be "0-0" */
	/* Load the first part, and be on the lookout for `-' characters.
	 * Note that we  may only ignore  casing for hex-characters  when
	 * `mode & FS_MODE_FDOSPATH' is true. */
	for (i = 0;; ++i) {
		char ch;
		u8 addend;
		if (i >= namelen)
			goto err;
		ch = name[i];
		if (ch >= '0' && ch <= '9') {
			addend = ch - '0';
		} else if (ch >= 'a' && ch <= 'f') {
			addend = 10 + ch - 'a';
		} else if likely(ch == '-') {
			if unlikely(i == 0) /* The first character cannot be a '-' */
				goto err;
			break;
		} else if ((ch >= 'A' && ch <= 'F') && (mode & FS_MODE_FDOSPATH)) {
			addend = 10 + ch - 'A';
		} else {
			goto err; /* Invalid character */
		}
		/* Verify that the resulting address doesn't overflow! */
		temp = (minaddr << 4) | addend;
		if unlikely(temp < minaddr)
			goto err;
		minaddr = temp;
	}
	/* At this point, `i' points at the `-' character in-between.
	 * With  this   in  mind,   we   must  now   load   `maxaddr' */
	++i;
	if (i >= namelen)
		goto err; /* Empty maxaddr-part. */
	do {
		char ch;
		u8 addend;
		ch = name[i];
		if (ch >= '0' && ch <= '9') {
			addend = ch - '0';
		} else if (ch >= 'a' && ch <= 'f') {
			addend = 10 + ch - 'a';
		} else if ((ch >= 'A' && ch <= 'F') && (mode & FS_MODE_FDOSPATH)) {
			addend = 10 + ch - 'A';
		} else {
			goto err; /* Invalid character */
		}
		/* Verify that the resulting address doesn't overflow! */
		temp = (maxaddr << 4) | addend;
		if unlikely(temp < maxaddr)
			goto err;
		maxaddr = temp;
	} while (++i < namelen);
	*pminaddr = (UNCHECKED void *)minaddr;
	*pmaxaddr = (UNCHECKED void *)maxaddr;
	return true;
err:
	return false;
}


INTERN NONNULL((1, 2)) REF struct directory_entry *KCALL
ProcFS_PerProc_MapFiles_Lookup(struct directory_node *__restrict self,
                               CHECKED USER /*utf-8*/ char const *name,
                               u16 namelen, uintptr_t UNUSED(hash), fsmode_t mode)
		THROWS(E_SEGFAULT, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	REF struct directory_entry *result;
	upid_t pid;
	REF struct task *thread;
	REF struct vm *threadmm;
	UNCHECKED void *minaddr;
	UNCHECKED void *maxaddr;
	/* Try to parse the min/max address range from `name' */
	if unlikely(!parse_mapfiles_filename(name, namelen, mode,
	                                     &minaddr, &maxaddr))
		goto err;
	/* Make sure that the given addresses are properly aligned. */
	if (!IS_ALIGNED((uintptr_t)minaddr, PAGESIZE))
		goto err;
	if (!IS_ALIGNED((uintptr_t)maxaddr + 1, PAGESIZE))
		goto err;
	/* Lookup the associated thread. */
	pid    = (upid_t)(self->i_fileino & PROCFS_INOTYPE_MAPFILES_PIDMASK);
	thread = pidns_trylookup_task(THIS_PIDNS, pid);
	if unlikely(!thread)
		goto err;
	/* Lookup the associated VM. */
	{
		FINALLY_DECREF_UNLIKELY(thread);
		threadmm = task_getmman(thread);
	}
	{
		FINALLY_DECREF_UNLIKELY(threadmm);
		size_t nodeid = 0;
		struct vm_node *node;
		/* Check if `threadvm' contains a  node that starts at  `minaddr',
		 * and either itself  also ends  at `maxaddr', or  is followed  by
		 * some other node that ends at `maxaddr', with no gap in-between.
		 * Note  that we  could in theory  also check if  all nodes within
		 * this  area could  be merged,  but that  isn't really necessary,
		 * and not doing so doesn't introduce any glaring inconsistencies. */
		vm_treelock_read(threadmm);
		{
			struct mnode_tree_minmax mima;
			/* TODO: mnode_tree_first() */
			mnode_tree_minmaxlocate(threadmm->mm_mappings,
			                        (void *)0, (void *)-1,
			                        &mima);
			node = mima.mm_min;
		}
		for (;;) {
			if unlikely(!node) {
unlock_threadvm_and_goto_err:
				vm_treelock_endread(threadmm);
				goto err;
			}
			if (mnode_getminaddr(node) >= minaddr)
				break;
			++nodeid;
			node = mnode_tree_nextnode(node);
		}
		if (mnode_getminaddr(node) != minaddr)
			goto unlock_threadvm_and_goto_err;
		/* Make sure that there is another node that ends at `maxaddr' */
		while (mnode_getmaxaddr(node) != maxaddr) {
			struct vm_node *succ;
			if (mnode_getmaxaddr(node) > maxaddr)
				goto unlock_threadvm_and_goto_err; /* `maxaddr' is too large */
			succ = mnode_tree_nextnode(node);
			if (!succ)
				goto unlock_threadvm_and_goto_err; /* Non-consecutive */
			if ((byte_t *)mnode_getminaddr(succ) != (byte_t *)mnode_getmaxaddr(node) + 1)
				goto unlock_threadvm_and_goto_err; /* Non-consecutive */
			node = succ;
		}
		vm_treelock_endread(threadmm);
		/* Found it! - It's the `nodeid'th node! */
		result = directory_entry_alloc(namelen);
		/* Re-print  the  proper  filename to  prevent  duplicate access
		 * to a (potentially)  user-space string, as  well as deal  with
		 * the  user-space   filename   having   been   case-insensitive
		 * Note  however that  we can  still assume  that the user-space
		 * filename's length was correct, since if this wasn't the case,
		 * then the call to `parse_mapfiles_filename()' above would have
		 * returned `false' */
		sprintf(result->de_name, "%" PRIxPTR "-%" PRIxPTR,
		        minaddr, maxaddr);
		result->de_ino  = PROCFS_INOMAKE_MAPFILES(pid, nodeid);
		result->de_type = DT_LNK;
		result->de_hash = directory_entry_hash(result->de_name, 1);
	}
	return result;
err:
	return NULL;
}



#define PROCFS_INOTYPE_MAPFILES_NUMMAX \
	((size_t)(PROCFS_INOTYPE_MAPFILES_NUMMASK >> PROCFS_INOTYPE_MAPFILES_NUMSHIFT))

struct mapfiles_enum_data {
	directory_enum_callback_t ed_callback; /* [1..1] Underlying callback for enumerating files */
	void                     *ed_arg;      /* [?..?] Argument to-be passed to `ed_callback' */
	upid_t                    ed_pid;      /* PID of the process associated with the current directory. */
};

PRIVATE ssize_t FCALL
vm_enum_callback_for_mapfiles_enum(void *arg, struct vm_mapinfo *__restrict info) {
	struct mapfiles_enum_data *ctx;
	/* Buffer   for  the  filename   of  the  /map_files/  file.
	 * This has  the  format:  '<pointer>-<pointer>\0',  meaning
	 * that we need 1 ('-') + 1 ('\0') + 2 * (<pointer>),  where
	 * <pointer> has a max length of `sizeof(void *) * 2`, since
	 * the  representation  used   is  always  lower-case   hex. */
	char filename[2 + (2 * (sizeof(void *) * 2))];
	u16 filename_len;
	if (!info->vmi_fspath || !info->vmi_fsname)
		return 0; /* Don't enumerate this one! */
	ctx = (struct mapfiles_enum_data *)arg;
	filename_len = (u16)sprintf(filename, "%" PRIxPTR "-%" PRIxPTR,
	                            info->vmi_min, info->vmi_max);
	/* Enumerate this file mapping. */
	(*ctx->ed_callback)(ctx->ed_arg, filename, filename_len, DT_LNK,
	                    PROCFS_INOMAKE_MAPFILES(ctx->ed_pid,
	                                            info->vmi_index));
	return 1;
}

INTERN NONNULL((1, 2)) void KCALL
ProcFS_PerProc_MapFiles_Enum(struct directory_node *__restrict self,
                             directory_enum_callback_t callback,
                             void *arg)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	REF struct task *thread;
	REF struct vm *threadvm;
	struct mapfiles_enum_data ed;
	/* Lookup the associated thread. */
	ed.ed_pid = (upid_t)(self->i_fileino & PROCFS_INOTYPE_MAPFILES_PIDMASK);
	thread    = pidns_trylookup_task(THIS_PIDNS, ed.ed_pid);
	if unlikely(!thread)
		goto done;
	/* Lookup the associated VM. */
	{
		FINALLY_DECREF_UNLIKELY(thread);
		threadvm = task_getmman(thread);
	}
	{
		FINALLY_DECREF_UNLIKELY(threadvm);
		ed.ed_callback = callback;
		ed.ed_arg      = arg;
		/* Enumerate files from /proc/[pid]/map_files */
		vm_enum(threadvm,
		        &vm_enum_callback_for_mapfiles_enum,
		        &ed);
	}
done:
	;
}


INTERN struct inode_type ProcFS_PerProc_MapFiles_Type = {
	/* .it_fini = */ NULL,
	/* .it_attr = */ {
		/* .a_loadattr = */ NULL,
		/* .a_saveattr = */ NULL,
		/* .a_maskattr = */ NULL,
		/* .a_stat     = */ &ProcFS_PerProc_StatInode,
	},
	/* .it_file = */ {
	},
	{
		/* .it_directory = */ {
			/* .d_readdir = */ NULL,
			/* .d_oneshot = */ {
				/* .o_lookup = */ &ProcFS_PerProc_MapFiles_Lookup,
				/* .o_enum   = */ &ProcFS_PerProc_MapFiles_Enum,
			}
		}
	}
};

PRIVATE NONNULL((1)) size_t KCALL
ProcFS_PerProc_MapFiles_Entry_Readlink(struct symlink_node *__restrict self,
                                       USER CHECKED /*utf-8*/ char *buf,
                                       size_t bufsize)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	REF struct task *thread;
	REF struct vm *threadvm;
	REF struct path *fspath;
	REF struct directory_entry *fsname;
	size_t nth, result;
	upid_t pid;
	/* Lookup the associated thread. */
	nth    = (size_t)((self->i_fileino & PROCFS_INOTYPE_MAPFILES_NUMMASK) >> PROCFS_INOTYPE_MAPFILES_NUMSHIFT);
	pid    = (upid_t)(self->i_fileino & PROCFS_INOTYPE_MAPFILES_PIDMASK);
	thread = pidns_trylookup_task(THIS_PIDNS, pid);
	if unlikely(!thread)
		goto err;
	/* Lookup the associated VM. */
	{
		FINALLY_DECREF_UNLIKELY(thread);
		threadvm = task_getmman(thread);
	}
	{
		struct vm_node *node;
		FINALLY_DECREF_UNLIKELY(threadvm);
		/* find the `nth'th `struct vm_node' within `threadvm' */
		vm_treelock_read(threadvm);
		{
			struct mnode_tree_minmax mima;
			/* TODO: mnode_tree_first() */
			mnode_tree_minmaxlocate(threadvm->mm_mappings,
			                        (void *)0, (void *)-1,
			                        &mima);
			node = mima.mm_min;
		}
		for (;;) {
			if unlikely(!node) {
unlock_threadvm_and_goto_err:
				vm_treelock_endread(threadvm);
				goto err;
			}
			if (!nth)
				break;
			node = mnode_tree_nextnode(node);
			--nth;
		}
		/* Found the node!
		 * Now to load its filesystem path and name. */
		fspath = node->vn_fspath;
		fsname = node->vn_fsname;
		if unlikely(!fspath || !fsname)
			goto unlock_threadvm_and_goto_err;
		incref(fspath);
		incref(fsname);
		vm_treelock_endread(threadvm);
	}
	TRY {
		/* Print the filesystem name. */
		result = path_sprintent(buf,
		                        bufsize,
		                        fspath,
		                        fsname->de_name,
		                        fsname->de_namelen);
	} EXCEPT {
		decref_unlikely(fspath);
		decref_unlikely(fsname);
		RETHROW();
	}
	decref_unlikely(fspath);
	decref_unlikely(fsname);
	return result;
err:
	return 0;
}



INTERN struct inode_type ProcFS_PerProc_MapFiles_Entry_Type = {
	/* .it_fini = */ NULL,
	/* .it_attr = */ {
		/* .a_loadattr = */ NULL,
		/* .a_saveattr = */ NULL,
		/* .a_maskattr = */ NULL,
		/* .a_stat     = */ &ProcFS_PerProc_StatInode,
	},
	/* .it_file = */ {
	},
	{
		 .it_symlink = {
			/* .sl_readlink = */ NULL,
			/* .sl_readlink_dynamic = */ &ProcFS_PerProc_MapFiles_Entry_Readlink
		}
	}
};


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_PERPROC_MAP_FILES_C */
