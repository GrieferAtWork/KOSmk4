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
#ifndef _LIBJSON_PARSER_H
#define _LIBJSON_PARSER_H 1

#include "api.h"
/**/

#ifndef LIBJSON_NO_SYSTEM_INCLUDES
#include <__stdinc.h>

#include <bits/crt/format-printer.h>
#include <bits/types.h>
#endif /* !LIBJSON_NO_SYSTEM_INCLUDES */

/* JSON parser example usage (without error checking):
 * >> struct json_parser parser;
 * >> char const *input = "{\"bar\":\"baz\",\"foo\":[10,20,30]}";
 * >> json_parser_init(&parser, input, strend(input));
 * >> json_parser_enterobject(&parser);
 * >> json_parser_findkey(&parser, "foo", 3);
 * >> json_parser_enterarray(&parser);
 * >> json_parser_findindex(&parser, 1);
 * >> intptr_t value;
 * >> json_parser_getnumber(&parser, &value);
 * >> printf("value = %Id\n", value); // `value = 20'
 */

__DECL_BEGIN


/* JSON parser error codes. */
#define JSON_ERROR_OK       0  /* Success */
#define JSON_ERROR_SYNTAX (-1) /* Syntax error. */
#define JSON_ERROR_NOOBJ  (-2) /* Entity does not exist */
#define JSON_ERROR_SYSERR (-3) /* Other error (context-specific) */
#define JSON_ERROR_RANGE  (-4) /* Integer under-/overflow */
#define JSON_ERROR_NOTEQ  JSON_ERROR_SYSERR /* Strings are not equal */
#define JSON_ERROR_EOF    JSON_ERROR_NOOBJ  /* End-of-file has been reached */

/* JSON encoding values. */
#define JSON_ENCODING_UTF8    0x0000 /* utf-8 */
#define JSON_ENCODING_UTF16LE 0x0001 /* utf-16 (Little endian) */
#define JSON_ENCODING_UTF32LE 0x0002 /* utf-32 (Little endian) */
#define JSON_ENCODING_UTF16BE 0x0003 /* utf-16 (Big endian) */
#define JSON_ENCODING_UTF32BE 0x0004 /* utf-32 (Big endian) */

/* JSON parser tokens. */
#define JSON_PARSER_EOF       0    /* End-of-file */
#define JSON_PARSER_ENDOBJECT '}'  /* } */
#define JSON_PARSER_ENDARRAY  ']'  /* ] */
#define JSON_PARSER_STRING    '\"' /* "foo" */
#define JSON_PARSER_NUMBER    '0'  /* 1234 */
#define JSON_PARSER_COLON     ':'  /* : */
#define JSON_PARSER_COMMA     ','  /* , */
#define JSON_PARSER_OBJECT    '{'  /* { */
#define JSON_PARSER_ARRAY     '['  /* [ */
#define JSON_PARSER_NULL      'n'  /* null */
#define JSON_PARSER_TRUE      't'  /* true */
#define JSON_PARSER_FALSE     'f'  /* false */


#ifdef __CC__
struct json_parser {
	char const  *jp_start;    /* Input data start */
	char const  *jp_end;      /* Input data end */
	char const  *jp_pos;      /* Current position within input data */
	unsigned int jp_encoding; /* [valid_if(jp_pos > jp_start)] Input encoding (One of `JSON_ENCODING_*')
	                           * The used  encoding is  automatically  determined when  parsing  starts. */
	/* NOTE: You may have noticed that this parser  is stateless, that is: it doesn't  keep
	 *       track  of a stack  of object vs. array  scopes, meaning that  when any kind of
	 *       scope is exited,  the token used  for this (whether  it be `]'  or `}')  isn't
	 *       actually taken into consideration, leading to the consequence that this parser
	 *       may accept JSON that would normally be considered to be malformed:
	 * >> {
	 * >>     "name": "demo",
	 * >>     "ids": [10, 20, 30},
	 * >>     "meta": {
	 * >>         "type": "demo_type"
	 * >>     ]
	 * >> ]
	 * As such, this  is a  known bug that  can be  considered as wont-fix,  as doing  so
	 * would  involve  having to  introduce  a heap-based  approach  to keeping  track of
	 * active JSON scopes, when  the dependency on a  heap wouldn't (and isn't)  actually
	 * a  requirement for proper execution. (Not depending  on a heap allows this library
	 * to function entirely portable, as well as be entirely freestanding with absolutely
	 * 0 hard ABI/library dependencies)
	 * However, when using `json_decode()' for parsing JSON text, this problem doesn't
	 * surface, as that function uses the C-stack itself to keep track of the stack of
	 * array/object scopes, meaning that it is actually able to detect such errors.
	 */
};

#define json_parser_fini(self) (void)0 /* nothing to do here (but still defined for forward-compatibility) */

/* Initialize a JSON parser with the given piece of in-memory JSON.
 * NOTE: This function automatically detects  the encoding (one of  `JSON_ENCODING_*')
 *       of the given input, as  specified by the JSON  specs, meaning you don't  have
 *       to concern yourself with the details on how to supply input to this function.
 * @param: start: Pointer to the start of JSON input data (usually points to a c-string)
 * @param: end:   Pointer to the first byte past the last piece of JSON input data (usually
 *                equal  to `strend(start)', though note that the input string doesn't need
 *                to be NUL-terminated. - Only bytes `x' with `x >= start && x < end'  will
 *                ever be accessed) */
typedef __ATTR_NONNULL_T((1, 2, 3)) void
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_INIT)(struct json_parser *__restrict __self,
                                               void const *__start, void const *__end);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1, 2, 3)) void
__NOTHROW_NCX(LIBJSON_CC json_parser_init)(struct json_parser *__restrict __self,
                                           void const *__start, void const *__end);
#endif /* LIBJSON_WANT_PROTOTYPES */

/* Yield to the current token and advance to the next one (*<ptr>++)
 * @return: JSON_PARSER_*:     The previously selected token (the parser now points at its end)
 * @return: JSON_ERROR_EOF:    The end of the input file has been reached.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
typedef __ATTR_NONNULL_T((1)) int
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_YIELD)(struct json_parser *__restrict __self);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(LIBJSON_CC json_parser_yield)(struct json_parser *__restrict __self);
#endif /* LIBJSON_WANT_PROTOTYPES */

/* Yield to the previous token and return it (*--<ptr>)
 * @return: JSON_PARSER_*:     The now selected token (The parser is now located at the previous token)
 * @return: JSON_ERROR_EOF:    The start of the input file had already been reached.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
typedef __ATTR_NONNULL_T((1)) int
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_UNYIELD)(struct json_parser *__restrict __self);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(LIBJSON_CC json_parser_unyield)(struct json_parser *__restrict __self);
#endif /* LIBJSON_WANT_PROTOTYPES */

/* Same as `libjson_parser_yield()', but don't actually advance the parser (*<ptr>)
 * @return: JSON_PARSER_*:     The currently selected token
 * @return: JSON_ERROR_EOF:    The end of the input file has been reached.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
typedef __ATTR_NONNULL_T((1)) int
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_PEEKNEXT)(struct json_parser *__restrict __self);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(LIBJSON_CC json_parser_peeknext)(struct json_parser *__restrict __self);
#endif /* LIBJSON_WANT_PROTOTYPES */

/* Same as `libjson_parser_unyield()', but don't actually rewind the parser (*(<ptr> - 1))
 * @return: JSON_PARSER_*:     The previously selected token
 * @return: JSON_ERROR_EOF:    The start of the input file had already been reached.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
typedef __ATTR_NONNULL_T((1)) int
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_PEEKPREV)(struct json_parser *__restrict __self);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(LIBJSON_CC json_parser_peekprev)(struct json_parser *__restrict __self);
#endif /* LIBJSON_WANT_PROTOTYPES */

/* Rewind to the start of the current object/array
 * @return: JSON_PARSER_ARRAY:  The parser now points at the first token following the initial `['.
 * @return: JSON_PARSER_OBJECT: The parser now points at the first token following the initial `{'.
 * @return: JSON_ERROR_SYNTAX:  Syntax error. */
typedef __ATTR_NONNULL_T((1)) int
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_REWIND)(struct json_parser *__restrict __self);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(LIBJSON_CC json_parser_rewind)(struct json_parser *__restrict __self);
#endif /* LIBJSON_WANT_PROTOTYPES */

/* Advance the parser to the next object member or array index
 * @return: JSON_ERROR_OK:    The parser now points at the first token after the `,'
 *                            following   previous   object   memory/array    index.
 *                            Should that token be a `}' or `]',  `JSON_ERROR_NOOBJ'
 *                            will be returned instead.
 * @return: JSON_ERROR_NOOBJ: The end of the current object/array was reached.
 *                            The parser now points at the `}' or `]' following the object/array
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
typedef __ATTR_NONNULL_T((1)) int
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_NEXT)(struct json_parser *__restrict __self);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(LIBJSON_CC json_parser_next)(struct json_parser *__restrict __self);
#endif /* LIBJSON_WANT_PROTOTYPES */

/* Rewind the parser to the previous object member or array index
 * @return: JSON_ERROR_OK:    The parser now points at the start of the previous object member/array index.
 * @return: JSON_ERROR_NOOBJ: The start of the current object/array was reached.
 *                            In this case, the position of the parser depends on `leave_object':
 *                            `leave_object == true':  The   parser   now   points   at   either:
 *                               - The `{' or `[' token if the inner object/array was an array index
 *                               - The start of the member name `"foo":{...}' if the inner
 *                                 object/array was an object member
 *                            `leave_object == false': The  parser  still points  at the  start of
 *                                                     the first member of the inner object/array.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
typedef __ATTR_NONNULL_T((1)) int
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_PREV)(struct json_parser *__restrict __self,
                                               __BOOL __leave_object);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(LIBJSON_CC json_parser_prev)(struct json_parser *__restrict __self,
                                           __BOOL __leave_object);
#endif /* LIBJSON_WANT_PROTOTYPES */

#ifndef LIBJSON_NO_PARSER_ENTER_LEAVE
/* Advance the parser to the first member/index of an object/array
 * @return: JSON_ERROR_OK:    The parser now points at first member/index of the inner object/array.
 * @return: JSON_ERROR_NOOBJ: The parser didn't point at `{' or `[' (its position remains unchanged).
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
typedef __ATTR_NONNULL_T((1)) int __NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_ENTER)(struct json_parser *__restrict __self);
typedef __ATTR_NONNULL_T((1)) int __NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_ENTEROBJECT)(struct json_parser *__restrict __self);
typedef __ATTR_NONNULL_T((1)) int __NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_ENTERARRAY)(struct json_parser *__restrict __self);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1)) int __NOTHROW_NCX(LIBJSON_CC json_parser_enter)(struct json_parser *__restrict __self);
LIBJSON_DECL __ATTR_NONNULL((1)) int __NOTHROW_NCX(LIBJSON_CC json_parser_enterobject)(struct json_parser *__restrict __self);
LIBJSON_DECL __ATTR_NONNULL((1)) int __NOTHROW_NCX(LIBJSON_CC json_parser_enterarray)(struct json_parser *__restrict __self);
#endif /* LIBJSON_WANT_PROTOTYPES */

/* Skip the remainder of the  current object/array and parse  until after the following  `,'
 * If that token doesn't exist, or is followed by another closing token, stop parsing there.
 * @return: JSON_ERROR_OK:  The  parser  now  points at  the  first token  after  the `,'
 *                          following  the previous object. - If that `,' does not exist,
 *                          the parser exists at the `}' or `]' that is taking its place.
 * @return: JSON_ERROR_EOF: The end of the input file has been reached.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
typedef __ATTR_NONNULL_T((1)) int __NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_LEAVE)(struct json_parser *__restrict __self);
typedef __ATTR_NONNULL_T((1)) int __NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_LEAVEOBJECT)(struct json_parser *__restrict __self);
typedef __ATTR_NONNULL_T((1)) int __NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_LEAVEARRAY)(struct json_parser *__restrict __self);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1)) int __NOTHROW_NCX(LIBJSON_CC json_parser_leave)(struct json_parser *__restrict __self);
LIBJSON_DECL __ATTR_NONNULL((1)) int __NOTHROW_NCX(LIBJSON_CC json_parser_leaveobject)(struct json_parser *__restrict __self);
LIBJSON_DECL __ATTR_NONNULL((1)) int __NOTHROW_NCX(LIBJSON_CC json_parser_leavearray)(struct json_parser *__restrict __self);
#endif /* LIBJSON_WANT_PROTOTYPES */
#endif /* !LIBJSON_NO_PARSER_ENTER_LEAVE */


/* Search for the given key within the current object.
 * The given key is searched in both forward, and backward direction, starting
 * at the current parser location. - If  the key exists multiple times, it  is
 * undefined which of these locations will be referenced upon return.
 * @return: JSON_ERROR_OK:     The parser now points after the `:' following the matching key's name.
 * @return: JSON_ERROR_NOOBJ:  The given `key' wasn't found (The position of `self' remains unchanged)
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
typedef __ATTR_NONNULL_T((1, 2)) int
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_FINDKEY)(struct json_parser *__restrict __self,
                                                  /*utf-8*/ char const *__restrict __key,
                                                  __size_t __keylen);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(LIBJSON_CC json_parser_findkey)(struct json_parser *__restrict __self,
                                              /*utf-8*/ char const *__restrict __key,
                                              __size_t __keylen);
#endif /* LIBJSON_WANT_PROTOTYPES */

#ifndef LIBJSON_NO_PARSER_FINDINDEX
/* Goto  the  `index'th'  array element  before  returning `JSON_ERROR_OK'
 * The parser is rewound to the start of the current array before skipping
 * exactly `index' elements, thus causing that element to end up selected.
 * NOTE: If  the intend is  to enumerate array elements,  it is more efficient
 *       to rewind to the start of the array with `json_parser_rewind()', then
 *       proceeding to use `json_parser_next()' to iterate elements.
 * @return: JSON_ERROR_OK:    The parser was now advanced  to the `index'th array  element.
 *                            In this case, the parser points at the start of that element.
 * @return: JSON_ERROR_NOOBJ: The end  of  the array  has  been  reached before,  or  when  `index'
 *                            elements had been skipped. (The position of `self' remains unchanged)
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
typedef __ATTR_NONNULL_T((1)) int
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_FINDINDEX)(struct json_parser *__restrict __self,
                                                    __uintptr_t __index);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(LIBJSON_CC json_parser_findindex)(struct json_parser *__restrict __self,
                                                __uintptr_t __index);
#endif /* LIBJSON_WANT_PROTOTYPES */
#endif /* !LIBJSON_NO_PARSER_FINDINDEX */

/* Check if the current parser token (which should be a string) is equal to `str'
 * @return: JSON_ERROR_OK:     The  previous  token  is  was  a   string  that  was  equal  to   `str'
 *                             In this case the parser now points at the first token after the string.
 * @return: JSON_ERROR_NOTEQ:  The string isn't equal to `str'.
 *                             In this case the parser now points at the first token after the string.
 * @return: JSON_ERROR_NOOBJ:  The parser didn't point at a string. (The position of `self' remains unchanged)
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
typedef __ATTR_NONNULL_T((1, 2)) int
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_EQSTRING)(struct json_parser *__restrict __self,
                                                   /*utf-8*/ char const *__restrict __str,
                                                   __size_t __len);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(LIBJSON_CC json_parser_eqstring)(struct json_parser *__restrict __self,
                                               /*utf-8*/ char const *__restrict __str,
                                               __size_t __len);
#endif /* LIBJSON_WANT_PROTOTYPES */

/* Parse a Json string and print its contents to `printer'
 * @return: JSON_ERROR_OK:     Success. - The sum  of all calls to  `*printer' is stored in  `*pprinter_result'
 *                             In this case the parser points at the first token after an optional trailing `,'
 *                             NOTE: Should the token following the string be a `:', the parser will point at
 *                                   that location instead.
 * @return: JSON_ERROR_NOOBJ:  The  parser  didn't  point at  a  string token.
 *                             In this case the parser didn't change position.
 * @return: JSON_ERROR_SYSERR: An invocation of `printer' returned a negative value (stored in `*pprinter_result').
 *                             In this case  the position  of the parser  is revered  to the start  of the  string.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
typedef __ATTR_NONNULL_T((1, 2, 4)) int
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_PRINTSTRING)(struct json_parser *__restrict __self,
                                                      __pformatprinter __printer, void *__arg,
                                                      __ssize_t *__restrict __pprinter_result);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1, 2, 4)) int
__NOTHROW_NCX(LIBJSON_CC json_parser_printstring)(struct json_parser *__restrict __self,
                                                  __pformatprinter __printer, void *__arg,
                                                  __ssize_t *__restrict __pprinter_result);
#endif /* LIBJSON_WANT_PROTOTYPES */

#ifndef LIBJSON_NO_PARSER_GETSTRING
/* A somewhat hacky variant of `libjson_parser_printstring()', which replaces the source
 * string  in-line (thus  modifying the source  string) with its  utf-8 encoded variant.
 * This is done by re-encoding the string using a special extension syntax token that is
 * specifically designed to be able to hold a NUL-terminated utf-8 string token:
 * BEFORE:  \"foo\\nbar\"
 * AFTER:   \0foo\nbar\0\0
 * NOTE: If the source input uses a multi-byte format, the leading \0's width matches
 *       that format's width, while the remainder of the string always follows  UTF-8
 * NOTE: Another special encoding also exists for an empty string:
 * BEFORE:  \"\"
 * AFTER:   \1\1 -- Additional \1 characters may follow
 * @param: plength: When non-NULL, write the length of the returned string here.
 * @return: * :     A pointer to the start of the inlined utf-8 string
 * @return: NULL:   An error occurred; when `perror` is non-NULL, that error is stored there:
 *                   - JSON_ERROR_NOOBJ:  Parser didn't point at a string object.
 *                   - JSON_ERROR_SYNTAX: Syntax error */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) /*utf-8*/ char *
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_GETSTRING)(struct json_parser *__restrict __self,
                                                    __size_t *__plength, int *__perror);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) /*utf-8*/ char *
__NOTHROW_NCX(LIBJSON_CC json_parser_getstring)(struct json_parser *__restrict __self,
                                                __size_t *__plength, int *__perror);
#endif /* LIBJSON_WANT_PROTOTYPES */
#endif /* !LIBJSON_NO_PARSER_GETSTRING */


#ifndef LIBJSON_NO_PARSER_GETNUMBER
/* Decode a Json number and store its value in `*presult'
 * @return: JSON_ERROR_OK:     Success. - The number is stored in `*presult'
 *                             In this case the parser points at the first token after the number
 * @return: JSON_ERROR_NOOBJ:  The  parser  didn't  point at  a  number token.
 *                             In this case the parser didn't change position.
 * @return: JSON_ERROR_SYNTAX: Syntax error.
 * @return: JSON_ERROR_RANGE:  The encoded value does not fit into the given type.
 *                             NOTE:  Not  returned  by   `json_parser_getfloat()'!
 *                             In this case `*presult' is filled with the truncated
 *                             integer value, and the parser points at the first token after the number */
typedef __ATTR_NONNULL_T((1, 2)) int
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_GETNUMBER)(struct json_parser *__restrict __self,
                                                    __intptr_t *__restrict __presult);
typedef __ATTR_NONNULL_T((1, 2)) int
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_GETINT64)(struct json_parser *__restrict __self,
                                                   __int64_t *__restrict __presult);
typedef __ATTR_NONNULL_T((1, 2)) int
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_GETUINT64)(struct json_parser *__restrict __self,
                                                    __uint64_t *__restrict __presult);
#endif /* !LIBJSON_NO_PARSER_GETNUMBER */
#ifndef LIBJSON_NO_PARSER_GETFLOAT
#ifndef __NO_FPU
typedef __ATTR_NONNULL_T((1, 2)) int
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_GETFLOAT)(struct json_parser *__restrict __self,
                                                   double *__restrict __presult);
#endif /* !__NO_FPU */
#endif /* !LIBJSON_NO_PARSER_GETFLOAT */
#ifdef LIBJSON_WANT_PROTOTYPES
#ifndef LIBJSON_NO_PARSER_GETNUMBER
LIBJSON_DECL __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(LIBJSON_CC json_parser_getnumber)(struct json_parser *__restrict __self,
                                                __intptr_t *__restrict __presult);
LIBJSON_DECL __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(LIBJSON_CC json_parser_getint64)(struct json_parser *__restrict __self,
                                               __int64_t *__restrict __presult);
LIBJSON_DECL __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(LIBJSON_CC json_parser_getuint64)(struct json_parser *__restrict __self,
                                                __uint64_t *__restrict __presult);
#endif /* !LIBJSON_NO_PARSER_GETNUMBER */
#ifndef LIBJSON_NO_PARSER_GETFLOAT
#ifndef __NO_FPU
LIBJSON_DECL __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(LIBJSON_CC json_parser_getfloat)(struct json_parser *__restrict __self,
                                               double *__restrict __presult);
#endif /* !__NO_FPU */
#endif /* !LIBJSON_NO_PARSER_GETFLOAT */
#endif /* LIBJSON_WANT_PROTOTYPES */

#ifndef LIBJSON_NO_PARSER_GETBOOL
/* Decode a Json boolean and store its value in `*presult'
 * @return: JSON_ERROR_OK:     Success. - The value is stored in `*presult'
 *                             In this case the parser points at the first token after an optional trailing `,'
 * @return: JSON_ERROR_NOOBJ:  The  parser didn't point at a true/false token.
 *                             In this case the parser didn't change position.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
typedef __ATTR_NONNULL_T((1, 2)) int
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_GETBOOL)(struct json_parser *__restrict __self,
                                                  __BOOL *__restrict __presult);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(LIBJSON_CC json_parser_getbool)(struct json_parser *__restrict __self,
                                              __BOOL *__restrict __presult);
#endif /* LIBJSON_WANT_PROTOTYPES */
#endif /* !LIBJSON_NO_PARSER_GETBOOL */

#ifndef LIBJSON_NO_PARSER_GETNULL
/* Decode a Json null-value
 * @return: JSON_ERROR_OK:     Success.
 *                             In this case the parser points at the first token after an optional trailing `,'
 * @return: JSON_ERROR_NOOBJ:  The  parser  didn't  point at  a  `null' token.
 *                             In this case the parser didn't change position.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
typedef __ATTR_NONNULL_T((1)) int
__NOTHROW_NCX_T(LIBJSON_CC *PJSON_PARSER_GETNULL)(struct json_parser *__restrict __self);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(LIBJSON_CC json_parser_getnull)(struct json_parser *__restrict __self);
#endif /* LIBJSON_WANT_PROTOTYPES */
#endif /* !LIBJSON_NO_PARSER_GETNULL */

#endif /* __CC__ */



__DECL_END

#endif /* !_LIBJSON_PARSER_H */
