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
#ifndef _I386_KOS_KOS_BITS_UKERN_H
#define _I386_KOS_KOS_BITS_UKERN_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <asm/intrin.h>

#ifdef __x86_64__
#define userkern_self()             ((struct userkern *)__rdgsbase())
#define userkern_valid()            (__rdgsbaseq() >= __UINT64_C(0xffff800000000000))
#define userkern_getfield(field)    ((__typeof__(((struct userkern *)0)->field))__rdgsptr(__builtin_ofgsetof(struct userkern, field)))
#define userkern_setfield(field, v) __wrgsptr(__builtin_ofgsetof(struct userkern, field), (void *)(v))
#else /* __x86_64__ */
#define userkern_self()             ((struct userkern *)__rdfsbase())
#define userkern_valid()            (__rdfsbasel() >= __UINT32_C(0xc0000000))
#define userkern_getfield(field)    ((__typeof__(((struct userkern *)0)->field))__rdfsptr(__builtin_offsetof(struct userkern, field)))
#define userkern_setfield(field, v) __wrfsptr(__builtin_offsetof(struct userkern, field), (void *)(v))
#endif /* !__x86_64__ */


#endif /* !_I386_KOS_KOS_BITS_UKERN_H */
