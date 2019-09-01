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
#ifndef _BITS_EPOLL_H
#define _BITS_EPOLL_H 1

#include <__stdinc.h>

__DECL_BEGIN

/* Flags to be passed to epoll_create1. */
#undef EPOLL_CLOEXEC
/*[[[enum]]]*/
#ifdef __CC__
enum {
	EPOLL_CLOEXEC = 02000000
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define EPOLL_CLOEXEC EPOLL_CLOEXEC
#else /* __COMPILER_PREFERR_ENUMS */
#define EPOLL_CLOEXEC 02000000
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

__DECL_END

#define __EPOLL_PACKED  __ATTR_PACKED

#endif /* !_BITS_EPOLL_H */
