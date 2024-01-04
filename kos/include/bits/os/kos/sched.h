/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_OS_KOS_SCHED_H
#define _BITS_OS_KOS_SCHED_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

#define __OFFSET_SCHED_PARAM_SCHED_PRIORITY 0
#define __SIZEOF_SCHED_PARAM                __SIZEOF_INT__
#define __ALIGNOF_SCHED_PARAM               __ALIGNOF_INT__
#ifdef __CC__
__DECL_BEGIN

struct sched_param /*[PREFIX()]*/ {
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("sched_priority")
#pragma push_macro("__sched_priority")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef sched_priority
#undef __sched_priority
	union {
		int sched_priority;
		int __sched_priority;
	};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("__sched_priority")
#pragma pop_macro("sched_priority")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("__sched_priority")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef __sched_priority
	int __sched_priority;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("__sched_priority")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#ifndef sched_priority
#define sched_priority __sched_priority
#endif /* !sched_priority */
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_SCHED_H */
