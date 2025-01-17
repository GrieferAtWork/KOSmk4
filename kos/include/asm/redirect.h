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
#ifndef _ASM_REDIRECT_H
#define _ASM_REDIRECT_H 1

#include <__stdinc.h>

/* Max # of bytes which may be modified by `__arch_redirect()'
 * You  can test if redirection is supported on your arch via:
 * >> #if __ARCH_REDIRECT_MAXBYTES != 0 */
#define __ARCH_REDIRECT_MAXBYTES 0

/* Override up to `__ARCH_REDIRECT_MAXBYTES' bytes at `from_pc' in
 * order to inject instructions  to redirect execution to  instead
 * execute at `to_pc'.  This can  then be used  to implement  live
 * patching of function entries.
 *
 * Architecture-specific constraints may make redirection impossible.
 * To check if redirection can be done, you may test the  possibility
 * with `__arch_redirect_possible()' (if  defined; when not  defined,
 * redirection is always possible)
 *
 * The caller must ensure that memory at `from_pc' is writable. */
#define __arch_redirect(from_pc, to_pc) (void)0

/* The actual number of bytes that will be overwritten  at
 * `from_pc' in order to facilitate the injected redirect. */
#define __arch_redirect_size(from_pc, to_pc) 0

/* Check if redirection is possible; when not defined, redirection is always possible. */
#define __arch_redirect_possible(from_pc, to_pc) 0

#endif /* !_ASM_REDIRECT_H */
