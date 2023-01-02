/* HASH CRC-32:0x2767cef1 */
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
#ifndef GUARD_LIBC_AUTO_CRTDBG_C
#define GUARD_LIBC_AUTO_CRTDBG_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/crtdbg.h"
#include "corecrt_malloc.h"
#include "../user/direct.h"
#include "../user/malloc.h"
#include "parts.wchar.unistd.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/unistd.h"
#include "../user/wchar.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") int
NOTHROW_NCX(LIBDCALL libc__CrtSetDbgFlag)(int new_flag) {
	int result, *ptr;
	ptr = libc___p__crtDbgFlag();
	result = *ptr;
	*ptr = new_flag;
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) void *
NOTHROW_NCX(LIBDCALL libc__malloc_dbg)(size_t num_bytes,
                                       int block_type,
                                       char const *filename,
                                       int line) {
	(void)block_type;
	(void)filename;
	(void)line;
	return libc_malloc(num_bytes);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1, 2)) void *
NOTHROW_NCX(LIBDCALL libc__calloc_dbg)(size_t count,
                                       size_t num_bytes,
                                       int block_type,
                                       char const *filename,
                                       int line) {
	(void)block_type;
	(void)filename;
	(void)line;
	return libc_calloc(count, num_bytes);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") WUNUSED ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBDCALL libc__realloc_dbg)(void *ptr,
                                        size_t num_bytes,
                                        int block_type,
                                        char const *filename,
                                        int line) {
	(void)block_type;
	(void)filename;
	(void)line;
	return libc_realloc(ptr, num_bytes);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *
NOTHROW_NCX(LIBDCALL libc__recalloc_dbg)(void *ptr,
                                         size_t count,
                                         size_t num_bytes,
                                         int block_type,
                                         char const *filename,
                                         int line) {
	(void)block_type;
	(void)filename;
	(void)line;
	return libc_recallocv(ptr, count, num_bytes);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") WUNUSED ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBDCALL libc__expand_dbg)(void *ptr,
                                       size_t num_bytes,
                                       int block_type,
                                       char const *filename,
                                       int line) {
	(void)block_type;
	(void)filename;
	(void)line;
	return libc_realloc_in_place(ptr, num_bytes);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") void
NOTHROW_NCX(LIBDCALL libc__free_dbg)(void *ptr,
                                     int block_type) {
	(void)block_type;
	libc_free(ptr);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") ATTR_PURE WUNUSED size_t
NOTHROW_NCX(LIBDCALL libc__msize_dbg)(void *ptr,
                                      int block_type) {
	(void)block_type;
	return libc_malloc_usable_size(ptr);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") ATTR_PURE WUNUSED size_t
NOTHROW_NCX(LIBDCALL libc__aligned_msize_dbg)(void *ptr,
                                              size_t min_alignment,
                                              size_t offset) {
	return libc__aligned_msize(ptr, min_alignment, offset);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") ATTR_MALLOC WUNUSED ATTR_ALLOC_ALIGN(2) ATTR_ALLOC_SIZE((1)) void *
NOTHROW_NCX(LIBDCALL libc__aligned_malloc_dbg)(size_t num_bytes,
                                               size_t min_alignment,
                                               char const *filename,
                                               int line) {
	(void)filename;
	(void)line;
	return libc__aligned_malloc(num_bytes, min_alignment);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") WUNUSED ATTR_ALLOC_ALIGN(3) ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBDCALL libc__aligned_realloc_dbg)(void *ptr,
                                                size_t num_bytes,
                                                size_t min_alignment,
                                                char const *filename,
                                                int line) {
	(void)filename;
	(void)line;
	return libc__aligned_realloc(ptr, num_bytes, min_alignment);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") WUNUSED ATTR_ALLOC_ALIGN(4) ATTR_ALLOC_SIZE((2, 3)) void *
NOTHROW_NCX(LIBDCALL libc__aligned_recalloc_dbg)(void *ptr,
                                                 size_t count,
                                                 size_t num_bytes,
                                                 size_t min_alignment,
                                                 char const *filename,
                                                 int line) {
	(void)filename;
	(void)line;
	return libc__aligned_recalloc(ptr, count, num_bytes, min_alignment);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) void *
NOTHROW_NCX(LIBDCALL libc__aligned_offset_malloc_dbg)(size_t num_bytes,
                                                      size_t min_alignment,
                                                      size_t offset,
                                                      char const *filename,
                                                      int line) {
	(void)filename;
	(void)line;
	return libc__aligned_offset_malloc(num_bytes, min_alignment, offset);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") WUNUSED ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBDCALL libc__aligned_offset_realloc_dbg)(void *ptr,
                                                       size_t num_bytes,
                                                       size_t min_alignment,
                                                       size_t offset,
                                                       char const *filename,
                                                       int line) {
	(void)filename;
	(void)line;
	return libc__aligned_offset_realloc(ptr, num_bytes, min_alignment, offset);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *
NOTHROW_NCX(LIBDCALL libc__aligned_offset_recalloc_dbg)(void *ptr,
                                                        size_t count,
                                                        size_t num_bytes,
                                                        size_t min_alignment,
                                                        size_t offset,
                                                        char const *filename,
                                                        int line) {
	(void)filename;
	(void)line;
	return libc__aligned_offset_recalloc(ptr, count, num_bytes, min_alignment, offset);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") void
NOTHROW_NCX(LIBDCALL libc__aligned_free_dbg)(void *ptr) {
	libc__aligned_free(ptr);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") ATTR_MALLOC WUNUSED char *
NOTHROW_NCX(LIBDCALL libc__strdup_dbg)(char const *string,
                                       int block_type,
                                       char const *filename,
                                       int line) {
	(void)block_type;
	(void)filename;
	(void)line;
	return libc_strdup(string);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") ATTR_MALLOC WUNUSED __WCHAR16_TYPE__ *
NOTHROW_NCX(LIBDCALL libc__wcsdup_dbg)(__WCHAR16_TYPE__ const *string,
                                       int block_type,
                                       char const *filename,
                                       int line) {
	(void)block_type;
	(void)filename;
	(void)line;
	return (__WCHAR16_TYPE__ *)libd_wcsdup((char16_t const *)string);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") ATTR_MALLOC WUNUSED char *
NOTHROW_NCX(LIBDCALL libc__tempnam_dbg)(char const *dir_name,
                                        char const *file_prefix,
                                        int block_type,
                                        char const *filename,
                                        int line) {
	(void)block_type;
	(void)filename;
	(void)line;
	return libc_tempnam(dir_name, file_prefix);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") WUNUSED __WCHAR16_TYPE__ *
NOTHROW_NCX(LIBDCALL libc__wtempnam_dbg)(__WCHAR16_TYPE__ const *dir_name,
                                         __WCHAR16_TYPE__ const *file_prefix,
                                         int block_type,
                                         char const *filename,
                                         int line) {
	(void)block_type;
	(void)filename;
	(void)line;
	(void)dir_name;
	(void)file_prefix;
	/* TODO: c16tempnam() */
	COMPILER_IMPURE();
	return NULL;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") WUNUSED ATTR_IN(2) ATTR_OUTS(1, 3) char *
NOTHROW_NCX(LIBDCALL libc__fullpath_dbg)(char *full_path,
                                         char const *path,
                                         size_t bufsize,
                                         int block_type,
                                         char const *filename,
                                         int line) {
	(void)block_type;
	(void)filename;
	(void)line;
	return libc__fullpath(full_path, path, bufsize);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") WUNUSED ATTR_IN(2) ATTR_OUTS(1, 3) __WCHAR16_TYPE__ *
NOTHROW_NCX(LIBDCALL libc__wfullpath_dbg)(__WCHAR16_TYPE__ *full_path,
                                          __WCHAR16_TYPE__ const *path,
                                          size_t buflen,
                                          int block_type,
                                          char const *filename,
                                          int line) {
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") WUNUSED ATTR_OUTS(1, 2) char *
NOTHROW_NCX(LIBDCALL libc__getcwd_dbg)(char *buf,
                                       __STDC_INT_AS_SIZE_T bufsize,
                                       int block_type,
                                       char const *filename,
                                       int line) {
	(void)block_type;
	(void)filename;
	(void)line;
	return libc_getcwd(buf, (size_t)bufsize);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") WUNUSED ATTR_OUTS(1, 2) __WCHAR16_TYPE__ *
NOTHROW_NCX(LIBDCALL libc__wgetcwd_dbg)(__WCHAR16_TYPE__ *buf,
                                        __STDC_INT_AS_SIZE_T buflen,
                                        int block_type,
                                        char const *filename,
                                        int line) {
	(void)block_type;
	(void)filename;
	(void)line;
	return (__WCHAR16_TYPE__ *)libd_wgetcwd((char16_t *)buf, buflen);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") WUNUSED ATTR_OUTS(2, 3) char *
NOTHROW_NCX(LIBDCALL libc__getdcwd_dbg)(int driveno,
                                        char *buf,
                                        __STDC_INT_AS_SIZE_T bufsize,
                                        int block_type,
                                        char const *filename,
                                        int line) {
	(void)block_type;
	(void)filename;
	(void)line;
	return libc__getdcwd(driveno, buf, bufsize);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") WUNUSED ATTR_OUTS(2, 3) __WCHAR16_TYPE__ *
NOTHROW_NCX(LIBDCALL libc__wgetdcwd_dbg)(int driveno,
                                         __WCHAR16_TYPE__ *buf,
                                         __STDC_INT_AS_SIZE_T buflen,
                                         int block_type,
                                         char const *filename,
                                         int line) {
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") _Check_return_wat_ ATTR_IN(3) ATTR_OUT(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBDCALL libc__dupenv_s_dbg)(char **pbuf,
                                         size_t *pbufsize,
                                         char const *varname,
                                         int block_type,
                                         char const *filename,
                                         int line) {
	(void)block_type;
	(void)filename;
	(void)line;
	return libc__dupenv_s(pbuf, pbufsize, varname);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") _Check_return_wat_ ATTR_IN(3) ATTR_OUT(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBDCALL libc__wdupenv_s_dbg)(__WCHAR16_TYPE__ **pbuf,
                                          size_t *pbuflen,
                                          __WCHAR16_TYPE__ const *varname,
                                          int block_type,
                                          char const *filename,
                                          int line) {
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") int
NOTHROW_NCX(LIBDCALL libc__CrtCheckMemory)(void) {
	COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libc__CrtDoForAllClientObjects)(_PFNCRTDOFORALLCLIENTOBJECTS pfn,
                                                     void *context) {
	COMPILER_IMPURE();
	(void)pfn;
	(void)context;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libc__CrtIsValidPointer)(void const *ptr,
                                              __STDC_UINT_AS_SIZE_T num_bytes,
                                              int writable) {
	COMPILER_IMPURE();
	(void)num_bytes;
	(void)writable;
	return ptr != NULL;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libc__CrtIsValidHeapPointer)(void const *heap_ptr) {
	COMPILER_IMPURE();
	return heap_ptr != NULL;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") int
NOTHROW_NCX(LIBDCALL libc__CrtIsMemoryBlock)(void const *ptr,
                                             __STDC_UINT_AS_SIZE_T num_bytes,
                                             __LONG32_TYPE__ *prequest_number,
                                             char **filename,
                                             int *line) {
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libc__CrtReportBlockType)(void const *ptr) {
	COMPILER_IMPURE();
	return ptr ? 1 /*_NORMAL_BLOCK*/ : 0 /*_FREE_BLOCK*/;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") ATTR_OUT(1) void
NOTHROW_NCX(LIBDCALL libc__CrtMemCheckpoint)(_CrtMemState *state) {
	libc_bzero(state, sizeof(*state));
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1) int
NOTHROW_NCX(LIBDCALL libc__CrtMemDifference)(_CrtMemState *state,
                                             _CrtMemState const *old_state,
                                             _CrtMemState const *new_state) {
	(void)old_state;
	(void)new_state;
	libc_bzero(state, sizeof(*state));
	return 0;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") ATTR_IN(1) void
NOTHROW_NCX(LIBDCALL libc__CrtMemDumpAllObjectsSince)(_CrtMemState const *state) {
	COMPILER_IMPURE();
	(void)state;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") ATTR_IN(1) void
NOTHROW_NCX(LIBDCALL libc__CrtMemDumpStatistics)(_CrtMemState const *state) {
	COMPILER_IMPURE();
	(void)state;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") int
NOTHROW_NCX(LIBDCALL libc__CrtDumpMemoryLeaks)(void) {
	COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") int
NOTHROW_NCX(LIBDCALL libc__CrtSetCheckCount)(int check_count) {
	(void)check_count;
	COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") ATTR_PURE int
NOTHROW_NCX(LIBDCALL libc__CrtGetCheckCount)(void) {
	COMPILER_IMPURE();
	return 0;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_CrtSetDbgFlag, libc__CrtSetDbgFlag);
DEFINE_PUBLIC_ALIAS(_malloc_dbg, libc__malloc_dbg);
DEFINE_PUBLIC_ALIAS(_calloc_dbg, libc__calloc_dbg);
DEFINE_PUBLIC_ALIAS(_realloc_dbg, libc__realloc_dbg);
DEFINE_PUBLIC_ALIAS(_recalloc_dbg, libc__recalloc_dbg);
DEFINE_PUBLIC_ALIAS(_expand_dbg, libc__expand_dbg);
DEFINE_PUBLIC_ALIAS(_free_dbg, libc__free_dbg);
DEFINE_PUBLIC_ALIAS(_msize_dbg, libc__msize_dbg);
DEFINE_PUBLIC_ALIAS(_aligned_msize_dbg, libc__aligned_msize_dbg);
DEFINE_PUBLIC_ALIAS(_aligned_malloc_dbg, libc__aligned_malloc_dbg);
DEFINE_PUBLIC_ALIAS(_aligned_realloc_dbg, libc__aligned_realloc_dbg);
DEFINE_PUBLIC_ALIAS(_aligned_recalloc_dbg, libc__aligned_recalloc_dbg);
DEFINE_PUBLIC_ALIAS(_aligned_offset_malloc_dbg, libc__aligned_offset_malloc_dbg);
DEFINE_PUBLIC_ALIAS(_aligned_offset_realloc_dbg, libc__aligned_offset_realloc_dbg);
DEFINE_PUBLIC_ALIAS(_aligned_offset_recalloc_dbg, libc__aligned_offset_recalloc_dbg);
DEFINE_PUBLIC_ALIAS(_aligned_free_dbg, libc__aligned_free_dbg);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_mbsdup_dbg, libc__strdup_dbg);
DEFINE_PUBLIC_ALIAS(mbsdup_dbg, libc__strdup_dbg);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(_strdup_dbg, libc__strdup_dbg);
DEFINE_PUBLIC_ALIAS(_wcsdup_dbg, libc__wcsdup_dbg);
DEFINE_PUBLIC_ALIAS(_tempnam_dbg, libc__tempnam_dbg);
DEFINE_PUBLIC_ALIAS(_wtempnam_dbg, libc__wtempnam_dbg);
DEFINE_PUBLIC_ALIAS(_fullpath_dbg, libc__fullpath_dbg);
DEFINE_PUBLIC_ALIAS(_wfullpath_dbg, libc__wfullpath_dbg);
DEFINE_PUBLIC_ALIAS(_getcwd_dbg, libc__getcwd_dbg);
DEFINE_PUBLIC_ALIAS(_wgetcwd_dbg, libc__wgetcwd_dbg);
DEFINE_PUBLIC_ALIAS(_getdcwd_dbg, libc__getdcwd_dbg);
DEFINE_PUBLIC_ALIAS(_wgetdcwd_dbg, libc__wgetdcwd_dbg);
DEFINE_PUBLIC_ALIAS(_dupenv_s_dbg, libc__dupenv_s_dbg);
DEFINE_PUBLIC_ALIAS(_wdupenv_s_dbg, libc__wdupenv_s_dbg);
DEFINE_PUBLIC_ALIAS(_CrtCheckMemory, libc__CrtCheckMemory);
DEFINE_PUBLIC_ALIAS(_CrtDoForAllClientObjects, libc__CrtDoForAllClientObjects);
DEFINE_PUBLIC_ALIAS(_CrtIsValidPointer, libc__CrtIsValidPointer);
DEFINE_PUBLIC_ALIAS(_CrtIsValidHeapPointer, libc__CrtIsValidHeapPointer);
DEFINE_PUBLIC_ALIAS(_CrtIsMemoryBlock, libc__CrtIsMemoryBlock);
DEFINE_PUBLIC_ALIAS(_CrtReportBlockType, libc__CrtReportBlockType);
DEFINE_PUBLIC_ALIAS(_CrtMemCheckpoint, libc__CrtMemCheckpoint);
DEFINE_PUBLIC_ALIAS(_CrtMemDifference, libc__CrtMemDifference);
DEFINE_PUBLIC_ALIAS(_CrtMemDumpAllObjectsSince, libc__CrtMemDumpAllObjectsSince);
DEFINE_PUBLIC_ALIAS(_CrtMemDumpStatistics, libc__CrtMemDumpStatistics);
DEFINE_PUBLIC_ALIAS(_CrtDumpMemoryLeaks, libc__CrtDumpMemoryLeaks);
DEFINE_PUBLIC_ALIAS(_CrtSetCheckCount, libc__CrtSetCheckCount);
DEFINE_PUBLIC_ALIAS(_CrtGetCheckCount, libc__CrtGetCheckCount);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_CRTDBG_C */
