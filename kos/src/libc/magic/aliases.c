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
/* (#) Portability: GNU C Library (/inet/aliases.h) */
/* (#) Portability: GNU Hurd      (/usr/include/aliases.h) */
/* (#) Portability: libc6         (/include/aliases.h) */
}

/* Declare a couple of crt-functions that are _always_ exported by the  kernel,
 * but aren't auto-implemented through libc/auto/[...].c, but rather elsewhere:
 *  - /kos/src/libc/hybrid/...
 *  - /kos/src/kernel/core/... */

/* /kos/src/libc/hybrid/arch/[...]/assert[...].S */
%[declare_kernel_export("__stack_chk_fail", "abort", "__ubsan_handle_builtin_unreachable")]
%[declare_kernel_export("__afail", "__afailf", "__stack_chk_guard")]
%[declare_kernel_only_export("__acheck", "__acheckf")]

/* Indicate that we have support for all of the different assert functions. */
%[declare_kernel_export("__afail", "__afailf")]
%[declare_user_export("__assert", "__assert_fail", "__assert_func")]
%[declare_user_export("__assertfail", "_assert", "_ZSt9terminatev", "terminate")]

%[default:section(".text.crt{|.dos}.database.aliases")]

/* Tell magic about known "imports" (symbols from libdl)
 *
 * These are required for __CRT_HAVE_* optimizations that
 * are done to expression in in "/kos/src/libc/auto/*.c". */
%[declare_user_import(
	"dlopen", "dlclose", "dltlsallocseg", "dltlsfreeseg", "dlgethandle",
	"dlgetmodule", "dlmodulefd", "dlmodulename", "dlauxctrl", "dlerror",
	"dlmodulebase", "dlexceptaware", "dltlsaddr", "dltlsaddr2", "dltlsalloc",
	"dltlsfree", "dladdr", "dlsym",
)]


%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <bits/crt/db/aliases.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

#ifdef __CC__
__SYSDECL_BEGIN

}


@@>> setaliasent(3)
@@Rewind/Open the internal mail alias database file (which is located in `/etc/aliases')
[[cp_kos]]
void setaliasent();

@@>> endaliasent(3)
@@Close the internal mail alias database file (s.a. `setaliasent(3)')
void endaliasent();

@@>> getaliasent(3)
@@Read  the  entry entry  from  the mail  alias  alias database.
@@If the database hadn't already been opened, this function will
@@open  it the same  way that a  call to `setaliasent(3)' would.
@@@return: * :   A pointer to an internal, statically allocated structure
@@@return: NULL: [errno=<unchanged>] Database end has been reached
@@@return: NULL: [errno=ENOENT]      Database end has been reached
@@@return: NULL: [errno=*]           Error
[[wunused, cp_kos, decl_include("<bits/crt/db/aliases.h>")]]
struct aliasent *getaliasent();

@@>> getaliasent_r(3)
@@Reentrant variant of `getaliasent(3)' (s.a. similar functions such as `getpwent_r(3)')
[[cp_kos, decl_include("<bits/types.h>", "<bits/crt/db/aliases.h>")]]
$errno_t getaliasent_r([[out]] struct aliasent *__restrict result_buf,
                       [[out(? <= buflen)]] char *__restrict buffer, size_t buflen,
                       [[out]] struct aliasent **__restrict result);

@@>> getaliasbyname(3)
@@Find a database entry associated with the given `name'
@@@return: * :   A pointer to an internal, statically allocated structure
@@@return: NULL: [errno=ENOENT] No entry matching `name'
@@@return: NULL: [errno=*]      Error
[[wunused, cp_kos, decl_include("<bits/crt/db/aliases.h>")]]
struct aliasent *getaliasbyname([[in]] char const *name);

@@>> getaliasbyname_r(3)
@@Reentrant variant of `getaliasbyname(3)' (s.a. similar functions such as `getpwnam_r(3)')
[[cp_kos, decl_include("<bits/types.h>", "<bits/crt/db/aliases.h>")]]
$errno_t getaliasbyname_r([[in]] char const *__restrict name,
                          [[out]] struct aliasent *__restrict result_buf,
                          [[out(? <= buflen)]] char *__restrict buffer, size_t buflen,
                          [[out]] struct aliasent **__restrict result);

%{

__SYSDECL_END
#endif /* __CC__ */

}
