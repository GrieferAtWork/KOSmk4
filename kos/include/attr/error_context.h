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
/* (#) Portability: libattr (/include/error_context.h) */
#ifndef _ATTR_ERROR_CONTEXT_H
#define _ATTR_ERROR_CONTEXT_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __CC__
__DECL_BEGIN

struct error_context {
	/* [0..1] Error message handler */
	void (__LIBKCALL *error)(struct error_context *__ec, char const *__fmt, ...);
	/* [0..1] Path quoting function */
	char const *(__LIBKCALL *quote)(struct error_context *__ec, char const *__path);
	/* [0..1] Release return value of `quote' */
	void (__LIBKCALL *quote_free)(struct error_context *__ec, char const *__quoted_path);
};

#define __attr_error(ctx, ...) \
	(((ctx) && (ctx)->error) ? (*(ctx)->error)(ctx, __VA_ARGS__) : (void)0)
#define __attr_quote(ctx, path) \
	(((ctx) && (ctx)->quote) ? (*(ctx)->quote)((ctx), (path)) : (path))
#define __attr_quote_free(ctx, quoted_path) \
	(((ctx) && (ctx)->quote_free) ? (*(ctx)->quote_free)(ctx, quoted_path) : (void)0)

#ifdef ERROR_CONTEXT_MACROS
#define error(ctx, ...)              __attr_error(ctx, __VA_ARGS__)
#define quote(ctx, path)             __attr_quote(ctx, path)
#define quote_free(ctx, quoted_path) __attr_quote_free(ctx, quoted_path)
#endif /* ERROR_CONTEXT_MACROS */

__DECL_END
#endif /* __CC__ */

#endif /* !_ATTR_ERROR_CONTEXT_H */
