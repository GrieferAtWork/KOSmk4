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
/*!included_by <kos/except.h>*/
#ifndef _KOS_BITS_EXCEPT_H
#define _KOS_BITS_EXCEPT_H 1

/* Helper macros for portably working with error register state,
 * as  well as specifying how an error register state even looks
 * like. */

/*
 * #define EXCEPTION_DATA_POINTERS ...
 *
 * #define __EXCEPT_REGISTER_STATE_TYPE ...
 *
 * #ifdef __USE_KOS_KERNEL
 * #define __SIZEOF_EXCEPT_REGISTER_STATE ...
 * #endif
 *
 * #define __except_register_state_getpc(x)                       (byte_t const *)...
 * #define __except_register_state_setpc(x, value)                ...
 * #define __except_register_state_getsp(x)                       (byte_t const *)...
 * #define __except_register_state_setsp(x, value)                ...
 * #define __except_register_state_get_unwind_exception(x)        (byte_t const *)...
 * #define __except_register_state_set_unwind_exception(x, value) ...
 * #define __except_register_state_get_unwind_switch(x)           (byte_t const *)...
 * #define __except_register_state_set_unwind_switch(x, value)    ...
 *
 */

#endif /* !_KOS_BITS_EXCEPT_H */
