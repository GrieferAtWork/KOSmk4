/* HASH CRC-32:0xef8d5db9 */
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
/* (#) Portability: Cygwin        (/newlib/libc/include/stdio_ext.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/stdio_ext.h) */
/* (#) Portability: GNU C Library (/include/stdio_ext.h) */
/* (#) Portability: GNU Hurd      (/usr/include/stdio_ext.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/stdio_ext.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/stdio_ext.h) */
/* (#) Portability: diet libc     (/include/stdio_ext.h) */
/* (#) Portability: libc6         (/include/stdio_ext.h) */
/* (#) Portability: musl libc     (/include/stdio_ext.h) */
/* (#) Portability: uClibc        (/include/stdio_ext.h) */
#ifndef _STDIO_EXT_H
#define _STDIO_EXT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <stdio.h>
#include <kos/anno.h>
#include <asm/crt/stdio_ext.h>
#include <bits/types.h>

/************************************************************************/
/* Possible values for `__fsetlocking(3)'                               */
/************************************************************************/
/* Don't change the locking type. */
#if !defined(FSETLOCKING_QUERY) && defined(__FSETLOCKING_QUERY)
#define FSETLOCKING_QUERY __FSETLOCKING_QUERY
#endif /* !FSETLOCKING_QUERY && __FSETLOCKING_QUERY */

/* Automatically acquire/release locks during file operators. */
#if !defined(FSETLOCKING_INTERNAL) && defined(__FSETLOCKING_INTERNAL)
#define FSETLOCKING_INTERNAL __FSETLOCKING_INTERNAL
#endif /* !FSETLOCKING_INTERNAL && __FSETLOCKING_INTERNAL */

/* Never automatically acquire  locks. The  only way file  locks are  still
 * acquired is through manual calls to `flockfile(3)' and `funlockfile(3)'.
 * This is the  equivalent of `__USE_STDIO_UNLOCKED'  on a per-file  basis. */
#if !defined(FSETLOCKING_BYCALLER) && defined(__FSETLOCKING_BYCALLER)
#define FSETLOCKING_BYCALLER __FSETLOCKING_BYCALLER
#endif /* !FSETLOCKING_BYCALLER && __FSETLOCKING_BYCALLER */
/************************************************************************/


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

/* >> __fbufsize(3)
 * Returns the used buffer size of the given `stream' (s.a. `setvbuf(3)')
 * @return: * : Used buffer size of `stream' */
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),size_t,__NOTHROW_NCX,__fbufsize,(__FILE __KOS_FIXED_CONST *__stream),(__stream))
/* >> __freading(3)
 * Returns  non-zero if the `stream' is read-only, or "the last operation
 * performed on `stream' was a read-operation". On KOS, this last part is
 * implemented such that we check for unsaved changes to `stream'. */
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__freading,(__FILE __KOS_FIXED_CONST *__stream),(__stream))
/* >> __fwriting(3)
 * Returns non-zero if the `stream'  is "write-only", or "the last  operation
 * performed on `stream' was a write-operation". On KOS, our stdio impl  does
 * not support write-only files (if reading isn't allowed, this will only  be
 * enforced on an fd-level by the kernel). Instead, we implement `__fwriting'
 * to return indicative of `stream' containing any unwritten changes. */
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__fwriting,(__FILE __KOS_FIXED_CONST *__stream),(__stream))
/* >> __freadable(3)
 * Returns non-zero if `stream'  allows for reading (s.a.  `fread(3)')
 * On  KOS, all stdio files can be  read from (except those opened for
 * file descriptors opened as `O_WRONLY', though in this case write(2)
 * is still attempted). As such, KOS  considers all stdio files to  be
 * readable, meaning that on KOS this function always returns `1'. */
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__freadable,(__FILE __KOS_FIXED_CONST *__stream),(__stream))
/* >> __fwritable(3)
 * Returns non-zero if `stream' is writable, that is: has been opened
 * with "w",  "r+", or  some similar  flag that  allows for  writing. */
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__fwritable,(__FILE __KOS_FIXED_CONST *__stream),(__stream))
/* >> __flbf(3)
 * Return  non-zero  if `stream'  is line-buffered.  (s.a. `_IOLBF')
 * Note  that on KOS, the line-buffered attribute of stdio files may
 * be determined  lazily, based  on  an underlying  file  descriptor
 * referring to a TTY. If this is the case, this function will  make
 * the appropriate call to `isatty(3)' and set the internal is-line-
 * buffered flag accordingly, before returning its state. */
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),int,__NOTHROW_NCX,__flbf,(__FILE *__stream),(__stream))
#ifdef __CRT_HAVE___fpurge
/* >> __fpurge(3)
 * Discard all modified, but unwritten data from `stream', as  well
 * as  all unread data previously buffered, but not yet read. After
 * a call to this function, the next `fread(3)' or `fwrite(3)' will
 * start off from a blank state. */
__CDECLARE_VOID(,__NOTHROW_NCX,__fpurge,(__FILE *__stream),(__stream))
#elif defined(__CRT_HAVE_fpurge)
/* >> __fpurge(3)
 * Discard all modified, but unwritten data from `stream', as  well
 * as  all unread data previously buffered, but not yet read. After
 * a call to this function, the next `fread(3)' or `fwrite(3)' will
 * start off from a blank state. */
__CREDIRECT_VOID(,__NOTHROW_NCX,__fpurge,(__FILE *__stream),fpurge,(__stream))
#endif /* ... */
#include <features.h>
#if defined(__CRT_HAVE___fpending_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> __fpending(3), __fpending_unlocked(3)
 * Returns the number of pending, but not-yet-written bytes of modified
 * file  data (s.a. `__fwriting(3)'). A call to `fflush(3)' can be used
 * to write all modified data to the system, and following such a call,
 * this function will return `0' until new unwritten data appears. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),size_t,__NOTHROW_NCX,__fpending,(__FILE __KOS_FIXED_CONST *__stream),__fpending_unlocked,(__stream))
#elif defined(__CRT_HAVE___fpending)
/* >> __fpending(3), __fpending_unlocked(3)
 * Returns the number of pending, but not-yet-written bytes of modified
 * file  data (s.a. `__fwriting(3)'). A call to `fflush(3)' can be used
 * to write all modified data to the system, and following such a call,
 * this function will return `0' until new unwritten data appears. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),size_t,__NOTHROW_NCX,__fpending,(__FILE __KOS_FIXED_CONST *__stream),(__stream))
#elif defined(__CRT_HAVE___fpending_unlocked)
/* >> __fpending(3), __fpending_unlocked(3)
 * Returns the number of pending, but not-yet-written bytes of modified
 * file  data (s.a. `__fwriting(3)'). A call to `fflush(3)' can be used
 * to write all modified data to the system, and following such a call,
 * this function will return `0' until new unwritten data appears. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),size_t,__NOTHROW_NCX,__fpending,(__FILE __KOS_FIXED_CONST *__stream),__fpending_unlocked,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE___fpending_unlocked
/* >> __fpending(3), __fpending_unlocked(3)
 * Returns the number of pending, but not-yet-written bytes of modified
 * file  data (s.a. `__fwriting(3)'). A call to `fflush(3)' can be used
 * to write all modified data to the system, and following such a call,
 * this function will return `0' until new unwritten data appears. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),size_t,__NOTHROW_NCX,__fpending_unlocked,(__FILE __KOS_FIXED_CONST *__stream),(__stream))
#elif defined(__CRT_HAVE___fpending)
/* >> __fpending(3), __fpending_unlocked(3)
 * Returns the number of pending, but not-yet-written bytes of modified
 * file  data (s.a. `__fwriting(3)'). A call to `fflush(3)' can be used
 * to write all modified data to the system, and following such a call,
 * this function will return `0' until new unwritten data appears. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),size_t,__NOTHROW_NCX,__fpending_unlocked,(__FILE __KOS_FIXED_CONST *__stream),__fpending,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE__flushlbf
/* >> _flushlbf(3)
 * Perform  a call  `fflush(stream)' for  every open  line-buffered stdio file.
 * Note that usually call this function isn't necessary, since the same already
 * happens automatically when  writing a line-feed  to any line-buffered  stdio
 * file (where line-buffered files are usually those opened on TTYs) */
__CDECLARE_VOID(,__NOTHROW_CB,_flushlbf,(void),())
#elif defined(__CRT_HAVE__IO_flush_all_linebuffered)
/* >> _flushlbf(3)
 * Perform  a call  `fflush(stream)' for  every open  line-buffered stdio file.
 * Note that usually call this function isn't necessary, since the same already
 * happens automatically when  writing a line-feed  to any line-buffered  stdio
 * file (where line-buffered files are usually those opened on TTYs) */
__CREDIRECT_VOID(,__NOTHROW_CB,_flushlbf,(void),_IO_flush_all_linebuffered,())
#endif /* ... */
/* >> __fsetlocking(3)
 * Set the locking type for `stream' to `type'. This affects all stdio functions
 * that aren't already lock-less by nature (iow: everything but `*_unlocked(3)')
 * @param: type: One of `FSETLOCKING_*', as defined in `<stdio_ext.h>'
 * @return: * : The locking type prior to this call (one of `FSETLOCKING_INTERNAL' or `FSETLOCKING_BYCALLER') */
__CDECLARE_OPT(,int,__NOTHROW_NCX,__fsetlocking,(__FILE *__stream, int __type),(__stream,__type))
/* >> __fseterr(3)
 * Set the error indicator of `stream', the same an error file error would, such
 * that `ferror(stream) != 0', and `clearerr(stream)' must be used if one wishes
 * to clear the error once again. */
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,__fseterr,(__FILE *__stream),(__stream))
#if defined(__CRT_HAVE___freadahead_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> __freadahead(3), __freadahead_unlocked(3)
 * Returns  the # of bytes pending to-be read from the given `stream's internal buffer.
 * Once this many bytes have been read (or `__fpurge(3)' is called), the next read will
 * query the stream's underlying read function (usually `read(2)') for more data.
 * NOTE: The function `__fpending(3)' can be used to query the # of modified bytes that
 *       are pending for write-back.
 * @return: * : The # of pending, unread bytes in the `stream's read-buffer. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),size_t,__NOTHROW_NCX,__freadahead,(__FILE __KOS_FIXED_CONST *__stream),__freadahead_unlocked,(__stream))
#elif defined(__CRT_HAVE___freadahead)
/* >> __freadahead(3), __freadahead_unlocked(3)
 * Returns  the # of bytes pending to-be read from the given `stream's internal buffer.
 * Once this many bytes have been read (or `__fpurge(3)' is called), the next read will
 * query the stream's underlying read function (usually `read(2)') for more data.
 * NOTE: The function `__fpending(3)' can be used to query the # of modified bytes that
 *       are pending for write-back.
 * @return: * : The # of pending, unread bytes in the `stream's read-buffer. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),size_t,__NOTHROW_NCX,__freadahead,(__FILE __KOS_FIXED_CONST *__stream),(__stream))
#elif defined(__CRT_HAVE___freadahead_unlocked)
/* >> __freadahead(3), __freadahead_unlocked(3)
 * Returns  the # of bytes pending to-be read from the given `stream's internal buffer.
 * Once this many bytes have been read (or `__fpurge(3)' is called), the next read will
 * query the stream's underlying read function (usually `read(2)') for more data.
 * NOTE: The function `__fpending(3)' can be used to query the # of modified bytes that
 *       are pending for write-back.
 * @return: * : The # of pending, unread bytes in the `stream's read-buffer. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),size_t,__NOTHROW_NCX,__freadahead,(__FILE __KOS_FIXED_CONST *__stream),__freadahead_unlocked,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE___freadahead_unlocked
/* >> __freadahead(3), __freadahead_unlocked(3)
 * Returns  the # of bytes pending to-be read from the given `stream's internal buffer.
 * Once this many bytes have been read (or `__fpurge(3)' is called), the next read will
 * query the stream's underlying read function (usually `read(2)') for more data.
 * NOTE: The function `__fpending(3)' can be used to query the # of modified bytes that
 *       are pending for write-back.
 * @return: * : The # of pending, unread bytes in the `stream's read-buffer. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),size_t,__NOTHROW_NCX,__freadahead_unlocked,(__FILE __KOS_FIXED_CONST *__stream),(__stream))
#elif defined(__CRT_HAVE___freadahead)
/* >> __freadahead(3), __freadahead_unlocked(3)
 * Returns  the # of bytes pending to-be read from the given `stream's internal buffer.
 * Once this many bytes have been read (or `__fpurge(3)' is called), the next read will
 * query the stream's underlying read function (usually `read(2)') for more data.
 * NOTE: The function `__fpending(3)' can be used to query the # of modified bytes that
 *       are pending for write-back.
 * @return: * : The # of pending, unread bytes in the `stream's read-buffer. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),size_t,__NOTHROW_NCX,__freadahead_unlocked,(__FILE __KOS_FIXED_CONST *__stream),__freadahead,(__stream))
#endif /* ... */
/* >> __freadptr(3)
 * Returns a pointer to the internal read-buffer of `stream', and set `*p_num_bytes'
 * to  the number of bytes which may be  read starting at the returned pointer. Note
 * that this function isn't thread-safe  unless the caller calls `flockfile(3)'  and
 * `funlockfile(3)' themselves.
 * Once the caller is done reading from `return', they should use `__freadptrinc(3)'
 * in order to advance the  file's read-pointer and to  mark consumed data as  read.
 * @param: p_num_bytes: Set to `__freadahead(stream)' when non-`NULL' is returned.
 * @return: * :   Pointer to a readable buffer of at least `*p_num_bytes' bytes
 * @return: NULL: The internal buffer of  `stream' is currently empty.  In
 *                this case, `*p_num_bytes' is left in an undefined state. */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,__freadptr,(__FILE __KOS_FIXED_CONST *__stream, size_t *__p_num_bytes),(__stream,__p_num_bytes))
/* >> __freadptrinc(3)
 * Consume `num_bytes' bytes from `stream's internal read-buffer. The caller  must
 * ensure that `num_bytes <= __freadahead(stream)'. Failure in doing so results in
 * undefined behavior. */
__CDECLARE_VOID_OPT(__ATTR_INOUT(1),__NOTHROW_NCX,__freadptrinc,(__FILE *__stream, size_t __num_bytes),(__stream,__num_bytes))

__SYSDECL_END
#endif /* __CC__ */

/* Never actually needed */
#ifndef enable_extended_FILE_stdio
#define enable_extended_FILE_stdio(fd, act) 0
#endif /* !enable_extended_FILE_stdio */

#endif /* !_STDIO_EXT_H */
