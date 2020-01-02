/* HASH CRC-32:0xc5da28a5 */
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
#ifndef GUARD_LIBC_USER_CRTDBG_H
#define GUARD_LIBC_USER_CRTDBG_H 1

#include "../api.h"
#include "../auto/crtdbg.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <crtdbg.h>

DECL_BEGIN

INTDEF __LONG32_TYPE__ *NOTHROW_NCX(LIBCCALL libc___p__crtAssertBusy)(void);
INTDEF __LONG32_TYPE__ *NOTHROW_NCX(LIBCCALL libc___p__crtBreakAlloc)(void);
INTDEF int *NOTHROW_NCX(LIBCCALL libc___p__crtDbgFlag)(void);
INTDEF _CRT_REPORT_HOOK NOTHROW_NCX(LIBCCALL libc__CrtGetReportHook)(void);
INTDEF _CRT_REPORT_HOOK NOTHROW_NCX(LIBCCALL libc__CrtSetReportHook)(_CRT_REPORT_HOOK pfn_new_hook);
INTDEF int NOTHROW_NCX(LIBCCALL libc__CrtSetReportHook2)(int mode, _CRT_REPORT_HOOK pfn_new_hook);
INTDEF int NOTHROW_NCX(LIBCCALL libc__CrtSetReportHookW2)(int mode, _CRT_REPORT_HOOKW pfn_new_hook);
INTDEF _CRT_ALLOC_HOOK NOTHROW_NCX(LIBCCALL libc__CrtGetAllocHook)(void);
INTDEF _CRT_ALLOC_HOOK NOTHROW_NCX(LIBCCALL libc__CrtSetAllocHook)(_CRT_ALLOC_HOOK pfn_new_hook);
INTDEF _CRT_DUMP_CLIENT NOTHROW_NCX(LIBCCALL libc__CrtGetDumpClient)(void);
INTDEF _CRT_DUMP_CLIENT NOTHROW_NCX(LIBCCALL libc__CrtSetDumpClient)(_CRT_DUMP_CLIENT pfn_new_dump);
INTDEF int NOTHROW_NCX(LIBCCALL libc__CrtSetDbgFlag)(int new_flag);
INTDEF int NOTHROW_NCX(LIBCCALL libc__CrtSetReportMode)(int report_type, int report_mode);
INTDEF _HFILE NOTHROW_NCX(LIBCCALL libc__CrtSetReportFile)(int report_type, _HFILE report_file);
INTDEF size_t NOTHROW_NCX(LIBCCALL libc__CrtSetDebugFillThreshold)(size_t new_debug_fill_threshold);
INTDEF int NOTHROW_NCX(VLIBCCALL libc__CrtDbgReport)(int report_type, char const *filename, int line, char const *module_name, char const *format, ...);
INTDEF int NOTHROW_NCX(VLIBCCALL libc__CrtDbgReportW)(int report_type, __WCHAR16_TYPE__ const *filename, int line, __WCHAR16_TYPE__ const *module_name, __WCHAR16_TYPE__ const *format, ...);
INTDEF void NOTHROW_NCX(LIBCCALL libc__CrtDbgBreak)(void);
INTDEF __LONG32_TYPE__ NOTHROW_NCX(LIBCCALL libc__CrtSetBreakAlloc)(__LONG32_TYPE__ break_alloc);
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc__malloc_dbg)(size_t num_bytes, int block_type, char const *filename, int line);
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1, 2)) void *NOTHROW_NCX(LIBCCALL libc__calloc_dbg)(size_t count, size_t num_bytes, int block_type, char const *filename, int line);
INTDEF WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc__realloc_dbg)(void *ptr, size_t num_bytes, int block_type, char const *filename, int line);
INTDEF WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBCCALL libc__recalloc_dbg)(void *ptr, size_t count, size_t num_bytes, int block_type, char const *filename, int line);
INTDEF WUNUSED NONNULL((1)) ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc__expand_dbg)(void *ptr, size_t num_bytes, int block_type, char const *filename, int line);
INTDEF void NOTHROW_NCX(LIBCCALL libc__free_dbg)(void *ptr, int block_type);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__msize_dbg)(void *ptr, int block_type);
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) ATTR_ALLOC_ALIGN(2) void *NOTHROW_NCX(LIBCCALL libc__aligned_malloc_dbg)(size_t num_bytes, size_t min_alignment, char const *filename, int line);
INTDEF WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_ALLOC_ALIGN(3) void *NOTHROW_NCX(LIBCCALL libc__aligned_realloc_dbg)(void *ptr, size_t num_bytes, size_t min_alignment, char const *filename, int line);
INTDEF WUNUSED ATTR_ALLOC_SIZE((2, 3)) ATTR_ALLOC_ALIGN(4) void *NOTHROW_NCX(LIBCCALL libc__aligned_recalloc_dbg)(void *ptr, size_t count, size_t num_bytes, size_t min_alignment, char const *filename, int line);
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc__aligned_offset_malloc_dbg)(size_t num_bytes, size_t min_alignment, size_t offset, char const *filename, int line);
INTDEF WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc__aligned_offset_realloc_dbg)(void *ptr, size_t num_bytes, size_t min_alignment, size_t offset, char const *filename, int line);
INTDEF WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBCCALL libc__aligned_offset_recalloc_dbg)(void *ptr, size_t count, size_t num_bytes, size_t min_alignment, size_t offset, char const *filename, int line);
INTDEF void NOTHROW_NCX(LIBCCALL libc__aligned_free_dbg)(void *ptr);
INTDEF ATTR_MALLOC WUNUSED char *NOTHROW_NCX(LIBCCALL libc__strdup_dbg)(char const *string, int block_type, char const *filename, int line);
INTDEF ATTR_MALLOC WUNUSED __WCHAR16_TYPE__ *NOTHROW_NCX(LIBCCALL libc__wcsdup_dbg)(__WCHAR16_TYPE__ const *string, int block_type, char const *filename, int line);
INTDEF ATTR_MALLOC WUNUSED char *NOTHROW_NCX(LIBCCALL libc__tempnam_dbg)(char const *dir_name, char const *file_prefix, int block_type, char const *filename, int line);
INTDEF WUNUSED NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc__fullpath_dbg)(char *full_path, char const *path, size_t bufsize, int block_type, char const *filename, int line);
INTDEF WUNUSED char *NOTHROW_NCX(LIBCCALL libc__getcwd_dbg)(char *buf, __STDC_INT_AS_SIZE_T bufsize, int block_type, char const *filename, int line);
INTDEF WUNUSED __WCHAR16_TYPE__ *NOTHROW_NCX(LIBCCALL libc__wgetcwd_dbg)(__WCHAR16_TYPE__ *buf, __STDC_INT_AS_SIZE_T buflen, int block_type, char const *filename, int line);
INTDEF WUNUSED char *NOTHROW_NCX(LIBCCALL libc__getdcwd_dbg)(int driveno, char *buf, __STDC_INT_AS_SIZE_T bufsize, int block_type, char const *filename, int line);
INTDEF _Check_return_wat_ NONNULL((3)) errno_t NOTHROW_NCX(LIBCCALL libc__dupenv_s_dbg)(char **pbuf, size_t *pbufsize, char const *varname, int block_type, char const *filename, int line);

DECL_END

#endif /* !GUARD_LIBC_USER_CRTDBG_H */
