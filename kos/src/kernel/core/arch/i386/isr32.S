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

#include <kernel/compiler.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/tss.h>
#include <kernel/pic.h>
#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state.h>
#include <sys/io.h>


#define VECTOR 81
#include "isr32-impl.S"
#define VECTOR 82
#include "isr32-impl.S"
#define VECTOR 83
#include "isr32-impl.S"
#define VECTOR 84
#include "isr32-impl.S"
#define VECTOR 85
#include "isr32-impl.S"
#define VECTOR 86
#include "isr32-impl.S"
#define VECTOR 87
#include "isr32-impl.S"
#define VECTOR 88
#include "isr32-impl.S"
#define VECTOR 89
#include "isr32-impl.S"
#define VECTOR 8a
#include "isr32-impl.S"
#define VECTOR 8b
#include "isr32-impl.S"
#define VECTOR 8c
#include "isr32-impl.S"
#define VECTOR 8d
#include "isr32-impl.S"
#define VECTOR 8e
#include "isr32-impl.S"
#define VECTOR 8f
#include "isr32-impl.S"
#define VECTOR 90
#include "isr32-impl.S"
#define VECTOR 91
#include "isr32-impl.S"
#define VECTOR 92
#include "isr32-impl.S"
#define VECTOR 93
#include "isr32-impl.S"
#define VECTOR 94
#include "isr32-impl.S"
#define VECTOR 95
#include "isr32-impl.S"
#define VECTOR 96
#include "isr32-impl.S"
#define VECTOR 97
#include "isr32-impl.S"
#define VECTOR 98
#include "isr32-impl.S"
#define VECTOR 99
#include "isr32-impl.S"
#define VECTOR 9a
#include "isr32-impl.S"
#define VECTOR 9b
#include "isr32-impl.S"
#define VECTOR 9c
#include "isr32-impl.S"
#define VECTOR 9d
#include "isr32-impl.S"
#define VECTOR 9e
#include "isr32-impl.S"
#define VECTOR 9f
#include "isr32-impl.S"
#define VECTOR a0
#include "isr32-impl.S"
#define VECTOR a1
#include "isr32-impl.S"
#define VECTOR a2
#include "isr32-impl.S"
#define VECTOR a3
#include "isr32-impl.S"
#define VECTOR a4
#include "isr32-impl.S"
#define VECTOR a5
#include "isr32-impl.S"
#define VECTOR a6
#include "isr32-impl.S"
#define VECTOR a7
#include "isr32-impl.S"
#define VECTOR a8
#include "isr32-impl.S"
#define VECTOR a9
#include "isr32-impl.S"
#define VECTOR aa
#include "isr32-impl.S"
#define VECTOR ab
#include "isr32-impl.S"
#define VECTOR ac
#include "isr32-impl.S"
#define VECTOR ad
#include "isr32-impl.S"
#define VECTOR ae
#include "isr32-impl.S"
#define VECTOR af
#include "isr32-impl.S"
#define VECTOR b0
#include "isr32-impl.S"
#define VECTOR b1
#include "isr32-impl.S"
#define VECTOR b2
#include "isr32-impl.S"
#define VECTOR b3
#include "isr32-impl.S"
#define VECTOR b4
#include "isr32-impl.S"
#define VECTOR b5
#include "isr32-impl.S"
#define VECTOR b6
#include "isr32-impl.S"
#define VECTOR b7
#include "isr32-impl.S"
#define VECTOR b8
#include "isr32-impl.S"
#define VECTOR b9
#include "isr32-impl.S"
#define VECTOR ba
#include "isr32-impl.S"
#define VECTOR bb
#include "isr32-impl.S"
#define VECTOR bc
#include "isr32-impl.S"
#define VECTOR bd
#include "isr32-impl.S"
#define VECTOR be
#include "isr32-impl.S"
#define VECTOR bf
#include "isr32-impl.S"
#define VECTOR c0
#include "isr32-impl.S"
#define VECTOR c1
#include "isr32-impl.S"
#define VECTOR c2
#include "isr32-impl.S"
#define VECTOR c3
#include "isr32-impl.S"
#define VECTOR c4
#include "isr32-impl.S"
#define VECTOR c5
#include "isr32-impl.S"
#define VECTOR c6
#include "isr32-impl.S"
#define VECTOR c7
#include "isr32-impl.S"
#define VECTOR c8
#include "isr32-impl.S"
#define VECTOR c9
#include "isr32-impl.S"
#define VECTOR ca
#include "isr32-impl.S"
#define VECTOR cb
#include "isr32-impl.S"
#define VECTOR cc
#include "isr32-impl.S"
#define VECTOR cd
#include "isr32-impl.S"
#define VECTOR ce
#include "isr32-impl.S"
#define VECTOR cf
#include "isr32-impl.S"
#define VECTOR d0
#include "isr32-impl.S"
#define VECTOR d1
#include "isr32-impl.S"
#define VECTOR d2
#include "isr32-impl.S"
#define VECTOR d3
#include "isr32-impl.S"
#define VECTOR d4
#include "isr32-impl.S"
#define VECTOR d5
#include "isr32-impl.S"
#define VECTOR d6
#include "isr32-impl.S"
#define VECTOR d7
#include "isr32-impl.S"
#define VECTOR d8
#include "isr32-impl.S"
#define VECTOR d9
#include "isr32-impl.S"
#define VECTOR da
#include "isr32-impl.S"
#define VECTOR db
#include "isr32-impl.S"
#define VECTOR dc
#include "isr32-impl.S"
#define VECTOR dd
#include "isr32-impl.S"
#define VECTOR de
#include "isr32-impl.S"
#define VECTOR df
#include "isr32-impl.S"
#define VECTOR e0
#include "isr32-impl.S"
#define VECTOR e1
#include "isr32-impl.S"
#define VECTOR e2
#include "isr32-impl.S"
#define VECTOR e3
#include "isr32-impl.S"
#define VECTOR e4
#include "isr32-impl.S"
#define VECTOR e5
#include "isr32-impl.S"
#define VECTOR e6
#include "isr32-impl.S"
#define VECTOR e7
#include "isr32-impl.S"
#define VECTOR e8
#include "isr32-impl.S"
#define VECTOR e9
#include "isr32-impl.S"
#define VECTOR ea
#include "isr32-impl.S"
#define VECTOR eb
#include "isr32-impl.S"
#define VECTOR ec
#include "isr32-impl.S"
#define VECTOR ed
#include "isr32-impl.S"


#define VECTOR f1
#include "isr32-impl.S"
#define VECTOR f2
#include "isr32-impl.S"
#define VECTOR f3
#include "isr32-impl.S"
#define VECTOR f4
#include "isr32-impl.S"
#define VECTOR f5
#include "isr32-impl.S"
#define VECTOR f6
#include "isr32-impl.S"
#define VECTOR f7
#include "isr32-impl.S"
#define VECTOR f8
#include "isr32-impl.S"
#define VECTOR f9
#include "isr32-impl.S"
#define VECTOR fa
#include "isr32-impl.S"
#define VECTOR fb
#include "isr32-impl.S"
#define VECTOR fc
#include "isr32-impl.S"
#define VECTOR fd
#include "isr32-impl.S"
#define VECTOR fe
#include "isr32-impl.S"
#define VECTOR ff
#include "isr32-impl.S"



