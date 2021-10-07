/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_USER_HANDLE_DEBUGGER_C
#define GUARD_KERNEL_SRC_USER_HANDLE_DEBUGGER_C 1
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_DEBUGGER
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <kernel/handle.h>

#include <stddef.h>

DECL_BEGIN


PRIVATE ATTR_DBGTEXT void KCALL
printhandle(unsigned int fd, struct handle const *__restrict hand) {
	if (hand->h_type == HANDLE_TYPE_UNDEFINED)
		return; /* Unused handle... */
	dbg_printf(DBGSTR(AC_WHITE("%u") "\t%c%c%c%c%c%c %-16s"),
	           fd,
	           (hand->h_mode & IO_ACCMODE) != IO_WRONLY ? 'r' : '-',
	           (hand->h_mode & IO_ACCMODE) != IO_RDONLY ? 'w' : '-',
	           hand->h_mode & IO_CLOEXEC ? 'e' : '-',
	           hand->h_mode & IO_CLOFORK ? 'f' : '-',
	           hand->h_mode & IO_APPEND ? 'a' : '-',
	           hand->h_mode & IO_NONBLOCK ? 'n' : '-',
	           handle_typename(*hand));
	handle_print(hand, &dbg_printer, NULL);
	dbg_putc('\n');
}

DBG_COMMAND(lsfd,
            "lsfd\n"
            "Enumate open file descriptors within the current thread\n"
            "The " AC_WHITE("flags") " field consists of:\n"
            "\t" AC_WHITE("r") ": Read-access is permitted\n"
            "\t" AC_WHITE("w") ": Write-access is permitted\n"
            "\t" AC_WHITE("e") ": The " AC_WITHFG(ANSITTY_CL_PURPLE, "CLOEXEC") " flag is set\n"
            "\t" AC_WHITE("f") ": The " AC_WITHFG(ANSITTY_CL_PURPLE, "CLOFORK") " flag is set\n"
            "\t" AC_WHITE("a") ": Writes append to the end of the file\n"
            "\t" AC_WHITE("n") ": Reading/writing does not block\n") {
	struct handle_manager *self;
	self = FORTASK(dbg_current, this_handle_manager);
	dbg_printf(DBGSTR("fd\tflags type             repr\n"));
	if (self->hm_mode == HANDLE_MANAGER_MODE_LINEAR) {
		unsigned int i;
		for (i = 0; i < self->hm_linear.hm_alloc; ++i)
			printhandle(i, &self->hm_linear.hm_vector[i]);
	} else {
		unsigned int i;
		for (i = 0; i <= self->hm_hashvector.hm_hashmsk; ++i) {
			struct handle_hashent ent;
			ent = self->hm_hashvector.hm_hashvec[i];
			if (ent.hh_handle_id == HANDLE_HASHENT_SENTINEL_ID)
				continue;
			if (ent.hh_vector_index == (unsigned int)-1)
				continue;
			printhandle(ent.hh_handle_id,
			            &self->hm_hashvector.hm_vector[ent.hh_vector_index]);
		}
	}
	return 0;
}



DECL_END

#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_USER_HANDLE_DEBUGGER_C */
