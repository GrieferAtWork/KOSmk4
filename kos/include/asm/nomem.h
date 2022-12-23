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
#ifndef _ASM_NOMEM_H
#define _ASM_NOMEM_H 1

#include <__stdinc.h>

#include <asm/nomem-arch.h>

/* Fallback: if not explicitly stated by the arch, assume 1 page of NOMEM at address 0 */
#ifndef __ARCH_NOMEM_BASE
#include <asm/pagesize.h>
#define __ARCH_NOMEM_BASE 0
#ifdef __ARCH_PAGESIZE
#define __ARCH_NOMEM_SIZE __ARCH_PAGESIZE
#else /* __ARCH_PAGESIZE */
#define __ARCH_NOMEM_SIZE 4096 /* Guess... */
#endif /* !__ARCH_PAGESIZE */
#elif !defined(__ARCH_NOMEM_SIZE)
#error "Arch did no specify nomem size"
#endif /* ... */


/* Figure out how many bits the NOMEM area gives us. */
/*[[[deemon
local isFirst = true;
for (local n: [1:63]) {
	local minSize = 1 << n;
	local minSizeBits = 8;
	while (n > minSizeBits)
		minSizeBits *= 2;
	print("#", (isFirst ? "" : "el"), "if __ARCH_NOMEM_SIZE <= __UINT", minSizeBits, "_C(", minSize.hex(), ")");
	print("#define __ARCH_NOMEM_BITS ", n);
	isFirst = false;
}
print("#else /" "* ... *" "/");
print("#define __ARCH_NOMEM_BITS 64");
print("#endif /" "* !... *" "/");
]]]*/
#if __ARCH_NOMEM_SIZE <= __UINT8_C(0x2)
#define __ARCH_NOMEM_BITS 1
#elif __ARCH_NOMEM_SIZE <= __UINT8_C(0x4)
#define __ARCH_NOMEM_BITS 2
#elif __ARCH_NOMEM_SIZE <= __UINT8_C(0x8)
#define __ARCH_NOMEM_BITS 3
#elif __ARCH_NOMEM_SIZE <= __UINT8_C(0x10)
#define __ARCH_NOMEM_BITS 4
#elif __ARCH_NOMEM_SIZE <= __UINT8_C(0x20)
#define __ARCH_NOMEM_BITS 5
#elif __ARCH_NOMEM_SIZE <= __UINT8_C(0x40)
#define __ARCH_NOMEM_BITS 6
#elif __ARCH_NOMEM_SIZE <= __UINT8_C(0x80)
#define __ARCH_NOMEM_BITS 7
#elif __ARCH_NOMEM_SIZE <= __UINT8_C(0x100)
#define __ARCH_NOMEM_BITS 8
#elif __ARCH_NOMEM_SIZE <= __UINT16_C(0x200)
#define __ARCH_NOMEM_BITS 9
#elif __ARCH_NOMEM_SIZE <= __UINT16_C(0x400)
#define __ARCH_NOMEM_BITS 10
#elif __ARCH_NOMEM_SIZE <= __UINT16_C(0x800)
#define __ARCH_NOMEM_BITS 11
#elif __ARCH_NOMEM_SIZE <= __UINT16_C(0x1000)
#define __ARCH_NOMEM_BITS 12
#elif __ARCH_NOMEM_SIZE <= __UINT16_C(0x2000)
#define __ARCH_NOMEM_BITS 13
#elif __ARCH_NOMEM_SIZE <= __UINT16_C(0x4000)
#define __ARCH_NOMEM_BITS 14
#elif __ARCH_NOMEM_SIZE <= __UINT16_C(0x8000)
#define __ARCH_NOMEM_BITS 15
#elif __ARCH_NOMEM_SIZE <= __UINT16_C(0x10000)
#define __ARCH_NOMEM_BITS 16
#elif __ARCH_NOMEM_SIZE <= __UINT32_C(0x20000)
#define __ARCH_NOMEM_BITS 17
#elif __ARCH_NOMEM_SIZE <= __UINT32_C(0x40000)
#define __ARCH_NOMEM_BITS 18
#elif __ARCH_NOMEM_SIZE <= __UINT32_C(0x80000)
#define __ARCH_NOMEM_BITS 19
#elif __ARCH_NOMEM_SIZE <= __UINT32_C(0x100000)
#define __ARCH_NOMEM_BITS 20
#elif __ARCH_NOMEM_SIZE <= __UINT32_C(0x200000)
#define __ARCH_NOMEM_BITS 21
#elif __ARCH_NOMEM_SIZE <= __UINT32_C(0x400000)
#define __ARCH_NOMEM_BITS 22
#elif __ARCH_NOMEM_SIZE <= __UINT32_C(0x800000)
#define __ARCH_NOMEM_BITS 23
#elif __ARCH_NOMEM_SIZE <= __UINT32_C(0x1000000)
#define __ARCH_NOMEM_BITS 24
#elif __ARCH_NOMEM_SIZE <= __UINT32_C(0x2000000)
#define __ARCH_NOMEM_BITS 25
#elif __ARCH_NOMEM_SIZE <= __UINT32_C(0x4000000)
#define __ARCH_NOMEM_BITS 26
#elif __ARCH_NOMEM_SIZE <= __UINT32_C(0x8000000)
#define __ARCH_NOMEM_BITS 27
#elif __ARCH_NOMEM_SIZE <= __UINT32_C(0x10000000)
#define __ARCH_NOMEM_BITS 28
#elif __ARCH_NOMEM_SIZE <= __UINT32_C(0x20000000)
#define __ARCH_NOMEM_BITS 29
#elif __ARCH_NOMEM_SIZE <= __UINT32_C(0x40000000)
#define __ARCH_NOMEM_BITS 30
#elif __ARCH_NOMEM_SIZE <= __UINT32_C(0x80000000)
#define __ARCH_NOMEM_BITS 31
#elif __ARCH_NOMEM_SIZE <= __UINT32_C(0x100000000)
#define __ARCH_NOMEM_BITS 32
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x200000000)
#define __ARCH_NOMEM_BITS 33
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x400000000)
#define __ARCH_NOMEM_BITS 34
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x800000000)
#define __ARCH_NOMEM_BITS 35
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x1000000000)
#define __ARCH_NOMEM_BITS 36
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x2000000000)
#define __ARCH_NOMEM_BITS 37
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x4000000000)
#define __ARCH_NOMEM_BITS 38
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x8000000000)
#define __ARCH_NOMEM_BITS 39
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x10000000000)
#define __ARCH_NOMEM_BITS 40
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x20000000000)
#define __ARCH_NOMEM_BITS 41
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x40000000000)
#define __ARCH_NOMEM_BITS 42
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x80000000000)
#define __ARCH_NOMEM_BITS 43
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x100000000000)
#define __ARCH_NOMEM_BITS 44
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x200000000000)
#define __ARCH_NOMEM_BITS 45
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x400000000000)
#define __ARCH_NOMEM_BITS 46
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x800000000000)
#define __ARCH_NOMEM_BITS 47
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x1000000000000)
#define __ARCH_NOMEM_BITS 48
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x2000000000000)
#define __ARCH_NOMEM_BITS 49
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x4000000000000)
#define __ARCH_NOMEM_BITS 50
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x8000000000000)
#define __ARCH_NOMEM_BITS 51
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x10000000000000)
#define __ARCH_NOMEM_BITS 52
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x20000000000000)
#define __ARCH_NOMEM_BITS 53
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x40000000000000)
#define __ARCH_NOMEM_BITS 54
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x80000000000000)
#define __ARCH_NOMEM_BITS 55
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x100000000000000)
#define __ARCH_NOMEM_BITS 56
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x200000000000000)
#define __ARCH_NOMEM_BITS 57
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x400000000000000)
#define __ARCH_NOMEM_BITS 58
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x800000000000000)
#define __ARCH_NOMEM_BITS 59
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x1000000000000000)
#define __ARCH_NOMEM_BITS 60
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x2000000000000000)
#define __ARCH_NOMEM_BITS 61
#elif __ARCH_NOMEM_SIZE <= __UINT64_C(0x4000000000000000)
#define __ARCH_NOMEM_BITS 62
#else /* ... */
#define __ARCH_NOMEM_BITS 64
#endif /* !... */
/*[[[end]]]*/


/* Helper macros to check if NOMEM pointers, as well as encode/decode their payloads:
 * >> bool        __ARCH_NOMEM_CHECK(void const *p);
 * >> bool        __ARCH_NOMEM_CHECK(uintptr_t p);
 * >> void const *__ARCH_NOMEM_ENCODE(uintptr_t p);
 * >> uintptr_t   __ARCH_NOMEM_DECODE(void const *p); */
#if __ARCH_NOMEM_BASE == 0
#define __ARCH_NOMEM_CONTAINS_NULL
#define __ARCH_NOMEM_CHECK(p) (__CCAST(__UINTPTR_TYPE__)(p) < __ARCH_NOMEM_SIZE)
#define __ARCH_NOMEM_ENCODE   __CCAST(void const *)
#define __ARCH_NOMEM_DECODE   __CCAST(__UINTPTR_TYPE__)
#else /* __ARCH_NOMEM_BASE == 0 */
#include <hybrid/limitcore.h>
#if (__ARCH_NOMEM_BASE + (__ARCH_NOMEM_SIZE - 1)) == __UINTPTR_MAX__
#define __ARCH_NOMEM_CHECK(p) (__CCAST(__UINTPTR_TYPE__)(p) >= __ARCH_NOMEM_BASE)
#else /* (__ARCH_NOMEM_BASE + (__ARCH_NOMEM_SIZE - 1)) == __UINTPTR_MAX__ */
#define __ARCH_NOMEM_CHECK(p)                             \
	(__CCAST(__UINTPTR_TYPE__)(p) >= __ARCH_NOMEM_BASE && \
	 __CCAST(__UINTPTR_TYPE__)(p) <= (__ARCH_NOMEM_BASE + (__ARCH_NOMEM_SIZE - 1)))
#endif /* (__ARCH_NOMEM_BASE + (__ARCH_NOMEM_SIZE - 1)) != __UINTPTR_MAX__ */
#define __ARCH_NOMEM_ENCODE(p) __CCAST(void const *)((p) + __ARCH_NOMEM_BASE)
#define __ARCH_NOMEM_DECODE(p) (__CCAST(__UINTPTR_TYPE__)(p) - __ARCH_NOMEM_BASE)
#endif /* __ARCH_NOMEM_BASE != 0 */

#endif /* !_ASM_NOMEM_H */
