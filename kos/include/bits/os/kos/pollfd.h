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
#ifndef _BITS_OS_KOS_POLLFD_H
#define _BITS_OS_KOS_POLLFD_H 1

#include <__stdinc.h>

#include <bits/types.h>

#define __OFFSET_POLLFD_FD      0
#define __OFFSET_POLLFD_EVENTS  __SIZEOF_FD_T__
#define __OFFSET_POLLFD_REVENTS (__SIZEOF_FD_T__ + 2)
#define __SIZEOF_POLLFD         (__SIZEOF_FD_T__ + 4)
#define __ALIGNOF_POLLFD        __SIZEOF_FD_T__

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("fd")
#pragma push_macro("events")
#pragma push_macro("revents")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef fd
#undef events
#undef revents

struct pollfd /*[PREFIX()]*/ {
	__fd_t         fd;      /* File descriptor to poll.  */
	__INT16_TYPE__ events;  /* Types of events poller cares about (Set of 'POLL*'). */
	__INT16_TYPE__ revents; /* Types of events that actually occurred (Set of 'POLL*'). */
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("revents")
#pragma pop_macro("events")
#pragma pop_macro("fd")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_POLLFD_H */
