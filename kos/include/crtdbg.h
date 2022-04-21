/* HASH CRC-32:0xb711d28f */
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
/* (#) Portability: MSVC         (/include/crtdbg.h) */
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/crtdbg.h) */
/* (#) Portability: Windows Kits (/ucrt/crtdbg.h) */
#ifndef _CRTDBG_H
#define _CRTDBG_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/__assert.h>
#include <hybrid/typecore.h>

#include <bits/types.h>
#include <parts/assert.h>

#include <crtdefs.h>


#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

#define _CRT_WARN   0
#define _CRT_ERROR  1
#define _CRT_ASSERT 2
#define _CRT_ERRCNT 3

#define _CRTDBG_MODE_FILE   0x1
#define _CRTDBG_MODE_DEBUG  0x2
#define _CRTDBG_MODE_WNDW   0x4
#define _CRTDBG_REPORT_MODE (-1)

#define _CRTDBG_INVALID_HFILE (__CCAST(_HFILE)-1)
#define _CRTDBG_HFILE_ERROR   (__CCAST(_HFILE)-2)
#define _CRTDBG_FILE_STDOUT   (__CCAST(_HFILE)-4)
#define _CRTDBG_FILE_STDERR   (__CCAST(_HFILE)-5)
#define _CRTDBG_REPORT_FILE   (__CCAST(_HFILE)-6)

#define _CRT_RPTHOOK_INSTALL 0
#define _CRT_RPTHOOK_REMOVE  1

#define _HOOK_ALLOC   1
#define _HOOK_REALLOC 2
#define _HOOK_FREE    3

#define _CRTDBG_ALLOC_MEM_DF      0x01
#define _CRTDBG_DELAY_FREE_MEM_DF 0x02
#define _CRTDBG_CHECK_ALWAYS_DF   0x04
#define _CRTDBG_RESERVED_DF       0x08
#define _CRTDBG_CHECK_CRT_DF      0x10
#define _CRTDBG_LEAK_CHECK_DF     0x20

#define _CRTDBG_CHECK_EVERY_16_DF   0x00100000
#define _CRTDBG_CHECK_EVERY_128_DF  0x00800000
#define _CRTDBG_CHECK_EVERY_1024_DF 0x04000000
#define _CRTDBG_CHECK_DEFAULT_DF    0

#define _CRTDBG_REPORT_FLAG (-1)

#define _BLOCK_TYPE(block)    ((block) & 0xffff)
#define _BLOCK_SUBTYPE(block) ((block) >> 16 & 0xffff)

#define _FREE_BLOCK   0
#define _NORMAL_BLOCK 1
#define _CRT_BLOCK    2
#define _IGNORE_BLOCK 3
#define _CLIENT_BLOCK 4
#define _MAX_BLOCKS   5

#ifndef _STATIC_ASSERT
#define _STATIC_ASSERT(expr) __STATIC_ASSERT(expr)
#endif /* !_STATIC_ASSERT */

#ifdef __CC__
__SYSDECL_BEGIN

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


#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("pBlockHeader")
#pragma push_macro("lCounts")
#pragma push_macro("lSizes")
#pragma push_macro("lHighWaterCount")
#pragma push_macro("lTotalCount")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef pBlockHeader
#undef lCounts
#undef lSizes
#undef lHighWaterCount
#undef lTotalCount
struct _CrtMemBlockHeader;
typedef struct _CrtMemState {
	struct _CrtMemBlockHeader *pBlockHeader;
	__SIZE_TYPE__              lCounts[_MAX_BLOCKS];
	__SIZE_TYPE__              lSizes[_MAX_BLOCKS];
	__SIZE_TYPE__              lHighWaterCount;
	__SIZE_TYPE__              lTotalCount;
} _CrtMemState;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("lTotalCount")
#pragma pop_macro("lHighWaterCount")
#pragma pop_macro("lSizes")
#pragma pop_macro("lCounts")
#pragma pop_macro("pBlockHeader")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

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

#ifndef _M_CEE_PURE
#ifdef __CRT_HAVE__crtAssertBusy
__CSDECLARE(,__LONG32_TYPE__,_crtAssertBusy)
#else /* __CRT_HAVE__crtAssertBusy */
#if !defined(____p__crtAssertBusy_defined) && defined(__CRT_HAVE___p__crtAssertBusy)
#define ____p__crtAssertBusy_defined
__LIBC __LONG32_TYPE__ *__NOTHROW_NCX(__LIBDCALL __p__crtAssertBusy)(void) __CASMNAME_SAME("__p__crtAssertBusy");
#endif /* !____p__crtAssertBusy_defined && __CRT_HAVE___p__crtAssertBusy */
#ifdef ____p__crtAssertBusy_defined
#define _crtAssertBusy  (*__p__crtAssertBusy())
#endif /* ____p__crtAssertBusy_defined */
#endif /* !__CRT_HAVE__crtAssertBusy */
#ifdef __CRT_HAVE__crtBreakAlloc
__CSDECLARE(,__LONG32_TYPE__,_crtBreakAlloc)
#else /* __CRT_HAVE__crtBreakAlloc */
#if !defined(____p__crtBreakAlloc_defined) && defined(__CRT_HAVE___p__crtBreakAlloc)
#define ____p__crtBreakAlloc_defined
__LIBC __LONG32_TYPE__ *__NOTHROW_NCX(__LIBDCALL __p__crtBreakAlloc)(void) __CASMNAME_SAME("__p__crtBreakAlloc");
#endif /* !____p__crtBreakAlloc_defined && __CRT_HAVE___p__crtBreakAlloc */
#ifdef ____p__crtBreakAlloc_defined
#define _crtBreakAlloc  (*__p__crtBreakAlloc())
#endif /* ____p__crtBreakAlloc_defined */
#endif /* !__CRT_HAVE__crtBreakAlloc */
#ifdef __CRT_HAVE__crtDbgFlag
__CSDECLARE(,int,_crtDbgFlag)
#else /* __CRT_HAVE__crtDbgFlag */
#if !defined(____p__crtDbgFlag_defined) && defined(__CRT_HAVE___p__crtDbgFlag)
#define ____p__crtDbgFlag_defined
__LIBC int *__NOTHROW_NCX(__LIBDCALL __p__crtDbgFlag)(void) __CASMNAME_SAME("__p__crtDbgFlag");
#endif /* !____p__crtDbgFlag_defined && __CRT_HAVE___p__crtDbgFlag */
#ifdef ____p__crtDbgFlag_defined
#define _crtDbgFlag  (*__p__crtDbgFlag())
#endif /* ____p__crtDbgFlag_defined */
#endif /* !__CRT_HAVE__crtDbgFlag */
#ifdef __CRT_HAVE__CrtGetReportHook
__LIBC _CRT_REPORT_HOOK __NOTHROW_NCX(__LIBDCALL _CrtGetReportHook)(void) __CASMNAME_SAME("_CrtGetReportHook");
#endif /* __CRT_HAVE__CrtGetReportHook */
#ifdef __CRT_HAVE__CrtSetReportHook
__LIBC _CRT_REPORT_HOOK __NOTHROW_NCX(__LIBDCALL _CrtSetReportHook)(_CRT_REPORT_HOOK __pfn_new_hook) __CASMNAME_SAME("_CrtSetReportHook");
#endif /* __CRT_HAVE__CrtSetReportHook */
#ifdef __CRT_HAVE__CrtSetReportHook2
__LIBC int __NOTHROW_NCX(__LIBDCALL _CrtSetReportHook2)(int __mode, _CRT_REPORT_HOOK __pfn_new_hook) __CASMNAME_SAME("_CrtSetReportHook2");
#endif /* __CRT_HAVE__CrtSetReportHook2 */
#ifdef __CRT_HAVE__CrtSetReportHookW2
__LIBC int __NOTHROW_NCX(__LIBDCALL _CrtSetReportHookW2)(int __mode, _CRT_REPORT_HOOKW __pfn_new_hook) __CASMNAME_SAME("_CrtSetReportHookW2");
#endif /* __CRT_HAVE__CrtSetReportHookW2 */
#ifdef __CRT_HAVE__CrtGetAllocHook
__LIBC _CRT_ALLOC_HOOK __NOTHROW_NCX(__LIBDCALL _CrtGetAllocHook)(void) __CASMNAME_SAME("_CrtGetAllocHook");
#endif /* __CRT_HAVE__CrtGetAllocHook */
#ifdef __CRT_HAVE__CrtSetAllocHook
__LIBC _CRT_ALLOC_HOOK __NOTHROW_NCX(__LIBDCALL _CrtSetAllocHook)(_CRT_ALLOC_HOOK __pfn_new_hook) __CASMNAME_SAME("_CrtSetAllocHook");
#endif /* __CRT_HAVE__CrtSetAllocHook */
#ifdef __CRT_HAVE__CrtGetDumpClient
__LIBC _CRT_DUMP_CLIENT __NOTHROW_NCX(__LIBDCALL _CrtGetDumpClient)(void) __CASMNAME_SAME("_CrtGetDumpClient");
#endif /* __CRT_HAVE__CrtGetDumpClient */
#ifdef __CRT_HAVE__CrtSetDumpClient
__LIBC _CRT_DUMP_CLIENT __NOTHROW_NCX(__LIBDCALL _CrtSetDumpClient)(_CRT_DUMP_CLIENT __pfn_new_dump) __CASMNAME_SAME("_CrtSetDumpClient");
#endif /* __CRT_HAVE__CrtSetDumpClient */
#endif /* !_M_CEE_PURE */
#ifdef __CRT_HAVE__CrtSetDbgFlag
__LIBC int __NOTHROW_NCX(__LIBDCALL _CrtSetDbgFlag)(int __new_flag) __CASMNAME_SAME("_CrtSetDbgFlag");
#elif defined(__CRT_HAVE___p__crtDbgFlag)
#include <libc/local/crtdbg/_CrtSetDbgFlag.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtSetDbgFlag, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBDCALL _CrtSetDbgFlag)(int __new_flag) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtSetDbgFlag))(__new_flag); })
#endif /* ... */
#ifdef __CRT_HAVE__CrtSetReportMode
__LIBC int __NOTHROW_NCX(__LIBDCALL _CrtSetReportMode)(int __report_type, int __report_mode) __CASMNAME_SAME("_CrtSetReportMode");
#endif /* __CRT_HAVE__CrtSetReportMode */
#ifdef __CRT_HAVE__CrtSetReportFile
__LIBC _HFILE __NOTHROW_NCX(__LIBDCALL _CrtSetReportFile)(int __report_type, _HFILE __report_file) __CASMNAME_SAME("_CrtSetReportFile");
#endif /* __CRT_HAVE__CrtSetReportFile */
#ifdef __CRT_HAVE__CrtSetDebugFillThreshold
__LIBC __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL _CrtSetDebugFillThreshold)(__SIZE_TYPE__ __new_debug_fill_threshold) __CASMNAME_SAME("_CrtSetDebugFillThreshold");
#endif /* __CRT_HAVE__CrtSetDebugFillThreshold */
#if !defined(___CrtDbgReport_defined) && defined(__CRT_HAVE__CrtDbgReport)
#define ___CrtDbgReport_defined
__LIBC int __NOTHROW_NCX(__VLIBDCALL _CrtDbgReport)(int __report_type, char const *__filename, int __line, char const *__module_name, char const *__format, ...) __CASMNAME_SAME("_CrtDbgReport");
#endif /* !___CrtDbgReport_defined && __CRT_HAVE__CrtDbgReport */
#ifndef ___CrtDbgReportW_defined
#define ___CrtDbgReportW_defined
#ifdef __CRT_HAVE__CrtDbgReportW
__LIBC int __NOTHROW_NCX(__VLIBDCALL _CrtDbgReportW)(int __report_type, __WCHAR16_TYPE__ const *__filename, int __line, __WCHAR16_TYPE__ const *__module_name, __WCHAR16_TYPE__ const *__format, ...) __CASMNAME_SAME("_CrtDbgReportW");
#elif defined(__CRT_HAVE_$Q_CrtDbgReportW$A$AYAHHPBGH00ZZ)
__LIBC int __NOTHROW_NCX(__VLIBDCALL _CrtDbgReportW)(int __report_type, __WCHAR16_TYPE__ const *__filename, int __line, __WCHAR16_TYPE__ const *__module_name, __WCHAR16_TYPE__ const *__format, ...) __CASMNAME("?_CrtDbgReportW@@YAHHPBGH00ZZ");
#else /* ... */
#undef ___CrtDbgReportW_defined
#endif /* !... */
#endif /* !___CrtDbgReportW_defined */
#if !defined(___CrtDbgBreak_defined) && defined(__CRT_HAVE__CrtDbgBreak)
#define ___CrtDbgBreak_defined
__LIBC void __NOTHROW_NCX(__LIBDCALL _CrtDbgBreak)(void) __CASMNAME_SAME("_CrtDbgBreak");
#endif /* !___CrtDbgBreak_defined && __CRT_HAVE__CrtDbgBreak */
#ifdef __CRT_HAVE__CrtSetBreakAlloc
__LIBC __LONG32_TYPE__ __NOTHROW_NCX(__LIBDCALL _CrtSetBreakAlloc)(__LONG32_TYPE__ __break_alloc) __CASMNAME_SAME("_CrtSetBreakAlloc");
#endif /* __CRT_HAVE__CrtSetBreakAlloc */
#ifndef ___malloc_dbg_defined
#define ___malloc_dbg_defined
#ifdef __CRT_HAVE__malloc_dbg
__LIBC __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBDCALL _malloc_dbg)(__SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) __CASMNAME_SAME("_malloc_dbg");
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/crtdbg/_malloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_malloc_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBDCALL _malloc_dbg)(__SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_malloc_dbg))(__num_bytes, __block_type, __filename, __line); })
#else /* ... */
#undef ___malloc_dbg_defined
#endif /* !... */
#endif /* !___malloc_dbg_defined */
#ifndef ___calloc_dbg_defined
#define ___calloc_dbg_defined
#ifdef __CRT_HAVE__calloc_dbg
__LIBC __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)) void *__NOTHROW_NCX(__LIBDCALL _calloc_dbg)(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) __CASMNAME_SAME("_calloc_dbg");
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/crtdbg/_calloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_calloc_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)) void *__NOTHROW_NCX(__LIBDCALL _calloc_dbg)(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_calloc_dbg))(__count, __num_bytes, __block_type, __filename, __line); })
#else /* ... */
#undef ___calloc_dbg_defined
#endif /* !... */
#endif /* !___calloc_dbg_defined */
#ifndef ___realloc_dbg_defined
#define ___realloc_dbg_defined
#ifdef __CRT_HAVE__realloc_dbg
__LIBC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBDCALL _realloc_dbg)(void *__ptr, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) __CASMNAME_SAME("_realloc_dbg");
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/crtdbg/_realloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_realloc_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBDCALL _realloc_dbg)(void *__ptr, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_realloc_dbg))(__ptr, __num_bytes, __block_type, __filename, __line); })
#else /* ... */
#undef ___realloc_dbg_defined
#endif /* !... */
#endif /* !___realloc_dbg_defined */
#ifndef ___recalloc_dbg_defined
#define ___recalloc_dbg_defined
#ifdef __CRT_HAVE__recalloc_dbg
__LIBC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBDCALL _recalloc_dbg)(void *__ptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) __CASMNAME_SAME("_recalloc_dbg");
#elif defined(__CRT_HAVE_recallocv) || defined(__CRT_HAVE__recalloc) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize)))
#include <libc/local/crtdbg/_recalloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_recalloc_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBDCALL _recalloc_dbg)(void *__ptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_recalloc_dbg))(__ptr, __count, __num_bytes, __block_type, __filename, __line); })
#else /* ... */
#undef ___recalloc_dbg_defined
#endif /* !... */
#endif /* !___recalloc_dbg_defined */
#ifndef ___expand_dbg_defined
#define ___expand_dbg_defined
#ifdef __CRT_HAVE__expand_dbg
__LIBC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBDCALL _expand_dbg)(void *__ptr, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) __CASMNAME_SAME("_expand_dbg");
#elif defined(__CRT_HAVE_realloc_in_place) || defined(__CRT_HAVE__expand)
#include <libc/local/crtdbg/_expand_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_expand_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBDCALL _expand_dbg)(void *__ptr, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_expand_dbg))(__ptr, __num_bytes, __block_type, __filename, __line); })
#else /* ... */
#undef ___expand_dbg_defined
#endif /* !... */
#endif /* !___expand_dbg_defined */
#ifndef ___free_dbg_defined
#define ___free_dbg_defined
#ifdef __CRT_HAVE__free_dbg
__LIBC void __NOTHROW_NCX(__LIBDCALL _free_dbg)(void *__ptr, int __block_type) __CASMNAME_SAME("_free_dbg");
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#include <libc/local/crtdbg/_free_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_free_dbg, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBDCALL _free_dbg)(void *__ptr, int __block_type) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_free_dbg))(__ptr, __block_type); })
#else /* ... */
#undef ___free_dbg_defined
#endif /* !... */
#endif /* !___free_dbg_defined */
#ifndef ___msize_dbg_defined
#define ___msize_dbg_defined
#ifdef __CRT_HAVE__msize_dbg
__LIBC __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL _msize_dbg)(void *__ptr, int __block_type) __CASMNAME_SAME("_msize_dbg");
#elif defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize)
#include <libc/local/crtdbg/_msize_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_msize_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL _msize_dbg)(void *__ptr, int __block_type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_msize_dbg))(__ptr, __block_type); })
#else /* ... */
#undef ___msize_dbg_defined
#endif /* !... */
#endif /* !___msize_dbg_defined */
#ifndef ___aligned_msize_dbg_defined
#define ___aligned_msize_dbg_defined
#ifdef __CRT_HAVE__aligned_msize_dbg
__LIBC __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL _aligned_msize_dbg)(void *__ptr, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset) __CASMNAME_SAME("_aligned_msize_dbg");
#else /* __CRT_HAVE__aligned_msize_dbg */
#include <libc/local/crtdbg/_aligned_msize_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_msize_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL _aligned_msize_dbg)(void *__ptr, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_msize_dbg))(__ptr, __min_alignment, __offset); })
#endif /* !__CRT_HAVE__aligned_msize_dbg */
#endif /* !___aligned_msize_dbg_defined */
#ifndef ___aligned_malloc_dbg_defined
#define ___aligned_malloc_dbg_defined
#ifdef __CRT_HAVE__aligned_malloc_dbg
__LIBC __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(2) __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBDCALL _aligned_malloc_dbg)(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, char const *__filename, int __line) __CASMNAME_SAME("_aligned_malloc_dbg");
#elif defined(__CRT_HAVE__aligned_malloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/crtdbg/_aligned_malloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_malloc_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(2) __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBDCALL _aligned_malloc_dbg)(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_malloc_dbg))(__num_bytes, __min_alignment, __filename, __line); })
#else /* ... */
#undef ___aligned_malloc_dbg_defined
#endif /* !... */
#endif /* !___aligned_malloc_dbg_defined */
#ifndef ___aligned_realloc_dbg_defined
#define ___aligned_realloc_dbg_defined
#ifdef __CRT_HAVE__aligned_realloc_dbg
__LIBC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(3) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBDCALL _aligned_realloc_dbg)(void *__ptr, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, char const *__filename, int __line) __CASMNAME_SAME("_aligned_realloc_dbg");
#elif defined(__CRT_HAVE__aligned_realloc) || ((defined(__CRT_HAVE__aligned_malloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE__aligned_free) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)))
#include <libc/local/crtdbg/_aligned_realloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_realloc_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(3) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBDCALL _aligned_realloc_dbg)(void *__ptr, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_realloc_dbg))(__ptr, __num_bytes, __min_alignment, __filename, __line); })
#else /* ... */
#undef ___aligned_realloc_dbg_defined
#endif /* !... */
#endif /* !___aligned_realloc_dbg_defined */
#ifndef ___aligned_recalloc_dbg_defined
#define ___aligned_recalloc_dbg_defined
#ifdef __CRT_HAVE__aligned_recalloc_dbg
__LIBC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(4) __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBDCALL _aligned_recalloc_dbg)(void *__ptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, char const *__filename, int __line) __CASMNAME_SAME("_aligned_recalloc_dbg");
#elif defined(__CRT_HAVE__aligned_recalloc) || ((defined(__CRT_HAVE__aligned_malloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE__aligned_free) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)))
#include <libc/local/crtdbg/_aligned_recalloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_recalloc_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(4) __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBDCALL _aligned_recalloc_dbg)(void *__ptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_recalloc_dbg))(__ptr, __count, __num_bytes, __min_alignment, __filename, __line); })
#else /* ... */
#undef ___aligned_recalloc_dbg_defined
#endif /* !... */
#endif /* !___aligned_recalloc_dbg_defined */
#ifndef ___aligned_offset_malloc_dbg_defined
#define ___aligned_offset_malloc_dbg_defined
#ifdef __CRT_HAVE__aligned_offset_malloc_dbg
__LIBC __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBDCALL _aligned_offset_malloc_dbg)(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset, char const *__filename, int __line) __CASMNAME_SAME("_aligned_offset_malloc_dbg");
#elif defined(__CRT_HAVE__aligned_offset_malloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/crtdbg/_aligned_offset_malloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_offset_malloc_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBDCALL _aligned_offset_malloc_dbg)(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_offset_malloc_dbg))(__num_bytes, __min_alignment, __offset, __filename, __line); })
#else /* ... */
#undef ___aligned_offset_malloc_dbg_defined
#endif /* !... */
#endif /* !___aligned_offset_malloc_dbg_defined */
#ifndef ___aligned_offset_realloc_dbg_defined
#define ___aligned_offset_realloc_dbg_defined
#ifdef __CRT_HAVE__aligned_offset_realloc_dbg
__LIBC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBDCALL _aligned_offset_realloc_dbg)(void *__ptr, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset, char const *__filename, int __line) __CASMNAME_SAME("_aligned_offset_realloc_dbg");
#elif defined(__CRT_HAVE__aligned_offset_realloc) || ((defined(__CRT_HAVE__aligned_offset_malloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE__aligned_free) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)))
#include <libc/local/crtdbg/_aligned_offset_realloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_offset_realloc_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBDCALL _aligned_offset_realloc_dbg)(void *__ptr, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_offset_realloc_dbg))(__ptr, __num_bytes, __min_alignment, __offset, __filename, __line); })
#else /* ... */
#undef ___aligned_offset_realloc_dbg_defined
#endif /* !... */
#endif /* !___aligned_offset_realloc_dbg_defined */
#ifndef ___aligned_offset_recalloc_dbg_defined
#define ___aligned_offset_recalloc_dbg_defined
#ifdef __CRT_HAVE__aligned_offset_recalloc_dbg
__LIBC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBDCALL _aligned_offset_recalloc_dbg)(void *__ptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset, char const *__filename, int __line) __CASMNAME_SAME("_aligned_offset_recalloc_dbg");
#elif defined(__CRT_HAVE__aligned_offset_recalloc) || ((defined(__CRT_HAVE__aligned_offset_malloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE__aligned_free) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)))
#include <libc/local/crtdbg/_aligned_offset_recalloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_offset_recalloc_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBDCALL _aligned_offset_recalloc_dbg)(void *__ptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_offset_recalloc_dbg))(__ptr, __count, __num_bytes, __min_alignment, __offset, __filename, __line); })
#else /* ... */
#undef ___aligned_offset_recalloc_dbg_defined
#endif /* !... */
#endif /* !___aligned_offset_recalloc_dbg_defined */
#ifndef ___aligned_free_dbg_defined
#define ___aligned_free_dbg_defined
#ifdef __CRT_HAVE__aligned_free_dbg
__LIBC void __NOTHROW_NCX(__LIBDCALL _aligned_free_dbg)(void *__ptr) __CASMNAME_SAME("_aligned_free_dbg");
#elif defined(__CRT_HAVE__aligned_free) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#include <libc/local/crtdbg/_aligned_free_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_free_dbg, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBDCALL _aligned_free_dbg)(void *__ptr) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_free_dbg))(__ptr); })
#else /* ... */
#undef ___aligned_free_dbg_defined
#endif /* !... */
#endif /* !___aligned_free_dbg_defined */
#ifndef ___strdup_dbg_defined
#define ___strdup_dbg_defined
#ifdef __CRT_HAVE__strdup_dbg
__LIBC __ATTR_MALLOC __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBDCALL _strdup_dbg)(char const *__string, int __block_type, char const *__filename, int __line) __CASMNAME_SAME("_strdup_dbg");
#elif defined(__CRT_HAVE__mbsdup_dbg)
__COMPILER_CREDIRECT(__LIBC,__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,__LIBDCALL,_strdup_dbg,(char const *__string, int __block_type, char const *__filename, int __line),_mbsdup_dbg,(__string,__block_type,__filename,__line))
#elif defined(__CRT_HAVE_strdup) || defined(__CRT_HAVE__strdup) || defined(__CRT_HAVE__mbsdup) || defined(__CRT_HAVE___strdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/crtdbg/_strdup_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strdup_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBDCALL _strdup_dbg)(char const *__string, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strdup_dbg))(__string, __block_type, __filename, __line); })
#else /* ... */
#undef ___strdup_dbg_defined
#endif /* !... */
#endif /* !___strdup_dbg_defined */
#ifndef ___wcsdup_dbg_defined
#define ___wcsdup_dbg_defined
#ifdef __CRT_HAVE__wcsdup_dbg
__LIBC __ATTR_MALLOC __ATTR_WUNUSED __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBDCALL _wcsdup_dbg)(__WCHAR16_TYPE__ const *__string, int __block_type, char const *__filename, int __line) __CASMNAME_SAME("_wcsdup_dbg");
#elif (defined(__CRT_HAVE_wcsdup) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wcsdup) || (defined(__CRT_HAVE__wcsdup) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wcsdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/crtdbg/_wcsdup_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsdup_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBDCALL _wcsdup_dbg)(__WCHAR16_TYPE__ const *__string, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsdup_dbg))(__string, __block_type, __filename, __line); })
#else /* ... */
#undef ___wcsdup_dbg_defined
#endif /* !... */
#endif /* !___wcsdup_dbg_defined */
#ifndef ___tempnam_dbg_defined
#define ___tempnam_dbg_defined
#ifdef __CRT_HAVE__tempnam_dbg
__LIBC __ATTR_MALLOC __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBDCALL _tempnam_dbg)(char const *__dir_name, char const *__file_prefix, int __block_type, char const *__filename, int __line) __CASMNAME_SAME("_tempnam_dbg");
#elif defined(__CRT_HAVE_tempnam) || defined(__CRT_HAVE__tempnam)
#include <libc/local/crtdbg/_tempnam_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_tempnam_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBDCALL _tempnam_dbg)(char const *__dir_name, char const *__file_prefix, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_tempnam_dbg))(__dir_name, __file_prefix, __block_type, __filename, __line); })
#else /* ... */
#undef ___tempnam_dbg_defined
#endif /* !... */
#endif /* !___tempnam_dbg_defined */
#ifndef ___wtempnam_dbg_defined
#define ___wtempnam_dbg_defined
#ifdef __CRT_HAVE__wtempnam_dbg
__LIBC __ATTR_WUNUSED __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBDCALL _wtempnam_dbg)(__WCHAR16_TYPE__ const *__dir_name, __WCHAR16_TYPE__ const *__file_prefix, int __block_type, char const *__filename, int __line) __CASMNAME_SAME("_wtempnam_dbg");
#else /* __CRT_HAVE__wtempnam_dbg */
#include <libc/local/crtdbg/_wtempnam_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtempnam_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBDCALL _wtempnam_dbg)(__WCHAR16_TYPE__ const *__dir_name, __WCHAR16_TYPE__ const *__file_prefix, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtempnam_dbg))(__dir_name, __file_prefix, __block_type, __filename, __line); })
#endif /* !__CRT_HAVE__wtempnam_dbg */
#endif /* !___wtempnam_dbg_defined */
#ifndef ___fullpath_dbg_defined
#define ___fullpath_dbg_defined
#ifdef __CRT_HAVE__fullpath_dbg
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBDCALL _fullpath_dbg)(char *__full_path, char const *__path, __SIZE_TYPE__ __bufsize, int __block_type, char const *__filename, int __line) __CASMNAME_SAME("_fullpath_dbg");
#else /* __CRT_HAVE__fullpath_dbg */
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE__fullpath) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_frealpathat))
#include <libc/local/crtdbg/_fullpath_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_fullpath_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBDCALL _fullpath_dbg)(char *__full_path, char const *__path, __SIZE_TYPE__ __bufsize, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fullpath_dbg))(__full_path, __path, __bufsize, __block_type, __filename, __line); })
#else /* __CRT_HAVE__fullpath || (__AT_FDCWD && __CRT_HAVE_frealpathat) */
#undef ___fullpath_dbg_defined
#endif /* !__CRT_HAVE__fullpath && (!__AT_FDCWD || !__CRT_HAVE_frealpathat) */
#endif /* !__CRT_HAVE__fullpath_dbg */
#endif /* !___fullpath_dbg_defined */
#ifndef ___wfullpath_dbg_defined
#define ___wfullpath_dbg_defined
#ifdef __CRT_HAVE__wfullpath_dbg
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((2)) __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBDCALL _wfullpath_dbg)(__WCHAR16_TYPE__ *__full_path, __WCHAR16_TYPE__ const *__path, __SIZE_TYPE__ __buflen, int __block_type, char const *__filename, int __line) __CASMNAME_SAME("_wfullpath_dbg");
#else /* __CRT_HAVE__wfullpath_dbg */
#include <libc/local/crtdbg/_wfullpath_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wfullpath_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBDCALL _wfullpath_dbg)(__WCHAR16_TYPE__ *__full_path, __WCHAR16_TYPE__ const *__path, __SIZE_TYPE__ __buflen, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wfullpath_dbg))(__full_path, __path, __buflen, __block_type, __filename, __line); })
#endif /* !__CRT_HAVE__wfullpath_dbg */
#endif /* !___wfullpath_dbg_defined */
#ifndef ___getcwd_dbg_defined
#define ___getcwd_dbg_defined
#ifdef __CRT_HAVE__getcwd_dbg
__LIBC __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBDCALL _getcwd_dbg)(char *__buf, __STDC_INT_AS_SIZE_T __bufsize, int __block_type, char const *__filename, int __line) __CASMNAME_SAME("_getcwd_dbg");
#elif defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)
#include <libc/local/crtdbg/_getcwd_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_getcwd_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBDCALL _getcwd_dbg)(char *__buf, __STDC_INT_AS_SIZE_T __bufsize, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_getcwd_dbg))(__buf, __bufsize, __block_type, __filename, __line); })
#else /* ... */
#undef ___getcwd_dbg_defined
#endif /* !... */
#endif /* !___getcwd_dbg_defined */
#ifndef ___wgetcwd_dbg_defined
#define ___wgetcwd_dbg_defined
#ifdef __CRT_HAVE__wgetcwd_dbg
__LIBC __ATTR_WUNUSED __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBDCALL _wgetcwd_dbg)(__WCHAR16_TYPE__ *__buf, __STDC_INT_AS_SIZE_T __buflen, int __block_type, char const *__filename, int __line) __CASMNAME_SAME("_wgetcwd_dbg");
#elif (defined(__CRT_HAVE_wgetcwd) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wgetcwd) || (defined(__CRT_HAVE__wgetcwd) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wgetcwd) || ((defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || ((defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_DOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))
#include <libc/local/crtdbg/_wgetcwd_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wgetcwd_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBDCALL _wgetcwd_dbg)(__WCHAR16_TYPE__ *__buf, __STDC_INT_AS_SIZE_T __buflen, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wgetcwd_dbg))(__buf, __buflen, __block_type, __filename, __line); })
#else /* ... */
#undef ___wgetcwd_dbg_defined
#endif /* !... */
#endif /* !___wgetcwd_dbg_defined */
#ifndef ___getdcwd_dbg_defined
#define ___getdcwd_dbg_defined
#ifdef __CRT_HAVE__getdcwd_dbg
__LIBC __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBDCALL _getdcwd_dbg)(int __driveno, char *__buf, __STDC_INT_AS_SIZE_T __bufsize, int __block_type, char const *__filename, int __line) __CASMNAME_SAME("_getdcwd_dbg");
#else /* __CRT_HAVE__getdcwd_dbg */
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE__getdcwd) || defined(__CRT_HAVE__getdcwd_nolock) || (defined(__CRT_HAVE_frealpath4) && defined(__AT_FDDRIVE_CWD))
#include <libc/local/crtdbg/_getdcwd_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_getdcwd_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBDCALL _getdcwd_dbg)(int __driveno, char *__buf, __STDC_INT_AS_SIZE_T __bufsize, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_getdcwd_dbg))(__driveno, __buf, __bufsize, __block_type, __filename, __line); })
#else /* __CRT_HAVE__getdcwd || __CRT_HAVE__getdcwd_nolock || (__CRT_HAVE_frealpath4 && __AT_FDDRIVE_CWD) */
#undef ___getdcwd_dbg_defined
#endif /* !__CRT_HAVE__getdcwd && !__CRT_HAVE__getdcwd_nolock && (!__CRT_HAVE_frealpath4 || !__AT_FDDRIVE_CWD) */
#endif /* !__CRT_HAVE__getdcwd_dbg */
#endif /* !___getdcwd_dbg_defined */
#ifndef ___wgetdcwd_dbg_defined
#define ___wgetdcwd_dbg_defined
#ifdef __CRT_HAVE__wgetdcwd_dbg
__LIBC __ATTR_WUNUSED __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBDCALL _wgetdcwd_dbg)(int __driveno, __WCHAR16_TYPE__ *__buf, __STDC_INT_AS_SIZE_T __buflen, int __block_type, char const *__filename, int __line) __CASMNAME_SAME("_wgetdcwd_dbg");
#else /* __CRT_HAVE__wgetdcwd_dbg */
#include <libc/local/crtdbg/_wgetdcwd_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wgetdcwd_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBDCALL _wgetdcwd_dbg)(int __driveno, __WCHAR16_TYPE__ *__buf, __STDC_INT_AS_SIZE_T __buflen, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wgetdcwd_dbg))(__driveno, __buf, __buflen, __block_type, __filename, __line); })
#endif /* !__CRT_HAVE__wgetdcwd_dbg */
#endif /* !___wgetdcwd_dbg_defined */
#ifndef ___getdcwd_lk_dbg_defined
#define ___getdcwd_lk_dbg_defined
#ifdef __CRT_HAVE__getdcwd_dbg
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED,char *,__NOTHROW_NCX,__LIBDCALL,_getdcwd_lk_dbg,(int __driveno, char *__buf, __STDC_INT_AS_SIZE_T __bufsize, int __block_type, char const *__filename, int __line),_getdcwd_dbg,(__driveno,__buf,__bufsize,__block_type,__filename,__line))
#else /* __CRT_HAVE__getdcwd_dbg */
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE__getdcwd) || defined(__CRT_HAVE__getdcwd_nolock) || (defined(__CRT_HAVE_frealpath4) && defined(__AT_FDDRIVE_CWD))
#include <libc/local/crtdbg/_getdcwd_dbg.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBDCALL _getdcwd_lk_dbg)(int __driveno, char *__buf, __STDC_INT_AS_SIZE_T __bufsize, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_getdcwd_dbg))(__driveno, __buf, __bufsize, __block_type, __filename, __line); }
#else /* __CRT_HAVE__getdcwd || __CRT_HAVE__getdcwd_nolock || (__CRT_HAVE_frealpath4 && __AT_FDDRIVE_CWD) */
#undef ___getdcwd_lk_dbg_defined
#endif /* !__CRT_HAVE__getdcwd && !__CRT_HAVE__getdcwd_nolock && (!__CRT_HAVE_frealpath4 || !__AT_FDDRIVE_CWD) */
#endif /* !__CRT_HAVE__getdcwd_dbg */
#endif /* !___getdcwd_lk_dbg_defined */
#ifndef ___wgetdcwd_lk_dbg_defined
#define ___wgetdcwd_lk_dbg_defined
#ifdef __CRT_HAVE__wgetdcwd_dbg
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED,__WCHAR16_TYPE__ *,__NOTHROW_NCX,__LIBDCALL,_wgetdcwd_lk_dbg,(int __driveno, __WCHAR16_TYPE__ *__buf, __STDC_INT_AS_SIZE_T __buflen, int __block_type, char const *__filename, int __line),_wgetdcwd_dbg,(__driveno,__buf,__buflen,__block_type,__filename,__line))
#else /* __CRT_HAVE__wgetdcwd_dbg */
#include <libc/local/crtdbg/_wgetdcwd_dbg.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBDCALL _wgetdcwd_lk_dbg)(int __driveno, __WCHAR16_TYPE__ *__buf, __STDC_INT_AS_SIZE_T __buflen, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wgetdcwd_dbg))(__driveno, __buf, __buflen, __block_type, __filename, __line); }
#endif /* !__CRT_HAVE__wgetdcwd_dbg */
#endif /* !___wgetdcwd_lk_dbg_defined */
#ifndef ___dupenv_s_dbg_defined
#define ___dupenv_s_dbg_defined
#ifdef __CRT_HAVE__dupenv_s_dbg
__LIBC _Check_return_wat_ __ATTR_NONNULL((3)) __errno_t __NOTHROW_NCX(__LIBDCALL _dupenv_s_dbg)(char **__pbuf, __SIZE_TYPE__ *__pbufsize, char const *__varname, int __block_type, char const *__filename, int __line) __CASMNAME_SAME("_dupenv_s_dbg");
#else /* __CRT_HAVE__dupenv_s_dbg */
#include <libc/template/environ.h>
#if defined(__CRT_HAVE__dupenv_s) || ((defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_strdup) || defined(__CRT_HAVE__strdup) || defined(__CRT_HAVE__mbsdup) || defined(__CRT_HAVE___strdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)))
#include <libc/local/crtdbg/_dupenv_s_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_dupenv_s_dbg, __FORCELOCAL __ATTR_ARTIFICIAL _Check_return_wat_ __ATTR_NONNULL((3)) __errno_t __NOTHROW_NCX(__LIBDCALL _dupenv_s_dbg)(char **__pbuf, __SIZE_TYPE__ *__pbufsize, char const *__varname, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_dupenv_s_dbg))(__pbuf, __pbufsize, __varname, __block_type, __filename, __line); })
#else /* __CRT_HAVE__dupenv_s || ((__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_strdup || __CRT_HAVE__strdup || __CRT_HAVE__mbsdup || __CRT_HAVE___strdup || __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign)) */
#undef ___dupenv_s_dbg_defined
#endif /* !__CRT_HAVE__dupenv_s && ((!__CRT_HAVE_getenv && !__LOCAL_environ) || (!__CRT_HAVE_strdup && !__CRT_HAVE__strdup && !__CRT_HAVE__mbsdup && !__CRT_HAVE___strdup && !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign)) */
#endif /* !__CRT_HAVE__dupenv_s_dbg */
#endif /* !___dupenv_s_dbg_defined */
#ifndef ___wdupenv_s_dbg_defined
#define ___wdupenv_s_dbg_defined
#ifdef __CRT_HAVE__wdupenv_s_dbg
__LIBC _Check_return_wat_ __ATTR_NONNULL((3)) __errno_t __NOTHROW_NCX(__LIBDCALL _wdupenv_s_dbg)(__WCHAR16_TYPE__ **__pbuf, __SIZE_TYPE__ *__pbuflen, __WCHAR16_TYPE__ const *__varname, int __block_type, char const *__filename, int __line) __CASMNAME_SAME("_wdupenv_s_dbg");
#else /* __CRT_HAVE__wdupenv_s_dbg */
#include <libc/local/crtdbg/_wdupenv_s_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wdupenv_s_dbg, __FORCELOCAL __ATTR_ARTIFICIAL _Check_return_wat_ __ATTR_NONNULL((3)) __errno_t __NOTHROW_NCX(__LIBDCALL _wdupenv_s_dbg)(__WCHAR16_TYPE__ **__pbuf, __SIZE_TYPE__ *__pbuflen, __WCHAR16_TYPE__ const *__varname, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wdupenv_s_dbg))(__pbuf, __pbuflen, __varname, __block_type, __filename, __line); })
#endif /* !__CRT_HAVE__wdupenv_s_dbg */
#endif /* !___wdupenv_s_dbg_defined */
#ifdef __CRT_HAVE__CrtCheckMemory
__LIBC int __NOTHROW_NCX(__LIBDCALL _CrtCheckMemory)(void) __CASMNAME_SAME("_CrtCheckMemory");
#else /* __CRT_HAVE__CrtCheckMemory */
#include <libc/local/crtdbg/_CrtCheckMemory.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtCheckMemory, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBDCALL _CrtCheckMemory)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtCheckMemory))(); })
#endif /* !__CRT_HAVE__CrtCheckMemory */
#ifdef __CRT_HAVE__CrtDoForAllClientObjects
__LIBC __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBDCALL _CrtDoForAllClientObjects)(_PFNCRTDOFORALLCLIENTOBJECTS __pfn, void *__context) __CASMNAME_SAME("_CrtDoForAllClientObjects");
#else /* __CRT_HAVE__CrtDoForAllClientObjects */
#include <libc/local/crtdbg/_CrtDoForAllClientObjects.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtDoForAllClientObjects, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBDCALL _CrtDoForAllClientObjects)(_PFNCRTDOFORALLCLIENTOBJECTS __pfn, void *__context) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtDoForAllClientObjects))(__pfn, __context); })
#endif /* !__CRT_HAVE__CrtDoForAllClientObjects */
#ifdef __CRT_HAVE__CrtIsValidPointer
__LIBC __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL _CrtIsValidPointer)(void const *__ptr, __STDC_UINT_AS_SIZE_T __num_bytes, int __writable) __CASMNAME_SAME("_CrtIsValidPointer");
#else /* __CRT_HAVE__CrtIsValidPointer */
#include <libc/local/crtdbg/_CrtIsValidPointer.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtIsValidPointer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL _CrtIsValidPointer)(void const *__ptr, __STDC_UINT_AS_SIZE_T __num_bytes, int __writable) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtIsValidPointer))(__ptr, __num_bytes, __writable); })
#endif /* !__CRT_HAVE__CrtIsValidPointer */
#ifdef __CRT_HAVE__CrtIsValidHeapPointer
__LIBC __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL _CrtIsValidHeapPointer)(void const *__heap_ptr) __CASMNAME_SAME("_CrtIsValidHeapPointer");
#else /* __CRT_HAVE__CrtIsValidHeapPointer */
#include <libc/local/crtdbg/_CrtIsValidHeapPointer.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtIsValidHeapPointer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL _CrtIsValidHeapPointer)(void const *__heap_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtIsValidHeapPointer))(__heap_ptr); })
#endif /* !__CRT_HAVE__CrtIsValidHeapPointer */
#ifdef __CRT_HAVE__CrtIsMemoryBlock
__LIBC int __NOTHROW_NCX(__LIBDCALL _CrtIsMemoryBlock)(void const *__ptr, __STDC_UINT_AS_SIZE_T __num_bytes, __LONG32_TYPE__ *__prequest_number, char **__filename, int *__line) __CASMNAME_SAME("_CrtIsMemoryBlock");
#else /* __CRT_HAVE__CrtIsMemoryBlock */
#include <libc/local/crtdbg/_CrtIsMemoryBlock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtIsMemoryBlock, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBDCALL _CrtIsMemoryBlock)(void const *__ptr, __STDC_UINT_AS_SIZE_T __num_bytes, __LONG32_TYPE__ *__prequest_number, char **__filename, int *__line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtIsMemoryBlock))(__ptr, __num_bytes, __prequest_number, __filename, __line); })
#endif /* !__CRT_HAVE__CrtIsMemoryBlock */
#ifdef __CRT_HAVE__CrtReportBlockType
__LIBC __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL _CrtReportBlockType)(void const *__ptr) __CASMNAME_SAME("_CrtReportBlockType");
#else /* __CRT_HAVE__CrtReportBlockType */
#include <libc/local/crtdbg/_CrtReportBlockType.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtReportBlockType, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL _CrtReportBlockType)(void const *__ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtReportBlockType))(__ptr); })
#endif /* !__CRT_HAVE__CrtReportBlockType */
#ifdef __CRT_HAVE__CrtMemCheckpoint
__LIBC __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBDCALL _CrtMemCheckpoint)(_CrtMemState *__state) __CASMNAME_SAME("_CrtMemCheckpoint");
#else /* __CRT_HAVE__CrtMemCheckpoint */
#include <libc/local/crtdbg/_CrtMemCheckpoint.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtMemCheckpoint, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBDCALL _CrtMemCheckpoint)(_CrtMemState *__state) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtMemCheckpoint))(__state); })
#endif /* !__CRT_HAVE__CrtMemCheckpoint */
#ifdef __CRT_HAVE__CrtMemDifference
__LIBC __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBDCALL _CrtMemDifference)(_CrtMemState *__state, _CrtMemState const *__old_state, _CrtMemState const *__new_state) __CASMNAME_SAME("_CrtMemDifference");
#else /* __CRT_HAVE__CrtMemDifference */
#include <libc/local/crtdbg/_CrtMemDifference.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtMemDifference, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBDCALL _CrtMemDifference)(_CrtMemState *__state, _CrtMemState const *__old_state, _CrtMemState const *__new_state) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtMemDifference))(__state, __old_state, __new_state); })
#endif /* !__CRT_HAVE__CrtMemDifference */
#ifdef __CRT_HAVE__CrtMemDumpAllObjectsSince
__LIBC __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBDCALL _CrtMemDumpAllObjectsSince)(_CrtMemState const *__state) __CASMNAME_SAME("_CrtMemDumpAllObjectsSince");
#else /* __CRT_HAVE__CrtMemDumpAllObjectsSince */
#include <libc/local/crtdbg/_CrtMemDumpAllObjectsSince.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtMemDumpAllObjectsSince, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBDCALL _CrtMemDumpAllObjectsSince)(_CrtMemState const *__state) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtMemDumpAllObjectsSince))(__state); })
#endif /* !__CRT_HAVE__CrtMemDumpAllObjectsSince */
#ifdef __CRT_HAVE__CrtMemDumpStatistics
__LIBC __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBDCALL _CrtMemDumpStatistics)(_CrtMemState const *__state) __CASMNAME_SAME("_CrtMemDumpStatistics");
#else /* __CRT_HAVE__CrtMemDumpStatistics */
#include <libc/local/crtdbg/_CrtMemDumpStatistics.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtMemDumpStatistics, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBDCALL _CrtMemDumpStatistics)(_CrtMemState const *__state) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtMemDumpStatistics))(__state); })
#endif /* !__CRT_HAVE__CrtMemDumpStatistics */
#ifdef __CRT_HAVE__CrtDumpMemoryLeaks
__LIBC int __NOTHROW_NCX(__LIBDCALL _CrtDumpMemoryLeaks)(void) __CASMNAME_SAME("_CrtDumpMemoryLeaks");
#else /* __CRT_HAVE__CrtDumpMemoryLeaks */
#include <libc/local/crtdbg/_CrtDumpMemoryLeaks.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtDumpMemoryLeaks, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBDCALL _CrtDumpMemoryLeaks)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtDumpMemoryLeaks))(); })
#endif /* !__CRT_HAVE__CrtDumpMemoryLeaks */
#ifdef __CRT_HAVE__CrtSetCheckCount
__LIBC int __NOTHROW_NCX(__LIBDCALL _CrtSetCheckCount)(int __check_count) __CASMNAME_SAME("_CrtSetCheckCount");
#else /* __CRT_HAVE__CrtSetCheckCount */
#include <libc/local/crtdbg/_CrtSetCheckCount.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtSetCheckCount, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBDCALL _CrtSetCheckCount)(int __check_count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtSetCheckCount))(__check_count); })
#endif /* !__CRT_HAVE__CrtSetCheckCount */
#ifdef __CRT_HAVE__CrtGetCheckCount
__LIBC __ATTR_PURE int __NOTHROW_NCX(__LIBDCALL _CrtGetCheckCount)(void) __CASMNAME_SAME("_CrtGetCheckCount");
#else /* __CRT_HAVE__CrtGetCheckCount */
#include <libc/local/crtdbg/_CrtGetCheckCount.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtGetCheckCount, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE int __NOTHROW_NCX(__LIBDCALL _CrtGetCheckCount)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtGetCheckCount))(); })
#endif /* !__CRT_HAVE__CrtGetCheckCount */

#ifndef ___CrtDbgBreak_defined
#define ___CrtDbgBreak_defined
__SYSDECL_END
#include <intrin.h>
__SYSDECL_BEGIN
#define _CrtDbgBreak() __debugbreak()
#endif /* !___CrtDbgBreak_defined */

#define _malloca_dbg(s, t, f, l) _malloc_dbg(s, t, f, l)
#define _freea_dbg(p, t) _free_dbg(p, t)

#if defined(__cplusplus) && defined(_CRTDBG_MAP_ALLOC)
__NAMESPACE_STD_BEGIN
#ifdef ___calloc_dbg_defined
__NAMESPACE_GLB_USING_OR_IMPL(_calloc_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)) void *__NOTHROW_NCX(__LIBDCALL _calloc_dbg)(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) { return (::_calloc_dbg)(__count, __num_bytes, __block_type, __filename, __line); })
#endif /* ___calloc_dbg_defined */
#ifdef ___free_dbg_defined
__NAMESPACE_GLB_USING_OR_IMPL(_free_dbg, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBDCALL _free_dbg)(void *__ptr, int __block_type) { return (::_free_dbg)(__ptr, __block_type); })
#endif /* ___free_dbg_defined */
#ifdef ___malloc_dbg_defined
__NAMESPACE_GLB_USING_OR_IMPL(_malloc_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBDCALL _malloc_dbg)(__SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) { return (::_malloc_dbg)(__num_bytes, __block_type, __filename, __line); })
#endif /* ___malloc_dbg_defined */
#ifdef ___realloc_dbg_defined
__NAMESPACE_GLB_USING_OR_IMPL(_realloc_dbg, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBDCALL _realloc_dbg)(void *__ptr, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) { return (::_realloc_dbg)(__ptr, __num_bytes, __block_type, __filename, __line); })
#endif /* ___realloc_dbg_defined */
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
#define _ASSERTE(expr) _ASSERT_EXPR(expr, _CRT_WIDE(#expr))
#endif  /* _ASSERTE */
#ifndef _ASSERT_BASE
#define _ASSERT_BASE _ASSERT_EXPR
#endif  /* _ASSERT_BASE */

#define _RPT0(rptno, msg)                                _RPT_BASE((rptno, __NULLPTR, 0, __NULLPTR, "%s", msg))
#define _RPT1(rptno, msg, arg1)                          _RPT_BASE((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1))
#define _RPT2(rptno, msg, arg1, arg2)                    _RPT_BASE((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1, arg2))
#define _RPT3(rptno, msg, arg1, arg2, arg3)              _RPT_BASE((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1, arg2, arg3))
#define _RPT4(rptno, msg, arg1, arg2, arg3, arg4)        _RPT_BASE((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1, arg2, arg3, arg4))
#define _RPT5(rptno, msg, arg1, arg2, arg3, arg4, arg5)  _RPT_BASE((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1, arg2, arg3, arg4, arg5))
#define _RPTF0(rptno, msg)                               _RPT_BASE((rptno, __FILE__, __LINE__, __NULLPTR, "%s", msg))
#define _RPTF1(rptno, msg, arg1)                         _RPT_BASE((rptno, __FILE__, __LINE__, __NULLPTR, msg, arg1))
#define _RPTF2(rptno, msg, arg1, arg2)                   _RPT_BASE((rptno, __FILE__, __LINE__, __NULLPTR, msg, arg1, arg2))
#define _RPTF3(rptno, msg, arg1, arg2, arg3)             _RPT_BASE((rptno, __FILE__, __LINE__, __NULLPTR, msg, arg1, arg2, arg3))
#define _RPTF4(rptno, msg, arg1, arg2, arg3, arg4)       _RPT_BASE((rptno, __FILE__, __LINE__, __NULLPTR, msg, arg1, arg2, arg3, arg4))
#define _RPTF5(rptno, msg, arg1, arg2, arg3, arg4, arg5) _RPT_BASE((rptno, __FILE__, __LINE__, __NULLPTR, msg, arg1, arg2, arg3, arg4, arg5))
#ifdef __HAVE_NATIVE_RPT_BASE_W
#define _RPTW0(rptno, msg)  _RPT_BASE_W((rptno, __NULLPTR, 0, __NULLPTR, L"%s", msg))
#define _RPTFW0(rptno, msg) _RPT_BASE_W((rptno, _CRT_WIDE(__FILE__), __LINE__, __NULLPTR, L"%s", msg))
#else /* __HAVE_NATIVE_RPT_BASE_W */
#define _RPTW0(rptno, msg)  _RPT_BASE((rptno, __NULLPTR, 0, __NULLPTR, "%ls", msg))
#define _RPTFW0(rptno, msg) _RPT_BASE((rptno, __FILE__, __LINE__, __NULLPTR, "%ls", msg))
#endif /* !__HAVE_NATIVE_RPT_BASE_W */
#define _RPTW1(rptno, msg, arg1)                          _RPT_BASE_W((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1))
#define _RPTW2(rptno, msg, arg1, arg2)                    _RPT_BASE_W((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1, arg2))
#define _RPTW3(rptno, msg, arg1, arg2, arg3)              _RPT_BASE_W((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1, arg2, arg3))
#define _RPTW4(rptno, msg, arg1, arg2, arg3, arg4)        _RPT_BASE_W((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1, arg2, arg3, arg4))
#define _RPTW5(rptno, msg, arg1, arg2, arg3, arg4, arg5)  _RPT_BASE_W((rptno, __NULLPTR, 0, __NULLPTR, msg, arg1, arg2, arg3, arg4, arg5))
#define _RPTFW1(rptno, msg, arg1)                         _RPT_BASE_W((rptno, _CRT_WIDE(__FILE__), __LINE__, __NULLPTR, msg, arg1))
#define _RPTFW2(rptno, msg, arg1, arg2)                   _RPT_BASE_W((rptno, _CRT_WIDE(__FILE__), __LINE__, __NULLPTR, msg, arg1, arg2))
#define _RPTFW3(rptno, msg, arg1, arg2, arg3)             _RPT_BASE_W((rptno, _CRT_WIDE(__FILE__), __LINE__, __NULLPTR, msg, arg1, arg2, arg3))
#define _RPTFW4(rptno, msg, arg1, arg2, arg3, arg4)       _RPT_BASE_W((rptno, _CRT_WIDE(__FILE__), __LINE__, __NULLPTR, msg, arg1, arg2, arg3, arg4))
#define _RPTFW5(rptno, msg, arg1, arg2, arg3, arg4, arg5) _RPT_BASE_W((rptno, _CRT_WIDE(__FILE__), __LINE__, __NULLPTR, msg, arg1, arg2, arg3, arg4, arg5))
#ifdef _CRTDBG_MAP_ALLOC
#define malloc(s)                               _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define calloc(c, s)                            _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define realloc(p, s)                           _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _recalloc(p, c, s)                      _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _expand(p, s)                           _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define free(p)                                 _free_dbg(p, _NORMAL_BLOCK)
#define _msize(p)                               _msize_dbg(p, _NORMAL_BLOCK)
#define _aligned_msize(p, a, o)                 _aligned_msize_dbg(p, a, o)
#define _aligned_malloc(s, a)                   _aligned_malloc_dbg(s, a, __FILE__, __LINE__)
#define _aligned_realloc(p, s, a)               _aligned_realloc_dbg(p, s, a, __FILE__, __LINE__)
#define _aligned_recalloc(p, c, s, a)           _aligned_recalloc_dbg(p, c, s, a, __FILE__, __LINE__)
#define _aligned_offset_malloc(s, a, o)         _aligned_offset_malloc_dbg(s, a, o, __FILE__, __LINE__)
#define _aligned_offset_realloc(p, s, a, o)     _aligned_offset_realloc_dbg(p, s, a, o, __FILE__, __LINE__)
#define _aligned_offset_recalloc(p, c, s, a, o) _aligned_offset_recalloc_dbg(p, c, s, a, o, __FILE__, __LINE__)
#define _aligned_free(p)                        _aligned_free_dbg(p)
#define _malloca(s)                             _malloca_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _freea(p)                               _freea_dbg(p, _NORMAL_BLOCK)
#define _strdup(s)                              _strdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _wcsdup(s)                              _wcsdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _mbsdup(s)                              _strdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _tempnam(s1, s2)                        _tempnam_dbg(s1, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _wtempnam(s1, s2)                       _wtempnam_dbg(s1, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _fullpath(s1, s2, le)                   _fullpath_dbg(s1, s2, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _wfullpath(s1, s2, le)                  _wfullpath_dbg(s1, s2, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _getcwd(s, le)                          _getcwd_dbg(s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _wgetcwd(s, le)                         _wgetcwd_dbg(s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _getdcwd(d, s, le)                      _getdcwd_dbg(d, s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _wgetdcwd(d, s, le)                     _wgetdcwd_dbg(d, s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _dupenv_s(ps1, size, s2)                _dupenv_s_dbg(ps1, size, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _wdupenv_s(ps1, size, s2)               _wdupenv_s_dbg(ps1, size, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
#define strdup(s)                               _strdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define wcsdup(s)                               _wcsdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define tempnam(s1, s2)                         _tempnam_dbg(s1, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
#define getcwd(s, le)                           _getcwd_dbg(s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif /* _CRTDBG_MAP_ALLOC */

#endif /* _DEBUG */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_CRTDBG_H */
