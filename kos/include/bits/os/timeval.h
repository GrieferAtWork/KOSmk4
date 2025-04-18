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
/*!included_by <sys/resource.h>*/
/*!included_by <sys/select.h>*/
/*!included_by <timeval-utils.h>*/
#ifndef _BITS_OS_TIMEVAL_H
#define _BITS_OS_TIMEVAL_H 1

/* File:
 *    <bits/os/timeval.h>
 *
 * Definitions:
 *    struct timeval {
 *        time_t      tv_sec;
 *        suseconds_t tv_usec;   // unsigned with __USE_KOS_ALTERATIONS
 *    };
 *    #ifdef __USE_TIME64
 *    struct timeval64  {
 *        time64_t    tv_sec;
 *        suseconds_t tv_usec;   // unsigned with __USE_KOS_ALTERATIONS
 *    };
 *    #endif // __USE_TIME64
 */

#include <__stdinc.h>

/**/
#include <bits/os/generic/timeval.h>

#endif /* !_BITS_OS_TIMEVAL_H */
