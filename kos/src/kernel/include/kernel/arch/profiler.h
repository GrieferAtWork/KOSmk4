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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_ARCH_PROFILER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_ARCH_PROFILER_H 1

#include <hybrid/compiler.h>

#include <hybrid/typecore.h>

#ifndef __BRANCH_PREDITION_ADDRESS_BASE
#define __BRANCH_PREDITION_ADDRESS_BASE (__CCAST(__ULONGPTR_TYPE__)0)
#endif /* !__BRANCH_PREDITION_ADDRESS_BASE */

#ifndef __BRANCH_PREDITION_ADDRESS_TYPE
#define __BRANCH_PREDITION_ADDRESS_TYPE __ULONGPTR_TYPE__
#endif /* !__BRANCH_PREDITION_ADDRESS_TYPE */

#ifndef __BRANCH_PREDITION_RIGHT_WRONG_TYPE
#define __BRANCH_PREDITION_RIGHT_WRONG_TYPE __ULONGPTR_TYPE__
#endif /* !__BRANCH_PREDITION_RIGHT_WRONG_TYPE */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_ARCH_PROFILER_H */
