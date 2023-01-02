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
%(c_prefix){
/* (#) Portability: EMX kLIBC (/libc/include/dyn-string.h) */
/* (#) Portability: libiberty (/include/dyn-string.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.libiberty")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/crt/dyn-string.h>
)]%[insert:prefix(
#include <libc/string.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

typedef struct dyn_string *dyn_string_t;

#define dyn_string_length(self)      (self)->length
#define dyn_string_buf(self)         (self)->s
#define dyn_string_compare(lhs, rhs) __libc_strcmp((lhs)->s, (rhs)->s)

/*
 * NOTE: The dyn_string API uses `xmalloc(3)', so there are no out-of-memory errors
 */

}

%[define_c_language_keyword(__KOS_FIXED_CONST)]

@@>> dyn_string_init(3)
@@Initialize a given `struct dyn_string'
@@@param: min_chars: Minimum value for `self->allocated'
@@@return: 1: Always returns `1'
[[decl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[impl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[requires_function(xmalloc)]]
int dyn_string_init([[out]] struct dyn_string *self, __STDC_INT_AS_SIZE_T min_chars) {
	if (min_chars == 0)
		min_chars = 1;
	self->@s@ = (char *)xmalloc((size_t)min_chars * sizeof(char));
@@pp_if $has_function(malloc_usable_size) && !defined(__OPTIMIZE_SIZE__)@@
	min_chars = (__STDC_INT_AS_SIZE_T)(malloc_usable_size(self->@s@) / sizeof(char));
@@pp_endif@@
	self->@allocated@ = min_chars;
	self->@length@    = 0;
	self->@s@[0]      = '\0';
	return 1;
}

@@>> dyn_string_init(3)
@@Allocate+initialize a new `dyn_string_t'
@@@param: min_chars: Minimum value for `return->allocated'
@@@return: * : The new dyn_string object (free using `dyn_string_delete(3)')
@@             -> uses `xmalloc(3)', so no error-return-value
[[nonnull]]
[[decl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[impl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[requires_function(xmalloc, dyn_string_init)]]
struct dyn_string *dyn_string_new(__STDC_INT_AS_SIZE_T min_chars) {
	struct dyn_string *result;
	result = (struct dyn_string *)xmalloc(sizeof(struct dyn_string));
	dyn_string_init(result, min_chars);
	return result;
}


@@>> dyn_string_delete(3)
@@Delete a `dyn_string_t' previously allocated by `dyn_string_new(3)'
[[decl_include("<bits/crt/dyn-string.h>")]]
[[impl_include("<bits/crt/dyn-string.h>")]]
[[requires_function(free)]]
void dyn_string_delete([[inout]] struct dyn_string *self) {
	free(self->@s@);
	free(self);
}

@@>> dyn_string_release(3)
@@Steal the  internal string  buffer  of `self'  and  free(self)
@@The returned pointer must be `free(3)'d once no longer needed.
[[nonnull, decl_include("<bits/crt/dyn-string.h>")]]
[[impl_include("<bits/crt/dyn-string.h>")]]
[[requires_function(free)]]
char *dyn_string_release([[inout]] struct dyn_string *self) {
	char *result = self->@s@;
@@pp_if $has_function(realloc) && !defined(__OPTIMIZE_SIZE__)@@
	result = (char *)realloc(result, (self->@length@ + 1) * sizeof(char));
	if unlikely(!result)
		result = self->@s@;
@@pp_endif@@
	free(self);
	return result;
}

@@>> dyn_string_release(3)
@@Ensure that  `self' has  sufficient  space for  at  least
@@`min_chars' total characters (excluding the trailing NUL)
@@@return: * : Always re-returns `self'
@@             -> uses `xmalloc(3)', so no error-return-value
[[nonnull]]
[[decl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[impl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[requires_function(realloc, xrealloc)]]
struct dyn_string *dyn_string_resize([[inout]] struct dyn_string *self,
                                     __STDC_INT_AS_SIZE_T min_chars) {
	char *newbuf;
	size_t newalloc;
	++min_chars; /* +1 for trailing NUL */
	if ((size_t)self->@allocated@ >= (size_t)min_chars)
		return self; /* Already enough space. */
	newalloc = (size_t)self->@allocated@;
	do {
		newalloc = (newalloc << 1) | 1;
	} while (newalloc < (size_t)min_chars);
	newbuf = (char *)realloc(self->@s@, newalloc * sizeof(char));
	if (!newbuf) {
		newalloc = min_chars;
		newbuf = (char *)xrealloc(self->@s@, newalloc * sizeof(char));
	}
@@pp_if $has_function(malloc_usable_size) && !defined(__OPTIMIZE_SIZE__)@@
	newalloc = malloc_usable_size(newbuf) / sizeof(char);
@@pp_endif@@
	self->@allocated@ = (__STDC_INT_AS_SIZE_T)newalloc;
	self->@s@         = newbuf;
	return self;
}

@@>> dyn_string_clear(3)
@@Set the length of `self' to `0'
[[decl_include("<bits/crt/dyn-string.h>")]]
[[impl_include("<bits/crt/dyn-string.h>")]]
void dyn_string_clear([[inout]] struct dyn_string *self) {
	self->@length@ = 0;
	self->@s@[0]   = '\0';
}


@@>> dyn_string_copy(3)
@@Assign `src' to `dst'
@@@return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value)
[[decl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[impl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[requires_function(dyn_string_resize)]]
int dyn_string_copy([[inout]] struct dyn_string *dst,
                    [[in]] struct dyn_string __KOS_FIXED_CONST *src) {
	dst = dyn_string_resize(dst, src->@length@);
	dst->@length@ = src->@length@;
	memcpyc(dst->@s@, src->@s@, src->@length@ + 1, sizeof(char));
	return 1;
}

@@>> dyn_string_copy_cstr(3)
@@Assign   `src'   to  `dst'
@@@return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value)
[[decl_include("<bits/crt/dyn-string.h>")]]
[[impl_include("<bits/crt/dyn-string.h>")]]
[[requires_function(dyn_string_resize)]]
int dyn_string_copy_cstr([[inout]] struct dyn_string *dst,
                         [[in]] char const *src) {
	size_t srclen = strlen(src);
	dst = dyn_string_resize(dst, srclen);
	dst->@length@ = srclen;
	memcpyc(dst->@s@, src, srclen + 1, sizeof(char));
	return 1;
}

@@>> dyn_string_prepend(3)
@@Insert `src' at the start of `dst'
@@@return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value)
[[decl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[impl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[requires_function(dyn_string_insert)]]
int dyn_string_prepend([[inout]] struct dyn_string *dst,
                       [[in]] struct dyn_string __KOS_FIXED_CONST *src) {
	return dyn_string_insert(dst, 0, src);
}

@@>> dyn_string_prepend_cstr(3)
@@Insert `src' at the start of `dst'
@@@return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value)
[[decl_include("<bits/crt/dyn-string.h>")]]
[[impl_include("<bits/crt/dyn-string.h>")]]
[[requires_function(dyn_string_insert_cstr)]]
int dyn_string_prepend_cstr([[inout]] struct dyn_string *dst,
                            [[in]] char const *src) {
	return dyn_string_insert_cstr(dst, 0, src);
}


@@>> dyn_string_insert(3)
@@Insert `src' into `dst' at position `index'
@@@return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value)
[[decl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[impl_include("<features.h>", "<bits/crt/dyn-string.h>", "<hybrid/__assert.h>")]]
[[requires_function(dyn_string_resize)]]
int dyn_string_insert([[inout]] struct dyn_string *dst, __STDC_INT_AS_SIZE_T index,
                      [[in]] struct dyn_string __KOS_FIXED_CONST *src) {
	__hybrid_assert((size_t)index <= dst->@length@);
	dst = dyn_string_resize(dst, dst->@length@ + src->@length@);
	/* Make space for the new string. */
	memmoveupc(dst->@s@ + index + src->@length@,
	           dst->@s@ + index,
	           (dst->@length@ - index) + 1, /* +1 for trailing NUL */
	           sizeof(char));
	/* Insert the source string. */
	memcpyc(dst->@s@ + index, src->@s@, src->@length@, sizeof(char));
	return 1;
}

@@>> dyn_string_insert_cstr(3)
@@Insert `src' into `dst' at position `index'
@@@return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value)
[[decl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[impl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[requires_function(dyn_string_insert)]]
int dyn_string_insert_cstr([[inout]] struct dyn_string *dst, __STDC_INT_AS_SIZE_T index,
                           [[in]] char const *src) {
	struct dyn_string fakesrc;
	fakesrc.@s@      = (char *)src;
	fakesrc.@length@ = strlen(src);
	return dyn_string_insert(dst, index, &fakesrc);
}

@@>> dyn_string_insert_char(3)
@@Insert `ch' into `dst' at position `index'
@@@return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value)
[[decl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[impl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[requires_function(dyn_string_insert)]]
int dyn_string_insert_char([[inout]] struct dyn_string *dst,
                           __STDC_INT_AS_SIZE_T index, int ch) {
	char chstr[1];
	struct dyn_string fakesrc;
	chstr[0] = (char)(unsigned char)(unsigned int)ch;
	fakesrc.@s@      = chstr;
	fakesrc.@length@ = 1;
	return dyn_string_insert(dst, index, &fakesrc);
}

@@>> dyn_string_append(3)
@@Append `src' to the end of `dst'
@@@return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value)
[[decl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[impl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[requires_function(dyn_string_insert)]]
int dyn_string_append([[inout]] struct dyn_string *dst,
                      [[in]] struct dyn_string __KOS_FIXED_CONST *src) {
	return dyn_string_insert(dst, dst->@length@, src);
}

@@>> dyn_string_append_cstr(3)
@@Append `src' to the end of `dst'
@@@return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value)
[[decl_include("<bits/crt/dyn-string.h>")]]
[[impl_include("<bits/crt/dyn-string.h>")]]
[[requires_function(dyn_string_insert_cstr)]]
int dyn_string_append_cstr([[inout]] struct dyn_string *dst,
                           [[in]] char const *src) {
	return dyn_string_insert_cstr(dst, dst->@length@, src);
}

@@>> dyn_string_append_char(3)
@@Append `ch' to the end of `dst'
@@@return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value)
[[decl_include("<bits/crt/dyn-string.h>")]]
[[impl_include("<bits/crt/dyn-string.h>")]]
[[requires_function(dyn_string_insert_char)]]
int dyn_string_append_char([[inout]] struct dyn_string *dst, int ch) {
	return dyn_string_insert_char(dst, dst->@length@, ch);
}


@@>> dyn_string_substring(3)
@@Assign  the substring `src[start:end]'  to `dst'. Note that
@@the given indices _must_ be properly ordered, and in-range!
@@@return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value)
[[decl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[impl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[impl_include("<hybrid/__assert.h>")]]
[[requires_function(dyn_string_copy)]]
int dyn_string_substring([[inout]] struct dyn_string *dst,
                         [[in]] struct dyn_string __KOS_FIXED_CONST *src,
                         __STDC_INT_AS_SIZE_T start,
                         __STDC_INT_AS_SIZE_T end) {
	struct dyn_string fakesrc;
	__hybrid_assert((size_t)start <= (size_t)end);
	__hybrid_assert((size_t)end <= (size_t)src->@length@);
	fakesrc.@s@      = src->@s@ + (size_t)start;
	fakesrc.@length@ = (__STDC_INT_AS_SIZE_T)((size_t)end - (size_t)start);
	return dyn_string_copy(dst, &fakesrc);
}


@@>> dyn_string_eq(3)
@@Return `1' if the contents of the given strings are equal; `0' otherwise.
@@@return: 0 : Strings differ
@@@return: 1 : Strings are identical
[[pure, wunused]]
[[decl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
[[impl_include("<features.h>", "<bits/crt/dyn-string.h>")]]
int dyn_string_eq([[in]] struct dyn_string __KOS_FIXED_CONST *lhs,
                  [[in]] struct dyn_string __KOS_FIXED_CONST *rhs) {
	if (lhs->@length@ != rhs->@length@)
		return 0;
	return bcmpc(lhs->@s@, rhs->@s@, lhs->@length@, sizeof(char)) == 0 ? 1 : 0;
}


%{

__SYSDECL_END
#endif /* __CC__ */

}
