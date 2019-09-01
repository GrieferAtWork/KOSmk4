/* HASH 0xea998e43 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef _LIBC_SLOW_UNICODE_H
#define _LIBC_SLOW_UNICODE_H 1

#include <__stdinc.h>
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#if defined(__CRT_HAVE_unicode_readutf8)
/* Read a single Unicode character from a given UTF-8 string */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,__libc_slow_unicode_readutf8,(/*utf-8*/char const **__restrict __ptext),unicode_readutf8,(__ptext))
#else /* LIBC: unicode_readutf8 */
#include <local/unicode/unicode_readutf8.h>
/* Read a single Unicode character from a given UTF-8 string */
#define __libc_slow_unicode_readutf8 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8))
#endif /* unicode_readutf8... */
#if defined(__CRT_HAVE_unicode_readutf8_rev)
/* Same as `unicode_readutf8', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__CREDIRECT(__ATTR_NONNULL((1)),__CHAR32_TYPE__,__NOTHROW_NCX,__libc_slow_unicode_readutf8_rev,(/*utf-8*/char const **__restrict __ptext),unicode_readutf8_rev,(__ptext))
#else /* LIBC: unicode_readutf8_rev */
#include <local/unicode/unicode_readutf8_rev.h>
/* Same as `unicode_readutf8', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
#define __libc_slow_unicode_readutf8_rev (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_rev))
#endif /* unicode_readutf8_rev... */
#if defined(__CRT_HAVE_unicode_readutf8_n)
/* Same as `unicode_readutf8()', but don't read past `text_end' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,__libc_slow_unicode_readutf8_n,(/*utf-8*/char const **__restrict __ptext, char const *__text_end),unicode_readutf8_n,(__ptext,__text_end))
#else /* LIBC: unicode_readutf8_n */
#include <local/unicode/unicode_readutf8_n.h>
/* Same as `unicode_readutf8()', but don't read past `text_end' */
#define __libc_slow_unicode_readutf8_n (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_n))
#endif /* unicode_readutf8_n... */
#if defined(__CRT_HAVE_unicode_readutf8_rev_n)
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,__libc_slow_unicode_readutf8_rev_n,(/*utf-8*/char const **__restrict __ptext, char const *__text_start),unicode_readutf8_rev_n,(__ptext,__text_start))
#else /* LIBC: unicode_readutf8_rev_n */
#include <local/unicode/unicode_readutf8_rev_n.h>
/* Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
#define __libc_slow_unicode_readutf8_rev_n (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_rev_n))
#endif /* unicode_readutf8_rev_n... */
#if defined(__CRT_HAVE_unicode_writeutf8)
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__libc_slow_unicode_writeutf8,(/*utf-8*/char *__restrict __dst, __CHAR32_TYPE__ __ch),unicode_writeutf8,(__dst,__ch))
#else /* LIBC: unicode_writeutf8 */
#include <local/unicode/unicode_writeutf8.h>
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
#define __libc_slow_unicode_writeutf8 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_writeutf8))
#endif /* unicode_writeutf8... */

__SYSDECL_END

#endif /* !_LIBC_SLOW_UNICODE_H */
