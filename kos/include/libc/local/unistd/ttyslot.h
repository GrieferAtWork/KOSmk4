/* HASH CRC-32:0x42267c47 */
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
#ifndef __local_ttyslot_defined
#define __local_ttyslot_defined
#include <__crt.h>
#include <paths.h>
#include <asm/os/fcntl.h>
#include <bits/os/dirent.h>
#include <features.h>
#include <asm/os/oflags.h>
#include <bits/os/stat.h>
#if (defined(__CRT_HAVE_ttyname) || defined(__CRT_HAVE___ttyname) || defined(__CRT_HAVE_ttyname_r) || defined(__CRT_HAVE_frealpath4) || ((defined(__CRT_HAVE_opendir) || defined(__CRT_HAVE___libc_opendir) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_opendirat) || defined(__CRT_HAVE_fopendirat) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || defined(__USE_DOS_DIRENT)) && ((defined(__CRT_HAVE_readdirk) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_readdirk64) && defined(__CRT_KOS)) || (defined(__CRT_HAVE_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE___libc_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_readdir64) && !defined(__CRT_KOS)) || (defined(__USE_DOS_DIRENT) && defined(_DIRENT_MATCHES_DIRENT64))) && ((defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE_fstat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_fstat64)) && ((defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE_lstat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_lstat64)) && defined(_PATH_DEV))) && defined(__CRT_HAVE_setttyent) && defined(__CRT_HAVE_getttyent)
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_endttyent_defined) && defined(__CRT_HAVE_endttyent)
#define __local___localdep_endttyent_defined
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_endttyent,(void),endttyent,())
#endif /* !__local___localdep_endttyent_defined && __CRT_HAVE_endttyent */
#ifndef __local___localdep_getttyent_defined
#define __local___localdep_getttyent_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/db/ttyent.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,struct ttyent *,__NOTHROW_RPC_KOS,__localdep_getttyent,(void),getttyent,())
#endif /* !__local___localdep_getttyent_defined */
#ifndef __local___localdep_setttyent_defined
#define __local___localdep_setttyent_defined
__CREDIRECT(,int,__NOTHROW_RPC_KOS,__localdep_setttyent,(void),setttyent,())
#endif /* !__local___localdep_setttyent_defined */
#ifndef __local___localdep_strcmp_defined
#define __local___localdep_strcmp_defined
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcmp __LIBC_LOCAL_NAME(strcmp)
#endif /* !... */
#endif /* !__local___localdep_strcmp_defined */
#ifndef __local___localdep_strrchrnul_defined
#define __local___localdep_strrchrnul_defined
#ifdef __CRT_HAVE_strrchrnul
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strrchrnul,(char const *__restrict __haystack, int __needle),strrchrnul,(__haystack,__needle))
#else /* __CRT_HAVE_strrchrnul */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strrchrnul.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strrchrnul __LIBC_LOCAL_NAME(strrchrnul)
#endif /* !__CRT_HAVE_strrchrnul */
#endif /* !__local___localdep_strrchrnul_defined */
#ifndef __local___localdep_ttyname_defined
#define __local___localdep_ttyname_defined
#ifdef __CRT_HAVE_ttyname
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,char *,__NOTHROW_RPC,__localdep_ttyname,(__fd_t __fd),ttyname,(__fd))
#elif defined(__CRT_HAVE___ttyname)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,char *,__NOTHROW_RPC,__localdep_ttyname,(__fd_t __fd),__ttyname,(__fd))
#elif defined(__CRT_HAVE_ttyname_r) || defined(__CRT_HAVE_frealpath4) || ((defined(__CRT_HAVE_opendir) || defined(__CRT_HAVE___libc_opendir) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_opendirat) || defined(__CRT_HAVE_fopendirat) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || defined(__USE_DOS_DIRENT)) && ((defined(__CRT_HAVE_readdirk) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_readdirk64) && defined(__CRT_KOS)) || (defined(__CRT_HAVE_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE___libc_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_readdir64) && !defined(__CRT_KOS)) || (defined(__USE_DOS_DIRENT) && defined(_DIRENT_MATCHES_DIRENT64))) && ((defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE_fstat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_fstat64)) && ((defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE_lstat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_lstat64)) && defined(_PATH_DEV))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/ttyname.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ttyname __LIBC_LOCAL_NAME(ttyname)
#else /* ... */
#undef __local___localdep_ttyname_defined
#endif /* !... */
#endif /* !__local___localdep_ttyname_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <bits/types.h>
#include <asm/os/stdio.h>
#include <bits/crt/db/ttyent.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ttyslot) __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ttyslot))(void) {
	__fd_t __fd;
	__PRIVATE_FOREACH_STDFILENO(__fd) {
		char const *__tnam;
		int __result;
		struct ttyent *__tty;
		if ((__tnam = (__NAMESPACE_LOCAL_SYM __localdep_ttyname)(__fd)) == __NULLPTR)
			continue;
		__tnam = (__NAMESPACE_LOCAL_SYM __localdep_strrchrnul)(__tnam, '/') + 1;
		(__NAMESPACE_LOCAL_SYM __localdep_setttyent)();
		for (__result = 1; (__tty = (__NAMESPACE_LOCAL_SYM __localdep_getttyent)()) != __NULLPTR; ++__result) {
			if ((__NAMESPACE_LOCAL_SYM __localdep_strcmp)(__tty->ty_name, __tnam) == 0) {
#ifdef __CRT_HAVE_endttyent
				(__NAMESPACE_LOCAL_SYM __localdep_endttyent)();
#endif /* __CRT_HAVE_endttyent */
				return __result;
			}
		}
#ifdef __CRT_HAVE_endttyent
		(__NAMESPACE_LOCAL_SYM __localdep_endttyent)();
#endif /* __CRT_HAVE_endttyent */
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ttyslot_defined
#define __local___localdep_ttyslot_defined
#define __localdep_ttyslot __LIBC_LOCAL_NAME(ttyslot)
#endif /* !__local___localdep_ttyslot_defined */
#else /* (__CRT_HAVE_ttyname || __CRT_HAVE___ttyname || __CRT_HAVE_ttyname_r || __CRT_HAVE_frealpath4 || ((__CRT_HAVE_opendir || __CRT_HAVE___libc_opendir || (__AT_FDCWD && (__CRT_HAVE_opendirat || __CRT_HAVE_fopendirat || (__CRT_HAVE_fdopendir && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || (__CRT_HAVE_fdopendir && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || __USE_DOS_DIRENT) && ((__CRT_HAVE_readdirk && __CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_readdirk64 && __CRT_KOS) || (__CRT_HAVE_readdir && !__CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE___libc_readdir && !__CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_readdir64 && !__CRT_KOS) || (__USE_DOS_DIRENT && _DIRENT_MATCHES_DIRENT64)) && ((__CRT_HAVE_kfstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__fstat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE__fstat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE_fstat && __STAT32_MATCHES_STAT64) || __CRT_HAVE_fstat64) && ((__CRT_HAVE_klstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_klstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE_lstat && __STAT32_MATCHES_STAT64) || __CRT_HAVE_lstat64) && _PATH_DEV)) && __CRT_HAVE_setttyent && __CRT_HAVE_getttyent */
#undef __local_ttyslot_defined
#endif /* (!__CRT_HAVE_ttyname && !__CRT_HAVE___ttyname && !__CRT_HAVE_ttyname_r && !__CRT_HAVE_frealpath4 && ((!__CRT_HAVE_opendir && !__CRT_HAVE___libc_opendir && (!__AT_FDCWD || (!__CRT_HAVE_opendirat && !__CRT_HAVE_fopendirat && (!__CRT_HAVE_fdopendir || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)))) && (!__CRT_HAVE_fdopendir || (!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)))) && !__USE_DOS_DIRENT) || ((!__CRT_HAVE_readdirk || !__CRT_KOS || !_DIRENT_MATCHES_DIRENT64) && (!__CRT_HAVE_readdirk64 || !__CRT_KOS) && (!__CRT_HAVE_readdir || __CRT_KOS || !_DIRENT_MATCHES_DIRENT64) && (!__CRT_HAVE___libc_readdir || __CRT_KOS || !_DIRENT_MATCHES_DIRENT64) && (!__CRT_HAVE_readdir64 || __CRT_KOS) && (!__USE_DOS_DIRENT || !_DIRENT_MATCHES_DIRENT64)) || ((!__CRT_HAVE_kfstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kfstat64 || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE__fstat64 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__fstat64i32 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__fstati64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64) && (!__CRT_HAVE__fstat32i64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64) && (!__CRT_HAVE_fstat || !__STAT32_MATCHES_STAT64) && !__CRT_HAVE_fstat64) || ((!__CRT_HAVE_klstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_klstat64 || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE__stat64 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stat64i32 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stati64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64) && (!__CRT_HAVE__stat32i64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64) && (!__CRT_HAVE_lstat || !__STAT32_MATCHES_STAT64) && !__CRT_HAVE_lstat64) || !_PATH_DEV)) || !__CRT_HAVE_setttyent || !__CRT_HAVE_getttyent */
#endif /* !__local_ttyslot_defined */
