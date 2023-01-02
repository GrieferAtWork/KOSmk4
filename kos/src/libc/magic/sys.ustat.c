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
/* (#) Portability: OpenSolaris (/usr/src/uts/common/sys/ustat.h) */
/* (#) Portability: uClibc      (/include/sys/ustat.h) */
}

%[define_replacement(dev_t = __dev_t)]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <bits/os/ustat.h> /* struct ustat */
)]%[insert:prefix(
#include <bits/types.h>    /* __dev_t */
)]%{

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

#ifdef __CC__
__SYSDECL_BEGIN

}

@@>> ustat(2)
[[decl_include("<bits/os/ustat.h>", "<bits/types.h>")]]
/* The following are libc4/5 aliases. -- We only export under these names.
 * We  don't import simply because these names feel really weird... °~°... */
[[export_as("prev_ustat", "__prev_ustat", "__libc_prev_ustat")]]
int ustat($dev_t dev, [[out]] struct ustat *ubuf);

%{

__SYSDECL_END
#endif /* __CC__ */

}
