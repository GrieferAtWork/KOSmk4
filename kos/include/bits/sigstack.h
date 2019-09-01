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
#ifndef _BITS_SIGSTACK_H
#define _BITS_SIGSTACK_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>


__SYSDECL_BEGIN

#ifndef __sigstack_defined
#define __sigstack_defined 1
#define __OFFSET_SIGSTACK_SP       0
#define __OFFSET_SIGSTACK_ONSTACK  __SIZEOF_POINTER__
#define __SIZEOF_SIGSTACK         (__SIZEOF_POINTER__*2)
#ifdef __CC__
/* Structure describing a signal stack (obsolete). */
struct sigstack /*[PREFIX(ss_)]*/ {
	void           *ss_sp;      /* Signal stack pointer. */
	int             ss_onstack; /* Nonzero if executing on this stack. */
#if __SIZEOF_POINTER__ > __SIZEOF_INT__
	__BYTE_TYPE__ __ss_pad[__SIZEOF_POINTER__ - __SIZEOF_INT__];
#endif /* __SIZEOF_POINTER__ > __SIZEOF_INT__ */
};
#endif /* __CC__ */
#endif /* !__sigstack_defined */


#ifndef __sigaltstack_defined
#define __sigaltstack_defined 1
#define __OFFSET_SIGALTSTACK_SP    0
#define __OFFSET_SIGALTSTACK_FLAGS 4
#define __OFFSET_SIGALTSTACK_SIZE  8
#define __SIZEOF_SIGALTSTACK       12
#ifdef __CC__
/* Alternate, preferred interface. */
struct sigaltstack /*[PREFIX(ss_)]*/ {
	void            *ss_sp;
	int              ss_flags;
#if __SIZEOF_POINTER__ > __SIZEOF_INT__
	__BYTE_TYPE__  __ss_pad[__SIZEOF_POINTER__ - __SIZEOF_INT__];
#endif /* __SIZEOF_POINTER__ > __SIZEOF_INT__ */
	__ULONG32_TYPE__ ss_size;
};
#endif /* __CC__ */
#endif /* !__sigaltstack_defined */


#ifndef __stack_t_defined
#define __stack_t_defined 1
#ifdef __CC__
struct sigaltstack;
typedef struct sigaltstack stack_t;
#endif /* __CC__ */
#endif /* !__stack_t_defined */


/* Possible values for `ss_flags.'. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	SS_ONSTACK = 1,
	SS_DISABLE = 2
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define SS_ONSTACK SS_ONSTACK
#define SS_DISABLE SS_DISABLE
#else /* __COMPILER_PREFERR_ENUMS */
#define SS_ONSTACK 1
#define SS_DISABLE 2
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


#ifndef MINSIGSTKSZ
#define MINSIGSTKSZ 2048 /* Minimum stack size for a signal handler. */
#endif /* !MINSIGSTKSZ */

#ifndef SIGSTKSZ
#define SIGSTKSZ    8192 /* System default stack size. */
#endif /* !SIGSTKSZ */


__SYSDECL_END

#endif /* !_BITS_SIGSTACK_H */
