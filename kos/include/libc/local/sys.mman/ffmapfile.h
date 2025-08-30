/* HASH CRC-32:0xfd529a3e */
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
#ifndef __local_ffmapfile_defined
#define __local_ffmapfile_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
#if (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_feof) || defined(__CRT_HAVE__IO_feof) || defined(__CRT_HAVE_feof_unlocked)) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE___fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <bits/crt/mapfile.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bzero_defined
#define __local___localdep_bzero_defined
#ifdef __CRT_HAVE_bzero
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/bzero.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bzero __LIBC_LOCAL_NAME(bzero)
#endif /* !... */
#endif /* !__local___localdep_bzero_defined */
#ifndef __local___localdep_calloc_defined
#define __local___localdep_calloc_defined
#if __has_builtin(__builtin_calloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_calloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,__localdep_calloc,(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),calloc,{ return __builtin_calloc(__count, __num_bytes); })
#elif defined(__CRT_HAVE_calloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,__localdep_calloc,(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),calloc,(__count,__num_bytes))
#elif defined(__CRT_HAVE___libc_calloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,__localdep_calloc,(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),__libc_calloc,(__count,__num_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/calloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_calloc __LIBC_LOCAL_NAME(calloc)
#endif /* !... */
#endif /* !__local___localdep_calloc_defined */
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
#ifndef __local___localdep_fileno_defined
#define __local___localdep_fileno_defined
#if defined(__CRT_HAVE_fileno_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#elif defined(__CRT_HAVE_fileno)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),fileno,(__stream))
#elif defined(__CRT_HAVE__fileno)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),_fileno,(__stream))
#elif defined(__CRT_HAVE_fileno_unlocked)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#else /* ... */
#undef __local___localdep_fileno_defined
#endif /* !... */
#endif /* !__local___localdep_fileno_defined */
#ifndef __local___localdep_fmapfile_defined
#define __local___localdep_fmapfile_defined
#ifdef __CRT_HAVE_fmapfile
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDARG(2) __ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_fmapfile,(struct mapfile *__restrict __mapping, __fd_t __fd, __pos64_t __offset, __SIZE_TYPE__ __min_bytes, __SIZE_TYPE__ __max_bytes, __SIZE_TYPE__ __num_trailing_nulbytes, unsigned int __flags),fmapfile,(__mapping,__fd,__offset,__min_bytes,__max_bytes,__num_trailing_nulbytes,__flags))
#elif defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.mman/fmapfile.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fmapfile __LIBC_LOCAL_NAME(fmapfile)
#else /* ... */
#undef __local___localdep_fmapfile_defined
#endif /* !... */
#endif /* !__local___localdep_fmapfile_defined */
#ifndef __local___localdep_fread_defined
#define __local___localdep_fread_defined
#if defined(__CRT_HAVE_fread_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fread_nolock) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_fread_nolock,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fread)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fread)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_IO_fread,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fread_unlocked)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_fread_nolock,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget)))
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fread.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fread __LIBC_LOCAL_NAME(fread)
#else /* ... */
#undef __local___localdep_fread_defined
#endif /* !... */
#endif /* !__local___localdep_fread_defined */
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
#ifndef __local___localdep_fseeko64_defined
#define __local___localdep_fseeko64_defined
#if defined(__CRT_HAVE_fseek_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE___fseeko64)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),__fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fseeko64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fseeko64 __LIBC_LOCAL_NAME(fseeko64)
#else /* ... */
#undef __local___localdep_fseeko64_defined
#endif /* !... */
#endif /* !__local___localdep_fseeko64_defined */
#ifndef __local___localdep_ftello64_defined
#define __local___localdep_ftello64_defined
#if defined(__CRT_HAVE_ftell_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),ftell,(__stream))
#elif defined(__CRT_HAVE__IO_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_ftello) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftello64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE___ftello64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),__ftello64,(__stream))
#elif defined(__CRT_HAVE_ftell64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),ftell64,(__stream))
#elif defined(__CRT_HAVE__ftelli64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_ftell_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__off64_t,__NOTHROW_CB_NCX,__localdep_ftello64,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/ftello64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ftello64 __LIBC_LOCAL_NAME(ftello64)
#else /* ... */
#undef __local___localdep_ftello64_defined
#endif /* !... */
#endif /* !__local___localdep_ftello64_defined */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE___libc_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),__libc_malloc,(__num_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/malloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_malloc __LIBC_LOCAL_NAME(malloc)
#endif /* !... */
#endif /* !__local___localdep_malloc_defined */
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),__libc_realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
#include <asm/os/mman.h>
#include <libc/errno.h>
#include <asm/os/stdio.h>
#include <hybrid/__overflow.h>
#include <asm/crt/malloc.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ffmapfile) __ATTR_WUNUSED __ATTR_INOUT(2) __ATTR_OUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ffmapfile))(struct mapfile *__restrict __mapping, __FILE *__stream, __pos64_t __offset, __SIZE_TYPE__ __min_bytes, __SIZE_TYPE__ __max_bytes, __SIZE_TYPE__ __num_trailing_nulbytes, unsigned int __flags) {
	__BYTE_TYPE__ *__buf;
	__SIZE_TYPE__ __bufsize;
	__SIZE_TYPE__ __bufused;
	__SIZE_TYPE__ __buffree;

	/* Helper macro that makes sure `errno(3)' is preserved across `expr' */
#if defined(__libc_geterrno) && defined(__libc_seterrno)
#define __LOCAL_preserve_errno(__expr)              \
	do {                                          \
		__errno_t ___saved_errno = __libc_geterrno(); \
		__expr;                                     \
		__libc_seterrno(___saved_errno);            \
	}	__WHILE0
#else /* __libc_geterrno && __libc_seterrno */
#define __LOCAL_preserve_errno(__expr) (__expr)
#endif /* !__libc_geterrno || !__libc_seterrno */

	/* Validate the given `flags' */
	if __unlikely(__flags & ~(__FMAPFILE_READALL | __FMAPFILE_MUSTMMAP |
	                      __FMAPFILE_MAPSHARED | __FMAPFILE_ATSTART)) {
#ifdef __EINVAL
		return __libc_seterrno(__EINVAL);
#else /* __EINVAL */
		return __libc_seterrno(1);
#endif /* !__EINVAL */
	}

	/* Check for special case: map an empty portion of the file. */
	if __unlikely(__max_bytes == 0) {
#ifndef __MALLOC_ZERO_IS_NONNULL
		if (__num_trailing_nulbytes == 0)
			__num_trailing_nulbytes = 1;
#endif /* !__MALLOC_ZERO_IS_NONNULL */
		__buf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_calloc)(1, __num_trailing_nulbytes);
		if __unlikely(!__buf)
			return -1;
		__mapping->mf_addr = __buf;
		__mapping->mf_size = 0;
		__mapping->__mf_mapsize = 0;
		return 0;
	}

	/* See if the stream has a file descriptor.
	 * If so: use `fmapfile(3)' to map the file */
#if (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE___ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)) && (defined(__CRT_HAVE_fmapfile) || defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read))
	{
		__fd_t __fd = (__NAMESPACE_LOCAL_SYM __localdep_fileno)(__stream);
		if (__fd != -1) {
			if (!(__flags & __FMAPFILE_ATSTART))
				__offset += (__NAMESPACE_LOCAL_SYM __localdep_ftello64)(__stream);
			return (__NAMESPACE_LOCAL_SYM __localdep_fmapfile)(__mapping, __fd, __offset, __min_bytes, __max_bytes, __num_trailing_nulbytes, __flags);
		}
	}
#endif /* (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_ftello64 || __CRT_HAVE___ftello64 || __CRT_HAVE_ftell64 || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE_ftell64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE__IO_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock) && (__CRT_HAVE_fmapfile || __CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) */

	/* Check if we're to error out if mmap can't be used */
	if (__flags & __FMAPFILE_MUSTMMAP) {
#ifdef __ENOTSUP
		return __libc_seterrno(__ENOTSUP);
#elif defined(__EOPNOTSUPP)
		return __libc_seterrno(__EOPNOTSUPP);
#else /* ... */
		return __libc_seterrno(1);
#endif /* !... */
	}

	/* Allocate a heap buffer. */
	__bufsize = __max_bytes;
	if (__bufsize > 0x10000)
		__bufsize = 0x10000;
	if (__bufsize < __min_bytes)
		__bufsize = __min_bytes;
	{
		__SIZE_TYPE__ __alcsize;
		if __unlikely(__hybrid_overflow_uadd(__bufsize, __num_trailing_nulbytes, &__alcsize))
			goto __err_2big;
		__LOCAL_preserve_errno(__buf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__alcsize));
	}
	if __unlikely(!__buf) {
		__bufsize = 1;
		if (__bufsize < __min_bytes)
			__bufsize = __min_bytes;
		__buf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__bufsize + __num_trailing_nulbytes);
		if __unlikely(!__buf)
			return -1;
	}
	__bufused = 0;
	__buffree = __bufsize;

	/* For a custom offset, try to use fseeko64() */
	if (__offset != (__pos64_t)-1 && (__offset != 0 || !(__flags & __FMAPFILE_ATSTART))) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_fseeko64)(__stream, (__off64_t)__offset, __SEEK_SET))
			goto __err_buf;
	}

	/* Use fread(3) to read data from the stream */
	for (;;) {
		__SIZE_TYPE__ __error = (__NAMESPACE_LOCAL_SYM __localdep_fread)(__buf + __bufused, 1, __buffree, __stream);
		if (__error <= 0 || (!(__flags & __FMAPFILE_READALL) && (__SIZE_TYPE__)__error < __buffree)) {
			if (__error >= 0 || (__NAMESPACE_LOCAL_SYM __localdep_feof)(__stream)) {
				/* End-of-file! */
				__BYTE_TYPE__ *__newbuf;
				__SIZE_TYPE__ __used_nulbytes;
				__bufused += (__SIZE_TYPE__)__error;
				__used_nulbytes = __num_trailing_nulbytes;
				if (__min_bytes > __bufused)
					__used_nulbytes += __min_bytes - __bufused;
				__LOCAL_preserve_errno(__newbuf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__buf, __bufused + __used_nulbytes));
				if __likely(__newbuf)
					__buf = __newbuf;
				(__NAMESPACE_LOCAL_SYM __localdep_bzero)(__buf + __bufused, __used_nulbytes); /* Trailing NUL-bytes */
				__mapping->mf_addr = __buf;
				__mapping->mf_size = __bufused;
				__mapping->__mf_mapsize = 0;
				return 0;
			}
			/* Read error */
			goto __err_buf;
		}
		__bufused += (__SIZE_TYPE__)__error;
		__buffree -= (__SIZE_TYPE__)__error;
		if (__buffree < 1024) {
			__BYTE_TYPE__ *__newbuf;
			__SIZE_TYPE__ __newsize, __alcsize;
			if __unlikely(__hybrid_overflow_umul(__bufsize, 2, &__newsize))
				__newsize = (__SIZE_TYPE__)-1;
			if __unlikely(__hybrid_overflow_uadd(__newsize, __num_trailing_nulbytes, &__alcsize))
				__alcsize = (__SIZE_TYPE__)-1;
			__LOCAL_preserve_errno(__newbuf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__buf, __alcsize));
			if (!__newbuf) {
				if __unlikely(__hybrid_overflow_uadd(__bufsize, 1024, &__newsize))
					__newsize = (__SIZE_TYPE__)-1;
				if __unlikely(__hybrid_overflow_uadd(__newsize, __num_trailing_nulbytes, &__alcsize))
					__alcsize = (__SIZE_TYPE__)-1;
				__LOCAL_preserve_errno(__newbuf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__buf, __alcsize));
				if (!__newbuf) {
					if (!__buffree) {
						if __unlikely(__hybrid_overflow_uadd(__bufsize, 1, &__newsize))
							goto __err_buf_2big;
						if __unlikely(__hybrid_overflow_uadd(__newsize, __num_trailing_nulbytes, &__alcsize))
							goto __err_buf_2big;
						__newbuf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__buf, __alcsize);
						if __unlikely(!__newbuf)
							goto __err_buf;
					} else {
						__newsize = __bufsize;
						__newbuf  = __buf;
					}
				}
			}
			__buffree += __newsize - __bufsize;
			__bufsize = __newsize;
			__buf     = __newbuf;
		}
	}

	/*--------------------------------------------------------------------*/
	{
		__BYTE_TYPE__ *__newbuf;
		__SIZE_TYPE__ __used_nulbytes;
		/* Because of how large our original buffer was, and because at this
		 * point all  we want  to do  is return  a  `num_trailing_nulbytes'-
		 * large buffer of  all NUL-bytes, it's  probably more efficient  to
		 * allocate a new  (small) buffer,  than trying to  realloc the  old
		 * buffer. If we try  to do realloc(), the  heap might see that  all
		 * we're  trying to do  is truncate the buffer,  and so might choose
		 * not to alter its base  address, which (if done repeatedly)  might
		 * lead to memory becoming very badly fragmented. */
		__used_nulbytes = __min_bytes + __num_trailing_nulbytes;
		__LOCAL_preserve_errno(__newbuf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_calloc)(1, __used_nulbytes));
		if __likely(__newbuf) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
			(__NAMESPACE_LOCAL_SYM __localdep_free)(__buf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
		} else {
#ifndef __REALLOC_ZERO_IS_NONNULL
			if __unlikely(!__used_nulbytes)
				__used_nulbytes = 1;
#endif /* !__REALLOC_ZERO_IS_NONNULL */
			__LOCAL_preserve_errno(__newbuf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__buf, __used_nulbytes));
			if (!__newbuf)
				__newbuf = __buf;
			(__NAMESPACE_LOCAL_SYM __localdep_bzero)(__newbuf, __used_nulbytes);
		}
		__mapping->mf_addr = __newbuf;
		__mapping->mf_size = 0;
		__mapping->__mf_mapsize = 0;
	}
#undef __LOCAL_preserve_errno
	return 0;
__err_2big:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	__buf = __NULLPTR;
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__err_buf_2big:
#ifdef __ENOMEM
	__libc_seterrno(__ENOMEM);
#else /* __ENOMEM */
	__libc_seterrno(1);
#endif /* !__ENOMEM */
__err_buf:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__buf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ffmapfile_defined
#define __local___localdep_ffmapfile_defined
#define __localdep_ffmapfile __LIBC_LOCAL_NAME(ffmapfile)
#endif /* !__local___localdep_ffmapfile_defined */
#else /* (__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_feof || __CRT_HAVE__IO_feof || __CRT_HAVE_feof_unlocked) && (__CRT_HAVE_fseeko64 || __CRT_HAVE___fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __local_ffmapfile_defined
#endif /* (!__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) || (!__CRT_HAVE_feof && !__CRT_HAVE__IO_feof && !__CRT_HAVE_feof_unlocked) || (!__CRT_HAVE_fseeko64 && !__CRT_HAVE___fseeko64 && !__CRT_HAVE_fseek64 && !__CRT_HAVE__fseeki64 && !__CRT_HAVE_fseeko64_unlocked && !__CRT_HAVE_fseek64_unlocked && !__CRT_HAVE__fseeki64_nolock && !__CRT_HAVE_fseeko && !__CRT_HAVE_fseeko_unlocked && !__CRT_HAVE_fseek && !__CRT_HAVE_fseek_unlocked && !__CRT_HAVE__fseek_nolock) || (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !__local_ffmapfile_defined */
