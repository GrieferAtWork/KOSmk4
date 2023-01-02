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
/* (#) Portability: DJGPP        (/include/direct.h) */
/* (#) Portability: EMX kLIBC    (/libc/include/direct.h) */
/* (#) Portability: MSVC         (/include/direct.h) */
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/direct.h) */
/* (#) Portability: Windows Kits (/ucrt/direct.h) */
}

%{
}%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <hybrid/pp/__va_nargs.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

}%[insert:prefix(
#include <bits/crt/_diskfree_t.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

}

%[insert:function(_getcwd = getcwd)]
%[insert:function(_chdir = chdir)]
%[insert:function(_rmdir = rmdir)]

%[default:section(".text.crt.dos.fs.property")]
%[insert:pp_if($has_function(_getdcwd))]
%#define _getdcwd_nolock(drive, buf, bufsize) _getdcwd(drive, buf, bufsize)
%[insert:pp_endif]

[[cp, decl_include("<hybrid/typecore.h>")]]
[[requires_include("<asm/os/fcntl.h>"), dos_export_alias("_getdcwd_nolock")]]
[[requires($has_function(frealpath4) && defined(__AT_FDDRIVE_CWD))]]
[[crt_dos_variant, impl_include("<libc/errno.h>")]]
char *_getdcwd(int drive, [[out(? <= bufsize)]] char *buf, size_t bufsize) {
	if unlikely(drive < __AT_DOS_DRIVEMIN || drive > __AT_DOS_DRIVEMAX) {
@@pp_ifdef EINVAL@@
		(void)libc_seterrno(EINVAL);
@@pp_else@@
		(void)libc_seterrno(1);
@@pp_endif@@
		return NULL;
	}
	return frealpath4(__AT_FDDRIVE_CWD(drive), buf, bufsize, 0);
}

[[cp, requires_include("<asm/os/fcntl.h>")]]
[[requires($has_function(fchdir) && defined(__AT_FDDRIVE_ROOT))]]
[[impl_include("<libc/errno.h>")]]
int _chdrive(int drive) {
	drive = (unsigned char)toupper((unsigned char)drive);
	if unlikely(drive < __AT_DOS_DRIVEMIN || drive > __AT_DOS_DRIVEMAX) {
@@pp_ifdef EINVAL@@
		return libc_seterrno(EINVAL);
@@pp_else@@
		return libc_seterrno(1);
@@pp_endif@@
	}
	return fchdir(__AT_FDDRIVE_ROOT(drive));
}

[[cp]]
int _getdrive();

[[cp, decl_include("<hybrid/typecore.h>")]]
__ULONG32_TYPE__ _getdrives();

%
[[cp, guard("_GETDISKFREE_DEFINED"), decl_include("<bits/crt/_diskfree_t.h>")]]
unsigned int _getdiskfree(unsigned int drive, [[out]] struct _diskfree_t *diskfree);

/* A small hand full of functions defined in '<direct.h>' */
%[insert:extern(getcwd)];
%[insert:extern(rmdir)];

%[define(DOS_MKDIR_ACCESS_MODE = 0755)]

[[section(".text.crt.dos.fs.modify")]]
[[cp, crt_dos_variant, requires_function(mkdir)]]
int _mkdir([[in]] char const *path) {
	return mkdir(path, DOS_MKDIR_ACCESS_MODE);
}

%{
/* DOS  normally defines  mkdir() as  the 1-argument  form, but for
 * compatibility with <sys/stat.h>, we define it as the  2-argument
 * form, with the addition of a preprocessor overload to also allow
 * use of the 1-argument variant. */
}
%[insert:extern(mkdir)]


%{

/* DOS defines mkdir() as a  1-argument function, but we also  need
 * it to accept 2 arguments. As such, we always define _mkdir()  as
 * the  1-argument form,  and mkdir()  as the  2-argument one, with
 * the addition of (if possible) a preprocessor overload of mkdir()
 * to also accept 1 argument. */
}%[insert:pp_if(defined(__HYBRID_PP_VA_OVERLOAD) && $has_function(mkdir) && $has_function(_mkdir))]%{
#define __PRIVATE_mkdir_1 (_mkdir)
#define __PRIVATE_mkdir_2 (mkdir)
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define mkdir(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mkdir_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define mkdir(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mkdir_, (args))(args)
#endif /* ... */
}%[insert:pp_endif]%{
}


%{

__SYSDECL_END
#endif /* __CC__ */

#if defined(__USE_DOS) && !defined(__USE_DOS_CLEAN)
#include <corecrt_wdirect.h> /* Include <wchar.h> instead */
#endif /* __USE_DOS && !__USE_DOS_CLEAN */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_DIRECT_H)
#include <parts/uchar/direct.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_DIRECT_H */
#endif /* __USE_UTF */

}
