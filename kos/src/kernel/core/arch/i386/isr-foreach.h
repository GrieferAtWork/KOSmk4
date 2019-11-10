/* Copyright (c) 2019 Griefer@Work                                            *
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
#define PRINT_VECTOR_INCLUDES(name, ...)                      \
	({                                                        \
		;                                                     \
		print "#ifdef", name;                                 \
		for (local x: (__VA_ARGS__)) {                        \
			print "#define ISR_VECTOR", x.hex()[2:].zfill(2); \
			print "#include", name;                           \
		}                                                     \
		print "#undef", name;                                 \
		print "#endif /*", name, "*/";                        \
	})


/* 0x00 ... 0x1f */
/*[[[deemon PRINT_VECTOR_INCLUDES("ISR_EXCEPT_IMPL", [0x00 : 0x1f + 1]); ]]]*/
#ifdef ISR_EXCEPT_IMPL
#define ISR_VECTOR 00
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 01
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 02
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 03
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 04
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 05
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 06
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 07
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 08
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 09
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 0a
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 0b
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 0c
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 0d
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 0e
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 0f
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 10
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 11
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 12
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 13
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 14
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 15
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 16
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 17
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 18
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 19
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 1a
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 1b
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 1c
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 1d
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 1e
#include ISR_EXCEPT_IMPL
#define ISR_VECTOR 1f
#include ISR_EXCEPT_IMPL
#undef ISR_EXCEPT_IMPL
#endif /* ISR_EXCEPT_IMPL */
/*[[[end]]]*/




/* 0x20 ... 0x2f */
/*[[[deemon PRINT_VECTOR_INCLUDES("ISR_WINSPEC_IMPL", [0x20 : 0x2f + 1]); ]]]*/
#ifdef ISR_WINSPEC_IMPL
#define ISR_VECTOR 20
#include ISR_WINSPEC_IMPL
#define ISR_VECTOR 21
#include ISR_WINSPEC_IMPL
#define ISR_VECTOR 22
#include ISR_WINSPEC_IMPL
#define ISR_VECTOR 23
#include ISR_WINSPEC_IMPL
#define ISR_VECTOR 24
#include ISR_WINSPEC_IMPL
#define ISR_VECTOR 25
#include ISR_WINSPEC_IMPL
#define ISR_VECTOR 26
#include ISR_WINSPEC_IMPL
#define ISR_VECTOR 27
#include ISR_WINSPEC_IMPL
#define ISR_VECTOR 28
#include ISR_WINSPEC_IMPL
#define ISR_VECTOR 29
#include ISR_WINSPEC_IMPL
#define ISR_VECTOR 2a
#include ISR_WINSPEC_IMPL
#define ISR_VECTOR 2b
#include ISR_WINSPEC_IMPL
#define ISR_VECTOR 2c
#include ISR_WINSPEC_IMPL
#define ISR_VECTOR 2d
#include ISR_WINSPEC_IMPL
#define ISR_VECTOR 2e
#include ISR_WINSPEC_IMPL
#define ISR_VECTOR 2f
#include ISR_WINSPEC_IMPL
#undef ISR_WINSPEC_IMPL
#endif /* ISR_WINSPEC_IMPL */
/*[[[end]]]*/




/* 0x30 ... 0x7f */
/*[[[deemon PRINT_VECTOR_INCLUDES("ISR_UNUSED_IMPL", [0x30 : 0x7f + 1]); ]]]*/
#ifdef ISR_UNUSED_IMPL
#define ISR_VECTOR 30
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 31
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 32
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 33
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 34
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 35
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 36
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 37
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 38
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 39
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 3a
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 3b
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 3c
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 3d
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 3e
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 3f
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 40
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 41
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 42
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 43
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 44
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 45
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 46
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 47
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 48
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 49
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 4a
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 4b
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 4c
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 4d
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 4e
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 4f
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 50
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 51
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 52
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 53
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 54
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 55
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 56
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 57
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 58
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 59
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 5a
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 5b
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 5c
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 5d
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 5e
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 5f
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 60
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 61
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 62
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 63
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 64
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 65
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 66
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 67
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 68
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 69
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 6a
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 6b
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 6c
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 6d
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 6e
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 6f
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 70
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 71
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 72
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 73
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 74
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 75
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 76
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 77
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 78
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 79
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 7a
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 7b
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 7c
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 7d
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 7e
#include ISR_UNUSED_IMPL
#define ISR_VECTOR 7f
#include ISR_UNUSED_IMPL
#undef ISR_UNUSED_IMPL
#endif /* ISR_UNUSED_IMPL */
/*[[[end]]]*/




/* 0x80 */
/*[[[deemon PRINT_VECTOR_INCLUDES("ISR_SYSCALL_IMPL", [0x80]); ]]]*/
#ifdef ISR_SYSCALL_IMPL
#define ISR_VECTOR 80
#include ISR_SYSCALL_IMPL
#undef ISR_SYSCALL_IMPL
#endif /* ISR_SYSCALL_IMPL */
/*[[[end]]]*/




/* 0x81 ... 0xed */
/*[[[deemon PRINT_VECTOR_INCLUDES("ISR_GENERIC_IMPL", [0x81 : 0xed + 1]); ]]]*/
#ifdef ISR_GENERIC_IMPL
#define ISR_VECTOR 81
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 82
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 83
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 84
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 85
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 86
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 87
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 88
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 89
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 8a
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 8b
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 8c
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 8d
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 8e
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 8f
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 90
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 91
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 92
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 93
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 94
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 95
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 96
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 97
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 98
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 99
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 9a
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 9b
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 9c
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 9d
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 9e
#include ISR_GENERIC_IMPL
#define ISR_VECTOR 9f
#include ISR_GENERIC_IMPL
#define ISR_VECTOR a0
#include ISR_GENERIC_IMPL
#define ISR_VECTOR a1
#include ISR_GENERIC_IMPL
#define ISR_VECTOR a2
#include ISR_GENERIC_IMPL
#define ISR_VECTOR a3
#include ISR_GENERIC_IMPL
#define ISR_VECTOR a4
#include ISR_GENERIC_IMPL
#define ISR_VECTOR a5
#include ISR_GENERIC_IMPL
#define ISR_VECTOR a6
#include ISR_GENERIC_IMPL
#define ISR_VECTOR a7
#include ISR_GENERIC_IMPL
#define ISR_VECTOR a8
#include ISR_GENERIC_IMPL
#define ISR_VECTOR a9
#include ISR_GENERIC_IMPL
#define ISR_VECTOR aa
#include ISR_GENERIC_IMPL
#define ISR_VECTOR ab
#include ISR_GENERIC_IMPL
#define ISR_VECTOR ac
#include ISR_GENERIC_IMPL
#define ISR_VECTOR ad
#include ISR_GENERIC_IMPL
#define ISR_VECTOR ae
#include ISR_GENERIC_IMPL
#define ISR_VECTOR af
#include ISR_GENERIC_IMPL
#define ISR_VECTOR b0
#include ISR_GENERIC_IMPL
#define ISR_VECTOR b1
#include ISR_GENERIC_IMPL
#define ISR_VECTOR b2
#include ISR_GENERIC_IMPL
#define ISR_VECTOR b3
#include ISR_GENERIC_IMPL
#define ISR_VECTOR b4
#include ISR_GENERIC_IMPL
#define ISR_VECTOR b5
#include ISR_GENERIC_IMPL
#define ISR_VECTOR b6
#include ISR_GENERIC_IMPL
#define ISR_VECTOR b7
#include ISR_GENERIC_IMPL
#define ISR_VECTOR b8
#include ISR_GENERIC_IMPL
#define ISR_VECTOR b9
#include ISR_GENERIC_IMPL
#define ISR_VECTOR ba
#include ISR_GENERIC_IMPL
#define ISR_VECTOR bb
#include ISR_GENERIC_IMPL
#define ISR_VECTOR bc
#include ISR_GENERIC_IMPL
#define ISR_VECTOR bd
#include ISR_GENERIC_IMPL
#define ISR_VECTOR be
#include ISR_GENERIC_IMPL
#define ISR_VECTOR bf
#include ISR_GENERIC_IMPL
#define ISR_VECTOR c0
#include ISR_GENERIC_IMPL
#define ISR_VECTOR c1
#include ISR_GENERIC_IMPL
#define ISR_VECTOR c2
#include ISR_GENERIC_IMPL
#define ISR_VECTOR c3
#include ISR_GENERIC_IMPL
#define ISR_VECTOR c4
#include ISR_GENERIC_IMPL
#define ISR_VECTOR c5
#include ISR_GENERIC_IMPL
#define ISR_VECTOR c6
#include ISR_GENERIC_IMPL
#define ISR_VECTOR c7
#include ISR_GENERIC_IMPL
#define ISR_VECTOR c8
#include ISR_GENERIC_IMPL
#define ISR_VECTOR c9
#include ISR_GENERIC_IMPL
#define ISR_VECTOR ca
#include ISR_GENERIC_IMPL
#define ISR_VECTOR cb
#include ISR_GENERIC_IMPL
#define ISR_VECTOR cc
#include ISR_GENERIC_IMPL
#define ISR_VECTOR cd
#include ISR_GENERIC_IMPL
#define ISR_VECTOR ce
#include ISR_GENERIC_IMPL
#define ISR_VECTOR cf
#include ISR_GENERIC_IMPL
#define ISR_VECTOR d0
#include ISR_GENERIC_IMPL
#define ISR_VECTOR d1
#include ISR_GENERIC_IMPL
#define ISR_VECTOR d2
#include ISR_GENERIC_IMPL
#define ISR_VECTOR d3
#include ISR_GENERIC_IMPL
#define ISR_VECTOR d4
#include ISR_GENERIC_IMPL
#define ISR_VECTOR d5
#include ISR_GENERIC_IMPL
#define ISR_VECTOR d6
#include ISR_GENERIC_IMPL
#define ISR_VECTOR d7
#include ISR_GENERIC_IMPL
#define ISR_VECTOR d8
#include ISR_GENERIC_IMPL
#define ISR_VECTOR d9
#include ISR_GENERIC_IMPL
#define ISR_VECTOR da
#include ISR_GENERIC_IMPL
#define ISR_VECTOR db
#include ISR_GENERIC_IMPL
#define ISR_VECTOR dc
#include ISR_GENERIC_IMPL
#define ISR_VECTOR dd
#include ISR_GENERIC_IMPL
#define ISR_VECTOR de
#include ISR_GENERIC_IMPL
#define ISR_VECTOR df
#include ISR_GENERIC_IMPL
#define ISR_VECTOR e0
#include ISR_GENERIC_IMPL
#define ISR_VECTOR e1
#include ISR_GENERIC_IMPL
#define ISR_VECTOR e2
#include ISR_GENERIC_IMPL
#define ISR_VECTOR e3
#include ISR_GENERIC_IMPL
#define ISR_VECTOR e4
#include ISR_GENERIC_IMPL
#define ISR_VECTOR e5
#include ISR_GENERIC_IMPL
#define ISR_VECTOR e6
#include ISR_GENERIC_IMPL
#define ISR_VECTOR e7
#include ISR_GENERIC_IMPL
#define ISR_VECTOR e8
#include ISR_GENERIC_IMPL
#define ISR_VECTOR e9
#include ISR_GENERIC_IMPL
#define ISR_VECTOR ea
#include ISR_GENERIC_IMPL
#define ISR_VECTOR eb
#include ISR_GENERIC_IMPL
#define ISR_VECTOR ec
#include ISR_GENERIC_IMPL
#define ISR_VECTOR ed
#include ISR_GENERIC_IMPL
#undef ISR_GENERIC_IMPL
#endif /* ISR_GENERIC_IMPL */
/*[[[end]]]*/




/* 0xee */
/*[[[deemon PRINT_VECTOR_INCLUDES("ISR_APIC_IPI_IMPL", [0xee]); ]]]*/
#ifdef ISR_APIC_IPI_IMPL
#define ISR_VECTOR ee
#include ISR_APIC_IPI_IMPL
#undef ISR_APIC_IPI_IMPL
#endif /* ISR_APIC_IPI_IMPL */
/*[[[end]]]*/




/* 0xef */
/*[[[deemon PRINT_VECTOR_INCLUDES("ISR_APIC_SPURIOUS_IMPL", [0xef]); ]]]*/
#ifdef ISR_APIC_SPURIOUS_IMPL
#define ISR_VECTOR ef
#include ISR_APIC_SPURIOUS_IMPL
#undef ISR_APIC_SPURIOUS_IMPL
#endif /* ISR_APIC_SPURIOUS_IMPL */
/*[[[end]]]*/




/* 0xf0 */
/*[[[deemon PRINT_VECTOR_INCLUDES("ISR_PREEMPT_IMPL", [0xf0]); ]]]*/
#ifdef ISR_PREEMPT_IMPL
#define ISR_VECTOR f0
#include ISR_PREEMPT_IMPL
#undef ISR_PREEMPT_IMPL
#endif /* ISR_PREEMPT_IMPL */
/*[[[end]]]*/




/* 0xf1 ... 0xff */
/*[[[deemon PRINT_VECTOR_INCLUDES("ISR_SPECIFIC_IMPL", [0xf1 : 0xff + 1]); ]]]*/
#ifdef ISR_SPECIFIC_IMPL
#define ISR_VECTOR f1
#include ISR_SPECIFIC_IMPL
#define ISR_VECTOR f2
#include ISR_SPECIFIC_IMPL
#define ISR_VECTOR f3
#include ISR_SPECIFIC_IMPL
#define ISR_VECTOR f4
#include ISR_SPECIFIC_IMPL
#define ISR_VECTOR f5
#include ISR_SPECIFIC_IMPL
#define ISR_VECTOR f6
#include ISR_SPECIFIC_IMPL
#define ISR_VECTOR f7
#include ISR_SPECIFIC_IMPL
#define ISR_VECTOR f8
#include ISR_SPECIFIC_IMPL
#define ISR_VECTOR f9
#include ISR_SPECIFIC_IMPL
#define ISR_VECTOR fa
#include ISR_SPECIFIC_IMPL
#define ISR_VECTOR fb
#include ISR_SPECIFIC_IMPL
#define ISR_VECTOR fc
#include ISR_SPECIFIC_IMPL
#define ISR_VECTOR fd
#include ISR_SPECIFIC_IMPL
#define ISR_VECTOR fe
#include ISR_SPECIFIC_IMPL
#define ISR_VECTOR ff
#include ISR_SPECIFIC_IMPL
#undef ISR_SPECIFIC_IMPL
#endif /* ISR_SPECIFIC_IMPL */
/*[[[end]]]*/




