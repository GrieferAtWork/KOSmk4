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
/*!replace_with_include <stdio.h>*/
#ifndef _LIBC_TEMPLATE_STDSTREAMS_H
#define _LIBC_TEMPLATE_STDSTREAMS_H 1
#include <__crt.h>
#ifdef __CRT_CYG_PRIMARY
#include <sys/reent.h>
#endif /* __CRT_CYG_PRIMARY */

#ifdef __CC__
__SYSDECL_BEGIN

/* Define symbols needed for stdio FILE access */
#if defined(__CYG_REENT)
/* nothing */
#elif !defined(___iob_defined) && defined(__CRT_HAVE__iob)
#include <bits/crt/io-file.h>
#define ___iob_defined
__CSDECLARE2(,__FILE _iob[],_iob)
#ifndef ____iob_func_defined
#define ____iob_func_defined
#define __iob_func() (_iob)
#endif /* !____iob_func_defined */
#elif !defined(____p__iob_defined) && defined(__CRT_HAVE___p__iob)
#include <bits/crt/io-file.h>
#define ____p__iob_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__FILE *,__NOTHROW,__p__iob,(void),())
#ifndef ____iob_func_defined
#define ____iob_func_defined
#define __iob_func __p__iob
#endif /* !____iob_func_defined */
#elif !defined(____iob_func_defined) && defined(__CRT_HAVE___iob_func)
#include <bits/crt/io-file.h>
#define ____iob_func_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__FILE *,__NOTHROW,__iob_func,(void),())
#endif /* ... */


/* ===== __LOCAL_stdin ============================== */
#ifndef __LOCAL_stdin
#ifdef stdin
#define __LOCAL_stdin stdin
#elif defined(__CRT_HAVE_stdin)
__CSDECLARE(,__FILE *,stdin)
#define stdin         stdin
#define __LOCAL_stdin stdin
#elif defined(__CYG_REENT)
#define __LOCAL_stdin (__CYG_REENT->__cyg_stdin)
#elif defined(____iob_func_defined)
#define __LOCAL_stdin (__iob_func() + 0)
#elif defined(__CRT_HAVE___stdinp)
#ifndef __stdinp
__CSDECLARE(,__FILE *,__stdinp)
#define __stdinp __stdinp
#endif /* !__stdinp */
#define __LOCAL_stdin __stdinp
#elif defined(__CRT_HAVE__IO_stdin_)
#ifndef _IO_stdin_
__CSDECLARE(,__FILE,_IO_stdin_)
#define _IO_stdin_ _IO_stdin_
#endif /* !_IO_stdin_ */
#define __LOCAL_stdin (&_IO_stdin_)
#elif defined(__CRT_HAVE__IO_2_1_stdin_)
#ifndef _IO_2_1_stdin_
__CSDECLARE(,__FILE,_IO_2_1_stdin_)
#define _IO_2_1_stdin_ _IO_2_1_stdin_
#endif /* !_IO_2_1_stdin_ */
#define __LOCAL_stdin (&_IO_2_1_stdin_)
#endif /* ... */
#endif /* !__LOCAL_stdin */


/* ===== __LOCAL_stdout ============================= */
#ifndef __LOCAL_stdout
#ifdef stdout
#define __LOCAL_stdout stdout
#elif defined(__CRT_HAVE_stdout)
__CSDECLARE(,__FILE *,stdout)
#define stdout         stdout
#define __LOCAL_stdout stdout
#elif defined(__CYG_REENT)
#define __LOCAL_stdout (__CYG_REENT->__cyg_stdout)
#elif defined(____iob_func_defined)
#define __LOCAL_stdout (__iob_func() + 1)
#elif defined(__CRT_HAVE___stdoutp)
#ifndef __stdoutp
__CSDECLARE(,__FILE *,__stdoutp)
#define __stdoutp __stdoutp
#endif /* !__stdoutp */
#define __LOCAL_stdout __stdoutp
#elif defined(__CRT_HAVE__IO_stdout_)
#ifndef _IO_stdout_
__CSDECLARE(,__FILE,_IO_stdout_)
#define _IO_stdout_ _IO_stdout_
#endif /* !_IO_stdout_ */
#define __LOCAL_stdout (&_IO_stdout_)
#elif defined(__CRT_HAVE__IO_2_1_stdout_)
#ifndef _IO_2_1_stdout_
__CSDECLARE(,__FILE,_IO_2_1_stdout_)
#define _IO_2_1_stdout_ _IO_2_1_stdout_
#endif /* !_IO_2_1_stdout_ */
#define __LOCAL_stdout (&_IO_2_1_stdout_)
#endif /* ... */
#endif /* !__LOCAL_stdout */


/* ===== __LOCAL_stderr ============================= */
#ifndef __LOCAL_stderr
#ifdef stderr
#define __LOCAL_stderr stderr
#elif defined(__CRT_HAVE_stderr)
__CSDECLARE(,__FILE *,stderr)
#define stderr         stderr
#define __LOCAL_stderr stderr
#elif defined(__CYG_REENT)
#define __LOCAL_stderr (__CYG_REENT->__cyg_stderr)
#elif defined(____iob_func_defined)
#define __LOCAL_stderr (__iob_func() + 2)
#elif defined(__CRT_HAVE___stderrp)
#ifndef __stderrp
__CSDECLARE(,__FILE *,__stderrp)
#define __stderrp __stderrp
#endif /* !__stderrp */
#define __LOCAL_stderr __stderrp
#elif defined(__CRT_HAVE__IO_stderr_)
#ifndef _IO_stderr_
__CSDECLARE(,__FILE,_IO_stderr_)
#define _IO_stderr_ _IO_stderr_
#endif /* !_IO_stderr_ */
#define __LOCAL_stderr (&_IO_stderr_)
#elif defined(__CRT_HAVE__IO_2_1_stderr_)
#ifndef _IO_2_1_stderr_
__CSDECLARE(,__FILE,_IO_2_1_stderr_)
#define _IO_2_1_stderr_ _IO_2_1_stderr_
#endif /* !_IO_2_1_stderr_ */
#define __LOCAL_stderr (&_IO_2_1_stderr_)
#endif /* ... */
#endif /* !__LOCAL_stderr */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_LIBC_TEMPLATE_STDSTREAMS_H */
