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

#if __has_include(<intrin.h>)
#include <intrin.h>
#endif /* __has_include(<intrin.h>) */

DECL_BEGIN

/*[[[head:libc___p__crtAssertBusy,hash:CRC-32=0x6476d96d]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.debug_malloc") __LONG32_TYPE__ *
NOTHROW_NCX(LIBDCALL libc___p__crtAssertBusy)(void)
/*[[[body:libc___p__crtAssertBusy]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("__p__crtAssertBusy"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___p__crtAssertBusy]]]*/

/*[[[head:libc___p__crtBreakAlloc,hash:CRC-32=0xc4e93b64]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.debug_malloc") __LONG32_TYPE__ *
NOTHROW_NCX(LIBDCALL libc___p__crtBreakAlloc)(void)
/*[[[body:libc___p__crtBreakAlloc]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("__p__crtBreakAlloc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___p__crtBreakAlloc]]]*/

/*[[[head:libc___p__crtDbgFlag,hash:CRC-32=0x6a8e593b]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.debug_malloc") int *
NOTHROW_NCX(LIBDCALL libc___p__crtDbgFlag)(void)
/*[[[body:libc___p__crtDbgFlag]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("__p__crtDbgFlag"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___p__crtDbgFlag]]]*/

/*[[[head:libc__CrtGetReportHook,hash:CRC-32=0xf27e3ac]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.debug_malloc") _CRT_REPORT_HOOK
NOTHROW_NCX(LIBDCALL libc__CrtGetReportHook)(void)
/*[[[body:libc__CrtGetReportHook]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_CrtGetReportHook"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__CrtGetReportHook]]]*/

/*[[[head:libc__CrtSetReportHook,hash:CRC-32=0x458da49d]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.debug_malloc") _CRT_REPORT_HOOK
NOTHROW_NCX(LIBDCALL libc__CrtSetReportHook)(_CRT_REPORT_HOOK pfn_new_hook)
/*[[[body:libc__CrtSetReportHook]]]*/
/*AUTO*/{
	(void)pfn_new_hook;
	CRT_UNIMPLEMENTED("_CrtSetReportHook"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__CrtSetReportHook]]]*/

/*[[[head:libc__CrtSetReportHook2,hash:CRC-32=0x19f6974a]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.debug_malloc") int
NOTHROW_NCX(LIBDCALL libc__CrtSetReportHook2)(int mode,
                                              _CRT_REPORT_HOOK pfn_new_hook)
/*[[[body:libc__CrtSetReportHook2]]]*/
/*AUTO*/{
	(void)mode;
	(void)pfn_new_hook;
	CRT_UNIMPLEMENTED("_CrtSetReportHook2"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__CrtSetReportHook2]]]*/

/*[[[head:libc__CrtSetReportHookW2,hash:CRC-32=0x880fc32a]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.debug_malloc") int
NOTHROW_NCX(LIBDCALL libc__CrtSetReportHookW2)(int mode,
                                               _CRT_REPORT_HOOKW pfn_new_hook)
/*[[[body:libc__CrtSetReportHookW2]]]*/
/*AUTO*/{
	(void)mode;
	(void)pfn_new_hook;
	CRT_UNIMPLEMENTED("_CrtSetReportHookW2"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__CrtSetReportHookW2]]]*/

/*[[[head:libc__CrtGetAllocHook,hash:CRC-32=0xed82ccda]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.debug_malloc") _CRT_ALLOC_HOOK
NOTHROW_NCX(LIBDCALL libc__CrtGetAllocHook)(void)
/*[[[body:libc__CrtGetAllocHook]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_CrtGetAllocHook"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__CrtGetAllocHook]]]*/

/*[[[head:libc__CrtSetAllocHook,hash:CRC-32=0x444e1954]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.debug_malloc") _CRT_ALLOC_HOOK
NOTHROW_NCX(LIBDCALL libc__CrtSetAllocHook)(_CRT_ALLOC_HOOK pfn_new_hook)
/*[[[body:libc__CrtSetAllocHook]]]*/
/*AUTO*/{
	(void)pfn_new_hook;
	CRT_UNIMPLEMENTED("_CrtSetAllocHook"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__CrtSetAllocHook]]]*/

/*[[[head:libc__CrtGetDumpClient,hash:CRC-32=0xa8c08c1]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.debug_malloc") _CRT_DUMP_CLIENT
NOTHROW_NCX(LIBDCALL libc__CrtGetDumpClient)(void)
/*[[[body:libc__CrtGetDumpClient]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_CrtGetDumpClient"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__CrtGetDumpClient]]]*/

/*[[[head:libc__CrtSetDumpClient,hash:CRC-32=0xba59149b]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.debug_malloc") _CRT_DUMP_CLIENT
NOTHROW_NCX(LIBDCALL libc__CrtSetDumpClient)(_CRT_DUMP_CLIENT pfn_new_dump)
/*[[[body:libc__CrtSetDumpClient]]]*/
/*AUTO*/{
	(void)pfn_new_dump;
	CRT_UNIMPLEMENTED("_CrtSetDumpClient"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__CrtSetDumpClient]]]*/

/*[[[head:libc__CrtSetReportMode,hash:CRC-32=0xe2d9f783]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.debug_malloc") int
NOTHROW_NCX(LIBDCALL libc__CrtSetReportMode)(int report_type,
                                             int report_mode)
/*[[[body:libc__CrtSetReportMode]]]*/
/*AUTO*/{
	(void)report_type;
	(void)report_mode;
	CRT_UNIMPLEMENTEDF("_CrtSetReportMode(%x, %x)", report_type, report_mode); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__CrtSetReportMode]]]*/

/*[[[head:libc__CrtSetReportFile,hash:CRC-32=0x20feabcd]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.debug_malloc") _HFILE
NOTHROW_NCX(LIBDCALL libc__CrtSetReportFile)(int report_type,
                                             _HFILE report_file)
/*[[[body:libc__CrtSetReportFile]]]*/
/*AUTO*/{
	(void)report_type;
	(void)report_file;
	CRT_UNIMPLEMENTEDF("_CrtSetReportFile(%x, %p)", report_type, report_file); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__CrtSetReportFile]]]*/

/*[[[head:libc__CrtDbgReport,hash:CRC-32=0xd42ec690]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.debug_malloc") int
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
	CRT_UNIMPLEMENTEDF("_CrtDbgReport(%x, %q, %x, %q, %q, ...)", report_type, filename, line, module_name, format); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__CrtDbgReport]]]*/


/*[[[head:libc__CrtSetDebugFillThreshold,hash:CRC-32=0x3a4eecaf]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.debug_malloc") size_t
NOTHROW_NCX(LIBDCALL libc__CrtSetDebugFillThreshold)(size_t new_debug_fill_threshold)
/*[[[body:libc__CrtSetDebugFillThreshold]]]*/
/*AUTO*/{
	(void)new_debug_fill_threshold;
	CRT_UNIMPLEMENTEDF("_CrtSetDebugFillThreshold(%Ix)", new_debug_fill_threshold); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__CrtSetDebugFillThreshold]]]*/


/*[[[head:libc__CrtDbgReportW,hash:CRC-32=0xfd19dbd4]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.debug_malloc") int
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
	CRT_UNIMPLEMENTEDF("_CrtDbgReportW(%x, %p, %x, %p, %p, ...)", report_type, filename, line, module_name, format); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__CrtDbgReportW]]]*/

/*[[[head:libc__CrtDbgBreak,hash:CRC-32=0xd43487a0]]]*/
#ifndef LIBC_ARCH_HAVE_CRTDBGBREAK
INTERN ATTR_SECTION(".text.crt.dos.utility") void
NOTHROW_NCX(LIBDCALL libc__CrtDbgBreak)(void)
/*[[[body:libc__CrtDbgBreak]]]*/
{
#ifdef __debugbreak
	__debugbreak();
#endif /* __debugbreak */
}
#endif /* MAGIC:impl_if */
/*[[[end:libc__CrtDbgBreak]]]*/

/*[[[head:libc__CrtSetBreakAlloc,hash:CRC-32=0xe82fa55e]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.debug_malloc") __LONG32_TYPE__
NOTHROW_NCX(LIBDCALL libc__CrtSetBreakAlloc)(__LONG32_TYPE__ break_alloc)
/*[[[body:libc__CrtSetBreakAlloc]]]*/
/*AUTO*/{
	(void)break_alloc;
	CRT_UNIMPLEMENTEDF("_CrtSetBreakAlloc(%" PRIx32 ")", break_alloc); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__CrtSetBreakAlloc]]]*/



/*[[[start:exports,hash:CRC-32=0xe4f493c4]]]*/
DEFINE_PUBLIC_ALIAS(__p__crtAssertBusy, libc___p__crtAssertBusy);
DEFINE_PUBLIC_ALIAS(__p__crtBreakAlloc, libc___p__crtBreakAlloc);
DEFINE_PUBLIC_ALIAS(__p__crtDbgFlag, libc___p__crtDbgFlag);
DEFINE_PUBLIC_ALIAS(_CrtGetReportHook, libc__CrtGetReportHook);
DEFINE_PUBLIC_ALIAS(_CrtSetReportHook, libc__CrtSetReportHook);
DEFINE_PUBLIC_ALIAS(_CrtSetReportHook2, libc__CrtSetReportHook2);
DEFINE_PUBLIC_ALIAS(_CrtSetReportHookW2, libc__CrtSetReportHookW2);
DEFINE_PUBLIC_ALIAS(_CrtGetAllocHook, libc__CrtGetAllocHook);
DEFINE_PUBLIC_ALIAS(_CrtSetAllocHook, libc__CrtSetAllocHook);
DEFINE_PUBLIC_ALIAS(_CrtGetDumpClient, libc__CrtGetDumpClient);
DEFINE_PUBLIC_ALIAS(_CrtSetDumpClient, libc__CrtSetDumpClient);
DEFINE_PUBLIC_ALIAS(_CrtSetReportMode, libc__CrtSetReportMode);
DEFINE_PUBLIC_ALIAS(_CrtSetReportFile, libc__CrtSetReportFile);
DEFINE_PUBLIC_ALIAS(_CrtSetDebugFillThreshold, libc__CrtSetDebugFillThreshold);
DEFINE_PUBLIC_ALIAS(_CrtDbgReport, libc__CrtDbgReport);
DEFINE_PUBLIC_ALIAS("?_CrtDbgReportW@@YAHHPBGH00ZZ", libc__CrtDbgReportW);
DEFINE_PUBLIC_ALIAS(_CrtDbgReportW, libc__CrtDbgReportW);
#ifndef LIBC_ARCH_HAVE_CRTDBGBREAK
DEFINE_PUBLIC_ALIAS(_CrtDbgBreak, libc__CrtDbgBreak);
#endif /* !LIBC_ARCH_HAVE_CRTDBGBREAK */
DEFINE_PUBLIC_ALIAS(_CrtSetBreakAlloc, libc__CrtSetBreakAlloc);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_CRTDBG_C */
