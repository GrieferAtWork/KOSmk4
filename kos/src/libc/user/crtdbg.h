/* HASH CRC-32:0x3a417f33 */
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
#ifndef GUARD_LIBC_USER_CRTDBG_H
#define GUARD_LIBC_USER_CRTDBG_H 1

#include "../api.h"
#include "../auto/crtdbg.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <crtdbg.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF __LONG32_TYPE__ *NOTHROW_NCX(LIBDCALL libc___p__crtAssertBusy)(void);
INTDEF __LONG32_TYPE__ *NOTHROW_NCX(LIBDCALL libc___p__crtBreakAlloc)(void);
INTDEF int *NOTHROW_NCX(LIBDCALL libc___p__crtDbgFlag)(void);
INTDEF _CRT_REPORT_HOOK NOTHROW_NCX(LIBDCALL libc__CrtGetReportHook)(void);
INTDEF _CRT_REPORT_HOOK NOTHROW_NCX(LIBDCALL libc__CrtSetReportHook)(_CRT_REPORT_HOOK pfn_new_hook);
INTDEF int NOTHROW_NCX(LIBDCALL libc__CrtSetReportHook2)(int mode, _CRT_REPORT_HOOK pfn_new_hook);
INTDEF int NOTHROW_NCX(LIBDCALL libc__CrtSetReportHookW2)(int mode, _CRT_REPORT_HOOKW pfn_new_hook);
INTDEF _CRT_ALLOC_HOOK NOTHROW_NCX(LIBDCALL libc__CrtGetAllocHook)(void);
INTDEF _CRT_ALLOC_HOOK NOTHROW_NCX(LIBDCALL libc__CrtSetAllocHook)(_CRT_ALLOC_HOOK pfn_new_hook);
INTDEF _CRT_DUMP_CLIENT NOTHROW_NCX(LIBDCALL libc__CrtGetDumpClient)(void);
INTDEF _CRT_DUMP_CLIENT NOTHROW_NCX(LIBDCALL libc__CrtSetDumpClient)(_CRT_DUMP_CLIENT pfn_new_dump);
INTDEF int NOTHROW_NCX(LIBDCALL libc__CrtSetReportMode)(int report_type, int report_mode);
INTDEF _HFILE NOTHROW_NCX(LIBDCALL libc__CrtSetReportFile)(int report_type, _HFILE report_file);
INTDEF size_t NOTHROW_NCX(LIBDCALL libc__CrtSetDebugFillThreshold)(size_t new_debug_fill_threshold);
INTDEF int NOTHROW_NCX(VLIBDCALL libc__CrtDbgReport)(int report_type, char const *filename, int line, char const *module_name, char const *format, ...);
INTDEF int NOTHROW_NCX(VLIBDCALL libc__CrtDbgReportW)(int report_type, __WCHAR16_TYPE__ const *filename, int line, __WCHAR16_TYPE__ const *module_name, __WCHAR16_TYPE__ const *format, ...);
INTDEF void NOTHROW_NCX(LIBDCALL libc__CrtDbgBreak)(void);
INTDEF __LONG32_TYPE__ NOTHROW_NCX(LIBDCALL libc__CrtSetBreakAlloc)(__LONG32_TYPE__ break_alloc);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_CRTDBG_H */
