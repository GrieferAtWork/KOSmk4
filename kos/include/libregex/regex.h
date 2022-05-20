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
#ifndef _LIBREGEX_REGEX_H
#define _LIBREGEX_REGEX_H 1

#include "api.h"

#include <bits/types.h>

__DECL_BEGIN

/* Regex syntax/behavior flags. */
#define REGEX_FLAG_NORMAL                        0x00000000 /* Normal regex flags. */
#define REGEX_FLAG_DOTLF                         0x00000001 /* The `.' regex matches line-feeds */
#define REGEX_FLAG_DOTNUL                        0x00000002 /* The `.' regex matches NUL-characters */
#define REGEX_FLAG_MULTILINE                     0x00000004 /* Allow `^' to match immediately after a line-feed. (else: only match at the start of input data, unless `REGEX_FLAG_NOT_BEGIN_OF_LINE' is set)
                                                             * Allow `$' to match immediately before a  line-feed. (else: only match at the end  of input data, unless `REGEX_FLAG_NOT_END_OF_LINE' is  set) */
#define REGEX_FLAG_NOCASE                        0x00000008 /* Ignore case when matching single characters, or character ranges. */
#define REGEX_FLAG_NO_BACKSLASH_UNICODE_DECIMAL  0x00000010 /* Don't support non-standard unicode numeric matching:
                                                             *  - "(?\\d=3)" Match any unicode character for `unicode_isdigit(x) && unicode_asu64(x) == 3'
                                                             *  - "(?\\d<7)" Match any unicode character for `unicode_isdigit(x) && unicode_asu64(x) < 7'
                                                             *  - "(?\\d>4)" Match any unicode character for `unicode_isdigit(x) && unicode_asu64(x) > 4'
                                                             *  - "(?\\d<=3>=1)" Match any unicode character for `unicode_isdigit(x) && unicode_asu64(x) >= 1 && unicode_asu64(x) <= 3' */
#define REGEX_FLAG_NO_CHARACTER_CLASSES          0x00000020 /* Don't support unicode character classes in ranges */
#define REGEX_FLAG_ESCAPED_INTERVALS             0x00000040 /* Swap the meaning of { and } with \{ and \} */
#define REGEX_FLAG_ALLOW_EMPTY_RANGES            0x00000080 /* Allow (and ignore) invalid ranges, such as "[z-a]" (prevents `REGEX_ERROR_EMPTY_RANGE') */
#define REGEX_FLAG_CONTEXT_DEPENDENT_START_END   0x00000100 /* The $ and ^ operators are only recognized at the start or end of a pattern, and in "abc(^foo$|^bar$)def" */
#define REGEX_FLAG_CONTEXT_DEPENDENT_REPEAT      0x00000200 /* The {, }, *, + and ? operators are only recognized as operators when used as a suffix. Elsewhere, they are matched as raw characters. */
#define REGEX_FLAG_CONTEXT_DEPENDENT_GROUPS      0x00000400 /* The | and ) operators are only recognized within groups. Elsewhere, they are matched as a raw character. */
#define REGEX_FLAG_CONTEXT_DEPENDENT_RANGES      0x00000800 /* The ] operator is only recognized after a preceding [. Elsewhere, it are matched as a raw character. */
#define REGEX_FLAG_NOT_BEGIN_OF_LINE             0x00001000 /* The ^ operator don't match the start of input data */
#define REGEX_FLAG_NOT_END_OF_LINE               0x00002000 /* The $ operator don't match the end of input data */
#define REGEX_FLAG_ESCAPED_GROUPS                0x00004000 /* Swap the meaning of ( and ) with \( and \) */
#define REGEX_FLAG_RANGE_NOT_NEWLINE             0x00008000 /* Inverse ranges [^...] do not match line-feed characters */
#define REGEX_FLAG_LIMITED_OPERATORS             0x00010000 /* Disable recognition of +, ? and |  (though does not disable \+ and \? with `REGEX_FLAG_ESCAPED_PLUS_QUESTIONMASK', or \| with `REGEX_FLAG_ESCAPED_PIPE') */
#define REGEX_FLAG_NEWLINE_IS_PIPE               0x00020000 /* line-feed characters within the pattern are recognized as the |-operator (though matched normally elsewhere) */
#define REGEX_FLAG_ESCAPED_PIPE                  0x00040000 /* Swap the meaning of | with \| */
#define REGEX_FLAG_IGNORE_INVALID_INTERVALS      0x00080000 /* Invalid intervals are matched as a raw character */
#define REGEX_FLAG_NO_BACKSLASH_IN_RANGES        0x00100000 /* Disable support for escaping in ranges "[\n]" will match \ or n */
#define REGEX_FLAG_ESCAPED_PLUS_QUESTIONMASK     0x00200000 /* Swap the meaning of + and ? with \+ and \? */
#define REGEX_FLAG_NO_INTERVALS                  0x00400000 /* Disable support for intervals (causes `REGEX_FLAG_ESCAPED_INTERVALS' and `REGEX_FLAG_IGNORE_INVALID_INTERVALS' to be ignored) */
#define REGEX_FLAG_NO_BACKSLASH_DIGIT            0x00800000 /* Disable support for `\<1-9>' matching for unicode decimal characters with the same value */
#define REGEX_FLAG_IGNORE_NOOP_PATTERNS          0x80000000 /* Don't produce the following errors:
                                                             *  - REGEX_ERROR_LBRACE_BOUND_ORDER
                                                             *  - REGEX_ERROR_LBRACE_BOUND_UPPER_ZERO
                                                             *  - REGEX_ERROR_DIGIT_RANGE_IMPOSSIBLE
                                                             *  - REGEX_ERROR_POSITIVE_LOOKAHEAD_BOUND_LOWER_ZERO */


/* Regex error codes. */
#define REGEX_ERROR_BADALLOC                             (-1) /* A heap allocation failed */
#define REGEX_ERROR_LBRACE_UNMATCHED                     (-2) /* Unmatched `{' (pattern end was reached) */
#define REGEX_ERROR_LBRACE_NO_COMMA_OR_DECIMAL           (-3) /* Expected `,' or a decimal after "{" */
#define REGEX_ERROR_LBRACE_NO_COMMA                      (-4) /* Expected `,' after "{:decimal:" */
#define REGEX_ERROR_LBRACE_NO_RBRACE                     (-5) /* Expected `}' after "{:[decimal]:,:[decimal]:" */
#define REGEX_ERROR_LBRACE_BOUND_ORDER                   (-6) /* :Upper: < :Lower: in "{:Lower:,:Upper:}" */
#define REGEX_ERROR_LBRACE_BOUND_UPPER_ZERO              (-7) /* :Upper: == 0 in "{:[Lower]:,:Upper:}" */
#define REGEX_ERROR_DIGIT_RANGE_NO_DECIMAL               (-8) /* Expected a decimal after "(?\d:[Lower]:<:[=]:" or "(?\d>:[=]:" or "(?\d=" */
#define REGEX_ERROR_DIGIT_RANGE_IMPOSSIBLE               (-9) /* Impossible digit range "(?\d<0)" or "(?\d>255)" */
#define REGEX_ERROR_DIGIT_RANGE_BADTAIL                 (-10) /* Expected `)' after "(?\d:[Lower]::SOME_OP::[Upper]:" */
#define REGEX_ERROR_POSITIVE_LOOKAHEAD_BOUND_LOWER_ZERO (-11) /* :Lower: == 0 in "(?=...){:Lower:,:Upper:}" (or "(?=...)?", "(?=...)*", ...) */
#define REGEX_ERROR_UNKNOWN_FLAG                        (-12) /* Unknown regex flag in "(?:~ims:...)" (only ~ims are recognized) */
#define REGEX_ERROR_UNKNOWN_EXTENSION                   (-13) /* Unknown extension character :C: in "(?:C:..." */
#define REGEX_ERROR_PIPE_OUTSIDE_OF_PAREN               (-14) /* The |-operator was used outside of parenthesis */
#define REGEX_ERROR_RPAREN_UNEXPECTED                   (-15) /* An unmatched )-character was encountered */
#define REGEX_ERROR_REPEAT_UNEXPECTED                   (-16) /* *, +, ? can only appear as a suffix */
#define REGEX_ERROR_LBRACE_UNEXPECTED                   (-17) /* { can only appear as a suffix */
#define REGEX_ERROR_RBRACE_UNMATCHED                    (-18) /* An unmatched }-character was encountered */
#define REGEX_ERROR_LBRACKET_UNMATCHED                  (-19) /* Unmatched `[' (pattern end was reached) */
#define REGEX_ERROR_RBRACKET_UNEXPECTED                 (-20) /* An unmatched ]-character was encountered */
#define REGEX_ERROR_ESCAPE_END_OF_PATTERN               (-21) /* A \-character was encountered at the end of a pattern */
#define REGEX_ERROR_UNKNOWN_CHARACTER_TRAIT             (-22) /* Trait <Trait> wasn't recognized in "[:<Trait>:]" */
#define REGEX_ERROR_EMPTY_RANGE                         (-23) /* An empty range (e.g. "[z-a]") was encountered.  */
#define REGEX_ERROR_LAST                               (-128) /* Last error */
#define REGEX_ISERROR(x) ((__size_t)(x) >= (__size_t)REGEX_ERROR_LAST)


#ifdef __CC__
/* Given a regular expression `pattern', check if it
 * matches the string found in `data', returning the
 * number of bytes in `data' that are being matched,
 * or `0' if the pattern doesn't match.
 * @param: datalen:           Number of bytes (not characters) in data.
 * @param: patternlen:        Number of bytes (not characters) in pattern.
 * @return: * :               Number of characters (not bytes) matched in `data'.
 * @return: 0 :               Pattern not found.
 * @return: REGEX_ISERROR(*): Error. */
typedef __ATTR_NONNULL_T((1, 3)) __size_t
(LIBREGEX_CC *PREGEX_MATCHES)(/*utf-8*/ char const *__restrict data, __size_t datalen,
                              /*utf-8*/ char const *__restrict pattern, __size_t patternlen,
                              __uintptr_t flags);
#ifdef LIBREGEX_WANT_PROTOTYPES
LIBREGEX_DECL __ATTR_NONNULL((1, 3)) __size_t LIBREGEX_CC
regex_matches(/*utf-8*/ char const *__restrict data, __size_t datalen,
              /*utf-8*/ char const *__restrict pattern, __size_t patternlen,
              __uintptr_t flags);
#endif /* LIBREGEX_WANT_PROTOTYPES */


/* Same as `regex_matches()',  but also  store a  pointer to  the end  of
 * consumed data in `pdataend'. Because input data is formatted in UTF-8,
 * this position would only be equal to `data + return' if all input data
 * was ASCII  only, meaning  that in  the universal  case, this  function
 * becomes useful when dealing with unicode data.
 * @param: pdataend:          Upon success (return != 0 && return != (size_t)-1),
 *                            save a pointer  to the end  of consumed data  here.
 * @param: datalen:           Number of bytes (not characters) in data.
 * @param: patternlen:        Number of bytes (not characters) in pattern.
 * @return: * :               Number of characters (not bytes) matched in `data'.
 * @return: 0 :               Pattern not found.
 * @return: REGEX_ISERROR(*): Error. */
typedef __ATTR_NONNULL_T((1, 3, 5)) __size_t
(LIBREGEX_CC *PREGEX_MATCHESPTR)(/*utf-8*/ char const *__restrict data, __size_t datalen,
                                 /*utf-8*/ char const *__restrict pattern, __size_t patternlen,
                                 /*utf-8*/ char const **__restrict pdataend,
                                 __uintptr_t flags);
#ifdef LIBREGEX_WANT_PROTOTYPES
LIBREGEX_DECL __ATTR_NONNULL((1, 3, 5)) __size_t LIBREGEX_CC
regex_matchesptr(/*utf-8*/ char const *__restrict data, __size_t datalen,
                 /*utf-8*/ char const *__restrict pattern, __size_t patternlen,
                 /*utf-8*/ char const **__restrict pdataend,
                 __uintptr_t flags);
#endif /* LIBREGEX_WANT_PROTOTYPES */



struct regex_range {
	__size_t rr_start; /* Starting character index. */
	__size_t rr_end;   /* End character index. */
};
struct regex_range_ptr {
	char    *rr_start; /* Starting character pointer. */
	char    *rr_end;   /* End character pointer. */
};
struct regex_range_ex {
	__size_t rr_start;     /* Starting character index. */
	__size_t rr_end;       /* End character index. */
	char    *rr_start_ptr; /* Starting character pointer. */
	char    *rr_end_ptr;   /* End character pointer. */
};


/* Find the  first instance  matching  `pattern' and  store  the
 * character indices (not byte offsets) in `*pstart' and `*pend'
 * @return: 1:                Pattern was found.
 * @return: 0:                Pattern not found.
 * @return: REGEX_ISERROR(*): Error. */
typedef __ATTR_NONNULL_T((1, 3, 5)) int
(LIBREGEX_CC *PREGEX_FIND)(/*utf-8*/ char const *__restrict data, __size_t datalen,
                           /*utf-8*/ char const *__restrict pattern, __size_t patternlen,
                           struct regex_range *__restrict presult, __uintptr_t flags);
typedef __ATTR_NONNULL_T((1, 3, 5)) int
(LIBREGEX_CC *PREGEX_RFIND)(/*utf-8*/ char const *__restrict data, __size_t datalen,
                            /*utf-8*/ char const *__restrict pattern, __size_t patternlen,
                            struct regex_range *__restrict presult, __uintptr_t flags);
#ifdef LIBREGEX_WANT_PROTOTYPES
LIBREGEX_DECL __ATTR_NONNULL((1, 3, 5)) int LIBREGEX_CC
regex_find(/*utf-8*/ char const *__restrict data, __size_t datalen,
           /*utf-8*/ char const *__restrict pattern, __size_t patternlen,
           struct regex_range *__restrict presult, __uintptr_t flags);
LIBREGEX_DECL __ATTR_NONNULL((1, 3, 5)) int LIBREGEX_CC
regex_rfind(/*utf-8*/ char const *__restrict data, __size_t datalen,
            /*utf-8*/ char const *__restrict pattern, __size_t patternlen,
            struct regex_range *__restrict presult, __uintptr_t flags);
#endif /* LIBREGEX_WANT_PROTOTYPES */

/* Same as the functions above, but return character pointers, rather than indices. */
typedef __ATTR_NONNULL_T((1, 3, 5)) int
(LIBREGEX_CC *PREGEX_FINDPTR)(/*utf-8*/ char const *__restrict data, __size_t datalen,
                              /*utf-8*/ char const *__restrict pattern, __size_t patternlen,
                              struct regex_range_ptr *__restrict presult, __uintptr_t flags);
typedef __ATTR_NONNULL_T((1, 3, 5)) int
(LIBREGEX_CC *PREGEX_RFINDPTR)(/*utf-8*/ char const *__restrict data, __size_t datalen,
                               /*utf-8*/ char const *__restrict pattern, __size_t patternlen,
                               struct regex_range_ptr *__restrict presult, __uintptr_t flags);
#ifdef LIBREGEX_WANT_PROTOTYPES
LIBREGEX_DECL __ATTR_NONNULL((1, 3, 5)) int LIBREGEX_CC
regex_findptr(/*utf-8*/ char const *__restrict data, __size_t datalen,
              /*utf-8*/ char const *__restrict pattern, __size_t patternlen,
              struct regex_range_ptr *__restrict presult, __uintptr_t flags);
LIBREGEX_DECL __ATTR_NONNULL((1, 3, 5)) int LIBREGEX_CC
regex_rfindptr(/*utf-8*/ char const *__restrict data, __size_t datalen,
               /*utf-8*/ char const *__restrict pattern, __size_t patternlen,
               struct regex_range_ptr *__restrict presult, __uintptr_t flags);
#endif /* LIBREGEX_WANT_PROTOTYPES */

/* Same as the functions above, but return both character indices _and_ pointers. */
typedef __ATTR_NONNULL_T((1, 3, 5)) int
(LIBREGEX_CC *PREGEX_FINDEX)(/*utf-8*/ char const *__restrict data, __size_t datalen,
                             /*utf-8*/ char const *__restrict pattern, __size_t patternlen,
                             struct regex_range_ex *__restrict presult, __uintptr_t flags);
typedef __ATTR_NONNULL_T((1, 3, 5)) int
(LIBREGEX_CC *PREGEX_RFINDEX)(/*utf-8*/ char const *__restrict data, __size_t datalen,
                              /*utf-8*/ char const *__restrict pattern, __size_t patternlen,
                              struct regex_range_ex *__restrict presult, __uintptr_t flags);
#ifdef LIBREGEX_WANT_PROTOTYPES
LIBREGEX_DECL __ATTR_NONNULL((1, 3, 5)) int LIBREGEX_CC
regex_findex(/*utf-8*/ char const *__restrict data, __size_t datalen,
             /*utf-8*/ char const *__restrict pattern, __size_t patternlen,
             struct regex_range_ex *__restrict presult, __uintptr_t flags);
LIBREGEX_DECL __ATTR_NONNULL((1, 3, 5)) int LIBREGEX_CC
regex_rfindex(/*utf-8*/ char const *__restrict data, __size_t datalen,
              /*utf-8*/ char const *__restrict pattern, __size_t patternlen,
              struct regex_range_ex *__restrict presult, __uintptr_t flags);
#endif /* LIBREGEX_WANT_PROTOTYPES */
#endif /* __CC__ */



__DECL_END

#endif /* !_LIBREGEX_REGEX_H */
