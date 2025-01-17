/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBJSON_GENERATOR_H
#define _LIBJSON_GENERATOR_H 1

#include <__stdinc.h>
#include <__crt.h> /* __NO_FPU */

#include <hybrid/byteorder.h>
#include <hybrid/typecore.h>

#include "api.h"

__DECL_BEGIN

/* Combination of writer  + parser that  can be  used to define  object layout  definitions,
 * which  can then be  used to describe a  mapping between json  and regular, old C-structs.
 * For this purpose, a special bytecode exists that encodes field names, types, and offsets:
 * >> struct my_struct {
 * >> 	int   ms_alpha;
 * >> 	int   ms_beta;
 * >> 	char *ms_name;
 * >> 	int   ms_values[8];
 * >> };
 * >> PRIVATE byte_t const my_struct_codec[] = {
 * >> 	JGEN_BEGINOBJECT,
 * >> 		JGEN_FIELD, 'a', 'l', 'p', 'h', 'a', 0, JGEN_INTO, JSON_OFFSETOF(struct my_struct, ms_alpha), JSON_TYPE_INT,
 * >> 		JGEN_FIELD, 'b', 'e', 't', 'a',      0, JGEN_INTO, JSON_OFFSETOF(struct my_struct, ms_beta), JSON_TYPE_INT,
 * >> 		JGEN_FIELD, 'n', 'a', 'm', 'e',      0, JGEN_INTO, JSON_OFFSETOF(struct my_struct, ms_name), JSON_TYPE_STRING_OR_NULL,
 * >> 		JGEN_FIELD, 'v', 'a', 'l', 'u', 'e', 's', 0, JGEN_BEGINARRAY,
 * >> 			JGEN_INDEX_REP(8, sizeof(int)), JGEN_INTO, JSON_OFFSETOF(struct my_struct, ms_values), JSON_TYPE_INT,
 * >> 		JGEN_END,
 * >> 	JGEN_END,
 * >> 	JGEN_TERM
 * >> };
 * >>
 * >> ...
 * >>
 * >> struct my_struct foo;
 * >> foo.ms_alpha = 10;
 * >> foo.ms_beta  = 20;
 * >> foo.ms_name  = "This is my name";
 * >> for (int i = 0; i < 8; ++i)
 * >> 	foo.ms_values[i] = 1 << i;
 * >> struct json_writer writer;
 * >> json_writer_init(&writer, &file_printer, stdout, JSON_WRITER_FORMAT_PRETTY);
 * >> json_encode(&writer, my_struct_codec, &foo);
 * Output:
 * >> {
 * >> 	"alpha": 10,
 * >> 	"beta": 20,
 * >> 	"name": "This is my name",
 * >> 	"values": [
 * >> 		1,
 * >> 		2,
 * >> 		4,
 * >> 		8,
 * >> 		16,
 * >> 		32,
 * >> 		64
 * >> 	]
 * >> }
 */

#ifdef __CC__
struct json_writer;
struct json_parser;

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define JGEN_ENCODE_UINT16(value) (value)&0xff, ((value)&0xff00) >> 8
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define JGEN_ENCODE_UINT16(value) ((value)&0xff00) >> 8, (value)&0xff
#endif

/* Json generator codec byteops
 * NOTE: Any generator codec must start with one of the following opcodes:
 *   - JGEN_BEGINOBJECT
 *   - JGEN_BEGINARRAY
 *   - JGEN_EXTERN(...)
 *   - JGEN_OPTIONAL    (Followed by `JGEN_BEGINOBJECT', `JGEN_BEGINARRAY' or `JGEN_EXTERN(...)')
 *   - JGEN_INTO        (Only allowed within the global scope: Parse the next
 *                       element as one of bool, number, float, string or null)
 *   - JGEN_TERM        (Mark the end of the codec) */


/* JGEN bytecode syntax:
 * Read as:
 *    x        The contents of the rule `x'
 *    [x]      `x' is optional
 *    'x'      `x' is the name of an opcode that is expected
 *    x y      First `x', then `y'
 *    x | y    Either `x' or `y'
 *    (x)      Same as `x' (used to clarify indent, and scope `|')
 *    x...     `x' can be repeated any number of times (but at least once)
 *    x ::= y  `x' is a rule defined as `y'
 *    @codec   Name for the primary rule.
 *
 *
 * @codec ::= [['JGEN_OPTIONAL'] DECL] 'JGEN_TERM';
 *
 * DECL ::= OBJECT_DECL | ARRAY_DECL | IMMEDIATE_DECL | EXTERN_DECL;
 *
 * OBJECT_DECL ::= (
 *     'JGEN_BEGINOBJECT'
 *     [(
 *         ['JGEN_OPTIONAL'] 'JGEN_FIELD'
 *         <Field name as inlined, NUL-terminated c-string>
 *         DECL
 *     )...]
 *     'JGEN_END'
 * );
 *
 * ARRAY_DECL ::= (
 *     'JGEN_BEGINARRAY'
 *     [(
 *         (['JGEN_OPTIONAL'] 'JGEN_INDEX_REP(...)' DECL) |
 *         ((
 *             ['JGEN_OPTIONAL'] 'JGEN_INDEX(...)'
 *             DECL
 *         )...)
 *     )]
 *     'JGEN_END'
 * );
 *
 * IMMEDIATE_DECL ::= (
 *     'JGEN_INTO'
 *     'JSON_OFFSET(...)'
 *     'JSON_TYPE_*'
 * );
 *
 * EXTERN_DECL ::= (
 *     'JGEN_EXTERN(...)'
 * );
 *
 */



/* Generator terminal indicator.
 * Must always appear at the end of any json codec. */
#define JGEN_TERM         0x00

/* End an object or array.
 * Must be followed by one of the same as the opcodes
 * as  those  allowed  at  the  start  of  a   codec. */
#define JGEN_END          0x01

/* Begin a new object.
 * Must be followed by one of:
 *    - JGEN_FIELD    (Repeated any number of times)
 *    - JGEN_OPTIONAL (Followed by `JGEN_FIELD')
 * ... must be followed by:
 *    - JGEN_END */
#define JGEN_BEGINOBJECT  0x02

/* Begin a new array.
 * Must be followed by one of:
 *    - JGEN_OPTIONAL     // Followed by `JGEN_INDEX' or `JGEN_INDEX_REP_OP')
 *    - JGEN_INDEX        // Repeated any number of times, though with ever increasing
 *                        // indices  Note that unspecified indices are ignored during
 *                        // decoding, and written as `null' during encoding)
 *    - JGEN_INDEX_REP_OP // May only appear once, and must then be used to describe
 *                        // the entire array from start to finish)
 * ... must be followed by:
 *    - JGEN_END */
#define JGEN_BEGINARRAY   0x03

/* [+uint16_t offset][+uint16_t id] Insert an external  json codec at this  location.
 * This is the same as having all instructions of that external codec appear in-line,
 * with  `offset'  added  to  the  offset  field  of  every  `JGEN_INTO' instruction.
 * The given `id'  is an index  into the  `ext' array accepted  by the  encode/decode
 * API functions. */
#define JGEN_EXTERN_OP    0x04
#define JGEN_EXTERN(offset, id) \
	JGEN_EXTERN_OP, JGEN_ENCODE_UINT16(offset), JGEN_ENCODE_UINT16(id)

/* Optional modifier prefix.
 * When  the  associated  data  doesn't  exist,  or  is  initiated   using
 * the   `null'-token,   data   is   zero-initialized   during   decoding.
 * Must be followed by one of (depending on where this modifier was used):
 *    - JGEN_FIELD
 *    - JGEN_BEGINOBJECT
 *    - JGEN_BEGINARRAY
 *    - JGEN_EXTERN(...)
 *    - JGEN_INDEX(...)
 *    - JGEN_INDEX_REP(...) */
#define JGEN_OPTIONAL     0x08

/* [+char utf8_c_string[]] Address a named field.
 * Must be followed by:
 *    - JGEN_BEGINOBJECT
 *    - JGEN_BEGINARRAY
 *    - JGEN_EXTERN(...)
 *    - JGEN_INTO */
#define JGEN_FIELD        0x10

/* [+uint16_t index] Address a specific array index
 * Must be followed by:
 *    - JGEN_BEGINOBJECT // For [{ ... }, ...]
 *    - JGEN_BEGINARRAY  // For [[ ... ], ...]
 *    - JGEN_EXTERN(...) // External codec...
 *    - JGEN_INTO        // For [ 10, ... ] */
#define JGEN_INDEX_OP     0x11
#define JGEN_INDEX(index) \
	JGEN_INDEX_OP, JGEN_ENCODE_UINT16(index)

/* [+uint16_t count][+uint16_t stride] Repeat an index operation
 * Must be followed by:
 *    - JGEN_BEGINOBJECT  // For [{ ... }, { ... }, ...]
 *    - JGEN_BEGINARRAY   // For [[ ... ], [ ... ], ...]
 *    - JGEN_EXTERN(...)  // External codec...
 *    - JGEN_INTO         // For [ 10, 20, 30, ... ]
 * This operator can be used to quickly define a complete array:
 * >> JGEN_BEGINARRAY,
 * >> 	JGEN_INDEX_REP(4, sizeof(int)), JGEN_INTO, JSON_OFFSETOF(struct my_struct, ms_values), JSON_TYPE_INT,
 * >> JGEN_END,
 * Same as:
 * >> JGEN_BEGINARRAY,
 * >> 	JGEN_INDEX(0), JGEN_INTO, JSON_OFFSETOF(struct my_struct, ms_values[0]), JSON_TYPE_INT,
 * >> 	JGEN_INDEX(1), JGEN_INTO, JSON_OFFSETOF(struct my_struct, ms_values[1]), JSON_TYPE_INT,
 * >> 	JGEN_INDEX(2), JGEN_INTO, JSON_OFFSETOF(struct my_struct, ms_values[2]), JSON_TYPE_INT,
 * >> 	JGEN_INDEX(3), JGEN_INTO, JSON_OFFSETOF(struct my_struct, ms_values[3]), JSON_TYPE_INT,
 * >> JGEN_END, */
#define JGEN_INDEX_REP_OP 0x12
#define JGEN_INDEX_REP(count, stride) \
	JGEN_INDEX_REP_OP, JGEN_ENCODE_UINT16((count) - 1), JGEN_ENCODE_UINT16(stride)

/* [+uint16_t offset][+uint8_t type]
 * Descriptor for the C type and structure offset of data to be de-/encoded
 * Must be followed by (in order):
 *   #1: JSON_OFFSET(...)
 *   #2: JSON_TYPE_* */
#define JGEN_INTO         0x13


/* Offset parameter generators for `JGEN_INTO' */
#define JSON_OFFSET(value)         JGEN_ENCODE_UINT16(value)
#define JSON_OFFSETOF(type, field) JGEN_ENCODE_UINT16(__builtin_offsetof(type, field))

/* Type parameter generators for `JGEN_INTO' */
#define JSON_TYPE_BOOL                0xe0 /* bool */
#define JSON_TYPE_BOOLBIT(bit)       (0xe0 | ((bit)&0x7)) /* Boolean bitflag (`*((u8 *)base + offset) ^= 1 << bit') */
#define JSON_TYPE_BOOLFLAG(flag)                     \
	((flag) == 0x01 ? 0xe0 : (flag) == 0x02 ? 0xe1 : \
	 (flag) == 0x04 ? 0xe2 : (flag) == 0x08 ? 0xe3 : \
	 (flag) == 0x10 ? 0xe4 : (flag) == 0x20 ? 0xe5 : \
	 (flag) == 0x40 ? 0xe6 : 0xe7)
#define JSON_TYPE_INT8                  0xe8 /* signed, 8-bit integer */
#define JSON_TYPE_INT16                 0xe9 /* signed, 16-bit integer */
#define JSON_TYPE_INT32                 0xea /* signed, 32-bit integer */
#define JSON_TYPE_INT64                 0xeb /* signed, 64-bit integer */
#define JSON_TYPE_UINT8                 0xec /* unsigned, 8-bit integer */
#define JSON_TYPE_UINT16                0xed /* unsigned, 16-bit integer */
#define JSON_TYPE_UINT32                0xee /* unsigned, 32-bit integer */
#define JSON_TYPE_UINT64                0xef /* unsigned, 64-bit integer */
#define JSON_TYPE_STRING                0xf0 /* utf8 *str -- Filled with a pointer returned by `libjson_parser_getstring()' */
#define JSON_TYPE_STRING_OR_NULL        0xf1 /* Same as `JSON_TYPE_STRING', but also allow a `null' token, which results in `NULL' */
#define JSON_TYPE_INLINE_STRING_OP      0xf2 /* [+uint16_t length] utf8[length] */
#define JSON_TYPE_INLINE_STRING(length) \
	JSON_TYPE_INLINE_STRING_OP, JGEN_ENCODE_UINT16(length)
#define JSON_TYPE_STRING_WITH_LENGTH_OP 0xf9 /* [+uint16_t len_offset] utf8 *str; size_t len@len_offset; */
#define JSON_TYPE_STRING_WITH_LENGTH(len_offset) \
	JSON_TYPE_STRING_WITH_LENGTH_OP, JGEN_ENCODE_UINT16(len_offset)
#define JSON_TYPE_VOID                  0xf3 /* void (nothing; parsed as `null'; the associated offset is ignored) */
#ifndef __NO_FPU
#define JSON_TYPE_FLOAT                 0xfd /* float */
#define JSON_TYPE_DOUBLE                0xfe /* double */
#ifdef __COMPILER_HAVE_LONGLONG
#define JSON_TYPE_LDOUBLE               0xff /* long double */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* !__NO_FPU */


#define JSON_PRIVATE_STYPEFOR_1  JSON_TYPE_INT8
#define JSON_PRIVATE_STYPEFOR_2  JSON_TYPE_INT16
#define JSON_PRIVATE_STYPEFOR_4  JSON_TYPE_INT32
#define JSON_PRIVATE_STYPEFOR_8  JSON_TYPE_INT64
#define JSON_PRIVATE_UTYPEFOR_1  JSON_TYPE_UINT8
#define JSON_PRIVATE_UTYPEFOR_2  JSON_TYPE_UINT16
#define JSON_PRIVATE_UTYPEFOR_4  JSON_TYPE_UINT32
#define JSON_PRIVATE_UTYPEFOR_8  JSON_TYPE_UINT64
#define JSON_PRIVATE_STYPEFOR2(sizeof) JSON_PRIVATE_STYPEFOR_##sizeof
#define JSON_PRIVATE_UTYPEFOR2(sizeof) JSON_PRIVATE_UTYPEFOR_##sizeof
#define JSON_PRIVATE_STYPEFOR(sizeof) JSON_PRIVATE_STYPEFOR2(sizeof)
#define JSON_PRIVATE_UTYPEFOR(sizeof) JSON_PRIVATE_UTYPEFOR2(sizeof)

#define JSON_TYPE_SCHAR          JSON_PRIVATE_STYPEFOR(__SIZEOF_CHAR__)
#define JSON_TYPE_UCHAR          JSON_PRIVATE_UTYPEFOR(__SIZEOF_CHAR__)
#define JSON_TYPE_SHORT          JSON_PRIVATE_STYPEFOR(__SIZEOF_SHORT__)
#define JSON_TYPE_USHORT         JSON_PRIVATE_UTYPEFOR(__SIZEOF_SHORT__)
#define JSON_TYPE_INT            JSON_PRIVATE_STYPEFOR(__SIZEOF_INT__)
#define JSON_TYPE_UINT           JSON_PRIVATE_UTYPEFOR(__SIZEOF_INT__)
#define JSON_TYPE_LONG           JSON_PRIVATE_STYPEFOR(__SIZEOF_LONG__)
#define JSON_TYPE_ULONG          JSON_PRIVATE_UTYPEFOR(__SIZEOF_LONG__)
#ifdef __COMPILER_HAVE_LONGLONG
#define JSON_TYPE_LLONG          JSON_PRIVATE_STYPEFOR(__SIZEOF_LONG_LONG__)
#define JSON_TYPE_ULLONG         JSON_PRIVATE_UTYPEFOR(__SIZEOF_LONG_LONG__)
#endif /* __COMPILER_HAVE_LONGLONG */
#define JSON_TYPE_SIZE_T         JSON_PRIVATE_UTYPEFOR(__SIZEOF_SIZE_T__)
#define JSON_TYPE_SSIZE_T        JSON_PRIVATE_STYPEFOR(__SIZEOF_SIZE_T__)
#define JSON_TYPE_PTRDIFF_T      JSON_PRIVATE_STYPEFOR(__SIZEOF_PTRDIFF_T__)
#define JSON_TYPE_INTPTR_T       JSON_PRIVATE_STYPEFOR(__SIZEOF_POINTER__)
#define JSON_TYPE_UINTPTR_T      JSON_PRIVATE_UTYPEFOR(__SIZEOF_POINTER__)
#define JSON_TYPE_INTMAX_T       JSON_PRIVATE_STYPEFOR(__SIZEOF_INTMAX_T__)
#define JSON_TYPE_UINTMAX_T      JSON_PRIVATE_UTYPEFOR(__SIZEOF_INTMAX_T__)
#define JSON_TYPE_CHAR16_T       JSON_TYPE_UINT16
#define JSON_TYPE_CHAR32_T       JSON_TYPE_UINT32
#ifdef __SIZEOF_WCHAR_T__
#ifdef __WCHAR_UNSIGNED__
#define JSON_TYPE_WCHAR_T        JSON_PRIVATE_UTYPEFOR(__SIZEOF_WCHAR_T__)
#else /* __WCHAR_UNSIGNED__ */
#define JSON_TYPE_WCHAR_T        JSON_PRIVATE_STYPEFOR(__SIZEOF_WCHAR_T__)
#endif /* !__WCHAR_UNSIGNED__ */
#endif /* __SIZEOF_WCHAR_T__ */
#define JSON_TYPE_INT_FAST8_T    JSON_PRIVATE_STYPEFOR(__SIZEOF_INT_FAST8_T__)
#define JSON_TYPE_UINT_FAST8_T   JSON_PRIVATE_UTYPEFOR(__SIZEOF_INT_FAST8_T__)
#define JSON_TYPE_INT_FAST16_T   JSON_PRIVATE_STYPEFOR(__SIZEOF_INT_FAST16_T__)
#define JSON_TYPE_UINT_FAST16_T  JSON_PRIVATE_UTYPEFOR(__SIZEOF_INT_FAST16_T__)
#define JSON_TYPE_INT_FAST32_T   JSON_PRIVATE_STYPEFOR(__SIZEOF_INT_FAST32_T__)
#define JSON_TYPE_UINT_FAST32_T  JSON_PRIVATE_UTYPEFOR(__SIZEOF_INT_FAST32_T__)
#ifdef __SIZEOF_INT_FAST64_T__
#define JSON_TYPE_INT_FAST64_T   JSON_PRIVATE_STYPEFOR(__SIZEOF_INT_FAST64_T__)
#define JSON_TYPE_UINT_FAST64_T  JSON_PRIVATE_UTYPEFOR(__SIZEOF_INT_FAST64_T__)
#endif /* __SIZEOF_INT_FAST64_T__ */
#define JSON_TYPE_INT_LEAST8_T   JSON_PRIVATE_STYPEFOR(__SIZEOF_INT_LEAST8_T__)
#define JSON_TYPE_UINT_LEAST8_T  JSON_PRIVATE_UTYPEFOR(__SIZEOF_INT_LEAST8_T__)
#define JSON_TYPE_INT_LEAST16_T  JSON_PRIVATE_STYPEFOR(__SIZEOF_INT_LEAST16_T__)
#define JSON_TYPE_UINT_LEAST16_T JSON_PRIVATE_UTYPEFOR(__SIZEOF_INT_LEAST16_T__)
#define JSON_TYPE_INT_LEAST32_T  JSON_PRIVATE_STYPEFOR(__SIZEOF_INT_LEAST32_T__)
#define JSON_TYPE_UINT_LEAST32_T JSON_PRIVATE_UTYPEFOR(__SIZEOF_INT_LEAST32_T__)
#ifdef __SIZEOF_INT_LEAST64_T__
#define JSON_TYPE_INT_LEAST64_T  JSON_PRIVATE_STYPEFOR(__SIZEOF_INT_LEAST64_T__)
#define JSON_TYPE_UINT_LEAST64_T JSON_PRIVATE_UTYPEFOR(__SIZEOF_INT_LEAST64_T__)
#endif /* __SIZEOF_INT_LEAST64_T__ */

#ifdef __CHAR_UNSIGNED__
#define JSON_TYPE_CHAR   JSON_TYPE_UCHAR
#else /* __CHAR_UNSIGNED__ */
#define JSON_TYPE_CHAR   JSON_TYPE_SCHAR
#endif /* !__CHAR_UNSIGNED__ */




/* Encode a given object `src' as Json, using the given `codec' as generator.
 * @param: ext: External codec vector (s.a. `JGEN_EXTERN(...)')
 * @return:  0: Success
 * @return: -1: Error: `writer->jw_result' has a negative value when the function was called.
 * @return: -1: Error: An invocation of the `writer->jw_printer' returned a negative value.
 * @return: -2: Error: Invalid usage during this, or during an earlier call. */
typedef __ATTR_NONNULL_T((1, 2, 3)) int
(LIBJSON_CC *PJSON_ENCODE)(struct json_writer *__restrict __writer,
                           void const *__restrict __codec,
                           void const *__restrict __src,
                           void const *const *__ext);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1, 2, 3)) int LIBJSON_CC
json_encode(struct json_writer *__restrict __writer,
            void const *__restrict __codec,
            void const *__restrict __src,
            void const *const *__ext);
#endif /* LIBJSON_WANT_PROTOTYPES */

/* Decode a given object `dst' from Json, using the given `codec' as generator.
 * @param: ext: External codec vector (s.a. `JGEN_EXTERN(...)')
 * @return: JSON_ERROR_OK:     Success.
 * @return: JSON_ERROR_SYNTAX: Syntax error.
 * @return: JSON_ERROR_NOOBJ:  A required field doesn't exist or has wrong typing.
 * @return: JSON_ERROR_SYSERR: Malformed codec.
 * @return: JSON_ERROR_RANGE:  The value of an integer field was too large. */
typedef __ATTR_NONNULL_T((1, 2, 3)) int
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_DECODE)(struct json_parser *__restrict __parser,
                                          void const *__restrict __codec,
                                          void *__restrict __dst,
                                          void const *const *__ext);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1, 2, 3)) int
__NOTHROW_NCX(LIBJSON_CC json_decode)(struct json_parser *__restrict __parser,
                                      void const *__restrict __codec,
                                      void *__restrict __dst,
                                      void const *const *__ext);
#endif /* LIBJSON_WANT_PROTOTYPES */


#endif /* __CC__ */

__DECL_END

#endif /* !_LIBJSON_GENERATOR_H */
