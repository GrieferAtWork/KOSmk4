/* HASH CRC-32:0xa3d6890b */
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
#ifndef __local_posix_madvise_defined
#define __local_posix_madvise_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_madvise_defined
#define __local___localdep_madvise_defined
#ifdef __CRT_HAVE_madvise
__CREDIRECT(__ATTR_ACCESS_NONE(1),int,__NOTHROW_NCX,__localdep_madvise,(void *__addr, __SIZE_TYPE__ __len, __STDC_INT_AS_UINT_T __advice),madvise,(__addr,__len,__advice))
#elif defined(__CRT_HAVE___madvise)
__CREDIRECT(__ATTR_ACCESS_NONE(1),int,__NOTHROW_NCX,__localdep_madvise,(void *__addr, __SIZE_TYPE__ __len, __STDC_INT_AS_UINT_T __advice),__madvise,(__addr,__len,__advice))
#else /* ... */
#undef __local___localdep_madvise_defined
#endif /* !... */
#endif /* !__local___localdep_madvise_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/mman.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(posix_madvise) __ATTR_ACCESS_NONE(1) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(posix_madvise))(void *__addr, __SIZE_TYPE__ __len, __STDC_INT_AS_UINT_T __advice) {
#if defined(__CRT_HAVE_madvise) || defined(__CRT_HAVE___madvise)
	int __result;
	switch (__advice) {
#if (!defined(__POSIX_MADV_NORMAL) || !defined(__MADV_NORMAL) || __POSIX_MADV_NORMAL == __MADV_NORMAL) && (!defined(__POSIX_MADV_RANDOM) || !defined(__MADV_RANDOM) || __POSIX_MADV_RANDOM == __MADV_RANDOM) && (!defined(__POSIX_MADV_SEQUENTIAL) || !defined(__MADV_SEQUENTIAL) || __POSIX_MADV_SEQUENTIAL == __MADV_SEQUENTIAL) && (!defined(__POSIX_MADV_WILLNEED) || !defined(__MADV_WILLNEED) || __POSIX_MADV_WILLNEED == __MADV_WILLNEED) && (!defined(__POSIX_MADV_DONTNEED) || !defined(__MADV_DONTNEED) || __POSIX_MADV_DONTNEED == __MADV_DONTNEED)




#ifdef __POSIX_MADV_NORMAL
	case __POSIX_MADV_NORMAL:
#endif /* __POSIX_MADV_NORMAL */
#ifdef __POSIX_MADV_RANDOM
	case __POSIX_MADV_RANDOM:
#endif /* __POSIX_MADV_RANDOM */
#ifdef __POSIX_MADV_SEQUENTIAL
	case __POSIX_MADV_SEQUENTIAL:
#endif /* __POSIX_MADV_SEQUENTIAL */
#ifdef __POSIX_MADV_WILLNEED
	case __POSIX_MADV_WILLNEED:
#endif /* __POSIX_MADV_WILLNEED */
#ifdef __POSIX_MADV_DONTNEED
	case __POSIX_MADV_DONTNEED:
#endif /* __POSIX_MADV_DONTNEED */
		break;
#else /* (!__POSIX_MADV_NORMAL || !__MADV_NORMAL || __POSIX_MADV_NORMAL == __MADV_NORMAL) && (!__POSIX_MADV_RANDOM || !__MADV_RANDOM || __POSIX_MADV_RANDOM == __MADV_RANDOM) && (!__POSIX_MADV_SEQUENTIAL || !__MADV_SEQUENTIAL || __POSIX_MADV_SEQUENTIAL == __MADV_SEQUENTIAL) && (!__POSIX_MADV_WILLNEED || !__MADV_WILLNEED || __POSIX_MADV_WILLNEED == __MADV_WILLNEED) && (!__POSIX_MADV_DONTNEED || !__MADV_DONTNEED || __POSIX_MADV_DONTNEED == __MADV_DONTNEED) */
#if defined(__POSIX_MADV_NORMAL) && defined(__MADV_NORMAL)
	case __POSIX_MADV_NORMAL:
		__advice = __MADV_NORMAL;
		break;
#endif /* __POSIX_MADV_NORMAL && __MADV_NORMAL */
#if defined(__POSIX_MADV_RANDOM) && defined(__MADV_RANDOM)
	case __POSIX_MADV_RANDOM:
		__advice = __MADV_RANDOM;
		break;
#endif /* __POSIX_MADV_RANDOM && __MADV_RANDOM */
#if defined(__POSIX_MADV_SEQUENTIAL) && defined(__MADV_SEQUENTIAL)
	case __POSIX_MADV_SEQUENTIAL:
		__advice = __MADV_SEQUENTIAL;
		break;
#endif /* __POSIX_MADV_SEQUENTIAL && __MADV_SEQUENTIAL */
#if defined(__POSIX_MADV_WILLNEED) && defined(__MADV_WILLNEED)
	case __POSIX_MADV_WILLNEED:
		__advice = __MADV_WILLNEED;
		break;
#endif /* __POSIX_MADV_WILLNEED && __MADV_WILLNEED */
#if defined(__POSIX_MADV_DONTNEED) && defined(__MADV_DONTNEED)
	case __POSIX_MADV_DONTNEED:
		__advice = __MADV_DONTNEED;
		break;
#endif /* __POSIX_MADV_DONTNEED && __MADV_DONTNEED */
#endif /* (__POSIX_MADV_NORMAL && __MADV_NORMAL && __POSIX_MADV_NORMAL != __MADV_NORMAL) || (__POSIX_MADV_RANDOM && __MADV_RANDOM && __POSIX_MADV_RANDOM != __MADV_RANDOM) || (__POSIX_MADV_SEQUENTIAL && __MADV_SEQUENTIAL && __POSIX_MADV_SEQUENTIAL != __MADV_SEQUENTIAL) || (__POSIX_MADV_WILLNEED && __MADV_WILLNEED && __POSIX_MADV_WILLNEED != __MADV_WILLNEED) || (__POSIX_MADV_DONTNEED && __MADV_DONTNEED && __POSIX_MADV_DONTNEED != __MADV_DONTNEED) */
	default:
#ifdef __EINVAL
		return __EINVAL;
#else /* __EINVAL */
		return 1;
#endif /* !__EINVAL */
	}
#if defined(__libc_geterrno) && defined(__libc_seterrno)
	{
		__errno_t __saved_errno;
		__saved_errno = __libc_geterrno();
		__result = (__NAMESPACE_LOCAL_SYM __localdep_madvise)(__addr, __len, __advice);
		if __unlikely(__result != 0)
			__result = __libc_geterrno();
		(void)__libc_seterrno(__saved_errno);
	}
#else /* __libc_geterrno && __libc_seterrno */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_madvise)(__addr, __len, __advice);
#ifdef __libc_geterrno
	if __unlikely(__result != 0)
		__result = __libc_geterrno();
#endif /* __libc_geterrno */
#endif /* !__libc_geterrno || !__libc_seterrno */
	return __result;
#else /* __CRT_HAVE_madvise || __CRT_HAVE___madvise */
	switch (__advice) {
#ifdef __POSIX_MADV_NORMAL
	case __POSIX_MADV_NORMAL:
#endif /* __POSIX_MADV_NORMAL */
#ifdef __POSIX_MADV_RANDOM
	case __POSIX_MADV_RANDOM:
#endif /* __POSIX_MADV_RANDOM */
#ifdef __POSIX_MADV_SEQUENTIAL
	case __POSIX_MADV_SEQUENTIAL:
#endif /* __POSIX_MADV_SEQUENTIAL */
#ifdef __POSIX_MADV_WILLNEED
	case __POSIX_MADV_WILLNEED:
#endif /* __POSIX_MADV_WILLNEED */
#ifdef __POSIX_MADV_DONTNEED
	case __POSIX_MADV_DONTNEED:
#endif /* __POSIX_MADV_DONTNEED */
		break;
	default:
#ifdef __EINVAL
		return __EINVAL;
#else /* __EINVAL */
		return 1;
#endif /* !__EINVAL */
	}
	/* Implement as a no-op, since this function is merely meant as a hint */
	__COMPILER_IMPURE();
	(void)__addr;
	(void)__len;
	(void)__advice;
	return 0;
#endif /* !__CRT_HAVE_madvise && !__CRT_HAVE___madvise */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_madvise_defined
#define __local___localdep_posix_madvise_defined
#define __localdep_posix_madvise __LIBC_LOCAL_NAME(posix_madvise)
#endif /* !__local___localdep_posix_madvise_defined */
#endif /* !__local_posix_madvise_defined */
