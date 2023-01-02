/* HASH CRC-32:0xe6ddd3b8 */
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
#ifndef _PARTS_UCHAR_WCTYPE_H
#define _PARTS_UCHAR_WCTYPE_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>
#ifndef _WCTYPE_H
#include <wctype.h>
#endif /* !_WCTYPE_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __wint16_t_defined
#define __wint16_t_defined
typedef __WINT16_TYPE__ wint16_t;
typedef __WINT32_TYPE__ wint32_t;
#endif /* !__wint16_t_defined */

#include <bits/crt/wctype.h>
#if defined(__crt_iswcntrl) && defined(__CRT_HAVE_iswcntrl) && __SIZEOF_WCHAR_T__ == 2
/* >> iswcntrl(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,iscntrl16,(wint16_t __wc),iswcntrl,{ return __crt_iswcntrl(__wc); })
#elif defined(__crt_iswcntrl) && __SIZEOF_WCHAR_T__ == 2
/* >> iswcntrl(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL iscntrl16)(wint16_t __wc) { return __crt_iswcntrl(__wc); }
#elif __has_builtin(__builtin_iswcntrl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswcntrl) && __SIZEOF_WCHAR_T__ == 2
/* >> iswcntrl(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,iscntrl16,(wint16_t __wc),iswcntrl,{ return __builtin_iswcntrl(__wc); })
#elif defined(__CRT_HAVE_iswcntrl) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswcntrl(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iscntrl16,(wint16_t __wc),iswcntrl,(__wc))
#elif defined(__CRT_HAVE_DOS$iswcntrl)
/* >> iswcntrl(3) */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iscntrl16,(wint16_t __wc),iswcntrl,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswcntrl.h>
/* >> iswcntrl(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL iscntrl16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswcntrl))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/iscntrl16.h>
/* >> iswcntrl(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iscntrl16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL iscntrl16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iscntrl16))(__wc); })
#endif /* !... */
#if defined(__crt_iswcntrl) && defined(__CRT_HAVE_iswcntrl) && __SIZEOF_WCHAR_T__ == 4
/* >> iswcntrl(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,iscntrl32,(wint32_t __wc),iswcntrl,{ return __crt_iswcntrl(__wc); })
#elif defined(__crt_iswcntrl) && __SIZEOF_WCHAR_T__ == 4
/* >> iswcntrl(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL iscntrl32)(wint32_t __wc) { return __crt_iswcntrl(__wc); }
#elif __has_builtin(__builtin_iswcntrl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswcntrl) && __SIZEOF_WCHAR_T__ == 4
/* >> iswcntrl(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,iscntrl32,(wint32_t __wc),iswcntrl,{ return __builtin_iswcntrl(__wc); })
#elif defined(__CRT_HAVE_iswcntrl) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswcntrl(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iscntrl32,(wint32_t __wc),iswcntrl,(__wc))
#elif defined(__CRT_HAVE_KOS$iswcntrl)
/* >> iswcntrl(3) */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iscntrl32,(wint32_t __wc),iswcntrl,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswcntrl.h>
/* >> iswcntrl(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL iscntrl32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswcntrl))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/iscntrl32.h>
/* >> iswcntrl(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iscntrl32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL iscntrl32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iscntrl32))(__wc); })
#endif /* !... */
#if defined(__crt_iswspace) && defined(__CRT_HAVE_iswspace) && __SIZEOF_WCHAR_T__ == 2
/* >> iswspace(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,isspace16,(wint16_t __wc),iswspace,{ return __crt_iswspace(__wc); })
#elif defined(__crt_iswspace) && __SIZEOF_WCHAR_T__ == 2
/* >> iswspace(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isspace16)(wint16_t __wc) { return __crt_iswspace(__wc); }
#elif __has_builtin(__builtin_iswspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswspace) && __SIZEOF_WCHAR_T__ == 2
/* >> iswspace(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,isspace16,(wint16_t __wc),iswspace,{ return __builtin_iswspace(__wc); })
#elif defined(__CRT_HAVE_iswspace) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswspace(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isspace16,(wint16_t __wc),iswspace,(__wc))
#elif defined(__CRT_HAVE_DOS$iswspace)
/* >> iswspace(3) */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isspace16,(wint16_t __wc),iswspace,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswspace.h>
/* >> iswspace(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isspace16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswspace))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isspace16.h>
/* >> iswspace(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isspace16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isspace16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isspace16))(__wc); })
#endif /* !... */
#if defined(__crt_iswspace) && defined(__CRT_HAVE_iswspace) && __SIZEOF_WCHAR_T__ == 4
/* >> iswspace(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,isspace32,(wint32_t __wc),iswspace,{ return __crt_iswspace(__wc); })
#elif defined(__crt_iswspace) && __SIZEOF_WCHAR_T__ == 4
/* >> iswspace(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isspace32)(wint32_t __wc) { return __crt_iswspace(__wc); }
#elif __has_builtin(__builtin_iswspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswspace) && __SIZEOF_WCHAR_T__ == 4
/* >> iswspace(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,isspace32,(wint32_t __wc),iswspace,{ return __builtin_iswspace(__wc); })
#elif defined(__CRT_HAVE_iswspace) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswspace(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isspace32,(wint32_t __wc),iswspace,(__wc))
#elif defined(__CRT_HAVE_KOS$iswspace)
/* >> iswspace(3) */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isspace32,(wint32_t __wc),iswspace,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswspace.h>
/* >> iswspace(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isspace32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswspace))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isspace32.h>
/* >> iswspace(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isspace32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isspace32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isspace32))(__wc); })
#endif /* !... */
#if defined(__crt_iswupper) && defined(__CRT_HAVE_iswupper) && __SIZEOF_WCHAR_T__ == 2
/* >> iswupper(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,isupper16,(wint16_t __wc),iswupper,{ return __crt_iswupper(__wc); })
#elif defined(__crt_iswupper) && __SIZEOF_WCHAR_T__ == 2
/* >> iswupper(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isupper16)(wint16_t __wc) { return __crt_iswupper(__wc); }
#elif __has_builtin(__builtin_iswupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswupper) && __SIZEOF_WCHAR_T__ == 2
/* >> iswupper(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,isupper16,(wint16_t __wc),iswupper,{ return __builtin_iswupper(__wc); })
#elif defined(__CRT_HAVE_iswupper) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswupper(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isupper16,(wint16_t __wc),iswupper,(__wc))
#elif defined(__CRT_HAVE_DOS$iswupper)
/* >> iswupper(3) */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isupper16,(wint16_t __wc),iswupper,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswupper.h>
/* >> iswupper(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isupper16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswupper))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isupper16.h>
/* >> iswupper(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isupper16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isupper16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isupper16))(__wc); })
#endif /* !... */
#if defined(__crt_iswupper) && defined(__CRT_HAVE_iswupper) && __SIZEOF_WCHAR_T__ == 4
/* >> iswupper(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,isupper32,(wint32_t __wc),iswupper,{ return __crt_iswupper(__wc); })
#elif defined(__crt_iswupper) && __SIZEOF_WCHAR_T__ == 4
/* >> iswupper(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isupper32)(wint32_t __wc) { return __crt_iswupper(__wc); }
#elif __has_builtin(__builtin_iswupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswupper) && __SIZEOF_WCHAR_T__ == 4
/* >> iswupper(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,isupper32,(wint32_t __wc),iswupper,{ return __builtin_iswupper(__wc); })
#elif defined(__CRT_HAVE_iswupper) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswupper(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isupper32,(wint32_t __wc),iswupper,(__wc))
#elif defined(__CRT_HAVE_KOS$iswupper)
/* >> iswupper(3) */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isupper32,(wint32_t __wc),iswupper,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswupper.h>
/* >> iswupper(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isupper32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswupper))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isupper32.h>
/* >> iswupper(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isupper32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isupper32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isupper32))(__wc); })
#endif /* !... */
#if defined(__crt_iswlower) && defined(__CRT_HAVE_iswlower) && __SIZEOF_WCHAR_T__ == 2
/* >> iswlower(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,islower16,(wint16_t __wc),iswlower,{ return __crt_iswlower(__wc); })
#elif defined(__crt_iswlower) && __SIZEOF_WCHAR_T__ == 2
/* >> iswlower(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL islower16)(wint16_t __wc) { return __crt_iswlower(__wc); }
#elif __has_builtin(__builtin_iswlower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswlower) && __SIZEOF_WCHAR_T__ == 2
/* >> iswlower(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,islower16,(wint16_t __wc),iswlower,{ return __builtin_iswlower(__wc); })
#elif defined(__CRT_HAVE_iswlower) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswlower(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,islower16,(wint16_t __wc),iswlower,(__wc))
#elif defined(__CRT_HAVE_DOS$iswlower)
/* >> iswlower(3) */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,islower16,(wint16_t __wc),iswlower,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswlower.h>
/* >> iswlower(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL islower16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswlower))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/islower16.h>
/* >> iswlower(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(islower16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL islower16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(islower16))(__wc); })
#endif /* !... */
#if defined(__crt_iswlower) && defined(__CRT_HAVE_iswlower) && __SIZEOF_WCHAR_T__ == 4
/* >> iswlower(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,islower32,(wint32_t __wc),iswlower,{ return __crt_iswlower(__wc); })
#elif defined(__crt_iswlower) && __SIZEOF_WCHAR_T__ == 4
/* >> iswlower(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL islower32)(wint32_t __wc) { return __crt_iswlower(__wc); }
#elif __has_builtin(__builtin_iswlower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswlower) && __SIZEOF_WCHAR_T__ == 4
/* >> iswlower(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,islower32,(wint32_t __wc),iswlower,{ return __builtin_iswlower(__wc); })
#elif defined(__CRT_HAVE_iswlower) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswlower(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,islower32,(wint32_t __wc),iswlower,(__wc))
#elif defined(__CRT_HAVE_KOS$iswlower)
/* >> iswlower(3) */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,islower32,(wint32_t __wc),iswlower,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswlower.h>
/* >> iswlower(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL islower32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswlower))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/islower32.h>
/* >> iswlower(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(islower32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL islower32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(islower32))(__wc); })
#endif /* !... */
#if defined(__crt_iswalpha) && defined(__CRT_HAVE_iswalpha) && __SIZEOF_WCHAR_T__ == 2
/* >> iswalpha(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,isalpha16,(wint16_t __wc),iswalpha,{ return __crt_iswalpha(__wc); })
#elif defined(__crt_iswalpha) && __SIZEOF_WCHAR_T__ == 2
/* >> iswalpha(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isalpha16)(wint16_t __wc) { return __crt_iswalpha(__wc); }
#elif __has_builtin(__builtin_iswalpha) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswalpha) && __SIZEOF_WCHAR_T__ == 2
/* >> iswalpha(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,isalpha16,(wint16_t __wc),iswalpha,{ return __builtin_iswalpha(__wc); })
#elif defined(__CRT_HAVE_iswalpha) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswalpha(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isalpha16,(wint16_t __wc),iswalpha,(__wc))
#elif defined(__CRT_HAVE_DOS$iswalpha)
/* >> iswalpha(3) */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isalpha16,(wint16_t __wc),iswalpha,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswalpha.h>
/* >> iswalpha(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isalpha16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalpha))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isalpha16.h>
/* >> iswalpha(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isalpha16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isalpha16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalpha16))(__wc); })
#endif /* !... */
#if defined(__crt_iswalpha) && defined(__CRT_HAVE_iswalpha) && __SIZEOF_WCHAR_T__ == 4
/* >> iswalpha(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,isalpha32,(wint32_t __wc),iswalpha,{ return __crt_iswalpha(__wc); })
#elif defined(__crt_iswalpha) && __SIZEOF_WCHAR_T__ == 4
/* >> iswalpha(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isalpha32)(wint32_t __wc) { return __crt_iswalpha(__wc); }
#elif __has_builtin(__builtin_iswalpha) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswalpha) && __SIZEOF_WCHAR_T__ == 4
/* >> iswalpha(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,isalpha32,(wint32_t __wc),iswalpha,{ return __builtin_iswalpha(__wc); })
#elif defined(__CRT_HAVE_iswalpha) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswalpha(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isalpha32,(wint32_t __wc),iswalpha,(__wc))
#elif defined(__CRT_HAVE_KOS$iswalpha)
/* >> iswalpha(3) */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isalpha32,(wint32_t __wc),iswalpha,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswalpha.h>
/* >> iswalpha(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isalpha32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalpha))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isalpha32.h>
/* >> iswalpha(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isalpha32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isalpha32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalpha32))(__wc); })
#endif /* !... */
#if defined(__crt_iswdigit) && defined(__CRT_HAVE_iswdigit) && __SIZEOF_WCHAR_T__ == 2
/* >> iswdigit(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,isdigit16,(wint16_t __wc),iswdigit,{ return __crt_iswdigit(__wc); })
#elif defined(__crt_iswdigit) && __SIZEOF_WCHAR_T__ == 2
/* >> iswdigit(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isdigit16)(wint16_t __wc) { return __crt_iswdigit(__wc); }
#elif __has_builtin(__builtin_iswdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswdigit) && __SIZEOF_WCHAR_T__ == 2
/* >> iswdigit(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,isdigit16,(wint16_t __wc),iswdigit,{ return __builtin_iswdigit(__wc); })
#elif defined(__CRT_HAVE_iswdigit) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswdigit(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isdigit16,(wint16_t __wc),iswdigit,(__wc))
#elif defined(__CRT_HAVE_DOS$iswdigit)
/* >> iswdigit(3) */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isdigit16,(wint16_t __wc),iswdigit,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswdigit.h>
/* >> iswdigit(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isdigit16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswdigit))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isdigit16.h>
/* >> iswdigit(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isdigit16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isdigit16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isdigit16))(__wc); })
#endif /* !... */
#if defined(__crt_iswdigit) && defined(__CRT_HAVE_iswdigit) && __SIZEOF_WCHAR_T__ == 4
/* >> iswdigit(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,isdigit32,(wint32_t __wc),iswdigit,{ return __crt_iswdigit(__wc); })
#elif defined(__crt_iswdigit) && __SIZEOF_WCHAR_T__ == 4
/* >> iswdigit(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isdigit32)(wint32_t __wc) { return __crt_iswdigit(__wc); }
#elif __has_builtin(__builtin_iswdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswdigit) && __SIZEOF_WCHAR_T__ == 4
/* >> iswdigit(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,isdigit32,(wint32_t __wc),iswdigit,{ return __builtin_iswdigit(__wc); })
#elif defined(__CRT_HAVE_iswdigit) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswdigit(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isdigit32,(wint32_t __wc),iswdigit,(__wc))
#elif defined(__CRT_HAVE_KOS$iswdigit)
/* >> iswdigit(3) */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isdigit32,(wint32_t __wc),iswdigit,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswdigit.h>
/* >> iswdigit(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isdigit32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswdigit))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isdigit32.h>
/* >> iswdigit(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isdigit32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isdigit32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isdigit32))(__wc); })
#endif /* !... */
#if defined(__crt_iswxdigit) && defined(__CRT_HAVE_iswxdigit) && __SIZEOF_WCHAR_T__ == 2
/* >> iswxdigit(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,isxdigit16,(wint16_t __wc),iswxdigit,{ return __crt_iswxdigit(__wc); })
#elif defined(__crt_iswxdigit) && __SIZEOF_WCHAR_T__ == 2
/* >> iswxdigit(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isxdigit16)(wint16_t __wc) { return __crt_iswxdigit(__wc); }
#elif __has_builtin(__builtin_iswxdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswxdigit) && __SIZEOF_WCHAR_T__ == 2
/* >> iswxdigit(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,isxdigit16,(wint16_t __wc),iswxdigit,{ return __builtin_iswxdigit(__wc); })
#elif defined(__CRT_HAVE_iswxdigit) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswxdigit(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isxdigit16,(wint16_t __wc),iswxdigit,(__wc))
#elif defined(__CRT_HAVE_DOS$iswxdigit)
/* >> iswxdigit(3) */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isxdigit16,(wint16_t __wc),iswxdigit,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswxdigit.h>
/* >> iswxdigit(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isxdigit16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswxdigit))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isxdigit16.h>
/* >> iswxdigit(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isxdigit16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isxdigit16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isxdigit16))(__wc); })
#endif /* !... */
#if defined(__crt_iswxdigit) && defined(__CRT_HAVE_iswxdigit) && __SIZEOF_WCHAR_T__ == 4
/* >> iswxdigit(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,isxdigit32,(wint32_t __wc),iswxdigit,{ return __crt_iswxdigit(__wc); })
#elif defined(__crt_iswxdigit) && __SIZEOF_WCHAR_T__ == 4
/* >> iswxdigit(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isxdigit32)(wint32_t __wc) { return __crt_iswxdigit(__wc); }
#elif __has_builtin(__builtin_iswxdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswxdigit) && __SIZEOF_WCHAR_T__ == 4
/* >> iswxdigit(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,isxdigit32,(wint32_t __wc),iswxdigit,{ return __builtin_iswxdigit(__wc); })
#elif defined(__CRT_HAVE_iswxdigit) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswxdigit(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isxdigit32,(wint32_t __wc),iswxdigit,(__wc))
#elif defined(__CRT_HAVE_KOS$iswxdigit)
/* >> iswxdigit(3) */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isxdigit32,(wint32_t __wc),iswxdigit,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswxdigit.h>
/* >> iswxdigit(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isxdigit32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswxdigit))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isxdigit32.h>
/* >> iswxdigit(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isxdigit32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isxdigit32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isxdigit32))(__wc); })
#endif /* !... */
#if defined(__crt_iswalnum) && defined(__CRT_HAVE_iswalnum) && __SIZEOF_WCHAR_T__ == 2
/* >> iswalnum(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,isalnum16,(wint16_t __wc),iswalnum,{ return __crt_iswalnum(__wc); })
#elif defined(__crt_iswalnum) && __SIZEOF_WCHAR_T__ == 2
/* >> iswalnum(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isalnum16)(wint16_t __wc) { return __crt_iswalnum(__wc); }
#elif __has_builtin(__builtin_iswalnum) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswalnum) && __SIZEOF_WCHAR_T__ == 2
/* >> iswalnum(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,isalnum16,(wint16_t __wc),iswalnum,{ return __builtin_iswalnum(__wc); })
#elif defined(__CRT_HAVE_iswalnum) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswalnum(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isalnum16,(wint16_t __wc),iswalnum,(__wc))
#elif defined(__CRT_HAVE_DOS$iswalnum)
/* >> iswalnum(3) */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isalnum16,(wint16_t __wc),iswalnum,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswalnum.h>
/* >> iswalnum(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isalnum16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalnum))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isalnum16.h>
/* >> iswalnum(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isalnum16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isalnum16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalnum16))(__wc); })
#endif /* !... */
#if defined(__crt_iswalnum) && defined(__CRT_HAVE_iswalnum) && __SIZEOF_WCHAR_T__ == 4
/* >> iswalnum(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,isalnum32,(wint32_t __wc),iswalnum,{ return __crt_iswalnum(__wc); })
#elif defined(__crt_iswalnum) && __SIZEOF_WCHAR_T__ == 4
/* >> iswalnum(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isalnum32)(wint32_t __wc) { return __crt_iswalnum(__wc); }
#elif __has_builtin(__builtin_iswalnum) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswalnum) && __SIZEOF_WCHAR_T__ == 4
/* >> iswalnum(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,isalnum32,(wint32_t __wc),iswalnum,{ return __builtin_iswalnum(__wc); })
#elif defined(__CRT_HAVE_iswalnum) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswalnum(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isalnum32,(wint32_t __wc),iswalnum,(__wc))
#elif defined(__CRT_HAVE_KOS$iswalnum)
/* >> iswalnum(3) */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isalnum32,(wint32_t __wc),iswalnum,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswalnum.h>
/* >> iswalnum(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isalnum32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalnum))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isalnum32.h>
/* >> iswalnum(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isalnum32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isalnum32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalnum32))(__wc); })
#endif /* !... */
#if defined(__crt_iswpunct) && defined(__CRT_HAVE_iswpunct) && __SIZEOF_WCHAR_T__ == 2
/* >> iswpunct(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,ispunct16,(wint16_t __wc),iswpunct,{ return __crt_iswpunct(__wc); })
#elif defined(__crt_iswpunct) && __SIZEOF_WCHAR_T__ == 2
/* >> iswpunct(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL ispunct16)(wint16_t __wc) { return __crt_iswpunct(__wc); }
#elif __has_builtin(__builtin_iswpunct) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswpunct) && __SIZEOF_WCHAR_T__ == 2
/* >> iswpunct(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,ispunct16,(wint16_t __wc),iswpunct,{ return __builtin_iswpunct(__wc); })
#elif defined(__CRT_HAVE_iswpunct) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswpunct(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,ispunct16,(wint16_t __wc),iswpunct,(__wc))
#elif defined(__CRT_HAVE_DOS$iswpunct)
/* >> iswpunct(3) */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,ispunct16,(wint16_t __wc),iswpunct,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswpunct.h>
/* >> iswpunct(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL ispunct16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswpunct))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/ispunct16.h>
/* >> iswpunct(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(ispunct16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL ispunct16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ispunct16))(__wc); })
#endif /* !... */
#if defined(__crt_iswpunct) && defined(__CRT_HAVE_iswpunct) && __SIZEOF_WCHAR_T__ == 4
/* >> iswpunct(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,ispunct32,(wint32_t __wc),iswpunct,{ return __crt_iswpunct(__wc); })
#elif defined(__crt_iswpunct) && __SIZEOF_WCHAR_T__ == 4
/* >> iswpunct(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL ispunct32)(wint32_t __wc) { return __crt_iswpunct(__wc); }
#elif __has_builtin(__builtin_iswpunct) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswpunct) && __SIZEOF_WCHAR_T__ == 4
/* >> iswpunct(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,ispunct32,(wint32_t __wc),iswpunct,{ return __builtin_iswpunct(__wc); })
#elif defined(__CRT_HAVE_iswpunct) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswpunct(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,ispunct32,(wint32_t __wc),iswpunct,(__wc))
#elif defined(__CRT_HAVE_KOS$iswpunct)
/* >> iswpunct(3) */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,ispunct32,(wint32_t __wc),iswpunct,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswpunct.h>
/* >> iswpunct(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL ispunct32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswpunct))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/ispunct32.h>
/* >> iswpunct(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(ispunct32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL ispunct32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ispunct32))(__wc); })
#endif /* !... */
#if defined(__crt_iswgraph) && defined(__CRT_HAVE_iswgraph) && __SIZEOF_WCHAR_T__ == 2
/* >> iswgraph(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,isgraph16,(wint16_t __wc),iswgraph,{ return __crt_iswgraph(__wc); })
#elif defined(__crt_iswgraph) && __SIZEOF_WCHAR_T__ == 2
/* >> iswgraph(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isgraph16)(wint16_t __wc) { return __crt_iswgraph(__wc); }
#elif __has_builtin(__builtin_iswgraph) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswgraph) && __SIZEOF_WCHAR_T__ == 2
/* >> iswgraph(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,isgraph16,(wint16_t __wc),iswgraph,{ return __builtin_iswgraph(__wc); })
#elif defined(__CRT_HAVE_iswgraph) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswgraph(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isgraph16,(wint16_t __wc),iswgraph,(__wc))
#elif defined(__CRT_HAVE_DOS$iswgraph)
/* >> iswgraph(3) */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isgraph16,(wint16_t __wc),iswgraph,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswgraph.h>
/* >> iswgraph(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isgraph16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswgraph))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isgraph16.h>
/* >> iswgraph(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isgraph16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isgraph16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isgraph16))(__wc); })
#endif /* !... */
#if defined(__crt_iswgraph) && defined(__CRT_HAVE_iswgraph) && __SIZEOF_WCHAR_T__ == 4
/* >> iswgraph(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,isgraph32,(wint32_t __wc),iswgraph,{ return __crt_iswgraph(__wc); })
#elif defined(__crt_iswgraph) && __SIZEOF_WCHAR_T__ == 4
/* >> iswgraph(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isgraph32)(wint32_t __wc) { return __crt_iswgraph(__wc); }
#elif __has_builtin(__builtin_iswgraph) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswgraph) && __SIZEOF_WCHAR_T__ == 4
/* >> iswgraph(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,isgraph32,(wint32_t __wc),iswgraph,{ return __builtin_iswgraph(__wc); })
#elif defined(__CRT_HAVE_iswgraph) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswgraph(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isgraph32,(wint32_t __wc),iswgraph,(__wc))
#elif defined(__CRT_HAVE_KOS$iswgraph)
/* >> iswgraph(3) */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isgraph32,(wint32_t __wc),iswgraph,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswgraph.h>
/* >> iswgraph(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isgraph32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswgraph))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isgraph32.h>
/* >> iswgraph(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isgraph32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isgraph32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isgraph32))(__wc); })
#endif /* !... */
#if defined(__crt_iswprint) && defined(__CRT_HAVE_iswprint) && __SIZEOF_WCHAR_T__ == 2
/* >> iswprint(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,isprint16,(wint16_t __wc),iswprint,{ return __crt_iswprint(__wc); })
#elif defined(__crt_iswprint) && __SIZEOF_WCHAR_T__ == 2
/* >> iswprint(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isprint16)(wint16_t __wc) { return __crt_iswprint(__wc); }
#elif __has_builtin(__builtin_iswprint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswprint) && __SIZEOF_WCHAR_T__ == 2
/* >> iswprint(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,isprint16,(wint16_t __wc),iswprint,{ return __builtin_iswprint(__wc); })
#elif defined(__CRT_HAVE_iswprint) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswprint(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isprint16,(wint16_t __wc),iswprint,(__wc))
#elif defined(__CRT_HAVE_DOS$iswprint)
/* >> iswprint(3) */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isprint16,(wint16_t __wc),iswprint,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswprint.h>
/* >> iswprint(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isprint16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswprint))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isprint16.h>
/* >> iswprint(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isprint16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isprint16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isprint16))(__wc); })
#endif /* !... */
#if defined(__crt_iswprint) && defined(__CRT_HAVE_iswprint) && __SIZEOF_WCHAR_T__ == 4
/* >> iswprint(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,isprint32,(wint32_t __wc),iswprint,{ return __crt_iswprint(__wc); })
#elif defined(__crt_iswprint) && __SIZEOF_WCHAR_T__ == 4
/* >> iswprint(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isprint32)(wint32_t __wc) { return __crt_iswprint(__wc); }
#elif __has_builtin(__builtin_iswprint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswprint) && __SIZEOF_WCHAR_T__ == 4
/* >> iswprint(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,isprint32,(wint32_t __wc),iswprint,{ return __builtin_iswprint(__wc); })
#elif defined(__CRT_HAVE_iswprint) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswprint(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isprint32,(wint32_t __wc),iswprint,(__wc))
#elif defined(__CRT_HAVE_KOS$iswprint)
/* >> iswprint(3) */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isprint32,(wint32_t __wc),iswprint,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswprint.h>
/* >> iswprint(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isprint32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswprint))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isprint32.h>
/* >> iswprint(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isprint32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isprint32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isprint32))(__wc); })
#endif /* !... */
#if defined(__crt_towlower) && defined(__CRT_HAVE_towlower) && __SIZEOF_WCHAR_T__ == 2
/* >> towlower(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint16_t,__NOTHROW,__LIBDCALL,tolower16,(wint16_t __wc),towlower,{ return __crt_towlower(__wc); })
#elif defined(__crt_towlower) && __SIZEOF_WCHAR_T__ == 2
/* >> towlower(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED wint16_t __NOTHROW(__LIBDCALL tolower16)(wint16_t __wc) { return __crt_towlower(__wc); }
#elif __has_builtin(__builtin_towlower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_towlower) && __SIZEOF_WCHAR_T__ == 2
/* >> towlower(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint16_t,__NOTHROW,__LIBDCALL,tolower16,(wint16_t __wc),towlower,{ return __builtin_towlower(__wc); })
#elif defined(__CRT_HAVE_towlower) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> towlower(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint16_t,__NOTHROW,tolower16,(wint16_t __wc),towlower,(__wc))
#elif defined(__CRT_HAVE_DOS$towlower)
/* >> towlower(3) */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,wint16_t,__NOTHROW,tolower16,(wint16_t __wc),towlower,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/towlower.h>
/* >> towlower(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint16_t __NOTHROW(__LIBDCALL tolower16)(wint16_t __wc) { return (__WINT16_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towlower))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/tolower16.h>
/* >> towlower(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(tolower16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint16_t __NOTHROW(__LIBDCALL tolower16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tolower16))(__wc); })
#endif /* !... */
#if defined(__crt_towlower) && defined(__CRT_HAVE_towlower) && __SIZEOF_WCHAR_T__ == 4
/* >> towlower(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint32_t,__NOTHROW,__LIBKCALL,tolower32,(wint32_t __wc),towlower,{ return __crt_towlower(__wc); })
#elif defined(__crt_towlower) && __SIZEOF_WCHAR_T__ == 4
/* >> towlower(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED wint32_t __NOTHROW(__LIBKCALL tolower32)(wint32_t __wc) { return __crt_towlower(__wc); }
#elif __has_builtin(__builtin_towlower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_towlower) && __SIZEOF_WCHAR_T__ == 4
/* >> towlower(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint32_t,__NOTHROW,__LIBKCALL,tolower32,(wint32_t __wc),towlower,{ return __builtin_towlower(__wc); })
#elif defined(__CRT_HAVE_towlower) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> towlower(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint32_t,__NOTHROW,tolower32,(wint32_t __wc),towlower,(__wc))
#elif defined(__CRT_HAVE_KOS$towlower)
/* >> towlower(3) */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,wint32_t,__NOTHROW,tolower32,(wint32_t __wc),towlower,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/towlower.h>
/* >> towlower(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint32_t __NOTHROW(__LIBKCALL tolower32)(wint32_t __wc) { return (__WINT32_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towlower))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/tolower32.h>
/* >> towlower(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(tolower32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint32_t __NOTHROW(__LIBKCALL tolower32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tolower32))(__wc); })
#endif /* !... */
#if defined(__crt_towupper) && defined(__CRT_HAVE_towupper) && __SIZEOF_WCHAR_T__ == 2
/* >> towupper(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint16_t,__NOTHROW,__LIBDCALL,toupper16,(wint16_t __wc),towupper,{ return __crt_towupper(__wc); })
#elif defined(__crt_towupper) && __SIZEOF_WCHAR_T__ == 2
/* >> towupper(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED wint16_t __NOTHROW(__LIBDCALL toupper16)(wint16_t __wc) { return __crt_towupper(__wc); }
#elif __has_builtin(__builtin_towupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_towupper) && __SIZEOF_WCHAR_T__ == 2
/* >> towupper(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint16_t,__NOTHROW,__LIBDCALL,toupper16,(wint16_t __wc),towupper,{ return __builtin_towupper(__wc); })
#elif defined(__CRT_HAVE_towupper) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> towupper(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint16_t,__NOTHROW,toupper16,(wint16_t __wc),towupper,(__wc))
#elif defined(__CRT_HAVE_DOS$towupper)
/* >> towupper(3) */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,wint16_t,__NOTHROW,toupper16,(wint16_t __wc),towupper,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/towupper.h>
/* >> towupper(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint16_t __NOTHROW(__LIBDCALL toupper16)(wint16_t __wc) { return (__WINT16_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towupper))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/toupper16.h>
/* >> towupper(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(toupper16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint16_t __NOTHROW(__LIBDCALL toupper16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(toupper16))(__wc); })
#endif /* !... */
#if defined(__crt_towupper) && defined(__CRT_HAVE_towupper) && __SIZEOF_WCHAR_T__ == 4
/* >> towupper(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint32_t,__NOTHROW,__LIBKCALL,toupper32,(wint32_t __wc),towupper,{ return __crt_towupper(__wc); })
#elif defined(__crt_towupper) && __SIZEOF_WCHAR_T__ == 4
/* >> towupper(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED wint32_t __NOTHROW(__LIBKCALL toupper32)(wint32_t __wc) { return __crt_towupper(__wc); }
#elif __has_builtin(__builtin_towupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_towupper) && __SIZEOF_WCHAR_T__ == 4
/* >> towupper(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint32_t,__NOTHROW,__LIBKCALL,toupper32,(wint32_t __wc),towupper,{ return __builtin_towupper(__wc); })
#elif defined(__CRT_HAVE_towupper) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> towupper(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint32_t,__NOTHROW,toupper32,(wint32_t __wc),towupper,(__wc))
#elif defined(__CRT_HAVE_KOS$towupper)
/* >> towupper(3) */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,wint32_t,__NOTHROW,toupper32,(wint32_t __wc),towupper,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/towupper.h>
/* >> towupper(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint32_t __NOTHROW(__LIBKCALL toupper32)(wint32_t __wc) { return (__WINT32_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towupper))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/toupper32.h>
/* >> towupper(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(toupper32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint32_t __NOTHROW(__LIBKCALL toupper32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(toupper32))(__wc); })
#endif /* !... */
#ifdef __USE_ISOC99
#if defined(__crt_iswblank) && defined(__CRT_HAVE_iswblank) && __SIZEOF_WCHAR_T__ == 2
/* >> iswblank(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,isblank16,(wint16_t __wc),iswblank,{ return __crt_iswblank(__wc); })
#elif defined(__crt_iswblank) && __SIZEOF_WCHAR_T__ == 2
/* >> iswblank(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isblank16)(wint16_t __wc) { return __crt_iswblank(__wc); }
#elif __has_builtin(__builtin_iswblank) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswblank) && __SIZEOF_WCHAR_T__ == 2
/* >> iswblank(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBDCALL,isblank16,(wint16_t __wc),iswblank,{ return __builtin_iswblank(__wc); })
#elif defined(__CRT_HAVE_iswblank) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswblank(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isblank16,(wint16_t __wc),iswblank,(__wc))
#elif defined(__CRT_HAVE_DOS$iswblank)
/* >> iswblank(3) */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isblank16,(wint16_t __wc),iswblank,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswblank.h>
/* >> iswblank(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isblank16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswblank))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isblank16.h>
/* >> iswblank(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isblank16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isblank16)(wint16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isblank16))(__wc); })
#endif /* !... */
#if defined(__crt_iswblank) && defined(__CRT_HAVE_iswblank) && __SIZEOF_WCHAR_T__ == 4
/* >> iswblank(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,isblank32,(wint32_t __wc),iswblank,{ return __crt_iswblank(__wc); })
#elif defined(__crt_iswblank) && __SIZEOF_WCHAR_T__ == 4
/* >> iswblank(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isblank32)(wint32_t __wc) { return __crt_iswblank(__wc); }
#elif __has_builtin(__builtin_iswblank) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswblank) && __SIZEOF_WCHAR_T__ == 4
/* >> iswblank(3) */
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,isblank32,(wint32_t __wc),iswblank,{ return __builtin_iswblank(__wc); })
#elif defined(__CRT_HAVE_iswblank) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswblank(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isblank32,(wint32_t __wc),iswblank,(__wc))
#elif defined(__CRT_HAVE_KOS$iswblank)
/* >> iswblank(3) */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isblank32,(wint32_t __wc),iswblank,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswblank.h>
/* >> iswblank(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isblank32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswblank))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isblank32.h>
/* >> iswblank(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isblank32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isblank32)(wint32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isblank32))(__wc); })
#endif /* !... */
#if defined(__CRT_HAVE_towctrans) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint16_t,__NOTHROW_NCX,toctrans16,(wint16_t __wc, wctrans_t __desc),towctrans,(__wc,__desc))
#elif defined(__CRT_HAVE_DOS$towctrans)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,wint16_t,__NOTHROW_NCX,toctrans16,(wint16_t __wc, wctrans_t __desc),towctrans,(__wc,__desc))
#elif defined(__CRT_HAVE___towctrans) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint16_t,__NOTHROW_NCX,toctrans16,(wint16_t __wc, wctrans_t __desc),__towctrans,(__wc,__desc))
#elif defined(__CRT_HAVE_DOS$__towctrans)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,wint16_t,__NOTHROW_NCX,toctrans16,(wint16_t __wc, wctrans_t __desc),__towctrans,(__wc,__desc))
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/towctrans.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint16_t __NOTHROW_NCX(__LIBDCALL toctrans16)(wint16_t __wc, wctrans_t __desc) { return (__WINT16_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towctrans))((__WINT_TYPE__)__wc, __desc); }
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
#include <libc/local/parts.uchar.wctype/toctrans16.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(toctrans16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint16_t __NOTHROW_NCX(__LIBDCALL toctrans16)(wint16_t __wc, wctrans_t __desc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(toctrans16))(__wc, __desc); })
#endif /* ... */
#if defined(__CRT_HAVE_towctrans) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint32_t,__NOTHROW_NCX,toctrans32,(wint32_t __wc, wctrans_t __desc),towctrans,(__wc,__desc))
#elif defined(__CRT_HAVE_KOS$towctrans)
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,wint32_t,__NOTHROW_NCX,toctrans32,(wint32_t __wc, wctrans_t __desc),towctrans,(__wc,__desc))
#elif defined(__CRT_HAVE___towctrans) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint32_t,__NOTHROW_NCX,toctrans32,(wint32_t __wc, wctrans_t __desc),__towctrans,(__wc,__desc))
#elif defined(__CRT_HAVE_KOS$__towctrans)
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,wint32_t,__NOTHROW_NCX,toctrans32,(wint32_t __wc, wctrans_t __desc),__towctrans,(__wc,__desc))
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/towctrans.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint32_t __NOTHROW_NCX(__LIBKCALL toctrans32)(wint32_t __wc, wctrans_t __desc) { return (__WINT32_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towctrans))((__WINT_TYPE__)__wc, __desc); }
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
#include <libc/local/parts.uchar.wctype/toctrans32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(toctrans32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint32_t __NOTHROW_NCX(__LIBKCALL toctrans32)(wint32_t __wc, wctrans_t __desc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(toctrans32))(__wc, __desc); })
#endif /* ... */
#endif /* __USE_ISOC99 */
#if defined(__CRT_HAVE_iswctype) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype16,(__WINT16_TYPE__ __wc, __wctype_t __desc),iswctype,(__wc,__desc))
#elif defined(__CRT_HAVE_DOS$iswctype)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype16,(__WINT16_TYPE__ __wc, __wctype_t __desc),iswctype,(__wc,__desc))
#elif defined(__CRT_HAVE_is_wctype) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype16,(__WINT16_TYPE__ __wc, __wctype_t __desc),is_wctype,(__wc,__desc))
#elif defined(__CRT_HAVE_DOS$is_wctype)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype16,(__WINT16_TYPE__ __wc, __wctype_t __desc),is_wctype,(__wc,__desc))
#elif defined(__CRT_HAVE___iswctype) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype16,(__WINT16_TYPE__ __wc, __wctype_t __desc),__iswctype,(__wc,__desc))
#elif defined(__CRT_HAVE_DOS$__iswctype)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype16,(__WINT16_TYPE__ __wc, __wctype_t __desc),__iswctype,(__wc,__desc))
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswctype.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isctype16)(__WINT16_TYPE__ __wc, __wctype_t __desc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswctype))((__WINT_TYPE__)__wc, __desc); }
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
#include <libc/local/parts.uchar.wctype/isctype16.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(isctype16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isctype16)(__WINT16_TYPE__ __wc, __wctype_t __desc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isctype16))(__wc, __desc); })
#endif /* ... */
#if defined(__CRT_HAVE_iswctype) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype32,(__WINT32_TYPE__ __wc, __wctype_t __desc),iswctype,(__wc,__desc))
#elif defined(__CRT_HAVE_KOS$iswctype)
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype32,(__WINT32_TYPE__ __wc, __wctype_t __desc),iswctype,(__wc,__desc))
#elif defined(__CRT_HAVE_is_wctype) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype32,(__WINT32_TYPE__ __wc, __wctype_t __desc),is_wctype,(__wc,__desc))
#elif defined(__CRT_HAVE_KOS$is_wctype)
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype32,(__WINT32_TYPE__ __wc, __wctype_t __desc),is_wctype,(__wc,__desc))
#elif defined(__CRT_HAVE___iswctype) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype32,(__WINT32_TYPE__ __wc, __wctype_t __desc),__iswctype,(__wc,__desc))
#elif defined(__CRT_HAVE_KOS$__iswctype)
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype32,(__WINT32_TYPE__ __wc, __wctype_t __desc),__iswctype,(__wc,__desc))
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswctype.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isctype32)(__WINT32_TYPE__ __wc, __wctype_t __desc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswctype))((__WINT_TYPE__)__wc, __desc); }
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
#include <libc/local/parts.uchar.wctype/isctype32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(isctype32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isctype32)(__WINT32_TYPE__ __wc, __wctype_t __desc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isctype32))(__wc, __desc); })
#endif /* ... */

#if defined(__USE_KOS) || defined(__USE_DOS)
#if defined(__CRT_HAVE_iswascii) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isascii16,(__WINT16_TYPE__ __wc),iswascii,(__wc))
#elif defined(__CRT_HAVE_DOS$iswascii)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isascii16,(__WINT16_TYPE__ __wc),iswascii,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswascii.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isascii16)(__WINT16_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswascii))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isascii16.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(isascii16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBDCALL isascii16)(__WINT16_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isascii16))(__wc); })
#endif /* !... */
#if defined(__CRT_HAVE_iswascii) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isascii32,(__WINT32_TYPE__ __wc),iswascii,(__wc))
#elif defined(__CRT_HAVE_KOS$iswascii)
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isascii32,(__WINT32_TYPE__ __wc),iswascii,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswascii.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isascii32)(__WINT32_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswascii))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isascii32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(isascii32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL isascii32)(__WINT32_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isascii32))(__wc); })
#endif /* !... */
#endif /* __USE_KOS || __USE_DOS */

#ifdef __USE_XOPEN2K8
#if defined(__crt_iswcntrl_l) && defined(__CRT_HAVE_iswcntrl_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswcntrl_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,iscntrl16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswcntrl_l,{ return __crt_iswcntrl_l(__ch, __locale); })
#elif defined(__crt_iswcntrl_l) && defined(__CRT_HAVE__iswcntrl_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswcntrl_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,iscntrl16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswcntrl_l,{ return __crt_iswcntrl_l(__ch, __locale); })
#elif defined(__crt_iswcntrl_l) && defined(__CRT_HAVE___iswcntrl_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswcntrl_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,iscntrl16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswcntrl_l,{ return __crt_iswcntrl_l(__ch, __locale); })
#elif defined(__crt_iswcntrl_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswcntrl_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL iscntrl16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return __crt_iswcntrl_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswcntrl_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswcntrl_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswcntrl_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$iswcntrl_l)
/* >> iswcntrl_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswcntrl_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswcntrl_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswcntrl_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswcntrl_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$_iswcntrl_l)
/* >> iswcntrl_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswcntrl_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswcntrl_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswcntrl_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswcntrl_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$__iswcntrl_l)
/* >> iswcntrl_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswcntrl_l,(__ch,__locale))
#elif defined(__crt_iswcntrl) && __SIZEOF_WCHAR_T__ == 2
/* >> iswcntrl_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL iscntrl16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswcntrl(__ch); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswcntrl_l.h>
/* >> iswcntrl_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL iscntrl16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswcntrl_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/iscntrl16_l.h>
/* >> iswcntrl_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iscntrl16_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL iscntrl16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iscntrl16_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswcntrl_l) && defined(__CRT_HAVE_iswcntrl_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswcntrl_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,iscntrl32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswcntrl_l,{ return __crt_iswcntrl_l(__ch, __locale); })
#elif defined(__crt_iswcntrl_l) && defined(__CRT_HAVE__iswcntrl_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswcntrl_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,iscntrl32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswcntrl_l,{ return __crt_iswcntrl_l(__ch, __locale); })
#elif defined(__crt_iswcntrl_l) && defined(__CRT_HAVE___iswcntrl_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswcntrl_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,iscntrl32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswcntrl_l,{ return __crt_iswcntrl_l(__ch, __locale); })
#elif defined(__crt_iswcntrl_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswcntrl_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL iscntrl32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return __crt_iswcntrl_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswcntrl_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswcntrl_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswcntrl_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$iswcntrl_l)
/* >> iswcntrl_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswcntrl_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswcntrl_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswcntrl_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswcntrl_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$_iswcntrl_l)
/* >> iswcntrl_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswcntrl_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswcntrl_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswcntrl_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswcntrl_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$__iswcntrl_l)
/* >> iswcntrl_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswcntrl_l,(__ch,__locale))
#elif defined(__crt_iswcntrl) && __SIZEOF_WCHAR_T__ == 4
/* >> iswcntrl_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL iscntrl32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswcntrl(__ch); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswcntrl_l.h>
/* >> iswcntrl_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL iscntrl32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswcntrl_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/iscntrl32_l.h>
/* >> iswcntrl_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iscntrl32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL iscntrl32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iscntrl32_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswspace_l) && defined(__CRT_HAVE_iswspace_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswspace_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isspace16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswspace_l,{ return __crt_iswspace_l(__ch, __locale); })
#elif defined(__crt_iswspace_l) && defined(__CRT_HAVE__iswspace_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswspace_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isspace16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswspace_l,{ return __crt_iswspace_l(__ch, __locale); })
#elif defined(__crt_iswspace_l) && defined(__CRT_HAVE___iswspace_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswspace_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isspace16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswspace_l,{ return __crt_iswspace_l(__ch, __locale); })
#elif defined(__crt_iswspace_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswspace_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isspace16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return __crt_iswspace_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswspace_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswspace_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswspace_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$iswspace_l)
/* >> iswspace_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswspace_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswspace_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswspace_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswspace_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$_iswspace_l)
/* >> iswspace_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswspace_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswspace_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswspace_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswspace_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$__iswspace_l)
/* >> iswspace_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswspace_l,(__ch,__locale))
#elif defined(__crt_iswspace) && __SIZEOF_WCHAR_T__ == 2
/* >> iswspace_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isspace16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswspace(__ch); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswspace_l.h>
/* >> iswspace_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isspace16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswspace_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isspace16_l.h>
/* >> iswspace_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isspace16_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isspace16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isspace16_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswspace_l) && defined(__CRT_HAVE_iswspace_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswspace_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isspace32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswspace_l,{ return __crt_iswspace_l(__ch, __locale); })
#elif defined(__crt_iswspace_l) && defined(__CRT_HAVE__iswspace_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswspace_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isspace32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswspace_l,{ return __crt_iswspace_l(__ch, __locale); })
#elif defined(__crt_iswspace_l) && defined(__CRT_HAVE___iswspace_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswspace_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isspace32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswspace_l,{ return __crt_iswspace_l(__ch, __locale); })
#elif defined(__crt_iswspace_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswspace_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isspace32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return __crt_iswspace_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswspace_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswspace_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswspace_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$iswspace_l)
/* >> iswspace_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswspace_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswspace_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswspace_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswspace_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$_iswspace_l)
/* >> iswspace_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswspace_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswspace_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswspace_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswspace_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$__iswspace_l)
/* >> iswspace_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswspace_l,(__ch,__locale))
#elif defined(__crt_iswspace) && __SIZEOF_WCHAR_T__ == 4
/* >> iswspace_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isspace32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswspace(__ch); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswspace_l.h>
/* >> iswspace_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isspace32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswspace_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isspace32_l.h>
/* >> iswspace_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isspace32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isspace32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isspace32_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswupper_l) && defined(__CRT_HAVE_iswupper_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswupper_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isupper16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswupper_l,{ return __crt_iswupper_l(__ch, __locale); })
#elif defined(__crt_iswupper_l) && defined(__CRT_HAVE__iswupper_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswupper_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isupper16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswupper_l,{ return __crt_iswupper_l(__ch, __locale); })
#elif defined(__crt_iswupper_l) && defined(__CRT_HAVE___iswupper_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswupper_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isupper16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswupper_l,{ return __crt_iswupper_l(__ch, __locale); })
#elif defined(__crt_iswupper_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isupper16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return __crt_iswupper_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswupper_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$iswupper_l)
/* >> iswupper_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswupper_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$_iswupper_l)
/* >> iswupper_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswupper_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$__iswupper_l)
/* >> iswupper_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswupper_l,(__ch,__locale))
#elif defined(__crt_iswupper) && __SIZEOF_WCHAR_T__ == 2
/* >> iswupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isupper16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswupper(__ch); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswupper_l.h>
/* >> iswupper_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isupper16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswupper_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isupper16_l.h>
/* >> iswupper_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isupper16_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isupper16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isupper16_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswupper_l) && defined(__CRT_HAVE_iswupper_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswupper_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswupper_l,{ return __crt_iswupper_l(__ch, __locale); })
#elif defined(__crt_iswupper_l) && defined(__CRT_HAVE__iswupper_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswupper_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswupper_l,{ return __crt_iswupper_l(__ch, __locale); })
#elif defined(__crt_iswupper_l) && defined(__CRT_HAVE___iswupper_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswupper_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswupper_l,{ return __crt_iswupper_l(__ch, __locale); })
#elif defined(__crt_iswupper_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isupper32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return __crt_iswupper_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswupper_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$iswupper_l)
/* >> iswupper_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswupper_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$_iswupper_l)
/* >> iswupper_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswupper_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$__iswupper_l)
/* >> iswupper_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswupper_l,(__ch,__locale))
#elif defined(__crt_iswupper) && __SIZEOF_WCHAR_T__ == 4
/* >> iswupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isupper32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswupper(__ch); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswupper_l.h>
/* >> iswupper_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isupper32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswupper_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isupper32_l.h>
/* >> iswupper_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isupper32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isupper32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isupper32_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswlower_l) && defined(__CRT_HAVE_iswlower_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswlower_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,islower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswlower_l,{ return __crt_iswlower_l(__ch, __locale); })
#elif defined(__crt_iswlower_l) && defined(__CRT_HAVE__iswlower_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswlower_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,islower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswlower_l,{ return __crt_iswlower_l(__ch, __locale); })
#elif defined(__crt_iswlower_l) && defined(__CRT_HAVE___iswlower_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswlower_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,islower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswlower_l,{ return __crt_iswlower_l(__ch, __locale); })
#elif defined(__crt_iswlower_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswlower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL islower16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return __crt_iswlower_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswlower_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$iswlower_l)
/* >> iswlower_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswlower_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$_iswlower_l)
/* >> iswlower_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswlower_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$__iswlower_l)
/* >> iswlower_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswlower_l,(__ch,__locale))
#elif defined(__crt_iswlower) && __SIZEOF_WCHAR_T__ == 2
/* >> iswlower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL islower16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswlower(__ch); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswlower_l.h>
/* >> iswlower_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL islower16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswlower_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/islower16_l.h>
/* >> iswlower_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(islower16_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL islower16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(islower16_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswlower_l) && defined(__CRT_HAVE_iswlower_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswlower_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,islower32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswlower_l,{ return __crt_iswlower_l(__ch, __locale); })
#elif defined(__crt_iswlower_l) && defined(__CRT_HAVE__iswlower_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswlower_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,islower32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswlower_l,{ return __crt_iswlower_l(__ch, __locale); })
#elif defined(__crt_iswlower_l) && defined(__CRT_HAVE___iswlower_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswlower_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,islower32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswlower_l,{ return __crt_iswlower_l(__ch, __locale); })
#elif defined(__crt_iswlower_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswlower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL islower32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return __crt_iswlower_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswlower_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$iswlower_l)
/* >> iswlower_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswlower_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$_iswlower_l)
/* >> iswlower_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswlower_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$__iswlower_l)
/* >> iswlower_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswlower_l,(__ch,__locale))
#elif defined(__crt_iswlower) && __SIZEOF_WCHAR_T__ == 4
/* >> iswlower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL islower32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswlower(__ch); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswlower_l.h>
/* >> iswlower_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL islower32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswlower_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/islower32_l.h>
/* >> iswlower_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(islower32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL islower32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(islower32_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswalpha_l) && defined(__CRT_HAVE_iswalpha_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswalpha_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isalpha16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswalpha_l,{ return __crt_iswalpha_l(__ch, __locale); })
#elif defined(__crt_iswalpha_l) && defined(__CRT_HAVE__iswalpha_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswalpha_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isalpha16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswalpha_l,{ return __crt_iswalpha_l(__ch, __locale); })
#elif defined(__crt_iswalpha_l) && defined(__CRT_HAVE___iswalpha_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswalpha_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isalpha16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswalpha_l,{ return __crt_iswalpha_l(__ch, __locale); })
#elif defined(__crt_iswalpha_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswalpha_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isalpha16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return __crt_iswalpha_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswalpha_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswalpha_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$iswalpha_l)
/* >> iswalpha_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswalpha_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswalpha_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$_iswalpha_l)
/* >> iswalpha_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswalpha_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswalpha_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$__iswalpha_l)
/* >> iswalpha_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswalpha_l,(__ch,__locale))
#elif defined(__crt_iswalpha) && __SIZEOF_WCHAR_T__ == 2
/* >> iswalpha_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isalpha16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswalpha(__ch); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswalpha_l.h>
/* >> iswalpha_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isalpha16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalpha_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isalpha16_l.h>
/* >> iswalpha_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isalpha16_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isalpha16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalpha16_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswalpha_l) && defined(__CRT_HAVE_iswalpha_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswalpha_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isalpha32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswalpha_l,{ return __crt_iswalpha_l(__ch, __locale); })
#elif defined(__crt_iswalpha_l) && defined(__CRT_HAVE__iswalpha_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswalpha_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isalpha32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswalpha_l,{ return __crt_iswalpha_l(__ch, __locale); })
#elif defined(__crt_iswalpha_l) && defined(__CRT_HAVE___iswalpha_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswalpha_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isalpha32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswalpha_l,{ return __crt_iswalpha_l(__ch, __locale); })
#elif defined(__crt_iswalpha_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswalpha_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isalpha32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return __crt_iswalpha_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswalpha_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswalpha_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$iswalpha_l)
/* >> iswalpha_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswalpha_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswalpha_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$_iswalpha_l)
/* >> iswalpha_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswalpha_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswalpha_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$__iswalpha_l)
/* >> iswalpha_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswalpha_l,(__ch,__locale))
#elif defined(__crt_iswalpha) && __SIZEOF_WCHAR_T__ == 4
/* >> iswalpha_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isalpha32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswalpha(__ch); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswalpha_l.h>
/* >> iswalpha_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isalpha32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalpha_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isalpha32_l.h>
/* >> iswalpha_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isalpha32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isalpha32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalpha32_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswdigit_l) && defined(__CRT_HAVE_iswdigit_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswdigit_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isdigit16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswdigit_l,{ return __crt_iswdigit_l(__ch, __locale); })
#elif defined(__crt_iswdigit_l) && defined(__CRT_HAVE__iswdigit_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswdigit_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isdigit16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswdigit_l,{ return __crt_iswdigit_l(__ch, __locale); })
#elif defined(__crt_iswdigit_l) && defined(__CRT_HAVE___iswdigit_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswdigit_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isdigit16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswdigit_l,{ return __crt_iswdigit_l(__ch, __locale); })
#elif defined(__crt_iswdigit_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isdigit16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return __crt_iswdigit_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswdigit_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$iswdigit_l)
/* >> iswdigit_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswdigit_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$_iswdigit_l)
/* >> iswdigit_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswdigit_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$__iswdigit_l)
/* >> iswdigit_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswdigit_l,(__ch,__locale))
#elif defined(__crt_iswdigit) && __SIZEOF_WCHAR_T__ == 2
/* >> iswdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isdigit16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswdigit(__ch); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswdigit_l.h>
/* >> iswdigit_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isdigit16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswdigit_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isdigit16_l.h>
/* >> iswdigit_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isdigit16_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isdigit16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isdigit16_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswdigit_l) && defined(__CRT_HAVE_iswdigit_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswdigit_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isdigit32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswdigit_l,{ return __crt_iswdigit_l(__ch, __locale); })
#elif defined(__crt_iswdigit_l) && defined(__CRT_HAVE__iswdigit_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswdigit_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isdigit32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswdigit_l,{ return __crt_iswdigit_l(__ch, __locale); })
#elif defined(__crt_iswdigit_l) && defined(__CRT_HAVE___iswdigit_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswdigit_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isdigit32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswdigit_l,{ return __crt_iswdigit_l(__ch, __locale); })
#elif defined(__crt_iswdigit_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isdigit32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return __crt_iswdigit_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswdigit_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$iswdigit_l)
/* >> iswdigit_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswdigit_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$_iswdigit_l)
/* >> iswdigit_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswdigit_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$__iswdigit_l)
/* >> iswdigit_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswdigit_l,(__ch,__locale))
#elif defined(__crt_iswdigit) && __SIZEOF_WCHAR_T__ == 4
/* >> iswdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isdigit32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswdigit(__ch); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswdigit_l.h>
/* >> iswdigit_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isdigit32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswdigit_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isdigit32_l.h>
/* >> iswdigit_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isdigit32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isdigit32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isdigit32_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswxdigit_l) && defined(__CRT_HAVE_iswxdigit_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswxdigit_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isxdigit16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswxdigit_l,{ return __crt_iswxdigit_l(__ch, __locale); })
#elif defined(__crt_iswxdigit_l) && defined(__CRT_HAVE__iswxdigit_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswxdigit_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isxdigit16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswxdigit_l,{ return __crt_iswxdigit_l(__ch, __locale); })
#elif defined(__crt_iswxdigit_l) && defined(__CRT_HAVE___iswxdigit_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswxdigit_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isxdigit16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswxdigit_l,{ return __crt_iswxdigit_l(__ch, __locale); })
#elif defined(__crt_iswxdigit_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswxdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isxdigit16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return __crt_iswxdigit_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswxdigit_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswxdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswxdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$iswxdigit_l)
/* >> iswxdigit_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswxdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswxdigit_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswxdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswxdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$_iswxdigit_l)
/* >> iswxdigit_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswxdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswxdigit_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswxdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswxdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$__iswxdigit_l)
/* >> iswxdigit_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswxdigit_l,(__ch,__locale))
#elif defined(__crt_iswxdigit) && __SIZEOF_WCHAR_T__ == 2
/* >> iswxdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isxdigit16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswxdigit(__ch); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswxdigit_l.h>
/* >> iswxdigit_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isxdigit16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswxdigit_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isxdigit16_l.h>
/* >> iswxdigit_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isxdigit16_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isxdigit16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isxdigit16_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswxdigit_l) && defined(__CRT_HAVE_iswxdigit_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswxdigit_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isxdigit32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswxdigit_l,{ return __crt_iswxdigit_l(__ch, __locale); })
#elif defined(__crt_iswxdigit_l) && defined(__CRT_HAVE__iswxdigit_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswxdigit_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isxdigit32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswxdigit_l,{ return __crt_iswxdigit_l(__ch, __locale); })
#elif defined(__crt_iswxdigit_l) && defined(__CRT_HAVE___iswxdigit_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswxdigit_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isxdigit32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswxdigit_l,{ return __crt_iswxdigit_l(__ch, __locale); })
#elif defined(__crt_iswxdigit_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswxdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isxdigit32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return __crt_iswxdigit_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswxdigit_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswxdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswxdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$iswxdigit_l)
/* >> iswxdigit_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswxdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswxdigit_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswxdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswxdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$_iswxdigit_l)
/* >> iswxdigit_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswxdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswxdigit_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswxdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswxdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$__iswxdigit_l)
/* >> iswxdigit_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswxdigit_l,(__ch,__locale))
#elif defined(__crt_iswxdigit) && __SIZEOF_WCHAR_T__ == 4
/* >> iswxdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isxdigit32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswxdigit(__ch); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswxdigit_l.h>
/* >> iswxdigit_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isxdigit32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswxdigit_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isxdigit32_l.h>
/* >> iswxdigit_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isxdigit32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isxdigit32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isxdigit32_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswalnum_l) && defined(__CRT_HAVE_iswalnum_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswalnum_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isalnum16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswalnum_l,{ return __crt_iswalnum_l(__ch, __locale); })
#elif defined(__crt_iswalnum_l) && defined(__CRT_HAVE__iswalnum_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswalnum_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isalnum16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswalnum_l,{ return __crt_iswalnum_l(__ch, __locale); })
#elif defined(__crt_iswalnum_l) && defined(__CRT_HAVE___iswalnum_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswalnum_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isalnum16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswalnum_l,{ return __crt_iswalnum_l(__ch, __locale); })
#elif defined(__crt_iswalnum_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswalnum_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isalnum16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return __crt_iswalnum_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswalnum_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswalnum_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$iswalnum_l)
/* >> iswalnum_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswalnum_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswalnum_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$_iswalnum_l)
/* >> iswalnum_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswalnum_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswalnum_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$__iswalnum_l)
/* >> iswalnum_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswalnum_l,(__ch,__locale))
#elif defined(__crt_iswalnum) && __SIZEOF_WCHAR_T__ == 2
/* >> iswalnum_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isalnum16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswalnum(__ch); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswalnum_l.h>
/* >> iswalnum_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isalnum16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalnum_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isalnum16_l.h>
/* >> iswalnum_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isalnum16_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isalnum16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalnum16_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswalnum_l) && defined(__CRT_HAVE_iswalnum_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswalnum_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isalnum32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswalnum_l,{ return __crt_iswalnum_l(__ch, __locale); })
#elif defined(__crt_iswalnum_l) && defined(__CRT_HAVE__iswalnum_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswalnum_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isalnum32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswalnum_l,{ return __crt_iswalnum_l(__ch, __locale); })
#elif defined(__crt_iswalnum_l) && defined(__CRT_HAVE___iswalnum_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswalnum_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isalnum32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswalnum_l,{ return __crt_iswalnum_l(__ch, __locale); })
#elif defined(__crt_iswalnum_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswalnum_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isalnum32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return __crt_iswalnum_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswalnum_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswalnum_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$iswalnum_l)
/* >> iswalnum_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswalnum_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswalnum_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$_iswalnum_l)
/* >> iswalnum_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswalnum_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswalnum_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$__iswalnum_l)
/* >> iswalnum_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswalnum_l,(__ch,__locale))
#elif defined(__crt_iswalnum) && __SIZEOF_WCHAR_T__ == 4
/* >> iswalnum_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isalnum32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswalnum(__ch); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswalnum_l.h>
/* >> iswalnum_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isalnum32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalnum_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isalnum32_l.h>
/* >> iswalnum_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isalnum32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isalnum32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalnum32_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswpunct_l) && defined(__CRT_HAVE_iswpunct_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswpunct_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,ispunct16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswpunct_l,{ return __crt_iswpunct_l(__ch, __locale); })
#elif defined(__crt_iswpunct_l) && defined(__CRT_HAVE__iswpunct_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswpunct_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,ispunct16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswpunct_l,{ return __crt_iswpunct_l(__ch, __locale); })
#elif defined(__crt_iswpunct_l) && defined(__CRT_HAVE___iswpunct_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswpunct_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,ispunct16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswpunct_l,{ return __crt_iswpunct_l(__ch, __locale); })
#elif defined(__crt_iswpunct_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswpunct_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL ispunct16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return __crt_iswpunct_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswpunct_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswpunct_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswpunct_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$iswpunct_l)
/* >> iswpunct_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswpunct_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswpunct_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswpunct_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswpunct_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$_iswpunct_l)
/* >> iswpunct_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswpunct_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswpunct_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswpunct_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswpunct_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$__iswpunct_l)
/* >> iswpunct_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswpunct_l,(__ch,__locale))
#elif defined(__crt_iswpunct) && __SIZEOF_WCHAR_T__ == 2
/* >> iswpunct_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL ispunct16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswpunct(__ch); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswpunct_l.h>
/* >> iswpunct_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL ispunct16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswpunct_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/ispunct16_l.h>
/* >> iswpunct_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(ispunct16_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL ispunct16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ispunct16_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswpunct_l) && defined(__CRT_HAVE_iswpunct_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswpunct_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,ispunct32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswpunct_l,{ return __crt_iswpunct_l(__ch, __locale); })
#elif defined(__crt_iswpunct_l) && defined(__CRT_HAVE__iswpunct_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswpunct_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,ispunct32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswpunct_l,{ return __crt_iswpunct_l(__ch, __locale); })
#elif defined(__crt_iswpunct_l) && defined(__CRT_HAVE___iswpunct_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswpunct_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,ispunct32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswpunct_l,{ return __crt_iswpunct_l(__ch, __locale); })
#elif defined(__crt_iswpunct_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswpunct_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL ispunct32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return __crt_iswpunct_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswpunct_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswpunct_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswpunct_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$iswpunct_l)
/* >> iswpunct_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswpunct_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswpunct_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswpunct_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswpunct_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$_iswpunct_l)
/* >> iswpunct_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswpunct_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswpunct_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswpunct_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswpunct_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$__iswpunct_l)
/* >> iswpunct_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswpunct_l,(__ch,__locale))
#elif defined(__crt_iswpunct) && __SIZEOF_WCHAR_T__ == 4
/* >> iswpunct_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL ispunct32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswpunct(__ch); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswpunct_l.h>
/* >> iswpunct_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL ispunct32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswpunct_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/ispunct32_l.h>
/* >> iswpunct_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(ispunct32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL ispunct32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ispunct32_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswgraph_l) && defined(__CRT_HAVE_iswgraph_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswgraph_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isgraph16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswgraph_l,{ return __crt_iswgraph_l(__ch, __locale); })
#elif defined(__crt_iswgraph_l) && defined(__CRT_HAVE__iswgraph_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswgraph_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isgraph16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswgraph_l,{ return __crt_iswgraph_l(__ch, __locale); })
#elif defined(__crt_iswgraph_l) && defined(__CRT_HAVE___iswgraph_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswgraph_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isgraph16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswgraph_l,{ return __crt_iswgraph_l(__ch, __locale); })
#elif defined(__crt_iswgraph_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswgraph_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isgraph16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return __crt_iswgraph_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswgraph_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswgraph_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswgraph_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$iswgraph_l)
/* >> iswgraph_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswgraph_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswgraph_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswgraph_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswgraph_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$_iswgraph_l)
/* >> iswgraph_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswgraph_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswgraph_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswgraph_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswgraph_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$__iswgraph_l)
/* >> iswgraph_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswgraph_l,(__ch,__locale))
#elif defined(__crt_iswgraph) && __SIZEOF_WCHAR_T__ == 2
/* >> iswgraph_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isgraph16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswgraph(__ch); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswgraph_l.h>
/* >> iswgraph_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isgraph16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswgraph_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isgraph16_l.h>
/* >> iswgraph_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isgraph16_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isgraph16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isgraph16_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswgraph_l) && defined(__CRT_HAVE_iswgraph_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswgraph_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isgraph32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswgraph_l,{ return __crt_iswgraph_l(__ch, __locale); })
#elif defined(__crt_iswgraph_l) && defined(__CRT_HAVE__iswgraph_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswgraph_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isgraph32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswgraph_l,{ return __crt_iswgraph_l(__ch, __locale); })
#elif defined(__crt_iswgraph_l) && defined(__CRT_HAVE___iswgraph_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswgraph_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isgraph32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswgraph_l,{ return __crt_iswgraph_l(__ch, __locale); })
#elif defined(__crt_iswgraph_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswgraph_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isgraph32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return __crt_iswgraph_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswgraph_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswgraph_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswgraph_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$iswgraph_l)
/* >> iswgraph_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswgraph_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswgraph_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswgraph_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswgraph_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$_iswgraph_l)
/* >> iswgraph_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswgraph_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswgraph_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswgraph_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswgraph_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$__iswgraph_l)
/* >> iswgraph_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswgraph_l,(__ch,__locale))
#elif defined(__crt_iswgraph) && __SIZEOF_WCHAR_T__ == 4
/* >> iswgraph_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isgraph32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswgraph(__ch); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswgraph_l.h>
/* >> iswgraph_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isgraph32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswgraph_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isgraph32_l.h>
/* >> iswgraph_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isgraph32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isgraph32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isgraph32_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswprint_l) && defined(__CRT_HAVE_iswprint_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswprint_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isprint16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswprint_l,{ return __crt_iswprint_l(__ch, __locale); })
#elif defined(__crt_iswprint_l) && defined(__CRT_HAVE__iswprint_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswprint_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isprint16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswprint_l,{ return __crt_iswprint_l(__ch, __locale); })
#elif defined(__crt_iswprint_l) && defined(__CRT_HAVE___iswprint_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswprint_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isprint16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswprint_l,{ return __crt_iswprint_l(__ch, __locale); })
#elif defined(__crt_iswprint_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswprint_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isprint16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return __crt_iswprint_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswprint_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswprint_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$iswprint_l)
/* >> iswprint_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswprint_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswprint_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$_iswprint_l)
/* >> iswprint_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswprint_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswprint_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$__iswprint_l)
/* >> iswprint_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswprint_l,(__ch,__locale))
#elif defined(__crt_iswprint) && __SIZEOF_WCHAR_T__ == 2
/* >> iswprint_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isprint16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswprint(__ch); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswprint_l.h>
/* >> iswprint_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isprint16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswprint_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isprint16_l.h>
/* >> iswprint_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isprint16_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isprint16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isprint16_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswprint_l) && defined(__CRT_HAVE_iswprint_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswprint_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isprint32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswprint_l,{ return __crt_iswprint_l(__ch, __locale); })
#elif defined(__crt_iswprint_l) && defined(__CRT_HAVE__iswprint_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswprint_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isprint32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswprint_l,{ return __crt_iswprint_l(__ch, __locale); })
#elif defined(__crt_iswprint_l) && defined(__CRT_HAVE___iswprint_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswprint_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isprint32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswprint_l,{ return __crt_iswprint_l(__ch, __locale); })
#elif defined(__crt_iswprint_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswprint_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isprint32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return __crt_iswprint_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswprint_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswprint_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$iswprint_l)
/* >> iswprint_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswprint_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswprint_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$_iswprint_l)
/* >> iswprint_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswprint_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswprint_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$__iswprint_l)
/* >> iswprint_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswprint_l,(__ch,__locale))
#elif defined(__crt_iswprint) && __SIZEOF_WCHAR_T__ == 4
/* >> iswprint_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isprint32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswprint(__ch); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswprint_l.h>
/* >> iswprint_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isprint32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswprint_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isprint32_l.h>
/* >> iswprint_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isprint32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isprint32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isprint32_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswblank_l) && defined(__CRT_HAVE_iswblank_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswblank_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isblank16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswblank_l,{ return __crt_iswblank_l(__ch, __locale); })
#elif defined(__crt_iswblank_l) && defined(__CRT_HAVE__iswblank_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswblank_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isblank16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswblank_l,{ return __crt_iswblank_l(__ch, __locale); })
#elif defined(__crt_iswblank_l) && defined(__CRT_HAVE___iswblank_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswblank_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,isblank16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswblank_l,{ return __crt_iswblank_l(__ch, __locale); })
#elif defined(__crt_iswblank_l) && __SIZEOF_WCHAR_T__ == 2
/* >> iswblank_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isblank16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return __crt_iswblank_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswblank_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswblank_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswblank_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$iswblank_l)
/* >> iswblank_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswblank_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswblank_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswblank_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswblank_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$_iswblank_l)
/* >> iswblank_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswblank_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswblank_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswblank_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswblank_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$__iswblank_l)
/* >> iswblank_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswblank_l,(__ch,__locale))
#elif defined(__crt_iswblank) && __SIZEOF_WCHAR_T__ == 2
/* >> iswblank_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isblank16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswblank(__ch); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswblank_l.h>
/* >> iswblank_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isblank16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswblank_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isblank16_l.h>
/* >> iswblank_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isblank16_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isblank16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isblank16_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswblank_l) && defined(__CRT_HAVE_iswblank_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswblank_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isblank32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswblank_l,{ return __crt_iswblank_l(__ch, __locale); })
#elif defined(__crt_iswblank_l) && defined(__CRT_HAVE__iswblank_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswblank_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isblank32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswblank_l,{ return __crt_iswblank_l(__ch, __locale); })
#elif defined(__crt_iswblank_l) && defined(__CRT_HAVE___iswblank_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswblank_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBKCALL,isblank32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswblank_l,{ return __crt_iswblank_l(__ch, __locale); })
#elif defined(__crt_iswblank_l) && __SIZEOF_WCHAR_T__ == 4
/* >> iswblank_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isblank32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return __crt_iswblank_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswblank_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswblank_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswblank_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$iswblank_l)
/* >> iswblank_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),iswblank_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswblank_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswblank_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswblank_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$_iswblank_l)
/* >> iswblank_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_iswblank_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswblank_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswblank_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswblank_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$__iswblank_l)
/* >> iswblank_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__iswblank_l,(__ch,__locale))
#elif defined(__crt_iswblank) && __SIZEOF_WCHAR_T__ == 4
/* >> iswblank_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isblank32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswblank(__ch); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswblank_l.h>
/* >> iswblank_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isblank32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswblank_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/isblank32_l.h>
/* >> iswblank_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isblank32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isblank32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isblank32_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_towlower_l) && defined(__CRT_HAVE_towlower_l) && __SIZEOF_WCHAR_T__ == 2
/* >> towlower_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,__LIBDCALL,tolower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),towlower_l,{ return __crt_towlower_l(__ch, __locale); })
#elif defined(__crt_towlower_l) && defined(__CRT_HAVE__towlower_l) && __SIZEOF_WCHAR_T__ == 2
/* >> towlower_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,__LIBDCALL,tolower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_towlower_l,{ return __crt_towlower_l(__ch, __locale); })
#elif defined(__crt_towlower_l) && defined(__CRT_HAVE___towlower_l) && __SIZEOF_WCHAR_T__ == 2
/* >> towlower_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,__LIBDCALL,tolower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__towlower_l,{ return __crt_towlower_l(__ch, __locale); })
#elif defined(__crt_towlower_l) && __SIZEOF_WCHAR_T__ == 2
/* >> towlower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT16_TYPE__ __NOTHROW_NCX(__LIBDCALL tolower16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return __crt_towlower_l(__ch, __locale); }
#elif defined(__CRT_HAVE_towlower_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> towlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,tolower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$towlower_l)
/* >> towlower_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,tolower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE__towlower_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> towlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,tolower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$_towlower_l)
/* >> towlower_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,tolower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE___towlower_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> towlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,tolower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$__towlower_l)
/* >> towlower_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,tolower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__towlower_l,(__ch,__locale))
#elif defined(__crt_towlower) && __SIZEOF_WCHAR_T__ == 2
/* >> towlower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT16_TYPE__ __NOTHROW_NCX(__LIBDCALL tolower16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_towlower(__ch); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/towlower_l.h>
/* >> towlower_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __WINT16_TYPE__ __NOTHROW_NCX(__LIBDCALL tolower16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__WINT16_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towlower_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/tolower16_l.h>
/* >> towlower_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(tolower16_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __WINT16_TYPE__ __NOTHROW_NCX(__LIBDCALL tolower16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tolower16_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_towlower_l) && defined(__CRT_HAVE_towlower_l) && __SIZEOF_WCHAR_T__ == 4
/* >> towlower_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,__LIBKCALL,tolower32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),towlower_l,{ return __crt_towlower_l(__ch, __locale); })
#elif defined(__crt_towlower_l) && defined(__CRT_HAVE__towlower_l) && __SIZEOF_WCHAR_T__ == 4
/* >> towlower_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,__LIBKCALL,tolower32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_towlower_l,{ return __crt_towlower_l(__ch, __locale); })
#elif defined(__crt_towlower_l) && defined(__CRT_HAVE___towlower_l) && __SIZEOF_WCHAR_T__ == 4
/* >> towlower_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,__LIBKCALL,tolower32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__towlower_l,{ return __crt_towlower_l(__ch, __locale); })
#elif defined(__crt_towlower_l) && __SIZEOF_WCHAR_T__ == 4
/* >> towlower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL tolower32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return __crt_towlower_l(__ch, __locale); }
#elif defined(__CRT_HAVE_towlower_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> towlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,tolower32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$towlower_l)
/* >> towlower_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,tolower32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE__towlower_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> towlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,tolower32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$_towlower_l)
/* >> towlower_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,tolower32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE___towlower_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> towlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,tolower32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$__towlower_l)
/* >> towlower_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,tolower32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__towlower_l,(__ch,__locale))
#elif defined(__crt_towlower) && __SIZEOF_WCHAR_T__ == 4
/* >> towlower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL tolower32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_towlower(__ch); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/towlower_l.h>
/* >> towlower_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __WINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL tolower32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__WINT32_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towlower_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/tolower32_l.h>
/* >> towlower_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(tolower32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __WINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL tolower32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tolower32_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_towupper_l) && defined(__CRT_HAVE_towupper_l) && __SIZEOF_WCHAR_T__ == 2
/* >> towupper_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,__LIBDCALL,toupper16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),towupper_l,{ return __crt_towupper_l(__ch, __locale); })
#elif defined(__crt_towupper_l) && defined(__CRT_HAVE__towupper_l) && __SIZEOF_WCHAR_T__ == 2
/* >> towupper_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,__LIBDCALL,toupper16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_towupper_l,{ return __crt_towupper_l(__ch, __locale); })
#elif defined(__crt_towupper_l) && defined(__CRT_HAVE___towupper_l) && __SIZEOF_WCHAR_T__ == 2
/* >> towupper_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,__LIBDCALL,toupper16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__towupper_l,{ return __crt_towupper_l(__ch, __locale); })
#elif defined(__crt_towupper_l) && __SIZEOF_WCHAR_T__ == 2
/* >> towupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT16_TYPE__ __NOTHROW_NCX(__LIBDCALL toupper16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return __crt_towupper_l(__ch, __locale); }
#elif defined(__CRT_HAVE_towupper_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> towupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,toupper16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$towupper_l)
/* >> towupper_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,toupper16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE__towupper_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> towupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,toupper16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$_towupper_l)
/* >> towupper_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,toupper16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE___towupper_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> towupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,toupper16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$__towupper_l)
/* >> towupper_l(3) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,toupper16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__towupper_l,(__ch,__locale))
#elif defined(__crt_towupper) && __SIZEOF_WCHAR_T__ == 2
/* >> towupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT16_TYPE__ __NOTHROW_NCX(__LIBDCALL toupper16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_towupper(__ch); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/towupper_l.h>
/* >> towupper_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __WINT16_TYPE__ __NOTHROW_NCX(__LIBDCALL toupper16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__WINT16_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towupper_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/toupper16_l.h>
/* >> towupper_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(toupper16_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __WINT16_TYPE__ __NOTHROW_NCX(__LIBDCALL toupper16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(toupper16_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_towupper_l) && defined(__CRT_HAVE_towupper_l) && __SIZEOF_WCHAR_T__ == 4
/* >> towupper_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,__LIBKCALL,toupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),towupper_l,{ return __crt_towupper_l(__ch, __locale); })
#elif defined(__crt_towupper_l) && defined(__CRT_HAVE__towupper_l) && __SIZEOF_WCHAR_T__ == 4
/* >> towupper_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,__LIBKCALL,toupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_towupper_l,{ return __crt_towupper_l(__ch, __locale); })
#elif defined(__crt_towupper_l) && defined(__CRT_HAVE___towupper_l) && __SIZEOF_WCHAR_T__ == 4
/* >> towupper_l(3) */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,__LIBKCALL,toupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__towupper_l,{ return __crt_towupper_l(__ch, __locale); })
#elif defined(__crt_towupper_l) && __SIZEOF_WCHAR_T__ == 4
/* >> towupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL toupper32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return __crt_towupper_l(__ch, __locale); }
#elif defined(__CRT_HAVE_towupper_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> towupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,toupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$towupper_l)
/* >> towupper_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,toupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE__towupper_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> towupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,toupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$_towupper_l)
/* >> towupper_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,toupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE___towupper_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> towupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,toupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$__towupper_l)
/* >> towupper_l(3) */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,toupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__towupper_l,(__ch,__locale))
#elif defined(__crt_towupper) && __SIZEOF_WCHAR_T__ == 4
/* >> towupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL toupper32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_towupper(__ch); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/towupper_l.h>
/* >> towupper_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __WINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL toupper32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__WINT32_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towupper_l))((__WINT_TYPE__)__ch, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/toupper32_l.h>
/* >> towupper_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(toupper32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __WINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL toupper32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(toupper32_l))(__ch, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_iswctype_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype16_l,(__WINT16_TYPE__ __wc, __wctype_t __type, __locale_t __locale),iswctype_l,(__wc,__type,__locale))
#elif defined(__CRT_HAVE_DOS$iswctype_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype16_l,(__WINT16_TYPE__ __wc, __wctype_t __type, __locale_t __locale),iswctype_l,(__wc,__type,__locale))
#elif defined(__CRT_HAVE__iswctype_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype16_l,(__WINT16_TYPE__ __wc, __wctype_t __type, __locale_t __locale),_iswctype_l,(__wc,__type,__locale))
#elif defined(__CRT_HAVE_DOS$_iswctype_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype16_l,(__WINT16_TYPE__ __wc, __wctype_t __type, __locale_t __locale),_iswctype_l,(__wc,__type,__locale))
#elif defined(__CRT_HAVE___iswctype_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype16_l,(__WINT16_TYPE__ __wc, __wctype_t __type, __locale_t __locale),__iswctype_l,(__wc,__type,__locale))
#elif defined(__CRT_HAVE_DOS$__iswctype_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype16_l,(__WINT16_TYPE__ __wc, __wctype_t __type, __locale_t __locale),__iswctype_l,(__wc,__type,__locale))
#elif (defined(__CRT_HAVE_iswctype) || defined(__CRT_HAVE_is_wctype) || defined(__CRT_HAVE___iswctype) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswctype_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isctype16_l)(__WINT16_TYPE__ __wc, __wctype_t __type, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswctype_l))((__WINT_TYPE__)__wc, __type, __locale); }
#elif (defined(__CRT_HAVE_iswctype) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$iswctype) || (defined(__CRT_HAVE_is_wctype) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$is_wctype) || (defined(__CRT_HAVE___iswctype) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$__iswctype) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))
#include <libc/local/parts.uchar.wctype/isctype16_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(isctype16_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL isctype16_l)(__WINT16_TYPE__ __wc, __wctype_t __type, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isctype16_l))(__wc, __type, __locale); })
#endif /* ... */
#if defined(__CRT_HAVE_iswctype_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype32_l,(__WINT32_TYPE__ __wc, __wctype_t __type, __locale_t __locale),iswctype_l,(__wc,__type,__locale))
#elif defined(__CRT_HAVE_KOS$iswctype_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype32_l,(__WINT32_TYPE__ __wc, __wctype_t __type, __locale_t __locale),iswctype_l,(__wc,__type,__locale))
#elif defined(__CRT_HAVE__iswctype_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype32_l,(__WINT32_TYPE__ __wc, __wctype_t __type, __locale_t __locale),_iswctype_l,(__wc,__type,__locale))
#elif defined(__CRT_HAVE_KOS$_iswctype_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype32_l,(__WINT32_TYPE__ __wc, __wctype_t __type, __locale_t __locale),_iswctype_l,(__wc,__type,__locale))
#elif defined(__CRT_HAVE___iswctype_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype32_l,(__WINT32_TYPE__ __wc, __wctype_t __type, __locale_t __locale),__iswctype_l,(__wc,__type,__locale))
#elif defined(__CRT_HAVE_KOS$__iswctype_l)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isctype32_l,(__WINT32_TYPE__ __wc, __wctype_t __type, __locale_t __locale),__iswctype_l,(__wc,__type,__locale))
#elif (defined(__CRT_HAVE_iswctype) || defined(__CRT_HAVE_is_wctype) || defined(__CRT_HAVE___iswctype) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswctype_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isctype32_l)(__WINT32_TYPE__ __wc, __wctype_t __type, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswctype_l))((__WINT_TYPE__)__wc, __type, __locale); }
#elif (defined(__CRT_HAVE_iswctype) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$iswctype) || (defined(__CRT_HAVE_is_wctype) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$is_wctype) || (defined(__CRT_HAVE___iswctype) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$__iswctype) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))
#include <libc/local/parts.uchar.wctype/isctype32_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(isctype32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL isctype32_l)(__WINT32_TYPE__ __wc, __wctype_t __type, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isctype32_l))(__wc, __type, __locale); })
#endif /* ... */
#if defined(__CRT_HAVE_towctrans_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,toctrans16_l,(__WINT16_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale),towctrans_l,(__wc,__desc,__locale))
#elif defined(__CRT_HAVE_DOS$towctrans_l)
__CREDIRECT_DOS(__ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,toctrans16_l,(__WINT16_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale),towctrans_l,(__wc,__desc,__locale))
#elif defined(__CRT_HAVE___towctrans_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,toctrans16_l,(__WINT16_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale),__towctrans_l,(__wc,__desc,__locale))
#elif defined(__CRT_HAVE_DOS$__towctrans_l)
__CREDIRECT_DOS(__ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,toctrans16_l,(__WINT16_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale),__towctrans_l,(__wc,__desc,__locale))
#elif (defined(__CRT_HAVE_towctrans) || defined(__CRT_HAVE___towctrans) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/towctrans_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __WINT16_TYPE__ __NOTHROW_NCX(__LIBDCALL toctrans16_l)(__WINT16_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale) { return (__WINT16_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towctrans_l))((__WINT_TYPE__)__wc, __desc, __locale); }
#elif (defined(__CRT_HAVE_towctrans) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$towctrans) || (defined(__CRT_HAVE___towctrans) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$__towctrans) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))
#include <libc/local/parts.uchar.wctype/toctrans16_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(toctrans16_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __WINT16_TYPE__ __NOTHROW_NCX(__LIBDCALL toctrans16_l)(__WINT16_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(toctrans16_l))(__wc, __desc, __locale); })
#endif /* ... */
#if defined(__CRT_HAVE_towctrans_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,toctrans32_l,(__WINT32_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale),towctrans_l,(__wc,__desc,__locale))
#elif defined(__CRT_HAVE_KOS$towctrans_l)
__CREDIRECT_KOS(__ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,toctrans32_l,(__WINT32_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale),towctrans_l,(__wc,__desc,__locale))
#elif defined(__CRT_HAVE___towctrans_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,toctrans32_l,(__WINT32_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale),__towctrans_l,(__wc,__desc,__locale))
#elif defined(__CRT_HAVE_KOS$__towctrans_l)
__CREDIRECT_KOS(__ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,toctrans32_l,(__WINT32_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale),__towctrans_l,(__wc,__desc,__locale))
#elif (defined(__CRT_HAVE_towctrans) || defined(__CRT_HAVE___towctrans) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/towctrans_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __WINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL toctrans32_l)(__WINT32_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale) { return (__WINT32_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towctrans_l))((__WINT_TYPE__)__wc, __desc, __locale); }
#elif (defined(__CRT_HAVE_towctrans) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$towctrans) || (defined(__CRT_HAVE___towctrans) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$__towctrans) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))
#include <libc/local/parts.uchar.wctype/toctrans32_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(toctrans32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __WINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL toctrans32_l)(__WINT32_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(toctrans32_l))(__wc, __desc, __locale); })
#endif /* ... */
#endif /* __USE_XOPEN2K8 */
#ifdef __USE_KOS
#if defined(__CRT_HAVE___iswcsymf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,issymstrt16,(__WINT16_TYPE__ __wc),__iswcsymf,(__wc))
#elif defined(__CRT_HAVE_DOS$__iswcsymf)
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,issymstrt16,(__WINT16_TYPE__ __wc),__iswcsymf,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswsymstrt.h>
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL issymstrt16)(__WINT16_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswsymstrt))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/issymstrt16.h>
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__NAMESPACE_LOCAL_USING_OR_IMPL(issymstrt16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL issymstrt16)(__WINT16_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(issymstrt16))(__wc); })
#endif /* !... */
#if defined(__CRT_HAVE___iswcsymf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,issymstrt32,(__WINT32_TYPE__ __wc),__iswcsymf,(__wc))
#elif defined(__CRT_HAVE_KOS$__iswcsymf)
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,issymstrt32,(__WINT32_TYPE__ __wc),__iswcsymf,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswsymstrt.h>
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL issymstrt32)(__WINT32_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswsymstrt))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/issymstrt32.h>
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__NAMESPACE_LOCAL_USING_OR_IMPL(issymstrt32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL issymstrt32)(__WINT32_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(issymstrt32))(__wc); })
#endif /* !... */
#if defined(__CRT_HAVE___iswcsym) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,issymcont16,(__WINT16_TYPE__ __wc),__iswcsym,(__wc))
#elif defined(__CRT_HAVE_DOS$__iswcsym)
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,issymcont16,(__WINT16_TYPE__ __wc),__iswcsym,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswsymcont.h>
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL issymcont16)(__WINT16_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswsymcont))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/issymcont16.h>
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__NAMESPACE_LOCAL_USING_OR_IMPL(issymcont16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL issymcont16)(__WINT16_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(issymcont16))(__wc); })
#endif /* !... */
#if defined(__CRT_HAVE___iswcsym) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,issymcont32,(__WINT32_TYPE__ __wc),__iswcsym,(__wc))
#elif defined(__CRT_HAVE_KOS$__iswcsym)
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,issymcont32,(__WINT32_TYPE__ __wc),__iswcsym,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswsymcont.h>
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL issymcont32)(__WINT32_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswsymcont))((__WINT_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/issymcont32.h>
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__NAMESPACE_LOCAL_USING_OR_IMPL(issymcont32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL issymcont32)(__WINT32_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(issymcont32))(__wc); })
#endif /* !... */
#if defined(__CRT_HAVE__iswcsymf_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,issymstrt16_l,(__WINT16_TYPE__ __wc, __locale_t __locale),_iswcsymf_l,(__wc,__locale))
#elif defined(__CRT_HAVE_DOS$_iswcsymf_l)
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,issymstrt16_l,(__WINT16_TYPE__ __wc, __locale_t __locale),_iswcsymf_l,(__wc,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswsymstrt_l.h>
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL issymstrt16_l)(__WINT16_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswsymstrt_l))((__WINT_TYPE__)__wc, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/issymstrt16_l.h>
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__NAMESPACE_LOCAL_USING_OR_IMPL(issymstrt16_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL issymstrt16_l)(__WINT16_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(issymstrt16_l))(__wc, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE__iswcsymf_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,issymstrt32_l,(__WINT32_TYPE__ __wc, __locale_t __locale),_iswcsymf_l,(__wc,__locale))
#elif defined(__CRT_HAVE_KOS$_iswcsymf_l)
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,issymstrt32_l,(__WINT32_TYPE__ __wc, __locale_t __locale),_iswcsymf_l,(__wc,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswsymstrt_l.h>
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL issymstrt32_l)(__WINT32_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswsymstrt_l))((__WINT_TYPE__)__wc, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/issymstrt32_l.h>
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__NAMESPACE_LOCAL_USING_OR_IMPL(issymstrt32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL issymstrt32_l)(__WINT32_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(issymstrt32_l))(__wc, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE__iswcsym_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,issymcont16_l,(__WINT16_TYPE__ __wc, __locale_t __locale),_iswcsym_l,(__wc,__locale))
#elif defined(__CRT_HAVE_DOS$_iswcsym_l)
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,issymcont16_l,(__WINT16_TYPE__ __wc, __locale_t __locale),_iswcsym_l,(__wc,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wctype/iswsymcont_l.h>
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL issymcont16_l)(__WINT16_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswsymcont_l))((__WINT_TYPE__)__wc, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/issymcont16_l.h>
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__NAMESPACE_LOCAL_USING_OR_IMPL(issymcont16_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL issymcont16_l)(__WINT16_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(issymcont16_l))(__wc, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE__iswcsym_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,issymcont32_l,(__WINT32_TYPE__ __wc, __locale_t __locale),_iswcsym_l,(__wc,__locale))
#elif defined(__CRT_HAVE_KOS$_iswcsym_l)
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,issymcont32_l,(__WINT32_TYPE__ __wc, __locale_t __locale),_iswcsym_l,(__wc,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wctype/iswsymcont_l.h>
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL issymcont32_l)(__WINT32_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswsymcont_l))((__WINT_TYPE__)__wc, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.wctype/issymcont32_l.h>
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__NAMESPACE_LOCAL_USING_OR_IMPL(issymcont32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBKCALL issymcont32_l)(__WINT32_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(issymcont32_l))(__wc, __locale); })
#endif /* !... */
#endif /* __USE_KOS */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PARTS_UCHAR_WCTYPE_H */
