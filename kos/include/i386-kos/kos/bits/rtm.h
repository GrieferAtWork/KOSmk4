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
#ifndef _I386_KOS_KOS_BITS_RTM_H
#define _I386_KOS_KOS_BITS_RTM_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

#define __SIZEOF_RTM_STATUS_T__ 4

#ifdef __CC__
__DECL_BEGIN
typedef __UINT32_TYPE__ __rtm_status_t;

#ifdef __COMPILER_HAVE_GCC_ASM
/* Inline-optimizations for specific RTM functions. */

/* Since we can assume that we're already inside of an RTM operation,
 * we   know  that  we   can  only  get   here  in  2  circumstances:
 *   - The real hardware has support for RTM, in which case it should
 *     also   be   able   to   recognize   the   `xend'  instruction.
 *   - We're  being emulated by  the `rtm' driver,  in which case its
 *     instruction decoder is able to detect the `xend'  instruction,
 *     and handle it as an alias for the `sys_rtm_end()' system call. */
#define __arch_rtm_end() __asm__ __volatile__("xend" : : : "memory")

#if defined(__GCC_ASM_FLAG_OUTPUTS__) && defined(__CRT_HAVE___x86_rtm_xtest)
#define __arch_rtm_test() __arch_rtm_test_impl()
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __BOOL
__NOTHROW(__arch_rtm_test_impl)(void) {
	__BOOL __res;
	__asm__ __volatile__(""
#ifdef __BUILDING_LIBC
	                     "call libc___x86_rtm_xtest"
#else /* __BUILDING_LIBC */
	                     "call __x86_rtm_xtest@PLT"
#endif /* !__BUILDING_LIBC */
	                     : "=@ccz" (__res)
	                     :
	                     : "cc"
	                     /* A call to `__x86_rtm_xtest' will also clobber `%Pax'! */
#ifdef __x86_64__
	                     , "%rax"
#else /* __x86_64__ */
	                     , "%eax"
#endif /* !__x86_64__ */
	                     );
	return __res;
}
#endif /* __GCC_ASM_FLAG_OUTPUTS__ && __CRT_HAVE___x86_rtm_test */

#endif /* __COMPILER_HAVE_GCC_ASM */

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_BITS_RTM_H */
