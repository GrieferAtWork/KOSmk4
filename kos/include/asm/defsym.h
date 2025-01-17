/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_DEFSYM_H
#define _ASM_DEFSYM_H 1

#include <__stdinc.h>

/* Helper macros to define linker symbols from C expressions. */
#ifdef __CC__
#define __PRIVATE_DEFINE_SYMBOL_COMMON(name, value, size, ...) \
	__asm__(".type " #name ", \"object\"\n\t"                  \
	        __VA_ARGS__                                        \
	        ".set " #name "," #value "\n\t"                    \
	        ".size " #name "," #size)
#define __PRIVATE_DEFSYM_STR(x) #x
#define DEFINE_PRIVATE_SYMBOL(name, value, size) \
	__PRIVATE_DEFINE_SYMBOL_COMMON(name, value, size, ".local " __PRIVATE_DEFSYM_STR(name) "\n\t")
#define DEFINE_PUBLIC_SYMBOL(name, value, size) \
	__PRIVATE_DEFINE_SYMBOL_COMMON(name, value, size, ".global " __PRIVATE_DEFSYM_STR(name) "\n\t")
#define DEFINE_INTERN_SYMBOL(name, value, size) \
	__PRIVATE_DEFINE_SYMBOL_COMMON(name, value, size, ".global " __PRIVATE_DEFSYM_STR(name) "\n\t.hidden " __PRIVATE_DEFSYM_STR(name) "\n\t")
#define DEFINE_PRIVATE_WEAK_SYMBOL(name, value, size) \
	__PRIVATE_DEFINE_SYMBOL_COMMON(name, value, size, ".weak " __PRIVATE_DEFSYM_STR(name) "\n\t.local " __PRIVATE_DEFSYM_STR(name) "\n\t")
#define DEFINE_PUBLIC_WEAK_SYMBOL(name, value, size) \
	__PRIVATE_DEFINE_SYMBOL_COMMON(name, value, size, ".weak " __PRIVATE_DEFSYM_STR(name) "\n\t.global " __PRIVATE_DEFSYM_STR(name) "\n\t")
#define DEFINE_INTERN_WEAK_SYMBOL(name, value, size) \
	__PRIVATE_DEFINE_SYMBOL_COMMON(name, value, size, ".weak " __PRIVATE_DEFSYM_STR(name) "\n\t.global " __PRIVATE_DEFSYM_STR(name) "\n\t.hidden " __PRIVATE_DEFSYM_STR(name) "\n\t")
#elif defined(__ASSEMBLER__)
#define __PRIVATE_DEFINE_SYMBOL_COMMON(name, value, size_, ...) \
	.type name, "object";                                       \
	__VA_ARGS__                                                 \
	.set name, value;                                           \
	.size name, size_
#define DEFINE_PRIVATE_SYMBOL(name, value, size) \
	__PRIVATE_DEFINE_SYMBOL_COMMON(name, value, size, .local name;)
#define DEFINE_PUBLIC_SYMBOL(name, value, size) \
	__PRIVATE_DEFINE_SYMBOL_COMMON(name, value, size, .global name;)
#define DEFINE_INTERN_SYMBOL(name, value, size) \
	__PRIVATE_DEFINE_SYMBOL_COMMON(name, value, size, .global name; .hidden name;)
#define DEFINE_PRIVATE_WEAK_SYMBOL(name, value, size) \
	__PRIVATE_DEFINE_SYMBOL_COMMON(name, value, size, .weak name; .local name;)
#define DEFINE_PUBLIC_WEAK_SYMBOL(name, value, size) \
	__PRIVATE_DEFINE_SYMBOL_COMMON(name, value, size, .weak name; .global name;)
#define DEFINE_INTERN_WEAK_SYMBOL(name, value, size) \
	__PRIVATE_DEFINE_SYMBOL_COMMON(name, value, size, .weak name; .global name; .hidden name;)
#endif /* ... */

#endif /* !_ASM_DEFSYM_H */
