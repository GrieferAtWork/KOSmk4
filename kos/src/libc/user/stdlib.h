/* HASH CRC-32:0xd32e0609 */
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
#ifndef GUARD_LIBC_USER_STDLIB_H
#define GUARD_LIBC_USER_STDLIB_H 1

#include "../api.h"
#include "../auto/stdlib.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stdlib.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBDCALL libd_getenv)(char const *varname);
INTDEF WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBCCALL libc_getenv)(char const *varname);
INTDEF ATTR_NORETURN void (LIBCCALL libc_exit)(int status);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_atexit)(void (LIBCCALL *func)(void));
INTDEF ATTR_NORETURN void (LIBCCALL libc_quick_exit)(int status);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_at_quick_exit)(void (LIBCCALL *func)(void));
INTDEF ATTR_NORETURN void (LIBCCALL libc__Exit)(int status);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc_malloc)(size_t num_bytes);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_calloc)(size_t count, size_t num_bytes);
INTDEF ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc_realloc)(void *mallptr, size_t num_bytes);
INTDEF void NOTHROW_NCX(LIBCCALL libc_free)(void *mallptr);
INTDEF void NOTHROW(LIBCCALL libc_srand)(long seed);
INTDEF int NOTHROW(LIBCCALL libc_rand)(void);
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) __STDC_INT32_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_strfromd)(char *__restrict buf, size_t buflen, char const *__restrict format, double fp);
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) __STDC_INT32_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_strfromf)(char *__restrict buf, size_t buflen, char const *__restrict format, float fp);
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) __STDC_INT32_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_strfroml)(char *__restrict buf, size_t buflen, char const *__restrict format, __LONGDOUBLE fp);
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc_rand_r)(unsigned int *__restrict pseed);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getloadavg)(double loadavg[], __STDC_INT_AS_SIZE_T nelem);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_drand48_r)(struct drand48_data *__restrict buffer, double *__restrict result);
INTDEF NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBCCALL libc_erand48_r)(unsigned short xsubi[3], struct drand48_data *__restrict buffer, double *__restrict result);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_lrand48_r)(struct drand48_data *__restrict buffer, long *__restrict result);
INTDEF NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBCCALL libc_nrand48_r)(unsigned short xsubi[3], struct drand48_data *__restrict buffer, long *__restrict result);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_mrand48_r)(struct drand48_data *__restrict buffer, long *__restrict result);
INTDEF NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBCCALL libc_jrand48_r)(unsigned short xsubi[3], struct drand48_data *__restrict buffer, long *__restrict result);
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_srand48_r)(long seedval, struct drand48_data *buffer);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_seed48_r)(unsigned short seed16v[3], struct drand48_data *buffer);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_lcong48_r)(unsigned short param[7], struct drand48_data *buffer);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_random_r)(struct random_data *__restrict buf, int32_t *__restrict result);
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_srandom_r)(unsigned int seed, struct random_data *buf);
INTDEF NONNULL((2, 4)) int NOTHROW_NCX(LIBCCALL libc_initstate_r)(unsigned int seed, char *__restrict statebuf, size_t statelen, struct random_data *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_setstate_r)(char *__restrict statebuf, struct random_data *__restrict buf);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(__LIBCCALL_IS_LIBDCALL)
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_on_exit)(void (LIBDCALL *func)(int status, void *arg), void *arg);
#endif /* !__KERNEL__ && !__LIBCCALL_IS_LIBDCALL */
#ifndef __KERNEL__
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_on_exit)(void (LIBCCALL *func)(int status, void *arg), void *arg);
INTDEF int NOTHROW_NCX(LIBCCALL libc_clearenv)(void);
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_setenv)(char const *varname, char const *val, int replace);
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_setenv)(char const *varname, char const *val, int replace);
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd_unsetenv)(char const *varname);
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBCCALL libc_unsetenv)(char const *varname);
INTDEF double NOTHROW_NCX(LIBCCALL libc_drand48)(void);
INTDEF long NOTHROW_NCX(LIBCCALL libc_lrand48)(void);
INTDEF long NOTHROW_NCX(LIBCCALL libc_mrand48)(void);
INTDEF NONNULL((1)) double NOTHROW_NCX(LIBCCALL libc_erand48)(unsigned short xsubi[3]);
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBCCALL libc_nrand48)(unsigned short xsubi[3]);
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBCCALL libc_jrand48)(unsigned short xsubi[3]);
INTDEF void NOTHROW_NCX(LIBCCALL libc_srand48)(long seedval);
INTDEF NONNULL((1)) unsigned short *NOTHROW_NCX(LIBCCALL libc_seed48)(unsigned short seed16v[3]);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_lcong48)(unsigned short param[7]);
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_putenv)(char *string);
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc_putenv)(char *string);
INTDEF long NOTHROW_NCX(LIBCCALL libc_random)(void);
INTDEF void NOTHROW_NCX(LIBCCALL libc_srandom)(unsigned int seed);
INTDEF ATTR_OUTS(2, 3) char *NOTHROW_NCX(LIBCCALL libc_initstate)(unsigned int seed, char *statebuf, size_t statelen);
INTDEF NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_setstate)(char *statebuf);
/* >> frealpath4(2)
 * Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * @param flags: Set of `0 | AT_ALTPATH | AT_DOSPATH'
 * NOTE: You  may use `AT_ALTPATH' to cause the  path to be printed in alternate
 *       representation  mode. This means  that if the  path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTDEF WUNUSED ATTR_FDARG(1) ATTR_OUT_OPT(2) char *NOTHROW_RPC(LIBDCALL libd_frealpath4)(fd_t fd, char *resolved, size_t buflen, atflag_t flags);
/* >> frealpath4(2)
 * Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * @param flags: Set of `0 | AT_ALTPATH | AT_DOSPATH'
 * NOTE: You  may use `AT_ALTPATH' to cause the  path to be printed in alternate
 *       representation  mode. This means  that if the  path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTDEF WUNUSED ATTR_FDARG(1) ATTR_OUT_OPT(2) char *NOTHROW_RPC(LIBCCALL libc_frealpath4)(fd_t fd, char *resolved, size_t buflen, atflag_t flags);
/* >> frealpathat(2)
 * Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is not dereferenced,
 * causing the path to  the symlink itself to  be printed. - Otherwise,  the
 * file pointed to by the symblic link is printed.
 * NOTE: You  may use `AT_ALTPATH' to cause the  path to be printed in alternate
 *       representation  mode. This means  that if the  path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size.
 * @param flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH'
 * @return: NULL: [errno=ERANGE]: `buflen' is too small to fit the entire path */
INTDEF WUNUSED ATTR_IN(2) ATTR_OUT_OPT(3) char *NOTHROW_RPC(LIBDCALL libd_frealpathat)(fd_t dirfd, char const *filename, char *resolved, size_t buflen, atflag_t flags);
/* >> frealpathat(2)
 * Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is not dereferenced,
 * causing the path to  the symlink itself to  be printed. - Otherwise,  the
 * file pointed to by the symblic link is printed.
 * NOTE: You  may use `AT_ALTPATH' to cause the  path to be printed in alternate
 *       representation  mode. This means  that if the  path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size.
 * @param flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH'
 * @return: NULL: [errno=ERANGE]: `buflen' is too small to fit the entire path */
INTDEF WUNUSED ATTR_IN(2) ATTR_OUT_OPT(3) char *NOTHROW_RPC(LIBCCALL libc_frealpathat)(fd_t dirfd, char const *filename, char *resolved, size_t buflen, atflag_t flags);
INTDEF ATTR_FDARG(1) int NOTHROW_NCX(LIBCCALL libc_grantpt)(fd_t fd);
INTDEF WUNUSED fd_t NOTHROW_RPC(LIBCCALL libc_posix_openpt)(oflag_t oflags);
/* Returns the name of the PTY slave (Pseudo TTY slave)
 * associated   with   the   master   descriptor   `fd' */
INTDEF ATTR_FDARG(1) ATTR_OUTS(2, 3) int NOTHROW_NCX(LIBDCALL libd_ptsname_r)(fd_t fd, char *buf, size_t buflen);
/* Returns the name of the PTY slave (Pseudo TTY slave)
 * associated   with   the   master   descriptor   `fd' */
INTDEF ATTR_FDARG(1) ATTR_OUTS(2, 3) int NOTHROW_NCX(LIBCCALL libc_ptsname_r)(fd_t fd, char *buf, size_t buflen);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getpt)(void);
/* >> canonicalize_file_name(3)
 * Return the result of `realpath(filename)' as a `malloc()'-
 * allocated  buffer. Upon error, `NULL' is returned instead. */
INTDEF ATTR_MALLOC WUNUSED ATTR_IN(1) char *NOTHROW_RPC(LIBDCALL libd_canonicalize_file_name)(char const *filename);
/* >> canonicalize_file_name(3)
 * Return the result of `realpath(filename)' as a `malloc()'-
 * allocated  buffer. Upon error, `NULL' is returned instead. */
INTDEF ATTR_MALLOC WUNUSED ATTR_IN(1) char *NOTHROW_RPC(LIBCCALL libc_canonicalize_file_name)(char const *filename);
INTDEF WUNUSED ATTR_OUT(1) ATTR_OUT(2) char *NOTHROW_NCX(LIBCCALL libc_getbsize)(int *headerlenp, __LONGPTR_TYPE__ *blocksizep);
INTDEF ATTR_INOUTS(1, 2) ATTR_IN_OPT(3) int NOTHROW_NCX(LIBCCALL libc_radixsort)(unsigned char const **base, int item_count, unsigned char const table[256], unsigned endbyte);
INTDEF ATTR_INOUTS(1, 2) ATTR_IN_OPT(3) int NOTHROW_NCX(LIBCCALL libc_sradixsort)(unsigned char const **base, int item_count, unsigned char const table[256], unsigned endbyte);
/* >> devname(3), devname_r(3) */
INTDEF ATTR_OUTS(3, 4) int NOTHROW_NCX(LIBCCALL libc_devname_r)(dev_t dev, mode_t type, char *buf, size_t len);
/* >> humanize_number(3), dehumanize_number(3)
 * @param: scale: Set of `HN_GETSCALE | HN_AUTOSCALE'
 * @param: flags: Set of `HN_DECIMAL | HN_NOSPACE | HN_B | HN_DIVISOR_1000 | HN_IEC_PREFIXES' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_humanize_number)(char *buf, size_t len, int64_t bytes, char const *suffix, int scale, int flags);
/* >> humanize_number(3), dehumanize_number(3)
 * @param: scale: Set of `HN_GETSCALE | HN_AUTOSCALE'
 * @param: flags: Set of `HN_DECIMAL | HN_NOSPACE | HN_B | HN_DIVISOR_1000 | HN_IEC_PREFIXES' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_dehumanize_number)(char const *str, int64_t *size);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__get_errno)(errno_t *perr);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__get_errno)(errno_t *perr);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__set_errno)(errno_t err);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__set_errno)(errno_t err);
INTDEF ATTR_CONST u32 *NOTHROW(LIBCCALL libc___doserrno)(void);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__get_doserrno)(u32 *perr);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__get_doserrno)(u32 *perr);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__set_doserrno)(u32 err);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED int *NOTHROW(LIBCCALL libc___p___argc)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char ***NOTHROW(LIBCCALL libc___p___argv)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t ***NOTHROW(LIBDCALL libd___p___wargv)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t ***NOTHROW(LIBKCALL libc___p___wargv)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t ***NOTHROW(LIBDCALL libd___p__wenviron)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t ***NOTHROW(LIBKCALL libc___p__wenviron)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t **NOTHROW(LIBDCALL libd___p__wpgmptr)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t **NOTHROW(LIBKCALL libc___p__wpgmptr)(void);
/* Access to the initial environment block */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char ***NOTHROW(LIBDCALL libd___p___initenv)(void);
/* Access to the initial environment block */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char ***NOTHROW(LIBCCALL libc___p___initenv)(void);
/* Access to the initial environment block */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t ***NOTHROW(LIBDCALL libd___p___winitenv)(void);
/* Access to the initial environment block */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t ***NOTHROW(LIBKCALL libc___p___winitenv)(void);
INTDEF _purecall_handler NOTHROW_NCX(LIBCCALL libc__set_purecall_handler)(_purecall_handler __handler);
INTDEF _purecall_handler NOTHROW_NCX(LIBCCALL libc__get_purecall_handler)(void);
INTDEF _invalid_parameter_handler NOTHROW_NCX(LIBCCALL libc__set_invalid_parameter_handler)(_invalid_parameter_handler handler);
INTDEF _invalid_parameter_handler NOTHROW_NCX(LIBCCALL libc__get_invalid_parameter_handler)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED int *NOTHROW(LIBCCALL libc___p__fmode)(void);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__set_fmode)(int mode);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__get_fmode)(int *pmode);
INTDEF unsigned int NOTHROW_NCX(LIBCCALL libc__set_abort_behavior)(unsigned int flags, unsigned int mask);
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_OUTS(3, 4) errno_t NOTHROW_RPC(LIBCCALL libc__searchenv_s)(char const *file, char const *envvar, char *__restrict resultpath, size_t resultpath_len);
INTDEF void NOTHROW_NCX(LIBCCALL libc__seterrormode)(int mode);
INTDEF int NOTHROW_NCX(LIBCCALL libc__set_error_mode)(int mode);
INTDEF void NOTHROW_NCX(LIBCCALL libc__beep)(unsigned int freq, unsigned int duration);
INTDEF onexit_t NOTHROW_NCX(LIBCCALL libc_onexit)(onexit_t func);
INTDEF WUNUSED ATTR_IN(1) char16_t *NOTHROW_NCX(LIBDCALL libd__wgetenv)(char16_t const *varname);
INTDEF WUNUSED ATTR_IN(1) char32_t *NOTHROW_NCX(LIBKCALL libc__wgetenv)(char32_t const *varname);
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd__wputenv)(char16_t *string);
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBKCALL libc__wputenv)(char32_t *string);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__wputenv_s)(char16_t const *varname, char16_t const *val);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__wputenv_s)(char32_t const *varname, char32_t const *val);
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_OUTS(3, 4) errno_t NOTHROW_RPC(LIBDCALL libd__wsearchenv_s)(char16_t const *file, char16_t const *envvar, char16_t *__restrict resultpath, size_t resultpath_len);
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_OUTS(3, 4) errno_t NOTHROW_RPC(LIBKCALL libc__wsearchenv_s)(char32_t const *file, char32_t const *envvar, char32_t *__restrict resultpath, size_t resultpath_len);
#endif /* !__KERNEL__ */
#ifdef __clang_tidy__
#define libc_malloc(num_bytes)           __builtin_malloc(num_bytes)
#define libc_calloc(count, num_bytes)    __builtin_calloc(count, num_bytes)
#define libc_realloc(mallptr, num_bytes) __builtin_realloc(mallptr, num_bytes)
#define libc_free(mallptr)               __builtin_free(mallptr)
#endif /* __clang_tidy__ */

DECL_END

#endif /* !GUARD_LIBC_USER_STDLIB_H */
