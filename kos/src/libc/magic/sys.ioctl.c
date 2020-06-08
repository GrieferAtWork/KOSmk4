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

%[define_replacement(fd_t = __fd_t)]
%[default_impl_section(".text.crt.io.utility")]

%{
#include <features.h>
#include <bits/ioctls.h>
#include <bits/types.h>
#include <bits/ioctl-types.h>
#include <sys/ttydefaults.h>

__SYSDECL_BEGIN

#ifdef __CC__
}

@@Perform the I/O control operation specified by REQUEST on FD.
@@One argument may follow; its presence and type depend on REQUEST.
@@Return value depends on REQUEST. Usually -1 indicates error
[[cp, guard]][vartypes(void *)]
ioctl:($fd_t fd, unsigned long int request, ...) -> __STDC_INT_AS_SSIZE_T;

%{
#endif /* __CC__ */

__SYSDECL_END

}