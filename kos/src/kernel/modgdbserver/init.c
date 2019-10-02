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
#ifndef GUARD_MODGDBSERVER_INIT_C
#define GUARD_MODGDBSERVER_INIT_C 1

#include <kernel/compiler.h>

#include <kernel/debugtrap.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/vm.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <signal.h> /* SIGTRAP */

#include "gdb.h"
#include "server.h" /* GDBServer_Features */

DECL_BEGIN

/* [1..1][const]
 * The fallback host thread used to drive the GDB server in the event
 * of the GDB remote being the one to instigate an exchange (such as
 * sending a \3-byte to stop system-wide execution) */
INTERN REF struct task *GDBServer_FallbackHost = NULL;


PRIVATE void FCALL
GDBServer_TerminateFallbackHostRPC(void *UNUSED(arg)) {
	THROW(E_EXIT_THREAD);
}

PRIVATE DRIVER_INIT void KCALL GDBServer_Fini(void) {
	/* Finalize the remote API. */
	GDBRemote_Fini();

	/* Uninstall interrupt handlers */
	GDBInterrupt_Fini();

	/* Uninstall traps and hooks. */
	vm_onfini_callbacks.remove(&GDB_ClearAllBreakpointsOfVM);
	kernel_debugtraps_uninstall(&GDBServer_DebugTraps);

	/* Terminate the fallback-host thread */
	if (GDBServer_FallbackHost) {
		task_schedule_synchronous_srpc(GDBServer_FallbackHost,
		                               &GDBServer_TerminateFallbackHostRPC);
		decref(GDBServer_FallbackHost);
		GDBServer_FallbackHost = NULL;
	}
}

PRIVATE DRIVER_INIT void KCALL GDBServer_Init(void) {
	TRY {
		/* Initialize the remote API. */
		GDBRemote_Init();

		/* Install interrupt handlers */
		GDBInterrupt_Init();

		/* Hook the vm finalizer to clear breakpoints for that VM. */
		vm_onfini_callbacks.insert(&GDB_ClearAllBreakpointsOfVM);

		/* Create the fallback-host thread. */
		GDBServer_FallbackHost = task_alloc(&vm_kernel);
		task_setup_kernel(GDBServer_FallbackHost, (thread_main_t)&GDBFallbackHost_Main, 0);
		/* Set the Stopped flag to that the fallback-host can't be stopped by GDB. */
		ATOMIC_FETCHOR(GDBServer_FallbackHost->t_flags, TASK_FGDB_STOPPED);
		task_start(GDBServer_FallbackHost, TASK_START_FNORMAL);

		printk(KERN_INFO "[gdb] Wait for attach\n");
		/* Wait until the GDB remote has been attached.
		 * For this purpose, keep waiting on the GDB host to become
		 * unlocked until the `GDB_SERVER_FEATURE_ATTACHED' feature
		 * becomes set. */
		while (!(ATOMIC_READ(GDBServer_Features) & GDB_SERVER_FEATURE_ATTACHED)) {
			task_connect(&GDBServer_HostUnlocked);
			if (ATOMIC_READ(GDBServer_Features) & GDB_SERVER_FEATURE_ATTACHED) {
				task_disconnectall();
				break;
			}
			task_waitfor();
		}

		printk(KERN_INFO "[gdb] Client attached (unlock kernel access & simulate fork())\n");
		/* Expose the kernel core to the GDB remote, and simulate a fork()
		 * -> As far as GDB is concerned, the kernel core is a child of /bin/init
		 * NOTE: This hacky work-around is required because GDB will $h1t itself during
		 *       initialization if it sees more than one process (in this case `/bin/init'
		 *       and `kernel') already attached when starting */
		ATOMIC_FETCHOR(GDBServer_Features, GDB_SERVER_FEATURE_SHOWKERNEL);
		{
			struct debugtrap_reason r;
			r.dtr_signo  = SIGTRAP;
			r.dtr_reason = DEBUGTRAP_REASON_FORK;
			r.dtr_ptrarg = &_bootidle;
			kernel_debugtrap(&r);
		}

	} EXCEPT {
		GDBServer_Fini();
		RETHROW();
	}
}

DECL_END

#endif /* !GUARD_MODGDBSERVER_INIT_C */
