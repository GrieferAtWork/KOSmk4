/* HASH CRC-32:0xe3c5abbd */
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
#ifndef __local__CrtSetDbgFlag_defined
#if defined(__CRT_HAVE___p__crtDbgFlag)
#define __local__CrtSetDbgFlag_defined 1
/* Dependency: "__p__crtDbgFlag" */
#ifndef ____localdep___p__crtDbgFlag_defined
#define ____localdep___p__crtDbgFlag_defined 1
#if defined(__CRT_HAVE___p__crtDbgFlag)
__CREDIRECT(,int *,__NOTHROW_NCX,__localdep___p__crtDbgFlag,(void),__p__crtDbgFlag,())
#else /* LIBC: __p__crtDbgFlag */
#undef ____localdep___p__crtDbgFlag_defined
#endif /* __p__crtDbgFlag... */
#endif /* !____localdep___p__crtDbgFlag_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_CrtSetDbgFlag) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_CrtSetDbgFlag))(int __new_flag) {
#line 259 "kos/src/libc/magic/crtdbg.c"
	int __result, *__ptr;
	__ptr = __localdep___p__crtDbgFlag();
	__result = *__ptr;
	*__ptr = __new_flag;
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE___p__crtDbgFlag) */
#endif /* !__local__CrtSetDbgFlag_defined */
