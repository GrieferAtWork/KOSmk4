/* HASH CRC-32:0xff40fcbc */
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
#ifndef __local_fmapfile_defined
#define __local_fmapfile_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <bits/types.h>
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
#ifndef __local___localdep_fstat64_defined
#define __local___localdep_fstat64_defined
#if defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat64,(__fd_t __fd, struct __stat64 *__restrict __buf),kfstat,(__fd,__buf))
#elif defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat64,(__fd_t __fd, struct __stat64 *__restrict __buf),kfstat64,(__fd,__buf))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat64,(__fd_t __fd, struct __stat64 *__restrict __buf),_fstat64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat64,(__fd_t __fd, struct __stat64 *__restrict __buf),_fstat64i32,(__fd,__buf))
#elif defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat64,(__fd_t __fd, struct __stat64 *__restrict __buf),_fstati64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat64,(__fd_t __fd, struct __stat64 *__restrict __buf),_fstat32i64,(__fd,__buf))
#elif defined(__CRT_HAVE___fstat64_time64) && defined(__USE_TIME_BITS64) && defined(__glc_stat64_time64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat64,(__fd_t __fd, struct __stat64 *__restrict __buf),__fstat64_time64,(__fd,__buf))
#elif defined(__CRT_HAVE_fstat) && defined(__STAT32_MATCHES_STAT64)
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat64,(__fd_t __fd, struct __stat64 *__restrict __buf),fstat,(__fd,__buf))
#elif defined(__CRT_HAVE_fstat64) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64))
__NAMESPACE_LOCAL_END
#include <bits/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat64,(__fd_t __fd, struct __stat64 *__restrict __buf),fstat64,(__fd,__buf))
#elif defined(__CRT_HAVE_fstat) || defined(__CRT_HAVE_fstat64) || defined(__CRT_HAVE___fstat64_time64) || defined(__CRT_HAVE__fstat) || defined(__CRT_HAVE__fstat32) || defined(__CRT_HAVE__fstati64) || defined(__CRT_HAVE__fstat32i64) || defined(__CRT_HAVE__fstat64) || defined(__CRT_HAVE__fstat64i32)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/fstat64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fstat64 __LIBC_LOCAL_NAME(fstat64)
#else /* ... */
#undef __local___localdep_fstat64_defined
#endif /* !... */
#endif /* !... */
#endif /* !__local___localdep_fstat64_defined */
#ifndef __local___localdep_lseek64_defined
#define __local___localdep_lseek64_defined
#if defined(__CRT_HAVE_lseek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_FDARG(1),__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_FDARG(1),__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___lseek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_FDARG(1),__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),__lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___libc_lseek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_FDARG(1),__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),__libc_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek64)
__CREDIRECT(__ATTR_FDARG(1),__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),lseek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseeki64)
__CREDIRECT(__ATTR_FDARG(1),__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),_lseeki64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_llseek)
__CREDIRECT(__ATTR_FDARG(1),__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),llseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___llseek)
__CREDIRECT(__ATTR_FDARG(1),__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),__llseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/lseek64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_lseek64 __LIBC_LOCAL_NAME(lseek64)
#else /* ... */
#undef __local___localdep_lseek64_defined
#endif /* !... */
#endif /* !__local___localdep_lseek64_defined */
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
#ifndef __local___localdep_mmap64_defined
#define __local___localdep_mmap64_defined
#if defined(__CRT_HAVE_mmap) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#include <features.h>
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_NONE(1) __ATTR_FDARG(5),void *,__NOTHROW_NCX,__localdep_mmap64,(void *__addr, __SIZE_TYPE__ __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __PIO_OFFSET64 __offset),mmap,(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE___mmap) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#include <features.h>
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_NONE(1) __ATTR_FDARG(5),void *,__NOTHROW_NCX,__localdep_mmap64,(void *__addr, __SIZE_TYPE__ __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __PIO_OFFSET64 __offset),__mmap,(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE_mmap64)
__NAMESPACE_LOCAL_END
#include <features.h>
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_NONE(1) __ATTR_FDARG(5),void *,__NOTHROW_NCX,__localdep_mmap64,(void *__addr, __SIZE_TYPE__ __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __PIO_OFFSET64 __offset),mmap64,(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE_mmap) || defined(__CRT_HAVE___mmap)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.mman/mmap64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mmap64 __LIBC_LOCAL_NAME(mmap64)
#else /* ... */
#undef __local___localdep_mmap64_defined
#endif /* !... */
#endif /* !__local___localdep_mmap64_defined */
#ifndef __local___localdep_pread64_defined
#define __local___localdep_pread64_defined
#if defined(__CRT_HAVE_pread) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#include <features.h>
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pread64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),pread,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pread64)
__NAMESPACE_LOCAL_END
#include <features.h>
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pread64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),pread64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE___pread64)
__NAMESPACE_LOCAL_END
#include <features.h>
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pread64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),__pread64,(__fd,__buf,__bufsize,__offset))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <asm/os/stdio.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/pread64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pread64 __LIBC_LOCAL_NAME(pread64)
#else /* __CRT_HAVE_pread || ((__CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 || __CRT_HAVE_llseek || __CRT_HAVE___llseek || __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE___libc_lseek) && __SEEK_CUR && __SEEK_SET) */
#undef __local___localdep_pread64_defined
#endif /* !__CRT_HAVE_pread && ((!__CRT_HAVE_lseek64 && !__CRT_HAVE__lseeki64 && !__CRT_HAVE_llseek && !__CRT_HAVE___llseek && !__CRT_HAVE_lseek && !__CRT_HAVE__lseek && !__CRT_HAVE___lseek && !__CRT_HAVE___libc_lseek) || !__SEEK_CUR || !__SEEK_SET) */
#endif /* !... */
#endif /* !__local___localdep_pread64_defined */
#ifndef __local___localdep_read_defined
#define __local___localdep_read_defined
#ifdef __CRT_HAVE_read
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__read)
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),_read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___read)
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),__read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___libc_read)
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),__libc_read,(__fd,__buf,__bufsize))
#else /* ... */
#undef __local___localdep_read_defined
#endif /* !... */
#endif /* !__local___localdep_read_defined */
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
__LOCAL_LIBC(fmapfile) __ATTR_WUNUSED __ATTR_FDARG(2) __ATTR_OUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fmapfile))(struct mapfile *__restrict __mapping, __fd_t __fd, __pos64_t __offset, __SIZE_TYPE__ __min_bytes, __SIZE_TYPE__ __max_bytes, __SIZE_TYPE__ __num_trailing_nulbytes, unsigned int __flags) {
	__BYTE_TYPE__ *__buf;
	__SIZE_TYPE__ __bufsize;
	__SIZE_TYPE__ __bufused;
	__SIZE_TYPE__ __buffree;

	/* Validate the given `flags' */
	if __unlikely(__flags & ~(__FMAPFILE_READALL | __FMAPFILE_MUSTMMAP |
	                      __FMAPFILE_MAPSHARED | __FMAPFILE_ATSTART)) {
#ifdef __EINVAL
		return __libc_seterrno(__EINVAL);
#else /* __EINVAL */
		return __libc_seterrno(1);
#endif /* !__EINVAL */
	}

	/* Try to use mmap(2) */
#if defined(__PROT_READ) && defined(__PROT_WRITE) && defined(__MAP_PRIVATE) && defined(__SEEK_SET) && (defined(__CRT_HAVE_mmap64) || defined(__CRT_HAVE_mmap) || defined(__CRT_HAVE___mmap)) && ((defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstat) || defined(__CRT_HAVE_fstat64) || defined(__CRT_HAVE___fstat64_time64) || defined(__CRT_HAVE__fstat) || defined(__CRT_HAVE__fstat32) || defined(__CRT_HAVE__fstati64) || defined(__CRT_HAVE__fstat32i64) || defined(__CRT_HAVE__fstat64) || defined(__CRT_HAVE__fstat64i32)) && (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek))
	{
		struct stat64 __st;
		if ((__NAMESPACE_LOCAL_SYM __localdep_fstat64)(__fd, &__st) == 0) {
#if defined(__libc_geterrno) && defined(__libc_seterrno)
			__errno_t __saved_errno = __libc_geterrno();
#endif /* __libc_geterrno && __libc_seterrno */
			__pos64_t __map_offset = __offset;
			__SIZE_TYPE__ __map_bytes;
			if (__map_offset == (__pos64_t)-1) {
				if __unlikely(__flags & __FMAPFILE_ATSTART) {
					__map_offset = 0;
				} else {
					/* Use the file descriptors current offset. */
					__map_offset = (__pos64_t)(__NAMESPACE_LOCAL_SYM __localdep_lseek64)(__fd, 0, __SEEK_CUR);
					if (__map_offset == (__pos64_t)-1)
						goto __after_mmap_attempt;
				}
			}
			if (__hybrid_overflow_usub(__st.st_size, __map_offset, &__map_bytes)) {
				__map_bytes = 0;
				if (__st.st_size > __map_offset)
					__map_bytes = (__SIZE_TYPE__)-1;
			}
			if (__map_bytes >= __max_bytes) {
				__map_bytes = __max_bytes;
#if __SIZEOF_SIZE_T__ < __SIZEOF_OFF64_T__
				if (__map_bytes == (__SIZE_TYPE__)-1) {
					/* Special case: caller wants to map the entire file, but it's too large. */
					__UINT64_TYPE__ __true_size = __st.st_size - __map_offset;
					if (__true_size > (__UINT64_TYPE__)(__SIZE_TYPE__)-1) {
						/* File is too large to be loaded into memory in its entirety. */
						if (__flags & __FMAPFILE_MUSTMMAP) {
#ifdef __ENOTSUP
							return __libc_seterrno(__ENOTSUP);
#elif defined(__EOPNOTSUPP)
							return __libc_seterrno(__EOPNOTSUPP);
#else /* ... */
							return __libc_seterrno(1);
#endif /* !... */
						}

						/* File is too large for a continuous heap-buffer to be posible */
#ifdef __ENOMEM
						return __libc_seterrno(__ENOMEM);
#else /* __ENOMEM */
						return __libc_seterrno(1);
#endif /* !__ENOMEM */
					}
				}
#endif /* __SIZEOF_SIZE_T__ < __SIZEOF_OFF64_T__ */
			}
			if (__map_bytes) {
				/* Map file into memory. */
				__SIZE_TYPE__ __mapsize, __used_nulbytes;
				__used_nulbytes = __num_trailing_nulbytes;
				if (__min_bytes > __map_bytes)
					__used_nulbytes += __min_bytes - __map_bytes;
				__mapsize = __map_bytes + __used_nulbytes;
#ifdef __MAP_SHARED
				if (__flags & __FMAPFILE_MAPSHARED) {
					if __unlikely(__num_trailing_nulbytes) {
#ifdef __EINVAL
						return __libc_seterrno(__EINVAL);
#else /* __EINVAL */
						return __libc_seterrno(1);
#endif /* !__EINVAL */
					}
					__buf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_mmap64)(__NULLPTR, __mapsize, __PROT_READ | __PROT_WRITE,
					                       __MAP_SHARED, __fd, (__PIO_OFFSET64)__map_offset);
				} else {
					__buf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_mmap64)(__NULLPTR, __mapsize, __PROT_READ | __PROT_WRITE,
					                       __MAP_PRIVATE, __fd, (__PIO_OFFSET64)__map_offset);
				}
#else /* __MAP_SHARED */
				if __unlikely(__flags & __FMAPFILE_MAPSHARED) {
					/* Shared memory mappings aren't supposed :( */
#ifdef __ENOSYS
					return __libc_seterrno(__ENOSYS);
#elif defined(__ENOTSUP)
					return __libc_seterrno(__ENOTSUP);
#elif defined(__EOPNOTSUPP)
					return __libc_seterrno(__EOPNOTSUPP);
#else /* ... */
					return __libc_seterrno(1);
#endif /* !... */
				}
				__buf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_mmap64)(__NULLPTR, __mapsize,
				                       __PROT_READ | __PROT_WRITE,
				                       __MAP_PRIVATE, __fd,
				                       (__PIO_OFFSET64)__map_offset);
#endif /* !__MAP_SHARED */
				if (__buf != (__BYTE_TYPE__ *)__MAP_FAILED) {
					/* Clear  out the caller-required trailing NUL bytes.
					 * We do this in a kind-of special way that tries not
					 * to write-fault memory if it already contains NULs. */
					__BYTE_TYPE__ *__nul = __buf + __map_bytes;
					while (__used_nulbytes) {
						if (*__nul) {
							(__NAMESPACE_LOCAL_SYM __localdep_bzero)(__nul, __used_nulbytes);
							break;
						}
						--__used_nulbytes;
						++__nul;
					}
					__mapping->mf_addr = __buf;
					__mapping->mf_size = __map_bytes;
					__mapping->__mf_mapsize = __mapsize;
					return 0;
				}
#if defined(__libc_geterrno) && defined(__libc_seterrno)
				__libc_seterrno(__saved_errno);
#endif /* __libc_geterrno && __libc_seterrno */
			} else {
				/* Special files from procfs indicate their size as `0',  even
				 * though they aren't actually empty. - As such, we can't just
				 * use the normal approach of read(2)-ing the file.
				 *
				 * Only if at that point it still indicates being empty, are we
				 * actually allowed to believe that claim! */
			}
		}
	}
__after_mmap_attempt:
#endif /* __PROT_READ && __PROT_WRITE && __MAP_PRIVATE && __SEEK_SET && (__CRT_HAVE_mmap64 || __CRT_HAVE_mmap || __CRT_HAVE___mmap) && ((__CRT_HAVE_kfstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstat || __CRT_HAVE_fstat64 || __CRT_HAVE___fstat64_time64 || __CRT_HAVE__fstat || __CRT_HAVE__fstat32 || __CRT_HAVE__fstati64 || __CRT_HAVE__fstat32i64 || __CRT_HAVE__fstat64 || __CRT_HAVE__fstat64i32) && (__CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 || __CRT_HAVE_llseek || __CRT_HAVE___llseek || __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE___libc_lseek) */

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
	__buf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__bufsize + __num_trailing_nulbytes);
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

	if (__offset != (__pos64_t)-1 && (__offset != 0 || !(__flags & __FMAPFILE_ATSTART))) {
		/* Try to use pread(2) */
#if defined(__CRT_HAVE_pread64) || defined(__CRT_HAVE___pread64) || defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
		for (;;) {
			__SSIZE_TYPE__ __error;
			__error = (__NAMESPACE_LOCAL_SYM __localdep_pread64)(__fd, __buf + __bufused, __buffree, __offset);
			if (__error <= 0 || (!(__flags & __FMAPFILE_READALL) && (__SIZE_TYPE__)__error < __buffree)) {
				if ((__SIZE_TYPE__)__error < __buffree) {
					/* End-of-file! */
					__BYTE_TYPE__ *__newbuf;
					__SIZE_TYPE__ __used_nulbytes;
					__bufused += (__SIZE_TYPE__)__error;
					__used_nulbytes = __num_trailing_nulbytes;
					if (__min_bytes > __bufused)
						__used_nulbytes += __min_bytes - __bufused;
					__newbuf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__buf, __bufused + __used_nulbytes);
					if __likely(__newbuf)
						__buf = __newbuf;
					(__NAMESPACE_LOCAL_SYM __localdep_bzero)(__buf + __bufused, __used_nulbytes); /* Trailing NUL-bytes */
					__mapping->mf_addr = __buf;
					__mapping->mf_size = __bufused;
					__mapping->__mf_mapsize = 0;
					return 0;
				}
				if (__bufused == 0)
					break; /* File probably doesn't support `pread(2)'... */
				/* Read error */
				goto __err_buf;
			}
			__offset  += (__SIZE_TYPE__)__error;
			__bufused += (__SIZE_TYPE__)__error;
			__buffree -= (__SIZE_TYPE__)__error;
			if (__buffree < 1024) {
				__BYTE_TYPE__ *__newbuf;
				__SIZE_TYPE__ __newsize = __bufsize * 2;
				__newbuf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__buf, __newsize + __num_trailing_nulbytes);
				if (!__newbuf) {
					__newsize = __bufsize + 1024;
					__newbuf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__buf, __newsize + __num_trailing_nulbytes);
					if (!__newbuf) {
						if (!__buffree) {
							__newsize = __bufsize + 1;
							__newbuf  = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__buf, __newsize + __num_trailing_nulbytes);
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
#endif /* __CRT_HAVE_pread64 || __CRT_HAVE___pread64 || __CRT_HAVE_pread || ((__CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 || __CRT_HAVE_llseek || __CRT_HAVE___llseek || __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE___libc_lseek) && __SEEK_CUR && __SEEK_SET) */

		/* For a custom offset, try to use lseek() (or read()) */
#if (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && defined(__SEEK_SET)
		if ((__NAMESPACE_LOCAL_SYM __localdep_lseek64)(__fd, (__off64_t)__offset, __SEEK_SET) != -1) {
			/* Was able to lseek(2) */
		} else
#endif /* (__CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 || __CRT_HAVE_llseek || __CRT_HAVE___llseek || __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE___libc_lseek) && __SEEK_SET */
		{
			/* Try to use read(2) to skip leading data. */
			while (__offset) {
				__SSIZE_TYPE__ __error;
				__SIZE_TYPE__ __skip = __bufsize + __num_trailing_nulbytes;
				if ((__pos64_t)__skip > __offset)
					__skip = (__SIZE_TYPE__)__offset;
				__error = (__NAMESPACE_LOCAL_SYM __localdep_read)(__fd, __buf, __skip);
				if (__error <= 0 || (!(__flags & __FMAPFILE_READALL) && (__SIZE_TYPE__)__error < __skip)) {
					if (__error < 0)
						goto __err_buf;
					goto __empty_file; /* EOF reached before `offset' */
				}
				__offset -= __error;
			}
		}
	}

	/* Use read(2) as fallback */
	for (;;) {
		__SSIZE_TYPE__ __error;
		__error = (__NAMESPACE_LOCAL_SYM __localdep_read)(__fd, __buf + __bufused, __buffree);
		if (__error <= 0 || (!(__flags & __FMAPFILE_READALL) && (__SIZE_TYPE__)__error < __buffree)) {
			if (__error >= 0) {
				/* End-of-file! */
				__BYTE_TYPE__ *__newbuf;
				__SIZE_TYPE__ __used_nulbytes;
				__bufused += (__SIZE_TYPE__)__error;
				__used_nulbytes = __num_trailing_nulbytes;
				if (__min_bytes > __bufused)
					__used_nulbytes += __min_bytes - __bufused;
				__newbuf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__buf, __bufused + __used_nulbytes);
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
			__SIZE_TYPE__ __newsize = __bufsize * 2;
			__newbuf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__buf, __newsize + __num_trailing_nulbytes);
			if (!__newbuf) {
				__newsize = __bufsize + 1024;
				__newbuf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__buf, __newsize + __num_trailing_nulbytes);
				if (!__newbuf) {
					if (!__buffree) {
						__newsize = __bufsize + 1;
						__newbuf  = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__buf, __newsize + __num_trailing_nulbytes);
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
__empty_file:
		__used_nulbytes = __min_bytes + __num_trailing_nulbytes;
		__newbuf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_calloc)(1, __used_nulbytes);
		if __likely(__newbuf) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
			(__NAMESPACE_LOCAL_SYM __localdep_free)(__buf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
		} else {
#ifndef __REALLOC_ZERO_IS_NONNULL
			if __unlikely(!__used_nulbytes)
				__used_nulbytes = 1;
#endif /* !__REALLOC_ZERO_IS_NONNULL */
			__newbuf = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__buf, __used_nulbytes);
			if (!__newbuf)
				__newbuf = __buf;
			(__NAMESPACE_LOCAL_SYM __localdep_bzero)(__newbuf, __used_nulbytes);
		}
		__mapping->mf_addr = __newbuf;
		__mapping->mf_size = 0;
		__mapping->__mf_mapsize = 0;
	}
	return 0;
__err_buf:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__buf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fmapfile_defined
#define __local___localdep_fmapfile_defined
#define __localdep_fmapfile __LIBC_LOCAL_NAME(fmapfile)
#endif /* !__local___localdep_fmapfile_defined */
#else /* (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __local_fmapfile_defined
#endif /* (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !__local_fmapfile_defined */
