/* HASH CRC-32:0x11b161e8 */
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
#ifndef GUARD_LIBC_AUTO_PARTS_WCHAR_PROCESS_H
#define GUARD_LIBC_AUTO_PARTS_WCHAR_PROCESS_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <parts/wchar/process.h>

DECL_BEGIN

#ifndef __T16ARGV
#ifdef __USE_DOS_ALTERATIONS
#define __T16ARGV char16_t const *const *__restrict ___argv
#define __T16ENVP char16_t const *const *__restrict ___envp
#else /* __USE_DOS_ALTERATIONS */
#define __T16ARGV char16_t *const ___argv[__restrict_arr]
#define __T16ENVP char16_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__T16ARGV */
#ifndef __T32ARGV
#ifdef __USE_DOS_ALTERATIONS
#define __T32ARGV char32_t const *const *__restrict ___argv
#define __T32ENVP char32_t const *const *__restrict ___envp
#else /* __USE_DOS_ALTERATIONS */
#define __T32ARGV char32_t *const ___argv[__restrict_arr]
#define __T32ENVP char32_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__T32ARGV */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_wexecv)(char16_t const *__restrict path, __T16ARGV);
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_RPC(LIBKCALL libc_wexecv)(char32_t const *__restrict path, __T32ARGV);
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) int NOTHROW_RPC(LIBDCALL libd_wexecve)(char16_t const *__restrict path, __T16ARGV, __T16ENVP);
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) int NOTHROW_RPC(LIBKCALL libc_wexecve)(char32_t const *__restrict path, __T32ARGV, __T32ENVP);
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_wexecvp)(char16_t const *__restrict file, __T16ARGV);
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_RPC(LIBKCALL libc_wexecvp)(char32_t const *__restrict file, __T32ARGV);
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) int NOTHROW_RPC(LIBDCALL libd_wexecvpe)(char16_t const *__restrict file, __T16ARGV, __T16ENVP);
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) int NOTHROW_RPC(LIBKCALL libc_wexecvpe)(char32_t const *__restrict file, __T32ARGV, __T32ENVP);
INTDEF ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2) int NOTHROW_RPC(VLIBDCALL libd_wexecl)(char16_t const *__restrict path, char16_t const *args, ...);
INTDEF ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2) int NOTHROW_RPC(VLIBKCALL libc_wexecl)(char32_t const *__restrict path, char32_t const *args, ...);
INTDEF ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1) int NOTHROW_RPC(VLIBDCALL libd_wexecle)(char16_t const *__restrict path, char16_t const *args, ...);
INTDEF ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1) int NOTHROW_RPC(VLIBKCALL libc_wexecle)(char32_t const *__restrict path, char32_t const *args, ...);
INTDEF ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2) int NOTHROW_RPC(VLIBDCALL libd_wexeclp)(char16_t const *__restrict file, char16_t const *args, ...);
INTDEF ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2) int NOTHROW_RPC(VLIBKCALL libc_wexeclp)(char32_t const *__restrict file, char32_t const *args, ...);
INTDEF ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1) int NOTHROW_RPC(VLIBDCALL libd_wexeclpe)(char16_t const *__restrict file, char16_t const *args, ...);
INTDEF ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1) int NOTHROW_RPC(VLIBKCALL libc_wexeclpe)(char32_t const *__restrict file, char32_t const *args, ...);
INTDEF ATTR_IN(2) ATTR_IN(3) pid_t NOTHROW_RPC(LIBDCALL libd_wspawnv)(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict path, __T16ARGV);
INTDEF ATTR_IN(2) ATTR_IN(3) pid_t NOTHROW_RPC(LIBKCALL libc_wspawnv)(__STDC_INT_AS_UINT_T mode, char32_t const *__restrict path, __T32ARGV);
INTDEF ATTR_IN(2) ATTR_IN(3) ATTR_IN(4) pid_t NOTHROW_RPC(LIBDCALL libd_wspawnve)(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict path, __T16ARGV, __T16ENVP);
INTDEF ATTR_IN(2) ATTR_IN(3) ATTR_IN(4) pid_t NOTHROW_RPC(LIBKCALL libc_wspawnve)(__STDC_INT_AS_UINT_T mode, char32_t const *__restrict path, __T32ARGV, __T32ENVP);
INTDEF ATTR_IN(2) ATTR_IN(3) pid_t NOTHROW_RPC(LIBDCALL libd_wspawnvp)(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict file, __T16ARGV);
INTDEF ATTR_IN(2) ATTR_IN(3) pid_t NOTHROW_RPC(LIBKCALL libc_wspawnvp)(__STDC_INT_AS_UINT_T mode, char32_t const *__restrict file, __T32ARGV);
INTDEF ATTR_IN(2) ATTR_IN(3) ATTR_IN(4) pid_t NOTHROW_RPC(LIBDCALL libd_wspawnvpe)(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict file, __T16ARGV, __T16ENVP);
INTDEF ATTR_IN(2) ATTR_IN(3) ATTR_IN(4) pid_t NOTHROW_RPC(LIBKCALL libc_wspawnvpe)(__STDC_INT_AS_UINT_T mode, char32_t const *__restrict file, __T32ARGV, __T32ENVP);
INTDEF ATTR_SENTINEL ATTR_IN(2) ATTR_IN_OPT(3) pid_t NOTHROW_RPC(VLIBDCALL libd_wspawnl)(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict path, char16_t const *args, ...);
INTDEF ATTR_SENTINEL ATTR_IN(2) ATTR_IN_OPT(3) pid_t NOTHROW_RPC(VLIBKCALL libc_wspawnl)(__STDC_INT_AS_UINT_T mode, char32_t const *__restrict path, char32_t const *args, ...);
INTDEF ATTR_IN(2) ATTR_IN_OPT(3) ATTR_SENTINEL_O(1) pid_t NOTHROW_RPC(VLIBDCALL libd_wspawnle)(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict path, char16_t const *args, ...);
INTDEF ATTR_IN(2) ATTR_IN_OPT(3) ATTR_SENTINEL_O(1) pid_t NOTHROW_RPC(VLIBKCALL libc_wspawnle)(__STDC_INT_AS_UINT_T mode, char32_t const *__restrict path, char32_t const *args, ...);
INTDEF ATTR_SENTINEL ATTR_IN(2) ATTR_IN_OPT(3) pid_t NOTHROW_RPC(VLIBDCALL libd_wspawnlp)(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict file, char16_t const *args, ...);
INTDEF ATTR_SENTINEL ATTR_IN(2) ATTR_IN_OPT(3) pid_t NOTHROW_RPC(VLIBKCALL libc_wspawnlp)(__STDC_INT_AS_UINT_T mode, char32_t const *__restrict file, char32_t const *args, ...);
INTDEF ATTR_IN(2) ATTR_IN_OPT(3) ATTR_SENTINEL_O(1) pid_t NOTHROW_RPC(VLIBDCALL libd_wspawnlpe)(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict file, char16_t const *args, ...);
INTDEF ATTR_IN(2) ATTR_IN_OPT(3) ATTR_SENTINEL_O(1) pid_t NOTHROW_RPC(VLIBKCALL libc_wspawnlpe)(__STDC_INT_AS_UINT_T mode, char32_t const *__restrict file, char32_t const *args, ...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_PROCESS_H */
