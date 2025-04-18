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
/*!replace_with_include <kos/bits/except-handler.h>*/
#ifndef _I386_KOS_KOS_BITS_EXCEPT_HANDLER32_H
#define _I386_KOS_KOS_BITS_EXCEPT_HANDLER32_H 1

#include <__stdinc.h>

#ifdef __CC__
#ifndef __restrict_111080
#ifdef __COMPILER_HAVE_BUG_GCC_111080
#define __restrict_111080 /* Nothing */
#else /* __COMPILER_HAVE_BUG_GCC_111080 */
#define __restrict_111080 __restrict
#endif /* !__COMPILER_HAVE_BUG_GCC_111080 */
#endif /* !__restrict_111080 */

#ifndef __x86_64__
__SYSDECL_BEGIN
struct kcpustate;
struct exception_data;
#define __except_handler32_t  __except_handler_t
#define __EXCEPT_HANDLER_CC   __ATTR_FASTCALL
#define __EXCEPT_HANDLER32_CC __ATTR_FASTCALL
typedef /*__ATTR_NORETURN*/ void
(__ATTR_FASTCALL *__except_handler32_t)(struct kcpustate *__restrict_111080 state,
                                        struct exception_data *__restrict_111080 error);
__SYSDECL_END
#else /* __x86_64__ */
#include <hybrid/__pointer.h>
__SYSDECL_BEGIN
struct kcpustate32;
struct __exception_data32;
#define __EXCEPT_HANDLER32_CC /*__ATTR_FASTCALL*/
typedef /*__ATTR_NORETURN*/
__HYBRID_FUNCPTR32(void, /*__ATTR_FASTCALL*/, __except_handler32_t,
                   (struct kcpustate32 *__restrict_111080 state,
                    struct __exception_data32 *__restrict_111080 error));
__SYSDECL_END
#endif /* !__x86_64__ */
#endif /* !__CC__ */

#endif /* !_I386_KOS_KOS_BITS_EXCEPT_HANDLER32_H */
