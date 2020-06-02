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

%[define_replacement(sigset_t = "struct __sigset_struct")]
%[default_impl_section(.text.crt.sched.pthread)]


%{

#include <__stdinc.h>
#include <features.h>
#include <bits/types.h>

/* Documentation (partially) derived from Glibc /usr/include/i386-linux-gnu/bits/statvfs.h */
/* Copyright (C) 1997-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


#if __SIZEOF_SYSCALL_LONG_T__ == 4
#define _STATVFSBUF_F_UNUSED 1
#endif /* __SIZEOF_SYSCALL_LONG_T__ == 4 */

/*[[[enum]]]*/
#ifdef __CC__
enum {
	ST_RDONLY      = 1,     /* Mount read-only.  */
	ST_NOSUID      = 2,     /* Ignore suid and sgid bits.  */
#ifdef __USE_GNU
	ST_NODEV       = 4,     /* Disallow access to device special files.  */
	ST_NOEXEC      = 8,     /* Disallow program execution.  */
	ST_SYNCHRONOUS = 16,    /* Writes are synced at once.  */
	ST_MANDLOCK    = 64,    /* Allow mandatory locks on an FS.  */
	ST_WRITE       = 128,   /* Write on file/directory/symlink.  */
	ST_APPEND      = 256,   /* Append-only file.  */
	ST_IMMUTABLE   = 512,   /* Immutable file.  */
	ST_NOATIME     = 1024,  /* Do not update access times.  */
	ST_NODIRATIME  = 2048,  /* Do not update directory access times.  */
	ST_RELATIME    = 4096,  /* Update atime relative to mtime/ctime.  */
#endif /* __USE_GNU */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define ST_RDONLY      ST_RDONLY      /* Mount read-only.  */
#define ST_NOSUID      ST_NOSUID      /* Ignore suid and sgid bits.  */
#ifdef __USE_GNU
#define ST_NODEV       ST_NODEV       /* Disallow access to device special files.  */
#define ST_NOEXEC      ST_NOEXEC      /* Disallow program execution.  */
#define ST_SYNCHRONOUS ST_SYNCHRONOUS /* Writes are synced at once.  */
#define ST_MANDLOCK    ST_MANDLOCK    /* Allow mandatory locks on an FS.  */
#define ST_WRITE       ST_WRITE       /* Write on file/directory/symlink.  */
#define ST_APPEND      ST_APPEND      /* Append-only file.  */
#define ST_IMMUTABLE   ST_IMMUTABLE   /* Immutable file.  */
#define ST_NOATIME     ST_NOATIME     /* Do not update access times.  */
#define ST_NODIRATIME  ST_NODIRATIME  /* Do not update directory access times.  */
#define ST_RELATIME    ST_RELATIME    /* Update atime relative to mtime/ctime.  */
#endif /* __USE_GNU */
#else /* __COMPILER_PREFERR_ENUMS */
#define ST_RDONLY      1    /* Mount read-only.  */
#define ST_NOSUID      2    /* Ignore suid and sgid bits.  */
#ifdef __USE_GNU
#define ST_NODEV       4    /* Disallow access to device special files.  */
#define ST_NOEXEC      8    /* Disallow program execution.  */
#define ST_SYNCHRONOUS 16   /* Writes are synced at once.  */
#define ST_MANDLOCK    64   /* Allow mandatory locks on an FS.  */
#define ST_WRITE       128  /* Write on file/directory/symlink.  */
#define ST_APPEND      256  /* Append-only file.  */
#define ST_IMMUTABLE   512  /* Immutable file.  */
#define ST_NOATIME     1024 /* Do not update access times.  */
#define ST_NODIRATIME  2048 /* Do not update directory access times.  */
#define ST_RELATIME    4096 /* Update atime relative to mtime/ctime.  */
#endif /* __USE_GNU */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


#ifdef __CC__
__SYSDECL_BEGIN

struct statvfs {
	__ULONGPTR_TYPE__   f_bsize;    /* TODO: DOC */
	__ULONGPTR_TYPE__   f_frsize;   /* TODO: DOC */
	__FS_TYPE(fsblkcnt) f_blocks;   /* TODO: DOC */
	__FS_TYPE(fsblkcnt) f_bfree;    /* TODO: DOC */
	__FS_TYPE(fsblkcnt) f_bavail;   /* TODO: DOC */
	__FS_TYPE(fsfilcnt) f_files;    /* TODO: DOC */
	__FS_TYPE(fsfilcnt) f_ffree;    /* TODO: DOC */
	__FS_TYPE(fsfilcnt) f_favail;   /* TODO: DOC */
	__ULONGPTR_TYPE__   f_fsid;     /* TODO: DOC */
#ifdef _STATVFSBUF_F_UNUSED
	__ULONGPTR_TYPE__ __f_unused;   /* ... */
//	__INT32_TYPE__    __f_unused;
#endif /* _STATVFSBUF_F_UNUSED */
	__ULONGPTR_TYPE__   f_flag;     /* TODO: DOC */
	__ULONGPTR_TYPE__   f_namemax;  /* TODO: DOC */
	__INT32_TYPE__    __f_spare[6]; /* ... */
};

#ifdef __USE_LARGEFILE64
struct statvfs64 {
	__ULONGPTR_TYPE__   f_bsize;    /* TODO: DOC */
	__ULONGPTR_TYPE__   f_frsize;   /* TODO: DOC */
	__fsblkcnt64_t      f_blocks;   /* TODO: DOC */
	__fsblkcnt64_t      f_bfree;    /* TODO: DOC */
	__fsblkcnt64_t      f_bavail;   /* TODO: DOC */
	__fsfilcnt64_t      f_files;    /* TODO: DOC */
	__fsfilcnt64_t      f_ffree;    /* TODO: DOC */
	__fsfilcnt64_t      f_favail;   /* TODO: DOC */
	__ULONGPTR_TYPE__   f_fsid;     /* TODO: DOC */
#ifdef _STATVFSBUF_F_UNUSED
	__ULONGPTR_TYPE__ __f_unused;   /* ... */
//	__INT32_TYPE__    __f_unused;
#endif /* _STATVFSBUF_F_UNUSED */
	__ULONGPTR_TYPE__   f_flag;     /* TODO: DOC */
	__ULONGPTR_TYPE__   f_namemax;  /* TODO: DOC */
	__INT32_TYPE__    __f_spare[6]; /* ... */
};
#endif /* __USE_LARGEFILE64 */

__SYSDECL_END
#endif /* __CC__ */

}