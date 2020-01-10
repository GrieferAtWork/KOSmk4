/* HASH CRC-32:0x35d92840 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_STDLIB_H
#define GUARD_LIBC_USER_STDLIB_H 1

#include "../api.h"
#include "../auto/stdlib.h"
#include <kos/anno.h>
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stdlib.h>

DECL_BEGIN

INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_getenv)(char const *varname);
INTDEF int NOTHROW_RPC(LIBCCALL libc_system)(char const *__restrict command);
INTDEF ATTR_NORETURN void (LIBCCALL libc_abort)(void);
INTDEF ATTR_NORETURN void (LIBCCALL libc_exit)(int status) __THROWS(...);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_atexit)(__atexit_func_t func);
INTDEF ATTR_NORETURN void (LIBCCALL libc_quick_exit)(int status) __THROWS(...);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_at_quick_exit)(__atexit_func_t func);
INTDEF ATTR_NORETURN void (LIBCCALL libc__Exit)(int status);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc_malloc)(size_t num_bytes);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_calloc)(size_t count, size_t num_bytes);
INTDEF ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc_realloc)(void *mallptr, size_t num_bytes);
INTDEF void NOTHROW_NCX(LIBCCALL libc_free)(void *mallptr);
INTDEF void NOTHROW(LIBCCALL libc_srand)(long seed);
INTDEF int NOTHROW(LIBCCALL libc_rand)(void);
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
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_on_exit)(__on_exit_func_t func, void *arg);
INTDEF int NOTHROW_NCX(LIBCCALL libc_clearenv)(void);
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_mkstemps)(char *template_, int suffixlen);
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_rpmatch)(char const *response);
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_mkstemps64)(char *template_, int suffixlen);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_rand_r)(unsigned int *__restrict pseed);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getloadavg)(double loadavg[], int nelem);
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
INTDEF WUNUSED char *NOTHROW_NCX(LIBCCALL libc_l64a)(long n);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long NOTHROW_NCX(LIBCCALL libc_a64l)(char const *s);
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink()', but will also function for
 * non-symlink paths, as well as always return an absolute (unambiguous) path
 * @param: resolved: A buffer of `PATH_MAX' bytes to-be filled with the resulting
 *                   path, or NULL to automatically `malloc()'ate and return a
 *                   buffer of sufficient size. */
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBCCALL libc_realpath)(char const *__restrict filename, char *resolved);
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `bufsize'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `bufsize' to automatically determine the required buffer size. */
INTDEF WUNUSED char *NOTHROW_RPC(LIBCCALL libc_frealpath)(fd_t fd, char *resolved, size_t bufsize);
/* Load the filesystem location of a given file handle.
 * This function behaves similar to `readlink("/proc/self/fd/%d" % fd)'
 * @param flags: Set of `0|AT_ALTPATH|AT_DOSPATH'
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `bufsize'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `bufsize' to automatically determine the required buffer size. */
INTDEF WUNUSED char *NOTHROW_RPC(LIBCCALL libc_frealpath4)(fd_t fd, char *resolved, size_t bufsize, atflag_t flags);
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_FOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `bufsize'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `bufsize' to automatically determine the required buffer size.
 * @param flags: Set of `0|AT_ALTPATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
INTDEF WUNUSED NONNULL((2)) char *NOTHROW_RPC(LIBCCALL libc_frealpathat)(fd_t dirfd, char const *filename, char *resolved, size_t bufsize, atflag_t flags);
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_setenv)(char const *varname, char const *val, int replace);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_unsetenv)(char const *varname);
INTDEF NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_mktemp)(char *template_);
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_mkstemp)(char *template_);
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_mkdtemp)(char *template_);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_setkey)(char const *key);
INTDEF int NOTHROW_NCX(LIBCCALL libc_grantpt)(fd_t fd);
INTDEF int NOTHROW_NCX(LIBCCALL libc_unlockpt)(fd_t fd);
INTDEF WUNUSED char *NOTHROW_NCX(LIBCCALL libc_ptsname)(fd_t fd);
INTDEF WUNUSED int NOTHROW_RPC(LIBCCALL libc_posix_openpt)(oflag_t oflags);
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_secure_getenv)(char const *varname);
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_ptsname_r)(fd_t fd, char *buf, size_t buflen);
INTDEF int NOTHROW_RPC(LIBCCALL libc_getpt)(void);
/* Return the result of `realpath(filename)' as a `malloc()'-allocated buffer
 * Upon error, `NULL' is returned instead */
INTDEF ATTR_MALLOC WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBCCALL libc_canonicalize_file_name)(char const *filename);
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_mkostemp)(char *template_, int flags);
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_mkostemps)(char *template_, int suffixlen, int flags);
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_mkostemp64)(char *template_, int flags);
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_mkostemps64)(char *template_, int suffixlen, int flags);
INTDEF ATTR_CONST WUNUSED errno_t *NOTHROW_NCX(LIBCCALL libc___errno_location)(void);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__get_errno)(errno_t *perr);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__set_errno)(errno_t err);
INTDEF ATTR_CONST u32 *NOTHROW_NCX(LIBCCALL libc___doserrno)(void);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__get_doserrno)(u32 *perr);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__set_doserrno)(u32 err);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED int *NOTHROW_NCX(LIBCCALL libc___p___argc)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char ***NOTHROW_NCX(LIBCCALL libc___p___argv)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t ***NOTHROW_NCX(LIBCCALL libc___p___wargv)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t ***NOTHROW_NCX(LIBDCALL libd___p___wargv)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t ***NOTHROW_NCX(LIBCCALL libc___p__wenviron)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t ***NOTHROW_NCX(LIBDCALL libd___p__wenviron)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t **NOTHROW_NCX(LIBCCALL libc___p__wpgmptr)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t **NOTHROW_NCX(LIBDCALL libd___p__wpgmptr)(void);
/* Alias for argv[0], as passed to main() */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char **NOTHROW_NCX(LIBCCALL libc___p__pgmptr)(void);
/* Access to the initial environment block */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char ***NOTHROW_NCX(LIBCCALL libc___p___initenv)(void);
/* Access to the initial environment block */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char32_t ***NOTHROW_NCX(LIBCCALL libc___p___winitenv)(void);
/* Access to the initial environment block */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char16_t ***NOTHROW_NCX(LIBDCALL libd___p___winitenv)(void);
INTDEF _purecall_handler NOTHROW_NCX(LIBCCALL libc__set_purecall_handler)(_purecall_handler __handler);
INTDEF _purecall_handler NOTHROW_NCX(LIBCCALL libc__get_purecall_handler)(void);
INTDEF _invalid_parameter_handler NOTHROW_NCX(LIBCCALL libc__set_invalid_parameter_handler)(_invalid_parameter_handler __handler);
INTDEF _invalid_parameter_handler NOTHROW_NCX(LIBCCALL libc__get_invalid_parameter_handler)(void);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__get_pgmptr)(char **pvalue);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__get_wpgmptr)(char32_t **pvalue);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__get_wpgmptr)(char16_t **pvalue);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED int *NOTHROW_NCX(LIBCCALL libc___p__fmode)(void);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__set_fmode)(int mode);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__get_fmode)(int *pmode);
INTDEF unsigned int NOTHROW_NCX(LIBCCALL libc__set_abort_behavior)(unsigned int flags, unsigned int mask);
INTDEF NONNULL((1, 2, 4)) errno_t NOTHROW_NCX(LIBCCALL libc_getenv_s)(size_t *psize, char *buf, rsize_t bufsize, char const *varname);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_NCX(LIBCCALL libc__dupenv_s)(char **__restrict pbuf, size_t *pbuflen, char const *varname);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_rand_s)(unsigned int *__restrict randval);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd_rand_s)(unsigned int *__restrict randval);
INTDEF ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBCCALL libc__recalloc)(void *mallptr, size_t count, size_t num_bytes);
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) ATTR_ALLOC_ALIGN(2) void *NOTHROW_NCX(LIBCCALL libc__aligned_malloc)(size_t num_bytes, size_t min_alignment);
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc__aligned_offset_malloc)(size_t num_bytes, size_t min_alignment, size_t offset);
INTDEF WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_ALLOC_ALIGN(3) void *NOTHROW_NCX(LIBCCALL libc__aligned_realloc)(void *aligned_mallptr, size_t newsize, size_t min_alignment);
INTDEF WUNUSED ATTR_ALLOC_SIZE((2, 3)) ATTR_ALLOC_ALIGN(4) void *NOTHROW_NCX(LIBCCALL libc__aligned_recalloc)(void *aligned_mallptr, size_t count, size_t num_bytes, size_t min_alignment);
INTDEF WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc__aligned_offset_realloc)(void *aligned_mallptr, size_t newsize, size_t min_alignment, size_t offset);
INTDEF WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBCCALL libc__aligned_offset_recalloc)(void *aligned_mallptr, size_t count, size_t num_bytes, size_t min_alignment, size_t offset);
INTDEF void NOTHROW_NCX(LIBCCALL libc__aligned_free)(void *aligned_mallptr);
INTDEF char *NOTHROW_RPC(LIBCCALL libc__fullpath)(char *buf, char const *path, size_t buflen);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__putenv_s)(char const *varname, char const *val);
INTDEF NONNULL((1, 2, 3)) void NOTHROW_RPC(LIBCCALL libc__searchenv)(char const *file, char const *envvar, char *__restrict resultpath);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_RPC(LIBCCALL libc__searchenv_s)(char const *file, char const *envvar, char *__restrict resultpath, size_t buflen);
INTDEF void NOTHROW_NCX(LIBCCALL libc__seterrormode)(int mode);
INTDEF int NOTHROW_NCX(LIBCCALL libc__set_error_mode)(int mode);
INTDEF void NOTHROW_NCX(LIBCCALL libc__beep)(unsigned int freq, unsigned int duration);
INTDEF onexit_t NOTHROW_NCX(LIBCCALL libc_onexit)(onexit_t func);
INTDEF WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc__wgetenv)(char32_t const *varname);
INTDEF WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd__wgetenv)(char16_t const *varname);
INTDEF NONNULL((1, 4)) errno_t NOTHROW_NCX(LIBCCALL libc__wgetenv_s)(size_t *return_size, char32_t *buf, size_t buflen, char32_t const *varname);
INTDEF NONNULL((1, 4)) errno_t NOTHROW_NCX(LIBDCALL libd__wgetenv_s)(size_t *return_size, char16_t *buf, size_t buflen, char16_t const *varname);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_NCX(LIBCCALL libc__wdupenv_s)(char32_t **pbuf, size_t *pbuflen, char32_t const *varname);
INTDEF NONNULL((1, 2, 3)) errno_t NOTHROW_NCX(LIBDCALL libd__wdupenv_s)(char16_t **pbuf, size_t *pbuflen, char16_t const *varname);

DECL_END

#endif /* !GUARD_LIBC_USER_STDLIB_H */
