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
#ifndef _KOS_BITS_FASTEXCEPT_H
#define _KOS_BITS_FASTEXCEPT_H 1

#include <__stdinc.h>

#if (defined(__CC__) && defined(__KOS__) && \
     defined(__KERNEL__) && !defined(__INTELLISENSE__))
#include <__crt.h>

#include <sched/pertask.h>

#include <kos/bits/except-register-state.h> /* __EXCEPT_REGISTER_STATE_TYPE */
#include <kos/bits/exception_data.h>        /* struct exception_data, __except_code_t, ... */

__DECL_BEGIN

#ifndef __except_register_state_t_defined
#define __except_register_state_t_defined
typedef __EXCEPT_REGISTER_STATE_TYPE except_register_state_t;
#endif /* !__except_register_state_t_defined */

struct exception_info;
struct exception_data;
__COMPILER_SREDIRECT(__PUBDEF,/*ATTR_PERTASK*/,struct exception_info,__arch_this_exception_info,this_exception_info)
__COMPILER_SREDIRECT(__PUBDEF,/*ATTR_PERTASK*/,struct exception_data,__arch_this_exception_data,this_exception_data)
__COMPILER_SREDIRECT(__PUBDEF,/*ATTR_PERTASK*/,except_register_state_t,__arch_this_exception_state,this_exception_state)
__COMPILER_SREDIRECT(__PUBDEF,/*ATTR_PERTASK*/,__except_code_t,__arch_this_exception_code,this_exception_code)
__COMPILER_SREDIRECT(__PUBDEF,/*ATTR_PERTASK*/,__except_class_t,__arch_this_exception_class,this_exception_class)
__COMPILER_SREDIRECT(__PUBDEF,/*ATTR_PERTASK*/,__except_subclass_t,__arch_this_exception_subclass,this_exception_subclass)

/* Directly access per-task variables, thus allowing for inline optimizations. */
#define __arch_except_data()           (&PERTASK(__arch_this_exception_data))
#define __arch_except_code()           PERTASK_GET(__arch_this_exception_code)
#define __arch_except_active()         PERTASK_TEST(__arch_this_exception_code)
#define __arch_except_class()          PERTASK_GET(__arch_this_exception_class)
#define __arch_except_subclass()       PERTASK_GET(__arch_this_exception_subclass)
#define __arch_except_register_state() (&PERTASK(__arch_this_exception_state))
#define __arch_except_info()           (&PERTASK(__arch_this_exception_info))

/* These are used to implement was_thrown() */
#define __arch_except_code_eq(x)  PERTASK_EQ(__arch_this_exception_code, x)
#define __arch_except_class_eq(x) PERTASK_EQ(__arch_this_exception_class, x)

__DECL_END
#endif /* __CC__ && __KOS__ && __KERNEL__ && !__INTELLISENSE__ */

#endif /* !_KOS_BITS_FASTEXCEPT_H */
