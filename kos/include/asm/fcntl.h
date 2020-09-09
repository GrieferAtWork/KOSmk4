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
#ifndef _ASM_FCNTL_H
#define _ASM_FCNTL_H 1

#include <__stdinc.h>
#include <__crt.h>

#if defined(__KOS__) || defined(__linux__)
/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

#define __F_DUPFD         0    /* [void arg] Duplicate and return file descriptor. (may be used to implement `dup(2)') */
#define __F_GETFD         1    /* [void arg] Get file descriptor flags.
                                * @return: * : Set of `FD_CLOEXEC | FD_CLOFORK' */
#define __F_SETFD         2    /* [int arg = <set of `FD_CLOEXEC', `FD_CLOFORK'>] Set file descriptor flags. */
#define __F_GETFL         3    /* [void arg] Get file status flags.
                                * @return: * : Set of `O_*' */
#define __F_SETFL         4    /* [oflag_t arg] Set file status flags. */
#define __F_GETLK         5    /* [struct flock *arg] Get record locking info. */
#define __F_SETLK         6    /* [struct flock const *arg] Set record locking info (non-blocking). */
#define __F_SETLKW        7    /* [struct flock const *arg] Set record locking info (blocking). */
#define __F_SETOWN        8    /* [pid_t arg] Set owner (process receiving SIGIO). */
#define __F_GETOWN        9    /* [void arg] Get owner (process receiving SIGIO).
                                * @return: * : The PID of the process (warning: the PID may not
                                *              fit into an int and -EOVERFLOW may be returned) */
#define __F_SETSIG        10   /* [int signo] Set number of signal to be sent. */
#define __F_GETSIG        11   /* [void arg] Get number of signal to be sent.
                                * @return: * : One of `SIG*' */
#define __F_GETLK64       12   /* [struct flock64 *arg] Get record locking info. */
#define __F_SETLK64       13   /* [struct flock64 const *arg] Set record locking info (non-blocking). */
#define __F_SETLKW64      14   /* [struct flock64 const *arg] Set record locking info (blocking). */
#define __F_SETOWN_EX     15   /* [struct f_owner_ex const *arg] Set owner (thread receiving SIGIO). */
#define __F_GETOWN_EX     16   /* [struct f_owner_ex *arg] Get owner (thread receiving SIGIO). */
#define __F_OFD_GETLK     36   /* [struct flock *arg] */
#define __F_OFD_SETLK     37   /* [struct flock const *arg] */
#define __F_OFD_SETLKW    38   /* [struct flock const *arg] */
#define __F_SETLEASE      1024 /* [int arg = <One of `F_RDLCK', `F_WRLCK', `F_UNLCK'>] Set a lease. */
#define __F_GETLEASE      1025 /* [void arg] Enquire what lease is active.
                                * @return: * : One of `F_RDLCK', `F_WRLCK', `F_UNLCK' */
#define __F_NOTIFY        1026 /* [int arg = <Set of `DN_*'>] Request notifications on a directory. */
#define __F_DUPFD_CLOEXEC 1030 /* [void arg] Duplicate file descriptor with close-on-exit set.
                                * @[fd_t return]: * : A new FD for the same kernel object. */
#define __F_SETPIPE_SZ    1031 /* [unsigned int arg] Set pipe buffer size (in bytes). */
#define __F_GETPIPE_SZ    1032 /* [void arg] Get pipe buffer size (in bytes).
                                * @return: * : The buffer size (in bytes) */
#ifdef __KOS__
#define __F_SETFL_XCH      5163 /* [int flags] Same as 'F_SETFL', but return the old set of flags instead of `-EOK' upon success. */
#define __F_NEXT           5164 /* [void arg] Return the next open handle id >= the given fd, or `-EBADF' if no such FD exists. (s.a. `https://lkml.org/lkml/2012/4/1/71') */
#define __F_CLOSEM         5165 /* [void arg] close all handles >= to the one given (s.a. `https://www.unix.com/man-page/FreeBSD/2/closefrom/') */
#define __F_MAXFD          5166 /* [void arg] return the max open handle id (the given fd is ignored) */
#define __F_DUP2FD         5167 /* [fd_t arg] Same as `dup2()' (the target FD is given as `(fd_t)arg') */
#define __F_DUP2FD_CLOEXEC 5168 /* [fd_t arg] Same as `F_DUP2FD', but set `FD_CLOEXEC'. */
#endif /* __KOS__ */


/* *at function flags (s.a. `atflag_t') */
#define __AT_SYMLINK_NOFOLLOW  0x0100 /* If the last path component is a symlink, don't follow it. */
#define __AT_REMOVEDIR         0x0200 /* Remove directory instead of unlinking file. */
#define __AT_EACCESS           0x0200 /* Test access permitted for effective IDs, not real IDs. */
#define __AT_SYMLINK_FOLLOW    0x0400 /* If the last path component is a symlink, follow it. (WARNING: Only used by `linkat(2)') */
#define __AT_NO_AUTOMOUNT      0x0800 /* Suppress terminal automount traversal. */
#define __AT_EMPTY_PATH        0x1000 /* Allow empty relative pathname. */
#ifdef __KOS__
#if __KOS_VERSION__ >= 300
#define __AT_SYMLINK_REGULAR   0x2000 /* Treat symbolic links similar to like regular files and throw an `ERROR_FS_TOO_MANY_LINKS' error during the first encounter. */
#define __AT_CHANGE_CTIME      0x0200 /* For use with `utimensat' and friends: Take `struct timespec[3]', where the 3rd entry
                                       * (when not equal to `UTIME_OMIT') is used to override the file creation timestamp.
                                       * NOTE: Passing this flag when the 3rd timespec isn't set to `UTIME_OMIT' requires
                                       *       that the calling thread be holding the `CAP_SYS_TIME' permission and be the
                                       *       owner of the file in question, or to be holding the `CAP_FOWNER' permission.
                                       *       Less permissions are required when `UTIME_NOW' is passed, in which case
                                       *      `CAP_SYS_TIME' is not required (similarly how having `CAP_FOWNER', or being
                                       *       the owner would allow you to copy the file (updating the timestamp), then
                                       *       replacing the original)
                                       * NOTE: This flag is used to implement full compatibility with NT's SetFileTime function. */
#define __AT_READLINK_REQSIZE  0x0200 /* For use with `freadlinkat' and friends.
                                       * Rather than following unix semantics and returning the amount of
                                       * copied bytes with no indication of whether or not everything was
                                       * copied, return the ~required~ buffer size (including a terminating
                                       * NUL-character that normally wouldn't be copied either) to user-space
                                       * (which may be more than the specified buffer size, which should be
                                       * reallocated to fit in successive calls)
                                       * Additionally, as already mentioned, a trailing NUL-character is
                                       * appended to the link text, ensuring that a valid C-style string
                                       * can be read so long as the provided buffer was of sufficient size. */
#define __AT_REMOVEREG        0x04000 /* Explicitly allow removing anything that unlink() removes. (Default;
                                       * Set in addition to `AT_REMOVEDIR' to implement `remove()' semantics
                                       * as an atomic kernel operation, removing any race condition that the
                                       * alternative of `if (unlink(x) && errno == EISDIR) rmdir(x)' would
                                       * introduce). */
#if __KOS_VERSION__ >= 400
#define __AT_ALTPATH         0x200000 /* For `frealpath4' / `frealpathat': the specified path should
                                       * be printed as the reverse of the `AT_DOSPATH' flag:
                                       *  - 0                      : in:UNIX  out:UNIX
                                       *  - AT_DOSPATH             : in:DOS   out:DOS
                                       *  - AT_ALTPATH             : in:UNIX  out:DOS
                                       *  - AT_ALTPATH | AT_DOSPATH: in:DOS   out:UNIX */
#endif /* __KOS_VERSION__ >= 400 */
#else /* __KOS_VERSION__ >= 300 */
#define __AT_REMOVEREG        0x40000 /* ... */
#ifdef __USE_KOS_KERNEL
#define __AT_REMOVEMNT        0x80000 /* Used internally by the kernel: Delete a mounting point. (Userspace must use `unmount()') */
#endif /* __USE_KOS_KERNEL */
#endif /* __KOS_VERSION__ < 300 */
#define __AT_DOSPATH         0x100000 /* Interpret '\\' as '/', and ignore casing during path resolution.
                                       * Additionally, recognize `<LETTER>:'-style drive prefixes, as well
                                       * as make use of per-drive working directories, as well as drive-relative
                                       * path names that start with a leading slash.
                                       * Basically, when set: perform the system call in DOS-compatibility mode.
                                       * HINT: This flag can be specified with the `fsmode()' system call. */
#endif /* __KOS__ */


/* Special values that may be used for the `dfd' argument of `*at' functions. */
#define __AT_FDCWD  (-100) /* The current working directory. */
#ifdef __KOS__
#define __AT_FDROOT (-101) /* Same as `__AT_FDCWD' but sets the filesystem root
                            * (using this, you can `chroot()' with 'dup2()'!) */
/* Special, symbolic file numbers.
 * These descriptors cannot be overwritten,
 * and their meaning is context-sensible. */
#define __AT_THIS_TASK     (-180)
#define __AT_THIS_MMAN     __AT_THIS_TASK /* DEPRECATED */
#define __AT_THIS_STACK    __AT_THIS_TASK /* DEPRECATED */
#if __KOS_VERSION__ >= 400
#define __AT_THIS_PROCESS     (-181) /* HANDLE_TYPE_TASK (writable, Equivalent of `getpid()') */
#define __AT_PARENT_PROCESS   (-182) /* HANDLE_TYPE_TASK (writable, Equivalent of `getppid()') */
#define __AT_GROUP_LEADER     (-183) /* HANDLE_TYPE_TASK (writable, Equivalent of `getpgid(0)') */
#define __AT_SESSION_LEADER   (-184) /* HANDLE_TYPE_TASK (writable, Equivalent of `getsid(0)') */
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
 * >> dup2(open("/"), AT_FDDRIVE_ROOT('C'));
 * >> dup2(open("/bin"), AT_FDDRIVE_ROOT('D'));
 * >> dup2(open("/home"), AT_FDDRIVE_ROOT('E'));
 * >>
 * >> // Open a file on a dos-path.
 * >> open("D:\\ls"); // open("/bin/ls")
 * >>
 * >> // Explicitly set the current-working directory of a specific drive.
 * >> // NOTE: Requires that the opened path be reachable from `AT_FDDRIVE_ROOT('E')'
 * >> //       If it isn't, an `ERROR_FS_CROSSDEVICE_LINK' error is thrown.
 * >> dup2(open("/home/me/Downloads"), AT_FDDRIVE_CWD('E'));
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
 *     >> open("C:\\foo.txt"); // Same as `openat(AT_FDDRIVE_ROOT('C'), "foo.txt")'
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
#define __AT_FDDRIVE_CWD(drivechar)  ((-350) + ((drivechar) - 'A'))
#define __AT_FDDRIVE_ROOT(drivechar) ((-300) + ((drivechar) - 'A'))
#define __AT_DOS_DRIVEMIN            'A'
#define __AT_DOS_DRIVEMAX            'Z'
#endif /* __KOS_VERSION__ >= 300 */
#endif /* __KOS__ */


/* File descriptor flags (s.a. `F_GETFD' and `F_SETFL') */
#define __FD_CLOEXEC 0x01 /* FLAG: Close the descriptor on `exec()'. */
#ifdef __KOS__
#define __FD_CLOFORK 0x02 /* FLAG: Close the descriptor during unsharing after `fork()' (Similar to `PROT_LOOSE' for memory). */
#endif /* __KOS__ */

#define __F_RDLCK 0 /* Read lock. */
#define __F_WRLCK 1 /* Write lock. */
#define __F_UNLCK 2 /* Remove lock. */
#define __F_EXLCK 4 /* TODO: DOC */
#define __F_SHLCK 8 /* TODO: DOC */


#define __LOCK_SH     1   /* Shared lock. */
#define __LOCK_EX     2   /* Exclusive lock. */
#define __LOCK_NB     4   /* Or'd with one of the above to prevent blocking. */
#define __LOCK_UN     8   /* Remove lock. */
#define __LOCK_ATOMIC 16  /* Atomic update.  */
#define __LOCK_MAND   32  /* This is a mandatory flock: */
#define __LOCK_READ   64  /* ... which allows concurrent read operations. */
#define __LOCK_WRITE  128 /* ... which allows concurrent write operations. */
#define __LOCK_RW     192 /* ... Which allows concurrent read & write operations. */


#define __DN_ACCESS    0x00000001 /* File accessed. */
#define __DN_MODIFY    0x00000002 /* File modified. */
#define __DN_CREATE    0x00000004 /* File created. */
#define __DN_DELETE    0x00000008 /* File removed. */
#define __DN_RENAME    0x00000010 /* File renamed. */
#define __DN_ATTRIB    0x00000020 /* File changed attributes. */
#define __DN_MULTISHOT 0x80000000 /* Don't remove notifier. */


#define __F_OWNER_TID  0 /* Kernel thread. */
#define __F_OWNER_PID  1 /* Process. */
#define __F_OWNER_PGRP 2 /* Process group. */
#define __F_OWNER_GID  2 /* Alternative, obsolete name. */


#define __POSIX_FADV_NORMAL     0 /* No further special treatment. */
#define __POSIX_FADV_RANDOM     1 /* Expect random page references. */
#define __POSIX_FADV_SEQUENTIAL 2 /* Expect sequential page references. */
#define __POSIX_FADV_WILLNEED   3 /* Will need these pages. */
#define __POSIX_FADV_DONTNEED   4 /* Don't need these pages. */
#define __POSIX_FADV_NOREUSE    5 /* Data will be accessed once. */


#define __SYNC_FILE_RANGE_WAIT_BEFORE 1 /* Wait upon writeout of all pages in the range before performing the write. */
#define __SYNC_FILE_RANGE_WRITE       2 /* Initiate writeout of all those dirty pages in the range which are not presently under writeback. */
#define __SYNC_FILE_RANGE_WAIT_AFTER  4 /* Wait upon writeout of all pages in the range after performing the write. */


#define __SPLICE_F_MOVE               1 /* Move pages instead of copying. */
#define __SPLICE_F_NONBLOCK           2 /* Don't block on the pipe splicing (but we may still block on the fd we splice from/to). */
#define __SPLICE_F_MORE               4 /* Expect more data. */
#define __SPLICE_F_GIFT               8 /* Pages passed in are a gift. */


#define __FALLOC_FL_KEEP_SIZE         1 /* Don't extend size of file even if offset + len is greater than file size. */
#define __FALLOC_FL_PUNCH_HOLE        2 /* Create a hole in the file. */
#define __FALLOC_FL_COLLAPSE_RANGE    8 /* Remove a range of a file without leaving a hole. */
#define __FALLOC_FL_ZERO_RANGE       16 /* Convert a range of a file to zeros. */

#define __MAX_HANDLE_SZ 128

#elif defined(__CRT_DOS_PRIMARY)
/************************************************************************/
/* DOS/MSVCRT                                                           */
/************************************************************************/

#elif defined(__CRT_CYG_PRIMARY)
/************************************************************************/
/* CYGWIN                                                               */
/************************************************************************/

#define __AT_FDCWD        (-2)
#define __FD_CLOEXEC      1
#define __F_DUPFD         0
#define __F_GETFD         1
#define __F_SETFD         2
#define __F_GETFL         3
#define __F_SETFL         4
#define __F_GETOWN        5
#define __F_SETOWN        6
#define __F_GETLK         7
#define __F_SETLK         8
#define __F_SETLKW        9
#define __F_RGETLK        10
#define __F_RSETLK        11
#define __F_CNVT          12
#define __F_RSETLKW       13
#define __F_DUPFD_CLOEXEC 14

#define __F_RDLCK   1
#define __F_WRLCK   2
#define __F_UNLCK   3
#define __F_UNLKSYS 4

#define __AT_EACCESS          1
#define __AT_SYMLINK_NOFOLLOW 2
#define __AT_SYMLINK_FOLLOW   4
#define __AT_REMOVEDIR        8
#define __AT_EMPTY_PATH       16

#define __LOCK_SH 0x01
#define __LOCK_EX 0x02
#define __LOCK_NB 0x04
#define __LOCK_UN 0x08

#ifdef __CC__
#include <features.h>
#if defined(__USE_NEWLIB) && defined(__USE_MISC)
#include <hybrid/typecore.h>
__DECL_BEGIN
struct eflock {
	__INT16_TYPE__   l_type;
	__INT16_TYPE__   l_whence;
	__LONGPTR_TYPE__ l_start;
	__LONGPTR_TYPE__ l_len;
	__INT16_TYPE__   l_pid;
	__INT16_TYPE__   l_xxx;
	__LONGPTR_TYPE__ l_rpid;
	__LONGPTR_TYPE__ l_rsys;
};
__DECL_END
#endif /* __USE_NEWLIB && __USE_MISC */
#endif /* __CC__ */

#elif defined(__NetBSD__)
/************************************************************************/
/* NetBSD                                                               */
/************************************************************************/

#define __F_DUPFD               0
#define __F_GETFD               1
#define __F_SETFD               2
#define __F_GETFL               3
#define __F_SETFL               4
#define __F_GETOWN              5
#define __F_SETOWN              6
#define __F_GETLK               7
#define __F_SETLK               8
#define __F_SETLKW              9
#define __F_CLOSEM              10
#define __F_MAXFD               11
#define __F_DUPFD_CLOEXEC       12
#define __F_GETNOSIGPIPE        13
#define __F_SETNOSIGPIPE        14
#define __F_GETPATH             15
#define __FD_CLOEXEC            1
#define __F_RDLCK               1
#define __F_UNLCK               2
#define __F_WRLCK               3
#define __LOCK_SH               0x01
#define __LOCK_EX               0x02
#define __LOCK_NB               0x04
#define __LOCK_UN               0x08
#define __POSIX_FADV_NORMAL     0
#define __POSIX_FADV_RANDOM     1
#define __POSIX_FADV_SEQUENTIAL 2
#define __POSIX_FADV_WILLNEED   3
#define __POSIX_FADV_DONTNEED   4
#define __POSIX_FADV_NOREUSE    5
#define __AT_FDCWD              (-100)
#define __AT_EACCESS            0x100
#define __AT_SYMLINK_NOFOLLOW   0x200
#define __AT_SYMLINK_FOLLOW     0x400
#define __AT_REMOVEDIR          0x800

#elif defined(__solaris__)
/************************************************************************/
/* SOLARIS                                                              */
/************************************************************************/
#define __F_DUPFD               0
#define __F_GETFD               1
#define __F_SETFD               2
#define __F_GETFL               3
#define __F_SETFL               4
#define __F_SETLK               6
#define __F_SETLKW              7
#define __F_CHKFL               8
#define __F_DUP2FD              9
#define __F_ALLOCSP             10
#define __F_FREESP              11
#define __F_ISSTREAM            13
#define __F_GETLK               14
#define __F_PRIV                15
#define __F_NPRIV               16
#define __F_QUOTACTL            17
#define __F_BLOCKS              18
#define __F_BLKSIZE             19
#define __F_GETOWN              23
#define __F_SETOWN              24
#define __F_REVOKE              25
#define __F_HASREMOTELOCKS      26
#define __F_SHARE               40
#define __F_UNSHARE             41
#define __F_SETLK_NBMAND        42
#define __F_SHARE_NBMAND        43
#define __F_GETXFL              45
#define __F_BADFD               46
#define __F_RDLCK               1
#define __F_WRLCK               2
#define __F_UNLCK               3
#define __F_UNLKSYS             4
#define __O_ACCMODE             3
#define __FD_CLOEXEC            1
#define __DIRECTIO_OFF          (0)
#define __DIRECTIO_ON           (1)
#define __F_RDACC               0x1
#define __F_WRACC               0x2
#define __F_RWACC               0x3
#define __F_RMACC               0x4
#define __F_MDACC               0x20
#define __F_NODNY               0x0
#define __F_RDDNY               0x1
#define __F_WRDNY               0x2
#define __F_RWDNY               0x3
#define __F_RMDNY               0x4
#define __F_COMPAT              0x8
#define __F_MANDDNY             0x10
#define __AT_FDCWD              0xffd19553
#define __AT_SYMLINK_NOFOLLOW   0x1000
#define __AT_REMOVEDIR          0x1
#define __AT_TRIGGER            0x2
#define __POSIX_FADV_NORMAL     0
#define __POSIX_FADV_RANDOM     1
#define __POSIX_FADV_SEQUENTIAL 2
#define __POSIX_FADV_WILLNEED   3
#define __POSIX_FADV_DONTNEED   4
#define __POSIX_FADV_NOREUSE    5
#ifdef __CC__
#include <features.h>

#ifdef __USE_SOLARIS
#include <hybrid/typecore.h>
__DECL_BEGIN

typedef struct fshare {
	__INT16_TYPE__ f_access;
	__INT16_TYPE__ f_deny;
	__INT32_TYPE__ f_id;
} fshare_t;

__DECL_END
#endif /* __USE_SOLARIS */
#endif /* __CC__ */


#else /* ... */
/************************************************************************/
/* GENERIC                                                              */
/************************************************************************/

#endif /* !... */


#ifndef __R_OK
#define __R_OK 4 /* Test for read permission. */
#define __W_OK 2 /* Test for write permission. */
#define __X_OK 1 /* Test for execute permission. */
#define __F_OK 0 /* Test for existence. */
#endif /* !__R_OK */

#ifndef __F_ULOCK
#define __F_ULOCK 0 /* Unlock a previously locked region. */
#define __F_LOCK  1 /* Lock a region for exclusive use. */
#define __F_TLOCK 2 /* Test and lock a region for exclusive use. */
#define __F_TEST  3 /* Test a region for other processes locks. */
#endif /* !__F_ULOCK */


/* Deal with fcntl redirection on platforms with 64-bit-by-default filesystems. */
#if (defined(__F_FREESP64) || defined(__F_ALLOCSP64) || \
     defined(__F_GETLK64) || defined(__F_SETLK64) ||    \
     defined(__F_SETLKW64) || defined(__F_SETLK64_NBMAND))
#include <bits/typesizes.h>
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
#ifdef __F_FREESP64
#undef __F_FREESP64
#ifdef __F_FREESP
#define __F_FREESP64 __F_FREESP
#endif /* __F_FREESP */
#endif /* __F_FREESP64 */

#ifdef __F_ALLOCSP64
#undef __F_ALLOCSP64
#ifdef __F_ALLOCSP
#define __F_ALLOCSP64 __F_ALLOCSP
#endif /* __F_ALLOCSP */
#endif /* __F_ALLOCSP64 */

#ifdef __F_GETLK64
#undef __F_GETLK64
#ifdef __F_GETLK
#define __F_GETLK64 __F_GETLK
#endif /* __F_GETLK */
#endif /* __F_GETLK64 */

#ifdef __F_SETLK64
#undef __F_SETLK64
#ifdef __F_SETLK
#define __F_SETLK64 __F_SETLK
#endif /* __F_SETLK */
#endif /* __F_SETLK64 */

#ifdef __F_SETLKW64
#undef __F_SETLKW64
#ifdef __F_SETLKW
#define __F_SETLKW64 __F_SETLKW
#endif /* __F_SETLKW */
#endif /* __F_SETLKW64 */

#ifdef __F_SETLK64_NBMAND
#undef __F_SETLK64_NBMAND
#ifdef __F_SETLK_NBMAND
#define __F_SETLK64_NBMAND __F_SETLK_NBMAND
#endif /* __F_SETLK_NBMAND */
#endif /* __F_SETLK64_NBMAND */
#endif /* __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */
#endif /* ... */


#endif /* !_ASM_FCNTL_H */
