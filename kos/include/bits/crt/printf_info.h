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
#ifndef _BITS_CRT_PRINTF_INFO_H
#define _BITS_CRT_PRINTF_INFO_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("prec")
#pragma push_macro("width")
#pragma push_macro("spec")
#pragma push_macro("is_long_double")
#pragma push_macro("is_short")
#pragma push_macro("is_long")
#pragma push_macro("alt")
#pragma push_macro("space")
#pragma push_macro("left")
#pragma push_macro("showsign")
#pragma push_macro("group")
#pragma push_macro("extra")
#pragma push_macro("is_char")
#pragma push_macro("wide")
#pragma push_macro("i18n")
#pragma push_macro("is_binary128")
#pragma push_macro("user")
#pragma push_macro("pad")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef prec
#undef width
#undef spec
#undef is_long_double
#undef is_short
#undef is_long
#undef alt
#undef space
#undef left
#undef showsign
#undef group
#undef extra
#undef is_char
#undef wide
#undef i18n
#undef is_binary128
#undef user
#undef pad

struct printf_info {
	__STDC_INT_AS_SIZE_T prec;              /* Precision. */
	__STDC_INT_AS_SIZE_T width;             /* Width. */
	__WCHAR32_TYPE__     spec;              /* Final format specification letter */
	unsigned int         is_long_double: 1; /* "L" (and "ll") */
	unsigned int         is_short      : 1; /* "h" */
	unsigned int         is_long       : 1; /* "l" */
	unsigned int         alt           : 1; /* "#" */
	unsigned int         space         : 1; /* " " */
	unsigned int         left          : 1; /* "-" */
	unsigned int         showsign      : 1; /* "+" */
	unsigned int         group         : 1; /* "'" */
	unsigned int         extra         : 1; /* ??? */
	unsigned int         is_char       : 1; /* "hh" */
	unsigned int         wide          : 1; /* Set if wchar_t-stream */
	unsigned int         i18n          : 1; /* "I" */
	unsigned int         is_binary128  : 1; /* ??? */
	unsigned int       __pad           : 3; /* ...*/
	__UINT16_TYPE__      user;              /* User-defined modifiers (s.a. `register_printf_modifier(3)') */
	__WCHAR32_TYPE__     pad;               /* Padding character */
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("pad")
#pragma pop_macro("user")
#pragma pop_macro("is_binary128")
#pragma pop_macro("i18n")
#pragma pop_macro("wide")
#pragma pop_macro("is_char")
#pragma pop_macro("extra")
#pragma pop_macro("group")
#pragma pop_macro("showsign")
#pragma pop_macro("left")
#pragma pop_macro("space")
#pragma pop_macro("alt")
#pragma pop_macro("is_long")
#pragma pop_macro("is_short")
#pragma pop_macro("is_long_double")
#pragma pop_macro("spec")
#pragma pop_macro("width")
#pragma pop_macro("prec")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/* Printf print handler (similar to KOS's `pformatprinter')
 * @param: stream: Output stream (wrapper around the underlying `pformatprinter')
 * @param: info:   Format specifiers
 * @param: args:   Vector  of pointers to argument data (iow: `*(int *)args[i]')
 *                 Vector has `return(printf_arginfo_size_function())' elements.
 * @return: >= 0:  The # of printed characters
 * @return: -1:    Error (on KOS, any negative value is treated as such) */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2, 3)) __STDC_INT_AS_SSIZE_T
(__LIBKCALL __printf_function)(__FILE *__stream,
                               struct printf_info const *__info,
                               void const *const *__args);

/* Printf argument info collection handler
 * @param: info:     Format specifiers
 * @param: n:        The # of elements the caller allocated for `argtypes'
 * @param: argtypes: To-be  filled with `PA_*' (optionally or'd with `PA_FLAG_*')
 *                   At most `n' elements can be filled, and the return value  is
 *                   the # of elements needed. When `return > n', the contents of
 *                   this array are left undefined.
 * @param: size:     To-be filled with the buffer size taken by `printf_va_arg_function'
 *                   At most  `n'  elements can  be  filled,  and the  return  value  is
 *                   the #  of  elements  needed. When  `return > n',  the  contents  of
 *                   this array are left undefined.
 * @return: >= 0:    The # of arguments used by this handler (at most this many elements have been filled in `argtypes')
 * @return: -1:      Unable to handle format specifier */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 3, 4)) __STDC_INT_AS_SSIZE_T
(__LIBKCALL __printf_arginfo_size_function)(struct printf_info const *__info,
                                            __SIZE_TYPE__ __n, int *__argtypes,
                                            __STDC_INT_AS_SIZE_T *__size);
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 3)) __STDC_INT_AS_SSIZE_T
(__LIBKCALL __printf_arginfo_function)(struct printf_info const *__info,
                                       __SIZE_TYPE__ __n, int *__argtypes);

/* Handler for custom printf argument decoder functions
 * @param: mem: Target buffer (buffer size is given by `printf_arginfo_size_function()')
 * @param: ap:  va_list source buffer. */
typedef __ATTR_NONNULL_T((1, 2)) void
(__LIBKCALL __printf_va_arg_function)(void *__mem, __builtin_va_list *__ap);


/* Printf type codes (more of these can be defined with `register_printf_type(3)') */
enum {
	PA_INT,     /* `va_arg(int)' */
	PA_CHAR,    /* `(char)va_arg(int)' */
	PA_WCHAR,   /* `(wchar_t)va_arg(wint_t)' */
	PA_STRING,  /* `va_arg(char const *)' (NUL-terminated) */
	PA_WSTRING, /* `va_arg(wchar_t const *)' (NUL-terminated) */
	PA_POINTER, /* `va_arg(void *)' */
	PA_FLOAT,   /* `(float)va_arg(double)' */
	PA_DOUBLE,  /* `va_arg(double)' */
	PA_LAST     /* First dynamically allocated (by `register_printf_type(3)') type-code */
};

/* Extra bits that can be set in printf type-codes */
#define PA_FLAG_MASK        0xff00
#define PA_FLAG_LONG_LONG   (1 << 8)
#define PA_FLAG_LONG_DOUBLE PA_FLAG_LONG_LONG
#define PA_FLAG_LONG        (1 << 9)
#define PA_FLAG_SHORT       (1 << 10)
#define PA_FLAG_PTR         (1 << 11)

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_PRINTF_INFO_H */
