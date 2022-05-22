/* HASH CRC-32:0x2b79e6c1 */
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
#ifndef GUARD_LIBC_AUTO_CRTDBG_H
#define GUARD_LIBC_AUTO_CRTDBG_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <crtdbg.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF int NOTHROW_NCX(LIBDCALL libc__CrtSetDbgFlag)(int new_flag);
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBDCALL libc__malloc_dbg)(size_t num_bytes, int block_type, char const *filename, int line);
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1, 2)) void *NOTHROW_NCX(LIBDCALL libc__calloc_dbg)(size_t count, size_t num_bytes, int block_type, char const *filename, int line);
INTDEF WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBDCALL libc__realloc_dbg)(void *ptr, size_t num_bytes, int block_type, char const *filename, int line);
INTDEF WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBDCALL libc__recalloc_dbg)(void *ptr, size_t count, size_t num_bytes, int block_type, char const *filename, int line);
INTDEF WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBDCALL libc__expand_dbg)(void *ptr, size_t num_bytes, int block_type, char const *filename, int line);
INTDEF void NOTHROW_NCX(LIBDCALL libc__free_dbg)(void *ptr, int block_type);
INTDEF ATTR_PURE WUNUSED size_t NOTHROW_NCX(LIBDCALL libc__msize_dbg)(void *ptr, int block_type);
INTDEF ATTR_PURE WUNUSED size_t NOTHROW_NCX(LIBDCALL libc__aligned_msize_dbg)(void *ptr, size_t min_alignment, size_t offset);
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_ALIGN(2) ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBDCALL libc__aligned_malloc_dbg)(size_t num_bytes, size_t min_alignment, char const *filename, int line);
INTDEF WUNUSED ATTR_ALLOC_ALIGN(3) ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBDCALL libc__aligned_realloc_dbg)(void *ptr, size_t num_bytes, size_t min_alignment, char const *filename, int line);
INTDEF WUNUSED ATTR_ALLOC_ALIGN(4) ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBDCALL libc__aligned_recalloc_dbg)(void *ptr, size_t count, size_t num_bytes, size_t min_alignment, char const *filename, int line);
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBDCALL libc__aligned_offset_malloc_dbg)(size_t num_bytes, size_t min_alignment, size_t offset, char const *filename, int line);
INTDEF WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBDCALL libc__aligned_offset_realloc_dbg)(void *ptr, size_t num_bytes, size_t min_alignment, size_t offset, char const *filename, int line);
INTDEF WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBDCALL libc__aligned_offset_recalloc_dbg)(void *ptr, size_t count, size_t num_bytes, size_t min_alignment, size_t offset, char const *filename, int line);
INTDEF void NOTHROW_NCX(LIBDCALL libc__aligned_free_dbg)(void *ptr);
INTDEF ATTR_MALLOC WUNUSED char *NOTHROW_NCX(LIBDCALL libc__strdup_dbg)(char const *string, int block_type, char const *filename, int line);
INTDEF ATTR_MALLOC WUNUSED __WCHAR16_TYPE__ *NOTHROW_NCX(LIBDCALL libc__wcsdup_dbg)(__WCHAR16_TYPE__ const *string, int block_type, char const *filename, int line);
INTDEF ATTR_MALLOC WUNUSED char *NOTHROW_NCX(LIBDCALL libc__tempnam_dbg)(char const *dir_name, char const *file_prefix, int block_type, char const *filename, int line);
INTDEF WUNUSED __WCHAR16_TYPE__ *NOTHROW_NCX(LIBDCALL libc__wtempnam_dbg)(__WCHAR16_TYPE__ const *dir_name, __WCHAR16_TYPE__ const *file_prefix, int block_type, char const *filename, int line);
INTDEF WUNUSED ATTR_IN(2) ATTR_OUTS(1, 3) char *NOTHROW_NCX(LIBDCALL libc__fullpath_dbg)(char *full_path, char const *path, size_t bufsize, int block_type, char const *filename, int line);
INTDEF WUNUSED ATTR_IN(2) ATTR_OUTS(1, 3) __WCHAR16_TYPE__ *NOTHROW_NCX(LIBDCALL libc__wfullpath_dbg)(__WCHAR16_TYPE__ *full_path, __WCHAR16_TYPE__ const *path, size_t buflen, int block_type, char const *filename, int line);
INTDEF WUNUSED ATTR_OUTS(1, 2) char *NOTHROW_NCX(LIBDCALL libc__getcwd_dbg)(char *buf, __STDC_INT_AS_SIZE_T bufsize, int block_type, char const *filename, int line);
INTDEF WUNUSED ATTR_OUTS(1, 2) __WCHAR16_TYPE__ *NOTHROW_NCX(LIBDCALL libc__wgetcwd_dbg)(__WCHAR16_TYPE__ *buf, __STDC_INT_AS_SIZE_T buflen, int block_type, char const *filename, int line);
INTDEF WUNUSED ATTR_OUTS(2, 3) char *NOTHROW_NCX(LIBDCALL libc__getdcwd_dbg)(int driveno, char *buf, __STDC_INT_AS_SIZE_T bufsize, int block_type, char const *filename, int line);
INTDEF WUNUSED ATTR_OUTS(2, 3) __WCHAR16_TYPE__ *NOTHROW_NCX(LIBDCALL libc__wgetdcwd_dbg)(int driveno, __WCHAR16_TYPE__ *buf, __STDC_INT_AS_SIZE_T buflen, int block_type, char const *filename, int line);
INTDEF _Check_return_wat_ ATTR_IN(3) ATTR_OUT(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libc__dupenv_s_dbg)(char **pbuf, size_t *pbufsize, char const *varname, int block_type, char const *filename, int line);
INTDEF _Check_return_wat_ ATTR_IN(3) ATTR_OUT(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libc__wdupenv_s_dbg)(__WCHAR16_TYPE__ **pbuf, size_t *pbuflen, __WCHAR16_TYPE__ const *varname, int block_type, char const *filename, int line);
INTDEF int NOTHROW_NCX(LIBDCALL libc__CrtCheckMemory)(void);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libc__CrtDoForAllClientObjects)(_PFNCRTDOFORALLCLIENTOBJECTS pfn, void *context);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libc__CrtIsValidPointer)(void const *ptr, __STDC_UINT_AS_SIZE_T num_bytes, int writable);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libc__CrtIsValidHeapPointer)(void const *heap_ptr);
INTDEF int NOTHROW_NCX(LIBDCALL libc__CrtIsMemoryBlock)(void const *ptr, __STDC_UINT_AS_SIZE_T num_bytes, __LONG32_TYPE__ *prequest_number, char **filename, int *line);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libc__CrtReportBlockType)(void const *ptr);
INTDEF void NOTHROW_NCX(LIBDCALL libc__CrtMemCheckpoint)(_CrtMemState *state);
INTDEF int NOTHROW_NCX(LIBDCALL libc__CrtMemDifference)(_CrtMemState *state, _CrtMemState const *old_state, _CrtMemState const *new_state);
INTDEF void NOTHROW_NCX(LIBDCALL libc__CrtMemDumpAllObjectsSince)(_CrtMemState const *state);
INTDEF void NOTHROW_NCX(LIBDCALL libc__CrtMemDumpStatistics)(_CrtMemState const *state);
INTDEF int NOTHROW_NCX(LIBDCALL libc__CrtDumpMemoryLeaks)(void);
INTDEF int NOTHROW_NCX(LIBDCALL libc__CrtSetCheckCount)(int check_count);
INTDEF ATTR_PURE int NOTHROW_NCX(LIBDCALL libc__CrtGetCheckCount)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CRTDBG_H */
