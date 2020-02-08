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
#ifndef _LIBJSON_GENERATOR_H
#define _LIBJSON_GENERATOR_H 1

#include <__stdinc.h>
#include <__crt.h> /* __NO_FPU */

#include <hybrid/__byteorder.h>
#include <hybrid/typecore.h>

#include "api.h"

__DECL_BEGIN

/* Combination of writer + parser that can be used to define object layout definitions,
 * which can then be used to describe a mapping between json and regular, old C-structs.
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
 *   - JGEN_OPTIONAL (Which itself must be followed by another one of these opcodes, though not `JGEN_OPTIONAL' again)
 *   - JGEN_INTO
 *   - JGEN_TERM
 */
#define JGEN_TERM         0x00 /* Generator terminal indicator. */
#define JGEN_END          0x01 /* End an object or array. */
#define JGEN_BEGINOBJECT  0x02 /* Begin a new object.
                                * Must be followed by one of:
                                *    - JGEN_FIELD
                                */
#define JGEN_BEGINARRAY   0x03 /* Begin a new array.
                                * Must be followed by one of:
                                *    - JGEN_INDEX
                                *    - JGEN_INDEX_REP_OP
                                */
#define JGEN_OPTIONAL     0x04 /* Optional modifier.
                                * When the associated data doesn't exist,
                                * it is zero-initialized during parsing.
                                * Must be followed by one of:
                                *    - JGEN_FIELD
                                *    - JGEN_BEGINOBJECT
                                *    - JGEN_BEGINARRAY
                                *    - JGEN_INDEX(*)
                                */
#define JGEN_FIELD        0x10 /* [+char utf8_c_string[]] Address a named field.
                                * Must be followed by:
                                *    - JGEN_BEGINOBJECT
                                *    - JGEN_BEGINARRAY
                                *    - JGEN_INTO
                                */
#define JGEN_INDEX        0x11 /* Must be followed by:
                                *    - JGEN_BEGINOBJECT
                                *    - JGEN_BEGINARRAY
                                *    - JGEN_INTO
                                */
#define JGEN_INDEX_REP_OP 0x12 /* [+uint16_t count][+uint16_t stride]
                                * Repeat an index operation
                                * Must be followed by:
                                *    - JGEN_BEGINOBJECT
                                *    - JGEN_BEGINARRAY
                                *    - JGEN_INTO
                                */
#define JGEN_INDEX_REP(count, stride) \
	JGEN_INDEX_REP_OP, JGEN_ENCODE_UINT16((count) - 1), JGEN_ENCODE_UINT16(stride)
#define JGEN_INTO         0x13 /* [+uint16_t offset][+uint8_t type]
                                * Must be followed by:
                                *   #1: JSON_OFFSET(*)
                                *   #2: JSON_TYPE_*
                                */


/* Offset parameter generators for `JGEN_INTO' */
#define JSON_OFFSET(value)         JGEN_ENCODE_UINT16(value)
#define JSON_OFFSETOF(type, field) JGEN_ENCODE_UINT16(__builtin_offsetof(type, field))

/* Type parameter generators for `JGEN_INTO' */
#define JSON_TYPE_BOOL                0xe0 /* bool */
#define JSON_TYPE_BOOLBIT(bit)       (0xe0|((bit)&0x7)) /* Boolean bitflag (`*((u8 *)base + offset) ^= 1 << bit') */
#define JSON_TYPE_BOOLFLAG(flag) \
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
#define JSON_TYPE_INLINE_STRING_OP      0xf2 /* [+uint16_t length] utf8[uint16_t] */
#define JSON_TYPE_INLINE_STRING(length) JSON_TYPE_INLINE_STRING_OP, JGEN_ENCODE_UINT16(length)
#define JSON_TYPE_STRING_WITH_LENGTH_OP 0xf9 /* [+uint16_t len_offset] utf8 *str; size_t len; */
#define JSON_TYPE_STRING_WITH_LENGTH(len_offset) JSON_TYPE_STRING_WITH_LENGTH_OP, JGEN_ENCODE_UINT16(len_offset)
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

#define JSON_TYPE_SCHAR        JSON_PRIVATE_STYPEFOR(__SIZEOF_CHAR__)
#define JSON_TYPE_UCHAR        JSON_PRIVATE_UTYPEFOR(__SIZEOF_CHAR__)
#define JSON_TYPE_SHORT        JSON_PRIVATE_STYPEFOR(__SIZEOF_SHORT__)
#define JSON_TYPE_USHORT       JSON_PRIVATE_UTYPEFOR(__SIZEOF_SHORT__)
#define JSON_TYPE_INT          JSON_PRIVATE_STYPEFOR(__SIZEOF_INT__)
#define JSON_TYPE_UINT         JSON_PRIVATE_UTYPEFOR(__SIZEOF_INT__)
#define JSON_TYPE_LONG         JSON_PRIVATE_STYPEFOR(__SIZEOF_LONG__)
#define JSON_TYPE_ULONG        JSON_PRIVATE_UTYPEFOR(__SIZEOF_LONG__)
#define JSON_TYPE_LLONG        JSON_PRIVATE_STYPEFOR(__SIZEOF_LONG_LONG__)
#define JSON_TYPE_ULLONG       JSON_PRIVATE_UTYPEFOR(__SIZEOF_LONG_LONG__)
#define JSON_TYPE_SIZE_T       JSON_PRIVATE_UTYPEFOR(__SIZEOF_SIZE_T__)
#define JSON_TYPE_SSIZE_T      JSON_PRIVATE_STYPEFOR(__SIZEOF_SIZE_T__)
#define JSON_TYPE_INTPTR_T     JSON_PRIVATE_STYPEFOR(__SIZEOF_POINTER__)
#define JSON_TYPE_UINTPTR_T    JSON_PRIVATE_UTYPEFOR(__SIZEOF_POINTER__)
#define JSON_TYPE_INTMAX_T     JSON_PRIVATE_STYPEFOR(__SIZEOF_INTMAX_T__)
#define JSON_TYPE_UINTMAX_T    JSON_PRIVATE_UTYPEFOR(__SIZEOF_INTMAX_T__)

#ifdef __CHAR_UNSIGNED__
#define JSON_TYPE_CHAR   JSON_TYPE_UCHAR
#else /* __CHAR_UNSIGNED__ */
#define JSON_TYPE_CHAR   JSON_TYPE_SCHAR
#endif /* !__CHAR_UNSIGNED__ */




/* Encode a given object `src' as Json, using the given `codec' as generator.
 * @return:  0: Success
 * @return: -1: Error: `writer->jw_result' has a negative value when the function was called.
 * @return: -1: Error: An invocation of the `writer->jw_printer' returned a negative value.
 * @return: -2: Error: Invalid usage during this, or during an earlier call. */
typedef __ATTR_NONNULL((1, 2, 3)) int
(LIBJSON_CC *PJSON_ENCODE)(struct json_writer *__restrict writer,
                           void const *__restrict codec,
                           void const *__restrict src);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1, 2, 3)) int LIBJSON_CC
json_encode(struct json_writer *__restrict writer,
            void const *__restrict codec,
            void const *__restrict src);
#endif /* LIBJSON_WANT_PROTOTYPES */

/* Decode a given object `dst' from Json, using the given `codec' as generator.
 * @return: JSON_ERROR_OK:     Success.
 * @return: JSON_ERROR_SYNTAX: Syntax error.
 * @return: JSON_ERROR_NOOBJ:  A required field doesn't exist or has wrong typing.
 * @return: JSON_ERROR_SYSERR: Malformed codec. */
typedef __ATTR_NONNULL((1, 2, 3)) int
(LIBJSON_CC *PJSON_DECODE)(struct json_parser *__restrict parser,
                           void const *__restrict codec,
                           void *__restrict dst);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1, 2, 3)) int
__NOTHROW_NCX(LIBJSON_CC json_decode)(struct json_parser *__restrict parser,
                                      void const *__restrict codec,
                                      void *__restrict dst);
#endif /* LIBJSON_WANT_PROTOTYPES */


#endif /* __CC__ */

__DECL_END

#endif /* !_LIBJSON_GENERATOR_H */
