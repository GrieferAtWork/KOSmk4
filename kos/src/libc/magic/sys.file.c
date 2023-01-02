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
%(c_prefix){
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/file.h) */
/* (#) Portability: DJGPP         (/include/sys/file.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/file.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/file.h) */
/* (#) Portability: FreeBSD       (/sys/sys/file.h) */
/* (#) Portability: GNU C Library (/misc/sys/file.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/sys/file.h) */
/* (#) Portability: NetBSD        (/sys/sys/file.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/file.h) */
/* (#) Portability: OpenBSD       (/sys/sys/file.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/file.h) */
/* (#) Portability: diet libc     (/include/sys/file.h) */
/* (#) Portability: libc4/5       (/include/sys/file.h) */
/* (#) Portability: mintlib       (/include/sys/file.h) */
/* (#) Portability: musl libc     (/include/sys/file.h) */
/* (#) Portability: uClibc        (/include/sys/file.h) */
}

%[define_replacement(fd_t = __fd_t)]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/os/fcntl.h> /* __LOCK_* */
)]%[insert:prefix(
#include <asm/os/stdio.h> /* __SEEK_* */
)]%[insert:prefix(
#include <bits/types.h>   /* fd_t */
)]%{

#ifdef __USE_GLIBC_BLOAT
#include <fcntl.h>
#endif /* __USE_GLIBC_BLOAT */

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


#if !defined(L_SET) && defined(__SEEK_SET)
#define L_SET  __SEEK_SET /* Seek from beginning of file. */
#endif /* !L_SET && __SEEK_SET */
#if !defined(L_CURR) && defined(__SEEK_CUR)
#define L_CURR __SEEK_CUR /* Seek from current position. */
#endif /* !L_CURR && __SEEK_CUR */
#if !defined(L_INCR) && defined(__SEEK_CUR)
#define L_INCR __SEEK_CUR /* Seek from current position. */
#endif /* !L_INCR && __SEEK_CUR */
#if !defined(L_XTND) && defined(__SEEK_END)
#define L_XTND __SEEK_END /* Seek from end of file. */
#endif /* !L_XTND && __SEEK_END */


/* Shared lock. */
#if !defined(LOCK_SH) && defined(__LOCK_SH)
#define LOCK_SH __LOCK_SH
#endif /* !LOCK_SH && __LOCK_SH */

/* Exclusive lock. */
#if !defined(LOCK_EX) && defined(__LOCK_EX)
#define LOCK_EX __LOCK_EX
#endif /* !LOCK_EX && __LOCK_EX */

/* Or'd with one of the above to prevent blocking. */
#if !defined(LOCK_NB) && defined(__LOCK_NB)
#define LOCK_NB __LOCK_NB
#endif /* !LOCK_NB && __LOCK_NB */

/* Remove lock. */
#if !defined(LOCK_UN) && defined(__LOCK_UN)
#define LOCK_UN __LOCK_UN
#endif /* !LOCK_UN && __LOCK_UN */


#ifdef __CC__
__SYSDECL_BEGIN

}

@@>> flock(2)
@@Apply or remove an advisory lock, according to `operation', on the file `fd' refers to
[[cp, decl_include("<features.h>", "<bits/types.h>")]]
[[export_alias("__flock")]]
/* The following as libc4/5 aliases, though behave slightly different.
 * These won't try to emulate the system call if -ENOSYS is  returned.
 * As such, only export with these aliases, but don't import! */
[[export_as("syscall_flock", "__syscall_flock", "__libc_syscall_flock")]]
int flock($fd_t fd, __STDC_INT_AS_UINT_T operation);

%{

__SYSDECL_END
#endif /* __CC__ */

}
