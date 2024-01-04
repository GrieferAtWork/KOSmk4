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
/* (#) Portability: Linux (/usr/include/[...]/asm/sockios.h) */
#ifndef _ASM_SOCKIOS_H
#define _ASM_SOCKIOS_H 1

#include <__stdinc.h>

#include <asm/os/socket-ioctls.h>

#if !defined(FIOSETOWN) && defined(__FIOSETOWN)
#define FIOSETOWN  __FIOSETOWN  /* ... */
#endif /* !FIOSETOWN && __FIOSETOWN */
#if !defined(SIOCSPGRP) && defined(__SIOCSPGRP)
#define SIOCSPGRP  __SIOCSPGRP  /* ... */
#endif /* !SIOCSPGRP && __SIOCSPGRP */
#if !defined(FIOGETOWN) && defined(__FIOGETOWN)
#define FIOGETOWN  __FIOGETOWN  /* ... */
#endif /* !FIOGETOWN && __FIOGETOWN */
#if !defined(SIOCGPGRP) && defined(__SIOCGPGRP)
#define SIOCGPGRP  __SIOCGPGRP  /* ... */
#endif /* !SIOCGPGRP && __SIOCGPGRP */
#if !defined(SIOCATMARK) && defined(__SIOCATMARK)
#define SIOCATMARK __SIOCATMARK /* ... */
#endif /* !SIOCATMARK && __SIOCATMARK */
 #if !defined(SIOCGSTAMP_OLD) && defined(__SIOCGSTAMP32)
#define SIOCGSTAMP_OLD   __SIOCGSTAMP32   /* [struct timeval *arg] Get stamp */
#endif /* !SIOCGSTAMP_OLD && __SIOCGSTAMP32 */
#if !defined(SIOCGSTAMPNS_OLD) && defined(__SIOCGSTAMPNS32)
#define SIOCGSTAMPNS_OLD __SIOCGSTAMPNS32 /* [struct timespec *arg] Get stamp */
#endif /* !SIOCGSTAMPNS_OLD && __SIOCGSTAMPNS32 */

#endif /* !_ASM_SOCKIOS_H */
