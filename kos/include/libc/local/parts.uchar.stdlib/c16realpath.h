/* HASH CRC-32:0x16e1238d */
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
#ifndef __local_c16realpath_defined
#define __local_c16realpath_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wfrealpathat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wfrealpathat) || (defined(__CRT_HAVE_frealpathat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_frealpathat) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_DOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))))) || ((defined(__CRT_HAVE_realpath) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_frealpathat))) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_DOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16frealpathat_defined
#define __local___localdep_c16frealpathat_defined
#if defined(__CRT_HAVE_wfrealpathat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__CHAR16_TYPE__ *,__NOTHROW_RPC,__localdep_c16frealpathat,(__fd_t __dirfd, __CHAR16_TYPE__ const *__filename, __CHAR16_TYPE__ *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),wfrealpathat,(__dirfd,__filename,__resolved,__buflen,__flags))
#elif defined(__CRT_HAVE_DOS$wfrealpathat)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((2)),__CHAR16_TYPE__ *,__NOTHROW_RPC,__localdep_c16frealpathat,(__fd_t __dirfd, __CHAR16_TYPE__ const *__filename, __CHAR16_TYPE__ *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),wfrealpathat,(__dirfd,__filename,__resolved,__buflen,__flags))
#elif defined(__CRT_HAVE_frealpathat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.stdlib/wfrealpathat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16frealpathat __NAMESPACE_LOCAL_TYPEHAX(__CHAR16_TYPE__ *(__LIBDCALL*)(__fd_t,__CHAR16_TYPE__ const *,__CHAR16_TYPE__ *,__SIZE_TYPE__,__atflag_t),__CHAR16_TYPE__ *(__LIBDCALL&)(__fd_t,__CHAR16_TYPE__ const *,__CHAR16_TYPE__ *,__SIZE_TYPE__,__atflag_t),wfrealpathat)
#elif defined(__CRT_HAVE_frealpathat) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_DOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdlib/c16frealpathat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16frealpathat __LIBC_LOCAL_NAME(c16frealpathat)
#else /* ... */
#undef __local___localdep_c16frealpathat_defined
#endif /* !... */
#endif /* !__local___localdep_c16frealpathat_defined */
#ifndef __local___localdep_c16len_defined
#define __local___localdep_c16len_defined
#if defined(__CRT_HAVE_wcslen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16len,(__CHAR16_TYPE__ const *__restrict __str),wcslen,(__str))
#elif defined(__CRT_HAVE_DOS$wcslen)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16len,(__CHAR16_TYPE__ const *__restrict __str),wcslen,(__str))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16len __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict),__SIZE_TYPE__(__LIBDCALL&)(__CHAR16_TYPE__ const *__restrict),wcslen)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c16len.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16len __LIBC_LOCAL_NAME(c16len)
#endif /* !... */
#endif /* !__local___localdep_c16len_defined */
#ifndef __local___localdep_convert_c16tombs_defined
#define __local___localdep_convert_c16tombs_defined
#if defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_convert_c16tombs,(__CHAR16_TYPE__ const *__str),convert_wcstombs,(__str))
#elif defined(__CRT_HAVE_DOS$convert_wcstombs)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_convert_c16tombs,(__CHAR16_TYPE__ const *__str),convert_wcstombs,(__str))
#elif (defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_wcstombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_c16tombs __NAMESPACE_LOCAL_TYPEHAX(char *(__LIBDCALL*)(__CHAR16_TYPE__ const *),char *(__LIBDCALL&)(__CHAR16_TYPE__ const *),convert_wcstombs)
#elif (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_c16tombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_c16tombs __LIBC_LOCAL_NAME(convert_c16tombs)
#else /* ... */
#undef __local___localdep_convert_c16tombs_defined
#endif /* !... */
#endif /* !__local___localdep_convert_c16tombs_defined */
#ifndef __local___localdep_convert_mbstoc16_defined
#define __local___localdep_convert_mbstoc16_defined
#if defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_convert_mbstoc16,(char const *__restrict __str),convert_mbstowcs,(__str))
#elif defined(__CRT_HAVE_DOS$convert_mbstowcs)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_WUNUSED,__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_convert_mbstoc16,(char const *__restrict __str),convert_mbstowcs,(__str))
#elif (defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_mbstowcs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_mbstoc16 __NAMESPACE_LOCAL_TYPEHAX(__CHAR16_TYPE__ *(__LIBDCALL*)(char const *__restrict),__CHAR16_TYPE__ *(__LIBDCALL&)(char const *__restrict),convert_mbstowcs)
#elif (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_DOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_mbstoc16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_mbstoc16 __LIBC_LOCAL_NAME(convert_mbstoc16)
#else /* ... */
#undef __local___localdep_convert_mbstoc16_defined
#endif /* !... */
#endif /* !__local___localdep_convert_mbstoc16_defined */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_memcpyw_defined
#define __local___localdep_memcpyw_defined
#ifdef __CRT_HAVE_memcpyw
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),memcpyw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemcpy) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),wmemcpy,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemcpy) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),DOS$wmemcpy,(__dst,__src,__n_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpyw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpyw __LIBC_LOCAL_NAME(memcpyw)
#endif /* !... */
#endif /* !__local___localdep_memcpyw_defined */
#ifndef __local___localdep_realpath_defined
#define __local___localdep_realpath_defined
#ifdef __CRT_HAVE_realpath
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_RPC,__localdep_realpath,(char const *__filename, char *__resolved),realpath,(__filename,__resolved))
#elif defined(__AT_FDCWD) && defined(__CRT_HAVE_frealpathat)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/realpath.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_realpath __LIBC_LOCAL_NAME(realpath)
#else /* ... */
#undef __local___localdep_realpath_defined
#endif /* !... */
#endif /* !__local___localdep_realpath_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/limits.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16realpath) __ATTR_WUNUSED __ATTR_NONNULL((1)) __CHAR16_TYPE__ *
__NOTHROW_RPC(__LIBDCALL __LIBC_LOCAL_NAME(c16realpath))(__CHAR16_TYPE__ const *__filename, __CHAR16_TYPE__ *__resolved) {
#if defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wfrealpathat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wfrealpathat) || (defined(__CRT_HAVE_frealpathat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_frealpathat) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_DOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))))
#if defined(__PATH_MAX) && __PATH_MAX != -1
	return (__NAMESPACE_LOCAL_SYM __localdep_c16frealpathat)(__AT_FDCWD, __filename, __resolved, __resolved ? __PATH_MAX : 0, 0);
#else /* __PATH_MAX && __PATH_MAX != -1 */
	return (__NAMESPACE_LOCAL_SYM __localdep_c16frealpathat)(__AT_FDCWD, __filename, __resolved, __resolved ? 256 : 0, 0);
#endif /* !__PATH_MAX || __PATH_MAX == -1 */
#else /* __AT_FDCWD && ((__CRT_HAVE_wfrealpathat && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wfrealpathat || (__CRT_HAVE_frealpathat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_convert_mbstowcs || __CRT_HAVE_convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && __SIZEOF_WCHAR_T__ == 2) || (__CRT_HAVE_frealpathat && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && ((__CRT_HAVE_convert_mbstowcs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_mbstowcs || ((__CRT_HAVE_convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && __SIZEOF_WCHAR_T__ == 2) || (__CRT_HAVE_convert_mbstowcsn && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __SIZEOF_WCHAR_T__ == 2) || (((__CRT_HAVE_format_waprintf_printer && __SIZEOF_WCHAR_T__ == 2 && __C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC) || __CRT_HAVE_DOS$format_waprintf_printer || (__CRT_HAVE_format_waprintf_alloc && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && ((__CRT_HAVE_format_waprintf_pack && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))))) */
	char *__utf8_filename, *__utf8_resolved;
	__CHAR16_TYPE__ *__wcs_resolved;
	__SIZE_TYPE__ __resolved_length;
	__utf8_filename = (__NAMESPACE_LOCAL_SYM __localdep_convert_c16tombs)(__filename);
	if __unlikely(!__utf8_filename)
		return __NULLPTR;
	__utf8_resolved = (__NAMESPACE_LOCAL_SYM __localdep_realpath)(__utf8_filename, __NULLPTR);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_filename);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	if __unlikely(!__utf8_resolved)
		return __NULLPTR;
	__wcs_resolved = (__NAMESPACE_LOCAL_SYM __localdep_convert_mbstoc16)(__utf8_resolved);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_resolved);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	if __unlikely(!__wcs_resolved)
		return __NULLPTR;
	if (!__resolved)
		return __wcs_resolved;
	__resolved_length = (__NAMESPACE_LOCAL_SYM __localdep_c16len)(__wcs_resolved) + 1;
#if defined(__PATH_MAX) && __PATH_MAX != -1
	if (__resolved_length > __PATH_MAX)
#else /* __PATH_MAX && __PATH_MAX != -1 */
	if (__resolved_length > 256)
#endif /* !__PATH_MAX || __PATH_MAX == -1 */
	{
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__wcs_resolved);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
#ifdef __ERANGE
		(void)__libc_seterrno(__ERANGE);
#else /* __ERANGE */
		(void)__libc_seterrno(1);
#endif /* !__ERANGE */
		return __NULLPTR;
	}
	(__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_memcpyw)(__resolved, __wcs_resolved, __resolved_length);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__wcs_resolved);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __resolved;
#endif /* !__AT_FDCWD || ((!__CRT_HAVE_wfrealpathat || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wfrealpathat && (!__CRT_HAVE_frealpathat || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_convert_mbstowcs && !__CRT_HAVE_convert_mbstowcsn && ((!__CRT_HAVE_format_waprintf_printer && !__CRT_HAVE_format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) || __SIZEOF_WCHAR_T__ != 2) && (!__CRT_HAVE_frealpathat || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || ((!__CRT_HAVE_convert_mbstowcs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_mbstowcs && ((!__CRT_HAVE_convert_mbstowcsn && ((!__CRT_HAVE_format_waprintf_printer && !__CRT_HAVE_format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) || __SIZEOF_WCHAR_T__ != 2) && (!__CRT_HAVE_convert_mbstowcsn || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_mbstowcsn && ((!__CRT_HAVE_format_waprintf_printer && !__CRT_HAVE_format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || __SIZEOF_WCHAR_T__ != 2) && (((!__CRT_HAVE_format_waprintf_printer || __SIZEOF_WCHAR_T__ != 2 || !__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC) && !__CRT_HAVE_DOS$format_waprintf_printer && (!__CRT_HAVE_format_waprintf_alloc || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || ((!__CRT_HAVE_format_waprintf_pack || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))))) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16realpath_defined
#define __local___localdep_c16realpath_defined
#define __localdep_c16realpath __LIBC_LOCAL_NAME(c16realpath)
#endif /* !__local___localdep_c16realpath_defined */
#else /* (__AT_FDCWD && ((__CRT_HAVE_wfrealpathat && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wfrealpathat || (__CRT_HAVE_frealpathat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_convert_mbstowcs || __CRT_HAVE_convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && __SIZEOF_WCHAR_T__ == 2) || (__CRT_HAVE_frealpathat && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && ((__CRT_HAVE_convert_mbstowcs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_mbstowcs || ((__CRT_HAVE_convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && __SIZEOF_WCHAR_T__ == 2) || (__CRT_HAVE_convert_mbstowcsn && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __SIZEOF_WCHAR_T__ == 2) || (((__CRT_HAVE_format_waprintf_printer && __SIZEOF_WCHAR_T__ == 2 && __C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC) || __CRT_HAVE_DOS$format_waprintf_printer || (__CRT_HAVE_format_waprintf_alloc && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && ((__CRT_HAVE_format_waprintf_pack && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))))) || ((__CRT_HAVE_realpath || (__AT_FDCWD && __CRT_HAVE_frealpathat)) && ((__CRT_HAVE_convert_wcstombs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_wcstombs || (__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && ((__CRT_HAVE_convert_mbstowcs && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_mbstowcs || ((__CRT_HAVE_convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && __SIZEOF_WCHAR_T__ == 2) || (__CRT_HAVE_convert_mbstowcsn && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __SIZEOF_WCHAR_T__ == 2) || (((__CRT_HAVE_format_waprintf_printer && __SIZEOF_WCHAR_T__ == 2 && __C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC) || __CRT_HAVE_DOS$format_waprintf_printer || (__CRT_HAVE_format_waprintf_alloc && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && ((__CRT_HAVE_format_waprintf_pack && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) */
#undef __local_c16realpath_defined
#endif /* (!__AT_FDCWD || ((!__CRT_HAVE_wfrealpathat || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wfrealpathat && (!__CRT_HAVE_frealpathat || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_convert_mbstowcs && !__CRT_HAVE_convert_mbstowcsn && ((!__CRT_HAVE_format_waprintf_printer && !__CRT_HAVE_format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) || __SIZEOF_WCHAR_T__ != 2) && (!__CRT_HAVE_frealpathat || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || ((!__CRT_HAVE_convert_mbstowcs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_mbstowcs && ((!__CRT_HAVE_convert_mbstowcsn && ((!__CRT_HAVE_format_waprintf_printer && !__CRT_HAVE_format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) || __SIZEOF_WCHAR_T__ != 2) && (!__CRT_HAVE_convert_mbstowcsn || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_mbstowcsn && ((!__CRT_HAVE_format_waprintf_printer && !__CRT_HAVE_format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || __SIZEOF_WCHAR_T__ != 2) && (((!__CRT_HAVE_format_waprintf_printer || __SIZEOF_WCHAR_T__ != 2 || !__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC) && !__CRT_HAVE_DOS$format_waprintf_printer && (!__CRT_HAVE_format_waprintf_alloc || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || ((!__CRT_HAVE_format_waprintf_pack || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)))))) && ((!__CRT_HAVE_realpath && (!__AT_FDCWD || !__CRT_HAVE_frealpathat)) || ((!__CRT_HAVE_convert_wcstombs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_wcstombs && (!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || ((!__CRT_HAVE_convert_mbstowcs || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_mbstowcs && ((!__CRT_HAVE_convert_mbstowcsn && ((!__CRT_HAVE_format_waprintf_printer && !__CRT_HAVE_format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) || __SIZEOF_WCHAR_T__ != 2) && (!__CRT_HAVE_convert_mbstowcsn || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$convert_mbstowcsn && ((!__CRT_HAVE_format_waprintf_printer && !__CRT_HAVE_format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || __SIZEOF_WCHAR_T__ != 2) && (((!__CRT_HAVE_format_waprintf_printer || __SIZEOF_WCHAR_T__ != 2 || !__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC) && !__CRT_HAVE_DOS$format_waprintf_printer && (!__CRT_HAVE_format_waprintf_alloc || __SIZEOF_WCHAR_T__ != 2) && !__CRT_HAVE_DOS$format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || ((!__CRT_HAVE_format_waprintf_pack || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)))) */
#endif /* !__local_c16realpath_defined */
