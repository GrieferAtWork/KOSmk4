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
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/prctl.h) */
/* (#) Portability: diet libc     (/include/sys/prctl.h) */
/* (#) Portability: musl libc     (/include/sys/prctl.h) */
}

%[define_replacement(fd_t = __fd_t)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <linux/prctl.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

@@>> prctl(2)
@@System process control interface. (Linux compatible)
@@@param: command: One of `PR_*' (from <linux/prctl.h>)
@@@param: ... :    Up  to 4 additional arguments (dependent on `command')
@@                 Note that some control codes  require you to pass  `0'
@@                 for  all seemingly "unused" arguments. In these cases,
@@                 the documentation for that command includes the number
@@                 of unused, but required trailing 0s in its comment.
@@@return: * :     Return value depends on `command'
@@@return: -1:     Error (s.a. `errno'; depends on `command')
@@@return: -1:     [errno=EINVAL] Unsupported `command' (including unsupported-on-this-arch)
[[decl_include("<features.h>")]]
[[vartypes(__syscall_ulong_t, __syscall_ulong_t, __syscall_ulong_t, __syscall_ulong_t)]]
int prctl(__STDC_INT_AS_UINT_T command, ...);


%{

__SYSDECL_END
#endif /* __CC__ */

}
