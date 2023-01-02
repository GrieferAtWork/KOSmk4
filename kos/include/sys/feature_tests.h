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
/* (#) Portability: OpenSolaris (/usr/src/uts/common/sys/feature_tests.h) */
#ifndef _SYS_FEATURE_TESTS_H
#define _SYS_FEATURE_TESTS_H 1

#include <__stdinc.h>
#include <features.h>
#include <unistd.h> /* For `_XOPEN_VERSION' */

#ifdef __USE_XOPEN2K
#define _XPG6
#endif /* __USE_XOPEN2K */

#ifdef __USE_UNIX98
#define _XPG5
#endif /* __USE_UNIX98 */

#ifdef __USE_XOPEN_EXTENDED
#define _XPG4_2
#endif /* __USE_XOPEN_EXTENDED */

#ifdef __USE_XOPEN
#define _XPG4
#define _XPG3
#endif /* __USE_XOPEN */
#define _RESTRICT_KYWD      __restrict
#define _ISO_CPP_14882_1998 /* __USE_ISOCXX98 */
#ifdef __USE_ISOC99
#define	_ISO_C_9899_1999
#endif /* __USE_ISOC99 */

//#define _DTRACE_VERSION 1

#endif /* !_SYS_FEATURE_TESTS_H */
