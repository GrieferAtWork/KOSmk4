/* HASH CRC-32:0xc3b859ff */
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
#ifndef GUARD_LIBC_AUTO_REGEX_C
#define GUARD_LIBC_AUTO_REGEX_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/regex.h"
#include "../user/stdlib.h"
#include "string.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
#include <libc/template/re_syntax_options.h>
/* >> re_set_syntax(3)
 * Set  the  regex  syntax used  by  `re_compile_pattern(3)', and
 * return the old default syntax (same as `re_syntax_options(3)') */
INTERN ATTR_SECTION(".text.crt.utility.regex") reg_syntax_t
NOTHROW_NCX(LIBCCALL libc_re_set_syntax)(reg_syntax_t syntax) {
	reg_syntax_t result = re_syntax_options;
	re_syntax_options   = syntax;
	return result;
}
/* >> re_compile_fastmap(3)
 * Compile the fast-map of `self'. No-op on KOS, where the fastmap is always compiled immediatly.
 * @return: 0 : Always returns `0' */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_re_compile_fastmap)(regex_t *self) {
	(void)self;
	COMPILER_IMPURE();
	return 0;
}
/* >> re_set_registers(3)
 * Initializes `regs', and sets some weird internal flag in `self' (which it doesn't do on KOS) */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_INOUT(1) ATTR_OUT(2) void
NOTHROW_NCX(LIBCCALL libc_re_set_registers)(regex_t *self,
                                            struct __re_registers *regs,
                                            unsigned int num_regs,
                                            regoff_t *starts,
                                            regoff_t *ends) {
	(void)self;
	regs->num_regs = num_regs;
	if (num_regs) {
		regs->start = starts;
		regs->end   = ends;
	} else {
		regs->start = NULL;
		regs->end   = NULL;
	}
}
/* >> regerror(3)
 * Produce a human-readable description for a regex error code `errcode' (s.a. `regerrordesc_np(3)')
 * @param: errcode: Regex error code (one of `REG_*'; s.a. `reg_errcode_t')
 * @param: self:    The compiled regex pattern that produced the error (unused in this impl)
 * @return: * :     The required buffer size (including a trailing '\0'-byte) */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_IN(2) ATTR_OUTS(3, 4) size_t
NOTHROW_NCX(LIBCCALL libc_regerror)(int errcode,
                                    regex_t const *__restrict self,
                                    char *__restrict errbuf,
                                    size_t errbuf_size) {
	char const *msg;
	size_t msglen;
	(void)self;
	msg = libc_regerrordesc_np(errcode);
	if unlikely(!msg)
		msg = "?";
	msglen = libc_strlen(msg);
	if (errbuf_size > (msglen + 1))
		errbuf_size = (msglen + 1);
	libc_memcpy(errbuf, msg, errbuf_size);
	return msglen;
}
/* >> regfree(3)
 * Free dynamic memory allocated during a successful call to `regcomp(3)'
 * @param: self: The compiled regex pattern to destroy */
INTERN ATTR_SECTION(".text.crt.utility.regex") void
NOTHROW_NCX(LIBCCALL libc_regfree)(regex_t *self) {
	libc_free(self->__REPB_PREFIX(buffer));
}
#include <asm/crt/regex.h>
/* >> regerrordesc_np(3)
 * Return a human-readable description for a given regex `errcode'
 * @param: errcode: Regex error code (one of `REG_*'; s.a. `reg_errcode_t')
 * @return: * :   The human-readable description for `errcode'
 * @return: NULL: No description is available for `errcode' */
INTERN ATTR_SECTION(".text.crt.utility.regex") ATTR_CONST WUNUSED char const *
NOTHROW_NCX(LIBCCALL libc_regerrordesc_np)(int errcode) {
	char const *result;
	switch (errcode) {

	case __REG_ENOSYS: /*  */ result = "Unable to load regex sub-system"; break;


	case __REG_NOERROR: /* */ result = "Success"; break;


	case __REG_NOMATCH: /* */ result = "No match"; break;


	case __REG_BADPAT: /*  */ result = "Invalid regex pattern"; break;


	case __REG_ECOLLATE: /**/ result = "Invalid collation character"; break;


	case __REG_ECTYPE: /*  */ result = "Invalid character class name"; break;


	case __REG_EESCAPE: /* */ result = "Trailing backslash"; break;


	case __REG_ESUBREG: /* */ result = "Invalid back reference"; break;


	case __REG_EBRACK: /*  */ result = "Unmatched [, [^, [:, [., or [="; break;


	case __REG_EPAREN: /*  */ result = "Unmatched ("; break;


	case __REG_EBRACE: /*  */ result = "Unmatched {"; break;


	case __REG_BADBR: /*   */ result = "Invalid content of {...}"; break;


	case __REG_ERANGE: /*  */ result = "Set-range start is greater than its end"; break;


	case __REG_ESPACE: /*  */ result = "Out of memory"; break;


	case __REG_BADRPT: /*  */ result = "Nothing precedes +, *, ?, or {"; break;


	case __REG_EEND: /*    */ result = "Unexpected end of pattern"; break;


	case __REG_ESIZE: /*   */ result = "Regular expression violates a hard upper limit"; break;


	case __REG_ERPAREN: /* */ result = "Unmatched )"; break;

	default: result = NULL; break;
	}
	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(re_set_syntax, libc_re_set_syntax);
DEFINE_PUBLIC_ALIAS(re_compile_fastmap, libc_re_compile_fastmap);
DEFINE_PUBLIC_ALIAS(re_set_registers, libc_re_set_registers);
DEFINE_PUBLIC_ALIAS(regerror, libc_regerror);
DEFINE_PUBLIC_ALIAS(regfree, libc_regfree);
DEFINE_PUBLIC_ALIAS(regerrordesc_np, libc_regerrordesc_np);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_REGEX_C */
