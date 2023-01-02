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
#ifndef GUARD_LIBJSON_PARSER_H
#define GUARD_LIBJSON_PARSER_H 1

#include "api.h"

#include <kos/types.h>

#include <format-printer.h>

#include <libjson/parser.h>

DECL_BEGIN

/* Initialize a json parser with the given piece of in-memory json.
 * NOTE: This function automatically detects  the encoding (one of  `JSON_ENCODING_*')
 *       of the given input, as  specified by the Json  specs, meaning you don't  have
 *       to concern yourself with the details on how to supply input to this function.
 * @param: start: Pointer to the start of json input data (usually points to a c-string)
 * @param: end:   Pointer to the first byte past the last piece of json input data (usually
 *                equal  to `strend(start)', though note that the input string doesn't need
 *                to be NUL-terminated. - Only bytes `x' with `x >= start && x < end'  will
 *                ever be accessed) */
INTDEF NONNULL((1, 2, 3)) void
NOTHROW_NCX(CC libjson_parser_init)(struct json_parser *__restrict self,
                                    void const *start, void const *end);

/* Yield to the current token and advance to the next one (*<ptr>++)
 * @return: JSON_PARSER_*:     The previously selected token (the parser now points at its end)
 * @return: JSON_ERROR_EOF:    The end of the input file has been reached.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTDEF NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_yield)(struct json_parser *__restrict self);

/* Yield to the previous token and return it (*--<ptr>)
 * @return: JSON_PARSER_*:     The now selected token (The parser is now located at the previous token)
 * @return: JSON_ERROR_EOF:    The start of the input file had already been reached.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTDEF NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_unyield)(struct json_parser *__restrict self);

/* Rewind to the start of the current object/array
 * @return: JSON_PARSER_ARRAY:  The parser now points at the first token following the initial `['.
 * @return: JSON_PARSER_OBJECT: The parser now points at the first token following the initial `{'.
 * @return: JSON_ERROR_SYNTAX:  Syntax error. */
INTDEF NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_rewind)(struct json_parser *__restrict self);

/* Advance the parser to the next object member or array index
 * @return: JSON_ERROR_OK:    The parser now points at the first token after the `,'
 *                            following   previous   object   memory/array    index.
 *                            Should that token be a `}' or `]',  `JSON_ERROR_NOOBJ'
 *                            will be returned instead.
 * @return: JSON_ERROR_NOOBJ: The end of the current object/array was reached.
 *                            The parser now points at the `}' or `]' following the object/array
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTDEF NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_next)(struct json_parser *__restrict self);

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
INTDEF NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_prev)(struct json_parser *__restrict self,
                                    bool leave_object);

/* Advance the parser to the next object sibling
 * @return: JSON_ERROR_OK:    The parser now points at first member/index of the inner object/array.
 * @return: JSON_ERROR_NOOBJ: The parser didn't point at `{' or `[' (its position remains unchanged).
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTDEF NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_enter)(struct json_parser *__restrict self);
INTDEF NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_enterobject)(struct json_parser *__restrict self);
INTDEF NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_enterarray)(struct json_parser *__restrict self);

/* Skip the remainder of the  current object/array and parse  until after the following  `,'
 * If that token doesn't exist, or is followed by another closing token, stop parsing there.
 * @return: JSON_ERROR_OK:  The  parser  now  points at  the  first token  after  the `,'
 *                          following  the previous object. - If that `,' does not exist,
 *                          the parser exists at the `}' or `]' that is taking its place.
 * @return: JSON_ERROR_EOF: The end of the input file has been reached.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTDEF NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_leave)(struct json_parser *__restrict self);
INTDEF NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_leaveobject)(struct json_parser *__restrict self);
INTDEF NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_leavearray)(struct json_parser *__restrict self);


/* Returns the current parser state / token type.
 * @return: JSON_PARSER_*: The current parser state.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTDEF NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_state)(struct json_parser *__restrict self);

/* Search for the given key within the current object.
 * The given key is searched in both forward, and backward direction, starting
 * at the current parser location. - If  the key exists multiple times, it  is
 * undefined which of these locations will be referenced upon return.
 * @return: JSON_ERROR_OK:     The parser now points after the `:' following the matching key's name.
 * @return: JSON_ERROR_NOOBJ:  The given `key' wasn't found (The position of `self' remains unchanged)
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTDEF NONNULL((1, 2)) int
NOTHROW_NCX(CC libjson_parser_findkey)(struct json_parser *__restrict self,
                                       /*utf-8*/ char const *__restrict key,
                                       size_t keylen);

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
INTDEF NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_findindex)(struct json_parser *__restrict self,
                                         uintptr_t index);

/* Check if the current parser token (which should be a string) is equal to `str'
 * @return: JSON_ERROR_OK:     The  previous  token  is  was  a   string  that  was  equal  to   `str'
 *                             In this case the parser now points at the first token after the string.
 * @return: JSON_ERROR_NOTEQ:  The string isn't equal to `str'.
 *                             In this case the parser now points at the first token after the string.
 * @return: JSON_ERROR_NOOBJ:  The parser didn't point at a string. (The position of `self' remains unchanged)
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTDEF NONNULL((1, 2)) int
NOTHROW_NCX(CC libjson_parser_eqstring)(struct json_parser *__restrict self,
                                        /*utf-8*/ char const *__restrict str,
                                        size_t len);

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
INTDEF NONNULL((1, 2, 4)) int
NOTHROW_NCX(CC libjson_parser_printstring)(struct json_parser *__restrict self,
                                           pformatprinter printer, void *arg,
                                           ssize_t *__restrict pprinter_result);

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
INTDEF WUNUSED NONNULL((1)) /*utf-8*/ char *
NOTHROW_NCX(CC libjson_parser_getstring)(struct json_parser *__restrict self,
                                         size_t *plength, int *perror);


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
INTDEF NONNULL((1, 2)) int
NOTHROW_NCX(CC libjson_parser_getnumber)(struct json_parser *__restrict self,
                                         intptr_t *__restrict presult);
INTDEF NONNULL((1, 2)) int
NOTHROW_NCX(CC libjson_parser_getint64)(struct json_parser *__restrict self,
                                        int64_t *__restrict presult);
INTDEF NONNULL((1, 2)) int
NOTHROW_NCX(CC libjson_parser_getuint64)(struct json_parser *__restrict self,
                                         uint64_t *__restrict presult);
#ifndef __NO_FPU
INTDEF NONNULL((1, 2)) int
NOTHROW_NCX(CC libjson_parser_getfloat)(struct json_parser *__restrict self,
                                        double *__restrict presult);
#endif /* !__NO_FPU */

/* Decode a Json boolean and store its value in `*presult'
 * @return: JSON_ERROR_OK:     Success. - The value is stored in `*presult'
 *                             In this case the parser points at the first token after an optional trailing `,'
 * @return: JSON_ERROR_NOOBJ:  The  parser didn't point at a true/false token.
 *                             In this case the parser didn't change position.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTDEF NONNULL((1, 2)) int
NOTHROW_NCX(CC libjson_parser_getbool)(struct json_parser *__restrict self,
                                       bool *__restrict presult);

/* Decode a Json null-value
 * @return: JSON_ERROR_OK:     Success.
 *                             In this case the parser points at the first token after an optional trailing `,'
 * @return: JSON_ERROR_NOOBJ:  The  parser  didn't  point at  a  `null' token.
 *                             In this case the parser didn't change position.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTDEF NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_getnull)(struct json_parser *__restrict self);


DECL_END

#endif /* !GUARD_LIBJSON_PARSER_H */
