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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _SYS__TYPES_H
#define _SYS__TYPES_H 1

#include <__stdinc.h>
#include <bits/types.h>
#include <features.h>
#include <hybrid/typecore.h>

__DECL_BEGIN

#ifdef __CC__
typedef __LONGPTR_TYPE__  __cyg_off_t;
typedef __off64_t         __cyg_off64_t;
typedef __LONGPTR_TYPE__  __cyg_fpos_t;
typedef __off64_t         __cyg_fpos64_t;
typedef void             *__cyg_iconv_t;
typedef void             *__cyg_flock_t;
typedef __builtin_va_list __cyg_va_list;


#ifdef __USE_CYG
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("_off_t")
#pragma push_macro("_off64_t")
#pragma push_macro("_fpos_t")
#pragma push_macro("_fpos64_t")
#pragma push_macro("_ssize_t")
#pragma push_macro("_iconv_t")
#pragma push_macro("_flock_t")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#undef _off_t
#undef _off64_t
#undef _fpos_t
#undef _ssize_t
#undef _iconv_t
#undef _flock_t
typedef __cyg_off_t   _off_t;
typedef __cyg_off64_t _off64_t;
typedef __cyg_fpos_t  _fpos_t;
#ifdef __USE_LARGEFILE64
#undef _fpos64_t
typedef __cyg_fpos64_t _fpos64_t;
#endif
typedef __SSIZE_TYPE__ _ssize_t;
typedef __cyg_iconv_t  _iconv_t;
typedef	__cyg_flock_t  _flock_t;

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("_flock_t")
#pragma pop_macro("_iconv_t")
#pragma pop_macro("_ssize_t")
#pragma pop_macro("_fpos64_t")
#pragma pop_macro("_fpos_t")
#pragma pop_macro("_off64_t")
#pragma pop_macro("_off_t")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __USE_CYG */
#endif /* __CC__ */

__DECL_END

#endif /* !_SYS__TYPES_H */
