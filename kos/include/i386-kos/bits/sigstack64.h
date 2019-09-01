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
#ifndef _BITS_SIGSTACK64_H
#define _BITS_SIGSTACK64_H 1

#include <__stdinc.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>
#include <hybrid/__pointer.h>

__SYSDECL_BEGIN

#ifdef __x86_64__

#ifndef __sigstack_defined
#define __sigstack_defined 1
#define __OFFSET_SIGSTACK_SP       __OFFSET_SIGSTACK64_SP
#define __OFFSET_SIGSTACK_ONSTACK  __OFFSET_SIGSTACK64_ONSTACK
#define __SIZEOF_SIGSTACK          __SIEZOF_SIGSTACK64
#define sigstack64                 sigstack
#endif /* !__sigstack_defined */

#ifndef __sigaltstack_defined
#define __sigaltstack_defined 1
#define __OFFSET_SIGALTSTACK_SP    __OFFSET_SIGALTSTACK64_SP
#define __OFFSET_SIGALTSTACK_FLAGS __OFFSET_SIGALTSTACK64_FLAGS
#define __OFFSET_SIGALTSTACK_SIZE  __OFFSET_SIGALTSTACK64_SIZE
#define __SIZEOF_SIGALTSTACK       __SIEZOF_SIGALTSTACK64
#define sigaltstack64              sigaltstack
#endif /* !__sigaltstack_defined */

#ifndef __stack_t_defined
#define __stack_t_defined 1
#ifdef __CC__
struct sigaltstack;
typedef struct sigaltstack stack_t;
#endif /* __CC__ */
#endif /* !__stack_t_defined */

#endif /* __x86_64__ */


#define __OFFSET_SIGSTACK64_SP       0
#define __OFFSET_SIGSTACK64_ONSTACK  8
#define __SIEZOF_SIGSTACK64          16

#ifdef __CC__
/* Structure describing a signal stack (obsolete). */
struct sigstack64 /*[PREFIX(ss_)]*/ {
	__HYBRID_PTR64(void) ss_sp;      /* Signal stack pointer. */
	int                  ss_onstack; /* Nonzero if executing on this stack. */
#if 8 > __SIZEOF_INT__
	__BYTE_TYPE__ __ss_pad[8 - __SIZEOF_INT__];
#endif /* 8 > __SIZEOF_INT__ */
};
#endif /* __CC__ */


#define __OFFSET_SIGALTSTACK64_SP    0
#define __OFFSET_SIGALTSTACK64_FLAGS 8
#define __OFFSET_SIGALTSTACK64_SIZE  16
#define __SIEZOF_SIGALTSTACK64       24

#ifdef __CC__
/* Alternate, preferred interface. */
struct sigaltstack64 /*[PREFIX(ss_)]*/ {
	__HYBRID_PTR64(void) ss_sp;
	int                  ss_flags;
#if 8 > __SIZEOF_INT__
	__BYTE_TYPE__      __ss_pad[8 - __SIZEOF_INT__];
#endif
	__ULONG64_TYPE__     ss_size;
};
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_BITS_SIGSTACK64_H */
