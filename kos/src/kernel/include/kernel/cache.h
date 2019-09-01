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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_CACHE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_CACHE_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <kernel/malloc.h>
#include <hybrid/sync/atomic-rwlock.h>

DECL_BEGIN

#ifdef __CC__

#ifdef CONFIG_BUILDING_KERNEL_CORE
#ifndef DEFINE_SYSTEM_CACHE_CLEAR
/* >> NOBLOCK size_t NOTHROW(KCALL func)(void);
 * Define a function that should be called when `system_clearcaches()' is invoked. */
#define DEFINE_SYSTEM_CACHE_CLEAR(func) \
	DEFINE_CALLBACK(".rodata.cold.callback.system_clearcaches",func)
#endif /* !DEFINE_SYSTEM_CACHE_CLEAR */
#endif /* CONFIG_BUILDING_KERNEL_CORE */

/* Declare/define a cache for preallocated/re-use free. */
#define DECLARE_PREALLOCATION_CACHE(decl, name, T)                                                         \
	decl ATTR_MALLOC WUNUSED ATTR_RETNONNULL T *(KCALL name##_alloc)(gfp_t alloc_flags)THROWS(E_BADALLOC); \
	decl NOBLOCK void NOTHROW(KCALL name##_free)(T * __restrict p);                                        \
	decl NOBLOCK size_t NOTHROW(KCALL name##_clear)(void);
#define DECLARE_PREALLOCATION_CACHE_ALLOC_NX(decl, name, T) \
	decl ATTR_MALLOC WUNUSED T *NOTHROW(KCALL name##_alloc_nx)(gfp_t alloc_flags);

#define DEFINE_PREALLOCATION_CACHE(decl, name, T, max_size) \
	decl DEFINE_ATOMIC_RWLOCK(name##_lock);                 \
	decl size_t name##_freesize = 0;                        \
	decl T *name##_freelist     = __NULLPTR;                \
	decl ATTR_MALLOC WUNUSED ATTR_RETNONNULL T *KCALL       \
	name##_alloc(gfp_t alloc_flags) THROWS(E_BADALLOC) {    \
		T *result = name##_freelist;                        \
		COMPILER_READ_BARRIER();                            \
		if (result) {                                       \
			sync_write(&name##_lock);                       \
			result = name##_freelist;                       \
			COMPILER_READ_BARRIER();                        \
			if (result) {                                   \
				name##_freelist = *(T **)result;            \
				--name##_freesize;                          \
				sync_endwrite(&name##_lock);                \
				return result;                              \
			}                                               \
			sync_endwrite(&name##_lock);                    \
		}                                                   \
		return (T *)kmalloc(sizeof(T), alloc_flags);        \
	}                                                       \
	decl NOBLOCK NONNULL((1)) void                          \
	NOTHROW(KCALL name##_free)(T * __restrict p) {          \
		if (name##_freesize < max_size) {                   \
			if (sync_trywrite(&name##_lock)) {              \
				COMPILER_READ_BARRIER();                    \
				if (name##_freesize < max_size) {           \
					*(T **)p        = name##_freelist;      \
					name##_freelist = p;                    \
					++name##_freesize;                      \
					sync_endwrite(&name##_lock);            \
					return;                                 \
				}                                           \
				sync_endwrite(&name##_lock);                \
			}                                               \
		}                                                   \
		kfree(p);                                           \
	}                                                       \
	DEFINE_SYSTEM_CACHE_CLEAR(name##_clear);                \
	decl NOBLOCK ATTR_USED                                  \
	ATTR_COLDTEXT size_t                                    \
	NOTHROW(KCALL name##_clear)(void) {                     \
		size_t result = 0;                                  \
		if (sync_trywrite(&name##_lock)) {                  \
			T *chain, *next;                                \
			chain           = name##_freelist;              \
			name##_freelist = NULL;                         \
			name##_freesize = 0;                            \
			sync_endwrite(&name##_lock);                    \
			while (chain) {                                 \
				next = *(T **)chain;                        \
				result += kmalloc_usable_size(chain);       \
				kfree(chain);                               \
				chain = next;                               \
			}                                               \
		}                                                   \
		return result;                                      \
	}
#define DEFINE_PREALLOCATION_CACHE_ALLOC_NX(decl, name, T) \
	decl ATTR_MALLOC WUNUSED T *                           \
	NOTHROW(KCALL name##_alloc_nx)(gfp_t alloc_flags) {    \
		T *result = name##_freelist;                       \
		COMPILER_READ_BARRIER();                           \
		if (result) {                                      \
			sync_write(&name##_lock);                      \
			result = name##_freelist;                      \
			COMPILER_READ_BARRIER();                       \
			if (result) {                                  \
				name##_freelist = *(T **)result;           \
				--name##_freesize;                         \
				sync_endwrite(&name##_lock);               \
				return result;                             \
			}                                              \
			sync_endwrite(&name##_lock);                   \
		}                                                  \
		return (T *)kmalloc_nx(sizeof(T), alloc_flags);    \
	}

#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_CACHE_H */
