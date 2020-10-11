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

#include <hybrid/typecore.h>

#include <bits/crt/_diskfree_t.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

}

%[insert:function(_getcwd = getcwd)]
%[insert:function(_chdir = chdir)]
%[insert:function(_rmdir = rmdir)]

%[default:section(".text.crt.dos.fs.property")]
%#define _getdcwd_nolock _getdcwd
[[cp, decl_include("<hybrid/typecore.h>")]]
char *_getdcwd(int drive, char *buf, size_t size);

[[cp]]
int _chdrive(int drive);

[[cp]]
int _getdrive();

[[cp, decl_include("<hybrid/typecore.h>")]]
__ULONG32_TYPE__ _getdrives();

%
[[cp, guard("_GETDISKFREE_DEFINED"), decl_include("<bits/crt/_diskfree_t.h>")]]
unsigned int _getdiskfree(unsigned int drive, struct _diskfree_t *diskfree);

/* A small hand full of functions defined in '<direct.h>' */
%[insert:extern(getcwd)];
%[insert:extern(rmdir)];

[[section(".text.crt.dos.fs.modify")]]
[[cp, requires_function(mkdir)]]
int _mkdir([[nonnull]] char const *path) {
	return mkdir(path, 0755);
}

%[insert:guarded_function(mkdir = _mkdir)]


%{

__SYSDECL_END
#endif /* __CC__ */

}
