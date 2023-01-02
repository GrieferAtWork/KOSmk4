/* HASH CRC-32:0xc86eb3c */
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
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/string.h) */
/* (#) Portability: DJGPP         (/include/string.h) */
/* (#) Portability: DragonFly BSD (/include/string.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/string.h) */
/* (#) Portability: FreeBSD       (/include/string.h) */
/* (#) Portability: GNU C Library (/string/string.h) */
/* (#) Portability: GNU Hurd      (/usr/include/string.h) */
/* (#) Portability: MSVC          (/include/string.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/string.h) */
/* (#) Portability: NetBSD        (/include/string.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/string.h) */
/* (#) Portability: OpenBSD       (/include/string.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/string.h) */
/* (#) Portability: PDCLib        (/include/string.h) */
/* (#) Portability: Windows Kits  (/ucrt/string.h) */
/* (#) Portability: avr-libc      (/include/string.h) */
/* (#) Portability: diet libc     (/include/string.h) */
/* (#) Portability: libbsd        (/include/bsd/string.h) */
/* (#) Portability: libc4/5       (/include/string.h) */
/* (#) Portability: libc6         (/include/string.h) */
/* (#) Portability: libcmini      (/include/string.h) */
/* (#) Portability: mintlib       (/include/string.h) */
/* (#) Portability: musl libc     (/include/string.h) */
/* (#) Portability: uClibc        (/include/string.h) */
#ifndef _STRING_H
#define _STRING_H 1

#ifdef _CXX_STDONLY_CSTRING
#ifdef __CXX_SYSTEM_HEADER
#undef _STRING_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "string.h" after "cstring" */
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#if !defined(__memcpy_defined) && defined(__std_memcpy_defined)
#define __memcpy_defined
__NAMESPACE_STD_USING(memcpy)
#endif /* !__memcpy_defined && __std_memcpy_defined */
__NAMESPACE_STD_USING(memmove)
__NAMESPACE_STD_USING(memset)
__NAMESPACE_STD_USING(memcmp)
__NAMESPACE_STD_USING(memchr)
__NAMESPACE_STD_USING(strlen)
__NAMESPACE_STD_USING(strchr)
__NAMESPACE_STD_USING(strrchr)
__NAMESPACE_STD_USING(strcmp)
__NAMESPACE_STD_USING(strncmp)
__NAMESPACE_STD_USING(strstr)
__NAMESPACE_STD_USING(strcpy)
__NAMESPACE_STD_USING(strncpy)
__NAMESPACE_STD_USING(strcat)
__NAMESPACE_STD_USING(strncat)
__NAMESPACE_STD_USING(strcspn)
__NAMESPACE_STD_USING(strspn)
__NAMESPACE_STD_USING(strpbrk)
__NAMESPACE_STD_USING(strtok)
__NAMESPACE_STD_USING(strcoll)
__NAMESPACE_STD_USING(strxfrm)
__NAMESPACE_STD_USING(strerror)
#undef _CXX_STDONLY_CSTRING
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CSTRING */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <hybrid/typecore.h>
#ifdef __USE_KOS
#include <parts/malloca.h>
#endif /* __USE_KOS */
#if defined(__USE_KOS) || defined(__USE_GNU)
#include <hybrid/__alloca.h>
#endif /* __USE_KOS || __USE_GNU */
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#ifdef __USE_DOS
#include <libc/errno.h>
#include <crtdefs.h>
#endif /* __USE_DOS */
#ifdef __USE_STRING_OVERLOADS
#include <hybrid/pp/__va_nargs.h>
#endif /* __USE_STRING_OVERLOADS */
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */

__SYSDECL_BEGIN

#ifdef __CC__
__NAMESPACE_STD_BEGIN
#ifndef __std_size_t_defined
#define __std_size_t_defined
typedef __size_t size_t;
#endif /* !__std_size_t_defined */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

/* Memory functions (An optional `[b|w|l|q]' suffix is a kos extension):
 *   [std] memcmp[b|w|l|q]      - Compare memory buffers and return the difference of the first non-matching byte/word/dword/qword
 *   [std] memset[b|w|l|q]      - Fill memory with a given byte/word/dword/qword
 *   [kos] mempset[b|w|l|q]     - Same as `memset[b|w|l|q]', but return `dst+n_(bytes|words|dwords|qwords)', rather than `dst'
 *   [std] memcpy[b|w|l|q]      - Copy memory between non-overlapping memory blocks.
 *   [glc] mempcpy[b|w|l|q]     - Same as `memcpy[b|w|l|q]', but return `dst+n_(bytes|words|dwords|qwords)', rather than `dst'
 *   [std] memmove[b|w|l|q]     - Move memory between potentially overlapping memory blocks.
 *   [kos] mempmove[b|w|l|q]    - Same as `memmove[b|w|l|q]', but return `dst+n_(bytes|words|dwords|qwords)', rather than `dst'
 *   [kos] memmoveup[b|w|l|q]   - Same as `memmove[b|w|l|q]', but assume that `dst >= src'
 *   [kos] memmovedown[b|w|l|q] - Same as `memmove[b|w|l|q]', but assume that `dst <= src'
 *   [kos] mempmoveup[b|w|l|q]  - Same as `mempmove[b|w|l|q]', but assume that `dst >= src'
 *   [kos] mempmovedown[b|w|l|q]- Same as `mempmove[b|w|l|q]', but assume that `dst <= src'
 *   [std] memchr[b|w|l|q]      - Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found.
 *   [glc] memrchr[b|w|l|q]     - Descendingly search for `needle', starting at `haystack+n_(bytes|words|dwords|qwords)-1'. - Return `NULL' if `needle' wasn't found.
 *   [glc] rawmemchr[b|w|l|q]   - Same as `memchr[b|w|l|q]' with a search limit of `(size_t)-1/sizeof(T)'
 *   [kos] rawmemrchr[b|w|l|q]  - Same as `memrchr[b|w|l|q]' without a search limit, starting at `haystack-sizeof(T)'
 *   [kos] memend[b|w|l|q]      - Same as `memchr[b|w|l|q]', but return `haystack+n_(bytes|words|dwords|qwords)', rather than `NULL' if `needle' wasn't found.
 *   [kos] memrend[b|w|l|q]     - Same as `memrchr[b|w|l|q]', but return `haystack - 1', rather than `NULL' if `needle' wasn't found.
 *   [kos] memlen[b|w|l|q]      - Same as `memend[b|w|l|q]', but return the offset from `haystack', rather than the actual address.
 *   [kos] memrlen[b|w|l|q]     - Same as `memrend[b|w|l|q]', but return the offset from `haystack', rather than the actual address.
 *   [kos] rawmemlen[b|w|l|q]   - Same as `rawmemchr[b|w|l|q]', but return the offset from `haystack', rather than the actual address.
 *   [kos] rawmemrlen[b|w|l|q]  - Same as `rawmemrchr[b|w|l|q]', but return the offset from `haystack', rather than the actual address.
 *   [kos] memxchr[b|w|l|q]     - Same as `memchr[b|w|l|q]', but search for non-matching locations.
 *   [kos] memrxchr[b|w|l|q]    - Same as `memrchr[b|w|l|q]', but search for non-matching locations.
 *   [kos] rawmemxchr[b|w|l|q]  - Same as `rawmemchr[b|w|l|q]', but search for non-matching locations.
 *   [kos] rawmemrxchr[b|w|l|q] - Same as `rawmemrchr[b|w|l|q]', but search for non-matching locations.
 *   [kos] memxend[b|w|l|q]     - Same as `memend[b|w|l|q]', but search for non-matching locations.
 *   [kos] memrxend[b|w|l|q]    - Same as `memrend[b|w|l|q]', but search for non-matching locations.
 *   [kos] memxlen[b|w|l|q]     - Same as `memlen[b|w|l|q]', but search for non-matching locations.
 *   [kos] memrxlen[b|w|l|q]    - Same as `memrlen[b|w|l|q]', but search for non-matching locations.
 *   [kos] rawmemxlen[b|w|l|q]  - Same as `rawmemlen[b|w|l|q]', but search for non-matching locations.
 *   [kos] rawmemrxlen[b|w|l|q] - Same as `rawmemrlen[b|w|l|q]', but search for non-matching locations.
 *   [kos] mempat[b|w|l|q]      - Same as `memset', but repeat a multi-byte pattern on aligned addresses.
 *
 * NOTE: Alignment requirements of b/w/l/q-suffixed functions:
 *   - For maximum portability, pointer arguments should have the same alignment as
 *     would be expected for Byte=1,Word=2,Long=4,Quad=8. The required alignment is
 *     also annotated for arguments.
 *   - On architecture that allow unaligned memory accesses (e.g. x86), the alignment
 *     isn't mandatory, but is still recommended. To determine if the current  target
 *     architecture allows for unaligned memory  access, and thereby doesn't  enforce
 *     the alignment requirements of b/w/l/q string  functions, you may test for  the
 *     `__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS' macro from `<hybrid/host.h>'
 *
 * String functions:
 *   [std] strlen               - Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')´)
 *   [std] strnlen              - Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´)
 *   [kos] strend               - Same as `str + strlen(str)'
 *   [kos] strnend              - Same as `str + strnlen(str, max_chars)'
 *   [std] strchr               - Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found.
 *   [std] strrchr              - Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found.
 *   [kos] strnchr              - Same as `strchr', but don't exceed `max_chars' characters.
 *   [kos] strnrchr             - Same as `strrchr', but don't exceed `max_chars' characters.
 *   [glc] strchrnul            - Same as `strchr', but return `strend(str)', rather than `NULL' if `needle' wasn't found.
 *   [kos] strrchrnul           - Same as `strrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found.
 *   [kos] strnchrnul           - Same as `strnchr', but return `strnend(str, max_chars)', rather than `NULL' if `needle' wasn't found.
 *   [kos] strnrchrnul          - Same as `strnrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found.
 *   [kos] stroff               - Same as `strchrnul', but return the offset from `str', rather than the actual address.
 *   [kos] strroff              - Same as `strrchrnul', but return the offset from `str', rather than the actual address.
 *   [kos] strnoff              - Same as `strnchrnul', but return the offset from `str', rather than the actual address.
 *   [kos] strnroff             - Same as `strnrchrnul', but return the offset from `str', rather than the actual address.
 *   [std] strcpy               - Same as `(char *)memcpy(dst, src, (strlen(src) + 1) * sizeof(char))'
 *   [std] strcat               - Same as `memcpy(strend(dst), src, (strlen(src) + 1) * sizeof(char))', but re-return `dst'
 *   [std] strncpy              - Similar to `strcpy', but always write `dstsize' characters, copying from `src' and filling the rest with padding ZEROes.
 *   [std] strncat              - Copy `strnlen(src, max_chars)' characters to `strend(dst)', then (try to) append a NUL-character thereafter. - Return `dst'.
 *   [glc] stpcpy               - Same as `mempcpy(dst, src, (strlen(src) + 1) * sizeof(char)) - 1´
 *   [glc] stpncpy              - Copy `strnlen(src, max_chars)' characters to `dst', then (try to) append a NUL-character thereafter. - Return `dst'.
 *
 * Annotations:
 *   [std]: The function is defined by the C standard
 *           - `memcpy()'
 *   [glc]: The function is also provided by Glibc, and is likely
 *          apart of some posix/unix standard
 *           - `rawmemchr()'
 *   [kos]: The function is kos-specific, or apart of a standard other than
 *          the C standard, or one  of the standards implemented by  Glibc.
 *           - `strend()' - Not apart of any standard (that I know of) -> KOS-specific
 *           - `strlwr()' - Can also be found in DOS -> DOS-specific, but also provided by KOS
 */
__NAMESPACE_STD_BEGIN
#ifndef __std_memcpy_defined
#define __std_memcpy_defined
#ifdef __memcpy_defined
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__NAMESPACE_GLB_USING_OR_IMPL(memcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memcpy)(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes) { return :: memcpy(__dst, __src, __n_bytes); })
#elif defined(__fast_memcpy_defined) && defined(__CRT_HAVE_memcpy)
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CEIDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memcpy,(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))(__dst, __src, __n_bytes); })
#elif defined(__fast_memcpy_defined)
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memcpy)(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_memcpy)
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memcpy,(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes),(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_STD_BEGIN
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memcpy)(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy))(__dst, __src, __n_bytes); })
#endif /* !... */
#endif /* !__std_memcpy_defined */
#if defined(__fast_memmove_defined) && defined(__CRT_HAVE_memmove)
/* >> memmove(3)
 * Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CEIDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmove,(void *__dst, void const *__src, size_t __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmove))(__dst, __src, __n_bytes); })
#elif defined(__fast_memmove_defined)
/* >> memmove(3)
 * Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmove)(void *__dst, void const *__src, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmove))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_memmove)
/* >> memmove(3)
 * Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmove,(void *__dst, void const *__src, size_t __n_bytes),(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/string/memmove.h>
__NAMESPACE_STD_BEGIN
/* >> memmove(3)
 * Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmove, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmove)(void *__dst, void const *__src, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmove))(__dst, __src, __n_bytes); })
#endif /* !... */
#if defined(__fast_memset_defined) && defined(__CRT_HAVE_memset)
/* >> memset(3)
 * Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__CEIDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memset,(void *__restrict __dst, int __byte, size_t __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))(__dst, __byte, __n_bytes); })
#elif defined(__fast_memset_defined)
/* >> memset(3)
 * Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memset)(void *__restrict __dst, int __byte, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))(__dst, __byte, __n_bytes); }
#elif defined(__CRT_HAVE_memset)
/* >> memset(3)
 * Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memset,(void *__restrict __dst, int __byte, size_t __n_bytes),(__dst,__byte,__n_bytes))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/string/memset.h>
__NAMESPACE_STD_BEGIN
/* >> memset(3)
 * Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memset)(void *__restrict __dst, int __byte, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memset))(__dst, __byte, __n_bytes); })
#endif /* !... */
#if defined(__fast_memcmp_defined) && defined(__CRT_HAVE_memcmp)
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __n_bytes); })
#elif defined(__fast_memcmp_defined)
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memcmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __n_bytes); }
#elif defined(__CRT_HAVE_memcmp)
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE___gcc_bcmp)
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),__gcc_bcmp,(__s1,__s2,__n_bytes))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/string/memcmp.h>
__NAMESPACE_STD_BEGIN
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memcmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp))(__s1, __s2, __n_bytes); })
#endif /* !... */
#if defined(__fast_memchr_defined) && defined(__CRT_HAVE_memchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memchr,(void *__restrict __haystack, int __needle, size_t __n_bytes),memchr,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __needle, __n_bytes); })
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memchr,(void const *__restrict __haystack, int __needle, size_t __n_bytes),memchr,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __needle, __n_bytes); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memchr,(void const *__restrict __haystack, int __needle, size_t __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memchr_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memchr)(void *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __needle, __n_bytes); }
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memchr)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memchr)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __needle, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memchr,(void *__restrict __haystack, int __needle, size_t __n_bytes),memchr,(__haystack,__needle,__n_bytes))
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memchr,(void const *__restrict __haystack, int __needle, size_t __n_bytes),memchr,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memchr,(void const *__restrict __haystack, int __needle, size_t __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/string/memchr.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memchr)(void *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))(__haystack, __needle, __n_bytes); }
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memchr)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memchr)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_strlen
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),size_t,__NOTHROW_NCX,strlen,(char const *__restrict __str),(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_STD_END
#include <libc/local/string/strlen.h>
__NAMESPACE_STD_BEGIN
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
__NAMESPACE_LOCAL_USING_OR_IMPL(strlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) size_t __NOTHROW_NCX(__LIBCCALL strlen)(char const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlen))(__str); })
#endif /* !__CRT_HAVE_strlen */
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strchr,(char *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,strchr,(char const *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strchr,(char const *__restrict __haystack, int __needle),{ return __builtin_strchr(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif __has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_index)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strchr,(char *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,strchr,(char const *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strchr,(char const *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_strchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strchr,(char *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,strchr,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strchr,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_index)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strchr,(char *__restrict __haystack, int __needle),index,(__haystack,__needle))
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,strchr,(char const *__restrict __haystack, int __needle),index,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strchr,(char const *__restrict __haystack, int __needle),index,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/string/strchr.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL strchr)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr))(__haystack, __needle); }
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char const *__NOTHROW_NCX(__LIBCCALL strchr)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL strchr)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if __has_builtin(__builtin_strrchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strrchr,(char *__restrict __haystack, int __needle),strrchr,{ return __builtin_strrchr(__haystack, __needle); })
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,strrchr,(char const *__restrict __haystack, int __needle),strrchr,{ return __builtin_strrchr(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strrchr,(char const *__restrict __haystack, int __needle),{ return __builtin_strrchr(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif __has_builtin(__builtin_rindex) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rindex)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strrchr,(char *__restrict __haystack, int __needle),rindex,{ return __builtin_rindex(__haystack, __needle); })
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,strrchr,(char const *__restrict __haystack, int __needle),rindex,{ return __builtin_rindex(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strrchr,(char const *__restrict __haystack, int __needle),rindex,{ return __builtin_rindex(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_strrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strrchr,(char *__restrict __haystack, int __needle),strrchr,(__haystack,__needle))
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,strrchr,(char const *__restrict __haystack, int __needle),strrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strrchr,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_rindex)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strrchr,(char *__restrict __haystack, int __needle),rindex,(__haystack,__needle))
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,strrchr,(char const *__restrict __haystack, int __needle),rindex,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strrchr,(char const *__restrict __haystack, int __needle),rindex,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/string/strrchr.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL strrchr)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchr))(__haystack, __needle); }
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char const *__NOTHROW_NCX(__LIBCCALL strrchr)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strrchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL strrchr)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcmp,(char const *__s1, char const *__s2),{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcmp,(char const *__s1, char const *__s2),(__s1,__s2))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/string/strcmp.h>
__NAMESPACE_STD_BEGIN
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__NAMESPACE_LOCAL_USING_OR_IMPL(strcmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL strcmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcmp))(__s1, __s2); })
#endif /* !... */
#if __has_builtin(__builtin_strncmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncmp)
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmp,(char const *__s1, char const *__s2, size_t __maxlen),{ return __builtin_strncmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_strncmp)
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmp,(char const *__s1, char const *__s2, size_t __maxlen),(__s1,__s2,__maxlen))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/string/strncmp.h>
__NAMESPACE_STD_BEGIN
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
__NAMESPACE_LOCAL_USING_OR_IMPL(strncmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncmp)(char const *__s1, char const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#if __has_builtin(__builtin_strstr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strstr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,strstr,(char *__haystack, char const *__needle),strstr,{ return __builtin_strstr(__haystack, __needle); })
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char const *,__NOTHROW_NCX,strstr,(char const *__haystack, char const *__needle),strstr,{ return __builtin_strstr(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,strstr,(char const *__haystack, char const *__needle),{ return __builtin_strstr(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_strstr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,strstr,(char *__haystack, char const *__needle),strstr,(__haystack,__needle))
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char const *,__NOTHROW_NCX,strstr,(char const *__haystack, char const *__needle),strstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,strstr,(char const *__haystack, char const *__needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/string/strstr.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char *__NOTHROW_NCX(__LIBCCALL strstr)(char *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strstr))(__haystack, __needle); }
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char const *__NOTHROW_NCX(__LIBCCALL strstr)(char const *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strstr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strstr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char *__NOTHROW_NCX(__LIBCCALL strstr)(char const *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strstr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if __has_builtin(__builtin_strcpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcpy)
/* >> strcpy(3)
 * Copy a NUL-terminated string `str' to `dst', and re-return `dst'.
 * The exact # of characters copied is `strlen(src) + 1' (+1 because
 * the trailing NUL-character is also copied) */
__CEIDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,strcpy,(char *__restrict __dst, char const *__restrict __src),{ return __builtin_strcpy(__dst, __src); })
#elif defined(__CRT_HAVE_strcpy)
/* >> strcpy(3)
 * Copy a NUL-terminated string `str' to `dst', and re-return `dst'.
 * The exact # of characters copied is `strlen(src) + 1' (+1 because
 * the trailing NUL-character is also copied) */
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,strcpy,(char *__restrict __dst, char const *__restrict __src),(__dst,__src))
#elif defined(__CRT_HAVE__mbscpy)
/* >> strcpy(3)
 * Copy a NUL-terminated string `str' to `dst', and re-return `dst'.
 * The exact # of characters copied is `strlen(src) + 1' (+1 because
 * the trailing NUL-character is also copied) */
__CREDIRECT_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,strcpy,(char *__restrict __dst, char const *__restrict __src),_mbscpy,(__dst,__src))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/string/strcpy.h>
__NAMESPACE_STD_BEGIN
/* >> strcpy(3)
 * Copy a NUL-terminated string `str' to `dst', and re-return `dst'.
 * The exact # of characters copied is `strlen(src) + 1' (+1 because
 * the trailing NUL-character is also copied) */
__NAMESPACE_LOCAL_USING_OR_IMPL(strcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1) char *__NOTHROW_NCX(__LIBCCALL strcpy)(char *__restrict __dst, char const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcpy))(__dst, __src); })
#endif /* !... */
#if __has_builtin(__builtin_strncpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncpy)
/* >> strncpy(3)
 * Always write exactly `buflen' characters to `buf'. As far as
 * space  for doing so is available, up to the `strlen(src)' of
 * the first characters  are copied from  `src'. All  remaining
 * characters are always set  to '\0'. Always re-returns  `buf' */
__CEIDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strncpy,(char *__restrict __buf, char const *__restrict __src, size_t __buflen),{ return __builtin_strncpy(__buf, __src, __buflen); })
#elif defined(__CRT_HAVE_strncpy)
/* >> strncpy(3)
 * Always write exactly `buflen' characters to `buf'. As far as
 * space  for doing so is available, up to the `strlen(src)' of
 * the first characters  are copied from  `src'. All  remaining
 * characters are always set  to '\0'. Always re-returns  `buf' */
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strncpy,(char *__restrict __buf, char const *__restrict __src, size_t __buflen),(__buf,__src,__buflen))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/string/strncpy.h>
__NAMESPACE_STD_BEGIN
/* >> strncpy(3)
 * Always write exactly `buflen' characters to `buf'. As far as
 * space  for doing so is available, up to the `strlen(src)' of
 * the first characters  are copied from  `src'. All  remaining
 * characters are always set  to '\0'. Always re-returns  `buf' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strncpy)(char *__restrict __buf, char const *__restrict __src, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncpy))(__buf, __src, __buflen); })
#endif /* !... */
#if __has_builtin(__builtin_strcat) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcat)
/* >> strcat(3)
 * Same as `strcpy(3)',  but rather  than copying `src'  ontop of  `dst',
 * append it at the end of `dst', or more precisely copy to `strend(dst)'
 * Always re-returns `dst' */
__CEIDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_INOUT(1),char *,__NOTHROW_NCX,strcat,(char *__restrict __dst, char const *__restrict __src),{ return __builtin_strcat(__dst, __src); })
#elif defined(__CRT_HAVE_strcat)
/* >> strcat(3)
 * Same as `strcpy(3)',  but rather  than copying `src'  ontop of  `dst',
 * append it at the end of `dst', or more precisely copy to `strend(dst)'
 * Always re-returns `dst' */
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_INOUT(1),char *,__NOTHROW_NCX,strcat,(char *__restrict __dst, char const *__restrict __src),(__dst,__src))
#elif defined(__CRT_HAVE__mbscat)
/* >> strcat(3)
 * Same as `strcpy(3)',  but rather  than copying `src'  ontop of  `dst',
 * append it at the end of `dst', or more precisely copy to `strend(dst)'
 * Always re-returns `dst' */
__CREDIRECT_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_INOUT(1),char *,__NOTHROW_NCX,strcat,(char *__restrict __dst, char const *__restrict __src),_mbscat,(__dst,__src))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/string/strcat.h>
__NAMESPACE_STD_BEGIN
/* >> strcat(3)
 * Same as `strcpy(3)',  but rather  than copying `src'  ontop of  `dst',
 * append it at the end of `dst', or more precisely copy to `strend(dst)'
 * Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strcat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_INOUT(1) char *__NOTHROW_NCX(__LIBCCALL strcat)(char *__restrict __dst, char const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcat))(__dst, __src); })
#endif /* !... */
#if __has_builtin(__builtin_strncat) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncat)
/* >> strncat(3)
 * Copy at most max_srclen (or rather: exactly `strnlen(src, max_srclen)')
 * characters   to    `strend(buf)',   and    always   re-return    `buf'. */
__CEIDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUT(1) __ATTR_INS(2, 3) __ATTR_NONNULL((2)),char *,__NOTHROW_NCX,strncat,(char *__restrict __buf, char const *__restrict __src, size_t __max_srclen),{ return __builtin_strncat(__buf, __src, __max_srclen); })
#elif defined(__CRT_HAVE_strncat)
/* >> strncat(3)
 * Copy at most max_srclen (or rather: exactly `strnlen(src, max_srclen)')
 * characters   to    `strend(buf)',   and    always   re-return    `buf'. */
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUT(1) __ATTR_INS(2, 3) __ATTR_NONNULL((2)),char *,__NOTHROW_NCX,strncat,(char *__restrict __buf, char const *__restrict __src, size_t __max_srclen),(__buf,__src,__max_srclen))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/string/strncat.h>
__NAMESPACE_STD_BEGIN
/* >> strncat(3)
 * Copy at most max_srclen (or rather: exactly `strnlen(src, max_srclen)')
 * characters   to    `strend(buf)',   and    always   re-return    `buf'. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strncat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUT(1) __ATTR_INS(2, 3) __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL strncat)(char *__restrict __buf, char const *__restrict __src, size_t __max_srclen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncat))(__buf, __src, __max_srclen); })
#endif /* !... */
#if __has_builtin(__builtin_strcspn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcspn)
/* >> strcspn(3)
 * Return the  offset from  `haystack' to  the first  character
 * for which `strchr(reject, ch) == NULL'. If no such character
 * exists, return `strlen(haystack)' */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),size_t,__NOTHROW_NCX,strcspn,(char const *__haystack, char const *__reject),{ return __builtin_strcspn(__haystack, __reject); })
#elif defined(__CRT_HAVE_strcspn)
/* >> strcspn(3)
 * Return the  offset from  `haystack' to  the first  character
 * for which `strchr(reject, ch) == NULL'. If no such character
 * exists, return `strlen(haystack)' */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),size_t,__NOTHROW_NCX,strcspn,(char const *__haystack, char const *__reject),(__haystack,__reject))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/string/strcspn.h>
__NAMESPACE_STD_BEGIN
/* >> strcspn(3)
 * Return the  offset from  `haystack' to  the first  character
 * for which `strchr(reject, ch) == NULL'. If no such character
 * exists, return `strlen(haystack)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strcspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) size_t __NOTHROW_NCX(__LIBCCALL strcspn)(char const *__haystack, char const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcspn))(__haystack, __reject); })
#endif /* !... */
#if __has_builtin(__builtin_strspn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strspn)
/* >> strspn(3)
 * Return the  offset from  `haystack' to  the first  character
 * for which `strchr(accept, ch) != NULL'. If no such character
 * exists, return `strlen(haystack)' */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),size_t,__NOTHROW_NCX,strspn,(char const *__haystack, char const *__accept),{ return __builtin_strspn(__haystack, __accept); })
#elif defined(__CRT_HAVE_strspn)
/* >> strspn(3)
 * Return the  offset from  `haystack' to  the first  character
 * for which `strchr(accept, ch) != NULL'. If no such character
 * exists, return `strlen(haystack)' */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),size_t,__NOTHROW_NCX,strspn,(char const *__haystack, char const *__accept),(__haystack,__accept))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/string/strspn.h>
__NAMESPACE_STD_BEGIN
/* >> strspn(3)
 * Return the  offset from  `haystack' to  the first  character
 * for which `strchr(accept, ch) != NULL'. If no such character
 * exists, return `strlen(haystack)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) size_t __NOTHROW_NCX(__LIBCCALL strspn)(char const *__haystack, char const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strspn))(__haystack, __accept); })
#endif /* !... */
#if __has_builtin(__builtin_strpbrk) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strpbrk)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,strpbrk,(char *__haystack, char const *__accept),strpbrk,{ return __builtin_strpbrk(__haystack, __accept); })
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char const *,__NOTHROW_NCX,strpbrk,(char const *__haystack, char const *__accept),strpbrk,{ return __builtin_strpbrk(__haystack, __accept); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,strpbrk,(char const *__haystack, char const *__accept),{ return __builtin_strpbrk(__haystack, __accept); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_strpbrk)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,strpbrk,(char *__haystack, char const *__accept),strpbrk,(__haystack,__accept))
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char const *,__NOTHROW_NCX,strpbrk,(char const *__haystack, char const *__accept),strpbrk,(__haystack,__accept))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,strpbrk,(char const *__haystack, char const *__accept),(__haystack,__accept))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/string/strpbrk.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char *__NOTHROW_NCX(__LIBCCALL strpbrk)(char *__haystack, char const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strpbrk))(__haystack, __accept); }
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char const *__NOTHROW_NCX(__LIBCCALL strpbrk)(char const *__haystack, char const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strpbrk))(__haystack, __accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strpbrk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char *__NOTHROW_NCX(__LIBCCALL strpbrk)(char const *__haystack, char const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strpbrk))(__haystack, __accept); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_strtok
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT_OPT(1),char *,__NOTHROW_NCX,strtok,(char *__str, char const *__delim),(__str,__delim))
#else /* __CRT_HAVE_strtok */
__NAMESPACE_STD_END
#include <libc/local/string/strtok.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtok, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT_OPT(1) char *__NOTHROW_NCX(__LIBCCALL strtok)(char *__str, char const *__delim) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtok))(__str, __delim); })
#endif /* !__CRT_HAVE_strtok */
#ifdef __CRT_HAVE_strcoll
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcoll,(char const *__s1, char const *__s2),(__s1,__s2))
#else /* __CRT_HAVE_strcoll */
__NAMESPACE_STD_END
#include <libc/local/string/strcoll.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strcoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL strcoll)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcoll))(__s1, __s2); })
#endif /* !__CRT_HAVE_strcoll */
#ifdef __CRT_HAVE_strxfrm
__CDECLARE(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),size_t,__NOTHROW_NCX,strxfrm,(char *__dst, char const *__restrict __src, size_t __buflen),(__dst,__src,__buflen))
#else /* __CRT_HAVE_strxfrm */
__NAMESPACE_STD_END
#include <libc/local/string/strxfrm.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strxfrm, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) size_t __NOTHROW_NCX(__LIBCCALL strxfrm)(char *__dst, char const *__restrict __src, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strxfrm))(__dst, __src, __buflen); })
#endif /* !__CRT_HAVE_strxfrm */
#ifdef __CRT_HAVE_strerror
__CDECLARE(__ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,strerror,(__errno_t __errnum),(__errnum))
#elif defined(__CRT_HAVE_xstrerror)
__CREDIRECT(__ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,strerror,(__errno_t __errnum),xstrerror,(__errnum))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/string/strerror.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strerror, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL strerror)(__errno_t __errnum) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strerror))(__errnum); })
#endif /* !... */
#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
extern "C++" {
#if defined(__fast_memcmpc_defined) && defined(__CRT_HAVE_memcmpc)
/* >> memcmpc(3)
 * Compare up to `elem_count' `elem_size'-bytes-large unsigned integers
 * from  the 2 given  buffers. If all are  identical, return `0'. Else:
 *  - return `< 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] < (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]'
 *  - return `> 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] > (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]' */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcmpc,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpc))(__s1, __s2, __elem_count, __elem_size); })
#elif defined(__fast_memcmpc_defined)
/* >> memcmpc(3)
 * Compare up to `elem_count' `elem_size'-bytes-large unsigned integers
 * from  the 2 given  buffers. If all are  identical, return `0'. Else:
 *  - return `< 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] < (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]'
 *  - return `> 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] > (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL memcmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpc))(__s1, __s2, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_memcmpc)
/* >> memcmpc(3)
 * Compare up to `elem_count' `elem_size'-bytes-large unsigned integers
 * from  the 2 given  buffers. If all are  identical, return `0'. Else:
 *  - return `< 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] < (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]'
 *  - return `> 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] > (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcmpc,(__s1,__s2,__elem_count,__elem_size))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/string/memcmpc.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* >> memcmpc(3)
 * Compare up to `elem_count' `elem_size'-bytes-large unsigned integers
 * from  the 2 given  buffers. If all are  identical, return `0'. Else:
 *  - return `< 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] < (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]'
 *  - return `> 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] > (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL memcmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpc))(__s1, __s2, __elem_count, __elem_size); }
#endif /* !... */
#if defined(__fast_memcpyc_defined) && defined(__CRT_HAVE_memcpyc)
/* >> memcpyc(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyc))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__fast_memcpyc_defined)
/* >> memcpyc(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL memcpy)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyc))(__dst, __src, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_memcpyc)
/* >> memcpyc(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/string/memcpyc.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* >> memcpyc(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL memcpy)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyc))(__dst, __src, __elem_count, __elem_size); }
#endif /* !... */
#if defined(__fast_memmovec_defined) && defined(__CRT_HAVE_memmovec)
/* >> memmovec(3)
 * Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,memmove,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmovec,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovec))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__fast_memmovec_defined)
/* >> memmovec(3)
 * Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL memmove)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovec))(__dst, __src, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_memmovec)
/* >> memmovec(3)
 * Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,memmove,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmovec,(__dst,__src,__elem_count,__elem_size))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/string/memmovec.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* >> memmovec(3)
 * Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL memmove)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovec))(__dst, __src, __elem_count, __elem_size); }
#endif /* !... */
} /* extern "C++" */
#endif /* __cplusplus && __USE_STRING_OVERLOADS */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#if !defined(__memcpy_defined) && defined(__std_memcpy_defined)
#define __memcpy_defined
__NAMESPACE_STD_USING(memcpy)
#endif /* !__memcpy_defined && __std_memcpy_defined */
__NAMESPACE_STD_USING(memmove)
__NAMESPACE_STD_USING(memset)
__NAMESPACE_STD_USING(memcmp)
__NAMESPACE_STD_USING(memchr)
__NAMESPACE_STD_USING(strlen)
__NAMESPACE_STD_USING(strchr)
__NAMESPACE_STD_USING(strrchr)
__NAMESPACE_STD_USING(strcmp)
__NAMESPACE_STD_USING(strncmp)
__NAMESPACE_STD_USING(strstr)
__NAMESPACE_STD_USING(strcpy)
__NAMESPACE_STD_USING(strncpy)
__NAMESPACE_STD_USING(strcat)
__NAMESPACE_STD_USING(strncat)
__NAMESPACE_STD_USING(strcspn)
__NAMESPACE_STD_USING(strspn)
__NAMESPACE_STD_USING(strpbrk)
__NAMESPACE_STD_USING(strtok)
__NAMESPACE_STD_USING(strcoll)
__NAMESPACE_STD_USING(strxfrm)
__NAMESPACE_STD_USING(strerror)
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef _MSC_VER
__NAMESPACE_STD_BEGIN
#pragma intrinsic(strcpy)
#pragma intrinsic(strcat)
__NAMESPACE_STD_END
#endif /* _MSC_VER */

#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#ifndef __strnlen_defined
#define __strnlen_defined
#if __has_builtin(__builtin_strnlen) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strnlen)
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),{ return __builtin_strnlen(__str, __maxlen); })
#elif defined(__CRT_HAVE_strnlen)
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#elif defined(__CRT_HAVE___strncnt)
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),__strncnt,(__str,__maxlen))
#else /* ... */
#include <libc/local/string/strnlen.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strnlen)(char const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnlen))(__str, __maxlen); })
#endif /* !... */
#endif /* !__strnlen_defined */
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#ifdef __USE_XOPEN2K8
#if __has_builtin(__builtin_stpcpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpcpy)
/* >> stpcpy(3)
 * Same as `mempcpy(dst, src, (strlen(src) + 1) * sizeof(char)) - 1´ */
__CEIDECLARE_GCCNCX(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,stpcpy,(char *__restrict __buf, char const *__restrict __src),{ return __builtin_stpcpy(__buf, __src); })
#elif defined(__CRT_HAVE_stpcpy)
/* >> stpcpy(3)
 * Same as `mempcpy(dst, src, (strlen(src) + 1) * sizeof(char)) - 1´ */
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,stpcpy,(char *__restrict __buf, char const *__restrict __src),(__buf,__src))
#elif defined(__CRT_HAVE___stpcpy)
/* >> stpcpy(3)
 * Same as `mempcpy(dst, src, (strlen(src) + 1) * sizeof(char)) - 1´ */
__CREDIRECT_GCCNCX(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,stpcpy,(char *__restrict __buf, char const *__restrict __src),__stpcpy,(__buf,__src))
#else /* ... */
#include <libc/local/string/stpcpy.h>
/* >> stpcpy(3)
 * Same as `mempcpy(dst, src, (strlen(src) + 1) * sizeof(char)) - 1´ */
__NAMESPACE_LOCAL_USING_OR_IMPL(stpcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) char *__NOTHROW_NCX(__LIBCCALL stpcpy)(char *__restrict __buf, char const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stpcpy))(__buf, __src); })
#endif /* !... */
#if __has_builtin(__builtin_stpncpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpncpy)
/* >> stpncpy(3) */
__CEIDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,stpncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),{ return __builtin_stpncpy(__buf, __src, __buflen); })
#elif defined(__CRT_HAVE_stpncpy)
/* >> stpncpy(3) */
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,stpncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#elif defined(__CRT_HAVE___stpncpy)
/* >> stpncpy(3) */
__CREDIRECT_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,stpncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),__stpncpy,(__buf,__src,__buflen))
#else /* ... */
#include <libc/local/string/stpncpy.h>
/* >> stpncpy(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(stpncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL stpncpy)(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stpncpy))(__buf, __src, __buflen); })
#endif /* !... */
#if __has_builtin(__builtin_stpcpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpcpy)
/* >> stpcpy(3)
 * Same as `mempcpy(dst, src, (strlen(src) + 1) * sizeof(char)) - 1´ */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__stpcpy,(char *__restrict __buf, char const *__restrict __src),stpcpy,{ return __builtin_stpcpy(__buf, __src); })
#elif defined(__CRT_HAVE_stpcpy)
/* >> stpcpy(3)
 * Same as `mempcpy(dst, src, (strlen(src) + 1) * sizeof(char)) - 1´ */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__stpcpy,(char *__restrict __buf, char const *__restrict __src),stpcpy,(__buf,__src))
#elif defined(__CRT_HAVE___stpcpy)
/* >> stpcpy(3)
 * Same as `mempcpy(dst, src, (strlen(src) + 1) * sizeof(char)) - 1´ */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__stpcpy,(char *__restrict __buf, char const *__restrict __src),(__buf,__src))
#else /* ... */
#include <libc/local/string/stpcpy.h>
/* >> stpcpy(3)
 * Same as `mempcpy(dst, src, (strlen(src) + 1) * sizeof(char)) - 1´ */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) char *__NOTHROW_NCX(__LIBCCALL __stpcpy)(char *__restrict __buf, char const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stpcpy))(__buf, __src); }
#endif /* !... */
#if __has_builtin(__builtin_stpncpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpncpy)
/* >> stpncpy(3) */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__stpncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),stpncpy,{ return __builtin_stpncpy(__buf, __src, __buflen); })
#elif defined(__CRT_HAVE_stpncpy)
/* >> stpncpy(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__stpncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),stpncpy,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE___stpncpy)
/* >> stpncpy(3) */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__stpncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#else /* ... */
#include <libc/local/string/stpncpy.h>
/* >> stpncpy(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __stpncpy)(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stpncpy))(__buf, __src, __buflen); }
#endif /* !... */
#ifdef __CRT_HAVE_strcoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcoll_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__strcoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcoll_l,(char const *__s1, char const *__s2, __locale_t __locale),_strcoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___strcoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcoll_l,(char const *__s1, char const *__s2, __locale_t __locale),__strcoll_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/string/strcoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL strcoll_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcoll_l))(__s1, __s2, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strxfrm_l
__CDECLARE(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,strxfrm_l,(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),(__dst,__src,__buflen,__locale))
#elif defined(__CRT_HAVE__strxfrm_l)
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,strxfrm_l,(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),_strxfrm_l,(__dst,__src,__buflen,__locale))
#elif defined(__CRT_HAVE___strxfrm_l)
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,strxfrm_l,(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),__strxfrm_l,(__dst,__src,__buflen,__locale))
#else /* ... */
#include <libc/local/string/strxfrm_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strxfrm_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strxfrm_l)(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strxfrm_l))(__dst, __src, __buflen, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strerror_l
__CDECLARE(__ATTR_COLD __ATTR_WUNUSED,char *,__NOTHROW_NCX,strerror_l,(__errno_t __errnum, __locale_t __locale),(__errnum,__locale))
#else /* __CRT_HAVE_strerror_l */
#include <libc/local/string/strerror_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strerror_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_COLD __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL strerror_l)(__errno_t __errnum, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strerror_l))(__errnum, __locale); })
#endif /* !__CRT_HAVE_strerror_l */
#ifndef __strsignal_defined
#define __strsignal_defined
#ifdef __CRT_HAVE_strsignal
__CDECLARE(__ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,strsignal,(__signo_t __signo),(__signo))
#else /* __CRT_HAVE_strsignal */
#include <libc/local/string/strsignal.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strsignal, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL strsignal)(__signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strsignal))(__signo); })
#endif /* !__CRT_HAVE_strsignal */
#endif /* !__strsignal_defined */
#if __has_builtin(__builtin_strndup) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strndup)
__CEIDECLARE_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INS(1, 2),char *,__NOTHROW_NCX,strndup,(char const *__restrict __str, __SIZE_TYPE__ __max_chars),{ return __builtin_strndup(__str, __max_chars); })
#elif defined(__CRT_HAVE_strndup)
__CDECLARE_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INS(1, 2),char *,__NOTHROW_NCX,strndup,(char const *__restrict __str, __SIZE_TYPE__ __max_chars),(__str,__max_chars))
#elif defined(__CRT_HAVE___strndup)
__CREDIRECT_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INS(1, 2),char *,__NOTHROW_NCX,strndup,(char const *__restrict __str, __SIZE_TYPE__ __max_chars),__strndup,(__str,__max_chars))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/string/strndup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strndup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INS(1, 2) char *__NOTHROW_NCX(__LIBCCALL strndup)(char const *__restrict __str, __SIZE_TYPE__ __max_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strndup))(__str, __max_chars); })
#endif /* ... */
#endif /* __USE_XOPEN2K8 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#if __has_builtin(__builtin_strdup) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strdup)
__CEIDECLARE_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strdup,(char const *__restrict __string),{ return __builtin_strdup(__string); })
#elif defined(__CRT_HAVE_strdup)
__CDECLARE_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strdup,(char const *__restrict __string),(__string))
#elif defined(__CRT_HAVE__strdup)
__CREDIRECT_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strdup,(char const *__restrict __string),_strdup,(__string))
#elif defined(__CRT_HAVE__mbsdup)
__CREDIRECT_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strdup,(char const *__restrict __string),_mbsdup,(__string))
#elif defined(__CRT_HAVE___strdup)
__CREDIRECT_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strdup,(char const *__restrict __string),__strdup,(__string))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/string/strdup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strdup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL strdup)(char const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strdup))(__string); })
#endif /* ... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 || __USE_DOS */

#ifdef __USE_POSIX
#ifdef __CRT_HAVE_strtok_r
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char *,__NOTHROW_NCX,strtok_r,(char *__str, char const *__delim, char **__restrict __save_ptr),(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE_strtok_s)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char *,__NOTHROW_NCX,strtok_r,(char *__str, char const *__delim, char **__restrict __save_ptr),strtok_s,(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE___strtok_r)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char *,__NOTHROW_NCX,strtok_r,(char *__str, char const *__delim, char **__restrict __save_ptr),__strtok_r,(__str,__delim,__save_ptr))
#else /* ... */
#include <libc/local/string/strtok_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtok_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1) char *__NOTHROW_NCX(__LIBCCALL strtok_r)(char *__str, char const *__delim, char **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtok_r))(__str, __delim, __save_ptr); })
#endif /* !... */
#endif /* __USE_POSIX */

#if defined(__USE_GNU) || defined(__USE_BSD)
#ifdef __CRT_HAVE_memrchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memrchr(3)
 * Descendingly search for `needle', starting at `haystack + n_bytes'.
 * Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrchr,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrchr,(__haystack,__needle,__n_bytes))
/* >> memrchr(3)
 * Descendingly search for `needle', starting at `haystack + n_bytes'.
 * Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memrchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrchr,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memrchr(3)
 * Descendingly search for `needle', starting at `haystack + n_bytes'.
 * Return `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrchr */
#include <libc/local/string/memrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memrchr(3)
 * Descendingly search for `needle', starting at `haystack + n_bytes'.
 * Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrchr)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))(__haystack, __needle, __n_bytes); }
/* >> memrchr(3)
 * Descendingly search for `needle', starting at `haystack + n_bytes'.
 * Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memrchr)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memrchr(3)
 * Descendingly search for `needle', starting at `haystack + n_bytes'.
 * Return `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrchr)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrchr */
#if defined(__CRT_HAVE_memmem0) && defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memmem(3)
 * Return the first address of a sub-string `needle...+=needlelen'
 * stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memmem,(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memmem0,(__haystack,__haystacklen,__needle,__needlelen))
/* >> memmem(3)
 * Return the first address of a sub-string `needle...+=needlelen'
 * stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memmem0,(__haystack,__haystacklen,__needle,__needlelen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memmem(3)
 * Return the first address of a sub-string `needle...+=needlelen'
 * stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memmem0,(__haystack,__haystacklen,__needle,__needlelen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memmem) && !defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memmem(3)
 * Return the first address of a sub-string `needle...+=needlelen'
 * stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memmem,(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memmem,(__haystack,__haystacklen,__needle,__needlelen))
/* >> memmem(3)
 * Return the first address of a sub-string `needle...+=needlelen'
 * stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memmem,(__haystack,__haystacklen,__needle,__needlelen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memmem(3)
 * Return the first address of a sub-string `needle...+=needlelen'
 * stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),(__haystack,__haystacklen,__needle,__needlelen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memmem.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memmem(3)
 * Return the first address of a sub-string `needle...+=needlelen'
 * stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memmem)(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmem))(__haystack, __haystacklen, __needle, __needlelen); }
/* >> memmem(3)
 * Return the first address of a sub-string `needle...+=needlelen'
 * stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) void const *__NOTHROW_NCX(__LIBCCALL memmem)(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmem))(__haystack, __haystacklen, __needle, __needlelen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memmem(3)
 * Return the first address of a sub-string `needle...+=needlelen'
 * stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmem, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memmem)(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmem))(__haystack, __haystacklen, __needle, __needlelen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_strcasestr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,strcasestr,(char *__haystack, char const *__needle),strcasestr,(__haystack,__needle))
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char const *,__NOTHROW_NCX,strcasestr,(char const *__haystack, char const *__needle),strcasestr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,strcasestr,(char const *__haystack, char const *__needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE___strcasestr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,strcasestr,(char *__haystack, char const *__needle),__strcasestr,(__haystack,__needle))
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char const *,__NOTHROW_NCX,strcasestr,(char const *__haystack, char const *__needle),__strcasestr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,strcasestr,(char const *__haystack, char const *__needle),__strcasestr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/strcasestr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char *__NOTHROW_NCX(__LIBCCALL strcasestr)(char *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasestr))(__haystack, __needle); }
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char const *__NOTHROW_NCX(__LIBCCALL strcasestr)(char const *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasestr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasestr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char *__NOTHROW_NCX(__LIBCCALL strcasestr)(char const *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasestr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#endif /* __USE_GNU || __USE_BSD */

#if defined(__USE_GNU) || defined(__USE_NETBSD)
#ifdef __CRT_HAVE_strchrnul
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strchrnul(3)
 * Same as `strchr', but return `strend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strchrnul,(char *__restrict __haystack, int __needle),strchrnul,(__haystack,__needle))
/* >> strchrnul(3)
 * Same as `strchr', but return `strend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,strchrnul,(char const *__restrict __haystack, int __needle),strchrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strchrnul(3)
 * Same as `strchr', but return `strend(str)', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strchrnul,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strchrnul */
#include <libc/local/string/strchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strchrnul(3)
 * Same as `strchr', but return `strend(str)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL strchrnul)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchrnul))(__haystack, __needle); }
/* >> strchrnul(3)
 * Same as `strchr', but return `strend(str)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char const *__NOTHROW_NCX(__LIBCCALL strchrnul)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strchrnul(3)
 * Same as `strchr', but return `strend(str)', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL strchrnul)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchrnul))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strchrnul */
#endif /* __USE_GNU || __USE_NETBSD */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_rawmemchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> rawmemchr(3)
 * Same as `memchr' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),void *,__NOTHROW_NCX,rawmemchr,(void *__restrict __haystack, int __needle),rawmemchr,(__haystack,__needle))
/* >> rawmemchr(3)
 * Same as `memchr' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),void const *,__NOTHROW_NCX,rawmemchr,(void const *__restrict __haystack, int __needle),rawmemchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> rawmemchr(3)
 * Same as `memchr' with a search limit of `(size_t)-1' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),void *,__NOTHROW_NCX,rawmemchr,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE___rawmemchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> rawmemchr(3)
 * Same as `memchr' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),void *,__NOTHROW_NCX,rawmemchr,(void *__restrict __haystack, int __needle),__rawmemchr,(__haystack,__needle))
/* >> rawmemchr(3)
 * Same as `memchr' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),void const *,__NOTHROW_NCX,rawmemchr,(void const *__restrict __haystack, int __needle),__rawmemchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> rawmemchr(3)
 * Same as `memchr' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),void *,__NOTHROW_NCX,rawmemchr,(void const *__restrict __haystack, int __needle),__rawmemchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/rawmemchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> rawmemchr(3)
 * Same as `memchr' with a search limit of `(size_t)-1' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) void *__NOTHROW_NCX(__LIBCCALL rawmemchr)(void *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchr))(__haystack, __needle); }
/* >> rawmemchr(3)
 * Same as `memchr' with a search limit of `(size_t)-1' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) void const *__NOTHROW_NCX(__LIBCCALL rawmemchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> rawmemchr(3)
 * Same as `memchr' with a search limit of `(size_t)-1' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) void *__NOTHROW_NCX(__LIBCCALL rawmemchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifndef __basename_defined
#define __basename_defined
#ifdef __CRT_HAVE_basename
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,basename,(char *__filename),basename,(__filename))
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,basename,(char const *__filename),basename,(__filename))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,basename,(char const *__filename),(__filename))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE___basename)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,basename,(char *__filename),__basename,(__filename))
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,basename,(char const *__filename),__basename,(__filename))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,basename,(char const *__filename),__basename,(__filename))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_lbasename)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,basename,(char *__filename),lbasename,(__filename))
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,basename,(char const *__filename),lbasename,(__filename))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,basename,(char const *__filename),lbasename,(__filename))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/basename.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL basename)(char *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(basename))(__filename); }
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char const *__NOTHROW_NCX(__LIBCCALL basename)(char const *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(basename))(__filename); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__NAMESPACE_LOCAL_USING_OR_IMPL(basename, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL basename)(char const *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(basename))(__filename); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#endif /* !__basename_defined */
#ifndef __strverscmp_defined
#define __strverscmp_defined
#ifdef __CRT_HAVE_strverscmp
/* >> strverscmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strverscmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE___strverscmp)
/* >> strverscmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strverscmp,(char const *__s1, char const *__s2),__strverscmp,(__s1,__s2))
#else /* ... */
#include <libc/local/string/strverscmp.h>
/* >> strverscmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(strverscmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL strverscmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strverscmp))(__s1, __s2); })
#endif /* !... */
#endif /* !__strverscmp_defined */
#if defined(__fast_mempcpy_defined) && defined(__CRT_HAVE_mempcpy)
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))(__dst, __src, __n_bytes); })
#elif defined(__fast_mempcpy_defined) && defined(__CRT_HAVE___mempcpy)
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))(__dst, __src, __n_bytes); })
#elif defined(__fast_mempcpy_defined)
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempcpy)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_mempcpy)
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/mempcpy.h>
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempcpy)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpy))(__dst, __src, __n_bytes); }
#endif /* !... */
#ifndef __mempcpy_defined
#define __mempcpy_defined
#if defined(__fast_mempcpy_defined) && defined(__CRT_HAVE_mempcpy)
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
__CEIDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))(__dst, __src, __n_bytes); })
#elif defined(__fast_mempcpy_defined) && defined(__CRT_HAVE___mempcpy)
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
__CEIREDIRECT_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))(__dst, __src, __n_bytes); })
#elif defined(__fast_mempcpy_defined)
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempcpy)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_mempcpy)
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
__CDECLARE_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
__CREDIRECT_GCCNCX(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/mempcpy.h>
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempcpy)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpy))(__dst, __src, __n_bytes); })
#endif /* !... */
#endif /* !__mempcpy_defined */
#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
extern "C++" {
#if defined(__fast_mempcpyc_defined) && defined(__CRT_HAVE_mempcpyc)
/* >> mempcpyc(3)
 * Same as `memcpyc', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempcpyc,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyc))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__fast_mempcpyc_defined)
/* >> mempcpyc(3)
 * Same as `memcpyc', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL mempcpy)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyc))(__dst, __src, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_mempcpyc)
/* >> mempcpyc(3)
 * Same as `memcpyc', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* ... */
} /* extern "C++" */
#include <libc/local/string/mempcpyc.h>
extern "C++" {
/* >> mempcpyc(3)
 * Same as `memcpyc', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL mempcpy)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyc))(__dst, __src, __elem_count, __elem_size); }
#endif /* !... */
} /* extern "C++" */
#endif /* __cplusplus && __USE_STRING_OVERLOADS */
#ifdef __CRT_HAVE_strfry
/* >> strfry(3) */
__CDECLARE(__ATTR_LEAF __ATTR_INOUT(1),char *,__NOTHROW_NCX,strfry,(char *__restrict __str),(__str))
#else /* __CRT_HAVE_strfry */
#include <libc/local/string/strfry.h>
/* >> strfry(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(strfry, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char *__NOTHROW_NCX(__LIBCCALL strfry)(char *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strfry))(__str); })
#endif /* !__CRT_HAVE_strfry */
#ifdef __CRT_HAVE_memfrob
/* >> memfrob(3)
 * Xor every byte in `buf...+=num_bytes' with decimal `42' (yeah...)
 * Always re-return the given `buf' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memfrob,(void *__buf, __SIZE_TYPE__ __num_bytes),(__buf,__num_bytes))
#else /* __CRT_HAVE_memfrob */
#include <libc/local/string/memfrob.h>
/* >> memfrob(3)
 * Xor every byte in `buf...+=num_bytes' with decimal `42' (yeah...)
 * Always re-return the given `buf' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memfrob, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memfrob)(void *__buf, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memfrob))(__buf, __num_bytes); })
#endif /* !__CRT_HAVE_memfrob */
#ifndef __strcasecmp_l_defined
#define __strcasecmp_l_defined
#ifdef __CRT_HAVE_strcasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__stricmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),_stricmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___strcasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),__strcasecmp_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/string/strcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL strcasecmp_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp_l))(__s1, __s2, __locale); })
#endif /* !... */
#endif /* !__strcasecmp_l_defined */
#ifndef __strncasecmp_l_defined
#define __strncasecmp_l_defined
#ifdef __CRT_HAVE_strncasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncmpi_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strncmpi_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___strncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/string/strncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL strncasecmp_l)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#endif /* !__strncasecmp_l_defined */
#ifdef __CRT_HAVE_strerrordesc_np
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,strerrordesc_np,(__errno_t __errnum),(__errnum))
#else /* __CRT_HAVE_strerrordesc_np */
#include <libc/local/string/strerrordesc_np.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strerrordesc_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(__LIBCCALL strerrordesc_np)(__errno_t __errnum) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strerrordesc_np))(__errnum); })
#endif /* !__CRT_HAVE_strerrordesc_np */
#ifdef __CRT_HAVE_strerrorname_np
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,strerrorname_np,(__errno_t __errnum),(__errnum))
#elif defined(__CRT_HAVE_strerrno)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,strerrorname_np,(__errno_t __errnum),strerrno,(__errnum))
#else /* ... */
#include <libc/local/string/strerrorname_np.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strerrorname_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(__LIBCCALL strerrorname_np)(__errno_t __errnum) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strerrorname_np))(__errnum); })
#endif /* !... */
#ifdef __CRT_HAVE_sigabbrev_np
/* >> sigabbrev_np(3)
 * Return the name of a given signal, _without_ the leading `SIG*' prefix.
 * When the given  `signo' isn't recognized,  `NULL' is returned  instead. */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,sigabbrev_np,(__signo_t __signo),(__signo))
#elif defined(__CRT_HAVE_signalname)
/* >> sigabbrev_np(3)
 * Return the name of a given signal, _without_ the leading `SIG*' prefix.
 * When the given  `signo' isn't recognized,  `NULL' is returned  instead. */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,sigabbrev_np,(__signo_t __signo),signalname,(__signo))
#elif defined(__CRT_HAVE_strsigno)
/* >> sigabbrev_np(3)
 * Return the name of a given signal, _without_ the leading `SIG*' prefix.
 * When the given  `signo' isn't recognized,  `NULL' is returned  instead. */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,sigabbrev_np,(__signo_t __signo),strsigno,(__signo))
#else /* ... */
#include <libc/local/string/sigabbrev_np.h>
/* >> sigabbrev_np(3)
 * Return the name of a given signal, _without_ the leading `SIG*' prefix.
 * When the given  `signo' isn't recognized,  `NULL' is returned  instead. */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigabbrev_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(__LIBCCALL sigabbrev_np)(__signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigabbrev_np))(__signo); })
#endif /* !... */
#ifdef __CRT_HAVE_sigdescr_np
/* >> sigdescr_np(3)
 * Return a description for the given signal.
 * If the given `signo' isn't recognized, return `NULL' instead. */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,sigdescr_np,(__signo_t __signo),(__signo))
#else /* __CRT_HAVE_sigdescr_np */
#include <libc/local/string/sigdescr_np.h>
/* >> sigdescr_np(3)
 * Return a description for the given signal.
 * If the given `signo' isn't recognized, return `NULL' instead. */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigdescr_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(__LIBCCALL sigdescr_np)(__signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigdescr_np))(__signo); })
#endif /* !__CRT_HAVE_sigdescr_np */
#endif /* __USE_GNU */

#ifdef __USE_XOPEN2K
#ifdef __USE_GNU
#ifdef __CRT_HAVE_strerror_r
__CDECLARE(__ATTR_COLD __ATTR_RETNONNULL __ATTR_NONNULL((2)),char *,__NOTHROW_NCX,strerror_r,(__errno_t __errnum, char *__buf, __SIZE_TYPE__ __buflen),(__errnum,__buf,__buflen))
#elif defined(__CRT_HAVE___strerror_r)
__CREDIRECT(__ATTR_COLD __ATTR_RETNONNULL __ATTR_NONNULL((2)),char *,__NOTHROW_NCX,strerror_r,(__errno_t __errnum, char *__buf, __SIZE_TYPE__ __buflen),__strerror_r,(__errnum,__buf,__buflen))
#else /* ... */
#include <libc/local/string/strerror_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strerror_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_COLD __ATTR_RETNONNULL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL strerror_r)(__errno_t __errnum, char *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strerror_r))(__errnum, __buf, __buflen); })
#endif /* !... */
#else /* __USE_GNU */
#ifdef __CRT_HAVE___xpg_strerror_r
__CREDIRECT(__ATTR_COLD __ATTR_OUTS(2, 3),__errno_t,__NOTHROW_NCX,strerror_r,(__errno_t __errnum, char *__buf, __SIZE_TYPE__ __buflen),__xpg_strerror_r,(__errnum,__buf,__buflen))
#else /* __CRT_HAVE___xpg_strerror_r */
#include <libc/local/string/__xpg_strerror_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_COLD __ATTR_OUTS(2, 3) __errno_t __NOTHROW_NCX(__LIBCCALL strerror_r)(__errno_t __errnum, char *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__xpg_strerror_r))(__errnum, __buf, __buflen); }
#endif /* !__CRT_HAVE___xpg_strerror_r */
#endif /* !__USE_GNU */
#endif /* __USE_XOPEN2K */

#ifdef __USE_MISC
#ifdef __CRT_HAVE_strsep
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(1),char *,__NOTHROW_NCX,strsep,(char **__restrict __stringp, char const *__restrict __delim),(__stringp,__delim))
#else /* __CRT_HAVE_strsep */
#include <libc/local/string/strsep.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strsep, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(1) char *__NOTHROW_NCX(__LIBCCALL strsep)(char **__restrict __stringp, char const *__restrict __delim) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strsep))(__stringp, __delim); })
#endif /* !__CRT_HAVE_strsep */
#ifndef __bcopy_defined
#define __bcopy_defined
#if __has_builtin(__builtin_bcopy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_bcopy)
/* Same as `memmove(dst, src, num_bytes)'
 * Note that bcopy is called with `dst' and `src' reversed */
__CEIDECLARE_GCCNCX(__ATTR_INS(1, 3) __ATTR_OUTS(2, 3),void,__NOTHROW_NCX,bcopy,(void const *__src, void *__dst, __SIZE_TYPE__ __num_bytes),{ __builtin_bcopy(__src, __dst, __num_bytes); })
#elif defined(__CRT_HAVE_bcopy)
/* Same as `memmove(dst, src, num_bytes)'
 * Note that bcopy is called with `dst' and `src' reversed */
__CDECLARE_VOID_GCCNCX(__ATTR_INS(1, 3) __ATTR_OUTS(2, 3),__NOTHROW_NCX,bcopy,(void const *__src, void *__dst, __SIZE_TYPE__ __num_bytes),(__src,__dst,__num_bytes))
#else /* ... */
#include <libc/local/string/bcopy.h>
/* Same as `memmove(dst, src, num_bytes)'
 * Note that bcopy is called with `dst' and `src' reversed */
__NAMESPACE_LOCAL_USING_OR_IMPL(bcopy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(1, 3) __ATTR_OUTS(2, 3) void __NOTHROW_NCX(__LIBCCALL bcopy)(void const *__src, void *__dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bcopy))(__src, __dst, __num_bytes); })
#endif /* !... */
#endif /* !__bcopy_defined */
#ifndef __bzero_defined
#define __bzero_defined
#if defined(__fast_bzero_defined) && defined(__CRT_HAVE_bzero)
__CEIDECLARE_GCCNCX(__ATTR_OUTS(1, 2),void,__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); })
#elif defined(__fast_bzero_defined) && defined(__CRT_HAVE___bzero)
__CEIREDIRECT_GCCNCX(__ATTR_OUTS(1, 2),void,__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); })
#elif defined(__fast_bzero_defined) && defined(__CRT_HAVE_explicit_bzero)
__CEIREDIRECT_GCCNCX(__ATTR_OUTS(1, 2),void,__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); })
#elif defined(__fast_bzero_defined)
__FORCELOCAL __ATTR_OUTS(1, 2) void __NOTHROW_NCX(__LIBCCALL bzero)(void *__restrict __dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); }
#elif defined(__CRT_HAVE_bzero)
__CDECLARE_VOID_GCCNCX(__ATTR_OUTS(1, 2),__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__CREDIRECT_VOID_GCCNCX(__ATTR_OUTS(1, 2),__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__CREDIRECT_VOID_GCCNCX(__ATTR_OUTS(1, 2),__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
#include <libc/local/string/bzero.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bzero, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(1, 2) void __NOTHROW_NCX(__LIBCCALL bzero)(void *__restrict __dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzero))(__dst, __num_bytes); })
#endif /* !... */
#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
extern "C++" {
#if defined(__fast_bzeroc_defined) && defined(__CRT_HAVE_bzeroc)
__CEIREDIRECT(__ATTR_LEAF __ATTR_OUT(1),void,__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bzeroc,{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroc))(__dst, __elem_count, __elem_size); })
#elif defined(__fast_bzeroc_defined)
__FORCELOCAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzero)(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroc))(__dst, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_bzeroc)
__CREDIRECT_VOID(__ATTR_LEAF __ATTR_OUT(1),__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bzeroc,(__dst,__elem_count,__elem_size))
#else /* ... */
} /* extern "C++" */
#include <libc/local/string/bzeroc.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzero)(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzeroc))(__dst, __elem_count, __elem_size); }
#endif /* !... */
} /* extern "C++" */
#endif /* __cplusplus && __USE_STRING_OVERLOADS */
#endif /* !__bzero_defined */

#ifdef __USE_STRING_BWLQ
#ifndef __bzerob_defined
#define __bzerob_defined
#if defined(__fast_bzero_defined) && defined(__CRT_HAVE_bzero)
__CEIREDIRECT(__ATTR_LEAF __ATTR_OUTS(1, 2) __ATTR_NONNULL((1)),void,__NOTHROW_NCX,bzerob,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); })
#elif defined(__fast_bzero_defined) && defined(__CRT_HAVE___bzero)
__CEIREDIRECT(__ATTR_LEAF __ATTR_OUTS(1, 2) __ATTR_NONNULL((1)),void,__NOTHROW_NCX,bzerob,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); })
#elif defined(__fast_bzero_defined) && defined(__CRT_HAVE_explicit_bzero)
__CEIREDIRECT(__ATTR_LEAF __ATTR_OUTS(1, 2) __ATTR_NONNULL((1)),void,__NOTHROW_NCX,bzerob,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); })
#elif defined(__fast_bzero_defined)
__FORCELOCAL __ATTR_LEAF __ATTR_OUTS(1, 2) __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzerob)(void *__restrict __dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); }
#elif defined(__CRT_HAVE_bzero)
__CREDIRECT_VOID(__ATTR_LEAF __ATTR_OUTS(1, 2) __ATTR_NONNULL((1)),__NOTHROW_NCX,bzerob,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__CREDIRECT_VOID(__ATTR_LEAF __ATTR_OUTS(1, 2) __ATTR_NONNULL((1)),__NOTHROW_NCX,bzerob,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__CREDIRECT_VOID(__ATTR_LEAF __ATTR_OUTS(1, 2) __ATTR_NONNULL((1)),__NOTHROW_NCX,bzerob,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
#include <libc/local/string/bzero.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_OUTS(1, 2) __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzerob)(void *__restrict __dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzero))(__dst, __num_bytes); }
#endif /* !... */
#endif /* !__bzerob_defined */
#ifndef __bzerow_defined
#define __bzerow_defined
#if defined(__fast_bzerow_defined) && defined(__CRT_HAVE_bzerow)
__CEIDECLARE(__ATTR_LEAF __ATTR_OUT(1),void,__NOTHROW_NCX,bzerow,(void *__restrict __dst, __SIZE_TYPE__ __num_words),{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzerow))(__dst, __num_words); })
#elif defined(__fast_bzerow_defined)
__FORCELOCAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzerow)(void *__restrict __dst, __SIZE_TYPE__ __num_words) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzerow))(__dst, __num_words); }
#elif defined(__CRT_HAVE_bzerow)
__CDECLARE_VOID(__ATTR_LEAF __ATTR_OUT(1),__NOTHROW_NCX,bzerow,(void *__restrict __dst, __SIZE_TYPE__ __num_words),(__dst,__num_words))
#else /* ... */
#include <libc/local/string/bzerow.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bzerow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzerow)(void *__restrict __dst, __SIZE_TYPE__ __num_words) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzerow))(__dst, __num_words); })
#endif /* !... */
#endif /* !__bzerow_defined */
#ifndef __bzerol_defined
#define __bzerol_defined
#if defined(__fast_bzerol_defined) && defined(__CRT_HAVE_bzerol)
__CEIDECLARE(__ATTR_LEAF __ATTR_OUT(1),void,__NOTHROW_NCX,bzerol,(void *__restrict __dst, __SIZE_TYPE__ __num_dwords),{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzerol))(__dst, __num_dwords); })
#elif defined(__fast_bzerol_defined)
__FORCELOCAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzerol)(void *__restrict __dst, __SIZE_TYPE__ __num_dwords) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzerol))(__dst, __num_dwords); }
#elif defined(__CRT_HAVE_bzerol)
__CDECLARE_VOID(__ATTR_LEAF __ATTR_OUT(1),__NOTHROW_NCX,bzerol,(void *__restrict __dst, __SIZE_TYPE__ __num_dwords),(__dst,__num_dwords))
#else /* ... */
#include <libc/local/string/bzerol.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bzerol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzerol)(void *__restrict __dst, __SIZE_TYPE__ __num_dwords) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzerol))(__dst, __num_dwords); })
#endif /* !... */
#endif /* !__bzerol_defined */
#ifndef __bcmpb_defined
#define __bcmpb_defined
#if defined(__fast_bcmp_defined) && defined(__CRT_HAVE_bcmp)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmpb,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmp))(__s1, __s2, __n_bytes); })
#elif defined(__fast_bcmp_defined)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmpb)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmp))(__s1, __s2, __n_bytes); }
#elif defined(__fast_memcmp_defined) && defined(__CRT_HAVE_bcmp)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmpb,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __n_bytes); })
#elif defined(__fast_memcmp_defined)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmpb)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __n_bytes); }
#elif defined(__CRT_HAVE_bcmp)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmpb,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_memcmp)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmpb,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#else /* ... */
#include <libc/local/string/memcmp.h>
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmpb)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp))(__s1, __s2, __n_bytes); }
#endif /* !... */
#endif /* !__bcmpb_defined */
#ifndef __bcmpw_defined
#define __bcmpw_defined
#if defined(__fast_bcmpw_defined) && defined(__CRT_HAVE_bcmpw)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpw))(__s1, __s2, __n_words); })
#elif defined(__fast_memcmpw_defined) && defined(__CRT_HAVE_bcmpw)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpw))(__s1, __s2, __n_words); })
#elif defined(__fast_bcmpw_defined) && defined(__CRT_HAVE_memcmpw)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),memcmpw,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpw))(__s1, __s2, __n_words); })
#elif defined(__fast_memcmpw_defined) && defined(__CRT_HAVE_memcmpw)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),memcmpw,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpw))(__s1, __s2, __n_words); })
#elif defined(__fast_bcmpw_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpw)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpw))(__s1, __s2, __n_words); }
#elif defined(__fast_memcmpw_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpw)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpw))(__s1, __s2, __n_words); }
#elif defined(__CRT_HAVE_bcmpw)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),(__s1,__s2,__n_words))
#elif defined(__CRT_HAVE_memcmpw)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),memcmpw,(__s1,__s2,__n_words))
#else /* ... */
#include <libc/local/string/memcmpw.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpw)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpw))(__s1, __s2, __n_words); }
#endif /* !... */
#endif /* !__bcmpw_defined */
#ifndef __bcmpl_defined
#define __bcmpl_defined
#if defined(__fast_bcmpl_defined) && defined(__CRT_HAVE_bcmpl)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpl))(__s1, __s2, __n_dwords); })
#elif defined(__fast_memcmpl_defined) && defined(__CRT_HAVE_bcmpl)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpl))(__s1, __s2, __n_dwords); })
#elif defined(__fast_bcmpl_defined) && defined(__CRT_HAVE_memcmpl)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),memcmpl,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpl))(__s1, __s2, __n_dwords); })
#elif defined(__fast_memcmpl_defined) && defined(__CRT_HAVE_memcmpl)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),memcmpl,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpl))(__s1, __s2, __n_dwords); })
#elif defined(__fast_bcmpl_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpl)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpl))(__s1, __s2, __n_dwords); }
#elif defined(__fast_memcmpl_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpl)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpl))(__s1, __s2, __n_dwords); }
#elif defined(__CRT_HAVE_bcmpl)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),(__s1,__s2,__n_dwords))
#elif defined(__CRT_HAVE_memcmpl)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),memcmpl,(__s1,__s2,__n_dwords))
#else /* ... */
#include <libc/local/string/memcmpl.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpl)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpl))(__s1, __s2, __n_dwords); }
#endif /* !... */
#endif /* !__bcmpl_defined */
#ifdef __UINT64_TYPE__
#ifndef __bzeroq_defined
#define __bzeroq_defined
#if defined(__fast_bzeroq_defined) && defined(__CRT_HAVE_bzeroq)
__CEIDECLARE(__ATTR_LEAF __ATTR_OUT(1),void,__NOTHROW_NCX,bzeroq,(void *__restrict __dst, __SIZE_TYPE__ __num_qwords),{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroq))(__dst, __num_qwords); })
#elif defined(__fast_bzeroq_defined)
__FORCELOCAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzeroq)(void *__restrict __dst, __SIZE_TYPE__ __num_qwords) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroq))(__dst, __num_qwords); }
#elif defined(__CRT_HAVE_bzeroq)
__CDECLARE_VOID(__ATTR_LEAF __ATTR_OUT(1),__NOTHROW_NCX,bzeroq,(void *__restrict __dst, __SIZE_TYPE__ __num_qwords),(__dst,__num_qwords))
#else /* ... */
#include <libc/local/string/bzeroq.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bzeroq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzeroq)(void *__restrict __dst, __SIZE_TYPE__ __num_qwords) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzeroq))(__dst, __num_qwords); })
#endif /* !... */
#endif /* !__bzeroq_defined */
#ifndef __bcmpq_defined
#define __bcmpq_defined
#if defined(__fast_bcmpq_defined) && defined(__CRT_HAVE_bcmpq)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpq))(__s1, __s2, __n_qwords); })
#elif defined(__fast_memcmpq_defined) && defined(__CRT_HAVE_bcmpq)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpq))(__s1, __s2, __n_qwords); })
#elif defined(__fast_bcmpq_defined) && defined(__CRT_HAVE_memcmpq)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords),memcmpq,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpq))(__s1, __s2, __n_qwords); })
#elif defined(__fast_memcmpq_defined) && defined(__CRT_HAVE_memcmpq)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords),memcmpq,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpq))(__s1, __s2, __n_qwords); })
#elif defined(__fast_bcmpq_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpq)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpq))(__s1, __s2, __n_qwords); }
#elif defined(__fast_memcmpq_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpq)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpq))(__s1, __s2, __n_qwords); }
#elif defined(__CRT_HAVE_bcmpq)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords),(__s1,__s2,__n_qwords))
#elif defined(__CRT_HAVE_memcmpq)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords),memcmpq,(__s1,__s2,__n_qwords))
#else /* ... */
#include <libc/local/string/memcmpq.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpq)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpq))(__s1, __s2, __n_qwords); }
#endif /* !... */
#endif /* !__bcmpq_defined */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */

#ifdef __USE_KOS
#ifndef __bzeroc_defined
#define __bzeroc_defined
#if defined(__fast_bzeroc_defined) && defined(__CRT_HAVE_bzeroc)
__CEIDECLARE(__ATTR_LEAF __ATTR_OUT(1),void,__NOTHROW_NCX,bzeroc,(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroc))(__dst, __elem_count, __elem_size); })
#elif defined(__fast_bzeroc_defined)
__FORCELOCAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzeroc)(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroc))(__dst, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_bzeroc)
__CDECLARE_VOID(__ATTR_LEAF __ATTR_OUT(1),__NOTHROW_NCX,bzeroc,(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__elem_count,__elem_size))
#else /* ... */
#include <libc/local/string/bzeroc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bzeroc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzeroc)(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzeroc))(__dst, __elem_count, __elem_size); })
#endif /* !... */
#endif /* !__bzeroc_defined */
#ifndef __bcmpc_defined
#define __bcmpc_defined
#if defined(__fast_bcmpc_defined) && defined(__CRT_HAVE_bcmpc)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpc))(__s1, __s2, __elem_count, __elem_size); })
#elif defined(__fast_bcmpc_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpc)(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpc))(__s1, __s2, __elem_count, __elem_size); }
#elif defined(__fast_memcmpc_defined) && defined(__CRT_HAVE_bcmpc)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpc))(__s1, __s2, __elem_count, __elem_size); })
#elif defined(__fast_memcmpc_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpc)(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpc))(__s1, __s2, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_bcmpc)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__s1,__s2,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_memcmpc)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcmpc,(__s1,__s2,__elem_count,__elem_size))
#else /* ... */
#include <libc/local/string/memcmpc.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpc)(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpc))(__s1, __s2, __elem_count, __elem_size); }
#endif /* !... */
#endif /* !__bcmpc_defined */
#endif /* __USE_KOS */
#ifndef __bcmp_defined
#define __bcmp_defined
#if defined(__fast_bcmp_defined) && defined(__CRT_HAVE_bcmp)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmp))(__s1, __s2, __n_bytes); })
#elif defined(__fast_bcmp_defined)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmp))(__s1, __s2, __n_bytes); }
#elif defined(__fast_memcmp_defined) && defined(__CRT_HAVE_bcmp)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __n_bytes); })
#elif defined(__fast_memcmp_defined)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __n_bytes); }
#elif defined(__CRT_HAVE_bcmp)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_memcmp)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#else /* ... */
#include <libc/local/string/memcmp.h>
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp))(__s1, __s2, __n_bytes); }
#endif /* !... */
#endif /* !__bcmp_defined */
#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
extern "C++" {
#if defined(__fast_bcmpc_defined) && defined(__CRT_HAVE_bcmpc)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bcmpc,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpc))(__s1, __s2, __elem_count, __elem_size); })
#elif defined(__fast_bcmpc_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpc))(__s1, __s2, __elem_count, __elem_size); }
#elif defined(__fast_memcmpc_defined) && defined(__CRT_HAVE_bcmpc)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bcmpc,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpc))(__s1, __s2, __elem_count, __elem_size); })
#elif defined(__fast_memcmpc_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpc))(__s1, __s2, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_bcmpc)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bcmpc,(__s1,__s2,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_memcmpc)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcmpc,(__s1,__s2,__elem_count,__elem_size))
#else /* ... */
} /* extern "C++" */
#include <libc/local/string/memcmpc.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpc))(__s1, __s2, __elem_count, __elem_size); }
#endif /* !... */
} /* extern "C++" */
#endif /* __cplusplus && __USE_STRING_OVERLOADS */
#ifndef __index_defined
#define __index_defined
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,index,(char *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif __has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_index)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,index,(char *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),{ return __builtin_index(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_strchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,index,(char *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_index)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,index,(char *__restrict __haystack, int __needle),index,(__haystack,__needle))
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),index,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/strchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL index)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr))(__haystack, __needle); }
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char const *__NOTHROW_NCX(__LIBCCALL index)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL index)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#endif /* !__index_defined */
#ifndef __rindex_defined
#define __rindex_defined
#if __has_builtin(__builtin_strrchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,rindex,(char *__restrict __haystack, int __needle),strrchr,{ return __builtin_strrchr(__haystack, __needle); })
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),strrchr,{ return __builtin_strrchr(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),strrchr,{ return __builtin_strrchr(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif __has_builtin(__builtin_rindex) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rindex)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,rindex,(char *__restrict __haystack, int __needle),rindex,{ return __builtin_rindex(__haystack, __needle); })
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),rindex,{ return __builtin_rindex(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),{ return __builtin_rindex(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_strrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,rindex,(char *__restrict __haystack, int __needle),strrchr,(__haystack,__needle))
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),strrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),strrchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_rindex)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,rindex,(char *__restrict __haystack, int __needle),rindex,(__haystack,__needle))
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),rindex,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/strrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL rindex)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchr))(__haystack, __needle); }
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char const *__NOTHROW_NCX(__LIBCCALL rindex)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL rindex)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchr))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#endif /* !__rindex_defined */
#ifndef __strcasecmp_defined
#define __strcasecmp_defined
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),{ return __builtin_strcasecmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcasecmp)
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE___strcasecmp)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),__strcasecmp,(__s1,__s2))
#else /* ... */
#include <libc/local/string/strcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL strcasecmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))(__s1, __s2); })
#endif /* !... */
#endif /* !__strcasecmp_defined */
#ifndef __strncasecmp_defined
#define __strncasecmp_defined
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),{ return __builtin_strncasecmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_strncasecmp)
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strncmpi,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncmpi,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/string/strncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncasecmp)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#endif /* !__strncasecmp_defined */
#ifndef __ffs_defined
#define __ffs_defined
#if __has_builtin(__builtin_ffs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ffs)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffs,(int __i),{ return __builtin_ffs(__i); })
#elif defined(__CRT_HAVE_ffs)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffs,(int __i),(__i))
#elif defined(__CRT_HAVE_ffsl) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffs,(int __i),ffsl,(__i))
#elif defined(__CRT_HAVE_ffsll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffs,(int __i),ffsll,(__i))
#elif defined(__CRT_HAVE___ffs)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffs,(int __i),__ffs,(__i))
#else /* ... */
#include <libc/local/string/ffs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ffs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __STDC_INT_AS_UINT_T __NOTHROW(__LIBCCALL ffs)(int __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ffs))(__i); })
#endif /* !... */
#endif /* !__ffs_defined */
#ifdef __USE_KOS
#include <hybrid/__bit.h>
/* shift_t FFS(INTEGER i):
 *     FindFirstSet
 *     Returns the index (starting at 1 for 0x01) of the first
 *     1-bit in given value, or ZERO(0) if the given value is ZERO(0).
 *     >> assert(!x ||  (x &  (1 << (ffs(x)-1))));    // FFS-bit is set
 *     >> assert(!x || !(x & ((1 << (ffs(x)-1))-1))); // Less significant bits are clear */
#define ffs(i) __hybrid_ffs(i)
#endif /* !__USE_KOS */
#ifdef __USE_GNU
#if __has_builtin(__builtin_ffsl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ffsl)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffsl,(long __i),{ return __builtin_ffsl(__i); })
#elif defined(__CRT_HAVE_ffsl)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffsl,(long __i),(__i))
#elif defined(__CRT_HAVE_ffs) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffsl,(long __i),ffs,(__i))
#elif defined(__CRT_HAVE_ffsll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffsl,(long __i),ffsll,(__i))
#else /* ... */
#include <libc/local/string/ffsl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ffsl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __STDC_INT_AS_UINT_T __NOTHROW(__LIBCCALL ffsl)(long __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ffsl))(__i); })
#endif /* !... */
#if __has_builtin(__builtin_ffsll) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ffsll)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffsll,(__LONGLONG __i),{ return __builtin_ffsll(__i); })
#elif defined(__CRT_HAVE_ffsll)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffsll,(__LONGLONG __i),(__i))
#elif defined(__CRT_HAVE_ffs) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffsll,(__LONGLONG __i),ffs,(__i))
#elif defined(__CRT_HAVE_ffsl) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffsll,(__LONGLONG __i),ffsl,(__i))
#else /* ... */
#include <libc/local/string/ffsll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ffsll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __STDC_INT_AS_UINT_T __NOTHROW(__LIBCCALL ffsll)(__LONGLONG __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ffsll))(__i); })
#endif /* !... */
#endif /* __USE_GNU */
#ifndef __strlcat_defined
#define __strlcat_defined
#ifdef __CRT_HAVE_strlcat
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,strlcat,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __bufsize),(__dst,__src,__bufsize))
#else /* __CRT_HAVE_strlcat */
#include <libc/local/string/strlcat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strlcat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strlcat)(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlcat))(__dst, __src, __bufsize); })
#endif /* !__CRT_HAVE_strlcat */
#endif /* !__strlcat_defined */
#ifndef __strlcpy_defined
#define __strlcpy_defined
#ifdef __CRT_HAVE_strlcpy
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,strlcpy,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __bufsize),(__dst,__src,__bufsize))
#else /* __CRT_HAVE_strlcpy */
#include <libc/local/string/strlcpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strlcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strlcpy)(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlcpy))(__dst, __src, __bufsize); })
#endif /* !__CRT_HAVE_strlcpy */
#endif /* !__strlcpy_defined */
#endif /* __USE_MISC */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifndef __memccpy_defined
#define __memccpy_defined
#ifdef __CRT_HAVE_memccpy
__CDECLARE(__ATTR_LEAF __ATTR_INS(2, 4) __ATTR_OUTS(1, 4) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes),(__dst,__src,__needle,__num_bytes))
#elif defined(__CRT_HAVE__memccpy)
__CREDIRECT(__ATTR_LEAF __ATTR_INS(2, 4) __ATTR_OUTS(1, 4) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes),_memccpy,(__dst,__src,__needle,__num_bytes))
#elif defined(__CRT_HAVE___memccpy)
__CREDIRECT(__ATTR_LEAF __ATTR_INS(2, 4) __ATTR_OUTS(1, 4) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes),__memccpy,(__dst,__src,__needle,__num_bytes))
#else /* ... */
#include <libc/local/string/memccpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memccpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INS(2, 4) __ATTR_OUTS(1, 4) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memccpy)(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memccpy))(__dst, __src, __needle, __num_bytes); })
#endif /* !... */
#endif /* !__memccpy_defined */
#endif /* __USE_MISC || __USE_XOPEN */


#if defined(__fast_bzero_defined) && defined(__CRT_HAVE_bzero)
__CEIREDIRECT(__ATTR_OUTS(1, 2),void,__NOTHROW_NCX,__bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); })
#elif defined(__fast_bzero_defined) && defined(__CRT_HAVE___bzero)
__CEIDECLARE(__ATTR_OUTS(1, 2),void,__NOTHROW_NCX,__bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); })
#elif defined(__fast_bzero_defined) && defined(__CRT_HAVE_explicit_bzero)
__CEIREDIRECT(__ATTR_OUTS(1, 2),void,__NOTHROW_NCX,__bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); })
#elif defined(__fast_bzero_defined)
__FORCELOCAL __ATTR_OUTS(1, 2) void __NOTHROW_NCX(__LIBCCALL __bzero)(void *__restrict __dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); }
#elif defined(__CRT_HAVE_bzero)
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__CDECLARE_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
#include <libc/local/string/bzero.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(1, 2) void __NOTHROW_NCX(__LIBCCALL __bzero)(void *__restrict __dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzero))(__dst, __num_bytes); }
#endif /* !... */
#ifdef __CRT_HAVE_strtok_r
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char *,__NOTHROW_NCX,__strtok_r,(char *__str, char const *__delim, char **__restrict __save_ptr),strtok_r,(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE_strtok_s)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char *,__NOTHROW_NCX,__strtok_r,(char *__str, char const *__delim, char **__restrict __save_ptr),strtok_s,(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE___strtok_r)
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char *,__NOTHROW_NCX,__strtok_r,(char *__str, char const *__delim, char **__restrict __save_ptr),(__str,__delim,__save_ptr))
#else /* ... */
#include <libc/local/string/strtok_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1) char *__NOTHROW_NCX(__LIBCCALL __strtok_r)(char *__str, char const *__delim, char **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtok_r))(__str, __delim, __save_ptr); }
#endif /* !... */

#ifdef __USE_STRING_BWLQ
#if defined(__fast_memcpy_defined) && defined(__CRT_HAVE_memcpy)
/* Copy memory between non-overlapping memory blocks. */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,memcpyb,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))(__dst, __src, __n_bytes); })
#elif defined(__fast_memcpy_defined)
/* Copy memory between non-overlapping memory blocks. */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyb)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_memcpy)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,memcpyb,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/memcpy.h>
/* Copy memory between non-overlapping memory blocks. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyb)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy))(__dst, __src, (__SIZE_TYPE__)__n_bytes); }
#endif /* !... */
#if defined(__fast_mempcpy_defined) && defined(__CRT_HAVE_mempcpy)
/* Same as `memcpyb', but return `dst + n_bytes', rather than `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempcpyb,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))(__dst, __src, __n_bytes); })
#elif defined(__fast_mempcpy_defined) && defined(__CRT_HAVE___mempcpy)
/* Same as `memcpyb', but return `dst + n_bytes', rather than `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempcpyb,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))(__dst, __src, __n_bytes); })
#elif defined(__fast_mempcpy_defined)
/* Same as `memcpyb', but return `dst + n_bytes', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyb)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_mempcpy)
/* Same as `memcpyb', but return `dst + n_bytes', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempcpyb,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
/* Same as `memcpyb', but return `dst + n_bytes', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempcpyb,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/mempcpy.h>
/* Same as `memcpyb', but return `dst + n_bytes', rather than `dst' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyb)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpy))(__dst, __src, __n_bytes); }
#endif /* !... */
#if defined(__fast_memcpyw_defined) && defined(__CRT_HAVE_memcpyw)
/* Copy memory between non-overlapping memory blocks. */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyw))(__dst, __src, __n_words); })
#elif defined(__fast_memcpyw_defined) && __SIZEOF_WCHAR_T__ == 2 && defined(__CRT_HAVE_wmemcpy)
/* Copy memory between non-overlapping memory blocks. */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),wmemcpy,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyw))(__dst, __src, __n_words); })
#elif defined(__fast_memcpyw_defined) && defined(__LIBCCALL_IS_LIBDCALL) && defined(__CRT_HAVE_DOS$wmemcpy)
/* Copy memory between non-overlapping memory blocks. */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),DOS$wmemcpy,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyw))(__dst, __src, __n_words); })
#elif defined(__fast_memcpyw_defined)
/* Copy memory between non-overlapping memory blocks. */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyw)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyw))(__dst, __src, __n_words); }
#elif defined(__CRT_HAVE_memcpyw)
/* Copy memory between non-overlapping memory blocks. */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemcpy) && __SIZEOF_WCHAR_T__ == 2
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),wmemcpy,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemcpy) && defined(__LIBCCALL_IS_LIBDCALL)
/* Copy memory between non-overlapping memory blocks. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),DOS$wmemcpy,(__dst,__src,__n_words))
#else /* ... */
#include <libc/local/string/memcpyw.h>
/* Copy memory between non-overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpyw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyw)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyw))(__dst, __src, __n_words); })
#endif /* !... */
#if defined(__fast_mempcpyw_defined) && defined(__CRT_HAVE_mempcpyw)
/* Same as `memcpyw', but return `dst + N_WORDS', rather than `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyw))(__dst, __src, __n_words); })
#elif defined(__fast_mempcpyw_defined) && __SIZEOF_WCHAR_T__ == 2 && defined(__CRT_HAVE_wmempcpy)
/* Same as `memcpyw', but return `dst + N_WORDS', rather than `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),wmempcpy,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyw))(__dst, __src, __n_words); })
#elif defined(__fast_mempcpyw_defined) && defined(__LIBCCALL_IS_LIBDCALL) && defined(__CRT_HAVE_DOS$wmempcpy)
/* Same as `memcpyw', but return `dst + N_WORDS', rather than `dst' */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),DOS$wmempcpy,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyw))(__dst, __src, __n_words); })
#elif defined(__fast_mempcpyw_defined)
/* Same as `memcpyw', but return `dst + N_WORDS', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyw)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyw))(__dst, __src, __n_words); }
#elif defined(__CRT_HAVE_mempcpyw)
/* Same as `memcpyw', but return `dst + N_WORDS', rather than `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempcpy) && __SIZEOF_WCHAR_T__ == 2
/* Same as `memcpyw', but return `dst + N_WORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),wmempcpy,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempcpy) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `memcpyw', but return `dst + N_WORDS', rather than `dst' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),DOS$wmempcpy,(__dst,__src,__n_words))
#else /* ... */
#include <libc/local/string/mempcpyw.h>
/* Same as `memcpyw', but return `dst + N_WORDS', rather than `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempcpyw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyw)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyw))(__dst, __src, __n_words); })
#endif /* !... */
#if defined(__fast_memcpyl_defined) && defined(__CRT_HAVE_memcpyl)
/* Copy memory between non-overlapping memory blocks. */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyl))(__dst, __src, __n_dwords); })
#elif defined(__fast_memcpyl_defined) && __SIZEOF_WCHAR_T__ == 4 && defined(__CRT_HAVE_wmemcpy)
/* Copy memory between non-overlapping memory blocks. */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),wmemcpy,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyl))(__dst, __src, __n_dwords); })
#elif defined(__fast_memcpyl_defined) && defined(__LIBCCALL_IS_LIBKCALL) && defined(__CRT_HAVE_KOS$wmemcpy)
/* Copy memory between non-overlapping memory blocks. */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),KOS$wmemcpy,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyl))(__dst, __src, __n_dwords); })
#elif defined(__fast_memcpyl_defined)
/* Copy memory between non-overlapping memory blocks. */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyl)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyl))(__dst, __src, __n_dwords); }
#elif defined(__CRT_HAVE_memcpyl)
/* Copy memory between non-overlapping memory blocks. */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemcpy) && __SIZEOF_WCHAR_T__ == 4
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),wmemcpy,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemcpy) && defined(__LIBCCALL_IS_LIBKCALL)
/* Copy memory between non-overlapping memory blocks. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),KOS$wmemcpy,(__dst,__src,__n_dwords))
#else /* ... */
#include <libc/local/string/memcpyl.h>
/* Copy memory between non-overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpyl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyl)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyl))(__dst, __src, __n_dwords); })
#endif /* !... */
#if defined(__fast_mempcpyl_defined) && defined(__CRT_HAVE_mempcpyl)
/* Same as `memcpyl', but return `dst + N_DWORDS', rather than `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyl))(__dst, __src, __n_dwords); })
#elif defined(__fast_mempcpyl_defined) && __SIZEOF_WCHAR_T__ == 4 && defined(__CRT_HAVE_wmempcpy)
/* Same as `memcpyl', but return `dst + N_DWORDS', rather than `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),wmempcpy,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyl))(__dst, __src, __n_dwords); })
#elif defined(__fast_mempcpyl_defined) && defined(__LIBCCALL_IS_LIBKCALL) && defined(__CRT_HAVE_KOS$wmempcpy)
/* Same as `memcpyl', but return `dst + N_DWORDS', rather than `dst' */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),KOS$wmempcpy,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyl))(__dst, __src, __n_dwords); })
#elif defined(__fast_mempcpyl_defined)
/* Same as `memcpyl', but return `dst + N_DWORDS', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyl)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyl))(__dst, __src, __n_dwords); }
#elif defined(__CRT_HAVE_mempcpyl)
/* Same as `memcpyl', but return `dst + N_DWORDS', rather than `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempcpy) && __SIZEOF_WCHAR_T__ == 4
/* Same as `memcpyl', but return `dst + N_DWORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),wmempcpy,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempcpy) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `memcpyl', but return `dst + N_DWORDS', rather than `dst' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),KOS$wmempcpy,(__dst,__src,__n_dwords))
#else /* ... */
#include <libc/local/string/mempcpyl.h>
/* Same as `memcpyl', but return `dst + N_DWORDS', rather than `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempcpyl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyl)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyl))(__dst, __src, __n_dwords); })
#endif /* !... */
#if defined(__fast_memmove_defined) && defined(__CRT_HAVE_memmove)
/* Move memory between potentially overlapping memory blocks. */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,memmoveb,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmove))(__dst, __src, __n_bytes); })
#elif defined(__fast_memmove_defined)
/* Move memory between potentially overlapping memory blocks. */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveb)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmove))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_memmove)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,memmoveb,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/memmove.h>
/* Move memory between potentially overlapping memory blocks. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveb)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmove))(__dst, __src, (__SIZE_TYPE__)__n_bytes); }
#endif /* !... */
#if defined(__fast_mempmove_defined) && defined(__CRT_HAVE_mempmove)
/* Same as `memmoveb', but return `dst + n_bytes', rather than `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempmoveb,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmove,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmove))(__dst, __src, __n_bytes); })
#elif defined(__fast_mempmove_defined)
/* Same as `memmoveb', but return `dst + n_bytes', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveb)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmove))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_mempmove)
/* Same as `memmoveb', but return `dst + n_bytes', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempmoveb,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmove,(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/mempmove.h>
/* Same as `memmoveb', but return `dst + n_bytes', rather than `dst' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveb)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmove))(__dst, __src, __n_bytes); }
#endif /* !... */
#if defined(__fast_memmovew_defined) && defined(__CRT_HAVE_memmovew)
/* Move memory between potentially overlapping memory blocks. */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovew))(__dst, __src, __n_words); })
#elif defined(__fast_memmovew_defined) && __SIZEOF_WCHAR_T__ == 2 && defined(__CRT_HAVE_wmemmove)
/* Move memory between potentially overlapping memory blocks. */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmemmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovew))(__dst, __src, __n_words); })
#elif defined(__fast_memmovew_defined) && defined(__LIBCCALL_IS_LIBDCALL) && defined(__CRT_HAVE_DOS$wmemmove)
/* Move memory between potentially overlapping memory blocks. */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmemmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovew))(__dst, __src, __n_words); })
#elif defined(__fast_memmovew_defined)
/* Move memory between potentially overlapping memory blocks. */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovew)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovew))(__dst, __src, __n_words); }
#elif defined(__CRT_HAVE_memmovew)
/* Move memory between potentially overlapping memory blocks. */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 2
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemmove) && defined(__LIBCCALL_IS_LIBDCALL)
/* Move memory between potentially overlapping memory blocks. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmemmove,(__dst,__src,__n_words))
#else /* ... */
#include <libc/local/string/memmovew.h>
/* Move memory between potentially overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmovew, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovew)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovew))(__dst, __src, __n_words); })
#endif /* !... */
#if defined(__fast_mempmovew_defined) && defined(__CRT_HAVE_mempmovew)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovew))(__dst, __src, __n_words); })
#elif defined(__fast_mempmovew_defined) && __SIZEOF_WCHAR_T__ == 2 && defined(__CRT_HAVE_wmempmove)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmempmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovew))(__dst, __src, __n_words); })
#elif defined(__fast_mempmovew_defined) && defined(__LIBCCALL_IS_LIBDCALL) && defined(__CRT_HAVE_DOS$wmempmove)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmempmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovew))(__dst, __src, __n_words); })
#elif defined(__fast_mempmovew_defined)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovew)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovew))(__dst, __src, __n_words); }
#elif defined(__CRT_HAVE_mempmovew)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 2
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmempmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempmove) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmempmove,(__dst,__src,__n_words))
#else /* ... */
#include <libc/local/string/mempmovew.h>
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmovew, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovew)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovew))(__dst, __src, __n_words); })
#endif /* !... */
#if defined(__fast_memmovel_defined) && defined(__CRT_HAVE_memmovel)
/* Move memory between potentially overlapping memory blocks. */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovel))(__dst, __src, __n_dwords); })
#elif defined(__fast_memmovel_defined) && __SIZEOF_WCHAR_T__ == 4 && defined(__CRT_HAVE_wmemmove)
/* Move memory between potentially overlapping memory blocks. */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovel))(__dst, __src, __n_dwords); })
#elif defined(__fast_memmovel_defined) && defined(__LIBCCALL_IS_LIBKCALL) && defined(__CRT_HAVE_KOS$wmemmove)
/* Move memory between potentially overlapping memory blocks. */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmemmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovel))(__dst, __src, __n_dwords); })
#elif defined(__fast_memmovel_defined)
/* Move memory between potentially overlapping memory blocks. */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovel)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovel))(__dst, __src, __n_dwords); }
#elif defined(__CRT_HAVE_memmovel)
/* Move memory between potentially overlapping memory blocks. */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 4
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemmove) && defined(__LIBCCALL_IS_LIBKCALL)
/* Move memory between potentially overlapping memory blocks. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmemmove,(__dst,__src,__n_dwords))
#else /* ... */
#include <libc/local/string/memmovel.h>
/* Move memory between potentially overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmovel, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovel)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovel))(__dst, __src, __n_dwords); })
#endif /* !... */
#if defined(__fast_mempmovel_defined) && defined(__CRT_HAVE_mempmovel)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovel))(__dst, __src, __n_dwords); })
#elif defined(__fast_mempmovel_defined) && __SIZEOF_WCHAR_T__ == 4 && defined(__CRT_HAVE_wmempmove)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmempmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovel))(__dst, __src, __n_dwords); })
#elif defined(__fast_mempmovel_defined) && defined(__LIBCCALL_IS_LIBKCALL) && defined(__CRT_HAVE_KOS$wmempmove)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmempmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovel))(__dst, __src, __n_dwords); })
#elif defined(__fast_mempmovel_defined)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovel)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovel))(__dst, __src, __n_dwords); }
#elif defined(__CRT_HAVE_mempmovel)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 4
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmempmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempmove) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmempmove,(__dst,__src,__n_dwords))
#else /* ... */
#include <libc/local/string/mempmovel.h>
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmovel, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovel)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovel))(__dst, __src, __n_dwords); })
#endif /* !... */
#ifdef __USE_KOS
#if defined(__fast_memmoveup_defined) && defined(__CRT_HAVE_memmoveup)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_bytes') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,memmoveupb,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmoveup,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveup))(__dst, __src, __n_bytes); })
#elif defined(__fast_memmoveup_defined)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_bytes') */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveupb)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveup))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_memmoveup)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_bytes') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,memmoveupb,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmoveup,(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/memmoveup.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_bytes') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveupb)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveup))(__dst, __src, __n_bytes); }
#endif /* !... */
#if defined(__fast_memmovedown_defined) && defined(__CRT_HAVE_memmovedown)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_bytes') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,memmovedownb,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmovedown,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedown))(__dst, __src, __n_bytes); })
#elif defined(__fast_memmovedown_defined)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_bytes') */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovedownb)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedown))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_memmovedown)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_bytes') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,memmovedownb,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmovedown,(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/memmovedown.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_bytes') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovedownb)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedown))(__dst, __src, __n_bytes); }
#endif /* !... */
#if defined(__fast_mempmoveup_defined) && defined(__CRT_HAVE_mempmoveup)
/* Same as `memmoveb', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempmoveupb,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmoveup,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveup))(__dst, __src, __n_bytes); })
#elif defined(__fast_mempmoveup_defined)
/* Same as `memmoveb', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes') */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveupb)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveup))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_mempmoveup)
/* Same as `memmoveb', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempmoveupb,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmoveup,(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/mempmoveup.h>
/* Same as `memmoveb', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveupb)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveup))(__dst, __src, __n_bytes); }
#endif /* !... */
#if defined(__fast_mempmovedown_defined) && defined(__CRT_HAVE_mempmovedown)
/* Same as `memmoveb', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempmovedownb,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmovedown,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedown))(__dst, __src, __n_bytes); })
#elif defined(__fast_mempmovedown_defined)
/* Same as `memmoveb', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovedownb)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedown))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_mempmovedown)
/* Same as `memmoveb', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempmovedownb,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmovedown,(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/mempmovedown.h>
/* Same as `memmoveb', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovedownb)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedown))(__dst, __src, __n_bytes); }
#endif /* !... */
#if defined(__fast_memmoveupw_defined) && defined(__CRT_HAVE_memmoveupw)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupw))(__dst, __src, __n_words); })
#elif defined(__fast_memmoveupw_defined) && defined(__CRT_HAVE_memmovew)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),memmovew,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupw))(__dst, __src, __n_words); })
#elif defined(__fast_memmoveupw_defined) && __SIZEOF_WCHAR_T__ == 2 && defined(__CRT_HAVE_wmemmove)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmemmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupw))(__dst, __src, __n_words); })
#elif defined(__fast_memmoveupw_defined) && defined(__LIBCCALL_IS_LIBDCALL) && defined(__CRT_HAVE_DOS$wmemmove)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmemmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupw))(__dst, __src, __n_words); })
#elif defined(__fast_memmoveupw_defined)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveupw)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupw))(__dst, __src, __n_words); }
#elif defined(__CRT_HAVE_memmoveupw)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_memmovew)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),memmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 2
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemmove) && defined(__LIBCCALL_IS_LIBDCALL)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmemmove,(__dst,__src,__n_words))
#else /* ... */
#include <libc/local/string/memmoveupw.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmoveupw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveupw)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupw))(__dst, __src, __n_words); })
#endif /* !... */
#if defined(__fast_memmovedownw_defined) && defined(__CRT_HAVE_memmovedownw)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownw))(__dst, __src, __n_words); })
#elif defined(__fast_memmovedownw_defined) && defined(__CRT_HAVE_memmovew)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),memmovew,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownw))(__dst, __src, __n_words); })
#elif defined(__fast_memmovedownw_defined) && __SIZEOF_WCHAR_T__ == 2 && defined(__CRT_HAVE_wmemmove)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmemmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownw))(__dst, __src, __n_words); })
#elif defined(__fast_memmovedownw_defined) && defined(__LIBCCALL_IS_LIBDCALL) && defined(__CRT_HAVE_DOS$wmemmove)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmemmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownw))(__dst, __src, __n_words); })
#elif defined(__fast_memmovedownw_defined)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovedownw)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownw))(__dst, __src, __n_words); }
#elif defined(__CRT_HAVE_memmovedownw)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_memmovew)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),memmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 2
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemmove) && defined(__LIBCCALL_IS_LIBDCALL)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmemmove,(__dst,__src,__n_words))
#else /* ... */
#include <libc/local/string/memmovedownw.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmovedownw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovedownw)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownw))(__dst, __src, __n_words); })
#endif /* !... */
#if defined(__fast_mempmoveupw_defined) && defined(__CRT_HAVE_mempmoveupw)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupw))(__dst, __src, __n_words); })
#elif defined(__fast_mempmoveupw_defined) && defined(__CRT_HAVE_mempmovew)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),mempmovew,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupw))(__dst, __src, __n_words); })
#elif defined(__fast_mempmoveupw_defined) && __SIZEOF_WCHAR_T__ == 2 && defined(__CRT_HAVE_wmempmove)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmempmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupw))(__dst, __src, __n_words); })
#elif defined(__fast_mempmoveupw_defined) && defined(__LIBCCALL_IS_LIBDCALL) && defined(__CRT_HAVE_DOS$wmempmove)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmempmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupw))(__dst, __src, __n_words); })
#elif defined(__fast_mempmoveupw_defined)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveupw)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupw))(__dst, __src, __n_words); }
#elif defined(__CRT_HAVE_mempmoveupw)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_mempmovew)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),mempmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 2
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmempmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempmove) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmempmove,(__dst,__src,__n_words))
#else /* ... */
#include <libc/local/string/mempmoveupw.h>
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmoveupw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveupw)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveupw))(__dst, __src, __n_words); })
#endif /* !... */
#if defined(__fast_mempmovedownw_defined) && defined(__CRT_HAVE_mempmovedownw)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownw))(__dst, __src, __n_words); })
#elif defined(__fast_mempmovedownw_defined) && defined(__CRT_HAVE_mempmovew)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),mempmovew,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownw))(__dst, __src, __n_words); })
#elif defined(__fast_mempmovedownw_defined) && __SIZEOF_WCHAR_T__ == 2 && defined(__CRT_HAVE_wmempmove)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmempmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownw))(__dst, __src, __n_words); })
#elif defined(__fast_mempmovedownw_defined) && defined(__LIBCCALL_IS_LIBDCALL) && defined(__CRT_HAVE_DOS$wmempmove)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmempmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownw))(__dst, __src, __n_words); })
#elif defined(__fast_mempmovedownw_defined)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovedownw)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownw))(__dst, __src, __n_words); }
#elif defined(__CRT_HAVE_mempmovedownw)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_mempmovew)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),mempmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 2
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmempmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempmove) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmempmove,(__dst,__src,__n_words))
#else /* ... */
#include <libc/local/string/mempmovedownw.h>
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmovedownw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovedownw)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedownw))(__dst, __src, __n_words); })
#endif /* !... */
#if defined(__fast_memmoveupl_defined) && defined(__CRT_HAVE_memmoveupl)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupl))(__dst, __src, __n_dwords); })
#elif defined(__fast_memmoveupl_defined) && defined(__CRT_HAVE_memmovel)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupl))(__dst, __src, __n_dwords); })
#elif defined(__fast_memmoveupl_defined) && __SIZEOF_WCHAR_T__ == 4 && defined(__CRT_HAVE_wmemmove)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupl))(__dst, __src, __n_dwords); })
#elif defined(__fast_memmoveupl_defined) && defined(__LIBCCALL_IS_LIBKCALL) && defined(__CRT_HAVE_KOS$wmemmove)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmemmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupl))(__dst, __src, __n_dwords); })
#elif defined(__fast_memmoveupl_defined)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveupl)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupl))(__dst, __src, __n_dwords); }
#elif defined(__CRT_HAVE_memmoveupl)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_memmovel)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 4
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemmove) && defined(__LIBCCALL_IS_LIBKCALL)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmemmove,(__dst,__src,__n_dwords))
#else /* ... */
#include <libc/local/string/memmoveupl.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmoveupl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveupl)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupl))(__dst, __src, __n_dwords); })
#endif /* !... */
#if defined(__fast_memmovedownl_defined) && defined(__CRT_HAVE_memmovedownl)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownl))(__dst, __src, __n_dwords); })
#elif defined(__fast_memmovedownl_defined) && defined(__CRT_HAVE_memmovel)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownl))(__dst, __src, __n_dwords); })
#elif defined(__fast_memmovedownl_defined) && __SIZEOF_WCHAR_T__ == 4 && defined(__CRT_HAVE_wmemmove)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownl))(__dst, __src, __n_dwords); })
#elif defined(__fast_memmovedownl_defined) && defined(__LIBCCALL_IS_LIBKCALL) && defined(__CRT_HAVE_KOS$wmemmove)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmemmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownl))(__dst, __src, __n_dwords); })
#elif defined(__fast_memmovedownl_defined)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovedownl)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownl))(__dst, __src, __n_dwords); }
#elif defined(__CRT_HAVE_memmovedownl)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_memmovel)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 4
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemmove) && defined(__LIBCCALL_IS_LIBKCALL)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmemmove,(__dst,__src,__n_dwords))
#else /* ... */
#include <libc/local/string/memmovedownl.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmovedownl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovedownl)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownl))(__dst, __src, __n_dwords); })
#endif /* !... */
#if defined(__fast_mempmoveupl_defined) && defined(__CRT_HAVE_mempmoveupl)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupl))(__dst, __src, __n_dwords); })
#elif defined(__fast_mempmoveupl_defined) && defined(__CRT_HAVE_mempmovel)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),mempmovel,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupl))(__dst, __src, __n_dwords); })
#elif defined(__fast_mempmoveupl_defined) && __SIZEOF_WCHAR_T__ == 4 && defined(__CRT_HAVE_wmempmove)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmempmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupl))(__dst, __src, __n_dwords); })
#elif defined(__fast_mempmoveupl_defined) && defined(__LIBCCALL_IS_LIBKCALL) && defined(__CRT_HAVE_KOS$wmempmove)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmempmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupl))(__dst, __src, __n_dwords); })
#elif defined(__fast_mempmoveupl_defined)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveupl)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupl))(__dst, __src, __n_dwords); }
#elif defined(__CRT_HAVE_mempmoveupl)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_mempmovel)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),mempmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 4
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmempmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempmove) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmempmove,(__dst,__src,__n_dwords))
#else /* ... */
#include <libc/local/string/mempmoveupl.h>
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmoveupl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveupl)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveupl))(__dst, __src, __n_dwords); })
#endif /* !... */
#if defined(__fast_mempmovedownl_defined) && defined(__CRT_HAVE_mempmovedownl)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownl))(__dst, __src, __n_dwords); })
#elif defined(__fast_mempmovedownl_defined) && defined(__CRT_HAVE_mempmovel)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),mempmovel,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownl))(__dst, __src, __n_dwords); })
#elif defined(__fast_mempmovedownl_defined) && __SIZEOF_WCHAR_T__ == 4 && defined(__CRT_HAVE_wmempmove)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmempmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownl))(__dst, __src, __n_dwords); })
#elif defined(__fast_mempmovedownl_defined) && defined(__LIBCCALL_IS_LIBKCALL) && defined(__CRT_HAVE_KOS$wmempmove)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmempmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownl))(__dst, __src, __n_dwords); })
#elif defined(__fast_mempmovedownl_defined)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovedownl)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownl))(__dst, __src, __n_dwords); }
#elif defined(__CRT_HAVE_mempmovedownl)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_mempmovel)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),mempmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 4
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmempmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempmove) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmempmove,(__dst,__src,__n_dwords))
#else /* ... */
#include <libc/local/string/mempmovedownl.h>
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmovedownl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovedownl)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedownl))(__dst, __src, __n_dwords); })
#endif /* !... */
#endif /* __USE_KOS */
#if defined(__fast_memset_defined) && defined(__CRT_HAVE_memset)
/* Fill memory with a given byte */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memsetb,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))(__dst, __byte, __n_bytes); })
#elif defined(__fast_memset_defined)
/* Fill memory with a given byte */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetb)(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))(__dst, __byte, __n_bytes); }
#elif defined(__CRT_HAVE_memset)
/* Fill memory with a given byte */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memsetb,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* ... */
#include <libc/local/string/memset.h>
/* Fill memory with a given byte */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetb)(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memset))(__dst, __byte, (__SIZE_TYPE__)__n_bytes); }
#endif /* !... */
#if defined(__fast_mempset_defined) && defined(__CRT_HAVE_mempset)
/* Same as `memsetb', but return `dst + n_bytes', rather than `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempsetb,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),mempset,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempset))(__dst, __byte, __n_bytes); })
#elif defined(__fast_mempset_defined)
/* Same as `memsetb', but return `dst + n_bytes', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetb)(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempset))(__dst, __byte, __n_bytes); }
#elif defined(__CRT_HAVE_mempset)
/* Same as `memsetb', but return `dst + n_bytes', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempsetb,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),mempset,(__dst,__byte,__n_bytes))
#else /* ... */
#include <libc/local/string/mempset.h>
/* Same as `memsetb', but return `dst + n_bytes', rather than `dst' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetb)(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempset))(__dst, __byte, __n_bytes); }
#endif /* !... */
#if defined(__fast_memsetw_defined) && defined(__CRT_HAVE_memsetw)
/* Fill memory with a given word */
__CEIDECLARE(__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetw))(__dst, __word, __n_words); })
#elif defined(__fast_memsetw_defined) && __SIZEOF_WCHAR_T__ == 2 && defined(__CRT_HAVE_wmemset)
/* Fill memory with a given word */
__CEIREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),wmemset,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetw))(__dst, __word, __n_words); })
#elif defined(__fast_memsetw_defined) && defined(__LIBCCALL_IS_LIBDCALL) && defined(__CRT_HAVE_DOS$wmemset)
/* Fill memory with a given word */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),DOS$wmemset,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetw))(__dst, __word, __n_words); })
#elif defined(__fast_memsetw_defined)
/* Fill memory with a given word */
__FORCELOCAL __ATTR_LEAF __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetw)(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetw))(__dst, __word, __n_words); }
#elif defined(__CRT_HAVE_memsetw)
/* Fill memory with a given word */
__CDECLARE(__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_wmemset) && __SIZEOF_WCHAR_T__ == 2
/* Fill memory with a given word */
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),wmemset,(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemset) && defined(__LIBCCALL_IS_LIBDCALL)
/* Fill memory with a given word */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),DOS$wmemset,(__dst,__word,__n_words))
#else /* ... */
#include <libc/local/string/memsetw.h>
/* Fill memory with a given word */
__NAMESPACE_LOCAL_USING_OR_IMPL(memsetw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetw)(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetw))(__dst, __word, __n_words); })
#endif /* !... */
#if defined(__fast_mempsetw_defined) && defined(__CRT_HAVE_mempsetw)
/* Same as `memsetw', but return `dst + N_WORDS', rather than `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetw))(__dst, __word, __n_words); })
#elif defined(__fast_mempsetw_defined) && __SIZEOF_WCHAR_T__ == 2 && defined(__CRT_HAVE_wmempset)
/* Same as `memsetw', but return `dst + N_WORDS', rather than `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),wmempset,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetw))(__dst, __word, __n_words); })
#elif defined(__fast_mempsetw_defined) && defined(__LIBCCALL_IS_LIBDCALL) && defined(__CRT_HAVE_DOS$wmempset)
/* Same as `memsetw', but return `dst + N_WORDS', rather than `dst' */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),DOS$wmempset,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetw))(__dst, __word, __n_words); })
#elif defined(__fast_mempsetw_defined)
/* Same as `memsetw', but return `dst + N_WORDS', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetw)(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetw))(__dst, __word, __n_words); }
#elif defined(__CRT_HAVE_mempsetw)
/* Same as `memsetw', but return `dst + N_WORDS', rather than `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_wmempset) && __SIZEOF_WCHAR_T__ == 2
/* Same as `memsetw', but return `dst + N_WORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),wmempset,(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempset) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `memsetw', but return `dst + N_WORDS', rather than `dst' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),DOS$wmempset,(__dst,__word,__n_words))
#else /* ... */
#include <libc/local/string/mempsetw.h>
/* Same as `memsetw', but return `dst + N_WORDS', rather than `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempsetw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_OUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetw)(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetw))(__dst, __word, __n_words); })
#endif /* !... */
#if defined(__fast_memsetl_defined) && defined(__CRT_HAVE_memsetl)
/* Fill memory with a given dword */
__CEIDECLARE(__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetl))(__dst, __dword, __n_dwords); })
#elif defined(__fast_memsetl_defined) && __SIZEOF_WCHAR_T__ == 4 && defined(__CRT_HAVE_wmemset)
/* Fill memory with a given dword */
__CEIREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmemset,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetl))(__dst, __dword, __n_dwords); })
#elif defined(__fast_memsetl_defined) && defined(__LIBCCALL_IS_LIBKCALL) && defined(__CRT_HAVE_KOS$wmemset)
/* Fill memory with a given dword */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),KOS$wmemset,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetl))(__dst, __dword, __n_dwords); })
#elif defined(__fast_memsetl_defined)
/* Fill memory with a given dword */
__FORCELOCAL __ATTR_LEAF __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetl)(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetl))(__dst, __dword, __n_dwords); }
#elif defined(__CRT_HAVE_memsetl)
/* Fill memory with a given dword */
__CDECLARE(__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_wmemset) && __SIZEOF_WCHAR_T__ == 4
/* Fill memory with a given dword */
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmemset,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemset) && defined(__LIBCCALL_IS_LIBKCALL)
/* Fill memory with a given dword */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),KOS$wmemset,(__dst,__dword,__n_dwords))
#else /* ... */
#include <libc/local/string/memsetl.h>
/* Fill memory with a given dword */
__NAMESPACE_LOCAL_USING_OR_IMPL(memsetl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetl)(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetl))(__dst, __dword, __n_dwords); })
#endif /* !... */
#if defined(__fast_mempsetl_defined) && defined(__CRT_HAVE_mempsetl)
/* Same as `memsetl', but return `dst + N_DWORDS', rather than `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetl))(__dst, __dword, __n_dwords); })
#elif defined(__fast_mempsetl_defined) && __SIZEOF_WCHAR_T__ == 4 && defined(__CRT_HAVE_wmempset)
/* Same as `memsetl', but return `dst + N_DWORDS', rather than `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmempset,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetl))(__dst, __dword, __n_dwords); })
#elif defined(__fast_mempsetl_defined) && defined(__LIBCCALL_IS_LIBKCALL) && defined(__CRT_HAVE_KOS$wmempset)
/* Same as `memsetl', but return `dst + N_DWORDS', rather than `dst' */
__COMPILER_CEIREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),KOS$wmempset,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetl))(__dst, __dword, __n_dwords); })
#elif defined(__fast_mempsetl_defined)
/* Same as `memsetl', but return `dst + N_DWORDS', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetl)(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetl))(__dst, __dword, __n_dwords); }
#elif defined(__CRT_HAVE_mempsetl)
/* Same as `memsetl', but return `dst + N_DWORDS', rather than `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_wmempset) && __SIZEOF_WCHAR_T__ == 4
/* Same as `memsetl', but return `dst + N_DWORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmempset,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempset) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `memsetl', but return `dst + N_DWORDS', rather than `dst' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),KOS$wmempset,(__dst,__dword,__n_dwords))
#else /* ... */
#include <libc/local/string/mempsetl.h>
/* Same as `memsetl', but return `dst + N_DWORDS', rather than `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempsetl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_OUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetl)(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetl))(__dst, __dword, __n_dwords); })
#endif /* !... */
#if defined(__fast_memcmp_defined) && defined(__CRT_HAVE_memcmp)
/* Compare memory buffers and return the difference of the first non-matching byte */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcmpb,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __n_bytes); })
#elif defined(__fast_memcmp_defined)
/* Compare memory buffers and return the difference of the first non-matching byte */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memcmpb)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __n_bytes); }
#elif defined(__CRT_HAVE_memcmp)
/* Compare memory buffers and return the difference of the first non-matching byte */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcmpb,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE___gcc_bcmp)
/* Compare memory buffers and return the difference of the first non-matching byte */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcmpb,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),__gcc_bcmp,(__s1,__s2,__n_bytes))
#else /* ... */
#include <libc/local/string/memcmp.h>
/* Compare memory buffers and return the difference of the first non-matching byte */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memcmpb)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp))(__s1, __s2, __n_bytes); }
#endif /* !... */
#if defined(__fast_memcmpw_defined) && defined(__CRT_HAVE_memcmpw)
/* Compare memory buffers and return the difference of the first non-matching word */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpw))(__s1, __s2, __n_words); })
#elif defined(__fast_memcmpw_defined) && __SIZEOF_WCHAR_T__ == 2 && defined(__CRT_HAVE_wmemcmp)
/* Compare memory buffers and return the difference of the first non-matching word */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),wmemcmp,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpw))(__s1, __s2, __n_words); })
#elif defined(__fast_memcmpw_defined) && defined(__LIBCCALL_IS_LIBDCALL) && defined(__CRT_HAVE_DOS$wmemcmp)
/* Compare memory buffers and return the difference of the first non-matching word */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__LIBCCALL,memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),DOS$wmemcmp,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpw))(__s1, __s2, __n_words); })
#elif defined(__fast_memcmpw_defined)
/* Compare memory buffers and return the difference of the first non-matching word */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL memcmpw)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpw))(__s1, __s2, __n_words); }
#elif defined(__CRT_HAVE_memcmpw)
/* Compare memory buffers and return the difference of the first non-matching word */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),(__s1,__s2,__n_words))
#elif defined(__CRT_HAVE_wmemcmp) && __SIZEOF_WCHAR_T__ == 2
/* Compare memory buffers and return the difference of the first non-matching word */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),wmemcmp,(__s1,__s2,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemcmp) && defined(__LIBCCALL_IS_LIBDCALL)
/* Compare memory buffers and return the difference of the first non-matching word */
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__LIBCCALL,memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),DOS$wmemcmp,(__s1,__s2,__n_words))
#else /* ... */
#include <libc/local/string/memcmpw.h>
/* Compare memory buffers and return the difference of the first non-matching word */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcmpw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL memcmpw)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpw))(__s1, __s2, __n_words); })
#endif /* !... */
#if defined(__fast_memcmpl_defined) && defined(__CRT_HAVE_memcmpl)
/* Compare memory buffers and return the difference of the first non-matching dword */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpl))(__s1, __s2, __n_dwords); })
#elif defined(__fast_memcmpl_defined) && __SIZEOF_WCHAR_T__ == 4 && defined(__CRT_HAVE_wmemcmp)
/* Compare memory buffers and return the difference of the first non-matching dword */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),wmemcmp,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpl))(__s1, __s2, __n_dwords); })
#elif defined(__fast_memcmpl_defined) && defined(__LIBCCALL_IS_LIBKCALL) && defined(__CRT_HAVE_KOS$wmemcmp)
/* Compare memory buffers and return the difference of the first non-matching dword */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__LIBCCALL,memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),KOS$wmemcmp,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpl))(__s1, __s2, __n_dwords); })
#elif defined(__fast_memcmpl_defined)
/* Compare memory buffers and return the difference of the first non-matching dword */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL memcmpl)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpl))(__s1, __s2, __n_dwords); }
#elif defined(__CRT_HAVE_memcmpl)
/* Compare memory buffers and return the difference of the first non-matching dword */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),(__s1,__s2,__n_dwords))
#elif defined(__CRT_HAVE_wmemcmp) && __SIZEOF_WCHAR_T__ == 4
/* Compare memory buffers and return the difference of the first non-matching dword */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),wmemcmp,(__s1,__s2,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemcmp) && defined(__LIBCCALL_IS_LIBKCALL)
/* Compare memory buffers and return the difference of the first non-matching dword */
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__LIBCCALL,memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),KOS$wmemcmp,(__s1,__s2,__n_dwords))
#else /* ... */
#include <libc/local/string/memcmpl.h>
/* Compare memory buffers and return the difference of the first non-matching dword */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcmpl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL memcmpl)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpl))(__s1, __s2, __n_dwords); })
#endif /* !... */
#if defined(__fast_memchr_defined) && defined(__CRT_HAVE_memchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memchrb,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memchr,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __needle, __n_bytes); })
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memchrb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memchr,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __needle, __n_bytes); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memchrb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memchr,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memchr_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrb)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __needle, __n_bytes); }
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __needle, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memchrb,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memchr,(__haystack,__needle,__n_bytes))
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memchrb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memchr,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memchrb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memchr,(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrb)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))(__haystack, __needle, (__SIZE_TYPE__)__n_bytes); }
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))(__haystack, __needle, (__SIZE_TYPE__)__n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))(__haystack, __needle, (__SIZE_TYPE__)__n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if defined(__fast_memchrw_defined) && defined(__CRT_HAVE_memchrw)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memchrw,(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memchrw,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(__haystack, __needle, __n_words); })
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ const *,__NOTHROW_NCX,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memchrw,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(__haystack, __needle, __n_words); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(__haystack, __needle, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memchrw_defined) && __SIZEOF_WCHAR_T__ == 2 && defined(__CRT_HAVE_wmemchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memchrw,(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),wmemchr,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(__haystack, __needle, __n_words); })
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ const *,__NOTHROW_NCX,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),wmemchr,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(__haystack, __needle, __n_words); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),wmemchr,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(__haystack, __needle, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memchrw_defined) && defined(__LIBCCALL_IS_LIBDCALL) && defined(__CRT_HAVE_DOS$wmemchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memchrw,(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),DOS$wmemchr,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(__haystack, __needle, __n_words); })
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ const *,__NOTHROW_NCX,__LIBCCALL,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),DOS$wmemchr,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(__haystack, __needle, __n_words); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),DOS$wmemchr,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(__haystack, __needle, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memchrw_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrw)(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(__haystack, __needle, __n_words); }
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(__haystack, __needle, __n_words); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(__haystack, __needle, __n_words); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memchrw)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memchrw,(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memchrw,(__haystack,__needle,__n_words))
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ const *,__NOTHROW_NCX,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memchrw,(__haystack,__needle,__n_words))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),(__haystack,__needle,__n_words))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_wmemchr) && __SIZEOF_WCHAR_T__ == 2
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memchrw,(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),wmemchr,(__haystack,__needle,__n_words))
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ const *,__NOTHROW_NCX,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),wmemchr,(__haystack,__needle,__n_words))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),wmemchr,(__haystack,__needle,__n_words))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wmemchr) && defined(__LIBCCALL_IS_LIBDCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memchrw,(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),DOS$wmemchr,(__haystack,__needle,__n_words))
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ const *,__NOTHROW_NCX,__LIBCCALL,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),DOS$wmemchr,(__haystack,__needle,__n_words))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),DOS$wmemchr,(__haystack,__needle,__n_words))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memchrw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrw)(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrw))(__haystack, __needle, __n_words); }
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrw))(__haystack, __needle, __n_words); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memchrw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrw))(__haystack, __needle, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if defined(__fast_memchrl_defined) && defined(__CRT_HAVE_memchrl)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memchrl,(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memchrl,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(__haystack, __needle, __n_dwords); })
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ const *,__NOTHROW_NCX,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memchrl,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(__haystack, __needle, __n_dwords); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(__haystack, __needle, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memchrl_defined) && __SIZEOF_WCHAR_T__ == 4 && defined(__CRT_HAVE_wmemchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memchrl,(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),wmemchr,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(__haystack, __needle, __n_dwords); })
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ const *,__NOTHROW_NCX,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),wmemchr,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(__haystack, __needle, __n_dwords); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),wmemchr,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(__haystack, __needle, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memchrl_defined) && defined(__LIBCCALL_IS_LIBKCALL) && defined(__CRT_HAVE_KOS$wmemchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memchrl,(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),KOS$wmemchr,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(__haystack, __needle, __n_dwords); })
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ const *,__NOTHROW_NCX,__LIBCCALL,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),KOS$wmemchr,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(__haystack, __needle, __n_dwords); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),KOS$wmemchr,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(__haystack, __needle, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memchrl_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrl)(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(__haystack, __needle, __n_dwords); }
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(__haystack, __needle, __n_dwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(__haystack, __needle, __n_dwords); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memchrl)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memchrl,(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memchrl,(__haystack,__needle,__n_dwords))
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ const *,__NOTHROW_NCX,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memchrl,(__haystack,__needle,__n_dwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),(__haystack,__needle,__n_dwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_wmemchr) && __SIZEOF_WCHAR_T__ == 4
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memchrl,(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),wmemchr,(__haystack,__needle,__n_dwords))
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ const *,__NOTHROW_NCX,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),wmemchr,(__haystack,__needle,__n_dwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),wmemchr,(__haystack,__needle,__n_dwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wmemchr) && defined(__LIBCCALL_IS_LIBKCALL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memchrl,(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),KOS$wmemchr,(__haystack,__needle,__n_dwords))
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ const *,__NOTHROW_NCX,__LIBCCALL,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),KOS$wmemchr,(__haystack,__needle,__n_dwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),KOS$wmemchr,(__haystack,__needle,__n_dwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memchrl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrl)(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrl))(__haystack, __needle, __n_dwords); }
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrl))(__haystack, __needle, __n_dwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memchrl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrl))(__haystack, __needle, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if defined(__fast_memrchr_defined) && defined(__CRT_HAVE_memrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `needle', starting at `haystack + n_bytes'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrchrb,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrchr,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchr))(__haystack, __needle, __n_bytes); })
/* Descendingly search for `needle', starting at `haystack + n_bytes'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memrchrb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrchr,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchr))(__haystack, __needle, __n_bytes); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `needle', starting at `haystack + n_bytes'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrchrb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrchr,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchr))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memrchr_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `needle', starting at `haystack + n_bytes'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrb)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchr))(__haystack, __needle, __n_bytes); }
/* Descendingly search for `needle', starting at `haystack + n_bytes'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchr))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `needle', starting at `haystack + n_bytes'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchr))(__haystack, __needle, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `needle', starting at `haystack + n_bytes'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrchrb,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrchr,(__haystack,__needle,__n_bytes))
/* Descendingly search for `needle', starting at `haystack + n_bytes'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memrchrb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrchr,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `needle', starting at `haystack + n_bytes'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrchrb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrchr,(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `needle', starting at `haystack + n_bytes'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrb)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))(__haystack, __needle, __n_bytes); }
/* Descendingly search for `needle', starting at `haystack + n_bytes'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `needle', starting at `haystack + n_bytes'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))(__haystack, __needle, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if defined(__fast_memrchrw_defined) && defined(__CRT_HAVE_memrchrw)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memrchrw,(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memrchrw,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrw))(__haystack, __needle, __n_words); })
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ const *,__NOTHROW_NCX,memrchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memrchrw,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrw))(__haystack, __needle, __n_words); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memrchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrw))(__haystack, __needle, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memrchrw_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrw)(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrw))(__haystack, __needle, __n_words); }
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrw))(__haystack, __needle, __n_words); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrw))(__haystack, __needle, __n_words); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memrchrw)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memrchrw,(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memrchrw,(__haystack,__needle,__n_words))
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ const *,__NOTHROW_NCX,memrchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memrchrw,(__haystack,__needle,__n_words))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memrchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),(__haystack,__needle,__n_words))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memrchrw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrw)(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrw))(__haystack, __needle, __n_words); }
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrw))(__haystack, __needle, __n_words); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrchrw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrw))(__haystack, __needle, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if defined(__fast_memrchrl_defined) && defined(__CRT_HAVE_memrchrl)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memrchrl,(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memrchrl,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrl))(__haystack, __needle, __n_dwords); })
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ const *,__NOTHROW_NCX,memrchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memrchrl,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrl))(__haystack, __needle, __n_dwords); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memrchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrl))(__haystack, __needle, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memrchrl_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrl)(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrl))(__haystack, __needle, __n_dwords); }
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrl))(__haystack, __needle, __n_dwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrl))(__haystack, __needle, __n_dwords); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memrchrl)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memrchrl,(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memrchrl,(__haystack,__needle,__n_dwords))
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ const *,__NOTHROW_NCX,memrchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memrchrl,(__haystack,__needle,__n_dwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memrchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),(__haystack,__needle,__n_dwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memrchrl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrl)(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrl))(__haystack, __needle, __n_dwords); }
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrl))(__haystack, __needle, __n_dwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrchrl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrl))(__haystack, __needle, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_rawmemchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemchrb,(void *__restrict __haystack, int __needle),rawmemchr,(__haystack,__needle))
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT8_TYPE__ const *,__NOTHROW_NCX,rawmemchrb,(void const *__restrict __haystack, int __needle),rawmemchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemchrb,(void const *__restrict __haystack, int __needle),rawmemchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE___rawmemchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemchrb,(void *__restrict __haystack, int __needle),__rawmemchr,(__haystack,__needle))
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT8_TYPE__ const *,__NOTHROW_NCX,rawmemchrb,(void const *__restrict __haystack, int __needle),__rawmemchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemchrb,(void const *__restrict __haystack, int __needle),__rawmemchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/rawmemchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrb)(void *__restrict __haystack, int __needle) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchr))(__haystack, __needle); }
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemchrb)(void const *__restrict __haystack, int __needle) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrb)(void const *__restrict __haystack, int __needle) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchr))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_rawmemchrw
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemchrw,(void *__restrict __haystack, __UINT16_TYPE__ __needle),rawmemchrw,(__haystack,__needle))
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ const *,__NOTHROW_NCX,rawmemchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle),rawmemchrw,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemchrw */
#include <libc/local/string/rawmemchrw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrw)(void *__restrict __haystack, __UINT16_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrw))(__haystack, __needle); }
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrw))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemchrw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrw))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemchrw */
#ifdef __CRT_HAVE_rawmemchrl
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemchrl,(void *__restrict __haystack, __UINT32_TYPE__ __needle),rawmemchrl,(__haystack,__needle))
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ const *,__NOTHROW_NCX,rawmemchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle),rawmemchrl,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemchrl */
#include <libc/local/string/rawmemchrl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrl)(void *__restrict __haystack, __UINT32_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrl))(__haystack, __needle); }
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrl))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemchrl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrl))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemchrl */
#ifdef __CRT_HAVE_rawmemrchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrb' without a search limit, starting at `haystack - 1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemrchrb,(void *__restrict __haystack, int __needle),rawmemrchr,(__haystack,__needle))
/* Same as `memrchrb' without a search limit, starting at `haystack - 1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,rawmemrchrb,(void const *__restrict __haystack, int __needle),rawmemrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrb' without a search limit, starting at `haystack - 1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemrchrb,(void const *__restrict __haystack, int __needle),rawmemrchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrchr */
#include <libc/local/string/rawmemrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrb' without a search limit, starting at `haystack - 1' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrb)(void *__restrict __haystack, int __needle) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchr))(__haystack, __needle); }
/* Same as `memrchrb' without a search limit, starting at `haystack - 1' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrchrb)(void const *__restrict __haystack, int __needle) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrb' without a search limit, starting at `haystack - 1' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrb)(void const *__restrict __haystack, int __needle) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchr))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrchr */
#ifdef __CRT_HAVE_rawmemrchrw
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)haystack - 2' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemrchrw,(void *__restrict __haystack, __UINT16_TYPE__ __needle),rawmemrchrw,(__haystack,__needle))
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)haystack - 2' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,rawmemrchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle),rawmemrchrw,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)haystack - 2' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemrchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrchrw */
#include <libc/local/string/rawmemrchrw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)haystack - 2' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrw)(void *__restrict __haystack, __UINT16_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrw))(__haystack, __needle); }
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)haystack - 2' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrw))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)haystack - 2' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrchrw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrw))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrchrw */
#ifdef __CRT_HAVE_rawmemrchrl
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)haystack - 4' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemrchrl,(void *__restrict __haystack, __UINT32_TYPE__ __needle),rawmemrchrl,(__haystack,__needle))
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)haystack - 4' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,rawmemrchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle),rawmemrchrl,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)haystack - 4' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemrchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrchrl */
#include <libc/local/string/rawmemrchrl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)haystack - 4' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrl)(void *__restrict __haystack, __UINT32_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrl))(__haystack, __needle); }
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)haystack - 4' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrl))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)haystack - 4' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrchrl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrl))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrchrl */
#if defined(__fast_memend_defined) && defined(__CRT_HAVE_memend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrb', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memendb,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memend,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __byte, __n_bytes); })
/* Same as `memchrb', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memendb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memend,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __byte, __n_bytes); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrb', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memendb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memend,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __byte, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memend_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrb', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendb)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __byte, __n_bytes); }
/* Same as `memchrb', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __byte, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrb', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __byte, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrb', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memendb,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memend,(__haystack,__needle,__n_bytes))
/* Same as `memchrb', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memendb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memend,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrb', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memendb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memend,(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrb', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendb)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))(__haystack, __needle, __n_bytes); }
/* Same as `memchrb', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrb', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))(__haystack, __needle, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if defined(__fast_memendw_defined) && defined(__CRT_HAVE_memendw)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memendw,(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_bytes),memendw,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendw))(__haystack, __needle, __n_bytes); })
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ const *,__NOTHROW_NCX,memendw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_bytes),memendw,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendw))(__haystack, __needle, __n_bytes); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
__CEIDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memendw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendw))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memendw_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendw)(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendw))(__haystack, __needle, __n_bytes); }
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendw))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendw))(__haystack, __needle, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memendw)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memendw,(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_bytes),memendw,(__haystack,__needle,__n_bytes))
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ const *,__NOTHROW_NCX,memendw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_bytes),memendw,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memendw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memendw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendw)(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendw))(__haystack, __needle, __n_bytes); }
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendw))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memendw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendw))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if defined(__fast_memendl_defined) && defined(__CRT_HAVE_memendl)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memendl,(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memendl,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendl))(__haystack, __needle, __n_dwords); })
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ const *,__NOTHROW_NCX,memendl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memendl,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendl))(__haystack, __needle, __n_dwords); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
__CEIDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memendl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendl))(__haystack, __needle, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memendl_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendl)(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendl))(__haystack, __needle, __n_dwords); }
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendl))(__haystack, __needle, __n_dwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendl))(__haystack, __needle, __n_dwords); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memendl)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memendl,(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memendl,(__haystack,__needle,__n_dwords))
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ const *,__NOTHROW_NCX,memendl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memendl,(__haystack,__needle,__n_dwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memendl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),(__haystack,__needle,__n_dwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memendl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendl)(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendl))(__haystack, __needle, __n_dwords); }
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendl))(__haystack, __needle, __n_dwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memendl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendl))(__haystack, __needle, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if defined(__fast_memrend_defined) && defined(__CRT_HAVE_memrend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrb', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrendb,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrend,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __needle, __n_bytes); })
/* Same as `memrchrb', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memrendb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrend,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __needle, __n_bytes); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrb', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrendb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrend,{ return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memrend_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrb', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendb)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __needle, __n_bytes); }
/* Same as `memrchrb', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrb', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __needle, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memrend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrb', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrendb,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrend,(__haystack,__needle,__n_bytes))
/* Same as `memrchrb', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memrendb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrend,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrb', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrendb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrend,(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memrend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrb', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendb)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))(__haystack, __needle, __n_bytes); }
/* Same as `memrchrb', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrb', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))(__haystack, __needle, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if defined(__fast_memrendw_defined) && defined(__CRT_HAVE_memrendw)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memrendw,(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memrendw,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendw))(__haystack, __needle, __n_words); })
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ const *,__NOTHROW_NCX,memrendw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memrendw,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendw))(__haystack, __needle, __n_words); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
__CEIDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memrendw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendw))(__haystack, __needle, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memrendw_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendw)(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendw))(__haystack, __needle, __n_words); }
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendw))(__haystack, __needle, __n_words); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendw))(__haystack, __needle, __n_words); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memrendw)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memrendw,(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memrendw,(__haystack,__needle,__n_words))
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ const *,__NOTHROW_NCX,memrendw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memrendw,(__haystack,__needle,__n_words))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memrendw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),(__haystack,__needle,__n_words))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memrendw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendw)(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendw))(__haystack, __needle, __n_words); }
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendw))(__haystack, __needle, __n_words); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrendw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendw))(__haystack, __needle, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if defined(__fast_memrendl_defined) && defined(__CRT_HAVE_memrendl)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memrendl,(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memrendl,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendl))(__haystack, __needle, __n_dwords); })
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ const *,__NOTHROW_NCX,memrendl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memrendl,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendl))(__haystack, __needle, __n_dwords); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
__CEIDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memrendl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendl))(__haystack, __needle, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memrendl_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendl)(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendl))(__haystack, __needle, __n_dwords); }
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendl))(__haystack, __needle, __n_dwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendl))(__haystack, __needle, __n_dwords); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memrendl)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memrendl,(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memrendl,(__haystack,__needle,__n_dwords))
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ const *,__NOTHROW_NCX,memrendl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memrendl,(__haystack,__needle,__n_dwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memrendl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),(__haystack,__needle,__n_dwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memrendl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendl)(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendl))(__haystack, __needle, __n_dwords); }
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendl))(__haystack, __needle, __n_dwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrendl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendl))(__haystack, __needle, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if defined(__fast_memlen_defined) && defined(__CRT_HAVE_memlen)
/* Same as `memendb', but return the offset from `haystack', rather than the actual address.
 * Returns `haystack + N_DWORDS' if the given `needle' wasn't found */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memlenb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memlen,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memlen))(__haystack, __needle, __n_bytes); })
#elif defined(__fast_memlen_defined)
/* Same as `memendb', but return the offset from `haystack', rather than the actual address.
 * Returns `haystack + N_DWORDS' if the given `needle' wasn't found */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memlenb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memlen))(__haystack, __needle, __n_bytes); }
#elif defined(__CRT_HAVE_memlen)
/* Same as `memendb', but return the offset from `haystack', rather than the actual address.
 * Returns `haystack + N_DWORDS' if the given `needle' wasn't found */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memlenb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memlen,(__haystack,__needle,__n_bytes))
#else /* ... */
#include <libc/local/string/memlen.h>
/* Same as `memendb', but return the offset from `haystack', rather than the actual address.
 * Returns `haystack + N_DWORDS' if the given `needle' wasn't found */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memlenb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlen))(__haystack, __needle, __n_bytes); }
#endif /* !... */
#ifdef __CRT_HAVE_memlenw
/* Same as `memendw', but return the offset from `haystack', rather than the actual address.
 * Returns    `haystack + N_DWORDS * 2'    if    the    given    `needle'    wasn't    found */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,memlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),(__haystack,__needle,__n_words))
#else /* __CRT_HAVE_memlenw */
#include <libc/local/string/memlenw.h>
/* Same as `memendw', but return the offset from `haystack', rather than the actual address.
 * Returns    `haystack + N_DWORDS * 2'    if    the    given    `needle'    wasn't    found */
__NAMESPACE_LOCAL_USING_OR_IMPL(memlenw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlenw))(__haystack, __needle, __n_words); })
#endif /* !__CRT_HAVE_memlenw */
#ifdef __CRT_HAVE_memlenl
/* Same as `memendl', but return the offset from `haystack', rather than the actual address.
 * Returns    `haystack + N_DWORDS * 4'    if    the    given    `needle'    wasn't    found */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,memlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),(__haystack,__needle,__n_dwords))
#else /* __CRT_HAVE_memlenl */
#include <libc/local/string/memlenl.h>
/* Same as `memendl', but return the offset from `haystack', rather than the actual address.
 * Returns    `haystack + N_DWORDS * 4'    if    the    given    `needle'    wasn't    found */
__NAMESPACE_LOCAL_USING_OR_IMPL(memlenl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlenl))(__haystack, __needle, __n_dwords); })
#endif /* !__CRT_HAVE_memlenl */
#if defined(__fast_memrlen_defined) && defined(__CRT_HAVE_memrlen)
/* Same as `memrendb', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1' if the given `needle' wasn't found */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memrlenb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrlen,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrlen))(__haystack, __needle, __n_bytes); })
#elif defined(__fast_memrlen_defined)
/* Same as `memrendb', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1' if the given `needle' wasn't found */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrlenb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrlen))(__haystack, __needle, __n_bytes); }
#elif defined(__CRT_HAVE_memrlen)
/* Same as `memrendb', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1' if the given `needle' wasn't found */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memrlenb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrlen,(__haystack,__needle,__n_bytes))
#else /* ... */
#include <libc/local/string/memrlen.h>
/* Same as `memrendb', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1' if the given `needle' wasn't found */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrlenb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlen))(__haystack, __needle, __n_bytes); }
#endif /* !... */
#ifdef __CRT_HAVE_memrlenw
/* Same as `memrendw', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 2' if the given `needle' wasn't found */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,memrlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),(__haystack,__needle,__n_words))
#else /* __CRT_HAVE_memrlenw */
#include <libc/local/string/memrlenw.h>
/* Same as `memrendw', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 2' if the given `needle' wasn't found */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrlenw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlenw))(__haystack, __needle, __n_words); })
#endif /* !__CRT_HAVE_memrlenw */
#ifdef __CRT_HAVE_memrlenl
/* Same as `memrendl', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 4' if the given `needle' wasn't found */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,memrlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),(__haystack,__needle,__n_dwords))
#else /* __CRT_HAVE_memrlenl */
#include <libc/local/string/memrlenl.h>
/* Same as `memrendl', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 4' if the given `needle' wasn't found */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrlenl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlenl))(__haystack, __needle, __n_dwords); })
#endif /* !__CRT_HAVE_memrlenl */
#ifdef __CRT_HAVE_rawmemlen
/* Same as `rawmemchrb', but return the offset from `haystack', rather than the actual address. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,rawmemlenb,(void const *__restrict __haystack, int __needle),rawmemlen,(__haystack,__needle))
#else /* __CRT_HAVE_rawmemlen */
#include <libc/local/string/rawmemlen.h>
/* Same as `rawmemchrb', but return the offset from `haystack', rather than the actual address. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemlenb)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemlen))(__haystack, __needle); }
#endif /* !__CRT_HAVE_rawmemlen */
#ifdef __CRT_HAVE_rawmemlenw
/* Same as `rawmemchrw', but return the offset from `haystack', rather than the actual address. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,rawmemlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle),(__haystack,__needle))
#else /* __CRT_HAVE_rawmemlenw */
#include <libc/local/string/rawmemlenw.h>
/* Same as `rawmemchrw', but return the offset from `haystack', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemlenw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemlenw))(__haystack, __needle); })
#endif /* !__CRT_HAVE_rawmemlenw */
#ifdef __CRT_HAVE_rawmemlenl
/* Same as `rawmemchrl', but return the offset from `haystack', rather than the actual address. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,rawmemlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle),(__haystack,__needle))
#else /* __CRT_HAVE_rawmemlenl */
#include <libc/local/string/rawmemlenl.h>
/* Same as `rawmemchrl', but return the offset from `haystack', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemlenl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemlenl))(__haystack, __needle); })
#endif /* !__CRT_HAVE_rawmemlenl */
#ifdef __CRT_HAVE_rawmemrlen
/* Same as `rawmemrchrb', but return the offset from `haystack', rather than the actual address. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrlenb,(void const *__restrict __haystack, int __needle),rawmemrlen,(__haystack,__needle))
#else /* __CRT_HAVE_rawmemrlen */
#include <libc/local/string/rawmemrlen.h>
/* Same as `rawmemrchrb', but return the offset from `haystack', rather than the actual address. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrlenb)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrlen))(__haystack, __needle); }
#endif /* !__CRT_HAVE_rawmemrlen */
#ifdef __CRT_HAVE_rawmemrlenw
/* Same as `rawmemrchrw', but return the offset from `haystack', rather than the actual address. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle),(__haystack,__needle))
#else /* __CRT_HAVE_rawmemrlenw */
#include <libc/local/string/rawmemrlenw.h>
/* Same as `rawmemrchrw', but return the offset from `haystack', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrlenw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrlenw))(__haystack, __needle); })
#endif /* !__CRT_HAVE_rawmemrlenw */
#ifdef __CRT_HAVE_rawmemrlenl
/* Same as `rawmemrchrl', but return the offset from `haystack', rather than the actual address. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle),(__haystack,__needle))
#else /* __CRT_HAVE_rawmemrlenl */
#include <libc/local/string/rawmemrlenl.h>
/* Same as `rawmemrchrl', but return the offset from `haystack', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrlenl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrlenl))(__haystack, __needle); })
#endif /* !__CRT_HAVE_rawmemrlenl */

#ifdef __UINT64_TYPE__
#if defined(__fast_memcpyq_defined) && defined(__CRT_HAVE_memcpyq)
/* Copy memory between non-overlapping memory blocks. */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memcpyq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyq))(__dst, __src, __n_qwords); })
#elif defined(__fast_memcpyq_defined)
/* Copy memory between non-overlapping memory blocks. */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyq))(__dst, __src, __n_qwords); }
#elif defined(__CRT_HAVE_memcpyq)
/* Copy memory between non-overlapping memory blocks. */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memcpyq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),(__dst,__src,__n_qwords))
#else /* ... */
#include <libc/local/string/memcpyq.h>
/* Copy memory between non-overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpyq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyq))(__dst, __src, __n_qwords); })
#endif /* !... */
#if defined(__fast_mempcpyq_defined) && defined(__CRT_HAVE_mempcpyq)
/* Same as `memcpyq', but return `dst + n_qwords', rather than `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,mempcpyq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyq))(__dst, __src, __n_qwords); })
#elif defined(__fast_mempcpyq_defined)
/* Same as `memcpyq', but return `dst + n_qwords', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyq))(__dst, __src, __n_qwords); }
#elif defined(__CRT_HAVE_mempcpyq)
/* Same as `memcpyq', but return `dst + n_qwords', rather than `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,mempcpyq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),(__dst,__src,__n_qwords))
#else /* ... */
#include <libc/local/string/mempcpyq.h>
/* Same as `memcpyq', but return `dst + n_qwords', rather than `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempcpyq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyq))(__dst, __src, __n_qwords); })
#endif /* !... */
#if defined(__fast_memmoveq_defined) && defined(__CRT_HAVE_memmoveq)
/* Move memory between potentially overlapping memory blocks. */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memmoveq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveq))(__dst, __src, __n_qwords); })
#elif defined(__fast_memmoveq_defined)
/* Move memory between potentially overlapping memory blocks. */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveq)(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveq))(__dst, __src, __n_qwords); }
#elif defined(__CRT_HAVE_memmoveq)
/* Move memory between potentially overlapping memory blocks. */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memmoveq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),(__dst,__src,__n_qwords))
#else /* ... */
#include <libc/local/string/memmoveq.h>
/* Move memory between potentially overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmoveq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveq)(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveq))(__dst, __src, __n_qwords); })
#endif /* !... */
#if defined(__fast_mempmoveq_defined) && defined(__CRT_HAVE_mempmoveq)
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,mempmoveq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveq))(__dst, __src, __n_qwords); })
#elif defined(__fast_mempmoveq_defined)
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveq))(__dst, __src, __n_qwords); }
#elif defined(__CRT_HAVE_mempmoveq)
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,mempmoveq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),(__dst,__src,__n_qwords))
#else /* ... */
#include <libc/local/string/mempmoveq.h>
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmoveq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveq))(__dst, __src, __n_qwords); })
#endif /* !... */
#ifdef __USE_KOS
#if defined(__fast_memmoveupq_defined) && defined(__CRT_HAVE_memmoveupq)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_qwords') */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memmoveupq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupq))(__dst, __src, __n_qwords); })
#elif defined(__fast_memmoveupq_defined) && defined(__CRT_HAVE_memmoveq)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_qwords') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memmoveupq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),memmoveq,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupq))(__dst, __src, __n_qwords); })
#elif defined(__fast_memmoveupq_defined)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_qwords') */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveupq)(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupq))(__dst, __src, __n_qwords); }
#elif defined(__CRT_HAVE_memmoveupq)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_qwords') */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memmoveupq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_memmoveq)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_qwords') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memmoveupq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),memmoveq,(__dst,__src,__n_qwords))
#else /* ... */
#include <libc/local/string/memmoveupq.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_qwords') */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmoveupq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveupq)(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupq))(__dst, __src, __n_qwords); })
#endif /* !... */
#if defined(__fast_memmovedownq_defined) && defined(__CRT_HAVE_memmovedownq)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_qwords') */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memmovedownq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownq))(__dst, __src, __n_qwords); })
#elif defined(__fast_memmovedownq_defined) && defined(__CRT_HAVE_memmoveq)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_qwords') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memmovedownq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),memmoveq,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownq))(__dst, __src, __n_qwords); })
#elif defined(__fast_memmovedownq_defined)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_qwords') */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovedownq)(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownq))(__dst, __src, __n_qwords); }
#elif defined(__CRT_HAVE_memmovedownq)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_qwords') */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memmovedownq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_memmoveq)
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_qwords') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memmovedownq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),memmoveq,(__dst,__src,__n_qwords))
#else /* ... */
#include <libc/local/string/memmovedownq.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_qwords') */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmovedownq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovedownq)(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownq))(__dst, __src, __n_qwords); })
#endif /* !... */
#if defined(__fast_mempmoveupq_defined) && defined(__CRT_HAVE_mempmoveupq)
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst >= src || !n_qwords') */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,mempmoveupq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupq))(__dst, __src, __n_qwords); })
#elif defined(__fast_mempmoveupq_defined) && defined(__CRT_HAVE_mempmoveq)
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst >= src || !n_qwords') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,mempmoveupq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmoveq,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupq))(__dst, __src, __n_qwords); })
#elif defined(__fast_mempmoveupq_defined)
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst >= src || !n_qwords') */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveupq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupq))(__dst, __src, __n_qwords); }
#elif defined(__CRT_HAVE_mempmoveupq)
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst >= src || !n_qwords') */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,mempmoveupq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_mempmoveq)
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst >= src || !n_qwords') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,mempmoveupq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmoveq,(__dst,__src,__n_qwords))
#else /* ... */
#include <libc/local/string/mempmoveupq.h>
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst >= src || !n_qwords') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmoveupq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveupq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveupq))(__dst, __src, __n_qwords); })
#endif /* !... */
#if defined(__fast_mempmovedownq_defined) && defined(__CRT_HAVE_mempmovedownq)
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst <= src || !n_qwords') */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,mempmovedownq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownq))(__dst, __src, __n_qwords); })
#elif defined(__fast_mempmovedownq_defined) && defined(__CRT_HAVE_mempmoveq)
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst <= src || !n_qwords') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,mempmovedownq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmoveq,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownq))(__dst, __src, __n_qwords); })
#elif defined(__fast_mempmovedownq_defined)
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst <= src || !n_qwords') */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovedownq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownq))(__dst, __src, __n_qwords); }
#elif defined(__CRT_HAVE_mempmovedownq)
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst <= src || !n_qwords') */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,mempmovedownq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_mempmoveq)
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst <= src || !n_qwords') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,mempmovedownq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmoveq,(__dst,__src,__n_qwords))
#else /* ... */
#include <libc/local/string/mempmovedownq.h>
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst <= src || !n_qwords') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmovedownq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovedownq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedownq))(__dst, __src, __n_qwords); })
#endif /* !... */
#endif /* __USE_KOS */
#if defined(__fast_memsetq_defined) && defined(__CRT_HAVE_memsetq)
/* Fill memory with a given qword */
__CEIDECLARE(__ATTR_LEAF __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memsetq,(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetq))(__dst, __qword, __n_qwords); })
#elif defined(__fast_memsetq_defined)
/* Fill memory with a given qword */
__FORCELOCAL __ATTR_LEAF __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetq)(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetq))(__dst, __qword, __n_qwords); }
#elif defined(__CRT_HAVE_memsetq)
/* Fill memory with a given qword */
__CDECLARE(__ATTR_LEAF __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memsetq,(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),(__dst,__qword,__n_qwords))
#else /* ... */
#include <libc/local/string/memsetq.h>
/* Fill memory with a given qword */
__NAMESPACE_LOCAL_USING_OR_IMPL(memsetq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetq)(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetq))(__dst, __qword, __n_qwords); })
#endif /* !... */
#if defined(__fast_mempsetq_defined) && defined(__CRT_HAVE_mempsetq)
/* Same as `memsetq', but return `dst + n_qwords', rather than `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,mempsetq,(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetq))(__dst, __qword, __n_qwords); })
#elif defined(__fast_mempsetq_defined)
/* Same as `memsetq', but return `dst + n_qwords', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetq)(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetq))(__dst, __qword, __n_qwords); }
#elif defined(__CRT_HAVE_mempsetq)
/* Same as `memsetq', but return `dst + n_qwords', rather than `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,mempsetq,(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),(__dst,__qword,__n_qwords))
#else /* ... */
#include <libc/local/string/mempsetq.h>
/* Same as `memsetq', but return `dst + n_qwords', rather than `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempsetq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_OUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetq)(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetq))(__dst, __qword, __n_qwords); })
#endif /* !... */
#if defined(__fast_memcmpq_defined) && defined(__CRT_HAVE_memcmpq)
/* Compare memory buffers and return the difference of the first non-matching qword */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,memcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpq))(__s1, __s2, __n_dwords); })
#elif defined(__fast_memcmpq_defined)
/* Compare memory buffers and return the difference of the first non-matching qword */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL memcmpq)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpq))(__s1, __s2, __n_dwords); }
#elif defined(__CRT_HAVE_memcmpq)
/* Compare memory buffers and return the difference of the first non-matching qword */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,memcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),(__s1,__s2,__n_dwords))
#else /* ... */
#include <libc/local/string/memcmpq.h>
/* Compare memory buffers and return the difference of the first non-matching qword */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcmpq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL memcmpq)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpq))(__s1, __s2, __n_dwords); })
#endif /* !... */
#if defined(__fast_memchrq_defined) && defined(__CRT_HAVE_memchrq)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memchrq,(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memchrq,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrq))(__haystack, __needle, __n_qwords); })
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ const *,__NOTHROW_NCX,memchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memchrq,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrq))(__haystack, __needle, __n_qwords); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrq))(__haystack, __needle, __n_qwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memchrq_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrq)(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrq))(__haystack, __needle, __n_qwords); }
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrq))(__haystack, __needle, __n_qwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrq))(__haystack, __needle, __n_qwords); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memchrq)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memchrq,(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memchrq,(__haystack,__needle,__n_qwords))
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ const *,__NOTHROW_NCX,memchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memchrq,(__haystack,__needle,__n_qwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),(__haystack,__needle,__n_qwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memchrq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrq)(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrq))(__haystack, __needle, __n_qwords); }
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrq))(__haystack, __needle, __n_qwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memchrq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrq))(__haystack, __needle, __n_qwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if defined(__fast_memrchrq_defined) && defined(__CRT_HAVE_memrchrq)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memrchrq,(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memrchrq,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrq))(__haystack, __needle, __n_qwords); })
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ const *,__NOTHROW_NCX,memrchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memrchrq,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrq))(__haystack, __needle, __n_qwords); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memrchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrq))(__haystack, __needle, __n_qwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memrchrq_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrq)(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrq))(__haystack, __needle, __n_qwords); }
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrq))(__haystack, __needle, __n_qwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrq))(__haystack, __needle, __n_qwords); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memrchrq)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memrchrq,(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memrchrq,(__haystack,__needle,__n_qwords))
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ const *,__NOTHROW_NCX,memrchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memrchrq,(__haystack,__needle,__n_qwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memrchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),(__haystack,__needle,__n_qwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memrchrq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrq)(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrq))(__haystack, __needle, __n_qwords); }
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrq))(__haystack, __needle, __n_qwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrchrq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrq))(__haystack, __needle, __n_qwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_rawmemchrq
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemchrq,(void *__restrict __haystack, __UINT64_TYPE__ __needle),rawmemchrq,(__haystack,__needle))
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ const *,__NOTHROW_NCX,rawmemchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle),rawmemchrq,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemchrq */
#include <libc/local/string/rawmemchrq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrq)(void *__restrict __haystack, __UINT64_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrq))(__haystack, __needle); }
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrq))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemchrq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrq))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemchrq */
#ifdef __CRT_HAVE_rawmemrchrq
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)haystack - 8' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemrchrq,(void *__restrict __haystack, __UINT64_TYPE__ __needle),rawmemrchrq,(__haystack,__needle))
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)haystack - 8' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,rawmemrchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle),rawmemrchrq,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)haystack - 8' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemrchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrchrq */
#include <libc/local/string/rawmemrchrq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)haystack - 8' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrq)(void *__restrict __haystack, __UINT64_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrq))(__haystack, __needle); }
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)haystack - 8' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrq))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)haystack - 8' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrchrq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrq))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrchrq */
#if defined(__fast_memendq_defined) && defined(__CRT_HAVE_memendq)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memendq,(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes),memendq,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendq))(__haystack, __needle, __n_bytes); })
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ const *,__NOTHROW_NCX,memendq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes),memendq,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendq))(__haystack, __needle, __n_bytes); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
__CEIDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memendq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendq))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memendq_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendq)(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendq))(__haystack, __needle, __n_bytes); }
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendq))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendq))(__haystack, __needle, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memendq)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memendq,(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes),memendq,(__haystack,__needle,__n_bytes))
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ const *,__NOTHROW_NCX,memendq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes),memendq,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memendq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memendq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendq)(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendq))(__haystack, __needle, __n_bytes); }
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendq))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memendq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendq))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if defined(__fast_memrendq_defined) && defined(__CRT_HAVE_memrendq)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memrendq,(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memrendq,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendq))(__haystack, __needle, __n_qwords); })
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ const *,__NOTHROW_NCX,memrendq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memrendq,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendq))(__haystack, __needle, __n_qwords); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
__CEIDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memrendq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendq))(__haystack, __needle, __n_qwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memrendq_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendq)(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendq))(__haystack, __needle, __n_qwords); }
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendq))(__haystack, __needle, __n_qwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendq))(__haystack, __needle, __n_qwords); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memrendq)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memrendq,(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memrendq,(__haystack,__needle,__n_qwords))
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ const *,__NOTHROW_NCX,memrendq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memrendq,(__haystack,__needle,__n_qwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memrendq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),(__haystack,__needle,__n_qwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memrendq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendq)(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendq))(__haystack, __needle, __n_qwords); }
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendq))(__haystack, __needle, __n_qwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrendq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendq))(__haystack, __needle, __n_qwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if defined(__fast_memlenq_defined) && defined(__CRT_HAVE_memlenq)
/* Same as `memendq', but return the offset from `haystack', rather than the actual address.
 * Returns `n_qwords' if the given `needle' wasn't found */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,memlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memlenq))(__haystack, __needle, __n_qwords); })
#elif defined(__fast_memlenq_defined)
/* Same as `memendq', but return the offset from `haystack', rather than the actual address.
 * Returns `n_qwords' if the given `needle' wasn't found */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memlenq))(__haystack, __needle, __n_qwords); }
#elif defined(__CRT_HAVE_memlenq)
/* Same as `memendq', but return the offset from `haystack', rather than the actual address.
 * Returns `n_qwords' if the given `needle' wasn't found */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,memlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),(__haystack,__needle,__n_qwords))
#else /* ... */
#include <libc/local/string/memlenq.h>
/* Same as `memendq', but return the offset from `haystack', rather than the actual address.
 * Returns `n_qwords' if the given `needle' wasn't found */
__NAMESPACE_LOCAL_USING_OR_IMPL(memlenq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlenq))(__haystack, __needle, __n_qwords); })
#endif /* !... */
#if defined(__fast_memrlenq_defined) && defined(__CRT_HAVE_memrlenq)
/* Same as `memrendq', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 8' if the given `needle' wasn't found */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,memrlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrlenq))(__haystack, __needle, __n_qwords); })
#elif defined(__fast_memrlenq_defined)
/* Same as `memrendq', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 8' if the given `needle' wasn't found */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrlenq))(__haystack, __needle, __n_qwords); }
#elif defined(__CRT_HAVE_memrlenq)
/* Same as `memrendq', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 8' if the given `needle' wasn't found */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,memrlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),(__haystack,__needle,__n_qwords))
#else /* ... */
#include <libc/local/string/memrlenq.h>
/* Same as `memrendq', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 8' if the given `needle' wasn't found */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrlenq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlenq))(__haystack, __needle, __n_qwords); })
#endif /* !... */
#if defined(__fast_rawmemlenq_defined) && defined(__CRT_HAVE_rawmemlenq)
/* Same as `rawmemchrq', but return the offset from `haystack', rather than the actual address. */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,rawmemlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(rawmemlenq))(__haystack, __needle); })
#elif defined(__fast_rawmemlenq_defined)
/* Same as `rawmemchrq', but return the offset from `haystack', rather than the actual address. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(rawmemlenq))(__haystack, __needle); }
#elif defined(__CRT_HAVE_rawmemlenq)
/* Same as `rawmemchrq', but return the offset from `haystack', rather than the actual address. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,rawmemlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle),(__haystack,__needle))
#else /* ... */
#include <libc/local/string/rawmemlenq.h>
/* Same as `rawmemchrq', but return the offset from `haystack', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemlenq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemlenq))(__haystack, __needle); })
#endif /* !... */
#if defined(__fast_rawmemrlenq_defined) && defined(__CRT_HAVE_rawmemrlenq)
/* Same as `rawmemrchrq', but return the offset from `haystack', rather than the actual address. */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(rawmemrlenq))(__haystack, __needle); })
#elif defined(__fast_rawmemrlenq_defined)
/* Same as `rawmemrchrq', but return the offset from `haystack', rather than the actual address. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(rawmemrlenq))(__haystack, __needle); }
#elif defined(__CRT_HAVE_rawmemrlenq)
/* Same as `rawmemrchrq', but return the offset from `haystack', rather than the actual address. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle),(__haystack,__needle))
#else /* ... */
#include <libc/local/string/rawmemrlenq.h>
/* Same as `rawmemrchrq', but return the offset from `haystack', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrlenq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrlenq))(__haystack, __needle); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */


#ifdef __USE_STRING_XCHR
#ifdef __CRT_HAVE_memxchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memxchr,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memxchr,(__haystack,__needle,__n_bytes))
/* Same as `memchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memxchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memxchr,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchr', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memxchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxchr */
#include <libc/local/string/memxchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memxchr)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchr))(__haystack, __needle, __n_bytes); }
/* Same as `memchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memxchr)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchr))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchr', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memxchr)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchr))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxchr */
#ifdef __CRT_HAVE_memrxchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrxchr,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrxchr,(__haystack,__needle,__n_bytes))
/* Same as `memrchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memrxchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrxchr,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchr', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrxchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxchr */
#include <libc/local/string/memrxchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrxchr)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchr))(__haystack, __needle, __n_bytes); }
/* Same as `memrchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memrxchr)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchr))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchr', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrxchr)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchr))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxchr */
#ifdef __CRT_HAVE_rawmemxchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),void *,__NOTHROW_NCX,rawmemxchr,(void *__restrict __haystack, int __needle),rawmemxchr,(__haystack,__needle))
/* Same as `rawmemchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),void const *,__NOTHROW_NCX,rawmemxchr,(void const *__restrict __haystack, int __needle),rawmemxchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchr', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),void *,__NOTHROW_NCX,rawmemxchr,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemxchr */
#include <libc/local/string/rawmemxchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) void *__NOTHROW_NCX(__LIBCCALL rawmemxchr)(void *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))(__haystack, __needle); }
/* Same as `rawmemchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) void const *__NOTHROW_NCX(__LIBCCALL rawmemxchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchr', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) void *__NOTHROW_NCX(__LIBCCALL rawmemxchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemxchr */
#ifdef __CRT_HAVE_rawmemrxchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemrxchr,(void *__restrict __haystack, int __needle),rawmemrxchr,(__haystack,__needle))
/* Same as `rawmemrchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,rawmemrxchr,(void const *__restrict __haystack, int __needle),rawmemrxchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchr', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemrxchr,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrxchr */
#include <libc/local/string/rawmemrxchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemrxchr)(void *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchr))(__haystack, __needle); }
/* Same as `rawmemrchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL rawmemrxchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchr', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemrxchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrxchr */
#ifdef __CRT_HAVE_memxend
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memend', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memxend,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memxend,(__haystack,__needle,__n_bytes))
/* Same as `memend', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memxend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memxend,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memend', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memxend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxend */
#include <libc/local/string/memxend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memend', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memxend)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))(__haystack, __needle, __n_bytes); }
/* Same as `memend', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memxend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memend', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxend, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memxend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxend */
#ifdef __CRT_HAVE_memrxend
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrend', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrxend,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrxend,(__haystack,__needle,__n_bytes))
/* Same as `memrend', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memrxend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrxend,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrend', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrxend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxend */
#include <libc/local/string/memrxend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrend', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrxend)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))(__haystack, __needle, __n_bytes); }
/* Same as `memrend', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memrxend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrend', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxend, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrxend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxend */
#ifdef __CRT_HAVE_memxlen
/* Same as `memlen', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memxlen,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memxlen */
#include <libc/local/string/memxlen.h>
/* Same as `memlen', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memxlen)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxlen))(__haystack, __needle, __n_bytes); })
#endif /* !__CRT_HAVE_memxlen */
#ifdef __CRT_HAVE_memrxlen
/* Same as `memrlen', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memrxlen,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memrxlen */
#include <libc/local/string/memrxlen.h>
/* Same as `memrlen', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrxlen)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxlen))(__haystack, __needle, __n_bytes); })
#endif /* !__CRT_HAVE_memrxlen */
#ifdef __CRT_HAVE_rawmemxlen
/* Same as `rawmemlen', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,rawmemxlen,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* __CRT_HAVE_rawmemxlen */
#include <libc/local/string/rawmemxlen.h>
/* Same as `rawmemlen', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemxlen)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxlen))(__haystack, __needle); })
#endif /* !__CRT_HAVE_rawmemxlen */
#ifdef __CRT_HAVE_rawmemrxlen
/* Same as `rawmemrlen', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrxlen,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* __CRT_HAVE_rawmemrxlen */
#include <libc/local/string/rawmemrxlen.h>
/* Same as `rawmemrlen', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrxlen)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxlen))(__haystack, __needle); })
#endif /* !__CRT_HAVE_rawmemrxlen */
#ifdef __USE_STRING_BWLQ
#ifdef __CRT_HAVE_memxchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memxchrb,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memxchr,(__haystack,__needle,__n_bytes))
/* Same as `memchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memxchrb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memxchr,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memxchrb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memxchr,(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxchr */
#include <libc/local/string/memxchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrb)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchr))(__haystack, __needle, __n_bytes); }
/* Same as `memchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxchrb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchr))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchr))(__haystack, __needle, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxchr */
#ifdef __CRT_HAVE_memxchrw
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memxchrw,(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memxchrw,(__haystack,__needle,__n_words))
/* Same as `memchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ const *,__NOTHROW_NCX,memxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memxchrw,(__haystack,__needle,__n_words))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),(__haystack,__needle,__n_words))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxchrw */
#include <libc/local/string/memxchrw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrw)(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrw))(__haystack, __needle, __n_words); }
/* Same as `memchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrw))(__haystack, __needle, __n_words); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxchrw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrw))(__haystack, __needle, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxchrw */
#ifdef __CRT_HAVE_memxchrl
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memxchrl,(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memxchrl,(__haystack,__needle,__n_dwords))
/* Same as `memchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ const *,__NOTHROW_NCX,memxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memxchrl,(__haystack,__needle,__n_dwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),(__haystack,__needle,__n_dwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxchrl */
#include <libc/local/string/memxchrl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrl)(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrl))(__haystack, __needle, __n_dwords); }
/* Same as `memchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrl))(__haystack, __needle, __n_dwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxchrl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrl))(__haystack, __needle, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxchrl */
#ifdef __CRT_HAVE_memrxchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrxchrb,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrxchr,(__haystack,__needle,__n_bytes))
/* Same as `memrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memrxchrb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrxchr,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrxchrb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrxchr,(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxchr */
#include <libc/local/string/memrxchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrb)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchr))(__haystack, __needle, __n_bytes); }
/* Same as `memrchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxchrb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchr))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchr))(__haystack, __needle, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxchr */
#ifdef __CRT_HAVE_memrxchrw
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memrxchrw,(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memrxchrw,(__haystack,__needle,__n_words))
/* Same as `memrchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ const *,__NOTHROW_NCX,memrxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memrxchrw,(__haystack,__needle,__n_words))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memrxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),(__haystack,__needle,__n_words))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxchrw */
#include <libc/local/string/memrxchrw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrw)(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrw))(__haystack, __needle, __n_words); }
/* Same as `memrchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrw))(__haystack, __needle, __n_words); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxchrw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrw))(__haystack, __needle, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxchrw */
#ifdef __CRT_HAVE_memrxchrl
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memrxchrl,(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memrxchrl,(__haystack,__needle,__n_dwords))
/* Same as `memrchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ const *,__NOTHROW_NCX,memrxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memrxchrl,(__haystack,__needle,__n_dwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memrxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),(__haystack,__needle,__n_dwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxchrl */
#include <libc/local/string/memrxchrl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrl)(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrl))(__haystack, __needle, __n_dwords); }
/* Same as `memrchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrl))(__haystack, __needle, __n_dwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxchrl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrl))(__haystack, __needle, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxchrl */
#ifdef __CRT_HAVE_rawmemxchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemxchrb,(void *__restrict __haystack, int __needle),rawmemxchr,(__haystack,__needle))
/* Same as `rawmemchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT8_TYPE__ const *,__NOTHROW_NCX,rawmemxchrb,(void const *__restrict __haystack, int __needle),rawmemxchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemxchrb,(void const *__restrict __haystack, int __needle),rawmemxchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemxchr */
#include <libc/local/string/rawmemxchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrb)(void *__restrict __haystack, int __needle) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))(__haystack, __needle); }
/* Same as `rawmemchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemxchrb)(void const *__restrict __haystack, int __needle) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrb)(void const *__restrict __haystack, int __needle) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemxchr */
#ifdef __CRT_HAVE_rawmemxchrw
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemxchrw,(void *__restrict __haystack, __UINT16_TYPE__ __needle),rawmemxchrw,(__haystack,__needle))
/* Same as `rawmemchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ const *,__NOTHROW_NCX,rawmemxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle),rawmemxchrw,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchrw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemxchrw */
#include <libc/local/string/rawmemxchrw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrw)(void *__restrict __haystack, __UINT16_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrw))(__haystack, __needle); }
/* Same as `rawmemchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrw))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchrw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxchrw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrw))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemxchrw */
#ifdef __CRT_HAVE_rawmemxchrl
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemxchrl,(void *__restrict __haystack, __UINT32_TYPE__ __needle),rawmemxchrl,(__haystack,__needle))
/* Same as `rawmemchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ const *,__NOTHROW_NCX,rawmemxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle),rawmemxchrl,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchrl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemxchrl */
#include <libc/local/string/rawmemxchrl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrl)(void *__restrict __haystack, __UINT32_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrl))(__haystack, __needle); }
/* Same as `rawmemchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrl))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchrl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxchrl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrl))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemxchrl */
#ifdef __CRT_HAVE_rawmemrxchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemrxchrb,(void *__restrict __haystack, int __needle),rawmemrxchr,(__haystack,__needle))
/* Same as `rawmemrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,rawmemrxchrb,(void const *__restrict __haystack, int __needle),rawmemrxchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemrxchrb,(void const *__restrict __haystack, int __needle),rawmemrxchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrxchr */
#include <libc/local/string/rawmemrxchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrb)(void *__restrict __haystack, int __needle) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchr))(__haystack, __needle); }
/* Same as `rawmemrchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrxchrb)(void const *__restrict __haystack, int __needle) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrb)(void const *__restrict __haystack, int __needle) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchr))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrxchr */
#ifdef __CRT_HAVE_rawmemrxchrw
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemrxchrw,(void *__restrict __haystack, __UINT16_TYPE__ __needle),rawmemrxchrw,(__haystack,__needle))
/* Same as `rawmemrchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,rawmemrxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle),rawmemrxchrw,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchrw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemrxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrxchrw */
#include <libc/local/string/rawmemrxchrw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrw)(void *__restrict __haystack, __UINT16_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrw))(__haystack, __needle); }
/* Same as `rawmemrchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrw))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchrw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxchrw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrw))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrxchrw */
#ifdef __CRT_HAVE_rawmemrxchrl
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemrxchrl,(void *__restrict __haystack, __UINT32_TYPE__ __needle),rawmemrxchrl,(__haystack,__needle))
/* Same as `rawmemrchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,rawmemrxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle),rawmemrxchrl,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchrl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemrxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrxchrl */
#include <libc/local/string/rawmemrxchrl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrl)(void *__restrict __haystack, __UINT32_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrl))(__haystack, __needle); }
/* Same as `rawmemrchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrl))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchrl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxchrl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrl))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrxchrl */
#ifdef __CRT_HAVE_memxend
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memxendb,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memxend,(__haystack,__needle,__n_bytes))
/* Same as `memendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memxendb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memxend,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memxendb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memxend,(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxend */
#include <libc/local/string/memxend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memendb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendb)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))(__haystack, __needle, __n_bytes); }
/* Same as `memendb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxendb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memendb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))(__haystack, __needle, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxend */
#ifdef __CRT_HAVE_memxendw
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memendw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memxendw,(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memxendw,(__haystack,__needle,__n_words))
/* Same as `memendw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ const *,__NOTHROW_NCX,memxendw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memxendw,(__haystack,__needle,__n_words))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memendw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memxendw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),(__haystack,__needle,__n_words))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxendw */
#include <libc/local/string/memxendw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memendw', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendw)(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendw))(__haystack, __needle, __n_words); }
/* Same as `memendw', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxendw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendw))(__haystack, __needle, __n_words); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memendw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxendw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendw))(__haystack, __needle, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxendw */
#ifdef __CRT_HAVE_memxendl
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memendl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memxendl,(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memxendl,(__haystack,__needle,__n_dwords))
/* Same as `memendl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ const *,__NOTHROW_NCX,memxendl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memxendl,(__haystack,__needle,__n_dwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memendl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memxendl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),(__haystack,__needle,__n_dwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxendl */
#include <libc/local/string/memxendl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memendl', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendl)(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendl))(__haystack, __needle, __n_dwords); }
/* Same as `memendl', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxendl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendl))(__haystack, __needle, __n_dwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memendl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxendl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendl))(__haystack, __needle, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxendl */
#ifdef __CRT_HAVE_memrxend
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrxendb,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrxend,(__haystack,__needle,__n_bytes))
/* Same as `memrendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memrxendb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrxend,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrxendb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrxend,(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxend */
#include <libc/local/string/memrxend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrendb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendb)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))(__haystack, __needle, __n_bytes); }
/* Same as `memrendb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxendb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrendb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))(__haystack, __needle, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxend */
#ifdef __CRT_HAVE_memrxendw
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrendw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memrxendw,(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memrxendw,(__haystack,__needle,__n_words))
/* Same as `memrendw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ const *,__NOTHROW_NCX,memrxendw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memrxendw,(__haystack,__needle,__n_words))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrendw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memrxendw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),(__haystack,__needle,__n_words))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxendw */
#include <libc/local/string/memrxendw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrendw', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendw)(void *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendw))(__haystack, __needle, __n_words); }
/* Same as `memrendw', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxendw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendw))(__haystack, __needle, __n_words); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrendw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxendw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendw))(__haystack, __needle, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxendw */
#ifdef __CRT_HAVE_memrxendl
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrendl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memrxendl,(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memrxendl,(__haystack,__needle,__n_dwords))
/* Same as `memrendl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ const *,__NOTHROW_NCX,memrxendl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memrxendl,(__haystack,__needle,__n_dwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrendl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memrxendl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),(__haystack,__needle,__n_dwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxendl */
#include <libc/local/string/memrxendl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrendl', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendl)(void *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendl))(__haystack, __needle, __n_dwords); }
/* Same as `memrendl', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxendl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendl))(__haystack, __needle, __n_dwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrendl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxendl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendl))(__haystack, __needle, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxendl */
#ifdef __CRT_HAVE_memxlen
/* Same as `memlenb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memxlenb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memxlen,(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memxlen */
#include <libc/local/string/memxlen.h>
/* Same as `memlenb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memxlenb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxlen))(__haystack, __needle, __n_bytes); }
#endif /* !__CRT_HAVE_memxlen */
#ifdef __CRT_HAVE_memxlenw
/* Same as `memlenw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,memxlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),(__haystack,__needle,__n_words))
#else /* __CRT_HAVE_memxlenw */
#include <libc/local/string/memxlenw.h>
/* Same as `memlenw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxlenw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memxlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxlenw))(__haystack, __needle, __n_words); })
#endif /* !__CRT_HAVE_memxlenw */
#ifdef __CRT_HAVE_memxlenl
/* Same as `memlenl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,memxlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),(__haystack,__needle,__n_dwords))
#else /* __CRT_HAVE_memxlenl */
#include <libc/local/string/memxlenl.h>
/* Same as `memlenl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxlenl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memxlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxlenl))(__haystack, __needle, __n_dwords); })
#endif /* !__CRT_HAVE_memxlenl */
#ifdef __CRT_HAVE_memrxlen
/* Same as `memrlenb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memrxlenb,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrxlen,(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memrxlen */
#include <libc/local/string/memrxlen.h>
/* Same as `memrlenb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrxlenb)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxlen))(__haystack, __needle, __n_bytes); }
#endif /* !__CRT_HAVE_memrxlen */
#ifdef __CRT_HAVE_memrxlenw
/* Same as `memrlenw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,memrxlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),(__haystack,__needle,__n_words))
#else /* __CRT_HAVE_memrxlenw */
#include <libc/local/string/memrxlenw.h>
/* Same as `memrlenw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxlenw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrxlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxlenw))(__haystack, __needle, __n_words); })
#endif /* !__CRT_HAVE_memrxlenw */
#ifdef __CRT_HAVE_memrxlenl
/* Same as `memrlenl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,memrxlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),(__haystack,__needle,__n_dwords))
#else /* __CRT_HAVE_memrxlenl */
#include <libc/local/string/memrxlenl.h>
/* Same as `memrlenl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxlenl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrxlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxlenl))(__haystack, __needle, __n_dwords); })
#endif /* !__CRT_HAVE_memrxlenl */
#ifdef __CRT_HAVE_rawmemxlen
/* Same as `rawmemlenb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,rawmemxlenb,(void const *__restrict __haystack, int __needle),rawmemxlen,(__haystack,__needle))
#else /* __CRT_HAVE_rawmemxlen */
#include <libc/local/string/rawmemxlen.h>
/* Same as `rawmemlenb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemxlenb)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxlen))(__haystack, __needle); }
#endif /* !__CRT_HAVE_rawmemxlen */
#ifdef __CRT_HAVE_rawmemxlenw
/* Same as `rawmemlenw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,rawmemxlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle),(__haystack,__needle))
#else /* __CRT_HAVE_rawmemxlenw */
#include <libc/local/string/rawmemxlenw.h>
/* Same as `rawmemlenw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxlenw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemxlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxlenw))(__haystack, __needle); })
#endif /* !__CRT_HAVE_rawmemxlenw */
#ifdef __CRT_HAVE_rawmemxlenl
/* Same as `rawmemlenl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,rawmemxlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle),(__haystack,__needle))
#else /* __CRT_HAVE_rawmemxlenl */
#include <libc/local/string/rawmemxlenl.h>
/* Same as `rawmemlenl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxlenl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemxlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxlenl))(__haystack, __needle); })
#endif /* !__CRT_HAVE_rawmemxlenl */
#ifdef __CRT_HAVE_rawmemrxlen
/* Same as `rawmemrlenb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrxlenb,(void const *__restrict __haystack, int __needle),rawmemrxlen,(__haystack,__needle))
#else /* __CRT_HAVE_rawmemrxlen */
#include <libc/local/string/rawmemrxlen.h>
/* Same as `rawmemrlenb', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrxlenb)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxlen))(__haystack, __needle); }
#endif /* !__CRT_HAVE_rawmemrxlen */
#ifdef __CRT_HAVE_rawmemrxlenw
/* Same as `rawmemrlenw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrxlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle),(__haystack,__needle))
#else /* __CRT_HAVE_rawmemrxlenw */
#include <libc/local/string/rawmemrxlenw.h>
/* Same as `rawmemrlenw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxlenw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrxlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxlenw))(__haystack, __needle); })
#endif /* !__CRT_HAVE_rawmemrxlenw */
#ifdef __CRT_HAVE_rawmemrxlenl
/* Same as `rawmemrlenl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrxlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle),(__haystack,__needle))
#else /* __CRT_HAVE_rawmemrxlenl */
#include <libc/local/string/rawmemrxlenl.h>
/* Same as `rawmemrlenl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxlenl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrxlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxlenl))(__haystack, __needle); })
#endif /* !__CRT_HAVE_rawmemrxlenl */
#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE_memxchrq
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memxchrq,(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memxchrq,(__haystack,__needle,__n_qwords))
/* Same as `memchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ const *,__NOTHROW_NCX,memxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memxchrq,(__haystack,__needle,__n_qwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),(__haystack,__needle,__n_qwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxchrq */
#include <libc/local/string/memxchrq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrq)(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrq))(__haystack, __needle, __n_qwords); }
/* Same as `memchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrq))(__haystack, __needle, __n_qwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxchrq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrq))(__haystack, __needle, __n_qwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxchrq */
#ifdef __CRT_HAVE_memrxchrq
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memrxchrq,(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memrxchrq,(__haystack,__needle,__n_qwords))
/* Same as `memrchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ const *,__NOTHROW_NCX,memrxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memrxchrq,(__haystack,__needle,__n_qwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memrxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),(__haystack,__needle,__n_qwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxchrq */
#include <libc/local/string/memrxchrq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrq)(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrq))(__haystack, __needle, __n_qwords); }
/* Same as `memrchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrq))(__haystack, __needle, __n_qwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxchrq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrq))(__haystack, __needle, __n_qwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxchrq */
#ifdef __CRT_HAVE_rawmemxchrq
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemxchrq,(void *__restrict __haystack, __UINT64_TYPE__ __needle),rawmemxchrq,(__haystack,__needle))
/* Same as `rawmemchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ const *,__NOTHROW_NCX,rawmemxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle),rawmemxchrq,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchrq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemxchrq */
#include <libc/local/string/rawmemxchrq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrq)(void *__restrict __haystack, __UINT64_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrq))(__haystack, __needle); }
/* Same as `rawmemchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrq))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchrq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxchrq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrq))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemxchrq */
#ifdef __CRT_HAVE_rawmemrxchrq
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemrxchrq,(void *__restrict __haystack, __UINT64_TYPE__ __needle),rawmemrxchrq,(__haystack,__needle))
/* Same as `rawmemrchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,rawmemrxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle),rawmemrxchrq,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchrq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemrxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrxchrq */
#include <libc/local/string/rawmemrxchrq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrq)(void *__restrict __haystack, __UINT64_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrq))(__haystack, __needle); }
/* Same as `rawmemrchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrq))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchrq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxchrq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrq))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrxchrq */
#ifdef __CRT_HAVE_memxendq
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memendq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memxendq,(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes),memxendq,(__haystack,__needle,__n_bytes))
/* Same as `memendq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ const *,__NOTHROW_NCX,memxendq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes),memxendq,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memendq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memxendq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxendq */
#include <libc/local/string/memxendq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memendq', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendq)(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendq))(__haystack, __needle, __n_bytes); }
/* Same as `memendq', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxendq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendq))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memendq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxendq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendq))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxendq */
#ifdef __CRT_HAVE_memrxendq
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrendq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memrxendq,(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memrxendq,(__haystack,__needle,__n_qwords))
/* Same as `memrendq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ const *,__NOTHROW_NCX,memrxendq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memrxendq,(__haystack,__needle,__n_qwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrendq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memrxendq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),(__haystack,__needle,__n_qwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxendq */
#include <libc/local/string/memrxendq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrendq', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendq)(void *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendq))(__haystack, __needle, __n_qwords); }
/* Same as `memrendq', but search for non-matching locations. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxendq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendq))(__haystack, __needle, __n_qwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrendq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxendq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendq))(__haystack, __needle, __n_qwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxendq */
#ifdef __CRT_HAVE_memxlenq
/* Same as `memlenq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,memxlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),(__haystack,__needle,__n_qwords))
#else /* __CRT_HAVE_memxlenq */
#include <libc/local/string/memxlenq.h>
/* Same as `memlenq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxlenq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memxlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxlenq))(__haystack, __needle, __n_qwords); })
#endif /* !__CRT_HAVE_memxlenq */
#ifdef __CRT_HAVE_memrxlenq
/* Same as `memrlenq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,memrxlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),(__haystack,__needle,__n_qwords))
#else /* __CRT_HAVE_memrxlenq */
#include <libc/local/string/memrxlenq.h>
/* Same as `memrlenq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxlenq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrxlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxlenq))(__haystack, __needle, __n_qwords); })
#endif /* !__CRT_HAVE_memrxlenq */
#ifdef __CRT_HAVE_rawmemxlenq
/* Same as `rawmemlenq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,rawmemxlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle),(__haystack,__needle))
#else /* __CRT_HAVE_rawmemxlenq */
#include <libc/local/string/rawmemxlenq.h>
/* Same as `rawmemlenq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxlenq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemxlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxlenq))(__haystack, __needle); })
#endif /* !__CRT_HAVE_rawmemxlenq */
#ifdef __CRT_HAVE_rawmemrxlenq
/* Same as `rawmemrlenq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrxlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle),(__haystack,__needle))
#else /* __CRT_HAVE_rawmemrxlenq */
#include <libc/local/string/rawmemrxlenq.h>
/* Same as `rawmemrlenq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxlenq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrxlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxlenq))(__haystack, __needle); })
#endif /* !__CRT_HAVE_rawmemrxlenq */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */
#endif /* __USE_STRING_XCHR */





#ifdef __USE_KOS
#if defined(__fast_memmoveup_defined) && defined(__CRT_HAVE_memmoveup)
/* >> memmoveup(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst >= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveup))(__dst, __src, __n_bytes); })
#elif defined(__fast_memmoveup_defined) && defined(__CRT_HAVE_memmove)
/* >> memmoveup(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst >= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveup))(__dst, __src, __n_bytes); })
#elif defined(__fast_memmoveup_defined)
/* >> memmoveup(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst >= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmoveup)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveup))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_memmoveup)
/* >> memmoveup(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst >= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE_memmove)
/* >> memmoveup(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst >= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/memmoveup.h>
/* >> memmoveup(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst >= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmoveup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmoveup)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveup))(__dst, __src, __n_bytes); })
#endif /* !... */
#if defined(__fast_memmovedown_defined) && defined(__CRT_HAVE_memmovedown)
/* >> memmovedown(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst <= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedown))(__dst, __src, __n_bytes); })
#elif defined(__fast_memmovedown_defined) && defined(__CRT_HAVE_memmove)
/* >> memmovedown(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst <= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedown))(__dst, __src, __n_bytes); })
#elif defined(__fast_memmovedown_defined)
/* >> memmovedown(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst <= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmovedown)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedown))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_memmovedown)
/* >> memmovedown(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst <= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE_memmove)
/* >> memmovedown(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst <= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/memmovedown.h>
/* >> memmovedown(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst <= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmovedown, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmovedown)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedown))(__dst, __src, __n_bytes); })
#endif /* !... */
#if defined(__fast_memcmpc_defined) && defined(__CRT_HAVE_memcmpc)
/* >> memcmpc(3)
 * Compare up to `elem_count' `elem_size'-bytes-large unsigned integers
 * from  the 2 given  buffers. If all are  identical, return `0'. Else:
 *  - return `< 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] < (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]'
 *  - return `> 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] > (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]' */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,memcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpc))(__s1, __s2, __elem_count, __elem_size); })
#elif defined(__fast_memcmpc_defined)
/* >> memcmpc(3)
 * Compare up to `elem_count' `elem_size'-bytes-large unsigned integers
 * from  the 2 given  buffers. If all are  identical, return `0'. Else:
 *  - return `< 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] < (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]'
 *  - return `> 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] > (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL memcmpc)(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpc))(__s1, __s2, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_memcmpc)
/* >> memcmpc(3)
 * Compare up to `elem_count' `elem_size'-bytes-large unsigned integers
 * from  the 2 given  buffers. If all are  identical, return `0'. Else:
 *  - return `< 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] < (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]'
 *  - return `> 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] > (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,memcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__s1,__s2,__elem_count,__elem_size))
#else /* ... */
#include <libc/local/string/memcmpc.h>
/* >> memcmpc(3)
 * Compare up to `elem_count' `elem_size'-bytes-large unsigned integers
 * from  the 2 given  buffers. If all are  identical, return `0'. Else:
 *  - return `< 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] < (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]'
 *  - return `> 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] > (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcmpc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL memcmpc)(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpc))(__s1, __s2, __elem_count, __elem_size); })
#endif /* !... */
#if defined(__fast_memcpyc_defined) && defined(__CRT_HAVE_memcpyc)
/* >> memcpyc(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyc))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__fast_memcpyc_defined)
/* >> memcpyc(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL memcpyc)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyc))(__dst, __src, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_memcpyc)
/* >> memcpyc(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__src,__elem_count,__elem_size))
#else /* ... */
#include <libc/local/string/memcpyc.h>
/* >> memcpyc(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpyc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL memcpyc)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyc))(__dst, __src, __elem_count, __elem_size); })
#endif /* !... */
#if defined(__fast_mempcpyc_defined) && defined(__CRT_HAVE_mempcpyc)
/* >> mempcpyc(3)
 * Same as `memcpyc', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,mempcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyc))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__fast_mempcpyc_defined)
/* >> mempcpyc(3)
 * Same as `memcpyc', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL mempcpyc)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyc))(__dst, __src, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_mempcpyc)
/* >> mempcpyc(3)
 * Same as `memcpyc', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,mempcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__src,__elem_count,__elem_size))
#else /* ... */
#include <libc/local/string/mempcpyc.h>
/* >> mempcpyc(3)
 * Same as `memcpyc', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempcpyc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL mempcpyc)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyc))(__dst, __src, __elem_count, __elem_size); })
#endif /* !... */
#if defined(__fast_memmovec_defined) && defined(__CRT_HAVE_memmovec)
/* >> memmovec(3)
 * Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,memmovec,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovec))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__fast_memmovec_defined)
/* >> memmovec(3)
 * Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL memmovec)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovec))(__dst, __src, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_memmovec)
/* >> memmovec(3)
 * Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,memmovec,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__src,__elem_count,__elem_size))
#else /* ... */
#include <libc/local/string/memmovec.h>
/* >> memmovec(3)
 * Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmovec, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL memmovec)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovec))(__dst, __src, __elem_count, __elem_size); })
#endif /* !... */
#if defined(__fast_mempmovec_defined) && defined(__CRT_HAVE_mempmovec)
/* >> mempmovec(3)
 * Same as `memmovec', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,mempmovec,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovec))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__fast_mempmovec_defined)
/* >> mempmovec(3)
 * Same as `memmovec', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL mempmovec)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovec))(__dst, __src, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_mempmovec)
/* >> mempmovec(3)
 * Same as `memmovec', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,mempmovec,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__src,__elem_count,__elem_size))
#else /* ... */
#include <libc/local/string/mempmovec.h>
/* >> mempmovec(3)
 * Same as `memmovec', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmovec, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL mempmovec)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovec))(__dst, __src, __elem_count, __elem_size); })
#endif /* !... */
#if defined(__fast_memmoveupc_defined) && defined(__CRT_HAVE_memmoveupc)
/* >> memmoveupc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,memmoveupc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupc))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__fast_memmoveupc_defined)
/* >> memmoveupc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL memmoveupc)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupc))(__dst, __src, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_memmoveupc)
/* >> memmoveupc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,memmoveupc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__src,__elem_count,__elem_size))
#else /* ... */
#include <libc/local/string/memmoveupc.h>
/* >> memmoveupc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmoveupc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL memmoveupc)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupc))(__dst, __src, __elem_count, __elem_size); })
#endif /* !... */
#if defined(__fast_mempmoveupc_defined) && defined(__CRT_HAVE_mempmoveupc)
/* >> mempmoveupc(3)
 * Same   as   `memmoveupc',  but   return  `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE') */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,mempmoveupc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupc))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__fast_mempmoveupc_defined)
/* >> mempmoveupc(3)
 * Same   as   `memmoveupc',  but   return  `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE') */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL mempmoveupc)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupc))(__dst, __src, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_mempmoveupc)
/* >> mempmoveupc(3)
 * Same   as   `memmoveupc',  but   return  `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE') */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,mempmoveupc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__src,__elem_count,__elem_size))
#else /* ... */
#include <libc/local/string/mempmoveupc.h>
/* >> mempmoveupc(3)
 * Same   as   `memmoveupc',  but   return  `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmoveupc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL mempmoveupc)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveupc))(__dst, __src, __elem_count, __elem_size); })
#endif /* !... */
#if defined(__fast_memmovedownc_defined) && defined(__CRT_HAVE_memmovedownc)
/* >> memmovedownc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,memmovedownc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownc))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__fast_memmovedownc_defined)
/* >> memmovedownc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL memmovedownc)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownc))(__dst, __src, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_memmovedownc)
/* >> memmovedownc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,memmovedownc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__src,__elem_count,__elem_size))
#else /* ... */
#include <libc/local/string/memmovedownc.h>
/* >> memmovedownc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmovedownc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL memmovedownc)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownc))(__dst, __src, __elem_count, __elem_size); })
#endif /* !... */
#if defined(__fast_mempmovedownc_defined) && defined(__CRT_HAVE_mempmovedownc)
/* >> mempmovedownc(3)
 * Same  as  `memmovedownc',  but  return   `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE') */
__CEIDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,mempmovedownc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownc))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__fast_mempmovedownc_defined)
/* >> mempmovedownc(3)
 * Same  as  `memmovedownc',  but  return   `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE') */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL mempmovedownc)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownc))(__dst, __src, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_mempmovedownc)
/* >> mempmovedownc(3)
 * Same  as  `memmovedownc',  but  return   `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE') */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,mempmovedownc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__src,__elem_count,__elem_size))
#else /* ... */
#include <libc/local/string/mempmovedownc.h>
/* >> mempmovedownc(3)
 * Same  as  `memmovedownc',  but  return   `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmovedownc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL mempmovedownc)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedownc))(__dst, __src, __elem_count, __elem_size); })
#endif /* !... */
#ifdef __CRT_HAVE_strend
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strend(3)
 * Same as `str + strlen(str)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strend,(char *__restrict __str),strend,(__str))
/* >> strend(3)
 * Same as `str + strlen(str)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,strend,(char const *__restrict __str),strend,(__str))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strend(3)
 * Same as `str + strlen(str)' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strend,(char const *__restrict __str),(__str))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strend */
#include <libc/local/string/strend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strend(3)
 * Same as `str + strlen(str)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL strend)(char *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strend))(__str); }
/* >> strend(3)
 * Same as `str + strlen(str)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char const *__NOTHROW_NCX(__LIBCCALL strend)(char const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strend))(__str); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strend(3)
 * Same as `str + strlen(str)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strend, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL strend)(char const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strend))(__str); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strend */
#ifdef __CRT_HAVE_strnend
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strnend(3)
 * Same as `str + strnlen(str, max_chars)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnend,(char *__restrict __str, __SIZE_TYPE__ __maxlen),strnend,(__str,__maxlen))
/* >> strnend(3)
 * Same as `str + strnlen(str, max_chars)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strnend,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),strnend,(__str,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strnend(3)
 * Same as `str + strnlen(str, max_chars)' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnend,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strnend */
#include <libc/local/string/strnend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strnend(3)
 * Same as `str + strnlen(str, max_chars)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnend)(char *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnend))(__str, __maxlen); }
/* >> strnend(3)
 * Same as `str + strnlen(str, max_chars)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strnend)(char const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnend))(__str, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strnend(3)
 * Same as `str + strnlen(str, max_chars)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnend, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnend)(char const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnend))(__str, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strnend */
#ifdef __CRT_HAVE_strnchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strnchr(3)
 * Same as `strchr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnchr,(char *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),strnchr,(__haystack,__needle,__maxlen))
/* >> strnchr(3)
 * Same as `strchr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strnchr,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),strnchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strnchr(3)
 * Same as `strchr', but don't exceed `max_chars' characters. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnchr,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strnchr */
#include <libc/local/string/strnchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strnchr(3)
 * Same as `strchr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnchr)(char *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnchr))(__haystack, __needle, __maxlen); }
/* >> strnchr(3)
 * Same as `strchr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strnchr)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strnchr(3)
 * Same as `strchr', but don't exceed `max_chars' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnchr)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnchr))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strnchr */
#ifdef __CRT_HAVE_strnrchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strnrchr(3)
 * Same as `strrchr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnrchr,(char *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),strnrchr,(__haystack,__needle,__maxlen))
/* >> strnrchr(3)
 * Same as `strrchr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strnrchr,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),strnrchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strnrchr(3)
 * Same as `strrchr', but don't exceed `max_chars' characters. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnrchr,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strnrchr */
#include <libc/local/string/strnrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strnrchr(3)
 * Same as `strrchr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnrchr)(char *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchr))(__haystack, __needle, __maxlen); }
/* >> strnrchr(3)
 * Same as `strrchr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strnrchr)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strnrchr(3)
 * Same as `strrchr', but don't exceed `max_chars' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnrchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnrchr)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchr))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strnrchr */
#ifdef __CRT_HAVE_strrchrnul
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrchrnul(3)
 * Same as `strrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strrchrnul,(char *__restrict __haystack, int __needle),strrchrnul,(__haystack,__needle))
/* >> strrchrnul(3)
 * Same as `strrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,strrchrnul,(char const *__restrict __haystack, int __needle),strrchrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrchrnul(3)
 * Same as `strrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strrchrnul,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strrchrnul */
#include <libc/local/string/strrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrchrnul(3)
 * Same as `strrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL strrchrnul)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchrnul))(__haystack, __needle); }
/* >> strrchrnul(3)
 * Same as `strrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char const *__NOTHROW_NCX(__LIBCCALL strrchrnul)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrchrnul(3)
 * Same as `strrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strrchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL strrchrnul)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchrnul))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strrchrnul */
#ifdef __CRT_HAVE_strnchrnul
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strnchrnul(3)
 * Same as `strnchr', but return `strnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnchrnul,(char *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),strnchrnul,(__haystack,__needle,__maxlen))
/* >> strnchrnul(3)
 * Same as `strnchr', but return `strnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strnchrnul,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),strnchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strnchrnul(3)
 * Same as `strnchr', but return `strnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnchrnul,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strnchrnul */
#include <libc/local/string/strnchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strnchrnul(3)
 * Same as `strnchr', but return `strnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnchrnul)(char *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnchrnul))(__haystack, __needle, __maxlen); }
/* >> strnchrnul(3)
 * Same as `strnchr', but return `strnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strnchrnul)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strnchrnul(3)
 * Same as `strnchr', but return `strnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnchrnul)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnchrnul))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strnchrnul */
#ifdef __CRT_HAVE_strnrchrnul
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strnrchrnul(3)
 * Same as `strnrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnrchrnul,(char *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),strnrchrnul,(__haystack,__needle,__maxlen))
/* >> strnrchrnul(3)
 * Same as `strnrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strnrchrnul,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),strnrchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strnrchrnul(3)
 * Same as `strnrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnrchrnul,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strnrchrnul */
#include <libc/local/string/strnrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strnrchrnul(3)
 * Same as `strnrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnrchrnul)(char *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchrnul))(__haystack, __needle, __maxlen); }
/* >> strnrchrnul(3)
 * Same as `strnrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strnrchrnul)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strnrchrnul(3)
 * Same as `strnrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnrchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnrchrnul)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchrnul))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strnrchrnul */
#ifdef __CRT_HAVE_stroff
/* >> stroff(3)
 * Same as `strchrnul', but return the offset from `str', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,stroff,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* __CRT_HAVE_stroff */
#include <libc/local/string/stroff.h>
/* >> stroff(3)
 * Same as `strchrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(stroff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL stroff)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stroff))(__haystack, __needle); })
#endif /* !__CRT_HAVE_stroff */
#ifdef __CRT_HAVE_strroff
/* >> strroff(3)
 * Same as `strrchrnul', but return the offset from `str', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,strroff,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* __CRT_HAVE_strroff */
#include <libc/local/string/strroff.h>
/* >> strroff(3)
 * Same as `strrchrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(strroff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strroff)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strroff))(__haystack, __needle); })
#endif /* !__CRT_HAVE_strroff */
#ifdef __CRT_HAVE_strnoff
/* >> strnoff(3)
 * Same as `strnchrnul', but return the offset from `str', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,strnoff,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#else /* __CRT_HAVE_strnoff */
#include <libc/local/string/strnoff.h>
/* >> strnoff(3)
 * Same as `strnchrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnoff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strnoff)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnoff))(__haystack, __needle, __maxlen); })
#endif /* !__CRT_HAVE_strnoff */
#ifdef __CRT_HAVE_strnroff
/* >> strnroff(3)
 * Same as `strnrchrnul', but return the offset from `str', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,strnroff,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#else /* __CRT_HAVE_strnroff */
#include <libc/local/string/strnroff.h>
/* >> strnroff(3)
 * Same as `strnrchrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnroff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strnroff)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnroff))(__haystack, __needle, __maxlen); })
#endif /* !__CRT_HAVE_strnroff */
#if defined(__fast_mempset_defined) && defined(__CRT_HAVE_mempset)
/* >> mempset(3)
 * Same as `memset', but return `dst + n_bytes', rather than `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempset))(__dst, __byte, __n_bytes); })
#elif defined(__fast_mempset_defined)
/* >> mempset(3)
 * Same as `memset', but return `dst + n_bytes', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempset)(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempset))(__dst, __byte, __n_bytes); }
#elif defined(__CRT_HAVE_mempset)
/* >> mempset(3)
 * Same as `memset', but return `dst + n_bytes', rather than `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),(__dst,__byte,__n_bytes))
#else /* ... */
#include <libc/local/string/mempset.h>
/* >> mempset(3)
 * Same as `memset', but return `dst + n_bytes', rather than `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempset)(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempset))(__dst, __byte, __n_bytes); })
#endif /* !... */
#if defined(__fast_mempmove_defined) && defined(__CRT_HAVE_mempmove)
/* >> mempmove(3)
 * Same as `memmove', but return `dst + n_bytes', rather than `dst' */
__CEIDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmove,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmove))(__dst, __src, __n_bytes); })
#elif defined(__fast_mempmove_defined)
/* >> mempmove(3)
 * Same as `memmove', but return `dst + n_bytes', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmove)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmove))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_mempmove)
/* >> mempmove(3)
 * Same as `memmove', but return `dst + n_bytes', rather than `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmove,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/mempmove.h>
/* >> mempmove(3)
 * Same as `memmove', but return `dst + n_bytes', rather than `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmove, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmove)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmove))(__dst, __src, __n_bytes); })
#endif /* !... */
#if defined(__fast_mempmoveup_defined) && defined(__CRT_HAVE_mempmoveup)
/* >> mempmoveup(3)
 * Same as `memmoveup', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes') */
__CEIDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveup))(__dst, __src, __n_bytes); })
#elif defined(__fast_mempmoveup_defined) && defined(__CRT_HAVE_mempmove)
/* >> mempmoveup(3)
 * Same as `memmoveup', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveup))(__dst, __src, __n_bytes); })
#elif defined(__fast_mempmoveup_defined)
/* >> mempmoveup(3)
 * Same as `memmoveup', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes') */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmoveup)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveup))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_mempmoveup)
/* >> mempmoveup(3)
 * Same as `memmoveup', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes') */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE_mempmove)
/* >> mempmoveup(3)
 * Same as `memmoveup', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmove,(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/mempmoveup.h>
/* >> mempmoveup(3)
 * Same as `memmoveup', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmoveup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmoveup)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveup))(__dst, __src, __n_bytes); })
#endif /* !... */
#if defined(__fast_mempmovedown_defined) && defined(__CRT_HAVE_mempmovedown)
/* >> mempmovedown(3)
 * Same as `memmovedown', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
__CEIDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedown))(__dst, __src, __n_bytes); })
#elif defined(__fast_mempmovedown_defined) && defined(__CRT_HAVE_mempmove)
/* >> mempmovedown(3)
 * Same as `memmovedown', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmove,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedown))(__dst, __src, __n_bytes); })
#elif defined(__fast_mempmovedown_defined)
/* >> mempmovedown(3)
 * Same as `memmovedown', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmovedown)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedown))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_mempmovedown)
/* >> mempmovedown(3)
 * Same as `memmovedown', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE_mempmove)
/* >> mempmovedown(3)
 * Same as `memmovedown', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmove,(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/mempmovedown.h>
/* >> mempmovedown(3)
 * Same as `memmovedown', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmovedown, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmovedown)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedown))(__dst, __src, __n_bytes); })
#endif /* !... */
#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
extern "C++" {
#if defined(__fast_mempmovec_defined) && defined(__CRT_HAVE_mempmovec)
/* >> mempmovec(3)
 * Same as `memmovec', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,mempmove,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempmovec,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovec))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__fast_mempmovec_defined)
/* >> mempmovec(3)
 * Same as `memmovec', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL mempmove)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovec))(__dst, __src, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_mempmovec)
/* >> mempmovec(3)
 * Same as `memmovec', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,mempmove,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempmovec,(__dst,__src,__elem_count,__elem_size))
#else /* ... */
} /* extern "C++" */
#include <libc/local/string/mempmovec.h>
extern "C++" {
/* >> mempmovec(3)
 * Same as `memmovec', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL mempmove)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovec))(__dst, __src, __elem_count, __elem_size); }
#endif /* !... */
#if defined(__fast_mempmoveupc_defined) && defined(__CRT_HAVE_mempmoveupc)
/* >> mempmoveupc(3)
 * Same   as   `memmoveupc',  but   return  `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,mempmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempmoveupc,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupc))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__fast_mempmoveupc_defined)
/* >> mempmoveupc(3)
 * Same   as   `memmoveupc',  but   return  `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE') */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL mempmoveup)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupc))(__dst, __src, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_mempmoveupc)
/* >> mempmoveupc(3)
 * Same   as   `memmoveupc',  but   return  `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,mempmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempmoveupc,(__dst,__src,__elem_count,__elem_size))
#else /* ... */
} /* extern "C++" */
#include <libc/local/string/mempmoveupc.h>
extern "C++" {
/* >> mempmoveupc(3)
 * Same   as   `memmoveupc',  but   return  `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL mempmoveup)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveupc))(__dst, __src, __elem_count, __elem_size); }
#endif /* !... */
#if defined(__fast_mempmovedownc_defined) && defined(__CRT_HAVE_mempmovedownc)
/* >> mempmovedownc(3)
 * Same  as  `memmovedownc',  but  return   `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE') */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,mempmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempmovedownc,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownc))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__fast_mempmovedownc_defined)
/* >> mempmovedownc(3)
 * Same  as  `memmovedownc',  but  return   `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE') */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL mempmovedown)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownc))(__dst, __src, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_mempmovedownc)
/* >> mempmovedownc(3)
 * Same  as  `memmovedownc',  but  return   `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,mempmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempmovedownc,(__dst,__src,__elem_count,__elem_size))
#else /* ... */
} /* extern "C++" */
#include <libc/local/string/mempmovedownc.h>
extern "C++" {
/* >> mempmovedownc(3)
 * Same  as  `memmovedownc',  but  return   `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL mempmovedown)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedownc))(__dst, __src, __elem_count, __elem_size); }
#endif /* !... */
#if defined(__fast_memmoveupc_defined) && defined(__CRT_HAVE_memmoveupc)
/* >> memmoveupc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,memmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmoveupc,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupc))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__fast_memmoveupc_defined)
/* >> memmoveupc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL memmoveup)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupc))(__dst, __src, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_memmoveupc)
/* >> memmoveupc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,memmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmoveupc,(__dst,__src,__elem_count,__elem_size))
#else /* ... */
} /* extern "C++" */
#include <libc/local/string/memmoveupc.h>
extern "C++" {
/* >> memmoveupc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL memmoveup)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupc))(__dst, __src, __elem_count, __elem_size); }
#endif /* !... */
#if defined(__fast_memmovedownc_defined) && defined(__CRT_HAVE_memmovedownc)
/* >> memmovedownc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,memmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmovedownc,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownc))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__fast_memmovedownc_defined)
/* >> memmovedownc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL memmovedown)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownc))(__dst, __src, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_memmovedownc)
/* >> memmovedownc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,memmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmovedownc,(__dst,__src,__elem_count,__elem_size))
#else /* ... */
} /* extern "C++" */
#include <libc/local/string/memmovedownc.h>
extern "C++" {
/* >> memmovedownc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1) void *__NOTHROW_NCX(__LIBCCALL memmovedown)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownc))(__dst, __src, __elem_count, __elem_size); }
#endif /* !... */
} /* extern "C++" */
#endif /* __cplusplus && __USE_STRING_OVERLOADS */
#ifdef __CRT_HAVE_rawmemrchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> rawmemrchr(3)
 * Same as `memrchr' without a search limit, starting at `haystack - 1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemrchr,(void *__restrict __haystack, int __needle),rawmemrchr,(__haystack,__needle))
/* >> rawmemrchr(3)
 * Same as `memrchr' without a search limit, starting at `haystack - 1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,rawmemrchr,(void const *__restrict __haystack, int __needle),rawmemrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> rawmemrchr(3)
 * Same as `memrchr' without a search limit, starting at `haystack - 1' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemrchr,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrchr */
#include <libc/local/string/rawmemrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> rawmemrchr(3)
 * Same as `memrchr' without a search limit, starting at `haystack - 1' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemrchr)(void *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchr))(__haystack, __needle); }
/* >> rawmemrchr(3)
 * Same as `memrchr' without a search limit, starting at `haystack - 1' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL rawmemrchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> rawmemrchr(3)
 * Same as `memrchr' without a search limit, starting at `haystack - 1' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemrchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrchr */
#if defined(__fast_memend_defined) && defined(__CRT_HAVE_memend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memend,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memend,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __needle, __n_bytes); })
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memend,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __needle, __n_bytes); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__CEIDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memend_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memend)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __needle, __n_bytes); }
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __needle, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memend,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memend,(__haystack,__needle,__n_bytes))
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memend,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memend)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))(__haystack, __needle, __n_bytes); }
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memend, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if defined(__fast_memrend_defined) && defined(__CRT_HAVE_memrend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrend,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrend,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __needle, __n_bytes); })
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memrend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrend,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __needle, __n_bytes); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__CEIDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__fast_memrend_defined)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrend)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __needle, __n_bytes); }
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memrend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __needle, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memrend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrend,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrend,(__haystack,__needle,__n_bytes))
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memrend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrend,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memrend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrend)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))(__haystack, __needle, __n_bytes); }
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memrend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrend, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if defined(__fast_memlen_defined) && defined(__CRT_HAVE_memlen)
/* >> memlen(3)
 * Same as `memend', but return the offset from `haystack', rather than the actual address.
 * Returns `n_bytes' if the given `needle' wasn't found */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memlen,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memlen))(__haystack, __needle, __n_bytes); })
#elif defined(__fast_memlen_defined)
/* >> memlen(3)
 * Same as `memend', but return the offset from `haystack', rather than the actual address.
 * Returns `n_bytes' if the given `needle' wasn't found */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memlen)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memlen))(__haystack, __needle, __n_bytes); }
#elif defined(__CRT_HAVE_memlen)
/* >> memlen(3)
 * Same as `memend', but return the offset from `haystack', rather than the actual address.
 * Returns `n_bytes' if the given `needle' wasn't found */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memlen,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#else /* ... */
#include <libc/local/string/memlen.h>
/* >> memlen(3)
 * Same as `memend', but return the offset from `haystack', rather than the actual address.
 * Returns `n_bytes' if the given `needle' wasn't found */
__NAMESPACE_LOCAL_USING_OR_IMPL(memlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memlen)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlen))(__haystack, __needle, __n_bytes); })
#endif /* !... */
#if defined(__fast_memrlen_defined) && defined(__CRT_HAVE_memrlen)
/* >> memrlen(3)
 * Same as `memrend', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1' if the given `needle' wasn't found */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memrlen,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrlen))(__haystack, __needle, __n_bytes); })
#elif defined(__fast_memrlen_defined)
/* >> memrlen(3)
 * Same as `memrend', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1' if the given `needle' wasn't found */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrlen)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrlen))(__haystack, __needle, __n_bytes); }
#elif defined(__CRT_HAVE_memrlen)
/* >> memrlen(3)
 * Same as `memrend', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1' if the given `needle' wasn't found */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memrlen,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#else /* ... */
#include <libc/local/string/memrlen.h>
/* >> memrlen(3)
 * Same as `memrend', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1' if the given `needle' wasn't found */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrlen)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlen))(__haystack, __needle, __n_bytes); })
#endif /* !... */
#ifdef __CRT_HAVE_rawmemlen
/* >> rawmemlen(3)
 * Same as `rawmemchr', but return the offset from `haystack', rather than the actual address. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,rawmemlen,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* __CRT_HAVE_rawmemlen */
#include <libc/local/string/rawmemlen.h>
/* >> rawmemlen(3)
 * Same as `rawmemchr', but return the offset from `haystack', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemlen)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemlen))(__haystack, __needle); })
#endif /* !__CRT_HAVE_rawmemlen */
#ifdef __CRT_HAVE_rawmemrlen
/* >> rawmemrlen(3)
 * Same as `rawmemrchr', but return the offset from `haystack', rather than the actual address. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrlen,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* __CRT_HAVE_rawmemrlen */
#include <libc/local/string/rawmemrlen.h>
/* >> rawmemrlen(3)
 * Same as `rawmemrchr', but return the offset from `haystack', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrlen)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrlen))(__haystack, __needle); })
#endif /* !__CRT_HAVE_rawmemrlen */
#if defined(__CRT_HAVE_memrmem0) && defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memrmem(3)
 * Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memrmem,(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memrmem0,(__haystack,__haystacklen,__needle,__needlelen))
/* >> memrmem(3)
 * Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memrmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memrmem0,(__haystack,__haystacklen,__needle,__needlelen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memrmem(3)
 * Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memrmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memrmem0,(__haystack,__haystacklen,__needle,__needlelen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memrmem) && !defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memrmem(3)
 * Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memrmem,(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memrmem,(__haystack,__haystacklen,__needle,__needlelen))
/* >> memrmem(3)
 * Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memrmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memrmem,(__haystack,__haystacklen,__needle,__needlelen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memrmem(3)
 * Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memrmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),(__haystack,__haystacklen,__needle,__needlelen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memrmem.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memrmem(3)
 * Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memrmem)(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrmem))(__haystack, __haystacklen, __needle, __needlelen); }
/* >> memrmem(3)
 * Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) void const *__NOTHROW_NCX(__LIBCCALL memrmem)(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrmem))(__haystack, __haystacklen, __needle, __needlelen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memrmem(3)
 * Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrmem, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memrmem)(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrmem))(__haystack, __haystacklen, __needle, __needlelen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if defined(__fast_memset_defined) && defined(__CRT_HAVE_memset)
/* >> mempatb(3)
 * Same as `memsetb', but repeat a 1-byte pattern on aligned addresses. */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempatb,(void *__restrict __dst, int __pattern, __SIZE_TYPE__ __n_bytes),memset,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))(__dst, __pattern, __n_bytes); })
#elif defined(__fast_memset_defined)
/* >> mempatb(3)
 * Same as `memsetb', but repeat a 1-byte pattern on aligned addresses. */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatb)(void *__restrict __dst, int __pattern, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))(__dst, __pattern, __n_bytes); }
#elif defined(__CRT_HAVE_memset)
/* >> mempatb(3)
 * Same as `memsetb', but repeat a 1-byte pattern on aligned addresses. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempatb,(void *__restrict __dst, int __pattern, __SIZE_TYPE__ __n_bytes),memset,(__dst,__pattern,__n_bytes))
#else /* ... */
#include <libc/local/string/memset.h>
/* >> mempatb(3)
 * Same as `memsetb', but repeat a 1-byte pattern on aligned addresses. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatb)(void *__restrict __dst, int __pattern, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memset))(__dst, __pattern, (__SIZE_TYPE__)__n_bytes); }
#endif /* !... */
#if defined(__fast_mempatw_defined) && defined(__CRT_HAVE_mempatw)
/* >> mempatw(3)
 * Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
__CEIDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempatw,(void *__restrict __dst, __UINT16_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatw))(__dst, __pattern, __n_bytes); })
#elif defined(__fast_mempatw_defined)
/* >> mempatw(3)
 * Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatw)(void *__restrict __dst, __UINT16_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatw))(__dst, __pattern, __n_bytes); }
#elif defined(__CRT_HAVE_mempatw)
/* >> mempatw(3)
 * Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempatw,(void *__restrict __dst, __UINT16_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes),(__dst,__pattern,__n_bytes))
#else /* ... */
#include <libc/local/string/mempatw.h>
/* >> mempatw(3)
 * Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempatw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatw)(void *__restrict __dst, __UINT16_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempatw))(__dst, __pattern, __n_bytes); })
#endif /* !... */
#if defined(__fast_mempatl_defined) && defined(__CRT_HAVE_mempatl)
/* >> mempatl(3)
 * Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
__CEIDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempatl,(void *__restrict __dst, __UINT32_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatl))(__dst, __pattern, __n_bytes); })
#elif defined(__fast_mempatl_defined)
/* >> mempatl(3)
 * Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatl)(void *__restrict __dst, __UINT32_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatl))(__dst, __pattern, __n_bytes); }
#elif defined(__CRT_HAVE_mempatl)
/* >> mempatl(3)
 * Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempatl,(void *__restrict __dst, __UINT32_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes),(__dst,__pattern,__n_bytes))
#else /* ... */
#include <libc/local/string/mempatl.h>
/* >> mempatl(3)
 * Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempatl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatl)(void *__restrict __dst, __UINT32_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempatl))(__dst, __pattern, __n_bytes); })
#endif /* !... */
#ifdef __UINT64_TYPE__
#if defined(__fast_mempatq_defined) && defined(__CRT_HAVE_mempatq)
/* >> mempatq(3)
 * Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
__CEIDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempatq,(void *__restrict __dst, __UINT64_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatq))(__dst, __pattern, __n_bytes); })
#elif defined(__fast_mempatq_defined)
/* >> mempatq(3)
 * Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatq)(void *__restrict __dst, __UINT64_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatq))(__dst, __pattern, __n_bytes); }
#elif defined(__CRT_HAVE_mempatq)
/* >> mempatq(3)
 * Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempatq,(void *__restrict __dst, __UINT64_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes),(__dst,__pattern,__n_bytes))
#else /* ... */
#include <libc/local/string/mempatq.h>
/* >> mempatq(3)
 * Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempatq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatq)(void *__restrict __dst, __UINT64_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempatq))(__dst, __pattern, __n_bytes); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */

/* memsetc() and mempsetc() */
#if defined(__cplusplus) && defined(__INTELLISENSE__)
extern "C++" {
template<class __T, class = decltype((int)(*(__T *)0 >> 0))> __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1))
void *__NOTHROW_NCX(memsetc)(void *__restrict __dst, __T __byte, size_t __word_count, size_t __word_size);
template<class __T, class = decltype((int)(*(__T *)0 >> 0))> __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1))
void *__NOTHROW_NCX(mempsetc)(void *__restrict __dst, __T __byte, size_t __word_count, size_t __word_size);
} /* extern "C++" */
#elif defined(__UINT64_TYPE__)
#ifndef __NO_builtin_choose_expr
#define memsetc(dst, word, word_count, word_size)                                                             \
	__builtin_choose_expr((word_size) == 1,                                                                   \
	                      (void *)(__NAMESPACE_STD_SYM memset)(dst, (int)(__UINT8_TYPE__)(word), word_count), \
	__builtin_choose_expr((word_size) == 2,                                                                   \
	                      (void *)memsetw(dst, (__UINT16_TYPE__)(word), word_count),                          \
	__builtin_choose_expr((word_size) == 4,                                                                   \
	                      (void *)memsetl(dst, (__UINT32_TYPE__)(word), word_count),                          \
	                      (void *)memsetq(dst, (__UINT64_TYPE__)(word), word_count))))
#define mempsetc(dst, word, word_count, word_size)                                         \
	__builtin_choose_expr((word_size) == 1,                                                \
	                      (void *)(mempset)(dst, (int)(__UINT8_TYPE__)(word), word_count), \
	__builtin_choose_expr((word_size) == 2,                                                \
	                      (void *)mempsetw(dst, (__UINT16_TYPE__)(word), word_count),      \
	__builtin_choose_expr((word_size) == 4,                                                \
	                      (void *)mempsetl(dst, (__UINT32_TYPE__)(word), word_count),      \
	                      (void *)mempsetq(dst, (__UINT64_TYPE__)(word), word_count))))
#else /* !__NO_builtin_choose_expr */
#define memsetc(dst, word, word_count, word_size)                                         \
	((word_size) == 1                                                                     \
	 ? (void *)(__NAMESPACE_STD_SYM memset)(dst, (int)(__UINT8_TYPE__)(word), word_count) \
	 : (word_size) == 2                                                                   \
	   ? (void *)memsetw(dst, (__UINT16_TYPE__)(word), word_count)                        \
	   : (word_size) == 4                                                                 \
	     ? (void *)memsetl(dst, (__UINT32_TYPE__)(word), word_count)                      \
	     : (void *)memsetq(dst, (__UINT64_TYPE__)(word), word_count))
#define mempsetc(dst, word, word_count, word_size)                     \
	((word_size) == 1                                                  \
	 ? (void *)(mempset)(dst, (int)(__UINT8_TYPE__)(word), word_count) \
	 : (word_size) == 2                                                \
	   ? (void *)mempsetw(dst, (__UINT16_TYPE__)(word), word_count)    \
	   : (word_size) == 4                                              \
	     ? (void *)mempsetl(dst, (__UINT32_TYPE__)(word), word_count)  \
	     : (void *)mempsetq(dst, (__UINT64_TYPE__)(word), word_count))
#endif /* __NO_builtin_choose_expr */
#else /* __UINT64_TYPE__ */
#ifndef __NO_builtin_choose_expr
#define memsetc(dst, word, word_count, word_size)                                                             \
	__builtin_choose_expr((word_size) == 1,                                                                   \
	                      (void *)(__NAMESPACE_STD_SYM memset)(dst, (int)(__UINT8_TYPE__)(word), word_count), \
	__builtin_choose_expr((word_size) == 2,                                                                   \
	                      (void *)memsetw(dst, (__UINT16_TYPE__)(word), word_count),                          \
	                      (void *)memsetl(dst, (__UINT32_TYPE__)(word), word_count)))
#define mempsetc(dst, word, word_count, word_size)                                         \
	__builtin_choose_expr((word_size) == 1,                                                \
	                      (void *)(mempset)(dst, (int)(__UINT8_TYPE__)(word), word_count), \
	__builtin_choose_expr((word_size) == 2,                                                \
	                      (void *)mempsetw(dst, (__UINT16_TYPE__)(word), word_count),      \
	                      (void *)mempsetl(dst, (__UINT32_TYPE__)(word), word_count)))
#else /* !__NO_builtin_choose_expr */
#define memsetc(dst, word, word_count, word_size)                                         \
	((word_size) == 1                                                                     \
	 ? (void *)(__NAMESPACE_STD_SYM memset)(dst, (int)(__UINT8_TYPE__)(word), word_count) \
	 : (word_size) == 2                                                                   \
	   ? (void *)memsetw(dst, (__UINT16_TYPE__)(word), word_count)                        \
	   : (void *)memsetl(dst, (__UINT32_TYPE__)(word), word_count))
#define mempsetc(dst, word, word_count, word_size)                     \
	((word_size) == 1                                                  \
	 ? (void *)(mempset)(dst, (int)(__UINT8_TYPE__)(word), word_count) \
	 : (word_size) == 2                                                \
	   ? (void *)mempsetw(dst, (__UINT16_TYPE__)(word), word_count)    \
	   : (void *)mempsetl(dst, (__UINT32_TYPE__)(word), word_count))
#endif /* __NO_builtin_choose_expr */
#endif /* !__UINT64_TYPE__ */

#ifdef __CRT_HAVE_memcasecmp
/* >> memcasecmp(3), memcasecmp_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE_memicmp)
/* >> memcasecmp(3), memcasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),memicmp,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE__memicmp)
/* >> memcasecmp(3), memcasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),_memicmp,(__s1,__s2,__num_chars))
#else /* ... */
#include <libc/local/string/memcasecmp.h>
/* >> memcasecmp(3), memcasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memcasecmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp))(__s1, __s2, __num_chars); })
#endif /* !... */
#if defined(__CRT_HAVE_memcasemem0) && defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem,(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memcasemem0,(__haystack,__haystacklen,__needle,__needlelen))
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memcasemem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memcasemem0,(__haystack,__haystacklen,__needle,__needlelen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memcasemem0,(__haystack,__haystacklen,__needle,__needlelen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memcasemem) && !defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem,(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memcasemem,(__haystack,__haystacklen,__needle,__needlelen))
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memcasemem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memcasemem,(__haystack,__haystacklen,__needle,__needlelen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),(__haystack,__haystacklen,__needle,__needlelen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memcasemem.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memcasemem)(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasemem))(__haystack, __haystacklen, __needle, __needlelen); }
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) void const *__NOTHROW_NCX(__LIBCCALL memcasemem)(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasemem))(__haystack, __haystacklen, __needle, __needlelen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcasemem, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memcasemem)(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasemem))(__haystack, __haystacklen, __needle, __needlelen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_memcasecmp_l
/* >> memcasecmp(3), memcasecmp_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcasecmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars, __locale_t __locale),(__s1,__s2,__num_chars,__locale))
#elif defined(__CRT_HAVE__memicmp_l)
/* >> memcasecmp(3), memcasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcasecmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars, __locale_t __locale),_memicmp_l,(__s1,__s2,__num_chars,__locale))
#else /* ... */
#include <libc/local/string/memcasecmp_l.h>
/* >> memcasecmp(3), memcasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memcasecmp_l)(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp_l))(__s1, __s2, __num_chars, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_memcasemem0_l) && defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem_l,(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen, __locale_t __locale),memcasemem0_l,(__haystack,__haystacklen,__needle,__needlelen,__locale))
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memcasemem_l,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen, __locale_t __locale),memcasemem0_l,(__haystack,__haystacklen,__needle,__needlelen,__locale))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem_l,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen, __locale_t __locale),memcasemem0_l,(__haystack,__haystacklen,__needle,__needlelen,__locale))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memcasemem_l) && !defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem_l,(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen, __locale_t __locale),memcasemem_l,(__haystack,__haystacklen,__needle,__needlelen,__locale))
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memcasemem_l,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen, __locale_t __locale),memcasemem_l,(__haystack,__haystacklen,__needle,__needlelen,__locale))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem_l,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen, __locale_t __locale),(__haystack,__haystacklen,__needle,__needlelen,__locale))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/memcasemem_l.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memcasemem_l)(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasemem_l))(__haystack, __haystacklen, __needle, __needlelen, __locale); }
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) void const *__NOTHROW_NCX(__LIBCCALL memcasemem_l)(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasemem_l))(__haystack, __haystacklen, __needle, __needlelen, __locale); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcasemem_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memcasemem_l)(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasemem_l))(__haystack, __haystacklen, __needle, __needlelen, __locale); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_strcasestr_l
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,strcasestr_l,(char *__haystack, char const *__needle, __locale_t __locale),strcasestr_l,(__haystack,__needle,__locale))
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char const *,__NOTHROW_NCX,strcasestr_l,(char const *__haystack, char const *__needle, __locale_t __locale),strcasestr_l,(__haystack,__needle,__locale))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,strcasestr_l,(char const *__haystack, char const *__needle, __locale_t __locale),(__haystack,__needle,__locale))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strcasestr_l */
#include <libc/local/string/strcasestr_l.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char *__NOTHROW_NCX(__LIBCCALL strcasestr_l)(char *__haystack, char const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasestr_l))(__haystack, __needle, __locale); }
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char const *__NOTHROW_NCX(__LIBCCALL strcasestr_l)(char const *__haystack, char const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasestr_l))(__haystack, __needle, __locale); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasestr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char *__NOTHROW_NCX(__LIBCCALL strcasestr_l)(char const *__haystack, char const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasestr_l))(__haystack, __needle, __locale); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strcasestr_l */
#endif /* __USE_XOPEN2K8 */



#ifdef __CRT_HAVE_vstrdupf
/* >> strdupf(3), vstrdupf(3)
 * Print the given `format' into a newly allocated, heap-allocated string */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 0),char *,__NOTHROW_NCX,vstrdupf,(char const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)))
#include <libc/local/string/vstrdupf.h>
/* >> strdupf(3), vstrdupf(3)
 * Print the given `format' into a newly allocated, heap-allocated string */
__NAMESPACE_LOCAL_USING_OR_IMPL(vstrdupf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 0) char *__NOTHROW_NCX(__LIBCCALL vstrdupf)(char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vstrdupf))(__format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE_strdupf
/* >> strdupf(3), vstrdupf(3)
 * Print the given `format' into a newly allocated, heap-allocated string */
__LIBC __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 2) char *__NOTHROW_NCX(__VLIBCCALL strdupf)(char const *__restrict __format, ...) __CASMNAME_SAME("strdupf");
#elif defined(__CRT_HAVE_vstrdupf) || defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)))
#include <libc/local/string/strdupf.h>
/* >> strdupf(3), vstrdupf(3)
 * Print the given `format' into a newly allocated, heap-allocated string */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(strdupf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 2) char *__NOTHROW_NCX(__VLIBCCALL strdupf)(char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strdupf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define strdupf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strdupf))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
/* mstrdupa() & friends. */
#ifdef __INTELLISENSE__
#define mstrdupa  mstrdupa
#define mstrndupa mstrndupa
#ifdef __malloca_mayfail
extern __ATTR_MALLOC __ATTR_WUNUSED __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(mstrdupa)(char const *__restrict __string);
#else /* __malloca_mayfail */
extern __ATTR_MALLOC __ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(mstrdupa)(char const *__restrict __string);
#endif /* !__malloca_mayfail */
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#ifdef __malloca_mayfail
extern __ATTR_MALLOC __ATTR_WUNUSED __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(mstrndupa)(char const *__restrict __string, __size_t __maxlen);
#else /* __malloca_mayfail */
extern __ATTR_MALLOC __ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(mstrndupa)(char const *__restrict __string, __size_t __maxlen);
#endif /* !__malloca_mayfail */
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#elif defined(__NO_XBLOCK)
__FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_NONNULL((2)) char *
__NOTHROW_NCX(__mstrdupa_init)(void *__buf, char const *__restrict __string) {
#ifdef __malloca_mayfail
	if __likely(__buf)
#endif /* __malloca_mayfail */
	{
		__buf = __NAMESPACE_STD_SYM strcpy((char *)__buf, __string);
	}
	return (char *)__buf;
}
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
__FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_NONNULL((2)) char *
__NOTHROW_NCX(__mstrndupa_init)(void *__buf, char const *__restrict __string, __size_t __maxlen) {
#ifdef __malloca_mayfail
	if __likely(__buf)
#endif /* __malloca_mayfail */
	{
		__size_t __buflen = strnlen(__string, __maxlen) * sizeof(char);
#ifdef __mempcpy_defined
		*(char *)mempcpy(__buf, __string, __buflen) = 0;
#else /* __mempcpy_defined */
		((char *)__NAMESPACE_STD_SYM memcpy(__buf, __string, __buflen))[__buflen] = 0;
#endif /* !__mempcpy_defined */
	}
	return (char *)__buf;
}
#endif /* __USE_XOPEN2K8 || __USE_DOS */
/* Without X-blocks, it's impossible to prevent multiple evaluations of the `str' argument... */
#define mstrdupa(str) \
	__mstrdupa_init(__malloca((__NAMESPACE_STD_SYM strlen(str) + 1) * sizeof(char)), str)
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#define mstrndupa(str, maxlen) \
	__mstrndupa_init(__malloca((strnlen(str, maxlen) + 1) * sizeof(char)), str, maxlen)
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#else /* __NO_XBLOCK */
#ifdef __malloca_mayfail
#define mstrdupa(str)                                                                     \
	__XBLOCK({                                                                            \
		char const *__orig_s = (str);                                                     \
		__size_t __orig_len  = (__NAMESPACE_STD_SYM strlen(__orig_s) + 1) * sizeof(char); \
		char *__copy_s       = (char *)__malloca(__orig_len);                             \
		__XRETURN __likely(__copy_s)                                                      \
		          ? (char *)__NAMESPACE_STD_SYM memcpy(__copy_s, __orig_s, __orig_len)    \
		          : __copy_s;                                                             \
	})
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#define mstrndupa(str, maxlen)                                               \
	__XBLOCK({                                                               \
		char const *__orig_s = (str);                                        \
		__size_t __orig_len  = strnlen(__orig_s, maxlen) * sizeof(char);     \
		char *__copy_s       = (char *)__malloca(__orig_len + sizeof(char)); \
		if __likely(__copy_s) {                                              \
			__copy_s[__orig_len / sizeof(char)] = 0;                         \
			__NAMESPACE_STD_SYM memcpy(__copy_s, __orig_s, __orig_len);      \
		}                                                                    \
		__XRETURN __copy_s;                                                  \
	})
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#else /* __malloca_mayfail */
#define mstrdupa(str)                                                                     \
	__XBLOCK({                                                                            \
		char const *__orig_s = (str);                                                     \
		__size_t __orig_len  = (__NAMESPACE_STD_SYM strlen(__orig_s) + 1) * sizeof(char); \
		char *__copy_s       = (char *)__malloca(__orig_len);                             \
		__XRETURN (char *)__NAMESPACE_STD_SYM memcpy(__copy_s, __orig_s, __orig_len);     \
	})
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#define mstrndupa(str, maxlen)                                                        \
	__XBLOCK({                                                                        \
		char const *__orig_s = (str);                                                 \
		__size_t __orig_len  = strnlen(__orig_s, maxlen) * sizeof(char);              \
		char *__copy_s = (char *)__malloca(__orig_len + sizeof(char));                \
		__copy_s[__orig_len / sizeof(char)] = 0;                                      \
		__XRETURN (char *)__NAMESPACE_STD_SYM memcpy(__copy_s, __orig_s, __orig_len); \
	})
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#endif /* !__malloca_mayfail */
#endif /* !__NO_XBLOCK */
#ifdef __CRT_HAVE_wildstrcmp
/* >> wildstrcmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wildstrcmp,(char const *__pattern, char const *__string),(__pattern,__string))
#else /* __CRT_HAVE_wildstrcmp */
#include <libc/local/string/wildstrcmp.h>
/* >> wildstrcmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wildstrcmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL wildstrcmp)(char const *__pattern, char const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildstrcmp))(__pattern, __string); })
#endif /* !__CRT_HAVE_wildstrcmp */
#ifdef __CRT_HAVE_wildstrcasecmp
/* >> wildstrcasecmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wildstrcasecmp,(char const *__pattern, char const *__string),(__pattern,__string))
#else /* __CRT_HAVE_wildstrcasecmp */
#include <libc/local/string/wildstrcasecmp.h>
/* >> wildstrcasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wildstrcasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL wildstrcasecmp)(char const *__pattern, char const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildstrcasecmp))(__pattern, __string); })
#endif /* !__CRT_HAVE_wildstrcasecmp */
#ifdef __CRT_HAVE_fuzzy_strcmp
/* >> fuzzy_strcmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_strcmp,(char const *__s1, char const *__s2),(__s1,__s2))
#else /* __CRT_HAVE_fuzzy_strcmp */
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_memcmp) || !defined(__NO_MALLOCA)
#include <libc/local/string/fuzzy_strcmp.h>
/* >> fuzzy_strcmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_strcmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_strcmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_strcmp))(__s1, __s2); })
#endif /* __CRT_HAVE_fuzzy_memcmp || !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_strcmp */
#ifdef __CRT_HAVE_fuzzy_strncmp
/* >> fuzzy_strncmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_strncmp,(char const *__s1, __SIZE_TYPE__ __s1_maxlen, char const *__s2, __SIZE_TYPE__ __s2_maxlen),(__s1,__s1_maxlen,__s2,__s2_maxlen))
#else /* __CRT_HAVE_fuzzy_strncmp */
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_memcmp) || !defined(__NO_MALLOCA)
#include <libc/local/string/fuzzy_strncmp.h>
/* >> fuzzy_strncmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_strncmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_strncmp)(char const *__s1, __SIZE_TYPE__ __s1_maxlen, char const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_strncmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* __CRT_HAVE_fuzzy_memcmp || !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_strncmp */
#ifdef __CRT_HAVE_fuzzy_strcasecmp
/* >> fuzzy_strcasecmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_strcasecmp,(char const *__s1, char const *__s2),(__s1,__s2))
#else /* __CRT_HAVE_fuzzy_strcasecmp */
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_memcasecmp) || !defined(__NO_MALLOCA)
#include <libc/local/string/fuzzy_strcasecmp.h>
/* >> fuzzy_strcasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_strcasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_strcasecmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_strcasecmp))(__s1, __s2); })
#endif /* __CRT_HAVE_fuzzy_memcasecmp || !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_strcasecmp */
#ifdef __CRT_HAVE_fuzzy_strncasecmp
/* >> fuzzy_strncasecmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_strncasecmp,(char const *__s1, __SIZE_TYPE__ __s1_maxlen, char const *__s2, __SIZE_TYPE__ __s2_maxlen),(__s1,__s1_maxlen,__s2,__s2_maxlen))
#else /* __CRT_HAVE_fuzzy_strncasecmp */
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_memcasecmp) || !defined(__NO_MALLOCA)
#include <libc/local/string/fuzzy_strncasecmp.h>
/* >> fuzzy_strncasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_strncasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_strncasecmp)(char const *__s1, __SIZE_TYPE__ __s1_maxlen, char const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_strncasecmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* __CRT_HAVE_fuzzy_memcasecmp || !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_strncasecmp */
#ifdef __CRT_HAVE_fuzzy_memcmp
/* >> fuzzy_memcmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_memcmp,(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes),(__s1,__s1_bytes,__s2,__s2_bytes))
#else /* __CRT_HAVE_fuzzy_memcmp */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <libc/local/string/fuzzy_memcmp.h>
/* >> fuzzy_memcmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_memcmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_memcmp)(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmp))(__s1, __s1_bytes, __s2, __s2_bytes); })
#endif /* !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_memcmp */
#ifdef __CRT_HAVE_fuzzy_memcasecmp
/* >> fuzzy_memcasecmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_memcasecmp,(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes),(__s1,__s1_bytes,__s2,__s2_bytes))
#else /* __CRT_HAVE_fuzzy_memcasecmp */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <libc/local/string/fuzzy_memcasecmp.h>
/* >> fuzzy_memcasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_memcasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_memcasecmp)(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcasecmp))(__s1, __s1_bytes, __s2, __s2_bytes); })
#endif /* !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_memcasecmp */
#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_fuzzy_strcasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#else /* __CRT_HAVE_fuzzy_strcasecmp_l */
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_memcasecmp_l) || !defined(__NO_MALLOCA)
#include <libc/local/string/fuzzy_strcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_strcasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_strcasecmp_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_strcasecmp_l))(__s1, __s2, __locale); })
#endif /* __CRT_HAVE_fuzzy_memcasecmp_l || !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_strcasecmp_l */
#ifdef __CRT_HAVE_fuzzy_strncasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_strncasecmp_l,(char const *__s1, __SIZE_TYPE__ __s1_maxlen, char const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#else /* __CRT_HAVE_fuzzy_strncasecmp_l */
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_memcasecmp_l) || !defined(__NO_MALLOCA)
#include <libc/local/string/fuzzy_strncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_strncasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_strncasecmp_l)(char const *__s1, __SIZE_TYPE__ __s1_maxlen, char const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_strncasecmp_l))(__s1, __s1_maxlen, __s2, __s2_maxlen, __locale); })
#endif /* __CRT_HAVE_fuzzy_memcasecmp_l || !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_strncasecmp_l */
#ifdef __CRT_HAVE_wildstrcasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wildstrcasecmp_l,(char const *__pattern, char const *__string, __locale_t __locale),(__pattern,__string,__locale))
#else /* __CRT_HAVE_wildstrcasecmp_l */
#include <libc/local/string/wildstrcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildstrcasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL wildstrcasecmp_l)(char const *__pattern, char const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildstrcasecmp_l))(__pattern, __string, __locale); })
#endif /* !__CRT_HAVE_wildstrcasecmp_l */
#ifdef __CRT_HAVE_fuzzy_memcasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_memcasecmp_l,(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#else /* __CRT_HAVE_fuzzy_memcasecmp_l */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <libc/local/string/fuzzy_memcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_memcasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_memcasecmp_l)(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcasecmp_l))(__s1, __s1_bytes, __s2, __s2_bytes, __locale); })
#endif /* !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_memcasecmp_l */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_STRING_BWLQ
#ifdef __CRT_HAVE_fuzzy_memcmp
/* >> fuzzy_memcmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_memcmpb,(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_memcmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#else /* __CRT_HAVE_fuzzy_memcmp */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <libc/local/string/fuzzy_memcmp.h>
/* >> fuzzy_memcmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_memcmpb)(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmp))(__s1, __s1_bytes, __s2, __s2_bytes); }
#endif /* !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_memcmp */
#ifdef __CRT_HAVE_fuzzy_memcmpw
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(3),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_memcmpw,(void const *__s1, __SIZE_TYPE__ __s1_words, void const *__s2, __SIZE_TYPE__ __s2_words),(__s1,__s1_words,__s2,__s2_words))
#elif defined(__CRT_HAVE_fuzzy_wmemcmp) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(3),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_memcmpw,(void const *__s1, __SIZE_TYPE__ __s1_words, void const *__s2, __SIZE_TYPE__ __s2_words),fuzzy_wmemcmp,(__s1,__s1_words,__s2,__s2_words))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(3),__SIZE_TYPE__,__NOTHROW_NCX,__LIBCCALL,fuzzy_memcmpw,(void const *__s1, __SIZE_TYPE__ __s1_words, void const *__s2, __SIZE_TYPE__ __s2_words),DOS$fuzzy_wmemcmp,(__s1,__s1_words,__s2,__s2_words))
#else /* ... */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <libc/local/string/fuzzy_memcmpw.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_memcmpw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(3) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_memcmpw)(void const *__s1, __SIZE_TYPE__ __s1_words, void const *__s2, __SIZE_TYPE__ __s2_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpw))(__s1, __s1_words, __s2, __s2_words); })
#endif /* !__NO_MALLOCA */
#endif /* !... */
#ifdef __CRT_HAVE_fuzzy_memcmpl
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(3),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_memcmpl,(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords),(__s1,__s1_dwords,__s2,__s2_dwords))
#elif defined(__CRT_HAVE_fuzzy_wmemcmp) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(3),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_memcmpl,(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords),fuzzy_wmemcmp,(__s1,__s1_dwords,__s2,__s2_dwords))
#elif defined(__CRT_HAVE_KOS$fuzzy_wmemcmp) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(3),__SIZE_TYPE__,__NOTHROW_NCX,__LIBCCALL,fuzzy_memcmpl,(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords),KOS$fuzzy_wmemcmp,(__s1,__s1_dwords,__s2,__s2_dwords))
#else /* ... */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <libc/local/string/fuzzy_memcmpl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_memcmpl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(3) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_memcmpl)(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpl))(__s1, __s1_dwords, __s2, __s2_dwords); })
#endif /* !__NO_MALLOCA */
#endif /* !... */
#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE_fuzzy_memcmpq
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(3),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_memcmpq,(void const *__s1, __SIZE_TYPE__ __s1_qwords, void const *__s2, __SIZE_TYPE__ __s2_qwords),(__s1,__s1_qwords,__s2,__s2_qwords))
#else /* __CRT_HAVE_fuzzy_memcmpq */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <libc/local/string/fuzzy_memcmpq.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_memcmpq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(3) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_memcmpq)(void const *__s1, __SIZE_TYPE__ __s1_qwords, void const *__s2, __SIZE_TYPE__ __s2_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpq))(__s1, __s1_qwords, __s2, __s2_qwords); })
#endif /* !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_memcmpq */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */
#ifdef __CRT_HAVE_strncoll
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strncoll,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/string/strncoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncoll)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#ifdef __CRT_HAVE_strcasecoll
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE__stricoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),_stricoll,(__s1,__s2))
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#else /* ... */
#include <libc/local/string/strcasecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasecoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL strcasecoll)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecoll))(__s1, __s2); })
#endif /* !... */
#ifdef __CRT_HAVE_strncasecoll
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/string/strncasecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncasecoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncasecoll)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#ifdef __CRT_HAVE_strnrev
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnrev,(char *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* __CRT_HAVE_strnrev */
#include <libc/local/string/strnrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnrev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnrev)(char *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrev))(__str, __maxlen); })
#endif /* !__CRT_HAVE_strnrev */
#ifdef __CRT_HAVE_strnlwr
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnlwr,(char *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* __CRT_HAVE_strnlwr */
#include <libc/local/string/strnlwr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnlwr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnlwr)(char *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnlwr))(__str, __maxlen); })
#endif /* !__CRT_HAVE_strnlwr */
#ifdef __CRT_HAVE_strnupr
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnupr,(char *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* __CRT_HAVE_strnupr */
#include <libc/local/string/strnupr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnupr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnupr)(char *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnupr))(__str, __maxlen); })
#endif /* !__CRT_HAVE_strnupr */
#ifdef __CRT_HAVE_memrev
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrev,(void *__restrict __base, __SIZE_TYPE__ __n_bytes),(__base,__n_bytes))
#else /* __CRT_HAVE_memrev */
#include <libc/local/string/memrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memrev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrev)(void *__restrict __base, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrev))(__base, __n_bytes); })
#endif /* !__CRT_HAVE_memrev */
#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_strncoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strncoll_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/string/strncoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncoll_l)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strcasecoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecoll_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__stricoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecoll_l,(char const *__s1, char const *__s2, __locale_t __locale),_stricoll_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/string/strcasecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasecoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL strcasecoll_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecoll_l))(__s1, __s2, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strncasecoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_strncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncmpi_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strncmpi_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/string/strncasecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncasecoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncasecoll_l)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strlwr_l
__CDECLARE(__ATTR_LEAF __ATTR_INOUT(1),char *,__NOTHROW_NCX,strlwr_l,(char *__restrict __str, __locale_t __locale),(__str,__locale))
#elif defined(__CRT_HAVE__strlwr_l)
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char *,__NOTHROW_NCX,strlwr_l,(char *__restrict __str, __locale_t __locale),_strlwr_l,(__str,__locale))
#else /* ... */
#include <libc/local/string/strlwr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strlwr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char *__NOTHROW_NCX(__LIBCCALL strlwr_l)(char *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlwr_l))(__str, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strupr_l
__CDECLARE(__ATTR_LEAF __ATTR_INOUT(1),char *,__NOTHROW_NCX,strupr_l,(char *__restrict __str, __locale_t __locale),(__str,__locale))
#elif defined(__CRT_HAVE__strupr_l)
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char *,__NOTHROW_NCX,strupr_l,(char *__restrict __str, __locale_t __locale),_strupr_l,(__str,__locale))
#else /* ... */
#include <libc/local/string/strupr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strupr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char *__NOTHROW_NCX(__LIBCCALL strupr_l)(char *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strupr_l))(__str, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strnlwr_l
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnlwr_l,(char *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__str,__maxlen,__locale))
#else /* __CRT_HAVE_strnlwr_l */
#include <libc/local/string/strnlwr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnlwr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnlwr_l)(char *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnlwr_l))(__str, __maxlen, __locale); })
#endif /* !__CRT_HAVE_strnlwr_l */
#ifdef __CRT_HAVE_strnupr_l
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnupr_l,(char *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__str,__maxlen,__locale))
#else /* __CRT_HAVE_strnupr_l */
#include <libc/local/string/strnupr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnupr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnupr_l)(char *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnupr_l))(__str, __maxlen, __locale); })
#endif /* !__CRT_HAVE_strnupr_l */
#endif /* __USE_XOPEN2K8 */
#ifdef __USE_STRING_BWLQ
#ifdef __CRT_HAVE_memrev
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrevb,(void *__restrict __base, __SIZE_TYPE__ __n_bytes),memrev,(__base,__n_bytes))
#else /* __CRT_HAVE_memrev */
#include <libc/local/string/memrev.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrevb)(void *__restrict __base, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrev))(__base, __n_bytes); }
#endif /* !__CRT_HAVE_memrev */
#ifdef __CRT_HAVE_memrevw
__CDECLARE(__ATTR_LEAF __ATTR_INOUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,memrevw,(void *__restrict __base, __SIZE_TYPE__ __n_words),(__base,__n_words))
#else /* __CRT_HAVE_memrevw */
#include <libc/local/string/memrevw.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memrevw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrevw)(void *__restrict __base, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrevw))(__base, __n_words); })
#endif /* !__CRT_HAVE_memrevw */
#ifdef __CRT_HAVE_memrevl
__CDECLARE(__ATTR_LEAF __ATTR_INOUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,memrevl,(void *__restrict __base, __SIZE_TYPE__ __n_dwords),(__base,__n_dwords))
#else /* __CRT_HAVE_memrevl */
#include <libc/local/string/memrevl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memrevl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrevl)(void *__restrict __base, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrevl))(__base, __n_dwords); })
#endif /* !__CRT_HAVE_memrevl */
#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE_memrevq
__CDECLARE(__ATTR_LEAF __ATTR_INOUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,memrevq,(void *__restrict __base, __SIZE_TYPE__ __n_qwords),(__base,__n_qwords))
#else /* __CRT_HAVE_memrevq */
#include <libc/local/string/memrevq.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memrevq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrevq)(void *__restrict __base, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrevq))(__base, __n_qwords); })
#endif /* !__CRT_HAVE_memrevq */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */
#ifdef __CRT_HAVE_strcmpz
/* >> strcmpz(3)
 * Similar to `strcmp(3)', but the given `rhs' string mustn't necessarily be NUL-terminated.
 * Instead, that string's length is  fixed at `rhs_len', and  the compare is equivalent  to:
 * > char *dup = (char *)malloc((rhs_len + 1) * sizeof(char));
 * > *(char *)mempcpy(dup, rhs, rhs_len, sizeof(char)) = '\0';
 * > return strcmp(lhs, dup); */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcmpz,(char const *__lhs, char const *__rhs, size_t __rhs_len),(__lhs,__rhs,__rhs_len))
#else /* __CRT_HAVE_strcmpz */
#include <libc/local/string/strcmpz.h>
/* >> strcmpz(3)
 * Similar to `strcmp(3)', but the given `rhs' string mustn't necessarily be NUL-terminated.
 * Instead, that string's length is  fixed at `rhs_len', and  the compare is equivalent  to:
 * > char *dup = (char *)malloc((rhs_len + 1) * sizeof(char));
 * > *(char *)mempcpy(dup, rhs, rhs_len, sizeof(char)) = '\0';
 * > return strcmp(lhs, dup); */
__NAMESPACE_LOCAL_USING_OR_IMPL(strcmpz, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcmpz)(char const *__lhs, char const *__rhs, size_t __rhs_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcmpz))(__lhs, __rhs, __rhs_len); })
#endif /* !__CRT_HAVE_strcmpz */
#ifdef __CRT_HAVE_strstartcmp
/* >> strstartcmp(3)
 * Compare the first `strnlen(str, strlen(startswith_str))' characters
 * of `str' with  `startswith_str', returning the  usual >0, <0,  ==0. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strstartcmp,(char const *__str, char const *__startswith),(__str,__startswith))
#else /* __CRT_HAVE_strstartcmp */
#include <libc/local/string/strstartcmp.h>
/* >> strstartcmp(3)
 * Compare the first `strnlen(str, strlen(startswith_str))' characters
 * of `str' with  `startswith_str', returning the  usual >0, <0,  ==0. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strstartcmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL strstartcmp)(char const *__str, char const *__startswith) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strstartcmp))(__str, __startswith); })
#endif /* !__CRT_HAVE_strstartcmp */
#ifdef __CRT_HAVE_strstartcmpz
/* >> strstartcmpz(3)
 * Compare the first `strnlen(str, startswith_len)' characters of
 * `str' with  `startswith', returning  the  usual >0,  <0,  ==0. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strstartcmpz,(char const *__str, char const *__startswith, size_t __startswith_len),(__str,__startswith,__startswith_len))
#else /* __CRT_HAVE_strstartcmpz */
#include <libc/local/string/strstartcmpz.h>
/* >> strstartcmpz(3)
 * Compare the first `strnlen(str, startswith_len)' characters of
 * `str' with  `startswith', returning  the  usual >0,  <0,  ==0. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strstartcmpz, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strstartcmpz)(char const *__str, char const *__startswith, size_t __startswith_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strstartcmpz))(__str, __startswith, __startswith_len); })
#endif /* !__CRT_HAVE_strstartcmpz */
#ifdef __CRT_HAVE_bitcpy
/* >> bitcpy(3)
 * Copy exactly `num_bits' from `src_base+(src_bit_offset/NBBY)' to `dst_base+(dst_bit_offset/NBBY)',
 * doing a byte-wise copy  but leaving bits not  meant to be copied  untouched. Inside of  individual
 * bytes, individual bits are  indexed such that the  least significant bit is  at `0', and the  most
 * significant bit is at `NBBY-1':
 * >> byte_t src[] = { 0b00001001 };
 * >> byte_t dst[] = { 0b00000000 };
 * >> bitcpy(dst, 4, src, 0, 4);
 * >> assert(dst == 0b10010000); */
__CDECLARE_VOID(__ATTR_IN(3) __ATTR_OUT(1),__NOTHROW_NCX,bitcpy,(void *__restrict __dst_base, size_t __dst_bit_offset, void const *__restrict __src_base, size_t __src_bit_offset, size_t __num_bits),(__dst_base,__dst_bit_offset,__src_base,__src_bit_offset,__num_bits))
#else /* __CRT_HAVE_bitcpy */
#include <libc/local/string/bitcpy.h>
/* >> bitcpy(3)
 * Copy exactly `num_bits' from `src_base+(src_bit_offset/NBBY)' to `dst_base+(dst_bit_offset/NBBY)',
 * doing a byte-wise copy  but leaving bits not  meant to be copied  untouched. Inside of  individual
 * bytes, individual bits are  indexed such that the  least significant bit is  at `0', and the  most
 * significant bit is at `NBBY-1':
 * >> byte_t src[] = { 0b00001001 };
 * >> byte_t dst[] = { 0b00000000 };
 * >> bitcpy(dst, 4, src, 0, 4);
 * >> assert(dst == 0b10010000); */
__NAMESPACE_LOCAL_USING_OR_IMPL(bitcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bitcpy)(void *__restrict __dst_base, size_t __dst_bit_offset, void const *__restrict __src_base, size_t __src_bit_offset, size_t __num_bits) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bitcpy))(__dst_base, __dst_bit_offset, __src_base, __src_bit_offset, __num_bits); })
#endif /* !__CRT_HAVE_bitcpy */
#ifdef __CRT_HAVE_strrstr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrstr(3)
 * Find the last instance of `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,strrstr,(char *__haystack, char const *__needle),strrstr,(__haystack,__needle))
/* >> strrstr(3)
 * Find the last instance of `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char const *,__NOTHROW_NCX,strrstr,(char const *__haystack, char const *__needle),strrstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrstr(3)
 * Find the last instance of `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,strrstr,(char const *__haystack, char const *__needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strrstr */
#include <libc/local/string/strrstr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrstr(3)
 * Find the last instance of `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char *__NOTHROW_NCX(__LIBCCALL strrstr)(char *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrstr))(__haystack, __needle); }
/* >> strrstr(3)
 * Find the last instance of `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char const *__NOTHROW_NCX(__LIBCCALL strrstr)(char const *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrstr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrstr(3)
 * Find the last instance of `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strrstr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char *__NOTHROW_NCX(__LIBCCALL strrstr)(char const *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrstr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strrstr */
#ifdef __CRT_HAVE_strlstrip
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strlstrip(3)
 * Skip all leading `isspace(3)'-characters of `str' to return a pointer
 * to  the first  non-space character (or  the trailing NUL  if `str' is
 * empty or contains only spaces).
 * NOTE: If available, use `unicode_isspace(3)' instead of `isspace(3)'
 * @return: * : Pointer to the first non-space character in `str' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strlstrip,(char *__str),strlstrip,(__str))
/* >> strlstrip(3)
 * Skip all leading `isspace(3)'-characters of `str' to return a pointer
 * to  the first  non-space character (or  the trailing NUL  if `str' is
 * empty or contains only spaces).
 * NOTE: If available, use `unicode_isspace(3)' instead of `isspace(3)'
 * @return: * : Pointer to the first non-space character in `str' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,strlstrip,(char const *__str),strlstrip,(__str))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strlstrip(3)
 * Skip all leading `isspace(3)'-characters of `str' to return a pointer
 * to  the first  non-space character (or  the trailing NUL  if `str' is
 * empty or contains only spaces).
 * NOTE: If available, use `unicode_isspace(3)' instead of `isspace(3)'
 * @return: * : Pointer to the first non-space character in `str' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strlstrip,(char const *__str),(__str))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strlstrip */
#include <libc/local/string/strlstrip.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strlstrip(3)
 * Skip all leading `isspace(3)'-characters of `str' to return a pointer
 * to  the first  non-space character (or  the trailing NUL  if `str' is
 * empty or contains only spaces).
 * NOTE: If available, use `unicode_isspace(3)' instead of `isspace(3)'
 * @return: * : Pointer to the first non-space character in `str' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL strlstrip)(char *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlstrip))(__str); }
/* >> strlstrip(3)
 * Skip all leading `isspace(3)'-characters of `str' to return a pointer
 * to  the first  non-space character (or  the trailing NUL  if `str' is
 * empty or contains only spaces).
 * NOTE: If available, use `unicode_isspace(3)' instead of `isspace(3)'
 * @return: * : Pointer to the first non-space character in `str' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char const *__NOTHROW_NCX(__LIBCCALL strlstrip)(char const *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlstrip))(__str); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strlstrip(3)
 * Skip all leading `isspace(3)'-characters of `str' to return a pointer
 * to  the first  non-space character (or  the trailing NUL  if `str' is
 * empty or contains only spaces).
 * NOTE: If available, use `unicode_isspace(3)' instead of `isspace(3)'
 * @return: * : Pointer to the first non-space character in `str' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strlstrip, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL strlstrip)(char const *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlstrip))(__str); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strlstrip */
#ifdef __CRT_HAVE_strrstrip
/* >> strrstrip(3)
 * Find the last trailing `isspace(3)'-character (i.e. the one closest
 * to the start and not followed by a non-`isspace(3)'-character), and
 * replace it with '\0', effectively deleting trailing space.
 * NOTE: If available, use `unicode_isspace(3)' instead of `isspace(3)'
 * @return: * : Always re-returns `str' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strrstrip,(char *__str),(__str))
#else /* __CRT_HAVE_strrstrip */
#include <libc/local/string/strrstrip.h>
/* >> strrstrip(3)
 * Find the last trailing `isspace(3)'-character (i.e. the one closest
 * to the start and not followed by a non-`isspace(3)'-character), and
 * replace it with '\0', effectively deleting trailing space.
 * NOTE: If available, use `unicode_isspace(3)' instead of `isspace(3)'
 * @return: * : Always re-returns `str' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strrstrip, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL strrstrip)(char *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrstrip))(__str); })
#endif /* !__CRT_HAVE_strrstrip */
#ifdef __CRT_HAVE_strstrip
/* >> strstrip(3)
 * The combination of `strlstrip(3)' and `strrstrip(3)'
 * @return: * : Same as `strrstrip(strlstrip(str))' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,strstrip,(char *__str),(__str))
#else /* __CRT_HAVE_strstrip */
#include <libc/local/string/strstrip.h>
/* >> strstrip(3)
 * The combination of `strlstrip(3)' and `strrstrip(3)'
 * @return: * : Same as `strrstrip(strlstrip(str))' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strstrip, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL strstrip)(char *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strstrip))(__str); })
#endif /* !__CRT_HAVE_strstrip */
#endif /* __USE_KOS */


#if defined(__USE_KOS) || defined(__USE_DOS)
#ifdef __CRT_HAVE_strlwr
__CDECLARE(__ATTR_INOUT(1),char *,__NOTHROW_NCX,strlwr,(char *__restrict __str),(__str))
#elif defined(__CRT_HAVE__strlwr)
__CREDIRECT(__ATTR_INOUT(1),char *,__NOTHROW_NCX,strlwr,(char *__restrict __str),_strlwr,(__str))
#else /* ... */
#include <libc/local/string/strlwr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strlwr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char *__NOTHROW_NCX(__LIBCCALL strlwr)(char *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlwr))(__str); })
#endif /* !... */
#ifdef __CRT_HAVE_strupr
__CDECLARE(__ATTR_INOUT(1),char *,__NOTHROW_NCX,strupr,(char *__restrict __str),(__str))
#elif defined(__CRT_HAVE__strupr)
__CREDIRECT(__ATTR_INOUT(1),char *,__NOTHROW_NCX,strupr,(char *__restrict __str),_strupr,(__str))
#else /* ... */
#include <libc/local/string/strupr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strupr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) char *__NOTHROW_NCX(__LIBCCALL strupr)(char *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strupr))(__str); })
#endif /* !... */
#ifdef __CRT_HAVE_strset
__CDECLARE(__ATTR_LEAF __ATTR_INOUT(1),char *,__NOTHROW_NCX,strset,(char *__restrict __str, int __ch),(__str,__ch))
#elif defined(__CRT_HAVE__strset)
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char *,__NOTHROW_NCX,strset,(char *__restrict __str, int __ch),_strset,(__str,__ch))
#else /* ... */
#include <libc/local/string/strset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char *__NOTHROW_NCX(__LIBCCALL strset)(char *__restrict __str, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strset))(__str, __ch); })
#endif /* !... */
#ifdef __CRT_HAVE_strnset
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnset,(char *__restrict __str, int __ch, __SIZE_TYPE__ __maxlen),(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE__strnset)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnset,(char *__restrict __str, int __ch, __SIZE_TYPE__ __maxlen),_strnset,(__str,__ch,__maxlen))
#else /* ... */
#include <libc/local/string/strnset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnset)(char *__restrict __str, int __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnset))(__str, __ch, __maxlen); })
#endif /* !... */
#ifdef __CRT_HAVE_strrev
__CDECLARE(__ATTR_LEAF __ATTR_INOUT(1),char *,__NOTHROW_NCX,strrev,(char *__restrict __str),(__str))
#elif defined(__CRT_HAVE__strrev)
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char *,__NOTHROW_NCX,strrev,(char *__restrict __str),_strrev,(__str))
#else /* ... */
#include <libc/local/string/strrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strrev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char *__NOTHROW_NCX(__LIBCCALL strrev)(char *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrev))(__str); })
#endif /* !... */
#endif /* __USE_KOS || __USE_DOS */


#ifdef __USE_DOS
#ifndef ___memccpy_defined
#define ___memccpy_defined
#ifdef __CRT_HAVE_memccpy
__CREDIRECT(__ATTR_LEAF __ATTR_INS(2, 4) __ATTR_OUTS(1, 4) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,_memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes),memccpy,(__dst,__src,__needle,__num_bytes))
#elif defined(__CRT_HAVE__memccpy)
__CDECLARE(__ATTR_LEAF __ATTR_INS(2, 4) __ATTR_OUTS(1, 4) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,_memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes),(__dst,__src,__needle,__num_bytes))
#elif defined(__CRT_HAVE___memccpy)
__CREDIRECT(__ATTR_LEAF __ATTR_INS(2, 4) __ATTR_OUTS(1, 4) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,_memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes),__memccpy,(__dst,__src,__needle,__num_bytes))
#else /* ... */
#include <libc/local/string/memccpy.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INS(2, 4) __ATTR_OUTS(1, 4) __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL _memccpy)(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memccpy))(__dst, __src, __needle, __num_bytes); }
#endif /* !... */
#endif /* !___memccpy_defined */
#ifndef ___memicmp_defined
#define ___memicmp_defined
#ifdef __CRT_HAVE_memcasecmp
/* >> memcasecmp(3), memcasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),memcasecmp,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE_memicmp)
/* >> memcasecmp(3), memcasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),memicmp,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE__memicmp)
/* >> memcasecmp(3), memcasecmp_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),(__s1,__s2,__num_chars))
#else /* ... */
#include <libc/local/string/memcasecmp.h>
/* >> memcasecmp(3), memcasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _memicmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp))(__s1, __s2, __num_chars); }
#endif /* !... */
#endif /* !___memicmp_defined */
#ifndef ___memicmp_l_defined
#define ___memicmp_l_defined
#ifdef __CRT_HAVE_memcasecmp_l
/* >> memcasecmp(3), memcasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars, __locale_t __locale),memcasecmp_l,(__s1,__s2,__num_chars,__locale))
#elif defined(__CRT_HAVE__memicmp_l)
/* >> memcasecmp(3), memcasecmp_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars, __locale_t __locale),(__s1,__s2,__num_chars,__locale))
#else /* ... */
#include <libc/local/string/memcasecmp_l.h>
/* >> memcasecmp(3), memcasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _memicmp_l)(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp_l))(__s1, __s2, __num_chars, __locale); }
#endif /* !... */
#endif /* !___memicmp_l_defined */
#ifndef __memicmp_defined
#define __memicmp_defined
#ifdef __CRT_HAVE_memcasecmp
/* >> memcasecmp(3), memcasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memicmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),memcasecmp,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE_memicmp)
/* >> memcasecmp(3), memcasecmp_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memicmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE__memicmp)
/* >> memcasecmp(3), memcasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memicmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),_memicmp,(__s1,__s2,__num_chars))
#else /* ... */
#include <libc/local/string/memcasecmp.h>
/* >> memcasecmp(3), memcasecmp_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memicmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp))(__s1, __s2, __num_chars); }
#endif /* !... */
#endif /* !__memicmp_defined */
#ifdef __CRT_HAVE__strset_s
__CDECLARE(__ATTR_INOUTS(1, 2),__errno_t,__NOTHROW_NCX,_strset_s,(char *__dst, __SIZE_TYPE__ __dstsize, int __ch),(__dst,__dstsize,__ch))
#else /* __CRT_HAVE__strset_s */
#include <libc/local/string/_strset_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strset_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUTS(1, 2) __errno_t __NOTHROW_NCX(__LIBCCALL _strset_s)(char *__dst, __SIZE_TYPE__ __dstsize, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strset_s))(__dst, __dstsize, __ch); })
#endif /* !__CRT_HAVE__strset_s */

#ifdef __USE_DOS_SLIB
#ifndef __memcpy_s_defined
#define __memcpy_s_defined
#ifdef __CRT_HAVE_memcpy_s
__CDECLARE(__ATTR_INS(3, 4) __ATTR_OUTS(1, 2),__errno_t,__NOTHROW_NCX,memcpy_s,(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength),(__dst,__dstlength,__src,__srclength))
#else /* __CRT_HAVE_memcpy_s */
#include <libc/local/string/memcpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpy_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) __errno_t __NOTHROW_NCX(__LIBCCALL memcpy_s)(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy_s))(__dst, __dstlength, __src, __srclength); })
#endif /* !__CRT_HAVE_memcpy_s */
#endif /* !__memcpy_s_defined */
#ifndef __memmove_s_defined
#define __memmove_s_defined
#ifdef __CRT_HAVE_memmove_s
__CDECLARE(__ATTR_INS(3, 4) __ATTR_OUTS(1, 2),__errno_t,__NOTHROW_NCX,memmove_s,(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength),(__dst,__dstlength,__src,__srclength))
#else /* __CRT_HAVE_memmove_s */
#include <libc/local/string/memmove_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memmove_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) __errno_t __NOTHROW_NCX(__LIBCCALL memmove_s)(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmove_s))(__dst, __dstlength, __src, __srclength); })
#endif /* !__CRT_HAVE_memmove_s */
#endif /* !__memmove_s_defined */
#ifdef __CRT_HAVE_strcpy_s
__CDECLARE(__ATTR_IN_OPT(3) __ATTR_OUTS(1, 2),__errno_t,__NOTHROW_NCX,strcpy_s,(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src),(__dst,__dstsize,__src))
#else /* __CRT_HAVE_strcpy_s */
#include <libc/local/string/strcpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcpy_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(3) __ATTR_OUTS(1, 2) __errno_t __NOTHROW_NCX(__LIBCCALL strcpy_s)(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcpy_s))(__dst, __dstsize, __src); })
#endif /* !__CRT_HAVE_strcpy_s */
#ifdef __CRT_HAVE_strcat_s
__CDECLARE(__ATTR_INOUT_OPT(1) __ATTR_IN_OPT(3),__errno_t,__NOTHROW_NCX,strcat_s,(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src),(__dst,__dstsize,__src))
#else /* __CRT_HAVE_strcat_s */
#include <libc/local/string/strcat_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcat_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(1) __ATTR_IN_OPT(3) __errno_t __NOTHROW_NCX(__LIBCCALL strcat_s)(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcat_s))(__dst, __dstsize, __src); })
#endif /* !__CRT_HAVE_strcat_s */
#ifndef __strnlen_s_defined
#define __strnlen_s_defined
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strnlen_defined
#define __local___localdep_strnlen_defined
#if __has_builtin(__builtin_strnlen) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strnlen)
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),strnlen,{ return __builtin_strnlen(__str, __maxlen); })
#elif defined(__CRT_HAVE_strnlen)
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),strnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE___strncnt)
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),__strncnt,(__str,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strnlen.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
#define __localdep_strnlen __LIBC_LOCAL_NAME(strnlen)
#endif /* !... */
#endif /* !__local___localdep_strnlen_defined */
__NAMESPACE_LOCAL_END
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strnlen_s)(char const *__str, __SIZE_TYPE__ __maxlen) { return __str ? (__NAMESPACE_LOCAL_SYM __localdep_strnlen)(__str, __maxlen) : 0; }
#endif /* !__strnlen_s_defined */
#ifdef __CRT_HAVE_strncat_s
__CDECLARE(__ATTR_INOUT_OPT(1) __ATTR_IN_OPT(3),__errno_t,__NOTHROW_NCX,strncat_s,(char *__dst, rsize_t __dstsize, const char *__src, rsize_t __maxlen),(__dst,__dstsize,__src,__maxlen))
#else /* __CRT_HAVE_strncat_s */
#include <libc/local/string/strncat_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncat_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(1) __ATTR_IN_OPT(3) __errno_t __NOTHROW_NCX(__LIBCCALL strncat_s)(char *__dst, rsize_t __dstsize, const char *__src, rsize_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncat_s))(__dst, __dstsize, __src, __maxlen); })
#endif /* !__CRT_HAVE_strncat_s */
#ifdef __CRT_HAVE_strncpy_s
__CDECLARE(__ATTR_IN_OPT(3) __ATTR_OUTS(1, 2),__errno_t,__NOTHROW_NCX,strncpy_s,(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __maxlen),(__dst,__dstsize,__src,__maxlen))
#else /* __CRT_HAVE_strncpy_s */
#include <libc/local/string/strncpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncpy_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(3) __ATTR_OUTS(1, 2) __errno_t __NOTHROW_NCX(__LIBCCALL strncpy_s)(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncpy_s))(__dst, __dstsize, __src, __maxlen); })
#endif /* !__CRT_HAVE_strncpy_s */
#ifdef __CRT_HAVE_strtok_r
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char *,__NOTHROW_NCX,strtok_s,(char *__str, char const *__delim, char **__restrict __save_ptr),strtok_r,(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE_strtok_s)
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char *,__NOTHROW_NCX,strtok_s,(char *__str, char const *__delim, char **__restrict __save_ptr),(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE___strtok_r)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),char *,__NOTHROW_NCX,strtok_s,(char *__str, char const *__delim, char **__restrict __save_ptr),__strtok_r,(__str,__delim,__save_ptr))
#else /* ... */
#include <libc/local/string/strtok_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1) char *__NOTHROW_NCX(__LIBCCALL strtok_s)(char *__str, char const *__delim, char **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtok_r))(__str, __delim, __save_ptr); }
#endif /* !... */
#endif /* __USE_DOS_SLIB */
#if __has_builtin(__builtin_strdup) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strdup)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,_strdup,(char const *__restrict __string),strdup,{ return __builtin_strdup(__string); })
#elif defined(__CRT_HAVE_strdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,_strdup,(char const *__restrict __string),strdup,(__string))
#elif defined(__CRT_HAVE__strdup)
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,_strdup,(char const *__restrict __string),(__string))
#elif defined(__CRT_HAVE__mbsdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,_strdup,(char const *__restrict __string),_mbsdup,(__string))
#elif defined(__CRT_HAVE___strdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,_strdup,(char const *__restrict __string),__strdup,(__string))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/string/strdup.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL _strdup)(char const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strdup))(__string); }
#endif /* ... */
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),strcasecmp,{ return __builtin_strcasecmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE___strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),__strcasecmp,(__s1,__s2))
#else /* ... */
#include <libc/local/string/strcasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL _stricmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))(__s1, __s2); }
#endif /* !... */
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),strcasecmp,{ return __builtin_strcasecmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE___strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),__strcasecmp,(__s1,__s2))
#else /* ... */
#include <libc/local/string/strcasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL _strcmpi)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))(__s1, __s2); }
#endif /* !... */
#ifdef __CRT_HAVE_strcasecmp_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricmp_l,(char const *__s1, char const *__s2, __locale_t __locale),strcasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__stricmp_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricmp_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___strcasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricmp_l,(char const *__s1, char const *__s2, __locale_t __locale),__strcasecmp_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/string/strcasecmp_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL _stricmp_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp_l))(__s1, __s2, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_strcoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_strcoll_l,(char const *__s1, char const *__s2, __locale_t __locale),strcoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__strcoll_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_strcoll_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___strcoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_strcoll_l,(char const *__s1, char const *__s2, __locale_t __locale),__strcoll_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/string/strcoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL _strcoll_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcoll_l))(__s1, __s2, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_strcasecoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),strcasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE__stricoll)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#else /* ... */
#include <libc/local/string/strcasecoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL _stricoll)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecoll))(__s1, __s2); }
#endif /* !... */
#ifdef __CRT_HAVE_strcasecoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricoll_l,(char const *__s1, char const *__s2, __locale_t __locale),strcasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__stricoll_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_stricoll_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/string/strcasecoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL _stricoll_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecoll_l))(__s1, __s2, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_strncoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncoll)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/string/strncoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strncoll)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncoll))(__s1, __s2, __maxlen); }
#endif /* !... */
#ifdef __CRT_HAVE_strncoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),strncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncoll_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/string/strncoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strncoll_l)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncoll_l))(__s1, __s2, __maxlen, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_strncasecoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicoll)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/string/strncasecoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strnicoll)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecoll))(__s1, __s2, __maxlen); }
#endif /* !... */
#ifdef __CRT_HAVE_strncasecoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),strncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicoll_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_strncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncmpi_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strncmpi_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/string/strncasecoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strnicoll_l)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecoll_l))(__s1, __s2, __maxlen, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE__strerror
__CDECLARE(__ATTR_WUNUSED __ATTR_IN_OPT(1),char *,__NOTHROW_RPC,_strerror,(char const *__message),(__message))
#else /* __CRT_HAVE__strerror */
#include <libc/errno.h>
#if defined(__CRT_HAVE__strerror_s) || defined(__libc_geterrno)
#include <libc/local/string/_strerror.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strerror, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN_OPT(1) char *__NOTHROW_RPC(__LIBCCALL _strerror)(char const *__message) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strerror))(__message); })
#endif /* __CRT_HAVE__strerror_s || __libc_geterrno */
#endif /* !__CRT_HAVE__strerror */
#ifdef __CRT_HAVE__strerror_s
__CDECLARE(__ATTR_IN_OPT(3) __ATTR_OUTS(1, 2),__errno_t,__NOTHROW_RPC,_strerror_s,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__message),(__buf,__buflen,__message))
#else /* __CRT_HAVE__strerror_s */
#include <libc/errno.h>
#ifdef __libc_geterrno
#include <libc/local/string/_strerror_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strerror_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(3) __ATTR_OUTS(1, 2) __errno_t __NOTHROW_RPC(__LIBCCALL _strerror_s)(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__message) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strerror_s))(__buf, __buflen, __message); })
#endif /* __libc_geterrno */
#endif /* !__CRT_HAVE__strerror_s */
#ifdef __CRT_HAVE__strlwr_s
__CDECLARE(__ATTR_INOUT_OPT(1),__errno_t,__NOTHROW_NCX,_strlwr_s,(char *__buf, __SIZE_TYPE__ __buflen),(__buf,__buflen))
#else /* __CRT_HAVE__strlwr_s */
#include <libc/local/string/_strlwr_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strlwr_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(1) __errno_t __NOTHROW_NCX(__LIBCCALL _strlwr_s)(char *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strlwr_s))(__buf, __buflen); })
#endif /* !__CRT_HAVE__strlwr_s */
#ifdef __CRT_HAVE__strupr_s
__CDECLARE(__ATTR_INOUT_OPT(1),__errno_t,__NOTHROW_NCX,_strupr_s,(char *__buf, __SIZE_TYPE__ __buflen),(__buf,__buflen))
#else /* __CRT_HAVE__strupr_s */
#include <libc/local/string/_strupr_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strupr_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(1) __errno_t __NOTHROW_NCX(__LIBCCALL _strupr_s)(char *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strupr_s))(__buf, __buflen); })
#endif /* !__CRT_HAVE__strupr_s */
#ifdef __CRT_HAVE__strlwr_s_l
__CDECLARE(__ATTR_INOUT_OPT(1),__errno_t,__NOTHROW_NCX,_strlwr_s_l,(char *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale),(__buf,__buflen,__locale))
#else /* __CRT_HAVE__strlwr_s_l */
#include <libc/local/string/_strlwr_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strlwr_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(1) __errno_t __NOTHROW_NCX(__LIBCCALL _strlwr_s_l)(char *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strlwr_s_l))(__buf, __buflen, __locale); })
#endif /* !__CRT_HAVE__strlwr_s_l */
#ifdef __CRT_HAVE__strupr_s_l
__CDECLARE(__ATTR_INOUT_OPT(1),__errno_t,__NOTHROW_NCX,_strupr_s_l,(char *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale),(__buf,__buflen,__locale))
#else /* __CRT_HAVE__strupr_s_l */
#include <libc/local/string/_strupr_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strupr_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(1) __errno_t __NOTHROW_NCX(__LIBCCALL _strupr_s_l)(char *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strupr_s_l))(__buf, __buflen, __locale); })
#endif /* !__CRT_HAVE__strupr_s_l */
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,{ return __builtin_strncasecmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strncmpi,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncmpi,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/string/strncasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strnicmp)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp))(__s1, __s2, __maxlen); }
#endif /* !... */
#ifdef __CRT_HAVE_strncasecmp_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_strnicmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicmp_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_strnicmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncmpi_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_strnicmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strncmpi_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___strncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_strnicmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/string/strncasecmp_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL _strnicmp_l)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp_l))(__s1, __s2, __maxlen, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE__strnset_s
__CDECLARE(__ATTR_INOUTS(1, 4),__errno_t,__NOTHROW_NCX,_strnset_s,(char *__restrict __buf, __SIZE_TYPE__ __buflen, int __ch, __SIZE_TYPE__ __maxlen),(__buf,__buflen,__ch,__maxlen))
#else /* __CRT_HAVE__strnset_s */
#include <libc/local/string/_strnset_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strnset_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUTS(1, 4) __errno_t __NOTHROW_NCX(__LIBCCALL _strnset_s)(char *__restrict __buf, __SIZE_TYPE__ __buflen, int __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strnset_s))(__buf, __buflen, __ch, __maxlen); })
#endif /* !__CRT_HAVE__strnset_s */
#ifdef __CRT_HAVE_strrev
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),char *,__NOTHROW_NCX,_strrev,(char *__restrict __str),strrev,(__str))
#elif defined(__CRT_HAVE__strrev)
__CDECLARE(__ATTR_LEAF __ATTR_INOUT(1),char *,__NOTHROW_NCX,_strrev,(char *__restrict __str),(__str))
#else /* ... */
#include <libc/local/string/strrev.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) char *__NOTHROW_NCX(__LIBCCALL _strrev)(char *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrev))(__str); }
#endif /* !... */
#ifdef __CRT_HAVE_strxfrm_l
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,_strxfrm_l,(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),strxfrm_l,(__dst,__src,__buflen,__locale))
#elif defined(__CRT_HAVE__strxfrm_l)
__CDECLARE(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,_strxfrm_l,(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),(__dst,__src,__buflen,__locale))
#elif defined(__CRT_HAVE___strxfrm_l)
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,_strxfrm_l,(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),__strxfrm_l,(__dst,__src,__buflen,__locale))
#else /* ... */
#include <libc/local/string/strxfrm_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _strxfrm_l)(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strxfrm_l))(__dst, __src, __buflen, __locale); }
#endif /* !... */
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),strcasecmp,{ return __builtin_strcasecmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE___strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),__strcasecmp,(__s1,__s2))
#else /* ... */
#include <libc/local/string/strcasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL stricmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))(__s1, __s2); }
#endif /* !... */
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),strcasecmp,{ return __builtin_strcasecmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE___strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),__strcasecmp,(__s1,__s2))
#else /* ... */
#include <libc/local/string/strcasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL strcmpi)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))(__s1, __s2); }
#endif /* !... */
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,{ return __builtin_strncasecmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strncmpi,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncmpi,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/string/strncasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strnicmp)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp))(__s1, __s2, __maxlen); }
#endif /* !... */
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,{ return __builtin_strncasecmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncmpi,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/string/strncasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strncmpi)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp))(__s1, __s2, __maxlen); }
#endif /* !... */
#ifdef __CRT_HAVE_strncasecmp_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_strncmpi_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_strncmpi_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncmpi_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_strncmpi_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___strncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_strncmpi_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/string/strncasecmp_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL _strncmpi_l)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp_l))(__s1, __s2, __maxlen, __locale); }
#endif /* !... */
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,{ return __builtin_strncasecmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strncmpi,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/string/strncasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncmpi)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp))(__s1, __s2, __maxlen); }
#endif /* !... */
#endif /* __USE_DOS */

#if defined(__LIBC_BIND_OPTIMIZATIONS) && !defined(__NO_builtin_constant_p)
#ifndef __INTELLISENSE__
#if __has_builtin(__builtin_strlen)
#ifdef __cplusplus
/* Special handling, so this macro also works as `std::strlen(...)' */
#define strlen(x) size_t(__builtin_constant_p(x) ? __builtin_strlen(x) : (__NAMESPACE_STD_SYM strlen)(x))
#else /* __cplusplus */
#define strlen(x) (__builtin_constant_p(x) ? __builtin_strlen(x) : (strlen)(x))
#endif /* !__cplusplus */
#endif /* __has_builtin(__builtin_strlen) */
#endif /* !__INTELLISENSE__ */
#endif /* __LIBC_BIND_OPTIMIZATIONS && !__NO_builtin_constant_p */

/* strdupa() & friends. */
#if defined(__USE_GNU) && defined(__hybrid_alloca)
#ifdef __INTELLISENSE__
#define strdupa  strdupa
#define strndupa strndupa
extern __ATTR_MALLOC __ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(strdupa)(char const *__restrict __string);
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
extern __ATTR_MALLOC __ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(strndupa)(char const *__restrict __string, __size_t __maxlen);
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#elif defined(__NO_XBLOCK)
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
__FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__strndupa_init)(void *__restrict __buf, char const *__restrict __string, __size_t __maxlen) {
	__size_t __buflen = strnlen(__string, __maxlen) * sizeof(char);
#ifdef __mempcpy_defined
	*(char *)mempcpy(__buf, __string, __buflen) = 0;
#else /* __mempcpy_defined */
	((char *)__NAMESPACE_STD_SYM memcpy(__buf, __string, __buflen))[__buflen] = 0;
#endif /* !__mempcpy_defined */
	return (char *)__buf;
}
#endif /* __USE_XOPEN2K8 || __USE_DOS */
/* Without X-blocks, it's impossible to prevent multiple evaluations of the `str' argument... */
#define strdupa(str) \
	(__NAMESPACE_STD_SYM strcpy((char *)__hybrid_alloca((__NAMESPACE_STD_SYM strlen(str) + 1) * sizeof(char)), str))
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#define strndupa(str, maxlen) \
	__strndupa_init(__hybrid_alloca((strnlen(str, maxlen) + 1) * sizeof(char)), str, maxlen)
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#else /* __NO_XBLOCK */
#define strdupa(str)                                                                      \
	__XBLOCK({                                                                            \
		char const *__orig_s = (str);                                                     \
		__size_t __orig_len  = (__NAMESPACE_STD_SYM strlen(__orig_s) + 1) * sizeof(char); \
		__XRETURN (char *)__NAMESPACE_STD_SYM memcpy(__hybrid_alloca(__orig_len),         \
		                                             __orig_s, __orig_len);               \
	})
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#define strndupa(str, maxlen)                                                         \
	__XBLOCK({                                                                        \
		char const *__orig_s = (str);                                                 \
		__size_t __orig_len  = strnlen(__orig_s, maxlen) * sizeof(char);              \
		char *__copy_s = (char *)__hybrid_alloca(__orig_len + sizeof(char));          \
		__copy_s[__orig_len / sizeof(char)] = 0;                                      \
		__XRETURN (char *)__NAMESPACE_STD_SYM memcpy(__copy_s, __orig_s, __orig_len); \
	})
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#endif /* !__NO_XBLOCK */
#endif /* __USE_GNU && __hybrid_alloca */


/* >> void *memset(void *dst, int byte, size_t num_bytes);
 * >> void *memset(void *dst, T word, size_t word_count, size_t word_size);
 * >> void *mempset(void *dst, int byte, size_t num_bytes);
 * >> void *mempset(void *dst, T word, size_t word_count, size_t word_size); */
#ifdef __USE_STRING_OVERLOADS
#if defined(__cplusplus) && defined(__INTELLISENSE__)
extern "C++" {
template<class __T, class = decltype((int)(*(__T *)0 >> 0))> __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1))
void *__NOTHROW_NCX(memset)(void *__restrict __dst, __T __byte, size_t __word_count, size_t __word_size);
#ifdef __USE_KOS
template<class __T, class = decltype((int)(*(__T *)0 >> 0))> __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1))
void *__NOTHROW_NCX(mempset)(void *__restrict __dst, __T __byte, size_t __word_count, size_t __word_size);
#endif /* __USE_KOS */
} /* extern "C++" */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
#define __PRIVATE_memset_3 (memset)
#ifdef __USE_KOS
#define __PRIVATE_memset_4  memsetc
#define __PRIVATE_mempset_3 (mempset)
#define __PRIVATE_mempset_4 mempsetc
#undef mempset
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define mempset(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempset_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define mempset(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempset_, (args))(args)
#endif /* ... */
#else /* __USE_KOS */
__SYSDECL_END
#include <libc/string.h>
__SYSDECL_BEGIN
#ifdef __UINT64_TYPE__
#ifndef __NO_builtin_choose_expr
#define __PRIVATE_memset_4(dst, word, word_count, word_size)                                   \
	__builtin_choose_expr((word_size) == 1,                                                    \
	                      (void *)__libc_memset(dst, (int)(__UINT8_TYPE__)(word), word_count), \
	__builtin_choose_expr((word_size) == 2,                                                    \
	                      (void *)__libc_memsetw(dst, (__UINT16_TYPE__)(word), word_count),    \
	__builtin_choose_expr((word_size) == 4,                                                    \
	                      (void *)__libc_memsetl(dst, (__UINT32_TYPE__)(word), word_count),    \
	                      (void *)__libc_memsetq(dst, (__UINT64_TYPE__)(word), word_count))))
#else /* !__NO_builtin_choose_expr */
#define __PRIVATE_memset_4(dst, word, word_count, word_size)                \
	((word_size) == 1                                                       \
	 ? (void *)__libc_memset(dst, (int)(__UINT8_TYPE__)(word), word_count)  \
	 : (word_size) == 2                                                     \
	   ? (void *)__libc_memsetw(dst, (__UINT16_TYPE__)(word), word_count)   \
	   : (word_size) == 4                                                   \
	     ? (void *)__libc_memsetl(dst, (__UINT32_TYPE__)(word), word_count) \
	     : (void *)__libc_memsetq(dst, (__UINT64_TYPE__)(word), word_count))
#endif /* __NO_builtin_choose_expr */
#else /* __UINT64_TYPE__ */
#ifndef __NO_builtin_choose_expr
#define __PRIVATE_memset_4(dst, word, word_count, word_size)                                   \
	__builtin_choose_expr((word_size) == 1,                                                    \
	                      (void *)__libc_memset(dst, (int)(__UINT8_TYPE__)(word), word_count), \
	__builtin_choose_expr((word_size) == 2,                                                    \
	                      (void *)__libc_memsetw(dst, (__UINT16_TYPE__)(word), word_count),    \
	                      (void *)__libc_memsetl(dst, (__UINT32_TYPE__)(word), word_count)))
#else /* !__NO_builtin_choose_expr */
#define __PRIVATE_memset_4(dst, word, word_count, word_size)               \
	((word_size) == 1                                                      \
	 ? (void *)__libc_memset(dst, (int)(__UINT8_TYPE__)(word), word_count) \
	 : (word_size) == 2                                                    \
	   ? (void *)__libc_memsetw(dst, (__UINT16_TYPE__)(word), word_count)  \
	   : (void *)__libc_memsetl(dst, (__UINT32_TYPE__)(word), word_count))
#endif /* __NO_builtin_choose_expr */
#endif /* !__UINT64_TYPE__ */
#endif /* !__USE_KOS */
#undef memset
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define memset(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memset_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define memset(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memset_, (args))(args)
#endif /* ... */
#endif /* __HYBRID_PP_VA_OVERLOAD */
#endif /* __USE_STRING_OVERLOADS */

#if !defined(__cplusplus) && defined(__USE_STRING_OVERLOADS) && defined(__HYBRID_PP_VA_OVERLOAD)
/* In C, we can use argument-count overload macros to implement these overloads:
 * >> int memcmp(void const *s1, void const *s2, size_t num_bytes);
 * >> int memcmp(void const *s1, void const *s2, size_t elem_count, size_t elem_size);
 * >> void *memcpy(void *dst, void const *src, size_t num_bytes);
 * >> void *memcpy(void *dst, void const *src, size_t elem_count, size_t elem_size);
 * >> void *memmove(void *dst, void const *src, size_t num_bytes);
 * >> void *memmove(void *dst, void const *src, size_t elem_count, size_t elem_size);
 * >> void *memmoveup(void *dst, void const *src, size_t num_bytes);
 * >> void *memmoveup(void *dst, void const *src, size_t elem_count, size_t elem_size);
 * >> void *memmovedown(void *dst, void const *src, size_t num_bytes);
 * >> void *memmovedown(void *dst, void const *src, size_t elem_count, size_t elem_size);
 * >> void *mempcpy(void *dst, void const *src, size_t num_bytes);
 * >> void *mempcpy(void *dst, void const *src, size_t elem_count, size_t elem_size);
 * >> void *mempmove(void *dst, void const *src, size_t num_bytes);
 * >> void *mempmove(void *dst, void const *src, size_t elem_count, size_t elem_size);
 * >> void *mempmoveup(void *dst, void const *src, size_t num_bytes);
 * >> void *mempmoveup(void *dst, void const *src, size_t elem_count, size_t elem_size);
 * >> void *mempmovedown(void *dst, void const *src, size_t num_bytes);
 * >> void *mempmovedown(void *dst, void const *src, size_t elem_count, size_t elem_size);
 * >> int bcmp(void const *s1, void const *s2, size_t num_bytes);
 * >> int bcmp(void const *s1, void const *s2, size_t elem_count, size_t elem_size);
 * >> void bzero(void *dst, size_t num_bytes);
 * >> void bzero(void *dst, size_t elem_count, size_t elem_size); */
#ifdef __USE_MISC
#undef __PRIVATE_bcmp_3
#undef __PRIVATE_bcmp_4
#undef __PRIVATE_bzero_2
#undef __PRIVATE_bzero_3
#ifdef __USE_KOS
#define __PRIVATE_bcmp_4  bcmpc
#define __PRIVATE_bzero_3 bzeroc
#else /* __USE_KOS */
__SYSDECL_END
#include <libc/string.h>
__SYSDECL_BEGIN
#define __PRIVATE_bcmp_4  __libc_bcmpc
#define __PRIVATE_bzero_3 __libc_bzeroc
#endif /* !__USE_KOS */
#define __PRIVATE_bcmp_3  (bcmp)
#define __PRIVATE_bzero_2 (bzero)
#undef bcmp
#undef bzero
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define bcmp(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_bcmp_, (__VA_ARGS__))(__VA_ARGS__)
#define bzero(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_bzero_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define bcmp(args...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_bcmp_, (args))(args)
#define bzero(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_bzero_, (args))(args)
#endif /* ... */
#endif /* __USE_MISC */
#ifdef __USE_KOS
#define __PRIVATE_memcmp_4  memcmpc
#define __PRIVATE_memcpy_4  memcpyc
#define __PRIVATE_memmove_4 memmovec
#ifdef __USE_GNU
#define __PRIVATE_mempcpy_4 mempcpyc
#endif /* __USE_GNU */
#else /* __USE_KOS */
__SYSDECL_END
#include <libc/string.h>
__SYSDECL_BEGIN
#define __PRIVATE_memcmp_4  __libc_memcmpc
#define __PRIVATE_memcpy_4  __libc_memcpyc
#define __PRIVATE_memmove_4 __libc_memmovec
#ifdef __USE_GNU
#define __PRIVATE_mempcpy_4 __libc_mempcpyc
#endif /* __USE_GNU */
#endif /* !__USE_KOS */
#define __PRIVATE_memcmp_3  (memcmp)
#define __PRIVATE_memcpy_3  (memcpy)
#define __PRIVATE_memmove_3 (memmove)
#undef memcmp
#undef memcpy
#undef memmove
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define memcmp(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memcmp_, (__VA_ARGS__))(__VA_ARGS__)
#define memcpy(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memcpy_, (__VA_ARGS__))(__VA_ARGS__)
#define memmove(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmove_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define memcmp(args...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memcmp_, (args))(args)
#define memcpy(args...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memcpy_, (args))(args)
#define memmove(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmove_, (args))(args)
#endif /* ... */
#ifdef __USE_GNU
#define __PRIVATE_mempcpy_3 (mempcpy)
#undef mempcpy
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define mempcpy(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempcpy_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define mempcpy(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempcpy_, (args))(args)
#endif /* ... */
#endif /* __USE_GNU */
#ifdef __USE_KOS
#define __PRIVATE_mempmove_4     mempmovec
#define __PRIVATE_mempmoveup_4   mempmoveupc
#define __PRIVATE_mempmovedown_4 mempmovedownc
#define __PRIVATE_memmoveup_4    memmoveupc
#define __PRIVATE_memmovedown_4  memmovedownc
#define __PRIVATE_mempmove_3     (mempmove)
#define __PRIVATE_mempmoveup_3   (mempmoveup)
#define __PRIVATE_mempmovedown_3 (mempmovedown)
#define __PRIVATE_memmoveup_3    (memmoveup)
#define __PRIVATE_memmovedown_3  (memmovedown)
#undef mempmove
#undef mempmoveup
#undef mempmovedown
#undef memmoveup
#undef memmovedown
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define mempmove(...)     __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmove_, (__VA_ARGS__))(__VA_ARGS__)
#define mempmoveup(...)   __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmoveup_, (__VA_ARGS__))(__VA_ARGS__)
#define mempmovedown(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmovedown_, (__VA_ARGS__))(__VA_ARGS__)
#define memmoveup(...)    __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmoveup_, (__VA_ARGS__))(__VA_ARGS__)
#define memmovedown(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmovedown_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define mempmove(args...)     __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmove_, (args))(args)
#define mempmoveup(args...)   __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmoveup_, (args))(args)
#define mempmovedown(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmovedown_, (args))(args)
#define memmoveup(args...)    __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmoveup_, (args))(args)
#define memmovedown(args...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmovedown_, (args))(args)
#endif /* ... */
#endif /* __USE_KOS */
#endif /* !__cplusplus && __USE_STRING_OVERLOADS && __HYBRID_PP_VA_OVERLOAD */


#if defined(__USE_BSD) || defined(__USE_KOS)
#ifndef __strnstr_defined
#define __strnstr_defined
#ifdef __CRT_HAVE_strnstr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strnstr(3)
 * Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If   found,   return  a   pointer   to  its   location   within  `str',   else   return  `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnstr,(char *__haystack, char const *__needle, __SIZE_TYPE__ __haystack_maxlen),strnstr,(__haystack,__needle,__haystack_maxlen))
/* >> strnstr(3)
 * Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If   found,   return  a   pointer   to  its   location   within  `str',   else   return  `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strnstr,(char const *__haystack, char const *__needle, __SIZE_TYPE__ __haystack_maxlen),strnstr,(__haystack,__needle,__haystack_maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strnstr(3)
 * Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If   found,   return  a   pointer   to  its   location   within  `str',   else   return  `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INS(1, 3) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnstr,(char const *__haystack, char const *__needle, __SIZE_TYPE__ __haystack_maxlen),(__haystack,__needle,__haystack_maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strnstr */
#include <libc/local/string/strnstr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strnstr(3)
 * Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If   found,   return  a   pointer   to  its   location   within  `str',   else   return  `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnstr)(char *__haystack, char const *__needle, __SIZE_TYPE__ __haystack_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnstr))(__haystack, __needle, __haystack_maxlen); }
/* >> strnstr(3)
 * Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If   found,   return  a   pointer   to  its   location   within  `str',   else   return  `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strnstr)(char const *__haystack, char const *__needle, __SIZE_TYPE__ __haystack_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnstr))(__haystack, __needle, __haystack_maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strnstr(3)
 * Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If   found,   return  a   pointer   to  its   location   within  `str',   else   return  `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnstr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnstr)(char const *__haystack, char const *__needle, __SIZE_TYPE__ __haystack_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnstr))(__haystack, __needle, __haystack_maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strnstr */
#endif /* !__strnstr_defined */
#endif /* __USE_BSD || __USE_KOS */


#ifdef __USE_BSD
#ifndef __strmode_defined
#define __strmode_defined
#ifdef __CRT_HAVE_strmode
/* Generate  a file mode representation similar to what's printed by `ls -l'
 * The representation is written to `p', and `mode' is the value as returned
 * by `stat(2)' in `struct stat::st_mode'
 * The format written is:
 *    p[0]  = <mode & S_IFMT>: { S_IFDIR: 'd', S_IFCHR: 'c', S_IFBLK:  'b',
 *                               S_IFREG: '-', S_IFLNK: 'l', S_IFSOCK: 's',
 *                               S_IFIFO: 'p' }, else: '?';
 *    p[1]  = mode & S_IRUSR ? 'r' : '-';
 *    p[2]  = mode & S_IWUSR ? 'w' : '-';
 *    p[3]  = <mode & S_IXUSR | S_ISUID>: { 0: '-', S_IXUSR: 'x', S_ISUID: 'S',
 *                                          S_IXUSR | S_ISUID: 's' };
 *    p[4] = mode & S_IRGRP ? 'r' : '-';
 *    p[5] = mode & S_IWGRP ? 'w' : '-';
 *    p[6]  = <mode & S_IXGRP | S_ISGID>: { 0: '-', S_IXGRP: 'x', S_ISGID: 'S',
 *                                          S_IXGRP | S_ISGID: 's' };
 *    p[7] = mode & S_IROTH ? 'r' : '-';
 *    p[8] = mode & S_IWOTH ? 'w' : '-';
 *    p[9]  = <mode & S_IXOTH | S_ISVTX>: { 0: '-', S_IXOTH: 'x', S_ISVTX: 'T',
 *                                          S_IXOTH | S_ISVTX: 't' };
 *    p[10] = ' '; // '+', if "alternate or additional access control
 *                 //          methods associated with the inode"
 *    p[11] = '\0'; */
__CDECLARE_VOID(__ATTR_OUT(2),__NOTHROW_NCX,strmode,(__mode_t __mode, char __p[12]),(__mode,__p))
#else /* __CRT_HAVE_strmode */
#include <libc/local/string/strmode.h>
/* Generate  a file mode representation similar to what's printed by `ls -l'
 * The representation is written to `p', and `mode' is the value as returned
 * by `stat(2)' in `struct stat::st_mode'
 * The format written is:
 *    p[0]  = <mode & S_IFMT>: { S_IFDIR: 'd', S_IFCHR: 'c', S_IFBLK:  'b',
 *                               S_IFREG: '-', S_IFLNK: 'l', S_IFSOCK: 's',
 *                               S_IFIFO: 'p' }, else: '?';
 *    p[1]  = mode & S_IRUSR ? 'r' : '-';
 *    p[2]  = mode & S_IWUSR ? 'w' : '-';
 *    p[3]  = <mode & S_IXUSR | S_ISUID>: { 0: '-', S_IXUSR: 'x', S_ISUID: 'S',
 *                                          S_IXUSR | S_ISUID: 's' };
 *    p[4] = mode & S_IRGRP ? 'r' : '-';
 *    p[5] = mode & S_IWGRP ? 'w' : '-';
 *    p[6]  = <mode & S_IXGRP | S_ISGID>: { 0: '-', S_IXGRP: 'x', S_ISGID: 'S',
 *                                          S_IXGRP | S_ISGID: 's' };
 *    p[7] = mode & S_IROTH ? 'r' : '-';
 *    p[8] = mode & S_IWOTH ? 'w' : '-';
 *    p[9]  = <mode & S_IXOTH | S_ISVTX>: { 0: '-', S_IXOTH: 'x', S_ISVTX: 'T',
 *                                          S_IXOTH | S_ISVTX: 't' };
 *    p[10] = ' '; // '+', if "alternate or additional access control
 *                 //          methods associated with the inode"
 *    p[11] = '\0'; */
__NAMESPACE_LOCAL_USING_OR_IMPL(strmode, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) void __NOTHROW_NCX(__LIBCCALL strmode)(__mode_t __mode, char __p[12]) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strmode))(__mode, __p); })
#endif /* !__CRT_HAVE_strmode */
#endif /* !__strmode_defined */
#ifdef __CRT_HAVE_timingsafe_bcmp
/* >> timingsafe_bcmp(3)
 * Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
 * @return: == 0: Memory blocks are equal.
 * @return: != 0: Memory blocks are non-equal. */
__CDECLARE(__ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3),int,__NOTHROW_NCX,timingsafe_bcmp,(void const *__s1, void const *__s2, size_t __n_bytes),(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_timingsafe_memcmp)
/* >> timingsafe_bcmp(3)
 * Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
 * @return: == 0: Memory blocks are equal.
 * @return: != 0: Memory blocks are non-equal. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3),int,__NOTHROW_NCX,timingsafe_bcmp,(void const *__s1, void const *__s2, size_t __n_bytes),timingsafe_memcmp,(__s1,__s2,__n_bytes))
#else /* ... */
#include <libc/local/string/timingsafe_memcmp.h>
/* >> timingsafe_bcmp(3)
 * Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
 * @return: == 0: Memory blocks are equal.
 * @return: != 0: Memory blocks are non-equal. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) int __NOTHROW_NCX(__LIBCCALL timingsafe_bcmp)(void const *__s1, void const *__s2, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timingsafe_memcmp))(__s1, __s2, __n_bytes); }
#endif /* !... */
#ifdef __CRT_HAVE_timingsafe_memcmp
/* >> timingsafe_memcmp(3)
 * Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
 * @return: <  0: Block `s1' should be considered less than `s2'
 * @return: == 0: Memory blocks are equal.
 * @return: >  0: Block `s1' should be considered greater than `s2' */
__CDECLARE(__ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3),int,__NOTHROW_NCX,timingsafe_memcmp,(void const *__s1, void const *__s2, size_t __n_bytes),(__s1,__s2,__n_bytes))
#else /* __CRT_HAVE_timingsafe_memcmp */
#include <libc/local/string/timingsafe_memcmp.h>
/* >> timingsafe_memcmp(3)
 * Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
 * @return: <  0: Block `s1' should be considered less than `s2'
 * @return: == 0: Memory blocks are equal.
 * @return: >  0: Block `s1' should be considered greater than `s2' */
__NAMESPACE_LOCAL_USING_OR_IMPL(timingsafe_memcmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) int __NOTHROW_NCX(__LIBCCALL timingsafe_memcmp)(void const *__s1, void const *__s2, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timingsafe_memcmp))(__s1, __s2, __n_bytes); })
#endif /* !__CRT_HAVE_timingsafe_memcmp */
#endif /* __USE_BSD */

#ifdef __USE_CYGWIN
#ifndef __strtosigno_defined
#define __strtosigno_defined
#ifdef __CRT_HAVE_strtosigno
/* >> strtosigno(3)
 * Return the signal number for a given name.
 * e.g.: `strtosigno("SIGINT") == SIGINT'
 * When `name' isn't recognized, return `0' instead. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__signo_t,__NOTHROW_NCX,strtosigno,(const char *__name),(__name))
#else /* __CRT_HAVE_strtosigno */
#include <libc/local/string/strtosigno.h>
/* >> strtosigno(3)
 * Return the signal number for a given name.
 * e.g.: `strtosigno("SIGINT") == SIGINT'
 * When `name' isn't recognized, return `0' instead. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strtosigno, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __signo_t __NOTHROW_NCX(__LIBCCALL strtosigno)(const char *__name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtosigno))(__name); })
#endif /* !__CRT_HAVE_strtosigno */
#endif /* !__strtosigno_defined */
#endif /* __USE_CYGWIN */

#ifdef __USE_NETBSD
#ifndef __explicit_memset_defined
#define __explicit_memset_defined
#ifdef __CRT_HAVE_memset
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,explicit_memset,(void *__restrict __dst, int __byte, size_t __n_bytes),memset,(__dst,__byte,__n_bytes))
#elif defined(__CRT_HAVE_explicit_memset)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,explicit_memset,(void *__restrict __dst, int __byte, size_t __n_bytes),(__dst,__byte,__n_bytes))
#else /* ... */
#include <libc/local/string/explicit_memset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(explicit_memset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL explicit_memset)(void *__restrict __dst, int __byte, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(explicit_memset))(__dst, __byte, __n_bytes); })
#endif /* !... */
#endif /* !__explicit_memset_defined */
#ifdef __CRT_HAVE_stresep
/* >> stresep(3)
 * Same as `strsep(3)', but allow the specification of an additional `escape'
 * character  that will cause  the following character  from `*stringp' to be
 * escaped, and not  be considered  as a separator,  even if  it is  included
 * within `delim'. Note that `escape'-characters (if present) are not removed
 * from  the input  string, meaning that  they will still  appear in returned
 * strings, should they have been present in the original input string. */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(1),char *,__NOTHROW_NCX,stresep,(char **__restrict __stringp, char const *__restrict __delim, int __escape),(__stringp,__delim,__escape))
#else /* __CRT_HAVE_stresep */
#include <libc/local/string/stresep.h>
/* >> stresep(3)
 * Same as `strsep(3)', but allow the specification of an additional `escape'
 * character  that will cause  the following character  from `*stringp' to be
 * escaped, and not  be considered  as a separator,  even if  it is  included
 * within `delim'. Note that `escape'-characters (if present) are not removed
 * from  the input  string, meaning that  they will still  appear in returned
 * strings, should they have been present in the original input string. */
__NAMESPACE_LOCAL_USING_OR_IMPL(stresep, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(1) char *__NOTHROW_NCX(__LIBCCALL stresep)(char **__restrict __stringp, char const *__restrict __delim, int __escape) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stresep))(__stringp, __delim, __escape); })
#endif /* !__CRT_HAVE_stresep */
#ifdef __CRT_HAVE_consttime_memequal
/* >> consttime_memequal(3)
 * Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
 * @return: == 0: Memory blocks are non-equal.
 * @return: != 0: Memory blocks are equal. */
__CDECLARE(__ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3),int,__NOTHROW_NCX,consttime_memequal,(void const *__s1, void const *__s2, size_t __n_bytes),(__s1,__s2,__n_bytes))
#else /* __CRT_HAVE_consttime_memequal */
#include <libc/local/string/consttime_memequal.h>
/* >> consttime_memequal(3)
 * Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
 * @return: == 0: Memory blocks are non-equal.
 * @return: != 0: Memory blocks are equal. */
__NAMESPACE_LOCAL_USING_OR_IMPL(consttime_memequal, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) int __NOTHROW_NCX(__LIBCCALL consttime_memequal)(void const *__s1, void const *__s2, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(consttime_memequal))(__s1, __s2, __n_bytes); })
#endif /* !__CRT_HAVE_consttime_memequal */
#endif /* __USE_NETBSD */

#ifdef __USE_SOLARIS
#ifdef __CRT_HAVE_uucopy
/* >> uucopy(2)
 * Copy `num_bytes' from `src' to `dst'. The copy is done such that  any
 * faulty memory access is handled by returning `-1' with `errno=EFAULT'
 * @return: 0 : Success
 * @return: -1: [errno=EFAULT] Faulty memory access */
__CDECLARE(__ATTR_INS(1, 3) __ATTR_OUTS(2, 3),int,__NOTHROW_NCX,uucopy,(void const *__restrict __src, void *__restrict __dst, size_t __num_bytes),(__src,__dst,__num_bytes))
#elif defined(__KOS__) && defined(__cplusplus) && defined(__CRT_HAVE_except_nesting_begin) && defined(__CRT_HAVE_except_nesting_end)
#include <libc/local/string/uucopy.h>
/* >> uucopy(2)
 * Copy `num_bytes' from `src' to `dst'. The copy is done such that  any
 * faulty memory access is handled by returning `-1' with `errno=EFAULT'
 * @return: 0 : Success
 * @return: -1: [errno=EFAULT] Faulty memory access */
__NAMESPACE_LOCAL_USING_OR_IMPL(uucopy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(1, 3) __ATTR_OUTS(2, 3) int __NOTHROW_NCX(__LIBCCALL uucopy)(void const *__restrict __src, void *__restrict __dst, size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(uucopy))(__src, __dst, __num_bytes); })
#endif /* ... */
#ifdef __CRT_HAVE_uucopystr
/* >> uucopystr(2)
 * Copy  a string `src' into `dst', but copy no more than `maxlen' characters (including trailing NUL).
 * The copy is done such that any faulty memory access is handled by returning `-1' with `errno=EFAULT'
 * @return: * : The number of copied characters (including trialing NUL; )
 * @return: -1: [errno=EFAULT]       Faulty memory access
 * @return: -1: [errno=ENAMETOOLONG] `strlen(src) >= maxlen' */
__CDECLARE(__ATTR_IN_OPT(1) __ATTR_OUT_OPT(2),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,uucopystr,(void const *__restrict __src, void *__restrict __dst, size_t __maxlen),(__src,__dst,__maxlen))
#elif defined(__KOS__) && defined(__cplusplus) && defined(__CRT_HAVE_except_nesting_begin) && defined(__CRT_HAVE_except_nesting_end)
#include <libc/local/string/uucopystr.h>
/* >> uucopystr(2)
 * Copy  a string `src' into `dst', but copy no more than `maxlen' characters (including trailing NUL).
 * The copy is done such that any faulty memory access is handled by returning `-1' with `errno=EFAULT'
 * @return: * : The number of copied characters (including trialing NUL; )
 * @return: -1: [errno=EFAULT]       Faulty memory access
 * @return: -1: [errno=ENAMETOOLONG] `strlen(src) >= maxlen' */
__NAMESPACE_LOCAL_USING_OR_IMPL(uucopystr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(1) __ATTR_OUT_OPT(2) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL uucopystr)(void const *__restrict __src, void *__restrict __dst, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(uucopystr))(__src, __dst, __maxlen); })
#endif /* ... */
#endif /* __USE_SOLARIS */

#endif /* __CC__ */

__SYSDECL_END

#if defined(__USE_DOS) && !defined(__USE_DOS_CLEAN)
#include <corecrt_wstring.h> /* Include <wchar.h> instead */
#endif /* __USE_DOS && !__USE_DOS_CLEAN */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STRING_H)
#include <parts/uchar/string.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_STRING_H */
#endif /* __USE_UTF */

#ifdef __SSP_FORTIFY_LEVEL
#include <ssp/string.h>
#endif /* __SSP_FORTIFY_LEVEL */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CSTRING
#undef _STRING_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CSTRING */
#endif /* !_STRING_H */
