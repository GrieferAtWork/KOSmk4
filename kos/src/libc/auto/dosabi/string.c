/* HASH CRC-32:0xdbf07aaf */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_STRING_C
#define GUARD_LIBC_AUTO_DOSABI_STRING_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/string.h"

DECL_BEGIN

/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd_memcpy)(void *__restrict dst,
                                  void const *__restrict src,
                                  size_t n_bytes) {
	return libc_memcpy(dst, src, n_bytes);
}
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd_memmove)(void *dst,
                                   void const *src,
                                   size_t n_bytes) {
	return libc_memmove(dst, src, n_bytes);
}
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_memset)(void *__restrict dst,
                                  int byte,
                                  size_t n_bytes) {
	return libc_memset(dst, byte, n_bytes);
}
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_memcmp)(void const *s1,
                                  void const *s2,
                                  size_t n_bytes) {
	return libc_memcmp(s1, s2, n_bytes);
}
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_memchr)(void const *__restrict haystack,
                                  int needle,
                                  size_t n_bytes) {
	return libc_memchr(haystack, needle, n_bytes);
}
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_strlen)(char const *__restrict string) {
	return libc_strlen(string);
}
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strchr)(char const *__restrict haystack,
                                  int needle) {
	return libc_strchr(haystack, needle);
}
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strrchr)(char const *__restrict haystack,
                                   int needle) {
	return libc_strrchr(haystack, needle);
}
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_strcmp)(char const *s1,
                                  char const *s2) {
	return libc_strcmp(s1, s2);
}
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_strncmp)(char const *s1,
                                   char const *s2,
                                   size_t maxlen) {
	return libc_strncmp(s1, s2, maxlen);
}
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_strstr)(char const *haystack,
                                  char const *needle) {
	return libc_strstr(haystack, needle);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_strcpy)(char *__restrict buf,
                                  char const *__restrict src) {
	return libc_strcpy(buf, src);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_strncpy)(char *__restrict buf,
                                   char const *__restrict src,
                                   size_t buflen) {
	return libc_strncpy(buf, src, buflen);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_strcat)(char *__restrict buf,
                                  char const *__restrict src) {
	return libc_strcat(buf, src);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_strncat)(char *__restrict buf,
                                   char const *__restrict src,
                                   size_t buflen) {
	return libc_strncat(buf, src, buflen);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_strcspn)(char const *haystack,
                                   char const *reject) {
	return libc_strcspn(haystack, reject);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_strspn)(char const *haystack,
                                  char const *accept) {
	return libc_strspn(haystack, accept);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_strpbrk)(char const *haystack,
                                   char const *accept) {
	return libc_strpbrk(haystack, accept);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((2)) char *
NOTHROW_NCX(LIBDCALL libd_strtok)(char *string,
                                  char const *delim) {
	return libc_strtok(string, delim);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_strcoll)(char const *s1,
                                   char const *s2) {
	return libc_strcoll(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") NONNULL((2)) size_t
NOTHROW_NCX(LIBDCALL libd_strxfrm)(char *dst,
                                   char const *__restrict src,
                                   size_t maxlen) {
	return libc_strxfrm(dst, src, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.errno") ATTR_COLD ATTR_RETNONNULL WUNUSED char *
NOTHROW_NCX(LIBDCALL libd_strerror)(int errnum) {
	return libc_strerror(errnum);
}
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_strnlen)(char const *__restrict string,
                                   size_t maxlen) {
	return libc_strnlen(string, maxlen);
}
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_stpcpy)(char *__restrict buf,
                                  char const *__restrict src) {
	return libc_stpcpy(buf, src);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_stpncpy)(char *__restrict buf,
                                   char const *__restrict src,
                                   size_t buflen) {
	return libc_stpncpy(buf, src, buflen);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_strcoll_l)(char const *s1,
                                     char const *s2,
                                     locale_t locale) {
	return libc_strcoll_l(s1, s2, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") NONNULL((2)) size_t
NOTHROW_NCX(LIBDCALL libd_strxfrm_l)(char *dst,
                                     char const *__restrict src,
                                     size_t maxlen,
                                     locale_t locale) {
	return libc_strxfrm_l(dst, src, maxlen, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.errno") ATTR_COLD WUNUSED char *
NOTHROW_NCX(LIBDCALL libd_strerror_l)(int errnum,
                                      locale_t locale) {
	return libc_strerror_l(errnum, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory.strsignal") ATTR_COLD ATTR_RETNONNULL WUNUSED char *
NOTHROW_NCX(LIBDCALL libd_strsignal)(int signo) {
	return libc_strsignal(signo);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strndup)(char const *__restrict string,
                                   size_t max_chars) {
	return libc_strndup(string, max_chars);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strdup)(char const *__restrict string) {
	return libc_strdup(string);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF NONNULL((2, 3)) char *
NOTHROW_NCX(LIBDCALL libd_strtok_r)(char *string,
                                    char const *delim,
                                    char **__restrict save_ptr) {
	return libc_strtok_r(string, delim, save_ptr);
}
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_memrchr)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
	return libc_memrchr(haystack, needle, n_bytes);
}
/* Same as `memchr' with a search limit of `(size_t)-1' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_rawmemchr)(void const *__restrict haystack,
                                     int needle) {
	return libc_rawmemchr(haystack, needle);
}
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strchrnul)(char const *__restrict haystack,
                                     int needle) {
	return libc_strchrnul(haystack, needle);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED char *
NOTHROW_NCX(LIBDCALL libd_basename)(char const *filename) {
	return libc_basename(filename);
}
/* Same as `strstr', but ignore casing */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_strcasestr)(char const *haystack,
                                      char const *needle) {
	return libc_strcasestr(haystack, needle);
}
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) void *
NOTHROW_NCX(LIBDCALL libd_memmem)(void const *haystack,
                                  size_t haystacklen,
                                  void const *needle,
                                  size_t needlelen) {
	return libc_memmem(haystack, haystacklen, needle, needlelen);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_strverscmp)(char const *s1,
                                      char const *s2) {
	return libc_strverscmp(s1, s2);
}
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd_mempcpy)(void *__restrict dst,
                                   void const *__restrict src,
                                   size_t n_bytes) {
	return libc_mempcpy(dst, src, n_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strfry)(char *__restrict string) {
	return libc_strfry(string);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_memfrob)(void *buf,
                                   size_t num_bytes) {
	return libc_memfrob(buf, num_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_strcasecmp_l)(char const *s1,
                                        char const *s2,
                                        locale_t locale) {
	return libc_strcasecmp_l(s1, s2, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_strncasecmp_l)(char const *s1,
                                         char const *s2,
                                         size_t maxlen,
                                         locale_t locale) {
	return libc_strncasecmp_l(s1, s2, maxlen, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.errno") ATTR_COLD ATTR_RETNONNULL NONNULL((2)) char *
NOTHROW_NCX(LIBDCALL libd_strerror_r)(int errnum,
                                      char *buf,
                                      size_t buflen) {
	return libc_strerror_r(errnum, buf, buflen);
}
INTERN ATTR_SECTION(".text.crt.dos.errno") ATTR_COLD NONNULL((2)) errno_t
NOTHROW_NCX(LIBDCALL libd___xpg_strerror_r)(int errnum,
                                            char *buf,
                                            size_t buflen) {
	return libc___xpg_strerror_r(errnum, buf, buflen);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_strsep)(char **__restrict stringp,
                                  char const *__restrict delim) {
	return libc_strsep(stringp, delim);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_strcasecmp)(char const *s1,
                                      char const *s2) {
	return libc_strcasecmp(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_strncasecmp)(char const *s1,
                                       char const *s2,
                                       size_t maxlen) {
	return libc_strncasecmp(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T
NOTHROW(LIBDCALL libd_ffs)(int i) {
	return libc_ffs(i);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T
NOTHROW(LIBDCALL libd_ffsl)(long i) {
	return libc_ffsl(i);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T
NOTHROW(LIBDCALL libd_ffsll)(__LONGLONG i) {
	return libc_ffsll(i);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_strlcat)(char *__restrict dst,
                                   char const *__restrict src,
                                   size_t bufsize) {
	return libc_strlcat(dst, src, bufsize);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_strlcpy)(char *__restrict dst,
                                   char const *__restrict src,
                                   size_t bufsize) {
	return libc_strlcpy(dst, src, bufsize);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd_memccpy)(void *__restrict dst,
                                   void const *__restrict src,
                                   int needle,
                                   size_t num_bytes) {
	return libc_memccpy(dst, src, needle, num_bytes);
}
/* Copy memory between non-overlapping memory blocks. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_memcpyw)(void *__restrict dst,
                                   void const *__restrict src,
                                   size_t n_words) {
	return libc_memcpyw(dst, src, n_words);
}
/* Same as `memcpyw', but return `DST + N_WORDS', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_mempcpyw)(void *__restrict dst,
                                    void const *__restrict src,
                                    size_t n_words) {
	return libc_mempcpyw(dst, src, n_words);
}
/* Copy memory between non-overlapping memory blocks. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_memcpyl)(void *__restrict dst,
                                   void const *__restrict src,
                                   size_t n_dwords) {
	return libc_memcpyl(dst, src, n_dwords);
}
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_mempcpyl)(void *__restrict dst,
                                    void const *__restrict src,
                                    size_t n_dwords) {
	return libc_mempcpyl(dst, src, n_dwords);
}
/* Move memory between potentially overlapping memory blocks. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_memmovew)(void *dst,
                                    void const *src,
                                    size_t n_words) {
	return libc_memmovew(dst, src, n_words);
}
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_mempmovew)(void *dst,
                                     void const *src,
                                     size_t n_words) {
	return libc_mempmovew(dst, src, n_words);
}
/* Move memory between potentially overlapping memory blocks. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_memmovel)(void *dst,
                                    void const *src,
                                    size_t n_dwords) {
	return libc_memmovel(dst, src, n_dwords);
}
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_mempmovel)(void *dst,
                                     void const *src,
                                     size_t n_dwords) {
	return libc_mempmovel(dst, src, n_dwords);
}
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_WORDS') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_memmoveupw)(void *dst,
                                      void const *src,
                                      size_t n_words) {
	return libc_memmoveupw(dst, src, n_words);
}
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_memmovedownw)(void *dst,
                                        void const *src,
                                        size_t n_words) {
	return libc_memmovedownw(dst, src, n_words);
}
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST >= SRC || !N_WORDS') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_mempmoveupw)(void *dst,
                                       void const *src,
                                       size_t n_words) {
	return libc_mempmoveupw(dst, src, n_words);
}
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST <= SRC || !N_WORDS') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_mempmovedownw)(void *dst,
                                         void const *src,
                                         size_t n_words) {
	return libc_mempmovedownw(dst, src, n_words);
}
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_memmoveupl)(void *dst,
                                      void const *src,
                                      size_t n_dwords) {
	return libc_memmoveupl(dst, src, n_dwords);
}
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_memmovedownl)(void *dst,
                                        void const *src,
                                        size_t n_dwords) {
	return libc_memmovedownl(dst, src, n_dwords);
}
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST >= SRC || !N_DWORDS') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_mempmoveupl)(void *dst,
                                       void const *src,
                                       size_t n_dwords) {
	return libc_mempmoveupl(dst, src, n_dwords);
}
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST <= SRC || !N_DWORDS') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_mempmovedownl)(void *dst,
                                         void const *src,
                                         size_t n_dwords) {
	return libc_mempmovedownl(dst, src, n_dwords);
}
/* Fill memory with a given word */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_memsetw)(void *__restrict dst,
                                   uint16_t word,
                                   size_t n_words) {
	return libc_memsetw(dst, word, n_words);
}
/* Same as `memsetw', but return `DST + N_WORDS', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_mempsetw)(void *__restrict dst,
                                    uint16_t word,
                                    size_t n_words) {
	return libc_mempsetw(dst, word, n_words);
}
/* Fill memory with a given dword */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_memsetl)(void *__restrict dst,
                                   uint32_t dword,
                                   size_t n_dwords) {
	return libc_memsetl(dst, dword, n_dwords);
}
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_mempsetl)(void *__restrict dst,
                                    uint32_t dword,
                                    size_t n_dwords) {
	return libc_mempsetl(dst, dword, n_dwords);
}
/* Compare memory buffers and return the difference of the first non-matching word */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int16_t
NOTHROW_NCX(LIBDCALL libd_memcmpw)(void const *s1,
                                   void const *s2,
                                   size_t n_words) {
	return libc_memcmpw(s1, s2, n_words);
}
/* Compare memory buffers and return the difference of the first non-matching dword */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int32_t
NOTHROW_NCX(LIBDCALL libd_memcmpl)(void const *s1,
                                   void const *s2,
                                   size_t n_dwords) {
	return libc_memcmpl(s1, s2, n_dwords);
}
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_memchrw)(void const *__restrict haystack,
                                   uint16_t word,
                                   size_t n_words) {
	return libc_memchrw(haystack, word, n_words);
}
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_memchrl)(void const *__restrict haystack,
                                   uint32_t dword,
                                   size_t n_dwords) {
	return libc_memchrl(haystack, dword, n_dwords);
}
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_WORDS * 2'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_memrchrw)(void const *__restrict haystack,
                                    uint16_t word,
                                    size_t n_words) {
	return libc_memrchrw(haystack, word, n_words);
}
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_DWORDS * 4'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_memrchrl)(void const *__restrict haystack,
                                    uint32_t dword,
                                    size_t n_dwords) {
	return libc_memrchrl(haystack, dword, n_dwords);
}
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_rawmemchrw)(void const *__restrict haystack,
                                      uint16_t word) {
	return libc_rawmemchrw(haystack, word);
}
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_rawmemchrl)(void const *__restrict haystack,
                                      uint32_t dword) {
	return libc_rawmemchrl(haystack, dword);
}
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK - 2' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_rawmemrchrw)(void const *__restrict haystack,
                                       uint16_t word) {
	return libc_rawmemrchrw(haystack, word);
}
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK - 4' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_rawmemrchrl)(void const *__restrict haystack,
                                       uint32_t dword) {
	return libc_rawmemrchrl(haystack, dword);
}
/* Same as `memchrw', but return `HAYSTACK + N_WORDS * 2', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_memendw)(void const *__restrict haystack,
                                   uint16_t word,
                                   size_t n_bytes) {
	return libc_memendw(haystack, word, n_bytes);
}
/* Same as `memchrl', but return `HAYSTACK + N_DWORDS * 4', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_memendl)(void const *__restrict haystack,
                                   uint32_t dword,
                                   size_t n_bytes) {
	return libc_memendl(haystack, dword, n_bytes);
}
/* Same as `memrchrw', but return `HAYSTACK - 2', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_memrendw)(void const *__restrict haystack,
                                    uint16_t word,
                                    size_t n_words) {
	return libc_memrendw(haystack, word, n_words);
}
/* Same as `memrchrl', but return `HAYSTACK - 4', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_memrendl)(void const *__restrict haystack,
                                    uint32_t dword,
                                    size_t n_dwords) {
	return libc_memrendl(haystack, dword, n_dwords);
}
/* Same as `memendw', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `HAYSTACK + N_DWORDS * 2' if the given `NEEDLE' wasn't found */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_memlenw)(void const *__restrict haystack,
                                   uint16_t word,
                                   size_t n_words) {
	return libc_memlenw(haystack, word, n_words);
}
/* Same as `memendl', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `HAYSTACK + N_DWORDS * 4' if the given `NEEDLE' wasn't found */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_memlenl)(void const *__restrict haystack,
                                   uint32_t dword,
                                   size_t n_dwords) {
	return libc_memlenl(haystack, dword, n_dwords);
}
/* Same as `memrendw', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 2' if the given `NEEDLE' wasn't found */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_memrlenw)(void const *__restrict haystack,
                                    uint16_t word,
                                    size_t n_words) {
	return libc_memrlenw(haystack, word, n_words);
}
/* Same as `memrendl', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 4' if the given `NEEDLE' wasn't found */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_memrlenl)(void const *__restrict haystack,
                                    uint32_t dword,
                                    size_t n_dwords) {
	return libc_memrlenl(haystack, dword, n_dwords);
}
/* Same as `rawmemchrw', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_rawmemlenw)(void const *__restrict haystack,
                                      uint16_t word) {
	return libc_rawmemlenw(haystack, word);
}
/* Same as `rawmemchrl', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_rawmemlenl)(void const *__restrict haystack,
                                      uint32_t dword) {
	return libc_rawmemlenl(haystack, dword);
}
/* Same as `rawmemrchrw', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_rawmemrlenw)(void const *__restrict haystack,
                                       uint16_t word) {
	return libc_rawmemrlenw(haystack, word);
}
/* Same as `rawmemrchrl', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_rawmemrlenl)(void const *__restrict haystack,
                                       uint32_t dword) {
	return libc_rawmemrlenl(haystack, dword);
}
/* Copy memory between non-overlapping memory blocks. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_memcpyq)(void *__restrict dst,
                                   void const *__restrict src,
                                   size_t n_qwords) {
	return libc_memcpyq(dst, src, n_qwords);
}
/* Same as `memcpyq', but return `DST + N_QWORDS', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_mempcpyq)(void *__restrict dst,
                                    void const *__restrict src,
                                    size_t n_qwords) {
	return libc_mempcpyq(dst, src, n_qwords);
}
/* Move memory between potentially overlapping memory blocks. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_memmoveq)(void *dst,
                                    void const *src,
                                    size_t n_qwords) {
	return libc_memmoveq(dst, src, n_qwords);
}
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_mempmoveq)(void *__restrict dst,
                                     void const *__restrict src,
                                     size_t n_qwords) {
	return libc_mempmoveq(dst, src, n_qwords);
}
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_QWORDS') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_memmoveupq)(void *dst,
                                      void const *src,
                                      size_t n_qwords) {
	return libc_memmoveupq(dst, src, n_qwords);
}
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_QWORDS') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_memmovedownq)(void *dst,
                                        void const *src,
                                        size_t n_qwords) {
	return libc_memmovedownq(dst, src, n_qwords);
}
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST >= SRC || !N_QWORDS') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_mempmoveupq)(void *__restrict dst,
                                       void const *__restrict src,
                                       size_t n_qwords) {
	return libc_mempmoveupq(dst, src, n_qwords);
}
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST <= SRC || !N_QWORDS') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_mempmovedownq)(void *__restrict dst,
                                         void const *__restrict src,
                                         size_t n_qwords) {
	return libc_mempmovedownq(dst, src, n_qwords);
}
/* Fill memory with a given qword */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_memsetq)(void *__restrict dst,
                                   uint64_t qword,
                                   size_t n_qwords) {
	return libc_memsetq(dst, qword, n_qwords);
}
/* Same as `memsetq', but return `DST + N_QWORDS', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_mempsetq)(void *__restrict dst,
                                    uint64_t qword,
                                    size_t n_qwords) {
	return libc_mempsetq(dst, qword, n_qwords);
}
/* Compare memory buffers and return the difference of the first non-matching qword */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int64_t
NOTHROW_NCX(LIBDCALL libd_memcmpq)(void const *s1,
                                   void const *s2,
                                   size_t n_dwords) {
	return libc_memcmpq(s1, s2, n_dwords);
}
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_memchrq)(void const *__restrict haystack,
                                   uint64_t qword,
                                   size_t n_qwords) {
	return libc_memchrq(haystack, qword, n_qwords);
}
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_memrchrq)(void const *__restrict haystack,
                                    uint64_t qword,
                                    size_t n_qwords) {
	return libc_memrchrq(haystack, qword, n_qwords);
}
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_rawmemchrq)(void const *__restrict haystack,
                                      uint64_t qword) {
	return libc_rawmemchrq(haystack, qword);
}
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK - 8' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_rawmemrchrq)(void const *__restrict haystack,
                                       uint64_t qword) {
	return libc_rawmemrchrq(haystack, qword);
}
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_memendq)(void const *__restrict haystack,
                                   uint64_t qword,
                                   size_t n_bytes) {
	return libc_memendq(haystack, qword, n_bytes);
}
/* Same as `memrchrq', but return `HAYSTACK - 8', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_memrendq)(void const *__restrict haystack,
                                    uint64_t qword,
                                    size_t n_qwords) {
	return libc_memrendq(haystack, qword, n_qwords);
}
/* Same as `memendq', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `N_QWORDS' if the given `NEEDLE' wasn't found */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_memlenq)(void const *__restrict haystack,
                                   uint64_t qword,
                                   size_t n_qwords) {
	return libc_memlenq(haystack, qword, n_qwords);
}
/* Same as `memrendq', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 8' if the given `NEEDLE' wasn't found */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_memrlenq)(void const *__restrict haystack,
                                    uint64_t qword,
                                    size_t n_qwords) {
	return libc_memrlenq(haystack, qword, n_qwords);
}
/* Same as `rawmemchrq', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_rawmemlenq)(void const *__restrict haystack,
                                      uint64_t qword) {
	return libc_rawmemlenq(haystack, qword);
}
/* Same as `rawmemrchrq', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_rawmemrlenq)(void const *__restrict haystack,
                                       uint64_t qword) {
	return libc_rawmemrlenq(haystack, qword);
}
/* Same as `memchr', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_memxchr)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
	return libc_memxchr(haystack, needle, n_bytes);
}
/* Same as `memrchr', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_memrxchr)(void const *__restrict haystack,
                                    int needle,
                                    size_t n_bytes) {
	return libc_memrxchr(haystack, needle, n_bytes);
}
/* Same as `rawmemchr', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_rawmemxchr)(void const *__restrict haystack,
                                      int needle) {
	return libc_rawmemxchr(haystack, needle);
}
/* Same as `rawmemrchr', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_rawmemrxchr)(void const *__restrict haystack,
                                       int needle) {
	return libc_rawmemrxchr(haystack, needle);
}
/* Same as `memend', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_memxend)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
	return libc_memxend(haystack, needle, n_bytes);
}
/* Same as `memrend', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_memrxend)(void const *__restrict haystack,
                                    int needle,
                                    size_t n_bytes) {
	return libc_memrxend(haystack, needle, n_bytes);
}
/* Same as `memlen', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_memxlen)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
	return libc_memxlen(haystack, needle, n_bytes);
}
/* Same as `memrlen', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_memrxlen)(void const *__restrict haystack,
                                    int needle,
                                    size_t n_bytes) {
	return libc_memrxlen(haystack, needle, n_bytes);
}
/* Same as `rawmemlen', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_rawmemxlen)(void const *__restrict haystack,
                                      int needle) {
	return libc_rawmemxlen(haystack, needle);
}
/* Same as `rawmemrlen', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_rawmemrxlen)(void const *__restrict haystack,
                                       int needle) {
	return libc_rawmemrxlen(haystack, needle);
}
/* Same as `memchrw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_memxchrw)(void const *__restrict haystack,
                                    uint16_t word,
                                    size_t n_words) {
	return libc_memxchrw(haystack, word, n_words);
}
/* Same as `memchrl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_memxchrl)(void const *__restrict haystack,
                                    uint32_t dword,
                                    size_t n_dwords) {
	return libc_memxchrl(haystack, dword, n_dwords);
}
/* Same as `memrchrw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_memrxchrw)(void const *__restrict haystack,
                                     uint16_t word,
                                     size_t n_words) {
	return libc_memrxchrw(haystack, word, n_words);
}
/* Same as `memrchrl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_memrxchrl)(void const *__restrict haystack,
                                     uint32_t dword,
                                     size_t n_dwords) {
	return libc_memrxchrl(haystack, dword, n_dwords);
}
/* Same as `rawmemchrw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_rawmemxchrw)(void const *__restrict haystack,
                                       uint16_t word) {
	return libc_rawmemxchrw(haystack, word);
}
/* Same as `rawmemchrl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_rawmemxchrl)(void const *__restrict haystack,
                                       uint32_t dword) {
	return libc_rawmemxchrl(haystack, dword);
}
/* Same as `rawmemrchrw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_rawmemrxchrw)(void const *__restrict haystack,
                                        uint16_t word) {
	return libc_rawmemrxchrw(haystack, word);
}
/* Same as `rawmemrchrl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_rawmemrxchrl)(void const *__restrict haystack,
                                        uint32_t dword) {
	return libc_rawmemrxchrl(haystack, dword);
}
/* Same as `memendw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_memxendw)(void const *__restrict haystack,
                                    uint16_t word,
                                    size_t n_bytes) {
	return libc_memxendw(haystack, word, n_bytes);
}
/* Same as `memendl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_memxendl)(void const *__restrict haystack,
                                    uint32_t dword,
                                    size_t n_bytes) {
	return libc_memxendl(haystack, dword, n_bytes);
}
/* Same as `memrendw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_memrxendw)(void const *__restrict haystack,
                                     uint16_t word,
                                     size_t n_words) {
	return libc_memrxendw(haystack, word, n_words);
}
/* Same as `memrendl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_memrxendl)(void const *__restrict haystack,
                                     uint32_t dword,
                                     size_t n_dwords) {
	return libc_memrxendl(haystack, dword, n_dwords);
}
/* Same as `memlenw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_memxlenw)(void const *__restrict haystack,
                                    uint16_t word,
                                    size_t n_words) {
	return libc_memxlenw(haystack, word, n_words);
}
/* Same as `memlenl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_memxlenl)(void const *__restrict haystack,
                                    uint32_t dword,
                                    size_t n_dwords) {
	return libc_memxlenl(haystack, dword, n_dwords);
}
/* Same as `memrlenw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_memrxlenw)(void const *__restrict haystack,
                                     uint16_t word,
                                     size_t n_words) {
	return libc_memrxlenw(haystack, word, n_words);
}
/* Same as `memrlenl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_memrxlenl)(void const *__restrict haystack,
                                     uint32_t dword,
                                     size_t n_dwords) {
	return libc_memrxlenl(haystack, dword, n_dwords);
}
/* Same as `rawmemlenw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_rawmemxlenw)(void const *__restrict haystack,
                                       uint16_t word) {
	return libc_rawmemxlenw(haystack, word);
}
/* Same as `rawmemlenl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_rawmemxlenl)(void const *__restrict haystack,
                                       uint32_t dword) {
	return libc_rawmemxlenl(haystack, dword);
}
/* Same as `rawmemrlenw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_rawmemrxlenw)(void const *__restrict haystack,
                                        uint16_t word) {
	return libc_rawmemrxlenw(haystack, word);
}
/* Same as `rawmemrlenl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_rawmemrxlenl)(void const *__restrict haystack,
                                        uint32_t dword) {
	return libc_rawmemrxlenl(haystack, dword);
}
/* Same as `memchrq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_memxchrq)(void const *__restrict haystack,
                                    uint64_t qword,
                                    size_t n_qwords) {
	return libc_memxchrq(haystack, qword, n_qwords);
}
/* Same as `memrchrq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_memrxchrq)(void const *__restrict haystack,
                                     uint64_t qword,
                                     size_t n_qwords) {
	return libc_memrxchrq(haystack, qword, n_qwords);
}
/* Same as `rawmemchrq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_rawmemxchrq)(void const *__restrict haystack,
                                       uint64_t qword) {
	return libc_rawmemxchrq(haystack, qword);
}
/* Same as `rawmemrchrq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_rawmemrxchrq)(void const *__restrict haystack,
                                        uint64_t qword) {
	return libc_rawmemrxchrq(haystack, qword);
}
/* Same as `memendq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_memxendq)(void const *__restrict haystack,
                                    uint64_t qword,
                                    size_t n_bytes) {
	return libc_memxendq(haystack, qword, n_bytes);
}
/* Same as `memrendq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_memrxendq)(void const *__restrict haystack,
                                     uint64_t qword,
                                     size_t n_qwords) {
	return libc_memrxendq(haystack, qword, n_qwords);
}
/* Same as `memlenq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_memxlenq)(void const *__restrict haystack,
                                    uint64_t qword,
                                    size_t n_qwords) {
	return libc_memxlenq(haystack, qword, n_qwords);
}
/* Same as `memrlenq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_memrxlenq)(void const *__restrict haystack,
                                     uint64_t qword,
                                     size_t n_qwords) {
	return libc_memrxlenq(haystack, qword, n_qwords);
}
/* Same as `rawmemlenq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_rawmemxlenq)(void const *__restrict haystack,
                                       uint64_t qword) {
	return libc_rawmemxlenq(haystack, qword);
}
/* Same as `rawmemrlenq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_rawmemrxlenq)(void const *__restrict haystack,
                                        uint64_t qword) {
	return libc_rawmemrxlenq(haystack, qword);
}
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd_memmoveup)(void *dst,
                                     void const *src,
                                     size_t n_bytes) {
	return libc_memmoveup(dst, src, n_bytes);
}
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd_memmovedown)(void *dst,
                                       void const *src,
                                       size_t n_bytes) {
	return libc_memmovedown(dst, src, n_bytes);
}
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd_memcpyc)(void *__restrict dst,
                                   void const *__restrict src,
                                   size_t elem_count,
                                   size_t elem_size) {
	return libc_memcpyc(dst, src, elem_count, elem_size);
}
/* Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd_mempcpyc)(void *__restrict dst,
                                    void const *__restrict src,
                                    size_t elem_count,
                                    size_t elem_size) {
	return libc_mempcpyc(dst, src, elem_count, elem_size);
}
/* Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd_memmovec)(void *dst,
                                    void const *src,
                                    size_t elem_count,
                                    size_t elem_size) {
	return libc_memmovec(dst, src, elem_count, elem_size);
}
/* Same as `memmovec', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd_mempmovec)(void *dst,
                                     void const *src,
                                     size_t elem_count,
                                     size_t elem_size) {
	return libc_mempmovec(dst, src, elem_count, elem_size);
}
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd_memmoveupc)(void *dst,
                                      void const *src,
                                      size_t elem_count,
                                      size_t elem_size) {
	return libc_memmoveupc(dst, src, elem_count, elem_size);
}
/* Same as `memmoveupc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd_mempmoveupc)(void *dst,
                                       void const *src,
                                       size_t elem_count,
                                       size_t elem_size) {
	return libc_mempmoveupc(dst, src, elem_count, elem_size);
}
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd_memmovedownc)(void *dst,
                                        void const *src,
                                        size_t elem_count,
                                        size_t elem_size) {
	return libc_memmovedownc(dst, src, elem_count, elem_size);
}
/* Same as `memmovedownc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd_mempmovedownc)(void *dst,
                                         void const *src,
                                         size_t elem_count,
                                         size_t elem_size) {
	return libc_mempmovedownc(dst, src, elem_count, elem_size);
}
/* Same as `STR + strlen(STR)' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strend)(char const *__restrict string) {
	return libc_strend(string);
}
/* Same as `STR + strnlen(STR, MAX_CHARS)' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strnend)(char const *__restrict string,
                                   size_t maxlen) {
	return libc_strnend(string, maxlen);
}
/* Same as `strchr', but don't exceed `MAX_CHARS' characters. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strnchr)(char const *__restrict haystack,
                                   int needle,
                                   size_t maxlen) {
	return libc_strnchr(haystack, needle, maxlen);
}
/* Same as `strrchr', but don't exceed `MAX_CHARS' characters. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strnrchr)(char const *__restrict haystack,
                                    int needle,
                                    size_t maxlen) {
	return libc_strnrchr(haystack, needle, maxlen);
}
/* Same as `strrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strrchrnul)(char const *__restrict haystack,
                                      int needle) {
	return libc_strrchrnul(haystack, needle);
}
/* Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strnchrnul)(char const *__restrict haystack,
                                      int needle,
                                      size_t maxlen) {
	return libc_strnchrnul(haystack, needle, maxlen);
}
/* Same as `strnrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strnrchrnul)(char const *__restrict haystack,
                                       int needle,
                                       size_t maxlen) {
	return libc_strnrchrnul(haystack, needle, maxlen);
}
/* Same as `strchrnul', but return the offset from `STR', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_stroff)(char const *__restrict haystack,
                                  int needle) {
	return libc_stroff(haystack, needle);
}
/* Same as `strrchrnul', but return the offset from `STR', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_strroff)(char const *__restrict haystack,
                                   int needle) {
	return libc_strroff(haystack, needle);
}
/* Same as `strnchrnul', but return the offset from `STR', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_strnoff)(char const *__restrict haystack,
                                   int needle,
                                   size_t maxlen) {
	return libc_strnoff(haystack, needle, maxlen);
}
/* Same as `strnrchrnul', but return the offset from `STR', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_strnroff)(char const *__restrict haystack,
                                    int needle,
                                    size_t maxlen) {
	return libc_strnroff(haystack, needle, maxlen);
}
/* Same as `memset', but return `DST + N_BYTES', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_mempset)(void *__restrict dst,
                                   int byte,
                                   size_t n_bytes) {
	return libc_mempset(dst, byte, n_bytes);
}
/* Same as `memmove', but return `DST + N_BYTES', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd_mempmove)(void *dst,
                                    void const *src,
                                    size_t n_bytes) {
	return libc_mempmove(dst, src, n_bytes);
}
/* Same as `memmoveup', but return `DST + N_BYTES', rather than `DST' (assumes that `DST >= SRC || !N_BYTES') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd_mempmoveup)(void *dst,
                                      void const *src,
                                      size_t n_bytes) {
	return libc_mempmoveup(dst, src, n_bytes);
}
/* Same as `memmovedown', but return `DST + N_BYTES', rather than `DST' (assumes that `DST <= SRC || !N_BYTES') */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd_mempmovedown)(void *dst,
                                        void const *src,
                                        size_t n_bytes) {
	return libc_mempmovedown(dst, src, n_bytes);
}
/* Same as `memrchr' without a search limit, starting at `HAYSTACK - 1' */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_rawmemrchr)(void const *__restrict haystack,
                                      int needle) {
	return libc_rawmemrchr(haystack, needle);
}
/* Same as `memchr', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_memend)(void const *__restrict haystack,
                                  int needle,
                                  size_t n_bytes) {
	return libc_memend(haystack, needle, n_bytes);
}
/* Same as `memrchr', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_memrend)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
	return libc_memrend(haystack, needle, n_bytes);
}
/* Same as `memend', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `n_bytes' if the given `NEEDLE' wasn't found */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_memlen)(void const *__restrict haystack,
                                  int needle,
                                  size_t n_bytes) {
	return libc_memlen(haystack, needle, n_bytes);
}
/* Same as `memrend', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1' if the given `NEEDLE' wasn't found */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_memrlen)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
	return libc_memrlen(haystack, needle, n_bytes);
}
/* Same as `rawmemchr', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_rawmemlen)(void const *__restrict haystack,
                                     int needle) {
	return libc_rawmemlen(haystack, needle);
}
/* Same as `rawmemrchr', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_rawmemrlen)(void const *__restrict haystack,
                                      int needle) {
	return libc_rawmemrlen(haystack, needle);
}
/* Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) void *
NOTHROW_NCX(LIBDCALL libd_memrmem)(void const *haystack,
                                   size_t haystacklen,
                                   void const *needle,
                                   size_t needlelen) {
	return libc_memrmem(haystack, haystacklen, needle, needlelen);
}
/* Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_mempatw)(void *__restrict dst,
                                   uint16_t pattern,
                                   size_t n_bytes) {
	return libc_mempatw(dst, pattern, n_bytes);
}
/* Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_mempatl)(void *__restrict dst,
                                   uint32_t pattern,
                                   size_t n_bytes) {
	return libc_mempatl(dst, pattern, n_bytes);
}
/* Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_mempatq)(void *__restrict dst,
                                   uint64_t pattern,
                                   size_t n_bytes) {
	return libc_mempatq(dst, pattern, n_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_memcasecmp)(void const *s1,
                                      void const *s2,
                                      size_t n_bytes) {
	return libc_memcasecmp(s1, s2, n_bytes);
}
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) void *
NOTHROW_NCX(LIBDCALL libd_memcasemem)(void const *haystack,
                                      size_t haystacklen,
                                      void const *needle,
                                      size_t needlelen) {
	return libc_memcasemem(haystack, haystacklen, needle, needlelen);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_memcasecmp_l)(void const *s1,
                                        void const *s2,
                                        size_t n_bytes,
                                        locale_t locale) {
	return libc_memcasecmp_l(s1, s2, n_bytes, locale);
}
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored using the given `locale' (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) void *
NOTHROW_NCX(LIBDCALL libd_memcasemem_l)(void const *haystack,
                                        size_t haystacklen,
                                        void const *needle,
                                        size_t needlelen,
                                        locale_t locale) {
	return libc_memcasemem_l(haystack, haystacklen, needle, needlelen, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_strcasestr_l)(char const *haystack,
                                        char const *needle,
                                        locale_t locale) {
	return libc_strcasestr_l(haystack, needle, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBDCALL libd_strsignal_s)(int signum) {
	return libc_strsignal_s(signum);
}
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
INTERN ATTR_SECTION(".text.crt.dos.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_LIBC_PRINTF(1, 0) char *
NOTHROW_NCX(LIBDCALL libd_vstrdupf)(char const *__restrict format,
                                    va_list args) {
	return libc_vstrdupf(format, args);
}
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
INTERN ATTR_SECTION(".text.crt.dos.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_LIBC_PRINTF(1, 0) char *
NOTHROW_NCX(VLIBDCALL libd_strdupf)(char const *__restrict format,
                                    ...) {
	char * result;
	va_list args;
	va_start(args, format);
	result = libc_vstrdupf(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wildstrcmp)(char const *pattern,
                                      char const *string) {
	return libc_wildstrcmp(pattern, string);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wildstrcasecmp)(char const *pattern,
                                          char const *string) {
	return libc_wildstrcasecmp(pattern, string);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_strcmp)(char const *s1,
                                        char const *s2) {
	return libc_fuzzy_strcmp(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_strncmp)(char const *s1,
                                         size_t s1_maxlen,
                                         char const *s2,
                                         size_t s2_maxlen) {
	return libc_fuzzy_strncmp(s1, s1_maxlen, s2, s2_maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_strcasecmp)(char const *s1,
                                            char const *s2) {
	return libc_fuzzy_strcasecmp(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_strncasecmp)(char const *s1,
                                             size_t s1_maxlen,
                                             char const *s2,
                                             size_t s2_maxlen) {
	return libc_fuzzy_strncasecmp(s1, s1_maxlen, s2, s2_maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_memcmp)(void const *s1,
                                        size_t s1_bytes,
                                        void const *s2,
                                        size_t s2_bytes) {
	return libc_fuzzy_memcmp(s1, s1_bytes, s2, s2_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_memcasecmp)(void const *s1,
                                            size_t s1_bytes,
                                            void const *s2,
                                            size_t s2_bytes) {
	return libc_fuzzy_memcasecmp(s1, s1_bytes, s2, s2_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_strcasecmp_l)(char const *s1,
                                              char const *s2,
                                              locale_t locale) {
	return libc_fuzzy_strcasecmp_l(s1, s2, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_strncasecmp_l)(char const *s1,
                                               size_t s1_maxlen,
                                               char const *s2,
                                               size_t s2_maxlen,
                                               locale_t locale) {
	return libc_fuzzy_strncasecmp_l(s1, s1_maxlen, s2, s2_maxlen, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wildstrcasecmp_l)(char const *pattern,
                                            char const *string,
                                            locale_t locale) {
	return libc_wildstrcasecmp_l(pattern, string, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_memcasecmp_l)(void const *s1,
                                              size_t s1_bytes,
                                              void const *s2,
                                              size_t s2_bytes,
                                              locale_t locale) {
	return libc_fuzzy_memcasecmp_l(s1, s1_bytes, s2, s2_bytes, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_memcmpw)(void const *s1,
                                         size_t s1_words,
                                         void const *s2,
                                         size_t s2_words) {
	return libc_fuzzy_memcmpw(s1, s1_words, s2, s2_words);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_memcmpl)(void const *s1,
                                         size_t s1_dwords,
                                         void const *s2,
                                         size_t s2_dwords) {
	return libc_fuzzy_memcmpl(s1, s1_dwords, s2, s2_dwords);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_memcmpq)(void const *s1,
                                         size_t s1_qwords,
                                         void const *s2,
                                         size_t s2_qwords) {
	return libc_fuzzy_memcmpq(s1, s1_qwords, s2, s2_qwords);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_strncoll)(char const *s1,
                                    char const *s2,
                                    size_t maxlen) {
	return libc_strncoll(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_strcasecoll)(char const *s1,
                                       char const *s2) {
	return libc_strcasecoll(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_strncasecoll)(char const *s1,
                                        char const *s2,
                                        size_t maxlen) {
	return libc_strncasecoll(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strnrev)(char *__restrict str,
                                   size_t maxlen) {
	return libc_strnrev(str, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strnlwr)(char *__restrict str,
                                   size_t maxlen) {
	return libc_strnlwr(str, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strnupr)(char *__restrict str,
                                   size_t maxlen) {
	return libc_strnupr(str, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_strncoll_l)(char const *s1,
                                      char const *s2,
                                      size_t maxlen,
                                      locale_t locale) {
	return libc_strncoll_l(s1, s2, maxlen, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_strcasecoll_l)(char const *s1,
                                         char const *s2,
                                         locale_t locale) {
	return libc_strcasecoll_l(s1, s2, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_strncasecoll_l)(char const *s1,
                                          char const *s2,
                                          size_t maxlen,
                                          locale_t locale) {
	return libc_strncasecoll_l(s1, s2, maxlen, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strlwr_l)(char *__restrict str,
                                    locale_t locale) {
	return libc_strlwr_l(str, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strupr_l)(char *__restrict str,
                                    locale_t locale) {
	return libc_strupr_l(str, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strnlwr_l)(char *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
	return libc_strnlwr_l(str, maxlen, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strnupr_l)(char *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
	return libc_strnupr_l(str, maxlen, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd_memrev)(void *__restrict base,
                                  size_t n_bytes) {
	return libc_memrev(base, n_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBDCALL libd_memrevw)(void *__restrict base,
                                   size_t n_words) {
	return libc_memrevw(base, n_words);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBDCALL libd_memrevl)(void *__restrict base,
                                   size_t n_dwords) {
	return libc_memrevl(base, n_dwords);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBDCALL libd_memrevq)(void *__restrict base,
                                   size_t n_qwords) {
	return libc_memrevq(base, n_qwords);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strlwr)(char *__restrict str) {
	return libc_strlwr(str);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strupr)(char *__restrict str) {
	return libc_strupr(str);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strset)(char *__restrict str,
                                  int ch) {
	return libc_strset(str, ch);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strnset)(char *__restrict str,
                                   int ch,
                                   size_t maxlen) {
	return libc_strnset(str, ch, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_strrev)(char *__restrict str) {
	return libc_strrev(str);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBDCALL libd__strset_s)(char *dst,
                                     size_t dstsize,
                                     int ch) {
	return libc__strset_s(dst, dstsize, ch);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBDCALL libd_memcpy_s)(void *dst,
                                    rsize_t dstlength,
                                    void const *src,
                                    rsize_t srclength) {
	return libc_memcpy_s(dst, dstlength, src, srclength);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBDCALL libd_memmove_s)(void *dst,
                                     rsize_t dstlength,
                                     void const *src,
                                     rsize_t srclength) {
	return libc_memmove_s(dst, dstlength, src, srclength);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") errno_t
NOTHROW_NCX(LIBDCALL libd_strcpy_s)(char *dst,
                                    size_t dstsize,
                                    char const *src) {
	return libc_strcpy_s(dst, dstsize, src);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") errno_t
NOTHROW_NCX(LIBDCALL libd_strcat_s)(char *dst,
                                    size_t dstsize,
                                    char const *src) {
	return libc_strcat_s(dst, dstsize, src);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") errno_t
NOTHROW_NCX(LIBDCALL libd_strncat_s)(char *dst,
                                     rsize_t dstsize,
                                     const char *src,
                                     rsize_t maxlen) {
	return libc_strncat_s(dst, dstsize, src, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") errno_t
NOTHROW_NCX(LIBDCALL libd_strncpy_s)(char *dst,
                                     size_t dstsize,
                                     char const *src,
                                     size_t maxlen) {
	return libc_strncpy_s(dst, dstsize, src, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.errno") WUNUSED char *
NOTHROW_RPC(LIBDCALL libd__strerror)(char const *message) {
	return libc__strerror(message);
}
INTERN ATTR_SECTION(".text.crt.dos.errno") NONNULL((1)) errno_t
NOTHROW_RPC(LIBDCALL libd__strerror_s)(char *__restrict buf,
                                       size_t buflen,
                                       char const *message) {
	return libc__strerror_s(buf, buflen, message);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") errno_t
NOTHROW_NCX(LIBDCALL libd__strlwr_s)(char *buf,
                                     size_t buflen) {
	return libc__strlwr_s(buf, buflen);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") errno_t
NOTHROW_NCX(LIBDCALL libd__strupr_s)(char *buf,
                                     size_t buflen) {
	return libc__strupr_s(buf, buflen);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") errno_t
NOTHROW_NCX(LIBDCALL libd__strlwr_s_l)(char *buf,
                                       size_t buflen,
                                       locale_t locale) {
	return libc__strlwr_s_l(buf, buflen, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") errno_t
NOTHROW_NCX(LIBDCALL libd__strupr_s_l)(char *buf,
                                       size_t buflen,
                                       locale_t locale) {
	return libc__strupr_s_l(buf, buflen, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.string.memory") errno_t
NOTHROW_NCX(LIBDCALL libd__strnset_s)(char *__restrict buf,
                                      size_t buflen,
                                      int ch,
                                      size_t maxlen) {
	return libc__strnset_s(buf, buflen, ch, maxlen);
}
/* Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If found, return a pointer to its location within `str', else return `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_strnstr)(char const *haystack,
                                   char const *needle,
                                   size_t haystack_maxlen) {
	return libc_strnstr(haystack, needle, haystack_maxlen);
}
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
INTERN ATTR_SECTION(".text.crt.dos.bsd.strstat") NONNULL((2)) void
NOTHROW_NCX(LIBDCALL libd_strmode)(mode_t mode,
                                   char p[12]) {
	libc_strmode(mode, p);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$memcpy, libd_memcpy);
DEFINE_PUBLIC_ALIAS(DOS$memmove, libd_memmove);
DEFINE_PUBLIC_ALIAS(DOS$memset, libd_memset);
DEFINE_PUBLIC_ALIAS(DOS$memcmp, libd_memcmp);
DEFINE_PUBLIC_ALIAS(DOS$memchr, libd_memchr);
DEFINE_PUBLIC_ALIAS(DOS$strlen, libd_strlen);
DEFINE_PUBLIC_ALIAS(DOS$strchr, libd_strchr);
DEFINE_PUBLIC_ALIAS(DOS$strrchr, libd_strrchr);
DEFINE_PUBLIC_ALIAS(DOS$strcmp, libd_strcmp);
DEFINE_PUBLIC_ALIAS(DOS$strncmp, libd_strncmp);
DEFINE_PUBLIC_ALIAS(DOS$strstr, libd_strstr);
DEFINE_PUBLIC_ALIAS(DOS$strcpy, libd_strcpy);
DEFINE_PUBLIC_ALIAS(DOS$strncpy, libd_strncpy);
DEFINE_PUBLIC_ALIAS(DOS$strcat, libd_strcat);
DEFINE_PUBLIC_ALIAS(DOS$strncat, libd_strncat);
DEFINE_PUBLIC_ALIAS(DOS$strcspn, libd_strcspn);
DEFINE_PUBLIC_ALIAS(DOS$strspn, libd_strspn);
DEFINE_PUBLIC_ALIAS(DOS$strpbrk, libd_strpbrk);
DEFINE_PUBLIC_ALIAS(DOS$strtok, libd_strtok);
DEFINE_PUBLIC_ALIAS(DOS$strcoll, libd_strcoll);
DEFINE_PUBLIC_ALIAS(DOS$strxfrm, libd_strxfrm);
DEFINE_PUBLIC_ALIAS(DOS$strerror, libd_strerror);
DEFINE_PUBLIC_ALIAS(DOS$strnlen, libd_strnlen);
DEFINE_PUBLIC_ALIAS(DOS$__stpcpy, libd_stpcpy);
DEFINE_PUBLIC_ALIAS(DOS$stpcpy, libd_stpcpy);
DEFINE_PUBLIC_ALIAS(DOS$__stpncpy, libd_stpncpy);
DEFINE_PUBLIC_ALIAS(DOS$stpncpy, libd_stpncpy);
DEFINE_PUBLIC_ALIAS(DOS$_strcoll_l, libd_strcoll_l);
DEFINE_PUBLIC_ALIAS(DOS$__strcoll_l, libd_strcoll_l);
DEFINE_PUBLIC_ALIAS(DOS$strcoll_l, libd_strcoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_strxfrm_l, libd_strxfrm_l);
DEFINE_PUBLIC_ALIAS(DOS$__strxfrm_l, libd_strxfrm_l);
DEFINE_PUBLIC_ALIAS(DOS$strxfrm_l, libd_strxfrm_l);
DEFINE_PUBLIC_ALIAS(DOS$strerror_l, libd_strerror_l);
DEFINE_PUBLIC_ALIAS(DOS$strsignal, libd_strsignal);
DEFINE_PUBLIC_ALIAS(DOS$__strndup, libd_strndup);
DEFINE_PUBLIC_ALIAS(DOS$strndup, libd_strndup);
DEFINE_PUBLIC_ALIAS(DOS$_strdup, libd_strdup);
DEFINE_PUBLIC_ALIAS(DOS$__strdup, libd_strdup);
DEFINE_PUBLIC_ALIAS(DOS$strdup, libd_strdup);
DEFINE_PUBLIC_ALIAS(DOS$strtok_s, libd_strtok_r);
DEFINE_PUBLIC_ALIAS(DOS$__strtok_r, libd_strtok_r);
DEFINE_PUBLIC_ALIAS(DOS$strtok_r, libd_strtok_r);
DEFINE_PUBLIC_ALIAS(DOS$memrchr, libd_memrchr);
DEFINE_PUBLIC_ALIAS(DOS$rawmemchr, libd_rawmemchr);
DEFINE_PUBLIC_ALIAS(DOS$strchrnul, libd_strchrnul);
DEFINE_PUBLIC_ALIAS(DOS$basename, libd_basename);
DEFINE_PUBLIC_ALIAS(DOS$__strcasestr, libd_strcasestr);
DEFINE_PUBLIC_ALIAS(DOS$strcasestr, libd_strcasestr);
DEFINE_PUBLIC_ALIAS(DOS$memmem, libd_memmem);
DEFINE_PUBLIC_ALIAS(DOS$__strverscmp, libd_strverscmp);
DEFINE_PUBLIC_ALIAS(DOS$strverscmp, libd_strverscmp);
DEFINE_PUBLIC_ALIAS(DOS$mempcpy, libd_mempcpy);
DEFINE_PUBLIC_ALIAS(DOS$strfry, libd_strfry);
DEFINE_PUBLIC_ALIAS(DOS$memfrob, libd_memfrob);
DEFINE_PUBLIC_ALIAS(DOS$_stricmp_l, libd_strcasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$__strcasecmp_l, libd_strcasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$strcasecmp_l, libd_strcasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$_strnicmp_l, libd_strncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$_strncmpi_l, libd_strncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$__strncasecmp_l, libd_strncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$strncasecmp_l, libd_strncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$__strerror_r, libd_strerror_r);
DEFINE_PUBLIC_ALIAS(DOS$strerror_r, libd_strerror_r);
DEFINE_PUBLIC_ALIAS(DOS$__xpg_strerror_r, libd___xpg_strerror_r);
DEFINE_PUBLIC_ALIAS(DOS$strsep, libd_strsep);
DEFINE_PUBLIC_ALIAS(DOS$_stricmp, libd_strcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$_strcmpi, libd_strcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$stricmp, libd_strcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$strcmpi, libd_strcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$__strcasecmp, libd_strcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$strcasecmp, libd_strcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$_strnicmp, libd_strncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$strnicmp, libd_strncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$_strncmpi, libd_strncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$strncmpi, libd_strncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$strncasecmp, libd_strncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$__ffs, libd_ffs);
DEFINE_PUBLIC_ALIAS(DOS$ffs, libd_ffs);
DEFINE_PUBLIC_ALIAS(DOS$ffsl, libd_ffsl);
DEFINE_PUBLIC_ALIAS(DOS$ffsll, libd_ffsll);
DEFINE_PUBLIC_ALIAS(DOS$strlcat, libd_strlcat);
DEFINE_PUBLIC_ALIAS(DOS$strlcpy, libd_strlcpy);
DEFINE_PUBLIC_ALIAS(DOS$_memccpy, libd_memccpy);
DEFINE_PUBLIC_ALIAS(DOS$memccpy, libd_memccpy);
DEFINE_PUBLIC_ALIAS(DOS$wmemcpy, libd_memcpyw);
DEFINE_PUBLIC_ALIAS(DOS$memcpyw, libd_memcpyw);
DEFINE_PUBLIC_ALIAS(DOS$wmempcpy, libd_mempcpyw);
DEFINE_PUBLIC_ALIAS(DOS$mempcpyw, libd_mempcpyw);
DEFINE_PUBLIC_ALIAS(DOS$memcpyl, libd_memcpyl);
DEFINE_PUBLIC_ALIAS(DOS$mempcpyl, libd_mempcpyl);
DEFINE_PUBLIC_ALIAS(DOS$wmemmove, libd_memmovew);
DEFINE_PUBLIC_ALIAS(DOS$memmovew, libd_memmovew);
DEFINE_PUBLIC_ALIAS(DOS$wmempmove, libd_mempmovew);
DEFINE_PUBLIC_ALIAS(DOS$mempmovew, libd_mempmovew);
DEFINE_PUBLIC_ALIAS(DOS$memmovel, libd_memmovel);
DEFINE_PUBLIC_ALIAS(DOS$mempmovel, libd_mempmovel);
DEFINE_PUBLIC_ALIAS(DOS$memmoveupw, libd_memmoveupw);
DEFINE_PUBLIC_ALIAS(DOS$memmovedownw, libd_memmovedownw);
DEFINE_PUBLIC_ALIAS(DOS$mempmoveupw, libd_mempmoveupw);
DEFINE_PUBLIC_ALIAS(DOS$mempmovedownw, libd_mempmovedownw);
DEFINE_PUBLIC_ALIAS(DOS$memmoveupl, libd_memmoveupl);
DEFINE_PUBLIC_ALIAS(DOS$memmovedownl, libd_memmovedownl);
DEFINE_PUBLIC_ALIAS(DOS$mempmoveupl, libd_mempmoveupl);
DEFINE_PUBLIC_ALIAS(DOS$mempmovedownl, libd_mempmovedownl);
DEFINE_PUBLIC_ALIAS(DOS$wmemset, libd_memsetw);
DEFINE_PUBLIC_ALIAS(DOS$memsetw, libd_memsetw);
DEFINE_PUBLIC_ALIAS(DOS$wmempset, libd_mempsetw);
DEFINE_PUBLIC_ALIAS(DOS$mempsetw, libd_mempsetw);
DEFINE_PUBLIC_ALIAS(DOS$memsetl, libd_memsetl);
DEFINE_PUBLIC_ALIAS(DOS$mempsetl, libd_mempsetl);
DEFINE_PUBLIC_ALIAS(DOS$wmemcmp, libd_memcmpw);
DEFINE_PUBLIC_ALIAS(DOS$memcmpw, libd_memcmpw);
DEFINE_PUBLIC_ALIAS(DOS$memcmpl, libd_memcmpl);
DEFINE_PUBLIC_ALIAS(DOS$wmemchr, libd_memchrw);
DEFINE_PUBLIC_ALIAS(DOS$memchrw, libd_memchrw);
DEFINE_PUBLIC_ALIAS(DOS$memchrl, libd_memchrl);
DEFINE_PUBLIC_ALIAS(DOS$memrchrw, libd_memrchrw);
DEFINE_PUBLIC_ALIAS(DOS$memrchrl, libd_memrchrl);
DEFINE_PUBLIC_ALIAS(DOS$rawmemchrw, libd_rawmemchrw);
DEFINE_PUBLIC_ALIAS(DOS$rawmemchrl, libd_rawmemchrl);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrchrw, libd_rawmemrchrw);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrchrl, libd_rawmemrchrl);
DEFINE_PUBLIC_ALIAS(DOS$memendw, libd_memendw);
DEFINE_PUBLIC_ALIAS(DOS$memendl, libd_memendl);
DEFINE_PUBLIC_ALIAS(DOS$memrendw, libd_memrendw);
DEFINE_PUBLIC_ALIAS(DOS$memrendl, libd_memrendl);
DEFINE_PUBLIC_ALIAS(DOS$memlenw, libd_memlenw);
DEFINE_PUBLIC_ALIAS(DOS$memlenl, libd_memlenl);
DEFINE_PUBLIC_ALIAS(DOS$memrlenw, libd_memrlenw);
DEFINE_PUBLIC_ALIAS(DOS$memrlenl, libd_memrlenl);
DEFINE_PUBLIC_ALIAS(DOS$rawmemlenw, libd_rawmemlenw);
DEFINE_PUBLIC_ALIAS(DOS$rawmemlenl, libd_rawmemlenl);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrlenw, libd_rawmemrlenw);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrlenl, libd_rawmemrlenl);
DEFINE_PUBLIC_ALIAS(DOS$memcpyq, libd_memcpyq);
DEFINE_PUBLIC_ALIAS(DOS$mempcpyq, libd_mempcpyq);
DEFINE_PUBLIC_ALIAS(DOS$memmoveq, libd_memmoveq);
DEFINE_PUBLIC_ALIAS(DOS$mempmoveq, libd_mempmoveq);
DEFINE_PUBLIC_ALIAS(DOS$memmoveupq, libd_memmoveupq);
DEFINE_PUBLIC_ALIAS(DOS$memmovedownq, libd_memmovedownq);
DEFINE_PUBLIC_ALIAS(DOS$mempmoveupq, libd_mempmoveupq);
DEFINE_PUBLIC_ALIAS(DOS$mempmovedownq, libd_mempmovedownq);
DEFINE_PUBLIC_ALIAS(DOS$memsetq, libd_memsetq);
DEFINE_PUBLIC_ALIAS(DOS$mempsetq, libd_mempsetq);
DEFINE_PUBLIC_ALIAS(DOS$memcmpq, libd_memcmpq);
DEFINE_PUBLIC_ALIAS(DOS$memchrq, libd_memchrq);
DEFINE_PUBLIC_ALIAS(DOS$memrchrq, libd_memrchrq);
DEFINE_PUBLIC_ALIAS(DOS$rawmemchrq, libd_rawmemchrq);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrchrq, libd_rawmemrchrq);
DEFINE_PUBLIC_ALIAS(DOS$memendq, libd_memendq);
DEFINE_PUBLIC_ALIAS(DOS$memrendq, libd_memrendq);
DEFINE_PUBLIC_ALIAS(DOS$memlenq, libd_memlenq);
DEFINE_PUBLIC_ALIAS(DOS$memrlenq, libd_memrlenq);
DEFINE_PUBLIC_ALIAS(DOS$rawmemlenq, libd_rawmemlenq);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrlenq, libd_rawmemrlenq);
DEFINE_PUBLIC_ALIAS(DOS$memxchr, libd_memxchr);
DEFINE_PUBLIC_ALIAS(DOS$memrxchr, libd_memrxchr);
DEFINE_PUBLIC_ALIAS(DOS$rawmemxchr, libd_rawmemxchr);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrxchr, libd_rawmemrxchr);
DEFINE_PUBLIC_ALIAS(DOS$memxend, libd_memxend);
DEFINE_PUBLIC_ALIAS(DOS$memrxend, libd_memrxend);
DEFINE_PUBLIC_ALIAS(DOS$memxlen, libd_memxlen);
DEFINE_PUBLIC_ALIAS(DOS$memrxlen, libd_memrxlen);
DEFINE_PUBLIC_ALIAS(DOS$rawmemxlen, libd_rawmemxlen);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrxlen, libd_rawmemrxlen);
DEFINE_PUBLIC_ALIAS(DOS$memxchrw, libd_memxchrw);
DEFINE_PUBLIC_ALIAS(DOS$memxchrl, libd_memxchrl);
DEFINE_PUBLIC_ALIAS(DOS$memrxchrw, libd_memrxchrw);
DEFINE_PUBLIC_ALIAS(DOS$memrxchrl, libd_memrxchrl);
DEFINE_PUBLIC_ALIAS(DOS$rawmemxchrw, libd_rawmemxchrw);
DEFINE_PUBLIC_ALIAS(DOS$rawmemxchrl, libd_rawmemxchrl);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrxchrw, libd_rawmemrxchrw);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrxchrl, libd_rawmemrxchrl);
DEFINE_PUBLIC_ALIAS(DOS$memxendw, libd_memxendw);
DEFINE_PUBLIC_ALIAS(DOS$memxendl, libd_memxendl);
DEFINE_PUBLIC_ALIAS(DOS$memrxendw, libd_memrxendw);
DEFINE_PUBLIC_ALIAS(DOS$memrxendl, libd_memrxendl);
DEFINE_PUBLIC_ALIAS(DOS$memxlenw, libd_memxlenw);
DEFINE_PUBLIC_ALIAS(DOS$memxlenl, libd_memxlenl);
DEFINE_PUBLIC_ALIAS(DOS$memrxlenw, libd_memrxlenw);
DEFINE_PUBLIC_ALIAS(DOS$memrxlenl, libd_memrxlenl);
DEFINE_PUBLIC_ALIAS(DOS$rawmemxlenw, libd_rawmemxlenw);
DEFINE_PUBLIC_ALIAS(DOS$rawmemxlenl, libd_rawmemxlenl);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrxlenw, libd_rawmemrxlenw);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrxlenl, libd_rawmemrxlenl);
DEFINE_PUBLIC_ALIAS(DOS$memxchrq, libd_memxchrq);
DEFINE_PUBLIC_ALIAS(DOS$memrxchrq, libd_memrxchrq);
DEFINE_PUBLIC_ALIAS(DOS$rawmemxchrq, libd_rawmemxchrq);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrxchrq, libd_rawmemrxchrq);
DEFINE_PUBLIC_ALIAS(DOS$memxendq, libd_memxendq);
DEFINE_PUBLIC_ALIAS(DOS$memrxendq, libd_memrxendq);
DEFINE_PUBLIC_ALIAS(DOS$memxlenq, libd_memxlenq);
DEFINE_PUBLIC_ALIAS(DOS$memrxlenq, libd_memrxlenq);
DEFINE_PUBLIC_ALIAS(DOS$rawmemxlenq, libd_rawmemxlenq);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrxlenq, libd_rawmemrxlenq);
DEFINE_PUBLIC_ALIAS(DOS$memmoveup, libd_memmoveup);
DEFINE_PUBLIC_ALIAS(DOS$memmovedown, libd_memmovedown);
DEFINE_PUBLIC_ALIAS(DOS$memcpyc, libd_memcpyc);
DEFINE_PUBLIC_ALIAS(DOS$mempcpyc, libd_mempcpyc);
DEFINE_PUBLIC_ALIAS(DOS$memmovec, libd_memmovec);
DEFINE_PUBLIC_ALIAS(DOS$mempmovec, libd_mempmovec);
DEFINE_PUBLIC_ALIAS(DOS$memmoveupc, libd_memmoveupc);
DEFINE_PUBLIC_ALIAS(DOS$mempmoveupc, libd_mempmoveupc);
DEFINE_PUBLIC_ALIAS(DOS$memmovedownc, libd_memmovedownc);
DEFINE_PUBLIC_ALIAS(DOS$mempmovedownc, libd_mempmovedownc);
DEFINE_PUBLIC_ALIAS(DOS$strend, libd_strend);
DEFINE_PUBLIC_ALIAS(DOS$strnend, libd_strnend);
DEFINE_PUBLIC_ALIAS(DOS$strnchr, libd_strnchr);
DEFINE_PUBLIC_ALIAS(DOS$strnrchr, libd_strnrchr);
DEFINE_PUBLIC_ALIAS(DOS$strrchrnul, libd_strrchrnul);
DEFINE_PUBLIC_ALIAS(DOS$strnchrnul, libd_strnchrnul);
DEFINE_PUBLIC_ALIAS(DOS$strnrchrnul, libd_strnrchrnul);
DEFINE_PUBLIC_ALIAS(DOS$stroff, libd_stroff);
DEFINE_PUBLIC_ALIAS(DOS$strroff, libd_strroff);
DEFINE_PUBLIC_ALIAS(DOS$strnoff, libd_strnoff);
DEFINE_PUBLIC_ALIAS(DOS$strnroff, libd_strnroff);
DEFINE_PUBLIC_ALIAS(DOS$mempset, libd_mempset);
DEFINE_PUBLIC_ALIAS(DOS$mempmove, libd_mempmove);
DEFINE_PUBLIC_ALIAS(DOS$mempmoveup, libd_mempmoveup);
DEFINE_PUBLIC_ALIAS(DOS$mempmovedown, libd_mempmovedown);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrchr, libd_rawmemrchr);
DEFINE_PUBLIC_ALIAS(DOS$memend, libd_memend);
DEFINE_PUBLIC_ALIAS(DOS$memrend, libd_memrend);
DEFINE_PUBLIC_ALIAS(DOS$memlen, libd_memlen);
DEFINE_PUBLIC_ALIAS(DOS$memrlen, libd_memrlen);
DEFINE_PUBLIC_ALIAS(DOS$rawmemlen, libd_rawmemlen);
DEFINE_PUBLIC_ALIAS(DOS$rawmemrlen, libd_rawmemrlen);
DEFINE_PUBLIC_ALIAS(DOS$memrmem, libd_memrmem);
DEFINE_PUBLIC_ALIAS(DOS$mempatw, libd_mempatw);
DEFINE_PUBLIC_ALIAS(DOS$mempatl, libd_mempatl);
DEFINE_PUBLIC_ALIAS(DOS$mempatq, libd_mempatq);
DEFINE_PUBLIC_ALIAS(DOS$memicmp, libd_memcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$_memicmp, libd_memcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$memcasecmp, libd_memcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$memcasemem, libd_memcasemem);
DEFINE_PUBLIC_ALIAS(DOS$_memicmp_l, libd_memcasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$memcasecmp_l, libd_memcasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$memcasemem_l, libd_memcasemem_l);
DEFINE_PUBLIC_ALIAS(DOS$strcasestr_l, libd_strcasestr_l);
DEFINE_PUBLIC_ALIAS(DOS$strsignal_s, libd_strsignal_s);
DEFINE_PUBLIC_ALIAS(DOS$vstrdupf, libd_vstrdupf);
DEFINE_PUBLIC_ALIAS(DOS$strdupf, libd_strdupf);
DEFINE_PUBLIC_ALIAS(DOS$wildstrcmp, libd_wildstrcmp);
DEFINE_PUBLIC_ALIAS(DOS$wildstrcasecmp, libd_wildstrcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_strcmp, libd_fuzzy_strcmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_strncmp, libd_fuzzy_strncmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_strcasecmp, libd_fuzzy_strcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_strncasecmp, libd_fuzzy_strncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_memcmp, libd_fuzzy_memcmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_memcasecmp, libd_fuzzy_memcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_strcasecmp_l, libd_fuzzy_strcasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_strncasecmp_l, libd_fuzzy_strncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$wildstrcasecmp_l, libd_wildstrcasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_memcasecmp_l, libd_fuzzy_memcasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wmemcmp, libd_fuzzy_memcmpw);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_memcmpw, libd_fuzzy_memcmpw);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wmemcmp, libd_fuzzy_memcmpl);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_memcmpl, libd_fuzzy_memcmpl);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_memcmpq, libd_fuzzy_memcmpq);
DEFINE_PUBLIC_ALIAS(DOS$_strncoll, libd_strncoll);
DEFINE_PUBLIC_ALIAS(DOS$strncoll, libd_strncoll);
DEFINE_PUBLIC_ALIAS(DOS$_stricoll, libd_strcasecoll);
DEFINE_PUBLIC_ALIAS(DOS$strcasecoll, libd_strcasecoll);
DEFINE_PUBLIC_ALIAS(DOS$_strnicoll, libd_strncasecoll);
DEFINE_PUBLIC_ALIAS(DOS$strncasecoll, libd_strncasecoll);
DEFINE_PUBLIC_ALIAS(DOS$strnrev, libd_strnrev);
DEFINE_PUBLIC_ALIAS(DOS$strnlwr, libd_strnlwr);
DEFINE_PUBLIC_ALIAS(DOS$strnupr, libd_strnupr);
DEFINE_PUBLIC_ALIAS(DOS$_strncoll_l, libd_strncoll_l);
DEFINE_PUBLIC_ALIAS(DOS$strncoll_l, libd_strncoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_stricoll_l, libd_strcasecoll_l);
DEFINE_PUBLIC_ALIAS(DOS$strcasecoll_l, libd_strcasecoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_strnicoll_l, libd_strncasecoll_l);
DEFINE_PUBLIC_ALIAS(DOS$strncasecoll_l, libd_strncasecoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_strlwr_l, libd_strlwr_l);
DEFINE_PUBLIC_ALIAS(DOS$strlwr_l, libd_strlwr_l);
DEFINE_PUBLIC_ALIAS(DOS$_strupr_l, libd_strupr_l);
DEFINE_PUBLIC_ALIAS(DOS$strupr_l, libd_strupr_l);
DEFINE_PUBLIC_ALIAS(DOS$strnlwr_l, libd_strnlwr_l);
DEFINE_PUBLIC_ALIAS(DOS$strnupr_l, libd_strnupr_l);
DEFINE_PUBLIC_ALIAS(DOS$memrev, libd_memrev);
DEFINE_PUBLIC_ALIAS(DOS$memrevw, libd_memrevw);
DEFINE_PUBLIC_ALIAS(DOS$memrevl, libd_memrevl);
DEFINE_PUBLIC_ALIAS(DOS$memrevq, libd_memrevq);
DEFINE_PUBLIC_ALIAS(DOS$_strlwr, libd_strlwr);
DEFINE_PUBLIC_ALIAS(DOS$strlwr, libd_strlwr);
DEFINE_PUBLIC_ALIAS(DOS$_strupr, libd_strupr);
DEFINE_PUBLIC_ALIAS(DOS$strupr, libd_strupr);
DEFINE_PUBLIC_ALIAS(DOS$_strset, libd_strset);
DEFINE_PUBLIC_ALIAS(DOS$strset, libd_strset);
DEFINE_PUBLIC_ALIAS(DOS$_strnset, libd_strnset);
DEFINE_PUBLIC_ALIAS(DOS$strnset, libd_strnset);
DEFINE_PUBLIC_ALIAS(DOS$_strrev, libd_strrev);
DEFINE_PUBLIC_ALIAS(DOS$strrev, libd_strrev);
DEFINE_PUBLIC_ALIAS(DOS$_strset_s, libd__strset_s);
DEFINE_PUBLIC_ALIAS(DOS$memcpy_s, libd_memcpy_s);
DEFINE_PUBLIC_ALIAS(DOS$memmove_s, libd_memmove_s);
DEFINE_PUBLIC_ALIAS(DOS$strcpy_s, libd_strcpy_s);
DEFINE_PUBLIC_ALIAS(DOS$strcat_s, libd_strcat_s);
DEFINE_PUBLIC_ALIAS(DOS$strncat_s, libd_strncat_s);
DEFINE_PUBLIC_ALIAS(DOS$strncpy_s, libd_strncpy_s);
DEFINE_PUBLIC_ALIAS(DOS$_strerror, libd__strerror);
DEFINE_PUBLIC_ALIAS(DOS$_strerror_s, libd__strerror_s);
DEFINE_PUBLIC_ALIAS(DOS$_strlwr_s, libd__strlwr_s);
DEFINE_PUBLIC_ALIAS(DOS$_strupr_s, libd__strupr_s);
DEFINE_PUBLIC_ALIAS(DOS$_strlwr_s_l, libd__strlwr_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_strupr_s_l, libd__strupr_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_strnset_s, libd__strnset_s);
DEFINE_PUBLIC_ALIAS(DOS$strnstr, libd_strnstr);
DEFINE_PUBLIC_ALIAS(DOS$strmode, libd_strmode);

#endif /* !GUARD_LIBC_AUTO_DOSABI_STRING_C */
