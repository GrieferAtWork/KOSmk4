/* HASH CRC-32:0xb4a9d02c */
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
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED char const *NOTHROW_NCX(LIBDCALL libd_dos_lbasename)(char const *filename);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED char const *NOTHROW_NCX(LIBCCALL libc_dos_lbasename)(char const *filename);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBDCALL libd_lrealpath)(char const *path);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBCCALL libc_lrealpath)(char const *path);
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
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBDCALL libd_xstrdup)(char const *__restrict string);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *NOTHROW_NCX(LIBCCALL libc_xstrdup)(char const *__restrict string);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED char *NOTHROW_NCX(LIBDCALL libd_xstrndup)(char const *string, size_t max_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED char *NOTHROW_NCX(LIBCCALL libc_xstrndup)(char const *string, size_t max_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((3)) ATTR_INS(1, 2) void *NOTHROW_NCX(LIBDCALL libd_xmemdup)(void const *src, size_t src_bytes, size_t alloc_size);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((3)) ATTR_INS(1, 2) void *NOTHROW_NCX(LIBCCALL libc_xmemdup)(void const *src, size_t src_bytes, size_t alloc_size);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strdupf(3), vstrdupf(3)
 * Print the given `format' into a newly allocated, heap-allocated string */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) char *NOTHROW_NCX(LIBDCALL libd_xvasprintf)(char const *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strdupf(3), vstrdupf(3)
 * Print the given `format' into a newly allocated, heap-allocated string */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) char *NOTHROW_NCX(LIBCCALL libc_xvasprintf)(char const *format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) char *NOTHROW_NCX(VLIBDCALL libd_xasprintf)(char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) char *NOTHROW_NCX(VLIBCCALL libc_xasprintf)(char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN_OPT(1) char **NOTHROW_NCX(LIBDCALL libd_dupargv)(char *__KOS_FIXED_CONST *argv);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN_OPT(1) char **NOTHROW_NCX(LIBCCALL libc_dupargv)(char *__KOS_FIXED_CONST *argv);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN_OPT(1) void NOTHROW_NCX(LIBDCALL libd_freeargv)(char **argv);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN_OPT(1) void NOTHROW_NCX(LIBCCALL libc_freeargv)(char **argv);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_IN_OPT(1) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd_countargv)(char *const *argv);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_IN_OPT(1) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_countargv)(char *const *argv);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED int NOTHROW_NCX(LIBDCALL libd_fdmatch)(fd_t fd1, fd_t fd2);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN_OPT(1) char **NOTHROW_NCX(LIBDCALL libd_buildargv)(char const *cmdline);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN_OPT(1) char **NOTHROW_NCX(LIBCCALL libc_buildargv)(char const *cmdline);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> expandargv(3)
 * Expand special `@file' arguments passed on the commandline */
INTDEF ATTR_INOUT(1) ATTR_INOUT(2) void NOTHROW_NCX(LIBDCALL libd_expandargv)(int *p_argc, char ***p_argv);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> expandargv(3)
 * Expand special `@file' arguments passed on the commandline */
INTDEF ATTR_INOUT(1) ATTR_INOUT(2) void NOTHROW_NCX(LIBCCALL libc_expandargv)(int *p_argc, char ***p_argv);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @return: 0 : Success
 * @return: 1 : Error */
INTDEF ATTR_IN(1) ATTR_INOUT_OPT(2) int NOTHROW_NCX(LIBDCALL libd_writeargv)(char *const *argv, FILE *fp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @return: 0 : Success
 * @return: 1 : Error */
INTDEF ATTR_IN(1) ATTR_INOUT_OPT(2) int NOTHROW_NCX(LIBCCALL libc_writeargv)(char *const *argv, FILE *fp);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_IN_OPT(1) char *NOTHROW_NCX(LIBCCALL libc_vconcat)(char const *first, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL ATTR_SENTINEL WUNUSED ATTR_IN_OPT(1) char *NOTHROW_NCX(VLIBDCALL libd_concat)(char const *first, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL ATTR_SENTINEL WUNUSED ATTR_IN_OPT(1) char *NOTHROW_NCX(VLIBCCALL libc_concat)(char const *first, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL ATTR_SENTINEL WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) char *NOTHROW_NCX(VLIBDCALL libd_reconcat)(char *old_ptr, char const *first, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL ATTR_SENTINEL WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) char *NOTHROW_NCX(VLIBCCALL libc_reconcat)(char *old_ptr, char const *first, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN_OPT(1) ulongptr_t NOTHROW_NCX(VLIBDCALL libd_concat_length)(char const *first, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN_OPT(1) ulongptr_t NOTHROW_NCX(VLIBCCALL libc_concat_length)(char const *first, ...);
INTDEF ATTR_RETNONNULL ATTR_IN_OPT(2) ATTR_OUT(1) char *NOTHROW_NCX(LIBCCALL libc_concat_vcopy)(char *dst, char const *first, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_RETNONNULL ATTR_IN_OPT(2) ATTR_OUT(1) char *NOTHROW_NCX(VLIBDCALL libd_concat_copy)(char *dst, char const *first, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL ATTR_IN_OPT(2) ATTR_OUT(1) char *NOTHROW_NCX(VLIBCCALL libc_concat_copy)(char *dst, char const *first, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN_OPT(1) char *NOTHROW_NCX(VLIBDCALL libd_concat_copy2)(char const *first, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN_OPT(1) char *NOTHROW_NCX(VLIBCCALL libc_concat_copy2)(char const *first, ...);
/* >> get_run_time(3)
 * Return the amount of time the calling process has run (in  microseconds)
 * If possible, time spent idling isn't counted, though if not possible, it
 * is included, also. */
INTDEF WUNUSED long NOTHROW_NCX(LIBCCALL libc_get_run_time)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char *NOTHROW_NCX(LIBDCALL libd_make_relative_prefix)(char const *a, char const *b, char const *c);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char *NOTHROW_NCX(LIBDCALL libd_make_relative_prefix_ignore_links)(char const *a, char const *b, char const *c);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> choose_temp_base(3)
 * Create a temporary filename in `choose_tmpdir(3)' by use of `mktemp(3)'
 * The  returned string must always be freed,  and if no filename could be
 * generated, an empty string is returned. */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char *NOTHROW_NCX(LIBCCALL libc_choose_temp_base)(void);
/* >> choose_tmpdir(3)
 * Return the path to a suitable temp directory.
 * The returned path is guarantied to be non-NULL, and include a trailing slash. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED char const *NOTHROW_NCX(LIBCCALL libc_choose_tmpdir)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) char *NOTHROW_NCX(LIBDCALL libd_make_temp_file_with_prefix)(char const *prefix, char const *suffix);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) char *NOTHROW_NCX(LIBCCALL libc_make_temp_file_with_prefix)(char const *prefix, char const *suffix);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_IN_OPT(1) char *NOTHROW_NCX(LIBDCALL libd_make_temp_file)(char const *suffix);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_IN_OPT(1) char *NOTHROW_NCX(LIBCCALL libc_make_temp_file)(char const *suffix);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unlink_if_ordinary(3)
 * Delete a file, but only if it's S_ISREG or S_ISLNK
 * @return:  0: File was deleted
 * @return:  1: File doesn't exist, isn't accessible, or not a "regular" file.
 * @return: -1: Unlink failed (s.a. `errno') */
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd_unlink_if_ordinary)(char const *filename);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> unlink_if_ordinary(3)
 * Delete a file, but only if it's S_ISREG or S_ISLNK
 * @return:  0: File was deleted
 * @return:  1: File doesn't exist, isn't accessible, or not a "regular" file.
 * @return: -1: Unlink failed (s.a. `errno') */
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBCCALL libc_unlink_if_ordinary)(char const *filename);
INTDEF ATTR_CONST WUNUSED double NOTHROW_NCX(LIBCCALL libc_physmem_total)(void);
INTDEF ATTR_PURE WUNUSED double NOTHROW_NCX(LIBCCALL libc_physmem_available)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) __UINT32_TYPE__ NOTHROW_NCX(LIBDCALL libd_xcrc32)(__BYTE_TYPE__ const *buf, __STDC_INT_AS_SIZE_T len, __UINT32_TYPE__ crc);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) __UINT32_TYPE__ NOTHROW_NCX(LIBCCALL libc_xcrc32)(__BYTE_TYPE__ const *buf, __STDC_INT_AS_SIZE_T len, __UINT32_TYPE__ crc);
/* >> hex_init(3)
 * Initialize the `_hex_value' array (unless it was already statically initialized) */
INTDEF void NOTHROW_NCX(LIBCCALL libc_hex_init)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF char const *NOTHROW_NCX(LIBDCALL libd_pex_run)(struct pex_obj *obj, int flags, char const *executable, char *const *argv, char const *outname, char const *errname, int *err);
INTDEF char const *NOTHROW_NCX(LIBDCALL libd_pex_run_in_environment)(struct pex_obj *obj, int flags, char const *executable, char *const *argv, char *const *env, char const *outname, char const *errname, int *err);
INTDEF FILE *NOTHROW_NCX(LIBDCALL libd_pex_input_file)(struct pex_obj *obj, int flags, char const *in_name);
INTDEF FILE *NOTHROW_NCX(LIBDCALL libd_pex_input_pipe)(struct pex_obj *obj, int binary);
INTDEF FILE *NOTHROW_NCX(LIBDCALL libd_pex_read_output)(struct pex_obj *obj, int binary);
INTDEF FILE *NOTHROW_NCX(LIBDCALL libd_pex_read_err)(struct pex_obj *obj, int binary);
INTDEF int NOTHROW_NCX(LIBDCALL libd_pex_get_status)(struct pex_obj *obj, int count, int *vector);
INTDEF struct pex_obj *NOTHROW_NCX(LIBDCALL libd_pex_init)(int flags, char const *pname, char const *tempbase);
INTDEF int NOTHROW_NCX(LIBDCALL libd_pex_get_times)(struct pex_obj *obj, int count, struct pex_time *vector);
INTDEF void NOTHROW_NCX(LIBDCALL libd_pex_free)(struct pex_obj *obj);
INTDEF char const *NOTHROW_NCX(LIBDCALL libd_pex_one)(int flags, char const *executable, char *const *argv, char const *pname, char const *outname, char const *errname, int *status, int *err);
INTDEF int NOTHROW_NCX(LIBDCALL libd_pexecute)(char const *a, char *const *b, char const *c, char const *d, char **e, char **f, int g);
INTDEF int NOTHROW_NCX(LIBDCALL libd_pwait)(int a, int *b, int c);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_LIBIBERTY_H */
