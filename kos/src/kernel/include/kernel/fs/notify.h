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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_NOTIFY_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_NOTIFY_H 1

#include <kernel/compiler.h>

#include <kernel/fs/notify-config.h> /* CONFIG_HAVE_KERNEL_FS_NOTIFY */

#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
#include <kernel/mman/mfile.h>
#include <kernel/types.h>
#include <sched/sig.h>

#include <hybrid/sched/atomic-lock.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>

#include <linux/inotify.h>

#ifdef __CC__
DECL_BEGIN

/*
 * Linux-compatible filesystem notifications
 *
 * - Every  mfile  has a  lazily-initialized  and self-deleting  (when  no longer  needed) field:
 *   >> struct inotify_controller *mf_notify; // [0..1][owned][lock(!PREEMPTION && :notify_lock)]
 *
 * - Files not currently loaded are  not monitored, and no  attempt is made to  load
 *   more files  from disk.  The case  where the  directory may  contain other  hard
 *   references to already opened files for which we simply don't know that they are
 *   also apart of the directory now being monitored is ignored:
 *   $ echo Content > /opt/subdir/testfile
 *   $ ln -P /opt/subdir/testfile /opt/testfile-alias
 *   $ sync && cc                    # Make the kernel forget about the new hardlink
 *   >> a = inotify("/opt/subdir/")
 *   >> b = inotify("/opt/")
 *   $ touch /opt/subdir/testfile    # Only  guarantied  to send  notification  to "a",
 *                                   # as kernel may not know about hardlink in "/opt/"
 *   $ touch /opt/testfile-alias     # Following everything  above,  this  will  notify
 *                                   # both "a" and "b", since at this point both files
 *                                   # are once again  visible in  the kernel's  cache.
 *   When you start to monitor a directory and want to make sure that files opened
 *   via paths outside of your directory (but that may also appear via  hard-links
 *   within your directory) are being monitored properly, you have to traverse the
 *   directory at least once (thus forcing the  kernel to load and bind all  files
 *   within  the directory at least once). Else, changes may not be visible as has
 *   been described above (though keep in mind that this only happens if hardlinks
 *   come into play)!
 *
 * - Because any given  file can  appear in more  than one  directory, and  because
 *   events  generated  by  files  must  be  send  to  containing  directories, any
 *   `inotify_controller' has a 0..n list of attached `dnotify_controller'  objects
 *   that  must all be notified when an event happens on the file. But see the case
 *   above which somewhat restricts this ability where watching a directory doesn't
 *   strictly  guaranty that  changes caused by  secondary hardlinks of  a file are
 *   always visible in directories other than those along the path to the file that
 *   is actually being modified.
 *
 * - Additionally,  creating new files  in a directory that  has a non-NULL notify
 *   controller  must  see those  files be  created  with their  notify controller
 *   already allocated, and set-up to forward events to the containing directory's
 *   controller.
 *
 *
 *
 * Ownership/Data-relation diagram:
 * ```
 *         [fdirnode] <══════════════════════════> [dnotify_controller] ═════╗
 *            ^                                         │          ^         ║
 *            ║                                     dnc_files      │         ║
 *            ║                                      [0..n]      [...]       ║
 *            ║                                       [...]     inc_dirs     ║
 *            ║                                         │        [0..n]      ║
 *            v             mf_notify                   v          │         ║
 *         [mfile] ──────────[0..1]──────────────> [inotify_controller] <════╝
 *            ^         [owned,notify_lock]             │
 *            │                                         │
 *          [1..1]                                inc_listeners
 *         nl_file                                   [0..n]
 *    [ref,notify_lock]                           [notify_lock]
 *            │                                         │
 *      ┌─> [notify_listener] <─────────────────────────┘
 *      │          │
 *      │        [1..1]
 *    [0..n]    nl_notfd
 *  nf_listenv  [const]
 *   [owned]       │
 *      │          v
 *      └───── [notifyfd]
 * ```
 *
 * NOTES:
 *   - `mf_notify' is lazily allocated, and deleted once `inc_listeners' and `inc_dirs' become empty
 *   - `dnc_files'  and  `inc_dirs' form  the N-to-N  relation  between files  and containing
 *     directories. When a `fnode' is allocated for a monitored directory, it also allocates:
 *      - a `struct inotify_controller' for the node itself
 *      - a `struct dnotify_link' that's then used to link the node's `struct inotify_controller'
 *        with the containing directory's `struct dnotify_controller'.
 *     When an already-loaded `fnode' is accessed via `fdirent_ops::fdo_opennode', and the containing
 *     directory is currently being monitored, then a `struct dnotify_link' is allocated to link  the
 *     node to its directory (unless this link has already been established)
 *
 */

struct fdirnode;
struct fdirent;
struct fnode;
struct mfile;

struct dnotify_link;
struct notifyfd;
struct notify_listener;
struct dnotify_controller;
struct inotify_controller;

LIST_HEAD(notify_listener_list, notify_listener);
LIST_HEAD(dnotify_link_list, dnotify_link);

/* SMP-lock  for filesystem event notify. -- We use a global lock for this because
 * the alternative would be to set-up many smaller locks, each of which would also
 * need to have a  list of lock-ops, which  probably wouldn't actually make  stuff
 * faster since filesystem event notification is usually a brief process. */
#ifndef CONFIG_NO_SMP
DATDEF struct atomic_lock notify_lock;
#endif /* !CONFIG_NO_SMP */
#define notify_lock_acquire()    atomic_lock_acquire_smp(&notify_lock)
#define notify_lock_release()    atomic_lock_release_smp(&notify_lock)
#define notify_lock_acquire_br() atomic_lock_acquire_smp_b(&notify_lock)
#define notify_lock_release_br() atomic_lock_release_smp_b(&notify_lock)



struct notify_listener {
	struct notifyfd            *nl_notfd; /* [1..1][valid_if(nl_file)][const] Associated notify FD */
	REF struct mfile           *nl_file;  /* [0..1][lock(!PREEMPTION && :notify_lock)] Attached notification controller. (only NULL if deleted) */
	LIST_ENTRY(notify_listener) nl_link;  /* [0..1][valid_if(nl_file)][lock(!PREEMPTION && :notify_lock)] Link in list of listeners attached to `nl_file->mf_notify' */
	uint32_t                    nl_mask;  /* [lock(!PREEMPTION && :notify_lock)] Mask of events to listen fork (set of `IN_ALL_EVENTS | IN_ONESHOT | IN_EXCL_UNLINK') */
#if __SIZEOF_POINTER__ > 4
	byte_t _nl_pad[__SIZEOF_POINTER__ - 4]; /* ... */
#endif /* __SIZEOF_POINTER__ > 4 */
};



/* Flag for `struct notifyfd_event::nfe_wd'. - If set, indicates `IN_ISDIR' */
#if __SIZEOF_INT__ == 4
#define NOTIFYFD_EVENT_ISDIR_FLAG 0x80000000u
#elif __SIZEOF_INT__ == 8
#define NOTIFYFD_EVENT_ISDIR_FLAG 0x8000000000000000u
#elif __SIZEOF_INT__ == 2
#define NOTIFYFD_EVENT_ISDIR_FLAG 0x8000u
#elif __SIZEOF_INT__ == 1
#define NOTIFYFD_EVENT_ISDIR_FLAG 0x80u
#else /* __SIZEOF_INT__ == ... */
#error "Unsupported sizeof(int)"
#endif /* __SIZEOF_INT__ != ... */

struct notifyfd_event {
	unsigned int        nfe_wd;     /* [const] Descriptor number. (most significant bit represents `IN_ISDIR') */
	uint16_t            mfe_mask;   /* [const] Event mask. */
	uint16_t            mfe_cookie; /* [const] Event cookie */
	REF struct fdirent *mfe_name;   /* [0..1][const] Name of associated file (or NULL if not a child-in-directory-event) */
};

/* The main NOTIFYFD object (as also exposed via `HANDLE_TYPE_NOTIFYFD') */
struct notifyfd {
	refcnt_t                nf_refcnt;  /* Reference counter. */
	SLIST_ENTRY(notifyfd)  _nf_blist;   /* [lock(SET_NON_NULL(!PREEMPTION && :notify_lock),
	                                     *       SET_NULL(DID_SET_NON_NULL && ATOMIC))]
	                                     * Used internally. */
	struct notify_listener *nf_listenv; /* [0..nf_listenc][owned][lock(!PREEMPTION && :notify_lock)]
	                                     * List  of listeners. (Index is "watch descriptor"; deleted
	                                     * entries are identified by `nl_file == NULL'). */
	unsigned int            nf_listenc; /* [lock(!PREEMPTION && :notify_lock)] # of allocated entries in `nf_listenv'. */
	unsigned int            nf_eventr;  /* [lock(!PREEMPTION && :notify_lock)][< nf_eventa] Index of next unread event */
	unsigned int            nf_eventc;  /* [lock(!PREEMPTION && :notify_lock)][<= nf_eventa] Number of pending unread events */
	unsigned int            nf_eventa;  /* [const] Total number of allocated events (including the failsafe overflow-event) */
	struct sig              nf_avail;   /* Signal broadcast when `nf_eventc' becomes non-zero. When
	                                     * `nf_eventa == 1', broadcast every time a monitored event
	                                     * happens (though  in some  situations, multiple  parallel
	                                     * broadcasts may be merged into one single one) */
	COMPILER_FLEXIBLE_ARRAY(struct notifyfd_event,
	                        nf_eventv); /* [nf_eventa] Vector of pending events. */
};

/* Check if `fd' is being used. */
#define notifyfd_fdused(self, fd) ((self)->nf_listenv[fd].nl_file != __NULLPTR)


/* Destroy a given notifyfd object. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL notifyfd_destroy)(struct notifyfd *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct notifyfd, nf_refcnt, notifyfd_destroy)

/* >> /proc/sys/fs/inotify/max_queued_events
 * Default # of max pending events in newly created `struct notifyfd' */
DATDEF unsigned int notifyfd_default_maxevents;

/* Create a new notifyfd object.
 * @param: num_events: The max number of unread pending events (excluding the failsafe overflow-event) */
FUNDEF ATTR_RETNONNULL WUNUSED REF struct notifyfd *KCALL
notifyfd_new(unsigned int num_events) THROWS(E_BADALLOC);

/* Add a new watch (listener) for `file' to `self'
 * NOTE: This function is only `BLOCKING' because `file->mf_ops->mo_stream_ops->mso_notify_attach'
 *       is  allowed  to  be `BLOCKING',  and  this function  may  need to  invoke  said operator!
 * @param: mask_and_flags: Set of `IN_ALL_EVENTS', optionally or'd with:
 *          - IN_EXCL_UNLINK | IN_ONESHOT: Include as bits in `notify_listener::nl_mask'
 *          - IN_MASK_ADD:    Or valid bits from `mask' with any pre-existing watch events
 *          - IN_MASK_CREATE: Return `-EEXIST' if `file' is already being watched.
 * @return: * :      The watch descriptor (index into `self->nf_listenv')
 * @return: -EEXIST: `IN_MASK_CREATE' was given and `file' is already being monitored. */
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) unsigned int KCALL
notifyfd_addwatch(struct notifyfd *__restrict self,
                  struct mfile *__restrict file,
                  uint32_t mask_and_flags)
		THROWS(E_BADALLOC);


/* Remove the watch descriptor `watchfd' (as previously returned by `notifyfd_addwatch')
 * @return: true:  Successfully deleted `watchfd'.
 * @return: false: The given `watchfd' was already deleted. */
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(KCALL notifyfd_rmwatch)(struct notifyfd *__restrict self,
                                unsigned int watchfd);






/* Descriptor for link between `inotify_controller' and `dnotify_controller' */
struct dnotify_link {
	LLRBTREE_NODE(dnotify_link)    dnl_dirnode; /* [1..1][lock(!PREEMPTION && :notify_lock)] Node in `dnl_dir->dnc_files' */
	struct dnotify_controller     *dnl_dir;     /* [1..1][const] Associated directory. */
#ifdef __WANT_DNOTIFY_LINK__dnl_fildead
	union {
		SLIST_ENTRY(dnotify_link) _dnl_fildead; /* Used internally during mfile destruction */
		LIST_ENTRY(dnotify_link)   dnl_fillink; /* [1..1][lock(!PREEMPTION && :notify_lock)] Link entry in `dnl_fil->inc_dirs' */
	};
#else /* __WANT_DNOTIFY_LINK__dnl_fildead */
	LIST_ENTRY(dnotify_link)       dnl_fillink; /* [1..1][lock(!PREEMPTION && :notify_lock)] Link entry in `dnl_fil->inc_dirs' */
#endif /* !__WANT_DNOTIFY_LINK__dnl_fildead */
#ifdef __WANT_DNOTIFY_LINK__dnl_rbword
	union {
		struct inotify_controller *dnl_fil;     /* [1..1][const] Associated file. (least significant bit is R/B-bit for `dnl_dirnode') */
		uintptr_t                 _dnl_rbword;  /* [lock(!PREEMPTION && :notify_lock)] R/B-word for `dnl_dirnode' */
	};
#else /* __WANT_DNOTIFY_LINK__dnl_rbword */
	struct inotify_controller     *dnl_fil;     /* [1..1][const] Associated file. (least significant bit is R/B-bit for `dnl_dirnode') */
#endif /* !__WANT_DNOTIFY_LINK__dnl_rbword */
	REF struct fdirent            *dnl_ent;     /* [1..1][const] Directory entry of `dnl_fil'. Note: the potential reference
	                                             * loop that exists when `fdirent'  also references `:nl_file' is solved  by
	                                             * the fact that `:nl_file->mf_notify' is  cleared when all event  listeners
	                                             * (inc_listeners+inc_dirs) have been removed. */
};

/* Allocate/free a given `struct dnotify_link' */
#define dnotify_link_alloc()       ((struct dnotify_link *)kmalloc(sizeof(struct dnotify_link), GFP_NORMAL))
#define dnotify_link_xfree(self)   kfree(self)
#define dnotify_link_free(self)    kfree(self)
#define dnotify_link_fini(self)    decref((self)->dnl_ent)
#define dnotify_link_destroy(self) (dnotify_link_fini(self), dnotify_link_free(self))

/* Helpers for accessing fields of `self' */
#define dnotify_link_getdir(self) ((self)->dnl_dir)
#define dnotify_link_getfil(self) ((struct inotify_controller *)((uintptr_t)(self)->dnl_fil & ~1))
#define dnotify_link_getent(self) ((self)->dnl_ent)

/* dnotify_link tree API. (s.a. `struct dnotify_controller::dnc_files') */
FUNDEF NOBLOCK ATTR_PURE WUNUSED struct dnotify_link *NOTHROW(FCALL dnotify_link_tree_locate)(/*nullable*/ struct dnotify_link *root, struct fdirent const *key);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL dnotify_link_tree_insert)(struct dnotify_link **__restrict proot, struct dnotify_link *__restrict node);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL dnotify_link_tree_removenode)(struct dnotify_link **__restrict proot, struct dnotify_link *__restrict node);


/* The base notification controller as pointed-to by `struct mfile::mf_notify' */
struct inotify_controller {
#ifdef __WANT_INOTIFY_CONTROLLER__inc_deadlnk
	union {
		struct notify_listener_list      inc_listeners; /* [0..n][lock(!PREEMPTION && :notify_lock)] List of attached listeners */
		SLIST_ENTRY(inotify_controller) _inc_deadlnk;   /* Used internally during destruction */
	};
#else /* __WANT_INOTIFY_CONTROLLER__inc_deadlnk */
	struct notify_listener_list inc_listeners; /* [0..n][lock(!PREEMPTION && :notify_lock)] List of attached listeners */
#endif /* !__WANT_INOTIFY_CONTROLLER__inc_deadlnk */
	struct dnotify_link_list    inc_dirs;      /* [0..n][lock(!PREEMPTION && :notify_lock)]
	                                            * [*->dnl_fil == this][link(dnl_fillink)]
	                                            * Directories containing this file/directory. */
	struct mfile               *inc_file;      /* [1..1][lock(!PREEMPTION && :notify_lock)] Associated file */
	void                       *inc_fhnd;      /* [?..?][lock(!PREEMPTION && :notify_lock)] Cookie returned by `mso_notify_attach(inc_file)' */
};
#define inotify_controller_isdnotify(self) mfile_isdir((self)->inc_file)
#define inotify_controller_asdnotify(self) ((struct dnotify_controller *)(self))

/* `struct mfile::mf_notify' is actually a `struct dnotify_controller' when `mfile_isdir(inc_file)' */
struct dnotify_controller
#ifdef __cplusplus
    : inotify_controller                   /* Underlying inotify controller */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct inotify_controller   dnc_icon;  /* Underlying inotify controller */
#endif /* !__cplusplus */
#ifdef __INTELLISENSE__
	struct dnotify_link        *dnc_files; /* [0..n][lock(!PREEMPTION && :notify_lock)]
	                                        * [*->dnl_dir == this][link(dnl_dirnode)]
	                                        * [owned] Files in this directory. - Always
	                                        * `NULL' when  `LIST_EMPTY(inc_listeners)'. */
#else /* __INTELLISENSE__ */
	LLRBTREE_ROOT(dnotify_link) dnc_files; /* [0..n][lock(!PREEMPTION && :notify_lock)]
	                                        * [*->dnl_dir == this][link(dnl_dirnode)]
	                                        * [owned] Files in this directory. - Always
	                                        * `NULL' when  `LIST_EMPTY(inc_listeners)'. */
#endif /* !__INTELLISENSE__ */
};

/* Allocate/free notification controllers. */
#define inotify_controller_alloc()     ((struct inotify_controller *)kmalloc(sizeof(struct inotify_controller), GFP_NORMAL))
#define inotify_controller_xfree(self) kfree(self)
#define inotify_controller_free(self)  kfree(self)
#define dnotify_controller_alloc()     ((struct dnotify_controller *)kmalloc(sizeof(struct dnotify_controller), GFP_NORMAL))
#define dnotify_controller_free(self)  inotify_controller_free(self)


/* If `dir->mf_notify != NULL', ensure that `child_file->mf_notify' has
 * been allocated, and that it is linked in the dnotify child-file list
 * of `dir'.
 *
 * Always inherits a reference to `child_file' that is also always re-
 * returned.  - In case  of an allocation error,  this pointer will be
 * decref'd! */
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
dnotify_controller_bindchild_slow(struct fdirnode *__restrict dir,
                                  struct fdirent *__restrict child_dent,
                                  /*inherit(always)*/ REF struct fnode *child_file)
		THROWS(E_BADALLOC, ...);
EIDECLARE(BLOCKING WUNUSED NONNULL((1, 2)), REF struct fnode *, , KCALL,
          dnotify_controller_bindchild, (struct fdirnode *__restrict dir,
                                         struct fdirent *__restrict child_dent,
                                         /*inherit(always)*/ REF struct fnode *child_file)
		THROWS(E_BADALLOC, ...), {
	if likely(((struct mfile *)dir)->mf_notify == __NULLPTR)
		return child_file; /* Directory isn't being watched --> nothing to do here! */
	return dnotify_controller_bindchild_slow(dir, child_dent, child_file);
});



/* Post filesystem events to the notify controller of  `self'
 * Don't call this function directly -- use the macros below.
 * @param: mask: One of `(IN_ALL_EVENTS | IN_UNMOUNT | IN_IGNORED) & ~(...)' */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL _mfile_postfsevent)(struct mfile *__restrict self, uint16_t mask) ASMNAME("mfile_postfsevent");
/* Same as `_mfile_postfsevent()', but only post to `inc_listeners' */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL _mfile_postfsfilevent)(struct mfile *__restrict self, uint16_t mask) ASMNAME("mfile_postfsfilevent");
/* Same as `_mfile_postfsevent()', but only post to `inc_dirs' */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL _mfile_postfsdirevent)(struct mfile *__restrict self, uint16_t mask) ASMNAME("mfile_postfsdirevent");
/* Same as `_mfile_postfsdirevent()', but has an explicit `cookie' */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL _mfile_postfsdirevent2)(struct mfile *__restrict self, uint16_t mask, uint16_t cookie) ASMNAME("mfile_postfsdirevent2");
/* Same as `_mfile_postfsevent()', but use different masks for `inc_listeners' and `inc_dirs' */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL _mfile_postfsevent_ex)(struct mfile *__restrict self, uint16_t fil_mask, uint16_t dir_mask) ASMNAME("mfile_postfsevent_ex");
#define _mfile_canpostfsevents(self) (__hybrid_atomic_load(&(self)->mf_notify, __ATOMIC_ACQUIRE) != __NULLPTR)
#ifdef __OPTIMIZE_SIZE__
#define _mfile_maybepostfsevent(self, expr_) expr_
#else /* __OPTIMIZE_SIZE__ */
#define _mfile_maybepostfsevent(self, expr_) (void)(_mfile_canpostfsevents(self) && (expr_, 1))
#endif /* !__OPTIMIZE_SIZE__ */
#define _mfile_postfsevent(self, mask)                  _mfile_maybepostfsevent(self, (_mfile_postfsevent)(self, mask))
#define _mfile_postfsfilevent(self, mask)               _mfile_maybepostfsevent(self, (_mfile_postfsfilevent)(self, mask))
#define _mfile_postfsdirevent(self, mask)               _mfile_maybepostfsevent(self, (_mfile_postfsdirevent)(self, mask))
#define _mfile_postfsdirevent2(self, mask, cookie)      _mfile_maybepostfsevent(self, (_mfile_postfsdirevent2)(self, mask, cookie))
#define _mfile_postfsevent_ex(self, fil_mask, dir_mask) _mfile_maybepostfsevent(self, (_mfile_postfsevent_ex)(self, fil_mask, dir_mask))

/* Helper macros for generating inotify events (use these instead of the functions above) */
#define mfile_inotify_accessed(self)         _mfile_postfsevent(self, IN_ACCESS)                    /* TODO */
#define mfile_inotify_modified(self)         _mfile_postfsevent(self, IN_MODIFY)                    /* Implemented */
#define mfile_inotify_attrib(self)           _mfile_postfsevent(self, IN_ATTRIB)                    /* Implemented */
#define mfile_inotify_closewr(self)          _mfile_postfsevent(self, IN_CLOSE_WRITE)               /* TODO */
#define mfile_inotify_closero(self)          _mfile_postfsevent(self, IN_CLOSE_NOWRITE)             /* Implemented */
#define mfile_inotify_opened(self)           _mfile_postfsevent(self, IN_OPEN)                      /* Implemented */
#define mfile_inotify_movefrom(self, cookie) _mfile_postfsdirevent2(self, IN_MOVED_FROM, cookie)    /* TODO */
#define mfile_inotify_moveto(self, cookie)   _mfile_postfsdirevent2(self, IN_MOVED_TO, cookie)      /* TODO */
#define mfile_inotify_moved(self)            _mfile_postfsfilevent(self, IN_MOVE_SELF)              /* TODO */
#define mfile_inotify_created(self)          _mfile_postfsdirevent(self, IN_CREATE)                 /* Implemented */
#define mfile_inotify_deleted(self)          _mfile_postfsevent_ex(self, IN_DELETE_SELF, IN_DELETE) /* Implemented */
#define mfile_inotify_unmount(self)          _mfile_postfsfilevent(self, IN_UNMOUNT)                /* Implemented */
/* TODO: `IN_DELETE' must remove inotify controllers from containing
 *       dir iff any of  dir's listeners have `IN_EXCL_UNLINK'  set. */

/* Special function to post `IN_IGNORED', as well as delete all watch-descriptors of `self' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_inotify_ignored)(struct mfile *__restrict self);
#define mfile_inotify_ignored(self) _mfile_maybepostfsevent(self, (mfile_inotify_ignored)(self)) /* Implemented */



DECL_END
#endif /* __CC__ */
#else /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
/* No-op directory-child-bind */
#define dnotify_controller_bindchild(dir, child_dent, child_file) (child_file)

/* No-op file event triggers */
#define mfile_inotify_accessed(self)         (void)0
#define mfile_inotify_modified(self)         (void)0
#define mfile_inotify_attrib(self)           (void)0
#define mfile_inotify_closewr(self)          (void)0
#define mfile_inotify_closero(self)          (void)0
#define mfile_inotify_opened(self)           (void)0
#define mfile_inotify_movefrom(self, cookie) (void)0
#define mfile_inotify_moveto(self, cookie)   (void)0
#define mfile_inotify_moved(self)            (void)0
#define mfile_inotify_created(self)          (void)0
#define mfile_inotify_deleted(self)          (void)0
#define mfile_inotify_unmount(self)          (void)0
#define mfile_inotify_ignored(self)          (void)0
#endif /* !CONFIG_HAVE_KERNEL_FS_NOTIFY */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_NOTIFY_H */
