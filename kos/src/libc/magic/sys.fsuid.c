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
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/fsuid.h) */
/* (#) Portability: diet libc     (/include/sys/fsuid.h) */
/* (#) Portability: musl libc     (/include/sys/fsuid.h) */
/* (#) Portability: uClibc        (/include/sys/fsuid.h) */
}

%[define_replacement(uid_t = __uid_t)]
%[define_replacement(gid_t = __gid_t)]
%[default:section(".text.crt{|.dos}.sched.user")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

#ifdef __CC__
__SYSDECL_BEGIN

}

@@>> setfsuid(2)
@@Set the  user ID  for the  cred-context (s.a.  `CLONE_CRED') of  the
@@calling thread. The calling thread needs the `CAP_SETUID' privilege.
@@@return: 0:  Success.
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>")]]
[[export_alias("__setfsuid", "__libc_setfsuid")]]
int setfsuid($uid_t uid);

@@>> setfsgid(2)
@@Set the group  ID for  the cred-context (s.a.  `CLONE_CRED') of  the
@@calling thread. The calling thread needs the `CAP_SETGID' privilege.
@@@return: 0:  Success.
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>")]]
[[export_alias("__setfsgid", "__libc_setfsgid")]]
int setfsgid($gid_t gid);

%{

__SYSDECL_END
#endif /* __CC__ */

}
