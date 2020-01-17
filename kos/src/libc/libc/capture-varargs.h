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
#ifndef GUARD_LIBC_LIBC_CAPTURE_VARARGS_H
#define GUARD_LIBC_LIBC_CAPTURE_VARARGS_H 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <alloca.h>

DECL_BEGIN

#ifdef __CC__

#define CAPTURE_VARARGS_PLUS_ONE(T, vector, args, first)             \
	do {                                                             \
		T *arg;                                                      \
		size_t count = 0;                                            \
		__builtin_va_list copy;                                      \
		__builtin_va_copy(copy, args);                               \
		if (first) {                                                 \
			++count;                                                 \
			while ((arg = __builtin_va_arg(copy, T *)) != NULL)      \
				++count;                                             \
		}                                                            \
		__builtin_va_end(copy);                                      \
		/* Always need to use alloca(), since malloc() might corrupt \
		 * the heap in a vfork() scenario */                         \
		vector    = (T **)alloca((count + 1) * sizeof(T *));         \
		vector[0] = (T *)(first);                                    \
		if (first) {                                                 \
			count = 1;                                               \
			do {                                                     \
				arg = __builtin_va_arg(args, T *);                   \
				vector[count++] = arg;                               \
			} while (arg != NULL);                                   \
		}                                                            \
	} __WHILE0

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_LIBC_LIBC_CAPTURE_VARARGS_H */
