/* HASH CRC-32:0x1a65f7fd */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_STDLIB_C
#define GUARD_LIBC_AUTO_STDLIB_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/stdlib.h"
#include "../user/ctype.h"
#include "err.h"
#include "../user/fcntl.h"
#include "format-printer.h"
#include "inttypes.h"
#include "../user/stdio.h"
#include "../user/string.h"
#include "../user/sys.ioctl.h"
#include "../user/sys.stat.h"
#include "../user/sys.time.h"
#include "../user/sys.wait.h"
#include "../user/unicode.h"
#include "../user/unistd.h"
#include "../user/wchar.h"

DECL_BEGIN

#include "../libc/globals.h"
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifndef __dwrap_sTPTP_TDTPTPTP_c0A0A1c1_defined
#define __dwrap_sTPTP_TDTPTPTP_c0A0A1c1_defined
struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0A0A1c1 {
	int (LIBDCALL *compar)(void const *a, void const *b, void *arg);
	void *arg;
};
PRIVATE ATTR_SECTION(".text.crt.dos.utility.stdlib") int
(LIBCCALL _dwrap_sTPTP_TDTPTPTP_c0A0A1c1)(void const *a,
                                          void const *b,
                                          struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0A0A1c1 *c) THROWS(...) {
	return (*c->compar)(a, b, c->arg);
}
#endif /* !__dwrap_sTPTP_TDTPTPTP_c0A0A1c1_defined */
INTERN ATTR_SECTION(".text.crt.dos.utility.stdlib") WUNUSED NONNULL((1, 2, 5)) void *
(LIBDCALL libd_bsearch_r)(void const *pkey,
                          void const *pbase,
                          size_t item_count,
                          size_t item_size,
                          int (LIBDCALL *compar)(void const *a, void const *b, void *arg),
                          void *arg) THROWS(...) {
	struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0A0A1c1 libd_bsearch_r_cookie;
	libd_bsearch_r_cookie.compar = compar;
	libd_bsearch_r_cookie.arg    = arg;
	return libc_bsearch_r(pkey, pbase, item_count, item_size, (int (LIBCCALL *)(void const *, void const *, void *))&_dwrap_sTPTP_TDTPTPTP_c0A0A1c1, &libd_bsearch_r_cookie);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.utility.stdlib") WUNUSED NONNULL((1, 2, 5)) void *
(LIBCCALL libc_bsearch_r)(void const *pkey,
                          void const *pbase,
                          size_t item_count,
                          size_t item_size,
                          int (LIBCCALL *compar)(void const *a, void const *b, void *arg),
                          void *arg) THROWS(...) {
	/* Optimize this function with the (allowed) assumption that `pbase' is sorted according to:
	 * >> qsort_r(pbase, item_count, item_size, compar, arg); */
	size_t lo, hi;
	lo = 0;
	hi = item_count;
	while likely(lo < hi) {
		size_t test_index;
		int difference;
		void *item_addr;
		/* Select the item right-smack in the middle of
		 * the  lower  and upper  bound  for comparison
		 * Assuming  an even  distribution, the  chance of  it being the
		 * intended item should be the greatest there, and will increase
		 * with every iteration
		 * Also: This way, the entire algorithm has a worst-case of
		 *       O(INDEX_OF_MSB(item_count))
		 *       with on 32-bit is O(32) and on 64-bit is O(64)
		 */
		test_index = (lo + hi) / 2;
		item_addr  = (byte_t *)pbase + (test_index * item_size);
		/* Check if the requested item lies above, or below the selected one */
		difference = (*compar)(pkey, item_addr, arg);
		if (difference < 0)
			/* KEY < ITEM --> Narrow the search-area to everything below */
			hi = test_index;
		else if (difference > 0)
			/* KEY > ITEM --> Narrow the search-area to everything above */
			lo = test_index + 1;
		else {
			/* Found it! */
			return item_addr;
		}
	}
	return NULL;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifndef __dwrap_cTP_TDTPTPTP_CA0A1_defined
#define __dwrap_cTP_TDTPTPTP_CA0A1_defined
PRIVATE ATTR_SECTION(".text.crt.dos.utility.stdlib") int
(LIBCCALL _dwrap_cTP_TDTPTPTP_CA0A1)(void const *a,
                                     void const *b,
                                     int (LIBDCALL *c)(void const *a, void const *b)) THROWS(...) {
	return (*c)(a, b);
}
#endif /* !__dwrap_cTP_TDTPTPTP_CA0A1_defined */
INTERN ATTR_SECTION(".text.crt.dos.utility.stdlib") NONNULL((1, 4)) void
(LIBDCALL libd_qsort)(void *pbase,
                      size_t item_count,
                      size_t item_size,
                      int (LIBDCALL *compar)(void const *a, void const *b)) THROWS(...) {
	libc_qsort_r(pbase, item_count, item_size, (int (LIBCCALL *)(void const *, void const *, void *))&_dwrap_cTP_TDTPTPTP_CA0A1, (void *)compar);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __LIBCCALL_CALLER_CLEANUP
#ifndef ____invoke_compare_helper_defined
__NAMESPACE_LOCAL_BEGIN
#define ____invoke_compare_helper_defined
__LOCAL_LIBC(__invoke_compare_helper) int
(__LIBCCALL __invoke_compare_helper)(void const *__a, void const *__b, void *__arg) {
	return (*(int (__LIBCCALL *)(void const *, void const *))__arg)(__a, __b);
}
__NAMESPACE_LOCAL_END
#endif /* !____invoke_compare_helper_defined */
#endif /* !__LIBCCALL_CALLER_CLEANUP */
INTERN ATTR_SECTION(".text.crt.utility.stdlib") NONNULL((1, 4)) void
(LIBCCALL libc_qsort)(void *pbase,
                      size_t item_count,
                      size_t item_size,
                      int (LIBCCALL *compar)(void const *a, void const *b)) THROWS(...) {
#ifdef __LIBCCALL_CALLER_CLEANUP
	libc_qsort_r(pbase, item_count, item_size,
	        (int (LIBCCALL *)(void const *, void const *, void *))(void *)compar,
	        NULL);
#else /* __LIBCCALL_CALLER_CLEANUP */
	libc_qsort_r(pbase, item_count, item_size,
	        &__NAMESPACE_LOCAL_SYM __invoke_compare_helper,
	        (void *)compar);
#endif /* !__LIBCCALL_CALLER_CLEANUP */
}
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifndef __dwrap_cTP_TDTPTPTP_CA0A1_defined
#define __dwrap_cTP_TDTPTPTP_CA0A1_defined
PRIVATE ATTR_SECTION(".text.crt.dos.utility.stdlib") int
(LIBCCALL _dwrap_cTP_TDTPTPTP_CA0A1)(void const *a,
                                     void const *b,
                                     int (LIBDCALL *c)(void const *a, void const *b)) THROWS(...) {
	return (*c)(a, b);
}
#endif /* !__dwrap_cTP_TDTPTPTP_CA0A1_defined */
INTERN ATTR_SECTION(".text.crt.dos.utility.stdlib") WUNUSED NONNULL((1, 2, 5)) void *
(LIBDCALL libd_bsearch)(void const *pkey,
                        void const *pbase,
                        size_t item_count,
                        size_t item_size,
                        int (LIBDCALL *compar)(void const *a, void const *b)) THROWS(...) {
	return libc_bsearch_r(pkey, pbase, item_count, item_size, (int (LIBCCALL *)(void const *, void const *, void *))&_dwrap_cTP_TDTPTPTP_CA0A1, (void *)compar);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.utility.stdlib") WUNUSED NONNULL((1, 2, 5)) void *
(LIBCCALL libc_bsearch)(void const *pkey,
                        void const *pbase,
                        size_t item_count,
                        size_t item_size,
                        int (LIBCCALL *compar)(void const *a, void const *b)) THROWS(...) {
#ifdef __LIBCCALL_CALLER_CLEANUP
	return (void *)libc_bsearch_r(pkey, pbase, item_count, item_size,
	                         (int (LIBCCALL *)(void const *, void const *, void *))(void *)compar,
	                         NULL);
#else /* __LIBCCALL_CALLER_CLEANUP */
	return (void *)libc_bsearch_r(pkey, pbase, item_count, item_size,
	                         &__NAMESPACE_LOCAL_SYM __invoke_compare_helper,
	                         (void *)compar);
#endif /* !__LIBCCALL_CALLER_CLEANUP */
}
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_labs, libc_abs);
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.math.utility") ATTR_CONST WUNUSED long
NOTHROW(LIBCCALL libc_labs)(long x) {
	return x < 0 ? -x : x;
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_INT__ */
#if __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_llabs, libc_abs);
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_llabs, libc_labs);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.math.utility") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBCCALL libc_llabs)(__LONGLONG x) {
	return x < 0 ? -x : x;
}
#endif /* !... */
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_ldiv, libc_div);
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.math.utility") ATTR_CONST WUNUSED ldiv_t
NOTHROW_NCX(LIBCCALL libc_ldiv)(long numer,
                                long denom) {
	ldiv_t result;
	result.quot = numer / denom;
	result.rem  = numer % denom;
	return result;
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_INT__ */
#if __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_lldiv, libc_div);
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_lldiv, libc_ldiv);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.math.utility") ATTR_CONST WUNUSED lldiv_t
NOTHROW_NCX(LIBCCALL libc_lldiv)(__LONGLONG numer,
                                 __LONGLONG denom) {
	lldiv_t result;
	result.quot = numer / denom;
	result.rem  = numer % denom;
	return result;
}
#endif /* !... */
INTERN ATTR_SECTION(".text.crt.math.utility") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_abs)(int x) {
	return x < 0 ? -x : x;
}
INTERN ATTR_SECTION(".text.crt.math.utility") ATTR_CONST WUNUSED struct __div_struct
NOTHROW_NCX(LIBCCALL libc_div)(int numer,
                               int denom) {
	div_t result;
	result.quot = numer / denom;
	result.rem  = numer % denom;
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBCCALL libc_mblen)(char const *str,
                                 size_t maxlen) {
	return libc_mbrlen(str, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBDCALL libd_mbtowc)(char16_t *__restrict pwc,
                                  char const *__restrict str,
                                  size_t maxlen) {
	return libd_mbrtowc(pwc, str, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBKCALL libc_mbtowc)(char32_t *__restrict pwc,
                                  char const *__restrict str,
                                  size_t maxlen) {
	return libc_mbrtowc(pwc, str, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBDCALL libd_wctomb)(char *str,
                                  char16_t wc) {
	return libd_wcrtomb(str, wc, NULL);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBKCALL libc_wctomb)(char *str,
                                  char32_t wc) {
	return libc_wcrtomb(str, wc, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_mbstowcs)(char16_t *__restrict dst,
                                    char const *__restrict src,
                                    size_t dstlen) {
	return libd_mbsrtowcs(dst, (char const **)&src, dstlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_mbstowcs)(char32_t *__restrict dst,
                                    char const *__restrict src,
                                    size_t dstlen) {
	return libc_mbsrtowcs(dst, (char const **)&src, dstlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_wcstombs)(char *__restrict dst,
                                    char16_t const *__restrict src,
                                    size_t dstlen) {
	return libd_wcsrtombs(dst, (char16_t const **)&src, dstlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_wcstombs)(char *__restrict dst,
                                    char32_t const *__restrict src,
                                    size_t dstlen) {
	return libc_wcsrtombs(dst, (char32_t const **)&src, dstlen, NULL);
}
#include <asm/os/wait.h>
/* >> system(3)
 * Execute a given `command' on the system interpreter (as in `sh -c $command')
 * The   return   value   is   the   exit   status   after   running  `command'
 * When `command' is `NULL' only check if a system interpreter is available.
 * When  no   system   interpreter   is  available,   `127'   is   returned. */
INTERN ATTR_SECTION(".text.crt.fs.exec.system") int
NOTHROW_RPC(LIBCCALL libc_system)(char const *command) {
	int status;
	pid_t cpid, error;
#if defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork)
	cpid = libc_vfork();
#else /* __CRT_HAVE_vfork || __CRT_HAVE___vfork */
	cpid = libc_fork();
#endif /* !__CRT_HAVE_vfork && !__CRT_HAVE___vfork */
	if (cpid == 0) {
		libc_shexec(command);
		/* NOTE: system() must return ZERO(0) if no command processor is available. */
		libc__Exit(command ? 127 : 0);
	}
	if (cpid < 0)
		return -1;
	for (;;) {
		error = libc_waitpid(cpid, &status, 0);
		if (error == cpid)
			break;
		if (error >= 0)
			continue;
#if defined(__libc_geterrno) && defined(__EINTR)
		if (__libc_geterrno() != __EINTR)
			return -1;
#else /* __libc_geterrno && __EINTR */
		return -1;
#endif /* !__libc_geterrno || !__EINTR */
	}
#ifdef __WIFEXITED
	if (!__WIFEXITED(status))
		return 1;
#endif /* __WIFEXITED */
#ifdef __WEXITSTATUS
	return __WEXITSTATUS(status);
#else /* __WEXITSTATUS */
	return status;
#endif /* !__WEXITSTATUS */
}
#ifndef LIBC_ARCH_HAVE_ABORT
#include <asm/os/stdlib.h>
INTERN ATTR_SECTION(".text.crt.application.exit") ATTR_NORETURN void
(LIBCCALL libc_abort)(void) THROWS(...) {
	libc__Exit(__EXIT_FAILURE);
}
#endif /* !LIBC_ARCH_HAVE_ABORT */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_atoi)(char const *__restrict nptr) {
#if __SIZEOF_INT__ <= 4
	return (int)libc_strto32(nptr, NULL, 10);
#else /* __SIZEOF_INT__ <= 4 */
	return (int)libc_strto64(nptr, NULL, 10);
#endif /* __SIZEOF_INT__ > 4 */
}
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_atol, libc_atoi);
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) long
NOTHROW_NCX(LIBCCALL libc_atol)(char const *__restrict nptr) {
#if __SIZEOF_LONG__ <= 4
	return (long)libc_strto32(nptr, NULL, 10);
#else /* __SIZEOF_LONG__ <= 4 */
	return (long)libc_strto64(nptr, NULL, 10);
#endif /* __SIZEOF_LONG__ > 4 */
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_INT__ */
#if __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_atoll, libc_atoi);
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc_atoll, libc_atol);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBCCALL libc_atoll)(char const *__restrict nptr) {
#if __SIZEOF_LONG_LONG__
	return (__LONGLONG)libc_strto32(nptr, NULL, 10);
#else /* __SIZEOF_LONG_LONG__ */
	return (__LONGLONG)libc_strto64(nptr, NULL, 10);
#endif /* !__SIZEOF_LONG_LONG__ */
}
#endif /* !... */
#if __SIZEOF_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_strtoul, libc_strtou32);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_strtoul, libc_strtou64);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) unsigned long
NOTHROW_NCX(LIBCCALL libc_strtoul)(char const *__restrict nptr,
                                   char **endptr,
                                   __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG__ <= 4
	return (unsigned long)libc_strtou32(nptr, endptr, base);
#else /* __SIZEOF_LONG__ <= 4 */
	return (unsigned long)libc_strtou64(nptr, endptr, base);
#endif /* __SIZEOF_LONG__ > 4 */
}
#endif /* !... */
#if __SIZEOF_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_strtol, libc_strto32);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_strtol, libc_strto64);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) long
NOTHROW_NCX(LIBCCALL libc_strtol)(char const *__restrict nptr,
                                  char **endptr,
                                  __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG__ <= 4
	return (long)libc_strto32(nptr, endptr, base);
#else /* __SIZEOF_LONG__ <= 4 */
	return (long)libc_strto64(nptr, endptr, base);
#endif /* __SIZEOF_LONG__ > 4 */
}
#endif /* !... */
#if __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_strtoull, libc_strtou64);
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_strtoull, libc_strtou32);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) __ULONGLONG
NOTHROW_NCX(LIBCCALL libc_strtoull)(char const *__restrict nptr,
                                    char **endptr,
                                    __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__ULONGLONG)libc_strtou32(nptr, endptr, base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__ULONGLONG)libc_strtou64(nptr, endptr, base);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
#endif /* !... */
#if __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_strtoll, libc_strto64);
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_strtoll, libc_strto32);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBCCALL libc_strtoll)(char const *__restrict nptr,
                                   char **endptr,
                                   __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__LONGLONG)libc_strto32(nptr, endptr, base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__LONGLONG)libc_strto64(nptr, endptr, base);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
#endif /* !... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF WUNUSED NONNULL((1)) double
NOTHROW_NCX(LIBCCALL libc_atof)(char const *__restrict nptr) {
	return libc_strtod(nptr, NULL);
}
#if __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
DEFINE_INTERN_ALIAS(libc_strtod, libc_strtod);
#else /* __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__ */
#include <asm/crt/stdio.h>
#if __SIZEOF_CHAR__ == 1
#ifndef ____vsscanf_getc_defined
#define ____vsscanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsscanf_getc) ssize_t
(FORMATPRINTER_CC vsscanf_getc)(void *arg) {
	char const *reader = *(char const **)arg;
	char32_t result = libc_unicode_readutf8(&reader);
	if (!result)
		return __EOF;
	*(char const **)arg = reader;
	return result;
}
__LOCAL_LIBC(vsscanf_ungetc) ssize_t
(FORMATPRINTER_CC vsscanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	libc_unicode_readutf8_rev((char const **)arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsscanf_getc_defined */

#elif __SIZEOF_CHAR__ == 2
#ifndef ____vsc16scanf_getc_defined
#define ____vsc16scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc16scanf_getc) ssize_t
(FORMATPRINTER_CC vsc16scanf_getc)(void *arg) {
	char16_t const *reader = *(char16_t const **)arg;
	char32_t result = unicode_readutf16(&reader);
	if (!result)
		return __EOF;
	*(char16_t const **)arg = reader;
	return result;
}
__LOCAL_LIBC(vsc16scanf_ungetc) ssize_t
(FORMATPRINTER_CC vsc16scanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	unicode_readutf16_rev((char16_t const **)arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc16scanf_getc_defined */

#else /* ... */
#ifndef ____vsc32scanf_getc_defined
#define ____vsc32scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc32scanf_getc) ssize_t
(FORMATPRINTER_CC vsc32scanf_getc)(void *arg) {
	char32_t const *reader = *(char32_t const **)arg;
	char32_t result = *reader++;
	if (!result)
		return __EOF;
	*(char32_t const **)arg = reader;
	return result;
}
__LOCAL_LIBC(vsc32scanf_ungetc) ssize_t
(FORMATPRINTER_CC vsc32scanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	--*(char32_t const **)arg;
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc32scanf_getc_defined */

#endif /* !... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) double
NOTHROW_NCX(LIBCCALL libc_strtod)(char const *__restrict nptr,
                                  char **endptr) {
	double result;
	char const *text_pointer = nptr;

	if (!libc_format_scanf(&__NAMESPACE_LOCAL_SYM vsscanf_getc,
	                  &__NAMESPACE_LOCAL_SYM vsscanf_ungetc,
	                  (void *)&text_pointer, "%lf", &result))
		result = 0.0;











	if (endptr)
		*endptr = (char *)text_pointer;
	return result;
}
#endif /* __SIZEOF_LONG_DOUBLE__ != __SIZEOF_DOUBLE__ */
#include <asm/crt/stdio.h>
#if __SIZEOF_CHAR__ == 1
#ifndef ____vsscanf_getc_defined
#define ____vsscanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsscanf_getc) ssize_t
(FORMATPRINTER_CC vsscanf_getc)(void *arg) {
	char const *reader = *(char const **)arg;
	char32_t result = libc_unicode_readutf8(&reader);
	if (!result)
		return __EOF;
	*(char const **)arg = reader;
	return result;
}
__LOCAL_LIBC(vsscanf_ungetc) ssize_t
(FORMATPRINTER_CC vsscanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	libc_unicode_readutf8_rev((char const **)arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsscanf_getc_defined */

#elif __SIZEOF_CHAR__ == 2
#ifndef ____vsc16scanf_getc_defined
#define ____vsc16scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc16scanf_getc) ssize_t
(FORMATPRINTER_CC vsc16scanf_getc)(void *arg) {
	char16_t const *reader = *(char16_t const **)arg;
	char32_t result = unicode_readutf16(&reader);
	if (!result)
		return __EOF;
	*(char16_t const **)arg = reader;
	return result;
}
__LOCAL_LIBC(vsc16scanf_ungetc) ssize_t
(FORMATPRINTER_CC vsc16scanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	unicode_readutf16_rev((char16_t const **)arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc16scanf_getc_defined */

#else /* ... */
#ifndef ____vsc32scanf_getc_defined
#define ____vsc32scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc32scanf_getc) ssize_t
(FORMATPRINTER_CC vsc32scanf_getc)(void *arg) {
	char32_t const *reader = *(char32_t const **)arg;
	char32_t result = *reader++;
	if (!result)
		return __EOF;
	*(char32_t const **)arg = reader;
	return result;
}
__LOCAL_LIBC(vsc32scanf_ungetc) ssize_t
(FORMATPRINTER_CC vsc32scanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	--*(char32_t const **)arg;
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc32scanf_getc_defined */

#endif /* !... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) float
NOTHROW_NCX(LIBCCALL libc_strtof)(char const *__restrict nptr,
                                  char **endptr) {
	float result;
	char const *text_pointer = nptr;

	if (!libc_format_scanf(&__NAMESPACE_LOCAL_SYM vsscanf_getc,
	                  &__NAMESPACE_LOCAL_SYM vsscanf_ungetc,
	                  (void *)&text_pointer, "%f", &result))
		result = 0.0f;











	if (endptr)
		*endptr = (char *)text_pointer;
	return result;
}
#if __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
DEFINE_INTERN_ALIAS(libc_strtold, libc_strtod);
#else /* __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__ */
#include <asm/crt/stdio.h>
#if __SIZEOF_CHAR__ == 1
#ifndef ____vsscanf_getc_defined
#define ____vsscanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsscanf_getc) ssize_t
(FORMATPRINTER_CC vsscanf_getc)(void *arg) {
	char const *reader = *(char const **)arg;
	char32_t result = libc_unicode_readutf8(&reader);
	if (!result)
		return __EOF;
	*(char const **)arg = reader;
	return result;
}
__LOCAL_LIBC(vsscanf_ungetc) ssize_t
(FORMATPRINTER_CC vsscanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	libc_unicode_readutf8_rev((char const **)arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsscanf_getc_defined */

#elif __SIZEOF_CHAR__ == 2
#ifndef ____vsc16scanf_getc_defined
#define ____vsc16scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc16scanf_getc) ssize_t
(FORMATPRINTER_CC vsc16scanf_getc)(void *arg) {
	char16_t const *reader = *(char16_t const **)arg;
	char32_t result = unicode_readutf16(&reader);
	if (!result)
		return __EOF;
	*(char16_t const **)arg = reader;
	return result;
}
__LOCAL_LIBC(vsc16scanf_ungetc) ssize_t
(FORMATPRINTER_CC vsc16scanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	unicode_readutf16_rev((char16_t const **)arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc16scanf_getc_defined */

#else /* ... */
#ifndef ____vsc32scanf_getc_defined
#define ____vsc32scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc32scanf_getc) ssize_t
(FORMATPRINTER_CC vsc32scanf_getc)(void *arg) {
	char32_t const *reader = *(char32_t const **)arg;
	char32_t result = *reader++;
	if (!result)
		return __EOF;
	*(char32_t const **)arg = reader;
	return result;
}
__LOCAL_LIBC(vsc32scanf_ungetc) ssize_t
(FORMATPRINTER_CC vsc32scanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	--*(char32_t const **)arg;
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc32scanf_getc_defined */

#endif /* !... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) __LONGDOUBLE
NOTHROW_NCX(LIBCCALL libc_strtold)(char const *__restrict nptr,
                                   char **endptr) {
	__LONGDOUBLE result;
	char const *text_pointer = nptr;

	if (!libc_format_scanf(&__NAMESPACE_LOCAL_SYM vsscanf_getc,
	                  &__NAMESPACE_LOCAL_SYM vsscanf_ungetc,
	                  (void *)&text_pointer, "%Lf", &result))
		result = 0.0L;











	if (endptr)
		*endptr = (char *)text_pointer;
	return result;
}
#endif /* __SIZEOF_LONG_DOUBLE__ != __SIZEOF_DOUBLE__ */
#endif /* !__KERNEL__ */
#include <asm/os/errno.h>
#include <hybrid/__overflow.h>
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint32_t
NOTHROW_NCX(LIBCCALL libc_strtou32_r)(char const *__restrict nptr,
                                      char **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      errno_t *error) {
	uint32_t result;
	char const *num_start = nptr;
	char const *num_iter;
	while (libc_isspace(*num_start))
		++num_start;
	if (base == 0) {
		/* Automatically deduce base. */
		if (*num_start == '0') {
			++num_start;
			if (*num_start == 'x' || *num_start == 'X') {
				base = 16;
				++num_start;
			} else if (*num_start == 'b' || *num_start == 'B') {
				base = 2;
				++num_start;
			} else {
				base = 8;
				/* Don't  consume the `0',  but handle it implicitly.
				 * That way, we can just always check that the number
				 * part of the integer is non-empty! */
			}
		} else {
			base = 10;
		}
	}
	num_iter = num_start;
	result   = 0;
	for (;;) {
		uint8_t digit;
		char ch = *num_iter;
		if (ch >= '0' && ch <= '9')
			digit = ch - '0';
		else if (ch >= 'a' && ch <= 'z')
			digit = 10 + (ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			digit = 10 + (ch - 'A');
		else {
			break;
		}
		if (digit >= base)
			break;
		++num_iter;
		if unlikely(__hybrid_overflow_umul(result, (unsigned int)base, &result) ||
		            __hybrid_overflow_uadd(result, digit, &result)) {
			/* Integer overflow. */
			if (error) {
#ifdef __ERANGE
				*error = __ERANGE;
#else /* __ERANGE */
				*error = 1;
#endif /* !__ERANGE */
			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (ch >= '0' && ch <= '9')
						digit = ch - '0';
					else if (ch >= 'a' && ch <= 'z')
						digit = 10 + (ch - 'a');
					else if (ch >= 'A' && ch <= 'Z')
						digit = 10 + (ch - 'A');
					else {
						break;
					}
					if (digit >= base)
						break;
					++num_iter;
				}
				*endptr = (char *)num_iter;
			}
			return (uint32_t)-1;
		}
	}
	if unlikely(num_iter == num_start) {
		/* Empty number... */
		if (error) {
#ifdef __ECANCELED
			*error = __ECANCELED;
#else /* __ECANCELED */
			*error = 1;
#endif /* !__ECANCELED */
		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (endptr)
			*endptr = (char *)nptr;
	} else {
		if (endptr) {
			*endptr = (char *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				while (libc_isspace(*num_iter))
					++num_iter;
				if (*num_iter) {
#ifdef __EINVAL
					*error = __EINVAL;
#else /* __EINVAL */
					*error = 1;
#endif /* !__EINVAL */
				}
			}
		}
	}
	return result;
}
#include <hybrid/limitcore.h>
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) int32_t
NOTHROW_NCX(LIBCCALL libc_strto32_r)(char const *__restrict nptr,
                                     char **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     errno_t *error) {
	int32_t result;
	char sign;
	char const *num_start = nptr;
	char const *num_iter;
	while (libc_isspace(*num_start))
		++num_start;
	sign = *num_start;
	if (sign == '-' || sign == '+')
		++num_start;
	if (base == 0) {
		/* Automatically deduce base. */
		if (*num_start == '0') {
			++num_start;
			if (*num_start == 'x' || *num_start == 'X') {
				base = 16;
				++num_start;
			} else if (*num_start == 'b' || *num_start == 'B') {
				base = 2;
				++num_start;
			} else {
				base = 8;
				/* Don't  consume the `0',  but handle it implicitly.
				 * That way, we can just always check that the number
				 * part of the integer is non-empty! */
			}
		} else {
			base = 10;
		}
	}
	num_iter = num_start;
	result   = 0;
	for (;;) {
		uint8_t digit;
		char ch;
		ch = *num_iter;
		if (ch >= '0' && ch <= '9')
			digit = ch - '0';
		else if (ch >= 'a' && ch <= 'z')
			digit = 10 + (ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			digit = 10 + (ch - 'A');
		else {
			break;
		}
		if (digit >= base)
			break;
		++num_iter;
		if unlikely(__hybrid_overflow_smul(result, (unsigned int)base, &result) ||
		            __hybrid_overflow_sadd(result, digit, &result)) {
handle_overflow:
			/* Integer overflow. */
			if (error) {
#ifdef __ERANGE
				*error = __ERANGE;
#else /* __ERANGE */
				*error = 1;
#endif /* !__ERANGE */
			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (ch >= '0' && ch <= '9')
						digit = ch - '0';
					else if (ch >= 'a' && ch <= 'z')
						digit = 10 + (ch - 'a');
					else if (ch >= 'A' && ch <= 'Z')
						digit = 10 + (ch - 'A');
					else {
						break;
					}
					if (digit >= base)
						break;
					++num_iter;
				}
				*endptr = (char *)num_iter;
			}
			if (sign == '-')
				return __INT32_MIN__;
			return __INT32_MAX__;
		}
	}
	if (sign == '-') {
		result = -result;
		if unlikely(result > 0)
			goto handle_overflow; /* Overflow... */
	}
	if unlikely(num_iter == num_start) {
		/* Empty number... */
		if (error) {
#ifdef __ECANCELED
			*error = __ECANCELED;
#else /* __ECANCELED */
			*error = 1;
#endif /* !__ECANCELED */
		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (endptr)
			*endptr = (char *)nptr;
	} else {
		if (endptr) {
			*endptr = (char *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				while (libc_isspace(*num_iter))
					++num_iter;
				if (*num_iter) {
#ifdef __EINVAL
					*error = __EINVAL;
#else /* __EINVAL */
					*error = 1;
#endif /* !__EINVAL */
				}
			}
		}
	}
	return result;
}
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint64_t
NOTHROW_NCX(LIBCCALL libc_strtou64_r)(char const *__restrict nptr,
                                      char **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      errno_t *error) {
	uint64_t result;
	char const *num_start = nptr;
	char const *num_iter;
	while (libc_isspace(*num_start))
		++num_start;
	if (base == 0) {
		/* Automatically deduce base. */
		if (*num_start == '0') {
			++num_start;
			if (*num_start == 'x' || *num_start == 'X') {
				base = 16;
				++num_start;
			} else if (*num_start == 'b' || *num_start == 'B') {
				base = 2;
				++num_start;
			} else {
				base = 8;
				/* Don't  consume the `0',  but handle it implicitly.
				 * That way, we can just always check that the number
				 * part of the integer is non-empty! */
			}
		} else {
			base = 10;
		}
	}
	num_iter = num_start;
	result   = 0;
	for (;;) {
		uint8_t digit;
		char ch = *num_iter;
		if (ch >= '0' && ch <= '9')
			digit = ch - '0';
		else if (ch >= 'a' && ch <= 'z')
			digit = 10 + (ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			digit = 10 + (ch - 'A');
		else {
			break;
		}
		if (digit >= base)
			break;
		++num_iter;
		if unlikely(__hybrid_overflow_umul(result, (unsigned int)base, &result) ||
		            __hybrid_overflow_uadd(result, digit, &result)) {
			/* Integer overflow. */
			if (error) {
#ifdef __ERANGE
				*error = __ERANGE;
#else /* __ERANGE */
				*error = 1;
#endif /* !__ERANGE */
			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (ch >= '0' && ch <= '9')
						digit = ch - '0';
					else if (ch >= 'a' && ch <= 'z')
						digit = 10 + (ch - 'a');
					else if (ch >= 'A' && ch <= 'Z')
						digit = 10 + (ch - 'A');
					else {
						break;
					}
					if (digit >= base)
						break;
					++num_iter;
				}
				*endptr = (char *)num_iter;
			}
			return (uint64_t)-1;
		}
	}
	if unlikely(num_iter == num_start) {
		/* Empty number... */
		if (error) {
#ifdef __ECANCELED
			*error = __ECANCELED;
#else /* __ECANCELED */
			*error = 1;
#endif /* !__ECANCELED */
		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (endptr)
			*endptr = (char *)nptr;
	} else {
		if (endptr) {
			*endptr = (char *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				while (libc_isspace(*num_iter))
					++num_iter;
				if (*num_iter) {
#ifdef __EINVAL
					*error = __EINVAL;
#else /* __EINVAL */
					*error = 1;
#endif /* !__EINVAL */
				}
			}
		}
	}
	return result;
}
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL).  The following errors are  defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly,  and
 *               the  returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supersedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by   at  least  1  additional  non-whitespace  character.
 *               The returned integer value is not affected by this error. */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) int64_t
NOTHROW_NCX(LIBCCALL libc_strto64_r)(char const *__restrict nptr,
                                     char **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     errno_t *error) {
	int64_t result;
	char sign;
	char const *num_start = nptr;
	char const *num_iter;
	while (libc_isspace(*num_start))
		++num_start;
	sign = *num_start;
	if (sign == '-' || sign == '+')
		++num_start;
	if (base == 0) {
		/* Automatically deduce base. */
		if (*num_start == '0') {
			++num_start;
			if (*num_start == 'x' || *num_start == 'X') {
				base = 16;
				++num_start;
			} else if (*num_start == 'b' || *num_start == 'B') {
				base = 2;
				++num_start;
			} else {
				base = 8;
				/* Don't  consume the `0',  but handle it implicitly.
				 * That way, we can just always check that the number
				 * part of the integer is non-empty! */
			}
		} else {
			base = 10;
		}
	}
	num_iter = num_start;
	result   = 0;
	for (;;) {
		uint8_t digit;
		char ch;
		ch = *num_iter;
		if (ch >= '0' && ch <= '9')
			digit = ch - '0';
		else if (ch >= 'a' && ch <= 'z')
			digit = 10 + (ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			digit = 10 + (ch - 'A');
		else {
			break;
		}
		if (digit >= base)
			break;
		++num_iter;
		if unlikely(__hybrid_overflow_smul(result, (unsigned int)base, &result) ||
		            __hybrid_overflow_sadd(result, digit, &result)) {
handle_overflow:
			/* Integer overflow. */
			if (error) {
#ifdef __ERANGE
				*error = __ERANGE;
#else /* __ERANGE */
				*error = 1;
#endif /* !__ERANGE */
			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (ch >= '0' && ch <= '9')
						digit = ch - '0';
					else if (ch >= 'a' && ch <= 'z')
						digit = 10 + (ch - 'a');
					else if (ch >= 'A' && ch <= 'Z')
						digit = 10 + (ch - 'A');
					else {
						break;
					}
					if (digit >= base)
						break;
					++num_iter;
				}
				*endptr = (char *)num_iter;
			}
			if (sign == '-')
				return __INT64_MIN__;
			return __INT64_MAX__;
		}
	}
	if (sign == '-') {
		result = -result;
		if unlikely(result > 0)
			goto handle_overflow; /* Overflow... */
	}
	if unlikely(num_iter == num_start) {
		/* Empty number... */
		if (error) {
#ifdef __ECANCELED
			*error = __ECANCELED;
#else /* __ECANCELED */
			*error = 1;
#endif /* !__ECANCELED */
		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (endptr)
			*endptr = (char *)nptr;
	} else {
		if (endptr) {
			*endptr = (char *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				while (libc_isspace(*num_iter))
					++num_iter;
				if (*num_iter) {
#ifdef __EINVAL
					*error = __EINVAL;
#else /* __EINVAL */
					*error = 1;
#endif /* !__EINVAL */
				}
			}
		}
	}
	return result;
}
#include <libc/errno.h>
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint32_t
NOTHROW_NCX(LIBCCALL libc_strtou32)(char const *__restrict nptr,
                                    char **endptr,
                                    __STDC_INT_AS_UINT_T base) {
#if defined(__libc_geterrno) && defined(ERANGE)
	uint32_t result;
	errno_t error;
	result = libc_strtou32_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)__libc_seterrno(ERANGE);
	return result;
#else /* __libc_geterrno && ERANGE */
	return libc_strtou32_r(nptr, endptr, base, NULL);
#endif /* !__libc_geterrno || !ERANGE */
}
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) int32_t
NOTHROW_NCX(LIBCCALL libc_strto32)(char const *__restrict nptr,
                                   char **endptr,
                                   __STDC_INT_AS_UINT_T base) {
#if defined(__libc_geterrno) && defined(ERANGE)
	int32_t result;
	errno_t error;
	result = libc_strto32_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)__libc_seterrno(ERANGE);
	return result;
#else /* __libc_geterrno && ERANGE */
	return libc_strto32_r(nptr, endptr, base, NULL);
#endif /* !__libc_geterrno || !ERANGE */
}
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint64_t
NOTHROW_NCX(LIBCCALL libc_strtou64)(char const *__restrict nptr,
                                    char **endptr,
                                    __STDC_INT_AS_UINT_T base) {
#if defined(__libc_geterrno) && defined(ERANGE)
	uint64_t result;
	errno_t error;
	result = libc_strtou64_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)__libc_seterrno(ERANGE);
	return result;
#else /* __libc_geterrno && ERANGE */
	return libc_strtou64_r(nptr, endptr, base, NULL);
#endif /* !__libc_geterrno || !ERANGE */
}
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string  (radix=`base') from `nptr'  into an  integer,
 * and store a  pointer to  the end  of the  number in  `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid   integer   (`U?INTn_(MIN|MAX))'.   (though   note   that
 * `endptr'  (if  non-NULL)  is  still  updated  in  this   case!)
 * Upon success, `errno' is left  unchanged, and the integer  repr
 * of the parsed number is  returned. When no integer was  parsed,
 * then `0' is returned, `*endptr'  is set to `nptr', but  `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) int64_t
NOTHROW_NCX(LIBCCALL libc_strto64)(char const *__restrict nptr,
                                   char **endptr,
                                   __STDC_INT_AS_UINT_T base) {
#if defined(__libc_geterrno) && defined(ERANGE)
	int64_t result;
	errno_t error;
	result = libc_strto64_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)__libc_seterrno(ERANGE);
	return result;
#else /* __libc_geterrno && ERANGE */
	return libc_strto64_r(nptr, endptr, base, NULL);
#endif /* !__libc_geterrno || !ERANGE */
}
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint32_t
NOTHROW_NCX(LIBCCALL libc_strtou32_l)(char const *__restrict nptr,
                                      char **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libc_strtou32(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) int32_t
NOTHROW_NCX(LIBCCALL libc_strto32_l)(char const *__restrict nptr,
                                     char **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_strto32(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint64_t
NOTHROW_NCX(LIBCCALL libc_strtou64_l)(char const *__restrict nptr,
                                      char **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libc_strtou64(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF NONNULL((1)) int64_t
NOTHROW_NCX(LIBCCALL libc_strto64_l)(char const *__restrict nptr,
                                     char **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_strto64(nptr, endptr, base);
}
#endif /* !__KERNEL__ */
#undef _itoa_digits
#undef libc__itoa_digits
DEFINE_PUBLIC_ALIAS(_itoa_digits, libc__itoa_digits);
INTERN_CONST ATTR_SECTION(".rodata.crt.unicode.static.ctype") char const libc__itoa_digits[101] =
"0123456789abcdefghijklmnopqrstuvwxyz\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
#define _itoa_digits libc__itoa_digits

/* For ABI compat, also export the lower/upper tables as dedicated symbols. (but only in user-space) */
#ifndef __KERNEL__
#undef libc__itoa_lower_digits
#undef libc__itoa_upper_digits
__asm__(".hidden libc__itoa_lower_digits\n"
        ".hidden libc__itoa_upper_digits\n"
        ".type   libc__itoa_lower_digits, @object\n"
        ".type   libc__itoa_upper_digits, @object\n"
        ".set    .Ldisp_itoa_lower_digits, libc__itoa_digits - 1\n"       /* Prevent size aliasing */
        ".set    libc__itoa_lower_digits, .Ldisp_itoa_lower_digits + 1\n" /* *ditto* */
        ".set    libc__itoa_upper_digits, libc__itoa_digits + 64\n"
        ".size   libc__itoa_lower_digits, 37\n"
        ".size   libc__itoa_upper_digits, 37\n");
#undef _itoa_lower_digits
#undef _itoa_upper_digits
DEFINE_PUBLIC_ALIAS(_itoa_lower_digits, libc__itoa_lower_digits);
DEFINE_PUBLIC_ALIAS(_itoa_upper_digits, libc__itoa_upper_digits);
#define _itoa_lower_digits (libc__itoa_digits + 0)
#define _itoa_upper_digits (libc__itoa_digits + 64)
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
#include <hybrid/floatcore.h>
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") WUNUSED NONNULL((3)) char *
NOTHROW_NCX(LIBCCALL libc_gcvt)(double val,
                                int ndigit,
                                char *buf) {
#ifndef DBL_NDIGIT_MAX
#if __DBL_MANT_DIG__ == 53
#define DBL_NDIGIT_MAX 17
#elif __DBL_MANT_DIG__ == 24
#define DBL_NDIGIT_MAX 9
#elif __DBL_MANT_DIG__ == 56
#define DBL_NDIGIT_MAX 18
#else /* ... */
	/* ceil(M_LN2 / M_LN10 * DBL_MANT_DIG + 1.0) */
#define DBL_NDIGIT_MAX (__DBL_MANT_DIG__ / 4)
#endif /* !... */
#endif /* !DBL_NDIGIT_MAX */
	if (ndigit > DBL_NDIGIT_MAX)
		ndigit = DBL_NDIGIT_MAX;
	libc_sprintf(buf, "%.*g", ndigit, val);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((3, 4, 5)) int
NOTHROW_NCX(LIBCCALL libc_ecvt_r)(double val,
                                  int ndigit,
                                  int *__restrict decptr,
                                  int *__restrict sign,
                                  char *__restrict buf,
                                  size_t len) {
#if defined(__CRT_HAVE__ecvt_s) && !defined(__BUILDING_LIBC)
	return dos_ecvt_s(buf, len, val, ndigit, decptr, sign) ? -1 : 0;
#else
	/* TODO: Implementation */
	(void)val;
	(void)ndigit;
	(void)decptr;
	(void)sign;
	(void)buf;
	(void)len;
	COMPILER_IMPURE();
	return 0;
#endif
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((3, 4, 5)) int
NOTHROW_NCX(LIBCCALL libc_fcvt_r)(double val,
                                  int ndigit,
                                  int *__restrict decptr,
                                  int *__restrict sign,
                                  char *__restrict buf,
                                  size_t len) {
#if defined(__CRT_HAVE__fcvt_s) && !defined(__BUILDING_LIBC)
	return dos_fcvt_s(buf, len, val, ndigit, decptr, sign) ? -1 : 0;
#else
	/* TODO: Implementation */
	(void)val;
	(void)ndigit;
	(void)decptr;
	(void)sign;
	(void)buf;
	(void)len;
	COMPILER_IMPURE();
	return 0;
#endif
}
#include <hybrid/floatcore.h>
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((3)) char *
NOTHROW_NCX(LIBCCALL libc_qgcvt)(__LONGDOUBLE val,
                                 int ndigit,
                                 char *buf) {
#ifndef LDBG_NDIGIT_MAX
#if __LDBL_MANT_DIG__ == 53
#define LDBG_NDIGIT_MAX 17
#elif __LDBL_MANT_DIG__ == 24
#define LDBG_NDIGIT_MAX 9
#elif __LDBL_MANT_DIG__ == 56
#define LDBG_NDIGIT_MAX 18
#else /* ... */
	/* ceil(M_LN2 / M_LN10 * DBL_MANT_DIG + 1.0) */
#define LDBG_NDIGIT_MAX (__LDBL_MANT_DIG__ / 4)
#endif /* !... */
#endif /* !LDBG_NDIGIT_MAX */
	if (ndigit > LDBG_NDIGIT_MAX)
		ndigit = LDBG_NDIGIT_MAX;
	libc_sprintf(buf, "%.*Lg", ndigit, val);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((3, 4, 5)) int
NOTHROW_NCX(LIBCCALL libc_qecvt_r)(__LONGDOUBLE val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign,
                                   char *__restrict buf,
                                   size_t len) {
#if defined(__CRT_HAVE__ecvt_s) && !defined(__BUILDING_LIBC)
	return dos_ecvt_s(buf, len, (double)val, ndigit, decptr, sign) ? -1 : 0;
#else
	/* TODO: Implementation */
	(void)val;
	(void)ndigit;
	(void)decptr;
	(void)sign;
	(void)buf;
	(void)len;
	COMPILER_IMPURE();
	return 0;
#endif
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((3, 4, 5)) int
NOTHROW_NCX(LIBCCALL libc_qfcvt_r)(__LONGDOUBLE val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign,
                                   char *__restrict buf,
                                   size_t len) {
#if defined(__CRT_HAVE__fcvt_s) && !defined(__BUILDING_LIBC)
	return dos_fcvt_s(buf, len, (double)val, ndigit, decptr, sign) ? -1 : 0;
#else
	/* TODO: Implementation */
	(void)val;
	(void)ndigit;
	(void)decptr;
	(void)sign;
	(void)buf;
	(void)len;
	COMPILER_IMPURE();
	return 0;
#endif
}
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
static char qcvt_buffer[32];
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") WUNUSED NONNULL((3, 4)) char *
NOTHROW_NCX(LIBCCALL libc_qecvt)(__LONGDOUBLE val,
                                 int ndigit,
                                 int *__restrict decptr,
                                 int *__restrict sign) {



	if (libc_qecvt_r(val, ndigit, decptr, sign,  qcvt_buffer, sizeof(qcvt_buffer)))
		return NULL;
	return qcvt_buffer;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") WUNUSED NONNULL((3, 4)) char *
NOTHROW_NCX(LIBCCALL libc_qfcvt)(__LONGDOUBLE val,
                                 int ndigit,
                                 int *__restrict decptr,
                                 int *__restrict sign) {



	if (libc_qfcvt_r(val, ndigit, decptr, sign, qcvt_buffer, sizeof(qcvt_buffer)))
		return NULL;
	return qcvt_buffer;
}
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all  'X'-characters before the  call (else errno=EINVAL  + return -1), with
 * random  characters such that the filename described by `template_' will not
 * already  exists. Then, create a new file  with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The #  of trailing  characters to-be  ignored
 *                    after the required 6 trailing 'X'-characters. */
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED NONNULL((1)) fd_t
NOTHROW_RPC(LIBCCALL libc_mkstemps)(char *template_,
                                    __STDC_INT_AS_SIZE_T suffixlen) {
	return libc_mkostemps(template_, suffixlen, 0);
}
INTERN ATTR_SECTION(".text.crt.utility.locale") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_rpmatch)(char const *response) {
	char c = response[0];
	if (c == 'n' || c == 'N')
		return 0;
	if (c == 'y' || c == 'Y')
		return 1;
	return -1;
}
#include <asm/os/oflags.h>
#if !defined(__O_LARGEFILE) || !__O_LARGEFILE
DEFINE_INTERN_ALIAS(libc_mkstemps64, libc_mkstemps);
#else /* !__O_LARGEFILE || !__O_LARGEFILE */
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all  'X'-characters before the  call (else errno=EINVAL  + return -1), with
 * random  characters such that the filename described by `template_' will not
 * already  exists. Then, create a new file  with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The #  of trailing  characters to-be  ignored
 *                    after the required 6 trailing 'X'-characters. */
INTERN ATTR_SECTION(".text.crt.unsorted") WUNUSED NONNULL((1)) fd_t
NOTHROW_RPC(LIBCCALL libc_mkstemps64)(char *template_,
                                      __STDC_INT_AS_SIZE_T suffixlen) {
	return libc_mkostemps64(template_, suffixlen, 0);
}
#endif /* __O_LARGEFILE && __O_LARGEFILE */
#include <hybrid/typecore.h>
/* >> l64a(3), a64l(3)
 * Convert between `long' and base-64 encoded integer strings. */
INTERN ATTR_SECTION(".text.crt.bsd") ATTR_RETNONNULL WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_l64a)(long n) {
	/* l64a_r() encodes 6 bytes from `n' into 1 character, followed
	 * by 1 trailing NUL-character. So we can can calculate the max
	 * required buffer size here, based on `sizeof(long)'! */
	static char buf[(((sizeof(long) * __CHAR_BIT__) + 5) / 6) + 1];
	libc_l64a_r(n, buf, sizeof(buf));
	return buf;
}
/* >> l64a(3), a64l(3)
 * Convert between `long' and base-64 encoded integer strings. */
INTERN ATTR_SECTION(".text.crt.bsd") ATTR_PURE WUNUSED NONNULL((1)) long
NOTHROW_NCX(LIBCCALL libc_a64l)(char const *s) {
	unsigned long digit, result = 0;
	shift_t shift = 0;
	for (;; ++s) {
		char ch = *s;
		if (ch <= 0) {
			break;
		} else if (ch <= '/') {
			digit = (ch - '.') + 0;
		} else if (ch <= '9') {
			digit = (ch - '0') + 2;
		} else if (ch <= 'Z') {
			digit = (ch - 'A') + 12;
		} else {
			digit = (ch - 'a') + 38;
		}
		digit <<= shift;
		result |= digit;
		shift += 6;
	}
	return result;
}
/* >> mktemp(3)
 * Badly designed version of  `mkstemp' that won't actually  create
 * the temporary file, meaning that by the time the caller tries to
 * create the  file themselves,  another process  may have  already
 * created it.
 * Also: when no  temporary filename  can be  created, rather  than
 *       returning something  sensible like  `NULL', this  function
 *       will instead set `template_' to an empty string, and still
 *       re-return it like it would if everything had worked! */
INTERN ATTR_SECTION(".text.crt.fs.utility") ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_mktemp)(char *template_) {
	if (libc_system_mktemp(2, template_, 0, 0) )
		*template_ = 0;
	return template_;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") WUNUSED NONNULL((3, 4)) char *
NOTHROW_NCX(LIBCCALL libc_ecvt)(double val,
                                int ndigit,
                                int *__restrict decptr,
                                int *__restrict sign) {



	if (libc_ecvt_r(val, ndigit, decptr, sign, qcvt_buffer, sizeof(qcvt_buffer)))
		return NULL;
	return qcvt_buffer;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") WUNUSED NONNULL((3, 4)) char *
NOTHROW_NCX(LIBCCALL libc_fcvt)(double val,
                                int ndigit,
                                int *__restrict decptr,
                                int *__restrict sign) {



	if (libc_fcvt_r(val, ndigit, decptr, sign, qcvt_buffer, sizeof(qcvt_buffer)))
		return NULL;
	return qcvt_buffer;
}
INTERN ATTR_SECTION(".text.crt.application.options") WUNUSED NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBCCALL libc_getsubopt)(char **__restrict optionp,
                                     char *const *__restrict tokens,
                                     char **__restrict valuep) {
	unsigned int i;
	char *option, *nextopt;
	size_t option_len;
	option  = *optionp;
	*valuep = NULL;
	/* Find the next option */
	nextopt = libc_strchr(option, ',');
	if (nextopt) {
		option_len = (size_t)(nextopt - option);
		*nextopt++ = '\0';
	} else {
		option_len = libc_strlen(option);
		nextopt = option + option_len;
	}
	*optionp = nextopt;
	for (i = 0; tokens[i]; ++i) {
		size_t toklen = libc_strlen(tokens[i]);
		/* Check if this token is matches the found option */
		if (libc_memcmp(tokens[i], option, toklen * sizeof(char)) != 0)
			continue;
		/* Deal with a potential option value. */
		if (option[toklen] == '=') {
			*valuep = option + toklen + 1;
		} else {
			/* Make sure that the option doesn't keep on going */
			if (option[toklen] != 0)
				continue;
		}
		return (int)i;
	}
	/* Not found (return the whole `name[=value]' string) */
	*valuep = option;
	return -1;
}
/* >> mkstemp(3), mkstemp64(3)
 * Replace the last 6 characters of  `template_', which must be filled  with
 * all  'X'-characters  before the  call  (else errno=EINVAL  +  return -1),
 * with random characters  such that the  filename described by  `template_'
 * will not already exists. Then, create a new file with `O_RDWR' and return
 * the file descriptor of that file. */
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED NONNULL((1)) fd_t
NOTHROW_RPC(LIBCCALL libc_mkstemp)(char *template_) {
	return libc_mkstemps(template_, 0);
}
#include <asm/os/oflags.h>
#if !defined(__O_LARGEFILE) || !__O_LARGEFILE
DEFINE_INTERN_ALIAS(libc_mkstemp64, libc_mkstemp);
#else /* !__O_LARGEFILE || !__O_LARGEFILE */
/* >> mkstemp(3), mkstemp64(3)
 * Replace the last 6 characters of  `template_', which must be filled  with
 * all  'X'-characters  before the  call  (else errno=EINVAL  +  return -1),
 * with random characters  such that the  filename described by  `template_'
 * will not already exists. Then, create a new file with `O_RDWR' and return
 * the file descriptor of that file. */
INTERN ATTR_SECTION(".text.crt.unsorted") WUNUSED NONNULL((1)) fd_t
NOTHROW_RPC(LIBCCALL libc_mkstemp64)(char *template_) {
	return libc_mkstemps64(template_, 0);
}
#endif /* __O_LARGEFILE && __O_LARGEFILE */
/* >> mkdtemp(3)
 * Replace the last 6 characters of `template_', which must be filled with
 * all  'X'-characters before  the call  (else errno=EINVAL  + return -1),
 * with random characters such that the pathname described by  `template_'
 * will not already exists. Then, create a new directory with `mode=0700',
 * and re-return `template_' to indicate success.
 * On error, `NULL' will be returned, and the contents of `template_' are undefined. */
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED NONNULL((1)) char *
NOTHROW_RPC(LIBCCALL libc_mkdtemp)(char *template_) {
	if (libc_system_mktemp(1, template_, 0, 0) )
		template_ = NULL;
	return template_;
}
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_NCX(LIBCCALL libc_unlockpt)(fd_t fd) {
	int action = 0;
	if (libc_ioctl(fd, __TIOCSPTLCK, &action))
		return -1;
	return 0;
}
/* >> ptsname(3)
 * Returns the name of the PTY slave (Pseudo TTY slave)
 * associated   with   the   master   descriptor   `fd' */
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_ptsname)(fd_t fd) {
	static char buf[64];
	if unlikely(libc_ptsname_r(fd, buf, sizeof(buf)))
		return NULL;
	return buf;
}
#if __SIZEOF_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_strtol_l, libc_strto32_l);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_strtol_l, libc_strto64_l);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1)) long
NOTHROW_NCX(LIBCCALL libc_strtol_l)(char const *__restrict nptr,
                                    char **endptr,
                                    __STDC_INT_AS_UINT_T base,
                                    locale_t locale) {
	(void)locale;
	return libc_strtol(nptr, endptr, base);
}
#endif /* !... */
#if __SIZEOF_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_strtoul_l, libc_strtou32_l);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_strtoul_l, libc_strtou64_l);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1)) unsigned long
NOTHROW_NCX(LIBCCALL libc_strtoul_l)(char const *__restrict nptr,
                                     char **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_strtoul(nptr, endptr, base);
}
#endif /* !... */
#if __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_strtoll_l, libc_strto64_l);
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_strtoll_l, libc_strto32_l);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBCCALL libc_strtoll_l)(char const *__restrict nptr,
                                     char **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_strtoll(nptr, endptr, base);
}
#endif /* !... */
#if __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_strtoull_l, libc_strtou64_l);
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_strtoull_l, libc_strtou32_l);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1)) __ULONGLONG
NOTHROW_NCX(LIBCCALL libc_strtoull_l)(char const *__restrict nptr,
                                      char **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libc_strtoull(nptr, endptr, base);
}
#endif /* !... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1)) double
NOTHROW_NCX(LIBCCALL libc_strtod_l)(char const *__restrict nptr,
                                    char **endptr,
                                    locale_t locale) {
	(void)locale;
	return libc_strtod(nptr, endptr);
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1)) float
NOTHROW_NCX(LIBCCALL libc_strtof_l)(char const *__restrict nptr,
                                    char **endptr,
                                    locale_t locale) {
	(void)locale;
	return libc_strtof(nptr, endptr);
}
#if __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
DEFINE_INTERN_ALIAS(libc_strtold_l, libc_strtod_l);
#else /* __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__ */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1)) __LONGDOUBLE
NOTHROW_NCX(LIBCCALL libc_strtold_l)(char const *__restrict nptr,
                                     char **endptr,
                                     locale_t locale) {
	(void)locale;
	return libc_strtold(nptr, endptr);
}
#endif /* __SIZEOF_LONG_DOUBLE__ != __SIZEOF_DOUBLE__ */
#include <asm/os/oflags.h>
#include <asm/crt/stdio.h>
#include <bits/os/timeval.h>
#include <bits/os/stat.h>
/* Internal implementation for creating temporary files.
 * @param: what: Select what kind of temporary object to create.
 *                  `0': Create a temporary file. (The handle of that file will be returned)
 *                       Creating mode used is 0600
 *                       This mode is only recognized when `$has_function(open)'
 *                  `1': Create a temporary directory. (0 is returned on success)
 *                       Creating mode used is 0700
 *                       This mode is only recognized when `$has_function(mkdir)'
 *                       NOTE: `flags' is ignored in this mode
 *                  `2': Braindead `mktemp(3)'-mode: Like `0', but don't actually create the
 *                       file. Instead, return `0' on success
 *                       This mode is only recognized when `$has_function(open) || $has_function(stat)'
 *                       NOTE: `flags' is ignored in this mode */
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED NONNULL((2)) fd_t
NOTHROW_RPC(LIBCCALL libc_system_mktemp)(unsigned int what,
                                         char *template_,
                                         __STDC_INT_AS_SIZE_T suffixlen,
                                         oflag_t flags) {
	/* Selection of random letters which  may appear as replacements for  XXXXXX
	 * For this  purpose,  only  use  lower-case letters,  as  well  as  digits.
	 * We  could also  use upper-case letters,  but that may  not work correctly
	 * depending on the calling process running in DOS-mode, or flags containing
	 * O_DOSPATH... */
	static char const letters[] = "abcdefghijklmnopqrstuvwxyz0123456789";
#define NUM_LETTERS 36
	char *xloc = libc_strend(template_) - (suffixlen + 6);
	uint32_t seed, overflow;
	size_t i, attempt;
	fd_t result;

	/* Verify the validity of the input template. */
	if unlikely(xloc < template_ || libc_memcmp(xloc, "XXXXXX", 6 * sizeof(char)) != 0) {
#ifdef EINVAL
		return __libc_seterrno(EINVAL);
#else /* EINVAL */
		return __libc_seterrno(1);
#endif /* !EINVAL */
	}

	/* Calculate an  initial,  random  seed.
	 * For this purpose, try to make use of:
	 *   - gettimeofday()
	 *   - gettid() or getpid()
	 *   - rand() */
	attempt = 0;
again:
	{
#if (defined(__CRT_HAVE_gettimeofday64) || defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday) || defined(__CRT_HAVE___libc_gettimeofday)) && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
		struct timeval64 tv;
		if (libc_gettimeofday64(&tv, NULL) == 0) {
			seed = (uint32_t)(tv.tv_sec) ^
			       (uint32_t)(tv.tv_sec >> 32) ^
			       (uint32_t)(tv.tv_usec << 12); /* The  max value is 0xf423f, so shift
			                                        * that to  become `0xf423f000',  thus
			                                        * filling in the upper bits of `seed' */
		} else
#elif defined(__CRT_HAVE_gettimeofday64) || defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday) || defined(__CRT_HAVE___libc_gettimeofday)
		struct timeval tv;
		if (libc_gettimeofday(&tv, NULL) == 0) {
			seed = (uint32_t)(tv.tv_sec) ^
#if __SIZEOF_TIME_T__ > 4
			       (uint32_t)(tv.tv_sec >> 32) ^
#endif /* __SIZEOF_TIME_T__ > 4 */
			       (uint32_t)(tv.tv_usec << 12); /* The  max value is 0xf423f, so shift
			                                        * that to  become `0xf423f000',  thus
			                                        * filling in the upper bits of `seed' */
		} else
#endif /* ... */
		{
			uint32_t sum;
#ifdef __RAND_MAX
#define LIBC_RAND_MAX __RAND_MAX
#else /* __RAND_MAX */
#define LIBC_RAND_MAX 0x7fff
#endif /* !__RAND_MAX */
			seed = sum = 0;
			/* Generate at least 32 bits of random data. */
			do {
				seed *= LIBC_RAND_MAX;
				seed += (uint32_t)libc_rand();
			} while (!__hybrid_overflow_uadd(sum, LIBC_RAND_MAX, &sum));
#undef LIBC_RAND_MAX
		}
	}
#ifdef __CRT_HAVE_gettid
	seed ^= libc_gettid();
#elif defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid)
	seed ^= libc_getpid();
#endif /* ... */

	/* Using the seed, generate some initial random data.
	 * We've generated 32 bits of entropy above, and with
	 * a total of 6 characters to generate from a pool of
	 * 36 letters each, this 5.333(rep) bits per digit. */
	overflow = seed >> 30;
	for (i = 0; i < 6; ++i) {
		unsigned int digit;
		digit = seed & 0x1f;                      /* digit in 0-31 */
		digit += overflow & ((1 << (i & 3)) - 1); /* Add a random addend between 0-7 */

		/* Right now, digit in 0-38. But because we're using 2 addend, `0' is less
		 * likely than the other digits. As such, subtract a bit if we're not at 0
		 * already. */
		if (digit)
			--digit;
		if (digit)
			--digit;

		/* Now, digit in 0-36, but 36 itself would still be invalid. */
		if (digit > 35)
			digit = 35;

		/* All right! we've got the digit. */
		xloc[i] = letters[digit];
		seed >>= 5;
	}

	/* Try to create/test the file/directory. */
	(void)flags;
	switch (what) {

#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
	case 0: {
#ifdef O_RDWR
#ifdef O_ACCMODE
		flags &= ~O_ACCMODE;
#endif /* O_ACCMODE */
		flags |= O_RDWR;
#endif /* O_RDWR */
#ifdef O_CREAT
		flags |= O_CREAT;
#endif /* O_CREAT */
#ifdef O_EXCL
		flags |= O_EXCL;
#endif /* O_EXCL */
		result = libc_open(template_, flags, 0600);
	}	break;
#endif /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */

#if defined(__CRT_HAVE_mkdir) || defined(__CRT_HAVE___mkdir) || defined(__CRT_HAVE___libc_mkdir) || (defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir))
	case 1:
		result = libc_mkdir(template_, 0700);
		break;
#endif /* __CRT_HAVE_mkdir || __CRT_HAVE___mkdir || __CRT_HAVE___libc_mkdir || (__CRT_DOS_PRIMARY && __CRT_HAVE__mkdir) */

#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))) || (defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_stat) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))) || (defined(__CRT_HAVE_stat64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)))
	case 2: {
#if (defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_stat) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))) || (defined(__CRT_HAVE_stat64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)))
		struct stat st;
		result = stat(template_, &st);
#else /* (__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE__stat32 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE_stat && (!__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) || (__CRT_HAVE_stat64 && (__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) */
		result = libc_open(template_,
#ifdef O_RDONLY
		              O_RDONLY
#elif defined(O_RDWR)
		              O_RDWR
#elif defined(O_WRONLY)
		              O_WRONLY
#else /* ... */
		              0
#endif /* !... */
		              ,
		              0600);
#endif /* (!__CRT_HAVE_kstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kstat64 || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE__stat64 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stat64i32 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stati64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || !__USE_FILE_OFFSET64) && (!__CRT_HAVE__stat32i64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || !__USE_FILE_OFFSET64) && (!__CRT_HAVE__stat || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || __USE_FILE_OFFSET64) && (!__CRT_HAVE__stat32 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || __USE_FILE_OFFSET64) && (!__CRT_HAVE_stat || (__USE_FILE_OFFSET64 && !__STAT32_MATCHES_STAT64)) && (!__CRT_HAVE_stat64 || (!__USE_FILE_OFFSET64 && !__STAT32_MATCHES_STAT64)) */
		if (result < 0) {
			/* File doesn't already exist. */
			result = 0;
		} else {
			/* File does already exist. */
#if (!defined(__CRT_HAVE_kstat) || !defined(__CRT_KOS_PRIMARY)) && (!defined(__CRT_HAVE_kstat64) || !defined(__CRT_KOS_PRIMARY)) && (!defined(__CRT_HAVE__stat64) || !defined(__CRT_DOS_PRIMARY) || !defined(__USE_TIME_BITS64)) && (!defined(__CRT_HAVE__stat64i32) || !defined(__CRT_DOS_PRIMARY) || !defined(__USE_TIME_BITS64)) && (!defined(__CRT_HAVE__stati64) || !defined(__CRT_DOS_PRIMARY) || defined(__USE_TIME_BITS64) || !defined(__USE_FILE_OFFSET64)) && (!defined(__CRT_HAVE__stat32i64) || !defined(__CRT_DOS_PRIMARY) || defined(__USE_TIME_BITS64) || !defined(__USE_FILE_OFFSET64)) && (!defined(__CRT_HAVE__stat) || !defined(__CRT_DOS_PRIMARY) || defined(__USE_TIME_BITS64) || defined(__USE_FILE_OFFSET64)) && (!defined(__CRT_HAVE__stat32) || !defined(__CRT_DOS_PRIMARY) || defined(__USE_TIME_BITS64) || defined(__USE_FILE_OFFSET64)) && (!defined(__CRT_HAVE_stat) || (defined(__USE_FILE_OFFSET64) && !defined(__STAT32_MATCHES_STAT64))) && (!defined(__CRT_HAVE_stat64) || (!defined(__USE_FILE_OFFSET64) && !defined(__STAT32_MATCHES_STAT64))) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close))
			libc_close(result);
#endif /* (!__CRT_HAVE_kstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kstat64 || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE__stat64 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stat64i32 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stati64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || !__USE_FILE_OFFSET64) && (!__CRT_HAVE__stat32i64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || !__USE_FILE_OFFSET64) && (!__CRT_HAVE__stat || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || __USE_FILE_OFFSET64) && (!__CRT_HAVE__stat32 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64 || __USE_FILE_OFFSET64) && (!__CRT_HAVE_stat || (__USE_FILE_OFFSET64 && !__STAT32_MATCHES_STAT64)) && (!__CRT_HAVE_stat64 || (!__USE_FILE_OFFSET64 && !__STAT32_MATCHES_STAT64)) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close) */
#ifdef EEXIST
			result = __libc_seterrno(EEXIST);
#else /* EEXIST */
			result = __libc_seterrno(1);
#endif /* !EEXIST */
#define NEED_do_try_again
			goto do_try_again;
		}
	}	break;
#endif /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) || (__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE__stat32 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE_stat && (!__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) || (__CRT_HAVE_stat64 && (__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) */

	default: __builtin_unreachable();
	}
	if (result == -1) {
		/* Only re-attempt if the error was that the file already existed. */
#if defined(__libc_geterrno) && defined(EEXIST)
		if (__libc_geterrno() == EEXIST)
#endif /* __libc_geterrno && EEXIST */
		{
#ifdef NEED_do_try_again
#undef NEED_do_try_again
do_try_again:
#endif /* NEED_do_try_again */
			/* Limit the max # of attempts */
#ifdef __TMP_MAX
			if (attempt < __TMP_MAX)
#else /* __TMP_MAX */
			if (attempt < 238328)
#endif /* !__TMP_MAX */
			{
				++attempt;
				goto again;
			}
		}
	}
	return result;
}
/* >> shexec(3)
 * Execute command with the system interpreter (such as: `/bin/sh -c $command')
 * This  function is used  to implement `system(3)' and  `popen(3)', and may be
 * used to invoke the system interpreter.
 * This function only returns on failure (similar to exec(2)), and will never
 * return on success (since in that case, the calling program will have  been
 * replaced by the system shell)
 * The shell paths attempted by this function are system-dependent, but before
 * any of them are tested, this function will try to use `getenv("SHELL")', if
 * and only if that variable is defined and starts with a '/'-character. */
INTERN ATTR_SECTION(".text.crt.fs.exec.system") int
NOTHROW_RPC(LIBCCALL libc_shexec)(char const *command) {
	static char const arg_sh[] = "sh";
	static char const arg__c[] = "-c";

#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
	/* Try to make use of $SHELL, if defined and an absolute path. */
	char const *environ_shell = libc_getenv("SHELL");
	if (environ_shell && *environ_shell == '/') {
		char const *environ_shell_sh;
		environ_shell_sh = libc_strrchrnul(environ_shell, '/') + 1;
		libc_execl(environ_shell, environ_shell_sh,
		      arg__c, command, (char *)NULL);
	}
#endif /* __CRT_HAVE_getenv || __LOCAL_environ */


	/* By default, KOS uses busybox, so try to invoke that first. */
	libc_execl("/bin/busybox", arg_sh, arg__c, command, (char *)NULL);
	libc_execl("/bin/sh", arg_sh, arg__c, command, (char *)NULL);
	libc_execl("/bin/bash", arg_sh, arg__c, command, (char *)NULL);





	return -1;
}
#include <libc/template/program_invocation_name.h>
/* Returns the absolute filename of the main executable (s.a. `program_invocation_name') */
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_CONST WUNUSED char const *
NOTHROW_NCX(LIBCCALL libc_getexecname)(void) {
	return __LOCAL_program_invocation_name;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifndef __dwrap_sTPTP_TDTPTIn__SIZEOF_FD_T___c0c1A1_defined
#define __dwrap_sTPTP_TDTPTIn__SIZEOF_FD_T___c0c1A1_defined
struct _dwrap_cookie_struct_sTPTP_TDTPTIn__SIZEOF_FD_T___c0c1A1 {
	int (LIBDCALL *walk)(void *arg, fd_t fd);
	void *arg;
};
PRIVATE ATTR_SECTION(".text.crt.dos.solaris") int
(LIBCCALL _dwrap_sTPTP_TDTPTIn__SIZEOF_FD_T___c0c1A1)(struct _dwrap_cookie_struct_sTPTP_TDTPTIn__SIZEOF_FD_T___c0c1A1 *c,
                                                      fd_t fd) THROWS(...) {
	return (*c->walk)(c->arg, fd);
}
#endif /* !__dwrap_sTPTP_TDTPTIn__SIZEOF_FD_T___c0c1A1_defined */
/* Enumerate all open file descriptors by  invoking `(*walk)(arg, <fd>)' for each of  them
 * If during any of these invocations, `(*walk)(...)' returns non-zero, enumeration stops,
 * and  `fdwalk()' returns with that same value. If `(*walk)(...)' is never called, or all
 * invocations return 0, `fdwalk()' will also return 0. */
INTERN ATTR_SECTION(".text.crt.dos.solaris") NONNULL((1)) int
(LIBDCALL libd_fdwalk)(int (LIBDCALL *walk)(void *arg, fd_t fd),
                       void *arg) THROWS(...) {
	struct _dwrap_cookie_struct_sTPTP_TDTPTIn__SIZEOF_FD_T___c0c1A1 libd_fdwalk_cookie;
	libd_fdwalk_cookie.walk = walk;
	libd_fdwalk_cookie.arg  = arg;
	return libc_fdwalk((int (LIBCCALL *)(void *, fd_t))&_dwrap_sTPTP_TDTPTIn__SIZEOF_FD_T___c0c1A1, &libd_fdwalk_cookie);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <asm/os/fcntl.h>
/* Enumerate all open file descriptors by  invoking `(*walk)(arg, <fd>)' for each of  them
 * If during any of these invocations, `(*walk)(...)' returns non-zero, enumeration stops,
 * and  `fdwalk()' returns with that same value. If `(*walk)(...)' is never called, or all
 * invocations return 0, `fdwalk()' will also return 0. */
INTERN ATTR_SECTION(".text.crt.solaris") NONNULL((1)) int
(LIBCCALL libc_fdwalk)(int (LIBCCALL *walk)(void *arg, fd_t fd),
                       void *arg) THROWS(...) {
	/* TODO: Implementation alternative using `opendir("/proc/self/fd")' */
	int result = 0;
#ifdef __libc_geterrno
	errno_t saved_err;
#endif /* __libc_geterrno */
	fd_t fd = 0;
	for (;;) {
#ifdef __libc_geterrno
		saved_err = __libc_geterrno();
#endif /* __libc_geterrno */
		/* fcntl(F_NEXT) returns the next valid  (i.e.
		 * currently open) fd that is >= the given fd. */
		fd = libc_fcntl(fd, __F_NEXT);
		if (fd < 0) {
#ifdef __libc_geterrno
			(void)__libc_seterrno(saved_err);
#endif /* __libc_geterrno */
			break;
		}
		result = (*walk)(arg, fd);
		if (result != 0)
			break;
		++fd;
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_RETNONNULL WUNUSED NONNULL((2)) char *
NOTHROW_NCX(LIBCCALL libc_lltostr)(__LONGLONG value,
                                   char *buf) {
	char *result;
	if (value < 0) {
		result    = libc_ulltostr((__ULONGLONG)0 - value, buf);
		*--result = '-';
	} else {
		result = libc_ulltostr((__ULONGLONG)value, buf);
	}
	return result;
}
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_RETNONNULL WUNUSED NONNULL((2)) char *
NOTHROW_NCX(LIBCCALL libc_ulltostr)(__ULONGLONG value,
                                    char *buf) {
	do {
		*--buf = itoa_decimal(value % 10);
	} while ((value /= 10) != 0);
	return buf;
}
#include <asm/crt/malloc.h>
INTERN ATTR_SECTION(".text.crt.heap.rare_helpers") ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBCCALL libc_reallocf)(void *mallptr,
                                    size_t num_bytes) {
	void *result;
	result = libc_realloc(mallptr, num_bytes);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#ifdef __REALLOC_ZERO_IS_NONNULL
	if unlikely(!result)
#else /* __REALLOC_ZERO_IS_NONNULL */
	/* Must check that num_bytes != 0 because if it isn't
	 * (iow: num_bytes == 0), then realloc(mallptr, 0) may
	 * act  the same as  `free(mallptr)'. If that happens,
	 * then we mustn't double-free `mallptr'.
	 * Note that realloc(<non-NULL>, 0) can't possibly fail
	 * for  lack  of memory  if `__REALLOC_ZERO_IS_NONNULL'
	 * was guessed incorrectly, so we know that the realloc
	 * can only fail when  returning `NULL' for a  non-zero
	 * size argument! */
	if unlikely(!result && num_bytes != 0)
#endif /* !__REALLOC_ZERO_IS_NONNULL */
	{
		libc_free(mallptr);
	}
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return result;
}
/* >> l64a_r(3)
 * Reentrant variant of `l64a(3)'. Note that the max required buffer size
 * @param: buf:     Target buffer (with a size of `bufsize' bytes)
 * @param: bufsize: Buffer size (including a trailing NUL-character)
 * @return: 0 : Success
 * @return: -1: Buffer too small (`errno' was not modified) */
INTERN ATTR_SECTION(".text.crt.bsd") int
NOTHROW_NCX(LIBCCALL libc_l64a_r)(long n,
                                  char *buf,
                                  __STDC_INT_AS_SIZE_T bufsize) {
	unsigned long un;
	/* Mapping from digit values --> base-64 characters. */
	static char const chrs[64] = {
		'.', '/', '0', '1', '2', '3', '4', '5',
		'6', '7', '8', '9', 'A', 'B', 'C', 'D',
		'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
		'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b',
		'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
		'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
		's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
	};
	un = (unsigned long )n;
	while (bufsize) {
		--bufsize;
		if (!un) {
			/* Done! */
			*buf = '\0';
			return 0;
		}
		/* Encode 1 character. */
		*buf++ = chrs[un & 0x3f];
		un >>= 6;
	}
	return -1;

}
/* >> getprogname(3), setprogname(3) */
INTERN ATTR_SECTION(".text.crt.bsd") ATTR_CONST WUNUSED char const *
NOTHROW_NCX(LIBCCALL libc_getprogname)(void) {
	return program_invocation_short_name;
}
/* >> getprogname(3), setprogname(3) */
INTERN ATTR_SECTION(".text.crt.bsd") void
NOTHROW_NCX(LIBCCALL libc_setprogname)(char const *name) {
	__LOCAL_program_invocation_short_name_p = (char *)name;
}
INTERN ATTR_SECTION(".text.crt.bsd") NONNULL((1, 4)) int
(LIBCCALL libc_heapsort)(void *pbase,
                         size_t item_count,
                         size_t item_size,
                         int (LIBCCALL *compar)(void const *a, void const *b)) THROWS(...) {
	/* TODO: Actually do heap-sort! */
	libc_qsort(pbase, item_count, item_size, compar);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.bsd") NONNULL((1, 4)) int
(LIBCCALL libc_mergesort)(void *pbase,
                          size_t item_count,
                          size_t item_size,
                          int (LIBCCALL *compar)(void const *a, void const *b)) THROWS(...) {
	/* TODO: Actually do merge-sort! */
	libc_qsort(pbase, item_count, item_size, compar);
	return 0;
}
#include <bits/types.h>
/* >> strtonum(3)
 * Similar to `strtoi()'  with `base=10',  but return  human-
 * readable error messages in `*p_errstr' on error (alongside
 * `return==0') (or `NULL' on success).
 * The following messages are defined:
 *   - "too large": Numeric value is too great (`ERANGE' && greater than `hi')
 *   - "too small": Numeric value is too small (`ERANGE' && less than `lo')
 *   - "invalid":   Any other error (`ENOTSUP' or `ECANCELED')
 * @return: 0 : [*p_errstr != NULL] Error
 * @return: 0 : [*p_errstr == NULL] Success
 * @return: * : [*p_errstr == NULL] Success */
INTERN ATTR_SECTION(".text.crt.bsd") WUNUSED NONNULL((1, 4)) __LONGLONG
NOTHROW_NCX(LIBCCALL libc_strtonum)(char const *nptr,
                                    __LONGLONG lo,
                                    __LONGLONG hi,
                                    char const **p_errstr) {
	errno_t error;
	__LONGLONG result;
	result = (__LONGLONG)libc_strtoi(nptr, NULL, 10, lo, hi, &error);
	if (error == 0) {
		if (p_errstr)
			*p_errstr = NULL;
		return result;
	}
	if (p_errstr) {
		*p_errstr = "invalid";
#ifdef ERANGE
		if (error == ERANGE) {
			*p_errstr = "too large";
			if (result == lo)
				*p_errstr = "too small";
		}
#endif /* ERANGE */
	}
	return 0;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifndef __dwrap_sTPTP_TDTPTPTP_c0A0A1c1_defined
#define __dwrap_sTPTP_TDTPTPTP_c0A0A1c1_defined
struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0A0A1c1 {
	int (LIBDCALL *compar)(void const *a, void const *b, void *arg);
	void *arg;
};
PRIVATE ATTR_SECTION(".text.crt.dos.utility.stdlib") int
(LIBCCALL _dwrap_sTPTP_TDTPTPTP_c0A0A1c1)(void const *a,
                                          void const *b,
                                          struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0A0A1c1 *c) THROWS(...) {
	return (*c->compar)(a, b, c->arg);
}
#endif /* !__dwrap_sTPTP_TDTPTPTP_c0A0A1c1_defined */
INTERN ATTR_SECTION(".text.crt.dos.utility.stdlib") NONNULL((1, 4)) void
(LIBDCALL libd_qsort_r)(void *pbase,
                        size_t item_count,
                        size_t item_size,
                        int (LIBDCALL *compar)(void const *a, void const *b, void *arg),
                        void *arg) THROWS(...) {
	struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0A0A1c1 libd_qsort_r_cookie;
	libd_qsort_r_cookie.compar = compar;
	libd_qsort_r_cookie.arg    = arg;
	libc_qsort_r(pbase, item_count, item_size, (int (LIBCCALL *)(void const *, void const *, void *))&_dwrap_sTPTP_TDTPTPTP_c0A0A1c1, &libd_qsort_r_cookie);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
INTERN ATTR_SECTION(".text.crt.utility.stdlib") NONNULL((1, 4)) void
(LIBCCALL libc_qsort_r)(void *pbase,
                        size_t item_count,
                        size_t item_size,
                        int (LIBCCALL *compar)(void const *a, void const *b, void *arg),
                        void *arg) THROWS(...) {
	/* A public domain qsort() drop-in implementation. I couldn't find the original
	 * source referenced (see the comment below), but this code is the first  thing
	 * that comes up when you search for `libc qsort public domain'.
	 * https://git.busybox.net/uClibc/tree/libc/stdlib/stdlib.c#n770
	 *
	 * Note that I made some modifications, and you should see the linked source for
	 * the original code.
	 *
	 * WARNING: This function's logic will break in situations where `item_count' is
	 *          greater than or equal to:
	 *  - sizeof(size_t) == 4: item_count >= 0x67ea0dc9         (> 2.5 GiB of data at least)
	 *  - sizeof(size_t) == 8: item_count >= 0xfd150e7b3dafdc31 (an insane amount of memory...)
	 *
	 * But I would argue that this isn't something that could ever feasibly happen, and
	 * even speaking architecturally, this isn't something that _can_ happen on x86_64.
	 * It ~could~ happen on i386, but I very much doubt that there is any justification
	 * as to why it should.
	 *
	 * ================= Documented origin =================
	 *  ssort()  --  Fast, small, qsort()-compatible Shell sort
	 *
	 *  by Ray Gardner,  public domain   5/90
	 */
	size_t total_bytes, gap;
	total_bytes = item_size * item_count;
	for (gap = 0; ++gap < item_count;)
		gap *= 3;
	while ((gap /= 3) != 0) {
		size_t i, gap_bytes;
		gap_bytes = item_size * gap;
		for (i = gap_bytes; i < total_bytes; i += item_size) {
			size_t j;
			for (j = i - gap_bytes;; j -= gap_bytes) {
				size_t swap_index;
				byte_t tmp, *a, *b;
				a = (byte_t *)pbase + j;
				b = a + gap_bytes;
				if ((*compar)(a, b, arg) <= 0)
					break;
				swap_index = item_size;
				do {
					tmp  = *a;
					*a++ = *b;
					*b++ = tmp;
				} while (--swap_index);
				if (j < gap_bytes)
					break;
			}
		}
	}
}
#ifndef __KERNEL__
/* >> mkostemp(3), mkostemp64(3)
 * Replace  the  last 6  characters of  `template_' (which  are followed  by exactly
 * `suffixlen'  more  characters that  are left  alone), which  must be  filled with
 * all  'X'-characters  before  the  call  (else  errno=EINVAL  +  return  -1), with
 * random  characters  such  that the  filename  described by  `template_'  will not
 * already exists. Then, create a new file with `O_RDWR | flags' and return the file
 * descriptor of that file.
 * @param: flags: Additional  flags  to pass  to `open(2)',
 *                but `O_ACCMODE' is always set to `O_RDWR' */
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED NONNULL((1)) fd_t
NOTHROW_NCX(LIBCCALL libc_mkostemp)(char *template_,
                                    oflag_t flags) {
	return libc_mkostemps(template_, 0, flags);
}
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED NONNULL((1)) fd_t
NOTHROW_NCX(LIBCCALL libc_mkostemps)(char *template_,
                                     __STDC_INT_AS_SIZE_T suffixlen,
                                     oflag_t flags) {
	return libc_system_mktemp(0, template_, suffixlen, flags);
}
#include <asm/os/oflags.h>
#if !defined(__O_LARGEFILE) || !__O_LARGEFILE
DEFINE_INTERN_ALIAS(libc_mkostemp64, libc_mkostemp);
#else /* !__O_LARGEFILE || !__O_LARGEFILE */
/* >> mkostemp(3), mkostemp64(3)
 * Replace  the  last 6  characters of  `template_' (which  are followed  by exactly
 * `suffixlen'  more  characters that  are left  alone), which  must be  filled with
 * all  'X'-characters  before  the  call  (else  errno=EINVAL  +  return  -1), with
 * random  characters  such  that the  filename  described by  `template_'  will not
 * already exists. Then, create a new file with `O_RDWR | flags' and return the file
 * descriptor of that file.
 * @param: flags: Additional  flags  to pass  to `open(2)',
 *                but `O_ACCMODE' is always set to `O_RDWR' */
INTERN ATTR_SECTION(".text.crt.bsd") WUNUSED NONNULL((1)) fd_t
NOTHROW_NCX(LIBCCALL libc_mkostemp64)(char *template_,
                                      oflag_t flags) {
	return libc_mkostemps64(template_, 0, flags);
}
#endif /* __O_LARGEFILE && __O_LARGEFILE */
#include <asm/os/oflags.h>
#if !defined(__O_LARGEFILE) || !__O_LARGEFILE
DEFINE_INTERN_ALIAS(libc_mkostemps64, libc_mkostemps);
#else /* !__O_LARGEFILE || !__O_LARGEFILE */
INTERN ATTR_SECTION(".text.crt.bsd") WUNUSED NONNULL((1)) fd_t
NOTHROW_NCX(LIBCCALL libc_mkostemps64)(char *template_,
                                       __STDC_INT_AS_SIZE_T suffixlen,
                                       oflag_t flags) {
#ifdef O_LARGEFILE
	return libc_system_mktemp(0, template_, suffixlen, flags | O_LARGEFILE);
#else /* O_LARGEFILE */
	return libc_system_mktemp(0, template_, suffixlen, flags);
#endif /* !O_LARGEFILE */
}
#endif /* __O_LARGEFILE && __O_LARGEFILE */
/* >> devname(3), devname_r(3) */
INTERN ATTR_SECTION(".text.crt.bsd") ATTR_CONST char *
NOTHROW_NCX(LIBCCALL libc_devname)(dev_t dev,
                                   mode_t type) {
	static char buf[64];
	return libc_devname_r(dev, type, buf, sizeof(buf)) ? NULL : buf;
}
#include <asm/os/stdlib.h>
/* >> strsuftoll(3)
 * Same as `strsuftollx(3)', but if an error happens, make
 * use of `errx(3)' to terminate the program, rather  than
 * return to the caller. */
INTERN ATTR_SECTION(".text.crt.bsd") WUNUSED NONNULL((1, 2)) __LONGLONG
NOTHROW_NCX(LIBCCALL libc_strsuftoll)(char const *desc,
                                      char const *val,
                                      __LONGLONG lo,
                                      __LONGLONG hi) {
	__LONGLONG result;
	char error_message[128];
	result = libc_strsuftollx(desc, val, lo, hi,
	                     error_message,
	                     sizeof(error_message));
	if (result == 0 && *error_message) {
#ifdef __EXIT_FAILURE
		libc_errx(__EXIT_FAILURE, "%s", error_message);
#else /* __EXIT_FAILURE */
		libc_errx(1, "%s", error_message);
#endif /* !__EXIT_FAILURE */
	}
	return result;
}
/* >> strsuftollx(3) */
INTERN ATTR_SECTION(".text.crt.bsd") WUNUSED NONNULL((1, 2)) __LONGLONG
NOTHROW_NCX(LIBCCALL libc_strsuftollx)(char const *desc,
                                       char const *val,
                                       __LONGLONG lo,
                                       __LONGLONG hi,
                                       char *errbuf,
                                       size_t errbuflen) {
	/* TODO */
	(void)desc;
	(void)lo;
	(void)hi;
	if (errbuflen)
		*errbuf = 0;
	return libc_strtoll(val, NULL, 10);
}
#include <libc/template/program_invocation_name.h>
/* Alias for argv[0], as passed to main() */
INTERN ATTR_SECTION(".text.crt.dos.application.init") ATTR_CONST ATTR_RETNONNULL WUNUSED char **
NOTHROW_NCX(LIBCCALL libc___p__pgmptr)(void) {
	return &__LOCAL_program_invocation_name_p;
}
#include <libc/template/program_invocation_name.h>
INTERN ATTR_SECTION(".text.crt.dos.application.init") errno_t
NOTHROW_NCX(LIBCCALL libc__get_pgmptr)(char **pvalue) {
	*pvalue = __LOCAL_program_invocation_name;
	return EOK;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.application.init") errno_t
NOTHROW_NCX(LIBDCALL libd__get_wpgmptr)(char16_t **pvalue) {
	*pvalue = *libd___p__wpgmptr();
	return EOK;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.application.init") errno_t
NOTHROW_NCX(LIBKCALL libc__get_wpgmptr)(char32_t **pvalue) {
	*pvalue = *libc___p__wpgmptr();
	return EOK;
}
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS(libc__abs64, libc_abs);
#elif __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__abs64, libc_llabs);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED __INT64_TYPE__
NOTHROW(LIBCCALL libc__abs64)(__INT64_TYPE__ x) {
	return x < 0 ? -x : x;
}
#endif /* !... */
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) double
NOTHROW_NCX(LIBCCALL libc__atof_l)(char const *__restrict nptr,
                                   locale_t locale) {
	return libc_strtod_l(nptr, NULL, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc__atoi_l)(char const *__restrict nptr,
                                   locale_t locale) {
	return (int)libc_strtol_l(nptr, NULL, 10, locale);
}
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc__atol_l, libc__atoi_l);
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) long int
NOTHROW_NCX(LIBCCALL libc__atol_l)(char const *__restrict nptr,
                                   locale_t locale) {
	return libc_strtol_l(nptr, NULL, 10, locale);
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_INT__ */
#if __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc__atoll_l, libc__atol_l);
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc__atoll_l, libc__atoi_l);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBCCALL libc__atoll_l)(char const *__restrict nptr,
                                    locale_t locale) {
	return libc_strtoll_l(nptr, NULL, 10, locale);
}
#endif /* !... */
#include <hybrid/__byteswap.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED u16
NOTHROW_NCX(LIBCCALL libc__byteswap_ushort)(u16 val) {
	return __hybrid_bswap16(val);
}
#include <hybrid/__byteswap.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED u32
NOTHROW_NCX(LIBCCALL libc__byteswap_ulong)(u32 val) {
	return __hybrid_bswap32(val);
}
#include <hybrid/__byteswap.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED u64
NOTHROW_NCX(LIBCCALL libc__byteswap_uint64)(u64 val) {
	return __hybrid_bswap64(val);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifndef __dwrap_sTPTP_TDTPTPTP_c0c1A0A1_defined
#define __dwrap_sTPTP_TDTPTPTP_c0c1A0A1_defined
struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0c1A0A1 {
	int (LIBDCALL *compar)(void *arg, void const *a, void const *b);
	void *arg;
};
PRIVATE ATTR_SECTION(".text.crt.dos.utility") int
(LIBCCALL _dwrap_sTPTP_TDTPTPTP_c0c1A0A1)(void const *a,
                                          void const *b,
                                          struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0c1A0A1 *c) THROWS(...) {
	return (*c->compar)(c->arg, a, b);
}
#endif /* !__dwrap_sTPTP_TDTPTPTP_c0c1A0A1_defined */
INTERN ATTR_SECTION(".text.crt.dos.utility") WUNUSED NONNULL((1, 2, 5)) void *
(LIBDCALL libd_bsearch_s)(void const *key,
                          void const *base,
                          size_t elem_count,
                          size_t elem_size,
                          int (LIBDCALL *compar)(void *arg, void const *a, void const *b),
                          void *arg) THROWS(...) {
	struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0c1A0A1 libd_bsearch_s_cookie;
	libd_bsearch_s_cookie.compar = compar;
	libd_bsearch_s_cookie.arg    = arg;
	return libc_bsearch_r(key, base, elem_count, elem_size, (int (LIBCCALL *)(void const *, void const *, void *))&_dwrap_sTPTP_TDTPTPTP_c0c1A0A1, &libd_bsearch_s_cookie);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#ifndef ____invoke_compare_helper_s_defined
#define ____invoke_compare_helper_s_defined
__NAMESPACE_LOCAL_BEGIN
struct __invoke_compare_helper_s_data {
	int (__LIBCCALL *__fun)(void *__arg, void const *__a, void const *__b);
	void            *__arg;
};
__LOCAL_LIBC(__invoke_compare_helper_s) int
(__LIBCCALL __invoke_compare_helper_s)(void const *__a, void const *__b, void *__arg) {
	void *__base_arg = ((struct __invoke_compare_helper_s_data *)__arg)->__arg;
	return (*((struct __invoke_compare_helper_s_data *)__arg)->__fun)(__base_arg, __a, __b);
}
__NAMESPACE_LOCAL_END
#endif /* !____invoke_compare_helper_s_defined */
INTERN ATTR_SECTION(".text.crt.dos.utility") WUNUSED NONNULL((1, 2, 5)) void *
(LIBCCALL libc_bsearch_s)(void const *key,
                          void const *base,
                          size_t elem_count,
                          size_t elem_size,
                          int (LIBCCALL *compar)(void *arg, void const *a, void const *b),
                          void *arg) THROWS(...) {
	struct __NAMESPACE_LOCAL_SYM __invoke_compare_helper_s_data data;
	data.__fun = compar;
	data.__arg = arg;
	return (void *)libc_bsearch_r(key, base, elem_count, elem_size,
	                         &__NAMESPACE_LOCAL_SYM __invoke_compare_helper_s,
	                         &data);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifndef __dwrap_sTPTP_TDTPTPTP_c0c1A0A1_defined
#define __dwrap_sTPTP_TDTPTPTP_c0c1A0A1_defined
struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0c1A0A1 {
	int (LIBDCALL *compar)(void *arg, void const *a, void const *b);
	void *arg;
};
PRIVATE ATTR_SECTION(".text.crt.dos.utility") int
(LIBCCALL _dwrap_sTPTP_TDTPTPTP_c0c1A0A1)(void const *a,
                                          void const *b,
                                          struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0c1A0A1 *c) THROWS(...) {
	return (*c->compar)(c->arg, a, b);
}
#endif /* !__dwrap_sTPTP_TDTPTPTP_c0c1A0A1_defined */
INTERN ATTR_SECTION(".text.crt.dos.utility") NONNULL((1, 4)) void
(LIBDCALL libd_qsort_s)(void *base,
                        size_t elem_count,
                        size_t elem_size,
                        int (LIBDCALL *compar)(void *arg, void const *a, void const *b),
                        void *arg) THROWS(...) {
	struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0c1A0A1 libd_qsort_s_cookie;
	libd_qsort_s_cookie.compar = compar;
	libd_qsort_s_cookie.arg    = arg;
	libc_qsort_r(base, elem_count, elem_size, (int (LIBCCALL *)(void const *, void const *, void *))&_dwrap_sTPTP_TDTPTPTP_c0c1A0A1, &libd_qsort_s_cookie);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#ifndef ____invoke_compare_helper_s_defined
#define ____invoke_compare_helper_s_defined
__NAMESPACE_LOCAL_BEGIN
struct __invoke_compare_helper_s_data {
	int (__LIBCCALL *__fun)(void *__arg, void const *__a, void const *__b);
	void            *__arg;
};
__LOCAL_LIBC(__invoke_compare_helper_s) int
(__LIBCCALL __invoke_compare_helper_s)(void const *__a, void const *__b, void *__arg) {
	void *__base_arg = ((struct __invoke_compare_helper_s_data *)__arg)->__arg;
	return (*((struct __invoke_compare_helper_s_data *)__arg)->__fun)(__base_arg, __a, __b);
}
__NAMESPACE_LOCAL_END
#endif /* !____invoke_compare_helper_s_defined */
INTERN ATTR_SECTION(".text.crt.dos.utility") NONNULL((1, 4)) void
(LIBCCALL libc_qsort_s)(void *base,
                        size_t elem_count,
                        size_t elem_size,
                        int (LIBCCALL *compar)(void *arg, void const *a, void const *b),
                        void *arg) THROWS(...) {
	struct __NAMESPACE_LOCAL_SYM __invoke_compare_helper_s_data data;
	data.__fun = compar;
	data.__arg = arg;
	return libc_qsort_r(base, elem_count, elem_size,
	               &__NAMESPACE_LOCAL_SYM __invoke_compare_helper_s,
	               &data);
}
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc__itoa_s)(int val,
                                   char *buf,
                                   size_t buflen,
                                   int radix) {
	char *p;
	int temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
#ifdef ERANGE
			return ERANGE;
#else /* ERANGE */
			return 1;
#endif /* !ERANGE */
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do {
		++p;
	} while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned int)radix];
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc__ltoa_s, libc__itoa_s);
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc__ltoa_s)(long val,
                                   char *buf,
                                   size_t buflen,
                                   int radix) {
	char *p;
	long temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
#ifdef ERANGE
			return ERANGE;
#else /* ERANGE */
			return 1;
#endif /* !ERANGE */
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do {
		++p;
	} while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned int)radix];
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_INT__ */
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc__ultoa_s)(unsigned long val,
                                    char *buf,
                                    size_t buflen,
                                    int radix) {
	char *p;
	unsigned long temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;
	temp = val;
	do {
		++p;
	} while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned int)radix];
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS(libc__i64toa, libc_itoa);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__i64toa, libc_ltoa);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) char *
NOTHROW_NCX(LIBCCALL libc__i64toa)(s64 val,
                                   char *buf,
                                   int radix) {
	libc__i64toa_s(val, buf, (size_t)-1, radix);
	return buf;
}
#endif /* !... */
#if __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__ui64toa, libc_ultoa);
#else /* __SIZEOF_LONG__ == 8 */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) char *
NOTHROW_NCX(LIBCCALL libc__ui64toa)(u64 val,
                                    char *buf,
                                    int radix) {
	libc__ui64toa_s(val, buf, (size_t)-1, radix);
	return buf;
}
#endif /* __SIZEOF_LONG__ != 8 */
#if __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__i64toa_s, libc__ltoa_s);
#elif __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS(libc__i64toa_s, libc__itoa_s);
#else /* ... */
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc__i64toa_s)(s64 val,
                                     char *buf,
                                     size_t buflen,
                                     int radix) {
	char *p;
	s64 temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
#ifdef ERANGE
			return ERANGE;
#else /* ERANGE */
			return 1;
#endif /* !ERANGE */
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do {
		++p;
	} while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned int)radix];
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#endif /* !... */
#if __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__ui64toa_s, libc__ultoa_s);
#else /* __SIZEOF_LONG__ == 8 */
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc__ui64toa_s)(u64 val,
                                      char *buf,
                                      size_t buflen,
                                      int radix) {
	char *p;
	u64 temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;
	temp = val;
	do {
		++p;
	} while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned int)radix];
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#endif /* __SIZEOF_LONG__ != 8 */
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS(libc__atoi64, libc_atoi);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__atoi64, libc_atol);
#elif __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__atoi64, libc_atoll);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) s64
NOTHROW_NCX(LIBCCALL libc__atoi64)(char const *__restrict nptr) {
	return libc_strto64(nptr, NULL, 10);
}
#endif /* !... */
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS(libc__atoi64_l, libc__atoi_l);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__atoi64_l, libc__atol_l);
#elif __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__atoi64_l, libc__atoll_l);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) s64
NOTHROW_NCX(LIBCCALL libc__atoi64_l)(char const *__restrict nptr,
                                     locale_t locale) {
	return libc_strto64_l(nptr, NULL, 10, locale);
}
#endif /* !... */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbstrlen)(char const *str) {
	size_t result = 0;
	while (libc_unicode_readutf8((char const **)&str))
		++result;
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbstrnlen)(char const *str,
                                      size_t maxlen) {
	size_t result = 0;
	char const *endptr = str + maxlen;
	while (libc_unicode_readutf8_n((char const **)&str, endptr))
		++result;
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbstrlen_l)(char const *str,
                                       locale_t locale) {
	(void)locale;
	return libc__mbstrlen(str);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbstrnlen_l)(char const *str,
                                        size_t maxlen,
                                        locale_t locale) {
	(void)locale;
	return libc__mbstrnlen(str, maxlen);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc__mblen_l)(char const *str,
                                    size_t maxlen,
                                    locale_t locale) {
	(void)locale;
	return libc_mblen(str, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBDCALL libd__mbtowc_l)(char16_t *dst,
                                     char const *src,
                                     size_t srclen,
                                     locale_t locale) {
	(void)locale;
	return libd_mbtowc(dst, src, srclen);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBKCALL libc__mbtowc_l)(char32_t *dst,
                                     char const *src,
                                     size_t srclen,
                                     locale_t locale) {
	(void)locale;
	return libc_mbtowc(dst, src, srclen);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") size_t
NOTHROW_NCX(LIBDCALL libd__mbstowcs_l)(char16_t *dst,
                                       char const *src,
                                       size_t dstlen,
                                       locale_t locale) {
	(void)locale;
	return libd_mbstowcs(dst, src, dstlen);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") size_t
NOTHROW_NCX(LIBKCALL libc__mbstowcs_l)(char32_t *dst,
                                       char const *src,
                                       size_t dstlen,
                                       locale_t locale) {
	(void)locale;
	return libc_mbstowcs(dst, src, dstlen);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") errno_t
NOTHROW_NCX(LIBDCALL libd__mbstowcs_s)(size_t *presult,
                                       char16_t *dst,
                                       size_t dstsize,
                                       char const *src,
                                       size_t dstlen) {
	size_t error;
	if (dstlen >= dstsize) {
		if (!dstsize)
			return 0;
		dstlen = dstsize - 1;
	}
	error = libd_mbstowcs(dst, src, dstlen);
	if (presult)
		*presult = error;
#ifdef EILSEQ
	if (error == (size_t)-1)
		return EILSEQ;
#endif /* EILSEQ */
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") errno_t
NOTHROW_NCX(LIBKCALL libc__mbstowcs_s)(size_t *presult,
                                       char32_t *dst,
                                       size_t dstsize,
                                       char const *src,
                                       size_t dstlen) {
	size_t error;
	if (dstlen >= dstsize) {
		if (!dstsize)
			return 0;
		dstlen = dstsize - 1;
	}
	error = libc_mbstowcs(dst, src, dstlen);
	if (presult)
		*presult = error;
#ifdef EILSEQ
	if (error == (size_t)-1)
		return EILSEQ;
#endif /* EILSEQ */
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") errno_t
NOTHROW_NCX(LIBDCALL libd_mbstowcs_s)(size_t *presult,
                                      char16_t *dst,
                                      size_t dstsize,
                                      char const *src,
                                      size_t dstlen) {
	size_t error;
	if (dstlen >= dstsize) {
		if (!dstsize)
			return 0;
		dstlen = dstsize - 1;
	}
	error = libd_mbstowcs(dst, src, dstlen);
	if (presult)
		*presult = error;
#ifdef EILSEQ
	if (error == (size_t)-1)
		return EILSEQ;
#endif /* EILSEQ */
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") errno_t
NOTHROW_NCX(LIBKCALL libc_mbstowcs_s)(size_t *presult,
                                      char32_t *dst,
                                      size_t dstsize,
                                      char const *src,
                                      size_t dstlen) {
	size_t error;
	if (dstlen >= dstsize) {
		if (!dstsize)
			return 0;
		dstlen = dstsize - 1;
	}
	error = libc_mbstowcs(dst, src, dstlen);
	if (presult)
		*presult = error;
#ifdef EILSEQ
	if (error == (size_t)-1)
		return EILSEQ;
#endif /* EILSEQ */
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") errno_t
NOTHROW_NCX(LIBDCALL libd__mbstowcs_s_l)(size_t *presult,
                                         char16_t *dst,
                                         size_t dstsize,
                                         char const *src,
                                         size_t dstlen,
                                         locale_t locale) {
	size_t error;
	if (dstlen >= dstsize) {
		if (!dstsize)
			return 0;
		dstlen = dstsize - 1;
	}
	error = libd__mbstowcs_l(dst, src, dstlen, locale);
	if (presult)
		*presult = error;
#ifdef EILSEQ
	if (error == (size_t)-1)
		return EILSEQ;
#endif /* EILSEQ */
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") errno_t
NOTHROW_NCX(LIBKCALL libc__mbstowcs_s_l)(size_t *presult,
                                         char32_t *dst,
                                         size_t dstsize,
                                         char const *src,
                                         size_t dstlen,
                                         locale_t locale) {
	size_t error;
	if (dstlen >= dstsize) {
		if (!dstsize)
			return 0;
		dstlen = dstsize - 1;
	}
	error = libc__mbstowcs_l(dst, src, dstlen, locale);
	if (presult)
		*presult = error;
#ifdef EILSEQ
	if (error == (size_t)-1)
		return EILSEQ;
#endif /* EILSEQ */
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_rand_s)(unsigned int *__restrict randval) {
	if (!randval) {
#ifdef EINVAL
		return EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	*randval = libc_rand();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBDCALL libd__wctomb_l)(char *buf,
                                     char16_t wc,
                                     locale_t locale) {
	(void)locale;
	return libd_wctomb(buf, wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBKCALL libc__wctomb_l)(char *buf,
                                     char32_t wc,
                                     locale_t locale) {
	(void)locale;
	return libc_wctomb(buf, wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBDCALL libd_wctomb_s)(int *presult,
                                    char *buf,
                                    rsize_t buflen,
                                    char16_t wc) {
	if (!presult || !buf) {
#ifdef EINVAL
		return EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	if (buflen < MB_CUR_MAX) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	*presult = libd_wctomb(buf, wc);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBKCALL libc_wctomb_s)(int *presult,
                                    char *buf,
                                    rsize_t buflen,
                                    char32_t wc) {
	if (!presult || !buf) {
#ifdef EINVAL
		return EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	if (buflen < MB_CUR_MAX) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	*presult = libc_wctomb(buf, wc);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBDCALL libd__wctomb_s_l)(int *presult,
                                       char *buf,
                                       size_t buflen,
                                       char16_t wc,
                                       locale_t locale) {
	(void)locale;
	return libd_wctomb_s(presult, buf, buflen, wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBKCALL libc__wctomb_s_l)(int *presult,
                                       char *buf,
                                       size_t buflen,
                                       char32_t wc,
                                       locale_t locale) {
	(void)locale;
	return libc_wctomb_s(presult, buf, buflen, wc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((1, 2, 4)) errno_t
NOTHROW_NCX(LIBDCALL libd__wcstombs_s_l)(size_t *presult,
                                         char *buf,
                                         size_t buflen,
                                         char16_t const *src,
                                         size_t maxlen,
                                         locale_t locale) {
	(void)locale;
	return libd_wcstombs_s(presult, buf, buflen, src, maxlen);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((1, 2, 4)) errno_t
NOTHROW_NCX(LIBKCALL libc__wcstombs_s_l)(size_t *presult,
                                         char *buf,
                                         size_t buflen,
                                         char32_t const *src,
                                         size_t maxlen,
                                         locale_t locale) {
	(void)locale;
	return libc_wcstombs_s(presult, buf, buflen, src, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd__wcstombs_l)(char *dst,
                                       char16_t const *src,
                                       size_t maxlen,
                                       locale_t locale) {
	(void)locale;
	return libd_wcstombs(dst, src, maxlen);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc__wcstombs_l)(char *dst,
                                       char32_t const *src,
                                       size_t maxlen,
                                       locale_t locale) {
	(void)locale;
	return libc_wcstombs(dst, src, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((1, 2, 4)) errno_t
NOTHROW_NCX(LIBDCALL libd_wcstombs_s)(size_t *presult,
                                      char *buf,
                                      size_t buflen,
                                      char16_t const *src,
                                      size_t maxlen) {
	if (!presult || !buf || !src) {
#ifdef EINVAL
		return EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	if (buflen > maxlen)
		buflen = maxlen;
	*presult = libd_wcstombs(buf, src, buflen);
	/* TODO: if (__buflen < *presult) return ERANGE; */
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((1, 2, 4)) errno_t
NOTHROW_NCX(LIBKCALL libc_wcstombs_s)(size_t *presult,
                                      char *buf,
                                      size_t buflen,
                                      char32_t const *src,
                                      size_t maxlen) {
	if (!presult || !buf || !src) {
#ifdef EINVAL
		return EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	if (buflen > maxlen)
		buflen = maxlen;
	*presult = libc_wcstombs(buf, src, buflen);
	/* TODO: if (__buflen < *presult) return ERANGE; */
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") ATTR_MALLOC WUNUSED ATTR_ALLOC_ALIGN(2) ATTR_ALLOC_SIZE((1)) void *
NOTHROW_NCX(LIBCCALL libc__aligned_malloc)(size_t num_bytes,
                                           size_t min_alignment) {
	void *result = libc_malloc(num_bytes + 2 * sizeof(void *) + min_alignment - 1);
	if (result) {
		void *base = (void *)(((uintptr_t)result + (min_alignment - 1)) & ~(min_alignment - 1));
		((void **)base)[-1] = result;
		((void **)base)[-2] = (void *)num_bytes;
		result = base;
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) void *
NOTHROW_NCX(LIBCCALL libc__aligned_offset_malloc)(size_t num_bytes,
                                                  size_t min_alignment,
                                                  size_t offset) {
	void *result;
	offset &= (min_alignment - 1);
	result = libc_malloc(num_bytes + 2 * sizeof(void *) + min_alignment - 1 + (min_alignment - offset));
	if (result) {
		void *base = (void *)((((uintptr_t)result + (min_alignment - 1)) & ~(min_alignment - 1)) + offset);
		((void **)base)[-1] = result;
		((void **)base)[-2] = (void *)num_bytes;
		result = base;
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") WUNUSED ATTR_ALLOC_ALIGN(3) ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBCCALL libc__aligned_realloc)(void *aligned_mallptr,
                                            size_t newsize,
                                            size_t min_alignment) {
	void *result;
	result = libc__aligned_malloc(newsize, min_alignment);
	if (result && aligned_mallptr) {
		size_t temp = libc__aligned_msize(aligned_mallptr, min_alignment, 0);
		if (temp > newsize)
			temp = newsize;
		libc_memcpy(result, aligned_mallptr, temp);
		libc__aligned_free(aligned_mallptr);
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") WUNUSED ATTR_ALLOC_ALIGN(4) ATTR_ALLOC_SIZE((2, 3)) void *
NOTHROW_NCX(LIBCCALL libc__aligned_recalloc)(void *aligned_mallptr,
                                             size_t count,
                                             size_t num_bytes,
                                             size_t min_alignment) {
	void *result;
	num_bytes *= count;
	result = libc__aligned_malloc(num_bytes, min_alignment);
	if (result) {
		size_t temp = libc__aligned_msize(aligned_mallptr, min_alignment, 0);
		if (temp > num_bytes)
			temp = num_bytes;
		libc_memcpy(result, aligned_mallptr, temp);
		libc_memset((byte_t *)result + temp, 0, num_bytes - temp);
		libc__aligned_free(aligned_mallptr);
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") WUNUSED ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBCCALL libc__aligned_offset_realloc)(void *aligned_mallptr,
                                                   size_t newsize,
                                                   size_t min_alignment,
                                                   size_t offset) {
	void *result;
	result = libc__aligned_offset_malloc(newsize, min_alignment, offset);
	if (result) {
		size_t temp = libc__aligned_msize(aligned_mallptr, min_alignment, offset);
		if (temp > newsize)
			temp = newsize;
		libc_memcpy(result, aligned_mallptr, temp);
		libc__aligned_free(aligned_mallptr);
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *
NOTHROW_NCX(LIBCCALL libc__aligned_offset_recalloc)(void *aligned_mallptr,
                                                    size_t count,
                                                    size_t num_bytes,
                                                    size_t min_alignment,
                                                    size_t offset) {
	void *result;
	num_bytes *= count;
	result = libc__aligned_offset_malloc(num_bytes, min_alignment, offset);
	if (result) {
		size_t temp = libc__aligned_msize(aligned_mallptr, min_alignment, offset);
		if (temp > num_bytes)
			temp = num_bytes;
		libc_memcpy(result, aligned_mallptr, temp);
		libc_memset((byte_t *)result + temp, 0, num_bytes - temp);
		libc__aligned_free(aligned_mallptr);
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") ATTR_PURE WUNUSED size_t
NOTHROW_NCX(LIBCCALL libc__aligned_msize)(void *aligned_mallptr,
                                          size_t min_alignment,
                                          size_t offset) {
	(void)min_alignment;
	(void)offset;
	if (!aligned_mallptr)
		return 0;
	return (size_t)(uintptr_t)((void **)aligned_mallptr)[-2];
}
INTERN ATTR_SECTION(".text.crt.dos.heap") void
NOTHROW_NCX(LIBCCALL libc__aligned_free)(void *aligned_mallptr) {
	if (aligned_mallptr)
		libc_free(((void **)aligned_mallptr)[-1]);
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1, 5, 6)) errno_t
NOTHROW_NCX(LIBCCALL libc__ecvt_s)(char *buf,
                                   size_t buflen,
                                   double val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign) {
	if (!buf || !decptr || !sign)
		return __EINVAL;
	libc_ecvt_r(val, ndigit, decptr, sign, buf, buflen);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1, 5, 6)) errno_t
NOTHROW_NCX(LIBCCALL libc__fcvt_s)(char *buf,
                                   size_t buflen,
                                   double val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign) {
	if (!buf || !decptr || !sign)
		return __EINVAL;
	libc_fcvt_r(val, ndigit, decptr, sign, buf, buflen);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__gcvt_s)(char *buf,
                                   size_t buflen,
                                   double val,
                                   int ndigit) {
	int a, b;
	if (!buf)
		return __EINVAL;
	libc_ecvt_r(val, ndigit, &a, &b, buf, buflen);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__atoflt)(float *__restrict result,
                                   char const *__restrict nptr) {
	*result = libc_strtof(nptr, NULL);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__atoflt_l)(float *__restrict result,
                                     char const *__restrict nptr,
                                     locale_t locale) {
	*result = libc_strtof_l(nptr, NULL, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__atodbl)(double *__restrict result,
                                   char __KOS_FIXED_CONST *__restrict nptr) {
	*result = libc_strtod(nptr, NULL);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__atodbl_l)(double *__restrict result,
                                     char __KOS_FIXED_CONST *__restrict nptr,
                                     locale_t locale) {
	*result = libc_strtod_l(nptr, NULL, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__atoldbl)(__LONGDOUBLE *__restrict result,
                                    char __KOS_FIXED_CONST *__restrict nptr) {
	*result = libc_strtold(nptr, NULL);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__atoldbl_l)(__LONGDOUBLE *__restrict result,
                                      char __KOS_FIXED_CONST *__restrict nptr,
                                      locale_t locale) {
	*result = libc_strtold_l(nptr, NULL, locale);
	return 0;
}
#include <hybrid/__rotate.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST unsigned int
NOTHROW(LIBCCALL libc__rotl)(unsigned int val,
                             int shift) {
	return __hybrid_rol(val, (shift_t)(unsigned int)shift);
}
#include <hybrid/__rotate.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST unsigned int
NOTHROW(LIBCCALL libc__rotr)(unsigned int val,
                             int shift) {
	return __hybrid_ror(val, (shift_t)(unsigned int)shift);
}
#include <hybrid/__rotate.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST u64
NOTHROW(LIBCCALL libc__rotl64)(u64 val,
                               int shift) {
	return __hybrid_rol64(val, (shift_t)(unsigned int)shift);
}
#include <hybrid/__rotate.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST u64
NOTHROW(LIBCCALL libc__rotr64)(u64 val,
                               int shift) {
	return __hybrid_ror64(val, (shift_t)(unsigned int)shift);
}
#include <hybrid/__rotate.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST unsigned long
NOTHROW(LIBCCALL libc__lrotl)(unsigned long val,
                              int shift) {
	return __hybrid_rol(val, (shift_t)(unsigned int)shift);
}
#include <hybrid/__rotate.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST unsigned long
NOTHROW(LIBCCALL libc__lrotr)(unsigned long val,
                              int shift) {
	return __hybrid_ror(val, (shift_t)(unsigned int)shift);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.environ") errno_t
NOTHROW_NCX(LIBCCALL libc__putenv_s)(char const *varname,
                                     char const *val) {
	return libc_setenv(varname, val, 1) ? __libc_geterrno_or(__EINVAL) : 0;
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1, 2, 3)) void
NOTHROW_RPC(LIBCCALL libc__searchenv)(char const *file,
                                      char const *envvar,
                                      char *__restrict resultpath) {
	libc__searchenv_s(file, envvar, resultpath, (size_t)-1);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc__makepath)(char *__restrict buf,
                                     char const *drive,
                                     char const *dir,
                                     char const *file,
                                     char const *ext) {
	libc__makepath_s(buf, (size_t)-1, drive, dir, file, ext);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc__splitpath)(char const *__restrict abspath,
                                      char *drive,
                                      char *dir,
                                      char *file,
                                      char *ext) {
	libc__splitpath_s(abspath,
	             drive, drive ? 3 : 0,
	             dir, dir ? 256 : 0,
	             file, file ? 256 : 0,
	             ext, ext ? 256 : 0);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__makepath_s)(char *buf,
                                       size_t buflen,
                                       char const *drive,
                                       char const *dir,
                                       char const *file,
                                       char const *ext) {
#define path_putn(p, n)                                  \
	do {                                                 \
		if unlikely(buflen < n)                          \
			goto err_buflen;                             \
		buf = (char *)libc_mempcpyc(buf, p, n, sizeof(char)); \
	} __WHILE0
#define path_putc(ch)          \
	do {                       \
		if unlikely(!buflen--) \
			goto err_buflen;   \
		*buf++ = (ch);         \
	} __WHILE0
	if (drive && *drive) {
		path_putc(*drive);
		path_putc(':');
	}
	if (dir && *dir) {
		size_t len = libc_strlen(dir);
		path_putn(dir, len);
		if (dir[len - 1] != '/' && dir[len - 1] != '\\')
			path_putc('\\');
	}
	if (file && *file) {
		size_t len = libc_strlen(file);
		path_putn(file, len);
	}
	if (ext && *ext) {
		size_t len = libc_strlen(ext);
		if (*ext != '.')
			path_putc('.');
		path_putn(ext, len);
	}
	path_putc('\0');
	return 0;
err_buflen:
#ifdef EINVAL
	return EINVAL;
#else /* EINVAL */
	return 1;
#endif /* !EINVAL */
#undef path_putn
#undef path_putc
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__splitpath_s)(char const *__restrict abspath,
                                        char *drive,
                                        size_t drivelen,
                                        char *dir,
                                        size_t dirlen,
                                        char *file,
                                        size_t filelen,
                                        char *ext,
                                        size_t extlen) {
	size_t len, last_slash, last_dot;
	if unlikely(!abspath)
		goto err_inval;
	if unlikely((drive != NULL) != (drivelen != 0))
		goto err_inval;
	if unlikely((dir != NULL) != (dirlen != 0))
		goto err_inval;
	if unlikely((file != NULL) != (filelen != 0))
		goto err_inval;
	if unlikely((ext != NULL) != (extlen != 0))
		goto err_inval;
	for (len = 0; len < 3; ++len) {
		if (abspath[len] == ':') {
			if (drive) {
				if unlikely(drivelen <= len)
					goto err_range;
				libc_memcpyc(drive, abspath, len, sizeof(char));
				drive[len] = 0;
			}
			abspath += len + 1;
			goto got_drive;
		}
	}
	if (drive)
		*drive = 0;
got_drive:
	last_slash = 0;
	last_dot = (size_t)-1;
	for (len = 0;; ++len) {
		char ch = abspath[len];
		if (!ch)
			break;
		if (ch == '/' || ch == '\\')
			last_slash = len + 1;
		if (ch == '.')
			last_dot = len;
	}
	if (last_slash) {
		if (dir) {
			if unlikely(dirlen <= last_slash)
				goto err_range;
			libc_memcpyc(dir, abspath, last_slash, sizeof(char));
			dir[last_slash] = 0;
		}
	} else {
		if (dir)
			*dir = 0;
	}
	if (last_dot != (size_t)-1 && last_dot > last_slash) {
		if (ext) {
			size_t path_extlen = len - last_dot;
			if unlikely(extlen <= path_extlen)
				goto err_range;
			libc_memcpyc(ext, abspath + last_dot, path_extlen, sizeof(char));
			ext[path_extlen] = 0;
		}
	} else {
		if (ext)
			*ext = 0;
		last_dot = len;
	}
	if (file) {
		len = last_dot - last_slash;
		if unlikely(filelen <= len)
			goto err_range;
		libc_memcpyc(file, abspath + last_slash, len, sizeof(char));
		file[len] = 0;
	}
	return 0;
err_inval:
#ifdef EINVAL
	return EINVAL;
#else /* EINVAL */
	return 1;
#endif /* !EINVAL */
err_range:
#ifdef ERANGE
	(void)__libc_seterrno(ERANGE);
	return ERANGE;
#else /* ERANGE */
	return 1;
#endif /* !ERANGE */
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((2)) char *
NOTHROW_NCX(LIBCCALL libc_itoa)(int val,
                                char *buf,
                                int radix) {
	libc__itoa_s(val, buf, (size_t)-1, radix);
	return buf;
}
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc_ltoa, libc_itoa);
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((2)) char *
NOTHROW_NCX(LIBCCALL libc_ltoa)(long val,
                                char *buf,
                                int radix) {
	libc__ltoa_s(val, buf, (size_t)-1, radix);
	return buf;
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") NONNULL((2)) char *
NOTHROW_NCX(LIBCCALL libc_ultoa)(unsigned long val,
                                 char *buf,
                                 int radix) {
	libc__ultoa_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) double
NOTHROW_NCX(LIBDCALL libd__wtof)(char16_t const *nptr) {
	return libd_wcstod(nptr, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) double
NOTHROW_NCX(LIBKCALL libc__wtof)(char32_t const *nptr) {
	return libc_wcstod(nptr, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) double
NOTHROW_NCX(LIBDCALL libd__wtof_l)(char16_t const *nptr,
                                   locale_t locale) {
	return libd_wcstod_l(nptr, NULL, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) double
NOTHROW_NCX(LIBKCALL libc__wtof_l)(char32_t const *nptr,
                                   locale_t locale) {
	return libc_wcstod_l(nptr, NULL, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) char16_t *
NOTHROW_NCX(LIBDCALL libd__itow)(int val,
                                 char16_t *buf,
                                 int radix) {
	libd__itow_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) char32_t *
NOTHROW_NCX(LIBKCALL libc__itow)(int val,
                                 char32_t *buf,
                                 int radix) {
	libc__itow_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) char16_t *
NOTHROW_NCX(LIBDCALL libd__ltow)(long val,
                                 char16_t *buf,
                                 int radix) {
	libd__ltow_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) char32_t *
NOTHROW_NCX(LIBKCALL libc__ltow)(long val,
                                 char32_t *buf,
                                 int radix) {
	libc__ltow_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) char16_t *
NOTHROW_NCX(LIBDCALL libd__ultow)(unsigned long val,
                                  char16_t *buf,
                                  int radix) {
	libd__ultow_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) char32_t *
NOTHROW_NCX(LIBKCALL libc__ultow)(unsigned long val,
                                  char32_t *buf,
                                  int radix) {
	libc__ultow_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) char16_t *
NOTHROW_NCX(LIBDCALL libd__i64tow)(s64 val,
                                   char16_t *buf,
                                   int radix) {
	libd__i64tow_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) char32_t *
NOTHROW_NCX(LIBKCALL libc__i64tow)(s64 val,
                                   char32_t *buf,
                                   int radix) {
	libc__i64tow_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) char16_t *
NOTHROW_NCX(LIBDCALL libd__ui64tow)(u64 val,
                                    char16_t *buf,
                                    int radix) {
	libd__ui64tow_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) char32_t *
NOTHROW_NCX(LIBKCALL libc__ui64tow)(u64 val,
                                    char32_t *buf,
                                    int radix) {
	libc__ui64tow_s(val, buf, (size_t)-1, radix);
	return buf;
}
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBDCALL libd__itow_s)(int val,
                                   char16_t *buf,
                                   size_t buflen,
                                   int radix) {
	char16_t *p;
	int temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
#ifdef ERANGE
			return ERANGE;
#else /* ERANGE */
			return 1;
#endif /* !ERANGE */
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do {
		++p;
	} while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned int)radix];
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBKCALL libc__itow_s)(int val,
                                   char32_t *buf,
                                   size_t buflen,
                                   int radix) {
	char32_t *p;
	int temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
#ifdef ERANGE
			return ERANGE;
#else /* ERANGE */
			return 1;
#endif /* !ERANGE */
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do {
		++p;
	} while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned int)radix];
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBDCALL libd__ltow_s)(long val,
                                   char16_t *buf,
                                   size_t buflen,
                                   int radix) {
	char16_t *p;
	long temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
#ifdef ERANGE
			return ERANGE;
#else /* ERANGE */
			return 1;
#endif /* !ERANGE */
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do {
		++p;
	} while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned int)radix];
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBKCALL libc__ltow_s)(long val,
                                   char32_t *buf,
                                   size_t buflen,
                                   int radix) {
	char32_t *p;
	long temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
#ifdef ERANGE
			return ERANGE;
#else /* ERANGE */
			return 1;
#endif /* !ERANGE */
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do {
		++p;
	} while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned int)radix];
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBDCALL libd__ultow_s)(unsigned long val,
                                    char16_t *buf,
                                    size_t buflen,
                                    int radix) {
	char16_t *p;
	unsigned long temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;
	temp = val;
	do {
		++p;
	} while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned int)radix];
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBKCALL libc__ultow_s)(unsigned long val,
                                    char32_t *buf,
                                    size_t buflen,
                                    int radix) {
	char32_t *p;
	unsigned long temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;
	temp = val;
	do {
		++p;
	} while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned int)radix];
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBDCALL libd__i64tow_s)(s64 val,
                                     char16_t *buf,
                                     size_t buflen,
                                     int radix) {
	char16_t *p;
	s64 temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
#ifdef ERANGE
			return ERANGE;
#else /* ERANGE */
			return 1;
#endif /* !ERANGE */
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do {
		++p;
	} while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned int)radix];
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBKCALL libc__i64tow_s)(s64 val,
                                     char32_t *buf,
                                     size_t buflen,
                                     int radix) {
	char32_t *p;
	s64 temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;
	if (val < 0) {
		if (!buflen--) {
#ifdef ERANGE
			return ERANGE;
#else /* ERANGE */
			return 1;
#endif /* !ERANGE */
		}
		*p++ = '-';
		val = -val;
	}
	temp = val;
	do {
		++p;
	} while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned int)radix];
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBDCALL libd__ui64tow_s)(u64 val,
                                      char16_t *buf,
                                      size_t buflen,
                                      int radix) {
	char16_t *p;
	u64 temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;
	temp = val;
	do {
		++p;
	} while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned int)radix];
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBKCALL libc__ui64tow_s)(u64 val,
                                      char32_t *buf,
                                      size_t buflen,
                                      int radix) {
	char32_t *p;
	u64 temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;
	temp = val;
	do {
		++p;
	} while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	temp = val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned int)radix];
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) s64
NOTHROW_NCX(LIBDCALL libd__wtoi64)(char16_t const *__restrict nptr) {
	return libd_wcsto64(nptr, NULL, 10);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) s64
NOTHROW_NCX(LIBKCALL libc__wtoi64)(char32_t const *__restrict nptr) {
	return libc_wcsto64(nptr, NULL, 10);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd__wtoi_l)(char16_t const *__restrict nptr,
                                   locale_t locale) {
	return (int)libd_wcstol_l(nptr, NULL, 10, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBKCALL libc__wtoi_l)(char32_t const *__restrict nptr,
                                   locale_t locale) {
	return (int)libc_wcstol_l(nptr, NULL, 10, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) long int
NOTHROW_NCX(LIBDCALL libd__wtol_l)(char16_t const *__restrict nptr,
                                   locale_t locale) {
	return libd_wcstol_l(nptr, NULL, 10, locale);
}
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc__wtol_l, libc__wtoi_l);
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) long int
NOTHROW_NCX(LIBKCALL libc__wtol_l)(char32_t const *__restrict nptr,
                                   locale_t locale) {
	return libc_wcstol_l(nptr, NULL, 10, locale);
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) s64
NOTHROW_NCX(LIBDCALL libd__wtoi64_l)(char16_t const *__restrict nptr,
                                     locale_t locale) {
	return libd_wcsto64_l(nptr, NULL, 10, locale);
}
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS(libc__wtoi64_l, libc__wtoi_l);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__wtoi64_l, libc__wtol_l);
#elif __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libc__wtoi64_l, libc__wtoll_l);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) s64
NOTHROW_NCX(LIBKCALL libc__wtoi64_l)(char32_t const *__restrict nptr,
                                     locale_t locale) {
	return libc_wcsto64_l(nptr, NULL, 10, locale);
}
#endif /* !... */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBDCALL libd__wtoll_l)(char16_t const *__restrict nptr,
                                    locale_t locale) {
	return libd_wcstoll_l(nptr, NULL, 10, locale);
}
#if __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS(libc__wtoll_l, libc__wtoi_l);
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS(libc__wtoll_l, libc__wtol_l);
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBKCALL libc__wtoll_l)(char32_t const *__restrict nptr,
                                    locale_t locale) {
	return libc_wcstoll_l(nptr, NULL, 10, locale);
}
#endif /* !... */
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") NONNULL((1)) errno_t
NOTHROW_NCX(LIBDCALL libd__wmakepath_s)(char16_t *buf,
                                        size_t buflen,
                                        char16_t const *drive,
                                        char16_t const *dir,
                                        char16_t const *file,
                                        char16_t const *ext) {
#define path_putn(p, n)                                  \
	do {                                                 \
		if unlikely(buflen < n)                          \
			goto err_buflen;                             \
		buf = (char16_t *)libc_mempcpyc(buf, p, n, sizeof(char16_t)); \
	} __WHILE0
#define path_putc(ch)          \
	do {                       \
		if unlikely(!buflen--) \
			goto err_buflen;   \
		*buf++ = (ch);         \
	} __WHILE0
	if (drive && *drive) {
		path_putc(*drive);
		path_putc(':');
	}
	if (dir && *dir) {
		size_t len = libd_wcslen(dir);
		path_putn(dir, len);
		if (dir[len - 1] != '/' && dir[len - 1] != '\\')
			path_putc('\\');
	}
	if (file && *file) {
		size_t len = libd_wcslen(file);
		path_putn(file, len);
	}
	if (ext && *ext) {
		size_t len = libd_wcslen(ext);
		if (*ext != '.')
			path_putc('.');
		path_putn(ext, len);
	}
	path_putc('\0');
	return 0;
err_buflen:
#ifdef EINVAL
	return EINVAL;
#else /* EINVAL */
	return 1;
#endif /* !EINVAL */
#undef path_putn
#undef path_putc
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") NONNULL((1)) errno_t
NOTHROW_NCX(LIBKCALL libc__wmakepath_s)(char32_t *buf,
                                        size_t buflen,
                                        char32_t const *drive,
                                        char32_t const *dir,
                                        char32_t const *file,
                                        char32_t const *ext) {
#define path_putn(p, n)                                  \
	do {                                                 \
		if unlikely(buflen < n)                          \
			goto err_buflen;                             \
		buf = (char32_t *)libc_mempcpyc(buf, p, n, sizeof(char32_t)); \
	} __WHILE0
#define path_putc(ch)          \
	do {                       \
		if unlikely(!buflen--) \
			goto err_buflen;   \
		*buf++ = (ch);         \
	} __WHILE0
	if (drive && *drive) {
		path_putc(*drive);
		path_putc(':');
	}
	if (dir && *dir) {
		size_t len = libc_wcslen(dir);
		path_putn(dir, len);
		if (dir[len - 1] != '/' && dir[len - 1] != '\\')
			path_putc('\\');
	}
	if (file && *file) {
		size_t len = libc_wcslen(file);
		path_putn(file, len);
	}
	if (ext && *ext) {
		size_t len = libc_wcslen(ext);
		if (*ext != '.')
			path_putc('.');
		path_putn(ext, len);
	}
	path_putc('\0');
	return 0;
err_buflen:
#ifdef EINVAL
	return EINVAL;
#else /* EINVAL */
	return 1;
#endif /* !EINVAL */
#undef path_putn
#undef path_putc
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd__wmakepath)(char16_t *__restrict buf,
                                      char16_t const *drive,
                                      char16_t const *dir,
                                      char16_t const *file,
                                      char16_t const *ext) {
	libd__wmakepath_s(buf, (size_t)-1, drive, dir, file, ext);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") NONNULL((1)) void
NOTHROW_NCX(LIBKCALL libc__wmakepath)(char32_t *__restrict buf,
                                      char32_t const *drive,
                                      char32_t const *dir,
                                      char32_t const *file,
                                      char32_t const *ext) {
	libc__wmakepath_s(buf, (size_t)-1, drive, dir, file, ext);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") NONNULL((1, 2, 3)) void
NOTHROW_RPC(LIBDCALL libd__wsearchenv)(char16_t const *file,
                                       char16_t const *envvar,
                                       char16_t *__restrict resultpath) {
	libd__wsearchenv_s(file, envvar, resultpath, (size_t)-1);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") NONNULL((1, 2, 3)) void
NOTHROW_RPC(LIBKCALL libc__wsearchenv)(char32_t const *file,
                                       char32_t const *envvar,
                                       char32_t *__restrict resultpath) {
	libc__wsearchenv_s(file, envvar, resultpath, (size_t)-1);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd__wsplitpath)(char16_t const *__restrict abspath,
                                       char16_t *drive,
                                       char16_t *dir,
                                       char16_t *file,
                                       char16_t *ext) {
	libd__wsplitpath_s(abspath,
	             drive, drive ? 3 : 0,
	             dir, dir ? 256 : 0,
	             file, file ? 256 : 0,
	             ext, ext ? 256 : 0);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") NONNULL((1)) void
NOTHROW_NCX(LIBKCALL libc__wsplitpath)(char32_t const *__restrict abspath,
                                       char32_t *drive,
                                       char32_t *dir,
                                       char32_t *file,
                                       char32_t *ext) {
	libc__wsplitpath_s(abspath,
	             drive, drive ? 3 : 0,
	             dir, dir ? 256 : 0,
	             file, file ? 256 : 0,
	             ext, ext ? 256 : 0);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") NONNULL((1)) errno_t
NOTHROW_NCX(LIBDCALL libd__wsplitpath_s)(char16_t const *__restrict abspath,
                                         char16_t *drive,
                                         size_t drivelen,
                                         char16_t *dir,
                                         size_t dirlen,
                                         char16_t *file,
                                         size_t filelen,
                                         char16_t *ext,
                                         size_t extlen) {
	size_t len, last_slash, last_dot;
	if unlikely(!abspath)
		goto err_inval;
	if unlikely((drive != NULL) != (drivelen != 0))
		goto err_inval;
	if unlikely((dir != NULL) != (dirlen != 0))
		goto err_inval;
	if unlikely((file != NULL) != (filelen != 0))
		goto err_inval;
	if unlikely((ext != NULL) != (extlen != 0))
		goto err_inval;
	for (len = 0; len < 3; ++len) {
		if (abspath[len] == ':') {
			if (drive) {
				if unlikely(drivelen <= len)
					goto err_range;
				libc_memcpyc(drive, abspath, len, sizeof(char16_t));
				drive[len] = 0;
			}
			abspath += len + 1;
			goto got_drive;
		}
	}
	if (drive)
		*drive = 0;
got_drive:
	last_slash = 0;
	last_dot = (size_t)-1;
	for (len = 0;; ++len) {
		char16_t ch = abspath[len];
		if (!ch)
			break;
		if (ch == '/' || ch == '\\')
			last_slash = len + 1;
		if (ch == '.')
			last_dot = len;
	}
	if (last_slash) {
		if (dir) {
			if unlikely(dirlen <= last_slash)
				goto err_range;
			libc_memcpyc(dir, abspath, last_slash, sizeof(char16_t));
			dir[last_slash] = 0;
		}
	} else {
		if (dir)
			*dir = 0;
	}
	if (last_dot != (size_t)-1 && last_dot > last_slash) {
		if (ext) {
			size_t path_extlen = len - last_dot;
			if unlikely(extlen <= path_extlen)
				goto err_range;
			libc_memcpyc(ext, abspath + last_dot, path_extlen, sizeof(char16_t));
			ext[path_extlen] = 0;
		}
	} else {
		if (ext)
			*ext = 0;
		last_dot = len;
	}
	if (file) {
		len = last_dot - last_slash;
		if unlikely(filelen <= len)
			goto err_range;
		libc_memcpyc(file, abspath + last_slash, len, sizeof(char16_t));
		file[len] = 0;
	}
	return 0;
err_inval:
#ifdef EINVAL
	return EINVAL;
#else /* EINVAL */
	return 1;
#endif /* !EINVAL */
err_range:
#ifdef ERANGE
	(void)__libc_seterrno(ERANGE);
	return ERANGE;
#else /* ERANGE */
	return 1;
#endif /* !ERANGE */
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") NONNULL((1)) errno_t
NOTHROW_NCX(LIBKCALL libc__wsplitpath_s)(char32_t const *__restrict abspath,
                                         char32_t *drive,
                                         size_t drivelen,
                                         char32_t *dir,
                                         size_t dirlen,
                                         char32_t *file,
                                         size_t filelen,
                                         char32_t *ext,
                                         size_t extlen) {
	size_t len, last_slash, last_dot;
	if unlikely(!abspath)
		goto err_inval;
	if unlikely((drive != NULL) != (drivelen != 0))
		goto err_inval;
	if unlikely((dir != NULL) != (dirlen != 0))
		goto err_inval;
	if unlikely((file != NULL) != (filelen != 0))
		goto err_inval;
	if unlikely((ext != NULL) != (extlen != 0))
		goto err_inval;
	for (len = 0; len < 3; ++len) {
		if (abspath[len] == ':') {
			if (drive) {
				if unlikely(drivelen <= len)
					goto err_range;
				libc_memcpyc(drive, abspath, len, sizeof(char32_t));
				drive[len] = 0;
			}
			abspath += len + 1;
			goto got_drive;
		}
	}
	if (drive)
		*drive = 0;
got_drive:
	last_slash = 0;
	last_dot = (size_t)-1;
	for (len = 0;; ++len) {
		char32_t ch = abspath[len];
		if (!ch)
			break;
		if (ch == '/' || ch == '\\')
			last_slash = len + 1;
		if (ch == '.')
			last_dot = len;
	}
	if (last_slash) {
		if (dir) {
			if unlikely(dirlen <= last_slash)
				goto err_range;
			libc_memcpyc(dir, abspath, last_slash, sizeof(char32_t));
			dir[last_slash] = 0;
		}
	} else {
		if (dir)
			*dir = 0;
	}
	if (last_dot != (size_t)-1 && last_dot > last_slash) {
		if (ext) {
			size_t path_extlen = len - last_dot;
			if unlikely(extlen <= path_extlen)
				goto err_range;
			libc_memcpyc(ext, abspath + last_dot, path_extlen, sizeof(char32_t));
			ext[path_extlen] = 0;
		}
	} else {
		if (ext)
			*ext = 0;
		last_dot = len;
	}
	if (file) {
		len = last_dot - last_slash;
		if unlikely(filelen <= len)
			goto err_range;
		libc_memcpyc(file, abspath + last_slash, len, sizeof(char32_t));
		file[len] = 0;
	}
	return 0;
err_inval:
#ifdef EINVAL
	return EINVAL;
#else /* EINVAL */
	return 1;
#endif /* !EINVAL */
err_range:
#ifdef ERANGE
	(void)__libc_seterrno(ERANGE);
	return ERANGE;
#else /* ERANGE */
	return 1;
#endif /* !ERANGE */
}
#endif /* !__KERNEL__ */

DECL_END

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$bsearch_r, libd_bsearch_r);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(bsearch_r, libc_bsearch_r);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$qsort, libd_qsort);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(qsort, libc_qsort);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$bsearch, libd_bsearch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(bsearch, libc_bsearch);
DEFINE_PUBLIC_ALIAS(labs, libc_labs);
DEFINE_PUBLIC_ALIAS(llabs, libc_llabs);
DEFINE_PUBLIC_ALIAS(qabs, libc_llabs);
DEFINE_PUBLIC_ALIAS(ldiv, libc_ldiv);
DEFINE_PUBLIC_ALIAS(lldiv, libc_lldiv);
DEFINE_PUBLIC_ALIAS(qdiv, libc_lldiv);
DEFINE_PUBLIC_ALIAS(abs, libc_abs);
DEFINE_PUBLIC_ALIAS(div, libc_div);
DEFINE_PUBLIC_ALIAS(mblen, libc_mblen);
DEFINE_PUBLIC_ALIAS(DOS$mbtowc, libd_mbtowc);
DEFINE_PUBLIC_ALIAS(mbtowc, libc_mbtowc);
DEFINE_PUBLIC_ALIAS(DOS$wctomb, libd_wctomb);
DEFINE_PUBLIC_ALIAS(wctomb, libc_wctomb);
DEFINE_PUBLIC_ALIAS(DOS$mbstowcs, libd_mbstowcs);
DEFINE_PUBLIC_ALIAS(mbstowcs, libc_mbstowcs);
DEFINE_PUBLIC_ALIAS(DOS$wcstombs, libd_wcstombs);
DEFINE_PUBLIC_ALIAS(wcstombs, libc_wcstombs);
DEFINE_PUBLIC_ALIAS(system, libc_system);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_ABORT)
DEFINE_PUBLIC_ALIAS(_ZSt9terminatev, libc_abort);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS("?terminate@@YAXXZ", libc_abort);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(abort, libc_abort);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_ABORT */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(atoi, libc_atoi);
DEFINE_PUBLIC_ALIAS(atol, libc_atol);
DEFINE_PUBLIC_ALIAS(atoll, libc_atoll);
DEFINE_PUBLIC_ALIAS(strtoul, libc_strtoul);
DEFINE_PUBLIC_ALIAS(strtol, libc_strtol);
DEFINE_PUBLIC_ALIAS(strtoull, libc_strtoull);
DEFINE_PUBLIC_ALIAS(strtouq, libc_strtoull);
DEFINE_PUBLIC_ALIAS(__strtouq, libc_strtoull);
DEFINE_PUBLIC_ALIAS(strtoll, libc_strtoll);
DEFINE_PUBLIC_ALIAS(strtoq, libc_strtoll);
DEFINE_PUBLIC_ALIAS(__strtoq, libc_strtoll);
DEFINE_PUBLIC_ALIAS(atof, libc_atof);
DEFINE_PUBLIC_ALIAS(strtod, libc_strtod);
DEFINE_PUBLIC_ALIAS(__strtof, libc_strtof);
DEFINE_PUBLIC_ALIAS(strtof, libc_strtof);
DEFINE_PUBLIC_ALIAS(__strtold, libc_strtold);
DEFINE_PUBLIC_ALIAS(strtold, libc_strtold);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(strtou32_r, libc_strtou32_r);
DEFINE_PUBLIC_ALIAS(strto32_r, libc_strto32_r);
DEFINE_PUBLIC_ALIAS(strtou64_r, libc_strtou64_r);
DEFINE_PUBLIC_ALIAS(strto64_r, libc_strto64_r);
DEFINE_PUBLIC_ALIAS(strtou32, libc_strtou32);
DEFINE_PUBLIC_ALIAS(strto32, libc_strto32);
#if defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(_strtoui64, libc_strtou64);
#endif /* __LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(strtou64, libc_strtou64);
#if defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(_strtoi64, libc_strto64);
#endif /* __LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(strto64, libc_strto64);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(strtou32_l, libc_strtou32_l);
DEFINE_PUBLIC_ALIAS(strto32_l, libc_strto32_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strtoui64_l, libc_strtou64_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(strtou64_l, libc_strtou64_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strtoi64_l, libc_strto64_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(strto64_l, libc_strto64_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_gcvt, libc_gcvt);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(gcvt, libc_gcvt);
DEFINE_PUBLIC_ALIAS(ecvt_r, libc_ecvt_r);
DEFINE_PUBLIC_ALIAS(fcvt_r, libc_fcvt_r);
DEFINE_PUBLIC_ALIAS(qgcvt, libc_qgcvt);
DEFINE_PUBLIC_ALIAS(qecvt_r, libc_qecvt_r);
DEFINE_PUBLIC_ALIAS(qfcvt_r, libc_qfcvt_r);
DEFINE_PUBLIC_ALIAS(qecvt, libc_qecvt);
DEFINE_PUBLIC_ALIAS(qfcvt, libc_qfcvt);
DEFINE_PUBLIC_ALIAS(mkstemps, libc_mkstemps);
DEFINE_PUBLIC_ALIAS(rpmatch, libc_rpmatch);
DEFINE_PUBLIC_ALIAS(mkstemps64, libc_mkstemps64);
DEFINE_PUBLIC_ALIAS(l64a, libc_l64a);
DEFINE_PUBLIC_ALIAS(a64l, libc_a64l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_mktemp, libc_mktemp);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__mktemp, libc_mktemp);
DEFINE_PUBLIC_ALIAS(mktemp, libc_mktemp);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_ecvt, libc_ecvt);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(ecvt, libc_ecvt);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_fcvt, libc_fcvt);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(fcvt, libc_fcvt);
DEFINE_PUBLIC_ALIAS(getsubopt, libc_getsubopt);
DEFINE_PUBLIC_ALIAS(mkstemp, libc_mkstemp);
DEFINE_PUBLIC_ALIAS(mkstemp64, libc_mkstemp64);
DEFINE_PUBLIC_ALIAS(mkdtemp, libc_mkdtemp);
DEFINE_PUBLIC_ALIAS(unlockpt, libc_unlockpt);
DEFINE_PUBLIC_ALIAS(ptsname, libc_ptsname);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strtol_l, libc_strtol_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__strtol_l, libc_strtol_l);
DEFINE_PUBLIC_ALIAS(strtol_l, libc_strtol_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strtoul_l, libc_strtoul_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__strtoul_l, libc_strtoul_l);
DEFINE_PUBLIC_ALIAS(strtoul_l, libc_strtoul_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strtoll_l, libc_strtoll_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__strtoll_l, libc_strtoll_l);
DEFINE_PUBLIC_ALIAS(strtoll_l, libc_strtoll_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strtoull_l, libc_strtoull_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__strtoull_l, libc_strtoull_l);
DEFINE_PUBLIC_ALIAS(strtoull_l, libc_strtoull_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strtod_l, libc_strtod_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__strtod_l, libc_strtod_l);
DEFINE_PUBLIC_ALIAS(strtod_l, libc_strtod_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strtof_l, libc_strtof_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__strtof_l, libc_strtof_l);
DEFINE_PUBLIC_ALIAS(strtof_l, libc_strtof_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strtold_l, libc_strtold_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__strtold_l, libc_strtold_l);
DEFINE_PUBLIC_ALIAS(strtold_l, libc_strtold_l);
DEFINE_PUBLIC_ALIAS(shexec, libc_shexec);
DEFINE_PUBLIC_ALIAS(getexecname, libc_getexecname);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$fdwalk, libd_fdwalk);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(fdwalk, libc_fdwalk);
DEFINE_PUBLIC_ALIAS(lltostr, libc_lltostr);
DEFINE_PUBLIC_ALIAS(ulltostr, libc_ulltostr);
DEFINE_PUBLIC_ALIAS(reallocf, libc_reallocf);
DEFINE_PUBLIC_ALIAS(l64a_r, libc_l64a_r);
DEFINE_PUBLIC_ALIAS(getprogname, libc_getprogname);
DEFINE_PUBLIC_ALIAS(setprogname, libc_setprogname);
DEFINE_PUBLIC_ALIAS(heapsort, libc_heapsort);
DEFINE_PUBLIC_ALIAS(mergesort, libc_mergesort);
DEFINE_PUBLIC_ALIAS(strtonum, libc_strtonum);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$qsort_r, libd_qsort_r);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(qsort_r, libc_qsort_r);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(mkostemp, libc_mkostemp);
DEFINE_PUBLIC_ALIAS(mkostemps, libc_mkostemps);
DEFINE_PUBLIC_ALIAS(mkostemp64, libc_mkostemp64);
DEFINE_PUBLIC_ALIAS(mkostemps64, libc_mkostemps64);
DEFINE_PUBLIC_ALIAS(devname, libc_devname);
DEFINE_PUBLIC_ALIAS(strsuftoll, libc_strsuftoll);
DEFINE_PUBLIC_ALIAS(strsuftollx, libc_strsuftollx);
DEFINE_PUBLIC_ALIAS(__p_program_invocation_name, libc___p__pgmptr);
DEFINE_PUBLIC_ALIAS(__p__pgmptr, libc___p__pgmptr);
DEFINE_PUBLIC_ALIAS(_get_pgmptr, libc__get_pgmptr);
DEFINE_PUBLIC_ALIAS(DOS$_get_wpgmptr, libd__get_wpgmptr);
DEFINE_PUBLIC_ALIAS(_get_wpgmptr, libc__get_wpgmptr);
DEFINE_PUBLIC_ALIAS(_abs64, libc__abs64);
DEFINE_PUBLIC_ALIAS(_atof_l, libc__atof_l);
DEFINE_PUBLIC_ALIAS(_atoi_l, libc__atoi_l);
DEFINE_PUBLIC_ALIAS(_atol_l, libc__atol_l);
DEFINE_PUBLIC_ALIAS(_atoll_l, libc__atoll_l);
DEFINE_PUBLIC_ALIAS(_byteswap_ushort, libc__byteswap_ushort);
DEFINE_PUBLIC_ALIAS(_byteswap_ulong, libc__byteswap_ulong);
DEFINE_PUBLIC_ALIAS(_byteswap_uint64, libc__byteswap_uint64);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$bsearch_s, libd_bsearch_s);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(bsearch_s, libc_bsearch_s);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$qsort_s, libd_qsort_s);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(qsort_s, libc_qsort_s);
DEFINE_PUBLIC_ALIAS(_itoa_s, libc__itoa_s);
DEFINE_PUBLIC_ALIAS(_ltoa_s, libc__ltoa_s);
DEFINE_PUBLIC_ALIAS(_ultoa_s, libc__ultoa_s);
DEFINE_PUBLIC_ALIAS(_i64toa, libc__i64toa);
DEFINE_PUBLIC_ALIAS(_ui64toa, libc__ui64toa);
DEFINE_PUBLIC_ALIAS(_i64toa_s, libc__i64toa_s);
DEFINE_PUBLIC_ALIAS(_ui64toa_s, libc__ui64toa_s);
DEFINE_PUBLIC_ALIAS(_atoi64, libc__atoi64);
DEFINE_PUBLIC_ALIAS(_atoi64_l, libc__atoi64_l);
DEFINE_PUBLIC_ALIAS(_mbstrlen, libc__mbstrlen);
DEFINE_PUBLIC_ALIAS(_mbstrnlen, libc__mbstrnlen);
DEFINE_PUBLIC_ALIAS(_mbstrlen_l, libc__mbstrlen_l);
DEFINE_PUBLIC_ALIAS(_mbstrnlen_l, libc__mbstrnlen_l);
DEFINE_PUBLIC_ALIAS(_mblen_l, libc__mblen_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbtowc_l, libd__mbtowc_l);
DEFINE_PUBLIC_ALIAS(_mbtowc_l, libc__mbtowc_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbstowcs_l, libd__mbstowcs_l);
DEFINE_PUBLIC_ALIAS(_mbstowcs_l, libc__mbstowcs_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbstowcs_s, libd__mbstowcs_s);
DEFINE_PUBLIC_ALIAS(_mbstowcs_s, libc__mbstowcs_s);
DEFINE_PUBLIC_ALIAS(DOS$mbstowcs_s, libd_mbstowcs_s);
DEFINE_PUBLIC_ALIAS(mbstowcs_s, libc_mbstowcs_s);
DEFINE_PUBLIC_ALIAS(DOS$_mbstowcs_s_l, libd__mbstowcs_s_l);
DEFINE_PUBLIC_ALIAS(_mbstowcs_s_l, libc__mbstowcs_s_l);
DEFINE_PUBLIC_ALIAS(rand_s, libc_rand_s);
DEFINE_PUBLIC_ALIAS(DOS$_wctomb_l, libd__wctomb_l);
DEFINE_PUBLIC_ALIAS(_wctomb_l, libc__wctomb_l);
DEFINE_PUBLIC_ALIAS(DOS$wctomb_s, libd_wctomb_s);
DEFINE_PUBLIC_ALIAS(wctomb_s, libc_wctomb_s);
DEFINE_PUBLIC_ALIAS(DOS$_wctomb_s_l, libd__wctomb_s_l);
DEFINE_PUBLIC_ALIAS(_wctomb_s_l, libc__wctomb_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcstombs_s_l, libd__wcstombs_s_l);
DEFINE_PUBLIC_ALIAS(_wcstombs_s_l, libc__wcstombs_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcstombs_l, libd__wcstombs_l);
DEFINE_PUBLIC_ALIAS(_wcstombs_l, libc__wcstombs_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstombs_s, libd_wcstombs_s);
DEFINE_PUBLIC_ALIAS(wcstombs_s, libc_wcstombs_s);
DEFINE_PUBLIC_ALIAS(_aligned_malloc, libc__aligned_malloc);
DEFINE_PUBLIC_ALIAS(_aligned_offset_malloc, libc__aligned_offset_malloc);
DEFINE_PUBLIC_ALIAS(_aligned_realloc, libc__aligned_realloc);
DEFINE_PUBLIC_ALIAS(_aligned_recalloc, libc__aligned_recalloc);
DEFINE_PUBLIC_ALIAS(_aligned_offset_realloc, libc__aligned_offset_realloc);
DEFINE_PUBLIC_ALIAS(_aligned_offset_recalloc, libc__aligned_offset_recalloc);
DEFINE_PUBLIC_ALIAS(_aligned_msize, libc__aligned_msize);
DEFINE_PUBLIC_ALIAS(_aligned_free, libc__aligned_free);
DEFINE_PUBLIC_ALIAS(_ecvt_s, libc__ecvt_s);
DEFINE_PUBLIC_ALIAS(_fcvt_s, libc__fcvt_s);
DEFINE_PUBLIC_ALIAS(_gcvt_s, libc__gcvt_s);
DEFINE_PUBLIC_ALIAS(_atoflt, libc__atoflt);
DEFINE_PUBLIC_ALIAS(_atoflt_l, libc__atoflt_l);
DEFINE_PUBLIC_ALIAS(_atodbl, libc__atodbl);
DEFINE_PUBLIC_ALIAS(_atodbl_l, libc__atodbl_l);
DEFINE_PUBLIC_ALIAS(_atoldbl, libc__atoldbl);
DEFINE_PUBLIC_ALIAS(_atoldbl_l, libc__atoldbl_l);
DEFINE_PUBLIC_ALIAS(_rotl, libc__rotl);
DEFINE_PUBLIC_ALIAS(_rotr, libc__rotr);
DEFINE_PUBLIC_ALIAS(_rotl64, libc__rotl64);
DEFINE_PUBLIC_ALIAS(_rotr64, libc__rotr64);
DEFINE_PUBLIC_ALIAS(_lrotl, libc__lrotl);
DEFINE_PUBLIC_ALIAS(_lrotr, libc__lrotr);
DEFINE_PUBLIC_ALIAS(_putenv_s, libc__putenv_s);
DEFINE_PUBLIC_ALIAS(_searchenv, libc__searchenv);
DEFINE_PUBLIC_ALIAS(_makepath, libc__makepath);
DEFINE_PUBLIC_ALIAS(_splitpath, libc__splitpath);
DEFINE_PUBLIC_ALIAS(_makepath_s, libc__makepath_s);
DEFINE_PUBLIC_ALIAS(_splitpath_s, libc__splitpath_s);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_itoa, libc_itoa);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(itoa, libc_itoa);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_ltoa, libc_ltoa);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(ltoa, libc_ltoa);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_ultoa, libc_ultoa);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(ultoa, libc_ultoa);
DEFINE_PUBLIC_ALIAS(DOS$_wtof, libd__wtof);
DEFINE_PUBLIC_ALIAS(_wtof, libc__wtof);
DEFINE_PUBLIC_ALIAS(DOS$_wtof_l, libd__wtof_l);
DEFINE_PUBLIC_ALIAS(_wtof_l, libc__wtof_l);
DEFINE_PUBLIC_ALIAS(DOS$_itow, libd__itow);
DEFINE_PUBLIC_ALIAS(_itow, libc__itow);
DEFINE_PUBLIC_ALIAS(DOS$_ltow, libd__ltow);
DEFINE_PUBLIC_ALIAS(_ltow, libc__ltow);
DEFINE_PUBLIC_ALIAS(DOS$_ultow, libd__ultow);
DEFINE_PUBLIC_ALIAS(_ultow, libc__ultow);
DEFINE_PUBLIC_ALIAS(DOS$_i64tow, libd__i64tow);
DEFINE_PUBLIC_ALIAS(_i64tow, libc__i64tow);
DEFINE_PUBLIC_ALIAS(DOS$_ui64tow, libd__ui64tow);
DEFINE_PUBLIC_ALIAS(_ui64tow, libc__ui64tow);
DEFINE_PUBLIC_ALIAS(DOS$_itow_s, libd__itow_s);
DEFINE_PUBLIC_ALIAS(_itow_s, libc__itow_s);
DEFINE_PUBLIC_ALIAS(DOS$_ltow_s, libd__ltow_s);
DEFINE_PUBLIC_ALIAS(_ltow_s, libc__ltow_s);
DEFINE_PUBLIC_ALIAS(DOS$_ultow_s, libd__ultow_s);
DEFINE_PUBLIC_ALIAS(_ultow_s, libc__ultow_s);
DEFINE_PUBLIC_ALIAS(DOS$_i64tow_s, libd__i64tow_s);
DEFINE_PUBLIC_ALIAS(_i64tow_s, libc__i64tow_s);
DEFINE_PUBLIC_ALIAS(DOS$_ui64tow_s, libd__ui64tow_s);
DEFINE_PUBLIC_ALIAS(_ui64tow_s, libc__ui64tow_s);
DEFINE_PUBLIC_ALIAS(DOS$_wtoi64, libd__wtoi64);
DEFINE_PUBLIC_ALIAS(_wtoi64, libc__wtoi64);
DEFINE_PUBLIC_ALIAS(DOS$_wtoi_l, libd__wtoi_l);
DEFINE_PUBLIC_ALIAS(_wtoi_l, libc__wtoi_l);
DEFINE_PUBLIC_ALIAS(DOS$_wtol_l, libd__wtol_l);
DEFINE_PUBLIC_ALIAS(_wtol_l, libc__wtol_l);
DEFINE_PUBLIC_ALIAS(DOS$_wtoi64_l, libd__wtoi64_l);
DEFINE_PUBLIC_ALIAS(_wtoi64_l, libc__wtoi64_l);
DEFINE_PUBLIC_ALIAS(DOS$_wtoll_l, libd__wtoll_l);
DEFINE_PUBLIC_ALIAS(_wtoll_l, libc__wtoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_wmakepath_s, libd__wmakepath_s);
DEFINE_PUBLIC_ALIAS(_wmakepath_s, libc__wmakepath_s);
DEFINE_PUBLIC_ALIAS(DOS$_wmakepath, libd__wmakepath);
DEFINE_PUBLIC_ALIAS(_wmakepath, libc__wmakepath);
DEFINE_PUBLIC_ALIAS(DOS$_wsearchenv, libd__wsearchenv);
DEFINE_PUBLIC_ALIAS(_wsearchenv, libc__wsearchenv);
DEFINE_PUBLIC_ALIAS(DOS$_wsplitpath, libd__wsplitpath);
DEFINE_PUBLIC_ALIAS(_wsplitpath, libc__wsplitpath);
DEFINE_PUBLIC_ALIAS(DOS$_wsplitpath_s, libd__wsplitpath_s);
DEFINE_PUBLIC_ALIAS(_wsplitpath_s, libc__wsplitpath_s);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_STDLIB_C */
