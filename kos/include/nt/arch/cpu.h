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
#ifndef GUARD_NT_ARCH_CPU_H
#define GUARD_NT_ARCH_CPU_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <asm/intrin.h>

#ifdef __CC__
__DECL_BEGIN

#if defined(__i386__) || defined(__x86_64__)
#ifndef __readfsbyte
#define __readfsbyte(offset)   __rdfsb(offset)
#endif /* !__readfsbyte */
#ifndef __readfsword
#define __readfsword(offset)   __rdfsw(offset)
#endif /* !__readfsword */
#ifndef __readfsdword
#define __readfsdword(offset)  __rdfsl(offset)
#endif /* !__readfsdword */
#ifndef __writefsbyte
#define __writefsbyte(offset)  __wrfsb(offset)
#endif /* !__writefsbyte */
#ifndef __writefsword
#define __writefsword(offset)  __wrfsw(offset)
#endif /* !__writefsword */
#ifndef __writefsdword
#define __writefsdword(offset) __wrfsl(offset)
#endif /* !__writefsdword */
#ifndef __readgsbyte
#define __readgsbyte(offset)   __rdgsb(offset)
#endif /* !__readgsbyte */
#ifndef __readgsword
#define __readgsword(offset)   __rdgsw(offset)
#endif /* !__readgsword */
#ifndef __readgsdword
#define __readgsdword(offset)  __rdgsl(offset)
#endif /* !__readgsdword */
#ifndef __writegsbyte
#define __writegsbyte(offset)  __wrgsb(offset)
#endif /* !__writegsbyte */
#ifndef __writegsword
#define __writegsword(offset)  __wrgsw(offset)
#endif /* !__writegsword */
#ifndef __writegsdword
#define __writegsdword(offset) __wrgsl(offset)
#endif /* !__writegsdword */
#ifdef __x86_64__
#ifndef __readfsqword
#define __readfsqword(offset)  __rdfsq(offset)
#endif /* !__readfsqword */
#ifndef __writefsqword
#define __writefsqword(offset) __wrfsq(offset)
#endif /* !__writefsqword */
#ifndef __readgsqword
#define __readgsqword(offset)  __rdgsq(offset)
#endif /* !__readgsqword */
#ifndef __writegsqword
#define __writegsqword(offset) __wrgsq(offset)
#endif /* !__writegsqword */
#endif /* __x86_64__ */
#endif /* __i386__ || __x86_64__ */

__DECL_END
#endif /* __CC__ */

#endif /* GUARD_NT_ARCH_CPU_H */
