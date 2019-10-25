/* HASH CRC-32:0xfb67edfc */
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
#ifndef __local_Execlpe_defined
#if defined(__CRT_HAVE_Execvpe)
#define __local_Execlpe_defined 1
#include <kos/anno.h>
#include <parts/redirect-exec.h>
/* Dependency: "Execvpe" */
#ifndef ____localdep_Execvpe_defined
#define ____localdep_Execvpe_defined 1
#if defined(__CRT_HAVE_Execvpe)
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT_VOID(__ATTR_NORETURN __ATTR_NONNULL((1, 2, 3)),,__localdep_Execvpe,(char const *__restrict __file, __TARGV, __TENVP),Execvpe,(__file,,)) __THROWS(...)
#else /* LIBC: Execvpe */
#undef ____localdep_Execvpe_defined
#endif /* Execvpe... */
#endif /* !____localdep_Execvpe_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinal */
__LOCAL_LIBC(Execlpe) __ATTR_NORETURN __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) void
(__VLIBCCALL __LIBC_LOCAL_NAME(Execlpe))(char const *__restrict __file,
                                         char const *__args,
                                         ... /*, (char *)NULL, (char **)environ*/) __THROWS(...) {
#line 69 "kos/src/libc/magic/kos.unistd.c"
	__REDIRECT_XEXECLE(char, __localdep_Execvpe, __file, __args)
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_Execvpe) */
#endif /* !__local_Execlpe_defined */
