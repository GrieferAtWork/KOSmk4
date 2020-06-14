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

%[define_ccompat_header("cstring")]

%[define_replacement(locale_t = __locale_t)]
%[define_replacement(rsize_t  = __SIZE_TYPE__)]
%[default:section(".text.crt.string.memory")]

%(auto_header){
#ifdef __KERNEL__
/* The kernel isn't exporting these functions, but they're still
 * used by a couple of function that _are_ exported by the kernel! */
#define _libc_CMEM(func, dst, src, elem_count, elem_size) \
	func(dst, src, (elem_count) * (elem_size))
#define libc_memcpyc(dst, src, elem_count, elem_size)       _libc_CMEM(libc_memcpy, dst, src, elem_count, elem_size)
#define libc_mempcpyc(dst, src, elem_count, elem_size)      _libc_CMEM(libc_mempcpy, dst, src, elem_count, elem_size)
#define libc_memmovec(dst, src, elem_count, elem_size)      _libc_CMEM(libc_memmove, dst, src, elem_count, elem_size)
#define libc_mempmovec(dst, src, elem_count, elem_size)     _libc_CMEM(libc_mempmove, dst, src, elem_count, elem_size)
#define libc_memmoveupc(dst, src, elem_count, elem_size)    _libc_CMEM(libc_memmoveup, dst, src, elem_count, elem_size)
#define libc_mempmoveupc(dst, src, elem_count, elem_size)   _libc_CMEM(libc_mempmoveup, dst, src, elem_count, elem_size)
#define libc_memmovedownc(dst, src, elem_count, elem_size)  _libc_CMEM(libc_memmovedown, dst, src, elem_count, elem_size)
#define libc_mempmovedownc(dst, src, elem_count, elem_size) _libc_CMEM(libc_mempmovedown, dst, src, elem_count, elem_size)
#endif /* __KERNEL__ */
}

%{
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
}%(c, ccompat){
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#if defined(__std___forward_size_defined) && !defined(____forward_size_defined)
#define ____forward_size_defined 1
__NAMESPACE_STD_USING(__forward_size)
#endif /* __std___forward_size_defined && !____forward_size_defined */
}%{
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
}
%[insert:std]
%


%(auto_header){
#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef int errno_t;
#endif /* !__errno_t_defined */
#ifndef __rsize_t_defined
#define __rsize_t_defined 1
typedef size_t rsize_t;
#endif /* !__rsize_t_defined */

}


/* TODO: [[fast]] is somewhat broken at the moment, though
 *       I'm also not entirely sure on how to fix it.
 *
 * The current way of using namespace-import-bindings is flawed, as
 * it doesn't allow for the user to take the address of a function
 * that has been linked against a fast implementation (since the
 * fast implementations are inline functions, they don't get linked
 * against libc)
 *
 * The alternative would be to use (with memcpy as an example):
 * >> [[libc, std, kernel, ATTR_LEAF]]
 * >> [[if(defined(__fast_memcpy_defined)), preferred_extern_inline("memcpy", { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))(dst, src, n_bytes); })]]
 * >> [[if(defined(__fast_memcpy_defined)), preferred_inline({ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))(dst, src, n_bytes); })]]
 * >> [[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCPY))]]
 * >> [[nonnull]] void *memcpy([[nonnull]] void *__restrict dst,
 * >>                          [[nonnull]] void const *__restrict src,
 * >>                          size_t n_bytes) {
 * >>     ...
 * >> }
 *
 * But this way, we're not taking advantage of namespacing, _and_ only adding on-to
 * the already immense bloat found in headers (though this is probably still what
 * we'll eventually have to end up using, whilst scrapping the [[fast]] annotation
 * altogether...)
 */

@@Copy memory between non-overlapping memory blocks.
@@@return: * : Always re-returns `dst'
[[fast, libc, std, kernel, ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCPY))]]
[[nonnull]] void *memcpy([[nonnull]] void *__restrict dst,
                         [[nonnull]] void const *__restrict src,
                         size_t n_bytes) {
	byte_t *pdst = (byte_t *)dst;
	byte_t *psrc = (byte_t *)src;
	while (n_bytes--)
		*pdst++ = *psrc++;
	return dst;
}


@@Move memory between potentially overlapping memory blocks.
@@@return: * : Always re-returns `dst'
[[fast, libc, std, kernel, ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVE))]]
[[nonnull]] void *memmove([[nonnull]] void *dst,
                          [[nonnull]] void const *src,
                          size_t n_bytes) {
	byte_t *pdst, *psrc;
	if (dst <= src) {
		pdst = (byte_t *)dst;
		psrc = (byte_t *)src;
		while (n_bytes--)
			*pdst++ = *psrc++;
	} else {
		pdst = (byte_t *)dst + n_bytes;
		psrc = (byte_t *)src + n_bytes;
		while (n_bytes--)
			*--pdst = *--psrc;
	}
	return dst;
}

@@Fill memory with a given byte
@@@return: * : Always re-returns `dst'
[[fast, libc, std, kernel, ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMSET))]]
[[nonnull]] void *memset([[nonnull]] void *__restrict dst,
                         int byte, size_t n_bytes) {
	byte_t *pdst = (byte_t *)dst;
	while (n_bytes--)
		*pdst++ = (byte_t)byte;
	return dst;
}

@@Compare memory buffers and return the difference of the first non-matching byte
@@@return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
@@@return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
@@@return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes'
[[std, libc, fast, kernel, wunused, ATTR_PURE, alias("bcmp")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCMP))]]
[[if(!defined(__KERNEL__)), export_as("bcmp")]]
int memcmp([[nonnull]] void const *s1,
           [[nonnull]] void const *s2, size_t n_bytes) {
	byte_t *p1 = (byte_t *)s1;
	byte_t *p2 = (byte_t *)s2;
	byte_t v1, v2;
	v1 = v2 = 0;
	while (n_bytes-- && ((v1 = *p1++) == (v2 = *p2++)))
		;
	return (int)v1 - (int)v2;
}

@@Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found.
[[fast, libc, std, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCHR))]]
void *memchr([[nonnull]] void const *__restrict haystack, int needle, size_t n_bytes)
	[([[nonnull]] void *__restrict haystack, int needle, size_t n_bytes): void *]
	[([[nonnull]] void const *__restrict haystack, int needle, size_t n_bytes): void const *]
{
	byte_t *hay_iter = (byte_t *)haystack;
	for (; n_bytes--; ++hay_iter) {
		if unlikely(*hay_iter == (byte_t)needle)
			return hay_iter;
	}
	return NULL;
}


%(libc_fast)#if defined(__LIBC_BIND_OPTIMIZATIONS) && !defined(__NO_builtin_constant_p) && (__has_builtin(__builtin_strlen) && defined(__CRT_HAVE_strlen))
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
%(libc_fast)#define __libc_strlen(string) (__builtin_constant_p(string) ? __builtin_strlen(string) : __libc_core_strlen(string))
%(libc_fast)#else /* __LIBC_BIND_OPTIMIZATIONS && !__NO_builtin_constant_p && __builtin_strlen && __CRT_HAVE_strlen */
@@Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')')
[[libc, std, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRLEN))]]
size_t strlen([[nonnull]] char const *__restrict string) {
	return (size_t)(strend(string) - string);
}
%(libc_fast)#endif /* !__LIBC_BIND_OPTIMIZATIONS || __NO_builtin_constant_p || !__builtin_strlen || !__CRT_HAVE_strlen */

@@Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found.
[[libc, std, kernel, wunused, crtbuiltin, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRCHR))]]
char *strchr([[nonnull]] char const *__restrict haystack, int needle)
	[([[nonnull]] char *__restrict haystack, int needle): char *]
	[([[nonnull]] char const *__restrict haystack, int needle): char const *]
{
	for (; *haystack; ++haystack) {
		if unlikely(*haystack == (char)needle)
			return (char *)haystack;
	}
	return NULL;
}

@@Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found.
[[std, wunused, crtbuiltin, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRRCHR))]]
char *strrchr([[nonnull]] char const *__restrict haystack, int needle)
	[([[nonnull]] char *__restrict haystack, int needle): char *]
	[([[nonnull]] char const *__restrict haystack, int needle): char const *]
{
	char const *result = NULL;
	for (; *haystack; ++haystack) {
		if unlikely(*haystack == (char)needle)
			result = haystack;
	}
	return (char *)result;
}

@@Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical
[[libc, std, kernel, wunused, crtbuiltin, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRCMP))]]
int strcmp([[nonnull]] char const *s1, [[nonnull]] char const *s2) {
	char c1, c2;
	do {
		if unlikely((c1 = *s1++) != (c2 = *s2++))
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}

@@Same as `strcmp', but compare at most `MAXLEN' characters from either string
[[std, wunused, crtbuiltin, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRNCMP))]]
int strncmp([[nonnull]] char const *s1,
            [[nonnull]] char const *s2, size_t maxlen) {
	char c1, c2;
	do {
		if (!maxlen--)
			break;
		if ((c1 = *s1++) != (c2 = *s2++))
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}

@@Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
@@If no such needle exists, return `NULL'
[[std, wunused, crtbuiltin, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRSTR))]]
char *strstr([[nonnull]] char const *haystack, [[nonnull]] char const *needle)
	[([[nonnull]] char *haystack, [[nonnull]] char *needle): char *]
	[([[nonnull]] char const *haystack, [[nonnull]] char const *needle): char const *]
{
	char ch, needle_start = *needle++;
	while ((ch = *haystack++) != '\0') {
		if (ch == needle_start) {
			char const *hay2, *ned_iter;
			hay2     = haystack;
			ned_iter = needle;
			while ((ch = *ned_iter++) != '\0') {
				if (*hay2++ != ch)
					goto miss;
			}
			return (char *)haystack - 1;
		}
miss:
		;
	}
	return NULL;
}


[[std, crtbuiltin, ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRCPY))]]
[[nonnull]] char *strcpy([[nonnull]] char *__restrict buf,
                         [[nonnull]] char const *__restrict src) {
	return (char *)memcpy(buf, src, (strlen(src) + 1) * sizeof(char));
}

[[std, crtbuiltin, ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRNCPY))]]
[[nonnull]] char *strncpy([[nonnull]] char *__restrict buf,
                          [[nonnull]] char const *__restrict src, size_t buflen) {
	size_t srclen = strnlen(src, buflen);
	memcpy(buf, src, srclen * sizeof(char));
	memset(buf + srclen, '\0', (buflen - srclen) * sizeof(char));
	return buf;
}

[[std, crtbuiltin, ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRCAT))]]
[[nonnull]] char *strcat([[nonnull]] char *__restrict buf,
                         [[nonnull]] char const *__restrict src) {
	memcpy(strend(buf), src, (strlen(src) + 1) * sizeof(char));
	return buf;
}

[[std, crtbuiltin, ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRNCAT))]]
[[nonnull]] char *strncat([[nonnull]] char *__restrict buf,
                          [[nonnull]] char const *__restrict src,
                          size_t buflen) {
	size_t srclen = strnlen(src, buflen);
	char *dst = strend(buf);
	memcpy(dst, src, srclen * sizeof(char));
	dst[srclen] = '\0';
	return buf;
}

[[std, wunused, crtbuiltin, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRCSPN))]]
size_t strcspn([[nonnull]] char const *haystack,
               [[nonnull]] char const *reject) {
	char const *iter = haystack;
	while (*iter && !strchr(reject, *iter))
		++iter;
	return (size_t)(iter - haystack);
}

[[std, wunused, crtbuiltin, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRSPN))]]
size_t strspn([[nonnull]] char const *haystack,
              [[nonnull]] char const *accept) {
	char const *iter = haystack;
	while (strchr(accept, *iter))
		++iter;
	return (size_t)(iter - haystack);
}

[[std, wunused, crtbuiltin, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRPBRK))]]
char *strpbrk([[nonnull]] char const *haystack, [[nonnull]] char const *accept)
	[([[nonnull]] char *haystack, [[nonnull]] char const *accept): char *]
	[([[nonnull]] char const *haystack, [[nonnull]] char const *accept): char const *]
{
	char haych, ch;
	while ((haych = *haystack++) != '\0') {
		char const *ned_iter;
		ned_iter = accept;
		while ((ch = *ned_iter++) != '\0') {
			if (haych == ch)
				return (char *)haystack - 1;
		}
	}
	return NULL;
}


[[std]]
char *strtok(char *string, [[nonnull]] char const *delim) {
	static char *save_ptr = NULL;
	return strtok_r(string, delim, &save_ptr);
}

[[std, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRCOLL))]]
[[section(".text.crt.unicode.static.memory")]]
int strcoll([[nonnull]] char const *s1,
            [[nonnull]] char const *s2) {
	return strcmp(s1, s2);
}

[[std, section(".text.crt.unicode.static.memory")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRXFRM))]]
size_t strxfrm(char *dst, [[nonnull]] char const *__restrict src, size_t maxlen) {
	/* XXX: Implement me */
	size_t n = strnlen(src, maxlen);
	memcpy(dst, src, n * sizeof(char));
	return n;
}

%[define(DEFINE_STRERROR_BUF =
@@pp_ifndef __local_strerror_buf_defined@@
#define __local_strerror_buf_defined 1
@@push_namespace(local)@@
__LOCAL_LIBC_DATA(strerror_buf) char strerror_buf[64] = { 0 };
@@pop_namespace@@
@@pp_endif@@
)]

[[std, wunused, ATTR_COLD]]
[[nonnull, section(".text.crt.errno")]]
[[impl_prefix(DEFINE_STRERROR_BUF)]]
char *strerror(int errnum) {
	char *result = __NAMESPACE_LOCAL_SYM strerror_buf;
	char const *string;
	string = strerror_s(errnum);
	if (string) {
		/* Copy the descriptor text. */
		result[COMPILER_LENOF(__NAMESPACE_LOCAL_SYM strerror_buf) - 1] = '\0';
		strncpy(result, string, COMPILER_LENOF(__NAMESPACE_LOCAL_SYM strerror_buf) - 1);
	} else {
		sprintf(result, "Unknown error %d", errnum);
	}
	return result;
}

%(std)#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
%[insert:std_function_nousing(memcpy = memcpyc, externLinkageOverride: "C++")]
%[insert:std_function_nousing(memmove = memmovec, externLinkageOverride: "C++")]
%(std)#endif /* __cplusplus && __USE_STRING_OVERLOADS */



%{

#ifdef _MSC_VER
__NAMESPACE_STD_BEGIN
#pragma intrinsic(strcpy)
#pragma intrinsic(strcat)
__NAMESPACE_STD_END
#endif /* _MSC_VER */

}

%#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
@@Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´)
[[libc, kernel, wunused, crtbuiltin, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRNLEN))]]
$size_t strnlen([[nonnull]] char const *__restrict string, $size_t maxlen) {
	return (size_t)(strnend(string, maxlen) - string);
}
%#endif /* __USE_XOPEN2K8 || __USE_DOS */

%#ifdef __USE_XOPEN2K8

@@Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´
[[crtbuiltin, ATTR_LEAF, export_alias("__stpcpy")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STPCPY))]]
stpcpy:([[nonnull]] char *__restrict buf,
        [[nonnull]] char const *__restrict src)
	-> [[== buf + strlen(src)]] char *
{
	return (char *)mempcpy(buf, src, (strlen(src) + 1) * sizeof(char)) - 1;
}

[[crtbuiltin, ATTR_LEAF, export_alias("__stpncpy")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STPNCPY))]]
stpncpy:([[nonnull]] char *__restrict buf,
         [[nonnull]] char const *__restrict src,
         $size_t buflen)
	-> [[== buf + strnlen(src, buflen)]] char *
{
	size_t srclen = strnlen(src, buflen);
	memcpy(buf, src, srclen * sizeof(char));
	memset(buf + srclen, '\0', (size_t)(buflen - srclen) * sizeof(char));
	return buf + srclen;
}

%[insert:function(__stpcpy = stpcpy)]
%[insert:function(__stpncpy = stpncpy)]

[[wunused, ATTR_PURE, export_alias("_strcoll_l", "__strcoll_l")]]
[[section(".text.crt.unicode.locale.memory")]]
int strcoll_l([[nonnull]] char const *s1,
              [[nonnull]] char const *s2,
              $locale_t locale) {
	(void)locale;
	return strcoll(s1, s2);
}

[[export_alias("_strxfrm_l", "__strxfrm_l")]]
[[section(".text.crt.unicode.locale.memory")]]
$size_t strxfrm_l(char *dst, [[nonnull]] char const *__restrict src,
                  $size_t maxlen, $locale_t locale) {
	(void)locale;
	return strxfrm(dst, src, maxlen);
}

[[ATTR_COLD, wunused, section(".text.crt.errno")]]
[[requires_function(strerror)]]
char *strerror_l(int errnum, $locale_t locale) {
	(void)locale;
	return strerror(errnum);
}

[[std, wunused, ATTR_COLD]]
[[nonnull, section(".text.crt.string.memory.strsignal")]]
char *strsignal(int signo) {
	static char strsignal_buf[64] = { 0 };
	char *result = strsignal_buf;
	char const *string;
	string = strsignal_s(signo);
	if (string) {
		/* Copy the descriptor text. */
		result[COMPILER_LENOF(strsignal_buf) - 1] = '\0';
		strncpy(result, string, COMPILER_LENOF(strsignal_buf) - 1);
	} else {
		sprintf(result, "Unknown signal %d", signo);
	}
	return result;
}

[[crtbuiltin, export_alias("__strndup")]]
[[requires_function(malloc), section(".text.crt.heap.strdup")]]
strndup([[nonnull]] char const *__restrict string, $size_t max_chars)
	-> [[malloc/*((strnlen(string, max_chars) + 1) * sizeof(char))*/]] char *
{
	size_t resultsize = strnlen(string, max_chars) * sizeof(char);
	char *result = (char *)malloc(resultsize + sizeof(char));
	if likely(result) {
		*(char *)mempcpy(result, string, resultsize) = '\0';
	}
	return result;
}


%{
#endif /* __USE_XOPEN2K8 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8) || defined(__USE_DOS)
}
[[crtbuiltin, export_alias("_strdup", "__strdup")]]
[[section(".text.crt.heap.strdup"), requires_function(malloc)]]
strdup([[nonnull]] char const *__restrict string)
	-> [[malloc/*((strlen(string) + 1) * sizeof(char))*/]] char *
{
	size_t resultsize = (strlen(string) + 1) * sizeof(char);
	char *result = (char *)malloc(resultsize);
	if likely(result)
		memcpy(result, string, resultsize);
	return result;
}
%{
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 || __USE_DOS */

#ifdef __USE_POSIX
}

[[ATTR_LEAF, export_alias("strtok_s", "__strtok_r")]]
char *strtok_r([[nullable]] char *string,
               [[nonnull]] char const *delim,
               [[nonnull]] char **__restrict save_ptr) {
	char *end;
	if (!string)
		string = *save_ptr;
	if (!*string) {
		*save_ptr = string;
		return NULL;
	}
	string += strspn(string, delim);
	if (!*string) {
		*save_ptr = string;
		return NULL;
	}
	end = string + strcspn(string, delim);
	if (!*end) {
		*save_ptr = end;
		return string;
	}
	*end = '\0';
	*save_ptr = end + 1;
	return string;
}
%{
#endif /* __USE_POSIX */

#ifdef __USE_GNU
}

@@Descendingly search for `NEEDLE', starting at `HAYSTACK + N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found.
[[libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRCHR))]]
void *memrchr([[nonnull]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[nonnull]] void *__restrict haystack, int needle, $size_t n_bytes): void *]
	[([[nonnull]] void const *__restrict haystack, int needle, $size_t n_bytes): void const *]
{
	byte_t *iter = (byte_t *)haystack + n_bytes;
	while (n_bytes--) {
		if (*--iter == (byte_t)needle)
			return iter;
	}
	return NULL;
}


@@Same as `memchr' with a search limit of `(size_t)-1'
[[kernel, wunused, ATTR_PURE, alias("__rawmemchr")]]
[[if(!defined(__KERNEL__)), export_as("__rawmemchr")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMCHR))]]
[[nonnull]] void *rawmemchr([[nonnull]] void const *__restrict haystack, int needle)
	[([[nonnull]] void *__restrict haystack, int needle): [[nonnull]] void *]
	[([[nonnull]] void const *__restrict haystack, int needle): [[nonnull]] void const *]
{
	byte_t *iter = (byte_t *)haystack;
	for (;; ++iter) {
		if (*iter == (byte_t)needle)
			break;
	}
	return iter;
}

@@Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRCHRNUL))]]
[[nonnull]] char *strchrnul([[nonnull]] char const *__restrict haystack, int needle)
	[([[nonnull]] char *__restrict haystack, int needle): [[nonnull]] char *]
	[([[nonnull]] char const *__restrict haystack, int needle): [[nonnull]] char const *]
{
	for (; *haystack; ++haystack) {
		if (*haystack == (char)needle)
			break;
	}
	return (char *)haystack;
}

[[guard, wunused, ATTR_PURE]]
char *basename([[nullable]] char const *filename)
	[([[nullable]] char *filename): char *]
	[([[nullable]] char const *filename): char const *]
{
	char ch, *iter = (char *)filename, *result = NULL;
	if (!filename || !*filename)
		return (char *)filename;
	do {
		ch = *iter++;
@@pp_ifdef _WIN32@@
		if (ch == '/' || ch == '\\')
			result = iter;
@@pp_else@@
		if (ch == '/')
			result = iter;
@@pp_endif@@
	} while (ch);
	if unlikely(!result)
		return (char *)filename; /* Path doesn't contain '/'. */
	if (*result)
		return result; /* Last character isn't a '/'. */
	iter = result;
@@pp_ifdef _WIN32@@
	while (iter != filename && (iter[-1] == '/' || iter[-1] == '\\'))
		--iter;
@@pp_else@@
	while (iter != filename && iter[-1] == '/')
		--iter;
@@pp_endif@@
	if (iter == filename)
		return result-1; /* Only `'/'"-characters. */
	//*iter = '\0'; /* Trim all ending `'/'"-characters. */
@@pp_ifdef _WIN32@@
	while (iter != filename && (iter[-1] != '/' || iter[-1] != '\\'))
		--iter; /* Scan until the previous '/'. */
@@pp_else@@
	while (iter != filename && iter[-1] != '/')
		--iter; /* Scan until the previous '/'. */
@@pp_endif@@
	return iter; /* Returns string after previous '/'. */
}


@@Same as `strstr', but ignore casing
[[wunused, ATTR_PURE, export_alias("__strcasestr")]]
[[section(".text.crt.unicode.static.memory")]]
[[nullable]] char *strcasestr([[nonnull]] char const *haystack, [[nonnull]] char const *needle)
	[([[nonnull]] char *haystack, [[nonnull]] char const *needle): [[nullable]] char *]
	[([[nonnull]] char const *haystack, [[nonnull]] char const *needle): [[nullable]] char const *]
{
	for (; *haystack; ++haystack) {
		if (strcasecmp(haystack, needle) == 0)
			return (char *)haystack;
	}
	return NULL;
}

@@Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
@@If no such sub-string exists, return `NULL' instead.
@@#ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
@@When `needlelen' is ZERO(0), also return `NULL' unconditionally.
@@#else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
@@When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
@@#endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
[[libc, wunused, ATTR_PURE, no_crt_self_import]]
[[if(defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), preferred_alias("memmem0")]]
[[if(!defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), preferred_alias("memmem")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMEM))]]
[[impl_include("<features.h>")]]
[[nullable]] void *memmem([[nonnull]] void const *haystack, $size_t haystacklen, [[nonnull]] void const *needle, $size_t needlelen)
	[([[nonnull]] void *haystack, $size_t haystacklen, [[nonnull]] void const *needle, $size_t needlelen): [[nullable]] void *]
	[([[nonnull]] void const *haystack, $size_t haystacklen, [[nonnull]] void const *needle, $size_t needlelen): [[nullable]] void const *]
{
	byte_t *candidate, marker;
#if defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL) && !defined(__BUILDING_LIBC)
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
#else /* __USE_MEMMEM_EMPTY_NEEDLE_NULL && !__BUILDING_LIBC */
	if unlikely(!needlelen)
		return (void *)haystack;
	if unlikely(needlelen > haystacklen)
		return NULL;
#endif /* !__USE_MEMMEM_EMPTY_NEEDLE_NULL || __BUILDING_LIBC */
	haystacklen -= (needlelen - 1);
	marker       = *(byte_t *)needle;
	while ((candidate = (byte_t *)memchr(haystack, marker, haystacklen)) != NULL) {
		if (memcmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((byte_t *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}

[[wunused, ATTR_PURE, export_alias("__strverscmp")]]
int strverscmp([[nonnull]] char const *s1,
               [[nonnull]] char const *s2) {
	char const *s1_start = s1;
	char c1, c2;
	do {
		if ((c1 = *s1) != (c2 = *s2)) {
			unsigned int vala, valb;
			/* Unwind common digits. */
			while (s1 != s1_start) {
				if (s1[-1] < '0' || s1[-1] > '9')
					break;
				c2 = c1 = *--s1, --s2;
			}
			/* Check if both strings have digit sequences in the same places. */
			if ((c1 < '0' || c1 > '9') &&
			    (c2 < '0' || c2 > '9'))
				return (int)((unsigned char)c1 - (unsigned char)c2);
			/* Deal with leading zeros. */
			if (c1 == '0')
				return -1;
			if (c2 == '0')
				return 1;
			/* Compare digits. */
			vala = c1 - '0';
			valb = c2 - '0';
			for (;;) {
				c1 = *s1++;
				if (c1 < '0' || c1 > '9')
					break;
				vala *= 10;
				vala += c1-'0';
			}
			for (;;) {
				c2 = *s2++;
				if (c2 < '0' || c2 > '9')
					break;
				valb *= 10;
				valb += c2-'0';
			}
			return (int)vala - (int)valb;
		}
		++s1, ++s2;
	} while (c1);
	return 0;
}


%[insert:function(__mempcpy = mempcpy)]

@@Same as `memcpy', but return `DST + N_BYTES', rather than `DST'
[[guard, libc, kernel, fast, ATTR_LEAF, alias("__mempcpy")]]
[[if(!defined(__KERNEL__)), export_as("__mempcpy")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPCPY))]]
mempcpy:([[nonnull]] void *__restrict dst,
         [[nonnull]] void const *__restrict src,
         $size_t n_bytes) -> [[== dst + n_bytes]] void * {
	byte_t *pdst = (byte_t *)dst;
	byte_t *psrc = (byte_t *)src;
	while (n_bytes--)
		*pdst++ = *psrc++;
	return pdst;
}

%#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
%[insert:function(mempcpy = mempcpyc, externLinkageOverride: "C++")]
%#endif /* __cplusplus && __USE_STRING_OVERLOADS */


[[ATTR_LEAF]]
strfry:([[nonnull]] char *__restrict string) -> [[== string]] char * {
	size_t i, count = strlen(string);
	for (i = 0; i < count; ++i) {
		char temp;
		size_t j = rand();
		j = i + (j % (count - i));
		/* Swap these 2 characters. */
		temp = string[i];
		string[i] = string[j];
		string[j] = temp;
	}
	return string;
}

[[ATTR_LEAF]]
memfrob:([[nonnull]] void *buf, $size_t num_bytes) -> [[== buf]] void * {
	byte_t *iter = (byte_t *)buf;
	while (num_bytes--)
		*iter++ ^= 42; /* -_-   yeah... */
	return buf;
}

[[guard, ATTR_PURE, wunused]]
[[export_alias("_stricmp_l", "__strcasecmp_l")]]
[[section(".text.crt.unicode.locale.memory")]]
strcasecmp_l:([[nonnull]] char const *s1, [[nonnull]] char const *s2, $locale_t locale) -> int {
	(void)locale;
	return strcasecmp(s1, s2);
}

[[guard, wunused, ATTR_PURE]]
[[export_alias("_strnicmp_l", "_strncmpi_l", "__strncasecmp_l")]]
[[section(".text.crt.unicode.locale.memory")]]
int strncasecmp_l([[nonnull]] char const *s1,
                  [[nonnull]] char const *s2,
                  $size_t maxlen, $locale_t locale) {
	(void)locale;
	return strncasecmp(s1, s2, maxlen);
}

%#endif /* __USE_GNU */
%
%#ifdef __USE_XOPEN2K
%#ifdef __USE_GNU
[[ATTR_COLD, export_alias("__strerror_r")]]
[[nonnull, section(".text.crt.errno")]]
[[impl_include("<hybrid/__assert.h>")]]
[[impl_prefix(DEFINE_STRERROR_BUF)]]
char *strerror_r(int errnum, [[nonnull]] char *buf, $size_t buflen) {
	char const *string;
	string = strerror_s(errnum);
	if (!buf || !buflen) {
		buf    = __NAMESPACE_LOCAL_SYM strerror_buf;
		buflen = COMPILER_LENOF(__NAMESPACE_LOCAL_SYM strerror_buf);
	}
	if (string) {
		/* Copy the descriptor text. */
		size_t msg_len = strlen(string) + 1;
		if (msg_len > buflen) {
			buf    = __NAMESPACE_LOCAL_SYM strerror_buf;
			buflen = COMPILER_LENOF(__NAMESPACE_LOCAL_SYM strerror_buf);
			if unlikely(msg_len > buflen) {
				msg_len      = buflen - 1;
				buf[msg_len] = '\0';
			}
		}
		memcpyc(buf, string, msg_len, sizeof(char));
	} else {
again_unknown:
		if (snprintf(buf, buflen, "Unknown error %d", errnum) >= buflen) {
			__hybrid_assert(buf != __NAMESPACE_LOCAL_SYM strerror_buf);
			buf    = __NAMESPACE_LOCAL_SYM strerror_buf;
			buflen = COMPILER_LENOF(__NAMESPACE_LOCAL_SYM strerror_buf);
			goto again_unknown;
		}
	}
	return buf;
}

%#else /* __USE_GNU */
[[ATTR_COLD, exposed_name("strerror_r"), section(".text.crt.errno")]]
[[impl_include("<parts/errno.h>")]]
$errno_t __xpg_strerror_r(int errnum, [[nonnull]] char *buf, $size_t buflen) {
	size_t msg_len;
	char const *string;
	string = strerror_s(errnum);
	if (!buf)
		buflen = 0;
	if (!string) {
@@pp_ifdef EINVAL@@
		return EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	/* Copy the descriptor text. */
	msg_len = strlen(string) + 1;
	if (msg_len > buflen) {
@@pp_ifdef ERANGE@@
		return ERANGE;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	memcpyc(buf, string, msg_len, sizeof(char));
	return EOK;
}
%#endif /* !__USE_GNU */
%#endif /* __USE_XOPEN2K */
%
%#ifdef __USE_MISC

[[ATTR_LEAF]]
char *strsep([[nonnull]] char **__restrict stringp,
             [[nonnull]] char const *__restrict delim) {
	char *result, *iter;
	if (!stringp || (result = *stringp) == NULL || !*result)
		return NULL;
	for (iter = result; *iter && !strchr(delim, *iter); ++iter)
		;
	if (*iter)
		*iter++ = '\0';
	*stringp = iter;
	return result;
}

%[insert:extern(bcopy)]
%[insert:extern(bzero)]
%[insert:guarded_function(bcmp = memcmp)]
%[insert:extern(index)]
%[insert:extern(rindex)]

[[guard, export_alias("_stricmp", "_strcmpi", "stricmp", "strcmpi", "__strcasecmp")]]
[[wunused, ATTR_PURE, section(".text.crt.unicode.static.memory"), crtbuiltin]]
int strcasecmp([[nonnull]] char const *s1, [[nonnull]] char const *s2) {
	char c1, c2;
	do {
		if ((c1 = *s1++) != (c2 = *s2++) && ((c1 = tolower(c1)) != (c2 = tolower(c2))))
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}
[[guard, export_alias("_strnicmp", "strnicmp", "_strncmpi", "strncmpi")]]
[[wunused, ATTR_PURE, section(".text.crt.unicode.static.memory"), crtbuiltin]]
int strncasecmp([[nonnull]] char const *s1, [[nonnull]] char const *s2, $size_t maxlen) {
	char c1, c2;
	do {
		if (!maxlen--)
			break;
		if ((c1 = *s1++) != (c2 = *s2++) && ((c1 = tolower(c1)) != (c2 = tolower(c2))))
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}


[[decl_include("<features.h>")]]
[[wunused, nothrow, ATTR_CONST, crtbuiltin]]
[[impl_include("<hybrid/__bit.h>"), export_alias("__ffs")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_FFS))]]
__STDC_INT_AS_SIZE_T ffs(int i) {
	return (__STDC_INT_AS_SIZE_T)__hybrid_ffs((unsigned int)i);
}

%{
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
}

%#ifdef __USE_GNU
[[decl_include("<features.h>")]]
[[wunused, nothrow, ATTR_CONST, crtbuiltin]]
[[impl_include("<hybrid/__bit.h>")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_FFSL))]]
__STDC_INT_AS_SIZE_T ffsl(long i) {
	return (__STDC_INT_AS_SIZE_T)__hybrid_ffs((unsigned long)i);
}

[[decl_include("<features.h>")]]
[[wunused, nothrow, ATTR_CONST, crtbuiltin]]
[[impl_include("<hybrid/__bit.h>")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_FFSLL))]]
__STDC_INT_AS_SIZE_T ffsll(__LONGLONG i) {
	return (__STDC_INT_AS_SIZE_T)__hybrid_ffs((__ULONGLONG)i);
}
%#endif /* __USE_GNU */

[[ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRLCAT))]]
$size_t strlcat([[nonnull]] char *__restrict dst,
                [[nonnull]] char const *__restrict src,
                $size_t bufsize) {
	size_t result = strlen(src);
	char *new_dst = dst + strnlen(dst, bufsize);
	size_t copy_size;
	bufsize -= (new_dst - dst);
	copy_size = result < bufsize ? result : bufsize - 1;
	memcpy(new_dst, src, copy_size*sizeof(char));
	new_dst[copy_size] = '\0';
	return result + (new_dst - dst);
}

[[ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRLCPY))]]
$size_t strlcpy([[nonnull]] char *__restrict dst,
                [[nonnull]] char const *__restrict src,
                $size_t bufsize) {
	size_t result = strlen(src);
	size_t copy_size = result < bufsize ? result : bufsize - 1;
	memcpy(dst, src, copy_size*sizeof(char));
	dst[copy_size] = '\0';
	return result;
}

%{
#endif /* __USE_MISC */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
}

[[ATTR_LEAF, export_alias("_memccpy")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCCPY))]]
void *memccpy([[nonnull]] void *__restrict dst,
              [[nonnull]] void const *__restrict src,
              int needle, $size_t num_bytes) {
	byte_t *pdst = (byte_t *)dst;
	byte_t const *psrc = (byte_t const *)src;
	while (num_bytes--) {
		if ((*pdst++ = *psrc++) == (byte_t)needle)
			return pdst; /* Yes, this returns +1 past the needle. */
	}
	return NULL;
}
%{
#endif /* __USE_MISC || __USE_XOPEN */


}

%[insert:function(__bzero = bzero)]
%[insert:function(__strtok_r = strtok_r)]

%
%#ifdef __USE_STRING_BWLQ

@@Copy memory between non-overlapping memory blocks.
[[ATTR_LEAF]]
memcpyb:([[nonnull]] /*aligned(1)*/ void *__restrict dst,
         [[nonnull]] /*aligned(1)*/ void const *__restrict src,
         $size_t n_bytes) -> [[== dst]] $uint8_t * = memcpy;

@@Same as `memcpyb', but return `DST + N_BYTES', rather than `DST'
[[ATTR_LEAF]]
mempcpyb:([[nonnull]] /*aligned(1)*/ void *__restrict dst,
          [[nonnull]] /*aligned(1)*/ void const *__restrict src,
          $size_t n_bytes) -> [[== dst + n_bytes]] $uint8_t * = mempcpy;

@@Copy memory between non-overlapping memory blocks.
[[fast, libc, kernel, ATTR_LEAF]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("wmemcpy")]]
[[alias("DOS$wmemcpy")]]
[[if(!defined(__KERNEL__)), export_as("DOS$wmemcpy")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCPYW))]]
memcpyw:([[nonnull]] /*aligned(2)*/ void *__restrict dst,
         [[nonnull]] /*aligned(2)*/ void const *__restrict src,
         $size_t n_words) -> [[== dst]] $uint16_t * {
	u16 *pdst = (u16 *)dst;
	u16 *psrc = (u16 *)src;
	while (n_words--)
		*pdst++ = *psrc++;
	return (u16 *)dst;
}

@@Same as `memcpyw', but return `DST + N_WORDS', rather than `DST'
[[fast, libc, kernel, ATTR_LEAF]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("wmempcpy")]]
[[alias("DOS$wmempcpy")]]
[[if(!defined(__KERNEL__)), export_as("DOS$wmempcpy")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPCPYW))]]
mempcpyw:([[nonnull]] /*aligned(2)*/ void *__restrict dst,
          [[nonnull]] /*aligned(2)*/ void const *__restrict src,
          $size_t n_words) -> [== dst + n_words * 2] $uint16_t * {
	return (u16 *)memcpyw(dst, src, n_words) + n_words;
}

@@Copy memory between non-overlapping memory blocks.
[[fast, libc, kernel, ATTR_LEAF]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("wmemcpy")]]
[[if(defined(__PE__)), alias("KOS$wmemcpy")]]
[[if(!defined(__KERNEL__)), export_as("wmemcpy")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCPYL))]]
memcpyl:([[nonnull]] /*aligned(4)*/ void *__restrict dst,
         [[nonnull]] /*aligned(4)*/ void const *__restrict src,
         $size_t n_dwords) -> [[== dst]] $uint32_t * {
	u32 *pdst = (u32 *)dst;
	u32 *psrc = (u32 *)src;
	while (n_dwords--)
		*pdst++ = *psrc++;
	return (u32 *)dst;
}

@@Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST'
[[fast, libc, kernel, ATTR_LEAF]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("wmempcpy")]]
[[if(defined(__PE__)), alias("KOS$wmempcpy")]]
[[if(!defined(__KERNEL__)), export_as("wmempcpy")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPCPYL))]]
mempcpyl:([[nonnull]] /*aligned(4)*/ void *__restrict dst,
          [[nonnull]] /*aligned(4)*/ void const *__restrict src,
          $size_t n_dwords) -> [== dst + n_dwords * 4] $uint32_t * {
	return (u32 *)memcpyl(dst, src, n_dwords) + n_dwords;
}


@@Move memory between potentially overlapping memory blocks.
[[ATTR_LEAF]]
memmoveb:([[nonnull]] /*aligned(1)*/ void *dst,
          [[nonnull]] /*aligned(1)*/ void const *src,
          $size_t n_bytes) -> [[== dst]] $uint8_t * = memmove;

@@Same as `memmoveb', but return `DST + N_BYTES', rather than `DST'
[[ATTR_LEAF]]
mempmoveb:([[nonnull]] /*aligned(1)*/ void *dst,
           [[nonnull]] /*aligned(1)*/ void const *src,
           $size_t n_bytes) -> [[== dst + n_bytes]] $uint8_t * = mempmove;

@@Move memory between potentially overlapping memory blocks.
[[fast, libc, kernel, ATTR_LEAF]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("wmemmove")]]
[[alias("DOS$wmemmove")]]
[[if(!defined(__KERNEL__)), export_as("DOS$wmemmove")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEW))]]
memmovew:([[nonnull]] /*aligned(2)*/ void *dst,
          [[nonnull]] /*aligned(2)*/ void const *src,
          $size_t n_words) -> [[== dst]] $uint16_t * {
	u16 *pdst, *psrc;
	if (dst <= src) {
		pdst = (u16 *)dst;
		psrc = (u16 *)src;
		while (n_words--)
			*pdst++ = *psrc++;
	} else {
		pdst = (u16 *)dst + n_words;
		psrc = (u16 *)src + n_words;
		while (n_words--)
			*--pdst = *--psrc;
	}
	return (u16 *)dst;
}

@@Same as `memmovew', but return `DST + N_WORDS', rather than `DST'
[[fast, libc, kernel, ATTR_LEAF]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("wmempmove")]]
[[alias("DOS$wmempmove")]]
[[if(!defined(__KERNEL__)), export_as("DOS$wmempmove")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEW))]]
mempmovew:([[nonnull]] /*aligned(2)*/ void *dst,
           [[nonnull]] /*aligned(2)*/ void const *src,
           $size_t n_words) -> [== dst + n_words * 2] $uint16_t * {
	return (u16 *)memmovew(dst, src, n_words) + n_words;
}

@@Move memory between potentially overlapping memory blocks.
[[fast, libc, kernel, ATTR_LEAF]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("wmemmove")]]
[[if(defined(__PE__)), alias("KOS$wmemmove")]]
[[if(!defined(__KERNEL__)), export_as("wmemmove")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEL))]]
memmovel:([[nonnull]] /*aligned(4)*/ void *dst,
          [[nonnull]] /*aligned(4)*/ void const *src,
          $size_t n_dwords) -> [[== dst]] $uint32_t * {
	u32 *pdst, *psrc;
	if (dst <= src) {
		pdst = (u32 *)dst;
		psrc = (u32 *)src;
		while (n_dwords--)
			*pdst++ = *psrc++;
	} else {
		pdst = (u32 *)dst + n_dwords;
		psrc = (u32 *)src + n_dwords;
		while (n_dwords--)
			*--pdst = *--psrc;
	}
	return (u32 *)dst;
}

@@Same as `memmovew', but return `DST + N_DWORDS', rather than `DST'
[[fast, libc, kernel, ATTR_LEAF]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("wmempmove")]]
[[if(defined(__PE__)), alias("KOS$wmempmove")]]
[[if(!defined(__KERNEL__)), export_as("wmempmove")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEL))]]
mempmovel:([[nonnull]] /*aligned(4)*/ void *dst,
           [[nonnull]] /*aligned(4)*/ void const *src,
           $size_t n_dwords) -> [== dst + n_dwords * 4] $uint32_t * {
	return (u32 *)memmovel(dst, src, n_dwords) + n_dwords;
}

%#ifdef __USE_KOS
@@Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_BYTES')
[[ATTR_LEAF]]
memmoveupb:([[nonnull]] /*aligned(1)*/ void *dst,
            [[nonnull]] /*aligned(1)*/ void const *src,
            $size_t n_bytes) -> [[== dst]] $uint8_t * = memmoveup;

@@Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_BYTES')
[[ATTR_LEAF]]
memmovedownb:([[nonnull]] /*aligned(1)*/ void *dst,
              [[nonnull]] /*aligned(1)*/ void const *src,
              $size_t n_bytes) -> [[== dst]] $uint8_t * = memmovedown;

@@Same as `memmoveb', but return `DST + N_BYTES', rather than `DST' (assumes that `DST >= SRC || !N_BYTES')
[[ATTR_LEAF]]
mempmoveupb:([[nonnull]] /*aligned(1)*/ void *dst,
             [[nonnull]] /*aligned(1)*/ void const *src,
             $size_t n_bytes) -> [[== dst + n_bytes]] $uint8_t * = mempmoveup;

@@Same as `memmoveb', but return `DST + N_BYTES', rather than `DST' (assumes that `DST <= SRC || !N_BYTES')
[[ATTR_LEAF]]
mempmovedownb:([[nonnull]] /*aligned(1)*/ void *dst,
               [[nonnull]] /*aligned(1)*/ void const *src,
               $size_t n_bytes) -> [[== dst + n_bytes]] $uint8_t * = mempmovedown;

@@Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_WORDS')
[[fast, libc, kernel, ATTR_LEAF, alias("memmovew")]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("wmemmove")]]
[[alias("DOS$wmemmove")]]
[[impl_include("<hybrid/__assert.h>")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEUPW))]]
memmoveupw:([[nonnull]] /*aligned(2)*/ void *dst,
            [[nonnull]] /*aligned(2)*/ void const *src,
            $size_t n_words) -> [[== dst]] $uint16_t * {
	u16 *pdst, *psrc;
	pdst = (u16 *)dst + n_words;
	psrc = (u16 *)src + n_words;
	@__hybrid_assertf@(pdst >= psrc || !n_words, "%p < %p (count:%Iu)", dst, src, n_words);
	while (n_words--)
		*--pdst = *--psrc;
	return (u16 *)dst;
}

@@Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS')
[[fast, libc, kernel, ATTR_LEAF, alias("memmovew")]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("wmemmove")]]
[[alias("DOS$wmemmove")]]
[[impl_include("<hybrid/__assert.h>")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEDOWNW))]]
memmovedownw:([[nonnull]] /*aligned(2)*/ void *dst,
              [[nonnull]] /*aligned(2)*/ void const *src,
              $size_t n_words) -> [[== dst]] $uint16_t * {
	u16 *pdst, *psrc;
	pdst = (u16 *)dst;
	psrc = (u16 *)src;
	@__hybrid_assertf@(pdst <= psrc || !n_words, "%p > %p (count:%Iu)", dst, src, n_words);
	while (n_words--)
		*pdst++ = *psrc++;
	return (u16 *)dst;
}

@@Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST >= SRC || !N_WORDS')
[[fast, libc, kernel, ATTR_LEAF, alias("mempmovew")]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("wmempmove")]]
[[alias("DOS$wmempmove")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEUPW))]]
mempmoveupw:([[nonnull]] /*aligned(2)*/ void *dst,
             [[nonnull]] /*aligned(2)*/ void const *src,
             $size_t n_words) -> [== dst + n_words * 2] $uint16_t * {
	return (u16 *)memmoveupw(dst, src, n_words) + n_words;
}

@@Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST <= SRC || !N_WORDS')
[[fast, libc, kernel, ATTR_LEAF, alias("mempmovew")]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("wmempmove")]]
[[alias("DOS$wmempmove")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEDOWNW))]]
mempmovedownw:([[nonnull]] /*aligned(2)*/ void *dst,
               [[nonnull]] /*aligned(2)*/ void const *src,
               $size_t n_words) -> [== dst + n_words * 2] $uint16_t * {
	return (u16 *)memmovedownw(dst, src, n_words) + n_words;
}

@@Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS')
[[fast, libc, kernel, alias("memmovel"), ATTR_LEAF]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("wmemmove")]]
[[if(defined(__PE__)), alias("KOS$wmemmove")]]
[[impl_include("<hybrid/__assert.h>")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEUPL))]]
memmoveupl:([[nonnull]] /*aligned(4)*/ void *dst,
            [[nonnull]] /*aligned(4)*/ void const *src,
            $size_t n_dwords) -> [[== dst]] $uint32_t * {
	u32 *pdst, *psrc;
	pdst = (u32 *)dst + n_dwords;
	psrc = (u32 *)src + n_dwords;
	@__hybrid_assertf@(pdst >= psrc || !n_dwords, "%p < %p (count:%Iu)", dst, src, n_dwords);
	while (n_dwords--)
		*--pdst = *--psrc;
	return (u32 *)dst;
}

@@Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS')
[[fast, libc, kernel, ATTR_LEAF, alias("memmovel")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("wmemmove")]]
[[if(defined(__PE__)), alias("KOS$wmemmove")]]
[[impl_include("<hybrid/__assert.h>")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEDOWNL))]]
memmovedownl:([[nonnull]] /*aligned(4)*/ void *dst,
              [[nonnull]] /*aligned(4)*/ void const *src,
              $size_t n_dwords) -> [[== dst]] $uint32_t * {
	u32 *pdst, *psrc;
	pdst = (u32 *)dst;
	psrc = (u32 *)src;
	@__hybrid_assertf@(pdst <= psrc || !n_dwords, "%p > %p (count:%Iu)", dst, src, n_dwords);
	while (n_dwords--)
		*pdst++ = *psrc++;
	return (u32 *)dst;
}

@@Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST >= SRC || !N_DWORDS')
[[fast, libc, kernel, ATTR_LEAF, alias("mempmovel")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("wmempmove")]]
[[if(defined(__PE__)), alias("KOS$wmempmove")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEUPL))]]
mempmoveupl:([[nonnull]] /*aligned(4)*/ void *dst,
             [[nonnull]] /*aligned(4)*/ void const *src,
             $size_t n_dwords) -> [== dst + n_dwords * 4] $uint32_t * {
	return (u32 *)memmoveupl(dst, src, n_dwords) + n_dwords;
}

@@Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST <= SRC || !N_DWORDS')
[[fast, libc, kernel, ATTR_LEAF, alias("mempmovel")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("wmempmove")]]
[[if(defined(__PE__)), alias("KOS$wmempmove")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEDOWNL))]]
mempmovedownl:([[nonnull]] /*aligned(4)*/ void *dst,
               [[nonnull]] /*aligned(4)*/ void const *src,
               $size_t n_dwords) -> [== dst + n_dwords * 4] $uint32_t * {
	return (u32 *)memmovedownl(dst, src, n_dwords) + n_dwords;
}

%#endif /* __USE_KOS */


@@Fill memory with a given byte
[[ATTR_LEAF]]
memsetb:([[nonnull]] /*aligned(1)*/ void *__restrict dst,
         int byte, $size_t n_bytes) -> [[== dst]] $uint8_t * = memset;

@@Same as `memsetb', but return `DST + N_BYTES', rather than `DST'
[[ATTR_LEAF]]
mempsetb:([[nonnull]] /*aligned(1)*/ void *__restrict dst,
          int byte, $size_t n_bytes) -> [[== dst + n_bytes]] $uint8_t * = mempset;

@@Fill memory with a given word
[[fast, libc, kernel, ATTR_LEAF]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("wmemset")]]
[[alias("DOS$wmemset")]]
[[if(!defined(__KERNEL__)), export_as("DOS$wmemset")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMSETW))]]
memsetw:([[nonnull]] /*aligned(2)*/ void *__restrict dst,
         $uint16_t word, $size_t n_words) -> [[== dst]] $uint16_t * {
	u16 *pdst = (u16 *)dst;
	while (n_words--)
		*pdst++ = word;
	return (u16 *)dst;
}

@@Same as `memsetw', but return `DST + N_WORDS', rather than `DST'
[[fast, libc, kernel, ATTR_LEAF]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("wmempset")]]
[[alias("DOS$wmempset")]]
[[if(!defined(__KERNEL__)), export_as("DOS$wmempset")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPSETW))]]
mempsetw:([[nonnull]] /*aligned(2)*/ void *__restrict dst,
          $uint16_t word, $size_t n_words) -> [== dst + n_words * 2] $uint16_t * {
	return (u16 *)memsetw(dst, word, n_words) + n_words;
}

@@Fill memory with a given dword
[[fast, libc, kernel, ATTR_LEAF]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("wmemset")]]
[[if(defined(__PE__)), alias("KOS$wmemset")]]
[[if(!defined(__KERNEL__)), export_as("wmemset")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMSETL))]]
memsetl:([[nonnull]] /*aligned(4)*/ void *__restrict dst,
         $uint32_t dword, $size_t n_dwords) -> [[== dst]] $uint32_t * {
	u32 *pdst = (u32 *)dst;
	while (n_dwords--)
		*pdst++ = dword;
	return (u32 *)dst;
}

@@Same as `memsetl', but return `DST + N_DWORDS', rather than `DST'
[[fast, libc, kernel, ATTR_LEAF]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("wmempset")]]
[[if(defined(__PE__)), alias("KOS$wmempset")]]
[[if(!defined(__KERNEL__)), export_as("wmempset")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPSETL))]]
mempsetl:([[nonnull]] /*aligned(4)*/ void *__restrict dst,
          $uint32_t dword, $size_t n_dwords) -> [== dst + n_dwords * 4] $uint32_t * {
	return (u32 *)memsetl(dst, dword, n_dwords) + n_dwords;
}


@@Compare memory buffers and return the difference of the first non-matching byte
[[wunused, ATTR_PURE]]
int memcmpb([[nonnull]] /*aligned(1)*/ void const *s1,
            [[nonnull]] /*aligned(1)*/ void const *s2,
            $size_t n_bytes) = memcmp;

@@Compare memory buffers and return the difference of the first non-matching word
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("wmemcmp")]]
[[alias("DOS$wmemcmp")]]
[[if(!defined(__KERNEL__)), export_as("DOS$wmemcmp")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCMPW))]]
$int16_t memcmpw([[nonnull]] /*aligned(2)*/ void const *s1,
                 [[nonnull]] /*aligned(2)*/ void const *s2, $size_t n_words) {
	s16 *p1 = (s16 *)s1;
	s16 *p2 = (s16 *)s2;
	s16 v1, v2;
	v1 = v2 = 0;
	while (n_words-- && ((v1 = *p1++) == (v2 = *p2++)));
	return v1 - v2;
}

@@Compare memory buffers and return the difference of the first non-matching dword
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("wmemcmp")]]
[[if(defined(__PE__)), alias("KOS$wmemcmp")]]
[[if(!defined(__KERNEL__)), export_as("wmemcmp")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCMPL))]]
$int32_t memcmpl([[nonnull]] /*aligned(4)*/ void const *s1,
                 [[nonnull]] /*aligned(4)*/ void const *s2,
                 $size_t n_dwords) {
	s32 *p1 = (s32 *)s1;
	s32 *p2 = (s32 *)s2;
	s32 v1, v2;
	v1 = v2 = 0;
	while (n_dwords-- && ((v1 = *p1++) == (v2 = *p2++)));
	return v1 - v2;
}

@@Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found.
[[wunused, ATTR_PURE]]
$uint8_t *memchrb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte, $size_t n_bytes)
	[([[nonnull]] /*aligned(1)*/ void *__restrict haystack, int byte, $size_t n_bytes): $uint8_t *]
	[([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte, $size_t n_bytes): $uint8_t const *]
	= memchr;

@@Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found.
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("wmemchr")]]
[[alias("DOS$wmemchr")]]
[[if(!defined(__KERNEL__)), export_as("DOS$wmemchr")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCHRW))]]
$uint16_t *memchrw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word, $size_t n_words)
	[([[nonnull]] /*aligned(2)*/ void *__restrict haystack, $uint16_t word, $size_t n_words): $uint16_t *]
	[([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word, $size_t n_words): $uint16_t const *]
{
	u16 *hay_iter = (u16 *)haystack;
	for (; n_words--; ++hay_iter) {
		if unlikely(*hay_iter == word)
			return hay_iter;
	}
	return NULL;
}

@@Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found.
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("wmemchr")]]
[[if(defined(__PE__)), alias("KOS$wmemchr")]]
[[if(!defined(__KERNEL__)), export_as("wmemchr")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCHRL))]]
$uint32_t *memchrl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword, $size_t n_dwords)
	[([[nonnull]] /*aligned(4)*/ void *__restrict haystack, $uint32_t dword, $size_t n_dwords): $uint32_t *]
	[([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword, $size_t n_dwords): $uint32_t const *]
{
	u32 *hay_iter = (u32 *)haystack;
	for (; n_dwords--; ++hay_iter) {
		if unlikely(*hay_iter == dword)
			return hay_iter;
	}
	return NULL;
}

@@Descendingly search for `NEEDLE', starting at `HAYSTACK + N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found.
[[wunused, ATTR_PURE]]
$uint8_t *memrchrb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte, $size_t n_bytes)
	[([[nonnull]] /*aligned(1)*/ void *__restrict haystack, int byte, $size_t n_bytes): $uint8_t *]
	[([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte, $size_t n_bytes): $uint8_t const *]
	= memrchr;

@@Descendingly search for `NEEDLE', starting at `HAYSTACK + N_WORDS * 2'. - Return `NULL' if `NEEDLE' wasn't found.
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRCHRW))]]
$uint16_t *memrchrw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word, $size_t n_words)
	[([[nonnull]] /*aligned(2)*/ void *__restrict haystack, $uint16_t word, $size_t n_words): $uint16_t *]
	[([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word, $size_t n_words): $uint16_t const *]
{
	u16 *iter = (u16 *)haystack + n_words;
	while (n_words--) {
		if unlikely(*--iter == word)
			return iter;
	}
	return NULL;
}

@@Descendingly search for `NEEDLE', starting at `HAYSTACK + N_DWORDS * 4'. - Return `NULL' if `NEEDLE' wasn't found.
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRCHRL))]]
$uint32_t *memrchrl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword, $size_t n_dwords)
	[([[nonnull]] /*aligned(4)*/ void *__restrict haystack, $uint32_t dword, $size_t n_dwords): $uint32_t *]
	[([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword, $size_t n_dwords): $uint32_t const *]
{
	u32 *iter = (u32 *)haystack + n_dwords;
	while (n_dwords--) {
		if unlikely(*--iter == dword)
			return iter;
	}
	return NULL;
}

@@Same as `memchrb' with a search limit of `(size_t)-1'
[[wunused, ATTR_PURE]]
[[nonnull]] $uint8_t *rawmemchrb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte)
	[([[nonnull]] /*aligned(1)*/ void *__restrict haystack, int byte): [[nonnull]] $uint8_t *]
	[([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte): [[nonnull]] $uint8_t const *]
	= rawmemchr;

@@Same as `memchrw' with a search limit of `(size_t)-1 / 2'
[[kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMCHRW))]]
[[nonnull]] $uint16_t *rawmemchrw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word)
	[([[nonnull]] /*aligned(2)*/ void *__restrict haystack, $uint16_t word): [[nonnull]] $uint16_t *]
	[([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word): [[nonnull]] $uint16_t const *]
{
	u16 *iter = (u16 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter == word)
			break;
	}
	return iter;
}

@@Same as `memchrl' with a search limit of `(size_t)-1 / 4'
[[kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMCHRL))]]
[[nonnull]] $uint32_t *rawmemchrl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword)
	[([[nonnull]] /*aligned(4)*/ void *__restrict haystack, $uint32_t dword): [[nonnull]] $uint32_t *]
	[([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword): [[nonnull]] $uint32_t const *]
{
	u32 *iter = (u32 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter == dword)
			break;
	}
	return iter;
}


@@Same as `memrchrb' without a search limit, starting at `HAYSTACK - 1'
[[wunused, ATTR_PURE]]
[[nonnull]] $uint8_t *rawmemrchrb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte)
	[([[nonnull]] /*aligned(1)*/ void *__restrict haystack, int byte): [[nonnull]] $uint8_t *]
	[([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte): [[nonnull]] $uint8_t const *]
	= rawmemrchr;

@@Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK - 2'
[[kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRCHRW))]]
[[nonnull]] $uint16_t *rawmemrchrw:([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word)
	[([[nonnull]] /*aligned(2)*/ void *__restrict haystack, $uint16_t word): [[nonnull]] $uint16_t *]
	[([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word): [[nonnull]] $uint16_t const *]
{
	u16 *iter = (u16 *)haystack;
	for (;;) {
		if unlikely(*--iter == word)
			break;
	}
	return iter;
}

@@Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK - 4'
[[kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRCHRL))]]
[[nonnull]] $uint32_t *rawmemrchrl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword)
	[([[nonnull]] /*aligned(4)*/ void *__restrict haystack, $uint32_t dword): [[nonnull]] $uint32_t *]
	[([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword): [[nonnull]] $uint32_t const *]
{
	u32 *iter = (u32 *)haystack;
	for (;;) {
		if unlikely(*--iter == dword)
			break;
	}
	return iter;
}


@@Same as `memchrb', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found.
[[wunused, ATTR_PURE]]
[[nonnull]] $uint8_t *memendb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte, $size_t n_bytes)
	[([[nonnull]] /*aligned(1)*/ void *__restrict haystack, int byte, $size_t n_bytes): [[nonnull]] $uint8_t *]
	[([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte, $size_t n_bytes): [[nonnull]] $uint8_t const *]
	= memend;

@@Same as `memchrw', but return `HAYSTACK + N_WORDS * 2', rather than `NULL' if `NEEDLE' wasn't found.
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMENDW))]]
[[nonnull]] $uint16_t *memendw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word, $size_t n_bytes)
	[([[nonnull]] /*aligned(2)*/ void *__restrict haystack, $uint16_t word, $size_t n_bytes): [[nonnull]] $uint16_t *]
	[([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word, $size_t n_bytes): [[nonnull]] $uint16_t const *]
{
	u16 *result = (u16 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == word)
			break;
	}
	return result;
}

@@Same as `memchrl', but return `HAYSTACK + N_DWORDS * 4', rather than `NULL' if `NEEDLE' wasn't found.
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMENDL))]]
[[nonnull]] $uint32_t *memendl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword, $size_t n_bytes)
	[([[nonnull]] /*aligned(4)*/ void *__restrict haystack, $uint32_t dword, $size_t n_bytes): [[nonnull]] $uint32_t *]
	[([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword, $size_t n_bytes): [[nonnull]] $uint32_t const *]
{
	u32 *result = (u32 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == dword)
			break;
	}
	return result;
}

@@Same as `memrchrb', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found.
[[wunused, ATTR_PURE]]
[[nonnull]] $uint8_t *memrendb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte, $size_t n_bytes)
	[([[nonnull]] /*aligned(1)*/ void *__restrict haystack, int byte, $size_t n_bytes): [[nonnull]] $uint8_t *]
	[([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte, $size_t n_bytes): [[nonnull]] $uint8_t const *]
	= memrend;

@@Same as `memrchrw', but return `HAYSTACK - 2', rather than `NULL' if `NEEDLE' wasn't found.
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRENDW))]]
[[nonnull]] $uint16_t *memrendw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word, $size_t n_words)
	[([[nonnull]] /*aligned(2)*/ void *__restrict haystack, $uint16_t word, $size_t n_words): [[nonnull]] $uint16_t *]
	[([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word, $size_t n_words): [[nonnull]] $uint16_t const *]
{
	u16 *result = (u16 *)haystack + n_words;
	for (;;) {
		--result;
		if unlikely(!n_words)
			break;
		if unlikely(*result == word)
			break;
		--n_words;
	}
	return result;
}

@@Same as `memrchrl', but return `HAYSTACK - 4', rather than `NULL' if `NEEDLE' wasn't found.
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRENDL))]]
[[nonnull]] $uint32_t *memrendl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword, $size_t n_dwords)
	[([[nonnull]] /*aligned(4)*/ void *__restrict haystack, $uint32_t dword, $size_t n_dwords): [[nonnull]] $uint32_t *]
	[([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword, $size_t n_dwords): [[nonnull]] $uint32_t const *]
{
	u32 *result = (u32 *)haystack + n_dwords;
	for (;;) {
		--result;
		if unlikely(!n_dwords)
			break;
		if unlikely(*result == dword)
			break;
		--n_dwords;
	}
	return result;
}



@@Same as `memendb', but return the offset from `HAYSTACK', rather than the actual address.
@@Returns `HAYSTACK + N_DWORDS' if the given `NEEDLE' wasn't found
[[wunused, ATTR_PURE]]
$size_t memlenb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack,
                int byte, $size_t n_bytes) = memlen;

@@Same as `memendw', but return the offset from `HAYSTACK', rather than the actual address.
@@Returns `HAYSTACK + N_DWORDS * 2' if the given `NEEDLE' wasn't found
[[kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMLENW))]]
$size_t memlenw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack,
                $uint16_t word, $size_t n_words) {
	return (size_t)(memendw(haystack, word, n_words) - (u16 *)haystack);
}

@@Same as `memendl', but return the offset from `HAYSTACK', rather than the actual address.
@@Returns `HAYSTACK + N_DWORDS * 4' if the given `NEEDLE' wasn't found
[[kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMLENL))]]
$size_t memlenl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack,
                $uint32_t dword, $size_t n_dwords) {
	return (size_t)(memendl(haystack, dword, n_dwords) - (u32 *)haystack);
}

@@Same as `memrendb', but return the offset from `HAYSTACK', rather than the actual address.
@@Returns `(size_t)-1' if the given `NEEDLE' wasn't found
[[wunused, ATTR_PURE]]
$size_t memrlenb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack,
                 int byte, $size_t n_bytes) = memrlen;

@@Same as `memrendw', but return the offset from `HAYSTACK', rather than the actual address.
@@Returns `(size_t)-1 / 2' if the given `NEEDLE' wasn't found
[[kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRLENW))]]
$size_t memrlenw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack,
                 $uint16_t word, $size_t n_words) {
	return (size_t)(memrendw(haystack, word, n_words) - (u16 *)haystack);
}

@@Same as `memrendl', but return the offset from `HAYSTACK', rather than the actual address.
@@Returns `(size_t)-1 / 4' if the given `NEEDLE' wasn't found
[[kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRLENL))]]
$size_t memrlenl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack,
                 $uint32_t dword, $size_t n_dwords) {
	return (size_t)(memrendl(haystack, dword, n_dwords) - (u32 *)haystack);
}



@@Same as `rawmemchrb', but return the offset from `HAYSTACK', rather than the actual address.
[[wunused, ATTR_PURE]]
$size_t rawmemlenb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack,
                   int needle) = rawmemlen;

@@Same as `rawmemchrw', but return the offset from `HAYSTACK', rather than the actual address.
[[kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMLENW))]]
$size_t rawmemlenw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word) {
	return (size_t)(rawmemchrw(haystack, word) - (u16 *)haystack);
}

@@Same as `rawmemchrl', but return the offset from `HAYSTACK', rather than the actual address.
[[kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMLENL))]]
$size_t rawmemlenl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword) {
	return (size_t)(rawmemchrl(haystack, dword) - (u32 *)haystack);
}


@@Same as `rawmemrchrb', but return the offset from `HAYSTACK', rather than the actual address.
[[wunused, ATTR_PURE]]
$size_t rawmemrlenb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack,
                    int needle) = rawmemrlen;

@@Same as `rawmemrchrw', but return the offset from `HAYSTACK', rather than the actual address.
[[kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRLENW))]]
$size_t rawmemrlenw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word) {
	return (size_t)(rawmemrchrw(haystack, word) - (u16 *)haystack);
}

@@Same as `rawmemrchrl', but return the offset from `HAYSTACK', rather than the actual address.
[[kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRLENL))]]
$size_t rawmemrlenl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword) {
	return (size_t)(rawmemrchrl(haystack, dword) - (u32 *)haystack);
}



%#ifdef __UINT64_TYPE__
@@Copy memory between non-overlapping memory blocks.
[[fast, libc, kernel, ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCPYQ))]]
memcpyq:([[nonnull]] /*aligned(8)*/ void *__restrict dst,
         [[nonnull]] /*aligned(8)*/ void const *__restrict src,
         $size_t n_qwords) -> [[== dst]] $uint64_t * {
#if __SIZEOF_POINTER__ >= 8
	u64 *pdst = (u64 *)dst;
	u64 *psrc = (u64 *)src;
	while (n_qwords--)
		*pdst++ = *psrc++;
#else /* __SIZEOF_POINTER__ >= 8 */
	u32 *pdst = (u32 *)dst;
	u32 *psrc = (u32 *)src;
	while (n_qwords--) {
		*pdst++ = *psrc++;
		*pdst++ = *psrc++;
	}
#endif /* __SIZEOF_POINTER__ < 8 */
	return (u64 *)dst;
}

@@Same as `memcpyq', but return `DST + N_QWORDS', rather than `DST'
[[fast, libc, kernel, ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPCPYQ))]]
mempcpyq:([[nonnull]] /*aligned(8)*/ void *__restrict dst,
          [[nonnull]] /*aligned(8)*/ void const *__restrict src,
          $size_t n_qwords) -> [[== dst + n_qwords * 8]] $uint64_t * {
	return (u64 *)memcpyq(dst, src, n_qwords) + n_qwords;
}

@@Move memory between potentially overlapping memory blocks.
[[fast, libc, kernel, ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEQ))]]
memmoveq:([[nonnull]] /*aligned(8)*/ void *dst,
          [[nonnull]] /*aligned(8)*/ void const *src,
          $size_t n_qwords) -> [[== dst]] $uint64_t * {
#if __SIZEOF_POINTER__ >= 8
	u64 *pdst, *psrc;
	if (dst <= src) {
		pdst = (u64 *)dst;
		psrc = (u64 *)src;
		while (n_qwords--)
			*pdst++ = *psrc++;
	} else {
		pdst = (u64 *)dst + n_qwords;
		psrc = (u64 *)src + n_qwords;
		while (n_qwords--)
			*--pdst = *--psrc;
	}
#else /* __SIZEOF_POINTER__ >= 8 */
	u32 *pdst, *psrc;
	if (dst <= src) {
		pdst = (u32 *)dst;
		psrc = (u32 *)src;
		while (n_qwords--) {
			*pdst++ = *psrc++;
			*pdst++ = *psrc++;
		}
	} else {
		pdst = (u32 *)dst + (n_qwords * 2);
		psrc = (u32 *)src + (n_qwords * 2);
		while (n_qwords--) {
			*--pdst = *--psrc;
			*--pdst = *--psrc;
		}
	}
#endif /* __SIZEOF_POINTER__ < 8 */
	return (u64 *)dst;
}

@@Same as `memmovew', but return `DST + N_QWORDS', rather than `DST'
[[fast, libc, kernel, ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEQ))]]
mempmoveq:([[nonnull]] /*aligned(8)*/ void *__restrict dst,
           [[nonnull]] /*aligned(8)*/ void const *__restrict src,
           $size_t n_qwords) -> [[== dst + n_qwords * 8]] $uint64_t * {
	return (u64 *)memmoveq(dst, src, n_qwords) + n_qwords;
}

%#ifdef __USE_KOS

@@Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_QWORDS')
[[fast, libc, kernel, ATTR_LEAF, alias("memmoveq")]]
[[impl_include("<hybrid/__assert.h>")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEUPQ))]]
memmoveupq:([[nonnull]] /*aligned(8)*/ void *dst,
            [[nonnull]] /*aligned(8)*/ void const *src,
            $size_t n_qwords) -> [[== dst]] $uint64_t * {
#if __SIZEOF_POINTER__ >= 8
	u64 *pdst, *psrc;
	pdst = (u64 *)dst + n_qwords;
	psrc = (u64 *)src + n_qwords;
	@__hybrid_assertf@(pdst >= psrc || !n_qwords, "%p < %p (count:%Iu)", dst, src, n_qwords);
	while (n_qwords--)
		*--pdst = *--psrc;
#else /* __SIZEOF_POINTER__ >= 8 */
	u32 *pdst, *psrc;
	pdst = (u32 *)dst + (n_qwords * 2);
	psrc = (u32 *)src + (n_qwords * 2);
	@__hybrid_assertf@(pdst >= psrc || !n_qwords, "%p < %p (count:%Iu)", dst, src, n_qwords);
	while (n_qwords--) {
		*--pdst = *--psrc;
		*--pdst = *--psrc;
	}
#endif /* __SIZEOF_POINTER__ < 8 */
	return (u64 *)dst;
}

@@Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_QWORDS')
[[fast, libc, kernel, ATTR_LEAF, alias("memmoveq")]]
[[impl_include("<hybrid/__assert.h>")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEDOWNQ))]]
memmovedownq:([[nonnull]] /*aligned(8)*/ void *dst,
              [[nonnull]] /*aligned(8)*/ void const *src,
              $size_t n_qwords) -> [[== dst]] $uint64_t * {
#if __SIZEOF_POINTER__ >= 8
	u64 *pdst, *psrc;
	pdst = (u64 *)dst;
	psrc = (u64 *)src;
	@__hybrid_assertf@(pdst <= psrc || !n_qwords, "%p > %p (count:%Iu)", dst, src, n_qwords);
	while (n_qwords--)
		*pdst++ = *psrc++;
#else /* __SIZEOF_POINTER__ >= 8 */
	u32 *pdst, *psrc;
	pdst = (u32 *)dst;
	psrc = (u32 *)src;
	@__hybrid_assertf@(pdst <= psrc || !n_qwords, "%p > %p (count:%Iu)", dst, src, n_qwords);
	while (n_qwords--) {
		*pdst++ = *psrc++;
		*pdst++ = *psrc++;
	}
#endif /* __SIZEOF_POINTER__ < 8 */
	return (u64 *)dst;
}

@@Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST >= SRC || !N_QWORDS')
[[fast, libc, kernel, ATTR_LEAF, alias("mempmoveq")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEUPQ))]]
mempmoveupq:([[nonnull]] /*aligned(8)*/ void *__restrict dst,
             [[nonnull]] /*aligned(8)*/ void const *__restrict src,
             $size_t n_qwords) -> [[== dst + n_qwords * 8]] $uint64_t * {
	return (u64 *)memmoveupq(dst, src, n_qwords) + n_qwords;
}

@@Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST <= SRC || !N_QWORDS')
[[fast, libc, kernel, ATTR_LEAF, alias("mempmoveq")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEDOWNQ))]]
mempmovedownq:([[nonnull]] /*aligned(8)*/ void *__restrict dst,
               [[nonnull]] /*aligned(8)*/ void const *__restrict src,
               $size_t n_qwords) -> [[== dst + n_qwords * 8]] $uint64_t * {
	return (u64 *)memmovedownq(dst, src, n_qwords) + n_qwords;
}

%#endif /* __USE_KOS */


@@Fill memory with a given qword
[[fast, libc, kernel, ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMSETQ))]]
memsetq:([[nonnull]] /*aligned(8)*/ void *__restrict dst,
         $uint64_t qword, $size_t n_qwords) -> [[== dst]] $uint64_t * {
	u64 *pdst = (u64 *)dst;
	while (n_qwords--)
		*pdst++ = qword;
	return (u64 *)dst;
}

@@Same as `memsetq', but return `DST + N_QWORDS', rather than `DST'
[[fast, libc, kernel, ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPSETQ))]]
mempsetq:([[nonnull]] /*aligned(8)*/ void *__restrict dst,
          $uint64_t qword, $size_t n_qwords) -> [[== dst + n_qwords * 8]] $uint64_t * {
	return (u64 *)memsetq(dst, qword, n_qwords) + n_qwords;
}

@@Compare memory buffers and return the difference of the first non-matching qword
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCMPQ))]]
$int64_t memcmpq([[nonnull]] /*aligned(8)*/ void const *s1,
                 [[nonnull]] /*aligned(8)*/ void const *s2, $size_t n_dwords) {
	s64 *p1 = (s64 *)s1;
	s64 *p2 = (s64 *)s2;
	s64 v1, v2;
	v1 = v2 = 0;
	while (n_dwords-- && ((v1 = *p1++) == (v2 = *p2++)));
	return v1 - v2;
}

@@Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found.
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMCHRQ))]]
$uint64_t *memchrq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword, $size_t n_qwords)
	[([[nonnull]] /*aligned(8)*/ void *__restrict haystack, $uint64_t qword, $size_t n_qwords): $uint64_t *]
	[([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword, $size_t n_qwords): $uint64_t const *]
{
	u64 *hay_iter = (u64 *)haystack;
	for (; n_qwords--; ++hay_iter) {
		if unlikely(*hay_iter == (u64)qword)
			return hay_iter;
	}
	return NULL;
}

@@Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found.
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRCHRQ))]]
$uint64_t *memrchrq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword, $size_t n_qwords)
	[([[nonnull]] /*aligned(8)*/ void *__restrict haystack, $uint64_t qword, $size_t n_qwords): $uint64_t *]
	[([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword, $size_t n_qwords): $uint64_t const *]
{
	u64 *iter = (u64 *)haystack + n_qwords;
	while (n_qwords--) {
		if unlikely(*--iter == qword)
			return iter;
	}
	return NULL;
}

@@Same as `memchrq' with a search limit of `(size_t)-1 / 8'
[[kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMCHRQ))]]
[[nonnull]] $uint64_t *rawmemchrq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword)
	[([[nonnull]] /*aligned(8)*/ void *__restrict haystack, $uint64_t qword): [[nonnull]] $uint64_t *]
	[([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword): [[nonnull]] $uint64_t const *]
{
	u64 *iter = (u64 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter == qword)
			break;
	}
	return iter;
}

@@Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK - 8'
[[kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRCHRQ))]]
[[nonnull]] $uint64_t *rawmemrchrq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword)
	[([[nonnull]] /*aligned(8)*/ void *__restrict haystack, $uint64_t qword): [[nonnull]] $uint64_t *]
	[([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword): [[nonnull]] $uint64_t const *]
{
	u64 *iter = (u64 *)haystack;
	for (;;) {
		if unlikely(*--iter == qword)
			break;
	}
	return iter;
}

@@Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found.
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMENDQ))]]
[[nonnull]] $uint64_t *memendq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword, $size_t n_bytes)
	[([[nonnull]] /*aligned(8)*/ void *__restrict haystack, $uint64_t qword, $size_t n_bytes): [[nonnull]] $uint64_t *]
	[([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword, $size_t n_bytes): [[nonnull]] $uint64_t const *]
{
	u64 *result = (u64 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == qword)
			break;
	}
	return result;
}

@@Same as `memrchrq', but return `HAYSTACK - 8', rather than `NULL' if `NEEDLE' wasn't found.
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRENDQ))]]
[[nonnull]] $uint64_t *memrendq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword, $size_t n_qwords)
	[([[nonnull]] /*aligned(8)*/ void *__restrict haystack, $uint64_t qword, $size_t n_qwords): [[nonnull]] $uint64_t *]
	[([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword, $size_t n_qwords): [[nonnull]] $uint64_t const *]
{
	u64 *result = (u64 *)haystack + n_qwords;
	for (;;) {
		--result;
		if unlikely(!n_qwords)
			break;
		if unlikely(*result == qword)
			break;
		--n_qwords;
	}
	return result;
}

@@Same as `memendq', but return the offset from `HAYSTACK', rather than the actual address.
@@Returns `N_QWORDS' if the given `NEEDLE' wasn't found
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMLENQ))]]
$size_t memlenq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack,
                $uint64_t qword, $size_t n_qwords) {
	return (size_t)(memendq(haystack, qword, n_qwords) - (u64 *)haystack);
}

@@Same as `memrendq', but return the offset from `HAYSTACK', rather than the actual address.
@@Returns `(size_t)-1 / 8' if the given `NEEDLE' wasn't found
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRLENQ))]]
$size_t memrlenq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack,
                 $uint64_t qword, $size_t n_qwords) {
	return (size_t)(memrendq(haystack, qword, n_qwords) - (u64 *)haystack);
}

@@Same as `rawmemchrq', but return the offset from `HAYSTACK', rather than the actual address.
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMLENQ))]]
$size_t rawmemlenq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword) {
	return (size_t)(rawmemchrq(haystack, qword) - (u64 *)haystack);
}

@@Same as `rawmemrchrq', but return the offset from `HAYSTACK', rather than the actual address.
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRLENQ))]]
$size_t rawmemrlenq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword) {
	return (size_t)(rawmemrchrq(haystack, qword) - (u64 *)haystack);
}


%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_STRING_BWLQ */
%
%
%#ifdef __USE_STRING_XCHR


@@Same as `memchr', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXCHR))]]
void *memxchr([[nonnull]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[nonnull]] void *__restrict haystack, int needle, $size_t n_bytes): void *]
	[([[nonnull]] void const *__restrict haystack, int needle, $size_t n_bytes): void const *]
{
	byte_t *hay_iter = (byte_t *)haystack;
	for (; n_bytes--; ++hay_iter) {
		if unlikely(*hay_iter != (byte_t)needle)
			return hay_iter;
	}
	return NULL;
}

@@Same as `memrchr', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXCHR))]]
void *memrxchr([[nonnull]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[nonnull]] void *__restrict haystack, int needle, $size_t n_bytes): void *]
	[([[nonnull]] void const *__restrict haystack, int needle, $size_t n_bytes): void const *]
{
	byte_t *iter = (byte_t *)haystack + n_bytes;
	while (n_bytes--) {
		if unlikely(*--iter != (byte_t)needle)
			return iter;
	}
	return NULL;
}


@@Same as `rawmemchr', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMXCHR))]]
[[nonnull]] void *rawmemxchr([[nonnull]] void const *__restrict haystack, int needle)
	[([[nonnull]] void *__restrict haystack, int needle): [[nonnull]] void *]
	[([[nonnull]] void const *__restrict haystack, int needle): [[nonnull]] void const *]
{
	byte_t *iter = (byte_t *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != (byte_t)needle)
			break;
	}
	return iter;
}

@@Same as `rawmemrchr', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRXCHR))]]
[[nonnull]] void *rawmemrxchr([[nonnull]] void const *__restrict haystack, int needle)
	[([[nonnull]] void *__restrict haystack, int needle): [[nonnull]] void *]
	[([[nonnull]] void const *__restrict haystack, int needle): [[nonnull]] void const *]
{
	byte_t *iter = (byte_t *)haystack;
	for (;;) {
		if unlikely(*--iter != (byte_t)needle)
			break;
	}
	return iter;
}

@@Same as `memend', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXEND))]]
[[nonnull]] void *memxend([[nonnull]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[nonnull]] void *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] void *]
	[([[nonnull]] void const *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] void const *]
{
	byte_t *result = (byte_t *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != (byte_t)needle)
			break;
	}
	return result;
}

@@Same as `memrend', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXEND))]]
[[nonnull]] void *memrxend([[nonnull]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[nonnull]] void *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] void *]
	[([[nonnull]] void const *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] void const *]
{
	byte_t *result = (byte_t *)haystack + n_bytes;
	while (n_bytes--) {
		if unlikely(*--result != (byte_t)needle)
			break;
	}
	return result;
}

@@Same as `memlen', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXLEN))]]
$size_t memxlen([[nonnull]] void const *__restrict haystack, int needle, $size_t n_bytes) {
	return (size_t)((byte_t *)memxend(haystack, needle, n_bytes) - (byte_t *)haystack);
}

@@Same as `memrlen', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXLEN))]]
$size_t memrxlen([[nonnull]] void const *__restrict haystack, int needle, $size_t n_bytes) {
	return (size_t)((byte_t *)memrxend(haystack, needle, n_bytes) - (byte_t *)haystack);
}

@@Same as `rawmemlen', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMXLEN))]]
$size_t rawmemxlen([[nonnull]] void const *__restrict haystack, int needle) {
	return (size_t)((byte_t *)rawmemxchr(haystack, needle) - (byte_t *)haystack);
}

@@Same as `rawmemrlen', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRXLEN))]]
$size_t rawmemrxlen([[nonnull]] void const *__restrict haystack, int needle) {
	return (size_t)((byte_t *)rawmemrxchr(haystack, needle) - (byte_t *)haystack);
}



%#ifdef __USE_STRING_BWLQ

@@Same as `memchrb', but search for non-matching locations.
[[wunused, ATTR_PURE]]
$uint8_t *memxchrb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte, $size_t n_bytes)
	[([[nonnull]] /*aligned(1)*/ void *__restrict haystack, int byte, $size_t n_bytes): $uint8_t *]
	[([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte, $size_t n_bytes): $uint8_t const *]
	= memxchr;

@@Same as `memchrw', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXCHRW))]]
$uint16_t *memxchrw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word, $size_t n_words)
	[([[nonnull]] /*aligned(2)*/ void *__restrict haystack, $uint16_t word, $size_t n_words): $uint16_t *]
	[([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word, $size_t n_words): $uint16_t const *]
{
	u16 *hay_iter = (u16 *)haystack;
	for (; n_words--; ++hay_iter) {
		if unlikely(*hay_iter != word)
			return hay_iter;
	}
	return NULL;
}

@@Same as `memchrl', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXCHRL))]]
$uint32_t *memxchrl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword, $size_t n_dwords)
	[([[nonnull]] /*aligned(4)*/ void *__restrict haystack, $uint32_t dword, $size_t n_dwords): $uint32_t *]
	[([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword, $size_t n_dwords): $uint32_t const *]
{
	u32 *hay_iter = (u32 *)haystack;
	for (; n_dwords--; ++hay_iter) {
		if unlikely(*hay_iter != dword)
			return hay_iter;
	}
	return NULL;
}

@@Same as `memrchrb', but search for non-matching locations.
[[wunused, ATTR_PURE]]
$uint8_t *memrxchrb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte, $size_t n_bytes)
	[([[nonnull]] /*aligned(1)*/ void *__restrict haystack, int byte, $size_t n_bytes): $uint8_t *]
	[([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte, $size_t n_bytes): $uint8_t const *]
	= memrxchr;

@@Same as `memrchrw', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXCHRW))]]
$uint16_t *memrxchrw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word, $size_t n_words)
	[([[nonnull]] /*aligned(2)*/ void *__restrict haystack, $uint16_t word, $size_t n_words): $uint16_t *]
	[([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word, $size_t n_words): $uint16_t const *]
{
	u16 *iter = (u16 *)haystack + n_words;
	while (n_words--) {
		if unlikely(*--iter != word)
			return iter;
	}
	return NULL;
}

@@Same as `memrchrl', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXCHRL))]]
$uint32_t *memrxchrl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword, $size_t n_dwords)
	[([[nonnull]] /*aligned(4)*/ void *__restrict haystack, $uint32_t dword, $size_t n_dwords): $uint32_t *]
	[([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword, $size_t n_dwords): $uint32_t const *]
{
	u32 *iter = (u32 *)haystack + n_dwords;
	while (n_dwords--) {
		if unlikely(*--iter != dword)
			return iter;
	}
	return NULL;
}

@@Same as `rawmemchrb', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[nonnull]] $uint8_t *rawmemxchrb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte)
	[([[nonnull]] /*aligned(1)*/ void *__restrict haystack, int byte): [[nonnull]] $uint8_t *]
	[([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte): [[nonnull]] $uint8_t const *]
	= rawmemxchr;

@@Same as `rawmemchrw', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMXCHRW))]]
[[nonnull]] $uint16_t *rawmemxchrw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word)
	[([[nonnull]] /*aligned(2)*/ void *__restrict haystack, $uint16_t word): [[nonnull]] $uint16_t *]
	[([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word): [[nonnull]] $uint16_t const *]
{
	u16 *iter = (u16 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != word)
			break;
	}
	return iter;
}

@@Same as `rawmemchrl', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMXCHRL))]]
[[nonnull]] $uint32_t *rawmemxchrl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword)
	[([[nonnull]] /*aligned(4)*/ void *__restrict haystack, $uint32_t dword): [[nonnull]] $uint32_t *]
	[([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword): [[nonnull]] $uint32_t const *]
{
	u32 *iter = (u32 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != dword)
			break;
	}
	return iter;
}


@@Same as `rawmemrchrb', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[nonnull]] $uint8_t *rawmemrxchrb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte)
	[([[nonnull]] /*aligned(1)*/ void *__restrict haystack, int byte): [[nonnull]] $uint8_t *]
	[([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte): [[nonnull]] $uint8_t const *]
	= rawmemrxchr;

@@Same as `rawmemrchrw', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRXCHRW))]]
[[nonnull]] $uint16_t *rawmemrxchrw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word)
	[([[nonnull]] /*aligned(2)*/ void *__restrict haystack, $uint16_t word): [[nonnull]] $uint16_t *]
	[([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word): [[nonnull]] $uint16_t const *]
{
	u16 *iter = (u16 *)haystack;
	for (;;) {
		if unlikely(*--iter != word)
			break;
	}
	return iter;
}

@@Same as `rawmemrchrl', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRXCHRL))]]
[[nonnull]] $uint32_t *rawmemrxchrl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword)
	[([[nonnull]] /*aligned(4)*/ void *__restrict haystack, $uint32_t dword): [[nonnull]] $uint32_t *]
	[([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword): [[nonnull]] $uint32_t const *]
{
	u32 *iter = (u32 *)haystack;
	for (;;) {
		if unlikely(*--iter != dword)
			break;
	}
	return iter;
}


@@Same as `memendb', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[nonnull]] $uint8_t *memxendb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte, $size_t n_bytes)
	[([[nonnull]] /*aligned(1)*/ void *__restrict haystack, int byte, $size_t n_bytes): [[nonnull]] $uint8_t *]
	[([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte, $size_t n_bytes): [[nonnull]] $uint8_t const *]
	= memxend;

@@Same as `memendw', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXENDW))]]
[[nonnull]] $uint16_t *memxendw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word, $size_t n_bytes)
	[([[nonnull]] /*aligned(2)*/ void *__restrict haystack, $uint16_t word, $size_t n_bytes): [[nonnull]] $uint16_t *]
	[([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word, $size_t n_bytes): [[nonnull]] $uint16_t const *]
{
	u16 *result = (u16 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != word)
			break;
	}
	return result;
}

@@Same as `memendl', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXENDL))]]
[[nonnull]] $uint32_t *memxendl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword, $size_t n_bytes)
	[([[nonnull]] /*aligned(4)*/ void *__restrict haystack, $uint32_t dword, $size_t n_bytes): [[nonnull]] $uint32_t *]
	[([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword, $size_t n_bytes): [[nonnull]] $uint32_t const *]
{
	u32 *result = (u32 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != dword)
			break;
	}
	return result;
}


@@Same as `memrendb', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[nonnull]] $uint8_t *memrxendb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte, $size_t n_bytes)
	[([[nonnull]] /*aligned(1)*/ void *__restrict haystack, int byte, $size_t n_bytes): [[nonnull]] $uint8_t *]
	[([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte, $size_t n_bytes): [[nonnull]] $uint8_t const *]
	= memrxend;

@@Same as `memrendw', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXENDW))]]
[[nonnull]] $uint16_t *memrxendw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word, $size_t n_words)
	[([[nonnull]] /*aligned(2)*/ void *__restrict haystack, $uint16_t word, $size_t n_words): [[nonnull]] $uint16_t *]
	[([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word, $size_t n_words): [[nonnull]] $uint16_t const *]
{
	u16 *result = (u16 *)haystack + n_words;
	while (n_words--) {
		if unlikely(*--result != word)
			break;
	}
	return result;
}

@@Same as `memrendl', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXENDL))]]
[[nonnull]] $uint32_t *memrxendl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword, $size_t n_dwords)
	[([[nonnull]] /*aligned(4)*/ void *__restrict haystack, $uint32_t dword, $size_t n_dwords): [[nonnull]] $uint32_t *]
	[([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword, $size_t n_dwords): [[nonnull]] $uint32_t const *]
{
	u32 *result = (u32 *)haystack + n_dwords;
	while (n_dwords--) {
		if unlikely(*--result != dword)
			break;
	}
	return result;
}



@@Same as `memlenb', but search for non-matching locations.
[[wunused, ATTR_PURE]]
$size_t memxlenb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte, $size_t n_bytes) = memxlen;

@@Same as `memlenw', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXLENW))]]
$size_t memxlenw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word, $size_t n_words) {
	return (size_t)(memxendw(haystack, word, n_words) - (u16 *)haystack);
}

@@Same as `memlenl', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXLENL))]]
$size_t memxlenl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword, $size_t n_dwords) {
	return (size_t)(memxendl(haystack, dword, n_dwords) - (u32 *)haystack);
}

@@Same as `memrlenb', but search for non-matching locations.
[[wunused, ATTR_PURE]]
$size_t memrxlenb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int byte, $size_t n_bytes) = memrxlen;

@@Same as `memrlenw', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXLENW))]]
$size_t memrxlenw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word, $size_t n_words) {
	return (size_t)(memrxendw(haystack, word, n_words) - (u16 *)haystack);
}

@@Same as `memrlenl', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXLENL))]]
$size_t memrxlenl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword, $size_t n_dwords) {
	return (size_t)(memrxendl(haystack, dword, n_dwords) - (u32 *)haystack);
}



@@Same as `rawmemlenb', but search for non-matching locations.
[[wunused, ATTR_PURE]]
$size_t rawmemxlenb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int needle) = rawmemxlen;

@@Same as `rawmemlenw', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMXLENW))]]
$size_t rawmemxlenw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word) {
	return (size_t)(rawmemxchrw(haystack, word) - (u16 *)haystack);
}

@@Same as `rawmemlenl', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMXLENL))]]
$size_t rawmemxlenl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword) {
	return (size_t)(rawmemxchrl(haystack, dword) - (u32 *)haystack);
}


@@Same as `rawmemrlenb', but search for non-matching locations.
[[wunused, ATTR_PURE]]
$size_t rawmemrxlenb([[nonnull]] /*aligned(1)*/ void const *__restrict haystack, int needle) = rawmemrxlen;

@@Same as `rawmemrlenw', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRXLENW))]]
$size_t rawmemrxlenw([[nonnull]] /*aligned(2)*/ void const *__restrict haystack, $uint16_t word) {
	return (size_t)(rawmemrxchrw(haystack, word) - (u16 *)haystack);
}

@@Same as `rawmemrlenl', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRXLENL))]]
$size_t rawmemrxlenl([[nonnull]] /*aligned(4)*/ void const *__restrict haystack, $uint32_t dword) {
	return (size_t)(rawmemrxchrl(haystack, dword) - (u32 *)haystack);
}



%#ifdef __UINT64_TYPE__

@@Same as `memchrq', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXCHRQ))]]
$uint64_t *memxchrq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword, $size_t n_qwords)
	[([[nonnull]] /*aligned(8)*/ void *__restrict haystack, $uint64_t qword, $size_t n_qwords): $uint64_t *]
	[([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword, $size_t n_qwords): $uint64_t const *]
{
	u64 *hay_iter = (u64 *)haystack;
	for (; n_qwords--; ++hay_iter) {
		if unlikely(*hay_iter != (u64)qword)
			return hay_iter;
	}
	return NULL;
}

@@Same as `memrchrq', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXCHRQ))]]
$uint64_t *memrxchrq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword, $size_t n_qwords)
	[([[nonnull]] /*aligned(8)*/ void *__restrict haystack, $uint64_t qword, $size_t n_qwords): $uint64_t *]
	[([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword, $size_t n_qwords): $uint64_t const *]
{
	u64 *iter = (u64 *)haystack + n_qwords;
	while (n_qwords--) {
		if unlikely(*--iter != qword)
			return iter;
	}
	return NULL;
}

@@Same as `rawmemchrq', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMXCHRQ))]]
[[nonnull]] $uint64_t *rawmemxchrq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword)
	[([[nonnull]] /*aligned(8)*/ void *__restrict haystack, $uint64_t qword): [[nonnull]] $uint64_t *]
	[([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword): [[nonnull]] $uint64_t const *]
{
	u64 *iter = (u64 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != qword)
			break;
	}
	return iter;
}

@@Same as `rawmemrchrq', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRXCHRQ))]]
[[nonnull]] $uint64_t *rawmemrxchrq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword)
	[([[nonnull]] /*aligned(8)*/ void *__restrict haystack, $uint64_t qword): [[nonnull]] $uint64_t *]
	[([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword): [[nonnull]] $uint64_t const *]
{
	u64 *iter = (u64 *)haystack;
	for (;;) {
		if unlikely(*--iter != qword)
			break;
	}
	return iter;
}

@@Same as `memendq', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXENDQ))]]
[[nonnull]] $uint64_t *memxendq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword, $size_t n_bytes)
	[([[nonnull]] /*aligned(8)*/ void *__restrict haystack, $uint64_t qword, $size_t n_bytes): [[nonnull]] $uint64_t *]
	[([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword, $size_t n_bytes): [[nonnull]] $uint64_t const *]
{
	u64 *result = (u64 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != qword)
			break;
	}
	return result;
}

@@Same as `memrendq', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXENDQ))]]
[[nonnull]] $uint64_t *memrxendq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword, $size_t n_qwords)
	[([[nonnull]] /*aligned(8)*/ void *__restrict haystack, $uint64_t qword, $size_t n_qwords): [[nonnull]] $uint64_t *]
	[([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword, $size_t n_qwords): [[nonnull]] $uint64_t const *]
{
	u64 *result = (u64 *)haystack + n_qwords;
	while (n_qwords--) {
		if unlikely(*--result != qword)
			break;
	}
	return result;
}

@@Same as `memlenq', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMXLENQ))]]
$size_t memxlenq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword, $size_t n_qwords) {
	return (size_t)(memxendq(haystack, qword, n_qwords) - (u64 *)haystack);
}

@@Same as `memrlenq', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRXLENQ))]]
$size_t memrxlenq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword, $size_t n_qwords) {
	return (size_t)(memrxendq(haystack, qword, n_qwords) - (u64 *)haystack);
}

@@Same as `rawmemlenq', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMXLENQ))]]
$size_t rawmemxlenq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword) {
	return (size_t)(rawmemxchrq(haystack, qword) - (u64 *)haystack);
}

@@Same as `rawmemrlenq', but search for non-matching locations.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRXLENQ))]]
$size_t rawmemrxlenq([[nonnull]] /*aligned(8)*/ void const *__restrict haystack, $uint64_t qword) {
	return (size_t)(rawmemrxchrq(haystack, qword) - (u64 *)haystack);
}

%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_STRING_BWLQ */
%#endif /* __USE_STRING_XCHR */
%
%
%
%
%
%#ifdef __USE_KOS

@@Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !N_BYTES')
@@@return: * : Always re-returns `dst'
[[fast, libc, kernel, ATTR_LEAF]]
[[impl_include("<hybrid/__assert.h>")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEUP))]]
memmoveup:([[nonnull]] void *dst,
           [[nonnull]] void const *src,
           $size_t n_bytes) -> [[== dst]] void * {
	byte_t *pdst, *psrc;
	pdst = (byte_t *)dst + n_bytes;
	psrc = (byte_t *)src + n_bytes;
	@__hybrid_assertf@(pdst >= psrc || !n_bytes, "%p < %p (count:%Iu)", dst, src, n_bytes);
	while (n_bytes--)
		*--pdst = *--psrc;
	return dst;
}

@@Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !N_BYTES')
@@@return: * : Always re-returns `dst'
[[fast, libc, kernel, ATTR_LEAF]]
[[impl_include("<hybrid/__assert.h>")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMMOVEDOWN))]]
memmovedown:([[nonnull]] void *dst,
             [[nonnull]] void const *src,
             $size_t n_bytes) -> [[== dst]] void * {
	byte_t *pdst, *psrc;
	pdst = (byte_t *)dst;
	psrc = (byte_t *)src;
	@__hybrid_assertf@(pdst <= psrc || !n_bytes, "%p > %p (count:%Iu)", dst, src, n_bytes);
	while (n_bytes--)
		*pdst++ = *psrc++;
	return dst;
}




@@Copy memory between non-overlapping memory blocks.
@@@return: * : Always re-returns `dst'
[[fast, libc, ATTR_LEAF, impl_include("<hybrid/host.h>")]]
memcpyc:([[nonnull]] void *__restrict dst,
         [[nonnull]] void const *__restrict src,
         $size_t elem_count, $size_t elem_size)
	-> [[== dst]] void * {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		return memcpy(dst, src, elem_count);

	case 2:
		return memcpyw(dst, src, elem_count);

	case 4:
		return memcpyl(dst, src, elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return memcpyq(dst, src, elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return memcpy(dst, src, elem_count * elem_size);
}

@@Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST'
[[fast, libc, ATTR_LEAF, impl_include("<hybrid/host.h>")]]
mempcpyc:([[nonnull]] void *__restrict dst,
          [[nonnull]] void const *__restrict src,
          $size_t elem_count, $size_t elem_size)
	-> [[== dst + (elem_count * elem_size)]] void * {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		return mempcpy(dst, src, elem_count);

	case 2:
		return mempcpyw(dst, src, elem_count);

	case 4:
		return mempcpyl(dst, src, elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return mempcpyq(dst, src, elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return mempcpy(dst, src, elem_count * elem_size);
}

@@Move memory between potentially overlapping memory blocks
@@@return: * : Always re-returns `dst'
[[fast, libc, ATTR_LEAF, impl_include("<hybrid/host.h>")]]
memmovec:([[nonnull]] void *dst,
          [[nonnull]] void const *src,
          $size_t elem_count, $size_t elem_size)
	-> [[== dst]] void * {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		return memmove(dst, src, elem_count);

	case 2:
		return memmovew(dst, src, elem_count);

	case 4:
		return memmovel(dst, src, elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return memmoveq(dst, src, elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return memmove(dst, src, elem_count * elem_size);
}

@@Same as `memmovec', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST'
[[fast, libc, ATTR_LEAF, impl_include("<hybrid/host.h>")]]
mempmovec:([[nonnull]] void *dst,
           [[nonnull]] void const *src,
           $size_t elem_count, $size_t elem_size)
	-> [[== dst + (elem_count * elem_size)]] void * {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		return mempmove(dst, src, elem_count);

	case 2:
		return mempmovew(dst, src, elem_count);

	case 4:
		return mempmovel(dst, src, elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return mempmoveq(dst, src, elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return mempmove(dst, src, elem_count * elem_size);
}

@@Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE')
@@@return: * : Always re-returns `dst'
[[fast, libc, ATTR_LEAF, impl_include("<hybrid/host.h>")]]
memmoveupc:([[nonnull]] void *dst,
            [[nonnull]] void const *src,
            $size_t elem_count, $size_t elem_size)
	-> [[== dst]] void * {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		return memmoveup(dst, src, elem_count);

	case 2:
		return memmoveupw(dst, src, elem_count);

	case 4:
		return memmoveupl(dst, src, elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return memmoveupq(dst, src, elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return memmoveup(dst, src, elem_count * elem_size);
}

@@Same as `memmoveupc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE')
[[fast, libc, ATTR_LEAF, impl_include("<hybrid/host.h>")]]
mempmoveupc:([[nonnull]] void *dst,
             [[nonnull]] void const *src,
             $size_t elem_count, $size_t elem_size)
	-> [[== dst + (elem_count * elem_size)]] void * {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		return mempmoveup(dst, src, elem_count);

	case 2:
		return mempmoveupw(dst, src, elem_count);

	case 4:
		return mempmoveupl(dst, src, elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return mempmoveupq(dst, src, elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return mempmoveup(dst, src, elem_count * elem_size);
}

@@Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
@@@return: * : Always re-returns `dst'
[[fast, libc, ATTR_LEAF, impl_include("<hybrid/host.h>")]]
memmovedownc:([[nonnull]] void *dst,
              [[nonnull]] void const *src,
              $size_t elem_count, $size_t elem_size)
	-> [[== dst]] void * {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		return memmovedown(dst, src, elem_count);

	case 2:
		return memmovedownw(dst, src, elem_count);

	case 4:
		return memmovedownl(dst, src, elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return memmovedownq(dst, src, elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return memmovedown(dst, src, elem_count * elem_size);
}

@@Same as `memmovedownc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
[[fast, libc, ATTR_LEAF, impl_include("<hybrid/host.h>")]]
mempmovedownc:([[nonnull]] void *dst,
               [[nonnull]] void const *src,
               $size_t elem_count, $size_t elem_size)
	-> [[== dst + (elem_count * elem_size)]] void * {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		return mempmovedown(dst, src, elem_count);

	case 2:
		return mempmovedownw(dst, src, elem_count);

	case 4:
		return mempmovedownl(dst, src, elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return mempmovedownq(dst, src, elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return mempmovedown(dst, src, elem_count * elem_size);
}




/* KOS String extension functions. */
@@Same as `STR + strlen(STR)'
[[libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STREND))]]
[[nonnull]] char *strend([[nonnull]] char const *__restrict string)
	[([[nonnull]] char *__restrict string): [[nonnull]] char *]
	[([[nonnull]] char const *__restrict string): [[nonnull]] char const *]
{
	while (*string)
		++string;
	return (char *)string;
}

@@Same as `STR + strnlen(STR, MAX_CHARS)'
[[libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRNEND))]]
[[nonnull]] char *strnend([[nonnull]] char const *__restrict string, $size_t maxlen)
	[([[nonnull]] char *__restrict string, $size_t maxlen): [[nonnull]] char *]
	[([[nonnull]] char const *__restrict string, $size_t maxlen): [[nonnull]] char const *]
{
	for (; maxlen && *string; ++string, --maxlen)
		;
	return (char *)string;
}

@@Same as `strchr', but don't exceed `MAX_CHARS' characters.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRNCHR))]]
char *strnchr([[nonnull]] char const *__restrict haystack, int needle, $size_t maxlen)
	[([[nonnull]] char *__restrict haystack, int needle, $size_t maxlen): char *]
	[([[nonnull]] char const *__restrict haystack, int needle, $size_t maxlen): char const *]
{
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			return (char *)haystack;
	}
	return NULL;
}

@@Same as `strrchr', but don't exceed `MAX_CHARS' characters.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRNRCHR))]]
char *strnrchr([[nonnull]] char const *__restrict haystack, int needle, $size_t maxlen)
	[([[nonnull]] char *__restrict haystack, int needle, $size_t maxlen): char *]
	[([[nonnull]] char const *__restrict haystack, int needle, $size_t maxlen): char const *]
{
	char const *result = NULL;
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			result = haystack;
	}
	return (char *)result;
}

@@Same as `strrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRRCHRNUL))]]
[[nonnull]] char *strrchrnul([[nonnull]] char const *__restrict haystack, int needle)
	[([[nonnull]] char *__restrict haystack, int needle): [[nonnull]] char *]
	[([[nonnull]] char const *__restrict haystack, int needle): [[nonnull]] char const *]
{
	char const *result = haystack - 1;
	do {
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			result = haystack;
	} while (*haystack++);
	return (char *)result;
}

@@Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRNCHRNUL))]]
[[nonnull]] char *strnchrnul([[nonnull]] char const *__restrict haystack, int needle, $size_t maxlen)
	[([[nonnull]] char *__restrict haystack, int needle, $size_t maxlen): [[nonnull]] char *]
	[([[nonnull]] char const *__restrict haystack, int needle, $size_t maxlen): [[nonnull]] char const *]
{
	for (; maxlen-- && *haystack && (unsigned char)*haystack != (unsigned char)needle; ++haystack)
		;
	return (char *)haystack;
}

@@Same as `strnrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found.
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRNRCHRNUL))]]
[[nonnull]] char *strnrchrnul([[nonnull]] char const *__restrict haystack, int needle, $size_t maxlen)
	[([[nonnull]] char *__restrict haystack, int needle, $size_t maxlen): [[nonnull]] char *]
	[([[nonnull]] char const *__restrict haystack, int needle, $size_t maxlen): [[nonnull]] char const *]
{
	char const *result = haystack - 1;
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			result = haystack;
	}
	return (char *)result;
}

@@Same as `strchrnul', but return the offset from `STR', rather than the actual address
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STROFF))]]
$size_t stroff([[nonnull]] char const *__restrict haystack, int needle) {
	return (size_t)(strchrnul(haystack, needle) - haystack);
}

@@Same as `strrchrnul', but return the offset from `STR', rather than the actual address
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRROFF))]]
$size_t strroff([[nonnull]] char const *__restrict haystack, int needle) {
	return (size_t)(strrchrnul(haystack, needle) - haystack);
}

@@Same as `strnchrnul', but return the offset from `STR', rather than the actual address
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRNOFF))]]
$size_t strnoff([[nonnull]] char const *__restrict haystack, int needle, $size_t maxlen) {
	return (size_t)(strnchrnul(haystack, needle, maxlen) - haystack);
}

@@Same as `strnrchrnul', but return the offset from `STR', rather than the actual address
[[wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_STRNROFF))]]
$size_t strnroff([[nonnull]] char const *__restrict haystack, int needle, $size_t maxlen) {
	return (size_t)(strnrchrnul(haystack, needle, maxlen) - haystack);
}


@@Same as `memset', but return `DST + N_BYTES', rather than `DST'
[[fast, libc, kernel, ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPSET))]]
mempset:([[nonnull]] void *__restrict dst, int byte, $size_t n_bytes) -> [[== dst + n_bytes]] void * {
	return (void *)((byte_t *)memset(dst, byte, n_bytes) + n_bytes);
}

@@Same as `memmove', but return `DST + N_BYTES', rather than `DST'
[[fast, libc, kernel, ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVE))]]
[[nonnull]] void *mempmove:([[nonnull]] void *dst, [[nonnull]] void const *src, $size_t n_bytes) {
	return (void *)((byte_t *)memmove(dst, src, n_bytes) + n_bytes);
}

@@Same as `memmoveup', but return `DST + N_BYTES', rather than `DST' (assumes that `DST >= SRC || !N_BYTES')
[[fast, libc, kernel, ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEUP))]]
[[nonnull]] void *mempmoveup:([[nonnull]] void *dst, [[nonnull]] void const *src, $size_t n_bytes) {
	return (void *)((byte_t *)memmoveup(dst, src, n_bytes) + n_bytes);
}

@@Same as `memmovedown', but return `DST + N_BYTES', rather than `DST' (assumes that `DST <= SRC || !N_BYTES')
[[fast, libc, kernel, ATTR_LEAF]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPMOVEDOWN))]]
[[nonnull]] void *mempmovedown:([[nonnull]] void *dst, [[nonnull]] void const *src, $size_t n_bytes) {
	return (void *)((byte_t *)memmovedown(dst, src, n_bytes) + n_bytes);
}

%#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
%[insert:function(mempmove = mempmovec, externLinkageOverride: "C++")]
%[insert:function(mempmoveup = mempmoveupc, externLinkageOverride: "C++")]
%[insert:function(mempmovedown = mempmovedownc, externLinkageOverride: "C++")]
%[insert:function(memmoveup = memmoveupc, externLinkageOverride: "C++")]
%[insert:function(memmovedown = memmovedownc, externLinkageOverride: "C++")]
%#endif /* __cplusplus && __USE_STRING_OVERLOADS */


@@Same as `memrchr' without a search limit, starting at `HAYSTACK - 1'
[[kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRCHR))]]
[[nonnull]] void *rawmemrchr([[nonnull]] void const *__restrict haystack, int needle)
	[([[nonnull]] void *__restrict haystack, int needle): [[nonnull]] void *]
	[([[nonnull]] void const *__restrict haystack, int needle): [[nonnull]] void const *]
{
	byte_t *iter = (byte_t *)haystack;
	for (;;) {
		if unlikely(*--iter == (byte_t)needle)
			break;
	}
	return iter;
}


/* This could be an idea. - But it may also turn out like memxch(), and never be used... */
//[[fast, libc, kernel, wunused, ATTR_PURE]]
//memdiff:([[nonnull]] void const *__restrict data, void const *__restrict baseline, $size_t n_bytes) -> void *
//	[([[nonnull]] void *__restrict data, void const *__restrict baseline, $size_t n_bytes) -> void *]
//	[([[nonnull]] void const *__restrict data, void const *__restrict baseline, $size_t n_bytes) -> void const *]
//{
//	byte_t *diter = (byte_t *)data;
//	byte_t *biter = (byte_t *)baseline;
//	for (; n_bytes--; ++diter, ++biter) {
//		if unlikely(*diter != *biter)
//			return diter;
//	}
//	return NULL;
//}
//[[fast, libc, kernel, wunused, ATTR_PURE]]
//memrdiff:([[nonnull]] void const *__restrict data, void const *__restrict baseline, $size_t n_bytes) -> void *
//	[([[nonnull]] void *__restrict data, void const *__restrict baseline, $size_t n_bytes) -> void *]
//	[([[nonnull]] void const *__restrict data, void const *__restrict baseline, $size_t n_bytes) -> void const *]
//{
//	byte_t *diter = (byte_t *)data + n_bytes;
//	byte_t *biter = (byte_t *)baseline + n_bytes;
//	while (n_bytes--) {
//		if unlikely(*--diter != *--biter)
//			return diter;
//	}
//	return NULL;
//}

@@Same as `memchr', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found.
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMEND))]]
[[nonnull]] void *memend([[nonnull]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[nonnull]] void *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] void *]
	[([[nonnull]] void const *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] void const *]
{
	byte_t *result = (byte_t *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == (byte_t)needle)
			break;
	}
	return result;
}

@@Same as `memrchr', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found.
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMREND))]]
[[nonnull]] void *memrend([[nonnull]] void const *__restrict haystack, int needle, $size_t n_bytes)
	[([[nonnull]] void *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] void *]
	[([[nonnull]] void const *__restrict haystack, int needle, $size_t n_bytes): [[nonnull]] void const *]
{
	byte_t *result = (byte_t *)haystack + n_bytes;
	for (;;) {
		--result;
		if unlikely(!n_bytes)
			break;
		if unlikely(*result == (byte_t)needle)
			break;
		--n_bytes;
	}
	return result;
}

@@Same as `memend', but return the offset from `HAYSTACK', rather than the actual address.
@@Returns `n_bytes' if the given `NEEDLE' wasn't found
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMLEN))]]
$size_t memlen([[nonnull]] void const *__restrict haystack, int needle, $size_t n_bytes) {
	return (size_t)((byte_t *)memend(haystack, needle, n_bytes) - (byte_t *)haystack);
}

@@Same as `memrend', but return the offset from `HAYSTACK', rather than the actual address.
@@Returns `(size_t)-1' if the given `NEEDLE' wasn't found
[[fast, libc, kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRLEN))]]
$size_t memrlen([[nonnull]] void const *__restrict haystack, int needle, $size_t n_bytes) {
	return (size_t)((byte_t *)memrend(haystack, needle, n_bytes) - (byte_t *)haystack);
}

@@Same as `rawmemchr', but return the offset from `HAYSTACK', rather than the actual address.
[[kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMLEN))]]
$size_t rawmemlen([[nonnull]] void const *__restrict haystack, int needle) {
	return (size_t)((byte_t *)rawmemchr(haystack, needle) - (byte_t *)haystack);
}

@@Same as `rawmemrchr', but return the offset from `HAYSTACK', rather than the actual address.
[[kernel, wunused, ATTR_PURE]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_RAWMEMRLEN))]]
$size_t rawmemrlen([[nonnull]] void const *__restrict haystack, int needle) {
	return (size_t)((byte_t *)rawmemrchr(haystack, needle) - (byte_t *)haystack);
}


@@Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
@@If no such sub-string exists, return `NULL' instead.
@@#ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
@@When `needlelen' is ZERO(0), also return `NULL' unconditionally.
@@#else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
@@When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
@@#endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
[[libc, wunused, ATTR_PURE, impl_include("<features.h>"), no_crt_self_import]]
[[if(defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), preferred_alias("memrmem0")]]
[[if(!defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), preferred_alias("memrmem")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMRMEM))]]
void *memrmem([[nonnull]] void const *haystack, $size_t haystacklen, [[nonnull]] void const *needle, $size_t needlelen)
	[([[nonnull]] void *haystack, $size_t haystacklen, [[nonnull]] void const *needle, $size_t needlelen): void *]
	[([[nonnull]] void const *haystack, $size_t haystacklen, [[nonnull]] void const *needle, $size_t needlelen): void const *]
{
	byte_t *candidate, marker;
#if defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL) && !defined(__BUILDING_LIBC)
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
#else /* __USE_MEMMEM_EMPTY_NEEDLE_NULL && !__BUILDING_LIBC */
	if unlikely(!needlelen)
		return (byte_t *)haystack + haystacklen;
	if unlikely(needlelen > haystacklen)
		return NULL;
#endif /* !__USE_MEMMEM_EMPTY_NEEDLE_NULL || __BUILDING_LIBC */
	haystacklen -= needlelen - 1;
	marker = *(uint8_t *)needle;
	while ((candidate = (byte_t *)memrchr(haystack, marker, haystacklen)) != NULL) {
		if (memcmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		haystacklen = (size_t)(candidate - (byte_t *)haystack);
	}
	return NULL;
}


@@Same as `memsetb', but repeat a 1-byte pattern on aligned addresses.
[[ATTR_LEAF]]
mempatb:([[nonnull]] void *__restrict dst,
         int pattern, $size_t n_bytes) -> [[== dst]] void * = memset;

@@Same as `memsetw', but repeat a 2-byte pattern on aligned addresses.
[[fast, libc, kernel, ATTR_LEAF, impl_include("<hybrid/__wordbits.h>")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPATW))]]
mempatw([[nonnull]] void *__restrict dst,
        $uint16_t pattern, $size_t n_bytes) -> [[== dst]] void * {
	byte_t *iter = (byte_t *)dst;
	if (n_bytes && (uintptr_t)iter & 1) {
		*iter = __INT16_BYTE(pattern, 1);
		++iter;
		--n_bytes;
	}
	iter = (byte_t *)mempsetw(iter, pattern, n_bytes / 2);
	if (n_bytes & 1)
		*iter = __INT16_BYTE(pattern, 0);
	return dst;
}

@@Same as `memsetl', but repeat a 4-byte pattern on aligned addresses.
[[fast, libc, kernel, ATTR_LEAF, impl_include("<hybrid/__wordbits.h>")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPATL))]]
mempatl([[nonnull]] void *__restrict dst,
        $uint32_t pattern, $size_t n_bytes) -> [[== dst]] void * {
	byte_t *iter = (byte_t *)dst;
	for (; n_bytes && (uintptr_t)iter & 3; ++iter, --n_bytes)
		*iter = __INT32_BYTE(pattern, (uintptr_t)iter & 3);
	iter = (byte_t *)mempsetl(iter, pattern, n_bytes / 4);
	for (n_bytes &= 3; n_bytes; ++iter, --n_bytes)
		*iter = __INT32_BYTE(pattern, (uintptr_t)iter & 3);
	return dst;
}

%#ifdef __UINT64_TYPE__
@@Same as `memsetq', but repeat an 8-byte pattern on aligned addresses.
[[fast, libc, kernel, ATTR_LEAF, impl_include("<hybrid/__wordbits.h>")]]
[[crt_impl_requires(!defined(LIBC_ARCH_HAVE_MEMPATQ))]]
mempatq([[nonnull]] void *__restrict dst,
        $uint64_t pattern, $size_t n_bytes) -> [[== dst]] void * {
	byte_t *iter = (byte_t *)dst;
	for (; n_bytes && (uintptr_t)iter & 7; ++iter, --n_bytes)
		*iter = __INT64_BYTE(pattern, (uintptr_t)iter & 7);
	iter = (byte_t *)mempsetq(iter, pattern, n_bytes / 8);
	for (n_bytes &= 7; n_bytes; ++iter, --n_bytes)
		*iter = __INT64_BYTE(pattern, (uintptr_t)iter & 7);
	return dst;
}
%#endif /* __UINT64_TYPE__ */

[[wunused, ATTR_PURE, export_alias("memicmp", "_memicmp")]]
[[section(".text.crt.unicode.static.memory")]]
int memcasecmp([[nonnull]] void const *s1,
               [[nonnull]] void const *s2, $size_t n_bytes) {
	byte_t *p1 = (byte_t *)s1;
	byte_t *p2 = (byte_t *)s2;
	byte_t v1, v2;
	v1 = v2 = 0;
	while (n_bytes-- &&
	    (((v1 = *p1++) == (v2 = *p2++)) ||
	     ((v1 = tolower(v1)) == (v2 = tolower(v2)))));
	return (int)v1 - (int)v2;
}


@@Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
@@During comprisons, casing of character is ignored (s.a. `memmem()')
@@If no such sub-string exists, return `NULL' instead.
@@#ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
@@When `needlelen' is ZERO(0), also return `NULL' unconditionally.
@@#else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
@@When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
@@#endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
[[wunused, ATTR_PURE, impl_include("<features.h>"), no_crt_self_import]]
[[if(defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), preferred_alias("memcasemem0")]]
[[if(!defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), preferred_alias("memcasemem")]]
[[section(".text.crt.unicode.static.memory")]]
void *memcasemem([[nonnull]] void const *haystack, $size_t haystacklen, [[nonnull]] void const *needle, $size_t needlelen)
	[([[nonnull]] void *haystack, $size_t haystacklen, [[nonnull]] void const *needle, $size_t needlelen): void *]
	[([[nonnull]] void const *haystack, $size_t haystacklen, [[nonnull]] void const *needle, $size_t needlelen): void const *]
{
	byte_t *candidate, marker;
	byte_t *hayend;
#if defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL) && !defined(__BUILDING_LIBC)
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
#else /* __USE_MEMMEM_EMPTY_NEEDLE_NULL && !__BUILDING_LIBC */
	if unlikely(!needlelen)
		return (byte_t *)haystack + haystacklen;
	if unlikely(needlelen > haystacklen)
		return NULL;
#endif /* !__USE_MEMMEM_EMPTY_NEEDLE_NULL || __BUILDING_LIBC */
	haystacklen -= (needlelen - 1);
	marker       = tolower(*(byte_t *)needle);
	hayend       = (byte_t *)haystack + haystacklen;
	for (;;) {
		for (candidate = (byte_t *)haystack; candidate < hayend; ++candidate) {
			byte_t b = *candidate;
			if (b == marker || tolower(b) == marker)
				goto got_candidate;
		}
		break;
got_candidate:
		if (memcasecmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((byte_t *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}

%#ifdef __USE_XOPEN2K8
[[wunused, ATTR_PURE, export_alias("_memicmp_l")]]
[[section(".text.crt.unicode.locale.memory")]]
int memcasecmp_l([[nonnull]] void const *s1,
                 [[nonnull]] void const *s2,
                 $size_t n_bytes, $locale_t locale) {
	(void)locale;
	return memcasecmp(s1, s2, n_bytes);
}


@@Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
@@During comprisons, casing of character is ignored using the given `locale' (s.a. `memmem()')
@@If no such sub-string exists, return `NULL' instead.
@@#ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
@@When `needlelen' is ZERO(0), also return `NULL' unconditionally.
@@#else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
@@When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
@@#endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
[[wunused, ATTR_PURE, impl_include("<features.h>"), no_crt_self_import]]
[[if(defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), preferred_alias("memcasemem0_l")]]
[[if(!defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), preferred_alias("memcasemem_l")]]
[[section(".text.crt.unicode.locale.memory")]]
void *memcasemem_l([[nonnull]] void const *haystack, $size_t haystacklen, [[nonnull]] void const *needle, $size_t needlelen, $locale_t locale)
	[([[nonnull]] void *haystack, $size_t haystacklen, [[nonnull]] void const *needle, $size_t needlelen, $locale_t locale): void *]
	[([[nonnull]] void const *haystack, $size_t haystacklen, [[nonnull]] void const *needle, $size_t needlelen, $locale_t locale): void const *]
{
	byte_t *candidate, marker;
	byte_t *hayend;
#if defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL) && !defined(__BUILDING_LIBC)
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
#else /* __USE_MEMMEM_EMPTY_NEEDLE_NULL && !__BUILDING_LIBC */
	if unlikely(!needlelen)
		return (byte_t *)haystack + haystacklen;
	if unlikely(needlelen > haystacklen)
		return NULL;
#endif /* !__USE_MEMMEM_EMPTY_NEEDLE_NULL || __BUILDING_LIBC */
	haystacklen -= (needlelen - 1);
	marker       = tolower_l(*(byte_t *)needle, locale);
	hayend       = (byte_t *)haystack + haystacklen;
	for (;;) {
		for (candidate = (byte_t *)haystack; candidate < hayend; ++candidate) {
			byte_t b = *candidate;
			if (b == marker || tolower_l(b, locale) == marker)
				goto got_candidate;
		}
		break;
got_candidate:
		if (memcasecmp_l(candidate, needle, needlelen, locale) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((byte_t *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}

[[wunused, ATTR_PURE, section(".text.crt.unicode.locale.memory")]]
char *strcasestr_l([[nonnull]] char const *haystack, [[nonnull]] char const *needle, $locale_t locale)
	[([[nonnull]] char *haystack, [[nonnull]] char const *needle, $locale_t locale): char *]
	[([[nonnull]] char const *haystack, [[nonnull]] char const *needle, $locale_t locale): char const *]
{
	for (; *haystack; ++haystack) {
		if (strcasecmp_l(haystack, needle, locale) == 0)
			return (char *)haystack;
	}
	return NULL;
}

%#endif /* __USE_XOPEN2K8 */
%
%
%


[[wunused, nothrow, ATTR_CONST]]
[[userimpl, impl_prefix(
#ifndef ___local_sys_errlist_defined
#define ___local_sys_errlist_defined 1
#if defined(__CRT_HAVE__sys_errlist) && defined(__CRT_HAVE__sys_nerr)
__LIBC char const *const _sys_errlist[];
__LIBC int _sys_nerr;
#elif defined(__CRT_HAVE___sys_errlist) && defined(__CRT_HAVE___sys_nerr)
__LIBC __ATTR_WUNUSED __ATTR_CONST char const *const *(__LIBCCALL __sys_errlist)(void);
__LIBC __ATTR_WUNUSED __ATTR_CONST int *(__LIBCCALL __sys_nerr)(void);
#else /* ... */
#undef ___local_sys_errlist_defined
#endif /* !... */
#endif /* !___local_sys_errlist_defined */
), section(".text.crt.errno")]]
char const *strerror_s(int errnum) {
#if defined(__CRT_HAVE__sys_errlist) && defined(__CRT_HAVE__sys_nerr)
	return (unsigned int)errnum < (unsigned int)@_sys_nerr@ ? @_sys_errlist@[errnum] : NULL;
#elif defined(__CRT_HAVE___sys_errlist) && defined(__CRT_HAVE___sys_nerr)
	return (unsigned int)errnum < (unsigned int)*@__sys_nerr@() ? @__sys_errlist@()[errnum] : NULL;
#else
	char const *result;
	switch (errnum) {

#ifdef EPERM
	case EPERM:           result = "Operation not permitted"; break;
#endif /* EPERM */
#ifdef ENOENT
	case ENOENT:          result = "No such file or directory"; break;
#endif /* ENOENT */
#ifdef ESRCH
	case ESRCH:           result = "No such process"; break;
#endif /* ESRCH */
#ifdef EINTR
	case EINTR:           result = "Interrupted system call"; break;
#endif /* EINTR */
#ifdef EIO
	case EIO:             result = "I/O error"; break;
#endif /* EIO */
#ifdef ENXIO
	case ENXIO:           result = "No such device or address"; break;
#endif /* ENXIO */
#ifdef E2BIG
	case E2BIG:           result = "Argument list too long"; break;
#endif /* E2BIG */
#ifdef ENOEXEC
	case ENOEXEC:         result = "Exec format error"; break;
#endif /* ENOEXEC */
#ifdef EBADF
	case EBADF:           result = "Bad file number"; break;
#endif /* EBADF */
#ifdef ECHILD
	case ECHILD:          result = "No child processes"; break;
#endif /* ECHILD */
#ifdef EAGAIN
	case EAGAIN:          result = "Try again"; break;
#endif /* EAGAIN */
#ifdef ENOMEM
	case ENOMEM:          result = "Out of memory"; break;
#endif /* ENOMEM */
#ifdef EACCES
	case EACCES:          result = "Permission denied"; break;
#endif /* EACCES */
#ifdef EFAULT
	case EFAULT:          result = "Bad address"; break;
#endif /* EFAULT */
#ifdef EBUSY
	case EBUSY:           result = "Device or resource busy"; break;
#endif /* EBUSY */
#ifdef EEXIST
	case EEXIST:          result = "File exists"; break;
#endif /* EEXIST */
#ifdef EXDEV
	case EXDEV:           result = "Cross-device link"; break;
#endif /* EXDEV */
#ifdef ENODEV
	case ENODEV:          result = "No such device"; break;
#endif /* ENODEV */
#ifdef ENOTDIR
	case ENOTDIR:         result = "Not a directory"; break;
#endif /* ENOTDIR */
#ifdef EISDIR
	case EISDIR:          result = "Is a directory"; break;
#endif /* EISDIR */
#ifdef ENFILE
	case ENFILE:          result = "File table overflow"; break;
#endif /* ENFILE */
#ifdef EMFILE
	case EMFILE:          result = "Too many open files"; break;
#endif /* EMFILE */
#ifdef ENOTTY
	case ENOTTY:          result = "Not a typewriter"; break;
#endif /* ENOTTY */
#ifdef EFBIG
	case EFBIG:           result = "File too large"; break;
#endif /* EFBIG */
#ifdef ENOSPC
	case ENOSPC:          result = "No space left on device"; break;
#endif /* ENOSPC */
#ifdef ESPIPE
	case ESPIPE:          result = "Illegal seek"; break;
#endif /* ESPIPE */
#ifdef EROFS
	case EROFS:           result = "Read-only file system"; break;
#endif /* EROFS */
#ifdef EMLINK
	case EMLINK:          result = "Too many links"; break;
#endif /* EMLINK */
#ifdef EPIPE
	case EPIPE:           result = "Broken pipe"; break;
#endif /* EPIPE */
#ifdef EDOM
	case EDOM:            result = "Math argument out of domain of func"; break;
#endif /* EDOM */
#ifdef ENAMETOOLONG
	case ENAMETOOLONG:    result = "File name too long"; break;
#endif /* ENAMETOOLONG */
#ifdef ENOLCK
	case ENOLCK:          result = "No record locks available"; break;
#endif /* ENOLCK */
#ifdef ENOSYS
	case ENOSYS:          result = "Function not implemented"; break;
#endif /* ENOSYS */
#ifdef ENOTEMPTY
	case ENOTEMPTY:       result = "Directory not empty"; break;
#endif /* ENOTEMPTY */
#ifdef EINVAL
	case EINVAL:          result = "Invalid argument"; break;
#endif /* EINVAL */
#ifdef ERANGE
	case ERANGE:          result = "Math result not representable"; break;
#endif /* ERANGE */
#ifdef EILSEQ
	case EILSEQ:          result = "Illegal byte sequence"; break;
#endif /* EILSEQ */
#ifdef EDEADLOCK
	case EDEADLOCK:       result = "Resource deadlock would occur"; break;
#endif /* EDEADLOCK */
#ifdef EADDRINUSE
	case EADDRINUSE:      result = "Address already in use"; break;
#endif /* EADDRINUSE */
#ifdef EADDRNOTAVAIL
	case EADDRNOTAVAIL:   result = "Cannot assign requested address"; break;
#endif /* EADDRNOTAVAIL */
#ifdef EAFNOSUPPORT
	case EAFNOSUPPORT:    result = "Address family not supported by protocol"; break;
#endif /* EAFNOSUPPORT */
#ifdef EALREADY
	case EALREADY:        result = "Operation already in progress"; break;
#endif /* EALREADY */
#ifdef EBADMSG
	case EBADMSG:         result = "Not a data message"; break;
#endif /* EBADMSG */
#ifdef ECANCELED
	case ECANCELED:       result = "Operation Canceled"; break;
#endif /* ECANCELED */
#ifdef ECONNABORTED
	case ECONNABORTED:    result = "Software caused connection abort"; break;
#endif /* ECONNABORTED */
#ifdef ECONNREFUSED
	case ECONNREFUSED:    result = "Connection refused"; break;
#endif /* ECONNREFUSED */
#ifdef ECONNRESET
	case ECONNRESET:      result = "Connection reset by peer"; break;
#endif /* ECONNRESET */
#ifdef EDESTADDRREQ
	case EDESTADDRREQ:    result = "Destination address required"; break;
#endif /* EDESTADDRREQ */
#ifdef EHOSTUNREACH
	case EHOSTUNREACH:    result = "No route to host"; break;
#endif /* EHOSTUNREACH */
#ifdef EIDRM
	case EIDRM:           result = "Identifier removed"; break;
#endif /* EIDRM */
#ifdef EINPROGRESS
	case EINPROGRESS:     result = "Operation now in progress"; break;
#endif /* EINPROGRESS */
#ifdef EISCONN
	case EISCONN:         result = "Transport endpoint is already connected"; break;
#endif /* EISCONN */
#ifdef ELOOP
	case ELOOP:           result = "Too many symbolic links encountered"; break;
#endif /* ELOOP */
#ifdef EMSGSIZE
	case EMSGSIZE:        result = "Message too long"; break;
#endif /* EMSGSIZE */
#ifdef ENETDOWN
	case ENETDOWN:        result = "Network is down"; break;
#endif /* ENETDOWN */
#ifdef ENETRESET
	case ENETRESET:       result = "Network dropped connection because of reset"; break;
#endif /* ENETRESET */
#ifdef ENETUNREACH
	case ENETUNREACH:     result = "Network is unreachable"; break;
#endif /* ENETUNREACH */
#ifdef ENOBUFS
	case ENOBUFS:         result = "No buffer space available"; break;
#endif /* ENOBUFS */
#ifdef ENODATA
	case ENODATA:         result = "No data available"; break;
#endif /* ENODATA */
#ifdef ENOLINK
	case ENOLINK:         result = "Link has been severed"; break;
#endif /* ENOLINK */
#ifdef ENOMSG
	case ENOMSG:          result = "No message of desired type"; break;
#endif /* ENOMSG */
#ifdef ENOPROTOOPT
	case ENOPROTOOPT:     result = "Protocol not available"; break;
#endif /* ENOPROTOOPT */
#ifdef ENOSR
	case ENOSR:           result = "Out of streams resources"; break;
#endif /* ENOSR */
#ifdef ENOSTR
	case ENOSTR:          result = "Device not a stream"; break;
#endif /* ENOSTR */
#ifdef ENOTCONN
	case ENOTCONN:        result = "Transport endpoint is not connected"; break;
#endif /* ENOTCONN */
#ifdef ENOTRECOVERABLE
	case ENOTRECOVERABLE: result = "State not recoverable"; break;
#endif /* ENOTRECOVERABLE */
#ifdef ENOTSOCK
	case ENOTSOCK:        result = "Socket operation on non-socket"; break;
#endif /* ENOTSOCK */
#ifdef ENOTSUP
	case ENOTSUP:         result = "Not supported"; break;
#endif /* ENOTSUP */
#ifdef EOPNOTSUPP
	case EOPNOTSUPP:      result = "Operation not supported on transport endpoint"; break;
#endif /* EOPNOTSUPP */
#ifdef EOTHER
	case EOTHER:          result = "Other"; break;
#endif /* EOTHER */
#ifdef EOVERFLOW
	case EOVERFLOW:       result = "Value too large for defined data type"; break;
#endif /* EOVERFLOW */
#ifdef EOWNERDEAD
	case EOWNERDEAD:      result = "Owner died"; break;
#endif /* EOWNERDEAD */
#ifdef EPROTO
	case EPROTO:          result = "Protocol error"; break;
#endif /* EPROTO */
#ifdef EPROTONOSUPPORT
	case EPROTONOSUPPORT: result = "Protocol not supported"; break;
#endif /* EPROTONOSUPPORT */
#ifdef EPROTOTYPE
	case EPROTOTYPE:      result = "Protocol wrong type for socket"; break;
#endif /* EPROTOTYPE */
#ifdef ETIME
	case ETIME:           result = "Timer expired"; break;
#endif /* ETIME */
#ifdef ETIMEDOUT
	case ETIMEDOUT:       result = "Connection timed out"; break;
#endif /* ETIMEDOUT */
#ifdef ETXTBSY
	case ETXTBSY:         result = "Text file busy"; break;
#endif /* ETXTBSY */
#ifdef EFTYPE
	case EFTYPE:          result = "Inappropriate file type or format"; break;
#endif /* EFTYPE */
#ifdef ENMFILE
	case ENMFILE:         result = "No more files"; break;
#endif /* ENMFILE */
#ifdef EPFNOSUPPORT
	case EPFNOSUPPORT:    result = "Protocol family not supported"; break;
#endif /* EPFNOSUPPORT */
#ifdef EHOSTDOWN
	case EHOSTDOWN:       result = "Host is down"; break;
#endif /* EHOSTDOWN */
#ifdef ETOOMANYREFS
	case ETOOMANYREFS:    result = "Too many references: cannot splice"; break;
#endif /* ETOOMANYREFS */
#ifdef EDQUOT
	case EDQUOT:          result = "Quota exceeded"; break;
#endif /* EDQUOT */
#ifdef ESTALE
	case ESTALE:          result = "Stale file handle"; break;
#endif /* ESTALE */
#ifdef ENOSHARE
	case ENOSHARE:        result = "No such host or network path"; break;
#endif /* ENOSHARE */
#ifdef ECASECLASH
	case ECASECLASH:      result = "Filename exists with different case"; break;
#endif /* ECASECLASH */
#ifdef ENOTBLK
	case ENOTBLK:         result = "Block device required"; break;
#endif /* ENOTBLK */
#ifdef ECHRNG
	case ECHRNG:          result = "Channel number out of range"; break;
#endif /* ECHRNG */
#ifdef EL2NSYNC
	case EL2NSYNC:        result = "Level 2 not synchronized"; break;
#endif /* EL2NSYNC */
#ifdef EL3HLT
	case EL3HLT:          result = "Level 3 halted"; break;
#endif /* EL3HLT */
#ifdef EL3RST
	case EL3RST:          result = "Level 3 reset"; break;
#endif /* EL3RST */
#ifdef ELNRNG
	case ELNRNG:          result = "Link number out of range"; break;
#endif /* ELNRNG */
#ifdef EUNATCH
	case EUNATCH:         result = "Protocol driver not attached"; break;
#endif /* EUNATCH */
#ifdef ENOCSI
	case ENOCSI:          result = "No CSI structure available"; break;
#endif /* ENOCSI */
#ifdef EL2HLT
	case EL2HLT:          result = "Level 2 halted"; break;
#endif /* EL2HLT */
#ifdef EBADE
	case EBADE:           result = "Invalid exchange"; break;
#endif /* EBADE */
#ifdef EBADR
	case EBADR:           result = "Invalid request descriptor"; break;
#endif /* EBADR */
#ifdef EXFULL
	case EXFULL:          result = "Exchange full"; break;
#endif /* EXFULL */
#ifdef ENOANO
	case ENOANO:          result = "No anode"; break;
#endif /* ENOANO */
#ifdef EBADRQC
	case EBADRQC:         result = "Invalid request code"; break;
#endif /* EBADRQC */
#ifdef EBADSLT
	case EBADSLT:         result = "Invalid slot"; break;
#endif /* EBADSLT */
#ifdef EBFONT
	case EBFONT:          result = "Bad font file fmt"; break;
#endif /* EBFONT */
#ifdef ENONET
	case ENONET:          result = "Machine is not on the network"; break;
#endif /* ENONET */
#ifdef ENOPKG
	case ENOPKG:          result = "Package not installed"; break;
#endif /* ENOPKG */
#ifdef EREMOTE
	case EREMOTE:         result = "The object is remote"; break;
#endif /* EREMOTE */
#ifdef EADV
	case EADV:            result = "Advertise error"; break;
#endif /* EADV */
#ifdef ESRMNT
	case ESRMNT:          result = "Srmount error"; break;
#endif /* ESRMNT */
#ifdef ECOMM
	case ECOMM:           result = "Communication error on send"; break;
#endif /* ECOMM */
#ifdef ELBIN
	case ELBIN:           result = "Inode is remote (not really error)"; break;
#endif /* ELBIN */
#ifdef EDOTDOT
	case EDOTDOT:         result = "Cross mount point (not really error)"; break;
#endif /* EDOTDOT */
#ifdef ENOTUNIQ
	case ENOTUNIQ:        result = "Given log. name not unique"; break;
#endif /* ENOTUNIQ */
#ifdef EBADFD
	case EBADFD:          result = "f.d. invalid for this operation"; break;
#endif /* EBADFD */
#ifdef EREMCHG
	case EREMCHG:         result = "Remote address changed"; break;
#endif /* EREMCHG */
#ifdef ELIBACC
	case ELIBACC:         result = "Can't access a needed shared lib"; break;
#endif /* ELIBACC */
#ifdef ELIBBAD
	case ELIBBAD:         result = "Accessing a corrupted shared lib"; break;
#endif /* ELIBBAD */
#ifdef ELIBSCN
	case ELIBSCN:         result = ".lib section in a.out corrupted"; break;
#endif /* ELIBSCN */
#ifdef ELIBMAX
	case ELIBMAX:         result = "Attempting to link in too many libs"; break;
#endif /* ELIBMAX */
#ifdef ELIBEXEC
	case ELIBEXEC:        result = "Attempting to exec a shared library"; break;
#endif /* ELIBEXEC */
#ifdef ESHUTDOWN
	case ESHUTDOWN:       result = "Can't send after socket shutdown"; break;
#endif /* ESHUTDOWN */
#ifdef ESOCKTNOSUPPORT
	case ESOCKTNOSUPPORT: result = "Socket type not supported"; break;
#endif /* ESOCKTNOSUPPORT */
#ifdef EPROCLIM
	case EPROCLIM:        result = "Process limit reached"; break;
#endif /* EPROCLIM */
#ifdef EUSERS
	case EUSERS:          result = "Too many users"; break;
#endif /* EUSERS */
#ifdef ENOMEDIUM
	case ENOMEDIUM:       result = "No medium (in tape drive)"; break;
#endif /* ENOMEDIUM */
#ifdef ESTRPIPE
	case ESTRPIPE:        result = "Streams pipe error"; break;
#endif /* ESTRPIPE */
#ifdef EMULTIHOP
	case EMULTIHOP:       result = "Multihop attempted"; break;
#endif /* EMULTIHOP */
#ifdef ERESTART
	case ERESTART:        result = "Interrupted system call should be restarted"; break;
#endif /* ERESTART */
#ifdef EUCLEAN
	case EUCLEAN:         result = "Structure needs cleaning"; break;
#endif /* EUCLEAN */
#ifdef ENOTNAM
	case ENOTNAM:         result = "Not a XENIX named type file"; break;
#endif /* ENOTNAM */
#ifdef ENAVAIL
	case ENAVAIL:         result = "No XENIX semaphores available"; break;
#endif /* ENAVAIL */
#ifdef EISNAM
	case EISNAM:          result = "Is a named type file"; break;
#endif /* EISNAM */
#ifdef EREMOTEIO
	case EREMOTEIO:       result = "Remote I/O error"; break;
#endif /* EREMOTEIO */
#ifdef EMEDIUMTYPE
	case EMEDIUMTYPE:     result = "Wrong medium type"; break;
#endif /* EMEDIUMTYPE */
#ifdef ENOKEY
	case ENOKEY:          result = "Required key not available"; break;
#endif /* ENOKEY */
#ifdef EKEYEXPIRED
	case EKEYEXPIRED:     result = "Key has expired"; break;
#endif /* EKEYEXPIRED */
#ifdef EKEYREVOKED
	case EKEYREVOKED:     result = "Key has been revoked"; break;
#endif /* EKEYREVOKED */
#ifdef EKEYREJECTED
	case EKEYREJECTED:    result = "Key was rejected by service"; break;
#endif /* EKEYREJECTED */
#ifdef ERFKILL
	case ERFKILL:         result = "Operation not possible due to RF-kill"; break;
#endif /* ERFKILL */
#ifdef EHWPOISON
	case EHWPOISON:       result = "Memory page has hardware error"; break;
#endif /* EHWPOISON */
#if defined(STRUNCATE) && (!defined(ERANGE) || STRUNCATE != ERANGE)
	case STRUNCATE:       result = "Truncated"; break;
#endif /* STRUNCATE && (!ERANGE || STRUNCATE != ERANGE) */
#if defined(EWOULDBLOCK) && (!defined(EAGAIN) || EWOULDBLOCK != EAGAIN)
	case EWOULDBLOCK:     result = "Operation would block"; break;
#endif /* EWOULDBLOCK && (!EAGAIN || EWOULDBLOCK != EAGAIN) */
#if defined(EDEADLK) && (!defined(EDEADLOCK) || EDEADLOCK != EDEADLK)
	case EDEADLK:         result = "Resource deadlock would occur"; break;
#endif /* EDEADLK && (!EDEADLOCK || EDEADLOCK != EDEADLK) */

	default:
		result = NULL;
		break;
	}
	return result;
#endif
}

[[wunused, nothrow, ATTR_CONST, section(".text.crt.errno")]]
[[userimpl, impl_include("<parts/errno.h>")]]
char const *strerrorname_s(int errnum) {
	char const *result;
	switch (errnum) {

#ifdef EPERM
	case EPERM:           result = "EPERM"; break;
#endif /* EPERM */
#ifdef ENOENT
	case ENOENT:          result = "ENOENT"; break;
#endif /* ENOENT */
#ifdef ESRCH
	case ESRCH:           result = "ESRCH"; break;
#endif /* ESRCH */
#ifdef EINTR
	case EINTR:           result = "EINTR"; break;
#endif /* EINTR */
#ifdef EIO
	case EIO:             result = "EIO"; break;
#endif /* EIO */
#ifdef ENXIO
	case ENXIO:           result = "ENXIO"; break;
#endif /* ENXIO */
#ifdef E2BIG
	case E2BIG:           result = "E2BIG"; break;
#endif /* E2BIG */
#ifdef ENOEXEC
	case ENOEXEC:         result = "ENOEXEC"; break;
#endif /* ENOEXEC */
#ifdef EBADF
	case EBADF:           result = "EBADF"; break;
#endif /* EBADF */
#ifdef ECHILD
	case ECHILD:          result = "ECHILD"; break;
#endif /* ECHILD */
#ifdef EAGAIN
	case EAGAIN:          result = "EAGAIN"; break;
#endif /* EAGAIN */
#ifdef ENOMEM
	case ENOMEM:          result = "ENOMEM"; break;
#endif /* ENOMEM */
#ifdef EACCES
	case EACCES:          result = "EACCES"; break;
#endif /* EACCES */
#ifdef EFAULT
	case EFAULT:          result = "EFAULT"; break;
#endif /* EFAULT */
#ifdef EBUSY
	case EBUSY:           result = "EBUSY"; break;
#endif /* EBUSY */
#ifdef EEXIST
	case EEXIST:          result = "EEXIST"; break;
#endif /* EEXIST */
#ifdef EXDEV
	case EXDEV:           result = "EXDEV"; break;
#endif /* EXDEV */
#ifdef ENODEV
	case ENODEV:          result = "ENODEV"; break;
#endif /* ENODEV */
#ifdef ENOTDIR
	case ENOTDIR:         result = "ENOTDIR"; break;
#endif /* ENOTDIR */
#ifdef EISDIR
	case EISDIR:          result = "EISDIR"; break;
#endif /* EISDIR */
#ifdef ENFILE
	case ENFILE:          result = "ENFILE"; break;
#endif /* ENFILE */
#ifdef EMFILE
	case EMFILE:          result = "EMFILE"; break;
#endif /* EMFILE */
#ifdef ENOTTY
	case ENOTTY:          result = "ENOTTY"; break;
#endif /* ENOTTY */
#ifdef EFBIG
	case EFBIG:           result = "EFBIG"; break;
#endif /* EFBIG */
#ifdef ENOSPC
	case ENOSPC:          result = "ENOSPC"; break;
#endif /* ENOSPC */
#ifdef ESPIPE
	case ESPIPE:          result = "ESPIPE"; break;
#endif /* ESPIPE */
#ifdef EROFS
	case EROFS:           result = "EROFS"; break;
#endif /* EROFS */
#ifdef EMLINK
	case EMLINK:          result = "EMLINK"; break;
#endif /* EMLINK */
#ifdef EPIPE
	case EPIPE:           result = "EPIPE"; break;
#endif /* EPIPE */
#ifdef EDOM
	case EDOM:            result = "EDOM"; break;
#endif /* EDOM */
#ifdef ENAMETOOLONG
	case ENAMETOOLONG:    result = "ENAMETOOLONG"; break;
#endif /* ENAMETOOLONG */
#ifdef ENOLCK
	case ENOLCK:          result = "ENOLCK"; break;
#endif /* ENOLCK */
#ifdef ENOSYS
	case ENOSYS:          result = "ENOSYS"; break;
#endif /* ENOSYS */
#ifdef ENOTEMPTY
	case ENOTEMPTY:       result = "ENOTEMPTY"; break;
#endif /* ENOTEMPTY */
#ifdef EINVAL
	case EINVAL:          result = "EINVAL"; break;
#endif /* EINVAL */
#ifdef ERANGE
	case ERANGE:          result = "ERANGE"; break;
#endif /* ERANGE */
#ifdef EILSEQ
	case EILSEQ:          result = "EILSEQ"; break;
#endif /* EILSEQ */
#ifdef EDEADLOCK
	case EDEADLOCK:       result = "EDEADLOCK"; break;
#endif /* EDEADLOCK */
#ifdef EADDRINUSE
	case EADDRINUSE:      result = "EADDRINUSE"; break;
#endif /* EADDRINUSE */
#ifdef EADDRNOTAVAIL
	case EADDRNOTAVAIL:   result = "EADDRNOTAVAIL"; break;
#endif /* EADDRNOTAVAIL */
#ifdef EAFNOSUPPORT
	case EAFNOSUPPORT:    result = "EAFNOSUPPORT"; break;
#endif /* EAFNOSUPPORT */
#ifdef EALREADY
	case EALREADY:        result = "EALREADY"; break;
#endif /* EALREADY */
#ifdef EBADMSG
	case EBADMSG:         result = "EBADMSG"; break;
#endif /* EBADMSG */
#ifdef ECANCELED
	case ECANCELED:       result = "ECANCELED"; break;
#endif /* ECANCELED */
#ifdef ECONNABORTED
	case ECONNABORTED:    result = "ECONNABORTED"; break;
#endif /* ECONNABORTED */
#ifdef ECONNREFUSED
	case ECONNREFUSED:    result = "ECONNREFUSED"; break;
#endif /* ECONNREFUSED */
#ifdef ECONNRESET
	case ECONNRESET:      result = "ECONNRESET"; break;
#endif /* ECONNRESET */
#ifdef EDESTADDRREQ
	case EDESTADDRREQ:    result = "EDESTADDRREQ"; break;
#endif /* EDESTADDRREQ */
#ifdef EHOSTUNREACH
	case EHOSTUNREACH:    result = "EHOSTUNREACH"; break;
#endif /* EHOSTUNREACH */
#ifdef EIDRM
	case EIDRM:           result = "EIDRM"; break;
#endif /* EIDRM */
#ifdef EINPROGRESS
	case EINPROGRESS:     result = "EINPROGRESS"; break;
#endif /* EINPROGRESS */
#ifdef EISCONN
	case EISCONN:         result = "EISCONN"; break;
#endif /* EISCONN */
#ifdef ELOOP
	case ELOOP:           result = "ELOOP"; break;
#endif /* ELOOP */
#ifdef EMSGSIZE
	case EMSGSIZE:        result = "EMSGSIZE"; break;
#endif /* EMSGSIZE */
#ifdef ENETDOWN
	case ENETDOWN:        result = "ENETDOWN"; break;
#endif /* ENETDOWN */
#ifdef ENETRESET
	case ENETRESET:       result = "ENETRESET"; break;
#endif /* ENETRESET */
#ifdef ENETUNREACH
	case ENETUNREACH:     result = "ENETUNREACH"; break;
#endif /* ENETUNREACH */
#ifdef ENOBUFS
	case ENOBUFS:         result = "ENOBUFS"; break;
#endif /* ENOBUFS */
#ifdef ENODATA
	case ENODATA:         result = "ENODATA"; break;
#endif /* ENODATA */
#ifdef ENOLINK
	case ENOLINK:         result = "ENOLINK"; break;
#endif /* ENOLINK */
#ifdef ENOMSG
	case ENOMSG:          result = "ENOMSG"; break;
#endif /* ENOMSG */
#ifdef ENOPROTOOPT
	case ENOPROTOOPT:     result = "ENOPROTOOPT"; break;
#endif /* ENOPROTOOPT */
#ifdef ENOSR
	case ENOSR:           result = "ENOSR"; break;
#endif /* ENOSR */
#ifdef ENOSTR
	case ENOSTR:          result = "ENOSTR"; break;
#endif /* ENOSTR */
#ifdef ENOTCONN
	case ENOTCONN:        result = "ENOTCONN"; break;
#endif /* ENOTCONN */
#ifdef ENOTRECOVERABLE
	case ENOTRECOVERABLE: result = "ENOTRECOVERABLE"; break;
#endif /* ENOTRECOVERABLE */
#ifdef ENOTSOCK
	case ENOTSOCK:        result = "ENOTSOCK"; break;
#endif /* ENOTSOCK */
#ifdef ENOTSUP
	case ENOTSUP:         result = "ENOTSUP"; break;
#endif /* ENOTSUP */
#ifdef EOPNOTSUPP
	case EOPNOTSUPP:      result = "EOPNOTSUPP"; break;
#endif /* EOPNOTSUPP */
#ifdef EOTHER
	case EOTHER:          result = "EOTHER"; break;
#endif /* EOTHER */
#ifdef EOVERFLOW
	case EOVERFLOW:       result = "EOVERFLOW"; break;
#endif /* EOVERFLOW */
#ifdef EOWNERDEAD
	case EOWNERDEAD:      result = "EOWNERDEAD"; break;
#endif /* EOWNERDEAD */
#ifdef EPROTO
	case EPROTO:          result = "EPROTO"; break;
#endif /* EPROTO */
#ifdef EPROTONOSUPPORT
	case EPROTONOSUPPORT: result = "EPROTONOSUPPORT"; break;
#endif /* EPROTONOSUPPORT */
#ifdef EPROTOTYPE
	case EPROTOTYPE:      result = "EPROTOTYPE"; break;
#endif /* EPROTOTYPE */
#ifdef ETIME
	case ETIME:           result = "ETIME"; break;
#endif /* ETIME */
#ifdef ETIMEDOUT
	case ETIMEDOUT:       result = "ETIMEDOUT"; break;
#endif /* ETIMEDOUT */
#ifdef ETXTBSY
	case ETXTBSY:         result = "ETXTBSY"; break;
#endif /* ETXTBSY */
#ifdef EFTYPE
	case EFTYPE:          result = "EFTYPE"; break;
#endif /* EFTYPE */
#ifdef ENMFILE
	case ENMFILE:         result = "ENMFILE"; break;
#endif /* ENMFILE */
#ifdef EPFNOSUPPORT
	case EPFNOSUPPORT:    result = "EPFNOSUPPORT"; break;
#endif /* EPFNOSUPPORT */
#ifdef EHOSTDOWN
	case EHOSTDOWN:       result = "EHOSTDOWN"; break;
#endif /* EHOSTDOWN */
#ifdef ETOOMANYREFS
	case ETOOMANYREFS:    result = "ETOOMANYREFS"; break;
#endif /* ETOOMANYREFS */
#ifdef EDQUOT
	case EDQUOT:          result = "EDQUOT"; break;
#endif /* EDQUOT */
#ifdef ESTALE
	case ESTALE:          result = "ESTALE"; break;
#endif /* ESTALE */
#ifdef ENOSHARE
	case ENOSHARE:        result = "ENOSHARE"; break;
#endif /* ENOSHARE */
#ifdef ECASECLASH
	case ECASECLASH:      result = "ECASECLASH"; break;
#endif /* ECASECLASH */
#ifdef ENOTBLK
	case ENOTBLK:         result = "ENOTBLK"; break;
#endif /* ENOTBLK */
#ifdef ECHRNG
	case ECHRNG:          result = "ECHRNG"; break;
#endif /* ECHRNG */
#ifdef EL2NSYNC
	case EL2NSYNC:        result = "EL2NSYNC"; break;
#endif /* EL2NSYNC */
#ifdef EL3HLT
	case EL3HLT:          result = "EL3HLT"; break;
#endif /* EL3HLT */
#ifdef EL3RST
	case EL3RST:          result = "EL3RST"; break;
#endif /* EL3RST */
#ifdef ELNRNG
	case ELNRNG:          result = "ELNRNG"; break;
#endif /* ELNRNG */
#ifdef EUNATCH
	case EUNATCH:         result = "EUNATCH"; break;
#endif /* EUNATCH */
#ifdef ENOCSI
	case ENOCSI:          result = "ENOCSI"; break;
#endif /* ENOCSI */
#ifdef EL2HLT
	case EL2HLT:          result = "EL2HLT"; break;
#endif /* EL2HLT */
#ifdef EBADE
	case EBADE:           result = "EBADE"; break;
#endif /* EBADE */
#ifdef EBADR
	case EBADR:           result = "EBADR"; break;
#endif /* EBADR */
#ifdef EXFULL
	case EXFULL:          result = "EXFULL"; break;
#endif /* EXFULL */
#ifdef ENOANO
	case ENOANO:          result = "ENOANO"; break;
#endif /* ENOANO */
#ifdef EBADRQC
	case EBADRQC:         result = "EBADRQC"; break;
#endif /* EBADRQC */
#ifdef EBADSLT
	case EBADSLT:         result = "EBADSLT"; break;
#endif /* EBADSLT */
#ifdef EBFONT
	case EBFONT:          result = "EBFONT"; break;
#endif /* EBFONT */
#ifdef ENONET
	case ENONET:          result = "ENONET"; break;
#endif /* ENONET */
#ifdef ENOPKG
	case ENOPKG:          result = "ENOPKG"; break;
#endif /* ENOPKG */
#ifdef EREMOTE
	case EREMOTE:         result = "EREMOTE"; break;
#endif /* EREMOTE */
#ifdef EADV
	case EADV:            result = "EADV"; break;
#endif /* EADV */
#ifdef ESRMNT
	case ESRMNT:          result = "ESRMNT"; break;
#endif /* ESRMNT */
#ifdef ECOMM
	case ECOMM:           result = "ECOMM"; break;
#endif /* ECOMM */
#ifdef ELBIN
	case ELBIN:           result = "ELBIN)"; break;
#endif /* ELBIN */
#ifdef EDOTDOT
	case EDOTDOT:         result = "EDOTDOT)"; break;
#endif /* EDOTDOT */
#ifdef ENOTUNIQ
	case ENOTUNIQ:        result = "ENOTUNIQ"; break;
#endif /* ENOTUNIQ */
#ifdef EBADFD
	case EBADFD:          result = "EBADFD"; break;
#endif /* EBADFD */
#ifdef EREMCHG
	case EREMCHG:         result = "EREMCHG"; break;
#endif /* EREMCHG */
#ifdef ELIBACC
	case ELIBACC:         result = "ELIBACC"; break;
#endif /* ELIBACC */
#ifdef ELIBBAD
	case ELIBBAD:         result = "ELIBBAD"; break;
#endif /* ELIBBAD */
#ifdef ELIBSCN
	case ELIBSCN:         result = "ELIBSCN"; break;
#endif /* ELIBSCN */
#ifdef ELIBMAX
	case ELIBMAX:         result = "ELIBMAX"; break;
#endif /* ELIBMAX */
#ifdef ELIBEXEC
	case ELIBEXEC:        result = "ELIBEXEC"; break;
#endif /* ELIBEXEC */
#ifdef ESHUTDOWN
	case ESHUTDOWN:       result = "ESHUTDOWN"; break;
#endif /* ESHUTDOWN */
#ifdef ESOCKTNOSUPPORT
	case ESOCKTNOSUPPORT: result = "ESOCKTNOSUPPORT"; break;
#endif /* ESOCKTNOSUPPORT */
#ifdef EPROCLIM
	case EPROCLIM:        result = "EPROCLIM"; break;
#endif /* EPROCLIM */
#ifdef EUSERS
	case EUSERS:          result = "EUSERS"; break;
#endif /* EUSERS */
#ifdef ENOMEDIUM
	case ENOMEDIUM:       result = "ENOMEDIUM)"; break;
#endif /* ENOMEDIUM */
#ifdef ESTRPIPE
	case ESTRPIPE:        result = "ESTRPIPE"; break;
#endif /* ESTRPIPE */
#ifdef EMULTIHOP
	case EMULTIHOP:       result = "EMULTIHOP"; break;
#endif /* EMULTIHOP */
#ifdef ERESTART
	case ERESTART:        result = "ERESTART"; break;
#endif /* ERESTART */
#ifdef EUCLEAN
	case EUCLEAN:         result = "EUCLEAN"; break;
#endif /* EUCLEAN */
#ifdef ENOTNAM
	case ENOTNAM:         result = "ENOTNAM"; break;
#endif /* ENOTNAM */
#ifdef ENAVAIL
	case ENAVAIL:         result = "ENAVAIL"; break;
#endif /* ENAVAIL */
#ifdef EISNAM
	case EISNAM:          result = "EISNAM"; break;
#endif /* EISNAM */
#ifdef EREMOTEIO
	case EREMOTEIO:       result = "EREMOTEIO"; break;
#endif /* EREMOTEIO */
#ifdef EMEDIUMTYPE
	case EMEDIUMTYPE:     result = "EMEDIUMTYPE"; break;
#endif /* EMEDIUMTYPE */
#ifdef ENOKEY
	case ENOKEY:          result = "ENOKEY"; break;
#endif /* ENOKEY */
#ifdef EKEYEXPIRED
	case EKEYEXPIRED:     result = "EKEYEXPIRED"; break;
#endif /* EKEYEXPIRED */
#ifdef EKEYREVOKED
	case EKEYREVOKED:     result = "EKEYREVOKED"; break;
#endif /* EKEYREVOKED */
#ifdef EKEYREJECTED
	case EKEYREJECTED:    result = "EKEYREJECTED"; break;
#endif /* EKEYREJECTED */
#ifdef ERFKILL
	case ERFKILL:         result = "ERFKILL"; break;
#endif /* ERFKILL */
#ifdef EHWPOISON
	case EHWPOISON:       result = "EHWPOISON"; break;
#endif /* EHWPOISON */
#if defined(STRUNCATE) && (!defined(ERANGE) || STRUNCATE != ERANGE)
	case STRUNCATE:       result = "STRUNCATE"; break;
#endif /* STRUNCATE && (!ERANGE || STRUNCATE != ERANGE) */
#if defined(EWOULDBLOCK) && (!defined(EAGAIN) || EWOULDBLOCK != EAGAIN)
	case EWOULDBLOCK:     result = "EWOULDBLOCK"; break;
#endif /* EWOULDBLOCK && (!EAGAIN || EWOULDBLOCK != EAGAIN) */
#if defined(EDEADLK) && (!defined(EDEADLOCK) || EDEADLOCK != EDEADLK)
	case EDEADLK:         result = "EDEADLK"; break;
#endif /* EDEADLK && (!EDEADLOCK || EDEADLOCK != EDEADLK) */

	default:
		result = NULL;
		break;
	}
	return result;
}

[[wunused, nothrow, ATTR_CONST, section(".text.crt.errno")]]
[[userimpl, impl_include("<bits/signum.h>"), impl_prefix(
#ifndef ___local_sys_siglist_defined
#define ___local_sys_siglist_defined 1
#undef sys_siglist
#undef _sys_siglist
#if defined(__CRT_HAVE___p_sys_siglist)
#ifndef ____p_sys_siglist_defined
#define ____p_sys_siglist_defined 1
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED __ATTR_RETNONNULL,char const *const *,__NOTHROW_NCX,__p_sys_siglist,(void),())
#endif /* !____p_sys_siglist_defined */
#define _sys_siglist  __p_sys_siglist()
#define sys_siglist   __p_sys_siglist()
#elif defined(__CRT_HAVE_sys_siglist)
#if defined(__CRT_HAVE__sys_siglist) || !defined(__NO_ASMNAME)
__LIBC char const *const _sys_siglist[_NSIG] __ASMNAME("sys_siglist");
#else /* __CRT_HAVE__sys_siglist || !__NO_ASMNAME */
#define _sys_siglist  sys_siglist
#endif /* !__CRT_HAVE__sys_siglist && __NO_ASMNAME */
__LIBC char const *const sys_siglist[_NSIG];
#elif defined(__CRT_HAVE__sys_siglist)
#ifndef __NO_ASMNAME
__LIBC char const *const sys_siglist[_NSIG] __ASMNAME("_sys_siglist");
#else /* !__NO_ASMNAME */
#define sys_siglist     _sys_siglist
#endif /* __NO_ASMNAME */
__LIBC char const *const _sys_siglist[_NSIG];
#endif /* sys_siglist... */
#endif /* !___local_sys_siglist_defined */
), impl_include("<bits/signum-values.h>")]]
char const *strsignal_s(int signum) {
#if defined(__CRT_HAVE___p_sys_siglist) || defined(__CRT_HAVE_sys_siglist) || defined(__CRT_HAVE__sys_siglist)
	return (unsigned int)errnum < _NSIG ? @_sys_siglist@[signum] : NULL;
#else /* __CRT_HAVE___p_sys_siglist || __CRT_HAVE_sys_siglist || __CRT_HAVE__sys_siglist */
	char const *result;
	switch (signum) {

#ifdef __SIGABRT_COMPAT
	case __SIGABRT_COMPAT : result = "SIGABRT_COMPAT"; break;
#endif /* __SIGABRT_COMPAT */
#ifdef __SIGBREAK
	case __SIGBREAK : result = "SIGBREAK"; break;
#endif /* __SIGBREAK */
#ifdef __SIGHUP
	case __SIGHUP   : result = "SIGHUP"; break;
#endif /* __SIGHUP */
#ifdef __SIGINT
	case __SIGINT   : result = "SIGINT"; break;
#endif /* __SIGINT */
#ifdef __SIGQUIT
	case __SIGQUIT  : result = "SIGQUIT"; break;
#endif /* __SIGQUIT */
#ifdef __SIGILL
	case __SIGILL   : result = "SIGILL"; break;
#endif /* __SIGILL */
#ifdef __SIGTRAP
	case __SIGTRAP  : result = "SIGTRAP"; break;
#endif /* __SIGTRAP */
#ifdef __SIGABRT
	case __SIGABRT  : result = "SIGABRT"; break;
#endif /* __SIGABRT */
#ifdef __SIGBUS
	case __SIGBUS   : result = "SIGBUS"; break;
#endif /* __SIGBUS */
#ifdef __SIGFPE
	case __SIGFPE   : result = "SIGFPE"; break;
#endif /* __SIGFPE */
#ifdef __SIGKILL
	case __SIGKILL  : result = "SIGKILL"; break;
#endif /* __SIGKILL */
#ifdef __SIGUSR1
	case __SIGUSR1  : result = "SIGUSR1"; break;
#endif /* __SIGUSR1 */
#ifdef __SIGSEGV
	case __SIGSEGV  : result = "SIGSEGV"; break;
#endif /* __SIGSEGV */
#ifdef __SIGUSR2
	case __SIGUSR2  : result = "SIGUSR2"; break;
#endif /* __SIGUSR2 */
#ifdef __SIGPIPE
	case __SIGPIPE  : result = "SIGPIPE"; break;
#endif /* __SIGPIPE */
#ifdef __SIGALRM
	case __SIGALRM  : result = "SIGALRM"; break;
#endif /* __SIGALRM */
#ifdef __SIGTERM
	case __SIGTERM  : result = "SIGTERM"; break;
#endif /* __SIGTERM */
#ifdef __SIGSTKFLT
	case __SIGSTKFLT: result = "SIGSTKFLT"; break;
#endif /* __SIGSTKFLT */
#ifdef __SIGCHLD
	case __SIGCHLD  : result = "SIGCHLD"; break;
#endif /* __SIGCHLD */
#ifdef __SIGCONT
	case __SIGCONT  : result = "SIGCONT"; break;
#endif /* __SIGCONT */
#ifdef __SIGSTOP
	case __SIGSTOP  : result = "SIGSTOP"; break;
#endif /* __SIGSTOP */
#ifdef __SIGTSTP
	case __SIGTSTP  : result = "SIGTSTP"; break;
#endif /* __SIGTSTP */
#ifdef __SIGTTIN
	case __SIGTTIN  : result = "SIGTTIN"; break;
#endif /* __SIGTTIN */
#ifdef __SIGTTOU
	case __SIGTTOU  : result = "SIGTTOU"; break;
#endif /* __SIGTTOU */
#ifdef __SIGURG
	case __SIGURG   : result = "SIGURG"; break;
#endif /* __SIGURG */
#ifdef __SIGXCPU
	case __SIGXCPU  : result = "SIGXCPU"; break;
#endif /* __SIGXCPU */
#ifdef __SIGXFSZ
	case __SIGXFSZ  : result = "SIGXFSZ"; break;
#endif /* __SIGXFSZ */
#ifdef __SIGVTALRM
	case __SIGVTALRM: result = "SIGVTALRM"; break;
#endif /* __SIGVTALRM */
#ifdef __SIGPROF
	case __SIGPROF  : result = "SIGPROF"; break;
#endif /* __SIGPROF */
#ifdef __SIGWINCH
	case __SIGWINCH : result = "SIGWINCH"; break;
#endif /* __SIGWINCH */
#ifdef __SIGIO
	case __SIGIO    : result = "SIGIO"; break;
#endif /* __SIGIO */
#ifdef __SIGSYS
	case __SIGSYS   : result = "SIGSYS"; break;
#endif /* __SIGSYS */
#ifdef __SIGEMT
	case __SIGEMT   : result = "SIGEMT"; break;
#endif /* __SIGEMT */
#ifdef __SIGLOST
	case __SIGLOST  : result = "SIGLOST"; break;
#endif /* __SIGLOST */
#if defined(__SIGCLD) && (!defined(__SIGCHLD) || __SIGCLD != __SIGCHLD)
	case __SIGCLD   : result = "SIGCLD"; break;
#endif /* __SIGCLD && (!__SIGCHLD || __SIGCLD != __SIGCHLD) */
#if defined(__SIGIOT) && (!defined(__SIGABRT) || __SIGIOT != __SIGABRT)
	case __SIGIOT   : result = "SIGIOT"; break;
#endif /* __SIGIOT && (!__SIGABRT || __SIGIOT != __SIGABRT) */
#if defined(__SIGPOLL) && (!defined(__SIGIO) || __SIGPOLL != __SIGIO)
	case __SIGPOLL   : result = "SIGPOLL"; break;
#endif /* __SIGPOLL && (!__SIGIO || __SIGPOLL != __SIGIO) */
#if defined(__SIGPWR) && (!defined(__SIGLOST) || __SIGPWR != __SIGLOST)
	case __SIGPWR   : result = "SIGPWR"; break;
#endif /* __SIGPWR && (!__SIGLOST || __SIGPWR != __SIGLOST) */

	default:
		result = NULL;
		break;
	}
	return result;
#endif /* !__CRT_HAVE___p_sys_siglist && !__CRT_HAVE_sys_siglist && !__CRT_HAVE__sys_siglist */
}



[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC, ATTR_LIBC_PRINTF(1, 0)]]
[[doc_alias("strdupf"), section(".text.crt.heap.strdup")]]
[[requires_function(vasprintf)]]
char *vstrdupf(char const *__restrict format, $va_list args) {
	char *result;
	return vasprintf(&result, format, args) >= 0 ? result : 0;
}

@@Print the given `FORMAT' into a newly allocated, heap-allocated string
[[wunused, ATTR_MALL_DEFAULT_ALIGNED]]
[[ATTR_MALLOC, ATTR_LIBC_PRINTF(1, 0)]]
[[section(".text.crt.heap.strdup")]]
char *strdupf(char const *__restrict format, ...)
	%{printf(vstrdupf)}

%{
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
}


/* TODO: strdupaf() */
/* TODO: vstrdupaf() */
/* TODO: mstrdupaf() */
/* TODO: vmstrdupaf() */


[[wunused, ATTR_PURE]]
int wildstrcmp([[nonnull]] char const *pattern,
               [[nonnull]] char const *string) {
	char card_post;
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*')
				++pattern;
			return -(int)(unsigned char)*pattern;
		}
		if (!*pattern)
			return (int)(unsigned char)*string; /* Pattern end doesn't match */
		if (*pattern == '*') {
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			for (;;) {
				char ch = *string++;
				if (ch == card_post) {
					/* Recursively check if the rest of the string and pattern match */
					if (!wildstrcmp(string, pattern))
						return 0;
				} else if (!ch) {
					return -(int)(unsigned char)card_post; /* Wildcard suffix not found */
				}
			}
		}
		if (*pattern == *string || *pattern == '?') {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((unsigned char)*string - (unsigned char)*pattern);
}

[[wunused, ATTR_PURE, section(".text.crt.unicode.static.memory")]]
int wildstrcasecmp([[nonnull]] char const *pattern,
                   [[nonnull]] char const *string) {
	char card_post, pattern_ch, string_ch;
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*') ++pattern;
			return -(int)*pattern;
		}
		if (!*pattern)
			return (int)*string; /* Pattern end doesn't match */
		if (*pattern == '*') {
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			card_post = tolower(card_post);
			for (;;) {
				char ch = *string++;
				if (card_post == ch || card_post == tolower(ch)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!wildstrcasecmp(string, pattern))
						return 0;
				} else if (!ch) {
					return -(int)(unsigned char)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		string_ch = *string;
		if (pattern_ch == string_ch || pattern_ch == '?' ||
		   (pattern_ch = tolower(pattern_ch),
		    string_ch = tolower(string_ch),
		    pattern_ch == string_ch)) {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((unsigned char)string_ch - (unsigned char)pattern_ch);
}

[[wunused, ATTR_PURE, requires($has_function(fuzzy_memcmp))]]
$size_t fuzzy_strcmp([[nonnull]] char const *s1, [[nonnull]] char const *s2) {
	return fuzzy_memcmp(s1, strlen(s1), s2, strlen(s2));
}

[[wunused, ATTR_PURE, requires($has_function(fuzzy_memcmp))]]
$size_t fuzzy_strncmp([[nonnull]] char const *s1, $size_t s1_maxlen,
                      [[nonnull]] char const *s2, $size_t s2_maxlen) {
	return fuzzy_memcmp(s1, strnlen(s1, s1_maxlen), s2, strnlen(s2, s2_maxlen));
}

[[section(".text.crt.unicode.static.memory")]]
[[wunused, ATTR_PURE, requires($has_function(fuzzy_memcasecmp))]]
$size_t fuzzy_strcasecmp([[nonnull]] char const *s1, [[nonnull]] char const *s2) {
	return fuzzy_memcasecmp(s1, strlen(s1), s2, strlen(s2));
}

[[section(".text.crt.unicode.static.memory")]]
[[wunused, ATTR_PURE, requires($has_function(fuzzy_memcasecmp))]]
$size_t fuzzy_strncasecmp([[nonnull]] char const *s1, $size_t s1_maxlen,
                          [[nonnull]] char const *s2, $size_t s2_maxlen) {
	return fuzzy_memcasecmp(s1, strnlen(s1, s1_maxlen), s2, strnlen(s2, s2_maxlen));
}

[[wunused, ATTR_PURE, requires_include("<parts/malloca.h>")]]
[[requires(!defined(__NO_MALLOCA))]]
[[impl_include("<parts/malloca.h>")]]
$size_t fuzzy_memcmp([[nonnull]] void const *s1, $size_t s1_bytes,
                     [[nonnull]] void const *s2, $size_t s2_bytes) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{
			void const *temp;
			temp = s1;
			s1   = s2;
			s2   = temp;
		}
		{
			size_t temp;
			temp     = s1_bytes;
			s1_bytes = s2_bytes;
			s2_bytes = temp;
		}
	}
	__malloca_tryhard(v0, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0)
		return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_bytes; ++i)
		v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_bytes; j++) {
			cost  = ((byte_t *)s1)[i] != ((byte_t *)s2)[j];
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		memcpyc((u8 *)v0, (u8 *)v1, s2_bytes, sizeof(size_t));
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}

[[wunused, ATTR_PURE, requires_include("<parts/malloca.h>")]]
[[section(".text.crt.unicode.static.memory")]]
[[requires(!defined(__NO_MALLOCA))]]
[[impl_include("<parts/malloca.h>")]]
$size_t fuzzy_memcasecmp([[nonnull]] void const *s1, $size_t s1_bytes,
                         [[nonnull]] void const *s2, $size_t s2_bytes) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{
			void const *temp;
			temp = (void const *)s1;
			s1   = s2;
			*(void const **)&s2 = temp;
		}
		{
			size_t temp;
			temp     = s1_bytes;
			s1_bytes = s2_bytes;
			s2_bytes = temp;
		}
	}
	__malloca_tryhard(v0, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0)
		return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_bytes; ++i)
		v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_bytes; j++) {
			byte_t c1 = ((byte_t *)s1)[i];
			byte_t c2 = ((byte_t *)s2)[j];
			cost  = c1 != c2 && tolower(c1) != tolower(c2);
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		memcpyc((u8 *)v0, (u8 *)v1, s2_bytes, sizeof(size_t));
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}

%#ifdef __USE_XOPEN2K8
[[wunused, ATTR_PURE, requires_function(fuzzy_memcasecmp_l)]]
[[section(".text.crt.unicode.locale.memory")]]
$size_t fuzzy_strcasecmp_l([[nonnull]] char const *s1, [[nonnull]] char const *s2, $locale_t locale) {
	return fuzzy_memcasecmp_l(s1, strlen(s1), s2, strlen(s2), locale);
}

[[wunused, ATTR_PURE, requires_function(fuzzy_memcasecmp_l)]]
[[section(".text.crt.unicode.locale.memory")]]
$size_t fuzzy_strncasecmp_l([[nonnull]] char const *s1, $size_t s1_maxlen,
                            [[nonnull]] char const *s2, $size_t s2_maxlen, $locale_t locale) {
	return fuzzy_memcasecmp_l(s1, strnlen(s1, s1_maxlen), s2, strnlen(s2, s2_maxlen), locale);
}

[[wunused, ATTR_PURE, section(".text.crt.unicode.locale.memory")]]
int wildstrcasecmp_l([[nonnull]] char const *pattern,
                     [[nonnull]] char const *string, $locale_t locale) {
	char card_post, pattern_ch, string_ch;
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*') ++pattern;
			return -(int)*pattern;
		}
		if (!*pattern)
			return (int)*string; /* Pattern end doesn't match */
		if (*pattern == '*') {
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			card_post = tolower_l(card_post, locale);
			for (;;) {
				char ch = *string++;
				if (card_post == ch || card_post == tolower_l(ch, locale)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!strcasecmp_l(string, pattern, locale))
						return 0;
				} else if (!ch) {
					return -(int)(unsigned char)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		string_ch = *string;
		if (pattern_ch == string_ch || pattern_ch == '?' ||
		   (pattern_ch = tolower_l(pattern_ch, locale),
		    string_ch = tolower_l(string_ch, locale),
		    pattern_ch == string_ch)) {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((unsigned char)string_ch - (unsigned char)pattern_ch);
}

[[wunused, ATTR_PURE, requires_include("<parts/malloca.h>")]]
[[requires(!defined(__NO_MALLOCA)), section(".text.crt.unicode.locale.memory")]]
$size_t fuzzy_memcasecmp_l([[nonnull]] void const *s1, $size_t s1_bytes,
                           [[nonnull]] void const *s2, $size_t s2_bytes,
                           $locale_t locale) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{
			void const *temp;
			temp = (void const *)s1;
			s1   = s2;
			*(void const **)&s2 = temp;
		}
		{
			size_t temp;
			temp     = s1_bytes;
			s1_bytes = s2_bytes;
			s2_bytes = temp;
		}
	}
	__malloca_tryhard(v0, (s2_bytes + 1) * sizeof(size_t));
@@pp_ifdef __malloca_tryhard_mayfail@@
	if unlikely(!v0)
		return (size_t)-1;
@@pp_endif@@
	__malloca_tryhard(v1, (s2_bytes + 1) * sizeof(size_t));
@@pp_ifdef __malloca_tryhard_mayfail@@
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
@@pp_endif@@
	for (i = 0; i < s2_bytes; ++i)
		v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_bytes; j++) {
			byte_t c1 = ((byte_t *)s1)[i];
			byte_t c2 = ((byte_t *)s2)[j];
			cost  = c1 != c2 && tolower_l(c1, locale) != tolower_l(c2, locale);
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		memcpyc((u8 *)v0, (u8 *)v1, s2_bytes, sizeof(size_t));
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}
%#endif /* __USE_XOPEN2K8 */

%{

#ifdef __USE_STRING_BWLQ
}

[[wunused, ATTR_PURE]]
$size_t fuzzy_memcmpb([[nonnull]] void const *s1, $size_t s1_bytes,
                      [[nonnull]] void const *s2, $size_t s2_bytes) = fuzzy_memcmp;

[[wunused, ATTR_PURE, requires_include("<parts/malloca.h>")]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("fuzzy_wmemcmp")]]
[[export_alias("DOS$fuzzy_wmemcmp"), requires(!defined(__NO_MALLOCA))]]
$size_t fuzzy_memcmpw([[nonnull]] void const *s1, $size_t s1_words,
                      [[nonnull]] void const *s2, $size_t s2_words) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_words)
		return s2_words;
	if unlikely(!s2_words)
		return s1_words;
	if (s2_words > s1_words) {
		{
			void const *temp;
			temp = s1;
			s1   = s2;
			s2   = temp;
		}
		{
			size_t temp;
			temp     = s1_words;
			s1_words = s2_words;
			s2_words = temp;
		}
	}
	__malloca_tryhard(v0, (s2_words+1) * sizeof(size_t));
@@pp_ifdef __malloca_tryhard_mayfail@@
	if unlikely(!v0)
		return (size_t)-1;
@@pp_endif@@
	__malloca_tryhard(v1, (s2_words+1) * sizeof(size_t));
@@pp_ifdef __malloca_tryhard_mayfail@@
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
@@pp_endif@@
	for (i = 0; i < s2_words; ++i)
		v0[i] = i;
	for (i = 0; i < s1_words; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_words; j++) {
			cost  = ((u16 *)s1)[i] != ((u16 *)s2)[j];
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		memcpyc((u8 *)v0, (u8 *)v1, s2_words, sizeof(size_t));
	}
	temp = v1[s2_words];
	__freea(v1);
	__freea(v0);
	return temp;
}


[[wunused, ATTR_PURE, requires_include("<parts/malloca.h>")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("fuzzy_wmemcmp")]]
[[if(defined(__PE__)), alias("KOS$fuzzy_wmemcmp")]]
[[export_as("fuzzy_wmemcmp"), requires(!defined(__NO_MALLOCA))]]
$size_t fuzzy_memcmpl([[nonnull]] void const *s1, $size_t s1_dwords,
                      [[nonnull]] void const *s2, $size_t s2_dwords) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_dwords)
		return s2_dwords;
	if unlikely(!s2_dwords)
		return s1_dwords;
	if (s2_dwords > s1_dwords) {
		{
			void const *temp;
			temp = s1;
			s1   = s2;
			s2   = temp;
		}
		{
			size_t temp;
			temp      = s1_dwords;
			s1_dwords = s2_dwords;
			s2_dwords = temp;
		}
	}
	__malloca_tryhard(v0, (s2_dwords+1) * sizeof(size_t));
@@pp_ifdef __malloca_tryhard_mayfail@@
	if unlikely(!v0)
		return (size_t)-1;
@@pp_endif@@
	__malloca_tryhard(v1, (s2_dwords+1) * sizeof(size_t));
@@pp_ifdef __malloca_tryhard_mayfail@@
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
@@pp_endif@@
	for (i = 0; i < s2_dwords; ++i)
		v0[i] = i;
	for (i = 0; i < s1_dwords; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_dwords; j++) {
			cost  = ((u32 *)s1)[i] != ((u32 *)s2)[j];
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		memcpyc((u8 *)v0, (u8 *)v1, s2_dwords, sizeof(size_t));
	}
	temp = v1[s2_dwords];
	__freea(v1);
	__freea(v0);
	return temp;
}

%#ifdef __UINT64_TYPE__
[[wunused, ATTR_PURE, requires_include("<parts/malloca.h>")]]
[[requires(!defined(__NO_MALLOCA))]]
$size_t fuzzy_memcmpq([[nonnull]] void const *s1, $size_t s1_qwords,
                      [[nonnull]] void const *s2, $size_t s2_qwords) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_qwords)
		return s2_qwords;
	if unlikely(!s2_qwords)
		return s1_qwords;
	if (s2_qwords > s1_qwords) {
		{
			void const *temp;
			temp = s1;
			s1   = s2;
			s2   = temp;
		}
		{
			size_t temp;
			temp      = s1_qwords;
			s1_qwords = s2_qwords;
			s2_qwords = temp;
		}
	}
	__malloca_tryhard(v0, (s2_qwords+1) * sizeof(size_t));
@@pp_ifdef __malloca_tryhard_mayfail@@
	if unlikely(!v0)
		return (size_t)-1;
@@pp_endif@@
	__malloca_tryhard(v1, (s2_qwords+1) * sizeof(size_t));
@@pp_ifdef __malloca_tryhard_mayfail@@
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
@@pp_endif@@
	for (i = 0; i < s2_qwords; ++i)
		v0[i] = i;
	for (i = 0; i < s1_qwords; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_qwords; j++) {
			cost  = ((u64 *)s1)[i] != ((u64 *)s2)[j];
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		memcpyc((u8 *)v0, (u8 *)v1, s2_qwords, sizeof(size_t));
	}
	temp = v1[s2_qwords];
	__freea(v1);
	__freea(v0);
	return temp;
}

%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_STRING_BWLQ */


[[wunused, ATTR_PURE, export_alias("_strncoll")]]
[[section(".text.crt.unicode.static.memory")]]
int strncoll([[nonnull]] char const *s1, [[nonnull]] char const *s2, $size_t maxlen) {
	return strncmp(s1, s2, maxlen);
}

[[export_alias("_stricoll"), alias("strcasecmp", "_stricmp", "stricmp", "_strcmpi", "strcmpi")]]
[[wunused, ATTR_PURE, section(".text.crt.unicode.static.memory")]]
int strcasecoll([[nonnull]] char const *s1, [[nonnull]] char const *s2) {
	return strcasecmp(s1, s2);
}

[[export_alias("_strnicoll"), alias("strncasecmp")]]
[[wunused, ATTR_PURE, section(".text.crt.unicode.static.memory")]]
int strncasecoll([[nonnull]] char const *s1, [[nonnull]] char const *s2, $size_t maxlen) {
	return strncasecmp(s1, s2, maxlen);
}

[[ATTR_LEAF]]
strnrev:([[nonnull]] char *__restrict str, $size_t maxlen) -> [[== str]] char * {
	return (char *)memrev(str, strnlen(str, maxlen));
}

[[ATTR_LEAF, section(".text.crt.unicode.static.memory")]]
strnlwr:([[nonnull]] char *__restrict str, $size_t maxlen) -> [[== str]] char * {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = tolower(ch);
	return str;
}

[[ATTR_LEAF, section(".text.crt.unicode.static.memory")]]
strnupr:([[nonnull]] char *__restrict str, $size_t maxlen) -> [[== str]] char * {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = toupper(ch);
	return str;
}


%#ifdef __USE_XOPEN2K8
[[wunused, ATTR_PURE, export_alias("_strncoll_l")]]
[[section(".text.crt.unicode.locale.memory")]]
int strncoll_l([[nonnull]] char const *s1,
               [[nonnull]] char const *s2,
               $size_t maxlen, $locale_t locale) {
	(void)locale;
	return strncoll(s1, s2, maxlen);
}

[[wunused, ATTR_PURE, export_alias("_stricoll_l")]]
[[section(".text.crt.unicode.locale.memory")]]
int strcasecoll_l([[nonnull]] char const *s1, [[nonnull]] char const *s2, $locale_t locale) {
	return strcasecmp_l(s1, s2, locale);
}

[[wunused, ATTR_PURE, export_alias("_strnicoll_l")]]
[[alias("strncasecmp_l", "_strnicmp_l", "_strncmpi_l")]]
[[section(".text.crt.unicode.locale.memory")]]
int strncasecoll_l([[nonnull]] char const *s1,
                   [[nonnull]] char const *s2,
                   $size_t maxlen, $locale_t locale) {
	(void)locale;
	return strncasecoll(s1, s2, maxlen);
}

[[ATTR_LEAF, export_alias("_strlwr_l")]]
[[section(".text.crt.unicode.locale.memory")]]
strlwr_l:([[nonnull]] char *__restrict str, $locale_t locale) -> [[== str]] char * {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = tolower_l(ch, locale);
	return str;
}

[[ATTR_LEAF, export_alias("_strupr_l")]]
[[section(".text.crt.unicode.locale.memory")]]
strupr_l:([[nonnull]] char *__restrict str, $locale_t locale) -> [[== str]] char * {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = toupper_l(ch, locale);
	return str;
}

[[ATTR_LEAF, section(".text.crt.unicode.locale.memory")]]
strnlwr_l:([[nonnull]] char *__restrict str, $size_t maxlen, $locale_t locale) -> [[== str]] char * {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = tolower_l(ch, locale);
	return str;
}

[[ATTR_LEAF, section(".text.crt.unicode.locale.memory")]]
strnupr_l:([[nonnull]] char *__restrict str, $size_t maxlen, $locale_t locale) -> [[== str]] char * {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = toupper_l(ch, locale);
	return str;
}

[[ATTR_LEAF]]
memrev:([[nonnull]] void *__restrict base, $size_t n_bytes) -> [[== base]] void * {
	byte_t *iter, *end;
	end = (iter = (byte_t *)base) + n_bytes;
	while (iter < end) {
		byte_t temp = *iter;
		*iter++ = *--end;
		*end = temp;
	}
	return base;
}
%#endif /* __USE_XOPEN2K8 */

%#ifdef __USE_STRING_BWLQ
[[ATTR_LEAF]]
memrevb:([[nonnull]] void *__restrict base, $size_t n_bytes) -> [[== base]] $uint8_t * = memrev;

[[ATTR_LEAF]]
memrevw:([[nonnull]] void *__restrict base, $size_t n_words) -> [[== base]] $uint16_t * {
	u16 *iter, *end;
	end = (iter = (u16 *)base) + n_words;
	while (iter < end) {
		u16 temp = *iter;
		*iter++ = *--end;
		*end = temp;
	}
	return (u16 *)base;
}

[[ATTR_LEAF]]
memrevl:([[nonnull]] void *__restrict base, $size_t n_dwords) -> [[== base]] $uint32_t * {
	u32 *iter, *end;
	end = (iter = (u32 *)base) + n_dwords;
	while (iter < end) {
		u32 temp = *iter;
		*iter++ = *--end;
		*end = temp;
	}
	return (u32 *)base;
}

%#ifdef __UINT64_TYPE__
[[ATTR_LEAF]]
memrevq:([[nonnull]] void *__restrict base, $size_t n_qwords) -> [[== base]] $uint64_t * {
	u64 *iter, *end;
	end = (iter = (u64 *)base) + n_qwords;
	while (iter < end) {
		u64 temp = *iter;
		*iter++ = *--end;
		*end = temp;
	}
	return (u64 *)base;
}
%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_STRING_BWLQ */

%#endif /* __USE_KOS */
%
%
%#if defined(__USE_KOS) || defined(__USE_DOS)

[[export_alias("_strlwr"), section(".text.crt.unicode.static.memory")]]
strlwr:([[nonnull]] char *__restrict str) -> [[== str]] char * {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = tolower(ch);
	return str;
}

[[export_alias("_strupr"), section(".text.crt.unicode.static.memory")]]
strupr:([[nonnull]] char *__restrict str) -> [[== str]] char * {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = toupper(ch);
	return str;
}

[[export_alias("_strset"), ATTR_LEAF]]
strset:([[nonnull]] char *__restrict str, int ch) -> [[== str]] char * {
	char *iter;
	for (iter = str; *iter; ++iter)
		*iter = (char)ch;
	return str;
}

[[export_alias("_strnset"), ATTR_LEAF]]
strnset:([[nonnull]] char *__restrict str, int ch, $size_t maxlen) -> [[== str]] char * {
	char *iter;
	for (iter = str; maxlen-- && *iter; ++iter)
		*iter = (char)ch;
	return str;
}

[[alias("_strrev"), ATTR_LEAF]]
strrev:([[nonnull]] char *__restrict str) -> [[== str]] char * {
	return (char *)memrev(str, strlen(str));
}
%{
#endif /* __USE_KOS || __USE_DOS */


#ifdef __USE_DOS
}

%[insert:function(_memccpy = memccpy)]
%[insert:function(_memicmp = memcasecmp)]
%[insert:function(_memicmp_l = memcasecmp_l)]
%[insert:function(memicmp = memcasecmp)]

[[impl_include("<parts/errno.h>", "<libc/string.h>")]]
[[section(".text.crt.dos.string.memory")]]
$errno_t _strset_s([[nonnull]] char *dst, $size_t dstsize, int ch) {
	char *p;
	size_t remaining;
	if (!dst && dstsize != 0)
		return __EINVAL;
	p = dst;
	remaining = dstsize;
	while (*p && --remaining != 0)
		*p++ = (char)ch;
	if (remaining == 0) {
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return __EINVAL;
	}
	__libc_memsetc(p, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}

%
%#ifdef __USE_DOS_SLIB
[[impl_include("<parts/errno.h>", "<libc/string.h>")]]
[[section(".text.crt.dos.string.memory")]]
$errno_t memcpy_s([[nonnull]] void *dst, rsize_t dstlength,
                  [[nonnull]] void const *src, rsize_t srclength) {
	if (!srclength)
		return 0;
	if (dst == NULL)
		return __EINVAL;
	if (!src || dstlength < srclength) {
		__libc_memsetc(dst, 0, dstlength, __SIZEOF_CHAR__);
		if (!src)
			return __EINVAL;
		if (dstlength < srclength)
			return __ERANGE;
		return __EINVAL;
	}
	__libc_memcpyc(dst, src, srclength, __SIZEOF_CHAR__);
	return 0;
}

[[impl_include("<parts/errno.h>", "<libc/string.h>")]]
[[section(".text.crt.dos.string.memory")]]
$errno_t memmove_s([[nonnull]] void *dst, rsize_t dstlength,
                   [[nonnull]] void const *src, rsize_t srclength) {
	if (!srclength)
		return 0;
	if (!dst || !src)
		return __EINVAL;
	if (dstlength < srclength)
		return __ERANGE;
	__libc_memmovec(dst, src, srclength, __SIZEOF_CHAR__);
	return 0;
}


[[impl_include("<parts/errno.h>", "<libc/string.h>")]]
[[section(".text.crt.dos.string.memory")]]
$errno_t strcpy_s(char *dst, $size_t dstsize, char const *src) {
	char *iter;
	size_t remaining;
	if ((!dst && dstsize) || !src)
		return __EINVAL;
	iter = dst;
	remaining = dstsize;
	while ((*iter++ = *src++) != 0 && --remaining)
		;
	if (!remaining) {
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return __ERANGE;
	}
	__libc_memsetc(iter, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}

[[impl_include("<parts/errno.h>")]]
[[section(".text.crt.dos.string.memory")]]
$errno_t strcat_s(char *dst, $size_t dstsize, char const *src) {
	if (!dst || !src)
		return __EINVAL;
	while (dstsize && *dst) {
		++dst;
		--dstsize;
	}
	if (!dstsize)
		return __EINVAL;
	while ((*dst++ = *src++) != 0 && --dstsize)
		;
	if (!dstsize)
		return __ERANGE;
	return 0;
}

[[guard, inline, nocrt, wunused, ATTR_PURE]]
$size_t strnlen_s([[nullable]] char const *str, $size_t maxlen) {
	return str ? strnlen(str, maxlen) : 0;
}

[[impl_include("<parts/errno.h>", "<libc/string.h>")]]
[[section(".text.crt.dos.string.memory")]]
$errno_t strncat_s(char *dst, rsize_t dstsize, const char *src, rsize_t maxlen) {
	char *iter;
	size_t remaining;
	if (!maxlen && !dst && !dstsize)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return __EINVAL;
	for (iter = dst, remaining = dstsize; remaining && *iter; ++iter, --remaining)
		;
	if (!remaining) {
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return __EINVAL;
	}
	if (maxlen == (size_t)-1) {
		while ((*iter++ = *src++) != 0 && --dstsize)
			;
	} else {
		if (maxlen >= remaining)
			return __ERANGE;
		while (maxlen && (*iter++ = *src++) != 0 && --remaining)
			--maxlen;
		if (!maxlen)
			*iter = 0;
	}
	if (!remaining) {
		if (maxlen == (size_t)-1) {
			dst[dstsize - 1] = 0;
			return __STRUNCATE;
		}
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return __ERANGE;
	}
	__libc_memsetc(iter, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}

[[impl_include("<parts/errno.h>", "<libc/string.h>")]]
[[section(".text.crt.dos.string.memory")]]
$errno_t strncpy_s(char *dst, $size_t dstsize, char const *src, $size_t maxlen) {
	char *iter;
	size_t remaining;
	if (maxlen == 0 && dst == NULL && dstsize == 0)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return __EINVAL;
	if (!maxlen) {
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return 0;
	}
	iter = dst;
	remaining = dstsize;
	if (maxlen == (size_t)-1) {
		while ((*iter++ = *src++) != 0 && --remaining)
			;
	} else {
		if (maxlen >= remaining)
			return __ERANGE;
		while ((*iter++ = *src++) != 0 && --remaining && --maxlen)
			;
		if (!maxlen)
			*iter = 0;
	}
	if (!remaining) {
		if (maxlen == (size_t)-1) {
			dst[dstsize - 1] = 0;
			return __STRUNCATE;
		}
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return __ERANGE;
	}
	__libc_memsetc(iter, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}

%[insert:function(strtok_s = strtok_r)]
%#endif /* __USE_DOS_SLIB */

%[insert:function(_strdup = strdup)]
%[insert:function(_stricmp = strcasecmp)]
%[insert:function(_strcmpi = strcasecmp)]
%[insert:function(_stricmp_l = strcasecmp_l)]
%[insert:function(_strcoll_l = strcoll_l)]
%[insert:function(_stricoll = strcasecoll)]
%[insert:function(_stricoll_l = strcasecoll_l)]
%[insert:function(_strncoll = strncoll)]
%[insert:function(_strncoll_l = strncoll_l)]
%[insert:function(_strnicoll = strncasecoll)]
%[insert:function(_strnicoll_l = strncasecoll_l)]

[[cp, wunused, section(".text.crt.dos.errno")]]
[[impl_prefix(DEFINE_STRERROR_BUF)]]
[[requires($has_function(_strerror_s))]]
char *_strerror(char const *message) {
	_strerror_s(__NAMESPACE_LOCAL_SYM strerror_buf,
	            COMPILER_LENOF(__NAMESPACE_LOCAL_SYM strerror_buf),
	            message);
	return __NAMESPACE_LOCAL_SYM strerror_buf;
}

[[cp, section(".text.crt.dos.errno")]]
[[requires_include("<parts/errno.h>")]]
[[requires(defined(__libc_geterrno))]]
[[impl_include("<bits/types.h>")]]
[[impl_include("<parts/errno.h>")]]
$errno_t _strerror_s([[nonnull]] char *__restrict buf,
                     $size_t buflen, char const *message) {
	char const *string;
	size_t reqlen;
	errno_t eno = __libc_geterrno();
	string = strerror_s(eno);
	if (string) {
		if (message) {
			reqlen = snprintf(buf, buflen, "%s: %s\n", message, string);
		} else {
			reqlen = snprintf(buf, buflen, "%s\n", string);
		}
	} else if (message) {
		reqlen = snprintf(buf, buflen, "%s: Unknown error %d\n", message, eno);
	} else {
		reqlen = snprintf(buf, buflen, "Unknown error %d\n", eno);
	}
	if (reqlen > buflen) {
@@pp_ifdef ERANGE@@
		return ERANGE;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	return 0;
}

[[ATTR_LEAF, impl_include("<parts/errno.h>")]]
[[section(".text.crt.dos.unicode.static.memory")]]
$errno_t _strlwr_s(char *buf, $size_t buflen) {
	char *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (strnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = tolower(ch);
	return 0;
}

[[ATTR_LEAF, section(".text.crt.dos.unicode.static.memory")]]
$errno_t _strupr_s(char *buf, $size_t buflen) {
	char *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (strnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = toupper(ch);
	return 0;
}

[[ATTR_LEAF, section(".text.crt.dos.unicode.locale.memory")]]
$errno_t _strlwr_s_l(char *buf, $size_t buflen, $locale_t locale) {
	char *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (strnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = tolower_l(ch, locale);
	return 0;
}

[[ATTR_LEAF, section(".text.crt.dos.unicode.locale.memory")]]
$errno_t _strupr_s_l(char *buf, $size_t buflen, $locale_t locale) {
	char *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (strnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = toupper_l(ch, locale);
	return 0;
}

%[insert:function(_strnicmp = strncasecmp)]
%[insert:function(_strnicmp_l = strncasecmp_l)]

[[section(".text.crt.dos.string.memory")]]
[[ATTR_LEAF, impl_include("<parts/errno.h>", "<libc/string.h>")]]
$errno_t _strnset_s(char *__restrict buf, $size_t buflen, int ch, $size_t maxlen) {
	char *iter;
	size_t remaining;
	if (maxlen == 0 && buf == NULL && buflen == 0)
		return 0;
	if (!buf && buflen)
		return __EINVAL;
	if (maxlen >= buflen)
		return __ERANGE;
	iter = buf;
	remaining = buflen;
	while (*iter != 0 && maxlen && --remaining) {
		*iter++ = (wchar_t)ch;
		--maxlen;
	}
	if (!maxlen) {
		while (*iter && --remaining)
			++iter;
	}
	if (!remaining) {
		__libc_memsetc(buf, 0, buflen, __SIZEOF_CHAR__);
		return __EINVAL;
	}
	__libc_memsetc(iter, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}

%[insert:function(_strrev = strrev)]
%[insert:function(_strxfrm_l = strxfrm_l)]
%[insert:function(stricmp = strcasecmp)]
%[insert:function(strcmpi = strcasecmp)]
%[insert:function(strnicmp = strncasecmp)]

/* The following aren't actually defined by DOS, but one might assume that they were */
%[insert:function(_strncmpi = strncasecmp)]
%[insert:function(_strncmpi_l = strncasecmp_l)]
%[insert:function(strncmpi = strncasecmp)]

%
%#ifndef _WSTRING_DEFINED
%#define _WSTRING_DEFINED 1
%[insert:guarded_function(_wcsdup = wcsdup)]
%[insert:extern(wcscat)]
%[insert:extern(wcschr)]
%[insert:extern(wcscmp)]
%[insert:extern(wcscpy)]
%[insert:extern(wcscspn)]
%[insert:extern(wcslen)]
%[insert:extern(wcsnlen)]
%[insert:extern(wcsncat)]
%[insert:extern(wcsncmp)]
%[insert:extern(wcsncpy)]
%[insert:extern(wcspbrk)]
%[insert:extern(wcsrchr)]
%[insert:extern(wcsspn)]
%[insert:extern(wcsstr)]
%[insert:extern(wcstok)]
%[insert:extern(_wcserror)]
%[insert:extern(_wcserror_s)]
%[insert:extern(__wcserror)]
%[insert:extern(__wcserror_s)]
%[insert:guarded_function(_wcsicmp = wcscasecmp)]
%[insert:guarded_function(_wcsicmp_l = wcscasecmp_l)]
%[insert:guarded_function(_wcsnicmp = wcsncasecmp)]
%[insert:guarded_function(_wcsnicmp_l = wcsncasecmp_l)]
%[insert:extern(_wcsnset_s)]
%[insert:guarded_function(_wcsnset = wcsnset)]
%[insert:guarded_function(_wcsrev = wcsrev)]
%[insert:extern(_wcsset_s)]
%[insert:guarded_function(_wcsset = wcsset)]
%[insert:extern(_wcslwr_s)]
%[insert:guarded_function(_wcslwr = wcslwr)]
%[insert:extern(_wcslwr_s_l)]
%[insert:guarded_function(_wcslwr_l = wcslwr_l)]
%[insert:extern(_wcsupr_s)]
%[insert:guarded_function(_wcsupr = wcsupr)]
%[insert:extern(_wcsupr_s_l)]
%[insert:guarded_function(_wcsupr_l = wcsupr_l)]
%[insert:extern(wcsxfrm)]
%[insert:guarded_function(_wcsxfrm_l = wcsxfrm_l)]
%[insert:extern(wcscoll)]
%[insert:guarded_function(_wcscoll_l = wcscoll_l)]
%[insert:guarded_function(_wcsicoll = wcscasecoll)]
%[insert:guarded_function(_wcsicoll_l = wcscasecoll_l)]
%[insert:guarded_function(_wcsncoll = wcsncasecoll)]
%[insert:guarded_function(_wcsncoll_l = wcsncoll_l)]
%[insert:guarded_function(_wcsnicoll = wcsncasecoll)]
%[insert:guarded_function(_wcsnicoll_l = wcsncasecoll_l)]
%[insert:extern(wcsdup)]
%[insert:guarded_function(wcswcs = wcsstr)]
%[insert:guarded_function(wcsicmp = wcscasecmp)]
%[insert:guarded_function(wcsnicmp = wcsncasecmp)]
%[insert:extern(wcsnset)]
%[insert:extern(wcsrev)]
%[insert:extern(wcsset)]
%[insert:extern(wcslwr)]
%[insert:extern(wcsupr)]
%[insert:guarded_function(wcsicoll = wcscasecoll)]
%#ifdef __USE_DOS_SLIB
%[insert:extern(wcscat_s)]
%[insert:extern(wcscpy_s)]
%[insert:extern(wcsncat_s)]
%[insert:extern(wcsncpy_s)]
%[insert:guarded_function(wcstok_s = wcstok)]
%[insert:extern(wcsnlen_s)]
%#endif  /* __USE_DOS_SLIB */
%#endif /* !_WSTRING_DEFINED */

%{
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


}
%#if defined(__USE_BSD) || defined(__USE_KOS)

@@Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
@@If found, return a pointer to its location within `str', else return `NULL'
@@This function originates from BSD, but is also provided as a KOS extension
[[wunused, ATTR_PURE]]
char *strnstr([[nonnull]] char const *haystack, [[nonnull]] char const *needle, $size_t haystack_maxlen)
	[([[nonnull]] char *haystack, [[nonnull]] char *needle, $size_t haystack_maxlen): char *]
	[([[nonnull]] char const *haystack, [[nonnull]] char const *needle, $size_t haystack_maxlen): char const *]
{
	char ch, needle_start = *needle++;
	while (haystack_maxlen-- && (ch = *haystack++) != '\0') {
		if (ch == needle_start) {
			char const *hay2, *ned_iter;
			size_t maxlen2;
			hay2     = haystack;
			ned_iter = needle;
			maxlen2  = haystack_maxlen;
			while ((ch = *ned_iter++) != '\0') {
				if (!maxlen2-- || *hay2++ != ch)
					goto miss;
			}
			return (char *)haystack - 1;
		}
miss:
		;
	}
	return NULL;
}

%#endif /* __USE_BSD || __USE_KOS */

%
%
%#ifdef __USE_BSD
%(auto_source)#include <sys/stat.h>

@@Generate a file mode representation similar to what's printed by `ls -l'
@@The representation is written to `p', and `mode' is the value as returned
@@by `stat(2)' in `struct stat::st_mode'
@@The format written is:
@@   p[0]  = <mode & S_IFMT>: { S_IFDIR: 'd', S_IFCHR: 'c', S_IFBLK:  'b',
@@                              S_IFREG: '-', S_IFLNK: 'l', S_IFSOCK: 's',
@@                              S_IFIFO: 'p' }, else: '?';
@@   p[1]  = mode & S_IRUSR ? 'r' : '-';
@@   p[2]  = mode & S_IWUSR ? 'w' : '-';
@@   p[3]  = <mode & S_IXUSR | S_ISUID>: { 0: '-', S_IXUSR: 'x', S_ISUID: 'S',
@@                                         S_IXUSR | S_ISUID: 's' };
@@   p[4]  = mode & S_IRGRP ? 'r' : '-';
@@   p[5]  = mode & S_IWGRP ? 'w' : '-';
@@   p[6]  = <mode & S_IXGRP | S_ISGID>: { 0: '-', S_IXGRP: 'x', S_ISGID: 'S',
@@                                         S_IXGRP | S_ISGID: 's' };
@@   p[7]  = mode & S_IROTH ? 'r' : '-';
@@   p[8]  = mode & S_IWOTH ? 'w' : '-';
@@   p[9]  = <mode & S_IXOTH | S_ISVTX>: { 0: '-', S_IXOTH: 'x', S_ISVTX: 'T',
@@                                         S_IXOTH | S_ISVTX: 't' };
@@   p[10] = ' '; // '+', if "alternate or additional access control
@@                //          methods associated with the inode"
@@   p[11] = '\0';
[[impl_include("<asm/stat.h>")]]
[[section(".text.crt.bsd.strstat")]]
void strmode($mode_t mode, [[nonnull]] char p[12]) {
	char ch;
	/* First character: File type */
	ch = '?';
#ifdef S_IFMT
	switch (mode & S_IFMT) {
#ifdef S_IFDIR
	case S_IFDIR:  ch = 'd'; break;
#endif /* S_IFDIR */
#ifdef S_IFCHR
	case S_IFCHR:  ch = 'c'; break;
#endif /* S_IFCHR */
#ifdef S_IFBLK
	case S_IFBLK:  ch = 'b'; break;
#endif /* S_IFBLK */
#ifdef S_IFREG
	case S_IFREG:  ch = '-'; break;
#endif /* S_IFREG */
#ifdef S_IFLNK
	case S_IFLNK:  ch = 'l'; break;
#endif /* S_IFLNK */
#ifdef S_IFSOCK
	case S_IFSOCK: ch = 's'; break;
#endif /* S_IFSOCK */
#ifdef S_IFIFO
	case S_IFIFO:  ch = 'p'; break; /* p=pipe */
#endif /* S_IFIFO */
	default: break;
	}
#endif /* S_IFMT */
	*p++ = ch;

#ifdef S_IRUSR
	*p++ = mode & S_IRUSR ? 'r' : '-';
#else /* S_IRUSR */
	*p++ = '-';
#endif /* !S_IRUSR */

#ifdef S_IWUSR
	*p++ = mode & S_IWUSR ? 'w' : '-';
#else /* S_IWUSR */
	*p++ = '-';
#endif /* !S_IWUSR */

#if defined(S_IXUSR) && defined(S_ISUID)
	switch (mode & (S_IXUSR | S_ISUID)) {
	case 0:                 ch = '-'; break;
	case S_IXUSR:           ch = 'x'; break;
	case S_ISUID:           ch = 'S'; break;
	case S_IXUSR | S_ISUID: ch = 's'; break;
	default: __builtin_unreachable();
	}
#elif defined(S_IXUSR)
	ch = mode & S_IXUSR ? 'x' : '-';
#elif defined(S_ISUID)
	ch = mode & S_ISUID ? 'S' : '-';
#else /* S_IWUSR */
	ch = '-';
#endif /* !S_IWUSR */
	*p++ = ch;

#ifdef S_IRGRP
	*p++ = mode & S_IRGRP ? 'r' : '-';
#else /* S_IRGRP */
	*p++ = '-';
#endif /* !S_IRGRP */

#ifdef S_IWGRP
	*p++ = mode & S_IWGRP ? 'w' : '-';
#else /* S_IWGRP */
	*p++ = '-';
#endif /* !S_IWGRP */

#if defined(S_IXGRP) && defined(S_ISGID)
	switch (mode & (S_IXGRP | S_ISGID)) {
	case 0:                 ch = '-'; break;
	case S_IXGRP:           ch = 'x'; break;
	case S_ISGID:           ch = 'S'; break;
	case S_IXGRP | S_ISGID: ch = 's'; break;
	default: __builtin_unreachable();
	}
#elif defined(S_IXGRP)
	ch = mode & S_IXGRP ? 'x' : '-';
#elif defined(S_ISGID)
	ch = mode & S_ISGID ? 'S' : '-';
#else /* S_IWUSR */
	ch = '-';
#endif /* !S_IWUSR */
	*p++ = ch;

#ifdef S_IROTH
	*p++ = mode & S_IROTH ? 'r' : '-';
#else /* S_IROTH */
	*p++ = '-';
#endif /* !S_IROTH */

#ifdef S_IWOTH
	*p++ = mode & S_IWOTH ? 'w' : '-';
#else /* S_IWOTH */
	*p++ = '-';
#endif /* !S_IWOTH */

#if defined(S_IXOTH) && defined(S_ISVTX)
	switch (mode & (S_IXOTH | S_ISVTX)) {
	case 0:                 ch = '-'; break;
	case S_IXOTH:           ch = 'x'; break;
	case S_ISVTX:           ch = 'T'; break;
	case S_IXOTH | S_ISVTX: ch = 't'; break;
	default: __builtin_unreachable();
	}
#elif defined(S_IXOTH)
	ch = mode & S_IXOTH ? 'x' : '-';
#elif defined(S_ISVTX)
	ch = mode & S_ISVTX ? 'T' : '-';
#else /* S_IWUSR */
	ch = '-';
#endif /* !S_IWUSR */
	*p++ = ch;

	/* Always space in this implementation */
	*p++ = ' ';

	/* NUL-terminate */
	*p = '\0';
}

%#endif /* __USE_BSD */

%(libc_fast){
#define __libc_PRIVATE_memset1 __libc_memset
#define __libc_PRIVATE_memset2 __libc_memsetw
#define __libc_PRIVATE_memset4 __libc_memsetl
#define __libc_PRIVATE_memset8 __libc_memsetq
#define __libc_PRIVATE_memset(dst, word, elem_count, elem_size) \
	__libc_PRIVATE_memset##elem_size(dst, word, elem_count)
#define __libc_memsetc(dst, word, elem_count, elem_size) \
	__libc_PRIVATE_memset(dst, word, elem_count, elem_size)
}


%{

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

}

