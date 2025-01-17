/* HASH CRC-32:0x4a56ceb1 */
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
#ifndef __local_posix_spawn_file_actions_destroy_defined
#define __local_posix_spawn_file_actions_destroy_defined
#include <__crt.h>
#include <asm/crt/posix_spawn.h>
#ifdef __POSIX_SPAWN_USE_KOS
#include <bits/crt/posix_spawn.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_memset_defined
#define __local___localdep_memset_defined
#ifdef __CRT_HAVE_memset
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_memset */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memset.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memset __LIBC_LOCAL_NAME(memset)
#endif /* !__CRT_HAVE_memset */
#endif /* !__local___localdep_memset_defined */
__LOCAL_LIBC(posix_spawn_file_actions_destroy) __ATTR_INOUT(1) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(posix_spawn_file_actions_destroy))(struct __posix_spawn_file_actions *__restrict __file_actions) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	unsigned int __i;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("__used")
#pragma push_macro("__actions")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef __used
#undef __actions
	for (__i = 0; __i < (unsigned int)__file_actions->__used; ++__i) {
		struct __spawn_action *__act;
		__act = &__file_actions->__actions[__i];
		switch (__act->__sa_tag) {

		case __POSIX_SPAWN_ACTION_OPEN:
			(__NAMESPACE_LOCAL_SYM __localdep_free)(__act->__sa_action.__sa_open_action.__sa_path);
			break;

		default:
			break;
		}
	}
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__file_actions->__actions);
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("__actions")
#pragma pop_macro("__used")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
	(__NAMESPACE_LOCAL_SYM __localdep_memset)(__file_actions, 0xcc, sizeof(*__file_actions));
#endif /* !NDEBUG && !NDEBUG_FINI */
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_spawn_file_actions_destroy_defined
#define __local___localdep_posix_spawn_file_actions_destroy_defined
#define __localdep_posix_spawn_file_actions_destroy __LIBC_LOCAL_NAME(posix_spawn_file_actions_destroy)
#endif /* !__local___localdep_posix_spawn_file_actions_destroy_defined */
#else /* __POSIX_SPAWN_USE_KOS */
#undef __local_posix_spawn_file_actions_destroy_defined
#endif /* !__POSIX_SPAWN_USE_KOS */
#endif /* !__local_posix_spawn_file_actions_destroy_defined */
