/* HASH CRC-32:0xce1d3674 */
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
#ifndef __local_strmode_defined
#define __local_strmode_defined 1
#include <__crt.h>
#include <bits/types.h>
#include <asm/stat.h>
__NAMESPACE_LOCAL_BEGIN
/* Generate a file mode representation similar to what's printed by `ls -l'
 * The representation is written to `p', and `mode' is the value as returned
 * by `stat(2)' in `struct stat::st_mode'
 * The format written is:
 *    p[0]  = <mode & S_IFMT>: { S_IFDIR: 'd', S_IFCHR: 'c', S_IFBLK:  'b',
 *                               S_IFREG: '-', S_IFLNK: 'l', S_IFSOCK: 's',
 *                               S_IFIFO: 'p' }, else: '?';
 *    p[1]  = mode & S_IRUSR ? 'r' : '-';
 *    p[2]  = mode & S_IWUSR ? 'w' : '-';
 *    p[3]  = <mode & S_IXUSR | S_ISUID>: { 0: '-', S_IXUSR: 'x', S_ISUID: 'S',
 *                                          S_IXUSR | S_ISUID: 's' };
 *    p[4]  = mode & S_IRGRP ? 'r' : '-';
 *    p[5]  = mode & S_IWGRP ? 'w' : '-';
 *    p[6]  = <mode & S_IXGRP | S_ISGID>: { 0: '-', S_IXGRP: 'x', S_ISGID: 'S',
 *                                          S_IXGRP | S_ISGID: 's' };
 *    p[7]  = mode & S_IROTH ? 'r' : '-';
 *    p[8]  = mode & S_IWOTH ? 'w' : '-';
 *    p[9]  = <mode & S_IXOTH | S_ISVTX>: { 0: '-', S_IXOTH: 'x', S_ISVTX: 'T',
 *                                          S_IXOTH | S_ISVTX: 't' };
 *    p[10] = ' '; // '+', if "alternate or additional access control
 *                 //          methods associated with the inode"
 *    p[11] = '\0'; */
__LOCAL_LIBC(strmode) __ATTR_NONNULL((2)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strmode))(__mode_t __mode, char __p[12]) {
	char __ch;
	/* First character: File type */
	__ch = '?';
#ifdef __S_IFMT
	switch (__mode & __S_IFMT) {
#ifdef __S_IFDIR
	case __S_IFDIR:  __ch = 'd'; break;
#endif /* S_IFDIR */
#ifdef __S_IFCHR
	case __S_IFCHR:  __ch = 'c'; break;
#endif /* S_IFCHR */
#ifdef __S_IFBLK
	case __S_IFBLK:  __ch = 'b'; break;
#endif /* S_IFBLK */
#ifdef __S_IFREG
	case __S_IFREG:  __ch = '-'; break;
#endif /* S_IFREG */
#ifdef __S_IFLNK
	case __S_IFLNK:  __ch = 'l'; break;
#endif /* S_IFLNK */
#ifdef __S_IFSOCK
	case __S_IFSOCK: __ch = 's'; break;
#endif /* S_IFSOCK */
#ifdef __S_IFIFO
	case __S_IFIFO:  __ch = 'p'; break; /* p=pipe */
#endif /* S_IFIFO */
	default: break;
	}
#endif /* S_IFMT */
	*__p++ = __ch;

#ifdef __S_IRUSR
	*__p++ = __mode & __S_IRUSR ? 'r' : '-';
#else /* S_IRUSR */
	*__p++ = '-';
#endif /* !S_IRUSR */

#ifdef __S_IWUSR
	*__p++ = __mode & __S_IWUSR ? 'w' : '-';
#else /* S_IWUSR */
	*__p++ = '-';
#endif /* !S_IWUSR */

#if defined(__S_IXUSR) && defined(__S_ISUID)
	switch (__mode & (__S_IXUSR | __S_ISUID)) {
	case 0:                 __ch = '-'; break;
	case __S_IXUSR:           __ch = 'x'; break;
	case __S_ISUID:           __ch = 'S'; break;
	case __S_IXUSR | __S_ISUID: __ch = 's'; break;
	default: __builtin_unreachable();
	}
#elif defined(__S_IXUSR)
	__ch = __mode & __S_IXUSR ? 'x' : '-';
#elif defined(__S_ISUID)
	__ch = __mode & __S_ISUID ? 'S' : '-';
#else /* S_IWUSR */
	__ch = '-';
#endif /* !S_IWUSR */
	*__p++ = __ch;

#ifdef __S_IRGRP
	*__p++ = __mode & __S_IRGRP ? 'r' : '-';
#else /* S_IRGRP */
	*__p++ = '-';
#endif /* !S_IRGRP */

#ifdef __S_IWGRP
	*__p++ = __mode & __S_IWGRP ? 'w' : '-';
#else /* S_IWGRP */
	*__p++ = '-';
#endif /* !S_IWGRP */

#if defined(__S_IXGRP) && defined(__S_ISGID)
	switch (__mode & (__S_IXGRP | __S_ISGID)) {
	case 0:                 __ch = '-'; break;
	case __S_IXGRP:           __ch = 'x'; break;
	case __S_ISGID:           __ch = 'S'; break;
	case __S_IXGRP | __S_ISGID: __ch = 's'; break;
	default: __builtin_unreachable();
	}
#elif defined(__S_IXGRP)
	__ch = __mode & __S_IXGRP ? 'x' : '-';
#elif defined(__S_ISGID)
	__ch = __mode & __S_ISGID ? 'S' : '-';
#else /* S_IWUSR */
	__ch = '-';
#endif /* !S_IWUSR */
	*__p++ = __ch;

#ifdef __S_IROTH
	*__p++ = __mode & __S_IROTH ? 'r' : '-';
#else /* S_IROTH */
	*__p++ = '-';
#endif /* !S_IROTH */

#ifdef __S_IWOTH
	*__p++ = __mode & __S_IWOTH ? 'w' : '-';
#else /* S_IWOTH */
	*__p++ = '-';
#endif /* !S_IWOTH */

#if defined(__S_IXOTH) && defined(__S_ISVTX)
	switch (__mode & (__S_IXOTH | __S_ISVTX)) {
	case 0:                 __ch = '-'; break;
	case __S_IXOTH:           __ch = 'x'; break;
	case __S_ISVTX:           __ch = 'T'; break;
	case __S_IXOTH | __S_ISVTX: __ch = 't'; break;
	default: __builtin_unreachable();
	}
#elif defined(__S_IXOTH)
	__ch = __mode & __S_IXOTH ? 'x' : '-';
#elif defined(__S_ISVTX)
	__ch = __mode & __S_ISVTX ? 'T' : '-';
#else /* S_IWUSR */
	__ch = '-';
#endif /* !S_IWUSR */
	*__p++ = __ch;

	/* Always space in this implementation */
	*__p++ = ' ';

	/* NUL-terminate */
	*__p = '\0';
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strmode_defined
#define __local___localdep_strmode_defined 1
#define __localdep_strmode __LIBC_LOCAL_NAME(strmode)
#endif /* !__local___localdep_strmode_defined */
#endif /* !__local_strmode_defined */
