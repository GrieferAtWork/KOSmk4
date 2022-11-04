/* HASH CRC-32:0x84d2186e */
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
#ifndef GUARD_LIBC_USER_STDIO_H
#define GUARD_LIBC_USER_STDIO_H 1

#include "../api.h"
#include "../auto/stdio.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stdio.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> rename(2)
 * Rename  a given file `oldname' to `newname_or_path', or in the event
 * that `newname_or_path' refers to a directory, place the file within. */
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_rename)(char const *oldname, char const *newname_or_path);
/* >> rename(2)
 * Rename  a given file `oldname' to `newname_or_path', or in the event
 * that `newname_or_path' refers to a directory, place the file within. */
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_RPC(LIBCCALL libc_rename)(char const *oldname, char const *newname_or_path);
/* >> tmpnam(3), tmpnam_r(3) */
INTDEF WUNUSED ATTR_OUT(1) char *NOTHROW_NCX(LIBDCALL libd_tmpnam)(char *buf);
/* >> tmpnam(3), tmpnam_r(3) */
INTDEF WUNUSED ATTR_OUT(1) char *NOTHROW_NCX(LIBCCALL libc_tmpnam)(char *buf);
/* >> fclose(3)
 * Close and destroy a given file `stream' */
INTDEF ATTR_INOUT(1) int (LIBCCALL libc_fclose)(FILE *__restrict stream) THROWS(...);
/* >> fflush(3)
 * Flush any unwritten data from `stream' to the underlying filesystem/TTY */
INTDEF int (LIBCCALL libc_fflush)(FILE *stream) THROWS(...);
/* >> setvbuf(3)
 * Set the buffer and buffer-mode to-be used by the given `stream'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc_setvbuf)(FILE *__restrict stream, char *__restrict buf, __STDC_INT_AS_UINT_T modes, size_t bufsize);
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
INTDEF ATTR_INOUT(1) int (LIBCCALL libc_fgetc)(FILE *__restrict stream) THROWS(...);
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
INTDEF ATTR_INOUT(2) int (LIBCCALL libc_fputc)(int ch, FILE *__restrict stream) THROWS(...);
/* >> ungetc(3)
 * Unget a single character byte of data previously returned by `getc()' */
INTDEF ATTR_INOUT(2) int NOTHROW_NCX(LIBCCALL libc_ungetc)(int ch, FILE *__restrict stream);
/* >> fread(3)
 * Read up to `elemsize * elemcount' bytes of data from `stream' into `buf' */
INTDEF WUNUSED ATTR_INOUT(4) ATTR_OUT_OPT(1) size_t (LIBCCALL libc_fread)(void *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* >> fwrite(3)
 * Write up to `elemsize * elemcount' bytes of data from `buf' into `stream' */
INTDEF ATTR_INOUT(4) ATTR_IN_OPT(1) size_t (LIBCCALL libc_fwrite)(void const *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
INTDEF ATTR_INOUT(1) int (LIBCCALL libc_fseek)(FILE *__restrict stream, long int off, int whence) THROWS(...);
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
INTDEF WUNUSED ATTR_INOUT(1) long int (LIBCCALL libc_ftell)(FILE *__restrict stream) THROWS(...);
/* >> rewind(3)
 * Rewind the current in-file position of `stream' to its starting position */
INTDEF ATTR_INOUT(1) void (LIBCCALL libc_rewind)(FILE *__restrict stream) THROWS(...);
/* >> clearerr(3)
 * Clear the error state of `stream', returning the stream to normal operations mode */
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBCCALL libc_clearerr)(FILE *__restrict stream);
/* >> feof(3)
 * Check if end-of-file has been reached in `stream' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBCCALL libc_feof)(FILE __KOS_FIXED_CONST *__restrict stream);
/* >> ferror(3)
 * Check if an I/O error occurred in `stream' */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBCCALL libc_ferror)(FILE __KOS_FIXED_CONST *__restrict stream);
/* >> tmpfile(3), tmpfile64(3)
 * Create and return a new file-stream for accessing a temporary file for reading/writing */
INTDEF WUNUSED FILE *NOTHROW_RPC(LIBCCALL libc_tmpfile)(void);
/* >> fopen(3), fopen64(3)
 * Create and return a new file-stream for accessing `filename' */
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) FILE *NOTHROW_RPC(LIBDCALL libd_fopen)(char const *__restrict filename, char const *__restrict modes);
/* >> fopen(3), fopen64(3)
 * Create and return a new file-stream for accessing `filename' */
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) FILE *NOTHROW_RPC(LIBCCALL libc_fopen)(char const *__restrict filename, char const *__restrict modes);
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_INOUT(3) FILE *NOTHROW_RPC(LIBDCALL libd_freopen)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_INOUT(3) FILE *NOTHROW_RPC(LIBCCALL libc_freopen)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
INTDEF ATTR_INOUT(1) ATTR_OUT(2) int (LIBCCALL libc_fgetpos)(FILE *__restrict stream, fpos_t *__restrict pos) THROWS(...);
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
INTDEF ATTR_IN(2) ATTR_INOUT(1) int (LIBCCALL libc_fsetpos)(FILE *__restrict stream, fpos_t const *__restrict pos) THROWS(...);
/* >> renameat(2) */
INTDEF ATTR_IN(2) ATTR_IN(4) int NOTHROW_RPC(LIBDCALL libd_renameat)(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path);
/* >> renameat(2) */
INTDEF ATTR_IN(2) ATTR_IN(4) int NOTHROW_RPC(LIBCCALL libc_renameat)(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path);
/* >> renameat2(2)
 * @param flags: Set of `0 | AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE |
 *                       AT_RENAME_WHITEOUT | AT_RENAME_MOVETODIR | AT_DOSPATH'
 * NOTE: For portability, use the following names:
 *   - `AT_RENAME_NOREPLACE' --> `RENAME_NOREPLACE'
 *   - `AT_RENAME_EXCHANGE'  --> `RENAME_EXCHANGE'
 *   - `AT_RENAME_WHITEOUT'  --> `RENAME_WHITEOUT' */
INTDEF ATTR_IN(2) ATTR_IN(4) int NOTHROW_RPC(LIBDCALL libd_renameat2)(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags);
/* >> renameat2(2)
 * @param flags: Set of `0 | AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE |
 *                       AT_RENAME_WHITEOUT | AT_RENAME_MOVETODIR | AT_DOSPATH'
 * NOTE: For portability, use the following names:
 *   - `AT_RENAME_NOREPLACE' --> `RENAME_NOREPLACE'
 *   - `AT_RENAME_EXCHANGE'  --> `RENAME_EXCHANGE'
 *   - `AT_RENAME_WHITEOUT'  --> `RENAME_WHITEOUT' */
INTDEF ATTR_IN(2) ATTR_IN(4) int NOTHROW_RPC(LIBCCALL libc_renameat2)(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags);
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
INTDEF int (LIBCCALL libc_fflush_unlocked)(FILE *stream) THROWS(...);
/* >> fread_unlocked(3)
 * Same as `fread()', but performs I/O without acquiring a lock to `stream' */
INTDEF WUNUSED ATTR_INOUT(4) ATTR_OUT_OPT(1) size_t (LIBCCALL libc_fread_unlocked)(void *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* >> fwrite_unlocked(3)
 * Same as `fwrite()', but performs I/O without acquiring a lock to `stream' */
INTDEF WUNUSED ATTR_INOUT(4) ATTR_IN_OPT(1) size_t (LIBCCALL libc_fwrite_unlocked)(void const *__restrict buf, size_t elemsize, size_t elemcount, FILE *__restrict stream) THROWS(...);
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
INTDEF ATTR_INOUT(1) int (LIBCCALL libc_fgetc_unlocked)(FILE *__restrict stream) THROWS(...);
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
INTDEF ATTR_INOUT(2) int (LIBCCALL libc_fputc_unlocked)(int ch, FILE *__restrict stream) THROWS(...);
/* >> tempnam(3) */
INTDEF ATTR_MALLOC WUNUSED char *NOTHROW_NCX(LIBCCALL libc_tempnam)(char const *dir, char const *pfx);
/* >> fdopen(3)
 * Open a new file stream by inheriting a given file descriptor `fd'
 * Note that upon success (`return != NULL'), the given `fd' will be
 * `close(2)'d once `fclose(return)' is called. */
INTDEF WUNUSED ATTR_IN(2) FILE *NOTHROW_NCX(LIBCCALL libc_fdopen)(fd_t fd, char const *__restrict modes);
/* >> fileno(3)
 * Return the underlying file descriptor number used by `stream' */
INTDEF WUNUSED ATTR_INOUT(1) fd_t NOTHROW_NCX(LIBCCALL libc_fileno)(FILE *__restrict stream);
/* >> flockfile(3)
 * Acquire a lock to `stream' and block until doing so succeeds */
INTDEF ATTR_INOUT(1) void NOTHROW_RPC(LIBCCALL libc_flockfile)(FILE *__restrict stream);
/* >> funlockfile(3)
 * Release a previously acquired lock from `stream' */
INTDEF void NOTHROW_NCX(LIBCCALL libc_funlockfile)(FILE *__restrict stream);
/* >> ftrylockfile(3)
 * Try to acquire a lock to `stream'
 * @return: == 0 : Lock successfully acquired
 * @return: != 0 : Failed to acquire lock */
INTDEF WUNUSED ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc_ftrylockfile)(FILE *__restrict stream);
/* >> popen(3)
 * Open and return a new process I/O stream for executing `command'
 * @param: command: The command to execute (s.a. `shexec(3)')
 * @param: modes:   One of "r", "w", "re" or "we" ('e' sets  O_CLOEXEC
 *                  for the internal file descriptor within the parent
 *                  process) */
INTDEF WUNUSED ATTR_IN(2) ATTR_IN_OPT(1) FILE *NOTHROW_RPC(LIBCCALL libc_popen)(char const *command, char const *modes);
/* >> pclose(3)
 * Close a process I/O file `stream' (s.a. `popen(3)') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_pclose)(FILE *stream);
/* >> popenve(3)
 * Similar to `popen(3)', but rather than running `shexec(command)', this
 * function will `execve(path, argv, envp)'. The returned FILE must still
 * be closed using `pclose(3)', rather than `fclose(3)' */
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) ATTR_IN(4) FILE *NOTHROW_RPC(LIBCCALL libc_popenve)(char const *path, __TARGV, __TENVP, char const *modes);
/* >> fcloseall(3)
 * Close all opened files */
INTDEF int (LIBCCALL libc_fcloseall)(void) THROWS(...);
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
INTDEF ATTR_INOUT(1) int (LIBCCALL libc_fseeko)(FILE *__restrict stream, off_t off, int whence) THROWS(...);
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
INTDEF WUNUSED ATTR_INOUT(1) off_t (LIBCCALL libc_ftello)(FILE *__restrict stream) THROWS(...);
/* >> tmpfile(3), tmpfile64(3)
 * Create and return a new file-stream for accessing a temporary file for reading/writing */
INTDEF WUNUSED FILE *NOTHROW_RPC(LIBCCALL libc_tmpfile64)(void);
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
INTDEF ATTR_INOUT(1) int (LIBCCALL libc_fseeko64)(FILE *__restrict stream, off64_t off, int whence) THROWS(...);
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
INTDEF WUNUSED ATTR_INOUT(1) off64_t (LIBCCALL libc_ftello64)(FILE *__restrict stream) THROWS(...);
/* >> fopen(3), fopen64(3)
 * Create and return a new file-stream for accessing `filename' */
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) FILE *NOTHROW_RPC(LIBDCALL libd_fopen64)(char const *__restrict filename, char const *__restrict modes);
/* >> fopen(3), fopen64(3)
 * Create and return a new file-stream for accessing `filename' */
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) FILE *NOTHROW_RPC(LIBCCALL libc_fopen64)(char const *__restrict filename, char const *__restrict modes);
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_INOUT(3) FILE *NOTHROW_RPC(LIBDCALL libd_freopen64)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_INOUT(3) FILE *NOTHROW_RPC(LIBCCALL libc_freopen64)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
INTDEF ATTR_INOUT(1) ATTR_OUT(2) int (LIBCCALL libc_fgetpos64)(FILE *__restrict stream, fpos64_t *__restrict pos) THROWS(...);
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
INTDEF ATTR_IN(2) ATTR_INOUT(1) int (LIBCCALL libc_fsetpos64)(FILE *__restrict stream, fpos64_t const *__restrict pos) THROWS(...);
/* >> file_printer(3)
 * For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
INTDEF ATTR_INS(2, 3) NONNULL((1)) ssize_t (__FORMATPRINTER_CC libc_file_printer)(void *arg, char const *__restrict data, size_t datalen) THROWS(...);
/* >> file_printer_unlocked(3)
 * Same as `file_printer()', but performs I/O without acquiring a lock to `(FILE *)arg' */
INTDEF ATTR_INS(2, 3) NONNULL((1)) ssize_t (__FORMATPRINTER_CC libc_file_printer_unlocked)(void *arg, char const *__restrict data, size_t datalen) THROWS(...);
/* >> fdreopen(3), fdreopen_unlocked(3)
 * Re-open the given `stream' as a file-stream for accessing `fd' */
INTDEF ATTR_IN(2) ATTR_INOUT(3) FILE *NOTHROW_RPC(LIBCCALL libc_fdreopen)(fd_t fd, char const *__restrict modes, FILE *__restrict stream);
/* >> fdreopen(3), fdreopen_unlocked(3)
 * Re-open the given `stream' as a file-stream for accessing `fd' */
INTDEF ATTR_IN(2) ATTR_INOUT(3) FILE *NOTHROW_RPC(LIBCCALL libc_fdreopen_unlocked)(fd_t fd, char const *__restrict modes, FILE *__restrict stream);
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_INOUT(3) FILE *NOTHROW_RPC(LIBDCALL libd_freopen_unlocked)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_INOUT(3) FILE *NOTHROW_RPC(LIBCCALL libc_freopen_unlocked)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_INOUT(3) FILE *NOTHROW_RPC(LIBDCALL libd_freopen64_unlocked)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_INOUT(3) FILE *NOTHROW_RPC(LIBCCALL libc_freopen64_unlocked)(char const *__restrict filename, char const *__restrict modes, FILE *__restrict stream);
INTDEF ATTR_INOUT(1) int (LIBCCALL libc_fseek_unlocked)(FILE *__restrict stream, long int off, int whence) THROWS(...);
INTDEF WUNUSED ATTR_INOUT(1) long int (LIBCCALL libc_ftell_unlocked)(FILE *__restrict stream) THROWS(...);
INTDEF ATTR_INOUT(1) int (LIBCCALL libc_fseeko_unlocked)(FILE *__restrict stream, off_t off, int whence) THROWS(...);
INTDEF WUNUSED ATTR_INOUT(1) off_t (LIBCCALL libc_ftello_unlocked)(FILE *__restrict stream) THROWS(...);
INTDEF int (LIBCCALL libc_flushall_unlocked)(void) THROWS(...);
INTDEF ATTR_INOUT(1) ATTR_OUT(2) int (LIBCCALL libc_fgetpos_unlocked)(FILE *__restrict stream, fpos_t *__restrict pos) THROWS(...);
INTDEF ATTR_IN(2) ATTR_INOUT(1) int (LIBCCALL libc_fsetpos_unlocked)(FILE *__restrict stream, fpos_t const *__restrict pos) THROWS(...);
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc_setvbuf_unlocked)(FILE *__restrict stream, char *__restrict buf, __STDC_INT_AS_UINT_T modes, size_t bufsize);
INTDEF ATTR_INOUT(2) int NOTHROW_NCX(LIBCCALL libc_ungetc_unlocked)(int ch, FILE *__restrict stream);
INTDEF ATTR_INOUT(1) void (LIBCCALL libc_rewind_unlocked)(FILE *__restrict stream) THROWS(...);
INTDEF WUNUSED ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc_fisatty)(FILE *__restrict stream);
/* >> fftruncate(3)
 * Truncate the given file `stream' to a length of `length' */
INTDEF ATTR_INOUT(1) int (LIBCCALL libc_fftruncate)(FILE *__restrict stream, __PIO_OFFSET length) THROWS(...);
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
INTDEF ATTR_INOUT(1) int (LIBCCALL libc_fftruncate_unlocked)(FILE *__restrict stream, __PIO_OFFSET length) THROWS(...);
INTDEF ATTR_INOUT(1) int (LIBCCALL libc_fseeko64_unlocked)(FILE *__restrict stream, off64_t off, int whence) THROWS(...);
INTDEF WUNUSED ATTR_INOUT(1) off64_t (LIBCCALL libc_ftello64_unlocked)(FILE *__restrict stream) THROWS(...);
INTDEF ATTR_INOUT(1) ATTR_OUT(2) int (LIBCCALL libc_fgetpos64_unlocked)(FILE *__restrict stream, fpos64_t *__restrict pos) THROWS(...);
INTDEF ATTR_IN(2) ATTR_INOUT(1) int (LIBCCALL libc_fsetpos64_unlocked)(FILE *__restrict stream, fpos64_t const *__restrict pos) THROWS(...);
/* >> fftruncate64(3)
 * Truncate the given file `stream' to a length of `length' */
INTDEF ATTR_INOUT(1) int (LIBCCALL libc_fftruncate64)(FILE *__restrict stream, __PIO_OFFSET64 length) THROWS(...);
/* >> fftruncate64_unlocked(3)
 * Truncate the given file `stream' to a length of `length' */
INTDEF ATTR_INOUT(1) int (LIBCCALL libc_fftruncate64_unlocked)(FILE *__restrict stream, __PIO_OFFSET64 length) THROWS(...);
/* >> fgetln(3)
 * A slightly more convenient (but way less portable) alternative to `fgets(3)'
 * This function automatically malloc's a  buffer of sufficient length for  the
 * next line in the given `stream', and stores its length in `*lenp'
 * NOTE: KOS adds the following extensions to this function:
 *  - We guaranty that "return[*lenp] == '\0'" upon a non-NULL return
 *  - You may pass `lenp == NULL', which simply ignores that argument
 * @return: NULL: The EOF flag of `stream' is set (fix this with `clearerr(3)'),
 *                or the underlying file has been fully read.
 * @return: * :   Pointer to an  automatically malloc'd  buffer (to-be  freed
 *                by  fclose(3)  once you  call  that function  on  the given
 *                `stream'). The buffer is re-used in subsequence invocations
 *                of this function, and documentation states that it may also
 *                be invalidated during any  other I/O operation relating  to
 *                `stream', though this isn't the case under KOS. */
INTDEF WUNUSED ATTR_INOUT(1) ATTR_OUT_OPT(2) char *NOTHROW_NCX(LIBCCALL libc_fgetln)(FILE *__restrict stream, size_t *__restrict lenp);
/* >> funopen2(3), funopen2_64(3) */
INTDEF WUNUSED FILE *NOTHROW_NCX(LIBCCALL libc_funopen2)(void const *cookie, ssize_t (LIBKCALL *readfn)(void *cookie, void *buf, size_t num_bytes), ssize_t (LIBKCALL *writefn)(void *cookie, void const *buf, size_t num_bytes), off_t (LIBKCALL *seekfn)(void *cookie, off_t off, int whence), int (LIBKCALL *flushfn)(void *cookie), int (LIBKCALL *closefn)(void *cookie));
/* >> funopen2(3), funopen2_64(3) */
INTDEF WUNUSED FILE *NOTHROW_NCX(LIBCCALL libc_funopen2_64)(void const *cookie, ssize_t (LIBKCALL *readfn)(void *cookie, void *buf, size_t num_bytes), ssize_t (LIBKCALL *writefn)(void *cookie, void const *buf, size_t num_bytes), off64_t (LIBKCALL *seekfn)(void *cookie, off64_t off, int whence), int (LIBKCALL *flushfn)(void *cookie), int (LIBKCALL *closefn)(void *cookie));
INTDEF int (LIBCCALL libc__flushall)(void) THROWS(...);
INTDEF int NOTHROW_RPC(LIBCCALL libc__rmtmp)(void);
INTDEF ATTR_INOUT(1) int (LIBCCALL libc__filbuf)(FILE *__restrict stream) THROWS(...);
INTDEF ATTR_INOUT(2) int (LIBCCALL libc__flsbuf)(int ch, FILE *__restrict stream) THROWS(...);
/* >> _get_printf_count_output(3), _set_printf_count_output(3)
 * Enable or disable use of '%n' in printf-style format strings. */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__get_printf_count_output)(void);
/* >> _get_printf_count_output(3), _set_printf_count_output(3)
 * Enable or disable use of '%n' in printf-style format strings. */
INTDEF int NOTHROW_NCX(LIBCCALL libc__set_printf_count_output)(int val);
INTDEF WUNUSED uint32_t NOTHROW_NCX(LIBCCALL libc__get_output_format)(void);
INTDEF uint32_t NOTHROW_NCX(LIBCCALL libc__set_output_format)(uint32_t format);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_STDIO_H */
