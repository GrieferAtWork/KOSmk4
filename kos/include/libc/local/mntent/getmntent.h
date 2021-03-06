/* HASH CRC-32:0xfb174742 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getmntent_defined
#define __local_getmntent_defined 1
#include <__crt.h>
#include <features.h>
#if defined(__CRT_HAVE_getmntent_r) || defined(__CRT_HAVE___getmntent_r) || defined(__CRT_HAVE_fgets) || defined(__CRT_HAVE_fgets_unlocked) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)))
#include <bits/crt/db/mntent.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: getmntent_r from mntent */
#ifndef __local___localdep_getmntent_r_defined
#define __local___localdep_getmntent_r_defined 1
#ifdef __CRT_HAVE_getmntent_r
/* >> getmntent(3), getmntent_r(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),struct mntent *,__NOTHROW_RPC,__localdep_getmntent_r,(__FILE *__restrict __stream, struct mntent *__restrict __result, char *__restrict __buffer, __STDC_INT_AS_SIZE_T __bufsize),getmntent_r,(__stream,__result,__buffer,__bufsize))
#elif defined(__CRT_HAVE___getmntent_r)
/* >> getmntent(3), getmntent_r(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),struct mntent *,__NOTHROW_RPC,__localdep_getmntent_r,(__FILE *__restrict __stream, struct mntent *__restrict __result, char *__restrict __buffer, __STDC_INT_AS_SIZE_T __bufsize),__getmntent_r,(__stream,__result,__buffer,__bufsize))
#elif defined(__CRT_HAVE_fgets) || defined(__CRT_HAVE_fgets_unlocked) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)))
__NAMESPACE_LOCAL_END
#include <libc/local/mntent/getmntent_r.h>
__NAMESPACE_LOCAL_BEGIN
/* >> getmntent(3), getmntent_r(3) */
#define __localdep_getmntent_r __LIBC_LOCAL_NAME(getmntent_r)
#else /* ... */
#undef __local___localdep_getmntent_r_defined
#endif /* !... */
#endif /* !__local___localdep_getmntent_r_defined */
/* Dependency: malloc from stdlib */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined 1
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
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/malloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_malloc __LIBC_LOCAL_NAME(malloc)
#else /* ... */
#undef __local___localdep_malloc_defined
#endif /* !... */
#endif /* !__local___localdep_malloc_defined */
/* >> getmntent(3), getmntent_r(3) */
__LOCAL_LIBC(getmntent) __ATTR_NONNULL((1)) struct mntent *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(getmntent))(__FILE *__stream) {
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
	static struct mntent *__ent = __NULLPTR;
	static char *__buf          = __NULLPTR;
	if (!__ent && (__ent = (struct mntent *)__localdep_malloc(sizeof(struct mntent))) == __NULLPTR)
		return __NULLPTR;
	if (!__buf && (__buf = (char *)__localdep_malloc(512 * sizeof(char))) == __NULLPTR)
		return __NULLPTR;
#else /* __CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign */
	static struct mntent __ent[1];
	static char __buf[512];
#endif /* !__CRT_HAVE_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign */
	return __localdep_getmntent_r(__stream, __ent, __buf, 512);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getmntent_defined
#define __local___localdep_getmntent_defined 1
#define __localdep_getmntent __LIBC_LOCAL_NAME(getmntent)
#endif /* !__local___localdep_getmntent_defined */
#else /* __CRT_HAVE_getmntent_r || __CRT_HAVE___getmntent_r || __CRT_HAVE_fgets || __CRT_HAVE_fgets_unlocked || ((__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked)) */
#undef __local_getmntent_defined
#endif /* !__CRT_HAVE_getmntent_r && !__CRT_HAVE___getmntent_r && !__CRT_HAVE_fgets && !__CRT_HAVE_fgets_unlocked && ((!__CRT_HAVE_fgetc && !__CRT_HAVE_getc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && (!__CRT_DOS || !__CRT_HAVE__filbuf) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock) || (!__CRT_HAVE_ferror && !__CRT_HAVE__IO_ferror && !__CRT_HAVE_ferror_unlocked)) */
#endif /* !__local_getmntent_defined */
