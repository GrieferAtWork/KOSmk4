/* HASH CRC-32:0xcc938555 */
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
#ifndef __local_mktemp_defined
#define __local_mktemp_defined 1
#include <__crt.h>
#include <features.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <bits/os/stat.h>
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))) || (defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_stat) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))) || (defined(__CRT_HAVE_stat64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_system_mktemp_defined
#define __local___localdep_system_mktemp_defined 1
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/system_mktemp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_system_mktemp __LIBC_LOCAL_NAME(system_mktemp)
#endif /* !__local___localdep_system_mktemp_defined */
__LOCAL_LIBC(mktemp) __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mktemp))(char *__template_) {
	if ((__NAMESPACE_LOCAL_SYM __localdep_system_mktemp)(2, __template_, 0, 0) )
		*__template_ = 0;
	return __template_;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mktemp_defined
#define __local___localdep_mktemp_defined 1
#define __localdep_mktemp __LIBC_LOCAL_NAME(mktemp)
#endif /* !__local___localdep_mktemp_defined */
#else /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) || (__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE__stat32 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE_stat && (!__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) || (__CRT_HAVE_stat64 && (__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) */
#undef __local_mktemp_defined
#endif /* !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) && (!__CRT_HAVE_kstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kstat64 || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE__stat64 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stat64i32 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stati64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || !__USE_FILE_OFFSET64) && (!__CRT_HAVE__stat32i64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || !__USE_FILE_OFFSET64) && (!__CRT_HAVE__stat || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || __USE_FILE_OFFSET64) && (!__CRT_HAVE__stat32 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || __USE_FILE_OFFSET64) && (!__CRT_HAVE_stat || (__USE_FILE_OFFSET64 && !__STAT32_MATCHES_STAT64)) && (!__CRT_HAVE_stat64 || (!__USE_FILE_OFFSET64 && !__STAT32_MATCHES_STAT64)) */
#endif /* !__local_mktemp_defined */
