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
/*!included_by <getopt.h>*/
#ifndef _BITS_CRT_GETOPT_H
#define _BITS_CRT_GETOPT_H 1

#include <__stdinc.h>

/* Possible values for `struct option::has_arg' */
#define __no_argument       0 /* Option does not take an argument */
#define __required_argument 1 /* Option requires an argument to be present */
#define __optional_argument 2 /* Option accepts an optional argument. */

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("name")
#pragma push_macro("has_arg")
#pragma push_macro("flag")
#pragma push_macro("val")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef name
#undef has_arg
#undef flag
#undef val
struct option {
	char const *name;    /* [1..1] Option name (or NULL for sentinal) */
	int         has_arg; /* One of `no_argument=0', `required_argument=1' or `optional_argument=2' */
	int        *flag;    /* [0..1] When non-NULL,  `getopt_long(3)'  will  do  `*flag = val'  and
	                      * return `0' when this option is encountered, rather than return `val'. */
	int         val;     /* Value-code for this option (value returned by `getopt_long(3)' upon
	                      * encountering this option. */
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("val")
#pragma pop_macro("flag")
#pragma pop_macro("has_arg")
#pragma pop_macro("name")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_GETOPT_H */
