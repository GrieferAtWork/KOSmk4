/* HASH CRC-32:0x541a62 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: OpenSolaris (/usr/src/head/siginfo.h) */
#ifndef _SIGINFO_H
#define _SIGINFO_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/os/siginfo.h>
#include <bits/types.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __siginfo_t_defined
#define __siginfo_t_defined
typedef struct __siginfo_struct siginfo_t;
#endif /* !__siginfo_t_defined */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("siginfolist")
#pragma push_macro("nsiginfo")
#pragma push_macro("vsiginfo")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef siginfolist
#undef nsiginfo
#undef vsiginfo

struct siginfolist {
	int    nsiginfo;
	char **vsiginfo;
};

/* For compatibility with OpenSolaris
 *
 * Note that on KOS, these same strings can (and should) instead be
 * accessed  through `sigcodedesc_np(3)', as declared in <signal.h>
 *
 * Portability notes:
 * >> _sys_siginfolist[signo-1].vsiginfo[code-1] == sigcodedesc_np(signo, code);
 * >> _sys_siginfolist[SIGILL-1].vsiginfo        == _sys_illlist;
 * >> _sys_siginfolist[SIGFPE-1].vsiginfo        == _sys_fpelist;
 * >> _sys_siginfolist[SIGSEGV-1].vsiginfo       == _sys_segvlist;
 * >> _sys_siginfolist[SIGBUS-1].vsiginfo        == _sys_buslist;
 * >> _sys_siginfolist[SIGTRAP-1].vsiginfo       == _sys_traplist;
 * >> _sys_siginfolist[SIGCLD-1].vsiginfo        == _sys_cldlist;
 * >> _sys_siginfolist[SIGPOLL-1].vsiginfo       == _sys_polllist;
 */

#ifndef _sys_illlist
#ifdef __CRT_HAVE__sys_illlist
extern char const *_sys_illlist[];
#define _sys_illlist _sys_illlist
#endif /* __CRT_HAVE__sys_illlist */
#endif /* !_sys_illlist */

#ifndef _sys_fpelist
#ifdef __CRT_HAVE__sys_fpelist
extern char const *_sys_fpelist[];
#define _sys_fpelist _sys_fpelist
#endif /* __CRT_HAVE__sys_fpelist */
#endif /* !_sys_fpelist */

#ifndef _sys_segvlist
#ifdef __CRT_HAVE__sys_segvlist
extern char const *_sys_segvlist[];
#define _sys_segvlist _sys_segvlist
#endif /* __CRT_HAVE__sys_segvlist */
#endif /* !_sys_segvlist */

#ifndef _sys_buslist
#ifdef __CRT_HAVE__sys_buslist
extern char const *_sys_buslist[];
#define _sys_buslist _sys_buslist
#endif /* __CRT_HAVE__sys_buslist */
#endif /* !_sys_buslist */

#ifndef _sys_traplist
#ifdef __CRT_HAVE__sys_traplist
extern char const *_sys_traplist[];
#define _sys_traplist _sys_traplist
#endif /* __CRT_HAVE__sys_traplist */
#endif /* !_sys_traplist */

#ifndef _sys_cldlist
#ifdef __CRT_HAVE__sys_cldlist
extern char const *_sys_cldlist[];
#define _sys_cldlist _sys_cldlist
#endif /* __CRT_HAVE__sys_cldlist */
#endif /* !_sys_cldlist */

#ifndef _sys_polllist
#ifdef __CRT_HAVE__sys_polllist
extern char const *_sys_polllist[];
#define _sys_polllist _sys_polllist
#endif /* __CRT_HAVE__sys_polllist */
#endif /* !_sys_polllist */

#ifndef _sys_siginfolistp
#ifdef __CRT_HAVE__sys_siginfolistp
extern struct siginfolist const *_sys_siginfolistp;
#define _sys_siginfolistp _sys_siginfolistp
#endif /* __CRT_HAVE__sys_siginfolistp */
#endif /* !_sys_siginfolistp */

#if !defined(_sys_siginfolist) && defined(_sys_siginfolistp)
#define _sys_siginfolist _sys_siginfolistp
#endif /* !_sys_siginfolist && _sys_siginfolistp */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("vsiginfo")
#pragma pop_macro("nsiginfo")
#pragma pop_macro("siginfolist")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#ifndef __psignal_defined
#define __psignal_defined
#ifdef __CRT_HAVE_psignal
/* >> psignal(3)
 * Same as `fprintf(stderr, "%s: %s\n", s, sigabbrev_np(signo) ? "SIG"+. : strdupf("Unknown signal %d", signo))'
 * When `s' is `NULL' or an empty string, omit the leading "%s: " from the format. */
__CDECLARE_VOID(,__NOTHROW_CB_NCX,psignal,(__signo_t __signo, char const *__s),(__signo,__s))
#else /* __CRT_HAVE_psignal */
#include <libc/template/stdstreams.h>
#if defined(__LOCAL_stderr) && (defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))
#include <libc/local/signal/psignal.h>
/* >> psignal(3)
 * Same as `fprintf(stderr, "%s: %s\n", s, sigabbrev_np(signo) ? "SIG"+. : strdupf("Unknown signal %d", signo))'
 * When `s' is `NULL' or an empty string, omit the leading "%s: " from the format. */
__NAMESPACE_LOCAL_USING_OR_IMPL(psignal, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_CB_NCX(__LIBCCALL psignal)(__signo_t __signo, char const *__s) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(psignal))(__signo, __s); })
#else /* __LOCAL_stderr && (__CRT_HAVE_fprintf_unlocked || __CRT_HAVE_fprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_HAVE_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE_fgetc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) */
#undef __psignal_defined
#endif /* !__LOCAL_stderr || (!__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && !__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) */
#endif /* !__CRT_HAVE_psignal */
#endif /* !__psignal_defined */
#ifndef __psiginfo_defined
#define __psiginfo_defined
#ifdef __CRT_HAVE_psiginfo
/* >> psiginfo(3)
 * Similar to `psignal(3)', but instead print extended signal information from `*pinfo' */
__CDECLARE_VOID(__ATTR_IN(1) __ATTR_IN_OPT(2),__NOTHROW_CB_NCX,psiginfo,(siginfo_t const *__pinfo, char const *__s),(__pinfo,__s))
#else /* __CRT_HAVE_psiginfo */
#include <libc/template/stdstreams.h>
#if defined(__LOCAL_stderr) && (defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))
#include <libc/local/signal/psiginfo.h>
/* >> psiginfo(3)
 * Similar to `psignal(3)', but instead print extended signal information from `*pinfo' */
__NAMESPACE_LOCAL_USING_OR_IMPL(psiginfo, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN_OPT(2) void __NOTHROW_CB_NCX(__LIBCCALL psiginfo)(siginfo_t const *__pinfo, char const *__s) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(psiginfo))(__pinfo, __s); })
#else /* __LOCAL_stderr && (__CRT_HAVE_fprintf_unlocked || __CRT_HAVE_fprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_HAVE_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE_fgetc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) */
#undef __psiginfo_defined
#endif /* !__LOCAL_stderr || (!__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && !__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) */
#endif /* !__CRT_HAVE_psiginfo */
#endif /* !__psiginfo_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SIGINFO_H */
