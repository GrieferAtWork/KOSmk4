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
#ifndef _KOS_EXEC_IDATA_H
#define _KOS_EXEC_IDATA_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

#if !defined(__KOS__)
#error "This header requires support for `STT_KOS_IDATA', which only exists on KOS. -- ~Sorry~"
#endif /* !__KOS__ */

/* Helpers for KOS's ELF extension: STT_KOS_IDATA
 *
 *
 * libmylib.c -> libmylib.so:
 * >>
 * >> #include <kos/exec/idata.h> // DEFINE_PUBLIC_IDATA
 * >> #include <sys/types.h>      // pid_t
 * >> #include <sched.h>          // sched_yield
 * >> #include <hybrid/atomic.h>  // ATOMIC_CMPXCH, ATOMIC_WRITE
 * >>
 * >> PRIVATE ATTR_USED pid_t *resolve_program_pid() {
 * >>     // Export a public symbol "program_pid" from this library that
 * >>     // is a data-object and will lazily invoke this function if used
 * >>     DEFINE_PUBLIC_IDATA(program_pid, resolve_program_pid);
 * >>     static pid_t program_pid  = 0; // The library address of `program_pid'
 * >>     static int program_loaded = 0; // init-once barrier
 * >> again:
 * >>     if (program_loaded != 2) {
 * >>         if (!ATOMIC_CMPXCH(program_loaded, 0, 1)) {
 * >>             sched_yield();
 * >>             goto again;
 * >>         }
 * >>         // Lazily initialize global data upon first access
 * >>         program_pid = getpid();
 * >>         ATOMIC_WRITE(program_loaded, 2);
 * >>     }
 * >>     return &program_pid;
 * >> }
 *
 * main.c:
 * >> #include <stdio.h>
 * >> extern pid_t program_pid;
 * >> int main() {
 * >>     printf("program_pid = %d\n", program_pid);
 * >>     return 0;
 * >> }
 *
 * Note that in the above example, `resolve_program_pid()' from `libmylib.so'
 * will only be  called when  the symbol  `program_pid' ends  up being  used!
 *
 * NOTE: The weird wrapper with `.set .Lidata_foo, rfoo - 1; .set foo, .Lidata_foo + 1'
 *       is required (and cannot be  replaced with `.set foo, rfoo') because  otherwise
 *       we won't be able to  explicitly assign the proper  .size to the symbol  `foo',
 *       because  otherwise gas  will think that  this is an  alias symbol declaration,
 *       and will lock us out of modifying  the new symbol's size attribute by  forcing
 *       it to be equivalent to the size of the resolver function... */

#ifdef __CC__
#define DEFINE_PUBLIC_IDATA_G(name, resolve, size)                                           \
	__asm__(".globl " __PP_PRIVATE_STR(name) "\n"                                            \
	        ".type  " __PP_PRIVATE_STR(name) ", @kos_indirect_data\n"                        \
	        ".set   .Lidata_" __PP_PRIVATE_STR(name) ", " __PP_PRIVATE_STR(resolve) " - 1\n" \
	        ".set   " __PP_PRIVATE_STR(name) ", .Lidata_" __PP_PRIVATE_STR(name) " + 1\n"    \
	        ".size  " __PP_PRIVATE_STR(name) ", " __PP_PRIVATE_STR(size) "\n")
#define DEFINE_PUBLIC_IDATA(name, resolve) \
	DEFINE_PUBLIC_IDATA_EX(name, resolve, sizeof((resolve)()))
#define DEFINE_PUBLIC_IDATA_EX(name, resolve, size)                                       \
	__asm__(".globl " __PP_PRIVATE_STR(name) "\n"                                         \
	        ".type  " __PP_PRIVATE_STR(name) ", @kos_indirect_data\n"                     \
	        ".set   .Lidata_" __PP_PRIVATE_STR(name) ", %p0 - 1\n"                        \
	        ".set   " __PP_PRIVATE_STR(name) ", .Lidata_" __PP_PRIVATE_STR(name) " + 1\n" \
	        ".size  " __PP_PRIVATE_STR(name) ", %p1\n"                                    \
	        : : "X" ((void *)(resolve)), "X" (size))
#elif defined(__ASSEMBLER__)
#define DEFINE_PUBLIC_IDATA_G(name, resolve, size_) \
	.globl name;                                    \
	.type  name, @kos_indirect_data;                \
	.set   .Lidata_##name, (resolve) - 1;           \
	.set   name, .Lidata_##name + 1;                \
	.size  name, size_
#endif /* ... */


#endif /* !_KOS_EXEC_IDATA_H */
