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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_RTM_H
#define GUARD_LIBC_LIBC_ARCH_I386_RTM_H 1

#include <hybrid/compiler.h>

/*[[[config CONFIG_LIBC_SUPPORTS_HARDWARE_RTM = true
 * Enable support for hardware RTM (s.a. `CPUID_7B_RTM')
 * ]]]*/
#ifdef CONFIG_NO_LIBC_SUPPORTS_HARDWARE_RTM
#undef CONFIG_LIBC_SUPPORTS_HARDWARE_RTM
#elif !defined(CONFIG_LIBC_SUPPORTS_HARDWARE_RTM)
#define CONFIG_LIBC_SUPPORTS_HARDWARE_RTM
#elif (-CONFIG_LIBC_SUPPORTS_HARDWARE_RTM - 1) == -1
#undef CONFIG_LIBC_SUPPORTS_HARDWARE_RTM
#define CONFIG_NO_LIBC_SUPPORTS_HARDWARE_RTM
#endif /* ... */
/*[[[end]]]*/


#ifdef CONFIG_LIBC_SUPPORTS_HARDWARE_RTM
/* environ variable:
 * The  first  time  that `rtm_begin()'  is  called, this
 * variable is searched for via `getenv(ENVIRON_HW_RTM)'.
 *  - If the variable isn't defined, check `cpuid' for RTM support
 *  - If the variable is defined as "0", disable hardware RTM
 *    and always make use of RTM emulation
 *  - If the variable is defined as "1", enable hardware RTM
 *    Warning: If you do this, your program may still run correctly,
 *             though still be using emulated RTM, as the KOS kernel
 *             emulates the instructions related to RTM if executing
 *             them normally results in a #UD
 *    Note though that the ability to trigger a #UD from executing RTM
 *    instructions isn't guarantied to happen on every X86 CPU, so you
 *    should really only set "HW_RTM=1" if you know better than cpuid!
 *  - If the variable is defined as anything else, also check `cpuid'
 *    for RTM support
 */
#define ENVIRON_HW_RTM "HW_RTM"
#endif /* CONFIG_LIBC_SUPPORTS_HARDWARE_RTM */


#endif /* GUARD_LIBC_LIBC_ARCH_I386_RTM_H */
