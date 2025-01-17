/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_CRTDBG_C
#define GUARD_LIBC_USER_CRTDBG_C 1

#include "../api.h"
/**/

#include "crtdbg.h"

#if __has_include(<intrin.h>)
#include <intrin.h>
#endif /* __has_include(<intrin.h>) */

DECL_BEGIN

/*[[[head:libc___p__crtAssertBusy,hash:CRC-32=0xad795aeb]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") __LONG32_TYPE__ *
NOTHROW_NCX(LIBDCALL libc___p__crtAssertBusy)(void)
/*[[[body:libc___p__crtAssertBusy]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("__p__crtAssertBusy"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___p__crtAssertBusy]]]*/

/*[[[head:libc___p__crtBreakAlloc,hash:CRC-32=0xde6b8e2]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") __LONG32_TYPE__ *
NOTHROW_NCX(LIBDCALL libc___p__crtBreakAlloc)(void)
/*[[[body:libc___p__crtBreakAlloc]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("__p__crtBreakAlloc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___p__crtBreakAlloc]]]*/

/*[[[head:libc___p__crtDbgFlag,hash:CRC-32=0xc52fee7f]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") int *
NOTHROW_NCX(LIBDCALL libc___p__crtDbgFlag)(void)
/*[[[body:libc___p__crtDbgFlag]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("__p__crtDbgFlag"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___p__crtDbgFlag]]]*/

/*[[[head:libc__CrtGetReportHook,hash:CRC-32=0x1ac59c2e]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") _CRT_REPORT_HOOK
NOTHROW_NCX(LIBDCALL libc__CrtGetReportHook)(void)
/*[[[body:libc__CrtGetReportHook]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_CrtGetReportHook"); /* TODO */
	return (_CRT_REPORT_HOOK)libc_seterrno(ENOSYS);
}
/*[[[end:libc__CrtGetReportHook]]]*/

/*[[[head:libc__CrtSetReportHook,hash:CRC-32=0x3fe68ae8]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") _CRT_REPORT_HOOK
NOTHROW_NCX(LIBDCALL libc__CrtSetReportHook)(_CRT_REPORT_HOOK pfn_new_hook)
/*[[[body:libc__CrtSetReportHook]]]*/
/*AUTO*/{
	(void)pfn_new_hook;
	CRT_UNIMPLEMENTED("_CrtSetReportHook"); /* TODO */
	return (_CRT_REPORT_HOOK)libc_seterrno(ENOSYS);
}
/*[[[end:libc__CrtSetReportHook]]]*/

/*[[[head:libc__CrtSetReportHook2,hash:CRC-32=0x2a5d4001]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") int
NOTHROW_NCX(LIBDCALL libc__CrtSetReportHook2)(int mode,
                                              _CRT_REPORT_HOOK pfn_new_hook)
/*[[[body:libc__CrtSetReportHook2]]]*/
/*AUTO*/{
	(void)mode;
	(void)pfn_new_hook;
	CRT_UNIMPLEMENTED("_CrtSetReportHook2"); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc__CrtSetReportHook2]]]*/

/*[[[head:libc__CrtSetReportHookW2,hash:CRC-32=0x7bbd8880]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") int
NOTHROW_NCX(LIBDCALL libc__CrtSetReportHookW2)(int mode,
                                               _CRT_REPORT_HOOKW pfn_new_hook)
/*[[[body:libc__CrtSetReportHookW2]]]*/
/*AUTO*/{
	(void)mode;
	(void)pfn_new_hook;
	CRT_UNIMPLEMENTED("_CrtSetReportHookW2"); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc__CrtSetReportHookW2]]]*/

/*[[[head:libc__CrtGetAllocHook,hash:CRC-32=0x678b5578]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") _CRT_ALLOC_HOOK
NOTHROW_NCX(LIBDCALL libc__CrtGetAllocHook)(void)
/*[[[body:libc__CrtGetAllocHook]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_CrtGetAllocHook"); /* TODO */
	return (_CRT_ALLOC_HOOK)libc_seterrno(ENOSYS);
}
/*[[[end:libc__CrtGetAllocHook]]]*/

/*[[[head:libc__CrtSetAllocHook,hash:CRC-32=0xe2d814fd]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") _CRT_ALLOC_HOOK
NOTHROW_NCX(LIBDCALL libc__CrtSetAllocHook)(_CRT_ALLOC_HOOK pfn_new_hook)
/*[[[body:libc__CrtSetAllocHook]]]*/
/*AUTO*/{
	(void)pfn_new_hook;
	CRT_UNIMPLEMENTED("_CrtSetAllocHook"); /* TODO */
	return (_CRT_ALLOC_HOOK)libc_seterrno(ENOSYS);
}
/*[[[end:libc__CrtSetAllocHook]]]*/

/*[[[head:libc__CrtGetDumpClient,hash:CRC-32=0x1f6e7743]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") _CRT_DUMP_CLIENT
NOTHROW_NCX(LIBDCALL libc__CrtGetDumpClient)(void)
/*[[[body:libc__CrtGetDumpClient]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_CrtGetDumpClient"); /* TODO */
	return (_CRT_DUMP_CLIENT)libc_seterrno(ENOSYS);
}
/*[[[end:libc__CrtGetDumpClient]]]*/

/*[[[head:libc__CrtSetDumpClient,hash:CRC-32=0xc0323aee]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") _CRT_DUMP_CLIENT
NOTHROW_NCX(LIBDCALL libc__CrtSetDumpClient)(_CRT_DUMP_CLIENT pfn_new_dump)
/*[[[body:libc__CrtSetDumpClient]]]*/
/*AUTO*/{
	(void)pfn_new_dump;
	CRT_UNIMPLEMENTED("_CrtSetDumpClient"); /* TODO */
	return (_CRT_DUMP_CLIENT)libc_seterrno(ENOSYS);
}
/*[[[end:libc__CrtSetDumpClient]]]*/

/*[[[head:libc__CrtSetReportMode,hash:CRC-32=0xf9cd3027]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") int
NOTHROW_NCX(LIBDCALL libc__CrtSetReportMode)(int report_type,
                                             int report_mode)
/*[[[body:libc__CrtSetReportMode]]]*/
/*AUTO*/{
	(void)report_type;
	(void)report_mode;
	CRT_UNIMPLEMENTEDF("_CrtSetReportMode(report_type: %x, report_mode: %x)", report_type, report_mode); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc__CrtSetReportMode]]]*/

/*[[[head:libc__CrtSetReportFile,hash:CRC-32=0x364e40a7]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") _HFILE
NOTHROW_NCX(LIBDCALL libc__CrtSetReportFile)(int report_type,
                                             _HFILE report_file)
/*[[[body:libc__CrtSetReportFile]]]*/
/*AUTO*/{
	(void)report_type;
	(void)report_file;
	CRT_UNIMPLEMENTEDF("_CrtSetReportFile(report_type: %x, report_file: %p)", report_type, report_file); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__CrtSetReportFile]]]*/

/*[[[head:libc__CrtDbgReport,hash:CRC-32=0xa2fa3cc0]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") int
NOTHROW_NCX(VLIBDCALL libc__CrtDbgReport)(int report_type,
                                          char const *filename,
                                          int line,
                                          char const *module_name,
                                          char const *format,
                                          ...)
/*[[[body:libc__CrtDbgReport]]]*/
/*AUTO*/{
	(void)report_type;
	(void)filename;
	(void)line;
	(void)module_name;
	(void)format;
	CRT_UNIMPLEMENTEDF("_CrtDbgReport(report_type: %x, filename: %q, line: %x, module_name: %q, format: %q, ...)", report_type, filename, line, module_name, format); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc__CrtDbgReport]]]*/


/*[[[head:libc__CrtSetDebugFillThreshold,hash:CRC-32=0x4025c2da]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") size_t
NOTHROW_NCX(LIBDCALL libc__CrtSetDebugFillThreshold)(size_t new_debug_fill_threshold)
/*[[[body:libc__CrtSetDebugFillThreshold]]]*/
/*AUTO*/{
	(void)new_debug_fill_threshold;
	CRT_UNIMPLEMENTEDF("_CrtSetDebugFillThreshold(new_debug_fill_threshold: %Ix)", new_debug_fill_threshold); /* TODO */
	return (size_t)libc_seterrno(ENOSYS);
}
/*[[[end:libc__CrtSetDebugFillThreshold]]]*/


/*[[[head:libc__CrtDbgReportW,hash:CRC-32=0xcceff7d]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") int
NOTHROW_NCX(VLIBDCALL libc__CrtDbgReportW)(int report_type,
                                           __WCHAR16_TYPE__ const *filename,
                                           int line,
                                           __WCHAR16_TYPE__ const *module_name,
                                           __WCHAR16_TYPE__ const *format,
                                           ...)
/*[[[body:libc__CrtDbgReportW]]]*/
/*AUTO*/{
	(void)report_type;
	(void)filename;
	(void)line;
	(void)module_name;
	(void)format;
	CRT_UNIMPLEMENTEDF("_CrtDbgReportW(report_type: %x, filename: %p, line: %x, module_name: %p, format: %p, ...)", report_type, filename, line, module_name, format); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc__CrtDbgReportW]]]*/

/*[[[head:libc__CrtDbgBreak,hash:CRC-32=0xb86394b7]]]*/
#ifndef LIBC_ARCH_HAVE_CRTDBGBREAK
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility") void
NOTHROW_NCX(LIBDCALL libc__CrtDbgBreak)(void)
/*[[[body:libc__CrtDbgBreak]]]*/
{
#ifdef __debugbreak
	__debugbreak();
#endif /* __debugbreak */
}
#endif /* MAGIC:impl_if */
/*[[[end:libc__CrtDbgBreak]]]*/

/*[[[head:libc__CrtSetBreakAlloc,hash:CRC-32=0x4eb9a8f7]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.debug_malloc") __LONG32_TYPE__
NOTHROW_NCX(LIBDCALL libc__CrtSetBreakAlloc)(__LONG32_TYPE__ break_alloc)
/*[[[body:libc__CrtSetBreakAlloc]]]*/
/*AUTO*/{
	(void)break_alloc;
	CRT_UNIMPLEMENTEDF("_CrtSetBreakAlloc(break_alloc: %" PRIx32 ")", break_alloc); /* TODO */
	return (__LONG32_TYPE__)libc_seterrno(ENOSYS);
}
/*[[[end:libc__CrtSetBreakAlloc]]]*/



/*[[[start:exports,hash:CRC-32=0x93acf27a]]]*/
DEFINE_PUBLIC_ALIAS_P(__p__crtAssertBusy,libc___p__crtAssertBusy,,__LONG32_TYPE__ *,NOTHROW_NCX,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__p__crtBreakAlloc,libc___p__crtBreakAlloc,,__LONG32_TYPE__ *,NOTHROW_NCX,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__p__crtDbgFlag,libc___p__crtDbgFlag,,int *,NOTHROW_NCX,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_CrtGetReportHook,libc__CrtGetReportHook,,_CRT_REPORT_HOOK,NOTHROW_NCX,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_CrtSetReportHook,libc__CrtSetReportHook,,_CRT_REPORT_HOOK,NOTHROW_NCX,LIBDCALL,(_CRT_REPORT_HOOK pfn_new_hook),(pfn_new_hook));
DEFINE_PUBLIC_ALIAS_P(_CrtSetReportHook2,libc__CrtSetReportHook2,,int,NOTHROW_NCX,LIBDCALL,(int mode, _CRT_REPORT_HOOK pfn_new_hook),(mode,pfn_new_hook));
DEFINE_PUBLIC_ALIAS_P(_CrtSetReportHookW2,libc__CrtSetReportHookW2,,int,NOTHROW_NCX,LIBDCALL,(int mode, _CRT_REPORT_HOOKW pfn_new_hook),(mode,pfn_new_hook));
DEFINE_PUBLIC_ALIAS_P(_CrtGetAllocHook,libc__CrtGetAllocHook,,_CRT_ALLOC_HOOK,NOTHROW_NCX,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_CrtSetAllocHook,libc__CrtSetAllocHook,,_CRT_ALLOC_HOOK,NOTHROW_NCX,LIBDCALL,(_CRT_ALLOC_HOOK pfn_new_hook),(pfn_new_hook));
DEFINE_PUBLIC_ALIAS_P(_CrtGetDumpClient,libc__CrtGetDumpClient,,_CRT_DUMP_CLIENT,NOTHROW_NCX,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(_CrtSetDumpClient,libc__CrtSetDumpClient,,_CRT_DUMP_CLIENT,NOTHROW_NCX,LIBDCALL,(_CRT_DUMP_CLIENT pfn_new_dump),(pfn_new_dump));
DEFINE_PUBLIC_ALIAS_P(_CrtSetReportMode,libc__CrtSetReportMode,,int,NOTHROW_NCX,LIBDCALL,(int report_type, int report_mode),(report_type,report_mode));
DEFINE_PUBLIC_ALIAS_P(_CrtSetReportFile,libc__CrtSetReportFile,,_HFILE,NOTHROW_NCX,LIBDCALL,(int report_type, _HFILE report_file),(report_type,report_file));
DEFINE_PUBLIC_ALIAS_P(_CrtSetDebugFillThreshold,libc__CrtSetDebugFillThreshold,,size_t,NOTHROW_NCX,LIBDCALL,(size_t new_debug_fill_threshold),(new_debug_fill_threshold));
DEFINE_PUBLIC_ALIAS_P(_CrtDbgReport,libc__CrtDbgReport,,int,NOTHROW_NCX,VLIBDCALL,(int report_type, char const *filename, int line, char const *module_name, char const *format, ...),(report_type,filename,line,module_name,format,));
DEFINE_PUBLIC_ALIAS_P("?_CrtDbgReportW@@YAHHPBGH00ZZ",libc__CrtDbgReportW,,int,NOTHROW_NCX,VLIBDCALL,(int report_type, __WCHAR16_TYPE__ const *filename, int line, __WCHAR16_TYPE__ const *module_name, __WCHAR16_TYPE__ const *format, ...),(report_type,filename,line,module_name,format,));
DEFINE_PUBLIC_ALIAS_P(_CrtDbgReportW,libc__CrtDbgReportW,,int,NOTHROW_NCX,VLIBDCALL,(int report_type, __WCHAR16_TYPE__ const *filename, int line, __WCHAR16_TYPE__ const *module_name, __WCHAR16_TYPE__ const *format, ...),(report_type,filename,line,module_name,format,));
#ifndef LIBC_ARCH_HAVE_CRTDBGBREAK
DEFINE_PUBLIC_ALIAS_P_VOID(_CrtDbgBreak,libc__CrtDbgBreak,,NOTHROW_NCX,LIBDCALL,(void),());
#endif /* !LIBC_ARCH_HAVE_CRTDBGBREAK */
DEFINE_PUBLIC_ALIAS_P(_CrtSetBreakAlloc,libc__CrtSetBreakAlloc,,__LONG32_TYPE__,NOTHROW_NCX,LIBDCALL,(__LONG32_TYPE__ break_alloc),(break_alloc));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_CRTDBG_C */
