/* HASH CRC-32:0x66fa143e */
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
#ifndef GUARD_LIBC_AUTO_DYN_STRING_C
#define GUARD_LIBC_AUTO_DYN_STRING_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "dyn-string.h"
#include "../user/libiberty.h"
#include "../user/malloc.h"
#include "../user/stdlib.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <features.h>
#include <bits/crt/dyn-string.h>
/* >> dyn_string_init(3)
 * Initialize a given `struct dyn_string'
 * @param: min_chars: Minimum value for `self->allocated'
 * @return: 1: Always returns `1' */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_dyn_string_init)(struct dyn_string *self,
                                           __STDC_INT_AS_SIZE_T min_chars) {
	if (min_chars == 0)
		min_chars = 1;
	self->s = (char *)libc_xmalloc((size_t)min_chars * sizeof(char));
#ifndef __OPTIMIZE_SIZE__
	min_chars = (__STDC_INT_AS_SIZE_T)(libc_malloc_usable_size(self->s) / sizeof(char));
#endif /* !__OPTIMIZE_SIZE__ */
	self->allocated = min_chars;
	self->length    = 0;
	self->s[0]      = '\0';
	return 1;
}
#include <features.h>
#include <bits/crt/dyn-string.h>
/* >> dyn_string_init(3)
 * Allocate+initialize a new `dyn_string_t'
 * @param: min_chars: Minimum value for `return->allocated'
 * @return: * : The new dyn_string object (free using `dyn_string_delete(3)')
 *              -> uses `xmalloc(3)', so no error-return-value */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_RETNONNULL struct dyn_string *
NOTHROW_NCX(LIBCCALL libc_dyn_string_new)(__STDC_INT_AS_SIZE_T min_chars) {
	struct dyn_string *result;
	result = (struct dyn_string *)libc_xmalloc(sizeof(struct dyn_string));
	libc_dyn_string_init(result, min_chars);
	return result;
}
#include <bits/crt/dyn-string.h>
/* >> dyn_string_delete(3)
 * Delete a `dyn_string_t' previously allocated by `dyn_string_new(3)' */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_INOUT(1) void
NOTHROW_NCX(LIBCCALL libc_dyn_string_delete)(struct dyn_string *self) {
	libc_free(self->s);
	libc_free(self);
}
#include <bits/crt/dyn-string.h>
/* >> dyn_string_release(3)
 * Steal the  internal string  buffer  of `self'  and  free(self)
 * The returned pointer must be `free(3)'d once no longer needed. */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_RETNONNULL ATTR_INOUT(1) char *
NOTHROW_NCX(LIBCCALL libc_dyn_string_release)(struct dyn_string *self) {
	char *result = self->s;
#ifndef __OPTIMIZE_SIZE__
	result = (char *)libc_realloc(result, (self->length + 1) * sizeof(char));
	if unlikely(!result)
		result = self->s;
#endif /* !__OPTIMIZE_SIZE__ */
	libc_free(self);
	return result;
}
#include <features.h>
#include <bits/crt/dyn-string.h>
/* >> dyn_string_release(3)
 * Ensure that  `self' has  sufficient  space for  at  least
 * `min_chars' total characters (excluding the trailing NUL)
 * @return: * : Always re-returns `self'
 *              -> uses `xmalloc(3)', so no error-return-value */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_RETNONNULL ATTR_INOUT(1) struct dyn_string *
NOTHROW_NCX(LIBCCALL libc_dyn_string_resize)(struct dyn_string *self,
                                             __STDC_INT_AS_SIZE_T min_chars) {
	char *newbuf;
	size_t newalloc;
	++min_chars; /* +1 for trailing NUL */
	if ((size_t)self->allocated >= (size_t)min_chars)
		return self; /* Already enough space. */
	newalloc = (size_t)self->allocated;
	do {
		newalloc = (newalloc << 1) | 1;
	} while (newalloc < (size_t)min_chars);
	newbuf = (char *)libc_realloc(self->s, newalloc * sizeof(char));
	if (!newbuf) {
		newalloc = min_chars;
		newbuf = (char *)libc_xrealloc(self->s, newalloc * sizeof(char));
	}
#ifndef __OPTIMIZE_SIZE__
	newalloc = libc_malloc_usable_size(newbuf) / sizeof(char);
#endif /* !__OPTIMIZE_SIZE__ */
	self->allocated = (__STDC_INT_AS_SIZE_T)newalloc;
	self->s         = newbuf;
	return self;
}
#include <bits/crt/dyn-string.h>
/* >> dyn_string_clear(3)
 * Set the length of `self' to `0' */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_INOUT(1) void
NOTHROW_NCX(LIBCCALL libc_dyn_string_clear)(struct dyn_string *self) {
	self->length = 0;
	self->s[0]   = '\0';
}
#include <features.h>
#include <bits/crt/dyn-string.h>
/* >> dyn_string_copy(3)
 * Assign `src' to `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_IN(2) ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_dyn_string_copy)(struct dyn_string *dst,
                                           struct dyn_string __KOS_FIXED_CONST *src) {
	dst = libc_dyn_string_resize(dst, src->length);
	dst->length = src->length;
	libc_memcpyc(dst->s, src->s, src->length + 1, sizeof(char));
	return 1;
}
#include <bits/crt/dyn-string.h>
/* >> dyn_string_copy_cstr(3)
 * Assign   `src'   to  `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_IN(2) ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_dyn_string_copy_cstr)(struct dyn_string *dst,
                                                char const *src) {
	size_t srclen = libc_strlen(src);
	dst = libc_dyn_string_resize(dst, srclen);
	dst->length = srclen;
	libc_memcpyc(dst->s, src, srclen + 1, sizeof(char));
	return 1;
}
#include <features.h>
#include <bits/crt/dyn-string.h>
/* >> dyn_string_prepend(3)
 * Insert `src' at the start of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_IN(2) ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_dyn_string_prepend)(struct dyn_string *dst,
                                              struct dyn_string __KOS_FIXED_CONST *src) {
	return libc_dyn_string_insert(dst, 0, src);
}
#include <bits/crt/dyn-string.h>
/* >> dyn_string_prepend_cstr(3)
 * Insert `src' at the start of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_IN(2) ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_dyn_string_prepend_cstr)(struct dyn_string *dst,
                                                   char const *src) {
	return libc_dyn_string_insert_cstr(dst, 0, src);
}
#include <features.h>
#include <bits/crt/dyn-string.h>
#include <hybrid/__assert.h>
/* >> dyn_string_insert(3)
 * Insert `src' into `dst' at position `index'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_IN(3) ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_dyn_string_insert)(struct dyn_string *dst,
                                             __STDC_INT_AS_SIZE_T index,
                                             struct dyn_string __KOS_FIXED_CONST *src) {
	__hybrid_assert((size_t)index <= dst->length);
	dst = libc_dyn_string_resize(dst, dst->length + src->length);
	/* Make space for the new string. */
	libc_memmoveupc(dst->s + index + src->length,
	           dst->s + index,
	           (dst->length - index) + 1, /* +1 for trailing NUL */
	           sizeof(char));
	/* Insert the source string. */
	libc_memcpyc(dst->s + index, src->s, src->length, sizeof(char));
	return 1;
}
#include <features.h>
#include <bits/crt/dyn-string.h>
/* >> dyn_string_insert_cstr(3)
 * Insert `src' into `dst' at position `index'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_IN(3) ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_dyn_string_insert_cstr)(struct dyn_string *dst,
                                                  __STDC_INT_AS_SIZE_T index,
                                                  char const *src) {
	struct dyn_string fakesrc;
	fakesrc.s      = (char *)src;
	fakesrc.length = libc_strlen(src);
	return libc_dyn_string_insert(dst, index, &fakesrc);
}
#include <features.h>
#include <bits/crt/dyn-string.h>
/* >> dyn_string_insert_char(3)
 * Insert `ch' into `dst' at position `index'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_dyn_string_insert_char)(struct dyn_string *dst,
                                                  __STDC_INT_AS_SIZE_T index,
                                                  int ch) {
	char chstr[1];
	struct dyn_string fakesrc;
	chstr[0] = (char)(unsigned char)(unsigned int)ch;
	fakesrc.s      = chstr;
	fakesrc.length = 1;
	return libc_dyn_string_insert(dst, index, &fakesrc);
}
#include <features.h>
#include <bits/crt/dyn-string.h>
/* >> dyn_string_append(3)
 * Append `src' to the end of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_IN(2) ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_dyn_string_append)(struct dyn_string *dst,
                                             struct dyn_string __KOS_FIXED_CONST *src) {
	return libc_dyn_string_insert(dst, dst->length, src);
}
#include <bits/crt/dyn-string.h>
/* >> dyn_string_append_cstr(3)
 * Append `src' to the end of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_IN(2) ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_dyn_string_append_cstr)(struct dyn_string *dst,
                                                  char const *src) {
	return libc_dyn_string_insert_cstr(dst, dst->length, src);
}
#include <bits/crt/dyn-string.h>
/* >> dyn_string_append_char(3)
 * Append `ch' to the end of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_dyn_string_append_char)(struct dyn_string *dst,
                                                  int ch) {
	return libc_dyn_string_insert_char(dst, dst->length, ch);
}
#include <features.h>
#include <bits/crt/dyn-string.h>
#include <hybrid/__assert.h>
/* >> dyn_string_substring(3)
 * Assign  the substring `src[start:end]'  to `dst'. Note that
 * the given indices _must_ be properly ordered, and in-range!
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_IN(2) ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_dyn_string_substring)(struct dyn_string *dst,
                                                struct dyn_string __KOS_FIXED_CONST *src,
                                                __STDC_INT_AS_SIZE_T start,
                                                __STDC_INT_AS_SIZE_T end) {
	struct dyn_string fakesrc;
	__hybrid_assert((size_t)start <= (size_t)end);
	__hybrid_assert((size_t)end <= (size_t)src->length);
	fakesrc.s      = src->s + (size_t)start;
	fakesrc.length = (__STDC_INT_AS_SIZE_T)((size_t)end - (size_t)start);
	return libc_dyn_string_copy(dst, &fakesrc);
}
#include <features.h>
#include <bits/crt/dyn-string.h>
/* >> dyn_string_eq(3)
 * Return `1' if the contents of the given strings are equal; `0' otherwise.
 * @return: 0 : Strings differ
 * @return: 1 : Strings are identical */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_dyn_string_eq)(struct dyn_string __KOS_FIXED_CONST *lhs,
                                         struct dyn_string __KOS_FIXED_CONST *rhs) {
	if (lhs->length != rhs->length)
		return 0;
	return libc_bcmpc(lhs->s, rhs->s, lhs->length, sizeof(char)) == 0 ? 1 : 0;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(dyn_string_init, libc_dyn_string_init);
DEFINE_PUBLIC_ALIAS(dyn_string_new, libc_dyn_string_new);
DEFINE_PUBLIC_ALIAS(dyn_string_delete, libc_dyn_string_delete);
DEFINE_PUBLIC_ALIAS(dyn_string_release, libc_dyn_string_release);
DEFINE_PUBLIC_ALIAS(dyn_string_resize, libc_dyn_string_resize);
DEFINE_PUBLIC_ALIAS(dyn_string_clear, libc_dyn_string_clear);
DEFINE_PUBLIC_ALIAS(dyn_string_copy, libc_dyn_string_copy);
DEFINE_PUBLIC_ALIAS(dyn_string_copy_cstr, libc_dyn_string_copy_cstr);
DEFINE_PUBLIC_ALIAS(dyn_string_prepend, libc_dyn_string_prepend);
DEFINE_PUBLIC_ALIAS(dyn_string_prepend_cstr, libc_dyn_string_prepend_cstr);
DEFINE_PUBLIC_ALIAS(dyn_string_insert, libc_dyn_string_insert);
DEFINE_PUBLIC_ALIAS(dyn_string_insert_cstr, libc_dyn_string_insert_cstr);
DEFINE_PUBLIC_ALIAS(dyn_string_insert_char, libc_dyn_string_insert_char);
DEFINE_PUBLIC_ALIAS(dyn_string_append, libc_dyn_string_append);
DEFINE_PUBLIC_ALIAS(dyn_string_append_cstr, libc_dyn_string_append_cstr);
DEFINE_PUBLIC_ALIAS(dyn_string_append_char, libc_dyn_string_append_char);
DEFINE_PUBLIC_ALIAS(dyn_string_substring, libc_dyn_string_substring);
DEFINE_PUBLIC_ALIAS(dyn_string_eq, libc_dyn_string_eq);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_DYN_STRING_C */
