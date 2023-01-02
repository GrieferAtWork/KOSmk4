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
#ifndef _LIBJSON_WRITER_H
#define _LIBJSON_WRITER_H 1

#include "api.h"
/**/

#include <__stdinc.h>

#include <bits/crt/format-printer.h>
#include <bits/types.h>

/* Json writer example usage:
 *
 * >> struct json_writer writer;
 * >> json_writer_init(&writer, printer, arg, format);
 * >> json_writer_beginobject(&writer);
 * >>     json_writer_addfield(&writer, "foo", 3);
 * >>     json_writer_beginarray(&writer);
 * >>         json_writer_putnumber(&writer, 10);
 * >>         json_writer_putnumber(&writer, 20);
 * >>         json_writer_putnumber(&writer, 30);
 * >>     json_writer_endarray(&writer);
 * >>     json_writer_addfield(&writer, "bar", 3);
 * >>     json_writer_putnull(&writer);
 * >> json_writer_endobject(&writer);
 *
 * Output (format == JSON_WRITER_FORMAT_COMPACT):
 * >> {"foo":[10,20,30],"bar":null}
 *
 * Output (format == JSON_WRITER_FORMAT_PRETTY):
 * >> {
 * >> 	"foo": [
 * >> 		10,
 * >> 		20,
 * >> 		30
 * >> 	],
 * >> 	"bar": null
 * >> }
 */

__DECL_BEGIN

#define JSON_WRITER_FORMAT_COMPACT 0x0000 /* Output compact data. */
#define JSON_WRITER_FORMAT_PRETTY  0x0001 /* Output pretty, human-readable data. */

#define JSON_WRITER_STATE_INITIAL  0x0000 /* Initial writer state (set this one during init) */
#define JSON_WRITER_STATE_BADUSAGE 0x0001 /* Exit state: Bad usage of writer functions. */
#define JSON_WRITER_STATE_SIBLING  0x0002 /* Sibling objects already exist (a `,' needs to be printed before values) */
#define JSON_WRITER_STATE_ONFIELD  0x0003 /* After an object field prefix. */


#ifdef __CC__
struct json_writer {
	__pformatprinter jw_printer; /* [1..1] Format printer */
	void            *jw_arg;     /* [?..?] Argument for `jw_printer' */
	__ssize_t        jw_result;  /* Sum of all calls to `jw_printer'
	                              * When negative, `jw_printer' will no longer be invoked.
	                              * When an invocation returns negative, that number is written to this field. */
	unsigned int     jw_format;  /* Output format (One of `JSON_WRITER_FORMAT_*') */
	unsigned int     jw_state;   /* Writer state (One of `JSON_WRITER_STATE_*') */
	unsigned int     jw_depth;   /* Object / array depth */
};

/* Initialize a given json writer
 * @param: format: One of `JSON_WRITER_FORMAT_*' */
#ifdef __INTELLISENSE__
void (json_writer_init)(struct json_writer *__restrict __self,
                        __pformatprinter __printer, void *__arg,
                        unsigned int __format);
#else /* __INTELLISENSE__ */
#define json_writer_init(self, printer, arg, format) \
	((self)->jw_printer = (printer),                 \
	 (self)->jw_arg     = (arg),                     \
	 (self)->jw_result  = 0,                         \
	 (self)->jw_format  = (format),                  \
	 (self)->jw_state   = JSON_WRITER_STATE_INITIAL, \
	 (self)->jw_depth   = 0)
#endif /* !__INTELLISENSE__ */

/* Json writer helper functions.
 * Note all of these have the same return value convention:
 * @return:  0: Success
 * @return: -1: Error: `self->jw_result' has a negative value when the function was called.
 * @return: -1: Error: An invocation of the `self->jw_printer' returned a negative value.
 * @return: -2: Error: Invalid usage during this, or during an earlier call. */
typedef __ATTR_NONNULL_T((1)) int (LIBJSON_CC *PJSON_WRITER_BEGINOBJECT)(struct json_writer *__restrict __self);
typedef __ATTR_NONNULL_T((1)) int (LIBJSON_CC *PJSON_WRITER_BEGINARRAY)(struct json_writer *__restrict __self);
typedef __ATTR_NONNULL_T((1)) int (LIBJSON_CC *PJSON_WRITER_ENDOBJECT)(struct json_writer *__restrict __self);
typedef __ATTR_NONNULL_T((1)) int (LIBJSON_CC *PJSON_WRITER_ENDARRAY)(struct json_writer *__restrict __self);
typedef __ATTR_NONNULL_T((1, 2)) int (LIBJSON_CC *PJSON_WRITER_ADDFIELD)(struct json_writer *__restrict __self, /*utf-8*/ char const *__restrict __key, __size_t __keylen);
typedef __ATTR_NONNULL_T((1, 2)) int (LIBJSON_CC *PJSON_WRITER_PUTSTRING)(struct json_writer *__restrict __self, /*utf-8*/ char const *__restrict __str, __size_t __len);
typedef __ATTR_NONNULL_T((1)) int (LIBJSON_CC *PJSON_WRITER_PUTNUMBER)(struct json_writer *__restrict __self, __intptr_t __val);
typedef __ATTR_NONNULL_T((1)) int (LIBJSON_CC *PJSON_WRITER_PUTINT64)(struct json_writer *__restrict __self, __int64_t __val);
typedef __ATTR_NONNULL_T((1)) int (LIBJSON_CC *PJSON_WRITER_PUTUINT64)(struct json_writer *__restrict __self, __uint64_t __val);
#ifndef __NO_FPU
typedef __ATTR_NONNULL_T((1)) int (LIBJSON_CC *PJSON_WRITER_PUTFLOAT)(struct json_writer *__restrict __self, double __val);
#endif /* !__NO_FPU */
typedef __ATTR_NONNULL_T((1)) int (LIBJSON_CC *PJSON_WRITER_PUTBOOL)(struct json_writer *__restrict __self, __BOOL __val);
typedef __ATTR_NONNULL_T((1)) int (LIBJSON_CC *PJSON_WRITER_PUTNULL)(struct json_writer *__restrict __self);
#ifdef LIBJSON_WANT_PROTOTYPES
LIBJSON_DECL __ATTR_NONNULL((1)) int LIBJSON_CC json_writer_beginobject(struct json_writer *__restrict __self);
LIBJSON_DECL __ATTR_NONNULL((1)) int LIBJSON_CC json_writer_beginarray(struct json_writer *__restrict __self);
LIBJSON_DECL __ATTR_NONNULL((1)) int LIBJSON_CC json_writer_endobject(struct json_writer *__restrict __self);
LIBJSON_DECL __ATTR_NONNULL((1)) int LIBJSON_CC json_writer_endarray(struct json_writer *__restrict __self);
LIBJSON_DECL __ATTR_NONNULL((1, 2)) int LIBJSON_CC json_writer_addfield(struct json_writer *__restrict __self, /*utf-8*/ char const *__restrict __key, __size_t __keylen);
LIBJSON_DECL __ATTR_NONNULL((1, 2)) int LIBJSON_CC json_writer_putstring(struct json_writer *__restrict __self, /*utf-8*/ char const *__restrict __str, __size_t __len);
LIBJSON_DECL __ATTR_NONNULL((1)) int LIBJSON_CC json_writer_putnumber(struct json_writer *__restrict __self, __intptr_t __val);
LIBJSON_DECL __ATTR_NONNULL((1)) int LIBJSON_CC json_writer_putint64(struct json_writer *__restrict __self, __int64_t __val);
LIBJSON_DECL __ATTR_NONNULL((1)) int LIBJSON_CC json_writer_putuint64(struct json_writer *__restrict __self, __uint64_t __val);
#ifndef __NO_FPU
LIBJSON_DECL __ATTR_NONNULL((1)) int LIBJSON_CC json_writer_putfloat(struct json_writer *__restrict __self, double __val);
#endif /* !__NO_FPU */
LIBJSON_DECL __ATTR_NONNULL((1)) int LIBJSON_CC json_writer_putbool(struct json_writer *__restrict __self, __BOOL __val);
LIBJSON_DECL __ATTR_NONNULL((1)) int LIBJSON_CC json_writer_putnull(struct json_writer *__restrict __self);
#endif /* LIBJSON_WANT_PROTOTYPES */

#endif /* __CC__ */

__DECL_END

#endif /* !_LIBJSON_WRITER_H */
