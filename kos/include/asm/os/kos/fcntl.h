/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_OS_KOS_FCNTL_H
#define _ASM_OS_KOS_FCNTL_H 1

#include <__stdinc.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

#define __F_DUPFD             0    /* [fd_t minfd] Same as `dup(2)', but returned FD is guarantied `>= minfd' */
#define __F_GETFD             1    /* [void arg] Get file descriptor flags.
                                    * @return: * : Set of `FD_CLOEXEC | FD_CLOFORK' */
#define __F_SETFD             2    /* [int arg = <set of `FD_CLOEXEC', `FD_CLOFORK'>] Set file descriptor flags. */
#define __F_GETFL             3    /* [void arg] Get file status flags (set of `O_APPEND | O_NONBLOCK | O_DSYNC | O_ASYNC | O_DIRECT') */
#define __F_SETFL             4    /* [oflag_t arg] Set file status flags. */
#define __F_GETLK             5    /* [struct flock *arg] Get record locking info. */
#define __F_SETLK             6    /* [struct flock const *arg] Set record locking info (non-blocking). */
#define __F_SETLKW            7    /* [struct flock const *arg] Set record locking info (blocking). */
#define __F_SETOWN            8    /* [pid_t arg] Set owner (process receiving SIGIO). */
#define __F_GETOWN            9    /* [void arg] Get owner (process receiving SIGIO).
                                    * @return: * : The PID of the process (warning: the PID may not
                                    *              fit into an int and -EOVERFLOW may be  returned) */
#define __F_SETSIG            10   /* [int signo] Set number of signal to be sent. */
#define __F_GETSIG            11   /* [void arg] Get number of signal to be sent.
                                    * @return: * : One of `SIG*' */
#define __F_GETLK64           12   /* [struct flock64 *arg] Get record locking info. */
#define __F_SETLK64           13   /* [struct flock64 const *arg] Set record locking info (non-blocking). */
#define __F_SETLKW64          14   /* [struct flock64 const *arg] Set record locking info (blocking). */
#define __F_SETOWN_EX         15   /* [struct f_owner_ex const *arg] Set owner (thread receiving SIGIO). */
#define __F_GETOWN_EX         16   /* [struct f_owner_ex *arg] Get owner (thread receiving SIGIO). */
#define __F_OFD_GETLK         36   /* [struct flock *arg] */
#define __F_OFD_SETLK         37   /* [struct flock const *arg] */
#define __F_OFD_SETLKW        38   /* [struct flock const *arg] */
#define __F_LINUX_SPECIFIC_BASE 1024
#define __F_SETLEASE          1024 /* [int arg = <One of `F_RDLCK', `F_WRLCK', `F_UNLCK'>] Set a lease. */
#define __F_GETLEASE          1025 /* [void arg] Enquire what lease is active.
                                    * @return: * : One of `F_RDLCK', `F_WRLCK', `F_UNLCK' */
#define __F_NOTIFY            1026 /* [int arg = <Set of `DN_*'>] Request notifications on a directory. */
/*      __F_                  1027  * ... */
/*      __F_                  1028  * ... */
/*      __F_                  1029  * ... */
#define __F_DUPFD_CLOEXEC     1030 /* [fd_t minfd] Same as `F_DUPFD', but also set `FD_CLOEXEC' bit. */
#define __F_SETPIPE_SZ        1031 /* [unsigned int arg] Set pipe buffer size (in bytes). */
#define __F_GETPIPE_SZ        1032 /* [void arg] Get pipe buffer size (in bytes).
                                    * @return: * : The buffer size (in bytes) */
#define __F_ADD_SEALS         1033 /* [unsigned int seals] Set file seals (`seals' is a set of `F_SEAL_*') */
#define __F_GET_SEALS         1034 /* [void arg] Get active file seals.
                                    * @return: * : Active seals (set of `F_SEAL_*') */
#define __F_GET_RW_HINT       1035 /* [uint64_t *arg] ??? */
#define __F_SET_RW_HINT       1036 /* [uint64_t const *arg] ??? */
#define __F_GET_FILE_RW_HINT  1037 /* [uint64_t *arg] ??? */
#define __F_SET_FILE_RW_HINT  1038 /* [uint64_t const *arg] ??? */


#ifdef __KOS__
#define __F_SETFL_XCH      5163 /* [int flags] Same as 'F_SETFL', but return the old set of flags instead of `-EOK' upon success. */
#define __F_NEXT           5164 /* [void arg] Return the next open handle id >= the given fd, or `-EBADF' if no such FD exists. (s.a. `https://lkml.org/lkml/2012/4/1/71') */
#define __F_CLOSEM         5165 /* [void arg] close all handles >= to the one given (s.a. `https://www.unix.com/man-page/FreeBSD/2/closefrom/') */
#define __F_MAXFD          5166 /* [void arg] return the max open handle id (the given fd is ignored) */
#define __F_DUP2FD         5167 /* [fd_t arg] Same as `dup2()' (the target FD is given as `(fd_t)arg') */
#define __F_DUP2FD_CLOEXEC 5168 /* [fd_t arg] Same as `F_DUP2FD', but set `FD_CLOEXEC'. */
#endif /* __KOS__ */

/* For use with `F_ADD_SEALS' and `F_GET_SEALS' */
#define __F_SEAL_SEAL         0x0001 /* Prevent further modification of seals */
#define __F_SEAL_SHRINK       0x0002 /* Prevent the file's size from being truncated */
#define __F_SEAL_GROW         0x0004 /* Prevent the file's size from being increased */
#define __F_SEAL_WRITE        0x0008 /* Prevent any modifications to the file's contents.
                                      * If  writable memory mappings exist, trying to set
                                      * this flag fails with TODO:EXCEPTION_FOR_EBUSY */
#define __F_SEAL_FUTURE_WRITE 0x0010 /* Same as `F_SEAL_WRITE', but pre-existing, writable
                                      * memory mappings continue to work. */

/* For use with `F_GET_RW_HINT' and `F_SET_RW_HINT' */
#define __RWF_WRITE_LIFE_NOT_SET 0 /* ??? */
#define __RWH_WRITE_LIFE_NONE    1 /* ??? */
#define __RWH_WRITE_LIFE_SHORT   2 /* ??? */
#define __RWH_WRITE_LIFE_MEDIUM  3 /* ??? */
#define __RWH_WRITE_LIFE_LONG    4 /* ??? */
#define __RWH_WRITE_LIFE_EXTREME 5 /* ??? */

/* *at function flags (s.a. `atflag_t') */
#define __AT_SYMLINK_NOFOLLOW  0x0100 /* If the last path component is a symlink, don't follow it. */
#define __AT_REMOVEDIR         0x0200 /* Remove directory instead of unlinking file. */
#define __AT_EACCESS           0x0200 /* Test access permitted for effective IDs, not real IDs. */
#define __AT_SYMLINK_FOLLOW    0x0400 /* If the last path component is a symlink, follow it. (WARNING: Only used by `linkat(2)') */
#define __AT_NO_AUTOMOUNT      0x0800 /* Suppress terminal automount traversal. */
#define __AT_EMPTY_PATH        0x1000 /* Allow empty relative pathname. */
#ifdef __KOS__
#if __KOS_VERSION__ >= 300
#define __AT_CHANGE_BTIME      0x0200 /* For use with `utimensat' and friends: Take `struct timespec[3]', where the 3rd entry
                                       * (when not  equal to  `UTIME_OMIT') is  used to  override the  file brith  timestamp.
                                       * NOTE: Passing this flag when the 3rd  timespec isn't set to `UTIME_OMIT'  requires
                                       *       that the calling thread be holding the `CAP_SYS_TIME' permission and be  the
                                       *       owner of the file in question, or to be holding the `CAP_FOWNER' permission.
                                       *       Less permissions  are required  when `UTIME_NOW'  is passed,  in which  case
                                       *       `CAP_SYS_TIME' is not required (similarly how having `CAP_FOWNER', or  being
                                       *       the owner would allow  you to copy the  file (updating the timestamp),  then
                                       *       replacing the original)
                                       * NOTE: This flag is used to implement full compatibility with NT's SetFileTime function. */
#define __AT_READLINK_REQSIZE  0x0200 /* For use with `freadlinkat' and friends.
                                       * Rather  than following  unix semantics  and returning  the amount of
                                       * copied bytes with  no indication  of whether or  not everything  was
                                       * copied, return the ~required~  buffer size (including a  terminating
                                       * NUL-character that normally wouldn't be copied either) to user-space
                                       * (which may be more than the  specified buffer size, which should  be
                                       * reallocated to fit in successive calls)
                                       * Additionally, as already  mentioned, a  trailing NUL-character  is
                                       * appended  to the link  text, ensuring that  a valid C-style string
                                       * can be read so long as the provided buffer was of sufficient size. */
#define __AT_REMOVEREG        0x04000 /* Explicitly allow removing anything that unlink() removes. (Default;
                                       * Set in addition to `AT_REMOVEDIR' to implement `remove()' semantics
                                       * as an atomic kernel operation, removing any race condition that the
                                       * alternative  of  `if (unlink(x) && errno == EISDIR) rmdir(x)' would
                                       * introduce). */
#if __KOS_VERSION__ >= 400
#define __AT_ALTPATH         0x200000 /* For `frealpath4' / `frealpathat': the specified path should
                                       * be  printed  as  the  reverse  of  the  `AT_DOSPATH'  flag:
                                       *  - 0                      : in:UNIX  out:UNIX
                                       *  - AT_DOSPATH             : in:DOS   out:DOS
                                       *  - AT_ALTPATH             : in:UNIX  out:DOS
                                       *  - AT_ALTPATH | AT_DOSPATH: in:DOS   out:UNIX */
#endif /* __KOS_VERSION__ >= 400 */
#else /* __KOS_VERSION__ >= 300 */
#define __AT_REMOVEREG        0x40000 /* ... */
#endif /* __KOS_VERSION__ < 300 */
#define __AT_DOSPATH         0x100000 /* Interpret '\\'  as  '/',  and ignore  casing  during  path  resolution.
                                       * Additionally,  recognize  `<LETTER>:'-style  drive  prefixes,  as  well
                                       * as make use of per-drive working directories, as well as drive-relative
                                       * path names that start with a leading slash.
                                       * Basically, when set: perform the system call in DOS-compatibility mode.
                                       * HINT:  This  flag can  be specified  with  the `fsmode()'  system call. */
#endif /* __KOS__ */


/* Special values that may be used for the `dfd' argument of `*at' functions. */
#define __AT_FDCWD  (-100) /* The current working directory. */
#ifdef __KOS__
#define __AT_FDROOT (-101) /* Same as `__AT_FDCWD' but sets the filesystem root
                            * (using this, you  can `chroot()' with  'dup2()'!) */
/* Special, symbolic file numbers.
 * These descriptors cannot be overwritten,
 * and their  meaning is  context-sensible. */
#define __AT_FDTHRD    (-180) /* HANDLE_TYPE_PIDFD (read-only; equivalent of `pidfd_open(gettid())') */
#if __KOS_VERSION__ >= 400
#define __AT_FDPROC    (-181) /* HANDLE_TYPE_PIDFD (read-only; equivalent of `pidfd_open(getpid())') */
#define __AT_FDPARPROC (-182) /* HANDLE_TYPE_PIDFD (read-only; equivalent of `pidfd_open(getppid())') */
#define __AT_FDCTTY    (-183) /* HANDLE_TYPE_MFILE (writable; equivalent of `open("/dev/tty")') */
#define __AT_FDSYSRTLD (-184) /* HANDLE_TYPE_MFILE (read-only; handle for `execabi_system_rtld_file') */
#endif /* __KOS_VERSION__ >= 400 */
#if __KOS_VERSION__ >= 300
#if __KOS_VERSION__ < 400
#define __AT_THIS_TASK  __AT_FDTHRD
#define __AT_THIS_MMAN  __AT_THIS_TASK
#define __AT_THIS_STACK __AT_THIS_TASK
#endif /* __KOS_VERSION__ < 400 */
/* DOS Drive root / current-working paths.
 * These are special file descriptors that can be written to using `dup2()',
 * where   they  expect  to  receive  either  a  FILE  or  PATH  descriptor.
 * Once  set,  these  paths  describe   the  root-paths  of  DOS's   drives:
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
 * >> //       If it isn't, an `E_FSERROR_CROSS_DEVICE_LINK' error is thrown.
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
 *     With  that  in   mind,  you   should  not   re-mount  a   DOS  drive   as  a   sub-directory  of   where
 *     it  was   located  before   then,  unless   you   first  unshared   your  VFS   (using   `CLONE_NEWNS').
 *     Allowing  a   program's   current   working   directory   to   be   located   outside   the   associated
 *     drive causes weak undefined behavior. In KOS this means:
 *       - `xfdname()' will not produce the correct path
 *       - Relative path names still operate on the old directory
 *       - Navigating into parent directories is no longer restricted (except by `chroot()')
 *       - Manually navigating into a portion of the new drives mounting point fixes the problem.
 *   - DOS drive mounting points are beneath UNIX mounting points, in that they don't
 *     actually mount a superblock to some  filesystem location, but rather mirror  a
 *     filesystem  path, meaning that DOS drives can  be thought of as the equivalent
 *     of the `dfd' argument of `*at' system calls:
 *     >> open("C:\\foo.txt"); // Same as `openat(AT_FDDRIVE_ROOT('C'), "foo.txt")'
 *     If `mount()' is used to create a  new (real) mounting point, it will  appear
 *     in  all DOS drives that are mounting  the location where the mount happened,
 *     or  any location further up the tree  immediately (it's the same data object
 *     internally; DOS drives are merely aliasing regular paths; aka. `O_PATH')
 *   - To ~unmount~ (quote-unquote) a DOS drive, simply close() the associated root file descriptor:
 *     >> // Unmount `C:' (also closes the associated FDCWD descriptor)
 *     >> close(AT_FDDRIVE_ROOT('C'));
 *   - Mounting, or unmounting dos drives requires the same privileges as the `mount()' and `umount()' system calls.
 *   - Closing an `AT_FDDRIVE_CWD()' descriptor will revert it to match the root path of the associated drive.
 *     >> close(AT_FDDRIVE_CWD('C'));
 *     >> // Same as:
 *     >> dup2(AT_FDDRIVE_ROOT('C'),AT_FDDRIVE_CWD('C'));
 *   - Symbolic links  are evaluated  the same  as any  user-provided  path.
 *     If a symbolic link starts with a '/' or '\\' character, the remainder
 *     of its  text  is relative  to  the  first DOS  drive  mounting  point
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
#define __FD_CLOFORK 0x20 /* FLAG: Close the descriptor during unsharing after `fork()'. */
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

#endif /* !_ASM_OS_KOS_FCNTL_H */
