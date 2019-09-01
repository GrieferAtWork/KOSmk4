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
#ifndef _ASM_SOCKIOS_H
#define _ASM_SOCKIOS_H 1

#include <features.h>

/* Socket-level I/O control calls. */
#define FIOSETOWN      0x8901
#define SIOCSPGRP      0x8902
#define FIOGETOWN      0x8903
#define SIOCGPGRP      0x8904
#define SIOCATMARK     0x8905
#ifdef __USE_TIME_BITS64
#define SIOCGSTAMP     0x8908 /* Get stamp (timeval) */
#define SIOCGSTAMPNS   0x8909 /* Get stamp (timespec) */
#else /* __USE_TIME_BITS64 */
#define SIOCGSTAMP     0x8906 /* Get stamp (timeval) */
#define SIOCGSTAMPNS   0x8907 /* Get stamp (timespec) */
#endif /* !__USE_TIME_BITS64 */
#ifdef __USE_KOS
#define SIOCGSTAMP32   0x8906 /* Get stamp (timeval32) */
#define SIOCGSTAMPNS32 0x8907 /* Get stamp (timespec32) */
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#define SIOCGSTAMP64   0x8908 /* Get stamp (timeval64) */
#define SIOCGSTAMPNS64 0x8909 /* Get stamp (timespec64) */
#endif /* __USE_TIME64 */

#endif /* !_ASM_SOCKIOS_H */
