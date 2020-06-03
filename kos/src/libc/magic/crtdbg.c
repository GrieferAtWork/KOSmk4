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
%[define_replacement(size_t = __SIZE_TYPE__)]
%[default_impl_section(.text.crt.dos.heap.debug_malloc)]

%{
#include <features.h>
#include <crtdefs.h>
#include <bits/types.h>
#include <hybrid/typecore.h>
#include <parts/assert.h>
#include <hybrid/__assert.h>

__SYSDECL_BEGIN

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

#define _CRT_WARN   0
#define _CRT_ERROR  1
#define _CRT_ASSERT 2
#define _CRT_ERRCNT 3

#define _CRTDBG_MODE_FILE    0x1
#define _CRTDBG_MODE_DEBUG   0x2
#define _CRTDBG_MODE_WNDW    0x4
#define _CRTDBG_REPORT_MODE  (-1)

#define _CRTDBG_INVALID_HFILE (__CCAST(_HFILE)-1)
#define _CRTDBG_HFILE_ERROR   (__CCAST(_HFILE)-2)
#define _CRTDBG_FILE_STDOUT   (__CCAST(_HFILE)-4)
#define _CRTDBG_FILE_STDERR   (__CCAST(_HFILE)-5)
#define _CRTDBG_REPORT_FILE   (__CCAST(_HFILE)-6)

#define _CRT_RPTHOOK_INSTALL  0
#define _CRT_RPTHOOK_REMOVE   1

#define _HOOK_ALLOC     1
#define _HOOK_REALLOC   2
#define _HOOK_FREE      3

#define _CRTDBG_ALLOC_MEM_DF        0x01
#define _CRTDBG_DELAY_FREE_MEM_DF   0x02
#define _CRTDBG_CHECK_ALWAYS_DF     0x04
#define _CRTDBG_RESERVED_DF         0x08
#define _CRTDBG_CHECK_CRT_DF        0x10
#define _CRTDBG_LEAK_CHECK_DF       0x20

#define _CRTDBG_CHECK_EVERY_16_DF   0x00100000
#define _CRTDBG_CHECK_EVERY_128_DF  0x00800000
#define _CRTDBG_CHECK_EVERY_1024_DF 0x04000000
#define _CRTDBG_CHECK_DEFAULT_DF    0

#define _CRTDBG_REPORT_FLAG         (-1)

#define _BLOCK_TYPE(block)          ((block) & 0xFFFF)
#define _BLOCK_SUBTYPE(block)       ((block) >> 16 & 0xFFFF)

#define _FREE_BLOCK      0
#define _NORMAL_BLOCK    1
#define _CRT_BLOCK       2
#define _IGNORE_BLOCK    3
#define _CLIENT_BLOCK    4
#define _MAX_BLOCKS      5

#ifndef _STATIC_ASSERT
#define _STATIC_ASSERT(expr) __STATIC_ASSERT(expr)
#endif /* !_STATIC_ASSERT */

#ifdef __CC__

typedef void *_HFILE;
#ifndef _M_CEE_PURE
typedef int (__ATTR_CDECL *_CRT_REPORT_HOOK)(int, char *, int *);
typedef int (__ATTR_CDECL *_CRT_REPORT_HOOKW)(int, __WCHAR16_TYPE__ *, int *);
typedef int (__ATTR_CDECL *_CRT_ALLOC_HOOK)(int, void *, __SIZE_TYPE__, int, __LONG32_TYPE__, unsigned char const *, int);
typedef void (__ATTR_CDECL *_CRT_DUMP_CLIENT)(void *, __SIZE_TYPE__);
#else /* !_M_CEE_PURE */
typedef int (__ATTR_CLRCALL *_CRT_REPORT_HOOK)(int, char *, int *);
typedef int (__ATTR_CLRCALL *_CRT_REPORT_HOOKW)(int, __WCHAR16_TYPE__ *, int *);
typedef int (__ATTR_CLRCALL *_CRT_ALLOC_HOOK)(int, void *, __SIZE_TYPE__, int, __LONG32_TYPE__, unsigned char const *, int);
typedef void (__ATTR_CLRCALL *_CRT_DUMP_CLIENT)(void *, __SIZE_TYPE__);
#endif /* _M_CEE_PURE */
#ifdef _M_CEE
typedef int (__ATTR_CLRCALL *_CRT_REPORT_HOOK_M)(int, char *, int *);
typedef int (__ATTR_CLRCALL *_CRT_REPORT_HOOKW_M)(int, __WCHAR16_TYPE__ *, int *);
typedef int (__ATTR_CLRCALL *_CRT_ALLOC_HOOK_M)(int, void *, __SIZE_TYPE__, int, __LONG32_TYPE__, unsigned char const *, int);
typedef void (__ATTR_CLRCALL *_CRT_DUMP_CLIENT_M)(void *, __SIZE_TYPE__);
#endif /* _M_CEE */

struct _CrtMemBlockHeader;
typedef struct _CrtMemState {
	struct _CrtMemBlockHeader *pBlockHeader;
	__SIZE_TYPE__              lCounts[_MAX_BLOCKS];
	__SIZE_TYPE__              lSizes[_MAX_BLOCKS];
	__SIZE_TYPE__              lHighWaterCount;
	__SIZE_TYPE__              lTotalCount;
} _CrtMemState;

typedef void (__ATTR_CDECL *_PFNCRTDOFORALLCLIENTOBJECTS)(void *, void *);


#ifndef _DEBUG
#ifndef _ASSERT
#define _ASSERT(expr) (void)0
#endif /* !_ASSERT */
#ifndef _ASSERTE
#define _ASSERTE(expr) (void)0
#endif /* !_ASSERTE */
#ifndef _ASSERT_EXPR
#define _ASSERT_EXPR(expr, expr_str) (void)0
#endif /* !_ASSERT_EXPR */
#ifndef _ASSERT_BASE
#define _ASSERT_BASE _ASSERT_EXPR
#endif  /* _ASSERT_BASE */
#define _RPT0(rptno, msg)
#define _RPTW0(rptno, msg)
#define _RPT1(rptno, msg, arg1)
#define _RPTW1(rptno, msg, arg1)
#define _RPT2(rptno, msg, arg1, arg2)
#define _RPTW2(rptno, msg, arg1, arg2)
#define _RPT3(rptno, msg, arg1, arg2, arg3)
#define _RPTW3(rptno, msg, arg1, arg2, arg3)
#define _RPT4(rptno, msg, arg1, arg2, arg3, arg4)
#define _RPTW4(rptno, msg, arg1, arg2, arg3, arg4)
#define _RPT5(rptno, msg, arg1, arg2, arg3, arg4, arg5)
#define _RPTW5(rptno, msg, arg1, arg2, arg3, arg4, arg5)
#define _RPTF0(rptno, msg)
#define _RPTFW0(rptno, msg)
#define _RPTF1(rptno, msg, arg1)
#define _RPTFW1(rptno, msg, arg1)
#define _RPTF2(rptno, msg, arg1, arg2)
#define _RPTFW2(rptno, msg, arg1, arg2)
#define _RPTF3(rptno, msg, arg1, arg2, arg3)
#define _RPTFW3(rptno, msg, arg1, arg2, arg3)
#define _RPTF4(rptno, msg, arg1, arg2, arg3, arg4)
#define _RPTFW4(rptno, msg, arg1, arg2, arg3, arg4)
#define _RPTF5(rptno, msg, arg1, arg2, arg3, arg4, arg5)
#define _RPTFW5(rptno, msg, arg1, arg2, arg3, arg4, arg5)
#define _malloc_dbg(s, t, f, l) malloc(s)
#define _calloc_dbg(c, s, t, f, l) calloc(c, s)
#define _realloc_dbg(p, s, t, f, l) realloc(p, s)
#define _recalloc_dbg(p, c, s, t, f, l) _recalloc(p, c, s)
#define _expand_dbg(p, s, t, f, l) _expand(p, s)
#define _free_dbg(p, t) free(p)
#define _msize_dbg(p, t) _msize(p)
#define _aligned_msize_dbg(p, a, o) _aligned_msize(p, a, o)
#define _aligned_malloc_dbg(s, a, f, l) _aligned_malloc(s, a)
#define _aligned_realloc_dbg(p, s, a, f, l) _aligned_realloc(p, s, a)
#define _aligned_recalloc_dbg(p, c, s, a, f, l) _aligned_recalloc(p, c, s, a)
#define _aligned_free_dbg(p) _aligned_free(p)
#define _aligned_offset_malloc_dbg(s, a, o, f, l) _aligned_offset_malloc(s, a, o)
#define _aligned_offset_realloc_dbg(p, s, a, o, f, l) _aligned_offset_realloc(p, s, a, o)
#define _aligned_offset_recalloc_dbg(p, c, s, a, o, f, l) _aligned_offset_recalloc(p, c, s, a, o)
#define _malloca_dbg(s, t, f, l) _malloca(s)
#define _freea_dbg(p, t) _freea(p)
#define _strdup_dbg(s, t, f, l) _strdup(s)
#define _wcsdup_dbg(s, t, f, l) _wcsdup(s)
#define _mbsdup_dbg(s, t, f, l) _mbsdup(s)
#define _tempnam_dbg(s1, s2, t, f, l) _tempnam(s1, s2)
#define _wtempnam_dbg(s1, s2, t, f, l) _wtempnam(s1, s2)
#define _fullpath_dbg(s1, s2, le, t, f, l) _fullpath(s1, s2, le)
#define _wfullpath_dbg(s1, s2, le, t, f, l) _wfullpath(s1, s2, le)
#define _getcwd_dbg(s, le, t, f, l) _getcwd(s, le)
#define _wgetcwd_dbg(s, le, t, f, l) _wgetcwd(s, le)
#define _getdcwd_dbg(d, s, le, t, f, l) _getdcwd(d, s, le)
#define _wgetdcwd_dbg(d, s, le, t, f, l) _wgetdcwd(d, s, le)
#define _getdcwd_lk_dbg(d, s, le, t, f, l) _getdcwd(d, s, le)
#define _wgetdcwd_lk_dbg(d, s, le, t, f, l) _wgetdcwd(d, s, le)
#define _dupenv_s_dbg(ps1, size, s2, t, f, l) _dupenv_s(ps1, size, s2)
#define _wdupenv_s_dbg(ps1, size, s2, t, f, l) _wdupenv_s(ps1, size, s2)
#define _CrtSetReportHook(f) ((_CRT_REPORT_HOOK)0)
#define _CrtGetReportHook() ((_CRT_REPORT_HOOK)0)
#define _CrtSetReportHook2(t, f) 0
#define _CrtSetReportHookW2(t, f) 0
#define _CrtSetReportMode(t, f) 0
#define _CrtSetReportFile(t, f) ((_HFILE)0)
#define _CrtDbgBreak() (void)0
#define _CrtSetBreakAlloc(a) ((__LONG32_TYPE__)0)
#define _CrtSetAllocHook(f) ((_CRT_ALLOC_HOOK)0)
#define _CrtGetAllocHook() ((_CRT_ALLOC_HOOK)0)
#define _CrtCheckMemory() 1
#define _CrtSetDbgFlag(f) 0
#define _CrtDoForAllClientObjects(f, c) (void)0
#define _CrtIsValidPointer(p, n, r) 1
#define _CrtIsValidHeapPointer(p) 1
#define _CrtIsMemoryBlock(p, t, r, f, l) 1
#define _CrtReportBlockType(p) ((int)-1)
#define _CrtSetDumpClient(f) ((_CRT_DUMP_CLIENT)0)
#define _CrtGetDumpClient() ((_CRT_DUMP_CLIENT)0)
#define _CrtMemCheckpoint(s) (void)0
#define _CrtMemDifference(s1, s2, s3) 0
#define _CrtMemDumpAllObjectsSince(s) (void)0
#define _CrtMemDumpStatistics(s) (void)0
#define _CrtDumpMemoryLeaks() 0
#define _CrtSetDebugFillThreshold(t) (__SIZE_TYPE__)0
#define _CrtSetCheckCount(f) 0
#define _CrtGetCheckCount() 0
#else /* _DEBUG */

}

%#ifndef _M_CEE_PURE

%#ifdef __CRT_HAVE__crtAssertBusy
%__LIBC __LONG32_TYPE__ _crtAssertBusy;
%#else /* __CRT_HAVE__crtAssertBusy */
[guard] __p__crtAssertBusy:() -> __LONG32_TYPE__ *;
%#ifdef ____p__crtAssertBusy_defined
%#define _crtAssertBusy  (*__p__crtAssertBusy())
%#endif /* ____p__crtAssertBusy_defined */
%#endif /* !__CRT_HAVE__crtAssertBusy */

%#ifdef __CRT_HAVE__crtBreakAlloc
%__LIBC __LONG32_TYPE__ _crtBreakAlloc;
%#else /* __CRT_HAVE__crtBreakAlloc */
[guard] __p__crtBreakAlloc:() -> __LONG32_TYPE__ *;
%#ifdef ____p__crtBreakAlloc_defined
%#define _crtBreakAlloc  (*__p__crtBreakAlloc())
%#endif /* ____p__crtBreakAlloc_defined */
%#endif /* !__CRT_HAVE__crtBreakAlloc */

%#ifdef __CRT_HAVE__crtDbgFlag
%__LIBC int _crtDbgFlag;
%#else /* __CRT_HAVE__crtDbgFlag */
[guard] __p__crtDbgFlag:() -> int *;
%#ifdef ____p__crtDbgFlag_defined
%#define _crtDbgFlag  (*__p__crtDbgFlag())
%#endif /* ____p__crtDbgFlag_defined */
%#endif /* !__CRT_HAVE__crtDbgFlag */

_CrtGetReportHook:() -> _CRT_REPORT_HOOK;
_CrtSetReportHook:(_CRT_REPORT_HOOK pfn_new_hook) -> _CRT_REPORT_HOOK;
_CrtSetReportHook2:(int mode, _CRT_REPORT_HOOK pfn_new_hook) -> int;
_CrtSetReportHookW2:(int mode, _CRT_REPORT_HOOKW pfn_new_hook) -> int;
_CrtGetAllocHook:() -> _CRT_ALLOC_HOOK;
_CrtSetAllocHook:(_CRT_ALLOC_HOOK pfn_new_hook) -> _CRT_ALLOC_HOOK;
_CrtGetDumpClient:() -> _CRT_DUMP_CLIENT;
_CrtSetDumpClient:(_CRT_DUMP_CLIENT pfn_new_dump) -> _CRT_DUMP_CLIENT;
%#endif /* !_M_CEE_PURE */

[userimpl][requires($has_function(__p__crtDbgFlag))]
_CrtSetDbgFlag:(int new_flag) -> int {
	int result, *ptr;
	ptr = __p__crtDbgFlag();
	result = *ptr;
	*ptr = new_flag;
	return result;
}


_CrtSetReportMode:(int report_type, int report_mode) -> int;
_CrtSetReportFile:(int report_type, _HFILE report_file) -> _HFILE;
_CrtSetDebugFillThreshold:($size_t new_debug_fill_threshold) -> $size_t;

[guard]
_CrtDbgReport:(int report_type, char const *filename, int line, char const *module_name, char const *format, ...) -> int;
/*[export_alias(?_CrtDbgReportW@@YAHHPEBGH00ZZ)]*/ /* __ptr64??? */
[guard][export_alias("?_CrtDbgReportW@@YAHHPBGH00ZZ")]
_CrtDbgReportW:(int report_type, __WCHAR16_TYPE__ const *filename, int line, __WCHAR16_TYPE__ const *module_name, __WCHAR16_TYPE__ const *format, ...) -> int;

[guard] _CrtDbgBreak:();

_CrtSetBreakAlloc:(__LONG32_TYPE__ break_alloc) -> __LONG32_TYPE__;

[ATTR_MALLOC][ATTR_ALLOC_SIZE((1))]
[guard][ATTR_WUNUSED][userimpl][requires($has_function(malloc))]
_malloc_dbg:($size_t num_bytes, int block_type,
             char const *filename, int line) -> void * {
	(void)block_type;
	(void)filename;
	(void)line;
	return malloc(num_bytes);
}

[ATTR_MALLOC][ATTR_ALLOC_SIZE((1, 2))]
[guard][ATTR_WUNUSED][userimpl][requires($has_function(calloc))]
_calloc_dbg:($size_t count, $size_t num_bytes,
             int block_type, char const *filename, int line) -> void * {
	(void)block_type;
	(void)filename;
	(void)line;
	return calloc(count, num_bytes);
}

[ATTR_ALLOC_SIZE((2))]
[guard][ATTR_WUNUSED][userimpl][requires($has_function(calloc))]
_realloc_dbg:([[nullable]] void *ptr, $size_t num_bytes,
              int block_type, char const *filename, int line) -> void * {
	(void)block_type;
	(void)filename;
	(void)line;
	return realloc(ptr, num_bytes);
}

[ATTR_ALLOC_SIZE((2, 3))]
[guard][ATTR_WUNUSED][userimpl][requires($has_function(recallocv))]
_recalloc_dbg:([[nullable]] void *ptr, $size_t count, $size_t num_bytes,
               int block_type, char const *filename, int line) -> void * {
	(void)block_type;
	(void)filename;
	(void)line;
	return recallocv(ptr, count, num_bytes);
}

[ATTR_ALLOC_SIZE((2))]
[guard][ATTR_WUNUSED][userimpl][requires($has_function(realloc_in_place))]
_expand_dbg:([[nonnull]] void *ptr, $size_t num_bytes,
             int block_type, char const *filename, int line) -> void * {
	(void)block_type;
	(void)filename;
	(void)line;
	return realloc_in_place(ptr, num_bytes);
}

[guard][userimpl][requires($has_function(free))]
_free_dbg:([[nullable]] void *ptr, int block_type) {
	(void)block_type;
	free(ptr);
}

[guard][ATTR_WUNUSED][userimpl][requires($has_function(_msize))][ATTR_PURE]
_msize_dbg:([[nonnull]] void *ptr, int block_type) -> $size_t {
	(void)block_type;
	return _msize(ptr);
}

[guard][ATTR_WUNUSED][userimpl][requires($has_function(_aligned_msize))][ATTR_PURE]
_aligned_msize_dbg:([[nonnull]] void *ptr, $size_t min_alignment, $size_t offset) -> $size_t {
	return _aligned_msize(ptr, min_alignment, offset);
}

[ATTR_MALLOC][ATTR_ALLOC_SIZE((1))][ATTR_ALLOC_ALIGN(2)]
[guard][ATTR_WUNUSED][userimpl][requires($has_function(_aligned_malloc))]
_aligned_malloc_dbg:($size_t num_bytes, $size_t min_alignment,
                     char const *filename, int line) -> void * {
	(void)filename;
	(void)line;
	return _aligned_malloc(num_bytes, min_alignment);
}

[ATTR_ALLOC_SIZE((2))][ATTR_ALLOC_ALIGN(3)]
[guard][ATTR_WUNUSED][userimpl][requires($has_function(_aligned_realloc))]
_aligned_realloc_dbg:([[nullable]] void *ptr, $size_t num_bytes,
                      $size_t min_alignment, char const *filename, int line) -> void * {
	(void)filename;
	(void)line;
	return _aligned_realloc(ptr, num_bytes, min_alignment);
}

[ATTR_ALLOC_SIZE((2, 3))][ATTR_ALLOC_ALIGN(4)]
[guard][ATTR_WUNUSED][userimpl][requires($has_function(_aligned_recalloc))]
_aligned_recalloc_dbg:([[nullable]] void *ptr, $size_t count, $size_t num_bytes,
                       $size_t min_alignment, char const *filename, int line) -> void * {
	(void)filename;
	(void)line;
	return _aligned_recalloc(ptr, count, num_bytes, min_alignment);
}

[ATTR_MALLOC][ATTR_ALLOC_SIZE((1))]
[guard][ATTR_WUNUSED][userimpl][requires($has_function(_aligned_offset_malloc))]
_aligned_offset_malloc_dbg:($size_t num_bytes, $size_t min_alignment, $size_t offset,
                            char const *filename, int line) -> void * {
	(void)filename;
	(void)line;
	return _aligned_offset_malloc(num_bytes, min_alignment, offset);
}

[ATTR_ALLOC_SIZE((2))]
[guard][ATTR_WUNUSED][userimpl][requires($has_function(_aligned_offset_realloc))]
_aligned_offset_realloc_dbg:([[nullable]] void *ptr, $size_t num_bytes,
                             $size_t min_alignment, $size_t offset,
                             char const *filename, int line) -> void * {
	(void)filename;
	(void)line;
	return _aligned_offset_realloc(ptr, num_bytes, min_alignment, offset);
}

[ATTR_ALLOC_SIZE((2, 3))]
[guard][ATTR_WUNUSED][userimpl][requires($has_function(_aligned_offset_recalloc))]
_aligned_offset_recalloc_dbg:([[nullable]] void *ptr, $size_t count,
                              $size_t num_bytes, $size_t min_alignment,
                              $size_t offset, char const *filename, int line) -> void * {
	(void)filename;
	(void)line;
	return _aligned_offset_recalloc(ptr, count, num_bytes, min_alignment, offset);
}

[guard][userimpl][requires($has_function(_aligned_free))]
_aligned_free_dbg:([[nullable]] void *ptr) {
	_aligned_free(ptr);
}

[ATTR_MALLOC]
[guard][ATTR_WUNUSED][userimpl][requires($has_function(strdup))]
_strdup_dbg:(char const *string, int block_type, char const *filename, int line) -> char * {
	(void)block_type;
	(void)filename;
	(void)line;
	return strdup(string);
}

[ATTR_MALLOC][guard][ATTR_WUNUSED][userimpl][requires($has_function(c16dup))]
_wcsdup_dbg:(__WCHAR16_TYPE__ const *string,
             int block_type, char const *filename, int line) -> __WCHAR16_TYPE__ * {
	(void)block_type;
	(void)filename;
	(void)line;
	return (__WCHAR16_TYPE__ *)c16dup((char16_t const *)string);
}

[ATTR_MALLOC]
[guard][ATTR_WUNUSED][userimpl][requires($has_function(tempnam))]
_tempnam_dbg:(char const *dir_name, char const *file_prefix,
              int block_type, char const *filename, int line) -> char * {
	(void)block_type;
	(void)filename;
	(void)line;
	return tempnam(dir_name, file_prefix);
}

[guard][ATTR_WUNUSED][userimpl]
_wtempnam_dbg:(__WCHAR16_TYPE__ const *dir_name,
               __WCHAR16_TYPE__ const *file_prefix,
               int block_type, char const *filename, int line) -> __WCHAR16_TYPE__ * {
	(void)block_type;
	(void)filename;
	(void)line;
	(void)dir_name;
	(void)file_prefix;
	/* TODO: c16tempnam() */
	COMPILER_IMPURE();
	return NULL;
}

[guard][ATTR_WUNUSED][userimpl][requires($has_function(_fullpath))]
_fullpath_dbg:([outp_opt(bufsize)] char *full_path,
               [[nonnull]] char const *path, $size_t bufsize,
               int block_type, char const *filename, int line) -> char * {
	(void)block_type;
	(void)filename;
	(void)line;
	return _fullpath(full_path, path, bufsize);
}

[guard][ATTR_WUNUSED][userimpl]
_wfullpath_dbg:([outp_opt(buflen)] __WCHAR16_TYPE__ *full_path,
                [[nonnull]] __WCHAR16_TYPE__ const *path, $size_t buflen,
                int block_type, char const *filename, int line) -> __WCHAR16_TYPE__ * {
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

[guard][ATTR_WUNUSED][userimpl][requires($has_function(getcwd))]
_getcwd_dbg:([outp_opt(bufsize)] char *buf, __STDC_INT_AS_SIZE_T bufsize,
             int block_type, char const *filename, int line) -> char * {
	(void)block_type;
	(void)filename;
	(void)line;
	return getcwd(buf, (size_t)bufsize);
}

[guard][ATTR_WUNUSED][userimpl][requires($has_function(c16getcwd))]
_wgetcwd_dbg:([outp_opt(buflen)] __WCHAR16_TYPE__ *buf, __STDC_INT_AS_SIZE_T buflen,
              int block_type, char const *filename, int line) -> __WCHAR16_TYPE__ * {
	(void)block_type;
	(void)filename;
	(void)line;
	return (__WCHAR16_TYPE__ *)c16getcwd((char16_t *)buf, buflen);
}


[guard][ATTR_WUNUSED][userimpl][requires($has_function(_getdcwd))]
_getdcwd_dbg:(int driveno, [outp_opt(bufsize)] char *buf, __STDC_INT_AS_SIZE_T bufsize,
              int block_type, char const *filename, int line) -> char * {
	(void)block_type;
	(void)filename;
	(void)line;
	return _getdcwd(driveno, buf, bufsize);
}

[guard][ATTR_WUNUSED][userimpl]
_wgetdcwd_dbg:(int driveno, [outp_opt(buflen)] __WCHAR16_TYPE__ *buf,
               __STDC_INT_AS_SIZE_T buflen, int block_type,
               char const *filename, int line) -> __WCHAR16_TYPE__ * {
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

[guard][ATTR_WUNUSED] _getdcwd_lk_dbg:(int driveno, [outp_opt(bufsize)] char *buf, __STDC_INT_AS_SIZE_T bufsize, int block_type, char const *filename, int line) -> char * = _getdcwd_dbg;
[guard][ATTR_WUNUSED] _wgetdcwd_lk_dbg:(int driveno, [outp_opt(buflen)] __WCHAR16_TYPE__ *buf, __STDC_INT_AS_SIZE_T buflen, int block_type, char const *filename, int line) -> __WCHAR16_TYPE__ * = _wgetdcwd_dbg;

[guard][attribute(@_Check_return_wat_@)][userimpl][requires($has_function(_dupenv_s))]
_dupenv_s_dbg:([[nullable]] char **pbuf, [[nullable]] $size_t *pbufsize,
               [[nonnull]] char const *varname,
               int block_type, char const *filename, int line) -> $errno_t {
	(void)block_type;
	(void)filename;
	(void)line;
	return _dupenv_s(pbuf, pbufsize, varname);
}

[guard][attribute(@_Check_return_wat_@)][userimpl]
_wdupenv_s_dbg:([[nullable]] __WCHAR16_TYPE__ **pbuf, [[nullable]] $size_t *pbuflen,
                [[nonnull]] __WCHAR16_TYPE__ const *varname,
                int block_type, char const *filename, int line) -> $errno_t {
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

_CrtCheckMemory:() -> int {
	COMPILER_IMPURE();
	return 0;
}

[userimpl]
_CrtDoForAllClientObjects:([[nonnull]] _PFNCRTDOFORALLCLIENTOBJECTS pfn, void *context) {
	COMPILER_IMPURE();
	(void)pfn;
	(void)context;
}

[ATTR_WUNUSED][userimpl][ATTR_PURE]
_CrtIsValidPointer:(void const *ptr, __STDC_UINT_AS_SIZE_T num_bytes, int writable) -> int {
	COMPILER_IMPURE();
	(void)num_bytes;
	(void)writable;
	return ptr != NULL;
}

[ATTR_WUNUSED][userimpl][ATTR_PURE]
_CrtIsValidHeapPointer:(void const *heap_ptr) -> int {
	COMPILER_IMPURE();
	return heap_ptr != NULL;
}


[userimpl]
_CrtIsMemoryBlock:(void const *ptr, __STDC_UINT_AS_SIZE_T num_bytes,
                   [[nullable]] __LONG32_TYPE__ *prequest_number,
                   [[nullable]] char **filename, [[nullable]] int *line) -> int {
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

[ATTR_WUNUSED][userimpl][ATTR_PURE]
_CrtReportBlockType:(void const *ptr) -> int {
	COMPILER_IMPURE();
	return ptr ? 1 /*_NORMAL_BLOCK*/ : 0 /*_FREE_BLOCK*/;
}

[userimpl]
_CrtMemCheckpoint:([[nonnull]] /*out*/ _CrtMemState *state) {
	memset(state, 0, sizeof(*state));
}

[userimpl]
_CrtMemDifference:([[nonnull]] /*out*/ _CrtMemState *state,
                   [[nonnull]] _CrtMemState const *old_state,
                   [[nonnull]] _CrtMemState const *new_state) -> int {
	(void)old_state;
	(void)new_state;
	memset(state, 0, sizeof(*state));
	return 0;
}

[userimpl]
_CrtMemDumpAllObjectsSince:([[nonnull]] _CrtMemState const *state) {
	COMPILER_IMPURE();
	(void)state;
}

[userimpl]
_CrtMemDumpStatistics:([[nonnull]] _CrtMemState const *state) {
	COMPILER_IMPURE();
	(void)state;
}

[userimpl]
_CrtDumpMemoryLeaks:() -> int {
	COMPILER_IMPURE();
	return 0;
}

[userimpl]
_CrtSetCheckCount:(int check_count) -> int {
	(void)check_count;
	COMPILER_IMPURE();
	return 0;
}

[userimpl][ATTR_PURE]
_CrtGetCheckCount:() -> int {
	COMPILER_IMPURE();
	return 0;
}

%{

#ifndef ___CrtDbgBreak_defined
#define ___CrtDbgBreak_defined 1
__SYSDECL_END
#include <intrin.h>
__SYSDECL_BEGIN
#define _CrtDbgBreak() __debugbreak()
#endif /* !___CrtDbgBreak_defined */

#define _malloca_dbg(s, t, f, l) _malloc_dbg(s, t, f, l)
#define _freea_dbg(p, t) _free_dbg(p, t)

#if defined(__cplusplus) && defined(_CRTDBG_MAP_ALLOC)
__NAMESPACE_STD_BEGIN
__NAMESPACE_GLB_USING(_calloc_dbg)
__NAMESPACE_GLB_USING(_free_dbg)
__NAMESPACE_GLB_USING(_malloc_dbg)
__NAMESPACE_GLB_USING(_realloc_dbg)
__NAMESPACE_STD_END
#endif /* __cplusplus && _CRTDBG_MAP_ALLOC */


#ifdef ___CrtDbgReportW_defined
#define _ASSERT_EXPR(expr, msg)                                                                        \
	(void)((!!(expr)) ||                                                                               \
	       (1 != _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, __NULLPTR, L"%s", msg)) || \
	       (_CrtDbgBreak(), 0))
#define __HAVE_NATIVE_RPT_BASE_W 1
#define _RPT_BASE_W(args) (void)((_CrtDbgReportW args) != 1 || (_CrtDbgBreak(), 0))
#else /* ___CrtDbgReportW_defined */
#define _ASSERT_EXPR(expr, msg) __hybrid_assertf(expr, "%ls", msg)
#define _RPT_BASE_W(args) (void)((_CrtDbgReportW args) != 1 || (_CrtDbgBreak(), 0))
#define _RPT_BASE_W2(report_type, filename, line, module_name, ...) \
	__assertion_failed_at(__NULLPTR, NULL, 0, "%ls(%d) : %ls", filename, line, module_name)
#define _RPT_BASE_W(args) _RPT_BASE_W2 args
#endif /* !___CrtDbgReportW_defined */
#ifdef ___CrtDbgReport_defined
#define _RPT_BASE(args) (void)((_CrtDbgReport args) != 1 || (_CrtDbgBreak(), 0))
#else /* ___CrtDbgReport_defined */
#define _RPT_BASE2(report_type, filename, line, module_name, ...) \
	__assertion_failedf_at(__NULLPTR, filename, line, module_name, __VA_ARGS__)
#define _RPT_BASE(args) _RPT_BASE2 args
#endif /* !___CrtDbgReport_defined */

#ifndef _ASSERT
#define _ASSERT(expr) _ASSERT_EXPR(expr, __NULLPTR)
#endif  /* _ASSERT */
#ifndef _ASSERTE
#define _ASSERTE(expr)  _ASSERT_EXPR(expr, _CRT_WIDE(#expr))
#endif  /* _ASSERTE */
#ifndef _ASSERT_BASE
#define _ASSERT_BASE _ASSERT_EXPR
#endif  /* _ASSERT_BASE */
#define _RPT0(rptno, msg) _RPT_BASE((rptno, __NULLPTR, 0, __NULLPTR, "%s", msg))
#define _RPT1(rptno, msg, arg1) _RPT_BASE((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1))
#define _RPT2(rptno, msg, arg1, arg2) _RPT_BASE((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1, arg2))
#define _RPT3(rptno, msg, arg1, arg2, arg3) _RPT_BASE((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1, arg2, arg3))
#define _RPT4(rptno, msg, arg1, arg2, arg3, arg4) _RPT_BASE((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1, arg2, arg3, arg4))
#define _RPT5(rptno, msg, arg1, arg2, arg3, arg4, arg5) _RPT_BASE((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1, arg2, arg3, arg4, arg5))
#define _RPTF0(rptno, msg) _RPT_BASE((rptno, __FILE__, __LINE__, __NULLPTR, "%s", msg))
#define _RPTF1(rptno, msg, arg1) _RPT_BASE((rptno, __FILE__, __LINE__, __NULLPTR, msg, arg1))
#define _RPTF2(rptno, msg, arg1, arg2) _RPT_BASE((rptno, __FILE__, __LINE__, __NULLPTR, msg, arg1, arg2))
#define _RPTF3(rptno, msg, arg1, arg2, arg3) _RPT_BASE((rptno, __FILE__, __LINE__, __NULLPTR, msg, arg1, arg2, arg3))
#define _RPTF4(rptno, msg, arg1, arg2, arg3, arg4) _RPT_BASE((rptno, __FILE__, __LINE__, __NULLPTR, msg, arg1, arg2, arg3, arg4))
#define _RPTF5(rptno, msg, arg1, arg2, arg3, arg4, arg5) _RPT_BASE((rptno, __FILE__, __LINE__, __NULLPTR, msg, arg1, arg2, arg3, arg4, arg5))
#ifdef __HAVE_NATIVE_RPT_BASE_W
#define _RPTW0(rptno, msg) _RPT_BASE_W((rptno, __NULLPTR, 0, __NULLPTR, L"%s", msg))
#define _RPTFW0(rptno, msg) _RPT_BASE_W((rptno, _CRT_WIDE(__FILE__), __LINE__, __NULLPTR, L"%s", msg))
#else /* __HAVE_NATIVE_RPT_BASE_W */
#define _RPTW0(rptno, msg) _RPT_BASE((rptno, __NULLPTR, 0, __NULLPTR, "%ls", msg))
#define _RPTFW0(rptno, msg) _RPT_BASE((rptno, __FILE__, __LINE__, __NULLPTR, "%ls", msg))
#endif /* !__HAVE_NATIVE_RPT_BASE_W */
#define _RPTW1(rptno, msg, arg1) _RPT_BASE_W((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1))
#define _RPTW2(rptno, msg, arg1, arg2) _RPT_BASE_W((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1, arg2))
#define _RPTW3(rptno, msg, arg1, arg2, arg3) _RPT_BASE_W((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1, arg2, arg3))
#define _RPTW4(rptno, msg, arg1, arg2, arg3, arg4) _RPT_BASE_W((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1, arg2, arg3, arg4))
#define _RPTW5(rptno, msg, arg1, arg2, arg3, arg4, arg5) _RPT_BASE_W((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1, arg2, arg3, arg4, arg5))
#define _RPTFW1(rptno, msg, arg1) _RPT_BASE_W((rptno, _CRT_WIDE(__FILE__), __LINE__, __NULLPTR, msg, arg1))
#define _RPTFW2(rptno, msg, arg1, arg2) _RPT_BASE_W((rptno, _CRT_WIDE(__FILE__), __LINE__, __NULLPTR, msg, arg1, arg2))
#define _RPTFW3(rptno, msg, arg1, arg2, arg3) _RPT_BASE_W((rptno, _CRT_WIDE(__FILE__), __LINE__, __NULLPTR, msg, arg1, arg2, arg3))
#define _RPTFW4(rptno, msg, arg1, arg2, arg3, arg4) _RPT_BASE_W((rptno, _CRT_WIDE(__FILE__), __LINE__, __NULLPTR, msg, arg1, arg2, arg3, arg4))
#define _RPTFW5(rptno, msg, arg1, arg2, arg3, arg4, arg5) _RPT_BASE_W((rptno, _CRT_WIDE(__FILE__), __LINE__, __NULLPTR, msg, arg1, arg2, arg3, arg4, arg5))
#ifdef _CRTDBG_MAP_ALLOC
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define calloc(c, s) _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define realloc(p, s) _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _recalloc(p, c, s) _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _expand(p, s) _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define free(p) _free_dbg(p, _NORMAL_BLOCK)
#define _msize(p) _msize_dbg(p, _NORMAL_BLOCK)
#define _aligned_msize(p, a, o) _aligned_msize_dbg(p, a, o)
#define _aligned_malloc(s, a) _aligned_malloc_dbg(s, a, __FILE__, __LINE__)
#define _aligned_realloc(p, s, a) _aligned_realloc_dbg(p, s, a, __FILE__, __LINE__)
#define _aligned_recalloc(p, c, s, a) _aligned_recalloc_dbg(p, c, s, a, __FILE__, __LINE__)
#define _aligned_offset_malloc(s, a, o) _aligned_offset_malloc_dbg(s, a, o, __FILE__, __LINE__)
#define _aligned_offset_realloc(p, s, a, o) _aligned_offset_realloc_dbg(p, s, a, o, __FILE__, __LINE__)
#define _aligned_offset_recalloc(p, c, s, a, o) _aligned_offset_recalloc_dbg(p, c, s, a, o, __FILE__, __LINE__)
#define _aligned_free(p) _aligned_free_dbg(p)
#define _malloca(s) _malloca_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _freea(p) _freea_dbg(p, _NORMAL_BLOCK)
#define _strdup(s) _strdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _wcsdup(s) _wcsdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _mbsdup(s) _strdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _tempnam(s1, s2) _tempnam_dbg(s1, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _wtempnam(s1, s2) _wtempnam_dbg(s1, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _fullpath(s1, s2, le) _fullpath_dbg(s1, s2, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _wfullpath(s1, s2, le) _wfullpath_dbg(s1, s2, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _getcwd(s, le) _getcwd_dbg(s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _wgetcwd(s, le) _wgetcwd_dbg(s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _getdcwd(d, s, le) _getdcwd_dbg(d, s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _wgetdcwd(d, s, le) _wgetdcwd_dbg(d, s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _dupenv_s(ps1, size, s2) _dupenv_s_dbg(ps1, size, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _wdupenv_s(ps1, size, s2) _wdupenv_s_dbg(ps1, size, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
#define strdup(s) _strdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define wcsdup(s) _wcsdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define tempnam(s1, s2) _tempnam_dbg(s1, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
#define getcwd(s, le) _getcwd_dbg(s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif  /* _CRTDBG_MAP_ALLOC */

#endif /* _DEBUG */

#endif /* __CC__ */

__SYSDECL_END

}