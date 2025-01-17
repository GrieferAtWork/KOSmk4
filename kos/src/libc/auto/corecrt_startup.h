/* HASH CRC-32:0xb3803970 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_CORECRT_STARTUP_H
#define GUARD_LIBC_AUTO_CORECRT_STARTUP_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <corecrt_startup.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED _crt_app_type NOTHROW(LIBDCALL libc__query_app_type)(void);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libc__configure_narrow_argv)(_crt_argv_mode mode);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libc__configure_wide_argv)(_crt_argv_mode mode);
INTDEF int NOTHROW_NCX(LIBDCALL libc__initialize_narrow_environment)(void);
INTDEF int NOTHROW_NCX(LIBDCALL libc__initialize_wide_environment)(void);
INTDEF ATTR_PURE WUNUSED char **NOTHROW_NCX(LIBDCALL libc__get_initial_narrow_environment)(void);
INTDEF ATTR_PURE WUNUSED __WCHAR16_TYPE__ **NOTHROW_NCX(LIBDCALL libc__get_initial_wide_environment)(void);
INTDEF ATTR_PURE WUNUSED char *NOTHROW_NCX(LIBDCALL libc__get_narrow_winmain_command_line)(void);
INTDEF ATTR_PURE WUNUSED __WCHAR16_TYPE__ *NOTHROW_NCX(LIBDCALL libc__get_wide_winmain_command_line)(void);
INTDEF void NOTHROW_NCX(LIBDCALL libc__initterm)(_PVFV *start, _PVFV *end);
INTDEF int NOTHROW_NCX(LIBDCALL libc__initterm_e)(_onexit_t *start, _onexit_t *end);
INTDEF int NOTHROW_NCX(LIBDCALL libc__initialize_onexit_table)(struct _onexit_table_t *self);
INTDEF int NOTHROW_NCX(LIBDCALL libc__register_onexit_function)(struct _onexit_table_t *self, _onexit_t function);
INTDEF int NOTHROW_NCX(LIBDCALL libc__execute_onexit_table)(struct _onexit_table_t *self);
INTDEF ATTR_INOUT(2) ATTR_INOUT(3) int NOTHROW_NCX(LIBDCALL libc___dllonexit)(_onexit_t func, _onexit_t **p_begin, _onexit_t **p_end);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CORECRT_STARTUP_H */
