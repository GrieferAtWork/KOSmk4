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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_IOPERM_C
#define GUARD_APPS_SYSTEM_TEST_TEST_IOPERM_C 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>
#include <sys/io.h>

#ifdef __port_t
#include <kos/except.h>
#include <kos/types.h>
#include <sys/perm.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

DECL_BEGIN

#define portno 0x3f8
static char const s[] = "\n"
                        "HELLO QEMU DEBUG PORT\n"
                        "HELLO QEMU DEBUG PORT\n"
                        "HELLO QEMU DEBUG PORT\n"
                        "\n";

LOCAL void doio() {
	outsb(portno, s, strlen(s));
}

#define assert_thrown(code) \
	assertf(was_thrown(code), "except_code(): %#Ix", except_code())

DEFINE_TEST(ioperm_works_correctly) {
	TRY {
		/* Make sure that outsb() doesn't work by default */
		doio();
		assert_failed("outsb:defl: ok\n");
	} EXCEPT {
		assert_thrown(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE);
	}
	TRY {
		/* Make sure outsb() works with IOPL=3 */
		EQ(0, iopl(3));
		doio();
	} EXCEPT {
		assert_failed("outsb:iopl(3): except_code(): %#Ix\n", except_code());
	}
	TRY {
		/* Make sure outsb() doesn't work with IOPL=0 */
		EQ(0, iopl(0));
		doio();
		assert_failed("outsb:iopl(0): ok\n");
	} EXCEPT {
		assert_thrown(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE);
	}
	TRY {
		/* Make sure ioperm() can be used to enable access to ports */
		EQ(0, ioperm(portno, 1, 1));
		doio();
	} EXCEPT {
		assert_failed("outsb:ioperm(1): except_code(): %#Ix\n", except_code());
	}
	{
		pid_t cpid;
		ISpos((cpid = fork()));
		if (cpid == 0) {
			/* Make sure that the child process inherited the ioperm() */
			TRY {
				doio();
			} EXCEPT {
				assert_failed("child:outsb:ioperm(1): except_code(): %#Ix\n", except_code());
			}
			TRY {
				/* Turn off permissions within the child process. */
				EQ(0, ioperm(portno, 1, 0));
				doio();
				assert_failed("child:outsb:ioperm(0): ok\n");
			} EXCEPT {
				assert_thrown(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE);
			}
			_Exit(0);
		}

		/* Wait for the child process, thus ensuring that our own
		 * thread got preempted at least once */
		errno = EOK;
		while (waitpid(cpid, NULL, 0) != cpid) {
			EQerrno(EOK);
		}
	}
	/* Make  sure that ioperm() continues to work after fork() and preemption
	 * This part is crucial,  since this is where  the CPU itself accesses  a
	 * kernel-space structure as-per instruction from user-space (essentially
	 * meaning that it is user-space  that accesses kernel-space memory in  a
	 * certain way) */
	TRY {
		doio();
	} EXCEPT {
		assert_failed("outsb:ioperm(1): except_code(): %#Ix\n", except_code());
	}
	TRY {
		/* Make sure ioperm() only enables access to the specified ports */
		outsb(portno + 1, s, strlen(s));
		assert_failed("outsb:ioperm+1: ok\n");
	} EXCEPT {
		assert_thrown(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE);
	}
	TRY {
		/* Make sure ioperm() can also be used to turn off permissions */
		EQ(0, ioperm(portno, 1, 0));
		doio();
		assert_failed("outsb:ioperm(0): ok\n");
	} EXCEPT {
		assert_thrown(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE);
	}
}


DECL_END
#endif /* __port_t */

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_IOPERM_C */
