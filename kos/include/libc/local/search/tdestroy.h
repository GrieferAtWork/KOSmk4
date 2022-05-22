/* HASH CRC-32:0x6de2427c */
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
#ifndef __local_tdestroy_defined
#define __local_tdestroy_defined
#include <__crt.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_tdestroy_r_defined
#define __local___localdep_tdestroy_r_defined
#ifdef __CRT_HAVE_tdestroy_r
__CREDIRECT_VOID(__ATTR_ACCESS_RW_OPT(1) __ATTR_NONNULL((2)),__THROWING,__localdep_tdestroy_r,(void *__root, void (__LIBCCALL *__freefct)(void *__nodep, void *__arg), void *__arg),tdestroy_r,(__root,__freefct,__arg))
#else /* __CRT_HAVE_tdestroy_r */
__NAMESPACE_LOCAL_END
#include <libc/local/search/tdestroy_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tdestroy_r __LIBC_LOCAL_NAME(tdestroy_r)
#endif /* !__CRT_HAVE_tdestroy_r */
#endif /* !__local___localdep_tdestroy_r_defined */
__NAMESPACE_LOCAL_END
#ifndef __LIBCCALL_CALLER_CLEANUP
#ifndef ____invoke_free_fn_helper_defined
__NAMESPACE_LOCAL_BEGIN
#define ____invoke_free_fn_helper_defined
__LOCAL_LIBC(__invoke_free_fn_helper) void
(__LIBCCALL __invoke_free_fn_helper)(void *__nodep, void *__arg) {
	(*(void (__LIBCCALL *)(void *))__arg)(__nodep);
}
__NAMESPACE_LOCAL_END
#endif /* !____invoke_free_fn_helper_defined */
#endif /* !__LIBCCALL_CALLER_CLEANUP */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(tdestroy) __ATTR_ACCESS_RW_OPT(1) __ATTR_NONNULL((2)) void
(__LIBCCALL __LIBC_LOCAL_NAME(tdestroy))(void *__root, void (__LIBCCALL *__freefct)(void *__nodep)) __THROWS(...) {
#ifdef __LIBCCALL_CALLER_CLEANUP
	(__NAMESPACE_LOCAL_SYM __localdep_tdestroy_r)(__root, (void (__LIBCCALL *)(void *, void *))(void *)__freefct, __NULLPTR);
#else /* __LIBCCALL_CALLER_CLEANUP */
	(__NAMESPACE_LOCAL_SYM __localdep_tdestroy_r)(__root, &__NAMESPACE_LOCAL_SYM __invoke_free_fn_helper, (void *)__freefct);
#endif /* !__LIBCCALL_CALLER_CLEANUP */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tdestroy_defined
#define __local___localdep_tdestroy_defined
#define __localdep_tdestroy __LIBC_LOCAL_NAME(tdestroy)
#endif /* !__local___localdep_tdestroy_defined */
#endif /* !__local_tdestroy_defined */
