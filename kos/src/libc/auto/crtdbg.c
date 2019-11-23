/* HASH CRC-32:0xb9833f1 */
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
#ifndef GUARD_LIBC_AUTO_CRTDBG_C
#define GUARD_LIBC_AUTO_CRTDBG_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "crtdbg.h"
#include "stdlib.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._aligned_msize_dbg") size_t
NOTHROW_NCX(LIBCCALL libc__aligned_msize_dbg)(void *ptr,
                                              size_t min_alignment,
                                              size_t offset) {
#line 344 "kos/src/libc/magic/crtdbg.c"
	return libc__aligned_msize(ptr, min_alignment, offset);
}

INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._wtempnam_dbg") __WCHAR16_TYPE__ *
NOTHROW_NCX(LIBCCALL libc__wtempnam_dbg)(__WCHAR16_TYPE__ const *dir_name,
                                         __WCHAR16_TYPE__ const *file_prefix,
                                         int block_type,
                                         char const *filename,
                                         int line) {
#line 440 "kos/src/libc/magic/crtdbg.c"
	(void)block_type;
	(void)filename;
	(void)line;
	(void)dir_name;
	(void)file_prefix;
	/* TODO: c16tempnam() */
	COMPILER_IMPURE();
	return NULL;
}

INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._wfullpath_dbg") __WCHAR16_TYPE__ *
NOTHROW_NCX(LIBCCALL libc__wfullpath_dbg)(__WCHAR16_TYPE__ *full_path,
                                          __WCHAR16_TYPE__ const *path,
                                          size_t buflen,
                                          int block_type,
                                          char const *filename,
                                          int line) {
#line 464 "kos/src/libc/magic/crtdbg.c"
	(void)block_type;
	(void)filename;
	(void)line;
	(void)full_path;
	(void)path;
	(void)buflen;
	/* TODO: c16fullpath() */
	COMPILER_IMPURE();
	return NULL;
}

INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._wgetdcwd_dbg") __WCHAR16_TYPE__ *
NOTHROW_NCX(LIBCCALL libc__wgetdcwd_dbg)(int driveno,
                                         __WCHAR16_TYPE__ *buf,
                                         __STDC_INT_AS_SIZE_T buflen,
                                         int block_type,
                                         char const *filename,
                                         int line) {
#line 507 "kos/src/libc/magic/crtdbg.c"
	(void)block_type;
	(void)filename;
	(void)line;
	(void)driveno;
	(void)buf;
	(void)buflen;
	/* TODO: c16getdcwd() */
	COMPILER_IMPURE();
	return NULL;
}

INTERN _Check_return_wat_ NONNULL((3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._wdupenv_s_dbg") errno_t
NOTHROW_NCX(LIBCCALL libc__wdupenv_s_dbg)(__WCHAR16_TYPE__ **pbuf,
                                          size_t *pbuflen,
                                          __WCHAR16_TYPE__ const *varname,
                                          int block_type,
                                          char const *filename,
                                          int line) {
#line 535 "kos/src/libc/magic/crtdbg.c"
	(void)block_type;
	(void)filename;
	(void)line;
	(void)pbuf;
	(void)pbuflen;
	(void)varname;
	/* TODO: c16dupenv_s() */
	COMPILER_IMPURE();
	return 1;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtCheckMemory") int
NOTHROW_NCX(LIBCCALL libc__CrtCheckMemory)(void) {
#line 547 "kos/src/libc/magic/crtdbg.c"
	COMPILER_IMPURE();
	return 0;
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtDoForAllClientObjects") void
NOTHROW_NCX(LIBCCALL libc__CrtDoForAllClientObjects)(_PFNCRTDOFORALLCLIENTOBJECTS pfn,
                                                     void *context) {
#line 554 "kos/src/libc/magic/crtdbg.c"
	COMPILER_IMPURE();
	(void)pfn;
	(void)context;
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtIsValidPointer") int
NOTHROW_NCX(LIBCCALL libc__CrtIsValidPointer)(void const *ptr,
                                              __STDC_UINT_AS_SIZE_T num_bytes,
                                              int writable) {
#line 561 "kos/src/libc/magic/crtdbg.c"
	COMPILER_IMPURE();
	(void)num_bytes;
	(void)writable;
	return ptr != NULL;
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtIsValidHeapPointer") int
NOTHROW_NCX(LIBCCALL libc__CrtIsValidHeapPointer)(void const *heap_ptr) {
#line 569 "kos/src/libc/magic/crtdbg.c"
	COMPILER_IMPURE();
	return heap_ptr != NULL;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtIsMemoryBlock") int
NOTHROW_NCX(LIBCCALL libc__CrtIsMemoryBlock)(void const *ptr,
                                             __STDC_UINT_AS_SIZE_T num_bytes,
                                             __LONG32_TYPE__ *prequest_number,
                                             char **filename,
                                             int *line) {
#line 578 "kos/src/libc/magic/crtdbg.c"
	(void)ptr;
	(void)num_bytes;
	if (prequest_number)
		*prequest_number = 0;
	if (filename)
		*filename = NULL;
	if (line)
		*line = 0;
	return 0;
}

INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtReportBlockType") int
NOTHROW_NCX(LIBCCALL libc__CrtReportBlockType)(void const *ptr) {
#line 591 "kos/src/libc/magic/crtdbg.c"
	COMPILER_IMPURE();
	return ptr ? 1 /*_NORMAL_BLOCK*/ : 0 /*_FREE_BLOCK*/;
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtMemCheckpoint") void
NOTHROW_NCX(LIBCCALL libc__CrtMemCheckpoint)(/*out*/ _CrtMemState *state) {
#line 597 "kos/src/libc/magic/crtdbg.c"
	memset(state, 0, sizeof(*state));
}

INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtMemDifference") int
NOTHROW_NCX(LIBCCALL libc__CrtMemDifference)(/*out*/ _CrtMemState *state,
                                             _CrtMemState const *old_state,
                                             _CrtMemState const *new_state) {
#line 604 "kos/src/libc/magic/crtdbg.c"
	(void)old_state;
	(void)new_state;
	memset(state, 0, sizeof(*state));
	return 0;
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtMemDumpAllObjectsSince") void
NOTHROW_NCX(LIBCCALL libc__CrtMemDumpAllObjectsSince)(_CrtMemState const *state) {
#line 612 "kos/src/libc/magic/crtdbg.c"
	COMPILER_IMPURE();
	(void)state;
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtMemDumpStatistics") void
NOTHROW_NCX(LIBCCALL libc__CrtMemDumpStatistics)(_CrtMemState const *state) {
#line 618 "kos/src/libc/magic/crtdbg.c"
	COMPILER_IMPURE();
	(void)state;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtDumpMemoryLeaks") int
NOTHROW_NCX(LIBCCALL libc__CrtDumpMemoryLeaks)(void) {
#line 624 "kos/src/libc/magic/crtdbg.c"
	COMPILER_IMPURE();
	return 0;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtSetCheckCount") int
NOTHROW_NCX(LIBCCALL libc__CrtSetCheckCount)(int check_count) {
#line 630 "kos/src/libc/magic/crtdbg.c"
	(void)check_count;
	COMPILER_IMPURE();
	return 0;
}

INTERN ATTR_PURE
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtGetCheckCount") int
NOTHROW_NCX(LIBCCALL libc__CrtGetCheckCount)(void) {
#line 637 "kos/src/libc/magic/crtdbg.c"
	COMPILER_IMPURE();
	return 0;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(_aligned_msize_dbg, libc__aligned_msize_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_wtempnam_dbg, libc__wtempnam_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_wfullpath_dbg, libc__wfullpath_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_wgetdcwd_dbg, libc__wgetdcwd_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_wgetdcwd_lk_dbg, libc__wgetdcwd_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_wdupenv_s_dbg, libc__wdupenv_s_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtCheckMemory, libc__CrtCheckMemory);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtDoForAllClientObjects, libc__CrtDoForAllClientObjects);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtIsValidPointer, libc__CrtIsValidPointer);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtIsValidHeapPointer, libc__CrtIsValidHeapPointer);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtIsMemoryBlock, libc__CrtIsMemoryBlock);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtReportBlockType, libc__CrtReportBlockType);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtMemCheckpoint, libc__CrtMemCheckpoint);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtMemDifference, libc__CrtMemDifference);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtMemDumpAllObjectsSince, libc__CrtMemDumpAllObjectsSince);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtMemDumpStatistics, libc__CrtMemDumpStatistics);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtDumpMemoryLeaks, libc__CrtDumpMemoryLeaks);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtSetCheckCount, libc__CrtSetCheckCount);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtGetCheckCount, libc__CrtGetCheckCount);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CRTDBG_C */
