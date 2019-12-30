/* HASH CRC-32:0x6af20f4 */
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
#ifndef _CRTDBG_H
#define _CRTDBG_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

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
__LIBC __LONG32_TYPE__ _crtAssertBusy;
#else /* __CRT_HAVE__crtAssertBusy */
#ifndef ____p__crtAssertBusy_defined
#define ____p__crtAssertBusy_defined 1
#ifdef __CRT_HAVE___p__crtAssertBusy
__CDECLARE(,__LONG32_TYPE__ *,__NOTHROW_NCX,__p__crtAssertBusy,(void),())
#else /* LIBC: __p__crtAssertBusy */
#undef ____p__crtAssertBusy_defined
#endif /* __p__crtAssertBusy... */
#endif /* !____p__crtAssertBusy_defined */
#ifdef ____p__crtAssertBusy_defined
#define _crtAssertBusy  (*__p__crtAssertBusy())
#endif /* ____p__crtAssertBusy_defined */
#endif /* !__CRT_HAVE__crtAssertBusy */
#ifdef __CRT_HAVE__crtBreakAlloc
__LIBC __LONG32_TYPE__ _crtBreakAlloc;
#else /* __CRT_HAVE__crtBreakAlloc */
#ifndef ____p__crtBreakAlloc_defined
#define ____p__crtBreakAlloc_defined 1
#ifdef __CRT_HAVE___p__crtBreakAlloc
__CDECLARE(,__LONG32_TYPE__ *,__NOTHROW_NCX,__p__crtBreakAlloc,(void),())
#else /* LIBC: __p__crtBreakAlloc */
#undef ____p__crtBreakAlloc_defined
#endif /* __p__crtBreakAlloc... */
#endif /* !____p__crtBreakAlloc_defined */
#ifdef ____p__crtBreakAlloc_defined
#define _crtBreakAlloc  (*__p__crtBreakAlloc())
#endif /* ____p__crtBreakAlloc_defined */
#endif /* !__CRT_HAVE__crtBreakAlloc */
#ifdef __CRT_HAVE__crtDbgFlag
__LIBC int _crtDbgFlag;
#else /* __CRT_HAVE__crtDbgFlag */
#ifndef ____p__crtDbgFlag_defined
#define ____p__crtDbgFlag_defined 1
#ifdef __CRT_HAVE___p__crtDbgFlag
__CDECLARE(,int *,__NOTHROW_NCX,__p__crtDbgFlag,(void),())
#else /* LIBC: __p__crtDbgFlag */
#undef ____p__crtDbgFlag_defined
#endif /* __p__crtDbgFlag... */
#endif /* !____p__crtDbgFlag_defined */
#ifdef ____p__crtDbgFlag_defined
#define _crtDbgFlag  (*__p__crtDbgFlag())
#endif /* ____p__crtDbgFlag_defined */
#endif /* !__CRT_HAVE__crtDbgFlag */
#ifdef __CRT_HAVE__CrtGetReportHook
__CDECLARE(,_CRT_REPORT_HOOK,__NOTHROW_NCX,_CrtGetReportHook,(void),())
#endif /* _CrtGetReportHook... */
#ifdef __CRT_HAVE__CrtSetReportHook
__CDECLARE(,_CRT_REPORT_HOOK,__NOTHROW_NCX,_CrtSetReportHook,(_CRT_REPORT_HOOK __pfn_new_hook),(__pfn_new_hook))
#endif /* _CrtSetReportHook... */
#ifdef __CRT_HAVE__CrtSetReportHook2
__CDECLARE(,int,__NOTHROW_NCX,_CrtSetReportHook2,(int __mode, _CRT_REPORT_HOOK __pfn_new_hook),(__mode,__pfn_new_hook))
#endif /* _CrtSetReportHook2... */
#ifdef __CRT_HAVE__CrtSetReportHookW2
__CDECLARE(,int,__NOTHROW_NCX,_CrtSetReportHookW2,(int __mode, _CRT_REPORT_HOOKW __pfn_new_hook),(__mode,__pfn_new_hook))
#endif /* _CrtSetReportHookW2... */
#ifdef __CRT_HAVE__CrtGetAllocHook
__CDECLARE(,_CRT_ALLOC_HOOK,__NOTHROW_NCX,_CrtGetAllocHook,(void),())
#endif /* _CrtGetAllocHook... */
#ifdef __CRT_HAVE__CrtSetAllocHook
__CDECLARE(,_CRT_ALLOC_HOOK,__NOTHROW_NCX,_CrtSetAllocHook,(_CRT_ALLOC_HOOK __pfn_new_hook),(__pfn_new_hook))
#endif /* _CrtSetAllocHook... */
#ifdef __CRT_HAVE__CrtGetDumpClient
__CDECLARE(,_CRT_DUMP_CLIENT,__NOTHROW_NCX,_CrtGetDumpClient,(void),())
#endif /* _CrtGetDumpClient... */
#ifdef __CRT_HAVE__CrtSetDumpClient
__CDECLARE(,_CRT_DUMP_CLIENT,__NOTHROW_NCX,_CrtSetDumpClient,(_CRT_DUMP_CLIENT __pfn_new_dump),(__pfn_new_dump))
#endif /* _CrtSetDumpClient... */
#endif /* !_M_CEE_PURE */
#ifdef __CRT_HAVE__CrtSetDbgFlag
__CDECLARE(,int,__NOTHROW_NCX,_CrtSetDbgFlag,(int __new_flag),(__new_flag))
#elif defined(__CRT_HAVE___p__crtDbgFlag)
#include <local/crtdbg/_CrtSetDbgFlag.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtSetDbgFlag, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL _CrtSetDbgFlag)(int __new_flag) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtSetDbgFlag))(__new_flag); })
#endif /* _CrtSetDbgFlag... */
#ifdef __CRT_HAVE__CrtSetReportMode
__CDECLARE(,int,__NOTHROW_NCX,_CrtSetReportMode,(int __report_type, int __report_mode),(__report_type,__report_mode))
#endif /* _CrtSetReportMode... */
#ifdef __CRT_HAVE__CrtSetReportFile
__CDECLARE(,_HFILE,__NOTHROW_NCX,_CrtSetReportFile,(int __report_type, _HFILE __report_file),(__report_type,__report_file))
#endif /* _CrtSetReportFile... */
#ifdef __CRT_HAVE__CrtSetDebugFillThreshold
__CDECLARE(,__SIZE_TYPE__,__NOTHROW_NCX,_CrtSetDebugFillThreshold,(__SIZE_TYPE__ __new_debug_fill_threshold),(__new_debug_fill_threshold))
#endif /* _CrtSetDebugFillThreshold... */
#ifndef ___CrtDbgReport_defined
#define ___CrtDbgReport_defined 1
#ifdef __CRT_HAVE__CrtDbgReport
__LIBC int __NOTHROW_NCX(__VLIBCCALL _CrtDbgReport)(int __report_type, char const *__filename, int __line, char const *__module_name, char const *__format, ...) __CASMNAME_SAME("_CrtDbgReport");
#else /* LIBC: _CrtDbgReport */
#undef ___CrtDbgReport_defined
#endif /* _CrtDbgReport... */
#endif /* !___CrtDbgReport_defined */
#ifndef ___CrtDbgReportW_defined
#define ___CrtDbgReportW_defined 1
#ifdef __CRT_HAVE__CrtDbgReportW
__LIBC int __NOTHROW_NCX(__VLIBCCALL _CrtDbgReportW)(int __report_type, __WCHAR16_TYPE__ const *__filename, int __line, __WCHAR16_TYPE__ const *__module_name, __WCHAR16_TYPE__ const *__format, ...) __CASMNAME_SAME("_CrtDbgReportW");
#elif defined(__KOS__) && !defined(__NO_ASMNAME) && defined(__CRT_HAVE_$Q_CrtDbgReportW$A$AYAHHPBGH00ZZ)
__LIBC int __NOTHROW_NCX(__VLIBCCALL _CrtDbgReportW)(int __report_type, __WCHAR16_TYPE__ const *__filename, int __line, __WCHAR16_TYPE__ const *__module_name, __WCHAR16_TYPE__ const *__format, ...) __CASMNAME("?_CrtDbgReportW@@YAHHPBGH00ZZ");
#else /* LIBC: _CrtDbgReportW */
#undef ___CrtDbgReportW_defined
#endif /* _CrtDbgReportW... */
#endif /* !___CrtDbgReportW_defined */
#ifndef ___CrtDbgBreak_defined
#define ___CrtDbgBreak_defined 1
#ifdef __CRT_HAVE__CrtDbgBreak
__CDECLARE_VOID(,__NOTHROW_NCX,_CrtDbgBreak,(void),())
#else /* LIBC: _CrtDbgBreak */
#undef ___CrtDbgBreak_defined
#endif /* _CrtDbgBreak... */
#endif /* !___CrtDbgBreak_defined */
#ifdef __CRT_HAVE__CrtSetBreakAlloc
__CDECLARE(,__LONG32_TYPE__,__NOTHROW_NCX,_CrtSetBreakAlloc,(__LONG32_TYPE__ __break_alloc),(__break_alloc))
#endif /* _CrtSetBreakAlloc... */
#ifndef ___malloc_dbg_defined
#define ___malloc_dbg_defined 1
#ifdef __CRT_HAVE__malloc_dbg
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,_malloc_dbg,(__SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line),(__num_bytes,__block_type,__filename,__line))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#include <local/crtdbg/_malloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_malloc_dbg, __FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL _malloc_dbg)(__SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_malloc_dbg))(__num_bytes, __block_type, __filename, __line); })
#else /* CUSTOM: _malloc_dbg */
#undef ___malloc_dbg_defined
#endif /* _malloc_dbg... */
#endif /* !___malloc_dbg_defined */
#ifndef ___calloc_dbg_defined
#define ___calloc_dbg_defined 1
#ifdef __CRT_HAVE__calloc_dbg
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,_calloc_dbg,(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line),(__count,__num_bytes,__block_type,__filename,__line))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#include <local/crtdbg/_calloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_calloc_dbg, __FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)) void *__NOTHROW_NCX(__LIBCCALL _calloc_dbg)(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_calloc_dbg))(__count, __num_bytes, __block_type, __filename, __line); })
#else /* CUSTOM: _calloc_dbg */
#undef ___calloc_dbg_defined
#endif /* _calloc_dbg... */
#endif /* !___calloc_dbg_defined */
#ifndef ___realloc_dbg_defined
#define ___realloc_dbg_defined 1
#ifdef __CRT_HAVE__realloc_dbg
__CDECLARE(__ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,_realloc_dbg,(void *__ptr, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line),(__ptr,__num_bytes,__block_type,__filename,__line))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#include <local/crtdbg/_realloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_realloc_dbg, __FORCELOCAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL _realloc_dbg)(void *__ptr, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_realloc_dbg))(__ptr, __num_bytes, __block_type, __filename, __line); })
#else /* CUSTOM: _realloc_dbg */
#undef ___realloc_dbg_defined
#endif /* _realloc_dbg... */
#endif /* !___realloc_dbg_defined */
#ifndef ___recalloc_dbg_defined
#define ___recalloc_dbg_defined 1
#ifdef __CRT_HAVE__recalloc_dbg
__CDECLARE(__ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,_recalloc_dbg,(void *__ptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line),(__ptr,__count,__num_bytes,__block_type,__filename,__line))
#elif defined(__CRT_HAVE__recalloc)
#include <local/crtdbg/_recalloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_recalloc_dbg, __FORCELOCAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL _recalloc_dbg)(void *__ptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_recalloc_dbg))(__ptr, __count, __num_bytes, __block_type, __filename, __line); })
#else /* CUSTOM: _recalloc_dbg */
#undef ___recalloc_dbg_defined
#endif /* _recalloc_dbg... */
#endif /* !___recalloc_dbg_defined */
#ifndef ___expand_dbg_defined
#define ___expand_dbg_defined 1
#ifdef __CRT_HAVE__expand_dbg
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,_expand_dbg,(void *__ptr, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line),(__ptr,__num_bytes,__block_type,__filename,__line))
#elif defined(__CRT_HAVE_realloc_in_place) || defined(__CRT_HAVE__expand)
#include <local/crtdbg/_expand_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_expand_dbg, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL _expand_dbg)(void *__ptr, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_expand_dbg))(__ptr, __num_bytes, __block_type, __filename, __line); })
#else /* CUSTOM: _expand_dbg */
#undef ___expand_dbg_defined
#endif /* _expand_dbg... */
#endif /* !___expand_dbg_defined */
#ifndef ___free_dbg_defined
#define ___free_dbg_defined 1
#ifdef __CRT_HAVE__free_dbg
__CDECLARE_VOID(,__NOTHROW_NCX,_free_dbg,(void *__ptr, int __block_type),(__ptr,__block_type))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
#include <local/crtdbg/_free_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_free_dbg, __FORCELOCAL void __NOTHROW_NCX(__LIBCCALL _free_dbg)(void *__ptr, int __block_type) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_free_dbg))(__ptr, __block_type); })
#else /* CUSTOM: _free_dbg */
#undef ___free_dbg_defined
#endif /* _free_dbg... */
#endif /* !___free_dbg_defined */
#ifndef ___msize_dbg_defined
#define ___msize_dbg_defined 1
#ifdef __CRT_HAVE__msize_dbg
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,_msize_dbg,(void *__ptr, int __block_type),(__ptr,__block_type))
#elif defined(__CRT_HAVE__msize) || defined(__CRT_HAVE_malloc_usable_size)
#include <local/crtdbg/_msize_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_msize_dbg, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _msize_dbg)(void *__ptr, int __block_type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_msize_dbg))(__ptr, __block_type); })
#else /* CUSTOM: _msize_dbg */
#undef ___msize_dbg_defined
#endif /* _msize_dbg... */
#endif /* !___msize_dbg_defined */
#ifndef ___aligned_msize_dbg_defined
#define ___aligned_msize_dbg_defined 1
#ifdef __CRT_HAVE__aligned_msize_dbg
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,_aligned_msize_dbg,(void *__ptr, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),(__ptr,__min_alignment,__offset))
#else /* LIBC: _aligned_msize_dbg */
#include <local/crtdbg/_aligned_msize_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_msize_dbg, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _aligned_msize_dbg)(void *__ptr, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_msize_dbg))(__ptr, __min_alignment, __offset); })
#endif /* _aligned_msize_dbg... */
#endif /* !___aligned_msize_dbg_defined */
#ifndef ___aligned_malloc_dbg_defined
#define ___aligned_malloc_dbg_defined 1
#ifdef __CRT_HAVE__aligned_malloc_dbg
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) __ATTR_ALLOC_ALIGN(2),void *,__NOTHROW_NCX,_aligned_malloc_dbg,(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, char const *__filename, int __line),(__num_bytes,__min_alignment,__filename,__line))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE__aligned_malloc)
#include <local/crtdbg/_aligned_malloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_malloc_dbg, __FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) __ATTR_ALLOC_ALIGN(2) void *__NOTHROW_NCX(__LIBCCALL _aligned_malloc_dbg)(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_malloc_dbg))(__num_bytes, __min_alignment, __filename, __line); })
#else /* CUSTOM: _aligned_malloc_dbg */
#undef ___aligned_malloc_dbg_defined
#endif /* _aligned_malloc_dbg... */
#endif /* !___aligned_malloc_dbg_defined */
#ifndef ___aligned_realloc_dbg_defined
#define ___aligned_realloc_dbg_defined 1
#ifdef __CRT_HAVE__aligned_realloc_dbg
__CDECLARE(__ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(3),void *,__NOTHROW_NCX,_aligned_realloc_dbg,(void *__ptr, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, char const *__filename, int __line),(__ptr,__num_bytes,__min_alignment,__filename,__line))
#elif ((defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE__aligned_malloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE__aligned_free))) || defined(__CRT_HAVE__aligned_realloc)
#include <local/crtdbg/_aligned_realloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_realloc_dbg, __FORCELOCAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(3) void *__NOTHROW_NCX(__LIBCCALL _aligned_realloc_dbg)(void *__ptr, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_realloc_dbg))(__ptr, __num_bytes, __min_alignment, __filename, __line); })
#else /* CUSTOM: _aligned_realloc_dbg */
#undef ___aligned_realloc_dbg_defined
#endif /* _aligned_realloc_dbg... */
#endif /* !___aligned_realloc_dbg_defined */
#ifndef ___aligned_recalloc_dbg_defined
#define ___aligned_recalloc_dbg_defined 1
#ifdef __CRT_HAVE__aligned_recalloc_dbg
__CDECLARE(__ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) __ATTR_ALLOC_ALIGN(4),void *,__NOTHROW_NCX,_aligned_recalloc_dbg,(void *__ptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, char const *__filename, int __line),(__ptr,__count,__num_bytes,__min_alignment,__filename,__line))
#elif ((defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE__aligned_malloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE__aligned_free))) || defined(__CRT_HAVE__aligned_recalloc)
#include <local/crtdbg/_aligned_recalloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_recalloc_dbg, __FORCELOCAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) __ATTR_ALLOC_ALIGN(4) void *__NOTHROW_NCX(__LIBCCALL _aligned_recalloc_dbg)(void *__ptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_recalloc_dbg))(__ptr, __count, __num_bytes, __min_alignment, __filename, __line); })
#else /* CUSTOM: _aligned_recalloc_dbg */
#undef ___aligned_recalloc_dbg_defined
#endif /* _aligned_recalloc_dbg... */
#endif /* !___aligned_recalloc_dbg_defined */
#ifndef ___aligned_offset_malloc_dbg_defined
#define ___aligned_offset_malloc_dbg_defined 1
#ifdef __CRT_HAVE__aligned_offset_malloc_dbg
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,_aligned_offset_malloc_dbg,(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset, char const *__filename, int __line),(__num_bytes,__min_alignment,__offset,__filename,__line))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE__aligned_offset_malloc)
#include <local/crtdbg/_aligned_offset_malloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_offset_malloc_dbg, __FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL _aligned_offset_malloc_dbg)(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_offset_malloc_dbg))(__num_bytes, __min_alignment, __offset, __filename, __line); })
#else /* CUSTOM: _aligned_offset_malloc_dbg */
#undef ___aligned_offset_malloc_dbg_defined
#endif /* _aligned_offset_malloc_dbg... */
#endif /* !___aligned_offset_malloc_dbg_defined */
#ifndef ___aligned_offset_realloc_dbg_defined
#define ___aligned_offset_realloc_dbg_defined 1
#ifdef __CRT_HAVE__aligned_offset_realloc_dbg
__CDECLARE(__ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,_aligned_offset_realloc_dbg,(void *__ptr, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset, char const *__filename, int __line),(__ptr,__num_bytes,__min_alignment,__offset,__filename,__line))
#elif ((defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE__aligned_offset_malloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE__aligned_free))) || defined(__CRT_HAVE__aligned_offset_realloc)
#include <local/crtdbg/_aligned_offset_realloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_offset_realloc_dbg, __FORCELOCAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL _aligned_offset_realloc_dbg)(void *__ptr, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_offset_realloc_dbg))(__ptr, __num_bytes, __min_alignment, __offset, __filename, __line); })
#else /* CUSTOM: _aligned_offset_realloc_dbg */
#undef ___aligned_offset_realloc_dbg_defined
#endif /* _aligned_offset_realloc_dbg... */
#endif /* !___aligned_offset_realloc_dbg_defined */
#ifndef ___aligned_offset_recalloc_dbg_defined
#define ___aligned_offset_recalloc_dbg_defined 1
#ifdef __CRT_HAVE__aligned_offset_recalloc_dbg
__CDECLARE(__ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,_aligned_offset_recalloc_dbg,(void *__ptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset, char const *__filename, int __line),(__ptr,__count,__num_bytes,__min_alignment,__offset,__filename,__line))
#elif ((defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE__aligned_offset_malloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE__aligned_free))) || defined(__CRT_HAVE__aligned_offset_recalloc)
#include <local/crtdbg/_aligned_offset_recalloc_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_offset_recalloc_dbg, __FORCELOCAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL _aligned_offset_recalloc_dbg)(void *__ptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_offset_recalloc_dbg))(__ptr, __count, __num_bytes, __min_alignment, __offset, __filename, __line); })
#else /* CUSTOM: _aligned_offset_recalloc_dbg */
#undef ___aligned_offset_recalloc_dbg_defined
#endif /* _aligned_offset_recalloc_dbg... */
#endif /* !___aligned_offset_recalloc_dbg_defined */
#ifndef ___aligned_free_dbg_defined
#define ___aligned_free_dbg_defined 1
#ifdef __CRT_HAVE__aligned_free_dbg
__CDECLARE_VOID(,__NOTHROW_NCX,_aligned_free_dbg,(void *__ptr),(__ptr))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE__aligned_free)
#include <local/crtdbg/_aligned_free_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_free_dbg, __FORCELOCAL void __NOTHROW_NCX(__LIBCCALL _aligned_free_dbg)(void *__ptr) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_free_dbg))(__ptr); })
#else /* CUSTOM: _aligned_free_dbg */
#undef ___aligned_free_dbg_defined
#endif /* _aligned_free_dbg... */
#endif /* !___aligned_free_dbg_defined */
#ifndef ___strdup_dbg_defined
#define ___strdup_dbg_defined 1
#ifdef __CRT_HAVE__strdup_dbg
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,_strdup_dbg,(char const *__string, int __block_type, char const *__filename, int __line),(__string,__block_type,__filename,__line))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_strdup) || defined(__CRT_HAVE__strdup) || defined(__CRT_HAVE___strdup)
#include <local/crtdbg/_strdup_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strdup_dbg, __FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL _strdup_dbg)(char const *__string, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strdup_dbg))(__string, __block_type, __filename, __line); })
#else /* CUSTOM: _strdup_dbg */
#undef ___strdup_dbg_defined
#endif /* _strdup_dbg... */
#endif /* !___strdup_dbg_defined */
#ifndef ___wcsdup_dbg_defined
#define ___wcsdup_dbg_defined 1
#ifdef __CRT_HAVE__wcsdup_dbg
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,__WCHAR16_TYPE__ *,__NOTHROW_NCX,_wcsdup_dbg,(__WCHAR16_TYPE__ const *__string, int __block_type, char const *__filename, int __line),(__string,__block_type,__filename,__line))
#elif (defined(__CRT_HAVE_wcsdup) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_c16dup) || (defined(__CRT_HAVE__wcsdup) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$_wcsdup) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#include <local/crtdbg/_wcsdup_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsdup_dbg, __FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBCCALL _wcsdup_dbg)(__WCHAR16_TYPE__ const *__string, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsdup_dbg))(__string, __block_type, __filename, __line); })
#else /* CUSTOM: _wcsdup_dbg */
#undef ___wcsdup_dbg_defined
#endif /* _wcsdup_dbg... */
#endif /* !___wcsdup_dbg_defined */
#ifndef ___tempnam_dbg_defined
#define ___tempnam_dbg_defined 1
#ifdef __CRT_HAVE__tempnam_dbg
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,_tempnam_dbg,(char const *__dir_name, char const *__file_prefix, int __block_type, char const *__filename, int __line),(__dir_name,__file_prefix,__block_type,__filename,__line))
#elif defined(__CRT_HAVE_tempnam) || defined(__CRT_HAVE__tempnam)
#include <local/crtdbg/_tempnam_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_tempnam_dbg, __FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL _tempnam_dbg)(char const *__dir_name, char const *__file_prefix, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_tempnam_dbg))(__dir_name, __file_prefix, __block_type, __filename, __line); })
#else /* CUSTOM: _tempnam_dbg */
#undef ___tempnam_dbg_defined
#endif /* _tempnam_dbg... */
#endif /* !___tempnam_dbg_defined */
#ifndef ___wtempnam_dbg_defined
#define ___wtempnam_dbg_defined 1
#ifdef __CRT_HAVE__wtempnam_dbg
__CDECLARE(__ATTR_WUNUSED,__WCHAR16_TYPE__ *,__NOTHROW_NCX,_wtempnam_dbg,(__WCHAR16_TYPE__ const *__dir_name, __WCHAR16_TYPE__ const *__file_prefix, int __block_type, char const *__filename, int __line),(__dir_name,__file_prefix,__block_type,__filename,__line))
#else /* LIBC: _wtempnam_dbg */
#include <local/crtdbg/_wtempnam_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtempnam_dbg, __FORCELOCAL __ATTR_WUNUSED __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBCCALL _wtempnam_dbg)(__WCHAR16_TYPE__ const *__dir_name, __WCHAR16_TYPE__ const *__file_prefix, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtempnam_dbg))(__dir_name, __file_prefix, __block_type, __filename, __line); })
#endif /* _wtempnam_dbg... */
#endif /* !___wtempnam_dbg_defined */
#ifndef ___fullpath_dbg_defined
#define ___fullpath_dbg_defined 1
#ifdef __CRT_HAVE__fullpath_dbg
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),char *,__NOTHROW_NCX,_fullpath_dbg,(char *__full_path, char const *__path, __SIZE_TYPE__ __bufsize, int __block_type, char const *__filename, int __line),(__full_path,__path,__bufsize,__block_type,__filename,__line))
#elif defined(__CRT_HAVE__fullpath)
#include <local/crtdbg/_fullpath_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_fullpath_dbg, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL _fullpath_dbg)(char *__full_path, char const *__path, __SIZE_TYPE__ __bufsize, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fullpath_dbg))(__full_path, __path, __bufsize, __block_type, __filename, __line); })
#else /* CUSTOM: _fullpath_dbg */
#undef ___fullpath_dbg_defined
#endif /* _fullpath_dbg... */
#endif /* !___fullpath_dbg_defined */
#ifndef ___wfullpath_dbg_defined
#define ___wfullpath_dbg_defined 1
#ifdef __CRT_HAVE__wfullpath_dbg
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),__WCHAR16_TYPE__ *,__NOTHROW_NCX,_wfullpath_dbg,(__WCHAR16_TYPE__ *__full_path, __WCHAR16_TYPE__ const *__path, __SIZE_TYPE__ __buflen, int __block_type, char const *__filename, int __line),(__full_path,__path,__buflen,__block_type,__filename,__line))
#else /* LIBC: _wfullpath_dbg */
#include <local/crtdbg/_wfullpath_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wfullpath_dbg, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBCCALL _wfullpath_dbg)(__WCHAR16_TYPE__ *__full_path, __WCHAR16_TYPE__ const *__path, __SIZE_TYPE__ __buflen, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wfullpath_dbg))(__full_path, __path, __buflen, __block_type, __filename, __line); })
#endif /* _wfullpath_dbg... */
#endif /* !___wfullpath_dbg_defined */
#ifndef ___getcwd_dbg_defined
#define ___getcwd_dbg_defined 1
#ifdef __CRT_HAVE__getcwd_dbg
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_NCX,_getcwd_dbg,(char *__buf, __STDC_INT_AS_SIZE_T __bufsize, int __block_type, char const *__filename, int __line),(__buf,__bufsize,__block_type,__filename,__line))
#elif defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)
#include <local/crtdbg/_getcwd_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_getcwd_dbg, __FORCELOCAL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL _getcwd_dbg)(char *__buf, __STDC_INT_AS_SIZE_T __bufsize, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_getcwd_dbg))(__buf, __bufsize, __block_type, __filename, __line); })
#else /* CUSTOM: _getcwd_dbg */
#undef ___getcwd_dbg_defined
#endif /* _getcwd_dbg... */
#endif /* !___getcwd_dbg_defined */
#ifndef ___wgetcwd_dbg_defined
#define ___wgetcwd_dbg_defined 1
#ifdef __CRT_HAVE__wgetcwd_dbg
__CDECLARE(__ATTR_WUNUSED,__WCHAR16_TYPE__ *,__NOTHROW_NCX,_wgetcwd_dbg,(__WCHAR16_TYPE__ *__buf, __STDC_INT_AS_SIZE_T __buflen, int __block_type, char const *__filename, int __line),(__buf,__buflen,__block_type,__filename,__line))
#elif defined(__CRT_HAVE_c16getcwd) || defined(__CRT_HAVE_DOS$_wgetcwd) || defined(__CRT_HAVE_wgetcwd) || defined(__CRT_HAVE__wgetcwd)
#include <local/crtdbg/_wgetcwd_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wgetcwd_dbg, __FORCELOCAL __ATTR_WUNUSED __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBCCALL _wgetcwd_dbg)(__WCHAR16_TYPE__ *__buf, __STDC_INT_AS_SIZE_T __buflen, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wgetcwd_dbg))(__buf, __buflen, __block_type, __filename, __line); })
#else /* CUSTOM: _wgetcwd_dbg */
#undef ___wgetcwd_dbg_defined
#endif /* _wgetcwd_dbg... */
#endif /* !___wgetcwd_dbg_defined */
#ifndef ___getdcwd_dbg_defined
#define ___getdcwd_dbg_defined 1
#ifdef __CRT_HAVE__getdcwd_dbg
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_NCX,_getdcwd_dbg,(int __driveno, char *__buf, __STDC_INT_AS_SIZE_T __bufsize, int __block_type, char const *__filename, int __line),(__driveno,__buf,__bufsize,__block_type,__filename,__line))
#elif defined(__CRT_HAVE__getdcwd)
#include <local/crtdbg/_getdcwd_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_getdcwd_dbg, __FORCELOCAL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL _getdcwd_dbg)(int __driveno, char *__buf, __STDC_INT_AS_SIZE_T __bufsize, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_getdcwd_dbg))(__driveno, __buf, __bufsize, __block_type, __filename, __line); })
#else /* CUSTOM: _getdcwd_dbg */
#undef ___getdcwd_dbg_defined
#endif /* _getdcwd_dbg... */
#endif /* !___getdcwd_dbg_defined */
#ifndef ___wgetdcwd_dbg_defined
#define ___wgetdcwd_dbg_defined 1
#ifdef __CRT_HAVE__wgetdcwd_dbg
__CDECLARE(__ATTR_WUNUSED,__WCHAR16_TYPE__ *,__NOTHROW_NCX,_wgetdcwd_dbg,(int __driveno, __WCHAR16_TYPE__ *__buf, __STDC_INT_AS_SIZE_T __buflen, int __block_type, char const *__filename, int __line),(__driveno,__buf,__buflen,__block_type,__filename,__line))
#else /* LIBC: _wgetdcwd_dbg */
#include <local/crtdbg/_wgetdcwd_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wgetdcwd_dbg, __FORCELOCAL __ATTR_WUNUSED __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBCCALL _wgetdcwd_dbg)(int __driveno, __WCHAR16_TYPE__ *__buf, __STDC_INT_AS_SIZE_T __buflen, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wgetdcwd_dbg))(__driveno, __buf, __buflen, __block_type, __filename, __line); })
#endif /* _wgetdcwd_dbg... */
#endif /* !___wgetdcwd_dbg_defined */
#ifndef ___getdcwd_lk_dbg_defined
#define ___getdcwd_lk_dbg_defined 1
#ifdef __CRT_HAVE__getdcwd_lk_dbg
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_NCX,_getdcwd_lk_dbg,(int __driveno, char *__buf, __STDC_INT_AS_SIZE_T __bufsize, int __block_type, char const *__filename, int __line),(__driveno,__buf,__bufsize,__block_type,__filename,__line))
#elif defined(__CRT_HAVE__getdcwd_dbg)
__CREDIRECT(__ATTR_WUNUSED,char *,__NOTHROW_NCX,_getdcwd_lk_dbg,(int __driveno, char *__buf, __STDC_INT_AS_SIZE_T __bufsize, int __block_type, char const *__filename, int __line),_getdcwd_dbg,(__driveno,__buf,__bufsize,__block_type,__filename,__line))
#elif defined(__CRT_HAVE__getdcwd)
#include <local/crtdbg/_getdcwd_dbg.h>
__FORCELOCAL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL _getdcwd_lk_dbg)(int __driveno, char *__buf, __STDC_INT_AS_SIZE_T __bufsize, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_getdcwd_dbg))(__driveno, __buf, __bufsize, __block_type, __filename, __line); }
#else /* CUSTOM: _getdcwd_dbg */
#undef ___getdcwd_lk_dbg_defined
#endif /* _getdcwd_lk_dbg... */
#endif /* !___getdcwd_lk_dbg_defined */
#ifndef ___wgetdcwd_lk_dbg_defined
#define ___wgetdcwd_lk_dbg_defined 1
#ifdef __CRT_HAVE__wgetdcwd_lk_dbg
__CDECLARE(__ATTR_WUNUSED,__WCHAR16_TYPE__ *,__NOTHROW_NCX,_wgetdcwd_lk_dbg,(int __driveno, __WCHAR16_TYPE__ *__buf, __STDC_INT_AS_SIZE_T __buflen, int __block_type, char const *__filename, int __line),(__driveno,__buf,__buflen,__block_type,__filename,__line))
#elif defined(__CRT_HAVE__wgetdcwd_dbg)
__CREDIRECT(__ATTR_WUNUSED,__WCHAR16_TYPE__ *,__NOTHROW_NCX,_wgetdcwd_lk_dbg,(int __driveno, __WCHAR16_TYPE__ *__buf, __STDC_INT_AS_SIZE_T __buflen, int __block_type, char const *__filename, int __line),_wgetdcwd_dbg,(__driveno,__buf,__buflen,__block_type,__filename,__line))
#else /* LIBC: _wgetdcwd_dbg */
#include <local/crtdbg/_wgetdcwd_dbg.h>
__FORCELOCAL __ATTR_WUNUSED __WCHAR16_TYPE__ *__NOTHROW_NCX(__LIBCCALL _wgetdcwd_lk_dbg)(int __driveno, __WCHAR16_TYPE__ *__buf, __STDC_INT_AS_SIZE_T __buflen, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wgetdcwd_dbg))(__driveno, __buf, __buflen, __block_type, __filename, __line); }
#endif /* _wgetdcwd_lk_dbg... */
#endif /* !___wgetdcwd_lk_dbg_defined */
#ifndef ___dupenv_s_dbg_defined
#define ___dupenv_s_dbg_defined 1
#ifdef __CRT_HAVE__dupenv_s_dbg
__CDECLARE(_Check_return_wat_ __ATTR_NONNULL((3)),__errno_t,__NOTHROW_NCX,_dupenv_s_dbg,(char **__pbuf, __SIZE_TYPE__ *__pbufsize, char const *__varname, int __block_type, char const *__filename, int __line),(__pbuf,__pbufsize,__varname,__block_type,__filename,__line))
#elif defined(__CRT_HAVE__dupenv_s)
#include <local/crtdbg/_dupenv_s_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_dupenv_s_dbg, __FORCELOCAL _Check_return_wat_ __ATTR_NONNULL((3)) __errno_t __NOTHROW_NCX(__LIBCCALL _dupenv_s_dbg)(char **__pbuf, __SIZE_TYPE__ *__pbufsize, char const *__varname, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_dupenv_s_dbg))(__pbuf, __pbufsize, __varname, __block_type, __filename, __line); })
#else /* CUSTOM: _dupenv_s_dbg */
#undef ___dupenv_s_dbg_defined
#endif /* _dupenv_s_dbg... */
#endif /* !___dupenv_s_dbg_defined */
#ifndef ___wdupenv_s_dbg_defined
#define ___wdupenv_s_dbg_defined 1
#ifdef __CRT_HAVE__wdupenv_s_dbg
__CDECLARE(_Check_return_wat_ __ATTR_NONNULL((3)),__errno_t,__NOTHROW_NCX,_wdupenv_s_dbg,(__WCHAR16_TYPE__ **__pbuf, __SIZE_TYPE__ *__pbuflen, __WCHAR16_TYPE__ const *__varname, int __block_type, char const *__filename, int __line),(__pbuf,__pbuflen,__varname,__block_type,__filename,__line))
#else /* LIBC: _wdupenv_s_dbg */
#include <local/crtdbg/_wdupenv_s_dbg.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wdupenv_s_dbg, __FORCELOCAL _Check_return_wat_ __ATTR_NONNULL((3)) __errno_t __NOTHROW_NCX(__LIBCCALL _wdupenv_s_dbg)(__WCHAR16_TYPE__ **__pbuf, __SIZE_TYPE__ *__pbuflen, __WCHAR16_TYPE__ const *__varname, int __block_type, char const *__filename, int __line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wdupenv_s_dbg))(__pbuf, __pbuflen, __varname, __block_type, __filename, __line); })
#endif /* _wdupenv_s_dbg... */
#endif /* !___wdupenv_s_dbg_defined */
#ifdef __CRT_HAVE__CrtCheckMemory
__CDECLARE(,int,__NOTHROW_NCX,_CrtCheckMemory,(void),())
#else /* LIBC: _CrtCheckMemory */
#include <local/crtdbg/_CrtCheckMemory.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtCheckMemory, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL _CrtCheckMemory)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtCheckMemory))(); })
#endif /* _CrtCheckMemory... */
typedef void (__ATTR_CDECL *_PFNCRTDOFORALLCLIENTOBJECTS)(void *, void *);
#ifdef __CRT_HAVE__CrtDoForAllClientObjects
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_CrtDoForAllClientObjects,(_PFNCRTDOFORALLCLIENTOBJECTS __pfn, void *__context),(__pfn,__context))
#else /* LIBC: _CrtDoForAllClientObjects */
#include <local/crtdbg/_CrtDoForAllClientObjects.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtDoForAllClientObjects, __FORCELOCAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL _CrtDoForAllClientObjects)(_PFNCRTDOFORALLCLIENTOBJECTS __pfn, void *__context) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtDoForAllClientObjects))(__pfn, __context); })
#endif /* _CrtDoForAllClientObjects... */
#ifdef __CRT_HAVE__CrtIsValidPointer
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_CrtIsValidPointer,(void const *__ptr, __STDC_UINT_AS_SIZE_T __num_bytes, int __writable),(__ptr,__num_bytes,__writable))
#else /* LIBC: _CrtIsValidPointer */
#include <local/crtdbg/_CrtIsValidPointer.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtIsValidPointer, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _CrtIsValidPointer)(void const *__ptr, __STDC_UINT_AS_SIZE_T __num_bytes, int __writable) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtIsValidPointer))(__ptr, __num_bytes, __writable); })
#endif /* _CrtIsValidPointer... */
#ifdef __CRT_HAVE__CrtIsValidHeapPointer
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_CrtIsValidHeapPointer,(void const *__heap_ptr),(__heap_ptr))
#else /* LIBC: _CrtIsValidHeapPointer */
#include <local/crtdbg/_CrtIsValidHeapPointer.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtIsValidHeapPointer, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _CrtIsValidHeapPointer)(void const *__heap_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtIsValidHeapPointer))(__heap_ptr); })
#endif /* _CrtIsValidHeapPointer... */
#ifdef __CRT_HAVE__CrtIsMemoryBlock
__CDECLARE(,int,__NOTHROW_NCX,_CrtIsMemoryBlock,(void const *__ptr, __STDC_UINT_AS_SIZE_T __num_bytes, __LONG32_TYPE__ *__prequest_number, char **__filename, int *__line),(__ptr,__num_bytes,__prequest_number,__filename,__line))
#else /* LIBC: _CrtIsMemoryBlock */
#include <local/crtdbg/_CrtIsMemoryBlock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtIsMemoryBlock, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL _CrtIsMemoryBlock)(void const *__ptr, __STDC_UINT_AS_SIZE_T __num_bytes, __LONG32_TYPE__ *__prequest_number, char **__filename, int *__line) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtIsMemoryBlock))(__ptr, __num_bytes, __prequest_number, __filename, __line); })
#endif /* _CrtIsMemoryBlock... */
#ifdef __CRT_HAVE__CrtReportBlockType
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_CrtReportBlockType,(void const *__ptr),(__ptr))
#else /* LIBC: _CrtReportBlockType */
#include <local/crtdbg/_CrtReportBlockType.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtReportBlockType, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _CrtReportBlockType)(void const *__ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtReportBlockType))(__ptr); })
#endif /* _CrtReportBlockType... */
#ifdef __CRT_HAVE__CrtMemCheckpoint
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_CrtMemCheckpoint,(/*out*/ _CrtMemState *__state),(__state))
#else /* LIBC: _CrtMemCheckpoint */
#include <local/crtdbg/_CrtMemCheckpoint.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtMemCheckpoint, __FORCELOCAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL _CrtMemCheckpoint)(/*out*/ _CrtMemState *__state) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtMemCheckpoint))(__state); })
#endif /* _CrtMemCheckpoint... */
#ifdef __CRT_HAVE__CrtMemDifference
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,_CrtMemDifference,(/*out*/ _CrtMemState *__state, _CrtMemState const *__old_state, _CrtMemState const *__new_state),(__state,__old_state,__new_state))
#else /* LIBC: _CrtMemDifference */
#include <local/crtdbg/_CrtMemDifference.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtMemDifference, __FORCELOCAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBCCALL _CrtMemDifference)(/*out*/ _CrtMemState *__state, _CrtMemState const *__old_state, _CrtMemState const *__new_state) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtMemDifference))(__state, __old_state, __new_state); })
#endif /* _CrtMemDifference... */
#ifdef __CRT_HAVE__CrtMemDumpAllObjectsSince
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_CrtMemDumpAllObjectsSince,(_CrtMemState const *__state),(__state))
#else /* LIBC: _CrtMemDumpAllObjectsSince */
#include <local/crtdbg/_CrtMemDumpAllObjectsSince.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtMemDumpAllObjectsSince, __FORCELOCAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL _CrtMemDumpAllObjectsSince)(_CrtMemState const *__state) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtMemDumpAllObjectsSince))(__state); })
#endif /* _CrtMemDumpAllObjectsSince... */
#ifdef __CRT_HAVE__CrtMemDumpStatistics
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_CrtMemDumpStatistics,(_CrtMemState const *__state),(__state))
#else /* LIBC: _CrtMemDumpStatistics */
#include <local/crtdbg/_CrtMemDumpStatistics.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtMemDumpStatistics, __FORCELOCAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL _CrtMemDumpStatistics)(_CrtMemState const *__state) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtMemDumpStatistics))(__state); })
#endif /* _CrtMemDumpStatistics... */
#ifdef __CRT_HAVE__CrtDumpMemoryLeaks
__CDECLARE(,int,__NOTHROW_NCX,_CrtDumpMemoryLeaks,(void),())
#else /* LIBC: _CrtDumpMemoryLeaks */
#include <local/crtdbg/_CrtDumpMemoryLeaks.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtDumpMemoryLeaks, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL _CrtDumpMemoryLeaks)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtDumpMemoryLeaks))(); })
#endif /* _CrtDumpMemoryLeaks... */
#ifdef __CRT_HAVE__CrtSetCheckCount
__CDECLARE(,int,__NOTHROW_NCX,_CrtSetCheckCount,(int __check_count),(__check_count))
#else /* LIBC: _CrtSetCheckCount */
#include <local/crtdbg/_CrtSetCheckCount.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtSetCheckCount, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL _CrtSetCheckCount)(int __check_count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtSetCheckCount))(__check_count); })
#endif /* _CrtSetCheckCount... */
#ifdef __CRT_HAVE__CrtGetCheckCount
__CDECLARE(__ATTR_PURE,int,__NOTHROW_NCX,_CrtGetCheckCount,(void),())
#else /* LIBC: _CrtGetCheckCount */
#include <local/crtdbg/_CrtGetCheckCount.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_CrtGetCheckCount, __FORCELOCAL __ATTR_PURE int __NOTHROW_NCX(__LIBCCALL _CrtGetCheckCount)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_CrtGetCheckCount))(); })
#endif /* _CrtGetCheckCount... */

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

#endif /* !_CRTDBG_H */
