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
#ifndef __GUARD_HYBRID___ALLOCA_H
#define __GUARD_HYBRID___ALLOCA_H 1

#include "../__stdinc.h"

#if defined(__GNUC__) || __has_builtin(__builtin_alloca)
#define __hybrid_alloca(s)  __builtin_alloca(s)
#elif defined(_MSC_VER)
#include "typecore.h"
__SYSDECL_BEGIN
__NAMESPACE_INT_BEGIN
extern __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *(__cdecl _alloca)(__SIZE_TYPE__ __n_bytes);
#pragma intrinsic(_alloca)
__NAMESPACE_INT_END
__SYSDECL_END
#define __hybrid_alloca(s) (__NAMESPACE_INT_SYM _alloca)(s)
#else /* ... */
#if !defined(__NO_has_include) && !defined(__KOS_SYSTEM_HEADERS__)
#if __has_include(<alloca.h>)
#include <alloca.h>
#define __hybrid_alloca(s)  alloca(s)
#endif
#endif /* !__NO_has_include && !__KOS_SYSTEM_HEADERS__ */
#ifndef __hybrid_alloca
#if 0
#include "typecore.h"
__SYSDECL_BEGIN
extern __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *(alloca)(__SIZE_TYPE__ __n_bytes);
__SYSDECL_END
#define __hybrid_alloca(s)  (alloca)(s)
#endif
#endif /* !__hybrid_alloca */
#endif /* ... */

#endif /* !__GUARD_HYBRID___ALLOCA_H */
