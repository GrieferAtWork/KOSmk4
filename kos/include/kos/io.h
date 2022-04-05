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
#ifndef _KOS_IO_H
#define _KOS_IO_H 1

#include <__stdinc.h>
#include <features.h>

#include <asm/os/dirent.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <asm/os/poll.h>
#include <asm/os/stat.h>
#include <asm/os/stdio.h>
#include <bits/types.h>

#ifndef __KOS__
#error "KOS-only system header"
#endif /* !__KOS__ */

__DECL_BEGIN

#ifdef __CC__
#ifndef __iomode_t_defined
#define __iomode_t_defined
typedef __iomode_t iomode_t; /* Set of `IO_*' */
#endif /* !__iomode_t_defined */

#ifndef __readdir_mode_t_defined
#define __readdir_mode_t_defined
typedef unsigned int readdir_mode_t; /* Set of `READDIR_*' */
#endif /* !__readdir_mode_t_defined */

#ifndef __fallocate_mode_t_defined
#define __fallocate_mode_t_defined
typedef unsigned int fallocate_mode_t; /* TODO */
#endif /* !__fallocate_mode_t_defined */

#ifndef __poll_mode_t_defined
#define __poll_mode_t_defined
typedef unsigned int poll_mode_t; /* Set of `POLL*' */
#endif /* !poll_mode_t_defined */
#endif /* __CC__ */


/* Access test flags (for use with `access(2)') */
#if !defined(R_OK) && defined(__R_OK)
#define R_OK __R_OK /* Test for read permission. */
#endif /* !R_OK && __R_OK */
#if !defined(W_OK) && defined(__W_OK)
#define W_OK __W_OK /* Test for write permission. */
#endif /* !W_OK && __W_OK */
#if !defined(X_OK) && defined(__X_OK)
#define X_OK __X_OK /* Test for execute permission. */
#endif /* !X_OK && __X_OK */
#if !defined(F_OK) && defined(__F_OK)
#define F_OK __F_OK /* Test for existence. */
#endif /* !F_OK && __F_OK */


/* Poll flags (`poll_mode_t' / `struct pollfd')
 *     Event  types that can be polled for. These bits may be set in `events'
 *     to indicate the interesting event types; they will appear in `revents'
 *     to indicate the status of the file descriptor. */
#if !defined(POLLIN) && defined(__POLLIN)
#define POLLIN               __POLLIN               /* There is data to read. (`read' & friends won't block when invoked) */
#endif /* !POLLIN && __POLLIN */
#if !defined(POLLPRI) && defined(__POLLPRI)
#define POLLPRI              __POLLPRI              /* There is urgent data to read. */
#endif /* !POLLPRI && __POLLPRI */
#if !defined(POLLOUT) && defined(__POLLOUT)
#define POLLOUT              __POLLOUT              /* Writing now will not block. (`write' & friends won't block when invoked) */
#endif /* !POLLOUT && __POLLOUT */
#if !defined(POLLRDNORM) && defined(__POLLRDNORM)
#define POLLRDNORM           __POLLRDNORM           /* 100% identical to `POLLIN' (Normal data may be read). */
#endif /* !POLLRDNORM && __POLLRDNORM */
#if !defined(POLLRDBAND) && defined(__POLLRDBAND)
#define POLLRDBAND           __POLLRDBAND           /* Priority data may be read. */
#endif /* !POLLRDBAND && __POLLRDBAND */
#if !defined(POLLWRNORM) && defined(__POLLWRNORM)
#define POLLWRNORM           __POLLWRNORM           /* 100% identical to `POLLOUT' (Writing now will not block). */
#endif /* !POLLWRNORM && __POLLWRNORM */
#if !defined(POLLWRBAND) && defined(__POLLWRBAND)
#define POLLWRBAND           __POLLWRBAND           /* Priority data may be written. */
#endif /* !POLLWRBAND && __POLLWRBAND */
#if !defined(POLLRDHUP) && defined(__POLLRDHUP)
#define POLLRDHUP            __POLLRDHUP            /* Socket peer closed connection, or shut down writing half of its connection */
#endif /* !POLLRDHUP && __POLLRDHUP */
#if !defined(POLLHUP) && defined(__POLLHUP)
#define POLLHUP              __POLLHUP              /* Hung up. (writes are no longer possible) */
#endif /* !POLLHUP && __POLLHUP */
#if !defined(POLLSELECT_READFDS) && defined(__POLLSELECT_READFDS)
#define POLLSELECT_READFDS   __POLLSELECT_READFDS   /* select(2).readfds */
#endif /* !POLLSELECT_READFDS && __POLLSELECT_READFDS */
#if !defined(POLLSELECT_WRITEFDS) && defined(__POLLSELECT_WRITEFDS)
#define POLLSELECT_WRITEFDS  __POLLSELECT_WRITEFDS  /* select(2).writefds */
#endif /* !POLLSELECT_WRITEFDS && __POLLSELECT_WRITEFDS */
#if !defined(POLLSELECT_EXCEPTFDS) && defined(__POLLSELECT_EXCEPTFDS)
#define POLLSELECT_EXCEPTFDS __POLLSELECT_EXCEPTFDS /* select(2).exceptfds */
#endif /* !POLLSELECT_EXCEPTFDS && __POLLSELECT_EXCEPTFDS */

#ifndef POLLINMASK
#if defined(__POLLIN) && defined(__POLLRDNORM)
#define POLLINMASK (__POLLIN | __POLLRDNORM)
#elif defined(__POLLIN)
#define POLLINMASK __POLLIN
#elif defined(__POLLRDNORM)
#define POLLINMASK __POLLRDNORM
#else /* ... */
#define POLLINMASK 0
#endif /* !... */
#endif /* !POLLINMASK */

#ifndef POLLOUTMASK
#if defined(__POLLOUT) && defined(__POLLWRNORM)
#define POLLOUTMASK (__POLLOUT | __POLLWRNORM)
#elif defined(__POLLOUT)
#define POLLOUTMASK __POLLOUT
#elif defined(__POLLWRNORM)
#define POLLOUTMASK __POLLWRNORM
#else /* ... */
#define POLLOUTMASK 0
#endif /* !... */
#endif /* !POLLOUTMASK */





/* File status flags (`struct stat::st_mode') */
#if !defined(S_IFMT) && defined(__S_IFMT)
#define S_IFMT   __S_IFMT   /* These bits determine file type. */
#endif /* !S_IFMT && __S_IFMT */
#if !defined(S_IFDIR) && defined(__S_IFDIR)
#define S_IFDIR  __S_IFDIR  /* Directory. */
#endif /* !S_IFDIR && __S_IFDIR */
#if !defined(S_IFCHR) && defined(__S_IFCHR)
#define S_IFCHR  __S_IFCHR  /* Character device. */
#endif /* !S_IFCHR && __S_IFCHR */
#if !defined(S_IFBLK) && defined(__S_IFBLK)
#define S_IFBLK  __S_IFBLK  /* Block device. */
#endif /* !S_IFBLK && __S_IFBLK */
#if !defined(S_IFREG) && defined(__S_IFREG)
#define S_IFREG  __S_IFREG  /* Regular file. */
#endif /* !S_IFREG && __S_IFREG */
#if !defined(S_IFIFO) && defined(__S_IFIFO)
#define S_IFIFO  __S_IFIFO  /* FIFO. */
#endif /* !S_IFIFO && __S_IFIFO */
#if !defined(S_IFLNK) && defined(__S_IFLNK)
#define S_IFLNK  __S_IFLNK  /* Symbolic link. */
#endif /* !S_IFLNK && __S_IFLNK */
#if !defined(S_IFSOCK) && defined(__S_IFSOCK)
#define S_IFSOCK __S_IFSOCK /* Socket. */
#endif /* !S_IFSOCK && __S_IFSOCK */
#if !defined(S_ISUID) && defined(__S_ISUID)
#define S_ISUID  __S_ISUID  /* Set user ID on execution. */
#endif /* !S_ISUID && __S_ISUID */
#if !defined(S_ISGID) && defined(__S_ISGID)
#define S_ISGID  __S_ISGID  /* Set group ID on execution. */
#endif /* !S_ISGID && __S_ISGID */
#if !defined(S_ISVTX) && defined(__S_ISVTX)
#define S_ISVTX  __S_ISVTX  /* Save swapped text after use (sticky). */
#endif /* !S_ISVTX && __S_ISVTX */

#ifndef S_IRUSR
#define S_IRUSR 0400 /* Read by owner. */
#define S_IWUSR 0200 /* Write by owner. */
#define S_IXUSR 0100 /* Execute by owner. */
#define S_IRWXU 0700
#define S_IRGRP 0040 /* Read by group. */
#define S_IWGRP 0020 /* Write by group. */
#define S_IXGRP 0010 /* Execute by group. */
#define S_IRWXG 0070
#define S_IROTH 0004 /* Read by others. */
#define S_IWOTH 0002 /* Write by others. */
#define S_IXOTH 0001 /* Execute by others. */
#define S_IRWXO 0007
#endif /* !S_IRWXO */

#ifndef S_IRWXUGO
#define S_IRWXUGO 0777
#endif /* !S_IRWXUGO */
#ifndef S_IALLUGO
#define S_IALLUGO 07777
#endif /* !S_IALLUGO */
#ifndef S_IRUGO
#define S_IRUGO 0444
#endif /* !S_IRUGO */
#ifndef S_IWUGO
#define S_IWUGO 0222
#endif /* !S_IWUGO */
#ifndef S_IXUGO
#define S_IXUGO 0111
#endif /* !S_IXUGO */


/* File mode test macros. */
#if !defined(S_ISDIR) && defined(__S_ISDIR)
#define S_ISDIR(mode)  __S_ISDIR(mode)  /* Directory. */
#endif /* !S_ISDIR && __S_ISDIR */
#if !defined(S_ISCHR) && defined(__S_ISCHR)
#define S_ISCHR(mode)  __S_ISCHR(mode)  /* Character device. */
#endif /* !S_ISCHR && __S_ISCHR */
#if !defined(S_ISBLK) && defined(__S_ISBLK)
#define S_ISBLK(mode)  __S_ISBLK(mode)  /* Block device. */
#endif /* !S_ISBLK && __S_ISBLK */
#if !defined(S_ISDEV) && defined(__S_ISDEV)
#define S_ISDEV(mode)  __S_ISDEV(mode) /* S_ISCHR(mode) || S_ISBLK(mode) */
#endif /* !S_ISDEV && __S_ISDEV */
#if !defined(S_ISREG) && defined(__S_ISREG)
#define S_ISREG(mode)  __S_ISREG(mode)  /* Regular file. */
#endif /* !S_ISREG && __S_ISREG */
#if !defined(S_ISFIFO) && defined(__S_ISFIFO)
#define S_ISFIFO(mode) __S_ISFIFO(mode) /* FIFO. */
#endif /* !S_ISFIFO && __S_ISFIFO */
#if !defined(S_ISLNK) && defined(__S_ISLNK)
#define S_ISLNK(mode)  __S_ISLNK(mode)  /* Symbolic link. */
#endif /* !S_ISLNK && __S_ISLNK */
#if !defined(S_ISSOCK) && defined(__S_ISSOCK)
#define S_ISSOCK(mode) __S_ISSOCK(mode) /* Socket. */
#endif /* !S_ISSOCK && __S_ISSOCK */


/* Directory entry types (`struct dirent::d_type'). */
#if !defined(DT_UNKNOWN) && defined(__DT_UNKNOWN)
#define DT_UNKNOWN __DT_UNKNOWN /* Unknown file type */
#endif /* !DT_UNKNOWN && __DT_UNKNOWN */
#if !defined(DT_FIFO) && defined(__DT_FIFO)
#define DT_FIFO    __DT_FIFO    /* FistInFirstOut (pipe) file (s.a. `S_ISFIFO()', `S_IFMT & S_IFIFO') */
#endif /* !DT_FIFO && __DT_FIFO */
#if !defined(DT_CHR) && defined(__DT_CHR)
#define DT_CHR     __DT_CHR     /* Character device file      (s.a. `S_ISCHR()', `S_IFMT & S_IFCHR') */
#endif /* !DT_CHR && __DT_CHR */
#if !defined(DT_DIR) && defined(__DT_DIR)
#define DT_DIR     __DT_DIR     /* Directory                  (s.a. `S_ISDIR()', `S_IFMT & S_IFDIR') */
#endif /* !DT_DIR && __DT_DIR */
#if !defined(DT_BLK) && defined(__DT_BLK)
#define DT_BLK     __DT_BLK     /* Block device file          (s.a. `S_ISBLK()', `S_IFMT & S_IFBLK') */
#endif /* !DT_BLK && __DT_BLK */
#if !defined(DT_REG) && defined(__DT_REG)
#define DT_REG     __DT_REG     /* Regular text file          (s.a. `S_ISREG()', `S_IFMT & S_IFREG') */
#endif /* !DT_REG && __DT_REG */
#if !defined(DT_LNK) && defined(__DT_LNK)
#define DT_LNK     __DT_LNK     /* Symbolic link              (s.a. `S_ISLNK()', `S_IFMT & S_IFLNK') */
#endif /* !DT_LNK && __DT_LNK */
#if !defined(DT_SOCK) && defined(__DT_SOCK)
#define DT_SOCK    __DT_SOCK    /* Socket file                (s.a. `S_ISSOCK()', `S_IFMT & S_IFSOCK') */
#endif /* !DT_SOCK && __DT_SOCK */
#if !defined(DT_WHT) && defined(__DT_WHT)
#define DT_WHT     __DT_WHT     /* Mounting point? */
#endif /* !DT_WHT && __DT_WHT */


/* Convert between stat structure types and directory types. */
#if !defined(IFTODT) && defined(__IFTODT)
#define IFTODT(mode) __IFTODT(mode)
#endif /* !IFTODT && __IFTODT */
#if !defined(DTTOIF) && defined(__DTTOIF)
#define DTTOIF(dirtype) __DTTOIF(dirtype)
#endif /* !DTTOIF && __DTTOIF */



/* Open flags (s.a. `open(2)', `oflag_t') */
#if !defined(O_ACCMODE) && defined(__O_ACCMODE)
#define O_ACCMODE   __O_ACCMODE   /* Mask for `O_RDONLY | O_WRONLY | O_RDWR' */
#endif /* !O_ACCMODE && __O_ACCMODE */
#if !defined(O_RDONLY) && defined(__O_RDONLY)
#define O_RDONLY    __O_RDONLY    /* Access mode: read-only */
#endif /* !O_RDONLY && __O_RDONLY */
#if !defined(O_WRONLY) && defined(__O_WRONLY)
#define O_WRONLY    __O_WRONLY    /* Access mode: write-only */
#endif /* !O_WRONLY && __O_WRONLY */
#if !defined(O_RDWR) && defined(__O_RDWR)
#define O_RDWR      __O_RDWR      /* Access mode: read/write */
#endif /* !O_RDWR && __O_RDWR */
#if !defined(O_TRUNC) && defined(__O_TRUNC)
#define O_TRUNC     __O_TRUNC     /* Truncate the file's size to 0 */
#endif /* !O_TRUNC && __O_TRUNC */
#if !defined(O_CREAT) && defined(__O_CREAT)
#define O_CREAT     __O_CREAT     /* If missing, create a new file */
#endif /* !O_CREAT && __O_CREAT */
#if !defined(O_EXCL) && defined(__O_EXCL)
#define O_EXCL      __O_EXCL      /* When used with `O_CREAT', throw an `E_FSERROR_FILE_ALREADY_EXISTS' (-EEXISTS)
                                   * exception if the file already exists. */
#endif /* !O_EXCL && __O_EXCL */
#if !defined(O_NOCTTY) && defined(__O_NOCTTY)
#define O_NOCTTY    __O_NOCTTY    /* If the calling process does not have a controlling terminal assigned,
                                   * do not attempt to assign the newly opened file as terminal, even when
                                   * `isatty(open(...))' would be true. */
#endif /* !O_NOCTTY && __O_NOCTTY */
#if !defined(O_APPEND) && defined(__O_APPEND)
#define O_APPEND    __O_APPEND    /* Always append data to the end of the file */
#endif /* !O_APPEND && __O_APPEND */
#if !defined(O_NONBLOCK) && defined(__O_NONBLOCK)
#define O_NONBLOCK  __O_NONBLOCK  /* Do not block when trying to read data that hasn't been written, yet. */
#endif /* !O_NONBLOCK && __O_NONBLOCK */
#if !defined(O_SYNC) && defined(__O_SYNC)
#define O_SYNC      __O_SYNC      /* ??? */
#endif /* !O_SYNC && __O_SYNC */
#if !defined(O_ASYNC) && defined(__O_ASYNC)
#define O_ASYNC     __O_ASYNC     /* ??? */
#endif /* !O_ASYNC && __O_ASYNC */
#if !defined(O_LARGEFILE) && defined(__O_LARGEFILE)
#define O_LARGEFILE __O_LARGEFILE /* Ignored... */
#endif /* !O_LARGEFILE && __O_LARGEFILE */
#if !defined(O_DIRECTORY) && defined(__O_DIRECTORY)
#define O_DIRECTORY __O_DIRECTORY /* Throw an `E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_OPEN' (-ENOTDIR) exception when the
                                   * final path component of  an open() system  call turns out  to be something  other than a  directory. */
#endif /* !O_DIRECTORY && __O_DIRECTORY */
#if !defined(O_NOFOLLOW) && defined(__O_NOFOLLOW)
#define O_NOFOLLOW  __O_NOFOLLOW  /* Throw an `E_FSERROR_IS_A_SYMBOLIC_LINK:E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN'  exception
                                   * when the final path component of an open() system call turns out to be a symbolic link. */
#endif /* !O_NOFOLLOW && __O_NOFOLLOW */
#if !defined(O_CLOEXEC) && defined(__O_CLOEXEC)
#define O_CLOEXEC   __O_CLOEXEC   /* Close the file during exec() */
#endif /* !O_CLOEXEC && __O_CLOEXEC */
#if !defined(O_CLOFORK) && defined(__O_CLOFORK)
#define O_CLOFORK   __O_CLOFORK   /* Close the handle when the file descriptors are unshared (s.a. `CLONE_FILES') */
#endif /* !O_CLOFORK && __O_CLOFORK */
#if !defined(O_DOSPATH) && defined(__O_DOSPATH)
#define O_DOSPATH   __O_DOSPATH   /* Interpret  '\\'  as  '/',  and   ignore  casing  during  path   resolution.
                                   * Additionally,   recognize  DOS  mounting   points,  and  interpret  leading
                                   * slashes as relative to the closest DOS mounting point. (s.a.: `AT_DOSPATH') */
#endif /* !O_DOSPATH && __O_DOSPATH */
#if !defined(O_DIRECT) && defined(__O_DIRECT)
#define O_DIRECT    __O_DIRECT    /* Bypass unified I/O buffers. Directly read-from / write-to hardware (s.a. `FILE_IOC_BLKSHIFT'). */
#endif /* !O_DIRECT && __O_DIRECT */
#if !defined(O_NOATIME) && defined(__O_NOATIME)
#define O_NOATIME   __O_NOATIME   /* Don't update last-accessed time stamps. */
#endif /* !O_NOATIME && __O_NOATIME */
#if !defined(O_PATH) && defined(__O_PATH)
#define O_PATH      __O_PATH      /* Open a path for *at system calls. */
#endif /* !O_PATH && __O_PATH */
#if !defined(O_TMPFILE) && defined(__O_TMPFILE)
#define O_TMPFILE   __O_TMPFILE   /* Open a temporary file */
#endif /* !O_TMPFILE && __O_TMPFILE */
#if !defined(O_DSYNC) && defined(__O_DSYNC)
#define O_DSYNC     __O_DSYNC     /* ??? */
#endif /* !O_DSYNC && __O_DSYNC */
#if !defined(O_RSYNC) && defined(__O_SYNC)
#define O_RSYNC     __O_SYNC      /* ??? */
#endif /* !O_RSYNC && __O_SYNC */



/* Seek (whence) options. */
#if !defined(SEEK_SET) && defined(__SEEK_SET)
#define SEEK_SET __SEEK_SET /* Seek from beginning of file. */
#endif /* !SEEK_SET && __SEEK_SET */
#if !defined(SEEK_CUR) && defined(__SEEK_CUR)
#define SEEK_CUR __SEEK_CUR /* Seek from current position. */
#endif /* !SEEK_CUR && __SEEK_CUR */
#if !defined(SEEK_END) && defined(__SEEK_END)
#define SEEK_END __SEEK_END /* Seek from end of file. */
#endif /* !SEEK_END && __SEEK_END */
#if !defined(SEEK_DATA) && defined(__SEEK_DATA)
#define SEEK_DATA __SEEK_DATA /* Seek to next data. */
#endif /* !SEEK_DATA && __SEEK_DATA */
#if !defined(SEEK_HOLE) && defined(__SEEK_HOLE)
#define SEEK_HOLE __SEEK_HOLE /* Seek to next hole. */
#endif /* !SEEK_HOLE && __SEEK_HOLE */



#ifndef READDIR_DEFAULT
#define READDIR_DEFAULT  0x0000 /* Yield to next entry when `buf' was of sufficient size. */
#define READDIR_CONTINUE 0x0001 /* Always yield to next entry. */
#define READDIR_PEEK     0x0002 /* Never yield to next entry. */
#if __KOS_VERSION__ >= 300
#define READDIR_SKIPREL  0x4000 /* Skip reading the `.' and `..' directory entries. */
#define READDIR_WANTEOF  0x8000 /* Minor optimization for `READDIR_MULTIPLE':
                                 * The system is allowed to append an empty directory entry
                                 * (with  `d_namlen = 0' and `d_name[0] = '\0''; other fields are undefined).
                                 * If there isn't enough space for such an entry, no such entry will be emit.
                                 * Since no other  directory entry can  ever have a  length of ZERO(0),  this
                                 * allows  user-space  to detect  end-of-directory  without the  need  of re-
                                 * invoking  the kreaddir() system  call and inspecting  its return value for
                                 * being equal to ZERO(0).
                                 * However, that check is still required, as this flag may be ignored for no
                                 * reason immediately apparent (if the EOF entry can't fit into the  buffer,
                                 * there's  no way of knowing if there's  a missing entry that's supposed to
                                 * go into the buffer, or if it was actually an EOF entry). Additionally, no
                                 * EOF  entry may be written if kreaddir()  is invoked on a directory handle
                                 * who's stream position is at the end of the directory.
                                 * For usage, see the example below, as well as `READDIR_MULTIPLE_ISEOF()' */
#define READDIR_MODEMASK 0x001f /* Mask for the kreaddir() mode. */
#define READDIR_FLAGMASK 0xc000 /* Mask of known kreaddir() flags. */
#define READDIR_MODEMAX  0x0003 /* Mask recognized mode ID. */
#define READDIR_MULTIPLE 0x0003 /* Read as many directory entries as can fit into the buffer. If at
                                 * least one entry could be read,  return the combined size of  all
                                 * read entries (in bytes) (in this case, `return <= bufsize').  If
                                 * the buffer was too small to  contain the next entry, return  the
                                 * required size to house that  pending entry, but don't yield  it,
                                 * the  same way `READDIR_DEFAULT'  wouldn't. To enumerate multiple
                                 * directories in some buffer, use the macros below. */
#ifdef __CC__
/* READDIR_MULTIPLE buffer helpers:
 * >> for (;;) {
 * >>     char buffer[2048]; size_t bufsize;
 * >>     struct dirent *iter = (struct dirent *)buffer;
 * >>     // Read as many entries as our buffer can fit
 * >>     bufsize = kreaddir(fd, iter, sizeof(buffer),
 * >>                        READDIR_MULTIPLE|
 * >>                        READDIR_WANTEOF);
 * >>     if (!bufsize)
 * >>         break; // End of directory
 * >>     if (bufsize > sizeof(buffer)) {
 * >>         printf("The next directory entry larger than the buffer\n");
 * >>         break;
 * >>     }
 * >>     // Process successfully read entries
 * >>     do {
 * >>         // This check is only required when `READDIR_WANTEOF' is passed.
 * >>         if (READDIR_MULTIPLE_ISEOF(iter))
 * >>             goto done;
 * >>         printf("Entry: %q\n", iter->d_name);
 * >>         iter = READDIR_MULTIPLE_GETNEXT(iter);
 * >>     } while (READDIR_MULTIPLE_ISVALID(iter, buffer, bufsize));
 * >> }
 * >>done:
 */
#define READDIR_MULTIPLE_GETNEXT(p)                                      \
	((struct dirent *)(((uintptr_t)((p)->d_name + ((p)->d_namlen + 1)) + \
	                    (sizeof(__ino64_t) - 1)) &                       \
	                   ~(sizeof(__ino64_t) - 1)))
#define READDIR_MULTIPLE_ISVALID(p, buf, bufsize)                               \
	(((__BYTE_TYPE__ *)((p)->d_name)) < ((__BYTE_TYPE__ *)(buf) + (bufsize)) && \
	 ((__BYTE_TYPE__ *)((p)->d_name + (p)->d_namlen)) < ((__BYTE_TYPE__ *)(buf) + (bufsize)))
#define READDIR_MULTIPLE_ISEOF(p) ((p)->d_namlen == 0)
#ifdef __USE_LARGEFILE64
#define READDIR_MULTIPLE_GETNEXT64(p) ((struct dirent64 *)READDIR_MULTIPLE_GETNEXT(p))
#endif /* __USE_LARGEFILE64 */
#endif /* __CC__ */
#endif /* __KOS_VERSION__ >= 300 */
#endif /* !READDIR_DEFAULT */




#if !defined(FD_CLOEXEC) && defined(__FD_CLOEXEC)
#define FD_CLOEXEC __FD_CLOEXEC /* FLAG: Close the descriptor on `exec()'. */
#endif /* !FD_CLOEXEC && __FD_CLOEXEC */
#if !defined(FD_CLOFORK) && defined(__FD_CLOFORK)
#define FD_CLOFORK __FD_CLOFORK /* FLAG: Close the descriptor during unsharing after `fork()'. */
#endif /* !FD_CLOFORK && __FD_CLOFORK */




/* Universal I/O mode & handle access flags. */
#ifndef IO_GENERIC
#define IO_GENERIC    0x0000 /* Generic I/O access. */
#define IO_ACCMODE    0x0003 /* Access mode mask */
#define IO_RDONLY     0x0000 /* Read-only access */
#define IO_WRONLY     0x0001 /* Write-only access */
#define IO_RDWR       0x0002 /* Read/write access */
#define IO_RDWR_ALT   0x0003 /* Read/write access */
#define IO_CLOEXEC    0x0004 /* Close during exec() */
/*efine IO_           0x0008  * -- O_<undef> */
/*efine IO_           0x0010  * -- O_<undef> */
/*efine IO_           0x0020  * -- O_<undef> */
/*efine IO_           0x0040  * -- O_CREAT */
#define IO_CLOFORK    0x0080 /* Close during fork() (or rather: `unshare(CLONE_FILES)') */
/*efine IO_           0x0100  * -- O_NOCTTY */
/*efine IO_           0x0200  * -- O_TRUNC */
#define IO_APPEND     0x0400 /* Append newly written data at the end (== O_APPEND) */
#define IO_NONBLOCK   0x0800 /* Don't block in I/O (== O_NONBLOCK) */
#define IO_DSYNC      0x1000 /* Ensure that all modified caches are flushed during write() (== O_DSYNC) */
#define IO_ASYNC      0x2000 /* Use asynchronous I/O and generate SIGIO upon completion. */
#define IO_DIRECT     0x4000 /* Bypass unified I/O buffers. Directly read-from / write-to hardware (s.a. `FILE_IOC_BLKSHIFT'). */
#define IO_NODATAZERO 0x8000 /* For use with  `IO_NONBLOCK': Allow  0 to be  returned (which  normally indicates  EOF)
                              * when no data  is available at  the moment (which  normally would cause  `E_WOULDBLOCK'
                              * to be thrown). NOTE: This flag is merely a hint. - Functions are allowed to ignore it! */
#define IO_OFLAG_IDENT_MASK 0x7c03 /* Mask of flags with identical values to O_* flags */


/* Check if reading/writing is possible with a given I/O mode. */
#define IO_CANREAD(mode)      (((mode) & IO_ACCMODE) != IO_WRONLY)
#define IO_CANWRITE(mode)     (((mode) & IO_ACCMODE) != IO_RDONLY)
#define IO_CANREADWRITE(mode) (((mode) & IO_ACCMODE) == IO_RDWR)

/* Mask of flags accepted by the kos extension functions:
 * -> `readf(2)', `writef(2)', `preadf(2)', `pwritef(2)', `ioctlf(2)' */
#define IO_USERF_MASK (IO_APPEND | IO_NONBLOCK | IO_DSYNC | IO_DIRECT | IO_NODATAZERO)

/* Mask of flags modifiable via `F_SETFD' / `F_SETFL' */
#define IO_SETFL_MASK (IO_APPEND | IO_NONBLOCK | IO_DSYNC | IO_DIRECT | IO_ASYNC)

/* Mask for handle flags (flags not inherited during `dup()'). */
#define IO_SETFD_MASK (IO_CLOEXEC | IO_CLOFORK)

/* NOTE: The following flags don't affect I/O, but are stored in the same field.
 *       Additionally,   their   `O_*'   equivalent   have   different   values. */
#define IO_HANDLE_CLOEXEC           IO_CLOEXEC /* Close during exec() */
#define IO_HANDLE_CLOFORK           IO_CLOFORK /* Close during fork() (or rather: `unshare(CLONE_FILES)') */
#define IO_HANDLE_FFROM_OPENFLAG(x) (__CCAST(__iomode_t)(((x) & 0x1080000) >> 17)) /* Convert O_CLOEXEC|O_CLOFORK --> IO_CLOEXEC|IO_CLOFORK */
#define IO_HANDLE_FTO_OPENFLAG(x)   ((__CCAST(__oflag_t)(x) & 0x84) << 17)         /* Convert IO_CLOEXEC|IO_CLOFORK --> O_CLOEXEC|O_CLOFORK */
/* Similar to `IO_HANDLE_FFROM_O()' / `IO_HANDLE_FTO_O()', but used for converting `FD_*' flags. */
#define IO_HANDLE_FFROM_FD(x) (__CCAST(__iomode_t)((x) << 2))
#define IO_HANDLE_FTO_FD(x)   (((x) & (IO_HANDLE_CLOEXEC | IO_HANDLE_CLOFORK)) >> 2)

/* Convert I/O flags to/from `O_*' flags. */
#define IO_FROM_OPENFLAG(x)          (((x) & IO_OFLAG_IDENT_MASK) | IO_HANDLE_FFROM_OPENFLAG(x))
#define IO_TO_OPENFLAG(x)            (((x) & IO_OFLAG_IDENT_MASK) | IO_HANDLE_FTO_OPENFLAG(x))
#define IO_FROM_OPENFLAG_NOHANDLE(x) ((x) & IO_OFLAG_IDENT_MASK)
#define IO_TO_OPENFLAG_NOHANDLE(x)   ((x) & IO_OFLAG_IDENT_MASK)
#endif /* !IO_GENERIC */


/* Standard interface flags. */
#ifndef IFF_UP
#define IFF_UP          0x0001  /* Interface is up. */
#define IFF_BROADCAST   0x0002  /* Broadcast address valid. */
#define IFF_DEBUG       0x0004  /* Turn on debugging. */
#define IFF_LOOPBACK    0x0008  /* Is a loopback net. */
#define IFF_POINTOPOINT 0x0010  /* Interface is point-to-point link. */
#define IFF_NOTRAILERS  0x0020  /* Avoid use of trailers. */
#define IFF_RUNNING     0x0040  /* Resources allocated. */
#define IFF_NOARP       0x0080  /* No address resolution protocol. */
#define IFF_PROMISC     0x0100  /* Receive all packets. */
#define IFF_ALLMULTI    0x0200  /* Receive all multicast packets. */
#define IFF_MASTER      0x0400  /* [const] Master of a load balancer. */
#define IFF_SLAVE       0x0800  /* [const] Slave of a load balancer. */
#define IFF_MULTICAST   0x1000  /* [const] Supports multicast. */
#define IFF_PORTSEL     0x2000  /* [const] Can set media type. */
#define IFF_AUTOMEDIA   0x4000  /* [const] Auto media select active. */
#define IFF_DYNAMIC     0x8000  /* [const] Dialup device with changing addresses. */
#endif /* !IFF_UP */
#define IFF_STATUS      0x0040  /* Mask for status flags. */
#define IFF_CONST       0xfc00  /* [const] Mask for constant (feature) flags. */

__DECL_END

#endif /* !_KOS_IO_H */
