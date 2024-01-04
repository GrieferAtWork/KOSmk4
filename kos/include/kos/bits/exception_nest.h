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
#ifndef _KOS_BITS_EXCEPTION_NEST_H
#define _KOS_BITS_EXCEPTION_NEST_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/byteorder.h>
#include <hybrid/typecore.h>

#include <bits/types.h>
#include <kos/bits/except-register-state.h> /* __EXCEPT_REGISTER_STATE_TYPE */
#include <kos/bits/exception_data.h>        /* struct exception_data */

#ifndef __EXCEPT_BACKTRACE_SIZE
#if defined(NDEBUG) || defined(NDEBUG_EXCEPT_TRACE)
#define __EXCEPT_BACKTRACE_SIZE 0
#else /* NDEBUG || NDEBUG_EXCEPT_TRACE */
#define __EXCEPT_BACKTRACE_SIZE 16
#endif /* !NDEBUG && !NDEBUG_EXCEPT_TRACE */
#endif /* !__EXCEPT_BACKTRACE_SIZE */

#ifdef __CC__
__DECL_BEGIN

#define _EXCEPTION_NESTING_DATA_SIZE (sizeof(struct _exception_nesting_data) - sizeof(__size_t))
struct _exception_nesting_data {
	__size_t                     en_size;  /* == _EXCEPTION_NESTING_DATA_SIZE */
	__EXCEPT_REGISTER_STATE_TYPE en_state; /* Saved exception state. */
	struct exception_data        en_data;  /* Saved exception data. */
#if __EXCEPT_BACKTRACE_SIZE != 0
	void                        *en_trace[__EXCEPT_BACKTRACE_SIZE]; /* Saved traceback. */
#endif /* __EXCEPT_BACKTRACE_SIZE != 0 */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_BITS_EXCEPTION_NEST_H */
