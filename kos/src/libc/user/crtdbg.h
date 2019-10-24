/* HASH CRC-32:0x73bb12d4 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
INTDEF ATTR_MALLOC ATTR_ALLOC_SIZE((1)) WUNUSED void *NOTHROW_NCX(LIBCCALL libc__malloc_dbg)(size_t num_bytes, int block_type, char const *filename, int line);
INTDEF ATTR_MALLOC ATTR_ALLOC_SIZE((1, 2)) WUNUSED void *NOTHROW_NCX(LIBCCALL libc__calloc_dbg)(size_t count, size_t num_bytes, int block_type, char const *filename, int line);
INTDEF ATTR_ALLOC_SIZE((2)) WUNUSED void *NOTHROW_NCX(LIBCCALL libc__realloc_dbg)(void *ptr, size_t num_bytes, int block_type, char const *filename, int line);
INTDEF ATTR_ALLOC_SIZE((2, 3)) WUNUSED void *NOTHROW_NCX(LIBCCALL libc__recalloc_dbg)(void *ptr, size_t count, size_t num_bytes, int block_type, char const *filename, int line);
INTDEF ATTR_ALLOC_SIZE((2)) WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc__expand_dbg)(void *ptr, size_t num_bytes, int block_type, char const *filename, int line);
INTDEF void NOTHROW_NCX(LIBCCALL libc__free_dbg)(void *ptr, int block_type);
INTDEF WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__msize_dbg)(void *ptr, int block_type);
INTDEF WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__aligned_msize_dbg)(void *ptr, size_t min_alignment, size_t offset);
INTDEF ATTR_MALLOC ATTR_ALLOC_SIZE((1)) ATTR_ALLOC_ALIGN(2) WUNUSED void *NOTHROW_NCX(LIBCCALL libc__aligned_malloc_dbg)(size_t num_bytes, size_t min_alignment, char const *filename, int line);
INTDEF ATTR_ALLOC_SIZE((2)) ATTR_ALLOC_ALIGN(3) WUNUSED void *NOTHROW_NCX(LIBCCALL libc__aligned_realloc_dbg)(void *ptr, size_t num_bytes, size_t min_alignment, char const *filename, int line);
INTDEF ATTR_ALLOC_SIZE((2, 3)) ATTR_ALLOC_ALIGN(4) WUNUSED void *NOTHROW_NCX(LIBCCALL libc__aligned_recalloc_dbg)(void *ptr, size_t count, size_t num_bytes, size_t min_alignment, char const *filename, int line);
INTDEF ATTR_MALLOC ATTR_ALLOC_SIZE((1)) WUNUSED void *NOTHROW_NCX(LIBCCALL libc__aligned_offset_malloc_dbg)(size_t num_bytes, size_t min_alignment, size_t offset, char const *filename, int line);
INTDEF ATTR_ALLOC_SIZE((2)) WUNUSED void *NOTHROW_NCX(LIBCCALL libc__aligned_offset_realloc_dbg)(void *ptr, size_t num_bytes, size_t min_alignment, size_t offset, char const *filename, int line);
INTDEF ATTR_ALLOC_SIZE((2, 3)) WUNUSED void *NOTHROW_NCX(LIBCCALL libc__aligned_offset_recalloc_dbg)(void *ptr, size_t count, size_t num_bytes, size_t min_alignment, size_t offset, char const *filename, int line);
INTDEF void NOTHROW_NCX(LIBCCALL libc__aligned_free_dbg)(void *ptr);
INTDEF ATTR_MALLOC WUNUSED char *NOTHROW_NCX(LIBCCALL libc__strdup_dbg)(char const *string, int block_type, char const *filename, int line);
INTDEF WUNUSED __WCHAR16_TYPE__ *NOTHROW_NCX(LIBCCALL libc__wcsdup_dbg)(__WCHAR16_TYPE__ const *string, int block_type, char const *filename, int line);
INTDEF ATTR_MALLOC WUNUSED char *NOTHROW_NCX(LIBCCALL libc__tempnam_dbg)(char const *dir_name, char const *file_prefix, int block_type, char const *filename, int line);
INTDEF WUNUSED __WCHAR16_TYPE__ *NOTHROW_NCX(LIBCCALL libc__wtempnam_dbg)(__WCHAR16_TYPE__ const *dir_name, __WCHAR16_TYPE__ const *file_prefix, int block_type, char const *filename, int line);
INTDEF WUNUSED NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc__fullpath_dbg)(char *full_path, char const *path, size_t bufsize, int block_type, char const *filename, int line);
INTDEF WUNUSED NONNULL((2)) __WCHAR16_TYPE__ *NOTHROW_NCX(LIBCCALL libc__wfullpath_dbg)(__WCHAR16_TYPE__ *full_path, __WCHAR16_TYPE__ const *path, size_t buflen, int block_type, char const *filename, int line);
INTDEF WUNUSED char *NOTHROW_NCX(LIBCCALL libc__getcwd_dbg)(char *buf, __STDC_INT_AS_SIZE_T bufsize, int block_type, char const *filename, int line);
INTDEF WUNUSED __WCHAR16_TYPE__ *NOTHROW_NCX(LIBCCALL libc__wgetcwd_dbg)(__WCHAR16_TYPE__ *buf, __STDC_INT_AS_SIZE_T buflen, int block_type, char const *filename, int line);
INTDEF WUNUSED char *NOTHROW_NCX(LIBCCALL libc__getdcwd_dbg)(int driveno, char *buf, __STDC_INT_AS_SIZE_T bufsize, int block_type, char const *filename, int line);
INTDEF WUNUSED __WCHAR16_TYPE__ *NOTHROW_NCX(LIBCCALL libc__wgetdcwd_dbg)(int driveno, __WCHAR16_TYPE__ *buf, __STDC_INT_AS_SIZE_T buflen, int block_type, char const *filename, int line);
INTDEF _Check_return_wat_ NONNULL((3)) errno_t NOTHROW_NCX(LIBCCALL libc__dupenv_s_dbg)(char **pbuf, size_t *pbufsize, char const *varname, int block_type, char const *filename, int line);
INTDEF _Check_return_wat_ NONNULL((3)) errno_t NOTHROW_NCX(LIBCCALL libc__wdupenv_s_dbg)(__WCHAR16_TYPE__ **pbuf, size_t *pbuflen, __WCHAR16_TYPE__ const *varname, int block_type, char const *filename, int line);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc__CrtDoForAllClientObjects)(_PFNCRTDOFORALLCLIENTOBJECTS pfn, void *context);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__CrtIsValidPointer)(void const *ptr, __STDC_UINT_AS_SIZE_T num_bytes, int writable);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__CrtIsValidHeapPointer)(void const *heap_ptr);
INTDEF int NOTHROW_NCX(LIBCCALL libc__CrtIsMemoryBlock)(void const *ptr, __STDC_UINT_AS_SIZE_T num_bytes, __LONG32_TYPE__ *prequest_number, char **filename, int *line);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__CrtReportBlockType)(void const *ptr);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc__CrtMemCheckpoint)(/*out*/ _CrtMemState *state);
INTDEF NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBCCALL libc__CrtMemDifference)(/*out*/ _CrtMemState *state, _CrtMemState const *old_state, _CrtMemState const *new_state);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc__CrtMemDumpAllObjectsSince)(_CrtMemState const *state);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc__CrtMemDumpStatistics)(_CrtMemState const *state);
INTDEF int NOTHROW_NCX(LIBCCALL libc__CrtDumpMemoryLeaks)(void);
INTDEF int NOTHROW_NCX(LIBCCALL libc__CrtSetCheckCount)(int check_count);
INTDEF int NOTHROW_NCX(LIBCCALL libc__CrtGetCheckCount)(void);

DECL_END

#endif /* !GUARD_LIBC_USER_CRTDBG_H */
