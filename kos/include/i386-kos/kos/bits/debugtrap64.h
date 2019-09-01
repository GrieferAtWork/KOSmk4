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
#ifndef _I386_KOS_KOS_BITS_DEBUGTRAP64_H
#define _I386_KOS_KOS_BITS_DEBUGTRAP64_H 1

#include <__stdinc.h>
#include <hybrid/host.h>
#include <hybrid/__pointer.h>

__DECL_BEGIN

#ifdef __x86_64__
#define __OFFSET_DEBUG_TRAP_REGISTER_NAME  __OFFSET_DEBUG_TRAP_REGISTER64_NAME
#define __OFFSET_DEBUG_TRAP_REGISTER_VALUE __OFFSET_DEBUG_TRAP_REGISTER64_VALUE
#define __SIZEOF_DEBUG_TRAP_REGISTER       __SIZEOF_DEBUG_TRAP_REGISTER64
#define debug_trap_register64 debug_trap_register
#endif /* __x86_64__ */


#define __OFFSET_DEBUG_TRAP_REGISTER64_NAME  0
#define __OFFSET_DEBUG_TRAP_REGISTER64_VALUE 8
#define __SIZEOF_DEBUG_TRAP_REGISTER64       16

#ifdef __CC__
struct debug_trap_register64 /*[PREFIX(dtr_)]*/ {
	/* Trap register pair.
	 * e.g.: { "library", "/lib/libc.so" }
	 * Used to inform a GDB remote of some special trap
	 * event which it may generate a breakpoint for. */
	__HYBRID_PTR64(char const) dtr_name;  /* [0..1][SENTINEL(NULL)] Register name */
	__HYBRID_PTR64(char const) dtr_value; /* [1..1][valid_if(dtr_name)] Register value */
};
#endif /* __CC__ */

__DECL_END

#endif /* !_I386_KOS_KOS_BITS_DEBUGTRAP64_H */
