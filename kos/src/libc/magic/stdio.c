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
%(c_prefix){
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/stdio.h) */
/* (#) Portability: DJGPP         (/include/stdio.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/stdio.h) */
/* (#) Portability: FreeBSD       (/include/stdio.h) */
/* (#) Portability: GNU C Library (/libio/stdio.h) */
/* (#) Portability: MSVC          (/include/stdio.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/stdio.h) */
/* (#) Portability: NetBSD        (/include/stdio.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/stdio.h) */
/* (#) Portability: OpenBSD       (/include/stdio.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/stdio.h) */
/* (#) Portability: PDCLib        (/include/stdio.h) */
/* (#) Portability: Windows Kits  (/ucrt/stdio.h) */
/* (#) Portability: avr-libc      (/include/stdio.h) */
/* (#) Portability: diet libc     (/include/stdio.h) */
/* (#) Portability: libbsd        (/include/bsd/stdio.h) */
/* (#) Portability: libc4/5       (/include/stdio.h) */
/* (#) Portability: libc6         (/include/stdio.h) */
/* (#) Portability: libcmini      (/include/stdio.h) */
/* (#) Portability: mintlib       (/include/stdio.h) */
/* (#) Portability: musl libc     (/include/stdio.h) */
/* (#) Portability: uClibc        (/include/stdio.h) */
}

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

%[define_ccompat_header("cstdio")]

%[define_replacement(FILE     = __FILE)]
%[define_replacement(fd_t     = __fd_t)]
%[define_replacement(atflag_t = __atflag_t)]
%[define_replacement(off_t    = "__FS_TYPE(off)")]
%[define_replacement(off32_t  = __off32_t)]
%[define_replacement(off64_t  = __off64_t)]
%[define_replacement(fpos_t   = "__FS_TYPE(fpos)")]
%[define_replacement(fpos32_t = __fpos32_t)]
%[define_replacement(fpos64_t = __fpos64_t)]
%[define_replacement(pos32_t  = __pos32_t)]
%[define_replacement(pos64_t  = __pos64_t)]
%[define_replacement(cookie_io_functions_t = _IO_cookie_io_functions_t)]
%[define_replacement(locale_t = __locale_t)]
%[define_replacement(rsize_t  = __SIZE_TYPE__)]

/* These are defined in <libc/template/stdstreams.h> */
%[define_replacement(stdin  = __LOCAL_stdin)]
%[define_replacement(stdout = __LOCAL_stdout)]
%[define_replacement(stderr = __LOCAL_stderr)]

%[define_replacement(SEEK_SET  = __SEEK_SET)]
%[define_replacement(SEEK_CUR  = __SEEK_CUR)]
%[define_replacement(SEEK_END  = __SEEK_END)]
%[define_replacement(SEEK_DATA = __SEEK_DATA)]
%[define_replacement(SEEK_HOLE = __SEEK_HOLE)]

%[define_replacement(STDIN_FILENO = __STDIN_FILENO)]
%[define_replacement(STDOUT_FILENO = __STDOUT_FILENO)]
%[define_replacement(STDERR_FILENO = __STDERR_FILENO)]
%[define_replacement(F_OK = __F_OK)]
%[define_replacement(X_OK = __X_OK)]
%[define_replacement(W_OK = __W_OK)]
%[define_replacement(R_OK = __R_OK)]
%[define_replacement(_IOFBF = ___IOFBF)]
%[define_replacement(_IOLBF = ___IOLBF)]
%[define_replacement(_IONBF = ___IONBF)]
%[define_replacement(BUFSIZ = __BUFSIZ)]
%[define_replacement(EOF = __EOF)]

%[assume_defined_in_kos_userspace(stdin, __LOCAL_stdin)]
%[assume_defined_in_kos_userspace(stdout, __LOCAL_stdout)]
%[assume_defined_in_kos_userspace(stderr, __LOCAL_stderr)]
%[assume_defined_in_kos_userspace(stdtty, __LOCAL_stdtty)]

%[assume_defined_in_kos(SEEK_SET, __SEEK_SET)]
%[assume_defined_in_kos(SEEK_CUR, __SEEK_CUR)]
%[assume_defined_in_kos(SEEK_END, __SEEK_END)]


%(auto_source){
#include "../libc/globals.h"
}

%{
#include <features.h>

}%[insert:prefix(
#include <asm/crt/stdio.h>
)]%[insert:prefix(
#include <asm/os/limits.h> /* __IOV_MAX */
)]%[insert:prefix(
#include <asm/os/oflags.h>
)]%[insert:prefix(
#include <asm/os/stdio.h>
)]%[insert:prefix(
#include <bits/crt/stdio.h> /* __fpos32_t, __fpos64_t */
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

}%[insert:prefix(
#include <libio.h>
)]%{

#ifdef __USE_KOS
#include <bits/crt/format-printer.h>
#endif /* __USE_KOS */

#ifdef __USE_DOS
#include <bits/crt/sys_errlist.h>
#include <xlocale.h>
#endif /* __USE_DOS */

#ifdef __CRT_CYG_PRIMARY
#include <sys/reent.h>
#endif /* __CRT_CYG_PRIMARY */

__SYSDECL_BEGIN

/* The possibilities for the third argument to `setvbuf()'. */
#ifdef ___IOFBF
#define _IOFBF ___IOFBF /* Fully buffered. */
#endif /* ___IOFBF */
#ifdef ___IOLBF
#define _IOLBF ___IOLBF /* Line buffered. */
#endif /* ___IOLBF */
#ifdef ___IONBF
#define _IONBF ___IONBF /* No buffering. */
#endif /* ___IONBF */

/* Default buffer size.  */
#ifndef BUFSIZ
#define BUFSIZ __BUFSIZ
#endif /* !BUFSIZ */

#ifndef EOF
#define EOF __EOF
#endif /* !EOF */

#if !defined(SEEK_SET) && defined(__SEEK_SET)
#define SEEK_SET __SEEK_SET /* Seek from beginning of file. */
#endif /* !SEEK_SET && __SEEK_SET */
#if !defined(SEEK_CUR) && defined(__SEEK_CUR)
#define SEEK_CUR __SEEK_CUR /* Seek from current position. */
#endif /* !SEEK_CUR && __SEEK_CUR */
#if !defined(SEEK_END) && defined(__SEEK_END)
#define SEEK_END __SEEK_END /* Seek from end of file. */
#endif /* !SEEK_END && __SEEK_END */
#if defined(__USE_GNU) || defined(__USE_SOLARIS)
#if !defined(SEEK_DATA) && defined(__SEEK_DATA)
#define SEEK_DATA __SEEK_DATA /* Seek to next data. */
#endif /* !SEEK_DATA && __SEEK_DATA */
#if !defined(SEEK_HOLE) && defined(__SEEK_HOLE)
#define SEEK_HOLE __SEEK_HOLE /* Seek to next hole. */
#endif /* !SEEK_HOLE && __SEEK_HOLE */
#endif /* __USE_GNU || __USE_SOLARIS */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifdef __CRT_DOS_PRIMARY
#define P_tmpdir "\\"
#else /* __CRT_DOS_PRIMARY */
#define P_tmpdir "/tmp"
#endif /* !__CRT_DOS_PRIMARY */
#endif /* __USE_MISC || __USE_XOPEN */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

/* Minimum buffer size for temporary file names */
#if !defined(L_tmpnam) && defined(__L_tmpnam)
#define L_tmpnam __L_tmpnam
#endif /* !L_tmpnam && __L_tmpnam */

/* Recommended buffer size for file names. */
#if !defined(FILENAME_MAX) && defined(__FILENAME_MAX)
#define FILENAME_MAX __FILENAME_MAX
#endif /* !FILENAME_MAX && __FILENAME_MAX */

/* Min # of unique temporary file names what can be generated by `tmpnam()' */
#if !defined(TMP_MAX) && defined(__TMP_MAX)
#define TMP_MAX __TMP_MAX
#endif /* !TMP_MAX && __TMP_MAX */

#ifdef __USE_POSIX
/* - Max # of characters in the string returned by `ctermid()'
 * - Buffer size that must be passed to `ctermid_r()' */
#if !defined(L_ctermid) && defined(__L_ctermid)
#define L_ctermid __L_ctermid
#endif /* !L_ctermid && __L_ctermid */

#if !defined(__USE_XOPEN2K) || defined(__USE_GNU)
/* Max # of characters in the string returned by `cuserid()' */
#if !defined(L_cuserid) && defined(__L_cuserid)
#define L_cuserid __L_cuserid
#endif /* !L_cuserid && __L_cuserid */
#endif /* !__USE_XOPEN2K || __USE_GNU */
#endif /* __USE_POSIX */

#ifndef FOPEN_MAX
#ifdef __CRT_DOS_PRIMARY
#define FOPEN_MAX 20
#else /* __CRT_DOS_PRIMARY */
#define FOPEN_MAX 16
#endif /* !__CRT_DOS_PRIMARY */
#endif /* !FOPEN_MAX */

#ifndef IOV_MAX
/* [default:_POSIX_UIO_MAXIOV] Max # of elements in a `struct iovec' vector. */
#if defined(__IOV_MAX) && __IOV_MAX != -1
#define IOV_MAX __IOV_MAX
#else /* __IOV_MAX != -1 */
#define IOV_MAX 16 /* 16 == _XOPEN_IOV_MAX */
#endif /* __IOV_MAX == -1 */
#endif /* !IOV_MAX */

#ifdef __USE_GNU
#if !defined(RENAME_NOREPLACE) && defined(__RENAME_NOREPLACE)
#define RENAME_NOREPLACE __RENAME_NOREPLACE /* Don't overwrite target */
#endif /* !RENAME_NOREPLACE && __RENAME_NOREPLACE */
#if !defined(RENAME_EXCHANGE) && defined(__RENAME_EXCHANGE)
#define RENAME_EXCHANGE  __RENAME_EXCHANGE  /* Exchange source and dest */
#endif /* !RENAME_EXCHANGE && __RENAME_EXCHANGE */
#if !defined(RENAME_WHITEOUT) && defined(__RENAME_WHITEOUT)
#define RENAME_WHITEOUT  __RENAME_WHITEOUT  /* Whiteout source */
#endif /* !RENAME_WHITEOUT && __RENAME_WHITEOUT */
#endif /* __USE_GNU */

#ifdef __USE_KOS
#if !defined(AT_RENAME_NOREPLACE) && defined(__RENAME_NOREPLACE)
#define AT_RENAME_NOREPLACE __RENAME_NOREPLACE /* Don't overwrite target */
#endif /* !AT_RENAME_NOREPLACE && __RENAME_NOREPLACE */
#if !defined(AT_RENAME_EXCHANGE) && defined(__RENAME_EXCHANGE)
#define AT_RENAME_EXCHANGE  __RENAME_EXCHANGE  /* Exchange source and dest */
#endif /* !AT_RENAME_EXCHANGE && __RENAME_EXCHANGE */
#if !defined(AT_RENAME_WHITEOUT) && defined(__RENAME_WHITEOUT)
#define AT_RENAME_WHITEOUT  __RENAME_WHITEOUT  /* Whiteout source */
#endif /* !AT_RENAME_WHITEOUT && __RENAME_WHITEOUT */
#if !defined(AT_RENAME_MOVETODIR) && defined(__RENAME_MOVETODIR)
#define AT_RENAME_MOVETODIR __RENAME_MOVETODIR /* If `newpath' is a directory, move `oldpath' into it. */
#endif /* !AT_RENAME_MOVETODIR && __RENAME_MOVETODIR */
#endif /* __USE_KOS */


#ifdef __CC__
#ifndef __std_size_t_defined
#define __std_size_t_defined
__NAMESPACE_STD_BEGIN
typedef __SIZE_TYPE__ size_t;
__NAMESPACE_STD_END
#endif /* !__std_size_t_defined */
#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef __USE_XOPEN2K8
#ifndef __off_t_defined
#define __off_t_defined
typedef __FS_TYPE(off) off_t;
#endif /* !__off_t_defined */

#ifndef __ssize_t_defined
#define __ssize_t_defined
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

#ifdef __USE_LARGEFILE64
#ifndef __off64_t_defined
#define __off64_t_defined
typedef __off64_t off64_t;
#endif /* !__off64_t_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN2K8 */

#ifndef __std_fpos_t_defined
#define __std_fpos_t_defined
__NAMESPACE_STD_BEGIN
typedef __FS_TYPE(fpos) fpos_t;
__NAMESPACE_STD_END
#endif /* !__std_fpos_t_defined */
#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __fpos_t_defined
#define __fpos_t_defined
__NAMESPACE_STD_USING(fpos_t)
#endif /* !__fpos_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef __USE_LARGEFILE64
#ifndef __fpos64_t_defined
#define __fpos64_t_defined
typedef __fpos64_t fpos64_t;
#endif /* !__fpos64_t_defined */
#endif /* __USE_LARGEFILE64 */

#ifndef __std_FILE_defined
#define __std_FILE_defined
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */
#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __FILE_defined
#define __FILE_defined
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */


/************************************************************************/
/* STDIO standard streams (stdin, stdout, stderr)                       */
/************************************************************************/

/* Define symbols needed for stdio FILE access */
#if defined(__CYG_REENT)
/* nothing */
#elif !defined(___iob_defined) && defined(__CRT_HAVE__iob)
#include <bits/crt/io-file.h>
#define ___iob_defined
__CSDECLARE2(,__FILE _iob[],_iob)
#ifndef ____iob_func_defined
#define ____iob_func_defined
#define __iob_func() (_iob)
#endif /* !____iob_func_defined */
#elif !defined(____p__iob_defined) && defined(__CRT_HAVE___p__iob)
#include <bits/crt/io-file.h>
#define ____p__iob_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__FILE *,__NOTHROW,__p__iob,(void),())
#ifndef ____iob_func_defined
#define ____iob_func_defined
#define __iob_func __p__iob
#endif /* !____iob_func_defined */
#elif !defined(____iob_func_defined) && defined(__CRT_HAVE___iob_func)
#include <bits/crt/io-file.h>
#define ____iob_func_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__FILE *,__NOTHROW,__iob_func,(void),())
#endif /* ... */


/* ===== stdin ============================== */
#ifndef stdin
#ifdef __LOCAL_stdin
#define stdin __LOCAL_stdin
#elif defined(__CRT_HAVE_stdin)
__CSDECLARE(,__FILE *,stdin)
#define stdin stdin
#elif defined(__CYG_REENT)
#define stdin (__CYG_REENT->__cyg_stdin)
#elif defined(____iob_func_defined)
#define stdin (__iob_func() + 0)
#elif defined(__CRT_HAVE__IO_stdin_)
#ifndef _IO_stdin_
__CSDECLARE(,__FILE,_IO_stdin_)
#define _IO_stdin_ _IO_stdin_
#endif /* !_IO_stdin_ */
#define stdin (&_IO_stdin_)
#elif defined(__CRT_HAVE__IO_2_1_stdin_)
#ifndef _IO_2_1_stdin_
__CSDECLARE(,__FILE,_IO_2_1_stdin_)
#define _IO_2_1_stdin_ _IO_2_1_stdin_
#endif /* !_IO_2_1_stdin_ */
#define stdin (&_IO_2_1_stdin_)
#endif /* ... */
#endif /* !stdin */


/* ===== stdout ============================= */
#ifndef stdout
#ifdef __LOCAL_stdout
#define stdout __LOCAL_stdout
#elif defined(__CRT_HAVE_stdout)
__CSDECLARE(,__FILE *,stdout)
#define stdout stdout
#elif defined(__CYG_REENT)
#define stdout (__CYG_REENT->__cyg_stdout)
#elif defined(____iob_func_defined)
#define stdout (__iob_func() + 1)
#elif defined(__CRT_HAVE__IO_stdout_)
#ifndef _IO_stdout_
__CSDECLARE(,__FILE,_IO_stdout_)
#define _IO_stdout_ _IO_stdout_
#endif /* !_IO_stdout_ */
#define stdout (&_IO_stdout_)
#elif defined(__CRT_HAVE__IO_2_1_stdout_)
#ifndef _IO_2_1_stdout_
__CSDECLARE(,__FILE,_IO_2_1_stdout_)
#define _IO_2_1_stdout_ _IO_2_1_stdout_
#endif /* !_IO_2_1_stdout_ */
#define stdout (&_IO_2_1_stdout_)
#endif /* ... */
#endif /* !stdout */


/* ===== stderr ============================= */
#ifndef stderr
#ifdef __LOCAL_stderr
#define stderr __LOCAL_stderr
#elif defined(__CRT_HAVE_stderr)
__CSDECLARE(,__FILE *,stderr)
#define stderr stderr
#elif defined(__CYG_REENT)
#define stderr (__CYG_REENT->__cyg_stderr)
#elif defined(____iob_func_defined)
#define stderr (__iob_func() + 2)
#elif defined(__CRT_HAVE__IO_stderr_)
#ifndef _IO_stderr_
__CSDECLARE(,__FILE,_IO_stderr_)
#define _IO_stderr_ _IO_stderr_
#endif /* !_IO_stderr_ */
#define stderr (&_IO_stderr_)
#elif defined(__CRT_HAVE__IO_2_1_stderr_)
#ifndef _IO_2_1_stderr_
__CSDECLARE(,__FILE,_IO_2_1_stderr_)
#define _IO_2_1_stderr_ _IO_2_1_stderr_
#endif /* !_IO_2_1_stderr_ */
#define stderr (&_IO_2_1_stderr_)
#endif /* ... */
#endif /* !stderr */


/* KOS-extension: standard file stream for `/dev/tty' */
#if defined(__USE_KOS) && !defined(stdtty) && defined(__CRT_HAVE_stdtty)
__CSDECLARE(,__FILE *,stdtty)
#define stdtty stdtty
#endif /* __USE_KOS && !stdtty && __CRT_HAVE_stdtty */

}

%[insert:std]
%


/************************************************************************/
/* CRT symbol name linkage lists for various functions.                 */
/************************************************************************/
%[define_crt_name_list(CNL_fgetpos            = ["fgetpos", "_IO_fgetpos"])]     /*  int fgetpos(FILE *, pos32_t *) */
%[define_crt_name_list(CNL_fgetpos64          = ["fgetpos64", "_IO_fgetpos64"])] /*  int fgetpos64(FILE *, pos64_t *) */
%[define_crt_name_list(CNL_fgetpos_unlocked   = ["fgetpos_unlocked"])]           /*  int fgetpos_unlocked(FILE *, pos32_t *) */
%[define_crt_name_list(CNL_fgetpos64_unlocked = ["fgetpos64_unlocked"])]         /*  int fgetpos64_unlocked(FILE *, pos64_t *) */

%[define_crt_name_list(CNL_fsetpos            = ["fsetpos", "_IO_fsetpos"])]     /*  int fsetpos(FILE *, pos32_t const *) */
%[define_crt_name_list(CNL_fsetpos64          = ["fsetpos64", "_IO_fsetpos64"])] /*  int fsetpos64(FILE *, pos64_t const *) */
%[define_crt_name_list(CNL_fsetpos_unlocked   = ["fsetpos_unlocked"])]           /*  int fsetpos_unlocked(FILE *, pos32_t const *) */
%[define_crt_name_list(CNL_fsetpos64_unlocked = ["fsetpos64_unlocked"])]         /*  int fsetpos64_unlocked(FILE *, pos64_t const *) */

%[define_crt_name_list(CNL_fseek             = ["fseek"])]                                                     /*  int fseek(FILE *, long int, int) */
%[define_crt_name_list(CNL_fseeko            = ["fseeko"])]                                                    /*  int fseeko(FILE *, off32_t, int) */
%[define_crt_name_list(CNL_fseeko64          = ["fseeko64", "fseek64", "_fseeki64"])]                          /*  int fseeko64(FILE *, off64_t, int) */
%[define_crt_name_list(CNL_fseek_unlocked    = ["fseek_unlocked", "_fseek_nolock"])]                           /*  int fseek_unlocked(FILE *, long int, int) */
%[define_crt_name_list(CNL_fseeko_unlocked   = ["fseeko_unlocked"])]                                           /*  int fseeko_unlocked(FILE *, off32_t, int) */
%[define_crt_name_list(CNL_fseeko64_unlocked = ["fseeko64_unlocked", "fseek64_unlocked", "_fseeki64_nolock"])] /*  int fseeko64_unlocked(FILE *, off64_t, int) */

%[define_crt_name_list(CNL_ftell             = ["ftell", "_IO_ftell"])]                                        /* long int ftell(FILE *) */
%[define_crt_name_list(CNL_ftello            = ["ftello"])]                                                    /* off32_t ftello(FILE *) */
%[define_crt_name_list(CNL_ftello64          = ["ftello64", "ftell64", "_ftelli64"])]                          /* off64_t ftello64(FILE *) */
%[define_crt_name_list(CNL_ftell_unlocked    = ["ftell_unlocked", "_ftell_nolock"])]                           /* long int ftell_unlocked(FILE *) */
%[define_crt_name_list(CNL_ftello_unlocked   = ["ftello_unlocked"])]                                           /* off32_t ftello_unlocked(FILE *) */
%[define_crt_name_list(CNL_ftello64_unlocked = ["ftello64_unlocked", "ftell64_unlocked", "_ftelli64_nolock"])] /* off64_t ftello64_unlocked(FILE *) */

%[define_crt_name_list(CNL_fgetc             = ["getc", "fgetc", "_IO_getc"])]                                        /* int fgetc(FILE *) */
%[define_crt_name_list(CNL_fgetc_unlocked    = ["fgetc_unlocked", "getc_unlocked", "_getc_nolock", "_fgetc_nolock"])] /* int fgetc_unlocked(FILE *) */

%[define_crt_name_list(CNL_fputc             = ["putc", "fputc", "_IO_putc"])]                                        /* int fputc(FILE *) */
%[define_crt_name_list(CNL_fputc_unlocked    = ["putc_unlocked", "fputc_unlocked", "_putc_nolock", "_fputc_nolock"])] /* int fputc_unlocked(FILE *) */

%[define_crt_name_list(CNL_ungetc            = ["ungetc", "_IO_ungetc"])]              /* int ungetc(int, FILE *) */
%[define_crt_name_list(CNL_ungetc_unlocked   = ["ungetc_unlocked", "_ungetc_nolock"])] /* int ungetc_unlocked(int, FILE *) */

%[define_crt_name_list(CNL_fread             = ["fread", "_IO_fread"])]              /* size_t fread(void *, size_t, size_t, FILE *) */
%[define_crt_name_list(CNL_fread_unlocked    = ["fread_unlocked", "_fread_nolock"])] /* size_t fread_unlocked(void *, size_t, size_t, FILE *) */

%[define_crt_name_list(CNL_fwrite            = ["fwrite", "_IO_fwrite", "fwrite_s"])]  /* size_t fwrite(void *, size_t, size_t, FILE *) */
%[define_crt_name_list(CNL_fwrite_unlocked   = ["fwrite_unlocked", "_fwrite_nolock"])] /* size_t fwrite_unlocked(void *, size_t, size_t, FILE *) */

%[define_crt_name_list(CNL_flushall          = ["_flushall", "_IO_flush_all"])] /* int flushall(); */
%[define_crt_name_list(CNL_flushall_unlocked = ["flushall_unlocked"])]          /* int flushall_unlocked(); */

%[define_crt_name_list(CNL_fflush          = ["fflush", "_IO_fflush"])]              /* int fflush(FILE *); */
%[define_crt_name_list(CNL_fflush_unlocked = ["fflush_unlocked", "_fflush_nolock"])] /* int fflush_unlocked(FILE *); */

%[define_crt_name_list(CNL_setvbuf          = ["setvbuf", "_IO_setvbuf"])] /* int setvbuf(FILE *, char *, int, size_t); */
%[define_crt_name_list(CNL_setvbuf_unlocked = ["setvbuf_unlocked"])]       /* int setvbuf_unlocked(FILE *, char *, int, size_t); */

%[define_crt_name_list(CNL_fftruncate            = ["fftruncate"])]            /* int fftruncate(File *, pos32_t); */
%[define_crt_name_list(CNL_fftruncate_unlocked   = ["fftruncate_unlocked"])]   /* int fftruncate_unlocked(File *, pos32_t); */
%[define_crt_name_list(CNL_fftruncate64          = ["fftruncate64"])]          /* int fftruncate64(File *, pos64_t); */
%[define_crt_name_list(CNL_fftruncate64_unlocked = ["fftruncate64_unlocked"])] /* int fftruncate64_unlocked(File *, pos64_t); */


/************************************************************************/
/* BEGIN: Declare crt-only variants of file Apis                        */
/************************************************************************/
[[cp_stdio, ignore, nocrt, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), alias(CNL_fwrite_unlocked...)]]
[[                                                                           alias(CNL_fwrite...)]]
[[                                                                           alias(CNL_fwrite_unlocked...)]]
$size_t crt_fwrite([[inp(min(elemsize * return, elemsize * elemcount))]] void const *__restrict buf,
                   $size_t elemsize, $size_t elemcount, [[nonnull]] $FILE *__restrict stream);

[[cp_stdio, ignore, nocrt, decl_include("<hybrid/typecore.h>")]]
[[alias(CNL_fwrite..., CNL_fwrite_unlocked...)]]
$size_t crt_fwrite_unlocked([[inp(min(elemsize * return, elemsize * elemcount))]] void const *__restrict buf,
                            $size_t elemsize, $size_t elemcount, [[nonnull]] $FILE *__restrict stream);

[[cp_stdio, ignore, wunused, nocrt, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), alias(CNL_fread_unlocked...)]]
[[                                                                           alias(CNL_fread...)]]
[[                                                                           alias(CNL_fread_unlocked...)]]
$size_t crt_fread([[outp(elemsize * elemcount)]] void *__restrict buf,
                  $size_t elemsize, $size_t elemcount,
                  [[nonnull]] $FILE *__restrict stream);

[[cp_stdio, ignore, wunused, nocrt, decl_include("<hybrid/typecore.h>")]]
[[alias(CNL_fread..., CNL_fread_unlocked...)]]
$size_t crt_fread_unlocked([[outp(elemsize * elemcount)]] void *__restrict buf,
                           $size_t elemsize, $size_t elemcount,
                           [[nonnull]] $FILE *__restrict stream);

[[cp_stdio, ignore, nocrt]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), alias(CNL_fgetc_unlocked...)]]
[[                                                                           alias(CNL_fgetc...)]]
[[                                                                           alias(CNL_fgetc_unlocked...)]]
int crt_fgetc([[nonnull]] $FILE *__restrict stream);

[[cp_stdio, ignore, nocrt, alias(CNL_fgetc_unlocked..., CNL_fgetc...)]]
int crt_fgetc_unlocked([[nonnull]] $FILE *__restrict stream);

[[cp_stdio, ignore, nocrt]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), alias(CNL_fputc_unlocked...)]]
[[                                                                           alias(CNL_fputc...)]]
[[                                                                           alias(CNL_fputc_unlocked...)]]
int crt_fputc(int ch, [[nonnull]] $FILE *__restrict stream);

[[cp_stdio, ignore, nocrt, alias(CNL_fputc_unlocked..., CNL_fputc...)]]
int crt_fputc_unlocked(int ch, [[nonnull]] $FILE *__restrict stream);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if(                                          defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_fgetpos_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fgetpos64_unlocked...)]]
[[                                                                                                                         alias(CNL_fgetpos...)]]
[[if($extended_include_prefix("<bits/types.h>")                                 __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fgetpos64...)]]
[[                                                                                                                         alias(CNL_fgetpos_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                 __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fgetpos64_unlocked...)]]
int crt_fgetpos([[nonnull]] $FILE *__restrict stream, [[nonnull]] $pos32_t *__restrict pos);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fgetpos_unlocked...)]]
[[if(                                          defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_fgetpos64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fgetpos...)]]
[[                                                                                                                         alias(CNL_fgetpos64...)]]
[[if($extended_include_prefix("<bits/types.h>")                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fgetpos_unlocked...)]]
[[                                                                                                                         alias(CNL_fgetpos64_unlocked...)]]
int crt_fgetpos64([[nonnull]] $FILE *__restrict stream, [[nonnull]] $pos64_t *__restrict pos);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<features.h>")                  defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_fsetpos_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fsetpos64_unlocked...)]]
[[                                                                                                                                         alias(CNL_fsetpos...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fsetpos64...)]]
[[                                                                                                                                         alias(CNL_fsetpos_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fsetpos64_unlocked...)]]
int crt_fsetpos([[nonnull]] $FILE *__restrict stream, [[nonnull]] $pos32_t const *__restrict pos);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fsetpos_unlocked...)]]
[[if($extended_include_prefix("<features.h>")                  defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_fsetpos64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fsetpos...)]]
[[                                                                                                                                         alias(CNL_fsetpos64...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fsetpos_unlocked...)]]
[[                                                                                                                                         alias(CNL_fsetpos64_unlocked...)]]
int crt_fsetpos64([[nonnull]] $FILE *__restrict stream, [[nonnull]] $pos64_t const *__restrict pos);

[[stdio_throws, ignore, nocrt]]
[[if($extended_include_prefix("<features.h>")                  defined(__USE_STDIO_UNLOCKED)                                         ), alias(CNL_fseek_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
[[                                                                                                                                      alias(CNL_fseek...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64...)]]
[[                                                                                                                                      alias(CNL_fseek_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
int crt_fseek([[nonnull]] $FILE *__restrict stream, long int off, int whence);

[[stdio_throws, ignore, nocrt]]
[[if($extended_include_prefix("<features.h>")                  defined(__USE_STDIO_UNLOCKED)),                                          alias(CNL_ftell_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
[[                                                                                                                                      alias(CNL_ftell...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64...)]]
[[                                                                                                                                      alias(CNL_ftell_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
long int crt_ftell([[nonnull]] $FILE *__restrict stream);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if($extended_include_prefix("<features.h>")                  defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_fseeko_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek...)]]
[[                                                                                                                                         alias(CNL_fseeko...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[                                                                                                                                         alias(CNL_fseeko_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
int crt_fseeko([[nonnull]] $FILE *__restrict stream, $off32_t off, int whence);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if($extended_include_prefix("<features.h>")                  defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_ftello_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell...)]]
[[                                                                                                                                         alias(CNL_ftello...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[                                                                                                                                         alias(CNL_ftello_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
$off32_t crt_ftello([[nonnull]] $FILE *__restrict stream);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if($extended_include_prefix("<features.h>")                  defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_fseeko64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[                                                                                                                                         alias(CNL_fseeko64...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[                                                                                                                                         alias(CNL_fseeko64_unlocked...)]]
int crt_fseeko64([[nonnull]] $FILE *__restrict stream, $off32_t off, int whence);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if($extended_include_prefix("<features.h>")                  defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_ftello64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[                                                                                                                                         alias(CNL_ftello64...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[                                                                                                                                         alias(CNL_ftello64_unlocked...)]]
$off64_t crt_ftello64([[nonnull]] $FILE *__restrict stream);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[                                                                                        alias(CNL_fgetpos_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fgetpos64_unlocked...)]]
[[                                                                                        alias(CNL_fgetpos...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fgetpos64...)]]
int crt_fgetpos_unlocked([[nonnull]] $FILE *__restrict stream, [[nonnull]] $pos32_t *__restrict pos);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[                                                                                        alias(CNL_fsetpos_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fsetpos64_unlocked...)]]
[[                                                                                        alias(CNL_fsetpos...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fsetpos64...)]]
int crt_fsetpos_unlocked([[nonnull]] $FILE *__restrict stream, [[nonnull]] $pos32_t const *__restrict pos);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fgetpos_unlocked...)]]
[[                                                                                        alias(CNL_fgetpos64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fgetpos...)]]
[[                                                                                        alias(CNL_fgetpos64...)]]
int crt_fgetpos64_unlocked([[nonnull]] $FILE *__restrict stream, [[nonnull]] $pos64_t *__restrict pos);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fsetpos_unlocked...)]]
[[                                              alias(CNL_fsetpos64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fsetpos...)]]
[[                                              alias(CNL_fsetpos64...)]]
int crt_fsetpos64_unlocked([[nonnull]] $FILE *__restrict stream, [[nonnull]] $pos64_t const *__restrict pos);

[[stdio_throws, ignore, nocrt]]
[[                                                                                     alias(CNL_fseek_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
[[                                                                                     alias(CNL_fseek...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64...)]]
int crt_fseek_unlocked([[nonnull]] $FILE *__restrict stream, long int off, int whence);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[                                                                                     alias(CNL_ftell_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
[[                                                                                     alias(CNL_ftell...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64...)]]
long int crt_ftell_unlocked([[nonnull]] $FILE *__restrict stream);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[                                                                                        alias(CNL_fseeko_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek...)]]
[[                                                                                        alias(CNL_fseeko...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64...)]]
int crt_fseeko_unlocked([[nonnull]] $FILE *__restrict stream, $off32_t off, int whence);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[                                                                                        alias(CNL_ftello_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell...)]]
[[                                                                                        alias(CNL_ftello...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64...)]]
$off32_t crt_ftello_unlocked([[nonnull]] $FILE *__restrict stream);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[                                                                                        alias(CNL_fseeko64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[                                                                                        alias(CNL_fseeko64...)]]
int crt_fseeko64_unlocked([[nonnull]] $FILE *__restrict stream, $off32_t off, int whence);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[                                                                                        alias(CNL_ftello64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[                                                                                        alias(CNL_ftello64...)]]
$off64_t crt_ftello64_unlocked([[nonnull]] $FILE *__restrict stream);

[[cp_stdio, ignore, nocrt, alias(CNL_flushall...)]]
int crt_flushall();


/************************************************************************/
/* END: Declare crt-only variants of file Apis                          */
/************************************************************************/




%[default:section(".text.crt{|.dos}.fs.modify")];

@@>> remove(3)
@@Remove a file or directory `filename'
[[crt_dos_variant, cp, std, guard]]
[[requires_include("<asm/os/fcntl.h>", "<asm/os/errno.h>")]]
[[requires((defined(__AT_FDCWD) && $has_function(removeat)) ||
           (defined(__EISDIR) && defined(__ENOTDIR) && $has_function(unlink, rmdir)))]]
[[impl_include("<asm/os/fcntl.h>", "<libc/errno.h>")]]
int remove([[nonnull]] char const *filename) {
@@pp_if defined(__AT_FDCWD) && $has_function(removeat)@@
	return removeat(__AT_FDCWD, filename);
@@pp_else@@
	int result;
	for (;;) {
		result = unlink(filename);
		if (result == 0 || __libc_geterrno_or(0) != __EISDIR)
			break;
		result = rmdir(filename);
		if (result == 0 || __libc_geterrno_or(0) != __ENOTDIR)
			break;
	}
	return result;
@@pp_endif@@
}

@@>> rename(2)
@@Rename  a given file `oldname' to `newname_or_path', or in the event
@@that `newname_or_path' refers to a directory, place the file within.
[[cp, std, guard, export_alias("__rename", "__libc_rename")]]
[[crt_dos_variant, userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(renameat))]]
int rename([[nonnull]] char const *oldname,
           [[nonnull]] char const *newname_or_path) {
	return renameat(__AT_FDCWD, oldname, __AT_FDCWD, newname_or_path);
}


@@>> tmpnam(3), tmpnam_r(3)
[[crt_dos_variant, std, wunused]]
[[section(".text.crt{|.dos}.fs.utility")]]
char *tmpnam([[nonnull]] char *buf);


@@>> fclose(3)
@@Close and destroy a given file `stream'
[[stdio_throws, std, dos_only_export_alias("_fclose_nolock"), export_alias("_IO_fclose")]]
[[section(".text.crt{|.dos}.FILE.locked.access")]]
int fclose([[nonnull]] FILE *__restrict stream);


@@>> fflush(3)
@@Flush any unwritten data from `stream' to the underlying filesystem/TTY
[[std, cp_stdio, no_crt_self_import, no_crt_self_export, export_as(CNL_fflush...)]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), alias(CNL_fflush_unlocked...)]]
[[                                                                           alias(CNL_fflush...)]]
[[                                                                           alias(CNL_fflush_unlocked...)]]
[[userimpl, section(".text.crt{|.dos}.FILE.locked.write.utility")]]
int fflush([[nullable]] FILE *stream) {
	/* NO-OP  (When  not  implemented  by  the  CRT,  assume  no
	 * buffering being done, meaning this function isn't needed) */
@@pp_if $has_function(crt_flushall)@@
	if (!stream)
		return crt_flushall();
@@pp_endif@@
	(void)stream;
	return 0;
}

%[default:section(".text.crt{|.dos}.FILE.locked.read.utility")]

@@>> setbuf(3)
@@Alias for `setvbuf(stream, buf, _IOFBF, BUFSIZ)'
[[std, requires_include("<asm/crt/stdio.h>"), impl_include("<asm/crt/stdio.h>")]]
[[requires(defined(___IOFBF) && defined(___IONBF) &&
           defined(__BUFSIZ) && $has_function(setvbuf))]]
void setbuf([[nonnull]] FILE *__restrict stream, [[nullable]] char *buf) {
	setvbuf(stream, buf,
	        buf ? ___IOFBF : ___IONBF,
	        buf ? __BUFSIZ : 0);
}

@@>> setvbuf(3)
@@Set the buffer and buffer-mode to-be used by the given `stream'
@@@param modes: One of `_IOFBF', `_IOLBF' or `_IONBF'
[[std, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_setvbuf...)]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), alias(CNL_setvbuf_unlocked...)]]
[[                                                                           alias(CNL_setvbuf...)]]
[[                                                                           alias(CNL_setvbuf_unlocked...)]]
int setvbuf([[nonnull]] FILE *__restrict stream,
            char *__restrict buf, __STDC_INT_AS_UINT_T modes,
            size_t bufsize);

%[default:section(".text.crt{|.dos}.FILE.locked.read.getc")]

@@>> getc(3), fgetc(3)
@@Read and return a single character from `stream'
@@If  the given `stream' has been exhausted or if an error occurred, `EOF' is
@@returned and the exact cause can be determined by using `ferror' and `feof'
[[std, cp_stdio, no_crt_self_import, no_crt_self_export, export_as(CNL_fgetc...)]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), alias(CNL_fgetc_unlocked...)]]
[[                                                                           alias(CNL_fgetc...)]]
[[                                                                           alias(CNL_fgetc_unlocked...)]]
[[userimpl, requires((defined(__CRT_DOS) && $has_function(_filbuf)) || $has_function(crt_fread))]]
[[impl_include("<bits/crt/io-file.h>")]]
int fgetc([[nonnull]] FILE *__restrict stream) {
@@pp_if defined(__CRT_DOS) && $has_function(_filbuf) && (defined(__USE_STDIO_UNLOCKED) || !$has_function(crt_fread))@@
	return --stream->__f_cnt >= 0 ? (int)((u8)*stream->__f_ptr++) : _filbuf(stream);
@@pp_else@@
	char ch;
	if (!crt_fread(&ch, sizeof(char), 1, stream))
		return EOF;
	return (int)ch;
@@pp_endif@@
}

%[insert:std_function(getc = fgetc)]

@@>> getchar(3)
@@Alias for `fgetc(stdin)'
[[std, cp_stdio]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("getchar_unlocked")]]
[[dos_only_export_alias("_fgetchar"), impl_include("<libc/template/stdstreams.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdin) && $has_function(fgetc))]]
int getchar() {
	return fgetc(stdin);
}

%[default:section(".text.crt{|.dos}.FILE.locked.write.putc")]

@@>> putc(3), fputc(3)
@@Write a single character `ch' to `stream'
[[std, cp_stdio, no_crt_self_import, no_crt_self_export, export_as(CNL_fputc...)]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), crtbuiltin(fputc_unlocked)]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias(CNL_fputc_unlocked...)]]
[[                                                                           alias(CNL_fputc...)]]
[[                                                                           alias(CNL_fputc_unlocked...)]]
[[crtbuiltin, userimpl, requires((defined(__CRT_DOS) && $has_function(_flsbuf)) || $has_function(crt_fwrite))]]
[[impl_include("<bits/crt/io-file.h>", "<features.h>")]]
int fputc(int ch, [[nonnull]] FILE *__restrict stream) {
@@pp_if defined(__CRT_DOS) && $has_function(_flsbuf) && (defined(__USE_STDIO_UNLOCKED) || !$has_function(crt_fwrite))@@
	return --stream->__f_cnt >= 0 ? (int)((u8)(*stream->__f_ptr++ = (char)ch)) : _flsbuf(ch, stream);
@@pp_else@@
	unsigned char byte = (unsigned char)(unsigned int)ch;
	if (!crt_fwrite(&byte, sizeof(unsigned char), 1, stream))
		return EOF;
	return ch;
@@pp_endif@@
}

%[insert:std_function(putc = fputc)]

@@>> putchar(3)
@@Alias for `fputc(ch, stdout)'
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), crtbuiltin(putchar_unlocked)]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("putchar_unlocked")]]
[[std, cp_stdio, crtbuiltin, dos_only_export_alias("_fputchar"), alias("putchar_unlocked")]]
[[impl_include("<libc/template/stdstreams.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdout) && $has_function(fputc))]]
int putchar(int ch) {
	return fputc(ch, stdout);
}

%[default:section(".text.crt{|.dos}.FILE.locked.read.read")]

@@>> fgets(3)
@@Read up to `bufsize - 1' bytes of data from `stream', storing them into `buf' stopped when the
@@buffer is full or a line-feed was read (in this case, the line-feed is also written to `buf').
@@Afterwards, append a trailing NUL-character and re-return `buf', or return `NULL' on error.
[[std, cp_stdio, wunused, decl_include("<features.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("fgets_unlocked")]]
[[export_alias("_IO_fgets"), alias("fgets_unlocked"), impl_include("<hybrid/typecore.h>", "<libc/errno.h>")]]
[[requires($has_function(fgetc) && $has_function(ungetc) && $has_function(ferror))]]
char *fgets([[outp(min(strlen(return), bufsize))]] char *__restrict buf,
            __STDC_INT_AS_SIZE_T bufsize, [[nonnull]] FILE *__restrict stream) {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
@@pp_ifdef ERANGE@@
		(void)libc_seterrno(ERANGE);
@@pp_endif@@
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
		if (ch == '\n') {
			++n; /* Must keep the trailing '\n' at the end of lines! */
			break;
		}
	}
	buf[n] = '\0'; /* NUL-terminate line */
	return buf;
}

%[default:section(".text.crt{|.dos}.FILE.locked.write.write")]

@@>> fputs(3)
@@Print a given string `string' to `stream'. This is identical to:
@@>> fwrite(string, sizeof(char), strlen(string), stream);
[[std, cp_stdio, decl_include("<features.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), crtbuiltin(fputs_unlocked)]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("fputs_unlocked")]]
[[crtbuiltin, export_alias("_IO_fputs"), alias("fputs_unlocked")]]
[[requires($has_function(fwrite))]]
__STDC_INT_AS_SSIZE_T fputs([[nonnull]] char const *__restrict string,
                            [[nonnull]] FILE *__restrict stream) {
	__STDC_INT_AS_SIZE_T result;
	result = fwrite(string,
	                sizeof(char),
	                strlen(string),
	                stream);
	return result;
}

@@>> puts(3)
@@Print a given string `string', followed by a line-feed to `stdout'. This is identical to:
@@>> fputs(string, stdout);
@@>> putchar('\n');
@@Return the number of written characters, or `EOF' on error
[[std, cp_stdio, decl_include("<features.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), crtbuiltin(puts_unlocked)]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("puts_unlocked")]]
[[crtbuiltin, export_alias("_IO_puts"), alias("puts_unlocked")]]
[[impl_include("<libc/template/stdstreams.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdout) && $has_function(fputs) && $has_function(fputc))]]
__STDC_INT_AS_SSIZE_T puts([[nonnull]] char const *__restrict string) {
	__STDC_INT_AS_SSIZE_T result, temp;
	result = fputs(string, stdout);
	if (result >= 0) {
		temp = fputc('\n', stdout);
		if (temp <= 0) {
			result = temp;
		} else {
			result += temp;
		}
	}
	return result;
}

@@>> ungetc(3)
@@Unget a single character byte of data previously returned by `getc()'
[[std, no_crt_self_import, no_crt_self_export, export_as(CNL_ungetc...)]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), alias(CNL_ungetc_unlocked...)]]
[[                                                                           alias(CNL_ungetc...)]]
[[                                                                           alias(CNL_ungetc_unlocked...)]]
[[section(".text.crt{|.dos}.FILE.locked.read.getc")]]
int ungetc(int ch, [[nonnull]] FILE *__restrict stream);

@@>> fread(3)
@@Read up to `elemsize * elemcount' bytes of data from `stream' into `buf'
[[std, cp_stdio, wunused, decl_include("<hybrid/typecore.h>")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fread...)]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), alias(CNL_fread_unlocked...)]]
[[                                                                           alias(CNL_fread...)]]
[[                                                                           alias(CNL_fread_unlocked...)]]
[[userimpl, requires_function(fgetc)]]
[[section(".text.crt{|.dos}.FILE.locked.read.read")]]
size_t fread([[inp(min(elemsize * return, elemsize * elemcount))]] void *__restrict buf,
             size_t elemsize, size_t elemcount, [[nonnull]] FILE *__restrict stream) {
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


@@>> fwrite(3)
@@Write up to `elemsize * elemcount' bytes of data from `buf' into `stream'
[[std, cp_stdio, decl_include("<hybrid/typecore.h>")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fwrite...)]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias(CNL_fwrite_unlocked...)]]
[[                                                                           alias(CNL_fwrite...)]]
[[                                                                           alias(CNL_fwrite_unlocked...)]]
[[crtbuiltin, userimpl, requires_function(fputc)]]
[[section(".text.crt{|.dos}.FILE.locked.write.write")]]
size_t fwrite([[inp(min(elemsize * return, elemsize * elemcount))]] void const *__restrict buf,
              size_t elemsize, size_t elemcount, [[nonnull]] FILE *__restrict stream) {
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

%[default:section(".text.crt{|.dos}.FILE.locked.seek.seek")]

@@>> fseek(3)
@@Change the current in-file position of `stream' as a byte-offset from the start of the file
[[stdio_throws, std, no_crt_self_import, no_crt_self_export, export_as(CNL_fseek...)]]
[[if($extended_include_prefix("<features.h>")                  defined(__USE_STDIO_UNLOCKED)                                         ), alias(CNL_fseek_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
[[                                                                                                                                      alias(CNL_fseek...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64...)]]
[[                                                                                                                                      alias(CNL_fseek_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
[[userimpl, requires($has_function(crt_fseeko) || $has_function(crt_fseeko64))]]
int fseek([[nonnull]] FILE *__restrict stream, long int off, int whence) {
@@pp_if __SIZEOF_OFF64_T__ == __SIZEOF_LONG__ && $has_function(crt_fseeko64)@@
	return crt_fseeko64(stream, (off64_t)off, whence);
@@pp_elif $has_function(crt_fseeko)@@
	return crt_fseeko(stream, (off32_t)off, whence);
@@pp_else@@
	return crt_fseeko64(stream, (off64_t)off, whence);
@@pp_endif@@
}

@@>> ftell(3)
@@Return the current in-file position of `stream' as a byte-offset from the start of the file
[[stdio_throws, std, wunused, no_crt_self_import, no_crt_self_export, export_as(CNL_ftell...)]]
[[if($extended_include_prefix("<features.h>")                  defined(__USE_STDIO_UNLOCKED)                                         ), alias(CNL_ftell_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
[[                                                                                                                                      alias(CNL_ftell...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64...)]]
[[                                                                                                                                      alias(CNL_ftell_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
[[userimpl, requires($has_function(crt_fgetpos64) || $has_function(crt_fgetpos) ||
                     $has_function(crt_ftello64) || $has_function(crt_ftello))]]
long int ftell([[nonnull]] FILE *__restrict stream) {
@@pp_if __SIZEOF_LONG__ == __SIZEOF_OFF64_T__ && $has_function(crt_fgetpos64)@@
	pos64_t pos;
	if (crt_fgetpos64(stream, &pos))
		return -1;
	return (long int)(off64_t)pos;
@@pp_elif __SIZEOF_LONG__ == __SIZEOF_OFF32_T__ && $has_function(crt_fgetpos)@@
	pos32_t pos;
	if (crt_fgetpos(stream, &pos))
		return -1;
	return (long int)(off32_t)pos;
@@pp_elif $has_function(crt_ftello64)@@
	return (long int)crt_ftello64(stream);
@@pp_elif $has_function(crt_ftello)@@
	return (long int)crt_ftello(stream);
@@pp_elif $has_function(crt_fgetpos64)@@
	pos64_t pos;
	if (crt_fgetpos64(stream, &pos))
		return -1;
	return (long int)(off64_t)pos;
@@pp_else@@
	pos32_t pos;
	if (crt_fgetpos(stream, &pos))
		return -1;
	return (long int)(off32_t)pos;
@@pp_endif@@
}


@@>> rewind(3)
@@Rewind the current in-file position of `stream' to its starting position
[[stdio_throws, std, export_alias("rewind_unlocked")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("rewind_unlocked")]]
[[requires_include("<asm/os/stdio.h>"), userimpl]]
[[requires(defined(__SEEK_SET) && $has_function(fseeko))]]
[[section(".text.crt{|.dos}.FILE.locked.seek.utility")]]
void rewind([[nonnull]] FILE *__restrict stream) {
	fseeko(stream, 0, __SEEK_SET);
}


@@>> clearerr(3)
@@Clear the error state of `stream', returning the stream to normal operations mode
[[std, export_alias("clearerr_unlocked")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("clearerr_unlocked")]]
[[section(".text.crt{|.dos}.FILE.locked.access")]]
void clearerr([[nonnull]] $FILE *__restrict stream);

%[define_c_language_keyword(__KOS_FIXED_CONST)]


@@>> feof(3)
@@Check if end-of-file has been reached in `stream'
[[decl_include("<features.h>")]]
[[std, pure, wunused, export_alias("_IO_feof", "feof_unlocked")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("feof_unlocked")]]
[[section(".text.crt{|.dos}.FILE.locked.read.utility")]]
int feof([[nonnull]] $FILE __KOS_FIXED_CONST *__restrict stream);


@@>> ferror(3)
@@Check if an I/O error occurred in `stream'
[[decl_include("<features.h>")]]
[[std, pure, wunused, export_alias("_IO_ferror", "ferror_unlocked")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("ferror_unlocked")]]
[[section(".text.crt{|.dos}.FILE.locked.utility")]]
int ferror([[nonnull]] $FILE __KOS_FIXED_CONST *__restrict stream);


@@>> perror(3)
@@Print a given `message' alongside `strerror(errno)' to stderr:
@@>> if (message) {
@@>>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
@@>> } else {
@@>>     fprintf(stderr, "%s\n", strerror(errno));
@@>> }
[[cp, std, guard, export_alias("_IO_perror")]]
[[requires_include("<libc/template/stdstreams.h>", "<libc/errno.h>")]]
[[requires(defined(__LOCAL_stderr) && defined(__libc_geterrno) &&
           $has_function(fprintf) && $has_function(strerror))]]
[[impl_include("<parts/printf-config.h>")]]
[[impl_include("<libc/template/stdstreams.h>", "<libc/errno.h>")]]
[[section(".text.crt{|.dos}.errno.utility")]]
void perror([[nullable]] char const *message) {
@@pp_ifdef __NO_PRINTF_STRERROR@@
	char const *enodesc;
	enodesc = strerror(__libc_geterrno());
	if (message) {
		fprintf(stderr, "%s: %s\n",
		        message, enodesc);
	} else {
		fprintf(stderr, "%s\n",
		        enodesc);
	}
@@pp_else@@
	if (message) {
		fprintf(stderr, "%s: %m\n", message);
	} else {
		fprintf(stderr, "%m\n");
	}
@@pp_endif@@
}



@@>> tmpfile(3), tmpfile64(3)
@@Create and return a new file-stream for accessing a temporary file for reading/writing
[[cp, std, wunused, no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>")!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0), alias("tmpfile")]]
[[                                                                                                                                                     alias("tmpfile64")]]
[[section(".text.crt{|.dos}.FILE.locked.access")]]
FILE *tmpfile();

@@>> fopen(3), fopen64(3)
@@Create and return a new file-stream for accessing `filename'
[[crt_dos_variant, cp, std, wunused, export_as("_IO_fopen")]]
[[export_as("setmntent", "__setmntent"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>")!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0), alias("fopen", "_IO_fopen")]]
[[                                                                                                                                                     alias("fopen64")]]
[[section(".text.crt{|.dos}.FILE.locked.access")]]
FILE *fopen([[nonnull]] char const *__restrict filename,
            [[nonnull]] char const *__restrict modes);

@@>> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
@@Re-open the given  `stream' as a  file-stream for accessing  `filename'
[[crt_dos_variant, cp, std, no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>")defined(__USE_STDIO_UNLOCKED) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)), alias("freopen_unlocked")]]
[[if($extended_include_prefix("<features.h>"                     )defined(__USE_STDIO_UNLOCKED)                                                                                        ), alias("freopen64_unlocked")]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>")                                 (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)), alias("freopen")]]
[[                                                                                                                                                                                        alias("freopen64")]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>")                                 (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)), alias("freopen_unlocked")]]
[[                                                                                                                                                                                        alias("freopen64_unlocked")]]
[[section(".text.crt{|.dos}.FILE.locked.access")]]
FILE *freopen([[nonnull]] char const *__restrict filename,
              [[nonnull]] char const *__restrict modes,
              [[nonnull]] FILE *__restrict stream);


@@>> fgetpos(3), fgetpos64(3)
@@Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
@@Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()'
[[stdio_throws, std, decl_include("<bits/crt/stdio.h>")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fgetpos...)]]
[[if($extended_include_prefix("<features.h>", "<bits/crt/stdio.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fgetpos_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/crt/stdio.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__), alias(CNL_fgetpos64_unlocked...)]]
[[if($extended_include_prefix(                "<bits/crt/stdio.h>")                                 __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fgetpos...)]]
[[if($extended_include_prefix(                "<bits/crt/stdio.h>")                                 __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__), alias(CNL_fgetpos64...)]]
[[if($extended_include_prefix(                "<bits/crt/stdio.h>")                                 __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fgetpos_unlocked...)]]
[[if($extended_include_prefix(                "<bits/crt/stdio.h>")                                 __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__), alias(CNL_fgetpos64_unlocked...)]]
[[userimpl, requires($has_function(crt_ftello64) || $has_function(crt_fgetpos) ||
                     $has_function(crt_fgetpos64) || $has_function(crt_ftello64) ||
                     $has_function(crt_ftello) || $has_function(crt_ftell))]]
[[section(".text.crt{|.dos}.FILE.locked.seek.pos")]]
int fgetpos([[nonnull]] FILE *__restrict stream, [[nonnull]] fpos_t *__restrict pos) {
@@pp_if defined(__USE_FILE_FPOSSET64) && $has_function(crt_ftello64)@@
	return (int32_t)(*pos = (fpos_t)crt_ftello64(stream)) < 0 ? -1 : 0;
@@pp_elif $has_function(crt_fgetpos)@@
	pos32_t pos32;
	int result = crt_fgetpos(stream, &pos32);
	if (!result)
		*pos = (fpos_t)pos32;
	return result;
@@pp_elif $has_function(crt_fgetpos64)@@
	fpos64_t pos64;
	int result = crt_fgetpos64(stream, &pos64);
	if (!result)
		*pos = (fpos_t)pos64;
	return result;
@@pp_elif $has_function(crt_ftello64)@@
	return (int32_t)(*pos = (fpos_t)crt_ftello64(stream)) < 0 ? -1 : 0;
@@pp_elif $has_function(crt_ftello)@@
	return (int32_t)(*pos = (fpos_t)crt_ftello(stream)) < 0 ? -1 : 0;
@@pp_else@@
	return (int32_t)(*pos = (fpos_t)crt_ftell(stream)) < 0 ? -1 : 0;
@@pp_endif@@
}

@@>> fsetpos(3), fsetpos64(3)
@@Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()'
[[stdio_throws, std, decl_include("<bits/crt/stdio.h>")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fsetpos...)]]
[[if($extended_include_prefix("<features.h>", "<bits/crt/stdio.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fsetpos_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/crt/stdio.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__), alias(CNL_fsetpos64_unlocked...)]]
[[if($extended_include_prefix(                "<bits/crt/stdio.h>")                                 __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fsetpos...)]]
[[if($extended_include_prefix(                "<bits/crt/stdio.h>")                                 __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__), alias(CNL_fsetpos64...)]]
[[if($extended_include_prefix(                "<bits/crt/stdio.h>")                                 __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fsetpos_unlocked...)]]
[[if($extended_include_prefix(                "<bits/crt/stdio.h>")                                 __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__), alias(CNL_fsetpos64_unlocked...)]]
[[userimpl, requires($has_function(crt_fseeko64) || $has_function(crt_fsetpos) ||
                     $has_function(crt_fsetpos64) || $has_function(crt_fseeko) ||
                     $has_function(crt_fseek))]]
[[impl_include("<features.h>")]]
[[section(".text.crt{|.dos}.FILE.locked.seek.pos")]]
int fsetpos([[nonnull]] FILE *__restrict stream,
            [[nonnull]] fpos_t const *__restrict pos) {
@@pp_if __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__ && $has_function(crt_fseeko64)@@
	return crt_fseeko64(stream, (off64_t)*pos, SEEK_SET);
@@pp_elif $has_function(crt_fsetpos)@@
	pos32_t pos32 = (pos32_t)*pos;
	return crt_fsetpos(stream, &pos32);
@@pp_elif $has_function(crt_fsetpos64)@@
	fpos64_t pos64 = (fpos64_t)*pos;
	return crt_fsetpos64(stream, &pos64);
@@pp_elif $has_function(crt_fseeko64)@@
	return crt_fseeko64(stream, (off64_t)*pos, SEEK_SET);
@@pp_elif $has_function(crt_fseeko)@@
	return crt_fseeko(stream, (off32_t)*pos, SEEK_SET);
@@pp_else@@
	return crt_fseek(stream, (long int)*pos, SEEK_SET);
@@pp_endif@@
}

%[default:section(".text.crt{|.dos}.FILE.locked.write.printf")]

[[std, cp_stdio, decl_include("<features.h>"), doc_alias("fprintf")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("vfprintf_unlocked")]]
[[crtbuiltin, export_alias("_IO_vfprintf"), alias("vfprintf_s", "vfprintf_unlocked")]]
[[requires_dependent_function(file_printer)]]
[[section(".text.crt{|.dos}.FILE.locked.write.printf")]]
__STDC_INT_AS_SSIZE_T vfprintf([[nonnull]] FILE *__restrict stream,
                               [[nonnull, format]] char const *__restrict format, $va_list args) {
	return (__STDC_INT_AS_SSIZE_T)format_vprintf(&file_printer, stream, format, args);
}

@@>> fprintf(3), vfprintf(3)
@@Print  data  to  `stream',  following  `format'
@@Return the number of successfully printed bytes
[[std, cp_stdio, decl_include("<features.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), crtbuiltin(fprintf_unlocked)]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("fprintf_unlocked")]]
[[crtbuiltin, export_alias("_IO_fprintf"), alias("fprintf_s", "fprintf_unlocked")]]
[[section(".text.crt{|.dos}.FILE.locked.write.printf")]]
__STDC_INT_AS_SSIZE_T fprintf([[nonnull]] FILE *__restrict stream,
                              [[nonnull, format]] char const *__restrict format, ...)
	%{printf("vfprintf")}


[[std, cp_stdio, decl_include("<features.h>"), doc_alias("printf")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("vprintf_unlocked")]]
[[crtbuiltin, alias("vprintf_s", "vprintf_unlocked")]]
[[impl_include("<libc/template/stdstreams.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdout) && $has_function(vfprintf))]]
[[section(".text.crt{|.dos}.FILE.locked.write.printf")]]
__STDC_INT_AS_SSIZE_T vprintf([[nonnull, format]] char const *__restrict format, $va_list args) {
	return vfprintf(stdout, format, args);
}

@@>> printf(3), vprintf(3)
@@Print  data  to  `stdout',  following  `format'
@@Return the number of successfully printed bytes
[[std, cp_stdio, decl_include("<features.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), crtbuiltin(printf_unlocked)]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("printf_unlocked")]]
[[crtbuiltin, export_alias("_IO_printf", "printf_s"), alias("printf_unlocked")]]
[[section(".text.crt{|.dos}.FILE.locked.write.printf")]]
__STDC_INT_AS_SSIZE_T printf([[nonnull, format]] char const *__restrict format, ...)
	%{printf("vprintf")}

%(std)
%(std)#if defined(__USE_ISOC99) || defined(__USE_DOS)

%[default:section(".text.crt{|.dos}.FILE.locked.read.read")]

%[define(DEFINE_VFSCANF_HELPERS =
@@pp_ifndef ____vfscanf_getc_defined@@
#define ____vfscanf_getc_defined
@@push_namespace(local)@@
@@pp_if !defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_FORMAT_WORD_T__ != __SIZEOF_INT__@@
__LOCAL_LIBC(@vfscanf_getc@) __format_word_t
(__FORMATPRINTER_CC vfscanf_getc)(void *arg) {
	return (__format_word_t)fgetc((FILE *)arg);
}
@@pp_endif@@
__LOCAL_LIBC(@vfscanf_ungetc@) ssize_t
(__FORMATPRINTER_CC vfscanf_ungetc)(void *arg, __format_word_t word) {
	return ungetc((int)(unsigned char)(unsigned int)word, (FILE *)arg);
}
@@pop_namespace@@
@@pp_endif@@
)]

[[std, cp_stdio, guard, wunused, doc_alias("fscanf"), decl_include("<features.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("vfscanf_unlocked")]]
[[crtbuiltin, export_alias("_IO_vfscanf", "__vfscanf"), alias("_vfscanf", "_vfscanf_s", "vfscanf_unlocked")]]
[[requires_dependent_function(fgetc, ungetc)]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_prefix(DEFINE_VFSCANF_HELPERS)]]
[[section(".text.crt{|.dos}.FILE.locked.read.scanf")]]
__STDC_INT_AS_SIZE_T vfscanf([[nonnull]] FILE *__restrict stream,
                             [[nonnull, format]] char const *__restrict format,
                             $va_list args) {
@@pp_if defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_FORMAT_WORD_T__ == __SIZEOF_INT__@@
	return format_vscanf((pformatgetc)(void *)&fgetc,
	                     &__NAMESPACE_LOCAL_SYM vfscanf_ungetc,
	                     (void *)stream,
	                     format, args);
@@pp_else@@
	return format_vscanf(&__NAMESPACE_LOCAL_SYM vfscanf_getc,
	                     &__NAMESPACE_LOCAL_SYM vfscanf_ungetc,
	                     (void *)stream,
	                     format, args);
@@pp_endif@@
}

[[std, cp_stdio, guard, wunused, doc_alias("scanf"), decl_include("<features.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("vscanf_unlocked")]]
[[crtbuiltin, alias("_vscanf", "vscanf_unlocked")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdin) && $has_function(vfscanf))]]
[[impl_include("<libc/template/stdstreams.h>")]]
[[section(".text.crt{|.dos}.FILE.locked.read.scanf")]]
__STDC_INT_AS_SIZE_T vscanf([[nonnull, format]] char const *__restrict format, $va_list args) {
	return vfscanf(stdin, format, args);
}
%(std)#endif /* __USE_ISOC99 || __USE_DOS */

%(std)

@@>> fscanf(3), vfscanf(3)
@@Scan  data   from   `stream',   following   `format'
@@Return the number of successfully scanned data items
[[std, cp_stdio, wunused, decl_include("<features.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("fscanf_unlocked")]]
[[crtbuiltin, export_alias("_IO_fscanf"), alias("fscanf_unlocked")]]
[[section(".text.crt{|.dos}.FILE.locked.read.scanf")]]
__STDC_INT_AS_SIZE_T fscanf([[nonnull]] FILE *__restrict stream,
                            [[nonnull, format]] char const *__restrict format, ...)
	%{printf("vfscanf")}

@@>> scanf(3), vscanf(3)
@@Scan data from `stdin', following `format'
@@Return the number of successfully scanned data items
[[std, cp_stdio, wunused, decl_include("<features.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("scanf_unlocked")]]
[[crtbuiltin, export_alias("_IO_scanf"), alias("scanf_unlocked")]]
[[section(".text.crt{|.dos}.FILE.locked.read.scanf")]]
__STDC_INT_AS_SIZE_T scanf([[nonnull, format]] char const *__restrict format, ...)
	%{printf("vscanf")}




%(std)
%(std)#if !defined(__USE_ISOC11) || (defined(__cplusplus) && __cplusplus <= 201103L)
[[std, cp_stdio, guard, wunused, export_alias("_IO_gets")]]
[[deprecated("No buffer size checks (use `fgets' instead)")]]
[[impl_include("<libc/template/stdstreams.h>", "<hybrid/typecore.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdin) && $has_function(fgets))]]
char *gets([[nonnull]] char *__restrict buf) {
	return fgets(buf, INT_MAX, stdin);
}
%(std)#endif /* !__USE_ISOC11 || __cplusplus <= 201103L */

%(std)
%(std)#if defined(__USE_ISOC99) || defined(__USE_DOS)


%[define(DEFINE_VSSCANF_HELPERS =
@@pp_ifndef ____vsscanf_getc_defined@@
#define ____vsscanf_getc_defined
@@push_namespace(local)@@
__LOCAL_LIBC(@vsscanf_getc@) __format_word_t
(FORMATPRINTER_CC vsscanf_getc)(void *arg) {
	unsigned char const *reader = *(unsigned char const **)arg;
	unsigned char result        = *reader++;
	if (!result)
		return __EOF;
	*(unsigned char const **)arg = reader;
	return (__format_word_t)result;
}
__LOCAL_LIBC(@vsscanf_ungetc@) ssize_t
(FORMATPRINTER_CC vsscanf_ungetc)(void *arg, __format_word_t UNUSED(word)) {
	--(*(unsigned char const **)arg);
	return 0;
}
@@pop_namespace@@
@@pp_endif@@
)]

[[std, guard, wunused, decl_include("<features.h>"), doc_alias("sscanf")]]
[[impl_include("<hybrid/typecore.h>", "<bits/crt/format-printer.h>", "<asm/crt/stdio.h>")]]
[[crtbuiltin, export_alias("__vsscanf", "_IO_vsscanf"), alias("_vsscanf", "_vsscanf_s")]]
[[section(".text.crt{|.dos}.unicode.static.format.scanf")]]
[[impl_prefix(DEFINE_VSSCANF_HELPERS)]]
__STDC_INT_AS_SIZE_T vsscanf([[nonnull]] char const *__restrict input,
                             [[nonnull, format]] char const *__restrict format, $va_list args) {
	return format_vscanf(&__NAMESPACE_LOCAL_SYM vsscanf_getc,
	                     &__NAMESPACE_LOCAL_SYM vsscanf_ungetc,
	                     (void *)&input, format, args);
}
%(std)#endif /* __USE_ISOC99 || __USE_DOS */

%(std)
@@>> sscanf(3), vsscanf(3)
@@Scan data from a given `input' string, following `format'
@@Return  the  number  of successfully  scanned  data items
[[std, decl_include("<features.h>")]]
[[crtbuiltin, export_alias("_IO_sscanf")]]
[[section(".text.crt{|.dos}.unicode.static.format.scanf")]]
__STDC_INT_AS_SIZE_T sscanf([[nonnull]] char const *__restrict input,
                            [[nonnull, format]] char const *__restrict format, ...)
	%{printf("vsscanf")}


[[std, kernel, decl_include("<features.h>"), doc_alias("sprintf")]]
[[crtbuiltin, alias("_IO_vsprintf")]]
[[if(!defined(__KERNEL__)), export_as("_IO_vsprintf")]]
[[section(".text.crt{|.dos}.unicode.static.format.printf")]]
[[dependency(format_sprintf_printer)]]
__STDC_INT_AS_SSIZE_T vsprintf([[nonnull]] char *__restrict dest,
                               [[nonnull, format]] char const *__restrict format, $va_list args) {
	__STDC_INT_AS_SSIZE_T result;
	char *dest_pointer = dest;
	result = (__STDC_INT_AS_SSIZE_T)format_vprintf(&format_sprintf_printer,
	                                               (void *)&dest_pointer,
	                                               format, args);
	if (result >= 0)
		*dest_pointer = '\0';
	return result;
}

@@>> sprintf(3), vsprintf(3)
@@Print  a  formatted  string  to  a  given  in-member  string  buffer  `buf'
@@Return the number of written characters, excluding a trailing NUL-character
[[std, kernel, decl_include("<features.h>")]]
[[crtbuiltin, alias("_IO_sprintf")]]
[[if(!defined(__KERNEL__)), export_as("_IO_sprintf")]]
[[section(".text.crt{|.dos}.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T sprintf([[nonnull]] char *__restrict buf,
                             [[nonnull, format]] char const *__restrict format, ...)
	%{printf("vsprintf")}


%(std)
%(std)#if defined(__USE_ISOC99) || defined(__USE_UNIX98) || defined(__USE_DOS)

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[std, kernel, guard, doc_alias("snprintf")]]
[[impl_prefix(
#ifndef ____format_snprintf_data_defined
#define ____format_snprintf_data_defined
struct __format_snprintf_data {
	char         *__sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ __sd_bufsiz; /* Remaining buffer size. */
};
#endif /* !____format_snprintf_data_defined */
), crtbuiltin, alias("__vsnprintf")]]
[[dependency(format_snprintf_printer)]]
[[section(".text.crt{|.dos}.unicode.static.format.printf")]]
[[if(!defined(__KERNEL__)), export_as("__vsnprintf")]]
__STDC_INT_AS_SIZE_T vsnprintf([[outp_opt(min(return, buflen))]] char *__restrict buf, size_t buflen,
                               [[nonnull, format]] char const *__restrict format, $va_list args) {
	struct __format_snprintf_data data;
	__STDC_INT_AS_SSIZE_T result;
	data.__sd_buffer = buf;
	data.__sd_bufsiz = buflen;
	result = (__STDC_INT_AS_SSIZE_T)format_vprintf(&format_snprintf_printer,
	                                               (void *)&data, format, args);
	if (result >= 0) {
		if (data.__sd_bufsiz != 0) {
			*data.__sd_buffer = '\0';
		} else {
			/* Special handling for when the buffer was truncated.
			 *
			 * This part right here isn't mandated by any of the specs and wasn't
			 * implemented in the original version of this function which  simply
			 * left the string without any NUL terminator.
			 *
			 * However, as it turns out `nano(1)' around `/src/help.c:55` has line:
			 * >> int length = help_line_len(ptr);
			 * >> char *oneline = nmalloc(length + 1);
			 * >>
			 * >> snprintf(oneline, length + 1, "%s", ptr);  // <<---- This line
			 * >> free(openfile->current->data);
			 * >> openfile->current->data = oneline;
			 *
			 * Here, it uses a `length' (which is smaller than `strlen(ptr)') as
			 * the limit in a call to snprintf(), using it to essentially copy a
			 * small part of the larger help string into a line-buffer.
			 *
			 * However,  it also expects  and assumes that  this buffer gets NUL
			 * terminated  even when truncated (which isn't explicitly specified
			 * by the specs; i.e. `man 3 snprintf'), and any program that relies
			 * on this relies on system-specific behavior.
			 *
			 * Amazingly enough,  even without  explicitly NUL  terminating it  at
			 * the correct location, nano didn't crash but occasionally  displayed
			 * some garbled lines, as well as the line-feed that always got copied
			 * at the end of a paragraph in its escaped form '^@'.
			 *
			 * But then again, NUL-termination on  truncation seems to be  something
			 * that happens on linux, and after all: KOS tries to be as much API/ABI
			 * compatible with linux as possible, so: in this goes! */
			if (buflen != 0)
				buf[buflen - 1] = '\0';
		}
	}
	return result;
}

@@>> snprintf(3), vsnprintf(3)
@@Print  a formatted string to a given in-member string buffer `buf'
@@Always return the REQUIRED buffer size (excluding a trailing  NUL-
@@character), and never write more than `buflen' characters to `buf'
[[std, kernel, guard, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[crtbuiltin, section(".text.crt{|.dos}.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T snprintf([[outp_opt(min(return, buflen))]] char *__restrict buf, size_t buflen,
                              [[nonnull, format]] char const *__restrict format, ...)
	%{printf("vsnprintf")}
%(std)#endif /* __USE_ISOC99 || __USE_UNIX98 || __USE_DOS */


%
%#ifdef __USE_XOPEN2K8
[[cp, doc_alias("dprintf"), decl_include("<features.h>", "<bits/types.h>")]]
[[requires_dependent_function(write_printer)]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/host.h>", "<bits/crt/format-printer.h>")]]
[[section(".text.crt{|.dos}.io.write")]]
__STDC_INT_AS_SSIZE_T vdprintf($fd_t fd, [[nonnull, format]] char const *__restrict format, $va_list args) {
	return format_vprintf(&write_printer,
	                      (void *)(__UINTPTR_TYPE__)(__CRT_PRIVATE_UINT(__SIZEOF_FD_T__))fd,
	                      format, args);
}

@@>> dprintf(3), vdprintf(3)
[[cp, decl_include("<features.h>", "<bits/types.h>")]]
[[section(".text.crt{|.dos}.io.write")]]
__STDC_INT_AS_SSIZE_T dprintf($fd_t fd, [[nonnull, format]] char const *__restrict format, ...)
	%{printf("vdprintf")}
%#endif /* __USE_XOPEN2K8 */

%
%#ifdef __USE_ATFILE
@@>> renameat(2)
[[cp, decl_include("<bits/types.h>")]]
[[crt_dos_variant, userimpl, requires_function(renameat2)]]
[[section(".text.crt{|.dos}.fs.modify")]]
int renameat($fd_t oldfd, [[nonnull]] char const *oldname,
             $fd_t newfd, [[nonnull]] char const *newname_or_path) {
	return renameat2(oldfd, oldname, newfd, newname_or_path, 0);
}

%
%#ifdef __USE_KOS
@@>> removeat(3)
@@Remove a file or directory `filename' relative to a given base directory `dirfd'
[[cp, decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/fcntl.h>", "<asm/os/errno.h>")]]
[[requires(defined(__AT_REMOVEDIR) && $has_function(unlinkat) &&
           (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR))))]]
[[impl_include("<asm/os/fcntl.h>", "<libc/errno.h>")]]
[[crt_dos_variant, section(".text.crt{|.dos}.fs.modify")]]
int removeat($fd_t dirfd, [[nonnull]] char const *filename) {
@@pp_ifdef __AT_REMOVEREG@@
	return unlinkat(dirfd, filename, __AT_REMOVEREG | __AT_REMOVEDIR);
@@pp_else@@
	int result;
	for (;;) {
		result = unlinkat(dirfd, filename, 0);
		if (result == 0 || __libc_geterrno_or(0) != __EISDIR)
			break;
		result = unlinkat(dirfd, filename, __AT_REMOVEDIR);
		if (result == 0 || __libc_geterrno_or(0) != __ENOTDIR)
			break;
	}
	return result;
@@pp_endif@@
}
%#endif /* __USE_KOS */
%#endif /* __USE_ATFILE */


%#ifdef __USE_GNU
@@>> renameat2(2)
@@@param flags: Set of `0 | AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE |
@@                      AT_RENAME_WHITEOUT | AT_RENAME_MOVETODIR | AT_DOSPATH'
@@NOTE: For portability, use the following names:
@@  - `AT_RENAME_NOREPLACE' --> `RENAME_NOREPLACE'
@@  - `AT_RENAME_EXCHANGE'  --> `RENAME_EXCHANGE'
@@  - `AT_RENAME_WHITEOUT'  --> `RENAME_WHITEOUT'
[[cp, decl_include("<bits/types.h>")]]
[[crt_dos_variant, section(".text.crt{|.dos}.fs.modify")]]
int renameat2($fd_t oldfd, [[nonnull]] char const *oldname,
              $fd_t newfd, [[nonnull]] char const *newname_or_path,
              $atflag_t flags);
%#endif /* __USE_GNU */




%
%#ifdef __USE_MISC
[[wunused, requires_function(tmpnam)]]
[[section(".text.crt{|.dos}.fs.utility"), doc_alias("tmpnam")]]
char *tmpnam_r([[nonnull]] char *buf) {
	return buf ? tmpnam(buf) : NULL;
}

@@>> setbuffer(3)
@@Specify the location and size for the buffer to-be used by `stream'
[[decl_include("<hybrid/typecore.h>"), export_alias("_IO_setbuffer")]]
[[requires_include("<asm/crt/stdio.h>"), impl_include("<asm/crt/stdio.h>")]]
[[requires(defined(___IOFBF) && defined(___IONBF) && $has_function(setvbuf))]]
[[section(".text.crt{|.dos}.FILE.locked.read.utility")]]
void setbuffer([[nonnull]] $FILE *__restrict stream,
               [[nullable]] char *buf, $size_t bufsize) {
	setvbuf(stream,
	        buf,
	        buf ? ___IOFBF : ___IONBF,
	        buf ? bufsize : ($size_t)0);
}

@@>> setlinebuf(3)
@@Change the given `stream' to become line-buffered
[[section(".text.crt{|.dos}.FILE.locked.read.utility")]]
[[requires_function(setvbuf)]]
void setlinebuf([[nonnull]] $FILE *__restrict stream) {
	setvbuf(stream, NULL, _IOLBF, 0);
}

@@>> fflush_unlocked(3)
@@Same as `fflush()', but performs I/O without acquiring a lock to `stream'
[[section(".text.crt{|.dos}.FILE.unlocked.write.utility")]]
[[dos_only_export_alias("_fflush_nolock")]]
[[cp_stdio, userimpl, alias(CNL_fflush...)]]
int fflush_unlocked([[nullable]] $FILE *stream) {
	/* NO-OP  (When  not  implemented  by  the  CRT,  assume  no
	 * buffering being done, meaning this function isn't needed) */
@@pp_if $has_function(crt_flushall)@@
	if (!stream)
		return crt_flushall();
@@pp_endif@@
	(void)stream;
	return 0;
}

@@>> fread_unlocked(3)
@@Same as `fread()', but performs I/O without acquiring a lock to `stream'
[[cp_stdio, wunused, decl_include("<hybrid/typecore.h>")]]
[[no_crt_self_import, no_crt_self_export]]
[[export_alias(CNL_fread_unlocked...), alias(CNL_fread...)]]
[[userimpl, requires_function(fgetc_unlocked)]]
[[section(".text.crt{|.dos}.FILE.unlocked.read.read")]]
$size_t fread_unlocked([[outp(min(return * elemsize, elemcount * elemsize))]] void *__restrict buf,
                       $size_t elemsize, $size_t elemcount, [[nonnull]] $FILE *__restrict stream) {
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

@@>> fwrite_unlocked(3)
@@Same as `fwrite()', but performs I/O without acquiring a lock to `stream'
[[cp_stdio, wunused, decl_include("<hybrid/typecore.h>")]]
[[no_crt_self_import, no_crt_self_export]]
[[export_alias(CNL_fwrite_unlocked...), alias(CNL_fwrite...)]]
[[userimpl, requires_function(fgetc_unlocked)]]
[[section(".text.crt{|.dos}.FILE.unlocked.write.write")]]
$size_t fwrite_unlocked([[inp(min(return * elemsize, elemcount * elemsize))]] void const *__restrict buf,
                        $size_t elemsize, $size_t elemcount, [[nonnull]] $FILE *__restrict stream) {
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


@@>> feof_unlocked(3)
@@Same as `feof()', but skip acquiring internal locks
feof_unlocked(*) = feof;

@@>> ferror_unlocked(3)
@@Same as `ferror()', but skip acquiring internal locks
ferror_unlocked(*) = ferror;

@@>> clearerr_unlocked(3)
@@Same as `clearerr()', but skip acquiring internal locks
clearerr_unlocked(*) = clearerr;

@@>> fileno_unlocked(3)
@@Same as `fileno()', but skip acquiring internal locks
fileno_unlocked(*) = fileno;


%[default:section(".text.crt{|.dos}.FILE.unlocked.read.getc")]

@@>> fgetc_unlocked(3)
@@Same as `fgetc()', but performs I/O without acquiring a lock to `stream'
[[impl_include("<bits/crt/io-file.h>")]]
[[cp_stdio, no_crt_self_import, no_crt_self_export, export_alias(CNL_fgetc_unlocked...)]]
[[if(!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf)), alias(CNL_fgetc...)]]
[[userimpl, requires((defined(__CRT_DOS) && $has_function(_filbuf)) || $has_function(crt_fread_unlocked))]]
int fgetc_unlocked([[nonnull]] $FILE *__restrict stream) {
@@pp_if defined(__CRT_DOS) && $has_function(_filbuf)@@
	return --stream->__f_cnt >= 0 ? (int)((__UINT8_TYPE__)*stream->__f_ptr++) : _filbuf(stream);
@@pp_else@@
	char ch;
	if (!crt_fread_unlocked(&ch, sizeof(char), 1, stream))
		return EOF;
	return (int)ch;
@@pp_endif@@
}

%[default:section(".text.crt{|.dos}.FILE.unlocked.write.putc")]

@@>> fputc_unlocked(3)
@@Same as `fputc()', but performs I/O without acquiring a lock to `stream'
[[cp_stdio, no_crt_self_import, no_crt_self_export]]
[[crtbuiltin, export_alias(CNL_fputc_unlocked...)]]
[[if(!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf)), alias(CNL_fputc...)]]
[[userimpl, requires((defined(__CRT_DOS) && $has_function(_flsbuf)) || $has_function(crt_fwrite_unlocked))]]
int fputc_unlocked(int ch, [[nonnull]] $FILE *__restrict stream) {
@@pp_if defined(__CRT_DOS) && $has_function(_flsbuf)@@
	return --stream->__f_cnt >= 0 ? (int)((__UINT8_TYPE__)(*stream->__f_ptr++ = (char)ch)) : _flsbuf(ch, stream);
@@pp_else@@
	unsigned char byte = (unsigned char)(unsigned int)ch;
	if (!crt_fwrite_unlocked(&byte, sizeof(unsigned char), 1, stream))
		return EOF;
	return ch;
@@pp_endif@@
}
%#endif /* __USE_MISC */


%[default:section(".text.crt{|.dos}.fs.utility")]

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN) || defined(__USE_DOS)
@@>> tempnam(3)
[[wunused, ATTR_MALLOC, dos_only_export_alias("_tempnam")]]
char *tempnam(char const *dir, char const *pfx);
%#endif /* __USE_MISC || __USE_XOPEN || __USE_DOS */


%
%#if defined(__USE_POSIX) || defined(__USE_DOS)
%[default:section(".text.crt{|.dos}.FILE.locked.utility")]

@@>> fdopen(3)
@@Open a new file stream by inheriting a given file descriptor `fd'
@@Note that upon success (`return != NULL'), the given `fd' will be
@@`close(2)'d once `fclose(return)' is called.
[[wunused, decl_include("<bits/types.h>")]]
[[dos_only_export_alias("_fdopen"), export_alias("_IO_fdopen")]]
$FILE *fdopen($fd_t fd, [[nonnull]] char const *__restrict modes);

@@>> fileno(3)
@@Return the underlying file descriptor number used by `stream'
[[wunused, decl_include("<bits/types.h>")]]
[[dos_only_export_alias("_fileno"), export_alias("fileno_unlocked")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("fileno_unlocked")]]
$fd_t fileno([[nonnull]] $FILE *__restrict stream);
%#endif /* __USE_POSIX || __USE_DOS */


%
%#ifdef __USE_XOPEN2K8
%[default:section(".text.crt{|.dos}.FILE.locked.access")]

@@>> fmemopen(3)
[[requires($has_function(malloc, funopen2_64))]]
[[dependency(malloc, strchr, funopen2_64, memcpy)]]
[[wunused, decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/typecore.h>", "<libc/errno.h>")]]
[[impl_include("<asm/os/stdio.h>", "<bits/types.h>")]]
[[impl_prefix(
@@push_namespace(local)@@
struct __memopen_cookie {
	byte_t *moc_base; /* [1..1] Base-pointer */
	byte_t *moc_cur;  /* [1..1] Current position */
	byte_t *moc_end;  /* [1..1] End-pointer */
};

__LOCAL_LIBC(@memopen_read@) ssize_t LIBCCALL
memopen_read(void *cookie, void *buf, size_t num_bytes) {
	size_t maxlen;
	struct __memopen_cookie *me;
	me = (struct __memopen_cookie *)cookie;
	maxlen = (size_t)(me->moc_end - me->moc_cur);
	if (maxlen > num_bytes)
		maxlen = num_bytes;
	memcpy(buf, me->moc_cur, maxlen);
	me->moc_cur += maxlen;
	return (size_t)maxlen;
}

__LOCAL_LIBC(@memopen_write@) ssize_t LIBCCALL
memopen_write(void *cookie, void const *buf, size_t num_bytes) {
	size_t maxlen;
	struct __memopen_cookie *me;
	me = (struct __memopen_cookie *)cookie;
	maxlen = (size_t)(me->moc_end - me->moc_cur);
	if (maxlen > num_bytes)
		maxlen = num_bytes;
	memcpy(me->moc_cur, buf, maxlen);
	me->moc_cur += maxlen;
	return (size_t)maxlen;
}

__LOCAL_LIBC(@memopen_seek@) off64_t LIBCCALL
memopen_seek(void *cookie, off64_t off, int whence) {
	pos64_t newpos;
	struct __memopen_cookie *me;
	size_t maxlen;
	me = (struct __memopen_cookie *)cookie;
	newpos = (pos64_t)off;
	maxlen = (size_t)(me->moc_end - me->moc_cur);
	switch (whence) {

	case SEEK_SET:
		break;

	case SEEK_CUR:
		newpos += (size_t)(me->moc_cur - me->moc_base);
		if unlikely((off64_t)newpos < 0)
			goto err_EOVERFLOW;
		break;

	case SEEK_END:
		newpos += maxlen;
		if unlikely((off64_t)newpos < 0)
			goto err_EOVERFLOW;
		break;

	default:
@@pp_ifdef EINVAL@@
		return (off64_t)libc_seterrno(EINVAL);
@@pp_else@@
		return (off64_t)libc_seterrno(1);
@@pp_endif@@
	}
	if (newpos > maxlen)
		newpos = maxlen;
	me->moc_cur = me->moc_base + (size_t)newpos;
	return (off64_t)newpos;
err_EOVERFLOW:
@@pp_ifdef EOVERFLOW@@
	return (off64_t)libc_seterrno(EOVERFLOW);
@@pp_else@@
	return (off64_t)libc_seterrno(1);
@@pp_endif@@
}

__LOCAL_LIBC(@memopen_close@) int LIBCCALL
memopen_close(void *cookie) {
@@pp_if $has_function(free)@@
	free(cookie);
@@pp_endif@@
	return 0;
}
@@pop_namespace@@
)]]
$FILE *fmemopen([[inoutp(len)]] void *mem, $size_t len,
                [[nonnull]] char const *modes) {
	FILE *result;
	struct __NAMESPACE_LOCAL_SYM __memopen_cookie *magic;
	magic = (struct __NAMESPACE_LOCAL_SYM __memopen_cookie *)malloc(sizeof(struct __NAMESPACE_LOCAL_SYM __memopen_cookie));
	if unlikely(!magic)
		return NULL;
	magic->moc_base = (byte_t *)mem;
	magic->moc_cur  = (byte_t *)mem;
	magic->moc_end  = (byte_t *)mem + len;
	/* Open a custom file-stream. */
	result = funopen2_64(magic,
	                     &__NAMESPACE_LOCAL_SYM memopen_read,
	                     (strchr(modes, 'w') || strchr(modes, '+'))
	                     ? &__NAMESPACE_LOCAL_SYM memopen_write
	                     : NULL,
	                     &__NAMESPACE_LOCAL_SYM memopen_seek,
	                     NULL,
	                     &__NAMESPACE_LOCAL_SYM memopen_close);
@@pp_if $has_function(free)@@
	if unlikely(!result)
		free(magic);
@@pp_endif@@
	return result;
}

@@>> open_memstream(3)
[[wunused, decl_include("<hybrid/typecore.h>")]]
[[requires($has_function(malloc, funopen2_64) && ($has_function(recalloc) || $has_function(realloc)))]]
[[dependency(memcpy, bzero, malloc, realloc, recalloc, funopen2_64, free)]]
[[impl_include("<hybrid/typecore.h>", "<libc/errno.h>", "<bits/types.h>")]]
[[impl_include("<asm/os/stdio.h>", "<hybrid/__overflow.h>")]]
[[impl_prefix(
@@push_namespace(local)@@
struct __memstream_file {
	byte_t **mf_pbase; /* Pointer to the user-defined base field. */
	size_t  *mf_psize; /* Pointer to the user-defined size field. */
	byte_t  *mf_base;  /* [0..1][owned] Allocated base pointer. */
	byte_t  *mf_ptr;   /* [0..1] Current read/write pointer (May be located beyond `mf_end'; allocated lazily during writes). */
	byte_t  *mf_end;   /* [0..1] Allocated buffer end pointer. */
};

__LOCAL_LIBC(@memstream_read@) ssize_t LIBCCALL
memstream_read(void *cookie, void *buf, size_t num_bytes) {
	struct __memstream_file *me;
	size_t maxread;
	me = (struct __memstream_file *)cookie;
	maxread = me->mf_end - me->mf_ptr;
	if (maxread > num_bytes)
		maxread = num_bytes;
	memcpy(buf, me->mf_ptr, maxread);
	me->mf_ptr += maxread;
	return (ssize_t)maxread;
}

__LOCAL_LIBC(@memstream_write@) ssize_t LIBCCALL
memstream_write(void *cookie, void const *buf, size_t num_bytes) {
	struct __memstream_file *me;
	size_t new_alloc, result = 0;
	byte_t *new_buffer;
	me = (struct __memstream_file *)cookie;
	if likely(me->mf_ptr < me->mf_end) {
		result = me->mf_end - me->mf_ptr;
		if (result > num_bytes)
			result = num_bytes;
		memcpy(me->mf_ptr, buf, num_bytes);
		me->mf_ptr += result;
		buf = (byte_t const *)buf + result;
		num_bytes -= result;
	}
	if (!num_bytes)
		goto done;
	/* Allocate more memory. */
	new_alloc = (size_t)(me->mf_ptr - me->mf_base);
	if unlikely(__hybrid_overflow_uadd(new_alloc, num_bytes, &new_alloc))
		goto err_EOVERFLOW;
@@pp_if $has_function(recalloc)@@
	/* Try  to use  recalloc() to  do the  zero-initialization for us.
	 * Since this is the only place where a buffer is ever  allocated,
	 * this also means that any newly allocated buffer space is always
	 * zero-initialized, and we  don't have to  worry about any  delta
	 * between `end - base' and `malloc_usable_size()'. */
	new_buffer = (byte_t *)recalloc(me->mf_base,
	                                (new_alloc + 1) *
	                                sizeof(char));
	if unlikely(!new_buffer)
		goto err;
@@pp_else@@
	new_buffer = (byte_t *)realloc(me->mf_base,
	                               (new_alloc + 1) *
	                               sizeof(char));
	if unlikely(!new_buffer)
		goto err;
	{
		/* Zero-initialize newly allocated memory (that won't be overwritten in a moment) */
		size_t oldsiz, baspos;
		oldsiz = (size_t)(me->mf_end - me->mf_base);
		baspos = (size_t)(me->mf_ptr - me->mf_base);
		if (baspos > oldsiz)
			bzero(new_buffer + oldsiz, (baspos - oldsiz) * sizeof(char));
	}
@@pp_endif@@
	me->mf_ptr  = new_buffer + (me->mf_ptr - me->mf_base);
	me->mf_base = new_buffer;
	me->mf_end  = new_buffer + new_alloc;
	/* Copy data into the new portion of the buf. */
	memcpy(me->mf_ptr, buf, num_bytes);
	*me->mf_end = 0; /* NUL-termination. */
	result += num_bytes;
	/* Update the user-given pointer locations with buf parameters. */
	*me->mf_pbase = me->mf_base;
	*me->mf_psize = (size_t)(me->mf_end - me->mf_base);
done:
	return (ssize_t)result;
err_EOVERFLOW:
@@pp_ifdef EOVERFLOW@@
	libc_seterrno(EOVERFLOW);
@@pp_else@@
	libc_seterrno(1);
@@pp_endif@@
err:
	return -1;
}

__LOCAL_LIBC(@memstream_seek@) off64_t LIBCCALL
memstream_seek(void *cookie, off64_t off, int whence) {
	struct __memstream_file *me;
	off64_t new_pos;
	me = (struct __memstream_file *)cookie;
	new_pos = (off64_t)(pos64_t)(size_t)(me->mf_ptr - me->mf_base);
	switch (whence) {

	case __SEEK_SET:
		new_pos = off;
		break;

	case __SEEK_CUR:
		new_pos += off;
		break;

	case __SEEK_END:
		new_pos = (size_t)(me->mf_end - me->mf_base) + off;
		break;

	default:
@@pp_ifdef EINVAL@@
		return (off64_t)libc_seterrno(EINVAL);
@@pp_else@@
		return (off64_t)libc_seterrno(1);
@@pp_endif@@
	}
	if unlikely(new_pos < 0)
		goto err_EOVERFLOW;
	/* Update the actual buffer read/write pointer. */
	if unlikely(__hybrid_overflow_uadd((uintptr_t)me->mf_base,
	                                   (pos64_t)new_pos,
	                                   (uintptr_t *)&me->mf_ptr))
		goto err_EOVERFLOW;
	return (off64_t)new_pos;
err_EOVERFLOW:
@@pp_ifdef EOVERFLOW@@
	return (off64_t)libc_seterrno(EOVERFLOW);
@@pp_else@@
	return (off64_t)libc_seterrno(1);
@@pp_endif@@
}

__LOCAL_LIBC(@memstream_close@) int LIBCCALL
memstream_close(void *cookie) {
@@pp_if $has_function(free)@@
	free(cookie);
@@pp_endif@@
	return 0;
}

@@pop_namespace@@
)]]
$FILE *open_memstream(char **bufloc, $size_t *sizeloc) {
	FILE *result;
	struct __NAMESPACE_LOCAL_SYM __memstream_file *magic;
	magic = (struct __NAMESPACE_LOCAL_SYM __memstream_file *)malloc(sizeof(struct __NAMESPACE_LOCAL_SYM __memstream_file));
	if unlikely(!magic)
		return NULL;
	magic->mf_pbase = (byte_t **)bufloc;
	magic->mf_psize = sizeloc;
	magic->mf_base  = NULL;
	magic->mf_ptr   = NULL;
	magic->mf_end   = NULL;
	/* Open a custom file-stream. */
	result = funopen2_64(magic,
	                     &__NAMESPACE_LOCAL_SYM memstream_read,
	                     &__NAMESPACE_LOCAL_SYM memstream_write,
	                     &__NAMESPACE_LOCAL_SYM memstream_seek,
	                     NULL,
	                     &__NAMESPACE_LOCAL_SYM memstream_close);
@@pp_if $has_function(free)@@
	if unlikely(!result)
		free(magic);
@@pp_endif@@
	return result;
}


%[default:section(".text.crt{|.dos}.FILE.locked.read.read")]
%[insert:function(__getdelim = getdelim)]

@@>> getdelim(3)
[[cp_stdio, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("getdelim_unlocked")]]
[[alias("getdelim_unlocked"), export_alias("__getdelim", "_IO_getdelim")]]
[[requires_function(realloc, fgetc, ungetc)]]
[[impl_include("<asm/crt/stdio.h>", "<hybrid/__assert.h>")]]
$ssize_t getdelim([[nonnull]] char **__restrict lineptr,
                  [[nonnull]] $size_t *__restrict pcount, int delimiter,
                  [[nonnull]] $FILE *__restrict stream) {
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
			__hybrid_assert(new_bufsize > result + 1);
			buffer = (char *)realloc(buffer,
			                         new_bufsize *
			                         sizeof(char));
			if unlikely(!buffer)
				return -1;
			bufsize  = new_bufsize;
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

@@>> getline(3)
[[cp_stdio, wunused, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("getline_unlocked")]]
[[alias("getline_unlocked"), export_alias("__getline", "_IO_getline")]]
[[requires_function(getdelim)]]
$ssize_t getline([[nonnull]] char **__restrict lineptr,
                 [[nonnull]] $size_t *__restrict pcount,
                 [[nonnull]] $FILE *__restrict stream) {
	return getdelim(lineptr, pcount, '\n', stream);
}

%#endif /* __USE_XOPEN2K8 */


%
%#if defined(__USE_POSIX) || defined(__USE_REENTRANT)
%[insert:function(getc_unlocked = fgetc_unlocked)]
%[insert:function(putc_unlocked = fputc_unlocked)]

%[default:section(".text.crt{|.dos}.FILE.unlocked.read.getc")]

@@>> getchar_unlocked(3)
@@Same as `getchar()', but performs I/O without acquiring a lock to `stdin'
[[cp_stdio, impl_include("<libc/template/stdstreams.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdin) && $has_function(fgetc_unlocked))]]
int getchar_unlocked() {
	return fgetc_unlocked(stdin);
}

%[default:section(".text.crt{|.dos}.FILE.unlocked.write.putc")]

@@>> putchar_unlocked(3)
@@Same as `putchar()', but performs I/O without acquiring a lock to `stdout'
[[cp_stdio, crtbuiltin, impl_include("<libc/template/stdstreams.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdout) && $has_function(fputc_unlocked))]]
int putchar_unlocked(int ch) {
	return fputc_unlocked(ch, stdout);
}

%[default:section(".text.crt{|.dos}.FILE.locked.utility")]

@@>> flockfile(3)
@@Acquire a lock to `stream' and block until doing so succeeds
[[cp, dos_only_export_alias("_lock_file"), export_alias("_IO_flockfile")]]
void flockfile([[nonnull]] $FILE *__restrict stream);

@@>> funlockfile(3)
@@Release a previously acquired lock from `stream'
[[dos_only_export_alias("_unlock_file"), export_alias("_IO_funlockfile")]]
void funlockfile([[nonnull]] $FILE *__restrict stream);

@@>> ftrylockfile(3)
@@Try to acquire a lock to `stream'
@@@return: == 0 : Lock successfully acquired
@@@return: != 0 : Failed to acquire lock
[[wunused, export_alias("_IO_ftrylockfile")]]
int ftrylockfile([[nonnull]] $FILE *__restrict stream);
%#endif /* __USE_POSIX || __USE_REENTRANT */

@@>> __uflow(3)
@@This is essentially gLibc's version of `_filbuf(3)' (but sadly not binary compatible)
[[wunused]] int __uflow([[nonnull]] FILE *stream) = _filbuf;

@@>> __overflow(3)
@@This is essentially gLibc's version of `_flsbuf(3)' (but sadly not binary compatible)
[[cp_stdio, section(".text.crt{|.dos}.FILE.locked.write.write")]]
[[requires_function(_flsbuf)]]
int __overflow([[nonnull]] $FILE *stream, int ch) {
	return _flsbuf(ch, stream);
}



%
%#ifdef __USE_POSIX
%[default:section(".text.crt{|.dos}.io.tty")]
%[insert:extern(ctermid)]
%#endif /* __USE_POSIX */

%
%#ifdef __USE_REENTRANT
%[insert:extern(ctermid_r)] /* NOTE: The feature-check for `ctermid_r()' here is guessed! */
%#endif /* __USE_REENTRANT */


%
%#ifdef __USE_XOPEN
%[insert:extern(cuserid)]
%#endif /* Use X/Open, but not issue 6.  */




%
%#ifdef __USE_POSIX2
%[default:section(".text.crt{|.dos}.FILE.utility.popen")]

@@>> popen(3)
@@Open and return a new process I/O stream for executing `command'
@@@param: command: The command to execute (s.a. `shexec(3)')
@@@param: modes:   One of "r", "w", "re" or "we" ('e' sets  O_CLOEXEC
@@                 for the internal file descriptor within the parent
@@                 process)
[[cp, wunused, dos_only_export_alias("_popen"), export_alias("_IO_popen")]]
$FILE *popen([[nonnull]] char const *command,
             [[nonnull]] char const *modes);

@@>> pclose(3)
@@Close a process I/O file `stream' (s.a. `popen(3)')
[[dos_only_export_alias("_pclose")]]
int pclose([[nonnull]] $FILE *stream);

%#endif /* __USE_POSIX2 */

%
%#ifdef __USE_NETBSD
%{
#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */
}

%[define(DEFINE_TARGV =
@@pp_ifndef __TARGV@@
@@pp_ifdef __USE_DOS_ALTERATIONS@@
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
@@pp_else@@
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
@@pp_endif@@
@@pp_endif@@
)]

@@>> popenve(3)
@@Similar to `popen(3)', but rather than running `shexec(command)', this
@@function will `execve(path, argv, envp)'. The returned FILE must still
@@be closed using `pclose(3)', rather than `fclose(3)'
[[cp, wunused, argument_names(path, ___argv, ___envp, modes)]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
$FILE *popenve([[nonnull]] char const *path,
               [[nonnull]] __TARGV, [[nonnull]] __TENVP,
               [[nonnull]] char const *modes);
%#endif /* __USE_NETBSD */

%
%#if (defined(__USE_MISC) || defined(__USE_DOS) || \
%     (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K)))

%[default:section(".text.crt{|.dos}.FILE.locked.read.getc")]

@@>> getw(3)
@@Similar to `getc()', but read 2 bytes
[[cp_stdio, dos_only_export_alias("_getw")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("getw_unlocked")]]
[[requires_function(fread), impl_include("<asm/crt/stdio.h>")]]
int getw([[nonnull]] $FILE *__restrict stream) {
	u16 result;
	return fread(&result, sizeof(result), 1, stream)
	       ? (int)result
	       : (int)EOF;
}

%[default:section(".text.crt{|.dos}.FILE.locked.write.putc")]

@@>> putw(3)
@@Similar to `putc()', but write 2 bytes loaded from `W & 0xffff'
[[cp_stdio, dos_only_export_alias("_putw")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("putw_unlocked")]]
[[requires_function(fwrite), impl_include("<asm/crt/stdio.h>")]]
int putw(int w, [[nonnull]] $FILE *__restrict stream) {
	u16 c = (u16)w;
	return fwrite(&c, sizeof(c), 1, stream)
	       ? w
	       : EOF;
}


%#endif /* __USE_MISC || __USE_DOS || (__USE_XOPEN && !__USE_XOPEN2K) */


%
%#if defined(__USE_GNU) || defined(__USE_DOS)
%[default:section(".text.crt.dos.FILE.utility")]

@@>> fcloseall(3)
@@Close all opened files
[[stdio_throws, dos_only_export_alias("_fcloseall")]]
int fcloseall();
%#endif /* __USE_GNU || __USE_DOS */

%
%#ifdef __USE_GNU

%[define(DEFINE_FOPENCOOKIE_HOLDER =
@@pp_ifndef ____fopencookie_holder_defined@@
@@push_namespace(local)@@
#define ____fopencookie_holder_defined
struct __fopencookie_holder {
	void                     *foch_cookie; /* User-defined `magic_cookie' */
	_IO_cookie_io_functions_t foch_funcs;  /* Cookie functions */
};
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_FOPENCOOKIE_TO_FUNOPEN_CLOSEFN =
@@pp_ifndef __fopencookie_to_funopen_closefn_defined@@
@@push_namespace(local)@@
#define __fopencookie_to_funopen_closefn_defined
__LOCAL_LIBC(fopencookie_to_funopen_closefn) int
(__LIBKCALL fopencookie_to_funopen_closefn)(void *cookie) {
	int result = 0;
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	if (holder->foch_funcs.@close@ != NULL)
		result = (*holder->foch_funcs.@close@)(holder->foch_cookie);
@@pp_if $has_function(free)@@
	free(holder);
@@pp_endif@@
	return result;
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_FOPENCOOKIE_TO_FUNOPEN_READFN =
@@pp_ifndef __fopencookie_to_funopen_readfn_defined@@
@@push_namespace(local)@@
#define __fopencookie_to_funopen_readfn_defined
__LOCAL_LIBC(fopencookie_to_funopen_readfn) int
(__LIBKCALL fopencookie_to_funopen_readfn)(void *cookie, char *buf, int num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (int)(*holder->foch_funcs.@read@)(holder->foch_cookie, buf, (size_t)(unsigned int)num_bytes);
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_FOPENCOOKIE_TO_FUNOPEN2_READFN =
@@pp_ifndef __fopencookie_to_funopen2_readfn_defined@@
@@push_namespace(local)@@
#define __fopencookie_to_funopen2_readfn_defined
__LOCAL_LIBC(fopencookie_to_funopen2_readfn) ssize_t
(__LIBKCALL fopencookie_to_funopen2_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (*holder->foch_funcs.@read@)(holder->foch_cookie, (char *)buf, num_bytes);
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_FOPENCOOKIE_TO_FUNOPEN_WRITEFN =
@@pp_ifndef __fopencookie_to_funopen_writefn_defined@@
@@push_namespace(local)@@
#define __fopencookie_to_funopen_writefn_defined
__LOCAL_LIBC(fopencookie_to_funopen_writefn) int
(__LIBKCALL fopencookie_to_funopen_writefn)(void *cookie, char const *buf, int num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (int)(*holder->foch_funcs.@write@)(holder->foch_cookie, buf, (size_t)(unsigned int)num_bytes);
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_FOPENCOOKIE_TO_FUNOPEN2_WRITEFN =
@@pp_ifndef __fopencookie_to_funopen2_writefn_defined@@
@@push_namespace(local)@@
#define __fopencookie_to_funopen2_writefn_defined
__LOCAL_LIBC(fopencookie_to_funopen2_writefn) ssize_t
(__LIBKCALL fopencookie_to_funopen2_writefn)(void *cookie, void const *buf, size_t num_bytes) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	return (*holder->foch_funcs.@write@)(holder->foch_cookie, (char const *)buf, num_bytes);
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_FOPENCOOKIE_TO_FUNOPEN_SEEKFN =
@@pp_ifndef __fopencookie_to_funopen_seekfn_defined@@
@@push_namespace(local)@@
#define __fopencookie_to_funopen_seekfn_defined
__LOCAL_LIBC(fopencookie_to_funopen_seekfn) __FS_TYPE(@off@)
(__LIBKCALL fopencookie_to_funopen_seekfn)(void *cookie, __FS_TYPE(@off@) off, int whence) {
@@pp_if __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__@@
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
@@pp_ifdef __USE_KOS_ALTERATIONS@@
	if ((*holder->foch_funcs.@seek@)(holder->foch_cookie, (pos64_t *)&off, whence) != 0)
		return -1;
@@pp_else@@
	if ((*holder->foch_funcs.@seek@)(holder->foch_cookie, (off64_t *)&off, whence) != 0)
		return -1;
@@pp_endif@@
	return off;
@@pp_else@@
@@pp_ifdef __USE_KOS_ALTERATIONS@@
	pos64_t newpos = (pos64_t)off;
@@pp_else@@
	off64_t newpos = off;
@@pp_endif@@
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
	if ((*holder->foch_funcs.@seek@)(holder->foch_cookie, &newpos, whence) != 0)
		return -1;
	return (__FS_TYPE(@off@))newpos;
@@pp_endif@@
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_FOPENCOOKIE_TO_FUNOPEN64_SEEKFN =
@@pp_ifndef __fopencookie_to_funopen64_seekfn_defined@@
@@push_namespace(local)@@
#define __fopencookie_to_funopen64_seekfn_defined
__LOCAL_LIBC(fopencookie_to_funopen64_seekfn) off64_t
(__LIBKCALL fopencookie_to_funopen64_seekfn)(void *cookie, off64_t off, int whence) {
	struct __fopencookie_holder *holder;
	holder = (struct __fopencookie_holder *)cookie;
@@pp_ifdef __USE_KOS_ALTERATIONS@@
	if ((*holder->foch_funcs.@seek@)(holder->foch_cookie, (pos64_t *)&off, whence) != 0)
		return -1;
@@pp_else@@
	if ((*holder->foch_funcs.@seek@)(holder->foch_cookie, &off, whence) != 0)
		return -1;
@@pp_endif@@
	return off;
}
@@pop_namespace@@
@@pp_endif@@
)]


[[ignore, wunused, decl_include("<libio.h>")]]
[[doc_alias("fopencookie"), nocrt, alias("fopencookie")]]
$FILE *crt_fopencookie(void *__restrict magic_cookie,
                       [[nonnull]] char const *__restrict modes,
                       $cookie_io_functions_t io_funcs);


@@>> fopencookie(3)
[[wunused, section(".text.crt{|.dos}.FILE.locked.access")]]
[[decl_include("<libio.h>")]]
[[requires($has_function(malloc) && ($has_function(funopen) || $has_function(funopen2)))]]
[[impl_include("<libio.h>")]]
[[impl_include("<features.h>")]]
[[impl_include("<bits/types.h>")]]
[[impl_prefix(DEFINE_FOPENCOOKIE_HOLDER)]]
[[impl_prefix(
DEFINE_FOPENCOOKIE_TO_FUNOPEN_CLOSEFN
@@pp_if !defined(__BUILDING_LIBC) && $crt_has_function(funopen64) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__@@
DEFINE_FOPENCOOKIE_TO_FUNOPEN_READFN
DEFINE_FOPENCOOKIE_TO_FUNOPEN_WRITEFN
DEFINE_FOPENCOOKIE_TO_FUNOPEN64_SEEKFN
@@pp_elif !defined(__BUILDING_LIBC) && $crt_has_function(funopen) && !$crt_has_function(funopen2_64) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__@@
DEFINE_FOPENCOOKIE_TO_FUNOPEN_READFN
DEFINE_FOPENCOOKIE_TO_FUNOPEN_WRITEFN
DEFINE_FOPENCOOKIE_TO_FUNOPEN_SEEKFN
@@pp_elif $has_function(funopen2_64)@@
DEFINE_FOPENCOOKIE_TO_FUNOPEN2_READFN
DEFINE_FOPENCOOKIE_TO_FUNOPEN2_WRITEFN
DEFINE_FOPENCOOKIE_TO_FUNOPEN64_SEEKFN
@@pp_elif $has_function(funopen2)@@
DEFINE_FOPENCOOKIE_TO_FUNOPEN2_READFN
DEFINE_FOPENCOOKIE_TO_FUNOPEN2_WRITEFN
DEFINE_FOPENCOOKIE_TO_FUNOPEN_SEEKFN
@@pp_elif $has_function(funopen64)@@
DEFINE_FOPENCOOKIE_TO_FUNOPEN_READFN
DEFINE_FOPENCOOKIE_TO_FUNOPEN_WRITEFN
DEFINE_FOPENCOOKIE_TO_FUNOPEN64_SEEKFN
@@pp_else@@
DEFINE_FOPENCOOKIE_TO_FUNOPEN_READFN
DEFINE_FOPENCOOKIE_TO_FUNOPEN_WRITEFN
DEFINE_FOPENCOOKIE_TO_FUNOPEN_SEEKFN
@@pp_endif@@
)]]
$FILE *fopencookie(void *__restrict magic_cookie,
                   [[nonnull]] char const *__restrict modes,
                   $cookie_io_functions_t io_funcs) {
	FILE *result;
	struct __NAMESPACE_LOCAL_SYM __fopencookie_holder *holder;
	(void)modes; /* unused... */
	holder = (struct __NAMESPACE_LOCAL_SYM __fopencookie_holder *)malloc(sizeof(struct __NAMESPACE_LOCAL_SYM __fopencookie_holder));
	if unlikely(!holder)
		return NULL;
	holder->foch_cookie        = magic_cookie;
	holder->foch_funcs.@read@  = io_funcs.@read@;
	holder->foch_funcs.@write@ = io_funcs.@write@;
	holder->foch_funcs.@seek@  = io_funcs.@seek@;
	holder->foch_funcs.@close@ = io_funcs.@close@;
@@pp_if !defined(__BUILDING_LIBC) && $crt_has_function(funopen64) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__@@
	result = funopen64(/* cookie:  */ holder,
	                   /* readfn:  */ io_funcs.@read@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_readfn : NULL,
	                   /* writefn: */ io_funcs.@write@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_writefn : NULL,
	                   /* seekfn:  */ io_funcs.@seek@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen64_seekfn : NULL,
	                   /* closefn: */ &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_closefn);
@@pp_elif !defined(__BUILDING_LIBC) && $crt_has_function(funopen) && !$crt_has_function(funopen2_64) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__@@
	result = funopen(/* cookie:  */ holder,
	                 /* readfn:  */ io_funcs.@read@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_readfn : NULL,
	                 /* writefn: */ io_funcs.@write@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_writefn : NULL,
	                 /* seekfn:  */ io_funcs.@seek@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_seekfn : NULL,
	                 /* closefn: */ io_funcs.@seek@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_closefn : NULL);
@@pp_elif $has_function(funopen2_64)@@
	result = funopen2_64(/* cookie:  */ holder,
	                     /* readfn:  */ io_funcs.@read@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen2_readfn : NULL,
	                     /* writefn: */ io_funcs.@write@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen2_writefn : NULL,
	                     /* seekfn:  */ io_funcs.@seek@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen64_seekfn : NULL,
	                     /* flushfn: */ NULL,
	                     /* closefn: */ &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_closefn);
@@pp_elif $has_function(funopen2)@@
	result = funopen2(/* cookie:  */ holder,
	                  /* readfn:  */ io_funcs.@read@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen2_readfn : NULL,
	                  /* writefn: */ io_funcs.@write@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen2_writefn : NULL,
	                  /* seekfn:  */ io_funcs.@seek@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_seekfn : NULL,
	                  /* flushfn: */ NULL,
	                  /* closefn: */ &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_closefn);
@@pp_elif $has_function(funopen64)@@
	result = funopen64(/* cookie:  */ holder,
	                   /* readfn:  */ io_funcs.@read@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_readfn : NULL,
	                   /* writefn: */ io_funcs.@write@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_writefn : NULL,
	                   /* seekfn:  */ io_funcs.@seek@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen64_seekfn : NULL,
	                   /* closefn: */ &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_closefn);
@@pp_else@@
	result = funopen(/* cookie:  */ holder,
	                 /* readfn:  */ io_funcs.@read@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_readfn : NULL,
	                 /* writefn: */ io_funcs.@write@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_writefn : NULL,
	                 /* seekfn:  */ io_funcs.@seek@ ? &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_seekfn : NULL,
	                 /* closefn: */ &__NAMESPACE_LOCAL_SYM fopencookie_to_funopen_closefn);
@@pp_endif@@
@@pp_if $has_function(free)@@
	if unlikely(!result)
		free(holder);
@@pp_endif@@
	return result;
}



%[default:section(".text.crt{|.dos}.FILE.unlocked.read.read")]

@@>> fgets_unlocked(3)
@@Same as `fgets()', but performs I/O without acquiring a lock to `stream'
[[cp_stdio, alias("fgets"), wunused, decl_include("<features.h>")]]
[[impl_include("<hybrid/typecore.h>", "<asm/crt/stdio.h>", "<libc/errno.h>")]]
[[requires($has_function(fgetc_unlocked) && $has_function(ungetc_unlocked) && $has_function(ferror_unlocked))]]
char *fgets_unlocked([[outp(min(strlen(return), bufsize))]] char *__restrict buf,
                     __STDC_INT_AS_SIZE_T bufsize, [[nonnull]] $FILE *__restrict stream) {
	$size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
@@pp_ifdef ERANGE@@
		(void)libc_seterrno(ERANGE);
@@pp_endif@@
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

%[default:section(".text.crt{|.dos}.FILE.unlocked.write.write")]

@@>> fputs_unlocked(3)
@@Same as `fputs()', but performs I/O without acquiring a lock to `stream'
[[cp_stdio, decl_include("<features.h>")]]
[[crtbuiltin, alias("fputs")]]
[[requires_function(fwrite_unlocked)]]
__STDC_INT_AS_SIZE_T fputs_unlocked([[nonnull]] char const *__restrict string,
                                    [[nonnull]] $FILE *__restrict stream) {
	__STDC_INT_AS_SIZE_T result;
	result = fwrite_unlocked(string,
	                         sizeof(char),
	                         strlen(string),
	                         stream);
	return result;
}

%
%struct obstack;

%[default:section(".text.crt{|.dos}.heap.obstack")]

@@>> obstack_printf(3), obstack_vprintf(3)
@@Append formated strings to a given obstack. s.a. `obstack_printer(3)'
[[decl_include("<features.h>"), decl_prefix(struct obstack;), requires_function(obstack_printer)]]
__STDC_INT_AS_SIZE_T obstack_vprintf([[nonnull]] struct obstack *__restrict self,
                                     [[nonnull, format]] char const *__restrict format,
                                     $va_list args) {
	return (__STDC_INT_AS_SIZE_T)format_vprintf(&obstack_printer, self, format, args);
}

[[decl_include("<features.h>"), decl_prefix(struct obstack;), doc_alias("obstack_vprintf")]]
__STDC_INT_AS_SIZE_T obstack_printf([[nonnull]] struct obstack *__restrict self,
                                    [[nonnull, format]] char const *__restrict format, ...)
	%{printf("obstack_vprintf")}
%#endif /* __USE_GNU */


%[default:section(".text.crt{|.dos}.FILE.locked.seek.seek")]
%#if defined(__USE_LARGEFILE) || defined(__USE_XOPEN2K)

@@>> fseeko(3), fseeko64(3)
@@Change the current in-file position of `stream'
[[decl_include("<bits/types.h>")]]
[[stdio_throws, no_crt_self_import, no_crt_self_export, export_as(CNL_fseeko...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                 __FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_fseek...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fseeko64...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                 __FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_LONG__), crt_intern_alias("fseek")]]
[[userimpl, requires($has_function(crt_fseeko64) || $has_function(crt_fseeko) || $has_function(crt_fseek))]]
int fseeko([[nonnull]] $FILE *__restrict stream, $off_t off, int whence) {
@@pp_if $has_function(crt_fseeko64)@@
	return crt_fseeko64(stream, (off64_t)off, whence);
@@pp_elif $has_function(crt_fseeko)@@
	return crt_fseeko(stream, (off32_t)off, whence);
@@pp_else@@
	return crt_fseek(stream, (long int)off, whence);
@@pp_endif@@
}

@@>> ftello(3), ftello64(3)
@@Return the current in-file position of `stream'
[[decl_include("<bits/types.h>")]]
[[stdio_throws, wunused, no_crt_self_import, no_crt_self_export, export_as(CNL_ftello...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                 __FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_ftell...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_ftello64...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                 __FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_LONG__), crt_intern_alias("ftell")]]
[[userimpl, requires($has_function(crt_fgetpos64) || $has_function(crt_fgetpos) ||
                     $has_function(crt_ftello64) || $has_function(crt_ftello) ||
                     $has_function(crt_ftell))]]
$off_t ftello([[nonnull]] $FILE *__restrict stream) {
@@pp_if defined(__USE_FILE_OFFSET64) && $has_function(crt_fgetpos64)@@
	pos64_t pos;
	if (crt_fgetpos64(stream, &pos))
		return -1;
	return (off64_t)pos;
@@pp_elif !defined(__USE_FILE_OFFSET64) && $has_function(crt_fgetpos)@@
	pos32_t pos;
	if (crt_fgetpos(stream, &pos))
		return -1;
	return (off32_t)pos;
@@pp_elif $has_function(crt_ftello64)@@
	return (off_t)crt_ftello64(stream);
@@pp_elif $has_function(crt_ftello)@@
	return (off_t)crt_ftello(stream);
@@pp_elif $has_function(crt_fgetpos64)@@
	pos64_t pos;
	if (crt_fgetpos64(stream, &pos))
		return -1;
	return (off_t)(off64_t)pos;
@@pp_elif $has_function(crt_fgetpos)@@
	pos32_t pos;
	if (crt_fgetpos(stream, &pos))
		return -1;
	return (off_t)(off32_t)pos;
@@pp_else@@
	return (off_t)crt_ftell(stream);
@@pp_endif@@
}

%#endif /* __USE_LARGEFILE || __USE_XOPEN2K */


%
%#ifdef __USE_LARGEFILE64
%[default:section(".text.crt{|.dos}.FILE.locked.access")]

[[cp, wunused]]
[[preferred_largefile64_variant_of(tmpfile), doc_alias("tmpfile")]]
$FILE *tmpfile64();

%[default:section(".text.crt{|.dos}.FILE.locked.seek.seek")]

[[doc_alias("fseeko"), decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), crt_intern_kos_alias("libc_fseeko")]]
[[stdio_throws, no_crt_self_import, no_crt_self_export, export_as(CNL_fseeko64...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if($extended_include_prefix("<features.h>")                  defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_fseeko64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[                                                                                                                                         alias(CNL_fseeko64...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[                                                                                                                                         alias(CNL_fseeko64_unlocked...)]]
[[userimpl, requires($has_function(crt_fseeko) || $has_function(crt_fseek))]]
int fseeko64([[nonnull]] $FILE *__restrict stream, $off64_t off, int whence) {
@@pp_if $has_function(crt_fseeko)@@
	return crt_fseeko(stream, (off32_t)off, whence);
@@pp_else@@
	return crt_fseek(stream, (long int)off, whence);
@@pp_endif@@
}

[[doc_alias("ftello"), decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), crt_intern_kos_alias("libc_ftello")]]
[[stdio_throws, wunused, no_crt_self_import, no_crt_self_export, export_as(CNL_ftello64...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if($extended_include_prefix("<features.h>")                  defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_ftello64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[                                                                                                                                         alias(CNL_ftello64...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[                                                                                                                                         alias(CNL_ftello64_unlocked...)]]
[[userimpl, requires($has_function(crt_fgetpos64) || $has_function(crt_fgetpos) ||
                     $has_function(crt_ftello) || $has_function(crt_ftell))]]
$off64_t ftello64([[nonnull]] $FILE *__restrict stream) {
@@pp_if $has_function(crt_fgetpos64)@@
	pos64_t pos;
	if (crt_fgetpos64(stream, &pos))
		return -1;
	return (off64_t)pos;
@@pp_elif $has_function(crt_fgetpos)@@
	pos32_t pos;
	if (crt_fgetpos(stream, &pos))
		return -1;
	return (off64_t)(off32_t)pos;
@@pp_elif $has_function(crt_ftello)@@
	return (off64_t)crt_ftello(stream);
@@pp_else@@
	return (off64_t)crt_ftell(stream);
@@pp_endif@@
}

%[default:section(".text.crt{|.dos}.FILE.locked.access")]

[[crt_dos_variant, cp, wunused]]
[[preferred_largefile64_variant_of(fopen), doc_alias("fopen")]]
$FILE *fopen64([[nonnull]] char const *__restrict filename,
               [[nonnull]] char const *__restrict modes);

[[crt_dos_variant, cp, doc_alias("freopen"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>")defined(__USE_STDIO_UNLOCKED) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)), alias("freopen_unlocked")]]
[[if($extended_include_prefix("<features.h>"                     )defined(__USE_STDIO_UNLOCKED)                                                       ), alias("freopen64_unlocked")]]
[[                                                                                                                                       largefile64_variant_of(freopen)]]
[[                                                                                                                                                       alias("freopen64")]]
[[if($extended_include_prefix(                "<asm/os/oflags.h>")                                  !defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0),  alias("freopen_unlocked")]]
[[                                                                                                                                                       alias("freopen64_unlocked")]]
$FILE *freopen64([[nonnull]] char const *__restrict filename,
                 [[nonnull]] char const *__restrict modes,
                 [[nonnull]] $FILE *__restrict stream);

%[default:section(".text.crt{|.dos}.FILE.locked.seek.pos")]

[[doc_alias("fgetpos"), decl_include("<bits/crt/stdio.h>")]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")__SIZEOF_FPOS32_T__ == __SIZEOF_FPOS64_T__), crt_intern_kos_alias("libc_fgetpos")]]
[[stdio_throws, no_crt_self_import, no_crt_self_export, export_as(CNL_fgetpos64...)]]
[[if($extended_include_prefix("<features.h>", "<bits/crt/stdio.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fgetpos_unlocked...)]]
[[if($extended_include_prefix("<features.h>")                      defined(__USE_STDIO_UNLOCKED)                                            ),   alias(CNL_fgetpos64_unlocked...)]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")                                                 __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fgetpos...)]]
[[                                                                                                                                               alias(CNL_fgetpos64...)]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")                                                 __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fgetpos_unlocked...)]]
[[                                                                                                                                               alias(CNL_fgetpos64_unlocked...)]]
[[userimpl, requires($has_function(crt_ftello64) || $has_function(crt_fgetpos) ||
                     $has_function(crt_ftello) || $has_function(crt_ftell))]]
int fgetpos64([[nonnull]] $FILE *__restrict stream, [[nonnull]] fpos64_t *__restrict pos) {
@@pp_if $has_function(crt_ftello64)@@
	return (int64_t)(*pos = (fpos64_t)crt_ftello64(stream)) < 0 ? -1 : 0;
@@pp_elif $has_function(crt_fgetpos)@@
	pos32_t pos32;
	int result = crt_fgetpos(stream, &pos32);
	if (!result)
		*pos = (fpos64_t)pos32;
	return result;
@@pp_elif $has_function(crt_ftello)@@
	return (int64_t)(*pos = (fpos64_t)crt_ftello(stream)) < 0 ? -1 : 0;
@@pp_else@@
	return (int64_t)(*pos = (fpos64_t)crt_ftell(stream)) < 0 ? -1 : 0;
@@pp_endif@@
}

[[doc_alias("fsetpos"), decl_include("<bits/crt/stdio.h>")]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")__SIZEOF_FPOS32_T__ == __SIZEOF_FPOS64_T__), crt_intern_kos_alias("libc_fsetpos")]]
[[stdio_throws, no_crt_self_import, no_crt_self_export, export_as(CNL_fsetpos64...)]]
[[if($extended_include_prefix("<features.h>", "<bits/crt/stdio.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fsetpos_unlocked...)]]
[[if($extended_include_prefix("<features.h>")                      defined(__USE_STDIO_UNLOCKED)                                              ), alias(CNL_fsetpos64_unlocked...)]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")                                                 __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fsetpos...)]]
[[                                                                                                                                               alias(CNL_fsetpos64...)]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")                                                 __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fsetpos_unlocked...)]]
[[                                                                                                                                               alias(CNL_fsetpos64_unlocked...)]]
[[userimpl, requires($has_function(crt_fsetpos) ||
                     (defined(__SEEK_SET) && ($has_function(crt_fseeko64) ||
                                              $has_function(crt_fseeko) ||
                                              $has_function(crt_fseek))))]]
int fsetpos64([[nonnull]] $FILE *__restrict stream,
              [[nonnull]] fpos64_t const *__restrict pos) {
@@pp_if defined(__SEEK_SET) && $has_function(crt_fseeko64)@@
	return crt_fseeko64(stream, (off64_t)*pos, __SEEK_SET);
@@pp_elif $has_function(crt_fsetpos)@@
	pos32_t pos32 = (pos32_t)*pos;
	return crt_fsetpos(stream, &pos32);
@@pp_elif $has_function(crt_fseeko)@@
	return crt_fseeko(stream, (off32_t)*pos, __SEEK_SET);
@@pp_else@@
	return crt_fseek(stream, (long int)*pos, __SEEK_SET);
@@pp_endif@@
}

%#endif /* __USE_LARGEFILE64 */


%
%#ifdef __USE_KOS
%[default:section(".text.crt{|.dos}.FILE.locked.write.write")]

@@>> file_printer(3)
@@For use with `format_printf()' and friends: Prints to a `FILE *' closure argument
[[decl_include("<hybrid/typecore.h>"), decl_include("<bits/crt/format-printer.h>")]]
[[cp_stdio, no_crt_dos_wrapper, cc(__FORMATPRINTER_CC)]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("file_printer_unlocked")]]
[[alias("file_printer_unlocked"), userimpl, requires_function(fwrite)]]
$ssize_t file_printer([[nonnull]] /*FILE*/ void *arg,
                      [[inp(datalen)]] char const *__restrict data,
                      $size_t datalen) {
	return (ssize_t)fwrite(data, sizeof(char), datalen, ($FILE *)arg);
}

%[default:section(".text.crt{|.dos}.FILE.unlocked.write.write")]

@@>> file_printer_unlocked(3)
@@Same as `file_printer()', but performs I/O without acquiring a lock to `(FILE *)arg'
[[decl_include("<hybrid/typecore.h>"), decl_include("<bits/crt/format-printer.h>")]]
[[cp_stdio, no_crt_dos_wrapper, cc(__FORMATPRINTER_CC)]]
[[alias("file_printer"), userimpl, requires_function(fwrite_unlocked)]]
$ssize_t file_printer_unlocked([[nonnull]] /*FILE*/ void *arg,
                               [[inp(datalen)]] char const *__restrict data,
                               $size_t datalen) {
	return (ssize_t)fwrite_unlocked(data, sizeof(char), datalen, ($FILE *)arg);
}
%#endif /* __USE_KOS */





%
%#if defined(__USE_GNU) || defined(__USE_SOLARIS) || defined(__USE_BSD)
%[default:section(".text.crt{|.dos}.heap.strdup")]

[[guard, doc_alias("asprintf"), decl_include("<features.h>")]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/__assert.h>")]]
[[requires_function(format_aprintf_pack, format_aprintf_printer, free)]]
[[impl_prefix(
#ifndef __format_aprintf_data_defined
#define __format_aprintf_data_defined
struct @format_aprintf_data@ {
	char         *@ap_base@;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owend] Buffer */
	__SIZE_TYPE__ @ap_avail@; /* Unused buffer size */
	__SIZE_TYPE__ @ap_used@;  /* Used buffer size */
};
#endif /* !__format_aprintf_data_defined */
), dependency(format_aprintf_printer)]]
__STDC_INT_AS_SSIZE_T vasprintf([[nonnull]] char **__restrict pstr,
                                [[nonnull, format]] char const *__restrict format,
                                $va_list args) {
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
		*pstr = NULL;
		return -1;
	}
	result = format_aprintf_pack(&data, NULL);
	*pstr  = result;
	if unlikely(!result)
		return -1;
	return (__STDC_INT_AS_SSIZE_T)error;
}

@@>> asprintf(3), vasprintf(3)
@@Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr'
[[guard, decl_include("<features.h>"), export_alias("__asprintf")]]
__STDC_INT_AS_SSIZE_T asprintf([[nonnull]] char **__restrict pstr,
                               [[nonnull, format]] char const *__restrict format, ...)
	%{printf("vasprintf")}

%[insert:function(__asprintf = asprintf)]
%#endif /* __USE_GNU || __USE_SOLARIS || __USE_BSD */

%{




}
%#ifdef __USE_KOS


@@>> fdreopen(3), fdreopen_unlocked(3)
@@Re-open the given `stream' as a file-stream for accessing `fd'
[[cp, decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("fdreopen_unlocked")]]
[[section(".text.crt{|.dos}.FILE.locked.access")]]
$FILE *fdreopen($fd_t fd, [[nonnull]] char const *__restrict modes,
                [[nonnull]] $FILE *__restrict stream);


%[default:section(".text.crt{|.dos}.FILE.unlocked.access")]

[[cp, doc_alias("fdreopen"), decl_include("<bits/types.h>"), alias("fdreopen")]]
$FILE *fdreopen_unlocked($fd_t fd, [[nonnull]] char const *__restrict modes,
                         [[nonnull]] $FILE *__restrict stream);

[[crt_dos_variant, cp, doc_alias("freopen"), no_crt_self_import, guard]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>")!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0), alias("freopen_unlocked")]]
[[                                                                                                                                                     alias("freopen64_unlocked")]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>")!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0), alias("freopen")]]
[[                                                                                                                                                     alias("freopen64")]]
$FILE *freopen_unlocked([[nonnull]] char const *__restrict filename,
                        [[nonnull]] char const *__restrict modes,
                        [[nonnull]] $FILE *__restrict stream);

[[crt_dos_variant, cp, doc_alias("freopen"), no_crt_self_import]]
[[                                                                                    largefile64_variant_of(freopen_unlocked)]]
[[                                                                                                    alias("freopen64_unlocked")]]
[[if($extended_include_prefix("<asm/os/oflags.h>")!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0), alias("freopen")]]
[[                                                                                                    alias("freopen64")]]
[[userimpl, requires_function(freopen64)]]
$FILE *freopen64_unlocked([[nonnull]] char const *__restrict filename,
                          [[nonnull]] char const *__restrict modes,
                          [[nonnull]] $FILE *__restrict stream) {
	return freopen64(filename, modes, stream);
}


%[default:section(".text.crt{|.dos}.FILE.unlocked.seek.seek")];

[[stdio_throws, no_crt_self_import, no_crt_self_export, export_as(CNL_fseek_unlocked...)]]
[[                                                                                     alias(CNL_fseek_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
[[                                                                                     alias(CNL_fseek...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64...)]]
[[userimpl, requires_function(fseek)]]
int fseek_unlocked([[nonnull]] $FILE *__restrict stream, long int off, int whence) {
	return fseek(stream, off, whence);
}

[[stdio_throws, wunused, no_crt_self_import, no_crt_self_export, export_as(CNL_ftell_unlocked...)]]
[[                                                                                     alias(CNL_ftell_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
[[                                                                                     alias(CNL_ftell...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64...)]]
[[userimpl, requires_function(ftell)]]
long int ftell_unlocked([[nonnull]] $FILE *__restrict stream) {
	return ftell(stream);
}

[[stdio_throws, decl_include("<bits/types.h>")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fseeko_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_fseek...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fseeko64...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), crt_intern_alias("fseek_unlocked")]]
[[userimpl, requires_function(fseeko)]]
int fseeko_unlocked([[nonnull]] $FILE *__restrict stream, $off_t off, int whence) {
	return fseeko(stream, off, whence);
}

[[stdio_throws, wunused, decl_include("<bits/types.h>")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_ftello_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_ftell...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_ftello64...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), crt_intern_alias("ftell_unlocked")]]
[[userimpl, requires_function(ftello)]]
$off_t ftello_unlocked([[nonnull]] $FILE *__restrict stream) {
	return ftello(stream);
}

[[section(".text.crt{|.dos}.FILE.unlocked.write.utility")]]
[[stdio_throws, no_crt_self_export, no_crt_self_import]]
[[export_alias(CNL_flushall_unlocked...), alias(CNL_flushall...)]]
[[userimpl, requires_function(fflush_unlocked)]]
int flushall_unlocked() {
	return fflush_unlocked(NULL);
}

%[default:section(".text.crt{|.dos}.FILE.unlocked.seek.pos")];
[[stdio_throws, decl_include("<bits/crt/stdio.h>")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fgetpos_unlocked...)]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")__SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fgetpos_unlocked...)]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")__SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__), alias(CNL_fgetpos64_unlocked...)]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")__SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fgetpos...)]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")__SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__), alias(CNL_fgetpos64...)]]
[[userimpl, requires_function(fgetpos)]]
int fgetpos_unlocked([[nonnull]] $FILE *__restrict stream,
                     [[nonnull]] $fpos_t *__restrict pos) {
	return fgetpos(stream, pos);
}

[[stdio_throws, decl_include("<bits/crt/stdio.h>")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fsetpos_unlocked...)]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")__SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fsetpos_unlocked...)]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")__SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__), alias(CNL_fsetpos64_unlocked...)]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")__SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fsetpos...)]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")__SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__), alias(CNL_fsetpos64...)]]
[[userimpl, requires_function(fsetpos)]]
int fsetpos_unlocked([[nonnull]] $FILE *__restrict stream,
                     [[nonnull]] $fpos_t const *__restrict pos) {
	return fsetpos(stream, pos);
}

[[cp_stdio, alias("getw", "_getw")]]
[[requires_function(fread_unlocked)]]
[[impl_include("<asm/crt/stdio.h>")]]
[[section(".text.crt{|.dos}.FILE.unlocked.read.getc")]]
int getw_unlocked([[nonnull]] $FILE *__restrict stream) {
	u16 result;
	return fread_unlocked(&result, sizeof(result), 1, stream)
	       ? (int)(unsigned int)result
	       : (int)EOF;
}

[[cp_stdio, alias("putw", "_putw")]]
[[requires_function(putw)]]
[[section(".text.crt{|.dos}.FILE.unlocked.write.putc")]]
int putw_unlocked(int w, [[nonnull]] $FILE *__restrict stream) {
	u16 c = (u16)w;
	return fwrite_unlocked(&c, sizeof(c), 1, stream)
	       ? w
	       : EOF;
}


[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[no_crt_self_import, no_crt_self_export]]
[[export_alias(CNL_setvbuf_unlocked...), alias(CNL_setvbuf...)]]
[[userimpl, requires_function(setvbuf)]]
[[section(".text.crt{|.dos}.FILE.unlocked.read.utility")]]
int setvbuf_unlocked([[nonnull]] $FILE *__restrict stream,
                     char *__restrict buf, __STDC_INT_AS_UINT_T modes,
                     $size_t bufsize) {
	return setvbuf(stream, buf, modes, bufsize);
}

[[no_crt_self_import, no_crt_self_export]]
[[export_alias(CNL_ungetc_unlocked...), alias(CNL_ungetc...)]]
[[userimpl, requires_function(ungetc)]]
[[section(".text.crt{|.dos}.FILE.unlocked.read.getc")]]
int ungetc_unlocked(int ch, [[nonnull]] $FILE *__restrict stream) {
	return ungetc(ch, stream);
}

[[cp_stdio, wunused, doc_alias("getdelim")]]
[[decl_include("<hybrid/typecore.h>")]]
[[alias("getdelim", "__getdelim", "_IO_getdelim")]]
[[requires_function(realloc, fgetc_unlocked, ungetc_unlocked)]]
[[impl_include("<asm/crt/stdio.h>", "<hybrid/__assert.h>")]]
[[section(".text.crt{|.dos}.FILE.unlocked.read.read")]]
$ssize_t getdelim_unlocked([[nonnull]] char **__restrict lineptr,
                           [[nonnull]] $size_t *__restrict pcount, int delimiter,
                           [[nonnull]] $FILE *__restrict stream) {
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
			__hybrid_assert(new_bufsize > result + 1);
			buffer = (char *)realloc(buffer,
			                         new_bufsize *
			                         sizeof(char));
			if unlikely(!buffer)
				goto err;
			bufsize  = new_bufsize;
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
err:
	return -1;
}

[[cp_stdio, wunused, decl_include("<hybrid/typecore.h>")]]
[[alias("getline", "__getline", "_IO_getline")]]
[[requires_function(getdelim_unlocked)]]
[[section(".text.crt{|.dos}.FILE.unlocked.read.read")]]
$ssize_t getline_unlocked([[nonnull]] char **__restrict lineptr,
                          [[nonnull]] $size_t *__restrict pcount,
                          [[nonnull]] $FILE *__restrict stream) {
	return getdelim_unlocked(lineptr, pcount, '\n', stream);
}

[[stdio_throws, alias("rewind")]]
[[userimpl, requires_function(fsetpos_unlocked)]]
[[section(".text.crt{|.dos}.FILE.unlocked.seek.utility")]]
void rewind_unlocked([[nonnull]] $FILE *__restrict stream) {
	fsetpos_unlocked(stream, 0);
}

[[wunused]]
[[userimpl, requires_function(isatty, fileno)]]
[[section(".text.crt{|.dos}.io.tty")]]
int fisatty([[nonnull]] $FILE *__restrict stream) {
	return isatty(fileno(stream));
}

%{
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __FS_TYPE(pos)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __FS_TYPE(off)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
}

%[define(DEFINE_PIO_OFFSET =
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __FS_TYPE(@pos@)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __FS_TYPE(@off@)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
)]



@@>> fftruncate(3)
@@Truncate the given file `stream' to a length of `length'
[[cp_stdio, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET)]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fftruncate...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fftruncate_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fftruncate64_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fftruncate...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fftruncate64...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fftruncate_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fftruncate64_unlocked...)]]
[[userimpl, requires_function(ftruncate, fileno)]]
[[section(".text.crt{|.dos}.FILE.locked.utility")]]
int fftruncate([[nonnull]] $FILE *__restrict stream, __PIO_OFFSET length) {
	int result = -1;
	fd_t fd = fileno(stream);
	if likely(fd >= 0)
		result = ftruncate(fd, length);
	return result;
}

@@>> fftruncate_unlocked(3)
@@Same as `fftruncate()', but don't acquire a lock to the file
[[cp_stdio, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET)]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fftruncate_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fftruncate_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fftruncate64_unlocked...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fftruncate...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fftruncate64...)]]
[[userimpl, requires_function(ftruncate, fileno_unlocked)]]
[[section(".text.crt{|.dos}.FILE.unlocked.utility")]]
int fftruncate_unlocked([[nonnull]] $FILE *__restrict stream, __PIO_OFFSET length) {
	int result = -1;
	fd_t fd = fileno_unlocked(stream);
	if likely(fd >= 0)
		result = ftruncate(fd, length);
	return result;
}


[[cp_stdio, decl_include("<features.h>")]]
[[crtbuiltin, alias("puts")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdout) && $has_function(fputs_unlocked))]]
[[impl_include("<libc/template/stdstreams.h>")]]
[[section(".text.crt{|.dos}.FILE.unlocked.write.write")]]
__STDC_INT_AS_SSIZE_T puts_unlocked([[nonnull]] char const *__restrict string) {
	__STDC_INT_AS_SSIZE_T result, temp;
	result = fputs_unlocked(string, stdout);
	if (result >= 0) {
		temp = fputc_unlocked('\n', stdout);
		if (temp <= 0)
			result = temp;
		else
			result += temp;
	}
	return result;
}

%
%#ifdef __USE_LARGEFILE64

[[stdio_throws, decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), crt_intern_kos_alias("libc_fseeko_unlocked")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fseeko64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[                                                                                        alias(CNL_fseeko64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[                                                                                        alias(CNL_fseeko64...)]]
[[userimpl, requires_function(fseeko64)]]
[[section(".text.crt{|.dos}.FILE.unlocked.seek.seek")]]
int fseeko64_unlocked([[nonnull]] $FILE *__restrict stream,
                      $off64_t off, int whence) {
	return fseeko64(stream, off, whence);
}

[[stdio_throws, wunused, decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), crt_intern_kos_alias("libc_ftello_unlocked")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_ftello64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[                                                                                        alias(CNL_ftello64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[                                                                                        alias(CNL_ftello64...)]]
[[userimpl, requires_function(ftello64)]]
[[section(".text.crt{|.dos}.FILE.unlocked.seek.seek")]]
$off64_t ftello64_unlocked([[nonnull]] $FILE *__restrict stream) {
	return ftello64(stream);
}

[[stdio_throws, decl_include("<bits/crt/stdio.h>")]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")__SIZEOF_FPOS32_T__ == __SIZEOF_FPOS64_T__), crt_intern_kos_alias("libc_fgetpos_unlocked")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fgetpos64_unlocked...)]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")__SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fgetpos_unlocked...)]]
[[                                                                                              alias(CNL_fgetpos64_unlocked...)]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")__SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fgetpos...)]]
[[                                                                                              alias(CNL_fgetpos64...)]]
[[userimpl, requires_function(fgetpos64)]]
[[section(".text.crt{|.dos}.FILE.unlocked.seek.pos")]]
int fgetpos64_unlocked([[nonnull]] $FILE *__restrict stream,
                       [[nonnull]] fpos64_t *__restrict pos) {
	return fgetpos64(stream, pos);
}


[[stdio_throws, decl_include("<bits/crt/stdio.h>")]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")__SIZEOF_FPOS32_T__ == __SIZEOF_FPOS64_T__), crt_intern_kos_alias("libc_fsetpos_unlocked")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fsetpos64_unlocked...)]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")__SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fsetpos_unlocked...)]]
[[                                                                                              alias(CNL_fsetpos64_unlocked...)]]
[[if($extended_include_prefix("<bits/crt/stdio.h>")__SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__), alias(CNL_fsetpos...)]]
[[                                                                                              alias(CNL_fsetpos64...)]]
[[userimpl, requires_function(fsetpos64)]]
[[section(".text.crt{|.dos}.FILE.unlocked.seek.pos")]]
int fsetpos64_unlocked([[nonnull]] $FILE *__restrict stream,
                       [[nonnull]] fpos64_t const *__restrict pos) {
	return fsetpos64(stream, pos);
}


@@>> fftruncate64(3)
@@Truncate the given file `stream' to a length of `length'
[[cp_stdio, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), crt_intern_kos_alias("libc_fftruncate")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fftruncate64...)]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fftruncate_unlocked...)]]
[[if($extended_include_prefix("<features.h>")                  defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_fftruncate64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fftruncate...)]]
[[                                                                                                                                         alias(CNL_fftruncate64...)]]
[[if($extended_include_prefix("<bits/types.h>")                                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fftruncate_unlocked...)]]
[[                                                                                                                                         alias(CNL_fftruncate64_unlocked...)]]
[[userimpl, requires_function(ftruncate64, fileno)]]
[[section(".text.crt{|.dos}.FILE.locked.utility")]]
int fftruncate64([[nonnull]] $FILE *__restrict stream, __PIO_OFFSET64 length) {
	int result = -1;
	fd_t fd = fileno(stream);
	if likely(fd >= 0)
		result = ftruncate64(fd, length);
	return result;
}

@@>> fftruncate64_unlocked(3)
@@Truncate the given file `stream' to a length of `length'
[[cp_stdio, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), crt_intern_kos_alias("libc_fftruncate_unlocked")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fftruncate64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fftruncate_unlocked...)]]
[[                                                                                        alias(CNL_fftruncate64_unlocked...)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fftruncate...)]]
[[                                                                                        alias(CNL_fftruncate64...)]]
[[userimpl, requires_function(ftruncate64, fileno_unlocked)]]
[[section(".text.crt{|.dos}.FILE.unlocked.utility")]]
int fftruncate64_unlocked([[nonnull]] $FILE *__restrict stream, __PIO_OFFSET64 length) {
	int result = -1;
	fd_t fd = fileno_unlocked(stream);
	if likely(fd >= 0)
		result = ftruncate64(fd, length);
	return result;
}

%#endif /* __USE_LARGEFILE64 */


%[default:section(".text.crt{|.dos}.FILE.unlocked.write.printf")]

[[cp_stdio, doc_alias("fprintf_unlocked"), decl_include("<features.h>")]]
[[alias("vfprintf", "vfprintf_s", "_IO_vfprintf")]]
[[requires_dependent_function(file_printer_unlocked)]]
__STDC_INT_AS_SSIZE_T vfprintf_unlocked([[nonnull]] $FILE *__restrict stream,
                                        [[nonnull, format]] char const *__restrict format,
                                        $va_list args) {
	return (__STDC_INT_AS_SSIZE_T)format_vprintf(&file_printer_unlocked, stream, format, args);
}

@@>> fprintf_unlocked(3), vfprintf_unlocked(3)
[[cp_stdio, decl_include("<features.h>")]]
[[crtbuiltin, dos_only_export_alias("fprintf_s")]]
__STDC_INT_AS_SSIZE_T fprintf_unlocked([[nonnull]] $FILE *__restrict stream,
                                       [[nonnull, format]] char const *__restrict format, ...)
	%{printf("vfprintf_unlocked")}

[[cp_stdio, doc_alias("printf_unlocked"), decl_include("<features.h>")]]
[[dos_only_export_alias("vprintf_s")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdout) && $has_function(vprintf))]]
[[impl_include("<libc/template/stdstreams.h>")]]
__STDC_INT_AS_SSIZE_T vprintf_unlocked([[nonnull, format]] char const *__restrict format,
                                       $va_list args) {
	return vfprintf_unlocked(stdout, format, args);
}

@@>> printf_unlocked(3), vprintf_unlocked(3)
[[cp_stdio, decl_include("<features.h>")]]
[[crtbuiltin, dos_only_export_alias("printf_s")]]
__STDC_INT_AS_SSIZE_T printf_unlocked([[nonnull, format]] char const *__restrict format, ...)
	%{printf("vprintf_unlocked")}

%[default:section(".text.crt{|.dos}.FILE.unlocked.read.scanf")]

[[cp_stdio, wunused, doc_alias("fscanf_unlocked")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[alias("vfscanf", "__vfscanf", "_vfscanf", "_vfscanf_s", "_IO_vfscanf")]]
[[requires_dependent_function(fgetc_unlocked, ungetc_unlocked)]]
[[impl_include("<hybrid/typecore.h>"), impl_prefix(
@@push_namespace(local)@@
@@pp_if !defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_SIZE_T__ != __SIZEOF_INT__@@
__LOCAL_LIBC(@vfscanf_getc_unlocked@) __format_word_t
(__FORMATPRINTER_CC vfscanf_getc_unlocked)(void *arg) {
	return (__format_word_t)fgetc_unlocked((FILE *)arg);
}
@@pp_endif@@
__LOCAL_LIBC(@vfscanf_ungetc_unlocked@) ssize_t
(__FORMATPRINTER_CC vfscanf_ungetc_unlocked)(void *arg, __format_word_t word) {
	return ungetc_unlocked((int)(unsigned char)(unsigned int)word, (FILE *)arg);
}
@@pop_namespace@@
)]]
__STDC_INT_AS_SIZE_T vfscanf_unlocked([[nonnull]] $FILE *__restrict stream,
                                      [[nonnull, format]] char const *__restrict format,
                                      $va_list args) {
@@pp_if defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_SIZE_T__ == __SIZEOF_INT__@@
	return format_vscanf((pformatgetc)(void *)&fgetc_unlocked,
	                     &__NAMESPACE_LOCAL_SYM vfscanf_ungetc_unlocked,
	                     (void *)stream,
	                     format, args);
@@pp_else@@
	return format_vscanf(&__NAMESPACE_LOCAL_SYM vfscanf_getc_unlocked,
	                     &__NAMESPACE_LOCAL_SYM vfscanf_ungetc_unlocked,
	                     (void *)stream,
	                     format, args);
@@pp_endif@@
}



[[cp_stdio, wunused, doc_alias("scanf_unlocked")]]
[[decl_include("<features.h>"), alias("_vscanf")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdin) && $has_function(vfscanf_unlocked))]]
[[impl_include("<libc/template/stdstreams.h>")]]
__STDC_INT_AS_SIZE_T vscanf_unlocked([[nonnull, format]] char const *__restrict format, $va_list args) {
	return vfscanf_unlocked(stdin, format, args);
}

@@>> fscanf_unlocked(3), vfscanf_unlocked(3)
[[cp_stdio, wunused, decl_include("<features.h>")]]
__STDC_INT_AS_SIZE_T fscanf_unlocked([[nonnull]] $FILE *__restrict stream,
                                     [[nonnull, format]] char const *__restrict format, ...)
	%{printf("vfscanf_unlocked")}

@@>> scanf_unlocked(3), vscanf_unlocked(3)
[[cp_stdio, wunused, decl_include("<features.h>")]]
__STDC_INT_AS_SIZE_T scanf_unlocked([[nonnull, format]] char const *__restrict format, ...)
	%{printf("vscanf_unlocked")}

%#endif /* __USE_KOS */


%
%#ifdef __USE_SOLARIS

%#if !defined(__USE_XOPEN) || defined(_EVERY_SOURCE)
%[insert:extern(getsubopt)]
%#endif /* !__USE_XOPEN || _EVERY_SOURCE */

%#endif /* __USE_SOLARIS */


%
%#ifdef __USE_LARGEFILE64
/* I wish I could find some <stdio.h> header that declares these (aside
 * of my own),  since I don't  really know where  exactly to put  them.
 *
 * For now, it makes sense to encapsulate them behind  _LARGEFILE64_SOURCE,
 * given that these are the 64-bit variants of fseek() and ftell(), however
 * there may be other  _*_SOURCE macros out there  that are supposed to  do
 * the same (only I can't find them...) */
%[insert:function(fseek64 = fseeko64)]
%[insert:function(ftell64 = ftello64)]
%#endif /* __USE_LARGEFILE64 */



%
%#ifdef __USE_NETBSD
%[insert:extern(fparseln)]

@@>> fmtcheck(3)
@@Check if `user_format' may be used as a drop-in replacement for `good_format'
@@in the context of a call to `printf(3)' (or `format_printf()'), such that all
@@contained format qualifiers reference the  same (or compatible) underlying  C
@@types, and in the same order.
@@If all of this is the  case, simply re-return `user_format'. Otherwise  (i.e.
@@when `user_format' isn't compatible with `good_format'), return `good_format'
@@instead. This function is meant to  be used to validate user-provided  printf
@@format strings before actually using them, after they've been read from  lang
@@config files: `printf(fmtcheck(get_user_fmt(), "%s %s"), "Foo", "Bar");'
[[guard, wunused, nonnull, attribute("__ATTR_FORMAT_ARG(2)")]]
char const *fmtcheck([[nullable]] char const *user_format,
                     [[nonnull]] char const *good_format) {
	/* TODO: Implement properly */
	COMPILER_IMPURE();
	(void)good_format;
	return user_format;
}
%#endif /* __USE_NETBSD */



%
%#ifdef __USE_BSD
%[insert:guarded_function(fpurge = __fpurge)]

@@>> fgetln(3)
@@A slightly more convenient (but way less portable) alternative to `fgets(3)'
@@This function automatically malloc's a  buffer of sufficient length for  the
@@next line in the given `stream', and stores its length in `*lenp'
@@NOTE: KOS adds the following extensions to this function:
@@ - We guaranty that "return[*lenp] == '\0'" upon a non-NULL return
@@ - You may pass `lenp == NULL', which simply ignores that argument
@@@return: NULL: The EOF flag of `stream' is set (fix this with `clearerr(3)'),
@@               or the underlying file has been fully read.
@@@return: * :   Pointer to an  automatically malloc'd  buffer (to-be  freed
@@               by  fclose(3)  once you  call  that function  on  the given
@@               `stream'). The buffer is re-used in subsequence invocations
@@               of this function, and documentation states that it may also
@@               be invalidated during any  other I/O operation relating  to
@@               `stream', tough this isn't the case under KOS.
[[guard, wunused, decl_include("<hybrid/typecore.h>")]]
char *fgetln([[nonnull]] $FILE *__restrict stream, $size_t *__restrict lenp);

%#endif /* __USE_BSD */




/************************************************************************/
/************************************************************************/
/* funopen(3) and funopen2(3)                                           */
/************************************************************************/
/************************************************************************/
%
%#if defined(__USE_BSD) || defined(__USE_KOS)

%{
#ifndef __off_t_defined
#define __off_t_defined
typedef __FS_TYPE(off) off_t;
#endif /* !__off_t_defined */
}


[[decl_include("<bits/types.h>")]]
[[ignore, guard, wunused, doc_alias("funopen"), nocrt, alias("funopen")]]
$FILE *crt_funopen32(void const *cookie,
                     int (LIBKCALL *readfn)(void *cookie, char *buf, int num_bytes),
                     int (LIBKCALL *writefn)(void *cookie, char const *buf, int num_bytes),
                     off32_t (LIBKCALL *seekfn)(void *cookie, off32_t off, int whence),
                     int (LIBKCALL *closefn)(void *cookie));

[[decl_include("<bits/types.h>")]]
[[ignore, guard, wunused, doc_alias("funopen2"), nocrt, alias("funopen2")]]
$FILE *crt_funopen2_32(void const *cookie,
                       ssize_t (LIBKCALL *readfn)(void *cookie, void *buf, size_t num_bytes),
                       ssize_t (LIBKCALL *writefn)(void *cookie, void const *buf, size_t num_bytes),
                       off32_t (LIBKCALL *seekfn)(void *cookie, off32_t off, int whence),
                       int (LIBKCALL *flushfn)(void *cookie),
                       int (LIBKCALL *closefn)(void *cookie));



/************************************************************************/
/* funopen() --> funopen2()                                             */
/************************************************************************/
%[define(DEFINE_FUNOPEN_HOLDER =
@@pp_ifndef ____funopen_holder_defined@@
@@push_namespace(local)@@
#define ____funopen_holder_defined
struct __funopen_holder {
	void            *fh_cookie;                                                 /* [?..?] funopen cookie */
	int   (LIBKCALL *fh_readfn)(void *cookie, char *buf, int num_bytes);        /* [0..1] funopen readfn */
	int   (LIBKCALL *fh_writefn)(void *cookie, char const *buf, int num_bytes); /* [0..1] funopen writefn */
	off_t (LIBKCALL *fh_seekfn)(void *cookie, off_t off, int whence);           /* [0..1] funopen seekfn */
	int   (LIBKCALL *fh_closefn)(void *cookie);                                 /* [0..1] funopen closefn */
};
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_FUNOPEN_TO_FUNOPEN2_READFN =
@@pp_ifndef __funopen_to_funopen2_readfn_defined@@
@@push_namespace(local)@@
#define __funopen_to_funopen2_readfn_defined
__LOCAL_LIBC(funopen_to_funopen2_readfn) ssize_t
(__LIBKCALL funopen_to_funopen2_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_readfn)(holder->fh_cookie, (char *)buf,
	                                     (int)(unsigned int)num_bytes);
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_FUNOPEN_TO_FUNOPEN2_WRITEFN =
@@pp_ifndef __funopen_to_funopen2_writefn_defined@@
@@push_namespace(local)@@
#define __funopen_to_funopen2_writefn_defined
__LOCAL_LIBC(funopen_to_funopen2_writefn) ssize_t
(__LIBKCALL funopen_to_funopen2_writefn)(void *cookie, void const *buf, size_t num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (ssize_t)(*holder->fh_writefn)(holder->fh_cookie, (char const *)buf,
	                                      (int)(unsigned int)num_bytes);
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_FUNOPEN_TO_FUNOPEN2_SEEKFN =
@@pp_ifndef __funopen_to_funopen2_seekfn_defined@@
@@push_namespace(local)@@
#define __funopen_to_funopen2_seekfn_defined
__LOCAL_LIBC(funopen_to_funopen2_seekfn) __FS_TYPE(@off@)
(__LIBKCALL funopen_to_funopen2_seekfn)(void *cookie, __FS_TYPE(@off@) off, int whence) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_seekfn)(holder->fh_cookie, off, whence);
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_FUNOPEN_TO_FUNOPEN2_CLOSEFN =
@@pp_ifndef __funopen_to_funopen2_closefn_defined@@
@@push_namespace(local)@@
#define __funopen_to_funopen2_closefn_defined
__LOCAL_LIBC(funopen_to_funopen2_closefn) int
(__LIBKCALL funopen_to_funopen2_closefn)(void *cookie) {
	int result = 0;
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	if (holder->fh_closefn != NULL)
		result = (*holder->fh_closefn)(holder->fh_cookie);
@@pp_if $has_function(free)@@
	free(holder);
@@pp_endif@@
	return result;
}
@@pop_namespace@@
@@pp_endif@@
)]
/************************************************************************/



/************************************************************************/
/* funopen() --> fopencookie()                                          */
/************************************************************************/
/* DEFINE_FUNOPEN_TO_FOPENCOOKIE_READFN = DEFINE_FUNOPEN_TO_FUNOPEN2_READFN */
/* DEFINE_FUNOPEN_TO_FOPENCOOKIE_WRITEFN = DEFINE_FUNOPEN_TO_FUNOPEN2_WRITEFN */
/* DEFINE_FUNOPEN_TO_FOPENCOOKIE_CLOSEFN = DEFINE_FUNOPEN_TO_FUNOPEN2_CLOSEFN */
%[define(DEFINE_FUNOPEN_TO_FOPENCOOKIE_SEEKFN =
@@pp_ifndef __funopen_to_fopencookie_seekfn_defined@@
@@push_namespace(local)@@
#define __funopen_to_fopencookie_seekfn_defined
@@pp_ifdef __USE_KOS_ALTERATIONS@@
__LOCAL_LIBC(funopen_to_fopencookie_seekfn) NONNULL((2)) int
(__LIBKCALL funopen_to_fopencookie_seekfn)(void *cookie, pos64_t *pos, int whence)
@@pp_else@@
__LOCAL_LIBC(funopen_to_fopencookie_seekfn) NONNULL((2)) int
(__LIBKCALL funopen_to_fopencookie_seekfn)(void *cookie, off64_t *pos, int whence)
@@pp_endif@@
{
	__FS_TYPE(@off@) newpos;
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	newpos = (*holder->fh_seekfn)(holder->fh_cookie, (__FS_TYPE(@off@))*pos, whence);
	if unlikely(newpos == -1)
		return -1;
@@pp_ifdef __USE_KOS_ALTERATIONS@@
	*pos = (pos64_t)(off64_t)newpos;
@@pp_else@@
	*pos = (off64_t)newpos;
@@pp_endif@@
	return 0;
}
@@pop_namespace@@
@@pp_endif@@
)]
/************************************************************************/



/************************************************************************/
/* funopen() --> funopen64()                                            */
/************************************************************************/
/* DEFINE_FUNOPEN_TO_FOPEN64_READFN = DEFINE_FUNOPEN_TO_FUNOPEN2_READFN */
/* DEFINE_FUNOPEN_TO_FOPEN64_WRITEFN = DEFINE_FUNOPEN_TO_FUNOPEN2_WRITEFN */
%[define(DEFINE_FUNOPEN_TO_FUNOPEN64_READFN =
@@pp_ifndef __funopen_to_funopen64_readfn_defined@@
@@push_namespace(local)@@
#define __funopen_to_funopen64_readfn_defined
__LOCAL_LIBC(funopen_to_funopen64_readfn) int
(__LIBKCALL funopen_to_funopen64_readfn)(void *cookie, char *buf, int num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_readfn)(holder->fh_cookie, buf, num_bytes);
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_FUNOPEN_TO_FUNOPEN64_WRITEFN =
@@pp_ifndef __funopen_to_funopen64_writefn_defined@@
@@push_namespace(local)@@
#define __funopen_to_funopen64_writefn_defined
__LOCAL_LIBC(funopen_to_funopen64_writefn) int
(__LIBKCALL funopen_to_funopen64_writefn)(void *cookie, char const *buf, int num_bytes) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_writefn)(holder->fh_cookie, buf, num_bytes);
}
@@pop_namespace@@
@@pp_endif@@
)]


/* DEFINE_FUNOPEN_TO_FOPEN64_CLOSEFN = DEFINE_FUNOPEN_TO_FUNOPEN2_CLOSEFN */
%[define(DEFINE_FUNOPEN_TO_FUNOPEN64_SEEKFN =
@@pp_ifndef __funopen_to_funopen64_seekfn_defined@@
@@push_namespace(local)@@
#define __funopen_to_funopen64_seekfn_defined
__LOCAL_LIBC(funopen_to_funopen64_seekfn) off64_t
(__LIBKCALL funopen_to_funopen64_seekfn)(void *cookie, off64_t off, int whence) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_seekfn)(holder->fh_cookie, (__FS_TYPE(@off@))off, whence);
}
@@pop_namespace@@
@@pp_endif@@
)]
/************************************************************************/




@@>> funopen(3), funopen64(3)
[[guard, wunused, decl_include("<features.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias("funopen")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias("funopen64")]]
[[requires_include("<hybrid/typecore.h>")]]
[[requires((__SIZEOF_INT__ == __SIZEOF_SIZE_T__ && $has_function(funopen2)) ||
           ($has_function(malloc) && ($has_function(funopen2) ||
                                      $has_function(crt_fopencookie) ||
                                      $has_function(funopen64))))]]
[[impl_prefix(
@@pp_if __SIZEOF_INT__ != __SIZEOF_SIZE_T__ || !$has_function(funopen2)@@
DEFINE_FUNOPEN_HOLDER
DEFINE_FUNOPEN_TO_FUNOPEN2_CLOSEFN
@@pp_if $has_function(funopen2)@@
DEFINE_FUNOPEN_TO_FUNOPEN2_READFN
DEFINE_FUNOPEN_TO_FUNOPEN2_WRITEFN
DEFINE_FUNOPEN_TO_FUNOPEN2_SEEKFN
@@pp_elif $has_function(crt_fopencookie)@@
DEFINE_FUNOPEN_TO_FUNOPEN2_READFN
DEFINE_FUNOPEN_TO_FUNOPEN2_WRITEFN
DEFINE_FUNOPEN_TO_FOPENCOOKIE_SEEKFN
#include <libio.h>
@@pp_else@@
@@pp_if __SIZEOF_INT__ == __SIZEOF_SIZE_T__@@
DEFINE_FUNOPEN_TO_FUNOPEN2_READFN
DEFINE_FUNOPEN_TO_FUNOPEN2_WRITEFN
@@pp_else@@
DEFINE_FUNOPEN_TO_FUNOPEN64_READFN
DEFINE_FUNOPEN_TO_FUNOPEN64_WRITEFN
@@pp_endif@@
DEFINE_FUNOPEN_TO_FUNOPEN64_SEEKFN
@@pp_endif@@
@@pp_endif@@
)]]
[[section(".text.crt{|.dos}.FILE.locked.utility")]]
$FILE *funopen(void const *cookie,
               int (LIBKCALL *readfn)(void *cookie, char *buf, int num_bytes),
               int (LIBKCALL *writefn)(void *cookie, char const *buf, int num_bytes),
               off_t (LIBKCALL *seekfn)(void *cookie, off_t off, int whence),
               int (LIBKCALL *closefn)(void *cookie)) {
@@pp_if __SIZEOF_INT__ == __SIZEOF_SIZE_T__ && $has_function(funopen2)@@
	return funopen2(cookie,
	                (ssize_t (LIBKCALL *)(void *, void *, size_t))readfn,
	                (ssize_t (LIBKCALL *)(void *, void const *, size_t))writefn,
	                seekfn, NULL, closefn);
@@pp_else@@
	FILE *result;
	struct __NAMESPACE_LOCAL_SYM __funopen_holder *holder;
@@pp_if $has_function(funopen64)@@
	if (!seekfn)
		return funopen64(cookie, readfn, writefn, NULL, closefn);
@@pp_endif@@
	holder = (struct __NAMESPACE_LOCAL_SYM __funopen_holder *)malloc(sizeof(struct __NAMESPACE_LOCAL_SYM __funopen_holder));
	if unlikely(!holder)
		return NULL;
	holder->fh_cookie  = (void *)cookie;
	holder->fh_readfn  = readfn;
	holder->fh_writefn = writefn;
	holder->fh_seekfn  = seekfn;
	holder->fh_closefn = closefn;
@@pp_if $has_function(funopen2)@@
	result = funopen2(/* cookie:  */ holder,
	                  /* readfn:  */ readfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn  : NULL,
	                  /* writefn: */ writefn ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL,
	                  /* seekfn:  */ seekfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_seekfn  : NULL,
	                  /* flushfn: */ NULL,
	                  /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
@@pp_elif $has_function(crt_fopencookie)@@
	{
		_IO_cookie_io_functions_t ioc_functions;
		ioc_functions.@read@  = readfn ? (__io_read_fn *)&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn : NULL;
		ioc_functions.@write@ = writefn ? (__io_write_fn *)&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL;
		ioc_functions.@seek@  = seekfn ? &__NAMESPACE_LOCAL_SYM funopen_to_fopencookie_seekfn  : NULL;
		ioc_functions.@close@ = &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn;
		result = crt_fopencookie(holder, readfn && writefn ? "r+" : readfn ? "r" : "w", ioc_functions);
	}
@@pp_else@@
@@pp_if __SIZEOF_INT__ == __SIZEOF_SIZE_T__@@
	result = funopen64(/* cookie:  */ holder,
	                   /* readfn:  */ readfn  ? (int (LIBKCALL *)(void *, char *, int))&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn  : NULL,
	                   /* writefn: */ writefn ? (int (LIBKCALL *)(void *, char const *, int))&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL,
	                   /* seekfn:  */ seekfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen64_seekfn  : NULL,
	                   /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
@@pp_else@@
	result = funopen64(/* cookie:  */ holder,
	                   /* readfn:  */ readfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen64_readfn  : NULL,
	                   /* writefn: */ writefn ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen64_writefn : NULL,
	                   /* seekfn:  */ seekfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen64_seekfn  : NULL,
	                   /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
@@pp_endif@@
@@pp_endif@@
@@pp_if $has_function(free)@@
	if unlikely(!result)
		free(holder);
@@pp_endif@@
	return result;
@@pp_endif@@
}






/************************************************************************/
/* funopen2() --> funopen2_64()                                            */
/************************************************************************/
%[define(DEFINE_FUNOPEN2_HOLDER =
@@pp_ifndef ____funopen2_holder_defined@@
#define ____funopen2_holder_defined
struct __funopen2_holder {
	void              *f2h_cookie;                                                    /* [0..1] funopen2 readfn */
	ssize_t (LIBKCALL *f2h_readfn)(void *cookie, void *buf, size_t num_bytes);        /* [0..1] funopen2 readfn */
	ssize_t (LIBKCALL *f2h_writefn)(void *cookie, void const *buf, size_t num_bytes); /* [0..1] funopen2 writefn */
	off_t   (LIBKCALL *f2h_seekfn)(void *cookie, off_t off, int whence);              /* [0..1] funopen2 seekfn */
	int     (LIBKCALL *f2h_closefn)(void *cookie);                                    /* [0..1] funopen2 closefn */
	int     (LIBKCALL *f2h_flushfn)(void *cookie);                                    /* [0..1] funopen2 flushfn */
};
@@pp_endif@@
)]

/* (#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__) == DEFINE_FUNOPEN_TO_FUNOPEN2_READFN */
%[define(DEFINE_FUNOPEN2_TO_FUNOPEN2_64_READFN =
@@pp_ifndef __funopen2_to_funopen2_64_readfn_defined@@
@@push_namespace(local)@@
#define __funopen2_to_funopen2_64_readfn_defined
__LOCAL_LIBC(funopen2_to_funopen2_64_readfn) ssize_t
(__LIBKCALL funopen2_to_funopen2_64_readfn)(void *cookie, void *buf, size_t num_bytes) {
	struct __funopen2_holder *holder;
	holder = (struct __funopen2_holder *)cookie;
	return (*holder->f2h_readfn)(holder->f2h_cookie, buf, num_bytes);
}
@@pop_namespace@@
@@pp_endif@@
)]

/* (#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__) == DEFINE_FUNOPEN_TO_FUNOPEN2_WRITEFN */
%[define(DEFINE_FUNOPEN2_TO_FUNOPEN2_64_WRITEFN =
@@pp_ifndef __funopen2_to_funopen2_64_writefn_defined@@
@@push_namespace(local)@@
#define __funopen2_to_funopen2_64_writefn_defined
__LOCAL_LIBC(funopen2_to_funopen2_64_writefn) ssize_t
(__LIBKCALL funopen2_to_funopen2_64_writefn)(void *cookie, void const *buf, size_t num_bytes) {
	struct __funopen2_holder *holder;
	holder = (struct __funopen2_holder *)cookie;
	return (*holder->f2h_writefn)(holder->f2h_cookie, buf, num_bytes);
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_FUNOPEN2_TO_FUNOPEN2_64_FLUSHFN =
@@pp_ifndef __funopen2_to_funopen2_64_flushfn_defined@@
@@push_namespace(local)@@
#define __funopen2_to_funopen2_64_flushfn_defined
__LOCAL_LIBC(funopen2_to_funopen2_64_flushfn) int
(__LIBKCALL funopen2_to_funopen2_64_flushfn)(void *cookie) {
	struct __funopen2_holder *holder;
	holder = (struct __funopen2_holder *)cookie;
	return (*holder->f2h_flushfn)(holder->f2h_cookie);
}
@@pop_namespace@@
@@pp_endif@@
)]

/* DEFINE_FUNOPEN2_TO_FUNOPEN2_64_SEEKFN = DEFINE_FUNOPEN_TO_FUNOPEN64_SEEKFN */
/* DEFINE_FUNOPEN2_TO_FUNOPEN2_64_CLOSEFN = DEFINE_FUNOPEN_TO_FUNOPEN2_CLOSEFN */
/************************************************************************/


@@>> funopen2(3), funopen2_64(3)
[[guard, wunused, decl_include("<features.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias("funopen2")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias("funopen2_64")]]
[[userimpl, requires($has_function(malloc) && $has_function(funopen2_64))]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_prefix(DEFINE_FUNOPEN_HOLDER)]]
[[impl_prefix(DEFINE_FUNOPEN2_HOLDER)]]
[[impl_prefix(DEFINE_FUNOPEN_TO_FUNOPEN64_SEEKFN)]] /* DEFINE_FUNOPEN2_TO_FUNOPEN2_64_SEEKFN */
[[impl_prefix(DEFINE_FUNOPEN_TO_FUNOPEN2_CLOSEFN)]] /* DEFINE_FUNOPEN2_TO_FUNOPEN2_64_CLOSEFN */
[[impl_prefix(DEFINE_FUNOPEN2_TO_FUNOPEN2_64_FLUSHFN)]]
[[impl_prefix(
@@pp_if __SIZEOF_INT__ == __SIZEOF_SIZE_T__@@
DEFINE_FUNOPEN_TO_FUNOPEN2_READFN
DEFINE_FUNOPEN_TO_FUNOPEN2_WRITEFN
@@pp_else@@
DEFINE_FUNOPEN2_TO_FUNOPEN2_64_READFN
DEFINE_FUNOPEN2_TO_FUNOPEN2_64_WRITEFN
@@pp_endif@@
)]]
[[section(".text.crt{|.dos}.FILE.locked.utility")]]
$FILE *funopen2(void const *cookie,
                ssize_t (LIBKCALL *readfn)(void *cookie, void *buf, size_t num_bytes),
                ssize_t (LIBKCALL *writefn)(void *cookie, void const *buf, size_t num_bytes),
                off_t (LIBKCALL *seekfn)(void *cookie, off_t off, int whence),
                int (LIBKCALL *flushfn)(void *cookie),
                int (LIBKCALL *closefn)(void *cookie)) {
	FILE *result;
	struct __NAMESPACE_LOCAL_SYM __funopen2_holder *holder;
	if (!seekfn)
		return funopen2_64(cookie, readfn, writefn, NULL, flushfn, closefn);
	holder = (struct __NAMESPACE_LOCAL_SYM __funopen2_holder *)malloc(sizeof(struct __NAMESPACE_LOCAL_SYM __funopen2_holder));
	if unlikely(!holder)
		return NULL;
	holder->f2h_cookie  = (void *)cookie;
	holder->f2h_readfn  = readfn;
	holder->f2h_writefn = writefn;
	holder->f2h_seekfn  = seekfn;
	holder->f2h_flushfn = flushfn;
	holder->f2h_closefn = closefn;
@@pp_if __SIZEOF_INT__ == __SIZEOF_SIZE_T__@@
	result = funopen2_64(/* cookie:  */ holder,
	                     /* readfn:  */ readfn ? (ssize_t (LIBKCALL *)(void *, void *, size_t))&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn : NULL,
	                     /* writefn: */ writefn ? (ssize_t (LIBKCALL *)(void *, void const *, size_t))&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL,
	                     /* seekfn:  */ seekfn ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen64_seekfn : NULL,
	                     /* flushfn: */ flushfn ? &__NAMESPACE_LOCAL_SYM funopen2_to_funopen2_64_flushfn : NULL,
	                     /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
@@pp_else@@
	result = funopen2_64(/* cookie:  */ holder,
	                     /* readfn:  */ readfn ? &__NAMESPACE_LOCAL_SYM funopen2_to_funopen2_64_readfn : NULL,
	                     /* writefn: */ writefn ? &__NAMESPACE_LOCAL_SYM funopen2_to_funopen2_64_writefn : NULL,
	                     /* seekfn:  */ seekfn ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen64_seekfn : NULL,
	                     /* flushfn: */ flushfn ? &__NAMESPACE_LOCAL_SYM funopen2_to_funopen2_64_flushfn : NULL,
	                     /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
@@pp_endif@@
@@pp_if $has_function(free)@@
	if unlikely(!result)
		free(holder);
@@pp_endif@@
	return result;
}



%#ifdef __USE_LARGEFILE64
%{
#ifndef __off64_t_defined
#define __off64_t_defined
typedef __off64_t off64_t;
#endif /* !__off64_t_defined */
}


%[define(DEFINE_FUNOPEN64_HOLDER =
@@pp_ifndef ____funopen64_holder_defined@@
@@push_namespace(local)@@
#define ____funopen64_holder_defined
struct __funopen64_holder {
	void              *fh64_cookie;                                                 /* [0..1] funopen cookie */
	int     (LIBKCALL *fh64_readfn)(void *cookie, char *buf, int num_bytes);        /* [0..1] funopen readfn */
	int     (LIBKCALL *fh64_writefn)(void *cookie, char const *buf, int num_bytes); /* [0..1] funopen writefn */
	off64_t (LIBKCALL *fh64_seekfn)(void *cookie, off64_t off, int whence);         /* [0..1] funopen seekfn */
	int     (LIBKCALL *fh64_closefn)(void *cookie);                                 /* [0..1] funopen closefn */
};
@@pop_namespace@@
@@pp_endif@@
)]


%[define(DEFINE_FUNOPEN64_TO_FUNOPEN2_64_SEEKFN =
@@pp_ifndef __funopen64_to_funopen2_64_seekfn_defined@@
@@push_namespace(local)@@
#define __funopen64_to_funopen2_64_seekfn_defined
__LOCAL_LIBC(funopen64_to_funopen2_64_seekfn) off64_t
(__LIBKCALL funopen64_to_funopen2_64_seekfn)(void *cookie, off64_t off, int whence) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (*holder->fh_seekfn)(holder->fh_cookie, off, whence);
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_FUNOPEN64_TO_FOPENCOOKIE_SEEKFN =
@@pp_ifndef __funopen64_to_fopencookie_seekfn_defined@@
@@push_namespace(local)@@
#define __funopen64_to_fopencookie_seekfn_defined
@@pp_ifdef __USE_KOS_ALTERATIONS@@
__LOCAL_LIBC(funopen64_to_fopencookie_seekfn) int
(__LIBKCALL funopen64_to_fopencookie_seekfn)(void *cookie, pos64_t *pos, int whence)
@@pp_else@@
__LOCAL_LIBC(funopen64_to_fopencookie_seekfn) int
(__LIBKCALL funopen64_to_fopencookie_seekfn)(void *cookie, off64_t *pos, int whence)
@@pp_endif@@
{
	off64_t newpos;
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	newpos = (*holder->fh_seekfn)(holder->fh_cookie, (off64_t)*pos, whence);
	if unlikely(newpos == -1)
		return -1;
@@pp_ifdef __USE_KOS_ALTERATIONS@@
	*pos = (pos64_t)newpos;
@@pp_else@@
	*pos = newpos;
@@pp_endif@@
	return 0;
}
@@pop_namespace@@
@@pp_endif@@
)]

/* DEFINE_FUNOPEN_TO_FOPEN64_CLOSEFN = DEFINE_FUNOPEN_TO_FUNOPEN2_CLOSEFN */
%[define(DEFINE_FUNOPEN64_TO_FUNOPEN_SEEKFN =
@@pp_ifndef __funopen64_to_funopen_seekfn_defined@@
@@push_namespace(local)@@
#define __funopen64_to_funopen_seekfn_defined
__LOCAL_LIBC(funopen64_to_funopen_seekfn) off_t
(__LIBKCALL funopen64_to_funopen_seekfn)(void *cookie, off_t off, int whence) {
	struct __funopen_holder *holder;
	holder = (struct __funopen_holder *)cookie;
	return (off_t)(*holder->fh_seekfn)(holder->fh_cookie, (off64_t)off, whence);
}
@@pop_namespace@@
@@pp_endif@@
)]



[[wunused, doc_alias("funopen")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), crt_intern_kos_alias("libc_funopen")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), preferred_alias("funopen")]]
[[requires((__SIZEOF_INT__ == __SIZEOF_SIZE_T__ && $has_function(funopen2_64)) ||
           ($has_function(malloc) && ($has_function(funopen2_64) ||
                                      $has_function(crt_fopencookie) ||
                                      $has_function(crt_funopen32))))]]
[[impl_prefix(
@@pp_if __SIZEOF_INT__ != __SIZEOF_SIZE_T__ || !$has_function(funopen2_64)@@
DEFINE_FUNOPEN_HOLDER
DEFINE_FUNOPEN64_HOLDER
DEFINE_FUNOPEN_TO_FUNOPEN2_CLOSEFN
@@pp_if $has_function(funopen2_64)@@
DEFINE_FUNOPEN_TO_FUNOPEN2_READFN
DEFINE_FUNOPEN_TO_FUNOPEN2_WRITEFN
@@pp_if __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__@@
DEFINE_FUNOPEN_TO_FUNOPEN2_SEEKFN
@@pp_else@@
DEFINE_FUNOPEN64_TO_FUNOPEN2_64_SEEKFN
@@pp_endif@@
@@pp_elif $has_function(crt_fopencookie)@@
DEFINE_FUNOPEN_TO_FUNOPEN2_READFN
DEFINE_FUNOPEN_TO_FUNOPEN2_WRITEFN
@@pp_if __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__@@
DEFINE_FUNOPEN_TO_FOPENCOOKIE_SEEKFN
@@pp_else@@
DEFINE_FUNOPEN64_TO_FOPENCOOKIE_SEEKFN
@@pp_endif@@
#include <libio.h>
@@pp_else@@
@@pp_if __SIZEOF_INT__ == __SIZEOF_SIZE_T__@@
DEFINE_FUNOPEN_TO_FUNOPEN2_READFN
DEFINE_FUNOPEN_TO_FUNOPEN2_WRITEFN
@@pp_else@@
DEFINE_FUNOPEN_TO_FUNOPEN64_READFN
DEFINE_FUNOPEN_TO_FUNOPEN64_WRITEFN
@@pp_endif@@
@@pp_if __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__@@
DEFINE_FUNOPEN_TO_FUNOPEN64_SEEKFN
@@pp_else@@
DEFINE_FUNOPEN64_TO_FUNOPEN_SEEKFN
@@pp_endif@@
@@pp_endif@@
@@pp_endif@@
)]]
[[section(".text.crt{|.dos}.FILE.locked.utility")]]
$FILE *funopen64(void const *cookie,
                 [[nullable]] int (LIBKCALL *readfn)(void *cookie, char *buf, int num_bytes),
                 [[nullable]] int (LIBKCALL *writefn)(void *cookie, char const *buf, int num_bytes),
                 [[nullable]] off64_t (LIBKCALL *seekfn)(void *cookie, off64_t off, int whence),
                 [[nullable]] int (LIBKCALL *closefn)(void *cookie)) {
@@pp_if __SIZEOF_INT__ == __SIZEOF_SIZE_T__ && $has_function(funopen2_64)@@
	return funopen2_64(cookie,
	                   (ssize_t (LIBKCALL *)(void *, void *, size_t))readfn,
	                   (ssize_t (LIBKCALL *)(void *, void const *, size_t))writefn,
	                   seekfn, NULL, closefn);
@@pp_else@@
	FILE *result;
	struct __NAMESPACE_LOCAL_SYM __funopen64_holder *holder;
@@pp_ifndef      __BUILDING_LIBC@@
@@pp_if $has_function(crt_funopen32)@@
	if (!seekfn)
		return crt_funopen32(cookie, readfn, writefn, NULL, closefn);
@@pp_endif@@
@@pp_endif@@
	holder = (struct __NAMESPACE_LOCAL_SYM __funopen64_holder *)malloc(sizeof(struct __NAMESPACE_LOCAL_SYM __funopen64_holder));
	if unlikely(!holder)
		return NULL;
	holder->fh64_cookie  = (void *)cookie;
	holder->fh64_readfn  = readfn;
	holder->fh64_writefn = writefn;
	holder->fh64_seekfn  = seekfn;
	holder->fh64_closefn = closefn;
@@pp_if $has_function(funopen2_64)@@
@@pp_if __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__@@
	result = funopen2_64(/* cookie:  */ holder,
	                     /* readfn:  */ readfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn  : NULL,
	                     /* writefn: */ writefn ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL,
	                     /* seekfn:  */ seekfn  ? (off64_t (LIBKCALL *)(void *, off64_t, int))&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_seekfn  : NULL,
	                     /* flushfn: */ NULL,
	                     /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
@@pp_else@@
	result = funopen2_64(/* cookie:  */ holder,
	                     /* readfn:  */ readfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn  : NULL,
	                     /* writefn: */ writefn ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL,
	                     /* seekfn:  */ seekfn  ? &__NAMESPACE_LOCAL_SYM funopen64_to_funopen2_64_seekfn  : NULL,
	                     /* flushfn: */ NULL,
	                     /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
@@pp_endif@@
@@pp_elif $has_function(crt_fopencookie)@@
	{
		_IO_cookie_io_functions_t ioc_functions;
		ioc_functions.@read@  = readfn ? (__io_read_fn *)&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn : NULL;
		ioc_functions.@write@ = writefn ? (__io_write_fn *)&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL;
@@pp_if __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__@@
		ioc_functions.@seek@  = seekfn ? &__NAMESPACE_LOCAL_SYM funopen_to_fopencookie_seekfn : NULL;
@@pp_else@@
		ioc_functions.@seek@  = seekfn ? &__NAMESPACE_LOCAL_SYM funopen64_to_fopencookie_seekfn : NULL;
@@pp_endif@@
		ioc_functions.@close@ = &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn;
		result = crt_fopencookie(holder, readfn && writefn ? "r+" : readfn ? "r" : "w", ioc_functions);
	}
@@pp_else@@
@@pp_if   __SIZEOF_INT__   ==  __SIZEOF_SIZE_T__@@
@@pp_if __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__@@
	result = crt_funopen32(/* cookie:  */ holder,
	                       /* readfn:  */ readfn  ? (int (LIBKCALL *)(void *, char *, int))&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn  : NULL,
	                       /* writefn: */ writefn ? (int (LIBKCALL *)(void *, char const *, int))&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL,
	                       /* seekfn:  */ seekfn  ? (off_t (LIBKCALL *)(void *, off_t, int))&__NAMESPACE_LOCAL_SYM funopen_to_funopen64_seekfn  : NULL,
	                       /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
@@pp_else@@
	result = crt_funopen32(/* cookie:  */ holder,
	                       /* readfn:  */ readfn  ? (int (LIBKCALL *)(void *, char *, int))&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn  : NULL,
	                       /* writefn: */ writefn ? (int (LIBKCALL *)(void *, char const *, int))&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL,
	                       /* seekfn:  */ seekfn  ? &__NAMESPACE_LOCAL_SYM funopen64_to_funopen_seekfn  : NULL,
	                       /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
@@pp_endif@@
@@pp_else@@
@@pp_if __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__@@
	result = crt_funopen32(/* cookie:  */ holder,
	                       /* readfn:  */ readfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen64_readfn  : NULL,
	                       /* writefn: */ writefn ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen64_writefn : NULL,
	                       /* seekfn:  */ seekfn  ? (off_t (LIBKCALL *)(void *, off_t, int))&__NAMESPACE_LOCAL_SYM funopen_to_funopen64_seekfn  : NULL,
	                       /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
@@pp_else@@
	result = crt_funopen32(/* cookie:  */ holder,
	                       /* readfn:  */ readfn  ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen64_readfn  : NULL,
	                       /* writefn: */ writefn ? &__NAMESPACE_LOCAL_SYM funopen_to_funopen64_writefn : NULL,
	                       /* seekfn:  */ seekfn  ? &__NAMESPACE_LOCAL_SYM funopen64_to_funopen_seekfn  : NULL,
	                       /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
@@pp_endif@@
@@pp_endif@@
@@pp_endif@@
@@pp_if $has_function(free)@@
	if unlikely(!result)
		free(holder);
@@pp_endif@@
	return result;
@@pp_endif@@
}








/************************************************************************/
/* funopen2_64() --> funopen2()                                         */
/************************************************************************/
%[define(DEFINE_FUNOPEN2_64_HOLDER =
@@pp_ifndef ____funopen2_64_holder_defined@@
#define ____funopen2_64_holder_defined
struct __funopen2_64_holder {
	void              *f2h64_cookie;                                                    /* [0..1] funopen2 readfn */
	ssize_t (LIBKCALL *f2h64_readfn)(void *cookie, void *buf, size_t num_bytes);        /* [0..1] funopen2 readfn */
	ssize_t (LIBKCALL *f2h64_writefn)(void *cookie, void const *buf, size_t num_bytes); /* [0..1] funopen2 writefn */
	off64_t (LIBKCALL *f2h64_seekfn)(void *cookie, off64_t off, int whence);            /* [0..1] funopen2 seekfn */
	int     (LIBKCALL *f2h64_closefn)(void *cookie);                                    /* [0..1] funopen2 closefn */
	int     (LIBKCALL *f2h64_flushfn)(void *cookie);                                    /* [0..1] funopen2 flushfn */
};
@@pp_endif@@
)]

/* (#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__) == DEFINE_FUNOPEN_TO_FUNOPEN2_READFN */
/* DEFINE_FUNOPEN2_64_TO_FUNOPEN2_READFN == DEFINE_FUNOPEN2_TO_FUNOPEN2_64_READFN */

/* (#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__) == DEFINE_FUNOPEN_TO_FUNOPEN2_WRITEFN */
/* DEFINE_FUNOPEN2_64_TO_FUNOPEN2_WRITEFN == DEFINE_FUNOPEN2_TO_FUNOPEN2_64_WRITEFN */
/* DEFINE_FUNOPEN2_64_TO_FUNOPEN2_FLUSHFN == DEFINE_FUNOPEN2_TO_FUNOPEN2_64_FLUSHFN */
%[define(DEFINE_FUNOPEN2_64_TO_FUNOPEN2_SEEKFN =
@@pp_ifndef __funopen2_64_to_funopen2_seekfn_defined@@
@@push_namespace(local)@@
#define __funopen2_64_to_funopen2_seekfn_defined
__LOCAL_LIBC(funopen2_64_to_funopen2_seekfn) __off32_t
(__LIBKCALL funopen2_64_to_funopen2_seekfn)(void *cookie, __off32_t off, int whence) {
	struct __funopen2_64_holder *holder;
	holder = (struct __funopen2_64_holder *)cookie;
	return (__off32_t)(*holder->f2h64_seekfn)(holder->f2h64_cookie, off, whence);
}
@@pop_namespace@@
@@pp_endif@@
)]
/* DEFINE_FUNOPEN2_64_TO_FUNOPEN2_CLOSEFN = DEFINE_FUNOPEN_TO_FUNOPEN2_CLOSEFN */
/************************************************************************/

[[wunused, doc_alias("funopen2"), decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), crt_intern_kos_alias("libc_funopen2")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), preferred_alias("funopen2")]]
[[userimpl, requires_function(malloc, crt_funopen2_32)]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_prefix(DEFINE_FUNOPEN_HOLDER)]]
[[impl_prefix(DEFINE_FUNOPEN2_HOLDER)]]
[[impl_prefix(DEFINE_FUNOPEN2_64_HOLDER)]]
[[impl_prefix(DEFINE_FUNOPEN2_64_TO_FUNOPEN2_SEEKFN)]]
[[impl_prefix(DEFINE_FUNOPEN2_TO_FUNOPEN2_64_FLUSHFN)]] /* DEFINE_FUNOPEN2_64_TO_FUNOPEN2_FLUSHFN */
[[impl_prefix(DEFINE_FUNOPEN_TO_FUNOPEN2_CLOSEFN)]]     /* DEFINE_FUNOPEN2_64_TO_FUNOPEN2_CLOSEFN */
[[impl_prefix(
@@pp_if __SIZEOF_INT__ == __SIZEOF_SIZE_T__@@
DEFINE_FUNOPEN_TO_FUNOPEN2_READFN
DEFINE_FUNOPEN_TO_FUNOPEN2_WRITEFN
@@pp_else@@
DEFINE_FUNOPEN2_TO_FUNOPEN2_64_READFN
DEFINE_FUNOPEN2_TO_FUNOPEN2_64_WRITEFN
@@pp_endif@@
)]]
[[section(".text.crt{|.dos}.FILE.locked.utility")]]
$FILE *funopen2_64(void const *cookie,
                   ssize_t (LIBKCALL *readfn)(void *cookie, void *buf, size_t num_bytes),
                   ssize_t (LIBKCALL *writefn)(void *cookie, void const *buf, size_t num_bytes),
                   off64_t (LIBKCALL *seekfn)(void *cookie, off64_t off, int whence),
                   int (LIBKCALL *flushfn)(void *cookie),
                   int (LIBKCALL *closefn)(void *cookie)) {
	FILE *result;
	struct __NAMESPACE_LOCAL_SYM __funopen2_64_holder *holder;
	if (!seekfn)
		return crt_funopen2_32(cookie, readfn, writefn, NULL, flushfn, closefn);
	holder = (struct __NAMESPACE_LOCAL_SYM __funopen2_64_holder *)malloc(sizeof(struct __NAMESPACE_LOCAL_SYM __funopen2_64_holder));
	if unlikely(!holder)
		return NULL;
	holder->f2h64_cookie  = cookie;
	holder->f2h64_readfn  = readfn;
	holder->f2h64_writefn = writefn;
	holder->f2h64_seekfn  = seekfn;
	holder->f2h64_closefn = closefn;
	holder->f2h64_flushfn = flushfn;
@@pp_if __SIZEOF_INT__ == __SIZEOF_SIZE_T__@@
	result = crt_funopen2_32(/* cookie:  */ holder,
	                         /* readfn:  */ readfn  ? (ssize_t (LIBKCALL *)(void *, void *, size_t))&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_readfn  : NULL,
	                         /* writefn: */ writefn ? (ssize_t (LIBKCALL *)(void *, void const *, size_t))&__NAMESPACE_LOCAL_SYM funopen_to_funopen2_writefn : NULL,
	                         /* seekfn:  */ seekfn  ? &__NAMESPACE_LOCAL_SYM funopen2_64_to_funopen2_seekfn  : NULL,
	                         /* flushfn: */ flushfn ? &__NAMESPACE_LOCAL_SYM funopen2_to_funopen2_64_flushfn : NULL,
	                         /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
@@pp_else@@
	result = crt_funopen2_32(/* cookie:  */ holder,
	                         /* readfn:  */ readfn  ? &__NAMESPACE_LOCAL_SYM funopen2_to_funopen2_64_readfn  : NULL,
	                         /* writefn: */ writefn ? &__NAMESPACE_LOCAL_SYM funopen2_to_funopen2_64_writefn : NULL,
	                         /* seekfn:  */ seekfn  ? &__NAMESPACE_LOCAL_SYM funopen2_64_to_funopen2_seekfn  : NULL,
	                         /* flushfn: */ flushfn ? &__NAMESPACE_LOCAL_SYM funopen2_to_funopen2_64_flushfn : NULL,
	                         /* closefn: */ &__NAMESPACE_LOCAL_SYM funopen_to_funopen2_closefn);
@@pp_endif@@
@@pp_if $has_function(free)@@
	if unlikely(!result)
		free(holder);
@@pp_endif@@
	return result;
}

%#endif /* __USE_LARGEFILE64 */


%{
#ifdef __USE_BSD
#ifdef __funopen_defined
#define fropen(cookie, fn) funopen(cookie, fn, __NULLPTR, __NULLPTR, __NULLPTR)
#define fwopen(cookie, fn) funopen(cookie, __NULLPTR, fn, __NULLPTR, __NULLPTR)
#endif /* __funopen_defined */
#ifdef __funopen2_defined
#define fropen2(cookie, fn) funopen2(cookie, fn, __NULLPTR, __NULLPTR, __NULLPTR, __NULLPTR)
#define fwopen2(cookie, fn) funopen2(cookie, __NULLPTR, fn, __NULLPTR, __NULLPTR, __NULLPTR)
#endif /* __funopen2_defined */
#endif /* __USE_BSD */
}
%#endif /* __USE_BSD || __USE_KOS */
/************************************************************************/
/************************************************************************/


%
%#endif /* __CC__ */


%
%
%
%
%
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
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */

#ifndef __rsize_t_defined
#define __rsize_t_defined
typedef __SIZE_TYPE__ rsize_t;
#endif /* !__rsize_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __std_FILE_defined
#define __std_FILE_defined
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */
#ifndef __FILE_defined
#define __FILE_defined
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */

}

%
%#ifndef _CRT_DIRECTORY_DEFINED
%#define _CRT_DIRECTORY_DEFINED 1
%[insert:guarded_function(unlink = unlink)]
%[insert:guarded_function(_unlink = unlink)]
%#endif /* !_CRT_DIRECTORY_DEFINED */


%
%#ifndef _STDIO_DEFINED
%#define _STDIO_DEFINED 1

%[insert:function(_popen = popen)]
%[insert:function(_pclose = pclose)]

[[cp, wunused, decl_include("<features.h>")]]
[[crt_dos_variant, requires_function(fopen)]]
[[section(".text.crt.dos.FILE.locked.access")]]
$FILE *_fsopen([[nonnull]] char const *filename,
               [[nonnull]] char const *modes,
               __STDC_INT_AS_UINT_T sflag) {
	(void)sflag;
	return fopen(filename, modes);
}

%[insert:function(_fdopen = fdopen)]

[[cp_stdio, userimpl, no_crt_self_import, no_crt_self_export, export_as(CNL_flushall...)]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), alias(CNL_flushall_unlocked...)]]
[[                                                                           alias(CNL_flushall...)]]
[[                                                                           alias(CNL_flushall_unlocked...)]]
[[section(".text.crt{|.dos}.application.exit")]]
int _flushall() {
	return fflush(NULL);
}

%[insert:function(_fcloseall = fcloseall)]
%[insert:function(_fileno = fileno)]
%[insert:function(_fgetchar = getchar)]
%[insert:function(_fputchar = putchar)]
%[insert:function(_getw = getw)]
%[insert:function(_putw = putw)]
%[insert:function(_tempnam = tempnam)]

%
%[insert:function(_fseeki64 = fseeko64)]
%[insert:function(_ftelli64 = ftello64)]

%
%[default:section(".text.crt.dos.FILE.utility")];

[[cp]] int _rmtmp();

%
[[cp_stdio]]
[[export_alias("__uflow", "__underflow")]]
[[section(".text.crt.dos.FILE.locked.read.read")]]
int _filbuf([[nonnull]] $FILE *__restrict stream);

[[cp_stdio]]
[[export_alias("__swbuf")]] /* __swbuf() is the cygwin name for this function */
[[section(".text.crt.dos.FILE.locked.write.write")]]
int _flsbuf(int ch, [[nonnull]] $FILE *__restrict stream);

%
%[default:section(".text.crt.dos.FILE.utility")];

[[wunused]]
[[requires_include("<asm/os/resource.h>")]]
[[requires(defined(__RLIMIT_NOFILE) && $has_function(getrlimit))]]
[[impl_include("<asm/os/resource.h>")]]
[[impl_include("<bits/os/rlimit.h>")]]
int _getmaxstdio() {
	struct rlimit rlim;
	if unlikely(getrlimit((__rlimit_resource_t)__RLIMIT_NOFILE, &rlim) != 0)
		rlim.@rlim_cur@ = (__FS_TYPE(@rlim@))-1;
	return (int)rlim.@rlim_cur@;
}


[[requires_include("<asm/os/resource.h>")]]
[[requires(defined(__RLIMIT_NOFILE) && $has_function(getrlimit, setrlimit))]]
[[impl_include("<asm/os/resource.h>")]]
[[impl_include("<bits/os/rlimit.h>")]]
int _setmaxstdio(int newmaxval) {
	struct rlimit rlim;
	if unlikely(getrlimit((__rlimit_resource_t)__RLIMIT_NOFILE, &rlim) != 0)
		goto err;
	rlim.@rlim_cur@ = (__FS_TYPE(@rlim@))newmaxval;
	if unlikely(setrlimit((__rlimit_resource_t)__RLIMIT_NOFILE, &rlim) != 0) {
err:
		rlim.@rlim_cur@ = (__FS_TYPE(@rlim@))-1;
	}
	return (int)rlim.@rlim_cur@;
}

@@>> _get_printf_count_output(3), _set_printf_count_output(3)
@@Enable or disable use of '%n' in printf-style format strings.
[[pure, wunused]]
int _get_printf_count_output(void);

[[doc_alias("_get_printf_count_output")]]
int _set_printf_count_output(int val);

[[wunused]]
$uint32_t _get_output_format();
$uint32_t _set_output_format($uint32_t format);


%
%#ifdef __USE_DOS_SLIB
[[cp, decl_include("<bits/types.h>")]]
[[crt_dos_variant, requires_function(fopen64)]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt.dos.FILE.locked.access")]]
errno_t fopen_s([[nonnull]] $FILE **pstream,
                [[nonnull]] char const *filename,
                [[nonnull]] char const *modes) {
	FILE *result;
	if unlikely(!pstream || !filename || !modes) {
@@pp_ifdef EINVAL@@
		return EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	result = fopen64(filename, modes);
	if unlikely(!result) {
@@pp_ifdef ENOMEM@@
		return __libc_geterrno_or(ENOMEM);
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	*pstream = result;
	return EOK;
}

[[cp, decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[crt_dos_variant, requires_function(freopen)]]
[[section(".text.crt.dos.FILE.locked.access")]]
errno_t freopen_s([[nonnull]] $FILE **pstream,
                  [[nonnull]] char const *filename,
                  [[nonnull]] char const *modes,
                  [[nonnull]] $FILE *oldstream) {
	if unlikely(!pstream || !filename || !modes || !oldstream) {
@@pp_ifdef EINVAL@@
		return EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	oldstream = freopen(filename, modes, oldstream);
	if unlikely(!oldstream) {
@@pp_ifdef __libc_geterrno@@
		return __libc_geterrno();
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	*pstream = oldstream;
	return EOK;
}

[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(tmpnam)]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt.dos.fs.utility")]]
errno_t tmpnam_s([[outp(bufsize)]] char *__restrict buf,
                 rsize_t bufsize) {
	if unlikely(!buf) {
@@pp_ifdef EINVAL@@
		return EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	if unlikely(bufsize < L_tmpnam) {
@@pp_ifdef ERANGE@@
		return ERANGE; /* XXX: Is this what dos does? */
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	if unlikely(!tmpnam(buf))
		return __libc_geterrno_or(1);
	return EOK;
}

%
[[decl_include("<bits/types.h>")]]
[[requires_function(clearerr)]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt.dos.FILE.locked.utility")]]
errno_t clearerr_s([[nonnull]] $FILE *__restrict stream) {
	if (!stream) {
@@pp_ifdef EINVAL@@
		return EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	clearerr(stream);
	return 0;
}

[[cp, decl_include("<bits/types.h>")]]
[[requires_function(tmpfile64)]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt.dos.FILE.locked.access")]]
errno_t tmpfile_s([[nonnull]] $FILE **pstream) {
	if (!pstream) {
@@pp_ifdef EINVAL@@
		return EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	*pstream = tmpfile64();
	if (!*pstream) {
@@pp_ifdef ENOMEM@@
		return __libc_geterrno_or(ENOMEM);
@@pp_else@@
		return __libc_geterrno_or(1);
@@pp_endif@@
	}
	return 0;
}

[[cp, wunused, decl_include("<hybrid/typecore.h>")]]
[[requires_function(fread)]]
[[impl_include("<libc/errno.h>", "<hybrid/__overflow.h>")]]
[[section(".text.crt.dos.FILE.locked.read.read")]]
$size_t fread_s([[outp(min(return * elemsize, elemcount * elemsize, bufsize))]] void *__restrict buf,
                $size_t bufsize, $size_t elemsize, $size_t elemcount,
                [[nonnull]] $FILE *__restrict stream) {
	size_t reqbuf;
	if (__hybrid_overflow_umul(elemsize, elemcount, &reqbuf) ||
	    reqbuf > bufsize) {
@@pp_ifdef ERANGE@@
		(void)libc_seterrno(ERANGE);
@@pp_endif@@
		return 0;
	}
	if unlikely(!stream || !buf) {
@@pp_ifdef EINVAL@@
		(void)libc_seterrno(EINVAL);
@@pp_endif@@
		return 0;
	}
	return fread(buf, elemsize, elemcount, stream);
}

[[cp, wunused, decl_include("<hybrid/typecore.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdin) && $has_function(fgets))]]
[[impl_include("<libc/template/stdstreams.h>", "<libc/errno.h>")]]
[[section(".text.crt.dos.FILE.locked.read.read")]]
char *gets_s([[outp(min(strlen(return), bufsize))]] char *__restrict buf, rsize_t bufsize) {
	if unlikely(!buf) {
@@pp_ifdef EINVAL@@
		(void)libc_seterrno(EINVAL);
@@pp_endif@@
		return NULL;
	}
	return fgets(buf, (__STDC_INT_AS_SIZE_T)(unsigned int)bufsize, stdin);
}

%#endif /* __USE_DOS_SLIB */
%#endif /* _STDIO_DEFINED */

/*[nocrt]*/ %[insert:function(_fgetc_nolock = fgetc_unlocked)]
/*[nocrt]*/ %[insert:function(_fputc_nolock = fputc_unlocked)]
/*[nocrt]*/ %[insert:function(_getc_nolock = fgetc_unlocked)]
/*[nocrt]*/ %[insert:function(_putc_nolock = fputc_unlocked)]
/*[nocrt]*/ %[insert:function(_getchar_nolock = getchar_unlocked)]
/*[nocrt]*/ %[insert:function(_putchar_nolock = putchar_unlocked)]

%[insert:function(_lock_file = flockfile)]
%[insert:function(_unlock_file = funlockfile)]
%[insert:function(_fclose_nolock = fclose)]
%[insert:function(_fflush_nolock = fflush_unlocked)]
%[insert:function(_fread_nolock = fread_unlocked)]
%[insert:function(_fwrite_nolock = fwrite_unlocked)]


[[cp_stdio, wunused, decl_include("<hybrid/typecore.h>")]]
[[requires_function(fread_unlocked)]]
[[section(".text.crt.dos.FILE.unlocked.read.read")]]
$size_t _fread_nolock_s([[outp(min(return * elemsize, elemcount * elemsize, bufsize))]] void *__restrict buf,
                        $size_t bufsize, $size_t elemsize, $size_t elemcount, [[nonnull]] $FILE *__restrict stream) {
	bufsize = elemsize ? bufsize / elemsize : 0;
	return fread_unlocked(buf, elemsize,
	                      bufsize < elemcount
	                      ? bufsize
	                      : elemcount,
	                      stream);
}

%[insert:function(_fseek_nolock = fseek_unlocked)]
%[insert:function(_ftell_nolock = ftell_unlocked)]
%[insert:function(_fseeki64_nolock = fseeko64_unlocked)]
%[insert:function(_ftelli64_nolock = ftello64_unlocked)]
%[insert:function(_ungetc_nolock = ungetc_unlocked)]

/*[nocrt]*/ %[insert:function(fgetchar = getchar)]
/*[nocrt]*/ %[insert:function(fputchar = putchar)]
/*[nocrt]*/ %[insert:function(flushall = _flushall)]
/*[nocrt]*/ %[insert:function(rmtmp = _rmtmp)]

%{
#define SYS_OPEN     _SYS_OPEN

}

%[define(_CRT_INTERNAL_PRINTF_LEGACY_VSPRINTF_NULL_TERMINATION = 1)]
%[define(_CRT_INTERNAL_PRINTF_STANDARD_SNPRINTF_BEHAVIOR       = 2)]
%[define(_CRT_INTERNAL_PRINTF_LEGACY_WIDE_SPECIFIERS           = 4)]
%[define(_CRT_INTERNAL_PRINTF_LEGACY_MSVCRT_COMPATIBILITY      = 8)]
%[define(_CRT_INTERNAL_PRINTF_LEGACY_THREE_DIGIT_EXPONENTS     = 16)]
%[define(_CRT_INTERNAL_SCANF_SECURECRT                         = 1)]
%[define(_CRT_INTERNAL_SCANF_LEGACY_WIDE_SPECIFIERS            = 2)]
%[define(_CRT_INTERNAL_SCANF_LEGACY_MSVCRT_COMPATIBILITY       = 4)]

%[default:section(".text.crt.dos.unicode.locale.format.printf")];
[[decl_include("<hybrid/typecore.h>"), requires_function(vfprintf)]]
__STDC_INT_AS_SSIZE_T __stdio_common_vfprintf($uint64_t options, [[nonnull]] $FILE *stream,
                                              [[nonnull, format]] char const *format,
                                              $locale_t locale, $va_list args) {
	(void)locale;
	(void)options;
	return vfprintf(stream, format, args);
}

[[decl_include("<hybrid/typecore.h>"), crt_intern_alias(__stdio_common_vfprintf), requires_function(__stdio_common_vfprintf)]]
__STDC_INT_AS_SSIZE_T __stdio_common_vfprintf_s($uint64_t options, [[nonnull]] $FILE *stream,
                                                [[nonnull, format]] char const *format,
                                                $locale_t locale, $va_list args) {
	return __stdio_common_vfprintf(options, stream, format, locale, args);
}

[[decl_include("<hybrid/typecore.h>"), requires_function(vfprintf)]]
[[crt_intern_alias("__stdio_common_vfprintf")]] /* Normal printf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T __stdio_common_vfprintf_p($uint64_t options, [[nonnull]] $FILE *stream,
                                                [[nonnull, format]] char const *format,
                                                $locale_t locale, $va_list args) {
	/* NOTE: DOS positional arguments work the same as gLibc's, only that
	 *       glibc and KOS  already bake them  into the normal  `printf'. */
	(void)locale;
	(void)options;
	return vfprintf(stream, format, args);
}

[[decl_include("<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T __stdio_common_vsprintf($uint64_t options, char *buf, $size_t bufsize,
                                              [[nonnull, format]] char const *format,
                                              $locale_t locale, $va_list args) {
	__STDC_INT_AS_SSIZE_T result;
	(void)locale;
	result = vsnprintf(buf, bufsize, format, args);
	if (!(options & _CRT_INTERNAL_PRINTF_STANDARD_SNPRINTF_BEHAVIOR) && (size_t)result > bufsize)
		result = bufsize;
	return result;
}

[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/__assert.h>")]]
__STDC_INT_AS_SSIZE_T __stdio_common_vsprintf_s($uint64_t options, char *buf, $size_t bufsize,
                                                [[nonnull, format]] char const *format,
                                                $locale_t locale, $va_list args) {
	__STDC_INT_AS_SSIZE_T result;
	(void)options;
	(void)locale;
	result = vsnprintf(buf, bufsize, format, args);
	__hybrid_assert(((size_t)result + 1) <= bufsize);
	return result;
}

[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/__assert.h>")]]
__STDC_INT_AS_SSIZE_T __stdio_common_vsnprintf_s($uint64_t options, char *buf, $size_t bufsize,
                                                 $size_t maxsize, [[nonnull, format]] char const *format,
                                                 $locale_t locale, $va_list args) {
	__hybrid_assert(bufsize <= maxsize);
	return __stdio_common_vsprintf(options, buf, bufsize, format, locale, args);
}

[[decl_include("<hybrid/typecore.h>")]]
[[crt_intern_alias("__stdio_common_vsprintf")]] /* Normal printf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T __stdio_common_vsprintf_p($uint64_t options, char *buf, $size_t bufsize,
                                                [[nonnull, format]] char const *format,
                                                $locale_t locale, $va_list args) {
	__STDC_INT_AS_SSIZE_T result;
	(void)locale;
	/* NOTE: DOS positional arguments work the same as gLibc's, only that
	 *       glibc and KOS  already bake them  into the normal  `printf'. */
	result = vsnprintf(buf, bufsize, format, args);
	if (!(options & _CRT_INTERNAL_PRINTF_STANDARD_SNPRINTF_BEHAVIOR) && (size_t)result > bufsize)
		result = bufsize;
	return result;
}

%[default:section(".text.crt.dos.FILE.locked.read.scanf")];
[[decl_include("<hybrid/typecore.h>"), wunused, requires_function(vfscanf)]]
__STDC_INT_AS_SSIZE_T __stdio_common_vfscanf($uint64_t options, [[nonnull]] $FILE *stream,
                                             [[nonnull, format]] char const *format,
                                             $locale_t locale, $va_list args) {
	(void)options;
	(void)locale;
	return vfscanf(stream, format, args);
}

[[decl_include("<hybrid/typecore.h>"), wunused]]
[[dependency(unicode_readutf8_n, unicode_readutf8_rev)]]
[[impl_include("<asm/crt/stdio.h>")]]
[[impl_prefix(
@@push_namespace(local)@@
struct __vsnscanf_data {
	unsigned char const *__ptr;
	unsigned char const *__end;
};
__LOCAL_LIBC(@vsnscanf_getc@) __format_word_t
(__FORMATPRINTER_CC vsnscanf_getc)(void *arg) {
	struct __vsnscanf_data *cookie;
	cookie = (struct __vsnscanf_data *)arg;
	if (cookie->__ptr >= cookie->__end)
		return __EOF;
	return (__format_word_t)*cookie->__ptr++;
}
__LOCAL_LIBC(@vsnscanf_ungetc@) __SSIZE_TYPE__
(__FORMATPRINTER_CC vsnscanf_ungetc)(void *arg, __format_word_t __UNUSED(word)) {
	struct __vsnscanf_data *cookie;
	cookie = (struct __vsnscanf_data *)arg;
	--cookie->__ptr;
	return 0;
}
@@pop_namespace@@
)]]
__STDC_INT_AS_SSIZE_T __stdio_common_vsscanf($uint64_t options, char const *input, $size_t inputsize,
                                             [[nonnull], format] char const *format,
                                             $locale_t locale, $va_list args) {
	struct __NAMESPACE_LOCAL_SYM __vsnscanf_data data;
	(void)options;
	(void)locale;
	if (inputsize == (size_t)-1)
		return vsscanf(input, format, args);
	data.__ptr = (unsigned char const *)input;
	data.__end = (unsigned char const *)input + inputsize;
	return format_vscanf(&__NAMESPACE_LOCAL_SYM vsnscanf_getc,
	                     &__NAMESPACE_LOCAL_SYM vsnscanf_ungetc,
	                     (void *)&data, format, args);
}

/************************************************************************/
/* __stdio_common_* wrappers                                            */
/************************************************************************/
%[default:section(".text.crt.dos.unicode.locale.format.printf")];
[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__stdio_common_vsprintf)]]
__STDC_INT_AS_SSIZE_T _vsnprintf_l(char *buf, $size_t bufsize, [[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	__STDC_INT_AS_SSIZE_T result = __stdio_common_vsprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS | _CRT_INTERNAL_PRINTF_LEGACY_VSPRINTF_NULL_TERMINATION, buf, bufsize, format, locale, args);
	return result < 0 ? -1 : result;
}
[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__stdio_common_vsprintf_s)]]
__STDC_INT_AS_SSIZE_T _vsprintf_s_l(char *buf, $size_t bufsize, [[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	__STDC_INT_AS_SSIZE_T result = __stdio_common_vsprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, buf, bufsize, format, locale, args);
	return result < 0 ? -1 : result;
}
[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__stdio_common_vsprintf_p)]]
[[crt_intern_alias("_vsnprintf_l")]] /* Normal printf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vsprintf_p_l(char *buf, $size_t bufsize, [[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	__STDC_INT_AS_SSIZE_T result = __stdio_common_vsprintf_p(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, buf, bufsize, format, locale, args);
	return result < 0 ? -1 : result;
}
[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__stdio_common_vsprintf)]]
__STDC_INT_AS_SSIZE_T _vscprintf_l([[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	__STDC_INT_AS_SSIZE_T result = __stdio_common_vsprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS | _CRT_INTERNAL_PRINTF_STANDARD_SNPRINTF_BEHAVIOR, NULL, 0, format, locale, args);
	return result < 0 ? -1 : result;
}
[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__stdio_common_vsprintf_p)]]
[[crt_intern_alias("_vscprintf_l")]] /* Normal printf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vscprintf_p_l([[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	__STDC_INT_AS_SSIZE_T result = __stdio_common_vsprintf_p(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS | _CRT_INTERNAL_PRINTF_STANDARD_SNPRINTF_BEHAVIOR, NULL, 0, format, locale, args);
	return result < 0 ? -1 : result;
}
[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__stdio_common_vsprintf)]]
__STDC_INT_AS_SSIZE_T _vsnprintf_c_l(char *buf, $size_t bufsize, [[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	__STDC_INT_AS_SSIZE_T result = __stdio_common_vsprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, buf, bufsize, format, locale, args);
	return result < 0 ? -1 : result;
}
[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__stdio_common_vsnprintf_s)]]
__STDC_INT_AS_SSIZE_T _vsnprintf_s_l(char *buf, $size_t bufsize, $size_t maxsize, [[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	__STDC_INT_AS_SSIZE_T result = __stdio_common_vsnprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, buf, bufsize, maxsize, format, locale, args);
	return result < 0 ? -1 : result;
}
[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__stdio_common_vfprintf_s)]]
__STDC_INT_AS_SSIZE_T _vfprintf_s_l([[nonnull]] $FILE *stream, [[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	return __stdio_common_vfprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, stream, format, locale, args);
}
[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__stdio_common_vfprintf_p)]]
[[crt_intern_alias("_vfprintf_l")]] /* Normal printf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vfprintf_p_l([[nonnull]] $FILE *stream, [[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	return __stdio_common_vfprintf_p(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, stream, format, locale, args);
}
%[default:section(".text.crt.dos.FILE.locked.read.scanf")];
[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), wunused, requires_function(__stdio_common_vfscanf)]]
__STDC_INT_AS_SSIZE_T _vfscanf_l([[nonnull]] $FILE *stream, [[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	return __stdio_common_vfscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, stream, format, locale, args);
}
[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), crt_intern_alias("_vfscanf_l"),  wunused, requires_function(__stdio_common_vfscanf)]]
__STDC_INT_AS_SSIZE_T _vfscanf_s_l([[nonnull]] $FILE *stream, [[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	return __stdio_common_vfscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS | _CRT_INTERNAL_SCANF_SECURECRT, stream, format, locale, args);
}
[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), ignore, wunused, requires_function(__stdio_common_vsscanf)]]
__STDC_INT_AS_SSIZE_T _vsnscanf_l(char const *buf, $size_t bufsize, [[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	return __stdio_common_vsscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, buf, bufsize, format, locale, args);
}
[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), crt_intern_alias("_vsnscanf_l"), ignore, wunused, requires_function(__stdio_common_vsscanf)]]
__STDC_INT_AS_SSIZE_T _vsnscanf_s_l(char const *buf, $size_t bufsize, [[nonnull, format]] char const *format, $locale_t locale, va_list args) {
	return __stdio_common_vsscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS | _CRT_INTERNAL_SCANF_SECURECRT, buf, bufsize, format, locale, args);
}


/************************************************************************/
/* Direct aliases                                                       */
/************************************************************************/
%[default:section(".text.crt.dos.unicode.locale.format.printf")];
[[decl_include("<features.h>"), requires_function(vprintf)]]
__STDC_INT_AS_SSIZE_T _vprintf_l([[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	(void)locale;
	return vprintf(format, args);
}
[[decl_include("<features.h>"), requires_function(vfprintf)]]
__STDC_INT_AS_SSIZE_T _vfprintf_l([[nonnull]] $FILE *stream, [[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	(void)locale;
	return vfprintf(stream, format, args);
}
[[decl_include("<features.h>"), wunused, requires_function(vscanf)]]
__STDC_INT_AS_SSIZE_T _vscanf_l([[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	(void)locale;
	return vscanf(format, args);
}
[[decl_include("<features.h>")]]
__STDC_INT_AS_SSIZE_T _vsprintf_l([[nonnull]] char *buf, [[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	(void)locale;
	return vsprintf(buf, format, args);
}


/************************************************************************/
/* Misc. wrappers                                                       */
/************************************************************************/
%[default:section(".text.crt.dos.unicode.static.format.printf")];
[[decl_include("<features.h>"), requires_function(_vfprintf_p_l)]]
[[crt_intern_alias("vfprintf")]] /* Normal printf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vfprintf_p([[nonnull]] $FILE *stream, [[nonnull, format]] char const *format, $va_list args) {
	return _vfprintf_p_l(stream, format, NULL, args);
}
[[decl_include("<features.h>"), requires_function(_vprintf_p_l)]]
[[crt_intern_alias("vprintf")]] /* Normal printf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vprintf_p([[nonnull, format]] char const *format, $va_list args) {
	return _vprintf_p_l(format, NULL, args);
}
@@WARNING: This function returns the number of written character. - Not the required buffer size!
[[decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vsnprintf_l)]]
__STDC_INT_AS_SSIZE_T _vsnprintf(char *buf, $size_t bufsize, [[nonnull, format]] char const *format, $va_list args) {
	return _vsnprintf_l(buf, bufsize, format, NULL, args);
}
[[decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vsprintf_p_l)]]
[[crt_intern_alias("vsnprintf")]] /* Normal printf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vsprintf_p(char *buf, $size_t bufsize, [[nonnull, format]] char const *format, $va_list args) {
	return _vsprintf_p_l(buf, bufsize, format, NULL, args);
}
[[decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vsnprintf_s_l)]]
__STDC_INT_AS_SSIZE_T _vsnprintf_s(char *buf, $size_t bufsize, $size_t maxsize, [[nonnull, format]] char const *format, $va_list args) {
	return _vsnprintf_s_l(buf, bufsize, maxsize, format, NULL, args);
}
[[decl_include("<features.h>"), requires_function(_vscprintf_l), wunused]]
__STDC_INT_AS_SSIZE_T _vscprintf([[nonnull, format]] char const *format, $va_list args) {
	return _vscprintf_l(format, NULL, args);
}
[[decl_include("<features.h>"), requires_function(_vscprintf_p_l), wunused]]
[[crt_intern_alias("_vscprintf")]] /* Normal printf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vscprintf_p([[nonnull, format]] char const *format, $va_list args) {
	return _vscprintf_p_l(format, NULL, args);
}
[[decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vsnprintf_c_l)]]
__STDC_INT_AS_SSIZE_T _vsnprintf_c(char *buf, $size_t bufsize, [[nonnull, format]] char const *format, $va_list args) {
	return _vsnprintf_c_l(buf, bufsize, format, NULL, args);
}

%[default:section(".text.crt.dos.FILE.locked.read.scanf")];
[[decl_include("<features.h>"), requires_function(_vsnscanf_l), wunused, impl_include("<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vsscanf_l([[nonnull]] char const *buf, [[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	return _vsnscanf_l(buf, ($size_t)-1, format, locale, args);
}
[[decl_include("<features.h>"), crt_intern_alias("_vsscanf_l"), requires_function(_vsnscanf_s_l), wunused, impl_include("<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vsscanf_s_l([[nonnull]] char const *buf, [[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	return _vsnscanf_s_l(buf, ($size_t)-1, format, locale, args);
}

[[decl_include("<features.h>"), requires_function(_vsnscanf_l), wunused, ignore, impl_include("<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vsnscanf(char const *buf, $size_t bufsize, [[nonnull, format]] char const *format, $va_list args) {
	return _vsnscanf_l(buf, bufsize, format, NULL, args);
}
[[decl_include("<features.h>"), crt_intern_alias("_vsnscanf"),  requires_function(_vsnscanf_s_l), wunused, ignore, impl_include("<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vsnscanf_s(char const *buf, $size_t bufsize, [[nonnull, format]] char const *format, $va_list args) {
	return _vsnscanf_s_l(buf, bufsize, format, NULL, args);
}


/************************************************************************/
/* STD-stream wrapper functions                                         */
/************************************************************************/
%[default:section(".text.crt.dos.unicode.locale.format.printf")];
[[decl_include("<features.h>"), impl_include("<libc/template/stdstreams.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdout) && $has_function(_vfprintf_s_l))]]
__STDC_INT_AS_SSIZE_T _vprintf_s_l([[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	return _vfprintf_s_l(stdout, format, locale, args);
}
[[decl_include("<features.h>"), impl_include("<libc/template/stdstreams.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdout) && $has_function(_vfprintf_p_l))]]
[[crt_intern_alias("_vprintf_l")]] /* Normal printf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vprintf_p_l([[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	return _vfprintf_p_l(stdout, format, locale, args);
}
%[default:section(".text.crt.dos.FILE.locked.read.scanf")];
[[wunused, decl_include("<features.h>"), impl_include("<libc/template/stdstreams.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdin) && $has_function(_vfscanf_s_l))]]
__STDC_INT_AS_SSIZE_T _vscanf_s_l([[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	return _vfscanf_s_l(stdin, format, locale, args);
}


/************************************************************************/
/* Auto-generated printf wrapper functions                              */
/************************************************************************/
%[default:section(".text.crt.dos.unicode.locale.format.printf")];
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _fprintf_l([[nonnull]] $FILE *stream, [[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vfprintf_l")}
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _fprintf_s_l([[nonnull]] $FILE *stream, [[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vfprintf_s_l")}
%[default:section(".text.crt.dos.unicode.static.format.printf")];
[[crt_intern_alias("fprintf")]] /* Normal printf already supports positional arguments! */
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _fprintf_p([[nonnull]] $FILE *stream, [[nonnull, format]] char const *format, ...) %{printf("_vfprintf_p")}
%[default:section(".text.crt.dos.unicode.locale.format.printf")];
[[crt_intern_alias("_fprintf_l")]] /* Normal printf already supports positional arguments! */
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _fprintf_p_l([[nonnull]] $FILE *stream, [[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vfprintf_p_l")}
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _printf_l([[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vprintf_l")}
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _printf_s_l([[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vprintf_s_l")}
%[default:section(".text.crt.dos.unicode.static.format.printf")];
[[crt_intern_alias("printf")]] /* Normal printf already supports positional arguments! */
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _printf_p([[nonnull, format]] char const *format, ...) %{printf("_vprintf_p")}
%[default:section(".text.crt.dos.unicode.locale.format.printf")];
[[crt_intern_alias("_printf_l")]] /* Normal printf already supports positional arguments! */
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _printf_p_l([[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vprintf_p_l")}
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _sprintf_l([[nonnull]] char *buf, [[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vsprintf_l")}
[[decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _sprintf_s_l(char *buf, $size_t bufsize, [[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vsprintf_s_l")}
[[crt_intern_alias("_sprintf_l")]] /* Normal printf already supports positional arguments! */
[[decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _sprintf_p_l(char *buf, $size_t bufsize, [[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vsprintf_p_l")}
%[default:section(".text.crt.dos.unicode.static.format.printf")];
[[crt_intern_alias("snprintf")]] /* Normal printf already supports positional arguments! */
[[decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _sprintf_p(char *buf, $size_t bufsize, [[nonnull, format]] char const *format, ...) %{printf("_vsprintf_p")}
%[default:section(".text.crt.dos.unicode.locale.format.printf")];
[[decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _snprintf_l(char *buf, $size_t bufsize, [[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vsnprintf_l")}
%[default:section(".text.crt.dos.unicode.static.format.printf")];
[[decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _snprintf(char *buf, $size_t bufsize, [[nonnull, format]] char const *format, ...) %{printf("_vsnprintf")}
%[default:section(".text.crt.dos.unicode.locale.format.printf")];
[[decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _snprintf_c_l(char *buf, $size_t bufsize, [[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vsnprintf_c_l")}
%[default:section(".text.crt.dos.unicode.static.format.printf")];
[[decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _snprintf_c(char *buf, $size_t bufsize, [[nonnull, format]] char const *format, ...) %{printf("_vsnprintf_c")}
%[default:section(".text.crt.dos.unicode.locale.format.printf")];
[[decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _snprintf_s_l(char *buf, $size_t bufsize, $size_t maxsize, [[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vsnprintf_s_l")}
%[default:section(".text.crt.dos.unicode.static.format.printf")];
[[decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _snprintf_s(char *buf, $size_t bufsize, $size_t maxsize, [[nonnull, format]] char const *format, ...) %{printf("_vsnprintf_s")}
%[default:section(".text.crt.dos.unicode.locale.format.printf")];
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _scprintf_l([[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vscprintf_l")}
%[default:section(".text.crt.dos.unicode.static.format.printf")];
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _scprintf([[nonnull, format]] char const *format, ...) %{printf("_vscprintf")}
%[default:section(".text.crt.dos.unicode.locale.format.printf")];
[[crt_intern_alias("_scprintf_l")]] /* Normal printf already supports positional arguments! */
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _scprintf_p_l([[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vscprintf_p_l")}
%[default:section(".text.crt.dos.unicode.static.format.printf")];
[[crt_intern_alias("_scprintf")]] /* Normal printf already supports positional arguments! */
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _scprintf_p([[nonnull, format]] char const *format, ...) %{printf("_vscprintf_p")}
%[default:section(".text.crt.dos.FILE.locked.read.scanf")];
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _fscanf_l([[nonnull]] $FILE *stream, [[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vfscanf_l")}
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _fscanf_s_l([[nonnull]] $FILE *stream, [[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vfscanf_s_l")}
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _scanf_l([[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vscanf_l")}
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _scanf_s_l([[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vscanf_s_l")}
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _sscanf_l([[nonnull]] char const *buf, [[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vsscanf_l")}
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _sscanf_s_l([[nonnull]] char const *buf, [[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vsscanf_s_l")}
[[decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]] __STDC_INT_AS_SSIZE_T _snscanf_l(char const *buf, $size_t bufsize, [[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vsnscanf_l")}
[[decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]] __STDC_INT_AS_SSIZE_T _snscanf(char const *buf, $size_t bufsize, [[nonnull, format]] char const *format, ...) %{printf("_vsnscanf")}
[[decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]] __STDC_INT_AS_SSIZE_T _snscanf_s_l(char const *buf, $size_t bufsize, [[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vsnscanf_s_l")}
[[decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]] __STDC_INT_AS_SSIZE_T _snscanf_s(char const *buf, $size_t bufsize, [[nonnull, format]] char const *format, ...) %{printf("_vsnscanf_s")}



/************************************************************************/
/* DOS's "secure" functions                                             */
/************************************************************************/
%#ifdef __USE_DOS_SLIB
%[default:section(".text.crt.dos.unicode.static.format.printf")];
[[decl_include("<features.h>"), requires_function(_vfprintf_s_l)]]
__STDC_INT_AS_SSIZE_T vfprintf_s([[nonnull]] $FILE *stream, [[nonnull, format]] char const *format, $va_list args) {
	return _vfprintf_s_l(stream, format, NULL, args);
}
[[decl_include("<features.h>"), requires_function(_vprintf_s_l)]]
__STDC_INT_AS_SSIZE_T vprintf_s([[nonnull, format]] char const *format, $va_list args) {
	return _vprintf_s_l(format, NULL, args);
}
[[decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vsprintf_s_l)]]
__STDC_INT_AS_SSIZE_T vsprintf_s(char *buf, $size_t bufsize, [[nonnull, format]] char const *format, $va_list args) {
	return _vsprintf_s_l(buf, bufsize, format, NULL, args);
}
[[decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vsnprintf_s_l)]]
__STDC_INT_AS_SSIZE_T vsnprintf_s(char *buf, $size_t bufsize, $size_t maxsize, [[nonnull, format]] char const *format, $va_list args) {
	return _vsnprintf_s_l(buf, bufsize, maxsize, format, NULL, args);
}
%[default:section(".text.crt.dos.FILE.locked.read.scanf")];
[[decl_include("<features.h>"), requires_function(_vfscanf_s_l), wunused]]
__STDC_INT_AS_SSIZE_T vfscanf_s([[nonnull]] $FILE *stream, [[nonnull, format]] char const *format, $va_list args) {
	return _vfscanf_s_l(stream, format, NULL, args);
}
[[decl_include("<features.h>"), requires_function(_vscanf_s_l), wunused]]
__STDC_INT_AS_SSIZE_T vscanf_s([[nonnull, format]] char const *format, $va_list args) {
	return _vscanf_s_l(format, NULL, args);
}
[[decl_include("<features.h>"), requires_function(_vsscanf_s_l), wunused]]
__STDC_INT_AS_SSIZE_T vsscanf_s([[nonnull]] char const *buf, [[nonnull, format]] char const *format, $va_list args) {
	return _vsscanf_s_l(buf, format, NULL, args);
}
%[default:section(".text.crt.dos.unicode.static.format.printf")];
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T fprintf_s([[nonnull]] $FILE *stream, [[nonnull, format]] char const *format, ...) %{printf("vfprintf_s")}
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T printf_s([[nonnull, format]] char const *format, ...) %{printf("vprintf_s")}
[[decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T sprintf_s(char *buf, $size_t bufsize, [[nonnull, format]] char const *format, ...) %{printf("vsprintf_s")}
%[default:section(".text.crt.dos.FILE.locked.read.scanf")];
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T fscanf_s([[nonnull]] $FILE *stream, [[nonnull, format]] char const *format, ...) %{printf("vfscanf_s")}
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T scanf_s([[nonnull, format]] char const *format, ...) %{printf("vscanf_s")}
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T sscanf_s([[nonnull]] char const *buf, [[nonnull, format]] char const *format, ...) %{printf("vsscanf_s")}
%#endif /* __USE_DOS_SLIB */
%#endif /* __CC__ */
%#endif /* __USE_DOS */
%



%{

__SYSDECL_END

#if defined(__USE_DOS) && !defined(__USE_DOS_CLEAN)
#include <corecrt_wstdio.h> /* Include <wchar.h> instead */
#endif /* __USE_DOS && !__USE_DOS_CLEAN */

#if ((defined(__USE_XOPEN) && !defined(__USE_XOPEN2K) && !defined(__USE_GNU)) || defined(__USE_SOLARIS))
#include <getopt.h>
#endif /* (__USE_XOPEN && !__USE_XOPEN2K && !__USE_GNU) || __USE_SOLARIS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STDIO_H)
#include <parts/uchar/stdio.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_STDIO_H */
#endif /* __USE_UTF */

#ifdef __USE_KOS
#if defined(_WCHAR_H) && !defined(_PARTS_WCHAR_STDIO_H)
#include <parts/wchar/stdio.h>
#endif /* _WCHAR_H && !_PARTS_WCHAR_STDIO_H */
#endif /* __USE_KOS */

}
