/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_APPS_RPC_SERVICE_MAIN_C
#define GUARD_APPS_RPC_SERVICE_MAIN_C 1

#include <hybrid/compiler.h>

#include <kos/syscalls.h>
#include <kos/ksysctl.h>

#include <signal.h>

DECL_BEGIN

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;
	/* This program was used to test a problem related to exception unwinding
	 * while inside of `task_serve()' (s.a. `LOG_SEGMENT_INCONSISTENCY()' in
	 * `kos/src/kernel/core/arch/i386/except.c')
	 * -> Start this program and press CTRL+C a couple of times (which will
	 *    eventually cause an E_INTERRUPT_USER_RPC to be thrown and propagated
	 *    through `task_serve()', that demonstrateted a design flaw caused by
	 *    a miss-understanding of how `pushl %<SEGMENT_REGISTER>' works on
	 *    different CPUs)
	 * (To exit the program, send SIGQUIT using CTRL+\ (or its alias: CTRL+4)) */
	signal(SIGINT, SIG_IGN);
	for (;;) {
		sys_rpc_service();
	}
	return 0;
}

DECL_END

#endif /* !GUARD_APPS_RPC_SERVICE_MAIN_C */
