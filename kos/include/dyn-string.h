/* HASH CRC-32:0x2bbda661 */
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
/* (#) Portability: EMX kLIBC (/libc/include/dyn-string.h) */
/* (#) Portability: libiberty (/include/dyn-string.h) */
#ifndef _DYN_STRING_H
#define _DYN_STRING_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/crt/dyn-string.h>
#include <libc/string.h>

#ifdef __CC__
__SYSDECL_BEGIN

typedef struct dyn_string *dyn_string_t;

#define dyn_string_length(self)      (self)->length
#define dyn_string_buf(self)         (self)->s
#define dyn_string_compare(lhs, rhs) __libc_strcmp((lhs)->s, (rhs)->s)

/*
 * NOTE: The dyn_string API uses `xmalloc(3)', so there are no out-of-memory errors
 */

#ifdef __CRT_HAVE_dyn_string_init
/* >> dyn_string_init(3)
 * Initialize a given `struct dyn_string'
 * @param: min_chars: Minimum value for `self->allocated'
 * @return: 1: Always returns `1' */
__CDECLARE(__ATTR_OUT(1),int,__NOTHROW_NCX,dyn_string_init,(struct dyn_string *__self, __STDC_INT_AS_SIZE_T __min_chars),(__self,__min_chars))
#elif defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
#include <libc/local/dyn-string/dyn_string_init.h>
/* >> dyn_string_init(3)
 * Initialize a given `struct dyn_string'
 * @param: min_chars: Minimum value for `self->allocated'
 * @return: 1: Always returns `1' */
__NAMESPACE_LOCAL_USING_OR_IMPL(dyn_string_init, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL dyn_string_init)(struct dyn_string *__self, __STDC_INT_AS_SIZE_T __min_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dyn_string_init))(__self, __min_chars); })
#endif /* ... */
#ifdef __CRT_HAVE_dyn_string_new
/* >> dyn_string_init(3)
 * Allocate+initialize a new `dyn_string_t'
 * @param: min_chars: Minimum value for `return->allocated'
 * @return: * : The new dyn_string object (free using `dyn_string_delete(3)')
 *              -> uses `xmalloc(3)', so no error-return-value */
__CDECLARE(__ATTR_RETNONNULL,struct dyn_string *,__NOTHROW_NCX,dyn_string_new,(__STDC_INT_AS_SIZE_T __min_chars),(__min_chars))
#elif defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
#include <libc/local/dyn-string/dyn_string_new.h>
/* >> dyn_string_init(3)
 * Allocate+initialize a new `dyn_string_t'
 * @param: min_chars: Minimum value for `return->allocated'
 * @return: * : The new dyn_string object (free using `dyn_string_delete(3)')
 *              -> uses `xmalloc(3)', so no error-return-value */
__NAMESPACE_LOCAL_USING_OR_IMPL(dyn_string_new, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL struct dyn_string *__NOTHROW_NCX(__LIBCCALL dyn_string_new)(__STDC_INT_AS_SIZE_T __min_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dyn_string_new))(__min_chars); })
#endif /* ... */
#ifdef __CRT_HAVE_dyn_string_delete
/* >> dyn_string_delete(3)
 * Delete a `dyn_string_t' previously allocated by `dyn_string_new(3)' */
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,dyn_string_delete,(struct dyn_string *__self),(__self))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#include <libc/local/dyn-string/dyn_string_delete.h>
/* >> dyn_string_delete(3)
 * Delete a `dyn_string_t' previously allocated by `dyn_string_new(3)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(dyn_string_delete, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) void __NOTHROW_NCX(__LIBCCALL dyn_string_delete)(struct dyn_string *__self) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dyn_string_delete))(__self); })
#endif /* ... */
#ifdef __CRT_HAVE_dyn_string_release
/* >> dyn_string_release(3)
 * Steal the  internal string  buffer  of `self'  and  free(self)
 * The returned pointer must be `free(3)'d once no longer needed. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INOUT(1),char *,__NOTHROW_NCX,dyn_string_release,(struct dyn_string *__self),(__self))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#include <libc/local/dyn-string/dyn_string_release.h>
/* >> dyn_string_release(3)
 * Steal the  internal string  buffer  of `self'  and  free(self)
 * The returned pointer must be `free(3)'d once no longer needed. */
__NAMESPACE_LOCAL_USING_OR_IMPL(dyn_string_release, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUT(1) char *__NOTHROW_NCX(__LIBCCALL dyn_string_release)(struct dyn_string *__self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dyn_string_release))(__self); })
#endif /* ... */
#ifdef __CRT_HAVE_dyn_string_resize
/* >> dyn_string_release(3)
 * Ensure that  `self' has  sufficient  space for  at  least
 * `min_chars' total characters (excluding the trailing NUL)
 * @return: * : Always re-returns `self'
 *              -> uses `xmalloc(3)', so no error-return-value */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INOUT(1),struct dyn_string *,__NOTHROW_NCX,dyn_string_resize,(struct dyn_string *__self, __STDC_INT_AS_SIZE_T __min_chars),(__self,__min_chars))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xmalloc_failed))
#include <libc/local/dyn-string/dyn_string_resize.h>
/* >> dyn_string_release(3)
 * Ensure that  `self' has  sufficient  space for  at  least
 * `min_chars' total characters (excluding the trailing NUL)
 * @return: * : Always re-returns `self'
 *              -> uses `xmalloc(3)', so no error-return-value */
__NAMESPACE_LOCAL_USING_OR_IMPL(dyn_string_resize, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUT(1) struct dyn_string *__NOTHROW_NCX(__LIBCCALL dyn_string_resize)(struct dyn_string *__self, __STDC_INT_AS_SIZE_T __min_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dyn_string_resize))(__self, __min_chars); })
#endif /* ... */
#ifdef __CRT_HAVE_dyn_string_clear
/* >> dyn_string_clear(3)
 * Set the length of `self' to `0' */
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,dyn_string_clear,(struct dyn_string *__self),(__self))
#else /* __CRT_HAVE_dyn_string_clear */
#include <libc/local/dyn-string/dyn_string_clear.h>
/* >> dyn_string_clear(3)
 * Set the length of `self' to `0' */
__NAMESPACE_LOCAL_USING_OR_IMPL(dyn_string_clear, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) void __NOTHROW_NCX(__LIBCCALL dyn_string_clear)(struct dyn_string *__self) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dyn_string_clear))(__self); })
#endif /* !__CRT_HAVE_dyn_string_clear */
#ifdef __CRT_HAVE_dyn_string_copy
/* >> dyn_string_copy(3)
 * Assign `src' to `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_NCX,dyn_string_copy,(struct dyn_string *__dst, struct dyn_string __KOS_FIXED_CONST *__src),(__dst,__src))
#elif defined(__CRT_HAVE_dyn_string_resize) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xmalloc_failed)))
#include <libc/local/dyn-string/dyn_string_copy.h>
/* >> dyn_string_copy(3)
 * Assign `src' to `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__NAMESPACE_LOCAL_USING_OR_IMPL(dyn_string_copy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL dyn_string_copy)(struct dyn_string *__dst, struct dyn_string __KOS_FIXED_CONST *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dyn_string_copy))(__dst, __src); })
#endif /* ... */
#ifdef __CRT_HAVE_dyn_string_copy_cstr
/* >> dyn_string_copy_cstr(3)
 * Assign   `src'   to  `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_NCX,dyn_string_copy_cstr,(struct dyn_string *__dst, char const *__src),(__dst,__src))
#elif defined(__CRT_HAVE_dyn_string_resize) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xmalloc_failed)))
#include <libc/local/dyn-string/dyn_string_copy_cstr.h>
/* >> dyn_string_copy_cstr(3)
 * Assign   `src'   to  `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__NAMESPACE_LOCAL_USING_OR_IMPL(dyn_string_copy_cstr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL dyn_string_copy_cstr)(struct dyn_string *__dst, char const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dyn_string_copy_cstr))(__dst, __src); })
#endif /* ... */
#ifdef __CRT_HAVE_dyn_string_prepend
/* >> dyn_string_prepend(3)
 * Insert `src' at the start of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_NCX,dyn_string_prepend,(struct dyn_string *__dst, struct dyn_string __KOS_FIXED_CONST *__src),(__dst,__src))
#elif defined(__CRT_HAVE_dyn_string_insert) || defined(__CRT_HAVE_dyn_string_resize) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xmalloc_failed)))
#include <libc/local/dyn-string/dyn_string_prepend.h>
/* >> dyn_string_prepend(3)
 * Insert `src' at the start of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__NAMESPACE_LOCAL_USING_OR_IMPL(dyn_string_prepend, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL dyn_string_prepend)(struct dyn_string *__dst, struct dyn_string __KOS_FIXED_CONST *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dyn_string_prepend))(__dst, __src); })
#endif /* ... */
#ifdef __CRT_HAVE_dyn_string_prepend_cstr
/* >> dyn_string_prepend_cstr(3)
 * Insert `src' at the start of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_NCX,dyn_string_prepend_cstr,(struct dyn_string *__dst, char const *__src),(__dst,__src))
#elif defined(__CRT_HAVE_dyn_string_insert_cstr) || defined(__CRT_HAVE_dyn_string_insert) || defined(__CRT_HAVE_dyn_string_resize) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xmalloc_failed)))
#include <libc/local/dyn-string/dyn_string_prepend_cstr.h>
/* >> dyn_string_prepend_cstr(3)
 * Insert `src' at the start of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__NAMESPACE_LOCAL_USING_OR_IMPL(dyn_string_prepend_cstr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL dyn_string_prepend_cstr)(struct dyn_string *__dst, char const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dyn_string_prepend_cstr))(__dst, __src); })
#endif /* ... */
#ifdef __CRT_HAVE_dyn_string_insert
/* >> dyn_string_insert(3)
 * Insert `src' into `dst' at position `index'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__CDECLARE(__ATTR_IN(3) __ATTR_INOUT(1),int,__NOTHROW_NCX,dyn_string_insert,(struct dyn_string *__dst, __STDC_INT_AS_SIZE_T __index, struct dyn_string __KOS_FIXED_CONST *__src),(__dst,__index,__src))
#elif defined(__CRT_HAVE_dyn_string_resize) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xmalloc_failed)))
#include <libc/local/dyn-string/dyn_string_insert.h>
/* >> dyn_string_insert(3)
 * Insert `src' into `dst' at position `index'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__NAMESPACE_LOCAL_USING_OR_IMPL(dyn_string_insert, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL dyn_string_insert)(struct dyn_string *__dst, __STDC_INT_AS_SIZE_T __index, struct dyn_string __KOS_FIXED_CONST *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dyn_string_insert))(__dst, __index, __src); })
#endif /* ... */
#ifdef __CRT_HAVE_dyn_string_insert_cstr
/* >> dyn_string_insert_cstr(3)
 * Insert `src' into `dst' at position `index'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__CDECLARE(__ATTR_IN(3) __ATTR_INOUT(1),int,__NOTHROW_NCX,dyn_string_insert_cstr,(struct dyn_string *__dst, __STDC_INT_AS_SIZE_T __index, char const *__src),(__dst,__index,__src))
#elif defined(__CRT_HAVE_dyn_string_insert) || defined(__CRT_HAVE_dyn_string_resize) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xmalloc_failed)))
#include <libc/local/dyn-string/dyn_string_insert_cstr.h>
/* >> dyn_string_insert_cstr(3)
 * Insert `src' into `dst' at position `index'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__NAMESPACE_LOCAL_USING_OR_IMPL(dyn_string_insert_cstr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL dyn_string_insert_cstr)(struct dyn_string *__dst, __STDC_INT_AS_SIZE_T __index, char const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dyn_string_insert_cstr))(__dst, __index, __src); })
#endif /* ... */
#ifdef __CRT_HAVE_dyn_string_insert_char
/* >> dyn_string_insert_char(3)
 * Insert `ch' into `dst' at position `index'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__CDECLARE(__ATTR_INOUT(1),int,__NOTHROW_NCX,dyn_string_insert_char,(struct dyn_string *__dst, __STDC_INT_AS_SIZE_T __index, int __ch),(__dst,__index,__ch))
#elif defined(__CRT_HAVE_dyn_string_insert) || defined(__CRT_HAVE_dyn_string_resize) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xmalloc_failed)))
#include <libc/local/dyn-string/dyn_string_insert_char.h>
/* >> dyn_string_insert_char(3)
 * Insert `ch' into `dst' at position `index'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__NAMESPACE_LOCAL_USING_OR_IMPL(dyn_string_insert_char, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL dyn_string_insert_char)(struct dyn_string *__dst, __STDC_INT_AS_SIZE_T __index, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dyn_string_insert_char))(__dst, __index, __ch); })
#endif /* ... */
#ifdef __CRT_HAVE_dyn_string_append
/* >> dyn_string_append(3)
 * Append `src' to the end of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_NCX,dyn_string_append,(struct dyn_string *__dst, struct dyn_string __KOS_FIXED_CONST *__src),(__dst,__src))
#elif defined(__CRT_HAVE_dyn_string_insert) || defined(__CRT_HAVE_dyn_string_resize) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xmalloc_failed)))
#include <libc/local/dyn-string/dyn_string_append.h>
/* >> dyn_string_append(3)
 * Append `src' to the end of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__NAMESPACE_LOCAL_USING_OR_IMPL(dyn_string_append, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL dyn_string_append)(struct dyn_string *__dst, struct dyn_string __KOS_FIXED_CONST *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dyn_string_append))(__dst, __src); })
#endif /* ... */
#ifdef __CRT_HAVE_dyn_string_append_cstr
/* >> dyn_string_append_cstr(3)
 * Append `src' to the end of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_NCX,dyn_string_append_cstr,(struct dyn_string *__dst, char const *__src),(__dst,__src))
#elif defined(__CRT_HAVE_dyn_string_insert_cstr) || defined(__CRT_HAVE_dyn_string_insert) || defined(__CRT_HAVE_dyn_string_resize) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xmalloc_failed)))
#include <libc/local/dyn-string/dyn_string_append_cstr.h>
/* >> dyn_string_append_cstr(3)
 * Append `src' to the end of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__NAMESPACE_LOCAL_USING_OR_IMPL(dyn_string_append_cstr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL dyn_string_append_cstr)(struct dyn_string *__dst, char const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dyn_string_append_cstr))(__dst, __src); })
#endif /* ... */
#ifdef __CRT_HAVE_dyn_string_append_char
/* >> dyn_string_append_char(3)
 * Append `ch' to the end of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__CDECLARE(__ATTR_INOUT(1),int,__NOTHROW_NCX,dyn_string_append_char,(struct dyn_string *__dst, int __ch),(__dst,__ch))
#elif defined(__CRT_HAVE_dyn_string_insert_char) || defined(__CRT_HAVE_dyn_string_insert) || defined(__CRT_HAVE_dyn_string_resize) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xmalloc_failed)))
#include <libc/local/dyn-string/dyn_string_append_char.h>
/* >> dyn_string_append_char(3)
 * Append `ch' to the end of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__NAMESPACE_LOCAL_USING_OR_IMPL(dyn_string_append_char, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL dyn_string_append_char)(struct dyn_string *__dst, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dyn_string_append_char))(__dst, __ch); })
#endif /* ... */
#ifdef __CRT_HAVE_dyn_string_substring
/* >> dyn_string_substring(3)
 * Assign  the substring `src[start:end]'  to `dst'. Note that
 * the given indices _must_ be properly ordered, and in-range!
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_NCX,dyn_string_substring,(struct dyn_string *__dst, struct dyn_string __KOS_FIXED_CONST *__src, __STDC_INT_AS_SIZE_T __start, __STDC_INT_AS_SIZE_T __end),(__dst,__src,__start,__end))
#elif defined(__CRT_HAVE_dyn_string_copy) || defined(__CRT_HAVE_dyn_string_resize) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xmalloc_failed)))
#include <libc/local/dyn-string/dyn_string_substring.h>
/* >> dyn_string_substring(3)
 * Assign  the substring `src[start:end]'  to `dst'. Note that
 * the given indices _must_ be properly ordered, and in-range!
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
__NAMESPACE_LOCAL_USING_OR_IMPL(dyn_string_substring, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL dyn_string_substring)(struct dyn_string *__dst, struct dyn_string __KOS_FIXED_CONST *__src, __STDC_INT_AS_SIZE_T __start, __STDC_INT_AS_SIZE_T __end) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dyn_string_substring))(__dst, __src, __start, __end); })
#endif /* ... */
#ifdef __CRT_HAVE_dyn_string_eq
/* >> dyn_string_eq(3)
 * Return `1' if the contents of the given strings are equal; `0' otherwise.
 * @return: 0 : Strings differ
 * @return: 1 : Strings are identical */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,dyn_string_eq,(struct dyn_string __KOS_FIXED_CONST *__lhs, struct dyn_string __KOS_FIXED_CONST *__rhs),(__lhs,__rhs))
#else /* __CRT_HAVE_dyn_string_eq */
#include <libc/local/dyn-string/dyn_string_eq.h>
/* >> dyn_string_eq(3)
 * Return `1' if the contents of the given strings are equal; `0' otherwise.
 * @return: 0 : Strings differ
 * @return: 1 : Strings are identical */
__NAMESPACE_LOCAL_USING_OR_IMPL(dyn_string_eq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL dyn_string_eq)(struct dyn_string __KOS_FIXED_CONST *__lhs, struct dyn_string __KOS_FIXED_CONST *__rhs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dyn_string_eq))(__lhs, __rhs); })
#endif /* !__CRT_HAVE_dyn_string_eq */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_DYN_STRING_H */
