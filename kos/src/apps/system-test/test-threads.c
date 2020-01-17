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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_THREADS_C
#define GUARD_APPS_SYSTEM_TEST_TEST_THREADS_C 1
#define _KOS_SOURCE 1

#include <hybrid/compiler.h>

#include <kos/except.h>
#include <kos/types.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <threads.h>

DECL_BEGIN

PRIVATE char message_pointer[] = "Hello!";
PRIVATE bool did_run_my_thread_main = false;

PRIVATE int my_thread_main(void *ptr) {
	assertf(!did_run_my_thread_main,
	        "Thread main already executed");
	assertf((char *)ptr == message_pointer,
	        "ptr = %p, message_pointer = %p",
	        ptr, message_pointer);
	did_run_my_thread_main = true;
	return 1234;
}

DEFINE_TEST(multi_threading) {
	thrd_t thread;
	int error, result;
	did_run_my_thread_main = false;
	COMPILER_BARRIER();
	error = thrd_create(&thread, &my_thread_main, (void *)message_pointer);
	assertf(error == thrd_success, "error = %d", error);
	COMPILER_BARRIER();
	error = thrd_join(thread, &result);
	assertf(error == thrd_success, "error = %d", error);
	assertf(did_run_my_thread_main, "Thread not actually executed");
	assertf(result == 1234, "result = %d", result);
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_THREADS_C */
