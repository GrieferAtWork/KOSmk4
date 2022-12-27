/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: DragonFly BSD (/include/printf.h) */
/* (#) Portability: FreeBSD       (/include/printf.h) */
/* (#) Portability: GNU C Library (/include/printf.h) */
/* (#) Portability: libc6         (/include/printf.h) */
/* (#) Portability: mintlib       (/include/printf.h) */
/* (#) Portability: uClibc        (/include/printf.h) */
}

%[default:section(".text.crt{|.dos}.compat.glibc.printf")]

%[default:nodos]
%[define_replacement(fd_t = __fd_t)]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <bits/crt/printf_info.h>
)]%{

#ifdef __USE_GLIBC_BLOAT
#include <stdarg.h>
#endif /* __USE_GLIBC_BLOAT */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifndef __std_FILE_defined
#define __std_FILE_defined
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __FILE_defined
#define __FILE_defined
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#endif /* !__CXX_SYSTEM_HEADER */

/* Function types (NOT POINTERS) from `<bits/crt/printf_info.h>' */
typedef __printf_function printf_function;
typedef __printf_arginfo_size_function printf_arginfo_size_function;
typedef __printf_arginfo_function printf_arginfo_function;
typedef __printf_va_arg_function printf_va_arg_function;

}

%[define_replacement(printf_function = __printf_function)]
%[define_replacement(printf_arginfo_size_function = __printf_arginfo_size_function)]
%[define_replacement(printf_arginfo_function = __printf_arginfo_function)]
%[define_replacement(printf_va_arg_function = __printf_va_arg_function)]

%[define_decl_include("<bits/crt/printf_info.h>": [
	"struct printf_info",
	"__printf_function",
	"__printf_arginfo_size_function",
	"__printf_arginfo_function",
	"__printf_va_arg_function",
])]


@@>> register_printf_specifier(3), register_printf_function(3)
[[decl_include("<bits/crt/printf_info.h>")]]
int register_printf_specifier(int spec,
                              [[nonnull]] printf_function *func,
                              [[nonnull]] printf_arginfo_size_function *arginfo);

[[doc_alias("register_printf_specifier")]]
[[decl_include("<bits/crt/printf_info.h>")]]
[[crt_intern_alias("register_printf_specifier")]]
int register_printf_function(int spec,
                             [[nonnull]] printf_function *func,
                             [[nonnull]] printf_arginfo_function *arginfo);

[[wunused]]
[[decl_include("<hybrid/typecore.h>")]]
int register_printf_modifier([[nonnull]] __WCHAR32_TYPE__ const *str);

[[wunused]]
[[decl_include("<bits/crt/printf_info.h>")]]
int register_printf_type([[nonnull]] printf_va_arg_function *fct);


[[decl_include("<hybrid/typecore.h>")]]
size_t parse_printf_format([[nonnull]] char const *__restrict fmt, size_t n,
                           [[out(? <= n)]] int *__restrict argtypes);



%
%
%
%{
/************************************************************************/
/* BUILT-IN PRINTF FUNCTIONS (that aren't linked by default)            */
/************************************************************************/
}
%

[[decl_include("<bits/crt/printf_info.h>")]]
int printf_size([[nonnull]] $FILE *__restrict fp,
                [[nonnull]] struct printf_info const *info,
                [[nonnull]] void const *const *__restrict args);

[[decl_include("<hybrid/typecore.h>", "<bits/crt/printf_info.h>")]]
int printf_size_info([[nonnull]] struct printf_info const *__restrict info, size_t n,
                     [[nonnull]] int *__restrict argtypes);


%{

__SYSDECL_END
#endif /* __CC__ */

}
