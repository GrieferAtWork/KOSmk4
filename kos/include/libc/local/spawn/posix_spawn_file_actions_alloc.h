/* HASH CRC-32:0x9e68eb10 */
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
#ifndef __local_posix_spawn_file_actions_alloc_defined
#define __local_posix_spawn_file_actions_alloc_defined
#include <__crt.h>
#include <asm/crt/posix_spawn.h>
#if defined(__POSIX_SPAWN_USE_KOS) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <bits/crt/posix_spawn.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),__libc_realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
__LOCAL_LIBC(posix_spawn_file_actions_alloc) __ATTR_WUNUSED __ATTR_INOUT(1) struct __spawn_action *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(posix_spawn_file_actions_alloc))(struct __posix_spawn_file_actions *__restrict __file_actions) {
	struct __spawn_action *__result;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("__used")
#pragma push_macro("__actions")
#pragma push_macro("__allocated")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef __used
#undef __actions
#undef __allocated
	__result = __file_actions->__actions;
	if ((unsigned int)__file_actions->__used >= (unsigned int)__file_actions->__allocated) {
		unsigned int __newalloc;
		__newalloc = (unsigned int)__file_actions->__used + 8;
		__result   = (struct __spawn_action *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__result, __newalloc * sizeof(struct __spawn_action));
		if __unlikely(!__result) {
			__newalloc = (unsigned int)__file_actions->__used + 1;
			__result = __file_actions->__actions;
			__result = (struct __spawn_action *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__result, __newalloc * sizeof(struct __spawn_action));
			if __unlikely(!__result)
				return __NULLPTR;
		}
		__file_actions->__actions   = __result;
		__file_actions->__allocated = __newalloc;
	}
	__result += __file_actions->__used++;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("__used")
#pragma pop_macro("__actions")
#pragma pop_macro("__allocated")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_spawn_file_actions_alloc_defined
#define __local___localdep_posix_spawn_file_actions_alloc_defined
#define __localdep_posix_spawn_file_actions_alloc __LIBC_LOCAL_NAME(posix_spawn_file_actions_alloc)
#endif /* !__local___localdep_posix_spawn_file_actions_alloc_defined */
#else /* __POSIX_SPAWN_USE_KOS && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __local_posix_spawn_file_actions_alloc_defined
#endif /* !__POSIX_SPAWN_USE_KOS || (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !__local_posix_spawn_file_actions_alloc_defined */
