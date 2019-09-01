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
#ifndef GUARD_LIBRPC_RPC_C
#define GUARD_LIBRPC_RPC_C 1
#define _KOS_KERNEL_SOURCE 1

#include "rpc.h"

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/except.h>
#include <kos/syscalls.h> /* From libc.so */
#include <kos/types.h>

#include <errno.h>

#include <librpc/rpc.h>

#ifdef __KERNEL__
#include <kernel/except.h>
#endif

DECL_BEGIN

/* >> rpc_service(2)
 * Service RPC callbacks (user-space variant of the kernel-space `task_serve()')
 * @return:  1: At least 1 RPC callback was serviced. (though this may
 *              have been a kernel-level RPC that didn't actually affect
 *              user-space)
 * @return:  0: No RPC callbacks were served.
 * @return: -1: Error (s.a. `errno')
 * @throws: * : Anything (RPC callbacks may throw exceptions) */
INTERN int CC librpc_service(void) {
	errno_t result;
	result = sys_rpc_service();
	if unlikely(E_ISERR(result)) {
		errno  = -result;
		result = -1;
	}
	return result;
}


/* >> rpc_schedule_ex(2)
 * Schedule an RPC for execution on the specified `target' thread.
 * @param: target:    The targeted thread.
 * @param: flags:     RPC flags (one of `RPC_SCHEDULE_*', or'd with a set of `RPC_SCHEDULE_FLAG_*')
 * @param: program:   An RPC loader program (vector of `RPC_PROGRAM_OP_*')
 * @param: arguments: Arguments for the RPC loader program.
 * @return: 1:  The specified `target' thread has already terminated.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno')
 * @throws: E_PROCESS_EXITED:  `target' does not reference a valid process
 * @throws: E_INVALID_ARGUMENT: The given `flag' is invalid.
 * NOTE: The system call of this function is called `sys_rpc_schedule()' */
INTERN int CC
librpc_schedule_ex(pid_t target, syscall_ulong_t flags,
                   uint8_t const *__restrict program,
                   void **arguments) {
	errno_t result;
	result = sys_rpc_schedule(target,
	                          flags,
	                          program,
	                          arguments);
	if unlikely(E_ISERR(result)) {
		errno  = -result;
		result = -1;
	}
	return result;
}

DEFINE_PUBLIC_ALIAS(rpc_service, librpc_service);
DEFINE_PUBLIC_ALIAS(rpc_schedule_ex, librpc_schedule_ex);

DECL_END

#endif /* !GUARD_LIBRPC_RPC_C */
