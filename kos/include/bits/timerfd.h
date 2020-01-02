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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_TIMERFD_H
#define _BITS_TIMERFD_H 1

#include <__stdinc.h>

/* Bits to be set in the FLAGS parameter of `timerfd_create'. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	TFD_CLOEXEC  = 02000000,
	TFD_NONBLOCK = 00004000
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define TFD_CLOEXEC  TFD_CLOEXEC
#define TFD_NONBLOCK TFD_NONBLOCK
#else /* __COMPILER_PREFERR_ENUMS */
#define TFD_CLOEXEC  02000000
#define TFD_NONBLOCK 00004000
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

#endif /* !_BITS_TIMERFD_H */
