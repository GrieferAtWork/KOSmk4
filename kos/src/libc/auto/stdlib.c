/* HASH CRC-32:0xe70b6d58 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
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
#ifndef LIBC_ARCH_HAVE_ABORTF
#include "format-printer.h"
#include "string.h"
#include "../user/sys.syslog.h"
#include "../user/unistd.h"
#endif /* !LIBC_ARCH_HAVE_ABORTF */
#include "../user/ctype.h"
#include "../user/dirent.h"
#include "err.h"
#include "../user/fcntl.h"
#include "inttypes.h"
#include "../user/malloc.h"
#include "../user/pthread.h"
#include "../user/stdio.h"
#include "string.h"
#include "../user/sys.ioctl.h"
#include "../user/sys.prctl.h"
#include "../user/sys.stat.h"
#include "../user/sys.time.h"
#include "../user/sys.wait.h"
#include "../user/time.h"
#include "../user/unicode.h"
#include "../user/unistd.h"
#include "../user/wchar.h"

DECL_BEGIN

#include "../libc/globals.h"
#include <strings.h>
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifndef __dwrap_sTPTP_TDTPTPTP_c0A0A1c1_defined
#define __dwrap_sTPTP_TDTPTPTP_c0A0A1c1_defined
struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0A0A1c1 {
	int (LIBDCALL *compar)(void const *a, void const *b, void *arg);
	void *arg;
};
PRIVATE ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility.stdlib") int
(LIBCCALL _dwrap_sTPTP_TDTPTPTP_c0A0A1c1)(void const *a,
                                          void const *b,
                                          struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0A0A1c1 *c) THROWS(...) {
	return (*c->compar)(a, b, c->arg);
}
#endif /* !__dwrap_sTPTP_TDTPTPTP_c0A0A1c1_defined */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility.stdlib") WUNUSED ATTR_IN(1) ATTR_IN_OPT(2) NONNULL((5)) void *
NOTHROW_CB_NCX(LIBDCALL libd_bsearch_r)(void const *pkey,
                                        void const *pbase,
                                        size_t item_count,
                                        size_t item_size,
                                        int (LIBDCALL *compar)(void const *a, void const *b, void *arg),
                                        void *arg) {
	struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0A0A1c1 libd_bsearch_r_cookie;
	libd_bsearch_r_cookie.compar = compar;
	libd_bsearch_r_cookie.arg    = arg;
	return libc_bsearch_r(pkey, pbase, item_count, item_size, (int (LIBCCALL *)(void const *, void const *, void *))&_dwrap_sTPTP_TDTPTPTP_c0A0A1c1, &libd_bsearch_r_cookie);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.utility.stdlib") WUNUSED ATTR_IN(1) ATTR_IN_OPT(2) NONNULL((5)) void *
NOTHROW_CB_NCX(LIBCCALL libc_bsearch_r)(void const *pkey,
                                        void const *pbase,
                                        size_t item_count,
                                        size_t item_size,
                                        int (LIBCCALL *compar)(void const *a, void const *b, void *arg),
                                        void *arg) {
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
		if (difference < 0) {
			/* KEY < ITEM --> Narrow the search-area to everything below */
			hi = test_index;
		} else if (difference > 0) {
			/* KEY > ITEM --> Narrow the search-area to everything above */
			lo = test_index + 1;
		} else {
			/* Found it! */
			return item_addr;
		}
	}
	return NULL;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P_VOID(libd_qsort,libd_qsort_r,ATTR_INOUT_OPT(1) NONNULL((4)),NOTHROW_CB_NCX,LIBDCALL,(void *pbase, size_t item_count, size_t item_size, int (LIBDCALL *compar)(void const *a, void const *b)),(pbase,item_count,item_size,compar));
#else /* __LIBDCALL_CALLER_CLEANUP */
#ifndef __dwrap_cTP_TDTPTPTP_CA0A1_defined
#define __dwrap_cTP_TDTPTPTP_CA0A1_defined
PRIVATE ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility.stdlib") int
(LIBCCALL _dwrap_cTP_TDTPTPTP_CA0A1)(void const *a,
                                     void const *b,
                                     int (LIBDCALL *c)(void const *a, void const *b)) THROWS(...) {
	return (*c)(a, b);
}
#endif /* !__dwrap_cTP_TDTPTPTP_CA0A1_defined */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility.stdlib") ATTR_INOUT_OPT(1) NONNULL((4)) void
NOTHROW_CB_NCX(LIBDCALL libd_qsort)(void *pbase,
                                    size_t item_count,
                                    size_t item_size,
                                    int (LIBDCALL *compar)(void const *a, void const *b)) {
	libc_qsort_r(pbase, item_count, item_size, (int (LIBCCALL *)(void const *, void const *, void *))&_dwrap_cTP_TDTPTPTP_CA0A1, (void *)compar);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P_VOID(libc_qsort,libc_qsort_r,ATTR_INOUT_OPT(1) NONNULL((4)),NOTHROW_CB_NCX,LIBCCALL,(void *pbase, size_t item_count, size_t item_size, int (LIBCCALL *compar)(void const *a, void const *b)),(pbase,item_count,item_size,compar));
#else /* __LIBKCALL_CALLER_CLEANUP */
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
INTERN ATTR_SECTION(".text.crt.utility.stdlib") ATTR_INOUT_OPT(1) NONNULL((4)) void
NOTHROW_CB_NCX(LIBCCALL libc_qsort)(void *pbase,
                                    size_t item_count,
                                    size_t item_size,
                                    int (LIBCCALL *compar)(void const *a, void const *b)) {
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
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd_bsearch,libd_bsearch_r,WUNUSED ATTR_IN(1) ATTR_IN_OPT(2) NONNULL((5)),void *,NOTHROW_CB_NCX,LIBDCALL,(void const *pkey, void const *pbase, size_t item_count, size_t item_size, int (LIBDCALL *compar)(void const *a, void const *b)),(pkey,pbase,item_count,item_size,compar));
#else /* __LIBDCALL_CALLER_CLEANUP */
#ifndef __dwrap_cTP_TDTPTPTP_CA0A1_defined
#define __dwrap_cTP_TDTPTPTP_CA0A1_defined
PRIVATE ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility.stdlib") int
(LIBCCALL _dwrap_cTP_TDTPTPTP_CA0A1)(void const *a,
                                     void const *b,
                                     int (LIBDCALL *c)(void const *a, void const *b)) THROWS(...) {
	return (*c)(a, b);
}
#endif /* !__dwrap_cTP_TDTPTPTP_CA0A1_defined */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility.stdlib") WUNUSED ATTR_IN(1) ATTR_IN_OPT(2) NONNULL((5)) void *
NOTHROW_CB_NCX(LIBDCALL libd_bsearch)(void const *pkey,
                                      void const *pbase,
                                      size_t item_count,
                                      size_t item_size,
                                      int (LIBDCALL *compar)(void const *a, void const *b)) {
	return libc_bsearch_r(pkey, pbase, item_count, item_size, (int (LIBCCALL *)(void const *, void const *, void *))&_dwrap_cTP_TDTPTPTP_CA0A1, (void *)compar);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_bsearch,libc_bsearch_r,WUNUSED ATTR_IN(1) ATTR_IN_OPT(2) NONNULL((5)),void *,NOTHROW_CB_NCX,LIBCCALL,(void const *pkey, void const *pbase, size_t item_count, size_t item_size, int (LIBCCALL *compar)(void const *a, void const *b)),(pkey,pbase,item_count,item_size,compar));
#else /* __LIBKCALL_CALLER_CLEANUP */
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
INTERN ATTR_SECTION(".text.crt.utility.stdlib") WUNUSED ATTR_IN(1) ATTR_IN_OPT(2) NONNULL((5)) void *
NOTHROW_CB_NCX(LIBCCALL libc_bsearch)(void const *pkey,
                                      void const *pbase,
                                      size_t item_count,
                                      size_t item_size,
                                      int (LIBCCALL *compar)(void const *a, void const *b)) {
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
#endif /* !__LIBKCALL_CALLER_CLEANUP */
INTERN ATTR_SECTION(".text.crt.math.utility") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_abs)(int x) {
	return x < 0 ? -x : x;
}
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS_P(libc_labs,libc_abs,ATTR_CONST WUNUSED,long,NOTHROW,LIBCCALL,(long x),(x));
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.math.utility") ATTR_CONST WUNUSED long
NOTHROW(LIBCCALL libc_labs)(long x) {
	return x < 0 ? -x : x;
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.math.utility") WUNUSED __ATTR_CONST struct __div_struct
NOTHROW_NCX(LIBCCALL libc_div)(int numer,
                               int denom) {
	div_t result;
	result.quot = numer / denom;
	result.rem  = numer % denom;
	return result;
}
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS_P(libc_ldiv,libc_div,WUNUSED __ATTR_CONST,ldiv_t,NOTHROW_NCX,LIBCCALL,(long numer, long denom),(numer,denom));
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.math.utility") WUNUSED __ATTR_CONST ldiv_t
NOTHROW_NCX(LIBCCALL libc_ldiv)(long numer,
                                long denom) {
	ldiv_t result;
	result.quot = numer / denom;
	result.rem  = numer % denom;
	return result;
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_INT__ */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS_P(libc_llabs,libc_abs,ATTR_CONST WUNUSED,__LONGLONG,NOTHROW,LIBCCALL,(__LONGLONG x),(x));
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS_P(libc_llabs,libc_labs,ATTR_CONST WUNUSED,__LONGLONG,NOTHROW,LIBCCALL,(__LONGLONG x),(x));
#else /* ... */
INTERN ATTR_SECTION(".text.crt.math.utility") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBCCALL libc_llabs)(__LONGLONG x) {
	return x < 0 ? -x : x;
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS_P(libc_lldiv,libc_div,WUNUSED __ATTR_CONST,lldiv_t,NOTHROW_NCX,LIBCCALL,(__LONGLONG numer, __LONGLONG denom),(numer,denom));
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS_P(libc_lldiv,libc_ldiv,WUNUSED __ATTR_CONST,lldiv_t,NOTHROW_NCX,LIBCCALL,(__LONGLONG numer, __LONGLONG denom),(numer,denom));
#else /* ... */
INTERN ATTR_SECTION(".text.crt.math.utility") WUNUSED __ATTR_CONST lldiv_t
NOTHROW_NCX(LIBCCALL libc_lldiv)(__LONGLONG numer,
                                 __LONGLONG denom) {
	lldiv_t result;
	result.quot = numer / denom;
	result.rem  = numer % denom;
	return result;
}
#endif /* !... */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_IN_OPT(1) int
NOTHROW_NCX(LIBCCALL libc_mblen)(char const *str,
                                 size_t maxlen) {
	return libc_mbrlen(str, maxlen, NULL);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_IN_OPT(2) ATTR_OUT_OPT(1) int
NOTHROW_NCX(LIBDCALL libd_mbtowc)(char16_t *__restrict pwc,
                                  char const *__restrict str,
                                  size_t maxlen) {
	return libd_mbrtowc(pwc, str, maxlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_IN_OPT(2) ATTR_OUT_OPT(1) int
NOTHROW_NCX(LIBKCALL libc_mbtowc)(char32_t *__restrict pwc,
                                  char const *__restrict str,
                                  size_t maxlen) {
	return libc_mbrtowc(pwc, str, maxlen, NULL);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_OUT_OPT(1) int
NOTHROW_NCX(LIBDCALL libd_wctomb)(char *str,
                                  char16_t wc) {
	return libd_wcrtomb(str, wc, NULL);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_OUT_OPT(1) int
NOTHROW_NCX(LIBKCALL libc_wctomb)(char *str,
                                  char32_t wc) {
	return libc_wcrtomb(str, wc, NULL);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_IN(2) ATTR_OUTS(1, 3) size_t
NOTHROW_NCX(LIBDCALL libd_mbstowcs)(char16_t *__restrict dst,
                                    char const *__restrict src,
                                    size_t dstlen) {
	return libd_mbsrtowcs(dst, (char const **)&src, dstlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_IN(2) ATTR_OUTS(1, 3) size_t
NOTHROW_NCX(LIBKCALL libc_mbstowcs)(char32_t *__restrict dst,
                                    char const *__restrict src,
                                    size_t dstlen) {
	return libc_mbsrtowcs(dst, (char const **)&src, dstlen, NULL);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_IN(2) ATTR_OUTS(1, 3) size_t
NOTHROW_NCX(LIBDCALL libd_wcstombs)(char *__restrict dst,
                                    char16_t const *__restrict src,
                                    size_t dstlen) {
	return libd_wcsrtombs(dst, (char16_t const **)&src, dstlen, NULL);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_IN(2) ATTR_OUTS(1, 3) size_t
NOTHROW_NCX(LIBKCALL libc_wcstombs)(char *__restrict dst,
                                    char32_t const *__restrict src,
                                    size_t dstlen) {
	return libc_wcsrtombs(dst, (char32_t const **)&src, dstlen, NULL);
}
/* >> system(3)
 * Execute a given `command' on the system interpreter (as in `sh -c $command')
 * The return value is the `union wait' status after running `command', and may
 * be inspected using the `W*' macros (e.g. `WIFEXITED()') from `<sys/wait.h>'.
 *
 * When `command' is `NULL' only check if a system interpreter is available, and
 * return 0(false)/1(true) indicative of its present. When no system interpreter
 * is available and `command != NIL', `W_EXITCODE(127, 0)' is returned.
 *
 * @return: -1: Error (s.a. `errno')
 * @return: 0 : [command == NULL] No system interpreter is available
 * @return: 1 : [command == NULL] A system interpreter is available
 * @return: * : The `union wait'-style exit status of running `command' */
INTERN ATTR_SECTION(".text.crt.fs.exec.system") ATTR_IN_OPT(1) int
NOTHROW_RPC(LIBCCALL libc_system)(char const *command) {
	int status;
	pid_t cpid, error;

	cpid = libc_vfork();



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

		if (__libc_geterrno() != __EINTR)
			return -1;



	}
	return status;
}
#ifndef LIBC_ARCH_HAVE_ABORT
#include <asm/os/stdlib.h>
INTERN ATTR_SECTION(".text.crt.application.exit") ATTR_NORETURN void
(LIBCCALL libc_abort)(void) {
	libc__Exit(__EXIT_FAILURE);
}
#endif /* !LIBC_ARCH_HAVE_ABORT */
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_PURE WUNUSED ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_atoi)(char const *__restrict nptr) {
#if __SIZEOF_INT__ <= 4
	return (int)libc_strto32(nptr, NULL, 10);
#else /* __SIZEOF_INT__ <= 4 */
	return (int)libc_strto64(nptr, NULL, 10);
#endif /* __SIZEOF_INT__ > 4 */
}
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS_P(libc_atol,libc_atoi,ATTR_PURE WUNUSED ATTR_IN(1),long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr),(nptr));
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_PURE WUNUSED ATTR_IN(1) long
NOTHROW_NCX(LIBCCALL libc_atol)(char const *__restrict nptr) {
#if __SIZEOF_LONG__ <= 4
	return (long)libc_strto32(nptr, NULL, 10);
#else /* __SIZEOF_LONG__ <= 4 */
	return (long)libc_strto64(nptr, NULL, 10);
#endif /* __SIZEOF_LONG__ > 4 */
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_INT__ */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == 4
DEFINE_INTERN_ALIAS_P(libc_strtol,libc_strto32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc_strtol,libc_strto64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) long
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
#if __SIZEOF_LONG__ == 4
DEFINE_INTERN_ALIAS_P(libc_strtoul,libc_strtou32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc_strtoul,libc_strtou64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#else /* ... */
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) unsigned long
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
#include <hybrid/typecore.h>
#if __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS_P(libc_atoll,libc_atoi,ATTR_PURE WUNUSED ATTR_IN(1),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr),(nptr));
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS_P(libc_atoll,libc_atol,ATTR_PURE WUNUSED ATTR_IN(1),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr),(nptr));
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_PURE WUNUSED ATTR_IN(1) __LONGLONG
NOTHROW_NCX(LIBCCALL libc_atoll)(char const *__restrict nptr) {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__LONGLONG)libc_strto32(nptr, NULL, 10);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__LONGLONG)libc_strto64(nptr, NULL, 10);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc_strtoll,libc_strto64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS_P(libc_strtoll,libc_strto32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) __LONGLONG
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
#include <hybrid/typecore.h>
#if __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc_strtoull,libc_strtou64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS_P(libc_strtoull,libc_strtou32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) __ULONGLONG
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
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF WUNUSED ATTR_IN(1) double
NOTHROW_NCX(LIBCCALL libc_atof)(char const *__restrict nptr) {
	return libc_strtod(nptr, NULL);
}
#include <ieee754.h>
#include <libm/inf.h>
#include <libm/nan.h>
#include <libc/unicode.h>
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) double
NOTHROW_NCX(LIBCCALL libc_strtod)(char const *__restrict nptr,
                                  char **endptr) {
	char sign, ch = *nptr;
	double float_extension_mult;
	double fltval = 0.0;
	uint8_t numsys, digit;
	while (libc_isspace((unsigned char)ch))
		ch = *++nptr;
	sign = ch;
	if (sign == '+' || sign == '-')
		ch = *++nptr;
	if (ch == '0') {
		ch = *++nptr;
		if (ch == 'x' || ch == 'X') {
			ch = *++nptr;
			numsys = 16;
		} else if (ch == 'b' || ch == 'B') {
			ch = *++nptr;
			numsys = 2;
		} else if (ch == '.') {
			numsys = 10;
		} else if (!libc_isdigit((unsigned char)ch)) {
			goto done;
		} else {
			/*numsys = 8;*/ /* Would be non-conforming */
			numsys = 10;
		}
	} else {

		if ((ch == 'i' || ch == 'I') &&
		    (nptr[1] == 'n' || nptr[1] == 'N') &&
		    (nptr[2] == 'f' || nptr[2] == 'F') &&
		    !libc_isalnum((unsigned char)nptr[3])) {
			nptr += 3;
			if (endptr)
				*endptr = (char *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN0(inf)
			                   : +__LIBM_MATHFUN0(inf);
		}
		if ((ch == 'n' || ch == 'N') &&
		    (nptr[1] == 'a' || nptr[1] == 'A') &&
		    (nptr[2] == 'n' || nptr[2] == 'N') &&
		    !libc_isalnum((unsigned char)nptr[3])) {
			nptr += 3;
			if (*nptr == '(') {
				++nptr;
				while (*nptr != ')')
					++nptr;
				++nptr;
				/* XXX: Custom nan-tag? */
			}
			if (endptr)
				*endptr = (char *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN1I(nan, NULL)
			                   : +__LIBM_MATHFUN1I(nan, NULL);
		}

		numsys = 10;
	}

	float_extension_mult = 0.0;
next:
	switch (ch) {
	case 'p':
	case 'P':
		if (numsys == 10)
			goto done;
		goto flt_exp;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		digit = ch - '0';
		break;

	case 'e':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'f':
		digit = 10 + ch - 'a';
		break;

	case 'E':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'F':
		digit = 10 + ch - 'A';
		break;

	case '.':
		if (float_extension_mult != 0.0)
			goto done;
		float_extension_mult = (double)numsys;
		ch = *++nptr;
		goto next;

	default: {

		char const *new_nptr;
		char32_t uni;
#ifndef __OPTIMIZE_SIZE__
		if ((unsigned char)ch < 0x80)
			goto done;
#endif /* !__OPTIMIZE_SIZE__ */
		new_nptr = nptr;
		uni = __libc_unicode_readutf8(&new_nptr);
		if (__libc_unicode_asdigit(uni, numsys, &digit)) {
			nptr = new_nptr;
		} else













		{
			goto done;
		}
	}	break;

	}
	if unlikely(digit >= numsys)
		goto done;
	ch = *++nptr;
	if (float_extension_mult != 0.0) {
		fltval += (double)digit / float_extension_mult;
		float_extension_mult *= numsys;
	} else {
		fltval = fltval * numsys + digit;
	}
	goto next;
	{
#define float_extension_pos digit
		unsigned int float_extension_off;
		char float_exp_mode;
flt_exp:
		float_exp_mode = ch;
		float_extension_pos = 1;
		float_extension_off = 0;
		ch = *++nptr;
		if (ch == '-' || ch == '+') {
			float_extension_pos = (ch == '+');
			ch = *++nptr;
		}
		while (ch >= '0' && ch <= '9') {
			float_extension_off *= 10;
			float_extension_off += ch - '0';
			ch = *++nptr;
		}
		float_extension_mult = 1.0;
		if (float_exp_mode == 'e' || float_exp_mode == 'E') {
			while (float_extension_off != 0) {
				float_extension_mult *= 10.0;
				--float_extension_off;
			}
		} else {
			while (float_extension_off != 0) {
				float_extension_mult *= 2.0;
				--float_extension_off;
			}
		}
		if (float_extension_pos) {
			fltval *= float_extension_mult;
		} else {
			fltval /= float_extension_mult;
		}
#undef float_extension_pos
		/* FALLTHRU to "done" */
	}
done:
	if (endptr)
		*endptr = (char *)nptr;
	if (sign == '-')
		fltval = -fltval;
	return fltval;
}
#include <ieee754.h>
#include <libm/inf.h>
#include <libm/nan.h>
#include <libc/unicode.h>
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) float
NOTHROW_NCX(LIBCCALL libc_strtof)(char const *__restrict nptr,
                                  char **endptr) {
	char sign, ch = *nptr;
	float float_extension_mult;
	float fltval = 0.0f;
	uint8_t numsys, digit;
	while (libc_isspace((unsigned char)ch))
		ch = *++nptr;
	sign = ch;
	if (sign == '+' || sign == '-')
		ch = *++nptr;
	if (ch == '0') {
		ch = *++nptr;
		if (ch == 'x' || ch == 'X') {
			ch = *++nptr;
			numsys = 16;
		} else if (ch == 'b' || ch == 'B') {
			ch = *++nptr;
			numsys = 2;
		} else if (ch == '.') {
			numsys = 10;
		} else if (!libc_isdigit((unsigned char)ch)) {
			goto done;
		} else {
			/*numsys = 8;*/ /* Would be non-conforming */
			numsys = 10;
		}
	} else {

		if ((ch == 'i' || ch == 'I') &&
		    (nptr[1] == 'n' || nptr[1] == 'N') &&
		    (nptr[2] == 'f' || nptr[2] == 'F') &&
		    !libc_isalnum((unsigned char)nptr[3])) {
			nptr += 3;
			if (endptr)
				*endptr = (char *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN0F(inf)
			                   : +__LIBM_MATHFUN0F(inf);
		}
		if ((ch == 'n' || ch == 'N') &&
		    (nptr[1] == 'a' || nptr[1] == 'A') &&
		    (nptr[2] == 'n' || nptr[2] == 'N') &&
		    !libc_isalnum((unsigned char)nptr[3])) {
			nptr += 3;
			if (*nptr == '(') {
				++nptr;
				while (*nptr != ')')
					++nptr;
				++nptr;
				/* XXX: Custom nan-tag? */
			}
			if (endptr)
				*endptr = (char *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN1IF(nan, NULL)
			                   : +__LIBM_MATHFUN1IF(nan, NULL);
		}

		numsys = 10;
	}

	float_extension_mult = 0.0f;
next:
	switch (ch) {
	case 'p':
	case 'P':
		if (numsys == 10)
			goto done;
		goto flt_exp;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		digit = ch - '0';
		break;

	case 'e':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'f':
		digit = 10 + ch - 'a';
		break;

	case 'E':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'F':
		digit = 10 + ch - 'A';
		break;

	case '.':
		if (float_extension_mult != 0.0f)
			goto done;
		float_extension_mult = (float)numsys;
		ch = *++nptr;
		goto next;

	default: {

		char const *new_nptr;
		char32_t uni;
#ifndef __OPTIMIZE_SIZE__
		if ((unsigned char)ch < 0x80)
			goto done;
#endif /* !__OPTIMIZE_SIZE__ */
		new_nptr = nptr;
		uni = __libc_unicode_readutf8(&new_nptr);
		if (__libc_unicode_asdigit(uni, numsys, &digit)) {
			nptr = new_nptr;
		} else













		{
			goto done;
		}
	}	break;

	}
	if unlikely(digit >= numsys)
		goto done;
	ch = *++nptr;
	if (float_extension_mult != 0.0f) {
		fltval += (float)digit / float_extension_mult;
		float_extension_mult *= numsys;
	} else {
		fltval = fltval * numsys + digit;
	}
	goto next;
	{
#define float_extension_pos digit
		unsigned int float_extension_off;
		char float_exp_mode;
flt_exp:
		float_exp_mode = ch;
		float_extension_pos = 1;
		float_extension_off = 0;
		ch = *++nptr;
		if (ch == '-' || ch == '+') {
			float_extension_pos = (ch == '+');
			ch = *++nptr;
		}
		while (ch >= '0' && ch <= '9') {
			float_extension_off *= 10;
			float_extension_off += ch - '0';
			ch = *++nptr;
		}
		float_extension_mult = 1.0f;
		if (float_exp_mode == 'e' || float_exp_mode == 'E') {
			while (float_extension_off != 0) {
				float_extension_mult *= 10.0f;
				--float_extension_off;
			}
		} else {
			while (float_extension_off != 0) {
				float_extension_mult *= 2.0f;
				--float_extension_off;
			}
		}
		if (float_extension_pos) {
			fltval *= float_extension_mult;
		} else {
			fltval /= float_extension_mult;
		}
#undef float_extension_pos
		/* FALLTHRU to "done" */
	}
done:
	if (endptr)
		*endptr = (char *)nptr;
	if (sign == '-')
		fltval = -fltval;
	return fltval;
}
#include <hybrid/typecore.h>
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS_P(libc_strtold,libc_strtod,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGDOUBLE,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr),(nptr,endptr));
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <ieee754.h>
#include <libm/inf.h>
#include <libm/nan.h>
#include <libc/unicode.h>
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) __LONGDOUBLE
NOTHROW_NCX(LIBCCALL libc_strtold)(char const *__restrict nptr,
                                   char **endptr) {
	char sign, ch = *nptr;
	__LONGDOUBLE float_extension_mult;
	__LONGDOUBLE fltval = 0.0L;
	uint8_t numsys, digit;
	while (libc_isspace((unsigned char)ch))
		ch = *++nptr;
	sign = ch;
	if (sign == '+' || sign == '-')
		ch = *++nptr;
	if (ch == '0') {
		ch = *++nptr;
		if (ch == 'x' || ch == 'X') {
			ch = *++nptr;
			numsys = 16;
		} else if (ch == 'b' || ch == 'B') {
			ch = *++nptr;
			numsys = 2;
		} else if (ch == '.') {
			numsys = 10;
		} else if (!libc_isdigit((unsigned char)ch)) {
			goto done;
		} else {
			/*numsys = 8;*/ /* Would be non-conforming */
			numsys = 10;
		}
	} else {

		if ((ch == 'i' || ch == 'I') &&
		    (nptr[1] == 'n' || nptr[1] == 'N') &&
		    (nptr[2] == 'f' || nptr[2] == 'F') &&
		    !libc_isalnum((unsigned char)nptr[3])) {
			nptr += 3;
			if (endptr)
				*endptr = (char *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN0L(inf)
			                   : +__LIBM_MATHFUN0L(inf);
		}
		if ((ch == 'n' || ch == 'N') &&
		    (nptr[1] == 'a' || nptr[1] == 'A') &&
		    (nptr[2] == 'n' || nptr[2] == 'N') &&
		    !libc_isalnum((unsigned char)nptr[3])) {
			nptr += 3;
			if (*nptr == '(') {
				++nptr;
				while (*nptr != ')')
					++nptr;
				++nptr;
				/* XXX: Custom nan-tag? */
			}
			if (endptr)
				*endptr = (char *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN1IL(nan, NULL)
			                   : +__LIBM_MATHFUN1IL(nan, NULL);
		}

		numsys = 10;
	}

	float_extension_mult = 0.0L;
next:
	switch (ch) {
	case 'p':
	case 'P':
		if (numsys == 10)
			goto done;
		goto flt_exp;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		digit = ch - '0';
		break;

	case 'e':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'f':
		digit = 10 + ch - 'a';
		break;

	case 'E':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'F':
		digit = 10 + ch - 'A';
		break;

	case '.':
		if (float_extension_mult != 0.0L)
			goto done;
		float_extension_mult = (__LONGDOUBLE)numsys;
		ch = *++nptr;
		goto next;

	default: {

		char const *new_nptr;
		char32_t uni;
#ifndef __OPTIMIZE_SIZE__
		if ((unsigned char)ch < 0x80)
			goto done;
#endif /* !__OPTIMIZE_SIZE__ */
		new_nptr = nptr;
		uni = __libc_unicode_readutf8(&new_nptr);
		if (__libc_unicode_asdigit(uni, numsys, &digit)) {
			nptr = new_nptr;
		} else













		{
			goto done;
		}
	}	break;

	}
	if unlikely(digit >= numsys)
		goto done;
	ch = *++nptr;
	if (float_extension_mult != 0.0L) {
		fltval += (__LONGDOUBLE)digit / float_extension_mult;
		float_extension_mult *= numsys;
	} else {
		fltval = fltval * numsys + digit;
	}
	goto next;
	{
#define float_extension_pos digit
		unsigned int float_extension_off;
		char float_exp_mode;
flt_exp:
		float_exp_mode = ch;
		float_extension_pos = 1;
		float_extension_off = 0;
		ch = *++nptr;
		if (ch == '-' || ch == '+') {
			float_extension_pos = (ch == '+');
			ch = *++nptr;
		}
		while (ch >= '0' && ch <= '9') {
			float_extension_off *= 10;
			float_extension_off += ch - '0';
			ch = *++nptr;
		}
		float_extension_mult = 1.0L;
		if (float_exp_mode == 'e' || float_exp_mode == 'E') {
			while (float_extension_off != 0) {
				float_extension_mult *= 10.0L;
				--float_extension_off;
			}
		} else {
			while (float_extension_off != 0) {
				float_extension_mult *= 2.0L;
				--float_extension_off;
			}
		}
		if (float_extension_pos) {
			fltval *= float_extension_mult;
		} else {
			fltval /= float_extension_mult;
		}
#undef float_extension_pos
		/* FALLTHRU to "done" */
	}
done:
	if (endptr)
		*endptr = (char *)nptr;
	if (sign == '-')
		fltval = -fltval;
	return fltval;
}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#endif /* !__KERNEL__ */
#include <asm/os/errno.h>
#include <hybrid/__overflow.h>
#include <libc/template/hex.h>
#include <hybrid/limitcore.h>
#include <libc/unicode.h>
#include <hybrid/typecore.h>
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
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4) uint32_t
NOTHROW_NCX(LIBCCALL libc_strtou32_r)(char const *__restrict nptr,
                                      char **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      errno_t *error) {







	uint32_t result;
	char const *num_start = nptr;
	char const *num_iter;
	num_start = libc_strlstrip(num_start);





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
				--num_start;
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
		if (!__libc_hex2int(ch, &digit)) {
#ifdef __CRT_HAVE___unicode_descriptor
			/* Unicode decimal support */

			char const *new_num_iter;
			char32_t uni;
#ifndef __OPTIMIZE_SIZE__
			if ((unsigned char)ch < 0x80)
				break;
#endif /* !__OPTIMIZE_SIZE__ */
			new_num_iter = num_iter;
			uni = __libc_unicode_readutf8(&new_num_iter);
			if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
				num_iter = new_num_iter;
			} else













#endif /* __CRT_HAVE___unicode_descriptor */
			{
				break;
			}
		} else {
			if (digit >= base)
				break;
			++num_iter;
		}
		if unlikely(__hybrid_overflow_umul(result, (unsigned int)base, &result) ||
		/*       */ __hybrid_overflow_uadd(result, digit, &result)) {





















































			/* Integer overflow. */
			if (error) {
#ifdef ERANGE
				*error = ERANGE;
#else /* ERANGE */
				*error = 1;
#endif /* !ERANGE */
			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (!__libc_hex2int(ch, &digit)) {
#ifdef __CRT_HAVE___unicode_descriptor
						/* Unicode decimal support */

						char const *new_num_iter;
						char32_t uni;
#ifndef __OPTIMIZE_SIZE__
						if ((unsigned char)ch < 0x80)
							break;
#endif /* !__OPTIMIZE_SIZE__ */
						new_num_iter = num_iter;
						uni = __libc_unicode_readutf8(&new_num_iter);
						if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
							num_iter = new_num_iter;
						} else













#endif /* __CRT_HAVE___unicode_descriptor */
						{
							break;
						}
					} else {
						if (digit >= base)
							break;
						++num_iter;
					}
				}
				*endptr = (char *)num_iter;
			}





			return __UINT32_MAX__;

		}
	}







	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char const *nptr_ps = nptr;
			nptr_ps = libc_strlstrip(nptr_ps);
			if (num_start > nptr_ps && *nptr_ps == '0') {
				if (endptr)
					*endptr = (char *)nptr_ps + 1;
				if (error)
					*error = 0;
				return 0;
			}
		}
		/* Empty number... */
		if (error) {
#ifdef ECANCELED
			*error = ECANCELED;
#else /* ECANCELED */
			*error = 1;
#endif /* !ECANCELED */
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
				num_iter = libc_strlstrip(num_iter);
				if (*num_iter) {
#ifdef EINVAL
					*error = EINVAL;
#else /* EINVAL */
					*error = 1;
#endif /* !EINVAL */
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
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4) int32_t
NOTHROW_NCX(LIBCCALL libc_strto32_r)(char const *__restrict nptr,
                                     char **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     errno_t *error) {





	char sign;

	int32_t result;
	char const *num_start = nptr;
	char const *num_iter;
	num_start = libc_strlstrip(num_start);

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
				--num_start;
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
		if (!__libc_hex2int(ch, &digit)) {
#ifdef __CRT_HAVE___unicode_descriptor
			/* Unicode decimal support */

			char const *new_num_iter;
			char32_t uni;
#ifndef __OPTIMIZE_SIZE__
			if ((unsigned char)ch < 0x80)
				break;
#endif /* !__OPTIMIZE_SIZE__ */
			new_num_iter = num_iter;
			uni = __libc_unicode_readutf8(&new_num_iter);
			if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
				num_iter = new_num_iter;
			} else













#endif /* __CRT_HAVE___unicode_descriptor */
			{
				break;
			}
		} else {
			if (digit >= base)
				break;
			++num_iter;
		}
		if unlikely(__hybrid_overflow_smul(result, (unsigned int)base, &result) ||
		/*       */ __hybrid_overflow_sadd(result, digit, &result)) {

			/* Check for special case: `strtoi(itos(T.MIN))' */
			if ((__UINT32_TYPE__)result == ((__UINT32_TYPE__)0 - (__UINT32_TYPE__)__INT32_MIN__) &&
			    sign == '-') {
				/* Must ensure that we're at the end of the input string. */
				ch = *num_iter;
				if (!__libc_hex2int(ch, &digit)) {
#ifdef __CRT_HAVE___unicode_descriptor
					/* Unicode decimal support */

					char const *new_num_iter;
					char32_t uni;
#ifndef __OPTIMIZE_SIZE__
					if ((unsigned char)ch < 0x80) {
						/* Not actually an overflow --> result is supposed to be `INTxx_MIN'! */
						goto handle_not_an_overflow;
					}
#endif /* !__OPTIMIZE_SIZE__ */
					new_num_iter = num_iter;
					uni = __libc_unicode_readutf8(&new_num_iter);
					if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
						goto handle_overflow;
					} else













#endif /* __CRT_HAVE___unicode_descriptor */
					{
						/* Not a digit valid for `radix' --> allowed */
					}
				} else {
					if (digit < base)
						goto handle_overflow;
				}
				/* Not actually an overflow --> result is supposed to be `INTxx_MIN'! */
#if defined(__CRT_HAVE___unicode_descriptor) && !defined(__OPTIMIZE_SIZE__)
handle_not_an_overflow:
#endif /* __CRT_HAVE___unicode_descriptor && !__OPTIMIZE_SIZE__ */
				result = __INT32_MIN__;
				goto return_not_an_overflow;
			}
handle_overflow:

			/* Integer overflow. */
			if (error) {
#ifdef ERANGE
				*error = ERANGE;
#else /* ERANGE */
				*error = 1;
#endif /* !ERANGE */
			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (!__libc_hex2int(ch, &digit)) {
#ifdef __CRT_HAVE___unicode_descriptor
						/* Unicode decimal support */

						char const *new_num_iter;
						char32_t uni;
#ifndef __OPTIMIZE_SIZE__
						if ((unsigned char)ch < 0x80)
							break;
#endif /* !__OPTIMIZE_SIZE__ */
						new_num_iter = num_iter;
						uni = __libc_unicode_readutf8(&new_num_iter);
						if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
							num_iter = new_num_iter;
						} else













#endif /* __CRT_HAVE___unicode_descriptor */
						{
							break;
						}
					} else {
						if (digit >= base)
							break;
						++num_iter;
					}
				}
				*endptr = (char *)num_iter;
			}

			if (sign == '-')
				return __INT32_MIN__;
			return __INT32_MAX__;



		}
	}

	if (sign == '-') {
		if (__hybrid_overflow_sneg_p2n(result, &result)) /* NOLINT */
			goto handle_overflow; /* Overflow... */
	}


	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char const *nptr_ps = nptr;
			nptr_ps = libc_strlstrip(nptr_ps);
			if (num_start > nptr_ps && *nptr_ps == '0') {
				if (endptr)
					*endptr = (char *)nptr_ps + 1;
				if (error)
					*error = 0;
				return 0;
			}
		}
		/* Empty number... */
		if (error) {
#ifdef ECANCELED
			*error = ECANCELED;
#else /* ECANCELED */
			*error = 1;
#endif /* !ECANCELED */
		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (endptr)
			*endptr = (char *)nptr;
	} else {

return_not_an_overflow:

		if (endptr) {
			*endptr = (char *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				num_iter = libc_strlstrip(num_iter);
				if (*num_iter) {
#ifdef EINVAL
					*error = EINVAL;
#else /* EINVAL */
					*error = 1;
#endif /* !EINVAL */
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
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4) uint64_t
NOTHROW_NCX(LIBCCALL libc_strtou64_r)(char const *__restrict nptr,
                                      char **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      errno_t *error) {







	uint64_t result;
	char const *num_start = nptr;
	char const *num_iter;
	num_start = libc_strlstrip(num_start);





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
				--num_start;
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
		if (!__libc_hex2int(ch, &digit)) {
#ifdef __CRT_HAVE___unicode_descriptor
			/* Unicode decimal support */

			char const *new_num_iter;
			char32_t uni;
#ifndef __OPTIMIZE_SIZE__
			if ((unsigned char)ch < 0x80)
				break;
#endif /* !__OPTIMIZE_SIZE__ */
			new_num_iter = num_iter;
			uni = __libc_unicode_readutf8(&new_num_iter);
			if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
				num_iter = new_num_iter;
			} else













#endif /* __CRT_HAVE___unicode_descriptor */
			{
				break;
			}
		} else {
			if (digit >= base)
				break;
			++num_iter;
		}
		if unlikely(__hybrid_overflow_umul(result, (unsigned int)base, &result) ||
		/*       */ __hybrid_overflow_uadd(result, digit, &result)) {





















































			/* Integer overflow. */
			if (error) {
#ifdef ERANGE
				*error = ERANGE;
#else /* ERANGE */
				*error = 1;
#endif /* !ERANGE */
			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (!__libc_hex2int(ch, &digit)) {
#ifdef __CRT_HAVE___unicode_descriptor
						/* Unicode decimal support */

						char const *new_num_iter;
						char32_t uni;
#ifndef __OPTIMIZE_SIZE__
						if ((unsigned char)ch < 0x80)
							break;
#endif /* !__OPTIMIZE_SIZE__ */
						new_num_iter = num_iter;
						uni = __libc_unicode_readutf8(&new_num_iter);
						if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
							num_iter = new_num_iter;
						} else













#endif /* __CRT_HAVE___unicode_descriptor */
						{
							break;
						}
					} else {
						if (digit >= base)
							break;
						++num_iter;
					}
				}
				*endptr = (char *)num_iter;
			}





			return __UINT64_MAX__;

		}
	}







	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char const *nptr_ps = nptr;
			nptr_ps = libc_strlstrip(nptr_ps);
			if (num_start > nptr_ps && *nptr_ps == '0') {
				if (endptr)
					*endptr = (char *)nptr_ps + 1;
				if (error)
					*error = 0;
				return 0;
			}
		}
		/* Empty number... */
		if (error) {
#ifdef ECANCELED
			*error = ECANCELED;
#else /* ECANCELED */
			*error = 1;
#endif /* !ECANCELED */
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
				num_iter = libc_strlstrip(num_iter);
				if (*num_iter) {
#ifdef EINVAL
					*error = EINVAL;
#else /* EINVAL */
					*error = 1;
#endif /* !EINVAL */
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
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4) int64_t
NOTHROW_NCX(LIBCCALL libc_strto64_r)(char const *__restrict nptr,
                                     char **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     errno_t *error) {





	char sign;

	int64_t result;
	char const *num_start = nptr;
	char const *num_iter;
	num_start = libc_strlstrip(num_start);

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
				--num_start;
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
		if (!__libc_hex2int(ch, &digit)) {
#ifdef __CRT_HAVE___unicode_descriptor
			/* Unicode decimal support */

			char const *new_num_iter;
			char32_t uni;
#ifndef __OPTIMIZE_SIZE__
			if ((unsigned char)ch < 0x80)
				break;
#endif /* !__OPTIMIZE_SIZE__ */
			new_num_iter = num_iter;
			uni = __libc_unicode_readutf8(&new_num_iter);
			if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
				num_iter = new_num_iter;
			} else













#endif /* __CRT_HAVE___unicode_descriptor */
			{
				break;
			}
		} else {
			if (digit >= base)
				break;
			++num_iter;
		}
		if unlikely(__hybrid_overflow_smul(result, (unsigned int)base, &result) ||
		/*       */ __hybrid_overflow_sadd(result, digit, &result)) {

			/* Check for special case: `strtoi(itos(T.MIN))' */
			if ((__UINT64_TYPE__)result == ((__UINT64_TYPE__)0 - (__UINT64_TYPE__)__INT64_MIN__) &&
			    sign == '-') {
				/* Must ensure that we're at the end of the input string. */
				ch = *num_iter;
				if (!__libc_hex2int(ch, &digit)) {
#ifdef __CRT_HAVE___unicode_descriptor
					/* Unicode decimal support */

					char const *new_num_iter;
					char32_t uni;
#ifndef __OPTIMIZE_SIZE__
					if ((unsigned char)ch < 0x80) {
						/* Not actually an overflow --> result is supposed to be `INTxx_MIN'! */
						goto handle_not_an_overflow;
					}
#endif /* !__OPTIMIZE_SIZE__ */
					new_num_iter = num_iter;
					uni = __libc_unicode_readutf8(&new_num_iter);
					if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
						goto handle_overflow;
					} else













#endif /* __CRT_HAVE___unicode_descriptor */
					{
						/* Not a digit valid for `radix' --> allowed */
					}
				} else {
					if (digit < base)
						goto handle_overflow;
				}
				/* Not actually an overflow --> result is supposed to be `INTxx_MIN'! */
#if defined(__CRT_HAVE___unicode_descriptor) && !defined(__OPTIMIZE_SIZE__)
handle_not_an_overflow:
#endif /* __CRT_HAVE___unicode_descriptor && !__OPTIMIZE_SIZE__ */
				result = __INT64_MIN__;
				goto return_not_an_overflow;
			}
handle_overflow:

			/* Integer overflow. */
			if (error) {
#ifdef ERANGE
				*error = ERANGE;
#else /* ERANGE */
				*error = 1;
#endif /* !ERANGE */
			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (!__libc_hex2int(ch, &digit)) {
#ifdef __CRT_HAVE___unicode_descriptor
						/* Unicode decimal support */

						char const *new_num_iter;
						char32_t uni;
#ifndef __OPTIMIZE_SIZE__
						if ((unsigned char)ch < 0x80)
							break;
#endif /* !__OPTIMIZE_SIZE__ */
						new_num_iter = num_iter;
						uni = __libc_unicode_readutf8(&new_num_iter);
						if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
							num_iter = new_num_iter;
						} else













#endif /* __CRT_HAVE___unicode_descriptor */
						{
							break;
						}
					} else {
						if (digit >= base)
							break;
						++num_iter;
					}
				}
				*endptr = (char *)num_iter;
			}

			if (sign == '-')
				return __INT64_MIN__;
			return __INT64_MAX__;



		}
	}

	if (sign == '-') {
		if (__hybrid_overflow_sneg_p2n(result, &result)) /* NOLINT */
			goto handle_overflow; /* Overflow... */
	}


	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char const *nptr_ps = nptr;
			nptr_ps = libc_strlstrip(nptr_ps);
			if (num_start > nptr_ps && *nptr_ps == '0') {
				if (endptr)
					*endptr = (char *)nptr_ps + 1;
				if (error)
					*error = 0;
				return 0;
			}
		}
		/* Empty number... */
		if (error) {
#ifdef ECANCELED
			*error = ECANCELED;
#else /* ECANCELED */
			*error = 1;
#endif /* !ECANCELED */
		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (endptr)
			*endptr = (char *)nptr;
	} else {

return_not_an_overflow:

		if (endptr) {
			*endptr = (char *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				num_iter = libc_strlstrip(num_iter);
				if (*num_iter) {
#ifdef EINVAL
					*error = EINVAL;
#else /* EINVAL */
					*error = 1;
#endif /* !EINVAL */
				}
			}
		}
	}
	return result;
}
#include <libc/errno.h>
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the  end of the number in  `*endptr'.
 *
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid  integer (`U?INTn_(MIN|MAX))'. (though note that `endptr'
 * (if non-NULL) is still updated in this case!)
 *
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 *
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) uint32_t
NOTHROW_NCX(LIBCCALL libc_strtou32)(char const *__restrict nptr,
                                    char **endptr,
                                    __STDC_INT_AS_UINT_T base) {
#if defined(__libc_geterrno) && defined(ERANGE)
	uint32_t result;
	errno_t error;
	result = libc_strtou32_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)libc_seterrno(ERANGE);
	return result;
#else /* __libc_geterrno && ERANGE */
	return libc_strtou32_r(nptr, endptr, base, NULL);
#endif /* !__libc_geterrno || !ERANGE */
}
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the  end of the number in  `*endptr'.
 *
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid  integer (`U?INTn_(MIN|MAX))'. (though note that `endptr'
 * (if non-NULL) is still updated in this case!)
 *
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 *
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) int32_t
NOTHROW_NCX(LIBCCALL libc_strto32)(char const *__restrict nptr,
                                   char **endptr,
                                   __STDC_INT_AS_UINT_T base) {
#if defined(__libc_geterrno) && defined(ERANGE)
	int32_t result;
	errno_t error;
	result = libc_strto32_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)libc_seterrno(ERANGE);
	return result;
#else /* __libc_geterrno && ERANGE */
	return libc_strto32_r(nptr, endptr, base, NULL);
#endif /* !__libc_geterrno || !ERANGE */
}
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the  end of the number in  `*endptr'.
 *
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid  integer (`U?INTn_(MIN|MAX))'. (though note that `endptr'
 * (if non-NULL) is still updated in this case!)
 *
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 *
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) uint64_t
NOTHROW_NCX(LIBCCALL libc_strtou64)(char const *__restrict nptr,
                                    char **endptr,
                                    __STDC_INT_AS_UINT_T base) {
#if defined(__libc_geterrno) && defined(ERANGE)
	uint64_t result;
	errno_t error;
	result = libc_strtou64_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)libc_seterrno(ERANGE);
	return result;
#else /* __libc_geterrno && ERANGE */
	return libc_strtou64_r(nptr, endptr, base, NULL);
#endif /* !__libc_geterrno || !ERANGE */
}
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the  end of the number in  `*endptr'.
 *
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid  integer (`U?INTn_(MIN|MAX))'. (though note that `endptr'
 * (if non-NULL) is still updated in this case!)
 *
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 *
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) int64_t
NOTHROW_NCX(LIBCCALL libc_strto64)(char const *__restrict nptr,
                                   char **endptr,
                                   __STDC_INT_AS_UINT_T base) {
#if defined(__libc_geterrno) && defined(ERANGE)
	int64_t result;
	errno_t error;
	result = libc_strto64_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)libc_seterrno(ERANGE);
	return result;
#else /* __libc_geterrno && ERANGE */
	return libc_strto64_r(nptr, endptr, base, NULL);
#endif /* !__libc_geterrno || !ERANGE */
}
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) uint32_t
NOTHROW_NCX(LIBCCALL libc_strtou32_l)(char const *__restrict nptr,
                                      char **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libc_strtou32(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) int32_t
NOTHROW_NCX(LIBCCALL libc_strto32_l)(char const *__restrict nptr,
                                     char **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_strto32(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) uint64_t
NOTHROW_NCX(LIBCCALL libc_strtou64_l)(char const *__restrict nptr,
                                      char **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libc_strtou64(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) int64_t
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
        ".global libc__itoa_lower_digits\n"
        ".global libc__itoa_upper_digits\n"
        ".type   libc__itoa_lower_digits, \"object\"\n"
        ".type   libc__itoa_upper_digits, \"object\"\n"
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
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") WUNUSED ATTR_OUT(3) char *
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
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_OUT(3) ATTR_OUT(4) ATTR_OUTS(5, 6) int
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
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_OUT(3) ATTR_OUT(4) ATTR_OUTS(5, 6) int
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
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS_P(libc_qgcvt,libc_gcvt,ATTR_OUT(3),char *,NOTHROW_NCX,LIBCCALL,(__LONGDOUBLE val, int ndigit, char *buf),(val,ndigit,buf));
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <hybrid/floatcore.h>
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_OUT(3) char *
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
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS_P(libc_qecvt_r,libc_ecvt_r,ATTR_OUT(3) ATTR_OUT(4) ATTR_OUTS(5, 6),int,NOTHROW_NCX,LIBCCALL,(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len),(val,ndigit,decptr,sign,buf,len));
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_OUT(3) ATTR_OUT(4) ATTR_OUTS(5, 6) int
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
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS_P(libc_qfcvt_r,libc_fcvt_r,ATTR_OUT(3) ATTR_OUT(4) ATTR_OUTS(5, 6),int,NOTHROW_NCX,LIBCCALL,(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len),(val,ndigit,decptr,sign,buf,len));
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_OUT(3) ATTR_OUT(4) ATTR_OUTS(5, 6) int
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
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS_P(libc_qecvt,libc_ecvt,WUNUSED ATTR_OUT(3) ATTR_OUT(4),char *,NOTHROW_NCX,LIBCCALL,(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign),(val,ndigit,decptr,sign));
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include "../libc/tls-globals.h"
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") WUNUSED ATTR_OUT(3) ATTR_OUT(4) char *
NOTHROW_NCX(LIBCCALL libc_qecvt)(__LONGDOUBLE val,
                                 int ndigit,
                                 int *__restrict decptr,
                                 int *__restrict sign) {
	char (*const _p_qcvt_buf)[32] = &libc_get_tlsglobals()->ltg_qcvt_buf;
#define qcvt_buf (*_p_qcvt_buf)
	if (libc_qecvt_r(val, ndigit, decptr, sign,  qcvt_buf, sizeof(qcvt_buf)))
		return NULL;
	return qcvt_buf;
}
#undef qcvt_buf
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS_P(libc_qfcvt,libc_fcvt,WUNUSED ATTR_OUT(3) ATTR_OUT(4),char *,NOTHROW_NCX,LIBCCALL,(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign),(val,ndigit,decptr,sign));
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
#include "../libc/tls-globals.h"
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") WUNUSED ATTR_OUT(3) ATTR_OUT(4) char *
NOTHROW_NCX(LIBCCALL libc_qfcvt)(__LONGDOUBLE val,
                                 int ndigit,
                                 int *__restrict decptr,
                                 int *__restrict sign) {
	char (*const _p_qcvt_buf)[32] = &libc_get_tlsglobals()->ltg_qcvt_buf;
#define qcvt_buf (*_p_qcvt_buf)
	if (libc_qfcvt_r(val, ndigit, decptr, sign, qcvt_buf, sizeof(qcvt_buf)))
		return NULL;
	return qcvt_buf;
}
#undef qcvt_buf
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all  'X'-characters before the  call (else errno=EINVAL  + return -1), with
 * random  characters such that the filename described by `template_' will not
 * already  exists. Then, create a new file  with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The #  of trailing  characters to-be  ignored
 *                    after the required 6 trailing 'X'-characters. */
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED ATTR_INOUT(1) fd_t
NOTHROW_RPC(LIBCCALL libc_mkstemps)(char *template_,
                                    __STDC_INT_AS_SIZE_T suffixlen) {
	return libc_mkostemps(template_, suffixlen, 0);
}
INTERN ATTR_SECTION(".text.crt.utility.locale") ATTR_PURE WUNUSED ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_rpmatch)(char const *response) {
	char c = response[0];
	if (c == 'n' || c == 'N')
		return 0;
	if (c == 'y' || c == 'Y')
		return 1;
	return -1;
}
#include <asm/os/oflags.h>
#if !__O_LARGEFILE
DEFINE_INTERN_ALIAS_P(libc_mkstemps64,libc_mkstemps,WUNUSED ATTR_INOUT(1),fd_t,NOTHROW_RPC,LIBCCALL,(char *template_, __STDC_INT_AS_SIZE_T suffixlen),(template_,suffixlen));
#else /* !__O_LARGEFILE */
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all  'X'-characters before the  call (else errno=EINVAL  + return -1), with
 * random  characters such that the filename described by `template_' will not
 * already  exists. Then, create a new file  with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The #  of trailing  characters to-be  ignored
 *                    after the required 6 trailing 'X'-characters. */
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED ATTR_INOUT(1) fd_t
NOTHROW_RPC(LIBCCALL libc_mkstemps64)(char *template_,
                                      __STDC_INT_AS_SIZE_T suffixlen) {
	return libc_mkostemps64(template_, suffixlen, 0);
}
#endif /* __O_LARGEFILE */
#include "../libc/tls-globals.h"
/* >> l64a(3), a64l(3)
 * Convert between `long' and base-64 encoded integer strings. */
INTERN ATTR_SECTION(".text.crt.bsd") ATTR_RETNONNULL WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_l64a)(long n) {
	/* l64a_r() encodes 6 bytes from `n' into 1 character, followed
	 * by 1 trailing NUL-character. So we can can calculate the max
	 * required buffer size here, based on `sizeof(long)'! */
	char (*const _p_l64a_buf)[(((sizeof(long) * __CHAR_BIT__) + 5) / 6) + 1] = &libc_get_tlsglobals()->ltg_l64a_buf;
#define l64a_buf (*_p_l64a_buf)
	libc_l64a_r(n, l64a_buf, sizeof(l64a_buf));
	return l64a_buf;
}
#undef l64a_buf
/* >> l64a(3), a64l(3)
 * Convert between `long' and base-64 encoded integer strings. */
INTERN ATTR_SECTION(".text.crt.bsd") ATTR_PURE WUNUSED ATTR_IN(1) long
NOTHROW_NCX(LIBCCALL libc_a64l)(char const *s) {
	unsigned long digit, result = 0;
	shift_t shift = 0;
	for (;; ++s) {
		char ch = *s;
		if ((unsigned char)ch <= '\0') {
			break;
		} else if ((unsigned char)ch <= '/') {
			digit = (unsigned long)(unsigned int)(ch - '.' + 0);
		} else if ((unsigned char)ch <= '9') {
			digit = (unsigned long)(unsigned int)(ch - '0' + 2);
		} else if ((unsigned char)ch <= 'Z') {
			digit = (unsigned long)(unsigned int)(ch - 'A' + 12);
		} else {
			digit = (unsigned long)(unsigned int)(ch - 'a' + 38);
		}
		digit <<= shift;
		result |= digit;
		shift += 6;
	}
	return result;
}
#include <asm/os/fcntl.h>
#include <asm/os/limits.h>
/* >> realpath(3)
 * Load the filesystem location of a given file handle.
 * This  function behaves similar to `readlink()', but will also function for
 * non-symlink paths, as well as always return an absolute (unambiguous) path
 * @param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
 *                   path, or NULL  to automatically `malloc()'ate  and return  a
 *                   buffer of sufficient size. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.property") WUNUSED ATTR_IN(1) char *
NOTHROW_RPC(LIBDCALL libd_realpath)(char const *filename,
                                    char *resolved) {



	return libd_frealpathat(__AT_FDCWD, filename, resolved, resolved ? 256 : 0, 0);

}
#include <asm/os/fcntl.h>
#include <asm/os/limits.h>
/* >> realpath(3)
 * Load the filesystem location of a given file handle.
 * This  function behaves similar to `readlink()', but will also function for
 * non-symlink paths, as well as always return an absolute (unambiguous) path
 * @param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
 *                   path, or NULL  to automatically `malloc()'ate  and return  a
 *                   buffer of sufficient size. */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED ATTR_IN(1) char *
NOTHROW_RPC(LIBCCALL libc_realpath)(char const *filename,
                                    char *resolved) {



	return libc_frealpathat(__AT_FDCWD, filename, resolved, resolved ? 256 : 0, 0);

}
/* >> frealpath(3)
 * Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.property") WUNUSED ATTR_FDARG(1) ATTR_OUT_OPT(2) char *
NOTHROW_RPC(LIBDCALL libd_frealpath)(fd_t fd,
                                     char *resolved,
                                     size_t buflen) {
	return libd_frealpath4(fd, resolved, buflen, 0);
}
/* >> frealpath(3)
 * Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED ATTR_FDARG(1) ATTR_OUT_OPT(2) char *
NOTHROW_RPC(LIBCCALL libc_frealpath)(fd_t fd,
                                     char *resolved,
                                     size_t buflen) {
	return libc_frealpath4(fd, resolved, buflen, 0);
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
INTERN ATTR_SECTION(".text.crt.fs.utility") ATTR_RETNONNULL ATTR_INOUT(1) char *
NOTHROW_NCX(LIBCCALL libc_mktemp)(char *template_) {
	if (libc_system_mktemp(2, template_, 0, 0))
		*template_ = 0;
	return template_;
}
#include "../libc/tls-globals.h"
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") WUNUSED ATTR_OUT(3) ATTR_OUT(4) char *
NOTHROW_NCX(LIBCCALL libc_ecvt)(double val,
                                int ndigit,
                                int *__restrict decptr,
                                int *__restrict sign) {
	char (*const _p_qcvt_buf)[32] = &libc_get_tlsglobals()->ltg_qcvt_buf;
#define qcvt_buf (*_p_qcvt_buf)
	if (libc_ecvt_r(val, ndigit, decptr, sign, qcvt_buf, sizeof(qcvt_buf)))
		return NULL;
	return qcvt_buf;
}
#undef qcvt_buf
#include "../libc/tls-globals.h"
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") WUNUSED ATTR_OUT(3) ATTR_OUT(4) char *
NOTHROW_NCX(LIBCCALL libc_fcvt)(double val,
                                int ndigit,
                                int *__restrict decptr,
                                int *__restrict sign) {
	char (*const _p_qcvt_buf)[32] = &libc_get_tlsglobals()->ltg_qcvt_buf;
#define qcvt_buf (*_p_qcvt_buf)
	if (libc_fcvt_r(val, ndigit, decptr, sign, qcvt_buf, sizeof(qcvt_buf)))
		return NULL;
	return qcvt_buf;
}
#undef qcvt_buf
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
#undef suboptarg
INTDEF char *libc_suboptarg;
INTERN ATTR_SECTION(".bss.crt.application.getopt") char *libc_suboptarg = NULL;
DEFINE_PUBLIC_ALIAS(suboptarg, libc_suboptarg);
#define suboptarg GET_NOREL_GLOBAL(suboptarg)
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
#include <libc/template/suboptarg.h>
/* >> getsubopt(3)
 * Parse a sequence of sub-options from `*optionp'.
 *
 * Sub-options look like this "rw,user=root drive=/dev/sda1"
 * Options may be separated by ',', ' ', or '\t' characters.
 * Both leading and trailing such characters are skipped.
 *
 * Note  that although KOS's implementation of this function only ever writes
 * to `suboptarg(3)' (meaning that it is technically thread-safe, so-long  as
 * no other piece of code ever reads from `suboptarg'), other implementations
 * _will_ in fact  perform reads  from `suboptarg', meaning  that a  portable
 * application must treat this function as thread-unsafe.
 *
 * Note that `suboptarg(3)' gets declared by <unistd.h> under `_NETBSD_SOURCE'
 *
 * @param: optionp: Pointer to sub-options that  have yet to be  parsed.
 *                  Note that the pointed-to string is modified in-place
 *                  in order to produce NUL-terminated strings.
 * @param: tokens:  A NULL-terminated  array of  recognized option  names.
 *                  The function searches this array for options specified
 *                  in `*optionp' (in the example above: "rw", "user"  and
 *                  "drive"), and returns the index of matched string,  or
 *                  `-1' with `*valuep'  set to the  whole sub-opt  option
 *                  string (e.g. "user=root") when  the option key is  not
 *                  part of this array.
 * @param: valuep:  Pointer to the value-portion of the matched sub-option.
 *                  When the sub-option name is not found in `tokens', this
 *                  pointer is set to  the entire sub-option string.  Else,
 *                  it is set to NULL when the end of `optionp' is reached,
 *                  or when the matched token doesn't have a value-portion.
 * @return: * : The return'th string from `tokens'  was matched. `*valuep' is  set
 *              to `NULL' when no `=' appeared in the sub-option, or to the string
 *              following `='  if it  was present  (e.g. "root"  in  "user=root").
 *              Additionally, the global variable `suboptarg'  is set to the  name
 *              of matched option (e.g. "user" in "root=user")
 * @return: -1: [*valuep == NULL] End of `optionp' has been reached (`suboptarg' is set to `NULL')
 * @return: -1: [*valuep != NULL] Unknown sub-option encountered (`*valuep' and
 *                                `suboptarg' are the whole sub-option  string) */
INTERN ATTR_SECTION(".text.crt.application.getopt") WUNUSED ATTR_IN(2) ATTR_INOUT_OPT(1) ATTR_OUT(3) int
NOTHROW_NCX(LIBCCALL libc_getsubopt)(char **__restrict optionp,
                                     char *const *__restrict tokens,
                                     char **__restrict valuep) {
	unsigned int i;
	char *option, *nextopt, *eq;
	*valuep = NULL;
	if unlikely(!optionp)
		goto err_noopt;
	option = *optionp;
	if unlikely(!option)
		goto err_noopt;

	/* Skip leading whitespace and commas */
#define GETSUBOPT_ISSPACE(ch) (libc_strchr(", \t", ch) != NULL)
	while (GETSUBOPT_ISSPACE(*option))
		++option;
	if unlikely(!*option)
		goto err_noopt;

	/* Save the starting pointer to the sub-option. */
#ifdef __LOCAL_suboptarg
	__LOCAL_suboptarg = option;
#endif /* __LOCAL_suboptarg */

	/* Find the next option */
	nextopt = option;
	while (*nextopt != '\0' && !GETSUBOPT_ISSPACE(*nextopt))
		++nextopt;
	if (*nextopt != '\0')
		*nextopt++ = '\0';
	while (GETSUBOPT_ISSPACE(*nextopt))
		++nextopt;
	*optionp = nextopt;
#undef GETSUBOPT_ISSPACE

	/* Check if this option has a value-part */
	eq = libc_strchr(option, '=');
	if (eq != NULL) {
		*eq++   = '\0';
		*valuep = eq;
	}

	/* Find the referenced token. */
	for (i = 0; tokens[i]; ++i) {
		if (libc_strcmp(tokens[i], option) == 0)
			return (int)i;
	}

	/* Not found (return the whole `name[=value]' string) */
	*valuep = option;
	/* Restore the '=' since we want to return the whole string */
	if (eq != NULL)
		eq[-1] = '=';
	return -1;
err_noopt:
#ifdef __LOCAL_suboptarg
	__LOCAL_suboptarg = NULL;
#endif /* __LOCAL_suboptarg */
	return -1;
}
/* >> mkstemp(3), mkstemp64(3)
 * Replace the last 6 characters of  `template_', which must be filled  with
 * all  'X'-characters  before the  call  (else errno=EINVAL  +  return -1),
 * with random characters  such that the  filename described by  `template_'
 * will not already exists. Then, create a new file with `O_RDWR' and return
 * the file descriptor of that file. */
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED ATTR_INOUT(1) fd_t
NOTHROW_RPC(LIBCCALL libc_mkstemp)(char *template_) {
	return libc_mkstemps(template_, 0);
}
#include <asm/os/oflags.h>
#if !__O_LARGEFILE
DEFINE_INTERN_ALIAS_P(libc_mkstemp64,libc_mkstemp,WUNUSED ATTR_INOUT(1),fd_t,NOTHROW_RPC,LIBCCALL,(char *template_),(template_));
#else /* !__O_LARGEFILE */
/* >> mkstemp(3), mkstemp64(3)
 * Replace the last 6 characters of  `template_', which must be filled  with
 * all  'X'-characters  before the  call  (else errno=EINVAL  +  return -1),
 * with random characters  such that the  filename described by  `template_'
 * will not already exists. Then, create a new file with `O_RDWR' and return
 * the file descriptor of that file. */
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED ATTR_INOUT(1) fd_t
NOTHROW_RPC(LIBCCALL libc_mkstemp64)(char *template_) {
	return libc_mkstemps64(template_, 0);
}
#endif /* __O_LARGEFILE */
/* >> mkdtemp(3)
 * Replace the last 6 characters of `template_', which must be filled with
 * all  'X'-characters before  the call  (else errno=EINVAL  + return -1),
 * with random characters such that the pathname described by  `template_'
 * will not already exists. Then, create a new directory with `mode=0700',
 * and re-return `template_' to indicate success.
 * On error, `NULL' will be returned, and the contents of `template_' are undefined. */
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED ATTR_INOUT(1) char *
NOTHROW_RPC(LIBCCALL libc_mkdtemp)(char *template_) {
	if (libc_system_mktemp(1, template_, 0, 0) )
		template_ = NULL;
	return template_;
}
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_FDARG(1) int
NOTHROW_NCX(LIBCCALL libc_unlockpt)(fd_t fd) {
	int action = 0;
	if (libc_ioctl(fd, __TIOCSPTLCK, &action))
		return -1;
	return 0;
}
#include "../libc/tls-globals.h"
/* >> ptsname(3)
 * Returns the name of the PTY slave (Pseudo TTY slave)
 * associated   with   the   master   descriptor   `fd' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.io.tty") WUNUSED ATTR_FDARG(1) char *
NOTHROW_NCX(LIBDCALL libd_ptsname)(fd_t fd) {

	/* Buffer is typed as `void *' so it can be re-used for `wptsname(3)' */
	void **const _p_ptsname_buf = &libc_get_tlsglobals()->ltg_ptsname_buf;
#define ptsname_buf (*_p_ptsname_buf)
	errno_t error;

	size_t bufsize = libc_malloc_usable_size(ptsname_buf) / sizeof(char);



	if (bufsize < 64) {
		void *newbuf;
		bufsize = 64;
		newbuf  = libc_realloc(ptsname_buf, bufsize * sizeof(char));
		if unlikely(!newbuf)
			goto err;
		ptsname_buf = newbuf;
	}

again:

	error = libd_ptsname_r(fd, (char *)ptsname_buf, bufsize);
	if likely(error == 0) {
		/* Trim unused memory (if a certain threshold is exceeded) */
		size_t retlen = libc_strlen((char *)ptsname_buf) + 1;
		if (retlen < 64)
			retlen = 64; /* Retain minimal buffer size */
		if likely((retlen + 32) < bufsize) {
			void *retbuf = libc_realloc(ptsname_buf, retlen * sizeof(char));
			if likely(retbuf)
				ptsname_buf = retbuf;
		}
		return (char *)ptsname_buf;
	}

	if (error == ERANGE && bufsize < 1024) {
		void *newbuf;
		bufsize *= 2;
		newbuf = libc_realloc(ptsname_buf, bufsize * sizeof(char));
		if unlikely(!newbuf)
			goto err;
		ptsname_buf = newbuf;
		goto again;
	}


	libc_free(ptsname_buf);
	ptsname_buf = NULL;

err:
	return NULL;






}
#undef ptsname_buf
#include "../libc/tls-globals.h"
/* >> ptsname(3)
 * Returns the name of the PTY slave (Pseudo TTY slave)
 * associated   with   the   master   descriptor   `fd' */
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED ATTR_FDARG(1) char *
NOTHROW_NCX(LIBCCALL libc_ptsname)(fd_t fd) {

	/* Buffer is typed as `void *' so it can be re-used for `wptsname(3)' */
	void **const _p_ptsname_buf = &libc_get_tlsglobals()->ltg_ptsname_buf;
#define ptsname_buf (*_p_ptsname_buf)
	errno_t error;

	size_t bufsize = libc_malloc_usable_size(ptsname_buf) / sizeof(char);



	if (bufsize < 64) {
		void *newbuf;
		bufsize = 64;
		newbuf  = libc_realloc(ptsname_buf, bufsize * sizeof(char));
		if unlikely(!newbuf)
			goto err;
		ptsname_buf = newbuf;
	}

again:

	error = libc_ptsname_r(fd, (char *)ptsname_buf, bufsize);
	if likely(error == 0) {
		/* Trim unused memory (if a certain threshold is exceeded) */
		size_t retlen = libc_strlen((char *)ptsname_buf) + 1;
		if (retlen < 64)
			retlen = 64; /* Retain minimal buffer size */
		if likely((retlen + 32) < bufsize) {
			void *retbuf = libc_realloc(ptsname_buf, retlen * sizeof(char));
			if likely(retbuf)
				ptsname_buf = retbuf;
		}
		return (char *)ptsname_buf;
	}

	if (error == ERANGE && bufsize < 1024) {
		void *newbuf;
		bufsize *= 2;
		newbuf = libc_realloc(ptsname_buf, bufsize * sizeof(char));
		if unlikely(!newbuf)
			goto err;
		ptsname_buf = newbuf;
		goto again;
	}


	libc_free(ptsname_buf);
	ptsname_buf = NULL;

err:
	return NULL;






}
#undef ptsname_buf
#if __SIZEOF_LONG__ == 4
DEFINE_INTERN_ALIAS_P(libc_strtol_l,libc_strto32_l,ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc_strtol_l,libc_strto64_l,ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_IN(1) ATTR_OUT_OPT(2) long
NOTHROW_NCX(LIBCCALL libc_strtol_l)(char const *__restrict nptr,
                                    char **endptr,
                                    __STDC_INT_AS_UINT_T base,
                                    locale_t locale) {
	(void)locale;
	return libc_strtol(nptr, endptr, base);
}
#endif /* !... */
#if __SIZEOF_LONG__ == 4
DEFINE_INTERN_ALIAS_P(libc_strtoul_l,libc_strtou32_l,ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc_strtoul_l,libc_strtou64_l,ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_IN(1) ATTR_OUT_OPT(2) unsigned long
NOTHROW_NCX(LIBCCALL libc_strtoul_l)(char const *__restrict nptr,
                                     char **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_strtoul(nptr, endptr, base);
}
#endif /* !... */
#if __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc_strtoll_l,libc_strto64_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS_P(libc_strtoll_l,libc_strto32_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_IN(1) ATTR_OUT_OPT(2) __LONGLONG
NOTHROW_NCX(LIBCCALL libc_strtoll_l)(char const *__restrict nptr,
                                     char **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_strtoll(nptr, endptr, base);
}
#endif /* !... */
#if __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc_strtoull_l,libc_strtou64_l,ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS_P(libc_strtoull_l,libc_strtou32_l,ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#else /* ... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_IN(1) ATTR_OUT_OPT(2) __ULONGLONG
NOTHROW_NCX(LIBCCALL libc_strtoull_l)(char const *__restrict nptr,
                                      char **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libc_strtoull(nptr, endptr, base);
}
#endif /* !... */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_IN(1) ATTR_OUT_OPT(2) double
NOTHROW_NCX(LIBCCALL libc_strtod_l)(char const *__restrict nptr,
                                    char **endptr,
                                    locale_t locale) {
	(void)locale;
	return libc_strtod(nptr, endptr);
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_IN(1) ATTR_OUT_OPT(2) float
NOTHROW_NCX(LIBCCALL libc_strtof_l)(char const *__restrict nptr,
                                    char **endptr,
                                    locale_t locale) {
	(void)locale;
	return libc_strtof(nptr, endptr);
}
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS_P(libc_strtold_l,libc_strtod_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGDOUBLE,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, locale_t locale),(nptr,endptr,locale));
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_IN(1) ATTR_OUT_OPT(2) __LONGDOUBLE
NOTHROW_NCX(LIBCCALL libc_strtold_l)(char const *__restrict nptr,
                                     char **endptr,
                                     locale_t locale) {
	(void)locale;
	return libc_strtold(nptr, endptr);
}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#include <libc/template/__libc_enable_secure.h>
/* >> secure_getenv(3)
 * Same as `getenv(3)', but always  return `NULL' if the  caller
 * is running in set-ugid mode (s.a. `__libc_enable_secure(3)'). */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.environ") WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBDCALL libd_secure_getenv)(char const *varname) {
#ifdef __LOCAL___libc_enable_secure
	if (__LOCAL___libc_enable_secure)
		return NULL; /* Unconditionally return `NULL' for setuid() programs */
#endif /* __LOCAL___libc_enable_secure */
	return libd_getenv(varname);
}
#include <libc/template/__libc_enable_secure.h>
/* >> secure_getenv(3)
 * Same as `getenv(3)', but always  return `NULL' if the  caller
 * is running in set-ugid mode (s.a. `__libc_enable_secure(3)'). */
INTERN ATTR_SECTION(".text.crt.fs.environ") WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_secure_getenv)(char const *varname) {
#ifdef __LOCAL___libc_enable_secure
	if (__LOCAL___libc_enable_secure)
		return NULL; /* Unconditionally return `NULL' for setuid() programs */
#endif /* __LOCAL___libc_enable_secure */
	return libc_getenv(varname);
}
#include <asm/os/oflags.h>
#include <asm/crt/stdio.h>
#include <bits/types.h>
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
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED ATTR_INOUT(2) fd_t
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
	if unlikely(xloc < template_ || libc_bcmpc(xloc, "XXXXXX", 6, sizeof(char)) != 0) {

		return libc_seterrno(EINVAL);



	}

	/* Calculate an  initial,  random  seed.
	 * For this purpose, try to make use of:
	 *   - gettimeofday()
	 *   - gettid() or getpid()
	 *   - rand() */
	attempt = 0;
again:
	{
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
		struct timeval64 tv;
		if (libc_gettimeofday64(&tv, NULL) == 0) {
			seed = (uint32_t)(tv.tv_sec) ^
			       (uint32_t)(tv.tv_sec >> 32) ^
			       (uint32_t)(tv.tv_usec << 12); /* The  max value is 0xf423f, so shift
			                                        * that to  become `0xf423f000',  thus
			                                        * filling in the upper bits of `seed' */
		} else
#else /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
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
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
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

	seed ^= libc_gettid();




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


	case 0: {


		flags &= ~O_ACCMODE;

		flags |= O_RDWR;


		flags |= O_CREAT;


		flags |= O_EXCL;

		result = libc_open(template_, flags, 0600);
	}	break;



	case 1:
		result = libc_mkdir(template_, 0700);
		break;



	case 2: {

		struct stat st;
		result = stat(template_, &st);














		if (result < 0) {
			/* File doesn't already exist. */
			result = 0;
		} else {
			/* File does already exist. */




			result = libc_seterrno(EEXIST);



#define NEED_do_try_again
			goto do_try_again;
		}
	}	break;


	default: __builtin_unreachable();
	}
	if (result == -1) {
		/* Only re-attempt if the error was that the file already existed. */

		if (__libc_geterrno() == EEXIST)

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
 * The shell paths attempted by this function are system-dependent, but before any
 * of them are tested, this function will try to use `secure_getenv("SHELL")',  if
 * and only if that variable is defined and starts with a '/'-character. */
INTERN ATTR_SECTION(".text.crt.fs.exec.system") ATTR_IN_OPT(1) int
NOTHROW_RPC(LIBCCALL libc_shexec)(char const *command) {
	static char const arg_sh[] = "sh";
	static char const arg__c[] = "-c";


	/* Try to make use of $SHELL, if defined and an absolute path. */
	char const *environ_shell = libc_secure_getenv("SHELL");
	if (environ_shell && *environ_shell == '/') {
		char const *environ_shell_sh;
		environ_shell_sh = libc_strrchrnul(environ_shell, '/') + 1;
		libc_execl(environ_shell, environ_shell_sh,
		      arg__c, command, (char *)NULL);
	}

	libc_execl("/bin/sh", arg_sh, arg__c, command, (char *)NULL);
	libc_execl("/bin/csh", "csh", arg__c, command, (char *)NULL);
	libc_execl("/bin/bash", "bash", arg__c, command, (char *)NULL);
	return libc_execl("/bin/busybox", arg_sh, arg__c, command, (char *)NULL);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#ifndef LIBC_ARCH_HAVE_ABORTF
__NAMESPACE_LOCAL_BEGIN
struct __vabortmsgf_data {
	char const *vamfd_ptag_str; /* [1..vamfd_ptag_len] Program tag. */
	size_t      vamfd_ptag_len; /* Length of the program tag. */
	bool        vamfd_isatty;   /* True if STDERR_FILENO is a tty. */
	bool        vamfd_at_sol;   /* True if at the start of a line. */
	bool        vamfd_rp_brk;   /* True if a closing ']' must be replaced with ": " on stderr */
};
__LOCAL_LIBC(vabortmsgf_printer) ssize_t
NOTHROW_NCX(FORMATPRINTER_CC abortf_printer)(void *arg, char const *__restrict data, size_t datalen) {
	ssize_t result = (ssize_t)datalen;
	struct __vabortmsgf_data *cookie = (struct __vabortmsgf_data *)arg;
	while (datalen) {
		char tailchar;
		size_t block_len;
		if (cookie->vamfd_at_sol) {
			cookie->vamfd_at_sol = false;
			cookie->vamfd_rp_brk = false;
			(void)libc_syslog_printer((void *)(uintptr_t)__LOG_ERR, "[", 1);
			(void)libc_syslog_printer((void *)(uintptr_t)__LOG_ERR, cookie->vamfd_ptag_str, cookie->vamfd_ptag_len);
			(void)libc_syslog_printer((void *)(uintptr_t)__LOG_ERR, "] ", data[0] == '[' ? 1 : 2);
			if (cookie->vamfd_isatty) {
				(void)libc_writeall(__STDERR_FILENO, cookie->vamfd_ptag_str, cookie->vamfd_ptag_len);
				(void)libc_writeall(__STDERR_FILENO, ": ", 2);
				if (data[0] == '[') {
					cookie->vamfd_rp_brk = true;
					(void)libc_syslog_printer((void *)(uintptr_t)__LOG_ERR, "[", 1);
					++data;
					--datalen;
				}
			}
		}
		for (block_len = 0;;) {
			for (; block_len < datalen; ++block_len) {
				if (libc_strchr("\r\n]", data[block_len]))
					break;
			}
			if (block_len >= datalen)
				break;
			if (data[block_len] != ']')
				break;
			if (cookie->vamfd_rp_brk)
				break;
		}
		tailchar = '\0';
		if (block_len < datalen)
			tailchar = data[block_len];
		if (tailchar == '\n') {
			cookie->vamfd_at_sol = true;
			++block_len;
		}
		(void)libc_syslog_printer((void *)(uintptr_t)__LOG_ERR, data, block_len);
		if (cookie->vamfd_isatty)
			(void)libc_writeall(__STDERR_FILENO, data, block_len);
		data += block_len;
		datalen -= block_len;
		if (tailchar == ']') {
			(void)libc_syslog_printer((void *)(uintptr_t)__LOG_ERR, "]", 1);
			if (cookie->vamfd_isatty)
				(void)libc_writeall(__STDERR_FILENO, ":", 1);
			++data;
			--datalen;
			cookie->vamfd_rp_brk = false;
		} else if (tailchar == '\r') {
			++data;
			--datalen;
			if (datalen && *data == '\n') {
				++data;
				--datalen;
			}
			(void)libc_syslog_printer((void *)(uintptr_t)__LOG_ERR, "\n", 1);
			if (cookie->vamfd_isatty)
				(void)libc_writeall(__STDERR_FILENO, "\n", 1);
			cookie->vamfd_at_sol = true;
		}
	}
	return result;
}
__NAMESPACE_LOCAL_END
/* >> abortf(3)
 * Same  as  `abort(3)',  but prior  to  doing what  `abort(3)'  does, this
 * function will print the specified message `format' to `syslog(LOG_ERR)',
 * as well as `STDERR_FILENO' (if  that file is opened  and a tty). In  the
 * message version that is printed  to `STDERR_FILENO', every line that  is
 * printed  is prefixed by  "{program_invocation_short_name}: ", and in the
 * syslog, every  line  is  prefixed  "[{program_invocation_short_name}] ".
 *
 * Additionally, in the stderr-version, `[foo]'  prefixes at the start  of
 * lines are replaced with `foo: ' (but are kept as-is in syslog messages) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.assert") ATTR_NORETURN ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) void
(VLIBDCALL libd_abortf)(char const *format,
                        ...) {
	struct __NAMESPACE_LOCAL_SYM __vabortmsgf_data data;
	va_list args;
	data.vamfd_ptag_str = program_invocation_name;
	if (data.vamfd_ptag_str == NULL)
		data.vamfd_ptag_str = "?";
	data.vamfd_ptag_len = libc_strlen(data.vamfd_ptag_str);
	data.vamfd_isatty   = libc_isatty(STDERR_FILENO) != 0;
	data.vamfd_at_sol   = true;
	data.vamfd_rp_brk   = false;
	va_start(args, format);
	(void)libc_format_vprintf(&__NAMESPACE_LOCAL_SYM abortf_printer, &data, format, args);
	if (!data.vamfd_at_sol)
		(void)__NAMESPACE_LOCAL_SYM abortf_printer(&data, "\n", 1);
	va_end(args);
	libc_abort();
}
#endif /* !LIBC_ARCH_HAVE_ABORTF */
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#ifndef LIBC_ARCH_HAVE_ABORTF
__NAMESPACE_LOCAL_BEGIN
struct __vabortmsgf_data {
	char const *vamfd_ptag_str; /* [1..vamfd_ptag_len] Program tag. */
	size_t      vamfd_ptag_len; /* Length of the program tag. */
	bool        vamfd_isatty;   /* True if STDERR_FILENO is a tty. */
	bool        vamfd_at_sol;   /* True if at the start of a line. */
	bool        vamfd_rp_brk;   /* True if a closing ']' must be replaced with ": " on stderr */
};
__LOCAL_LIBC(vabortmsgf_printer) ssize_t
NOTHROW_NCX(FORMATPRINTER_CC abortf_printer)(void *arg, char const *__restrict data, size_t datalen) {
	ssize_t result = (ssize_t)datalen;
	struct __vabortmsgf_data *cookie = (struct __vabortmsgf_data *)arg;
	while (datalen) {
		char tailchar;
		size_t block_len;
		if (cookie->vamfd_at_sol) {
			cookie->vamfd_at_sol = false;
			cookie->vamfd_rp_brk = false;
			(void)libc_syslog_printer((void *)(uintptr_t)__LOG_ERR, "[", 1);
			(void)libc_syslog_printer((void *)(uintptr_t)__LOG_ERR, cookie->vamfd_ptag_str, cookie->vamfd_ptag_len);
			(void)libc_syslog_printer((void *)(uintptr_t)__LOG_ERR, "] ", data[0] == '[' ? 1 : 2);
			if (cookie->vamfd_isatty) {
				(void)libc_writeall(__STDERR_FILENO, cookie->vamfd_ptag_str, cookie->vamfd_ptag_len);
				(void)libc_writeall(__STDERR_FILENO, ": ", 2);
				if (data[0] == '[') {
					cookie->vamfd_rp_brk = true;
					(void)libc_syslog_printer((void *)(uintptr_t)__LOG_ERR, "[", 1);
					++data;
					--datalen;
				}
			}
		}
		for (block_len = 0;;) {
			for (; block_len < datalen; ++block_len) {
				if (libc_strchr("\r\n]", data[block_len]))
					break;
			}
			if (block_len >= datalen)
				break;
			if (data[block_len] != ']')
				break;
			if (cookie->vamfd_rp_brk)
				break;
		}
		tailchar = '\0';
		if (block_len < datalen)
			tailchar = data[block_len];
		if (tailchar == '\n') {
			cookie->vamfd_at_sol = true;
			++block_len;
		}
		(void)libc_syslog_printer((void *)(uintptr_t)__LOG_ERR, data, block_len);
		if (cookie->vamfd_isatty)
			(void)libc_writeall(__STDERR_FILENO, data, block_len);
		data += block_len;
		datalen -= block_len;
		if (tailchar == ']') {
			(void)libc_syslog_printer((void *)(uintptr_t)__LOG_ERR, "]", 1);
			if (cookie->vamfd_isatty)
				(void)libc_writeall(__STDERR_FILENO, ":", 1);
			++data;
			--datalen;
			cookie->vamfd_rp_brk = false;
		} else if (tailchar == '\r') {
			++data;
			--datalen;
			if (datalen && *data == '\n') {
				++data;
				--datalen;
			}
			(void)libc_syslog_printer((void *)(uintptr_t)__LOG_ERR, "\n", 1);
			if (cookie->vamfd_isatty)
				(void)libc_writeall(__STDERR_FILENO, "\n", 1);
			cookie->vamfd_at_sol = true;
		}
	}
	return result;
}
__NAMESPACE_LOCAL_END
/* >> abortf(3)
 * Same  as  `abort(3)',  but prior  to  doing what  `abort(3)'  does, this
 * function will print the specified message `format' to `syslog(LOG_ERR)',
 * as well as `STDERR_FILENO' (if  that file is opened  and a tty). In  the
 * message version that is printed  to `STDERR_FILENO', every line that  is
 * printed  is prefixed by  "{program_invocation_short_name}: ", and in the
 * syslog, every  line  is  prefixed  "[{program_invocation_short_name}] ".
 *
 * Additionally, in the stderr-version, `[foo]'  prefixes at the start  of
 * lines are replaced with `foo: ' (but are kept as-is in syslog messages) */
INTERN ATTR_SECTION(".text.crt.assert") ATTR_NORETURN ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) void
(VLIBCCALL libc_abortf)(char const *format,
                        ...) {
	struct __NAMESPACE_LOCAL_SYM __vabortmsgf_data data;
	va_list args;
	data.vamfd_ptag_str = program_invocation_name;
	if (data.vamfd_ptag_str == NULL)
		data.vamfd_ptag_str = "?";
	data.vamfd_ptag_len = libc_strlen(data.vamfd_ptag_str);
	data.vamfd_isatty   = libc_isatty(STDERR_FILENO) != 0;
	data.vamfd_at_sol   = true;
	data.vamfd_rp_brk   = false;
	va_start(args, format);
	(void)libc_format_vprintf(&__NAMESPACE_LOCAL_SYM abortf_printer, &data, format, args);
	if (!data.vamfd_at_sol)
		(void)__NAMESPACE_LOCAL_SYM abortf_printer(&data, "\n", 1);
	va_end(args);
	libc_abort();
}
#endif /* !LIBC_ARCH_HAVE_ABORTF */
#include <libc/template/program_invocation_name.h>
/* >> getexecname(3)
 * Returns the absolute filename of the main executable (s.a. `program_invocation_name') */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.solaris") ATTR_CONST WUNUSED char const *
NOTHROW(LIBDCALL libd_getexecname)(void) {
	return __LOCAL_program_invocation_name;
}
#include <libc/template/program_invocation_name.h>
/* >> getexecname(3)
 * Returns the absolute filename of the main executable (s.a. `program_invocation_name') */
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_CONST WUNUSED char const *
NOTHROW(LIBCCALL libc_getexecname)(void) {
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
PRIVATE ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.solaris") ATTR_FDARG(2) int
(LIBCCALL _dwrap_sTPTP_TDTPTIn__SIZEOF_FD_T___c0c1A1)(struct _dwrap_cookie_struct_sTPTP_TDTPTIn__SIZEOF_FD_T___c0c1A1 *c,
                                                      fd_t fd) THROWS(...) {
	return (*c->walk)(c->arg, fd);
}
#endif /* !__dwrap_sTPTP_TDTPTIn__SIZEOF_FD_T___c0c1A1_defined */
/* >> fdwalk(3)
 * Enumerate all open file descriptors by  invoking `(*walk)(arg, <fd>)' for each of  them
 * If during any of these invocations, `(*walk)(...)' returns non-zero, enumeration stops,
 * and  `fdwalk()' returns with that same value. If `(*walk)(...)' is never called, or all
 * invocations return 0, `fdwalk()' will also return 0. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.solaris") NONNULL((1)) int
NOTHROW_CB_NCX(LIBDCALL libd_fdwalk)(int (LIBDCALL *walk)(void *arg, fd_t fd),
                                     void *arg) {
	struct _dwrap_cookie_struct_sTPTP_TDTPTIn__SIZEOF_FD_T___c0c1A1 libd_fdwalk_cookie;
	libd_fdwalk_cookie.walk = walk;
	libd_fdwalk_cookie.arg  = arg;
	return libc_fdwalk((int (LIBCCALL *)(void *, fd_t))&_dwrap_sTPTP_TDTPTIn__SIZEOF_FD_T___c0c1A1, &libd_fdwalk_cookie);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <asm/os/fcntl.h>
#include <bits/os/dirent.h>
/* >> fdwalk(3)
 * Enumerate all open file descriptors by  invoking `(*walk)(arg, <fd>)' for each of  them
 * If during any of these invocations, `(*walk)(...)' returns non-zero, enumeration stops,
 * and  `fdwalk()' returns with that same value. If `(*walk)(...)' is never called, or all
 * invocations return 0, `fdwalk()' will also return 0. */
INTERN ATTR_SECTION(".text.crt.solaris") NONNULL((1)) int
NOTHROW_CB_NCX(LIBCCALL libc_fdwalk)(int (LIBCCALL *walk)(void *arg, fd_t fd),
                                     void *arg) {
	int result = 0;

	errno_t saved_err;


	fd_t fd = 0;
	for (;;) {

		saved_err = __libc_geterrno();

		/* fcntl(F_NEXT) returns the next valid  (i.e.
		 * currently open) fd that is >= the given fd. */
		fd = libc_fcntl(fd, __F_NEXT);
		if (fd < 0) {

			(void)libc_seterrno(saved_err);

			break;
		}
		result = (*walk)(arg, fd);
		if (result != 0)
			break;
		if (__hybrid_overflow_sadd(fd, 1, &fd))
			break;
	}





















	return result;
}
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_RETNONNULL WUNUSED ATTR_OUT(2) char *
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
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_RETNONNULL WUNUSED ATTR_OUT(2) char *
NOTHROW_NCX(LIBCCALL libc_ulltostr)(__ULONGLONG value,
                                    char *buf) {
	do {
		*--buf = itoa_decimal(value % 10);
	} while ((value /= 10) != 0);
	return buf;
}
#include <asm/crt/malloc.h>
/* >> reallocf(3)
 * Same as `realloc(3)',  but `mallptr'  is always freed  when `NULL'  is
 * returned (both error and the implementation-specific `realloc(ptr, 0)'
 * case; s.a. __REALLOC_ZERO_IS_NONNULL) */
INTERN ATTR_SECTION(".text.crt.heap.rare_helpers") ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBCCALL libc_reallocf)(void *mallptr,
                                    size_t num_bytes) {
	void *result;
	result = libc_realloc(mallptr, num_bytes);

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

	return result;
}
/* >> recallocarray(3)
 * Same  as  `recallocv(mallptr, new_elem_count, elem_size)', but  also ensure  that when
 * `mallptr != NULL', memory pointed to by the old `mallptr...+=old_elem_count*elem_size'
 * is explicitly freed to zero (s.a. `freezero()') when reallocation must move the memory
 * block */
INTERN ATTR_SECTION(".text.crt.heap.rare_helpers") ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((3, 4)) void *
NOTHROW_NCX(LIBCCALL libc_recallocarray)(void *mallptr,
                                         size_t old_elem_count,
                                         size_t new_elem_count,
                                         size_t elem_size) {
	if (mallptr != NULL && old_elem_count != 0) {
		void *result;
		size_t oldusable, newneeded;
		oldusable = libc_malloc_usable_size(mallptr);
		newneeded = new_elem_count * elem_size;
		if (oldusable >= newneeded) {
			if (old_elem_count > new_elem_count) {
				size_t zero_bytes;
				zero_bytes = (old_elem_count - new_elem_count) * elem_size;
				explicit_bzero((byte_t *)mallptr + newneeded, zero_bytes);
			}
			return mallptr;
		}
		/* Allocate a new block so we can ensure that  an
		 * existing block gets freezero()'ed in all cases */
		result = libc_calloc(new_elem_count, elem_size);
		if (result) {
			if (oldusable > newneeded)
				oldusable = newneeded;
			libc_memcpy(result, mallptr, oldusable);
			libc_freezero(mallptr, old_elem_count * elem_size);
		}
		return result;
	}
	return libc_recallocv(mallptr, new_elem_count, elem_size);
}
/* >> freezero(3)
 * Same as  `free(mallptr)', but  also ensure  that the  memory  region
 * described by `mallptr...+=num_bytes' is explicitly freed to zero, or
 * immediately returned  to the  OS, rather  than being  left in  cache
 * while still containing its previous contents. */
INTERN ATTR_SECTION(".text.crt.heap.rare_helpers") void
NOTHROW_NCX(LIBCCALL libc_freezero)(void *mallptr,
                                    size_t num_bytes) {
	if likely(mallptr) {
		explicit_bzero(mallptr, num_bytes);
		libc_free(mallptr);
	}
}
/* >> daemon(3), daemonfd(3) */
INTERN ATTR_SECTION(".text.crt.system.utility") int
NOTHROW_RPC(LIBCCALL libc_daemonfd)(fd_t chdirfd,
                                    fd_t nullfd) {
	int error = libc_daemon_setup();
	if likely(error == 0) {
		if (chdirfd != -1)
			(void)libc_fchdir(chdirfd);
		if (nullfd != -1) {
			fd_t i;
			for (i = 0; i < 3; ++i) {
				if (nullfd != i)
					(void)libc_dup2(nullfd, i);
			}
		}
	}
	return error;
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
NOTHROW(LIBCCALL libc_getprogname)(void) {
	return program_invocation_short_name;
}
/* >> getprogname(3), setprogname(3) */
INTERN ATTR_SECTION(".text.crt.bsd") void
NOTHROW_NCX(LIBCCALL libc_setprogname)(char const *name) {
	__LOCAL_program_invocation_short_name_p = (char *)name;
}
INTERN ATTR_SECTION(".text.crt.bsd") ATTR_INOUT_OPT(1) NONNULL((4)) int
NOTHROW_CB_NCX(LIBCCALL libc_heapsort)(void *pbase,
                                       size_t item_count,
                                       size_t item_size,
                                       int (LIBCCALL *compar)(void const *a, void const *b)) {
	/* TODO: Actually do heap-sort! */
	libc_qsort(pbase, item_count, item_size, compar);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.bsd") ATTR_INOUT_OPT(1) NONNULL((4)) int
NOTHROW_CB_NCX(LIBCCALL libc_mergesort)(void *pbase,
                                        size_t item_count,
                                        size_t item_size,
                                        int (LIBCCALL *compar)(void const *a, void const *b)) {
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
INTERN ATTR_SECTION(".text.crt.bsd") WUNUSED ATTR_IN(1) ATTR_OUT(4) __LONGLONG
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

		if (error == ERANGE) {
			*p_errstr = "too large";
			if (result == lo)
				*p_errstr = "too small";
		}

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
PRIVATE ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility.stdlib") int
(LIBCCALL _dwrap_sTPTP_TDTPTPTP_c0A0A1c1)(void const *a,
                                          void const *b,
                                          struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0A0A1c1 *c) THROWS(...) {
	return (*c->compar)(a, b, c->arg);
}
#endif /* !__dwrap_sTPTP_TDTPTPTP_c0A0A1c1_defined */
/* >> qsort_r(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility.stdlib") ATTR_INOUT_OPT(1) NONNULL((4)) void
NOTHROW_CB_NCX(LIBDCALL libd_qsort_r)(void *pbase,
                                      size_t item_count,
                                      size_t item_size,
                                      int (LIBDCALL *compar)(void const *a, void const *b, void *arg),
                                      void *arg) {
	struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0A0A1c1 libd_qsort_r_cookie;
	libd_qsort_r_cookie.compar = compar;
	libd_qsort_r_cookie.arg    = arg;
	libc_qsort_r(pbase, item_count, item_size, (int (LIBCCALL *)(void const *, void const *, void *))&_dwrap_sTPTP_TDTPTPTP_c0A0A1c1, &libd_qsort_r_cookie);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> qsort_r(3) */
INTERN ATTR_SECTION(".text.crt.utility.stdlib") ATTR_INOUT_OPT(1) NONNULL((4)) void
NOTHROW_CB_NCX(LIBCCALL libc_qsort_r)(void *pbase,
                                      size_t item_count,
                                      size_t item_size,
                                      int (LIBCCALL *compar)(void const *a, void const *b, void *arg),
                                      void *arg) {
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
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED ATTR_INOUT(1) fd_t
NOTHROW_NCX(LIBCCALL libc_mkostemp)(char *template_,
                                    oflag_t flags) {
	return libc_mkostemps(template_, 0, flags);
}
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED ATTR_INOUT(1) fd_t
NOTHROW_NCX(LIBCCALL libc_mkostemps)(char *template_,
                                     __STDC_INT_AS_SIZE_T suffixlen,
                                     oflag_t flags) {
	return libc_system_mktemp(0, template_, suffixlen, flags);
}
#include <asm/os/oflags.h>
#if !__O_LARGEFILE
DEFINE_INTERN_ALIAS_P(libc_mkostemp64,libc_mkostemp,WUNUSED ATTR_INOUT(1),fd_t,NOTHROW_NCX,LIBCCALL,(char *template_, oflag_t flags),(template_,flags));
#else /* !__O_LARGEFILE */
/* >> mkostemp(3), mkostemp64(3)
 * Replace  the  last 6  characters of  `template_' (which  are followed  by exactly
 * `suffixlen'  more  characters that  are left  alone), which  must be  filled with
 * all  'X'-characters  before  the  call  (else  errno=EINVAL  +  return  -1), with
 * random  characters  such  that the  filename  described by  `template_'  will not
 * already exists. Then, create a new file with `O_RDWR | flags' and return the file
 * descriptor of that file.
 * @param: flags: Additional  flags  to pass  to `open(2)',
 *                but `O_ACCMODE' is always set to `O_RDWR' */
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED ATTR_INOUT(1) fd_t
NOTHROW_NCX(LIBCCALL libc_mkostemp64)(char *template_,
                                      oflag_t flags) {
	return libc_mkostemps64(template_, 0, flags);
}
#endif /* __O_LARGEFILE */
#include <asm/os/oflags.h>
#if !__O_LARGEFILE
DEFINE_INTERN_ALIAS_P(libc_mkostemps64,libc_mkostemps,WUNUSED ATTR_INOUT(1),fd_t,NOTHROW_NCX,LIBCCALL,(char *template_, __STDC_INT_AS_SIZE_T suffixlen, oflag_t flags),(template_,suffixlen,flags));
#else /* !__O_LARGEFILE */
INTERN ATTR_SECTION(".text.crt.fs.utility") WUNUSED ATTR_INOUT(1) fd_t
NOTHROW_NCX(LIBCCALL libc_mkostemps64)(char *template_,
                                       __STDC_INT_AS_SIZE_T suffixlen,
                                       oflag_t flags) {

	return libc_system_mktemp(0, template_, suffixlen, flags | O_LARGEFILE);



}
#endif /* __O_LARGEFILE */
#include "../libc/tls-globals.h"
/* >> devname(3), devname_r(3) */
INTERN ATTR_SECTION(".text.crt.bsd") char *
NOTHROW_NCX(LIBCCALL libc_devname)(dev_t dev,
                                   mode_t type) {

	/* Buffer is typed as `void *' so it can be re-used for `wdevname(3)' */
	void **const _p_devname_buf = &libc_get_tlsglobals()->ltg_devname_buf;
#define devname_buf (*_p_devname_buf)
	errno_t error;

	size_t bufsize = libc_malloc_usable_size(devname_buf) / sizeof(char);



	if (bufsize < 64) {
		void *newbuf;
		bufsize = 64;
		newbuf  = libc_realloc(devname_buf, bufsize * sizeof(char));
		if unlikely(!newbuf)
			goto err;
		devname_buf = newbuf;
	}

again:

	error = libc_devname_r(dev, type, (char *)devname_buf, bufsize);
	if likely(error == 0) {
		/* Trim unused memory (if a certain threshold is exceeded) */
		size_t retlen = libc_strlen((char *)devname_buf) + 1;
		if (retlen < 64)
			retlen = 64; /* Retain minimal buffer size */
		if likely((retlen + 32) < bufsize) {
			void *retbuf = libc_realloc(devname_buf, retlen * sizeof(char));
			if likely(retbuf)
				devname_buf = retbuf;
		}
		return (char *)devname_buf;
	}

	if (error == ERANGE && bufsize < 1024) {
		void *newbuf;
		bufsize *= 2;
		newbuf = libc_realloc(devname_buf, bufsize * sizeof(char));
		if unlikely(!newbuf)
			goto err;
		devname_buf = newbuf;
		goto again;
	}


	libc_free(devname_buf);
	devname_buf = NULL;

err:
	return NULL;






}
#undef devname_buf
#include <linux/prctl.h>
INTERN ATTR_SECTION(".text.crt.bsd") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) void
NOTHROW_NCX(LIBCCALL libc_vsetproctitle)(char const *format,
                                         va_list args) {
	/* Load+fill a buffer for the fully qualified program name. */
#ifdef __TASK_COMM_LEN
	char namebuf[__TASK_COMM_LEN];
	libc_vsnprintf(namebuf, __TASK_COMM_LEN - 1, format, args);
	namebuf[__TASK_COMM_LEN - 1] = '\0';
#else /* __TASK_COMM_LEN */
	char *namebuf = libc_vstrdupf(format, args);
	if unlikely(!namebuf)
		return;
#endif /* !__TASK_COMM_LEN */

	/* Tell the kernel about our new program name. */
#ifdef PR_SET_NAME
	libc_prctl(PR_SET_NAME, namebuf);
#else /* PR_SET_NAME */
	libc_pthread_setname_np(libc_pthread_self(), namebuf);
#endif /* !PR_SET_NAME */

	/* Free the name buffer if it was allocated dynamically. */
#ifndef __TASK_COMM_LEN
	libc_free(namebuf);
#endif /* !__TASK_COMM_LEN */
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> setproctitle(3)
 * Set the program comm name. S.a.:
 *  - pthread_setname_np(3)
 *  - prctl(PR_SET_NAME)
 *  - "/proc/self/comm" */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.bsd") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) void
NOTHROW_NCX(VLIBDCALL libd_setproctitle)(char const *format,
                                         ...) {
	va_list args;
	va_start(args, format);
	libc_vsetproctitle(format, args);
	va_end(args);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> setproctitle(3)
 * Set the program comm name. S.a.:
 *  - pthread_setname_np(3)
 *  - prctl(PR_SET_NAME)
 *  - "/proc/self/comm" */
INTERN ATTR_SECTION(".text.crt.bsd") ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) void
NOTHROW_NCX(VLIBCCALL libc_setproctitle)(char const *format,
                                         ...) {
	va_list args;
	va_start(args, format);
	libc_vsetproctitle(format, args);
	va_end(args);
}
/* >> reallocarr(3)
 * Badly designed  alternative to  `reallocarray(3)'. Note  that
 * the given `ptr_p' argument is really typed as `void **ptr_p',
 * but for API compatibility  is defined as `void *ptr_p'.  This
 * function simply does:
 * >> *(void **)ptr_p = reallocarray(*(void **)ptr_p, elem_count, elem_size);
 * Though `*(void **)ptr_p' is only updated on success.
 * @return: 0 : Success (`*(void **)ptr_p' was updated)
 * @return: -1: Error (s.a. `errno'; `*(void **)ptr_p' is unchanged) */
INTERN ATTR_SECTION(".text.crt.heap.rare_helpers") WUNUSED int
NOTHROW_NCX(LIBCCALL libc_reallocarr)(void *ptr_p,
                                      size_t elem_count,
                                      size_t elem_size) {
	void **p_ptr = (void **)ptr_p;
	void *result;
	result = libc_reallocarray(*p_ptr, elem_count, elem_size);
	if unlikely(!result)
		return -1;
	*p_ptr = result;
	return 0;
}
#include <asm/os/stdlib.h>
/* >> strsuftoll(3)
 * Same as `strsuftollx(3)', but if an error happens, make
 * use of `errx(3)' to terminate the program, rather  than
 * return to the caller. */
INTERN ATTR_SECTION(".text.crt.bsd") WUNUSED ATTR_IN(1) ATTR_IN(2) __LONGLONG
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
INTERN ATTR_SECTION(".text.crt.bsd") WUNUSED ATTR_IN(1) ATTR_IN(2) __LONGLONG
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
NOTHROW(LIBCCALL libc___p__pgmptr)(void) {
	return &__LOCAL_program_invocation_name_p;
}
#include <libc/template/program_invocation_name.h>
INTERN ATTR_SECTION(".text.crt.dos.application.init") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc__get_pgmptr)(char **pvalue) {
	*pvalue = __LOCAL_program_invocation_name;
	return EOK;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.application.init") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBDCALL libd__get_wpgmptr)(char16_t **pvalue) {
	*pvalue = *libd___p__wpgmptr();
	return EOK;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.application.init") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBKCALL libc__get_wpgmptr)(char32_t **pvalue) {
	*pvalue = *libc___p__wpgmptr();
	return EOK;
}
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS_P(libc__abs64,libc_abs,ATTR_CONST WUNUSED,__INT64_TYPE__,NOTHROW,LIBCCALL,(__INT64_TYPE__ x),(x));
#elif __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc__abs64,libc_llabs,ATTR_CONST WUNUSED,__INT64_TYPE__,NOTHROW,LIBCCALL,(__INT64_TYPE__ x),(x));
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED __INT64_TYPE__
NOTHROW(LIBCCALL libc__abs64)(__INT64_TYPE__ x) {
	return x < 0 ? -x : x;
}
#endif /* !... */
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.convert") ATTR_PURE WUNUSED ATTR_IN(1) double
NOTHROW_NCX(LIBCCALL libc__atof_l)(char const *__restrict nptr,
                                   locale_t locale) {
	return libc_strtod_l(nptr, NULL, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.convert") ATTR_PURE WUNUSED ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc__atoi_l)(char const *__restrict nptr,
                                   locale_t locale) {
	return (int)libc_strtol_l(nptr, NULL, 10, locale);
}
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS_P(libc__atol_l,libc__atoi_l,ATTR_PURE WUNUSED ATTR_IN(1),long int,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, locale_t locale),(nptr,locale));
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.convert") ATTR_PURE WUNUSED ATTR_IN(1) long int
NOTHROW_NCX(LIBCCALL libc__atol_l)(char const *__restrict nptr,
                                   locale_t locale) {
	return libc_strtol_l(nptr, NULL, 10, locale);
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_INT__ */
#if __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS_P(libc__atoll_l,libc__atol_l,ATTR_PURE WUNUSED ATTR_IN(1),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, locale_t locale),(nptr,locale));
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS_P(libc__atoll_l,libc__atoi_l,ATTR_PURE WUNUSED ATTR_IN(1),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, locale_t locale),(nptr,locale));
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.convert") ATTR_PURE WUNUSED ATTR_IN(1) __LONGLONG
NOTHROW_NCX(LIBCCALL libc__atoll_l)(char const *__restrict nptr,
                                    locale_t locale) {
	return libc_strtoll_l(nptr, NULL, 10, locale);
}
#endif /* !... */
#include <hybrid/__byteswap.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED u16
NOTHROW(LIBCCALL libc__byteswap_ushort)(u16 val) {
	return __hybrid_bswap16(val);
}
#include <hybrid/__byteswap.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED u32
NOTHROW(LIBCCALL libc__byteswap_ulong)(u32 val) {
	return __hybrid_bswap32(val);
}
#include <hybrid/__byteswap.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED u64
NOTHROW(LIBCCALL libc__byteswap_uint64)(u64 val) {
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
PRIVATE ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility") int
(LIBCCALL _dwrap_sTPTP_TDTPTPTP_c0c1A0A1)(void const *a,
                                          void const *b,
                                          struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0c1A0A1 *c) THROWS(...) {
	return (*c->compar)(c->arg, a, b);
}
#endif /* !__dwrap_sTPTP_TDTPTPTP_c0c1A0A1_defined */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility") WUNUSED ATTR_IN(1) ATTR_IN_OPT(2) NONNULL((5)) void *
NOTHROW_CB_NCX(LIBDCALL libd_bsearch_s)(void const *key,
                                        void const *base,
                                        size_t elem_count,
                                        size_t elem_size,
                                        int (LIBDCALL *compar)(void *arg, void const *a, void const *b),
                                        void *arg) {
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
INTERN ATTR_SECTION(".text.crt.dos.utility") WUNUSED ATTR_IN(1) ATTR_IN_OPT(2) NONNULL((5)) void *
NOTHROW_CB_NCX(LIBCCALL libc_bsearch_s)(void const *key,
                                        void const *base,
                                        size_t elem_count,
                                        size_t elem_size,
                                        int (LIBCCALL *compar)(void *arg, void const *a, void const *b),
                                        void *arg) {
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
PRIVATE ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility") int
(LIBCCALL _dwrap_sTPTP_TDTPTPTP_c0c1A0A1)(void const *a,
                                          void const *b,
                                          struct _dwrap_cookie_struct_sTPTP_TDTPTPTP_c0c1A0A1 *c) THROWS(...) {
	return (*c->compar)(c->arg, a, b);
}
#endif /* !__dwrap_sTPTP_TDTPTPTP_c0c1A0A1_defined */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility") ATTR_INOUT_OPT(1) NONNULL((4)) void
NOTHROW_CB_NCX(LIBDCALL libd_qsort_s)(void *base,
                                      size_t elem_count,
                                      size_t elem_size,
                                      int (LIBDCALL *compar)(void *arg, void const *a, void const *b),
                                      void *arg) {
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
INTERN ATTR_SECTION(".text.crt.dos.utility") ATTR_INOUT_OPT(1) NONNULL((4)) void
NOTHROW_CB_NCX(LIBCCALL libc_qsort_s)(void *base,
                                      size_t elem_count,
                                      size_t elem_size,
                                      int (LIBCCALL *compar)(void *arg, void const *a, void const *b),
                                      void *arg) {
	struct __NAMESPACE_LOCAL_SYM __invoke_compare_helper_s_data data;
	data.__fun = compar;
	data.__arg = arg;
	libc_qsort_r(base, elem_count, elem_size,
	        &__NAMESPACE_LOCAL_SYM __invoke_compare_helper_s,
	        &data);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility") ATTR_IN(4) ATTR_OUT(1) ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBDCALL libd_getenv_s)(size_t *preqsize,
                                    char *buf,
                                    rsize_t bufsize,
                                    char const *varname) {
	size_t reqsize;
	char *name = libd_getenv(varname);
	if (!name) {
		if (preqsize)
			*preqsize = 0;
		return EOK;
	}
	reqsize = (libc_strlen(name) + 1) * sizeof(char);
	if (preqsize)
		*preqsize = reqsize;
	if (reqsize > bufsize) {

		return ERANGE;



	}
	libc_memcpy(buf, name, reqsize);
	return EOK;
}
INTERN ATTR_SECTION(".text.crt.dos.utility") ATTR_IN(4) ATTR_OUT(1) ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBCCALL libc_getenv_s)(size_t *preqsize,
                                    char *buf,
                                    rsize_t bufsize,
                                    char const *varname) {
	size_t reqsize;
	char *name = libc_getenv(varname);
	if (!name) {
		if (preqsize)
			*preqsize = 0;
		return EOK;
	}
	reqsize = (libc_strlen(name) + 1) * sizeof(char);
	if (preqsize)
		*preqsize = reqsize;
	if (reqsize > bufsize) {

		return ERANGE;



	}
	libc_memcpy(buf, name, reqsize);
	return EOK;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility") ATTR_IN(3) ATTR_OUT(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBDCALL libd__dupenv_s)(char **__restrict pbuf,
                                     size_t *pbuflen,
                                     char const *varname) {
	char *name = libd_getenv(varname);
	if (!name) {
		*pbuf    = NULL;
		*pbuflen = 0;
		return 0;
	}
	name = libc_strdup(name);
	if (!name) {

		return 12;



	}
	*pbuf    = name;
	*pbuflen = (libc_strlen(name) + 1) * sizeof(char);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.utility") ATTR_IN(3) ATTR_OUT(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc__dupenv_s)(char **__restrict pbuf,
                                     size_t *pbuflen,
                                     char const *varname) {
	char *name = libc_getenv(varname);
	if (!name) {
		*pbuf    = NULL;
		*pbuflen = 0;
		return EOK;
	}
	name = libc_strdup(name);
	if (!name) {

		return ENOMEM;



	}
	*pbuf    = name;
	*pbuflen = (libc_strlen(name) + 1) * sizeof(char);
	return EOK;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBDCALL libd__itoa_s)(int val,
                                   char *buf,
                                   size_t buflen,
                                   int radix) {
	return libd_errno_kos2dos(libc__itoa_s(val, buf, buflen, radix));
}
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBCCALL libc__itoa_s)(int val,
                                   char *buf,
                                   size_t buflen,
                                   int radix) {

	char *p;
	unsigned int temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;

	if (val < 0) {
		if (!buflen--) {

			return ERANGE;



		}
		*p++ = '-';
		val = -val;
	}

	temp = (unsigned int)val;
	do {
		++p;
	} while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {

		return ERANGE;



	}
	temp = (unsigned int)val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned int)radix];
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS_P(libc__ltoa_s,libc__itoa_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBCCALL,(long val, char *buf, size_t buflen, int radix),(val,buf,buflen,radix));
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBCCALL libc__ltoa_s)(long val,
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

	if (val < 0) {
		if (!buflen--) {

			return ERANGE;



		}
		*p++ = '-';
		val = -val;
	}

	temp = (unsigned long)val;
	do {
		++p;
	} while ((temp /= (unsigned long)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {

		return ERANGE;



	}
	temp = (unsigned long)val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned long)radix];
	} while ((temp /= (unsigned long)radix) != 0);
	return 0;
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_INT__ */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBDCALL libd__ultoa_s)(unsigned long val,
                                    char *buf,
                                    size_t buflen,
                                    int radix) {
	return libd_errno_kos2dos(libc__ultoa_s(val, buf, buflen, radix));
}
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
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













	temp = (unsigned long)val;
	do {
		++p;
	} while ((temp /= (unsigned long)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {

		return ERANGE;



	}
	temp = (unsigned long)val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned long)radix];
	} while ((temp /= (unsigned long)radix) != 0);
	return 0;
}
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS_P(libc__i64toa,libc_itoa,ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(s64 val, char *buf, int radix),(val,buf,radix));
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc__i64toa,libc_ltoa,ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(s64 val, char *buf, int radix),(val,buf,radix));
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_OUT(2) char *
NOTHROW_NCX(LIBCCALL libc__i64toa)(s64 val,
                                   char *buf,
                                   int radix) {
	libc__i64toa_s(val, buf, (size_t)-1, radix);
	return buf;
}
#endif /* !... */
#if __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc__ui64toa,libc_ultoa,ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(u64 val, char *buf, int radix),(val,buf,radix));
#else /* __SIZEOF_LONG__ == 8 */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_OUT(2) char *
NOTHROW_NCX(LIBCCALL libc__ui64toa)(u64 val,
                                    char *buf,
                                    int radix) {
	libc__ui64toa_s(val, buf, (size_t)-1, radix);
	return buf;
}
#endif /* __SIZEOF_LONG__ != 8 */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBDCALL libd__i64toa_s)(s64 val,
                                     char *buf,
                                     size_t buflen,
                                     int radix) {
	return libd_errno_kos2dos(libc__i64toa_s(val, buf, buflen, radix));
}
#if __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc__i64toa_s,libc__ltoa_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBCCALL,(s64 val, char *buf, size_t buflen, int radix),(val,buf,buflen,radix));
#elif __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS_P(libc__i64toa_s,libc__itoa_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBCCALL,(s64 val, char *buf, size_t buflen, int radix),(val,buf,buflen,radix));
#else /* ... */
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBCCALL libc__i64toa_s)(s64 val,
                                     char *buf,
                                     size_t buflen,
                                     int radix) {

	char *p;
	__UINT64_TYPE__ temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;

	if (val < 0) {
		if (!buflen--) {

			return ERANGE;



		}
		*p++ = '-';
		val = -val;
	}

	temp = (__UINT64_TYPE__)val;
	do {
		++p;
	} while ((temp /= (__UINT64_TYPE__)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {

		return ERANGE;



	}
	temp = (__UINT64_TYPE__)val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (__UINT64_TYPE__)radix];
	} while ((temp /= (__UINT64_TYPE__)radix) != 0);
	return 0;
}
#endif /* !... */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBDCALL libd__ui64toa_s)(u64 val,
                                      char *buf,
                                      size_t buflen,
                                      int radix) {
	return libd_errno_kos2dos(libc__ui64toa_s(val, buf, buflen, radix));
}
#if __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc__ui64toa_s,libc__ultoa_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBCCALL,(u64 val, char *buf, size_t buflen, int radix),(val,buf,buflen,radix));
#else /* __SIZEOF_LONG__ == 8 */
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBCCALL libc__ui64toa_s)(u64 val,
                                      char *buf,
                                      size_t buflen,
                                      int radix) {

	char *p;
	__UINT64_TYPE__ temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;













	temp = (__UINT64_TYPE__)val;
	do {
		++p;
	} while ((temp /= (__UINT64_TYPE__)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {

		return ERANGE;



	}
	temp = (__UINT64_TYPE__)val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (__UINT64_TYPE__)radix];
	} while ((temp /= (__UINT64_TYPE__)radix) != 0);
	return 0;
}
#endif /* __SIZEOF_LONG__ != 8 */
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS_P(libc__atoi64,libc_atoi,ATTR_PURE WUNUSED ATTR_IN(1),s64,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr),(nptr));
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc__atoi64,libc_atol,ATTR_PURE WUNUSED ATTR_IN(1),s64,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr),(nptr));
#elif __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc__atoi64,libc_atoll,ATTR_PURE WUNUSED ATTR_IN(1),s64,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr),(nptr));
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_PURE WUNUSED ATTR_IN(1) s64
NOTHROW_NCX(LIBCCALL libc__atoi64)(char const *__restrict nptr) {
	return libc_strto64(nptr, NULL, 10);
}
#endif /* !... */
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS_P(libc__atoi64_l,libc__atoi_l,ATTR_PURE WUNUSED ATTR_IN(1),s64,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, locale_t locale),(nptr,locale));
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc__atoi64_l,libc__atol_l,ATTR_PURE WUNUSED ATTR_IN(1),s64,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, locale_t locale),(nptr,locale));
#elif __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc__atoi64_l,libc__atoll_l,ATTR_PURE WUNUSED ATTR_IN(1),s64,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, locale_t locale),(nptr,locale));
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_PURE WUNUSED ATTR_IN(1) s64
NOTHROW_NCX(LIBCCALL libc__atoi64_l)(char const *__restrict nptr,
                                     locale_t locale) {
	return libc_strto64_l(nptr, NULL, 10, locale);
}
#endif /* !... */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc__mbstrlen)(char const *str) {
	size_t result = 0;
	while (libc_unicode_readutf8((char const **)&str))
		++result;
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbstrnlen)(char const *str,
                                      size_t maxlen) {
	size_t result = 0;
	char const *endptr = str + maxlen;
	while (libc_unicode_readutf8_n((char const **)&str, endptr))
		++result;
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc__mbstrlen_l)(char const *str,
                                       locale_t locale) {
	(void)locale;
	return libc__mbstrlen(str);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbstrnlen_l)(char const *str,
                                        size_t maxlen,
                                        locale_t locale) {
	(void)locale;
	return libc__mbstrnlen(str, maxlen);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc__mblen_l)(char const *str,
                                    size_t maxlen,
                                    locale_t locale) {
	(void)locale;
	return libc_mblen(str, maxlen);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") int
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") size_t
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
#include <bits/types.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") errno_t
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

	if (error == (size_t)-1)
		return 42;

	return 0;
}
#include <bits/types.h>
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

	if (error == (size_t)-1)
		return EILSEQ;

	return EOK;
}
#include <bits/types.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") errno_t
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

	if (error == (size_t)-1)
		return 42;

	return 0;
}
#include <bits/types.h>
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

	if (error == (size_t)-1)
		return EILSEQ;

	return EOK;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.random") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBDCALL libd_rand_s)(unsigned int *__restrict randval) {
	return libd_errno_kos2dos(libc_rand_s(randval));
}
INTERN ATTR_SECTION(".text.crt.dos.random") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_rand_s)(unsigned int *__restrict randval) {
	if (!randval) {

		return EINVAL;



	}
	*randval = libc_rand();
	return EOK;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") int
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
#include <libc/template/MB_CUR_MAX.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_OUTS(2, 3) ATTR_OUT_OPT(1) errno_t
NOTHROW_NCX(LIBDCALL libd_wctomb_s)(int *presult,
                                    char *buf,
                                    rsize_t buflen,
                                    char16_t wc) {
	if (!presult || !buf) {

		return 22;



	}
#ifdef __LOCAL_MB_CUR_MAX
	if (buflen < __LOCAL_MB_CUR_MAX)
#else /* __LOCAL_MB_CUR_MAX */
	if (buflen < 7)
#endif /* !__LOCAL_MB_CUR_MAX */
	{

		return 34;



	}
	*presult = libd_wctomb(buf, wc);
	return 0;
}
#include <libc/template/MB_CUR_MAX.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_OUTS(2, 3) ATTR_OUT_OPT(1) errno_t
NOTHROW_NCX(LIBKCALL libc_wctomb_s)(int *presult,
                                    char *buf,
                                    rsize_t buflen,
                                    char32_t wc) {
	if (!presult || !buf) {

		return EINVAL;



	}
#ifdef __LOCAL_MB_CUR_MAX
	if (buflen < __LOCAL_MB_CUR_MAX)
#else /* __LOCAL_MB_CUR_MAX */
	if (buflen < 7)
#endif /* !__LOCAL_MB_CUR_MAX */
	{

		return ERANGE;



	}
	*presult = libc_wctomb(buf, wc);
	return EOK;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_OUTS(2, 3) ATTR_OUT_OPT(1) errno_t
NOTHROW_NCX(LIBDCALL libd__wctomb_s_l)(int *presult,
                                       char *buf,
                                       size_t buflen,
                                       char16_t wc,
                                       locale_t locale) {
	(void)locale;
	return libd_wctomb_s(presult, buf, buflen, wc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_OUTS(2, 3) ATTR_OUT_OPT(1) errno_t
NOTHROW_NCX(LIBKCALL libc__wctomb_s_l)(int *presult,
                                       char *buf,
                                       size_t buflen,
                                       char32_t wc,
                                       locale_t locale) {
	(void)locale;
	return libc_wctomb_s(presult, buf, buflen, wc);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_INS(4, 5) ATTR_OUTS(2, 3) ATTR_OUT_OPT(1) errno_t
NOTHROW_NCX(LIBDCALL libd__wcstombs_s_l)(size_t *presult,
                                         char *buf,
                                         size_t buflen,
                                         char16_t const *src,
                                         size_t maxlen,
                                         locale_t locale) {
	(void)locale;
	return libd_wcstombs_s(presult, buf, buflen, src, maxlen);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_INS(4, 5) ATTR_OUTS(2, 3) ATTR_OUT_OPT(1) errno_t
NOTHROW_NCX(LIBKCALL libc__wcstombs_s_l)(size_t *presult,
                                         char *buf,
                                         size_t buflen,
                                         char32_t const *src,
                                         size_t maxlen,
                                         locale_t locale) {
	(void)locale;
	return libc_wcstombs_s(presult, buf, buflen, src, maxlen);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_IN(2) ATTR_OUTS(1, 3) size_t
NOTHROW_NCX(LIBDCALL libd__wcstombs_l)(char *dst,
                                       char16_t const *src,
                                       size_t dstlen,
                                       locale_t locale) {
	(void)locale;
	return libd_wcstombs(dst, src, dstlen);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_IN(2) ATTR_OUTS(1, 3) size_t
NOTHROW_NCX(LIBKCALL libc__wcstombs_l)(char *dst,
                                       char32_t const *src,
                                       size_t dstlen,
                                       locale_t locale) {
	(void)locale;
	return libc_wcstombs(dst, src, dstlen);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_INS(4, 5) ATTR_OUTS(2, 3) ATTR_OUT_OPT(1) errno_t
NOTHROW_NCX(LIBDCALL libd_wcstombs_s)(size_t *presult,
                                      char *buf,
                                      size_t buflen,
                                      char16_t const *src,
                                      size_t maxlen) {
	if (!presult || !buf || !src) {

		return 22;



	}
	if (buflen > maxlen)
		buflen = maxlen;
	*presult = libd_wcstombs(buf, src, buflen);
	/* TODO: if (buflen < *presult) return ERANGE; */
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_INS(4, 5) ATTR_OUTS(2, 3) ATTR_OUT_OPT(1) errno_t
NOTHROW_NCX(LIBKCALL libc_wcstombs_s)(size_t *presult,
                                      char *buf,
                                      size_t buflen,
                                      char32_t const *src,
                                      size_t maxlen) {
	if (!presult || !buf || !src) {

		return EINVAL;



	}
	if (buflen > maxlen)
		buflen = maxlen;
	*presult = libc_wcstombs(buf, src, buflen);
	/* TODO: if (buflen < *presult) return ERANGE; */
	return EOK;
}
#include <asm/os/fcntl.h>
/* >> _fullpath(3)
 * s.a. `realpath(3)', `frealpathat(3)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED ATTR_IN(2) ATTR_OUTS(1, 3) char *
NOTHROW_RPC(LIBDCALL libd__fullpath)(char *buf,
                                     char const *path,
                                     size_t buflen) {
	return libd_frealpathat(__AT_FDCWD, path, buf, buflen, 0);
}
#include <asm/os/fcntl.h>
/* >> _fullpath(3)
 * s.a. `realpath(3)', `frealpathat(3)' */
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED ATTR_IN(2) ATTR_OUTS(1, 3) char *
NOTHROW_RPC(LIBCCALL libc__fullpath)(char *buf,
                                     char const *path,
                                     size_t buflen) {
	return libc_frealpathat(__AT_FDCWD, path, buf, buflen, 0);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_OUT(5) ATTR_OUT(6) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd__ecvt_s)(char *buf,
                                   size_t buflen,
                                   double val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign) {
	return libd_errno_kos2dos(libc__ecvt_s(buf, buflen, val, ndigit, decptr, sign));
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_OUT(5) ATTR_OUT(6) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__ecvt_s)(char *buf,
                                   size_t buflen,
                                   double val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign) {
	if (!buf || !decptr || !sign) {

		return EINVAL;



	}
	libc_ecvt_r(val, ndigit, decptr, sign, buf, buflen);
	return EOK;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_OUT(5) ATTR_OUT(6) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd__fcvt_s)(char *buf,
                                   size_t buflen,
                                   double val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign) {
	return libd_errno_kos2dos(libc__fcvt_s(buf, buflen, val, ndigit, decptr, sign));
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_OUT(5) ATTR_OUT(6) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__fcvt_s)(char *buf,
                                   size_t buflen,
                                   double val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign) {
	if (!buf || !decptr || !sign) {

		return EINVAL;



	}
	libc_fcvt_r(val, ndigit, decptr, sign, buf, buflen);
	return EOK;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd__gcvt_s)(char *buf,
                                   size_t buflen,
                                   double val,
                                   int ndigit) {
	return libd_errno_kos2dos(libc__gcvt_s(buf, buflen, val, ndigit));
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__gcvt_s)(char *buf,
                                   size_t buflen,
                                   double val,
                                   int ndigit) {
	int a, b;
	if (!buf) {

		return EINVAL;



	}
	libc_ecvt_r(val, ndigit, &a, &b, buf, buflen);
	return EOK;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_IN(2) ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc__atoflt)(float *__restrict result,
                                   char const *__restrict nptr) {
	*result = libc_strtof(nptr, NULL);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_IN(2) ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc__atoflt_l)(float *__restrict result,
                                     char const *__restrict nptr,
                                     locale_t locale) {
	*result = libc_strtof_l(nptr, NULL, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_IN(2) ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc__atodbl)(double *__restrict result,
                                   char __KOS_FIXED_CONST *__restrict nptr) {
	*result = libc_strtod(nptr, NULL);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_IN(2) ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc__atodbl_l)(double *__restrict result,
                                     char __KOS_FIXED_CONST *__restrict nptr,
                                     locale_t locale) {
	*result = libc_strtod_l(nptr, NULL, locale);
	return 0;
}
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS_P(libc__atoldbl,libc__atodbl,ATTR_IN(2) ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(__LONGDOUBLE *__restrict result, char __KOS_FIXED_CONST *__restrict nptr),(result,nptr));
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_IN(2) ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc__atoldbl)(__LONGDOUBLE *__restrict result,
                                    char __KOS_FIXED_CONST *__restrict nptr) {
	*result = libc_strtold(nptr, NULL);
	return 0;
}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS_P(libc__atoldbl_l,libc__atodbl_l,ATTR_IN(2) ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(__LONGDOUBLE *__restrict result, char __KOS_FIXED_CONST *__restrict nptr, locale_t locale),(result,nptr,locale));
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_IN(2) ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc__atoldbl_l)(__LONGDOUBLE *__restrict result,
                                      char __KOS_FIXED_CONST *__restrict nptr,
                                      locale_t locale) {
	*result = libc_strtold_l(nptr, NULL, locale);
	return 0;
}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS_P(libc__rotl,libc__rotl64,ATTR_CONST,unsigned int,NOTHROW,LIBCCALL,(unsigned int val, int shift),(val,shift));
#else /* __SIZEOF_INT__ == 8 */
#include <hybrid/__rotate.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST unsigned int
NOTHROW(LIBCCALL libc__rotl)(unsigned int val,
                             int shift) {
	return __hybrid_rol(val, (shift_t)(unsigned int)shift);
}
#endif /* __SIZEOF_INT__ != 8 */
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS_P(libc__rotr,libc__rotr64,ATTR_CONST,unsigned int,NOTHROW,LIBCCALL,(unsigned int val, int shift),(val,shift));
#else /* __SIZEOF_INT__ == 8 */
#include <hybrid/__rotate.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST unsigned int
NOTHROW(LIBCCALL libc__rotr)(unsigned int val,
                             int shift) {
	return __hybrid_ror(val, (shift_t)(unsigned int)shift);
}
#endif /* __SIZEOF_INT__ != 8 */
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS_P(libc__lrotl,libc__rotl,ATTR_CONST,unsigned long,NOTHROW,LIBCCALL,(unsigned long val, int shift),(val,shift));
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc__lrotl,libc__rotl64,ATTR_CONST,unsigned long,NOTHROW,LIBCCALL,(unsigned long val, int shift),(val,shift));
#else /* ... */
#include <hybrid/__rotate.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST unsigned long
NOTHROW(LIBCCALL libc__lrotl)(unsigned long val,
                              int shift) {
	return __hybrid_rol(val, (shift_t)(unsigned int)shift);
}
#endif /* !... */
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS_P(libc__lrotr,libc__rotr,ATTR_CONST,unsigned long,NOTHROW,LIBCCALL,(unsigned long val, int shift),(val,shift));
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc__lrotr,libc__rotr64,ATTR_CONST,unsigned long,NOTHROW,LIBCCALL,(unsigned long val, int shift),(val,shift));
#else /* ... */
#include <hybrid/__rotate.h>
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST unsigned long
NOTHROW(LIBCCALL libc__lrotr)(unsigned long val,
                              int shift) {
	return __hybrid_ror(val, (shift_t)(unsigned int)shift);
}
#endif /* !... */
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.environ") errno_t
NOTHROW_NCX(LIBDCALL libd__putenv_s)(char const *varname,
                                     char const *val) {
	return libd_setenv(varname, val, 1)

	       ? __libc_geterrno_or(22)



	       : 0;
}
INTERN ATTR_SECTION(".text.crt.dos.fs.environ") errno_t
NOTHROW_NCX(LIBCCALL libc__putenv_s)(char const *varname,
                                     char const *val) {
	return libc_setenv(varname, val, 1)

	       ? __libc_geterrno_or(EINVAL)



	       : 0;
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") ATTR_IN(1) ATTR_IN(2) ATTR_OUT(3) void
NOTHROW_RPC(LIBCCALL libc__searchenv)(char const *file,
                                      char const *envvar,
                                      char *__restrict resultpath) {
	libc__searchenv_s(file, envvar, resultpath, (size_t)-1);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") ATTR_IN_OPT(2) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_OUT(1) void
NOTHROW_NCX(LIBCCALL libc__makepath)(char *__restrict buf,
                                     char const *drive,
                                     char const *dir,
                                     char const *file,
                                     char const *ext) {
	libc__makepath_s(buf, (size_t)-1, drive, dir, file, ext);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(3) ATTR_OUT_OPT(4) ATTR_OUT_OPT(5) void
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.utility") ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_IN_OPT(6) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd__makepath_s)(char *buf,
                                       size_t buflen,
                                       char const *drive,
                                       char const *dir,
                                       char const *file,
                                       char const *ext) {
	return libd_errno_kos2dos(libc__makepath_s(buf, buflen, drive, dir, file, ext));
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_IN_OPT(6) ATTR_OUTS(1, 2) errno_t
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
	}	__WHILE0
#define path_putc(ch)          \
	do {                       \
		if unlikely(!buflen--) \
			goto err_buflen;   \
		*buf++ = (ch);         \
	}	__WHILE0
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

	return EINVAL;



#undef path_putn
#undef path_putc
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.utility") ATTR_IN(1) ATTR_OUTS(2, 3) ATTR_OUTS(4, 5) ATTR_OUTS(6, 7) ATTR_OUTS(8, 9) errno_t
NOTHROW_NCX(LIBDCALL libd__splitpath_s)(char const *__restrict abspath,
                                        char *drive,
                                        size_t drivelen,
                                        char *dir,
                                        size_t dirlen,
                                        char *file,
                                        size_t filelen,
                                        char *ext,
                                        size_t extlen) {
	return libd_errno_kos2dos(libc__splitpath_s(abspath, drive, drivelen, dir, dirlen, file, filelen, ext, extlen));
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") ATTR_IN(1) ATTR_OUTS(2, 3) ATTR_OUTS(4, 5) ATTR_OUTS(6, 7) ATTR_OUTS(8, 9) errno_t
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

	return EINVAL;



err_range:

	(void)libc_seterrno(ERANGE);
	return ERANGE;



}
#include <bits/os/timespec.h>
/* >> _sleep(3)
 * Sleep for `milli' milliseconds (1/1.000 seconds) */
INTERN ATTR_SECTION(".text.crt.bsd") void
NOTHROW_RPC(LIBCCALL libc__sleep)(uint32_t milli) {
	struct timespec ts;
	ts.tv_sec  = milli / 1000;
	ts.tv_nsec = (milli % 1000) * 1000;

	{
		struct timespec rem;
		for (;;) {
			rem.tv_sec  = 0;
			rem.tv_nsec = 0;
			if (libc_nanosleep(&ts, &rem) == 0)
				break;
			if (__libc_geterrno() == EINTR)
				break;
			ts.tv_sec  = rem.tv_sec;
			ts.tv_nsec = rem.tv_nsec;
		}
	}



}
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_OUT(2) char *
NOTHROW_NCX(LIBCCALL libc_itoa)(int val,
                                char *buf,
                                int radix) {
	libc__itoa_s(val, buf, (size_t)-1, radix);
	return buf;
}
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS_P(libc_ltoa,libc_itoa,ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(long val, char *buf, int radix),(val,buf,radix));
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_OUT(2) char *
NOTHROW_NCX(LIBCCALL libc_ltoa)(long val,
                                char *buf,
                                int radix) {
	libc__ltoa_s(val, buf, (size_t)-1, radix);
	return buf;
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.unicode.static.convert") ATTR_OUT(2) char *
NOTHROW_NCX(LIBCCALL libc_ultoa)(unsigned long val,
                                 char *buf,
                                 int radix) {
	libc__ultoa_s(val, buf, (size_t)-1, radix);
	return buf;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_IN(4) ATTR_OUT(1) ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBDCALL libd__wgetenv_s)(size_t *preqsize,
                                      char16_t *buf,
                                      rsize_t bufsize,
                                      char16_t const *varname) {
	size_t reqsize;
	char16_t *name = libd__wgetenv(varname);
	if (!name) {
		if (preqsize)
			*preqsize = 0;
		return EOK;
	}
	reqsize = (libd_wcslen(name) + 1) * sizeof(char16_t);
	if (preqsize)
		*preqsize = reqsize;
	if (reqsize > bufsize) {

		return ERANGE;



	}
	libc_memcpy(buf, name, reqsize);
	return EOK;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_IN(4) ATTR_OUT(1) ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBKCALL libc__wgetenv_s)(size_t *preqsize,
                                      char32_t *buf,
                                      rsize_t bufsize,
                                      char32_t const *varname) {
	size_t reqsize;
	char32_t *name = libc__wgetenv(varname);
	if (!name) {
		if (preqsize)
			*preqsize = 0;
		return EOK;
	}
	reqsize = (libc_wcslen(name) + 1) * sizeof(char32_t);
	if (preqsize)
		*preqsize = reqsize;
	if (reqsize > bufsize) {

		return ERANGE;



	}
	libc_memcpy(buf, name, reqsize);
	return EOK;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_IN(3) ATTR_OUT(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBDCALL libd__wdupenv_s)(char16_t **__restrict pbuf,
                                      size_t *pbuflen,
                                      char16_t const *varname) {
	char16_t *name = libd__wgetenv(varname);
	if (!name) {
		*pbuf    = NULL;
		*pbuflen = 0;
		return 0;
	}
	name = libd_wcsdup(name);
	if (!name) {

		return 12;



	}
	*pbuf    = name;
	*pbuflen = (libd_wcslen(name) + 1) * sizeof(char16_t);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_IN(3) ATTR_OUT(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBKCALL libc__wdupenv_s)(char32_t **__restrict pbuf,
                                      size_t *pbuflen,
                                      char32_t const *varname) {
	char32_t *name = libc__wgetenv(varname);
	if (!name) {
		*pbuf    = NULL;
		*pbuflen = 0;
		return EOK;
	}
	name = libc_wcsdup(name);
	if (!name) {

		return ENOMEM;



	}
	*pbuf    = name;
	*pbuflen = (libc_wcslen(name) + 1) * sizeof(char32_t);
	return EOK;
}
#include <libc/template/environ.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.environ") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc__get_environ)(char ***p_environ) {
	*p_environ = __LOCAL_environ;
	return 0;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBDCALL libd__get_wenviron)(char16_t ***p_wenviron) {
	*p_wenviron = *libd___p__wenviron();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBKCALL libc__get_wenviron)(char32_t ***p_wenviron) {
	*p_wenviron = *libc___p__wenviron();
	return 0;
}
#endif /* !__KERNEL__ */

DECL_END

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$bsearch_r,libd_bsearch_r,WUNUSED ATTR_IN(1) ATTR_IN_OPT(2) NONNULL((5)),void *,NOTHROW_CB_NCX,LIBDCALL,(void const *pkey, void const *pbase, size_t item_count, size_t item_size, int (LIBDCALL *compar)(void const *a, void const *b, void *arg), void *arg),(pkey,pbase,item_count,item_size,compar,arg));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(bsearch_r,libc_bsearch_r,WUNUSED ATTR_IN(1) ATTR_IN_OPT(2) NONNULL((5)),void *,NOTHROW_CB_NCX,LIBCCALL,(void const *pkey, void const *pbase, size_t item_count, size_t item_size, int (LIBCCALL *compar)(void const *a, void const *b, void *arg), void *arg),(pkey,pbase,item_count,item_size,compar,arg));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$qsort,libd_qsort,ATTR_INOUT_OPT(1) NONNULL((4)),NOTHROW_CB_NCX,LIBDCALL,(void *pbase, size_t item_count, size_t item_size, int (LIBDCALL *compar)(void const *a, void const *b)),(pbase,item_count,item_size,compar));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
DEFINE_PUBLIC_ALIAS_P_VOID(qsort,libc_qsort,ATTR_INOUT_OPT(1) NONNULL((4)),NOTHROW_CB_NCX,LIBCCALL,(void *pbase, size_t item_count, size_t item_size, int (LIBCCALL *compar)(void const *a, void const *b)),(pbase,item_count,item_size,compar));
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$bsearch,libd_bsearch,WUNUSED ATTR_IN(1) ATTR_IN_OPT(2) NONNULL((5)),void *,NOTHROW_CB_NCX,LIBDCALL,(void const *pkey, void const *pbase, size_t item_count, size_t item_size, int (LIBDCALL *compar)(void const *a, void const *b)),(pkey,pbase,item_count,item_size,compar));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(bsearch,libc_bsearch,WUNUSED ATTR_IN(1) ATTR_IN_OPT(2) NONNULL((5)),void *,NOTHROW_CB_NCX,LIBCCALL,(void const *pkey, void const *pbase, size_t item_count, size_t item_size, int (LIBCCALL *compar)(void const *a, void const *b)),(pkey,pbase,item_count,item_size,compar));
#if __SIZEOF_INTMAX_T__ == __SIZEOF_INT__
DEFINE_PUBLIC_ALIAS_P(imaxabs,libc_abs,ATTR_CONST WUNUSED,int,NOTHROW,LIBCCALL,(int x),(x));
#endif /* __SIZEOF_INTMAX_T__ == __SIZEOF_INT__ */
DEFINE_PUBLIC_ALIAS_P(abs,libc_abs,ATTR_CONST WUNUSED,int,NOTHROW,LIBCCALL,(int x),(x));
#if __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
DEFINE_PUBLIC_ALIAS_P(imaxabs,libc_labs,ATTR_CONST WUNUSED,long,NOTHROW,LIBCCALL,(long x),(x));
#endif /* __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ */
DEFINE_PUBLIC_ALIAS_P(labs,libc_labs,ATTR_CONST WUNUSED,long,NOTHROW,LIBCCALL,(long x),(x));
#if __SIZEOF_INTMAX_T__ == __SIZEOF_INT__
DEFINE_PUBLIC_ALIAS_P(imaxdiv,libc_div,WUNUSED __ATTR_CONST,struct __div_struct,NOTHROW_NCX,LIBCCALL,(int numer, int denom),(numer,denom));
#endif /* __SIZEOF_INTMAX_T__ == __SIZEOF_INT__ */
DEFINE_PUBLIC_ALIAS_P(div,libc_div,WUNUSED __ATTR_CONST,struct __div_struct,NOTHROW_NCX,LIBCCALL,(int numer, int denom),(numer,denom));
#if __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
DEFINE_PUBLIC_ALIAS_P(imaxdiv,libc_ldiv,WUNUSED __ATTR_CONST,ldiv_t,NOTHROW_NCX,LIBCCALL,(long numer, long denom),(numer,denom));
#endif /* __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ */
DEFINE_PUBLIC_ALIAS_P(ldiv,libc_ldiv,WUNUSED __ATTR_CONST,ldiv_t,NOTHROW_NCX,LIBCCALL,(long numer, long denom),(numer,denom));
#if __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
DEFINE_PUBLIC_ALIAS_P(imaxabs,libc_llabs,ATTR_CONST WUNUSED,__LONGLONG,NOTHROW,LIBCCALL,(__LONGLONG x),(x));
#endif /* __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ */
DEFINE_PUBLIC_ALIAS_P(llabs,libc_llabs,ATTR_CONST WUNUSED,__LONGLONG,NOTHROW,LIBCCALL,(__LONGLONG x),(x));
DEFINE_PUBLIC_ALIAS_P(qabs,libc_llabs,ATTR_CONST WUNUSED,__LONGLONG,NOTHROW,LIBCCALL,(__LONGLONG x),(x));
#if __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
DEFINE_PUBLIC_ALIAS_P(imaxdiv,libc_lldiv,WUNUSED __ATTR_CONST,lldiv_t,NOTHROW_NCX,LIBCCALL,(__LONGLONG numer, __LONGLONG denom),(numer,denom));
#endif /* __SIZEOF_INTMAX_T__ != __SIZEOF_INT__ && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ */
DEFINE_PUBLIC_ALIAS_P(lldiv,libc_lldiv,WUNUSED __ATTR_CONST,lldiv_t,NOTHROW_NCX,LIBCCALL,(__LONGLONG numer, __LONGLONG denom),(numer,denom));
DEFINE_PUBLIC_ALIAS_P(qdiv,libc_lldiv,WUNUSED __ATTR_CONST,lldiv_t,NOTHROW_NCX,LIBCCALL,(__LONGLONG numer, __LONGLONG denom),(numer,denom));
DEFINE_PUBLIC_ALIAS_P(mblen,libc_mblen,ATTR_IN_OPT(1),int,NOTHROW_NCX,LIBCCALL,(char const *str, size_t maxlen),(str,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$mbtowc,libd_mbtowc,ATTR_IN_OPT(2) ATTR_OUT_OPT(1),int,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict pwc, char const *__restrict str, size_t maxlen),(pwc,str,maxlen));
DEFINE_PUBLIC_ALIAS_P(mbtowc,libc_mbtowc,ATTR_IN_OPT(2) ATTR_OUT_OPT(1),int,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict pwc, char const *__restrict str, size_t maxlen),(pwc,str,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$wctomb,libd_wctomb,ATTR_OUT_OPT(1),int,NOTHROW_NCX,LIBDCALL,(char *str, char16_t wc),(str,wc));
DEFINE_PUBLIC_ALIAS_P(wctomb,libc_wctomb,ATTR_OUT_OPT(1),int,NOTHROW_NCX,LIBKCALL,(char *str, char32_t wc),(str,wc));
DEFINE_PUBLIC_ALIAS_P(DOS$mbstowcs,libd_mbstowcs,ATTR_IN(2) ATTR_OUTS(1, 3),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict dst, char const *__restrict src, size_t dstlen),(dst,src,dstlen));
DEFINE_PUBLIC_ALIAS_P(mbstowcs,libc_mbstowcs,ATTR_IN(2) ATTR_OUTS(1, 3),size_t,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict dst, char const *__restrict src, size_t dstlen),(dst,src,dstlen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcstombs,libd_wcstombs,ATTR_IN(2) ATTR_OUTS(1, 3),size_t,NOTHROW_NCX,LIBDCALL,(char *__restrict dst, char16_t const *__restrict src, size_t dstlen),(dst,src,dstlen));
DEFINE_PUBLIC_ALIAS_P(wcstombs,libc_wcstombs,ATTR_IN(2) ATTR_OUTS(1, 3),size_t,NOTHROW_NCX,LIBKCALL,(char *__restrict dst, char32_t const *__restrict src, size_t dstlen),(dst,src,dstlen));
DEFINE_PUBLIC_ALIAS_P(__libc_system,libc_system,ATTR_IN_OPT(1),int,NOTHROW_RPC,LIBCCALL,(char const *command),(command));
DEFINE_PUBLIC_ALIAS_P(system,libc_system,ATTR_IN_OPT(1),int,NOTHROW_RPC,LIBCCALL,(char const *command),(command));
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_ABORT)
DEFINE_PUBLIC_ALIAS_P_VOID(_ZSt9terminatev,libc_abort,ATTR_NORETURN,,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P_VOID(terminate,libc_abort,ATTR_NORETURN,,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P_VOID(__chk_fail,libc_abort,ATTR_NORETURN,,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P_VOID("?terminate@@YAXXZ",libc_abort,ATTR_NORETURN,,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P_VOID(abort,libc_abort,ATTR_NORETURN,,LIBCCALL,(void),());
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_ABORT */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(atoi,libc_atoi,ATTR_PURE WUNUSED ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr),(nptr));
DEFINE_PUBLIC_ALIAS_P(atol,libc_atol,ATTR_PURE WUNUSED ATTR_IN(1),long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr),(nptr));
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
DEFINE_PUBLIC_ALIAS_P(strtoimax,libc_strtol,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ */
DEFINE_PUBLIC_ALIAS_P(strtol,libc_strtol,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
DEFINE_PUBLIC_ALIAS_P(strtoumax,libc_strtoul,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ */
DEFINE_PUBLIC_ALIAS_P(strtoul,libc_strtoul,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
DEFINE_PUBLIC_ALIAS_P(atoll,libc_atoll,ATTR_PURE WUNUSED ATTR_IN(1),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr),(nptr));
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
DEFINE_PUBLIC_ALIAS_P(strtoimax,libc_strtoll,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ */
DEFINE_PUBLIC_ALIAS_P(strtoll,libc_strtoll,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
DEFINE_PUBLIC_ALIAS_P(strtoq,libc_strtoll,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
DEFINE_PUBLIC_ALIAS_P(__strtoq,libc_strtoll,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
DEFINE_PUBLIC_ALIAS_P(strtoumax,libc_strtoull,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ */
DEFINE_PUBLIC_ALIAS_P(strtoull,libc_strtoull,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
DEFINE_PUBLIC_ALIAS_P(strtouq,libc_strtoull,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
DEFINE_PUBLIC_ALIAS_P(__strtouq,libc_strtoull,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
DEFINE_PUBLIC_ALIAS_P(atof,libc_atof,ATTR_LEAF WUNUSED ATTR_IN(1),double,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr),(nptr));
DEFINE_PUBLIC_ALIAS_P(strtod,libc_strtod,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),double,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr),(nptr,endptr));
DEFINE_PUBLIC_ALIAS_P(__strtof,libc_strtof,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),float,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr),(nptr,endptr));
DEFINE_PUBLIC_ALIAS_P(strtof,libc_strtof,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),float,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr),(nptr,endptr));
DEFINE_PUBLIC_ALIAS_P(__strtold,libc_strtold,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGDOUBLE,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr),(nptr,endptr));
DEFINE_PUBLIC_ALIAS_P(strtold,libc_strtold,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGDOUBLE,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr),(nptr,endptr));
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS_P(strtou32_r,libc_strtou32_r,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4),uint32_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, errno_t *error),(nptr,endptr,base,error));
DEFINE_PUBLIC_ALIAS_P(strto32_r,libc_strto32_r,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4),int32_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, errno_t *error),(nptr,endptr,base,error));
DEFINE_PUBLIC_ALIAS_P(strtou64_r,libc_strtou64_r,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4),uint64_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, errno_t *error),(nptr,endptr,base,error));
DEFINE_PUBLIC_ALIAS_P(strto64_r,libc_strto64_r,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4),int64_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, errno_t *error),(nptr,endptr,base,error));
#if !defined(__KERNEL__) && __SIZEOF_INTMAX_T__ == 4
DEFINE_PUBLIC_ALIAS_P(strtoumax,libc_strtou32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint32_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* !__KERNEL__ && __SIZEOF_INTMAX_T__ == 4 */
DEFINE_PUBLIC_ALIAS_P(strtou32,libc_strtou32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint32_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#if !defined(__KERNEL__) && __SIZEOF_INTMAX_T__ == 4
DEFINE_PUBLIC_ALIAS_P(strtoimax,libc_strto32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int32_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* !__KERNEL__ && __SIZEOF_INTMAX_T__ == 4 */
DEFINE_PUBLIC_ALIAS_P(strto32,libc_strto32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int32_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#if !defined(__KERNEL__) && __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS_P(strtoumax,libc_strtou64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint64_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* !__KERNEL__ && __SIZEOF_INTMAX_T__ == 8 */
#if defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(_strtoui64,libc_strtou64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint64_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
DEFINE_PUBLIC_ALIAS_P(strtou64,libc_strtou64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint64_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#if !defined(__KERNEL__) && __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS_P(strtoimax,libc_strto64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int64_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* !__KERNEL__ && __SIZEOF_INTMAX_T__ == 8 */
#if defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(_strtoi64,libc_strto64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int64_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
DEFINE_PUBLIC_ALIAS_P(strto64,libc_strto64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int64_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#ifndef __KERNEL__
#if __SIZEOF_INTMAX_T__ == 4
DEFINE_PUBLIC_ALIAS_P(strtoumax_l,libc_strtou32_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint32_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ == 4 */
#if defined(__LIBCCALL_IS_LIBDCALL) && __SIZEOF_INTMAX_T__ == 4
DEFINE_PUBLIC_ALIAS_P(_strtoumax_l,libc_strtou32_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint32_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __LIBCCALL_IS_LIBDCALL && __SIZEOF_INTMAX_T__ == 4 */
DEFINE_PUBLIC_ALIAS_P(strtou32_l,libc_strtou32_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint32_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#if __SIZEOF_INTMAX_T__ == 4
DEFINE_PUBLIC_ALIAS_P(strtoimax_l,libc_strto32_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int32_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ == 4 */
#if defined(__LIBCCALL_IS_LIBDCALL) && __SIZEOF_INTMAX_T__ == 4
DEFINE_PUBLIC_ALIAS_P(_strtoimax_l,libc_strto32_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int32_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __LIBCCALL_IS_LIBDCALL && __SIZEOF_INTMAX_T__ == 4 */
DEFINE_PUBLIC_ALIAS_P(strto32_l,libc_strto32_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int32_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#if __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS_P(strtoumax_l,libc_strtou64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint64_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ == 8 */
#if defined(__LIBCCALL_IS_LIBDCALL) && __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS_P(_strtoumax_l,libc_strtou64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint64_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __LIBCCALL_IS_LIBDCALL && __SIZEOF_INTMAX_T__ == 8 */
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_strtoui64_l,libc_strtou64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint64_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(strtou64_l,libc_strtou64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint64_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#if __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS_P(strtoimax_l,libc_strto64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int64_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ == 8 */
#if defined(__LIBCCALL_IS_LIBDCALL) && __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS_P(_strtoimax_l,libc_strto64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int64_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __LIBCCALL_IS_LIBDCALL && __SIZEOF_INTMAX_T__ == 8 */
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_strtoi64_l,libc_strto64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int64_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(strto64_l,libc_strto64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int64_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_gcvt,libc_gcvt,WUNUSED ATTR_OUT(3),char *,NOTHROW_NCX,LIBCCALL,(double val, int ndigit, char *buf),(val,ndigit,buf));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(gcvt,libc_gcvt,WUNUSED ATTR_OUT(3),char *,NOTHROW_NCX,LIBCCALL,(double val, int ndigit, char *buf),(val,ndigit,buf));
DEFINE_PUBLIC_ALIAS_P(ecvt_r,libc_ecvt_r,ATTR_OUT(3) ATTR_OUT(4) ATTR_OUTS(5, 6),int,NOTHROW_NCX,LIBCCALL,(double val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len),(val,ndigit,decptr,sign,buf,len));
DEFINE_PUBLIC_ALIAS_P(fcvt_r,libc_fcvt_r,ATTR_OUT(3) ATTR_OUT(4) ATTR_OUTS(5, 6),int,NOTHROW_NCX,LIBCCALL,(double val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len),(val,ndigit,decptr,sign,buf,len));
DEFINE_PUBLIC_ALIAS_P(qgcvt,libc_qgcvt,ATTR_OUT(3),char *,NOTHROW_NCX,LIBCCALL,(__LONGDOUBLE val, int ndigit, char *buf),(val,ndigit,buf));
DEFINE_PUBLIC_ALIAS_P(qecvt_r,libc_qecvt_r,ATTR_OUT(3) ATTR_OUT(4) ATTR_OUTS(5, 6),int,NOTHROW_NCX,LIBCCALL,(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len),(val,ndigit,decptr,sign,buf,len));
DEFINE_PUBLIC_ALIAS_P(qfcvt_r,libc_qfcvt_r,ATTR_OUT(3) ATTR_OUT(4) ATTR_OUTS(5, 6),int,NOTHROW_NCX,LIBCCALL,(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign, char *__restrict buf, size_t len),(val,ndigit,decptr,sign,buf,len));
DEFINE_PUBLIC_ALIAS_P(qecvt,libc_qecvt,WUNUSED ATTR_OUT(3) ATTR_OUT(4),char *,NOTHROW_NCX,LIBCCALL,(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign),(val,ndigit,decptr,sign));
DEFINE_PUBLIC_ALIAS_P(qfcvt,libc_qfcvt,WUNUSED ATTR_OUT(3) ATTR_OUT(4),char *,NOTHROW_NCX,LIBCCALL,(__LONGDOUBLE val, int ndigit, int *__restrict decptr, int *__restrict sign),(val,ndigit,decptr,sign));
DEFINE_PUBLIC_ALIAS_P(mkstemps,libc_mkstemps,WUNUSED ATTR_INOUT(1),fd_t,NOTHROW_RPC,LIBCCALL,(char *template_, __STDC_INT_AS_SIZE_T suffixlen),(template_,suffixlen));
DEFINE_PUBLIC_ALIAS_P(rpmatch,libc_rpmatch,ATTR_PURE WUNUSED ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(char const *response),(response));
DEFINE_PUBLIC_ALIAS_P(mkstemps64,libc_mkstemps64,WUNUSED ATTR_INOUT(1),fd_t,NOTHROW_RPC,LIBCCALL,(char *template_, __STDC_INT_AS_SIZE_T suffixlen),(template_,suffixlen));
DEFINE_PUBLIC_ALIAS_P(l64a,libc_l64a,ATTR_RETNONNULL WUNUSED,char *,NOTHROW_NCX,LIBCCALL,(long n),(n));
DEFINE_PUBLIC_ALIAS_P(a64l,libc_a64l,ATTR_PURE WUNUSED ATTR_IN(1),long,NOTHROW_NCX,LIBCCALL,(char const *s),(s));
DEFINE_PUBLIC_ALIAS_P(DOS$realpath,libd_realpath,WUNUSED ATTR_IN(1),char *,NOTHROW_RPC,LIBDCALL,(char const *filename, char *resolved),(filename,resolved));
DEFINE_PUBLIC_ALIAS_P(realpath,libc_realpath,WUNUSED ATTR_IN(1),char *,NOTHROW_RPC,LIBCCALL,(char const *filename, char *resolved),(filename,resolved));
DEFINE_PUBLIC_ALIAS_P(DOS$frealpath,libd_frealpath,WUNUSED ATTR_FDARG(1) ATTR_OUT_OPT(2),char *,NOTHROW_RPC,LIBDCALL,(fd_t fd, char *resolved, size_t buflen),(fd,resolved,buflen));
DEFINE_PUBLIC_ALIAS_P(frealpath,libc_frealpath,WUNUSED ATTR_FDARG(1) ATTR_OUT_OPT(2),char *,NOTHROW_RPC,LIBCCALL,(fd_t fd, char *resolved, size_t buflen),(fd,resolved,buflen));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_mktemp,libc_mktemp,ATTR_RETNONNULL ATTR_INOUT(1),char *,NOTHROW_NCX,LIBCCALL,(char *template_),(template_));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__mktemp,libc_mktemp,ATTR_RETNONNULL ATTR_INOUT(1),char *,NOTHROW_NCX,LIBCCALL,(char *template_),(template_));
DEFINE_PUBLIC_ALIAS_P(mktemp,libc_mktemp,ATTR_RETNONNULL ATTR_INOUT(1),char *,NOTHROW_NCX,LIBCCALL,(char *template_),(template_));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_ecvt,libc_ecvt,WUNUSED ATTR_OUT(3) ATTR_OUT(4),char *,NOTHROW_NCX,LIBCCALL,(double val, int ndigit, int *__restrict decptr, int *__restrict sign),(val,ndigit,decptr,sign));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(ecvt,libc_ecvt,WUNUSED ATTR_OUT(3) ATTR_OUT(4),char *,NOTHROW_NCX,LIBCCALL,(double val, int ndigit, int *__restrict decptr, int *__restrict sign),(val,ndigit,decptr,sign));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_fcvt,libc_fcvt,WUNUSED ATTR_OUT(3) ATTR_OUT(4),char *,NOTHROW_NCX,LIBCCALL,(double val, int ndigit, int *__restrict decptr, int *__restrict sign),(val,ndigit,decptr,sign));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(fcvt,libc_fcvt,WUNUSED ATTR_OUT(3) ATTR_OUT(4),char *,NOTHROW_NCX,LIBCCALL,(double val, int ndigit, int *__restrict decptr, int *__restrict sign),(val,ndigit,decptr,sign));
DEFINE_PUBLIC_ALIAS_P(getsubopt,libc_getsubopt,WUNUSED ATTR_IN(2) ATTR_INOUT_OPT(1) ATTR_OUT(3),int,NOTHROW_NCX,LIBCCALL,(char **__restrict optionp, char *const *__restrict tokens, char **__restrict valuep),(optionp,tokens,valuep));
DEFINE_PUBLIC_ALIAS_P(mkstemp,libc_mkstemp,WUNUSED ATTR_INOUT(1),fd_t,NOTHROW_RPC,LIBCCALL,(char *template_),(template_));
DEFINE_PUBLIC_ALIAS_P(mkstemp64,libc_mkstemp64,WUNUSED ATTR_INOUT(1),fd_t,NOTHROW_RPC,LIBCCALL,(char *template_),(template_));
DEFINE_PUBLIC_ALIAS_P(mkdtemp,libc_mkdtemp,WUNUSED ATTR_INOUT(1),char *,NOTHROW_RPC,LIBCCALL,(char *template_),(template_));
DEFINE_PUBLIC_ALIAS_P(unlockpt,libc_unlockpt,ATTR_FDARG(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(DOS$ptsname,libd_ptsname,WUNUSED ATTR_FDARG(1),char *,NOTHROW_NCX,LIBDCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(ptsname,libc_ptsname,WUNUSED ATTR_FDARG(1),char *,NOTHROW_NCX,LIBCCALL,(fd_t fd),(fd));
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG___
DEFINE_PUBLIC_ALIAS_P(strtoimax_l,libc_strtol_l,ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG___ */
#if defined(__LIBCCALL_IS_LIBDCALL) && __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG___
DEFINE_PUBLIC_ALIAS_P(_strtoimax_l,libc_strtol_l,ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __LIBCCALL_IS_LIBDCALL && __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG___ */
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_strtol_l,libc_strtol_l,ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__strtol_l,libc_strtol_l,ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(strtol_l,libc_strtol_l,ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG___
DEFINE_PUBLIC_ALIAS_P(strtoumax_l,libc_strtoul_l,ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG___ */
#if defined(__LIBCCALL_IS_LIBDCALL) && __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG___
DEFINE_PUBLIC_ALIAS_P(_strtoumax_l,libc_strtoul_l,ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __LIBCCALL_IS_LIBDCALL && __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG___ */
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_strtoul_l,libc_strtoul_l,ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__strtoul_l,libc_strtoul_l,ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(strtoul_l,libc_strtoul_l,ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG___ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG___
DEFINE_PUBLIC_ALIAS_P(strtoimax_l,libc_strtoll_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG___ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG___ */
#if defined(__LIBCCALL_IS_LIBDCALL) && __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG___ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG___
DEFINE_PUBLIC_ALIAS_P(_strtoimax_l,libc_strtoll_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __LIBCCALL_IS_LIBDCALL && __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG___ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG___ */
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_strtoll_l,libc_strtoll_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__strtoll_l,libc_strtoll_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(strtoll_l,libc_strtoll_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG___ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG___
DEFINE_PUBLIC_ALIAS_P(strtoumax_l,libc_strtoull_l,ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG___ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG___ */
#if defined(__LIBCCALL_IS_LIBDCALL) && __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG___ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG___
DEFINE_PUBLIC_ALIAS_P(_strtoumax_l,libc_strtoull_l,ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __LIBCCALL_IS_LIBDCALL && __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG___ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG___ */
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_strtoull_l,libc_strtoull_l,ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__strtoull_l,libc_strtoull_l,ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(strtoull_l,libc_strtoull_l,ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_strtod_l,libc_strtod_l,ATTR_IN(1) ATTR_OUT_OPT(2),double,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, locale_t locale),(nptr,endptr,locale));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__strtod_l,libc_strtod_l,ATTR_IN(1) ATTR_OUT_OPT(2),double,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(strtod_l,libc_strtod_l,ATTR_IN(1) ATTR_OUT_OPT(2),double,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, locale_t locale),(nptr,endptr,locale));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_strtof_l,libc_strtof_l,ATTR_IN(1) ATTR_OUT_OPT(2),float,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, locale_t locale),(nptr,endptr,locale));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__strtof_l,libc_strtof_l,ATTR_IN(1) ATTR_OUT_OPT(2),float,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(strtof_l,libc_strtof_l,ATTR_IN(1) ATTR_OUT_OPT(2),float,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, locale_t locale),(nptr,endptr,locale));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_strtold_l,libc_strtold_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGDOUBLE,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, locale_t locale),(nptr,endptr,locale));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__strtold_l,libc_strtold_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGDOUBLE,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(strtold_l,libc_strtold_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGDOUBLE,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, char **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__secure_getenv,libd_secure_getenv,WUNUSED ATTR_IN(1),char *,NOTHROW_NCX,LIBDCALL,(char const *varname),(varname));
DEFINE_PUBLIC_ALIAS_P(DOS$__libc_secure_getenv,libd_secure_getenv,WUNUSED ATTR_IN(1),char *,NOTHROW_NCX,LIBDCALL,(char const *varname),(varname));
DEFINE_PUBLIC_ALIAS_P(DOS$secure_getenv,libd_secure_getenv,WUNUSED ATTR_IN(1),char *,NOTHROW_NCX,LIBDCALL,(char const *varname),(varname));
DEFINE_PUBLIC_ALIAS_P(__secure_getenv,libc_secure_getenv,WUNUSED ATTR_IN(1),char *,NOTHROW_NCX,LIBCCALL,(char const *varname),(varname));
DEFINE_PUBLIC_ALIAS_P(__libc_secure_getenv,libc_secure_getenv,WUNUSED ATTR_IN(1),char *,NOTHROW_NCX,LIBCCALL,(char const *varname),(varname));
DEFINE_PUBLIC_ALIAS_P(secure_getenv,libc_secure_getenv,WUNUSED ATTR_IN(1),char *,NOTHROW_NCX,LIBCCALL,(char const *varname),(varname));
DEFINE_PUBLIC_ALIAS_P(shexec,libc_shexec,ATTR_IN_OPT(1),int,NOTHROW_RPC,LIBCCALL,(char const *command),(command));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_ABORTF)
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$abortf,libd_abortf,ATTR_NORETURN ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2),,VLIBDCALL,(char const *format, ...),(format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ && !LIBC_ARCH_HAVE_ABORTF */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_ABORTF)
DEFINE_PUBLIC_ALIAS_P_VOID(abortf,libc_abortf,ATTR_NORETURN ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2),,VLIBCCALL,(char const *format, ...),(format,));
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_ABORTF */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(DOS$getexecname,libd_getexecname,ATTR_CONST WUNUSED,char const *,NOTHROW,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(getexecname,libc_getexecname,ATTR_CONST WUNUSED,char const *,NOTHROW,LIBCCALL,(void),());
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$fdwalk,libd_fdwalk,NONNULL((1)),int,NOTHROW_CB_NCX,LIBDCALL,(int (LIBDCALL *walk)(void *arg, fd_t fd), void *arg),(walk,arg));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(fdwalk,libc_fdwalk,NONNULL((1)),int,NOTHROW_CB_NCX,LIBCCALL,(int (LIBCCALL *walk)(void *arg, fd_t fd), void *arg),(walk,arg));
DEFINE_PUBLIC_ALIAS_P(lltostr,libc_lltostr,ATTR_RETNONNULL WUNUSED ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(__LONGLONG value, char *buf),(value,buf));
DEFINE_PUBLIC_ALIAS_P(ulltostr,libc_ulltostr,ATTR_RETNONNULL WUNUSED ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(__ULONGLONG value, char *buf),(value,buf));
DEFINE_PUBLIC_ALIAS_P(reallocf,libc_reallocf,ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)),void *,NOTHROW_NCX,LIBCCALL,(void *mallptr, size_t num_bytes),(mallptr,num_bytes));
DEFINE_PUBLIC_ALIAS_P(recallocarray,libc_recallocarray,ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((3, 4)),void *,NOTHROW_NCX,LIBCCALL,(void *mallptr, size_t old_elem_count, size_t new_elem_count, size_t elem_size),(mallptr,old_elem_count,new_elem_count,elem_size));
DEFINE_PUBLIC_ALIAS_P_VOID(freezero,libc_freezero,,NOTHROW_NCX,LIBCCALL,(void *mallptr, size_t num_bytes),(mallptr,num_bytes));
DEFINE_PUBLIC_ALIAS_P(daemonfd,libc_daemonfd,,int,NOTHROW_RPC,LIBCCALL,(fd_t chdirfd, fd_t nullfd),(chdirfd,nullfd));
DEFINE_PUBLIC_ALIAS_P(l64a_r,libc_l64a_r,,int,NOTHROW_NCX,LIBCCALL,(long n, char *buf, __STDC_INT_AS_SIZE_T bufsize),(n,buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(getprogname,libc_getprogname,ATTR_CONST WUNUSED,char const *,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P_VOID(setprogname,libc_setprogname,,NOTHROW_NCX,LIBCCALL,(char const *name),(name));
DEFINE_PUBLIC_ALIAS_P(heapsort,libc_heapsort,ATTR_INOUT_OPT(1) NONNULL((4)),int,NOTHROW_CB_NCX,LIBCCALL,(void *pbase, size_t item_count, size_t item_size, int (LIBCCALL *compar)(void const *a, void const *b)),(pbase,item_count,item_size,compar));
DEFINE_PUBLIC_ALIAS_P(mergesort,libc_mergesort,ATTR_INOUT_OPT(1) NONNULL((4)),int,NOTHROW_CB_NCX,LIBCCALL,(void *pbase, size_t item_count, size_t item_size, int (LIBCCALL *compar)(void const *a, void const *b)),(pbase,item_count,item_size,compar));
DEFINE_PUBLIC_ALIAS_P(strtonum,libc_strtonum,WUNUSED ATTR_IN(1) ATTR_OUT(4),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *nptr, __LONGLONG lo, __LONGLONG hi, char const **p_errstr),(nptr,lo,hi,p_errstr));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$_quicksort,libd_qsort_r,ATTR_INOUT_OPT(1) NONNULL((4)),NOTHROW_CB_NCX,LIBDCALL,(void *pbase, size_t item_count, size_t item_size, int (LIBDCALL *compar)(void const *a, void const *b, void *arg), void *arg),(pbase,item_count,item_size,compar,arg));
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$qsort_r,libd_qsort_r,ATTR_INOUT_OPT(1) NONNULL((4)),NOTHROW_CB_NCX,LIBDCALL,(void *pbase, size_t item_count, size_t item_size, int (LIBDCALL *compar)(void const *a, void const *b, void *arg), void *arg),(pbase,item_count,item_size,compar,arg));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P_VOID(_quicksort,libc_qsort_r,ATTR_INOUT_OPT(1) NONNULL((4)),NOTHROW_CB_NCX,LIBCCALL,(void *pbase, size_t item_count, size_t item_size, int (LIBCCALL *compar)(void const *a, void const *b, void *arg), void *arg),(pbase,item_count,item_size,compar,arg));
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS_P_VOID(qsort_r,libc_qsort_r,ATTR_INOUT_OPT(1) NONNULL((4)),NOTHROW_CB_NCX,LIBCCALL,(void *pbase, size_t item_count, size_t item_size, int (LIBCCALL *compar)(void const *a, void const *b, void *arg), void *arg),(pbase,item_count,item_size,compar,arg));
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(mkostemp,libc_mkostemp,WUNUSED ATTR_INOUT(1),fd_t,NOTHROW_NCX,LIBCCALL,(char *template_, oflag_t flags),(template_,flags));
DEFINE_PUBLIC_ALIAS_P(mkostemps,libc_mkostemps,WUNUSED ATTR_INOUT(1),fd_t,NOTHROW_NCX,LIBCCALL,(char *template_, __STDC_INT_AS_SIZE_T suffixlen, oflag_t flags),(template_,suffixlen,flags));
DEFINE_PUBLIC_ALIAS_P(mkostemp64,libc_mkostemp64,WUNUSED ATTR_INOUT(1),fd_t,NOTHROW_NCX,LIBCCALL,(char *template_, oflag_t flags),(template_,flags));
DEFINE_PUBLIC_ALIAS_P(mkostemps64,libc_mkostemps64,WUNUSED ATTR_INOUT(1),fd_t,NOTHROW_NCX,LIBCCALL,(char *template_, __STDC_INT_AS_SIZE_T suffixlen, oflag_t flags),(template_,suffixlen,flags));
DEFINE_PUBLIC_ALIAS_P(devname,libc_devname,,char *,NOTHROW_NCX,LIBCCALL,(dev_t dev, mode_t type),(dev,type));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$setproctitle,libd_setproctitle,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2),NOTHROW_NCX,VLIBDCALL,(char const *format, ...),(format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P_VOID(setproctitle,libc_setproctitle,ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2),NOTHROW_NCX,VLIBCCALL,(char const *format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(reallocarr,libc_reallocarr,WUNUSED,int,NOTHROW_NCX,LIBCCALL,(void *ptr_p, size_t elem_count, size_t elem_size),(ptr_p,elem_count,elem_size));
DEFINE_PUBLIC_ALIAS_P(strsuftoll,libc_strsuftoll,WUNUSED ATTR_IN(1) ATTR_IN(2),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *desc, char const *val, __LONGLONG lo, __LONGLONG hi),(desc,val,lo,hi));
DEFINE_PUBLIC_ALIAS_P(strsuftollx,libc_strsuftollx,WUNUSED ATTR_IN(1) ATTR_IN(2),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *desc, char const *val, __LONGLONG lo, __LONGLONG hi, char *errbuf, size_t errbuflen),(desc,val,lo,hi,errbuf,errbuflen));
DEFINE_PUBLIC_ALIAS_P(__p_program_invocation_name,libc___p__pgmptr,ATTR_CONST ATTR_RETNONNULL WUNUSED,char **,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__p__pgmptr,libc___p__pgmptr,ATTR_CONST ATTR_RETNONNULL WUNUSED,char **,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_get_pgmptr,libc__get_pgmptr,ATTR_OUT(1),errno_t,NOTHROW_NCX,LIBCCALL,(char **pvalue),(pvalue));
DEFINE_PUBLIC_ALIAS_P(DOS$_get_wpgmptr,libd__get_wpgmptr,ATTR_OUT(1),errno_t,NOTHROW_NCX,LIBDCALL,(char16_t **pvalue),(pvalue));
DEFINE_PUBLIC_ALIAS_P(_get_wpgmptr,libc__get_wpgmptr,ATTR_OUT(1),errno_t,NOTHROW_NCX,LIBKCALL,(char32_t **pvalue),(pvalue));
#if __SIZEOF_INT__ != 8 && __SIZEOF_LONG__ != 8 && __SIZEOF_LONG_LONG__ != 8 && __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS_P(imaxabs,libc__abs64,ATTR_CONST WUNUSED,__INT64_TYPE__,NOTHROW,LIBCCALL,(__INT64_TYPE__ x),(x));
#endif /* __SIZEOF_INT__ != 8 && __SIZEOF_LONG__ != 8 && __SIZEOF_LONG_LONG__ != 8 && __SIZEOF_INTMAX_T__ == 8 */
DEFINE_PUBLIC_ALIAS_P(_abs64,libc__abs64,ATTR_CONST WUNUSED,__INT64_TYPE__,NOTHROW,LIBCCALL,(__INT64_TYPE__ x),(x));
DEFINE_PUBLIC_ALIAS_P(_atof_l,libc__atof_l,ATTR_PURE WUNUSED ATTR_IN(1),double,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, locale_t locale),(nptr,locale));
DEFINE_PUBLIC_ALIAS_P(_atoi_l,libc__atoi_l,ATTR_PURE WUNUSED ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, locale_t locale),(nptr,locale));
DEFINE_PUBLIC_ALIAS_P(_atol_l,libc__atol_l,ATTR_PURE WUNUSED ATTR_IN(1),long int,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, locale_t locale),(nptr,locale));
DEFINE_PUBLIC_ALIAS_P(_atoll_l,libc__atoll_l,ATTR_PURE WUNUSED ATTR_IN(1),__LONGLONG,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, locale_t locale),(nptr,locale));
DEFINE_PUBLIC_ALIAS_P(_byteswap_ushort,libc__byteswap_ushort,ATTR_CONST WUNUSED,u16,NOTHROW,LIBCCALL,(u16 val),(val));
DEFINE_PUBLIC_ALIAS_P(_byteswap_ulong,libc__byteswap_ulong,ATTR_CONST WUNUSED,u32,NOTHROW,LIBCCALL,(u32 val),(val));
DEFINE_PUBLIC_ALIAS_P(_byteswap_uint64,libc__byteswap_uint64,ATTR_CONST WUNUSED,u64,NOTHROW,LIBCCALL,(u64 val),(val));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$bsearch_s,libd_bsearch_s,WUNUSED ATTR_IN(1) ATTR_IN_OPT(2) NONNULL((5)),void *,NOTHROW_CB_NCX,LIBDCALL,(void const *key, void const *base, size_t elem_count, size_t elem_size, int (LIBDCALL *compar)(void *arg, void const *a, void const *b), void *arg),(key,base,elem_count,elem_size,compar,arg));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(bsearch_s,libc_bsearch_s,WUNUSED ATTR_IN(1) ATTR_IN_OPT(2) NONNULL((5)),void *,NOTHROW_CB_NCX,LIBCCALL,(void const *key, void const *base, size_t elem_count, size_t elem_size, int (LIBCCALL *compar)(void *arg, void const *a, void const *b), void *arg),(key,base,elem_count,elem_size,compar,arg));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$qsort_s,libd_qsort_s,ATTR_INOUT_OPT(1) NONNULL((4)),NOTHROW_CB_NCX,LIBDCALL,(void *base, size_t elem_count, size_t elem_size, int (LIBDCALL *compar)(void *arg, void const *a, void const *b), void *arg),(base,elem_count,elem_size,compar,arg));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P_VOID(qsort_s,libc_qsort_s,ATTR_INOUT_OPT(1) NONNULL((4)),NOTHROW_CB_NCX,LIBCCALL,(void *base, size_t elem_count, size_t elem_size, int (LIBCCALL *compar)(void *arg, void const *a, void const *b), void *arg),(base,elem_count,elem_size,compar,arg));
DEFINE_PUBLIC_ALIAS_P(DOS$getenv_s,libd_getenv_s,ATTR_IN(4) ATTR_OUT(1) ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBDCALL,(size_t *preqsize, char *buf, rsize_t bufsize, char const *varname),(preqsize,buf,bufsize,varname));
DEFINE_PUBLIC_ALIAS_P(getenv_s,libc_getenv_s,ATTR_IN(4) ATTR_OUT(1) ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBCCALL,(size_t *preqsize, char *buf, rsize_t bufsize, char const *varname),(preqsize,buf,bufsize,varname));
DEFINE_PUBLIC_ALIAS_P(DOS$_dupenv_s,libd__dupenv_s,ATTR_IN(3) ATTR_OUT(1) ATTR_OUT(2),errno_t,NOTHROW_NCX,LIBDCALL,(char **__restrict pbuf, size_t *pbuflen, char const *varname),(pbuf,pbuflen,varname));
DEFINE_PUBLIC_ALIAS_P(_dupenv_s,libc__dupenv_s,ATTR_IN(3) ATTR_OUT(1) ATTR_OUT(2),errno_t,NOTHROW_NCX,LIBCCALL,(char **__restrict pbuf, size_t *pbuflen, char const *varname),(pbuf,pbuflen,varname));
DEFINE_PUBLIC_ALIAS_P(DOS$_itoa_s,libd__itoa_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBDCALL,(int val, char *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(_itoa_s,libc__itoa_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBCCALL,(int val, char *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(_ltoa_s,libc__ltoa_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBCCALL,(long val, char *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(DOS$_ultoa_s,libd__ultoa_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBDCALL,(unsigned long val, char *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(_ultoa_s,libc__ultoa_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned long val, char *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(_i64toa,libc__i64toa,ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(s64 val, char *buf, int radix),(val,buf,radix));
DEFINE_PUBLIC_ALIAS_P(_ui64toa,libc__ui64toa,ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(u64 val, char *buf, int radix),(val,buf,radix));
DEFINE_PUBLIC_ALIAS_P(DOS$_i64toa_s,libd__i64toa_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBDCALL,(s64 val, char *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(_i64toa_s,libc__i64toa_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBCCALL,(s64 val, char *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(DOS$_ui64toa_s,libd__ui64toa_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBDCALL,(u64 val, char *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(_ui64toa_s,libc__ui64toa_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBCCALL,(u64 val, char *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(_atoi64,libc__atoi64,ATTR_PURE WUNUSED ATTR_IN(1),s64,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr),(nptr));
DEFINE_PUBLIC_ALIAS_P(_atoi64_l,libc__atoi64_l,ATTR_PURE WUNUSED ATTR_IN(1),s64,NOTHROW_NCX,LIBCCALL,(char const *__restrict nptr, locale_t locale),(nptr,locale));
DEFINE_PUBLIC_ALIAS_P(_mbstrlen,libc__mbstrlen,ATTR_PURE WUNUSED ATTR_IN(1),size_t,NOTHROW_NCX,LIBCCALL,(char const *str),(str));
DEFINE_PUBLIC_ALIAS_P(_mbstrnlen,libc__mbstrnlen,ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)),size_t,NOTHROW_NCX,LIBCCALL,(char const *str, size_t maxlen),(str,maxlen));
DEFINE_PUBLIC_ALIAS_P(_mbstrlen_l,libc__mbstrlen_l,ATTR_PURE WUNUSED ATTR_IN(1),size_t,NOTHROW_NCX,LIBCCALL,(char const *str, locale_t locale),(str,locale));
DEFINE_PUBLIC_ALIAS_P(_mbstrnlen_l,libc__mbstrnlen_l,ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)),size_t,NOTHROW_NCX,LIBCCALL,(char const *str, size_t maxlen, locale_t locale),(str,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(_mblen_l,libc__mblen_l,ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)),int,NOTHROW_NCX,LIBCCALL,(char const *str, size_t maxlen, locale_t locale),(str,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_mbtowc_l,libd__mbtowc_l,,int,NOTHROW_NCX,LIBDCALL,(char16_t *dst, char const *src, size_t srclen, locale_t locale),(dst,src,srclen,locale));
DEFINE_PUBLIC_ALIAS_P(_mbtowc_l,libc__mbtowc_l,,int,NOTHROW_NCX,LIBKCALL,(char32_t *dst, char const *src, size_t srclen, locale_t locale),(dst,src,srclen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_mbstowcs_l,libd__mbstowcs_l,,size_t,NOTHROW_NCX,LIBDCALL,(char16_t *dst, char const *src, size_t dstlen, locale_t locale),(dst,src,dstlen,locale));
DEFINE_PUBLIC_ALIAS_P(_mbstowcs_l,libc__mbstowcs_l,,size_t,NOTHROW_NCX,LIBKCALL,(char32_t *dst, char const *src, size_t dstlen, locale_t locale),(dst,src,dstlen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$mbstowcs_s,libd_mbstowcs_s,,errno_t,NOTHROW_NCX,LIBDCALL,(size_t *presult, char16_t *dst, size_t dstsize, char const *src, size_t dstlen),(presult,dst,dstsize,src,dstlen));
DEFINE_PUBLIC_ALIAS_P(mbstowcs_s,libc_mbstowcs_s,,errno_t,NOTHROW_NCX,LIBKCALL,(size_t *presult, char32_t *dst, size_t dstsize, char const *src, size_t dstlen),(presult,dst,dstsize,src,dstlen));
DEFINE_PUBLIC_ALIAS_P(DOS$_mbstowcs_s_l,libd__mbstowcs_s_l,,errno_t,NOTHROW_NCX,LIBDCALL,(size_t *presult, char16_t *dst, size_t dstsize, char const *src, size_t dstlen, locale_t locale),(presult,dst,dstsize,src,dstlen,locale));
DEFINE_PUBLIC_ALIAS_P(_mbstowcs_s_l,libc__mbstowcs_s_l,,errno_t,NOTHROW_NCX,LIBKCALL,(size_t *presult, char32_t *dst, size_t dstsize, char const *src, size_t dstlen, locale_t locale),(presult,dst,dstsize,src,dstlen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$rand_s,libd_rand_s,ATTR_OUT(1),errno_t,NOTHROW_NCX,LIBDCALL,(unsigned int *__restrict randval),(randval));
DEFINE_PUBLIC_ALIAS_P(rand_s,libc_rand_s,ATTR_OUT(1),errno_t,NOTHROW_NCX,LIBCCALL,(unsigned int *__restrict randval),(randval));
DEFINE_PUBLIC_ALIAS_P(DOS$_wctomb_l,libd__wctomb_l,,int,NOTHROW_NCX,LIBDCALL,(char *buf, char16_t wc, locale_t locale),(buf,wc,locale));
DEFINE_PUBLIC_ALIAS_P(_wctomb_l,libc__wctomb_l,,int,NOTHROW_NCX,LIBKCALL,(char *buf, char32_t wc, locale_t locale),(buf,wc,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wctomb_s,libd_wctomb_s,ATTR_OUTS(2, 3) ATTR_OUT_OPT(1),errno_t,NOTHROW_NCX,LIBDCALL,(int *presult, char *buf, rsize_t buflen, char16_t wc),(presult,buf,buflen,wc));
DEFINE_PUBLIC_ALIAS_P(wctomb_s,libc_wctomb_s,ATTR_OUTS(2, 3) ATTR_OUT_OPT(1),errno_t,NOTHROW_NCX,LIBKCALL,(int *presult, char *buf, rsize_t buflen, char32_t wc),(presult,buf,buflen,wc));
DEFINE_PUBLIC_ALIAS_P(DOS$_wctomb_s_l,libd__wctomb_s_l,ATTR_OUTS(2, 3) ATTR_OUT_OPT(1),errno_t,NOTHROW_NCX,LIBDCALL,(int *presult, char *buf, size_t buflen, char16_t wc, locale_t locale),(presult,buf,buflen,wc,locale));
DEFINE_PUBLIC_ALIAS_P(_wctomb_s_l,libc__wctomb_s_l,ATTR_OUTS(2, 3) ATTR_OUT_OPT(1),errno_t,NOTHROW_NCX,LIBKCALL,(int *presult, char *buf, size_t buflen, char32_t wc, locale_t locale),(presult,buf,buflen,wc,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstombs_s_l,libd__wcstombs_s_l,ATTR_INS(4, 5) ATTR_OUTS(2, 3) ATTR_OUT_OPT(1),errno_t,NOTHROW_NCX,LIBDCALL,(size_t *presult, char *buf, size_t buflen, char16_t const *src, size_t maxlen, locale_t locale),(presult,buf,buflen,src,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(_wcstombs_s_l,libc__wcstombs_s_l,ATTR_INS(4, 5) ATTR_OUTS(2, 3) ATTR_OUT_OPT(1),errno_t,NOTHROW_NCX,LIBKCALL,(size_t *presult, char *buf, size_t buflen, char32_t const *src, size_t maxlen, locale_t locale),(presult,buf,buflen,src,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstombs_l,libd__wcstombs_l,ATTR_IN(2) ATTR_OUTS(1, 3),size_t,NOTHROW_NCX,LIBDCALL,(char *dst, char16_t const *src, size_t dstlen, locale_t locale),(dst,src,dstlen,locale));
DEFINE_PUBLIC_ALIAS_P(_wcstombs_l,libc__wcstombs_l,ATTR_IN(2) ATTR_OUTS(1, 3),size_t,NOTHROW_NCX,LIBKCALL,(char *dst, char32_t const *src, size_t dstlen, locale_t locale),(dst,src,dstlen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wcstombs_s,libd_wcstombs_s,ATTR_INS(4, 5) ATTR_OUTS(2, 3) ATTR_OUT_OPT(1),errno_t,NOTHROW_NCX,LIBDCALL,(size_t *presult, char *buf, size_t buflen, char16_t const *src, size_t maxlen),(presult,buf,buflen,src,maxlen));
DEFINE_PUBLIC_ALIAS_P(wcstombs_s,libc_wcstombs_s,ATTR_INS(4, 5) ATTR_OUTS(2, 3) ATTR_OUT_OPT(1),errno_t,NOTHROW_NCX,LIBKCALL,(size_t *presult, char *buf, size_t buflen, char32_t const *src, size_t maxlen),(presult,buf,buflen,src,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$_fullpath,libd__fullpath,WUNUSED ATTR_IN(2) ATTR_OUTS(1, 3),char *,NOTHROW_RPC,LIBDCALL,(char *buf, char const *path, size_t buflen),(buf,path,buflen));
DEFINE_PUBLIC_ALIAS_P(_fullpath,libc__fullpath,WUNUSED ATTR_IN(2) ATTR_OUTS(1, 3),char *,NOTHROW_RPC,LIBCCALL,(char *buf, char const *path, size_t buflen),(buf,path,buflen));
DEFINE_PUBLIC_ALIAS_P(DOS$_ecvt_s,libd__ecvt_s,ATTR_OUT(5) ATTR_OUT(6) ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBDCALL,(char *buf, size_t buflen, double val, int ndigit, int *__restrict decptr, int *__restrict sign),(buf,buflen,val,ndigit,decptr,sign));
DEFINE_PUBLIC_ALIAS_P(_ecvt_s,libc__ecvt_s,ATTR_OUT(5) ATTR_OUT(6) ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(char *buf, size_t buflen, double val, int ndigit, int *__restrict decptr, int *__restrict sign),(buf,buflen,val,ndigit,decptr,sign));
DEFINE_PUBLIC_ALIAS_P(DOS$_fcvt_s,libd__fcvt_s,ATTR_OUT(5) ATTR_OUT(6) ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBDCALL,(char *buf, size_t buflen, double val, int ndigit, int *__restrict decptr, int *__restrict sign),(buf,buflen,val,ndigit,decptr,sign));
DEFINE_PUBLIC_ALIAS_P(_fcvt_s,libc__fcvt_s,ATTR_OUT(5) ATTR_OUT(6) ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(char *buf, size_t buflen, double val, int ndigit, int *__restrict decptr, int *__restrict sign),(buf,buflen,val,ndigit,decptr,sign));
DEFINE_PUBLIC_ALIAS_P(DOS$_gcvt_s,libd__gcvt_s,ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBDCALL,(char *buf, size_t buflen, double val, int ndigit),(buf,buflen,val,ndigit));
DEFINE_PUBLIC_ALIAS_P(_gcvt_s,libc__gcvt_s,ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(char *buf, size_t buflen, double val, int ndigit),(buf,buflen,val,ndigit));
DEFINE_PUBLIC_ALIAS_P(_atoflt,libc__atoflt,ATTR_IN(2) ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(float *__restrict result, char const *__restrict nptr),(result,nptr));
DEFINE_PUBLIC_ALIAS_P(_atoflt_l,libc__atoflt_l,ATTR_IN(2) ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(float *__restrict result, char const *__restrict nptr, locale_t locale),(result,nptr,locale));
DEFINE_PUBLIC_ALIAS_P(_atodbl,libc__atodbl,ATTR_IN(2) ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(double *__restrict result, char __KOS_FIXED_CONST *__restrict nptr),(result,nptr));
DEFINE_PUBLIC_ALIAS_P(_atodbl_l,libc__atodbl_l,ATTR_IN(2) ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(double *__restrict result, char __KOS_FIXED_CONST *__restrict nptr, locale_t locale),(result,nptr,locale));
DEFINE_PUBLIC_ALIAS_P(_atoldbl,libc__atoldbl,ATTR_IN(2) ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(__LONGDOUBLE *__restrict result, char __KOS_FIXED_CONST *__restrict nptr),(result,nptr));
DEFINE_PUBLIC_ALIAS_P(_atoldbl_l,libc__atoldbl_l,ATTR_IN(2) ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(__LONGDOUBLE *__restrict result, char __KOS_FIXED_CONST *__restrict nptr, locale_t locale),(result,nptr,locale));
DEFINE_PUBLIC_ALIAS_P(_rotl,libc__rotl,ATTR_CONST,unsigned int,NOTHROW,LIBCCALL,(unsigned int val, int shift),(val,shift));
DEFINE_PUBLIC_ALIAS_P(_rotr,libc__rotr,ATTR_CONST,unsigned int,NOTHROW,LIBCCALL,(unsigned int val, int shift),(val,shift));
DEFINE_PUBLIC_ALIAS_P(_lrotl,libc__lrotl,ATTR_CONST,unsigned long,NOTHROW,LIBCCALL,(unsigned long val, int shift),(val,shift));
DEFINE_PUBLIC_ALIAS_P(_lrotr,libc__lrotr,ATTR_CONST,unsigned long,NOTHROW,LIBCCALL,(unsigned long val, int shift),(val,shift));
DEFINE_PUBLIC_ALIAS_P(_rotl64,libc__rotl64,ATTR_CONST,u64,NOTHROW,LIBCCALL,(u64 val, int shift),(val,shift));
DEFINE_PUBLIC_ALIAS_P(_rotr64,libc__rotr64,ATTR_CONST,u64,NOTHROW,LIBCCALL,(u64 val, int shift),(val,shift));
DEFINE_PUBLIC_ALIAS_P(DOS$_putenv_s,libd__putenv_s,,errno_t,NOTHROW_NCX,LIBDCALL,(char const *varname, char const *val),(varname,val));
DEFINE_PUBLIC_ALIAS_P(_putenv_s,libc__putenv_s,,errno_t,NOTHROW_NCX,LIBCCALL,(char const *varname, char const *val),(varname,val));
DEFINE_PUBLIC_ALIAS_P_VOID(_searchenv,libc__searchenv,ATTR_IN(1) ATTR_IN(2) ATTR_OUT(3),NOTHROW_RPC,LIBCCALL,(char const *file, char const *envvar, char *__restrict resultpath),(file,envvar,resultpath));
DEFINE_PUBLIC_ALIAS_P_VOID(_makepath,libc__makepath,ATTR_IN_OPT(2) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_OUT(1),NOTHROW_NCX,LIBCCALL,(char *__restrict buf, char const *drive, char const *dir, char const *file, char const *ext),(buf,drive,dir,file,ext));
DEFINE_PUBLIC_ALIAS_P_VOID(_splitpath,libc__splitpath,ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(3) ATTR_OUT_OPT(4) ATTR_OUT_OPT(5),NOTHROW_NCX,LIBCCALL,(char const *__restrict abspath, char *drive, char *dir, char *file, char *ext),(abspath,drive,dir,file,ext));
DEFINE_PUBLIC_ALIAS_P(DOS$_makepath_s,libd__makepath_s,ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_IN_OPT(6) ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBDCALL,(char *buf, size_t buflen, char const *drive, char const *dir, char const *file, char const *ext),(buf,buflen,drive,dir,file,ext));
DEFINE_PUBLIC_ALIAS_P(_makepath_s,libc__makepath_s,ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_IN_OPT(6) ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBCCALL,(char *buf, size_t buflen, char const *drive, char const *dir, char const *file, char const *ext),(buf,buflen,drive,dir,file,ext));
DEFINE_PUBLIC_ALIAS_P(DOS$_splitpath_s,libd__splitpath_s,ATTR_IN(1) ATTR_OUTS(2, 3) ATTR_OUTS(4, 5) ATTR_OUTS(6, 7) ATTR_OUTS(8, 9),errno_t,NOTHROW_NCX,LIBDCALL,(char const *__restrict abspath, char *drive, size_t drivelen, char *dir, size_t dirlen, char *file, size_t filelen, char *ext, size_t extlen),(abspath,drive,drivelen,dir,dirlen,file,filelen,ext,extlen));
DEFINE_PUBLIC_ALIAS_P(_splitpath_s,libc__splitpath_s,ATTR_IN(1) ATTR_OUTS(2, 3) ATTR_OUTS(4, 5) ATTR_OUTS(6, 7) ATTR_OUTS(8, 9),errno_t,NOTHROW_NCX,LIBCCALL,(char const *__restrict abspath, char *drive, size_t drivelen, char *dir, size_t dirlen, char *file, size_t filelen, char *ext, size_t extlen),(abspath,drive,drivelen,dir,dirlen,file,filelen,ext,extlen));
DEFINE_PUBLIC_ALIAS_P_VOID(__crtSleep,libc__sleep,,NOTHROW_RPC,LIBCCALL,(uint32_t milli),(milli));
DEFINE_PUBLIC_ALIAS_P_VOID(_sleep,libc__sleep,,NOTHROW_RPC,LIBCCALL,(uint32_t milli),(milli));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_itoa,libc_itoa,ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(int val, char *buf, int radix),(val,buf,radix));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(itoa,libc_itoa,ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(int val, char *buf, int radix),(val,buf,radix));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_ltoa,libc_ltoa,ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(long val, char *buf, int radix),(val,buf,radix));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(ltoa,libc_ltoa,ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(long val, char *buf, int radix),(val,buf,radix));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_ultoa,libc_ultoa,ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(unsigned long val, char *buf, int radix),(val,buf,radix));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(ultoa,libc_ultoa,ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(unsigned long val, char *buf, int radix),(val,buf,radix));
DEFINE_PUBLIC_ALIAS_P(DOS$_wgetenv_s,libd__wgetenv_s,ATTR_IN(4) ATTR_OUT(1) ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBDCALL,(size_t *preqsize, char16_t *buf, rsize_t bufsize, char16_t const *varname),(preqsize,buf,bufsize,varname));
DEFINE_PUBLIC_ALIAS_P(_wgetenv_s,libc__wgetenv_s,ATTR_IN(4) ATTR_OUT(1) ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBKCALL,(size_t *preqsize, char32_t *buf, rsize_t bufsize, char32_t const *varname),(preqsize,buf,bufsize,varname));
DEFINE_PUBLIC_ALIAS_P(DOS$_wdupenv_s,libd__wdupenv_s,ATTR_IN(3) ATTR_OUT(1) ATTR_OUT(2),errno_t,NOTHROW_NCX,LIBDCALL,(char16_t **__restrict pbuf, size_t *pbuflen, char16_t const *varname),(pbuf,pbuflen,varname));
DEFINE_PUBLIC_ALIAS_P(_wdupenv_s,libc__wdupenv_s,ATTR_IN(3) ATTR_OUT(1) ATTR_OUT(2),errno_t,NOTHROW_NCX,LIBKCALL,(char32_t **__restrict pbuf, size_t *pbuflen, char32_t const *varname),(pbuf,pbuflen,varname));
DEFINE_PUBLIC_ALIAS_P(_get_environ,libc__get_environ,ATTR_OUT(1),errno_t,NOTHROW_NCX,LIBCCALL,(char ***p_environ),(p_environ));
DEFINE_PUBLIC_ALIAS_P(DOS$_get_wenviron,libd__get_wenviron,ATTR_OUT(1),errno_t,NOTHROW_NCX,LIBDCALL,(char16_t ***p_wenviron),(p_wenviron));
DEFINE_PUBLIC_ALIAS_P(_get_wenviron,libc__get_wenviron,ATTR_OUT(1),errno_t,NOTHROW_NCX,LIBKCALL,(char32_t ***p_wenviron),(p_wenviron));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_STDLIB_C */
