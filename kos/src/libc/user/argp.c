/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
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

/*[[[head:libc_argp_parse,hash:CRC-32=0xc12979bb]]]*/
/* >> argp_parse(3)
 * @param: flags: Set  of  `ARGP_PARSE_ARGV0  | ARGP_NO_ERRS  |  ARGP_NO_ARGS |
 *                ARGP_IN_ORDER | ARGP_NO_HELP | ARGP_NO_EXIT | ARGP_LONG_ONLY' */
INTERN ATTR_SECTION(".text.crt.compat.glibc.string.argp") ATTR_IN(1) ATTR_INS(3, 2) ATTR_OUT(5) error_t
NOTHROW_NCX(LIBCCALL libc_argp_parse)(struct argp const *__restrict ap,
                                      int argc,
                                      char **__restrict argv,
                                      unsigned int flags,
                                      int *__restrict arg_index,
                                      void *input)
/*[[[body:libc_argp_parse]]]*/
/*AUTO*/{
	(void)ap;
	(void)argc;
	(void)argv;
	(void)flags;
	(void)arg_index;
	(void)input;
	CRT_UNIMPLEMENTEDF("argp_parse(ap: %p, argc: %x, argv: %p, flags: %x, arg_index: %p, input: %p)", ap, argc, argv, flags, arg_index, input); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_argp_parse]]]*/

/*[[[head:libc_argp_help,hash:CRC-32=0x7cc47848]]]*/
/* >> argp_parse(3)
 * @param: flags: Set of `ARGP_HELP_*' */
INTERN ATTR_SECTION(".text.crt.compat.glibc.string.argp") ATTR_IN(1) ATTR_IN(4) ATTR_INOUT(2) void
NOTHROW_NCX(LIBCCALL libc_argp_help)(struct argp const *__restrict ap,
                                     FILE *__restrict stream,
                                     unsigned int flags,
                                     char __KOS_FIXED_CONST *__restrict name)
/*[[[body:libc_argp_help]]]*/
/*AUTO*/{
	(void)ap;
	(void)stream;
	(void)flags;
	(void)name;
	CRT_UNIMPLEMENTEDF("argp_help(ap: %p, stream: %p, flags: %x, name: %p)", ap, stream, flags, name); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_argp_help]]]*/

/*[[[head:libc_argp_state_help,hash:CRC-32=0xea770548]]]*/
/* >> argp_state_help(3)
 * @param: flags: Set of `ARGP_HELP_*' */
INTERN ATTR_SECTION(".text.crt.compat.glibc.string.argp") ATTR_INOUT_OPT(2) ATTR_IN_OPT(1) void
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



/*[[[head:libc__argp_input,hash:CRC-32=0xf61b8336]]]*/
INTERN ATTR_SECTION(".text.crt.compat.glibc.string.argp") ATTR_IN_OPT(1) ATTR_IN_OPT(2) void *
NOTHROW_NCX(LIBCCALL libc__argp_input)(struct argp const *__restrict ap,
                                       struct argp_state const *__restrict state)
/*[[[body:libc__argp_input]]]*/
/*AUTO*/{
	(void)ap;
	(void)state;
	CRT_UNIMPLEMENTEDF("_argp_input(ap: %p, state: %p)", ap, state); /* TODO */
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
