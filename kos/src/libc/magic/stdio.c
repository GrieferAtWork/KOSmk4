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

/* STDIO Sections:
 * - .text.crt.FILE.locked.access         (fopen(), fclose(), ...)
 * - .text.crt.FILE.locked.utility        (ferror(), ...)
 * - .text.crt.FILE.locked.read.getc      (getc(), ...)
 * - .text.crt.FILE.locked.read.read      (fread(), ...)
 * - .text.crt.FILE.locked.read.utility   (setvbuf(), feof(), ...)
 * - .text.crt.FILE.locked.write.putc     (putc(), ...)
 * - .text.crt.FILE.locked.write.write    (fwrite(), ...)
 * - .text.crt.FILE.locked.write.utility  (fflush(), ...)
 * - .text.crt.FILE.locked.seek.seek      (fseek(), ...)
 * - .text.crt.FILE.locked.seek.pos       (fgetpos(), ...)
 * - .text.crt.FILE.locked.seek.utility   (rewind(), ...)
 * - .text.crt.FILE.unlocked.*            (Same as locked.*)
 */

%[define_ccompat_header(cstdio)]

/* Declare stdio data sections as known, so they are guarantied to get linked properly */
%[declare_known_section(.data.crt.FILE.core.read)]
%[declare_known_section(.data.crt.FILE.core.write)]
%[declare_known_section(.data.crt.FILE.core.seek)]
%[declare_known_section(.data.crt.FILE.core.utility)]
%[declare_known_section(.data.crt.FILE.locked.utility)]
%[declare_known_section(.data.crt.FILE.locked.read.read)]
%[declare_known_section(.data.crt.FILE.locked.write.write)]


%[define_replacement(FILE     = __FILE)]
%[define_replacement(fd_t     = __fd_t)]
%[define_replacement(atflag_t = __atflag_t)]
%[define_replacement(off_t    = __FS_TYPE(off))]
%[define_replacement(off32_t  = __off32_t)]
%[define_replacement(off64_t  = __off64_t)]
%[define_replacement(fpos_t   = __FS_TYPE(pos))]
%[define_replacement(fpos64_t = __pos64_t)]
%[define_replacement(pos32_t  = __pos32_t)]
%[define_replacement(pos64_t  = __pos64_t)]
%[define_replacement(SEEK_SET = 0)]
%[define_replacement(SEEK_CUR = 1)]
%[define_replacement(SEEK_END = 2)]
%[define_replacement(cookie_io_functions_t = _IO_cookie_io_functions_t)]
%[define_replacement(locale_t = __locale_t)]

[cp_stdio][ignore][alias(fwrite_s)][section(.text.crt.FILE.locked.write.write)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fwrite_unlocked, _fwrite_nolock)]
crt_fwrite:([inp(min(elemsize*return,elemsize*elemcount))] void const *__restrict buf,
            $size_t elemsize, $size_t elemcount,
            [nonnull] $FILE *__restrict stream) -> $size_t = fwrite?;

[cp_stdio][ignore][alias(_fwrite_nolock, fwrite, fwrite_s)]
[section(.text.crt.FILE.unlocked.write.write)]
crt_fwrite_unlocked:([inp(min(elemsize*return,elemsize*elemcount))] void const *__restrict buf,
                     $size_t elemsize, $size_t elemcount,
                     [nonnull] $FILE *__restrict stream) -> $size_t = fwrite_unlocked?;

[cp_stdio][ignore][ATTR_WUNUSED]
[section(.text.crt.FILE.locked.read.read)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fread_unlocked, _fread_nolock)]
crt_fread:([outp(elemsize*elemcount)] void *__restrict buf,
           $size_t elemsize, $size_t elemcount,
           [nonnull] $FILE *__restrict stream) -> $size_t = fread?;

[cp_stdio][ignore][alias(_fread_nolock, fread)]
[section(.text.crt.FILE.unlocked.read.read)]
crt_fread_unlocked:([outp(elemsize*elemcount)] void *__restrict buf,
                    $size_t elemsize, $size_t elemcount,
                    [nonnull] $FILE *__restrict stream) -> $size_t = fread_unlocked?;

[cp_stdio][ignore][section(.text.crt.FILE.locked.read.getc)][alias(_IO_getc)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fgetc_unlocked, getc_unlocked)]
crt_fgetc:([nonnull] $FILE *__restrict stream) -> int = fgetc?;

[cp_stdio][ignore][alias(getc_unlocked, fgetc, getc, _IO_getc)]
[section(.text.crt.FILE.unlocked.read.getc)]
crt_fgetc_unlocked:([nonnull] $FILE *__restrict stream) -> int = fgetc_unlocked?;

[cp_stdio][ignore][alias(putc, _IO_putc)]
[section(.text.crt.FILE.locked.write.putc)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fputc_unlocked, putc_unlocked)]
crt_fputc:(int ch, [nonnull] $FILE *__restrict stream) -> int = fputc?;

[cp_stdio][ignore][alias(putc_unlocked, fputc, putc, _IO_putc)]
[section(.text.crt.FILE.unlocked.write.putc)]
crt_fputc_unlocked:(int ch, [nonnull] $FILE *__restrict stream) -> int = crt_fputc_unlocked?;


%{
#include <features.h>
#include <bits/types.h>
#include <bits/stdio_lim.h>
#include <libio.h>
#include <bits/oflags.h>
#ifdef __USE_DOS
#include <xlocale.h>
#endif /* __USE_DOS */
#ifdef __CRT_CYG_PRIMARY
#include <sys/reent.h>
#endif /* __CRT_CYG_PRIMARY */
#ifdef __CRT_DOS_PRIMARY
#include <bits/io-file.h>
#endif /* __CRT_DOS_PRIMARY */

__SYSDECL_BEGIN

/* The possibilities for the third argument to `setvbuf()'. */
#ifdef __CRT_DOS_PRIMARY
#define _IOFBF 0x0000 /* Fully buffered. */
#define _IOLBF 0x0040 /* Line buffered. */
#define _IONBF 0x0004 /* No buffering. */
#else
#define _IOFBF 0      /* Fully buffered. */
#define _IOLBF 1      /* Line buffered. */
#define _IONBF 2      /* No buffering. */
#endif

/* Default buffer size.  */
#ifndef BUFSIZ
#ifdef __USE_DOS
#define BUFSIZ 512
#else
#define BUFSIZ 8192
#endif
#endif

#ifndef EOF
#ifdef __EOF
#define EOF __EOF
#else
#define EOF (-1)
#endif
#endif

#ifndef SEEK_SET
#   define SEEK_SET  0 /* Seek from beginning of file.  */
#   define SEEK_CUR  1 /* Seek from current position.  */
#   define SEEK_END  2 /* Seek from end of file.  */
#if defined(__USE_GNU) && (defined(__CRT_KOS) || defined(__CRT_GLC))
#   define SEEK_DATA 3 /* Seek to next data.  */
#   define SEEK_HOLE 4 /* Seek to next hole.  */
#endif /* __USE_GNU && (__CRT_KOS || __CRT_GLC) */
#endif

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifdef __USE_DOS
#define P_tmpdir "\\"
#else
#define P_tmpdir "/tmp"
#endif
#endif


#ifdef __CC__
#ifndef __std_size_t_defined
#define __std_size_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __SIZE_TYPE__ size_t;
__NAMESPACE_STD_END
#endif /* !__std_size_t_defined */
#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef NULL
#define NULL __NULLPTR
#endif

#ifdef __USE_XOPEN2K8
#ifndef __off_t_defined
#define __off_t_defined 1
typedef __typedef_off_t off_t;
#endif /* !__off_t_defined */

#ifndef __ssize_t_defined
#define __ssize_t_defined 1
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

#ifdef __USE_LARGEFILE64
#ifndef __off64_t_defined
#define __off64_t_defined 1
typedef __off64_t off64_t;
#endif /* !__off64_t_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN2K8 */

#ifndef __std_fpos_t_defined
#define __std_fpos_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __FS_TYPE(pos) fpos_t;
__NAMESPACE_STD_END
#endif /* !__std_fpos_t_defined */
#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __fpos_t_defined
#define __fpos_t_defined 1
__NAMESPACE_STD_USING(fpos_t)
#endif /* !__fpos_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef __USE_LARGEFILE64
#ifndef __fpos64_t_defined
#define __fpos64_t_defined 1
typedef __pos64_t      fpos64_t;
#endif /* !__fpos64_t_defined */
#endif /* __USE_LARGEFILE64 */

#ifndef __std_FILE_defined
#define __std_FILE_defined 1
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */
#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __FILE_defined
#define __FILE_defined 1
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __NO_STDSTREAMS
/* Standard streams. */
#ifndef __stdstreams_defined
#define __stdstreams_defined 1
#undef stdin
#undef stdout
#undef stderr
#ifdef __CRT_CYG_PRIMARY
#   define stdin  (__CYG_REENT->__cyg_stdin)
#   define stdout (__CYG_REENT->__cyg_stdout)
#   define stderr (__CYG_REENT->__cyg_stderr)
#elif defined(__CRT_DOS_PRIMARY)
#ifdef __USE_DOS_LINKOBJECTS
#ifndef ___iob_defined
#define ___iob_defined 1
__LIBC FILE _iob[];
#endif /* !___iob_defined */
#   define stdin    (_iob+0)
#   define stdout   (_iob+1)
#   define stderr   (_iob+2)
#else /* __USE_DOS_LINKOBJECTS */
#ifndef ____iob_func_defined
#define ____iob_func_defined 1
__LIBC __ATTR_WUNUSED __ATTR_RETNONNULL FILE *__NOTHROW(__LIBCCALL __iob_func)(void);
#endif /* !____iob_func_defined */
#   define stdin    (__iob_func()+0)
#   define stdout   (__iob_func()+1)
#   define stderr   (__iob_func()+2)
#endif /* !__USE_DOS_LINKOBJECTS */
#else
__LIBC __FILE *stdin;
#define stdin  stdin
__LIBC __FILE *stdout;
#define stdout stdout
__LIBC __FILE *stderr;
#define stderr stderr
#endif
#endif /* !__stdstreams_defined */
#endif /* !__NO_STDSTREAMS */


}

%[insert:std]
%

%[default_impl_section(.text.crt.FILE.locked.seek.pos)]

[alias(fgetpos_unlocked)]
[stdio_throws][ignore][if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fgetpos_unlocked)]
crt_fgetpos:([nonnull] $FILE *__restrict stream, [nonnull] $pos32_t *__restrict pos) -> int = fgetpos?;

[stdio_throws][ignore][if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fgetpos64_unlocked)]
crt_fgetpos64:([nonnull] $FILE *__restrict stream, [nonnull] $pos64_t *__restrict pos) -> int = fgetpos64?;

[stdio_throws][ignore][if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fsetpos_unlocked)]
crt_fsetpos:([nonnull] $FILE *__restrict stream, [nonnull] $pos32_t const *__restrict pos) -> int = fsetpos?;

[stdio_throws][ignore][if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fsetpos64_unlocked)]
[alias(fsetpos64_unlocked)] crt_fsetpos64:([nonnull] $FILE *__restrict stream, [nonnull] $pos64_t const *__restrict pos) -> int = fsetpos64?;

%[default_impl_section(.text.crt.FILE.locked.seek.seek)]
[stdio_throws][ignore][if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fseeko_unlocked)]
[alias(fseeko_unlocked)]    crt_fseeko:([nonnull] $FILE *__restrict stream, $off32_t off, int whence) -> int = fseeko?;
[stdio_throws][ignore][if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(ftello_unlocked)]
[alias(ftello_unlocked)]    crt_ftello:([nonnull] $FILE *__restrict stream) -> $off32_t = ftello?;
[stdio_throws][ignore][if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fseeko64_unlocked)]
[alias(fseeko64_unlocked, _fseeki64)] crt_fseeko64:([nonnull] $FILE *__restrict stream, $off32_t off, int whence) -> int = fseeko64?;
[stdio_throws][ignore][if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(ftello64_unlocked)]
[alias(ftello64_unlocked, _ftelli64)] crt_ftello64:([nonnull] $FILE *__restrict stream) -> $off64_t = ftello?;
[stdio_throws][ignore][if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(ftell_unlocked)]
[alias(ftell_unlocked)]     crt_ftell:([nonnull] $FILE *__restrict stream) -> long int = ftell?;
[stdio_throws][ignore][if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fseek_unlocked)]
[alias(fseek_unlocked)]     crt_fseek:([nonnull] $FILE *__restrict stream, long int off, int whence) -> int = fseek?;

%[default_impl_section(.text.crt.fs.modify)]

@@Remove a file or directory `FILENAME'
[cp][std][std_guard][noexport]
[same_impl][requires(defined(__CRT_AT_FDCWD) && $has_function(removeat))]
remove:([nonnull] char const *filename) -> int {
	return removeat(__CRT_AT_FDCWD, filename);
}

@@Rename a given file `OLDNAME' to `NEWNAME_OR_PATH', or in the event
@@that `NEWNAME_OR_PATH' refers to a directory, place the file within.
[cp][std][std_guard]
[same_impl][requires(defined(__CRT_HAVE_renameat) || $has_function(renameat))]
rename:([nonnull] char const *oldname, [nonnull] char const *newname_or_path) -> int {
	return renameat(__CRT_AT_FDCWD, oldname, __CRT_AT_FDCWD, newname_or_path);
}

%[default_impl_section(.text.crt.fs.utility)]
[std][ATTR_WUNUSED] tmpnam:([nonnull] char *buf) -> char *;

%[default_impl_section(.text.crt.FILE.locked.access)]
@@Close and destroy a given file `STREAM'
[stdio_throws][std] fclose:([nonnull] FILE *__restrict stream) -> int;

%[default_impl_section(.text.crt.FILE.locked.write.utility)]
[cp_stdio][ignore] crt_flushall:() -> int = _flushall?;

%[default_impl_section(.text.crt.FILE.locked.write.utility)]
[cp_stdio][ignore] crt_flushall:() -> int = _flushall?;

@@Flush any unwritten data from `STREAM' to the underlying filesystem/TTY
[cp_stdio][std][user]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fflush_unlocked, _fflush_nolock)]
[alias(fflush_unlocked, _fflush_nolock)][libc_impl({
	return stream ? 0 : libc__flushall();
})] fflush:([nullable] FILE *stream) -> int {
	/* NO-OP (When not implemented by the CRT, assume no
	 * buffering being done, meaning this function isn't needed) */
#ifdef __CRT_HAVE__flushall
	if (!stream)
		return crt_flushall();
#endif
	(void)stream;
	return 0;
}

%[default_impl_section(.text.crt.FILE.locked.read.utility)]

@@Alias for `setvbuf(STREAM, buf, _IOFBF, BUFSIZ)'
[std][impl_prefix(
#ifndef __BUFSIZ
#ifdef __USE_DOS
#define __BUFSIZ 512
#else
#define __BUFSIZ 8192
#endif
#endif
#ifdef __CRT_DOS_PRIMARY
#define ___IOFBF 0x0000 /* Fully buffered. */
#define ___IOLBF 0x0040 /* Line buffered. */
#define ___IONBF 0x0004 /* No buffering. */
#else
#define ___IOFBF 0      /* Fully buffered. */
#define ___IOLBF 1      /* Line buffered. */
#define ___IONBF 2      /* No buffering. */
#endif
)][requires($has_function(setvbuf))][same_impl]
setbuf:([nonnull] FILE *__restrict stream, char *__restrict buf) {
	setvbuf(stream, buf,
	        buf ? @___IOFBF@ : @___IONBF@,
	        buf ? __BUFSIZ : 0);
}

@@Set the buffer and buffer-mode to-be used by the given `STREAM'
@@@param modes: One of `_IOFBF', `_IOLBF' or `_IONBF'
[std] setvbuf:([nonnull] FILE *__restrict stream, char *__restrict buf, int modes, size_t bufsize) -> int;

%[default_impl_section(.text.crt.FILE.locked.read.getc)]

@@Read and return a single character from `STREAM'
@@If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
@@returned and the exact cause can be determined by using `ferror' and `feof'
[cp_stdio][std]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fgetc_unlocked, getc_unlocked)]
[alias(getc)][export_alias(_IO_getc)][noexport]
[requires((defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_s) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))))]
[dependency_string(defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))))]
fgetc:([nonnull] FILE *__restrict stream) -> int {
#if defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf) && (!defined(__USE_STDIO_UNLOCKED) || !(defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)))))
	return --stream->@__f_cnt@ >= 0 ? (int)((__UINT8_TYPE__)*stream->@__f_ptr@++) : _filbuf(stream);
#else
	char ch;
	if (!crt_fread(&ch, sizeof(char), 1, stream))
		return EOF;
	return (int)ch;
#endif
}

@@Alias for `fgetc()'
[cp_stdio][std][alias(_IO_getc)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(getc_unlocked, fgetc_unlocked)]
getc:([nonnull] FILE *__restrict stream) -> int = fgetc;


@@Alias for `fgetc(stdin)'
[cp_stdio][std]
[requires_include(<__crt.h>)]
[dependency_include(<local/stdstreams.h>)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(getchar_unlocked)]
[alias(_fgetchar)][noexport][same_impl]
[requires(!defined(__NO_STDSTREAMS) && $has_function(fgetc))]
getchar:() -> int {
	return fgetc(@__LOCAL_stdin@);
}

%[default_impl_section(.text.crt.FILE.locked.write.putc)]
@@Write a single character `CH' to `STREAM'
[cp_stdio][std]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fputc_unlocked, putc_unlocked)]
[alias(putc)][export_alias(_IO_putc)][noexport][crtbuiltin]
[requires((defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))))]
[dependency_string(defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))))]
fputc:(int ch, [nonnull] FILE *__restrict stream) -> int {
#if defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf) && (!defined(__USE_STDIO_UNLOCKED) || !(defined(__CRT_HAVE_fwrite) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))))
	return --stream->@__f_cnt@ >= 0 ? (int)((__UINT8_TYPE__)(*stream->@__f_ptr@++ = (char)ch)) : _flsbuf(ch, stream);
#else
	unsigned char byte = (unsigned char)(unsigned int)ch;
	if (!crt_fwrite(&byte, sizeof(unsigned char), 1, stream))
		return EOF;
	return ch;
#endif
}

@@Alias for `fputc()'
[cp_stdio][std][alias(_IO_putc)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(putc_unlocked, fputc_unlocked)]
[alias(putc_unlocked, fputc_unlocked)][crtbuiltin]
putc:(int ch, [nonnull] FILE *__restrict stream) -> int = fputc;

@@Alias for `fputc(CH, stdout)'
[requires_include(<__crt.h>)]
[cp_stdio][std][dependency_include(<local/stdstreams.h>)]
[requires(!defined(__NO_STDSTREAMS) && $has_function(fputc))][same_impl]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(putchar_unlocked)]
[alias(_fputchar, putchar_unlocked)][noexport][crtbuiltin]
putchar:(int ch) -> int {
	return fputc(ch, @__LOCAL_stdout@);
}

%[default_impl_section(.text.crt.FILE.locked.read.read)]

@@Read up to `BUFSIZE - 1' bytes of data from `STREAM', storing them into `BUF' stopped when
@@the buffer is full or a line-feed was read (in this case, the line-feed is also written to `BUF')
@@Afterwards, append a trailing NUL-character and re-return `BUF', or return `NULL' if an error occurred.
[cp_stdio][std][ATTR_WUNUSED][alias(fgets_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fgets_unlocked)]
[dependency_include(<parts/errno.h>)][same_impl]
[requires($has_function(fgetc) && $has_function(ungetc) && $has_function(ferror))]
fgets:([outp(min(strlen(return),bufsize))] char *__restrict buf,
       __STDC_INT_AS_SIZE_T bufsize,
       [nonnull] FILE *__restrict stream) -> char * {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
#ifdef @__ERANGE@
		__libc_seterrno(@__ERANGE@);
#endif /* __ERANGE */
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		int ch = fgetc(stream);
		if (ch == EOF) {
			if (n == 0 || ferror(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = fgetc(stream);
			if (ch == EOF) {
				if (n == 0 || ferror(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			ungetc(ch, stream);
			break;
		}
		buf[n] = (char)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}

%[default_impl_section(.text.crt.FILE.locked.write.write)]
@@Print a given string `STR' to `STREAM'. This is identical to:
@@>> fwrite(str, sizeof(char), strlen(str), stream);
[cp_stdio][std][requires($has_function(fwrite))]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fputs_unlocked)]
[alias(fputs_unlocked)][crtbuiltin][same_impl]
fputs:([nonnull] char const *__restrict str,
       [nonnull] FILE *__restrict stream) -> __STDC_INT_AS_SSIZE_T {
	__STDC_INT_AS_SIZE_T result;
	result = fwrite(str,
	                sizeof(char),
	                strlen(str),
	                stream);
	return result;
}

@@Print a given string `STR', followed by a line-feed to `STDOUT'
[cp_stdio][std][noexport][same_impl]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(puts_unlocked)]
[requires(!defined(__NO_STDSTREAMS) && $has_function(fputs))]
[requires_include(<__crt.h>)][export_alias(_IO_puts)]
[dependency_include(<local/stdstreams.h>)][crtbuiltin]
puts:([nonnull] char const *__restrict string) -> __STDC_INT_AS_SSIZE_T {
	__STDC_INT_AS_SSIZE_T result, temp;
	result = fputs(string, @__LOCAL_stdout@);
	if (result >= 0) {
		temp = fputc('\n', @__LOCAL_stdout@);
		if (temp <= 0)
			result = temp;
		else
			result += temp;
	}
	return result;
}

@@Unget a single character byte of data previously returned by `getc()'
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(ungetc_unlocked)]
[section(.text.crt.FILE.locked.read.getc)]
[std] ungetc:(int ch, [nonnull] FILE *__restrict stream) -> int;

@@Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF'
[cp_stdio][std][ATTR_WUNUSED][section(.text.crt.FILE.locked.read.read)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fread_unlocked, _fread_nolock)]
[noexport][requires($has_function(fgetc))]
[dependency_string(defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked))))]
fread:([inp(min(elemsize*return,elemsize*elemcount))] void *__restrict buf,
       size_t elemsize, size_t elemcount,
       [nonnull] FILE *__restrict stream) -> size_t {
	size_t i, result = 0;
	for (; elemcount; --elemcount, ++result) {
		for (i = 0; i < elemsize; ++i) {
			int byte;
			byte = fgetc(stream);
			if (byte == EOF)
				goto done;
			*(unsigned char *)buf = (unsigned char)(unsigned int)byte;
			buf = (unsigned char *)buf + 1;
		}
	}
done:
	return result;
}


@@Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM'
[cp_stdio][std][section(.text.crt.FILE.locked.write.write)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fwrite_unlocked, _fwrite_nolock)]
[alias(fwrite_s)][noexport][requires($has_function(fputc))][crtbuiltin]
[dependency_string(defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)|| defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked))))]
fwrite:([inp(min(elemsize*return,elemsize*elemcount))] void const *__restrict buf,
        size_t elemsize, size_t elemcount,
        [nonnull] FILE *__restrict stream) -> size_t {
	size_t i, result = 0;
	for (; elemcount; --elemcount, ++result) {
		for (i = 0; i < elemsize; ++i) {
			unsigned char byte;
			byte = *(unsigned char *)buf;
			if (fputc((int)(unsigned int)byte, stream) == EOF)
				goto done;
			buf = (unsigned char *)buf + 1;
		}
	}
done:
	return result;
}

%[default_impl_section(.text.crt.FILE.locked.seek.seek)]
@@Change the current in-file position of `STREAM' as a byte-offet from the start of the file
[stdio_throws][std]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fseek_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == 4), preferred_alias(fseeko_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == 8), preferred_alias(fseeko64_unlocked)]
[if(__SIZEOF_LONG__ == 4), alias(fseeko)]
[if(__SIZEOF_LONG__ == 8), alias(fseeko64, _fseeki64)]
[requires(defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE__fseeki64) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseeko64_unlocked))))]
fseek:([nonnull] FILE *__restrict stream, long int off, int whence) -> int {
#if __SIZEOF_LONG__ == 8 && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE__fseeki64) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fseeko64_unlocked)))
	return crt_fseeko64(stream, (off64_t)off, whence);
#elif defined(__CRT_HAVE_fseeko) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fseeko_unlocked))
	return crt_fseeko(stream, (off32_t)off, whence);
#else
	return crt_fseeko64(stream, (off64_t)off, whence);
#endif
}

@@Return the current in-file position of `STREAM' as a byte-offet from the start of the file
[stdio_throws][std][ATTR_WUNUSED]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(ftell_unlocked)]
[if(__SIZEOF_LONG__ == 4 && defined(__USE_STDIO_UNLOCKED)), preferred_alias(ftello_unlocked)]
[if(__SIZEOF_LONG__ == 8 && defined(__USE_STDIO_UNLOCKED)), preferred_alias(ftello64_unlocked)]
[if(__SIZEOF_LONG__ == 4), alias(ftello)]
[if(__SIZEOF_LONG__ == 8), alias(ftello64, _ftelli64)]
[requires(defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE__ftelli64) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftello64_unlocked))))]
ftell:([nonnull] FILE *__restrict stream) -> long int {
#if (__SIZEOF_LONG__ == 8) && (defined(__CRT_HAVE_fgetpos64) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fgetpos64_unlocked)))
	pos64_t pos;
	if (crt_fgetpos64(stream, &pos))
		return -1;
	return (long int)(off64_t)pos;
#elif (__SIZEOF_LONG__ == 4) && (defined(__CRT_HAVE_fgetpos) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fgetpos_unlocked)))
	pos32_t pos;
	if (crt_fgetpos(stream, &pos))
		return -1;
	return (long int)(off32_t)pos;
#elif defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE__ftelli64) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_ftello64_unlocked))
	return (long int)crt_ftello64(stream);
#elif defined(__CRT_HAVE_ftello) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_ftello_unlocked))
	return (long int)crt_ftello(stream);
#elif defined(__CRT_HAVE_fgetpos64) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fgetpos64_unlocked))
	pos64_t pos;
	if (crt_fgetpos64(stream, &pos))
		return -1;
	return (long int)(off64_t)pos;
#else
	pos32_t pos;
	if (crt_fgetpos(stream, &pos))
		return -1;
	return (long int)(off32_t)pos;
#endif
}

%[default_impl_section(.text.crt.FILE.locked.seek.utility)]
@@Rewind the current in-file position of `STREAM' to its starting position
[stdio_throws][std] rewind:([nonnull] FILE *__restrict stream);

%[default_impl_section(.text.crt.FILE.locked.access)]
@@Clear the error state of `STREAM', returning the stream to normal operations mode
[std][alias(clearerr_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(clearerr_unlocked)]
clearerr:([nonnull] FILE *__restrict stream);

%[default_impl_section(.text.crt.FILE.locked.read.utility)]
@@Check if end-of-file has been reached in `STREAM'
[std][ATTR_WUNUSED][alias(feof_unlocked)][export_alias(_IO_feof)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(feof_unlocked)]
feof:([nonnull] FILE *__restrict stream) -> int;

@@Check if an I/O error occurred in `STREAM'
%[default_impl_section(.text.crt.FILE.locked.utility)]
[std][ATTR_WUNUSED][alias(ferror_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(ferror_unlocked)]
ferror:([nonnull] FILE *__restrict stream) -> int;

@@Print a given `MESSAGE' alongside `strerror(errno)' to stderr:
@@>> if (message) {
@@>>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
@@>> } else {
@@>>     fprintf(stderr, "%s\n", strerror(errno));
@@>> }
%[default_impl_section(.text.crt.errno.utility)]
[cp][std][std_guard] perror:([nullable] char const *message);

%[default_impl_section(.text.crt.FILE.locked.access)]
@@Create and return a new file-stream for accessing a temporary file for reading/writing
[cp][if(defined(__USE_FILE_OFFSET64)), preferred_alias(tmpfile64)]
[alias(tmpfile64)][std][ATTR_WUNUSED]
tmpfile:() -> FILE *;

@@Create and return a new file-stream for accessing `FILENAME'
[cp][std][ATTR_WUNUSED]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(fopen64)][alias(fopen64)]
fopen:([nonnull] char const *__restrict filename,
       [nonnull] char const *__restrict modes) -> FILE *;

@@Re-open the given `STREAM' as a file-stream for accessing `FILENAME'
[cp][std]
[if(defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)), preferred_alias(freopen64_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(freopen_unlocked)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(freopen64)]
[alias(freopen64, freopen_unlocked, freopen64_unlocked)]
freopen:([nonnull] char const *__restrict filename,
         [nonnull] char const *__restrict modes,
         [nonnull] FILE *__restrict stream) -> FILE *;

%[default_impl_section(.text.crt.FILE.locked.seek.pos)]

@@Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
@@Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()'
[if(defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)), preferred_alias(fgetpos64_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED) && !defined(__USE_FILE_OFFSET64)), preferred_alias(fgetpos_unlocked)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(fgetpos64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(fgetpos)]
[requires(defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello64) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64))))]
[stdio_throws][noexport][std]
fgetpos:([nonnull] FILE *__restrict stream, [nonnull] fpos_t *__restrict pos) -> int {
#if defined(__USE_FILE_OFFSET64) && (defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE__ftelli64) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_ftello64_unlocked)))
	return (int32_t)(*pos = (fpos_t)crt_ftello64(stream)) < 0 ? -1 : 0;
#elif defined(__CRT_HAVE_fgetpos) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fgetpos_unlocked))
	pos32_t pos32;
	int result = crt_fgetpos(stream, &pos32);
	if (!result)
		*pos = (fpos_t)pos32;
	return result;
#elif defined(__CRT_HAVE_fgetpos64) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fgetpos64_unlocked))
	fpos64_t pos64;
	int result = crt_fgetpos64(stream, &pos64);
	if (!result)
		*pos = (fpos_t)pos64;
	return result;
#elif defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE__ftelli64) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_ftello64_unlocked))
	return (int32_t)(*pos = (fpos_t)crt_ftello64(stream)) < 0 ? -1 : 0;
#elif defined(__CRT_HAVE_ftello) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_ftello_unlocked))
	return (int32_t)(*pos = (fpos_t)crt_ftello(stream)) < 0 ? -1 : 0;
#else
	return (int32_t)(*pos = (fpos_t)crt_ftell(stream)) < 0 ? -1 : 0;
#endif
}

@@Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()'
[if(defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)), preferred_alias(fsetpos64_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED) && !defined(__USE_FILE_OFFSET64)), preferred_alias(fsetpos_unlocked)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(fsetpos64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(fsetpos)]
[requires(defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE__fseeki64) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseeko64_unlocked))))]
[stdio_throws][noexport][std]
fsetpos:([nonnull] FILE *__restrict stream, [nonnull] fpos_t const *__restrict pos) -> int {
#if defined(__USE_FILE_OFFSET64) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE__fseeki64) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fseeko64_unlocked)))
	return crt_fseeko64(stream, (off64_t)*pos, SEEK_SET);
#elif defined(__CRT_HAVE_fsetpos) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fsetpos_unlocked))
	pos32_t pos32 = (pos32_t)*pos;
	return crt_fsetpos(stream, &pos32);
#elif defined(__CRT_HAVE_fsetpos64) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fsetpos64_unlocked))
	fpos64_t pos64 = (fpos64_t)*pos;
	return crt_fsetpos64(stream, &pos64);
#elif defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE__fseeki64) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fseeko64_unlocked))
	return crt_fseeko64(stream, (off64_t)*pos, SEEK_SET);
#elif defined(__CRT_HAVE_fseeko) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fseeko_unlocked))
	return crt_fseeko(stream, (off32_t)*pos, SEEK_SET);
#else
	return crt_fseek(stream, (long int)*pos, SEEK_SET);
#endif
}

%[default_impl_section(.text.crt.FILE.locked.write.printf)]

@@Print data to `STREAM', following `FORMAT'
@@Return the number of successfully printed bytes
[cp_stdio][std][ATTR_LIBC_PRINTF(2, 0)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(vfprintf_unlocked)]
[same_impl][requires($has_function(file_printer))][alias(vfprintf_s)]
[section(.text.crt.FILE.locked.write.printf)][crtbuiltin]
vfprintf:([nonnull] FILE *__restrict stream,
          [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SSIZE_T {
	return (__STDC_INT_AS_SSIZE_T)format_vprintf(&file_printer, stream, format, args);
}

@@Print data to `STREAM', following `FORMAT'
@@Return the number of successfully printed bytes
[cp_stdio][if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fprintf_unlocked)]
[same_impl][requires($has_function(vfprintf))][alias(fprintf_s)]
[std][ATTR_LIBC_PRINTF(2, 3)]
[section(.text.crt.FILE.locked.write.printf)][crtbuiltin]
fprintf:([nonnull] FILE *__restrict stream, [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SSIZE_T
%{
	auto_block(printf(vfprintf))
}


@@Print data to `stdout', following `FORMAT'
@@Return the number of successfully printed bytes
[cp_stdio][std][ATTR_LIBC_PRINTF(1, 0)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(vprintf_unlocked)]
[same_impl][requires(!defined(__NO_STDSTREAMS) && $has_function(vfprintf))]
[requires_include(<__crt.h>)]
[alias(vprintf_s)][dependency_include(<local/stdstreams.h>)]
[section(.text.crt.FILE.locked.write.printf)][crtbuiltin]
vprintf:([nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SSIZE_T {
	return vfprintf(@__LOCAL_stdout@, format, args);
}

@@Print data to `stdout', following `FORMAT'
@@Return the number of successfully printed bytes
[cp_stdio][std][ATTR_LIBC_PRINTF(1, 2)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(printf_unlocked)]
[same_impl][requires($has_function(vprintf))][alias(printf_s)]
[section(.text.crt.FILE.locked.write.printf)][crtbuiltin]
printf:([nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SSIZE_T
%{
	auto_block(printf(vprintf))
}

%(std)
%(std)#if defined(__USE_ISOC99) || defined(__USE_DOS)

%[default_impl_section(.text.crt.FILE.locked.read.read)]

@@Scan data from `STREAM', following `FORMAT'
@@Return the number of successfully scanned data items
[cp_stdio][std][std_guard][ATTR_LIBC_SCANF(2, 0)][ATTR_WUNUSED][alias(_vfscanf, _vfscanf_s)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(vfscanf_unlocked)]
[same_impl][requires($has_function(fgetc) && $has_function(ungetc))]
[section(.text.crt.FILE.locked.read.scanf)]
[impl_prefix(
__LOCAL_LIBC(@vfscanf_ungetc@) __SSIZE_TYPE__ (__LIBCCALL __vfscanf_ungetc)(void *__arg, __CHAR32_TYPE__ __ch) {
	return ungetc((int)(unsigned int)__ch, (FILE *)__arg);
}
)][crtbuiltin][export_alias(__vfscanf)]
vfscanf:([nonnull] FILE *__restrict stream, [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	return format_vscanf((pformatgetc)&@fgetc@, &@__vfscanf_ungetc@, (void *)stream, format, args);
}

@@Scan data from `stdin', following `FORMAT'
@@Return the number of successfully scanned data items
[cp_stdio][std][std_guard][ATTR_LIBC_SCANF(1, 0)][ATTR_WUNUSED]
[requires_include(<__crt.h>)][alias(_vscanf)]
[dependency_include(<local/stdstreams.h>)]
[same_impl][requires(!defined(__NO_STDSTREAMS) && $has_function(vfscanf))]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(vscanf_unlocked)]
[section(.text.crt.FILE.locked.read.scanf)][crtbuiltin]
vscanf:([nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	return vfscanf(@__LOCAL_stdin@, format, args);
}
%(std)#endif /* __USE_ISOC99 || __USE_DOS */

%(std)

@@Scan data from `STREAM', following `FORMAT'
@@Return the number of successfully scanned data items
[cp_stdio][std][ATTR_LIBC_SCANF(2, 3)][ATTR_WUNUSED]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fscanf_unlocked)]
[section(.text.crt.FILE.locked.read.scanf)][crtbuiltin]
fscanf:([nonnull] FILE *__restrict stream, [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
%{
	auto_block(printf(vfscanf))
}

@@Scan data from `stdin', following `FORMAT'
@@Return the number of successfully scanned data items
[cp_stdio][std][ATTR_LIBC_SCANF(1, 2)][ATTR_WUNUSED]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(scanf_unlocked)]
[section(.text.crt.FILE.locked.read.scanf)][crtbuiltin]
scanf:([nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
%{
	auto_block(printf(vscanf))
}




%(std)
%(std)#if !defined(__USE_ISOC11) || (defined(__cplusplus) && __cplusplus <= 201103L)
[cp_stdio][std][std_guard]
[same_impl][requires(!defined(__NO_STDSTREAMS) && $has_function(fgets))]
[requires_include(<__crt.h>)][ATTR_WUNUSED]
[dependency_include(<local/stdstreams.h>)]
[dependency_include(<hybrid/typecore.h>)]
[ATTR_DEPRECATED("No buffer size checks (use `fgets' instead)")]
gets:([nonnull] char *__restrict buf) -> char * {
	return fgets(buf, @__INT_MAX__@, @__LOCAL_stdin@);
}
%(std)#endif /* !__USE_ISOC11 || __cplusplus <= 201103L */

%(std)
%(std)#if defined(__USE_ISOC99) || defined(__USE_DOS)


@@Scan data from a given `INPUT' string, following `FORMAT'
@@Return the number of successfully scanned data items
[guard][std][std_guard]
[dependency(unicode_readutf8)]
[dependency(unicode_readutf8_rev)]
[impl_prefix(
#include <hybrid/typecore.h>
#ifndef __EOF
#ifdef EOF
#define __EOF  EOF
#else
#define __EOF (-1)
#endif
#endif
__LOCAL_LIBC(@vsscanf_getc@) __SSIZE_TYPE__ (__LIBCCALL __vsscanf_getc)(void *__arg) {
	__CHAR32_TYPE__ __result = unicode_readutf8((char const **)__arg);
	return __result ? __result : __EOF;
}
__LOCAL_LIBC(@vsscanf_ungetc@) __SSIZE_TYPE__ (__LIBCCALL __vsscanf_ungetc)(void *__arg, __CHAR32_TYPE__ __UNUSED(__ch)) {
	unicode_readutf8_rev((char const **)__arg);
	return 0;
}
)][ATTR_LIBC_SCANF(2, 0)][ATTR_WUNUSED][alias(_vsscanf, _vsscanf_s)][crtbuiltin]
[section(.text.crt.unicode.static.format.scanf)][export_alias(__vsscanf)]
vsscanf:([nonnull] char const *__restrict input,
         [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	return format_vscanf(&@__vsscanf_getc@, &@__vsscanf_ungetc@, (void *)&input, format, args);
}
%(std)#endif /* __USE_ISOC99 || __USE_DOS */

%(std)
@@Scan data from a given `INPUT' string, following `FORMAT'
@@Return the number of successfully scanned data items
[std][ATTR_LIBC_SCANF(2, 3)][crtbuiltin]
[section(.text.crt.unicode.static.format.scanf)]
sscanf:([nonnull] char const *__restrict input,
        [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
%{
	auto_block(printf(vsscanf))
}


@@Print a formatted string to a given in-member string buffer `BUF'
@@Return the number of written characters, excluding a trailing NUL-character
[std][ATTR_LIBC_PRINTF(2, 0)][kernel][crtbuiltin]
[section(.text.crt.unicode.static.format.printf)]
vsprintf:([nonnull] char *__restrict dest,
          [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SSIZE_T {
	@__STDC_INT_AS_SSIZE_T@ result;
	result = (@__STDC_INT_AS_SSIZE_T@)format_vprintf(&format_sprintf_printer,
	                                                 (void *)&dest,
	                                                 format,
	                                                 args);
	if (result >= 0)
		*dest = '\0';
	return result;
}

@@Print a formatted string to a given in-member string buffer `BUF'
@@Return the number of written characters, excluding a trailing NUL-character
[std][ATTR_LIBC_PRINTF(2, 3)][kernel][crtbuiltin]
[section(.text.crt.unicode.static.format.printf)]
sprintf:([nonnull] char *__restrict buf,
         [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
%{
	auto_block(printf(vsprintf))
}


%(std)
%(std)#if defined(__USE_ISOC99) || defined(__USE_UNIX98) || defined(__USE_DOS)

@@Print a formatted string to a given in-member string buffer `BUF'
@@Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF'
[ATTR_LIBC_PRINTF(3, 0)][kernel][std][std_guard]
[dependency_prefix(
#ifndef ____format_snprintf_data_defined
#define ____format_snprintf_data_defined 1
struct __format_snprintf_data {
	char         *__sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ __sd_bufsiz; /* Remaining buffer size. */
};
#endif /* !____format_snprintf_data_defined */
)][crtbuiltin]
[section(.text.crt.unicode.static.format.printf)][export_alias(__vsnprintf)]
vsnprintf:([outp_opt(min(return,buflen))] char *__restrict buf, size_t buflen,
           [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	struct @__format_snprintf_data@ data;
	@__STDC_INT_AS_SSIZE_T@ result;
	data.@__sd_buffer@ = buf;
	data.@__sd_bufsiz@ = buflen;
	result = (@__STDC_INT_AS_SSIZE_T@)format_vprintf(&format_snprintf_printer,
	                                                (void *)&data,
	                                                 format,
	                                                 args);
	if (result >= 0 && data.@__sd_bufsiz@ != 0)
		*data.@__sd_buffer@ = '\0';
	return result;
}

@@Print a formatted string to a given in-member string buffer `BUF'
@@Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF'
[ATTR_LIBC_PRINTF(3, 4)][kernel][crtbuiltin][std][std_guard]
[section(.text.crt.unicode.static.format.printf)]
snprintf:([outp_opt(min(return,buflen))] char *__restrict buf, size_t buflen,
          [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
%{
	auto_block(printf(vsnprintf))
}
%(std)#endif /* __USE_ISOC99 || __USE_UNIX98 || __USE_DOS */


%
%#ifdef __USE_XOPEN2K8
[section(.text.crt.io.write)]
[cp][same_impl][requires($has_function(write))][dependency(write)][impl_prefix(
__LOCAL_LIBC(@vdprintf_printer@) __ssize_t (__LIBCCALL __vdprintf_printer)(void *__arg, char const *__restrict __data, __size_t __datalen) {
	return (__ssize_t)write((int)(unsigned int)(__UINTPTR_TYPE__)__arg, __data, __datalen);
}
)][ATTR_LIBC_PRINTF(2, 0)]
vdprintf:($fd_t fd, [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SSIZE_T {
	return format_vprintf(&__vdprintf_printer,
	                     (void *)(__UINTPTR_TYPE__)(unsigned int)fd,
	                      format,
	                      args);
}

[cp][ATTR_LIBC_PRINTF(2, 3)]
[section(.text.crt.io.write)]
dprintf:($fd_t fd, [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SSIZE_T
%{
	auto_block(printf(vdprintf))
}
%#endif /* __USE_XOPEN2K8 */

%
%#ifdef __USE_ATFILE
[cp][same_impl][requires($has_function(frenameat))]
[section(.text.crt.fs.modify)]
renameat:($fd_t oldfd, [nonnull] char const *oldname,
          $fd_t newfd, [nonnull] char const *newname_or_path) -> int {
	return frenameat(oldfd, oldname, newfd, newname_or_path, 0);
}

%
%#ifdef __USE_KOS
@@Remove a file or directory `FILENAME' relative to a given base directory `DIRFD'
[section(.text.crt.fs.modify)]
[cp] removeat:($fd_t dirfd, [nonnull] char const *filename) -> int;

@@@param flags: Set of `0|AT_DOSPATH'
[section(.text.crt.fs.modify)]
[cp] frenameat:($fd_t oldfd, [nonnull] char const *oldname,
                $fd_t newfd, [nonnull] char const *newname_or_path, $atflag_t flags) -> int;

%#endif /* __USE_KOS */
%#endif /* __USE_ATFILE */

%
%#ifdef __USE_MISC
[ATTR_WUNUSED][noexport][requires(defined(__CRT_HAVE_tmpnam))]
[section(.text.crt.fs.utility)]
tmpnam_r:([nonnull] char *buf) -> char * {
	return buf ? tmpnam(buf) : NULL;
}

@@Specify the location and size for the buffer to-be used by `STREAM'
[requires($has_function(setvbuf))][same_impl]
[section(.text.crt.FILE.locked.read.utility)]
setbuffer:([nonnull] $FILE *__restrict stream, [nullable] char *buf, $size_t bufsize) {
	setvbuf(stream,
	        buf,
	        buf ? _IOFBF : _IONBF,
	        buf ? bufsize : ($size_t)0);
}

@@Change the given `STREAM' to become line-buffered
[requires($has_function(setvbuf))][same_impl]
[section(.text.crt.FILE.locked.read.utility)]
setlinebuf:([nonnull] $FILE *__restrict stream) {
	setvbuf(stream, NULL, _IOLBF, 0);
}

@@Same as `fflush()', but performs I/O without acquiring a lock to `STREAM'
[cp_stdio][alias(_fflush_nolock)][alias(fflush)][user]
[section(.text.crt.FILE.unlocked.write.utility)]
fflush_unlocked:([nullable] $FILE *stream) -> int = fflush;

@@Same as `fread()', but performs I/O without acquiring a lock to `STREAM'
[cp_stdio][ATTR_WUNUSED][alias(_fread_nolock, fread)][noexport]
[requires($has_function(fgetc_unlocked))]
[dependency_string(defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc))]
[section(.text.crt.FILE.unlocked.read.read)]
fread_unlocked:([outp(min(return*elemsize,elemcount*elemsize))] void *__restrict buf,
                $size_t elemsize, $size_t elemcount,
                [nonnull] $FILE *__restrict stream) -> $size_t {
	$size_t i, result = 0;
	for (; elemcount; --elemcount, ++result) {
		for (i = 0; i < elemsize; ++i) {
			int byte;
			byte = fgetc_unlocked(stream);
			if (byte == EOF)
				goto done;
			*(unsigned char *)buf = (unsigned char)(unsigned int)byte;
			buf = (unsigned char *)buf + 1;
		}
	}
done:
	return result;
}

@@Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM'
[cp_stdio][alias(_fwrite_nolock, fwrite, fwrite_s)][noexport]
[requires($has_function(fputc_unlocked))][crtbuiltin]
[dependency_string(defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc))]
[section(.text.crt.FILE.unlocked.write.printf)]
fwrite_unlocked:([inp(min(return*elemsize,elemcount*elemsize))] void const *__restrict buf,
                 $size_t elemsize, $size_t elemcount,
                 [nonnull] $FILE *__restrict stream) -> $size_t {
	$size_t i, result = 0;
	for (; elemcount; --elemcount, ++result) {
		for (i = 0; i < elemsize; ++i) {
			unsigned char byte;
			byte = *(unsigned char *)buf;
			if (fputc_unlocked((int)(unsigned int)byte, stream) == EOF)
				goto done;
			buf = (unsigned char *)buf + 1;
		}
	}
done:
	return result;
}


%[default_impl_section(.text.crt.FILE.unlocked.read.utility)]
@@Same as `feof()', but performs I/O without acquiring a lock to `STREAM'
[ATTR_WUNUSED] feof_unlocked:([nonnull] $FILE *__restrict stream) -> int = feof;

%[default_impl_section(.text.crt.FILE.unlocked.utility)]
@@Same as `ferror()', but performs I/O without acquiring a lock to `STREAM'
[ATTR_WUNUSED] ferror_unlocked:([nonnull] $FILE *__restrict stream) -> int = ferror;

@@Same as `clearerr()', but performs I/O without acquiring a lock to `STREAM'
clearerr_unlocked:([nonnull] $FILE *__restrict stream) = clearerr;

@@Same as `fileno()', but performs I/O without acquiring a lock to `STREAM'
[ATTR_WUNUSED][alias(_fileno)]
fileno_unlocked:([nonnull] $FILE *__restrict stream) -> $fd_t = fileno;


%[default_impl_section(.text.crt.FILE.unlocked.read.getc)]
@@Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM'
[cp_stdio][noexport][alias(getc_unlocked)]
[if(!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf)), alias(getc, fgetc)]
[requires((defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_s))]
[dependency_string(defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_s))]
fgetc_unlocked:([nonnull] $FILE *__restrict stream) -> int {
#if defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)
	return --stream->@__f_cnt@ >= 0 ? (int)((__UINT8_TYPE__)*stream->@__f_ptr@++) : _filbuf(stream);
#else
	char ch;
	if (!crt_fread_unlocked(&ch, sizeof(char), 1, stream))
		return EOF;
	return (int)ch;
#endif
}

%[default_impl_section(.text.crt.FILE.unlocked.write.putc)]

@@Same as `fputc()', but performs I/O without acquiring a lock to `STREAM'
[cp_stdio][noexport][alias(putc_unlocked)]
[if(!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf)), alias(putc, fputc)][crtbuiltin]
[requires((defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s))]
[dependency_string(defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s))]
fputc_unlocked:(int ch, [nonnull] $FILE *__restrict stream) -> int {
#if defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)
	return --stream->@__f_cnt@ >= 0 ? (int)((__UINT8_TYPE__)(*stream->@__f_ptr@++ = (char)ch)) : _flsbuf(ch, stream);
#else
	unsigned char byte = (unsigned char)(unsigned int)ch;
	if (!crt_fwrite(&byte, sizeof(unsigned char), 1, stream))
		return EOF;
	return ch;
#endif
}
%#endif /* __USE_MISC */


%[default_impl_section(.text.crt.fs.utility)]
%
%#if defined(__USE_MISC) || defined(__USE_XOPEN) || defined(__USE_DOS)
[alias(_tempnam)][ATTR_MALLOC][ATTR_WUNUSED]
tempnam:(char const *dir, char const *pfx) -> char *;
%#endif /* __USE_MISC || __USE_XOPEN || __USE_DOS */


%
%#if defined(__USE_POSIX) || defined(__USE_DOS)
%[default_impl_section(.text.crt.FILE.locked.utility)]
@@Open a new file stream by inheriting a given file descriptor `FD'
@@Note that upon success (`return != NULL'), the given `FD' will be `close()'d once `fclose(return)' is called
[ATTR_WUNUSED][alias(_fdopen)]
fdopen:($fd_t fd, [nonnull] char const *__restrict modes) -> $FILE *;

@@Return the underlying file descriptor number used by `STREAM'
[ATTR_WUNUSED][alias(_fileno, fileno_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fileno_unlocked)]
fileno:([nonnull] $FILE *__restrict stream) -> $fd_t;
%#endif /* __USE_POSIX || __USE_DOS */


%
%#ifdef __USE_XOPEN2K8
%[default_impl_section(.text.crt.FILE.locked.access)]
[ATTR_WUNUSED] fmemopen:([inoutp(len)] void *mem, $size_t len, [nonnull] char const *modes) -> $FILE *;

[ATTR_WUNUSED]
open_memstream:(char **bufloc, $size_t *sizeloc) -> $FILE *;

%[default_impl_section(.text.crt.FILE.locked.read.read)]
[cp_stdio][ATTR_WUNUSED][nocrt]
__getdelim:([nonnull] char **__restrict lineptr,
            [nonnull] $size_t *__restrict pcount, int delimiter,
            [nonnull] $FILE *__restrict stream) -> $ssize_t = getdelim;

[cp_stdio][ATTR_WUNUSED][alias(getdelim_unlocked)][same_impl][alias(__getdelim)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(getdelim_unlocked)]
[requires($has_function(realloc) && $has_function(fgetc) && $has_function(ungetc))]
getdelim:([nonnull] char **__restrict lineptr,
          [nonnull] $size_t *__restrict pcount, int delimiter,
          [nonnull] $FILE *__restrict stream) -> $ssize_t {
	int ch;
	char *buffer;
	$size_t bufsize, result = 0;
	buffer  = *lineptr;
	bufsize = buffer ? *pcount : 0;
	for (;;) {
		if (result + 1 >= bufsize) {
			/* Allocate more memory. */
			$size_t new_bufsize = bufsize * 2;
			if (new_bufsize <= result + 1)
				new_bufsize = 16;
			assert(new_bufsize > result + 1);
			buffer = (char *)realloc(buffer,
			                         new_bufsize *
			                         sizeof(char));
			if unlikely(!buffer)
				return -1;
			*lineptr = buffer;
			*pcount  = bufsize;
		}
		ch = fgetc(stream);
		if (ch == EOF)
			break; /* EOF */
		buffer[result++] = (char)ch;
		if (ch == delimiter)
			break; /* Delimiter reached */
		/* Special case for line-delimiter. */
		if (delimiter == '\n' && ch == '\r') {
			/* Deal with '\r\n', as well as '\r' */
			ch = fgetc(stream);
			if (ch != EOF && ch != '\n')
				ungetc(ch, stream);
			/* Unify linefeeds (to use POSIX notation) */
			buffer[result - 1] = '\n';
			break;
		}
	}
	/* NUL-Terminate the buffer. */
	buffer[result] = '\0';
	return result;
}

[cp_stdio][ATTR_WUNUSED][requires($has_function(getdelim))]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(getline_unlocked)]
[alias(getline_unlocked)][same_impl]
getline:([nonnull] char **__restrict lineptr,
         [nonnull] $size_t *__restrict pcount,
         [nonnull] $FILE *__restrict stream) -> $ssize_t {
	return getdelim(lineptr, pcount, '\n', stream);
}

%#endif /* __USE_XOPEN2K8 */


%
%#ifdef __USE_POSIX
@@Alias for `fgetc_unlocked()'
%[default_impl_section(.text.crt.FILE.unlocked.read.getc)]
[cp_stdio][noexport][alias(getc, fgetc)]
getc_unlocked:([nonnull] $FILE *__restrict stream) -> int = fgetc_unlocked;

@@Alias for `fputc_unlocked()'
%[default_impl_section(.text.crt.FILE.unlocked.write.putc)]
[cp_stdio][noexport][alias(getc, fgetc)][crtbuiltin]
putc_unlocked:(int ch, [nonnull] $FILE *__restrict stream) -> int = fputc_unlocked;

%[default_impl_section(.text.crt.FILE.unlocked.read.getc)]
@@Same as `getchar()', but performs I/O without acquiring a lock to `stdin'
[requires_include(<__crt.h>)]
[cp_stdio][noexport][dependency_include(<local/stdstreams.h>)]
[same_impl][requires(!defined(__NO_STDSTREAMS) && $has_function(fgetc_unlocked))]
getchar_unlocked:() -> int {
	return fgetc_unlocked(@__LOCAL_stdin@);
}

%[default_impl_section(.text.crt.FILE.unlocked.write.putc)]
@@Same as `putchar()', but performs I/O without acquiring a lock to `stdout'
[requires_include(<__crt.h>)]
[cp_stdio][noexport][dependency_include(<local/stdstreams.h>)][crtbuiltin]
[same_impl][requires(!defined(__NO_STDSTREAMS) && $has_function(fputc_unlocked))]
putchar_unlocked:(int ch) -> int {
	return fputc_unlocked(ch, @__LOCAL_stdout@);
}

%[default_impl_section(.text.crt.FILE.locked.utility)]
@@Acquire a lock to `STREAM' and block until doing so succeeds
[cp][alias(_lock_file)] flockfile:([nonnull] $FILE *__restrict stream);

@@Release a previously acquired lock from `STREAM'
[alias(_unlock_file)] funlockfile:([nonnull] $FILE *__restrict stream);

@@Try to acquire a lock to `STREAM'
[ATTR_WUNUSED] ftrylockfile:([nonnull] $FILE *__restrict stream) -> int;

%[default_impl_section(.text.crt.io.tty)]
%[insert:extern(ctermid)]
%#endif /* __USE_POSIX */

%
%#ifdef __USE_XOPEN
@@Return the name of the current user (`getpwuid(geteuid())'), storing
@@that name in `S'. When `S' is NULL, a static buffer is used instead
cuserid:(char *s) -> char *;
%#endif /* Use X/Open, but not issue 6.  */

%
%#ifdef __USE_POSIX2
%[default_impl_section(.text.crt.FILE.locked.access)]
@@Open and return a new process I/O stream for executing `COMMAND'
[cp][alias(_popen)][ATTR_WUNUSED]
popen:([nonnull] char const *command, [nonnull] char const *modes) -> $FILE *;

@@Close a process I/O file `STREAM'
[alias(_pclose)] pclose:([nonnull] $FILE *stream) -> int;

%#endif /* __USE_POSIX2 */

%
%#if defined(__USE_MISC) || defined(__USE_DOS) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))

%[default_impl_section(.text.crt.FILE.locked.read.getc)]
@@Similar to `getc()', but read 2 bytes
[cp_stdio][alias(_getw)]
[same_impl][requires($has_function(fgetc) && $has_function(ungetc))]
getw:([nonnull] $FILE *__restrict stream) -> int {
	char bytes[2]; int ch;
	ch = fgetc(self);
	if unlikely(ch == EOF)
		return EOF;
	bytes[0] = (char)ch;
	ch = fgetc(self);
	if unlikely(ch == EOF) {
		ungetc(bytes[0], stream);
		return EOF;
	}
	bytes[1] = (char)ch;
	bytes[2] = (char)ch;
	return (int)*(u16 *)bytes;
}

%[default_impl_section(.text.crt.FILE.locked.write.putc)]
@@Similar to `putc()', but write 2 bytes loaded from `W & 0xffff'
[cp_stdio][alias(_putw)]
[same_impl][requires($has_function(fwrite))]
putw:(int w, [nonnull] $FILE *__restrict stream) -> int {
	u16 word = (u16)(unsigned int)w;
	if (!fwrite(&word, 2, 1, stream))
		return EOF;
	return w;
}


%#endif /* __USE_MISC || __USE_DOS || (__USE_XOPEN && !__USE_XOPEN2K) */


%
%#if defined(__USE_GNU) || defined(__USE_DOS)
%[default_impl_section(.text.crt.dos.FILE.utility)]
@@Alias for `_fcloseall()'
[stdio_throws][alias(_fcloseall)] fcloseall:() -> int;
%#endif /* __USE_GNU || __USE_DOS */

%
%#ifdef __USE_GNU

[ATTR_WUNUSED][section(.text.crt.FILE.locked.access)]
fopencookie:(void *__restrict magic_cookie,
             [nonnull] char const *__restrict modes,
             $cookie_io_functions_t io_funcs) -> $FILE *;

%[default_impl_section(.text.crt.FILE.unlocked.read.read)]
@@Same as `fgets()', but performs I/O without acquiring a lock to `($FILE *)ARG'
[cp_stdio][alias(fgets)][ATTR_WUNUSED][dependency_include(<parts/errno.h>)]
[requires($has_function(fgetc_unlocked) && $has_function(ungetc_unlocked) && $has_function(ferror_unlocked))][same_impl]
fgets_unlocked:([outp(min(strlen(return),bufsize))] char *__restrict buf,
                __STDC_INT_AS_SIZE_T bufsize,
                [nonnull] $FILE *__restrict stream) -> char * {
	$size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
#ifdef @__ERANGE@
		__libc_seterrno(@__ERANGE@);
#endif /* __ERANGE */
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		int ch = fgetc_unlocked(stream);
		if (ch == EOF) {
			if (n == 0 || ferror_unlocked(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = fgetc_unlocked(stream);
			if (ch == EOF) {
				if (n == 0 || ferror_unlocked(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			ungetc_unlocked(ch, stream);
			break;
		}
		buf[n] = (char)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}

%[default_impl_section(.text.crt.FILE.unlocked.write.write)]
@@Same as `fputs()', but performs I/O without acquiring a lock to `($FILE *)ARG'
[cp_stdio][alias(fputs)][crtbuiltin][same_impl][requires($has_function(fwrite_unlocked))]
fputs_unlocked:([nonnull] char const *__restrict string,
                [nonnull] $FILE *__restrict stream) -> __STDC_INT_AS_SIZE_T {
	__STDC_INT_AS_SIZE_T result;
	result = fwrite_unlocked(string,
	                         sizeof(char),
	                         strlen(string),
	                         stream);
	return result;
}

%
%struct obstack;

%[default_impl_section(.text.crt.obstack)]
[ATTR_LIBC_PRINTF(2, 0)]
obstack_vprintf:([nonnull] struct obstack *__restrict obstack_,
                 [nonnull] char const *__restrict format, $va_list args) -> int;

[ATTR_LIBC_PRINTF(2, 3)][noexport]
[same_impl][requires(defined(__CRT_HAVE_obstack_vprintf))]
obstack_printf:([nonnull] struct obstack *__restrict obstack_,
                [nonnull] char const *__restrict format, ...) -> int {
	int result;
	va_list args;
	va_start(args, format);
	result = obstack_vprintf(obstack_, format, args);
	va_end(args);
	return result;
}
%#endif /* __USE_GNU */


%[default_impl_section(.text.crt.FILE.locked.seek.seek)]
%#if defined(__USE_LARGEFILE) || defined(__USE_XOPEN2K)
@@Change the current in-file position of `STREAM'
[stdio_throws]
[if(defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)), preferred_alias(fseeko64_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED) && !defined(__USE_FILE_OFFSET64)), preferred_alias(fseeko_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED) && (defined(__USE_FILE_OFFSET64) && __SIZEOF_LONG__ == 8) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_LONG__ == 4)), preferred_alias(fseek_unlocked)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(fseeko64, _fseeki64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(fseeko)]
[if((defined(__USE_FILE_OFFSET64) && __SIZEOF_LONG__ == 8) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_LONG__ == 4)), preferred_alias(fseek)]
[requires(defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseek) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek_unlocked))))]
fseeko:([nonnull] $FILE *__restrict stream, $off_t off, int whence) -> int {
#if defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE__fseeki64) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fseeko64_unlocked))
	return crt_fseeko64(stream, (off64_t)off, whence);
#elif defined(__CRT_HAVE_fseeko) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fseeko_unlocked))
	return crt_fseeko(stream, (off32_t)off, whence);
#else
	return crt_seek(stream, (long int)off, whence);
#endif
}

@@Return the current in-file position of `STREAM'
[stdio_throws][ATTR_WUNUSED]
[if(defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)), preferred_alias(ftello64_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED) && !defined(__USE_FILE_OFFSET64)), preferred_alias(ftello_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED) && (defined(__USE_FILE_OFFSET64) && __SIZEOF_LONG__ == 8) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_LONG__ == 4)), preferred_alias(ftell_unlocked)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(ftello64, _ftelli64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(ftello)]
[if((defined(__USE_FILE_OFFSET64) && __SIZEOF_LONG__ == 8) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_LONG__ == 4)), preferred_alias(ftell)]
[requires(defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE__ftelli64) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftello64_unlocked))))]
ftello:([nonnull] $FILE *__restrict stream) -> $off_t {
#if defined(__USE_FILE_OFFSET64) && (defined(__CRT_HAVE_fgetpos64) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fgetpos64_unlocked)))
	pos64_t pos;
	if (crt_fgetpos64(stream, &pos))
		return -1;
	return (off64_t)pos;
#elif !defined(__USE_FILE_OFFSET64) && (defined(__CRT_HAVE_fgetpos) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fgetpos_unlocked)))
	pos32_t pos;
	if (crt_fgetpos(stream, &pos))
		return -1;
	return (off32_t)pos;
#elif defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE__ftelli64) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_ftello64_unlocked))
	return (off_t)crt_ftello64(stream);
#elif defined(__CRT_HAVE_ftello)
	return (off_t)crt_ftello(stream);
#elif defined(__CRT_HAVE_fgetpos64) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fgetpos64_unlocked))
	pos64_t pos;
	if (crt_fgetpos64(stream, &pos))
		return -1;
	return (off_t)(off64_t)pos;
#else
	pos32_t pos;
	if (crt_fgetpos(stream, &pos))
		return -1;
	return (off_t)(off32_t)pos;
#endif
}

%#endif /* __USE_LARGEFILE || __USE_XOPEN2K */


%
%#ifdef __USE_LARGEFILE64
%[default_impl_section(.text.crt.FILE.locked.access)]
@@64-bit variant of `tmpfile'
[cp][alias(tmpfile)][ATTR_WUNUSED]
[largefile64_variant_of(tmpfile)] tmpfile64:() -> $FILE *;

%[default_impl_section(.text.crt.FILE.locked.seek.seek)]
@@64-bit variant of `fseeko'
[stdio_throws][alias(_fseeki64)][noexport][off64_variant_of(fseeko)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fseeko64_unlocked)]
[requires(defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseeko) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE_fseeko_unlocked))))]
fseeko64:([nonnull] $FILE *__restrict stream, $off64_t off, int whence) -> int {
#if defined(__CRT_HAVE_fseeko) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fseeko_unlocked))
	return crt_fseeko(stream, (off32_t)off, whence);
#else
	return crt_fseek(stream, (long int)off, whence);
#endif
}

@@64-bit variant of `ftello'
[stdio_throws][alias(_ftelli64)][noexport][ATTR_WUNUSED]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(ftello64_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == 8), preferred_alias(ftell_unlocked)]
[if(__SIZEOF_LONG__ == 8), alias(ftell)][off64_variant_of(ftello)]
[requires(defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftello) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE_ftello_unlocked))))]
ftello64:([nonnull] $FILE *__restrict stream) -> $off64_t {
#if defined(__CRT_HAVE_fgetpos64) || (defined(__USE_STDIO_UNLOCKED) && defined(__CRT_HAVE_fgetpos64_unlocked))
	pos64_t pos;
	if (crt_fgetpos64(stream, &pos))
		return -1;
	return (off64_t)pos;
#elif defined(__CRT_HAVE_fgetpos) || (defined(__USE_STDIO_UNLOCKED) &&defined(__CRT_HAVE_fgetpos_unlocked))
	pos32_t pos;
	if (crt_fgetpos(stream, &pos))
		return -1;
	return (off64_t)(off32_t)pos;
#elif defined(__CRT_HAVE_ftello) || (defined(__USE_STDIO_UNLOCKED) &&defined(__CRT_HAVE_ftello_unlocked))
	return (off64_t)crt_ftello(stream);
#else
	return (off64_t)crt_ftell(stream);
#endif
}

%[default_impl_section(.text.crt.FILE.locked.access)]

@@64-bit variant of `fopen'
[cp][alias(fopen)][ATTR_WUNUSED][user][largefile64_variant_of(fopen)]
fopen64:([nonnull] char const *__restrict filename,
         [nonnull] char const *__restrict modes) -> $FILE * = fopen;

@@64-bit variant of `freopen'
[cp][user][largefile64_variant_of(freopen)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(freopen64_unlocked)]
[alias(freopen, freopen_unlocked, freopen64_unlocked)]
freopen64:([nonnull] char const *__restrict filename,
           [nonnull] char const *__restrict modes,
           [nonnull] $FILE *__restrict stream) -> $FILE * = freopen;

%[default_impl_section(.text.crt.FILE.locked.seek.pos)]

@@64-bit variant of `fgetpos'
[stdio_throws][noexport]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fgetpos64_unlocked)]
[alias(fgetpos64_unlocked)][off64_variant_of(fgetpos)]
[requires(defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64))]
fgetpos64:([nonnull] $FILE *__restrict stream, [nonnull] fpos64_t *__restrict pos) -> int {
#if defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64)
	return (int64_t)(*pos = (fpos64_t)crt_ftello64(stream)) < 0 ? -1 : 0;
#elif defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked)
	pos32_t pos32;
	int result = crt_fgetpos(stream, &pos32);
	if (!result)
		*pos = (fpos64_t)pos32;
	return result;
#elif defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked)
	return (int64_t)(*pos = (fpos64_t)crt_ftello(stream)) < 0 ? -1 : 0;
#else
	return (int64_t)(*pos = (fpos64_t)crt_ftell(stream)) < 0 ? -1 : 0;
#endif
}

@@64-bit variant of `fsetpos'
[stdio_throws][noexport][off64_variant_of(fsetpos)]
[requires(defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE__fseeki64))]
fsetpos64:([nonnull] $FILE *__restrict stream, [nonnull] fpos64_t const *__restrict pos) -> int {
#if defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE__fseeki64)
	return crt_fseeko64(stream, (off64_t)*pos, @SEEK_SET@);
#elif defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked)
	pos32_t pos32 = (pos32_t)*pos;
	return crt_fsetpos(stream, &pos32);
#elif defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked)
	return crt_fseeko(stream, (off32_t)*pos, @SEEK_SET@);
#else
	return crt_fseek(stream, (long int)*pos, @SEEK_SET@);
#endif
}

%#endif /* __USE_LARGEFILE64 */


%
%#ifdef __USE_KOS
%[default_impl_section(.text.crt.FILE.locked.write.write)]
@@For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument
[cp_stdio][noexport]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(file_printer_unlocked)]
[alias(file_printer_unlocked)][same_impl][requires($has_function(fwrite))]
file_printer:([nonnull] void *arg, [inp(datalen)] char const *__restrict data, $size_t datalen) -> $ssize_t {
	return (ssize_t)fwrite(data, sizeof(char), datalen, ($FILE *)arg);
}

%[default_impl_section(.text.crt.FILE.unlocked.write.write)]
@@Same as `file_printer()', but performs I/O without acquiring a lock to `($FILE *)ARG'
[cp_stdio][alias(file_printer)][noexport]
[same_impl][requires($has_function(fwrite_unlocked))]
file_printer_unlocked:([nonnull] void *arg, [inp(datalen)] char const *__restrict data, $size_t datalen) -> $ssize_t {
	return (ssize_t)fwrite_unlocked(data, sizeof(char), datalen, ($FILE *)arg);
}
%#endif /* __USE_KOS */





%
%#ifdef __USE_GNU
%[default_impl_section(.text.crt.heap.strdup)]
@@Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR'
[ATTR_LIBC_PRINTF(2, 3)][ATTR_WUNUSED][same_impl][dependency_include(<hybrid/__assert.h>)]
[requires($has_function(format_aprintf_pack) && $has_function(format_aprintf_printer) && $has_function(free))]
[dependency_prefix(
#ifndef __format_aprintf_data_defined
#define __format_aprintf_data_defined 1
struct format_aprintf_data {
	char         *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owend] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_aprintf_data_defined */
)]
vasprintf:([nonnull] char **__restrict pstr, [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SSIZE_T {
	char *result;
	ssize_t error;
	struct @format_aprintf_data@ data;
	__hybrid_assert(pstr != NULL);
	data.@ap_avail@ = 0;
	data.@ap_used@  = 0;
	data.@ap_base@  = NULL;
	error = format_vprintf(&format_aprintf_printer, &data, format, args);
	if unlikely(error < 0) {
		free(data.@ap_base@);
		return -1;
	}
	result = format_aprintf_pack(&data, NULL);
	if unlikely(!result)
		return -1;
	*pstr = result;
	return (__STDC_INT_AS_SSIZE_T)error;
}
@@Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR'
[ATTR_LIBC_PRINTF(2, 3)][ATTR_WUNUSED][alias(__asprintf)]
asprintf:([nonnull] char **__restrict pstr, [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SSIZE_T
%{
	auto_block(printf(vasprintf))
}
[ATTR_LIBC_PRINTF(2, 3)][ATTR_WUNUSED]
__asprintf:([nonnull] char **__restrict pstr, [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SSIZE_T = asprintf;
%#endif /* __USE_GNU */

%{




}
%#ifdef __USE_KOS

%[default_impl_section(.text.crt.FILE.locked.access)]

@@Re-open the given `STREAM' as a file-stream for accessing `FD'
[if(defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)), preferred_alias(fdreopen64_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fdreopen_unlocked)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(fdreopen64)]
[cp][alias(fdreopen64, fdreopen_unlocked, fdreopen64_unlocked)]
fdreopen:($fd_t fd, [nonnull] char const *__restrict modes,
          [nonnull] $FILE *__restrict stream) -> $FILE *;


%[default_impl_section(.text.crt.FILE.unlocked.access)]
[cp][user][alias(fdreopen)][doc_alias(fdreopen)]
fdreopen_unlocked:($fd_t fd, [nonnull] char const *__restrict modes,
                   [nonnull] $FILE *__restrict stream) -> $FILE * = fdreopen;

[cp][user][if(defined(__USE_FILE_OFFSET64)), preferred_alias(freopen64_unlocked)]
[alias(freopen64_unlocked, freopen, freopen64)][doc_alias(freopen)]
freopen_unlocked:([nonnull] char const *__restrict filename,
                  [nonnull] char const *__restrict modes,
                  [nonnull] $FILE *__restrict stream) -> $FILE * = freopen;

[cp][user][alias(freopen64, freopen_unlocked, freopen)][doc_alias(freopen)]
freopen64_unlocked:([nonnull] char const *__restrict filename,
                    [nonnull] char const *__restrict modes,
                    [nonnull] $FILE *__restrict stream) -> $FILE * = freopen64;


%[default_impl_section(.text.crt.FILE.unlocked.seek.seek)]
[stdio_throws][user] fseek_unlocked:([nonnull] $FILE *__restrict stream, long int off, int whence) -> int = fseek;
[stdio_throws][user] fseeko_unlocked:([nonnull] $FILE *__restrict stream, $off_t off, int whence) -> int = fseeko;
[stdio_throws][user] ftell_unlocked:([nonnull] $FILE *__restrict stream) -> long int = ftell;
[stdio_throws][user] ftello_unlocked:([nonnull] $FILE *__restrict stream) -> $off_t = ftello;

%[default_impl_section(.text.crt.FILE.unlocked.write.utility)]
[stdio_throws][user] flushall_unlocked:() -> int {
#if defined(__CRT_HAVE_fflush_unlocked) || defined(__CRT_HAVE__fflush_nolock)
	return fflush_unlocked(NULL);
#else
	return _flushall();
#endif
}

%[default_impl_section(.text.crt.FILE.unlocked.seek.pos)]
[stdio_throws][user] fgetpos_unlocked:([nonnull] $FILE *__restrict stream, [nonnull] $fpos_t *__restrict pos) -> int = fgetpos;
[stdio_throws][user] fsetpos_unlocked:([nonnull] $FILE *__restrict stream, [nonnull] $fpos_t const *__restrict pos) -> int = fsetpos;

[section(.text.crt.FILE.unlocked.read.getc)]
[cp_stdio][user] getw_unlocked:([nonnull] $FILE *__restrict stream) -> int = getw;

[cp_stdio][user][section(.text.crt.FILE.unlocked.write.putc)]
putw_unlocked:(int w, [nonnull] $FILE *__restrict stream) -> int = putw;

[user][section(.text.crt.FILE.unlocked.read.utility)]
setvbuf_unlocked:([nonnull] $FILE *__restrict stream, char *__restrict buf, int modes, $size_t bufsize) -> int = setvbuf;

[user][section(.text.crt.FILE.unlocked.read.getc)]
ungetc_unlocked:(int ch, [nonnull] $FILE *__restrict stream) -> int = ungetc;

[cp_stdio][ATTR_WUNUSED][user][section(.text.crt.FILE.unlocked.read.read)]
[requires($has_function(realloc) && $has_function(fgetc_unlocked) && $has_function(ungetc_unlocked))]
[alias(getdelim)][doc_alias(getdelim)][same_impl]
getdelim_unlocked:([nonnull] char **__restrict lineptr,
                   [nonnull] $size_t *__restrict pcount, int delimiter,
                   [nonnull] $FILE *__restrict stream) -> $ssize_t {
	int ch;
	char *buffer;
	$size_t bufsize, result = 0;
	buffer  = *lineptr;
	bufsize = buffer ? *pcount : 0;
	for (;;) {
		if (result + 1 >= bufsize) {
			/* Allocate more memory. */
			$size_t new_bufsize = bufsize * 2;
			if (new_bufsize <= result + 1)
				new_bufsize = 16;
			assert(new_bufsize > result + 1);
			buffer = (char *)realloc(buffer,
			                         new_bufsize *
			                         sizeof(char));
			if unlikely(!buffer)
				return -1;
			*lineptr = buffer;
			*pcount  = bufsize;
		}
		ch = fgetc_unlocked(stream);
		if (ch == EOF)
			break; /* EOF */
		buffer[result++] = (char)ch;
		if (ch == delimiter)
			break; /* Delimiter reached */
		/* Special case for line-delimiter. */
		if (delimiter == '\n' && ch == '\r') {
			/* Deal with '\r\n', as well as '\r' */
			ch = fgetc_unlocked(stream);
			if (ch != EOF && ch != '\n')
				ungetc_unlocked(ch, stream);
			/* Unify linefeeds (to use POSIX notation) */
			buffer[result - 1] = '\n';
			break;
		}
	}
	/* NUL-Terminate the buffer. */
	buffer[result] = '\0';
	return result;
}

[cp_stdio][ATTR_WUNUSED][user][section(.text.crt.FILE.unlocked.read.read)]
[requires($has_function(getdelim_unlocked))][alias(getline)][same_impl]
getline_unlocked:([nonnull] char **__restrict lineptr,
                  [nonnull] $size_t *__restrict pcount,
                  [nonnull] $FILE *__restrict stream) -> $ssize_t {
	return getdelim_unlocked(lineptr, pcount, '\n', stream);
}

[stdio_throws][user][section(.text.crt.FILE.unlocked.seek.utility)]
rewind_unlocked:([nonnull] $FILE *__restrict stream) = rewind;

[section(.text.crt.io.tty)][ATTR_WUNUSED][user]
[same_impl][requires($has_function(isatty) && $has_function(fileno))]
fisatty:([nonnull] $FILE *__restrict stream) -> int {
	return isatty(fileno(stream));
}

%#ifndef __PIO_OFFSET
%#ifdef __USE_KOS
%#define __PIO_OFFSET     __FS_TYPE(pos)
%#define __PIO_OFFSET64   __pos64_t
%#else /* __USE_KOS */
%#define __PIO_OFFSET     __FS_TYPE(off)
%#define __PIO_OFFSET64   __off64_t
%#endif /* !__USE_KOS */
%#endif /* !__PIO_OFFSET */


@@>> fftruncate(3)
@@Truncate the given file `STREAM' to a length of `LENGTH'
[if(defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)), preferred_alias(fftruncate64_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED) && !defined(__USE_FILE_OFFSET64)), preferred_alias(fftruncate_unlocked)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(fftruncate64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(fftruncate)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(fftruncate64_unlocked)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(fftruncate_unlocked)]
[requires($has_function(ftruncate) && $has_function(fileno))]
[section(.text.crt.FILE.locked.utility)][impl_prefix(
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else /* __USE_KOS */
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif /* !__USE_KOS */
#endif /* !__PIO_OFFSET */
)][noexport][cp_stdio]
fftruncate:([nonnull] $FILE *__restrict stream, __PIO_OFFSET length) -> int {
	int result = -1;
	fd_t fd = fileno(stream);
	if likely(fd >= 0)
		result = ftruncate(fd, length);
	return result;
}

@@>> fftruncate_unlocked(3)
@@Same as `fftruncate()', but don't acquire a lock to the file
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(fftruncate64_unlocked)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(fftruncate_unlocked)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(fftruncate64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(fftruncate)]
[requires($has_function(ftruncate) && $has_function(fileno_unlocked))]
[section(.text.crt.FILE.unlocked.utility)][impl_prefix(
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else /* __USE_KOS */
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif /* !__USE_KOS */
#endif /* !__PIO_OFFSET */
)][noexport][cp_stdio]
fftruncate_unlocked:([nonnull] $FILE *__restrict stream, __PIO_OFFSET length) -> int {
	int result = -1;
	fd_t fd = fileno_unlocked(stream);
	if likely(fd >= 0)
		result = ftruncate(fd, length);
	return result;
}


[cp_stdio][user][crtbuiltin][section(.text.crt.FILE.unlocked.write.write)]
[same_impl][alias(puts)][dependency_include(<local/stdstreams.h>)]
[requires(!defined(__NO_STDSTREAMS) && $has_function(fputs_unlocked))]
puts_unlocked:([nonnull] char const *__restrict string) -> __STDC_INT_AS_SSIZE_T {
	__STDC_INT_AS_SSIZE_T result, temp;
	result = fputs_unlocked(string, @__LOCAL_stdout@);
	if (result >= 0) {
		temp = fputc_unlocked('\n', @__LOCAL_stdout@);
		if (temp <= 0)
			result = temp;
		else
			result += temp;
	}
	return result;
}

%
%#ifdef __USE_LARGEFILE64

[off64_variant_of(fseeko_unlocked)]
[stdio_throws][user][section(.text.crt.FILE.unlocked.seek.seek)]
fseeko64_unlocked:([nonnull] $FILE *__restrict stream, $off64_t off, int whence) -> int = fseeko64;

[off64_variant_of(ftello_unlocked)]
[stdio_throws][ATTR_WUNUSED][user][section(.text.crt.FILE.unlocked.seek.seek)]
ftello64_unlocked:([nonnull] $FILE *__restrict stream) -> $off64_t = ftello64;

[off64_variant_of(fgetpos_unlocked)]
[stdio_throws][user][section(.text.crt.FILE.unlocked.seek.pos)]
fgetpos64_unlocked:([nonnull] $FILE *__restrict stream, [nonnull] fpos64_t *__restrict pos) -> int = fgetpos64;

[off64_variant_of(fsetpos_unlocked)]
[stdio_throws][user][section(.text.crt.FILE.unlocked.seek.pos)]
fsetpos64_unlocked:([nonnull] $FILE *__restrict stream, [nonnull] fpos64_t const *__restrict pos) -> int = fsetpos64;

@@>> fftruncate64(3)
@@Truncate the given file `STREAM' to a length of `LENGTH'
[off64_variant_of(fftruncate)][alias(fftruncate64_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fftruncate64_unlocked)]
[requires($has_function(ftruncate64) && $has_function(fileno))]
[section(.text.crt.FILE.locked.utility)][impl_prefix(
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else /* __USE_KOS */
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif /* !__USE_KOS */
#endif /* !__PIO_OFFSET */
)][noexport][cp_stdio]
fftruncate64:([nonnull] $FILE *__restrict stream, __PIO_OFFSET64 length) -> int {
	int result = -1;
	fd_t fd = fileno(stream);
	if likely(fd >= 0)
		result = ftruncate64(fd, length);
	return result;
}

@@>> fftruncate64_unlocked(3)
@@Truncate the given file `STREAM' to a length of `LENGTH'
[off64_variant_of(fftruncate_unlocked)][alias(fftruncate64)]
[requires($has_function(ftruncate64) && $has_function(fileno_unlocked))]
[section(.text.crt.FILE.unlocked.utility)][impl_prefix(
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else /* __USE_KOS */
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif /* !__USE_KOS */
#endif /* !__PIO_OFFSET */
)][noexport][cp_stdio]
fftruncate64_unlocked:([nonnull] $FILE *__restrict stream, __PIO_OFFSET64 length) -> int {
	int result = -1;
	fd_t fd = fileno_unlocked(stream);
	if likely(fd >= 0)
		result = ftruncate64(fd, length);
	return result;
}

%#endif /* __USE_LARGEFILE64 */


%[default_impl_section(.text.crt.FILE.unlocked.write.printf)]
[cp_stdio][ATTR_LIBC_PRINTF(2, 0)][same_impl]
[alias(vfprintf, vfprintf_s)][user][requires($has_function(file_printer_unlocked))]
vfprintf_unlocked:([nonnull] $FILE *__restrict stream,
                   [nonnull] char const *__restrict format,
                   $va_list args) -> __STDC_INT_AS_SSIZE_T {
	return (__STDC_INT_AS_SSIZE_T)format_vprintf(&file_printer_unlocked, stream, format, args);
}

[cp_stdio][ATTR_LIBC_PRINTF(2, 3)][alias(fprintf_s)][user][crtbuiltin]
fprintf_unlocked:([nonnull] $FILE *__restrict stream, [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SSIZE_T = fprintf;

[cp_stdio][ATTR_LIBC_PRINTF(1, 0)][alias(vprintf_s)][user]
vprintf_unlocked:([nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SSIZE_T = vprintf;

[cp_stdio][ATTR_LIBC_PRINTF(1, 2)][alias(printf_s)][user][crtbuiltin]
printf_unlocked:([nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SSIZE_T = printf;

%[default_impl_section(.text.crt.FILE.unlocked.read.scanf)]
[cp_stdio][ATTR_LIBC_SCANF(2, 0)][ATTR_WUNUSED][alias(_vfscanf, _vfscanf_s)][user]
vfscanf_unlocked:([nonnull] $FILE *__restrict stream, [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T = vfscanf;

[cp_stdio][ATTR_LIBC_SCANF(1, 0)][ATTR_WUNUSED][alias(_vscanf)][user]
vscanf_unlocked:([nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T = vscanf;

[cp_stdio][ATTR_LIBC_SCANF(2, 3)][ATTR_WUNUSED][user]
fscanf_unlocked:([nonnull] $FILE *__restrict stream, [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T = fscanf;

[cp_stdio][ATTR_LIBC_SCANF(1, 2)][ATTR_WUNUSED][user]
scanf_unlocked:([nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T = scanf;

%{
#endif /* __USE_KOS */

#endif /* __CC__ */

__SYSDECL_END

}



%{




}
%#ifdef __USE_DOS
%{
#define _NFILE          512
#define _NSTREAM_       512
#define _IOB_ENTRIES    20
#define _P_tmpdir       "\\"
#define _wP_tmpdir     L"\\"
#define _SYS_OPEN       20
#ifdef __USE_DOS_SLIB
#define L_tmpnam_s      18
#define TMP_MAX_S       2147483647
#define _TMP_MAX_S      2147483647
#endif /* __USE_DOS_SLIB */

#ifndef _FPOS_T_DEFINED
#define _FPOS_T_DEFINED 1
#endif /* !_FPOS_T_DEFINED */

#ifndef _STDSTREAM_DEFINED
#define _STDSTREAM_DEFINED 1
#endif /* !_STDSTREAM_DEFINED */

#ifndef _FILE_DEFINED
#define _FILE_DEFINED 1
#endif /* !_FILE_DEFINED */

#ifndef _CRT_PERROR_DEFINED
#define _CRT_PERROR_DEFINED 1
#endif /* !_CRT_PERROR_DEFINED */

}
%#ifdef __CC__
%{
#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */

#ifndef __rsize_t_defined
#define __rsize_t_defined 1
typedef __size_t rsize_t;
#endif /* !__rsize_t_defined */

}

%
%#ifndef _CRT_DIRECTORY_DEFINED
%#define _CRT_DIRECTORY_DEFINED 1
%[default_impl_section(.text.crt.dos.fs.modify)]
%[insert:extern(unlink)]
[guard][noexport] _unlink:([nonnull] char const *filename) -> int = unlink;
%#endif /* !_CRT_DIRECTORY_DEFINED */


%
%#ifndef _STDIO_DEFINED
%#define _STDIO_DEFINED 1

[attribute(*)][alias(*)] _popen:(*) = popen;
[attribute(*)][alias(*)] _pclose:(*) = pclose;

[section(.text.crt.dos.FILE.locked.access)]
[cp][ATTR_WUNUSED][requires($has_function(fopen))]
_fsopen:([nonnull] char const *filename, [nonnull] char const *modes, int sflag) -> $FILE * {
	(void)sflag;
	return fopen(filename, modes);
}

[attribute(*)][alias(*)] _fdopen:(*) = fdopen;

[section(.text.crt.dos.FILE.locked.write.utility)]
[cp_stdio] _flushall:() -> int {
#if defined(__CRT_HAVE_fflush) || defined(__CRT_HAVE_fflush_unlocked) || defined(__CRT_HAVE__fflush_nolock)
	return fflush(NULL);
#else
	return 0;
#endif
}

[attribute(*)][alias(*)] _fcloseall:(*) = fcloseall;
[attribute(*)][alias(*)] _fileno:(*) = fileno;
[attribute(*)][alias(*)] _fgetchar:(*) = getchar;
[attribute(*)][alias(*)] _fputchar:(*) = putchar;
[attribute(*)][alias(*)] _getw:(*) = getw;
[attribute(*)][alias(*)] _putw:(*) = putw;
[attribute(*)][alias(*)] _tempnam:(*) = tempnam;

%
[attribute(*)][alias(*)] _fseeki64:(*) = fseeko64;
[attribute(*)][alias(*)] _ftelli64:(*) = ftello64;

%[default_impl_section(.text.crt.dos.FILE.utility)]
%
[cp] _rmtmp:() -> int;

%
[section(.text.crt.dos.FILE.locked.read.read)]
[cp_stdio] _filbuf:([nonnull] $FILE *__restrict stream) -> int;

[section(.text.crt.dos.FILE.locked.write.write)]
[cp_stdio] _flsbuf:(int ch, [nonnull] $FILE *__restrict stream) -> int;

%
%[default_impl_section(.text.crt.dos.FILE.utility)]

[ATTR_WUNUSED] _getmaxstdio:() -> int;

_setmaxstdio:(int val) -> int;

[ATTR_WUNUSED] _get_printf_count_output:() -> int;

_set_printf_count_output:(int val) -> int;

[ATTR_WUNUSED] _get_output_format:() -> $uint32_t;

_set_output_format:($uint32_t format) -> $uint32_t;

%[default_impl_section(.text.crt.dos.FILE.locked.read.scanf)]

/* TODO: Header implementations of all of these printf functions */
[cp_stdio][ignore][ATTR_LIBC_SCANF(1, 3)][ATTR_WUNUSED][alias(_vscanf_s)]
_vscanf:([nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T = vscanf;
[cp_stdio][ignore][ATTR_LIBC_SCANF(1, 3)][ATTR_WUNUSED][alias(_vscanf_s_l)]
[same_impl][requires($has_function(vscanf))]
_vscanf_l:([nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T {
	(void)locale;
	return vscanf(format, args);
}
[cp_stdio][ignore][ATTR_LIBC_SCANF(1, 3)][ATTR_WUNUSED][alias(_vscanf)]
_vscanf_s:([nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T = vscanf;
[cp_stdio][ignore][ATTR_LIBC_SCANF(1, 3)][ATTR_WUNUSED]
_vscanf_s_l:([nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T = _vscanf_l;

[cp_stdio][ignore][ATTR_LIBC_SCANF(2, 4)][ATTR_WUNUSED][alias(_vfscanf_s)]
_vfscanf:([nonnull] $FILE *__restrict stream, [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T = vfscanf;
[cp_stdio][ignore][ATTR_LIBC_SCANF(2, 4)][ATTR_WUNUSED][alias(_vfscanf)]
_vfscanf_s:([nonnull] $FILE *__restrict stream, [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T = vfscanf;
[cp_stdio][ignore][ATTR_LIBC_SCANF(2, 4)][ATTR_WUNUSED]
[same_impl][requires($has_function(vfscanf))]
_vfscanf_l:([nonnull] $FILE *__restrict stream, [nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T {
	(void)locale;
	return vfscanf(stream, format, args);
}
[cp_stdio][ignore][ATTR_LIBC_SCANF(2, 4)][ATTR_WUNUSED]
_vfscanf_s_l:([nonnull] $FILE *__restrict stream, [nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T = _vfscanf_l;

%[default_impl_section(.text.crt.dos.unicode.static.format.scanf)]
[ignore][ATTR_LIBC_SCANF(2, 4)][ATTR_WUNUSED][alias(_vsscanf_s)]
_vsscanf:([nonnull] char const *__restrict input, [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T = vsscanf;
[ignore][ATTR_LIBC_SCANF(2, 4)][ATTR_WUNUSED][alias(_vsscanf)]
_vsscanf_s:([nonnull] char const *__restrict input, [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T = vsscanf;

%[default_impl_section(.text.crt.dos.unicode.locale.format.scanf)]
[ignore][ATTR_LIBC_SCANF(2, 4)][ATTR_WUNUSED]
_vsscanf_l:([nonnull] char const *__restrict input, [nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T {
	(void)locale;
	return vsscanf(input, format, args);
}
[ignore][ATTR_LIBC_SCANF(2, 4)][ATTR_WUNUSED]
_vsscanf_s_l:([nonnull] char const *__restrict input, [nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T = _vsscanf_l;


%[default_impl_section(.text.crt.dos.unicode.static.format.scanf)]
[ignore][alias(_vsnscanf_s)]
[dependency(unicode_readutf8_n)]
[dependency(unicode_readutf8_rev)]
[impl_prefix(
#include <hybrid/typecore.h>
#ifndef __EOF
#ifdef EOF
#define __EOF  EOF
#else
#define __EOF (-1)
#endif
#endif
struct __vsnscanf_data {
	char const *__ptr;
	char const *__end;
};
__LOCAL_LIBC(@vsnscanf_getc@) __SSIZE_TYPE__ (__LIBCCALL __vsnscanf_getc)(void *__arg) {
	__CHAR32_TYPE__ __result;
	__result = unicode_readutf8_n(
		&((struct __vsnscanf_data *)__arg)->__ptr,
		((struct __vsnscanf_data *)__arg)->__end);
	return __result ? __result : __EOF;
}
__LOCAL_LIBC(@vsnscanf_ungetc@) __SSIZE_TYPE__ (__LIBCCALL __vsnscanf_ungetc)(void *__arg, __CHAR32_TYPE__ __UNUSED(__ch)) {
	unicode_readutf8_rev(&((struct __vsnscanf_data *)__arg)->__ptr);
	return 0;
}
)][ATTR_WUNUSED][ATTR_LIBC_SCANF(3, 4)]
_vsnscanf:([inp(inputlen)] char const *__restrict input, $size_t inputlen,
           [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	struct @__vsnscanf_data@ data;
	data.@__ptr@ = input;
	data.@__end@ = input + inputlen;
	return format_vscanf(&@__vsnscanf_getc@, &@__vsnscanf_ungetc@, (void *)&data, format, args);
}
[ignore][ATTR_LIBC_SCANF(3, 0)]
_vsnscanf_s:([inp(inputlen)] char const *__restrict input, $size_t inputlen,
             [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T = _vsnscanf;

%[default_impl_section(.text.crt.dos.unicode.locale.format.scanf)]
[ignore][ATTR_LIBC_SCANF(3, 5)]
_vsnscanf_l:([inp(inputlen)] char const *__restrict input, $size_t inputlen,
             [nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T {
	(void)locale;
	return _vsnscanf(input, inputlen, format, args);
}
[ignore][ATTR_LIBC_SCANF(3, 0)]
_vsnscanf_s_l:([inp(inputlen)] char const *__restrict input, $size_t inputlen,
               [nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T = _vsnscanf_l;


%
[section(.text.crt.dos.FILE.locked.read.scanf)]
[cp_stdio][ATTR_LIBC_SCANF(1, 3)][export_alias(_scanf_s_l)]
_scanf_l:([nonnull] char const *__restrict format, $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vscanf_l))}

[section(.text.crt.dos.FILE.locked.read.scanf)]
[cp_stdio][ATTR_LIBC_SCANF(2, 4)][export_alias(_fscanf_s_l)]
_fscanf_l:([nonnull] $FILE *__restrict stream,
           [nonnull] char const *__restrict format, $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vfscanf_l))}

[section(.text.crt.dos.unicode.static.format.scanf)]
[ATTR_LIBC_SCANF(3, 4)][export_alias(_snscanf_s)]
_snscanf:([inp(inputlen)] char const *__restrict input, $size_t inputlen,
          [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vsnscanf))}

[section(.text.crt.dos.unicode.locale.format.scanf)]
[ATTR_LIBC_SCANF(3, 5)][export_alias(_snscanf_s_l)]
_snscanf_l:([inp(inputlen)] char const *__restrict input, $size_t inputlen,
            [nonnull] char const *__restrict format, $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vsnscanf_l))}

[section(.text.crt.dos.FILE.locked.read.scanf)]
[cp_stdio][ATTR_LIBC_SCANF(1, 3)][noexport][nouser]
_scanf_s_l:([nonnull] char const *__restrict format, $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vscanf_s_l))}

[section(.text.crt.dos.unicode.locale.format.scanf)]
[cp_stdio][ATTR_LIBC_SCANF(2, 4)][noexport][nouser]
_sscanf_s_l:([nonnull] char const *__restrict input, [nonnull] char const *__restrict format, $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T  %{auto_block(printf(_vsscanf_s_l))}

[section(.text.crt.dos.FILE.locked.read.scanf)]
[cp_stdio][ATTR_LIBC_SCANF(2, 4)][noexport][nouser]
_fscanf_s_l:([nonnull] $FILE *__restrict stream, [nonnull] char const *__restrict format, $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vfscanf_s_l))}

[section(.text.crt.dos.unicode.static.format.scanf)]
[ATTR_LIBC_SCANF(3, 4)][noexport][nouser]
_snscanf_s:([inp(inputlen)] char const *__restrict input, $size_t inputlen,
            [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vsnscanf_s))}

[section(.text.crt.dos.unicode.locale.format.scanf)]
[ATTR_LIBC_SCANF(3, 5)][noexport][nouser]
_snscanf_s_l:([inp(inputlen)] char const *__restrict input, $size_t inputlen,
              [nonnull] char const *__restrict format, $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vsnscanf_s_l))}

%
[section(.text.crt.dos.unicode.locale.format.printf)]
[ATTR_LIBC_PRINTF(2, 0)]
_vsprintf_l:([outp(return)] char *__restrict buf,
             [nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T {
	(void)locale;
	return vsprintf(buf, format, args);
}

[section(.text.crt.dos.unicode.locale.format.printf)]
[ATTR_LIBC_PRINTF(3, 0)][alias(_vsnprintf_l)]
_vsprintf_s_l:([outp_opt(min(return,bufsize))] char *__restrict buf, $size_t bufsize,
               [nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T = _vsnprintf_l;

[section(.text.crt.dos.unicode.static.format.printf)]
[ATTR_LIBC_PRINTF_P(3, 0)]
_vsprintf_p:([outp_opt(min(return,bufsize))] char *__restrict buf, $size_t bufsize,
             [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	(void)buf;
	(void)bufsize;
	(void)format;
	(void)args;
	/* TODO */
	return 0;
}

[section(.text.crt.dos.unicode.locale.format.printf)]
[ATTR_LIBC_PRINTF_P(3, 0)]
_vsprintf_p_l:([outp_opt(min(return,bufsize))] char *__restrict buf, $size_t bufsize,
               [nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T {
	(void)locale;
	return _vsprintf_p(buf, bufsize, format, args);
}

%
%[default_impl_section(.text.crt.dos.unicode.locale.format.printf)]
[ATTR_LIBC_PRINTF(2, 4)] _sprintf_l:([outp(return)] char *__restrict buf, [nonnull] char const *__restrict format, $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vsprintf_l))}
[ATTR_LIBC_PRINTF(3, 5)] _sprintf_s_l:([outp_opt(min(return,bufsize))] char *__restrict buf, $size_t bufsize, [nonnull] char const *__restrict format, $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vsprintf_s_l))}
[ATTR_LIBC_PRINTF_P(3, 4)] _sprintf_p:([outp_opt(min(return,bufsize))] char *__restrict buf, $size_t bufsize, [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vsprintf_p))}
[ATTR_LIBC_PRINTF_P(3, 5)] _sprintf_p_l:([outp_opt(min(return,bufsize))] char *__restrict buf, $size_t bufsize, [nonnull] char const *__restrict format, $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vsprintf_p_l))}

%
[section(.text.crt.dos.unicode.static.format.printf)]
[ATTR_LIBC_PRINTF(1, 0)][ATTR_WUNUSED]
_vscprintf:([nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	return vsnprintf(NULL, 0, format, args);
}

[ATTR_LIBC_PRINTF(1, 2)][ATTR_WUNUSED]
[section(.text.crt.dos.unicode.static.format.printf)]
_scprintf:([nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
%{
	auto_block(printf(_vscprintf))
}

%
[ATTR_LIBC_PRINTF(1, 0)][ATTR_WUNUSED]
[section(.text.crt.dos.unicode.locale.format.printf)]
_vscprintf_l:([nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T {
	(void)locale;
	return _vscprintf(format, args);
}

[ATTR_LIBC_PRINTF_P(1, 0)][ATTR_WUNUSED]
[section(.text.crt.dos.unicode.static.format.printf)]
_vscprintf_p:([nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	(void)format;
	(void)args;
	/* TODO */
	return 0;
}

[ATTR_LIBC_PRINTF_P(1, 0)][ATTR_WUNUSED]
[section(.text.crt.dos.unicode.locale.format.printf)]
_vscprintf_p_l:([nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T {
	(void)locale;
	return _vscprintf_p(format, args);
}

[ATTR_LIBC_PRINTF(1, 3)][ATTR_WUNUSED]
[section(.text.crt.dos.unicode.locale.format.printf)]
_scprintf_l:([nonnull] char const *__restrict format, $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vscprintf_l))}

[section(.text.crt.dos.unicode.static.format.printf)]
[ATTR_LIBC_PRINTF_P(1, 2)][ATTR_WUNUSED]
_scprintf_p:([nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vscprintf_p))}

[section(.text.crt.dos.unicode.locale.format.printf)]
[ATTR_LIBC_PRINTF_P(1, 3)][ATTR_WUNUSED]
_scprintf_p_l:([nonnull] char const *__restrict format, $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vscprintf_p_l))}

%
@@WARNING: This function returns the number of written character. - Not the required buffer size!
[ATTR_LIBC_PRINTF(3, 0)]
[section(.text.crt.dos.unicode.static.format.printf)]
_vsnprintf:([outp_opt(min(return,bufsize))] char *__restrict buf, $size_t bufsize,
            [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	__STDC_INT_AS_SIZE_T result;
	result = vsnprintf(buf, bufsize, format, args);
	if (result > bufsize)
		result = bufsize;
	return result;
}

[section(.text.crt.dos.unicode.locale.format.printf)]
[ATTR_LIBC_PRINTF(3, 0)][alias(_vsprintf_s_l)]
_vsnprintf_l:([outp_opt(min(return,bufsize))] char *__restrict buf, $size_t bufsize,
              [nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T {
	(void)locale;
	return _vsnprintf(buf, bufsize, format, args);
}

[ATTR_LIBC_PRINTF(3, 0)][section(.text.crt.dos.unicode.static.format.printf)]
_vsnprintf_c:([outp_opt(min(return,bufsize))] char *__restrict buf, $size_t bufsize, [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T = _vsnprintf;

[ATTR_LIBC_PRINTF(3, 0)][section(.text.crt.dos.unicode.locale.format.printf)]
_vsnprintf_c_l:([outp_opt(min(return,bufsize))] char *__restrict buf, $size_t bufsize, [nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T = _vsnprintf_l;

[ATTR_LIBC_PRINTF(4, 0)][section(.text.crt.dos.unicode.static.format.printf)]
_vsnprintf_s:([outp_opt(min(return,bufsize,buflen))] char *__restrict buf, $size_t bufsize, $size_t buflen,
              [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	(void)buflen;
	return _vsnprintf(buf, bufsize, format, args);
}

[ATTR_LIBC_PRINTF(4, 0)][section(.text.crt.dos.unicode.locale.format.printf)]
_vsnprintf_s_l:([outp_opt(min(return,bufsize,buflen))] char *__restrict buf, $size_t bufsize, $size_t buflen,
                [nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T {
	(void)buflen;
	(void)locale;
	return _vsnprintf(buf, bufsize, format, args);
}

[ATTR_LIBC_PRINTF(3, 4)][section(.text.crt.dos.unicode.static.format.printf)]
_snprintf:([outp_opt(min(return,buf,bufsize))] char *__restrict buf, $size_t bufsize, [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vsnprintf))}

[ATTR_LIBC_PRINTF(3, 5)][section(.text.crt.dos.unicode.locale.format.printf)]
_snprintf_l:([outp_opt(min(return,buf,bufsize))] char *__restrict buf, $size_t bufsize, [nonnull] char const *__restrict format, $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vsnprintf_l))}

[ATTR_LIBC_PRINTF(3, 4)][section(.text.crt.dos.unicode.static.format.printf)]
_snprintf_c:([outp_opt(min(return,buf,bufsize))] char *__restrict buf, $size_t bufsize, [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vsnprintf_c))}

[ATTR_LIBC_PRINTF(3, 5)][section(.text.crt.dos.unicode.locale.format.printf)]
_snprintf_c_l:([outp_opt(min(return,buf,bufsize))] char *__restrict buf, $size_t bufsize, [nonnull] char const *__restrict format, $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vsnprintf_c_l))}

[ATTR_LIBC_PRINTF(4, 5)][section(.text.crt.dos.unicode.static.format.printf)]
_snprintf_s:([outp_opt(min(return,buf,bufsize,buflen))] char *__restrict buf, $size_t bufsize, $size_t buflen, [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vsnprintf_s))}

[ATTR_LIBC_PRINTF(4, 6)][section(.text.crt.dos.unicode.locale.format.printf)]
_snprintf_s_l:([outp_opt(min(return,buf,bufsize,buflen))] char *__restrict buf, $size_t bufsize, $size_t buflen, [nonnull] char const *__restrict format, $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vsnprintf_s_l))}

%
%[default_impl_section(.text.crt.dos.unicode.locale.format.printf)]
[cp_stdio][ATTR_LIBC_PRINTF(1, 0)][alias(_vprintf_s_l)]
[same_impl][requires($has_function(vprintf))]
_vprintf_l:([nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T {
	(void)locale;
	return vprintf(format, args);
}
[cp_stdio][ATTR_LIBC_PRINTF(1, 0)]
_vprintf_s_l:([nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T = _vprintf_l;

%[default_impl_section(.text.crt.dos.unicode.static.format.printf)]
[cp_stdio][ATTR_LIBC_PRINTF_P(1, 0)]
[same_impl][requires(!defined(__NO_STDSTREAMS) && $has_function(_vfprintf_p))]
[dependency_include(<local/stdstreams.h>)]
_vprintf_p:([nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	return _vfprintf_p(@__LOCAL_stdout@, format, args);
}

%[default_impl_section(.text.crt.dos.unicode.locale.format.printf)]
[cp_stdio][ATTR_LIBC_PRINTF_P(1, 0)]
[same_impl][requires($has_function(_vprintf_p))]
_vprintf_p_l:([nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T {
	(void)locale;
	return _vprintf_p(format, args);
}

[cp_stdio][ATTR_LIBC_PRINTF(1, 3)][section(.text.crt.dos.unicode.locale.format.printf)]
_printf_l:([nonnull] char const *__restrict format, $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vprintf_l))}

[cp_stdio][ATTR_LIBC_PRINTF(1, 3)][section(.text.crt.dos.unicode.locale.format.printf)]
_printf_s_l:([nonnull] char const *__restrict format, $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vprintf_s_l))}

[cp_stdio][ATTR_LIBC_PRINTF_P(1, 2)][section(.text.crt.dos.unicode.static.format.printf)]
_printf_p:([nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vprintf_p))}

[cp_stdio][ATTR_LIBC_PRINTF_P(1, 3)][section(.text.crt.dos.unicode.locale.format.printf)]
_printf_p_l:([nonnull] char const *__restrict format, $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vprintf_p_l))}

%
[cp_stdio][ATTR_LIBC_PRINTF(2, 0)][alias(_vfprintf_s_l)]
[same_impl][requires($has_function(vfprintf))]
[section(.text.crt.dos.unicode.locale.format.printf)]
_vfprintf_l:([nonnull] $FILE *__restrict stream,
             [nonnull] char const *__restrict format,
             $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T {
	(void)locale;
	return vfprintf(stream, format, args);
}

[cp_stdio][ATTR_LIBC_PRINTF(2, 0)]
[section(.text.crt.dos.unicode.locale.format.printf)]
_vfprintf_s_l:([nonnull] $FILE *__restrict stream,
               [nonnull] char const *__restrict format,
               $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T = _vfprintf_l;

[cp_stdio][ATTR_LIBC_PRINTF_P(2, 0)]
[same_impl][requires($has_function(fwrite))]
[section(.text.crt.dos.unicode.static.format.printf)]
_vfprintf_p:([nonnull] $FILE *__restrict stream,
             [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	/* TODO */
	(void)stream;
	(void)format;
	(void)args;
	return 0;
}

[section(.text.crt.dos.unicode.locale.format.printf)]
[cp_stdio][ATTR_LIBC_PRINTF_P(2, 0)]
[same_impl][requires($has_function(_vfprintf_p))]
_vfprintf_p_l:([nonnull] $FILE *__restrict stream,
               [nonnull] char const *__restrict format, $locale_t locale, $va_list args) -> __STDC_INT_AS_SIZE_T {
	(void)locale;
	return _vfprintf_p(stream, format, args);
}

[cp_stdio][ATTR_LIBC_PRINTF(2, 4)][section(.text.crt.dos.unicode.locale.format.printf)]
_fprintf_l:([nonnull] $FILE *__restrict stream,
            [nonnull] char const *__restrict format,
            $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vfprintf_l))}

[cp_stdio][ATTR_LIBC_PRINTF(2, 4)][section(.text.crt.dos.unicode.locale.format.printf)]
_fprintf_s_l:([nonnull] $FILE *__restrict stream,
              [nonnull] char const *__restrict format,
              $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vfprintf_s_l))}

[cp_stdio][ATTR_LIBC_PRINTF_P(2, 3)][section(.text.crt.dos.unicode.static.format.printf)]
_fprintf_p:([nonnull] $FILE *__restrict stream,
            [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vfprintf_p))}

[cp_stdio][ATTR_LIBC_PRINTF_P(2, 4)][section(.text.crt.dos.unicode.locale.format.printf)]
_fprintf_p_l:([nonnull] $FILE *__restrict stream,
              [nonnull] char const *__restrict format,
              $locale_t locale, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(_vfprintf_p_l))}

%
%#ifdef __USE_DOS_SLIB
[cp][section(.text.crt.dos.FILE.locked.access)]
fopen_s:([nonnull] $FILE **pstream,
         [nonnull] char const *filename,
         [nonnull] char const *modes) -> errno_t;

[cp][section(.text.crt.dos.FILE.locked.access)]
freopen_s:([nonnull] $FILE **pstream,
           [nonnull] char const *filename,
           [nonnull] char const *modes,
           [nonnull] $FILE *oldstream) -> errno_t;

[section(.text.crt.dos.fs.utility)]
tmpnam_s:([outp(bufsize)] char *__restrict buf, rsize_t bufsize) -> errno_t;

%
[dependency_include(<parts/errno.h>)]
[same_impl][requires($has_function(clearerr))][noexport]
[section(.text.crt.dos.FILE.locked.utility)]
clearerr_s:([nonnull] $FILE *__restrict stream) -> errno_t {
	if (!stream)
		return __EINVAL;
	clearerr(stream);
	return 0;
}

[cp][dependency_include(<parts/errno.h>)]
[same_impl][requires($has_function(tmpfile))][noexport]
[section(.text.crt.dos.FILE.locked.access)]
tmpfile_s:([nonnull] $FILE **pstream) -> errno_t {
	if (!pstream)
		return @__EINVAL@;
	*pstream = tmpfile();
	if (!*pstream)
		return @__libc_geterrno_or@(@__ENOMEM@);
	return 0;
}

[cp][ATTR_WUNUSED][noexport]
[same_impl][requires($has_function(fread))]
[dependency_include(<parts/errno.h>)]
[section(.text.crt.dos.FILE.locked.read.read)]
fread_s:([outp(min(return*elemsize,elemcount*elemsize,bufsize))] void *__restrict buf, $size_t bufsize,
         $size_t elemsize, $size_t elemcount, [nonnull] $FILE *__restrict stream) -> $size_t {
	bufsize = elemsize ? bufsize / elemsize : 0;
	return fread(buf, elemsize, bufsize < elemcount ? bufsize : elemcount, stream);
}

%[default_impl_section(.text.crt.dos.FILE.locked.read.read)]
[cp][ATTR_WUNUSED]
[requires_include(<__crt.h>)]
[same_impl][requires(!defined(__NO_STDSTREAMS) && $has_function(fgets))]
[dependency_include(<local/stdstreams.h>)]
gets_s:([outp(min(strlen(return),bufsize))] char *__restrict buf, rsize_t bufsize) -> char * {
	return fgets(buf, (int)(unsigned int)bufsize, @__LOCAL_stdin@);
}

/* TODO: Header implementations of all of these printf functions */
%[default_impl_section(.text.crt.dos.FILE.locked.write.printf)]
[cp_stdio][ATTR_LIBC_PRINTF(1, 2)] printf_s:([nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T = printf;
[cp_stdio][ATTR_LIBC_PRINTF(1, 0)] vprintf_s:([nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T = vprintf;
[cp_stdio][ATTR_LIBC_PRINTF(2, 3)] fprintf_s:([nonnull] $FILE *__restrict stream, [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T = fprintf;
[cp_stdio][ATTR_LIBC_PRINTF(2, 0)] vfprintf_s:([nonnull] $FILE *__restrict stream, [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T = vfprintf;
%[default_impl_section(.text.crt.dos.unicode.static.format.printf)]
[ATTR_LIBC_PRINTF(3, 4)] sprintf_s:([outp_opt(min(return,buflen))] char *__restrict buf, $size_t buflen, [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T = snprintf; /* XXX: This binding probably isn't correct... */
[ATTR_LIBC_PRINTF(3, 0)] vsprintf_s:([outp_opt(min(return,buflen))] char *__restrict buf, $size_t buflen, [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T = vsnprintf; /* XXX: This binding probably isn't correct... */
%[default_impl_section(.text.crt.dos.FILE.locked.read.scanf)]
[cp_stdio][ATTR_LIBC_PRINTF(2, 3)] fscanf_s:([nonnull] $FILE *__restrict stream, [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(vfscanf_s))}
[cp_stdio][ATTR_LIBC_PRINTF(2, 0)] vfscanf_s:([nonnull] $FILE *__restrict stream, [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T;
%[default_impl_section(.text.crt.dos.unicode.static.format.scanf)]
[cp_stdio][ATTR_LIBC_PRINTF(1, 2)] scanf_s:([nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(vscanf_s))}
[cp_stdio][ATTR_LIBC_PRINTF(1, 0)] vscanf_s:([nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T;
[ATTR_LIBC_PRINTF(2, 3)] sscanf_s:([nonnull] char const *__restrict input, [nonnull] char const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T %{auto_block(printf(vsscanf_s))}
[ATTR_LIBC_PRINTF(2, 0)] vsscanf_s:([nonnull] char const *__restrict input, [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T;
%[default_impl_section(.text.crt.dos.unicode.static.format.printf)]
[ATTR_LIBC_PRINTF(4, 0)] vsnprintf_s:([outp_opt(min(return,buflen,bufsize))] char *__restrict buf, $size_t bufsize, $size_t buflen, [nonnull] char const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T;

%#endif /* __USE_DOS_SLIB */

%
%#ifndef _CRT_WPERROR_DEFINED
%#define _CRT_WPERROR_DEFINED 1
%[default_impl_section(.text.crt.dos.errno.utility)]
[cp_stdio][wchar][ATTR_COLD] _wperror:($wchar_t const *__restrict message);
%#endif /* !_CRT_WPERROR_DEFINED */
%
%#endif /* _STDIO_DEFINED */


%[default_impl_section(.text.crt.dos.FILE.unlocked.read.getc)]
[cp_stdio][noexport][nocrt][alias(getc_unlocked, getc, fgetc)]
_fgetc_nolock:([nonnull] $FILE *__restrict stream) -> int = fgetc_unlocked;

%[default_impl_section(.text.crt.dos.FILE.unlocked.write.putc)]
[cp_stdio][noexport][nocrt][alias(putc_unlocked, putc, fputc)]
_fputc_nolock:(int ch, [nonnull] $FILE *__restrict stream) -> int = fputc_unlocked;

%[default_impl_section(.text.crt.dos.FILE.unlocked.read.getc)]
[cp_stdio][noexport][nocrt][alias(getc_unlocked, getc, fgetc)]
_getc_nolock:([nonnull] $FILE *__restrict stream) -> int = fgetc_unlocked;

%[default_impl_section(.text.crt.dos.FILE.unlocked.write.putc)]
[cp_stdio][noexport][nocrt][alias(putc_unlocked, putc, fputc)]
_putc_nolock:(int ch, [nonnull] $FILE *__restrict stream) -> int = fputc_unlocked;

%[default_impl_section(.text.crt.dos.FILE.unlocked.read.getc)]
[cp_stdio][noexport][nocrt] _getchar_nolock:() -> int = getchar_unlocked;

%[default_impl_section(.text.crt.dos.FILE.unlocked.write.putc)]
[cp_stdio][noexport][nocrt] _putchar_nolock:(int ch) -> int = putchar_unlocked;

%[default_impl_section(.text.crt.dos.FILE.locked.utility)]
[cp] _lock_file:([nonnull] $FILE *__restrict stream) = flockfile;
 _unlock_file:([nonnull] $FILE *__restrict stream) = funlockfile;
%[default_impl_section(.text.crt.dos.FILE.unlocked.access)]
[stdio_throws] _fclose_nolock:([nonnull] $FILE *__restrict stream) -> int = fclose;

%[default_impl_section(.text.crt.dos.FILE.unlocked.write.utility)]
[cp_stdio][preferred_alias(fflush_unlocked, _fflush_nolock)]
_fflush_nolock:([nonnull] $FILE *__restrict stream) -> int = fflush;

%[default_impl_section(.text.crt.dos.FILE.unlocked.read.read)]
[cp_stdio][ATTR_WUNUSED][alias(fread, fread_s)][noexport]
_fread_nolock:([outp(min(return*elemsize,elemcount*elemsize))] void *__restrict buf, $size_t elemsize, $size_t elemcount, [nonnull] $FILE *__restrict stream) -> $size_t = fread_unlocked;

%[default_impl_section(.text.crt.dos.FILE.unlocked.write.write)]
[cp_stdio][ATTR_WUNUSED][alias(fwrite, fwrite_s)][noexport]
_fwrite_nolock:([inp(min(return*elemsize,elemcount*elemsize))] void const *__restrict buf, $size_t elemsize, $size_t elemcount, [nonnull] $FILE *__restrict stream) -> $size_t = fwrite_unlocked;

%[default_impl_section(.text.crt.dos.FILE.unlocked.read.read)]
[cp_stdio][ATTR_WUNUSED]
[same_impl][noexport][requires($has_function(fread_unlocked))]
_fread_nolock_s:([outp(min(return*elemsize,elemcount*elemsize,bufsize))] void *__restrict buf, $size_t bufsize, $size_t elemsize, $size_t elemcount, [nonnull] $FILE *__restrict stream) -> $size_t {
	bufsize = elemsize ? bufsize / elemsize : 0;
	return fread_unlocked(buf, elemsize, bufsize < elemcount ? bufsize : elemcount, stream);
}

%[default_impl_section(.text.crt.dos.FILE.unlocked.seek.seek)]
[stdio_throws]
[if(__SIZEOF_LONG__ == 4), alias(fseeko)]
[if(__SIZEOF_LONG__ == 8), alias(fseeko64, _fseeki64)]
_fseek_nolock:([nonnull] $FILE *__restrict stream, long int off, int whence) = fseek;

[stdio_throws]
[if(__SIZEOF_LONG__ == 4), alias(ftello)]
[if(__SIZEOF_LONG__ == 8), alias(ftello64, _ftelli64)]
_ftell_nolock:([nonnull] $FILE *__restrict stream) -> long int = ftell;

[stdio_throws]
_fseeki64_nolock:([nonnull] $FILE *__restrict stream, $off64_t off, int whence) -> int = fseeko64;

[stdio_throws]
_ftelli64_nolock:([nonnull] $FILE *__restrict stream) -> $off64_t = ftello64;

[section(.text.crt.dos.FILE.unlocked.read.getc)]
_ungetc_nolock:(int ch, [nonnull] $FILE *__restrict stream) -> int = ungetc;

[section(.text.crt.dos.FILE.locked.read.getc)]
[cp_stdio][nocrt] fgetchar:() -> int = getchar;

[section(.text.crt.dos.FILE.locked.write.putc)]
[cp_stdio][nocrt] fputchar:(int ch) -> int = putchar;

[section(.text.crt.FILE.locked.write.utility)]
[cp_stdio][nocrt] flushall:() -> int = _flushall;

[section(.text.crt.dos.FILE.utility)]
[cp][nocrt] rmtmp:(*) = _rmtmp;

%{
#define SYS_OPEN     _SYS_OPEN

}


%#ifndef _WSTDIO_DEFINED
%#define _WSTDIO_DEFINED 1

%{
#ifndef WEOF
#if __SIZEOF_WCHAR_T__ == 4
#define WEOF (__CCAST(__WINT_TYPE__)0xffffffffu)
#else /* __SIZEOF_WCHAR_T__ == 4 */
#define WEOF (__CCAST(__WINT_TYPE__)0xffff)
#endif /* __SIZEOF_WCHAR_T__ != 4 */
#endif /* !WEOF */

/* Define 'wchar_t' */
#ifndef __wchar_t_defined
#define __wchar_t_defined 1
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */
}

%[insert:extern(fgetwc)]
%[insert:extern(fputwc)]
%[insert:extern(getwc)]
%[insert:extern(getwchar)]
%[insert:extern(putwc)]
%[insert:extern(putwchar)]
%[insert:extern(ungetwc)]
%[insert:extern(fgetws)]
%[insert:extern(fputws)]
%[insert:extern(vfwprintf)]
%[insert:extern(fwprintf)]
%[insert:extern(vfwscanf)]
%[insert:extern(fwscanf)]
%[insert:extern(vwprintf)]
%[insert:extern(wprintf)]
%[insert:extern(vwscanf)]
%[insert:extern(wscanf)]
%[insert:extern(vswscanf)]
%[insert:extern(swscanf)]

%#ifdef __USE_DOS_SLIB
%[insert:extern(vswprintf_s)]
%[insert:extern(swprintf_s)]
%[insert:extern(vfwprintf_s)]
%[insert:extern(fwprintf_s)]
%[insert:extern(vwprintf_s)]
%[insert:extern(wprintf_s)]
%[insert:extern(vswscanf_s)]
%[insert:extern(swscanf_s)]
%[insert:extern(vfwscanf_s)]
%[insert:extern(fwscanf_s)]
%[insert:extern(vwscanf_s)]
%[insert:extern(wscanf_s)]
%#endif /* __USE_DOS_SLIB */
%[insert:extern(_vscwprintf)]
%[insert:extern(_scwprintf)]
%[insert:extern(_vscwprintf_p)]
%[insert:extern(_scwprintf_p)]
%[insert:extern(_vscwprintf_l)]
%[insert:extern(_scwprintf_l)]
%[insert:extern(_vscwprintf_p_l)]
%[insert:extern(_scwprintf_p_l)]
%[insert:extern(_vswprintf_c)]
%[insert:extern(_swprintf_c)]
%[insert:extern(_vsnwprintf_s)]
%[insert:extern(_snwprintf_s)]
%[insert:extern(_vfwprintf_p)]
%[insert:extern(_fwprintf_p)]
%[insert:extern(_vwprintf_p)]
%[insert:extern(_wprintf_p)]
%[insert:extern(_vswprintf_p)]
%[insert:extern(_swprintf_p)]
%[insert:extern(_vwprintf_l)]
%[insert:extern(_wprintf_l)]
%[insert:extern(_vwprintf_p_l)]
%[insert:extern(_wprintf_p_l)]
%[insert:extern(_vwprintf_s_l)]
%[insert:extern(_wprintf_s_l)]
%[insert:extern(_vfwprintf_l)]
%[insert:extern(_fwprintf_l)]
%[insert:extern(_vfwprintf_p_l)]
%[insert:extern(_fwprintf_p_l)]
%[insert:extern(_vfwprintf_s_l)]
%[insert:extern(_fwprintf_s_l)]
%[insert:extern(_vswprintf_c_l)]
%[insert:extern(_swprintf_c_l)]
%[insert:extern(_vswprintf_p_l)]
%[insert:extern(_swprintf_p_l)]
%[insert:extern(_vswprintf_s_l)]
%[insert:extern(_swprintf_s_l)]
%[insert:extern(_vsnwprintf_l)]
%[insert:extern(_snwprintf_l)]
%[insert:extern(_vsnwprintf_s_l)]
%[insert:extern(_snwprintf_s_l)]
%[insert:extern(_fwscanf_l)]
%[insert:extern(_fwscanf_s_l)]
%[insert:extern(_swscanf_l)]
%[insert:extern(_swscanf_s_l)]
%[insert:extern(_snwscanf)]
%[insert:extern(_snwscanf_l)]
%[insert:extern(_snwscanf_s)]
%[insert:extern(_snwscanf_s_l)]
%[insert:extern(_wscanf_l)]
%[insert:extern(_wscanf_s_l)]
%[insert:extern(_wfsopen)]
%[insert:extern(_wfdopen)]
%[insert:extern(_wfopen_s)]
%[insert:extern(_wfreopen_s)]
%[insert:extern(_wfopen)]
%[insert:extern(_wfreopen)]
%[insert:extern(_fgetwchar)]
%[insert:extern(_fputwchar)]
%[insert:extern(_getws_s)]
%[insert:extern(_putws)]
%[insert:extern(_wtempnam)]
%#ifndef _CRT_WPERROR_DEFINED
%#define _CRT_WPERROR_DEFINED
%[insert:extern(_wperror)]
%#endif  /* _CRT_WPERROR_DEFINED */
%[insert:extern(_wpopen)]
%[insert:extern(_wremove)]
%[insert:extern(_wtmpnam_s)]
%[insert:extern(_fgetwc_nolock)]
%[insert:extern(_fputwc_nolock)]
%[insert:extern(_ungetwc_nolock)]
%[insert:extern(_getwc_nolock)]
%[insert:extern(_putwc_nolock)]
%#endif /* !_WSTDIO_DEFINED */


%#endif /* __CC__ */
%#endif /* __USE_DOS */
%

//__STDC_INT_AS_SSIZE_T


%{

#if defined(__USE_XOPEN) && !defined(__USE_XOPEN2K) && !defined(__USE_GNU)
#include <getopt.h>
#endif

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STDIO_H)
#include <parts/uchar/stdio.h>
#endif
#endif /* __USE_UTF */

}

