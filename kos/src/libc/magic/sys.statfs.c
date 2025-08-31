/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/statfs.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/statfs.h) */
/* (#) Portability: GNU C Library (/io/sys/statfs.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/statfs.h) */
/* (#) Portability: diet libc     (/include/sys/statfs.h) */
/* (#) Portability: mintlib       (/include/sys/statfs.h) */
/* (#) Portability: musl libc     (/include/sys/statfs.h) */
/* (#) Portability: uClibc        (/include/sys/statfs.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.fs.statfs.statfs")]

%[define_decl_include_implication("<bits/os/statfs.h>" => ["<bits/types.h>"])]
%[define_decl_include("<bits/os/statfs.h>": ["struct statfs", "struct statfs64"])]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <bits/os/statfs.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

#ifdef __CC__
__SYSDECL_BEGIN

}

[[decl_include("<bits/os/statfs.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("statfs", "__statfs", "__libc_statfs")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("statfs64")]]
[[export_as("__statfs", "__libc_statfs")]]
int statfs([[in]] char const *file, [[out]] struct statfs *buf);

[[decl_include("<bits/os/statfs.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("fstatfs", "__fstatfs", "__libc_fstatfs")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("fstatfs64")]]
[[export_as("__fstatfs", "__libc_fstatfs")]]
int fstatfs([[fdarg]] $fd_t filedes, [[out]] struct statfs *buf);

%
%#ifdef __USE_LARGEFILE64
%#ifndef statfs64
[[decl_include("<bits/os/statfs.h>")]]
[[preferred_statfs64_variant_of(statfs), doc_alias("statfs")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), preferred_alias("statfs", "__statfs", "__libc_statfs")]]
int statfs64([[in]] char const *file, [[out]] struct statfs64 *buf);
%#endif /* !statfs64 */

[[decl_include("<bits/os/statfs.h>")]]
[[preferred_statfs64_variant_of(fstatfs), doc_alias("fstatfs")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), preferred_alias("fstatfs", "__fstatfs", "__libc_fstatfs")]]
int fstatfs64([[fdarg]] $fd_t filedes, [[out]] struct statfs64 *buf);
%#endif /* __USE_LARGEFILE64 */


%{

__SYSDECL_END
#endif /* __CC__ */

}
