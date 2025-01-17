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
/* (#) Portability: MSVC (/include/vcruntime_startup.h) */
#ifndef _VCRUNTIME_STARTUP_H
#define _VCRUNTIME_STARTUP_H 1

#include <__stdinc.h>

#include <vcruntime.h>

#ifdef __CC__
__SYSDECL_BEGIN

typedef enum _crt_argv_mode {
	_crt_argv_no_arguments         = 0,
	_crt_argv_unexpanded_arguments = 1,
	_crt_argv_expanded_arguments   = 2,
} _crt_argv_mode;

typedef enum _crt_exit_return_mode {
	_crt_exit_terminate_process = 0,
	_crt_exit_return_to_caller  = 1
} _crt_exit_return_mode;

typedef enum _crt_exit_cleanup_mode {
	_crt_exit_full_cleanup  = 0,
	_crt_exit_quick_cleanup = 1,
	_crt_exit_no_cleanup    = 2
} _crt_exit_cleanup_mode;

/* Static functions */
#ifdef _MSC_VER
extern _crt_exit_return_mode __current_exit_return_mode;
extern __BOOL (__LIBDCALL __vcrt_initialize)(void);
extern __BOOL (__LIBDCALL __vcrt_uninitialize)(__BOOL __terminating);
extern __BOOL (__LIBDCALL __vcrt_uninitialize_critical)(void);
extern __BOOL (__LIBDCALL __vcrt_thread_attach)(void);
extern __BOOL (__LIBDCALL __vcrt_thread_detach)(void);
extern int (__LIBDCALL __isa_available_init)(void);
extern _crt_argv_mode (__LIBDCALL _get_startup_argv_mode)(void);
#endif /* _MSC_VER */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_VCRUNTIME_STARTUP_H */
