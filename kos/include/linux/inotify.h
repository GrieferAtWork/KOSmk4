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
/* (#) Portability: Linux (/usr/include/linux/inotify.h) */
#ifndef _LINUX_INOTIFY_H
#define _LINUX_INOTIFY_H 1

#include <linux/fcntl.h>
#include <linux/types.h>
#include <features.h>

#if defined(__KOS__) || defined(__linux__)

#ifdef __CC__
__DECL_BEGIN

/* Structure read(2)d from file descriptors created by `inotify_init(2)' */
struct inotify_event {
#if defined(__USE_KOS_KERNEL) && defined(__USE_KOS_PURE)
	__s32 ine_wd;      /* Watch token (return value of `inotify_add_watch(2)') */
	__u32 ine_mask;    /* The type of event that occurred (one of `IN_*'; optionally or'd with `IN_ISDIR') */
	__u32 ine_cookie;  /* Event cookie (for connecting related events).
	                    * Only used by `IN_MOVED_FROM' / `IN_MOVED_TO'.
	                    * When not used, set to `0'. */
	__u32 ine_len;     /* Length of `ine_name', including a trailing `NUL' character.
	                    * When `ine_wd' isn't a directory, or the event itself refers
	                    * to the directory itself, this is set to `0'. */
	__COMPILER_FLEXIBLE_ARRAY(char, ine_name); /* [len] Filename (only present when `len != 0') */
#elif defined(__USE_KOS_KERNEL)
	union { __s32 ine_wd;     __s32 wd;     };
	union { __u32 ine_mask;   __u32 mask;   };
	union { __u32 ine_cookie; __u32 cookie; };
	union {
		struct { __u32 ine_len; __COMPILER_FLEXIBLE_ARRAY(char, ine_name); };
		struct { __u32 len;     __COMPILER_FLEXIBLE_ARRAY(char, name); };
	};
#else /* ... */
	__s32 wd;      /* Watch token (return value of `inotify_add_watch(2)') */
	__u32 mask;    /* The type of event that occurred (one of `IN_*'; optionally or'd with `IN_ISDIR') */
	__u32 cookie;  /* Event cookie (for connecting related events).
	                * Only used by `IN_MOVED_FROM' / `IN_MOVED_TO'.
	                * When not used, set to `0'. */
	__u32 len;     /* Length of `name', including a trailing `NUL' character.
	                * When `wd' isn't a directory, or the event itself refers
	                * to the directory itself, this is set to `0'. */
	__COMPILER_FLEXIBLE_ARRAY(char, name); /* [len] Filename (only present when `len != 0') */
#endif /* !... */
};

__DECL_END
#endif /* __CC__ */

/* Valid events to listen for (passed as `mask' to `inotify_add_watch(2)')
 *
 * When monitoring a directory:
 * [*] ... can happen for both the directory itself _AND_ for files within
 * [+] ... can only happen for files within
 * [!] Only generated for the monitored object itself (irregardless of that being a directory) */
#define IN_ACCESS        0x00000001 /* [+] File was accessed (e.g. `read(2)'; internal: `mfile::mf_atime' changed, except from `utime(2)') */
#define IN_MODIFY        0x00000002 /* [+] File was modified (e.g. `write(2)'; internal: `mfile::mf_mtime' changed, except from `utime(2)') */
#define IN_ATTRIB        0x00000004 /* [*] File attributes changed (internal: chmod, chown, utime, link/unlink (if st_nlink changes)) */
#define IN_CLOSE_WRITE   0x00000008 /* [+] File was closed for write (internal: `filehandle_destroy()' w/ IO_CANWRITE) */
#define IN_CLOSE_NOWRITE 0x00000010 /* [*] File was closed for read (internal: `filehandle_destroy()' w/o IO_CANWRITE) */
#define IN_OPEN          0x00000020 /* [*] File was opened (internal: `filehandle_new()' was called) */
#define IN_MOVED_FROM    0x00000040 /* [+] During rename(2): generated for source directory (same `inotify_event::cookie' as in `IN_MOVED_TO'; internal: called after `fdirnode_ops::dno_rename') */
#define IN_MOVED_TO      0x00000080 /* [+] During rename(2): generated for target directory (same `inotify_event::cookie' as in `IN_MOVED_FROM'; internal: called after `fdirnode_ops::dno_rename') */
#define IN_CREATE        0x00000100 /* [+] File or directory create within watched directory (internal: called after `fdirnode_ops::dno_mkfile') */
#define IN_DELETE        0x00000200 /* [+] File or directory deleted from watched directory (internal: called after `fdirnode_ops::dno_unlink') */
#define IN_DELETE_SELF   0x00000400 /* [!] Monitored file/dir was deleted (often followed by `IN_IGNORED'; internal: called after `fdirnode_ops::dno_unlink') */
#define IN_MOVE_SELF     0x00000800 /* [!] Monitored file/dir was moved (internal: called after `fdirnode_ops::dno_rename') */
#define IN_ISDIR         0x40000000 /* FLAG: the originating object is a directory. */


/* Additional events that are always send (don't include these in `mask' to `inotify_add_watch(2)') */
#define IN_UNMOUNT    0x00002000 /* [!] The filesystem containing the monitored object was unmounted (followed by `IN_IGNORED'; internal: called during `fsuper_delete()') */
#define IN_Q_OVERFLOW 0x00004000 /* [ ] Event queue overflow (no more events can be enqueued until you read(2) some; `ine_wd' is set to `-1') */
#define IN_IGNORED    0x00008000 /* [!] Watch was removed (either via `inotify_rm_watch(2)', `unlink(2)', `rename(2)' or `unmount(2)'; internally: <explicit request> or `mfile_delete()') */


/* Helper macros */
#define IN_CLOSE (IN_CLOSE_WRITE | IN_CLOSE_NOWRITE) /* Any kind of `close(2)' */
#define IN_MOVE  (IN_MOVED_FROM | IN_MOVED_TO)       /* Rename _into_ directory, as well as _out_ _of_ directory. */


/* Additional flags for `inotify_add_watch(2)' (affect how a watch is created) */
/*efine IN_UNMOUNT     0x00002000  * Seems to be ignored if passed to `inotify_add_watch(2)' */
/*efine IN_Q_OVERFLOW  0x00004000  * Seems to be ignored if passed to `inotify_add_watch(2)' */
/*efine IN_IGNORED     0x00008000  * Seems to be ignored if passed to `inotify_add_watch(2)' */
#define IN_ONLYDIR     0x01000000 /* Fail with `E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_WATCH' if not a directory */
#define IN_DONT_FOLLOW 0x02000000 /* Use `AT_SYMLINK_NOFOLLOW' when walking the user-given path. */
#define IN_EXCL_UNLINK 0x04000000 /* After `fdirnode_ops::dno_unlink', remove the file's  `inotify_controller'
                                   * from the directory's `dn_dnotify->dnc_files'  (meaning it will no  longer
                                   * generate events, as it otherwise might, especially in directories such as
                                   * `/tmp' where files are often used for a while after first being unlink'd) */
#define IN_MASK_CREATE 0x10000000 /* Return `-EEXIST' if the named file is already being watched */
#define IN_MASK_ADD    0x20000000 /* If the named file is already being watched, or' the new events to its mask. (else: replace its mask) */
/*efine IN_ISDIR       0x40000000  * Seems to be ignored if passed to `inotify_add_watch(2)' */
#define IN_ONESHOT     0x80000000 /* Only allow 1 event to be generated before the named file is unwatched once again */


/* List of all recognized events. */
#define IN_ALL_EVENTS                                       \
	(IN_ACCESS | IN_MODIFY | IN_ATTRIB | IN_CLOSE_WRITE |   \
	 IN_CLOSE_NOWRITE | IN_OPEN | IN_MOVED_FROM |           \
	 IN_MOVED_TO | IN_CREATE | IN_DELETE | IN_DELETE_SELF | \
	 IN_MOVE_SELF)


/* Values for `inotify_init1(2)'s `flags' argument */
#define IN_NONBLOCK __O_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#define IN_CLOEXEC  __O_CLOEXEC  /* Close the file during exec() */
#ifdef __KOS__
#define IN_CLOFORK  __O_CLOFORK  /* Close the handle when the file descriptors are unshared (s.a. `CLONE_FILES') */
#endif /* __KOS__ */

#endif /* __KOS__ || __linux__ */

#endif /* _LINUX_INOTIFY_H */
