/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: GNU C Library (/include/stdc-predef.h) */
/* (#) Portability: libc6         (/include/stdc-predef.h) */
/* (#) Portability: musl libc     (/include/stdc-predef.h) */
#ifndef _STDC_PREDEF_H
#define _STDC_PREDEF_H 1

/* Special case: This header (is|may be) included by a compiler as the first  thing
 *               that's  done when  compilation starts.  As such,  we don't include
 *               <__stdinc.h> in here,  since that  would mean there  (may) not  be
 *               any way to prevent that header from being included, or to override
 *               some of its macros on a per-file basis (also: doing so would  mean
 *               a lot of (possibly) unnecessary overhead) */


#ifdef __GCC_IEC_559
#if (__GCC_IEC_559 + 0) > 0
#define __STDC_IEC_559__ 1
#endif /* __GCC_IEC_559 > 0 */
#else /* __GCC_IEC_559 */
#define __STDC_IEC_559__ 1
#endif /* !__GCC_IEC_559 */

#ifdef __GCC_IEC_559_COMPLEX
#if (__GCC_IEC_559_COMPLEX + 0) > 0
#define __STDC_IEC_559_COMPLEX__ 1
#endif /* __GCC_IEC_559_COMPLEX > 0 */
#else /* __GCC_IEC_559_COMPLEX */
#define __STDC_IEC_559_COMPLEX__ 1
#endif /* !__GCC_IEC_559_COMPLEX */

#define __STDC_ISO_10646__ 201505L /* KOS's wchar_t uses unicode */

/* #undef __STDC_NO_COMPLEX__ */ /* We do have <complex.h> support! */
/* #undef __STDC_NO_THREADS__ */ /* We do have <threads.h> support! */


#endif /* !_STDC_PREDEF_H */
