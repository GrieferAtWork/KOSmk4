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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_CRTDBG_C
#define GUARD_LIBC_USER_CRTDBG_C 1

#include "../api.h"
/**/

#include "crtdbg.h"
#include "direct.h"
#include "malloc.h"
#include "parts.wchar.unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "wchar.h"

#define libc_c16dup    libd__wcsdup
#define libc_c16getcwd libd__wgetcwd
#define libc__msize    libc_malloc_usable_size

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:__p__crtAssertBusy,hash:CRC-32=0x4f2c976a]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc.__p__crtAssertBusy") __LONG32_TYPE__ *
NOTHROW_NCX(LIBCCALL libc___p__crtAssertBusy)(void)
/*[[[body:__p__crtAssertBusy]]]*/
{
	CRT_UNIMPLEMENTED("__p__crtAssertBusy"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:__p__crtAssertBusy]]]*/

/*[[[head:__p__crtBreakAlloc,hash:CRC-32=0x6a2f7a88]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc.__p__crtBreakAlloc") __LONG32_TYPE__ *
NOTHROW_NCX(LIBCCALL libc___p__crtBreakAlloc)(void)
/*[[[body:__p__crtBreakAlloc]]]*/
{
	CRT_UNIMPLEMENTED("__p__crtBreakAlloc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:__p__crtBreakAlloc]]]*/

/*[[[head:__p__crtDbgFlag,hash:CRC-32=0xed6e2816]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc.__p__crtDbgFlag") int *
NOTHROW_NCX(LIBCCALL libc___p__crtDbgFlag)(void)
/*[[[body:__p__crtDbgFlag]]]*/
{
	CRT_UNIMPLEMENTED("__p__crtDbgFlag"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:__p__crtDbgFlag]]]*/

/*[[[head:_CrtGetReportHook,hash:CRC-32=0x87773fbb]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtGetReportHook") _CRT_REPORT_HOOK
NOTHROW_NCX(LIBCCALL libc__CrtGetReportHook)(void)
/*[[[body:_CrtGetReportHook]]]*/
{
	CRT_UNIMPLEMENTED("_CrtGetReportHook"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_CrtGetReportHook]]]*/

/*[[[head:_CrtSetReportHook,hash:CRC-32=0x616bc36a]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtSetReportHook") _CRT_REPORT_HOOK
NOTHROW_NCX(LIBCCALL libc__CrtSetReportHook)(_CRT_REPORT_HOOK pfn_new_hook)
/*[[[body:_CrtSetReportHook]]]*/
{
	(void)pfn_new_hook;
	CRT_UNIMPLEMENTED("_CrtSetReportHook"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_CrtSetReportHook]]]*/

/*[[[head:_CrtSetReportHook2,hash:CRC-32=0xf9a4e19e]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtSetReportHook2") int
NOTHROW_NCX(LIBCCALL libc__CrtSetReportHook2)(int mode,
                                              _CRT_REPORT_HOOK pfn_new_hook)
/*[[[body:_CrtSetReportHook2]]]*/
{
	(void)mode;
	(void)pfn_new_hook;
	CRT_UNIMPLEMENTED("_CrtSetReportHook2"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_CrtSetReportHook2]]]*/

/*[[[head:_CrtSetReportHookW2,hash:CRC-32=0x2b644052]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtSetReportHookW2") int
NOTHROW_NCX(LIBCCALL libc__CrtSetReportHookW2)(int mode,
                                               _CRT_REPORT_HOOKW pfn_new_hook)
/*[[[body:_CrtSetReportHookW2]]]*/
{
	(void)mode;
	(void)pfn_new_hook;
	CRT_UNIMPLEMENTED("_CrtSetReportHookW2"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_CrtSetReportHookW2]]]*/

/*[[[head:_CrtGetAllocHook,hash:CRC-32=0x847277e9]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtGetAllocHook") _CRT_ALLOC_HOOK
NOTHROW_NCX(LIBCCALL libc__CrtGetAllocHook)(void)
/*[[[body:_CrtGetAllocHook]]]*/
{
	CRT_UNIMPLEMENTED("_CrtGetAllocHook"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_CrtGetAllocHook]]]*/

/*[[[head:_CrtSetAllocHook,hash:CRC-32=0x93cc8cc3]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtSetAllocHook") _CRT_ALLOC_HOOK
NOTHROW_NCX(LIBCCALL libc__CrtSetAllocHook)(_CRT_ALLOC_HOOK pfn_new_hook)
/*[[[body:_CrtSetAllocHook]]]*/
{
	(void)pfn_new_hook;
	CRT_UNIMPLEMENTED("_CrtSetAllocHook"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_CrtSetAllocHook]]]*/

/*[[[head:_CrtGetDumpClient,hash:CRC-32=0xaa4ef986]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtGetDumpClient") _CRT_DUMP_CLIENT
NOTHROW_NCX(LIBCCALL libc__CrtGetDumpClient)(void)
/*[[[body:_CrtGetDumpClient]]]*/
{
	CRT_UNIMPLEMENTED("_CrtGetDumpClient"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_CrtGetDumpClient]]]*/

/*[[[head:_CrtSetDumpClient,hash:CRC-32=0x4b4ce95a]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtSetDumpClient") _CRT_DUMP_CLIENT
NOTHROW_NCX(LIBCCALL libc__CrtSetDumpClient)(_CRT_DUMP_CLIENT pfn_new_dump)
/*[[[body:_CrtSetDumpClient]]]*/
{
	(void)pfn_new_dump;
	CRT_UNIMPLEMENTED("_CrtSetDumpClient"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_CrtSetDumpClient]]]*/

/*[[[head:_CrtSetReportMode,hash:CRC-32=0x1ef39768]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtSetReportMode") int
NOTHROW_NCX(LIBCCALL libc__CrtSetReportMode)(int report_type,
                                             int report_mode)
/*[[[body:_CrtSetReportMode]]]*/
{
	(void)report_type;
	(void)report_mode;
	CRT_UNIMPLEMENTED("_CrtSetReportMode"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_CrtSetReportMode]]]*/

/*[[[head:_CrtSetReportFile,hash:CRC-32=0xa46a0cfa]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtSetReportFile") _HFILE
NOTHROW_NCX(LIBCCALL libc__CrtSetReportFile)(int report_type,
                                             _HFILE report_file)
/*[[[body:_CrtSetReportFile]]]*/
{
	(void)report_type;
	(void)report_file;
	CRT_UNIMPLEMENTED("_CrtSetReportFile"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_CrtSetReportFile]]]*/

/*[[[head:_CrtDbgReport,hash:CRC-32=0x203cce42]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtDbgReport") int
NOTHROW_NCX(VLIBCCALL libc__CrtDbgReport)(int report_type,
                                          char const *filename,
                                          int line,
                                          char const *module_name,
                                          char const *format,
                                          ...)
/*[[[body:_CrtDbgReport]]]*/
{
	(void)report_type;
	(void)filename;
	(void)line;
	(void)module_name;
	(void)format;
	CRT_UNIMPLEMENTED("_CrtDbgReport"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_CrtDbgReport]]]*/

/*[[[head:_CrtSetDebugFillThreshold,hash:CRC-32=0xaf8d91fa]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtSetDebugFillThreshold") size_t
NOTHROW_NCX(LIBCCALL libc__CrtSetDebugFillThreshold)(size_t new_debug_fill_threshold)
/*[[[body:_CrtSetDebugFillThreshold]]]*/
{
	(void)new_debug_fill_threshold;
	CRT_UNIMPLEMENTED("_CrtSetDebugFillThreshold"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_CrtSetDebugFillThreshold]]]*/

/*[[[head:_CrtDbgReportW,hash:CRC-32=0xe1eb92ed]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtDbgReportW") int
NOTHROW_NCX(VLIBCCALL libc__CrtDbgReportW)(int report_type,
                                           __WCHAR16_TYPE__ const *filename,
                                           int line,
                                           __WCHAR16_TYPE__ const *module_name,
                                           __WCHAR16_TYPE__ const *format,
                                           ...)
/*[[[body:_CrtDbgReportW]]]*/
{
	(void)report_type;
	(void)filename;
	(void)line;
	(void)module_name;
	(void)format;
	CRT_UNIMPLEMENTED("_CrtDbgReportW"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_CrtDbgReportW]]]*/

/*[[[head:_CrtDbgBreak,hash:CRC-32=0x496b21e0]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtDbgBreak") void
NOTHROW_NCX(LIBCCALL libc__CrtDbgBreak)(void)
/*[[[body:_CrtDbgBreak]]]*/
{
	CRT_UNIMPLEMENTED("_CrtDbgBreak"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:_CrtDbgBreak]]]*/

/*[[[head:_CrtSetBreakAlloc,hash:CRC-32=0x88eb043f]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtSetBreakAlloc") __LONG32_TYPE__
NOTHROW_NCX(LIBCCALL libc__CrtSetBreakAlloc)(__LONG32_TYPE__ break_alloc)
/*[[[body:_CrtSetBreakAlloc]]]*/
{
	(void)break_alloc;
	CRT_UNIMPLEMENTED("_CrtSetBreakAlloc"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_CrtSetBreakAlloc]]]*/

/*[[[head:_malloc_dbg,hash:CRC-32=0xc51cdf7e]]]*/
INTERN ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._malloc_dbg") void *
NOTHROW_NCX(LIBCCALL libc__malloc_dbg)(size_t num_bytes,
                                       int block_type,
                                       char const *filename,
                                       int line)
/*[[[body:_malloc_dbg]]]*/
/*AUTO*/{
	(void)block_type;
	(void)filename;
	(void)line;
	return libc_malloc(num_bytes);
}
/*[[[end:_malloc_dbg]]]*/

/*[[[head:_calloc_dbg,hash:CRC-32=0x36a131f9]]]*/
INTERN ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._calloc_dbg") void *
NOTHROW_NCX(LIBCCALL libc__calloc_dbg)(size_t count,
                                       size_t num_bytes,
                                       int block_type,
                                       char const *filename,
                                       int line)
/*[[[body:_calloc_dbg]]]*/
/*AUTO*/{
	(void)block_type;
	(void)filename;
	(void)line;
	return libc_calloc(count, num_bytes);
}
/*[[[end:_calloc_dbg]]]*/

/*[[[head:_realloc_dbg,hash:CRC-32=0xc9ec3dc2]]]*/
INTERN WUNUSED ATTR_ALLOC_SIZE((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._realloc_dbg") void *
NOTHROW_NCX(LIBCCALL libc__realloc_dbg)(void *ptr,
                                        size_t num_bytes,
                                        int block_type,
                                        char const *filename,
                                        int line)
/*[[[body:_realloc_dbg]]]*/
/*AUTO*/{
	(void)block_type;
	(void)filename;
	(void)line;
	return libc_realloc(ptr, num_bytes);
}
/*[[[end:_realloc_dbg]]]*/

/*[[[head:_recalloc_dbg,hash:CRC-32=0x54044ac6]]]*/
INTERN WUNUSED ATTR_ALLOC_SIZE((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._recalloc_dbg") void *
NOTHROW_NCX(LIBCCALL libc__recalloc_dbg)(void *ptr,
                                         size_t count,
                                         size_t num_bytes,
                                         int block_type,
                                         char const *filename,
                                         int line)
/*[[[body:_recalloc_dbg]]]*/
/*AUTO*/{
	(void)block_type;
	(void)filename;
	(void)line;
	return libc_recallocv(ptr, count, num_bytes);
}
/*[[[end:_recalloc_dbg]]]*/

/*[[[head:_expand_dbg,hash:CRC-32=0xe7dd7e2f]]]*/
INTERN WUNUSED ATTR_ALLOC_SIZE((2)) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._expand_dbg") void *
NOTHROW_NCX(LIBCCALL libc__expand_dbg)(void *ptr,
                                       size_t num_bytes,
                                       int block_type,
                                       char const *filename,
                                       int line)
/*[[[body:_expand_dbg]]]*/
/*AUTO*/{
	(void)block_type;
	(void)filename;
	(void)line;
	return libc_realloc_in_place(ptr, num_bytes);
}
/*[[[end:_expand_dbg]]]*/

/*[[[head:_free_dbg,hash:CRC-32=0xa52c85d5]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._free_dbg") void
NOTHROW_NCX(LIBCCALL libc__free_dbg)(void *ptr,
                                     int block_type)
/*[[[body:_free_dbg]]]*/
/*AUTO*/{
	(void)block_type;
	libc_free(ptr);
}
/*[[[end:_free_dbg]]]*/

/*[[[head:_msize_dbg,hash:CRC-32=0xc95d3a62]]]*/
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._msize_dbg") size_t
NOTHROW_NCX(LIBCCALL libc__msize_dbg)(void *ptr,
                                      int block_type)
/*[[[body:_msize_dbg]]]*/
/*AUTO*/{
	(void)block_type;
	return libc__msize(ptr);
}
/*[[[end:_msize_dbg]]]*/


/*[[[head:_aligned_malloc_dbg,hash:CRC-32=0x68c67824]]]*/
INTERN ATTR_MALLOC WUNUSED ATTR_ALLOC_ALIGN(2) ATTR_ALLOC_SIZE((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._aligned_malloc_dbg") void *
NOTHROW_NCX(LIBCCALL libc__aligned_malloc_dbg)(size_t num_bytes,
                                               size_t min_alignment,
                                               char const *filename,
                                               int line)
/*[[[body:_aligned_malloc_dbg]]]*/
/*AUTO*/{
	(void)filename;
	(void)line;
	return libc__aligned_malloc(num_bytes, min_alignment);
}
/*[[[end:_aligned_malloc_dbg]]]*/

/*[[[head:_aligned_realloc_dbg,hash:CRC-32=0x1bbcae20]]]*/
INTERN WUNUSED ATTR_ALLOC_ALIGN(3) ATTR_ALLOC_SIZE((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._aligned_realloc_dbg") void *
NOTHROW_NCX(LIBCCALL libc__aligned_realloc_dbg)(void *ptr,
                                                size_t num_bytes,
                                                size_t min_alignment,
                                                char const *filename,
                                                int line)
/*[[[body:_aligned_realloc_dbg]]]*/
/*AUTO*/{
	(void)filename;
	(void)line;
	return libc__aligned_realloc(ptr, num_bytes, min_alignment);
}
/*[[[end:_aligned_realloc_dbg]]]*/

/*[[[head:_aligned_recalloc_dbg,hash:CRC-32=0x3aa7e3cc]]]*/
INTERN WUNUSED ATTR_ALLOC_ALIGN(4) ATTR_ALLOC_SIZE((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._aligned_recalloc_dbg") void *
NOTHROW_NCX(LIBCCALL libc__aligned_recalloc_dbg)(void *ptr,
                                                 size_t count,
                                                 size_t num_bytes,
                                                 size_t min_alignment,
                                                 char const *filename,
                                                 int line)
/*[[[body:_aligned_recalloc_dbg]]]*/
/*AUTO*/{
	(void)filename;
	(void)line;
	return libc__aligned_recalloc(ptr, count, num_bytes, min_alignment);
}
/*[[[end:_aligned_recalloc_dbg]]]*/

/*[[[head:_aligned_offset_malloc_dbg,hash:CRC-32=0x9464676d]]]*/
INTERN ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._aligned_offset_malloc_dbg") void *
NOTHROW_NCX(LIBCCALL libc__aligned_offset_malloc_dbg)(size_t num_bytes,
                                                      size_t min_alignment,
                                                      size_t offset,
                                                      char const *filename,
                                                      int line)
/*[[[body:_aligned_offset_malloc_dbg]]]*/
/*AUTO*/{
	(void)filename;
	(void)line;
	return libc__aligned_offset_malloc(num_bytes, min_alignment, offset);
}
/*[[[end:_aligned_offset_malloc_dbg]]]*/

/*[[[head:_aligned_offset_realloc_dbg,hash:CRC-32=0x82bd13ae]]]*/
INTERN WUNUSED ATTR_ALLOC_SIZE((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._aligned_offset_realloc_dbg") void *
NOTHROW_NCX(LIBCCALL libc__aligned_offset_realloc_dbg)(void *ptr,
                                                       size_t num_bytes,
                                                       size_t min_alignment,
                                                       size_t offset,
                                                       char const *filename,
                                                       int line)
/*[[[body:_aligned_offset_realloc_dbg]]]*/
/*AUTO*/{
	(void)filename;
	(void)line;
	return libc__aligned_offset_realloc(ptr, num_bytes, min_alignment, offset);
}
/*[[[end:_aligned_offset_realloc_dbg]]]*/

/*[[[head:_aligned_offset_recalloc_dbg,hash:CRC-32=0xb7e2f1f0]]]*/
INTERN WUNUSED ATTR_ALLOC_SIZE((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._aligned_offset_recalloc_dbg") void *
NOTHROW_NCX(LIBCCALL libc__aligned_offset_recalloc_dbg)(void *ptr,
                                                        size_t count,
                                                        size_t num_bytes,
                                                        size_t min_alignment,
                                                        size_t offset,
                                                        char const *filename,
                                                        int line)
/*[[[body:_aligned_offset_recalloc_dbg]]]*/
/*AUTO*/{
	(void)filename;
	(void)line;
	return libc__aligned_offset_recalloc(ptr, count, num_bytes, min_alignment, offset);
}
/*[[[end:_aligned_offset_recalloc_dbg]]]*/

/*[[[head:_aligned_free_dbg,hash:CRC-32=0x9ecdd551]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._aligned_free_dbg") void
NOTHROW_NCX(LIBCCALL libc__aligned_free_dbg)(void *ptr)
/*[[[body:_aligned_free_dbg]]]*/
/*AUTO*/{
	libc__aligned_free(ptr);
}
/*[[[end:_aligned_free_dbg]]]*/

/*[[[head:_strdup_dbg,hash:CRC-32=0x4a5458eb]]]*/
INTERN ATTR_MALLOC WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._strdup_dbg") char *
NOTHROW_NCX(LIBCCALL libc__strdup_dbg)(char const *string,
                                       int block_type,
                                       char const *filename,
                                       int line)
/*[[[body:_strdup_dbg]]]*/
/*AUTO*/{
	(void)block_type;
	(void)filename;
	(void)line;
	return libc_strdup(string);
}
/*[[[end:_strdup_dbg]]]*/

/*[[[head:_wcsdup_dbg,hash:CRC-32=0x8658f470]]]*/
INTERN ATTR_MALLOC WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._wcsdup_dbg") __WCHAR16_TYPE__ *
NOTHROW_NCX(LIBCCALL libc__wcsdup_dbg)(__WCHAR16_TYPE__ const *string,
                                       int block_type,
                                       char const *filename,
                                       int line)
/*[[[body:_wcsdup_dbg]]]*/
/*AUTO*/{
	(void)block_type;
	(void)filename;
	(void)line;
	return (__WCHAR16_TYPE__ *)libc_c16dup((char16_t const *)string);
}
/*[[[end:_wcsdup_dbg]]]*/

/*[[[head:_tempnam_dbg,hash:CRC-32=0xae5cb6f9]]]*/
INTERN ATTR_MALLOC WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._tempnam_dbg") char *
NOTHROW_NCX(LIBCCALL libc__tempnam_dbg)(char const *dir_name,
                                        char const *file_prefix,
                                        int block_type,
                                        char const *filename,
                                        int line)
/*[[[body:_tempnam_dbg]]]*/
/*AUTO*/{
	(void)block_type;
	(void)filename;
	(void)line;
	return libc_tempnam(dir_name, file_prefix);
}
/*[[[end:_tempnam_dbg]]]*/


/*[[[head:_fullpath_dbg,hash:CRC-32=0x260ef7af]]]*/
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._fullpath_dbg") char *
NOTHROW_NCX(LIBCCALL libc__fullpath_dbg)(char *full_path,
                                         char const *path,
                                         size_t bufsize,
                                         int block_type,
                                         char const *filename,
                                         int line)
/*[[[body:_fullpath_dbg]]]*/
/*AUTO*/{
	(void)block_type;
	(void)filename;
	(void)line;
	return libc__fullpath(full_path, path, bufsize);
}
/*[[[end:_fullpath_dbg]]]*/


/*[[[head:_getcwd_dbg,hash:CRC-32=0xe4435ad2]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._getcwd_dbg") char *
NOTHROW_NCX(LIBCCALL libc__getcwd_dbg)(char *buf,
                                       __STDC_INT_AS_SIZE_T bufsize,
                                       int block_type,
                                       char const *filename,
                                       int line)
/*[[[body:_getcwd_dbg]]]*/
/*AUTO*/{
	(void)block_type;
	(void)filename;
	(void)line;
	return libc_getcwd(buf, (size_t)bufsize);
}
/*[[[end:_getcwd_dbg]]]*/

/*[[[head:_wgetcwd_dbg,hash:CRC-32=0xe58cd925]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._wgetcwd_dbg") __WCHAR16_TYPE__ *
NOTHROW_NCX(LIBCCALL libc__wgetcwd_dbg)(__WCHAR16_TYPE__ *buf,
                                        __STDC_INT_AS_SIZE_T buflen,
                                        int block_type,
                                        char const *filename,
                                        int line)
/*[[[body:_wgetcwd_dbg]]]*/
/*AUTO*/{
	(void)block_type;
	(void)filename;
	(void)line;
	return (__WCHAR16_TYPE__ *)libc_c16getcwd((char16_t *)buf, buflen);
}
/*[[[end:_wgetcwd_dbg]]]*/

/*[[[head:_getdcwd_dbg,hash:CRC-32=0x7ab2fe66]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._getdcwd_dbg") char *
NOTHROW_NCX(LIBCCALL libc__getdcwd_dbg)(int driveno,
                                        char *buf,
                                        __STDC_INT_AS_SIZE_T bufsize,
                                        int block_type,
                                        char const *filename,
                                        int line)
/*[[[body:_getdcwd_dbg]]]*/
/*AUTO*/{
	(void)block_type;
	(void)filename;
	(void)line;
	return libc__getdcwd(driveno, buf, bufsize);
}
/*[[[end:_getdcwd_dbg]]]*/

//DEFINE_PUBLIC_ALIAS("\"?_CrtDbgReportW@@YAHHPEBGH00ZZ\"", libc__wgetdcwd_dbg);

/*[[[head:_dupenv_s_dbg,hash:CRC-32=0x1db97b3c]]]*/
INTERN _Check_return_wat_ NONNULL((3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._dupenv_s_dbg") errno_t
NOTHROW_NCX(LIBCCALL libc__dupenv_s_dbg)(char **pbuf,
                                         size_t *pbufsize,
                                         char const *varname,
                                         int block_type,
                                         char const *filename,
                                         int line)
/*[[[body:_dupenv_s_dbg]]]*/
/*AUTO*/{
	(void)block_type;
	(void)filename;
	(void)line;
	return libc__dupenv_s(pbuf, pbufsize, varname);
}
/*[[[end:_dupenv_s_dbg]]]*/

/*[[[head:_CrtSetDbgFlag,hash:CRC-32=0x66336d1c]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.heap.debug_malloc._CrtSetDbgFlag") int
NOTHROW_NCX(LIBCCALL libc__CrtSetDbgFlag)(int new_flag)
/*[[[body:_CrtSetDbgFlag]]]*/
/*AUTO*/{
	int result, *ptr;
	ptr = libc___p__crtDbgFlag();
	result = *ptr;
	*ptr = new_flag;
	return result;
}
/*[[[end:_CrtSetDbgFlag]]]*/



/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xc04a36cf]]]*/
#undef _CrtDbgReport
#undef _CrtDbgReportW
DEFINE_PUBLIC_WEAK_ALIAS(__p__crtAssertBusy, libc___p__crtAssertBusy);
DEFINE_PUBLIC_WEAK_ALIAS(__p__crtBreakAlloc, libc___p__crtBreakAlloc);
DEFINE_PUBLIC_WEAK_ALIAS(__p__crtDbgFlag, libc___p__crtDbgFlag);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtGetReportHook, libc__CrtGetReportHook);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtSetReportHook, libc__CrtSetReportHook);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtSetReportHook2, libc__CrtSetReportHook2);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtSetReportHookW2, libc__CrtSetReportHookW2);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtGetAllocHook, libc__CrtGetAllocHook);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtSetAllocHook, libc__CrtSetAllocHook);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtGetDumpClient, libc__CrtGetDumpClient);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtSetDumpClient, libc__CrtSetDumpClient);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtSetDbgFlag, libc__CrtSetDbgFlag);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtSetReportMode, libc__CrtSetReportMode);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtSetReportFile, libc__CrtSetReportFile);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtSetDebugFillThreshold, libc__CrtSetDebugFillThreshold);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtDbgReport, libc__CrtDbgReport);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtDbgReportW, libc__CrtDbgReportW);
DEFINE_PUBLIC_WEAK_ALIAS("?_CrtDbgReportW@@YAHHPBGH00ZZ", libc__CrtDbgReportW);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtDbgBreak, libc__CrtDbgBreak);
DEFINE_PUBLIC_WEAK_ALIAS(_CrtSetBreakAlloc, libc__CrtSetBreakAlloc);
DEFINE_PUBLIC_WEAK_ALIAS(_malloc_dbg, libc__malloc_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_calloc_dbg, libc__calloc_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_realloc_dbg, libc__realloc_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_recalloc_dbg, libc__recalloc_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_expand_dbg, libc__expand_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_free_dbg, libc__free_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_msize_dbg, libc__msize_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_aligned_malloc_dbg, libc__aligned_malloc_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_aligned_realloc_dbg, libc__aligned_realloc_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_aligned_recalloc_dbg, libc__aligned_recalloc_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_aligned_offset_malloc_dbg, libc__aligned_offset_malloc_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_aligned_offset_realloc_dbg, libc__aligned_offset_realloc_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_aligned_offset_recalloc_dbg, libc__aligned_offset_recalloc_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_aligned_free_dbg, libc__aligned_free_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_strdup_dbg, libc__strdup_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsdup_dbg, libc__wcsdup_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_tempnam_dbg, libc__tempnam_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_fullpath_dbg, libc__fullpath_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_getcwd_dbg, libc__getcwd_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_wgetcwd_dbg, libc__wgetcwd_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_getdcwd_dbg, libc__getdcwd_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_getdcwd_lk_dbg, libc__getdcwd_dbg);
DEFINE_PUBLIC_WEAK_ALIAS(_dupenv_s_dbg, libc__dupenv_s_dbg);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_CRTDBG_C */
