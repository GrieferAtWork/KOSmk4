/* HASH CRC-32:0x83617ce5 */
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
#ifndef __local_fgetspnam_r_defined
#define __local_fgetspnam_r_defined
#include <__crt.h>
#include <features.h>
#include <bits/crt/stdio.h>
#include <bits/types.h>
#if (defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE___ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)) && (defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || (defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE___fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)))) && (defined(__CRT_HAVE_fparseln) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && (defined(__CRT_HAVE_feof) || defined(__CRT_HAVE__IO_feof) || defined(__CRT_HAVE_feof_unlocked))
#include <bits/crt/db/spwd.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_feof_defined
#define __local___localdep_feof_defined
#if defined(__CRT_HAVE_feof_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__localdep_feof,(__FILE __KOS_FIXED_CONST *__restrict __stream),feof_unlocked,(__stream))
#elif defined(__CRT_HAVE_feof)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__localdep_feof,(__FILE __KOS_FIXED_CONST *__restrict __stream),feof,(__stream))
#elif defined(__CRT_HAVE__IO_feof)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__localdep_feof,(__FILE __KOS_FIXED_CONST *__restrict __stream),_IO_feof,(__stream))
#elif defined(__CRT_HAVE_feof_unlocked)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__localdep_feof,(__FILE __KOS_FIXED_CONST *__restrict __stream),feof_unlocked,(__stream))
#else /* ... */
#undef __local___localdep_feof_defined
#endif /* !... */
#endif /* !__local___localdep_feof_defined */
#ifndef __local___localdep_fgetpos64_defined
#define __local___localdep_fgetpos64_defined
#if defined(__CRT_HAVE_fgetpos_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2),int,__NOTHROW_CB_NCX,__localdep_fgetpos64,(__FILE *__restrict __stream, __fpos64_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2),int,__NOTHROW_CB_NCX,__localdep_fgetpos64,(__FILE *__restrict __stream, __fpos64_t *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2),int,__NOTHROW_CB_NCX,__localdep_fgetpos64,(__FILE *__restrict __stream, __fpos64_t *__restrict __pos),fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2),int,__NOTHROW_CB_NCX,__localdep_fgetpos64,(__FILE *__restrict __stream, __fpos64_t *__restrict __pos),_IO_fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64)
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2),int,__NOTHROW_CB_NCX,__localdep_fgetpos64,(__FILE *__restrict __stream, __fpos64_t *__restrict __pos),fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos64)
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2),int,__NOTHROW_CB_NCX,__localdep_fgetpos64,(__FILE *__restrict __stream, __fpos64_t *__restrict __pos),_IO_fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos_unlocked) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2),int,__NOTHROW_CB_NCX,__localdep_fgetpos64,(__FILE *__restrict __stream, __fpos64_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked)
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2),int,__NOTHROW_CB_NCX,__localdep_fgetpos64,(__FILE *__restrict __stream, __fpos64_t *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE___ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fgetpos64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fgetpos64 __LIBC_LOCAL_NAME(fgetpos64)
#else /* ... */
#undef __local___localdep_fgetpos64_defined
#endif /* !... */
#endif /* !__local___localdep_fgetpos64_defined */
#ifndef __local___localdep_fparseln_defined
#define __local___localdep_fparseln_defined
#ifdef __CRT_HAVE_fparseln
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_IN_OPT(4) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(3),char *,__NOTHROW_CB_NCX,__localdep_fparseln,(__FILE *__stream, __SIZE_TYPE__ *__plen, __SIZE_TYPE__ *__plineno, char const __delim[3], __STDC_INT_AS_UINT_T __flags),fparseln,(__stream,__plen,__plineno,__delim,__flags))
#elif (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
__NAMESPACE_LOCAL_END
#include <libc/local/util/fparseln.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fparseln __LIBC_LOCAL_NAME(fparseln)
#else /* ... */
#undef __local___localdep_fparseln_defined
#endif /* !... */
#endif /* !__local___localdep_fparseln_defined */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_fsetpos64_defined
#define __local___localdep_fsetpos64_defined
#if defined(__CRT_HAVE_fsetpos_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fsetpos64,(__FILE *__restrict __stream, __fpos64_t const *__restrict __pos),fsetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fsetpos64,(__FILE *__restrict __stream, __fpos64_t const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fsetpos64,(__FILE *__restrict __stream, __fpos64_t const *__restrict __pos),fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fsetpos64,(__FILE *__restrict __stream, __fpos64_t const *__restrict __pos),_IO_fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fsetpos64,(__FILE *__restrict __stream, __fpos64_t const *__restrict __pos),fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos64)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fsetpos64,(__FILE *__restrict __stream, __fpos64_t const *__restrict __pos),_IO_fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos_unlocked) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fsetpos64,(__FILE *__restrict __stream, __fpos64_t const *__restrict __pos),fsetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64_unlocked)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fsetpos64,(__FILE *__restrict __stream, __fpos64_t const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || (defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE___fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)))
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fsetpos64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fsetpos64 __LIBC_LOCAL_NAME(fsetpos64)
#else /* ... */
#undef __local___localdep_fsetpos64_defined
#endif /* !... */
#endif /* !__local___localdep_fsetpos64_defined */
#ifndef __local___localdep_mempcpy_defined
#define __local___localdep_mempcpy_defined
#ifdef __CRT_HAVE_mempcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempcpy __LIBC_LOCAL_NAME(mempcpy)
#endif /* !... */
#endif /* !__local___localdep_mempcpy_defined */
#ifndef __local___localdep_rewind_defined
#define __local___localdep_rewind_defined
#if defined(__CRT_HAVE_rewind_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_CB_NCX,__localdep_rewind,(__FILE *__restrict __stream),rewind_unlocked,(__stream))
#elif defined(__CRT_HAVE_rewind)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_CB_NCX,__localdep_rewind,(__FILE *__restrict __stream),rewind,(__stream))
#elif defined(__CRT_HAVE_rewind_unlocked)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_CB_NCX,__localdep_rewind,(__FILE *__restrict __stream),rewind_unlocked,(__stream))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <asm/os/stdio.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE___fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock))
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/rewind.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_rewind __LIBC_LOCAL_NAME(rewind)
#else /* __SEEK_SET && (__CRT_HAVE_fseeko64 || __CRT_HAVE___fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock) */
#undef __local___localdep_rewind_defined
#endif /* !__SEEK_SET || (!__CRT_HAVE_fseeko64 && !__CRT_HAVE___fseeko64 && !__CRT_HAVE_fseek64 && !__CRT_HAVE__fseeki64 && !__CRT_HAVE_fseeko64_unlocked && !__CRT_HAVE_fseek64_unlocked && !__CRT_HAVE__fseeki64_nolock && !__CRT_HAVE_fseeko && !__CRT_HAVE_fseeko_unlocked && !__CRT_HAVE_fseek && !__CRT_HAVE_fseek_unlocked && !__CRT_HAVE__fseek_nolock) */
#endif /* !... */
#endif /* !__local___localdep_rewind_defined */
#ifndef __local___localdep_strchrnul_defined
#define __local___localdep_strchrnul_defined
#ifdef __CRT_HAVE_strchrnul
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchrnul,(char const *__restrict __haystack, int __needle),strchrnul,(__haystack,__needle))
#else /* __CRT_HAVE_strchrnul */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strchrnul.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strchrnul __LIBC_LOCAL_NAME(strchrnul)
#endif /* !__CRT_HAVE_strchrnul */
#endif /* !__local___localdep_strchrnul_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
#ifndef __local___localdep_strtou32_r_defined
#define __local___localdep_strtou32_r_defined
#ifdef __CRT_HAVE_strtou32_r
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),strtou32_r,(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_strtou32_r */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtou32_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtou32_r __LIBC_LOCAL_NAME(strtou32_r)
#endif /* !__CRT_HAVE_strtou32_r */
#endif /* !__local___localdep_strtou32_r_defined */
#ifndef __local___localdep_strtou64_r_defined
#define __local___localdep_strtou64_r_defined
#ifdef __CRT_HAVE_strtou64_r
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),strtou64_r,(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_strtou64_r */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtou64_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtou64_r __LIBC_LOCAL_NAME(strtou64_r)
#endif /* !__CRT_HAVE_strtou64_r */
#endif /* !__local___localdep_strtou64_r_defined */
#ifndef __local___localdep_syslog_defined
#define __local___localdep_syslog_defined
#ifdef __CRT_HAVE_syslog
__LIBC __ATTR_IN(2) __ATTR_LIBC_PRINTF(2, 3) void __NOTHROW_RPC(__VLIBCCALL __localdep_syslog)(__STDC_INT_AS_UINT_T __level, char const *__format, ...) __CASMNAME("syslog");
#elif defined(__CRT_HAVE_vsyslog) || defined(__CRT_HAVE_syslog_printer)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.syslog/syslog.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_syslog __LIBC_LOCAL_NAME(syslog)
#else /* ... */
#undef __local___localdep_syslog_defined
#endif /* !... */
#endif /* !__local___localdep_syslog_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <hybrid/typecore.h>
#include <asm/os/syslog.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fgetspnam_r) __ATTR_INOUT(1) __ATTR_IN_OPT(2) __ATTR_OUT(3) __ATTR_OUT(6) __ATTR_OUTS(4, 5) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(fgetspnam_r))(__FILE *__restrict __stream, char const *__filtered_name, struct spwd *__restrict __resultbuf, char *__restrict __buffer, __SIZE_TYPE__ __buflen, struct spwd **__restrict __result) {
	__errno_t __retval = 0;
	char *__dbline;
	__fpos64_t __startpos, __curpos;
	__fpos64_t __maxpos = (__fpos64_t)-1;
	if ((__NAMESPACE_LOCAL_SYM __localdep_fgetpos64)(__stream, &__startpos))
		goto __err_nodbline;
	__curpos = __startpos;
__again_parseln:
	__dbline = (__NAMESPACE_LOCAL_SYM __localdep_fparseln)(__stream, __NULLPTR, __NULLPTR, "\0\0#", 0);
	if __unlikely(!__dbline)
		goto __err_restore;
	if (!*__dbline) {
		if (!(__NAMESPACE_LOCAL_SYM __localdep_feof)(__stream))
			goto __nextline; /* Skip empty lines! */
		if (__filtered_name != __NULLPTR && __startpos != 0) {
			__maxpos   = __startpos;
			__startpos = 0;
#if defined(__CRT_HAVE_rewind) || defined(__CRT_HAVE_rewind_unlocked) || (defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE___fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)))
			(__NAMESPACE_LOCAL_SYM __localdep_rewind)(__stream);
#else /* __CRT_HAVE_rewind || __CRT_HAVE_rewind_unlocked || (__SEEK_SET && (__CRT_HAVE_fseeko64 || __CRT_HAVE___fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock)) */
			if ((__NAMESPACE_LOCAL_SYM __localdep_fsetpos64)(__stream, &__startpos))
				goto __err;
#endif /* !__CRT_HAVE_rewind && !__CRT_HAVE_rewind_unlocked && (!__SEEK_SET || (!__CRT_HAVE_fseeko64 && !__CRT_HAVE___fseeko64 && !__CRT_HAVE_fseek64 && !__CRT_HAVE__fseeki64 && !__CRT_HAVE_fseeko64_unlocked && !__CRT_HAVE_fseek64_unlocked && !__CRT_HAVE__fseeki64_nolock && !__CRT_HAVE_fseeko && !__CRT_HAVE_fseeko_unlocked && !__CRT_HAVE_fseek && !__CRT_HAVE_fseek_unlocked && !__CRT_HAVE__fseek_nolock)) */
			/* Search for the requested uid/name prior to the initial search-start position. */
			goto __again_parseln;
		}
__eof:
		/* End-of-file */
#ifdef __ENOENT
		__retval = __ENOENT;
#else /* __ENOENT */
		__retval = 1;
#endif /* !__ENOENT */
		goto __done_free_dbline;
	}

	/* Accepted format:
	 *     sp_namp:sp_pwdp:sp_lstchg:sp_min:sp_max:sp_warn:sp_inact:sp_expire:sp_flag */
	{
		char *__field_starts[9];
		char *__iter = __dbline;
		unsigned int __i;
		for (__i = 0; __i < 9; ++__i) {
			if __unlikely(!*__iter)
				goto __badline;
			__field_starts[__i] = __iter;
			__iter = (__NAMESPACE_LOCAL_SYM __localdep_strchrnul)(__iter, ':');
			*__iter++ = '\0';
		}

		/* Fill in defaults (for when fields are empty). */
		__resultbuf->sp_lstchg = (__LONGPTR_TYPE__)__INTPTR_MAX__;
		__resultbuf->sp_min    = 0;
		__resultbuf->sp_max    = (__LONGPTR_TYPE__)__INTPTR_MAX__;
		__resultbuf->sp_warn   = 0;
		__resultbuf->sp_inact  = 0;
		__resultbuf->sp_expire = (__LONGPTR_TYPE__)__INTPTR_MAX__;
		__resultbuf->sp_flag   = 0;

		/* Now parse and fill in fields */
		for (__i = 0; __i < 9; ++__i) {
			static __UINTPTR_TYPE__ const __offsets[9] = {
				__builtin_offsetof(struct spwd, sp_namp),
				__builtin_offsetof(struct spwd, sp_pwdp),
				__builtin_offsetof(struct spwd, sp_lstchg),
				__builtin_offsetof(struct spwd, sp_min),
				__builtin_offsetof(struct spwd, sp_max),
				__builtin_offsetof(struct spwd, sp_warn),
				__builtin_offsetof(struct spwd, sp_inact),
				__builtin_offsetof(struct spwd, sp_expire),
				__builtin_offsetof(struct spwd, sp_flag),
			};
			char *__str;
			__UINTPTR_TYPE__ __offset = __offsets[__i];
			if (__offset == (__UINTPTR_TYPE__)-1)
				continue;
			__str = __field_starts[__i];

			/* Check if this is a string-field */
			if (__i < 2) {
				__SIZE_TYPE__ __len;
				__len = ((__NAMESPACE_LOCAL_SYM __localdep_strlen)(__str) + 1) * sizeof(char);
				/* Ensure that sufficient space is available in the user-provided buffer. */
				if __unlikely(__buflen < __len)
					goto __err_ERANGE;

				/* Set the associated pointer in `resultbuf' */
				*(char **)((__BYTE_TYPE__ *)__resultbuf + __offset) = __buffer;

				/* Copy the string to the user-provided buffer. */
				__buffer = (char *)(__NAMESPACE_LOCAL_SYM __localdep_mempcpy)(__buffer, __str, __len);
				__buflen -= __len;
			} else if (*__str != '\0') {
				__ULONGPTR_TYPE__ ___value;
				__errno_t __error;
				/* Parse as unsigned since we don't want to accept negative numbers. */
#if __SIZEOF_POINTER__ > 4
				___value = (__NAMESPACE_LOCAL_SYM __localdep_strtou64_r)(__str, (char **)&__str, 10, &__error);
#else /* __SIZEOF_POINTER__ > 4 */
				___value = (__NAMESPACE_LOCAL_SYM __localdep_strtou32_r)(__str, (char **)&__str, 10, &__error);
#endif /* __SIZEOF_POINTER__ <= 4 */
				if __unlikely(__error != 0)
					goto __badline;
				if __unlikely(*__str != '\0')
					goto __badline;

				/* Since the record fields are all signed in the public interface,
				 * and  since we parsed  everything as unsigned,  we still have to
				 * make sure that the numbers we'll end up writing won't overflow. */
				if __unlikely(___value > (__ULONGPTR_TYPE__)(__UINTPTR_TYPE__)__INTPTR_MAX__)
					goto __badline;

				/* Save parsed value in record structure. */
				*(__LONGPTR_TYPE__ *)((__BYTE_TYPE__ *)__resultbuf + __offset) = (__LONGPTR_TYPE__)___value;
			}
		}
	}
__done_free_dbline:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__dbline);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	*__result = __retval ? __NULLPTR : __resultbuf;
	return __retval;

__err_ERANGE:
#ifdef __ERANGE
	(void)__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
	/* FALLTHRU */
__err_restore:
	__retval = __libc_geterrno_or(1);
	if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_fsetpos64)(__stream, &__curpos))
		goto __err;
	goto __done_free_dbline;

__err_nodbline:
	__dbline = __NULLPTR;
	/* FALLTHRU */
__err:
	__retval = __libc_geterrno_or(1);
	goto __done_free_dbline;

__badline:
#if defined(__LOG_ERR) && (defined(__CRT_HAVE_syslog) || defined(__CRT_HAVE_vsyslog) || defined(__CRT_HAVE_syslog_printer))
	(__NAMESPACE_LOCAL_SYM __localdep_syslog)(__LOG_ERR, "[shadow] Bad db line: %q\n", __dbline);
#endif /* __LOG_ERR && (__CRT_HAVE_syslog || __CRT_HAVE_vsyslog || __CRT_HAVE_syslog_printer) */
	/* FALLTHRU */
__nextline:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__dbline);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_fgetpos64)(__stream, &__curpos))
		goto __err_nodbline;
	if (__curpos >= __maxpos) {
		__dbline = __NULLPTR;
		goto __eof;
	}
	goto __again_parseln;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fgetspnam_r_defined
#define __local___localdep_fgetspnam_r_defined
#define __localdep_fgetspnam_r __LIBC_LOCAL_NAME(fgetspnam_r)
#endif /* !__local___localdep_fgetspnam_r_defined */
#else /* (__CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_ftello64 || __CRT_HAVE___ftello64 || __CRT_HAVE_ftell64 || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE_ftell64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE__IO_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock) && (__CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || (__SEEK_SET && (__CRT_HAVE_fseeko64 || __CRT_HAVE___fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock))) && (__CRT_HAVE_fparseln || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && (__CRT_HAVE_feof || __CRT_HAVE__IO_feof || __CRT_HAVE_feof_unlocked) */
#undef __local_fgetspnam_r_defined
#endif /* (!__CRT_HAVE_fgetpos64 && !__CRT_HAVE__IO_fgetpos64 && !__CRT_HAVE_fgetpos64_unlocked && !__CRT_HAVE_ftello64 && !__CRT_HAVE___ftello64 && !__CRT_HAVE_ftell64 && !__CRT_HAVE__ftelli64 && !__CRT_HAVE_ftello64_unlocked && !__CRT_HAVE_ftell64_unlocked && !__CRT_HAVE__ftelli64_nolock && !__CRT_HAVE_fgetpos && !__CRT_HAVE__IO_fgetpos && !__CRT_HAVE_fgetpos_unlocked && !__CRT_HAVE_ftello && !__CRT_HAVE_ftello_unlocked && !__CRT_HAVE_ftell && !__CRT_HAVE__IO_ftell && !__CRT_HAVE_ftell_unlocked && !__CRT_HAVE__ftell_nolock) || (!__CRT_HAVE_fsetpos64 && !__CRT_HAVE__IO_fsetpos64 && !__CRT_HAVE_fsetpos64_unlocked && !__CRT_HAVE_fsetpos && !__CRT_HAVE__IO_fsetpos && !__CRT_HAVE_fsetpos_unlocked && (!__SEEK_SET || (!__CRT_HAVE_fseeko64 && !__CRT_HAVE___fseeko64 && !__CRT_HAVE_fseek64 && !__CRT_HAVE__fseeki64 && !__CRT_HAVE_fseeko64_unlocked && !__CRT_HAVE_fseek64_unlocked && !__CRT_HAVE__fseeki64_nolock && !__CRT_HAVE_fseeko && !__CRT_HAVE_fseeko_unlocked && !__CRT_HAVE_fseek && !__CRT_HAVE_fseek_unlocked && !__CRT_HAVE__fseek_nolock))) || (!__CRT_HAVE_fparseln && ((!__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock) || (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) || (!__CRT_HAVE_feof && !__CRT_HAVE__IO_feof && !__CRT_HAVE_feof_unlocked) */
#endif /* !__local_fgetspnam_r_defined */
