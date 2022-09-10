/* HASH CRC-32:0xdfdde51f */
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
#ifndef __local_attr_copy_action_defined
#define __local_attr_copy_action_defined
#include <__crt.h>
#include <attr/error_context.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_attr_load_actions_defined
#define __local___localdep_attr_load_actions_defined
__NAMESPACE_LOCAL_END
#include <libc/local/attr.libattr/attr_load_actions.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_attr_load_actions __LIBC_LOCAL_NAME(attr_load_actions)
#endif /* !__local___localdep_attr_load_actions_defined */
#ifndef __local___localdep_fnmatch_defined
#define __local___localdep_fnmatch_defined
#ifdef __CRT_HAVE_fnmatch
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_fnmatch,(char const *__pattern, char const *__name, __STDC_INT_AS_UINT_T __match_flags),fnmatch,(__pattern,__name,__match_flags))
#else /* __CRT_HAVE_fnmatch */
__NAMESPACE_LOCAL_END
#include <libc/local/fnmatch/fnmatch.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fnmatch __LIBC_LOCAL_NAME(fnmatch)
#endif /* !__CRT_HAVE_fnmatch */
#endif /* !__local___localdep_fnmatch_defined */
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined
#ifdef __CRT_HAVE_strend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(attr_copy_action) __ATTR_IN(1) __ATTR_INOUT_OPT(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(attr_copy_action))(char const *__attr_name, struct error_context *__ctx) {
	/* NOTE: `actions' has the following format:
	 * >> actions_base:     [
	 * >>                       {NAME}
	 * >>                       \0
	 * >>                       {CODE}
	 * >>                   ]...
	 * >> actions_end:      \0
	 * Where NAME is a C-string, and CODE is \1 or \2
	 */
	static char const *__actions = __NULLPTR;
	char const *__iter;
	if (__actions == __NULLPTR)
		__actions = (__NAMESPACE_LOCAL_SYM __localdep_attr_load_actions)(__ctx); /* Lazily load actions. */

	/* Search for the requested action. */
	for (__iter = __actions; *__iter; __iter = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__iter) + 2) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_fnmatch)(__iter, __attr_name, 0) == 0)
			return (int)(unsigned int)(unsigned char)(__NAMESPACE_LOCAL_SYM __localdep_strend)(__iter)[1];
	}

	/* No special action... */
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_attr_copy_action_defined
#define __local___localdep_attr_copy_action_defined
#define __localdep_attr_copy_action __LIBC_LOCAL_NAME(attr_copy_action)
#endif /* !__local___localdep_attr_copy_action_defined */
#endif /* !__local_attr_copy_action_defined */
