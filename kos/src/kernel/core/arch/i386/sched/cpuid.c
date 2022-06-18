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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_CPUID_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_CPUID_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/x86/cpuid.h>

#include <hybrid/host.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN

/* Basic CPU feature flags (Set of `CPU_BASIC_FEATURE_F*') */
PUBLIC ATTR_PERCPU u16 _thiscpu_x86_cpufeatures ASMNAME("thiscpu_x86_cpufeatures") = CPU_FEATURE_FNONE;
PUBLIC ATTR_PERCPU struct cpuinfo _thiscpu_x86_cpuid ASMNAME("thiscpu_x86_cpuid") = {};

static_assert(OFFSET_CPUID_0A        == offsetof(struct cpuinfo, ci_0a));
static_assert(OFFSET_CPUID_80000000A == offsetof(struct cpuinfo, ci_80000000a));
static_assert(OFFSET_CPUID_1A        == offsetof(struct cpuinfo, ci_1a));
static_assert(OFFSET_CPUID_1B        == offsetof(struct cpuinfo, ci_1b));
static_assert(OFFSET_CPUID_1D        == offsetof(struct cpuinfo, ci_1d));
static_assert(OFFSET_CPUID_1C        == offsetof(struct cpuinfo, ci_1c));
static_assert(OFFSET_CPUID_7D        == offsetof(struct cpuinfo, ci_7d));
static_assert(OFFSET_CPUID_7C        == offsetof(struct cpuinfo, ci_7c));
static_assert(OFFSET_CPUID_7B        == offsetof(struct cpuinfo, ci_7b));
static_assert(OFFSET_CPUID_80000001C == offsetof(struct cpuinfo, ci_80000001c));
static_assert(OFFSET_CPUID_80000001D == offsetof(struct cpuinfo, ci_80000001d));
static_assert(OFFSET_CPUID_0B        == offsetof(struct cpuinfo, ci_0b));
static_assert(OFFSET_CPUID_0D        == offsetof(struct cpuinfo, ci_0d));
static_assert(OFFSET_CPUID_0C        == offsetof(struct cpuinfo, ci_0c));
static_assert(OFFSET_CPUID_80000002A == offsetof(struct cpuinfo, ci_80000002a));
static_assert(OFFSET_CPUID_80000002B == offsetof(struct cpuinfo, ci_80000002b));
static_assert(OFFSET_CPUID_80000002C == offsetof(struct cpuinfo, ci_80000002c));
static_assert(OFFSET_CPUID_80000002D == offsetof(struct cpuinfo, ci_80000002d));
static_assert(OFFSET_CPUID_80000003A == offsetof(struct cpuinfo, ci_80000003a));
static_assert(OFFSET_CPUID_80000003B == offsetof(struct cpuinfo, ci_80000003b));
static_assert(OFFSET_CPUID_80000003C == offsetof(struct cpuinfo, ci_80000003c));
static_assert(OFFSET_CPUID_80000003D == offsetof(struct cpuinfo, ci_80000003d));
static_assert(OFFSET_CPUID_80000004A == offsetof(struct cpuinfo, ci_80000004a));
static_assert(OFFSET_CPUID_80000004B == offsetof(struct cpuinfo, ci_80000004b));
static_assert(OFFSET_CPUID_80000004C == offsetof(struct cpuinfo, ci_80000004c));
static_assert(OFFSET_CPUID_80000004D == offsetof(struct cpuinfo, ci_80000004d));
static_assert(OFFSET_CPUID_80000007D == offsetof(struct cpuinfo, ci_80000007d));
static_assert(SIZEOF_CPUID_CPUINFO   == sizeof(struct cpuinfo));

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_CPUID_C */
