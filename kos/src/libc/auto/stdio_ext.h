/* HASH CRC-32:0xe103165f */
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
#ifndef GUARD_LIBC_AUTO_STDIO_EXT_H
#define GUARD_LIBC_AUTO_STDIO_EXT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stdio_ext.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> __fbufsize(3)
 * Returns the used buffer size of the given `stream' (s.a. `setvbuf(3)')
 * @return: * : Used buffer size of `stream' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd___fbufsize)(FILE __KOS_FIXED_CONST *stream);
/* >> __freading(3)
 * Returns  non-zero if the `stream' is read-only, or "the last operation
 * performed on `stream' was a read-operation". On KOS, this last part is
 * implemented such that we check for unsaved changes to `stream'. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd___freading)(FILE __KOS_FIXED_CONST *stream);
/* >> __fwriting(3)
 * Returns non-zero if the `stream'  is "write-only", or "the last  operation
 * performed on `stream' was a write-operation". On KOS, our stdio impl  does
 * not support write-only files (if reading isn't allowed, this will only  be
 * enforced on an fd-level by the kernel). Instead, we implement `__fwriting'
 * to return indicative of `stream' containing any unwritten changes. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd___fwriting)(FILE __KOS_FIXED_CONST *stream);
/* >> __freadable(3)
 * Returns non-zero if `stream'  allows for reading (s.a.  `fread(3)')
 * On  KOS, all stdio files can be  read from (except those opened for
 * file descriptors opened as `O_WRONLY', though in this case write(2)
 * is still attempted). As such, KOS  considers all stdio files to  be
 * readable, meaning that on KOS this function always returns `1'. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd___freadable)(FILE __KOS_FIXED_CONST *stream);
/* >> __fwritable(3)
 * Returns non-zero if `stream' is writable, that is: has been opened
 * with "w",  "r+", or  some similar  flag that  allows for  writing. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd___fwritable)(FILE __KOS_FIXED_CONST *stream);
/* >> __flbf(3)
 * Return  non-zero  if `stream'  is line-buffered.  (s.a. `_IOLBF')
 * Note  that on KOS, the line-buffered attribute of stdio files may
 * be determined  lazily, based  on  an underlying  file  descriptor
 * referring to a TTY. If this is the case, this function will  make
 * the appropriate call to `isatty(3)' and set the internal is-line-
 * buffered flag accordingly, before returning its state. */
INTDEF ATTR_PURE WUNUSED ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd___flbf)(FILE *stream);
/* >> __fpurge(3)
 * Discard all modified, but unwritten data from `stream', as  well
 * as  all unread data previously buffered, but not yet read. After
 * a call to this function, the next `fread(3)' or `fwrite(3)' will
 * start off from a blank state. */
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBDCALL libd___fpurge)(FILE *stream);
/* >> __fpending(3), __fpending_unlocked(3)
 * Returns the number of pending, but not-yet-written bytes of modified
 * file  data (s.a. `__fwriting(3)'). A call to `fflush(3)' can be used
 * to write all modified data to the system, and following such a call,
 * this function will return `0' until new unwritten data appears. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd___fpending)(FILE __KOS_FIXED_CONST *stream);
/* >> __fpending(3), __fpending_unlocked(3)
 * Returns the number of pending, but not-yet-written bytes of modified
 * file  data (s.a. `__fwriting(3)'). A call to `fflush(3)' can be used
 * to write all modified data to the system, and following such a call,
 * this function will return `0' until new unwritten data appears. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd___fpending_unlocked)(FILE __KOS_FIXED_CONST *stream);
/* >> __fsetlocking(3)
 * Set the locking type for `stream' to `type'. This affects all stdio functions
 * that aren't already lock-less by nature (iow: everything but `*_unlocked(3)')
 * @param: type: One of `FSETLOCKING_*', as defined in `<stdio_ext.h>'
 * @return: * : The locking type prior to this call (one of `FSETLOCKING_INTERNAL' or `FSETLOCKING_BYCALLER') */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd___fsetlocking)(FILE *stream, int type);
/* >> __fseterr(3)
 * Set the error indicator of `stream', the same an error file error would, such
 * that `ferror(stream) != 0', and `clearerr(stream)' must be used if one wishes
 * to clear the error once again. */
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBDCALL libd___fseterr)(FILE *stream);
/* >> __freadahead(3), __freadahead_unlocked(3)
 * Returns  the # of bytes pending to-be read from the given `stream's internal buffer.
 * Once this many bytes have been read (or `__fpurge(3)' is called), the next read will
 * query the stream's underlying read function (usually `read(2)') for more data.
 * NOTE: The function `__fpending(3)' can be used to query the # of modified bytes that
 *       are pending for write-back.
 * @return: * : The # of pending, unread bytes in the `stream's read-buffer. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd___freadahead)(FILE __KOS_FIXED_CONST *stream);
/* >> __freadahead(3), __freadahead_unlocked(3)
 * Returns  the # of bytes pending to-be read from the given `stream's internal buffer.
 * Once this many bytes have been read (or `__fpurge(3)' is called), the next read will
 * query the stream's underlying read function (usually `read(2)') for more data.
 * NOTE: The function `__fpending(3)' can be used to query the # of modified bytes that
 *       are pending for write-back.
 * @return: * : The # of pending, unread bytes in the `stream's read-buffer. */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) size_t NOTHROW_NCX(LIBDCALL libd___freadahead_unlocked)(FILE __KOS_FIXED_CONST *stream);
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
INTDEF WUNUSED ATTR_IN(1) char const *NOTHROW_NCX(LIBDCALL libd___freadptr)(FILE __KOS_FIXED_CONST *stream, size_t *p_num_bytes);
/* >> __freadptrinc(3)
 * Consume `num_bytes' bytes from `stream's internal read-buffer. The caller  must
 * ensure that `num_bytes <= __freadahead(stream)'. Failure in doing so results in
 * undefined behavior. */
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBDCALL libd___freadptrinc)(FILE *stream, size_t num_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_STDIO_EXT_H */
