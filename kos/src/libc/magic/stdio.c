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

/* Declare stdio data sections as known, so they are guarantied to get linked properly */
%[declare_known_section(".data.crt.FILE.core.read")]
%[declare_known_section(".data.crt.FILE.core.write")]
%[declare_known_section(".data.crt.FILE.core.seek")]
%[declare_known_section(".data.crt.FILE.core.utility")]
%[declare_known_section(".data.crt.FILE.locked.utility")]
%[declare_known_section(".data.crt.FILE.locked.read.read")]
%[declare_known_section(".data.crt.FILE.locked.write.write")]


%[define_replacement(FILE     = __FILE)]
%[define_replacement(fd_t     = __fd_t)]
%[define_replacement(atflag_t = __atflag_t)]
%[define_replacement(off_t    = "__FS_TYPE(off)")]
%[define_replacement(off32_t  = __off32_t)]
%[define_replacement(off64_t  = __off64_t)]
%[define_replacement(fpos_t   = "__FS_TYPE(pos)")]
%[define_replacement(fpos64_t = __pos64_t)]
%[define_replacement(pos32_t  = __pos32_t)]
%[define_replacement(pos64_t  = __pos64_t)]
%[define_replacement(cookie_io_functions_t = _IO_cookie_io_functions_t)]
%[define_replacement(locale_t = __locale_t)]
%[define_replacement(EOK      = 0)]
%[define_replacement(rsize_t  = __SIZE_TYPE__)]

/* These are defined in <local/stdstreams.h> */
%[define_replacement(stdin  = __LOCAL_stdin)]
%[define_replacement(stdout = __LOCAL_stdout)]
%[define_replacement(stderr = __LOCAL_stderr)]

%[define_replacement(SEEK_SET = __SEEK_SET)]
%[define_replacement(SEEK_CUR = __SEEK_CUR)]
%[define_replacement(SEEK_END = __SEEK_END)]
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

%(auto_source){
#include "../libc/globals.h"
}

%{
#include <features.h>

#include <asm/crt/stdio.h>
#include <asm/limits.h> /* __IOV_MAX */
#include <asm/oflags.h>
#include <asm/stdio.h>
#include <bits/types.h>
#include <kos/anno.h>

#include <libio.h>

#ifdef __USE_KOS
#include <bits/format-printer.h>
#endif /* __USE_KOS */

#ifdef __USE_DOS
#include <bits/crt/sys_errlist.h>
#include <xlocale.h>
#endif /* __USE_DOS */

#ifdef __CRT_CYG_PRIMARY
#include <sys/reent.h>
#endif /* __CRT_CYG_PRIMARY */

#ifdef __CRT_DOS_PRIMARY
#include <bits/crt/io-file.h>
#endif /* __CRT_DOS_PRIMARY */

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

#ifndef SEEK_SET
#define SEEK_SET __SEEK_SET /* Seek from beginning of file. */
#define SEEK_CUR __SEEK_CUR /* Seek from current position. */
#define SEEK_END __SEEK_END /* Seek from end of file. */
#ifdef __USE_GNU
#ifdef __SEEK_DATA
#define SEEK_DATA __SEEK_DATA /* Seek to next data. */
#endif /* __SEEK_DATA */
#ifdef __SEEK_HOLE
#define SEEK_HOLE __SEEK_HOLE /* Seek to next hole. */
#endif /* __SEEK_HOLE */
#endif /* __USE_GNU */
#endif /* !SEEK_SET */

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

#ifdef __USE_XOPEN2K8
#ifndef __off_t_defined
#define __off_t_defined 1
typedef __FS_TYPE(off) off_t;
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
typedef __pos64_t fpos64_t;
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
#   define stdin    (_iob + 0)
#   define stdout   (_iob + 1)
#   define stderr   (_iob + 2)
#else /* __USE_DOS_LINKOBJECTS */
#ifndef ____iob_func_defined
#define ____iob_func_defined 1
__LIBC __ATTR_WUNUSED __ATTR_RETNONNULL FILE *__NOTHROW(__LIBCCALL __iob_func)(void);
#endif /* !____iob_func_defined */
#   define stdin    (__iob_func() + 0)
#   define stdout   (__iob_func() + 1)
#   define stderr   (__iob_func() + 2)
#endif /* !__USE_DOS_LINKOBJECTS */
#else /* __CRT_... */
__LIBC __FILE *stdin;
#define stdin  stdin
__LIBC __FILE *stdout;
#define stdout stdout
__LIBC __FILE *stderr;
#define stderr stderr
#endif /* !__CRT_... */
#endif /* !__stdstreams_defined */
#endif /* !__NO_STDSTREAMS */


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

%[define_crt_name_list(CNL_fgetc             = ["fgetc", "getc", "_IO_getc"])]        /* int fgetc(FILE *) */
%[define_crt_name_list(CNL_fgetc_unlocked    = ["fgetc_unlocked", "getc_unlocked"])]  /* int fgetc_unlocked(FILE *) */

%[define_crt_name_list(CNL_fputc             = ["fputc", "putc", "_IO_putc"])]        /* int fputc(FILE *) */
%[define_crt_name_list(CNL_fputc_unlocked    = ["fputc_unlocked", "putc_unlocked"])]  /* int fputc_unlocked(FILE *) */

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
[[if(defined(__USE_STDIO_UNLOCKED)), alias(CNL_fwrite_unlocked...)]]
[[                                   alias(CNL_fwrite...)]]
[[                                   alias(CNL_fwrite_unlocked...)]]
$size_t crt_fwrite([[inp(min(elemsize * return, elemsize * elemcount))]] void const *__restrict buf,
                   $size_t elemsize, $size_t elemcount, [[nonnull]] $FILE *__restrict stream);

[[cp_stdio, ignore, nocrt, decl_include("<hybrid/typecore.h>")]]
[[alias(CNL_fwrite..., CNL_fwrite_unlocked...)]]
$size_t crt_fwrite_unlocked([[inp(min(elemsize * return, elemsize * elemcount))]] void const *__restrict buf,
                            $size_t elemsize, $size_t elemcount, [[nonnull]] $FILE *__restrict stream);

[[cp_stdio, ignore, wunused, nocrt, decl_include("<hybrid/typecore.h>")]]
[[if(defined(__USE_STDIO_UNLOCKED)), alias(CNL_fread_unlocked...)]]
[[                                   alias(CNL_fread...)]]
[[                                   alias(CNL_fread_unlocked...)]]
$size_t crt_fread([[outp(elemsize * elemcount)]] void *__restrict buf,
                  $size_t elemsize, $size_t elemcount,
                  [[nonnull]] $FILE *__restrict stream);

[[cp_stdio, ignore, wunused, nocrt, decl_include("<hybrid/typecore.h>")]]
[[alias(CNL_fread..., CNL_fread_unlocked...)]]
$size_t crt_fread_unlocked([[outp(elemsize * elemcount)]] void *__restrict buf,
                           $size_t elemsize, $size_t elemcount,
                           [[nonnull]] $FILE *__restrict stream);

[[cp_stdio, ignore, nocrt]]
[[if(defined(__USE_STDIO_UNLOCKED)), alias(CNL_fgetc_unlocked...)]]
[[                                   alias(CNL_fgetc...)]]
[[                                   alias(CNL_fgetc_unlocked...)]]
int crt_fgetc([[nonnull]] $FILE *__restrict stream);

[[cp_stdio, ignore, nocrt, alias(CNL_fgetc_unlocked..., CNL_fgetc...)]]
int crt_fgetc_unlocked([[nonnull]] $FILE *__restrict stream);

[[cp_stdio, ignore, nocrt]]
[[if(defined(__USE_STDIO_UNLOCKED)), alias(CNL_fputc_unlocked...)]]
[[                                   alias(CNL_fputc...)]]
[[                                   alias(CNL_fputc_unlocked...)]]
int crt_fputc(int ch, [[nonnull]] $FILE *__restrict stream);

[[cp_stdio, ignore, nocrt, alias(CNL_fputc_unlocked..., CNL_fputc...)]]
int crt_fputc_unlocked(int ch, [[nonnull]] $FILE *__restrict stream);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if(defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_fgetpos_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fgetpos64_unlocked...)]]
[[                                                                               alias(CNL_fgetpos...)]]
[[if(                                 __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fgetpos64...)]]
[[                                                                               alias(CNL_fgetpos_unlocked...)]]
[[if(                                 __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fgetpos64_unlocked...)]]
int crt_fgetpos([[nonnull]] $FILE *__restrict stream, [[nonnull]] $pos32_t *__restrict pos);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fgetpos_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_fgetpos64_unlocked...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fgetpos...)]]
[[                                                                               alias(CNL_fgetpos64...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fgetpos_unlocked...)]]
[[                                                                               alias(CNL_fgetpos64_unlocked...)]]
int crt_fgetpos64([[nonnull]] $FILE *__restrict stream, [[nonnull]] $pos64_t *__restrict pos);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if(defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_fsetpos_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fsetpos64_unlocked...)]]
[[                                                                               alias(CNL_fsetpos...)]]
[[if(                                 __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fsetpos64...)]]
[[                                                                               alias(CNL_fsetpos_unlocked...)]]
[[if(                                 __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fsetpos64_unlocked...)]]
int crt_fsetpos([[nonnull]] $FILE *__restrict stream, [[nonnull]] $pos32_t const *__restrict pos);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fsetpos_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_fsetpos64_unlocked...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fsetpos...)]]
[[                                                                               alias(CNL_fsetpos64...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fsetpos_unlocked...)]]
[[                                                                               alias(CNL_fsetpos64_unlocked...)]]
int crt_fsetpos64([[nonnull]] $FILE *__restrict stream, [[nonnull]] $pos64_t const *__restrict pos);

[[stdio_throws, ignore, nocrt]]
[[if(defined(__USE_STDIO_UNLOCKED)                                         ), alias(CNL_fseek_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
[[                                                                            alias(CNL_fseek...)]]
[[if(                                 __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[if(                                 __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64...)]]
[[                                                                            alias(CNL_fseek_unlocked...)]]
[[if(                                 __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if(                                 __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
int crt_fseek([[nonnull]] $FILE *__restrict stream, long int off, int whence);

[[stdio_throws, ignore, nocrt]]
[[if(defined(__USE_STDIO_UNLOCKED)),                                          alias(CNL_ftell_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
[[                                                                            alias(CNL_ftell...)]]
[[if(                                 __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[if(                                 __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64...)]]
[[                                                                            alias(CNL_ftell_unlocked...)]]
[[if(                                 __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if(                                 __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
long int crt_ftell([[nonnull]] $FILE *__restrict stream);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_fseeko_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
[[if(                                 __SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek...)]]
[[                                                                               alias(CNL_fseeko...)]]
[[if(                                 __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64...)]]
[[if(                                 __SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[                                                                               alias(CNL_fseeko_unlocked...)]]
[[if(                                 __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
int crt_fseeko([[nonnull]] $FILE *__restrict stream, $off32_t off, int whence);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_ftello_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
[[if(                                 __SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell...)]]
[[                                                                               alias(CNL_ftello...)]]
[[if(                                 __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64...)]]
[[if(                                 __SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[                                                                               alias(CNL_ftello_unlocked...)]]
[[if(                                 __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
$off32_t crt_ftello([[nonnull]] $FILE *__restrict stream);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_fseeko64_unlocked...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[                                                                               alias(CNL_fseeko64...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[                                                                               alias(CNL_fseeko64_unlocked...)]]
int crt_fseeko64([[nonnull]] $FILE *__restrict stream, $off32_t off, int whence);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_ftello64_unlocked...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[                                                                               alias(CNL_ftello64...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[                                                                               alias(CNL_ftello64_unlocked...)]]
$off64_t crt_ftello64([[nonnull]] $FILE *__restrict stream);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[                                              alias(CNL_fgetpos_unlocked...)]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fgetpos64_unlocked...)]]
[[                                              alias(CNL_fgetpos...)]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fgetpos64...)]]
int crt_fgetpos_unlocked([[nonnull]] $FILE *__restrict stream, [[nonnull]] $pos32_t *__restrict pos);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[                                              alias(CNL_fsetpos_unlocked...)]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fsetpos64_unlocked...)]]
[[                                              alias(CNL_fsetpos...)]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fsetpos64...)]]
int crt_fsetpos_unlocked([[nonnull]] $FILE *__restrict stream, [[nonnull]] $pos32_t const *__restrict pos);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fgetpos_unlocked...)]]
[[                                              alias(CNL_fgetpos64_unlocked...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fgetpos...)]]
[[                                              alias(CNL_fgetpos64...)]]
int crt_fgetpos64_unlocked([[nonnull]] $FILE *__restrict stream, [[nonnull]] $pos64_t *__restrict pos);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fsetpos_unlocked...)]]
[[                                              alias(CNL_fsetpos64_unlocked...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fsetpos...)]]
[[                                              alias(CNL_fsetpos64...)]]
int crt_fsetpos64_unlocked([[nonnull]] $FILE *__restrict stream, [[nonnull]] $pos64_t const *__restrict pos);

[[stdio_throws, ignore, nocrt]]
[[                                           alias(CNL_fseek_unlocked...)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
[[                                           alias(CNL_fseek...)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64...)]]
int crt_fseek_unlocked([[nonnull]] $FILE *__restrict stream, long int off, int whence);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[                                           alias(CNL_ftell_unlocked...)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
[[                                           alias(CNL_ftell...)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64...)]]
long int crt_ftell_unlocked([[nonnull]] $FILE *__restrict stream);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[                                              alias(CNL_fseeko_unlocked...)]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek...)]]
[[                                              alias(CNL_fseeko...)]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64...)]]
int crt_fseeko_unlocked([[nonnull]] $FILE *__restrict stream, $off32_t off, int whence);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[                                              alias(CNL_ftello_unlocked...)]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell...)]]
[[                                              alias(CNL_ftello...)]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64...)]]
$off32_t crt_ftello_unlocked([[nonnull]] $FILE *__restrict stream);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[                                              alias(CNL_fseeko64_unlocked...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[                                              alias(CNL_fseeko64...)]]
int crt_fseeko64_unlocked([[nonnull]] $FILE *__restrict stream, $off32_t off, int whence);

[[stdio_throws, ignore, nocrt, decl_include("<bits/types.h>")]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[                                              alias(CNL_ftello64_unlocked...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[                                              alias(CNL_ftello64...)]]
$off64_t crt_ftello64_unlocked([[nonnull]] $FILE *__restrict stream);

[[cp_stdio, ignore, nocrt, alias(CNL_flushall...)]]
int crt_flushall();


/************************************************************************/
/* END: Declare crt-only variants of file Apis                          */
/************************************************************************/




%[default:section(".text.crt{|.dos}.fs.modify")];

@@Remove a file or directory `FILENAME'
[[cp, std, guard]]
[[userimpl, requires(defined(__CRT_AT_FDCWD) && $has_function(removeat))]]
int remove([[nonnull]] char const *filename) {
	return removeat(__CRT_AT_FDCWD, filename);
}

@@Rename a given file `OLDNAME' to `NEWNAME_OR_PATH', or in the event
@@that `NEWNAME_OR_PATH' refers to a directory, place the file within.
[[cp, std, guard]]
[[userimpl, requires(defined(__CRT_AT_FDCWD) && $has_function(renameat))]]
int rename([[nonnull]] char const *oldname,
           [[nonnull]] char const *newname_or_path) {
	return renameat(__CRT_AT_FDCWD, oldname, __CRT_AT_FDCWD, newname_or_path);
}

%[default:section(".text.crt{|.dos}.fs.utility")]
[[std, wunused]] char *tmpnam([[nonnull]] char *buf);

%[default:section(".text.crt{|.dos}.FILE.locked.access")]
@@Close and destroy a given file `STREAM'
[[stdio_throws, std, dos_export_alias("_fclose_nolock"), export_alias("_IO_fclose")]]
int fclose([[nonnull]] FILE *__restrict stream);

%[default:section(".text.crt{|.dos}.FILE.locked.write.utility")]

@@Flush any unwritten data from `STREAM' to the underlying filesystem/TTY
[[std, cp_stdio, userimpl]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fflush...)]]
[[if(defined(__USE_STDIO_UNLOCKED)), alias(CNL_fflush_unlocked...)]]
[[                                   alias(CNL_fflush...)]]
[[                                   alias(CNL_fflush_unlocked...)]]
int fflush([[nullable]] FILE *stream) {
	/* NO-OP (When not implemented by the CRT, assume no
	 * buffering being done, meaning this function isn't needed) */
@@pp_if $has_function(crt_flushall)@@
	if (!stream)
		return crt_flushall();
@@pp_endif@@
	(void)stream;
	return 0;
}

%[default:section(".text.crt{|.dos}.FILE.locked.read.utility")]

@@Alias for `setvbuf(STREAM, buf, _IOFBF, BUFSIZ)'
[[std, requires_include("<asm/crt/stdio.h>"), impl_include("<asm/crt/stdio.h>")]]
[[requires(defined(___IOFBF) && defined(___IONBF) &&
           defined(__BUFSIZ) && $has_function(setvbuf))]]
void setbuf([[nonnull]] FILE *__restrict stream, [[nullable]] char *buf) {
	setvbuf(stream, buf,
	        buf ? ___IOFBF : ___IONBF,
	        buf ? __BUFSIZ : 0);
}

@@Set the buffer and buffer-mode to-be used by the given `STREAM'
@@@param modes: One of `_IOFBF', `_IOLBF' or `_IONBF'
[[decl_include("<hybrid/typecore.h>")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_setvbuf...)]]
[[if(defined(__USE_STDIO_UNLOCKED)), alias(CNL_setvbuf_unlocked...)]]
[[                                   alias(CNL_setvbuf...)]]
[[                                   alias(CNL_setvbuf_unlocked...)]]
int setvbuf([[nonnull]] FILE *__restrict stream,
            char *__restrict buf, int modes,
            size_t bufsize);

%[default:section(".text.crt{|.dos}.FILE.locked.read.getc")]

@@Read and return a single character from `STREAM'
@@If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
@@returned and the exact cause can be determined by using `ferror' and `feof'
[[std, cp_stdio, no_crt_self_import, no_crt_self_export, export_as(CNL_fgetc...)]]
[[if(defined(__USE_STDIO_UNLOCKED)), alias(CNL_fgetc_unlocked...)]]
[[                                   alias(CNL_fgetc...)]]
[[                                   alias(CNL_fgetc_unlocked...)]]
[[userimpl, requires((defined(__CRT_DOS) && $has_function(_filbuf)) || $has_function(crt_fread))]]
[[impl_include("<bits/crt/io-file.h>")]]
int fgetc([[nonnull]] FILE *__restrict stream) {
@@pp_if defined(__CRT_DOS) && $has_function(_filbuf) && (!defined(__USE_STDIO_UNLOCKED) || !$has_function(crt_fread))@@
	return --stream->__f_cnt >= 0 ? (int)((u8)*stream->__f_ptr++) : _filbuf(stream);
@@pp_else@@
	char ch;
	if (!crt_fread(&ch, sizeof(char), 1, stream))
		return EOF;
	return (int)ch;
@@pp_endif@@
}

%[insert:std_function(getc = fgetc)]

@@Alias for `fgetc(stdin)'
[[std, cp_stdio, requires_include("<__crt.h>")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("getchar_unlocked")]]
[[dos_export_alias("_fgetchar"), impl_include("<local/stdstreams.h>")]]
[[requires(!defined(__NO_STDSTREAMS) && $has_function(fgetc))]]
int getchar() {
	return fgetc(stdin);
}

%[default:section(".text.crt{|.dos}.FILE.locked.write.putc")]
@@Write a single character `CH' to `STREAM'
[[std, cp_stdio, crtbuiltin]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fputc...)]]
[[if(defined(__USE_STDIO_UNLOCKED)), alias(CNL_fputc_unlocked...)]]
[[                                   alias(CNL_fputc...)]]
[[                                   alias(CNL_fputc_unlocked...)]]
[[userimpl, requires((defined(__CRT_DOS) && $has_function(_flsbuf)) || $has_function(crt_fwrite))]]
[[impl_include("<bits/crt/io-file.h>")]]
int fputc(int ch, [[nonnull]] FILE *__restrict stream) {
@@pp_if defined(__CRT_DOS) && $has_function(_flsbuf) && (!defined(__USE_STDIO_UNLOCKED) || !$has_function(crt_fwrite))@@
	return --stream->__f_cnt >= 0 ? (int)((u8)(*stream->__f_ptr++ = (char)ch)) : _flsbuf(ch, stream);
@@pp_else@@
	unsigned char byte = (unsigned char)(unsigned int)ch;
	if (!crt_fwrite(&byte, sizeof(unsigned char), 1, stream))
		return EOF;
	return ch;
@@pp_endif@@
}

%[insert:std_function(putc = fputc)]

@@Alias for `fputc(CH, stdout)'
[[std, cp_stdio, crtbuiltin]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("putchar_unlocked")]]
[[dos_export_alias("_fputchar"), alias("putchar_unlocked")]]
[[requires_include("<__crt.h>"), impl_include("<local/stdstreams.h>")]]
[[requires(!defined(__NO_STDSTREAMS) && $has_function(fputc))]]
int putchar(int ch) {
	return fputc(ch, stdout);
}

%[default:section(".text.crt{|.dos}.FILE.locked.read.read")]

@@Read up to `BUFSIZE - 1' bytes of data from `STREAM', storing them into `BUF' stopped when
@@the buffer is full or a line-feed was read (in this case, the line-feed is also written to `BUF')
@@Afterwards, append a trailing NUL-character and re-return `BUF', or return `NULL' if an error occurred.
[[std, cp_stdio, wunused, decl_include("<features.h>")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("fgets_unlocked")]]
[[alias("fgets_unlocked"), impl_include("<hybrid/typecore.h>", "<parts/errno.h>")]]
[[requires($has_function(fgetc) && $has_function(ungetc) && $has_function(ferror))]]
char *fgets([[outp(min(strlen(return), bufsize))]] char *__restrict buf,
            __STDC_INT_AS_SIZE_T bufsize, [[nonnull]] FILE *__restrict stream) {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
#ifdef ERANGE
		__libc_seterrno(ERANGE);
#endif /* ERANGE */
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

%[default:section(".text.crt{|.dos}.FILE.locked.write.write")]
@@Print a given string `STR' to `STREAM'. This is identical to:
@@>> fwrite(str, sizeof(char), strlen(str), stream);
[[std, cp_stdio, crtbuiltin, decl_include("<features.h>")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("fputs_unlocked")]]
[[export_alias("_IO_fputs"), alias("fputs_unlocked")]]
[[requires($has_function(fwrite))]]
__STDC_INT_AS_SSIZE_T fputs([[nonnull]] char const *__restrict str,
                            [[nonnull]] FILE *__restrict stream) {
	__STDC_INT_AS_SIZE_T result;
	result = fwrite(str,
	                sizeof(char),
	                strlen(str),
	                stream);
	return result;
}

@@Print a given string `STR', followed by a line-feed to `STDOUT'
[[std, cp_stdio, crtbuiltin, decl_include("<features.h>")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("puts_unlocked")]]
[[export_alias("_IO_puts"), alias("puts_unlocked")]]
[[requires_include("<__crt.h>"), impl_include("<local/stdstreams.h>")]]
[[requires(!defined(__NO_STDSTREAMS) && $has_function(fputs) && $has_function(fputc))]]
__STDC_INT_AS_SSIZE_T puts([[nonnull]] char const *__restrict string) {
	__STDC_INT_AS_SSIZE_T result, temp;
	result = fputs(string, stdout);
	if (result >= 0) {
		temp = fputc('\n', stdout);
		if (temp <= 0)
			result = temp;
		else
			result += temp;
	}
	return result;
}

@@Unget a single character byte of data previously returned by `getc()'
[[std, no_crt_self_import, no_crt_self_export, export_as(CNL_ungetc...)]]
[[if(defined(__USE_STDIO_UNLOCKED)), alias(CNL_ungetc_unlocked...)]]
[[                                   alias(CNL_ungetc...)]]
[[                                   alias(CNL_ungetc_unlocked...)]]
[[section(".text.crt{|.dos}.FILE.locked.read.getc")]]
int ungetc(int ch, [[nonnull]] FILE *__restrict stream);

@@Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF'
[[std, cp_stdio, wunused, decl_include("<hybrid/typecore.h>")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fread...)]]
[[if(defined(__USE_STDIO_UNLOCKED)), alias(CNL_fread_unlocked...)]]
[[                                   alias(CNL_fread...)]]
[[                                   alias(CNL_fread_unlocked...)]]
[[userimpl, requires_function(fgetc), section(".text.crt{|.dos}.FILE.locked.read.read")]]
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


@@Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM'
[[std, cp_stdio, crtbuiltin, decl_include("<hybrid/typecore.h>")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fwrite...)]]
[[if(defined(__USE_STDIO_UNLOCKED)), alias(CNL_fwrite_unlocked...)]]
[[                                   alias(CNL_fwrite...)]]
[[                                   alias(CNL_fwrite_unlocked...)]]
[[section(".text.crt{|.dos}.FILE.locked.write.write")]]
[[userimpl, requires_function(fputc)]]
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
@@Change the current in-file position of `STREAM' as a byte-offet from the start of the file
[[stdio_throws, std, no_crt_self_import, no_crt_self_export, export_as(CNL_fseek...)]]
[[if(defined(__USE_STDIO_UNLOCKED)                                         ), alias(CNL_fseek_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
[[                                                                            alias(CNL_fseek...)]]
[[if(                                 __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[if(                                 __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64...)]]
[[                                                                            alias(CNL_fseek_unlocked...)]]
[[if(                                 __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if(                                 __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
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

@@Return the current in-file position of `STREAM' as a byte-offet from the start of the file
[[stdio_throws, std, wunused, no_crt_self_import, no_crt_self_export, export_as(CNL_ftell...)]]
[[if(defined(__USE_STDIO_UNLOCKED)                                         ), alias(CNL_ftell_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
[[                                                                            alias(CNL_ftell...)]]
[[if(                                 __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[if(                                 __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64...)]]
[[                                                                            alias(CNL_ftell_unlocked...)]]
[[if(                                 __SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if(                                 __SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
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

%[default:section(".text.crt{|.dos}.FILE.locked.seek.utility")]

@@Rewind the current in-file position of `STREAM' to its starting position
[[stdio_throws, std, export_alias("rewind_unlocked")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("rewind_unlocked")]]
[[userimpl, requires_function(fsetpos)]]
void rewind([[nonnull]] FILE *__restrict stream) {
	fsetpos(stream, 0);
}

%[default:section(".text.crt{|.dos}.FILE.locked.access")]

@@Clear the error state of `STREAM', returning the stream to normal operations mode
[[std, export_alias("clearerr_unlocked")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("clearerr_unlocked")]]
void clearerr([[nonnull]] $FILE *__restrict stream);

%[define_c_language_keyword(__KOS_FIXED_CONST)]

%[default:section(".text.crt{|.dos}.FILE.locked.read.utility")]
@@Check if end-of-file has been reached in `STREAM'
[[decl_include("<features.h>")]]
[[std, wunused, ATTR_PURE, export_alias("_IO_feof", "feof_unlocked")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("feof_unlocked")]]
int feof([[nonnull]] $FILE __KOS_FIXED_CONST *__restrict stream);

%[default:section(".text.crt{|.dos}.FILE.locked.utility")]

@@Check if an I/O error occurred in `STREAM'
[[decl_include("<features.h>")]]
[[std, wunused, ATTR_PURE, export_alias("_IO_ferror", "ferror_unlocked")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("ferror_unlocked")]]
int ferror([[nonnull]] $FILE __KOS_FIXED_CONST *__restrict stream);

%[default:section(".text.crt{|.dos}.errno.utility")]

@@Print a given `MESSAGE' alongside `strerror(errno)' to stderr:
@@>> if (message) {
@@>>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
@@>> } else {
@@>>     fprintf(stderr, "%s\n", strerror(errno));
@@>> }
[[cp, std, guard]]
[[requires_include("<__crt.h>", "<parts/errno.h>")]]
[[impl_include("<local/stdstreams.h>", "<parts/errno.h>")]]
[[requires(!defined(__NO_STDSTREAMS) && defined(__libc_geterrno) &&
           $has_function(fprintf) && $has_function(strerror))]]
void perror([[nullable]] char const *message) {
	char const *enodesc;
	enodesc = strerror(__libc_geterrno());
	if (message) {
		fprintf(stderr, "%s: %s\n",
		        message, enodesc);
	} else {
		fprintf(stderr, "%s\n",
		        enodesc);
	}
}


%[default:section(".text.crt{|.dos}.FILE.locked.access")]

@@Create and return a new file-stream for accessing a temporary file for reading/writing
[[cp, std, wunused, alias("tmpfile64")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("tmpfile64")]]
FILE *tmpfile();

@@Create and return a new file-stream for accessing `FILENAME'
[[cp, std, wunused, export_alias("_IO_fopen"), alias("fopen64")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("fopen64")]]
FILE *fopen([[nonnull]] char const *__restrict filename,
            [[nonnull]] char const *__restrict modes);

@@Re-open the given `STREAM' as a file-stream for accessing `FILENAME'
[[cp, std]]
[[if(defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)), preferred_alias("freopen64_unlocked")]]
[[if(defined(__USE_STDIO_UNLOCKED)                                ), preferred_alias("freopen_unlocked")]]
[[if(defined(__USE_FILE_OFFSET64)                                 ), preferred_alias("freopen64")]]
[[alias("freopen64", "freopen_unlocked", "freopen64_unlocked")]]
FILE *freopen([[nonnull]] char const *__restrict filename,
              [[nonnull]] char const *__restrict modes,
              [[nonnull]] FILE *__restrict stream);

%[default:section(".text.crt{|.dos}.FILE.locked.seek.pos")]

@@Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
@@Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()'
[[stdio_throws, std, decl_include("<bits/types.h>")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fgetpos...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fgetpos_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fgetpos64_unlocked...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fgetpos...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fgetpos64...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fgetpos_unlocked...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fgetpos64_unlocked...)]]
[[userimpl, requires($has_function(crt_ftello64) || $has_function(crt_fgetpos) ||
                     $has_function(crt_fgetpos64) || $has_function(crt_ftello64) ||
                     $has_function(crt_ftello) || $has_function(crt_ftell))]]
int fgetpos([[nonnull]] FILE *__restrict stream, [[nonnull]] fpos_t *__restrict pos) {
@@pp_if defined(__USE_FILE_OFFSET64) && $has_function(crt_ftello64)@@
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

@@Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()'
[[stdio_throws, std, decl_include("<bits/types.h>")]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fsetpos...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fsetpos_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fsetpos64_unlocked...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fsetpos...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fsetpos64...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fsetpos_unlocked...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fsetpos64_unlocked...)]]
[[userimpl, requires($has_function(crt_fseeko64) || $has_function(crt_fsetpos) ||
                     $has_function(crt_fsetpos64) || $has_function(crt_fseeko) ||
                     $has_function(crt_fseek))]]
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

@@Print data to `STREAM', following `FORMAT'
@@Return the number of successfully printed bytes
[[decl_include("<features.h>")]]
[[std, cp_stdio, crtbuiltin, ATTR_LIBC_PRINTF(2, 0)]]
[[section(".text.crt{|.dos}.FILE.locked.write.printf")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("vfprintf_unlocked")]]
[[requires_dependent_function(file_printer), alias("vfprintf_s")]]
[[export_alias("_IO_vfprintf"), alias("vfprintf_unlocked")]]
__STDC_INT_AS_SSIZE_T vfprintf([[nonnull]] FILE *__restrict stream,
                               [[nonnull]] char const *__restrict format, $va_list args) {
	return (__STDC_INT_AS_SSIZE_T)format_vprintf(&file_printer, stream, format, args);
}

@@Print data to `STREAM', following `FORMAT'
@@Return the number of successfully printed bytes
[[decl_include("<features.h>")]]
[[std, cp_stdio, ATTR_LIBC_PRINTF(2, 3), export_alias("_IO_fprintf")]]
[[section(".text.crt{|.dos}.FILE.locked.write.printf"), crtbuiltin]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("fprintf_unlocked")]]
[[alias("fprintf_s", "fprintf_unlocked")]]
__STDC_INT_AS_SSIZE_T fprintf([[nonnull]] FILE *__restrict stream,
                              [[nonnull]] char const *__restrict format, ...)
	%{printf("vfprintf")}


@@Print data to `stdout', following `FORMAT'
@@Return the number of successfully printed bytes
[[decl_include("<features.h>")]]
[[std, cp_stdio, crtbuiltin, ATTR_LIBC_PRINTF(1, 0)]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("vprintf_unlocked")]]
[[alias("vprintf_s", "vprintf_unlocked")]]
[[requires_include("<__crt.h>"), impl_include("<local/stdstreams.h>")]]
[[requires(!defined(__NO_STDSTREAMS) && $has_function(vfprintf))]]
[[section(".text.crt{|.dos}.FILE.locked.write.printf")]]
__STDC_INT_AS_SSIZE_T vprintf([[nonnull]] char const *__restrict format, $va_list args) {
	return vfprintf(stdout, format, args);
}

@@Print data to `stdout', following `FORMAT'
@@Return the number of successfully printed bytes
[[decl_include("<features.h>")]]
[[std, cp_stdio, ATTR_LIBC_PRINTF(1, 2), crtbuiltin]]
[[export_alias("_IO_printf", "printf_s")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("printf_unlocked")]]
[[section(".text.crt{|.dos}.FILE.locked.write.printf"), alias("printf_unlocked")]]
__STDC_INT_AS_SSIZE_T printf([[nonnull]] char const *__restrict format, ...)
	%{printf("vprintf")}

%(std)
%(std)#if defined(__USE_ISOC99) || defined(__USE_DOS)

%[default:section(".text.crt{|.dos}.FILE.locked.read.read")]

@@Scan data from `STREAM', following `FORMAT'
@@Return the number of successfully scanned data items
[[std, cp_stdio, guard, ATTR_LIBC_SCANF(2, 0), wunused]]
[[alias("_vfscanf", "_vfscanf_s"), export_alias("_IO_vfscanf")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("vfscanf_unlocked")]]
[[requires($has_function(fgetc) && $has_function(ungetc))]]
[[section(".text.crt{|.dos}.FILE.locked.read.scanf"), alias("vfscanf_unlocked")]]
[[decl_include("<features.h>"), dependency(fgetc)]]
[[impl_include("<hybrid/typecore.h>"), impl_prefix(
@@push_namespace(local)@@
@@pp_if !defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_SIZE_T__ != __SIZEOF_INT__@@
__LOCAL_LIBC(@vfscanf_getc@) ssize_t
(__FORMATPRINTER_CC vfscanf_getc)(void *arg) {
	return (ssize_t)fgetc((FILE *)arg);
}
@@pp_endif@@
__LOCAL_LIBC(@vfscanf_ungetc@) ssize_t
(__FORMATPRINTER_CC vfscanf_ungetc)(void *arg, char32_t ch) {
	return ungetc((int)(unsigned int)ch, (FILE *)arg);
}
@@pop_namespace@@
), crtbuiltin, export_alias("__vfscanf")]]
__STDC_INT_AS_SIZE_T vfscanf([[nonnull]] FILE *__restrict stream,
                             [[nonnull]] char const *__restrict format,
                             $va_list args) {
@@pp_if defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_SIZE_T__ == __SIZEOF_INT__@@
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

@@Scan data from `stdin', following `FORMAT'
@@Return the number of successfully scanned data items
[[decl_include("<features.h>")]]
[[std, cp_stdio, guard, crtbuiltin, ATTR_LIBC_SCANF(1, 0), wunused]]
[[requires_include("<__crt.h>"), alias("_vscanf", "vscanf_unlocked")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(vscanf_unlocked)]]
[[requires(!defined(__NO_STDSTREAMS) && $has_function(vfscanf))]]
[[impl_include("<local/stdstreams.h>"), section(".text.crt{|.dos}.FILE.locked.read.scanf")]]
__STDC_INT_AS_SIZE_T vscanf([[nonnull]] char const *__restrict format, $va_list args) {
	return vfscanf(stdin, format, args);
}
%(std)#endif /* __USE_ISOC99 || __USE_DOS */

%(std)

@@Scan data from `STREAM', following `FORMAT'
@@Return the number of successfully scanned data items
[[decl_include("<features.h>")]]
[[std, cp_stdio, crtbuiltin, ATTR_LIBC_SCANF(2, 3), wunused]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("fscanf_unlocked")]]
[[section(".text.crt{|.dos}.FILE.locked.read.scanf"), alias("fscanf_unlocked")]]
__STDC_INT_AS_SIZE_T fscanf([[nonnull]] FILE *__restrict stream,
                            [[nonnull]] char const *__restrict format, ...)
	%{printf("vfscanf")}

@@Scan data from `stdin', following `FORMAT'
@@Return the number of successfully scanned data items
[[decl_include("<features.h>")]]
[[std, cp_stdio, crtbuiltin, ATTR_LIBC_SCANF(1, 2), wunused]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("scanf_unlocked")]]
[[section(".text.crt{|.dos}.FILE.locked.read.scanf"), alias("scanf_unlocked")]]
__STDC_INT_AS_SIZE_T scanf([[nonnull]] char const *__restrict format, ...)
	%{printf("vscanf")}




%(std)
%(std)#if !defined(__USE_ISOC11) || (defined(__cplusplus) && __cplusplus <= 201103L)
[[std, cp_stdio, guard, wunused]]
[[deprecated("No buffer size checks (use `fgets' instead)")]]
[[export_alias("_IO_gets"), requires_include("<__crt.h>")]]
[[impl_include("<local/stdstreams.h>", "<hybrid/typecore.h>")]]
[[requires(!defined(__NO_STDSTREAMS) && $has_function(fgets))]]
char *gets([[nonnull]] char *__restrict buf) {
	return fgets(buf, INT_MAX, stdin);
}
%(std)#endif /* !__USE_ISOC11 || __cplusplus <= 201103L */

%(std)
%(std)#if defined(__USE_ISOC99) || defined(__USE_DOS)


%[define(DEFINE_VSSCANF_HELPERS_C8 =
@@pp_ifndef ____vsscanf_getc_defined@@
#define ____vsscanf_getc_defined 1
@@push_namespace(local)@@
__LOCAL_LIBC(@vsscanf_getc@) ssize_t
(FORMATPRINTER_CC vsscanf_getc)(void *arg) {
	char const *reader = *(char const **)arg;
	char32_t result = unicode_readutf8(&reader);
	if (!result)
		return __EOF;
	*(char const **)arg = reader;
	return result;
}
__LOCAL_LIBC(@vsscanf_ungetc@) ssize_t
(FORMATPRINTER_CC vsscanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	unicode_readutf8_rev((char const **)arg);
	return 0;
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_VSSCANF_HELPERS_C16 =
@@pp_ifndef ____vsc16scanf_getc_defined@@
#define ____vsc16scanf_getc_defined 1
@@push_namespace(local)@@
__LOCAL_LIBC(@vsc16scanf_getc@) ssize_t
(FORMATPRINTER_CC vsc16scanf_getc)(void *arg) {
	char16_t const *reader = *(char16_t const **)arg;
	char32_t result = unicode_readutf16(&reader);
	if (!result)
		return __EOF;
	*(char16_t const **)arg = reader;
	return result;
}
__LOCAL_LIBC(@vsc16scanf_ungetc@) ssize_t
(FORMATPRINTER_CC vsc16scanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	unicode_readutf16_rev((char16_t const **)arg);
	return 0;
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_VSSCANF_HELPERS_C32 =
@@pp_ifndef ____vsc32scanf_getc_defined@@
#define ____vsc32scanf_getc_defined 1
@@push_namespace(local)@@
__LOCAL_LIBC(@vsc32scanf_getc@) ssize_t
(FORMATPRINTER_CC vsc32scanf_getc)(void *arg) {
	char32_t const *reader = *(char32_t const **)arg;
	char32_t result = *reader++;
	if (!result)
		return __EOF;
	*(char32_t const **)arg = reader;
	return result;
}
__LOCAL_LIBC(@vsc32scanf_ungetc@) ssize_t
(FORMATPRINTER_CC vsc32scanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	--*(char32_t const **)arg;
	return 0;
}
@@pop_namespace@@
@@pp_endif@@
)]

@@Scan data from a given `INPUT' string, following `FORMAT'
@@Return the number of successfully scanned data items
[[guard, std, guard, crtbuiltin, impl_include("<asm/crt/stdio.h>")]]
[[wunused, ATTR_LIBC_SCANF(2, 0), decl_include("<features.h>")]]
[[dependency(unicode_readutf8, unicode_readutf8_rev)]]
[[impl_include("<hybrid/typecore.h>", "<bits/format-printer.h>")]]
[[impl_prefix(DEFINE_VSSCANF_HELPERS_C8), alias("_vsscanf", "_vsscanf_s")]]
[[section(".text.crt{|.dos}.unicode.static.format.scanf"), export_alias("__vsscanf")]]
__STDC_INT_AS_SIZE_T vsscanf([[nonnull]] char const *__restrict input,
                             [[nonnull]] char const *__restrict format, $va_list args) {
	char const *input_pointer = input;
@@pp_if __SIZEOF_CHAR__ == 1@@
	return format_vscanf(&__NAMESPACE_LOCAL_SYM vsscanf_getc,
	                     &__NAMESPACE_LOCAL_SYM vsscanf_ungetc,
	                     (void *)&input_pointer, format, args);
@@pp_elif __SIZEOF_CHAR__ == 2@@
	return format_vscanf(&__NAMESPACE_LOCAL_SYM vsc16scanf_getc,
	                     &__NAMESPACE_LOCAL_SYM vsc16scanf_ungetc,
	                     (void *)&input_pointer, format, args);
@@pp_else@@
	return format_vscanf(&__NAMESPACE_LOCAL_SYM vsc32scanf_getc,
	                     &__NAMESPACE_LOCAL_SYM vsc32scanf_ungetc,
	                     (void *)&input_pointer, format, args);
@@pp_endif@@
}
%(std)#endif /* __USE_ISOC99 || __USE_DOS */

%(std)
@@Scan data from a given `INPUT' string, following `FORMAT'
@@Return the number of successfully scanned data items
[[decl_include("<features.h>")]]
[[std, ATTR_LIBC_SCANF(2, 3), crtbuiltin, export_alias("_IO_sscanf")]]
[[section(".text.crt{|.dos}.unicode.static.format.scanf")]]
__STDC_INT_AS_SIZE_T sscanf([[nonnull]] char const *__restrict input,
                            [[nonnull]] char const *__restrict format, ...)
	%{printf("vsscanf")}


@@Print a formatted string to a given in-member string buffer `BUF'
@@Return the number of written characters, excluding a trailing NUL-character
[[decl_include("<features.h>")]]
[[std, ATTR_LIBC_PRINTF(2, 0), kernel, crtbuiltin, alias("_IO_vsprintf")]]
[[if(!defined(__KERNEL__)), export_as("_IO_vsprintf")]]
[[section(".text.crt{|.dos}.unicode.static.format.printf"), dependency(format_sprintf_printer)]]
__STDC_INT_AS_SSIZE_T vsprintf([[nonnull]] char *__restrict dest,
                               [[nonnull]] char const *__restrict format, $va_list args) {
	__STDC_INT_AS_SSIZE_T result;
	char *dest_pointer = dest;
	result = (__STDC_INT_AS_SSIZE_T)format_vprintf(&format_sprintf_printer,
	                                               (void *)&dest_pointer,
	                                               format, args);
	if (result >= 0)
		*dest_pointer = '\0';
	return result;
}

@@Print a formatted string to a given in-member string buffer `BUF'
@@Return the number of written characters, excluding a trailing NUL-character
[[decl_include("<features.h>")]]
[[std, ATTR_LIBC_PRINTF(2, 3), kernel, crtbuiltin, alias("_IO_sprintf")]]
[[if(!defined(__KERNEL__)), export_as("_IO_sprintf")]]
[[section(".text.crt{|.dos}.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T sprintf([[nonnull]] char *__restrict buf,
                             [[nonnull]] char const *__restrict format, ...)
	%{printf("vsprintf")}


%(std)
%(std)#if defined(__USE_ISOC99) || defined(__USE_UNIX98) || defined(__USE_DOS)

@@Print a formatted string to a given in-member string buffer `BUF'
@@Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF'
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[ATTR_LIBC_PRINTF(3, 0), std, kernel, guard]]
[[impl_prefix(
#ifndef ____format_snprintf_data_defined
#define ____format_snprintf_data_defined 1
struct __format_snprintf_data {
	char         *__sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ __sd_bufsiz; /* Remaining buffer size. */
};
#endif /* !____format_snprintf_data_defined */
), crtbuiltin, dependency(format_snprintf_printer)]]
[[section(".text.crt{|.dos}.unicode.static.format.printf"), alias("__vsnprintf")]]
[[if(!defined(__KERNEL__)), export_as("__vsnprintf")]]
__STDC_INT_AS_SIZE_T vsnprintf([[outp_opt(min(return, buflen))]] char *__restrict buf, size_t buflen,
                               [[nonnull]] char const *__restrict format, $va_list args) {
	struct __format_snprintf_data data;
	__STDC_INT_AS_SSIZE_T result;
	data.__sd_buffer = buf;
	data.__sd_bufsiz = buflen;
	result = (__STDC_INT_AS_SSIZE_T)format_vprintf(&format_snprintf_printer,
	                                               (void *)&data, format, args);
	if (result >= 0 && data.__sd_bufsiz != 0)
		*data.__sd_buffer = '\0';
	return result;
}

@@Print a formatted string to a given in-member string buffer `BUF'
@@Always return the REQUIRED buffer size (excluding a trailing NUL-character),
@@and never write more than `BUFLEN' characters to `BUF'
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[std, kernel, guard, crtbuiltin, ATTR_LIBC_PRINTF(3, 4)]]
[[section(".text.crt{|.dos}.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T snprintf([[outp_opt(min(return, buflen))]] char *__restrict buf, size_t buflen,
                              [[nonnull]] char const *__restrict format, ...)
	%{printf("vsnprintf")}
%(std)#endif /* __USE_ISOC99 || __USE_UNIX98 || __USE_DOS */


%
%#ifdef __USE_XOPEN2K8
[[section(".text.crt{|.dos}.io.write"), decl_include("<features.h>")]]
[[impl_include("<hybrid/typecore.h>", "<hybrid/host.h>", "<bits/format-printer.h>")]]
[[cp, requires_dependent_function(write), impl_prefix(
@@pp_if !defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_INT__ != __SIZEOF_POINTER__@@
@@push_namespace(local)@@
__LOCAL_LIBC(@vdprintf_printer@) __ssize_t
(__FORMATPRINTER_CC __vdprintf_printer)(void *__arg, char const *__restrict __data, __size_t __datalen) {
	return (__ssize_t)write((int)(unsigned int)(__UINTPTR_TYPE__)__arg, __data, __datalen);
}
@@pop_namespace@@
@@pp_endif@@
), ATTR_LIBC_PRINTF(2, 0)]]
__STDC_INT_AS_SSIZE_T vdprintf($fd_t fd, [[nonnull]] char const *__restrict format, $va_list args) {
@@pp_if !defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_INT__ != __SIZEOF_POINTER__@@
	return format_vprintf(&__NAMESPACE_LOCAL_SYM __vdprintf_printer,
	                      (void *)(__UINTPTR_TYPE__)(unsigned int)fd,
	                      format, args);
@@pp_else@@
	return format_vprintf((pformatprinter)(void *)&write,
	                      (void *)(__UINTPTR_TYPE__)(unsigned int)fd,
	                      format, args);
@@pp_endif@@
}

[[decl_include("<features.h>")]]
[[cp, ATTR_LIBC_PRINTF(2, 3), section(".text.crt{|.dos}.io.write")]]
__STDC_INT_AS_SSIZE_T dprintf($fd_t fd, [[nonnull]] char const *__restrict format, ...)
	%{printf("vdprintf")}
%#endif /* __USE_XOPEN2K8 */

%
%#ifdef __USE_ATFILE
[[cp, userimpl, requires_function(frenameat), section(".text.crt{|.dos}.fs.modify")]]
int renameat($fd_t oldfd, [[nonnull]] char const *oldname,
             $fd_t newfd, [[nonnull]] char const *newname_or_path) {
	return frenameat(oldfd, oldname, newfd, newname_or_path, 0);
}

%
%#ifdef __USE_KOS
@@Remove a file or directory `FILENAME' relative to a given base directory `DIRFD'
[[cp, section(".text.crt{|.dos}.fs.modify")]]
int removeat($fd_t dirfd, [[nonnull]] char const *filename);

@@@param flags: Set of `0 | AT_DOSPATH'
[[cp, section(".text.crt{|.dos}.fs.modify")]]
int frenameat($fd_t oldfd, [[nonnull]] char const *oldname,
              $fd_t newfd, [[nonnull]] char const *newname_or_path,
              $atflag_t flags);

%#endif /* __USE_KOS */
%#endif /* __USE_ATFILE */

%
%#ifdef __USE_MISC
[[wunused, userimpl, requires_function(tmpnam)]]
[[section(".text.crt{|.dos}.fs.utility")]]
char *tmpnam_r([[nonnull]] char *buf) {
	return buf ? tmpnam(buf) : NULL;
}

@@Specify the location and size for the buffer to-be used by `STREAM'
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

@@Change the given `STREAM' to become line-buffered
[[section(".text.crt{|.dos}.FILE.locked.read.utility")]]
[[requires_function(setvbuf)]]
void setlinebuf([[nonnull]] $FILE *__restrict stream) {
	setvbuf(stream, NULL, _IOLBF, 0);
}

@@Same as `fflush()', but performs I/O without acquiring a lock to `STREAM'
[[section(".text.crt{|.dos}.FILE.unlocked.write.utility")]]
[[cp_stdio, userimpl, no_crt_self_import, no_crt_self_export]]
[[export_alias(CNL_fflush_unlocked...), alias(CNL_fflush...)]]
int fflush_unlocked([[nullable]] $FILE *stream) {
	/* NO-OP (When not implemented by the CRT, assume no
	 * buffering being done, meaning this function isn't needed) */
@@pp_if $has_function(crt_flushall)@@
	if (!stream)
		return crt_flushall();
@@pp_endif@@
	(void)stream;
	return 0;
}

@@Same as `fread()', but performs I/O without acquiring a lock to `STREAM'
[[cp_stdio, wunused, decl_include("<hybrid/typecore.h>")]]
[[no_crt_self_import, no_crt_self_export]]
[[export_alias(CNL_fread_unlocked...), alias(CNL_fread...)]]
[[section(".text.crt{|.dos}.FILE.unlocked.read.read")]]
[[userimpl, requires_function(fgetc_unlocked)]]
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

@@Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM'
[[cp_stdio, wunused, decl_include("<hybrid/typecore.h>")]]
[[no_crt_self_import, no_crt_self_export]]
[[export_alias(CNL_fwrite_unlocked...), alias(CNL_fwrite...)]]
[[section(".text.crt{|.dos}.FILE.unlocked.write.write")]]
[[userimpl, requires_function(fgetc_unlocked)]]
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


@@Same as `feof()', but performs I/O without acquiring a lock to `STREAM'
feof_unlocked(*) = feof;

@@Same as `ferror()', but performs I/O without acquiring a lock to `STREAM'
ferror_unlocked(*) = ferror;

@@Same as `clearerr()', but performs I/O without acquiring a lock to `STREAM'
clearerr_unlocked(*) = clearerr;

@@Same as `fileno()', but performs I/O without acquiring a lock to `STREAM'
fileno_unlocked(*) = fileno;


%[default:section(".text.crt{|.dos}.FILE.unlocked.read.getc")]
@@Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM'
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

@@Same as `fputc()', but performs I/O without acquiring a lock to `STREAM'
[[cp_stdio, no_crt_self_import, no_crt_self_export, export_alias(CNL_fputc_unlocked...)]]
[[if(!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf)), alias(CNL_fputc...)]]
[[crtbuiltin, userimpl, requires((defined(__CRT_DOS) && $has_function(_flsbuf)) || $has_function(crt_fwrite_unlocked))]]
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
[[dos_export_alias("_tempnam"), ATTR_MALLOC, wunused]]
char *tempnam(char const *dir, char const *pfx);
%#endif /* __USE_MISC || __USE_XOPEN || __USE_DOS */


%
%#if defined(__USE_POSIX) || defined(__USE_DOS)
%[default:section(".text.crt{|.dos}.FILE.locked.utility")]
@@Open a new file stream by inheriting a given file descriptor `FD'
@@Note that upon success (`return != NULL'), the given `FD'
@@will be `close()'d once `fclose(return)' is called
[[wunused, dos_export_alias("_fdopen"), export_alias("_IO_fdopen")]]
$FILE *fdopen($fd_t fd, [[nonnull]] char const *__restrict modes);

@@Return the underlying file descriptor number used by `STREAM'
[[wunused, dos_export_alias("_fileno"), export_alias("fileno_unlocked")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("fileno_unlocked")]]
$fd_t fileno([[nonnull]] $FILE *__restrict stream);
%#endif /* __USE_POSIX || __USE_DOS */


%
%#ifdef __USE_XOPEN2K8
%[default:section(".text.crt{|.dos}.FILE.locked.access")]
[[wunused, decl_include("<hybrid/typecore.h>")]]
$FILE *fmemopen([[inoutp(len)]] void *mem, $size_t len,
                [[nonnull]] char const *modes);

[[wunused, decl_include("<hybrid/typecore.h>")]]
$FILE *open_memstream(char **bufloc, $size_t *sizeloc);

%[default:section(".text.crt{|.dos}.FILE.locked.read.read")]
%[insert:function(__getdelim = getdelim)]

[[cp_stdio, wunused, alias("getdelim_unlocked"), export_alias("__getdelim")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("getdelim_unlocked")]]
[[requires_function(realloc, fgetc, ungetc)]]
[[decl_include("<hybrid/typecore.h>")]]
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

[[cp_stdio, wunused, alias("getline_unlocked")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("getline_unlocked")]]
[[requires_function(getdelim), decl_include("<hybrid/typecore.h>")]]
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
@@Same as `getchar()', but performs I/O without acquiring a lock to `stdin'
[[cp_stdio, impl_include("<local/stdstreams.h>"), requires_include("<__crt.h>")]]
[[requires(!defined(__NO_STDSTREAMS) && $has_function(fgetc_unlocked))]]
int getchar_unlocked() {
	return fgetc_unlocked(stdin);
}

%[default:section(".text.crt{|.dos}.FILE.unlocked.write.putc")]
@@Same as `putchar()', but performs I/O without acquiring a lock to `stdout'
[[crtbuiltin, requires_include("<__crt.h>")]]
[[cp_stdio, impl_include("<local/stdstreams.h>")]]
[[requires(!defined(__NO_STDSTREAMS) && $has_function(fputc_unlocked))]]
int putchar_unlocked(int ch) {
	return fputc_unlocked(ch, stdout);
}

%[default:section(".text.crt{|.dos}.FILE.locked.utility")]
@@Acquire a lock to `STREAM' and block until doing so succeeds
[[cp, dos_export_alias("_lock_file"), export_alias("_IO_flockfile")]]
void flockfile([[nonnull]] $FILE *__restrict stream);

@@Release a previously acquired lock from `STREAM'
[[dos_export_alias("_unlock_file"), export_alias("_IO_funlockfile")]]
void funlockfile([[nonnull]] $FILE *__restrict stream);

@@Try to acquire a lock to `STREAM'
[[wunused, export_alias("_IO_ftrylockfile")]]
int ftrylockfile([[nonnull]] $FILE *__restrict stream);
%#endif /* __USE_POSIX || __USE_REENTRANT */

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
@@Return the name of the current user (`getpwuid(geteuid())'), storing
@@that name in `S'. When `S' is NULL, a static buffer is used instead
[[guard]]
char *cuserid(char *s); /* TODO: Implement inline */
%#endif /* Use X/Open, but not issue 6.  */




%
%#ifdef __USE_POSIX2
%[default:section(".text.crt{|.dos}.FILE.locked.access")]
@@Open and return a new process I/O stream for executing `COMMAND'
[[cp, wunused, dos_export_alias("_popen"), export_alias("_IO_popen")]]
$FILE *popen([[nonnull]] char const *command,
             [[nonnull]] char const *modes);

@@Close a process I/O file `STREAM'
[[dos_export_alias("_pclose")]]
int pclose([[nonnull]] $FILE *stream);

%#endif /* __USE_POSIX2 */

%
%#if (defined(__USE_MISC) || defined(__USE_DOS) || \
%     (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K)))

%[default:section(".text.crt{|.dos}.FILE.locked.read.getc")]

@@Similar to `getc()', but read 2 bytes
[[cp_stdio, dos_export_alias("_getw")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("getw_unlocked")]]
[[requires_function(fread)]]
[[impl_include("<asm/crt/stdio.h>")]]
int getw([[nonnull]] $FILE *__restrict stream) {
	u16 result;
	return fread(&result, sizeof(result), 1, stream)
	       ? (int)result
	       : (int)EOF;
}

%[default:section(".text.crt{|.dos}.FILE.locked.write.putc")]
@@Similar to `putc()', but write 2 bytes loaded from `W & 0xffff'
[[cp_stdio, dos_export_alias("_putw"), requires_function(fwrite)]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("putw_unlocked")]]
[[impl_include("<asm/crt/stdio.h>")]]
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
@@Alias for `_fcloseall()'
[[stdio_throws, dos_export_alias("_fcloseall")]]
int fcloseall();
%#endif /* __USE_GNU || __USE_DOS */

%
%#ifdef __USE_GNU

[[wunused, section(".text.crt{|.dos}.FILE.locked.access")]]
$FILE *fopencookie(void *__restrict magic_cookie,
                   [[nonnull]] char const *__restrict modes,
                   $cookie_io_functions_t io_funcs);

%[default:section(".text.crt{|.dos}.FILE.unlocked.read.read")]

@@Same as `fgets()', but performs I/O without acquiring a lock to `($FILE *)ARG'
[[cp_stdio, alias("fgets"), wunused, decl_include("<features.h>")]]
[[impl_include("<hybrid/typecore.h>", "<asm/crt/stdio.h>", "<parts/errno.h>")]]
[[requires($has_function(fgetc_unlocked) && $has_function(ungetc_unlocked) && $has_function(ferror_unlocked))]]
char *fgets_unlocked([[outp(min(strlen(return), bufsize))]] char *__restrict buf,
                     __STDC_INT_AS_SIZE_T bufsize, [[nonnull]] $FILE *__restrict stream) {
	$size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
@@pp_ifdef ERANGE@@
		__libc_seterrno(ERANGE);
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

@@Same as `fputs()', but performs I/O without acquiring a lock to `($FILE *)ARG'
[[cp_stdio, alias("fputs"), crtbuiltin, decl_include("<features.h>")]]
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

%[default:section(".text.crt{|.dos}.obstack")]
[[ATTR_LIBC_PRINTF(2, 0)]]
int obstack_vprintf([[nonnull]] struct obstack *__restrict obstack_,
                    [[nonnull]] char const *__restrict format, $va_list args);

[[ATTR_LIBC_PRINTF(2, 3)]]
[[requires_function(obstack_vprintf)]]
int obstack_printf([[nonnull]] struct obstack *__restrict obstack_,
                   [[nonnull]] char const *__restrict format, ...) {
	int result;
	va_list args;
	va_start(args, format);
	result = obstack_vprintf(obstack_, format, args);
	va_end(args);
	return result;
}
%#endif /* __USE_GNU */


%[default:section(".text.crt{|.dos}.FILE.locked.seek.seek")]
%#if defined(__USE_LARGEFILE) || defined(__USE_XOPEN2K)
@@Change the current in-file position of `STREAM'
[[stdio_throws, no_crt_self_import, no_crt_self_export, export_as(CNL_fseeko...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_fseek...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fseeko64...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
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

@@Return the current in-file position of `STREAM'
[[stdio_throws, wunused, no_crt_self_import, no_crt_self_export, export_as(CNL_ftello...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_ftell...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_ftello64...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
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

@@64-bit variant of `tmpfile'
[[cp, alias("tmpfile"), wunused]]
[[largefile64_variant_of(tmpfile)]]
$FILE *tmpfile64();

%[default:section(".text.crt{|.dos}.FILE.locked.seek.seek")]
@@64-bit variant of `fseeko'
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), crt_intern_kos_alias(fseeko)]]
[[stdio_throws, no_crt_self_import, no_crt_self_export, export_as(CNL_fseeko64...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_fseeko64_unlocked...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[                                                                               alias(CNL_fseeko64...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[                                                                               alias(CNL_fseeko64_unlocked...)]]
[[userimpl, requires($has_function(crt_fseeko) || $has_function(crt_fseek))]]
int fseeko64([[nonnull]] $FILE *__restrict stream, $off64_t off, int whence) {
@@pp_if $has_function(crt_fseeko)@@
	return crt_fseeko(stream, (off32_t)off, whence);
@@pp_else@@
	return crt_fseek(stream, (long int)off, whence);
@@pp_endif@@
}

@@64-bit variant of `ftello'
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), crt_intern_kos_alias(ftello)]]
[[stdio_throws, wunused, no_crt_self_import, no_crt_self_export, export_as(CNL_ftello64...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_ftello64_unlocked...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[                                                                               alias(CNL_ftello64...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[                                                                               alias(CNL_ftello64_unlocked...)]]
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

@@64-bit variant of `fopen'
[[cp, wunused, alias("fopen"), largefile64_variant_of(fopen)]]
[[userimpl, requires_function(fopen)]]
$FILE *fopen64([[nonnull]] char const *__restrict filename,
               [[nonnull]] char const *__restrict modes) {
	return fopen(filename, modes);
}

@@64-bit variant of `freopen'
[[cp, largefile64_variant_of(freopen)]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("freopen64_unlocked")]]
[[alias("freopen", "freopen_unlocked", "freopen64_unlocked")]]
[[userimpl, requires_function(freopen)]]
$FILE *freopen64([[nonnull]] char const *__restrict filename,
                 [[nonnull]] char const *__restrict modes,
                 [[nonnull]] $FILE *__restrict stream) {
	return freopen(filename, modes, stream);
}

%[default:section(".text.crt{|.dos}.FILE.locked.seek.pos")]

@@64-bit variant of `fgetpos'
[[decl_include("<bits/types.h>")]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), crt_intern_kos_alias(fgetpos)]]
[[stdio_throws, no_crt_self_import, no_crt_self_export, export_as(CNL_fgetpos64...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fgetpos_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_fgetpos64_unlocked...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fgetpos...)]]
[[                                                                               alias(CNL_fgetpos64...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fgetpos_unlocked...)]]
[[                                                                               alias(CNL_fgetpos64_unlocked...)]]
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

@@64-bit variant of `fsetpos'
[[decl_include("<bits/types.h>")]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), crt_intern_kos_alias(fsetpos)]]
[[stdio_throws, no_crt_self_import, no_crt_self_export, export_as(CNL_fsetpos64...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fsetpos_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_fsetpos64_unlocked...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fsetpos...)]]
[[                                                                               alias(CNL_fsetpos64...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fsetpos_unlocked...)]]
[[                                                                               alias(CNL_fsetpos64_unlocked...)]]
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
@@For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument
[[decl_include("<hybrid/typecore.h>")]]
[[cp_stdio, no_crt_dos_wrapper, cc(__FORMATPRINTER_CC), decl_include("<bits/format-printer.h>")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("file_printer_unlocked")]]
[[alias("file_printer_unlocked"), userimpl, requires_function(fwrite)]]
$ssize_t file_printer([[nonnull]] /*FILE*/ void *arg,
                      [[inp(datalen)]] char const *__restrict data,
                      $size_t datalen) {
	return (ssize_t)fwrite(data, sizeof(char), datalen, ($FILE *)arg);
}

%[default:section(".text.crt{|.dos}.FILE.unlocked.write.write")]
@@Same as `file_printer()', but performs I/O without acquiring a lock to `($FILE *)ARG'
[[decl_include("<hybrid/typecore.h>")]]
[[cp_stdio, no_crt_dos_wrapper, cc(__FORMATPRINTER_CC), decl_include("<bits/format-printer.h>")]]
[[alias("file_printer"), userimpl, requires_function(fwrite_unlocked)]]
$ssize_t file_printer_unlocked([[nonnull]] /*FILE*/ void *arg,
                               [[inp(datalen)]] char const *__restrict data,
                               $size_t datalen) {
	return (ssize_t)fwrite_unlocked(data, sizeof(char), datalen, ($FILE *)arg);
}
%#endif /* __USE_KOS */





%
%#if defined(__USE_GNU) || defined(__USE_SOLARIS)
%[default:section(".text.crt{|.dos}.heap.strdup")]

@@Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR'
[[decl_include("<features.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[ATTR_LIBC_PRINTF(2, 3), impl_include("<hybrid/__assert.h>")]]
[[requires_function(format_aprintf_pack, format_aprintf_printer, free)]]
[[impl_prefix(
#ifndef __format_aprintf_data_defined
#define __format_aprintf_data_defined 1
struct @format_aprintf_data@ {
	char         *@ap_base@;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owend] Buffer */
	__SIZE_TYPE__ @ap_avail@; /* Unused buffer size */
	__SIZE_TYPE__ @ap_used@;  /* Used buffer size */
};
#endif /* !__format_aprintf_data_defined */
), dependency(format_aprintf_printer)]]
__STDC_INT_AS_SSIZE_T vasprintf([[nonnull]] char **__restrict pstr,
                                [[nonnull]] char const *__restrict format,
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

@@Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR'
[[decl_include("<features.h>")]]
[[ATTR_LIBC_PRINTF(2, 3), export_alias("__asprintf")]]
__STDC_INT_AS_SSIZE_T asprintf([[nonnull]] char **__restrict pstr,
                               [[nonnull]] char const *__restrict format, ...)
	%{printf("vasprintf")}

%[insert:function(__asprintf = asprintf)]
%#endif /* __USE_GNU || __USE_SOLARIS */

%{




}
%#ifdef __USE_KOS

%[default:section(".text.crt{|.dos}.FILE.locked.access")]

@@Re-open the given `STREAM' as a file-stream for accessing `FD'
[[if(defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)), preferred_alias("fdreopen64_unlocked")]]
[[if(defined(__USE_STDIO_UNLOCKED)                                ), preferred_alias("fdreopen_unlocked")]]
[[if(defined(__USE_FILE_OFFSET64)                                 ), preferred_alias("fdreopen64")]]
[[cp, alias("fdreopen64", "fdreopen_unlocked", "fdreopen64_unlocked")]]
$FILE *fdreopen($fd_t fd, [[nonnull]] char const *__restrict modes,
                [[nonnull]] $FILE *__restrict stream);


%[default:section(".text.crt{|.dos}.FILE.unlocked.access")]
[[cp, alias("fdreopen"), doc_alias("fdreopen")]]
[[userimpl, requires_function(fdreopen)]]
$FILE *fdreopen_unlocked($fd_t fd, [[nonnull]] char const *__restrict modes,
                         [[nonnull]] $FILE *__restrict stream) {
	return fdreopen(fd, modes, stream);
}

[[cp, alias("freopen64_unlocked", "freopen", "freopen64"), doc_alias("freopen")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("freopen64_unlocked")]]
[[userimpl, requires_function(freopen)]]
$FILE *freopen_unlocked([[nonnull]] char const *__restrict filename,
                        [[nonnull]] char const *__restrict modes,
                        [[nonnull]] $FILE *__restrict stream) {
	return freopen(filename, modes, stream);
}

[[cp, alias("freopen64", "freopen_unlocked", "freopen"), doc_alias("freopen")]]
[[userimpl, requires_function(freopen64)]]
$FILE *freopen64_unlocked([[nonnull]] char const *__restrict filename,
                          [[nonnull]] char const *__restrict modes,
                          [[nonnull]] $FILE *__restrict stream) {
	return freopen64(filename, modes, stream);
}


%[default:section(".text.crt{|.dos}.FILE.unlocked.seek.seek")];

[[stdio_throws, no_crt_self_import, no_crt_self_export, export_as(CNL_fseek_unlocked...)]]
[[                                           alias(CNL_fseek_unlocked...)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
[[                                           alias(CNL_fseek...)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_fseeko64...)]]
[[userimpl, requires_function(fseek)]]
int fseek_unlocked([[nonnull]] $FILE *__restrict stream, long int off, int whence) {
	return fseek(stream, off, whence);
}

[[stdio_throws, wunused, no_crt_self_import, no_crt_self_export, export_as(CNL_ftell_unlocked...)]]
[[                                           alias(CNL_ftell_unlocked...)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
[[                                           alias(CNL_ftell...)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_OFF64_T__), alias(CNL_ftello64...)]]
[[userimpl, requires_function(ftell)]]
long int ftell_unlocked([[nonnull]] $FILE *__restrict stream) {
	return ftell(stream);
}

[[stdio_throws]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fseeko_unlocked...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fseeko64_unlocked...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_fseek...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fseeko64...)]]
[[userimpl, requires_function(fseeko)]]
int fseeko_unlocked([[nonnull]] $FILE *__restrict stream, $off_t off, int whence) {
	return fseeko(stream, off, whence);
}

[[stdio_throws, wunused]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_ftello_unlocked...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_ftello64_unlocked...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_LONG__   ), alias(CNL_ftell...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_ftello64...)]]
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
[[stdio_throws]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fgetpos_unlocked...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fgetpos_unlocked...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fgetpos64_unlocked...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fgetpos...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fgetpos64...)]]
[[userimpl, requires_function(fgetpos), decl_include("<bits/types.h>")]]
int fgetpos_unlocked([[nonnull]] $FILE *__restrict stream,
                     [[nonnull]] $fpos_t *__restrict pos) {
	return fgetpos(stream, pos);
}

[[stdio_throws]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fsetpos_unlocked...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fsetpos_unlocked...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fsetpos64_unlocked...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fsetpos...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fsetpos64...)]]
[[userimpl, requires_function(fsetpos), decl_include("<bits/types.h>")]]
int fsetpos_unlocked([[nonnull]] $FILE *__restrict stream,
                     [[nonnull]] $fpos_t const *__restrict pos) {
	return fsetpos(stream, pos);
}

[[cp_stdio, alias("getw", "_getw")]]
[[section(".text.crt{|.dos}.FILE.unlocked.read.getc")]]
[[requires_function(fread_unlocked)]]
[[impl_include("<asm/crt/stdio.h>")]]
int getw_unlocked([[nonnull]] $FILE *__restrict stream) {
	u16 result;
	return fread_unlocked(&result, sizeof(result), 1, stream)
	       ? (int)(unsigned int)result
	       : (int)EOF;
}

[[cp_stdio, alias("putw", "_putw")]]
[[section(".text.crt{|.dos}.FILE.unlocked.write.putc")]]
[[requires_function(putw)]]
int putw_unlocked(int w, [[nonnull]] $FILE *__restrict stream) {
	u16 c = (u16)w;
	return fwrite_unlocked(&c, sizeof(c), 1, stream)
	       ? w
	       : EOF;
}


[[decl_include("<hybrid/typecore.h>"), no_crt_self_import, no_crt_self_export]]
[[export_alias(CNL_setvbuf_unlocked...), alias(CNL_setvbuf...)]]
[[section(".text.crt{|.dos}.FILE.unlocked.read.utility")]]
[[userimpl, requires_function(setvbuf)]]
int setvbuf_unlocked([[nonnull]] $FILE *__restrict stream,
                     char *__restrict buf, int modes,
                     $size_t bufsize) {
	return setvbuf(stream, buf, modes, bufsize);
}

[[no_crt_self_import, no_crt_self_export]]
[[export_alias(CNL_ungetc_unlocked...), alias(CNL_ungetc...)]]
[[section(".text.crt{|.dos}.FILE.unlocked.read.getc")]]
[[userimpl, requires_function(ungetc)]]
int ungetc_unlocked(int ch, [[nonnull]] $FILE *__restrict stream) {
	return ungetc(ch, stream);
}

[[cp_stdio, wunused, alias("getdelim"), doc_alias("getdelim")]]
[[section(".text.crt{|.dos}.FILE.unlocked.read.read")]]
[[requires_function(realloc, fgetc_unlocked, ungetc_unlocked)]]
[[impl_include("<asm/crt/stdio.h>", "<hybrid/__assert.h>")]]
[[decl_include("<hybrid/typecore.h>")]]
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

[[decl_include("<hybrid/typecore.h>")]]
[[cp_stdio, wunused, alias("getline")]]
[[section(".text.crt{|.dos}.FILE.unlocked.read.read")]]
[[requires_function(getdelim_unlocked)]]
$ssize_t getline_unlocked([[nonnull]] char **__restrict lineptr,
                          [[nonnull]] $size_t *__restrict pcount,
                          [[nonnull]] $FILE *__restrict stream) {
	return getdelim_unlocked(lineptr, pcount, '\n', stream);
}

[[stdio_throws, alias("rewind")]]
[[section(".text.crt{|.dos}.FILE.unlocked.seek.utility")]]
[[userimpl, requires_function(fsetpos_unlocked)]]
void rewind_unlocked([[nonnull]] $FILE *__restrict stream) {
	fsetpos_unlocked(stream, 0);
}

[[wunused, section(".text.crt{|.dos}.io.tty")]]
[[userimpl, requires_function(isatty, fileno)]]
int fisatty([[nonnull]] $FILE *__restrict stream) {
	return isatty(fileno(stream));
}

%{
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else /* __USE_KOS */
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif /* !__USE_KOS */
#endif /* !__PIO_OFFSET */
}

%[define(DEFINE_PIO_OFFSET =
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET   __FS_TYPE(pos)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS */
#define __PIO_OFFSET   __FS_TYPE(off)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS */
#endif /* !__PIO_OFFSET */
)]



@@>> fftruncate(3)
@@Truncate the given file `STREAM' to a length of `LENGTH'
[[cp_stdio, decl_prefix(DEFINE_PIO_OFFSET), no_crt_self_import, no_crt_self_export, export_as(CNL_fftruncate...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fftruncate_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fftruncate64_unlocked...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fftruncate...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fftruncate64...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fftruncate_unlocked...)]]
[[if(                                 __FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fftruncate64_unlocked...)]]
[[section(".text.crt{|.dos}.FILE.locked.utility")]]
[[userimpl, requires_function(ftruncate, fileno)]]
int fftruncate([[nonnull]] $FILE *__restrict stream, __PIO_OFFSET length) {
	int result = -1;
	fd_t fd = fileno(stream);
	if likely(fd >= 0)
		result = ftruncate(fd, length);
	return result;
}

@@>> fftruncate_unlocked(3)
@@Same as `fftruncate()', but don't acquire a lock to the file
[[cp_stdio, decl_prefix(DEFINE_PIO_OFFSET)]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fftruncate_unlocked...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fftruncate_unlocked...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fftruncate64_unlocked...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF32_T__), alias(CNL_fftruncate...)]]
[[if(__FS_SIZEOF(@OFF@) == __SIZEOF_OFF64_T__), alias(CNL_fftruncate64...)]]
[[section(".text.crt{|.dos}.FILE.unlocked.utility")]]
[[userimpl, requires_function(ftruncate, fileno_unlocked)]]
int fftruncate_unlocked([[nonnull]] $FILE *__restrict stream, __PIO_OFFSET length) {
	int result = -1;
	fd_t fd = fileno_unlocked(stream);
	if likely(fd >= 0)
		result = ftruncate(fd, length);
	return result;
}


[[cp_stdio, crtbuiltin, alias("puts"), decl_include("<features.h>")]]
[[section(".text.crt{|.dos}.FILE.unlocked.write.write"), impl_include("<local/stdstreams.h>")]]
[[requires(!defined(__NO_STDSTREAMS) && $has_function(fputs_unlocked))]]
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
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), crt_intern_kos_alias(fseeko_unlocked)]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fseeko64_unlocked...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek_unlocked...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko_unlocked...)]]
[[                                              alias(CNL_fseeko64_unlocked...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_fseek...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fseeko...)]]
[[                                              alias(CNL_fseeko64...)]]
[[section(".text.crt{|.dos}.FILE.unlocked.seek.seek")]]
[[userimpl, requires_function(fseeko64)]]
int fseeko64_unlocked([[nonnull]] $FILE *__restrict stream,
                      $off64_t off, int whence) {
	return fseeko64(stream, off, whence);
}

[[stdio_throws, wunused, decl_include("<bits/types.h>")]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), crt_intern_kos_alias(ftello_unlocked)]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_ftello64_unlocked...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell_unlocked...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello_unlocked...)]]
[[                                              alias(CNL_ftello64_unlocked...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_LONG__   ), alias(CNL_ftell...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_ftello...)]]
[[                                              alias(CNL_ftello64...)]]
[[section(".text.crt{|.dos}.FILE.unlocked.seek.seek")]]
[[userimpl, requires_function(ftello64)]]
$off64_t ftello64_unlocked([[nonnull]] $FILE *__restrict stream) {
	return ftello64(stream);
}

[[stdio_throws]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), crt_intern_kos_alias(fgetpos_unlocked)]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fgetpos64_unlocked...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fgetpos_unlocked...)]]
[[                                              alias(CNL_fgetpos64_unlocked...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fgetpos...)]]
[[                                              alias(CNL_fgetpos64...)]]
[[section(".text.crt{|.dos}.FILE.unlocked.seek.pos")]]
[[userimpl, requires_function(fgetpos64), decl_include("<bits/types.h>")]]
int fgetpos64_unlocked([[nonnull]] $FILE *__restrict stream,
                       [[nonnull]] fpos64_t *__restrict pos) {
	return fgetpos64(stream, pos);
}


[[stdio_throws]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), crt_intern_kos_alias(fsetpos_unlocked)]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fsetpos64_unlocked...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fsetpos_unlocked...)]]
[[                                              alias(CNL_fsetpos64_unlocked...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fsetpos...)]]
[[                                              alias(CNL_fsetpos64...)]]
[[section(".text.crt{|.dos}.FILE.unlocked.seek.pos")]]
[[userimpl, requires_function(fsetpos64), decl_include("<bits/types.h>")]]
int fsetpos64_unlocked([[nonnull]] $FILE *__restrict stream,
                       [[nonnull]] fpos64_t const *__restrict pos) {
	return fsetpos64(stream, pos);
}


@@>> fftruncate64(3)
@@Truncate the given file `STREAM' to a length of `LENGTH'
[[cp_stdio, decl_prefix(DEFINE_PIO_OFFSET)]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), crt_intern_kos_alias(fftruncate)]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fftruncate64...)]]
[[if(defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fftruncate_unlocked...)]]
[[if(defined(__USE_STDIO_UNLOCKED)                                            ), alias(CNL_fftruncate64_unlocked...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fftruncate...)]]
[[                                                                               alias(CNL_fftruncate64...)]]
[[if(                                 __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fftruncate_unlocked...)]]
[[                                                                               alias(CNL_fftruncate64_unlocked...)]]
[[section(".text.crt{|.dos}.FILE.locked.utility")]]
[[userimpl, requires_function(ftruncate64, fileno)]]
int fftruncate64([[nonnull]] $FILE *__restrict stream, __PIO_OFFSET64 length) {
	int result = -1;
	fd_t fd = fileno(stream);
	if likely(fd >= 0)
		result = ftruncate64(fd, length);
	return result;
}

@@>> fftruncate64_unlocked(3)
@@Truncate the given file `STREAM' to a length of `LENGTH'
[[cp_stdio, decl_prefix(DEFINE_PIO_OFFSET)]]
[[if(__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), crt_intern_kos_alias(fftruncate_unlocked)]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_fftruncate64_unlocked...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fftruncate_unlocked...)]]
[[                                              alias(CNL_fftruncate64_unlocked...)]]
[[if(__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), alias(CNL_fftruncate...)]]
[[                                              alias(CNL_fftruncate64...)]]
[[section(".text.crt{|.dos}.FILE.unlocked.utility")]]
[[userimpl, requires_function(ftruncate64, fileno_unlocked)]]
int fftruncate64_unlocked([[nonnull]] $FILE *__restrict stream, __PIO_OFFSET64 length) {
	int result = -1;
	fd_t fd = fileno_unlocked(stream);
	if likely(fd >= 0)
		result = ftruncate64(fd, length);
	return result;
}

%#endif /* __USE_LARGEFILE64 */


%[default:section(".text.crt{|.dos}.FILE.unlocked.write.printf")]

[[decl_include("<features.h>")]]
[[cp_stdio, ATTR_LIBC_PRINTF(2, 0), alias("vfprintf", "vfprintf_s", "_IO_vfprintf")]]
[[requires_dependent_function(file_printer_unlocked)]]
__STDC_INT_AS_SSIZE_T vfprintf_unlocked([[nonnull]] $FILE *__restrict stream,
                                        [[nonnull]] char const *__restrict format,
                                        $va_list args) {
	return (__STDC_INT_AS_SSIZE_T)format_vprintf(&file_printer_unlocked, stream, format, args);
}

[[decl_include("<features.h>")]]
[[cp_stdio, crtbuiltin, ATTR_LIBC_PRINTF(2, 3), dos_export_alias("fprintf_s")]]
__STDC_INT_AS_SSIZE_T fprintf_unlocked([[nonnull]] $FILE *__restrict stream,
                                       [[nonnull]] char const *__restrict format, ...)
	%{printf("vfprintf_unlocked")}

[[decl_include("<features.h>"), requires_include("<__crt.h>")]]
[[cp_stdio, ATTR_LIBC_PRINTF(1, 0), dos_export_alias("vprintf_s")]]
[[impl_include("<local/stdstreams.h>")]]
[[requires(!defined(__NO_STDSTREAMS) && $has_function(vprintf))]]
__STDC_INT_AS_SSIZE_T vprintf_unlocked([[nonnull]] char const *__restrict format,
                                       $va_list args) {
	return vfprintf_unlocked(stdout, format, args);
}

[[decl_include("<features.h>")]]
[[cp_stdio, crtbuiltin, ATTR_LIBC_PRINTF(1, 2), dos_export_alias("printf_s")]]
__STDC_INT_AS_SSIZE_T printf_unlocked([[nonnull]] char const *__restrict format, ...)
	%{printf("vprintf_unlocked")}

%[default:section(".text.crt{|.dos}.FILE.unlocked.read.scanf")]

[[doc_alias("vfscanf")]]
[[cp_stdio, ATTR_LIBC_SCANF(2, 0), wunused]]
[[alias("vfscanf", "__vfscanf", "_vfscanf", "_vfscanf_s", "_IO_vfscanf")]]
[[requires_function(fgetc_unlocked, ungetc_unlocked)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>"), dependency(fgetc_unlocked)]]
[[impl_include("<hybrid/typecore.h>"), impl_prefix(
@@push_namespace(local)@@
@@pp_if !defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_SIZE_T__ != __SIZEOF_INT__@@
__LOCAL_LIBC(@vfscanf_getc_unlocked@) ssize_t
(__FORMATPRINTER_CC vfscanf_getc_unlocked)(void *arg) {
	return (ssize_t)fgetc_unlocked((FILE *)arg);
}
@@pp_endif@@
__LOCAL_LIBC(@vfscanf_ungetc_unlocked@) ssize_t
(__FORMATPRINTER_CC vfscanf_ungetc_unlocked)(void *arg, char32_t ch) {
	return ungetc_unlocked((int)(unsigned int)ch, (FILE *)arg);
}
@@pop_namespace@@
)]]
__STDC_INT_AS_SIZE_T vfscanf_unlocked([[nonnull]] $FILE *__restrict stream,
                                      [[nonnull]] char const *__restrict format,
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



[[decl_include("<features.h>"), requires_include("<__crt.h>")]]
[[impl_include("<local/stdstreams.h>")]]
[[requires(!defined(__NO_STDSTREAMS) && $has_function(vfscanf_unlocked))]]
[[cp_stdio, ATTR_LIBC_SCANF(1, 0), wunused, alias("_vscanf")]]
__STDC_INT_AS_SIZE_T vscanf_unlocked([[nonnull]] char const *__restrict format, $va_list args) {
	return vfscanf_unlocked(stdin, format, args);
}

[[cp_stdio, wunused, ATTR_LIBC_SCANF(2, 3), decl_include("<features.h>")]]
__STDC_INT_AS_SIZE_T fscanf_unlocked([[nonnull]] $FILE *__restrict stream,
                                     [[nonnull]] char const *__restrict format, ...)
	%{printf("vfscanf_unlocked")}

[[cp_stdio, wunused, ATTR_LIBC_SCANF(1, 2), decl_include("<features.h>")]]
__STDC_INT_AS_SIZE_T scanf_unlocked([[nonnull]] char const *__restrict format, ...)
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
 * of my own), since I don't really know where exactly to put them.
 *
 * For now, it makes sense to encapsulate them behind _LARGEFILE64_SOURCE,
 * given that these are the 64-bit variants of fseek() and ftell(), however
 * there may be other _*_SOURCE macros out there that are supposed to do
 * the same (only I can't find them...) */
%[insert:function(fseek64 = fseeko64)]
%[insert:function(ftell64 = ftello64)]
%#endif /* __USE_LARGEFILE64 */




%{

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
typedef __SIZE_TYPE__ rsize_t;
#endif /* !__rsize_t_defined */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __std_FILE_defined
#define __std_FILE_defined 1
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */
#ifndef __FILE_defined
#define __FILE_defined 1
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

[[cp, wunused, section(".text.crt.dos.FILE.locked.access")]]
[[requires_function(fopen)]]
$FILE *_fsopen([[nonnull]] char const *filename,
               [[nonnull]] char const *modes, int sflag) {
	(void)sflag;
	return fopen(filename, modes);
}

%[insert:function(_fdopen = fdopen)]

[[section(".text.crt{|.dos}.application.exit")]]
[[cp_stdio, userimpl, no_crt_self_import, no_crt_self_export, export_as(CNL_flushall...)]]
[[if(defined(__USE_STDIO_UNLOCKED)), alias(CNL_flushall_unlocked...)]]
[[                                   alias(CNL_flushall...)]]
[[                                   alias(CNL_flushall_unlocked...)]]
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
[[cp_stdio, section(".text.crt.dos.FILE.locked.read.read")]]
int _filbuf([[nonnull]] $FILE *__restrict stream);

[[cp_stdio, section(".text.crt.dos.FILE.locked.write.write")]]
int _flsbuf(int ch, [[nonnull]] $FILE *__restrict stream);

%
%[default:section(".text.crt.dos.FILE.utility")];

[[wunused]]
int _getmaxstdio();

int _setmaxstdio(int val);

[[wunused]]
int _get_printf_count_output();

int _set_printf_count_output(int val);

[[wunused]]
$uint32_t _get_output_format();

$uint32_t _set_output_format($uint32_t format);

%[default:section(".text.crt.dos.FILE.locked.read.scanf")];

%[insert:function(_vscanf = vscanf)]

[[decl_include("<features.h>"), requires_function(vscanf)]]
[[cp_stdio, ignore, ATTR_LIBC_SCANF(1, 3), wunused, export_alias("_vscanf_s_l")]]
__STDC_INT_AS_SIZE_T _vscanf_l([[nonnull]] char const *__restrict format,
                               $locale_t locale, $va_list args) {
	(void)locale;
	return vscanf(format, args);
}

[[decl_include("<features.h>"), requires_function(vfscanf)]]
[[cp_stdio, ignore, ATTR_LIBC_SCANF(2, 4), wunused, export_alias("_vfscanf_s_l")]]
__STDC_INT_AS_SIZE_T _vfscanf_l([[nonnull]] $FILE *__restrict stream,
                                [[nonnull]] char const *__restrict format,
                                $locale_t locale, $va_list args) {
	(void)locale;
	return vfscanf(stream, format, args);
}

[[decl_include("<features.h>")]]
[[ignore, ATTR_LIBC_SCANF(2, 4), wunused, export_alias("_vsscanf_s_l")]]
[[requires_function(vsscanf), section(".text.crt.dos.unicode.locale.format.scanf")]]
__STDC_INT_AS_SIZE_T _vsscanf_l([[nonnull]] char const *__restrict input,
                                [[nonnull]] char const *__restrict format,
                                $locale_t locale, $va_list args) {
	(void)locale;
	return vsscanf(input, format, args);
}

[[ignore]] _vscanf_s(*) = vscanf;
[[ignore]] _vscanf_s_l(*) = _vscanf_l;
[[ignore]] _vfscanf(*) = vfscanf;
[[ignore]] _vfscanf_s(*) = vfscanf;
[[ignore]] _vfscanf_s_l(*) = _vfscanf_l;
[[ignore]] _vsscanf(*) = vsscanf;
[[ignore]] _vsscanf_s(*) = vsscanf;
[[ignore]] _vsscanf_s_l(*) = _vsscanf_l;


[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[ignore, export_alias("_vsnscanf_s")]]
[[section(".text.crt.dos.unicode.static.format.scanf")]]
[[dependency(unicode_readutf8_n, unicode_readutf8_rev)]]
[[impl_include("<asm/crt/stdio.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_prefix(
@@push_namespace(local)@@
struct __vsnscanf_data {
	char const *__ptr;
	char const *__end;
};
__LOCAL_LIBC(@vsnscanf_getc@) __SSIZE_TYPE__
(__FORMATPRINTER_CC __vsnscanf_getc)(void *__arg) {
	__CHAR32_TYPE__ __result;
	__result = unicode_readutf8_n(&((struct __vsnscanf_data *)__arg)->__ptr,
	                              ((struct __vsnscanf_data *)__arg)->__end);
	return __result ? __result : __EOF;
}
__LOCAL_LIBC(@vsnscanf_ungetc@) __SSIZE_TYPE__
(__FORMATPRINTER_CC __vsnscanf_ungetc)(void *__arg, __CHAR32_TYPE__ __UNUSED(__ch)) {
	unicode_readutf8_rev(&((struct __vsnscanf_data *)__arg)->__ptr);
	return 0;
}
@@pop_namespace@@
), wunused, ATTR_LIBC_SCANF(3, 4)]]
__STDC_INT_AS_SIZE_T _vsnscanf([[inp(inputlen)]] char const *__restrict input, $size_t inputlen,
                               [[nonnull]] char const *__restrict format, $va_list args) {
	struct __NAMESPACE_LOCAL_SYM __vsnscanf_data data;
	data.__ptr = input;
	data.__end = input + inputlen;
	return format_vscanf(&__NAMESPACE_LOCAL_SYM __vsnscanf_getc,
	                     &__NAMESPACE_LOCAL_SYM __vsnscanf_ungetc,
	                     (void *)&data, format, args);
}

[[ignore]] _vsnscanf_s(*) = _vsnscanf;

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[ignore, ATTR_LIBC_SCANF(3, 5), export_alias("_vsnscanf_s_l")]]
[[section(".text.crt.dos.unicode.locale.format.scanf")]]
[[requires_function(_vsnscanf)]]
__STDC_INT_AS_SIZE_T _vsnscanf_l([[inp(inputlen)]] char const *__restrict input, $size_t inputlen,
                                 [[nonnull]] char const *__restrict format, $locale_t locale, $va_list args) {
	(void)locale;
	return _vsnscanf(input, inputlen, format, args);
}
[[ignore]] _vsnscanf_s_l(*) = _vsnscanf_l;


%
[[decl_include("<features.h>")]]
[[cp_stdio, ATTR_LIBC_SCANF(1, 3), export_alias("_scanf_s_l")]]
[[section(".text.crt.dos.FILE.locked.read.scanf")]]
__STDC_INT_AS_SIZE_T _scanf_l([[nonnull]] char const *__restrict format,
                              $locale_t locale, ...)
	%{printf("_vscanf_l")}

[[decl_include("<features.h>")]]
[[cp_stdio, ATTR_LIBC_SCANF(2, 4), export_alias("_fscanf_s_l")]]
[[section(".text.crt.dos.FILE.locked.read.scanf")]]
__STDC_INT_AS_SIZE_T _fscanf_l([[nonnull]] $FILE *__restrict stream,
                               [[nonnull]] char const *__restrict format, $locale_t locale, ...)
	%{printf("_vfscanf_l")}


[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt.dos.unicode.static.format.scanf")]]
[[ATTR_LIBC_SCANF(3, 4), export_alias(_snscanf_s)]]
__STDC_INT_AS_SIZE_T _snscanf([[inp(inputlen)]] char const *__restrict input, $size_t inputlen,
                              [[nonnull]] char const *__restrict format, ...)
	%{printf("_vsnscanf")}

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt.dos.unicode.locale.format.scanf")]]
[[ATTR_LIBC_SCANF(3, 5), export_alias("_snscanf_s_l")]]
__STDC_INT_AS_SIZE_T _snscanf_l([[inp(inputlen)]] char const *__restrict input, $size_t inputlen,
                                [[nonnull]] char const *__restrict format, $locale_t locale, ...)
	%{printf("_vsnscanf_l")}

[[decl_include("<features.h>")]]
[[cp_stdio, ATTR_LIBC_SCANF(1, 3), no_crt_impl]]
__STDC_INT_AS_SIZE_T _scanf_s_l([[nonnull]] char const *__restrict format,
                                $locale_t locale, ...)
	%{printf("_vscanf_s_l")}

[[decl_include("<features.h>")]]
[[cp_stdio, ATTR_LIBC_SCANF(2, 4), no_crt_impl]]
__STDC_INT_AS_SIZE_T  _sscanf_s_l([[nonnull]] char const *__restrict input,
                                  [[nonnull]] char const *__restrict format,
                                  $locale_t locale, ...)
	%{printf("_vsscanf_s_l")}

[[decl_include("<features.h>")]]
[[cp_stdio, ATTR_LIBC_SCANF(2, 4), no_crt_impl]]
__STDC_INT_AS_SIZE_T _fscanf_s_l([[nonnull]] $FILE *__restrict stream,
                                 [[nonnull]] char const *__restrict format,
                                 $locale_t locale, ...)
	%{printf("_vfscanf_s_l")}

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[ATTR_LIBC_SCANF(3, 4), no_crt_impl]]
__STDC_INT_AS_SIZE_T _snscanf_s([[inp(inputlen)]] char const *__restrict input, $size_t inputlen,
                                [[nonnull]] char const *__restrict format, ...)
	%{printf("_vsnscanf_s")}

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[ATTR_LIBC_SCANF(3, 5), no_crt_impl]]
__STDC_INT_AS_SIZE_T _snscanf_s_l([[inp(inputlen)]] char const *__restrict input, $size_t inputlen,
                                  [[nonnull]] char const *__restrict format, $locale_t locale, ...)
	%{printf("_vsnscanf_s_l")}

%
[[decl_include("<features.h>"), ATTR_LIBC_PRINTF(2, 0)]]
[[section(".text.crt.dos.unicode.locale.format.printf")]]
__STDC_INT_AS_SIZE_T _vsprintf_l([[outp(return)]] char *__restrict buf,
                                 [[nonnull]] char const *__restrict format,
                                 $locale_t locale, $va_list args) {
	(void)locale;
	return vsprintf(buf, format, args);
}

_vsprintf_s_l(*) = _vsnprintf_l;

[[decl_include("<features.h>", "<hybrid/typecore.h>"), ATTR_LIBC_PRINTF_P(3, 0)]]
[[section(".text.crt.dos.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T _vsprintf_p([[outp_opt(min(return, bufsize))]] char *__restrict buf, $size_t bufsize,
                                 [[nonnull]] char const *__restrict format, $va_list args) {
	(void)buf;
	(void)bufsize;
	(void)format;
	(void)args;
	/* TODO */
	__COMPILER_IMPURE();
	return 0;
}

[[decl_include("<features.h>", "<hybrid/typecore.h>"), ATTR_LIBC_PRINTF_P(3, 0)]]
[[section(".text.crt.dos.unicode.locale.format.printf")]]
__STDC_INT_AS_SIZE_T _vsprintf_p_l([[outp_opt(min(return, bufsize))]] char *__restrict buf, $size_t bufsize,
                                   [[nonnull]] char const *__restrict format, $locale_t locale, $va_list args) {
	(void)locale;
	return _vsprintf_p(buf, bufsize, format, args);
}

%
%[default:section(".text.crt.dos.unicode.locale.format.printf")]

[[decl_include("<features.h>"), ATTR_LIBC_PRINTF(2, 4)]]
__STDC_INT_AS_SIZE_T _sprintf_l([[outp(return)]] char *__restrict buf,
                                [[nonnull]] char const *__restrict format,
                                $locale_t locale, ...)
	%{printf("_vsprintf_l")}

[[decl_include("<features.h>", "<hybrid/typecore.h>"), ATTR_LIBC_PRINTF(3, 5)]]
__STDC_INT_AS_SIZE_T _sprintf_s_l([[outp_opt(min(return, bufsize))]] char *__restrict buf, $size_t bufsize,
                                  [[nonnull]] char const *__restrict format, $locale_t locale, ...)
	%{printf("_vsprintf_s_l")}

[[decl_include("<features.h>", "<hybrid/typecore.h>"), ATTR_LIBC_PRINTF_P(3, 4)]]
__STDC_INT_AS_SIZE_T _sprintf_p([[outp_opt(min(return, bufsize))]] char *__restrict buf, $size_t bufsize,
                                [[nonnull]] char const *__restrict format, ...)
	%{printf("_vsprintf_p")}

[[decl_include("<features.h>", "<hybrid/typecore.h>"), ATTR_LIBC_PRINTF_P(3, 5)]]
__STDC_INT_AS_SIZE_T _sprintf_p_l([[outp_opt(min(return, bufsize))]] char *__restrict buf, $size_t bufsize,
                                  [[nonnull]] char const *__restrict format, $locale_t locale, ...)
	%{printf("_vsprintf_p_l")}

%
[[decl_include("<features.h>"), wunused, ATTR_LIBC_PRINTF(1, 0)]]
[[section(".text.crt.dos.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T _vscprintf([[nonnull]] char const *__restrict format, $va_list args) {
	return vsnprintf(NULL, 0, format, args);
}

[[decl_include("<features.h>"), wunused, ATTR_LIBC_PRINTF(1, 2)]]
[[section(".text.crt.dos.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T _scprintf([[nonnull]] char const *__restrict format, ...)
	%{printf("_vscprintf")}

%
[[decl_include("<features.h>"), wunused, ATTR_LIBC_PRINTF(1, 0)]]
[[section(".text.crt.dos.unicode.locale.format.printf")]]
__STDC_INT_AS_SIZE_T _vscprintf_l([[nonnull]] char const *__restrict format,
                                  $locale_t locale, $va_list args) {
	(void)locale;
	return _vscprintf(format, args);
}


[[decl_include("<features.h>"), wunused, ATTR_LIBC_PRINTF_P(1, 0)]]
[[section(".text.crt.dos.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T _vscprintf_p([[nonnull]] char const *__restrict format, $va_list args) {
	(void)format;
	(void)args;
	/* TODO */
	__COMPILER_IMPURE();
	return 0;
}

[[decl_include("<features.h>"), wunused, ATTR_LIBC_PRINTF_P(1, 0)]]
[[section(".text.crt.dos.unicode.locale.format.printf")]]
__STDC_INT_AS_SIZE_T _vscprintf_p_l([[nonnull]] char const *__restrict format,
                                    $locale_t locale, $va_list args) {
	(void)locale;
	return _vscprintf_p(format, args);
}

[[decl_include("<features.h>"), wunused, ATTR_LIBC_PRINTF(1, 3)]]
[[section(".text.crt.dos.unicode.locale.format.printf")]]
__STDC_INT_AS_SIZE_T _scprintf_l([[nonnull]] char const *__restrict format,
                                 $locale_t locale, ...)
	%{printf("_vscprintf_l")}

[[decl_include("<features.h>"), wunused, ATTR_LIBC_PRINTF_P(1, 2)]]
[[section(".text.crt.dos.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T _scprintf_p([[nonnull]] char const *__restrict format, ...)
	%{printf("_vscprintf_p")}

[[decl_include("<features.h>"), wunused, ATTR_LIBC_PRINTF_P(1, 3)]]
[[section(".text.crt.dos.unicode.locale.format.printf")]]
__STDC_INT_AS_SIZE_T _scprintf_p_l([[nonnull]] char const *__restrict format,
                                   $locale_t locale, ...)
	%{printf("_vscprintf_p_l")}

%
@@WARNING: This function returns the number of written character. - Not the required buffer size!
[[decl_include("<features.h>", "<hybrid/typecore.h>"), ATTR_LIBC_PRINTF(3, 0)]]
[[section(".text.crt.dos.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T _vsnprintf([[outp_opt(min(return, bufsize))]] char *__restrict buf, $size_t bufsize,
                                [[nonnull]] char const *__restrict format, $va_list args) {
	__STDC_INT_AS_SIZE_T result;
	result = vsnprintf(buf, bufsize, format, args);
	if (result > bufsize)
		result = bufsize;
	return result;
}

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[ATTR_LIBC_PRINTF(3, 0), export_alias("_vsprintf_s_l")]]
[[section(".text.crt.dos.unicode.locale.format.printf")]]
__STDC_INT_AS_SIZE_T _vsnprintf_l([[outp_opt(min(return, bufsize))]] char *__restrict buf, $size_t bufsize,
                                  [[nonnull]] char const *__restrict format, $locale_t locale, $va_list args) {
	(void)locale;
	return _vsnprintf(buf, bufsize, format, args);
}

_vsnprintf_c(*) = _vsnprintf;
_vsnprintf_c_l(*) = _vsnprintf_l;

[[decl_include("<features.h>", "<hybrid/typecore.h>"), ATTR_LIBC_PRINTF(4, 0)]]
[[section(".text.crt.dos.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T _vsnprintf_s([[outp_opt(min(return, bufsize, buflen))]] char *__restrict buf,
                                  $size_t bufsize, $size_t buflen,
                                  [[nonnull]] char const *__restrict format, $va_list args) {
	(void)buflen;
	return _vsnprintf(buf, bufsize, format, args);
}

[[decl_include("<features.h>", "<hybrid/typecore.h>"), ATTR_LIBC_PRINTF(4, 0)]]
[[section(".text.crt.dos.unicode.locale.format.printf")]]
__STDC_INT_AS_SIZE_T _vsnprintf_s_l([[outp_opt(min(return, bufsize, buflen))]] char *__restrict buf,
                                    $size_t bufsize, $size_t buflen,
                                    [[nonnull]] char const *__restrict format, $locale_t locale, $va_list args) {
	(void)buflen;
	(void)locale;
	return _vsnprintf(buf, bufsize, format, args);
}

[[decl_include("<features.h>", "<hybrid/typecore.h>"), ATTR_LIBC_PRINTF(3, 4)]]
[[section(".text.crt.dos.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T _snprintf([[outp_opt(min(return, buf, bufsize))]] char *__restrict buf,
                               $size_t bufsize, [[nonnull]] char const *__restrict format, ...)
	%{printf("_vsnprintf")}

[[decl_include("<features.h>", "<hybrid/typecore.h>"), ATTR_LIBC_PRINTF(3, 5)]]
[[section(".text.crt.dos.unicode.locale.format.printf")]]
__STDC_INT_AS_SIZE_T _snprintf_l([[outp_opt(min(return, buf, bufsize))]] char *__restrict buf, $size_t bufsize,
                                 [[nonnull]] char const *__restrict format, $locale_t locale, ...)
	%{printf("_vsnprintf_l")}

[[decl_include("<features.h>", "<hybrid/typecore.h>"), ATTR_LIBC_PRINTF(3, 4)]]
[[section(".text.crt.dos.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T _snprintf_c([[outp_opt(min(return, buf, bufsize))]] char *__restrict buf, $size_t bufsize,
                                 [[nonnull]] char const *__restrict format, ...)
	%{printf("_vsnprintf_c")}

[[decl_include("<features.h>", "<hybrid/typecore.h>"), ATTR_LIBC_PRINTF(3, 5)]]
[[section(".text.crt.dos.unicode.locale.format.printf")]]
__STDC_INT_AS_SIZE_T _snprintf_c_l([[outp_opt(min(return, buf, bufsize))]] char *__restrict buf, $size_t bufsize,
                                   [[nonnull]] char const *__restrict format, $locale_t locale, ...)
	%{printf("_vsnprintf_c_l")}

[[decl_include("<features.h>", "<hybrid/typecore.h>"), ATTR_LIBC_PRINTF(4, 5)]]
[[section(".text.crt.dos.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T _snprintf_s([[outp_opt(min(return, bufsize, buflen))]] char *__restrict buf, $size_t bufsize,
                                 $size_t buflen, [[nonnull]] char const *__restrict format, ...)
	%{printf("_vsnprintf_s")}

[[decl_include("<features.h>", "<hybrid/typecore.h>"), ATTR_LIBC_PRINTF(4, 6)]]
[[section(".text.crt.dos.unicode.locale.format.printf")]]
__STDC_INT_AS_SIZE_T _snprintf_s_l([[outp_opt(min(return, bufsize, buflen))]] char *__restrict buf, $size_t bufsize,
                                   $size_t buflen, [[nonnull]] char const *__restrict format, $locale_t locale, ...)
	%{printf("_vsnprintf_s_l")}

%
%[default:section(".text.crt.dos.unicode.locale.format.printf")];
[[decl_include("<features.h>"), requires_function(vprintf)]]
[[cp_stdio, ATTR_LIBC_PRINTF(1, 0), export_alias("_vprintf_s_l")]]
__STDC_INT_AS_SIZE_T _vprintf_l([[nonnull]] char const *__restrict format,
                                $locale_t locale, $va_list args) {
	(void)locale;
	return vprintf(format, args);
}

_vprintf_s_l(*) = _vprintf_l;

%[default:section(".text.crt.dos.unicode.static.format.printf")];

[[decl_include("<features.h>")]]
[[cp_stdio, ATTR_LIBC_PRINTF_P(1, 0), impl_include("<local/stdstreams.h>")]]
[[requires(!defined(__NO_STDSTREAMS) && $has_function(_vfprintf_p))]]
__STDC_INT_AS_SIZE_T _vprintf_p([[nonnull]] char const *__restrict format, $va_list args) {
	return _vfprintf_p(stdout, format, args);
}

%[default:section(".text.crt.dos.unicode.locale.format.printf")];

[[decl_include("<features.h>")]]
[[cp_stdio, ATTR_LIBC_PRINTF_P(1, 0), requires_function(_vprintf_p)]]
__STDC_INT_AS_SIZE_T _vprintf_p_l([[nonnull]] char const *__restrict format,
                                  $locale_t locale, $va_list args) {
	(void)locale;
	return _vprintf_p(format, args);
}

[[decl_include("<features.h>")]]
[[cp_stdio, ATTR_LIBC_PRINTF(1, 3), section(".text.crt.dos.unicode.locale.format.printf")]]
__STDC_INT_AS_SIZE_T _printf_l([[nonnull]] char const *__restrict format, $locale_t locale, ...)
	%{printf("_vprintf_l")}

[[decl_include("<features.h>")]]
[[cp_stdio, ATTR_LIBC_PRINTF(1, 3), section(".text.crt.dos.unicode.locale.format.printf")]]
__STDC_INT_AS_SIZE_T _printf_s_l([[nonnull]] char const *__restrict format, $locale_t locale, ...)
	%{printf("_vprintf_s_l")}

[[decl_include("<features.h>")]]
[[cp_stdio, ATTR_LIBC_PRINTF_P(1, 2), section(".text.crt.dos.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T _printf_p([[nonnull]] char const *__restrict format, ...)
	%{printf("_vprintf_p")}

[[decl_include("<features.h>")]]
[[cp_stdio, ATTR_LIBC_PRINTF_P(1, 3), section(".text.crt.dos.unicode.locale.format.printf")]]
__STDC_INT_AS_SIZE_T _printf_p_l([[nonnull]] char const *__restrict format, $locale_t locale, ...)
	%{printf("_vprintf_p_l")}

%
[[decl_include("<features.h>"), requires_function(vfprintf)]]
[[cp_stdio, ATTR_LIBC_PRINTF(2, 0), export_alias("_vfprintf_s_l")]]
[[section(".text.crt.dos.unicode.locale.format.printf")]]
__STDC_INT_AS_SIZE_T _vfprintf_l([[nonnull]] $FILE *__restrict stream,
                                 [[nonnull]] char const *__restrict format,
                                 $locale_t locale, $va_list args) {
	(void)locale;
	return vfprintf(stream, format, args);
}

_vfprintf_s_l(*) = _vfprintf_l;

[[decl_include("<features.h>")]]
[[cp_stdio, ATTR_LIBC_PRINTF_P(2, 0), requires_function(fwrite)]]
[[section(".text.crt.dos.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T _vfprintf_p([[nonnull]] $FILE *__restrict stream,
                                 [[nonnull]] char const *__restrict format,
                                 $va_list args) {
	(void)stream;
	(void)format;
	(void)args;
	/* TODO */
	__COMPILER_IMPURE();
	return 0;
}

[[decl_include("<features.h>")]]
[[section(".text.crt.dos.unicode.locale.format.printf")]]
[[cp_stdio, ATTR_LIBC_PRINTF_P(2, 0), requires_function(_vfprintf_p)]]
__STDC_INT_AS_SIZE_T _vfprintf_p_l([[nonnull]] $FILE *__restrict stream,
                                   [[nonnull]] char const *__restrict format,
                                   $locale_t locale, $va_list args) {
	(void)locale;
	return _vfprintf_p(stream, format, args);
}

[[cp_stdio, ATTR_LIBC_PRINTF(2, 4), decl_include("<features.h>")]]
[[section(".text.crt.dos.unicode.locale.format.printf")]]
__STDC_INT_AS_SIZE_T _fprintf_l([[nonnull]] $FILE *__restrict stream,
                                [[nonnull]] char const *__restrict format,
                                $locale_t locale, ...)
	%{printf("_vfprintf_l")}

[[decl_include("<features.h>")]]
[[cp_stdio, ATTR_LIBC_PRINTF(2, 4)]]
[[section(".text.crt.dos.unicode.locale.format.printf")]]
__STDC_INT_AS_SIZE_T _fprintf_s_l([[nonnull]] $FILE *__restrict stream,
                                  [[nonnull]] char const *__restrict format,
                                  $locale_t locale, ...)
	%{printf("_vfprintf_s_l")}

[[cp_stdio, ATTR_LIBC_PRINTF_P(2, 3), decl_include("<features.h>")]]
[[section(".text.crt.dos.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T _fprintf_p([[nonnull]] $FILE *__restrict stream,
                                [[nonnull]] char const *__restrict format, ...)
	%{printf("_vfprintf_p")}

[[cp_stdio, ATTR_LIBC_PRINTF_P(2, 4), decl_include("<features.h>")]]
[[section(".text.crt.dos.unicode.locale.format.printf")]]
__STDC_INT_AS_SIZE_T _fprintf_p_l([[nonnull]] $FILE *__restrict stream,
                                  [[nonnull]] char const *__restrict format,
                                  $locale_t locale, ...)
	%{printf("_vfprintf_p_l")}

%
%#ifdef __USE_DOS_SLIB
[[cp, section(".text.crt.dos.FILE.locked.access")]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<parts/errno.h>")]]
[[requires_function(fopen64)]]
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

[[cp, section(".text.crt.dos.FILE.locked.access")]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<parts/errno.h>")]]
[[requires_function(freopen)]]
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

[[section(".text.crt.dos.fs.utility")]]
[[decl_include("<hybrid/typecore.h>")]]
[[impl_include("<parts/errno.h>")]]
[[requires_function(tmpnam)]]
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
	if unlikely(!tmpnam(buf)) {
@@pp_ifdef __libc_geterrno@@
		return __libc_geterrno();
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	return EOK;
}

%
[[decl_include("<bits/types.h>")]]
[[section(".text.crt.dos.FILE.locked.utility")]]
[[impl_include("<parts/errno.h>")]]
[[requires_function(clearerr)]]
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

[[decl_include("<bits/types.h>")]]
[[cp, impl_include("<parts/errno.h>")]]
[[requires_function(tmpfile64)]]
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

[[requires($has_function(fread))]]
[[cp, wunused, impl_include("<parts/errno.h>", "<hybrid/__overflow.h>")]]
[[section(".text.crt.dos.FILE.locked.read.read")]]
[[decl_include("<hybrid/typecore.h>")]]
$size_t fread_s([[outp(min(return * elemsize, elemcount * elemsize, bufsize))]] void *__restrict buf,
                $size_t bufsize, $size_t elemsize, $size_t elemcount,
                [[nonnull]] $FILE *__restrict stream) {
	size_t reqbuf;
	if (__hybrid_overflow_umul(elemsize, elemcount, &reqbuf) ||
	    reqbuf > bufsize) {
@@pp_ifdef ERANGE@@
		__libc_seterrno(ERANGE);
@@pp_endif@@
		return 0;
	}
	if unlikely(!stream || !buf) {
@@pp_ifdef EINVAL@@
		__libc_seterrno(EINVAL);
@@pp_endif@@
		return 0;
	}
	return fread(buf, elemsize, elemcount, stream);
}

%[default:section(".text.crt.dos.FILE.locked.read.read")];
[[cp, wunused, requires_include("<__crt.h>")]]
[[impl_include("<local/stdstreams.h>", "<parts/errno.h>")]]
[[decl_include("<hybrid/typecore.h>")]]
[[requires(!defined(__NO_STDSTREAMS) && $has_function(fgets))]]
char *gets_s([[outp(min(strlen(return), bufsize))]] char *__restrict buf, rsize_t bufsize) {
	if unlikely(!buf) {
@@pp_ifdef EINVAL@@
		__libc_seterrno(EINVAL);
@@pp_endif@@
		return NULL;
	}
	return fgets(buf, (__STDC_INT_AS_SIZE_T)(unsigned int)bufsize, stdin);
}

%[insert:function(printf_s = printf)]
%[insert:function(vprintf_s = vprintf)]
%[insert:function(fprintf_s = fprintf)]
%[insert:function(vfprintf_s = vfprintf)]
%[insert:function(sprintf_s = snprintf)]   /* XXX: This binding probably isn't correct... */
%[insert:function(vsprintf_s = vsnprintf)] /* XXX: This binding probably isn't correct... */
%[insert:function(fscanf_s = fscanf)]
%[insert:function(vfscanf_s = vfscanf)]
%[insert:function(scanf_s = scanf)]
%[insert:function(vscanf_s = vscanf)]
%[insert:function(sscanf_s = sscanf)]
%[insert:function(vsscanf_s = vsscanf)]

[[decl_include("<features.h>"), ATTR_LIBC_PRINTF(4, 0)]]
__STDC_INT_AS_SIZE_T vsnprintf_s([[outp_opt(min(return, buflen, bufsize))]] char *__restrict buf,
                                 $size_t bufsize, $size_t buflen,
                                 [[nonnull]] char const *__restrict format,
                                 $va_list args) {
	return vsnprintf(buf, buflen < bufsize ? buflen : bufsize, format, args);
}

%#endif /* __USE_DOS_SLIB */

%
[[section(".text.crt.dos.errno.utility")]]
[[cp_stdio, wchar, ATTR_COLD, guard("_CRT_WPERROR_DEFINED")]]
[[requires_include("<__crt.h>", "<parts/errno.h>")]]
[[impl_include("<local/stdstreams.h>", "<parts/errno.h>")]]
[[requires(!defined(__NO_STDSTREAMS) && defined(__libc_geterrno) && $has_function(fprintf) && $has_function(strerror))]]
[[decl_include("<hybrid/typecore.h>")]]
void _wperror($wchar_t const *__restrict message) {
	char const *enodesc;
	enodesc = strerror(__libc_geterrno());
	if (message) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
		fprintf(stderr, "%I16s: %s\n", message, enodesc);
@@pp_else@@
		fprintf(stderr, "%I32s: %s\n", message, enodesc);
@@pp_endif@@
	} else {
		fprintf(stderr, "%s\n",
		        enodesc);
	}
}

%
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

%[default:section(".text.crt.dos.FILE.unlocked.read.read")]

[[cp_stdio, wunused, requires_function(fread_unlocked)]]
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


%#ifndef _WSTDIO_DEFINED
%#define _WSTDIO_DEFINED 1

%{
#ifndef WEOF
#define WEOF __WEOF
#endif /* !WEOF */

/* Define 'wchar_t' */
#ifndef __wchar_t_defined
#define __wchar_t_defined 1
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */
}

%[insert:extern(fgetwc)]
%[insert:extern(fputwc)]
%[insert:guarded_function(getwc = fgetwc)]
%[insert:extern(getwchar)]
%[insert:guarded_function(putwc = fputwc)]
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
%[insert:guarded_function(vswprintf_s = vswprintf)]
%[insert:guarded_function(swprintf_s = swprintf)]
%[insert:guarded_function(vfwprintf_s = vfwprintf)]
%[insert:guarded_function(fwprintf_s = fwprintf)]
%[insert:guarded_function(vwprintf_s = vwprintf)]
%[insert:guarded_function(wprintf_s = wprintf)]
%[insert:guarded_function(vswscanf_s = vswscanf)]
%[insert:guarded_function(swscanf_s = swscanf)]
%[insert:guarded_function(vfwscanf_s = vfwscanf)]
%[insert:guarded_function(fwscanf_s = fwscanf)]
%[insert:guarded_function(vwscanf_s = vwscanf)]
%[insert:guarded_function(wscanf_s = wscanf)]
%#endif /* __USE_DOS_SLIB */
%[insert:extern(_vscwprintf)]
%[insert:extern(_scwprintf)]
%[insert:extern(_vscwprintf_p)]
%[insert:extern(_scwprintf_p)]
%[insert:extern(_vscwprintf_l)]
%[insert:extern(_scwprintf_l)]
%[insert:extern(_vscwprintf_p_l)]
%[insert:extern(_scwprintf_p_l)]
%[insert:guarded_function(_vswprintf_c = vswprintf)]
%[insert:guarded_function(_swprintf_c = swprintf)]
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
%[insert:guarded_function(_fwscanf_s_l = _fwscanf_l)]
%[insert:extern(_swscanf_l)]
%[insert:guarded_function(_swscanf_s_l = _swscanf_l)]
%[insert:extern(_snwscanf)]
%[insert:extern(_snwscanf_l)]
%[insert:guarded_function(_snwscanf_s = _snwscanf)]
%[insert:extern(_snwscanf_s_l)]
%[insert:extern(_wscanf_l)]
%[insert:guarded_function(_wscanf_s_l = _wscanf_l)]
%[insert:extern(_wfsopen)]
%[insert:extern(_wfdopen)]
%[insert:extern(_wfopen_s)]
%[insert:extern(_wfreopen_s)]
%[insert:guarded_function(_wfopen = wfopen)]
%[insert:guarded_function(_wfreopen = wfreopen)]
%[insert:guarded_function(_fgetwchar = getwchar)]
%[insert:guarded_function(_fputwchar = putwchar)]
%[insert:extern(_getws_s)]
%[insert:extern(_putws)]
%[insert:extern(_wtempnam)]
%[insert:function(_wperror = _wperror, guardName: "_CRT_WPERROR_DEFINED")]
%[insert:function(_wperror = _wperror, guardName: "_CRT_WPERROR_DEFINED")]
%[insert:guarded_function(_wpopen = wpopen)]
%[insert:guarded_function(_wremove = wremove)]
%[insert:extern(_wtmpnam_s)]
%[insert:guarded_function(_fgetwc_nolock = fgetwc_unlocked)]
%[insert:guarded_function(_fputwc_nolock = fputwc_unlocked)]
%[insert:guarded_function(_ungetwc_nolock = ungetwc_unlocked)]
%[insert:guarded_function(_getwc_nolock = fgetwc_unlocked)]
%[insert:guarded_function(_putwc_nolock = fputwc_unlocked)]
%#endif /* !_WSTDIO_DEFINED */


%#endif /* __CC__ */
%#endif /* __USE_DOS */
%



%{

#if ((defined(__USE_XOPEN) && !defined(__USE_XOPEN2K) && !defined(__USE_GNU)) || defined(__USE_SOLARIS))
#include <getopt.h>
#endif /* (__USE_XOPEN && !__USE_XOPEN2K && !__USE_GNU) || __USE_SOLARIS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STDIO_H)
#include <parts/uchar/stdio.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_STDIO_H */
#endif /* __USE_UTF */

}

