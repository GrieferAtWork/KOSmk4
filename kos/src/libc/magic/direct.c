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

%{
#include <features.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef _DISKFREE_T_DEFINED
#define _DISKFREE_T_DEFINED 1
}%[push_macro @undef { total_clusters avail_clusters sectors_per_cluster bytes_per_sector }]%{
struct _diskfree_t {
	__UINT32_TYPE__ total_clusters;
	__UINT32_TYPE__ avail_clusters;
	__UINT32_TYPE__ sectors_per_cluster;
	__UINT32_TYPE__ bytes_per_sector;
};
}%[pop_macro]%{
#endif /* !_DISKFREE_T_DEFINED */

}

[section(.text.crt.dos.fs.basic_property)]
[cp] _getcwd:(char *buf, size_t bufsize) -> char * = getcwd;

[section(.text.crt.dos.fs.basic_property)]
[cp] _chdir:([nonnull] char const *path) -> int = chdir;

%[default_impl_section(.text.crt.dos.fs.modify)]
[cp] _rmdir:([nonnull] char const *path) -> int = rmdir;

%[default_impl_section(.text.crt.dos.fs.property)]
%#define _getdcwd_nolock _getdcwd
[cp] _getdcwd:(int drive, char *buf, size_t size) -> char *;

[cp] _chdrive:(int drive) -> int;
[cp] _getdrive:() -> int;
[cp] _getdrives:() -> __ULONG32_TYPE__;

%
%#ifndef _GETDISKFREE_DEFINED
%#define _GETDISKFREE_DEFINED 1
[cp][guard] _getdiskfree:(unsigned int drive, struct _diskfree_t *diskfree) -> unsigned int;
%#endif /* !_GETDISKFREE_DEFINED */

/* A small hand full of functions defined in '<direct.h>' */
%[insert:extern(getcwd)]
%[insert:extern(rmdir)]

%[default_impl_section(.text.crt.dos.fs.modify)]
[cp][noexport][requires(defined(__CRT_HAVE_mkdir))]
_mkdir:([nonnull] char const *path) -> int {
	return mkdir(path, 0755);
}

[cp][guard][noexport] mkdir:([nonnull] char const *path) -> int = _mkdir;

%{
#endif /* __CC__ */

__SYSDECL_END

}
