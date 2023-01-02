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
#ifndef _BITS_OS_KOS_SEMBUF_H
#define _BITS_OS_KOS_SEMBUF_H 1

#include <__stdinc.h>

#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("sem_num")
#pragma push_macro("sem_op")
#pragma push_macro("sem_flg")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef sem_num
#undef sem_op
#undef sem_flg

/* Structure used for argument to `semop' to describe operations.  */
struct sembuf {
	__uint16_t sem_num; /* semaphore number */
	__int16_t  sem_op;  /* semaphore operation */
	__int16_t  sem_flg; /* operation flag */
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("sem_flg")
#pragma pop_macro("sem_op")
#pragma pop_macro("sem_num")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */


#endif /* !_BITS_OS_KOS_SEMBUF_H */
