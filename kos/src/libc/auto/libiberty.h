/* HASH CRC-32:0xfe9358f6 */
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
#ifndef GUARD_LIBC_AUTO_LIBIBERTY_H
#define GUARD_LIBC_AUTO_LIBIBERTY_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <libiberty.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBDCALL libd_C_alloca)(size_t num_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc_C_alloca)(size_t num_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_NCX(LIBDCALL libd_stack_limit_increase)(ulongptr_t newlim);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF void NOTHROW_NCX(LIBCCALL libc_stack_limit_increase)(ulongptr_t newlim);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(_WIN32)
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED const char *NOTHROW_NCX(LIBDCALL libd_dos_lbasename)(const char *filename);
#endif /* !__LIBCCALL_IS_LIBDCALL && !_WIN32 */
#ifndef _WIN32
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED const char *NOTHROW_NCX(LIBCCALL libc_dos_lbasename)(const char *filename);
#endif /* !_WIN32 */
#if !defined(__LIBCCALL_IS_LIBDCALL) && defined(_WIN32)
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED const char *NOTHROW_NCX(LIBDCALL libd_unix_lbasename)(const char *filename);
#endif /* !__LIBCCALL_IS_LIBDCALL && _WIN32 */
#ifdef _WIN32
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED const char *NOTHROW_NCX(LIBCCALL libc_unix_lbasename)(const char *filename);
#endif /* _WIN32 */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_lrealpath)(char const *path);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_lrealpath)(char const *path);
INTDEF WUNUSED char *NOTHROW_NCX(LIBCCALL libc_getpwd)(void);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_errno_max)(void);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_signo_max)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED errno_t NOTHROW_NCX(LIBDCALL libd_strtoerrno)(char const *name);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED errno_t NOTHROW_NCX(LIBCCALL libc_strtoerrno)(char const *name);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_NCX(LIBDCALL libd_unlock_stream)(FILE *fp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF void NOTHROW_NCX(LIBCCALL libc_unlock_stream)(FILE *fp);
INTDEF void NOTHROW_NCX(LIBCCALL libc_unlock_std_streams)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF FILE *NOTHROW_NCX(LIBDCALL libd_fopen_unlocked)(char const *filename, char const *mode);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF FILE *NOTHROW_NCX(LIBCCALL libc_fopen_unlocked)(char const *filename, char const *mode);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF FILE *NOTHROW_NCX(LIBDCALL libd_fdopen_unlocked)(fd_t fd, char const *mode);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF FILE *NOTHROW_NCX(LIBCCALL libc_fdopen_unlocked)(fd_t fd, char const *mode);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED char const *NOTHROW_NCX(LIBDCALL libd_spaces)(__STDC_INT_AS_SIZE_T count);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED char const *NOTHROW_NCX(LIBCCALL libc_spaces)(__STDC_INT_AS_SIZE_T count);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_NCX(LIBDCALL libd_xmalloc_set_program_name)(char const *progname);
INTDEF ATTR_NORETURN void (LIBDCALL libd_xmalloc_failed)(size_t num_bytes) THROWS(...);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBDCALL libd_xmalloc)(size_t num_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc_xmalloc)(size_t num_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBDCALL libd_xrealloc)(void *ptr, size_t num_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc_xrealloc)(void *ptr, size_t num_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((1, 2)) void *NOTHROW_NCX(LIBDCALL libd_xcalloc)(size_t elem_count, size_t elem_size);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_xcalloc)(size_t elem_count, size_t elem_size);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_xstrdup)(char const *__restrict string);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_xstrdup)(char const *__restrict string);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED char *NOTHROW_NCX(LIBDCALL libd_xstrndup)(char const *string, size_t max_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED char *NOTHROW_NCX(LIBCCALL libc_xstrndup)(char const *string, size_t max_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((3)) NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd_xmemdup)(void const *src, size_t src_bytes, size_t alloc_size);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((3)) NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_xmemdup)(void const *src, size_t src_bytes, size_t alloc_size);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strdupf(3), vstrdupf(3)
 * Print the given `format' into a newly allocated, heap-allocated string */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_xvasprintf)(const char *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strdupf(3), vstrdupf(3)
 * Print the given `format' into a newly allocated, heap-allocated string */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_xvasprintf)(const char *format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) char *NOTHROW_NCX(VLIBDCALL libd_xasprintf)(char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) char *NOTHROW_NCX(VLIBCCALL libc_xasprintf)(char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char **NOTHROW_NCX(LIBDCALL libd_dupargv)(char **argv);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char **NOTHROW_NCX(LIBCCALL libc_dupargv)(char **argv);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_NCX(LIBDCALL libd_freeargv)(char **argv);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF void NOTHROW_NCX(LIBCCALL libc_freeargv)(char **argv);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd_countargv)(char *const *argv);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_countargv)(char *const *argv);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED int NOTHROW_NCX(LIBDCALL libd_fdmatch)(fd_t fd1, fd_t fd2);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char **NOTHROW_NCX(LIBDCALL libd_buildargv)(char const *a);
INTDEF NONNULL((1, 2)) void NOTHROW_NCX(LIBDCALL libd_expandargv)(int *p_argc, char ***p_argv);
/* @return: 0 : Success
 * @return: 1 : Error */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_writeargv)(char *const *argv, FILE *fp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @return: 0 : Success
 * @return: 1 : Error */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_writeargv)(char *const *argv, FILE *fp);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED char *NOTHROW_NCX(LIBCCALL libc_vconcat)(char const *first, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL ATTR_SENTINEL WUNUSED char *NOTHROW_NCX(VLIBDCALL libd_concat)(char const *first, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL ATTR_SENTINEL WUNUSED char *NOTHROW_NCX(VLIBCCALL libc_concat)(char const *first, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL ATTR_SENTINEL WUNUSED char *NOTHROW_NCX(VLIBDCALL libd_reconcat)(char *old_ptr, char const *first, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL ATTR_SENTINEL WUNUSED char *NOTHROW_NCX(VLIBCCALL libc_reconcat)(char *old_ptr, char const *first, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ulongptr_t NOTHROW_NCX(VLIBDCALL libd_concat_length)(char const *first, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ulongptr_t NOTHROW_NCX(VLIBCCALL libc_concat_length)(char const *first, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(VLIBDCALL libd_concat_copy)(char *dst, char const *first, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(VLIBCCALL libc_concat_copy)(char *dst, char const *first, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char *NOTHROW_NCX(LIBDCALL libd_make_relative_prefix)(char const *a, char const *b, char const *c);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char *NOTHROW_NCX(LIBDCALL libd_make_relative_prefix_ignore_links)(const char *a, const char *b, const char *c);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char *NOTHROW_NCX(LIBDCALL libd_make_temp_file)(char const *a);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char *NOTHROW_NCX(LIBDCALL libd_make_temp_file_with_prefix)(const char *a, const char *b);
/* >> unlink_if_ordinary(3)
 * Delete a file, but only if it's S_ISREG or S_ISLNK
 * @return:  0: File was deleted
 * @return:  1: File doesn't exist, isn't accessible, or not a "regular" file.
 * @return: -1: Unlink failed (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBDCALL libd_unlink_if_ordinary)(char const *filename);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> unlink_if_ordinary(3)
 * Delete a file, but only if it's S_ISREG or S_ISLNK
 * @return:  0: File was deleted
 * @return:  1: File doesn't exist, isn't accessible, or not a "regular" file.
 * @return: -1: Unlink failed (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_unlink_if_ordinary)(char const *filename);
INTDEF ATTR_CONST WUNUSED double NOTHROW_NCX(LIBCCALL libc_physmem_total)(void);
INTDEF ATTR_PURE WUNUSED double NOTHROW_NCX(LIBCCALL libc_physmem_available)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED __UINT32_TYPE__ NOTHROW_NCX(LIBDCALL libd_xcrc32)(__BYTE_TYPE__ const *buf, __STDC_INT_AS_SIZE_T len, __UINT32_TYPE__ crc);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED __UINT32_TYPE__ NOTHROW_NCX(LIBCCALL libc_xcrc32)(__BYTE_TYPE__ const *buf, __STDC_INT_AS_SIZE_T len, __UINT32_TYPE__ crc);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF const char *NOTHROW_NCX(LIBDCALL libd_pex_run)(struct pex_obj *obj, int flags, const char *executable, char *const *argv, const char *outname, const char *errname, int *err);
INTDEF const char *NOTHROW_NCX(LIBDCALL libd_pex_run_in_environment)(struct pex_obj *obj, int flags, const char *executable, char *const *argv, char *const *env, const char *outname, const char *errname, int *err);
INTDEF FILE *NOTHROW_NCX(LIBDCALL libd_pex_input_file)(struct pex_obj *obj, int flags, const char *in_name);
INTDEF FILE *NOTHROW_NCX(LIBDCALL libd_pex_input_pipe)(struct pex_obj *obj, int binary);
INTDEF FILE *NOTHROW_NCX(LIBDCALL libd_pex_read_output)(struct pex_obj *obj, int binary);
INTDEF FILE *NOTHROW_NCX(LIBDCALL libd_pex_read_err)(struct pex_obj *obj, int binary);
INTDEF int NOTHROW_NCX(LIBDCALL libd_pex_get_status)(struct pex_obj *obj, int count, int *vector);
INTDEF struct pex_obj *NOTHROW_NCX(LIBDCALL libd_pex_init)(int flags, char const *pname, char const *tempbase);
INTDEF int NOTHROW_NCX(LIBDCALL libd_pex_get_times)(struct pex_obj *obj, int count, struct pex_time *vector);
INTDEF void NOTHROW_NCX(LIBDCALL libd_pex_free)(struct pex_obj *obj);
INTDEF const char *NOTHROW_NCX(LIBDCALL libd_pex_one)(int flags, const char *executable, char *const *argv, const char *pname, const char *outname, const char *errname, int *status, int *err);
INTDEF int NOTHROW_NCX(LIBDCALL libd_pexecute)(char const *a, char *const *b, char const *c, char const *d, char **e, char **f, int g);
INTDEF int NOTHROW_NCX(LIBDCALL libd_pwait)(int a, int *b, int c);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_LIBIBERTY_H */
