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
#ifndef __local_program_invocation_name_defined
#define __local_program_invocation_name_defined
#include <__crt.h>

__SYSDECL_BEGIN

#ifndef __LOCAL_program_invocation_name
#ifdef program_invocation_name
#define __LOCAL_program_invocation_name   program_invocation_name
#define __LOCAL_program_invocation_name_p program_invocation_name
#elif defined(_pgmptr)
#define __LOCAL_program_invocation_name   _pgmptr
#define __LOCAL_program_invocation_name_p _pgmptr
#elif defined(__progname_full)
#define __LOCAL_program_invocation_name   __progname_full
#define __LOCAL_program_invocation_name_p __progname_full
#elif defined(__CRT_HAVE_program_invocation_name)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,char *,__LOCAL_program_invocation_name,program_invocation_name)
#define __LOCAL_program_invocation_name   __LOCAL_program_invocation_name
#define __LOCAL_program_invocation_name_p __LOCAL_program_invocation_name
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,char *,program_invocation_name)
#define program_invocation_name           program_invocation_name
#define __LOCAL_program_invocation_name   program_invocation_name
#define __LOCAL_program_invocation_name_p program_invocation_name
#endif /* __NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE__pgmptr)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,char *,__LOCAL_program_invocation_name,_pgmptr)
#define __LOCAL_program_invocation_name   __LOCAL_program_invocation_name
#define __LOCAL_program_invocation_name_p __LOCAL_program_invocation_name
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,char *,_pgmptr)
#define _pgmptr                           _pgmptr
#define __LOCAL_program_invocation_name   _pgmptr
#define __LOCAL_program_invocation_name_p _pgmptr
#endif /* __NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___progname_full)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,char *,__LOCAL_program_invocation_name,__progname_full)
#define __LOCAL_program_invocation_name   __LOCAL_program_invocation_name
#define __LOCAL_program_invocation_name_p __LOCAL_program_invocation_name_p
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,char *,__progname_full)
#define __progname_full                   __progname_full
#define __LOCAL_program_invocation_name   __progname_full
#define __LOCAL_program_invocation_name_p __LOCAL_program_invocation_name_p
#endif /* __NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE_getexecname)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char /*const*/ *,__NOTHROW_NCX,__LOCAL_getexecname,(void),getexecname,())
#define __LOCAL_program_invocation_name __LOCAL_getexecname()
#elif defined(__CRT_HAVE___p__pgmptr) || defined(__CRT_HAVE___p_program_invocation_name)
#ifndef ____p__pgmptr_defined
#define ____p__pgmptr_defined
#ifdef __CRT_HAVE___p__pgmptr
/* Alias for argv[0], as passed to main() */
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char **,__NOTHROW_NCX,__p__pgmptr,(void),())
#else /* __CRT_HAVE___p__pgmptr */
/* Alias for argv[0], as passed to main() */
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char **,__NOTHROW_NCX,__p__pgmptr,(void),__p_program_invocation_name,())
#endif /* !__CRT_HAVE___p__pgmptr */
#endif /* !____p__pgmptr_defined */
#define __LOCAL_program_invocation_name   (*__NAMESPACE_GLB_SYM __p__pgmptr())
#define __LOCAL_program_invocation_name_p (*__NAMESPACE_GLB_SYM __p__pgmptr())
#endif /* ... */
#endif /* !__LOCAL_program_invocation_name */

/* Alias for `strchr(argv[0], '/') ? strchr(argv[0], '/') + 1 : argv[0]', as passed to main() */
#ifndef __LOCAL_program_invocation_short_name
#ifdef program_invocation_short_name
#define __LOCAL_program_invocation_short_name   program_invocation_short_name
#define __LOCAL_program_invocation_short_name_p program_invocation_short_name
#elif defined(__progname)
#define __LOCAL_program_invocation_short_name   __progname
#define __LOCAL_program_invocation_short_name_p __progname
#elif defined(__CRT_HAVE_program_invocation_short_name)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,char *,__LOCAL_program_invocation_short_name,program_invocation_short_name)
#define __LOCAL_program_invocation_short_name   __LOCAL_program_invocation_short_name
#define __LOCAL_program_invocation_short_name_p __LOCAL_program_invocation_short_name
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,char *,program_invocation_short_name)
#define program_invocation_short_name           program_invocation_short_name
#define __LOCAL_program_invocation_short_name   program_invocation_short_name
#define __LOCAL_program_invocation_short_name_p program_invocation_short_name
#endif /* __NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___progname)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,char *,__LOCAL_program_invocation_short_name,__progname)
#define __LOCAL_program_invocation_short_name   __LOCAL_program_invocation_short_name
#define __LOCAL_program_invocation_short_name_p __LOCAL_program_invocation_short_name
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,char *,__progname)
#define __progname                              __progname
#define __LOCAL_program_invocation_short_name   __progname
#define __LOCAL_program_invocation_short_name_p __progname
#endif /* __NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___p_program_invocation_short_name)
#ifndef ____p_program_invocation_short_name_defined
#define ____p_program_invocation_short_name_defined
/* Alias for `strchr(argv[0], '/') ? strchr(argv[0], '/') + 1 : argv[0]', as passed to main() */
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char **,__NOTHROW_NCX,__p_program_invocation_short_name,(void),())
#endif /* !____p_program_invocation_short_name_defined */
#define __LOCAL_program_invocation_short_name   (*__NAMESPACE_GLB_SYM __p_program_invocation_short_name())
#define __LOCAL_program_invocation_short_name_p (*__NAMESPACE_GLB_SYM __p_program_invocation_short_name())
#elif defined(__LOCAL_program_invocation_name)
__SYSDECL_END
#include <libc/string.h>
__SYSDECL_BEGIN
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(get_program_invocation_short_name) __ATTR_RETNONNULL __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(get_program_invocation_short_name))(void) {
	char *__result = __LOCAL_program_invocation_name;
	if (__result) {
#ifdef _WIN32
		char *__iter, *__ptr = __NULLPTR;
		for (__iter = __result; *__iter; ++__iter) {
			if (*__iter == '/' || *__iter == '\\')
				__ptr = __iter;
		}
#else /* _WIN32 */
		char *__ptr = __libc_strrchr(__result, '/');
#endif /* !_WIN32 */
		if (__ptr)
			__result = __ptr + 1;
	}
	return __result;
}
__NAMESPACE_LOCAL_END

#define __LOCAL_program_invocation_short_name \
	((__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(get_program_invocation_short_name))())
#endif /* ... */
#endif /* !__LOCAL_program_invocation_short_name */

__SYSDECL_END

#endif /* !__local_program_invocation_name_defined */
