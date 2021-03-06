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
#ifndef GUARD_LIBC_USER_PROCESS_C
#define GUARD_LIBC_USER_PROCESS_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>
#include <sys/wait.h>

#include <malloc.h>
#include <sched.h>
#include <stdlib.h>
#include <string.h>

#include "../libc/dl.h"
#include "../libc/globals.h"
#include "process.h"

DECL_BEGIN


#ifdef __NO_ATTR_STDCALL
#define _BEGINTHREADEX_CC __LIBDCALL
#else /* __NO_ATTR_STDCALL */
#define _BEGINTHREADEX_CC __ATTR_STDCALL
#endif /* !__NO_ATTR_STDCALL */

struct simple_thread_data {
	void (LIBDCALL *std_entry)(void *arg); /* [1..1] Entry callback. */
	void           *std_arg;               /* Entry argument. */
};

PRIVATE ATTR_SECTION(".text.crt.dos.sched.thread.simple_thread_entry") u32
_BEGINTHREADEX_CC simple_thread_entry(void *arg) {
	struct simple_thread_data data;
	memcpy(&data, arg, sizeof(struct simple_thread_data));
	free(arg);
	(*data.std_entry)(data.std_arg);
	return 0;
}


/*[[[head:libc__beginthread,hash:CRC-32=0xd8642289]]]*/
INTERN ATTR_SECTION(".text.crt.dos.sched.thread") uintptr_t
NOTHROW_NCX(LIBCCALL libc__beginthread)(__dos_beginthread_entry_t entry,
                                        u32 stacksz,
                                        void *arg)
/*[[[body:libc__beginthread]]]*/
{
	struct simple_thread_data *data;
	uintptr_t result;
	data = (struct simple_thread_data *)malloc(sizeof(struct simple_thread_data));
	if unlikely(!data)
		return (uintptr_t)-1;
	data->std_entry = entry;
	data->std_arg   = arg;
	result = _beginthreadex(NULL,
	                        stacksz,
	                        &simple_thread_entry,
	                        data,
	                        0,
	                        NULL);
	if unlikely(!result)
		free(data);
	return result;
}
/*[[[end:libc__beginthread]]]*/



struct dos_thread_data {
	u32 (_BEGINTHREADEX_CC *dtd_entry)(void *arg); /* [1..1] Entry callback. */
	void                   *dtd_arg;               /* Entry argument. */
};
PRIVATE ATTR_SECTION(".text.crt.dos.sched.thread.dos_thread_entry")
int LIBCCALL dos_thread_entry(void *arg) {
	int result;
	struct dos_thread_data data;
	memcpy(&data, arg, sizeof(struct dos_thread_data));
	free(arg);
	result = (int)(*data.dtd_entry)(data.dtd_arg);
	return result;
}

/*[[[head:libc__beginthreadex,hash:CRC-32=0x5f8be1b6]]]*/
INTERN ATTR_SECTION(".text.crt.dos.sched.thread") uintptr_t
NOTHROW_NCX(LIBCCALL libc__beginthreadex)(void *sec,
                                          u32 stacksz,
                                          __dos_beginthreadex_entry_t entry,
                                          void *arg,
                                          u32 flags,
                                          u32 *threadaddr)
/*[[[body:libc__beginthreadex]]]*/
{
	pid_t result;
	struct dos_thread_data *data;
	(void)sec;
	(void)stacksz;
	(void)flags;
	data = (struct dos_thread_data *)malloc(sizeof(struct dos_thread_data));
	if unlikely(!data)
		return (uintptr_t)-1;
	data->dtd_entry = entry;
	data->dtd_arg   = arg;
	result = clone(&dos_thread_entry,
	               CLONE_CHILDSTACK_AUTO,
	               CLONE_VM | CLONE_FS | CLONE_FILES |
	               CLONE_SIGHAND | CLONE_THREAD,
	               arg);
	if unlikely(result == -1) {
		free(data);
		result = 0;
	}
	if (threadaddr)
		*threadaddr = (u32)result;
	return result;
}
/*[[[end:libc__beginthreadex]]]*/


/*[[[head:libc__endthreadex,hash:CRC-32=0x627e50db]]]*/
INTERN ATTR_SECTION(".text.crt.dos.sched.thread") void
NOTHROW_NCX(LIBCCALL libc__endthreadex)(u32 exitcode)
/*[[[body:libc__endthreadex]]]*/
{
	sys_exit((int)exitcode);
}
/*[[[end:libc__endthreadex]]]*/

INTDEF void LIBCCALL libc_run_atexit(int status);

/*[[[head:libc__cexit,hash:CRC-32=0xb122eb11]]]*/
INTERN ATTR_SECTION(".text.crt.dos.sched.process") void
(LIBCCALL libc__cexit)(void) THROWS(...)
/*[[[body:libc__cexit]]]*/
{
	/* Same as `exit()', but without actually exiting... */
	dlauxctrl(NULL, DLAUXCTRL_RUNTLSFINI, NULL, NULL);
	libc_run_atexit(0);
	dlauxctrl(NULL, DLAUXCTRL_RUNFINI, NULL, NULL);
}
/*[[[end:libc__cexit]]]*/




/*[[[start:exports,hash:CRC-32=0x13d1477b]]]*/
DEFINE_PUBLIC_ALIAS(_beginthread, libc__beginthread);
DEFINE_PUBLIC_ALIAS(_beginthreadex, libc__beginthreadex);
DEFINE_PUBLIC_ALIAS(_endthreadex, libc__endthreadex);
DEFINE_PUBLIC_ALIAS(_cexit, libc__cexit);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PROCESS_C */
