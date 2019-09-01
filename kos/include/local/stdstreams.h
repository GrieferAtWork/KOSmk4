/* HASH 0x76cb06c3 */
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
#ifndef __local_stdstream_defined
#define __local_stdstream_defined 1
#ifndef __NO_STDSTREAMS
#ifdef __cplusplus

#ifndef __stdstreams_defined
#define __stdstreams_defined 1
#undef stdin
#undef stdout
#undef stderr
#ifdef __CRT_CYG_PRIMARY
#   define stdin  (__CYG_REENT->__cyg_stdin)
#   define stdout (__CYG_REENT->__cyg_stdout)
#   define stderr (__CYG_REENT->__cyg_stderr)
#elif defined(__CRT_DOS_PRIMARY)
#ifdef __USE_DOS_LINKOBJECTS
__LIBC FILE _iob[];
#   define stdin    (_iob+0)
#   define stdout   (_iob+1)
#   define stderr   (_iob+2)
#else /* __USE_DOS_LINKOBJECTS */
__LIBC __ATTR_WUNUSED __ATTR_RETNONNULL FILE *__NOTHROW(__LIBCCALL __iob_func)(void);
#   define stdin    (__iob_func()+0)
#   define stdout   (__iob_func()+1)
#   define stderr   (__iob_func()+2)
#endif /* !__USE_DOS_LINKOBJECTS */
#else
__LIBC __FILE *stdin;
#define stdin  stdin
__LIBC __FILE *stdout;
#define stdout stdout
__LIBC __FILE *stderr;
#define stderr stderr
#endif
#endif /* !__stdstreams_defined */

#else /* __cplusplus */

#ifdef __CRT_CYG_PRIMARY
#include <sys/reent.h>
#define __LOCAL_stdin  (__CYG_REENT->__cyg_stdin)
#define __LOCAL_stdout (__CYG_REENT->__cyg_stdout)
#define __LOCAL_stderr (__CYG_REENT->__cyg_stderr)
#elif defined(__CRT_DOS_PRIMARY)
#ifdef __USE_DOS_LINKOBJECTS
#ifndef ___iob_defined
#define ___iob_defined 1
__LIBC FILE _iob[];
#endif /* !___iob_defined */
#define __LOCAL_stdin    (_iob+0)
#define __LOCAL_stdout   (_iob+1)
#define __LOCAL_stderr   (_iob+2)
#else /* __USE_DOS_LINKOBJECTS */
#ifndef ____iob_func_defined
#define ____iob_func_defined 1
__LIBC __ATTR_WUNUSED __ATTR_RETNONNULL FILE *__NOTHROW(__LIBCCALL __iob_func)(void);
#endif /* !____iob_func_defined */
#   define __LOCAL_stdin    (__iob_func()+0)
#   define __LOCAL_stdout   (__iob_func()+1)
#   define __LOCAL_stderr   (__iob_func()+2)
#endif /* !__USE_DOS_LINKOBJECTS */
#elif !defined(__NO_ASMNAME)
__LIBC __FILE *__LOCAL_stdin __ASMNAME("stdin");
__LIBC __FILE *__LOCAL_stdout __ASMNAME("stdout");
__LIBC __FILE *__LOCAL_stderr __ASMNAME("stderr");
#else
#ifndef __stdstreams_defined
#define __stdstreams_defined 1
__LIBC __FILE *stdin;
#define stdin  stdin
__LIBC __FILE *stdout;
#define stdout stdout
__LIBC __FILE *stderr;
#define stderr stderr
#endif /* !__stdstreams_defined */
#define __LOCAL_stdin    stdin
#define __LOCAL_stdout   stdout
#define __LOCAL_stderr   stderr
#endif

#endif /* !__cplusplus */
#endif /* !__NO_STDSTREAMS */
#endif /* !__local_stdstream_defined */
