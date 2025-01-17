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
/* (#) Portability: Windows Kits (/ucrt/corecrt_wdirect.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(oflag_t = __oflag_t)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __ernno_t_defined
#define __ernno_t_defined
typedef __errno_t errno_t;
#endif /* !__ernno_t_defined */

#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

}

%[insert:function(_wgetcwd = wgetcwd)]

[[wchar, cp, decl_include("<hybrid/typecore.h>"), dos_export_alias("_wgetdcwd_nolock")]]
[[requires_include("<asm/os/fcntl.h>"), impl_include("<libc/errno.h>")]]
[[requires($has_function(wfrealpath4) && defined(__AT_FDDRIVE_CWD))]]
wchar_t *_wgetdcwd(int drive, [[out(? <= size)]] wchar_t *buf, size_t size) {
	if unlikely(drive < __AT_DOS_DRIVEMIN || drive > __AT_DOS_DRIVEMAX) {
@@pp_ifdef EINVAL@@
		(void)libc_seterrno(EINVAL);
@@pp_else@@
		(void)libc_seterrno(1);
@@pp_endif@@
		return NULL;
	}
	return wfrealpath4(__AT_FDDRIVE_CWD(drive), buf, size, 0);
}

%[insert:pp_if($has_function(_wgetdcwd))]
%#define _wgetdcwd_nolock(drive, buf, size) _wgetdcwd(drive, buf, size)
%[insert:pp_endif]

%[insert:function(_wchdir = wchdir)]
%[insert:function(_wrmdir = wrmdir)]

[[wchar, cp, requires_function(wmkdir)]]
[[decl_include("<hybrid/typecore.h>")]]
int _wmkdir([[in]] wchar_t const *path) {
	return wmkdir(path, DOS_MKDIR_ACCESS_MODE);
}

%{

__SYSDECL_END
#endif /* __CC__ */

}
