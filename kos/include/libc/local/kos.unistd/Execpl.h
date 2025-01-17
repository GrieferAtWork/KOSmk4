/* HASH CRC-32:0xa3cfe030 */
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
#ifndef __local_Execpl_defined
#define __local_Execpl_defined
#include <__crt.h>
#ifdef __CRT_HAVE_Execvp
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_Execvp_defined
#define __local___localdep_Execvp_defined
__NAMESPACE_LOCAL_END
#include <features.h>
#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN __ATTR_IN(1) __ATTR_IN(2),__THROWING(...),__localdep_Execvp,(char const *__restrict __file, __TARGV),Execvp,(__file,___argv))
#endif /* !__local___localdep_Execvp_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(Execpl) __ATTR_NORETURN __ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2) void
(__VLIBCCALL __LIBC_LOCAL_NAME(Execpl))(char const *__restrict __file, char const *__args, ...) __THROWS(...) {
	__REDIRECT_XEXECL(char, (__NAMESPACE_LOCAL_SYM __localdep_Execvp), __file, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_Execpl_defined
#define __local___localdep_Execpl_defined
#define __localdep_Execpl __LIBC_LOCAL_NAME(Execpl)
#endif /* !__local___localdep_Execpl_defined */
#else /* __CRT_HAVE_Execvp */
#undef __local_Execpl_defined
#endif /* !__CRT_HAVE_Execvp */
#endif /* !__local_Execpl_defined */
