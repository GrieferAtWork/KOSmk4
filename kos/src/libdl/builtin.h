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
#ifndef GUARD_LIBDL_BUILTIN_H
#define GUARD_LIBDL_BUILTIN_H 1

/* NOTE: Don't #include "api.h" from this header! */
#include <__stdinc.h>

/* Addressable sections of the RTLD driver itself.
 *
 * Of note here are mostly the .eh_frame and  .gcc_except_table
 * sections, which are required for allowing exceptions to work
 * properly when being propagated through the callbacks invoked
 * by the RTLD driver.
 *
 * NOTE: Each section has 2 symbols defined by the linker script:
 *       `__rtld_<name>_start' and `__rtld_<name>_end', that  are
 *       used to lazily  fill in section  information as-per  the
 *       request of a  call to `dllocksection(3D)'  when given  a
 *       handle for the RTLD core library. */
#define BUILTIN_SECTIONS_COUNT 6
#define BUILTIN_SECTIONS_ENUMERATE(cb)                                                    \
	cb(0, ".text",             text,             SHT_PROGBITS, SHF_ALLOC | SHF_EXECINSTR) \
	cb(1, ".rodata",           rodata,           SHT_PROGBITS, SHF_ALLOC)                 \
	cb(2, ".eh_frame",         eh_frame,         SHT_PROGBITS, SHF_ALLOC)                 \
	cb(3, ".gcc_except_table", gcc_except_table, SHT_PROGBITS, SHF_ALLOC)                 \
	cb(4, ".data",             data,             SHT_PROGBITS, SHF_ALLOC | SHF_WRITE)     \
	cb(5, ".bss",              bss,              SHT_NOBITS,   SHF_ALLOC | SHF_WRITE)

/* For the purpose of being able to safely handle exceptions the same way
 * loaded modules do, a couple of global functions that aren't defined by
 * the RTLD driver itself need to be provided by loaded libraries.
 *
 * Note  that these functions are only needed when thrown exceptions pass
 * through functions apart of the RTLD core, meaning that when exceptions
 * aren't being used by the hosted application or its libraries, or  even
 * if no exception is ever thrown from an  `__attribute__((constructor))'
 * function,  these are never  loaded. - However, if  they are, then they
 * must be provided by one of the loaded libraries (usually that  library
 * simply being `libc.so')
 *
 * If  one of these functions is used, but isn't provided by any of the
 * loaded modules, the hosted application gets terminated ungracefully,
 * and an error message is written to the system log.
 *
 * HINT: When required, the functions are searched for the same  way
 *       `dlsym(RTLD_DEFAULT, ...)' would search for them, following
 *       regular symbol lookup order throughout all globally visible
 *       libraries.
 * NOTE: The behavior of these functions is specified and standardized
 *       in different places. - Search  around the project and on  the
 *       Internet to find out what each of these has to do, and how it
 *       has to do exactly that. */
#define BUILTIN_GLOBALS_ENUMERATE(cb) \
	cb(__gxx_personality_v0)          \
	cb(__cxa_begin_catch)             \
	cb(__cxa_end_catch)               \
	cb(__cxa_rethrow)                 \
	cb(_Unwind_Resume)

#endif /* !GUARD_LIBDL_BUILTIN_H */
