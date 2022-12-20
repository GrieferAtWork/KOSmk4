/* HASH CRC-32:0xc400609e */
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
#ifndef GUARD_LIBC_USER_REGEX_H
#define GUARD_LIBC_USER_REGEX_H 1

#include "../api.h"
#include "../auto/regex.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <regex.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> re_compile_pattern(3)
 * Compile a regular expression pattern (s.a. re_compiler_compile(3R)')
 * @param: pattern: Regex pattern string
 * @param: length:  Length of regex pattern string (in bytes)
 * @param: self:    The `regex_t' object to initialize.
 * @return: NULL:   Success
 * @return: * :     An error message, as would be produced by `regerror(3)' */
INTDEF ATTR_INS(1, 2) ATTR_OUT(3) char const *NOTHROW_NCX(LIBCCALL libc_re_compile_pattern)(char const *pattern, size_t length, regex_t *self);
/* >> re_search(3)
 * Perform a regex search for the first matching byte-offset in `[start,start+range)'.
 * The  accessed area of  the input buffer  is restricted to `[string,string+length)'.
 * @param: self:   The compiled regex pattern to use. NOTE: regex `eflags' are set as:
 *                  - `REG_NOTBOL = self->__not_bol'
 *                  - `REG_NOTEOL = self->__not_eol'
 *                 Sadly, this make this interface really badly designed, as this choice
 *                 (which was made by Glibc  btw), prevents multiple threads from  using
 *                 the same `regex_t' buffer simultaneously. Though note that this  same
 *                 restriction doesn't apply to  `regexec(3)', or (when targeting  KOS),
 *                 if  you completely by-pass  the `<regex.h>' API  and directly talk to
 *                 the public API of `libregex.so' from `<libregex/regexec.h>'.
 * @param: string: Base pointer for input data.
 * @param: length: Length of input data (in bytes)
 * @param: start:  Starting offset where to begin searching
 * @param: range:  The max # of searches to attempt at successive byte-offsets starting at `start'
 * @param: regs:   Group match information (like `regexec(3)'s `nmatch' and `pmatch' arguments)
 * @return: >= 0:  Was able to discover a match at this offset. (always `< range')
 * @return: -1:    No match was found
 * @return: -2:    Internal error (probably meaning out-of-memory) */
INTDEF ATTR_IN(1) ATTR_INS(2, 3) ATTR_OUT_OPT(6) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc_re_search)(regex_t __KOS_FIXED_CONST *self, char const *string, __STDC_INT_AS_SIZE_T length, __STDC_INT_AS_SIZE_T start, __STDC_INT_AS_SIZE_T range, struct __re_registers *regs);
/* >> re_search_2(3)
 * Same as `re_search(3)',  but use the  virtual concatenation of  `string1...+=length1'
 * and  `string2...+=length2' as input  buffer. Also: use `stop'  as the end-offset into
 * this  virtual buffer of where to stop  doing non-extra accessing accesses (extra data
 * accesses are positional assertion checks at the end of the regex pattern, such as '$'
 * checking  if it is followed by a line-feed being allowed to read until the actual end
 * of the virtual buffer,  whilst actual byte-matching is  only allowed to happen  until
 * an offset of `stop' bytes has been reached)
 *
 * Note that on KOS, the underlying API used is `re_exec_search(3R)' from `libregex.so'
 * and exposed in `<libregex/regexec.h>', which allows for the virtual concatenation of
 * not just 2, but an arbitrary number of buffers which are then used as input.
 *
 * @param: self:    The compiled regex pattern to use. NOTE: regex `eflags' are set as:
 *                   - `REG_NOTBOL = self->__not_bol'
 *                   - `REG_NOTEOL = self->__not_eol'
 *                  Sadly, this make this interface really badly designed, as this choice
 *                  (which was made by Glibc  btw), prevents multiple threads from  using
 *                  the same `regex_t' buffer simultaneously. Though note that this  same
 *                  restriction doesn't apply to  `regexec(3)', or (when targeting  KOS),
 *                  if  you completely by-pass  the `<regex.h>' API  and directly talk to
 *                  the public API of `libregex.so' from `<libregex/regexec.h>'.
 * @param: string1: First base pointer for input data.
 * @param: length1: Length of first input data (in bytes)
 * @param: string2: Second base pointer for input data.
 * @param: length2: Length of second input data (in bytes)
 * @param: start:   Starting offset where to begin searching
 * @param: range:   The max # of searches to attempt at successive byte-offsets starting at `start'
 * @param: regs:    Group match information (like `regexec(3)'s `nmatch' and `pmatch' arguments)
 * @param: stop:    Offset into the virtual input buffer that marks its end (must be `<= length1+length2')
 * @return: >= 0:   Was able to discover a match at this offset. (always `< range')
 * @return: -1:     No match was found
 * @return: -2:     Internal error (probably meaning out-of-memory) */
INTDEF ATTR_IN(1) ATTR_INS(2, 3) ATTR_INS(4, 5) ATTR_OUT_OPT(8) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc_re_search_2)(regex_t __KOS_FIXED_CONST *self, char const *string1, __STDC_INT_AS_SIZE_T length1, char const *string2, __STDC_INT_AS_SIZE_T length2, __STDC_INT_AS_SIZE_T start, __STDC_INT_AS_SIZE_T range, struct __re_registers *regs, __STDC_INT_AS_SIZE_T stop);
/* >> re_match(3)
 * Match input data `[string+start,string+length)' against the regex pattern `self'
 * The accessed area of the input buffer is restricted to `[string,string+length)'.
 * @param: self:   The compiled regex pattern to use. NOTE: regex `eflags' are set as:
 *                  - `REG_NOTBOL = self->__not_bol'
 *                  - `REG_NOTEOL = self->__not_eol'
 *                 Sadly, this make this interface really badly designed, as this choice
 *                 (which was made by Glibc  btw), prevents multiple threads from  using
 *                 the same `regex_t' buffer simultaneously. Though note that this  same
 *                 restriction doesn't apply to  `regexec(3)', or (when targeting  KOS),
 *                 if  you completely by-pass  the `<regex.h>' API  and directly talk to
 *                 the public API of `libregex.so' from `<libregex/regexec.h>'.
 * @param: string: Base pointer for input data.
 * @param: length: Length of input data (in bytes)
 * @param: start:  Starting offset where to begin searching
 * @param: regs:   Group match information (like `regexec(3)'s `nmatch' and `pmatch' arguments)
 * @return: >= 0:  The number of bytes starting at `start' that were matched against `self'
 * @return: -1:    No match was found
 * @return: -2:    Internal error (probably meaning out-of-memory) */
INTDEF ATTR_IN(1) ATTR_INS(2, 3) ATTR_OUT_OPT(5) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc_re_match)(regex_t __KOS_FIXED_CONST *self, char const *string, __STDC_INT_AS_SIZE_T length, __STDC_INT_AS_SIZE_T start, struct __re_registers *regs);
/* >> re_match_2(3)
 * Same  as `re_match(3)',  but use  the virtual  concatenation of `string1...+=length1'
 * and  `string2...+=length2' as input  buffer. Also: use `stop'  as the end-offset into
 * this  virtual buffer of where to stop  doing non-extra accessing accesses (extra data
 * accesses are positional assertion checks at the end of the regex pattern, such as '$'
 * checking  if it is followed by a line-feed being allowed to read until the actual end
 * of the virtual buffer,  whilst actual byte-matching is  only allowed to happen  until
 * an offset of `stop' bytes has been reached)
 *
 * Note that on KOS, the underlying API used is `re_exec_match(3R)' from  `libregex.so'
 * and exposed in `<libregex/regexec.h>', which allows for the virtual concatenation of
 * not just 2, but an arbitrary number of buffers which are then used as input.
 *
 * @param: self:    The compiled regex pattern to use. NOTE: regex `eflags' are set as:
 *                   - `REG_NOTBOL = self->__not_bol'
 *                   - `REG_NOTEOL = self->__not_eol'
 *                  Sadly, this make this interface really badly designed, as this choice
 *                  (which was made by Glibc  btw), prevents multiple threads from  using
 *                  the same `regex_t' buffer simultaneously. Though note that this  same
 *                  restriction doesn't apply to  `regexec(3)', or (when targeting  KOS),
 *                  if  you completely by-pass  the `<regex.h>' API  and directly talk to
 *                  the public API of `libregex.so' from `<libregex/regexec.h>'.
 * @param: string1: First base pointer for input data.
 * @param: length1: Length of first input data (in bytes)
 * @param: string2: Second base pointer for input data.
 * @param: length2: Length of second input data (in bytes)
 * @param: start:   Starting offset where to begin searching
 * @param: range:   The max # of searches to attempt at successive byte-offsets starting at `start'
 * @param: regs:    Group match information (like `regexec(3)'s `nmatch' and `pmatch' arguments)
 * @param: stop:    Offset into the virtual input buffer that marks its end (must be `<= length1+length2')
 * @return: >= 0:   The number of bytes starting at `start' that were matched against `self'
 * @return: -1:     No match was found
 * @return: -2:     Internal error (probably meaning out-of-memory) */
INTDEF ATTR_IN(1) ATTR_INS(2, 3) ATTR_INS(4, 5) ATTR_OUT_OPT(7) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc_re_match_2)(regex_t __KOS_FIXED_CONST *self, char const *string1, __STDC_INT_AS_SIZE_T length1, char const *string2, __STDC_INT_AS_SIZE_T length2, __STDC_INT_AS_SIZE_T start, struct __re_registers *regs, __STDC_INT_AS_SIZE_T stop);
/* >> regcomp(3)
 * Compile a regular expression `pattern' and initialize `self'
 * @param: self:    Storage for the produced regex pattern.
 * @param: pattern: The pattern to compile.
 * @param: cflags:  Set of `REG_EXTENDED | REG_ICASE | REG_NEWLINE | REG_NOSUB'
 * @return: REG_NOERROR: Success
 * @return: REG_BADPAT:  General pattern syntax error.
 * @return: REG_ECTYPE:  Invalid/unknown character class name.
 * @return: REG_EESCAPE: Trailing backslash.
 * @return: REG_ESUBREG: Invalid back reference.
 * @return: REG_EBRACK:  Unmatched '['.
 * @return: REG_EPAREN:  Unmatched '('.
 * @return: REG_EBRACE:  Unmatched '{'.
 * @return: REG_BADBR:   Invalid contents of '{...}'.
 * @return: REG_ERANGE:  Invalid range end (e.g. '[z-a]').
 * @return: REG_ESPACE:  Out of memory.
 * @return: REG_BADRPT:  Nothing is preceding '+', '*', '?' or '{'.
 * @return: REG_EEND:    Unexpected end of pattern.
 * @return: REG_ESIZE:   Compiled pattern bigger than 2^16 bytes.
 * @return: REG_ERPAREN: Unmatched ')' (only when `RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD' was set)
 * @return: REG_EILLSET: Tried to combine raw bytes with unicode characters in charsets (e.g. "[Ä\xC3]")
 * @return: REG_ENOSYS:  Unable to load `libregex.so' (shouldn't happen) */
INTDEF ATTR_IN(2) ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_regcomp)(regex_t *__restrict self, char const *__restrict pattern, int cflags);
/* >> regcomp(3)
 * Compile a regular expression `pattern' and initialize `self'
 * @param: self:   Storage for the produced regex pattern.
 * @param: string: Input data base pointer (must be a NUL-terminated string, unless `REG_STARTEND' is given)
 * @param: nmatch: Max # of group start/end-offsets to write to `*pmatch' (ignored if `REG_NOSUB' was set)
 * @param: pmatch: Storage for at least `nmatch' group start/end-offsets (ignored if `REG_NOSUB' was set)
 * @param: eflags: Set of `REG_NOTBOL | REG_NOTEOL | REG_STARTEND'
 * @return: REG_NOERROR: Success
 * @return: REG_NOMATCH: General pattern syntax error.
 * @return: REG_ESPACE:  Out of memory.
 * @return: REG_ENOSYS:  Unable to load `libregex.so' (shouldn't happen) */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_INOUTS(4, 3) int NOTHROW_NCX(LIBCCALL libc_regexec)(regex_t const *__restrict self, char const *__restrict string, size_t nmatch, regmatch_t pmatch[__restrict_arr], int eflags);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_REGEX_H */
