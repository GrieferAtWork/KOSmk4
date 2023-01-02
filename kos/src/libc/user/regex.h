/* HASH CRC-32:0x43fb0d2e */
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
 * @return: REG_NOERROR:  Success
 * @return: REG_BADPAT:   General pattern syntax error.
 * @return: REG_ECOLLATE: Unsupported/unknown collating character (in '[[.xxx.]]' and '[[=xxx=]]')
 * @return: REG_ECTYPE:   Invalid/unknown character class name.
 * @return: REG_EESCAPE:  Trailing backslash.
 * @return: REG_ESUBREG:  Invalid back reference.
 * @return: REG_EBRACK:   Unmatched '['.
 * @return: REG_EPAREN:   Unmatched '('.
 * @return: REG_EBRACE:   Unmatched '{'.
 * @return: REG_BADBR:    Invalid contents of '{...}'.
 * @return: REG_ERANGE:   Invalid range end (e.g. '[z-a]').
 * @return: REG_ESPACE:   Out of memory.
 * @return: REG_BADRPT:   Nothing is preceding '+', '*', '?' or '{'.
 * @return: REG_EEND:     Unexpected end of pattern.
 * @return: REG_ESIZE:    Compiled pattern bigger than 2^16 bytes.
 * @return: REG_ERPAREN:  Unmatched ')' (only when `RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD' was set)
 * @return: REG_EILLSEQ:  Illegal unicode character (when `RE_NO_UTF8' wasn't set)
 * @return: REG_EILLSET:  Tried to combine raw bytes with unicode characters in charsets (e.g. "[Ä\xC3]")
 * @return: REG_ENOSYS:   Unable to load `libregex.so' (shouldn't happen) */
INTDEF ATTR_IN(2) ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_regcomp)(regex_t *__restrict self, char const *__restrict pattern, int cflags);
/* >> regexec(3)
 * Execute a compiled regular expression `pattern' on the priveded string.
 * - This function searches for the FIRST position in `string' at which `self' can be matched.
 * - When `nmatch > 0' (and `REG_NOSUB' wasn't set), the matched address-range is stored in `pmatch[0]'
 * - When `nmatch > 1' (and `REG_NOSUB' wasn't set), the start/end-offsets of "(...)"-groups are stored
 *   here for up to the  first `nmatch - 1' groups. Non-existant groups  are assigned `-1' in  offsets.
 * - When nothing was matched, and `nmatch > 0' (and `REG_NOSUB' wasn't set), the offsets of all elements
 *   of `pmatch' are set to `-1' (thus indicating a lack of any sort of match).
 * @param: self:   The compiled regex pattern.
 * @param: string: Input data that should be matched (must be a NUL-terminated string, unless `REG_STARTEND' is given)
 * @param: nmatch: one plus max # of group start/end-offsets to write to `*pmatch' (ignored if `REG_NOSUB' was set)
 *                 When non-zero, `pmatch[0]' will receive the start/end offsets where `self' matched in  `string'.
 * @param: pmatch: Storage for at least `nmatch' group start/end-offsets (ignored if `REG_NOSUB' was set)
 * @param: eflags: Set of `REG_NOTBOL | REG_NOTEOL | REG_STARTEND'
 * @return: 0:           Success
 * @return: REG_NOMATCH: Nothing was matched, or some internal error happened */
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_regexec)(regex_t const *__restrict self, char const *__restrict string, size_t nmatch, regmatch_t pmatch[__restrict_arr], int eflags);
/* >> re_comp(3)
 * Compare the given `pattern' and assign it to an internal regex buffer which can
 * then later be used in conjunction with `re_exec(3)'. The Syntax options used by
 * this function are  `re_syntax_options | RE_ANCHORS_IGNORE_EFLAGS'. By  default,
 * the global `re_syntax_options' is set to `RE_SYNTAX_EMACS'.
 * WARNING: This function is not thread-safe!
 * @param: pattern: The pattern to compile (or `NULL' to verify that a pattern has already been compiled)
 * @return: NULL:   Success
 * @return: * :     Error (returned pointer is the human-readable error message, as returned by `regerrordesc_np(3)')
 *                  In this case, the internal, static regex buffer is left unaltered. */
INTDEF char __KOS_FIXED_CONST *NOTHROW_NCX(LIBCCALL libc_re_comp)(char const *pattern);
/* >> re_exec(3)
 * Try to match the regex previous compiled by `re_comp(3)'
 * against some sub-string of `string'. This is equivalent to:
 * >> re_search(&REGEX_COMPILED_BY_RE_COMP, // self
 * >>           string,                     // string
 * >>           strlen(string),             // length
 * >>           0,                          // start
 * >>           strlen(string),             // range
 * >>           NULL) >= 0                  // regs
 * Note that to  force matching to  only happen at  the start of  `string',
 * the pattern passed to `re_comp(3)' should begin with "^" (thus requiring
 * that the pattern only matches at the start, or after a line-feed).
 *
 * If `re_comp(3)' has never been called, always returns `0'
 * @param: string: The pattern to compile (or `NULL' to verify that a pattern has already been compiled)
 * @return: 1:     The given `string' contains (at least) one matching sub-string
 * @return: 0:     The given `string' does not contain a sub-string that matches the previously compiled pattern. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_re_exec)(char const *string);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_REGEX_H */
