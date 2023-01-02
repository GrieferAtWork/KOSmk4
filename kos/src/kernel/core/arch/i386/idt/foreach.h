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
#define PRINT_VECTOR_INCLUDES(name, ...)                      \
	({                                                        \
		;                                                     \
		print "#ifdef", name;                                 \
		for (local x: (__VA_ARGS__)) {                        \
			print "#define IDT_VECTOR", x.hex()[2:].zfill(2); \
			print "#include", name;                           \
		}                                                     \
		print "#undef", name;                                 \
		print "#endif /*", name, "*/";                        \
	})


/* 0x00 ... 0x1f */
/*[[[deemon PRINT_VECTOR_INCLUDES("IDT_EXCEPT_IMPL", [0x00 : 0x1f + 1]); ]]]*/
#ifdef IDT_EXCEPT_IMPL
#define IDT_VECTOR 00
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 01
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 02
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 03
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 04
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 05
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 06
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 07
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 08
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 09
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 0a
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 0b
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 0c
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 0d
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 0e
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 0f
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 10
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 11
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 12
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 13
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 14
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 15
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 16
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 17
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 18
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 19
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 1a
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 1b
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 1c
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 1d
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 1e
#include IDT_EXCEPT_IMPL
#define IDT_VECTOR 1f
#include IDT_EXCEPT_IMPL
#undef IDT_EXCEPT_IMPL
#endif /* IDT_EXCEPT_IMPL */
/*[[[end]]]*/




/* 0x20 ... 0x2f */
/*[[[deemon PRINT_VECTOR_INCLUDES("IDT_WINSPEC_IMPL", [0x20 : 0x2f + 1]); ]]]*/
#ifdef IDT_WINSPEC_IMPL
#define IDT_VECTOR 20
#include IDT_WINSPEC_IMPL
#define IDT_VECTOR 21
#include IDT_WINSPEC_IMPL
#define IDT_VECTOR 22
#include IDT_WINSPEC_IMPL
#define IDT_VECTOR 23
#include IDT_WINSPEC_IMPL
#define IDT_VECTOR 24
#include IDT_WINSPEC_IMPL
#define IDT_VECTOR 25
#include IDT_WINSPEC_IMPL
#define IDT_VECTOR 26
#include IDT_WINSPEC_IMPL
#define IDT_VECTOR 27
#include IDT_WINSPEC_IMPL
#define IDT_VECTOR 28
#include IDT_WINSPEC_IMPL
#define IDT_VECTOR 29
#include IDT_WINSPEC_IMPL
#define IDT_VECTOR 2a
#include IDT_WINSPEC_IMPL
#define IDT_VECTOR 2b
#include IDT_WINSPEC_IMPL
#define IDT_VECTOR 2c
#include IDT_WINSPEC_IMPL
#define IDT_VECTOR 2d
#include IDT_WINSPEC_IMPL
#define IDT_VECTOR 2e
#include IDT_WINSPEC_IMPL
#define IDT_VECTOR 2f
#include IDT_WINSPEC_IMPL
#undef IDT_WINSPEC_IMPL
#endif /* IDT_WINSPEC_IMPL */
/*[[[end]]]*/




/* 0x30 ... 0x7f */
/*[[[deemon PRINT_VECTOR_INCLUDES("IDT_UNUSED_IMPL", [0x30 : 0x7f + 1]); ]]]*/
#ifdef IDT_UNUSED_IMPL
#define IDT_VECTOR 30
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 31
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 32
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 33
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 34
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 35
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 36
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 37
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 38
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 39
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 3a
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 3b
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 3c
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 3d
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 3e
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 3f
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 40
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 41
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 42
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 43
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 44
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 45
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 46
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 47
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 48
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 49
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 4a
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 4b
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 4c
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 4d
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 4e
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 4f
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 50
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 51
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 52
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 53
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 54
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 55
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 56
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 57
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 58
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 59
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 5a
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 5b
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 5c
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 5d
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 5e
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 5f
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 60
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 61
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 62
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 63
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 64
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 65
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 66
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 67
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 68
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 69
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 6a
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 6b
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 6c
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 6d
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 6e
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 6f
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 70
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 71
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 72
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 73
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 74
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 75
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 76
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 77
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 78
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 79
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 7a
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 7b
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 7c
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 7d
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 7e
#include IDT_UNUSED_IMPL
#define IDT_VECTOR 7f
#include IDT_UNUSED_IMPL
#undef IDT_UNUSED_IMPL
#endif /* IDT_UNUSED_IMPL */
/*[[[end]]]*/




/* 0x80 */
/*[[[deemon PRINT_VECTOR_INCLUDES("IDT_SYSCALL_IMPL", [0x80]); ]]]*/
#ifdef IDT_SYSCALL_IMPL
#define IDT_VECTOR 80
#include IDT_SYSCALL_IMPL
#undef IDT_SYSCALL_IMPL
#endif /* IDT_SYSCALL_IMPL */
/*[[[end]]]*/




/* 0x81 ... 0xed */
/*[[[deemon PRINT_VECTOR_INCLUDES("IDT_GENERIC_IMPL", [0x81 : 0xed + 1]); ]]]*/
#ifdef IDT_GENERIC_IMPL
#define IDT_VECTOR 81
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 82
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 83
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 84
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 85
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 86
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 87
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 88
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 89
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 8a
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 8b
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 8c
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 8d
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 8e
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 8f
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 90
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 91
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 92
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 93
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 94
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 95
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 96
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 97
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 98
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 99
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 9a
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 9b
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 9c
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 9d
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 9e
#include IDT_GENERIC_IMPL
#define IDT_VECTOR 9f
#include IDT_GENERIC_IMPL
#define IDT_VECTOR a0
#include IDT_GENERIC_IMPL
#define IDT_VECTOR a1
#include IDT_GENERIC_IMPL
#define IDT_VECTOR a2
#include IDT_GENERIC_IMPL
#define IDT_VECTOR a3
#include IDT_GENERIC_IMPL
#define IDT_VECTOR a4
#include IDT_GENERIC_IMPL
#define IDT_VECTOR a5
#include IDT_GENERIC_IMPL
#define IDT_VECTOR a6
#include IDT_GENERIC_IMPL
#define IDT_VECTOR a7
#include IDT_GENERIC_IMPL
#define IDT_VECTOR a8
#include IDT_GENERIC_IMPL
#define IDT_VECTOR a9
#include IDT_GENERIC_IMPL
#define IDT_VECTOR aa
#include IDT_GENERIC_IMPL
#define IDT_VECTOR ab
#include IDT_GENERIC_IMPL
#define IDT_VECTOR ac
#include IDT_GENERIC_IMPL
#define IDT_VECTOR ad
#include IDT_GENERIC_IMPL
#define IDT_VECTOR ae
#include IDT_GENERIC_IMPL
#define IDT_VECTOR af
#include IDT_GENERIC_IMPL
#define IDT_VECTOR b0
#include IDT_GENERIC_IMPL
#define IDT_VECTOR b1
#include IDT_GENERIC_IMPL
#define IDT_VECTOR b2
#include IDT_GENERIC_IMPL
#define IDT_VECTOR b3
#include IDT_GENERIC_IMPL
#define IDT_VECTOR b4
#include IDT_GENERIC_IMPL
#define IDT_VECTOR b5
#include IDT_GENERIC_IMPL
#define IDT_VECTOR b6
#include IDT_GENERIC_IMPL
#define IDT_VECTOR b7
#include IDT_GENERIC_IMPL
#define IDT_VECTOR b8
#include IDT_GENERIC_IMPL
#define IDT_VECTOR b9
#include IDT_GENERIC_IMPL
#define IDT_VECTOR ba
#include IDT_GENERIC_IMPL
#define IDT_VECTOR bb
#include IDT_GENERIC_IMPL
#define IDT_VECTOR bc
#include IDT_GENERIC_IMPL
#define IDT_VECTOR bd
#include IDT_GENERIC_IMPL
#define IDT_VECTOR be
#include IDT_GENERIC_IMPL
#define IDT_VECTOR bf
#include IDT_GENERIC_IMPL
#define IDT_VECTOR c0
#include IDT_GENERIC_IMPL
#define IDT_VECTOR c1
#include IDT_GENERIC_IMPL
#define IDT_VECTOR c2
#include IDT_GENERIC_IMPL
#define IDT_VECTOR c3
#include IDT_GENERIC_IMPL
#define IDT_VECTOR c4
#include IDT_GENERIC_IMPL
#define IDT_VECTOR c5
#include IDT_GENERIC_IMPL
#define IDT_VECTOR c6
#include IDT_GENERIC_IMPL
#define IDT_VECTOR c7
#include IDT_GENERIC_IMPL
#define IDT_VECTOR c8
#include IDT_GENERIC_IMPL
#define IDT_VECTOR c9
#include IDT_GENERIC_IMPL
#define IDT_VECTOR ca
#include IDT_GENERIC_IMPL
#define IDT_VECTOR cb
#include IDT_GENERIC_IMPL
#define IDT_VECTOR cc
#include IDT_GENERIC_IMPL
#define IDT_VECTOR cd
#include IDT_GENERIC_IMPL
#define IDT_VECTOR ce
#include IDT_GENERIC_IMPL
#define IDT_VECTOR cf
#include IDT_GENERIC_IMPL
#define IDT_VECTOR d0
#include IDT_GENERIC_IMPL
#define IDT_VECTOR d1
#include IDT_GENERIC_IMPL
#define IDT_VECTOR d2
#include IDT_GENERIC_IMPL
#define IDT_VECTOR d3
#include IDT_GENERIC_IMPL
#define IDT_VECTOR d4
#include IDT_GENERIC_IMPL
#define IDT_VECTOR d5
#include IDT_GENERIC_IMPL
#define IDT_VECTOR d6
#include IDT_GENERIC_IMPL
#define IDT_VECTOR d7
#include IDT_GENERIC_IMPL
#define IDT_VECTOR d8
#include IDT_GENERIC_IMPL
#define IDT_VECTOR d9
#include IDT_GENERIC_IMPL
#define IDT_VECTOR da
#include IDT_GENERIC_IMPL
#define IDT_VECTOR db
#include IDT_GENERIC_IMPL
#define IDT_VECTOR dc
#include IDT_GENERIC_IMPL
#define IDT_VECTOR dd
#include IDT_GENERIC_IMPL
#define IDT_VECTOR de
#include IDT_GENERIC_IMPL
#define IDT_VECTOR df
#include IDT_GENERIC_IMPL
#define IDT_VECTOR e0
#include IDT_GENERIC_IMPL
#define IDT_VECTOR e1
#include IDT_GENERIC_IMPL
#define IDT_VECTOR e2
#include IDT_GENERIC_IMPL
#define IDT_VECTOR e3
#include IDT_GENERIC_IMPL
#define IDT_VECTOR e4
#include IDT_GENERIC_IMPL
#define IDT_VECTOR e5
#include IDT_GENERIC_IMPL
#define IDT_VECTOR e6
#include IDT_GENERIC_IMPL
#define IDT_VECTOR e7
#include IDT_GENERIC_IMPL
#define IDT_VECTOR e8
#include IDT_GENERIC_IMPL
#define IDT_VECTOR e9
#include IDT_GENERIC_IMPL
#define IDT_VECTOR ea
#include IDT_GENERIC_IMPL
#define IDT_VECTOR eb
#include IDT_GENERIC_IMPL
#define IDT_VECTOR ec
#include IDT_GENERIC_IMPL
#define IDT_VECTOR ed
#include IDT_GENERIC_IMPL
#undef IDT_GENERIC_IMPL
#endif /* IDT_GENERIC_IMPL */
/*[[[end]]]*/




/* 0xee */
/*[[[deemon PRINT_VECTOR_INCLUDES("IDT_APIC_IPI_IMPL", [0xee]); ]]]*/
#ifdef IDT_APIC_IPI_IMPL
#define IDT_VECTOR ee
#include IDT_APIC_IPI_IMPL
#undef IDT_APIC_IPI_IMPL
#endif /* IDT_APIC_IPI_IMPL */
/*[[[end]]]*/




/* 0xef */
/*[[[deemon PRINT_VECTOR_INCLUDES("IDT_APIC_SPURIOUS_IMPL", [0xef]); ]]]*/
#ifdef IDT_APIC_SPURIOUS_IMPL
#define IDT_VECTOR ef
#include IDT_APIC_SPURIOUS_IMPL
#undef IDT_APIC_SPURIOUS_IMPL
#endif /* IDT_APIC_SPURIOUS_IMPL */
/*[[[end]]]*/




/* 0xf1 ... 0xff */
/*[[[deemon PRINT_VECTOR_INCLUDES("IDT_SPECIFIC_IMPL",
	[      0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
	       0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff]); ]]]*/
#ifdef IDT_SPECIFIC_IMPL
#define IDT_VECTOR f1
#include IDT_SPECIFIC_IMPL
#define IDT_VECTOR f2
#include IDT_SPECIFIC_IMPL
#define IDT_VECTOR f3
#include IDT_SPECIFIC_IMPL
#define IDT_VECTOR f4
#include IDT_SPECIFIC_IMPL
#define IDT_VECTOR f5
#include IDT_SPECIFIC_IMPL
#define IDT_VECTOR f6
#include IDT_SPECIFIC_IMPL
#define IDT_VECTOR f7
#include IDT_SPECIFIC_IMPL
#define IDT_VECTOR f9
#include IDT_SPECIFIC_IMPL
#define IDT_VECTOR fa
#include IDT_SPECIFIC_IMPL
#define IDT_VECTOR fb
#include IDT_SPECIFIC_IMPL
#define IDT_VECTOR fc
#include IDT_SPECIFIC_IMPL
#define IDT_VECTOR fd
#include IDT_SPECIFIC_IMPL
#define IDT_VECTOR fe
#include IDT_SPECIFIC_IMPL
#define IDT_VECTOR ff
#include IDT_SPECIFIC_IMPL
#undef IDT_SPECIFIC_IMPL
#endif /* IDT_SPECIFIC_IMPL */
/*[[[end]]]*/
