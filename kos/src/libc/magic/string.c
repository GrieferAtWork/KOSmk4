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

%[define_ccompat_header(cstring)]

%[define_replacement(locale_t = __locale_t)]
%[define_replacement(rsize_t  = __SIZE_TYPE__)]
%[default_impl_section(.text.crt.string.memory)]


%{
#include <features.h>
#include <bits/types.h>
#include <hybrid/typecore.h>
#ifdef __USE_KOS
#include <parts/malloca.h>
#endif /* __USE_KOS */
#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 || __USE_DOS */
#ifdef __USE_DOS
#include <parts/errno.h>
#include <crtdefs.h>
#endif /* __USE_DOS */

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


@@Copy memory between non-overlapping memory blocks.
@@@return: * : Always re-returns `dst'
[nobuiltin][fast][libc][kernel][std][ATTR_LEAF]
memcpy:([nonnull] void *__restrict dst,
        [nonnull] void const *__restrict src,
        size_t n_bytes) -> [== dst] void * {
	byte_t *pdst = (byte_t *)dst;
	byte_t *psrc = (byte_t *)src;
	while (n_bytes--)
		*pdst++ = *psrc++;
	return dst;
}

@@Move memory between potentially overlapping memory blocks.
@@@return: * : Always re-returns `dst'
[fast][libc][kernel][std][nobuiltin][ATTR_LEAF]
memmove:([nonnull] void *dst, [nonnull] void const *src, size_t n_bytes) -> [== dst] void * {
	byte_t *pdst, *psrc;
	if (dst < src) {
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
[fast][libc][kernel][std][nobuiltin][ATTR_LEAF]
memset:([nonnull] void *__restrict dst, int byte, size_t n_bytes) -> [== dst] void * {
	byte_t *pdst = (byte_t *)dst;
	while (n_bytes--)
		*pdst++ = (byte_t)byte;
	return dst;
}

@@Compare memory buffers and return the difference of the first non-matching byte
@@@return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
@@@return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
@@@return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes'
[fast][libc][kernel][alias(bcmp)][std][ATTR_WUNUSED][ATTR_PURE][nobuiltin]
memcmp:([nonnull] void const *s1, [nonnull] void const *s2, size_t n_bytes) -> int {
	byte_t *p1 = (byte_t *)s1;
	byte_t *p2 = (byte_t *)s2;
	byte_t v1, v2;
	v1 = v2 = 0;
	while (n_bytes-- && ((v1 = *p1++) == (v2 = *p2++)));
	return (int)v1 - (int)v2;
}

@@Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found.
[fast][libc][kernel][std][ATTR_WUNUSED][ATTR_PURE][nobuiltin]
memchr:([nonnull] void const *__restrict haystack, int needle, size_t n_bytes) -> void *
	[([nonnull] void *__restrict haystack, int needle, size_t n_bytes) -> void *]
	[([nonnull] void const *__restrict haystack, int needle, size_t n_bytes) -> void const *]
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
%(libc_fast)#define __libc_strlen(string) (__builtin_constant_p(string) ? __builtin_strlen(string) : __libc_slow_strlen(string))
%(libc_fast)#else /* __LIBC_BIND_OPTIMIZATIONS && !__NO_builtin_constant_p && __builtin_strlen && __CRT_HAVE_strlen */
@@Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')')
[libc][kernel][std][ATTR_WUNUSED][ATTR_PURE][nobuiltin]
strlen:([nonnull] char const *__restrict string) -> size_t {
	return (size_t)(strend(string) - string);
}
%(libc_fast)#endif /* !__LIBC_BIND_OPTIMIZATIONS || __NO_builtin_constant_p || !__builtin_strlen || !__CRT_HAVE_strlen */

@@Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found.
[libc][kernel][std][ATTR_WUNUSED][ATTR_PURE][crtbuiltin]
strchr:([nonnull] char const *__restrict haystack, int needle) -> char *
	[([nonnull] char *__restrict haystack, int needle) -> char *]
	[([nonnull] char const *__restrict haystack, int needle) -> char const *]
{
	for (; *haystack; ++haystack)
		if (*haystack == (char)needle)
			return (char *)haystack;
	return NULL;
}

@@Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found.
[std][ATTR_WUNUSED][ATTR_PURE][crtbuiltin]
strrchr:([nonnull] char const *__restrict haystack, int needle) -> char *
	[([nonnull] char *__restrict haystack, int needle) -> char *]
	[([nonnull] char const *__restrict haystack, int needle) -> char const *]
{
	char const *result = NULL;
	for (; *haystack; ++haystack)
		if (*haystack == (char)needle)
			result = haystack;
	return (char *)result;
}

@@Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical
[libc][kernel][std][ATTR_WUNUSED][ATTR_PURE][crtbuiltin]
strcmp:([nonnull] char const *s1, [nonnull] char const *s2) -> int {
	char c1, c2;
	do {
		if unlikely((c1 = *s1++) != (c2 = *s2++))
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}

@@Same as `strcmp', but compare at most `MAXLEN' characters from either string
[std][ATTR_WUNUSED][ATTR_PURE][crtbuiltin]
strncmp:([nonnull] char const *s1, [nonnull] char const *s2, size_t maxlen) -> int {
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
[std][ATTR_WUNUSED][ATTR_PURE][crtbuiltin]
strstr:([nonnull] char const *haystack, [nonnull] char const *needle) -> char *
	[([nonnull] char *haystack, [nonnull] char *needle) -> char *]
	[([nonnull] char const *haystack, [nonnull] char const *needle) -> char const *]
{
	char const *hay2, *ned_iter;
	char ch, needle_start = *needle++;
	while ((ch = *haystack++) != '\0') {
		if (ch == needle_start) {
			hay2 = haystack;
			ned_iter = needle;
			while ((ch = *ned_iter++) != '\0') {
				if (*hay2++ != ch)
					goto miss;
			}
			return (char *)haystack-1;
		}
miss:
		;
	}
	return NULL;
}


[std][crtbuiltin][ATTR_LEAF]
strcpy:([nonnull] char *__restrict buf, [nonnull] char const *__restrict src) -> [== buf] char * {
	return (char *)memcpy(buf, src, (strlen(src) + 1) * sizeof(char));
}

[std][crtbuiltin][ATTR_LEAF]
strncpy:([nonnull] char *__restrict buf, [nonnull] char const *__restrict src, size_t buflen) -> [== buf] char * {
	size_t srclen = strnlen(src, buflen);
	memcpy(buf, src, srclen * sizeof(char));
	memset(buf + srclen, '\0', (buflen - srclen) * sizeof(char));
	return buf;
}

[std][crtbuiltin][ATTR_LEAF]
strcat:([nonnull] char *__restrict buf, [nonnull] char const *__restrict src) -> [== buf] char * {
	memcpy(strend(buf), src, (strlen(src) + 1) * sizeof(char));
	return buf;
}

[std][crtbuiltin][ATTR_LEAF]
strncat:([nonnull] char *__restrict buf, [nonnull] char const *__restrict src, size_t buflen) -> [== buf] char * {
	size_t srclen = strnlen(src, buflen);
	char *dst = strend(buf);
	memcpy(dst, src, srclen * sizeof(char));
	dst[srclen] = '\0';
	return buf;
}

[std][ATTR_WUNUSED][ATTR_PURE][crtbuiltin]
strcspn:([nonnull] char const *haystack, [nonnull] char const *reject) -> size_t {
	char const *iter = haystack;
	while (*iter && !strchr(reject, *iter))
		++iter;
	return (size_t)(iter - haystack);
}

[std][ATTR_WUNUSED][ATTR_PURE][crtbuiltin]
strspn:([nonnull] char const *haystack, [nonnull] char const *accept) -> size_t {
	char const *iter = haystack;
	while (strchr(accept, *iter))
		++iter;
	return (size_t)(iter - haystack);
}

[std][ATTR_WUNUSED][ATTR_PURE][crtbuiltin]
strpbrk:([nonnull] char const *haystack, [nonnull] char const *accept) -> char *
	[([nonnull] char *haystack, [nonnull] char const *accept) -> char *]
	[([nonnull] char const *haystack, [nonnull] char const *accept) -> char const *]
{
	char const *ned_iter;
	char haych, ch;
	while ((haych = *haystack++) != '\0') {
		ned_iter = accept;
		while ((ch = *ned_iter++) != '\0') {
			if (haych == ch)
				return (char *)haystack - 1;
		}
	}
	return NULL;
}


[impl_prefix(
@__LOCAL_LIBC_DATA@(save_ptr) char *save_ptr = NULL;
)][std]
strtok:(char *string, [nonnull] char const *delim) -> char * {
	return strtok_r(string, delim, &save_ptr);
}

[std][ATTR_WUNUSED][ATTR_PURE]
[section(.text.crt.unicode.static.memory)]
strcoll:([nonnull] char const *s1, [nonnull] char const *s2) -> int {
	return strcmp(s1, s2);
}

[std][section(.text.crt.unicode.static.memory)]
strxfrm:(char *dst, [nonnull] char const *__restrict src, size_t maxlen) -> size_t {
	/* XXX: Implement me */
	size_t n = strnlen(src, maxlen);
	memcpy(dst, src, n * sizeof(char));
	return n;
}

[std][ATTR_WUNUSED][impl_prefix(
@__LOCAL_LIBC_DATA@(strerror_buf) char strerror_buf[64] = { 0 };
)][section(.text.crt.errno)][noexport][user]
strerror:(int errnum) -> [nonnull] char * {
	char *result = strerror_buf;
	char const *string;
	string = strerror_s(errnum);
	if (string) {
		/* Copy the descriptor text. */
		result[__COMPILER_LENOF(strerror_buf) - 1] = '\0';
		strncpy(result, string, __COMPILER_LENOF(strerror_buf) - 1);
	} else {
		sprintf(result, "Unknown error %d", errnum);
	}
	return result;
}


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
[libc][kernel][ATTR_WUNUSED][ATTR_PURE][crtbuiltin]
strnlen:([nonnull] char const *__restrict string, $size_t maxlen) -> $size_t {
	return (size_t)(strnend(string, maxlen) - string);
}
%#endif /* __USE_XOPEN2K8 || __USE_DOS */

%#ifdef __USE_XOPEN2K8

@@Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´
[crtbuiltin][alias(__stpcpy)]
stpcpy:([nonnull] char *__restrict buf,
        [nonnull] char const *__restrict src)
	-> [== buf + strlen(src)] char *
{
	return (char *)mempcpy(buf, src, (strlen(src) + 1) * sizeof(char)) - 1;
}

[crtbuiltin][alias(__stpncpy)]
stpncpy:([nonnull] char *__restrict buf,
         [nonnull] char const *__restrict src,
         $size_t buflen)
	-> [== buf + strnlen(src, buflen)] char *
{
	size_t srclen = strnlen(src, buflen);
	memcpy(buf, src, srclen * sizeof(char));
	memset(buf + srclen, '\0', (size_t)(buflen - srclen) * sizeof(char));
	return buf + srclen;
}

[alias(*)][attribute(*)] __stpcpy:(*) = stpcpy;
[alias(*)][attribute(*)] __stpncpy:(*) = stpncpy;

[alias(_strcoll_l)][ATTR_WUNUSED][ATTR_PURE]
[section(.text.crt.unicode.locale.memory)][export_alias(__strcoll_l)]
strcoll_l:([nonnull] char const *s1, [nonnull] char const *s2, $locale_t locale) -> int {
	(void)locale;
	return strcoll(s1, s2);
}

[alias(_strxfrm_l)][requires($has_function(strxfrm))]
[section(.text.crt.unicode.locale.memory)][export_alias(__strxfrm_l)]
strxfrm_l:(char *dst, [nonnull] char const *__restrict src,
           $size_t maxlen, $locale_t locale) -> $size_t {
	(void)locale;
	return strxfrm(dst, src, maxlen);
}

[requires($has_function(strerror))][noexport][user]
[ATTR_WUNUSED][section(.text.crt.errno)][same_impl]
strerror_l:(int errnum, $locale_t locale) -> char * {
	(void)locale;
	return strerror(errnum);
}
[ATTR_WUNUSED] strsignal:(int signo) -> char *;

[requires($has_function(malloc))]
[section(.text.crt.heap.strdup)][crtbuiltin][export_alias(__strndup)]
strndup:([nonnull] char const *__restrict string, $size_t max_chars)
	-> [malloc((strnlen(string, max_chars) + 1) * sizeof(char))] char *
%{auto_block(any({
	size_t resultlen = strnlen(string, max_chars);
	char *result = (char *)malloc((resultlen + 1) * sizeof(char));
	if likely(result)
@@if $wchar_function@@
		*wmempcpy(result, string, resultlen) = '\0';
@@else@@
		*(char *)mempcpy(result, string, resultlen * sizeof(char)) = '\0';
@@endif@@
	return result;
}))}


%{
#endif /* __USE_XOPEN2K8 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8) || defined(__USE_DOS)
}
[requires($has_function(malloc))][alias(_strdup)]
[section(.text.crt.heap.strdup)][same_impl][crtbuiltin][export_alias(__strdup)]
strdup:([nonnull] char const *__restrict string)
	-> [malloc((strlen(string) + 1) * sizeof(char))] char *
%{auto_block(any({
	size_t resultsize = (strlen(string) + 1) * sizeof(char);
	char *result = (char *)malloc(resultsize);
	if likely(result)
		memcpy(result, string, resultsize);
	return result;
}))}
%{
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 || __USE_DOS */

#ifdef __USE_POSIX
}

[ATTR_LEAF][alias(strtok_s, __strtok_r)]
strtok_r:(char *string,
          [nonnull] char const *delim,
          [nonnull] char **__restrict save_ptr) -> char * {
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

@@Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found.
[libc][kernel][ATTR_WUNUSED][ATTR_PURE]
memrchr:([nonnull] void const *__restrict haystack, int needle, $size_t n_bytes) -> void *
	[([nonnull] void *__restrict haystack, int needle, $size_t n_bytes) -> void *]
	[([nonnull] void const *__restrict haystack, int needle, $size_t n_bytes) -> void const *]
{
	byte_t *iter = (byte_t *)haystack + n_bytes;
	while (n_bytes--) {
		if (*--iter == (byte_t)needle)
			return iter;
	}
	return NULL;
}


@@Same as `memchr' with a search limit of `(size_t)-1'
[kernel][ATTR_WUNUSED][ATTR_PURE][export_alias(__rawmemchr)]
rawmemchr:([nonnull] void const *__restrict haystack, int needle) -> [nonnull] void *
	[([nonnull] void *__restrict haystack, int needle) -> [nonnull] void *]
	[([nonnull] void const *__restrict haystack, int needle) -> [nonnull] void const *]
{
	byte_t *iter = (byte_t *)haystack;
	for (;; ++iter) {
		if (*iter == (byte_t)needle)
			break;
	}
	return iter;
}

@@Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found.
[ATTR_WUNUSED][ATTR_PURE]
strchrnul:([nonnull] char const *__restrict haystack, int needle) -> [nonnull] char *
	[([nonnull] char *__restrict haystack, int needle) -> [nonnull] char *]
	[([nonnull] char const *__restrict haystack, int needle) -> [nonnull] char const *]
{
	for (; *haystack; ++haystack)
		if (*haystack == (char)needle)
			break;
	return (char *)haystack;
}

[guard][ATTR_WUNUSED][ATTR_PURE]
basename:([nullable] char const *filename) -> char *
	[([nullable] char *filename) -> char *]
	[([nullable] char const *filename) -> char const *]
{
	char ch, *iter = (char *)filename, *result = NULL;
	if (!filename || !*filename)
		return (char *)filename;
	do {
		ch = *iter++;
#ifdef _WIN32
		if (ch == '/' || ch == '\\')
			result = iter;
#else /* _WIN32 */
		if (ch == '/')
			result = iter;
#endif /* !_WIN32 */
	} while (ch);
	if unlikely(!result)
		return (char *)filename; /* Path doesn't contain '/'. */
	if (*result)
		return result; /* Last character isn't a '/'. */
	iter = result;
#ifdef _WIN32
	while (iter != filename && (iter[-1] == '/' || iter[-1] == '\\'))
		--iter;
#else /* _WIN32 */
	while (iter != filename && iter[-1] == '/')
		--iter;
#endif /* !_WIN32 */
	if (iter == filename)
		return result-1; /* Only `'/'"-characters. */
	//*iter = '\0'; /* Trim all ending `'/'"-characters. */
#ifdef _WIN32
	while (iter != filename && (iter[-1] != '/' || iter[-1] != '\\'))
		--iter; /* Scan until the previous '/'. */
#else /* _WIN32 */
	while (iter != filename && iter[-1] != '/')
		--iter; /* Scan until the previous '/'. */
#endif /* !_WIN32 */
	return iter; /* Returns string after previous '/'. */
}


@@Same as `strstr', but ignore casing
[ATTR_WUNUSED][section(.text.crt.unicode.static.memory)][export_alias(__strcasestr)]
strcasestr:([nonnull] char const *haystack, [nonnull] char const *needle) -> char *
	[([nonnull] char *haystack, [nonnull] char const *needle) -> char *]
	[([nonnull] char const *haystack, [nonnull] char const *needle) -> char const *]
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
[libc][ATTR_WUNUSED][ATTR_PURE][impl_include(<features.h>)]
[if(defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), preferred_alias(memmem0)]
[if(!defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), preferred_alias(memmem)]
memmem:([nonnull] void const *haystack, $size_t haystacklen, [nonnull] void const *needle, $size_t needlelen) -> void *
	[([nonnull] void *haystack, $size_t haystacklen, [nonnull] void const *needle, $size_t needlelen) -> void *]
	[([nonnull] void const *haystack, $size_t haystacklen, [nonnull] void const *needle, $size_t needlelen) -> void const *]
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

[ATTR_WUNUSED][ATTR_PURE][export_alias(__strverscmp)]
strverscmp:([nonnull] char const *s1, [nonnull] char const *s2) -> int {
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


[alias(*)][attribute(*)] __mempcpy:(*) = mempcpy;

@@Same as `memcpy', but return `DST+N_BYTES', rather than `DST'
[libc][kernel][fast][nobuiltin][export_alias(__mempcpy)][ATTR_LEAF]
mempcpy:([nonnull] void *__restrict dst,
         [nonnull] void const *__restrict src,
         $size_t n_bytes) -> [== dst + n_bytes] void * {
	byte_t *pdst = (byte_t *)dst;
	byte_t *psrc = (byte_t *)src;
	while (n_bytes--)
		*pdst++ = *psrc++;
	return pdst;
}

[ATTR_LEAF]
strfry:([nonnull] char *__restrict string) -> [== string] char * {
	char temp;
	size_t i, count = strlen(string);
	for (i = 0; i < count; ++i) {
		size_t j = rand();
		j = i + (j % (count - i));
		/* Swap these 2 characters. */
		temp = string[i];
		string[i] = string[j];
		string[j] = temp;
	}
	return string;
}

[ATTR_LEAF]
memfrob:([nonnull] void *buf, $size_t num_bytes) -> [== buf] void * {
	byte_t *iter = (byte_t *)buf;
	while (num_bytes--)
		*iter++ ^= 42; /* -_-   yeah... */
	return buf;
}

[guard][alias(_stricmp_l)][ATTR_WUNUSED]
[section(.text.crt.unicode.locale.memory)][export_alias(__strcasecmp_l)]
strcasecmp_l:([nonnull] char const *s1, [nonnull] char const *s2, $locale_t locale) -> int {
	(void)locale;
	return strcasecmp(s1, s2);
}

[guard][alias(_strnicmp_l, _strncmpi_l)][ATTR_WUNUSED]
[section(.text.crt.unicode.locale.memory)][export_alias(__strncasecmp_l)]
strncasecmp_l:([nonnull] char const *s1, [nonnull] char const *s2, $size_t maxlen, $locale_t locale) -> int {
	(void)locale;
	return strncasecmp(s1, s2, maxlen);
}

%#endif /* __USE_GNU */
%
%#ifdef __USE_XOPEN2K
%#ifdef __USE_GNU
[section(.text.crt.errno)][export_alias(__strerror_r)]
strerror_r:(int errnum, [nonnull] char *buf, $size_t buflen) -> [nonnull] char *;
%#else /* __USE_GNU */
[section(.text.crt.errno)]
strerror_r:(int errnum, [nonnull] char *buf, $size_t buflen) -> $errno_t = __xpg_strerror_r?;
%#endif /* !__USE_GNU */
%#endif /* __USE_XOPEN2K */
%
%#ifdef __USE_MISC

[ATTR_LEAF]
strsep:([nonnull] char **__restrict stringp,
        [nonnull] char const *__restrict delim) -> char * {
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
%[insert:extern(bcmp)]
%[insert:extern(index)]
%[insert:extern(rindex)]

[guard][alias(_stricmp, _strcmpi, stricmp, strcmpi)][export_alias(__strcasecmp)]
[ATTR_WUNUSED][section(.text.crt.unicode.static.memory)][crtbuiltin]
strcasecmp:([nonnull] char const *s1, [nonnull] char const *s2) -> int {
	char c1, c2;
	do {
		if ((c1 = *s1++) != (c2 = *s2++) && ((c1 = tolower(c1)) != (c2 = tolower(c2))))
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}
[guard][alias(_strnicmp, strnicmp, _strncmpi, strncmpi)]
[ATTR_WUNUSED][section(.text.crt.unicode.static.memory)][crtbuiltin]
strncasecmp:([nonnull] char const *s1, [nonnull] char const *s2, $size_t maxlen) -> int {
	char c1, c2;
	do {
		if (!maxlen--)
			break;
		if ((c1 = *s1++) != (c2 = *s2++) && ((c1 = tolower(c1)) != (c2 = tolower(c2))))
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}


[ATTR_WUNUSED][ATTR_CONST][nothrow]
[dependency_prefix(
#include <hybrid/__bit.h>
)][crtbuiltin][export_alias(__ffs)]
ffs:(int i) -> __STDC_INT_AS_SIZE_T {
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
[ATTR_WUNUSED][ATTR_CONST][nothrow]
[dependency_prefix(
#include <hybrid/__bit.h>
)][crtbuiltin]
ffsl:(long i) -> __STDC_INT_AS_SIZE_T {
	return (__STDC_INT_AS_SIZE_T)__hybrid_ffs((unsigned long)i);
}

[ATTR_WUNUSED][ATTR_CONST][nothrow]
[dependency_prefix(
#include <hybrid/__bit.h>
)][crtbuiltin]
ffsll:(__LONGLONG i) -> __STDC_INT_AS_SIZE_T {
	return (__STDC_INT_AS_SIZE_T)__hybrid_ffs((__ULONGLONG)i);
}
%#endif /* __USE_GNU */

[ATTR_LEAF]
strlcat:([nonnull] char *__restrict dst,
         [nonnull] char const *__restrict src,
         $size_t bufsize) -> $size_t {
	size_t result = strlen(src);
	char *new_dst = dst + strnlen(dst, bufsize);
	size_t copy_size;
	bufsize -= (new_dst - dst);
	copy_size = result < bufsize ? result : bufsize - 1;
	memcpy(new_dst, src, copy_size*sizeof(char));
	new_dst[copy_size] = '\0';
	return result + (new_dst - dst);
}

[ATTR_LEAF]
strlcpy:([nonnull] char *__restrict dst,
         [nonnull] char const *__restrict src,
         $size_t bufsize) -> $size_t {
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

[alias(_memccpy)][ATTR_LEAF]
memccpy:([nonnull] void *__restrict dst,
         [nonnull] void const *__restrict src,
         int needle, $size_t num_bytes) -> void * {
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

[attribute(*)][alias(*)] __bzero:(*) = bzero;
[attribute(*)][alias(*)] __strtok_r:(*) = strtok_r;

/* TODO: strdupa */
/* TODO: strndupa */
/* TODO: mstrdupa */
/* TODO: mstrndupa */

%{

#ifdef __USE_STRING_BWLQ
}

@@Copy memory between non-overlapping memory blocks.
[noexport][ATTR_LEAF]
memcpyb:([nonnull] void *__restrict dst,
         [nonnull] void const *__restrict src,
         $size_t n_bytes) -> [== dst] $uint8_t * = memcpy;

@@Same as `memcpyb', but return `DST+N_BYTES', rather than `DST'
[noexport][ATTR_LEAF]
mempcpyb:([nonnull] void *__restrict dst,
          [nonnull] void const *__restrict src,
          $size_t n_bytes) -> [== dst + n_bytes] $uint8_t * = mempcpy;

@@Copy memory between non-overlapping memory blocks.
[fast][libc][kernel][if(__SIZEOF_WCHAR_T__ == 2), alias(wmemcpy)][ATTR_LEAF]
memcpyw:([nonnull] void *__restrict dst,
         [nonnull] void const *__restrict src,
         $size_t n_words) -> [== dst] $uint16_t * {
	u16 *pdst = (u16 *)dst;
	u16 *psrc = (u16 *)src;
	while (n_words--)
		*pdst++ = *psrc++;
	return (u16 *)dst;
}

@@Same as `memcpyw', but return `DST+N_WORDS', rather than `DST'
[fast][libc][kernel][if(__SIZEOF_WCHAR_T__ == 2), alias(wmempcpy)][ATTR_LEAF]
mempcpyw:([nonnull] void *__restrict dst,
          [nonnull] void const *__restrict src,
          $size_t n_words) -> [== dst + n_words * 2] $uint16_t * {
	return (u16 *)memcpyw(dst, src, n_words) + n_words;
}

@@Copy memory between non-overlapping memory blocks.
[fast][libc][kernel][if(__SIZEOF_WCHAR_T__ == 4), alias(wmemcpy)][ATTR_LEAF]
memcpyl:([nonnull] void *__restrict dst,
         [nonnull] void const *__restrict src,
         $size_t n_dwords) -> [== dst] $uint32_t * {
	u32 *pdst = (u32 *)dst;
	u32 *psrc = (u32 *)src;
	while (n_dwords--)
		*pdst++ = *psrc++;
	return (u32 *)dst;
}

@@Same as `memcpyl', but return `DST+N_DWORDS', rather than `DST'
[fast][libc][kernel][if(__SIZEOF_WCHAR_T__ == 4), alias(wmempcpy)][ATTR_LEAF]
mempcpyl:([nonnull] void *__restrict dst,
          [nonnull] void const *__restrict src,
          $size_t n_dwords) -> [== dst + n_dwords * 4] $uint32_t * {
	return (u32 *)memcpyl(dst, src, n_dwords) + n_dwords;
}


@@Move memory between potentially overlapping memory blocks.
[noexport][ATTR_LEAF]
memmoveb:([nonnull] void *dst,
          [nonnull] void const *src,
          $size_t n_bytes) -> [== dst] $uint8_t * = memmove;

@@Same as `memmoveb', but return `DST+N_BYTES', rather than `DST'
[noexport][ATTR_LEAF]
mempmoveb:([nonnull] void *dst,
           [nonnull] void const *src,
           $size_t n_bytes) -> [== dst + n_bytes] $uint8_t * = mempmove;

@@Move memory between potentially overlapping memory blocks.
[fast][libc][kernel][if(__SIZEOF_WCHAR_T__ == 2), alias(wmemmove)][ATTR_LEAF]
memmovew:([nonnull] void *dst,
          [nonnull] void const *src,
          $size_t n_words) -> [== dst] $uint16_t * {
	u16 *pdst, *psrc;
	if (dst < src) {
		psrc = (u16 *)src;
		pdst = (u16 *)dst;
		while (n_words--)
			*pdst++ = *psrc++;
	} else {
		psrc = (u16 *)src + n_words;
		pdst = (u16 *)dst + n_words;
		while (n_words--)
			*--pdst = *--psrc;
	}
	return (u16 *)dst;
}

@@Same as `memmovew', but return `DST+N_WORDS', rather than `DST'
[fast][libc][kernel][ATTR_LEAF]
mempmovew:([nonnull] void *__restrict dst,
           [nonnull] void const *__restrict src,
           $size_t n_words) -> [== dst + n_words * 2] $uint16_t * {
	return (u16 *)memmovew(dst, src, n_words) + n_words;
}

@@Move memory between potentially overlapping memory blocks.
[fast][libc][kernel][if(__SIZEOF_WCHAR_T__ == 4), alias(wmemmove)][ATTR_LEAF]
memmovel:([nonnull] void *dst,
          [nonnull] void const *src,
          $size_t n_dwords) -> [== dst] $uint32_t * {
	u32 *pdst, *psrc;
	if (dst < src) {
		psrc = (u32 *)src;
		pdst = (u32 *)dst;
		while (n_dwords--)
			*pdst++ = *psrc++;
	} else {
		psrc = (u32 *)src + n_dwords;
		pdst = (u32 *)dst + n_dwords;
		while (n_dwords--)
			*--pdst = *--psrc;
	}
	return (u32 *)dst;
}

@@Same as `memmovew', but return `DST+N_DWORDS', rather than `DST'
[fast][libc][kernel][ATTR_LEAF]
mempmovel:([nonnull] void *__restrict dst,
           [nonnull] void const *__restrict src,
           $size_t n_dwords) -> [== dst + n_dwords * 4] $uint32_t * {
	return (u32 *)memmovel(dst, src, n_dwords) + n_dwords;
}

@@Fill memory with a given byte
[noexport][ATTR_LEAF]
memsetb:([nonnull] void *__restrict dst,
         int byte, $size_t n_bytes) -> [== dst] $uint8_t * = memset;

@@Same as `memsetb', but return `DST+N_BYTES', rather than `DST'
[noexport][ATTR_LEAF]
mempsetb:([nonnull] void *__restrict dst,
          int byte, $size_t n_bytes) -> [== dst + n_bytes] $uint8_t * = mempset;

@@Fill memory with a given word
[fast][libc][kernel][ATTR_LEAF]
memsetw:([nonnull] void *__restrict dst,
         $uint16_t word, $size_t n_words) -> [== dst] $uint16_t * {
	u16 *pdst = (u16 *)dst;
	while (n_words--)
		*pdst++ = word;
	return (u16 *)dst;
}

@@Same as `memsetw', but return `DST+N_WORDS', rather than `DST'
[fast][libc][kernel][ATTR_LEAF]
mempsetw:([nonnull] void *__restrict dst,
          $uint16_t word, $size_t n_words) -> [== dst + n_words * 2] $uint16_t * {
	return (u16 *)memsetw(dst, word, n_words) + n_words;
}

@@Fill memory with a given dword
[fast][libc][kernel][ATTR_LEAF]
memsetl:([nonnull] void *__restrict dst,
         $uint32_t dword, $size_t n_dwords) -> [== dst] $uint32_t * {
	u32 *pdst = (u32 *)dst;
	while (n_dwords--)
		*pdst++ = dword;
	return (u32 *)dst;
}

@@Same as `memsetl', but return `DST+N_DWORDS', rather than `DST'
[fast][libc][kernel][ATTR_LEAF]
mempsetl:([nonnull] void *__restrict dst,
          $uint32_t dword, $size_t n_dwords) -> [== dst + n_dwords * 4] $uint32_t * {
	return (u32 *)memsetl(dst, dword, n_dwords) + n_dwords;
}


@@Compare memory buffers and return the difference of the first non-matching byte
[noexport][alias(bcmp)][ATTR_WUNUSED][ATTR_PURE]
memcmpb:([nonnull] void const *s1,
         [nonnull] void const *s2, $size_t n_bytes) -> int = memcmp;

@@Compare memory buffers and return the difference of the first non-matching word
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
[if(__SIZEOF_WCHAR_T__ == 2), alias(wmemcmp)]
memcmpw:([nonnull] void const *s1,
         [nonnull] void const *s2, $size_t n_words) -> $int16_t {
	s16 *p1 = (s16 *)s1;
	s16 *p2 = (s16 *)s2;
	s16 v1, v2;
	v1 = v2 = 0;
	while (n_words-- && ((v1 = *p1++) == (v2 = *p2++)));
	return v1 - v2;
}

@@Compare memory buffers and return the difference of the first non-matching dword
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
[if(__SIZEOF_WCHAR_T__ == 4), alias(wmemcmp)]
memcmpl:([nonnull] void const *s1,
         [nonnull] void const *s2, $size_t n_dwords) -> $int32_t {
	s32 *p1 = (s32 *)s1;
	s32 *p2 = (s32 *)s2;
	s32 v1, v2;
	v1 = v2 = 0;
	while (n_dwords-- && ((v1 = *p1++) == (v2 = *p2++)));
	return v1 - v2;
}

@@Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found.
[noexport][ATTR_WUNUSED][ATTR_PURE]
memchrb:([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> $uint8_t *
	[([nonnull] void *__restrict haystack, int byte, $size_t n_bytes) -> $uint8_t *]
	[([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> $uint8_t const *]
	= memchr;

@@Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE][if(__SIZEOF_WCHAR_T__ == 2), alias(wmemchr)]
memchrw:([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_words) -> $uint16_t *
	[([nonnull] void *__restrict haystack, $uint16_t word, $size_t n_words) -> $uint16_t *]
	[([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_words) -> $uint16_t const *]
{
	u16 *hay_iter = (u16 *)haystack;
	for (; n_words--; ++hay_iter) {
		if unlikely(*hay_iter == word)
			return hay_iter;
	}
	return NULL;
}

@@Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE][if(__SIZEOF_WCHAR_T__ == 4), alias(wmemchr)]
memchrl:([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> $uint32_t *
	[([nonnull] void *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> $uint32_t *]
	[([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> $uint32_t const *]
{
	u32 *hay_iter = (u32 *)haystack;
	for (; n_dwords--; ++hay_iter) {
		if unlikely(*hay_iter == dword)
			return hay_iter;
	}
	return NULL;
}

@@Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found.
[noexport][ATTR_WUNUSED][ATTR_PURE]
memrchrb:([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> $uint8_t *
	[([nonnull] void *__restrict haystack, int byte, $size_t n_bytes) -> $uint8_t *]
	[([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> $uint8_t const *]
	= memrchr;

@@Descendingly search for `NEEDLE', starting at `HAYSTACK+N_WORDS'. - Return `NULL' if `NEEDLE' wasn't found.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
memrchrw:([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_words) -> $uint16_t *
	[([nonnull] void *__restrict haystack, $uint16_t word, $size_t n_words) -> $uint16_t *]
	[([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_words) -> $uint16_t const *]
{
	u16 *iter = (u16 *)haystack + n_words;
	while (n_words--) {
		if unlikely(*--iter == word)
			return iter;
	}
	return NULL;
}

@@Descendingly search for `NEEDLE', starting at `HAYSTACK+N_DWORDS'. - Return `NULL' if `NEEDLE' wasn't found.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
memrchrl:([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> $uint32_t *
	[([nonnull] void *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> $uint32_t *]
	[([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> $uint32_t const *]
{
	u32 *iter = (u32 *)haystack + n_dwords;
	while (n_dwords--) {
		if unlikely(*--iter == dword)
			return iter;
	}
	return NULL;
}

@@Same as `memchrb' with a search limit of `(size_t)-1'
[noexport][ATTR_WUNUSED][ATTR_PURE]
rawmemchrb:([nonnull] void const *__restrict haystack, int byte) -> [nonnull] $uint8_t *
	[([nonnull] void *__restrict haystack, int byte) -> [nonnull] $uint8_t *]
	[([nonnull] void const *__restrict haystack, int byte) -> [nonnull] $uint8_t const *]
	= rawmemchr;

@@Same as `memchrw' with a search limit of `(size_t)-1 / 2'
[kernel][ATTR_WUNUSED][ATTR_PURE]
rawmemchrw:([nonnull] void const *__restrict haystack, $uint16_t word) -> [nonnull] $uint16_t *
	[([nonnull] void *__restrict haystack, $uint16_t word) -> [nonnull] $uint16_t *]
	[([nonnull] void const *__restrict haystack, $uint16_t word) -> [nonnull] $uint16_t const *]
{
	u16 *iter = (u16 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter == word)
			break;
	}
	return iter;
}

@@Same as `memchrl' with a search limit of `(size_t)-1 / 4'
[kernel][ATTR_WUNUSED][ATTR_PURE]
rawmemchrl:([nonnull] void const *__restrict haystack, $uint32_t dword) -> [nonnull] $uint32_t *
	[([nonnull] void *__restrict haystack, $uint32_t dword) -> [nonnull] $uint32_t *]
	[([nonnull] void const *__restrict haystack, $uint32_t dword) -> [nonnull] $uint32_t const *]
{
	u32 *iter = (u32 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter == dword)
			break;
	}
	return iter;
}


@@Same as `memrchrb' without a search limit, starting at `HAYSTACK-1'
[noexport][ATTR_WUNUSED][ATTR_PURE]
rawmemrchrb:([nonnull] void const *__restrict haystack, int byte) -> [nonnull] $uint8_t *
	[([nonnull] void *__restrict haystack, int byte) -> [nonnull] $uint8_t *]
	[([nonnull] void const *__restrict haystack, int byte) -> [nonnull] $uint8_t const *]
	= rawmemrchr;

@@Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK-2'
[kernel][ATTR_WUNUSED][ATTR_PURE]
rawmemrchrw:([nonnull] void const *__restrict haystack, $uint16_t word) -> [nonnull] $uint16_t *
	[([nonnull] void *__restrict haystack, $uint16_t word) -> [nonnull] $uint16_t *]
	[([nonnull] void const *__restrict haystack, $uint16_t word) -> [nonnull] $uint16_t const *]
{
	u16 *iter = (u16 *)haystack;
	for (;;) {
		if unlikely(*--iter == word)
			break;
	}
	return iter;
}

@@Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK-4'
[kernel][ATTR_WUNUSED][ATTR_PURE]
rawmemrchrl:([nonnull] void const *__restrict haystack, $uint32_t dword) -> [nonnull] $uint32_t *
	[([nonnull] void *__restrict haystack, $uint32_t dword) -> [nonnull] $uint32_t *]
	[([nonnull] void const *__restrict haystack, $uint32_t dword) -> [nonnull] $uint32_t const *]
{
	u32 *iter = (u32 *)haystack;
	for (;;) {
		if unlikely(*--iter == dword)
			break;
	}
	return iter;
}


@@Same as `memchrb', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found.
[noexport][ATTR_WUNUSED][ATTR_PURE]
memendb:([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> [nonnull] $uint8_t *
	[([nonnull] void *__restrict haystack, int byte, $size_t n_bytes) -> [nonnull] $uint8_t *]
	[([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> [nonnull] $uint8_t const *]
	= memend;

@@Same as `memchrw', but return `HAYSTACK+N_WORDS', rather than `NULL' if `NEEDLE' wasn't found.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
memendw:([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_bytes) -> [nonnull] $uint16_t *
	[([nonnull] void *__restrict haystack, $uint16_t word, $size_t n_bytes) -> [nonnull] $uint16_t *]
	[([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_bytes) -> [nonnull] $uint16_t const *]
{
	u16 *result = (u16 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == word)
			break;
	}
	return result;
}

@@Same as `memchrl', but return `HAYSTACK+N_DWORDS', rather than `NULL' if `NEEDLE' wasn't found.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
memendl:([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_bytes) -> [nonnull] $uint32_t *
	[([nonnull] void *__restrict haystack, $uint32_t dword, $size_t n_bytes) -> [nonnull] $uint32_t *]
	[([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_bytes) -> [nonnull] $uint32_t const *]
{
	u32 *result = (u32 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == dword)
			break;
	}
	return result;
}

@@Same as `memrchrb', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found.
[noexport][ATTR_WUNUSED][ATTR_PURE]
memrendb:([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> [nonnull] $uint8_t *
	[([nonnull] void *__restrict haystack, int byte, $size_t n_bytes) -> [nonnull] $uint8_t *]
	[([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> [nonnull] $uint8_t const *]
	= memrend;

@@Same as `memrchrw', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
memrendw:([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_words) -> [nonnull] $uint16_t *
	[([nonnull] void *__restrict haystack, $uint16_t word, $size_t n_words) -> [nonnull] $uint16_t *]
	[([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_words) -> [nonnull] $uint16_t const *]
{
	u16 *result = (u16 *)haystack + n_words;
	while (n_words--) {
		if unlikely(*--result == word)
			break;
	}
	return result;
}

@@Same as `memrchrl', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
memrendl:([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> [nonnull] $uint32_t *
	[([nonnull] void *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> [nonnull] $uint32_t *]
	[([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> [nonnull] $uint32_t const *]
{
	u32 *result = (u32 *)haystack + n_dwords;
	while (n_dwords--) {
		if unlikely(*--result == dword)
			break;
	}
	return result;
}



@@Same as `memendb', but return the offset from `HAYSTACK', rather than the actual address.
[noexport][ATTR_WUNUSED][ATTR_PURE]
memlenb:([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> $size_t = memlen;

@@Same as `memendw', but return the offset from `HAYSTACK', rather than the actual address.
[kernel][ATTR_WUNUSED][ATTR_PURE]
memlenw:([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_words) -> $size_t {
	return (size_t)(memendw(haystack, word, n_words) - (u16 *)haystack);
}

@@Same as `memendl', but return the offset from `HAYSTACK', rather than the actual address.
[kernel][ATTR_WUNUSED][ATTR_PURE]
memlenl:([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> $size_t {
	return (size_t)(memendl(haystack, dword, n_dwords) - (u32 *)haystack);
}

@@Same as `memrendb', but return the offset from `HAYSTACK', rather than the actual address.
[noexport][ATTR_WUNUSED][ATTR_PURE]
memrlenb:([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> $size_t = memrlen;

@@Same as `memrendw', but return the offset from `HAYSTACK', rather than the actual address.
[kernel][ATTR_WUNUSED][ATTR_PURE]
memrlenw:([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_words) -> $size_t {
	return (size_t)(memrendw(haystack, word, n_words) - (u16 *)haystack);
}

@@Same as `memrendl', but return the offset from `HAYSTACK', rather than the actual address.
[kernel][ATTR_WUNUSED][ATTR_PURE]
memrlenl:([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> $size_t {
	return (size_t)(memrendl(haystack, dword, n_dwords) - (u32 *)haystack);
}



@@Same as `rawmemchrb', but return the offset from `HAYSTACK', rather than the actual address.
[noexport][ATTR_WUNUSED][ATTR_PURE]
rawmemlenb:([nonnull] void const *__restrict haystack, int needle) -> $size_t = rawmemlen;

@@Same as `rawmemchrw', but return the offset from `HAYSTACK', rather than the actual address.
[kernel][ATTR_WUNUSED][ATTR_PURE]
rawmemlenw:([nonnull] void const *__restrict haystack, $uint16_t word) -> $size_t {
	return (size_t)(rawmemchrw(haystack, word) - (u16 *)haystack);
}

@@Same as `rawmemchrl', but return the offset from `HAYSTACK', rather than the actual address.
[kernel][ATTR_WUNUSED][ATTR_PURE]
rawmemlenl:([nonnull] void const *__restrict haystack, $uint32_t dword) -> $size_t {
	return (size_t)(rawmemchrl(haystack, dword) - (u32 *)haystack);
}


@@Same as `rawmemrchrb', but return the offset from `HAYSTACK', rather than the actual address.
[noexport][ATTR_WUNUSED][ATTR_PURE]
rawmemrlenb:([nonnull] void const *__restrict haystack, int needle) -> $size_t = rawmemrlen;

@@Same as `rawmemrchrw', but return the offset from `HAYSTACK', rather than the actual address.
[kernel][ATTR_WUNUSED][ATTR_PURE]
rawmemrlenw:([nonnull] void const *__restrict haystack, $uint16_t word) -> $size_t {
	return (size_t)(rawmemrchrw(haystack, word) - (u16 *)haystack);
}

@@Same as `rawmemrchrl', but return the offset from `HAYSTACK', rather than the actual address.
[kernel][ATTR_WUNUSED][ATTR_PURE]
rawmemrlenl:([nonnull] void const *__restrict haystack, $uint32_t dword) -> $size_t {
	return (size_t)(rawmemrchrl(haystack, dword) - (u32 *)haystack);
}



%#ifdef __UINT64_TYPE__
@@Copy memory between non-overlapping memory blocks.
[fast][libc][kernel][ATTR_LEAF]
memcpyq:([nonnull] void *__restrict dst,
         [nonnull] void const *__restrict src,
         $size_t n_qwords) -> [== dst] $uint64_t * {
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

@@Same as `memcpyq', but return `DST+N_QWORDS', rather than `DST'
[fast][libc][kernel][ATTR_LEAF]
mempcpyq:([nonnull] void *__restrict dst,
          [nonnull] void const *__restrict src,
          $size_t n_qwords) -> [== dst + n_qwords * 8] $uint64_t * {
	return (u64 *)memcpyq(dst, src, n_qwords) + n_qwords;
}

@@Move memory between potentially overlapping memory blocks.
[fast][libc][kernel][ATTR_LEAF]
memmoveq:([nonnull] void *dst,
          [nonnull] void const *src,
          $size_t n_qwords) -> [== dst] $uint64_t * {
#if __SIZEOF_POINTER__ >= 8
	u64 *pdst, *psrc;
	if (dst < src) {
		psrc = (u64 *)src;
		pdst = (u64 *)dst;
		while (n_qwords--)
			*pdst++ = *psrc++;
	} else {
		psrc = (u64 *)src + n_qwords;
		pdst = (u64 *)dst + n_qwords;
		while (n_qwords--)
			*--pdst = *--psrc;
	}
#else /* __SIZEOF_POINTER__ >= 8 */
	u32 *pdst, *psrc;
	if (dst < src) {
		psrc = (u32 *)src;
		pdst = (u32 *)dst;
		while (n_qwords--) {
			*pdst++ = *psrc++;
			*pdst++ = *psrc++;
		}
	} else {
		psrc = (u32 *)src + (n_qwords * 2);
		pdst = (u32 *)dst + (n_qwords * 2);
		while (n_qwords--) {
			*--pdst = *--psrc;
			*--pdst = *--psrc;
		}
	}
#endif /* __SIZEOF_POINTER__ < 8 */
	return (u64 *)dst;
}

@@Same as `memmovew', but return `DST+N_QWORDS', rather than `DST'
[fast][libc][kernel][ATTR_LEAF]
mempmoveq:([nonnull] void *__restrict dst,
           [nonnull] void const *__restrict src,
           $size_t n_qwords) -> [== dst + n_qwords * 8] $uint64_t * {
	return (u64 *)memmoveq(dst, src, n_qwords) + n_qwords;
}

@@Fill memory with a given qword
[fast][libc][kernel][ATTR_LEAF]
memsetq:([nonnull] void *__restrict dst,
         $uint64_t qword, $size_t n_qwords) -> [== dst] $uint64_t * {
	u64 *pdst = (u64 *)dst;
	while (n_qwords--)
		*pdst++ = qword;
	return (u64 *)dst;
}

@@Same as `memsetq', but return `DST+N_QWORDS', rather than `DST'
[fast][libc][kernel][ATTR_LEAF]
mempsetq:([nonnull] void *__restrict dst,
          $uint64_t qword, $size_t n_qwords) -> [== dst + n_qwords * 8] $uint64_t * {
	return (u64 *)memsetq(dst, qword, n_qwords) + n_qwords;
}

@@Compare memory buffers and return the difference of the first non-matching qword
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
memcmpq:([nonnull] void const *s1,
         [nonnull] void const *s2, $size_t n_dwords) -> $int64_t {
	s64 *p1 = (s64 *)s1;
	s64 *p2 = (s64 *)s2;
	s64 v1, v2;
	v1 = v2 = 0;
	while (n_dwords-- && ((v1 = *p1++) == (v2 = *p2++)));
	return v1 - v2;
}

@@Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
memchrq:([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> $uint64_t *
	[([nonnull] void *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> $uint64_t *]
	[([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> $uint64_t const *]
{
	u64 *hay_iter = (u64 *)haystack;
	for (; n_qwords--; ++hay_iter) {
		if unlikely(*hay_iter == (u64)qword)
			return hay_iter;
	}
	return NULL;
}

@@Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
memrchrq:([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> $uint64_t *
	[([nonnull] void *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> $uint64_t *]
	[([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> $uint64_t const *]
{
	u64 *iter = (u64 *)haystack + n_qwords;
	while (n_qwords--) {
		if unlikely(*--iter == qword)
			return iter;
	}
	return NULL;
}

@@Same as `memchrq' with a search limit of `(size_t)-1 / 8'
[kernel][ATTR_WUNUSED][ATTR_PURE]
rawmemchrq:([nonnull] void const *__restrict haystack, $uint64_t qword) -> [nonnull] $uint64_t *
	[([nonnull] void *__restrict haystack, $uint64_t qword) -> [nonnull] $uint64_t *]
	[([nonnull] void const *__restrict haystack, $uint64_t qword) -> [nonnull] $uint64_t const *]
{
	u64 *iter = (u64 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter == qword)
			break;
	}
	return iter;
}

@@Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK-8'
[kernel][ATTR_WUNUSED][ATTR_PURE]
rawmemrchrq:([nonnull] void const *__restrict haystack, $uint64_t qword) -> [nonnull] $uint64_t *
	[([nonnull] void *__restrict haystack, $uint64_t qword) -> [nonnull] $uint64_t *]
	[([nonnull] void const *__restrict haystack, $uint64_t qword) -> [nonnull] $uint64_t const *]
{
	u64 *iter = (u64 *)haystack;
	for (;;) {
		if unlikely(*--iter == qword)
			break;
	}
	return iter;
}

@@Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
memendq:([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_bytes) -> [nonnull] $uint64_t *
	[([nonnull] void *__restrict haystack, $uint64_t qword, $size_t n_bytes) -> [nonnull] $uint64_t *]
	[([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_bytes) -> [nonnull] $uint64_t const *]
{
	u64 *result = (u64 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == qword)
			break;
	}
	return result;
}

@@Same as `memrchrq', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
memrendq:([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> [nonnull] $uint64_t *
	[([nonnull] void *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> [nonnull] $uint64_t *]
	[([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> [nonnull] $uint64_t const *]
{
	u64 *result = (u64 *)haystack + n_qwords;
	while (n_qwords--) {
		if unlikely(*--result == qword)
			break;
	}
	return result;
}

@@Same as `memendq', but return the offset from `HAYSTACK', rather than the actual address.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
memlenq:([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> $size_t {
	return (size_t)(memendq(haystack, qword, n_qwords) - (u64 *)haystack);
}

@@Same as `memrendq', but return the offset from `HAYSTACK', rather than the actual address.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
memrlenq:([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> $size_t {
	return (size_t)(memrendq(haystack, qword, n_qwords) - (u64 *)haystack);
}

@@Same as `rawmemchrq', but return the offset from `HAYSTACK', rather than the actual address.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
rawmemlenq:([nonnull] void const *__restrict haystack, $uint64_t qword) -> $size_t {
	return (size_t)(rawmemchrq(haystack, qword) - (u64 *)haystack);
}

@@Same as `rawmemrchrq', but return the offset from `HAYSTACK', rather than the actual address.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
rawmemrlenq:([nonnull] void const *__restrict haystack, $uint64_t qword) -> $size_t {
	return (size_t)(rawmemrchrq(haystack, qword) - (u64 *)haystack);
}


%{
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */


#ifdef __USE_STRING_XCHR
}

@@Same as `memchr', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memxchr:([nonnull] void const *__restrict haystack, int needle, $size_t n_bytes) -> void *
	[([nonnull] void *__restrict haystack, int needle, $size_t n_bytes) -> void *]
	[([nonnull] void const *__restrict haystack, int needle, $size_t n_bytes) -> void const *]
{
	byte_t *hay_iter = (byte_t *)haystack;
	for (; n_bytes--; ++hay_iter) {
		if unlikely(*hay_iter != (byte_t)needle)
			return hay_iter;
	}
	return NULL;
}

@@Same as `memrchr', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memrxchr:([nonnull] void const *__restrict haystack, int needle, $size_t n_bytes) -> void *
	[([nonnull] void *__restrict haystack, int needle, $size_t n_bytes) -> void *]
	[([nonnull] void const *__restrict haystack, int needle, $size_t n_bytes) -> void const *]
{
	byte_t *iter = (byte_t *)haystack + n_bytes;
	while (n_bytes--) {
		if unlikely(*--iter != (byte_t)needle)
			return iter;
	}
	return NULL;
}


@@Same as `rawmemchr', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
rawmemxchr:([nonnull] void const *__restrict haystack, int needle) -> [nonnull] void *
	[([nonnull] void *__restrict haystack, int needle) -> [nonnull] void *]
	[([nonnull] void const *__restrict haystack, int needle) -> [nonnull] void const *]
{
	byte_t *iter = (byte_t *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != (byte_t)needle)
			break;
	}
	return iter;
}

@@Same as `rawmemrchr', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
rawmemrxchr:([nonnull] void const *__restrict haystack, int needle) -> [nonnull] void *
	[([nonnull] void *__restrict haystack, int needle) -> [nonnull] void *]
	[([nonnull] void const *__restrict haystack, int needle) -> [nonnull] void const *]
{
	byte_t *iter = (byte_t *)haystack;
	for (;;) {
		if unlikely(*--iter != (byte_t)needle)
			break;
	}
	return iter;
}

@@Same as `memend', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memxend:([nonnull] void const *__restrict haystack, int needle, $size_t n_bytes) -> [nonnull] void *
	[([nonnull] void *__restrict haystack, int needle, $size_t n_bytes) -> [nonnull] void *]
	[([nonnull] void const *__restrict haystack, int needle, $size_t n_bytes) -> [nonnull] void const *]
{
	byte_t *result = (byte_t *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != (byte_t)needle)
			break;
	}
	return result;
}

@@Same as `memrend', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memrxend:([nonnull] void const *__restrict haystack, int needle, $size_t n_bytes) -> [nonnull] void *
	[([nonnull] void *__restrict haystack, int needle, $size_t n_bytes) -> [nonnull] void *]
	[([nonnull] void const *__restrict haystack, int needle, $size_t n_bytes) -> [nonnull] void const *]
{
	byte_t *result = (byte_t *)haystack + n_bytes;
	while (n_bytes--) {
		if unlikely(*--result != (byte_t)needle)
			break;
	}
	return result;
}

@@Same as `memlen', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memxlen:([nonnull] void const *__restrict haystack, int needle, $size_t n_bytes) -> $size_t {
	return (size_t)((byte_t *)memxend(haystack, needle, n_bytes) - (byte_t *)haystack);
}

@@Same as `memrlen', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memrxlen:([nonnull] void const *__restrict haystack, int needle, $size_t n_bytes) -> $size_t {
	return (size_t)((byte_t *)memrxend(haystack, needle, n_bytes) - (byte_t *)haystack);
}

@@Same as `rawmemlen', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
rawmemxlen:([nonnull] void const *__restrict haystack, int needle) -> $size_t {
	return (size_t)((byte_t *)rawmemxchr(haystack, needle) - (byte_t *)haystack);
}

@@Same as `rawmemrlen', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
rawmemrxlen:([nonnull] void const *__restrict haystack, int needle) -> $size_t {
	return (size_t)((byte_t *)rawmemrxchr(haystack, needle) - (byte_t *)haystack);
}



%#ifdef __USE_STRING_BWLQ

@@Same as `memchrb', but search for non-matching locations.
[noexport][ATTR_WUNUSED][ATTR_PURE]
memxchrb:([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> $uint8_t *
	[([nonnull] void *__restrict haystack, int byte, $size_t n_bytes) -> $uint8_t *]
	[([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> $uint8_t const *]
	= memxchr;

@@Same as `memchrw', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memxchrw:([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_words) -> $uint16_t *
	[([nonnull] void *__restrict haystack, $uint16_t word, $size_t n_words) -> $uint16_t *]
	[([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_words) -> $uint16_t const *]
{
	u16 *hay_iter = (u16 *)haystack;
	for (; n_words--; ++hay_iter) {
		if unlikely(*hay_iter != word)
			return hay_iter;
	}
	return NULL;
}

@@Same as `memchrl', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memxchrl:([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> $uint32_t *
	[([nonnull] void *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> $uint32_t *]
	[([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> $uint32_t const *]
{
	u32 *hay_iter = (u32 *)haystack;
	for (; n_dwords--; ++hay_iter) {
		if unlikely(*hay_iter != dword)
			return hay_iter;
	}
	return NULL;
}

@@Same as `memrchrb', but search for non-matching locations.
[noexport][ATTR_WUNUSED][ATTR_PURE]
memrxchrb:([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> $uint8_t *
	[([nonnull] void *__restrict haystack, int byte, $size_t n_bytes) -> $uint8_t *]
	[([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> $uint8_t const *]
	= memrxchr;

@@Same as `memrchrw', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memrxchrw:([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_words) -> $uint16_t *
	[([nonnull] void *__restrict haystack, $uint16_t word, $size_t n_words) -> $uint16_t *]
	[([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_words) -> $uint16_t const *]
{
	u16 *iter = (u16 *)haystack + n_words;
	while (n_words--) {
		if unlikely(*--iter != word)
			return iter;
	}
	return NULL;
}

@@Same as `memrchrl', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memrxchrl:([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> $uint32_t *
	[([nonnull] void *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> $uint32_t *]
	[([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> $uint32_t const *]
{
	u32 *iter = (u32 *)haystack + n_dwords;
	while (n_dwords--) {
		if unlikely(*--iter != dword)
			return iter;
	}
	return NULL;
}

@@Same as `rawmemchrb', but search for non-matching locations.
[noexport][ATTR_WUNUSED][ATTR_PURE]
rawmemxchrb:([nonnull] void const *__restrict haystack, int byte) -> [nonnull] $uint8_t *
	[([nonnull] void *__restrict haystack, int byte) -> [nonnull] $uint8_t *]
	[([nonnull] void const *__restrict haystack, int byte) -> [nonnull] $uint8_t const *]
	= rawmemxchr;

@@Same as `rawmemchrw', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
rawmemxchrw:([nonnull] void const *__restrict haystack, $uint16_t word) -> [nonnull] $uint16_t *
	[([nonnull] void *__restrict haystack, $uint16_t word) -> [nonnull] $uint16_t *]
	[([nonnull] void const *__restrict haystack, $uint16_t word) -> [nonnull] $uint16_t const *]
{
	u16 *iter = (u16 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != word)
			break;
	}
	return iter;
}

@@Same as `rawmemchrl', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
rawmemxchrl:([nonnull] void const *__restrict haystack, $uint32_t dword) -> [nonnull] $uint32_t *
	[([nonnull] void *__restrict haystack, $uint32_t dword) -> [nonnull] $uint32_t *]
	[([nonnull] void const *__restrict haystack, $uint32_t dword) -> [nonnull] $uint32_t const *]
{
	u32 *iter = (u32 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != dword)
			break;
	}
	return iter;
}


@@Same as `rawmemrchrb', but search for non-matching locations.
[noexport][ATTR_WUNUSED][ATTR_PURE]
rawmemrxchrb:([nonnull] void const *__restrict haystack, int byte) -> [nonnull] $uint8_t *
	[([nonnull] void *__restrict haystack, int byte) -> [nonnull] $uint8_t *]
	[([nonnull] void const *__restrict haystack, int byte) -> [nonnull] $uint8_t const *]
	= rawmemrxchr;

@@Same as `rawmemrchrw', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
rawmemrxchrw:([nonnull] void const *__restrict haystack, $uint16_t word) -> [nonnull] $uint16_t *
	[([nonnull] void *__restrict haystack, $uint16_t word) -> [nonnull] $uint16_t *]
	[([nonnull] void const *__restrict haystack, $uint16_t word) -> [nonnull] $uint16_t const *]
{
	u16 *iter = (u16 *)haystack;
	for (;;) {
		if unlikely(*--iter != word)
			break;
	}
	return iter;
}

@@Same as `rawmemrchrl', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
rawmemrxchrl:([nonnull] void const *__restrict haystack, $uint32_t dword) -> [nonnull] $uint32_t *
	[([nonnull] void *__restrict haystack, $uint32_t dword) -> [nonnull] $uint32_t *]
	[([nonnull] void const *__restrict haystack, $uint32_t dword) -> [nonnull] $uint32_t const *]
{
	u32 *iter = (u32 *)haystack;
	for (;;) {
		if unlikely(*--iter != dword)
			break;
	}
	return iter;
}


@@Same as `memendb', but search for non-matching locations.
[noexport][ATTR_WUNUSED][ATTR_PURE]
memxendb:([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> [nonnull] $uint8_t *
	[([nonnull] void *__restrict haystack, int byte, $size_t n_bytes) -> [nonnull] $uint8_t *]
	[([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> [nonnull] $uint8_t const *]
	= memxend;

@@Same as `memendw', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memxendw:([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_bytes) -> [nonnull] $uint16_t *
	[([nonnull] void *__restrict haystack, $uint16_t word, $size_t n_bytes) -> [nonnull] $uint16_t *]
	[([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_bytes) -> [nonnull] $uint16_t const *]
{
	u16 *result = (u16 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != word)
			break;
	}
	return result;
}

@@Same as `memendl', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memxendl:([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_bytes) -> [nonnull] $uint32_t *
	[([nonnull] void *__restrict haystack, $uint32_t dword, $size_t n_bytes) -> [nonnull] $uint32_t *]
	[([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_bytes) -> [nonnull] $uint32_t const *]
{
	u32 *result = (u32 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != dword)
			break;
	}
	return result;
}


@@Same as `memrendb', but search for non-matching locations.
[noexport][ATTR_WUNUSED][ATTR_PURE]
memrxendb:([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> [nonnull] $uint8_t *
	[([nonnull] void *__restrict haystack, int byte, $size_t n_bytes) -> [nonnull] $uint8_t *]
	[([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> [nonnull] $uint8_t const *]
	= memrxend;

@@Same as `memrendw', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memrxendw:([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_words) -> [nonnull] $uint16_t *
	[([nonnull] void *__restrict haystack, $uint16_t word, $size_t n_words) -> [nonnull] $uint16_t *]
	[([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_words) -> [nonnull] $uint16_t const *]
{
	u16 *result = (u16 *)haystack + n_words;
	while (n_words--) {
		if unlikely(*--result != word)
			break;
	}
	return result;
}

@@Same as `memrendl', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memrxendl:([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> [nonnull] $uint32_t *
	[([nonnull] void *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> [nonnull] $uint32_t *]
	[([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> [nonnull] $uint32_t const *]
{
	u32 *result = (u32 *)haystack + n_dwords;
	while (n_dwords--) {
		if unlikely(*--result != dword)
			break;
	}
	return result;
}



@@Same as `memlenb', but search for non-matching locations.
[noexport][ATTR_WUNUSED][ATTR_PURE]
memxlenb:([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> $size_t = memxlen;

@@Same as `memlenw', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memxlenw:([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_words) -> $size_t {
	return (size_t)(memxendw(haystack, word, n_words) - (u16 *)haystack);
}

@@Same as `memlenl', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memxlenl:([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> $size_t {
	return (size_t)(memxendl(haystack, dword, n_dwords) - (u32 *)haystack);
}

@@Same as `memrlenb', but search for non-matching locations.
[noexport][ATTR_WUNUSED][ATTR_PURE]
memrxlenb:([nonnull] void const *__restrict haystack, int byte, $size_t n_bytes) -> $size_t = memrxlen;

@@Same as `memrlenw', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memrxlenw:([nonnull] void const *__restrict haystack, $uint16_t word, $size_t n_words) -> $size_t {
	return (size_t)(memrxendw(haystack, word, n_words) - (u16 *)haystack);
}

@@Same as `memrlenl', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memrxlenl:([nonnull] void const *__restrict haystack, $uint32_t dword, $size_t n_dwords) -> $size_t {
	return (size_t)(memrxendl(haystack, dword, n_dwords) - (u32 *)haystack);
}



@@Same as `rawmemlenb', but search for non-matching locations.
[noexport][ATTR_WUNUSED][ATTR_PURE]
rawmemxlenb:([nonnull] void const *__restrict haystack, int needle) -> $size_t = rawmemxlen;

@@Same as `rawmemlenw', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
rawmemxlenw:([nonnull] void const *__restrict haystack, $uint16_t word) -> $size_t {
	return (size_t)(rawmemxchrw(haystack, word) - (u16 *)haystack);
}

@@Same as `rawmemlenl', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
rawmemxlenl:([nonnull] void const *__restrict haystack, $uint32_t dword) -> $size_t {
	return (size_t)(rawmemxchrl(haystack, dword) - (u32 *)haystack);
}


@@Same as `rawmemrlenb', but search for non-matching locations.
[noexport][ATTR_WUNUSED][ATTR_PURE]
rawmemrxlenb:([nonnull] void const *__restrict haystack, int needle) -> $size_t = rawmemrxlen;

@@Same as `rawmemrlenw', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
rawmemrxlenw:([nonnull] void const *__restrict haystack, $uint16_t word) -> $size_t {
	return (size_t)(rawmemrxchrw(haystack, word) - (u16 *)haystack);
}

@@Same as `rawmemrlenl', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
rawmemrxlenl:([nonnull] void const *__restrict haystack, $uint32_t dword) -> $size_t {
	return (size_t)(rawmemrxchrl(haystack, dword) - (u32 *)haystack);
}



%#ifdef __UINT64_TYPE__

@@Same as `memchrq', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memxchrq:([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> $uint64_t *
	[([nonnull] void *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> $uint64_t *]
	[([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> $uint64_t const *]
{
	u64 *hay_iter = (u64 *)haystack;
	for (; n_qwords--; ++hay_iter) {
		if unlikely(*hay_iter != (u64)qword)
			return hay_iter;
	}
	return NULL;
}

@@Same as `memrchrq', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memrxchrq:([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> $uint64_t *
	[([nonnull] void *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> $uint64_t *]
	[([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> $uint64_t const *]
{
	u64 *iter = (u64 *)haystack + n_qwords;
	while (n_qwords--) {
		if unlikely(*--iter != qword)
			return iter;
	}
	return NULL;
}

@@Same as `rawmemchrq', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
rawmemxchrq:([nonnull] void const *__restrict haystack, $uint64_t qword) -> [nonnull] $uint64_t *
	[([nonnull] void *__restrict haystack, $uint64_t qword) -> [nonnull] $uint64_t *]
	[([nonnull] void const *__restrict haystack, $uint64_t qword) -> [nonnull] $uint64_t const *]
{
	u64 *iter = (u64 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != qword)
			break;
	}
	return iter;
}

@@Same as `rawmemrchrq', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
rawmemrxchrq:([nonnull] void const *__restrict haystack, $uint64_t qword) -> [nonnull] $uint64_t *
	[([nonnull] void *__restrict haystack, $uint64_t qword) -> [nonnull] $uint64_t *]
	[([nonnull] void const *__restrict haystack, $uint64_t qword) -> [nonnull] $uint64_t const *]
{
	u64 *iter = (u64 *)haystack;
	for (;;) {
		if unlikely(*--iter != qword)
			break;
	}
	return iter;
}

@@Same as `memendq', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memxendq:([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_bytes) -> [nonnull] $uint64_t *
	[([nonnull] void *__restrict haystack, $uint64_t qword, $size_t n_bytes) -> [nonnull] $uint64_t *]
	[([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_bytes) -> [nonnull] $uint64_t const *]
{
	u64 *result = (u64 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != qword)
			break;
	}
	return result;
}

@@Same as `memrendq', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memrxendq:([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> [nonnull] $uint64_t *
	[([nonnull] void *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> [nonnull] $uint64_t *]
	[([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> [nonnull] $uint64_t const *]
{
	u64 *result = (u64 *)haystack + n_qwords;
	while (n_qwords--) {
		if unlikely(*--result != qword)
			break;
	}
	return result;
}

@@Same as `memlenq', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memxlenq:([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> $size_t {
	return (size_t)(memxendq(haystack, qword, n_qwords) - (u64 *)haystack);
}

@@Same as `memrlenq', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
memrxlenq:([nonnull] void const *__restrict haystack, $uint64_t qword, $size_t n_qwords) -> $size_t {
	return (size_t)(memrxendq(haystack, qword, n_qwords) - (u64 *)haystack);
}

@@Same as `rawmemlenq', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
rawmemxlenq:([nonnull] void const *__restrict haystack, $uint64_t qword) -> $size_t {
	return (size_t)(rawmemxchrq(haystack, qword) - (u64 *)haystack);
}

@@Same as `rawmemrlenq', but search for non-matching locations.
[ATTR_WUNUSED][ATTR_PURE]
rawmemrxlenq:([nonnull] void const *__restrict haystack, $uint64_t qword) -> $size_t {
	return (size_t)(rawmemrxchrq(haystack, qword) - (u64 *)haystack);
}

%{
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */
#endif /* __USE_STRING_XCHR */





#ifdef __USE_KOS
}


/* KOS String extension functions. */
@@Same as `STR+strlen(STR)'
[libc][kernel][ATTR_WUNUSED][ATTR_PURE]
strend:([nonnull] char const *__restrict string) -> [nonnull] char *
	[([nonnull] char *__restrict string) -> [nonnull] char *]
	[([nonnull] char const *__restrict string) -> [nonnull] char const *]
{
	while (*string)
		++string;
	return (char *)string;
}

@@Same as `STR+strnlen(STR, MAX_CHARS)'
[libc][kernel][ATTR_WUNUSED][ATTR_PURE]
strnend:([nonnull] char const *__restrict string, $size_t maxlen) -> [nonnull] char *
	[([nonnull] char *__restrict string, $size_t maxlen) -> [nonnull] char *]
	[([nonnull] char const *__restrict string, $size_t maxlen) -> [nonnull] char const *]
{
	for (; maxlen && *string; ++string, --maxlen)
		;
	return (char *)string;
}

@@Same as `strchr', but don't exceed `MAX_CHARS' characters.
[ATTR_WUNUSED][ATTR_PURE]
strnchr:([nonnull] char const *__restrict haystack, int needle, $size_t maxlen) -> char *
	[([nonnull] char *__restrict haystack, int needle, $size_t maxlen) -> char *]
	[([nonnull] char const *__restrict haystack, int needle, $size_t maxlen) -> char const *]
{
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			return (char *)haystack;
	}
	return NULL;
}

@@Same as `strrchr', but don't exceed `MAX_CHARS' characters.
[ATTR_WUNUSED][ATTR_PURE]
strnrchr:([nonnull] char const *__restrict haystack, int needle, $size_t maxlen) -> char *
	[([nonnull] char *__restrict haystack, int needle, $size_t maxlen) -> char *]
	[([nonnull] char const *__restrict haystack, int needle, $size_t maxlen) -> char const *]
{
	char const *result = NULL;
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			result = haystack;
	}
	return (char *)result;
}

@@Same as `strrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found.
[ATTR_WUNUSED][ATTR_PURE]
strrchrnul:([nonnull] char const *__restrict haystack, int needle) -> [nonnull] char *
	[([nonnull] char *__restrict haystack, int needle) -> [nonnull] char *]
	[([nonnull] char const *__restrict haystack, int needle) -> [nonnull] char const *]
{
	char const *result = haystack - 1;
	do {
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			result = haystack;
	} while (*haystack++);
	return (char *)result;
}

@@Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found.
[ATTR_WUNUSED][ATTR_PURE]
strnchrnul:([nonnull] char const *__restrict haystack, int needle, $size_t maxlen) -> [nonnull] char *
	[([nonnull] char *__restrict haystack, int needle, $size_t maxlen) -> [nonnull] char *]
	[([nonnull] char const *__restrict haystack, int needle, $size_t maxlen) -> [nonnull] char const *]
{
	for (; maxlen-- && *haystack && (unsigned char)*haystack != (unsigned char)needle; ++haystack)
		;
	return (char *)haystack;
}

@@Same as `strnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found.
[ATTR_WUNUSED][ATTR_PURE]
strnrchrnul:([nonnull] char const *__restrict haystack, int needle, $size_t maxlen) -> [nonnull] char *
	[([nonnull] char *__restrict haystack, int needle, $size_t maxlen) -> [nonnull] char *]
	[([nonnull] char const *__restrict haystack, int needle, $size_t maxlen) -> [nonnull] char const *]
{
	char const *result = haystack - 1;
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			result = haystack;
	}
	return (char *)result;
}

@@Same as `strchrnul', but return the offset from `STR', rather than the actual address
[ATTR_WUNUSED][ATTR_PURE]
stroff:([nonnull] char const *__restrict haystack, int needle) -> $size_t {
	return (size_t)(strchrnul(haystack, needle) - haystack);
}

@@Same as `strrchrnul', but return the offset from `STR', rather than the actual address
[ATTR_WUNUSED][ATTR_PURE]
strroff:([nonnull] char const *__restrict haystack, int needle) -> $size_t {
	return (size_t)(strrchrnul(haystack, needle) - haystack);
}

@@Same as `strnchrnul', but return the offset from `STR', rather than the actual address
[ATTR_WUNUSED][ATTR_PURE]
strnoff:([nonnull] char const *__restrict haystack, int needle, $size_t maxlen) -> $size_t {
	return (size_t)(strnchrnul(haystack, needle, maxlen) - haystack);
}

@@Same as `strnrchrnul', but return the offset from `STR', rather than the actual address
[ATTR_WUNUSED][ATTR_PURE]
strnroff:([nonnull] char const *__restrict haystack, int needle, $size_t maxlen) -> $size_t {
	return (size_t)(strnrchrnul(haystack, needle, maxlen) - haystack);
}


@@Same as `memset', but return `DST+N_BYTES', rather than `DST'
[fast][libc][kernel]
mempset:([nonnull] void *__restrict dst, int byte, $size_t n_bytes) -> [nonnull] void * {
	return (void *)((byte_t *)memset(dst, byte, n_bytes) + n_bytes);
}

@@Same as `memmove', but return `DST+N_BYTES', rather than `DST'
[fast][libc][kernel]
mempmove:([nonnull] void *dst, [nonnull] void const *src, $size_t n_bytes) -> [nonnull] void * {
	return (void *)((byte_t *)memmove(dst, src, n_bytes) + n_bytes);
}

@@Same as `memrchr' without a search limit, starting at `HAYSTACK-1'
[kernel][ATTR_WUNUSED][ATTR_PURE]
rawmemrchr:([nonnull] void const *__restrict haystack, int needle) -> [nonnull] void *
	[([nonnull] void *__restrict haystack, int needle) -> [nonnull] void *]
	[([nonnull] void const *__restrict haystack, int needle) -> [nonnull] void const *]
{
	byte_t *iter = (byte_t *)haystack;
	for (;;) {
		if unlikely(*--iter == (byte_t)needle)
			break;
	}
	return iter;
}


/* This could be an idea. - But it may also turn out like memxch(), and never be used... */
//[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
//memdiff:([nonnull] void const *__restrict data, void const *__restrict baseline, $size_t n_bytes) -> void *
//	[([nonnull] void *__restrict data, void const *__restrict baseline, $size_t n_bytes) -> void *]
//	[([nonnull] void const *__restrict data, void const *__restrict baseline, $size_t n_bytes) -> void const *]
//{
//	byte_t *diter = (byte_t *)data;
//	byte_t *biter = (byte_t *)baseline;
//	for (; n_bytes--; ++diter, ++biter) {
//		if unlikely(*diter != *biter)
//			return diter;
//	}
//	return NULL;
//}
//[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
//memrdiff:([nonnull] void const *__restrict data, void const *__restrict baseline, $size_t n_bytes) -> void *
//	[([nonnull] void *__restrict data, void const *__restrict baseline, $size_t n_bytes) -> void *]
//	[([nonnull] void const *__restrict data, void const *__restrict baseline, $size_t n_bytes) -> void const *]
//{
//	byte_t *diter = (byte_t *)data + n_bytes;
//	byte_t *biter = (byte_t *)baseline + n_bytes;
//	while (n_bytes--) {
//		if unlikely(*--diter != *--biter)
//			return diter;
//	}
//	return NULL;
//}

@@Same as `memchr', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
memend:([nonnull] void const *__restrict haystack, int needle, $size_t n_bytes) -> [nonnull] void *
	[([nonnull] void *__restrict haystack, int needle, $size_t n_bytes) -> [nonnull] void *]
	[([nonnull] void const *__restrict haystack, int needle, $size_t n_bytes) -> [nonnull] void const *]
{
	byte_t *result = (byte_t *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == (byte_t)needle)
			break;
	}
	return result;
}

@@Same as `memrchr', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
memrend:([nonnull] void const *__restrict haystack, int needle, $size_t n_bytes) -> [nonnull] void *
	[([nonnull] void *__restrict haystack, int needle, $size_t n_bytes) -> [nonnull] void *]
	[([nonnull] void const *__restrict haystack, int needle, $size_t n_bytes) -> [nonnull] void const *]
{
	byte_t *result = (byte_t *)haystack + n_bytes;
	while (n_bytes--) {
		if unlikely(*--result == (byte_t)needle)
			break;
	}
	return result;
}

@@Same as `memend', but return the offset from `HAYSTACK', rather than the actual address.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
memlen:([nonnull] void const *__restrict haystack, int needle, $size_t n_bytes) -> $size_t {
	return (size_t)((byte_t *)memend(haystack, needle, n_bytes) - (byte_t *)haystack);
}

@@Same as `memrend', but return the offset from `HAYSTACK', rather than the actual address.
[fast][libc][kernel][ATTR_WUNUSED][ATTR_PURE]
memrlen:([nonnull] void const *__restrict haystack, int needle, $size_t n_bytes) -> $size_t {
	return (size_t)((byte_t *)memrend(haystack, needle, n_bytes) - (byte_t *)haystack);
}

@@Same as `rawmemchr', but return the offset from `HAYSTACK', rather than the actual address.
[kernel][ATTR_WUNUSED][ATTR_PURE]
rawmemlen:([nonnull] void const *__restrict haystack, int needle) -> $size_t {
	return (size_t)((byte_t *)rawmemchr(haystack, needle) - (byte_t *)haystack);
}

@@Same as `rawmemrchr', but return the offset from `HAYSTACK', rather than the actual address.
[kernel][ATTR_WUNUSED][ATTR_PURE]
rawmemrlen:([nonnull] void const *__restrict haystack, int needle) -> $size_t {
	return (size_t)((byte_t *)rawmemrchr(haystack, needle) - (byte_t *)haystack);
}


@@Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
@@If no such sub-string exists, return `NULL' instead.
@@#ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
@@When `needlelen' is ZERO(0), also return `NULL' unconditionally.
@@#else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
@@When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
@@#endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
[libc][ATTR_WUNUSED][ATTR_PURE][impl_include(<features.h>)]
[if(defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), preferred_alias(memrmem0)]
[if(!defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), preferred_alias(memrmem)]
memrmem:([nonnull] void const *haystack, $size_t haystacklen, [nonnull] void const *needle, $size_t needlelen) -> void *
	[([nonnull] void *haystack, $size_t haystacklen, [nonnull] void const *needle, $size_t needlelen) -> void *]
	[([nonnull] void const *haystack, $size_t haystacklen, [nonnull] void const *needle, $size_t needlelen) -> void const *]
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
[noexport]
mempatb:([nonnull] void *__restrict dst,
         int pattern, $size_t n_bytes) -> [== dst] void * = memset;

@@Same as `memsetw', but repeat a 2-byte pattern on aligned addresses.
[fast][libc][kernel][dependency_include(<hybrid/__wordbits.h>)]
mempatw:([nonnull] void *__restrict dst,
         $uint16_t pattern, $size_t n_bytes) -> [== dst] void * {
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
[fast][libc][kernel][dependency_include(<hybrid/__wordbits.h>)]
mempatl:([nonnull] void *__restrict dst,
         $uint32_t pattern, $size_t n_bytes) -> [== dst] void * {
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
[fast][libc][kernel][dependency_include(<hybrid/__wordbits.h>)]
mempatq:([nonnull] void *__restrict dst,
         $uint64_t pattern, $size_t n_bytes) -> [== dst] void * {
	byte_t *iter = (byte_t *)dst;
	for (; n_bytes && (uintptr_t)iter & 7; ++iter, --n_bytes)
		*iter = __INT64_BYTE(pattern, (uintptr_t)iter & 7);
	iter = (byte_t *)mempsetq(iter, pattern, n_bytes / 8);
	for (n_bytes &= 7; n_bytes; ++iter, --n_bytes)
		*iter = __INT64_BYTE(pattern, (uintptr_t)iter & 7);
	return dst;
}
%#endif /* __UINT64_TYPE__ */

[alias(memicmp, _memicmp)][ATTR_WUNUSED]
[section(.text.crt.unicode.static.memory)]
memcasecmp:([nonnull] void const *s1,
            [nonnull] void const *s2, $size_t n_bytes) -> int {
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
[ATTR_WUNUSED][ATTR_PURE][impl_include(<features.h>)]
[if(defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), preferred_alias(memcasemem0)]
[if(!defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), preferred_alias(memcasemem)]
[section(.text.crt.unicode.static.memory)]
memcasemem:([nonnull] void const *haystack, $size_t haystacklen, [nonnull] void const *needle, $size_t needlelen) -> void *
	[([nonnull] void *haystack, $size_t haystacklen, [nonnull] void const *needle, $size_t needlelen) -> void *]
	[([nonnull] void const *haystack, $size_t haystacklen, [nonnull] void const *needle, $size_t needlelen) -> void const *]
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
[alias(_memicmp_l)][ATTR_WUNUSED]
[section(.text.crt.unicode.locale.memory)]
memcasecmp_l:([nonnull] void const *s1,
              [nonnull] void const *s2,
              $size_t n_bytes, $locale_t locale) -> int {
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
[ATTR_WUNUSED][ATTR_PURE][impl_include(<features.h>)]
[if(defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), preferred_alias(memcasemem0_l)]
[if(!defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)), preferred_alias(memcasemem_l)]
[section(.text.crt.unicode.locale.memory)]
memcasemem_l:([nonnull] void const *haystack, $size_t haystacklen, [nonnull] void const *needle, $size_t needlelen, $locale_t locale) -> void *
	[([nonnull] void *haystack, $size_t haystacklen, [nonnull] void const *needle, $size_t needlelen, $locale_t locale) -> void *]
	[([nonnull] void const *haystack, $size_t haystacklen, [nonnull] void const *needle, $size_t needlelen, $locale_t locale) -> void const *]
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

[ATTR_WUNUSED][section(.text.crt.unicode.locale.memory)]
strcasestr_l:([nonnull] char const *haystack, [nonnull] char const *needle, $locale_t locale) -> char *
	[([nonnull] char *haystack, [nonnull] char const *needle, $locale_t locale) -> char *]
	[([nonnull] char const *haystack, [nonnull] char const *needle, $locale_t locale) -> char const *]
{
	for (; *haystack; ++haystack) {
		if (strcasecmp_l(haystack, needle, locale) == 0)
			return (char *)haystack;
	}
	return NULL;
}
%{
#endif /* __USE_XOPEN2K8 */



}


[nothrow][user][noexport]
[impl_prefix(
#ifndef ___local_sys_errlist_defined
#define ___local_sys_errlist_defined 1
#if defined(__CRT_HAVE__sys_errlist) && defined(__CRT_HAVE__sys_nerr)
__LIBC char const *const _sys_errlist[];
__LIBC int _sys_nerr;
#elif defined(__CRT_HAVE___sys_errlist) && defined(__CRT_HAVE___sys_nerr)
__LIBC __ATTR_WUNUSED __ATTR_CONST char const *const *(__LIBCCALL __sys_errlist)(void);
__LIBC __ATTR_WUNUSED __ATTR_CONST int *(__LIBCCALL __sys_nerr)(void);
#else
#undef ___local_sys_errlist_defined
#endif
#endif /* !___local_sys_errlist_defined */
)]
[ATTR_WUNUSED][ATTR_CONST][nothrow][section(.text.crt.errno)]
strerror_s:(int errnum) -> char const * {
#if defined(__CRT_HAVE__sys_errlist) && defined(__CRT_HAVE__sys_nerr)
	return (unsigned int)errnum < (unsigned int)@_sys_nerr@ ? @_sys_errlist@[errnum] : NULL;
#elif defined(__CRT_HAVE___sys_errlist) && defined(__CRT_HAVE___sys_nerr)
	return (unsigned int)errnum < (unsigned int)*@__sys_nerr@() ? @__sys_errlist@()[errnum] : NULL;
#else
	char const *result;
	switch (errnum) {

#ifdef @__EPERM@
	case @__EPERM@:           result = "Operation not permitted"; break;
#endif /* __EPERM */
#ifdef @__ENOENT@
	case @__ENOENT@:          result = "No such file or directory"; break;
#endif /* __ENOENT */
#ifdef @__ESRCH@
	case @__ESRCH@:           result = "No such process"; break;
#endif /* __ESRCH */
#ifdef @__EINTR@
	case @__EINTR@:           result = "Interrupted system call"; break;
#endif /* __EINTR */
#ifdef @__EIO@
	case @__EIO@:             result = "I/O error"; break;
#endif /* __EIO */
#ifdef @__ENXIO@
	case @__ENXIO@:           result = "No such device or address"; break;
#endif /* __ENXIO */
#ifdef @__E2BIG@
	case @__E2BIG@:           result = "Argument list too long"; break;
#endif /* __E2BIG */
#ifdef @__ENOEXEC@
	case @__ENOEXEC@:         result = "Exec format error"; break;
#endif /* __ENOEXEC */
#ifdef @__EBADF@
	case @__EBADF@:           result = "Bad file number"; break;
#endif /* __EBADF */
#ifdef @__ECHILD@
	case @__ECHILD@:          result = "No child processes"; break;
#endif /* __ECHILD */
#ifdef @__EAGAIN@
	case @__EAGAIN@:          result = "Try again"; break;
#endif /* __EAGAIN */
#ifdef @__ENOMEM@
	case @__ENOMEM@:          result = "Out of memory"; break;
#endif /* __ENOMEM */
#ifdef @__EACCES@
	case @__EACCES@:          result = "Permission denied"; break;
#endif /* __EACCES */
#ifdef @__EFAULT@
	case @__EFAULT@:          result = "Bad address"; break;
#endif /* __EFAULT */
#ifdef @__EBUSY@
	case @__EBUSY@:           result = "Device or resource busy"; break;
#endif /* __EBUSY */
#ifdef @__EEXIST@
	case @__EEXIST@:          result = "File exists"; break;
#endif /* __EEXIST */
#ifdef @__EXDEV@
	case @__EXDEV@:           result = "Cross-device link"; break;
#endif /* __EXDEV */
#ifdef @__ENODEV@
	case @__ENODEV@:          result = "No such device"; break;
#endif /* __ENODEV */
#ifdef @__ENOTDIR@
	case @__ENOTDIR@:         result = "Not a directory"; break;
#endif /* __ENOTDIR */
#ifdef @__EISDIR@
	case @__EISDIR@:          result = "Is a directory"; break;
#endif /* __EISDIR */
#ifdef @__ENFILE@
	case @__ENFILE@:          result = "File table overflow"; break;
#endif /* __ENFILE */
#ifdef @__EMFILE@
	case @__EMFILE@:          result = "Too many open files"; break;
#endif /* __EMFILE */
#ifdef @__ENOTTY@
	case @__ENOTTY@:          result = "Not a typewriter"; break;
#endif /* __ENOTTY */
#ifdef @__EFBIG@
	case @__EFBIG@:           result = "File too large"; break;
#endif /* __EFBIG */
#ifdef @__ENOSPC@
	case @__ENOSPC@:          result = "No space left on device"; break;
#endif /* __ENOSPC */
#ifdef @__ESPIPE@
	case @__ESPIPE@:          result = "Illegal seek"; break;
#endif /* __ESPIPE */
#ifdef @__EROFS@
	case @__EROFS@:           result = "Read-only file system"; break;
#endif /* __EROFS */
#ifdef @__EMLINK@
	case @__EMLINK@:          result = "Too many links"; break;
#endif /* __EMLINK */
#ifdef @__EPIPE@
	case @__EPIPE@:           result = "Broken pipe"; break;
#endif /* __EPIPE */
#ifdef @__EDOM@
	case @__EDOM@:            result = "Math argument out of domain of func"; break;
#endif /* __EDOM */
#ifdef @__ENAMETOOLONG@
	case @__ENAMETOOLONG@:    result = "File name too long"; break;
#endif /* __ENAMETOOLONG */
#ifdef @__ENOLCK@
	case @__ENOLCK@:          result = "No record locks available"; break;
#endif /* __ENOLCK */
#ifdef @__ENOSYS@
	case @__ENOSYS@:          result = "Function not implemented"; break;
#endif /* __ENOSYS */
#ifdef @__ENOTEMPTY@
	case @__ENOTEMPTY@:       result = "Directory not empty"; break;
#endif /* __ENOTEMPTY */
#ifdef @__EINVAL@
	case @__EINVAL@:          result = "Invalid argument"; break;
#endif /* __EINVAL */
#ifdef @__ERANGE@
	case @__ERANGE@:          result = "Math result not representable"; break;
#endif /* __ERANGE */
#ifdef @__EILSEQ@
	case @__EILSEQ@:          result = "Illegal byte sequence"; break;
#endif /* __EILSEQ */
#ifdef @__EDEADLOCK@
	case @__EDEADLOCK@:       result = "Resource deadlock would occur"; break;
#endif /* __EDEADLOCK */
#ifdef @__EADDRINUSE@
	case @__EADDRINUSE@:      result = "Address already in use"; break;
#endif /* __EADDRINUSE */
#ifdef @__EADDRNOTAVAIL@
	case @__EADDRNOTAVAIL@:   result = "Cannot assign requested address"; break;
#endif /* __EADDRNOTAVAIL */
#ifdef @__EAFNOSUPPORT@
	case @__EAFNOSUPPORT@:    result = "Address family not supported by protocol"; break;
#endif /* __EAFNOSUPPORT */
#ifdef @__EALREADY@
	case @__EALREADY@:        result = "Operation already in progress"; break;
#endif /* __EALREADY */
#ifdef @__EBADMSG@
	case @__EBADMSG@:         result = "Not a data message"; break;
#endif /* __EBADMSG */
#ifdef @__ECANCELED@
	case @__ECANCELED@:       result = "Operation Canceled"; break;
#endif /* __ECANCELED */
#ifdef @__ECONNABORTED@
	case @__ECONNABORTED@:    result = "Software caused connection abort"; break;
#endif /* __ECONNABORTED */
#ifdef @__ECONNREFUSED@
	case @__ECONNREFUSED@:    result = "Connection refused"; break;
#endif /* __ECONNREFUSED */
#ifdef @__ECONNRESET@
	case @__ECONNRESET@:      result = "Connection reset by peer"; break;
#endif /* __ECONNRESET */
#ifdef @__EDESTADDRREQ@
	case @__EDESTADDRREQ@:    result = "Destination address required"; break;
#endif /* __EDESTADDRREQ */
#ifdef @__EHOSTUNREACH@
	case @__EHOSTUNREACH@:    result = "No route to host"; break;
#endif /* __EHOSTUNREACH */
#ifdef @__EIDRM@
	case @__EIDRM@:           result = "Identifier removed"; break;
#endif /* __EIDRM */
#ifdef @__EINPROGRESS@
	case @__EINPROGRESS@:     result = "Operation now in progress"; break;
#endif /* __EINPROGRESS */
#ifdef @__EISCONN@
	case @__EISCONN@:         result = "Transport endpoint is already connected"; break;
#endif /* __EISCONN */
#ifdef @__ELOOP@
	case @__ELOOP@:           result = "Too many symbolic links encountered"; break;
#endif /* __ELOOP */
#ifdef @__EMSGSIZE@
	case @__EMSGSIZE@:        result = "Message too long"; break;
#endif /* __EMSGSIZE */
#ifdef @__ENETDOWN@
	case @__ENETDOWN@:        result = "Network is down"; break;
#endif /* __ENETDOWN */
#ifdef @__ENETRESET@
	case @__ENETRESET@:       result = "Network dropped connection because of reset"; break;
#endif /* __ENETRESET */
#ifdef @__ENETUNREACH@
	case @__ENETUNREACH@:     result = "Network is unreachable"; break;
#endif /* __ENETUNREACH */
#ifdef @__ENOBUFS@
	case @__ENOBUFS@:         result = "No buffer space available"; break;
#endif /* __ENOBUFS */
#ifdef @__ENODATA@
	case @__ENODATA@:         result = "No data available"; break;
#endif /* __ENODATA */
#ifdef @__ENOLINK@
	case @__ENOLINK@:         result = "Link has been severed"; break;
#endif /* __ENOLINK */
#ifdef @__ENOMSG@
	case @__ENOMSG@:          result = "No message of desired type"; break;
#endif /* __ENOMSG */
#ifdef @__ENOPROTOOPT@
	case @__ENOPROTOOPT@:     result = "Protocol not available"; break;
#endif /* __ENOPROTOOPT */
#ifdef @__ENOSR@
	case @__ENOSR@:           result = "Out of streams resources"; break;
#endif /* __ENOSR */
#ifdef @__ENOSTR@
	case @__ENOSTR@:          result = "Device not a stream"; break;
#endif /* __ENOSTR */
#ifdef @__ENOTCONN@
	case @__ENOTCONN@:        result = "Transport endpoint is not connected"; break;
#endif /* __ENOTCONN */
#ifdef @__ENOTRECOVERABLE@
	case @__ENOTRECOVERABLE@: result = "State not recoverable"; break;
#endif /* __ENOTRECOVERABLE */
#ifdef @__ENOTSOCK@
	case @__ENOTSOCK@:        result = "Socket operation on non-socket"; break;
#endif /* __ENOTSOCK */
#ifdef @__ENOTSUP@
	case @__ENOTSUP@:         result = "Not supported"; break;
#endif /* __ENOTSUP */
#ifdef @__EOPNOTSUPP@
	case @__EOPNOTSUPP@:      result = "Operation not supported on transport endpoint"; break;
#endif /* __EOPNOTSUPP */
#ifdef @__EOTHER@
	case @__EOTHER@:          result = "Other"; break;
#endif /* __EOTHER */
#ifdef @__EOVERFLOW@
	case @__EOVERFLOW@:       result = "Value too large for defined data type"; break;
#endif /* __EOVERFLOW */
#ifdef @__EOWNERDEAD@
	case @__EOWNERDEAD@:      result = "Owner died"; break;
#endif /* __EOWNERDEAD */
#ifdef @__EPROTO@
	case @__EPROTO@:          result = "Protocol error"; break;
#endif /* __EPROTO */
#ifdef @__EPROTONOSUPPORT@
	case @__EPROTONOSUPPORT@: result = "Protocol not supported"; break;
#endif /* __EPROTONOSUPPORT */
#ifdef @__EPROTOTYPE@
	case @__EPROTOTYPE@:      result = "Protocol wrong type for socket"; break;
#endif /* __EPROTOTYPE */
#ifdef @__ETIME@
	case @__ETIME@:           result = "Timer expired"; break;
#endif /* __ETIME */
#ifdef @__ETIMEDOUT@
	case @__ETIMEDOUT@:       result = "Connection timed out"; break;
#endif /* __ETIMEDOUT */
#ifdef @__ETXTBSY@
	case @__ETXTBSY@:         result = "Text file busy"; break;
#endif /* __ETXTBSY */
#ifdef @__EFTYPE@
	case @__EFTYPE@:          result = "Inappropriate file type or format"; break;
#endif /* __EFTYPE */
#ifdef @__ENMFILE@
	case @__ENMFILE@:         result = "No more files"; break;
#endif /* __ENMFILE */
#ifdef @__EPFNOSUPPORT@
	case @__EPFNOSUPPORT@:    result = "Protocol family not supported"; break;
#endif /* __EPFNOSUPPORT */
#ifdef @__EHOSTDOWN@
	case @__EHOSTDOWN@:       result = "Host is down"; break;
#endif /* __EHOSTDOWN */
#ifdef @__ETOOMANYREFS@
	case @__ETOOMANYREFS@:    result = "Too many references: cannot splice"; break;
#endif /* __ETOOMANYREFS */
#ifdef @__EDQUOT@
	case @__EDQUOT@:          result = "Quota exceeded"; break;
#endif /* __EDQUOT */
#ifdef @__ESTALE@
	case @__ESTALE@:          result = "Stale file handle"; break;
#endif /* __ESTALE */
#ifdef @__ENOSHARE@
	case @__ENOSHARE@:        result = "No such host or network path"; break;
#endif /* __ENOSHARE */
#ifdef @__ECASECLASH@
	case @__ECASECLASH@:      result = "Filename exists with different case"; break;
#endif /* __ECASECLASH */
#ifdef @__ENOTBLK@
	case @__ENOTBLK@:         result = "Block device required"; break;
#endif /* __ENOTBLK */
#ifdef @__ECHRNG@
	case @__ECHRNG@:          result = "Channel number out of range"; break;
#endif /* __ECHRNG */
#ifdef @__EL2NSYNC@
	case @__EL2NSYNC@:        result = "Level 2 not synchronized"; break;
#endif /* __EL2NSYNC */
#ifdef @__EL3HLT@
	case @__EL3HLT@:          result = "Level 3 halted"; break;
#endif /* __EL3HLT */
#ifdef @__EL3RST@
	case @__EL3RST@:          result = "Level 3 reset"; break;
#endif /* __EL3RST */
#ifdef @__ELNRNG@
	case @__ELNRNG@:          result = "Link number out of range"; break;
#endif /* __ELNRNG */
#ifdef @__EUNATCH@
	case @__EUNATCH@:         result = "Protocol driver not attached"; break;
#endif /* __EUNATCH */
#ifdef @__ENOCSI@
	case @__ENOCSI@:          result = "No CSI structure available"; break;
#endif /* __ENOCSI */
#ifdef @__EL2HLT@
	case @__EL2HLT@:          result = "Level 2 halted"; break;
#endif /* __EL2HLT */
#ifdef @__EBADE@
	case @__EBADE@:           result = "Invalid exchange"; break;
#endif /* __EBADE */
#ifdef @__EBADR@
	case @__EBADR@:           result = "Invalid request descriptor"; break;
#endif /* __EBADR */
#ifdef @__EXFULL@
	case @__EXFULL@:          result = "Exchange full"; break;
#endif /* __EXFULL */
#ifdef @__ENOANO@
	case @__ENOANO@:          result = "No anode"; break;
#endif /* __ENOANO */
#ifdef @__EBADRQC@
	case @__EBADRQC@:         result = "Invalid request code"; break;
#endif /* __EBADRQC */
#ifdef @__EBADSLT@
	case @__EBADSLT@:         result = "Invalid slot"; break;
#endif /* __EBADSLT */
#ifdef @__EBFONT@
	case @__EBFONT@:          result = "Bad font file fmt"; break;
#endif /* __EBFONT */
#ifdef @__ENONET@
	case @__ENONET@:          result = "Machine is not on the network"; break;
#endif /* __ENONET */
#ifdef @__ENOPKG@
	case @__ENOPKG@:          result = "Package not installed"; break;
#endif /* __ENOPKG */
#ifdef @__EREMOTE@
	case @__EREMOTE@:         result = "The object is remote"; break;
#endif /* __EREMOTE */
#ifdef @__EADV@
	case @__EADV@:            result = "Advertise error"; break;
#endif /* __EADV */
#ifdef @__ESRMNT@
	case @__ESRMNT@:          result = "Srmount error"; break;
#endif /* __ESRMNT */
#ifdef @__ECOMM@
	case @__ECOMM@:           result = "Communication error on send"; break;
#endif /* __ECOMM */
#ifdef @__ELBIN@
	case @__ELBIN@:           result = "Inode is remote (not really error)"; break;
#endif /* __ELBIN */
#ifdef @__EDOTDOT@
	case @__EDOTDOT@:         result = "Cross mount point (not really error)"; break;
#endif /* __EDOTDOT */
#ifdef @__ENOTUNIQ@
	case @__ENOTUNIQ@:        result = "Given log. name not unique"; break;
#endif /* __ENOTUNIQ */
#ifdef @__EBADFD@
	case @__EBADFD@:          result = "f.d. invalid for this operation"; break;
#endif /* __EBADFD */
#ifdef @__EREMCHG@
	case @__EREMCHG@:         result = "Remote address changed"; break;
#endif /* __EREMCHG */
#ifdef @__ELIBACC@
	case @__ELIBACC@:         result = "Can't access a needed shared lib"; break;
#endif /* __ELIBACC */
#ifdef @__ELIBBAD@
	case @__ELIBBAD@:         result = "Accessing a corrupted shared lib"; break;
#endif /* __ELIBBAD */
#ifdef @__ELIBSCN@
	case @__ELIBSCN@:         result = ".lib section in a.out corrupted"; break;
#endif /* __ELIBSCN */
#ifdef @__ELIBMAX@
	case @__ELIBMAX@:         result = "Attempting to link in too many libs"; break;
#endif /* __ELIBMAX */
#ifdef @__ELIBEXEC@
	case @__ELIBEXEC@:        result = "Attempting to exec a shared library"; break;
#endif /* __ELIBEXEC */
#ifdef @__ESHUTDOWN@
	case @__ESHUTDOWN@:       result = "Can't send after socket shutdown"; break;
#endif /* __ESHUTDOWN */
#ifdef @__ESOCKTNOSUPPORT@
	case @__ESOCKTNOSUPPORT@: result = "Socket type not supported"; break;
#endif /* __ESOCKTNOSUPPORT */
#ifdef @__EPROCLIM@
	case @__EPROCLIM@:        result = "Process limit reached"; break;
#endif /* __EPROCLIM */
#ifdef @__EUSERS@
	case @__EUSERS@:          result = "Too many users"; break;
#endif /* __EUSERS */
#ifdef @__ENOMEDIUM@
	case @__ENOMEDIUM@:       result = "No medium (in tape drive)"; break;
#endif /* __ENOMEDIUM */
#ifdef @__ESTRPIPE@
	case @__ESTRPIPE@:        result = "Streams pipe error"; break;
#endif /* __ESTRPIPE */
#ifdef @__EMULTIHOP@
	case @__EMULTIHOP@:       result = "Multihop attempted"; break;
#endif /* __EMULTIHOP */
#ifdef @__ERESTART@
	case @__ERESTART@:        result = "Interrupted system call should be restarted"; break;
#endif /* __ERESTART */
#ifdef @__EUCLEAN@
	case @__EUCLEAN@:         result = "Structure needs cleaning"; break;
#endif /* __EUCLEAN */
#ifdef @__ENOTNAM@
	case @__ENOTNAM@:         result = "Not a XENIX named type file"; break;
#endif /* __ENOTNAM */
#ifdef @__ENAVAIL@
	case @__ENAVAIL@:         result = "No XENIX semaphores available"; break;
#endif /* __ENAVAIL */
#ifdef @__EISNAM@
	case @__EISNAM@:          result = "Is a named type file"; break;
#endif /* __EISNAM */
#ifdef @__EREMOTEIO@
	case @__EREMOTEIO@:       result = "Remote I/O error"; break;
#endif /* __EREMOTEIO */
#ifdef @__EMEDIUMTYPE@
	case @__EMEDIUMTYPE@:     result = "Wrong medium type"; break;
#endif /* __EMEDIUMTYPE */
#ifdef @__ENOKEY@
	case @__ENOKEY@:          result = "Required key not available"; break;
#endif /* __ENOKEY */
#ifdef @__EKEYEXPIRED@
	case @__EKEYEXPIRED@:     result = "Key has expired"; break;
#endif /* __EKEYEXPIRED */
#ifdef @__EKEYREVOKED@
	case @__EKEYREVOKED@:     result = "Key has been revoked"; break;
#endif /* __EKEYREVOKED */
#ifdef @__EKEYREJECTED@
	case @__EKEYREJECTED@:    result = "Key was rejected by service"; break;
#endif /* __EKEYREJECTED */
#ifdef @__ERFKILL@
	case @__ERFKILL@:         result = "Operation not possible due to RF-kill"; break;
#endif /* __ERFKILL */
#ifdef @__EHWPOISON@
	case @__EHWPOISON@:       result = "Memory page has hardware error"; break;
#endif /* __EHWPOISON */
#if defined(@__STRUNCATE@) && (!defined(@__ERANGE@) || @__STRUNCATE@ != @__ERANGE@)
	case @__STRUNCATE@:       result = "Truncated"; break;
#endif /* __STRUNCATE && (!__ERANGE || __STRUNCATE != __ERANGE) */
#if defined(@__EWOULDBLOCK@) && (!defined(@__EAGAIN@) || @__EWOULDBLOCK@ != @__EAGAIN@)
	case @__EWOULDBLOCK@:     result = "Operation would block"; break;
#endif /* __EWOULDBLOCK && (!__EAGAIN || __EWOULDBLOCK != __EAGAIN) */
#if defined(@__EDEADLK@) && (!defined(@__EDEADLOCK@) || @__EDEADLOCK@ != @__EDEADLK@)
	case @__EDEADLK@:         result = "Resource deadlock would occur"; break;
#endif /* __EDEADLK && (!__EDEADLOCK || __EDEADLOCK != __EDEADLK) */

	default:
		result = NULL;
		break;
	}
	return result;
#endif
}

[ATTR_WUNUSED][ATTR_CONST][nothrow][section(.text.crt.errno)]
[dependency_include(<parts/errno.h>)][user][noexport]
strerrorname_s:(int errnum) -> char const * {
	char const *result;
	switch (errnum) {

#ifdef @__EPERM@
	case @__EPERM@:           result = "EPERM"; break;
#endif /* __EPERM */
#ifdef @__ENOENT@
	case @__ENOENT@:          result = "ENOENT"; break;
#endif /* __ENOENT */
#ifdef @__ESRCH@
	case @__ESRCH@:           result = "ESRCH"; break;
#endif /* __ESRCH */
#ifdef @__EINTR@
	case @__EINTR@:           result = "EINTR"; break;
#endif /* __EINTR */
#ifdef @__EIO@
	case @__EIO@:             result = "EIO"; break;
#endif /* __EIO */
#ifdef @__ENXIO@
	case @__ENXIO@:           result = "ENXIO"; break;
#endif /* __ENXIO */
#ifdef @__E2BIG@
	case @__E2BIG@:           result = "E2BIG"; break;
#endif /* __E2BIG */
#ifdef @__ENOEXEC@
	case @__ENOEXEC@:         result = "ENOEXEC"; break;
#endif /* __ENOEXEC */
#ifdef @__EBADF@
	case @__EBADF@:           result = "EBADF"; break;
#endif /* __EBADF */
#ifdef @__ECHILD@
	case @__ECHILD@:          result = "ECHILD"; break;
#endif /* __ECHILD */
#ifdef @__EAGAIN@
	case @__EAGAIN@:          result = "EAGAIN"; break;
#endif /* __EAGAIN */
#ifdef @__ENOMEM@
	case @__ENOMEM@:          result = "ENOMEM"; break;
#endif /* __ENOMEM */
#ifdef @__EACCES@
	case @__EACCES@:          result = "EACCES"; break;
#endif /* __EACCES */
#ifdef @__EFAULT@
	case @__EFAULT@:          result = "EFAULT"; break;
#endif /* __EFAULT */
#ifdef @__EBUSY@
	case @__EBUSY@:           result = "EBUSY"; break;
#endif /* __EBUSY */
#ifdef @__EEXIST@
	case @__EEXIST@:          result = "EEXIST"; break;
#endif /* __EEXIST */
#ifdef @__EXDEV@
	case @__EXDEV@:           result = "EXDEV"; break;
#endif /* __EXDEV */
#ifdef @__ENODEV@
	case @__ENODEV@:          result = "ENODEV"; break;
#endif /* __ENODEV */
#ifdef @__ENOTDIR@
	case @__ENOTDIR@:         result = "ENOTDIR"; break;
#endif /* __ENOTDIR */
#ifdef @__EISDIR@
	case @__EISDIR@:          result = "EISDIR"; break;
#endif /* __EISDIR */
#ifdef @__ENFILE@
	case @__ENFILE@:          result = "ENFILE"; break;
#endif /* __ENFILE */
#ifdef @__EMFILE@
	case @__EMFILE@:          result = "EMFILE"; break;
#endif /* __EMFILE */
#ifdef @__ENOTTY@
	case @__ENOTTY@:          result = "ENOTTY"; break;
#endif /* __ENOTTY */
#ifdef @__EFBIG@
	case @__EFBIG@:           result = "EFBIG"; break;
#endif /* __EFBIG */
#ifdef @__ENOSPC@
	case @__ENOSPC@:          result = "ENOSPC"; break;
#endif /* __ENOSPC */
#ifdef @__ESPIPE@
	case @__ESPIPE@:          result = "ESPIPE"; break;
#endif /* __ESPIPE */
#ifdef @__EROFS@
	case @__EROFS@:           result = "EROFS"; break;
#endif /* __EROFS */
#ifdef @__EMLINK@
	case @__EMLINK@:          result = "EMLINK"; break;
#endif /* __EMLINK */
#ifdef @__EPIPE@
	case @__EPIPE@:           result = "EPIPE"; break;
#endif /* __EPIPE */
#ifdef @__EDOM@
	case @__EDOM@:            result = "EDOM"; break;
#endif /* __EDOM */
#ifdef @__ENAMETOOLONG@
	case @__ENAMETOOLONG@:    result = "ENAMETOOLONG"; break;
#endif /* __ENAMETOOLONG */
#ifdef @__ENOLCK@
	case @__ENOLCK@:          result = "ENOLCK"; break;
#endif /* __ENOLCK */
#ifdef @__ENOSYS@
	case @__ENOSYS@:          result = "ENOSYS"; break;
#endif /* __ENOSYS */
#ifdef @__ENOTEMPTY@
	case @__ENOTEMPTY@:       result = "ENOTEMPTY"; break;
#endif /* __ENOTEMPTY */
#ifdef @__EINVAL@
	case @__EINVAL@:          result = "EINVAL"; break;
#endif /* __EINVAL */
#ifdef @__ERANGE@
	case @__ERANGE@:          result = "ERANGE"; break;
#endif /* __ERANGE */
#ifdef @__EILSEQ@
	case @__EILSEQ@:          result = "EILSEQ"; break;
#endif /* __EILSEQ */
#ifdef @__EDEADLOCK@
	case @__EDEADLOCK@:       result = "EDEADLOCK"; break;
#endif /* __EDEADLOCK */
#ifdef @__EADDRINUSE@
	case @__EADDRINUSE@:      result = "EADDRINUSE"; break;
#endif /* __EADDRINUSE */
#ifdef @__EADDRNOTAVAIL@
	case @__EADDRNOTAVAIL@:   result = "EADDRNOTAVAIL"; break;
#endif /* __EADDRNOTAVAIL */
#ifdef @__EAFNOSUPPORT@
	case @__EAFNOSUPPORT@:    result = "EAFNOSUPPORT"; break;
#endif /* __EAFNOSUPPORT */
#ifdef @__EALREADY@
	case @__EALREADY@:        result = "EALREADY"; break;
#endif /* __EALREADY */
#ifdef @__EBADMSG@
	case @__EBADMSG@:         result = "EBADMSG"; break;
#endif /* __EBADMSG */
#ifdef @__ECANCELED@
	case @__ECANCELED@:       result = "ECANCELED"; break;
#endif /* __ECANCELED */
#ifdef @__ECONNABORTED@
	case @__ECONNABORTED@:    result = "ECONNABORTED"; break;
#endif /* __ECONNABORTED */
#ifdef @__ECONNREFUSED@
	case @__ECONNREFUSED@:    result = "ECONNREFUSED"; break;
#endif /* __ECONNREFUSED */
#ifdef @__ECONNRESET@
	case @__ECONNRESET@:      result = "ECONNRESET"; break;
#endif /* __ECONNRESET */
#ifdef @__EDESTADDRREQ@
	case @__EDESTADDRREQ@:    result = "EDESTADDRREQ"; break;
#endif /* __EDESTADDRREQ */
#ifdef @__EHOSTUNREACH@
	case @__EHOSTUNREACH@:    result = "EHOSTUNREACH"; break;
#endif /* __EHOSTUNREACH */
#ifdef @__EIDRM@
	case @__EIDRM@:           result = "EIDRM"; break;
#endif /* __EIDRM */
#ifdef @__EINPROGRESS@
	case @__EINPROGRESS@:     result = "EINPROGRESS"; break;
#endif /* __EINPROGRESS */
#ifdef @__EISCONN@
	case @__EISCONN@:         result = "EISCONN"; break;
#endif /* __EISCONN */
#ifdef @__ELOOP@
	case @__ELOOP@:           result = "ELOOP"; break;
#endif /* __ELOOP */
#ifdef @__EMSGSIZE@
	case @__EMSGSIZE@:        result = "EMSGSIZE"; break;
#endif /* __EMSGSIZE */
#ifdef @__ENETDOWN@
	case @__ENETDOWN@:        result = "ENETDOWN"; break;
#endif /* __ENETDOWN */
#ifdef @__ENETRESET@
	case @__ENETRESET@:       result = "ENETRESET"; break;
#endif /* __ENETRESET */
#ifdef @__ENETUNREACH@
	case @__ENETUNREACH@:     result = "ENETUNREACH"; break;
#endif /* __ENETUNREACH */
#ifdef @__ENOBUFS@
	case @__ENOBUFS@:         result = "ENOBUFS"; break;
#endif /* __ENOBUFS */
#ifdef @__ENODATA@
	case @__ENODATA@:         result = "ENODATA"; break;
#endif /* __ENODATA */
#ifdef @__ENOLINK@
	case @__ENOLINK@:         result = "ENOLINK"; break;
#endif /* __ENOLINK */
#ifdef @__ENOMSG@
	case @__ENOMSG@:          result = "ENOMSG"; break;
#endif /* __ENOMSG */
#ifdef @__ENOPROTOOPT@
	case @__ENOPROTOOPT@:     result = "ENOPROTOOPT"; break;
#endif /* __ENOPROTOOPT */
#ifdef @__ENOSR@
	case @__ENOSR@:           result = "ENOSR"; break;
#endif /* __ENOSR */
#ifdef @__ENOSTR@
	case @__ENOSTR@:          result = "ENOSTR"; break;
#endif /* __ENOSTR */
#ifdef @__ENOTCONN@
	case @__ENOTCONN@:        result = "ENOTCONN"; break;
#endif /* __ENOTCONN */
#ifdef @__ENOTRECOVERABLE@
	case @__ENOTRECOVERABLE@: result = "ENOTRECOVERABLE"; break;
#endif /* __ENOTRECOVERABLE */
#ifdef @__ENOTSOCK@
	case @__ENOTSOCK@:        result = "ENOTSOCK"; break;
#endif /* __ENOTSOCK */
#ifdef @__ENOTSUP@
	case @__ENOTSUP@:         result = "ENOTSUP"; break;
#endif /* __ENOTSUP */
#ifdef @__EOPNOTSUPP@
	case @__EOPNOTSUPP@:      result = "EOPNOTSUPP"; break;
#endif /* __EOPNOTSUPP */
#ifdef @__EOTHER@
	case @__EOTHER@:          result = "EOTHER"; break;
#endif /* __EOTHER */
#ifdef @__EOVERFLOW@
	case @__EOVERFLOW@:       result = "EOVERFLOW"; break;
#endif /* __EOVERFLOW */
#ifdef @__EOWNERDEAD@
	case @__EOWNERDEAD@:      result = "EOWNERDEAD"; break;
#endif /* __EOWNERDEAD */
#ifdef @__EPROTO@
	case @__EPROTO@:          result = "EPROTO"; break;
#endif /* __EPROTO */
#ifdef @__EPROTONOSUPPORT@
	case @__EPROTONOSUPPORT@: result = "EPROTONOSUPPORT"; break;
#endif /* __EPROTONOSUPPORT */
#ifdef @__EPROTOTYPE@
	case @__EPROTOTYPE@:      result = "EPROTOTYPE"; break;
#endif /* __EPROTOTYPE */
#ifdef @__ETIME@
	case @__ETIME@:           result = "ETIME"; break;
#endif /* __ETIME */
#ifdef @__ETIMEDOUT@
	case @__ETIMEDOUT@:       result = "ETIMEDOUT"; break;
#endif /* __ETIMEDOUT */
#ifdef @__ETXTBSY@
	case @__ETXTBSY@:         result = "ETXTBSY"; break;
#endif /* __ETXTBSY */
#ifdef @__EFTYPE@
	case @__EFTYPE@:          result = "EFTYPE"; break;
#endif /* __EFTYPE */
#ifdef @__ENMFILE@
	case @__ENMFILE@:         result = "ENMFILE"; break;
#endif /* __ENMFILE */
#ifdef @__EPFNOSUPPORT@
	case @__EPFNOSUPPORT@:    result = "EPFNOSUPPORT"; break;
#endif /* __EPFNOSUPPORT */
#ifdef @__EHOSTDOWN@
	case @__EHOSTDOWN@:       result = "EHOSTDOWN"; break;
#endif /* __EHOSTDOWN */
#ifdef @__ETOOMANYREFS@
	case @__ETOOMANYREFS@:    result = "ETOOMANYREFS"; break;
#endif /* __ETOOMANYREFS */
#ifdef @__EDQUOT@
	case @__EDQUOT@:          result = "EDQUOT"; break;
#endif /* __EDQUOT */
#ifdef @__ESTALE@
	case @__ESTALE@:          result = "ESTALE"; break;
#endif /* __ESTALE */
#ifdef @__ENOSHARE@
	case @__ENOSHARE@:        result = "ENOSHARE"; break;
#endif /* __ENOSHARE */
#ifdef @__ECASECLASH@
	case @__ECASECLASH@:      result = "ECASECLASH"; break;
#endif /* __ECASECLASH */
#ifdef @__ENOTBLK@
	case @__ENOTBLK@:         result = "ENOTBLK"; break;
#endif /* __ENOTBLK */
#ifdef @__ECHRNG@
	case @__ECHRNG@:          result = "ECHRNG"; break;
#endif /* __ECHRNG */
#ifdef @__EL2NSYNC@
	case @__EL2NSYNC@:        result = "EL2NSYNC"; break;
#endif /* __EL2NSYNC */
#ifdef @__EL3HLT@
	case @__EL3HLT@:          result = "EL3HLT"; break;
#endif /* __EL3HLT */
#ifdef @__EL3RST@
	case @__EL3RST@:          result = "EL3RST"; break;
#endif /* __EL3RST */
#ifdef @__ELNRNG@
	case @__ELNRNG@:          result = "ELNRNG"; break;
#endif /* __ELNRNG */
#ifdef @__EUNATCH@
	case @__EUNATCH@:         result = "EUNATCH"; break;
#endif /* __EUNATCH */
#ifdef @__ENOCSI@
	case @__ENOCSI@:          result = "ENOCSI"; break;
#endif /* __ENOCSI */
#ifdef @__EL2HLT@
	case @__EL2HLT@:          result = "EL2HLT"; break;
#endif /* __EL2HLT */
#ifdef @__EBADE@
	case @__EBADE@:           result = "EBADE"; break;
#endif /* __EBADE */
#ifdef @__EBADR@
	case @__EBADR@:           result = "EBADR"; break;
#endif /* __EBADR */
#ifdef @__EXFULL@
	case @__EXFULL@:          result = "EXFULL"; break;
#endif /* __EXFULL */
#ifdef @__ENOANO@
	case @__ENOANO@:          result = "ENOANO"; break;
#endif /* __ENOANO */
#ifdef @__EBADRQC@
	case @__EBADRQC@:         result = "EBADRQC"; break;
#endif /* __EBADRQC */
#ifdef @__EBADSLT@
	case @__EBADSLT@:         result = "EBADSLT"; break;
#endif /* __EBADSLT */
#ifdef @__EBFONT@
	case @__EBFONT@:          result = "EBFONT"; break;
#endif /* __EBFONT */
#ifdef @__ENONET@
	case @__ENONET@:          result = "ENONET"; break;
#endif /* __ENONET */
#ifdef @__ENOPKG@
	case @__ENOPKG@:          result = "ENOPKG"; break;
#endif /* __ENOPKG */
#ifdef @__EREMOTE@
	case @__EREMOTE@:         result = "EREMOTE"; break;
#endif /* __EREMOTE */
#ifdef @__EADV@
	case @__EADV@:            result = "EADV"; break;
#endif /* __EADV */
#ifdef @__ESRMNT@
	case @__ESRMNT@:          result = "ESRMNT"; break;
#endif /* __ESRMNT */
#ifdef @__ECOMM@
	case @__ECOMM@:           result = "ECOMM"; break;
#endif /* __ECOMM */
#ifdef @__ELBIN@
	case @__ELBIN@:           result = "ELBIN)"; break;
#endif /* __ELBIN */
#ifdef @__EDOTDOT@
	case @__EDOTDOT@:         result = "EDOTDOT)"; break;
#endif /* __EDOTDOT */
#ifdef @__ENOTUNIQ@
	case @__ENOTUNIQ@:        result = "ENOTUNIQ"; break;
#endif /* __ENOTUNIQ */
#ifdef @__EBADFD@
	case @__EBADFD@:          result = "EBADFD"; break;
#endif /* __EBADFD */
#ifdef @__EREMCHG@
	case @__EREMCHG@:         result = "EREMCHG"; break;
#endif /* __EREMCHG */
#ifdef @__ELIBACC@
	case @__ELIBACC@:         result = "ELIBACC"; break;
#endif /* __ELIBACC */
#ifdef @__ELIBBAD@
	case @__ELIBBAD@:         result = "ELIBBAD"; break;
#endif /* __ELIBBAD */
#ifdef @__ELIBSCN@
	case @__ELIBSCN@:         result = "ELIBSCN"; break;
#endif /* __ELIBSCN */
#ifdef @__ELIBMAX@
	case @__ELIBMAX@:         result = "ELIBMAX"; break;
#endif /* __ELIBMAX */
#ifdef @__ELIBEXEC@
	case @__ELIBEXEC@:        result = "ELIBEXEC"; break;
#endif /* __ELIBEXEC */
#ifdef @__ESHUTDOWN@
	case @__ESHUTDOWN@:       result = "ESHUTDOWN"; break;
#endif /* __ESHUTDOWN */
#ifdef @__ESOCKTNOSUPPORT@
	case @__ESOCKTNOSUPPORT@: result = "ESOCKTNOSUPPORT"; break;
#endif /* __ESOCKTNOSUPPORT */
#ifdef @__EPROCLIM@
	case @__EPROCLIM@:        result = "EPROCLIM"; break;
#endif /* __EPROCLIM */
#ifdef @__EUSERS@
	case @__EUSERS@:          result = "EUSERS"; break;
#endif /* __EUSERS */
#ifdef @__ENOMEDIUM@
	case @__ENOMEDIUM@:       result = "ENOMEDIUM)"; break;
#endif /* __ENOMEDIUM */
#ifdef @__ESTRPIPE@
	case @__ESTRPIPE@:        result = "ESTRPIPE"; break;
#endif /* __ESTRPIPE */
#ifdef @__EMULTIHOP@
	case @__EMULTIHOP@:       result = "EMULTIHOP"; break;
#endif /* __EMULTIHOP */
#ifdef @__ERESTART@
	case @__ERESTART@:        result = "ERESTART"; break;
#endif /* __ERESTART */
#ifdef @__EUCLEAN@
	case @__EUCLEAN@:         result = "EUCLEAN"; break;
#endif /* __EUCLEAN */
#ifdef @__ENOTNAM@
	case @__ENOTNAM@:         result = "ENOTNAM"; break;
#endif /* __ENOTNAM */
#ifdef @__ENAVAIL@
	case @__ENAVAIL@:         result = "ENAVAIL"; break;
#endif /* __ENAVAIL */
#ifdef @__EISNAM@
	case @__EISNAM@:          result = "EISNAM"; break;
#endif /* __EISNAM */
#ifdef @__EREMOTEIO@
	case @__EREMOTEIO@:       result = "EREMOTEIO"; break;
#endif /* __EREMOTEIO */
#ifdef @__EMEDIUMTYPE@
	case @__EMEDIUMTYPE@:     result = "EMEDIUMTYPE"; break;
#endif /* __EMEDIUMTYPE */
#ifdef @__ENOKEY@
	case @__ENOKEY@:          result = "ENOKEY"; break;
#endif /* __ENOKEY */
#ifdef @__EKEYEXPIRED@
	case @__EKEYEXPIRED@:     result = "EKEYEXPIRED"; break;
#endif /* __EKEYEXPIRED */
#ifdef @__EKEYREVOKED@
	case @__EKEYREVOKED@:     result = "EKEYREVOKED"; break;
#endif /* __EKEYREVOKED */
#ifdef @__EKEYREJECTED@
	case @__EKEYREJECTED@:    result = "EKEYREJECTED"; break;
#endif /* __EKEYREJECTED */
#ifdef @__ERFKILL@
	case @__ERFKILL@:         result = "ERFKILL"; break;
#endif /* __ERFKILL */
#ifdef @__EHWPOISON@
	case @__EHWPOISON@:       result = "EHWPOISON"; break;
#endif /* __EHWPOISON */
#if defined(@__STRUNCATE@) && (!defined(@__ERANGE@) || @__STRUNCATE@ != @__ERANGE@)
	case @__STRUNCATE@:       result = "STRUNCATE"; break;
#endif /* __STRUNCATE && (!__ERANGE || __STRUNCATE != __ERANGE) */
#if defined(@__EWOULDBLOCK@) && (!defined(@__EAGAIN@) || @__EWOULDBLOCK@ != @__EAGAIN@)
	case @__EWOULDBLOCK@:     result = "EWOULDBLOCK"; break;
#endif /* __EWOULDBLOCK && (!__EAGAIN || __EWOULDBLOCK != __EAGAIN) */
#if defined(@__EDEADLK@) && (!defined(@__EDEADLOCK@) || @__EDEADLOCK@ != @__EDEADLK@)
	case @__EDEADLK@:         result = "EDEADLK"; break;
#endif /* __EDEADLK && (!__EDEADLOCK || __EDEADLOCK != __EDEADLK) */

	default:
		result = NULL;
		break;
	}
	return result;
}

[ATTR_WUNUSED][ATTR_CONST][nothrow][section(.text.crt.errno)]
[dependency_include(<bits/signum.h>)][user][noexport]
[impl_prefix(
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
)][dependency_include(<bits/signum-values.h>)]
strsignal_s:(int signum) -> char const * {
#if defined(__CRT_HAVE___p_sys_siglist) || defined(__CRT_HAVE_sys_siglist) || defined(__CRT_HAVE__sys_siglist)
	return (unsigned int)errnum < _NSIG ? @_sys_siglist@[signum] : NULL;
#else /* __CRT_HAVE___p_sys_siglist || __CRT_HAVE_sys_siglist || __CRT_HAVE__sys_siglist */
	char const *result;
	switch (signum) {

#ifdef @__SIGABRT_COMPAT@
	case @__SIGABRT_COMPAT@ : result = "SIGABRT_COMPAT"; break;
#endif /* __SIGABRT_COMPAT */
#ifdef @__SIGBREAK@
	case @__SIGBREAK@ : result = "SIGBREAK"; break;
#endif /* __SIGBREAK */
#ifdef @__SIGHUP@
	case @__SIGHUP@   : result = "SIGHUP"; break;
#endif /* __SIGHUP */
#ifdef @__SIGINT@
	case @__SIGINT@   : result = "SIGINT"; break;
#endif /* __SIGINT */
#ifdef @__SIGQUIT@
	case @__SIGQUIT@  : result = "SIGQUIT"; break;
#endif /* __SIGQUIT */
#ifdef @__SIGILL@
	case @__SIGILL@   : result = "SIGILL"; break;
#endif /* __SIGILL */
#ifdef @__SIGTRAP@
	case @__SIGTRAP@  : result = "SIGTRAP"; break;
#endif /* __SIGTRAP */
#ifdef @__SIGABRT@
	case @__SIGABRT@  : result = "SIGABRT"; break;
#endif /* __SIGABRT */
#ifdef @__SIGBUS@
	case @__SIGBUS@   : result = "SIGBUS"; break;
#endif /* __SIGBUS */
#ifdef @__SIGFPE@
	case @__SIGFPE@   : result = "SIGFPE"; break;
#endif /* __SIGFPE */
#ifdef @__SIGKILL@
	case @__SIGKILL@  : result = "SIGKILL"; break;
#endif /* __SIGKILL */
#ifdef @__SIGUSR1@
	case @__SIGUSR1@  : result = "SIGUSR1"; break;
#endif /* __SIGUSR1 */
#ifdef @__SIGSEGV@
	case @__SIGSEGV@  : result = "SIGSEGV"; break;
#endif /* __SIGSEGV */
#ifdef @__SIGUSR2@
	case @__SIGUSR2@  : result = "SIGUSR2"; break;
#endif /* __SIGUSR2 */
#ifdef @__SIGPIPE@
	case @__SIGPIPE@  : result = "SIGPIPE"; break;
#endif /* __SIGPIPE */
#ifdef @__SIGALRM@
	case @__SIGALRM@  : result = "SIGALRM"; break;
#endif /* __SIGALRM */
#ifdef @__SIGTERM@
	case @__SIGTERM@  : result = "SIGTERM"; break;
#endif /* __SIGTERM */
#ifdef @__SIGSTKFLT@
	case @__SIGSTKFLT@: result = "SIGSTKFLT"; break;
#endif /* __SIGSTKFLT */
#ifdef @__SIGCHLD@
	case @__SIGCHLD@  : result = "SIGCHLD"; break;
#endif /* __SIGCHLD */
#ifdef @__SIGCONT@
	case @__SIGCONT@  : result = "SIGCONT"; break;
#endif /* __SIGCONT */
#ifdef @__SIGSTOP@
	case @__SIGSTOP@  : result = "SIGSTOP"; break;
#endif /* __SIGSTOP */
#ifdef @__SIGTSTP@
	case @__SIGTSTP@  : result = "SIGTSTP"; break;
#endif /* __SIGTSTP */
#ifdef @__SIGTTIN@
	case @__SIGTTIN@  : result = "SIGTTIN"; break;
#endif /* __SIGTTIN */
#ifdef @__SIGTTOU@
	case @__SIGTTOU@  : result = "SIGTTOU"; break;
#endif /* __SIGTTOU */
#ifdef @__SIGURG@
	case @__SIGURG@   : result = "SIGURG"; break;
#endif /* __SIGURG */
#ifdef @__SIGXCPU@
	case @__SIGXCPU@  : result = "SIGXCPU"; break;
#endif /* __SIGXCPU */
#ifdef @__SIGXFSZ@
	case @__SIGXFSZ@  : result = "SIGXFSZ"; break;
#endif /* __SIGXFSZ */
#ifdef @__SIGVTALRM@
	case @__SIGVTALRM@: result = "SIGVTALRM"; break;
#endif /* __SIGVTALRM */
#ifdef @__SIGPROF@
	case @__SIGPROF@  : result = "SIGPROF"; break;
#endif /* __SIGPROF */
#ifdef @__SIGWINCH@
	case @__SIGWINCH@ : result = "SIGWINCH"; break;
#endif /* __SIGWINCH */
#ifdef @__SIGIO@
	case @__SIGIO@    : result = "SIGIO"; break;
#endif /* __SIGIO */
#ifdef @__SIGSYS@
	case @__SIGSYS@   : result = "SIGSYS"; break;
#endif /* __SIGSYS */
#ifdef @__SIGEMT@
	case @__SIGEMT@   : result = "SIGEMT"; break;
#endif /* __SIGEMT */
#ifdef @__SIGLOST@
	case @__SIGLOST@  : result = "SIGLOST"; break;
#endif /* __SIGLOST */
#if defined(@__SIGCLD@) && (!defined(@__SIGCHLD@) || @__SIGCLD@ != @__SIGCHLD@)
	case @__SIGCLD@   : result = "SIGCLD"; break;
#endif /* __SIGCLD && (!__SIGCHLD || __SIGCLD != __SIGCHLD) */
#if defined(@__SIGIOT@) && (!defined(@__SIGABRT@) || @__SIGIOT@ != @__SIGABRT@)
	case @__SIGIOT@   : result = "SIGIOT"; break;
#endif /* __SIGIOT && (!__SIGABRT || __SIGIOT != __SIGABRT) */
#if defined(@__SIGPOLL@) && (!defined(@__SIGIO@) || @__SIGPOLL@ != @__SIGIO@)
	case @__SIGPOLL@   : result = "SIGPOLL"; break;
#endif /* __SIGPOLL && (!__SIGIO || __SIGPOLL != __SIGIO) */
#if defined(@__SIGPWR@) && (!defined(@__SIGLOST@) || @__SIGPWR@ != @__SIGLOST@)
	case @__SIGPWR@   : result = "SIGPWR"; break;
#endif /* __SIGPWR && (!__SIGLOST || __SIGPWR != __SIGLOST) */

	default:
		result = NULL;
		break;
	}
	return result;
#endif /* !__CRT_HAVE___p_sys_siglist && !__CRT_HAVE_sys_siglist && !__CRT_HAVE__sys_siglist */
}



[doc_alias(strdupf)]
[same_impl][requires($has_function(vasprintf))][ATTR_WUNUSED]
[ATTR_MALL_DEFAULT_ALIGNED][ATTR_MALLOC][ATTR_LIBC_PRINTF(1, 0)]
[section(.text.crt.heap.strdup)]
vstrdupf:(char const *__restrict format, $va_list args) -> char * {
	char *result;
	return vasprintf(&result, format, args) >= 0 ? result : 0;
}

@@Print the given `FORMAT' into a newly allocated, heap-allocated string
[ATTR_WUNUSED][ATTR_MALL_DEFAULT_ALIGNED]
[ATTR_MALLOC][ATTR_LIBC_PRINTF(1, 0)]
[section(.text.crt.heap.strdup)]
strdupf:(char const *__restrict format, ...) -> char *
%{
	auto_block(printf(vstrdupf))
}

/* TODO: strdupaf() */
/* TODO: vstrdupaf() */



[ATTR_WUNUSED][ATTR_PURE]
wildstrcmp:([nonnull] char const *pattern,
            [nonnull] char const *string) -> int {
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

[ATTR_WUNUSED][section(.text.crt.unicode.static.memory)]
wildstrcasecmp:([nonnull] char const *pattern,
                [nonnull] char const *string) -> int {
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

[ATTR_WUNUSED][dependency_include(<parts/malloca.h>)]
[same_impl][requires($has_function(fuzzy_memcmp))][export]
fuzzy_strcmp:([nonnull] char const *s1, [nonnull] char const *s2) -> $size_t {
	return fuzzy_memcmp(s1, strlen(s1), s2, strlen(s2));
}

[ATTR_WUNUSED][dependency_include(<parts/malloca.h>)]
[same_impl][requires($has_function(fuzzy_memcmp))][export]
fuzzy_strncmp:([nonnull] char const *s1, $size_t s1_maxlen,
               [nonnull] char const *s2, $size_t s2_maxlen) -> $size_t {
	return fuzzy_memcmp(s1, strnlen(s1, s1_maxlen), s2, strnlen(s2, s2_maxlen));
}

[dependency_include(<parts/malloca.h>)][ATTR_WUNUSED]
[same_impl][requires($has_function(fuzzy_memcasecmp))][export]
[section(.text.crt.unicode.static.memory)]
fuzzy_strcasecmp:([nonnull] char const *s1, [nonnull] char const *s2) -> $size_t {
	return fuzzy_memcasecmp(s1, strlen(s1), s2, strlen(s2));
}

[dependency_include(<parts/malloca.h>)][ATTR_WUNUSED]
[same_impl][requires($has_function(fuzzy_memcasecmp))][export]
[section(.text.crt.unicode.static.memory)]
fuzzy_strncasecmp:([nonnull] char const *s1, $size_t s1_maxlen,
                   [nonnull] char const *s2, $size_t s2_maxlen) -> $size_t {
	return fuzzy_memcasecmp(s1, strnlen(s1, s1_maxlen), s2, strnlen(s2, s2_maxlen));
}

[dependency_include(<parts/malloca.h>)][ATTR_WUNUSED]
[same_impl][requires(!defined(__NO_MALLOCA))][export]
fuzzy_memcmp:([nonnull] void const *s1, $size_t s1_bytes,
              [nonnull] void const *s2, $size_t s2_bytes) -> $size_t {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{ void const *temp = s1; s1 = s2; s2 = temp; }
		{ size_t temp = s1_bytes; s1_bytes = s2_bytes; s2_bytes = temp; }
	}
	__malloca_tryhard(v0, (s2_bytes+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0)
		return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_bytes+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_bytes; ++i)
		v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i+1;
		for (j = 0; j < s2_bytes; j++) {
			cost  = ((byte_t *)s1)[i] != ((byte_t *)s2)[j];
			cost += v0[j];
			temp  = v1[j]+1;
			if (cost > temp) cost = temp;
			temp  = v0[j+1]+1;
			if (cost > temp) cost = temp;
			v1[j+1] = cost;
		}
#if __SIZEOF_SIZE_T__ == 8
		memcpyq((u64 *)v0, (u64 *)v1, s2_bytes);
#elif __SIZEOF_SIZE_T__ == 4
		memcpyl((u32 *)v0, (u32 *)v1, s2_bytes);
#elif __SIZEOF_SIZE_T__ == 2
		memcpyw((u16 *)v0, (u16 *)v1, s2_bytes);
#else
		memcpy((u8 *)v0, (u8 *)v1, s2_bytes*sizeof(size_t));
#endif
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}

[dependency_include(<parts/malloca.h>)][ATTR_WUNUSED]
[same_impl][requires(!defined(__NO_MALLOCA))][export]
[section(.text.crt.unicode.static.memory)]
fuzzy_memcasecmp:([nonnull] void const *s1, $size_t s1_bytes,
                  [nonnull] void const *s2, $size_t s2_bytes) -> $size_t {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{ @@yield $wchar_function ? "wchar_t" : "void"@@ const *temp = s1; s1 = s2; s2 = temp; }
		{ size_t temp = s1_bytes; s1_bytes = s2_bytes; s2_bytes = temp; }
	}
	__malloca_tryhard(v0, (s2_bytes+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0)
		return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_bytes+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_bytes; ++i)
		v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i+1;
		for (j = 0; j < s2_bytes; j++) {
			byte_t c1 = ((byte_t *)s1)[i];
			byte_t c2 = ((byte_t *)s2)[j];
			cost  = c1 != c2 && tolower(c1) != tolower(c2);
			cost += v0[j];
			temp  = v1[j]+1;
			if (cost > temp) cost = temp;
			temp  = v0[j+1]+1;
			if (cost > temp) cost = temp;
			v1[j+1] = cost;
		}
#if __SIZEOF_SIZE_T__ == 8
		memcpyq((u64 *)v0, (u64 *)v1, s2_bytes);
#elif __SIZEOF_SIZE_T__ == 4
		memcpyl((u32 *)v0, (u32 *)v1, s2_bytes);
#elif __SIZEOF_SIZE_T__ == 2
		memcpyw((u16 *)v0, (u16 *)v1, s2_bytes);
#else
		memcpy((u8 *)v0, (u8 *)v1, s2_bytes*sizeof(size_t));
#endif
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}

%#ifdef __USE_XOPEN2K8
[ATTR_WUNUSED][dependency_include(<parts/malloca.h>)]
[same_impl][requires(!defined(__NO_MALLOCA))][export][section(.text.crt.unicode.locale.memory)]
fuzzy_strcasecmp_l:([nonnull] char const *s1, [nonnull] char const *s2, $locale_t locale) -> $size_t {
	return fuzzy_memcasecmp_l(s1, strlen(s1), s2, strlen(s2), locale);
}

[ATTR_WUNUSED][dependency_include(<parts/malloca.h>)]
[same_impl][requires(!defined(__NO_MALLOCA))][export][section(.text.crt.unicode.locale.memory)]
fuzzy_strncasecmp_l:([nonnull] char const *s1, $size_t s1_maxlen,
                     [nonnull] char const *s2, $size_t s2_maxlen, $locale_t locale) -> $size_t {
	return fuzzy_memcasecmp_l(s1, strnlen(s1, s1_maxlen), s2, strnlen(s2, s2_maxlen), locale);
}

[ATTR_WUNUSED][section(.text.crt.unicode.locale.memory)]
wildstrcasecmp_l:([nonnull] char const *pattern,
                  [nonnull] char const *string, $locale_t locale) -> int {
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

[dependency_include(<parts/malloca.h>)][ATTR_WUNUSED]
[same_impl][requires(!defined(__NO_MALLOCA))][export][section(.text.crt.unicode.locale.memory)]
fuzzy_memcasecmp_l:([nonnull] void const *s1, $size_t s1_bytes,
                    [nonnull] void const *s2, $size_t s2_bytes, $locale_t locale) -> $size_t {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{ @@yield $wchar_function ? "wchar_t" : "void"@@ const *temp = s1; s1 = s2; s2 = temp; }
		{ size_t temp = s1_bytes; s1_bytes = s2_bytes; s2_bytes = temp; }
	}
	__malloca_tryhard(v0, (s2_bytes+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0)
		return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_bytes+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_bytes; ++i)
		v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i+1;
		for (j = 0; j < s2_bytes; j++) {
			byte_t c1 = ((byte_t *)s1)[i];
			byte_t c2 = ((byte_t *)s2)[j];
			cost  = c1 != c2 && tolower_l(c1, locale) != tolower_l(c2, locale);
			cost += v0[j];
			temp  = v1[j]+1;
			if (cost > temp) cost = temp;
			temp  = v0[j+1]+1;
			if (cost > temp) cost = temp;
			v1[j+1] = cost;
		}
#if __SIZEOF_SIZE_T__ == 8
		memcpyq((u64 *)v0, (u64 *)v1, s2_bytes);
#elif __SIZEOF_SIZE_T__ == 4
		memcpyl((u32 *)v0, (u32 *)v1, s2_bytes);
#elif __SIZEOF_SIZE_T__ == 2
		memcpyw((u16 *)v0, (u16 *)v1, s2_bytes);
#else
		memcpy((u8 *)v0, (u8 *)v1, s2_bytes*sizeof(size_t));
#endif
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

[noexport][ATTR_WUNUSED]
fuzzy_memcmpb:([nonnull] void const *s1, $size_t s1_bytes,
               [nonnull] void const *s2, $size_t s2_bytes) -> $size_t = fuzzy_memcmp;

[dependency_include(<parts/malloca.h>)][ATTR_WUNUSED]
[same_impl][requires(!defined(__NO_MALLOCA))][export]
fuzzy_memcmpw:([nonnull] void const *s1, $size_t s1_words,
               [nonnull] void const *s2, $size_t s2_words) -> $size_t {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_words)
		return s2_words;
	if unlikely(!s2_words)
		return s1_words;
	if (s2_words > s1_words) {
		{ void const *temp = s1; s1 = s2; s2 = temp; }
		{ size_t temp = s1_words; s1_words = s2_words; s2_words = temp; }
	}
	__malloca_tryhard(v0, (s2_words+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0)
		return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_words+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_words; ++i)
		v0[i] = i;
	for (i = 0; i < s1_words; ++i) {
		v1[0] = i+1;
		for (j = 0; j < s2_words; j++) {
			cost  = ((u16 *)s1)[i] != ((u16 *)s2)[j];
			cost += v0[j];
			temp  = v1[j]+1;
			if (cost > temp) cost = temp;
			temp  = v0[j+1]+1;
			if (cost > temp) cost = temp;
			v1[j+1] = cost;
		}
#if __SIZEOF_SIZE_T__ == 8
		memcpyq((u64 *)v0, (u64 *)v1, s2_words);
#elif __SIZEOF_SIZE_T__ == 4
		memcpyl((u32 *)v0, (u32 *)v1, s2_words);
#elif __SIZEOF_SIZE_T__ == 2
		memcpyw((u16 *)v0, (u16 *)v1, s2_words);
#else
		memcpy((u8 *)v0, (u8 *)v1, s2_words*sizeof(size_t));
#endif
	}
	temp = v1[s2_words];
	__freea(v1);
	__freea(v0);
	return temp;
}

[dependency_include(<parts/malloca.h>)][ATTR_WUNUSED]
[same_impl][requires(!defined(__NO_MALLOCA))][export]
fuzzy_memcmpl:([nonnull] void const *s1, $size_t s1_dwords,
               [nonnull] void const *s2, $size_t s2_dwords) -> $size_t {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_dwords)
		return s2_dwords;
	if unlikely(!s2_dwords)
		return s1_dwords;
	if (s2_dwords > s1_dwords) {
		{ void const *temp = s1; s1 = s2; s2 = temp; }
		{ size_t temp = s1_dwords; s1_dwords = s2_dwords; s2_dwords = temp; }
	}
	__malloca_tryhard(v0, (s2_dwords+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0) return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_dwords+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_dwords; ++i)
		v0[i] = i;
	for (i = 0; i < s1_dwords; ++i) {
		v1[0] = i+1;
		for (j = 0; j < s2_dwords; j++) {
			cost  = ((u32 *)s1)[i] != ((u32 *)s2)[j];
			cost += v0[j];
			temp  = v1[j]+1;
			if (cost > temp) cost = temp;
			temp  = v0[j+1]+1;
			if (cost > temp) cost = temp;
			v1[j+1] = cost;
		}
#if __SIZEOF_SIZE_T__ == 8
		memcpyq((u64 *)v0, (u64 *)v1, s2_dwords);
#elif __SIZEOF_SIZE_T__ == 4
		memcpyl((u32 *)v0, (u32 *)v1, s2_dwords);
#elif __SIZEOF_SIZE_T__ == 2
		memcpyw((u16 *)v0, (u16 *)v1, s2_dwords);
#else
		memcpy((u8 *)v0, (u8 *)v1, s2_dwords*sizeof(size_t));
#endif
	}
	temp = v1[s2_dwords];
	__freea(v1);
	__freea(v0);
	return temp;
}

%#ifdef __UINT64_TYPE__
[dependency_include(<parts/malloca.h>)][ATTR_WUNUSED]
[same_impl][requires(!defined(__NO_MALLOCA))][export]
fuzzy_memcmpq:([nonnull] void const *s1, $size_t s1_qwords,
               [nonnull] void const *s2, $size_t s2_qwords) -> $size_t {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_qwords)
		return s2_qwords;
	if unlikely(!s2_qwords)
		return s1_qwords;
	if (s2_qwords > s1_qwords) {
		{ void const *temp = s1; s1 = s2; s2 = temp; }
		{ size_t temp = s1_qwords; s1_qwords = s2_qwords; s2_qwords = temp; }
	}
	__malloca_tryhard(v0, (s2_qwords+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0) return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_qwords+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_qwords; ++i)
		v0[i] = i;
	for (i = 0; i < s1_qwords; ++i) {
		v1[0] = i+1;
		for (j = 0; j < s2_qwords; j++) {
			cost  = ((u64 *)s1)[i] != ((u64 *)s2)[j];
			cost += v0[j];
			temp  = v1[j]+1;
			if (cost > temp) cost = temp;
			temp  = v0[j+1]+1;
			if (cost > temp) cost = temp;
			v1[j+1] = cost;
		}
#if __SIZEOF_SIZE_T__ == 8
		memcpyq((u64 *)v0, (u64 *)v1, s2_qwords);
#elif __SIZEOF_SIZE_T__ == 4
		memcpyl((u32 *)v0, (u32 *)v1, s2_qwords);
#elif __SIZEOF_SIZE_T__ == 2
		memcpyw((u16 *)v0, (u16 *)v1, s2_qwords);
#else
		memcpy((u8 *)v0, (u8 *)v1, s2_qwords*sizeof(size_t));
#endif
	}
	temp = v1[s2_qwords];
	__freea(v1);
	__freea(v0);
	return temp;
}

%{
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */
}


[alias(_strncoll)][ATTR_WUNUSED][ATTR_PURE][section(.text.crt.unicode.static.memory)]
strncoll:([nonnull] char const *s1, [nonnull] char const *s2, $size_t maxlen) -> int {
	return strncmp(s1, s2, maxlen);
}

[alias(_stricoll, strcasecmp, _stricmp, stricmp, _strcmpi, strcmpi)]
[ATTR_WUNUSED][ATTR_PURE][section(.text.crt.unicode.static.memory)]
strcasecoll:([nonnull] char const *s1, [nonnull] char const *s2) -> int {
	return strcasecmp(s1, s2);
}

[alias(_strnicoll, strncasecmp)]
[ATTR_WUNUSED][ATTR_PURE][section(.text.crt.unicode.static.memory)]
strncasecoll:([nonnull] char const *s1, [nonnull] char const *s2, $size_t maxlen) -> int {
	return strncasecmp(s1, s2, maxlen);
}

[ATTR_LEAF]
strnrev:([nonnull] char *__restrict str, $size_t maxlen) -> [== str] char * {
	return (char *)memrev(str, strnlen(str, maxlen));
}

[ATTR_LEAF][section(.text.crt.unicode.static.memory)]
strnlwr:([nonnull] char *__restrict str, $size_t maxlen) -> [== str] char * {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = tolower(ch);
	return str;
}

[ATTR_LEAF][section(.text.crt.unicode.static.memory)]
strnupr:([nonnull] char *__restrict str, $size_t maxlen) -> [== str] char * {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = toupper(ch);
	return str;
}


%#ifdef __USE_XOPEN2K8
[alias(_strncoll_l)][ATTR_WUNUSED]
[section(.text.crt.unicode.locale.memory)]
strncoll_l:([nonnull] char const *s1, [nonnull] char const *s2, $size_t maxlen, $locale_t locale) -> int {
	(void)locale;
	return strncoll(s1, s2, maxlen);
}

[alias(_stricoll_l)][ATTR_WUNUSED]
[section(.text.crt.unicode.locale.memory)]
strcasecoll_l:([nonnull] char const *s1, [nonnull] char const *s2, $locale_t locale) -> int {
	return strcasecmp_l(s1, s2, locale);
}

[alias(_strnicoll_l, strncasecmp_l, _strnicmp_l, _strncmpi_l)]
[ATTR_WUNUSED][section(.text.crt.unicode.locale.memory)]
strncasecoll_l:([nonnull] char const *s1, [nonnull] char const *s2, $size_t maxlen, $locale_t locale) -> int {
	(void)locale;
	return strncasecoll(s1, s2, maxlen);
}

[export_alias(_strlwr_l)][section(.text.crt.unicode.locale.memory)]
strlwr_l:([nonnull] char *__restrict str, $locale_t locale) -> [== str] char * {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = tolower_l(ch, locale);
	return str;
}

[export_alias(_strupr_l)][section(.text.crt.unicode.locale.memory)]
strupr_l:([nonnull] char *__restrict str, $locale_t locale) -> [== str] char * {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = toupper_l(ch, locale);
	return str;
}

[section(.text.crt.unicode.locale.memory)]
strnlwr_l:([nonnull] char *__restrict str, $size_t maxlen, $locale_t locale) -> [== str] char * {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = tolower_l(ch, locale);
	return str;
}

[section(.text.crt.unicode.locale.memory)]
strnupr_l:([nonnull] char *__restrict str, $size_t maxlen, $locale_t locale) -> [== str] char * {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = toupper_l(ch, locale);
	return str;
}

[ATTR_LEAF]
memrev:([nonnull] void *__restrict base, $size_t n_bytes) -> [== base] void * {
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
[noexport][attribute(*)][alias(*)]
memrevb:([nonnull] void *__restrict base, $size_t n_bytes) -> [== base] $uint8_t * = memrev;

[ATTR_LEAF]
memrevw:([nonnull] void *__restrict base, $size_t n_words) -> [== base] $uint16_t * {
	u16 *iter, *end;
	end = (iter = (u16 *)base) + n_words;
	while (iter < end) {
		u16 temp = *iter;
		*iter++ = *--end;
		*end = temp;
	}
	return (u16 *)base;
}

[ATTR_LEAF]
memrevl:([nonnull] void *__restrict base, $size_t n_dwords) -> [== base] $uint32_t * {
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
[ATTR_LEAF]
memrevq:([nonnull] void *__restrict base, $size_t n_qwords) -> [== base] $uint64_t * {
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

%{
#endif /* __USE_KOS */


#if defined(__USE_KOS) || defined(__USE_DOS)
}
[export_alias(_strlwr)][section(.text.crt.unicode.static.memory)]
strlwr:([nonnull] char *__restrict str) -> [== str] char * {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = tolower(ch);
	return str;
}
[export_alias(_strupr)][section(.text.crt.unicode.static.memory)]
strupr:([nonnull] char *__restrict str) -> [== str] char * {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = toupper(ch);
	return str;
}

[export_alias(_strset)][ATTR_LEAF]
strset:([nonnull] char *__restrict str, int ch) -> [== str] char * {
	char *iter;
	for (iter = str; *iter; ++iter)
		*iter = (char)ch;
	return str;
}

[export_alias(_strnset)][ATTR_LEAF]
strnset:([nonnull] char *__restrict str, int ch, $size_t maxlen) -> [== str] char * {
	char *iter;
	for (iter = str; maxlen-- && *iter; ++iter)
		*iter = (char)ch;
	return str;
}

[alias(_strrev)][ATTR_LEAF]
strrev:([nonnull] char *__restrict str) -> [== str] char * {
	return (char *)memrev(str, strlen(str));
}
%{
#endif /* __USE_KOS || __USE_DOS */


#ifdef __USE_DOS
}

[attribute(*)][alias(*)] _memccpy:(*) = memccpy;
[attribute(*)][alias(*)] _memicmp:(*) = memcasecmp;
[attribute(*)][alias(*)] _memicmp_l:(*) = memcasecmp_l;
[attribute(*)][alias(*)] memicmp:(*) = memcasecmp;

[dependency_include(<parts/errno.h>)]
[section(.text.crt.dos.string.memory)]
_strset_s:([nonnull] char *dst, $size_t dstsize, int ch) -> $errno_t {
@@exec MEMSET = $wchar_function ? "wmemset" : "memset"@@
@@exec MULTIPLY = $wchar_function ? none : " * sizeof(char)"@@
	char *p;
	size_t remaining;
	if (!dst && dstsize != 0)
		return __EINVAL;
	p = dst;
	remaining = dstsize;
	while (*p && --remaining != 0)
		*p++ = (char)ch;
	if (remaining == 0) {
		@@yield MEMSET@@(dst, 1, dstsize@@yield MULTIPLY@@);
		return __EINVAL;
	}
	@@yield MEMSET@@(p, 0, remaining@@yield MULTIPLY@@);
	return 0;
}

%
%#ifdef __USE_DOS_SLIB
[dependency_include(<parts/errno.h>)]
[section(.text.crt.dos.string.memory)]
memcpy_s:([nonnull] void *dst, rsize_t dstlength,
          [nonnull] void const *src, rsize_t srclength) -> $errno_t {
@@exec MEMSET = $wchar_function ? "wmemset" : "memset"@@
@@exec MEMCPY = $wchar_function ? "wmemcpy" : "memcpy"@@
	if (!srclength)
		return 0;
	if (dst == NULL)
		return __EINVAL;
	if (!src || dstlength < srclength) {
		@@yield MEMSET@@(dst, 0, dstlength);
		if (!src)
			return __EINVAL;
		if (dstlength < srclength)
			return __ERANGE;
		return __EINVAL;
	}
	@@yield MEMCPY@@(dst, src, srclength);
	return 0;
}

[dependency_include(<parts/errno.h>)]
[section(.text.crt.dos.string.memory)]
memmove_s:([nonnull] void *dst, rsize_t dstlength,
           [nonnull] void const *src, rsize_t srclength) -> $errno_t {
@@exec MEMMOVE = $wchar_function ? "wmemmove" : "memmove"@@
	if (!srclength)
		return 0;
	if (!dst || !src)
		return __EINVAL;
	if (dstlength < srclength)
		return __ERANGE;
	@@yield MEMMOVE@@(dst, src, srclength);
	return 0;
}


[dependency_include(<parts/errno.h>)]
[section(.text.crt.dos.string.memory)]
strcpy_s:(char *dst, $size_t dstsize, char const *src) -> $errno_t {
@@exec MEMSET = $wchar_function ? "wmemset" : "memset"@@
@@exec MULTIPLY = $wchar_function ? none : " * sizeof(char)"@@
	char *iter;
	size_t remaining;
	if ((!dst && dstsize) || !src)
		return __EINVAL;
	iter = dst;
	remaining = dstsize;
	while ((*iter++ = *src++) != 0 && --remaining)
		;
	if (!remaining) {
		@@yield MEMSET@@(dst, 0, dstsize@@yield MULTIPLY@@);
		return __ERANGE;
	}
	@@yield MEMSET@@(iter, 0, remaining@@yield MULTIPLY@@);
	return 0;
}

[dependency_include(<parts/errno.h>)]
[section(.text.crt.dos.string.memory)]
strcat_s:(char *dst, $size_t dstsize, char const *src) -> $errno_t {
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

%{
__LOCAL __ATTR_WUNUSED __ATTR_PURE
__SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strnlen_s)(char const *__str, __SIZE_TYPE__ __maxlen) {
	return __str ? strnlen(__str, __maxlen) : 0;
}
}

[dependency_include(<parts/errno.h>)][section(.text.crt.dos.string.memory)]
strncat_s:(char *dst, rsize_t dstsize, const char *src, rsize_t maxlen) -> $errno_t {
@@exec MEMSET = $wchar_function ? "wmemset" : "memset"@@
@@exec MULTIPLY = $wchar_function ? none : " * sizeof(char)"@@
	char *iter;
	size_t remaining;
	if (!maxlen && !dst && !dstsize)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return __EINVAL;
	for (iter = dst, remaining = dstsize; remaining && *iter; ++iter, --remaining)
		;
	if (!remaining) {
		@@yield MEMSET@@(dst, 0, dstsize@@yield MULTIPLY@@);
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
		@@yield MEMSET@@(dst, 0, dstsize@@yield MULTIPLY@@);
		return __ERANGE;
	}
	@@yield MEMSET@@(iter, 0, remaining@@yield MULTIPLY@@);
	return 0;
}

[dependency_include(<parts/errno.h>)]
[section(.text.crt.dos.string.memory)]
strncpy_s:(char *dst, $size_t dstsize, char const *src, $size_t maxlen) -> $errno_t {
@@exec MEMSET = $wchar_function ? "wmemset" : "memset"@@
@@exec MULTIPLY = $wchar_function ? none : " * sizeof(char)"@@
	char *iter;
	size_t remaining;
	if (maxlen == 0 && dst == NULL && dstsize == 0)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return __EINVAL;
	if (!maxlen) {
		@@yield MEMSET@@(dst, 0, dstsize@@yield MULTIPLY@@);
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
		@@yield MEMSET@@(dst, 0, dstsize@@yield MULTIPLY@@);
		return __ERANGE;
	}
	@@yield MEMSET@@(iter, 0, remaining@@yield MULTIPLY@@);
	return 0;
}

[alias(*)][attribute(*)] strtok_s:(*) = strtok_r;
%#endif /* __USE_DOS_SLIB */

[alias(*)][attribute(*)] _strdup:(*) = strdup;
[alias(*)][attribute(*)] _stricmp:(*) = strcasecmp;
[alias(*)][attribute(*)] _strcmpi:(*) = strcasecmp;
[alias(*)][attribute(*)] _stricmp_l:(*) = strcasecmp_l;
[alias(*)][attribute(*)] _strcoll_l:(*) = strcoll_l;
[alias(*)][attribute(*)] _stricoll:(*) = strcasecoll;
[alias(*)][attribute(*)] _stricoll_l:(*) = strcasecoll_l;
[alias(*)][attribute(*)] _strncoll:(*) = strncoll;
[alias(*)][attribute(*)] _strncoll_l:(*) = strncoll_l;
[alias(*)][attribute(*)] _strnicoll:(*) = strncasecoll;
[alias(*)][attribute(*)] _strnicoll_l:(*) = strncasecoll_l;

[section(.text.crt.dos.errno)][cp][ATTR_WUNUSED]
_strerror:(char const *message) -> char *;

[section(.text.crt.dos.errno)][cp][dos_variant]
_strerror_s:([nonnull] char *__restrict buf, $size_t buflen, char const *message) -> $errno_t;

[dependency_include(<parts/errno.h>)]
[section(.text.crt.dos.unicode.static.memory)]
_strlwr_s:(char *buf, $size_t buflen) -> $errno_t {
	char *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (strnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = tolower(ch);
	return 0;
}

[section(.text.crt.dos.unicode.static.memory)]
_strupr_s:(char *buf, $size_t buflen) -> $errno_t {
	char *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (strnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = toupper(ch);
	return 0;
}

[section(.text.crt.dos.unicode.locale.memory)]
_strlwr_s_l:(char *buf, $size_t buflen, $locale_t locale) -> $errno_t {
	char *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (strnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = tolower_l(ch, locale);
	return 0;
}

[section(.text.crt.dos.unicode.locale.memory)]
_strupr_s_l:(char *buf, $size_t buflen, $locale_t locale) -> $errno_t {
	char *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (strnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = toupper_l(ch, locale);
	return 0;
}

[alias(*)][attribute(*)] _strnicmp:(*) = strncasecmp;
[alias(*)][attribute(*)] _strnicmp_l:(*) = strncasecmp_l;

[dependency_include(<parts/errno.h>)][section(.text.crt.dos.string.memory)]
_strnset_s:(char *__restrict buf, $size_t buflen, int ch, $size_t maxlen) -> $errno_t {
@@exec MEMSET = $wchar_function ? "wmemset" : "memset"@@
@@exec MULTIPLY = $wchar_function ? none : " * sizeof(char)"@@
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
		@@yield MEMSET@@(buf, 0, buflen@@yield MULTIPLY@@);
		return __EINVAL;
	}
	@@yield MEMSET@@(iter, 0, remaining@@yield MULTIPLY@@);
	return 0;
}

[alias(*)][attribute(*)] _strrev:(*) = strrev;
[alias(*)][attribute(*)] _strxfrm_l:(*) = strxfrm_l;
[alias(*)][attribute(*)] stricmp:(*) = strcasecmp;
[alias(*)][attribute(*)] strcmpi:(*) = strcasecmp;
[alias(*)][attribute(*)] strnicmp:(*) = strncasecmp;

/* The following aren't actually defined by DOS, but one might assume that they were */
[alias(*)][attribute(*)] _strncmpi:(*) = strncasecmp;
[alias(*)][attribute(*)] _strncmpi_l:(*) = strncasecmp_l;
[alias(*)][attribute(*)] strncmpi:(*) = strncasecmp;

%
%#ifndef _WSTRING_DEFINED
%#define _WSTRING_DEFINED 1
%[insert:extern(_wcsdup)]
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
%[insert:extern(_wcsicmp)]
%[insert:extern(_wcsicmp_l)]
%[insert:extern(_wcsnicmp)]
%[insert:extern(_wcsnicmp_l)]
%[insert:extern(_wcsnset_s)]
%[insert:extern(_wcsnset)]
%[insert:extern(_wcsrev)]
%[insert:extern(_wcsset_s)]
%[insert:extern(_wcsset)]
%[insert:extern(_wcslwr_s)]
%[insert:extern(_wcslwr)]
%[insert:extern(_wcslwr_s_l)]
%[insert:extern(_wcslwr_l)]
%[insert:extern(_wcsupr_s)]
%[insert:extern(_wcsupr)]
%[insert:extern(_wcsupr_s_l)]
%[insert:extern(_wcsupr_l)]
%[insert:extern(wcsxfrm)]
%[insert:extern(_wcsxfrm_l)]
%[insert:extern(wcscoll)]
%[insert:extern(_wcscoll_l)]
%[insert:extern(_wcsicoll)]
%[insert:extern(_wcsicoll_l)]
%[insert:extern(_wcsncoll)]
%[insert:extern(_wcsncoll_l)]
%[insert:extern(_wcsnicoll)]
%[insert:extern(_wcsnicoll_l)]
%[insert:extern(wcsdup)]
%[insert:extern(wcswcs)]
%[insert:extern(wcsicmp)]
%[insert:extern(wcsnicmp)]
%[insert:extern(wcsnset)]
%[insert:extern(wcsrev)]
%[insert:extern(wcsset)]
%[insert:extern(wcslwr)]
%[insert:extern(wcsupr)]
%[insert:extern(wcsicoll)]
%#ifdef __USE_DOS_SLIB
%[insert:extern(wcscat_s)]
%[insert:extern(wcscpy_s)]
%[insert:extern(wcsncat_s)]
%[insert:extern(wcsncpy_s)]
%[insert:extern(wcstok_s)]
%{
#ifndef __wcsnlen_s_defined
#define __wcsnlen_s_defined 1
__LOCAL __ATTR_WUNUSED __ATTR_PURE
__SIZE_TYPE__ __NOTHROW_NCX((__LIBCCALL wcsnlen_s)(wchar_t const *__str, __SIZE_TYPE__ __maxlen)) {
	return __str ? wcsnlen(__str, __maxlen) : 0;
}
#endif /* !__wcsnlen_s_defined */
}
%#endif  /* __USE_DOS_SLIB */
%#endif /* !_WSTRING_DEFINED */

%{
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
#endif /* !__CXX_SYSTEM_HEADER */
#define strlen(x) __forward_size(__builtin_constant_p(x) ? __builtin_strlen(x) : (__NAMESPACE_STD_SYM strlen)(x))
#else /* __cplusplus */
#define strlen(x) (__builtin_constant_p(x) ? __builtin_strlen(x) : (strlen)(x))
#endif /* !__cplusplus */
#endif /* __has_builtin(__builtin_strlen) */
#endif /* !__INTELLISENSE__ */
#endif /* __LIBC_BIND_OPTIMIZATIONS && !__NO_builtin_constant_p */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STRING_H)
#include <parts/uchar/string.h>
#endif
#endif /* __USE_UTF */

}

