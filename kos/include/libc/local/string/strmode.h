/* HASH CRC-32:0xdffa1c49 */
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
#ifndef __local_strmode_defined
#define __local_strmode_defined
#include <__crt.h>
#include <bits/types.h>
#include <asm/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strmode) __ATTR_OUT(2) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strmode))(__mode_t __mode, char __p[12]) {
	char __ch;

#ifndef __S_IRUSR
#define __S_IRUSR 0400 /* Read by owner. */
#endif /* !__S_IRUSR */
#ifndef __S_IWUSR
#define __S_IWUSR 0200 /* Write by owner. */
#endif /* !__S_IWUSR */
#ifndef __S_IXUSR
#define __S_IXUSR 0100 /* Execute by owner. */
#endif /* !__S_IXUSR */
#ifndef __S_IRWXU
#define __S_IRWXU 0700
#endif /* !__S_IRWXU */
#ifndef __S_IRGRP
#define __S_IRGRP 0040 /* Read by group. */
#endif /* !__S_IRGRP */
#ifndef __S_IWGRP
#define __S_IWGRP 0020 /* Write by group. */
#endif /* !__S_IWGRP */
#ifndef __S_IXGRP
#define __S_IXGRP 0010 /* Execute by group. */
#endif /* !__S_IXGRP */
#ifndef __S_IRWXG
#define __S_IRWXG 0070
#endif /* !__S_IRWXG */
#ifndef __S_IROTH
#define __S_IROTH 0004 /* Read by others. */
#endif /* !__S_IROTH */
#ifndef __S_IWOTH
#define __S_IWOTH 0002 /* Write by others. */
#endif /* !__S_IWOTH */
#ifndef __S_IXOTH
#define __S_IXOTH 0001 /* Execute by others. */
#endif /* !__S_IXOTH */
#ifndef __S_IRWXO
#define __S_IRWXO 0007
#endif /* !__S_IRWXO */

	/* First character: File type */
	__ch = '?';
#ifdef __S_IFMT
	switch (__mode & __S_IFMT) {
#ifdef __S_IFDIR
	case __S_IFDIR:  __ch = 'd'; break;
#endif /* __S_IFDIR */
#ifdef __S_IFCHR
	case __S_IFCHR:  __ch = 'c'; break;
#endif /* __S_IFCHR */
#ifdef __S_IFBLK
	case __S_IFBLK:  __ch = 'b'; break;
#endif /* __S_IFBLK */
#ifdef __S_IFREG
	case __S_IFREG:  __ch = '-'; break;
#endif /* __S_IFREG */
#ifdef __S_IFLNK
	case __S_IFLNK:  __ch = 'l'; break;
#endif /* __S_IFLNK */
#ifdef __S_IFSOCK
	case __S_IFSOCK: __ch = 's'; break;
#endif /* __S_IFSOCK */
#ifdef __S_IFIFO
	case __S_IFIFO:  __ch = 'p'; break; /* p=pipe */
#endif /* __S_IFIFO */
	default: break;
	}
#endif /* __S_IFMT */
	*__p++ = __ch;

	*__p++ = __mode & __S_IRUSR ? 'r' : '-';
	*__p++ = __mode & __S_IWUSR ? 'w' : '-';

#ifdef __S_ISUID
	switch (__mode & (__S_IXUSR | __S_ISUID)) {
	case 0:                 __ch = '-'; break;
	case __S_IXUSR:           __ch = 'x'; break;
	case __S_ISUID:           __ch = 'S'; break;
	case __S_IXUSR | __S_ISUID: __ch = 's'; break;
	default: __builtin_unreachable();
	}
#else /* __S_ISUID */
	__ch = __mode & __S_IXUSR ? 'x' : '-';
#endif /* !__S_ISUID */
	*__p++ = __ch;

	*__p++ = __mode & __S_IRGRP ? 'r' : '-';
	*__p++ = __mode & __S_IWGRP ? 'w' : '-';

#ifdef __S_ISGID
	switch (__mode & (__S_IXGRP | __S_ISGID)) {
	case 0:                 __ch = '-'; break;
	case __S_IXGRP:           __ch = 'x'; break;
	case __S_ISGID:           __ch = 'S'; break;
	case __S_IXGRP | __S_ISGID: __ch = 's'; break;
	default: __builtin_unreachable();
	}
#else /* __S_ISGID */
	__ch = __mode & __S_IXGRP ? 'x' : '-';
#endif /* !__S_ISGID */
	*__p++ = __ch;

	*__p++ = __mode & __S_IROTH ? 'r' : '-';
	*__p++ = __mode & __S_IWOTH ? 'w' : '-';

#ifdef __S_ISVTX
	switch (__mode & (__S_IXOTH | __S_ISVTX)) {
	case 0:                 __ch = '-'; break;
	case __S_IXOTH:           __ch = 'x'; break;
	case __S_ISVTX:           __ch = 'T'; break;
	case __S_IXOTH | __S_ISVTX: __ch = 't'; break;
	default: __builtin_unreachable();
	}
#else /* __S_ISVTX */
	__ch = __mode & __S_IXOTH ? 'x' : '-';
#endif /* !__S_ISVTX */
	*__p++ = __ch;

	/* Always space in this implementation */
	*__p++ = ' ';

	/* NUL-terminate */
	*__p = '\0';
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strmode_defined
#define __local___localdep_strmode_defined
#define __localdep_strmode __LIBC_LOCAL_NAME(strmode)
#endif /* !__local___localdep_strmode_defined */
#endif /* !__local_strmode_defined */
