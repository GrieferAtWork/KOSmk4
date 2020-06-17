/* HASH CRC-32:0x7fec3593 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_STDIO_C
#define GUARD_LIBC_AUTO_DOSABI_STDIO_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/stdio.h"

DECL_BEGIN

/* Remove a file or directory `FILENAME' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_remove)(char const *filename) {
	return libc_remove(filename);
}
/* Rename a given file `OLDNAME' to `NEWNAME_OR_PATH', or in the event
 * that `NEWNAME_OR_PATH' refers to a directory, place the file within. */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_rename)(char const *oldname,
                                  char const *newname_or_path) {
	return libc_rename(oldname, newname_or_path);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_tmpnam)(char *buf) {
	return libc_tmpnam(buf);
}
/* Close and destroy a given file `STREAM' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") NONNULL((1)) int
(LIBDCALL libd_fclose)(FILE *__restrict stream) THROWS(...) {
	return libc_fclose(stream);
}
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.write.utility") int
(LIBDCALL libd_fflush)(FILE *stream) THROWS(...) {
	return libc_fflush(stream);
}
/* Alias for `setvbuf(STREAM, buf, _IOFBF, BUFSIZ)' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.utility") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd_setbuf)(FILE *__restrict stream,
                                  char *buf) {
	libc_setbuf(stream, buf);
}
/* Set the buffer and buffer-mode to-be used by the given `STREAM'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.utility") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_setvbuf)(FILE *__restrict stream,
                                   char *__restrict buf,
                                   int modes,
                                   size_t bufsize) {
	return libc_setvbuf(stream, buf, modes, bufsize);
}
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.getc") NONNULL((1)) int
(LIBDCALL libd_fgetc)(FILE *__restrict stream) THROWS(...) {
	return libc_fgetc(stream);
}
/* Write a single character `CH' to `STREAM' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.write.putc") NONNULL((2)) int
(LIBDCALL libd_fputc)(int ch,
                      FILE *__restrict stream) THROWS(...) {
	return libc_fputc(ch, stream);
}
/* Alias for `fputc(CH, stdout)' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.write.putc") int
(LIBDCALL libd_putchar)(int ch) THROWS(...) {
	return libc_putchar(ch);
}
/* Read up to `BUFSIZE - 1' bytes of data from `STREAM', storing them into `BUF' stopped when
 * the buffer is full or a line-feed was read (in this case, the line-feed is also written to `BUF')
 * Afterwards, append a trailing NUL-character and re-return `BUF', or return `NULL' if an error occurred. */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.read") WUNUSED NONNULL((1, 3)) char *
(LIBDCALL libd_fgets)(char *__restrict buf,
                      __STDC_INT_AS_SIZE_T bufsize,
                      FILE *__restrict stream) THROWS(...) {
	return libc_fgets(buf, bufsize, stream);
}
/* Print a given string `STR' to `STREAM'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.write.write") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(LIBDCALL libd_fputs)(char const *__restrict str,
                      FILE *__restrict stream) THROWS(...) {
	return libc_fputs(str, stream);
}
/* Print a given string `STR', followed by a line-feed to `STDOUT' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.write.write") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBDCALL libd_puts)(char const *__restrict string) THROWS(...) {
	return libc_puts(string);
}
/* Unget a single character byte of data previously returned by `getc()' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.getc") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_ungetc)(int ch,
                                  FILE *__restrict stream) {
	return libc_ungetc(ch, stream);
}
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.read") WUNUSED NONNULL((1, 4)) size_t
(LIBDCALL libd_fread)(void *__restrict buf,
                      size_t elemsize,
                      size_t elemcount,
                      FILE *__restrict stream) THROWS(...) {
	return libc_fread(buf, elemsize, elemcount, stream);
}
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.write.write") NONNULL((1, 4)) size_t
(LIBDCALL libd_fwrite)(void const *__restrict buf,
                       size_t elemsize,
                       size_t elemcount,
                       FILE *__restrict stream) THROWS(...) {
	return libc_fwrite(buf, elemsize, elemcount, stream);
}
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.seek.seek") NONNULL((1)) int
(LIBDCALL libd_fseek)(FILE *__restrict stream,
                      long int off,
                      int whence) THROWS(...) {
	return libc_fseek(stream, off, whence);
}
/* Return the current in-file position of `STREAM' as a byte-offet from the start of the file */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.seek.seek") WUNUSED NONNULL((1)) long int
(LIBDCALL libd_ftell)(FILE *__restrict stream) THROWS(...) {
	return libc_ftell(stream);
}
/* Rewind the current in-file position of `STREAM' to its starting position */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.seek.utility") NONNULL((1)) void
(LIBDCALL libd_rewind)(FILE *__restrict stream) THROWS(...) {
	libc_rewind(stream);
}
/* Clear the error state of `STREAM', returning the stream to normal operations mode */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd_clearerr)(FILE *__restrict stream) {
	libc_clearerr(stream);
}
/* Check if end-of-file has been reached in `STREAM' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.utility") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_feof)(FILE __KOS_FIXED_CONST *__restrict stream) {
	return libc_feof(stream);
}
/* Check if an I/O error occurred in `STREAM' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.utility") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_ferror)(FILE __KOS_FIXED_CONST *__restrict stream) {
	return libc_ferror(stream);
}
/* Print a given `MESSAGE' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
INTERN ATTR_SECTION(".text.crt.dos.errno.utility") void
NOTHROW_RPC(LIBDCALL libd_perror)(char const *message) {
	libc_perror(message);
}
/* Create and return a new file-stream for accessing `FILENAME' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_RPC(LIBDCALL libd_fopen)(char const *__restrict filename,
                                 char const *__restrict modes) {
	return libc_fopen(filename, modes);
}
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") NONNULL((1, 2, 3)) FILE *
NOTHROW_RPC(LIBDCALL libd_freopen)(char const *__restrict filename,
                                   char const *__restrict modes,
                                   FILE *__restrict stream) {
	return libc_freopen(filename, modes, stream);
}
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.seek.pos") NONNULL((1, 2)) int
(LIBDCALL libd_fgetpos)(FILE *__restrict stream,
                        fpos_t *__restrict pos) THROWS(...) {
	return libc_fgetpos(stream, pos);
}
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.seek.pos") NONNULL((1, 2)) int
(LIBDCALL libd_fsetpos)(FILE *__restrict stream,
                        fpos_t const *__restrict pos) THROWS(...) {
	return libc_fsetpos(stream, pos);
}
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.write.printf") ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(LIBDCALL libd_vfprintf)(FILE *__restrict stream,
                         char const *__restrict format,
                         va_list args) THROWS(...) {
	return libc_vfprintf(stream, format, args);
}
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.write.printf") ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd_fprintf)(FILE *__restrict stream,
                         char const *__restrict format,
                         ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfprintf(stream, format, args);
	va_end(args);
	return result;
}
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.write.printf") ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBDCALL libd_vprintf)(char const *__restrict format,
                        va_list args) THROWS(...) {
	return libc_vprintf(format, args);
}
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.write.printf") ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd_printf)(char const *__restrict format,
                        ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vprintf(format, args);
	va_end(args);
	return result;
}
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vfscanf)(FILE *__restrict stream,
                        char const *__restrict format,
                        va_list args) THROWS(...) {
	return libc_vfscanf(stream, format, args);
}
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vscanf)(char const *__restrict format,
                       va_list args) THROWS(...) {
	return libc_vscanf(format, args);
}
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_fscanf)(FILE *__restrict stream,
                        char const *__restrict format,
                        ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfscanf(stream, format, args);
	va_end(args);
	return result;
}
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_scanf)(char const *__restrict format,
                       ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vscanf(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.read") WUNUSED ATTR_DEPRECATED("No buffer size checks (use `fgets\' instead)") NONNULL((1)) char *
(LIBDCALL libd_gets)(char *__restrict buf) THROWS(...) {
	return libc_gets(buf);
}
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.scanf") WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd_vsscanf)(char const *__restrict input,
                                   char const *__restrict format,
                                   va_list args) {
	return libc_vsscanf(input, format, args);
}
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.scanf") ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd_sscanf)(char const *__restrict input,
                                   char const *__restrict format,
                                   ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vsscanf(input, format, args);
	va_end(args);
	return result;
}
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd_vsprintf)(char *__restrict dest,
                                    char const *__restrict format,
                                    va_list args) {
	return libc_vsprintf(dest, format, args);
}
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd_sprintf)(char *__restrict buf,
                                    char const *__restrict format,
                                    ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vsprintf(buf, format, args);
	va_end(args);
	return result;
}
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd_vsnprintf)(char *__restrict buf,
                                     size_t buflen,
                                     char const *__restrict format,
                                     va_list args) {
	return libc_vsnprintf(buf, buflen, format, args);
}
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd_snprintf)(char *__restrict buf,
                                     size_t buflen,
                                     char const *__restrict format,
                                     ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vsnprintf(buf, buflen, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.io.write") ATTR_LIBC_PRINTF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBDCALL libd_vdprintf)(fd_t fd,
                                    char const *__restrict format,
                                    va_list args) {
	return libc_vdprintf(fd, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.io.write") ATTR_LIBC_PRINTF(2, 3) NONNULL((2)) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(VLIBDCALL libd_dprintf)(fd_t fd,
                                    char const *__restrict format,
                                    ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vdprintf(fd, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2, 4)) int
NOTHROW_RPC(LIBDCALL libd_renameat)(fd_t oldfd,
                                    char const *oldname,
                                    fd_t newfd,
                                    char const *newname_or_path) {
	return libc_renameat(oldfd, oldname, newfd, newname_or_path);
}
/* Remove a file or directory `FILENAME' relative to a given base directory `DIRFD' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_removeat)(fd_t dirfd,
                                    char const *filename) {
	return libc_removeat(dirfd, filename);
}
/* @param flags: Set of `0 | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2, 4)) int
NOTHROW_RPC(LIBDCALL libd_frenameat)(fd_t oldfd,
                                     char const *oldname,
                                     fd_t newfd,
                                     char const *newname_or_path,
                                     atflag_t flags) {
	return libc_frenameat(oldfd, oldname, newfd, newname_or_path, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_tmpnam_r)(char *buf) {
	return libc_tmpnam_r(buf);
}
/* Specify the location and size for the buffer to-be used by `STREAM' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.utility") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd_setbuffer)(FILE *__restrict stream,
                                     char *buf,
                                     size_t bufsize) {
	libc_setbuffer(stream, buf, bufsize);
}
/* Change the given `STREAM' to become line-buffered */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.utility") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd_setlinebuf)(FILE *__restrict stream) {
	libc_setlinebuf(stream);
}
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.write.utility") int
(LIBDCALL libd_fflush_unlocked)(FILE *stream) THROWS(...) {
	return libc_fflush_unlocked(stream);
}
/* Same as `fread()', but performs I/O without acquiring a lock to `STREAM' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.read") WUNUSED NONNULL((1, 4)) size_t
(LIBDCALL libd_fread_unlocked)(void *__restrict buf,
                               size_t elemsize,
                               size_t elemcount,
                               FILE *__restrict stream) THROWS(...) {
	return libc_fread_unlocked(buf, elemsize, elemcount, stream);
}
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.write.write") WUNUSED NONNULL((1, 4)) size_t
(LIBDCALL libd_fwrite_unlocked)(void const *__restrict buf,
                                size_t elemsize,
                                size_t elemcount,
                                FILE *__restrict stream) THROWS(...) {
	return libc_fwrite_unlocked(buf, elemsize, elemcount, stream);
}
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.getc") NONNULL((1)) int
(LIBDCALL libd_fgetc_unlocked)(FILE *__restrict stream) THROWS(...) {
	return libc_fgetc_unlocked(stream);
}
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.write.putc") NONNULL((2)) int
(LIBDCALL libd_fputc_unlocked)(int ch,
                               FILE *__restrict stream) THROWS(...) {
	return libc_fputc_unlocked(ch, stream);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") ATTR_MALLOC WUNUSED char *
NOTHROW_NCX(LIBDCALL libd_tempnam)(char const *dir,
                                   char const *pfx) {
	return libc_tempnam(dir, pfx);
}
/* Open a new file stream by inheriting a given file descriptor `FD'
 * Note that upon success (`return != NULL'), the given `FD'
 * will be `close()'d once `fclose(return)' is called */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.utility") WUNUSED NONNULL((2)) FILE *
NOTHROW_NCX(LIBDCALL libd_fdopen)(fd_t fd,
                                  char const *__restrict modes) {
	return libc_fdopen(fd, modes);
}
/* Return the underlying file descriptor number used by `STREAM' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.utility") WUNUSED NONNULL((1)) fd_t
NOTHROW_NCX(LIBDCALL libd_fileno)(FILE *__restrict stream) {
	return libc_fileno(stream);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") WUNUSED NONNULL((1, 3)) FILE *
NOTHROW_NCX(LIBDCALL libd_fmemopen)(void *mem,
                                    size_t len,
                                    char const *modes) {
	return libc_fmemopen(mem, len, modes);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") WUNUSED FILE *
NOTHROW_NCX(LIBDCALL libd_open_memstream)(char **bufloc,
                                          size_t *sizeloc) {
	return libc_open_memstream(bufloc, sizeloc);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.read") WUNUSED NONNULL((1, 2, 4)) ssize_t
(LIBDCALL libd_getdelim)(char **__restrict lineptr,
                         size_t *__restrict pcount,
                         int delimiter,
                         FILE *__restrict stream) THROWS(...) {
	return libc_getdelim(lineptr, pcount, delimiter, stream);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.read") WUNUSED NONNULL((1, 2, 3)) ssize_t
(LIBDCALL libd_getline)(char **__restrict lineptr,
                        size_t *__restrict pcount,
                        FILE *__restrict stream) THROWS(...) {
	return libc_getline(lineptr, pcount, stream);
}
/* Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.write.putc") int
(LIBDCALL libd_putchar_unlocked)(int ch) THROWS(...) {
	return libc_putchar_unlocked(ch);
}
/* Acquire a lock to `STREAM' and block until doing so succeeds */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.utility") NONNULL((1)) void
NOTHROW_RPC(LIBDCALL libd_flockfile)(FILE *__restrict stream) {
	libc_flockfile(stream);
}
/* Release a previously acquired lock from `STREAM' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.utility") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd_funlockfile)(FILE *__restrict stream) {
	libc_funlockfile(stream);
}
/* Try to acquire a lock to `STREAM' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.utility") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_ftrylockfile)(FILE *__restrict stream) {
	return libc_ftrylockfile(stream);
}
/* Return the name of the current user (`getpwuid(geteuid())'), storing
 * that name in `S'. When `S' is NULL, a static buffer is used instead */
INTERN ATTR_SECTION(".text.crt.dos.io.tty") char *
NOTHROW_NCX(LIBDCALL libd_cuserid)(char *s) {
	return libc_cuserid(s);
}
/* Open and return a new process I/O stream for executing `COMMAND' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_RPC(LIBDCALL libd_popen)(char const *command,
                                 char const *modes) {
	return libc_popen(command, modes);
}
/* Close a process I/O file `STREAM' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pclose)(FILE *stream) {
	return libc_pclose(stream);
}
/* Similar to `getc()', but read 2 bytes */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.getc") NONNULL((1)) int
(LIBDCALL libd_getw)(FILE *__restrict stream) THROWS(...) {
	return libc_getw(stream);
}
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.write.putc") NONNULL((2)) int
(LIBDCALL libd_putw)(int w,
                     FILE *__restrict stream) THROWS(...) {
	return libc_putw(w, stream);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") WUNUSED NONNULL((2)) FILE *
NOTHROW_NCX(LIBDCALL libd_fopencookie)(void *__restrict magic_cookie,
                                       char const *__restrict modes,
                                       cookie_io_functions_t io_funcs) {
	return libc_fopencookie(magic_cookie, modes, io_funcs);
}
/* Same as `fgets()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.read") WUNUSED NONNULL((1, 3)) char *
(LIBDCALL libd_fgets_unlocked)(char *__restrict buf,
                               __STDC_INT_AS_SIZE_T bufsize,
                               FILE *__restrict stream) THROWS(...) {
	return libc_fgets_unlocked(buf, bufsize, stream);
}
/* Same as `fputs()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.write.write") NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_fputs_unlocked)(char const *__restrict string,
                               FILE *__restrict stream) THROWS(...) {
	return libc_fputs_unlocked(string, stream);
}
INTERN ATTR_SECTION(".text.crt.dos.obstack") ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_obstack_vprintf)(struct obstack *__restrict obstack_,
                                           char const *__restrict format,
                                           va_list args) {
	return libc_obstack_vprintf(obstack_, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.obstack") ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(VLIBDCALL libd_obstack_printf)(struct obstack *__restrict obstack_,
                                           char const *__restrict format,
                                           ...) {
	int result;
	va_list args;
	va_start(args, format);
	result = libc_obstack_vprintf(obstack_, format, args);
	va_end(args);
	return result;
}
/* Change the current in-file position of `STREAM' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.seek.seek") NONNULL((1)) int
(LIBDCALL libd_fseeko)(FILE *__restrict stream,
                       off_t off,
                       int whence) THROWS(...) {
	return libc_fseeko(stream, off, whence);
}
/* Return the current in-file position of `STREAM' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.seek.seek") WUNUSED NONNULL((1)) off_t
(LIBDCALL libd_ftello)(FILE *__restrict stream) THROWS(...) {
	return libc_ftello(stream);
}
/* 64-bit variant of `fseeko' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.seek.seek") NONNULL((1)) int
(LIBDCALL libd_fseeko64)(FILE *__restrict stream,
                         off64_t off,
                         int whence) THROWS(...) {
	return libc_fseeko64(stream, off, whence);
}
/* 64-bit variant of `ftello' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.seek.seek") WUNUSED NONNULL((1)) off64_t
(LIBDCALL libd_ftello64)(FILE *__restrict stream) THROWS(...) {
	return libc_ftello64(stream);
}
/* 64-bit variant of `fopen' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_RPC(LIBDCALL libd_fopen64)(char const *__restrict filename,
                                   char const *__restrict modes) {
	return libc_fopen64(filename, modes);
}
/* 64-bit variant of `freopen' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") NONNULL((1, 2, 3)) FILE *
NOTHROW_RPC(LIBDCALL libd_freopen64)(char const *__restrict filename,
                                     char const *__restrict modes,
                                     FILE *__restrict stream) {
	return libc_freopen64(filename, modes, stream);
}
/* 64-bit variant of `fgetpos' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.seek.pos") NONNULL((1, 2)) int
(LIBDCALL libd_fgetpos64)(FILE *__restrict stream,
                          fpos64_t *__restrict pos) THROWS(...) {
	return libc_fgetpos64(stream, pos);
}
/* 64-bit variant of `fsetpos' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.seek.pos") NONNULL((1, 2)) int
(LIBDCALL libd_fsetpos64)(FILE *__restrict stream,
                          fpos64_t const *__restrict pos) THROWS(...) {
	return libc_fsetpos64(stream, pos);
}
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.write.write") NONNULL((1, 2)) ssize_t
(LIBDCALL libd_file_printer)(void *arg,
                             char const *__restrict data,
                             size_t datalen) THROWS(...) {
	return libc_file_printer(arg, data, datalen);
}
/* Same as `file_printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.write.write") NONNULL((1, 2)) ssize_t
(LIBDCALL libd_file_printer_unlocked)(void *arg,
                                      char const *__restrict data,
                                      size_t datalen) THROWS(...) {
	return libc_file_printer_unlocked(arg, data, datalen);
}
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
INTERN ATTR_SECTION(".text.crt.dos.heap.strdup") WUNUSED ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd_vasprintf)(char **__restrict pstr,
                                     char const *__restrict format,
                                     va_list args) {
	return libc_vasprintf(pstr, format, args);
}
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
INTERN ATTR_SECTION(".text.crt.dos.heap.strdup") WUNUSED ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd_asprintf)(char **__restrict pstr,
                                     char const *__restrict format,
                                     ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vasprintf(pstr, format, args);
	va_end(args);
	return result;
}
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") NONNULL((2, 3)) FILE *
NOTHROW_RPC(LIBDCALL libd_fdreopen)(fd_t fd,
                                    char const *__restrict modes,
                                    FILE *__restrict stream) {
	return libc_fdreopen(fd, modes, stream);
}
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.access") NONNULL((2, 3)) FILE *
NOTHROW_RPC(LIBDCALL libd_fdreopen_unlocked)(fd_t fd,
                                             char const *__restrict modes,
                                             FILE *__restrict stream) {
	return libc_fdreopen_unlocked(fd, modes, stream);
}
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.access") NONNULL((1, 2, 3)) FILE *
NOTHROW_RPC(LIBDCALL libd_freopen_unlocked)(char const *__restrict filename,
                                            char const *__restrict modes,
                                            FILE *__restrict stream) {
	return libc_freopen_unlocked(filename, modes, stream);
}
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.access") NONNULL((1, 2, 3)) FILE *
NOTHROW_RPC(LIBDCALL libd_freopen64_unlocked)(char const *__restrict filename,
                                              char const *__restrict modes,
                                              FILE *__restrict stream) {
	return libc_freopen64_unlocked(filename, modes, stream);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.seek.seek") NONNULL((1)) int
(LIBDCALL libd_fseek_unlocked)(FILE *__restrict stream,
                               long int off,
                               int whence) THROWS(...) {
	return libc_fseek_unlocked(stream, off, whence);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.seek.seek") NONNULL((1)) long int
(LIBDCALL libd_ftell_unlocked)(FILE *__restrict stream) THROWS(...) {
	return libc_ftell_unlocked(stream);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.seek.seek") NONNULL((1)) int
(LIBDCALL libd_fseeko_unlocked)(FILE *__restrict stream,
                                off_t off,
                                int whence) THROWS(...) {
	return libc_fseeko_unlocked(stream, off, whence);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.seek.seek") NONNULL((1)) off_t
(LIBDCALL libd_ftello_unlocked)(FILE *__restrict stream) THROWS(...) {
	return libc_ftello_unlocked(stream);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.seek.pos") NONNULL((1, 2)) int
(LIBDCALL libd_fgetpos_unlocked)(FILE *__restrict stream,
                                 fpos_t *__restrict pos) THROWS(...) {
	return libc_fgetpos_unlocked(stream, pos);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.seek.pos") NONNULL((1, 2)) int
(LIBDCALL libd_fsetpos_unlocked)(FILE *__restrict stream,
                                 fpos_t const *__restrict pos) THROWS(...) {
	return libc_fsetpos_unlocked(stream, pos);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.getc") NONNULL((1)) int
(LIBDCALL libd_getw_unlocked)(FILE *__restrict stream) THROWS(...) {
	return libc_getw_unlocked(stream);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.write.putc") NONNULL((2)) int
(LIBDCALL libd_putw_unlocked)(int w,
                              FILE *__restrict stream) THROWS(...) {
	return libc_putw_unlocked(w, stream);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.utility") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_setvbuf_unlocked)(FILE *__restrict stream,
                                            char *__restrict buf,
                                            int modes,
                                            size_t bufsize) {
	return libc_setvbuf_unlocked(stream, buf, modes, bufsize);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.getc") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_ungetc_unlocked)(int ch,
                                           FILE *__restrict stream) {
	return libc_ungetc_unlocked(ch, stream);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.read") WUNUSED NONNULL((1, 2, 4)) ssize_t
(LIBDCALL libd_getdelim_unlocked)(char **__restrict lineptr,
                                  size_t *__restrict pcount,
                                  int delimiter,
                                  FILE *__restrict stream) THROWS(...) {
	return libc_getdelim_unlocked(lineptr, pcount, delimiter, stream);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.read") WUNUSED NONNULL((1, 2, 3)) ssize_t
(LIBDCALL libd_getline_unlocked)(char **__restrict lineptr,
                                 size_t *__restrict pcount,
                                 FILE *__restrict stream) THROWS(...) {
	return libc_getline_unlocked(lineptr, pcount, stream);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.seek.utility") NONNULL((1)) void
(LIBDCALL libd_rewind_unlocked)(FILE *__restrict stream) THROWS(...) {
	libc_rewind_unlocked(stream);
}
INTERN ATTR_SECTION(".text.crt.dos.io.tty") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_fisatty)(FILE *__restrict stream) {
	return libc_fisatty(stream);
}
/* >> fftruncate(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.utility") NONNULL((1)) int
(LIBDCALL libd_fftruncate)(FILE *__restrict stream,
                           __PIO_OFFSET length) THROWS(...) {
	return libc_fftruncate(stream, length);
}
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.utility") NONNULL((1)) int
(LIBDCALL libd_fftruncate_unlocked)(FILE *__restrict stream,
                                    __PIO_OFFSET length) THROWS(...) {
	return libc_fftruncate_unlocked(stream, length);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.write.write") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBDCALL libd_puts_unlocked)(char const *__restrict string) THROWS(...) {
	return libc_puts_unlocked(string);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.seek.seek") NONNULL((1)) int
(LIBDCALL libd_fseeko64_unlocked)(FILE *__restrict stream,
                                  off64_t off,
                                  int whence) THROWS(...) {
	return libc_fseeko64_unlocked(stream, off, whence);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.seek.seek") WUNUSED NONNULL((1)) off64_t
(LIBDCALL libd_ftello64_unlocked)(FILE *__restrict stream) THROWS(...) {
	return libc_ftello64_unlocked(stream);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.seek.pos") NONNULL((1, 2)) int
(LIBDCALL libd_fgetpos64_unlocked)(FILE *__restrict stream,
                                   fpos64_t *__restrict pos) THROWS(...) {
	return libc_fgetpos64_unlocked(stream, pos);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.seek.pos") NONNULL((1, 2)) int
(LIBDCALL libd_fsetpos64_unlocked)(FILE *__restrict stream,
                                   fpos64_t const *__restrict pos) THROWS(...) {
	return libc_fsetpos64_unlocked(stream, pos);
}
/* >> fftruncate64(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.utility") NONNULL((1)) int
(LIBDCALL libd_fftruncate64)(FILE *__restrict stream,
                             __PIO_OFFSET64 length) THROWS(...) {
	return libc_fftruncate64(stream, length);
}
/* >> fftruncate64_unlocked(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.utility") NONNULL((1)) int
(LIBDCALL libd_fftruncate64_unlocked)(FILE *__restrict stream,
                                      __PIO_OFFSET64 length) THROWS(...) {
	return libc_fftruncate64_unlocked(stream, length);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.write.printf") ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(LIBDCALL libd_vfprintf_unlocked)(FILE *__restrict stream,
                                  char const *__restrict format,
                                  va_list args) THROWS(...) {
	return libc_vfprintf_unlocked(stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.write.printf") ATTR_LIBC_PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd_fprintf_unlocked)(FILE *__restrict stream,
                                  char const *__restrict format,
                                  ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfprintf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.write.printf") ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBDCALL libd_vprintf_unlocked)(char const *__restrict format,
                                 va_list args) THROWS(...) {
	return libc_vprintf_unlocked(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.write.printf") ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd_printf_unlocked)(char const *__restrict format,
                                 ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vprintf_unlocked(format, args);
	va_end(args);
	return result;
}
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vfscanf_unlocked)(FILE *__restrict stream,
                                 char const *__restrict format,
                                 va_list args) THROWS(...) {
	return libc_vfscanf_unlocked(stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vscanf_unlocked)(char const *__restrict format,
                                va_list args) THROWS(...) {
	return libc_vscanf_unlocked(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_fscanf_unlocked)(FILE *__restrict stream,
                                 char const *__restrict format,
                                 ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfscanf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_scanf_unlocked)(char const *__restrict format,
                                ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vscanf_unlocked(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_RPC(LIBDCALL libd__fsopen)(char const *filename,
                                   char const *modes,
                                   int sflag) {
	return libc__fsopen(filename, modes, sflag);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.read") NONNULL((1)) int
(LIBDCALL libd__filbuf)(FILE *__restrict stream) THROWS(...) {
	return libc__filbuf(stream);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.write.write") NONNULL((2)) int
(LIBDCALL libd__flsbuf)(int ch,
                        FILE *__restrict stream) THROWS(...) {
	return libc__flsbuf(ch, stream);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") int
NOTHROW_NCX(LIBDCALL libd__setmaxstdio)(int val) {
	return libc__setmaxstdio(val);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") int
NOTHROW_NCX(LIBDCALL libd__set_printf_count_output)(int val) {
	return libc__set_printf_count_output(val);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") uint32_t
NOTHROW_NCX(LIBDCALL libd__set_output_format)(uint32_t format) {
	return libc__set_output_format(format);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd__vscanf_l)(char const *__restrict format,
                          locale_t locale,
                          va_list args) THROWS(...) {
	return libc__vscanf_l(format, locale, args);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd__vfscanf_l)(FILE *__restrict stream,
                           char const *__restrict format,
                           locale_t locale,
                           va_list args) THROWS(...) {
	return libc__vfscanf_l(stream, format, locale, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.scanf") WUNUSED ATTR_LIBC_SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd__vsscanf_l)(char const *__restrict input,
                                      char const *__restrict format,
                                      locale_t locale,
                                      va_list args) {
	return libc__vsscanf_l(input, format, locale, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.scanf") WUNUSED ATTR_LIBC_SCANF(3, 4) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnscanf)(char const *__restrict input,
                                     size_t inputlen,
                                     char const *__restrict format,
                                     va_list args) {
	return libc__vsnscanf(input, inputlen, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.scanf") ATTR_LIBC_SCANF(3, 5) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnscanf_l)(char const *__restrict input,
                                       size_t inputlen,
                                       char const *__restrict format,
                                       locale_t locale,
                                       va_list args) {
	return libc__vsnscanf_l(input, inputlen, format, locale, args);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__scanf_l)(char const *__restrict format,
                          locale_t locale,
                          ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscanf_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.scanf") ATTR_LIBC_SCANF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__fscanf_l)(FILE *__restrict stream,
                           char const *__restrict format,
                           locale_t locale,
                           ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfscanf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.scanf") ATTR_LIBC_SCANF(3, 4) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__snscanf)(char const *__restrict input,
                                     size_t inputlen,
                                     char const *__restrict format,
                                     ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnscanf(input, inputlen, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.scanf") ATTR_LIBC_SCANF(3, 5) NONNULL((1, 3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__snscanf_l)(char const *__restrict input,
                                       size_t inputlen,
                                       char const *__restrict format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnscanf_l(input, inputlen, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd__vsprintf_l)(char *__restrict buf,
                                       char const *__restrict format,
                                       locale_t locale,
                                       va_list args) {
	return libc__vsprintf_l(buf, format, locale, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF_P(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd__vsprintf_p)(char *__restrict buf,
                                       size_t bufsize,
                                       char const *__restrict format,
                                       va_list args) {
	return libc__vsprintf_p(buf, bufsize, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF_P(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd__vsprintf_p_l)(char *__restrict buf,
                                         size_t bufsize,
                                         char const *__restrict format,
                                         locale_t locale,
                                         va_list args) {
	return libc__vsprintf_p_l(buf, bufsize, format, locale, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__sprintf_l)(char *__restrict buf,
                                       char const *__restrict format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsprintf_l(buf, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__sprintf_s_l)(char *__restrict buf,
                                         size_t bufsize,
                                         char const *__restrict format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnprintf_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF_P(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__sprintf_p)(char *__restrict buf,
                                       size_t bufsize,
                                       char const *__restrict format,
                                       ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsprintf_p(buf, bufsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF_P(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__sprintf_p_l)(char *__restrict buf,
                                         size_t bufsize,
                                         char const *__restrict format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsprintf_p_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") WUNUSED ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd__vscprintf)(char const *__restrict format,
                                      va_list args) {
	return libc__vscprintf(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") WUNUSED ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__scprintf)(char const *__restrict format,
                                      ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vscprintf(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") WUNUSED ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd__vscprintf_l)(char const *__restrict format,
                                        locale_t locale,
                                        va_list args) {
	return libc__vscprintf_l(format, locale, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") WUNUSED ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd__vscprintf_p)(char const *__restrict format,
                                        va_list args) {
	return libc__vscprintf_p(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") WUNUSED ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd__vscprintf_p_l)(char const *__restrict format,
                                          locale_t locale,
                                          va_list args) {
	return libc__vscprintf_p_l(format, locale, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") WUNUSED ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__scprintf_l)(char const *__restrict format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscprintf_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") WUNUSED ATTR_LIBC_PRINTF_P(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__scprintf_p)(char const *__restrict format,
                                        ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vscprintf_p(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") WUNUSED ATTR_LIBC_PRINTF_P(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__scprintf_p_l)(char const *__restrict format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscprintf_p_l(format, locale, args);
	va_end(args);
	return result;
}
/* WARNING: This function returns the number of written character. - Not the required buffer size! */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnprintf)(char *__restrict buf,
                                      size_t bufsize,
                                      char const *__restrict format,
                                      va_list args) {
	return libc__vsnprintf(buf, bufsize, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnprintf_l)(char *__restrict buf,
                                        size_t bufsize,
                                        char const *__restrict format,
                                        locale_t locale,
                                        va_list args) {
	return libc__vsnprintf_l(buf, bufsize, format, locale, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnprintf_s)(char *__restrict buf,
                                        size_t bufsize,
                                        size_t buflen,
                                        char const *__restrict format,
                                        va_list args) {
	return libc__vsnprintf_s(buf, bufsize, buflen, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnprintf_s_l)(char *__restrict buf,
                                          size_t bufsize,
                                          size_t buflen,
                                          char const *__restrict format,
                                          locale_t locale,
                                          va_list args) {
	return libc__vsnprintf_s_l(buf, bufsize, buflen, format, locale, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__snprintf)(char *__restrict buf,
                                      size_t bufsize,
                                      char const *__restrict format,
                                      ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnprintf(buf, bufsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__snprintf_l)(char *__restrict buf,
                                        size_t bufsize,
                                        char const *__restrict format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnprintf_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__snprintf_c)(char *__restrict buf,
                                        size_t bufsize,
                                        char const *__restrict format,
                                        ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnprintf(buf, bufsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(3, 5) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__snprintf_c_l)(char *__restrict buf,
                                          size_t bufsize,
                                          char const *__restrict format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnprintf_l(buf, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF(4, 5) NONNULL((4)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__snprintf_s)(char *__restrict buf,
                                        size_t bufsize,
                                        size_t buflen,
                                        char const *__restrict format,
                                        ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnprintf_s(buf, bufsize, buflen, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(4, 6) NONNULL((4)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd__snprintf_s_l)(char *__restrict buf,
                                          size_t bufsize,
                                          size_t buflen,
                                          char const *__restrict format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnprintf_s_l(buf, bufsize, buflen, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd__vprintf_l)(char const *__restrict format,
                           locale_t locale,
                           va_list args) THROWS(...) {
	return libc__vprintf_l(format, locale, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd__vprintf_p)(char const *__restrict format,
                           va_list args) THROWS(...) {
	return libc__vprintf_p(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd__vprintf_p_l)(char const *__restrict format,
                             locale_t locale,
                             va_list args) THROWS(...) {
	return libc__vprintf_p_l(format, locale, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__printf_l)(char const *__restrict format,
                           locale_t locale,
                           ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vprintf_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__printf_s_l)(char const *__restrict format,
                             locale_t locale,
                             ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vprintf_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF_P(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__printf_p)(char const *__restrict format,
                           ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vprintf_p(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF_P(1, 3) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__printf_p_l)(char const *__restrict format,
                             locale_t locale,
                             ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vprintf_p_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd__vfprintf_l)(FILE *__restrict stream,
                            char const *__restrict format,
                            locale_t locale,
                            va_list args) THROWS(...) {
	return libc__vfprintf_l(stream, format, locale, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF_P(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd__vfprintf_p)(FILE *__restrict stream,
                            char const *__restrict format,
                            va_list args) THROWS(...) {
	return libc__vfprintf_p(stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF_P(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd__vfprintf_p_l)(FILE *__restrict stream,
                              char const *__restrict format,
                              locale_t locale,
                              va_list args) THROWS(...) {
	return libc__vfprintf_p_l(stream, format, locale, args);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__fprintf_l)(FILE *__restrict stream,
                            char const *__restrict format,
                            locale_t locale,
                            ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfprintf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__fprintf_s_l)(FILE *__restrict stream,
                              char const *__restrict format,
                              locale_t locale,
                              ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfprintf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.format.printf") ATTR_LIBC_PRINTF_P(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__fprintf_p)(FILE *__restrict stream,
                            char const *__restrict format,
                            ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vfprintf_p(stream, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.format.printf") ATTR_LIBC_PRINTF_P(2, 4) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd__fprintf_p_l)(FILE *__restrict stream,
                              char const *__restrict format,
                              locale_t locale,
                              ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfprintf_p_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") NONNULL((1, 2, 3)) errno_t
NOTHROW_RPC(LIBDCALL libd_fopen_s)(FILE **pstream,
                                   char const *filename,
                                   char const *modes) {
	return libc_fopen_s(pstream, filename, modes);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") NONNULL((1, 2, 3, 4)) errno_t
NOTHROW_RPC(LIBDCALL libd_freopen_s)(FILE **pstream,
                                     char const *filename,
                                     char const *modes,
                                     FILE *oldstream) {
	return libc_freopen_s(pstream, filename, modes, oldstream);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1)) errno_t
NOTHROW_NCX(LIBDCALL libd_tmpnam_s)(char *__restrict buf,
                                    rsize_t bufsize) {
	return libc_tmpnam_s(buf, bufsize);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.utility") NONNULL((1)) errno_t
NOTHROW_NCX(LIBDCALL libd_clearerr_s)(FILE *__restrict stream) {
	return libc_clearerr_s(stream);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.access") NONNULL((1)) errno_t
NOTHROW_RPC(LIBDCALL libd_tmpfile_s)(FILE **pstream) {
	return libc_tmpfile_s(pstream);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.read") WUNUSED NONNULL((1, 5)) size_t
NOTHROW_RPC(LIBDCALL libd_fread_s)(void *__restrict buf,
                                   size_t bufsize,
                                   size_t elemsize,
                                   size_t elemcount,
                                   FILE *__restrict stream) {
	return libc_fread_s(buf, bufsize, elemsize, elemcount, stream);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.read") WUNUSED NONNULL((1)) char *
NOTHROW_RPC(LIBDCALL libd_gets_s)(char *__restrict buf,
                                  rsize_t bufsize) {
	return libc_gets_s(buf, bufsize);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.locked.read.read") ATTR_LIBC_PRINTF(4, 0) NONNULL((4)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd_vsnprintf_s)(char *__restrict buf,
                                       size_t bufsize,
                                       size_t buflen,
                                       char const *__restrict format,
                                       va_list args) {
	return libc_vsnprintf_s(buf, bufsize, buflen, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.unlocked.read.read") WUNUSED NONNULL((1, 5)) size_t
(LIBDCALL libd__fread_nolock_s)(void *__restrict buf,
                                size_t bufsize,
                                size_t elemsize,
                                size_t elemcount,
                                FILE *__restrict stream) THROWS(...) {
	return libc__fread_nolock_s(buf, bufsize, elemsize, elemcount, stream);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$remove, libd_remove);
DEFINE_PUBLIC_ALIAS(DOS$rename, libd_rename);
DEFINE_PUBLIC_ALIAS(DOS$tmpnam, libd_tmpnam);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fclose, libd_fclose);
DEFINE_PUBLIC_ALIAS(DOS$_fclose_nolock, libd_fclose);
DEFINE_PUBLIC_ALIAS(DOS$fclose, libd_fclose);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fflush, libd_fflush);
DEFINE_PUBLIC_ALIAS(DOS$fflush, libd_fflush);
DEFINE_PUBLIC_ALIAS(DOS$setbuf, libd_setbuf);
DEFINE_PUBLIC_ALIAS(DOS$_IO_setvbuf, libd_setvbuf);
DEFINE_PUBLIC_ALIAS(DOS$setvbuf, libd_setvbuf);
DEFINE_PUBLIC_ALIAS(DOS$getc, libd_fgetc);
DEFINE_PUBLIC_ALIAS(DOS$_IO_getc, libd_fgetc);
DEFINE_PUBLIC_ALIAS(DOS$fgetc, libd_fgetc);
DEFINE_PUBLIC_ALIAS(DOS$putc, libd_fputc);
DEFINE_PUBLIC_ALIAS(DOS$_IO_putc, libd_fputc);
DEFINE_PUBLIC_ALIAS(DOS$fputc, libd_fputc);
DEFINE_PUBLIC_ALIAS(DOS$_fputchar, libd_putchar);
DEFINE_PUBLIC_ALIAS(DOS$putchar, libd_putchar);
DEFINE_PUBLIC_ALIAS(DOS$fgets, libd_fgets);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fputs, libd_fputs);
DEFINE_PUBLIC_ALIAS(DOS$fputs, libd_fputs);
DEFINE_PUBLIC_ALIAS(DOS$_IO_puts, libd_puts);
DEFINE_PUBLIC_ALIAS(DOS$puts, libd_puts);
DEFINE_PUBLIC_ALIAS(DOS$_IO_ungetc, libd_ungetc);
DEFINE_PUBLIC_ALIAS(DOS$ungetc, libd_ungetc);
DEFINE_PUBLIC_ALIAS(DOS$fread, libd_fread);
DEFINE_PUBLIC_ALIAS(DOS$fwrite_s, libd_fwrite);
DEFINE_PUBLIC_ALIAS(DOS$fwrite, libd_fwrite);
DEFINE_PUBLIC_ALIAS(DOS$fseek, libd_fseek);
DEFINE_PUBLIC_ALIAS(DOS$_IO_ftell, libd_ftell);
DEFINE_PUBLIC_ALIAS(DOS$ftell, libd_ftell);
DEFINE_PUBLIC_ALIAS(DOS$rewind_unlocked, libd_rewind);
DEFINE_PUBLIC_ALIAS(DOS$rewind, libd_rewind);
DEFINE_PUBLIC_ALIAS(DOS$clearerr_unlocked, libd_clearerr);
DEFINE_PUBLIC_ALIAS(DOS$clearerr, libd_clearerr);
DEFINE_PUBLIC_ALIAS(DOS$_IO_feof, libd_feof);
DEFINE_PUBLIC_ALIAS(DOS$feof, libd_feof);
DEFINE_PUBLIC_ALIAS(DOS$_IO_ferror, libd_ferror);
DEFINE_PUBLIC_ALIAS(DOS$ferror, libd_ferror);
DEFINE_PUBLIC_ALIAS(DOS$perror, libd_perror);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fopen, libd_fopen);
DEFINE_PUBLIC_ALIAS(DOS$fopen, libd_fopen);
DEFINE_PUBLIC_ALIAS(DOS$freopen, libd_freopen);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fgetpos, libd_fgetpos);
DEFINE_PUBLIC_ALIAS(DOS$fgetpos, libd_fgetpos);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fsetpos, libd_fsetpos);
DEFINE_PUBLIC_ALIAS(DOS$fsetpos, libd_fsetpos);
DEFINE_PUBLIC_ALIAS(DOS$_IO_vfprintf, libd_vfprintf);
DEFINE_PUBLIC_ALIAS(DOS$vfprintf, libd_vfprintf);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fprintf, libd_fprintf);
DEFINE_PUBLIC_ALIAS(DOS$fprintf, libd_fprintf);
DEFINE_PUBLIC_ALIAS(DOS$vprintf, libd_vprintf);
DEFINE_PUBLIC_ALIAS(DOS$_IO_printf, libd_printf);
DEFINE_PUBLIC_ALIAS(DOS$printf_s, libd_printf);
DEFINE_PUBLIC_ALIAS(DOS$printf, libd_printf);
DEFINE_PUBLIC_ALIAS(DOS$_IO_vfscanf, libd_vfscanf);
DEFINE_PUBLIC_ALIAS(DOS$__vfscanf, libd_vfscanf);
DEFINE_PUBLIC_ALIAS(DOS$vfscanf, libd_vfscanf);
DEFINE_PUBLIC_ALIAS(DOS$vscanf, libd_vscanf);
DEFINE_PUBLIC_ALIAS(DOS$fscanf, libd_fscanf);
DEFINE_PUBLIC_ALIAS(DOS$scanf, libd_scanf);
DEFINE_PUBLIC_ALIAS(DOS$_IO_gets, libd_gets);
DEFINE_PUBLIC_ALIAS(DOS$gets, libd_gets);
DEFINE_PUBLIC_ALIAS(DOS$__vsscanf, libd_vsscanf);
DEFINE_PUBLIC_ALIAS(DOS$vsscanf, libd_vsscanf);
DEFINE_PUBLIC_ALIAS(DOS$_IO_sscanf, libd_sscanf);
DEFINE_PUBLIC_ALIAS(DOS$sscanf, libd_sscanf);
DEFINE_PUBLIC_ALIAS(DOS$_IO_vsprintf, libd_vsprintf);
DEFINE_PUBLIC_ALIAS(DOS$vsprintf, libd_vsprintf);
DEFINE_PUBLIC_ALIAS(DOS$_IO_sprintf, libd_sprintf);
DEFINE_PUBLIC_ALIAS(DOS$sprintf, libd_sprintf);
DEFINE_PUBLIC_ALIAS(DOS$__vsnprintf, libd_vsnprintf);
DEFINE_PUBLIC_ALIAS(DOS$vsnprintf, libd_vsnprintf);
DEFINE_PUBLIC_ALIAS(DOS$snprintf, libd_snprintf);
DEFINE_PUBLIC_ALIAS(DOS$vdprintf, libd_vdprintf);
DEFINE_PUBLIC_ALIAS(DOS$dprintf, libd_dprintf);
DEFINE_PUBLIC_ALIAS(DOS$renameat, libd_renameat);
DEFINE_PUBLIC_ALIAS(DOS$removeat, libd_removeat);
DEFINE_PUBLIC_ALIAS(DOS$frenameat, libd_frenameat);
DEFINE_PUBLIC_ALIAS(DOS$tmpnam_r, libd_tmpnam_r);
DEFINE_PUBLIC_ALIAS(DOS$_IO_setbuffer, libd_setbuffer);
DEFINE_PUBLIC_ALIAS(DOS$setbuffer, libd_setbuffer);
DEFINE_PUBLIC_ALIAS(DOS$setlinebuf, libd_setlinebuf);
DEFINE_PUBLIC_ALIAS(DOS$_fflush_nolock, libd_fflush_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fflush_unlocked, libd_fflush_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_fread_nolock, libd_fread_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fread, libd_fread_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fread_unlocked, libd_fread_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_fwrite_nolock, libd_fwrite_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fwrite, libd_fwrite_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fwrite_unlocked, libd_fwrite_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$getc_unlocked, libd_fgetc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fgetc_unlocked, libd_fgetc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$putc_unlocked, libd_fputc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fputc_unlocked, libd_fputc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_tempnam, libd_tempnam);
DEFINE_PUBLIC_ALIAS(DOS$tempnam, libd_tempnam);
DEFINE_PUBLIC_ALIAS(DOS$_fdopen, libd_fdopen);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fdopen, libd_fdopen);
DEFINE_PUBLIC_ALIAS(DOS$fdopen, libd_fdopen);
DEFINE_PUBLIC_ALIAS(DOS$_fileno, libd_fileno);
DEFINE_PUBLIC_ALIAS(DOS$fileno_unlocked, libd_fileno);
DEFINE_PUBLIC_ALIAS(DOS$fileno, libd_fileno);
DEFINE_PUBLIC_ALIAS(DOS$fmemopen, libd_fmemopen);
DEFINE_PUBLIC_ALIAS(DOS$open_memstream, libd_open_memstream);
DEFINE_PUBLIC_ALIAS(DOS$__getdelim, libd_getdelim);
DEFINE_PUBLIC_ALIAS(DOS$getdelim, libd_getdelim);
DEFINE_PUBLIC_ALIAS(DOS$getline, libd_getline);
DEFINE_PUBLIC_ALIAS(DOS$putchar_unlocked, libd_putchar_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_lock_file, libd_flockfile);
DEFINE_PUBLIC_ALIAS(DOS$_IO_flockfile, libd_flockfile);
DEFINE_PUBLIC_ALIAS(DOS$flockfile, libd_flockfile);
DEFINE_PUBLIC_ALIAS(DOS$_unlock_file, libd_funlockfile);
DEFINE_PUBLIC_ALIAS(DOS$_IO_funlockfile, libd_funlockfile);
DEFINE_PUBLIC_ALIAS(DOS$funlockfile, libd_funlockfile);
DEFINE_PUBLIC_ALIAS(DOS$_IO_ftrylockfile, libd_ftrylockfile);
DEFINE_PUBLIC_ALIAS(DOS$ftrylockfile, libd_ftrylockfile);
DEFINE_PUBLIC_ALIAS(DOS$cuserid, libd_cuserid);
DEFINE_PUBLIC_ALIAS(DOS$_popen, libd_popen);
DEFINE_PUBLIC_ALIAS(DOS$_IO_popen, libd_popen);
DEFINE_PUBLIC_ALIAS(DOS$popen, libd_popen);
DEFINE_PUBLIC_ALIAS(DOS$_pclose, libd_pclose);
DEFINE_PUBLIC_ALIAS(DOS$pclose, libd_pclose);
DEFINE_PUBLIC_ALIAS(DOS$_getw, libd_getw);
DEFINE_PUBLIC_ALIAS(DOS$getw, libd_getw);
DEFINE_PUBLIC_ALIAS(DOS$_putw, libd_putw);
DEFINE_PUBLIC_ALIAS(DOS$putw, libd_putw);
DEFINE_PUBLIC_ALIAS(DOS$fopencookie, libd_fopencookie);
DEFINE_PUBLIC_ALIAS(DOS$fgets_unlocked, libd_fgets_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fputs_unlocked, libd_fputs_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$obstack_vprintf, libd_obstack_vprintf);
DEFINE_PUBLIC_ALIAS(DOS$obstack_printf, libd_obstack_printf);
DEFINE_PUBLIC_ALIAS(DOS$fseeko, libd_fseeko);
DEFINE_PUBLIC_ALIAS(DOS$ftello, libd_ftello);
DEFINE_PUBLIC_ALIAS(DOS$fseeko64, libd_fseeko64);
DEFINE_PUBLIC_ALIAS(DOS$ftello64, libd_ftello64);
DEFINE_PUBLIC_ALIAS(DOS$fopen64, libd_fopen64);
DEFINE_PUBLIC_ALIAS(DOS$freopen64, libd_freopen64);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fgetpos64, libd_fgetpos64);
DEFINE_PUBLIC_ALIAS(DOS$fgetpos64, libd_fgetpos64);
DEFINE_PUBLIC_ALIAS(DOS$_IO_fsetpos64, libd_fsetpos64);
DEFINE_PUBLIC_ALIAS(DOS$fsetpos64, libd_fsetpos64);
DEFINE_PUBLIC_ALIAS(DOS$file_printer, libd_file_printer);
DEFINE_PUBLIC_ALIAS(DOS$file_printer_unlocked, libd_file_printer_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$vasprintf, libd_vasprintf);
DEFINE_PUBLIC_ALIAS(DOS$__asprintf, libd_asprintf);
DEFINE_PUBLIC_ALIAS(DOS$asprintf, libd_asprintf);
DEFINE_PUBLIC_ALIAS(DOS$fdreopen, libd_fdreopen);
DEFINE_PUBLIC_ALIAS(DOS$fdreopen_unlocked, libd_fdreopen_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$freopen_unlocked, libd_freopen_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$freopen64_unlocked, libd_freopen64_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_fseek_nolock, libd_fseek_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fseek_unlocked, libd_fseek_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_ftell_nolock, libd_ftell_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$ftell_unlocked, libd_ftell_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fseeko_unlocked, libd_fseeko_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$ftello_unlocked, libd_ftello_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fgetpos_unlocked, libd_fgetpos_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fsetpos_unlocked, libd_fsetpos_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$getw_unlocked, libd_getw_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$putw_unlocked, libd_putw_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$setvbuf_unlocked, libd_setvbuf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_ungetc_nolock, libd_ungetc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$ungetc_unlocked, libd_ungetc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$getdelim_unlocked, libd_getdelim_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$getline_unlocked, libd_getline_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$rewind_unlocked, libd_rewind_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fisatty, libd_fisatty);
DEFINE_PUBLIC_ALIAS(DOS$fftruncate, libd_fftruncate);
DEFINE_PUBLIC_ALIAS(DOS$fftruncate_unlocked, libd_fftruncate_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$puts_unlocked, libd_puts_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_fseeki64_nolock, libd_fseeko64_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fseeko64_unlocked, libd_fseeko64_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_ftelli64_nolock, libd_ftello64_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$ftello64_unlocked, libd_ftello64_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fgetpos64_unlocked, libd_fgetpos64_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fsetpos64_unlocked, libd_fsetpos64_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fftruncate64, libd_fftruncate64);
DEFINE_PUBLIC_ALIAS(DOS$fftruncate64_unlocked, libd_fftruncate64_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$vfprintf_unlocked, libd_vfprintf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fprintf_s, libd_fprintf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fprintf_unlocked, libd_fprintf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$vprintf_s, libd_vprintf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$vprintf_unlocked, libd_vprintf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$printf_s, libd_printf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$printf_unlocked, libd_printf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$vfscanf_unlocked, libd_vfscanf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$vscanf_unlocked, libd_vscanf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fscanf_unlocked, libd_fscanf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$scanf_unlocked, libd_scanf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_fsopen, libd__fsopen);
DEFINE_PUBLIC_ALIAS(DOS$_filbuf, libd__filbuf);
DEFINE_PUBLIC_ALIAS(DOS$_flsbuf, libd__flsbuf);
DEFINE_PUBLIC_ALIAS(DOS$_setmaxstdio, libd__setmaxstdio);
DEFINE_PUBLIC_ALIAS(DOS$_set_printf_count_output, libd__set_printf_count_output);
DEFINE_PUBLIC_ALIAS(DOS$_set_output_format, libd__set_output_format);
DEFINE_PUBLIC_ALIAS(DOS$_vscanf_s_l, libd__vscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vscanf_l, libd__vscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfscanf_s_l, libd__vfscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfscanf_l, libd__vfscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsscanf_s_l, libd__vsscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsscanf_l, libd__vsscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnscanf_s, libd__vsnscanf);
DEFINE_PUBLIC_ALIAS(DOS$_vsnscanf, libd__vsnscanf);
DEFINE_PUBLIC_ALIAS(DOS$_vsnscanf_s_l, libd__vsnscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnscanf_l, libd__vsnscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_scanf_s_l, libd__scanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_scanf_l, libd__scanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_fscanf_s_l, libd__fscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_fscanf_l, libd__fscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_snscanf_s, libd__snscanf);
DEFINE_PUBLIC_ALIAS(DOS$_snscanf, libd__snscanf);
DEFINE_PUBLIC_ALIAS(DOS$_snscanf_s_l, libd__snscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_snscanf_l, libd__snscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsprintf_l, libd__vsprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsprintf_p, libd__vsprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_vsprintf_p_l, libd__vsprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_sprintf_l, libd__sprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_sprintf_s_l, libd__sprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_sprintf_p, libd__sprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_sprintf_p_l, libd__sprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_vscprintf, libd__vscprintf);
DEFINE_PUBLIC_ALIAS(DOS$_scprintf, libd__scprintf);
DEFINE_PUBLIC_ALIAS(DOS$_vscprintf_l, libd__vscprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vscprintf_p, libd__vscprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_vscprintf_p_l, libd__vscprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_scprintf_l, libd__scprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_scprintf_p, libd__scprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_scprintf_p_l, libd__scprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnprintf, libd__vsnprintf);
DEFINE_PUBLIC_ALIAS(DOS$_vsprintf_s_l, libd__vsnprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnprintf_l, libd__vsnprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnprintf_s, libd__vsnprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$_vsnprintf_s_l, libd__vsnprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_snprintf, libd__snprintf);
DEFINE_PUBLIC_ALIAS(DOS$_snprintf_l, libd__snprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_snprintf_c, libd__snprintf_c);
DEFINE_PUBLIC_ALIAS(DOS$_snprintf_c_l, libd__snprintf_c_l);
DEFINE_PUBLIC_ALIAS(DOS$_snprintf_s, libd__snprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$_snprintf_s_l, libd__snprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vprintf_s_l, libd__vprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vprintf_l, libd__vprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vprintf_p, libd__vprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_vprintf_p_l, libd__vprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_printf_l, libd__printf_l);
DEFINE_PUBLIC_ALIAS(DOS$_printf_s_l, libd__printf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_printf_p, libd__printf_p);
DEFINE_PUBLIC_ALIAS(DOS$_printf_p_l, libd__printf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfprintf_s_l, libd__vfprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfprintf_l, libd__vfprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfprintf_p, libd__vfprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_vfprintf_p_l, libd__vfprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_fprintf_l, libd__fprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_fprintf_s_l, libd__fprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_fprintf_p, libd__fprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_fprintf_p_l, libd__fprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$fopen_s, libd_fopen_s);
DEFINE_PUBLIC_ALIAS(DOS$freopen_s, libd_freopen_s);
DEFINE_PUBLIC_ALIAS(DOS$tmpnam_s, libd_tmpnam_s);
DEFINE_PUBLIC_ALIAS(DOS$clearerr_s, libd_clearerr_s);
DEFINE_PUBLIC_ALIAS(DOS$tmpfile_s, libd_tmpfile_s);
DEFINE_PUBLIC_ALIAS(DOS$fread_s, libd_fread_s);
DEFINE_PUBLIC_ALIAS(DOS$gets_s, libd_gets_s);
DEFINE_PUBLIC_ALIAS(DOS$vsnprintf_s, libd_vsnprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$_fread_nolock_s, libd__fread_nolock_s);

#endif /* !GUARD_LIBC_AUTO_DOSABI_STDIO_C */
