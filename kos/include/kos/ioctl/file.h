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
#ifndef _KOS_IOCTL_FILE_H
#define _KOS_IOCTL_FILE_H 1

/* KOS-specific ioctl codes for anything derived from `mfile' */

#include <__stdinc.h>

#include <asm/ioctl.h>
#include <linux/fs.h>

/* Standard (linux-compatible) file I/O-control codes.
 * Commented out ioctls work, but shouldn't be used because they suck. */
/*efine FILE_IOC_GETFLAGS   FS_IOC_GETFLAGS    * Get INode flags (set of `FS_*') */
/*efine FILE_IOC_SETFLAGS   FS_IOC_SETFLAGS    * Set INode flags (set of `FS_*') */
#define FILE_IOC_GETFSLABEL FS_IOC_GETFSLABEL /* Get volume label */
#define FILE_IOC_SETFSLABEL FS_IOC_SETFSLABEL /* Set volume label */
#define FILE_IOC_GETRO      BLKROGET          /* [int *arg] Get `MFILE_F_READONLY' */
#define FILE_IOC_SETRO      BLKROSET          /* [int const *arg] Set `MFILE_F_READONLY'
                                               * - requires `CAP_SYS_ADMIN' for devices
                                               * - requires `CAP_FOWNER' / st_uid==geteuid() for regular files */
/*efine FILE_IOC_GETSIZE512 BLKGETSIZE         * [ulongptr_t *arg] Get `st_size / 512' */
/*efine FILE_IOC_FLSBUF     BLKFLSBUF          * Alias for `fdatasync(fd)', followed by discarding preloaded read-buffers */
/*efine _FILE_IOC_BLOCKSIZE BLKSSZGET          * [int *arg]    Get *actual* block size */
#define FILE_IOC_BLOCKSIZE  BLKBSZGET         /* [size_t *arg] Get *actual* block size */
#define FILE_IOC_GETSIZE    BLKGETSIZE64      /* [uint64_t *arg] Return `st_size' */


/************************************************************************/
/* Actually KOS-specific ioctls.                                        */
/************************************************************************/
#define FILE_IOC_DELETED   _IOR_KOS('F', 0x00, int)                  /* Check if the file was deleted (as per `unlink(2)') */
#define FILE_IOC_HASRAWIO  _IOR_KOS('F', 0x01, int)                  /* Check if the file supports "raw io" (s.a. `mfile_hasrawio()') */
#define FILE_IOC_DCHANGED  _IOR_KOS('F', 0x02, int)                  /* Check if data of the file has changed (s.a. `fdatasync(2)', `mfile_haschanged()') */
#define FILE_IOC_CHANGED   _IOR_KOS('F', 0x03, int)                  /* Check if attributes or data have changed (s.a. `fsync(2)', `MFILE_F_CHANGED | MFILE_F_ATTRCHANGED') */
#define FILE_IOC_BLKSHIFT  _IOR_KOS('F', 0x04, struct file_blkshift) /* This ioctl is meant to be used to query buffer requirements for `O_DIRECT',
                                                                      * which requires file offsets be  aligned by `1 << fbs_blck', and I/O  buffer
                                                                      * pointers to be aligned by `1 << fbs_ioba' (IOBaseAddress_SHIFT). */
#define FILE_IOC_TAILREAD _IOWR_KOS('F', 0x20, struct file_tailread) /* Tail read (see below) */


/* Return `_PC_*' for the superblock associated with the given file.
 * - This ioctl is only support for `fnode'-derived files */
#define FILE_IOC_GETFSLINKMAX _IOR_KOS('F', 0x80, __nlink_t)      /* _PC_LINK_MAX:           `struct fsuper::fs_feat::sf_link_max' */
#define FILE_IOC_GETFSNAMEMAX _IOR_KOS('F', 0x81, __uint16_t)     /* _PC_NAME_MAX:           `struct fsuper::fs_feat::sf_name_max' */
#define FILE_IOC_GETFSSIZBITS _IOR_KOS('F', 0x82, __SHIFT_TYPE__) /* _PC_FILESIZEBITS:       `struct fsuper::fs_feat::sf_filesizebits' */
#define FILE_IOC_GETFSXFERINC _IOR_KOS('F', 0x83, __uint32_t)     /* _PC_REC_INCR_XFER_SIZE: `struct fsuper::fs_feat::sf_rec_incr_xfer_size' */
#define FILE_IOC_GETFSXFERMAX _IOR_KOS('F', 0x84, __uint32_t)     /* _PC_REC_MAX_XFER_SIZE:  `struct fsuper::fs_feat::sf_rec_max_xfer_size' */
#define FILE_IOC_GETFSXFERMIN _IOR_KOS('F', 0x85, __uint32_t)     /* _PC_REC_MIN_XFER_SIZE:  `struct fsuper::fs_feat::sf_rec_min_xfer_size' */
#define FILE_IOC_GETFSXFERALN _IOR_KOS('F', 0x86, __uint32_t)     /* _PC_REC_XFER_ALIGN:     `struct fsuper::fs_feat::sf_rec_xfer_align' (also re-used for `_PC_ALLOC_SIZE_MIN') */
#define FILE_IOC_GETFSSYMMAX  _IOR_KOS('F', 0x87, __uint64_t)     /* _PC_SYMLINK_MAX:        `struct fsuper::fs_feat::sf_symlink_max' (non-zero-ness determines `_PC_2_SYMLINKS') */


#ifdef __CC__
__DECL_BEGIN

struct file_blkshift {
	/* Buffer requirements for O_DIRECT:
	 * >> fd_t fd = open("/my/file.txt", O_RDWR | O_DIRECT);
	 * >> assert((           pos & ((1 << fbs_blck) - 1)) == 0);
	 * >> assert((           siz & ((1 << fbs_blck) - 1)) == 0);
	 * >> assert(((uintptr_t)buf & ((1 << fbs_ioba) - 1)) == 0); // HINT: `memalign((size_t)1 << fbs_ioba, bufsize)'
	 * >> pread_or_pwrite(fd, buf, siz, pos);
	 * NOTE: You may assume that `fbs_ioba <= fbs_blck' */
	__SHIFT_TYPE__ fbs_blck; /* log2(FILE_IOC_BLOCKSIZE)             (s.a. `struct mfile::mf_blockshift') */
	__SHIFT_TYPE__ fbs_ioba; /* log2(BUFFER_ALIGNMENT_FOR_O_DIRECT)  (s.a. `struct mfile::mf_iobashift') */
};

/* Perform a tail read from a file. This ioctl behaves the same  as
 * a normal `pread(2)', with the exception that trying to read past
 * the end of a file will not indicate EOF, but will instead  cause
 * the system call to block until the file was extended by at least
 * one byte (blocking is only done on the first byte at `ftr_pos').
 *
 * When the associated file is deleted (as per `unlink(2)') while a
 * tail-read  is blocking, the  read will no  longer block and will
 * instead always indicate EOF.
 *
 * Should the file get extended by means of a write() past the end
 * of the file, whatever was written beyond the file's end will be
 * immediately written to the buffer  provided to this ioctl.  The
 * easiest way to append data at the end of a file is `IO_APPEND'.
 *
 * As  such, this ioctl can be used to implement `tail -f' without
 * the need of periodically polling for the file to have grown, or
 * doing other os-specific shenanigans relating to dnotify.
 *
 * NOTE: This ioctl can only be used on files that support the  "raw"
 *       i/o mechanism (`FILE_IOC_HASRAWIO'),  and doesn't  overwrite
 *       the pread(2) operator. Trying to use this function on a file
 *       to  which this doesn't apply will cause this ioctl to behave
 *       the  same  as `preadf(..., IO_NONBLOCK)',  meaning  that the
 *       function will not block when nothing could be read, but will
 *       instead return with `ftr_siz = 0'. */
struct file_tailread {
	/* Argument type for `FILE_IOC_TAILREAD' */
	__uint64_t      ftr_pos;   /* [in] Absolute file position at which to start reading */
	__uint64_t      ftr_siz;   /* [in]  Input buffer size (in bytes) / max # of bytes to read
	                            * [out] Actual # of bytes that were read. */
	union {
		void       *ftr_buf;   /* [0..ftr_siz] Target buffer for read data. */
		__uint64_t _ftr_albuf; /* ... */
	};
};

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_IOCTL_FILE_H */
