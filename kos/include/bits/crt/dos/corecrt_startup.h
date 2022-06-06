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
#ifndef _BITS_CRT_DOS__CRTMEMSTATE_H
#define _BITS_CRT_DOS__CRTMEMSTATE_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

struct _EXCEPTION_POINTERS;

typedef enum _crt_app_type {
	_crt_unknown_app = 0,
	_crt_console_app = 1,
	_crt_gui_app     = 2,
} _crt_app_type;

typedef int (__LIBCCALL *_UserMathErrorFunctionPointer)(struct _exception *);

typedef void (__LIBDCALL *_PVFV)(void);
typedef int  (__LIBDCALL *_PIFV)(void);
typedef void (__LIBDCALL *_PVFI)(int __exit_code);

typedef struct _onexit_table_t {
	_PVFV *_first;
	_PVFV *_last;
	_PVFV *_end;
} _onexit_table_t;

#ifndef _CRT_ONEXIT_T_DEFINED
#define _CRT_ONEXIT_T_DEFINED
#ifndef _ONEXIT_T_DEFINED
#define _ONEXIT_T_DEFINED
typedef int (__LIBDCALL *_onexit_t)(void);
#endif /* !_ONEXIT_T_DEFINED */
#endif /* !_CRT_ONEXIT_T_DEFINED */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_DOS__CRTMEMSTATE_H */
