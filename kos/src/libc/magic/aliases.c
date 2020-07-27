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

/* Declare a couple of crt-functions that are _always_ exported by the kernel,
 * but aren't auto-implemented through libc/auto/[...].c, but rather elsewhere:
 *  - /kos/src/libc/hybrid/...
 *  - /kos/src/kernel/core/... */

/* /kos/src/libc/hybrid/arch/[...]/assert[...].S */
%[declare_kernel_export("__stack_chk_fail", "abort", "_ZSt9terminatev", "__crt_unreachable")]
%[declare_kernel_export("__afail", "__afailf", "__stack_chk_guard")]
%[declare_kernel_only_export("__acheck", "__acheckf")]

/* /kos/src/libc/hybrid/arch/[...]/except[...].S */
%[declare_kernel_export("error_rethrow", "__cxa_rethrow", "_Unwind_Resume")]
%[declare_kernel_export("error_thrown", "error_throw", "error_throw_current")]

/* /kos/src/kernel/core/misc/except.c */
%[declare_kernel_export("error_info", "error_data", "error_register_state")]
%[declare_kernel_export("error_code", "error_active", "error_class", "error_subclass")]

/* /kos/src/kernel/core/arch/[...]/except.c */
%[declare_kernel_export("error_unwind", "__gxx_personality_v0", "__cxa_begin_catch", "__cxa_end_catch")]

/* /kos/src/libc/hybrid/except_to_posix.c */
%[declare_kernel_export("error_as_errno", "error_as_signal")]

/* /kos/src/libc/hybrid/unicode.c */
%[declare_kernel_export("unicode_utf8seqlen")]

/* Indicate that we have support for all of the different assert functions. */
%[declare_kernel_export("__afail", "__afailf")]
%[declare_user_export("__assert", "__assert_fail", "__assert_func")]
%[declare_user_export("__assertfail", "_assert")]


%[define_replacement(sigset_t = "struct __sigset_struct")]
%[default:section(".text.crt{|.dos}.database.aliases")]

%{
#include <features.h>

#include <bits/crt/db/aliases.h>

#ifdef __USE_GLIBC
#include <sys/types.h>
#endif /* __USE_GLIBC */

#ifdef __CC__
__SYSDECL_BEGIN

}


@@Rewind/Open the internal mail alias database file (which is located in `/etc/aliases')
[[cp_kos]]
void setaliasent();

@@Close the internal mail alias database file (s.a. `setaliasent(3)')
void endaliasent();

@@Read the entry entry from the mail alias alias database.
@@If the database hadn't already been opened, this function will
@@open it the same way that a call to `setaliasent(3)' would.
@@@return: * :   A pointer to an internal, statically allocated structure
@@@return: NULL: [errno=<unchanged>] Database end has been reached
@@@return: NULL: [errno=ENOENT]      Database end has been reached
@@@return: NULL: [errno=*]           Error
[[wunused, cp_kos, decl_include("<bits/crt/db/aliases.h>")]]
struct aliasent *getaliasent();

@@Reentrant variant of `getaliasent(3)' (s.a. similar functions such as `getpwent_r(3)')
[[cp_kos, decl_include("<bits/types.h>", "<bits/crt/db/aliases.h>")]]
$errno_t getaliasent_r([[nonnull]] struct aliasent *__restrict result_buf,
                       [[nonnull]] char *__restrict buffer, size_t buflen,
                       [[nonnull]] struct aliasent **__restrict result);

@@Find a database entry associated with the given `name'
@@@return: * :   A pointer to an internal, statically allocated structure
@@@return: NULL: [errno=ENOENT] No entry matching `name'
@@@return: NULL: [errno=*]      Error
[[wunused, cp_kos, decl_include("<bits/crt/db/aliases.h>")]]
struct aliasent *getaliasbyname([[nonnull]] char const *name);

@@Reentrant variant of `getaliasbyname(3)' (s.a. similar functions such as `getpwnam_r(3)')
[[cp_kos, decl_include("<bits/types.h>", "<bits/crt/db/aliases.h>")]]
$errno_t getaliasbyname_r([[nonnull]] char const *__restrict name,
                          [[nonnull]] struct aliasent *__restrict result_buf,
                          [[nonnull]] char *__restrict buffer, size_t buflen,
                          [[nonnull]] struct aliasent **__restrict result);

%{

__SYSDECL_END
#endif /* __CC__ */

}
