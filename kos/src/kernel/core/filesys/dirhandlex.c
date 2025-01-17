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
#ifndef GUARD_KERNEL_CORE_FILESYS_DIRHANDLEX_C
#define GUARD_KERNEL_CORE_FILESYS_DIRHANDLEX_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/dirhandle.h>
#include <kernel/fs/dirhandlex.h>
#include <kernel/fs/notify.h>
#include <kernel/fs/path.h>
#include <kernel/malloc.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>

#include <kos/except.h>

#include <assert.h>
#include <atomic.h>
#include <fcntl.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/************************************************************************/
/* Handle operators for `HANDLE_TYPE_DIRHANDLEX'                        */
/************************************************************************/

/* NOTE: most operators were already defined in "./dirhandle.c", with the
 *       exception of the decref() operator, which can't be shared  since
 *       it needs to call `dirhandlex_destroy()' */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL handle_dirhandlex_decref)(REF struct dirhandlex *__restrict self) {
	decref(self);
}


struct dirhandlex_SIGIO_notify_data {
	REF struct dirhandlex *dsnd_dir; /* [1..1] The dirhandle on which to trigger SIGIO. */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL dirhandlex_SIGIO_notify_p)(struct sig_completion_context *__restrict UNUSED(context),
                                         void *buf) {
	struct dirhandlex_hdr *hdr;
	REF struct dirhandlex *dir;
	struct dirhandlex_SIGIO_notify_data *shared;

	/* Load arguments. */
	shared = (struct dirhandlex_SIGIO_notify_data *)buf;
	dir    = shared->dsnd_dir;
	hdr    = dirhandlex_ashdr(dir);

	/* Actually send the signal! */
	{
		REF struct taskpid *proc;
		signo_t signo;
		signo = dirhandlex_hdr_getsigio(hdr);
		proc  = dirhandlex_hdr_gettaskpid(hdr);
		assert(sigvalid(signo));
		_task_raisesignoprocess(proc, signo); /* Raise the signal */
		decref_unlikely(proc);
	}
	decref_unlikely(dir); /* Inherited from `dirhandlex_SIGIO_notify()' */
}

/* Called in order to trigger SIGIO */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL dirhandlex_SIGIO_notify)(struct sig_completion *__restrict self,
                                       struct sig_completion_context *__restrict context,
                                       void *buf, size_t bufsize) {
	struct dirhandlex_hdr *hdr;
	struct dirhandlex *dir;
	struct dirhandlex_SIGIO_notify_data *shared;
	if (bufsize < sizeof(struct dirhandlex_SIGIO_notify_data))
		return sizeof(struct dirhandlex_SIGIO_notify_data);
	shared = (struct dirhandlex_SIGIO_notify_data *)buf;

	/* Load the dirhandle responsible. */
	hdr = container_of(self, struct dirhandlex_hdr, dxh_com);
	dir = dirhandlex_fromhdr(hdr);

	/* Need to get a reference to the associated dirhandle! */
	if (!tryincref(dir))
		return 0; /* Can't send SIGIO like that! */

	/* Re-prime our function so we get re-invoked on the next event! */
	sig_completion_reprime(self, true);

	/* Setup a post-completion callback (our current context doesn't
	 * allow us to actually send signals, so we have to do the  rest
	 * of the work from a post-completion callback) */
	shared->dsnd_dir  = dir; /* Inherit reference. */
	context->scc_post = &dirhandlex_SIGIO_notify_p;
	return sizeof(struct dirhandlex_SIGIO_notify_data);
}



/* Destroy the given dirhandlex object. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL dirhandlex_destroy)(struct dirhandlex *__restrict self) {
	struct dirhandlex_hdr *hdr = dirhandlex_ashdr(self);

	/* Destroy fields of the extended object header. */
	sig_completion_disconnect(&hdr->dxh_com);
	arref_fini(&hdr->dxh_thrio);
	decref_likely(hdr->dxh_notify);

	/* Do the same sort of cleanup as also done by `dirhandle_destroy()'... */
	mfile_inotify_closero(self->dh_enum.de_dir); /* Post `IN_CLOSE_NOWRITE' */
	fdirenum_fini(&self->dh_enum);
	xdecref_unlikely(self->dh_path);
	xdecref_unlikely(self->dh_dirent);

	/* ... With the exception that we need to pass the base address  of
	 *     the header to `kfree()', since it is the actual base-address
	 *     of the kernel object! */
	kfree(hdr);
}


PRIVATE NONNULL((1, 2)) void KCALL
dirhandle_copyenum(struct dirhandle *__restrict dst,
                   struct dirhandle *__restrict src) {
	pos_t pos = fdirenum_seekdir(&src->dh_enum, 0, SEEK_CUR);
	fdirenum_seekdir(&dst->dh_enum, (off_t)pos, SEEK_SET);
}


/* Add/remove a `struct dirhandle_nhdr' prefix from a given directory handle.
 * For  this purpose, a new object needs  to be constructed, which the caller
 * should then use to replace the old object in the caller's handle table. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct dirhandlex *KCALL
dirhandle_xadd(struct dirhandle *__restrict self) {
	REF struct dirhandlex *result;
	struct dirhandlex_hdr *hdr;
	struct fdirnode_ops const *ops;
	struct taskpid *mypid;
	ops = fdirnode_getops(self->dh_enum.de_dir);
	assert(ops->dno_enumsz >= sizeof(struct fdirenum));
	hdr = (REF struct dirhandlex_hdr *)kmalloc(sizeof(struct dirhandlex_hdr) +
	                                           offsetof(struct dirhandlex, dh_enum) +
	                                           ops->dno_enumsz,
	                                           GFP_NORMAL);
	result = dirhandlex_fromhdr(hdr);
	DBG_memset(&result->dh_enum, 0xcc, sizeof(result->dh_enum));
	result->dh_enum.de_dir = self->dh_enum.de_dir;
	incref(result->dh_enum.de_dir);
	TRY {
		/* Construct a directory enumerator. */
		(*ops->dno_enum)(&result->dh_enum);

		/* Construct and attach the notify controller.
		 * NOTE: Still has to be primed by `dirhandlex_setnotify()'!
		 * NOTE: By using `0' for  `num_events', we force the  notify
		 *       logic  to  always trigger  a broadcast  on monitored
		 *       events, whilst also not needing to consume generated
		 *       events! */
		TRY {
			dirhandle_copyenum(result, self);
			hdr->dxh_notify = notifyfd_new(0);
		} EXCEPT {
			fdirenum_fini(&result->dh_enum);
			RETHROW();
		}
	} EXCEPT {
		decref_unlikely(result->dh_enum.de_dir);
		kfree(hdr);
		RETHROW();
	}

	/* Fill in remaining fields. */
	result->dh_refcnt = 1;
	result->dh_path   = xincref(self->dh_path);
	result->dh_dirent = xincref(self->dh_dirent);
	result->dh_dots   = 0;
	mfile_inotify_opened(result->dh_enum.de_dir); /* Post `IN_OPEN' */

	/* Attach a signal completion callback to the notify controller's broadcast. */
	mypid = incref(THIS_TASKPID);
	arref_init(&hdr->dxh_thrio, mypid);
	hdr->dxh_sigio = SIGIO;
	sig_completion_init(&hdr->dxh_com, &dirhandlex_SIGIO_notify);
	sig_connect_completion_for_poll(&hdr->dxh_notify->nf_avail, &hdr->dxh_com);
	return result;
}

#if 0
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct dirhandle *KCALL
dirhandle_xdel(struct dirhandlex *__restrict self) {
	REF struct dirhandle *result;
	result = dirhandle_new(self->dh_enum.de_dir,
	                       self->dh_path,
	                       self->dh_dirent);
	result->dh_dots = atomic_read(&self->dh_dots);

	/* Try to copy directory enumerator positions. */
	TRY {
		dirhandle_copyenum(result, self);
	} EXCEPT {
		decref_likely(result);
		RETHROW();
	}
	return result;
}
#endif


/* Implementation for `fcntl(F_NOTIFY)'
 * @param: flags: Set of `DN_*' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL dirhandlex_setnotify)(struct dirhandlex *__restrict self,
                                    syscall_ulong_t flags) {
	unsigned int watchfd;
	struct dirhandlex_hdr *hdr = dirhandlex_ashdr(self);
	uint32_t mask = IN_MASK_ADD | IN_ONESHOT;

	/* Convert DN_* bits into the appropriate IN_* set of flags. */
#if DN_ACCESS == IN_ACCESS
	mask |= (flags & DN_ACCESS);
#else /* DN_ACCESS == IN_ACCESS */
	if (flags & DN_ACCESS)
		mask |= IN_ACCESS;
#endif /* DN_ACCESS != IN_ACCESS */

#if DN_MODIFY == IN_MODIFY
	mask |= (flags & DN_MODIFY);
#else /* DN_MODIFY == IN_MODIFY */
	if (flags & DN_MODIFY)
		mask |= IN_MODIFY;
#endif /* DN_MODIFY != IN_MODIFY */

#if DN_CREATE == IN_CREATE
	mask |= (flags & DN_CREATE);
#else /* DN_CREATE == IN_CREATE */
	if (flags & DN_CREATE)
		mask |= IN_CREATE;
#endif /* DN_CREATE != IN_CREATE */

#if DN_DELETE == IN_DELETE
	mask |= (flags & DN_DELETE);
#else /* DN_DELETE == IN_DELETE */
	if (flags & DN_DELETE)
		mask |= IN_DELETE;
#endif /* DN_DELETE != IN_DELETE */

#if DN_RENAME == IN_MOVE
	mask |= (flags & DN_RENAME);
#else /* DN_RENAME == IN_MOVE */
	if (flags & DN_RENAME)
		mask |= IN_MOVE;
#endif /* DN_RENAME != IN_MOVE */

#if DN_ATTRIB == IN_ATTRIB
	mask |= (flags & DN_ATTRIB);
#else /* DN_ATTRIB == IN_ATTRIB */
	if (flags & DN_ATTRIB)
		mask |= IN_ATTRIB;
#endif /* DN_ATTRIB != IN_ATTRIB */

	if (flags & DN_MULTISHOT)
		mask &= ~IN_ONESHOT;

	/* Update the underlying watch-descriptor. */
	watchfd = notifyfd_addwatch(hdr->dxh_notify,
	                            self->dh_enum.de_dir,
	                            mask);
	assert(watchfd == 0);
	(void)watchfd;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DIRHANDLEX_C */
