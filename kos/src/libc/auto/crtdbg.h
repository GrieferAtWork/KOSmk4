/* HASH CRC-32:0xcff4a65e */
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
#ifndef GUARD_LIBC_AUTO_CRTDBG_H
#define GUARD_LIBC_AUTO_CRTDBG_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <crtdbg.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc__aligned_msize_dbg)(void *ptr, size_t min_alignment, size_t offset);
INTDEF WUNUSED __WCHAR16_TYPE__ *NOTHROW_NCX(LIBCCALL libc__wtempnam_dbg)(__WCHAR16_TYPE__ const *dir_name, __WCHAR16_TYPE__ const *file_prefix, int block_type, char const *filename, int line);
INTDEF WUNUSED NONNULL((2)) __WCHAR16_TYPE__ *NOTHROW_NCX(LIBCCALL libc__wfullpath_dbg)(__WCHAR16_TYPE__ *full_path, __WCHAR16_TYPE__ const *path, size_t buflen, int block_type, char const *filename, int line);
INTDEF WUNUSED __WCHAR16_TYPE__ *NOTHROW_NCX(LIBCCALL libc__wgetdcwd_dbg)(int driveno, __WCHAR16_TYPE__ *buf, __STDC_INT_AS_SIZE_T buflen, int block_type, char const *filename, int line);
#define libc__wgetdcwd_lk_dbg libc__wgetdcwd_dbg
INTDEF _Check_return_wat_ NONNULL((3)) errno_t NOTHROW_NCX(LIBCCALL libc__wdupenv_s_dbg)(__WCHAR16_TYPE__ **pbuf, size_t *pbuflen, __WCHAR16_TYPE__ const *varname, int block_type, char const *filename, int line);
INTDEF int NOTHROW_NCX(LIBCCALL libc__CrtCheckMemory)(void);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc__CrtDoForAllClientObjects)(_PFNCRTDOFORALLCLIENTOBJECTS pfn, void *context);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__CrtIsValidPointer)(void const *ptr, __STDC_UINT_AS_SIZE_T num_bytes, int writable);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__CrtIsValidHeapPointer)(void const *heap_ptr);
INTDEF int NOTHROW_NCX(LIBCCALL libc__CrtIsMemoryBlock)(void const *ptr, __STDC_UINT_AS_SIZE_T num_bytes, __LONG32_TYPE__ *prequest_number, char **filename, int *line);
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc__CrtReportBlockType)(void const *ptr);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc__CrtMemCheckpoint)(/*out*/ _CrtMemState *state);
INTDEF NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBCCALL libc__CrtMemDifference)(/*out*/ _CrtMemState *state, _CrtMemState const *old_state, _CrtMemState const *new_state);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc__CrtMemDumpAllObjectsSince)(_CrtMemState const *state);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc__CrtMemDumpStatistics)(_CrtMemState const *state);
INTDEF int NOTHROW_NCX(LIBCCALL libc__CrtDumpMemoryLeaks)(void);
INTDEF int NOTHROW_NCX(LIBCCALL libc__CrtSetCheckCount)(int check_count);
INTDEF ATTR_PURE int NOTHROW_NCX(LIBCCALL libc__CrtGetCheckCount)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CRTDBG_H */
