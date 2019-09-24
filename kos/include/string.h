/* HASH CRC-32:0x1ff25a26 */
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
#ifndef _STRING_H
#define _STRING_H 1

#include <__stdinc.h>
#if defined(_CXX_CSTRING) && !defined(__CXX_SYSTEM_HEADER)
/* Import all symbols into the global namespace when re-including "string.h" after "cstring" */
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
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
#else /* _CXX_CSTRING && !__CXX_SYSTEM_HEADER */
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <features.h>
#include <bits/types.h>
#include <hybrid/typecore.h>
#ifdef __USE_KOS
#include <parts/malloca.h>
#endif /* __USE_KOS */
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#include <xlocale.h>
#endif
#ifdef __USE_DOS
#include <parts/errno.h>
#include <crtdefs.h>
#endif

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
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef NULL
#define NULL __NULLPTR
#endif

/* Memory functions (An optional `[b|w|l|q]' suffix is a kos extension):
 *   [std] memcmp[b|w|l|q]      - Compare memory buffers and return the difference of the first non-matching byte/word/dword/qword
 *   [std] memset[b|w|l|q]      - Fill memory with a given byte/word/dword/qword
 *   [kos] mempset[b|w|l|q]     - Same as `memset[b|w|l|q]', but return `DST+N_(BYTES|WORDS|DWORDS)', rather than `DST'
 *   [std] memcpy[b|w|l|q]      - Copy memory between non-overlapping memory blocks.
 *   [glc] mempcpy[b|w|l|q]     - Same as `memcpy[b|w|l|q]', but return `DST+N_(BYTES|WORDS|DWORDS)', rather than `DST'
 *   [std] memmove[b|w|l|q]     - Move memory between potentially overlapping memory blocks.
 *   [kos] mempmove[b|w|l|q]    - Same as `memmove[b|w|l|q]', but return `DST+N_(BYTES|WORDS|DWORDS)', rather than `DST'
 *   [std] memchr[b|w|l|q]      - Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found.
 *   [glc] memrchr[b|w|l|q]     - Descendingly search for `NEEDLE', starting at `HAYSTACK+N_(BYTES|WORDS|DWORDS)'. - Return `NULL' if `NEEDLE' wasn't found.
 *   [glc] rawmemchr[b|w|l|q]   - Same as `memchr[b|w|l|q]' with a search limit of `(size_t)-1/sizeof(T)'
 *   [kos] rawmemrchr[b|w|l|q]  - Same as `memrchr[b|w|l|q]' without a search limit, starting at `HAYSTACK-sizeof(T)'
 *   [kos] memend[b|w|l|q]      - Same as `memchr[b|w|l|q]', but return `HAYSTACK+N_(BYTES|WORDS|DWORDS)', rather than `NULL' if `NEEDLE' wasn't found.
 *   [kos] memrend[b|w|l|q]     - Same as `memrchr[b|w|l|q]', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found.
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
 * String functions:
 *   [std] strlen               - Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')´)
 *   [std] strnlen              - Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´)
 *   [kos] strend               - Same as `STR+strlen(STR)'
 *   [kos] strnend              - Same as `STR+strnlen(STR, MAX_CHARS)'
 *   [std] strchr               - Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found.
 *   [std] strrchr              - Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found.
 *   [kos] strnchr              - Same as `strchr', but don't exceed `MAX_CHARS' characters.
 *   [kos] strnrchr             - Same as `strrchr', but don't exceed `MAX_CHARS' characters.
 *   [glc] strchrnul            - Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found.
 *   [kos] strrchrnul           - Same as `strrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found.
 *   [kos] strnchrnul           - Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found.
 *   [kos] strnrchrnul          - Same as `strnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found.
 *   [kos] stroff               - Same as `strchrnul', but return the offset from `STR', rather than the actual address.
 *   [kos] strroff              - Same as `strrchrnul', but return the offset from `STR', rather than the actual address.
 *   [kos] strnoff              - Same as `strnchrnul', but return the offset from `STR', rather than the actual address.
 *   [kos] strnroff             - Same as `strnrchrnul', but return the offset from `STR', rather than the actual address.
 *   [std] strcpy               - Same as <TODO: This replacement is incorrect> `memcpy(DST, SRC, (strlen(SRC)+1)*sizeof(char))´
 *   [std] strcat               - Same as <TODO: This replacement is incorrect> `memcpy(strend(DST), SRC, (strlen(SRC)+1)*sizeof(char))'
 *   [std] strncpy              - <TODO: Check if this doc is correct> Similar to `strcpy', but always write `DSTSIZE' characters, copying from `SRC' and filling the rest with padding ZEROes.
 *   [std] strncat              - <TODO: Check if this doc is correct> Same as Copy `strnlen(SRC, MAX_CHARS)' characters to `strend(DST)', then append a NUL-character thereafter. - Return `DST'.
 *   [glc] stpcpy               - Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´
 *   [glc] stpncpy              - <TODO: Check if this doc is correct> Same as `strncpy(DST, SRC, DSTSIZE)+strnlen(SRC, DSTSIZE)' (Returns a pointer to the end of `DST', or to the first NUL-character)
 */
__NAMESPACE_STD_BEGIN
#if defined(__fast_memcpy_defined)
/* Copy memory between non-overlapping memory blocks. */
__NAMESPACE_FAST_USING_OR_IMPL(memcpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memcpy)(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))(__dst, __src, __n_bytes); })
#elif defined(__CRT_HAVE_memcpy)
/* Copy memory between non-overlapping memory blocks. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memcpy,(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes),(__dst,__src,__n_bytes))
#else /* LIBC: memcpy */
__NAMESPACE_STD_END
#include <local/string/memcpy.h>
__NAMESPACE_STD_BEGIN
/* Copy memory between non-overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memcpy)(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy))(__dst, __src, __n_bytes); })
#endif /* memcpy... */
#if defined(__fast_memmove_defined)
/* Move memory between potentially overlapping memory blocks. */
__NAMESPACE_FAST_USING_OR_IMPL(memmove, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmove)(void *__dst, void const *__src, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmove))(__dst, __src, __n_bytes); })
#elif defined(__CRT_HAVE_memmove)
/* Move memory between potentially overlapping memory blocks. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memmove,(void *__dst, void const *__src, size_t __n_bytes),(__dst,__src,__n_bytes))
#else /* LIBC: memmove */
__NAMESPACE_STD_END
#include <local/string/memmove.h>
__NAMESPACE_STD_BEGIN
/* Move memory between potentially overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmove, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memmove)(void *__dst, void const *__src, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmove))(__dst, __src, __n_bytes); })
#endif /* memmove... */
#if defined(__fast_memset_defined)
/* Fill memory with a given byte */
__NAMESPACE_FAST_USING_OR_IMPL(memset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memset)(void *__restrict __dst, int __byte, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))(__dst, __byte, __n_bytes); })
#elif defined(__CRT_HAVE_memset)
/* Fill memory with a given byte */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memset,(void *__restrict __dst, int __byte, size_t __n_bytes),(__dst,__byte,__n_bytes))
#else /* LIBC: memset */
__NAMESPACE_STD_END
#include <local/string/memset.h>
__NAMESPACE_STD_BEGIN
/* Fill memory with a given byte */
__NAMESPACE_LOCAL_USING_OR_IMPL(memset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memset)(void *__restrict __dst, int __byte, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memset))(__dst, __byte, __n_bytes); })
#endif /* memset... */
#if defined(__fast_memcmp_defined)
/* Compare memory buffers and return the difference of the first non-matching byte */
__NAMESPACE_FAST_USING_OR_IMPL(memcmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memcmp)(void const *__s1, void const *__s2, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __n_bytes); })
#elif defined(__CRT_HAVE_memcmp)
/* Compare memory buffers and return the difference of the first non-matching byte */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcmp,(void const *__s1, void const *__s2, size_t __n_bytes),(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_bcmp)
/* Compare memory buffers and return the difference of the first non-matching byte */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcmp,(void const *__s1, void const *__s2, size_t __n_bytes),bcmp,(__s1,__s2,__n_bytes))
#else /* LIBC: memcmp */
__NAMESPACE_STD_END
#include <local/string/memcmp.h>
__NAMESPACE_STD_BEGIN
/* Compare memory buffers and return the difference of the first non-matching byte */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memcmp)(void const *__s1, void const *__s2, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp))(__s1, __s2, __n_bytes); })
#endif /* memcmp... */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __fast_memchr_defined
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memchr)(void *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __needle, __n_bytes); }
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memchr)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __needle, __n_bytes); }
}
#elif defined(__CRT_HAVE_memchr)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memchr,(void *__restrict __haystack, int __needle, size_t __n_bytes),memchr,(__haystack, __needle, __n_bytes))
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memchr,(void const *__restrict __haystack, int __needle, size_t __n_bytes),memchr,(__haystack, __needle, __n_bytes))
}
#else /* LIBC: memchr */
__NAMESPACE_STD_END
#include <local/string/memchr.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memchr)(void *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))(__haystack, __needle, __n_bytes); }
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memchr)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))(__haystack, __needle, __n_bytes); }
}
#endif /* memchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memchr_defined)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_FAST_USING_OR_IMPL(memchr, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memchr)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __needle, __n_bytes); })
#elif defined(__CRT_HAVE_memchr)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memchr,(void const *__restrict __haystack, int __needle, size_t __n_bytes),(__haystack,__needle,__n_bytes))
#else /* LIBC: memchr */
__NAMESPACE_STD_END
#include <local/string/memchr.h>
__NAMESPACE_STD_BEGIN
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memchr, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memchr)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))(__haystack, __needle, __n_bytes); })
#endif /* memchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_strlen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,strlen,(char const *__restrict __string),(__string))
#else /* LIBC: strlen */
__NAMESPACE_STD_END
#include <local/string/strlen.h>
__NAMESPACE_STD_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__NAMESPACE_LOCAL_USING_OR_IMPL(strlen, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL strlen)(char const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlen))(__string); })
#endif /* strlen... */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strchr)(char *__restrict __haystack, int __needle) { return __builtin_strchr(__haystack, __needle); }
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strchr)(char const *__restrict __haystack, int __needle) { return __builtin_strchr(__haystack, __needle); }
}
#elif defined(__CRT_HAVE_strchr)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strchr,(char *__restrict __haystack, int __needle),strchr,(__haystack, __needle))
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strchr,(char const *__restrict __haystack, int __needle),strchr,(__haystack, __needle))
}
#else /* LIBC: strchr */
__NAMESPACE_STD_END
#include <local/string/strchr.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strchr)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr))(__haystack, __needle); }
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strchr)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr))(__haystack, __needle); }
}
#endif /* strchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strchr)(char const *__restrict __haystack, int __needle) { return __builtin_strchr(__haystack, __needle); }
#elif defined(__CRT_HAVE_strchr)
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strchr,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* LIBC: strchr */
__NAMESPACE_STD_END
#include <local/string/strchr.h>
__NAMESPACE_STD_BEGIN
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strchr, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strchr)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr))(__haystack, __needle); })
#endif /* strchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if __has_builtin(__builtin_strrchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strrchr)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strrchr)(char *__restrict __haystack, int __needle) { return __builtin_strrchr(__haystack, __needle); }
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strrchr)(char const *__restrict __haystack, int __needle) { return __builtin_strrchr(__haystack, __needle); }
}
#elif defined(__CRT_HAVE_strrchr)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strrchr,(char *__restrict __haystack, int __needle),strrchr,(__haystack, __needle))
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strrchr,(char const *__restrict __haystack, int __needle),strrchr,(__haystack, __needle))
}
#else /* LIBC: strrchr */
__NAMESPACE_STD_END
#include <local/string/strrchr.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strrchr)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchr))(__haystack, __needle); }
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strrchr)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchr))(__haystack, __needle); }
}
#endif /* strrchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if __has_builtin(__builtin_strrchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strrchr)
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strrchr)(char const *__restrict __haystack, int __needle) { return __builtin_strrchr(__haystack, __needle); }
#elif defined(__CRT_HAVE_strrchr)
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strrchr,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* LIBC: strrchr */
__NAMESPACE_STD_END
#include <local/string/strrchr.h>
__NAMESPACE_STD_BEGIN
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strrchr, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strrchr)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchr))(__haystack, __needle); })
#endif /* strrchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcmp)(char const *__s1, char const *__s2) { return __builtin_strcmp(__s1, __s2); }
#elif defined(__CRT_HAVE_strcmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcmp,(char const *__s1, char const *__s2),(__s1,__s2))
#else /* LIBC: strcmp */
__NAMESPACE_STD_END
#include <local/string/strcmp.h>
__NAMESPACE_STD_BEGIN
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__NAMESPACE_LOCAL_USING_OR_IMPL(strcmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcmp))(__s1, __s2); })
#endif /* strcmp... */
#if __has_builtin(__builtin_strncmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncmp)
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncmp)(char const *__s1, char const *__s2, size_t __maxlen) { return __builtin_strncmp(__s1, __s2, __maxlen); }
#elif defined(__CRT_HAVE_strncmp)
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmp,(char const *__s1, char const *__s2, size_t __maxlen),(__s1,__s2,__maxlen))
#else /* LIBC: strncmp */
__NAMESPACE_STD_END
#include <local/string/strncmp.h>
__NAMESPACE_STD_BEGIN
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
__NAMESPACE_LOCAL_USING_OR_IMPL(strncmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncmp)(char const *__s1, char const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncmp))(__s1, __s2, __maxlen); })
#endif /* strncmp... */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if __has_builtin(__builtin_strstr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strstr)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strstr)(char *__haystack, char *__needle) { return __builtin_strstr(__haystack, __needle); }
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) char const *__NOTHROW_NCX(__LIBCCALL strstr)(char const *__haystack, char const *__needle) { return __builtin_strstr(__haystack, __needle); }
}
#elif defined(__CRT_HAVE_strstr)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strstr,(char *__haystack, char *__needle),strstr,(__haystack, __needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),char const *,__NOTHROW_NCX,strstr,(char const *__haystack, char const *__needle),strstr,(__haystack, __needle))
}
#else /* LIBC: strstr */
__NAMESPACE_STD_END
#include <local/string/strstr.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strstr)(char *__haystack, char *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strstr))(__haystack, __needle); }
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) char const *__NOTHROW_NCX(__LIBCCALL strstr)(char const *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strstr))(__haystack, __needle); }
}
#endif /* strstr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if __has_builtin(__builtin_strstr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strstr)
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strstr)(char const *__haystack, char const *__needle) { return __builtin_strstr(__haystack, __needle); }
#elif defined(__CRT_HAVE_strstr)
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strstr,(char const *__haystack, char const *__needle),(__haystack,__needle))
#else /* LIBC: strstr */
__NAMESPACE_STD_END
#include <local/string/strstr.h>
__NAMESPACE_STD_BEGIN
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strstr, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strstr)(char const *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strstr))(__haystack, __needle); })
#endif /* strstr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if __has_builtin(__builtin_strcpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcpy)
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strcpy)(char *__restrict __buf, char const *__restrict __src) { return __builtin_strcpy(__buf, __src); }
#elif defined(__CRT_HAVE_strcpy)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strcpy,(char *__restrict __buf, char const *__restrict __src),(__buf,__src))
#else /* LIBC: strcpy */
__NAMESPACE_STD_END
#include <local/string/strcpy.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strcpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strcpy)(char *__restrict __buf, char const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcpy))(__buf, __src); })
#endif /* strcpy... */
#if __has_builtin(__builtin_strncpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncpy)
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strncpy)(char *__restrict __buf, char const *__restrict __src, size_t __buflen) { return __builtin_strncpy(__buf, __src, __buflen); }
#elif defined(__CRT_HAVE_strncpy)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strncpy,(char *__restrict __buf, char const *__restrict __src, size_t __buflen),(__buf,__src,__buflen))
#else /* LIBC: strncpy */
__NAMESPACE_STD_END
#include <local/string/strncpy.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strncpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strncpy)(char *__restrict __buf, char const *__restrict __src, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncpy))(__buf, __src, __buflen); })
#endif /* strncpy... */
#if __has_builtin(__builtin_strcat) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcat)
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strcat)(char *__restrict __buf, char const *__restrict __src) { return __builtin_strcat(__buf, __src); }
#elif defined(__CRT_HAVE_strcat)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strcat,(char *__restrict __buf, char const *__restrict __src),(__buf,__src))
#else /* LIBC: strcat */
__NAMESPACE_STD_END
#include <local/string/strcat.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strcat, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strcat)(char *__restrict __buf, char const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcat))(__buf, __src); })
#endif /* strcat... */
#if __has_builtin(__builtin_strncat) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncat)
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strncat)(char *__restrict __buf, char const *__restrict __src, size_t __buflen) { return __builtin_strncat(__buf, __src, __buflen); }
#elif defined(__CRT_HAVE_strncat)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strncat,(char *__restrict __buf, char const *__restrict __src, size_t __buflen),(__buf,__src,__buflen))
#else /* LIBC: strncat */
__NAMESPACE_STD_END
#include <local/string/strncat.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strncat, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strncat)(char *__restrict __buf, char const *__restrict __src, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncat))(__buf, __src, __buflen); })
#endif /* strncat... */
#if __has_builtin(__builtin_strcspn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcspn)
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL strcspn)(char const *__haystack, char const *__reject) { return __builtin_strcspn(__haystack, __reject); }
#elif defined(__CRT_HAVE_strcspn)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,strcspn,(char const *__haystack, char const *__reject),(__haystack,__reject))
#else /* LIBC: strcspn */
__NAMESPACE_STD_END
#include <local/string/strcspn.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strcspn, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL strcspn)(char const *__haystack, char const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcspn))(__haystack, __reject); })
#endif /* strcspn... */
#if __has_builtin(__builtin_strspn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strspn)
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL strspn)(char const *__haystack, char const *__accept) { return __builtin_strspn(__haystack, __accept); }
#elif defined(__CRT_HAVE_strspn)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,strspn,(char const *__haystack, char const *__accept),(__haystack,__accept))
#else /* LIBC: strspn */
__NAMESPACE_STD_END
#include <local/string/strspn.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strspn, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL strspn)(char const *__haystack, char const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strspn))(__haystack, __accept); })
#endif /* strspn... */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if __has_builtin(__builtin_strpbrk) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strpbrk)
extern "C++" {
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strpbrk)(char *__haystack, char const *__accept) { return __builtin_strpbrk(__haystack, __accept); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) char const *__NOTHROW_NCX(__LIBCCALL strpbrk)(char const *__haystack, char const *__accept) { return __builtin_strpbrk(__haystack, __accept); }
}
#elif defined(__CRT_HAVE_strpbrk)
extern "C++" {
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strpbrk,(char *__haystack, char const *__accept),strpbrk,(__haystack, __accept))
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),char const *,__NOTHROW_NCX,strpbrk,(char const *__haystack, char const *__accept),strpbrk,(__haystack, __accept))
}
#else /* LIBC: strpbrk */
__NAMESPACE_STD_END
#include <local/string/strpbrk.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strpbrk)(char *__haystack, char const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strpbrk))(__haystack, __accept); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) char const *__NOTHROW_NCX(__LIBCCALL strpbrk)(char const *__haystack, char const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strpbrk))(__haystack, __accept); }
}
#endif /* strpbrk... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if __has_builtin(__builtin_strpbrk) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strpbrk)
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strpbrk)(char const *__haystack, char const *__accept) { return __builtin_strpbrk(__haystack, __accept); }
#elif defined(__CRT_HAVE_strpbrk)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strpbrk,(char const *__haystack, char const *__accept),(__haystack,__accept))
#else /* LIBC: strpbrk */
__NAMESPACE_STD_END
#include <local/string/strpbrk.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strpbrk, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strpbrk)(char const *__haystack, char const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strpbrk))(__haystack, __accept); })
#endif /* strpbrk... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_strtok)
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,strtok,(char *__string, char const *__delim),(__string,__delim))
#else /* LIBC: strtok */
__NAMESPACE_STD_END
#include <local/string/strtok.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtok, __FORCELOCAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL strtok)(char *__string, char const *__delim) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtok))(__string, __delim); })
#endif /* strtok... */
#if defined(__CRT_HAVE_strcoll)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcoll,(char const *__s1, char const *__s2),(__s1,__s2))
#else /* LIBC: strcoll */
__NAMESPACE_STD_END
#include <local/string/strcoll.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strcoll, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcoll)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcoll))(__s1, __s2); })
#endif /* strcoll... */
#if defined(__CRT_HAVE_strxfrm)
__CDECLARE(__ATTR_NONNULL((2)),size_t,__NOTHROW_NCX,strxfrm,(char *__dst, char const *__restrict __src, size_t __maxlen),(__dst,__src,__maxlen))
#else /* LIBC: strxfrm */
__NAMESPACE_STD_END
#include <local/string/strxfrm.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strxfrm, __FORCELOCAL __ATTR_NONNULL((2)) size_t __NOTHROW_NCX(__LIBCCALL strxfrm)(char *__dst, char const *__restrict __src, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strxfrm))(__dst, __src, __maxlen); })
#endif /* strxfrm... */
#if defined(__CRT_HAVE_strerror)
__CDECLARE(__ATTR_WUNUSED __ATTR_RETNONNULL,char *,__NOTHROW_NCX,strerror,(int __errnum),(__errnum))
#else /* LIBC: strerror */
__NAMESPACE_STD_END
#include <local/string/strerror.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strerror, __FORCELOCAL __ATTR_WUNUSED __ATTR_RETNONNULL char *__NOTHROW_NCX(__LIBCCALL strerror)(int __errnum) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strerror))(__errnum); })
#endif /* strerror... */
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
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL strnlen)(char const *__restrict __string, size_t __maxlen) { return __builtin_strnlen(__string, __maxlen); }
#elif defined(__CRT_HAVE_strnlen)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,strnlen,(char const *__restrict __string, size_t __maxlen),(__string,__maxlen))
#else /* LIBC: strnlen */
#include <local/string/strnlen.h>
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnlen, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL strnlen)(char const *__restrict __string, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnlen))(__string, __maxlen); })
#endif /* strnlen... */
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#ifdef __USE_XOPEN2K8
#if __has_builtin(__builtin_stpcpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpcpy)
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL stpcpy)(char *__restrict __buf, char const *__restrict __src) { return __builtin_stpcpy(__buf, __src); }
#elif defined(__CRT_HAVE_stpcpy)
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,stpcpy,(char *__restrict __buf, char const *__restrict __src),(__buf,__src))
#else /* LIBC: stpcpy */
#include <local/string/stpcpy.h>
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__NAMESPACE_LOCAL_USING_OR_IMPL(stpcpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL stpcpy)(char *__restrict __buf, char const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stpcpy))(__buf, __src); })
#endif /* stpcpy... */
#if __has_builtin(__builtin_stpncpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpncpy)
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL stpncpy)(char *__restrict __buf, char const *__restrict __src, size_t __buflen) { return __builtin_stpncpy(__buf, __src, __buflen); }
#elif defined(__CRT_HAVE_stpncpy)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,stpncpy,(char *__restrict __buf, char const *__restrict __src, size_t __buflen),(__buf,__src,__buflen))
#else /* LIBC: stpncpy */
#include <local/string/stpncpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(stpncpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL stpncpy)(char *__restrict __buf, char const *__restrict __src, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stpncpy))(__buf, __src, __buflen); })
#endif /* stpncpy... */
#if __has_builtin(__builtin_stpcpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpcpy)
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __stpcpy)(char *__restrict __buf, char const *__restrict __src) { return __builtin_stpcpy(__buf, __src); }
#elif defined(__CRT_HAVE___stpcpy)
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__stpcpy,(char *__restrict __buf, char const *__restrict __src),(__buf,__src))
#elif defined(__CRT_HAVE_stpcpy)
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__stpcpy,(char *__restrict __buf, char const *__restrict __src),stpcpy,(__buf,__src))
#else /* LIBC: stpcpy */
#include <local/string/stpcpy.h>
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __stpcpy)(char *__restrict __buf, char const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stpcpy))(__buf, __src); }
#endif /* __stpcpy... */
#if __has_builtin(__builtin_stpncpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpncpy)
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __stpncpy)(char *__restrict __buf, char const *__restrict __src, size_t __buflen) { return __builtin_stpncpy(__buf, __src, __buflen); }
#elif defined(__CRT_HAVE___stpncpy)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__stpncpy,(char *__restrict __buf, char const *__restrict __src, size_t __buflen),(__buf,__src,__buflen))
#elif defined(__CRT_HAVE_stpncpy)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__stpncpy,(char *__restrict __buf, char const *__restrict __src, size_t __buflen),stpncpy,(__buf,__src,__buflen))
#else /* LIBC: stpncpy */
#include <local/string/stpncpy.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __stpncpy)(char *__restrict __buf, char const *__restrict __src, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stpncpy))(__buf, __src, __buflen); }
#endif /* __stpncpy... */
#if defined(__CRT_HAVE_strcoll_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcoll_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__strcoll_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcoll_l,(char const *__s1, char const *__s2, __locale_t __locale),_strcoll_l,(__s1,__s2,__locale))
#else /* LIBC: strcoll_l */
#include <local/string/strcoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcoll_l, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcoll_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcoll_l))(__s1, __s2, __locale); })
#endif /* strcoll_l... */
#if defined(__CRT_HAVE_strxfrm_l)
__CDECLARE(__ATTR_NONNULL((2)),size_t,__NOTHROW_NCX,strxfrm_l,(char *__dst, char const *__restrict __src, size_t __maxlen, __locale_t __locale),(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE__strxfrm_l)
__CREDIRECT(__ATTR_NONNULL((2)),size_t,__NOTHROW_NCX,strxfrm_l,(char *__dst, char const *__restrict __src, size_t __maxlen, __locale_t __locale),_strxfrm_l,(__dst,__src,__maxlen,__locale))
#else /* LIBC: strxfrm_l */
#include <local/string/strxfrm_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strxfrm_l, __FORCELOCAL __ATTR_NONNULL((2)) size_t __NOTHROW_NCX(__LIBCCALL strxfrm_l)(char *__dst, char const *__restrict __src, size_t __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strxfrm_l))(__dst, __src, __maxlen, __locale); })
#endif /* strxfrm_l... */
#if defined(__CRT_HAVE_strerror_l)
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_NCX,strerror_l,(int __errnum, __locale_t __locale),(__errnum,__locale))
#else /* LIBC: strerror_l */
#include <local/string/strerror_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strerror_l, __FORCELOCAL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL strerror_l)(int __errnum, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strerror_l))(__errnum, __locale); })
#endif /* strerror_l... */
#if defined(__CRT_HAVE_strsignal)
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_NCX,strsignal,(int __signo),(__signo))
#endif /* strsignal... */
#if __has_builtin(__builtin_strndup) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strndup)
__FORCELOCAL __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strndup)(char const *__restrict __string, size_t __max_chars) { return __builtin_strndup(__string, __max_chars); }
#elif defined(__CRT_HAVE_strndup)
__CDECLARE(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strndup,(char const *__restrict __string, size_t __max_chars),(__string,__max_chars))
#elif (defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)) || (__has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)) || defined(__CRT_HAVE_malloc)
#include <local/string/strndup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strndup, __FORCELOCAL __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strndup)(char const *__restrict __string, size_t __max_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strndup))(__string, __max_chars); })
#endif /* strndup... */
#endif /* __USE_XOPEN2K8 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#if __has_builtin(__builtin_strdup) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strdup)
__FORCELOCAL __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strdup)(char const *__restrict __string) { return __builtin_strdup(__string); }
#elif defined(__CRT_HAVE_strdup)
__CDECLARE(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strdup,(char const *__restrict __string),(__string))
#elif defined(__CRT_HAVE__strdup)
__CREDIRECT(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strdup,(char const *__restrict __string),_strdup,(__string))
#elif defined(__CRT_HAVE___strdup)
__CREDIRECT(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strdup,(char const *__restrict __string),__strdup,(__string))
#elif (defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)) || (__has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)) || defined(__CRT_HAVE_malloc)
#include <local/string/strdup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strdup, __FORCELOCAL __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strdup)(char const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strdup))(__string); })
#endif /* strdup... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 || __USE_DOS */

#ifdef __USE_POSIX
#if defined(__CRT_HAVE_strtok_r)
__CDECLARE(__ATTR_NONNULL((2, 3)),char *,__NOTHROW_NCX,strtok_r,(char *__string, char const *__delim, char **__restrict __save_ptr),(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_strtok_s)
__CREDIRECT(__ATTR_NONNULL((2, 3)),char *,__NOTHROW_NCX,strtok_r,(char *__string, char const *__delim, char **__restrict __save_ptr),strtok_s,(__string,__delim,__save_ptr))
#else /* LIBC: strtok_r */
#include <local/string/strtok_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtok_r, __FORCELOCAL __ATTR_NONNULL((2, 3)) char *__NOTHROW_NCX(__LIBCCALL strtok_r)(char *__string, char const *__delim, char **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtok_r))(__string, __delim, __save_ptr); })
#endif /* strtok_r... */
#endif /* __USE_POSIX */

#ifdef __USE_GNU
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memrchr)
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrchr,(void *__restrict __haystack, int __needle, size_t __n_bytes),memrchr,(__haystack, __needle, __n_bytes))
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memrchr,(void const *__restrict __haystack, int __needle, size_t __n_bytes),memrchr,(__haystack, __needle, __n_bytes))
}
#else /* LIBC: memrchr */
#include <local/string/memrchr.h>
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrchr)(void *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))(__haystack, __needle, __n_bytes); }
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memrchr)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))(__haystack, __needle, __n_bytes); }
}
#endif /* memrchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memrchr)
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrchr,(void const *__restrict __haystack, int __needle, size_t __n_bytes),(__haystack,__needle,__n_bytes))
#else /* LIBC: memrchr */
#include <local/string/memrchr.h>
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrchr, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrchr)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))(__haystack, __needle, __n_bytes); })
#endif /* memrchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemchr)
extern "C++" {
/* Same as `memchr' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemchr,(void *__restrict __haystack, int __needle),rawmemchr,(__haystack, __needle))
/* Same as `memchr' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,rawmemchr,(void const *__restrict __haystack, int __needle),rawmemchr,(__haystack, __needle))
}
#else /* LIBC: rawmemchr */
#include <local/string/rawmemchr.h>
extern "C++" {
/* Same as `memchr' with a search limit of `(size_t)-1' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemchr)(void *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchr))(__haystack, __needle); }
/* Same as `memchr' with a search limit of `(size_t)-1' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL rawmemchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchr))(__haystack, __needle); }
}
#endif /* rawmemchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemchr)
/* Same as `memchr' with a search limit of `(size_t)-1' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemchr,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* LIBC: rawmemchr */
#include <local/string/rawmemchr.h>
/* Same as `memchr' with a search limit of `(size_t)-1' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemchr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchr))(__haystack, __needle); })
#endif /* rawmemchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_strchrnul)
extern "C++" {
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strchrnul,(char *__restrict __haystack, int __needle),strchrnul,(__haystack, __needle))
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strchrnul,(char const *__restrict __haystack, int __needle),strchrnul,(__haystack, __needle))
}
#else /* LIBC: strchrnul */
#include <local/string/strchrnul.h>
extern "C++" {
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strchrnul)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchrnul))(__haystack, __needle); }
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strchrnul)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchrnul))(__haystack, __needle); }
}
#endif /* strchrnul... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_strchrnul)
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strchrnul,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* LIBC: strchrnul */
#include <local/string/strchrnul.h>
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strchrnul, __FORCELOCAL __ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strchrnul)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchrnul))(__haystack, __needle); })
#endif /* strchrnul... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#ifndef __basename_defined
#define __basename_defined 1
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_basename)
extern "C++" {
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE,char *,__NOTHROW_NCX,basename,(char *__filename),basename,(__filename))
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE,char const *,__NOTHROW_NCX,basename,(char const *__filename),basename,(__filename))
}
#else /* LIBC: basename */
#include <local/string/basename.h>
extern "C++" {
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE char *__NOTHROW_NCX(__LIBCCALL basename)(char *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(basename))(__filename); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE char const *__NOTHROW_NCX(__LIBCCALL basename)(char const *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(basename))(__filename); }
}
#endif /* basename... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_basename)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE,char *,__NOTHROW_NCX,basename,(char const *__filename),(__filename))
#else /* LIBC: basename */
#include <local/string/basename.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(basename, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE char *__NOTHROW_NCX(__LIBCCALL basename)(char const *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(basename))(__filename); })
#endif /* basename... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !__basename_defined */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_strcasestr)
extern "C++" {
/* Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strcasestr,(char *__haystack, char const *__needle),strcasestr,(__haystack, __needle))
/* Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),char const *,__NOTHROW_NCX,strcasestr,(char const *__haystack, char const *__needle),strcasestr,(__haystack, __needle))
}
#else /* LIBC: strcasestr */
#include <local/string/strcasestr.h>
extern "C++" {
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strcasestr)(char *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasestr))(__haystack, __needle); }
/* Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) char const *__NOTHROW_NCX(__LIBCCALL strcasestr)(char const *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasestr))(__haystack, __needle); }
}
#endif /* strcasestr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_strcasestr)
/* Same as `strstr', but ignore casing */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strcasestr,(char const *__haystack, char const *__needle),(__haystack,__needle))
#else /* LIBC: strcasestr */
#include <local/string/strcasestr.h>
/* Same as `strstr', but ignore casing */
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasestr, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strcasestr)(char const *__haystack, char const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasestr))(__haystack, __needle); })
#endif /* strcasestr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memmem)
extern "C++" {
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memmem,(void *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen),memmem,(__haystack, __haystacklen, __needle, __needlelen))
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memmem,(void const *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen),memmem,(__haystack, __haystacklen, __needle, __needlelen))
}
#else /* LIBC: memmem */
#include <local/string/memmem.h>
extern "C++" {
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memmem)(void *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmem))(__haystack, __haystacklen, __needle, __needlelen); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) void const *__NOTHROW_NCX(__LIBCCALL memmem)(void const *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmem))(__haystack, __haystacklen, __needle, __needlelen); }
}
#endif /* memmem... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memmem)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memmem,(void const *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen),(__haystack,__haystacklen,__needle,__needlelen))
#else /* LIBC: memmem */
#include <local/string/memmem.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memmem, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memmem)(void const *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmem))(__haystack, __haystacklen, __needle, __needlelen); })
#endif /* memmem... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_strverscmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strverscmp,(char const *__s1, char const *__s2),(__s1,__s2))
#else /* LIBC: strverscmp */
#include <local/string/strverscmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strverscmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strverscmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strverscmp))(__s1, __s2); })
#endif /* strverscmp... */
#if defined(__fast_mempcpy_defined)
/* Same as `memcpy', but return `DST+N_BYTES', rather than `DST' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempcpy)(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE___mempcpy)
/* Same as `memcpy', but return `DST+N_BYTES', rather than `DST' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__mempcpy,(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes),(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE_mempcpy)
/* Same as `memcpy', but return `DST+N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__mempcpy,(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#else /* LIBC: mempcpy */
#include <local/string/mempcpy.h>
/* Same as `memcpy', but return `DST+N_BYTES', rather than `DST' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __mempcpy)(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpy))(__dst, __src, __n_bytes); }
#endif /* __mempcpy... */
#if defined(__fast_mempcpy_defined)
/* Same as `memcpy', but return `DST+N_BYTES', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempcpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempcpy)(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))(__dst, __src, __n_bytes); })
#elif defined(__CRT_HAVE_mempcpy)
/* Same as `memcpy', but return `DST+N_BYTES', rather than `DST' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempcpy,(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes),(__dst,__src,__n_bytes))
#else /* LIBC: mempcpy */
#include <local/string/mempcpy.h>
/* Same as `memcpy', but return `DST+N_BYTES', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempcpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempcpy)(void *__restrict __dst, void const *__restrict __src, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpy))(__dst, __src, __n_bytes); })
#endif /* mempcpy... */
#if defined(__CRT_HAVE_strfry)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strfry,(char *__restrict __string),(__string))
#else /* LIBC: strfry */
#include <local/string/strfry.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strfry, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strfry)(char *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strfry))(__string); })
#endif /* strfry... */
#if defined(__CRT_HAVE_memfrob)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memfrob,(void *__buf, size_t __num_bytes),(__buf,__num_bytes))
#else /* LIBC: memfrob */
#include <local/string/memfrob.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memfrob, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memfrob)(void *__buf, size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memfrob))(__buf, __num_bytes); })
#endif /* memfrob... */
#ifndef __strcasecmp_l_defined
#define __strcasecmp_l_defined 1
#if defined(__CRT_HAVE_strcasecmp_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__stricmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),_stricmp_l,(__s1,__s2,__locale))
#else /* LIBC: strcasecmp_l */
#include <local/string/strcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasecmp_l, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcasecmp_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp_l))(__s1, __s2, __locale); })
#endif /* strcasecmp_l... */
#endif /* !__strcasecmp_l_defined */
#ifndef __strncasecmp_l_defined
#define __strncasecmp_l_defined 1
#if defined(__CRT_HAVE_strncasecmp_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),_strnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncmpi_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),_strncmpi_l,(__s1,__s2,__maxlen,__locale))
#else /* LIBC: strncasecmp_l */
#include <local/string/strncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncasecmp_l, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncasecmp_l)(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp_l))(__s1, __s2, __maxlen, __locale); })
#endif /* strncasecmp_l... */
#endif /* !__strncasecmp_l_defined */
#endif /* __USE_GNU */

#ifdef __USE_XOPEN2K
#ifdef __USE_GNU
#if defined(__CRT_HAVE_strerror_r)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((2)),char *,__NOTHROW_NCX,strerror_r,(int __errnum, char *__buf, size_t __buflen),(__errnum,__buf,__buflen))
#elif defined(__CRT_HAVE___strerror_r)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((2)),char *,__NOTHROW_NCX,strerror_r,(int __errnum, char *__buf, size_t __buflen),__strerror_r,(__errnum,__buf,__buflen))
#endif /* strerror_r... */
#else /* __USE_GNU */
#if defined(__CRT_HAVE___xpg_strerror_r)
__CREDIRECT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,strerror_r,(int __errnum, char *__buf, size_t __buflen),__xpg_strerror_r,(__errnum,__buf,__buflen))
#endif /* strerror_r... */
#endif /* !__USE_GNU */
#endif /* __USE_XOPEN2K */

#ifdef __USE_MISC
#if defined(__CRT_HAVE_strsep)
__CDECLARE(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strsep,(char **__restrict __stringp, char const *__restrict __delim),(__stringp,__delim))
#else /* LIBC: strsep */
#include <local/string/strsep.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strsep, __FORCELOCAL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strsep)(char **__restrict __stringp, char const *__restrict __delim) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strsep))(__stringp, __delim); })
#endif /* strsep... */
#ifndef __bcopy_defined
#define __bcopy_defined 1
#if __has_builtin(__builtin_bcopy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_bcopy)
__FORCELOCAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL bcopy)(void const *__src, void *__dst, size_t __num_bytes) { return __builtin_bcopy(__src, __dst, __num_bytes); }
#elif defined(__CRT_HAVE_bcopy)
__CDECLARE_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,bcopy,(void const *__src, void *__dst, size_t __num_bytes),(__src,__dst,__num_bytes))
#else /* LIBC: bcopy */
#include <local/strings/bcopy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bcopy, __FORCELOCAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL bcopy)(void const *__src, void *__dst, size_t __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bcopy))(__src, __dst, __num_bytes); })
#endif /* bcopy... */
#endif /* !__bcopy_defined */
#ifndef __bzero_defined
#define __bzero_defined 1
#if __has_builtin(__builtin_bzero) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_bzero)
__FORCELOCAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzero)(void *__restrict __dst, size_t __num_bytes) { return __builtin_bzero(__dst, __num_bytes); }
#elif defined(__CRT_HAVE_bzero)
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,bzero,(void *__restrict __dst, size_t __num_bytes),(__dst,__num_bytes))
#else /* LIBC: bzero */
#include <local/strings/bzero.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bzero, __FORCELOCAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzero)(void *__restrict __dst, size_t __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzero))(__dst, __num_bytes); })
#endif /* bzero... */
#endif /* !__bzero_defined */
#ifndef __bcmp_defined
#define __bcmp_defined 1
#if defined(__fast_memcmp_defined)
/* Compare memory buffers and return the difference of the first non-matching byte */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, size_t __num_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __num_bytes); }
#elif defined(__CRT_HAVE_bcmp)
/* Compare memory buffers and return the difference of the first non-matching byte */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, size_t __num_bytes),(__s1,__s2,__num_bytes))
#elif defined(__CRT_HAVE_memcmp)
/* Compare memory buffers and return the difference of the first non-matching byte */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, size_t __num_bytes),memcmp,(__s1,__s2,__num_bytes))
#else /* LIBC: memcmp */
#include <local/string/memcmp.h>
/* Compare memory buffers and return the difference of the first non-matching byte */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp))(__s1, __s2, __num_bytes); }
#endif /* bcmp... */
#endif /* !__bcmp_defined */
#ifndef __index_defined
#define __index_defined 1
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRINGS_H_PROTO)
#if __has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_index)
extern "C++" {
__FORCELOCAL __ATTR_NONNULL((1)) __ATTR_WUNUSED __ATTR_PURE char *__NOTHROW_NCX(__LIBCCALL index)(char *__restrict __haystack, int __needle) { return __builtin_index(__haystack, __needle); }
__FORCELOCAL __ATTR_NONNULL((1)) __ATTR_WUNUSED __ATTR_PURE char const *__NOTHROW_NCX(__LIBCCALL index)(char const *__restrict __haystack, int __needle) { return __builtin_index(__haystack, __needle); }
}
#elif defined(__CRT_HAVE_index)
extern "C++" {
__CREDIRECT(__ATTR_NONNULL((1)) __ATTR_WUNUSED __ATTR_PURE,char *,__NOTHROW_NCX,index,(char *__restrict __haystack, int __needle),index,(__haystack, __needle))
__CREDIRECT(__ATTR_NONNULL((1)) __ATTR_WUNUSED __ATTR_PURE,char const *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),index,(__haystack, __needle))
}
#else /* LIBC: index */
#include <local/strings/index.h>
extern "C++" {
__FORCELOCAL __ATTR_NONNULL((1)) __ATTR_WUNUSED __ATTR_PURE char *__NOTHROW_NCX(__LIBCCALL index)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(index))(__haystack, __needle); }
__FORCELOCAL __ATTR_NONNULL((1)) __ATTR_WUNUSED __ATTR_PURE char const *__NOTHROW_NCX(__LIBCCALL index)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(index))(__haystack, __needle); }
}
#endif /* index... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRINGS_H_PROTO */
#if __has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_index)
__FORCELOCAL __ATTR_NONNULL((1)) __ATTR_WUNUSED __ATTR_PURE char *__NOTHROW_NCX(__LIBCCALL index)(char const *__restrict __haystack, int __needle) { return __builtin_index(__haystack, __needle); }
#elif defined(__CRT_HAVE_index)
__CDECLARE(__ATTR_NONNULL((1)) __ATTR_WUNUSED __ATTR_PURE,char *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* LIBC: index */
#include <local/strings/index.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(index, __FORCELOCAL __ATTR_NONNULL((1)) __ATTR_WUNUSED __ATTR_PURE char *__NOTHROW_NCX(__LIBCCALL index)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(index))(__haystack, __needle); })
#endif /* index... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRINGS_H_PROTO */
#endif /* !__index_defined */
#ifndef __rindex_defined
#define __rindex_defined 1
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRINGS_H_PROTO)
#if __has_builtin(__builtin_rindex) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rindex)
extern "C++" {
__FORCELOCAL __ATTR_NONNULL((1)) __ATTR_WUNUSED __ATTR_PURE char *__NOTHROW_NCX(__LIBCCALL rindex)(char *__restrict __haystack, int __needle) { return __builtin_rindex(__haystack, __needle); }
__FORCELOCAL __ATTR_NONNULL((1)) __ATTR_WUNUSED __ATTR_PURE char const *__NOTHROW_NCX(__LIBCCALL rindex)(char const *__restrict __haystack, int __needle) { return __builtin_rindex(__haystack, __needle); }
}
#elif defined(__CRT_HAVE_rindex)
extern "C++" {
__CREDIRECT(__ATTR_NONNULL((1)) __ATTR_WUNUSED __ATTR_PURE,char *,__NOTHROW_NCX,rindex,(char *__restrict __haystack, int __needle),rindex,(__haystack, __needle))
__CREDIRECT(__ATTR_NONNULL((1)) __ATTR_WUNUSED __ATTR_PURE,char const *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),rindex,(__haystack, __needle))
}
#else /* LIBC: rindex */
#include <local/strings/rindex.h>
extern "C++" {
__FORCELOCAL __ATTR_NONNULL((1)) __ATTR_WUNUSED __ATTR_PURE char *__NOTHROW_NCX(__LIBCCALL rindex)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rindex))(__haystack, __needle); }
__FORCELOCAL __ATTR_NONNULL((1)) __ATTR_WUNUSED __ATTR_PURE char const *__NOTHROW_NCX(__LIBCCALL rindex)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rindex))(__haystack, __needle); }
}
#endif /* rindex... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRINGS_H_PROTO */
#if __has_builtin(__builtin_rindex) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rindex)
__FORCELOCAL __ATTR_NONNULL((1)) __ATTR_WUNUSED __ATTR_PURE char *__NOTHROW_NCX(__LIBCCALL rindex)(char const *__restrict __haystack, int __needle) { return __builtin_rindex(__haystack, __needle); }
#elif defined(__CRT_HAVE_rindex)
__CDECLARE(__ATTR_NONNULL((1)) __ATTR_WUNUSED __ATTR_PURE,char *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* LIBC: rindex */
#include <local/strings/rindex.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(rindex, __FORCELOCAL __ATTR_NONNULL((1)) __ATTR_WUNUSED __ATTR_PURE char *__NOTHROW_NCX(__LIBCCALL rindex)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rindex))(__haystack, __needle); })
#endif /* rindex... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRINGS_H_PROTO */
#endif /* !__rindex_defined */
#ifndef __strcasecmp_defined
#define __strcasecmp_defined 1
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcasecmp)(char const *__s1, char const *__s2) { return __builtin_strcasecmp(__s1, __s2); }
#elif defined(__CRT_HAVE_strcasecmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#else /* LIBC: strcasecmp */
#include <local/string/strcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasecmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcasecmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))(__s1, __s2); })
#endif /* strcasecmp... */
#endif /* !__strcasecmp_defined */
#ifndef __strncasecmp_defined
#define __strncasecmp_defined 1
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncasecmp)(char const *__s1, char const *__s2, size_t __maxlen) { return __builtin_strncasecmp(__s1, __s2, __maxlen); }
#elif defined(__CRT_HAVE_strncasecmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, size_t __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, size_t __maxlen),_strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, size_t __maxlen),strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, size_t __maxlen),_strncmpi,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, size_t __maxlen),strncmpi,(__s1,__s2,__maxlen))
#else /* LIBC: strncasecmp */
#include <local/string/strncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncasecmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncasecmp)(char const *__s1, char const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp))(__s1, __s2, __maxlen); })
#endif /* strncasecmp... */
#endif /* !__strncasecmp_defined */
#if __has_builtin(__builtin_ffs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ffs)
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __STDC_INT_AS_SIZE_T __NOTHROW(__LIBCCALL ffs)(int __i) { return __builtin_ffs(__i); }
#elif defined(__CRT_HAVE_ffs)
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST,__STDC_INT_AS_SIZE_T,__NOTHROW,ffs,(int __i),(__i))
#else /* LIBC: ffs */
#include <local/string/ffs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ffs, __FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __STDC_INT_AS_SIZE_T __NOTHROW(__LIBCCALL ffs)(int __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ffs))(__i); })
#endif /* ffs... */
#ifdef __USE_KOS
#include <hybrid/bit.h>
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
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __STDC_INT_AS_SIZE_T __NOTHROW(__LIBCCALL ffsl)(long __i) { return __builtin_ffsl(__i); }
#elif defined(__CRT_HAVE_ffsl)
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST,__STDC_INT_AS_SIZE_T,__NOTHROW,ffsl,(long __i),(__i))
#else /* LIBC: ffsl */
#include <local/string/ffsl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ffsl, __FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __STDC_INT_AS_SIZE_T __NOTHROW(__LIBCCALL ffsl)(long __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ffsl))(__i); })
#endif /* ffsl... */
#if __has_builtin(__builtin_ffsll) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ffsll)
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __STDC_INT_AS_SIZE_T __NOTHROW(__LIBCCALL ffsll)(__LONGLONG __i) { return __builtin_ffsll(__i); }
#elif defined(__CRT_HAVE_ffsll)
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST,__STDC_INT_AS_SIZE_T,__NOTHROW,ffsll,(__LONGLONG __i),(__i))
#else /* LIBC: ffsll */
#include <local/string/ffsll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ffsll, __FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __STDC_INT_AS_SIZE_T __NOTHROW(__LIBCCALL ffsll)(__LONGLONG __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ffsll))(__i); })
#endif /* ffsll... */
#endif /* __USE_GNU */
#if defined(__CRT_HAVE_strlcat)
__CDECLARE(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,strlcat,(char *__restrict __dst, char const *__restrict __src, size_t __bufsize),(__dst,__src,__bufsize))
#else /* LIBC: strlcat */
#include <local/string/strlcat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strlcat, __FORCELOCAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL strlcat)(char *__restrict __dst, char const *__restrict __src, size_t __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlcat))(__dst, __src, __bufsize); })
#endif /* strlcat... */
#if defined(__CRT_HAVE_strlcpy)
__CDECLARE(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,strlcpy,(char *__restrict __dst, char const *__restrict __src, size_t __bufsize),(__dst,__src,__bufsize))
#else /* LIBC: strlcpy */
#include <local/string/strlcpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strlcpy, __FORCELOCAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL strlcpy)(char *__restrict __dst, char const *__restrict __src, size_t __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlcpy))(__dst, __src, __bufsize); })
#endif /* strlcpy... */
#endif /* __USE_MISC */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#if defined(__CRT_HAVE_memccpy)
__CDECLARE(__ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, size_t __num_bytes),(__dst,__src,__needle,__num_bytes))
#elif defined(__CRT_HAVE__memccpy)
__CREDIRECT(__ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, size_t __num_bytes),_memccpy,(__dst,__src,__needle,__num_bytes))
#else /* LIBC: memccpy */
#include <local/string/memccpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memccpy, __FORCELOCAL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL memccpy)(void *__restrict __dst, void const *__restrict __src, int __needle, size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memccpy))(__dst, __src, __needle, __num_bytes); })
#endif /* memccpy... */
#endif /* __USE_MISC || __USE_XOPEN */


#if __has_builtin(__builtin_bzero) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_bzero)
__FORCELOCAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL __bzero)(void *__restrict __dst, size_t __num_bytes) { return __builtin_bzero(__dst, __num_bytes); }
#elif defined(__CRT_HAVE___bzero)
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__bzero,(void *__restrict __dst, size_t __num_bytes),(__dst,__num_bytes))
#elif defined(__CRT_HAVE_bzero)
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__bzero,(void *__restrict __dst, size_t __num_bytes),bzero,(__dst,__num_bytes))
#else /* LIBC: bzero */
#include <local/strings/bzero.h>
__FORCELOCAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL __bzero)(void *__restrict __dst, size_t __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzero))(__dst, __num_bytes); }
#endif /* __bzero... */
#if defined(__CRT_HAVE___strtok_r)
__CDECLARE(__ATTR_NONNULL((2, 3)),char *,__NOTHROW_NCX,__strtok_r,(char *__string, char const *__delim, char **__restrict __save_ptr),(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_strtok_r)
__CREDIRECT(__ATTR_NONNULL((2, 3)),char *,__NOTHROW_NCX,__strtok_r,(char *__string, char const *__delim, char **__restrict __save_ptr),strtok_r,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_strtok_s)
__CREDIRECT(__ATTR_NONNULL((2, 3)),char *,__NOTHROW_NCX,__strtok_r,(char *__string, char const *__delim, char **__restrict __save_ptr),strtok_s,(__string,__delim,__save_ptr))
#else /* LIBC: strtok_r */
#include <local/string/strtok_r.h>
__FORCELOCAL __ATTR_NONNULL((2, 3)) char *__NOTHROW_NCX(__LIBCCALL __strtok_r)(char *__string, char const *__delim, char **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtok_r))(__string, __delim, __save_ptr); }
#endif /* __strtok_r... */

#ifdef __USE_STRING_BWLQ
#if defined(__fast_memcpy_defined)
/* Copy memory between non-overlapping memory blocks. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyb)(void *__restrict __dst, void const *__restrict __src, size_t __n_words) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))(__dst, __src, __n_words); }
#elif defined(__CRT_HAVE_memcpyb)
/* Copy memory between non-overlapping memory blocks. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,memcpyb,(void *__restrict __dst, void const *__restrict __src, size_t __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_memcpy)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,memcpyb,(void *__restrict __dst, void const *__restrict __src, size_t __n_words),memcpy,(__dst,__src,__n_words))
#else /* LIBC: memcpy */
#include <local/string/memcpy.h>
/* Copy memory between non-overlapping memory blocks. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyb)(void *__restrict __dst, void const *__restrict __src, size_t __n_words) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy))(__dst, __src, __n_words); }
#endif /* memcpyb... */
#if defined(__fast_mempcpy_defined)
/* Same as `memcpyb', but return `DST+N_BYTES', rather than `DST' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyb)(void *__restrict __dst, void const *__restrict __src, size_t __n_words) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))(__dst, __src, __n_words); }
#elif defined(__CRT_HAVE_mempcpyb)
/* Same as `memcpyb', but return `DST+N_BYTES', rather than `DST' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempcpyb,(void *__restrict __dst, void const *__restrict __src, size_t __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_mempcpy)
/* Same as `memcpyb', but return `DST+N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempcpyb,(void *__restrict __dst, void const *__restrict __src, size_t __n_words),mempcpy,(__dst,__src,__n_words))
#else /* LIBC: mempcpy */
#include <local/string/mempcpy.h>
/* Same as `memcpyb', but return `DST+N_BYTES', rather than `DST' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyb)(void *__restrict __dst, void const *__restrict __src, size_t __n_words) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpy))(__dst, __src, __n_words); }
#endif /* mempcpyb... */
#if defined(__fast_memcpyw_defined)
/* Copy memory between non-overlapping memory blocks. */
__NAMESPACE_FAST_USING_OR_IMPL(memcpyw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyw)(void *__restrict __dst, void const *__restrict __src, size_t __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyw))(__dst, __src, __n_words); })
#elif defined(__CRT_HAVE_memcpyw)
/* Copy memory between non-overlapping memory blocks. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,memcpyw,(void *__restrict __dst, void const *__restrict __src, size_t __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 2)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,memcpyw,(void *__restrict __dst, void const *__restrict __src, size_t __n_words),wmemcpy,(__dst,__src,__n_words))
#else /* LIBC: memcpyw */
#include <local/string/memcpyw.h>
/* Copy memory between non-overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpyw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyw)(void *__restrict __dst, void const *__restrict __src, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyw))(__dst, __src, __n_words); })
#endif /* memcpyw... */
#if defined(__fast_mempcpyw_defined)
/* Same as `memcpyw', but return `DST+N_WORDS', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempcpyw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyw)(void *__restrict __dst, void const *__restrict __src, size_t __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyw))(__dst, __src, __n_words); })
#elif defined(__CRT_HAVE_mempcpyw)
/* Same as `memcpyw', but return `DST+N_WORDS', rather than `DST' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,mempcpyw,(void *__restrict __dst, void const *__restrict __src, size_t __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `memcpyw', but return `DST+N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,mempcpyw,(void *__restrict __dst, void const *__restrict __src, size_t __n_words),wmempcpy,(__dst,__src,__n_words))
#else /* LIBC: mempcpyw */
#include <local/string/mempcpyw.h>
/* Same as `memcpyw', but return `DST+N_WORDS', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempcpyw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyw)(void *__restrict __dst, void const *__restrict __src, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyw))(__dst, __src, __n_words); })
#endif /* mempcpyw... */
#if defined(__fast_memcpyl_defined)
/* Copy memory between non-overlapping memory blocks. */
__NAMESPACE_FAST_USING_OR_IMPL(memcpyl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyl)(void *__restrict __dst, void const *__restrict __src, size_t __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyl))(__dst, __src, __n_dwords); })
#elif defined(__CRT_HAVE_memcpyl)
/* Copy memory between non-overlapping memory blocks. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,memcpyl,(void *__restrict __dst, void const *__restrict __src, size_t __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 4)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,memcpyl,(void *__restrict __dst, void const *__restrict __src, size_t __n_dwords),wmemcpy,(__dst,__src,__n_dwords))
#else /* LIBC: memcpyl */
#include <local/string/memcpyl.h>
/* Copy memory between non-overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpyl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyl)(void *__restrict __dst, void const *__restrict __src, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyl))(__dst, __src, __n_dwords); })
#endif /* memcpyl... */
#if defined(__fast_mempcpyl_defined)
/* Same as `memcpyl', but return `DST+N_DWORDS', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempcpyl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyl)(void *__restrict __dst, void const *__restrict __src, size_t __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyl))(__dst, __src, __n_dwords); })
#elif defined(__CRT_HAVE_mempcpyl)
/* Same as `memcpyl', but return `DST+N_DWORDS', rather than `DST' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,mempcpyl,(void *__restrict __dst, void const *__restrict __src, size_t __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `memcpyl', but return `DST+N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,mempcpyl,(void *__restrict __dst, void const *__restrict __src, size_t __n_dwords),wmempcpy,(__dst,__src,__n_dwords))
#else /* LIBC: mempcpyl */
#include <local/string/mempcpyl.h>
/* Same as `memcpyl', but return `DST+N_DWORDS', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempcpyl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyl)(void *__restrict __dst, void const *__restrict __src, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyl))(__dst, __src, __n_dwords); })
#endif /* mempcpyl... */
#if defined(__fast_memmove_defined)
/* Move memory between potentially overlapping memory blocks. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveb)(void *__dst, void const *__src, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmove))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_memmoveb)
/* Move memory between potentially overlapping memory blocks. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,memmoveb,(void *__dst, void const *__src, size_t __n_bytes),(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE_memmove)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,memmoveb,(void *__dst, void const *__src, size_t __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* LIBC: memmove */
#include <local/string/memmove.h>
/* Move memory between potentially overlapping memory blocks. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveb)(void *__dst, void const *__src, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmove))(__dst, __src, __n_bytes); }
#endif /* memmoveb... */
#if defined(__fast_mempmove_defined)
/* Same as `memmoveb', but return `DST+N_BYTES', rather than `DST' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveb)(void *__dst, void const *__src, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmove))(__dst, __src, __n_bytes); }
#elif defined(__CRT_HAVE_mempmoveb)
/* Same as `memmoveb', but return `DST+N_BYTES', rather than `DST' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempmoveb,(void *__dst, void const *__src, size_t __n_bytes),(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE_mempmove)
/* Same as `memmoveb', but return `DST+N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempmoveb,(void *__dst, void const *__src, size_t __n_bytes),mempmove,(__dst,__src,__n_bytes))
#else /* LIBC: mempmove */
#include <local/string/mempmove.h>
/* Same as `memmoveb', but return `DST+N_BYTES', rather than `DST' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveb)(void *__dst, void const *__src, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmove))(__dst, __src, __n_bytes); }
#endif /* mempmoveb... */
#if defined(__fast_memmovew_defined)
/* Move memory between potentially overlapping memory blocks. */
__NAMESPACE_FAST_USING_OR_IMPL(memmovew, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovew)(void *__dst, void const *__src, size_t __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovew))(__dst, __src, __n_words); })
#elif defined(__CRT_HAVE_memmovew)
/* Move memory between potentially overlapping memory blocks. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,memmovew,(void *__dst, void const *__src, size_t __n_words),(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 2)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,memmovew,(void *__dst, void const *__src, size_t __n_words),wmemmove,(__dst,__src,__n_words))
#else /* LIBC: memmovew */
#include <local/string/memmovew.h>
/* Move memory between potentially overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmovew, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovew)(void *__dst, void const *__src, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovew))(__dst, __src, __n_words); })
#endif /* memmovew... */
#if defined(__fast_mempmovew_defined)
/* Same as `memmovew', but return `DST+N_WORDS', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempmovew, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovew)(void *__restrict __dst, void const *__restrict __src, size_t __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovew))(__dst, __src, __n_words); })
#elif defined(__CRT_HAVE_mempmovew)
/* Same as `memmovew', but return `DST+N_WORDS', rather than `DST' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,mempmovew,(void *__restrict __dst, void const *__restrict __src, size_t __n_words),(__dst,__src,__n_words))
#else /* LIBC: mempmovew */
#include <local/string/mempmovew.h>
/* Same as `memmovew', but return `DST+N_WORDS', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmovew, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovew)(void *__restrict __dst, void const *__restrict __src, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovew))(__dst, __src, __n_words); })
#endif /* mempmovew... */
#if defined(__fast_memmovel_defined)
/* Move memory between potentially overlapping memory blocks. */
__NAMESPACE_FAST_USING_OR_IMPL(memmovel, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovel)(void *__dst, void const *__src, size_t __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovel))(__dst, __src, __n_dwords); })
#elif defined(__CRT_HAVE_memmovel)
/* Move memory between potentially overlapping memory blocks. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,memmovel,(void *__dst, void const *__src, size_t __n_dwords),(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 4)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,memmovel,(void *__dst, void const *__src, size_t __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#else /* LIBC: memmovel */
#include <local/string/memmovel.h>
/* Move memory between potentially overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmovel, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmovel)(void *__dst, void const *__src, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovel))(__dst, __src, __n_dwords); })
#endif /* memmovel... */
#if defined(__fast_mempmovel_defined)
/* Same as `memmovew', but return `DST+N_DWORDS', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempmovel, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovel)(void *__restrict __dst, void const *__restrict __src, size_t __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovel))(__dst, __src, __n_dwords); })
#elif defined(__CRT_HAVE_mempmovel)
/* Same as `memmovew', but return `DST+N_DWORDS', rather than `DST' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,mempmovel,(void *__restrict __dst, void const *__restrict __src, size_t __n_dwords),(__dst,__src,__n_dwords))
#else /* LIBC: mempmovel */
#include <local/string/mempmovel.h>
/* Same as `memmovew', but return `DST+N_DWORDS', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmovel, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmovel)(void *__restrict __dst, void const *__restrict __src, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovel))(__dst, __src, __n_dwords); })
#endif /* mempmovel... */
#if defined(__fast_memset_defined)
/* Fill memory with a given byte */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetb)(void *__restrict __dst, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))(__dst, __byte, __n_bytes); }
#elif defined(__CRT_HAVE_memsetb)
/* Fill memory with a given byte */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memsetb,(void *__restrict __dst, int __byte, size_t __n_bytes),(__dst,__byte,__n_bytes))
#elif defined(__CRT_HAVE_memset)
/* Fill memory with a given byte */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memsetb,(void *__restrict __dst, int __byte, size_t __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* LIBC: memset */
#include <local/string/memset.h>
/* Fill memory with a given byte */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetb)(void *__restrict __dst, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memset))(__dst, __byte, __n_bytes); }
#endif /* memsetb... */
#if defined(__fast_mempset_defined)
/* Same as `memsetb', but return `DST+N_BYTES', rather than `DST' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetb)(void *__restrict __dst, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempset))(__dst, __byte, __n_bytes); }
#elif defined(__CRT_HAVE_mempsetb)
/* Same as `memsetb', but return `DST+N_BYTES', rather than `DST' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempsetb,(void *__restrict __dst, int __byte, size_t __n_bytes),(__dst,__byte,__n_bytes))
#elif defined(__CRT_HAVE_mempset)
/* Same as `memsetb', but return `DST+N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,mempsetb,(void *__restrict __dst, int __byte, size_t __n_bytes),mempset,(__dst,__byte,__n_bytes))
#else /* LIBC: mempset */
#include <local/string/mempset.h>
/* Same as `memsetb', but return `DST+N_BYTES', rather than `DST' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetb)(void *__restrict __dst, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempset))(__dst, __byte, __n_bytes); }
#endif /* mempsetb... */
#if defined(__fast_memsetw_defined)
/* Fill memory with a given word */
__NAMESPACE_FAST_USING_OR_IMPL(memsetw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetw)(void *__restrict __dst, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetw))(__dst, __word, __n_words); })
#elif defined(__CRT_HAVE_memsetw)
/* Fill memory with a given word */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, size_t __n_words),(__dst,__word,__n_words))
#else /* LIBC: memsetw */
#include <local/string/memsetw.h>
/* Fill memory with a given word */
__NAMESPACE_LOCAL_USING_OR_IMPL(memsetw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetw)(void *__restrict __dst, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetw))(__dst, __word, __n_words); })
#endif /* memsetw... */
#if defined(__fast_mempsetw_defined)
/* Same as `memsetw', but return `DST+N_WORDS', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempsetw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetw)(void *__restrict __dst, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetw))(__dst, __word, __n_words); })
#elif defined(__CRT_HAVE_mempsetw)
/* Same as `memsetw', but return `DST+N_WORDS', rather than `DST' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, size_t __n_words),(__dst,__word,__n_words))
#else /* LIBC: mempsetw */
#include <local/string/mempsetw.h>
/* Same as `memsetw', but return `DST+N_WORDS', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempsetw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetw)(void *__restrict __dst, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetw))(__dst, __word, __n_words); })
#endif /* mempsetw... */
#if defined(__fast_memsetl_defined)
/* Fill memory with a given dword */
__NAMESPACE_FAST_USING_OR_IMPL(memsetl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetl)(void *__restrict __dst, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetl))(__dst, __dword, __n_dwords); })
#elif defined(__CRT_HAVE_memsetl)
/* Fill memory with a given dword */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, size_t __n_dwords),(__dst,__dword,__n_dwords))
#else /* LIBC: memsetl */
#include <local/string/memsetl.h>
/* Fill memory with a given dword */
__NAMESPACE_LOCAL_USING_OR_IMPL(memsetl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetl)(void *__restrict __dst, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetl))(__dst, __dword, __n_dwords); })
#endif /* memsetl... */
#if defined(__fast_mempsetl_defined)
/* Same as `memsetl', but return `DST+N_DWORDS', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempsetl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetl)(void *__restrict __dst, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetl))(__dst, __dword, __n_dwords); })
#elif defined(__CRT_HAVE_mempsetl)
/* Same as `memsetl', but return `DST+N_DWORDS', rather than `DST' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, size_t __n_dwords),(__dst,__dword,__n_dwords))
#else /* LIBC: mempsetl */
#include <local/string/mempsetl.h>
/* Same as `memsetl', but return `DST+N_DWORDS', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempsetl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetl)(void *__restrict __dst, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetl))(__dst, __dword, __n_dwords); })
#endif /* mempsetl... */
#if defined(__fast_memcmp_defined)
/* Compare memory buffers and return the difference of the first non-matching byte */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memcmpb)(void const *__s1, void const *__s2, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __n_bytes); }
#elif defined(__CRT_HAVE_memcmpb)
/* Compare memory buffers and return the difference of the first non-matching byte */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcmpb,(void const *__s1, void const *__s2, size_t __n_bytes),(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_memcmp)
/* Compare memory buffers and return the difference of the first non-matching byte */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcmpb,(void const *__s1, void const *__s2, size_t __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_bcmp)
/* Compare memory buffers and return the difference of the first non-matching byte */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcmpb,(void const *__s1, void const *__s2, size_t __n_bytes),bcmp,(__s1,__s2,__n_bytes))
#else /* LIBC: memcmp */
#include <local/string/memcmp.h>
/* Compare memory buffers and return the difference of the first non-matching byte */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memcmpb)(void const *__s1, void const *__s2, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp))(__s1, __s2, __n_bytes); }
#endif /* memcmpb... */
#if defined(__fast_memcmpw_defined)
/* Compare memory buffers and return the difference of the first non-matching word */
__NAMESPACE_FAST_USING_OR_IMPL(memcmpw, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) __INT16_TYPE__ __NOTHROW_NCX(__LIBCCALL memcmpw)(void const *__s1, void const *__s2, size_t __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpw))(__s1, __s2, __n_words); })
#elif defined(__CRT_HAVE_memcmpw)
/* Compare memory buffers and return the difference of the first non-matching word */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),__INT16_TYPE__,__NOTHROW_NCX,memcmpw,(void const *__s1, void const *__s2, size_t __n_words),(__s1,__s2,__n_words))
#elif defined(__CRT_HAVE_wmemcmp) && (__SIZEOF_WCHAR_T__ == 2)
/* Compare memory buffers and return the difference of the first non-matching word */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),__INT16_TYPE__,__NOTHROW_NCX,memcmpw,(void const *__s1, void const *__s2, size_t __n_words),wmemcmp,(__s1,__s2,__n_words))
#else /* LIBC: memcmpw */
#include <local/string/memcmpw.h>
/* Compare memory buffers and return the difference of the first non-matching word */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcmpw, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) __INT16_TYPE__ __NOTHROW_NCX(__LIBCCALL memcmpw)(void const *__s1, void const *__s2, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpw))(__s1, __s2, __n_words); })
#endif /* memcmpw... */
#if defined(__fast_memcmpl_defined)
/* Compare memory buffers and return the difference of the first non-matching dword */
__NAMESPACE_FAST_USING_OR_IMPL(memcmpl, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) __INT32_TYPE__ __NOTHROW_NCX(__LIBCCALL memcmpl)(void const *__s1, void const *__s2, size_t __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpl))(__s1, __s2, __n_dwords); })
#elif defined(__CRT_HAVE_memcmpl)
/* Compare memory buffers and return the difference of the first non-matching dword */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),__INT32_TYPE__,__NOTHROW_NCX,memcmpl,(void const *__s1, void const *__s2, size_t __n_dwords),(__s1,__s2,__n_dwords))
#elif defined(__CRT_HAVE_wmemcmp) && (__SIZEOF_WCHAR_T__ == 4)
/* Compare memory buffers and return the difference of the first non-matching dword */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),__INT32_TYPE__,__NOTHROW_NCX,memcmpl,(void const *__s1, void const *__s2, size_t __n_dwords),wmemcmp,(__s1,__s2,__n_dwords))
#else /* LIBC: memcmpl */
#include <local/string/memcmpl.h>
/* Compare memory buffers and return the difference of the first non-matching dword */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcmpl, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) __INT32_TYPE__ __NOTHROW_NCX(__LIBCCALL memcmpl)(void const *__s1, void const *__s2, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpl))(__s1, __s2, __n_dwords); })
#endif /* memcmpl... */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __fast_memchr_defined
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrb)(void *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __byte, __n_bytes); }
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __byte, __n_bytes); }
}
#elif defined(__CRT_HAVE_memchrb)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memchrb,(void *__restrict __haystack, int __byte, size_t __n_bytes),memchrb,(__haystack, __byte, __n_bytes))
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memchrb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memchrb,(__haystack, __byte, __n_bytes))
}
#elif defined(__CRT_HAVE_memchr)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memchrb,(void *__restrict __haystack, int __byte, size_t __n_bytes),memchr,(__haystack, __byte, __n_bytes))
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memchrb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memchr,(__haystack, __byte, __n_bytes))
}
#else /* LIBC: memchr */
#include <local/string/memchr.h>
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrb)(void *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))(__haystack, __byte, __n_bytes); }
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))(__haystack, __byte, __n_bytes); }
}
#endif /* memchrb... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memchr_defined)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))(__haystack, __byte, __n_bytes); }
#elif defined(__CRT_HAVE_memchrb)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memchrb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),(__haystack,__byte,__n_bytes))
#elif defined(__CRT_HAVE_memchr)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memchrb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memchr,(__haystack,__byte,__n_bytes))
#else /* LIBC: memchr */
#include <local/string/memchr.h>
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))(__haystack, __byte, __n_bytes); }
#endif /* memchrb... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __fast_memchrw_defined
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(__haystack, __word, __n_words); }
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(__haystack, __word, __n_words); }
}
#elif defined(__CRT_HAVE_memchrw)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),memchrw,(__haystack, __word, __n_words))
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),memchrw,(__haystack, __word, __n_words))
}
#elif defined(__CRT_HAVE_wmemchr) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),wmemchr,(__haystack, __word, __n_words))
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),wmemchr,(__haystack, __word, __n_words))
}
#else /* LIBC: memchrw */
#include <local/string/memchrw.h>
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrw))(__haystack, __word, __n_words); }
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrw))(__haystack, __word, __n_words); }
}
#endif /* memchrw... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memchrw_defined)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_FAST_USING_OR_IMPL(memchrw, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))(__haystack, __word, __n_words); })
#elif defined(__CRT_HAVE_memchrw)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),(__haystack,__word,__n_words))
#elif defined(__CRT_HAVE_wmemchr) && (__SIZEOF_WCHAR_T__ == 2)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),wmemchr,(__haystack,__word,__n_words))
#else /* LIBC: memchrw */
#include <local/string/memchrw.h>
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memchrw, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrw))(__haystack, __word, __n_words); })
#endif /* memchrw... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __fast_memchrl_defined
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(__haystack, __dword, __n_dwords); }
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(__haystack, __dword, __n_dwords); }
}
#elif defined(__CRT_HAVE_memchrl)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),memchrl,(__haystack, __dword, __n_dwords))
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),memchrl,(__haystack, __dword, __n_dwords))
}
#elif defined(__CRT_HAVE_wmemchr) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),wmemchr,(__haystack, __dword, __n_dwords))
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),wmemchr,(__haystack, __dword, __n_dwords))
}
#else /* LIBC: memchrl */
#include <local/string/memchrl.h>
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrl))(__haystack, __dword, __n_dwords); }
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrl))(__haystack, __dword, __n_dwords); }
}
#endif /* memchrl... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memchrl_defined)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_FAST_USING_OR_IMPL(memchrl, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))(__haystack, __dword, __n_dwords); })
#elif defined(__CRT_HAVE_memchrl)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),(__haystack,__dword,__n_dwords))
#elif defined(__CRT_HAVE_wmemchr) && (__SIZEOF_WCHAR_T__ == 4)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),wmemchr,(__haystack,__dword,__n_dwords))
#else /* LIBC: memchrl */
#include <local/string/memchrl.h>
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memchrl, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrl))(__haystack, __dword, __n_dwords); })
#endif /* memchrl... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memrchrb)
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrchrb,(void *__restrict __haystack, int __byte, size_t __n_bytes),memrchrb,(__haystack, __byte, __n_bytes))
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memrchrb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memrchrb,(__haystack, __byte, __n_bytes))
}
#elif defined(__CRT_HAVE_memrchr)
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrchrb,(void *__restrict __haystack, int __byte, size_t __n_bytes),memrchr,(__haystack, __byte, __n_bytes))
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memrchrb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memrchr,(__haystack, __byte, __n_bytes))
}
#else /* LIBC: memrchr */
#include <local/string/memrchr.h>
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrb)(void *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))(__haystack, __byte, __n_bytes); }
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))(__haystack, __byte, __n_bytes); }
}
#endif /* memrchrb... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memrchrb)
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrchrb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),(__haystack,__byte,__n_bytes))
#elif defined(__CRT_HAVE_memrchr)
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrchrb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memrchr,(__haystack,__byte,__n_bytes))
#else /* LIBC: memrchr */
#include <local/string/memrchr.h>
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))(__haystack, __byte, __n_bytes); }
#endif /* memrchrb... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __fast_memrchrw_defined
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_WORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrw))(__haystack, __word, __n_words); }
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_WORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrw))(__haystack, __word, __n_words); }
}
#elif defined(__CRT_HAVE_memrchrw)
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_WORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memrchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),memrchrw,(__haystack, __word, __n_words))
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_WORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,memrchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),memrchrw,(__haystack, __word, __n_words))
}
#else /* LIBC: memrchrw */
#include <local/string/memrchrw.h>
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_WORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrw))(__haystack, __word, __n_words); }
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_WORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrw))(__haystack, __word, __n_words); }
}
#endif /* memrchrw... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memrchrw_defined)
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_WORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_FAST_USING_OR_IMPL(memrchrw, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrw))(__haystack, __word, __n_words); })
#elif defined(__CRT_HAVE_memrchrw)
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_WORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memrchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),(__haystack,__word,__n_words))
#else /* LIBC: memrchrw */
#include <local/string/memrchrw.h>
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_WORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrchrw, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrw))(__haystack, __word, __n_words); })
#endif /* memrchrw... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __fast_memrchrl_defined
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_DWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrl))(__haystack, __dword, __n_dwords); }
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_DWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrl))(__haystack, __dword, __n_dwords); }
}
#elif defined(__CRT_HAVE_memrchrl)
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_DWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memrchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),memrchrl,(__haystack, __dword, __n_dwords))
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_DWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,memrchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),memrchrl,(__haystack, __dword, __n_dwords))
}
#else /* LIBC: memrchrl */
#include <local/string/memrchrl.h>
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_DWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrl))(__haystack, __dword, __n_dwords); }
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_DWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrl))(__haystack, __dword, __n_dwords); }
}
#endif /* memrchrl... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memrchrl_defined)
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_DWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_FAST_USING_OR_IMPL(memrchrl, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrl))(__haystack, __dword, __n_dwords); })
#elif defined(__CRT_HAVE_memrchrl)
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_DWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memrchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),(__haystack,__dword,__n_dwords))
#else /* LIBC: memrchrl */
#include <local/string/memrchrl.h>
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_DWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrchrl, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrl))(__haystack, __dword, __n_dwords); })
#endif /* memrchrl... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemchrb)
extern "C++" {
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemchrb,(void *__restrict __haystack, int __byte),rawmemchrb,(__haystack, __byte))
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,rawmemchrb,(void const *__restrict __haystack, int __byte),rawmemchrb,(__haystack, __byte))
}
#elif defined(__CRT_HAVE_rawmemchr)
extern "C++" {
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemchrb,(void *__restrict __haystack, int __byte),rawmemchr,(__haystack, __byte))
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,rawmemchrb,(void const *__restrict __haystack, int __byte),rawmemchr,(__haystack, __byte))
}
#else /* LIBC: rawmemchr */
#include <local/string/rawmemchr.h>
extern "C++" {
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrb)(void *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchr))(__haystack, __byte); }
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemchrb)(void const *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchr))(__haystack, __byte); }
}
#endif /* rawmemchrb... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemchrb)
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemchrb,(void const *__restrict __haystack, int __byte),(__haystack,__byte))
#elif defined(__CRT_HAVE_rawmemchr)
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemchrb,(void const *__restrict __haystack, int __byte),rawmemchr,(__haystack,__byte))
#else /* LIBC: rawmemchr */
#include <local/string/rawmemchr.h>
/* Same as `memchrb' with a search limit of `(size_t)-1' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrb)(void const *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchr))(__haystack, __byte); }
#endif /* rawmemchrb... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemchrw)
extern "C++" {
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word),rawmemchrw,(__haystack, __word))
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,rawmemchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),rawmemchrw,(__haystack, __word))
}
#else /* LIBC: rawmemchrw */
#include <local/string/rawmemchrw.h>
extern "C++" {
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrw))(__haystack, __word); }
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrw))(__haystack, __word); }
}
#endif /* rawmemchrw... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemchrw)
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),(__haystack,__word))
#else /* LIBC: rawmemchrw */
#include <local/string/rawmemchrw.h>
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemchrw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrw))(__haystack, __word); })
#endif /* rawmemchrw... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemchrl)
extern "C++" {
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword),rawmemchrl,(__haystack, __dword))
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,rawmemchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),rawmemchrl,(__haystack, __dword))
}
#else /* LIBC: rawmemchrl */
#include <local/string/rawmemchrl.h>
extern "C++" {
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrl))(__haystack, __dword); }
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrl))(__haystack, __dword); }
}
#endif /* rawmemchrl... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemchrl)
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),(__haystack,__dword))
#else /* LIBC: rawmemchrl */
#include <local/string/rawmemchrl.h>
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemchrl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrl))(__haystack, __dword); })
#endif /* rawmemchrl... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemrchrb)
extern "C++" {
/* Same as `memrchrb' without a search limit, starting at `HAYSTACK-1' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemrchrb,(void *__restrict __haystack, int __byte),rawmemrchrb,(__haystack, __byte))
/* Same as `memrchrb' without a search limit, starting at `HAYSTACK-1' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,rawmemrchrb,(void const *__restrict __haystack, int __byte),rawmemrchrb,(__haystack, __byte))
}
#elif defined(__CRT_HAVE_rawmemrchr)
extern "C++" {
/* Same as `memrchrb' without a search limit, starting at `HAYSTACK-1' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemrchrb,(void *__restrict __haystack, int __byte),rawmemrchr,(__haystack, __byte))
/* Same as `memrchrb' without a search limit, starting at `HAYSTACK-1' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,rawmemrchrb,(void const *__restrict __haystack, int __byte),rawmemrchr,(__haystack, __byte))
}
#else /* LIBC: rawmemrchr */
#include <local/string/rawmemrchr.h>
extern "C++" {
/* Same as `memrchrb' without a search limit, starting at `HAYSTACK-1' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrb)(void *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchr))(__haystack, __byte); }
/* Same as `memrchrb' without a search limit, starting at `HAYSTACK-1' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrchrb)(void const *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchr))(__haystack, __byte); }
}
#endif /* rawmemrchrb... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemrchrb)
/* Same as `memrchrb' without a search limit, starting at `HAYSTACK-1' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemrchrb,(void const *__restrict __haystack, int __byte),(__haystack,__byte))
#elif defined(__CRT_HAVE_rawmemrchr)
/* Same as `memrchrb' without a search limit, starting at `HAYSTACK-1' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemrchrb,(void const *__restrict __haystack, int __byte),rawmemrchr,(__haystack,__byte))
#else /* LIBC: rawmemrchr */
#include <local/string/rawmemrchr.h>
/* Same as `memrchrb' without a search limit, starting at `HAYSTACK-1' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrb)(void const *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchr))(__haystack, __byte); }
#endif /* rawmemrchrb... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemrchrw)
extern "C++" {
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK-2' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemrchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word),rawmemrchrw,(__haystack, __word))
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK-2' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,rawmemrchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),rawmemrchrw,(__haystack, __word))
}
#else /* LIBC: rawmemrchrw */
#include <local/string/rawmemrchrw.h>
extern "C++" {
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK-2' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrw))(__haystack, __word); }
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK-2' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrw))(__haystack, __word); }
}
#endif /* rawmemrchrw... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemrchrw)
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK-2' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemrchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),(__haystack,__word))
#else /* LIBC: rawmemrchrw */
#include <local/string/rawmemrchrw.h>
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK-2' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrchrw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrw))(__haystack, __word); })
#endif /* rawmemrchrw... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemrchrl)
extern "C++" {
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK-4' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemrchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword),rawmemrchrl,(__haystack, __dword))
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK-4' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,rawmemrchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),rawmemrchrl,(__haystack, __dword))
}
#else /* LIBC: rawmemrchrl */
#include <local/string/rawmemrchrl.h>
extern "C++" {
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK-4' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrl))(__haystack, __dword); }
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK-4' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrl))(__haystack, __dword); }
}
#endif /* rawmemrchrl... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemrchrl)
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK-4' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemrchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),(__haystack,__dword))
#else /* LIBC: rawmemrchrl */
#include <local/string/rawmemrchrl.h>
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK-4' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrchrl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrl))(__haystack, __dword); })
#endif /* rawmemrchrl... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __fast_memend_defined
extern "C++" {
/* Same as `memchrb', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendb)(void *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __byte, __n_bytes); }
/* Same as `memchrb', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __byte, __n_bytes); }
}
#elif defined(__CRT_HAVE_memendb)
extern "C++" {
/* Same as `memchrb', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memendb,(void *__restrict __haystack, int __byte, size_t __n_bytes),memendb,(__haystack, __byte, __n_bytes))
/* Same as `memchrb', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memendb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memendb,(__haystack, __byte, __n_bytes))
}
#elif defined(__CRT_HAVE_memend)
extern "C++" {
/* Same as `memchrb', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memendb,(void *__restrict __haystack, int __byte, size_t __n_bytes),memend,(__haystack, __byte, __n_bytes))
/* Same as `memchrb', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memendb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memend,(__haystack, __byte, __n_bytes))
}
#else /* LIBC: memend */
#include <local/string/memend.h>
extern "C++" {
/* Same as `memchrb', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendb)(void *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))(__haystack, __byte, __n_bytes); }
/* Same as `memchrb', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))(__haystack, __byte, __n_bytes); }
}
#endif /* memendb... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memend_defined)
/* Same as `memchrb', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __byte, __n_bytes); }
#elif defined(__CRT_HAVE_memendb)
/* Same as `memchrb', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memendb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),(__haystack,__byte,__n_bytes))
#elif defined(__CRT_HAVE_memend)
/* Same as `memchrb', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memendb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memend,(__haystack,__byte,__n_bytes))
#else /* LIBC: memend */
#include <local/string/memend.h>
/* Same as `memchrb', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))(__haystack, __byte, __n_bytes); }
#endif /* memendb... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __fast_memendw_defined
extern "C++" {
/* Same as `memchrw', but return `HAYSTACK+N_WORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendw)(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendw))(__haystack, __word, __n_bytes); }
/* Same as `memchrw', but return `HAYSTACK+N_WORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendw))(__haystack, __word, __n_bytes); }
}
#elif defined(__CRT_HAVE_memendw)
extern "C++" {
/* Same as `memchrw', but return `HAYSTACK+N_WORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memendw,(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_bytes),memendw,(__haystack, __word, __n_bytes))
/* Same as `memchrw', but return `HAYSTACK+N_WORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,memendw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_bytes),memendw,(__haystack, __word, __n_bytes))
}
#else /* LIBC: memendw */
#include <local/string/memendw.h>
extern "C++" {
/* Same as `memchrw', but return `HAYSTACK+N_WORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendw)(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendw))(__haystack, __word, __n_bytes); }
/* Same as `memchrw', but return `HAYSTACK+N_WORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendw))(__haystack, __word, __n_bytes); }
}
#endif /* memendw... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memendw_defined)
/* Same as `memchrw', but return `HAYSTACK+N_WORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_FAST_USING_OR_IMPL(memendw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendw))(__haystack, __word, __n_bytes); })
#elif defined(__CRT_HAVE_memendw)
/* Same as `memchrw', but return `HAYSTACK+N_WORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memendw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_bytes),(__haystack,__word,__n_bytes))
#else /* LIBC: memendw */
#include <local/string/memendw.h>
/* Same as `memchrw', but return `HAYSTACK+N_WORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memendw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendw))(__haystack, __word, __n_bytes); })
#endif /* memendw... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __fast_memendl_defined
extern "C++" {
/* Same as `memchrl', but return `HAYSTACK+N_DWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendl))(__haystack, __dword, __n_bytes); }
/* Same as `memchrl', but return `HAYSTACK+N_DWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendl))(__haystack, __dword, __n_bytes); }
}
#elif defined(__CRT_HAVE_memendl)
extern "C++" {
/* Same as `memchrl', but return `HAYSTACK+N_DWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memendl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_bytes),memendl,(__haystack, __dword, __n_bytes))
/* Same as `memchrl', but return `HAYSTACK+N_DWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,memendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_bytes),memendl,(__haystack, __dword, __n_bytes))
}
#else /* LIBC: memendl */
#include <local/string/memendl.h>
extern "C++" {
/* Same as `memchrl', but return `HAYSTACK+N_DWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendl))(__haystack, __dword, __n_bytes); }
/* Same as `memchrl', but return `HAYSTACK+N_DWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendl))(__haystack, __dword, __n_bytes); }
}
#endif /* memendl... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memendl_defined)
/* Same as `memchrl', but return `HAYSTACK+N_DWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_FAST_USING_OR_IMPL(memendl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendl))(__haystack, __dword, __n_bytes); })
#elif defined(__CRT_HAVE_memendl)
/* Same as `memchrl', but return `HAYSTACK+N_DWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_bytes),(__haystack,__dword,__n_bytes))
#else /* LIBC: memendl */
#include <local/string/memendl.h>
/* Same as `memchrl', but return `HAYSTACK+N_DWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memendl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendl))(__haystack, __dword, __n_bytes); })
#endif /* memendl... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __fast_memrend_defined
extern "C++" {
/* Same as `memrchrb', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendb)(void *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __byte, __n_bytes); }
/* Same as `memrchrb', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __byte, __n_bytes); }
}
#elif defined(__CRT_HAVE_memrendb)
extern "C++" {
/* Same as `memrchrb', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrendb,(void *__restrict __haystack, int __byte, size_t __n_bytes),memrendb,(__haystack, __byte, __n_bytes))
/* Same as `memrchrb', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memrendb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memrendb,(__haystack, __byte, __n_bytes))
}
#elif defined(__CRT_HAVE_memrend)
extern "C++" {
/* Same as `memrchrb', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrendb,(void *__restrict __haystack, int __byte, size_t __n_bytes),memrend,(__haystack, __byte, __n_bytes))
/* Same as `memrchrb', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memrendb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memrend,(__haystack, __byte, __n_bytes))
}
#else /* LIBC: memrend */
#include <local/string/memrend.h>
extern "C++" {
/* Same as `memrchrb', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendb)(void *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))(__haystack, __byte, __n_bytes); }
/* Same as `memrchrb', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))(__haystack, __byte, __n_bytes); }
}
#endif /* memrendb... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memrend_defined)
/* Same as `memrchrb', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __byte, __n_bytes); }
#elif defined(__CRT_HAVE_memrendb)
/* Same as `memrchrb', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrendb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),(__haystack,__byte,__n_bytes))
#elif defined(__CRT_HAVE_memrend)
/* Same as `memrchrb', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrendb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memrend,(__haystack,__byte,__n_bytes))
#else /* LIBC: memrend */
#include <local/string/memrend.h>
/* Same as `memrchrb', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))(__haystack, __byte, __n_bytes); }
#endif /* memrendb... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __fast_memrendw_defined
extern "C++" {
/* Same as `memrchrw', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendw)(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendw))(__haystack, __word, __n_words); }
/* Same as `memrchrw', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendw))(__haystack, __word, __n_words); }
}
#elif defined(__CRT_HAVE_memrendw)
extern "C++" {
/* Same as `memrchrw', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memrendw,(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),memrendw,(__haystack, __word, __n_words))
/* Same as `memrchrw', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,memrendw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),memrendw,(__haystack, __word, __n_words))
}
#else /* LIBC: memrendw */
#include <local/string/memrendw.h>
extern "C++" {
/* Same as `memrchrw', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendw)(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendw))(__haystack, __word, __n_words); }
/* Same as `memrchrw', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendw))(__haystack, __word, __n_words); }
}
#endif /* memrendw... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memrendw_defined)
/* Same as `memrchrw', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_FAST_USING_OR_IMPL(memrendw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendw))(__haystack, __word, __n_words); })
#elif defined(__CRT_HAVE_memrendw)
/* Same as `memrchrw', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memrendw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),(__haystack,__word,__n_words))
#else /* LIBC: memrendw */
#include <local/string/memrendw.h>
/* Same as `memrchrw', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrendw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendw))(__haystack, __word, __n_words); })
#endif /* memrendw... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __fast_memrendl_defined
extern "C++" {
/* Same as `memrchrl', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendl))(__haystack, __dword, __n_dwords); }
/* Same as `memrchrl', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendl))(__haystack, __dword, __n_dwords); }
}
#elif defined(__CRT_HAVE_memrendl)
extern "C++" {
/* Same as `memrchrl', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memrendl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),memrendl,(__haystack, __dword, __n_dwords))
/* Same as `memrchrl', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,memrendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),memrendl,(__haystack, __dword, __n_dwords))
}
#else /* LIBC: memrendl */
#include <local/string/memrendl.h>
extern "C++" {
/* Same as `memrchrl', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendl))(__haystack, __dword, __n_dwords); }
/* Same as `memrchrl', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendl))(__haystack, __dword, __n_dwords); }
}
#endif /* memrendl... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memrendl_defined)
/* Same as `memrchrl', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_FAST_USING_OR_IMPL(memrendl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendl))(__haystack, __dword, __n_dwords); })
#elif defined(__CRT_HAVE_memrendl)
/* Same as `memrchrl', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memrendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),(__haystack,__dword,__n_dwords))
#else /* LIBC: memrendl */
#include <local/string/memrendl.h>
/* Same as `memrchrl', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrendl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendl))(__haystack, __dword, __n_dwords); })
#endif /* memrendl... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memlen_defined)
/* Same as `memendb', but return the offset from `HAYSTACK', rather than the actual address. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memlenb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memlen))(__haystack, __byte, __n_bytes); }
#elif defined(__CRT_HAVE_memlenb)
/* Same as `memendb', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memlenb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),(__haystack,__byte,__n_bytes))
#elif defined(__CRT_HAVE_memlen)
/* Same as `memendb', but return the offset from `HAYSTACK', rather than the actual address. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memlenb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memlen,(__haystack,__byte,__n_bytes))
#else /* LIBC: memlen */
#include <local/string/memlen.h>
/* Same as `memendb', but return the offset from `HAYSTACK', rather than the actual address. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memlenb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlen))(__haystack, __byte, __n_bytes); }
#endif /* memlenb... */
#if defined(__CRT_HAVE_memlenw)
/* Same as `memendw', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),(__haystack,__word,__n_words))
#else /* LIBC: memlenw */
#include <local/string/memlenw.h>
/* Same as `memendw', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memlenw, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlenw))(__haystack, __word, __n_words); })
#endif /* memlenw... */
#if defined(__CRT_HAVE_memlenl)
/* Same as `memendl', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),(__haystack,__dword,__n_dwords))
#else /* LIBC: memlenl */
#include <local/string/memlenl.h>
/* Same as `memendl', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memlenl, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlenl))(__haystack, __dword, __n_dwords); })
#endif /* memlenl... */
#if defined(__fast_memrlen_defined)
/* Same as `memrendb', but return the offset from `HAYSTACK', rather than the actual address. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memrlenb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrlen))(__haystack, __byte, __n_bytes); }
#elif defined(__CRT_HAVE_memrlenb)
/* Same as `memrendb', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memrlenb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),(__haystack,__byte,__n_bytes))
#elif defined(__CRT_HAVE_memrlen)
/* Same as `memrendb', but return the offset from `HAYSTACK', rather than the actual address. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memrlenb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memrlen,(__haystack,__byte,__n_bytes))
#else /* LIBC: memrlen */
#include <local/string/memrlen.h>
/* Same as `memrendb', but return the offset from `HAYSTACK', rather than the actual address. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memrlenb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlen))(__haystack, __byte, __n_bytes); }
#endif /* memrlenb... */
#if defined(__CRT_HAVE_memrlenw)
/* Same as `memrendw', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memrlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),(__haystack,__word,__n_words))
#else /* LIBC: memrlenw */
#include <local/string/memrlenw.h>
/* Same as `memrendw', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrlenw, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memrlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlenw))(__haystack, __word, __n_words); })
#endif /* memrlenw... */
#if defined(__CRT_HAVE_memrlenl)
/* Same as `memrendl', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memrlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),(__haystack,__dword,__n_dwords))
#else /* LIBC: memrlenl */
#include <local/string/memrlenl.h>
/* Same as `memrendl', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrlenl, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memrlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlenl))(__haystack, __dword, __n_dwords); })
#endif /* memrlenl... */
#if defined(__CRT_HAVE_rawmemlenb)
/* Same as `rawmemchrb', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemlenb,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#elif defined(__CRT_HAVE_rawmemlen)
/* Same as `rawmemchrb', but return the offset from `HAYSTACK', rather than the actual address. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemlenb,(void const *__restrict __haystack, int __needle),rawmemlen,(__haystack,__needle))
#else /* LIBC: rawmemlen */
#include <local/string/rawmemlen.h>
/* Same as `rawmemchrb', but return the offset from `HAYSTACK', rather than the actual address. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemlenb)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemlen))(__haystack, __needle); }
#endif /* rawmemlenb... */
#if defined(__CRT_HAVE_rawmemlenw)
/* Same as `rawmemchrw', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),(__haystack,__word))
#else /* LIBC: rawmemlenw */
#include <local/string/rawmemlenw.h>
/* Same as `rawmemchrw', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemlenw, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemlenw))(__haystack, __word); })
#endif /* rawmemlenw... */
#if defined(__CRT_HAVE_rawmemlenl)
/* Same as `rawmemchrl', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),(__haystack,__dword))
#else /* LIBC: rawmemlenl */
#include <local/string/rawmemlenl.h>
/* Same as `rawmemchrl', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemlenl, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemlenl))(__haystack, __dword); })
#endif /* rawmemlenl... */
#if defined(__CRT_HAVE_rawmemrlenb)
/* Same as `rawmemrchrb', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemrlenb,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#elif defined(__CRT_HAVE_rawmemrlen)
/* Same as `rawmemrchrb', but return the offset from `HAYSTACK', rather than the actual address. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemrlenb,(void const *__restrict __haystack, int __needle),rawmemrlen,(__haystack,__needle))
#else /* LIBC: rawmemrlen */
#include <local/string/rawmemrlen.h>
/* Same as `rawmemrchrb', but return the offset from `HAYSTACK', rather than the actual address. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemrlenb)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrlen))(__haystack, __needle); }
#endif /* rawmemrlenb... */
#if defined(__CRT_HAVE_rawmemrlenw)
/* Same as `rawmemrchrw', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemrlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),(__haystack,__word))
#else /* LIBC: rawmemrlenw */
#include <local/string/rawmemrlenw.h>
/* Same as `rawmemrchrw', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrlenw, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemrlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrlenw))(__haystack, __word); })
#endif /* rawmemrlenw... */
#if defined(__CRT_HAVE_rawmemrlenl)
/* Same as `rawmemrchrl', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemrlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),(__haystack,__dword))
#else /* LIBC: rawmemrlenl */
#include <local/string/rawmemrlenl.h>
/* Same as `rawmemrchrl', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrlenl, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemrlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrlenl))(__haystack, __dword); })
#endif /* rawmemrlenl... */
#ifdef __UINT64_TYPE__
#if defined(__fast_memcpyq_defined)
/* Copy memory between non-overlapping memory blocks. */
__NAMESPACE_FAST_USING_OR_IMPL(memcpyq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyq)(void *__restrict __dst, void const *__restrict __src, size_t __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyq))(__dst, __src, __n_qwords); })
#elif defined(__CRT_HAVE_memcpyq)
/* Copy memory between non-overlapping memory blocks. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,memcpyq,(void *__restrict __dst, void const *__restrict __src, size_t __n_qwords),(__dst,__src,__n_qwords))
#else /* LIBC: memcpyq */
#include <local/string/memcpyq.h>
/* Copy memory between non-overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpyq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memcpyq)(void *__restrict __dst, void const *__restrict __src, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyq))(__dst, __src, __n_qwords); })
#endif /* memcpyq... */
#if defined(__fast_mempcpyq_defined)
/* Same as `memcpyq', but return `DST+N_QWORDS', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempcpyq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyq)(void *__restrict __dst, void const *__restrict __src, size_t __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyq))(__dst, __src, __n_qwords); })
#elif defined(__CRT_HAVE_mempcpyq)
/* Same as `memcpyq', but return `DST+N_QWORDS', rather than `DST' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,mempcpyq,(void *__restrict __dst, void const *__restrict __src, size_t __n_qwords),(__dst,__src,__n_qwords))
#else /* LIBC: mempcpyq */
#include <local/string/mempcpyq.h>
/* Same as `memcpyq', but return `DST+N_QWORDS', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempcpyq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempcpyq)(void *__restrict __dst, void const *__restrict __src, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyq))(__dst, __src, __n_qwords); })
#endif /* mempcpyq... */
#if defined(__fast_memmoveq_defined)
/* Move memory between potentially overlapping memory blocks. */
__NAMESPACE_FAST_USING_OR_IMPL(memmoveq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveq)(void *__dst, void const *__src, size_t __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveq))(__dst, __src, __n_qwords); })
#elif defined(__CRT_HAVE_memmoveq)
/* Move memory between potentially overlapping memory blocks. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,memmoveq,(void *__dst, void const *__src, size_t __n_qwords),(__dst,__src,__n_qwords))
#else /* LIBC: memmoveq */
#include <local/string/memmoveq.h>
/* Move memory between potentially overlapping memory blocks. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memmoveq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memmoveq)(void *__dst, void const *__src, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveq))(__dst, __src, __n_qwords); })
#endif /* memmoveq... */
#if defined(__fast_mempmoveq_defined)
/* Same as `memmovew', but return `DST+N_QWORDS', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempmoveq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveq)(void *__restrict __dst, void const *__restrict __src, size_t __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveq))(__dst, __src, __n_qwords); })
#elif defined(__CRT_HAVE_mempmoveq)
/* Same as `memmovew', but return `DST+N_QWORDS', rather than `DST' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,mempmoveq,(void *__restrict __dst, void const *__restrict __src, size_t __n_qwords),(__dst,__src,__n_qwords))
#else /* LIBC: mempmoveq */
#include <local/string/mempmoveq.h>
/* Same as `memmovew', but return `DST+N_QWORDS', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmoveq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempmoveq)(void *__restrict __dst, void const *__restrict __src, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveq))(__dst, __src, __n_qwords); })
#endif /* mempmoveq... */
#if defined(__fast_memsetq_defined)
/* Fill memory with a given qword */
__NAMESPACE_FAST_USING_OR_IMPL(memsetq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetq)(void *__restrict __dst, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetq))(__dst, __qword, __n_qwords); })
#elif defined(__CRT_HAVE_memsetq)
/* Fill memory with a given qword */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memsetq,(void *__restrict __dst, __UINT64_TYPE__ __qword, size_t __n_qwords),(__dst,__qword,__n_qwords))
#else /* LIBC: memsetq */
#include <local/string/memsetq.h>
/* Fill memory with a given qword */
__NAMESPACE_LOCAL_USING_OR_IMPL(memsetq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memsetq)(void *__restrict __dst, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetq))(__dst, __qword, __n_qwords); })
#endif /* memsetq... */
#if defined(__fast_mempsetq_defined)
/* Same as `memsetq', but return `DST+N_QWORDS', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempsetq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetq)(void *__restrict __dst, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetq))(__dst, __qword, __n_qwords); })
#elif defined(__CRT_HAVE_mempsetq)
/* Same as `memsetq', but return `DST+N_QWORDS', rather than `DST' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,mempsetq,(void *__restrict __dst, __UINT64_TYPE__ __qword, size_t __n_qwords),(__dst,__qword,__n_qwords))
#else /* LIBC: mempsetq */
#include <local/string/mempsetq.h>
/* Same as `memsetq', but return `DST+N_QWORDS', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempsetq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL mempsetq)(void *__restrict __dst, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetq))(__dst, __qword, __n_qwords); })
#endif /* mempsetq... */
#if defined(__fast_memcmpq_defined)
/* Compare memory buffers and return the difference of the first non-matching qword */
__NAMESPACE_FAST_USING_OR_IMPL(memcmpq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL memcmpq)(void const *__s1, void const *__s2, size_t __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpq))(__s1, __s2, __n_dwords); })
#elif defined(__CRT_HAVE_memcmpq)
/* Compare memory buffers and return the difference of the first non-matching qword */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),__INT64_TYPE__,__NOTHROW_NCX,memcmpq,(void const *__s1, void const *__s2, size_t __n_dwords),(__s1,__s2,__n_dwords))
#else /* LIBC: memcmpq */
#include <local/string/memcmpq.h>
/* Compare memory buffers and return the difference of the first non-matching qword */
__NAMESPACE_LOCAL_USING_OR_IMPL(memcmpq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL memcmpq)(void const *__s1, void const *__s2, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpq))(__s1, __s2, __n_dwords); })
#endif /* memcmpq... */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __fast_memchrq_defined
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrq))(__haystack, __qword, __n_qwords); }
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrq))(__haystack, __qword, __n_qwords); }
}
#elif defined(__CRT_HAVE_memchrq)
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memchrq,(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),memchrq,(__haystack, __qword, __n_qwords))
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,memchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),memchrq,(__haystack, __qword, __n_qwords))
}
#else /* LIBC: memchrq */
#include <local/string/memchrq.h>
extern "C++" {
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrq))(__haystack, __qword, __n_qwords); }
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrq))(__haystack, __qword, __n_qwords); }
}
#endif /* memchrq... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memchrq_defined)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_FAST_USING_OR_IMPL(memchrq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrq))(__haystack, __qword, __n_qwords); })
#elif defined(__CRT_HAVE_memchrq)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),(__haystack,__qword,__n_qwords))
#else /* LIBC: memchrq */
#include <local/string/memchrq.h>
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memchrq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrq))(__haystack, __qword, __n_qwords); })
#endif /* memchrq... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __fast_memrchrq_defined
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrq))(__haystack, __qword, __n_qwords); }
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrq))(__haystack, __qword, __n_qwords); }
}
#elif defined(__CRT_HAVE_memrchrq)
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memrchrq,(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),memrchrq,(__haystack, __qword, __n_qwords))
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,memrchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),memrchrq,(__haystack, __qword, __n_qwords))
}
#else /* LIBC: memrchrq */
#include <local/string/memrchrq.h>
extern "C++" {
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrq))(__haystack, __qword, __n_qwords); }
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrq))(__haystack, __qword, __n_qwords); }
}
#endif /* memrchrq... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memrchrq_defined)
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_FAST_USING_OR_IMPL(memrchrq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrq))(__haystack, __qword, __n_qwords); })
#elif defined(__CRT_HAVE_memrchrq)
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memrchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),(__haystack,__qword,__n_qwords))
#else /* LIBC: memrchrq */
#include <local/string/memrchrq.h>
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrchrq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrq))(__haystack, __qword, __n_qwords); })
#endif /* memrchrq... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemchrq)
extern "C++" {
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemchrq,(void *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemchrq,(__haystack, __qword))
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,rawmemchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemchrq,(__haystack, __qword))
}
#else /* LIBC: rawmemchrq */
#include <local/string/rawmemchrq.h>
extern "C++" {
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrq))(__haystack, __qword); }
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrq))(__haystack, __qword); }
}
#endif /* rawmemchrq... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemchrq)
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),(__haystack,__qword))
#else /* LIBC: rawmemchrq */
#include <local/string/rawmemchrq.h>
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemchrq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemchrq))(__haystack, __qword); })
#endif /* rawmemchrq... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemrchrq)
extern "C++" {
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK-8' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemrchrq,(void *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemrchrq,(__haystack, __qword))
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK-8' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,rawmemrchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemrchrq,(__haystack, __qword))
}
#else /* LIBC: rawmemrchrq */
#include <local/string/rawmemrchrq.h>
extern "C++" {
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK-8' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrq))(__haystack, __qword); }
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK-8' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrq))(__haystack, __qword); }
}
#endif /* rawmemrchrq... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemrchrq)
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK-8' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemrchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),(__haystack,__qword))
#else /* LIBC: rawmemrchrq */
#include <local/string/rawmemrchrq.h>
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK-8' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrchrq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchrq))(__haystack, __qword); })
#endif /* rawmemrchrq... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __fast_memendq_defined
extern "C++" {
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendq))(__haystack, __qword, __n_bytes); }
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendq))(__haystack, __qword, __n_bytes); }
}
#elif defined(__CRT_HAVE_memendq)
extern "C++" {
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memendq,(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_bytes),memendq,(__haystack, __qword, __n_bytes))
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,memendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_bytes),memendq,(__haystack, __qword, __n_bytes))
}
#else /* LIBC: memendq */
#include <local/string/memendq.h>
extern "C++" {
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendq))(__haystack, __qword, __n_bytes); }
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendq))(__haystack, __qword, __n_bytes); }
}
#endif /* memendq... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memendq_defined)
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_FAST_USING_OR_IMPL(memendq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendq))(__haystack, __qword, __n_bytes); })
#elif defined(__CRT_HAVE_memendq)
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_bytes),(__haystack,__qword,__n_bytes))
#else /* LIBC: memendq */
#include <local/string/memendq.h>
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memendq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendq))(__haystack, __qword, __n_bytes); })
#endif /* memendq... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __fast_memrendq_defined
extern "C++" {
/* Same as `memrchrq', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendq))(__haystack, __qword, __n_qwords); }
/* Same as `memrchrq', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendq))(__haystack, __qword, __n_qwords); }
}
#elif defined(__CRT_HAVE_memrendq)
extern "C++" {
/* Same as `memrchrq', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memrendq,(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),memrendq,(__haystack, __qword, __n_qwords))
/* Same as `memrchrq', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,memrendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),memrendq,(__haystack, __qword, __n_qwords))
}
#else /* LIBC: memrendq */
#include <local/string/memrendq.h>
extern "C++" {
/* Same as `memrchrq', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendq))(__haystack, __qword, __n_qwords); }
/* Same as `memrchrq', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendq))(__haystack, __qword, __n_qwords); }
}
#endif /* memrendq... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memrendq_defined)
/* Same as `memrchrq', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_FAST_USING_OR_IMPL(memrendq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendq))(__haystack, __qword, __n_qwords); })
#elif defined(__CRT_HAVE_memrendq)
/* Same as `memrchrq', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memrendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),(__haystack,__qword,__n_qwords))
#else /* LIBC: memrendq */
#include <local/string/memrendq.h>
/* Same as `memrchrq', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrendq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendq))(__haystack, __qword, __n_qwords); })
#endif /* memrendq... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memlenq_defined)
/* Same as `memendq', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_FAST_USING_OR_IMPL(memlenq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memlenq))(__haystack, __qword, __n_qwords); })
#elif defined(__CRT_HAVE_memlenq)
/* Same as `memendq', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),(__haystack,__qword,__n_qwords))
#else /* LIBC: memlenq */
#include <local/string/memlenq.h>
/* Same as `memendq', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memlenq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlenq))(__haystack, __qword, __n_qwords); })
#endif /* memlenq... */
#if defined(__fast_memrlenq_defined)
/* Same as `memrendq', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_FAST_USING_OR_IMPL(memrlenq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memrlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrlenq))(__haystack, __qword, __n_qwords); })
#elif defined(__CRT_HAVE_memrlenq)
/* Same as `memrendq', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memrlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),(__haystack,__qword,__n_qwords))
#else /* LIBC: memrlenq */
#include <local/string/memrlenq.h>
/* Same as `memrendq', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrlenq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memrlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlenq))(__haystack, __qword, __n_qwords); })
#endif /* memrlenq... */
#if defined(__fast_rawmemlenq_defined)
/* Same as `rawmemchrq', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_FAST_USING_OR_IMPL(rawmemlenq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(rawmemlenq))(__haystack, __qword); })
#elif defined(__CRT_HAVE_rawmemlenq)
/* Same as `rawmemchrq', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),(__haystack,__qword))
#else /* LIBC: rawmemlenq */
#include <local/string/rawmemlenq.h>
/* Same as `rawmemchrq', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemlenq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemlenq))(__haystack, __qword); })
#endif /* rawmemlenq... */
#if defined(__fast_rawmemrlenq_defined)
/* Same as `rawmemrchrq', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_FAST_USING_OR_IMPL(rawmemrlenq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemrlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(rawmemrlenq))(__haystack, __qword); })
#elif defined(__CRT_HAVE_rawmemrlenq)
/* Same as `rawmemrchrq', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemrlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),(__haystack,__qword))
#else /* LIBC: rawmemrlenq */
#include <local/string/rawmemrlenq.h>
/* Same as `rawmemrchrq', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrlenq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemrlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrlenq))(__haystack, __qword); })
#endif /* rawmemrlenq... */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */


#ifdef __USE_STRING_XCHR
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memxchr)
extern "C++" {
/* Same as `memchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memxchr,(void *__restrict __haystack, int __needle, size_t __n_bytes),memxchr,(__haystack, __needle, __n_bytes))
/* Same as `memchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memxchr,(void const *__restrict __haystack, int __needle, size_t __n_bytes),memxchr,(__haystack, __needle, __n_bytes))
}
#else /* LIBC: memxchr */
#include <local/string/memxchr.h>
extern "C++" {
/* Same as `memchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memxchr)(void *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchr))(__haystack, __needle, __n_bytes); }
/* Same as `memchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memxchr)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchr))(__haystack, __needle, __n_bytes); }
}
#endif /* memxchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memxchr)
/* Same as `memchr', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memxchr,(void const *__restrict __haystack, int __needle, size_t __n_bytes),(__haystack,__needle,__n_bytes))
#else /* LIBC: memxchr */
#include <local/string/memxchr.h>
/* Same as `memchr', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxchr, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memxchr)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchr))(__haystack, __needle, __n_bytes); })
#endif /* memxchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memrxchr)
extern "C++" {
/* Same as `memrchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrxchr,(void *__restrict __haystack, int __needle, size_t __n_bytes),memrxchr,(__haystack, __needle, __n_bytes))
/* Same as `memrchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memrxchr,(void const *__restrict __haystack, int __needle, size_t __n_bytes),memrxchr,(__haystack, __needle, __n_bytes))
}
#else /* LIBC: memrxchr */
#include <local/string/memrxchr.h>
extern "C++" {
/* Same as `memrchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrxchr)(void *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchr))(__haystack, __needle, __n_bytes); }
/* Same as `memrchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memrxchr)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchr))(__haystack, __needle, __n_bytes); }
}
#endif /* memrxchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memrxchr)
/* Same as `memrchr', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrxchr,(void const *__restrict __haystack, int __needle, size_t __n_bytes),(__haystack,__needle,__n_bytes))
#else /* LIBC: memrxchr */
#include <local/string/memrxchr.h>
/* Same as `memrchr', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxchr, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrxchr)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchr))(__haystack, __needle, __n_bytes); })
#endif /* memrxchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemxchr)
extern "C++" {
/* Same as `rawmemchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemxchr,(void *__restrict __haystack, int __needle),rawmemxchr,(__haystack, __needle))
/* Same as `rawmemchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,rawmemxchr,(void const *__restrict __haystack, int __needle),rawmemxchr,(__haystack, __needle))
}
#else /* LIBC: rawmemxchr */
#include <local/string/rawmemxchr.h>
extern "C++" {
/* Same as `rawmemchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemxchr)(void *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))(__haystack, __needle); }
/* Same as `rawmemchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL rawmemxchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))(__haystack, __needle); }
}
#endif /* rawmemxchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemxchr)
/* Same as `rawmemchr', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemxchr,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* LIBC: rawmemxchr */
#include <local/string/rawmemxchr.h>
/* Same as `rawmemchr', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxchr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemxchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))(__haystack, __needle); })
#endif /* rawmemxchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemrxchr)
extern "C++" {
/* Same as `rawmemrchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemrxchr,(void *__restrict __haystack, int __needle),rawmemrxchr,(__haystack, __needle))
/* Same as `rawmemrchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,rawmemrxchr,(void const *__restrict __haystack, int __needle),rawmemrxchr,(__haystack, __needle))
}
#else /* LIBC: rawmemrxchr */
#include <local/string/rawmemrxchr.h>
extern "C++" {
/* Same as `rawmemrchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemrxchr)(void *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchr))(__haystack, __needle); }
/* Same as `rawmemrchr', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL rawmemrxchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchr))(__haystack, __needle); }
}
#endif /* rawmemrxchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemrxchr)
/* Same as `rawmemrchr', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemrxchr,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* LIBC: rawmemrxchr */
#include <local/string/rawmemrxchr.h>
/* Same as `rawmemrchr', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxchr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemrxchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchr))(__haystack, __needle); })
#endif /* rawmemrxchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memxend)
extern "C++" {
/* Same as `memend', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memxend,(void *__restrict __haystack, int __needle, size_t __n_bytes),memxend,(__haystack, __needle, __n_bytes))
/* Same as `memend', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memxend,(void const *__restrict __haystack, int __needle, size_t __n_bytes),memxend,(__haystack, __needle, __n_bytes))
}
#else /* LIBC: memxend */
#include <local/string/memxend.h>
extern "C++" {
/* Same as `memend', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memxend)(void *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))(__haystack, __needle, __n_bytes); }
/* Same as `memend', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memxend)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))(__haystack, __needle, __n_bytes); }
}
#endif /* memxend... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memxend)
/* Same as `memend', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memxend,(void const *__restrict __haystack, int __needle, size_t __n_bytes),(__haystack,__needle,__n_bytes))
#else /* LIBC: memxend */
#include <local/string/memxend.h>
/* Same as `memend', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxend, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memxend)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))(__haystack, __needle, __n_bytes); })
#endif /* memxend... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memrxend)
extern "C++" {
/* Same as `memrend', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrxend,(void *__restrict __haystack, int __needle, size_t __n_bytes),memrxend,(__haystack, __needle, __n_bytes))
/* Same as `memrend', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memrxend,(void const *__restrict __haystack, int __needle, size_t __n_bytes),memrxend,(__haystack, __needle, __n_bytes))
}
#else /* LIBC: memrxend */
#include <local/string/memrxend.h>
extern "C++" {
/* Same as `memrend', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrxend)(void *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))(__haystack, __needle, __n_bytes); }
/* Same as `memrend', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memrxend)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))(__haystack, __needle, __n_bytes); }
}
#endif /* memrxend... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memrxend)
/* Same as `memrend', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrxend,(void const *__restrict __haystack, int __needle, size_t __n_bytes),(__haystack,__needle,__n_bytes))
#else /* LIBC: memrxend */
#include <local/string/memrxend.h>
/* Same as `memrend', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxend, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrxend)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))(__haystack, __needle, __n_bytes); })
#endif /* memrxend... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memxlen)
/* Same as `memlen', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memxlen,(void const *__restrict __haystack, int __needle, size_t __n_bytes),(__haystack,__needle,__n_bytes))
#else /* LIBC: memxlen */
#include <local/string/memxlen.h>
/* Same as `memlen', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxlen, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memxlen)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxlen))(__haystack, __needle, __n_bytes); })
#endif /* memxlen... */
#if defined(__CRT_HAVE_memrxlen)
/* Same as `memrlen', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memrxlen,(void const *__restrict __haystack, int __needle, size_t __n_bytes),(__haystack,__needle,__n_bytes))
#else /* LIBC: memrxlen */
#include <local/string/memrxlen.h>
/* Same as `memrlen', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxlen, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memrxlen)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxlen))(__haystack, __needle, __n_bytes); })
#endif /* memrxlen... */
#if defined(__CRT_HAVE_rawmemxlen)
/* Same as `rawmemlen', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemxlen,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* LIBC: rawmemxlen */
#include <local/string/rawmemxlen.h>
/* Same as `rawmemlen', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxlen, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemxlen)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxlen))(__haystack, __needle); })
#endif /* rawmemxlen... */
#if defined(__CRT_HAVE_rawmemrxlen)
/* Same as `rawmemrlen', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemrxlen,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* LIBC: rawmemrxlen */
#include <local/string/rawmemrxlen.h>
/* Same as `rawmemrlen', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxlen, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemrxlen)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxlen))(__haystack, __needle); })
#endif /* rawmemrxlen... */
#ifdef __USE_STRING_BWLQ
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memxchrb)
extern "C++" {
/* Same as `memchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memxchrb,(void *__restrict __haystack, int __byte, size_t __n_bytes),memxchrb,(__haystack, __byte, __n_bytes))
/* Same as `memchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memxchrb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memxchrb,(__haystack, __byte, __n_bytes))
}
#elif defined(__CRT_HAVE_memxchr)
extern "C++" {
/* Same as `memchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memxchrb,(void *__restrict __haystack, int __byte, size_t __n_bytes),memxchr,(__haystack, __byte, __n_bytes))
/* Same as `memchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memxchrb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memxchr,(__haystack, __byte, __n_bytes))
}
#else /* LIBC: memxchr */
#include <local/string/memxchr.h>
extern "C++" {
/* Same as `memchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrb)(void *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchr))(__haystack, __byte, __n_bytes); }
/* Same as `memchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxchrb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchr))(__haystack, __byte, __n_bytes); }
}
#endif /* memxchrb... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memxchrb)
/* Same as `memchrb', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memxchrb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),(__haystack,__byte,__n_bytes))
#elif defined(__CRT_HAVE_memxchr)
/* Same as `memchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memxchrb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memxchr,(__haystack,__byte,__n_bytes))
#else /* LIBC: memxchr */
#include <local/string/memxchr.h>
/* Same as `memchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchr))(__haystack, __byte, __n_bytes); }
#endif /* memxchrb... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memxchrw)
extern "C++" {
/* Same as `memchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memxchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),memxchrw,(__haystack, __word, __n_words))
/* Same as `memchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,memxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),memxchrw,(__haystack, __word, __n_words))
}
#else /* LIBC: memxchrw */
#include <local/string/memxchrw.h>
extern "C++" {
/* Same as `memchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrw))(__haystack, __word, __n_words); }
/* Same as `memchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrw))(__haystack, __word, __n_words); }
}
#endif /* memxchrw... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memxchrw)
/* Same as `memchrw', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),(__haystack,__word,__n_words))
#else /* LIBC: memxchrw */
#include <local/string/memxchrw.h>
/* Same as `memchrw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxchrw, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrw))(__haystack, __word, __n_words); })
#endif /* memxchrw... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memxchrl)
extern "C++" {
/* Same as `memchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memxchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),memxchrl,(__haystack, __dword, __n_dwords))
/* Same as `memchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,memxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),memxchrl,(__haystack, __dword, __n_dwords))
}
#else /* LIBC: memxchrl */
#include <local/string/memxchrl.h>
extern "C++" {
/* Same as `memchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrl))(__haystack, __dword, __n_dwords); }
/* Same as `memchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrl))(__haystack, __dword, __n_dwords); }
}
#endif /* memxchrl... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memxchrl)
/* Same as `memchrl', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),(__haystack,__dword,__n_dwords))
#else /* LIBC: memxchrl */
#include <local/string/memxchrl.h>
/* Same as `memchrl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxchrl, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrl))(__haystack, __dword, __n_dwords); })
#endif /* memxchrl... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memrxchrb)
extern "C++" {
/* Same as `memrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrxchrb,(void *__restrict __haystack, int __byte, size_t __n_bytes),memrxchrb,(__haystack, __byte, __n_bytes))
/* Same as `memrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memrxchrb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memrxchrb,(__haystack, __byte, __n_bytes))
}
#elif defined(__CRT_HAVE_memrxchr)
extern "C++" {
/* Same as `memrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrxchrb,(void *__restrict __haystack, int __byte, size_t __n_bytes),memrxchr,(__haystack, __byte, __n_bytes))
/* Same as `memrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memrxchrb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memrxchr,(__haystack, __byte, __n_bytes))
}
#else /* LIBC: memrxchr */
#include <local/string/memrxchr.h>
extern "C++" {
/* Same as `memrchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrb)(void *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchr))(__haystack, __byte, __n_bytes); }
/* Same as `memrchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxchrb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchr))(__haystack, __byte, __n_bytes); }
}
#endif /* memrxchrb... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memrxchrb)
/* Same as `memrchrb', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrxchrb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),(__haystack,__byte,__n_bytes))
#elif defined(__CRT_HAVE_memrxchr)
/* Same as `memrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrxchrb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memrxchr,(__haystack,__byte,__n_bytes))
#else /* LIBC: memrxchr */
#include <local/string/memrxchr.h>
/* Same as `memrchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchr))(__haystack, __byte, __n_bytes); }
#endif /* memrxchrb... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memrxchrw)
extern "C++" {
/* Same as `memrchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memrxchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),memrxchrw,(__haystack, __word, __n_words))
/* Same as `memrchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,memrxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),memrxchrw,(__haystack, __word, __n_words))
}
#else /* LIBC: memrxchrw */
#include <local/string/memrxchrw.h>
extern "C++" {
/* Same as `memrchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrw))(__haystack, __word, __n_words); }
/* Same as `memrchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrw))(__haystack, __word, __n_words); }
}
#endif /* memrxchrw... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memrxchrw)
/* Same as `memrchrw', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memrxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),(__haystack,__word,__n_words))
#else /* LIBC: memrxchrw */
#include <local/string/memrxchrw.h>
/* Same as `memrchrw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxchrw, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrw))(__haystack, __word, __n_words); })
#endif /* memrxchrw... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memrxchrl)
extern "C++" {
/* Same as `memrchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memrxchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),memrxchrl,(__haystack, __dword, __n_dwords))
/* Same as `memrchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,memrxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),memrxchrl,(__haystack, __dword, __n_dwords))
}
#else /* LIBC: memrxchrl */
#include <local/string/memrxchrl.h>
extern "C++" {
/* Same as `memrchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrl))(__haystack, __dword, __n_dwords); }
/* Same as `memrchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrl))(__haystack, __dword, __n_dwords); }
}
#endif /* memrxchrl... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memrxchrl)
/* Same as `memrchrl', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memrxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),(__haystack,__dword,__n_dwords))
#else /* LIBC: memrxchrl */
#include <local/string/memrxchrl.h>
/* Same as `memrchrl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxchrl, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrl))(__haystack, __dword, __n_dwords); })
#endif /* memrxchrl... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemxchrb)
extern "C++" {
/* Same as `rawmemchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemxchrb,(void *__restrict __haystack, int __byte),rawmemxchrb,(__haystack, __byte))
/* Same as `rawmemchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,rawmemxchrb,(void const *__restrict __haystack, int __byte),rawmemxchrb,(__haystack, __byte))
}
#elif defined(__CRT_HAVE_rawmemxchr)
extern "C++" {
/* Same as `rawmemchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemxchrb,(void *__restrict __haystack, int __byte),rawmemxchr,(__haystack, __byte))
/* Same as `rawmemchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,rawmemxchrb,(void const *__restrict __haystack, int __byte),rawmemxchr,(__haystack, __byte))
}
#else /* LIBC: rawmemxchr */
#include <local/string/rawmemxchr.h>
extern "C++" {
/* Same as `rawmemchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrb)(void *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))(__haystack, __byte); }
/* Same as `rawmemchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemxchrb)(void const *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))(__haystack, __byte); }
}
#endif /* rawmemxchrb... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemxchrb)
/* Same as `rawmemchrb', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemxchrb,(void const *__restrict __haystack, int __byte),(__haystack,__byte))
#elif defined(__CRT_HAVE_rawmemxchr)
/* Same as `rawmemchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemxchrb,(void const *__restrict __haystack, int __byte),rawmemxchr,(__haystack,__byte))
#else /* LIBC: rawmemxchr */
#include <local/string/rawmemxchr.h>
/* Same as `rawmemchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrb)(void const *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))(__haystack, __byte); }
#endif /* rawmemxchrb... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemxchrw)
extern "C++" {
/* Same as `rawmemchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemxchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word),rawmemxchrw,(__haystack, __word))
/* Same as `rawmemchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,rawmemxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),rawmemxchrw,(__haystack, __word))
}
#else /* LIBC: rawmemxchrw */
#include <local/string/rawmemxchrw.h>
extern "C++" {
/* Same as `rawmemchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrw))(__haystack, __word); }
/* Same as `rawmemchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrw))(__haystack, __word); }
}
#endif /* rawmemxchrw... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemxchrw)
/* Same as `rawmemchrw', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),(__haystack,__word))
#else /* LIBC: rawmemxchrw */
#include <local/string/rawmemxchrw.h>
/* Same as `rawmemchrw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxchrw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrw))(__haystack, __word); })
#endif /* rawmemxchrw... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemxchrl)
extern "C++" {
/* Same as `rawmemchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemxchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword),rawmemxchrl,(__haystack, __dword))
/* Same as `rawmemchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,rawmemxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),rawmemxchrl,(__haystack, __dword))
}
#else /* LIBC: rawmemxchrl */
#include <local/string/rawmemxchrl.h>
extern "C++" {
/* Same as `rawmemchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrl))(__haystack, __dword); }
/* Same as `rawmemchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrl))(__haystack, __dword); }
}
#endif /* rawmemxchrl... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemxchrl)
/* Same as `rawmemchrl', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),(__haystack,__dword))
#else /* LIBC: rawmemxchrl */
#include <local/string/rawmemxchrl.h>
/* Same as `rawmemchrl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxchrl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrl))(__haystack, __dword); })
#endif /* rawmemxchrl... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemrxchrb)
extern "C++" {
/* Same as `rawmemrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemrxchrb,(void *__restrict __haystack, int __byte),rawmemrxchrb,(__haystack, __byte))
/* Same as `rawmemrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,rawmemrxchrb,(void const *__restrict __haystack, int __byte),rawmemrxchrb,(__haystack, __byte))
}
#elif defined(__CRT_HAVE_rawmemrxchr)
extern "C++" {
/* Same as `rawmemrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemrxchrb,(void *__restrict __haystack, int __byte),rawmemrxchr,(__haystack, __byte))
/* Same as `rawmemrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,rawmemrxchrb,(void const *__restrict __haystack, int __byte),rawmemrxchr,(__haystack, __byte))
}
#else /* LIBC: rawmemrxchr */
#include <local/string/rawmemrxchr.h>
extern "C++" {
/* Same as `rawmemrchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrb)(void *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchr))(__haystack, __byte); }
/* Same as `rawmemrchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrxchrb)(void const *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchr))(__haystack, __byte); }
}
#endif /* rawmemrxchrb... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemrxchrb)
/* Same as `rawmemrchrb', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemrxchrb,(void const *__restrict __haystack, int __byte),(__haystack,__byte))
#elif defined(__CRT_HAVE_rawmemrxchr)
/* Same as `rawmemrchrb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,rawmemrxchrb,(void const *__restrict __haystack, int __byte),rawmemrxchr,(__haystack,__byte))
#else /* LIBC: rawmemrxchr */
#include <local/string/rawmemrxchr.h>
/* Same as `rawmemrchrb', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrb)(void const *__restrict __haystack, int __byte) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchr))(__haystack, __byte); }
#endif /* rawmemrxchrb... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemrxchrw)
extern "C++" {
/* Same as `rawmemrchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemrxchrw,(void *__restrict __haystack, __UINT16_TYPE__ __word),rawmemrxchrw,(__haystack, __word))
/* Same as `rawmemrchrw', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,rawmemrxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),rawmemrxchrw,(__haystack, __word))
}
#else /* LIBC: rawmemrxchrw */
#include <local/string/rawmemrxchrw.h>
extern "C++" {
/* Same as `rawmemrchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrw)(void *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrw))(__haystack, __word); }
/* Same as `rawmemrchrw', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrw))(__haystack, __word); }
}
#endif /* rawmemrxchrw... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemrxchrw)
/* Same as `rawmemrchrw', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,rawmemrxchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),(__haystack,__word))
#else /* LIBC: rawmemrxchrw */
#include <local/string/rawmemrxchrw.h>
/* Same as `rawmemrchrw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxchrw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrw))(__haystack, __word); })
#endif /* rawmemrxchrw... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemrxchrl)
extern "C++" {
/* Same as `rawmemrchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemrxchrl,(void *__restrict __haystack, __UINT32_TYPE__ __dword),rawmemrxchrl,(__haystack, __dword))
/* Same as `rawmemrchrl', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,rawmemrxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),rawmemrxchrl,(__haystack, __dword))
}
#else /* LIBC: rawmemrxchrl */
#include <local/string/rawmemrxchrl.h>
extern "C++" {
/* Same as `rawmemrchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrl)(void *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrl))(__haystack, __dword); }
/* Same as `rawmemrchrl', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrl))(__haystack, __dword); }
}
#endif /* rawmemrxchrl... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemrxchrl)
/* Same as `rawmemrchrl', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,rawmemrxchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),(__haystack,__dword))
#else /* LIBC: rawmemrxchrl */
#include <local/string/rawmemrxchrl.h>
/* Same as `rawmemrchrl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxchrl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrl))(__haystack, __dword); })
#endif /* rawmemrxchrl... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memxendb)
extern "C++" {
/* Same as `memendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memxendb,(void *__restrict __haystack, int __byte, size_t __n_bytes),memxendb,(__haystack, __byte, __n_bytes))
/* Same as `memendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memxendb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memxendb,(__haystack, __byte, __n_bytes))
}
#elif defined(__CRT_HAVE_memxend)
extern "C++" {
/* Same as `memendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memxendb,(void *__restrict __haystack, int __byte, size_t __n_bytes),memxend,(__haystack, __byte, __n_bytes))
/* Same as `memendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memxendb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memxend,(__haystack, __byte, __n_bytes))
}
#else /* LIBC: memxend */
#include <local/string/memxend.h>
extern "C++" {
/* Same as `memendb', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendb)(void *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))(__haystack, __byte, __n_bytes); }
/* Same as `memendb', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxendb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))(__haystack, __byte, __n_bytes); }
}
#endif /* memxendb... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memxendb)
/* Same as `memendb', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memxendb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),(__haystack,__byte,__n_bytes))
#elif defined(__CRT_HAVE_memxend)
/* Same as `memendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memxendb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memxend,(__haystack,__byte,__n_bytes))
#else /* LIBC: memxend */
#include <local/string/memxend.h>
/* Same as `memendb', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))(__haystack, __byte, __n_bytes); }
#endif /* memxendb... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memxendw)
extern "C++" {
/* Same as `memendw', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memxendw,(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_bytes),memxendw,(__haystack, __word, __n_bytes))
/* Same as `memendw', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,memxendw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_bytes),memxendw,(__haystack, __word, __n_bytes))
}
#else /* LIBC: memxendw */
#include <local/string/memxendw.h>
extern "C++" {
/* Same as `memendw', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendw)(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendw))(__haystack, __word, __n_bytes); }
/* Same as `memendw', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendw))(__haystack, __word, __n_bytes); }
}
#endif /* memxendw... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memxendw)
/* Same as `memendw', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memxendw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_bytes),(__haystack,__word,__n_bytes))
#else /* LIBC: memxendw */
#include <local/string/memxendw.h>
/* Same as `memendw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxendw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendw))(__haystack, __word, __n_bytes); })
#endif /* memxendw... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memxendl)
extern "C++" {
/* Same as `memendl', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memxendl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_bytes),memxendl,(__haystack, __dword, __n_bytes))
/* Same as `memendl', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,memxendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_bytes),memxendl,(__haystack, __dword, __n_bytes))
}
#else /* LIBC: memxendl */
#include <local/string/memxendl.h>
extern "C++" {
/* Same as `memendl', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendl))(__haystack, __dword, __n_bytes); }
/* Same as `memendl', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendl))(__haystack, __dword, __n_bytes); }
}
#endif /* memxendl... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memxendl)
/* Same as `memendl', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memxendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_bytes),(__haystack,__dword,__n_bytes))
#else /* LIBC: memxendl */
#include <local/string/memxendl.h>
/* Same as `memendl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxendl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendl))(__haystack, __dword, __n_bytes); })
#endif /* memxendl... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memrxendb)
extern "C++" {
/* Same as `memrendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrxendb,(void *__restrict __haystack, int __byte, size_t __n_bytes),memrxendb,(__haystack, __byte, __n_bytes))
/* Same as `memrendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memrxendb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memrxendb,(__haystack, __byte, __n_bytes))
}
#elif defined(__CRT_HAVE_memrxend)
extern "C++" {
/* Same as `memrendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrxendb,(void *__restrict __haystack, int __byte, size_t __n_bytes),memrxend,(__haystack, __byte, __n_bytes))
/* Same as `memrendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ const *,__NOTHROW_NCX,memrxendb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memrxend,(__haystack, __byte, __n_bytes))
}
#else /* LIBC: memrxend */
#include <local/string/memrxend.h>
extern "C++" {
/* Same as `memrendb', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendb)(void *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))(__haystack, __byte, __n_bytes); }
/* Same as `memrendb', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxendb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))(__haystack, __byte, __n_bytes); }
}
#endif /* memrxendb... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memrxendb)
/* Same as `memrendb', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrxendb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),(__haystack,__byte,__n_bytes))
#elif defined(__CRT_HAVE_memrxend)
/* Same as `memrendb', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrxendb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memrxend,(__haystack,__byte,__n_bytes))
#else /* LIBC: memrxend */
#include <local/string/memrxend.h>
/* Same as `memrendb', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))(__haystack, __byte, __n_bytes); }
#endif /* memrxendb... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memrxendw)
extern "C++" {
/* Same as `memrendw', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memrxendw,(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),memrxendw,(__haystack, __word, __n_words))
/* Same as `memrendw', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ const *,__NOTHROW_NCX,memrxendw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),memrxendw,(__haystack, __word, __n_words))
}
#else /* LIBC: memrxendw */
#include <local/string/memrxendw.h>
extern "C++" {
/* Same as `memrendw', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendw)(void *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendw))(__haystack, __word, __n_words); }
/* Same as `memrendw', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendw))(__haystack, __word, __n_words); }
}
#endif /* memrxendw... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memrxendw)
/* Same as `memrendw', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memrxendw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),(__haystack,__word,__n_words))
#else /* LIBC: memrxendw */
#include <local/string/memrxendw.h>
/* Same as `memrendw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxendw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendw))(__haystack, __word, __n_words); })
#endif /* memrxendw... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memrxendl)
extern "C++" {
/* Same as `memrendl', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memrxendl,(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),memrxendl,(__haystack, __dword, __n_dwords))
/* Same as `memrendl', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ const *,__NOTHROW_NCX,memrxendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),memrxendl,(__haystack, __dword, __n_dwords))
}
#else /* LIBC: memrxendl */
#include <local/string/memrxendl.h>
extern "C++" {
/* Same as `memrendl', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendl)(void *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendl))(__haystack, __dword, __n_dwords); }
/* Same as `memrendl', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendl))(__haystack, __dword, __n_dwords); }
}
#endif /* memrxendl... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memrxendl)
/* Same as `memrendl', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memrxendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),(__haystack,__dword,__n_dwords))
#else /* LIBC: memrxendl */
#include <local/string/memrxendl.h>
/* Same as `memrendl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxendl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendl))(__haystack, __dword, __n_dwords); })
#endif /* memrxendl... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memxlenb)
/* Same as `memlenb', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memxlenb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),(__haystack,__byte,__n_bytes))
#elif defined(__CRT_HAVE_memxlen)
/* Same as `memlenb', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memxlenb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memxlen,(__haystack,__byte,__n_bytes))
#else /* LIBC: memxlen */
#include <local/string/memxlen.h>
/* Same as `memlenb', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memxlenb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxlen))(__haystack, __byte, __n_bytes); }
#endif /* memxlenb... */
#if defined(__CRT_HAVE_memxlenw)
/* Same as `memlenw', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memxlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),(__haystack,__word,__n_words))
#else /* LIBC: memxlenw */
#include <local/string/memxlenw.h>
/* Same as `memlenw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxlenw, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memxlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxlenw))(__haystack, __word, __n_words); })
#endif /* memxlenw... */
#if defined(__CRT_HAVE_memxlenl)
/* Same as `memlenl', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memxlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),(__haystack,__dword,__n_dwords))
#else /* LIBC: memxlenl */
#include <local/string/memxlenl.h>
/* Same as `memlenl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxlenl, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memxlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxlenl))(__haystack, __dword, __n_dwords); })
#endif /* memxlenl... */
#if defined(__CRT_HAVE_memrxlenb)
/* Same as `memrlenb', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memrxlenb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),(__haystack,__byte,__n_bytes))
#elif defined(__CRT_HAVE_memrxlen)
/* Same as `memrlenb', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memrxlenb,(void const *__restrict __haystack, int __byte, size_t __n_bytes),memrxlen,(__haystack,__byte,__n_bytes))
#else /* LIBC: memrxlen */
#include <local/string/memrxlen.h>
/* Same as `memrlenb', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memrxlenb)(void const *__restrict __haystack, int __byte, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxlen))(__haystack, __byte, __n_bytes); }
#endif /* memrxlenb... */
#if defined(__CRT_HAVE_memrxlenw)
/* Same as `memrlenw', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memrxlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words),(__haystack,__word,__n_words))
#else /* LIBC: memrxlenw */
#include <local/string/memrxlenw.h>
/* Same as `memrlenw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxlenw, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memrxlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __word, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxlenw))(__haystack, __word, __n_words); })
#endif /* memrxlenw... */
#if defined(__CRT_HAVE_memrxlenl)
/* Same as `memrlenl', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memrxlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords),(__haystack,__dword,__n_dwords))
#else /* LIBC: memrxlenl */
#include <local/string/memrxlenl.h>
/* Same as `memrlenl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxlenl, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memrxlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxlenl))(__haystack, __dword, __n_dwords); })
#endif /* memrxlenl... */
#if defined(__CRT_HAVE_rawmemxlenb)
/* Same as `rawmemlenb', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemxlenb,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#elif defined(__CRT_HAVE_rawmemxlen)
/* Same as `rawmemlenb', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemxlenb,(void const *__restrict __haystack, int __needle),rawmemxlen,(__haystack,__needle))
#else /* LIBC: rawmemxlen */
#include <local/string/rawmemxlen.h>
/* Same as `rawmemlenb', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemxlenb)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxlen))(__haystack, __needle); }
#endif /* rawmemxlenb... */
#if defined(__CRT_HAVE_rawmemxlenw)
/* Same as `rawmemlenw', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemxlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),(__haystack,__word))
#else /* LIBC: rawmemxlenw */
#include <local/string/rawmemxlenw.h>
/* Same as `rawmemlenw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxlenw, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemxlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxlenw))(__haystack, __word); })
#endif /* rawmemxlenw... */
#if defined(__CRT_HAVE_rawmemxlenl)
/* Same as `rawmemlenl', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemxlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),(__haystack,__dword))
#else /* LIBC: rawmemxlenl */
#include <local/string/rawmemxlenl.h>
/* Same as `rawmemlenl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxlenl, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemxlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxlenl))(__haystack, __dword); })
#endif /* rawmemxlenl... */
#if defined(__CRT_HAVE_rawmemrxlenb)
/* Same as `rawmemrlenb', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemrxlenb,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#elif defined(__CRT_HAVE_rawmemrxlen)
/* Same as `rawmemrlenb', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemrxlenb,(void const *__restrict __haystack, int __needle),rawmemrxlen,(__haystack,__needle))
#else /* LIBC: rawmemrxlen */
#include <local/string/rawmemrxlen.h>
/* Same as `rawmemrlenb', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemrxlenb)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxlen))(__haystack, __needle); }
#endif /* rawmemrxlenb... */
#if defined(__CRT_HAVE_rawmemrxlenw)
/* Same as `rawmemrlenw', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemrxlenw,(void const *__restrict __haystack, __UINT16_TYPE__ __word),(__haystack,__word))
#else /* LIBC: rawmemrxlenw */
#include <local/string/rawmemrxlenw.h>
/* Same as `rawmemrlenw', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxlenw, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemrxlenw)(void const *__restrict __haystack, __UINT16_TYPE__ __word) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxlenw))(__haystack, __word); })
#endif /* rawmemrxlenw... */
#if defined(__CRT_HAVE_rawmemrxlenl)
/* Same as `rawmemrlenl', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemrxlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword),(__haystack,__dword))
#else /* LIBC: rawmemrxlenl */
#include <local/string/rawmemrxlenl.h>
/* Same as `rawmemrlenl', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxlenl, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemrxlenl)(void const *__restrict __haystack, __UINT32_TYPE__ __dword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxlenl))(__haystack, __dword); })
#endif /* rawmemrxlenl... */
#ifdef __UINT64_TYPE__
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memxchrq)
extern "C++" {
/* Same as `memchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memxchrq,(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),memxchrq,(__haystack, __qword, __n_qwords))
/* Same as `memchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,memxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),memxchrq,(__haystack, __qword, __n_qwords))
}
#else /* LIBC: memxchrq */
#include <local/string/memxchrq.h>
extern "C++" {
/* Same as `memchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrq))(__haystack, __qword, __n_qwords); }
/* Same as `memchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrq))(__haystack, __qword, __n_qwords); }
}
#endif /* memxchrq... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memxchrq)
/* Same as `memchrq', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),(__haystack,__qword,__n_qwords))
#else /* LIBC: memxchrq */
#include <local/string/memxchrq.h>
/* Same as `memchrq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxchrq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxchrq))(__haystack, __qword, __n_qwords); })
#endif /* memxchrq... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memrxchrq)
extern "C++" {
/* Same as `memrchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memrxchrq,(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),memrxchrq,(__haystack, __qword, __n_qwords))
/* Same as `memrchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,memrxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),memrxchrq,(__haystack, __qword, __n_qwords))
}
#else /* LIBC: memrxchrq */
#include <local/string/memrxchrq.h>
extern "C++" {
/* Same as `memrchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrq))(__haystack, __qword, __n_qwords); }
/* Same as `memrchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrq))(__haystack, __qword, __n_qwords); }
}
#endif /* memrxchrq... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memrxchrq)
/* Same as `memrchrq', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memrxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),(__haystack,__qword,__n_qwords))
#else /* LIBC: memrxchrq */
#include <local/string/memrxchrq.h>
/* Same as `memrchrq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxchrq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxchrq))(__haystack, __qword, __n_qwords); })
#endif /* memrxchrq... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemxchrq)
extern "C++" {
/* Same as `rawmemchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemxchrq,(void *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemxchrq,(__haystack, __qword))
/* Same as `rawmemchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,rawmemxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemxchrq,(__haystack, __qword))
}
#else /* LIBC: rawmemxchrq */
#include <local/string/rawmemxchrq.h>
extern "C++" {
/* Same as `rawmemchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrq))(__haystack, __qword); }
/* Same as `rawmemchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrq))(__haystack, __qword); }
}
#endif /* rawmemxchrq... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemxchrq)
/* Same as `rawmemchrq', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),(__haystack,__qword))
#else /* LIBC: rawmemxchrq */
#include <local/string/rawmemxchrq.h>
/* Same as `rawmemchrq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxchrq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrq))(__haystack, __qword); })
#endif /* rawmemxchrq... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemrxchrq)
extern "C++" {
/* Same as `rawmemrchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemrxchrq,(void *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemrxchrq,(__haystack, __qword))
/* Same as `rawmemrchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,rawmemrxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemrxchrq,(__haystack, __qword))
}
#else /* LIBC: rawmemrxchrq */
#include <local/string/rawmemrxchrq.h>
extern "C++" {
/* Same as `rawmemrchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrq)(void *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrq))(__haystack, __qword); }
/* Same as `rawmemrchrq', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL rawmemrxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrq))(__haystack, __qword); }
}
#endif /* rawmemrxchrq... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemrxchrq)
/* Same as `rawmemrchrq', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,rawmemrxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),(__haystack,__qword))
#else /* LIBC: rawmemrxchrq */
#include <local/string/rawmemrxchrq.h>
/* Same as `rawmemrchrq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxchrq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL rawmemrxchrq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxchrq))(__haystack, __qword); })
#endif /* rawmemrxchrq... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memxendq)
extern "C++" {
/* Same as `memendq', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memxendq,(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_bytes),memxendq,(__haystack, __qword, __n_bytes))
/* Same as `memendq', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,memxendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_bytes),memxendq,(__haystack, __qword, __n_bytes))
}
#else /* LIBC: memxendq */
#include <local/string/memxendq.h>
extern "C++" {
/* Same as `memendq', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendq))(__haystack, __qword, __n_bytes); }
/* Same as `memendq', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memxendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendq))(__haystack, __qword, __n_bytes); }
}
#endif /* memxendq... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memxendq)
/* Same as `memendq', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memxendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_bytes),(__haystack,__qword,__n_bytes))
#else /* LIBC: memxendq */
#include <local/string/memxendq.h>
/* Same as `memendq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxendq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memxendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxendq))(__haystack, __qword, __n_bytes); })
#endif /* memxendq... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memrxendq)
extern "C++" {
/* Same as `memrendq', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memrxendq,(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),memrxendq,(__haystack, __qword, __n_qwords))
/* Same as `memrendq', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ const *,__NOTHROW_NCX,memrxendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),memrxendq,(__haystack, __qword, __n_qwords))
}
#else /* LIBC: memrxendq */
#include <local/string/memrxendq.h>
extern "C++" {
/* Same as `memrendq', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendq)(void *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendq))(__haystack, __qword, __n_qwords); }
/* Same as `memrendq', but search for non-matching locations. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ const *__NOTHROW_NCX(__LIBCCALL memrxendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendq))(__haystack, __qword, __n_qwords); }
}
#endif /* memrxendq... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memrxendq)
/* Same as `memrendq', but search for non-matching locations. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memrxendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),(__haystack,__qword,__n_qwords))
#else /* LIBC: memrxendq */
#include <local/string/memrxendq.h>
/* Same as `memrendq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxendq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrxendq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxendq))(__haystack, __qword, __n_qwords); })
#endif /* memrxendq... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memxlenq)
/* Same as `memlenq', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memxlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),(__haystack,__qword,__n_qwords))
#else /* LIBC: memxlenq */
#include <local/string/memxlenq.h>
/* Same as `memlenq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memxlenq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memxlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxlenq))(__haystack, __qword, __n_qwords); })
#endif /* memxlenq... */
#if defined(__CRT_HAVE_memrxlenq)
/* Same as `memrlenq', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memrxlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords),(__haystack,__qword,__n_qwords))
#else /* LIBC: memrxlenq */
#include <local/string/memrxlenq.h>
/* Same as `memrlenq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrxlenq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memrxlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxlenq))(__haystack, __qword, __n_qwords); })
#endif /* memrxlenq... */
#if defined(__CRT_HAVE_rawmemxlenq)
/* Same as `rawmemlenq', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemxlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),(__haystack,__qword))
#else /* LIBC: rawmemxlenq */
#include <local/string/rawmemxlenq.h>
/* Same as `rawmemlenq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemxlenq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemxlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxlenq))(__haystack, __qword); })
#endif /* rawmemxlenq... */
#if defined(__CRT_HAVE_rawmemrxlenq)
/* Same as `rawmemrlenq', but search for non-matching locations. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemrxlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),(__haystack,__qword))
#else /* LIBC: rawmemrxlenq */
#include <local/string/rawmemrxlenq.h>
/* Same as `rawmemrlenq', but search for non-matching locations. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrxlenq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemrxlenq)(void const *__restrict __haystack, __UINT64_TYPE__ __qword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrxlenq))(__haystack, __qword); })
#endif /* rawmemrxlenq... */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */
#endif /* __USE_STRING_XCHR */





#ifdef __USE_KOS
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_strend)
extern "C++" {
/* Same as `STR+strlen(STR)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strend,(char *__restrict __string),strend,(__string))
/* Same as `STR+strlen(STR)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strend,(char const *__restrict __string),strend,(__string))
}
#else /* LIBC: strend */
#include <local/string/strend.h>
extern "C++" {
/* Same as `STR+strlen(STR)' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strend)(char *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strend))(__string); }
/* Same as `STR+strlen(STR)' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strend)(char const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strend))(__string); }
}
#endif /* strend... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_strend)
/* Same as `STR+strlen(STR)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strend,(char const *__restrict __string),(__string))
#else /* LIBC: strend */
#include <local/string/strend.h>
/* Same as `STR+strlen(STR)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strend, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strend)(char const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strend))(__string); })
#endif /* strend... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_strnend)
extern "C++" {
/* Same as `STR+strnlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnend,(char *__restrict __string, size_t __maxlen),strnend,(__string, __maxlen))
/* Same as `STR+strnlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strnend,(char const *__restrict __string, size_t __maxlen),strnend,(__string, __maxlen))
}
#else /* LIBC: strnend */
#include <local/string/strnend.h>
extern "C++" {
/* Same as `STR+strnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnend)(char *__restrict __string, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnend))(__string, __maxlen); }
/* Same as `STR+strnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strnend)(char const *__restrict __string, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnend))(__string, __maxlen); }
}
#endif /* strnend... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_strnend)
/* Same as `STR+strnlen(STR, MAX_CHARS)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnend,(char const *__restrict __string, size_t __maxlen),(__string,__maxlen))
#else /* LIBC: strnend */
#include <local/string/strnend.h>
/* Same as `STR+strnlen(STR, MAX_CHARS)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnend, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnend)(char const *__restrict __string, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnend))(__string, __maxlen); })
#endif /* strnend... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_strnchr)
extern "C++" {
/* Same as `strchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnchr,(char *__restrict __haystack, int __needle, size_t __maxlen),strnchr,(__haystack, __needle, __maxlen))
/* Same as `strchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strnchr,(char const *__restrict __haystack, int __needle, size_t __maxlen),strnchr,(__haystack, __needle, __maxlen))
}
#else /* LIBC: strnchr */
#include <local/string/strnchr.h>
extern "C++" {
/* Same as `strchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnchr)(char *__restrict __haystack, int __needle, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnchr))(__haystack, __needle, __maxlen); }
/* Same as `strchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strnchr)(char const *__restrict __haystack, int __needle, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnchr))(__haystack, __needle, __maxlen); }
}
#endif /* strnchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_strnchr)
/* Same as `strchr', but don't exceed `MAX_CHARS' characters. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnchr,(char const *__restrict __haystack, int __needle, size_t __maxlen),(__haystack,__needle,__maxlen))
#else /* LIBC: strnchr */
#include <local/string/strnchr.h>
/* Same as `strchr', but don't exceed `MAX_CHARS' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnchr, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnchr)(char const *__restrict __haystack, int __needle, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnchr))(__haystack, __needle, __maxlen); })
#endif /* strnchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_strnrchr)
extern "C++" {
/* Same as `strrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnrchr,(char *__restrict __haystack, int __needle, size_t __maxlen),strnrchr,(__haystack, __needle, __maxlen))
/* Same as `strrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strnrchr,(char const *__restrict __haystack, int __needle, size_t __maxlen),strnrchr,(__haystack, __needle, __maxlen))
}
#else /* LIBC: strnrchr */
#include <local/string/strnrchr.h>
extern "C++" {
/* Same as `strrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnrchr)(char *__restrict __haystack, int __needle, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchr))(__haystack, __needle, __maxlen); }
/* Same as `strrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strnrchr)(char const *__restrict __haystack, int __needle, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchr))(__haystack, __needle, __maxlen); }
}
#endif /* strnrchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_strnrchr)
/* Same as `strrchr', but don't exceed `MAX_CHARS' characters. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnrchr,(char const *__restrict __haystack, int __needle, size_t __maxlen),(__haystack,__needle,__maxlen))
#else /* LIBC: strnrchr */
#include <local/string/strnrchr.h>
/* Same as `strrchr', but don't exceed `MAX_CHARS' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnrchr, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnrchr)(char const *__restrict __haystack, int __needle, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchr))(__haystack, __needle, __maxlen); })
#endif /* strnrchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_strrchrnul)
extern "C++" {
/* Same as `strrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strrchrnul,(char *__restrict __haystack, int __needle),strrchrnul,(__haystack, __needle))
/* Same as `strrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strrchrnul,(char const *__restrict __haystack, int __needle),strrchrnul,(__haystack, __needle))
}
#else /* LIBC: strrchrnul */
#include <local/string/strrchrnul.h>
extern "C++" {
/* Same as `strrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strrchrnul)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchrnul))(__haystack, __needle); }
/* Same as `strrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strrchrnul)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchrnul))(__haystack, __needle); }
}
#endif /* strrchrnul... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_strrchrnul)
/* Same as `strrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strrchrnul,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* LIBC: strrchrnul */
#include <local/string/strrchrnul.h>
/* Same as `strrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strrchrnul, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strrchrnul)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchrnul))(__haystack, __needle); })
#endif /* strrchrnul... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_strnchrnul)
extern "C++" {
/* Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnchrnul,(char *__restrict __haystack, int __needle, size_t __maxlen),strnchrnul,(__haystack, __needle, __maxlen))
/* Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strnchrnul,(char const *__restrict __haystack, int __needle, size_t __maxlen),strnchrnul,(__haystack, __needle, __maxlen))
}
#else /* LIBC: strnchrnul */
#include <local/string/strnchrnul.h>
extern "C++" {
/* Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnchrnul)(char *__restrict __haystack, int __needle, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnchrnul))(__haystack, __needle, __maxlen); }
/* Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strnchrnul)(char const *__restrict __haystack, int __needle, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnchrnul))(__haystack, __needle, __maxlen); }
}
#endif /* strnchrnul... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_strnchrnul)
/* Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnchrnul,(char const *__restrict __haystack, int __needle, size_t __maxlen),(__haystack,__needle,__maxlen))
#else /* LIBC: strnchrnul */
#include <local/string/strnchrnul.h>
/* Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnchrnul, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnchrnul)(char const *__restrict __haystack, int __needle, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnchrnul))(__haystack, __needle, __maxlen); })
#endif /* strnchrnul... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_strnrchrnul)
extern "C++" {
/* Same as `strnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnrchrnul,(char *__restrict __haystack, int __needle, size_t __maxlen),strnrchrnul,(__haystack, __needle, __maxlen))
/* Same as `strnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,strnrchrnul,(char const *__restrict __haystack, int __needle, size_t __maxlen),strnrchrnul,(__haystack, __needle, __maxlen))
}
#else /* LIBC: strnrchrnul */
#include <local/string/strnrchrnul.h>
extern "C++" {
/* Same as `strnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnrchrnul)(char *__restrict __haystack, int __needle, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchrnul))(__haystack, __needle, __maxlen); }
/* Same as `strnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL strnrchrnul)(char const *__restrict __haystack, int __needle, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchrnul))(__haystack, __needle, __maxlen); }
}
#endif /* strnrchrnul... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_strnrchrnul)
/* Same as `strnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnrchrnul,(char const *__restrict __haystack, int __needle, size_t __maxlen),(__haystack,__needle,__maxlen))
#else /* LIBC: strnrchrnul */
#include <local/string/strnrchrnul.h>
/* Same as `strnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnrchrnul, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnrchrnul)(char const *__restrict __haystack, int __needle, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchrnul))(__haystack, __needle, __maxlen); })
#endif /* strnrchrnul... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_stroff)
/* Same as `strchrnul', but return the offset from `STR', rather than the actual address */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,stroff,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* LIBC: stroff */
#include <local/string/stroff.h>
/* Same as `strchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(stroff, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL stroff)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stroff))(__haystack, __needle); })
#endif /* stroff... */
#if defined(__CRT_HAVE_strroff)
/* Same as `strrchrnul', but return the offset from `STR', rather than the actual address */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,strroff,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* LIBC: strroff */
#include <local/string/strroff.h>
/* Same as `strrchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(strroff, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL strroff)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strroff))(__haystack, __needle); })
#endif /* strroff... */
#if defined(__CRT_HAVE_strnoff)
/* Same as `strnchrnul', but return the offset from `STR', rather than the actual address */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,strnoff,(char const *__restrict __haystack, int __needle, size_t __maxlen),(__haystack,__needle,__maxlen))
#else /* LIBC: strnoff */
#include <local/string/strnoff.h>
/* Same as `strnchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnoff, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL strnoff)(char const *__restrict __haystack, int __needle, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnoff))(__haystack, __needle, __maxlen); })
#endif /* strnoff... */
#if defined(__CRT_HAVE_strnroff)
/* Same as `strnrchrnul', but return the offset from `STR', rather than the actual address */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,strnroff,(char const *__restrict __haystack, int __needle, size_t __maxlen),(__haystack,__needle,__maxlen))
#else /* LIBC: strnroff */
#include <local/string/strnroff.h>
/* Same as `strnrchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnroff, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL strnroff)(char const *__restrict __haystack, int __needle, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnroff))(__haystack, __needle, __maxlen); })
#endif /* strnroff... */
#if defined(__fast_mempset_defined)
/* Same as `memset', but return `DST+N_BYTES', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempset)(void *__restrict __dst, int __byte, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempset))(__dst, __byte, __n_bytes); })
#elif defined(__CRT_HAVE_mempset)
/* Same as `memset', but return `DST+N_BYTES', rather than `DST' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempset,(void *__restrict __dst, int __byte, size_t __n_bytes),(__dst,__byte,__n_bytes))
#else /* LIBC: mempset */
#include <local/string/mempset.h>
/* Same as `memset', but return `DST+N_BYTES', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempset)(void *__restrict __dst, int __byte, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempset))(__dst, __byte, __n_bytes); })
#endif /* mempset... */
#if defined(__fast_mempmove_defined)
/* Same as `memmove', but return `DST+N_BYTES', rather than `DST' */
__NAMESPACE_FAST_USING_OR_IMPL(mempmove, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmove)(void *__dst, void const *__src, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmove))(__dst, __src, __n_bytes); })
#elif defined(__CRT_HAVE_mempmove)
/* Same as `memmove', but return `DST+N_BYTES', rather than `DST' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,mempmove,(void *__dst, void const *__src, size_t __n_bytes),(__dst,__src,__n_bytes))
#else /* LIBC: mempmove */
#include <local/string/mempmove.h>
/* Same as `memmove', but return `DST+N_BYTES', rather than `DST' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempmove, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL mempmove)(void *__dst, void const *__src, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmove))(__dst, __src, __n_bytes); })
#endif /* mempmove... */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_rawmemrchr)
extern "C++" {
/* Same as `memrchr' without a search limit, starting at `HAYSTACK-1' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemrchr,(void *__restrict __haystack, int __needle),rawmemrchr,(__haystack, __needle))
/* Same as `memrchr' without a search limit, starting at `HAYSTACK-1' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,rawmemrchr,(void const *__restrict __haystack, int __needle),rawmemrchr,(__haystack, __needle))
}
#else /* LIBC: rawmemrchr */
#include <local/string/rawmemrchr.h>
extern "C++" {
/* Same as `memrchr' without a search limit, starting at `HAYSTACK-1' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemrchr)(void *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchr))(__haystack, __needle); }
/* Same as `memrchr' without a search limit, starting at `HAYSTACK-1' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL rawmemrchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchr))(__haystack, __needle); }
}
#endif /* rawmemrchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_rawmemrchr)
/* Same as `memrchr' without a search limit, starting at `HAYSTACK-1' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,rawmemrchr,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* LIBC: rawmemrchr */
#include <local/string/rawmemrchr.h>
/* Same as `memrchr' without a search limit, starting at `HAYSTACK-1' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrchr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL rawmemrchr)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrchr))(__haystack, __needle); })
#endif /* rawmemrchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __fast_memend_defined
extern "C++" {
/* Same as `memchr', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memend)(void *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __needle, __n_bytes); }
/* Same as `memchr', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memend)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __needle, __n_bytes); }
}
#elif defined(__CRT_HAVE_memend)
extern "C++" {
/* Same as `memchr', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memend,(void *__restrict __haystack, int __needle, size_t __n_bytes),memend,(__haystack, __needle, __n_bytes))
/* Same as `memchr', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memend,(void const *__restrict __haystack, int __needle, size_t __n_bytes),memend,(__haystack, __needle, __n_bytes))
}
#else /* LIBC: memend */
#include <local/string/memend.h>
extern "C++" {
/* Same as `memchr', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memend)(void *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))(__haystack, __needle, __n_bytes); }
/* Same as `memchr', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memend)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))(__haystack, __needle, __n_bytes); }
}
#endif /* memend... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memend_defined)
/* Same as `memchr', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_FAST_USING_OR_IMPL(memend, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memend)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))(__haystack, __needle, __n_bytes); })
#elif defined(__CRT_HAVE_memend)
/* Same as `memchr', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memend,(void const *__restrict __haystack, int __needle, size_t __n_bytes),(__haystack,__needle,__n_bytes))
#else /* LIBC: memend */
#include <local/string/memend.h>
/* Same as `memchr', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memend, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memend)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))(__haystack, __needle, __n_bytes); })
#endif /* memend... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#ifdef __fast_memrend_defined
extern "C++" {
/* Same as `memrchr', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrend)(void *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __needle, __n_bytes); }
/* Same as `memrchr', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memrend)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __needle, __n_bytes); }
}
#elif defined(__CRT_HAVE_memrend)
extern "C++" {
/* Same as `memrchr', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrend,(void *__restrict __haystack, int __needle, size_t __n_bytes),memrend,(__haystack, __needle, __n_bytes))
/* Same as `memrchr', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void const *,__NOTHROW_NCX,memrend,(void const *__restrict __haystack, int __needle, size_t __n_bytes),memrend,(__haystack, __needle, __n_bytes))
}
#else /* LIBC: memrend */
#include <local/string/memrend.h>
extern "C++" {
/* Same as `memrchr', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrend)(void *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))(__haystack, __needle, __n_bytes); }
/* Same as `memrchr', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void const *__NOTHROW_NCX(__LIBCCALL memrend)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))(__haystack, __needle, __n_bytes); }
}
#endif /* memrend... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memrend_defined)
/* Same as `memrchr', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_FAST_USING_OR_IMPL(memrend, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrend)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))(__haystack, __needle, __n_bytes); })
#elif defined(__CRT_HAVE_memrend)
/* Same as `memrchr', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrend,(void const *__restrict __haystack, int __needle, size_t __n_bytes),(__haystack,__needle,__n_bytes))
#else /* LIBC: memrend */
#include <local/string/memrend.h>
/* Same as `memrchr', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrend, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrend)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))(__haystack, __needle, __n_bytes); })
#endif /* memrend... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__fast_memlen_defined)
/* Same as `memend', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_FAST_USING_OR_IMPL(memlen, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memlen)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memlen))(__haystack, __needle, __n_bytes); })
#elif defined(__CRT_HAVE_memlen)
/* Same as `memend', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memlen,(void const *__restrict __haystack, int __needle, size_t __n_bytes),(__haystack,__needle,__n_bytes))
#else /* LIBC: memlen */
#include <local/string/memlen.h>
/* Same as `memend', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memlen, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memlen)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlen))(__haystack, __needle, __n_bytes); })
#endif /* memlen... */
#if defined(__fast_memrlen_defined)
/* Same as `memrend', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_FAST_USING_OR_IMPL(memrlen, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memrlen)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrlen))(__haystack, __needle, __n_bytes); })
#elif defined(__CRT_HAVE_memrlen)
/* Same as `memrend', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,memrlen,(void const *__restrict __haystack, int __needle, size_t __n_bytes),(__haystack,__needle,__n_bytes))
#else /* LIBC: memrlen */
#include <local/string/memrlen.h>
/* Same as `memrend', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memrlen, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL memrlen)(void const *__restrict __haystack, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlen))(__haystack, __needle, __n_bytes); })
#endif /* memrlen... */
#if defined(__CRT_HAVE_rawmemlen)
/* Same as `rawmemchr', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemlen,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* LIBC: rawmemlen */
#include <local/string/rawmemlen.h>
/* Same as `rawmemchr', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemlen, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemlen)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemlen))(__haystack, __needle); })
#endif /* rawmemlen... */
#if defined(__CRT_HAVE_rawmemrlen)
/* Same as `rawmemrchr', but return the offset from `HAYSTACK', rather than the actual address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,rawmemrlen,(void const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* LIBC: rawmemrlen */
#include <local/string/rawmemrlen.h>
/* Same as `rawmemrchr', but return the offset from `HAYSTACK', rather than the actual address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rawmemrlen, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL rawmemrlen)(void const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrlen))(__haystack, __needle); })
#endif /* rawmemrlen... */
#if defined(__fast_memset_defined)
/* Same as `memsetb', but repeat a 1-byte pattern on aligned addresses. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatb)(void *__restrict __dst, int __pattern, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))(__dst, __pattern, __n_bytes); }
#elif defined(__CRT_HAVE_mempatb)
/* Same as `memsetb', but repeat a 1-byte pattern on aligned addresses. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempatb,(void *__restrict __dst, int __pattern, size_t __n_bytes),(__dst,__pattern,__n_bytes))
#elif defined(__CRT_HAVE_memset)
/* Same as `memsetb', but repeat a 1-byte pattern on aligned addresses. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempatb,(void *__restrict __dst, int __pattern, size_t __n_bytes),memset,(__dst,__pattern,__n_bytes))
#else /* LIBC: memset */
#include <local/string/memset.h>
/* Same as `memsetb', but repeat a 1-byte pattern on aligned addresses. */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatb)(void *__restrict __dst, int __pattern, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memset))(__dst, __pattern, __n_bytes); }
#endif /* mempatb... */
#if defined(__fast_mempatw_defined)
/* Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
__NAMESPACE_FAST_USING_OR_IMPL(mempatw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatw)(void *__restrict __dst, __UINT16_TYPE__ __pattern, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatw))(__dst, __pattern, __n_bytes); })
#elif defined(__CRT_HAVE_mempatw)
/* Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempatw,(void *__restrict __dst, __UINT16_TYPE__ __pattern, size_t __n_bytes),(__dst,__pattern,__n_bytes))
#else /* LIBC: mempatw */
#include <local/string/mempatw.h>
/* Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempatw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatw)(void *__restrict __dst, __UINT16_TYPE__ __pattern, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempatw))(__dst, __pattern, __n_bytes); })
#endif /* mempatw... */
#if defined(__fast_mempatl_defined)
/* Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
__NAMESPACE_FAST_USING_OR_IMPL(mempatl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatl)(void *__restrict __dst, __UINT32_TYPE__ __pattern, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatl))(__dst, __pattern, __n_bytes); })
#elif defined(__CRT_HAVE_mempatl)
/* Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempatl,(void *__restrict __dst, __UINT32_TYPE__ __pattern, size_t __n_bytes),(__dst,__pattern,__n_bytes))
#else /* LIBC: mempatl */
#include <local/string/mempatl.h>
/* Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempatl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatl)(void *__restrict __dst, __UINT32_TYPE__ __pattern, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempatl))(__dst, __pattern, __n_bytes); })
#endif /* mempatl... */
#ifdef __UINT64_TYPE__
#if defined(__fast_mempatq_defined)
/* Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
__NAMESPACE_FAST_USING_OR_IMPL(mempatq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatq)(void *__restrict __dst, __UINT64_TYPE__ __pattern, size_t __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatq))(__dst, __pattern, __n_bytes); })
#elif defined(__CRT_HAVE_mempatq)
/* Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,mempatq,(void *__restrict __dst, __UINT64_TYPE__ __pattern, size_t __n_bytes),(__dst,__pattern,__n_bytes))
#else /* LIBC: mempatq */
#include <local/string/mempatq.h>
/* Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
__NAMESPACE_LOCAL_USING_OR_IMPL(mempatq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL mempatq)(void *__restrict __dst, __UINT64_TYPE__ __pattern, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempatq))(__dst, __pattern, __n_bytes); })
#endif /* mempatq... */
#endif /* __UINT64_TYPE__ */
#if defined(__CRT_HAVE_memcasecmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcasecmp,(void const *__s1, void const *__s2, size_t __n_bytes),(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_memicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcasecmp,(void const *__s1, void const *__s2, size_t __n_bytes),memicmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE__memicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcasecmp,(void const *__s1, void const *__s2, size_t __n_bytes),_memicmp,(__s1,__s2,__n_bytes))
#else /* LIBC: memcasecmp */
#include <local/string/memcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memcasecmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memcasecmp)(void const *__s1, void const *__s2, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp))(__s1, __s2, __n_bytes); })
#endif /* memcasecmp... */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memcasemem)
extern "C++" {
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem,(void *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen),memcasemem,(__haystack, __haystacklen, __needle, __needlelen))
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memcasemem,(void const *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen),memcasemem,(__haystack, __haystacklen, __needle, __needlelen))
}
#elif defined(__CRT_HAVE__memicmp_l)
extern "C++" {
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem,(void *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen),_memicmp_l,(__haystack, __haystacklen, __needle, __needlelen))
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memcasemem,(void const *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen),_memicmp_l,(__haystack, __haystacklen, __needle, __needlelen))
}
#else /* LIBC: memcasemem */
#include <local/string/memcasemem.h>
extern "C++" {
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memcasemem)(void *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasemem))(__haystack, __haystacklen, __needle, __needlelen); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) void const *__NOTHROW_NCX(__LIBCCALL memcasemem)(void const *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasemem))(__haystack, __haystacklen, __needle, __needlelen); }
}
#endif /* memcasemem... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memcasemem)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem,(void const *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen),(__haystack,__haystacklen,__needle,__needlelen))
#elif defined(__CRT_HAVE__memicmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem,(void const *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen),_memicmp_l,(__haystack,__haystacklen,__needle,__needlelen))
#else /* LIBC: memcasemem */
#include <local/string/memcasemem.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memcasemem, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memcasemem)(void const *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasemem))(__haystack, __haystacklen, __needle, __needlelen); })
#endif /* memcasemem... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_memcasecmp_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcasecmp_l,(void const *__s1, void const *__s2, size_t __n_bytes, __locale_t __locale),(__s1,__s2,__n_bytes,__locale))
#elif defined(__CRT_HAVE__memicmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memcasecmp_l,(void const *__s1, void const *__s2, size_t __n_bytes, __locale_t __locale),_memicmp_l,(__s1,__s2,__n_bytes,__locale))
#else /* LIBC: memcasecmp_l */
#include <local/string/memcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memcasecmp_l, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memcasecmp_l)(void const *__s1, void const *__s2, size_t __n_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp_l))(__s1, __s2, __n_bytes, __locale); })
#endif /* memcasecmp_l... */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_memcasemem_l)
extern "C++" {
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem_l,(void *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen, __locale_t __locale),memcasemem_l,(__haystack, __haystacklen, __needle, __needlelen, __locale))
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memcasemem_l,(void const *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen, __locale_t __locale),memcasemem_l,(__haystack, __haystacklen, __needle, __needlelen, __locale))
}
#elif defined(__CRT_HAVE__memicmp_l)
extern "C++" {
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem_l,(void *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen, __locale_t __locale),_memicmp_l,(__haystack, __haystacklen, __needle, __needlelen, __locale))
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),void const *,__NOTHROW_NCX,memcasemem_l,(void const *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen, __locale_t __locale),_memicmp_l,(__haystack, __haystacklen, __needle, __needlelen, __locale))
}
#else /* LIBC: memcasemem_l */
#include <local/string/memcasemem_l.h>
extern "C++" {
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memcasemem_l)(void *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasemem_l))(__haystack, __haystacklen, __needle, __needlelen, __locale); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) void const *__NOTHROW_NCX(__LIBCCALL memcasemem_l)(void const *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasemem_l))(__haystack, __haystacklen, __needle, __needlelen, __locale); }
}
#endif /* memcasemem_l... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_memcasemem_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem_l,(void const *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen, __locale_t __locale),(__haystack,__haystacklen,__needle,__needlelen,__locale))
#elif defined(__CRT_HAVE__memicmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,memcasemem_l,(void const *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen, __locale_t __locale),_memicmp_l,(__haystack,__haystacklen,__needle,__needlelen,__locale))
#else /* LIBC: memcasemem_l */
#include <local/string/memcasemem_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memcasemem_l, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) void *__NOTHROW_NCX(__LIBCCALL memcasemem_l)(void const *__haystack, size_t __haystacklen, void const *__needle, size_t __needlelen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasemem_l))(__haystack, __haystacklen, __needle, __needlelen, __locale); })
#endif /* memcasemem_l... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
#if defined(__CRT_HAVE_strcasestr_l)
extern "C++" {
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strcasestr_l,(char *__haystack, char const *__needle, __locale_t __locale),strcasestr_l,(__haystack, __needle, __locale))
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),char const *,__NOTHROW_NCX,strcasestr_l,(char const *__haystack, char const *__needle, __locale_t __locale),strcasestr_l,(__haystack, __needle, __locale))
}
#else /* LIBC: strcasestr_l */
#include <local/string/strcasestr_l.h>
extern "C++" {
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strcasestr_l)(char *__haystack, char const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasestr_l))(__haystack, __needle, __locale); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) char const *__NOTHROW_NCX(__LIBCCALL strcasestr_l)(char const *__haystack, char const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasestr_l))(__haystack, __needle, __locale); }
}
#endif /* strcasestr_l... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
#if defined(__CRT_HAVE_strcasestr_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,strcasestr_l,(char const *__haystack, char const *__needle, __locale_t __locale),(__haystack,__needle,__locale))
#else /* LIBC: strcasestr_l */
#include <local/string/strcasestr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasestr_l, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL strcasestr_l)(char const *__haystack, char const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasestr_l))(__haystack, __needle, __locale); })
#endif /* strcasestr_l... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* __USE_XOPEN2K8 */



#if defined(__CRT_HAVE_strerror_s)
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST,char const *,__NOTHROW,strerror_s,(int __errnum),(__errnum))
#else /* LIBC: strerror_s */
#include <local/string/strerror_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strerror_s, __FORCELOCAL __ATTR_WUNUSED __ATTR_CONST char const *__NOTHROW(__LIBCCALL strerror_s)(int __errnum) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strerror_s))(__errnum); })
#endif /* strerror_s... */
#if defined(__CRT_HAVE_strerrorname_s)
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST,char const *,__NOTHROW,strerrorname_s,(int __errnum),(__errnum))
#else /* LIBC: strerrorname_s */
#include <local/string/strerrorname_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strerrorname_s, __FORCELOCAL __ATTR_WUNUSED __ATTR_CONST char const *__NOTHROW(__LIBCCALL strerrorname_s)(int __errnum) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strerrorname_s))(__errnum); })
#endif /* strerrorname_s... */
#if defined(__CRT_HAVE_strsignal_s)
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST,char const *,__NOTHROW,strsignal_s,(int __signum),(__signum))
#else /* LIBC: strsignal_s */
#include <local/string/strsignal_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strsignal_s, __FORCELOCAL __ATTR_WUNUSED __ATTR_CONST char const *__NOTHROW(__LIBCCALL strsignal_s)(int __signum) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strsignal_s))(__signum); })
#endif /* strsignal_s... */
#if defined(__CRT_HAVE_vstrdupf)
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
__CDECLARE(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_LIBC_PRINTF(1, 0),char *,__NOTHROW_NCX,vstrdupf,(char const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif (((__has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_format_aprintf_pack)) && ((__has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_format_aprintf_printer)) && ((__has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)) || defined(__CRT_HAVE_vasprintf))
#include <local/string/vstrdupf.h>
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
__NAMESPACE_LOCAL_USING_OR_IMPL(vstrdupf, __FORCELOCAL __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_LIBC_PRINTF(1, 0) char *__NOTHROW_NCX(__LIBCCALL vstrdupf)(char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vstrdupf))(__format, __args); })
#endif /* vstrdupf... */
#if defined(__CRT_HAVE_strdupf)
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
__LIBC __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_LIBC_PRINTF(1, 0) char *__NOTHROW_NCX(__VLIBCCALL strdupf)(char const *__restrict __format, ...) __CASMNAME_SAME("strdupf");
#elif (((__has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_format_aprintf_pack)) && ((__has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_format_aprintf_printer)) && ((__has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)) || defined(__CRT_HAVE_vasprintf)) || defined(__CRT_HAVE_vstrdupf)
#include <local/string/strdupf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(strdupf)
#else /* __cplusplus */
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
#define strdupf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strdupf))
#endif /* !__cplusplus */
#endif /* strdupf... */
#if defined(__CRT_HAVE_wildstrcmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildstrcmp,(char const *__pattern, char const *__string),(__pattern,__string))
#else /* LIBC: wildstrcmp */
#include <local/string/wildstrcmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildstrcmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildstrcmp)(char const *__pattern, char const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildstrcmp))(__pattern, __string); })
#endif /* wildstrcmp... */
#if defined(__CRT_HAVE_wildstrcasecmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildstrcasecmp,(char const *__pattern, char const *__string),(__pattern,__string))
#else /* LIBC: wildstrcasecmp */
#include <local/string/wildstrcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildstrcasecmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildstrcasecmp)(char const *__pattern, char const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildstrcasecmp))(__pattern, __string); })
#endif /* wildstrcasecmp... */
#if defined(__CRT_HAVE_fuzzy_strcmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,fuzzy_strcmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_memcmp)
#include <local/string/fuzzy_strcmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_strcmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL fuzzy_strcmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_strcmp))(__s1, __s2); })
#endif /* fuzzy_strcmp... */
#if defined(__CRT_HAVE_fuzzy_strncmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),size_t,__NOTHROW_NCX,fuzzy_strncmp,(char const *__s1, size_t __s1_maxlen, char const *__s2, size_t __s2_maxlen),(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_memcmp)
#include <local/string/fuzzy_strncmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_strncmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) size_t __NOTHROW_NCX(__LIBCCALL fuzzy_strncmp)(char const *__s1, size_t __s1_maxlen, char const *__s2, size_t __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_strncmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* fuzzy_strncmp... */
#if defined(__CRT_HAVE_fuzzy_strcasecmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,fuzzy_strcasecmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_memcasecmp)
#include <local/string/fuzzy_strcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_strcasecmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL fuzzy_strcasecmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_strcasecmp))(__s1, __s2); })
#endif /* fuzzy_strcasecmp... */
#if defined(__CRT_HAVE_fuzzy_strncasecmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),size_t,__NOTHROW_NCX,fuzzy_strncasecmp,(char const *__s1, size_t __s1_maxlen, char const *__s2, size_t __s2_maxlen),(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_memcasecmp)
#include <local/string/fuzzy_strncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_strncasecmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) size_t __NOTHROW_NCX(__LIBCCALL fuzzy_strncasecmp)(char const *__s1, size_t __s1_maxlen, char const *__s2, size_t __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_strncasecmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* fuzzy_strncasecmp... */
#if defined(__CRT_HAVE_fuzzy_memcmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),size_t,__NOTHROW_NCX,fuzzy_memcmp,(void const *__s1, size_t __s1_bytes, void const *__s2, size_t __s2_bytes),(__s1,__s1_bytes,__s2,__s2_bytes))
#elif !defined(__NO_MALLOCA)
#include <local/string/fuzzy_memcmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_memcmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) size_t __NOTHROW_NCX(__LIBCCALL fuzzy_memcmp)(void const *__s1, size_t __s1_bytes, void const *__s2, size_t __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmp))(__s1, __s1_bytes, __s2, __s2_bytes); })
#endif /* fuzzy_memcmp... */
#if defined(__CRT_HAVE_fuzzy_memcasecmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),size_t,__NOTHROW_NCX,fuzzy_memcasecmp,(void const *__s1, size_t __s1_bytes, void const *__s2, size_t __s2_bytes),(__s1,__s1_bytes,__s2,__s2_bytes))
#elif !defined(__NO_MALLOCA)
#include <local/string/fuzzy_memcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_memcasecmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) size_t __NOTHROW_NCX(__LIBCCALL fuzzy_memcasecmp)(void const *__s1, size_t __s1_bytes, void const *__s2, size_t __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcasecmp))(__s1, __s1_bytes, __s2, __s2_bytes); })
#endif /* fuzzy_memcasecmp... */
#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_fuzzy_strcasecmp_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,fuzzy_strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif !defined(__NO_MALLOCA)
#include <local/string/fuzzy_strcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_strcasecmp_l, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL fuzzy_strcasecmp_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_strcasecmp_l))(__s1, __s2, __locale); })
#endif /* fuzzy_strcasecmp_l... */
#if defined(__CRT_HAVE_fuzzy_strncasecmp_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),size_t,__NOTHROW_NCX,fuzzy_strncasecmp_l,(char const *__s1, size_t __s1_maxlen, char const *__s2, size_t __s2_maxlen, __locale_t __locale),(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#elif !defined(__NO_MALLOCA)
#include <local/string/fuzzy_strncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_strncasecmp_l, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) size_t __NOTHROW_NCX(__LIBCCALL fuzzy_strncasecmp_l)(char const *__s1, size_t __s1_maxlen, char const *__s2, size_t __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_strncasecmp_l))(__s1, __s1_maxlen, __s2, __s2_maxlen, __locale); })
#endif /* fuzzy_strncasecmp_l... */
#if defined(__CRT_HAVE_wildstrcasecmp_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildstrcasecmp_l,(char const *__pattern, char const *__string, __locale_t __locale),(__pattern,__string,__locale))
#else /* LIBC: wildstrcasecmp_l */
#include <local/string/wildstrcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildstrcasecmp_l, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildstrcasecmp_l)(char const *__pattern, char const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildstrcasecmp_l))(__pattern, __string, __locale); })
#endif /* wildstrcasecmp_l... */
#if defined(__CRT_HAVE_fuzzy_memcasecmp_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),size_t,__NOTHROW_NCX,fuzzy_memcasecmp_l,(void const *__s1, size_t __s1_bytes, void const *__s2, size_t __s2_bytes, __locale_t __locale),(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif !defined(__NO_MALLOCA)
#include <local/string/fuzzy_memcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_memcasecmp_l, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) size_t __NOTHROW_NCX(__LIBCCALL fuzzy_memcasecmp_l)(void const *__s1, size_t __s1_bytes, void const *__s2, size_t __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcasecmp_l))(__s1, __s1_bytes, __s2, __s2_bytes, __locale); })
#endif /* fuzzy_memcasecmp_l... */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_STRING_BWLQ
#if defined(__CRT_HAVE_fuzzy_memcmpb)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),size_t,__NOTHROW_NCX,fuzzy_memcmpb,(void const *__s1, size_t __s1_bytes, void const *__s2, size_t __s2_bytes),(__s1,__s1_bytes,__s2,__s2_bytes))
#elif defined(__CRT_HAVE_fuzzy_memcmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),size_t,__NOTHROW_NCX,fuzzy_memcmpb,(void const *__s1, size_t __s1_bytes, void const *__s2, size_t __s2_bytes),fuzzy_memcmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif !defined(__NO_MALLOCA)
#include <local/string/fuzzy_memcmp.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) size_t __NOTHROW_NCX(__LIBCCALL fuzzy_memcmpb)(void const *__s1, size_t __s1_bytes, void const *__s2, size_t __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmp))(__s1, __s1_bytes, __s2, __s2_bytes); }
#endif /* fuzzy_memcmpb... */
#if defined(__CRT_HAVE_fuzzy_memcmpw)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),size_t,__NOTHROW_NCX,fuzzy_memcmpw,(void const *__s1, size_t __s1_words, void const *__s2, size_t __s2_words),(__s1,__s1_words,__s2,__s2_words))
#elif !defined(__NO_MALLOCA)
#include <local/string/fuzzy_memcmpw.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_memcmpw, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) size_t __NOTHROW_NCX(__LIBCCALL fuzzy_memcmpw)(void const *__s1, size_t __s1_words, void const *__s2, size_t __s2_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpw))(__s1, __s1_words, __s2, __s2_words); })
#endif /* fuzzy_memcmpw... */
#if defined(__CRT_HAVE_fuzzy_memcmpl)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),size_t,__NOTHROW_NCX,fuzzy_memcmpl,(void const *__s1, size_t __s1_dwords, void const *__s2, size_t __s2_dwords),(__s1,__s1_dwords,__s2,__s2_dwords))
#elif !defined(__NO_MALLOCA)
#include <local/string/fuzzy_memcmpl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_memcmpl, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) size_t __NOTHROW_NCX(__LIBCCALL fuzzy_memcmpl)(void const *__s1, size_t __s1_dwords, void const *__s2, size_t __s2_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpl))(__s1, __s1_dwords, __s2, __s2_dwords); })
#endif /* fuzzy_memcmpl... */
#ifdef __UINT64_TYPE__
#if defined(__CRT_HAVE_fuzzy_memcmpq)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),size_t,__NOTHROW_NCX,fuzzy_memcmpq,(void const *__s1, size_t __s1_qwords, void const *__s2, size_t __s2_qwords),(__s1,__s1_qwords,__s2,__s2_qwords))
#elif !defined(__NO_MALLOCA)
#include <local/string/fuzzy_memcmpq.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_memcmpq, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)) size_t __NOTHROW_NCX(__LIBCCALL fuzzy_memcmpq)(void const *__s1, size_t __s1_qwords, void const *__s2, size_t __s2_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpq))(__s1, __s1_qwords, __s2, __s2_qwords); })
#endif /* fuzzy_memcmpq... */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */
#if defined(__CRT_HAVE_strncoll)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncoll,(char const *__s1, char const *__s2, size_t __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncoll)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncoll,(char const *__s1, char const *__s2, size_t __maxlen),_strncoll,(__s1,__s2,__maxlen))
#else /* LIBC: strncoll */
#include <local/string/strncoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncoll, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncoll)(char const *__s1, char const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncoll))(__s1, __s2, __maxlen); })
#endif /* strncoll... */
#if defined(__CRT_HAVE_strcasecoll)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE__stricoll)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),_stricoll,(__s1,__s2))
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecoll,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#else /* LIBC: strcasecoll */
#include <local/string/strcasecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasecoll, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcasecoll)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecoll))(__s1, __s2); })
#endif /* strcasecoll... */
#if defined(__CRT_HAVE_strncasecoll)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll,(char const *__s1, char const *__s2, size_t __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicoll)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll,(char const *__s1, char const *__s2, size_t __maxlen),_strnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll,(char const *__s1, char const *__s2, size_t __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#else /* LIBC: strncasecoll */
#include <local/string/strncasecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncasecoll, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncasecoll)(char const *__s1, char const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecoll))(__s1, __s2, __maxlen); })
#endif /* strncasecoll... */
#if defined(__CRT_HAVE_strnrev)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnrev,(char *__restrict __str, size_t __maxlen),(__str,__maxlen))
#else /* LIBC: strnrev */
#include <local/string/strnrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnrev, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnrev)(char *__restrict __str, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrev))(__str, __maxlen); })
#endif /* strnrev... */
#if defined(__CRT_HAVE_strnlwr)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnlwr,(char *__restrict __str, size_t __maxlen),(__str,__maxlen))
#else /* LIBC: strnlwr */
#include <local/string/strnlwr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnlwr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnlwr)(char *__restrict __str, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnlwr))(__str, __maxlen); })
#endif /* strnlwr... */
#if defined(__CRT_HAVE_strnupr)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnupr,(char *__restrict __str, size_t __maxlen),(__str,__maxlen))
#else /* LIBC: strnupr */
#include <local/string/strnupr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnupr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnupr)(char *__restrict __str, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnupr))(__str, __maxlen); })
#endif /* strnupr... */
#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_strncoll_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncoll_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncoll_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncoll_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),_strncoll_l,(__s1,__s2,__maxlen,__locale))
#else /* LIBC: strncoll_l */
#include <local/string/strncoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncoll_l, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncoll_l)(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* strncoll_l... */
#if defined(__CRT_HAVE_strcasecoll_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecoll_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__stricoll_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecoll_l,(char const *__s1, char const *__s2, __locale_t __locale),_stricoll_l,(__s1,__s2,__locale))
#else /* LIBC: strcasecoll_l */
#include <local/string/strcasecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasecoll_l, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcasecoll_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecoll_l))(__s1, __s2, __locale); })
#endif /* strcasecoll_l... */
#if defined(__CRT_HAVE_strncasecoll_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicoll_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),_strnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_strncasecmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),_strnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncmpi_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecoll_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),_strncmpi_l,(__s1,__s2,__maxlen,__locale))
#else /* LIBC: strncasecoll_l */
#include <local/string/strncasecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncasecoll_l, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncasecoll_l)(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* strncasecoll_l... */
#if defined(__CRT_HAVE_strlwr_l)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strlwr_l,(char *__restrict __str, __locale_t __locale),(__str,__locale))
#elif defined(__CRT_HAVE__strlwr_l)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strlwr_l,(char *__restrict __str, __locale_t __locale),_strlwr_l,(__str,__locale))
#else /* LIBC: strlwr_l */
#include <local/string/strlwr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strlwr_l, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strlwr_l)(char *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlwr_l))(__str, __locale); })
#endif /* strlwr_l... */
#if defined(__CRT_HAVE_strupr_l)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strupr_l,(char *__restrict __str, __locale_t __locale),(__str,__locale))
#elif defined(__CRT_HAVE__strupr_l)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strupr_l,(char *__restrict __str, __locale_t __locale),_strupr_l,(__str,__locale))
#else /* LIBC: strupr_l */
#include <local/string/strupr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strupr_l, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strupr_l)(char *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strupr_l))(__str, __locale); })
#endif /* strupr_l... */
#if defined(__CRT_HAVE_strnlwr_l)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnlwr_l,(char *__restrict __str, size_t __maxlen, __locale_t __locale),(__str,__maxlen,__locale))
#else /* LIBC: strnlwr_l */
#include <local/string/strnlwr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnlwr_l, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnlwr_l)(char *__restrict __str, size_t __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnlwr_l))(__str, __maxlen, __locale); })
#endif /* strnlwr_l... */
#if defined(__CRT_HAVE_strnupr_l)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnupr_l,(char *__restrict __str, size_t __maxlen, __locale_t __locale),(__str,__maxlen,__locale))
#else /* LIBC: strnupr_l */
#include <local/string/strnupr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnupr_l, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnupr_l)(char *__restrict __str, size_t __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnupr_l))(__str, __maxlen, __locale); })
#endif /* strnupr_l... */
#if defined(__CRT_HAVE_memrev)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,memrev,(void *__restrict __base, size_t __n_bytes),(__base,__n_bytes))
#else /* LIBC: memrev */
#include <local/string/memrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memrev, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL memrev)(void *__restrict __base, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrev))(__base, __n_bytes); })
#endif /* memrev... */
#endif /* __USE_XOPEN2K8 */
#ifdef __USE_STRING_BWLQ
#if defined(__CRT_HAVE_memrevb)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrevb,(void *__restrict __base, size_t __n_bytes),(__base,__n_bytes))
#elif defined(__CRT_HAVE_memrev)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT8_TYPE__ *,__NOTHROW_NCX,memrevb,(void *__restrict __base, size_t __n_bytes),memrev,(__base,__n_bytes))
#else /* LIBC: memrev */
#include <local/string/memrev.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT8_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrevb)(void *__restrict __base, size_t __n_bytes) { return (__UINT8_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrev))(__base, __n_bytes); }
#endif /* memrevb... */
#if defined(__CRT_HAVE_memrevw)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,memrevw,(void *__restrict __base, size_t __n_words),(__base,__n_words))
#else /* LIBC: memrevw */
#include <local/string/memrevw.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memrevw, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT16_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrevw)(void *__restrict __base, size_t __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrevw))(__base, __n_words); })
#endif /* memrevw... */
#if defined(__CRT_HAVE_memrevl)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,memrevl,(void *__restrict __base, size_t __n_dwords),(__base,__n_dwords))
#else /* LIBC: memrevl */
#include <local/string/memrevl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memrevl, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT32_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrevl)(void *__restrict __base, size_t __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrevl))(__base, __n_dwords); })
#endif /* memrevl... */
#ifdef __UINT64_TYPE__
#if defined(__CRT_HAVE_memrevq)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,memrevq,(void *__restrict __base, size_t __n_qwords),(__base,__n_qwords))
#else /* LIBC: memrevq */
#include <local/string/memrevq.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memrevq, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT64_TYPE__ *__NOTHROW_NCX(__LIBCCALL memrevq)(void *__restrict __base, size_t __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrevq))(__base, __n_qwords); })
#endif /* memrevq... */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */
#endif /* __USE_KOS */


#if defined(__USE_KOS) || defined(__USE_DOS)
#if defined(__CRT_HAVE_strlwr)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strlwr,(char *__restrict __str),(__str))
#elif defined(__CRT_HAVE__strlwr)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strlwr,(char *__restrict __str),_strlwr,(__str))
#else /* LIBC: strlwr */
#include <local/string/strlwr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strlwr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strlwr)(char *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlwr))(__str); })
#endif /* strlwr... */
#if defined(__CRT_HAVE_strupr)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strupr,(char *__restrict __str),(__str))
#elif defined(__CRT_HAVE__strupr)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strupr,(char *__restrict __str),_strupr,(__str))
#else /* LIBC: strupr */
#include <local/string/strupr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strupr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strupr)(char *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strupr))(__str); })
#endif /* strupr... */
#if defined(__CRT_HAVE_strset)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strset,(char *__restrict __str, int __ch),(__str,__ch))
#elif defined(__CRT_HAVE__strset)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strset,(char *__restrict __str, int __ch),_strset,(__str,__ch))
#else /* LIBC: strset */
#include <local/string/strset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strset)(char *__restrict __str, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strset))(__str, __ch); })
#endif /* strset... */
#if defined(__CRT_HAVE_strnset)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnset,(char *__restrict __str, int __ch, size_t __maxlen),(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE__strnset)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strnset,(char *__restrict __str, int __ch, size_t __maxlen),_strnset,(__str,__ch,__maxlen))
#else /* LIBC: strnset */
#include <local/string/strnset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strnset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strnset)(char *__restrict __str, int __ch, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnset))(__str, __ch, __maxlen); })
#endif /* strnset... */
#if defined(__CRT_HAVE_strrev)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strrev,(char *__restrict __str),(__str))
#elif defined(__CRT_HAVE__strrev)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,strrev,(char *__restrict __str),_strrev,(__str))
#else /* LIBC: strrev */
#include <local/string/strrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strrev, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL strrev)(char *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrev))(__str); })
#endif /* strrev... */
#endif /* __USE_KOS || __USE_DOS */


#ifdef __USE_DOS
#if defined(__CRT_HAVE_memccpy)
__CREDIRECT(__ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,_memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, size_t __num_bytes),memccpy,(__dst,__src,__needle,__num_bytes))
#elif defined(__CRT_HAVE__memccpy)
__CDECLARE(__ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,_memccpy,(void *__restrict __dst, void const *__restrict __src, int __needle, size_t __num_bytes),(__dst,__src,__needle,__num_bytes))
#else /* LIBC: memccpy */
#include <local/string/memccpy.h>
__FORCELOCAL __ATTR_NONNULL((1, 2)) void *__NOTHROW_NCX(__LIBCCALL _memccpy)(void *__restrict __dst, void const *__restrict __src, int __needle, size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memccpy))(__dst, __src, __needle, __num_bytes); }
#endif /* _memccpy... */
#if defined(__CRT_HAVE_memcasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp,(void const *__s1, void const *__s2, size_t __n_bytes),memcasecmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_memicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp,(void const *__s1, void const *__s2, size_t __n_bytes),memicmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE__memicmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp,(void const *__s1, void const *__s2, size_t __n_bytes),(__s1,__s2,__n_bytes))
#else /* LIBC: memcasecmp */
#include <local/string/memcasecmp.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _memicmp)(void const *__s1, void const *__s2, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp))(__s1, __s2, __n_bytes); }
#endif /* _memicmp... */
#if defined(__CRT_HAVE_memcasecmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp_l,(void const *__s1, void const *__s2, size_t __n_bytes, __locale_t __locale),memcasecmp_l,(__s1,__s2,__n_bytes,__locale))
#elif defined(__CRT_HAVE__memicmp_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_memicmp_l,(void const *__s1, void const *__s2, size_t __n_bytes, __locale_t __locale),(__s1,__s2,__n_bytes,__locale))
#else /* LIBC: memcasecmp_l */
#include <local/string/memcasecmp_l.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _memicmp_l)(void const *__s1, void const *__s2, size_t __n_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp_l))(__s1, __s2, __n_bytes, __locale); }
#endif /* _memicmp_l... */
#if defined(__CRT_HAVE_memcasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memicmp,(void const *__s1, void const *__s2, size_t __n_bytes),memcasecmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_memicmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memicmp,(void const *__s1, void const *__s2, size_t __n_bytes),(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE__memicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,memicmp,(void const *__s1, void const *__s2, size_t __n_bytes),_memicmp,(__s1,__s2,__n_bytes))
#else /* LIBC: memcasecmp */
#include <local/string/memcasecmp.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL memicmp)(void const *__s1, void const *__s2, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcasecmp))(__s1, __s2, __n_bytes); }
#endif /* memicmp... */
#if defined(__CRT_HAVE__strset_s)
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,_strset_s,(char *__dst, size_t __dstsize, int __ch),(__dst,__dstsize,__ch))
#else /* LIBC: _strset_s */
#include <local/string/_strset_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strset_s, __FORCELOCAL __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBCCALL _strset_s)(char *__dst, size_t __dstsize, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strset_s))(__dst, __dstsize, __ch); })
#endif /* _strset_s... */

#ifdef __USE_DOS_SLIB
#if defined(__CRT_HAVE_memcpy_s)
__CDECLARE(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,memcpy_s,(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength),(__dst,__dstlength,__src,__srclength))
#else /* LIBC: memcpy_s */
#include <local/string/memcpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpy_s, __FORCELOCAL __ATTR_NONNULL((1, 3)) __errno_t __NOTHROW_NCX(__LIBCCALL memcpy_s)(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy_s))(__dst, __dstlength, __src, __srclength); })
#endif /* memcpy_s... */
#if defined(__CRT_HAVE_memmove_s)
__CDECLARE(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,memmove_s,(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength),(__dst,__dstlength,__src,__srclength))
#else /* LIBC: memmove_s */
#include <local/string/memmove_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memmove_s, __FORCELOCAL __ATTR_NONNULL((1, 3)) __errno_t __NOTHROW_NCX(__LIBCCALL memmove_s)(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmove_s))(__dst, __dstlength, __src, __srclength); })
#endif /* memmove_s... */
#if defined(__CRT_HAVE_strcpy_s)
__CDECLARE(,__errno_t,__NOTHROW_NCX,strcpy_s,(char *__dst, size_t __dstsize, char const *__src),(__dst,__dstsize,__src))
#else /* LIBC: strcpy_s */
#include <local/string/strcpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcpy_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL strcpy_s)(char *__dst, size_t __dstsize, char const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcpy_s))(__dst, __dstsize, __src); })
#endif /* strcpy_s... */
#if defined(__CRT_HAVE_strcat_s)
__CDECLARE(,__errno_t,__NOTHROW_NCX,strcat_s,(char *__dst, size_t __dstsize, char const *__src),(__dst,__dstsize,__src))
#else /* LIBC: strcat_s */
#include <local/string/strcat_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcat_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL strcat_s)(char *__dst, size_t __dstsize, char const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcat_s))(__dst, __dstsize, __src); })
#endif /* strcat_s... */
__LOCAL __ATTR_WUNUSED __ATTR_PURE
size_t __NOTHROW_NCX(__LIBCCALL strnlen_s)(char const *__str, size_t __maxlen) {
	return __str ? strnlen(__str, __maxlen) : 0;
}
#if defined(__CRT_HAVE_strncat_s)
__CDECLARE(,__errno_t,__NOTHROW_NCX,strncat_s,(char *__dst, rsize_t __dstsize, const char *__src, rsize_t __maxlen),(__dst,__dstsize,__src,__maxlen))
#else /* LIBC: strncat_s */
#include <local/string/strncat_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncat_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL strncat_s)(char *__dst, rsize_t __dstsize, const char *__src, rsize_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncat_s))(__dst, __dstsize, __src, __maxlen); })
#endif /* strncat_s... */
#if defined(__CRT_HAVE_strncpy_s)
__CDECLARE(,__errno_t,__NOTHROW_NCX,strncpy_s,(char *__dst, size_t __dstsize, char const *__src, size_t __maxlen),(__dst,__dstsize,__src,__maxlen))
#else /* LIBC: strncpy_s */
#include <local/string/strncpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncpy_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL strncpy_s)(char *__dst, size_t __dstsize, char const *__src, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncpy_s))(__dst, __dstsize, __src, __maxlen); })
#endif /* strncpy_s... */
#if defined(__CRT_HAVE_strtok_r)
__CREDIRECT(__ATTR_NONNULL((2, 3)),char *,__NOTHROW_NCX,strtok_s,(char *__string, char const *__delim, char **__restrict __save_ptr),strtok_r,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_strtok_s)
__CDECLARE(__ATTR_NONNULL((2, 3)),char *,__NOTHROW_NCX,strtok_s,(char *__string, char const *__delim, char **__restrict __save_ptr),(__string,__delim,__save_ptr))
#else /* LIBC: strtok_r */
#include <local/string/strtok_r.h>
__FORCELOCAL __ATTR_NONNULL((2, 3)) char *__NOTHROW_NCX(__LIBCCALL strtok_s)(char *__string, char const *__delim, char **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtok_r))(__string, __delim, __save_ptr); }
#endif /* strtok_s... */
#endif /* __USE_DOS_SLIB */
#if __has_builtin(__builtin_strdup) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strdup)
__FORCELOCAL __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL _strdup)(char const *__restrict __string) { return __builtin_strdup(__string); }
#elif defined(__CRT_HAVE_strdup)
__CREDIRECT(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,_strdup,(char const *__restrict __string),strdup,(__string))
#elif defined(__CRT_HAVE__strdup)
__CDECLARE(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,_strdup,(char const *__restrict __string),(__string))
#elif defined(__CRT_HAVE___strdup)
__CREDIRECT(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,_strdup,(char const *__restrict __string),__strdup,(__string))
#elif (defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)) || (__has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)) || defined(__CRT_HAVE_malloc)
#include <local/string/strdup.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL _strdup)(char const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strdup))(__string); }
#endif /* _strdup... */
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _stricmp)(char const *__s1, char const *__s2) { return __builtin_strcasecmp(__s1, __s2); }
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricmp,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#else /* LIBC: strcasecmp */
#include <local/string/strcasecmp.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _stricmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))(__s1, __s2); }
#endif /* _stricmp... */
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strcmpi)(char const *__s1, char const *__s2) { return __builtin_strcasecmp(__s1, __s2); }
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strcmpi,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#else /* LIBC: strcasecmp */
#include <local/string/strcasecmp.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strcmpi)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))(__s1, __s2); }
#endif /* _strcmpi... */
#if defined(__CRT_HAVE_strcasecmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricmp_l,(char const *__s1, char const *__s2, __locale_t __locale),strcasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__stricmp_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricmp_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#else /* LIBC: strcasecmp_l */
#include <local/string/strcasecmp_l.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _stricmp_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp_l))(__s1, __s2, __locale); }
#endif /* _stricmp_l... */
#if defined(__CRT_HAVE_strcoll_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strcoll_l,(char const *__s1, char const *__s2, __locale_t __locale),strcoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__strcoll_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strcoll_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#else /* LIBC: strcoll_l */
#include <local/string/strcoll_l.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strcoll_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcoll_l))(__s1, __s2, __locale); }
#endif /* _strcoll_l... */
#if defined(__CRT_HAVE_strcasecoll)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),strcasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE__stricoll)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricoll,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#else /* LIBC: strcasecoll */
#include <local/string/strcasecoll.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _stricoll)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecoll))(__s1, __s2); }
#endif /* _stricoll... */
#if defined(__CRT_HAVE_strcasecoll_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricoll_l,(char const *__s1, char const *__s2, __locale_t __locale),strcasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__stricoll_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stricoll_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#else /* LIBC: strcasecoll_l */
#include <local/string/strcasecoll_l.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _stricoll_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecoll_l))(__s1, __s2, __locale); }
#endif /* _stricoll_l... */
#if defined(__CRT_HAVE_strncoll)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncoll,(char const *__s1, char const *__s2, size_t __maxlen),strncoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncoll)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncoll,(char const *__s1, char const *__s2, size_t __maxlen),(__s1,__s2,__maxlen))
#else /* LIBC: strncoll */
#include <local/string/strncoll.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strncoll)(char const *__s1, char const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncoll))(__s1, __s2, __maxlen); }
#endif /* _strncoll... */
#if defined(__CRT_HAVE_strncoll_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncoll_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),strncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncoll_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncoll_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#else /* LIBC: strncoll_l */
#include <local/string/strncoll_l.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strncoll_l)(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncoll_l))(__s1, __s2, __maxlen, __locale); }
#endif /* _strncoll_l... */
#if defined(__CRT_HAVE_strncasecoll)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll,(char const *__s1, char const *__s2, size_t __maxlen),strncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicoll)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll,(char const *__s1, char const *__s2, size_t __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll,(char const *__s1, char const *__s2, size_t __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#else /* LIBC: strncasecoll */
#include <local/string/strncasecoll.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strnicoll)(char const *__s1, char const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecoll))(__s1, __s2, __maxlen); }
#endif /* _strnicoll... */
#if defined(__CRT_HAVE_strncasecoll_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),strncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicoll_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_strncasecmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),_strnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncmpi_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicoll_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),_strncmpi_l,(__s1,__s2,__maxlen,__locale))
#else /* LIBC: strncasecoll_l */
#include <local/string/strncasecoll_l.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strnicoll_l)(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecoll_l))(__s1, __s2, __maxlen, __locale); }
#endif /* _strnicoll_l... */
#if defined(__CRT_HAVE__strerror)
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_RPC,_strerror,(char const *__message),(__message))
#endif /* _strerror... */
#if defined(__CRT_HAVE__strerror_s)
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_RPC,_strerror_s,(char *__restrict __buf, size_t __buflen, char const *__message),(__buf,__buflen,__message))
#endif /* _strerror_s... */
#if defined(__CRT_HAVE__strlwr_s)
__CDECLARE(,__errno_t,__NOTHROW_NCX,_strlwr_s,(char *__buf, size_t __buflen),(__buf,__buflen))
#else /* LIBC: _strlwr_s */
#include <local/string/_strlwr_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strlwr_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _strlwr_s)(char *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strlwr_s))(__buf, __buflen); })
#endif /* _strlwr_s... */
#if defined(__CRT_HAVE__strupr_s)
__CDECLARE(,__errno_t,__NOTHROW_NCX,_strupr_s,(char *__buf, size_t __buflen),(__buf,__buflen))
#else /* LIBC: _strupr_s */
#include <local/string/_strupr_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strupr_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _strupr_s)(char *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strupr_s))(__buf, __buflen); })
#endif /* _strupr_s... */
#if defined(__CRT_HAVE__strlwr_s_l)
__CDECLARE(,__errno_t,__NOTHROW_NCX,_strlwr_s_l,(char *__buf, size_t __buflen, __locale_t __locale),(__buf,__buflen,__locale))
#else /* LIBC: _strlwr_s_l */
#include <local/string/_strlwr_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strlwr_s_l, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _strlwr_s_l)(char *__buf, size_t __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strlwr_s_l))(__buf, __buflen, __locale); })
#endif /* _strlwr_s_l... */
#if defined(__CRT_HAVE__strupr_s_l)
__CDECLARE(,__errno_t,__NOTHROW_NCX,_strupr_s_l,(char *__buf, size_t __buflen, __locale_t __locale),(__buf,__buflen,__locale))
#else /* LIBC: _strupr_s_l */
#include <local/string/_strupr_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strupr_s_l, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _strupr_s_l)(char *__buf, size_t __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strupr_s_l))(__buf, __buflen, __locale); })
#endif /* _strupr_s_l... */
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strnicmp)(char const *__s1, char const *__s2, size_t __maxlen) { return __builtin_strncasecmp(__s1, __s2, __maxlen); }
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp,(char const *__s1, char const *__s2, size_t __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp,(char const *__s1, char const *__s2, size_t __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp,(char const *__s1, char const *__s2, size_t __maxlen),strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp,(char const *__s1, char const *__s2, size_t __maxlen),_strncmpi,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp,(char const *__s1, char const *__s2, size_t __maxlen),strncmpi,(__s1,__s2,__maxlen))
#else /* LIBC: strncasecmp */
#include <local/string/strncasecmp.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strnicmp)(char const *__s1, char const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp))(__s1, __s2, __maxlen); }
#endif /* _strnicmp... */
#if defined(__CRT_HAVE_strncasecmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicmp_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncmpi_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strnicmp_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),_strncmpi_l,(__s1,__s2,__maxlen,__locale))
#else /* LIBC: strncasecmp_l */
#include <local/string/strncasecmp_l.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strnicmp_l)(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp_l))(__s1, __s2, __maxlen, __locale); }
#endif /* _strnicmp_l... */
#if defined(__CRT_HAVE__strnset_s)
__CDECLARE(,__errno_t,__NOTHROW_NCX,_strnset_s,(char *__restrict __buf, size_t __buflen, int __ch, size_t __maxlen),(__buf,__buflen,__ch,__maxlen))
#else /* LIBC: _strnset_s */
#include <local/string/_strnset_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strnset_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _strnset_s)(char *__restrict __buf, size_t __buflen, int __ch, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strnset_s))(__buf, __buflen, __ch, __maxlen); })
#endif /* _strnset_s... */
#if defined(__CRT_HAVE_strrev)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,_strrev,(char *__restrict __str),strrev,(__str))
#elif defined(__CRT_HAVE__strrev)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,_strrev,(char *__restrict __str),(__str))
#else /* LIBC: strrev */
#include <local/string/strrev.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL _strrev)(char *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrev))(__str); }
#endif /* _strrev... */
#if defined(__CRT_HAVE_strxfrm_l)
__CREDIRECT(__ATTR_NONNULL((2)),size_t,__NOTHROW_NCX,_strxfrm_l,(char *__dst, char const *__restrict __src, size_t __maxlen, __locale_t __locale),strxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE__strxfrm_l)
__CDECLARE(__ATTR_NONNULL((2)),size_t,__NOTHROW_NCX,_strxfrm_l,(char *__dst, char const *__restrict __src, size_t __maxlen, __locale_t __locale),(__dst,__src,__maxlen,__locale))
#else /* LIBC: strxfrm_l */
#include <local/string/strxfrm_l.h>
__FORCELOCAL __ATTR_NONNULL((2)) size_t __NOTHROW_NCX(__LIBCCALL _strxfrm_l)(char *__dst, char const *__restrict __src, size_t __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strxfrm_l))(__dst, __src, __maxlen, __locale); }
#endif /* _strxfrm_l... */
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL stricmp)(char const *__s1, char const *__s2) { return __builtin_strcasecmp(__s1, __s2); }
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stricmp,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#else /* LIBC: strcasecmp */
#include <local/string/strcasecmp.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL stricmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))(__s1, __s2); }
#endif /* stricmp... */
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcmpi)(char const *__s1, char const *__s2) { return __builtin_strcasecmp(__s1, __s2); }
#elif defined(__CRT_HAVE_strcasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcmpi,(char const *__s1, char const *__s2),(__s1,__s2))
#else /* LIBC: strcasecmp */
#include <local/string/strcasecmp.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcmpi)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))(__s1, __s2); }
#endif /* strcmpi... */
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strnicmp)(char const *__s1, char const *__s2, size_t __maxlen) { return __builtin_strncasecmp(__s1, __s2, __maxlen); }
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strnicmp,(char const *__s1, char const *__s2, size_t __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strnicmp,(char const *__s1, char const *__s2, size_t __maxlen),_strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strnicmp,(char const *__s1, char const *__s2, size_t __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strnicmp,(char const *__s1, char const *__s2, size_t __maxlen),_strncmpi,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strnicmp,(char const *__s1, char const *__s2, size_t __maxlen),strncmpi,(__s1,__s2,__maxlen))
#else /* LIBC: strncasecmp */
#include <local/string/strncasecmp.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strnicmp)(char const *__s1, char const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp))(__s1, __s2, __maxlen); }
#endif /* strnicmp... */
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strncmpi)(char const *__s1, char const *__s2, size_t __maxlen) { return __builtin_strncasecmp(__s1, __s2, __maxlen); }
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi,(char const *__s1, char const *__s2, size_t __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi,(char const *__s1, char const *__s2, size_t __maxlen),_strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi,(char const *__s1, char const *__s2, size_t __maxlen),strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi,(char const *__s1, char const *__s2, size_t __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi,(char const *__s1, char const *__s2, size_t __maxlen),strncmpi,(__s1,__s2,__maxlen))
#else /* LIBC: strncasecmp */
#include <local/string/strncasecmp.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strncmpi)(char const *__s1, char const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp))(__s1, __s2, __maxlen); }
#endif /* _strncmpi... */
#if defined(__CRT_HAVE_strncasecmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),_strnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncmpi_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_strncmpi_l,(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#else /* LIBC: strncasecmp_l */
#include <local/string/strncasecmp_l.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _strncmpi_l)(char const *__s1, char const *__s2, size_t __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp_l))(__s1, __s2, __maxlen, __locale); }
#endif /* _strncmpi_l... */
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncmpi)(char const *__s1, char const *__s2, size_t __maxlen) { return __builtin_strncasecmp(__s1, __s2, __maxlen); }
#elif defined(__CRT_HAVE_strncasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmpi,(char const *__s1, char const *__s2, size_t __maxlen),strncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmpi,(char const *__s1, char const *__s2, size_t __maxlen),_strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmpi,(char const *__s1, char const *__s2, size_t __maxlen),strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmpi,(char const *__s1, char const *__s2, size_t __maxlen),_strncmpi,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncmpi,(char const *__s1, char const *__s2, size_t __maxlen),(__s1,__s2,__maxlen))
#else /* LIBC: strncasecmp */
#include <local/string/strncasecmp.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncmpi)(char const *__s1, char const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp))(__s1, __s2, __maxlen); }
#endif /* strncmpi... */

#ifndef _WSTRING_DEFINED
#define _WSTRING_DEFINED 1
#ifndef ___wcsdup_defined
#define ___wcsdup_defined 1
#if defined(__CRT_HAVE__wcsdup)
__CDECLARE(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsdup,(wchar_t const *__restrict __string),(__string))
#elif defined(__CRT_HAVE_wcsdup)
__CREDIRECT(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsdup,(wchar_t const *__restrict __string),wcsdup,(__string))
#elif (defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)) || (__has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)) || defined(__CRT_HAVE_malloc)
#include <local/wchar/wcsdup.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsdup)(wchar_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))(__string); }
#else /* CUSTOM: wcsdup */
#undef ___wcsdup_defined
#endif /* _wcsdup... */
#endif /* !___wcsdup_defined */
#ifndef __wcscat_defined
#define __wcscat_defined 1
#ifdef __std_wcscat_defined
__NAMESPACE_STD_USING(wcscat)
#elif defined(__CRT_HAVE_wcscat)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscat,(wchar_t *__restrict __buf, wchar_t const *__restrict __src),(__buf,__src))
#else /* LIBC: wcscat */
#include <local/wchar/wcscat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscat, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscat)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat))(__buf, __src); })
#endif /* wcscat... */
#endif /* !__wcscat_defined */
#ifndef __wcschr_defined
#define __wcschr_defined 1
#ifdef __std_wcschr_defined
__NAMESPACE_STD_USING(wcschr)
#elif defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#if defined(__CRT_HAVE_wcschr)
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcschr,(wchar_t *__restrict __haystack, wchar_t __needle),wcschr,(__haystack, __needle))
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcschr,(wchar_t const *__restrict __haystack, wchar_t __needle),wcschr,(__haystack, __needle))
}
#else /* LIBC: wcschr */
#include <local/wchar/wcschr.h>
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))(__haystack, __needle); }
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))(__haystack, __needle); }
}
#endif /* wcschr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#if defined(__CRT_HAVE_wcschr)
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcschr,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#else /* LIBC: wcschr */
#include <local/wchar/wcschr.h>
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcschr, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))(__haystack, __needle); })
#endif /* wcschr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__wcschr_defined */
#ifndef __wcscmp_defined
#define __wcscmp_defined 1
#ifdef __std_wcscmp_defined
__NAMESPACE_STD_USING(wcscmp)
#elif defined(__CRT_HAVE_wcscmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* LIBC: wcscmp */
#include <local/wchar/wcscmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))(__s1, __s2); })
#endif /* wcscmp... */
#endif /* !__wcscmp_defined */
#ifndef __wcscpy_defined
#define __wcscpy_defined 1
#ifdef __std_wcscpy_defined
__NAMESPACE_STD_USING(wcscpy)
#elif defined(__CRT_HAVE_wcscpy)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src),(__buf,__src))
#else /* LIBC: wcscpy */
#include <local/wchar/wcscpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy))(__buf, __src); })
#endif /* wcscpy... */
#endif /* !__wcscpy_defined */
#ifndef __wcscspn_defined
#define __wcscspn_defined 1
#ifdef __std_wcscspn_defined
__NAMESPACE_STD_USING(wcscspn)
#elif defined(__CRT_HAVE_wcscspn)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,wcscspn,(wchar_t const *__haystack, wchar_t const *__reject),(__haystack,__reject))
#else /* LIBC: wcscspn */
#include <local/wchar/wcscspn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscspn, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL wcscspn)(wchar_t const *__haystack, wchar_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscspn))(__haystack, __reject); })
#endif /* wcscspn... */
#endif /* !__wcscspn_defined */
#ifndef __wcslen_defined
#define __wcslen_defined 1
#ifdef __std_wcslen_defined
__NAMESPACE_STD_USING(wcslen)
#elif defined(__CRT_HAVE_wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,wcslen,(wchar_t const *__restrict __string),(__string))
#else /* LIBC: wcslen */
#include <local/wchar/wcslen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslen, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL wcslen)(wchar_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))(__string); })
#endif /* wcslen... */
#endif /* !__wcslen_defined */
#ifndef __wcsnlen_defined
#define __wcsnlen_defined 1
#if defined(__CRT_HAVE_wcsnlen)
/* Same as `wcslen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcsnlen,(wchar_t const *__restrict __string, __SIZE_TYPE__ __maxlen),(__string,__maxlen))
#else /* LIBC: wcsnlen */
#include <local/wchar/wcsnlen.h>
/* Same as `wcslen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnlen, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnlen)(wchar_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))(__string, __maxlen); })
#endif /* wcsnlen... */
#endif /* !__wcsnlen_defined */
#ifndef __wcsncat_defined
#define __wcsncat_defined 1
#ifdef __std_wcsncat_defined
__NAMESPACE_STD_USING(wcsncat)
#elif defined(__CRT_HAVE_wcsncat)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsncat,(wchar_t *__restrict __buf, wchar_t const *__restrict __src, size_t __buflen),(__buf,__src,__buflen))
#else /* LIBC: wcsncat */
#include <local/wchar/wcsncat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncat, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsncat)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat))(__buf, __src, __buflen); })
#endif /* wcsncat... */
#endif /* !__wcsncat_defined */
#ifndef __wcsncmp_defined
#define __wcsncmp_defined 1
#ifdef __std_wcsncmp_defined
__NAMESPACE_STD_USING(wcsncmp)
#elif defined(__CRT_HAVE_wcsncmp)
/* Same as `wcscmp', but compare at most `MAXLEN' characters from either string */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncmp,(wchar_t const *__s1, wchar_t const *__s2, size_t __maxlen),(__s1,__s2,__maxlen))
#else /* LIBC: wcsncmp */
#include <local/wchar/wcsncmp.h>
/* Same as `wcscmp', but compare at most `MAXLEN' characters from either string */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncmp)(wchar_t const *__s1, wchar_t const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))(__s1, __s2, __maxlen); })
#endif /* wcsncmp... */
#endif /* !__wcsncmp_defined */
#ifndef __wcsncpy_defined
#define __wcsncpy_defined 1
#ifdef __std_wcsncpy_defined
__NAMESPACE_STD_USING(wcsncpy)
#elif defined(__CRT_HAVE_wcsncpy)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsncpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src, size_t __buflen),(__buf,__src,__buflen))
#else /* LIBC: wcsncpy */
#include <local/wchar/wcsncpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsncpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy))(__buf, __src, __buflen); })
#endif /* wcsncpy... */
#endif /* !__wcsncpy_defined */
#ifndef __wcspbrk_defined
#define __wcspbrk_defined 1
#ifdef __std_wcspbrk_defined
__NAMESPACE_STD_USING(wcspbrk)
#elif defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#if defined(__CRT_HAVE_wcspbrk)
extern "C++" {
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcspbrk,(wchar_t *__haystack, wchar_t const *__accept),wcspbrk,(__haystack, __accept))
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcspbrk,(wchar_t const *__haystack, wchar_t const *__accept),wcspbrk,(__haystack, __accept))
}
#else /* LIBC: wcspbrk */
#include <local/wchar/wcspbrk.h>
extern "C++" {
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))(__haystack, __accept); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t const *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))(__haystack, __accept); }
}
#endif /* wcspbrk... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#if defined(__CRT_HAVE_wcspbrk)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcspbrk,(wchar_t const *__haystack, wchar_t const *__accept),(__haystack,__accept))
#else /* LIBC: wcspbrk */
#include <local/wchar/wcspbrk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcspbrk, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t const *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))(__haystack, __accept); })
#endif /* wcspbrk... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__wcspbrk_defined */
#ifndef __wcsrchr_defined
#define __wcsrchr_defined 1
#ifdef __std_wcsrchr_defined
__NAMESPACE_STD_USING(wcsrchr)
#elif defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#if defined(__CRT_HAVE_wcsrchr)
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrchr,(wchar_t *__restrict __haystack, wchar_t __needle),wcsrchr,(__haystack, __needle))
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsrchr,(wchar_t const *__restrict __haystack, wchar_t __needle),wcsrchr,(__haystack, __needle))
}
#else /* LIBC: wcsrchr */
#include <local/wchar/wcsrchr.h>
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))(__haystack, __needle); }
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))(__haystack, __needle); }
}
#endif /* wcsrchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#if defined(__CRT_HAVE_wcsrchr)
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrchr,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#else /* LIBC: wcsrchr */
#include <local/wchar/wcsrchr.h>
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrchr, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))(__haystack, __needle); })
#endif /* wcsrchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__wcsrchr_defined */
#ifndef __wcsspn_defined
#define __wcsspn_defined 1
#ifdef __std_wcsspn_defined
__NAMESPACE_STD_USING(wcsspn)
#elif defined(__CRT_HAVE_wcsspn)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,wcsspn,(wchar_t const *__haystack, wchar_t const *__accept),(__haystack,__accept))
#else /* LIBC: wcsspn */
#include <local/wchar/wcsspn.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsspn, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL wcsspn)(wchar_t const *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsspn))(__haystack, __accept); })
#endif /* wcsspn... */
#endif /* !__wcsspn_defined */
#ifndef __wcsstr_defined
#define __wcsstr_defined 1
#ifdef __std_wcsstr_defined
__NAMESPACE_STD_USING(wcsstr)
#elif defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#if defined(__CRT_HAVE_wcsstr)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t *__haystack, wchar_t *__needle),wcsstr,(__haystack, __needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),wcsstr,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_wcswcs)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t *__haystack, wchar_t *__needle),wcswcs,(__haystack, __needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack, __needle))
}
#else /* LIBC: wcsstr */
#include <local/wchar/wcsstr.h>
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t *__haystack, wchar_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
}
#endif /* wcsstr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#if defined(__CRT_HAVE_wcsstr)
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),(__haystack,__needle))
#elif defined(__CRT_HAVE_wcswcs)
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack,__needle))
#else /* LIBC: wcsstr */
#include <local/wchar/wcsstr.h>
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsstr, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); })
#endif /* wcsstr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__wcsstr_defined */
#ifndef __wcstok_defined
#define __wcstok_defined 1
#ifdef __std_wcstok_defined
__NAMESPACE_STD_USING(wcstok)
#elif defined(__CRT_HAVE_wcstok) && (!defined(__CRT_DOS_PRIMARY))
__CDECLARE(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok,(wchar_t *__string, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok_s)
__CREDIRECT(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok,(wchar_t *__string, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok_s,(__string,__delim,__save_ptr))
#else /* LIBC: wcstok */
#include <local/wchar/wcstok.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstok, __FORCELOCAL __ATTR_NONNULL((2, 3)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcstok)(wchar_t *__string, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))(__string, __delim, __save_ptr); })
#endif /* wcstok... */
#endif /* !__wcstok_defined */
#ifndef ___wcserror_defined
#define ___wcserror_defined 1
#if defined(__CRT_HAVE__wcserror)
__CDECLARE(,wchar_t *,__NOTHROW_NCX,_wcserror,(int __errno_value),(__errno_value))
#else /* LIBC: _wcserror */
#undef ___wcserror_defined
#endif /* _wcserror... */
#endif /* !___wcserror_defined */
#ifndef ___wcserror_s_defined
#define ___wcserror_s_defined 1
#if defined(__CRT_HAVE__wcserror_s)
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcserror_s,(wchar_t *__buf, __SIZE_TYPE__ __bufsize, int __errno_value),(__buf,__bufsize,__errno_value))
#else /* LIBC: _wcserror_s */
#undef ___wcserror_s_defined
#endif /* _wcserror_s... */
#endif /* !___wcserror_s_defined */
#ifndef ____wcserror_defined
#define ____wcserror_defined 1
#if defined(__CRT_HAVE___wcserror)
__CDECLARE(,wchar_t *,__NOTHROW_NCX,__wcserror,(wchar_t const *__message),(__message))
#else /* LIBC: __wcserror */
#undef ____wcserror_defined
#endif /* __wcserror... */
#endif /* !____wcserror_defined */
#ifndef ____wcserror_s_defined
#define ____wcserror_s_defined 1
#if defined(__CRT_HAVE___wcserror_s)
__CDECLARE(,__errno_t,__NOTHROW_NCX,__wcserror_s,(wchar_t *__buf, __SIZE_TYPE__ __bufsize, wchar_t const *__message),(__buf,__bufsize,__message))
#else /* LIBC: __wcserror_s */
#undef ____wcserror_s_defined
#endif /* __wcserror_s... */
#endif /* !____wcserror_s_defined */
#ifndef ___wcsicmp_defined
#define ___wcsicmp_defined 1
#if defined(__CRT_HAVE__wcsicmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),wcsicmp,(__s1,__s2))
#else /* LIBC: wcscasecmp */
#include <local/wchar/wcscasecmp.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))(__s1, __s2); }
#endif /* _wcsicmp... */
#endif /* !___wcsicmp_defined */
#ifndef ___wcsicmp_l_defined
#define ___wcsicmp_l_defined 1
#if defined(__CRT_HAVE__wcsicmp_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscasecmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcsicmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcsicmp_l,(__s1,__s2,__locale))
#else /* LIBC: wcscasecmp_l */
#include <local/wchar/wcscasecmp_l.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicmp_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp_l))(__s1, __s2, __locale); }
#endif /* _wcsicmp_l... */
#endif /* !___wcsicmp_l_defined */
#ifndef ___wcsnicmp_defined
#define ___wcsnicmp_defined 1
#if defined(__CRT_HAVE__wcsnicmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#else /* LIBC: wcsncasecmp */
#include <local/wchar/wcsncasecmp.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicmp)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))(__s1, __s2, __maxlen); }
#endif /* _wcsnicmp... */
#endif /* !___wcsnicmp_defined */
#ifndef ___wcsnicmp_l_defined
#define ___wcsnicmp_l_defined 1
#if defined(__CRT_HAVE__wcsnicmp_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncasecmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsnicmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#else /* LIBC: wcsncasecmp_l */
#include <local/wchar/wcsncasecmp_l.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicmp_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp_l))(__s1, __s2, __maxlen, __locale); }
#endif /* _wcsnicmp_l... */
#endif /* !___wcsnicmp_l_defined */
#ifndef ___wcsnset_s_defined
#define ___wcsnset_s_defined 1
#if defined(__CRT_HAVE__wcsnset_s)
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcsnset_s,(wchar_t *__buf, __SIZE_TYPE__ __buflen, wchar_t __ch, __SIZE_TYPE__ __maxlen),(__buf,__buflen,__ch,__maxlen))
#else /* LIBC: _wcsnset_s */
#include <local/wchar/_wcsnset_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsnset_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcsnset_s)(wchar_t *__buf, __SIZE_TYPE__ __buflen, wchar_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsnset_s))(__buf, __buflen, __ch, __maxlen); })
#endif /* _wcsnset_s... */
#endif /* !___wcsnset_s_defined */
#ifndef ___wcsnset_defined
#define ___wcsnset_defined 1
#if defined(__CRT_HAVE_wcsnset)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsnset,(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE__wcsnset)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsnset,(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen),(__str,__ch,__maxlen))
#else /* LIBC: wcsnset */
#include <local/wchar/wcsnset.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsnset)(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))(__str, __ch, __maxlen); }
#endif /* _wcsnset... */
#endif /* !___wcsnset_defined */
#ifndef ___wcsrev_defined
#define ___wcsrev_defined 1
#if defined(__CRT_HAVE_wcsrev)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsrev,(wchar_t *__restrict __str),wcsrev,(__str))
#elif defined(__CRT_HAVE__wcsrev)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsrev,(wchar_t *__restrict __str),(__str))
#else /* LIBC: wcsrev */
#include <local/wchar/wcsrev.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsrev)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))(__str); }
#endif /* _wcsrev... */
#endif /* !___wcsrev_defined */
#ifndef ___wcsset_s_defined
#define ___wcsset_s_defined 1
#if defined(__CRT_HAVE__wcsset_s)
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,_wcsset_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t __ch),(__dst,__dstsize,__ch))
#else /* LIBC: _wcsset_s */
#include <local/wchar/_wcsset_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsset_s, __FORCELOCAL __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBCCALL _wcsset_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsset_s))(__dst, __dstsize, __ch); })
#endif /* _wcsset_s... */
#endif /* !___wcsset_s_defined */
#ifndef ___wcsset_defined
#define ___wcsset_defined 1
#if defined(__CRT_HAVE_wcsset)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsset,(wchar_t *__restrict __str, wchar_t __ch),wcsset,(__str,__ch))
#elif defined(__CRT_HAVE__wcsset)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsset,(wchar_t *__restrict __str, wchar_t __ch),(__str,__ch))
#else /* LIBC: wcsset */
#include <local/wchar/wcsset.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsset)(wchar_t *__restrict __str, wchar_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))(__str, __ch); }
#endif /* _wcsset... */
#endif /* !___wcsset_defined */
#ifndef ___wcslwr_s_defined
#define ___wcslwr_s_defined 1
#if defined(__CRT_HAVE__wcslwr_s)
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcslwr_s,(wchar_t *__buf, __SIZE_TYPE__ __buflen),(__buf,__buflen))
#else /* LIBC: _wcslwr_s */
#include <local/wchar/_wcslwr_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcslwr_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcslwr_s)(wchar_t *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcslwr_s))(__buf, __buflen); })
#endif /* _wcslwr_s... */
#endif /* !___wcslwr_s_defined */
#ifndef ___wcslwr_defined
#define ___wcslwr_defined 1
#if defined(__CRT_HAVE_wcslwr)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcslwr,(wchar_t *__restrict __str),wcslwr,(__str))
#elif defined(__CRT_HAVE__wcslwr)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcslwr,(wchar_t *__restrict __str),(__str))
#else /* LIBC: wcslwr */
#include <local/wchar/wcslwr.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcslwr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))(__str); }
#endif /* _wcslwr... */
#endif /* !___wcslwr_defined */
#ifndef ___wcslwr_s_l_defined
#define ___wcslwr_s_l_defined 1
#if defined(__CRT_HAVE__wcslwr_s_l)
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcslwr_s_l,(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale),(__buf,__buflen,__locale))
#else /* LIBC: _wcslwr_s_l */
#include <local/wchar/_wcslwr_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcslwr_s_l, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcslwr_s_l)(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcslwr_s_l))(__buf, __buflen, __locale); })
#endif /* _wcslwr_s_l... */
#endif /* !___wcslwr_s_l_defined */
#ifndef ___wcslwr_l_defined
#define ___wcslwr_l_defined 1
#if defined(__CRT_HAVE_wcslwr_l)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcslwr_l,(wchar_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcslwr_l)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcslwr_l,(wchar_t *__restrict __str, __locale_t __locale),(__str,__locale))
#else /* LIBC: wcslwr_l */
#include <local/wchar/wcslwr_l.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcslwr_l)(wchar_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr_l))(__str, __locale); }
#endif /* _wcslwr_l... */
#endif /* !___wcslwr_l_defined */
#ifndef ___wcsupr_s_defined
#define ___wcsupr_s_defined 1
#if defined(__CRT_HAVE__wcsupr_s)
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcsupr_s,(wchar_t *__buf, __SIZE_TYPE__ __buflen),(__buf,__buflen))
#else /* LIBC: _wcsupr_s */
#include <local/wchar/_wcsupr_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsupr_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcsupr_s)(wchar_t *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsupr_s))(__buf, __buflen); })
#endif /* _wcsupr_s... */
#endif /* !___wcsupr_s_defined */
#ifndef ___wcsupr_defined
#define ___wcsupr_defined 1
#if defined(__CRT_HAVE_wcsupr)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsupr,(wchar_t *__restrict __str),wcsupr,(__str))
#elif defined(__CRT_HAVE__wcsupr)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsupr,(wchar_t *__restrict __str),(__str))
#else /* LIBC: wcsupr */
#include <local/wchar/wcsupr.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsupr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))(__str); }
#endif /* _wcsupr... */
#endif /* !___wcsupr_defined */
#ifndef ___wcsupr_s_l_defined
#define ___wcsupr_s_l_defined 1
#if defined(__CRT_HAVE__wcsupr_s_l)
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcsupr_s_l,(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale),(__buf,__buflen,__locale))
#else /* LIBC: _wcsupr_s_l */
#include <local/wchar/_wcsupr_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsupr_s_l, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcsupr_s_l)(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsupr_s_l))(__buf, __buflen, __locale); })
#endif /* _wcsupr_s_l... */
#endif /* !___wcsupr_s_l_defined */
#ifndef ___wcsupr_l_defined
#define ___wcsupr_l_defined 1
#if defined(__CRT_HAVE_wcsupr_l)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsupr_l,(wchar_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcsupr_l)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsupr_l,(wchar_t *__restrict __str, __locale_t __locale),(__str,__locale))
#else /* LIBC: wcsupr_l */
#include <local/wchar/wcsupr_l.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsupr_l)(wchar_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr_l))(__str, __locale); }
#endif /* _wcsupr_l... */
#endif /* !___wcsupr_l_defined */
#ifndef __wcsxfrm_defined
#define __wcsxfrm_defined 1
#ifdef __std_wcsxfrm_defined
__NAMESPACE_STD_USING(wcsxfrm)
#elif defined(__CRT_HAVE_wcsxfrm)
__CDECLARE(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,wcsxfrm,(wchar_t *__dst, wchar_t const *__restrict __src, size_t __maxlen),(__dst,__src,__maxlen))
#else /* LIBC: wcsxfrm */
#include <local/wchar/wcsxfrm.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsxfrm, __FORCELOCAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL wcsxfrm)(wchar_t *__dst, wchar_t const *__restrict __src, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm))(__dst, __src, __maxlen); })
#endif /* wcsxfrm... */
#endif /* !__wcsxfrm_defined */
#ifndef ___wcsxfrm_l_defined
#define ___wcsxfrm_l_defined 1
#if defined(__CRT_HAVE_wcsxfrm_l)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,_wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsxfrm_l)
__CDECLARE(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,_wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__dst,__src,__maxlen,__locale))
#else /* LIBC: wcsxfrm_l */
#include <local/wchar/wcsxfrm_l.h>
__FORCELOCAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcsxfrm_l)(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm_l))(__dst, __src, __maxlen, __locale); }
#endif /* _wcsxfrm_l... */
#endif /* !___wcsxfrm_l_defined */
#ifndef __wcscoll_defined
#define __wcscoll_defined 1
#ifdef __std_wcscoll_defined
__NAMESPACE_STD_USING(wcscoll)
#elif defined(__CRT_HAVE_wcscoll)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscoll,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* LIBC: wcscoll */
#include <local/wchar/wcscoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscoll, __FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll))(__s1, __s2); })
#endif /* wcscoll... */
#endif /* !__wcscoll_defined */
#ifndef ___wcscoll_l_defined
#define ___wcscoll_l_defined 1
#if defined(__CRT_HAVE_wcscoll_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcscoll_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#else /* LIBC: wcscoll_l */
#include <local/wchar/wcscoll_l.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcscoll_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll_l))(__s1, __s2, __locale); }
#endif /* _wcscoll_l... */
#endif /* !___wcscoll_l_defined */
#ifndef ___wcsicoll_defined
#define ___wcsicoll_defined 1
#if defined(__CRT_HAVE_wcscasecoll)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicoll)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcsicmp,(__s1,__s2))
#else /* LIBC: wcscasecoll */
#include <local/wchar/wcscasecoll.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))(__s1, __s2); }
#endif /* _wcsicoll... */
#endif /* !___wcsicoll_defined */
#ifndef ___wcsicoll_l_defined
#define ___wcsicoll_l_defined 1
#if defined(__CRT_HAVE_wcscasecoll_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicoll_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscasecmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#else /* LIBC: wcscasecoll_l */
#include <local/wchar/wcscasecoll_l.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicoll_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll_l))(__s1, __s2, __locale); }
#endif /* _wcsicoll_l... */
#endif /* !___wcsicoll_l_defined */
#ifndef ___wcsncoll_defined
#define ___wcsncoll_defined 1
#if defined(__CRT_HAVE__wcsncoll)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecoll)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicoll)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#else /* LIBC: wcsncasecoll */
#include <local/wchar/wcsncasecoll.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsncoll)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))(__s1, __s2, __maxlen); }
#endif /* _wcsncoll... */
#endif /* !___wcsncoll_defined */
#ifndef ___wcsncoll_l_defined
#define ___wcsncoll_l_defined 1
#if defined(__CRT_HAVE_wcsncoll_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsncoll_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#else /* LIBC: wcsncoll_l */
#include <local/wchar/wcsncoll_l.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsncoll_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll_l))(__s1, __s2, __maxlen, __locale); }
#endif /* _wcsncoll_l... */
#endif /* !___wcsncoll_l_defined */
#ifndef ___wcsnicoll_defined
#define ___wcsnicoll_defined 1
#if defined(__CRT_HAVE_wcsncasecoll)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicoll)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#else /* LIBC: wcsncasecoll */
#include <local/wchar/wcsncasecoll.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicoll)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))(__s1, __s2, __maxlen); }
#endif /* _wcsnicoll... */
#endif /* !___wcsnicoll_defined */
#ifndef ___wcsnicoll_l_defined
#define ___wcsnicoll_l_defined 1
#if defined(__CRT_HAVE_wcsncasecoll_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicoll_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncasecmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#else /* LIBC: wcsncasecoll_l */
#include <local/wchar/wcsncasecoll_l.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicoll_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll_l))(__s1, __s2, __maxlen, __locale); }
#endif /* _wcsnicoll_l... */
#endif /* !___wcsnicoll_l_defined */
#ifndef __wcsdup_defined
#define __wcsdup_defined 1
#if defined(__CRT_HAVE_wcsdup)
__CDECLARE(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsdup,(wchar_t const *__restrict __string),(__string))
#elif defined(__CRT_HAVE__wcsdup)
__CREDIRECT(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsdup,(wchar_t const *__restrict __string),_wcsdup,(__string))
#elif (defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)) || (__has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)) || defined(__CRT_HAVE_malloc)
#include <local/wchar/wcsdup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsdup, __FORCELOCAL __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsdup)(wchar_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))(__string); })
#else /* CUSTOM: wcsdup */
#undef __wcsdup_defined
#endif /* wcsdup... */
#endif /* !__wcsdup_defined */
#ifndef __wcswcs_defined
#define __wcswcs_defined 1
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#if defined(__CRT_HAVE_wcswcs)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t *__haystack, wchar_t *__needle),wcswcs,(__haystack, __needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_wcsstr)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t *__haystack, wchar_t *__needle),wcsstr,(__haystack, __needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),wcsstr,(__haystack, __needle))
}
#else /* LIBC: wcsstr */
#include <local/wchar/wcsstr.h>
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcswcs)(wchar_t *__haystack, wchar_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcswcs)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
}
#endif /* wcswcs... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#if defined(__CRT_HAVE_wcswcs)
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),(__haystack,__needle))
#elif defined(__CRT_HAVE_wcsstr)
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),wcsstr,(__haystack,__needle))
#else /* LIBC: wcsstr */
#include <local/wchar/wcsstr.h>
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcswcs)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
#endif /* wcswcs... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__wcswcs_defined */
#ifndef __wcsicmp_defined
#define __wcsicmp_defined 1
#if defined(__CRT_HAVE_wcscasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* LIBC: wcscasecmp */
#include <local/wchar/wcscasecmp.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsicmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))(__s1, __s2); }
#endif /* wcsicmp... */
#endif /* !__wcsicmp_defined */
#ifndef __wcsnicmp_defined
#define __wcsnicmp_defined 1
#if defined(__CRT_HAVE_wcsncasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#else /* LIBC: wcsncasecmp */
#include <local/wchar/wcsncasecmp.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsnicmp)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))(__s1, __s2, __maxlen); }
#endif /* wcsnicmp... */
#endif /* !__wcsnicmp_defined */
#ifndef __wcsnset_defined
#define __wcsnset_defined 1
#if defined(__CRT_HAVE_wcsnset)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnset,(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen),(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE__wcsnset)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnset,(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen),_wcsnset,(__str,__ch,__maxlen))
#else /* LIBC: wcsnset */
#include <local/wchar/wcsnset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnset)(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))(__str, __ch, __maxlen); })
#endif /* wcsnset... */
#endif /* !__wcsnset_defined */
#ifndef __wcsrev_defined
#define __wcsrev_defined 1
#if defined(__CRT_HAVE_wcsrev)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrev,(wchar_t *__restrict __str),(__str))
#elif defined(__CRT_HAVE__wcsrev)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrev,(wchar_t *__restrict __str),_wcsrev,(__str))
#else /* LIBC: wcsrev */
#include <local/wchar/wcsrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrev, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrev)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))(__str); })
#endif /* wcsrev... */
#endif /* !__wcsrev_defined */
#ifndef __wcsset_defined
#define __wcsset_defined 1
#if defined(__CRT_HAVE_wcsset)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsset,(wchar_t *__restrict __str, wchar_t __ch),(__str,__ch))
#elif defined(__CRT_HAVE__wcsset)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsset,(wchar_t *__restrict __str, wchar_t __ch),_wcsset,(__str,__ch))
#else /* LIBC: wcsset */
#include <local/wchar/wcsset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsset)(wchar_t *__restrict __str, wchar_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))(__str, __ch); })
#endif /* wcsset... */
#endif /* !__wcsset_defined */
#ifndef __wcslwr_defined
#define __wcslwr_defined 1
#if defined(__CRT_HAVE_wcslwr)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcslwr,(wchar_t *__restrict __str),(__str))
#elif defined(__CRT_HAVE__wcslwr)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcslwr,(wchar_t *__restrict __str),_wcslwr,(__str))
#else /* LIBC: wcslwr */
#include <local/wchar/wcslwr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslwr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcslwr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))(__str); })
#endif /* wcslwr... */
#endif /* !__wcslwr_defined */
#ifndef __wcsupr_defined
#define __wcsupr_defined 1
#if defined(__CRT_HAVE_wcsupr)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsupr,(wchar_t *__restrict __str),(__str))
#elif defined(__CRT_HAVE__wcsupr)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsupr,(wchar_t *__restrict __str),_wcsupr,(__str))
#else /* LIBC: wcsupr */
#include <local/wchar/wcsupr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsupr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsupr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))(__str); })
#endif /* wcsupr... */
#endif /* !__wcsupr_defined */
#ifndef __wcsicoll_defined
#define __wcsicoll_defined 1
#if defined(__CRT_HAVE_wcscasecoll)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicoll)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll)
__CDECLARE(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcsicmp,(__s1,__s2))
#else /* LIBC: wcscasecoll */
#include <local/wchar/wcscasecoll.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsicoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))(__s1, __s2); }
#endif /* wcsicoll... */
#endif /* !__wcsicoll_defined */
#ifdef __USE_DOS_SLIB
#ifndef __wcscat_s_defined
#define __wcscat_s_defined 1
#if defined(__CRT_HAVE_wcscat_s)
__CDECLARE(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,wcscat_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src),(__dst,__dstsize,__src))
#else /* LIBC: wcscat_s */
#include <local/wchar/wcscat_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscat_s, __FORCELOCAL __ATTR_NONNULL((1, 3)) __errno_t __NOTHROW_NCX(__LIBCCALL wcscat_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat_s))(__dst, __dstsize, __src); })
#endif /* wcscat_s... */
#endif /* !__wcscat_s_defined */
#ifndef __wcscpy_s_defined
#define __wcscpy_s_defined 1
#if defined(__CRT_HAVE_wcscpy_s)
__CDECLARE(,__errno_t,__NOTHROW_NCX,wcscpy_s,(wchar_t *__dst, rsize_t __dstsize, wchar_t const *__src),(__dst,__dstsize,__src))
#else /* LIBC: wcscpy_s */
#include <local/wchar/wcscpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscpy_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL wcscpy_s)(wchar_t *__dst, rsize_t __dstsize, wchar_t const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy_s))(__dst, __dstsize, __src); })
#endif /* wcscpy_s... */
#endif /* !__wcscpy_s_defined */
#ifndef __wcsncat_s_defined
#define __wcsncat_s_defined 1
#if defined(__CRT_HAVE_wcsncat_s)
__CDECLARE(,__errno_t,__NOTHROW_NCX,wcsncat_s,(wchar_t *__dst, rsize_t __dstsize, wchar_t const *__src, rsize_t __maxlen),(__dst,__dstsize,__src,__maxlen))
#else /* LIBC: wcsncat_s */
#include <local/wchar/wcsncat_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncat_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL wcsncat_s)(wchar_t *__dst, rsize_t __dstsize, wchar_t const *__src, rsize_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat_s))(__dst, __dstsize, __src, __maxlen); })
#endif /* wcsncat_s... */
#endif /* !__wcsncat_s_defined */
#ifndef __wcsncpy_s_defined
#define __wcsncpy_s_defined 1
#if defined(__CRT_HAVE_wcsncpy_s)
__CDECLARE(,__errno_t,__NOTHROW_NCX,wcsncpy_s,(wchar_t *__dst, rsize_t __dstsize, wchar_t const *__src, rsize_t __maxlen),(__dst,__dstsize,__src,__maxlen))
#else /* LIBC: wcsncpy_s */
#include <local/wchar/wcsncpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncpy_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL wcsncpy_s)(wchar_t *__dst, rsize_t __dstsize, wchar_t const *__src, rsize_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy_s))(__dst, __dstsize, __src, __maxlen); })
#endif /* wcsncpy_s... */
#endif /* !__wcsncpy_s_defined */
#ifndef __wcstok_s_defined
#define __wcstok_s_defined 1
#if defined(__CRT_HAVE_wcstok_s)
__CDECLARE(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok_s,(wchar_t *__string, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok)
__CREDIRECT(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok_s,(wchar_t *__string, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok,(__string,__delim,__save_ptr))
#else /* LIBC: wcstok */
#include <local/wchar/wcstok.h>
__FORCELOCAL __ATTR_NONNULL((2, 3)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcstok_s)(wchar_t *__string, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))(__string, __delim, __save_ptr); }
#endif /* wcstok_s... */
#endif /* !__wcstok_s_defined */
#ifndef __wcsnlen_s_defined
#define __wcsnlen_s_defined 1
__LOCAL __ATTR_WUNUSED __ATTR_PURE
size_t __NOTHROW_NCX((__LIBCCALL wcsnlen_s)(wchar_t const *__str, size_t __maxlen)) {
	return __str ? wcsnlen(__str, __maxlen) : 0;
}
#endif /* !__wcsnlen_s_defined */
#endif  /* __USE_DOS_SLIB */
#endif /* !_WSTRING_DEFINED */
#endif /* __USE_DOS */

#if defined(__LIBC_BIND_OPTIMIZATIONS) && !defined(__NO_builtin_constant_p)
#ifndef __INTELLISENSE__
#if __has_builtin(__builtin_strlen)
#ifdef __cplusplus
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST size_t __NOTHROW(__LIBCCALL __forward_size)(size_t __x) { return __x; }
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(__forward_size)
#endif
#define strlen(x) __forward_size(__builtin_constant_p(x) ? __builtin_strlen(x) : (__NAMESPACE_STD_SYM strlen)(x))
#else /* __cplusplus */
#define strlen(x) (__builtin_constant_p(x) ? __builtin_strlen(x) : (strlen)(x))
#endif /* !__cplusplus */
#endif
#endif
#endif /* __LIBC_BIND_OPTIMIZATIONS && !__NO_builtin_constant_p */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STRING_H)
#include <parts/uchar/string.h>
#endif
#endif /* __USE_UTF */

#endif /* !_CXX_CSTRING || __CXX_SYSTEM_HEADER */
#endif /* !_STRING_H */
