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
%(c_prefix){
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/xattr.h) */
/* (#) Portability: GNU C Library (/misc/sys/xattr.h) */
/* (#) Portability: NetBSD        (/sys/sys/xattr.h) */
/* (#) Portability: diet libc     (/include/sys/xattr.h) */
/* (#) Portability: musl libc     (/include/sys/xattr.h) */
/* (#) Portability: uClibc        (/include/sys/xattr.h) */
}

%[define_replacement(fd_t = __fd_t)]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/os/xattr.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __USE_GLIBC
#include <sys/types.h>
#endif /* __USE_GLIBC */

__SYSDECL_BEGIN

#ifndef __USE_KERNEL_XATTR_DEFS
#if (defined(__XATTR_CREATE) || defined(__XATTR_REPLACE))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __XATTR_CREATE
	XATTR_CREATE  = __XATTR_CREATE, /* set value, fail if attr already exists. */
#endif /* __XATTR_CREATE */
#ifdef __XATTR_REPLACE
	XATTR_REPLACE = __XATTR_REPLACE /* set value, fail if attr does not exist. */
#endif /* __XATTR_REPLACE */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __XATTR_CREATE
#define XATTR_CREATE  XATTR_CREATE  /* set value, fail if attr already exists. */
#endif /* __XATTR_CREATE */
#ifdef __XATTR_REPLACE
#define XATTR_REPLACE XATTR_REPLACE /* set value, fail if attr does not exist. */
#endif /* __XATTR_REPLACE */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __XATTR_CREATE
#define XATTR_CREATE  __XATTR_CREATE  /* set value, fail if attr already exists. */
#endif /* __XATTR_CREATE */
#ifdef __XATTR_REPLACE
#define XATTR_REPLACE __XATTR_REPLACE /* set value, fail if attr does not exist. */
#endif /* __XATTR_REPLACE */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */
#endif /* !__USE_KERNEL_XATTR_DEFS */

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __ssize_t_defined
#define __ssize_t_defined 1
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

}


@@>> setxattr(2)
@@@param: flags: One of `XATTR_*', or `0'
[[cp, decl_include("<features.h>", "<hybrid/typecore.h>")]]
int setxattr([[nonnull]] char const *path,
             [[nonnull]] char const *name,
             [[inp(bufsize)]] void const *buf,
             size_t bufsize,
             __STDC_INT_AS_UINT_T flags);

@@>> lsetxattr(2)
@@@param: flags: One of `XATTR_*', or `0'
[[cp, decl_include("<features.h>", "<hybrid/typecore.h>")]]
int lsetxattr([[nonnull]] char const *path,
              [[nonnull]] char const *name,
              [[inp(bufsize)]] void const *buf,
              size_t bufsize,
              __STDC_INT_AS_UINT_T flags);

@@>> fsetxattr(2)
@@@param: flags: One of `XATTR_*', or `0'
[[cp, decl_include("<features.h>", "<hybrid/typecore.h>")]]
int fsetxattr($fd_t fd,
              [[nonnull]] char const *name,
              [[inp(bufsize)]] void const *buf,
              size_t bufsize,
              __STDC_INT_AS_UINT_T flags);

@@>> getxattr(2)
[[cp, decl_include("<hybrid/typecore.h>")]]
ssize_t getxattr([[nonnull]] char const *path,
                 [[nonnull]] char const *name,
                 [[outp(bufsize)]] void *buf,
                 size_t bufsize);

@@>> lgetxattr(2)
[[cp, decl_include("<hybrid/typecore.h>")]]
ssize_t lgetxattr([[nonnull]] char const *path,
                  [[nonnull]] char const *name,
                  [[outp(bufsize)]] void *buf,
                  size_t bufsize);

@@>> fgetxattr(2)
[[cp, decl_include("<bits/types.h>")]]
ssize_t fgetxattr($fd_t fd,
                  [[nonnull]] char const *name,
                  [[outp(bufsize)]] void *buf,
                  size_t bufsize);

@@>> listxattr(2)
[[cp, decl_include("<hybrid/typecore.h>")]]
ssize_t listxattr([[nonnull]] char const *path,
                  [[outp(listbufsize)]] char *listbuf,
                  size_t listbufsize);

@@>> llistxattr(2)
[[cp, decl_include("<hybrid/typecore.h>")]]
ssize_t llistxattr([[nonnull]] char const *path,
                   [[outp(listbufsize)]] char *listbuf,
                   size_t listbufsize);

@@>> flistxattr(2)
[[cp, decl_include("<bits/types.h>")]]
ssize_t flistxattr($fd_t fd,
                   [[outp(listbufsize)]] char *listbuf,
                   size_t listbufsize);

@@>> removexattr(2)
[[cp]]
int removexattr([[nonnull]] char const *path,
                [[nonnull]] char const *name);

@@>> lremovexattr(2)
[[cp]]
int lremovexattr([[nonnull]] char const *path,
                 [[nonnull]] char const *name);

@@>> fremovexattr(2)
[[cp]]
int fremovexattr($fd_t fd,
                 [[nonnull]] char const *name);


%{
#endif /* __CC__ */

__SYSDECL_END

}
