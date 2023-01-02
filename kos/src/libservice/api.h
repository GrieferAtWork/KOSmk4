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
#ifndef GUARD_LIBSERVICE_API_H
#define GUARD_LIBSERVICE_API_H 1

#include <__crt.h>
#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/config/config.h> /* Pull in config-specific macro overrides */

#include <libservice/api.h>

#define CC LIBSERVICE_CC

#ifndef NOBLOCK
#define NOBLOCK __NOBLOCK
#endif /* !NOBLOCK */

#ifndef REF
#define REF __REF
#endif /* !REF */

#ifndef WEAK
#define WEAK __WEAK
#endif /* !WEAK */

#ifndef THROWS
#define THROWS __THROWS
#endif /* !THROWS */

#ifndef NOPREEMPT
 /* Here, this means that all posix signals are masked! */
#define NOPREEMPT __NOPREEMPT
#endif /* !NOPREEMPT */

#ifndef FCALL
#define FCALL __FCALL
#endif /* !FCALL */

#endif /* !GUARD_LIBSERVICE_API_H */
