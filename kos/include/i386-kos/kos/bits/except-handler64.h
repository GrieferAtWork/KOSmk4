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
#ifndef _I386_KOS_KOS_BITS_EXCEPT_HANDLER64_H
#define _I386_KOS_KOS_BITS_EXCEPT_HANDLER64_H 1

#include <__stdinc.h>

#ifdef __CC__
#ifdef __x86_64__
__SYSDECL_BEGIN
struct kcpustate;
struct exception_data;
#define __except_handler64_t  __except_handler_t
#define __EXCEPT_HANDLER_CC   __ATTR_SYSVABI
#define __EXCEPT_HANDLER64_CC __ATTR_SYSVABI
typedef /*__ATTR_NORETURN*/ void
(__ATTR_SYSVABI *__except_handler64_t)(struct kcpustate *__restrict state,
                                       struct exception_data *__restrict error);
__SYSDECL_END
#else /* __x86_64__ */
#include <hybrid/__pointer.h>
__SYSDECL_BEGIN
struct kcpustate64;
struct exception_data64;
#define __EXCEPT_HANDLER64_CC /*__ATTR_SYSVABI*/
typedef /*__ATTR_NORETURN*/
__HYBRID_FUNCPTR64(void, /*__ATTR_SYSVABI*/, __except_handler64_t,
                   (struct kcpustate64 * __restrict state,
                    struct exception_data64 *__restrict error));
__SYSDECL_END
#endif /* !__x86_64__ */
#endif /* !__CC__ */

#endif /* !_I386_KOS_KOS_BITS_EXCEPT_HANDLER64_H */
