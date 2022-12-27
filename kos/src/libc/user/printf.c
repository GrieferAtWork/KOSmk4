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
#ifndef GUARD_LIBC_USER_PRINTF_C
#define GUARD_LIBC_USER_PRINTF_C 1

#include "../api.h"
/**/

#include "printf.h"

DECL_BEGIN

/*[[[head:libc_register_printf_specifier,hash:CRC-32=0x62ed38cb]]]*/
/* >> register_printf_specifier(3), register_printf_function(3) */
INTERN ATTR_SECTION(".text.crt.compat.glibc.printf") NONNULL((2, 3)) int
NOTHROW_NCX(LIBCCALL libc_register_printf_specifier)(int spec,
                                                     printf_function *func,
                                                     printf_arginfo_size_function *arginfo)
/*[[[body:libc_register_printf_specifier]]]*/
/*AUTO*/{
	(void)spec;
	(void)func;
	(void)arginfo;
	CRT_UNIMPLEMENTEDF("register_printf_specifier(spec: %x, func: %p, arginfo: %p)", spec, func, arginfo); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_register_printf_specifier]]]*/

/*[[[impl:libc_register_printf_function]]]*/
DEFINE_INTERN_ALIAS(libc_register_printf_function, libc_register_printf_specifier);

/*[[[head:libc_register_printf_modifier,hash:CRC-32=0xe89a1e5]]]*/
INTERN ATTR_SECTION(".text.crt.compat.glibc.printf") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_register_printf_modifier)(__WCHAR32_TYPE__ const *str)
/*[[[body:libc_register_printf_modifier]]]*/
/*AUTO*/{
	(void)str;
	CRT_UNIMPLEMENTEDF("register_printf_modifier(str: %p)", str); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_register_printf_modifier]]]*/

/*[[[head:libc_register_printf_type,hash:CRC-32=0xb7ea678e]]]*/
INTERN ATTR_SECTION(".text.crt.compat.glibc.printf") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_register_printf_type)(printf_va_arg_function *fct)
/*[[[body:libc_register_printf_type]]]*/
/*AUTO*/{
	(void)fct;
	CRT_UNIMPLEMENTEDF("register_printf_type(fct: %p)", fct); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_register_printf_type]]]*/

/*[[[head:libc_parse_printf_format,hash:CRC-32=0xdc912d99]]]*/
INTERN ATTR_SECTION(".text.crt.compat.glibc.printf") ATTR_OUTS(3, 2) NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_parse_printf_format)(char const *__restrict fmt,
                                               size_t n,
                                               int *__restrict argtypes)
/*[[[body:libc_parse_printf_format]]]*/
/*AUTO*/{
	(void)fmt;
	(void)n;
	(void)argtypes;
	CRT_UNIMPLEMENTEDF("parse_printf_format(fmt: %q, n: %Ix, argtypes: %p)", fmt, n, argtypes); /* TODO */
	return (size_t)libc_seterrno(ENOSYS);
}
/*[[[end:libc_parse_printf_format]]]*/

/*[[[head:libc_printf_size,hash:CRC-32=0x618e6bdf]]]*/
INTERN ATTR_SECTION(".text.crt.compat.glibc.printf") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBCCALL libc_printf_size)(FILE *__restrict fp,
                                       struct printf_info const *info,
                                       void const *const *__restrict args)
/*[[[body:libc_printf_size]]]*/
/*AUTO*/{
	(void)fp;
	(void)info;
	(void)args;
	CRT_UNIMPLEMENTEDF("printf_size(fp: %p, info: %p, args: %p)", fp, info, args); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_printf_size]]]*/

/*[[[head:libc_printf_size_info,hash:CRC-32=0xb8e9c95d]]]*/
INTERN ATTR_SECTION(".text.crt.compat.glibc.printf") NONNULL((1, 3)) int
NOTHROW_NCX(LIBCCALL libc_printf_size_info)(struct printf_info const *__restrict info,
                                            size_t n,
                                            int *__restrict argtypes)
/*[[[body:libc_printf_size_info]]]*/
/*AUTO*/{
	(void)info;
	(void)n;
	(void)argtypes;
	CRT_UNIMPLEMENTEDF("printf_size_info(info: %p, n: %Ix, argtypes: %p)", info, n, argtypes); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_printf_size_info]]]*/

/*[[[start:exports,hash:CRC-32=0xfd739d1]]]*/
DEFINE_PUBLIC_ALIAS(register_printf_specifier, libc_register_printf_specifier);
DEFINE_PUBLIC_ALIAS(register_printf_function, libc_register_printf_function);
DEFINE_PUBLIC_ALIAS(register_printf_modifier, libc_register_printf_modifier);
DEFINE_PUBLIC_ALIAS(register_printf_type, libc_register_printf_type);
DEFINE_PUBLIC_ALIAS(parse_printf_format, libc_parse_printf_format);
DEFINE_PUBLIC_ALIAS(printf_size, libc_printf_size);
DEFINE_PUBLIC_ALIAS(printf_size_info, libc_printf_size_info);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PRINTF_C */
