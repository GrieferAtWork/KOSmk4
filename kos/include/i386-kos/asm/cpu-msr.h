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
#ifndef _I386_KOS_ASM_CPU_MSR_H
#define _I386_KOS_ASM_CPU_MSR_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

/* MSR Indices */

#define IA32_P5_MC_ADDR           __UINT32_C(0x00000000)
#define IA32_P5_MC_TYPE           __UINT32_C(0x00000001)
#define IA32_MONITOR_FILTER_SIZE  __UINT32_C(0x00000006)
#define IA32_TIME_STAMP_COUNTER   __UINT32_C(0x00000010)
#define IA32_PLATFORM_ID          __UINT32_C(0x00000017)
#define IA32_APIC_BASE            __UINT32_C(0x0000001b)
#define     IA32_APIC_BASE_BSP    __UINT64_C(0x0000000000000100) /* [bit(8)] BSP flag (R/W) */
#define     IA32_APIC_BASE_X2APIC __UINT64_C(0x0000000000000400) /* [bit(10)] Enable x2APIC mode */
#define     IA32_APIC_BASE_GLOBAL __UINT64_C(0x0000000000000800) /* [bit(11)] APIC Global Enable (R/W) */
#define IA32_FEATURE_CONTROL      __UINT32_C(0x0000003a)
#define IA32_TSC_ADJUST           __UINT32_C(0x0000003b)
#define IA32_SPEC_CTRL            __UINT32_C(0x00000048)
#define IA32_PRED_CMD             __UINT32_C(0x00000049)
#define IA32_BIOS_UPDT_TRIG       __UINT32_C(0x00000079)
#define IA32_BIOS_SIGN_ID         __UINT32_C(0x0000008b)
#define IA32_SGXLEPUBKEYHASH0     __UINT32_C(0x0000008c)
#define IA32_SGXLEPUBKEYHASH1     __UINT32_C(0x0000008d)
#define IA32_SGXLEPUBKEYHASH2     __UINT32_C(0x0000008e)
#define IA32_SGXLEPUBKEYHASH3     __UINT32_C(0x0000008f)
#define IA32_SMM_MONITOR_CTL      __UINT32_C(0x0000009b)
#define IA32_SMBASE               __UINT32_C(0x0000009e)
#define IA32_PMC0                 __UINT32_C(0x000000c1)
#define IA32_PMC1                 __UINT32_C(0x000000c2)
#define IA32_PMC2                 __UINT32_C(0x000000c3)
#define IA32_PMC3                 __UINT32_C(0x000000c4)
#define IA32_PMC4                 __UINT32_C(0x000000c5)
#define IA32_PMC5                 __UINT32_C(0x000000c6)
#define IA32_PMC6                 __UINT32_C(0x000000c7)
#define IA32_PMC7                 __UINT32_C(0x000000c8)
#define IA32_UMWAIT_CONTROL       __UINT32_C(0x000000e1)
#define IA32_MPERF                __UINT32_C(0x000000e7)
#define IA32_APERF                __UINT32_C(0x000000e8)
#define IA32_MTRRCAP              __UINT32_C(0x000000fe)
#define IA32_ARCH_CAPABILITIES    __UINT32_C(0x0000010a)
#define IA32_FLUSH_CMD            __UINT32_C(0x0000010b)
#define IA32_SYSENTER_CS          __UINT32_C(0x00000174)
#define IA32_SYSENTER_ESP         __UINT32_C(0x00000175)
#define IA32_SYSENTER_EIP         __UINT32_C(0x00000176)
#define IA32_MCG_CAP              __UINT32_C(0x00000179)
#define IA32_MCG_STATUS           __UINT32_C(0x0000017a)
#define IA32_MCG_CTL              __UINT32_C(0x0000017b)
#define IA32_PERFEVTSEL0          __UINT32_C(0x00000186)
#define IA32_PERFEVTSEL1          __UINT32_C(0x00000187)
#define IA32_PERFEVTSEL2          __UINT32_C(0x00000188)
#define IA32_PERFEVTSEL3          __UINT32_C(0x00000189)
#define IA32_PERF_STATUS          __UINT32_C(0x00000198)
#define IA32_PERF_CTL             __UINT32_C(0x00000199)
#define IA32_CLOCK_MODULATION     __UINT32_C(0x0000019a)
#define IA32_THERM_INTERRUPT      __UINT32_C(0x0000019b)
#define IA32_THERM_STATUS         __UINT32_C(0x0000019c)
#define IA32_MISC_ENABLE          __UINT32_C(0x000001a0)
#define     IA32_MISC_ENABLE_FAST_STRING        __UINT64_C(0x0000000000000001) /* [bit(0)] Fast strings enable */
#define     IA32_MISC_ENABLE_TCC                __UINT64_C(0x0000000000000002) /* [bit(1)] */
#define     IA32_MISC_ENABLE_X87_COMPAT         __UINT64_C(0x0000000000000004) /* [bit(2)] FOPCODE compatibility mode enable */
#define     IA32_MISC_ENABLE_TM1                __UINT64_C(0x0000000000000008) /* [bit(3)] Thermal monitor enable */
#define     IA32_MISC_ENABLE_SPLIT_LOCK_DISABLE __UINT64_C(0x0000000000000010) /* [bit(4)] Split-lock disable */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000000000000020)  * [bit(5)] */
#define     IA32_MISC_ENABLE_L3CACHE_DISABLE    __UINT64_C(0x0000000000000040) /* [bit(6)] */
#define     IA32_MISC_ENABLE_EMON               __UINT64_C(0x0000000000000080) /* [bit(7)] */
#define     IA32_MISC_ENABLE_SUPPRESS_LOCK      __UINT64_C(0x0000000000000100) /* [bit(8)] Bus lock on cache line splits disable */
#define     IA32_MISC_ENABLE_PREFETCH_DISABLE   __UINT64_C(0x0000000000000200) /* [bit(9)] Hardware prefetch disable */
#define     IA32_MISC_ENABLE_FERR               __UINT64_C(0x0000000000000400) /* [bit(10)] */
#define     IA32_MISC_ENABLE_FERR_MULTIPLEX     __UINT64_C(0x0000000000000400) /* [bit(10)] */
#define     IA32_MISC_ENABLE_BTS_UNAVAIL        __UINT64_C(0x0000000000000800) /* [bit(11)] */
#define     IA32_MISC_ENABLE_PEBS_UNAVAIL       __UINT64_C(0x0000000000001000) /* [bit(12)] */
#define     IA32_MISC_ENABLE_TM2                __UINT64_C(0x0000000000002000) /* [bit(13)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000000000004000)  * [bit(14)] */
#define     IA32_MISC_ENABLE_GV12_LEGACY_ENABLE __UINT64_C(0x0000000000008000) /* [bit(15)] GV1/2 legacy enable */
#define     IA32_MISC_ENABLE_ENHANCED_SPEEDSTEP __UINT64_C(0x0000000000010000) /* [bit(16)][requires(CPUID_1C_EST)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000000000020000)  * [bit(17)] */
#define     IA32_MISC_ENABLE_MWAIT              __UINT64_C(0x0000000000040000) /* [bit(18)] MONITOR/MWAIT s/m enable */
#define     IA32_MISC_ENABLE_ADJ_PREF_DISABLE   __UINT64_C(0x0000000000080000) /* [bit(19)] Adjacent sector prefetch disable */
#define     IA32_MISC_ENABLE_SPEEDSTEP_LOCK     __UINT64_C(0x0000000000100000) /* [bit(20)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000000000200000)  * [bit(21)] */
#define     IA32_MISC_ENABLE_LIMIT_CPUID        __UINT64_C(0x0000000000400000) /* [bit(22)] */
#define     IA32_MISC_ENABLE_XTPR_DISABLE       __UINT64_C(0x0000000000800000) /* [bit(23)][requires(CPUID_1C_XTPR)] */
#define     IA32_MISC_ENABLE_L1D_CONTEXT        __UINT64_C(0x0000000001000000) /* [bit(24)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000000002000000)  * [bit(25)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000000004000000)  * [bit(26)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000000008000000)  * [bit(27)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000000010000000)  * [bit(28)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000000020000000)  * [bit(29)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000000040000000)  * [bit(30)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000000080000000)  * [bit(31)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000000100000000)  * [bit(32)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000000200000000)  * [bit(33)] */
#define     IA32_MISC_ENABLE_XD_DISABLE         __UINT64_C(0x0000000400000000) /* [bit(34)][requires(CPUID_80000001D_NX)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000000800000000)  * [bit(35)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000001000000000)  * [bit(36)] */
#define     IA32_MISC_ENABLE_DCU_PREF_DISABLE   __UINT64_C(0x0000002000000000) /* [bit(37)] */
#define     IA32_MISC_ENABLE_TURBO_DISABLE      __UINT64_C(0x0000004000000000) /* [bit(38)] */
#define     IA32_MISC_ENABLE_IP_PREF_DISABLE    __UINT64_C(0x0000008000000000) /* [bit(39)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000010000000000)  * [bit(40)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000020000000000)  * [bit(41)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000040000000000)  * [bit(42)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000080000000000)  * [bit(43)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000100000000000)  * [bit(44)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000200000000000)  * [bit(45)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000400000000000)  * [bit(46)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0000800000000000)  * [bit(47)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0001000000000000)  * [bit(48)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0002000000000000)  * [bit(49)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0004000000000000)  * [bit(50)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0008000000000000)  * [bit(51)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0010000000000000)  * [bit(52)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0020000000000000)  * [bit(53)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0040000000000000)  * [bit(54)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0080000000000000)  * [bit(55)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0100000000000000)  * [bit(56)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0200000000000000)  * [bit(57)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0400000000000000)  * [bit(58)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x0800000000000000)  * [bit(59)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x1000000000000000)  * [bit(60)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x2000000000000000)  * [bit(61)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x4000000000000000)  * [bit(62)] */
/*          IA32_MISC_ENABLE_                   __UINT64_C(0x8000000000000000)  * [bit(63)] */
#define IA32_ENERGY_PERF_BIAS     __UINT32_C(0x000001b0)
#define IA32_PACKAGE_THERM_STATUS __UINT32_C(0x000001b1)
#define IA32_PACKAGE_THERM_INTERRUPT __UINT32_C(0x000001b2)
#define IA32_DEBUGCTL             __UINT32_C(0x000001d9)
#define IA32_SMRR_PHYSBASE        __UINT32_C(0x000001f2)
#define IA32_SMRR_PHYSMASK        __UINT32_C(0x000001f3)
#define IA32_PLATFORM_DCA_CAP     __UINT32_C(0x000001f8)
#define IA32_CPU_DCA_CAP          __UINT32_C(0x000001f9)
#define IA32_DCA_0_CAP            __UINT32_C(0x000001fa)
#define IA32_MTRR_PHYSBASE0       __UINT32_C(0x00000200)
#define IA32_MTRR_PHYSMASK0       __UINT32_C(0x00000201)
#define IA32_MTRR_PHYSBASE1       __UINT32_C(0x00000202)
#define IA32_MTRR_PHYSMASK1       __UINT32_C(0x00000203)
#define IA32_MTRR_PHYSBASE2       __UINT32_C(0x00000204)
#define IA32_MTRR_PHYSMASK2       __UINT32_C(0x00000205)
#define IA32_MTRR_PHYSBASE3       __UINT32_C(0x00000206)
#define IA32_MTRR_PHYSMASK3       __UINT32_C(0x00000207)
#define IA32_MTRR_PHYSBASE4       __UINT32_C(0x00000208)
#define IA32_MTRR_PHYSMASK4       __UINT32_C(0x00000209)
#define IA32_MTRR_PHYSBASE5       __UINT32_C(0x0000020a)
#define IA32_MTRR_PHYSMASK5       __UINT32_C(0x0000020b)
#define IA32_MTRR_PHYSBASE6       __UINT32_C(0x0000020c)
#define IA32_MTRR_PHYSMASK6       __UINT32_C(0x0000020d)
#define IA32_MTRR_PHYSBASE7       __UINT32_C(0x0000020e)
#define IA32_MTRR_PHYSMASK7       __UINT32_C(0x0000020f)
#define IA32_MTRR_PHYSBASE8       __UINT32_C(0x00000210)
#define IA32_MTRR_PHYSMASK8       __UINT32_C(0x00000211)
#define IA32_MTRR_PHYSBASE9       __UINT32_C(0x00000212)
#define IA32_MTRR_PHYSMASK9       __UINT32_C(0x00000213)
#define IA32_MTRR_FIX64K_00000    __UINT32_C(0x00000250)
#define IA32_MTRR_FIX16K_80000    __UINT32_C(0x00000258)
#define IA32_MTRR_FIX16K_A0000    __UINT32_C(0x00000259)
#define IA32_MTRR_FIX4K_C0000     __UINT32_C(0x00000268)
#define IA32_MTRR_FIX4K_C8000     __UINT32_C(0x00000269)
#define IA32_MTRR_FIX4K_D0000     __UINT32_C(0x0000026a)
#define IA32_MTRR_FIX4K_D8000     __UINT32_C(0x0000026b)
#define IA32_MTRR_FIX4K_E0000     __UINT32_C(0x0000026c)
#define IA32_MTRR_FIX4K_E8000     __UINT32_C(0x0000026d)
#define IA32_MTRR_FIX4K_F0000     __UINT32_C(0x0000026e)
#define IA32_MTRR_FIX4K_F8000     __UINT32_C(0x0000026f)
#define IA32_PAT                  __UINT32_C(0x00000277)
#define IA32_MC0_CTL2             __UINT32_C(0x00000280)
#define IA32_MC1_CTL2             __UINT32_C(0x00000281)
#define IA32_MC2_CTL2             __UINT32_C(0x00000282)
#define IA32_MC3_CTL2             __UINT32_C(0x00000283)
#define IA32_MC4_CTL2             __UINT32_C(0x00000284)
#define IA32_MC5_CTL2             __UINT32_C(0x00000285)
#define IA32_MC6_CTL2             __UINT32_C(0x00000286)
#define IA32_MC7_CTL2             __UINT32_C(0x00000287)
#define IA32_MC8_CTL2             __UINT32_C(0x00000288)
#define IA32_MC9_CTL2             __UINT32_C(0x00000289)
#define IA32_MC10_CTL2            __UINT32_C(0x0000028a)
#define IA32_MC11_CTL2            __UINT32_C(0x0000028b)
#define IA32_MC12_CTL2            __UINT32_C(0x0000028c)
#define IA32_MC13_CTL2            __UINT32_C(0x0000028d)
#define IA32_MC14_CTL2            __UINT32_C(0x0000028e)
#define IA32_MC15_CTL2            __UINT32_C(0x0000028f)
#define IA32_MC16_CTL2            __UINT32_C(0x00000290)
#define IA32_MC17_CTL2            __UINT32_C(0x00000291)
#define IA32_MC18_CTL2            __UINT32_C(0x00000292)
#define IA32_MC19_CTL2            __UINT32_C(0x00000293)
#define IA32_MC20_CTL2            __UINT32_C(0x00000294)
#define IA32_MC21_CTL2            __UINT32_C(0x00000295)
#define IA32_MC22_CTL2            __UINT32_C(0x00000296)
#define IA32_MC23_CTL2            __UINT32_C(0x00000297)
#define IA32_MC24_CTL2            __UINT32_C(0x00000298)
#define IA32_MC25_CTL2            __UINT32_C(0x00000299)
#define IA32_MC26_CTL2            __UINT32_C(0x0000029a)
#define IA32_MC27_CTL2            __UINT32_C(0x0000029b)
#define IA32_MC28_CTL2            __UINT32_C(0x0000029c)
#define IA32_MC29_CTL2            __UINT32_C(0x0000029d)
#define IA32_MC30_CTL2            __UINT32_C(0x0000029e)
#define IA32_MC31_CTL2            __UINT32_C(0x0000029f)
#define IA32_MTRR_DEF_TYPE        __UINT32_C(0x000002ff)
#define IA32_FIXED_CTR0           __UINT32_C(0x00000309)
#define IA32_FIXED_CTR1           __UINT32_C(0x0000030a)
#define IA32_FIXED_CTR2           __UINT32_C(0x0000030b)
#define IA32_PERF_CAPABILITIES    __UINT32_C(0x00000345)
#define IA32_FIXED_CTR_CTRL       __UINT32_C(0x0000038d)
#define IA32_PERF_GLOBAL_STATUS   __UINT32_C(0x0000038e)
#define IA32_PERF_GLOBAL_CTRL     __UINT32_C(0x0000038f)
#define IA32_PERF_GLOBAL_OVF_CTRL __UINT32_C(0x00000390)
#define IA32_PERF_GLOBAL_STATUS_RESET __UINT32_C(0x00000390)
#define IA32_PERF_GLOBAL_STATUS_SET __UINT32_C(0x00000391)
#define IA32_PERF_GLOBAL_INUSE    __UINT32_C(0x00000392)
#define IA32_PEBS_ENABLE          __UINT32_C(0x000003f1)

#define IA32_MC0_CTL              __UINT32_C(0x00000400)
#define IA32_MC0_STATUS           __UINT32_C(0x00000401)
#define IA32_MC0_ADDR             __UINT32_C(0x00000402)
#define IA32_MC0_MISC             __UINT32_C(0x00000403)
#define IA32_MC1_CTL              __UINT32_C(0x00000404)
#define IA32_MC1_STATUS           __UINT32_C(0x00000405)
#define IA32_MC1_ADDR             __UINT32_C(0x00000406)
#define IA32_MC1_MISC             __UINT32_C(0x00000407)
#define IA32_MC2_CTL              __UINT32_C(0x00000408)
#define IA32_MC2_STATUS           __UINT32_C(0x00000409)
#define IA32_MC2_ADDR             __UINT32_C(0x0000040a)
#define IA32_MC2_MISC             __UINT32_C(0x0000040b)
#define IA32_MC3_CTL              __UINT32_C(0x0000040c)
#define IA32_MC3_STATUS           __UINT32_C(0x0000040d)
#define IA32_MC3_ADDR             __UINT32_C(0x0000040e)
#define IA32_MC3_MISC             __UINT32_C(0x0000040f)
#define IA32_MC4_CTL              __UINT32_C(0x00000410)
#define IA32_MC4_STATUS           __UINT32_C(0x00000411)
#define IA32_MC4_ADDR             __UINT32_C(0x00000412)
#define IA32_MC4_MISC             __UINT32_C(0x00000413)
#define IA32_MC5_CTL              __UINT32_C(0x00000414)
#define IA32_MC5_STATUS           __UINT32_C(0x00000415)
#define IA32_MC5_ADDR             __UINT32_C(0x00000416)
#define IA32_MC5_MISC             __UINT32_C(0x00000417)
#define IA32_MC6_CTL              __UINT32_C(0x00000418)
#define IA32_MC6_STATUS           __UINT32_C(0x00000419)
#define IA32_MC6_ADDR             __UINT32_C(0x0000041a)
#define IA32_MC6_MISC             __UINT32_C(0x0000041b)
#define IA32_MC7_CTL              __UINT32_C(0x0000041c)
#define IA32_MC7_STATUS           __UINT32_C(0x0000041d)
#define IA32_MC7_ADDR             __UINT32_C(0x0000041e)
#define IA32_MC7_MISC             __UINT32_C(0x0000041f)
#define IA32_MC8_CTL              __UINT32_C(0x00000420)
#define IA32_MC8_STATUS           __UINT32_C(0x00000421)
#define IA32_MC8_ADDR             __UINT32_C(0x00000422)
#define IA32_MC8_MISC             __UINT32_C(0x00000423)
#define IA32_MC9_CTL              __UINT32_C(0x00000424)
#define IA32_MC9_STATUS           __UINT32_C(0x00000425)
#define IA32_MC9_ADDR             __UINT32_C(0x00000426)
#define IA32_MC9_MISC             __UINT32_C(0x00000427)
#define IA32_MC10_CTL             __UINT32_C(0x00000428)
#define IA32_MC10_STATUS          __UINT32_C(0x00000429)
#define IA32_MC10_ADDR            __UINT32_C(0x0000042a)
#define IA32_MC10_MISC            __UINT32_C(0x0000042b)
#define IA32_MC11_CTL             __UINT32_C(0x0000042c)
#define IA32_MC11_STATUS          __UINT32_C(0x0000042d)
#define IA32_MC11_ADDR            __UINT32_C(0x0000042e)
#define IA32_MC11_MISC            __UINT32_C(0x0000042f)
#define IA32_MC12_CTL             __UINT32_C(0x00000430)
#define IA32_MC12_STATUS          __UINT32_C(0x00000431)
#define IA32_MC12_ADDR            __UINT32_C(0x00000432)
#define IA32_MC12_MISC            __UINT32_C(0x00000433)
#define IA32_MC13_CTL             __UINT32_C(0x00000434)
#define IA32_MC13_STATUS          __UINT32_C(0x00000435)
#define IA32_MC13_ADDR            __UINT32_C(0x00000436)
#define IA32_MC13_MISC            __UINT32_C(0x00000437)
#define IA32_MC14_CTL             __UINT32_C(0x00000438)
#define IA32_MC14_STATUS          __UINT32_C(0x00000439)
#define IA32_MC14_ADDR            __UINT32_C(0x0000043a)
#define IA32_MC14_MISC            __UINT32_C(0x0000043b)
#define IA32_MC15_CTL             __UINT32_C(0x0000043c)
#define IA32_MC15_STATUS          __UINT32_C(0x0000043d)
#define IA32_MC15_ADDR            __UINT32_C(0x0000043e)
#define IA32_MC15_MISC            __UINT32_C(0x0000043f)
#define IA32_MC16_CTL             __UINT32_C(0x00000440)
#define IA32_MC16_STATUS          __UINT32_C(0x00000441)
#define IA32_MC16_ADDR            __UINT32_C(0x00000442)
#define IA32_MC16_MISC            __UINT32_C(0x00000443)
#define IA32_MC17_CTL             __UINT32_C(0x00000444)
#define IA32_MC17_STATUS          __UINT32_C(0x00000445)
#define IA32_MC17_ADDR            __UINT32_C(0x00000446)
#define IA32_MC17_MISC            __UINT32_C(0x00000447)
#define IA32_MC18_CTL             __UINT32_C(0x00000448)
#define IA32_MC18_STATUS          __UINT32_C(0x00000449)
#define IA32_MC18_ADDR            __UINT32_C(0x0000044a)
#define IA32_MC18_MISC            __UINT32_C(0x0000044b)
#define IA32_MC19_CTL             __UINT32_C(0x0000044c)
#define IA32_MC19_STATUS          __UINT32_C(0x0000044d)
#define IA32_MC19_ADDR            __UINT32_C(0x0000044e)
#define IA32_MC19_MISC            __UINT32_C(0x0000044f)
#define IA32_MC20_CTL             __UINT32_C(0x00000450)
#define IA32_MC20_STATUS          __UINT32_C(0x00000451)
#define IA32_MC20_ADDR            __UINT32_C(0x00000452)
#define IA32_MC20_MISC            __UINT32_C(0x00000453)
#define IA32_MC21_CTL             __UINT32_C(0x00000454)
#define IA32_MC21_STATUS          __UINT32_C(0x00000455)
#define IA32_MC21_ADDR            __UINT32_C(0x00000456)
#define IA32_MC21_MISC            __UINT32_C(0x00000457)
#define IA32_MC22_CTL             __UINT32_C(0x00000458)
#define IA32_MC22_STATUS          __UINT32_C(0x00000459)
#define IA32_MC22_ADDR            __UINT32_C(0x0000045a)
#define IA32_MC22_MISC            __UINT32_C(0x0000045b)
#define IA32_MC23_CTL             __UINT32_C(0x0000045c)
#define IA32_MC23_STATUS          __UINT32_C(0x0000045d)
#define IA32_MC23_ADDR            __UINT32_C(0x0000045e)
#define IA32_MC23_MISC            __UINT32_C(0x0000045f)
#define IA32_MC24_CTL             __UINT32_C(0x00000460)
#define IA32_MC24_STATUS          __UINT32_C(0x00000461)
#define IA32_MC24_ADDR            __UINT32_C(0x00000462)
#define IA32_MC24_MISC            __UINT32_C(0x00000463)
#define IA32_MC25_CTL             __UINT32_C(0x00000464)
#define IA32_MC25_STATUS          __UINT32_C(0x00000465)
#define IA32_MC25_ADDR            __UINT32_C(0x00000466)
#define IA32_MC25_MISC            __UINT32_C(0x00000467)
#define IA32_MC26_CTL             __UINT32_C(0x00000468)
#define IA32_MC26_STATUS          __UINT32_C(0x00000469)
#define IA32_MC26_ADDR            __UINT32_C(0x0000046a)
#define IA32_MC26_MISC            __UINT32_C(0x0000046b)
#define IA32_MC27_CTL             __UINT32_C(0x0000046c)
#define IA32_MC27_STATUS          __UINT32_C(0x0000046d)
#define IA32_MC27_ADDR            __UINT32_C(0x0000046e)
#define IA32_MC27_MISC            __UINT32_C(0x0000046f)
#define IA32_MC28_CTL             __UINT32_C(0x00000470)
#define IA32_MC28_STATUS          __UINT32_C(0x00000471)
#define IA32_MC28_ADDR            __UINT32_C(0x00000472)
#define IA32_MC28_MISC            __UINT32_C(0x00000473)
#define IA32_VMX_BASIC            __UINT32_C(0x00000480)
#define IA32_VMX_PINBASED_CTLS    __UINT32_C(0x00000481)
#define IA32_VMX_PROCBASED_CTLS   __UINT32_C(0x00000482)
#define IA32_VMX_EXIT_CTLS        __UINT32_C(0x00000483)
#define IA32_VMX_ENTRY_CTLS       __UINT32_C(0x00000484)
#define IA32_VMX_MISC             __UINT32_C(0x00000485)
#define IA32_VMX_CR0_FIXED0       __UINT32_C(0x00000486)
#define IA32_VMX_CR0_FIXED1       __UINT32_C(0x00000487)
#define IA32_VMX_CR4_FIXED0       __UINT32_C(0x00000488)
#define IA32_VMX_CR4_FIXED1       __UINT32_C(0x00000489)
#define IA32_VMX_VMCS_ENUM        __UINT32_C(0x0000048a)
#define IA32_VMX_PROCBASED_CTLS2  __UINT32_C(0x0000048b)
#define IA32_VMX_EPT_VPID_CAP     __UINT32_C(0x0000048c)
#define IA32_VMX_TRUE_PINBASED_CTLS __UINT32_C(0x0000048d)
#define IA32_VMX_TRUE_PROCBASED_CTLS __UINT32_C(0x0000048e)
#define IA32_VMX_TRUE_EXIT_CTLS   __UINT32_C(0x0000048f)
#define IA32_VMX_TRUE_ENTRY_CTLS  __UINT32_C(0x00000490)
#define IA32_VMX_VMFUNC           __UINT32_C(0x00000491)
#define IA32_A_PMC0               __UINT32_C(0x000004c1)
#define IA32_A_PMC1               __UINT32_C(0x000004c2)
#define IA32_A_PMC2               __UINT32_C(0x000004c3)
#define IA32_A_PMC3               __UINT32_C(0x000004c4)
#define IA32_A_PMC4               __UINT32_C(0x000004c5)
#define IA32_A_PMC5               __UINT32_C(0x000004c6)
#define IA32_A_PMC6               __UINT32_C(0x000004c7)
#define IA32_A_PMC7               __UINT32_C(0x000004c8)
#define IA32_MCG_EXT_CTL          __UINT32_C(0x000004d0)
#define IA32_SGX_SVN_STATUS       __UINT32_C(0x00000500)
#define IA32_RTIT_OUTPUT_BASE     __UINT32_C(0x00000560)
#define IA32_RTIT_OUTPUT_MASK_PTRS __UINT32_C(0x00000561)
#define IA32_RTIT_CTL             __UINT32_C(0x00000570)
#define IA32_RTIT_STATUS          __UINT32_C(0x00000571)
#define IA32_RTIT_CR3_MATCH       __UINT32_C(0x00000572)
#define IA32_RTIT_ADDR0_A         __UINT32_C(0x00000580)
#define IA32_RTIT_ADDR0_B         __UINT32_C(0x00000581)
#define IA32_RTIT_ADDR1_A         __UINT32_C(0x00000582)
#define IA32_RTIT_ADDR1_B         __UINT32_C(0x00000583)
#define IA32_RTIT_ADDR2_A         __UINT32_C(0x00000584)
#define IA32_RTIT_ADDR2_B         __UINT32_C(0x00000585)
#define IA32_RTIT_ADDR3_A         __UINT32_C(0x00000586)
#define IA32_RTIT_ADDR3_B         __UINT32_C(0x00000587)
#define IA32_DS_AREA              __UINT32_C(0x00000600)
#define IA32_TSC_DEADLINE         __UINT32_C(0x000006e0)
#define IA32_PM_ENABLE            __UINT32_C(0x00000770)
#define IA32_HWP_CAPABILITIES     __UINT32_C(0x00000771)
#define IA32_HWP_REQUEST_PKG      __UINT32_C(0x00000772)
#define IA32_HWP_INTERRUPT        __UINT32_C(0x00000773)
#define IA32_HWP_REQUEST          __UINT32_C(0x00000774)
#define IA32_HWP_STATUS           __UINT32_C(0x00000777)
#define IA32_X2APIC_APICID        __UINT32_C(0x00000802)
#define IA32_X2APIC_VERSION       __UINT32_C(0x00000803)
#define IA32_X2APIC_TPR           __UINT32_C(0x00000808)
#define IA32_X2APIC_PPR           __UINT32_C(0x0000080a)
#define IA32_X2APIC_EOI           __UINT32_C(0x0000080b)
#define IA32_X2APIC_LDR           __UINT32_C(0x0000080d)
#define IA32_X2APIC_SIVR          __UINT32_C(0x0000080f)
#define IA32_X2APIC_ISR0          __UINT32_C(0x00000810)
#define IA32_X2APIC_ISR1          __UINT32_C(0x00000811)
#define IA32_X2APIC_ISR2          __UINT32_C(0x00000812)
#define IA32_X2APIC_ISR3          __UINT32_C(0x00000813)
#define IA32_X2APIC_ISR4          __UINT32_C(0x00000814)
#define IA32_X2APIC_ISR5          __UINT32_C(0x00000815)
#define IA32_X2APIC_ISR6          __UINT32_C(0x00000816)
#define IA32_X2APIC_ISR7          __UINT32_C(0x00000817)
#define IA32_X2APIC_TMR0          __UINT32_C(0x00000818)
#define IA32_X2APIC_TMR1          __UINT32_C(0x00000819)
#define IA32_X2APIC_TMR2          __UINT32_C(0x0000081a)
#define IA32_X2APIC_TMR3          __UINT32_C(0x0000081b)
#define IA32_X2APIC_TMR4          __UINT32_C(0x0000081c)
#define IA32_X2APIC_TMR5          __UINT32_C(0x0000081d)
#define IA32_X2APIC_TMR6          __UINT32_C(0x0000081e)
#define IA32_X2APIC_TMR7          __UINT32_C(0x0000081f)
#define IA32_X2APIC_IRR0          __UINT32_C(0x00000820)
#define IA32_X2APIC_IRR1          __UINT32_C(0x00000821)
#define IA32_X2APIC_IRR2          __UINT32_C(0x00000822)
#define IA32_X2APIC_IRR3          __UINT32_C(0x00000823)
#define IA32_X2APIC_IRR4          __UINT32_C(0x00000824)
#define IA32_X2APIC_IRR5          __UINT32_C(0x00000825)
#define IA32_X2APIC_IRR6          __UINT32_C(0x00000826)
#define IA32_X2APIC_IRR7          __UINT32_C(0x00000827)
#define IA32_X2APIC_ESR           __UINT32_C(0x00000828)
#define IA32_X2APIC_LVT_CMCI      __UINT32_C(0x0000082f)
#define IA32_X2APIC_ICR           __UINT32_C(0x00000830)
#define IA32_X2APIC_LVT_TIMER     __UINT32_C(0x00000832)
#define IA32_X2APIC_LVT_THERMAL   __UINT32_C(0x00000833)
#define IA32_X2APIC_LVT_PMI       __UINT32_C(0x00000834)
#define IA32_X2APIC_LVT_LINT0     __UINT32_C(0x00000835)
#define IA32_X2APIC_LVT_LINT1     __UINT32_C(0x00000836)
#define IA32_X2APIC_LVT_ERROR     __UINT32_C(0x00000837)
#define IA32_X2APIC_INIT_COUNT    __UINT32_C(0x00000838)
#define IA32_X2APIC_CUR_COUNT     __UINT32_C(0x00000839)
#define IA32_X2APIC_DIV_CONF      __UINT32_C(0x0000083e)
#define IA32_X2APIC_SELF_IPI      __UINT32_C(0x0000083f)
#define IA32_DEBUG_INTERFACE      __UINT32_C(0x00000c80)
#define IA32_L3_QOS_CFG           __UINT32_C(0x00000c81)
#define IA32_L2_QOS_CFG           __UINT32_C(0x00000c82)
#define IA32_QM_EVTSEL            __UINT32_C(0x00000c8d)
#define IA32_QM_CTR               __UINT32_C(0x00000c8e)
#define IA32_PQR_ASSOC            __UINT32_C(0x00000c8f)
#define IA32_L3_MASK_0            __UINT32_C(0x00000c90)
#define IA32_L3_MASK_n(n)        (__UINT32_C(0x00000c90) + (n))
#define IA32_L2_MASK_0            __UINT32_C(0x00000d10)
#define IA32_L2_MASK_n(n)        (__UINT32_C(0x00000d10) + (n))
#define IA32_BNDCFGS              __UINT32_C(0x00000d90)
#define IA32_XSS                  __UINT32_C(0x00000da0)
#define IA32_PKG_HDC_CTL          __UINT32_C(0x00000db0)
#define IA32_PM_CTL1              __UINT32_C(0x00000db1)
#define IA32_THREAD_STALL         __UINT32_C(0x00000db2)

#define IA32_EFER                 __UINT32_C(0xc0000080)
#define     IA32_EFER_SCE             __UINT32_C(0x00000001)  /* System Call Extensions */
#define     IA32_EFER_LME             __UINT32_C(0x00000100)  /* Long Mode Enable */
#define     IA32_EFER_LMA             __UINT32_C(0x00000400)  /* Long Mode Active */
#define     IA32_EFER_NXE             __UINT32_C(0x00000800)  /* No-Execute Enable */
#define     IA32_EFER_SVME            __UINT32_C(0x00001000)  /* Secure Virtual Machine Enable */
#define     IA32_EFER_LMSLE           __UINT32_C(0x00002000)  /* Long Mode Segment Limit Enable */
#define     IA32_EFER_FFXSR           __UINT32_C(0x00004000)  /* Fast FXSAVE/FXRSTOR */
#define     IA32_EFER_TCE             __UINT32_C(0x00008000)  /* Translation Cache Extension */
#define IA32_STAR                 __UINT32_C(0xc0000081)
#define IA32_LSTAR                __UINT32_C(0xc0000082)
#define IA32_CSTAR                __UINT32_C(0xc0000083)
#define IA32_FMASK                __UINT32_C(0xc0000084)
#define IA32_FS_BASE              __UINT32_C(0xc0000100)
#define IA32_GS_BASE              __UINT32_C(0xc0000101)
#define IA32_KERNEL_GS_BASE       __UINT32_C(0xc0000102)
#define IA32_TSC_AUX              __UINT32_C(0xc0000103)


#endif /* !_I386_KOS_ASM_CPU_MSR_H */
