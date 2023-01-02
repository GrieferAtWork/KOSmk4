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
#ifndef _BITS_OS_GENERIC_WAIT_H
#define _BITS_OS_GENERIC_WAIT_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/__bitfield.h>
#include <hybrid/byteorder.h>
#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("wait")
#pragma push_macro("w_status")
#pragma push_macro("w_termsig")
#pragma push_macro("w_coredump")
#pragma push_macro("w_retcode")
#pragma push_macro("w_stopsig")
#pragma push_macro("w_stopval")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
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
		__HYBRID_BITFIELD8_T w_termsig  : 7; /* Terminating signal. */
		__HYBRID_BITFIELD8_T w_coredump : 1; /* Set if dumped core. */
		__UINT8_TYPE__       w_retcode;      /* Return code if exited normally. */
		__UINT16_TYPE__    __w_pad0;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		__UINT16_TYPE__    __w_pad0;
		__UINT8_TYPE__       w_retcode;      /* Return code if exited normally. */
		__HYBRID_BITFIELD8_T w_coredump : 1; /* Set if dumped core. */
		__HYBRID_BITFIELD8_T w_termsig  : 7; /* Terminating signal. */
#endif /* Endian... */
	};
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		__UINT8_TYPE__       w_stopval; /* W_STOPPED if stopped. */
		__UINT8_TYPE__       w_stopsig; /* Stopping signal. */
		__UINT16_TYPE__    __w_pad1;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		__UINT16_TYPE__    __w_pad1;
		__UINT8_TYPE__       w_stopsig; /* Stopping signal. */
		__UINT8_TYPE__       w_stopval; /* W_STOPPED if stopped. */
#endif /* Endian... */
	};
#endif /* __COMPILER_HAVE_TRANSPARENT_STRUCT */
#if (!defined(__USE_KOS_ALTERATIONS) || \
     !defined(__COMPILER_HAVE_TRANSPARENT_STRUCT))
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		__HYBRID_BITFIELD8_T __w_termsig  : 7; /* Terminating signal. */
		__HYBRID_BITFIELD8_T __w_coredump : 1; /* Set if dumped core. */
		__UINT8_TYPE__       __w_retcode;      /* Return code if exited normally. */
		__UINT16_TYPE__      __w_pad0;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		__UINT16_TYPE__      __w_pad0;
		__UINT8_TYPE__       __w_retcode;      /* Return code if exited normally. */
		__HYBRID_BITFIELD8_T __w_coredump : 1; /* Set if dumped core. */
		__HYBRID_BITFIELD8_T __w_termsig  : 7; /* Terminating signal. */
#endif /* Endian... */
	} __wait_terminated;
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		__UINT8_TYPE__      __w_stopval; /* W_STOPPED if stopped. */
		__UINT8_TYPE__      __w_stopsig; /* Stopping signal. */
		__UINT16_TYPE__     __w_pad1;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		__UINT16_TYPE__     __w_pad1;
		__UINT8_TYPE__      __w_stopsig; /* Stopping signal. */
		__UINT8_TYPE__      __w_stopval; /* W_STOPPED if stopped. */
#endif /* Endian... */
	} __wait_stopped;
#ifndef __COMPILER_HAVE_TRANSPARENT_STRUCT
#define w_termsig  __wait_terminated.__w_termsig
#define w_coredump __wait_terminated.__w_coredump
#define w_retcode  __wait_terminated.__w_retcode
#define w_stopsig  __wait_stopped.__w_stopsig
#define w_stopval  __wait_stopped.__w_stopval
#endif /* !__COMPILER_HAVE_TRANSPARENT_STRUCT */
#endif /* !__USE_KOS_ALTERATIONS || !__COMPILER_HAVE_TRANSPARENT_STRUCT */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("w_retcode")
#pragma pop_macro("w_coredump")
#pragma pop_macro("w_termsig")
#pragma pop_macro("w_status")
#pragma pop_macro("w_stopsig")
#pragma pop_macro("w_stopval")
#pragma pop_macro("wait")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_GENERIC_WAIT_H */
