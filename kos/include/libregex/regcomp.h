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
#ifndef _LIBREGEX_REGCOMP_H
#define _LIBREGEX_REGCOMP_H 1

#include "api.h"

#ifndef LIBREGEX_NO_SYSTEM_INCLUDES
#include <bits/types.h>

#include <libc/string.h>
#include <libc/malloc.h>

#ifndef NDEBUG
#include <bits/crt/format-printer.h>
#endif /* !NDEBUG */
#endif /* !LIBREGEX_NO_SYSTEM_INCLUDES */

__DECL_BEGIN

/* RE error codes */
typedef int re_errno_t;
#define RE_NOERROR  0  /* Success. */
#define RE_NOMATCH  1  /* Didn't find a match (for `regexec(3)'). */
#define RE_BADPAT   2  /* General pattern syntax error. */
#define RE_ECOLLATE 3  /* Unsupported/unknown collating character (in '[[.xxx.]]' and '[[=xxx=]]') */
#define RE_ECTYPE   4  /* Invalid/unknown character class name. */
#define RE_EESCAPE  5  /* Trailing '\'. */
#define RE_ESUBREG  6  /* Back reference to group that was never initialized. */
#define RE_EBRACK   7  /* Unmatched '['. */
#define RE_EPAREN   8  /* Unmatched '('. */
#define RE_EBRACE   9  /* Unmatched '{'. */
#define RE_BADBR    10 /* Invalid contents of '{...}'. */
#define RE_ERANGE   11 /* Invalid range end (e.g. '[z-a]'). */
#define RE_ESPACE   12 /* Out of memory. */
#define RE_BADRPT   13 /* Nothing is preceding '+', '*', '?' or '{'. */
#define RE_EEND     14 /* Unexpected end of pattern. */
#define RE_ESIZE    15 /* Too large (pattern violates some hard limit that isn't the currently available ram) */
#define RE_ERPAREN  16 /* Unmatched ')' (only when `RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD' was set) */
#define RE_EILLSEQ  17 /* Illegal unicode character (when `RE_NO_UTF8' wasn't set) */
#define RE_EILLSET  18 /* Tried to combine raw bytes with unicode characters in charsets (e.g. "[Ä\xC3]") */



/* RE instruction stream opcodes
 *
 * ================================================ Compilation ================================================
 *
 * Simple matches:
 *     >> "x"                    REOP_BYTE 'x'
 *     >> "abc"                  REOP_EXACT "abc"
 *     >> "."                    REOP_ANY
 *     >> "[<x>]"                REOP_BYTE 'x'            (can be used to escape other characters)
 *     >> "\\"                   REOP_BYTE '\'
 *     >> "\<x>"                 REOP_BYTE 'x'            (caution: many characters here have special meaning!)
 *     >> "[a-z]"                REOP_BITSET "[a-z]"      (NOTE: multi-byte utf-8 characters are encoded using `REOP_CONTAINS_UTF8')
 *     >> "[^a-z]"               REOP_BITSET_NOT "[a-z]"  (NOTE: multi-byte utf-8 characters are encoded using `REOP_NCONTAINS_UTF8')
 *     >> "\<1-9>"               REOP_GROUP_MATCH <1-9>   // Replaced by `REOP_GROUP_MATCH_Jn' if followed by a repeat-suffix
 *     >> "\w"                   <[[:symcont:]]>          (HINT: Also allowed in []-sets when RE_SYNTAX_BACKSLASH_ESCAPE_IN_LISTS && !RE_SYNTAX_NO_KOS_OPS)
 *     >> "\W"                   <[^[:symcont:]]>
 *     >> "\n"                   <[[:lf:]]>               (HINT: Also allowed in []-sets when RE_SYNTAX_BACKSLASH_ESCAPE_IN_LISTS)     [kos-extension]
 *     >> "\N"                   <[^[:lf:]]>                                                                                           [kos-extension]
 *     >> "[[:<foo>:]]"          REOP_UTF8_IS<foo>                                                                                     [some classes are kos extensions]
 *     >> "[^[:<foo>:]]"         REOP_UTF8_IS<foo>_NOT                                                                                 [kos-extension]
 *     >> "\s"                   <[[:space:]]>            (HINT: Also allowed in []-sets when RE_SYNTAX_BACKSLASH_ESCAPE_IN_LISTS)
 *     >> "\S"                   <[^[:space:]]>
 *     >> "\d"                   <[[:digit:]]>            (HINT: Also allowed in []-sets when RE_SYNTAX_BACKSLASH_ESCAPE_IN_LISTS)     [python-extension]
 *     >> "\D"                   <[^[:digit:]]>                                                                                        [python-extension]
 *     >> "\0123"                REOP_BYTE '\0123'        (octal-byte)                                                                 [kos-extension]
 *     >> "\xAB"                 REOP_BYTE '\xAB'         (hex-byte)                                                                   [kos-extension]
 *     >> "\uABCD"               REOP_EXACT "\uABCD"      (utf-8 encoded)                                                              [kos-extension]
 *     >> "\UABCDABCD"           REOP_EXACT "\UABCDABCD"  (utf-8 encoded)                                                              [kos-extension]
 *     >> "\u{1234 5689}"        REOP_EXACT "\u1234\u5689" (utf-8 encoded)                                                             [unicode-extension] (TODO)
 *     >> "[\u{1234 5689}]"      <[\u1234\u5689]>         (utf-8 encoded)                                                              [unicode-extension]
 *
 * [1]: <OP> is one of "=" (or "=="), "!=", "<", "<=", ">", ">="
 *
 * Location assertion (note: it is a syntax error to use these before repetition expressions):
 *     >> "^"            REOP_AT_SOL
 *     >> "$"            REOP_AT_EOL
 *     >> "\`"           REOP_AT_SOI
 *     >> "\'"           REOP_AT_EOI
 *     >> "\b"           REOP_AT_WOB
 *     >> "\B"           REOP_AT_WOB_NOT
 *     >> "\<"           REOP_AT_SOW
 *     >> "\>"           REOP_AT_EOW
 *     >> "\_<"          REOP_AT_SOS
 *     >> "\_>"          REOP_AT_EOS
 *     >> "\A"           REOP_AT_SOI  [python-extension]
 *     >> "\Z"           REOP_AT_EOI  [python-extension]
 *
 * Expressions:
 *     >> "(X)"          REOP_GROUP_START {GID}
 *     >>                <X>
 *     >>                REOP_GROUP_END   {GID}  // Replaced by `REOP_GROUP_END_Jn' if followed by a repeat-suffix
 *
 *     >> "X|Y"          REOP_JMP_ONFAIL  1f
 *     >>                <X>
 *     >>                REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 1f'
 *     >>                REOP_JMP         2f
 *     >>            1:  // HINT: Another `REOP_JMP_ONFAIL' to <Z> would go here if it existed
 *     >>                <Y>
 *     >>            2:
 *
 *     >> "X|Y|Z"        REOP_JMP_ONFAIL 1f
 *     >>                <X>
 *     >>                REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 1f'
 *     >>                REOP_JMP        3f
 *     >>            1:  REOP_JMP_ONFAIL 2f
 *     >>                <Y>
 *     >>                REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 2f'
 *     >>                REOP_JMP        3f
 *     >>            2:  <Z>
 *     >>            3:
 *
 *     >> "X?"           REOP_JMP_ONFAIL 1f
 *     >>                <X>
 *     >>                REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 1f'
 *     >>            1:
 *
 *     >> "X*"           REOP_JMP_ONFAIL 2f
 *     >>            1:  <X>     // Last instruction is `REOP_*_Jn(N)'-transformed to jump to `2f'
 *     >>                REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 2f'
 *     >>                REOP_JMP_AND_RETURN_ONFAIL 1b
 *     >>            2:
 *
 *     >> "X+"           REOP_JMP_ONFAIL_DUMMY_AT 2f
 *     >>            1:  <X>     // Last instruction is `REOP_*_Jn(N)'-transformed to jump to `2f'
 *     >>                REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 2f'
 *     >>                REOP_JMP_AND_RETURN_ONFAIL 1b
 *     >>            2:
 *
 *     >> "X{0}"         REOP_NOP   // Or just no instructions at all (but note that group start/end opcodes are retained!)
 *
 *     >> "X{1}"         <X>
 *
 *     >> "X{0,1}"       <X?>
 *
 *     >> "X{0,}"        <X*>
 *
 *     >> "X{1,}"        <X+>
 *
 *     >> "X{n}"         REOP_SETVAR  {VAR = (n - 1)}
 *     >>            1:  <X>
 *     >>                REOP_DEC_JMP {VAR}, 1b
 *
 *     >> "X{n,}"        REOP_SETVAR  {VAR = (n - 1)}
 *     >>            1:  REOP_JMP_ONFAIL_DUMMY_AT 3f
 *     >>            2:  <X>     // Last instruction is `REOP_*_Jn(N)'-transformed to jump to `3f'
 *     >>                REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 2f'
 *     >>                REOP_DEC_JMP {VAR}, 1b
 *     >>                REOP_JMP_AND_RETURN_ONFAIL 2b
 *     >>            3:
 *
 *     >> "X{0,m}"       REOP_SETVAR  {VAR = (m - 1)}
 *     >>                REOP_JMP_ONFAIL 2f
 *     >>            1:  <X>     // Last instruction is `REOP_*_Jn(N)'-transformed to jump to `2f'
 *     >>                REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 2f'
 *     >>                REOP_DEC_JMP_AND_RETURN_ONFAIL {VAR}, 1b
 *     >>            2:
 *
 *     >> "X{1,m}"       REOP_SETVAR  {VAR = (m - 1)}
 *     >>                REOP_JMP_ONFAIL_DUMMY_AT 2f
 *     >>            1:  <X>     // Last instruction is `REOP_*_Jn(N)'-transformed to jump to `2f'
 *     >>                REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 2f'
 *     >>                REOP_DEC_JMP_AND_RETURN_ONFAIL {VAR}, 1b
 *     >>            2:
 *
 *     >> "X{n,m}"       REOP_SETVAR  {VAR1 = n - 1}
 *     >>                REOP_SETVAR  {VAR2 = (m - n)}
 *     >>            1:  REOP_JMP_ONFAIL_DUMMY_AT 3f
 *     >>            2:  <X>     // Last instruction is `REOP_*_Jn(N)'-transformed to jump to `3f'
 *     >>                REOP_MAYBE_POP_ONFAIL   // Replaced with `REOP_POP_ONFAIL_AT 3f'
 *     >>                REOP_DEC_JMP {VAR1}, 1b
 *     >>                REOP_DEC_JMP_AND_RETURN_ONFAIL {VAR2}, 2b
 *     >>            3:
 *
 * When <X> is small enough:
 *     >> "X+"           <XX*>
 *     >> "X{n,}"        <XX{n-1,}>      // For "n >= 2", and size of "X" multiplied by "n"
 *     >> "X{1,m}"       <XX{0,m-1}>
 *     >> "X{n,m}"       <XX{n-1,m-1}>   // For "n >= 2", and size of "X" multiplied by "n"
 *
 * HINT: Using the above  compilation patterns, inserting  code in front  of
 *       already-compiled code can simply be done whilst ignoring the chance
 *       of  relocations. This is because jumps are relative, and will never
 *       jump out of- or into some block "<X>".
 *       As such, in  order to  compile (e.g.) "X{n,m}",  simply compile  "X",
 *       then memmoveup(3) its bytecode to insert the 2 `REOP_SETVAR' opcodes,
 *       with the guaranty that no jump offsets ever need to be adjusted.
 *
 * NOTES:
 * - "on-failure stack" elements only consist of "{ RESUME_PC, INPUT_POINTER }"
 * - Whenever a mismatch happens, the top-most element of the  "on-failure stack"
 *   is popped, which in turn contains the address of the next REOP_* instruction
 *   with which to continue, as well as the input pointer that should be restored
 * - `REOP_*_Jn(N)'-transformation works on the bytecode of an expression <X>, by
 *   replacing the last opcode:
 *    - REOP_GROUP_MATCH -> REOP_GROUP_MATCH_Jn
 *    - REOP_GROUP_END -> REOP_GROUP_END_Jn
 *   This opcode replacement is not performed when <X> cannot match epsilon.
 *   -> This transformation has to be done to prevent infinite loops in "()+",
 *      which would otherwise be encoded as:
 *      >> 1:  REOP_GROUP_START {GID}
 *      >>     REOP_GROUP_END   {GID}
 *      >>     REOP_JMP_AND_RETURN_ONFAIL 1b
 *      >>     REOP_MATCHED
 *      Since the body can never fail, `REOP_JMP_AND_RETURN_ONFAIL' will  just
 *      keep on  jumping back  to the  start of  the expression  indefinitely.
 *      However, by performing `REOP_*_Jn(N)'-transformation, the new code is:
 *      >> 1:  REOP_GROUP_START  {GID}
 *      >>     REOP_GROUP_END_J3 {GID}
 *      >>     REOP_JMP_AND_RETURN_ONFAIL 1b
 *      >>     REOP_MATCHED
 *      Which behaves differently. When executed, `regexec(3)' will notice  that
 *      the group-expression matched epsilon, so  rather than continue with  the
 *      `REOP_JMP_AND_RETURN_ONFAIL' instruction, it  will skip  3 bytes,  which
 *      just to happens to land us at the `REOP_MATCHED' opcode, thus preventing
 *      any sort of looping.
 *   -> This  also works in  something like "(|foo|bar)+".  Here, the first time
 *      around, the regex will push an  on-fail address for "foo" when  matching
 *      epsilon before proceeding to skip over the "+" suffix. With the  initial
 *      match  (of an  empty string) set,  the previously pushed  on-fail is now
 *      run, and the other branches are allowed to (try) to match more than just
 *      an empty word.
 *
 *
 * TODO: "(?<=X)"   -- Current input position must be preceded by "X"
 * TODO: "(?<!X)"   -- Current input position must not be preceded by "X"
 * TODO: "(?=X)"    -- Current input position must be succeeded by "X"
 * TODO: "(?!X)"    -- Current input position must not be succeeded by "X"
 * TODO: Support for other (?)-extensions
 */


/* Regex charset opcodes */
enum {
/*[[[deemon
print("#define case_RECS_BITSET_MIN_to_MAX_UTF8        \\");
for (local segment: [:0x63+1].segments(4)) {
	local isLast = segment.last == 0x63;
	print("\t", ": ".join(for (local x: segment) f"case 0x{x.hex()[2:].zfill(2)}")),;
	if (!isLast)
		print(": \\"),;
	print;
}
print("#define case_RECS_BITSET_MIN_to_MAX_BYTE        \\");
print("\tcase_RECS_BITSET_MIN_to_MAX_UTF8:           \\");
for (local segment: [0x64:0xe3+1].segments(4)) {
	local isLast = segment.last == 0xe3;
	print("\t", ": ".join(for (local x: segment) f"case 0x{x.hex()[2:].zfill(2)}")),;
	if (!isLast)
		print(": \\"),;
	print;
}
]]]*/
#define case_RECS_BITSET_MIN_to_MAX_UTF8        \
	case 0x00: case 0x01: case 0x02: case 0x03: \
	case 0x04: case 0x05: case 0x06: case 0x07: \
	case 0x08: case 0x09: case 0x0a: case 0x0b: \
	case 0x0c: case 0x0d: case 0x0e: case 0x0f: \
	case 0x10: case 0x11: case 0x12: case 0x13: \
	case 0x14: case 0x15: case 0x16: case 0x17: \
	case 0x18: case 0x19: case 0x1a: case 0x1b: \
	case 0x1c: case 0x1d: case 0x1e: case 0x1f: \
	case 0x20: case 0x21: case 0x22: case 0x23: \
	case 0x24: case 0x25: case 0x26: case 0x27: \
	case 0x28: case 0x29: case 0x2a: case 0x2b: \
	case 0x2c: case 0x2d: case 0x2e: case 0x2f: \
	case 0x30: case 0x31: case 0x32: case 0x33: \
	case 0x34: case 0x35: case 0x36: case 0x37: \
	case 0x38: case 0x39: case 0x3a: case 0x3b: \
	case 0x3c: case 0x3d: case 0x3e: case 0x3f: \
	case 0x40: case 0x41: case 0x42: case 0x43: \
	case 0x44: case 0x45: case 0x46: case 0x47: \
	case 0x48: case 0x49: case 0x4a: case 0x4b: \
	case 0x4c: case 0x4d: case 0x4e: case 0x4f: \
	case 0x50: case 0x51: case 0x52: case 0x53: \
	case 0x54: case 0x55: case 0x56: case 0x57: \
	case 0x58: case 0x59: case 0x5a: case 0x5b: \
	case 0x5c: case 0x5d: case 0x5e: case 0x5f: \
	case 0x60: case 0x61: case 0x62: case 0x63
#define case_RECS_BITSET_MIN_to_MAX_BYTE        \
	case_RECS_BITSET_MIN_to_MAX_UTF8:           \
	case 0x64: case 0x65: case 0x66: case 0x67: \
	case 0x68: case 0x69: case 0x6a: case 0x6b: \
	case 0x6c: case 0x6d: case 0x6e: case 0x6f: \
	case 0x70: case 0x71: case 0x72: case 0x73: \
	case 0x74: case 0x75: case 0x76: case 0x77: \
	case 0x78: case 0x79: case 0x7a: case 0x7b: \
	case 0x7c: case 0x7d: case 0x7e: case 0x7f: \
	case 0x80: case 0x81: case 0x82: case 0x83: \
	case 0x84: case 0x85: case 0x86: case 0x87: \
	case 0x88: case 0x89: case 0x8a: case 0x8b: \
	case 0x8c: case 0x8d: case 0x8e: case 0x8f: \
	case 0x90: case 0x91: case 0x92: case 0x93: \
	case 0x94: case 0x95: case 0x96: case 0x97: \
	case 0x98: case 0x99: case 0x9a: case 0x9b: \
	case 0x9c: case 0x9d: case 0x9e: case 0x9f: \
	case 0xa0: case 0xa1: case 0xa2: case 0xa3: \
	case 0xa4: case 0xa5: case 0xa6: case 0xa7: \
	case 0xa8: case 0xa9: case 0xaa: case 0xab: \
	case 0xac: case 0xad: case 0xae: case 0xaf: \
	case 0xb0: case 0xb1: case 0xb2: case 0xb3: \
	case 0xb4: case 0xb5: case 0xb6: case 0xb7: \
	case 0xb8: case 0xb9: case 0xba: case 0xbb: \
	case 0xbc: case 0xbd: case 0xbe: case 0xbf: \
	case 0xc0: case 0xc1: case 0xc2: case 0xc3: \
	case 0xc4: case 0xc5: case 0xc6: case 0xc7: \
	case 0xc8: case 0xc9: case 0xca: case 0xcb: \
	case 0xcc: case 0xcd: case 0xce: case 0xcf: \
	case 0xd0: case 0xd1: case 0xd2: case 0xd3: \
	case 0xd4: case 0xd5: case 0xd6: case 0xd7: \
	case 0xd8: case 0xd9: case 0xda: case 0xdb: \
	case 0xdc: case 0xdd: case 0xde: case 0xdf: \
	case 0xe0: case 0xe1: case 0xe2: case 0xe3
/*[[[end]]]*/
	RECS_BITSET_MIN,        /* [+RECS_BITSET_GETBYTES(.)] First bitset opcode (s.a. `RECS_BITSET_*')
	                         * >> bool is_char_in_set(byte_t const *layout_ptr, uint8_t ch) {
	                         * >>     uint8_t layout      = *layout_ptr++; // Layout is the RECS_BITSET_* opcode
	                         * >>     uint8_t minch       = RECS_BITSET_GETBASE(layout);
	                         * >>     uint8_t bitset_size = RECS_BITSET_GETBYTES(layout);
	                         * >>     unsigned int bitset_bits = bitset_size * 8;
	                         * >>     if (OVERFLOW_USUB(ch, minch, &ch))
	                         * >>         return false;
	                         * >>     if (ch >= bitset_bits)
	                         * >>         return false;
	                         * >>     return (layout_ptr[ch / 8] & (1 << (ch % 8))) != 0;
	                         * >> }
	                         * NOTE: In utf-8 mode, only ASCII characters may be encoded via bitsets. */
	/* In utf-8 mode, the lowest-possible bitset opcode is 0x63, since in this context, bitsets are only
	 * allowed to define  ASCII characters  (so the last-valid  opcode is  `RECS_BITSET_BUILD(0x60, 4)') */
	RECS_BITSET_MAX_UTF8 = 0x63, /* [+RECS_BITSET_GETBYTES(.)] Last utf8-bitset opcode (encodes bitset for range 60h-7Fh) */
#define case_RECS_ISX_MIN_to_MAX                                                     \
	case RECS_ISCNTRL:   case RECS_ISSPACE:   case RECS_ISUPPER:  case RECS_ISLOWER: \
	case RECS_ISALPHA:   case RECS_ISDIGIT:   case RECS_ISXDIGIT: case RECS_ISALNUM: \
	case RECS_ISPUNCT:   case RECS_ISGRAPH:   case RECS_ISPRINT:  case RECS_ISBLANK: \
	case RECS_ISSYMSTRT: case RECS_ISSYMCONT: case RECS_ISTAB:    case RECS_ISWHITE: \
	case RECS_ISEMPTY:   case RECS_ISLF:      case RECS_ISHEX:    case RECS_ISTITLE: \
	case RECS_ISNUMERIC
#define RECS_ISX_MIN RECS_ISCNTRL
	RECS_ISCNTRL,           /* [+0] consume trait `unicode_iscntrl(ch)'   (ONLY VALID IN UTF-8 MODE) */
	RECS_ISSPACE,           /* [+0] consume trait `unicode_isspace(ch)'   (ONLY VALID IN UTF-8 MODE) */
	RECS_ISUPPER,           /* [+0] consume trait `unicode_isupper(ch)'   (ONLY VALID IN UTF-8 MODE) */
	RECS_ISLOWER,           /* [+0] consume trait `unicode_islower(ch)'   (ONLY VALID IN UTF-8 MODE) */
	RECS_ISALPHA,           /* [+0] consume trait `unicode_isalpha(ch)'   (ONLY VALID IN UTF-8 MODE) */
	RECS_ISDIGIT,           /* [+0] consume trait `unicode_isdigit(ch)'   (ONLY VALID IN UTF-8 MODE) */
	RECS_ISXDIGIT,          /* [+0] consume trait `unicode_isxdigit(ch)'  (ONLY VALID IN UTF-8 MODE) */
	RECS_ISALNUM,           /* [+0] consume trait `unicode_isalnum(ch)'   (ONLY VALID IN UTF-8 MODE) */
	RECS_ISPUNCT,           /* [+0] consume trait `unicode_ispunct(ch)'   (ONLY VALID IN UTF-8 MODE) */
	RECS_ISGRAPH,           /* [+0] consume trait `unicode_isgraph(ch)'   (ONLY VALID IN UTF-8 MODE) */
	RECS_ISPRINT,           /* [+0] consume trait `unicode_isprint(ch)'   (ONLY VALID IN UTF-8 MODE) */
	RECS_ISBLANK,           /* [+0] consume trait `unicode_isblank(ch)'   (ONLY VALID IN UTF-8 MODE) */
	RECS_ISSYMSTRT,         /* [+0] consume trait `unicode_issymstrt(ch)' (ONLY VALID IN UTF-8 MODE) */
	RECS_ISSYMCONT,         /* [+0] consume trait `unicode_issymcont(ch)' (ONLY VALID IN UTF-8 MODE) */
	RECS_ISTAB,             /* [+0] consume trait `unicode_istab(ch)'     (ONLY VALID IN UTF-8 MODE) */
	RECS_ISWHITE,           /* [+0] consume trait `unicode_iswhite(ch)'   (ONLY VALID IN UTF-8 MODE) */
	RECS_ISEMPTY,           /* [+0] consume trait `unicode_isempty(ch)'   (ONLY VALID IN UTF-8 MODE) */
	RECS_ISLF,              /* [+0] consume trait `unicode_islf(ch)'      (ONLY VALID IN UTF-8 MODE) */
	RECS_ISHEX,             /* [+0] consume trait `unicode_ishex(ch)'     (ONLY VALID IN UTF-8 MODE) */
	RECS_ISTITLE,           /* [+0] consume trait `unicode_istitle(ch)'   (ONLY VALID IN UTF-8 MODE) */
	RECS_ISNUMERIC,         /* [+0] consume trait `unicode_isnumeric(ch)' (ONLY VALID IN UTF-8 MODE) */
#define RECS_ISX_MAX RECS_ISNUMERIC

	RECS_BITSET_MAX_BYTE = 0xe3, /* [+RECS_BITSET_GETBYTES(.)] Last byte-bitset opcode (encodes bitset for range E0h-FFh) */
#define RECS_BITSET_GETBYTES(cs_opcode)    (((cs_opcode)&0x1f) + 1)
#define RECS_BITSET_GETBASE(cs_opcode)     ((cs_opcode)&0xe0)
#define RECS_BITSET_BUILD(base, num_bytes) ((base) | ((num_bytes)-1))
#define RECS_BITSET_BASEFOR(minbyte)       ((minbyte)&0xe0)

	RECS_DONE,              /* End of charset sequence */
	RECS_CHAR,              /* [+1] Followed by 1 byte (or utf8-character) that is apart of the bitset */
	RECS_CHAR2,             /* [+2] Followed by 2 bytes (or utf8-characters) that are apart of the bitset */
	RECS_RANGE,             /* [+2] Followed by 2 bytes (or utf8-characters) that form a `[lo,hi]' inclusive range of bytes apart of the bitset */
	RECS_RANGE_ICASE,       /* [+2] Followed by 2 utf8-characters that form a `[lo,hi]' inclusive range of bytes apart of the bitset
	                         *      the 2 utf8-characters must both be lower-case (ONLY VALID IN UTF-8 MODE) */
	RECS_CONTAINS,          /* [+1+n] Followed by a COUNT-byte, followed by a `COUNT'-character long byte/utf-8 string.
	                         * Whether or not COUNT are bytes/utf-8 depends on the `REOP_CS_*' starting opcode. Matches
	                         * a character contained in said string. NOTE: COUNT must be >= 3 */
};

/* Regex opcodes (always encoded as a single byte) */
enum {

	/* Opcodes for matching (and thus: consuming) input */
	REOP_EXACT,                /* [+1+n] Followed by 1 byte N = *PC++, followed by N more bytes that must be matched exactly
	                            * NOTE: N must be >= 2 */
	REOP_EXACT_ASCII_ICASE,    /* [+1+n] Like 'REOP_EXACT', but strings are both ascii, and casing should be ignored (used instead of
	                            * `REOP_EXACT_UTF8_ICASE' when the pattern string is ascii-only, or when `RE_SYNTAX_NO_UTF8' was set)
	                            * NOTE: N must be >= 2 */
	REOP_EXACT_UTF8_ICASE,     /* [+1+n] Followed  by  a  COUNT-byte, followed  by  a `COUNT'-character
	                            * long utf-8 string (matches utf-8 character contained in said string).
	                            * NOTE: COUNT must be >= 1 */
#define REOP_MAKEANY(want_nul, want_lf, want_utf8) \
	((REOP_ANY) + ((want_nul) ? 0 : 4) + ((want_lf) ? 0 : 2) + ((want_utf8) ? 1 : 0))
#define case_REOP_ANY_MIN_to_MAX                                                 \
	case REOP_ANY:              case REOP_ANY_UTF8:   case REOP_ANY_NOTLF:       \
	case REOP_ANY_NOTLF_UTF8:   case REOP_ANY_NOTNUL: case REOP_ANY_NOTNUL_UTF8: \
	case REOP_ANY_NOTNUL_NOTLF: case REOP_ANY_NOTNUL_NOTLF_UTF8
#define REOP_ANY_MIN REOP_ANY
	REOP_ANY,                  /* [+0] Match any byte */
	REOP_ANY_UTF8,             /* [+0] Match any character */
	REOP_ANY_NOTLF,            /* [+0] Match any character (except ASCII line-feeds) */
	REOP_ANY_NOTLF_UTF8,       /* [+0] Match any utf-8 character (except unicode line-feeds) */
	REOP_ANY_NOTNUL,           /* [+0] Match any byte (except '\0') */
	REOP_ANY_NOTNUL_UTF8,      /* [+0] Match any utf-8 character (except '\0') */
	REOP_ANY_NOTNUL_NOTLF,     /* [+0] Match any character (except '\0' or ASCII line-feeds) */
	REOP_ANY_NOTNUL_NOTLF_UTF8, /* [+0] Match any character (except '\0' or unicode line-feeds) */
#define REOP_ANY_MAX REOP_ANY_NOTNUL_NOTLF_UTF8
	REOP_BYTE,                 /* [+1] Followed by 1 byte that must be matched exactly */
	REOP_NBYTE,                /* [+1] Followed by 1 byte that must not be matched exactly */
	REOP_BYTE2,                /* [+2] Followed by 2 bytes, one of which must be matched exactly (for "[ab]" or "a" -> "[aA]" in ICASE-mode) (the 2 bytes must be sorted ascendingly) */
	REOP_NBYTE2,               /* [+2] Followed by 2 bytes, neither of which may be matched (the 2 bytes must be sorted ascendingly) */
	REOP_RANGE,                /* [+2] Followed by 2 bytes, with input having to match `ch >= pc[0] && ch <= pc[1]' */
	REOP_NRANGE,               /* [+2] Followed by 2 bytes, with input having to match `ch < pc[0] || ch > pc[1]' */
	/* TODO: Re-design `REOP_CONTAINS_UTF8' / `REOP_NCONTAINS_UTF8'  to allow for binary  search!
	 *       For this, instead of encoding a COUNT-byte, we need to encode the actual # of bytes,
	 *       with the assumption that the # of bytes ends at the perfect end of a utf-8 char. */
	REOP_CONTAINS_UTF8,        /* [+1+n] Followed by a COUNT-byte, followed by a `COUNT'-character long utf-8 string
	                            * - Matches utf-8 character contained in said string
	                            * - The utf-8 character in the follow-up string must be sorted ascendingly by their ordinal values
	                            * NOTE: COUNT must be >= 2 */
	REOP_NCONTAINS_UTF8,       /* [+1+n] Followed by a COUNT-byte, followed by a `COUNT'-character long utf-8 string
	                            * - Matches utf-8 character NOT contained in said string
	                            * - The utf-8 character in the follow-up string must be sorted ascendingly by their ordinal values
	                            * NOTE: COUNT must be >= 1 */
	REOP_CS_UTF8,              /* [+*] Followed by a `RECS_*' sequence which the next utf-8 character must match */
	REOP_CS_BYTE,              /* [+*] Followed by a `RECS_*' sequence which the next byte must match */
	REOP_NCS_UTF8,             /* [+*] Followed by a `RECS_*' sequence which the next utf-8 character must not match */
	REOP_GROUP_MATCH,          /* [+1] Re-match the contents of the (N = *PC++)'th already-matched group; If group start/end aren't, triggers a match-failure. */
#define case_REOP_GROUP_MATCH_JMIN_to_JMAX                                         \
	case REOP_GROUP_MATCH_J3: case REOP_GROUP_MATCH_J4:  case REOP_GROUP_MATCH_J5: \
	case REOP_GROUP_MATCH_J6: case REOP_GROUP_MATCH_J7:  case REOP_GROUP_MATCH_J8: \
	case REOP_GROUP_MATCH_J9: case REOP_GROUP_MATCH_J10: case REOP_GROUP_MATCH_J11
#define REOP_GROUP_MATCH_JMIN  REOP_GROUP_MATCH_J3
	REOP_GROUP_MATCH_J3,       /* [+1] Same as `REOP_GROUP_MATCH', but skip the next 3 instruction bytes if epsilon was matched (iow: `regmatch_t[N].rm_so == regmatch_t[N].rm_eo') */
	REOP_GROUP_MATCH_J4,       /* [+1] Same as `REOP_GROUP_MATCH', but skip the next 4 instruction bytes if epsilon was matched (iow: `regmatch_t[N].rm_so == regmatch_t[N].rm_eo') */
	REOP_GROUP_MATCH_J5,       /* [+1] Same as `REOP_GROUP_MATCH', but skip the next 5 instruction bytes if epsilon was matched (iow: `regmatch_t[N].rm_so == regmatch_t[N].rm_eo') */
	REOP_GROUP_MATCH_J6,       /* [+1] Same as `REOP_GROUP_MATCH', but skip the next 6 instruction bytes if epsilon was matched (iow: `regmatch_t[N].rm_so == regmatch_t[N].rm_eo') */
	REOP_GROUP_MATCH_J7,       /* [+1] Same as `REOP_GROUP_MATCH', but skip the next 7 instruction bytes if epsilon was matched (iow: `regmatch_t[N].rm_so == regmatch_t[N].rm_eo') */
	REOP_GROUP_MATCH_J8,       /* [+1] Same as `REOP_GROUP_MATCH', but skip the next 8 instruction bytes if epsilon was matched (iow: `regmatch_t[N].rm_so == regmatch_t[N].rm_eo') */
	REOP_GROUP_MATCH_J9,       /* [+1] Same as `REOP_GROUP_MATCH', but skip the next 8 instruction bytes if epsilon was matched (iow: `regmatch_t[N].rm_so == regmatch_t[N].rm_eo') */
	REOP_GROUP_MATCH_J10,      /* [+1] Same as `REOP_GROUP_MATCH', but skip the next 8 instruction bytes if epsilon was matched (iow: `regmatch_t[N].rm_so == regmatch_t[N].rm_eo') */
	REOP_GROUP_MATCH_J11,      /* [+1] Same as `REOP_GROUP_MATCH', but skip the next 8 instruction bytes if epsilon was matched (iow: `regmatch_t[N].rm_so == regmatch_t[N].rm_eo') */
#define REOP_GROUP_MATCH_JMAX  REOP_GROUP_MATCH_J11
#define REOP_GROUP_MATCH_Jn(n) (REOP_GROUP_MATCH_J3 + (n) - 3)
#define REOP_GROUP_MATCH_Joff(opcode) (3 + (opcode) - REOP_GROUP_MATCH_J3)

	/* Opcodes for asserting the current position in input (these don't consume anything) */
#define case_REOP_AT_MIN_to_MAX                                                                 \
	case REOP_AT_SOI:     case REOP_AT_EOI:          case REOP_AT_SOL:  case REOP_AT_SOL_UTF8:  \
	case REOP_AT_EOL:     case REOP_AT_EOL_UTF8:     case REOP_AT_SOXL: case REOP_AT_SOXL_UTF8: \
	case REOP_AT_EOXL:    case REOP_AT_EOXL_UTF8:    case REOP_AT_WOB:  case REOP_AT_WOB_UTF8:  \
	case REOP_AT_WOB_NOT: case REOP_AT_WOB_UTF8_NOT: case REOP_AT_SOW:  case REOP_AT_SOW_UTF8:  \
	case REOP_AT_EOW:     case REOP_AT_EOW_UTF8:     case REOP_AT_SOS_UTF8
#define REOP_AT_MIN REOP_AT_SOI
	REOP_AT_SOI,          /* [+0] Start-of-input */
	REOP_AT_EOI,          /* [+0] End-of-input */
#define REOP_AT_SOLEOL_CHECK(opcode) ((opcode) >= REOP_AT_SOL && (opcode) <= REOP_AT_EOXL_UTF8)
#define REOP_AT_SOLEOL_MAKEX(opcode) ((opcode) + (REOP_AT_SOXL - REOP_AT_SOL))
	REOP_AT_SOL,          /* [+0] Start-of-line (following a line-feed, or `REOP_AT_SOI') */
	REOP_AT_SOL_UTF8,     /* [+0] Start-of-line (following a line-feed, or `REOP_AT_SOI') */
	REOP_AT_EOL,          /* [+0] End-of-line (preceding a line-feed, or `REOP_AT_EOI') */
	REOP_AT_EOL_UTF8,     /* [+0] End-of-line (preceding a line-feed, or `REOP_AT_EOI') */
	REOP_AT_SOXL,         /* [+0] Start-of-line (following a line-feed, or `REOP_AT_SOI' unless `RE_EXEC_NOTBOL' was set) */
	REOP_AT_SOXL_UTF8,    /* [+0] Start-of-line (following a line-feed, or `REOP_AT_SOI' unless `RE_EXEC_NOTBOL' was set) */
	REOP_AT_EOXL,         /* [+0] End-of-line (preceding a line-feed, or `REOP_AT_EOI' unless `RE_EXEC_NOTEOL' was set) */
	REOP_AT_EOXL_UTF8,    /* [+0] End-of-line (preceding a line-feed, or `REOP_AT_EOI' unless `RE_EXEC_NOTEOL' was set) */
	REOP_AT_WOB,          /* [+0] WOrdBoundary (preceding and next character have non-equal `issymcont(ch)'; OOB counts as `issymcont == false') */
	REOP_AT_WOB_UTF8,     /* [+0] WOrdBoundary (preceding and next character have non-equal `unicode_issymcont(ch)'; OOB counts as `unicode_issymcont == false') */
	REOP_AT_WOB_NOT,      /* [+0] NOT WOrdBoundary (preceding and next character have equal `issymcont(ch)'; OOB counts as `unicode_issymcont == false') */
	REOP_AT_WOB_UTF8_NOT, /* [+0] NOT WOrdBoundary (preceding and next character have equal `unicode_issymcont(ch)'; OOB counts as `issymcont == false') */
	REOP_AT_SOW,          /* [+0] StartOfWord (preceding and next character are `!issymcont(lhs) && issymcont(rhs)'; OOB counts as `issymcont == false') */
	REOP_AT_SOW_UTF8,     /* [+0] StartOfWord (preceding and next character are `!unicode_issymcont(lhs) && unicode_issymcont(rhs)'; OOB counts as `unicode_issymcont == false') */
	REOP_AT_EOW,          /* [+0] EndOfWord (preceding and next character are `issymcont(lhs) && !issymcont(rhs)'; OOB counts as `issymcont == false') */
	REOP_AT_EOW_UTF8,     /* [+0] EndOfWord (preceding and next character are `unicode_issymcont(lhs) && !unicode_issymcont(rhs)'; OOB counts as `unicode_issymcont == false') */
#define REOP_AT_SOS REOP_AT_SOW
	REOP_AT_SOS_UTF8,     /* [+0] StartOfSymbol (preceding and next character are `!unicode_issymcont(lhs) && unicode_issymstrt(rhs)'; OOB counts as `issymcont[/strt] == false') */
#define REOP_AT_EOS      REOP_AT_EOW
#define REOP_AT_EOS_UTF8 REOP_AT_EOW_UTF8
#define REOP_AT_MAX      REOP_AT_SOS_UTF8

	/* Opcodes for expression logic and processing. */
	REOP_GROUP_START,           /* [+1] Mark the start of the (N = *PC++)'th group; open "("
	                             * - The current input pointer is written to `regmatch_t[N].rm_so'
	                             * - Writes a backup of the old `regmatch_t[N].rm_so' that is restored on-fail. */
	REOP_GROUP_END,             /* [+1] Mark the end of the (N = *PC++)'th group; closing ")"
	                             * - The current input pointer is written to `regmatch_t[N].rm_eo')
	                             * - Writes a backup of the old `regmatch_t[N].rm_eo' that is restored on-fail. */
#define REOP_GROUP_END_Jn(n)        (REOP_GROUP_END_J3 + (n) - 3)
#define REOP_GROUP_END_Joff(opcode) (3 + (opcode) - REOP_GROUP_END_J3)
#define case_REOP_GROUP_END_JMIN_to_JMAX                                     \
	case REOP_GROUP_END_J3: case REOP_GROUP_END_J4:  case REOP_GROUP_END_J5: \
	case REOP_GROUP_END_J6: case REOP_GROUP_END_J7:  case REOP_GROUP_END_J8: \
	case REOP_GROUP_END_J9: case REOP_GROUP_END_J10: case REOP_GROUP_END_J11
#define REOP_GROUP_END_JMIN         REOP_GROUP_END_J3
	REOP_GROUP_END_J3,          /* [+1] Same as `REOP_GROUP_END', but skip the next 3 instruction bytes if epsilon was matched (iow: `regmatch_t[N].rm_so == regmatch_t[N].rm_eo') */
	REOP_GROUP_END_J4,          /* [+1] Same as `REOP_GROUP_END', but skip the next 4 instruction bytes if epsilon was matched (iow: `regmatch_t[N].rm_so == regmatch_t[N].rm_eo') */
	REOP_GROUP_END_J5,          /* [+1] Same as `REOP_GROUP_END', but skip the next 5 instruction bytes if epsilon was matched (iow: `regmatch_t[N].rm_so == regmatch_t[N].rm_eo') */
	REOP_GROUP_END_J6,          /* [+1] Same as `REOP_GROUP_END', but skip the next 6 instruction bytes if epsilon was matched (iow: `regmatch_t[N].rm_so == regmatch_t[N].rm_eo') */
	REOP_GROUP_END_J7,          /* [+1] Same as `REOP_GROUP_END', but skip the next 7 instruction bytes if epsilon was matched (iow: `regmatch_t[N].rm_so == regmatch_t[N].rm_eo') */
	REOP_GROUP_END_J8,          /* [+1] Same as `REOP_GROUP_END', but skip the next 8 instruction bytes if epsilon was matched (iow: `regmatch_t[N].rm_so == regmatch_t[N].rm_eo') */
	REOP_GROUP_END_J9,          /* [+1] Same as `REOP_GROUP_END', but skip the next 8 instruction bytes if epsilon was matched (iow: `regmatch_t[N].rm_so == regmatch_t[N].rm_eo') */
	REOP_GROUP_END_J10,         /* [+1] Same as `REOP_GROUP_END', but skip the next 8 instruction bytes if epsilon was matched (iow: `regmatch_t[N].rm_so == regmatch_t[N].rm_eo') */
	REOP_GROUP_END_J11,         /* [+1] Same as `REOP_GROUP_END', but skip the next 8 instruction bytes if epsilon was matched (iow: `regmatch_t[N].rm_so == regmatch_t[N].rm_eo') */
#define REOP_GROUP_END_JMAX         REOP_GROUP_END_J11
	REOP_POP_ONFAIL,            /* [+0] Pop the top-most element from the on-fail stack (no-op if the stack is empty) */
	REOP_POP_ONFAIL_AT,         /* [+2] Pop on-fail stack items until one is found referencing the given 16-bit, signed, relative address.
	                             * Then, pop one more (i.e. the one at the referenced address). (if the referenced address doesn't  exist,
	                             * the on-fail stack is cleared) */
	REOP_JMP_ONFAIL,            /* [+2] push onto the "on-failure stack" a 16-bit, signed, relative addr */
	REOP_JMP_ONFAIL_DUMMY_AT,   /* [+2] Push a dummy on-fail stack item (that will be skipped during on-fail unwinding, but not by `REOP_POP_ONFAIL')
	                             *      Operand is a 16-bit, signed, relative addr used to identify the on-fail item (for `REOP_POP_ONFAIL_AT'). */
	REOP_JMP_ONFAIL_DUMMY,      /* [+0] Like `REOP_JMP_ONFAIL_DUMMY_AT', but the produced on-failure item can't be identified by `REOP_POP_ONFAIL_AT' */
	REOP_JMP,                   /* [+2] 16-bit, signed, relative jump (relative to instruction end) */
	REOP_JMP_AND_RETURN_ONFAIL, /* [+2] push onto the "on-failure stack" the address of the next instruction before doing `REOP_JMP' */
	REOP_DEC_JMP,               /* [+3] VAR = VARS[*PC++]; if VAR != 0, do `--VAR', followed by `REOP_JMP'; else, do nothing (and leave `VAR' unchanged) */
	REOP_DEC_JMP_AND_RETURN_ONFAIL, /* [+3] VAR = VARS[*PC++]; if VAR != 0, do `--VAR', followed by `REOP_JMP_AND_RETURN_ONFAIL'; else, do nothing (and leave `VAR' and the "on-failure stack" unchanged) */
	REOP_SETVAR,                /* [+2] VAR = VARS[*PC++]; VAR = *PC++; */
	REOP_NOP,                   /* [+0] No-op */
	REOP_MATCHED,               /* [+0] Text has been matched (end of instruction stream)
	                             * If  the "on-failure stack" is  non-empty (and the  current match isn't perfect),
	                             * the current match is saved as a candidate, and the "on-failure stack" is popped.
	                             * Extra candidates are compared against prior ones, and the "best" one is  finally
	                             * used  (note that a  candidate consists of `{ end_input_pointer, regmatch_t[] }')
	                             * Candidate A is better than B if `A.end_input_pointer > B.end_input_pointer' */
	REOP_MATCHED_PERFECT,       /* [+0] Same as `REOP_MATCHED', but act as though the match was perfect (even if it might not be; s.a. `RE_SYNTAX_NO_POSIX_BACKTRACKING') */
	/* ==== END OF ACTUAL RUNTIME OPCODES ==== */

	REOP_MAYBE_POP_ONFAIL,      /* [+2] Marker for the peephole optimizer (cannot appear at runtime, and treated as an illegal instruction)
	                             * - The 2 operand bytes are undefined (and used as placeholder for `REOP_POP_ONFAIL_AT')
	                             * - Encoding  as `REOP_POP_ONFAIL_AT' only happens if no  input can match both branches of
	                             *   the associated bi-branch expression (as started by either `REOP_JMP_ONFAIL_DUMMY[_AT]'
	                             *   or `REOP_JMP_ONFAIL')
	                             * - When this encoding cannot be used, this opcode is instead `REOP_NOP'd away. */
};



/* Regex syntax flags */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_BACKSLASH_ESCAPE_IN_LISTS) && !defined(RE_SYNTAX_BACKSLASH_ESCAPE_IN_LISTS)
#define RE_SYNTAX_BACKSLASH_ESCAPE_IN_LISTS 0x00000001 /* '\' can be used to escape characters in sets: '[a\[\]\-]' */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_BACKSLASH_ESCAPE_IN_LISTS && !RE_SYNTAX_BACKSLASH_ESCAPE_IN_LISTS */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_BK_PLUS_QM) && !defined(RE_SYNTAX_BK_PLUS_QM)
#define RE_SYNTAX_BK_PLUS_QM                0x00000002 /* If clear: '+' and '?' are operators and '\+' and '\?' are literals; if set: the opposite is the case. */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_BK_PLUS_QM && !RE_SYNTAX_BK_PLUS_QM */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_CHAR_CLASSES) && !defined(RE_SYNTAX_CHAR_CLASSES)
#define RE_SYNTAX_CHAR_CLASSES              0x00000004 /* Support for char-classes (e.g. `[[:alpha:]]') */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_CHAR_CLASSES && !RE_SYNTAX_CHAR_CLASSES */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_CONTEXT_INDEP_ANCHORS) && !defined(RE_SYNTAX_CONTEXT_INDEP_ANCHORS)
#define RE_SYNTAX_CONTEXT_INDEP_ANCHORS     0x00000008 /* '^' and '$' are always anchors (as opposed to only at the start/end or after/before a '(' and ')') */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_CONTEXT_INDEP_ANCHORS && !RE_SYNTAX_CONTEXT_INDEP_ANCHORS */
#ifndef RE_SYNTAX_CONTEXT_INDEP_OPS
#define RE_SYNTAX_CONTEXT_INDEP_OPS         0x00000010 /* Ignored... */
#endif /* !RE_SYNTAX_CONTEXT_INDEP_OPS */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_CONTEXT_INVALID_OPS) && !defined(RE_SYNTAX_CONTEXT_INVALID_OPS)
#define RE_SYNTAX_CONTEXT_INVALID_OPS       0x00000020 /* '*', '+', '{' and '?' appearing at the start or after '(' or '|' results in `RE_BADRPT'; If not set, they are treated as literals. */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_CONTEXT_INVALID_OPS && !RE_SYNTAX_CONTEXT_INVALID_OPS */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_DOT_NEWLINE) && !defined(RE_SYNTAX_DOT_NEWLINE)
#define RE_SYNTAX_DOT_NEWLINE               0x00000040 /* '.' matches line-feeds (if not set, then it doesn't) */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_DOT_NEWLINE && !RE_SYNTAX_DOT_NEWLINE */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_DOT_NOT_NULL) && !defined(RE_SYNTAX_DOT_NOT_NULL)
#define RE_SYNTAX_DOT_NOT_NULL              0x00000080 /* '.' doesn't match '\0' (if not set, then it does) */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_DOT_NOT_NULL && !RE_SYNTAX_DOT_NOT_NULL */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_HAT_LISTS_NOT_NEWLINE) && !defined(RE_SYNTAX_HAT_LISTS_NOT_NEWLINE)
#define RE_SYNTAX_HAT_LISTS_NOT_NEWLINE     0x00000100 /* '[^abc]' will never match line-feeds (as though line-feeds were part of the set of characters never matched). If not set, [^]-sets will match them (unless explicitly added to the set of unmatched characters) */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_HAT_LISTS_NOT_NEWLINE && !RE_SYNTAX_HAT_LISTS_NOT_NEWLINE */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_INTERVALS) && !defined(RE_SYNTAX_INTERVALS)
#define RE_SYNTAX_INTERVALS                 0x00000200 /* Enable support for intervals: 'x{1,2}' (if not set, '{' and '}' are literals, though escaping is governed by `RE_SYNTAX_NO_BK_BRACES') */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_INTERVALS && !RE_SYNTAX_INTERVALS */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_LIMITED_OPS) && !defined(RE_SYNTAX_LIMITED_OPS)
#define RE_SYNTAX_LIMITED_OPS               0x00000400 /* If set, support for '+', '?' and '|' is disabled (if not set, support is enabled, though escaping is governed by `RE_SYNTAX_BK_PLUS_QM' and `RE_SYNTAX_NO_BK_VBAR') */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_LIMITED_OPS && !RE_SYNTAX_LIMITED_OPS */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_NEWLINE_ALT) && !defined(RE_SYNTAX_NEWLINE_ALT)
#define RE_SYNTAX_NEWLINE_ALT               0x00000800 /* '\n' (embedded ASCII 10h) is treated like as an alias for the '|'-operator (if not set, '\n' is a literal; but note the kos-exception "\" "n", which matches that 2-character sequence against arbitrary line-feeds) */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_NEWLINE_ALT && !RE_SYNTAX_NEWLINE_ALT */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_NO_BK_BRACES) && !defined(RE_SYNTAX_NO_BK_BRACES)
#define RE_SYNTAX_NO_BK_BRACES              0x00001000 /* If set, '{...}' are intervals, and '\{' and '\}' are literals; if clear, the opposite is the case (iow: '\{...\}' is an interval) */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_NO_BK_BRACES && !RE_SYNTAX_NO_BK_BRACES */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_NO_BK_PARENS) && !defined(RE_SYNTAX_NO_BK_PARENS)
#define RE_SYNTAX_NO_BK_PARENS              0x00002000 /* If set, '(...)' are groups, and '\(' and '\)' are literals; if clear, the opposite is the case (iow: '\(...\)' is a group) */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_NO_BK_PARENS && !RE_SYNTAX_NO_BK_PARENS */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_NO_BK_REFS) && !defined(RE_SYNTAX_NO_BK_REFS)
#define RE_SYNTAX_NO_BK_REFS                0x00004000 /* If set, '\<1-9>' matches the literal <1-9>; if clear, '\<1-9>' is a back-reference */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_NO_BK_REFS && !RE_SYNTAX_NO_BK_REFS */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_NO_BK_VBAR) && !defined(RE_SYNTAX_NO_BK_VBAR)
#define RE_SYNTAX_NO_BK_VBAR                0x00008000 /* If set, '|' is the alternation operation: '(a|b)' (and '\|' is a literal); if clear, the opposite is the case (iow: '(a\|b)' matches '[ab]') */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_NO_BK_VBAR && !RE_SYNTAX_NO_BK_VBAR */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_NO_EMPTY_RANGES) && !defined(RE_SYNTAX_NO_EMPTY_RANGES)
#define RE_SYNTAX_NO_EMPTY_RANGES           0x00010000 /* If set, a []-set like '[z-a]' results in `RE_ERANGE'; if clear, it is equal to '[]' (iow: bad ranges are simply ignored) */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_NO_EMPTY_RANGES && !RE_SYNTAX_NO_EMPTY_RANGES */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD) && !defined(RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD)
#define RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD 0x00020000 /* If set, unmatched ')' are treated as literals; if clear, unmatched an ')' results in `RE_ERPAREN' */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD && !RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_NO_POSIX_BACKTRACKING) && !defined(RE_SYNTAX_NO_POSIX_BACKTRACKING)
#define RE_SYNTAX_NO_POSIX_BACKTRACKING     0x00040000 /* If set, return the first match, rather than the perfect one (s.a. `REOP_MATCHED' and `REOP_MATCHED_PERFECT') */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_NO_POSIX_BACKTRACKING && !RE_SYNTAX_NO_POSIX_BACKTRACKING */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_NO_GNU_OPS) && !defined(RE_SYNTAX_NO_GNU_OPS)
#define RE_SYNTAX_NO_GNU_OPS                0x00080000 /* If set, disable support for '\<', '\>', '\b', '\B', '\w', '\W', '\s', '\S', '\`' and "\'" */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_NO_GNU_OPS && !RE_SYNTAX_NO_GNU_OPS */
#ifndef RE_SYNTAX_DEBUG
#define RE_SYNTAX_DEBUG                     0x00100000 /* Ignored... */
#endif /* !RE_SYNTAX_DEBUG */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_INVALID_INTERVAL_ORD) && !defined(RE_SYNTAX_INVALID_INTERVAL_ORD)
#define RE_SYNTAX_INVALID_INTERVAL_ORD      0x00200000 /* Invalid intervals like "a{b" are treated as literals (i.e. like "a\{b") */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_INVALID_INTERVAL_ORD && !RE_SYNTAX_INVALID_INTERVAL_ORD */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_ICASE) && !defined(RE_SYNTAX_ICASE)
#define RE_SYNTAX_ICASE                     0x00400000 /* Casing is ignored by literal-matches, and '[[:lower:]]', '[[:upper:]]', '[[:title:]]' are aliases for '[[:alpha:]]' */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_ICASE && !RE_SYNTAX_ICASE */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_CARET_ANCHORS_HERE) && !defined(RE_SYNTAX_CARET_ANCHORS_HERE)
#define RE_SYNTAX_CARET_ANCHORS_HERE        0x00800000 /* Alias for `RE_SYNTAX_CONTEXT_INDEP_ANCHORS', but only for '^', and used internally */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_CARET_ANCHORS_HERE && !RE_SYNTAX_CARET_ANCHORS_HERE */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_CONTEXT_INVALID_DUP) && !defined(RE_SYNTAX_CONTEXT_INVALID_DUP)
#define RE_SYNTAX_CONTEXT_INVALID_DUP       0x01000000 /* If set, '{' appearing at the start, or after '(', '|' or '}' results in `RE_BADRPT'; else, behavior is governed by `RE_SYNTAX_CONTEXT_INVALID_OPS' */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_CONTEXT_INVALID_DUP && !RE_SYNTAX_CONTEXT_INVALID_DUP */
#ifndef RE_SYNTAX_NO_SUB
#define RE_SYNTAX_NO_SUB                    0x02000000 /* Ignored... (used at a different point to implement `RE_NOSUB') */
#endif /* !RE_SYNTAX_NO_SUB */
/*      RE_SYNTAX_                          0x04000000  * ... */
/*      RE_SYNTAX_                          0x08000000  * ... */
/*      RE_SYNTAX_                          0x10000000  * ... */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_ANCHORS_IGNORE_EFLAGS) && !defined(RE_SYNTAX_ANCHORS_IGNORE_EFLAGS)
#define RE_SYNTAX_ANCHORS_IGNORE_EFLAGS     0x20000000 /* '^' and '$' operators will ignore `RE_EXEC_NOTBOL' and `RE_EXEC_NOTEOL' */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_ANCHORS_IGNORE_EFLAGS && !RE_SYNTAX_ANCHORS_IGNORE_EFLAGS */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_NO_UTF8) && !defined(RE_SYNTAX_NO_UTF8)
#define RE_SYNTAX_NO_UTF8                   0x40000000 /* If set, pattern is byte-based (rather than a utf-8 string; e.g. '[ä]' is like '[\xC3\xA4]'). Also disables support for '\uABCD', '\UABCDABCD' */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_NO_UTF8 && !RE_SYNTAX_NO_UTF8 */
#if !defined(LIBREGEX_CONSTANT__RE_SYNTAX_NO_KOS_OPS) && !defined(RE_SYNTAX_NO_KOS_OPS)
#define RE_SYNTAX_NO_KOS_OPS                0x80000000 /* If set, disable support for python- and kos-extensions: '\n', '\N', "[^:<foo>:]", '\d', '\D', '\0123', '\xAB', '\uABCD', '\UABCDABCD', '\A', '\Z' */
#endif /* !LIBREGEX_CONSTANT__RE_SYNTAX_NO_KOS_OPS && !RE_SYNTAX_NO_KOS_OPS */

/* Regex parser structure.
 * The behavior of `re_parser_yield(3R)' is affected by the following syntax flags:
 * - RE_SYNTAX_BK_PLUS_QM
 * - RE_SYNTAX_CONTEXT_INDEP_ANCHORS
 * - RE_SYNTAX_INTERVALS
 * - RE_SYNTAX_LIMITED_OPS
 * - RE_SYNTAX_NEWLINE_ALT
 * - RE_SYNTAX_NO_BK_BRACES
 * - RE_SYNTAX_NO_BK_PARENS
 * - RE_SYNTAX_NO_BK_REFS
 * - RE_SYNTAX_NO_BK_VBAR
 * - RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD
 * - RE_SYNTAX_NO_GNU_OPS
 * - RE_SYNTAX_INVALID_INTERVAL_ORD
 * - RE_SYNTAX_CARET_ANCHORS_HERE
 * - RE_SYNTAX_NO_UTF8
 * - RE_SYNTAX_NO_KOS_OPS */
struct re_parser {
	char const *rep_pos;    /* [1..1][>= rep_pat && <= rep_end] Pointer to next pattern-character that has yet to be compiled. */
	char const *rep_pat;    /* [1..1][const] Pointer to the start of the pattern being compiled. */
	char const *rep_end;    /* [1..1][>= rep_pat][const] Pattern end
	                         * WARNING: This memory address must be dereferencable, and point to a NUL-byte!
	                         * -> Internally, the parser only checks for end-of-pattern when it hits a  NUL-
	                         *    byte, at which point it check if  that byte appeared at `rep_end'. If  so,
	                         *    then the end of the pattern has been reached; if not, then the NUL-byte it
	                         *    just found is encoded as a literal NUL-byte (e.g. 'exact "\0"').
	                         * -> This makes it possible for the pattern to match NUL-bytes in input, without
	                         *    needing to make use of other kos-extensions like "\0", "\x00", or  similar. */
	__uintptr_t rep_syntax; /* [const] RE syntax flags (set of `RE_SYNTAX_*') */
};

#define re_parser_init(self, pattern, pattern_end, syntax) \
	(void)((self)->rep_pos    = (pattern),                 \
	       (self)->rep_pat    = (pattern),                 \
	       (self)->rep_end    = (pattern_end),             \
	       (self)->rep_syntax = (syntax))

/* Regex token (one of `RE_TOKEN_*', or a utf-32 character (or byte when `RE_SYNTAX_NO_UTF8' is set)) */
typedef __uint32_t re_token_t;
#define RE_TOKEN_BASE           0x110000               /* First regex token number */
#define RE_TOKEN_BYTE80h_MIN    RE_TOKEN_BASE          /* "\x80" */
#define RE_TOKEN_BYTE80h_MAX    (RE_TOKEN_BASE + 0x7f) /* "\xff" */
#define RE_TOKEN_XBASE          0x110080               /* First custom regex token number */
#define RE_TOKEN_ISBYTE80h(x)   ((x) >= RE_TOKEN_BYTE80h_MIN && (x) <= RE_TOKEN_BYTE80h_MAX)
#define RE_TOKEN_GETBYTE80h(x)  ((__byte_t)(0x80 + (x) - RE_TOKEN_BYTE80h_MIN))
#define RE_TOKEN_ISUTF8(x)      ((x) >= 0x80 && (x) < RE_TOKEN_BASE)
#define RE_TOKEN_ISLITERAL(x)   ((x) < RE_TOKEN_XBASE)
#define RE_TOKEN_ISSUFFIX(x)    ((x) >= RE_TOKEN_PLUS && (x) <= RE_TOKEN_STARTINTERVAL)
#define RE_TOKEN_ANY            (RE_TOKEN_XBASE + 1)  /* '.' */
#define RE_TOKEN_PLUS           (RE_TOKEN_XBASE + 2)  /* '+' */
#define RE_TOKEN_STAR           (RE_TOKEN_XBASE + 3)  /* '*' */
#define RE_TOKEN_QMARK          (RE_TOKEN_XBASE + 4)  /* '?' */
#define RE_TOKEN_STARTINTERVAL  (RE_TOKEN_XBASE + 5)  /* '{' */
#define RE_TOKEN_STARTSET       (RE_TOKEN_XBASE + 6)  /* '[' */
#define RE_TOKEN_STARTGROUP     (RE_TOKEN_XBASE + 7)  /* '(' */
#define RE_TOKEN_ENDGROUP       (RE_TOKEN_XBASE + 8)  /* ')' */
#define RE_TOKEN_ALTERNATION    (RE_TOKEN_XBASE + 9)  /* '|' */
#define RE_TOKEN_BK_w           (RE_TOKEN_XBASE + 10) /* '\w' (<[:symcont:]>  -- REOP_ASCII_ISSYMCONT / REOP_UTF8_ISSYMCONT) */
#define RE_TOKEN_BK_W           (RE_TOKEN_XBASE + 11) /* '\W' (<[^:symcont:]> -- REOP_ASCII_ISSYMCONT_NOT / REOP_UTF8_ISSYMCONT_NOT) */
#define RE_TOKEN_BK_s           (RE_TOKEN_XBASE + 12) /* '\s' (<[:space:]>    -- REOP_ASCII_ISSPACE / REOP_UTF8_ISSPACE) */
#define RE_TOKEN_BK_S           (RE_TOKEN_XBASE + 13) /* '\S' (<[^:space:]>   -- REOP_ASCII_ISSPACE_NOT / REOP_UTF8_ISSPACE_NOT) */
#define RE_TOKEN_BK_d           (RE_TOKEN_XBASE + 14) /* '\d' (<[:digit:]>    -- REOP_ASCII_ISDIGIT / REOP_UTF8_ISDIGIT) */
#define RE_TOKEN_BK_D           (RE_TOKEN_XBASE + 15) /* '\D' (<[^:digit:]>   -- REOP_ASCII_ISDIGIT_NOT / REOP_UTF8_ISDIGIT_NOT) */
#define RE_TOKEN_BK_n           (RE_TOKEN_XBASE + 16) /* '\n' (<[:lf:]>       -- [\r\n] / REOP_UTF8_ISLF) */
#define RE_TOKEN_BK_N           (RE_TOKEN_XBASE + 17) /* '\N' (<[:lf:]>       -- [^\r\n] / REOP_UTF8_ISLF_NOT) */
#define case_RE_TOKEN_AT_MIN_to_MAX                                                             \
	case RE_TOKEN_AT_SOL: case RE_TOKEN_AT_EOL:     case RE_TOKEN_AT_SOI: case RE_TOKEN_AT_EOI: \
	case RE_TOKEN_AT_WOB: case RE_TOKEN_AT_WOB_NOT: case RE_TOKEN_AT_SOW: case RE_TOKEN_AT_EOW: \
	case RE_TOKEN_AT_SOS: case RE_TOKEN_AT_EOS
#define RE_TOKEN_AT_MIN         RE_TOKEN_AT_SOL
#define RE_TOKEN_AT_SOL         (RE_TOKEN_XBASE + 18) /* "^" */
#define RE_TOKEN_AT_EOL         (RE_TOKEN_XBASE + 19) /* "$" */
#define RE_TOKEN_AT_SOI         (RE_TOKEN_XBASE + 20) /* "\`" */
#define RE_TOKEN_AT_EOI         (RE_TOKEN_XBASE + 21) /* "\'" */
#define RE_TOKEN_AT_WOB         (RE_TOKEN_XBASE + 22) /* "\b" */
#define RE_TOKEN_AT_WOB_NOT     (RE_TOKEN_XBASE + 23) /* "\B" */
#define RE_TOKEN_AT_SOW         (RE_TOKEN_XBASE + 24) /* "\<" */
#define RE_TOKEN_AT_EOW         (RE_TOKEN_XBASE + 25) /* "\>" */
#define RE_TOKEN_AT_SOS         (RE_TOKEN_XBASE + 26) /* "\_<" */
#define RE_TOKEN_AT_EOS         (RE_TOKEN_XBASE + 27) /* "\_>" */
#define RE_TOKEN_AT_MAX         RE_TOKEN_AT_EOS
#define case_RE_TOKEN_BKREF_1_to_9 \
	case RE_TOKEN_BKREF_1: case RE_TOKEN_BKREF_2: case RE_TOKEN_BKREF_3: \
	case RE_TOKEN_BKREF_4: case RE_TOKEN_BKREF_5: case RE_TOKEN_BKREF_6: \
	case RE_TOKEN_BKREF_7: case RE_TOKEN_BKREF_8: case RE_TOKEN_BKREF_9
#define RE_TOKEN_BKREF_1        (RE_TOKEN_XBASE + 28) /* "\1" */
#define RE_TOKEN_BKREF_2        (RE_TOKEN_XBASE + 29) /* "\2" */
#define RE_TOKEN_BKREF_3        (RE_TOKEN_XBASE + 30) /* "\3" */
#define RE_TOKEN_BKREF_4        (RE_TOKEN_XBASE + 31) /* "\4" */
#define RE_TOKEN_BKREF_5        (RE_TOKEN_XBASE + 32) /* "\5" */
#define RE_TOKEN_BKREF_6        (RE_TOKEN_XBASE + 33) /* "\6" */
#define RE_TOKEN_BKREF_7        (RE_TOKEN_XBASE + 34) /* "\7" */
#define RE_TOKEN_BKREF_8        (RE_TOKEN_XBASE + 35) /* "\8" */
#define RE_TOKEN_BKREF_9        (RE_TOKEN_XBASE + 36) /* "\9" */
#define RE_TOKEN_ERROR(code)    (RE_TOKEN_XBASE + 37 + (code)) /* Propagate error-condition */
#define RE_TOKEN_ISERROR(code)  ((code) >= RE_TOKEN_ERROR(0))
#define RE_TOKEN_GETERROR(code) ((re_errno_t)((code)-RE_TOKEN_ERROR(0)))
#define RE_TOKEN_UNMATCHED_BK   RE_TOKEN_ERROR(RE_EESCAPE)
#define RE_TOKEN_ILLSEQ         RE_TOKEN_ERROR(RE_EILLSEQ)
#define RE_TOKEN_EOF            RE_TOKEN_ERROR(RE_EEND)

/* Parse and yield the next regex-token pointed-to by `self->rep_pos'.
 * @return: * : A unicode character, or one of `RE_TOKEN_*' */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) re_token_t
__NOTHROW_NCX_T(LIBREGEX_CC *PRE_PARSER_YIELD)(struct re_parser *__restrict self);
#ifdef LIBREGEX_WANT_PROTOTYPES
LIBREGEX_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) re_token_t
__NOTHROW_NCX(LIBREGEX_CC re_parser_yield)(struct re_parser *__restrict self);
#define re_parser_yieldat(self, pos) ((self)->rep_pos = (pos), re_parser_yield(self))
#endif /* LIBREGEX_WANT_PROTOTYPES */


/* The compiled regex output structure produced by `re_compiler_compile(3R)' */
struct re_code {
	__byte_t   rc_fmap[256]; /* Fast map: take the first byte of input data to match as index:
	                          * - rc_fmap[input[0]] == 0xff --> input will never match
	                          * - rc_fmap[input[0]] != 0xff --> Start executing at `PC = rc_code + rc_fmap[input[0]]'
	                          * Allowed  to be `0x00', even if the regex never accepts input starting with that byte.
	                          * iow: all 256 possible bytes indicating `0x00' is always valid.
	                          * The only assumptions that may be made are:
	                          * -> rc_fmap[X] == 0xff --> `rc_code' always rejects input whose first byte is `X'
	                          * -> rc_fmap[X] >  0x00 --> `rc_code'  only ever handles a first byte `X' in a branch
	                          *                           that begins at  this offset (e.g.  "abc|def" can set  the
	                          *                           fmap offset for "d"  to directly point at  `exact "def"')
	                          *                           Note that this doesn't guaranty that `rc_code' won't just
	                          *                           always reject input whose first byte is `X'!
	                          * -> rc_fmap[X] == 0x00 --> `rc_code' may or may not accept input starting with `X' */
	__size_t   rc_minmatch;  /* The smallest input length that can be matched by `rc_code' (or `0' when `rc_code' can match epsilon)
	                          * NOTE: Allowed to be less than the *true* minimum-match length of `rc_code'; iow: `0' is always valid
	                          * -> The only assumption allowed is that input smaller than this will never match. */
	__uint16_t rc_ngrps;     /* # of groups referenced by code (<= 0x100) */
	__uint16_t rc_nvars;     /* # of variables referenced by code (<= 0x100) */
	__uint8_t  rc_flags;     /* Regex code flags (set of `RE_CODE_FLAG_*') */
#define RE_CODE_FLAG_NORMAL     0x00 /* Normal flags. */
#define RE_CODE_FLAG_NEEDGROUPS 0x01 /* Groups are expected to be correct (set if `REOP_GROUP_MATCH*' opcodes are used) */
#define RE_CODE_FLAG_OPTGROUPS  0x02 /* The regex code contains optional groups (e.g. "foo(x)?bar" or "foo(|b(a)r)") */
	__COMPILER_FLEXIBLE_ARRAY(__byte_t, rc_code); /* Code buffer (`REOP_*' instruction stream) */
};


/* Regex compiler structure */
struct re_compiler {
	struct re_parser    rec_parser;     /* Underlying parser. */
	union {
		struct re_code *rec_code;       /* [?..1][owned] Regex code object that is being produced. */
		__byte_t       *rec_cbase;      /* [?..1][<= rec_cend][owned] Base-pointer for output code-buffer. */
	};
	__byte_t           *rec_estart;     /* [?..1][<= rec_cpos] Start-pointer for current expression's code. */
	__byte_t           *rec_cpos;       /* [?..1][>= rec_cbase && <= rec_cend] Pointer to next unset opcode in code-buffer. */
	__byte_t           *rec_cend;       /* [?..1][>= rec_cbase] End-pointer for output code-buffer. */
	__uint8_t           rec_grpinfo[9]; /* Information about the first 9 groups (for back-references); each is a set of `RE_COMPILER_GRPINFO_*' */
#define RE_COMPILER_GRPINFO_DEFINED 0x01 /* Group has been defined */
#define RE_COMPILER_GRPINFO_EPSILON 0x02 /* Group contents are able to match epsilon (for `REOP_GROUP_MATCH_Jn') */
};

#define re_compiler_init(self, pattern, pattern_end, syntax)                  \
	(void)(re_parser_init(&(self)->rec_parser, pattern, pattern_end, syntax), \
	       (self)->rec_cbase = (self)->rec_estart = __NULLPTR,                \
	       (self)->rec_cpos = (self)->rec_cend = __NULLPTR,                   \
	       __libc_bzero((self)->rec_grpinfo, sizeof((self)->rec_grpinfo)))
#define re_compiler_fini(self) \
	(void)__libc_free((self)->rec_cbase)
#ifdef LIBREGEX_WANT_PROTOTYPES
#define re_compiler_yield(self)        re_parser_yield(&(self)->rec_parser)
#define re_compiler_yieldat(self, pos) re_parser_yieldat(&(self)->rec_parser, pos)
#endif /* LIBREGEX_WANT_PROTOTYPES */


/* Pack the result of the given reg-ex compiler `self',
 * and return its  produced `struct re_code'. Use  this
 * function INSTEAD OF `re_compiler_fini(3R)' following
 * a successful call to `re_compiler_compile(3R)' */
#define re_compiler_pack(self) ((self)->rec_code)


/* Parse  and compile the pattern given to `self' to generate code.
 * Even  upon error, `self'  remains in a  valid state (except that
 * you're  not allowed to call `re_compiler_compile(3R)' again), so
 * that the caller has to invoke `re_compiler_fini(3R)' in order to
 * perform cleanup.
 * Upon success, members of `self' are initialized as:
 * - *rec_parser.rep_pos    == '\0'
 * - rec_parser.rep_pos     == rec_parser.rep_end
 * - rec_parser.rep_syntax  == <unchanged>
 * - rec_parser.rec_cbase   == <pointer-to-struct re_code>
 * - rec_parser.rec_estart  == <undefined>
 * - rec_parser.rec_cpos    == <undefined>
 * - rec_parser.rec_cend    == <code-end-pointer (1 past the `REOP_MATCHED[_PERFECT]' opcode)>
 * - rec_parser.rec_ngrp    == <greaters-referenced-group + 1>
 * - rec_parser.rec_nvar    == <greaters-referenced-var + 1>
 * - rec_parser.rec_grpinfo == <undefined>
 * @return: RE_NOERROR:  Success
 * @return: RE_BADPAT:   General pattern syntax error.
 * @return: RE_ECOLLATE: Unsupported/unknown collating character (in '[[.xxx.]]' and '[[=xxx=]]')
 * @return: RE_ECTYPE:   Invalid/unknown character class name.
 * @return: RE_EESCAPE:  Trailing backslash.
 * @return: RE_ESUBREG:  Invalid back reference.
 * @return: RE_EBRACK:   Unmatched '['.
 * @return: RE_EPAREN:   Unmatched '('.
 * @return: RE_EBRACE:   Unmatched '{'.
 * @return: RE_BADBR:    Invalid contents of '{...}'.
 * @return: RE_ERANGE:   Invalid range end (e.g. '[z-a]').
 * @return: RE_ESPACE:   Out of memory.
 * @return: RE_BADRPT:   Nothing is preceding '+', '*', '?' or '{'.
 * @return: RE_EEND:     Unexpected end of pattern.
 * @return: RE_ESIZE:    Compiled pattern bigger than 2^16 bytes.
 * @return: RE_ERPAREN:  Unmatched ')' (only when `RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD' was set)
 * @return: RE_EILLSEQ:  Illegal unicode character (when `RE_NO_UTF8' wasn't set)
 * @return: RE_EILLSET:  Tried to combine raw bytes with unicode characters in charsets (e.g. "[Ä\xC3]") */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) re_errno_t
__NOTHROW_NCX_T(LIBREGEX_CC *PRE_COMPILER_COMPILE)(struct re_compiler *__restrict self);
#ifdef LIBREGEX_WANT_PROTOTYPES
LIBREGEX_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) re_errno_t
__NOTHROW_NCX(LIBREGEX_CC re_compiler_compile)(struct re_compiler *__restrict self);
#endif /* LIBREGEX_WANT_PROTOTYPES */



/* Print a disassembly of `self' (for debugging) */
typedef __ATTR_NONNULL_T((1)) __ssize_t
__NOTHROW_NCX_T(LIBREGEX_CC *PRE_CODE_DISASM)(struct re_code const *__restrict self,
                                              __pformatprinter printer, void *arg);
#if !defined(LIBREGEX_NO_RE_CODE_DISASM) && !defined(NDEBUG)
#ifdef LIBREGEX_WANT_PROTOTYPES
LIBREGEX_DECL __ATTR_NONNULL((1)) __ssize_t
__NOTHROW_NCX(LIBREGEX_CC re_code_disasm)(struct re_code const *__restrict self,
                                          __pformatprinter printer, void *arg);
#endif /* LIBREGEX_WANT_PROTOTYPES */
#endif /* !LIBREGEX_NO_RE_CODE_DISASM && !NDEBUG */




__DECL_END

#endif /* !_LIBREGEX_REGCOMP_H */
