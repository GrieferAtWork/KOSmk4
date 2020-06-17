/* HASH CRC-32:0xb655c4e9 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_STDLIB_C
#define GUARD_LIBC_AUTO_DOSABI_STDLIB_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/stdlib.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.utility.stdlib") NONNULL((1, 4)) void
(LIBDCALL libd_qsort_r)(void *pbase,
                        size_t item_count,
                        size_t item_size,
                        __compar_d_fn_t cmp,
                        void *arg) THROWS(...) {
	libc_qsort_r(pbase, item_count, item_size, cmp, arg);
}
INTERN ATTR_SECTION(".text.crt.dos.utility.stdlib") WUNUSED NONNULL((1, 2, 5)) void *
(LIBDCALL libd_bsearch_r)(void const *pkey,
                          void const *pbase,
                          size_t item_count,
                          size_t item_size,
                          __compar_d_fn_t cmp,
                          void *arg) THROWS(...) {
	return libc_bsearch_r(pkey, pbase, item_count, item_size, cmp, arg);
}
INTERN ATTR_SECTION(".text.crt.dos.utility.stdlib") NONNULL((1, 4)) void
(LIBDCALL libd_qsort)(void *pbase,
                      size_t item_count,
                      size_t item_size,
                      __compar_fn_t cmp) THROWS(...) {
	libc_qsort(pbase, item_count, item_size, cmp);
}
INTERN ATTR_SECTION(".text.crt.dos.utility.stdlib") WUNUSED NONNULL((1, 2, 5)) void *
(LIBDCALL libd_bsearch)(void const *pkey,
                        void const *pbase,
                        size_t item_count,
                        size_t item_size,
                        __compar_fn_t cmp) THROWS(...) {
	return libc_bsearch(pkey, pbase, item_count, item_size, cmp);
}
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED long
NOTHROW(LIBDCALL libd_labs)(long x) {
	return libc_labs(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED __LONGLONG
NOTHROW(LIBDCALL libd_llabs)(__LONGLONG x) {
	return libc_llabs(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED ldiv_t
NOTHROW_NCX(LIBDCALL libd_ldiv)(long numer,
                                long denom) {
	return libc_ldiv(numer, denom);
}
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED lldiv_t
NOTHROW_NCX(LIBDCALL libd_lldiv)(__LONGLONG numer,
                                 __LONGLONG denom) {
	return libc_lldiv(numer, denom);
}
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_abs)(int x) {
	return libc_abs(x);
}
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED struct __div_struct
NOTHROW_NCX(LIBDCALL libd_div)(int numer,
                               int denom) {
	return libc_div(numer, denom);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.environ") WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_getenv)(char const *varname) {
	return libc_getenv(varname);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") int
NOTHROW_NCX(LIBDCALL libd_mblen)(char const *str,
                                 size_t maxlen) {
	return libc_mblen(str, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.system") int
NOTHROW_RPC(LIBDCALL libd_system)(char const *command) {
	return libc_system(command);
}
INTERN ATTR_SECTION(".text.crt.dos.application.exit") ATTR_NORETURN void
(LIBDCALL libd_exit)(int status) THROWS(...) {
	libc_exit(status);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.process") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_atexit)(__atexit_func_t func) {
	return libc_atexit(func);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.process") ATTR_NORETURN void
(LIBDCALL libd_quick_exit)(int status) THROWS(...) {
	libc_quick_exit(status);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.process") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_at_quick_exit)(__atexit_func_t func) {
	return libc_at_quick_exit(func);
}
INTERN ATTR_SECTION(".text.crt.dos.application.exit") ATTR_NORETURN void
(LIBDCALL libd__Exit)(int status) THROWS(...) {
	libc__Exit(status);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.malloc") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((1)) void *
NOTHROW_NCX(LIBDCALL libd_malloc)(size_t num_bytes) {
	return libc_malloc(num_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.malloc") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd_calloc)(size_t count,
                                  size_t num_bytes) {
	return libc_calloc(count, num_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.malloc") ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBDCALL libd_realloc)(void *mallptr,
                                   size_t num_bytes) {
	return libc_realloc(mallptr, num_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.malloc") void
NOTHROW_NCX(LIBDCALL libd_free)(void *mallptr) {
	libc_free(mallptr);
}
INTERN ATTR_SECTION(".text.crt.dos.random") void
NOTHROW(LIBDCALL libd_srand)(long seed) {
	libc_srand(seed);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_atoi)(char const *__restrict nptr) {
	return libc_atoi(nptr);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) long
NOTHROW_NCX(LIBDCALL libd_atol)(char const *__restrict nptr) {
	return libc_atol(nptr);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBDCALL libd_atoll)(char const *__restrict nptr) {
	return libc_atoll(nptr);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_LEAF NONNULL((1)) unsigned long
NOTHROW_NCX(LIBDCALL libd_strtoul)(char const *__restrict nptr,
                                   char **endptr,
                                   int base) {
	return libc_strtoul(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_LEAF NONNULL((1)) long
NOTHROW_NCX(LIBDCALL libd_strtol)(char const *__restrict nptr,
                                  char **endptr,
                                  int base) {
	return libc_strtol(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_LEAF NONNULL((1)) __ULONGLONG
NOTHROW_NCX(LIBDCALL libd_strtoull)(char const *__restrict nptr,
                                    char **endptr,
                                    int base) {
	return libc_strtoull(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_LEAF NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBDCALL libd_strtoll)(char const *__restrict nptr,
                                   char **endptr,
                                   int base) {
	return libc_strtoll(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_LEAF WUNUSED NONNULL((1)) double
NOTHROW_NCX(LIBDCALL libd_atof)(char const *__restrict nptr) {
	return libc_atof(nptr);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_LEAF NONNULL((1)) double
NOTHROW_NCX(LIBDCALL libd_strtod)(char const *__restrict nptr,
                                  char **endptr) {
	return libc_strtod(nptr, endptr);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_LEAF NONNULL((1)) float
NOTHROW_NCX(LIBDCALL libd_strtof)(char const *__restrict nptr,
                                  char **endptr) {
	return libc_strtof(nptr, endptr);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_LEAF NONNULL((1)) __LONGDOUBLE
NOTHROW_NCX(LIBDCALL libd_strtold)(char const *__restrict nptr,
                                   char **endptr) {
	return libc_strtold(nptr, endptr);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint32_t
NOTHROW_NCX(LIBDCALL libd_strtou32)(char const *__restrict nptr,
                                    char **endptr,
                                    int base) {
	return libc_strtou32(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_LEAF NONNULL((1)) int32_t
NOTHROW_NCX(LIBDCALL libd_strto32)(char const *__restrict nptr,
                                   char **endptr,
                                   int base) {
	return libc_strto32(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint64_t
NOTHROW_NCX(LIBDCALL libd_strtou64)(char const *__restrict nptr,
                                    char **endptr,
                                    int base) {
	return libc_strtou64(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_LEAF NONNULL((1)) int64_t
NOTHROW_NCX(LIBDCALL libd_strto64)(char const *__restrict nptr,
                                   char **endptr,
                                   int base) {
	return libc_strto64(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint32_t
NOTHROW_NCX(LIBDCALL libd_strtou32_l)(char const *__restrict nptr,
                                      char **endptr,
                                      int base,
                                      locale_t locale) {
	return libc_strtou32_l(nptr, endptr, base, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_LEAF NONNULL((1)) int32_t
NOTHROW_NCX(LIBDCALL libd_strto32_l)(char const *__restrict nptr,
                                     char **endptr,
                                     int base,
                                     locale_t locale) {
	return libc_strto32_l(nptr, endptr, base, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint64_t
NOTHROW_NCX(LIBDCALL libd_strtou64_l)(char const *__restrict nptr,
                                      char **endptr,
                                      int base,
                                      locale_t locale) {
	return libc_strtou64_l(nptr, endptr, base, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_LEAF NONNULL((1)) int64_t
NOTHROW_NCX(LIBDCALL libd_strto64_l)(char const *__restrict nptr,
                                     char **endptr,
                                     int base,
                                     locale_t locale) {
	return libc_strto64_l(nptr, endptr, base, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") WUNUSED NONNULL((3)) char *
NOTHROW_NCX(LIBDCALL libd_gcvt)(double val,
                                int ndigit,
                                char *buf) {
	return libc_gcvt(val, ndigit, buf);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((3, 4, 5)) int
NOTHROW_NCX(LIBDCALL libd_ecvt_r)(double val,
                                  int ndigit,
                                  int *__restrict decptr,
                                  int *__restrict sign,
                                  char *__restrict buf,
                                  size_t len) {
	return libc_ecvt_r(val, ndigit, decptr, sign, buf, len);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((3, 4, 5)) int
NOTHROW_NCX(LIBDCALL libd_fcvt_r)(double val,
                                  int ndigit,
                                  int *__restrict decptr,
                                  int *__restrict sign,
                                  char *__restrict buf,
                                  size_t len) {
	return libc_fcvt_r(val, ndigit, decptr, sign, buf, len);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((3)) char *
NOTHROW_NCX(LIBDCALL libd_qgcvt)(__LONGDOUBLE val,
                                 int ndigit,
                                 char *buf) {
	return libc_qgcvt(val, ndigit, buf);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((3, 4, 5)) int
NOTHROW_NCX(LIBDCALL libd_qecvt_r)(__LONGDOUBLE val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign,
                                   char *__restrict buf,
                                   size_t len) {
	return libc_qecvt_r(val, ndigit, decptr, sign, buf, len);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((3, 4, 5)) int
NOTHROW_NCX(LIBDCALL libd_qfcvt_r)(__LONGDOUBLE val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign,
                                   char *__restrict buf,
                                   size_t len) {
	return libc_qfcvt_r(val, ndigit, decptr, sign, buf, len);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") WUNUSED NONNULL((3, 4)) char *
NOTHROW_NCX(LIBDCALL libd_qecvt)(__LONGDOUBLE val,
                                 int ndigit,
                                 int *__restrict decptr,
                                 int *__restrict sign) {
	return libc_qecvt(val, ndigit, decptr, sign);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") WUNUSED NONNULL((3, 4)) char *
NOTHROW_NCX(LIBDCALL libd_qfcvt)(__LONGDOUBLE val,
                                 int ndigit,
                                 int *__restrict decptr,
                                 int *__restrict sign) {
	return libc_qfcvt(val, ndigit, decptr, sign);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_drand48_r)(struct drand48_data *__restrict buffer,
                                     double *__restrict result) {
	return libc_drand48_r(buffer, result);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBDCALL libd_erand48_r)(unsigned short xsubi[3],
                                     struct drand48_data *__restrict buffer,
                                     double *__restrict result) {
	return libc_erand48_r(xsubi, buffer, result);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_lrand48_r)(struct drand48_data *__restrict buffer,
                                     long *__restrict result) {
	return libc_lrand48_r(buffer, result);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBDCALL libd_nrand48_r)(unsigned short xsubi[3],
                                     struct drand48_data *__restrict buffer,
                                     long *__restrict result) {
	return libc_nrand48_r(xsubi, buffer, result);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_mrand48_r)(struct drand48_data *__restrict buffer,
                                     long *__restrict result) {
	return libc_mrand48_r(buffer, result);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBDCALL libd_jrand48_r)(unsigned short xsubi[3],
                                     struct drand48_data *__restrict buffer,
                                     long *__restrict result) {
	return libc_jrand48_r(xsubi, buffer, result);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_srand48_r)(long seedval,
                                     struct drand48_data *buffer) {
	return libc_srand48_r(seedval, buffer);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_seed48_r)(unsigned short seed16v[3],
                                    struct drand48_data *buffer) {
	return libc_seed48_r(seed16v, buffer);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_lcong48_r)(unsigned short param[7],
                                     struct drand48_data *buffer) {
	return libc_lcong48_r(param, buffer);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_random_r)(struct random_data *__restrict buf,
                                    int32_t *__restrict result) {
	return libc_random_r(buf, result);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_srandom_r)(unsigned int seed,
                                     struct random_data *buf) {
	return libc_srandom_r(seed, buf);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((2, 4)) int
NOTHROW_NCX(LIBDCALL libd_initstate_r)(unsigned int seed,
                                       char *__restrict statebuf,
                                       size_t statelen,
                                       struct random_data *__restrict buf) {
	return libc_initstate_r(seed, statebuf, statelen, buf);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_setstate_r)(char *__restrict statebuf,
                                      struct random_data *__restrict buf) {
	return libc_setstate_r(statebuf, buf);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.process") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_on_exit)(__on_exit_func_t func,
                                   void *arg) {
	return libc_on_exit(func, arg);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_mkstemps)(char *template_,
                                    int suffixlen) {
	return libc_mkstemps(template_, suffixlen);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_rpmatch)(char const *response) {
	return libc_rpmatch(response);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_mkstemps64)(char *template_,
                                      int suffixlen) {
	return libc_mkstemps64(template_, suffixlen);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_rand_r)(unsigned int *__restrict pseed) {
	return libc_rand_r(pseed);
}
INTERN ATTR_SECTION(".text.crt.dos.system.utility") int
NOTHROW_RPC(LIBDCALL libd_getloadavg)(double loadavg[],
                                      int nelem) {
	return libc_getloadavg(loadavg, nelem);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1)) double
NOTHROW_NCX(LIBDCALL libd_erand48)(unsigned short xsubi[3]) {
	return libc_erand48(xsubi);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1)) long
NOTHROW_NCX(LIBDCALL libd_nrand48)(unsigned short xsubi[3]) {
	return libc_nrand48(xsubi);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1)) long
NOTHROW_NCX(LIBDCALL libd_jrand48)(unsigned short xsubi[3]) {
	return libc_jrand48(xsubi);
}
INTERN ATTR_SECTION(".text.crt.dos.random") void
NOTHROW_NCX(LIBDCALL libd_srand48)(long seedval) {
	libc_srand48(seedval);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1)) unsigned short *
NOTHROW_NCX(LIBDCALL libd_seed48)(unsigned short seed16v[3]) {
	return libc_seed48(seed16v);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd_lcong48)(unsigned short param[7]) {
	libc_lcong48(param);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.environ") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_putenv)(char *string) {
	return libc_putenv(string);
}
INTERN ATTR_SECTION(".text.crt.dos.random") void
NOTHROW_NCX(LIBDCALL libd_srandom)(unsigned int seed) {
	libc_srandom(seed);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((2)) char *
NOTHROW_NCX(LIBDCALL libd_initstate)(unsigned int seed,
                                     char *statebuf,
                                     size_t statelen) {
	return libc_initstate(seed, statebuf, statelen);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_setstate)(char *statebuf) {
	return libc_setstate(statebuf);
}
INTERN ATTR_SECTION(".text.crt.dos.string.encrypt") WUNUSED char *
NOTHROW_NCX(LIBDCALL libd_l64a)(long n) {
	return libc_l64a(n);
}
INTERN ATTR_SECTION(".text.crt.dos.string.encrypt") ATTR_PURE WUNUSED NONNULL((1)) long
NOTHROW_NCX(LIBDCALL libd_a64l)(char const *s) {
	return libc_a64l(s);
}
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink()', but will also function for
 * non-symlink paths, as well as always return an absolute (unambiguous) path
 * @param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
 *                   path, or NULL to automatically `malloc()'ate and return a
 *                   buffer of sufficient size. */
INTERN ATTR_SECTION(".text.crt.dos.fs.property") WUNUSED NONNULL((1)) char *
NOTHROW_RPC(LIBDCALL libd_realpath)(char const *__restrict filename,
                                    char *resolved) {
	return libc_realpath(filename, resolved);
}
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `buflen'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTERN ATTR_SECTION(".text.crt.dos.fs.property") WUNUSED char *
NOTHROW_RPC(LIBDCALL libd_frealpath)(fd_t fd,
                                     char *resolved,
                                     size_t buflen) {
	return libc_frealpath(fd, resolved, buflen);
}
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * @param flags: Set of `0|AT_ALTPATH|AT_DOSPATH'
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `buflen'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTERN ATTR_SECTION(".text.crt.dos.fs.property") WUNUSED char *
NOTHROW_RPC(LIBDCALL libd_frealpath4)(fd_t fd,
                                      char *resolved,
                                      size_t buflen,
                                      atflag_t flags) {
	return libc_frealpath4(fd, resolved, buflen, flags);
}
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_FOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `buflen'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size.
 * @param flags: Set of `0|AT_ALTPATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.property") WUNUSED NONNULL((2)) char *
NOTHROW_RPC(LIBDCALL libd_frealpathat)(fd_t dirfd,
                                       char const *filename,
                                       char *resolved,
                                       size_t buflen,
                                       atflag_t flags) {
	return libc_frealpathat(dirfd, filename, resolved, buflen, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.environ") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_setenv)(char const *varname,
                                  char const *val,
                                  int replace) {
	return libc_setenv(varname, val, replace);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.environ") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_unsetenv)(char const *varname) {
	return libc_unsetenv(varname);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_mktemp)(char *template_) {
	return libc_mktemp(template_);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") WUNUSED NONNULL((3, 4)) char *
NOTHROW_NCX(LIBDCALL libd_ecvt)(double val,
                                int ndigit,
                                int *__restrict decptr,
                                int *__restrict sign) {
	return libc_ecvt(val, ndigit, decptr, sign);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") WUNUSED NONNULL((3, 4)) char *
NOTHROW_NCX(LIBDCALL libd_fcvt)(double val,
                                int ndigit,
                                int *__restrict decptr,
                                int *__restrict sign) {
	return libc_fcvt(val, ndigit, decptr, sign);
}
INTERN ATTR_SECTION(".text.crt.dos.application.options") WUNUSED NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBDCALL libd_getsubopt)(char **__restrict optionp,
                                     char *const *__restrict tokens,
                                     char **__restrict valuep) {
	return libc_getsubopt(optionp, tokens, valuep);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_mkstemp)(char *template_) {
	return libc_mkstemp(template_);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_mkstemp64)(char *template_) {
	return libc_mkstemp64(template_);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_mkdtemp)(char *template_) {
	return libc_mkdtemp(template_);
}
INTERN ATTR_SECTION(".text.crt.dos.io.tty") int
NOTHROW_NCX(LIBDCALL libd_grantpt)(fd_t fd) {
	return libc_grantpt(fd);
}
INTERN ATTR_SECTION(".text.crt.dos.io.tty") int
NOTHROW_NCX(LIBDCALL libd_unlockpt)(fd_t fd) {
	return libc_unlockpt(fd);
}
INTERN ATTR_SECTION(".text.crt.dos.io.tty") WUNUSED char *
NOTHROW_NCX(LIBDCALL libd_ptsname)(fd_t fd) {
	return libc_ptsname(fd);
}
INTERN ATTR_SECTION(".text.crt.dos.io.tty") WUNUSED int
NOTHROW_RPC(LIBDCALL libd_posix_openpt)(oflag_t oflags) {
	return libc_posix_openpt(oflags);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((1)) long
NOTHROW_NCX(LIBDCALL libd_strtol_l)(char const *__restrict nptr,
                                    char **endptr,
                                    int base,
                                    locale_t locale) {
	return libc_strtol_l(nptr, endptr, base, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((1)) unsigned long
NOTHROW_NCX(LIBDCALL libd_strtoul_l)(char const *__restrict nptr,
                                     char **endptr,
                                     int base,
                                     locale_t locale) {
	return libc_strtoul_l(nptr, endptr, base, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBDCALL libd_strtoll_l)(char const *__restrict nptr,
                                     char **endptr,
                                     int base,
                                     locale_t locale) {
	return libc_strtoll_l(nptr, endptr, base, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((1)) __ULONGLONG
NOTHROW_NCX(LIBDCALL libd_strtoull_l)(char const *__restrict nptr,
                                      char **endptr,
                                      int base,
                                      locale_t locale) {
	return libc_strtoull_l(nptr, endptr, base, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((1)) double
NOTHROW_NCX(LIBDCALL libd_strtod_l)(char const *__restrict nptr,
                                    char **endptr,
                                    locale_t locale) {
	return libc_strtod_l(nptr, endptr, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((1)) float
NOTHROW_NCX(LIBDCALL libd_strtof_l)(char const *__restrict nptr,
                                    char **endptr,
                                    locale_t locale) {
	return libc_strtof_l(nptr, endptr, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((1)) __LONGDOUBLE
NOTHROW_NCX(LIBDCALL libd_strtold_l)(char const *__restrict nptr,
                                     char **endptr,
                                     locale_t locale) {
	return libc_strtold_l(nptr, endptr, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.environ") WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_secure_getenv)(char const *varname) {
	return libc_secure_getenv(varname);
}
INTERN ATTR_SECTION(".text.crt.dos.io.tty") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_ptsname_r)(fd_t fd,
                                     char *buf,
                                     size_t buflen) {
	return libc_ptsname_r(fd, buf, buflen);
}
/* Return the result of `realpath(filename)' as a `malloc()'-allocated buffer
 * Upon error, `NULL' is returned instead */
INTERN ATTR_SECTION(".text.crt.dos.fs.property") ATTR_MALLOC WUNUSED NONNULL((1)) char *
NOTHROW_RPC(LIBDCALL libd_canonicalize_file_name)(char const *filename) {
	return libc_canonicalize_file_name(filename);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_mkostemp)(char *template_,
                                    int flags) {
	return libc_mkostemp(template_, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_mkostemps)(char *template_,
                                     int suffixlen,
                                     int flags) {
	return libc_mkostemps(template_, suffixlen, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_mkostemp64)(char *template_,
                                      int flags) {
	return libc_mkostemp64(template_, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_mkostemps64)(char *template_,
                                       int suffixlen,
                                       int flags) {
	return libc_mkostemps64(template_, suffixlen, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.rare_helpers") ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBDCALL libd_reallocf)(void *mallptr,
                                    size_t num_bytes) {
	return libc_reallocf(mallptr, num_bytes);
}
/* Same as `recallocv(mallptr, new_elem_count, elem_size)', but also ensure that
 * when `mallptr != NULL', memory pointed to by the old `mallptr...+=old_elem_count*elem_size'
 * is explicitly freed to zero (s.a. `freezero()') when reallocation must move the memory block */
INTERN ATTR_SECTION(".text.crt.dos.heap.rare_helpers") ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((3, 4)) void *
NOTHROW_NCX(LIBDCALL libd_recallocarray)(void *mallptr,
                                         size_t old_elem_count,
                                         size_t new_elem_count,
                                         size_t elem_size) {
	return libc_recallocarray(mallptr, old_elem_count, new_elem_count, elem_size);
}
/* Same as `free(mallptr)', but also ensure that the memory region
 * described by `mallptr...+=size' is explicitly freed to zero, or
 * immediately returned to the OS, rather than being left in cache
 * while still containing its previous contents. */
INTERN ATTR_SECTION(".text.crt.dos.heap.rare_helpers") void
NOTHROW_NCX(LIBDCALL libd_freezero)(void *mallptr,
                                    size_t size) {
	libc_freezero(mallptr, size);
}
INTERN ATTR_SECTION(".text.crt.dos.errno") errno_t
NOTHROW_NCX(LIBDCALL libd__set_doserrno)(u32 err) {
	return libc__set_doserrno(err);
}
INTERN ATTR_SECTION(".text.crt.dos.errno") _purecall_handler
NOTHROW_NCX(LIBDCALL libd__set_purecall_handler)(_purecall_handler __handler) {
	return libc__set_purecall_handler(__handler);
}
INTERN ATTR_SECTION(".text.crt.dos.errno") _invalid_parameter_handler
NOTHROW_NCX(LIBDCALL libd__set_invalid_parameter_handler)(_invalid_parameter_handler __handler) {
	return libc__set_invalid_parameter_handler(__handler);
}
INTERN ATTR_SECTION(".text.crt.dos.application.init") errno_t
NOTHROW_NCX(LIBDCALL libd__get_pgmptr)(char **pvalue) {
	return libc__get_pgmptr(pvalue);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") errno_t
NOTHROW_NCX(LIBDCALL libd__set_fmode)(int mode) {
	return libc__set_fmode(mode);
}
INTERN ATTR_SECTION(".text.crt.dos.FILE.utility") errno_t
NOTHROW_NCX(LIBDCALL libd__get_fmode)(int *pmode) {
	return libc__get_fmode(pmode);
}
INTERN ATTR_SECTION(".text.crt.dos.errno") unsigned int
NOTHROW_NCX(LIBDCALL libd__set_abort_behavior)(unsigned int flags,
                                               unsigned int mask) {
	return libc__set_abort_behavior(flags, mask);
}
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED __INT64_TYPE__
NOTHROW(LIBDCALL libd__abs64)(__INT64_TYPE__ x) {
	return libc__abs64(x);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) double
NOTHROW_NCX(LIBDCALL libd__atof_l)(char const *__restrict nptr,
                                   locale_t locale) {
	return libc__atof_l(nptr, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd__atoi_l)(char const *__restrict nptr,
                                   locale_t locale) {
	return libc__atoi_l(nptr, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) long int
NOTHROW_NCX(LIBDCALL libd__atol_l)(char const *__restrict nptr,
                                   locale_t locale) {
	return libc__atol_l(nptr, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.convert") ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBDCALL libd__atoll_l)(char const *__restrict nptr,
                                    locale_t locale) {
	return libc__atoll_l(nptr, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED u16
NOTHROW_NCX(LIBDCALL libd__byteswap_ushort)(u16 val) {
	return libc__byteswap_ushort(val);
}
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED u32
NOTHROW_NCX(LIBDCALL libd__byteswap_ulong)(u32 val) {
	return libc__byteswap_ulong(val);
}
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST WUNUSED u64
NOTHROW_NCX(LIBDCALL libd__byteswap_uint64)(u64 val) {
	return libc__byteswap_uint64(val);
}
INTERN ATTR_SECTION(".text.crt.dos.utility") WUNUSED NONNULL((1, 2, 5)) void *
(LIBDCALL libd_bsearch_s)(void const *key,
                          void const *base,
                          size_t nmemb,
                          size_t size,
                          __dos_compar_d_fn_t compar,
                          void *arg) THROWS(...) {
	return libc_bsearch_s(key, base, nmemb, size, compar, arg);
}
INTERN ATTR_SECTION(".text.crt.dos.utility") NONNULL((1, 4)) void
(LIBDCALL libd_qsort_s)(void *base,
                        size_t nmemb,
                        size_t size,
                        __dos_compar_d_fn_t compar,
                        void *arg) THROWS(...) {
	libc_qsort_s(base, nmemb, size, compar, arg);
}
INTERN ATTR_SECTION(".text.crt.dos.utility") NONNULL((1, 2, 4)) errno_t
NOTHROW_NCX(LIBDCALL libd_getenv_s)(size_t *psize,
                                    char *buf,
                                    rsize_t buflen,
                                    char const *varname) {
	return libc_getenv_s(psize, buf, buflen, varname);
}
INTERN ATTR_SECTION(".text.crt.dos.utility") NONNULL((1, 2, 3)) errno_t
NOTHROW_NCX(LIBDCALL libd__dupenv_s)(char **__restrict pbuf,
                                     size_t *pbuflen,
                                     char const *varname) {
	return libc__dupenv_s(pbuf, pbuflen, varname);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBDCALL libd__itoa_s)(int val,
                                   char *buf,
                                   size_t buflen,
                                   int radix) {
	return libc__itoa_s(val, buf, buflen, radix);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBDCALL libd__ltoa_s)(long val,
                                   char *buf,
                                   size_t buflen,
                                   int radix) {
	return libc__ltoa_s(val, buf, buflen, radix);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBDCALL libd__ultoa_s)(unsigned long val,
                                    char *buf,
                                    size_t buflen,
                                    int radix) {
	return libc__ultoa_s(val, buf, buflen, radix);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) char *
NOTHROW_NCX(LIBDCALL libd__i64toa)(s64 val,
                                   char *buf,
                                   int radix) {
	return libc__i64toa(val, buf, radix);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) char *
NOTHROW_NCX(LIBDCALL libd__ui64toa)(u64 val,
                                    char *buf,
                                    int radix) {
	return libc__ui64toa(val, buf, radix);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBDCALL libd__i64toa_s)(s64 val,
                                     char *buf,
                                     size_t buflen,
                                     int radix) {
	return libc__i64toa_s(val, buf, buflen, radix);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) errno_t
NOTHROW_NCX(LIBDCALL libd__ui64toa_s)(u64 val,
                                      char *buf,
                                      size_t buflen,
                                      int radix) {
	return libc__ui64toa_s(val, buf, buflen, radix);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) s64
NOTHROW_NCX(LIBDCALL libd__atoi64)(char const *__restrict nptr) {
	return libc__atoi64(nptr);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") ATTR_PURE WUNUSED NONNULL((1)) s64
NOTHROW_NCX(LIBDCALL libd__atoi64_l)(char const *__restrict nptr,
                                     locale_t locale) {
	return libc__atoi64_l(nptr, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd__mbstrlen)(char const *str) {
	return libc__mbstrlen(str);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd__mbstrnlen)(char const *str,
                                      size_t maxlen) {
	return libc__mbstrnlen(str, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd__mbstrlen_l)(char const *str,
                                       locale_t locale) {
	return libc__mbstrlen_l(str, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd__mbstrnlen_l)(char const *str,
                                        size_t maxlen,
                                        locale_t locale) {
	return libc__mbstrnlen_l(str, maxlen, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd__mblen_l)(char const *str,
                                    size_t maxlen,
                                    locale_t locale) {
	return libc__mblen_l(str, maxlen, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.random") NONNULL((1)) errno_t
NOTHROW_NCX(LIBDCALL libd_rand_s)(unsigned int *__restrict randval) {
	return libc_rand_s(randval);
}
INTERN ATTR_SECTION(".text.crt.dos.heap") ATTR_MALLOC WUNUSED ATTR_ALLOC_ALIGN(2) ATTR_ALLOC_SIZE((1)) void *
NOTHROW_NCX(LIBDCALL libd__aligned_malloc)(size_t num_bytes,
                                           size_t min_alignment) {
	return libc__aligned_malloc(num_bytes, min_alignment);
}
INTERN ATTR_SECTION(".text.crt.dos.heap") ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) void *
NOTHROW_NCX(LIBDCALL libd__aligned_offset_malloc)(size_t num_bytes,
                                                  size_t min_alignment,
                                                  size_t offset) {
	return libc__aligned_offset_malloc(num_bytes, min_alignment, offset);
}
INTERN ATTR_SECTION(".text.crt.dos.heap") WUNUSED ATTR_ALLOC_ALIGN(3) ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBDCALL libd__aligned_realloc)(void *aligned_mallptr,
                                            size_t newsize,
                                            size_t min_alignment) {
	return libc__aligned_realloc(aligned_mallptr, newsize, min_alignment);
}
INTERN ATTR_SECTION(".text.crt.dos.heap") WUNUSED ATTR_ALLOC_ALIGN(4) ATTR_ALLOC_SIZE((2, 3)) void *
NOTHROW_NCX(LIBDCALL libd__aligned_recalloc)(void *aligned_mallptr,
                                             size_t count,
                                             size_t num_bytes,
                                             size_t min_alignment) {
	return libc__aligned_recalloc(aligned_mallptr, count, num_bytes, min_alignment);
}
INTERN ATTR_SECTION(".text.crt.dos.heap") WUNUSED ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBDCALL libd__aligned_offset_realloc)(void *aligned_mallptr,
                                                   size_t newsize,
                                                   size_t min_alignment,
                                                   size_t offset) {
	return libc__aligned_offset_realloc(aligned_mallptr, newsize, min_alignment, offset);
}
INTERN ATTR_SECTION(".text.crt.dos.heap") WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *
NOTHROW_NCX(LIBDCALL libd__aligned_offset_recalloc)(void *aligned_mallptr,
                                                    size_t count,
                                                    size_t num_bytes,
                                                    size_t min_alignment,
                                                    size_t offset) {
	return libc__aligned_offset_recalloc(aligned_mallptr, count, num_bytes, min_alignment, offset);
}
INTERN ATTR_SECTION(".text.crt.dos.heap") ATTR_PURE WUNUSED size_t
NOTHROW_NCX(LIBDCALL libd__aligned_msize)(void *aligned_mallptr,
                                          size_t min_alignment,
                                          size_t offset) {
	return libc__aligned_msize(aligned_mallptr, min_alignment, offset);
}
INTERN ATTR_SECTION(".text.crt.dos.heap") void
NOTHROW_NCX(LIBDCALL libd__aligned_free)(void *aligned_mallptr) {
	libc__aligned_free(aligned_mallptr);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") char *
NOTHROW_RPC(LIBDCALL libd__fullpath)(char *buf,
                                     char const *path,
                                     size_t buflen) {
	return libc__fullpath(buf, path, buflen);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((1, 5, 6)) errno_t
NOTHROW_NCX(LIBDCALL libd__ecvt_s)(char *buf,
                                   size_t buflen,
                                   double val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign) {
	return libc__ecvt_s(buf, buflen, val, ndigit, decptr, sign);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((1, 5, 6)) errno_t
NOTHROW_NCX(LIBDCALL libd__fcvt_s)(char *buf,
                                   size_t buflen,
                                   double val,
                                   int ndigit,
                                   int *__restrict decptr,
                                   int *__restrict sign) {
	return libc__fcvt_s(buf, buflen, val, ndigit, decptr, sign);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((1)) errno_t
NOTHROW_NCX(LIBDCALL libd__gcvt_s)(char *buf,
                                   size_t buflen,
                                   double val,
                                   int ndigit) {
	return libc__gcvt_s(buf, buflen, val, ndigit);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd__atoflt)(float *__restrict result,
                                   char const *__restrict nptr) {
	return libc__atoflt(result, nptr);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd__atoflt_l)(float *__restrict result,
                                     char const *__restrict nptr,
                                     locale_t locale) {
	return libc__atoflt_l(result, nptr, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd__atodbl)(double *__restrict result,
                                   char __KOS_FIXED_CONST *__restrict nptr) {
	return libc__atodbl(result, nptr);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd__atodbl_l)(double *__restrict result,
                                     char __KOS_FIXED_CONST *__restrict nptr,
                                     locale_t locale) {
	return libc__atodbl_l(result, nptr, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd__atoldbl)(__LONGDOUBLE *__restrict result,
                                    char __KOS_FIXED_CONST *__restrict nptr) {
	return libc__atoldbl(result, nptr);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd__atoldbl_l)(__LONGDOUBLE *__restrict result,
                                      char __KOS_FIXED_CONST *__restrict nptr,
                                      locale_t locale) {
	return libc__atoldbl_l(result, nptr, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST unsigned int
NOTHROW(LIBDCALL libd__rotl)(unsigned int val,
                             int shift) {
	return libc__rotl(val, shift);
}
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST unsigned int
NOTHROW(LIBDCALL libd__rotr)(unsigned int val,
                             int shift) {
	return libc__rotr(val, shift);
}
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST u64
NOTHROW(LIBDCALL libd__rotl64)(u64 val,
                               int shift) {
	return libc__rotl64(val, shift);
}
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST u64
NOTHROW(LIBDCALL libd__rotr64)(u64 val,
                               int shift) {
	return libc__rotr64(val, shift);
}
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST unsigned long
NOTHROW(LIBDCALL libd__lrotl)(unsigned long val,
                              int shift) {
	return libc__lrotl(val, shift);
}
INTERN ATTR_SECTION(".text.crt.dos.math.utility") ATTR_CONST unsigned long
NOTHROW(LIBDCALL libd__lrotr)(unsigned long val,
                              int shift) {
	return libc__lrotr(val, shift);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.environ") errno_t
NOTHROW_NCX(LIBDCALL libd__putenv_s)(char const *varname,
                                     char const *val) {
	return libc__putenv_s(varname, val);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1, 2, 3)) void
NOTHROW_RPC(LIBDCALL libd__searchenv)(char const *file,
                                      char const *envvar,
                                      char *__restrict resultpath) {
	libc__searchenv(file, envvar, resultpath);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1, 2, 3)) errno_t
NOTHROW_RPC(LIBDCALL libd__searchenv_s)(char const *file,
                                        char const *envvar,
                                        char *__restrict resultpath,
                                        size_t buflen) {
	return libc__searchenv_s(file, envvar, resultpath, buflen);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd__makepath)(char *__restrict buf,
                                     char const *drive,
                                     char const *dir,
                                     char const *file,
                                     char const *ext) {
	libc__makepath(buf, drive, dir, file, ext);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd__splitpath)(char const *__restrict abspath,
                                      char *drive,
                                      char *dir,
                                      char *file,
                                      char *ext) {
	libc__splitpath(abspath, drive, dir, file, ext);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1)) errno_t
NOTHROW_NCX(LIBDCALL libd__makepath_s)(char *buf,
                                       size_t buflen,
                                       char const *drive,
                                       char const *dir,
                                       char const *file,
                                       char const *ext) {
	return libc__makepath_s(buf, buflen, drive, dir, file, ext);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1)) errno_t
NOTHROW_NCX(LIBDCALL libd__splitpath_s)(char const *__restrict abspath,
                                        char *drive,
                                        size_t drivelen,
                                        char *dir,
                                        size_t dirlen,
                                        char *file,
                                        size_t filelen,
                                        char *ext,
                                        size_t extlen) {
	return libc__splitpath_s(abspath, drive, drivelen, dir, dirlen, file, filelen, ext, extlen);
}
INTERN ATTR_SECTION(".text.crt.dos.errno") void
NOTHROW_NCX(LIBDCALL libd__seterrormode)(int mode) {
	libc__seterrormode(mode);
}
INTERN ATTR_SECTION(".text.crt.dos.errno") int
NOTHROW_NCX(LIBDCALL libd__set_error_mode)(int mode) {
	return libc__set_error_mode(mode);
}
INTERN ATTR_SECTION(".text.crt.dos.system") void
NOTHROW_NCX(LIBDCALL libd__beep)(unsigned int freq,
                                 unsigned int duration) {
	libc__beep(freq, duration);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) char *
NOTHROW_NCX(LIBDCALL libd_itoa)(int val,
                                char *buf,
                                int radix) {
	return libc_itoa(val, buf, radix);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) char *
NOTHROW_NCX(LIBDCALL libd_ltoa)(long val,
                                char *buf,
                                int radix) {
	return libc_ltoa(val, buf, radix);
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.convert") NONNULL((2)) char *
NOTHROW_NCX(LIBDCALL libd_ultoa)(unsigned long val,
                                 char *buf,
                                 int radix) {
	return libc_ultoa(val, buf, radix);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.process") onexit_t
NOTHROW_NCX(LIBDCALL libd_onexit)(onexit_t func) {
	return libc_onexit(func);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$qsort_r, libd_qsort_r);
DEFINE_PUBLIC_ALIAS(DOS$bsearch_r, libd_bsearch_r);
DEFINE_PUBLIC_ALIAS(DOS$qsort, libd_qsort);
DEFINE_PUBLIC_ALIAS(DOS$bsearch, libd_bsearch);
DEFINE_PUBLIC_ALIAS(DOS$labs, libd_labs);
DEFINE_PUBLIC_ALIAS(DOS$llabs, libd_llabs);
DEFINE_PUBLIC_ALIAS(DOS$ldiv, libd_ldiv);
DEFINE_PUBLIC_ALIAS(DOS$lldiv, libd_lldiv);
DEFINE_PUBLIC_ALIAS(DOS$abs, libd_abs);
DEFINE_PUBLIC_ALIAS(DOS$div, libd_div);
DEFINE_PUBLIC_ALIAS(DOS$getenv, libd_getenv);
DEFINE_PUBLIC_ALIAS(DOS$mblen, libd_mblen);
DEFINE_PUBLIC_ALIAS(DOS$system, libd_system);
DEFINE_PUBLIC_ALIAS(DOS$exit, libd_exit);
DEFINE_PUBLIC_ALIAS(DOS$atexit, libd_atexit);
DEFINE_PUBLIC_ALIAS(DOS$quick_exit, libd_quick_exit);
DEFINE_PUBLIC_ALIAS(DOS$at_quick_exit, libd_at_quick_exit);
DEFINE_PUBLIC_ALIAS(DOS$_exit, libd__Exit);
DEFINE_PUBLIC_ALIAS(DOS$_Exit, libd__Exit);
DEFINE_PUBLIC_ALIAS(DOS$malloc, libd_malloc);
DEFINE_PUBLIC_ALIAS(DOS$calloc, libd_calloc);
DEFINE_PUBLIC_ALIAS(DOS$realloc, libd_realloc);
DEFINE_PUBLIC_ALIAS(DOS$cfree, libd_free);
DEFINE_PUBLIC_ALIAS(DOS$free, libd_free);
DEFINE_PUBLIC_ALIAS(DOS$srand, libd_srand);
DEFINE_PUBLIC_ALIAS(DOS$atoi, libd_atoi);
DEFINE_PUBLIC_ALIAS(DOS$atol, libd_atol);
DEFINE_PUBLIC_ALIAS(DOS$atoll, libd_atoll);
DEFINE_PUBLIC_ALIAS(DOS$strtoul, libd_strtoul);
DEFINE_PUBLIC_ALIAS(DOS$strtol, libd_strtol);
DEFINE_PUBLIC_ALIAS(DOS$strtouq, libd_strtoull);
DEFINE_PUBLIC_ALIAS(DOS$strtoull, libd_strtoull);
DEFINE_PUBLIC_ALIAS(DOS$strtoq, libd_strtoll);
DEFINE_PUBLIC_ALIAS(DOS$strtoll, libd_strtoll);
DEFINE_PUBLIC_ALIAS(DOS$atof, libd_atof);
DEFINE_PUBLIC_ALIAS(DOS$strtod, libd_strtod);
DEFINE_PUBLIC_ALIAS(DOS$strtof, libd_strtof);
DEFINE_PUBLIC_ALIAS(DOS$strtold, libd_strtold);
DEFINE_PUBLIC_ALIAS(DOS$strtou32, libd_strtou32);
DEFINE_PUBLIC_ALIAS(DOS$strto32, libd_strto32);
DEFINE_PUBLIC_ALIAS(DOS$_strtoui64, libd_strtou64);
DEFINE_PUBLIC_ALIAS(DOS$strtou64, libd_strtou64);
DEFINE_PUBLIC_ALIAS(DOS$_strtoi64, libd_strto64);
DEFINE_PUBLIC_ALIAS(DOS$strto64, libd_strto64);
DEFINE_PUBLIC_ALIAS(DOS$strtou32_l, libd_strtou32_l);
DEFINE_PUBLIC_ALIAS(DOS$strto32_l, libd_strto32_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtoui64_l, libd_strtou64_l);
DEFINE_PUBLIC_ALIAS(DOS$strtou64_l, libd_strtou64_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtoi64_l, libd_strto64_l);
DEFINE_PUBLIC_ALIAS(DOS$strto64_l, libd_strto64_l);
DEFINE_PUBLIC_ALIAS(DOS$_gcvt, libd_gcvt);
DEFINE_PUBLIC_ALIAS(DOS$gcvt, libd_gcvt);
DEFINE_PUBLIC_ALIAS(DOS$ecvt_r, libd_ecvt_r);
DEFINE_PUBLIC_ALIAS(DOS$fcvt_r, libd_fcvt_r);
DEFINE_PUBLIC_ALIAS(DOS$qgcvt, libd_qgcvt);
DEFINE_PUBLIC_ALIAS(DOS$qecvt_r, libd_qecvt_r);
DEFINE_PUBLIC_ALIAS(DOS$qfcvt_r, libd_qfcvt_r);
DEFINE_PUBLIC_ALIAS(DOS$_ecvt, libd_qecvt);
DEFINE_PUBLIC_ALIAS(DOS$qecvt, libd_qecvt);
DEFINE_PUBLIC_ALIAS(DOS$_fcvt, libd_qfcvt);
DEFINE_PUBLIC_ALIAS(DOS$qfcvt, libd_qfcvt);
DEFINE_PUBLIC_ALIAS(DOS$drand48_r, libd_drand48_r);
DEFINE_PUBLIC_ALIAS(DOS$erand48_r, libd_erand48_r);
DEFINE_PUBLIC_ALIAS(DOS$lrand48_r, libd_lrand48_r);
DEFINE_PUBLIC_ALIAS(DOS$nrand48_r, libd_nrand48_r);
DEFINE_PUBLIC_ALIAS(DOS$mrand48_r, libd_mrand48_r);
DEFINE_PUBLIC_ALIAS(DOS$jrand48_r, libd_jrand48_r);
DEFINE_PUBLIC_ALIAS(DOS$srand48_r, libd_srand48_r);
DEFINE_PUBLIC_ALIAS(DOS$seed48_r, libd_seed48_r);
DEFINE_PUBLIC_ALIAS(DOS$lcong48_r, libd_lcong48_r);
DEFINE_PUBLIC_ALIAS(DOS$random_r, libd_random_r);
DEFINE_PUBLIC_ALIAS(DOS$srandom_r, libd_srandom_r);
DEFINE_PUBLIC_ALIAS(DOS$initstate_r, libd_initstate_r);
DEFINE_PUBLIC_ALIAS(DOS$setstate_r, libd_setstate_r);
DEFINE_PUBLIC_ALIAS(DOS$on_exit, libd_on_exit);
DEFINE_PUBLIC_ALIAS(DOS$mkstemps, libd_mkstemps);
DEFINE_PUBLIC_ALIAS(DOS$rpmatch, libd_rpmatch);
DEFINE_PUBLIC_ALIAS(DOS$mkstemps64, libd_mkstemps64);
DEFINE_PUBLIC_ALIAS(DOS$rand_r, libd_rand_r);
DEFINE_PUBLIC_ALIAS(DOS$getloadavg, libd_getloadavg);
DEFINE_PUBLIC_ALIAS(DOS$erand48, libd_erand48);
DEFINE_PUBLIC_ALIAS(DOS$nrand48, libd_nrand48);
DEFINE_PUBLIC_ALIAS(DOS$jrand48, libd_jrand48);
DEFINE_PUBLIC_ALIAS(DOS$srand48, libd_srand48);
DEFINE_PUBLIC_ALIAS(DOS$seed48, libd_seed48);
DEFINE_PUBLIC_ALIAS(DOS$lcong48, libd_lcong48);
DEFINE_PUBLIC_ALIAS(DOS$_putenv, libd_putenv);
DEFINE_PUBLIC_ALIAS(DOS$putenv, libd_putenv);
DEFINE_PUBLIC_ALIAS(DOS$srandom, libd_srandom);
DEFINE_PUBLIC_ALIAS(DOS$initstate, libd_initstate);
DEFINE_PUBLIC_ALIAS(DOS$setstate, libd_setstate);
DEFINE_PUBLIC_ALIAS(DOS$l64a, libd_l64a);
DEFINE_PUBLIC_ALIAS(DOS$a64l, libd_a64l);
DEFINE_PUBLIC_ALIAS(DOS$realpath, libd_realpath);
DEFINE_PUBLIC_ALIAS(DOS$frealpath, libd_frealpath);
DEFINE_PUBLIC_ALIAS(DOS$frealpath4, libd_frealpath4);
DEFINE_PUBLIC_ALIAS(DOS$frealpathat, libd_frealpathat);
DEFINE_PUBLIC_ALIAS(DOS$setenv, libd_setenv);
DEFINE_PUBLIC_ALIAS(DOS$unsetenv, libd_unsetenv);
DEFINE_PUBLIC_ALIAS(DOS$__mktemp, libd_mktemp);
DEFINE_PUBLIC_ALIAS(DOS$mktemp, libd_mktemp);
DEFINE_PUBLIC_ALIAS(DOS$_ecvt, libd_ecvt);
DEFINE_PUBLIC_ALIAS(DOS$ecvt, libd_ecvt);
DEFINE_PUBLIC_ALIAS(DOS$_ecvt, libd_fcvt);
DEFINE_PUBLIC_ALIAS(DOS$fcvt, libd_fcvt);
DEFINE_PUBLIC_ALIAS(DOS$getsubopt, libd_getsubopt);
DEFINE_PUBLIC_ALIAS(DOS$mkstemp, libd_mkstemp);
DEFINE_PUBLIC_ALIAS(DOS$mkstemp64, libd_mkstemp64);
DEFINE_PUBLIC_ALIAS(DOS$mkdtemp, libd_mkdtemp);
DEFINE_PUBLIC_ALIAS(DOS$grantpt, libd_grantpt);
DEFINE_PUBLIC_ALIAS(DOS$unlockpt, libd_unlockpt);
DEFINE_PUBLIC_ALIAS(DOS$ptsname, libd_ptsname);
DEFINE_PUBLIC_ALIAS(DOS$posix_openpt, libd_posix_openpt);
DEFINE_PUBLIC_ALIAS(DOS$_strtol_l, libd_strtol_l);
DEFINE_PUBLIC_ALIAS(DOS$__strtol_l, libd_strtol_l);
DEFINE_PUBLIC_ALIAS(DOS$strtol_l, libd_strtol_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtoul_l, libd_strtoul_l);
DEFINE_PUBLIC_ALIAS(DOS$__strtoul_l, libd_strtoul_l);
DEFINE_PUBLIC_ALIAS(DOS$strtoul_l, libd_strtoul_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtoll_l, libd_strtoll_l);
DEFINE_PUBLIC_ALIAS(DOS$__strtoll_l, libd_strtoll_l);
DEFINE_PUBLIC_ALIAS(DOS$strtoll_l, libd_strtoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtoull_l, libd_strtoull_l);
DEFINE_PUBLIC_ALIAS(DOS$__strtoull_l, libd_strtoull_l);
DEFINE_PUBLIC_ALIAS(DOS$strtoull_l, libd_strtoull_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtod_l, libd_strtod_l);
DEFINE_PUBLIC_ALIAS(DOS$__strtod_l, libd_strtod_l);
DEFINE_PUBLIC_ALIAS(DOS$strtod_l, libd_strtod_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtof_l, libd_strtof_l);
DEFINE_PUBLIC_ALIAS(DOS$__strtof_l, libd_strtof_l);
DEFINE_PUBLIC_ALIAS(DOS$strtof_l, libd_strtof_l);
DEFINE_PUBLIC_ALIAS(DOS$_strtold_l, libd_strtold_l);
DEFINE_PUBLIC_ALIAS(DOS$__strtold_l, libd_strtold_l);
DEFINE_PUBLIC_ALIAS(DOS$strtold_l, libd_strtold_l);
DEFINE_PUBLIC_ALIAS(DOS$__secure_getenv, libd_secure_getenv);
DEFINE_PUBLIC_ALIAS(DOS$secure_getenv, libd_secure_getenv);
DEFINE_PUBLIC_ALIAS(DOS$ptsname_r, libd_ptsname_r);
DEFINE_PUBLIC_ALIAS(DOS$canonicalize_file_name, libd_canonicalize_file_name);
DEFINE_PUBLIC_ALIAS(DOS$mkostemp, libd_mkostemp);
DEFINE_PUBLIC_ALIAS(DOS$mkostemps, libd_mkostemps);
DEFINE_PUBLIC_ALIAS(DOS$mkostemp64, libd_mkostemp64);
DEFINE_PUBLIC_ALIAS(DOS$mkostemps64, libd_mkostemps64);
DEFINE_PUBLIC_ALIAS(DOS$reallocf, libd_reallocf);
DEFINE_PUBLIC_ALIAS(DOS$recallocarray, libd_recallocarray);
DEFINE_PUBLIC_ALIAS(DOS$freezero, libd_freezero);
DEFINE_PUBLIC_ALIAS(DOS$_set_doserrno, libd__set_doserrno);
DEFINE_PUBLIC_ALIAS(DOS$_set_purecall_handler, libd__set_purecall_handler);
DEFINE_PUBLIC_ALIAS(DOS$_set_invalid_parameter_handler, libd__set_invalid_parameter_handler);
DEFINE_PUBLIC_ALIAS(DOS$_get_pgmptr, libd__get_pgmptr);
DEFINE_PUBLIC_ALIAS(DOS$_set_fmode, libd__set_fmode);
DEFINE_PUBLIC_ALIAS(DOS$_get_fmode, libd__get_fmode);
DEFINE_PUBLIC_ALIAS(DOS$_set_abort_behavior, libd__set_abort_behavior);
DEFINE_PUBLIC_ALIAS(DOS$_abs64, libd__abs64);
DEFINE_PUBLIC_ALIAS(DOS$_atof_l, libd__atof_l);
DEFINE_PUBLIC_ALIAS(DOS$_atoi_l, libd__atoi_l);
DEFINE_PUBLIC_ALIAS(DOS$_atol_l, libd__atol_l);
DEFINE_PUBLIC_ALIAS(DOS$_atoll_l, libd__atoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_byteswap_ushort, libd__byteswap_ushort);
DEFINE_PUBLIC_ALIAS(DOS$_byteswap_ulong, libd__byteswap_ulong);
DEFINE_PUBLIC_ALIAS(DOS$_byteswap_uint64, libd__byteswap_uint64);
DEFINE_PUBLIC_ALIAS(DOS$bsearch_s, libd_bsearch_s);
DEFINE_PUBLIC_ALIAS(DOS$qsort_s, libd_qsort_s);
DEFINE_PUBLIC_ALIAS(DOS$getenv_s, libd_getenv_s);
DEFINE_PUBLIC_ALIAS(DOS$_dupenv_s, libd__dupenv_s);
DEFINE_PUBLIC_ALIAS(DOS$_itoa_s, libd__itoa_s);
DEFINE_PUBLIC_ALIAS(DOS$_ltoa_s, libd__ltoa_s);
DEFINE_PUBLIC_ALIAS(DOS$_ultoa_s, libd__ultoa_s);
DEFINE_PUBLIC_ALIAS(DOS$_i64toa, libd__i64toa);
DEFINE_PUBLIC_ALIAS(DOS$_ui64toa, libd__ui64toa);
DEFINE_PUBLIC_ALIAS(DOS$_i64toa_s, libd__i64toa_s);
DEFINE_PUBLIC_ALIAS(DOS$_ui64toa_s, libd__ui64toa_s);
DEFINE_PUBLIC_ALIAS(DOS$_atoi64, libd__atoi64);
DEFINE_PUBLIC_ALIAS(DOS$_atoi64_l, libd__atoi64_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbstrlen, libd__mbstrlen);
DEFINE_PUBLIC_ALIAS(DOS$_mbstrnlen, libd__mbstrnlen);
DEFINE_PUBLIC_ALIAS(DOS$_mbstrlen_l, libd__mbstrlen_l);
DEFINE_PUBLIC_ALIAS(DOS$_mbstrnlen_l, libd__mbstrnlen_l);
DEFINE_PUBLIC_ALIAS(DOS$_mblen_l, libd__mblen_l);
DEFINE_PUBLIC_ALIAS(DOS$rand_s, libd_rand_s);
DEFINE_PUBLIC_ALIAS(DOS$_aligned_malloc, libd__aligned_malloc);
DEFINE_PUBLIC_ALIAS(DOS$_aligned_offset_malloc, libd__aligned_offset_malloc);
DEFINE_PUBLIC_ALIAS(DOS$_aligned_realloc, libd__aligned_realloc);
DEFINE_PUBLIC_ALIAS(DOS$_aligned_recalloc, libd__aligned_recalloc);
DEFINE_PUBLIC_ALIAS(DOS$_aligned_offset_realloc, libd__aligned_offset_realloc);
DEFINE_PUBLIC_ALIAS(DOS$_aligned_offset_recalloc, libd__aligned_offset_recalloc);
DEFINE_PUBLIC_ALIAS(DOS$_aligned_msize, libd__aligned_msize);
DEFINE_PUBLIC_ALIAS(DOS$_aligned_free, libd__aligned_free);
DEFINE_PUBLIC_ALIAS(DOS$_fullpath, libd__fullpath);
DEFINE_PUBLIC_ALIAS(DOS$_ecvt_s, libd__ecvt_s);
DEFINE_PUBLIC_ALIAS(DOS$_fcvt_s, libd__fcvt_s);
DEFINE_PUBLIC_ALIAS(DOS$_gcvt_s, libd__gcvt_s);
DEFINE_PUBLIC_ALIAS(DOS$_atoflt, libd__atoflt);
DEFINE_PUBLIC_ALIAS(DOS$_atoflt_l, libd__atoflt_l);
DEFINE_PUBLIC_ALIAS(DOS$_atodbl, libd__atodbl);
DEFINE_PUBLIC_ALIAS(DOS$_atodbl_l, libd__atodbl_l);
DEFINE_PUBLIC_ALIAS(DOS$_atoldbl, libd__atoldbl);
DEFINE_PUBLIC_ALIAS(DOS$_atoldbl_l, libd__atoldbl_l);
DEFINE_PUBLIC_ALIAS(DOS$_rotl, libd__rotl);
DEFINE_PUBLIC_ALIAS(DOS$_rotr, libd__rotr);
DEFINE_PUBLIC_ALIAS(DOS$_rotl64, libd__rotl64);
DEFINE_PUBLIC_ALIAS(DOS$_rotr64, libd__rotr64);
DEFINE_PUBLIC_ALIAS(DOS$_lrotl, libd__lrotl);
DEFINE_PUBLIC_ALIAS(DOS$_lrotr, libd__lrotr);
DEFINE_PUBLIC_ALIAS(DOS$_putenv_s, libd__putenv_s);
DEFINE_PUBLIC_ALIAS(DOS$_searchenv, libd__searchenv);
DEFINE_PUBLIC_ALIAS(DOS$_searchenv_s, libd__searchenv_s);
DEFINE_PUBLIC_ALIAS(DOS$_makepath, libd__makepath);
DEFINE_PUBLIC_ALIAS(DOS$_splitpath, libd__splitpath);
DEFINE_PUBLIC_ALIAS(DOS$_makepath_s, libd__makepath_s);
DEFINE_PUBLIC_ALIAS(DOS$_splitpath_s, libd__splitpath_s);
DEFINE_PUBLIC_ALIAS(DOS$_seterrormode, libd__seterrormode);
DEFINE_PUBLIC_ALIAS(DOS$_set_error_mode, libd__set_error_mode);
DEFINE_PUBLIC_ALIAS(DOS$_beep, libd__beep);
DEFINE_PUBLIC_ALIAS(DOS$_itoa, libd_itoa);
DEFINE_PUBLIC_ALIAS(DOS$itoa, libd_itoa);
DEFINE_PUBLIC_ALIAS(DOS$_ltoa, libd_ltoa);
DEFINE_PUBLIC_ALIAS(DOS$ltoa, libd_ltoa);
DEFINE_PUBLIC_ALIAS(DOS$_ultoa, libd_ultoa);
DEFINE_PUBLIC_ALIAS(DOS$ultoa, libd_ultoa);
DEFINE_PUBLIC_ALIAS(DOS$_onexit, libd_onexit);
DEFINE_PUBLIC_ALIAS(DOS$onexit, libd_onexit);

#endif /* !GUARD_LIBC_AUTO_DOSABI_STDLIB_C */
