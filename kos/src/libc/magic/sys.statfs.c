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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/statfs.h) */
/* (#) Portability: GNU C Library (/io/sys/statfs.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/statfs.h) */
/* (#) Portability: diet libc     (/include/sys/statfs.h) */
/* (#) Portability: musl libc     (/include/sys/statfs.h) */
/* (#) Portability: uClibc        (/include/sys/statfs.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.fs.statfs.statfs")]

%{
#include <features.h>

#include <bits/os/statfs.h>
#include <bits/types.h>

#ifdef __USE_GLIBC
#include <sys/types.h>
#endif /* __USE_GLIBC */

#ifdef __CC__
__SYSDECL_BEGIN

}

[[no_crt_self_import, export_as("__statfs")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("statfs", "__statfs")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("statfs64")]]
[[decl_include("<bits/os/statfs.h>")]]
int statfs([[nonnull]] char const *file, [[nonnull]] struct statfs *buf);

[[no_crt_self_import]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("fstatfs")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("fstatfs64")]]
[[decl_include("<bits/os/statfs.h>")]]
int fstatfs($fd_t filedes, [[nonnull]] struct statfs *buf);

%
%#ifdef __USE_LARGEFILE64
%#ifndef statfs64
[[doc_alias("statfs"), statfs64_variant_of(statfs)]]
[[decl_include("<bits/os/statfs.h>")]]
int statfs64([[nonnull]] const char *file, [[nonnull]] struct statfs64 *buf);
%#endif /* !statfs64 */

[[doc_alias("fstatfs"), statfs64_variant_of(fstatfs)]]
[[decl_include("<bits/os/statfs.h>")]]
int fstatfs64($fd_t filedes, [[nonnull]] struct statfs64 *buf);
%#endif /* __USE_LARGEFILE64 */


%{

__SYSDECL_END
#endif /* __CC__ */

}
