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
%[define_replacement(pid_t      = __pid_t)]
%[define_replacement(off_t      = "__FS_TYPE(off)")]
%[define_replacement(pos_t      = "__FS_TYPE(pos)")]
%[define_replacement(off32_t    = __off32_t)]
%[define_replacement(off64_t    = __off64_t)]
%[define_replacement(pos32_t    = __pos32_t)]
%[define_replacement(pos64_t    = __pos64_t)]
%[define_replacement(ulongptr_t = __ULONGPTR_TYPE__)]

%{
#include <features.h>

#include <bits/types.h>
#include <bits/uio.h>
#include <sys/types.h>

__SYSDECL_BEGIN


#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

}

%
%#ifdef __USE_GNU
[[cp, wunused, decl_include("<bits/iovec-struct.h>")]]
ssize_t process_vm_readv($pid_t pid,
                         [[inp_opt(liovcnt)]] struct iovec const *local_iov, $ulongptr_t liovcnt,
                         [[inp_opt(riovcnt)]] struct iovec const *remote_iov, $ulongptr_t riovcnt,
                         $ulongptr_t flags);

[[cp, decl_include("<bits/iovec-struct.h>")]]
process_vm_writev:($pid_t pid,
                   [[inp_opt(liovcnt)]] struct iovec const *local_iov, $ulongptr_t liovcnt,
                   [[inp_opt(riovcnt)]] struct iovec const *remote_iov, $ulongptr_t riovcnt,
                   $ulongptr_t flags) -> ssize_t;
%#endif /* __USE_GNU */

%
[[cp, wunused, decl_include("<bits/iovec-struct.h>", "<features.h>")]]
ssize_t readv($fd_t fd, [[inp(count)]] struct iovec const *iov, __STDC_INT_AS_SIZE_T count);

[[cp, decl_include("<bits/iovec-struct.h>", "<features.h>")]]
ssize_t writev($fd_t fd, [[inp(count)]] struct iovec const *iov, __STDC_INT_AS_SIZE_T count);


%
%#ifdef __USE_MISC

[[cp, ignore, nocrt, alias("preadv")]]
[[decl_include("<features.h>", "<bits/iovec-struct.h>")]]
ssize_t preadv32($fd_t fd, [[inp(count)]] struct iovec const *iov,
                 __STDC_INT_AS_SIZE_T count, $off32_t offset);

[[cp, ignore, nocrt, alias("pwritev")]]
[[decl_include("<features.h>", "<bits/iovec-struct.h>")]]
ssize_t pwritev32($fd_t fd, [[inp(count)]] struct iovec const *iov,
                  __STDC_INT_AS_SIZE_T count, $off32_t offset);

[[cp, wunused, no_crt_self_import]]
[[decl_include("<features.h>", "<bits/iovec-struct.h>")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("preadv64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("preadv")]]
[[userimpl, requires($has_function(preadv32) || $has_function(preadv64))]]
ssize_t preadv($fd_t fd, [[inp(count)]] struct iovec const *iov,
               __STDC_INT_AS_SIZE_T count, $off_t offset) {
@@pp_if $has_function(preadv64)@@
	return preadv64(fd, iov, count, (off64_t)offset);
@@pp_else@@
	return preadv32(fd, iov, count, (off32_t)offset);
@@pp_endif@@
}

[[cp, no_crt_self_import]]
[[decl_include("<features.h>", "<bits/iovec-struct.h>")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias(pwritev64)]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(pwritev)]]
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
[[cp, wunused, doc_alias("preadv"), off64_variant_of(preadv)]]
[[decl_include("<features.h>", "<bits/iovec-struct.h>")]]
[[userimpl, requires_function(preadv32)]]
ssize_t preadv64($fd_t fd, [[inp(count)]] struct iovec const *iov,
                 __STDC_INT_AS_SIZE_T count, $off64_t offset) {
	return preadv32(fd, iov, count, (off32_t)offset);
}

[[cp, doc_alias("pwritev"), off64_variant_of(pwritev)]]
[[decl_include("<features.h>", "<bits/iovec-struct.h>")]]
[[userimpl, requires_function(pwritev32)]]
ssize_t pwritev64($fd_t fd, [[inp(count)]] struct iovec const *iov,
                  __STDC_INT_AS_SIZE_T count, $off64_t offset) {
	return pwritev32(fd, iov, count, (off32_t)offset);
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* !__USE_MISC */

%{

#endif /* __CC__ */

__SYSDECL_END

}