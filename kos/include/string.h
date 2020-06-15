/* HASH CRC-32:0x711c0026 */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _STRING_H
#define _STRING_H 1

#ifdef _CXX_STDONLY_CSTRING
#ifdef __CXX_SYSTEM_HEADER
#undef _STRING_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "string.h" after "cstring" */
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#if defined(__std___forward_size_defined) && !defined(____forward_size_defined)
#define ____forward_size_defined 1
__NAMESPACE_STD_USING(__forward_size)
#endif /* __std___forward_size_defined && !____forward_size_defined */
__NAMESPACE_STD_USING(memcpy)
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
__NAMESPACE_STD_USING(strsignal)
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
#include <parts/errno.h>
#include <crtdefs.h>
#endif /* __USE_DOS */
#if !defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus && __USE_STRING_OVERLOADS */
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */

__SYSDECL_BEGIN

#ifdef __CC__
__NAMESPACE_STD_BEGIN
#ifndef __std_size_t_defined
#define __std_size_t_defined 1
typedef __size_t size_t;
#endif /* !__std_size_t_defined */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#if defined(__std___forward_size_defined) && !defined(____forward_size_defined)
#define ____forward_size_defined 1
__NAMESPACE_STD_USING(__forward_size)
#endif /* __std___forward_size_defined && !____forward_size_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

/* Memory functions (An optional `[b|w|l|q]' suffix is a kos extension):
 *   [std] memcmp[b|w|l|q]      - Compare memory buffers and return the difference of the first non-matching byte/word/dword/qword
 *   [std] memset[b|w|l|q]      - Fill memory with a given byte/word/dword/qword
 *   [kos] mempset[b|w|l|q]     - Same as `memset[b|w|l|q]', but return `DST+N_(BYTES|WORDS|DWORDS)', rather than `DST'
 *   [std] memcpy[b|w|l|q]      - Copy memory between non-overlapping memory blocks.
 *   [glc] mempcpy[b|w|l|q]     - Same as `memcpy[b|w|l|q]', but return `DST+N_(BYTES|WORDS|DWORDS)', rather than `DST'
 *   [std] memmove[b|w|l|q]     - Move memory between potentially overlapping memory blocks.
 *   [kos] mempmove[b|w|l|q]    - Same as `memmove[b|w|l|q]', but return `DST+N_(BYTES|WORDS|DWORDS)', rather than `DST'
 *   [kos] memmoveup[b|w|l|q]   - Same as `memmove[b|w|l|q]', but assume that `DST >= SRC'
 *   [kos] memmovedown[b|w|l|q] - Same as `memmove[b|w|l|q]', but assume that `DST <= SRC'
 *   [kos] mempmoveup[b|w|l|q]  - Same as `mempmove[b|w|l|q]', but assume that `DST >= SRC'
 *   [kos] mempmovedown[b|w|l|q]- Same as `mempmove[b|w|l|q]', but assume that `DST <= SRC'
 *   [std] memchr[b|w|l|q]      - Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found.
 *   [glc] memrchr[b|w|l|q]     - Descendingly search for `NEEDLE', starting at `HAYSTACK+N_(BYTES|WORDS|DWORDS)'. - Return `NULL' if `NEEDLE' wasn't found.
 *   [glc] rawmemchr[b|w|l|q]   - Same as `memchr[b|w|l|q]' with a search limit of `(size_t)-1/sizeof(T)'
 *   [kos] rawmemrchr[b|w|l|q]  - Same as `memrchr[b|w|l|q]' without a search limit, starting at `HAYSTACK-sizeof(T)'
 *   [kos] memend[b|w|l|q]      - Same as `memchr[b|w|l|q]', but return `HAYSTACK+N_(BYTES|WORDS|DWORDS)', rather than `NULL' if `NEEDLE' wasn't found.
 *   [kos] memrend[b|w|l|q]     - Same as `memrchr[b|w|l|q]', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found.
 *   [kos] memlen[b|w|l|q]      - Same as `memend[b|w|l|q]', but return the offset from `HAYSTACK', rather than the actual address.
 *   [kos] memrlen[b|w|l|q]     - Same as `memrend[b|w|l|q]', but return the offset from `HAYSTACK', rather than the actual address.
 *   [kos] rawmemlen[b|w|l|q]   - Same as `rawmemchr[b|w|l|q]', but return the offset from `HAYSTACK', rather than the actual address.
 *   [kos] rawmemrlen[b|w|l|q]  - Same as `rawmemrchr[b|w|l|q]', but return the offset from `HAYSTACK', rather than the actual address.
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
 *     isn't mandatory, but is still recommended. To determine if the current target
 *     architecture allows for unaligned memory access, and thereby doesn't enforce
 *     the alignment requirements of b/w/l/q string functions, you may test for the
 *     `__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS' macro from `<hybrid/host.h>'
 *
 * String functions:
 *   [std] strlen               - Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')´)
 *   [std] strnlen              - Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´)
 *   [kos] strend               - Same as `STR + strlen(STR)'
 *   [kos] strnend              - Same as `STR + strnlen(STR, MAX_CHARS)'
 *   [std] strchr               - Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found.
 *   [std] strrchr              - Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found.
 *   [kos] strnchr              - Same as `strchr', but don't exceed `MAX_CHARS' characters.
 *   [kos] strnrchr             - Same as `strrchr', but don't exceed `MAX_CHARS' characters.
 *   [glc] strchrnul            - Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found.
 *   [kos] strrchrnul           - Same as `strrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found.
 *   [kos] strnchrnul           - Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found.
 *   [kos] strnrchrnul          - Same as `strnrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found.
 *   [kos] stroff               - Same as `strchrnul', but return the offset from `STR', rather than the actual address.
 *   [kos] strroff              - Same as `strrchrnul', but return the offset from `STR', rather than the actual address.
 *   [kos] strnoff              - Same as `strnchrnul', but return the offset from `STR', rather than the actual address.
 *   [kos] strnroff             - Same as `strnrchrnul', but return the offset from `STR', rather than the actual address.
 *   [std] strcpy               - Same as `(char *)memcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char))'
 *   [std] strcat               - Same as `memcpy(strend(DST), SRC, (strlen(SRC) + 1) * sizeof(char))', but re-return `DST'
 *   [std] strncpy              - Similar to `strcpy', but always write `DSTSIZE' characters, copying from `SRC' and filling the rest with padding ZEROes.
 *   [std] strncat              - Copy `strnlen(SRC, MAX_CHARS)' characters to `strend(DST)', then (try to) append a NUL-character thereafter. - Return `DST'.
 *   [glc] stpcpy               - Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´
 *   [glc] stpncpy              - Copy `strnlen(SRC, MAX_CHARS)' characters to `DST', then (try to) append a NUL-character thereafter. - Return `DST'.
 *
 * Annotations:
 *   [std]: The function is defined by the C standard
 *           - `memcpy()'
 *   [glc]: The function is also provided by GLibc, and is likely
 *          apart of some posix/unix standard
 *           - `rawmemchr()'
 *   [kos]: The function is kos-specific, or apart of a standard other than
 *          the C standard, or one of the standards implemented by GLibc.
 *           - `strend()' - Not apart of any standard (that I know of) -> KOS-specific
 *           - `strlwr()' - Can also be found in DOS -> DOS-specific, but also provided by KOS
 */
__NAMESPACE_STD_BEGIN
#ifdef __fast_memcpy_defined
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__NAMESPACE_FAST_USING_OR_IMPL(memcpy, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memcpy)(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))(__dst, __src, __n_bytes); })
#elif defined(__CRT_HAVE_memcpy)
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memcpy,(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes),(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_STD_END
#include <local/string/memcpy.h>
__NAMESPACE_STD_BEGIN
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpy, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memcpy)(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy))(__dst, __src, __n_bytes); })
#endif /* !... */
#ifdef __fast_memmove_defined
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__NAMESPACE_FAST_USING_OR_IMPL(memmove, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmove)(void *__dst, void const *__src, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmove))(__dst, __src, __n_bytes); })
#elif defined(__CRT_HAVE_memmove)
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmove,(void *__dst, void const *__src, size_t __n_bytes),(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_STD_END
#include <local/string/memmove.h>
__NAMESPACE_STD_BEGIN
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmove, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmove)(void *__dst, void const *__src, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmove))(__dst, __src, __n_bytes); })
#endif /* !... */
#ifdef __fast_memset_defined
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__NAMESPACE_FAST_USING_OR_IMPL(memset, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memset)(void *__restrict __dst, int __byte, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))(__dst, __byte, __n_bytes); })
#elif defined(__CRT_HAVE_memset)
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memset,(void *__restrict __dst, int __byte, size_t __n_bytes),(__dst,__byte,__n_bytes))
#else /* ... */
__NAMESPACE_STD_END
#include <local/string/memset.h>
__NAMESPACE_STD_BEGIN
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memset, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memset)(void *__restrict __dst, int __byte, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memset))(__dst, __byte, __n_bytes); })
#endif /* !... */
#ifdef __fast_memcmp_defined
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__NAMESPACE_FAST_USING_OR_IMPL(memcmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memcmp)(void const *__s1, void const *__s2, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __n_bytes); })
#elif defined(__CRT_HAVE_memcmp)
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcmp,(void const *__s1, void const *__s2, size_t __n_bytes),(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_bcmp)
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcmp,(void const *__s1, void const *__s2, size_t __n_bytes),bcmp,(__s1,__s2,__n_bytes))
#else /* ... */
__NAMESPACE_STD_END
#include <local/string/memcmp.h>
__NAMESPACE_STD_BEGIN
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memcmp)(void const *__s1, void const *__s2, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp))(__s1, __s2, __n_bytes); })
#endif /* !... */
#ifdef __fast_memchr_defined
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __cplusplus
__NAMESPACE_FAST_USING(memchr)
#else /* __cplusplus */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memchr)(void *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __needle, __n_bytes); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memchr)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __needle, __n_bytes); }
#endif /* !__cplusplus */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_FAST_USING_OR_IMPL(memchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memchr)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memchr,(void *__restrict __haystack, int __needle, size_t __n_bytes),memchr,(__haystack,__needle,__n_bytes))
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memchr,(void const *__restrict __haystack, int __needle, size_t __n_bytes),memchr,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memchr,(void const *__restrict __haystack, int __needle, size_t __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <local/string/memchr.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memchr)(void *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))(__haystack, __needle, __n_bytes); }
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memchr)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memchr)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_strlen
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,strlen,(char const *__restrict __string),(__string))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_STD_END
#include <local/string/strlen.h>
__NAMESPACE_STD_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__NAMESPACE_LOCAL_USING_OR_IMPL(strlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL strlen)(char const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlen))(__string); })
#endif /* !__CRT_HAVE_strlen */
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strchr,(char *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strchr,(char const *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strchr,(char const *__restrict __haystack, int __needle),{ return __builtin_strchr(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_strchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strchr,(char *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strchr,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strchr,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <local/string/strchr.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strchr)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr))(__haystack, __needle); }
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strchr)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strchr)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if __has_builtin(__builtin_strrchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strrchr,(char *__restrict __haystack, int __needle),strrchr,{ return __builtin_strrchr(__haystack, __needle); })
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strrchr,(char const *__restrict __haystack, int __needle),strrchr,{ return __builtin_strrchr(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strrchr,(char const *__restrict __haystack, int __needle),{ return __builtin_strrchr(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_strrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strrchr,(char *__restrict __haystack, int __needle),strrchr,(__haystack,__needle))
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strrchr,(char const *__restrict __haystack, int __needle),strrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strrchr,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <local/string/strrchr.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strrchr)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchr))(__haystack, __needle); }
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strrchr)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strrchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strrchr)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcmp,(char const *__s1, char const *__s2),{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcmp,(char const *__s1, char const *__s2),(__s1,__s2))
#else /* ... */
__NAMESPACE_STD_END
#include <local/string/strcmp.h>
__NAMESPACE_STD_BEGIN
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__NAMESPACE_LOCAL_USING_OR_IMPL(strcmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcmp))(__s1, __s2); })
#endif /* !... */
#if __has_builtin(__builtin_strncmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncmp)
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmp,(char const *__s1, char const *__s2, size_t __maxlen),{ return __builtin_strncmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_strncmp)
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmp,(char const *__s1, char const *__s2, size_t __maxlen),(__s1,__s2,__maxlen))
#else /* ... */
__NAMESPACE_STD_END
#include <local/string/strncmp.h>
__NAMESPACE_STD_BEGIN
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__NAMESPACE_LOCAL_USING_OR_IMPL(strncmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncmp)(char const *__s1, char const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#if __has_builtin(__builtin_strstr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strstr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strstr,(char *__haystack, char *__needle),strstr,{ return __builtin_strstr(__haystack, __needle); })
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char const *,__NOTHROW_NCX,strstr,(char const *__haystack, char const *__needle),strstr,{ return __builtin_strstr(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strstr,(char const *__haystack, char const *__needle),{ return __builtin_strstr(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_strstr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strstr,(char *__haystack, char *__needle),strstr,(__haystack,__needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char const *,__NOTHROW_NCX,strstr,(char const *__haystack, char const *__needle),strstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strstr,(char const *__haystack, char const *__needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <local/string/strstr.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strstr)(char *__haystack, char *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strstr))(__haystack, __needle); }
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char const *__NOTHROW_NCX(__LIBCCALL strstr)(char const *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strstr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strstr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strstr)(char const *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strstr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if __has_builtin(__builtin_strcpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcpy)
__CEIDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strcpy,(char *__restrict __buf, char const *__restrict __src),{ return __builtin_strcpy(__buf, __src); })
#elif defined(__CRT_HAVE_strcpy)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strcpy,(char *__restrict __buf, char const *__restrict __src),(__buf,__src))
#else /* ... */
__NAMESPACE_STD_END
#include <local/string/strcpy.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strcpy, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strcpy)(char *__restrict __buf, char const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcpy))(__buf, __src); })
#endif /* !... */
#if __has_builtin(__builtin_strncpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncpy)
__CEIDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strncpy,(char *__restrict __buf, char const *__restrict __src, size_t __buflen),{ return __builtin_strncpy(__buf, __src, __buflen); })
#elif defined(__CRT_HAVE_strncpy)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strncpy,(char *__restrict __buf, char const *__restrict __src, size_t __buflen),(__buf,__src,__buflen))
#else /* ... */
__NAMESPACE_STD_END
#include <local/string/strncpy.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strncpy, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strncpy)(char *__restrict __buf, char const *__restrict __src, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncpy))(__buf, __src, __buflen); })
#endif /* !... */
#if __has_builtin(__builtin_strcat) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcat)
__CEIDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strcat,(char *__restrict __buf, char const *__restrict __src),{ return __builtin_strcat(__buf, __src); })
#elif defined(__CRT_HAVE_strcat)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strcat,(char *__restrict __buf, char const *__restrict __src),(__buf,__src))
#else /* ... */
__NAMESPACE_STD_END
#include <local/string/strcat.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strcat, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strcat)(char *__restrict __buf, char const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcat))(__buf, __src); })
#endif /* !... */
#if __has_builtin(__builtin_strncat) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncat)
__CEIDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strncat,(char *__restrict __buf, char const *__restrict __src, size_t __buflen),{ return __builtin_strncat(__buf, __src, __buflen); })
#elif defined(__CRT_HAVE_strncat)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strncat,(char *__restrict __buf, char const *__restrict __src, size_t __buflen),(__buf,__src,__buflen))
#else /* ... */
__NAMESPACE_STD_END
#include <local/string/strncat.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strncat, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strncat)(char *__restrict __buf, char const *__restrict __src, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncat))(__buf, __src, __buflen); })
#endif /* !... */
#if __has_builtin(__builtin_strcspn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcspn)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,strcspn,(char const *__haystack, char const *__reject),{ return __builtin_strcspn(__haystack, __reject); })
#elif defined(__CRT_HAVE_strcspn)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,strcspn,(char const *__haystack, char const *__reject),(__haystack,__reject))
#else /* ... */
__NAMESPACE_STD_END
#include <local/string/strcspn.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strcspn, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL strcspn)(char const *__haystack, char const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcspn))(__haystack, __reject); })
#endif /* !... */
#if __has_builtin(__builtin_strspn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strspn)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,strspn,(char const *__haystack, char const *__accept),{ return __builtin_strspn(__haystack, __accept); })
#elif defined(__CRT_HAVE_strspn)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,strspn,(char const *__haystack, char const *__accept),(__haystack,__accept))
#else /* ... */
__NAMESPACE_STD_END
#include <local/string/strspn.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strspn, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL strspn)(char const *__haystack, char const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strspn))(__haystack, __accept); })
#endif /* !... */
#if __has_builtin(__builtin_strpbrk) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strpbrk)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strpbrk,(char *__haystack, char const *__accept),strpbrk,{ return __builtin_strpbrk(__haystack, __accept); })
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char const *,__NOTHROW_NCX,strpbrk,(char const *__haystack, char const *__accept),strpbrk,{ return __builtin_strpbrk(__haystack, __accept); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strpbrk,(char const *__haystack, char const *__accept),{ return __builtin_strpbrk(__haystack, __accept); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_strpbrk)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strpbrk,(char *__haystack, char const *__accept),strpbrk,(__haystack,__accept))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char const *,__NOTHROW_NCX,strpbrk,(char const *__haystack, char const *__accept),strpbrk,(__haystack,__accept))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strpbrk,(char const *__haystack, char const *__accept),(__haystack,__accept))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <local/string/strpbrk.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strpbrk)(char *__haystack, char const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strpbrk))(__haystack, __accept); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char const *__NOTHROW_NCX(__LIBCCALL strpbrk)(char const *__haystack, char const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strpbrk))(__haystack, __accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_LOCAL_USING_OR_IMPL(strpbrk, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strpbrk)(char const *__haystack, char const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strpbrk))(__haystack, __accept); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_strtok
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,strtok,(char *__string, char const *__delim),(__string,__delim))
#else /* __CRT_HAVE_strtok */
__NAMESPACE_STD_END
#include <local/string/strtok.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtok, __FORCELOCAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL strtok)(char *__string, char const *__delim) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtok))(__string, __delim); })
#endif /* !__CRT_HAVE_strtok */
#ifdef __CRT_HAVE_strcoll
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcoll,(char const *__s1, char const *__s2),(__s1,__s2))
#else /* __CRT_HAVE_strcoll */
__NAMESPACE_STD_END
#include <local/string/strcoll.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strcoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcoll)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcoll))(__s1, __s2); })
#endif /* !__CRT_HAVE_strcoll */
#ifdef __CRT_HAVE_strxfrm
__CDECLARE(__ATTR_NONNULL((2)),size_t,__NOTHROW_NCX,strxfrm,(char *__dst, char const *__restrict __src, size_t __maxlen),(__dst,__src,__maxlen))
#else /* __CRT_HAVE_strxfrm */
__NAMESPACE_STD_END
#include <local/string/strxfrm.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strxfrm, __FORCELOCAL __ATTR_NONNULL((2)) size_t __NOTHROW_NCX(__LIBCCALL strxfrm)(char *__dst, char const *__restrict __src, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strxfrm))(__dst, __src, __maxlen); })
#endif /* !__CRT_HAVE_strxfrm */
#ifdef __CRT_HAVE_strerror
__CDECLARE(__ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,strerror,(int __errnum),(__errnum))
#else /* __CRT_HAVE_strerror */
__NAMESPACE_STD_END
#include <local/string/strerror.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strerror, __FORCELOCAL __ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL strerror)(int __errnum) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strerror))(__errnum); })
#endif /* !__CRT_HAVE_strerror */
#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
extern "C++" {
#ifdef __CRT_HAVE_memcpyc
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memcpyc */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <local/string/memcpyc.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memcpy)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyc))(__dst, __src, __elem_count, __elem_size); }
#endif /* !__CRT_HAVE_memcpyc */
#ifdef __CRT_HAVE_memmovec
/* Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmove,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmovec,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memmovec */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <local/string/memmovec.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmove)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovec))(__dst, __src, __elem_count, __elem_size); }
#endif /* !__CRT_HAVE_memmovec */
} /* extern "C++" */
#endif /* __cplusplus && __USE_STRING_OVERLOADS */
#ifdef __CRT_HAVE_strsignal
__CDECLARE(__ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,strsignal,(int __signo),(__signo))
#else /* __CRT_HAVE_strsignal */
__NAMESPACE_STD_END
#include <local/string/strsignal.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strsignal, __FORCELOCAL __ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL strsignal)(int __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strsignal))(__signo); })
#endif /* !__CRT_HAVE_strsignal */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(memcpy)
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
#if __has_builtin(__builtin_strnlen) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strnlen)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,strnlen,(char const *__restrict __string, __SIZE_TYPE__ __maxlen),{ return __builtin_strnlen(__string, __maxlen); })
#elif defined(__CRT_HAVE_strnlen)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,strnlen,(char const *__restrict __string, __SIZE_TYPE__ __maxlen),(__string,__maxlen))
#else /* ... */
#include <local/string/strnlen.h>
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strnlen)(char const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnlen))(__string, __maxlen); })
#endif /* !... */
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#ifdef __USE_XOPEN2K8
#if __has_builtin(__builtin_stpcpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpcpy)
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__CEIDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,stpcpy,(char *__restrict __buf, char const *__restrict __src),{ return __builtin_stpcpy(__buf, __src); })
#elif defined(__CRT_HAVE_stpcpy)
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,stpcpy,(char *__restrict __buf, char const *__restrict __src),(__buf,__src))
#elif defined(__CRT_HAVE___stpcpy)
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,stpcpy,(char *__restrict __buf, char const *__restrict __src),__stpcpy,(__buf,__src))
#else /* ... */
#include <local/string/stpcpy.h>
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__NAMESPACE_LOCAL_USING_OR_IMPL(stpcpy, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL stpcpy)(char *__restrict __buf, char const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stpcpy))(__buf, __src); })
#endif /* !... */
#if __has_builtin(__builtin_stpncpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpncpy)
__CEIDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,stpncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),{ return __builtin_stpncpy(__buf, __src, __buflen); })
#elif defined(__CRT_HAVE_stpncpy)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,stpncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#elif defined(__CRT_HAVE___stpncpy)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,stpncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),__stpncpy,(__buf,__src,__buflen))
#else /* ... */
#include <local/string/stpncpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(stpncpy, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL stpncpy)(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stpncpy))(__buf, __src, __buflen); })
#endif /* !... */
#if __has_builtin(__builtin_stpcpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpcpy)
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__stpcpy,(char *__restrict __buf, char const *__restrict __src),stpcpy,{ return __builtin_stpcpy(__buf, __src); })
#elif defined(__CRT_HAVE_stpcpy)
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__stpcpy,(char *__restrict __buf, char const *__restrict __src),stpcpy,(__buf,__src))
#elif defined(__CRT_HAVE___stpcpy)
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__stpcpy,(char *__restrict __buf, char const *__restrict __src),(__buf,__src))
#else /* ... */
#include <local/string/stpcpy.h>
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __stpcpy)(char *__restrict __buf, char const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stpcpy))(__buf, __src); }
#endif /* !... */
#if __has_builtin(__builtin_stpncpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpncpy)
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__stpncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),stpncpy,{ return __builtin_stpncpy(__buf, __src, __buflen); })
#elif defined(__CRT_HAVE_stpncpy)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__stpncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),stpncpy,(__buf,__src,__buflen))
#elif defined(__CRT_HAVE___stpncpy)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__stpncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#else /* ... */
#include <local/string/stpncpy.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __stpncpy)(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stpncpy))(__buf, __src, __buflen); }
#endif /* !... */
#ifdef __CRT_HAVE_strcoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcoll_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__strcoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcoll_l,(char const *__s1, char const *__s2, __locale_t __locale),_strcoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___strcoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcoll_l,(char const *__s1, char const *__s2, __locale_t __locale),__strcoll_l,(__s1,__s2,__locale))
#else /* ... */
#include <local/string/strcoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcoll_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcoll_l))(__s1, __s2, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strxfrm_l
__CDECLARE(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,strxfrm_l,(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE__strxfrm_l)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,strxfrm_l,(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE___strxfrm_l)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,strxfrm_l,(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),__strxfrm_l,(__dst,__src,__maxlen,__locale))
#else /* ... */
#include <local/string/strxfrm_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strxfrm_l, __FORCELOCAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strxfrm_l)(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strxfrm_l))(__dst, __src, __maxlen, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strerror_l
__CDECLARE(__ATTR_COLD __ATTR_WUNUSED,char *,__NOTHROW_NCX,strerror_l,(int __errnum, __locale_t __locale),(__errnum,__locale))
#else /* __CRT_HAVE_strerror_l */
#include <local/string/strerror_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strerror_l, __FORCELOCAL __ATTR_COLD __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL strerror_l)(int __errnum, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strerror_l))(__errnum, __locale); })
#endif /* !__CRT_HAVE_strerror_l */
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(strsignal)
#endif /* !__CXX_SYSTEM_HEADER */
#if __has_builtin(__builtin_strndup) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strndup)
__CEIDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strndup,(char const *__restrict __string, __SIZE_TYPE__ __max_chars),{ return __builtin_strndup(__string, __max_chars); })
#elif defined(__CRT_HAVE_strndup)
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strndup,(char const *__restrict __string, __SIZE_TYPE__ __max_chars),(__string,__max_chars))
#elif defined(__CRT_HAVE___strndup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strndup,(char const *__restrict __string, __SIZE_TYPE__ __max_chars),__strndup,(__string,__max_chars))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <local/string/strndup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strndup, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strndup)(char const *__restrict __string, __SIZE_TYPE__ __max_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strndup))(__string, __max_chars); })
#endif /* ... */
#endif /* __USE_XOPEN2K8 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#if __has_builtin(__builtin_strdup) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strdup)
__CEIDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strdup,(char const *__restrict __string),{ return __builtin_strdup(__string); })
#elif defined(__CRT_HAVE_strdup)
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strdup,(char const *__restrict __string),(__string))
#elif defined(__CRT_HAVE__strdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strdup,(char const *__restrict __string),_strdup,(__string))
#elif defined(__CRT_HAVE___strdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strdup,(char const *__restrict __string),__strdup,(__string))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <local/string/strdup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strdup, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strdup)(char const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strdup))(__string); })
#endif /* ... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 || __USE_DOS */

#ifdef __USE_POSIX
#ifdef __CRT_HAVE_strtok_r
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((2, 3)),char *,__NOTHROW_NCX,strtok_r,(char *__string, char const *__delim, char **__restrict __save_ptr),(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_strtok_s)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((2, 3)),char *,__NOTHROW_NCX,strtok_r,(char *__string, char const *__delim, char **__restrict __save_ptr),strtok_s,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE___strtok_r)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((2, 3)),char *,__NOTHROW_NCX,strtok_r,(char *__string, char const *__delim, char **__restrict __save_ptr),__strtok_r,(__string,__delim,__save_ptr))
#else /* ... */
#include <local/string/strtok_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtok_r, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((2, 3)) char *__NOTHROW_NCX(__LIBCCALL strtok_r)(char *__string, char const *__delim, char **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtok_r))(__string, __delim, __save_ptr); })
#endif /* !... */
#endif /* __USE_POSIX */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_memrchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrchr,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrchr,(__haystack,__needle,__n_bytes))
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memrchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrchr,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrchr */
#include <local/string/memrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrchr)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))(__haystack, __needle, __n_bytes); }
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memrchr)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrchr)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrchr */
#ifdef __CRT_HAVE_rawmemchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchr' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemchr,(void *__restrict __haystack, int __needle),rawmemchr,(__haystack,__needle))
/* Same as `memchr' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,rawmemchr,(void const *__restrict __haystack, int __needle),rawmemchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchr' with a search limit of `(size_t)-1' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemchr,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE___rawmemchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchr' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemchr,(void *__restrict __haystack, int __needle),__rawmemchr,(__haystack,__needle))
/* Same as `memchr' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,rawmemchr,(void const *__restrict __haystack, int __needle),__rawmemchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchr' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemchr,(void const *__restrict __haystack, int __needle),__rawmemchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/rawmemchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchr' with a search limit of `(size_t)-1' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemchr)(void *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchr))(__haystack, __needle); }
/* Same as `memchr' with a search limit of `(size_t)-1' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL rawmemchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchr' with a search limit of `(size_t)-1' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemchr, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_strchrnul
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strchrnul,(char *__restrict __haystack, int __needle),strchrnul,(__haystack,__needle))
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strchrnul,(char const *__restrict __haystack, int __needle),strchrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strchrnul,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strchrnul */
#include <local/string/strchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strchrnul)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchrnul))(__haystack, __needle); }
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strchrnul)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strchrnul, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strchrnul)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchrnul))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strchrnul */
#ifndef __basename_defined
#define __basename_defined 1
#ifdef __CRT_HAVE_basename
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,basename,(char *__filename),basename,(__filename))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char const *,__NOTHROW_NCX,basename,(char const *__filename),basename,(__filename))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,basename,(char const *__filename),(__filename))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_basename */
#include <local/string/basename.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL basename)(char *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(basename))(__filename); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL basename)(char const *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(basename))(__filename); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_LOCAL_USING_OR_IMPL(basename, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL basename)(char const *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(basename))(__filename); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_basename */
#endif /* !__basename_defined */
#ifdef __CRT_HAVE_strcasestr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strcasestr,(char *__haystack, char const *__needle),strcasestr,(__haystack,__needle))
/* Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char const *,__NOTHROW_NCX,strcasestr,(char const *__haystack, char const *__needle),strcasestr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `strstr', but ignore casing */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strcasestr,(char const *__haystack, char const *__needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE___strcasestr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strcasestr,(char *__haystack, char const *__needle),__strcasestr,(__haystack,__needle))
/* Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char const *,__NOTHROW_NCX,strcasestr,(char const *__haystack, char const *__needle),__strcasestr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strcasestr,(char const *__haystack, char const *__needle),__strcasestr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/strcasestr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strcasestr)(char *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasestr))(__haystack, __needle); }
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char const *__NOTHROW_NCX(__LIBCCALL strcasestr)(char const *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasestr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `strstr', but ignore casing */
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasestr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strcasestr)(char const *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasestr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#if defined(__CRT_HAVE_memmem0) && defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memmem,(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memmem0,(__haystack,__haystacklen,__needle,__needlelen))
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memmem0,(__haystack,__haystacklen,__needle,__needlelen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memmem0,(__haystack,__haystacklen,__needle,__needlelen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memmem) && !defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memmem,(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memmem,(__haystack,__haystacklen,__needle,__needlelen))
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memmem,(__haystack,__haystacklen,__needle,__needlelen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),(__haystack,__haystacklen,__needle,__needlelen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/memmem.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memmem)(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmem))(__haystack, __haystacklen, __needle, __needlelen); }
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) void const *__NOTHROW_NCX(__LIBCCALL memmem)(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmem))(__haystack, __haystacklen, __needle, __needlelen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmem, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memmem)(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmem))(__haystack, __haystacklen, __needle, __needlelen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_strverscmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strverscmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE___strverscmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strverscmp,(char const *__s1, char const *__s2),__strverscmp,(__s1,__s2))
#else /* ... */
#include <local/string/strverscmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strverscmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strverscmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strverscmp))(__s1, __s2); })
#endif /* !... */
#ifdef __CRT_HAVE_mempcpy
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),(__dst,__src,__n_bytes))
#else /* ... */
#include <local/string/mempcpy.h>
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempcpy)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpy))(__dst, __src, __n_bytes); }
#endif /* !... */
#ifndef __mempcpy_defined
#define __mempcpy_defined 1
#ifdef __fast_mempcpy_defined
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempcpy, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempcpy)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))(__dst, __src, __n_bytes); })
#elif defined(__CRT_HAVE_mempcpy)
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,(__dst,__src,__n_bytes))
#else /* ... */
#include <local/string/mempcpy.h>
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempcpy, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempcpy)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpy))(__dst, __src, __n_bytes); })
#endif /* !... */
#endif /* !__mempcpy_defined */
#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
extern "C++" {
#ifdef __CRT_HAVE_mempcpyc
/* Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_mempcpyc */
} /* extern "C++" */
#include <local/string/mempcpyc.h>
extern "C++" {
/* Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempcpy)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyc))(__dst, __src, __elem_count, __elem_size); }
#endif /* !__CRT_HAVE_mempcpyc */
} /* extern "C++" */
#endif /* __cplusplus && __USE_STRING_OVERLOADS */
#ifdef __CRT_HAVE_strfry
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strfry,(char *__restrict __string),(__string))
#else /* __CRT_HAVE_strfry */
#include <local/string/strfry.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strfry, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strfry)(char *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strfry))(__string); })
#endif /* !__CRT_HAVE_strfry */
#ifdef __CRT_HAVE_memfrob
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memfrob,(void *__buf, __SIZE_TYPE__ __num_bytes),(__buf,__num_bytes))
#else /* __CRT_HAVE_memfrob */
#include <local/string/memfrob.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memfrob, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memfrob)(void *__buf, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memfrob))(__buf, __num_bytes); })
#endif /* !__CRT_HAVE_memfrob */
#ifndef __strcasecmp_l_defined
#define __strcasecmp_l_defined 1
#ifdef __CRT_HAVE_strcasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__stricmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),_stricmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___strcasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),__strcasecmp_l,(__s1,__s2,__locale))
#else /* ... */
#include <local/string/strcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcasecmp_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp_l))(__s1, __s2, __locale); })
#endif /* !... */
#endif /* !__strcasecmp_l_defined */
#ifndef __strncasecmp_l_defined
#define __strncasecmp_l_defined 1
#ifdef __CRT_HAVE_strncasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncmpi_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strncmpi_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___strncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <local/string/strncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncasecmp_l)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#endif /* !__strncasecmp_l_defined */
#endif /* __USE_GNU */

#ifdef __USE_XOPEN2K
#ifdef __USE_GNU
#ifdef __CRT_HAVE_strerror_r
__CDECLARE(__ATTR_COLD __ATTR_RETNONNULL __ATTR_NONNULL((2)),char *,__NOTHROW_NCX,strerror_r,(int __errnum, char *__buf, __SIZE_TYPE__ __buflen),(__errnum,__buf,__buflen))
#elif defined(__CRT_HAVE___strerror_r)
__CREDIRECT(__ATTR_COLD __ATTR_RETNONNULL __ATTR_NONNULL((2)),char *,__NOTHROW_NCX,strerror_r,(int __errnum, char *__buf, __SIZE_TYPE__ __buflen),__strerror_r,(__errnum,__buf,__buflen))
#else /* ... */
#include <local/string/strerror_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strerror_r, __FORCELOCAL __ATTR_COLD __ATTR_RETNONNULL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL strerror_r)(int __errnum, char *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strerror_r))(__errnum, __buf, __buflen); })
#endif /* !... */
#else /* __USE_GNU */
#ifdef __CRT_HAVE___xpg_strerror_r
__CREDIRECT(__ATTR_COLD __ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,strerror_r,(int __errnum, char *__buf, __SIZE_TYPE__ __buflen),__xpg_strerror_r,(__errnum,__buf,__buflen))
#else /* __CRT_HAVE___xpg_strerror_r */
#include <local/string/__xpg_strerror_r.h>
__FORCELOCAL __ATTR_COLD __ATTR_NONNULL((2)) __errno_t __NOTHROW_NCX(__LIBCCALL strerror_r)(int __errnum, char *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__xpg_strerror_r))(__errnum, __buf, __buflen); }
#endif /* !__CRT_HAVE___xpg_strerror_r */
#endif /* !__USE_GNU */
#endif /* __USE_XOPEN2K */

#ifdef __USE_MISC
#ifdef __CRT_HAVE_strsep
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strsep,(char **__restrict __stringp, char const *__restrict __delim),(__stringp,__delim))
#else /* __CRT_HAVE_strsep */
#include <local/string/strsep.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strsep, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strsep)(char **__restrict __stringp, char const *__restrict __delim) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strsep))(__stringp, __delim); })
#endif /* !__CRT_HAVE_strsep */
#ifndef __bcopy_defined
#define __bcopy_defined 1
#if __has_builtin(__builtin_bcopy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_bcopy)
__CEIDECLARE(__ATTR_NONNULL((1, 2)),void,__NOTHROW_NCX,bcopy,(void const *__src, void *__dst, __SIZE_TYPE__ __num_bytes),{ return __builtin_bcopy(__src, __dst, __num_bytes); })
#elif defined(__CRT_HAVE_bcopy)
__CDECLARE_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,bcopy,(void const *__src, void *__dst, __SIZE_TYPE__ __num_bytes),(__src,__dst,__num_bytes))
#else /* ... */
#include <local/strings/bcopy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bcopy, __FORCELOCAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL bcopy)(void const *__src, void *__dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bcopy))(__src, __dst, __num_bytes); })
#endif /* !... */
#endif /* !__bcopy_defined */
#ifndef __bzero_defined
#define __bzero_defined 1
#if __has_builtin(__builtin_bzero) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_bzero)
__CEIDECLARE(__ATTR_NONNULL((1)),void,__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),{ return __builtin_bzero(__dst, __num_bytes); })
#elif defined(__CRT_HAVE_bzero)
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
#include <local/strings/bzero.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bzero, __FORCELOCAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzero)(void *__restrict __dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzero))(__dst, __num_bytes); })
#endif /* !... */
#endif /* !__bzero_defined */
#ifndef __bcmp_defined
#define __bcmp_defined 1
#ifdef __CRT_HAVE_memcmp
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, size_t __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_bcmp)
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, size_t __n_bytes),(__s1,__s2,__n_bytes))
#else /* ... */
#include <local/string/memcmp.h>
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp))(__s1, __s2, __n_bytes); }
#endif /* !... */
#endif /* !__bcmp_defined */
#ifndef __index_defined
#define __index_defined 1
#if __has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_index)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRINGS_H_PROTO)
extern "C++" {
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,index,(char *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRINGS_H_PROTO */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),{ return __builtin_index(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRINGS_H_PROTO */
#elif defined(__CRT_HAVE_index)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRINGS_H_PROTO)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,index,(char *__restrict __haystack, int __needle),index,(__haystack,__needle))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),index,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRINGS_H_PROTO */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRINGS_H_PROTO */
#else /* ... */
#include <local/strings/index.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRINGS_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL index)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(index))(__haystack, __needle); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL index)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(index))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRINGS_H_PROTO */
__NAMESPACE_LOCAL_USING_OR_IMPL(index, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL index)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(index))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRINGS_H_PROTO */
#endif /* !... */
#endif /* !__index_defined */
#ifndef __rindex_defined
#define __rindex_defined 1
#if __has_builtin(__builtin_rindex) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rindex)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRINGS_H_PROTO)
extern "C++" {
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,rindex,(char *__restrict __haystack, int __needle),rindex,{ return __builtin_rindex(__haystack, __needle); })
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),rindex,{ return __builtin_rindex(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRINGS_H_PROTO */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),{ return __builtin_rindex(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRINGS_H_PROTO */
#elif defined(__CRT_HAVE_rindex)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRINGS_H_PROTO)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,rindex,(char *__restrict __haystack, int __needle),rindex,(__haystack,__needle))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),rindex,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRINGS_H_PROTO */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRINGS_H_PROTO */
#else /* ... */
#include <local/strings/rindex.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRINGS_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL rindex)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rindex))(__haystack, __needle); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL rindex)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rindex))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRINGS_H_PROTO */
__NAMESPACE_LOCAL_USING_OR_IMPL(rindex, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL rindex)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rindex))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRINGS_H_PROTO */
#endif /* !... */
#endif /* !__rindex_defined */
#ifndef __strcasecmp_defined
#define __strcasecmp_defined 1
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),{ return __builtin_strcasecmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcasecmp)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE___strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),__strcasecmp,(__s1,__s2))
#else /* ... */
#include <local/string/strcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcasecmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))(__s1, __s2); })
#endif /* !... */
#endif /* !__strcasecmp_defined */
#ifndef __strncasecmp_defined
#define __strncasecmp_defined 1
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),{ return __builtin_strncasecmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_strncasecmp)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strncmpi,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncmpi,(__s1,__s2,__maxlen))
#else /* ... */
#include <local/string/strncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncasecmp)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#endif /* !__strncasecmp_defined */
#if __has_builtin(__builtin_ffs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ffs)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,ffs,(int __i),{ return __builtin_ffs(__i); })
#elif defined(__CRT_HAVE_ffs)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,ffs,(int __i),(__i))
#elif defined(__CRT_HAVE___ffs)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,ffs,(int __i),__ffs,(__i))
#else /* ... */
#include <local/string/ffs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ffs, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __STDC_INT_AS_SIZE_T __NOTHROW(__LIBCCALL ffs)(int __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ffs))(__i); })
#endif /* !... */
#ifdef __USE_KOS
#include <hybrid/__bit.h>
/* unsigned int FFS(INTEGER i):
 *     FindFirstSet
 *     Returns the index (starting at 1 for 0x01) of the first
 *     1-bit in given value, or ZERO(0) if the given value is ZERO(0).
 *     >> assert(!x ||  (x &  (1 << (ffs(x)-1))));    // FFS-bit is set
 *     >> assert(!x || !(x & ((1 << (ffs(x)-1))-1))); // Less significant bits are clear */
#define ffs(i) __hybrid_ffs(i)
#endif /* !__USE_KOS */
#ifdef __USE_GNU
#if __has_builtin(__builtin_ffsl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ffsl)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,ffsl,(long __i),{ return __builtin_ffsl(__i); })
#elif defined(__CRT_HAVE_ffsl)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,ffsl,(long __i),(__i))
#else /* ... */
#include <local/string/ffsl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ffsl, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __STDC_INT_AS_SIZE_T __NOTHROW(__LIBCCALL ffsl)(long __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ffsl))(__i); })
#endif /* !... */
#if __has_builtin(__builtin_ffsll) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ffsll)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,ffsll,(__LONGLONG __i),{ return __builtin_ffsll(__i); })
#elif defined(__CRT_HAVE_ffsll)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,ffsll,(__LONGLONG __i),(__i))
#else /* ... */
#include <local/string/ffsll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ffsll, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __STDC_INT_AS_SIZE_T __NOTHROW(__LIBCCALL ffsll)(__LONGLONG __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ffsll))(__i); })
#endif /* !... */
#endif /* __USE_GNU */
#ifdef __CRT_HAVE_strlcat
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,strlcat,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __bufsize),(__dst,__src,__bufsize))
#else /* __CRT_HAVE_strlcat */
#include <local/string/strlcat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strlcat, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strlcat)(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlcat))(__dst, __src, __bufsize); })
#endif /* !__CRT_HAVE_strlcat */
#ifdef __CRT_HAVE_strlcpy
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,strlcpy,(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __bufsize),(__dst,__src,__bufsize))
#else /* __CRT_HAVE_strlcpy */
#include <local/string/strlcpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strlcpy, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strlcpy)(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlcpy))(__dst, __src, __bufsize); })
#endif /* !__CRT_HAVE_strlcpy */
#endif /* __USE_MISC */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifdef __CRT_HAVE_memccpy
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes),(__dst,__src,__needle,__num_bytes))
#elif defined(__CRT_HAVE__memccpy)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes),_memccpy,(__dst,__src,__needle,__num_bytes))
#else /* ... */
#include <local/string/memccpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memccpy, __FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memccpy)(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memccpy))(__dst, __src, __needle, __num_bytes); })
#endif /* !... */
#endif /* __USE_MISC || __USE_XOPEN */


#if __has_builtin(__builtin_bzero) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_bzero)
__CEIREDIRECT(__ATTR_NONNULL((1)),void,__NOTHROW_NCX,__bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,{ return __builtin_bzero(__dst, __num_bytes); })
#elif defined(__CRT_HAVE_bzero)
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
#include <local/strings/bzero.h>
__FORCELOCAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL __bzero)(void *__restrict __dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzero))(__dst, __num_bytes); }
#endif /* !... */
#ifdef __CRT_HAVE_strtok_r
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((2, 3)),char *,__NOTHROW_NCX,__strtok_r,(char *__string, char const *__delim, char **__restrict __save_ptr),strtok_r,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_strtok_s)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((2, 3)),char *,__NOTHROW_NCX,__strtok_r,(char *__string, char const *__delim, char **__restrict __save_ptr),strtok_s,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE___strtok_r)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((2, 3)),char *,__NOTHROW_NCX,__strtok_r,(char *__string, char const *__delim, char **__restrict __save_ptr),(__string,__delim,__save_ptr))
#else /* ... */
#include <local/string/strtok_r.h>
__FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((2, 3)) char *__NOTHROW_NCX(__LIBCCALL __strtok_r)(char *__string, char const *__delim, char **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtok_r))(__string, __delim, __save_ptr); }
#endif /* !... */

#ifdef __USE_STRING_BWLQ
#ifdef __CRT_HAVE_memcpy
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,memcpyb,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
#include <local/string/memcpy.h>
/* Copy memory between non-overlapping memory blocks. */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyb)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy))(__dst, __src, (__SIZE_TYPE__)__n_bytes); }
#endif /* !__CRT_HAVE_memcpy */
#ifdef __CRT_HAVE_mempcpy
/* Same as `memcpyb', but return `DST + N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempcpyb,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
/* Same as `memcpyb', but return `DST + N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempcpyb,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,(__dst,__src,__n_bytes))
#else /* ... */
#include <local/string/mempcpy.h>
/* Same as `memcpyb', but return `DST + N_BYTES', rather than `DST' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyb)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpy))(__dst, __src, __n_bytes); }
#endif /* !... */
#ifdef __fast_memcpyw_defined
/* Copy memory between non-overlapping memory blocks. */
__NAMESPACE_FAST_USING_OR_IMPL(memcpyw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyw)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyw))(__dst, __src, __n_words); })
#elif defined(__CRT_HAVE_memcpyw)
/* Copy memory between non-overlapping memory blocks. */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 2)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),wmemcpy,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemcpy)
/* Copy memory between non-overlapping memory blocks. */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),DOS$wmemcpy,(__dst,__src,__n_words))
#else /* ... */
#include <local/string/memcpyw.h>
/* Copy memory between non-overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpyw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyw)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyw))(__dst, __src, __n_words); })
#endif /* !... */
#ifdef __fast_mempcpyw_defined
/* Same as `memcpyw', but return `DST + N_WORDS', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempcpyw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyw)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyw))(__dst, __src, __n_words); })
#elif defined(__CRT_HAVE_mempcpyw)
/* Same as `memcpyw', but return `DST + N_WORDS', rather than `DST' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `memcpyw', but return `DST + N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),wmempcpy,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempcpy)
/* Same as `memcpyw', but return `DST + N_WORDS', rather than `DST' */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),DOS$wmempcpy,(__dst,__src,__n_words))
#else /* ... */
#include <local/string/mempcpyw.h>
/* Same as `memcpyw', but return `DST + N_WORDS', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempcpyw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyw)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyw))(__dst, __src, __n_words); })
#endif /* !... */
#ifdef __fast_memcpyl_defined
/* Copy memory between non-overlapping memory blocks. */
__NAMESPACE_FAST_USING_OR_IMPL(memcpyl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyl)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyl))(__dst, __src, __n_dwords); })
#elif defined(__CRT_HAVE_memcpyl)
/* Copy memory between non-overlapping memory blocks. */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 4)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),wmemcpy,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemcpy) && defined(__PE__)
/* Copy memory between non-overlapping memory blocks. */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),KOS$wmemcpy,(__dst,__src,__n_dwords))
#else /* ... */
#include <local/string/memcpyl.h>
/* Copy memory between non-overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpyl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyl)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyl))(__dst, __src, __n_dwords); })
#endif /* !... */
#ifdef __fast_mempcpyl_defined
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempcpyl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyl)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyl))(__dst, __src, __n_dwords); })
#elif defined(__CRT_HAVE_mempcpyl)
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),wmempcpy,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempcpy) && defined(__PE__)
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),KOS$wmempcpy,(__dst,__src,__n_dwords))
#else /* ... */
#include <local/string/mempcpyl.h>
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempcpyl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyl)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyl))(__dst, __src, __n_dwords); })
#endif /* !... */
#ifdef __CRT_HAVE_memmove
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,memmoveb,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memmove */
#include <local/string/memmove.h>
/* Move memory between potentially overlapping memory blocks. */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveb)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmove))(__dst, __src, (__SIZE_TYPE__)__n_bytes); }
#endif /* !__CRT_HAVE_memmove */
#ifdef __CRT_HAVE_mempmove
/* Same as `memmoveb', but return `DST + N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempmoveb,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmove,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_mempmove */
#include <local/string/mempmove.h>
/* Same as `memmoveb', but return `DST + N_BYTES', rather than `DST' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveb)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmove))(__dst, __src, __n_bytes); }
#endif /* !__CRT_HAVE_mempmove */
#ifdef __fast_memmovew_defined
/* Move memory between potentially overlapping memory blocks. */
__NAMESPACE_FAST_USING_OR_IMPL(memmovew, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovew)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovew))(__dst, __src, __n_words); })
#elif defined(__CRT_HAVE_memmovew)
/* Move memory between potentially overlapping memory blocks. */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 2)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemmove)
/* Move memory between potentially overlapping memory blocks. */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmemmove,(__dst,__src,__n_words))
#else /* ... */
#include <local/string/memmovew.h>
/* Move memory between potentially overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmovew, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovew)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovew))(__dst, __src, __n_words); })
#endif /* !... */
#ifdef __fast_mempmovew_defined
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempmovew, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovew)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovew))(__dst, __src, __n_words); })
#elif defined(__CRT_HAVE_mempmovew)
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempmove) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmempmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempmove)
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmempmove,(__dst,__src,__n_words))
#else /* ... */
#include <local/string/mempmovew.h>
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmovew, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovew)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovew))(__dst, __src, __n_words); })
#endif /* !... */
#ifdef __fast_memmovel_defined
/* Move memory between potentially overlapping memory blocks. */
__NAMESPACE_FAST_USING_OR_IMPL(memmovel, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovel)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovel))(__dst, __src, __n_dwords); })
#elif defined(__CRT_HAVE_memmovel)
/* Move memory between potentially overlapping memory blocks. */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 4)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemmove) && defined(__PE__)
/* Move memory between potentially overlapping memory blocks. */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmemmove,(__dst,__src,__n_dwords))
#else /* ... */
#include <local/string/memmovel.h>
/* Move memory between potentially overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmovel, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovel)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovel))(__dst, __src, __n_dwords); })
#endif /* !... */
#ifdef __fast_mempmovel_defined
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempmovel, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovel)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovel))(__dst, __src, __n_dwords); })
#elif defined(__CRT_HAVE_mempmovel)
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempmove) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmempmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempmove) && defined(__PE__)
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmempmove,(__dst,__src,__n_dwords))
#else /* ... */
#include <local/string/mempmovel.h>
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmovel, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovel)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovel))(__dst, __src, __n_dwords); })
#endif /* !... */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_memmoveup
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_BYTES') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,memmoveupb,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmoveup,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memmoveup */
#include <local/string/memmoveup.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_BYTES') */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveupb)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveup))(__dst, __src, __n_bytes); }
#endif /* !__CRT_HAVE_memmoveup */
#ifdef __CRT_HAVE_memmovedown
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_BYTES') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,memmovedownb,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmovedown,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memmovedown */
#include <local/string/memmovedown.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_BYTES') */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovedownb)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedown))(__dst, __src, __n_bytes); }
#endif /* !__CRT_HAVE_memmovedown */
#ifdef __CRT_HAVE_mempmoveup
/* Same as `memmoveb', but return `DST + N_BYTES', rather than `DST' (assumes that `DST >= SRC || !N_BYTES') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempmoveupb,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmoveup,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_mempmoveup */
#include <local/string/mempmoveup.h>
/* Same as `memmoveb', but return `DST + N_BYTES', rather than `DST' (assumes that `DST >= SRC || !N_BYTES') */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveupb)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveup))(__dst, __src, __n_bytes); }
#endif /* !__CRT_HAVE_mempmoveup */
#ifdef __CRT_HAVE_mempmovedown
/* Same as `memmoveb', but return `DST + N_BYTES', rather than `DST' (assumes that `DST <= SRC || !N_BYTES') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempmovedownb,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmovedown,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_mempmovedown */
#include <local/string/mempmovedown.h>
/* Same as `memmoveb', but return `DST + N_BYTES', rather than `DST' (assumes that `DST <= SRC || !N_BYTES') */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovedownb)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedown))(__dst, __src, __n_bytes); }
#endif /* !__CRT_HAVE_mempmovedown */
#ifdef __fast_memmoveupw_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_WORDS') */
__NAMESPACE_FAST_USING_OR_IMPL(memmoveupw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveupw)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupw))(__dst, __src, __n_words); })
#elif defined(__CRT_HAVE_memmoveupw)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_WORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_memmovew)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),memmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 2)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemmove)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_WORDS') */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmemmove,(__dst,__src,__n_words))
#else /* ... */
#include <local/string/memmoveupw.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_WORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmoveupw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveupw)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupw))(__dst, __src, __n_words); })
#endif /* !... */
#ifdef __fast_memmovedownw_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
__NAMESPACE_FAST_USING_OR_IMPL(memmovedownw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovedownw)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownw))(__dst, __src, __n_words); })
#elif defined(__CRT_HAVE_memmovedownw)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_memmovew)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),memmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 2)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemmove)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmemmove,(__dst,__src,__n_words))
#else /* ... */
#include <local/string/memmovedownw.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmovedownw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovedownw)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownw))(__dst, __src, __n_words); })
#endif /* !... */
#ifdef __fast_mempmoveupw_defined
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST >= SRC || !N_WORDS') */
__NAMESPACE_FAST_USING_OR_IMPL(mempmoveupw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveupw)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupw))(__dst, __src, __n_words); })
#elif defined(__CRT_HAVE_mempmoveupw)
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST >= SRC || !N_WORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_mempmovew)
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST >= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),mempmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempmove) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST >= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmempmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempmove)
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST >= SRC || !N_WORDS') */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmempmove,(__dst,__src,__n_words))
#else /* ... */
#include <local/string/mempmoveupw.h>
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST >= SRC || !N_WORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmoveupw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveupw)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveupw))(__dst, __src, __n_words); })
#endif /* !... */
#ifdef __fast_mempmovedownw_defined
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST <= SRC || !N_WORDS') */
__NAMESPACE_FAST_USING_OR_IMPL(mempmovedownw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovedownw)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownw))(__dst, __src, __n_words); })
#elif defined(__CRT_HAVE_mempmovedownw)
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST <= SRC || !N_WORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_mempmovew)
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST <= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),mempmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempmove) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST <= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmempmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempmove)
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST <= SRC || !N_WORDS') */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmempmove,(__dst,__src,__n_words))
#else /* ... */
#include <local/string/mempmovedownw.h>
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST <= SRC || !N_WORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmovedownw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovedownw)(void *__dst, void const *__src, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedownw))(__dst, __src, __n_words); })
#endif /* !... */
#ifdef __fast_memmoveupl_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
__NAMESPACE_FAST_USING_OR_IMPL(memmoveupl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveupl)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupl))(__dst, __src, __n_dwords); })
#elif defined(__CRT_HAVE_memmoveupl)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_memmovel)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 4)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemmove) && defined(__PE__)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmemmove,(__dst,__src,__n_dwords))
#else /* ... */
#include <local/string/memmoveupl.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmoveupl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveupl)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupl))(__dst, __src, __n_dwords); })
#endif /* !... */
#ifdef __fast_memmovedownl_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
__NAMESPACE_FAST_USING_OR_IMPL(memmovedownl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovedownl)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownl))(__dst, __src, __n_dwords); })
#elif defined(__CRT_HAVE_memmovedownl)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_memmovel)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 4)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemmove) && defined(__PE__)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmemmove,(__dst,__src,__n_dwords))
#else /* ... */
#include <local/string/memmovedownl.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmovedownl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovedownl)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownl))(__dst, __src, __n_dwords); })
#endif /* !... */
#ifdef __fast_mempmoveupl_defined
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST >= SRC || !N_DWORDS') */
__NAMESPACE_FAST_USING_OR_IMPL(mempmoveupl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveupl)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupl))(__dst, __src, __n_dwords); })
#elif defined(__CRT_HAVE_mempmoveupl)
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST >= SRC || !N_DWORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_mempmovel)
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST >= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),mempmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempmove) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST >= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmempmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempmove) && defined(__PE__)
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST >= SRC || !N_DWORDS') */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmempmove,(__dst,__src,__n_dwords))
#else /* ... */
#include <local/string/mempmoveupl.h>
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST >= SRC || !N_DWORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmoveupl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveupl)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveupl))(__dst, __src, __n_dwords); })
#endif /* !... */
#ifdef __fast_mempmovedownl_defined
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST <= SRC || !N_DWORDS') */
__NAMESPACE_FAST_USING_OR_IMPL(mempmovedownl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovedownl)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownl))(__dst, __src, __n_dwords); })
#elif defined(__CRT_HAVE_mempmovedownl)
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST <= SRC || !N_DWORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_mempmovel)
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST <= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),mempmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempmove) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST <= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmempmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempmove) && defined(__PE__)
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST <= SRC || !N_DWORDS') */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmempmove,(__dst,__src,__n_dwords))
#else /* ... */
#include <local/string/mempmovedownl.h>
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST <= SRC || !N_DWORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmovedownl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovedownl)(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedownl))(__dst, __src, __n_dwords); })
#endif /* !... */
#endif /* __USE_KOS */
#ifdef __CRT_HAVE_memset
/* Fill memory with a given byte */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memsetb,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_memset */
#include <local/string/memset.h>
/* Fill memory with a given byte */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetb)(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memset))(__dst, __byte, (__SIZE_TYPE__)__n_bytes); }
#endif /* !__CRT_HAVE_memset */
#ifdef __CRT_HAVE_mempset
/* Same as `memsetb', but return `DST + N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempsetb,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),mempset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_mempset */
#include <local/string/mempset.h>
/* Same as `memsetb', but return `DST + N_BYTES', rather than `DST' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetb)(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempset))(__dst, __byte, __n_bytes); }
#endif /* !__CRT_HAVE_mempset */
#ifdef __fast_memsetw_defined
/* Fill memory with a given word */
__NAMESPACE_FAST_USING_OR_IMPL(memsetw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetw)(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetw))(__dst, __word, __n_words); })
#elif defined(__CRT_HAVE_memsetw)
/* Fill memory with a given word */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_wmemset) && (__SIZEOF_WCHAR_T__ == 2)
/* Fill memory with a given word */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),wmemset,(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemset)
/* Fill memory with a given word */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),DOS$wmemset,(__dst,__word,__n_words))
#else /* ... */
#include <local/string/memsetw.h>
/* Fill memory with a given word */
__NAMESPACE_LOCAL_USING_OR_IMPL(memsetw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetw)(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetw))(__dst, __word, __n_words); })
#endif /* !... */
#ifdef __fast_mempsetw_defined
/* Same as `memsetw', but return `DST + N_WORDS', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempsetw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetw)(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetw))(__dst, __word, __n_words); })
#elif defined(__CRT_HAVE_mempsetw)
/* Same as `memsetw', but return `DST + N_WORDS', rather than `DST' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_wmempset) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `memsetw', but return `DST + N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),wmempset,(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempset)
/* Same as `memsetw', but return `DST + N_WORDS', rather than `DST' */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),DOS$wmempset,(__dst,__word,__n_words))
#else /* ... */
#include <local/string/mempsetw.h>
/* Same as `memsetw', but return `DST + N_WORDS', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempsetw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetw)(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetw))(__dst, __word, __n_words); })
#endif /* !... */
#ifdef __fast_memsetl_defined
/* Fill memory with a given dword */
__NAMESPACE_FAST_USING_OR_IMPL(memsetl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetl)(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetl))(__dst, __dword, __n_dwords); })
#elif defined(__CRT_HAVE_memsetl)
/* Fill memory with a given dword */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_wmemset) && (__SIZEOF_WCHAR_T__ == 4)
/* Fill memory with a given dword */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmemset,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemset) && defined(__PE__)
/* Fill memory with a given dword */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),KOS$wmemset,(__dst,__dword,__n_dwords))
#else /* ... */
#include <local/string/memsetl.h>
/* Fill memory with a given dword */
__NAMESPACE_LOCAL_USING_OR_IMPL(memsetl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetl)(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetl))(__dst, __dword, __n_dwords); })
#endif /* !... */
#ifdef __fast_mempsetl_defined
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempsetl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetl)(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetl))(__dst, __dword, __n_dwords); })
#elif defined(__CRT_HAVE_mempsetl)
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_wmempset) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmempset,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempset) && defined(__PE__)
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),KOS$wmempset,(__dst,__dword,__n_dwords))
#else /* ... */
#include <local/string/mempsetl.h>
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempsetl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetl)(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetl))(__dst, __dword, __n_dwords); })
#endif /* !... */
#ifdef __CRT_HAVE_memcmp
/* Compare memory buffers and return the difference of the first non-matching byte */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcmpb,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_bcmp)
/* Compare memory buffers and return the difference of the first non-matching byte */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcmpb,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,(__s1,__s2,__n_bytes))
#else /* ... */
#include <local/string/memcmp.h>
/* Compare memory buffers and return the difference of the first non-matching byte */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memcmpb)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp))(__s1, __s2, (__SIZE_TYPE__)__n_bytes); }
#endif /* !... */
#ifdef __fast_memcmpw_defined
/* Compare memory buffers and return the difference of the first non-matching word */
__NAMESPACE_FAST_USING_OR_IMPL(memcmpw, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __INT16_TYPE__ __NOTHROW_NCX(__LIBCCALL memcmpw)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpw))(__s1, __s2, __n_words); })
#elif defined(__CRT_HAVE_memcmpw)
/* Compare memory buffers and return the difference of the first non-matching word */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__INT16_TYPE__,__NOTHROW_NCX,memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),(__s1,__s2,__n_words))
#elif defined(__CRT_HAVE_wmemcmp) && (__SIZEOF_WCHAR_T__ == 2)
/* Compare memory buffers and return the difference of the first non-matching word */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__INT16_TYPE__,__NOTHROW_NCX,memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),wmemcmp,(__s1,__s2,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemcmp)
/* Compare memory buffers and return the difference of the first non-matching word */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__INT16_TYPE__,__NOTHROW_NCX,__LIBCCALL,memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),DOS$wmemcmp,(__s1,__s2,__n_words))
#else /* ... */
#include <local/string/memcmpw.h>
/* Compare memory buffers and return the difference of the first non-matching word */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcmpw, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __INT16_TYPE__ __NOTHROW_NCX(__LIBCCALL memcmpw)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpw))(__s1, __s2, __n_words); })
#endif /* !... */
#ifdef __fast_memcmpl_defined
/* Compare memory buffers and return the difference of the first non-matching dword */
__NAMESPACE_FAST_USING_OR_IMPL(memcmpl, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __INT32_TYPE__ __NOTHROW_NCX(__LIBCCALL memcmpl)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpl))(__s1, __s2, __n_dwords); })
#elif defined(__CRT_HAVE_memcmpl)
/* Compare memory buffers and return the difference of the first non-matching dword */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__INT32_TYPE__,__NOTHROW_NCX,memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),(__s1,__s2,__n_dwords))
#elif defined(__CRT_HAVE_wmemcmp) && (__SIZEOF_WCHAR_T__ == 4)
/* Compare memory buffers and return the difference of the first non-matching dword */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__INT32_TYPE__,__NOTHROW_NCX,memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),wmemcmp,(__s1,__s2,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemcmp) && defined(__PE__)
/* Compare memory buffers and return the difference of the first non-matching dword */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__INT32_TYPE__,__NOTHROW_NCX,__LIBCCALL,memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),KOS$wmemcmp,(__s1,__s2,__n_dwords))
#else /* ... */
#include <local/string/memcmpl.h>
/* Compare memory buffers and return the difference of the first non-matching dword */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcmpl, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __INT32_TYPE__ __NOTHROW_NCX(__LIBCCALL memcmpl)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpl))(__s1, __s2, __n_dwords); })
#endif /* !... */
#ifdef __CRT_HAVE_memchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memchrb,(void *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memchr,(__haystack,__byte,__n_bytes))
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memchrb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memchr,(__haystack,__byte,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memchrb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memchr,(__haystack,__byte,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memchr */
#include <local/string/memchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrb)(void *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))(__haystack, __byte, (__SIZE_TYPE__)__n_bytes); }
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))(__haystack, __byte, (__SIZE_TYPE__)__n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))(__haystack, __byte, (__SIZE_TYPE__)__n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memchr */
#ifdef __fast_memchrw_defined
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __cplusplus
__NAMESPACE_FAST_USING(memchrw)
#else /* __cplusplus */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(__haystack, __word, __n_words); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(__haystack, __word, __n_words); }
#endif /* !__cplusplus */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_FAST_USING_OR_IMPL(memchrw, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(__haystack, __word, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memchrw)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memchrw,(__haystack,__word,__n_words))
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memchrw,(__haystack,__word,__n_words))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),(__haystack,__word,__n_words))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_wmemchr) && (__SIZEOF_WCHAR_T__ == 2)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),wmemchr,(__haystack,__word,__n_words))
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),wmemchr,(__haystack,__word,__n_words))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),wmemchr,(__haystack,__word,__n_words))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_DOS$wmemchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),DOS$wmemchr,(__haystack,__word,__n_words))
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,__LIBCCALL,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),DOS$wmemchr,(__haystack,__word,__n_words))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),DOS$wmemchr,(__haystack,__word,__n_words))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/memchrw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrw))(__haystack, __word, __n_words); }
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrw))(__haystack, __word, __n_words); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memchrw, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrw))(__haystack, __word, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __fast_memchrl_defined
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __cplusplus
__NAMESPACE_FAST_USING(memchrl)
#else /* __cplusplus */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(__haystack, __dword, __n_dwords); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(__haystack, __dword, __n_dwords); }
#endif /* !__cplusplus */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_FAST_USING_OR_IMPL(memchrl, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(__haystack, __dword, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memchrl)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memchrl,(__haystack,__dword,__n_dwords))
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memchrl,(__haystack,__dword,__n_dwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),(__haystack,__dword,__n_dwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_wmemchr) && (__SIZEOF_WCHAR_T__ == 4)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmemchr,(__haystack,__dword,__n_dwords))
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmemchr,(__haystack,__dword,__n_dwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmemchr,(__haystack,__dword,__n_dwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_KOS$wmemchr) && defined(__PE__)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),KOS$wmemchr,(__haystack,__dword,__n_dwords))
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,__LIBCCALL,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),KOS$wmemchr,(__haystack,__dword,__n_dwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),KOS$wmemchr,(__haystack,__dword,__n_dwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/memchrl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrl))(__haystack, __dword, __n_dwords); }
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrl))(__haystack, __dword, __n_dwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memchrl, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrl))(__haystack, __dword, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_memrchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrchrb,(void *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memrchr,(__haystack,__byte,__n_bytes))
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memrchrb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memrchr,(__haystack,__byte,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrchrb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memrchr,(__haystack,__byte,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrchr */
#include <local/string/memrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrb)(void *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))(__haystack, __byte, __n_bytes); }
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))(__haystack, __byte, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))(__haystack, __byte, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrchr */
#ifdef __fast_memrchrw_defined
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_WORDS * 2'. - Return `NULL' if `NEEDLE' wasn't found. */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __cplusplus
__NAMESPACE_FAST_USING(memrchrw)
#else /* __cplusplus */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrw))(__haystack, __word, __n_words); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrw))(__haystack, __word, __n_words); }
#endif /* !__cplusplus */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_FAST_USING_OR_IMPL(memrchrw, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrw))(__haystack, __word, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memrchrw)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_WORDS * 2'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memrchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memrchrw,(__haystack,__word,__n_words))
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_WORDS * 2'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,memrchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memrchrw,(__haystack,__word,__n_words))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_WORDS * 2'. - Return `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memrchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),(__haystack,__word,__n_words))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/memrchrw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_WORDS * 2'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrw))(__haystack, __word, __n_words); }
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_WORDS * 2'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrw))(__haystack, __word, __n_words); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_WORDS * 2'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrchrw, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrw))(__haystack, __word, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __fast_memrchrl_defined
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_DWORDS * 4'. - Return `NULL' if `NEEDLE' wasn't found. */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __cplusplus
__NAMESPACE_FAST_USING(memrchrl)
#else /* __cplusplus */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrl))(__haystack, __dword, __n_dwords); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrl))(__haystack, __dword, __n_dwords); }
#endif /* !__cplusplus */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_FAST_USING_OR_IMPL(memrchrl, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrl))(__haystack, __dword, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memrchrl)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_DWORDS * 4'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memrchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memrchrl,(__haystack,__dword,__n_dwords))
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_DWORDS * 4'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,memrchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memrchrl,(__haystack,__dword,__n_dwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_DWORDS * 4'. - Return `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memrchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),(__haystack,__dword,__n_dwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/memrchrl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_DWORDS * 4'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrl))(__haystack, __dword, __n_dwords); }
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_DWORDS * 4'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrl))(__haystack, __dword, __n_dwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_DWORDS * 4'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrchrl, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrl))(__haystack, __dword, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_rawmemchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemchrb,(void *__restrict __haystack, int __byte),rawmemchr,(__haystack,__byte))
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,rawmemchrb,(void const *__restrict __haystack, int __byte),rawmemchr,(__haystack,__byte))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemchrb,(void const *__restrict __haystack, int __byte),rawmemchr,(__haystack,__byte))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE___rawmemchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemchrb,(void *__restrict __haystack, int __byte),__rawmemchr,(__haystack,__byte))
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,rawmemchrb,(void const *__restrict __haystack, int __byte),__rawmemchr,(__haystack,__byte))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemchrb,(void const *__restrict __haystack, int __byte),__rawmemchr,(__haystack,__byte))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/rawmemchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrb)(void *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchr))(__haystack, __byte); }
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemchrb)(void const *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchr))(__haystack, __byte); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrb)(void const *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchr))(__haystack, __byte); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_rawmemchrw
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word),rawmemchrw,(__haystack,__word))
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,rawmemchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),rawmemchrw,(__haystack,__word))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),(__haystack,__word))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemchrw */
#include <local/string/rawmemchrw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrw))(__haystack, __word); }
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrw))(__haystack, __word); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemchrw, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrw))(__haystack, __word); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemchrw */
#ifdef __CRT_HAVE_rawmemchrl
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword),rawmemchrl,(__haystack,__dword))
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,rawmemchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),rawmemchrl,(__haystack,__dword))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),(__haystack,__dword))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemchrl */
#include <local/string/rawmemchrl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrl))(__haystack, __dword); }
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrl))(__haystack, __dword); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemchrl, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrl))(__haystack, __dword); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemchrl */
#ifdef __CRT_HAVE_rawmemrchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrb' without a search limit, starting at `HAYSTACK - 1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemrchrb,(void *__restrict __haystack, int __byte),rawmemrchr,(__haystack,__byte))
/* Same as `memrchrb' without a search limit, starting at `HAYSTACK - 1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,rawmemrchrb,(void const *__restrict __haystack, int __byte),rawmemrchr,(__haystack,__byte))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrb' without a search limit, starting at `HAYSTACK - 1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemrchrb,(void const *__restrict __haystack, int __byte),rawmemrchr,(__haystack,__byte))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrchr */
#include <local/string/rawmemrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrb' without a search limit, starting at `HAYSTACK - 1' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrb)(void *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchr))(__haystack, __byte); }
/* Same as `memrchrb' without a search limit, starting at `HAYSTACK - 1' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrchrb)(void const *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchr))(__haystack, __byte); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrb' without a search limit, starting at `HAYSTACK - 1' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrb)(void const *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchr))(__haystack, __byte); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrchr */
#ifdef __CRT_HAVE_rawmemrchrw
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK - 2' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemrchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word),rawmemrchrw,(__haystack,__word))
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK - 2' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,rawmemrchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),rawmemrchrw,(__haystack,__word))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK - 2' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemrchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),(__haystack,__word))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrchrw */
#include <local/string/rawmemrchrw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK - 2' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrw))(__haystack, __word); }
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK - 2' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrw))(__haystack, __word); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK - 2' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrchrw, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrw))(__haystack, __word); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrchrw */
#ifdef __CRT_HAVE_rawmemrchrl
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK - 4' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemrchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword),rawmemrchrl,(__haystack,__dword))
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK - 4' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,rawmemrchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),rawmemrchrl,(__haystack,__dword))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK - 4' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemrchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),(__haystack,__dword))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrchrl */
#include <local/string/rawmemrchrl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK - 4' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrl))(__haystack, __dword); }
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK - 4' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrl))(__haystack, __dword); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK - 4' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrchrl, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrl))(__haystack, __dword); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrchrl */
#ifdef __CRT_HAVE_memend
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrb', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memendb,(void *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memend,(__haystack,__byte,__n_bytes))
/* Same as `memchrb', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memendb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memend,(__haystack,__byte,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrb', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memendb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memend,(__haystack,__byte,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memend */
#include <local/string/memend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrb', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendb)(void *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))(__haystack, __byte, __n_bytes); }
/* Same as `memchrb', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))(__haystack, __byte, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrb', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))(__haystack, __byte, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memend */
#ifdef __fast_memendw_defined
/* Same as `memchrw', but return `HAYSTACK + N_WORDS * 2', rather than `NULL' if `NEEDLE' wasn't found. */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __cplusplus
__NAMESPACE_FAST_USING(memendw)
#else /* __cplusplus */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendw)(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendw))(__haystack, __word, __n_bytes); }
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendw))(__haystack, __word, __n_bytes); }
#endif /* !__cplusplus */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_FAST_USING_OR_IMPL(memendw, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendw))(__haystack, __word, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memendw)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrw', but return `HAYSTACK + N_WORDS * 2', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memendw,(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_bytes),memendw,(__haystack,__word,__n_bytes))
/* Same as `memchrw', but return `HAYSTACK + N_WORDS * 2', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,memendw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_bytes),memendw,(__haystack,__word,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrw', but return `HAYSTACK + N_WORDS * 2', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memendw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_bytes),(__haystack,__word,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/memendw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrw', but return `HAYSTACK + N_WORDS * 2', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendw)(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendw))(__haystack, __word, __n_bytes); }
/* Same as `memchrw', but return `HAYSTACK + N_WORDS * 2', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendw))(__haystack, __word, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrw', but return `HAYSTACK + N_WORDS * 2', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memendw, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendw))(__haystack, __word, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __fast_memendl_defined
/* Same as `memchrl', but return `HAYSTACK + N_DWORDS * 4', rather than `NULL' if `NEEDLE' wasn't found. */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __cplusplus
__NAMESPACE_FAST_USING(memendl)
#else /* __cplusplus */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendl))(__haystack, __dword, __n_bytes); }
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendl))(__haystack, __dword, __n_bytes); }
#endif /* !__cplusplus */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_FAST_USING_OR_IMPL(memendl, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendl))(__haystack, __dword, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memendl)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrl', but return `HAYSTACK + N_DWORDS * 4', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memendl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_bytes),memendl,(__haystack,__dword,__n_bytes))
/* Same as `memchrl', but return `HAYSTACK + N_DWORDS * 4', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,memendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_bytes),memendl,(__haystack,__dword,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrl', but return `HAYSTACK + N_DWORDS * 4', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_bytes),(__haystack,__dword,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/memendl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrl', but return `HAYSTACK + N_DWORDS * 4', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendl))(__haystack, __dword, __n_bytes); }
/* Same as `memchrl', but return `HAYSTACK + N_DWORDS * 4', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendl))(__haystack, __dword, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrl', but return `HAYSTACK + N_DWORDS * 4', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memendl, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendl))(__haystack, __dword, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_memrend
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrb', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrendb,(void *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memrend,(__haystack,__byte,__n_bytes))
/* Same as `memrchrb', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memrendb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memrend,(__haystack,__byte,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrb', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrendb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memrend,(__haystack,__byte,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrend */
#include <local/string/memrend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrb', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendb)(void *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))(__haystack, __byte, __n_bytes); }
/* Same as `memrchrb', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))(__haystack, __byte, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrb', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))(__haystack, __byte, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrend */
#ifdef __fast_memrendw_defined
/* Same as `memrchrw', but return `HAYSTACK - 2', rather than `NULL' if `NEEDLE' wasn't found. */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __cplusplus
__NAMESPACE_FAST_USING(memrendw)
#else /* __cplusplus */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendw)(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendw))(__haystack, __word, __n_words); }
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendw))(__haystack, __word, __n_words); }
#endif /* !__cplusplus */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_FAST_USING_OR_IMPL(memrendw, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendw))(__haystack, __word, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memrendw)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrw', but return `HAYSTACK - 2', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memrendw,(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memrendw,(__haystack,__word,__n_words))
/* Same as `memrchrw', but return `HAYSTACK - 2', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,memrendw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memrendw,(__haystack,__word,__n_words))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrw', but return `HAYSTACK - 2', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memrendw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),(__haystack,__word,__n_words))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/memrendw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrw', but return `HAYSTACK - 2', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendw)(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendw))(__haystack, __word, __n_words); }
/* Same as `memrchrw', but return `HAYSTACK - 2', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendw))(__haystack, __word, __n_words); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrw', but return `HAYSTACK - 2', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrendw, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendw))(__haystack, __word, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __fast_memrendl_defined
/* Same as `memrchrl', but return `HAYSTACK - 4', rather than `NULL' if `NEEDLE' wasn't found. */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __cplusplus
__NAMESPACE_FAST_USING(memrendl)
#else /* __cplusplus */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendl))(__haystack, __dword, __n_dwords); }
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendl))(__haystack, __dword, __n_dwords); }
#endif /* !__cplusplus */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_FAST_USING_OR_IMPL(memrendl, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendl))(__haystack, __dword, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memrendl)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrl', but return `HAYSTACK - 4', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memrendl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memrendl,(__haystack,__dword,__n_dwords))
/* Same as `memrchrl', but return `HAYSTACK - 4', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,memrendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memrendl,(__haystack,__dword,__n_dwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrl', but return `HAYSTACK - 4', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memrendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),(__haystack,__dword,__n_dwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/memrendl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrl', but return `HAYSTACK - 4', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendl))(__haystack, __dword, __n_dwords); }
/* Same as `memrchrl', but return `HAYSTACK - 4', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendl))(__haystack, __dword, __n_dwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrl', but return `HAYSTACK - 4', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrendl, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendl))(__haystack, __dword, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_memlen
/* Same as `memendb', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `HAYSTACK + N_DWORDS' if the given `NEEDLE' wasn't found */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memlenb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memlen,(__haystack,__byte,__n_bytes))
#else /* __CRT_HAVE_memlen */
#include <local/string/memlen.h>
/* Same as `memendb', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `HAYSTACK + N_DWORDS' if the given `NEEDLE' wasn't found */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memlenb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlen))(__haystack, __byte, __n_bytes); }
#endif /* !__CRT_HAVE_memlen */
#ifdef __CRT_HAVE_memlenw
/* Same as `memendw', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `HAYSTACK + N_DWORDS * 2' if the given `NEEDLE' wasn't found */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),(__haystack,__word,__n_words))
#else /* __CRT_HAVE_memlenw */
#include <local/string/memlenw.h>
/* Same as `memendw', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `HAYSTACK + N_DWORDS * 2' if the given `NEEDLE' wasn't found */
__NAMESPACE_LOCAL_USING_OR_IMPL(memlenw, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlenw))(__haystack, __word, __n_words); })
#endif /* !__CRT_HAVE_memlenw */
#ifdef __CRT_HAVE_memlenl
/* Same as `memendl', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `HAYSTACK + N_DWORDS * 4' if the given `NEEDLE' wasn't found */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),(__haystack,__dword,__n_dwords))
#else /* __CRT_HAVE_memlenl */
#include <local/string/memlenl.h>
/* Same as `memendl', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `HAYSTACK + N_DWORDS * 4' if the given `NEEDLE' wasn't found */
__NAMESPACE_LOCAL_USING_OR_IMPL(memlenl, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlenl))(__haystack, __dword, __n_dwords); })
#endif /* !__CRT_HAVE_memlenl */
#ifdef __CRT_HAVE_memrlen
/* Same as `memrendb', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1' if the given `NEEDLE' wasn't found */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memrlenb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memrlen,(__haystack,__byte,__n_bytes))
#else /* __CRT_HAVE_memrlen */
#include <local/string/memrlen.h>
/* Same as `memrendb', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1' if the given `NEEDLE' wasn't found */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrlenb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlen))(__haystack, __byte, __n_bytes); }
#endif /* !__CRT_HAVE_memrlen */
#ifdef __CRT_HAVE_memrlenw
/* Same as `memrendw', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 2' if the given `NEEDLE' wasn't found */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memrlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),(__haystack,__word,__n_words))
#else /* __CRT_HAVE_memrlenw */
#include <local/string/memrlenw.h>
/* Same as `memrendw', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 2' if the given `NEEDLE' wasn't found */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrlenw, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlenw))(__haystack, __word, __n_words); })
#endif /* !__CRT_HAVE_memrlenw */
#ifdef __CRT_HAVE_memrlenl
/* Same as `memrendl', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 4' if the given `NEEDLE' wasn't found */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memrlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),(__haystack,__dword,__n_dwords))
#else /* __CRT_HAVE_memrlenl */
#include <local/string/memrlenl.h>
/* Same as `memrendl', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 4' if the given `NEEDLE' wasn't found */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrlenl, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlenl))(__haystack, __dword, __n_dwords); })
#endif /* !__CRT_HAVE_memrlenl */
#ifdef __CRT_HAVE_rawmemlen
/* Same as `rawmemchrb', but return the offset from `HAYSTACK', rather than the actual address. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemlenb,(void const *__restrict __haystack, int __needle),rawmemlen,(__haystack,__needle))
#else /* __CRT_HAVE_rawmemlen */
#include <local/string/rawmemlen.h>
/* Same as `rawmemchrb', but return the offset from `HAYSTACK', rather than the actual address. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemlenb)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemlen))(__haystack, __needle); }
#endif /* !__CRT_HAVE_rawmemlen */
#ifdef __CRT_HAVE_rawmemlenw
/* Same as `rawmemchrw', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),(__haystack,__word))
#else /* __CRT_HAVE_rawmemlenw */
#include <local/string/rawmemlenw.h>
/* Same as `rawmemchrw', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemlenw, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemlenw))(__haystack, __word); })
#endif /* !__CRT_HAVE_rawmemlenw */
#ifdef __CRT_HAVE_rawmemlenl
/* Same as `rawmemchrl', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),(__haystack,__dword))
#else /* __CRT_HAVE_rawmemlenl */
#include <local/string/rawmemlenl.h>
/* Same as `rawmemchrl', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemlenl, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemlenl))(__haystack, __dword); })
#endif /* !__CRT_HAVE_rawmemlenl */
#ifdef __CRT_HAVE_rawmemrlen
/* Same as `rawmemrchrb', but return the offset from `HAYSTACK', rather than the actual address. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrlenb,(void const *__restrict __haystack, int __needle),rawmemrlen,(__haystack,__needle))
#else /* __CRT_HAVE_rawmemrlen */
#include <local/string/rawmemrlen.h>
/* Same as `rawmemrchrb', but return the offset from `HAYSTACK', rather than the actual address. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrlenb)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrlen))(__haystack, __needle); }
#endif /* !__CRT_HAVE_rawmemrlen */
#ifdef __CRT_HAVE_rawmemrlenw
/* Same as `rawmemrchrw', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),(__haystack,__word))
#else /* __CRT_HAVE_rawmemrlenw */
#include <local/string/rawmemrlenw.h>
/* Same as `rawmemrchrw', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrlenw, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrlenw))(__haystack, __word); })
#endif /* !__CRT_HAVE_rawmemrlenw */
#ifdef __CRT_HAVE_rawmemrlenl
/* Same as `rawmemrchrl', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),(__haystack,__dword))
#else /* __CRT_HAVE_rawmemrlenl */
#include <local/string/rawmemrlenl.h>
/* Same as `rawmemrchrl', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrlenl, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrlenl))(__haystack, __dword); })
#endif /* !__CRT_HAVE_rawmemrlenl */
#ifdef __UINT64_TYPE__
#ifdef __fast_memcpyq_defined
/* Copy memory between non-overlapping memory blocks. */
__NAMESPACE_FAST_USING_OR_IMPL(memcpyq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyq))(__dst, __src, __n_qwords); })
#elif defined(__CRT_HAVE_memcpyq)
/* Copy memory between non-overlapping memory blocks. */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,memcpyq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),(__dst,__src,__n_qwords))
#else /* ... */
#include <local/string/memcpyq.h>
/* Copy memory between non-overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpyq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyq))(__dst, __src, __n_qwords); })
#endif /* !... */
#ifdef __fast_mempcpyq_defined
/* Same as `memcpyq', but return `DST + N_QWORDS', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempcpyq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyq))(__dst, __src, __n_qwords); })
#elif defined(__CRT_HAVE_mempcpyq)
/* Same as `memcpyq', but return `DST + N_QWORDS', rather than `DST' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,mempcpyq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),(__dst,__src,__n_qwords))
#else /* ... */
#include <local/string/mempcpyq.h>
/* Same as `memcpyq', but return `DST + N_QWORDS', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempcpyq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyq))(__dst, __src, __n_qwords); })
#endif /* !... */
#ifdef __fast_memmoveq_defined
/* Move memory between potentially overlapping memory blocks. */
__NAMESPACE_FAST_USING_OR_IMPL(memmoveq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveq)(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveq))(__dst, __src, __n_qwords); })
#elif defined(__CRT_HAVE_memmoveq)
/* Move memory between potentially overlapping memory blocks. */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,memmoveq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),(__dst,__src,__n_qwords))
#else /* ... */
#include <local/string/memmoveq.h>
/* Move memory between potentially overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmoveq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveq)(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveq))(__dst, __src, __n_qwords); })
#endif /* !... */
#ifdef __fast_mempmoveq_defined
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempmoveq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveq))(__dst, __src, __n_qwords); })
#elif defined(__CRT_HAVE_mempmoveq)
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,mempmoveq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),(__dst,__src,__n_qwords))
#else /* ... */
#include <local/string/mempmoveq.h>
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmoveq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveq))(__dst, __src, __n_qwords); })
#endif /* !... */
#ifdef __USE_KOS
#ifdef __fast_memmoveupq_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_QWORDS') */
__NAMESPACE_FAST_USING_OR_IMPL(memmoveupq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveupq)(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupq))(__dst, __src, __n_qwords); })
#elif defined(__CRT_HAVE_memmoveupq)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_QWORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,memmoveupq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_memmoveq)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_QWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,memmoveupq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),memmoveq,(__dst,__src,__n_qwords))
#else /* ... */
#include <local/string/memmoveupq.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_QWORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmoveupq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveupq)(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupq))(__dst, __src, __n_qwords); })
#endif /* !... */
#ifdef __fast_memmovedownq_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_QWORDS') */
__NAMESPACE_FAST_USING_OR_IMPL(memmovedownq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovedownq)(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownq))(__dst, __src, __n_qwords); })
#elif defined(__CRT_HAVE_memmovedownq)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_QWORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,memmovedownq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_memmoveq)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_QWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,memmovedownq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),memmoveq,(__dst,__src,__n_qwords))
#else /* ... */
#include <local/string/memmovedownq.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_QWORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmovedownq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovedownq)(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownq))(__dst, __src, __n_qwords); })
#endif /* !... */
#ifdef __fast_mempmoveupq_defined
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST >= SRC || !N_QWORDS') */
__NAMESPACE_FAST_USING_OR_IMPL(mempmoveupq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveupq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupq))(__dst, __src, __n_qwords); })
#elif defined(__CRT_HAVE_mempmoveupq)
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST >= SRC || !N_QWORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,mempmoveupq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_mempmoveq)
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST >= SRC || !N_QWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,mempmoveupq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmoveq,(__dst,__src,__n_qwords))
#else /* ... */
#include <local/string/mempmoveupq.h>
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST >= SRC || !N_QWORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmoveupq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveupq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveupq))(__dst, __src, __n_qwords); })
#endif /* !... */
#ifdef __fast_mempmovedownq_defined
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST <= SRC || !N_QWORDS') */
__NAMESPACE_FAST_USING_OR_IMPL(mempmovedownq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovedownq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownq))(__dst, __src, __n_qwords); })
#elif defined(__CRT_HAVE_mempmovedownq)
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST <= SRC || !N_QWORDS') */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,mempmovedownq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_mempmoveq)
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST <= SRC || !N_QWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,mempmovedownq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmoveq,(__dst,__src,__n_qwords))
#else /* ... */
#include <local/string/mempmovedownq.h>
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST <= SRC || !N_QWORDS') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmovedownq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovedownq)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedownq))(__dst, __src, __n_qwords); })
#endif /* !... */
#endif /* __USE_KOS */
#ifdef __fast_memsetq_defined
/* Fill memory with a given qword */
__NAMESPACE_FAST_USING_OR_IMPL(memsetq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetq)(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetq))(__dst, __qword, __n_qwords); })
#elif defined(__CRT_HAVE_memsetq)
/* Fill memory with a given qword */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memsetq,(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),(__dst,__qword,__n_qwords))
#else /* ... */
#include <local/string/memsetq.h>
/* Fill memory with a given qword */
__NAMESPACE_LOCAL_USING_OR_IMPL(memsetq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetq)(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetq))(__dst, __qword, __n_qwords); })
#endif /* !... */
#ifdef __fast_mempsetq_defined
/* Same as `memsetq', but return `DST + N_QWORDS', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempsetq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetq)(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetq))(__dst, __qword, __n_qwords); })
#elif defined(__CRT_HAVE_mempsetq)
/* Same as `memsetq', but return `DST + N_QWORDS', rather than `DST' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,mempsetq,(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),(__dst,__qword,__n_qwords))
#else /* ... */
#include <local/string/mempsetq.h>
/* Same as `memsetq', but return `DST + N_QWORDS', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempsetq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetq)(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetq))(__dst, __qword, __n_qwords); })
#endif /* !... */
#ifdef __fast_memcmpq_defined
/* Compare memory buffers and return the difference of the first non-matching qword */
__NAMESPACE_FAST_USING_OR_IMPL(memcmpq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL memcmpq)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpq))(__s1, __s2, __n_dwords); })
#elif defined(__CRT_HAVE_memcmpq)
/* Compare memory buffers and return the difference of the first non-matching qword */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__INT64_TYPE__,__NOTHROW_NCX,memcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),(__s1,__s2,__n_dwords))
#else /* ... */
#include <local/string/memcmpq.h>
/* Compare memory buffers and return the difference of the first non-matching qword */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcmpq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL memcmpq)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpq))(__s1, __s2, __n_dwords); })
#endif /* !... */
#ifdef __fast_memchrq_defined
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __cplusplus
__NAMESPACE_FAST_USING(memchrq)
#else /* __cplusplus */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrq))(__haystack, __qword, __n_qwords); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrq))(__haystack, __qword, __n_qwords); }
#endif /* !__cplusplus */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_FAST_USING_OR_IMPL(memchrq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrq))(__haystack, __qword, __n_qwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memchrq)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memchrq,(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memchrq,(__haystack,__qword,__n_qwords))
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,memchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memchrq,(__haystack,__qword,__n_qwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),(__haystack,__qword,__n_qwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/memchrq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrq))(__haystack, __qword, __n_qwords); }
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrq))(__haystack, __qword, __n_qwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memchrq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrq))(__haystack, __qword, __n_qwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __fast_memrchrq_defined
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __cplusplus
__NAMESPACE_FAST_USING(memrchrq)
#else /* __cplusplus */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrq))(__haystack, __qword, __n_qwords); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrq))(__haystack, __qword, __n_qwords); }
#endif /* !__cplusplus */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_FAST_USING_OR_IMPL(memrchrq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrq))(__haystack, __qword, __n_qwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memrchrq)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memrchrq,(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memrchrq,(__haystack,__qword,__n_qwords))
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,memrchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memrchrq,(__haystack,__qword,__n_qwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memrchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),(__haystack,__qword,__n_qwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/memrchrq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrq))(__haystack, __qword, __n_qwords); }
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrq))(__haystack, __qword, __n_qwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrchrq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrq))(__haystack, __qword, __n_qwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_rawmemchrq
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemchrq,(void *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemchrq,(__haystack,__qword))
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,rawmemchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemchrq,(__haystack,__qword))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),(__haystack,__qword))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemchrq */
#include <local/string/rawmemchrq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrq))(__haystack, __qword); }
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrq))(__haystack, __qword); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemchrq, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrq))(__haystack, __qword); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemchrq */
#ifdef __CRT_HAVE_rawmemrchrq
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK - 8' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemrchrq,(void *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemrchrq,(__haystack,__qword))
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK - 8' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,rawmemrchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemrchrq,(__haystack,__qword))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK - 8' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemrchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),(__haystack,__qword))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrchrq */
#include <local/string/rawmemrchrq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK - 8' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrq))(__haystack, __qword); }
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK - 8' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrq))(__haystack, __qword); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK - 8' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrchrq, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrq))(__haystack, __qword); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrchrq */
#ifdef __fast_memendq_defined
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __cplusplus
__NAMESPACE_FAST_USING(memendq)
#else /* __cplusplus */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendq))(__haystack, __qword, __n_bytes); }
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendq))(__haystack, __qword, __n_bytes); }
#endif /* !__cplusplus */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_FAST_USING_OR_IMPL(memendq, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendq))(__haystack, __qword, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memendq)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memendq,(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_bytes),memendq,(__haystack,__qword,__n_bytes))
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,memendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_bytes),memendq,(__haystack,__qword,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_bytes),(__haystack,__qword,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/memendq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendq))(__haystack, __qword, __n_bytes); }
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendq))(__haystack, __qword, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memendq, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendq))(__haystack, __qword, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __fast_memrendq_defined
/* Same as `memrchrq', but return `HAYSTACK - 8', rather than `NULL' if `NEEDLE' wasn't found. */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __cplusplus
__NAMESPACE_FAST_USING(memrendq)
#else /* __cplusplus */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendq))(__haystack, __qword, __n_qwords); }
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendq))(__haystack, __qword, __n_qwords); }
#endif /* !__cplusplus */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_FAST_USING_OR_IMPL(memrendq, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendq))(__haystack, __qword, __n_qwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memrendq)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrq', but return `HAYSTACK - 8', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memrendq,(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memrendq,(__haystack,__qword,__n_qwords))
/* Same as `memrchrq', but return `HAYSTACK - 8', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,memrendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memrendq,(__haystack,__qword,__n_qwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrq', but return `HAYSTACK - 8', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memrendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),(__haystack,__qword,__n_qwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/memrendq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrq', but return `HAYSTACK - 8', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendq))(__haystack, __qword, __n_qwords); }
/* Same as `memrchrq', but return `HAYSTACK - 8', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendq))(__haystack, __qword, __n_qwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrq', but return `HAYSTACK - 8', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrendq, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendq))(__haystack, __qword, __n_qwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __fast_memlenq_defined
/* Same as `memendq', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `N_QWORDS' if the given `NEEDLE' wasn't found */
__NAMESPACE_FAST_USING_OR_IMPL(memlenq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memlenq))(__haystack, __qword, __n_qwords); })
#elif defined(__CRT_HAVE_memlenq)
/* Same as `memendq', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `N_QWORDS' if the given `NEEDLE' wasn't found */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),(__haystack,__qword,__n_qwords))
#else /* ... */
#include <local/string/memlenq.h>
/* Same as `memendq', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `N_QWORDS' if the given `NEEDLE' wasn't found */
__NAMESPACE_LOCAL_USING_OR_IMPL(memlenq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlenq))(__haystack, __qword, __n_qwords); })
#endif /* !... */
#ifdef __fast_memrlenq_defined
/* Same as `memrendq', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 8' if the given `NEEDLE' wasn't found */
__NAMESPACE_FAST_USING_OR_IMPL(memrlenq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrlenq))(__haystack, __qword, __n_qwords); })
#elif defined(__CRT_HAVE_memrlenq)
/* Same as `memrendq', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 8' if the given `NEEDLE' wasn't found */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memrlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),(__haystack,__qword,__n_qwords))
#else /* ... */
#include <local/string/memrlenq.h>
/* Same as `memrendq', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 8' if the given `NEEDLE' wasn't found */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrlenq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlenq))(__haystack, __qword, __n_qwords); })
#endif /* !... */
#ifdef __fast_rawmemlenq_defined
/* Same as `rawmemchrq', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_FAST_USING_OR_IMPL(rawmemlenq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(rawmemlenq))(__haystack, __qword); })
#elif defined(__CRT_HAVE_rawmemlenq)
/* Same as `rawmemchrq', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),(__haystack,__qword))
#else /* ... */
#include <local/string/rawmemlenq.h>
/* Same as `rawmemchrq', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemlenq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemlenq))(__haystack, __qword); })
#endif /* !... */
#ifdef __fast_rawmemrlenq_defined
/* Same as `rawmemrchrq', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_FAST_USING_OR_IMPL(rawmemrlenq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(rawmemrlenq))(__haystack, __qword); })
#elif defined(__CRT_HAVE_rawmemrlenq)
/* Same as `rawmemrchrq', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),(__haystack,__qword))
#else /* ... */
#include <local/string/rawmemrlenq.h>
/* Same as `rawmemrchrq', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrlenq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrlenq))(__haystack, __qword); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */


#ifdef __USE_STRING_XCHR
#ifdef __CRT_HAVE_memxchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memxchr,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memxchr,(__haystack,__needle,__n_bytes))
/* Same as `memchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memxchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memxchr,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchr', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memxchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxchr */
#include <local/string/memxchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memxchr)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchr))(__haystack, __needle, __n_bytes); }
/* Same as `memchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memxchr)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchr))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchr', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memxchr)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchr))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxchr */
#ifdef __CRT_HAVE_memrxchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrxchr,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrxchr,(__haystack,__needle,__n_bytes))
/* Same as `memrchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memrxchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrxchr,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchr', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrxchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxchr */
#include <local/string/memrxchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrxchr)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchr))(__haystack, __needle, __n_bytes); }
/* Same as `memrchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memrxchr)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchr))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchr', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrxchr)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchr))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxchr */
#ifdef __CRT_HAVE_rawmemxchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemxchr,(void *__restrict __haystack, int __needle),rawmemxchr,(__haystack,__needle))
/* Same as `rawmemchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,rawmemxchr,(void const *__restrict __haystack, int __needle),rawmemxchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchr', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemxchr,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemxchr */
#include <local/string/rawmemxchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemxchr)(void *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))(__haystack, __needle); }
/* Same as `rawmemchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL rawmemxchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchr', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxchr, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemxchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))(__haystack, __needle); })
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
#include <local/string/rawmemrxchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemrxchr)(void *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchr))(__haystack, __needle); }
/* Same as `rawmemrchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL rawmemrxchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchr', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxchr, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemrxchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrxchr */
#ifdef __CRT_HAVE_memxend
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memend', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memxend,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memxend,(__haystack,__needle,__n_bytes))
/* Same as `memend', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memxend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memxend,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memend', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memxend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxend */
#include <local/string/memxend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memend', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memxend)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))(__haystack, __needle, __n_bytes); }
/* Same as `memend', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memxend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memend', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxend, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memxend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxend */
#ifdef __CRT_HAVE_memrxend
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrend', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrxend,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrxend,(__haystack,__needle,__n_bytes))
/* Same as `memrend', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memrxend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrxend,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrend', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrxend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxend */
#include <local/string/memrxend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrend', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrxend)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))(__haystack, __needle, __n_bytes); }
/* Same as `memrend', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memrxend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrend', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxend, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrxend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxend */
#ifdef __CRT_HAVE_memxlen
/* Same as `memlen', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memxlen,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memxlen */
#include <local/string/memxlen.h>
/* Same as `memlen', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memxlen)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxlen))(__haystack, __needle, __n_bytes); })
#endif /* !__CRT_HAVE_memxlen */
#ifdef __CRT_HAVE_memrxlen
/* Same as `memrlen', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memrxlen,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memrxlen */
#include <local/string/memrxlen.h>
/* Same as `memrlen', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrxlen)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxlen))(__haystack, __needle, __n_bytes); })
#endif /* !__CRT_HAVE_memrxlen */
#ifdef __CRT_HAVE_rawmemxlen
/* Same as `rawmemlen', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemxlen,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* __CRT_HAVE_rawmemxlen */
#include <local/string/rawmemxlen.h>
/* Same as `rawmemlen', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemxlen)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxlen))(__haystack, __needle); })
#endif /* !__CRT_HAVE_rawmemxlen */
#ifdef __CRT_HAVE_rawmemrxlen
/* Same as `rawmemrlen', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrxlen,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* __CRT_HAVE_rawmemrxlen */
#include <local/string/rawmemrxlen.h>
/* Same as `rawmemrlen', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrxlen)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxlen))(__haystack, __needle); })
#endif /* !__CRT_HAVE_rawmemrxlen */
#ifdef __USE_STRING_BWLQ
#ifdef __CRT_HAVE_memxchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memxchrb,(void *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memxchr,(__haystack,__byte,__n_bytes))
/* Same as `memchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memxchrb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memxchr,(__haystack,__byte,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memxchrb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memxchr,(__haystack,__byte,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxchr */
#include <local/string/memxchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrb)(void *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchr))(__haystack, __byte, __n_bytes); }
/* Same as `memchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxchrb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchr))(__haystack, __byte, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchr))(__haystack, __byte, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxchr */
#ifdef __CRT_HAVE_memxchrw
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memxchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memxchrw,(__haystack,__word,__n_words))
/* Same as `memchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,memxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memxchrw,(__haystack,__word,__n_words))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),(__haystack,__word,__n_words))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxchrw */
#include <local/string/memxchrw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrw))(__haystack, __word, __n_words); }
/* Same as `memchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrw))(__haystack, __word, __n_words); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxchrw, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrw))(__haystack, __word, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxchrw */
#ifdef __CRT_HAVE_memxchrl
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memxchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memxchrl,(__haystack,__dword,__n_dwords))
/* Same as `memchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,memxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memxchrl,(__haystack,__dword,__n_dwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),(__haystack,__dword,__n_dwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxchrl */
#include <local/string/memxchrl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrl))(__haystack, __dword, __n_dwords); }
/* Same as `memchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrl))(__haystack, __dword, __n_dwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxchrl, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrl))(__haystack, __dword, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxchrl */
#ifdef __CRT_HAVE_memrxchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrxchrb,(void *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memrxchr,(__haystack,__byte,__n_bytes))
/* Same as `memrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memrxchrb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memrxchr,(__haystack,__byte,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrxchrb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memrxchr,(__haystack,__byte,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxchr */
#include <local/string/memrxchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrb)(void *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchr))(__haystack, __byte, __n_bytes); }
/* Same as `memrchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxchrb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchr))(__haystack, __byte, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchr))(__haystack, __byte, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxchr */
#ifdef __CRT_HAVE_memrxchrw
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memrxchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memrxchrw,(__haystack,__word,__n_words))
/* Same as `memrchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,memrxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memrxchrw,(__haystack,__word,__n_words))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memrxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),(__haystack,__word,__n_words))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxchrw */
#include <local/string/memrxchrw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrw))(__haystack, __word, __n_words); }
/* Same as `memrchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrw))(__haystack, __word, __n_words); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxchrw, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrw))(__haystack, __word, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxchrw */
#ifdef __CRT_HAVE_memrxchrl
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memrxchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memrxchrl,(__haystack,__dword,__n_dwords))
/* Same as `memrchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,memrxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memrxchrl,(__haystack,__dword,__n_dwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memrxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),(__haystack,__dword,__n_dwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxchrl */
#include <local/string/memrxchrl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrl))(__haystack, __dword, __n_dwords); }
/* Same as `memrchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrl))(__haystack, __dword, __n_dwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxchrl, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrl))(__haystack, __dword, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxchrl */
#ifdef __CRT_HAVE_rawmemxchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemxchrb,(void *__restrict __haystack, int __byte),rawmemxchr,(__haystack,__byte))
/* Same as `rawmemchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,rawmemxchrb,(void const *__restrict __haystack, int __byte),rawmemxchr,(__haystack,__byte))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemxchrb,(void const *__restrict __haystack, int __byte),rawmemxchr,(__haystack,__byte))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemxchr */
#include <local/string/rawmemxchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrb)(void *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))(__haystack, __byte); }
/* Same as `rawmemchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemxchrb)(void const *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))(__haystack, __byte); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrb)(void const *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))(__haystack, __byte); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemxchr */
#ifdef __CRT_HAVE_rawmemxchrw
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemxchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word),rawmemxchrw,(__haystack,__word))
/* Same as `rawmemchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,rawmemxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),rawmemxchrw,(__haystack,__word))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchrw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),(__haystack,__word))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemxchrw */
#include <local/string/rawmemxchrw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrw))(__haystack, __word); }
/* Same as `rawmemchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrw))(__haystack, __word); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchrw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxchrw, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrw))(__haystack, __word); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemxchrw */
#ifdef __CRT_HAVE_rawmemxchrl
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemxchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword),rawmemxchrl,(__haystack,__dword))
/* Same as `rawmemchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,rawmemxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),rawmemxchrl,(__haystack,__dword))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchrl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),(__haystack,__dword))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemxchrl */
#include <local/string/rawmemxchrl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrl))(__haystack, __dword); }
/* Same as `rawmemchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrl))(__haystack, __dword); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchrl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxchrl, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrl))(__haystack, __dword); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemxchrl */
#ifdef __CRT_HAVE_rawmemrxchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemrxchrb,(void *__restrict __haystack, int __byte),rawmemrxchr,(__haystack,__byte))
/* Same as `rawmemrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,rawmemrxchrb,(void const *__restrict __haystack, int __byte),rawmemrxchr,(__haystack,__byte))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemrxchrb,(void const *__restrict __haystack, int __byte),rawmemrxchr,(__haystack,__byte))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrxchr */
#include <local/string/rawmemrxchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrb)(void *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchr))(__haystack, __byte); }
/* Same as `rawmemrchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrxchrb)(void const *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchr))(__haystack, __byte); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrb)(void const *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchr))(__haystack, __byte); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrxchr */
#ifdef __CRT_HAVE_rawmemrxchrw
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemrxchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word),rawmemrxchrw,(__haystack,__word))
/* Same as `rawmemrchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,rawmemrxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),rawmemrxchrw,(__haystack,__word))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchrw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemrxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),(__haystack,__word))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrxchrw */
#include <local/string/rawmemrxchrw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrw))(__haystack, __word); }
/* Same as `rawmemrchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrw))(__haystack, __word); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchrw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxchrw, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrw))(__haystack, __word); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrxchrw */
#ifdef __CRT_HAVE_rawmemrxchrl
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemrxchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword),rawmemrxchrl,(__haystack,__dword))
/* Same as `rawmemrchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,rawmemrxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),rawmemrxchrl,(__haystack,__dword))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchrl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemrxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),(__haystack,__dword))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrxchrl */
#include <local/string/rawmemrxchrl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrl))(__haystack, __dword); }
/* Same as `rawmemrchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrl))(__haystack, __dword); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchrl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxchrl, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrl))(__haystack, __dword); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrxchrl */
#ifdef __CRT_HAVE_memxend
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memxendb,(void *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memxend,(__haystack,__byte,__n_bytes))
/* Same as `memendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memxendb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memxend,(__haystack,__byte,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memxendb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memxend,(__haystack,__byte,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxend */
#include <local/string/memxend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memendb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendb)(void *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))(__haystack, __byte, __n_bytes); }
/* Same as `memendb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxendb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))(__haystack, __byte, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memendb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))(__haystack, __byte, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxend */
#ifdef __CRT_HAVE_memxendw
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memendw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memxendw,(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_bytes),memxendw,(__haystack,__word,__n_bytes))
/* Same as `memendw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,memxendw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_bytes),memxendw,(__haystack,__word,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memendw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memxendw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_bytes),(__haystack,__word,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxendw */
#include <local/string/memxendw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memendw', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendw)(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendw))(__haystack, __word, __n_bytes); }
/* Same as `memendw', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendw))(__haystack, __word, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memendw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxendw, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendw))(__haystack, __word, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxendw */
#ifdef __CRT_HAVE_memxendl
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memendl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memxendl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_bytes),memxendl,(__haystack,__dword,__n_bytes))
/* Same as `memendl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,memxendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_bytes),memxendl,(__haystack,__dword,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memendl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memxendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_bytes),(__haystack,__dword,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxendl */
#include <local/string/memxendl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memendl', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendl))(__haystack, __dword, __n_bytes); }
/* Same as `memendl', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendl))(__haystack, __dword, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memendl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxendl, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendl))(__haystack, __dword, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxendl */
#ifdef __CRT_HAVE_memrxend
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrxendb,(void *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memrxend,(__haystack,__byte,__n_bytes))
/* Same as `memrendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memrxendb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memrxend,(__haystack,__byte,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrxendb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memrxend,(__haystack,__byte,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxend */
#include <local/string/memrxend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrendb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendb)(void *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))(__haystack, __byte, __n_bytes); }
/* Same as `memrendb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxendb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))(__haystack, __byte, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrendb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))(__haystack, __byte, __n_bytes); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxend */
#ifdef __CRT_HAVE_memrxendw
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrendw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memrxendw,(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memrxendw,(__haystack,__word,__n_words))
/* Same as `memrendw', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,memrxendw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memrxendw,(__haystack,__word,__n_words))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrendw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memrxendw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),(__haystack,__word,__n_words))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxendw */
#include <local/string/memrxendw.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrendw', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendw)(void *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendw))(__haystack, __word, __n_words); }
/* Same as `memrendw', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendw))(__haystack, __word, __n_words); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrendw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxendw, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendw))(__haystack, __word, __n_words); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxendw */
#ifdef __CRT_HAVE_memrxendl
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrendl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memrxendl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memrxendl,(__haystack,__dword,__n_dwords))
/* Same as `memrendl', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,memrxendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memrxendl,(__haystack,__dword,__n_dwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrendl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memrxendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),(__haystack,__dword,__n_dwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxendl */
#include <local/string/memrxendl.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrendl', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendl))(__haystack, __dword, __n_dwords); }
/* Same as `memrendl', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendl))(__haystack, __dword, __n_dwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrendl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxendl, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendl))(__haystack, __dword, __n_dwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxendl */
#ifdef __CRT_HAVE_memxlen
/* Same as `memlenb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memxlenb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memxlen,(__haystack,__byte,__n_bytes))
#else /* __CRT_HAVE_memxlen */
#include <local/string/memxlen.h>
/* Same as `memlenb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memxlenb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxlen))(__haystack, __byte, __n_bytes); }
#endif /* !__CRT_HAVE_memxlen */
#ifdef __CRT_HAVE_memxlenw
/* Same as `memlenw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memxlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),(__haystack,__word,__n_words))
#else /* __CRT_HAVE_memxlenw */
#include <local/string/memxlenw.h>
/* Same as `memlenw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxlenw, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memxlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxlenw))(__haystack, __word, __n_words); })
#endif /* !__CRT_HAVE_memxlenw */
#ifdef __CRT_HAVE_memxlenl
/* Same as `memlenl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memxlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),(__haystack,__dword,__n_dwords))
#else /* __CRT_HAVE_memxlenl */
#include <local/string/memxlenl.h>
/* Same as `memlenl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxlenl, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memxlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxlenl))(__haystack, __dword, __n_dwords); })
#endif /* !__CRT_HAVE_memxlenl */
#ifdef __CRT_HAVE_memrxlen
/* Same as `memrlenb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memrxlenb,(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes),memrxlen,(__haystack,__byte,__n_bytes))
#else /* __CRT_HAVE_memrxlen */
#include <local/string/memrxlen.h>
/* Same as `memrlenb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrxlenb)(void const *__restrict __haystack, int __byte, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxlen))(__haystack, __byte, __n_bytes); }
#endif /* !__CRT_HAVE_memrxlen */
#ifdef __CRT_HAVE_memrxlenw
/* Same as `memrlenw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memrxlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),(__haystack,__word,__n_words))
#else /* __CRT_HAVE_memrxlenw */
#include <local/string/memrxlenw.h>
/* Same as `memrlenw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxlenw, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrxlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxlenw))(__haystack, __word, __n_words); })
#endif /* !__CRT_HAVE_memrxlenw */
#ifdef __CRT_HAVE_memrxlenl
/* Same as `memrlenl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memrxlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),(__haystack,__dword,__n_dwords))
#else /* __CRT_HAVE_memrxlenl */
#include <local/string/memrxlenl.h>
/* Same as `memrlenl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxlenl, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrxlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxlenl))(__haystack, __dword, __n_dwords); })
#endif /* !__CRT_HAVE_memrxlenl */
#ifdef __CRT_HAVE_rawmemxlen
/* Same as `rawmemlenb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemxlenb,(void const *__restrict __haystack, int __needle),rawmemxlen,(__haystack,__needle))
#else /* __CRT_HAVE_rawmemxlen */
#include <local/string/rawmemxlen.h>
/* Same as `rawmemlenb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemxlenb)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxlen))(__haystack, __needle); }
#endif /* !__CRT_HAVE_rawmemxlen */
#ifdef __CRT_HAVE_rawmemxlenw
/* Same as `rawmemlenw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemxlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),(__haystack,__word))
#else /* __CRT_HAVE_rawmemxlenw */
#include <local/string/rawmemxlenw.h>
/* Same as `rawmemlenw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxlenw, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemxlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxlenw))(__haystack, __word); })
#endif /* !__CRT_HAVE_rawmemxlenw */
#ifdef __CRT_HAVE_rawmemxlenl
/* Same as `rawmemlenl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemxlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),(__haystack,__dword))
#else /* __CRT_HAVE_rawmemxlenl */
#include <local/string/rawmemxlenl.h>
/* Same as `rawmemlenl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxlenl, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemxlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxlenl))(__haystack, __dword); })
#endif /* !__CRT_HAVE_rawmemxlenl */
#ifdef __CRT_HAVE_rawmemrxlen
/* Same as `rawmemrlenb', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrxlenb,(void const *__restrict __haystack, int __needle),rawmemrxlen,(__haystack,__needle))
#else /* __CRT_HAVE_rawmemrxlen */
#include <local/string/rawmemrxlen.h>
/* Same as `rawmemrlenb', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrxlenb)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxlen))(__haystack, __needle); }
#endif /* !__CRT_HAVE_rawmemrxlen */
#ifdef __CRT_HAVE_rawmemrxlenw
/* Same as `rawmemrlenw', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrxlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),(__haystack,__word))
#else /* __CRT_HAVE_rawmemrxlenw */
#include <local/string/rawmemrxlenw.h>
/* Same as `rawmemrlenw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxlenw, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrxlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxlenw))(__haystack, __word); })
#endif /* !__CRT_HAVE_rawmemrxlenw */
#ifdef __CRT_HAVE_rawmemrxlenl
/* Same as `rawmemrlenl', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrxlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),(__haystack,__dword))
#else /* __CRT_HAVE_rawmemrxlenl */
#include <local/string/rawmemrxlenl.h>
/* Same as `rawmemrlenl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxlenl, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrxlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxlenl))(__haystack, __dword); })
#endif /* !__CRT_HAVE_rawmemrxlenl */
#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE_memxchrq
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memxchrq,(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memxchrq,(__haystack,__qword,__n_qwords))
/* Same as `memchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,memxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memxchrq,(__haystack,__qword,__n_qwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),(__haystack,__qword,__n_qwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxchrq */
#include <local/string/memxchrq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrq))(__haystack, __qword, __n_qwords); }
/* Same as `memchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrq))(__haystack, __qword, __n_qwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchrq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxchrq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrq))(__haystack, __qword, __n_qwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxchrq */
#ifdef __CRT_HAVE_memrxchrq
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memrxchrq,(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memrxchrq,(__haystack,__qword,__n_qwords))
/* Same as `memrchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,memrxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memrxchrq,(__haystack,__qword,__n_qwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memrxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),(__haystack,__qword,__n_qwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxchrq */
#include <local/string/memrxchrq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrq))(__haystack, __qword, __n_qwords); }
/* Same as `memrchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrq))(__haystack, __qword, __n_qwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchrq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxchrq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrq))(__haystack, __qword, __n_qwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxchrq */
#ifdef __CRT_HAVE_rawmemxchrq
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemxchrq,(void *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemxchrq,(__haystack,__qword))
/* Same as `rawmemchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,rawmemxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemxchrq,(__haystack,__qword))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchrq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),(__haystack,__qword))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemxchrq */
#include <local/string/rawmemxchrq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrq))(__haystack, __qword); }
/* Same as `rawmemchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrq))(__haystack, __qword); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemchrq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxchrq, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrq))(__haystack, __qword); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemxchrq */
#ifdef __CRT_HAVE_rawmemrxchrq
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemrxchrq,(void *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemrxchrq,(__haystack,__qword))
/* Same as `rawmemrchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,rawmemrxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemrxchrq,(__haystack,__qword))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchrq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemrxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),(__haystack,__qword))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrxchrq */
#include <local/string/rawmemrxchrq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `rawmemrchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrq))(__haystack, __qword); }
/* Same as `rawmemrchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrq))(__haystack, __qword); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `rawmemrchrq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxchrq, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrq))(__haystack, __qword); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrxchrq */
#ifdef __CRT_HAVE_memxendq
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memendq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memxendq,(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_bytes),memxendq,(__haystack,__qword,__n_bytes))
/* Same as `memendq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,memxendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_bytes),memxendq,(__haystack,__qword,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memendq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memxendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_bytes),(__haystack,__qword,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memxendq */
#include <local/string/memxendq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memendq', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendq))(__haystack, __qword, __n_bytes); }
/* Same as `memendq', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendq))(__haystack, __qword, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memendq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxendq, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendq))(__haystack, __qword, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memxendq */
#ifdef __CRT_HAVE_memrxendq
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrendq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memrxendq,(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memrxendq,(__haystack,__qword,__n_qwords))
/* Same as `memrendq', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,memrxendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memrxendq,(__haystack,__qword,__n_qwords))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrendq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memrxendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),(__haystack,__qword,__n_qwords))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_memrxendq */
#include <local/string/memrxendq.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrendq', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendq))(__haystack, __qword, __n_qwords); }
/* Same as `memrendq', but search for non-matching locations. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendq))(__haystack, __qword, __n_qwords); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrendq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxendq, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendq))(__haystack, __qword, __n_qwords); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_memrxendq */
#ifdef __CRT_HAVE_memxlenq
/* Same as `memlenq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memxlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),(__haystack,__qword,__n_qwords))
#else /* __CRT_HAVE_memxlenq */
#include <local/string/memxlenq.h>
/* Same as `memlenq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxlenq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memxlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxlenq))(__haystack, __qword, __n_qwords); })
#endif /* !__CRT_HAVE_memxlenq */
#ifdef __CRT_HAVE_memrxlenq
/* Same as `memrlenq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memrxlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),(__haystack,__qword,__n_qwords))
#else /* __CRT_HAVE_memrxlenq */
#include <local/string/memrxlenq.h>
/* Same as `memrlenq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxlenq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrxlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxlenq))(__haystack, __qword, __n_qwords); })
#endif /* !__CRT_HAVE_memrxlenq */
#ifdef __CRT_HAVE_rawmemxlenq
/* Same as `rawmemlenq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemxlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),(__haystack,__qword))
#else /* __CRT_HAVE_rawmemxlenq */
#include <local/string/rawmemxlenq.h>
/* Same as `rawmemlenq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxlenq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemxlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxlenq))(__haystack, __qword); })
#endif /* !__CRT_HAVE_rawmemxlenq */
#ifdef __CRT_HAVE_rawmemrxlenq
/* Same as `rawmemrlenq', but search for non-matching locations. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrxlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),(__haystack,__qword))
#else /* __CRT_HAVE_rawmemrxlenq */
#include <local/string/rawmemrxlenq.h>
/* Same as `rawmemrlenq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxlenq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrxlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxlenq))(__haystack, __qword); })
#endif /* !__CRT_HAVE_rawmemrxlenq */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */
#endif /* __USE_STRING_XCHR */





#ifdef __USE_KOS
#ifdef __fast_memmoveup_defined
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
__NAMESPACE_FAST_USING_OR_IMPL(memmoveup, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmoveup)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveup))(__dst, __src, __n_bytes); })
#elif defined(__CRT_HAVE_memmoveup)
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),(__dst,__src,__n_bytes))
#else /* ... */
#include <local/string/memmoveup.h>
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmoveup, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmoveup)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveup))(__dst, __src, __n_bytes); })
#endif /* !... */
#ifdef __fast_memmovedown_defined
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
__NAMESPACE_FAST_USING_OR_IMPL(memmovedown, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmovedown)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedown))(__dst, __src, __n_bytes); })
#elif defined(__CRT_HAVE_memmovedown)
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),(__dst,__src,__n_bytes))
#else /* ... */
#include <local/string/memmovedown.h>
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmovedown, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmovedown)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedown))(__dst, __src, __n_bytes); })
#endif /* !... */
#ifdef __fast_memcpyc_defined
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__NAMESPACE_FAST_USING_OR_IMPL(memcpyc, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memcpyc)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyc))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__CRT_HAVE_memcpyc)
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__src,__elem_count,__elem_size))
#else /* ... */
#include <local/string/memcpyc.h>
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpyc, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memcpyc)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyc))(__dst, __src, __elem_count, __elem_size); })
#endif /* !... */
#ifdef __fast_mempcpyc_defined
/* Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempcpyc, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempcpyc)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyc))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__CRT_HAVE_mempcpyc)
/* Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__src,__elem_count,__elem_size))
#else /* ... */
#include <local/string/mempcpyc.h>
/* Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempcpyc, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempcpyc)(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyc))(__dst, __src, __elem_count, __elem_size); })
#endif /* !... */
#ifdef __fast_memmovec_defined
/* Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
__NAMESPACE_FAST_USING_OR_IMPL(memmovec, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmovec)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovec))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__CRT_HAVE_memmovec)
/* Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmovec,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__src,__elem_count,__elem_size))
#else /* ... */
#include <local/string/memmovec.h>
/* Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmovec, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmovec)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovec))(__dst, __src, __elem_count, __elem_size); })
#endif /* !... */
#ifdef __fast_mempmovec_defined
/* Same as `memmovec', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempmovec, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmovec)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovec))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__CRT_HAVE_mempmovec)
/* Same as `memmovec', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmovec,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__src,__elem_count,__elem_size))
#else /* ... */
#include <local/string/mempmovec.h>
/* Same as `memmovec', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmovec, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmovec)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovec))(__dst, __src, __elem_count, __elem_size); })
#endif /* !... */
#ifdef __fast_memmoveupc_defined
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__NAMESPACE_FAST_USING_OR_IMPL(memmoveupc, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmoveupc)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupc))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__CRT_HAVE_memmoveupc)
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmoveupc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__src,__elem_count,__elem_size))
#else /* ... */
#include <local/string/memmoveupc.h>
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmoveupc, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmoveupc)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupc))(__dst, __src, __elem_count, __elem_size); })
#endif /* !... */
#ifdef __fast_mempmoveupc_defined
/* Same as `memmoveupc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE') */
__NAMESPACE_FAST_USING_OR_IMPL(mempmoveupc, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmoveupc)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupc))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__CRT_HAVE_mempmoveupc)
/* Same as `memmoveupc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE') */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmoveupc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__src,__elem_count,__elem_size))
#else /* ... */
#include <local/string/mempmoveupc.h>
/* Same as `memmoveupc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmoveupc, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmoveupc)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveupc))(__dst, __src, __elem_count, __elem_size); })
#endif /* !... */
#ifdef __fast_memmovedownc_defined
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__NAMESPACE_FAST_USING_OR_IMPL(memmovedownc, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmovedownc)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownc))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__CRT_HAVE_memmovedownc)
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmovedownc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__src,__elem_count,__elem_size))
#else /* ... */
#include <local/string/memmovedownc.h>
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmovedownc, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmovedownc)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownc))(__dst, __src, __elem_count, __elem_size); })
#endif /* !... */
#ifdef __fast_mempmovedownc_defined
/* Same as `memmovedownc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE') */
__NAMESPACE_FAST_USING_OR_IMPL(mempmovedownc, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmovedownc)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownc))(__dst, __src, __elem_count, __elem_size); })
#elif defined(__CRT_HAVE_mempmovedownc)
/* Same as `memmovedownc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE') */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmovedownc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__src,__elem_count,__elem_size))
#else /* ... */
#include <local/string/mempmovedownc.h>
/* Same as `memmovedownc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmovedownc, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmovedownc)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedownc))(__dst, __src, __elem_count, __elem_size); })
#endif /* !... */
#ifdef __CRT_HAVE_strend
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `STR + strlen(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strend,(char *__restrict __string),strend,(__string))
/* Same as `STR + strlen(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strend,(char const *__restrict __string),strend,(__string))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `STR + strlen(STR)' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strend,(char const *__restrict __string),(__string))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strend */
#include <local/string/strend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `STR + strlen(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strend)(char *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strend))(__string); }
/* Same as `STR + strlen(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strend)(char const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strend))(__string); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `STR + strlen(STR)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strend, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strend)(char const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strend))(__string); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strend */
#ifdef __CRT_HAVE_strnend
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `STR + strnlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnend,(char *__restrict __string, __SIZE_TYPE__ __maxlen),strnend,(__string,__maxlen))
/* Same as `STR + strnlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strnend,(char const *__restrict __string, __SIZE_TYPE__ __maxlen),strnend,(__string,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `STR + strnlen(STR, MAX_CHARS)' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnend,(char const *__restrict __string, __SIZE_TYPE__ __maxlen),(__string,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strnend */
#include <local/string/strnend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `STR + strnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnend)(char *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnend))(__string, __maxlen); }
/* Same as `STR + strnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strnend)(char const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnend))(__string, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `STR + strnlen(STR, MAX_CHARS)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnend, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnend)(char const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnend))(__string, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strnend */
#ifdef __CRT_HAVE_strnchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `strchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnchr,(char *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),strnchr,(__haystack,__needle,__maxlen))
/* Same as `strchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strnchr,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),strnchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `strchr', but don't exceed `MAX_CHARS' characters. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnchr,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strnchr */
#include <local/string/strnchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `strchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnchr)(char *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnchr))(__haystack, __needle, __maxlen); }
/* Same as `strchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strnchr)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `strchr', but don't exceed `MAX_CHARS' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnchr)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnchr))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strnchr */
#ifdef __CRT_HAVE_strnrchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `strrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnrchr,(char *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),strnrchr,(__haystack,__needle,__maxlen))
/* Same as `strrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strnrchr,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),strnrchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `strrchr', but don't exceed `MAX_CHARS' characters. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnrchr,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strnrchr */
#include <local/string/strnrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `strrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnrchr)(char *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchr))(__haystack, __needle, __maxlen); }
/* Same as `strrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strnrchr)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `strrchr', but don't exceed `MAX_CHARS' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnrchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnrchr)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchr))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strnrchr */
#ifdef __CRT_HAVE_strrchrnul
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `strrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strrchrnul,(char *__restrict __haystack, int __needle),strrchrnul,(__haystack,__needle))
/* Same as `strrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strrchrnul,(char const *__restrict __haystack, int __needle),strrchrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `strrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strrchrnul,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strrchrnul */
#include <local/string/strrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `strrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strrchrnul)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchrnul))(__haystack, __needle); }
/* Same as `strrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strrchrnul)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `strrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strrchrnul, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strrchrnul)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchrnul))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strrchrnul */
#ifdef __CRT_HAVE_strnchrnul
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnchrnul,(char *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),strnchrnul,(__haystack,__needle,__maxlen))
/* Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strnchrnul,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),strnchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnchrnul,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strnchrnul */
#include <local/string/strnchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnchrnul)(char *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnchrnul))(__haystack, __needle, __maxlen); }
/* Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strnchrnul)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnchrnul, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnchrnul)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnchrnul))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strnchrnul */
#ifdef __CRT_HAVE_strnrchrnul
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `strnrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnrchrnul,(char *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),strnrchrnul,(__haystack,__needle,__maxlen))
/* Same as `strnrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strnrchrnul,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),strnrchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `strnrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnrchrnul,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strnrchrnul */
#include <local/string/strnrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `strnrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnrchrnul)(char *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchrnul))(__haystack, __needle, __maxlen); }
/* Same as `strnrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strnrchrnul)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `strnrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnrchrnul, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnrchrnul)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchrnul))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strnrchrnul */
#ifdef __CRT_HAVE_stroff
/* Same as `strchrnul', but return the offset from `STR', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,stroff,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* __CRT_HAVE_stroff */
#include <local/string/stroff.h>
/* Same as `strchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(stroff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL stroff)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stroff))(__haystack, __needle); })
#endif /* !__CRT_HAVE_stroff */
#ifdef __CRT_HAVE_strroff
/* Same as `strrchrnul', but return the offset from `STR', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,strroff,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* __CRT_HAVE_strroff */
#include <local/string/strroff.h>
/* Same as `strrchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(strroff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strroff)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strroff))(__haystack, __needle); })
#endif /* !__CRT_HAVE_strroff */
#ifdef __CRT_HAVE_strnoff
/* Same as `strnchrnul', but return the offset from `STR', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,strnoff,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#else /* __CRT_HAVE_strnoff */
#include <local/string/strnoff.h>
/* Same as `strnchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnoff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strnoff)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnoff))(__haystack, __needle, __maxlen); })
#endif /* !__CRT_HAVE_strnoff */
#ifdef __CRT_HAVE_strnroff
/* Same as `strnrchrnul', but return the offset from `STR', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,strnroff,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#else /* __CRT_HAVE_strnroff */
#include <local/string/strnroff.h>
/* Same as `strnrchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnroff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strnroff)(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnroff))(__haystack, __needle, __maxlen); })
#endif /* !__CRT_HAVE_strnroff */
#ifdef __fast_mempset_defined
/* Same as `memset', but return `DST + N_BYTES', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempset, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempset)(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempset))(__dst, __byte, __n_bytes); })
#elif defined(__CRT_HAVE_mempset)
/* Same as `memset', but return `DST + N_BYTES', rather than `DST' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),(__dst,__byte,__n_bytes))
#else /* ... */
#include <local/string/mempset.h>
/* Same as `memset', but return `DST + N_BYTES', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempset, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempset)(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempset))(__dst, __byte, __n_bytes); })
#endif /* !... */
#ifdef __fast_mempmove_defined
/* Same as `memmove', but return `DST + N_BYTES', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempmove, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmove)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmove))(__dst, __src, __n_bytes); })
#elif defined(__CRT_HAVE_mempmove)
/* Same as `memmove', but return `DST + N_BYTES', rather than `DST' */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmove,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),(__dst,__src,__n_bytes))
#else /* ... */
#include <local/string/mempmove.h>
/* Same as `memmove', but return `DST + N_BYTES', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmove, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmove)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmove))(__dst, __src, __n_bytes); })
#endif /* !... */
#ifdef __fast_mempmoveup_defined
/* Same as `memmoveup', but return `DST + N_BYTES', rather than `DST' (assumes that `DST >= SRC || !N_BYTES') */
__NAMESPACE_FAST_USING_OR_IMPL(mempmoveup, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmoveup)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveup))(__dst, __src, __n_bytes); })
#elif defined(__CRT_HAVE_mempmoveup)
/* Same as `memmoveup', but return `DST + N_BYTES', rather than `DST' (assumes that `DST >= SRC || !N_BYTES') */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),(__dst,__src,__n_bytes))
#else /* ... */
#include <local/string/mempmoveup.h>
/* Same as `memmoveup', but return `DST + N_BYTES', rather than `DST' (assumes that `DST >= SRC || !N_BYTES') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmoveup, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmoveup)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveup))(__dst, __src, __n_bytes); })
#endif /* !... */
#ifdef __fast_mempmovedown_defined
/* Same as `memmovedown', but return `DST + N_BYTES', rather than `DST' (assumes that `DST <= SRC || !N_BYTES') */
__NAMESPACE_FAST_USING_OR_IMPL(mempmovedown, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmovedown)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedown))(__dst, __src, __n_bytes); })
#elif defined(__CRT_HAVE_mempmovedown)
/* Same as `memmovedown', but return `DST + N_BYTES', rather than `DST' (assumes that `DST <= SRC || !N_BYTES') */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),(__dst,__src,__n_bytes))
#else /* ... */
#include <local/string/mempmovedown.h>
/* Same as `memmovedown', but return `DST + N_BYTES', rather than `DST' (assumes that `DST <= SRC || !N_BYTES') */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmovedown, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmovedown)(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedown))(__dst, __src, __n_bytes); })
#endif /* !... */
#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
extern "C++" {
#ifdef __CRT_HAVE_mempmovec
/* Same as `memmovec', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmove,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempmovec,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_mempmovec */
} /* extern "C++" */
#include <local/string/mempmovec.h>
extern "C++" {
/* Same as `memmovec', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmove)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovec))(__dst, __src, __elem_count, __elem_size); }
#endif /* !__CRT_HAVE_mempmovec */
#ifdef __CRT_HAVE_mempmoveupc
/* Same as `memmoveupc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempmoveupc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_mempmoveupc */
} /* extern "C++" */
#include <local/string/mempmoveupc.h>
extern "C++" {
/* Same as `memmoveupc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE') */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmoveup)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveupc))(__dst, __src, __elem_count, __elem_size); }
#endif /* !__CRT_HAVE_mempmoveupc */
#ifdef __CRT_HAVE_mempmovedownc
/* Same as `memmovedownc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempmovedownc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_mempmovedownc */
} /* extern "C++" */
#include <local/string/mempmovedownc.h>
extern "C++" {
/* Same as `memmovedownc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE') */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmovedown)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedownc))(__dst, __src, __elem_count, __elem_size); }
#endif /* !__CRT_HAVE_mempmovedownc */
#ifdef __CRT_HAVE_memmoveupc
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmoveupc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memmoveupc */
} /* extern "C++" */
#include <local/string/memmoveupc.h>
extern "C++" {
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmoveup)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupc))(__dst, __src, __elem_count, __elem_size); }
#endif /* !__CRT_HAVE_memmoveupc */
#ifdef __CRT_HAVE_memmovedownc
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmovedownc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memmovedownc */
} /* extern "C++" */
#include <local/string/memmovedownc.h>
extern "C++" {
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmovedown)(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownc))(__dst, __src, __elem_count, __elem_size); }
#endif /* !__CRT_HAVE_memmovedownc */
} /* extern "C++" */
#endif /* __cplusplus && __USE_STRING_OVERLOADS */
#ifdef __CRT_HAVE_rawmemrchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchr' without a search limit, starting at `HAYSTACK - 1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemrchr,(void *__restrict __haystack, int __needle),rawmemrchr,(__haystack,__needle))
/* Same as `memrchr' without a search limit, starting at `HAYSTACK - 1' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,rawmemrchr,(void const *__restrict __haystack, int __needle),rawmemrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchr' without a search limit, starting at `HAYSTACK - 1' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemrchr,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_rawmemrchr */
#include <local/string/rawmemrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchr' without a search limit, starting at `HAYSTACK - 1' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemrchr)(void *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchr))(__haystack, __needle); }
/* Same as `memrchr' without a search limit, starting at `HAYSTACK - 1' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL rawmemrchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchr' without a search limit, starting at `HAYSTACK - 1' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrchr, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemrchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_rawmemrchr */
#ifdef __fast_memend_defined
/* Same as `memchr', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __cplusplus
__NAMESPACE_FAST_USING(memend)
#else /* __cplusplus */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memend)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __needle, __n_bytes); }
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __needle, __n_bytes); }
#endif /* !__cplusplus */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_FAST_USING_OR_IMPL(memend, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchr', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memend,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memend,(__haystack,__needle,__n_bytes))
/* Same as `memchr', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memend,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchr', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/memend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memchr', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memend)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))(__haystack, __needle, __n_bytes); }
/* Same as `memchr', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memchr', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memend, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __fast_memrend_defined
/* Same as `memrchr', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found. */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __cplusplus
__NAMESPACE_FAST_USING(memrend)
#else /* __cplusplus */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrend)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __needle, __n_bytes); }
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memrend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __needle, __n_bytes); }
#endif /* !__cplusplus */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_FAST_USING_OR_IMPL(memrend, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memrend)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchr', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrend,(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrend,(__haystack,__needle,__n_bytes))
/* Same as `memrchr', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memrend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrend,(__haystack,__needle,__n_bytes))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchr', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/memrend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Same as `memrchr', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrend)(void *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))(__haystack, __needle, __n_bytes); }
/* Same as `memrchr', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memrend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))(__haystack, __needle, __n_bytes); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Same as `memrchr', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrend, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrend)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))(__haystack, __needle, __n_bytes); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __fast_memlen_defined
/* Same as `memend', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `n_bytes' if the given `NEEDLE' wasn't found */
__NAMESPACE_FAST_USING_OR_IMPL(memlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memlen)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memlen))(__haystack, __needle, __n_bytes); })
#elif defined(__CRT_HAVE_memlen)
/* Same as `memend', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `n_bytes' if the given `NEEDLE' wasn't found */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memlen,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#else /* ... */
#include <local/string/memlen.h>
/* Same as `memend', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `n_bytes' if the given `NEEDLE' wasn't found */
__NAMESPACE_LOCAL_USING_OR_IMPL(memlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memlen)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlen))(__haystack, __needle, __n_bytes); })
#endif /* !... */
#ifdef __fast_memrlen_defined
/* Same as `memrend', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1' if the given `NEEDLE' wasn't found */
__NAMESPACE_FAST_USING_OR_IMPL(memrlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrlen)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrlen))(__haystack, __needle, __n_bytes); })
#elif defined(__CRT_HAVE_memrlen)
/* Same as `memrend', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1' if the given `NEEDLE' wasn't found */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,memrlen,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),(__haystack,__needle,__n_bytes))
#else /* ... */
#include <local/string/memrlen.h>
/* Same as `memrend', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1' if the given `NEEDLE' wasn't found */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL memrlen)(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlen))(__haystack, __needle, __n_bytes); })
#endif /* !... */
#ifdef __CRT_HAVE_rawmemlen
/* Same as `rawmemchr', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemlen,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* __CRT_HAVE_rawmemlen */
#include <local/string/rawmemlen.h>
/* Same as `rawmemchr', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemlen)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemlen))(__haystack, __needle); })
#endif /* !__CRT_HAVE_rawmemlen */
#ifdef __CRT_HAVE_rawmemrlen
/* Same as `rawmemrchr', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,rawmemrlen,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* __CRT_HAVE_rawmemrlen */
#include <local/string/rawmemrlen.h>
/* Same as `rawmemrchr', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL rawmemrlen)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrlen))(__haystack, __needle); })
#endif /* !__CRT_HAVE_rawmemrlen */
#if defined(__CRT_HAVE_memrmem0) && defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memrmem,(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memrmem0,(__haystack,__haystacklen,__needle,__needlelen))
/* Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memrmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memrmem0,(__haystack,__haystacklen,__needle,__needlelen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memrmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memrmem0,(__haystack,__haystacklen,__needle,__needlelen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memrmem) && !defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memrmem,(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memrmem,(__haystack,__haystacklen,__needle,__needlelen))
/* Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memrmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memrmem,(__haystack,__haystacklen,__needle,__needlelen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memrmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),(__haystack,__haystacklen,__needle,__needlelen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/memrmem.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memrmem)(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrmem))(__haystack, __haystacklen, __needle, __needlelen); }
/* Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) void const *__NOTHROW_NCX(__LIBCCALL memrmem)(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrmem))(__haystack, __haystacklen, __needle, __needlelen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrmem, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memrmem)(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrmem))(__haystack, __haystacklen, __needle, __needlelen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_memset
/* Same as `memsetb', but repeat a 1-byte pattern on aligned addresses. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempatb,(void *__restrict __dst, int __pattern, __SIZE_TYPE__ __n_bytes),memset,(__dst,__pattern,__n_bytes))
#else /* __CRT_HAVE_memset */
#include <local/string/memset.h>
/* Same as `memsetb', but repeat a 1-byte pattern on aligned addresses. */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatb)(void *__restrict __dst, int __pattern, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memset))(__dst, __pattern, (__SIZE_TYPE__)__n_bytes); }
#endif /* !__CRT_HAVE_memset */
#ifdef __fast_mempatw_defined
/* Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
__NAMESPACE_FAST_USING_OR_IMPL(mempatw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatw)(void *__restrict __dst, __UINT16_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatw))(__dst, __pattern, __n_bytes); })
#elif defined(__CRT_HAVE_mempatw)
/* Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempatw,(void *__restrict __dst, __UINT16_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes),(__dst,__pattern,__n_bytes))
#else /* ... */
#include <local/string/mempatw.h>
/* Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempatw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatw)(void *__restrict __dst, __UINT16_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempatw))(__dst, __pattern, __n_bytes); })
#endif /* !... */
#ifdef __fast_mempatl_defined
/* Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
__NAMESPACE_FAST_USING_OR_IMPL(mempatl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatl)(void *__restrict __dst, __UINT32_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatl))(__dst, __pattern, __n_bytes); })
#elif defined(__CRT_HAVE_mempatl)
/* Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempatl,(void *__restrict __dst, __UINT32_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes),(__dst,__pattern,__n_bytes))
#else /* ... */
#include <local/string/mempatl.h>
/* Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempatl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatl)(void *__restrict __dst, __UINT32_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempatl))(__dst, __pattern, __n_bytes); })
#endif /* !... */
#ifdef __UINT64_TYPE__
#ifdef __fast_mempatq_defined
/* Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
__NAMESPACE_FAST_USING_OR_IMPL(mempatq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatq)(void *__restrict __dst, __UINT64_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatq))(__dst, __pattern, __n_bytes); })
#elif defined(__CRT_HAVE_mempatq)
/* Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempatq,(void *__restrict __dst, __UINT64_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes),(__dst,__pattern,__n_bytes))
#else /* ... */
#include <local/string/mempatq.h>
/* Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempatq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatq)(void *__restrict __dst, __UINT64_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempatq))(__dst, __pattern, __n_bytes); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */
#ifdef __CRT_HAVE_memcasecmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_memicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memicmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE__memicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),_memicmp,(__s1,__s2,__n_bytes))
#else /* ... */
#include <local/string/memcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memcasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memcasecmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp))(__s1, __s2, __n_bytes); })
#endif /* !... */
#if defined(__CRT_HAVE_memcasemem0) && defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem,(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memcasemem0,(__haystack,__haystacklen,__needle,__needlelen))
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memcasemem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memcasemem0,(__haystack,__haystacklen,__needle,__needlelen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memcasemem0,(__haystack,__haystacklen,__needle,__needlelen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memcasemem) && !defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem,(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memcasemem,(__haystack,__haystacklen,__needle,__needlelen))
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memcasemem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memcasemem,(__haystack,__haystacklen,__needle,__needlelen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),(__haystack,__haystacklen,__needle,__needlelen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/memcasemem.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memcasemem)(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasemem))(__haystack, __haystacklen, __needle, __needlelen); }
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) void const *__NOTHROW_NCX(__LIBCCALL memcasemem)(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasemem))(__haystack, __haystacklen, __needle, __needlelen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcasemem, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memcasemem)(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasemem))(__haystack, __haystacklen, __needle, __needlelen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_memcasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcasecmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes, __locale_t __locale),(__s1,__s2,__n_bytes,__locale))
#elif defined(__CRT_HAVE__memicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcasecmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes, __locale_t __locale),_memicmp_l,(__s1,__s2,__n_bytes,__locale))
#else /* ... */
#include <local/string/memcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memcasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memcasecmp_l)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp_l))(__s1, __s2, __n_bytes, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_memcasemem0_l) && defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored using the given `locale' (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem_l,(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen, __locale_t __locale),memcasemem0_l,(__haystack,__haystacklen,__needle,__needlelen,__locale))
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored using the given `locale' (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memcasemem_l,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen, __locale_t __locale),memcasemem0_l,(__haystack,__haystacklen,__needle,__needlelen,__locale))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored using the given `locale' (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem_l,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen, __locale_t __locale),memcasemem0_l,(__haystack,__haystacklen,__needle,__needlelen,__locale))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_memcasemem_l) && !defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored using the given `locale' (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem_l,(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen, __locale_t __locale),memcasemem_l,(__haystack,__haystacklen,__needle,__needlelen,__locale))
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored using the given `locale' (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memcasemem_l,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen, __locale_t __locale),memcasemem_l,(__haystack,__haystacklen,__needle,__needlelen,__locale))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored using the given `locale' (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem_l,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen, __locale_t __locale),(__haystack,__haystacklen,__needle,__needlelen,__locale))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <local/string/memcasemem_l.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored using the given `locale' (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memcasemem_l)(void *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasemem_l))(__haystack, __haystacklen, __needle, __needlelen, __locale); }
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored using the given `locale' (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) void const *__NOTHROW_NCX(__LIBCCALL memcasemem_l)(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasemem_l))(__haystack, __haystacklen, __needle, __needlelen, __locale); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored using the given `locale' (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcasemem_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memcasemem_l)(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasemem_l))(__haystack, __haystacklen, __needle, __needlelen, __locale); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_strcasestr_l
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strcasestr_l,(char *__haystack, char const *__needle, __locale_t __locale),strcasestr_l,(__haystack,__needle,__locale))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char const *,__NOTHROW_NCX,strcasestr_l,(char const *__haystack, char const *__needle, __locale_t __locale),strcasestr_l,(__haystack,__needle,__locale))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strcasestr_l,(char const *__haystack, char const *__needle, __locale_t __locale),(__haystack,__needle,__locale))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strcasestr_l */
#include <local/string/strcasestr_l.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strcasestr_l)(char *__haystack, char const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasestr_l))(__haystack, __needle, __locale); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char const *__NOTHROW_NCX(__LIBCCALL strcasestr_l)(char const *__haystack, char const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasestr_l))(__haystack, __needle, __locale); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasestr_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strcasestr_l)(char const *__haystack, char const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasestr_l))(__haystack, __needle, __locale); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strcasestr_l */
#endif /* __USE_XOPEN2K8 */



#ifdef __CRT_HAVE_strerror_s
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,strerror_s,(int __errnum),(__errnum))
#else /* __CRT_HAVE_strerror_s */
#include <local/string/strerror_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strerror_s, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(__LIBCCALL strerror_s)(int __errnum) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strerror_s))(__errnum); })
#endif /* !__CRT_HAVE_strerror_s */
#ifdef __CRT_HAVE_strerrorname_s
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,strerrorname_s,(int __errnum),(__errnum))
#else /* __CRT_HAVE_strerrorname_s */
#include <local/string/strerrorname_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strerrorname_s, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(__LIBCCALL strerrorname_s)(int __errnum) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strerrorname_s))(__errnum); })
#endif /* !__CRT_HAVE_strerrorname_s */
#ifdef __CRT_HAVE_strsignal_s
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,strsignal_s,(int __signum),(__signum))
#else /* __CRT_HAVE_strsignal_s */
#include <local/string/strsignal_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strsignal_s, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(__LIBCCALL strsignal_s)(int __signum) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strsignal_s))(__signum); })
#endif /* !__CRT_HAVE_strsignal_s */
#ifdef __CRT_HAVE_vstrdupf
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 0),char *,__NOTHROW_NCX,vstrdupf,(char const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)))
#include <local/string/vstrdupf.h>
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
__NAMESPACE_LOCAL_USING_OR_IMPL(vstrdupf, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 0) char *__NOTHROW_NCX(__LIBCCALL vstrdupf)(char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vstrdupf))(__format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE_strdupf
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
__LIBC __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 0) char *__NOTHROW_NCX(__VLIBCCALL strdupf)(char const *__restrict __format, ...) __CASMNAME_SAME("strdupf");
#elif defined(__CRT_HAVE_vstrdupf) || defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)))
#include <local/string/strdupf.h>
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(strdupf)
#else /* __cplusplus */
#define strdupf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strdupf))
#endif /* !__cplusplus */
#endif /* ... */
/* mstrdupa() & friends. */
#ifdef __INTELLISENSE__
#define mstrdupa  mstrdupa
#define mstrndupa mstrndupa
extern __ATTR_WUNUSED __ATTR_MALLOC __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(mstrdupa)(char const *__restrict __string);
extern __ATTR_WUNUSED __ATTR_MALLOC __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(mstrndupa)(char const *__restrict __string, __size_t __maxlen);
#elif defined(__NO_XBLOCK)
__FORCELOCAL __ATTR_WUNUSED __ATTR_MALLOC __ATTR_NONNULL((2)) char *
__NOTHROW_NCX(__LIBCCALL __mstrdupa_init)(void *__buf, char const *__restrict __string) {
#ifdef __malloca_mayfail
	if __likely(__buf)
#endif /* __malloca_mayfail */
	{
		__buf = __NAMESPACE_STD_SYM strcpy((char *)__buf, __string);
	}
	return (char *)__buf;
}
__FORCELOCAL __ATTR_WUNUSED __ATTR_MALLOC __ATTR_NONNULL((2)) char *
__NOTHROW_NCX(__LIBCCALL __mstrndupa_init)(void *__buf, char const *__restrict __string, __size_t __maxlen) {
#ifdef __malloca_mayfail
	if __likely(__buf)
#endif /* __malloca_mayfail */
	{
		__size_t __buflen = __NAMESPACE_STD_SYM strnlen(__string, __maxlen) * sizeof(char);
#ifdef __mempcpy_defined
		*(char *)mempcpy(__buf, __string, __buflen) = 0;
#else /* __mempcpy_defined */
		((char *)__NAMESPACE_STD_SYM memcpy(__buf, __string, __buflen))[__buflen] = 0;
#endif /* !__mempcpy_defined */
	}
	return (char *)__buf;
}
/* Without X-blocks, it's impossible to prevent multiple evaluations of the `string' argument... */
#define mstrdupa(string) \
	__mstrdupa_init(__malloca((__NAMESPACE_STD_SYM strlen(string) + 1) * sizeof(char)), string)
#define strndupa(string, maxlen) \
	__mstrndupa_init(__malloca((__NAMESPACE_STD_SYM strnlen(string, maxlen) + 1) * sizeof(char)), string, maxlen)
#else /* __NO_XBLOCK */
#ifdef __malloca_mayfail
#define mstrdupa(string)                                                                  \
	__XBLOCK({                                                                            \
		char const *__orig_s = (string);                                                  \
		__size_t __orig_len  = (__NAMESPACE_STD_SYM strlen(__orig_s) + 1) * sizeof(char); \
		char *__copy_s       = (char *)__malloca(__orig_len);                             \
		__XRETURN __likely(__copy_s)                                                      \
		          ? (char *)__NAMESPACE_STD_SYM memcpy(__copy_s, __orig_s, __orig_len)    \
		          : __copy_s;                                                             \
	})
#define mstrndupa(string, maxlen)                                                   \
	__XBLOCK({                                                                      \
		char const *__orig_s = (string);                                            \
		__size_t __orig_len  = __NAMESPACE_STD_SYM strlen(__orig_s) * sizeof(char); \
		char *__copy_s       = (char *)__malloca(__orig_len + sizeof(char));        \
		if __likely(__copy_s) {                                                     \
			__copy_s[__orig_len / sizeof(char)] = 0;                                \
			__NAMESPACE_STD_SYM memcpy(__copy_s, __orig_s, __orig_len);             \
		}                                                                           \
		__XRETURN __copy_s;                                                         \
	})
#else /* __malloca_mayfail */
#define mstrdupa(string)                                                                  \
	__XBLOCK({                                                                            \
		char const *__orig_s = (string);                                                  \
		__size_t __orig_len  = (__NAMESPACE_STD_SYM strlen(__orig_s) + 1) * sizeof(char); \
		char *__copy_s       = (char *)__malloca(__orig_len);                             \
		__XRETURN (char *)__NAMESPACE_STD_SYM memcpy(__copy_s, __orig_s, __orig_len);     \
	})
#define mstrndupa(string, maxlen)                                                     \
	__XBLOCK({                                                                        \
		char const *__orig_s = (string);                                              \
		__size_t __orig_len  = __NAMESPACE_STD_SYM strlen(__orig_s) * sizeof(char);   \
		char *__copy_s = (char *)__malloca(__orig_len + sizeof(char));                \
		__copy_s[__orig_len / sizeof(char)] = 0;                                      \
		__XRETURN (char *)__NAMESPACE_STD_SYM memcpy(__copy_s, __orig_s, __orig_len); \
	})
#endif /* !__malloca_mayfail */
#endif /* !__NO_XBLOCK */
#ifdef __CRT_HAVE_wildstrcmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildstrcmp,(char const *__pattern, char const *__string),(__pattern,__string))
#else /* __CRT_HAVE_wildstrcmp */
#include <local/string/wildstrcmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildstrcmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildstrcmp)(char const *__pattern, char const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildstrcmp))(__pattern, __string); })
#endif /* !__CRT_HAVE_wildstrcmp */
#ifdef __CRT_HAVE_wildstrcasecmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildstrcasecmp,(char const *__pattern, char const *__string),(__pattern,__string))
#else /* __CRT_HAVE_wildstrcasecmp */
#include <local/string/wildstrcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildstrcasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildstrcasecmp)(char const *__pattern, char const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildstrcasecmp))(__pattern, __string); })
#endif /* !__CRT_HAVE_wildstrcasecmp */
#ifdef __CRT_HAVE_fuzzy_strcmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_strcmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_fuzzy_memcmp) || !defined(__NO_MALLOCA)
#include <local/string/fuzzy_strcmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_strcmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_strcmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_strcmp))(__s1, __s2); })
#endif /* ... */
#ifdef __CRT_HAVE_fuzzy_strncmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_strncmp,(char const *__s1, __SIZE_TYPE__ __s1_maxlen, char const *__s2, __SIZE_TYPE__ __s2_maxlen),(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif defined(__CRT_HAVE_fuzzy_memcmp) || !defined(__NO_MALLOCA)
#include <local/string/fuzzy_strncmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_strncmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_strncmp)(char const *__s1, __SIZE_TYPE__ __s1_maxlen, char const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_strncmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* ... */
#ifdef __CRT_HAVE_fuzzy_strcasecmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_strcasecmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_fuzzy_memcasecmp) || !defined(__NO_MALLOCA)
#include <local/string/fuzzy_strcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_strcasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_strcasecmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_strcasecmp))(__s1, __s2); })
#endif /* ... */
#ifdef __CRT_HAVE_fuzzy_strncasecmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_strncasecmp,(char const *__s1, __SIZE_TYPE__ __s1_maxlen, char const *__s2, __SIZE_TYPE__ __s2_maxlen),(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif defined(__CRT_HAVE_fuzzy_memcasecmp) || !defined(__NO_MALLOCA)
#include <local/string/fuzzy_strncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_strncasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_strncasecmp)(char const *__s1, __SIZE_TYPE__ __s1_maxlen, char const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_strncasecmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* ... */
#ifdef __CRT_HAVE_fuzzy_memcmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_memcmp,(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes),(__s1,__s1_bytes,__s2,__s2_bytes))
#else /* __CRT_HAVE_fuzzy_memcmp */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <local/string/fuzzy_memcmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_memcmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_memcmp)(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmp))(__s1, __s1_bytes, __s2, __s2_bytes); })
#endif /* !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_memcmp */
#ifdef __CRT_HAVE_fuzzy_memcasecmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_memcasecmp,(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes),(__s1,__s1_bytes,__s2,__s2_bytes))
#else /* __CRT_HAVE_fuzzy_memcasecmp */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <local/string/fuzzy_memcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_memcasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_memcasecmp)(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcasecmp))(__s1, __s1_bytes, __s2, __s2_bytes); })
#endif /* !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_memcasecmp */
#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_fuzzy_strcasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_fuzzy_memcasecmp_l) || !defined(__NO_MALLOCA)
#include <local/string/fuzzy_strcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_strcasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_strcasecmp_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_strcasecmp_l))(__s1, __s2, __locale); })
#endif /* ... */
#ifdef __CRT_HAVE_fuzzy_strncasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_strncasecmp_l,(char const *__s1, __SIZE_TYPE__ __s1_maxlen, char const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#elif defined(__CRT_HAVE_fuzzy_memcasecmp_l) || !defined(__NO_MALLOCA)
#include <local/string/fuzzy_strncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_strncasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_strncasecmp_l)(char const *__s1, __SIZE_TYPE__ __s1_maxlen, char const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_strncasecmp_l))(__s1, __s1_maxlen, __s2, __s2_maxlen, __locale); })
#endif /* ... */
#ifdef __CRT_HAVE_wildstrcasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildstrcasecmp_l,(char const *__pattern, char const *__string, __locale_t __locale),(__pattern,__string,__locale))
#else /* __CRT_HAVE_wildstrcasecmp_l */
#include <local/string/wildstrcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildstrcasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildstrcasecmp_l)(char const *__pattern, char const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildstrcasecmp_l))(__pattern, __string, __locale); })
#endif /* !__CRT_HAVE_wildstrcasecmp_l */
#ifdef __CRT_HAVE_fuzzy_memcasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_memcasecmp_l,(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#else /* __CRT_HAVE_fuzzy_memcasecmp_l */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <local/string/fuzzy_memcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_memcasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_memcasecmp_l)(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcasecmp_l))(__s1, __s1_bytes, __s2, __s2_bytes, __locale); })
#endif /* !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_memcasecmp_l */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_STRING_BWLQ
#ifdef __CRT_HAVE_fuzzy_memcmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_memcmpb,(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_memcmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#else /* __CRT_HAVE_fuzzy_memcmp */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <local/string/fuzzy_memcmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_memcmpb)(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmp))(__s1, __s1_bytes, __s2, __s2_bytes); }
#endif /* !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_memcmp */
#ifdef __CRT_HAVE_fuzzy_memcmpw
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_memcmpw,(void const *__s1, __SIZE_TYPE__ __s1_words, void const *__s2, __SIZE_TYPE__ __s2_words),(__s1,__s1_words,__s2,__s2_words))
#elif defined(__CRT_HAVE_fuzzy_wmemcmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_memcmpw,(void const *__s1, __SIZE_TYPE__ __s1_words, void const *__s2, __SIZE_TYPE__ __s2_words),fuzzy_wmemcmp,(__s1,__s1_words,__s2,__s2_words))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcmp)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBCCALL,fuzzy_memcmpw,(void const *__s1, __SIZE_TYPE__ __s1_words, void const *__s2, __SIZE_TYPE__ __s2_words),DOS$fuzzy_wmemcmp,(__s1,__s1_words,__s2,__s2_words))
#else /* ... */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <local/string/fuzzy_memcmpw.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_memcmpw, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_memcmpw)(void const *__s1, __SIZE_TYPE__ __s1_words, void const *__s2, __SIZE_TYPE__ __s2_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpw))(__s1, __s1_words, __s2, __s2_words); })
#endif /* !__NO_MALLOCA */
#endif /* !... */
#ifdef __CRT_HAVE_fuzzy_memcmpl
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_memcmpl,(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords),(__s1,__s1_dwords,__s2,__s2_dwords))
#elif defined(__CRT_HAVE_fuzzy_wmemcmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_memcmpl,(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords),fuzzy_wmemcmp,(__s1,__s1_dwords,__s2,__s2_dwords))
#elif defined(__CRT_HAVE_KOS$fuzzy_wmemcmp) && defined(__PE__)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBCCALL,fuzzy_memcmpl,(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords),KOS$fuzzy_wmemcmp,(__s1,__s1_dwords,__s2,__s2_dwords))
#else /* ... */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <local/string/fuzzy_memcmpl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_memcmpl, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_memcmpl)(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpl))(__s1, __s1_dwords, __s2, __s2_dwords); })
#endif /* !__NO_MALLOCA */
#endif /* !... */
#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE_fuzzy_memcmpq
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_memcmpq,(void const *__s1, __SIZE_TYPE__ __s1_qwords, void const *__s2, __SIZE_TYPE__ __s2_qwords),(__s1,__s1_qwords,__s2,__s2_qwords))
#else /* __CRT_HAVE_fuzzy_memcmpq */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <local/string/fuzzy_memcmpq.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_memcmpq, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_memcmpq)(void const *__s1, __SIZE_TYPE__ __s1_qwords, void const *__s2, __SIZE_TYPE__ __s2_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpq))(__s1, __s1_qwords, __s2, __s2_qwords); })
#endif /* !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_memcmpq */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */
#ifdef __CRT_HAVE_strncoll
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strncoll,(__s1,__s2,__maxlen))
#else /* ... */
#include <local/string/strncoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncoll)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#ifdef __CRT_HAVE_strcasecoll
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE__stricoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),_stricoll,(__s1,__s2))
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#else /* ... */
#include <local/string/strcasecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasecoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcasecoll)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecoll))(__s1, __s2); })
#endif /* !... */
#ifdef __CRT_HAVE_strncasecoll
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#else /* ... */
#include <local/string/strncasecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncasecoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncasecoll)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#ifdef __CRT_HAVE_strnrev
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnrev,(char *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* __CRT_HAVE_strnrev */
#include <local/string/strnrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnrev, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnrev)(char *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrev))(__str, __maxlen); })
#endif /* !__CRT_HAVE_strnrev */
#ifdef __CRT_HAVE_strnlwr
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnlwr,(char *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* __CRT_HAVE_strnlwr */
#include <local/string/strnlwr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnlwr, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnlwr)(char *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnlwr))(__str, __maxlen); })
#endif /* !__CRT_HAVE_strnlwr */
#ifdef __CRT_HAVE_strnupr
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnupr,(char *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* __CRT_HAVE_strnupr */
#include <local/string/strnupr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnupr, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnupr)(char *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnupr))(__str, __maxlen); })
#endif /* !__CRT_HAVE_strnupr */
#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_strncoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strncoll_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <local/string/strncoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncoll_l)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strcasecoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecoll_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__stricoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecoll_l,(char const *__s1, char const *__s2, __locale_t __locale),_stricoll_l,(__s1,__s2,__locale))
#else /* ... */
#include <local/string/strcasecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasecoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcasecoll_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecoll_l))(__s1, __s2, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strncasecoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_strncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncmpi_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strncmpi_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <local/string/strncasecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncasecoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncasecoll_l)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strlwr_l
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strlwr_l,(char *__restrict __str, __locale_t __locale),(__str,__locale))
#elif defined(__CRT_HAVE__strlwr_l)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strlwr_l,(char *__restrict __str, __locale_t __locale),_strlwr_l,(__str,__locale))
#else /* ... */
#include <local/string/strlwr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strlwr_l, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strlwr_l)(char *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlwr_l))(__str, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strupr_l
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strupr_l,(char *__restrict __str, __locale_t __locale),(__str,__locale))
#elif defined(__CRT_HAVE__strupr_l)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strupr_l,(char *__restrict __str, __locale_t __locale),_strupr_l,(__str,__locale))
#else /* ... */
#include <local/string/strupr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strupr_l, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strupr_l)(char *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strupr_l))(__str, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strnlwr_l
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnlwr_l,(char *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__str,__maxlen,__locale))
#else /* __CRT_HAVE_strnlwr_l */
#include <local/string/strnlwr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnlwr_l, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnlwr_l)(char *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnlwr_l))(__str, __maxlen, __locale); })
#endif /* !__CRT_HAVE_strnlwr_l */
#ifdef __CRT_HAVE_strnupr_l
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnupr_l,(char *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__str,__maxlen,__locale))
#else /* __CRT_HAVE_strnupr_l */
#include <local/string/strnupr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnupr_l, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnupr_l)(char *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnupr_l))(__str, __maxlen, __locale); })
#endif /* !__CRT_HAVE_strnupr_l */
#ifdef __CRT_HAVE_memrev
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrev,(void *__restrict __base, __SIZE_TYPE__ __n_bytes),(__base,__n_bytes))
#else /* __CRT_HAVE_memrev */
#include <local/string/memrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memrev, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrev)(void *__restrict __base, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrev))(__base, __n_bytes); })
#endif /* !__CRT_HAVE_memrev */
#endif /* __USE_XOPEN2K8 */
#ifdef __USE_STRING_BWLQ
#ifdef __CRT_HAVE_memrev
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrevb,(void *__restrict __base, __SIZE_TYPE__ __n_bytes),memrev,(__base,__n_bytes))
#else /* __CRT_HAVE_memrev */
#include <local/string/memrev.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrevb)(void *__restrict __base, __SIZE_TYPE__ __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrev))(__base, __n_bytes); }
#endif /* !__CRT_HAVE_memrev */
#ifdef __CRT_HAVE_memrevw
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memrevw,(void *__restrict __base, __SIZE_TYPE__ __n_words),(__base,__n_words))
#else /* __CRT_HAVE_memrevw */
#include <local/string/memrevw.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memrevw, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrevw)(void *__restrict __base, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrevw))(__base, __n_words); })
#endif /* !__CRT_HAVE_memrevw */
#ifdef __CRT_HAVE_memrevl
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memrevl,(void *__restrict __base, __SIZE_TYPE__ __n_dwords),(__base,__n_dwords))
#else /* __CRT_HAVE_memrevl */
#include <local/string/memrevl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memrevl, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrevl)(void *__restrict __base, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrevl))(__base, __n_dwords); })
#endif /* !__CRT_HAVE_memrevl */
#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE_memrevq
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memrevq,(void *__restrict __base, __SIZE_TYPE__ __n_qwords),(__base,__n_qwords))
#else /* __CRT_HAVE_memrevq */
#include <local/string/memrevq.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memrevq, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrevq)(void *__restrict __base, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrevq))(__base, __n_qwords); })
#endif /* !__CRT_HAVE_memrevq */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */
#endif /* __USE_KOS */


#if defined(__USE_KOS) || defined(__USE_DOS)
#ifdef __CRT_HAVE_strlwr
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strlwr,(char *__restrict __str),(__str))
#elif defined(__CRT_HAVE__strlwr)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strlwr,(char *__restrict __str),_strlwr,(__str))
#else /* ... */
#include <local/string/strlwr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strlwr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strlwr)(char *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlwr))(__str); })
#endif /* !... */
#ifdef __CRT_HAVE_strupr
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strupr,(char *__restrict __str),(__str))
#elif defined(__CRT_HAVE__strupr)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strupr,(char *__restrict __str),_strupr,(__str))
#else /* ... */
#include <local/string/strupr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strupr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strupr)(char *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strupr))(__str); })
#endif /* !... */
#ifdef __CRT_HAVE_strset
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strset,(char *__restrict __str, int __ch),(__str,__ch))
#elif defined(__CRT_HAVE__strset)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strset,(char *__restrict __str, int __ch),_strset,(__str,__ch))
#else /* ... */
#include <local/string/strset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strset, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strset)(char *__restrict __str, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strset))(__str, __ch); })
#endif /* !... */
#ifdef __CRT_HAVE_strnset
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnset,(char *__restrict __str, int __ch, __SIZE_TYPE__ __maxlen),(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE__strnset)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnset,(char *__restrict __str, int __ch, __SIZE_TYPE__ __maxlen),_strnset,(__str,__ch,__maxlen))
#else /* ... */
#include <local/string/strnset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnset, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnset)(char *__restrict __str, int __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnset))(__str, __ch, __maxlen); })
#endif /* !... */
#ifdef __CRT_HAVE_strrev
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strrev,(char *__restrict __str),(__str))
#elif defined(__CRT_HAVE__strrev)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strrev,(char *__restrict __str),_strrev,(__str))
#else /* ... */
#include <local/string/strrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strrev, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strrev)(char *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrev))(__str); })
#endif /* !... */
#endif /* __USE_KOS || __USE_DOS */


#ifdef __USE_DOS
#ifdef __CRT_HAVE_memccpy
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,_memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes),memccpy,(__dst,__src,__needle,__num_bytes))
#elif defined(__CRT_HAVE__memccpy)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,_memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes),(__dst,__src,__needle,__num_bytes))
#else /* ... */
#include <local/string/memccpy.h>
__FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL _memccpy)(void *__restrict __dst, void const *__restrict __src, int __needle, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memccpy))(__dst, __src, __needle, __num_bytes); }
#endif /* !... */
#ifdef __CRT_HAVE_memcasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcasecmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_memicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memicmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE__memicmp)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),(__s1,__s2,__n_bytes))
#else /* ... */
#include <local/string/memcasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _memicmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp))(__s1, __s2, __n_bytes); }
#endif /* !... */
#ifdef __CRT_HAVE_memcasecmp_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes, __locale_t __locale),memcasecmp_l,(__s1,__s2,__n_bytes,__locale))
#elif defined(__CRT_HAVE__memicmp_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes, __locale_t __locale),(__s1,__s2,__n_bytes,__locale))
#else /* ... */
#include <local/string/memcasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _memicmp_l)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp_l))(__s1, __s2, __n_bytes, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_memcasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memicmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcasecmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_memicmp)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memicmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE__memicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memicmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),_memicmp,(__s1,__s2,__n_bytes))
#else /* ... */
#include <local/string/memcasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memicmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp))(__s1, __s2, __n_bytes); }
#endif /* !... */
#ifdef __CRT_HAVE__strset_s
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,_strset_s,(char *__dst, __SIZE_TYPE__ __dstsize, int __ch),(__dst,__dstsize,__ch))
#else /* __CRT_HAVE__strset_s */
#include <local/string/_strset_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strset_s, __FORCELOCAL __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBCCALL _strset_s)(char *__dst, __SIZE_TYPE__ __dstsize, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strset_s))(__dst, __dstsize, __ch); })
#endif /* !__CRT_HAVE__strset_s */

#ifdef __USE_DOS_SLIB
#ifdef __CRT_HAVE_memcpy_s
__CDECLARE(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,memcpy_s,(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength),(__dst,__dstlength,__src,__srclength))
#else /* __CRT_HAVE_memcpy_s */
#include <local/string/memcpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpy_s, __FORCELOCAL __ATTR_NONNULL((1, 3)) __errno_t __NOTHROW_NCX(__LIBCCALL memcpy_s)(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy_s))(__dst, __dstlength, __src, __srclength); })
#endif /* !__CRT_HAVE_memcpy_s */
#ifdef __CRT_HAVE_memmove_s
__CDECLARE(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,memmove_s,(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength),(__dst,__dstlength,__src,__srclength))
#else /* __CRT_HAVE_memmove_s */
#include <local/string/memmove_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memmove_s, __FORCELOCAL __ATTR_NONNULL((1, 3)) __errno_t __NOTHROW_NCX(__LIBCCALL memmove_s)(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmove_s))(__dst, __dstlength, __src, __srclength); })
#endif /* !__CRT_HAVE_memmove_s */
#ifdef __CRT_HAVE_strcpy_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,strcpy_s,(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src),(__dst,__dstsize,__src))
#else /* __CRT_HAVE_strcpy_s */
#include <local/string/strcpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcpy_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL strcpy_s)(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcpy_s))(__dst, __dstsize, __src); })
#endif /* !__CRT_HAVE_strcpy_s */
#ifdef __CRT_HAVE_strcat_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,strcat_s,(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src),(__dst,__dstsize,__src))
#else /* __CRT_HAVE_strcat_s */
#include <local/string/strcat_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcat_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL strcat_s)(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcat_s))(__dst, __dstsize, __src); })
#endif /* !__CRT_HAVE_strcat_s */
#ifndef __strnlen_s_defined
#define __strnlen_s_defined 1
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strnlen_defined
#define __local___localdep_strnlen_defined 1
#if __has_builtin(__builtin_strnlen) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strnlen)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __string, __SIZE_TYPE__ __maxlen),strnlen,{ return __builtin_strnlen(__string, __maxlen); })
#elif defined(__CRT_HAVE_strnlen)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __string, __SIZE_TYPE__ __maxlen),strnlen,(__string,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/strnlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_strnlen __LIBC_LOCAL_NAME(strnlen)
#endif /* !... */
#endif /* !__local___localdep_strnlen_defined */
__NAMESPACE_LOCAL_END
__LOCAL __ATTR_PURE __ATTR_WUNUSED __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strnlen_s)(char const *__str, __SIZE_TYPE__ __maxlen) { return __str ? (__NAMESPACE_LOCAL_SYM __localdep_strnlen)(__str, __maxlen) : 0; }
#endif /* !__strnlen_s_defined */
#ifdef __CRT_HAVE_strncat_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,strncat_s,(char *__dst, rsize_t __dstsize, const char *__src, rsize_t __maxlen),(__dst,__dstsize,__src,__maxlen))
#else /* __CRT_HAVE_strncat_s */
#include <local/string/strncat_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncat_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL strncat_s)(char *__dst, rsize_t __dstsize, const char *__src, rsize_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncat_s))(__dst, __dstsize, __src, __maxlen); })
#endif /* !__CRT_HAVE_strncat_s */
#ifdef __CRT_HAVE_strncpy_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,strncpy_s,(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __maxlen),(__dst,__dstsize,__src,__maxlen))
#else /* __CRT_HAVE_strncpy_s */
#include <local/string/strncpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncpy_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL strncpy_s)(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncpy_s))(__dst, __dstsize, __src, __maxlen); })
#endif /* !__CRT_HAVE_strncpy_s */
#ifdef __CRT_HAVE_strtok_r
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((2, 3)),char *,__NOTHROW_NCX,strtok_s,(char *__string, char const *__delim, char **__restrict __save_ptr),strtok_r,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_strtok_s)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((2, 3)),char *,__NOTHROW_NCX,strtok_s,(char *__string, char const *__delim, char **__restrict __save_ptr),(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE___strtok_r)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((2, 3)),char *,__NOTHROW_NCX,strtok_s,(char *__string, char const *__delim, char **__restrict __save_ptr),__strtok_r,(__string,__delim,__save_ptr))
#else /* ... */
#include <local/string/strtok_r.h>
__FORCELOCAL __ATTR_LEAF __ATTR_NONNULL((2, 3)) char *__NOTHROW_NCX(__LIBCCALL strtok_s)(char *__string, char const *__delim, char **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtok_r))(__string, __delim, __save_ptr); }
#endif /* !... */
#endif /* __USE_DOS_SLIB */
#if __has_builtin(__builtin_strdup) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strdup)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,_strdup,(char const *__restrict __string),strdup,{ return __builtin_strdup(__string); })
#elif defined(__CRT_HAVE_strdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,_strdup,(char const *__restrict __string),strdup,(__string))
#elif defined(__CRT_HAVE__strdup)
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,_strdup,(char const *__restrict __string),(__string))
#elif defined(__CRT_HAVE___strdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,_strdup,(char const *__restrict __string),__strdup,(__string))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <local/string/strdup.h>
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL _strdup)(char const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strdup))(__string); }
#endif /* ... */
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),strcasecmp,{ return __builtin_strcasecmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE___strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),__strcasecmp,(__s1,__s2))
#else /* ... */
#include <local/string/strcasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _stricmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))(__s1, __s2); }
#endif /* !... */
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),strcasecmp,{ return __builtin_strcasecmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE___strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),__strcasecmp,(__s1,__s2))
#else /* ... */
#include <local/string/strcasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strcmpi)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))(__s1, __s2); }
#endif /* !... */
#ifdef __CRT_HAVE_strcasecmp_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricmp_l,(char const *__s1, char const *__s2, __locale_t __locale),strcasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__stricmp_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricmp_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___strcasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricmp_l,(char const *__s1, char const *__s2, __locale_t __locale),__strcasecmp_l,(__s1,__s2,__locale))
#else /* ... */
#include <local/string/strcasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _stricmp_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp_l))(__s1, __s2, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_strcoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strcoll_l,(char const *__s1, char const *__s2, __locale_t __locale),strcoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__strcoll_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strcoll_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___strcoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strcoll_l,(char const *__s1, char const *__s2, __locale_t __locale),__strcoll_l,(__s1,__s2,__locale))
#else /* ... */
#include <local/string/strcoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strcoll_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcoll_l))(__s1, __s2, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_strcasecoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),strcasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE__stricoll)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#else /* ... */
#include <local/string/strcasecoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _stricoll)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecoll))(__s1, __s2); }
#endif /* !... */
#ifdef __CRT_HAVE_strcasecoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricoll_l,(char const *__s1, char const *__s2, __locale_t __locale),strcasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__stricoll_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricoll_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#else /* ... */
#include <local/string/strcasecoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _stricoll_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecoll_l))(__s1, __s2, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_strncoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncoll)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#else /* ... */
#include <local/string/strncoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strncoll)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncoll))(__s1, __s2, __maxlen); }
#endif /* !... */
#ifdef __CRT_HAVE_strncoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),strncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncoll_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <local/string/strncoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strncoll_l)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncoll_l))(__s1, __s2, __maxlen, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_strncasecoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicoll)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#else /* ... */
#include <local/string/strncasecoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strnicoll)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecoll))(__s1, __s2, __maxlen); }
#endif /* !... */
#ifdef __CRT_HAVE_strncasecoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),strncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicoll_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_strncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncmpi_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strncmpi_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <local/string/strncasecoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strnicoll_l)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecoll_l))(__s1, __s2, __maxlen, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE__strerror
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_RPC,_strerror,(char const *__message),(__message))
#elif defined(__CRT_HAVE__strerror_s) || defined(__libc_geterrno)
#include <local/string/_strerror.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strerror, __FORCELOCAL __ATTR_WUNUSED char *__NOTHROW_RPC(__LIBCCALL _strerror)(char const *__message) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strerror))(__message); })
#endif /* ... */
#ifdef __CRT_HAVE__strerror_s
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_RPC,_strerror_s,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__message),(__buf,__buflen,__message))
#else /* __CRT_HAVE__strerror_s */
#include <parts/errno.h>
#ifdef __libc_geterrno
#include <local/string/_strerror_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strerror_s, __FORCELOCAL __ATTR_NONNULL((1)) __errno_t __NOTHROW_RPC(__LIBCCALL _strerror_s)(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__message) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strerror_s))(__buf, __buflen, __message); })
#endif /* __libc_geterrno */
#endif /* !__CRT_HAVE__strerror_s */
#ifdef __CRT_HAVE__strlwr_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,_strlwr_s,(char *__buf, __SIZE_TYPE__ __buflen),(__buf,__buflen))
#else /* __CRT_HAVE__strlwr_s */
#include <local/string/_strlwr_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strlwr_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _strlwr_s)(char *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strlwr_s))(__buf, __buflen); })
#endif /* !__CRT_HAVE__strlwr_s */
#ifdef __CRT_HAVE__strupr_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,_strupr_s,(char *__buf, __SIZE_TYPE__ __buflen),(__buf,__buflen))
#else /* __CRT_HAVE__strupr_s */
#include <local/string/_strupr_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strupr_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _strupr_s)(char *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strupr_s))(__buf, __buflen); })
#endif /* !__CRT_HAVE__strupr_s */
#ifdef __CRT_HAVE__strlwr_s_l
__CDECLARE(,__errno_t,__NOTHROW_NCX,_strlwr_s_l,(char *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale),(__buf,__buflen,__locale))
#else /* __CRT_HAVE__strlwr_s_l */
#include <local/string/_strlwr_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strlwr_s_l, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _strlwr_s_l)(char *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strlwr_s_l))(__buf, __buflen, __locale); })
#endif /* !__CRT_HAVE__strlwr_s_l */
#ifdef __CRT_HAVE__strupr_s_l
__CDECLARE(,__errno_t,__NOTHROW_NCX,_strupr_s_l,(char *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale),(__buf,__buflen,__locale))
#else /* __CRT_HAVE__strupr_s_l */
#include <local/string/_strupr_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strupr_s_l, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _strupr_s_l)(char *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strupr_s_l))(__buf, __buflen, __locale); })
#endif /* !__CRT_HAVE__strupr_s_l */
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,{ return __builtin_strncasecmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strncmpi,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncmpi,(__s1,__s2,__maxlen))
#else /* ... */
#include <local/string/strncasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strnicmp)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp))(__s1, __s2, __maxlen); }
#endif /* !... */
#ifdef __CRT_HAVE_strncasecmp_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicmp_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncmpi_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strncmpi_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___strncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <local/string/strncasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strnicmp_l)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp_l))(__s1, __s2, __maxlen, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE__strnset_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,_strnset_s,(char *__restrict __buf, __SIZE_TYPE__ __buflen, int __ch, __SIZE_TYPE__ __maxlen),(__buf,__buflen,__ch,__maxlen))
#else /* __CRT_HAVE__strnset_s */
#include <local/string/_strnset_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strnset_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _strnset_s)(char *__restrict __buf, __SIZE_TYPE__ __buflen, int __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strnset_s))(__buf, __buflen, __ch, __maxlen); })
#endif /* !__CRT_HAVE__strnset_s */
#ifdef __CRT_HAVE_strrev
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,_strrev,(char *__restrict __str),strrev,(__str))
#elif defined(__CRT_HAVE__strrev)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,_strrev,(char *__restrict __str),(__str))
#else /* ... */
#include <local/string/strrev.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL _strrev)(char *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrev))(__str); }
#endif /* !... */
#ifdef __CRT_HAVE_strxfrm_l
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,_strxfrm_l,(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),strxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE__strxfrm_l)
__CDECLARE(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,_strxfrm_l,(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE___strxfrm_l)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,_strxfrm_l,(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),__strxfrm_l,(__dst,__src,__maxlen,__locale))
#else /* ... */
#include <local/string/strxfrm_l.h>
__FORCELOCAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _strxfrm_l)(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strxfrm_l))(__dst, __src, __maxlen, __locale); }
#endif /* !... */
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),strcasecmp,{ return __builtin_strcasecmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE___strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),__strcasecmp,(__s1,__s2))
#else /* ... */
#include <local/string/strcasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL stricmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))(__s1, __s2); }
#endif /* !... */
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),strcasecmp,{ return __builtin_strcasecmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE___strcasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),__strcasecmp,(__s1,__s2))
#else /* ... */
#include <local/string/strcasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcmpi)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))(__s1, __s2); }
#endif /* !... */
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,{ return __builtin_strncasecmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strncmpi,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strnicmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncmpi,(__s1,__s2,__maxlen))
#else /* ... */
#include <local/string/strncasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strnicmp)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp))(__s1, __s2, __maxlen); }
#endif /* !... */
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,{ return __builtin_strncasecmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncmpi,(__s1,__s2,__maxlen))
#else /* ... */
#include <local/string/strncasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strncmpi)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp))(__s1, __s2, __maxlen); }
#endif /* !... */
#ifdef __CRT_HAVE_strncasecmp_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncmpi_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___strncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <local/string/strncasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strncmpi_l)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp_l))(__s1, __s2, __maxlen, __locale); }
#endif /* !... */
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,{ return __builtin_strncasecmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strncmpi,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmpi,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#else /* ... */
#include <local/string/strncasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncmpi)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp))(__s1, __s2, __maxlen); }
#endif /* !... */

#ifndef _WSTRING_DEFINED
#define _WSTRING_DEFINED 1
#ifndef ___wcsdup_defined
#define ___wcsdup_defined 1
#ifdef __CRT_HAVE_wcsdup
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsdup,(wchar_t const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <local/wchar/wcsdup.h>
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsdup)(wchar_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))(__string); }
#else /* ... */
#undef ___wcsdup_defined
#endif /* !... */
#endif /* !___wcsdup_defined */
#ifndef __wcscat_defined
#define __wcscat_defined 1
#ifdef __std_wcscat_defined
__NAMESPACE_STD_USING(wcscat)
#elif defined(__CRT_HAVE_wcscat)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscat,(wchar_t *__restrict __buf, wchar_t const *__restrict __src),(__buf,__src))
#else /* ... */
#include <local/wchar/wcscat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscat, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscat)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat))(__buf, __src); })
#endif /* !... */
#endif /* !__wcscat_defined */
#ifndef __wcschr_defined
#define __wcschr_defined 1
#ifdef __std_wcschr_defined
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_STD_USING(wcschr)
#elif defined(__CRT_HAVE_wcschr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcschr,(wchar_t *__restrict __haystack, wchar_t __needle),wcschr,(__haystack,__needle))
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcschr,(wchar_t const *__restrict __haystack, wchar_t __needle),wcschr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcschr,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/wchar/wcschr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))(__haystack, __needle); }
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcschr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__wcschr_defined */
#ifndef __wcscmp_defined
#define __wcscmp_defined 1
#ifdef __std_wcscmp_defined
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__NAMESPACE_STD_USING(wcscmp)
#elif defined(__CRT_HAVE_wcscmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* ... */
#include <local/wchar/wcscmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))(__s1, __s2); })
#endif /* !... */
#endif /* !__wcscmp_defined */
#ifndef __wcscpy_defined
#define __wcscpy_defined 1
#ifdef __std_wcscpy_defined
__NAMESPACE_STD_USING(wcscpy)
#elif defined(__CRT_HAVE_wcscpy)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src),(__buf,__src))
#else /* ... */
#include <local/wchar/wcscpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy))(__buf, __src); })
#endif /* !... */
#endif /* !__wcscpy_defined */
#ifndef __wcscspn_defined
#define __wcscspn_defined 1
#ifdef __std_wcscspn_defined
__NAMESPACE_STD_USING(wcscspn)
#elif defined(__CRT_HAVE_wcscspn)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,wcscspn,(wchar_t const *__haystack, wchar_t const *__reject),(__haystack,__reject))
#else /* ... */
#include <local/wchar/wcscspn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscspn, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL wcscspn)(wchar_t const *__haystack, wchar_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscspn))(__haystack, __reject); })
#endif /* !... */
#endif /* !__wcscspn_defined */
#ifndef __wcslen_defined
#define __wcslen_defined 1
#ifdef __std_wcslen_defined
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__NAMESPACE_STD_USING(wcslen)
#elif defined(__CRT_HAVE_wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,wcslen,(wchar_t const *__restrict __string),(__string))
#else /* ... */
#include <local/wchar/wcslen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL wcslen)(wchar_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))(__string); })
#endif /* !... */
#endif /* !__wcslen_defined */
#ifndef __wcsnlen_defined
#define __wcsnlen_defined 1
#ifdef __CRT_HAVE_wcsnlen
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcsnlen,(wchar_t const *__restrict __string, __SIZE_TYPE__ __maxlen),(__string,__maxlen))
#else /* __CRT_HAVE_wcsnlen */
#include <local/wchar/wcsnlen.h>
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnlen)(wchar_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))(__string, __maxlen); })
#endif /* !__CRT_HAVE_wcsnlen */
#endif /* !__wcsnlen_defined */
#ifndef __wcsncat_defined
#define __wcsncat_defined 1
#ifdef __std_wcsncat_defined
__NAMESPACE_STD_USING(wcsncat)
#elif defined(__CRT_HAVE_wcsncat)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsncat,(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#else /* ... */
#include <local/wchar/wcsncat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncat, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsncat)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat))(__buf, __src, __buflen); })
#endif /* !... */
#endif /* !__wcsncat_defined */
#ifndef __wcsncmp_defined
#define __wcsncmp_defined 1
#ifdef __std_wcsncmp_defined
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__NAMESPACE_STD_USING(wcsncmp)
#elif defined(__CRT_HAVE_wcsncmp)
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncmp,(wchar_t const *__s1, wchar_t const *__s2, size_t __maxlen),(__s1,__s2,__maxlen))
#else /* ... */
#include <local/wchar/wcsncmp.h>
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncmp)(wchar_t const *__s1, wchar_t const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#endif /* !__wcsncmp_defined */
#ifndef __wcsncpy_defined
#define __wcsncpy_defined 1
#ifdef __std_wcsncpy_defined
__NAMESPACE_STD_USING(wcsncpy)
#elif defined(__CRT_HAVE_wcsncpy)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsncpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#else /* ... */
#include <local/wchar/wcsncpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsncpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy))(__buf, __src, __buflen); })
#endif /* !... */
#endif /* !__wcsncpy_defined */
#ifndef __wcspbrk_defined
#define __wcspbrk_defined 1
#ifdef __std_wcspbrk_defined
__NAMESPACE_STD_USING(wcspbrk)
#elif defined(__CRT_HAVE_wcspbrk)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcspbrk,(wchar_t *__haystack, wchar_t const *__accept),wcspbrk,(__haystack,__accept))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcspbrk,(wchar_t const *__haystack, wchar_t const *__accept),wcspbrk,(__haystack,__accept))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcspbrk,(wchar_t const *__haystack, wchar_t const *__accept),(__haystack,__accept))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/wchar/wcspbrk.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))(__haystack, __accept); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t const *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))(__haystack, __accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcspbrk, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t const *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))(__haystack, __accept); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__wcspbrk_defined */
#ifndef __wcsrchr_defined
#define __wcsrchr_defined 1
#ifdef __std_wcsrchr_defined
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_STD_USING(wcsrchr)
#elif defined(__CRT_HAVE_wcsrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrchr,(wchar_t *__restrict __haystack, wchar_t __needle),wcsrchr,(__haystack,__needle))
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsrchr,(wchar_t const *__restrict __haystack, wchar_t __needle),wcsrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrchr,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/wchar/wcsrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))(__haystack, __needle); }
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__wcsrchr_defined */
#ifndef __wcsspn_defined
#define __wcsspn_defined 1
#ifdef __std_wcsspn_defined
__NAMESPACE_STD_USING(wcsspn)
#elif defined(__CRT_HAVE_wcsspn)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,wcsspn,(wchar_t const *__haystack, wchar_t const *__accept),(__haystack,__accept))
#else /* ... */
#include <local/wchar/wcsspn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsspn, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL wcsspn)(wchar_t const *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsspn))(__haystack, __accept); })
#endif /* !... */
#endif /* !__wcsspn_defined */
#ifndef __wcsstr_defined
#define __wcsstr_defined 1
#ifdef __std_wcsstr_defined
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__NAMESPACE_STD_USING(wcsstr)
#elif defined(__CRT_HAVE_wcsstr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t *__haystack, wchar_t *__needle),wcsstr,(__haystack,__needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_wcswcs)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t *__haystack, wchar_t *__needle),wcswcs,(__haystack,__needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/wchar/wcsstr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t *__haystack, wchar_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsstr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__wcsstr_defined */
#ifndef __wcstok_defined
#define __wcstok_defined 1
#ifdef __std_wcstok_defined
__NAMESPACE_STD_USING(wcstok)
#elif defined(__CRT_HAVE_wcstok) && !defined(__CRT_DOS_PRIMARY)
__CDECLARE(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok,(wchar_t *__string, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok_s) && defined(__CRT_DOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok,(wchar_t *__string, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok_s,(__string,__delim,__save_ptr))
#else /* ... */
#include <local/wchar/wcstok.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstok, __FORCELOCAL __ATTR_NONNULL((2, 3)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcstok)(wchar_t *__string, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))(__string, __delim, __save_ptr); })
#endif /* !... */
#endif /* !__wcstok_defined */
#ifndef ___wcserror_defined
#define ___wcserror_defined 1
#ifdef __CRT_HAVE__wcserror
__CDECLARE(,wchar_t *,__NOTHROW_NCX,_wcserror,(int __errno_value),(__errno_value))
#else /* __CRT_HAVE__wcserror */
#undef ___wcserror_defined
#endif /* !__CRT_HAVE__wcserror */
#endif /* !___wcserror_defined */
#ifndef ___wcserror_s_defined
#define ___wcserror_s_defined 1
#ifdef __CRT_HAVE__wcserror_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcserror_s,(wchar_t *__buf, __SIZE_TYPE__ __bufsize, int __errno_value),(__buf,__bufsize,__errno_value))
#else /* __CRT_HAVE__wcserror_s */
#undef ___wcserror_s_defined
#endif /* !__CRT_HAVE__wcserror_s */
#endif /* !___wcserror_s_defined */
#ifndef ____wcserror_defined
#define ____wcserror_defined 1
#ifdef __CRT_HAVE___wcserror
__CDECLARE(,wchar_t *,__NOTHROW_NCX,__wcserror,(wchar_t const *__message),(__message))
#else /* __CRT_HAVE___wcserror */
#undef ____wcserror_defined
#endif /* !__CRT_HAVE___wcserror */
#endif /* !____wcserror_defined */
#ifndef ____wcserror_s_defined
#define ____wcserror_s_defined 1
#ifdef __CRT_HAVE___wcserror_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,__wcserror_s,(wchar_t *__buf, __SIZE_TYPE__ __bufsize, wchar_t const *__message),(__buf,__bufsize,__message))
#else /* __CRT_HAVE___wcserror_s */
#undef ____wcserror_s_defined
#endif /* !__CRT_HAVE___wcserror_s */
#endif /* !____wcserror_s_defined */
#ifndef ___wcsicmp_defined
#define ___wcsicmp_defined 1
#ifdef __CRT_HAVE_wcscasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#else /* __CRT_HAVE_wcscasecmp */
#include <local/wchar/wcscasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))(__s1, __s2); }
#endif /* !__CRT_HAVE_wcscasecmp */
#endif /* !___wcsicmp_defined */
#ifndef ___wcsicmp_l_defined
#define ___wcsicmp_l_defined 1
#ifdef __CRT_HAVE_wcscasecmp_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#else /* ... */
#include <local/wchar/wcscasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicmp_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp_l))(__s1, __s2, __locale); }
#endif /* !... */
#endif /* !___wcsicmp_l_defined */
#ifndef ___wcsnicmp_defined
#define ___wcsnicmp_defined 1
#ifdef __CRT_HAVE_wcsncasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#else /* __CRT_HAVE_wcsncasecmp */
#include <local/wchar/wcsncasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicmp)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))(__s1, __s2, __maxlen); }
#endif /* !__CRT_HAVE_wcsncasecmp */
#endif /* !___wcsnicmp_defined */
#ifndef ___wcsnicmp_l_defined
#define ___wcsnicmp_l_defined 1
#ifdef __CRT_HAVE_wcsncasecmp_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <local/wchar/wcsncasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicmp_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp_l))(__s1, __s2, __maxlen, __locale); }
#endif /* !... */
#endif /* !___wcsnicmp_l_defined */
#ifndef ___wcsnset_s_defined
#define ___wcsnset_s_defined 1
#ifdef __CRT_HAVE__wcsnset_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcsnset_s,(wchar_t *__restrict __buf, __SIZE_TYPE__ __buflen, wchar_t __ch, __SIZE_TYPE__ __maxlen),(__buf,__buflen,__ch,__maxlen))
#else /* __CRT_HAVE__wcsnset_s */
#include <local/wchar/_wcsnset_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsnset_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcsnset_s)(wchar_t *__restrict __buf, __SIZE_TYPE__ __buflen, wchar_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsnset_s))(__buf, __buflen, __ch, __maxlen); })
#endif /* !__CRT_HAVE__wcsnset_s */
#endif /* !___wcsnset_s_defined */
#ifndef ___wcsnset_defined
#define ___wcsnset_defined 1
#ifdef __CRT_HAVE_wcsnset
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsnset,(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#else /* __CRT_HAVE_wcsnset */
#include <local/wchar/wcsnset.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsnset)(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))(__str, __ch, __maxlen); }
#endif /* !__CRT_HAVE_wcsnset */
#endif /* !___wcsnset_defined */
#ifndef ___wcsrev_defined
#define ___wcsrev_defined 1
#ifdef __CRT_HAVE_wcsrev
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsrev,(wchar_t *__restrict __str),wcsrev,(__str))
#else /* __CRT_HAVE_wcsrev */
#include <local/wchar/wcsrev.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsrev)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))(__str); }
#endif /* !__CRT_HAVE_wcsrev */
#endif /* !___wcsrev_defined */
#ifndef ___wcsset_s_defined
#define ___wcsset_s_defined 1
#ifdef __CRT_HAVE__wcsset_s
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,_wcsset_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t __ch),(__dst,__dstsize,__ch))
#else /* __CRT_HAVE__wcsset_s */
#include <local/wchar/_wcsset_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsset_s, __FORCELOCAL __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBCCALL _wcsset_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsset_s))(__dst, __dstsize, __ch); })
#endif /* !__CRT_HAVE__wcsset_s */
#endif /* !___wcsset_s_defined */
#ifndef ___wcsset_defined
#define ___wcsset_defined 1
#ifdef __CRT_HAVE_wcsset
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsset,(wchar_t *__restrict __str, int __ch),wcsset,(__str,__ch))
#else /* __CRT_HAVE_wcsset */
#include <local/wchar/wcsset.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsset)(wchar_t *__restrict __str, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))(__str, __ch); }
#endif /* !__CRT_HAVE_wcsset */
#endif /* !___wcsset_defined */
#ifndef ___wcslwr_s_defined
#define ___wcslwr_s_defined 1
#ifdef __CRT_HAVE__wcslwr_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcslwr_s,(wchar_t *__buf, __SIZE_TYPE__ __buflen),(__buf,__buflen))
#else /* __CRT_HAVE__wcslwr_s */
#include <local/wchar/_wcslwr_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcslwr_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcslwr_s)(wchar_t *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcslwr_s))(__buf, __buflen); })
#endif /* !__CRT_HAVE__wcslwr_s */
#endif /* !___wcslwr_s_defined */
#ifndef ___wcslwr_defined
#define ___wcslwr_defined 1
#ifdef __CRT_HAVE_wcslwr
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcslwr,(wchar_t *__restrict __str),wcslwr,(__str))
#else /* __CRT_HAVE_wcslwr */
#include <local/wchar/wcslwr.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcslwr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))(__str); }
#endif /* !__CRT_HAVE_wcslwr */
#endif /* !___wcslwr_defined */
#ifndef ___wcslwr_s_l_defined
#define ___wcslwr_s_l_defined 1
#ifdef __CRT_HAVE__wcslwr_s_l
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcslwr_s_l,(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale),(__buf,__buflen,__locale))
#else /* __CRT_HAVE__wcslwr_s_l */
#include <local/wchar/_wcslwr_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcslwr_s_l, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcslwr_s_l)(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcslwr_s_l))(__buf, __buflen, __locale); })
#endif /* !__CRT_HAVE__wcslwr_s_l */
#endif /* !___wcslwr_s_l_defined */
#ifndef ___wcslwr_l_defined
#define ___wcslwr_l_defined 1
#ifdef __CRT_HAVE_wcslwr_l
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcslwr_l,(wchar_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#else /* __CRT_HAVE_wcslwr_l */
#include <local/wchar/wcslwr_l.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcslwr_l)(wchar_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr_l))(__str, __locale); }
#endif /* !__CRT_HAVE_wcslwr_l */
#endif /* !___wcslwr_l_defined */
#ifndef ___wcsupr_s_defined
#define ___wcsupr_s_defined 1
#ifdef __CRT_HAVE__wcsupr_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcsupr_s,(wchar_t *__buf, __SIZE_TYPE__ __buflen),(__buf,__buflen))
#else /* __CRT_HAVE__wcsupr_s */
#include <local/wchar/_wcsupr_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsupr_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcsupr_s)(wchar_t *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsupr_s))(__buf, __buflen); })
#endif /* !__CRT_HAVE__wcsupr_s */
#endif /* !___wcsupr_s_defined */
#ifndef ___wcsupr_defined
#define ___wcsupr_defined 1
#ifdef __CRT_HAVE_wcsupr
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsupr,(wchar_t *__restrict __str),wcsupr,(__str))
#else /* __CRT_HAVE_wcsupr */
#include <local/wchar/wcsupr.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsupr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))(__str); }
#endif /* !__CRT_HAVE_wcsupr */
#endif /* !___wcsupr_defined */
#ifndef ___wcsupr_s_l_defined
#define ___wcsupr_s_l_defined 1
#ifdef __CRT_HAVE__wcsupr_s_l
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcsupr_s_l,(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale),(__buf,__buflen,__locale))
#else /* __CRT_HAVE__wcsupr_s_l */
#include <local/wchar/_wcsupr_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsupr_s_l, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcsupr_s_l)(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsupr_s_l))(__buf, __buflen, __locale); })
#endif /* !__CRT_HAVE__wcsupr_s_l */
#endif /* !___wcsupr_s_l_defined */
#ifndef ___wcsupr_l_defined
#define ___wcsupr_l_defined 1
#ifdef __CRT_HAVE_wcsupr_l
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsupr_l,(wchar_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#else /* __CRT_HAVE_wcsupr_l */
#include <local/wchar/wcsupr_l.h>
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsupr_l)(wchar_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr_l))(__str, __locale); }
#endif /* !__CRT_HAVE_wcsupr_l */
#endif /* !___wcsupr_l_defined */
#ifndef __wcsxfrm_defined
#define __wcsxfrm_defined 1
#ifdef __std_wcsxfrm_defined
__NAMESPACE_STD_USING(wcsxfrm)
#elif defined(__CRT_HAVE_wcsxfrm)
__CDECLARE(__ATTR_NONNULL((2)),size_t,__NOTHROW_NCX,wcsxfrm,(wchar_t *__dst, wchar_t const *__restrict __src, size_t __maxlen),(__dst,__src,__maxlen))
#else /* ... */
#include <local/wchar/wcsxfrm.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsxfrm, __FORCELOCAL __ATTR_NONNULL((2)) size_t __NOTHROW_NCX(__LIBCCALL wcsxfrm)(wchar_t *__dst, wchar_t const *__restrict __src, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm))(__dst, __src, __maxlen); })
#endif /* !... */
#endif /* !__wcsxfrm_defined */
#ifndef ___wcsxfrm_l_defined
#define ___wcsxfrm_l_defined 1
#ifdef __CRT_HAVE_wcsxfrm_l
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,_wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsxfrm_l)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,_wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#else /* ... */
#include <local/wchar/wcsxfrm_l.h>
__FORCELOCAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcsxfrm_l)(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm_l))(__dst, __src, __maxlen, __locale); }
#endif /* !... */
#endif /* !___wcsxfrm_l_defined */
#ifndef __wcscoll_defined
#define __wcscoll_defined 1
#ifdef __std_wcscoll_defined
__NAMESPACE_STD_USING(wcscoll)
#elif defined(__CRT_HAVE_wcscoll)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscoll,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* ... */
#include <local/wchar/wcscoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll))(__s1, __s2); })
#endif /* !... */
#endif /* !__wcscoll_defined */
#ifndef ___wcscoll_l_defined
#define ___wcscoll_l_defined 1
#ifdef __CRT_HAVE_wcscoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#else /* ... */
#include <local/wchar/wcscoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcscoll_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll_l))(__s1, __s2, __locale); }
#endif /* !... */
#endif /* !___wcscoll_l_defined */
#ifndef ___wcsicoll_defined
#define ___wcsicoll_defined 1
#ifdef __CRT_HAVE_wcscasecoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcsicmp,(__s1,__s2))
#else /* ... */
#include <local/wchar/wcscasecoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))(__s1, __s2); }
#endif /* !... */
#endif /* !___wcsicoll_defined */
#ifndef ___wcsicoll_l_defined
#define ___wcsicoll_l_defined 1
#ifdef __CRT_HAVE_wcscasecoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#else /* ... */
#include <local/wchar/wcscasecoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicoll_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll_l))(__s1, __s2, __locale); }
#endif /* !... */
#endif /* !___wcsicoll_l_defined */
#ifndef ___wcsncoll_defined
#define ___wcsncoll_defined 1
#ifdef __CRT_HAVE_wcsncasecoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#else /* ... */
#include <local/wchar/wcsncasecoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsncoll)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))(__s1, __s2, __maxlen); }
#endif /* !... */
#endif /* !___wcsncoll_defined */
#ifndef ___wcsncoll_l_defined
#define ___wcsncoll_l_defined 1
#ifdef __CRT_HAVE_wcsncoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#else /* __CRT_HAVE_wcsncoll_l */
#include <local/wchar/wcsncoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsncoll_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll_l))(__s1, __s2, __maxlen, __locale); }
#endif /* !__CRT_HAVE_wcsncoll_l */
#endif /* !___wcsncoll_l_defined */
#ifndef ___wcsnicoll_defined
#define ___wcsnicoll_defined 1
#ifdef __CRT_HAVE_wcsncasecoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#else /* ... */
#include <local/wchar/wcsncasecoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicoll)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))(__s1, __s2, __maxlen); }
#endif /* !... */
#endif /* !___wcsnicoll_defined */
#ifndef ___wcsnicoll_l_defined
#define ___wcsnicoll_l_defined 1
#ifdef __CRT_HAVE_wcsncasecoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <local/wchar/wcsncasecoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicoll_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll_l))(__s1, __s2, __maxlen, __locale); }
#endif /* !... */
#endif /* !___wcsnicoll_l_defined */
#ifndef __wcsdup_defined
#define __wcsdup_defined 1
#ifdef __CRT_HAVE_wcsdup
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsdup,(wchar_t const *__restrict __string),(__string))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <local/wchar/wcsdup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsdup, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsdup)(wchar_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))(__string); })
#else /* ... */
#undef __wcsdup_defined
#endif /* !... */
#endif /* !__wcsdup_defined */
#ifndef __wcswcs_defined
#define __wcswcs_defined 1
#ifdef __CRT_HAVE_wcsstr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t *__haystack, wchar_t *__needle),wcsstr,(__haystack,__needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),wcsstr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_wcswcs)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t *__haystack, wchar_t *__needle),wcswcs,(__haystack,__needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <local/wchar/wcsstr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcswcs)(wchar_t *__haystack, wchar_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcswcs)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcswcs)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__wcswcs_defined */
#ifndef __wcsicmp_defined
#define __wcsicmp_defined 1
#ifdef __CRT_HAVE_wcscasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#else /* __CRT_HAVE_wcscasecmp */
#include <local/wchar/wcscasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsicmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))(__s1, __s2); }
#endif /* !__CRT_HAVE_wcscasecmp */
#endif /* !__wcsicmp_defined */
#ifndef __wcsnicmp_defined
#define __wcsnicmp_defined 1
#ifdef __CRT_HAVE_wcsncasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#else /* __CRT_HAVE_wcsncasecmp */
#include <local/wchar/wcsncasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsnicmp)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))(__s1, __s2, __maxlen); }
#endif /* !__CRT_HAVE_wcsncasecmp */
#endif /* !__wcsnicmp_defined */
#ifndef __wcsnset_defined
#define __wcsnset_defined 1
#ifdef __CRT_HAVE_wcsnset
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnset,(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen),(__str,__ch,__maxlen))
#else /* __CRT_HAVE_wcsnset */
#include <local/wchar/wcsnset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnset)(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))(__str, __ch, __maxlen); })
#endif /* !__CRT_HAVE_wcsnset */
#endif /* !__wcsnset_defined */
#ifndef __wcsrev_defined
#define __wcsrev_defined 1
#ifdef __CRT_HAVE_wcsrev
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrev,(wchar_t *__restrict __str),(__str))
#else /* __CRT_HAVE_wcsrev */
#include <local/wchar/wcsrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrev, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrev)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))(__str); })
#endif /* !__CRT_HAVE_wcsrev */
#endif /* !__wcsrev_defined */
#ifndef __wcsset_defined
#define __wcsset_defined 1
#ifdef __CRT_HAVE_wcsset
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsset,(wchar_t *__restrict __str, int __ch),(__str,__ch))
#else /* __CRT_HAVE_wcsset */
#include <local/wchar/wcsset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsset, __FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsset)(wchar_t *__restrict __str, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))(__str, __ch); })
#endif /* !__CRT_HAVE_wcsset */
#endif /* !__wcsset_defined */
#ifndef __wcslwr_defined
#define __wcslwr_defined 1
#ifdef __CRT_HAVE_wcslwr
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcslwr,(wchar_t *__restrict __str),(__str))
#else /* __CRT_HAVE_wcslwr */
#include <local/wchar/wcslwr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslwr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcslwr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))(__str); })
#endif /* !__CRT_HAVE_wcslwr */
#endif /* !__wcslwr_defined */
#ifndef __wcsupr_defined
#define __wcsupr_defined 1
#ifdef __CRT_HAVE_wcsupr
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsupr,(wchar_t *__restrict __str),(__str))
#else /* __CRT_HAVE_wcsupr */
#include <local/wchar/wcsupr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsupr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsupr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))(__str); })
#endif /* !__CRT_HAVE_wcsupr */
#endif /* !__wcsupr_defined */
#ifndef __wcsicoll_defined
#define __wcsicoll_defined 1
#ifdef __CRT_HAVE_wcscasecoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcsicmp,(__s1,__s2))
#else /* ... */
#include <local/wchar/wcscasecoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsicoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))(__s1, __s2); }
#endif /* !... */
#endif /* !__wcsicoll_defined */
#ifdef __USE_DOS_SLIB
#ifndef __wcscat_s_defined
#define __wcscat_s_defined 1
#ifdef __CRT_HAVE_wcscat_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,wcscat_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src),(__dst,__dstsize,__src))
#else /* __CRT_HAVE_wcscat_s */
#include <local/wchar/wcscat_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscat_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL wcscat_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat_s))(__dst, __dstsize, __src); })
#endif /* !__CRT_HAVE_wcscat_s */
#endif /* !__wcscat_s_defined */
#ifndef __wcscpy_s_defined
#define __wcscpy_s_defined 1
#ifdef __CRT_HAVE_wcscpy_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,wcscpy_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src),(__dst,__dstsize,__src))
#else /* __CRT_HAVE_wcscpy_s */
#include <local/wchar/wcscpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscpy_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL wcscpy_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy_s))(__dst, __dstsize, __src); })
#endif /* !__CRT_HAVE_wcscpy_s */
#endif /* !__wcscpy_s_defined */
#ifndef __wcsncat_s_defined
#define __wcsncat_s_defined 1
#ifdef __CRT_HAVE_wcsncat_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,wcsncat_s,(wchar_t *__dst, rsize_t __dstsize, const wchar_t *__src, rsize_t __maxlen),(__dst,__dstsize,__src,__maxlen))
#else /* __CRT_HAVE_wcsncat_s */
#include <local/wchar/wcsncat_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncat_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL wcsncat_s)(wchar_t *__dst, rsize_t __dstsize, const wchar_t *__src, rsize_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat_s))(__dst, __dstsize, __src, __maxlen); })
#endif /* !__CRT_HAVE_wcsncat_s */
#endif /* !__wcsncat_s_defined */
#ifndef __wcsncpy_s_defined
#define __wcsncpy_s_defined 1
#ifdef __CRT_HAVE_wcsncpy_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,wcsncpy_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src, __SIZE_TYPE__ __maxlen),(__dst,__dstsize,__src,__maxlen))
#else /* __CRT_HAVE_wcsncpy_s */
#include <local/wchar/wcsncpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncpy_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL wcsncpy_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy_s))(__dst, __dstsize, __src, __maxlen); })
#endif /* !__CRT_HAVE_wcsncpy_s */
#endif /* !__wcsncpy_s_defined */
#ifndef __wcstok_s_defined
#define __wcstok_s_defined 1
#if defined(__CRT_HAVE_wcstok) && !defined(__CRT_DOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok_s,(wchar_t *__string, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok_s) && defined(__CRT_DOS_PRIMARY)
__CDECLARE(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok_s,(wchar_t *__string, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),(__string,__delim,__save_ptr))
#else /* ... */
#include <local/wchar/wcstok.h>
__FORCELOCAL __ATTR_NONNULL((2, 3)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcstok_s)(wchar_t *__string, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))(__string, __delim, __save_ptr); }
#endif /* !... */
#endif /* !__wcstok_s_defined */
#ifndef __wcsnlen_s_defined
#define __wcsnlen_s_defined 1
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcsnlen_defined
#define __local___localdep_wcsnlen_defined 1
#ifdef __CRT_HAVE_wcsnlen
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(wchar_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#else /* __CRT_HAVE_wcsnlen */
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsnlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_wcsnlen __LIBC_LOCAL_NAME(wcsnlen)
#endif /* !__CRT_HAVE_wcsnlen */
#endif /* !__local___localdep_wcsnlen_defined */
__NAMESPACE_LOCAL_END
__LOCAL __ATTR_PURE __ATTR_WUNUSED __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnlen_s)(wchar_t const *__str, __SIZE_TYPE__ __maxlen) { return __str ? (__NAMESPACE_LOCAL_SYM __localdep_wcsnlen)(__str, __maxlen) : 0; }
#endif /* !__wcsnlen_s_defined */
#endif  /* __USE_DOS_SLIB */
#endif /* !_WSTRING_DEFINED */
#endif /* __USE_DOS */

#if defined(__LIBC_BIND_OPTIMIZATIONS) && !defined(__NO_builtin_constant_p)
#ifndef __INTELLISENSE__
#if __has_builtin(__builtin_strlen)
#ifdef __cplusplus
#ifndef __std___forward_size_defined
#define __std___forward_size_defined 1
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST size_t __NOTHROW(__LIBCCALL __forward_size)(size_t __x) { return __x; }
__NAMESPACE_STD_END
#endif /* !__std___forward_size_defined */
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(__forward_size)
#endif /* !__CXX_SYSTEM_HEADER */
#define strlen(x) __forward_size(__builtin_constant_p(x) ? __builtin_strlen(x) : (__NAMESPACE_STD_SYM strlen)(x))
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
extern __ATTR_WUNUSED __ATTR_MALLOC __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(strdupa)(char const *__restrict __string);
extern __ATTR_WUNUSED __ATTR_MALLOC __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(strndupa)(char const *__restrict __string, __size_t __maxlen);
#elif defined(__NO_XBLOCK)
__FORCELOCAL __ATTR_WUNUSED __ATTR_MALLOC __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __strndupa_init)(void *__restrict __buf, char const *__restrict __string, __size_t __maxlen) {
	__size_t __buflen = __NAMESPACE_STD_SYM strnlen(__string, __maxlen) * sizeof(char);
#ifdef __mempcpy_defined
	*(char *)mempcpy(__buf, __string, __buflen) = 0;
#else /* __mempcpy_defined */
	((char *)__NAMESPACE_STD_SYM memcpy(__buf, __string, __buflen))[__buflen] = 0;
#endif /* !__mempcpy_defined */
	return (char *)__buf;
}
/* Without X-blocks, it's impossible to prevent multiple evaluations of the `string' argument... */
#define strdupa(string) \
	(__NAMESPACE_STD_SYM strcpy((char *)__hybrid_alloca((__NAMESPACE_STD_SYM strlen(string) + 1) * sizeof(char)), string))
#define strndupa(string, maxlen) \
	__strndupa_init(__hybrid_alloca((__NAMESPACE_STD_SYM strnlen(string, maxlen) + 1) * sizeof(char)), string, maxlen)
#else /* __NO_XBLOCK */
#define strdupa(string)                                                                   \
	__XBLOCK({                                                                            \
		char const *__orig_s = (string);                                                  \
		__size_t __orig_len  = (__NAMESPACE_STD_SYM strlen(__orig_s) + 1) * sizeof(char); \
		__XRETURN (char *)__NAMESPACE_STD_SYM memcpy(__hybrid_alloca(__orig_len),         \
		                                             __orig_s, __orig_len);               \
	})
#define strndupa(string, maxlen)                                                      \
	__XBLOCK({                                                                        \
		char const *__orig_s = (string);                                              \
		__size_t __orig_len  = __NAMESPACE_STD_SYM strlen(__orig_s) * sizeof(char);   \
		char *__copy_s = (char *)__hybrid_alloca(__orig_len + sizeof(char));          \
		__copy_s[__orig_len / sizeof(char)] = 0;                                      \
		__XRETURN (char *)__NAMESPACE_STD_SYM memcpy(__copy_s, __orig_s, __orig_len); \
	})
#endif /* !__NO_XBLOCK */
#endif /* __USE_GNU && __hybrid_alloca */


#if !defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
/* In C, we can use argument-count overload macros to implement these overloads! */
#ifdef __USE_KOS
#define __PRIVATE_memcpy_4  memcpyc
#define __PRIVATE_memmove_4 memmovec
#ifdef __USE_GNU
#define __PRIVATE_mempcpy_4 mempcpyc
#endif /* __USE_GNU */
#else /* __USE_KOS */
__SYSDECL_END
#include <libc/string.h>
__SYSDECL_BEGIN
#define __PRIVATE_memcpy_4  __libc_memcpyc
#define __PRIVATE_memmove_4 __libc_memmovec
#ifdef __USE_GNU
#define __PRIVATE_mempcpy_4 __libc_mempcpyc
#endif /* __USE_GNU */
#endif /* !__USE_KOS */
#define __PRIVATE_memcpy_3  (memcpy)
#define __PRIVATE_memmove_3 (memmove)
#undef memcpy
#undef memmove
#define memcpy(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memcpy_, (__VA_ARGS__))(__VA_ARGS__)
#define memmove(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmove_, (__VA_ARGS__))(__VA_ARGS__)
#ifdef __USE_GNU
#define __PRIVATE_mempcpy_3 (mempcpy)
#undef mempcpy
#define mempcpy(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempcpy_, (__VA_ARGS__))(__VA_ARGS__)
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
#define mempmove(...)     __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmove_, (__VA_ARGS__))(__VA_ARGS__)
#define mempmoveup(...)   __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmoveup_, (__VA_ARGS__))(__VA_ARGS__)
#define mempmovedown(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_mempmovedown_, (__VA_ARGS__))(__VA_ARGS__)
#define memmoveup(...)    __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmoveup_, (__VA_ARGS__))(__VA_ARGS__)
#define memmovedown(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_memmovedown_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* __USE_KOS */
#endif /* !__cplusplus && __USE_STRING_OVERLOADS */


#if defined(__USE_BSD) || defined(__USE_KOS)
#ifdef __CRT_HAVE_strnstr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If found, return a pointer to its location within `str', else return `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strnstr,(char *__haystack, char *__needle, __SIZE_TYPE__ __haystack_maxlen),strnstr,(__haystack,__needle,__haystack_maxlen))
/* Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If found, return a pointer to its location within `str', else return `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char const *,__NOTHROW_NCX,strnstr,(char const *__haystack, char const *__needle, __SIZE_TYPE__ __haystack_maxlen),strnstr,(__haystack,__needle,__haystack_maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If found, return a pointer to its location within `str', else return `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strnstr,(char const *__haystack, char const *__needle, __SIZE_TYPE__ __haystack_maxlen),(__haystack,__needle,__haystack_maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* __CRT_HAVE_strnstr */
#include <local/string/strnstr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If found, return a pointer to its location within `str', else return `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strnstr)(char *__haystack, char *__needle, __SIZE_TYPE__ __haystack_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnstr))(__haystack, __needle, __haystack_maxlen); }
/* Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If found, return a pointer to its location within `str', else return `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char const *__NOTHROW_NCX(__LIBCCALL strnstr)(char const *__haystack, char const *__needle, __SIZE_TYPE__ __haystack_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnstr))(__haystack, __needle, __haystack_maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If found, return a pointer to its location within `str', else return `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnstr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strnstr)(char const *__haystack, char const *__needle, __SIZE_TYPE__ __haystack_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnstr))(__haystack, __needle, __haystack_maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__CRT_HAVE_strnstr */
#endif /* __USE_BSD || __USE_KOS */


#ifdef __USE_BSD
#ifdef __CRT_HAVE_strmode
/* Generate a file mode representation similar to what's printed by `ls -l'
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
 *    p[4]  = mode & S_IRGRP ? 'r' : '-';
 *    p[5]  = mode & S_IWGRP ? 'w' : '-';
 *    p[6]  = <mode & S_IXGRP | S_ISGID>: { 0: '-', S_IXGRP: 'x', S_ISGID: 'S',
 *                                          S_IXGRP | S_ISGID: 's' };
 *    p[7]  = mode & S_IROTH ? 'r' : '-';
 *    p[8]  = mode & S_IWOTH ? 'w' : '-';
 *    p[9]  = <mode & S_IXOTH | S_ISVTX>: { 0: '-', S_IXOTH: 'x', S_ISVTX: 'T',
 *                                          S_IXOTH | S_ISVTX: 't' };
 *    p[10] = ' '; // '+', if "alternate or additional access control
 *                 //          methods associated with the inode"
 *    p[11] = '\0'; */
__CDECLARE_VOID(__ATTR_NONNULL((2)),__NOTHROW_NCX,strmode,(__mode_t __mode, char __p[12]),(__mode,__p))
#else /* __CRT_HAVE_strmode */
#include <local/string/strmode.h>
/* Generate a file mode representation similar to what's printed by `ls -l'
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
 *    p[4]  = mode & S_IRGRP ? 'r' : '-';
 *    p[5]  = mode & S_IWGRP ? 'w' : '-';
 *    p[6]  = <mode & S_IXGRP | S_ISGID>: { 0: '-', S_IXGRP: 'x', S_ISGID: 'S',
 *                                          S_IXGRP | S_ISGID: 's' };
 *    p[7]  = mode & S_IROTH ? 'r' : '-';
 *    p[8]  = mode & S_IWOTH ? 'w' : '-';
 *    p[9]  = <mode & S_IXOTH | S_ISVTX>: { 0: '-', S_IXOTH: 'x', S_ISVTX: 'T',
 *                                          S_IXOTH | S_ISVTX: 't' };
 *    p[10] = ' '; // '+', if "alternate or additional access control
 *                 //          methods associated with the inode"
 *    p[11] = '\0'; */
__NAMESPACE_LOCAL_USING_OR_IMPL(strmode, __FORCELOCAL __ATTR_NONNULL((2)) void __NOTHROW_NCX(__LIBCCALL strmode)(__mode_t __mode, char __p[12]) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strmode))(__mode, __p); })
#endif /* !__CRT_HAVE_strmode */
#endif /* __USE_BSD */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STRING_H)
#include <parts/uchar/string.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_STRING_H */
#endif /* __USE_UTF */

#ifdef __SSP_FORTIFY_LEVEL
#include <ssp/string.h>
#endif /* __SSP_FORTIFY_LEVEL */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CSTRING 1
#undef _STRING_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CSTRING */
#endif /* !_STRING_H */
