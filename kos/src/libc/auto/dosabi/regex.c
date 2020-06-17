/* HASH CRC-32:0x622e76e7 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_REGEX_C
#define GUARD_LIBC_AUTO_DOSABI_REGEX_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/regex.h"

DECL_BEGIN

/* Sets the current default syntax to SYNTAX, and return the old syntax.
 * You can also simply assign to the `re_syntax_options' variable */
INTERN ATTR_SECTION(".text.crt.dos.utility.regex") reg_syntax_t
NOTHROW_NCX(LIBDCALL libd_re_set_syntax)(reg_syntax_t syntax) {
	return libc_re_set_syntax(syntax);
}
/* Compile the regular expression PATTERN, with length LENGTH
 * and syntax given by the global `re_syntax_options', into the buffer
 * BUFFER. Return NULL if successful, and an error string if not.
 * To free the allocated storage, you must call `regfree' on BUFFER.
 * Note that the translate table must either have been initialized by
 * `regcomp', with a malloc'd value, or set to NULL before calling `regfree' */
INTERN ATTR_SECTION(".text.crt.dos.utility.regex") char const *
NOTHROW_NCX(LIBDCALL libd_re_compile_pattern)(char const *pattern,
                                              size_t length,
                                              struct re_pattern_buffer *buffer) {
	return libc_re_compile_pattern(pattern, length, buffer);
}
/* Compile a fastmap for the compiled pattern in BUFFER; used to
 * accelerate searches. Return 0 if successful and -2 if was an internal error */
INTERN ATTR_SECTION(".text.crt.dos.utility.regex") int
NOTHROW_NCX(LIBDCALL libd_re_compile_fastmap)(struct re_pattern_buffer *buffer) {
	return libc_re_compile_fastmap(buffer);
}
/* Search in the string STRING (with length LENGTH) for the pattern
 * compiled into BUFFER. Start searching at position START, for RANGE
 * characters. Return the starting position of the match, -1 for no
 * match, or -2 for an internal error. Also return register
 * information in REGS (if REGS and BUFFER->no_sub are nonzero) */
INTERN ATTR_SECTION(".text.crt.dos.utility.regex") int
NOTHROW_NCX(LIBDCALL libd_re_search)(struct re_pattern_buffer *buffer,
                                     char const *string,
                                     int length,
                                     int start,
                                     int range,
                                     struct re_registers *regs) {
	return libc_re_search(buffer, string, length, start, range, regs);
}
/* Like `re_search', but search in the concatenation of STRING1
 * and STRING2. Also, stop searching at index START + STOP */
INTERN ATTR_SECTION(".text.crt.dos.utility.regex") int
NOTHROW_NCX(LIBDCALL libd_re_search_2)(struct re_pattern_buffer *buffer,
                                       char const *string1,
                                       int length1,
                                       char const *string2,
                                       int length2,
                                       int start,
                                       int range,
                                       struct re_registers *regs,
                                       int stop) {
	return libc_re_search_2(buffer, string1, length1, string2, length2, start, range, regs, stop);
}
/* Like `re_search', but return how many characters in STRING
 * the regexp in BUFFER matched, starting at position START */
INTERN ATTR_SECTION(".text.crt.dos.utility.regex") int
NOTHROW_NCX(LIBDCALL libd_re_match)(struct re_pattern_buffer *buffer,
                                    char const *string,
                                    int length,
                                    int start,
                                    struct re_registers *regs) {
	return libc_re_match(buffer, string, length, start, regs);
}
/* Relates to `re_match' as `re_search_2' relates to `re_search' */
INTERN ATTR_SECTION(".text.crt.dos.utility.regex") int
NOTHROW_NCX(LIBDCALL libd_re_match_2)(struct re_pattern_buffer *buffer,
                                      char const *string1,
                                      int length1,
                                      char const *string2,
                                      int length2,
                                      int start,
                                      struct re_registers *regs,
                                      int stop) {
	return libc_re_match_2(buffer, string1, length1, string2, length2, start, regs, stop);
}
/* Set REGS to hold NUM_REGS registers, storing them in STARTS and
 * ENDS. Subsequent matches using BUFFER and REGS will use this memory
 * for recording register information. STARTS and ENDS must be allocated
 * with malloc, and must each be at least `NUM_REGS * sizeof(regoff_t)' bytes long.
 * If NUM_REGS == 0, then subsequent matches should allocate their own register data.
 * Unless this function is called, the first search or match using
 * PATTERN_BUFFER will allocate its own register data, without freeing the old data */
INTERN ATTR_SECTION(".text.crt.dos.utility.regex") void
NOTHROW_NCX(LIBDCALL libd_re_set_registers)(struct re_pattern_buffer *buffer,
                                            struct re_registers *regs,
                                            unsigned int num_regs,
                                            regoff_t *starts,
                                            regoff_t *ends) {
	libc_re_set_registers(buffer, regs, num_regs, starts, ends);
}
INTERN ATTR_SECTION(".text.crt.dos.utility.regex") int
NOTHROW_NCX(LIBDCALL libd_regcomp)(regex_t *__restrict preg,
                                   char const *__restrict pattern,
                                   int cflags) {
	return libc_regcomp(preg, pattern, cflags);
}
INTERN ATTR_SECTION(".text.crt.dos.utility.regex") int
NOTHROW_NCX(LIBDCALL libd_regexec)(regex_t const *__restrict preg,
                                   char const *__restrict string,
                                   size_t nmatch,
                                   regmatch_t pmatch[__restrict_arr],
                                   int eflags) {
	return libc_regexec(preg, string, nmatch, pmatch, eflags);
}
INTERN ATTR_SECTION(".text.crt.dos.utility.regex") size_t
NOTHROW_NCX(LIBDCALL libd_regerror)(int errcode,
                                    regex_t const *__restrict preg,
                                    char *__restrict errbuf,
                                    size_t errbuf_size) {
	return libc_regerror(errcode, preg, errbuf, errbuf_size);
}
INTERN ATTR_SECTION(".text.crt.dos.utility.regex") void
NOTHROW_NCX(LIBDCALL libd_regfree)(regex_t *preg) {
	libc_regfree(preg);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$re_set_syntax, libd_re_set_syntax);
DEFINE_PUBLIC_ALIAS(DOS$re_compile_pattern, libd_re_compile_pattern);
DEFINE_PUBLIC_ALIAS(DOS$re_compile_fastmap, libd_re_compile_fastmap);
DEFINE_PUBLIC_ALIAS(DOS$re_search, libd_re_search);
DEFINE_PUBLIC_ALIAS(DOS$re_search_2, libd_re_search_2);
DEFINE_PUBLIC_ALIAS(DOS$re_match, libd_re_match);
DEFINE_PUBLIC_ALIAS(DOS$re_match_2, libd_re_match_2);
DEFINE_PUBLIC_ALIAS(DOS$re_set_registers, libd_re_set_registers);
DEFINE_PUBLIC_ALIAS(DOS$regcomp, libd_regcomp);
DEFINE_PUBLIC_ALIAS(DOS$regexec, libd_regexec);
DEFINE_PUBLIC_ALIAS(DOS$regerror, libd_regerror);
DEFINE_PUBLIC_ALIAS(DOS$regfree, libd_regfree);

#endif /* !GUARD_LIBC_AUTO_DOSABI_REGEX_C */
