/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_WAITSTATUS_H
#define _BITS_WAITSTATUS_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/waitflags.h>
#ifdef __USE_MISC
#include <hybrid/byteorder.h>
#endif /* __USE_MISC */

__SYSDECL_BEGIN

/* NOTE: This file based on the GLIBC header of the same name: */
/* Definitions of status bits for `wait' et al.
   Copyright (C) 1992-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


/* Everything extant so far uses these same bits. */
#ifndef __WEXITSTATUS
#define __WEXITSTATUS(status)  (((status)&0xff00)>>8)    /* If WIFEXITED(STATUS), the low-order 8 bits of the status. */
#endif /* !__WEXITSTATUS */
#ifndef __WTERMSIG
#define __WTERMSIG(status)      ((status)&0x7f)          /* If WIFSIGNALED(STATUS), the terminating signal. */
#endif /* !__WTERMSIG */
#ifndef __WSTOPSIG
#define __WSTOPSIG(status)      __WEXITSTATUS(status)    /* If WIFSTOPPED(STATUS), the signal that stopped the child. */
#endif /* !__WSTOPSIG */
#ifndef __WIFEXITED
#define __WIFEXITED(status)    (__WTERMSIG(status)==0)   /* Nonzero if STATUS indicates normal termination. */
#endif /* !__WIFEXITED */
#ifndef __WIFSIGNALED
#define __WIFSIGNALED(status)  (((signed char)(((status)&0x7f)+1)>>1)>0) /* Nonzero if STATUS indicates termination by a signal. */
#endif /* !__WIFSIGNALED */
#ifndef __WIFSTOPPED
#define __WIFSTOPPED(status)   (((status)&0xff)==0x7f)   /* Nonzero if STATUS indicates the child is stopped. */
#endif /* !__WIFSTOPPED */
#ifndef __WCOREDUMP
#define __WCOREDUMP(status)    ((status)&__WCOREFLAG)    /* Nonzero if STATUS indicates the child dumped core. */
#endif /* !__WCOREDUMP */
#ifdef WCONTINUED
#ifndef __WIFCONTINUED
#define __WIFCONTINUED(status) ((status)==__W_CONTINUED) /* Nonzero if STATUS indicates the child continued after a stop. */
#endif /* !__WIFCONTINUED */
#endif /* WCONTINUED */

/* Macros for constructing status values. */
#ifndef __W_EXITCODE
#define __W_EXITCODE(ret,sig) ((ret)<<8|(sig))
#endif /* !__W_EXITCODE */
#ifndef __W_STOPCODE
#define __W_STOPCODE(sig)     ((sig)<<8|0x7f)
#endif /* !__W_STOPCODE */
#ifndef __W_CONTINUED
#define __W_CONTINUED           0xffff
#endif /* !__W_CONTINUED */
#ifndef __WCOREFLAG
#define __WCOREFLAG             0x80
#endif /* !__WCOREFLAG */

#ifdef __CC__
#ifdef __USE_MISC
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("wait")
#pragma push_macro("w_status")
#pragma push_macro("w_termsig")
#pragma push_macro("w_coredump")
#pragma push_macro("w_retcode")
#pragma push_macro("w_stopsig")
#pragma push_macro("w_stopval")
#endif
#undef wait
#undef w_status
#undef w_termsig
#undef w_coredump
#undef w_retcode
#undef w_stopsig
#undef w_stopval
union wait {
	int w_status;
#ifdef __COMPILER_HAVE_TRANSPARENT_STRUCT
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		unsigned int w_termsig  : 7; /* Terminating signal. */
		unsigned int w_coredump : 1; /* Set if dumped core. */
		unsigned int w_retcode  : 8; /* Return code if exited normally. */
		unsigned int __w_pad0   : 16;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		unsigned int __w_pad0   : 16;
		unsigned int w_retcode  : 8; /* Return code if exited normally. */
		unsigned int w_coredump : 1; /* Set if dumped core. */
		unsigned int w_termsig  : 7; /* Terminating signal. */
#endif /* Endian... */
	};
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		unsigned int w_stopval : 8; /* W_STOPPED if stopped. */
		unsigned int w_stopsig : 8; /* Stopping signal. */
		unsigned int __w_pad1  : 16;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		unsigned int __w_pad1  : 16;
		unsigned int w_stopsig : 8; /* Stopping signal. */
		unsigned int w_stopval : 8; /* W_STOPPED if stopped. */
#endif /* Endian... */
	};
#endif /* __COMPILER_HAVE_TRANSPARENT_STRUCT */
#if !defined(__USE_KOS) || \
	!defined(__COMPILER_HAVE_TRANSPARENT_STRUCT)
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		unsigned int __w_termsig  : 7; /* Terminating signal. */
		unsigned int __w_coredump : 1; /* Set if dumped core. */
		unsigned int __w_retcode  : 8; /* Return code if exited normally. */
		unsigned int __w_pad0     : 16;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		unsigned int __w_pad0     : 16;
		unsigned int __w_retcode  : 8; /* Return code if exited normally. */
		unsigned int __w_coredump : 1; /* Set if dumped core. */
		unsigned int __w_termsig  : 7; /* Terminating signal. */
#endif /* Endian... */
	} __wait_terminated;
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		unsigned int __w_stopval : 8; /* W_STOPPED if stopped. */
		unsigned int __w_stopsig : 8; /* Stopping signal. */
		unsigned int __w_pad1    : 16;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		unsigned int __w_pad1    : 16;
		unsigned int __w_stopsig : 8; /* Stopping signal. */
		unsigned int __w_stopval : 8; /* W_STOPPED if stopped. */
#endif /* Endian... */
	} __wait_stopped;
#ifndef __COMPILER_HAVE_TRANSPARENT_STRUCT
#define w_termsig  __wait_terminated.__w_termsig
#define w_coredump __wait_terminated.__w_coredump
#define w_retcode  __wait_terminated.__w_retcode
#define w_stopsig  __wait_stopped.__w_stopsig
#define w_stopval  __wait_stopped.__w_stopval
#endif /* !__COMPILER_HAVE_TRANSPARENT_STRUCT */
#endif /* !__USE_KOS || !__COMPILER_HAVE_TRANSPARENT_STRUCT */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("w_retcode")
#pragma pop_macro("w_coredump")
#pragma pop_macro("w_termsig")
#pragma pop_macro("w_status")
#pragma pop_macro("w_stopsig")
#pragma pop_macro("w_stopval")
#pragma pop_macro("wait")
#endif
#endif /* __USE_MISC */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_BITS_WAITSTATUS_H */
