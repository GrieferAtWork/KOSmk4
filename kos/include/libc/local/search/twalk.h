/* HASH CRC-32:0xcb395618 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_twalk_defined
#define __local_twalk_defined
#include <__crt.h>
#ifndef __VISIT_defined
#define __VISIT_defined
typedef enum {
	preorder  = 0,
	postorder = 1,
	endorder  = 2,
	leaf      = 3
} VISIT;
#endif /* !__VISIT_defined */
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_twalk_r_defined
#define __local___localdep_twalk_r_defined
#ifdef __CRT_HAVE_twalk_r
__CREDIRECT_VOID(__ATTR_IN_OPT(1),__THROWING,__localdep_twalk_r,(void const *__root, void (__LIBCCALL *__action)(void const *__nodep, VISIT ___value, int __level, void *__arg), void *__arg),twalk_r,(__root,__action,__arg))
#elif defined(__CRT_HAVE___twalk_r)
__CREDIRECT_VOID(__ATTR_IN_OPT(1),__THROWING,__localdep_twalk_r,(void const *__root, void (__LIBCCALL *__action)(void const *__nodep, VISIT ___value, int __level, void *__arg), void *__arg),__twalk_r,(__root,__action,__arg))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/search/twalk_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_twalk_r __LIBC_LOCAL_NAME(twalk_r)
#endif /* !... */
#endif /* !__local___localdep_twalk_r_defined */
__NAMESPACE_LOCAL_END
#ifndef __LIBCCALL_CALLER_CLEANUP
#ifndef ____invoke_twalk_action_helper_defined
__NAMESPACE_LOCAL_BEGIN
#define ____invoke_twalk_action_helper_defined
__LOCAL_LIBC(__invoke_twalk_action_helper) void
(__LIBCCALL __invoke_twalk_action_helper)(void const *__nodep, VISIT ___value, int __level, void *__arg) {
	(*(void (__LIBCCALL *)(void const *, VISIT, int))__arg)(__nodep, ___value, __level);
}
__NAMESPACE_LOCAL_END
#endif /* !____invoke_twalk_action_helper_defined */
#endif /* !__LIBCCALL_CALLER_CLEANUP */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(twalk) __ATTR_IN_OPT(1) void
(__LIBCCALL __LIBC_LOCAL_NAME(twalk))(void const *__root, void (__LIBCCALL *__action)(void const *__nodep, VISIT ___value, int __level)) __THROWS(...) {
#ifdef __LIBCCALL_CALLER_CLEANUP
	(__NAMESPACE_LOCAL_SYM __localdep_twalk_r)(__root, (void (__LIBCCALL *)(void const *, VISIT, int, void *))(void *)__action, __NULLPTR);
#else /* __LIBCCALL_CALLER_CLEANUP */
	(__NAMESPACE_LOCAL_SYM __localdep_twalk_r)(__root, &__NAMESPACE_LOCAL_SYM __invoke_twalk_action_helper, (void *)__action);
#endif /* !__LIBCCALL_CALLER_CLEANUP */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_twalk_defined
#define __local___localdep_twalk_defined
#define __localdep_twalk __LIBC_LOCAL_NAME(twalk)
#endif /* !__local___localdep_twalk_defined */
#endif /* !__local_twalk_defined */
