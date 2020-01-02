/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_FSGSBASE_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_FSGSBASE_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <hybrid/host.h>
#include <kernel/arch/fsgsbase.h>

#ifdef __x86_64__
DECL_BEGIN

#ifdef __CC__
/* Patch one of the (rd|wr)(fs|gs)base instructions at `pc' to instead
 * become a call to one of the internal functions capable of emulating
 * the behavior of the instruction.
 * WARNING: Only the 64-bit variants of these instructions can be patched!
 *          The 32-bit variants cannot.
 * Before using this function, the caller should check that fsgsbase really
 * isn't supported by the host CPU, as indicated by `CPUID_7B_FSGSBASE'
 * @return: true:  Successfully patched the given code location.
 * @return: false: The given code location was already patched,
 *                 or isn't one of the above instructions. */
FUNDEF NOBLOCK bool NOTHROW(FCALL x86_fsgsbase_patch)(void *__restrict pc);
#endif /* __CC__ */

DECL_END
#endif /* __x86_64__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_FSGSBASE_H */
