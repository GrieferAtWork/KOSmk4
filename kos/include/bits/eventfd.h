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
#ifndef _BITS_EVENTFD_H
#define _BITS_EVENTFD_H 1

#include <__stdinc.h>

__DECL_BEGIN

/* Flags for eventfd. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	EFD_SEMAPHORE = 0x00001,
	EFD_NONBLOCK  = 0x00800,
	EFD_CLOEXEC   = 0x80000
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define EFD_SEMAPHORE EFD_SEMAPHORE
#define EFD_NONBLOCK  EFD_NONBLOCK
#define EFD_CLOEXEC   EFD_CLOEXEC
#else /* __COMPILER_PREFERR_ENUMS */
#define EFD_SEMAPHORE 0x00001
#define EFD_NONBLOCK  0x00800
#define EFD_CLOEXEC   0x80000
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

__DECL_END

#endif /* !_BITS_EVENTFD_H */
