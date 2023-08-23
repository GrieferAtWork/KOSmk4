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
#ifndef GUARD_LIBC_USER_ARGP_C
#define GUARD_LIBC_USER_ARGP_C 1

#include "../api.h"
/**/

#include "argp.h"

DECL_BEGIN

/*[[[head:libc_argp_parse,hash:CRC-32=0xd4e721c6]]]*/
INTERN ATTR_SECTION(".text.crt.compat.glibc.string.argp") ATTR_IN(1) ATTR_INS(3, 2) ATTR_OUT(5) error_t
NOTHROW_NCX(LIBCCALL libc_argp_parse)(struct argp const *__restrict argp,
                                      int argc,
                                      char **__restrict argv,
                                      unsigned int flags,
                                      int *__restrict arg_index,
                                      void *__restrict input)
/*[[[body:libc_argp_parse]]]*/
/*AUTO*/{
	(void)argp;
	(void)argc;
	(void)argv;
	(void)flags;
	(void)arg_index;
	(void)input;
	CRT_UNIMPLEMENTEDF("argp_parse(argp: %p, argc: %x, argv: %p, flags: %x, arg_index: %p, input: %p)", argp, argc, argv, flags, arg_index, input); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_argp_parse]]]*/

/*[[[head:libc_argp_help,hash:CRC-32=0xaa15eb1f]]]*/
INTERN ATTR_SECTION(".text.crt.compat.glibc.string.argp") ATTR_IN(1) ATTR_IN(4) ATTR_INOUT(2) void
NOTHROW_NCX(LIBCCALL libc_argp_help)(struct argp const *__restrict argp,
                                     FILE *__restrict stream,
                                     unsigned int flags,
                                     char __KOS_FIXED_CONST *__restrict name)
/*[[[body:libc_argp_help]]]*/
/*AUTO*/{
	(void)argp;
	(void)stream;
	(void)flags;
	(void)name;
	CRT_UNIMPLEMENTEDF("argp_help(argp: %p, stream: %p, flags: %x, name: %p)", argp, stream, flags, name); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_argp_help]]]*/

/*[[[head:libc_argp_state_help,hash:CRC-32=0x444ea592]]]*/
INTERN ATTR_SECTION(".text.crt.compat.glibc.string.argp") ATTR_IN(1) ATTR_INOUT(2) void
NOTHROW_NCX(LIBCCALL libc_argp_state_help)(struct argp_state const *__restrict state,
                                           FILE *__restrict stream,
                                           unsigned int flags)
/*[[[body:libc_argp_state_help]]]*/
/*AUTO*/{
	(void)state;
	(void)stream;
	(void)flags;
	CRT_UNIMPLEMENTEDF("argp_state_help(state: %p, stream: %p, flags: %x)", state, stream, flags); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_argp_state_help]]]*/

/*[[[head:libc_argp_verror,hash:CRC-32=0xc4511992]]]*/
INTERN ATTR_SECTION(".text.crt.compat.glibc.string.argp") ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0) void
NOTHROW_NCX(LIBCCALL libc_argp_verror)(struct argp_state const *__restrict state,
                                       char const *__restrict format,
                                       va_list args)
/*[[[body:libc_argp_verror]]]*/
/*AUTO*/{
	(void)state;
	(void)format;
	(void)args;
	CRT_UNIMPLEMENTEDF("argp_verror(state: %p, format: %q, args: %p)", state, format, args); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_argp_verror]]]*/

/*[[[head:libc_argp_vfailure,hash:CRC-32=0x36552b0a]]]*/
INTERN ATTR_SECTION(".text.crt.compat.glibc.string.argp") ATTR_IN(1) ATTR_IN(4) ATTR_LIBC_PRINTF(4, 0) void
NOTHROW_NCX(LIBCCALL libc_argp_vfailure)(struct argp_state const *__restrict state,
                                         int status,
                                         errno_t errnum,
                                         char const *__restrict format,
                                         va_list args)
/*[[[body:libc_argp_vfailure]]]*/
/*AUTO*/{
	(void)state;
	(void)status;
	(void)errnum;
	(void)format;
	(void)args;
	CRT_UNIMPLEMENTEDF("argp_vfailure(state: %p, status: %x, errnum: %" PRIxN(__SIZEOF_ERRNO_T__) ", format: %q, args: %p)", state, status, errnum, format, args); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_argp_vfailure]]]*/

/*[[[head:libc__argp_input,hash:CRC-32=0xe5d8ebe3]]]*/
INTERN ATTR_SECTION(".text.crt.compat.glibc.string.argp") ATTR_IN_OPT(1) ATTR_IN_OPT(2) void *
NOTHROW_NCX(LIBCCALL libc__argp_input)(struct argp const *__restrict argp,
                                       struct argp_state const *__restrict state)
/*[[[body:libc__argp_input]]]*/
/*AUTO*/{
	(void)argp;
	(void)state;
	CRT_UNIMPLEMENTEDF("_argp_input(argp: %p, state: %p)", argp, state); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__argp_input]]]*/

/*[[[start:exports,hash:CRC-32=0xfac959b3]]]*/
DEFINE_PUBLIC_ALIAS(__argp_parse, libc_argp_parse);
DEFINE_PUBLIC_ALIAS(argp_parse, libc_argp_parse);
DEFINE_PUBLIC_ALIAS(__argp_parse, libc_argp_help);
DEFINE_PUBLIC_ALIAS(argp_help, libc_argp_help);
DEFINE_PUBLIC_ALIAS(__argp_state_help, libc_argp_state_help);
DEFINE_PUBLIC_ALIAS(argp_state_help, libc_argp_state_help);
DEFINE_PUBLIC_ALIAS(__argp_input, libc__argp_input);
DEFINE_PUBLIC_ALIAS(_argp_input, libc__argp_input);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_ARGP_C */
