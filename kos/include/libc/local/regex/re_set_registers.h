/* HASH CRC-32:0xfbc3bece */
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
#ifndef __local_re_set_registers_defined
#define __local_re_set_registers_defined
#include <__crt.h>
#include <bits/crt/regex.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(re_set_registers) __ATTR_INOUT(1) __ATTR_OUT(2) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(re_set_registers))(struct re_pattern_buffer *__self, struct __re_registers *__regs, unsigned int __num_regs, __regoff_t *__starts, __regoff_t *__ends) {
	(void)__self;
	__regs->num_regs = __num_regs;
	if (__num_regs) {
		__regs->start = __starts;
		__regs->end   = __ends;
	} else {
		__regs->start = __NULLPTR;
		__regs->end   = __NULLPTR;
	}
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_re_set_registers_defined
#define __local___localdep_re_set_registers_defined
#define __localdep_re_set_registers __LIBC_LOCAL_NAME(re_set_registers)
#endif /* !__local___localdep_re_set_registers_defined */
#endif /* !__local_re_set_registers_defined */
