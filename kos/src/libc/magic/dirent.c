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

%[define_replacement(fd_t       = __fd_t)]
%[define_replacement(off_t      = "__FS_TYPE(off)")]
%[define_replacement(pos_t      = "__FS_TYPE(pos)")]
%[define_replacement(off32_t    = __off32_t)]
%[define_replacement(off64_t    = __off64_t)]
%[define_replacement(pos32_t    = __pos32_t)]
%[define_replacement(pos64_t    = __pos64_t)]
%[define_replacement(atflag_t   = __atflag_t)]
%[define_replacement(oflag_t    = __oflag_t)]
%[define_replacement(DIR        = "struct __dirstream")]
%[default_impl_section(".text.crt.fs.dir")]


%{
#include <features.h>

#include <asm/dirent.h>
#include <bits/dirent.h>
#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __USE_MISC
#ifndef DT_UNKNOWN
/*[[[enum]]]*/
#ifdef __CC__
enum {
	DT_UNKNOWN = __DT_UNKNOWN,
	DT_FIFO    = __DT_FIFO,
	DT_CHR     = __DT_CHR,
	DT_DIR     = __DT_DIR,
	DT_BLK     = __DT_BLK,
	DT_REG     = __DT_REG,
	DT_LNK     = __DT_LNK,
	DT_SOCK    = __DT_SOCK,
	DT_WHT     = __DT_WHT
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define DT_UNKNOWN DT_UNKNOWN
#define DT_FIFO    DT_FIFO
#define DT_CHR     DT_CHR
#define DT_DIR     DT_DIR
#define DT_BLK     DT_BLK
#define DT_REG     DT_REG
#define DT_LNK     DT_LNK
#define DT_SOCK    DT_SOCK
#define DT_WHT     DT_WHT
#else /* __COMPILER_PREFERR_ENUMS */
#define DT_UNKNOWN __DT_UNKNOWN
#define DT_FIFO    __DT_FIFO
#define DT_CHR     __DT_CHR
#define DT_DIR     __DT_DIR
#define DT_BLK     __DT_BLK
#define DT_REG     __DT_REG
#define DT_LNK     __DT_LNK
#define DT_SOCK    __DT_SOCK
#define DT_WHT     __DT_WHT
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* !DT_UNKNOWN */

/* Convert between stat structure types and directory types. */
#ifndef IFTODT
#define IFTODT(mode)    __IFTODT(mode)
#define DTTOIF(dirtype) __DTTOIF(dirtype)
#endif /* !IFTODT */

#if defined(__USE_XOPEN2K8) && !defined(MAXNAMLEN)
#define MAXNAMLEN    255 /* == 'NAME_MAX' from <linux/limits.h> */
#endif /* __USE_XOPEN2K8 && !MAXNAMLEN */
#endif /* __USE_MISC */


#ifdef __CC__
#ifdef _DIRENT_HAVE_D_NAMLEN
#define _D_EXACT_NAMLEN(d) ((d)->d_namlen)
#define _D_ALLOC_NAMLEN(d) (_D_EXACT_NAMLEN(d) + 1)
#else /* _DIRENT_HAVE_D_NAMLEN */
__SYSDECL_END
#include <libc/string.h>
__SYSDECL_BEGIN
#define _D_EXACT_NAMLEN(d) __libc_strlen((d)->d_name)
#ifdef _DIRENT_HAVE_D_RECLEN
#define _D_ALLOC_NAMLEN(d) (((char *)(d) + (d)->d_reclen) - &(d)->d_name[0])
#else /* _DIRENT_HAVE_D_RECLEN */
#define _D_ALLOC_NAMLEN(d) (sizeof((d)->d_name) > 1 ? sizeof((d)->d_name) : _D_EXACT_NAMLEN(d) + 1)
#endif /* !_DIRENT_HAVE_D_RECLEN */
#endif /* !_DIRENT_HAVE_D_NAMLEN */

#ifdef __USE_XOPEN
#ifndef __ino_t_defined
#define __ino_t_defined 1
typedef __typedef_ino_t ino_t; /* INode number */
#endif /* !__ino_t_defined */
#ifdef __USE_LARGEFILE64
#ifndef __ino64_t_defined
#define __ino64_t_defined 1
typedef __ino64_t ino64_t; /* INode number */
#endif /* !__ino64_t_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __DIR_defined
#define __DIR_defined 1
typedef struct __dirstream DIR;
#endif /* !__DIR_defined */

}

%[define(DEFINE_STRUCT_DIRSTREAM = struct __dirstream;)]

@@Open and return a new directory stream for reading, referring to `name'
[[cp, ATTR_WUNUSED, decl_prefix(DEFINE_STRUCT_DIRSTREAM)]]
[[userimpl, requires(defined(__CRT_AT_FDCWD) && $has_function(opendirat))]]
DIR *opendir([[nonnull]] char const *name) {
	/* TODO: Emulate using DOS's _find* functions */
	/* TODO: Emulate using fdopendir(open(name, 0)) */
	return opendirat(__CRT_AT_FDCWD, name);
}


%
%#if defined(__USE_KOS) && defined(__USE_ATFILE)
@@Directory-handle-relative, and flags-enabled versions of `opendir(3)'
[[cp, ATTR_WUNUSED, decl_prefix(DEFINE_STRUCT_DIRSTREAM)]]
[[userimpl, requires($has_function(fdopendir) && $has_function(openat))]]
DIR *fopendirat($fd_t dirfd, [[nonnull]] char const *name, $oflag_t oflags) {
	DIR *result;
	fd_t fd = openat(dirfd, name, oflags);
	if unlikely(fd < 0)
		return NULL;
	result = fdopendir(fd);
@@pp_if $has_function(close)@@
	if unlikely(!result)
		close(fd);
@@pp_endif@@
	return result;
}

@@Directory-handle-relative, and flags-enabled versions of `opendir(3)'
[[cp, ATTR_WUNUSED, decl_prefix(DEFINE_STRUCT_DIRSTREAM)]]
[[userimpl, requires_function(fopendirat)]]
DIR *opendirat($fd_t dirfd, [[nonnull]] char const *name) {
	return fopendirat(dirfd, name, 0);
}
%#endif /* __USE_KOS && __USE_ATFILE */

%
@@Close a directory stream previously returned by `opendir(3)' and friends
[[decl_prefix(DEFINE_STRUCT_DIRSTREAM)]]
int closedir([[nonnull]] DIR *dirp);


%
%#ifdef __USE_BSD
@@Same as `closedir()', but instead of closing the underlying file descriptor, return it
[[ATTR_WUNUSED, decl_prefix(DEFINE_STRUCT_DIRSTREAM)]]
$fd_t fdclosedir([[nonnull]] DIR *dirp);
%#endif /* __USE_BSD */

%
@@Read and return the next pending directory entry of the given directory stream `DIRP'
@@@EXCEPT: Returns NULL for end-of-directory; throws an error if something else went wrong
[[cp, decl_prefix(DEFINE_STRUCT_DIRSTREAM), no_crt_self_import]]
[[if(!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64)), preferred_alias("readdir")]]
[[if(defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64)), preferred_alias("readdir64")]]
struct dirent *readdir([[nonnull]] DIR *__restrict dirp);

%
@@Rewind the given directory stream in such a way that the next call
@@to `readdir(3)' will once again return the first directory entry
[[decl_prefix(DEFINE_STRUCT_DIRSTREAM)]]
void rewinddir([[nonnull]] DIR *__restrict dirp);

%
%#ifdef __USE_XOPEN2K8
@@Create a new directory stream by inheriting the given `FD' as stream handle
[[ATTR_WUNUSED, decl_prefix(DEFINE_STRUCT_DIRSTREAM)]]
DIR *fdopendir($fd_t fd);
%#endif /* __USE_XOPEN2K8 */

%
%#ifdef __USE_LARGEFILE64
@@64-bit equivalent of `readdir(3)'
@@@EXCEPT: Returns NULL for end-of-directory; throws an error if something else went wrong
[[cp, dirent64_variant_of(readdir), decl_prefix(DEFINE_STRUCT_DIRSTREAM)]]
struct dirent64 *readdir64([[nonnull]] DIR *__restrict dirp);
%#endif /* __USE_LARGEFILE64 */


%#ifdef __USE_POSIX
@@Reentrant version of `readdir(3)' (Using this is not recommended in KOS)
[[cp, decl_prefix(DEFINE_STRUCT_DIRSTREAM), no_crt_self_import]]
[[if(!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64)), preferred_alias("readdir_r")]]
[[if(defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64)), preferred_alias("readdir64_r")]]
int readdir_r([[nonnull]] DIR *__restrict dirp,
              [[nonnull]] struct dirent *__restrict entry,
              [[nonnull]] struct dirent **__restrict result);

%
%#ifdef __USE_LARGEFILE64
@@NOTE: This ~reentrant~ version of readdir() is strongly discouraged from being used in KOS, as the
@@      kernel does not impose a limit on the length of a single directory entry name (s.a. 'kreaddir')
@@>> Instead, simply use `readdir()' / `readdir64()', which will automatically (re-)allocate an internal,
@@   per-directory buffer of sufficient size to house any directory entry (s.a.: `READDIR_DEFAULT')
[[cp, decl_prefix(DEFINE_STRUCT_DIRSTREAM), dirent64_variant_of(readdir_r)]]
int readdir64_r([[nonnull]] DIR *__restrict dirp,
                [[nonnull]] struct dirent64 *__restrict entry,
                [[nonnull]] struct dirent64 **__restrict result);
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_POSIX */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN)

@@Get the directory stream position
[[decl_prefix(DEFINE_STRUCT_DIRSTREAM)]]
void seekdir([[nonnull]] DIR *__restrict dirp, long int pos);

@@Get the directory stream position
[[decl_prefix(DEFINE_STRUCT_DIRSTREAM)]]
long int telldir([[nonnull]] DIR *__restrict dirp);

%#endif /* __USE_MISC || __USE_XOPEN */

%[define_c_language_keyword(__KOS_FIXED_CONST)]

%
%#ifdef __USE_XOPEN2K8
@@Return the underlying file descriptor of the given directory stream
[[decl_include("<features.h>")]]
[[ATTR_PURE, decl_prefix(DEFINE_STRUCT_DIRSTREAM)]]
$fd_t dirfd([[nonnull]] DIR __KOS_FIXED_CONST *__restrict dirp);


%typedef int (*__scandir_selector_t)(struct dirent const *);
%typedef int (*__scandir_cmp_t)(struct dirent const **, struct dirent const **);

%
@@Scan a directory `DIR' for all contained directory entries
[[cp, userimpl, requires(defined(__CRT_AT_FDCWD) && $has_function(scandirat)), no_crt_self_import]]
[[if(!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64)), preferred_alias("scandir")]]
[[if(defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64)), preferred_alias("scandir64")]]
int scandir([[nonnull]] char const *__restrict dir,
            [[nonnull]] struct dirent ***__restrict namelist,
            __scandir_selector_t selector, __scandir_cmp_t cmp) {
	return scandirat(__CRT_AT_FDCWD, dir, namelist, selector, cmp);
}

%
@@Sort the 2 given directory entries `E1' and `E2' the same way `strcmp(3)' would
[[ATTR_PURE, no_crt_self_import, impl_include("<bits/dirent.h>")]]
[[if(!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64)), preferred_alias("alphasort")]]
[[if(defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64)), preferred_alias("alphasort64")]]
int alphasort([[nonnull]] struct dirent const **e1,
              [[nonnull]] struct dirent const **e2) {
	return strcoll((*e1)->@d_name@, (*e2)->@d_name@);
}
%#ifdef __USE_LARGEFILE64
@@64-bit variant of `alphasort()'
[[ATTR_PURE, dirent64_variant_of(alphasort), impl_include("<bits/dirent.h>")]]
int alphasort64([[nonnull]] struct dirent64 const **e1,
                [[nonnull]] struct dirent64 const **e2) {
	return strcoll((*e1)->@d_name@, (*e2)->@d_name@);
}
%#endif /* __USE_LARGEFILE64 */

%
%#ifdef __USE_GNU
@@Scan a directory `DIRFD:DIR' for all contained directory entries
[[cp, no_crt_self_import]]
[[if(!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64)), preferred_alias("scandirat")]]
[[if(defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64)), preferred_alias("scandirat64")]]
int scandirat($fd_t dirfd, [[nonnull]] char const *__restrict dir,
              [[nonnull]] struct dirent ***__restrict namelist,
              __scandir_selector_t selector, __scandir_cmp_t cmp);

%
%#ifdef __USE_LARGEFILE64
%typedef int (*__scandir64_selector_t)(struct dirent64 const *);
%typedef int (*__scandir64_cmp_t)(struct dirent64 const **, struct dirent64 const **);

@@64-bit variant of `scandir()'
[[cp, dirent64_variant_of(scandir)]]
[[userimpl, requires(defined(__CRT_AT_FDCWD) && $has_function(scandirat64))]]
int scandir64([[nonnull]] char const *__restrict dir,
              [[nonnull]] struct dirent64 ***__restrict namelist,
              __scandir64_selector_t selector, __scandir64_cmp_t cmp) {
	return scandirat64(__CRT_AT_FDCWD, dir, namelist, selector, cmp);
}

@@64-bit variant of `scandirat()'
[[cp, dirent64_variant_of(scandirat)]]
int scandirat64($fd_t dirfd, [[nonnull]] char const *__restrict dir,
                [[nonnull]] struct dirent64 ***__restrict namelist,
                __scandir64_selector_t selector, __scandir64_cmp_t cmp);

%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_GNU */
%#endif /* __USE_XOPEN2K8 */

%
%#ifdef __USE_MISC
@@Linux's underlying system call for reading the entries of a directory
[[cp, no_crt_self_import]]
[[if(!defined(__USE_FILE_OFFSET64) || (defined(_DIRENT_MATCHES_DIRENT64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)), preferred_alias("getdirentries")]]
[[if(defined(__USE_FILE_OFFSET64) || (defined(_DIRENT_MATCHES_DIRENT64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)), preferred_alias("getdirentries64")]]
$ssize_t getdirentries($fd_t fd, [[nonnull]] char *__restrict buf,
                       size_t nbytes, [[nonnull]] $off_t *__restrict basep);

%#ifdef __USE_LARGEFILE64
@@64-bit variant of `getdirentries()'
[[dirent64_variant_of(getdirentries), cp]]
$ssize_t getdirentries64($fd_t fd, [[nonnull]] char *__restrict buf, size_t nbytes,
                         [[nonnull]] $off64_t *__restrict basep);
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_MISC */

%
%#ifdef __USE_GNU
@@Sort the 2 given directory entries `E1' and `E2' the same way `strvercmp(3)' would.
[[ATTR_PURE, no_crt_self_import, impl_include("<bits/dirent.h>")]]
[[if(!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64)), preferred_alias("versionsort")]]
[[if(defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64)), preferred_alias("versionsort64")]]
int versionsort([[nonnull]] struct dirent const **e1,
                [[nonnull]] struct dirent const **e2) {
	return strverscmp((*e1)->@d_name@, (*e2)->@d_name@);
}
%#ifdef __USE_LARGEFILE64
@@64-bit variant of `versionsort()'
[[ATTR_PURE, dirent64_variant_of(versionsort), impl_include("<bits/dirent.h>")]]
int versionsort64([[nonnull]] struct dirent64 const **e1,
                  [[nonnull]] struct dirent64 const **e2) {
	return strverscmp((*e1)->@d_name@, (*e2)->@d_name@);
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_GNU */

%
%#if defined(__USE_KOS) && defined(__KOS__)
@@The KOS-specific system call for reading a single directory entry
@@from a file descriptor referring to an open directory stream.
@@@param: MODE: One of `READDIR_*' (See below)
@@@return: * : The actually required buffer size for the directory entry (in bytes)
@@             NOTE: When `READDIR_DEFAULT' was passed for `MODE', the directory
@@                   stream will only be advanced when this value is >= 'BUFSIZE'
@@@return: 0 : The end of the directory has been reached.
@@@return: -1: Failed to read a directory entry for some reason (s.a.: `errno')
[[if(defined(_DIRENT_MATCHES_DIRENT64)), alias("kreaddir64")]]
[[cp, ATTR_WUNUSED, userimpl, requires_function(kreaddirf)]]
$ssize_t kreaddir($fd_t fd, struct dirent *buf, size_t bufsize, unsigned int mode) {
	return kreaddirf(fd, buf, bufsize, mode, 0);
}

@@The KOS-specific system call for reading a single directory entry
@@from a file descriptor referring to an open directory stream.
@@@param: MODE: One of `READDIR_*' (See below)
@@@return: * : The actually required buffer size for the directory entry (in bytes)
@@             NOTE: When `READDIR_DEFAULT' was passed for `MODE', the directory
@@                   stream will only be advanced when this value is >= 'BUFSIZE'
@@@return: 0 : The end of the directory has been reached.
@@@return: -1: Failed to read a directory entry for some reason (s.a.: `errno')
[[cp, ATTR_WUNUSED, no_crt_self_import]]
[[if(!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64)), preferred_alias("kreaddirf")]]
[[if(defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64)), preferred_alias("kreaddirf64")]]
$ssize_t kreaddirf($fd_t fd, struct dirent *buf, size_t bufsize, unsigned int mode, $oflag_t flags);

%#ifdef __USE_LARGEFILE64

@@64-bit variant of `kreaddir()'
[[cp, ATTR_WUNUSED, dirent64_variant_of(kreaddir)]]
[[if(defined(_DIRENT_MATCHES_DIRENT64)), alias("kreaddir")]]
[[userimpl, requires_function(kreaddirf64)]]
$ssize_t kreaddir64($fd_t fd, struct dirent64 *buf, size_t bufsize, unsigned int mode) {
	return kreaddirf64(fd, buf, bufsize, mode, 0);
}

@@64-bit variant of `kreaddirf()'
[[cp, ATTR_WUNUSED, dirent64_variant_of(kreaddirf)]]
$ssize_t kreaddirf64($fd_t fd, struct dirent64 *buf, size_t bufsize,
                     unsigned int mode, $oflag_t flags);

%#endif /* __USE_LARGEFILE64 */

%
%{
#ifndef READDIR_DEFAULT
#define READDIR_DEFAULT  0x0000 /* Yield to next entry when `buf' was of sufficient size. */
#define READDIR_CONTINUE 0x0001 /* Always yield to next entry. */
#define READDIR_PEEK     0x0002 /* Never yield to next entry. */
#if __KOS_VERSION__ >= 300
#define READDIR_SKIPREL  0x4000 /* Skip reading the `.' and `..' directory entries. */
#define READDIR_WANTEOF  0x8000 /* Minor optimization for `READDIR_MULTIPLE':
                                 * The system is allowed to append an empty directory entry
                                 * (with `d_namlen = 0' and `d_name[0] = '\0''; other fields are undefined).
                                 * If there isn't enough space for such an entry, no such entry will be emit.
                                 * Since no other directory entry can ever have a length of ZERO(0),
                                 * this allows user-space to detect end-of-directory without the need
                                 * of re-invoking the kreaddir() system call and inspecting its return
                                 * value for being equal to ZERO(0).
                                 * However, that check is still required, as this flag may be ignored
                                 * for no reason immediately apparent (if the EOF entry can't fit into
                                 * the buffer, there's no way of knowing if there's a missing entry that's
                                 * supposed to go into the buffer, or if it was actually an EOF entry).
                                 * Additionally, no eof entry may be written if kreaddir() is invoked
                                 * on a directory handle who's stream position is at the end of the directory.
                                 * For usage, see the example below, as well as `READDIR_MULTIPLE_ISEOF()' */
#define READDIR_MODEMASK 0x001f /* Mask for the kreaddir() mode. */
#define READDIR_FLAGMASK 0xc000 /* Mask of known kreaddir() flags. */
#define READDIR_MODEMAX  0x0003 /* Mask recognized mode ID. */
#define READDIR_MULTIPLE 0x0003 /* Read as many directory entries as can fit into the buffer.
                                 * If at least one entry could be read, return the combined size
                                 * of all read entries (in bytes) (in this case, `return <= bufsize')
                                 * If the buffer was too small to contain the next entry,
                                 * return the required size to house that pending entry,
                                 * but don't yield it, the same way `READDIR_DEFAULT' wouldn't.
                                 * To enumerate multiple directories in some buffer, use the
                                 * macros below. */
#ifdef __CC__
/* READDIR_MULTIPLE buffer helpers:
 * >> for (;;) {
 * >>     char buffer[2048]; size_t bufsize;
 * >>     struct dirent *iter = (struct dirent *)buffer;
 * >>     // Read as many entries as our buffer can fit
 * >>     bufsize = kreaddir(fd, iter, sizeof(buffer),
 * >>                        READDIR_MULTIPLE|
 * >>                        READDIR_WANTEOF);
 * >>     if (!bufsize) break; // End of directory
 * >>     if (bufsize > sizeof(buffer)) {
 * >>         printf("The next directory entry is too larger for the buffer\n");
 * >>         break;
 * >>     }
 * >>     // Process successfully read entries
 * >>     do {
 * >>         // This check is only required when `READDIR_WANTEOF' is passed.
 * >>         if (READDIR_MULTIPLE_ISEOF(iter))
 * >>             goto done;
 * >>         printf("Entry: %q\n", iter->d_name);
 * >>         iter = READDIR_MULTIPLE_GETNEXT(iter);
 * >>     } while (READDIR_MULTIPLE_ISVALID(iter, buffer, bufsize));
 * >> }
 * >>done:
 */
#define READDIR_MULTIPLE_GETNEXT(p) \
   ((struct dirent *)(((uintptr_t)((p)->d_name+((p)->d_namlen+1))+ \
                       (sizeof(__ino64_t)-1)) & ~(sizeof(__ino64_t)-1)))
#define READDIR_MULTIPLE_ISVALID(p, buf, bufsize) \
   (((__BYTE_TYPE__ *)((p)->d_name)) < ((__BYTE_TYPE__ *)(buf)+(bufsize)) && \
    ((__BYTE_TYPE__ *)((p)->d_name+(p)->d_namlen)) < ((__BYTE_TYPE__ *)(buf)+(bufsize)))
#define READDIR_MULTIPLE_ISEOF(p) ((p)->d_namlen == 0)
#ifdef __USE_LARGEFILE64
#define READDIR_MULTIPLE_GETNEXT64(p) ((struct dirent64 *)READDIR_MULTIPLE_GETNEXT(p))
#endif /* __USE_LARGEFILE64 */
#endif /* __CC__ */
#endif /* __KOS_VERSION__ >= 300 */
#endif /* !READDIR_DEFAULT */
}
%#endif /* __USE_KOS */

%{

#endif /* __CC__ */

__SYSDECL_END

}