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
#ifndef _BITS_IO_FILE_H
#define _BITS_IO_FILE_H 1

#include <__stdinc.h>
#include <__crt.h>
#include <hybrid/typecore.h>

/* I/O buffer flags (DOS-compatible)
 * WARNING: These flags may change in the future. */
#define __IO_FILE_IOR       0x0001 /* The current buffer was read from disk (Undefined when 'if_cnt == 0'). */
#define __IO_FILE_IOW       0x0002 /* The current buffer has changed since being read. */
#define __IO_FILE_IONBF     0x0004 /* ??? */
#define __IO_FILE_IOMALLBUF 0x0008 /* The buffer was allocated internally. */
#define __IO_FILE_IOEOF     0x0010 /* Set when the file pointed to by 'if_fd' has been exhausted. */
#define __IO_FILE_IOERR     0x0020 /* Set when an I/O error occurred. */
#define __IO_FILE_IONOFD    0x0040 /* The file acts as output to buffer only. - 'if_fd' is not valid. (Currently ignored when loading/flushing data) */
#define __IO_FILE_IORW      0x0080 /* The file was opened for read+write permissions ('+' flag) */
#define __IO_FILE_IOUSERBUF 0x0100 /* The buffer was given by the user. */
#define __IO_FILE_IOLNBUF   0x0200 /* NOT ORIGINALLY DEFINED IN DOS: Use line-buffering. */
#define __IO_FILE_IOSETVBUF 0x0400 /* ??? */
#define __IO_FILE_IOFEOF    0x0800 /* Never used */
#define __IO_FILE_IOFLRTN   0x1000 /* ??? */
#define __IO_FILE_IOCTRLZ   0x2000 /* ??? */
#define __IO_FILE_IOCOMMIT  0x4000 /* Invoke fsync() during fflush() */
#define __IO_FILE_IOLOCKED  0x8000 /* ??? */
#define __IO_FILE_IOLNIFTYY 0x80000000 /* NOT ORIGINALLY DEFINED IN DOS: Determine 'isatty()' on first access and set `__IO_FILE_IOLNBUF' accordingly. */
#define __IO_FILE_IOREADING 0x40000000 /* NOT ORIGINALLY DEFINED IN DOS: The buffer is currently being read into and must not be changed or resized. */
#define __IO_FILE_IOISATTY  0x20000000 /* NOT ORIGINALLY DEFINED IN DOS: The buffer refers to a TTY */
#define __IO_FILE_IONOTATTY 0x10000000 /* NOT ORIGINALLY DEFINED IN DOS: The buffer doesn't refer to a TTY */


#ifdef __CC__
#ifdef __CRT_KOS_PRIMARY
#ifdef __BUILDING_LIBC
/* This structure is only defined internally, because
 * that's how private data should be encapsulated.
 * NOTE: The first byte of this structure is always the NUL character,
 *       thus allowing library users to interpret a pointer to it as
 *       a C-string of 0 length. */
struct iofile_data;
#endif /* __BUILDING_LIBC */
#endif /* __CRT_KOS_PRIMARY */

__NAMESPACE_STD_BEGIN

#ifdef __CRT_KOS_PRIMARY
struct __IO_FILE {
#ifdef __BUILDING_LIBC
#if __SIZEOF_POINTER__ >= 8
#define __IO_FILE_INIT(if_ptr_, if_cnt_, if_base_, if_flag_, if_fd_, if_charbuf_, if_bufsize_, if_exdata_) \
	{                                                                                                      \
		/* .if_ptr     = */ if_ptr_,                                                                       \
		/* .if_cnt     = */ if_cnt_,                                                                       \
		/* .__if_pad0  = */ 0,                                                                             \
		/* .if_base    = */ if_base_,                                                                      \
		/* .if_flag    = */ if_flag_,                                                                      \
		/* .if_fd      = */ if_fd_,                                                                        \
		/* .if_charbuf = */ if_charbuf_,                                                                   \
		/* .if_bufsiz  = */ if_bufsize_,                                                                   \
		/* .if_exdata  = */ if_exdata_                                                                     \
	}
#else /* __SIZEOF_POINTER__ >= 8 */
#define __IO_FILE_INIT(if_ptr_, if_cnt_, if_base_, if_flag_, if_fd_, if_charbuf_, if_bufsize_, if_exdata_) \
	{                                                                                                      \
		/* .if_ptr     = */ if_ptr_,                                                                       \
		/* .if_cnt     = */ if_cnt_,                                                                       \
		/* .if_base    = */ if_base_,                                                                      \
		/* .if_flag    = */ if_flag_,                                                                      \
		/* .if_fd      = */ if_fd_,                                                                        \
		/* .if_charbuf = */ if_charbuf_,                                                                   \
		/* .if_bufsiz  = */ if_bufsize_,                                                                   \
		/* .if_exdata  = */ if_exdata_                                                                     \
	}
#endif /* __SIZEOF_POINTER__ < 8 */
	__BYTE_TYPE__      *if_ptr;        /* [>= if_base][+if_cnt <= if_base + if_bufsiz][lock(if_exdata->io_lock)]
	                                    * Pointer to the next character to-be read/written.
	                                    * The absolute in-file position is then `if_exdata->io_fblk + (if_ptr - if_base)' */
	__UINT32_TYPE__     if_cnt;        /* [lock(if_exdata->io_lock)] The amount of unread, buffered bytes located at `if_ptr'. */
#if __SIZEOF_POINTER__ >= 8
	__INT32_TYPE__    __if_pad0;
#endif /* __SIZEOF_POINTER__ >= 8 */
	__BYTE_TYPE__      *if_base;       /* [0..if_bufsiz][owned_if(IO_MALLBUF)][lock(if_exdata->io_lock)]
	                                    * Allocated buffer. NOTE: This pointer must not be modified when `IO_READING' is set. */
	__UINT32_TYPE__     if_flag;       /* Set of `IO_*' (aka. `__IO_FILE_IO*') */
	__INT32_TYPE__      if_fd;         /* [valid_if(!IO_HASVTAB)] Underlying file descriptor.
	                                    * NOTE: When available, this stream's file pointer is assumed
	                                    *       to be located at the end of the loaded buffer. */
	__BYTE_TYPE__       if_charbuf[4]; /* A very small inline-allocated buffer used as fallback for 'if_base' */
	__UINT32_TYPE__     if_bufsiz;     /* [lock(if_exdata->io_lock)] Total allocated / available buffer size.
	                                    * NOTE: This pointer must not be modified when `IO_READING' is set. */
	struct iofile_data *if_exdata;     /* [1..1][owned][const] Pointer to some internal data.
	                                    * HINT: To fix binary compatibility with DOS, the first byte of
	                                    *       this structure is a NUL-character, allowing library users
	                                    *       to interpret this member as a C-string of 0 length. */
#define __f_ptr      if_ptr
#define __f_cnt      if_cnt
#define __f_base     if_base
#define __f_flag     if_flag
#define __f_file     if_fd
#define __f_charbuf  if_charbuf
#define __f_bufsiz   if_bufsiz
#define __f_tmpfname if_exdata
#else /* __BUILDING_LIBC */
#ifdef __USE_KOS
	/* Use names that are protected by the C standard. */
	char          *__f_ptr;
	__INT32_TYPE__ __f_cnt;
#if __SIZEOF_POINTER__ >= 8
	__INT32_TYPE__ __f_pad0;
#endif
	char          *__f_base;
	__INT32_TYPE__ __f_flag;
	__INT32_TYPE__ __f_file;
	__INT32_TYPE__ __f_charbuf;
	__INT32_TYPE__ __f_bufsiz;
	char          *__f_tmpfname;
#else /* __USE_KOS */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("_ptr")
#pragma push_macro("_cnt")
#pragma push_macro("_base")
#pragma push_macro("_flag")
#pragma push_macro("_file")
#pragma push_macro("_charbuf")
#pragma push_macro("_bufsiz")
#pragma push_macro("_tmpfname")
#endif
	/* Must #undef keyboard that are not allowed by the C
	 * standard and may collide with user-defined macros. */
#undef _ptr
#undef _cnt
#undef _base
#undef _flag
#undef _file
#undef _charbuf
#undef _bufsiz
#undef _tmpfname

#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union { char          *__f_ptr;      char          *_ptr;      };
	union { __INT32_TYPE__ __f_cnt;      __INT32_TYPE__ _cnt;      };
#if __SIZEOF_POINTER__ >= 8
	__INT32_TYPE__         __f_pad0;
#endif
	union { char          *__f_base;     char          *_base;     };
	union { __INT32_TYPE__ __f_flag;     __INT32_TYPE__ _flag;     };
	union { __INT32_TYPE__ __f_file;     __INT32_TYPE__ _file;     };
	union { __INT32_TYPE__ __f_charbuf;  __INT32_TYPE__ _charbuf;  };
	union { __INT32_TYPE__ __f_bufsiz;   __INT32_TYPE__ _bufsiz;   };
	union { char          *__f_tmpfname; char          *_tmpfname; };
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	char          *_ptr;
	__INT32_TYPE__ _cnt;
#if __SIZEOF_POINTER__ >= 8
	__INT32_TYPE__ __f_pad0;
#endif
	char          *_base;
	__INT32_TYPE__ _flag;
	__INT32_TYPE__ _file;
	__INT32_TYPE__ _charbuf;
	__INT32_TYPE__ _bufsiz;
	char          *_tmpfname;
#define __f_ptr      _ptr
#define __f_cnt      _cnt
#define __f_base     _base
#define __f_flag     _flag
#define __f_file     _file
#define __f_charbuf  _charbuf
#define __f_bufsiz   _bufsiz
#define __f_tmpfname _tmpfname
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("_tmpfname")
#pragma pop_macro("_bufsiz")
#pragma pop_macro("_charbuf")
#pragma pop_macro("_file")
#pragma pop_macro("_flag")
#pragma pop_macro("_base")
#pragma pop_macro("_cnt")
#pragma pop_macro("_ptr")
#endif
#endif /* !__USE_KOS */
#endif /* !__BUILDING_LIBC */
};
#elif defined(__CRT_DOS_PRIMARY)
struct __IO_FILE {
#ifdef __USE_KOS
	/* Use names that are protected by the C standard. */
	char          *__f_ptr;
	__INT32_TYPE__ __f_cnt;
#if __SIZEOF_POINTER__ >= 8
	__INT32_TYPE__ __f_pad0;
#endif
	char          *__f_base;
	__INT32_TYPE__ __f_flag;
	__INT32_TYPE__ __f_file;
	__INT32_TYPE__ __f_charbuf;
	__INT32_TYPE__ __f_bufsiz;
	char          *__f_tmpfname;
#else /* __USE_KOS */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("_ptr")
#pragma push_macro("_cnt")
#pragma push_macro("_base")
#pragma push_macro("_flag")
#pragma push_macro("_file")
#pragma push_macro("_charbuf")
#pragma push_macro("_bufsiz")
#pragma push_macro("_tmpfname")
#endif

	/* Must #undef keyboard that are not allowed by the C
	 * standard and may collide with user-defined macros. */
#undef _ptr
#undef _cnt
#undef _base
#undef _flag
#undef _file
#undef _charbuf
#undef _bufsiz
#undef _tmpfname

#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union { char          *__f_ptr;      char          *_ptr;      };
	union { __INT32_TYPE__ __f_cnt;      __INT32_TYPE__ _cnt;      };
#if __SIZEOF_POINTER__ >= 8
	__INT32_TYPE__         __f_pad0;
#endif
	union { char          *__f_base;     char          *_base;     };
	union { __INT32_TYPE__ __f_flag;     __INT32_TYPE__ _flag;     };
	union { __INT32_TYPE__ __f_file;     __INT32_TYPE__ _file;     };
	union { __INT32_TYPE__ __f_charbuf;  __INT32_TYPE__ _charbuf;  };
	union { __INT32_TYPE__ __f_bufsiz;   __INT32_TYPE__ _bufsiz;   };
	union { char          *__f_tmpfname; char          *_tmpfname; };
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	char          *_ptr;
	__INT32_TYPE__ _cnt;
#if __SIZEOF_POINTER__ >= 8
	__INT32_TYPE__ __f_pad0;
#endif
	char          *_base;
	__INT32_TYPE__ _flag;
	__INT32_TYPE__ _file;
	__INT32_TYPE__ _charbuf;
	__INT32_TYPE__ _bufsiz;
	char          *_tmpfname;
#define __f_ptr      _ptr
#define __f_cnt      _cnt
#define __f_base     _base
#define __f_flag     _flag
#define __f_file     _file
#define __f_charbuf  _charbuf
#define __f_bufsiz   _bufsiz
#define __f_tmpfname _tmpfname
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("_tmpfname")
#pragma pop_macro("_bufsiz")
#pragma pop_macro("_charbuf")
#pragma pop_macro("_file")
#pragma pop_macro("_flag")
#pragma pop_macro("_base")
#pragma pop_macro("_cnt")
#pragma pop_macro("_ptr")
#endif
#endif /* !__USE_KOS */
};
#else
struct __IO_FILE; /* Opaque */
#endif

#ifndef __std_FILE_defined
#define __std_FILE_defined 1
typedef __FILE FILE;
#endif /* !__std_FILE_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#ifndef __FILE_defined
#define __FILE_defined 1
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#endif /* __CC__ */


#endif /* !_BITS_IO_FILE_H */
