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
#ifndef _KOS_IO_H
#define _KOS_IO_H 1

#include <__stdinc.h>
#include <features.h>

#include <asm/dirent.h>
#include <asm/stat.h>
#include <bits/types.h>
#include <bits/fcntl.h> /* Open flags (`oflag_t') */

#ifndef __KOS__
#error "KOS-only system header"
#endif /* !__KOS__ */

__DECL_BEGIN

#ifdef __CC__
#ifndef __iomode_t_defined
#define __iomode_t_defined 1
typedef __iomode_t iomode_t; /* Set of `IO_*' */
#endif /* !__iomode_t_defined */

#ifndef __readdir_mode_t_defined
#define __readdir_mode_t_defined 1
typedef unsigned int readdir_mode_t; /* Set of `READDIR_*' */
#endif /* !__readdir_mode_t_defined */

#ifndef __fallocate_mode_t_defined
#define __fallocate_mode_t_defined 1
typedef unsigned int fallocate_mode_t; /* TODO */
#endif /* !__fallocate_mode_t_defined */

#ifndef __poll_mode_t_defined
#define __poll_mode_t_defined 1
typedef unsigned int poll_mode_t; /* Set of `POLL*' */
#endif /* !poll_mode_t_defined */
#endif /* __CC__ */


/* Poll flags (`poll_mode_t' / `struct pollfd') */
#ifndef POLLIN
#define POLLIN   0x001 /* There is data to read. (`read' & friends won't block when invoked) */
#define POLLPRI  0x002 /* There is urgent data to read. */
#define POLLOUT  0x004 /* Writing now will not block. (`write' & friends won't block when invoked) */
#endif /* !POLLOUT */



/* File status flags (`struct stat::st_mode') */
#ifndef S_IFMT
#define S_IFMT   __S_IFMT   /* These bits determine file type. */
#define S_IFDIR  __S_IFDIR  /* Directory. */
#define S_IFCHR  __S_IFCHR  /* Character device. */
#define S_IFBLK  __S_IFBLK  /* Block device. */
#define S_IFREG  __S_IFREG  /* Regular file. */
#define S_IFIFO  __S_IFIFO  /* FIFO. */
#define S_IFLNK  __S_IFLNK  /* Symbolic link. */
#define S_IFSOCK __S_IFSOCK /* Socket. */
#define S_ISUID  __S_ISUID  /* Set user ID on execution. */
#define S_ISGID  __S_ISGID  /* Set group ID on execution. */
#define S_ISVTX  __S_ISVTX  /* Save swapped text after use (sticky). */
#define S_IREAD  __S_IREAD  /* Read by owner. */
#define S_IWRITE __S_IWRITE /* Write by owner. */
#define S_IEXEC  __S_IEXEC  /* Execute by owner. */
#endif /* !S_IFMT */

#ifndef S_ISDIR
#define S_ISDIR(x)  __S_ISDIR(x)
#define S_ISCHR(x)  __S_ISCHR(x)
#define S_ISBLK(x)  __S_ISBLK(x)
#define S_ISREG(x)  __S_ISREG(x)
#define S_ISFIFO(x) __S_ISFIFO(x)
#define S_ISLNK(x)  __S_ISLNK(x)
#endif /* !S_ISDIR */
#ifndef S_ISDEV
#define S_ISDEV(x)  __S_ISDEV(x)
#endif /* !S_ISDEV */


/* Directory entry types (`struct dirent::d_type'). */
#ifndef DT_UNKNOWN
#define DT_UNKNOWN __DT_UNKNOWN
#define DT_FIFO    __DT_FIFO
#define DT_CHR     __DT_CHR
#define DT_DIR     __DT_DIR
#define DT_BLK     __DT_BLK
#define DT_REG     __DT_REG
#define DT_LNK     __DT_LNK
#define DT_SOCK    __DT_SOCK
#define DT_WHT     __DT_WHT
#endif /* DT_UNKNOWN */

/* Convert between stat structure types and directory types. */
#ifndef IFTODT
#define IFTODT(mode)    __IFTODT(mode)
#define DTTOIF(dirtype) __DTTOIF(dirtype)
#endif /* !IFTODT */


/* File system mode (`atflag_t') */
#ifndef FS_MODE_FNORMAL
#define FS_MODE_FNORMAL                   0x00000000 /* Operate normally. */
#define FS_MODE_FIGNORE_TRAILING_SLASHES  0x00000002 /* Ignore empty trailing path segments. */
#define FS_MODE_FSYMLINK_NOFOLLOW         0x00000100 /* If the last path component is a symlink, don't follow it. */
#define FS_MODE_FNO_AUTOMOUNT             0x00000800 /* Suppress terminal automount traversal. */
#define FS_MODE_FEMPTY_PATH               0x00001000 /* Allow empty relative pathname. */
#define FS_MODE_FSYMLINK_REGULAR          0x00002000 /* Treat symbolic links similar to like regular files and throw an
                                                      * `E_FSERROR_TOO_MANY_SYMBOLIC_LINKS' error during the first encounter. */
#define FS_MODE_FDOSPATH                  0x00100000 /* Interpret '\\' as '/', and ignore casing during path resolution. */

#define FS_MODE_FALWAYS0MASK              0xffefc7ff /* Mask of bits always 0 in `struct fs::f_atmask' */
#define FS_MODE_FALWAYS1MASK              0x00000100 /* Mask of bits always 1 in `struct fs::f_atmask' */
#define FS_MODE_FALWAYS0FLAG              0xffefc7ff /* Mask of bits always 0 in `struct fs::f_atflag' */
#define FS_MODE_FALWAYS1FLAG              0x00000000 /* Mask of bits always 1 in `struct fs::f_atflag' */
#endif /* !FS_MODE_FNORMAL */





#ifndef READDIR_DEFAULT
#define READDIR_DEFAULT  0x0000 /* Yield to next entry when `buf' was of sufficient size. */
#define READDIR_CONTINUE 0x0001 /* Always yield to next entry. */
#define READDIR_PEEK     0x0002 /* Never yield to next entry. */
#if __KOS_VERSION__ >= 300
#define READDIR_SKIPREL  0x4000 /* Skip reading the `.' and `..' directory entries. */
#define READDIR_WANTEOF  0x8000 /* Minor optimization for `READDIR_MULTIPLE':
                                 * The system is allowed to append an empty directory entry
                                 * (with `d_namlen = 0' and `d_name[0] = '\0''; other fields are undefined).
                                 * If there isn't enough space for such an entry, no such entry will be emit.
                                 * Since no other directory entry can ever have a length of ZERO(0),
                                 * this allows user-space to detect end-of-directory without the need
                                 * of re-invoking the kreaddir() system call and inspecting its return
                                 * value for being equal to ZERO(0).
                                 * However, that check is still required, as this flag may be ignored
                                 * for no reason immediately apparent (if the EOF entry can't fit into
                                 * the buffer, there's no way of knowing if there's a missing entry that's
                                 * supposed to go into the buffer, or if it was actually an EOF entry).
                                 * Additionally, no eof entry may be written if kreaddir() is invoked
                                 * on a directory handle who's stream position is at the end of the directory.
                                 * For usage, see the example below, as well as `READDIR_MULTIPLE_ISEOF()' */
#define READDIR_MODEMASK 0x001f /* Mask for the kreaddir() mode. */
#define READDIR_FLAGMASK 0xc000 /* Mask of known kreaddir() flags. */
#define READDIR_MODEMAX  0x0003 /* Mask recognized mode ID. */
#define READDIR_MULTIPLE 0x0003 /* Read as many directory entries as can fit into the buffer.
                                 * If at least one entry could be read, return the combined size
                                 * of all read entries (in bytes) (in this case, `return <= bufsize')
                                 * If the buffer was too small to contain the next entry,
                                 * return the required size to house that pending entry,
                                 * but don't yield it, the same way `READDIR_DEFAULT' wouldn't.
                                 * To enumerate multiple directories in some buffer, use the
                                 * macros below. */
#ifdef __CC__
/* READDIR_MULTIPLE buffer helpers:
 * >> for (;;) {
 * >> 	char buffer[2048]; size_t bufsize;
 * >> 	struct dirent *iter = (struct dirent *)buffer;
 * >> 	// Read as many entries as our buffer can fit
 * >> 	bufsize = kreaddir(fd,iter,sizeof(buffer),
 * >> 	                   READDIR_MULTIPLE|
 * >> 	                   READDIR_WANTEOF);
 * >> 	if (!bufsize)
 * >> 		break; // End of directory
 * >> 	if (bufsize > sizeof(buffer)) {
 * >> 		printf("The next directory entry is too larger for the buffer\n");
 * >> 		break;
 * >> 	}
 * >> 	// Process successfully read entries
 * >> 	do {
 * >> 		// This check is only required when `READDIR_WANTEOF' is passed.
 * >> 		if (READDIR_MULTIPLE_ISEOF(iter))
 * >> 			goto done;
 * >> 		printf("Entry: %q\n",iter->d_name);
 * >> 		iter = READDIR_MULTIPLE_GETNEXT(iter);
 * >> 	} while (READDIR_MULTIPLE_ISVALID(iter,buffer,bufsize));
 * >> }
 * >>done:
 */
#define READDIR_MULTIPLE_GETNEXT(p) \
	((struct dirent *)(((uintptr_t)((p)->d_name+((p)->d_namlen+1))+ \
	                    (sizeof(__ino64_t)-1)) & ~(sizeof(__ino64_t)-1)))
#define READDIR_MULTIPLE_ISVALID(p,buf,bufsize) \
	(((__BYTE_TYPE__ *)((p)->d_name)) < ((__BYTE_TYPE__ *)(buf)+(bufsize)) && \
	 ((__BYTE_TYPE__ *)((p)->d_name+(p)->d_namlen)) < ((__BYTE_TYPE__ *)(buf)+(bufsize)))
#define READDIR_MULTIPLE_ISEOF(p) ((p)->d_namlen == 0)
#ifdef __USE_LARGEFILE64
#define READDIR_MULTIPLE_GETNEXT64(p) ((struct dirent64 *)READDIR_MULTIPLE_GETNEXT(p))
#endif /* __USE_LARGEFILE64 */
#endif /* __CC__ */
#endif /* __KOS_VERSION__ >= 300 */
#endif /* !READDIR_DEFAULT */




/* Universal I/O mode & handle access flags. */
#ifndef IO_GENERIC
#define IO_GENERIC     0x0000 /* Generic I/O access. */
#define IO_ACCMODE     0x0003 /* Access mode mask */
#define IO_RDONLY      0x0000 /* Read-only access */
#define IO_WRONLY      0x0001 /* Write-only access */
#define IO_RDWR        0x0002 /* Read/write access */
#define IO_RDWR_ALT    0x0003 /* Read/write access */
#define IO_CLOEXEC     0x0004 /* Close during exec() */
#define IO_CLOFORK     0x0008 /* Close during fork() */
#define IO_APPEND      0x0400 /* Append newly written data at the end */
#define IO_NONBLOCK    0x0800 /* Don't block in I/O */
#define IO_SYNC        0x1000 /* Ensure that all modified caches are flushed during write() */
#define IO_ASYNC       0x2000 /* Use asynchronous I/O and generate SIGIO upon completion. */
#define IO_DIRECT      0x4000 /* Bypass input/output buffers if possible. - Try to read/write data directly to/from provided buffers. */
#define IO_NODATAZERO  0x8000 /* For use with `IO_NONBLOCK': Allow 0 to be returned (which normally indicates EOF)
                               * when no data is available at the moment (which normally would cause `E_WOULDBLOCK'
                               * to be thrown). NOTE: This flag is merely a hint. - Functions are allowed to ignore it! */

/* Check if reading/writing is possible with a given I/O mode. */
#define IO_CANREAD(mode)      (((mode) & IO_ACCMODE) != IO_WRONLY)
#define IO_CANWRITE(mode)     (((mode) & IO_ACCMODE) != IO_RDONLY)
#define IO_CANREADWRITE(mode) (((mode) & IO_ACCMODE) == IO_RDWR)

/* Mask of flags accepted by the kos extension functions:
 *  `readf', `writef', `preadf', `pwritef', `ioctlf()', `hopf()' */
#define IO_USERF_MASK (IO_APPEND | IO_NONBLOCK | IO_SYNC | IO_ASYNC | IO_DIRECT | IO_NODATAZERO)

/* Mask of flags modifiable via `F_SETFD' / `F_SETFL' */
#define IO_SETFL_MASK (IO_APPEND | IO_NONBLOCK | IO_SYNC | IO_ASYNC | IO_DIRECT | IO_NODATAZERO)

/* Mask for handle flags (flags not inherited during `dup()'). */
#define IO_SETFD_MASK (IO_CLOEXEC | IO_CLOFORK)

/* NOTE: The following flags don't affect I/O, but are stored in the same field.
 *       Additionally, their `O_*' equivalent have different values. */
#define IO_HANDLE_CLOEXEC           IO_CLOEXEC /* Close during exec() */
#define IO_HANDLE_CLOFORK           IO_CLOFORK /* Close during fork() */
#define IO_HANDLE_FFROM_OPENFLAG(x) (__CCAST(__iomode_t)(((x) & 0x180000) >> 17))
#define IO_HANDLE_FTO_OPENFLAG(x)   ((__CCAST(__oflag_t)(x) & 0xc) << 17)
/* Similar to `IO_HANDLE_FFROM_O()' / `IO_HANDLE_FTO_O()', but used for converting `FD_*' flags. */
#define IO_HANDLE_FFROM_FD(x) (__CCAST(__iomode_t)((x) << 2))
#define IO_HANDLE_FTO_FD(x)   (__CCAST(__oflag_t)(x) >> 2)

/* Convert I/O flags to/from `O_*' flags. */
#define IO_FROM_OPENFLAG(x)          (((x) & 0xfff3) | IO_HANDLE_FFROM_OPENFLAG(x))
#define IO_TO_OPENFLAG(x)            (((x) & 0xfff3) | IO_HANDLE_FTO_OPENFLAG(x))
#define IO_FROM_OPENFLAG_NOHANDLE(x) ((x) & 0xfff3)
#define IO_TO_OPENFLAG_NOHANDLE(x)   ((x) & 0xfff3)
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
