/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_FCNTL_H
#define _BITS_FCNTL_H 1

#include <__stdinc.h>
#include <bits/types.h>
#include <bits/oflags.h>
#include <hybrid/typecore.h>
#include <features.h>

#ifdef __USE_GNU
#include <bits/uio.h>
#endif /* __USE_GNU */

__SYSDECL_BEGIN

#ifdef __CC__
struct flock {
	__INT16_TYPE__ l_type;   /* Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK.	*/
	__INT16_TYPE__ l_whence; /* Where `l_start' is relative to (like `lseek'). */
	__FS_TYPE(off) l_start;  /* Offset where the lock begins. */
	__FS_TYPE(off) l_len;    /* Size of the locked area; zero means until EOF. */
	__pid_t        l_pid;    /* Process holding the lock. */
};
#ifdef __USE_LARGEFILE64
struct flock64 {
	__INT16_TYPE__ l_type;   /* Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK. */
	__INT16_TYPE__ l_whence; /* Where `l_start' is relative to (like `lseek'). */
	__off64_t      l_start;  /* Offset where the lock begins. */
	__off64_t      l_len;    /* Size of the locked area; zero means until EOF. */
	__pid_t        l_pid;    /* Process holding the lock. */
};
#endif /* __USE_LARGEFILE64 */
#endif /* __CC__ */

#define O_ACCMODE     __O_ACCMODE
#define O_RDONLY      __O_RDONLY 
#define O_WRONLY      __O_WRONLY 
#define O_RDWR        __O_RDWR   
#define O_TRUNC       __O_TRUNC


#ifdef __USE_DOS
/* DOS extension flags. */
#ifdef __CRT_DOS_PRIMARY
#define O_RAW           __DOS_O_RAW
#define O_TEXT          __DOS_O_TEXT
#define O_BINARY        __DOS_O_BINARY
#define O_SEQUENTIAL    __DOS_O_SEQUENTIAL
#define O_RANDOM        __DOS_O_RANDOM
#define _O_SHORT_LIVED  __DOS_O_SHORT_LIVED
#define _O_U16TEXT      __DOS_O_U16TEXT
#define _O_U8TEXT       __DOS_O_U8TEXT
#define _O_WTEXT        __DOS_O_WTEXT
#define _O_OBTAIN_DIR   __DOS_O_OBTAIN_DIR
#define O_TEMPORARY     __DOS_O_TEMPORARY
#define _O_TEMPORARY    __DOS_O_TEMPORARY
#else /* __CRT_DOS_PRIMARY */
#define O_RAW           0
#define O_TEXT          0
#define O_BINARY        0
#define O_SEQUENTIAL    0
#define O_RANDOM        0
#define _O_SHORT_LIVED  0
#define _O_U16TEXT      0
#define _O_U8TEXT       0
#define _O_WTEXT        0
#define _O_OBTAIN_DIR   0 /* Not the same as `O_DIRECTORY'! (quite the opposite actually) */
#endif /* !__CRT_DOS_PRIMARY */
#endif /* __USE_DOS */

#define O_CREAT      __O_CREAT    /* If missing, create a new file */
#define O_EXCL       __O_EXCL     /* When used with `O_CREAT', throw an `E_FSERROR_FILE_ALREADY_EXISTS'
                                   * exception if the file already exists. */
#define O_NOCTTY     __O_NOCTTY   /* If the calling process does not have a controlling terminal assigned,
                                   * do not attempt to assign the newly opened file as terminal, even when
                                   * `isatty(open(...))' would be true. */
#define O_APPEND     __O_APPEND   /* Always append data to the end of the file */
#define O_NONBLOCK   __O_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#define O_SYNC       __O_SYNC     /* ??? */
#define O_ASYNC      __O_ASYNC    /* ??? */


#ifdef __USE_KOS
#define O_ANYTHING   __O_ANYTHING
#endif

/* Aliases */
#define O_NDELAY     __O_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#define O_FSYNC      __O_SYNC     /* ??? */

#ifdef __USE_LARGEFILE64
#define O_LARGEFILE   __O_LARGEFILE /* Ignored... */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_XOPEN2K8
#ifdef __O_DIRECTORY
#define O_DIRECTORY  __O_DIRECTORY /* Throw an `E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_OPEN' exception when the final
                                    * path component of an open() system call turns out to be something other than a directory. */
#endif /* __O_DIRECTORY */
#ifdef __O_NOFOLLOW
#define O_NOFOLLOW   __O_NOFOLLOW /* Throw an `E_FSERROR_IS_A_SYMBOLIC_LINK:E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN' exception when the
                                   * final path component of an open() system call turns out to be a symbolic link, unless `O_SYMLINK'
                                   * is given, in which case the link itself is opened. */
#endif /* __O_NOFOLLOW */
#ifdef __O_CLOEXEC
#define O_CLOEXEC    __O_CLOEXEC /* Close the file during exec() */
#endif /* __O_CLOEXEC */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_KOS
#ifdef __O_CLOFORK
#define O_CLOFORK    __O_CLOFORK /* Close the handle when the file descriptors are unshared (s.a. `CLONE_FILES') */
#endif /* __O_CLOFORK */
#ifdef __O_DOSPATH
#define O_DOSPATH    __O_DOSPATH /* Interpret '\\' as '/', and ignore casing during path resolution.
                                  * Additionally, recognize DOS mounting points, and interpret leading
                                  * slashes as relative to the closest DOS mounting point. (s.a.: `AT_DOSPATH') */
#endif /* __O_DOSPATH */
#ifdef __O_SYMLINK
#define O_SYMLINK    __O_SYMLINK /* Open a symlink itself, rather than dereferencing it. (This flag implies `O_NOFOLLOW')
                                  * NOTE: When combined with `O_EXCL', throw an `E_FSERROR_NOT_A_SYMBOLIC_LINK:
                                  *       E_FILESYSTEM_NOT_A_SYMBOLIC_LINK_OPEN' if the file isn't a symbolic link. */
#endif /* __O_SYMLINK */
#endif /* __USE_KOS */

#ifdef __USE_GNU
#define O_DIRECT     __O_DIRECT  /* ??? */
#define O_NOATIME    __O_NOATIME /* Don't update last-accessed time stamps. */
#define O_PATH       __O_PATH    /* Open a path for *at system calls. */
#ifdef __O_TMPFILE
#define O_TMPFILE    __O_TMPFILE
#endif /* __O_TMPFILE */
#endif

#if defined(__USE_POSIX199309) || defined(__USE_UNIX98)
#define O_DSYNC __O_DSYNC /* ??? */
#define O_RSYNC __O_SYNC  /* ??? */
#endif /* __USE_POSIX199309 || __USE_UNIX98 */






#ifndef __CRT_DOS_PRIMARY
#ifndef __USE_FILE_OFFSET64
#define F_GETLK     5 /* Get record locking info. */
#define F_SETLK     6 /* Set record locking info (non-blocking). */
#define F_SETLKW    7 /* Set record locking info (blocking).    */
#else /* __USE_FILE_OFFSET64 */
#define F_GETLK     F_GETLK64  /* Get record locking info. */
#define F_SETLK     F_SETLK64  /* Set record locking info (non-blocking).*/
#define F_SETLKW    F_SETLKW64 /* Set record locking info (blocking). */
#endif /* !__USE_FILE_OFFSET64 */
#ifndef F_GETLK64
#define F_GETLK64   12 /* Get record locking info. */
#define F_SETLK64   13 /* Set record locking info (non-blocking). */
#define F_SETLKW64  14 /* Set record locking info (blocking). */
#endif /* !F_GETLK64 */
#ifdef __USE_GNU
#define F_OFD_GETLK  36
#define F_OFD_SETLK  37
#define F_OFD_SETLKW 38
#endif /* __USE_GNU */

#ifndef F_DUPFD
#define F_DUPFD       0 /* Duplicate file descriptor. */
#endif /* !F_DUPFD */
#ifndef F_GETFD
#define F_GETFD       1 /* Get file descriptor flags. */
#define F_SETFD       2 /* Set file descriptor flags. */
#endif /* !F_GETFD */
#ifndef F_GETFL
#define F_GETFL       3 /* Get file status flags. */
#define F_SETFL       4 /* Set file status flags. */
#endif /* !F_GETFL */

#ifndef __F_SETOWN
#define __F_SETOWN    8 /* Get owner (process receiving SIGIO). */
#define __F_GETOWN    9 /* Set owner (process receiving SIGIO). */
#endif /* !__F_SETOWN */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#ifndef F_SETOWN
#define F_SETOWN      __F_SETOWN /* Get owner (process receiving SIGIO). */
#define F_GETOWN      __F_GETOWN /* Set owner (process receiving SIGIO). */
#endif /* !F_SETOWN */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

#ifndef __F_SETSIG
#define __F_SETSIG    10 /* Set number of signal to be sent. */
#define __F_GETSIG    11 /* Get number of signal to be sent. */
#endif /* !__F_SETSIG */

#ifndef __F_SETOWN_EX
#define __F_SETOWN_EX 15 /* Get owner (thread receiving SIGIO). */
#define __F_GETOWN_EX 16 /* Set owner (thread receiving SIGIO). */
#endif /* !__F_SETOWN_EX */

#ifdef __USE_GNU
#ifndef F_SETSIG
#define F_SETSIG      __F_SETSIG    /* Set number of signal to be sent. */
#define F_GETSIG      __F_GETSIG    /* Get number of signal to be sent. */
#endif /* !F_SETSIG */
#ifndef F_SETOWN_EX
#define F_SETOWN_EX   __F_SETOWN_EX /* Get owner (thread receiving SIGIO). */
#define F_GETOWN_EX   __F_GETOWN_EX /* Set owner (thread receiving SIGIO). */
#endif /* !F_SETOWN_EX */
#endif /* __USE_GNU */

#ifdef __USE_GNU
#ifndef F_SETLEASE
#define F_SETLEASE   1024 /* Set a lease. */
#define F_GETLEASE   1025 /* Enquire what lease is active. */
#endif /* !F_SETLEASE */
#ifndef F_NOTIFY
#define F_NOTIFY     1026 /* Request notifications on a directory. */
#endif /* !F_NOTIFY */
#ifndef F_SETPIPE_SZ
#define F_SETPIPE_SZ 1031 /* Set pipe page size array. */
#define F_GETPIPE_SZ 1032 /* Get pipe page size array. */
#endif /* !F_SETPIPE_SZ */
#endif /* __USE_GNU */

#ifdef __USE_XOPEN2K8
#ifndef F_DUPFD_CLOEXEC
#define F_DUPFD_CLOEXEC 1030 /* Duplicate file descriptor with close-on-exit set. */
#endif /* !F_DUPFD_CLOEXEC */
#endif /* __USE_XOPEN2K8 */

#if defined(__USE_KOS) && defined(__KOS__)
#ifndef F_SETFL_XCH
#define F_SETFL_XCH  5163 /* Same as 'F_SETFL', but return the old set of flags instead of `-EOK' upon success. */
#endif /* !F_SETFL_XCH */
#endif /* __USE_KOS && __KOS__ */

#ifndef FD_CLOEXEC
#define FD_CLOEXEC   0x01 /* FLAG: Close the descriptor on `exec()'. */
#endif /* !FD_CLOEXEC */
#if defined(__USE_KOS) && defined(__KOS__)
#ifndef FD_CLOFORK
#define FD_CLOFORK   0x02 /* FLAG: Close the descriptor during unsharing after `fork()' (Similar to `PROT_LOOSE' for memory). */
#endif /* !FD_CLOFORK */
#endif /* __USE_KOS && __KOS__ */

#ifndef F_RDLCK
#define F_RDLCK 0 /* Read lock. */
#define F_WRLCK 1 /* Write lock. */
#define F_UNLCK 2 /* Remove lock. */
#endif /* !F_RDLCK */

#ifndef F_EXLCK
#define F_EXLCK 4
#define F_SHLCK 8
#endif /* !F_EXLCK */

#ifdef __USE_MISC
#ifndef LOCK_SH
#define LOCK_SH        1 /* Shared lock. */
#define LOCK_EX        2 /* Exclusive lock. */
#define LOCK_NB        4 /* Or'd with one of the above to prevent blocking. */
#define LOCK_UN        8 /* Remove lock. */
#define __LOCK_ATOMIC 16 /* Atomic update.  */
#endif /* !LOCK_SH */
#endif

#ifdef __USE_GNU
#ifndef LOCK_MAND
#define LOCK_MAND  32  /* This is a mandatory flock: */
#define LOCK_READ  64  /* ... which allows concurrent read operations. */
#define LOCK_WRITE 128 /* ... which allows concurrent write operations. */
#define LOCK_RW    192 /* ... Which allows concurrent read & write operations. */
#endif /* !LOCK_MAND */
#endif /* __USE_GNU */

#ifdef __USE_GNU
#ifndef DN_ACCESS
#define DN_ACCESS    0x00000001 /* File accessed. */
#define DN_MODIFY    0x00000002 /* File modified. */
#define DN_CREATE    0x00000004 /* File created. */
#define DN_DELETE    0x00000008 /* File removed. */
#define DN_RENAME    0x00000010 /* File renamed. */
#define DN_ATTRIB    0x00000020 /* File changed attributes. */
#define DN_MULTISHOT 0x80000000 /* Don't remove notifier. */
#endif /* !DN_ACCESS */
#endif /* __USE_GNU */

#ifdef __USE_GNU
/*[[[enum]]]*/
#ifdef __CC__
enum __pid_type {
	F_OWNER_TID  = 0, /* Kernel thread. */
	F_OWNER_PID  = 1, /* Process. */
	F_OWNER_PGRP = 2, /* Process group. */
	F_OWNER_GID  = 2  /* Alternative, obsolete name. */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define F_OWNER_TID  F_OWNER_TID  /* Kernel thread. */
#define F_OWNER_PID  F_OWNER_PID  /* Process. */
#define F_OWNER_PGRP F_OWNER_PGRP /* Process group. */
#define F_OWNER_GID  F_OWNER_GID  /* Alternative, obsolete name. */
#else /* __COMPILER_PREFERR_ENUMS */
#define F_OWNER_TID  0 /* Kernel thread. */
#define F_OWNER_PID  1 /* Process. */
#define F_OWNER_PGRP 2 /* Process group. */
#define F_OWNER_GID  2 /* Alternative, obsolete name. */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("type")
#pragma push_macro("pid")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef type
#undef pid
struct f_owner_ex {
#ifdef __COMPILER_PREFERR_ENUMS
	enum __pid_type type; /* Owner type of ID. */
#else /* __COMPILER_PREFERR_ENUMS */
	int             type; /* Owner type of ID. */
#endif /* !__COMPILER_PREFERR_ENUMS */
	__pid_t         pid;  /* ID of owner. */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("pid")
#pragma pop_macro("type")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */
#endif /* __USE_GNU */

#ifdef __USE_MISC
#ifndef FAPPEND
#define FAPPEND   O_APPEND
#endif /* !FAPPEND */
#ifndef FFSYNC
#define FFSYNC    O_FSYNC
#endif /* !FFSYNC */
#ifndef FASYNC
#define FASYNC    O_ASYNC
#endif /* !FASYNC */
#ifndef FNONBLOCK
#define FNONBLOCK O_NONBLOCK
#endif /* !FNONBLOCK */
#ifndef FNDELAY
#define FNDELAY   O_NDELAY
#endif /* !FNDELAY */
#endif /* __USE_MISC */

#ifndef __POSIX_FADV_DONTNEED
#define __POSIX_FADV_DONTNEED 4
#define __POSIX_FADV_NOREUSE  5
#endif /* !__POSIX_FADV_DONTNEED */

#ifdef __USE_XOPEN2K
#define POSIX_FADV_NORMAL     0 /* No further special treatment. */
#define POSIX_FADV_RANDOM     1 /* Expect random page references. */
#define POSIX_FADV_SEQUENTIAL 2 /* Expect sequential page references. */
#define POSIX_FADV_WILLNEED   3 /* Will need these pages. */
#define POSIX_FADV_DONTNEED   __POSIX_FADV_DONTNEED /* Don't need these pages. */
#define POSIX_FADV_NOREUSE    __POSIX_FADV_NOREUSE  /* Data will be accessed once. */
#endif /* !__USE_XOPEN2K */

#ifdef __USE_GNU
#define SYNC_FILE_RANGE_WAIT_BEFORE 1 /* Wait upon writeout of all pages in the range before performing the write. */
#define SYNC_FILE_RANGE_WRITE       2 /* Initiate writeout of all those dirty pages in the range which are not presently under writeback. */
#define SYNC_FILE_RANGE_WAIT_AFTER  4 /* Wait upon writeout of all pages in the range after performing the write. */

#define SPLICE_F_MOVE               1 /* Move pages instead of copying. */
#define SPLICE_F_NONBLOCK           2 /* Don't block on the pipe splicing (but we may still block on the fd we splice from/to). */
#define SPLICE_F_MORE               4 /* Expect more data. */
#define SPLICE_F_GIFT               8 /* Pages passed in are a gift. */

#define FALLOC_FL_KEEP_SIZE         1 /* Don't extend size of file even if offset + len is greater than file size. */
#define FALLOC_FL_PUNCH_HOLE        2 /* Create a hole in the file. */
#define FALLOC_FL_COLLAPSE_RANGE    8 /* Remove a range of a file without leaving a hole. */
#define FALLOC_FL_ZERO_RANGE       16 /* Convert a range of a file to zeros. */

#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("handle_bytes")
#pragma push_macro("handle_type")
#pragma push_macro("f_handle")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef handle_bytes
#undef handle_type
#undef f_handle
struct file_handle {
	unsigned int  handle_bytes;
	int           handle_type;
	__COMPILER_FLEXIBLE_ARRAY(unsigned char, f_handle); /* File identifier (max is `MAX_HANDLE_SZ'). */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("f_handle")
#pragma pop_macro("handle_type")
#pragma pop_macro("handle_bytes")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

#define MAX_HANDLE_SZ    128
#endif /* __USE_GNU */

#ifdef __USE_ATFILE
#if defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL) || defined(__CRT_GLC)
#define AT_FDCWD           (-100)   /* Special value used to indicate the *at functions should use the current working directory. */
#elif defined(__CRT_CYG)
#define AT_FDCWD           (-2)     /* Special value used to indicate the *at functions should use the current working directory. */
#endif

#define AT_SYMLINK_NOFOLLOW  0x0100 /* If the last path component is a symlink, don't follow it. */
#define AT_REMOVEDIR         0x0200 /* Remove directory instead of unlinking file. */
#define AT_EACCESS           0x0200 /* Test access permitted for effective IDs, not real IDs. */
#define AT_SYMLINK_FOLLOW    0x0400 /* If the last path component is a symlink, follow it. (WARNING: Only used by `linkat(2)') */
#if defined(__USE_GNU) || defined(__USE_KOS_KERNEL)
#define AT_NO_AUTOMOUNT      0x0800 /* Suppress terminal automount traversal. */
#define AT_EMPTY_PATH        0x1000 /* Allow empty relative pathname. */
#endif /* __USE_GNU || __USE_KOS_KERNEL */

#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
#if __KOS_VERSION__ >= 300
#define AT_SYMLINK_REGULAR   0x2000 /* Treat symbolic links similar to like regular files and throw an `ERROR_FS_TOO_MANY_LINKS' error during the first encounter. */
#define AT_CHANGE_CTIME      0x0200 /* For use with `utimensat' and friends: Take `struct timespec[3]', where the 3rd entry
                                     * (when not equal to `UTIME_OMIT') is used to override the file creation timestamp.
                                     * NOTE: Passing this flag when the 3rd timespec isn't set to `UTIME_OMIT' requires
                                     *       that the calling thread be holding the `CAP_SYS_TIME' permission and be the
                                     *       owner of the file in question, or to be holding the `CAP_FOWNER' permission.
                                     *       Less permissions are required when `UTIME_NOW' is passed, in which case
                                     *      `CAP_SYS_TIME' is not required (similarly how having `CAP_FOWNER', or being
                                     *       the owner would allow you to copy the file (updating the timestamp), then
                                     *       replacing the original)
                                     * NOTE: This flag is used to implement full compatibility with NT's SetFileTime function. */
#define AT_READLINK_REQSIZE  0x0200 /* For use with `freadlinkat' and friends.
                                     * Rather than following unix semantics and returning the amount of
                                     * copied bytes with no indication of whether or not everything was
                                     * copied, return the ~required~ buffer size (including a terminating
                                     * NUL-character that normally wouldn't be copied either) to user-space
                                     * (which may be more than the specified buffer size, which should be
                                     * reallocated to fit in successive calls)
                                     * Additionally, as already mentioned, a trailing NUL-character is
                                     * appended to the link text, ensuring that a valid C-style string
                                     * can be read so long as the provided buffer was of sufficient size. */
#define AT_REMOVEREG        0x04000 /* Explicitly allow removing anything that unlink() removes. (Default;
                                     * Set in addition to `AT_REMOVEDIR' to implement `remove()' semantics
                                     * as an atomic kernel operation, removing any race condition that the
                                     * alternative of `if (unlink(x) && errno == EISDIR) rmdir(x)' would
                                     * introduce). */
#if __KOS_VERSION__ >= 400
#define AT_ALTPATH         0x200000 /* For `frealpath4' / `frealpathat': the specified path should
                                     * be printed as the reverse of the `AT_DOSPATH' flag:
                                     *  - 0                      : in:UNIX  out:UNIX
                                     *  - AT_DOSPATH             : in:DOS   out:DOS
                                     *  - AT_ALTPATH             : in:UNIX  out:DOS
                                     *  - AT_ALTPATH | AT_DOSPATH: in:DOS   out:UNIX */
#endif /* __KOS_VERSION__ >= 400 */
#else /* __KOS_VERSION__ >= 300 */
#define AT_REMOVEREG        0x40000 /* ... */
#ifdef __KERNEL__
#define AT_REMOVEMNT        0x80000 /* Used internally by the kernel: Delete a mounting point. (Userspace must use `unmount()') */
#endif /* __KERNEL__ */
#endif /* __KOS_VERSION__ < 300 */
#define AT_DOSPATH         0x100000 /* Interpret '\\' as '/', and ignore casing during path resolution.
                                     * Additionally, recognize `<LETTER>:'-style drive prefixes, as well
                                     * as make use of per-drive working directories, as well as drive-relative
                                     * path names that start with a leading slash.
                                     * Basically, when set: perform the system call in DOS-compatibility mode.
                                     * HINT: This flag can be specified with the `fsmode()' system call. */


/* Same as `AT_FDCWD' but sets the filesystem root
 * (using this, you can `chroot()' with 'dup2()'!) */
#define AT_FDROOT        (-101)

/* Special, symbolic file numbers.
 * These descriptors cannot be overwritten,
 * and their meaning is context-sensible. */
#define AT_THIS_TASK     (-180)
#define AT_THIS_MMAN     AT_THIS_TASK /* DEPRECATED */
#define AT_THIS_STACK    AT_THIS_TASK /* DEPRECATED */

#if __KOS_VERSION__ >= 400
#define AT_THIS_PROCESS     (-181) /* HANDLE_TYPE_TASK (writable, Equivalent of `getpid()') */
#define AT_PARENT_PROCESS   (-182) /* HANDLE_TYPE_TASK (writable, Equivalent of `getppid()') */
#define AT_GROUP_LEADER     (-183) /* HANDLE_TYPE_TASK (writable, Equivalent of `getpgid(0)') */
#define AT_SESSION_LEADER   (-184) /* HANDLE_TYPE_TASK (writable, Equivalent of `getsid(0)') */
#endif /* __KOS_VERSION__ >= 400 */



#if __KOS_VERSION__ >= 300
/* DOS Drive root / current-working paths.
 * These are special file descriptors that can be written to using `dup2()',
 * where they expect to receive either a FILE or PATH descriptor.
 * Once set, these paths describe the root-paths of DOS's drives:
 * >> // Force DOS filesystem semantics for all filesystem operations.
 * >> struct fsmask mask = {0,0};
 * >> mask = fsmode(mask);
 * >> mask.fm_mask &= ~AT_DOSPATH;
 * >> mask.fm_mode |=  AT_DOSPATH;
 * >> fsmode(mask);
 * >>
 * >> // Mount some filesystem locations as DOS drives.
 * >> dup2(open("/"),AT_FDDRIVE_ROOT('C'));
 * >> dup2(open("/bin"),AT_FDDRIVE_ROOT('D'));
 * >> dup2(open("/home"),AT_FDDRIVE_ROOT('E'));
 * >>
 * >> // Open a file on a dos-path.
 * >> open("D:\\ls"); // open("/bin/ls")
 * >>
 * >> // Explicitly set the current-working directory of a specific drive.
 * >> // NOTE: Requires that the opened path be reachable from `AT_FDDRIVE_ROOT('E')'
 * >> //       If it isn't, an `ERROR_FS_CROSSDEVICE_LINK' error is thrown.
 * >> dup2(open("/home/me/Downloads"),AT_FDDRIVE_CWD('E'));
 * >>
 * >> chdir("C:\\bin"); // AT_FDCWD = "/bin"; AT_FDDRIVE_CWD('C') = AT_FDCWD;
 * >> chdir("E:");      // AT_FDCWD = AT_FDDRIVE_CWD('E'); (`/home/me/Downloads')
 * >> chdir("E:\\");    // AT_FDCWD = "/home"; AT_FDDRIVE_CWD('E') = AT_FDCWD;
 * >> chdir("C:");      // AT_FDCWD = AT_FDDRIVE_CWD('C'); (`/bin')
 * >> chdir("D:\\");    // AT_FDCWD = "/bin"; AT_FDDRIVE_CWD('D') = AT_FDCWD;
 * >> chdir("..");      // AT_FDCWD = "/bin"; AT_FDDRIVE_CWD('D') = AT_FDCWD; (Don't escape the current drive)
 * >>
 * NOTES:
 *   - Setting the root-path of a drive will not update the drive working directories of processes sharing VFS.
 *     With that in mind, you should not re-mount a DOS drive as a sub-directory of where
 *     it was located before then, unless you first unshared your VFS (using `CLONE_NEWNS').
 *     Allowing a program's current working directory to be located outside the associated
 *     drive causes weak undefined behavior. In KOS this means:
 *       - `xfdname()' will not produce the correct path
 *       - Relative path names still operate on the old directory
 *       - Navigating into parent directories is no longer restricted (except by `chroot()')
 *       - Manually navigating into a portion of the new drives mounting point fixes the problem.
 *   - DOS drive mounting points are beneath UNIX mounting points, in that they don't
 *     actually mount a superblock to some filesystem location, but rather mirror a
 *     filesystem path, meaning that DOS drives can be thought of as the equivalent
 *     of the `dfd' argument of `*at' system calls:
 *     >> open("C:\\foo.txt"); // Same as `openat(AT_FDDRIVE_ROOT('C'),"foo.txt")'
 *     If `mount()' is used to create a new (real) mounting point, it will appear
 *     in all DOS drives that are mounting the location where the mount happened,
 *     or any location further up the tree immediately (it's the same data object
 *     internally; DOS drives are merely aliasing regular paths; aka. `O_PATH')
 *   - To ~unmount~ (quote-unquote) a DOS drive, simply close() the associated root file descriptor:
 *     >> // Unmount `C:' (also closes the associated FDCWD descriptor)
 *     >> close(AT_FDDRIVE_ROOT('C'));
 *   - Mounting, or unmounting dos drives requires the same privileges as the `mount()' and `umount()' system calls.
 *   - Closing an `AT_FDDRIVE_CWD()' descriptor will revert it to match the root path of the associated drive.
 *     >> close(AT_FDDRIVE_CWD('C'));
 *     >> // Same as:
 *     >> dup2(AT_FDDRIVE_ROOT('C'),AT_FDDRIVE_CWD('C'));
 *   - Symbolic links are evaluated the same as any user-provided path.
 *     If a symbolic link starts with a '/' or '\\' character, the remainder
 *     of its text is relative to the first DOS drive mounting point
 *     encountered while walking up the chain of parent directories. */
#define AT_FDDRIVE_CWD(drivechar)  ((-350)+((drivechar)-'A'))
#define AT_FDDRIVE_ROOT(drivechar) ((-300)+((drivechar)-'A'))
#define AT_DOS_DRIVEMIN            'A'
#define AT_DOS_DRIVEMAX            'Z'
#endif /* __KOS_VERSION__ >= 300 */
#endif /* __USE_KOS */
#endif /* __USE_ATFILE */

#endif /* !__CRT_DOS_PRIMARY */





#ifdef __USE_DOS
/* DOS name aliases */
#define _O_RDONLY       O_RDONLY
#define _O_WRONLY       O_WRONLY
#define _O_RDWR         O_RDWR
#define _O_APPEND       O_APPEND
#define _O_BINARY       O_BINARY
#define _O_CREAT        O_CREAT
#define _O_EXCL         O_EXCL
#define _O_RANDOM       O_RANDOM
#define _O_RAW          O_RAW
#define _O_SEQUENTIAL   O_SEQUENTIAL
#define _O_TEXT         O_TEXT
#define _O_TRUNC        O_TRUNC
#define O_NOINHERIT     __O_CLOEXEC
#define _O_NOINHERIT    __O_CLOEXEC
#ifndef _O_TEMPORARY
/* XXX: Figure out exactly what `O_TEMPORARY' does,
 *      and check if it matches linux's `O_TMPFILE' */
//#define _O_TEMPORARY    __O_TMPFILE
//#define O_TEMPORARY     __O_TMPFILE
#endif /* !_O_TEMPORARY */
#endif /* __USE_DOS */



__SYSDECL_END

#endif /* !_BITS_FCNTL_H */
