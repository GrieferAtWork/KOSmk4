/* HASH CRC-32:0xa5612f05 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
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
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_getenv)(char const *varname);
INTDEF ATTR_NORETURN void (LIBCCALL libc_exit)(int status) THROWS(...);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_atexit)(void (LIBCCALL *func)(void));
INTDEF ATTR_NORETURN void (LIBCCALL libc_quick_exit)(int status) THROWS(...);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_at_quick_exit)(void (LIBCCALL *func)(void));
INTDEF ATTR_NORETURN void (LIBCCALL libc__Exit)(int status) THROWS(...);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc_malloc)(size_t num_bytes);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_calloc)(size_t count, size_t num_bytes);
INTDEF ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc_realloc)(void *mallptr, size_t num_bytes);
INTDEF void NOTHROW_NCX(LIBCCALL libc_free)(void *mallptr);
INTDEF void NOTHROW(LIBCCALL libc_srand)(long seed);
INTDEF int NOTHROW(LIBCCALL libc_rand)(void);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_rand_r)(unsigned int *__restrict pseed);
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
INTDEF int NOTHROW_RPC(LIBCCALL libc_getloadavg)(double loadavg[], __STDC_INT_AS_SIZE_T nelem);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_setenv)(char const *varname, char const *val, int replace);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_unsetenv)(char const *varname);
INTDEF double NOTHROW_NCX(LIBCCALL libc_drand48)(void);
INTDEF long NOTHROW_NCX(LIBCCALL libc_lrand48)(void);
INTDEF long NOTHROW_NCX(LIBCCALL libc_mrand48)(void);
INTDEF NONNULL((1)) double NOTHROW_NCX(LIBCCALL libc_erand48)(unsigned short xsubi[3]);
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBCCALL libc_nrand48)(unsigned short xsubi[3]);
INTDEF NONNULL((1)) long NOTHROW_NCX(LIBCCALL libc_jrand48)(unsigned short xsubi[3]);
INTDEF void NOTHROW_NCX(LIBCCALL libc_srand48)(long seedval);
INTDEF NONNULL((1)) unsigned short *NOTHROW_NCX(LIBCCALL libc_seed48)(unsigned short seed16v[3]);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_lcong48)(unsigned short param[7]);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_putenv)(char *string);
INTDEF long NOTHROW_NCX(LIBCCALL libc_random)(void);
INTDEF void NOTHROW_NCX(LIBCCALL libc_srandom)(unsigned int seed);
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_initstate)(unsigned int seed, char *statebuf, size_t statelen);
INTDEF NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_setstate)(char *statebuf);
/* Load the filesystem location of a given file handle.
 * This  function behaves similar to `readlink()', but will also function for
 * non-symlink paths, as well as always return an absolute (unambiguous) path
 * @param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
 *                   path, or NULL  to automatically `malloc()'ate  and return  a
 *                   buffer of sufficient size. */
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBCCALL libc_realpath)(char const *filename, char *resolved);
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTDEF WUNUSED char *NOTHROW_RPC(LIBCCALL libc_frealpath)(fd_t fd, char *resolved, size_t buflen);
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * @param flags: Set of `0 | AT_ALTPATH | AT_DOSPATH'
 * NOTE: You  may use `AT_ALTPATH' to cause the  path to be printed in alternate
 *       representation  mode. This means  that if the  path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may  also pass  `NULL' for  `resolved' to  have a  buffer of  `buflen'
 *       bytes  automatically allocated  in the heap,  ontop of which  you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size. */
INTDEF WUNUSED char *NOTHROW_RPC(LIBCCALL libc_frealpath4)(fd_t fd, char *resolved, size_t buflen, atflag_t flags);
/* Returns the absolute filesystem path for the specified file
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
INTDEF WUNUSED NONNULL((2)) char *NOTHROW_RPC(LIBCCALL libc_frealpathat)(fd_t dirfd, char const *filename, char *resolved, size_t buflen, atflag_t flags);
INTDEF int NOTHROW_NCX(LIBCCALL libc_grantpt)(fd_t fd);
INTDEF WUNUSED fd_t NOTHROW_RPC(LIBCCALL libc_posix_openpt)(oflag_t oflags);
/* Returns the name of the PTY slave (Pseudo TTY slave)
 * associated   with   the   master   descriptor   `fd' */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_ptsname_r)(fd_t fd, char *buf, size_t buflen);
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_secure_getenv)(char const *varname);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getpt)(void);
/* Return the result of `realpath(filename)' as a `malloc()'-allocated buffer
 * Upon error, `NULL' is returned instead */
INTDEF ATTR_MALLOC WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBCCALL libc_canonicalize_file_name)(char const *filename);
/* >> recallocarray(3)
 * Same   as    `recallocv(mallptr, new_elem_count, elem_size)',   but    also   ensure    that
 * when `mallptr != NULL', memory pointed to by the old  `mallptr...+=old_elem_count*elem_size'
 * is explicitly freed to zero (s.a. `freezero()') when reallocation must move the memory block */
INTDEF ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((3, 4)) void *NOTHROW_NCX(LIBCCALL libc_recallocarray)(void *mallptr, size_t old_elem_count, size_t new_elem_count, size_t elem_size);
/* >> freezero(3)
 * Same as  `free(mallptr)', but  also ensure  that the  memory  region
 * described by `mallptr...+=num_bytes' is explicitly freed to zero, or
 * immediately returned  to the  OS, rather  than being  left in  cache
 * while still containing its previous contents. */
INTDEF void NOTHROW_NCX(LIBCCALL libc_freezero)(void *mallptr, size_t num_bytes);
INTDEF WUNUSED NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_getbsize)(int *headerlenp, __LONGPTR_TYPE__ *blocksizep);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_radixsort)(unsigned char const **base, int item_count, unsigned char const *table, unsigned endbyte);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sradixsort)(unsigned char const **base, int item_count, unsigned char const *table, unsigned endbyte);
/* >> devname(3), devname_r(3) */
INTDEF NONNULL((3)) int NOTHROW_NCX(LIBCCALL libc_devname_r)(dev_t dev, mode_t type, char *buf, size_t len);
/* >> humanize_number(3), dehumanize_number(3)
 * @param: scale: Set of `HN_GETSCALE | HN_AUTOSCALE'
 * @param: flags: Set of `HN_DECIMAL | HN_NOSPACE | HN_B | HN_DIVISOR_1000 | HN_IEC_PREFIXES' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_humanize_number)(char *buf, size_t len, int64_t bytes, char const *suffix, int scale, int flags);
/* >> humanize_number(3), dehumanize_number(3)
 * @param: scale: Set of `HN_GETSCALE | HN_AUTOSCALE'
 * @param: flags: Set of `HN_DECIMAL | HN_NOSPACE | HN_B | HN_DIVISOR_1000 | HN_IEC_PREFIXES' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_dehumanize_number)(char const *str, int64_t *size);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> setproctitle(3) */
INTDEF ATTR_LIBC_PRINTF(1, 2) void NOTHROW_NCX(VLIBDCALL libd_setproctitle)(char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> setproctitle(3) */
INTDEF ATTR_LIBC_PRINTF(1, 2) void NOTHROW_NCX(VLIBCCALL libc_setproctitle)(char const *format, ...);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__get_errno)(errno_t *perr);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__get_errno)(errno_t *perr);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__set_errno)(errno_t err);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__set_errno)(errno_t err);
INTDEF ATTR_CONST u32 *NOTHROW_NCX(LIBCCALL libc___doserrno)(void);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__get_doserrno)(u32 *perr);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__get_doserrno)(u32 *perr);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__set_doserrno)(u32 err);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED int *NOTHROW_NCX(LIBCCALL libc___p___argc)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char ***NOTHROW_NCX(LIBCCALL libc___p___argv)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t ***NOTHROW_NCX(LIBDCALL libd___p___wargv)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t ***NOTHROW_NCX(LIBKCALL libc___p___wargv)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t ***NOTHROW_NCX(LIBDCALL libd___p__wenviron)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t ***NOTHROW_NCX(LIBKCALL libc___p__wenviron)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t **NOTHROW_NCX(LIBDCALL libd___p__wpgmptr)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t **NOTHROW_NCX(LIBKCALL libc___p__wpgmptr)(void);
/* Access to the initial environment block */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char ***NOTHROW_NCX(LIBCCALL libc___p___initenv)(void);
/* Access to the initial environment block */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t ***NOTHROW_NCX(LIBDCALL libd___p___winitenv)(void);
/* Access to the initial environment block */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t ***NOTHROW_NCX(LIBKCALL libc___p___winitenv)(void);
INTDEF _purecall_handler NOTHROW_NCX(LIBCCALL libc__set_purecall_handler)(_purecall_handler __handler);
INTDEF _purecall_handler NOTHROW_NCX(LIBCCALL libc__get_purecall_handler)(void);
INTDEF _invalid_parameter_handler NOTHROW_NCX(LIBCCALL libc__set_invalid_parameter_handler)(_invalid_parameter_handler __handler);
INTDEF _invalid_parameter_handler NOTHROW_NCX(LIBCCALL libc__get_invalid_parameter_handler)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED int *NOTHROW_NCX(LIBCCALL libc___p__fmode)(void);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__set_fmode)(int mode);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__get_fmode)(int *pmode);
INTDEF unsigned int NOTHROW_NCX(LIBCCALL libc__set_abort_behavior)(unsigned int flags, unsigned int mask);
INTDEF NONNULL((1, 2, 4)) errno_t NOTHROW_NCX(LIBCCALL libc_getenv_s)(size_t *psize, char *buf, rsize_t buflen, char const *varname);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_NCX(LIBCCALL libc__dupenv_s)(char **__restrict pbuf, size_t *pbuflen, char const *varname);
INTDEF char *NOTHROW_RPC(LIBCCALL libc__fullpath)(char *buf, char const *path, size_t buflen);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_RPC(LIBCCALL libc__searchenv_s)(char const *file, char const *envvar, char *__restrict resultpath, size_t buflen);
INTDEF void NOTHROW_NCX(LIBCCALL libc__seterrormode)(int mode);
INTDEF int NOTHROW_NCX(LIBCCALL libc__set_error_mode)(int mode);
INTDEF void NOTHROW_NCX(LIBCCALL libc__beep)(unsigned int freq, unsigned int duration);
INTDEF onexit_t NOTHROW_NCX(LIBCCALL libc_onexit)(onexit_t func);
INTDEF WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd__wgetenv)(char16_t const *varname);
INTDEF WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBKCALL libc__wgetenv)(char32_t const *varname);
INTDEF NONNULL((1, 4)) errno_t NOTHROW_NCX(LIBDCALL libd__wgetenv_s)(size_t *return_size, char16_t *buf, size_t buflen, char16_t const *varname);
INTDEF NONNULL((1, 4)) errno_t NOTHROW_NCX(LIBKCALL libc__wgetenv_s)(size_t *return_size, char32_t *buf, size_t buflen, char32_t const *varname);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_NCX(LIBDCALL libd__wdupenv_s)(char16_t **pbuf, size_t *pbuflen, char16_t const *varname);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_NCX(LIBKCALL libc__wdupenv_s)(char32_t **pbuf, size_t *pbuflen, char32_t const *varname);
INTDEF char16_t *NOTHROW_NCX(LIBDCALL libd__wfullpath)(char16_t *buf, char16_t const *path, size_t buflen);
INTDEF char32_t *NOTHROW_NCX(LIBKCALL libc__wfullpath)(char32_t *buf, char32_t const *path, size_t buflen);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd__wputenv)(char16_t *string);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBKCALL libc__wputenv)(char32_t *string);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__wputenv_s)(char16_t const *varname, char16_t const *val);
INTDEF errno_t NOTHROW_NCX(LIBKCALL libc__wputenv_s)(char32_t const *varname, char32_t const *val);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_RPC(LIBDCALL libd__wsearchenv_s)(char16_t const *file, char16_t const *envvar, char16_t *__restrict resultpath, size_t buflen);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_RPC(LIBKCALL libc__wsearchenv_s)(char32_t const *file, char32_t const *envvar, char32_t *__restrict resultpath, size_t buflen);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_STDLIB_H */
