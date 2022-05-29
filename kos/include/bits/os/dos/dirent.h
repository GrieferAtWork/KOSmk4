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
#ifndef _BITS_OS_DOS_DIRENT_H
#define _BITS_OS_DOS_DIRENT_H 1

#include <__crt.h> /* __CRT_DOS_PRIMARY */
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#ifdef __CRT_DOS_PRIMARY
#define __USE_DOS_DIRENT
#endif /* __CRT_DOS_PRIMARY */

#ifdef __USE_DOS_DIRENT
#include <libc/malloc.h>
#ifndef ____libc_malloc_defined
#undef __USE_DOS_DIRENT
#endif /* !____libc_malloc_defined */
#ifdef __USE_DOS_DIRENT
#include <asm/os/dirent.h>
#include <parts/malloca.h>
#include <libc/errno.h>
#include <libc/string.h>
#endif /* __USE_DOS_DIRENT */

#define __dos_dirent dirent
#ifdef __USE_LARGEFILE64
#define __dirent64 dirent64
#ifdef __USE_STRUCT64_MACRO
#define __dos_dirent64 dirent
#define dirent64       dirent
#else /* __USE_STRUCT64_MACRO */
#define __NEED_STRUCT___DOS_DIRENT64
#define __dos_dirent64 dirent64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_LARGEFILE64 */
#define __dirent64 dirent
#endif /* !__USE_LARGEFILE64 */
#define _DIRENT_HAVE_D_TYPE      1
#define _DIRENT_HAVE_D_BTIME     1
#define _DIRENT_HAVE_D_ATIME     1
#define _DIRENT_HAVE_D_MTIME     1
#define _DIRENT_HAVE_D_FILESIZE  1
#define _DIRENT_MATCHES_DIRENT64 1
#endif /* __USE_DOS_DIRENT */

#ifdef __CC__
__DECL_BEGIN

struct __dos_dirent {
	/* == struct __finddata64_t */
	__UINT32_TYPE__      _d_attrib;   /* Dos-specific file attributes. */
	__UINT32_TYPE__      d_type;      /* File type  (NOTE: In `struct __finddata64_t', this is normally padding) */
	__INT64_TYPE__       d_btime;     /* Birth time */
	__INT64_TYPE__       d_atime;     /* Accessed time */
	__INT64_TYPE__       d_mtime;     /* Modified time */
	__UINT64_TYPE__      d_filesize;  /* File size */
	char                 d_name[260]; /* File name */
};

#ifdef __NEED_STRUCT___DOS_DIRENT64
#undef __NEED_STRUCT___DOS_DIRENT64
struct __dos_dirent64 {
	/* == struct __finddata64_t */
	__UINT32_TYPE__      _d_attrib;   /* Dos-specific file attributes. */
	__UINT32_TYPE__      d_type;      /* File type  (NOTE: In `struct __finddata64_t', this is normally padding) */
	__INT64_TYPE__       d_btime;     /* Birth time */
	__INT64_TYPE__       d_atime;     /* Accessed time */
	__INT64_TYPE__       d_mtime;     /* Modified time */
	__UINT64_TYPE__      d_filesize;  /* File size */
	char                 d_name[260]; /* File name */
};
#endif /* __NEED_STRUCT___DOS_DIRENT64 */


#ifdef __USE_DOS_DIRENT
struct __finddata64_t;
struct _finddata64i32_t;

#ifndef ___findfirst64_defined
#define ___findfirst64_defined
#ifdef __CRT_HAVE__findfirst64
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__intptr_t,__NOTHROW_RPC,_findfirst64,(char const *__restrict __filename, struct __finddata64_t *__restrict __finddata),(__filename,__finddata))
#elif defined(___findfirst64i32_defined)
#define _findfirst64(filename, finddata) _findfirst64i32(filename, (struct _finddata64i32_t *)(finddata))
#elif defined(__CRT_HAVE__findfirst64i32)
#define ___findfirst64i32_defined
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__intptr_t,__NOTHROW_RPC,_findfirst64i32,(char const *__restrict __filename, struct _finddata64i32_t *__restrict __finddata),(__filename,__finddata))
#define _findfirst64(filename, finddata) _findfirst64i32(filename, (struct _finddata64i32_t *)(finddata))
#else /* ... */
#undef ___findfirst64_defined
#endif /* !... */
#endif /* !___findfirst64_defined */

#ifndef ___findnext64_defined
#define ___findnext64_defined
#ifdef __CRT_HAVE__findnext64
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,_findnext64,(__intptr_t __findfd, struct __finddata64_t *__restrict __finddata),(__findfd,__finddata))
#elif defined(___findnext64i32_defined)
#define _findnext64(findfd, finddata) _findnext64i32(findfd, (struct _finddata64i32_t *)(finddata))
#elif defined(__CRT_HAVE__findnext64i32)
#define ___findnext64i32_defined
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,_findnext64i32,(__intptr_t __findfd, struct _finddata64i32_t *__restrict __finddata),(__findfd,__finddata))
#define _findnext64(findfd, finddata) _findnext64i32(findfd, (struct _finddata64i32_t *)(finddata))
#else /* ... */
#undef ___findnext64_defined
#endif /* !... */
#endif /* !___findnext64_defined */

#if !defined(___findclose_defined) && defined(__CRT_HAVE__findclose)
#define ___findclose_defined
__CDECLARE(,int,__NOTHROW_NCX,_findclose,(__intptr_t __findfd),(__findfd))
#endif /* !___findclose_defined && __CRT_HAVE__findclose */


#ifdef ___findfirst64_defined
#define __dos_dirent_findfirst(filename, finddata) _findfirst64(filename, (struct __finddata64_t *)(finddata))
#elif defined(__ENOSYS)
#define __dos_dirent_findfirst(filename, finddata) __libc_seterrno(__ENOSYS)
#else /* ... */
#define __dos_dirent_findfirst(filename, finddata) __libc_seterrno(1)
#endif /* !... */

#ifdef ___findnext64_defined
#define __dos_dirent_findnext(findfd, finddata) _findnext64(findfd, (struct __finddata64_t *)(finddata))
#elif defined(__ENOSYS)
#define __dos_dirent_findnext(findfd, finddata) __libc_seterrno(__ENOSYS)
#else /* ... */
#define __dos_dirent_findnext(findfd, finddata) __libc_seterrno(1)
#endif /* !... */

#ifdef ___findclose_defined
#define __dos_dirent_findclose(findfd) _findclose(findfd)
#else /* ... */
#define __dos_dirent_findclose(findfd) 0
#endif /* !... */

struct __dos_dirp {
	__intptr_t          __dd_findfd;  /* [owned] Find file-handle. */
	struct __dos_dirent __dd_nextent; /* [valid_if(__dd_hasnext)] Next find-data entry */
	__BOOL              __dd_hasnext; /* `__dd_nextent' has been loaded. */
};

/* opendir(3) */
#define __dos_dirent_opendir(name) __dos_dirent_opendir(name)
__LOCAL_LIBC(__dos_dirent_opendir) __ATTR_WUNUSED __ATTR_NONNULL((1)) struct __dos_dirp *
__NOTHROW_RPC(__LIBCCALL __dos_dirent_opendir)(char const *__name) {
	struct __dos_dirp *__result;
	__result = (struct __dos_dirp *)__libc_malloc(sizeof(struct __dos_dirp));
	if __likely(__result) {
		char *__pattern, *__dest;
		__size_t __namelen;
		__namelen = __libc_strlen(__name);
		while (__namelen && (__name[__namelen - 1] == '/' ||
		                     __name[__namelen - 1] == '\\'))
			--__namelen;
		__pattern = (char *)__malloca((__namelen + 3) * sizeof(char));
		if __unlikely(!__pattern)
			goto __err_r;
		__dest    = (char *)__libc_mempcpy(__pattern, __name, __namelen * sizeof(char));
		*__dest++ = '\\';
		*__dest++ = '*';
		*__dest++ = '\0';
		__result->__dd_findfd = __dos_dirent_findfirst(__pattern, &__result->__dd_nextent._d_attrib);
		__freea(__pattern);
		if (__result->__dd_findfd == -1)
			goto __err_r;
		__result->__dd_hasnext = 1;
	}
	return __result;
__err_r:
#ifdef ____libc_free_defined
	__libc_free(__result);
#endif /* ____libc_free_defined */
	return __NULLPTR;
}

/* closedir(3) */
#define __dos_dirent_closedir(dirp) __dos_dirent_closedir((struct __dos_dirp *)(dirp))
__LOCAL_LIBC(__dos_dirent_closedir) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __dos_dirent_closedir)(struct __dos_dirp *__self) {
	int __result = __dos_dirent_findclose(__self->__dd_findfd);
#ifdef ____libc_free_defined
	__libc_free(__self);
#endif /* ____libc_free_defined */
	return __result;
}


/* readdir(3) */
#define __dos_dirent_readdir(dirp) __dos_dirent_readdir((struct __dos_dirp *)(dirp))
__LOCAL_LIBC(__dos_dirent_readdir) __ATTR_NONNULL((1)) struct __dos_dirent *
__NOTHROW_RPC(__LIBCCALL __dos_dirent_readdir)(struct __dos_dirp *__self) {
	if (__self->__dd_hasnext) {
		__self->__dd_hasnext = 0;
	} else {
		if (__dos_dirent_findnext(__self->__dd_findfd, &__self->__dd_nextent._d_attrib) != 0)
			return __NULLPTR;
	}
	__self->__dd_nextent.d_type = __DT_REG;
	if (__self->__dd_nextent._d_attrib & 0x10) /* 0x10: _A_SUBDIR */
		__self->__dd_nextent.d_type = __DT_DIR;
	return (struct __dos_dirent *)&__self->__dd_nextent;
}
#endif /* __USE_DOS_DIRENT */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_DOS_DIRENT_H */
