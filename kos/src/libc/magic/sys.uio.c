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
%(c_prefix){
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/uio.h) */
/* (#) Portability: DJGPP         (/include/sys/uio.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/uio.h) */
/* (#) Portability: FreeBSD       (/sys/sys/uio.h) */
/* (#) Portability: GNU C Library (/misc/sys/uio.h) */
/* (#) Portability: NetBSD        (/sys/sys/uio.h) */
/* (#) Portability: OpenBSD       (/sys/sys/uio.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/uio.h) */
/* (#) Portability: diet libc     (/include/sys/uio.h) */
/* (#) Portability: libc4/5       (/include/sys/uio.h) */
/* (#) Portability: mintlib       (/include/sys/uio.h) */
/* (#) Portability: musl libc     (/include/sys/uio.h) */
/* (#) Portability: uClibc        (/include/sys/uio.h) */
}

%[define_replacement(fd_t       = __fd_t)]
%[define_replacement(pid_t      = __pid_t)]
%[define_replacement(off_t      = "__FS_TYPE(off)")]
%[define_replacement(pos_t      = "__FS_TYPE(pos)")]
%[define_replacement(off32_t    = __off32_t)]
%[define_replacement(off64_t    = __off64_t)]
%[define_replacement(pos32_t    = __pos32_t)]
%[define_replacement(pos64_t    = __pos64_t)]
%[define_replacement(ulongptr_t = __ULONGPTR_TYPE__)]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/os/limits.h> /* __IOV_MAX */
)]%[insert:prefix(
#include <bits/os/iovec.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#include <sys/types.h>

#ifndef UIO_MAXIOV
#if !defined(__IOV_MAX) || (__IOV_MAX == -1)
#define UIO_MAXIOV 16
#else /* !__IOV_MAX || __IOV_MAX == -1 */
#define UIO_MAXIOV __IOV_MAX
#endif /* __IOV_MAX && __IOV_MAX != -1 */
#endif /* !UIO_MAXIOV */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

}

%
%#ifdef __USE_GNU
@@>> process_vm_readv(2)
@@Read memory from another process's VM
@@@param: flags: Must be `0'
@@@return: * :   The actual number of read bytes
[[cp, wunused, decl_include("<bits/os/iovec.h>", "<bits/types.h>")]]
ssize_t process_vm_readv($pid_t pid,
                         [[inp_opt(liovcnt)]] struct iovec const *local_iov, $ulongptr_t liovcnt,
                         [[inp_opt(riovcnt)]] struct iovec const *remote_iov, $ulongptr_t riovcnt,
                         $ulongptr_t flags);

@@>> process_vm_writev(2)
@@Write memory to another process's VM
@@@param: flags: Must be `0'
@@@return: * :   The actual number of written bytes
[[cp, decl_include("<bits/os/iovec.h>", "<bits/types.h>")]]
ssize_t process_vm_writev($pid_t pid,
                          [[inp_opt(liovcnt)]] struct iovec const *local_iov, $ulongptr_t liovcnt,
                          [[inp_opt(riovcnt)]] struct iovec const *remote_iov, $ulongptr_t riovcnt,
                          $ulongptr_t flags);
%#endif /* __USE_GNU */

%
@@>> readv(2)
@@Same as `read(2)', but rather than specifying a single, continuous buffer,
@@read  data into `count'  separate buffers, though  still return the actual
@@number of read bytes.
@@When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
@@available at the time the call was made, and throw E_WOULDBLOCK if no data
@@was available at the time.
@@@return: <= SUM(iov[*].iov_len): The actual amount of read bytes
@@@return: 0                     : EOF
[[cp, wunused, decl_include("<bits/os/iovec.h>", "<features.h>", "<bits/types.h>")]]
[[export_alias("__readv")]]
/* The following as libc4/5 aliases, though behave slightly different.
 * In libc4/5, `readv()' tries to emulate the system call if it's  not
 * supported by the kernel,  but `syscall_readv()' doesn't. Yet  since
 * on  KOS `readv(2)' always works as a  system call, we don't have to
 * worry about that. -- However, for the sake of consistency we  still
 * don't  import this function under these aliases. The same also goes
 * for `writev()' below! */
[[export_as("syscall_readv", "__syscall_readv", "__libc_syscall_readv")]]
ssize_t readv($fd_t fd, [[inp(count)]] struct iovec const *iov, __STDC_INT_AS_SIZE_T count);

@@>> writev(2)
@@Same as `write(2)', but rather than specifying a single, continuous buffer,
@@write  data from `count'  separate buffers, though  still return the actual
@@number of written bytes.
@@When `fd' has the `O_NONBLOCK' flag set, only write as much  data
@@as possible at the time the call was made, and throw E_WOULDBLOCK
@@if no data could be written at the time.
@@@return: <= SUM(iov[*].iov_len): The actual amount of written bytes
@@@return: 0                     : No more data can be written
[[cp, decl_include("<bits/os/iovec.h>", "<features.h>", "<bits/types.h>")]]
[[export_alias("__writev")]]
[[export_as("syscall_writev", "__syscall_writev", "__libc_syscall_writev")]]
ssize_t writev($fd_t fd, [[inp(count)]] struct iovec const *iov, __STDC_INT_AS_SIZE_T count);


%
%#ifdef __USE_MISC

[[cp, ignore, nocrt, alias("preadv"), doc_alias("preadv")]]
[[decl_include("<features.h>", "<bits/os/iovec.h>", "<bits/types.h>")]]
ssize_t preadv32($fd_t fd, [[inp(count)]] struct iovec const *iov,
                 __STDC_INT_AS_SIZE_T count, $off32_t offset);

[[cp, ignore, nocrt, alias("pwritev"), doc_alias("pwritev")]]
[[decl_include("<features.h>", "<bits/os/iovec.h>", "<bits/types.h>")]]
ssize_t pwritev32($fd_t fd, [[inp(count)]] struct iovec const *iov,
                  __STDC_INT_AS_SIZE_T count, $off32_t offset);

@@>> preadv(2), preadv64(2)
@@Same as  `readv(2)', but  read data  from a  file at  a
@@specific `offset', rather than the current R/W position
@@@return: <= SUM(iov[*].iov_len): The actual amount of read bytes
[[cp, wunused, decl_include("<features.h>", "<bits/os/iovec.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("preadv")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("preadv64")]]
[[userimpl, requires($has_function(preadv32) || $has_function(preadv64))]]
ssize_t preadv($fd_t fd, [[inp(count)]] struct iovec const *iov,
               __STDC_INT_AS_SIZE_T count, $off_t offset) {
@@pp_if $has_function(preadv64)@@
	return preadv64(fd, iov, count, (off64_t)offset);
@@pp_else@@
	return preadv32(fd, iov, count, (off32_t)offset);
@@pp_endif@@
}

@@>> pwritev(2), pwritev64(2)
@@Same as  `writev(2)', but  write data  to a  file at  a
@@specific `offset', rather than the current R/W position
@@@return: <= SUM(iov[*].iov_len): The actual amount of written bytes
[[cp, decl_include("<features.h>", "<bits/os/iovec.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("pwritev")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("pwritev64")]]
[[userimpl, requires($has_function(pwritev32) || $has_function(pwritev64))]]
ssize_t pwritev($fd_t fd, [[inp(count)]] struct iovec const *iov,
                __STDC_INT_AS_SIZE_T count, $off_t offset) {
@@pp_if $has_function(pwritev64)@@
	return pwritev64(fd, iov, count, (off64_t)offset);
@@pp_else@@
	return pwritev32(fd, iov, count, (off32_t)offset);
@@pp_endif@@
}

%
%#ifdef __USE_LARGEFILE64
[[cp, wunused, decl_include("<features.h>", "<bits/os/iovec.h>", "<bits/types.h>")]]
[[preferred_off64_variant_of(preadv), doc_alias("preadv")]]
[[userimpl, requires_function(preadv32)]]
ssize_t preadv64($fd_t fd, [[inp(count)]] struct iovec const *iov,
                 __STDC_INT_AS_SIZE_T count, $off64_t offset) {
	return preadv32(fd, iov, count, (off32_t)offset);
}

[[cp, decl_include("<features.h>", "<bits/os/iovec.h>", "<bits/types.h>")]]
[[preferred_off64_variant_of(pwritev), doc_alias("pwritev")]]
[[userimpl, requires_function(pwritev32)]]
ssize_t pwritev64($fd_t fd, [[inp(count)]] struct iovec const *iov,
                  __STDC_INT_AS_SIZE_T count, $off64_t offset) {
	return pwritev32(fd, iov, count, (off32_t)offset);
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* !__USE_MISC */

%{

__SYSDECL_END
#endif /* __CC__ */

}
