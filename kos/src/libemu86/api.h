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
#ifndef GUARD_LIBEMU86_API_H
#define GUARD_LIBEMU86_API_H 1

#include <hybrid/host.h>

#define LIBEMU86_WANT_PROTOTYPES
#define LIBEMU86_CONFIG_WANT_32BIT 1
#ifdef __x86_64__
/* Disable 16-bit support on 64-bit x86_64 targets by default. */
#define LIBEMU86_CONFIG_WANT_16BIT 0
#define LIBEMU86_CONFIG_WANT_64BIT 1
#elif defined(__i386__)
#define LIBEMU86_CONFIG_WANT_16BIT 1
/* Disable 64-bit support on 32-bit i386 targets by default. */
#define LIBEMU86_CONFIG_WANT_64BIT 0
#else /* __x86_64__ */
#define LIBEMU86_CONFIG_WANT_16BIT 1
#define LIBEMU86_CONFIG_WANT_64BIT 1
#endif /* !__x86_64__ */

#include <kos/config/config.h> /* Pull in config-specific macro overrides */

#include <libemu86/api.h>

#undef LIBEMU86_DECL
#undef LIBEMU86_IMPL
#define LIBEMU86_DECL __INTDEF
#define LIBEMU86_IMPL __INTERN

#include <hybrid/compiler.h>

#define emu86_opcode_decode libemu86_opcode_decode
#define emu86_modrm_decode  libemu86_modrm_decode

#endif /* !GUARD_LIBEMU86_API_H */
