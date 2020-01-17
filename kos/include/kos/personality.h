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
#ifndef _KOS_PERSONALITY_H
#define _KOS_PERSONALITY_H 1

#include <__stdinc.h>

/* Kernel personality feature codes to configure the behavior of the kernel. */

/*[[[enum]]]*/
#ifdef __CC__
enum {
	KP_INVALID,               /* Invalid/unused personality code. */
	KP_OPEN_CREAT_CHECK_MODE, /* [default=0] The `open(..., O_CREAT, mode)' system call will check
	                           * its `mode' for invalid bits, as opposed to simply masking them away.
	                           * Effect:
	                           *   0: When used by open(), `mode' will always be masked by `07777' (aka. `S_IALLUGO')
	                           *   1: When used by open(), `mode' is checked for invalid bits. If at least one bit is
	                           *      set that cannot be masked by `07777' (aka. `S_IALLUGO'), then an exception
	                           *      `E_INVALID_ARGUMENT_UNKNOWN_FLAG:E_INVALID_ARGUMENT_CONTEXT_OPEN_MODE'
	                           *      is thrown, that may be translated into `EINVAL'
	                           * Compliance:
	                           *   - Posix does not define an errno code for bad bits in open's mode argument.
	                           *     As such, full posix compliance requires this personality to be disabled.
	                           *   - Linux always masks the mode argument and doesn't have a way of changing this.
	                           * Affected programs:
	                           *   - python: Whether intentional or not, python has problems updating its *.pyc
	                           *             files when this personality is enabled. */
	KP_COUNT,                 /* # of different personality codes. */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define KP_INVALID               KP_INVALID               /* Invalid/unused personality code. */
#define KP_OPEN_CREAT_CHECK_MODE KP_OPEN_CREAT_CHECK_MODE /* [default=0] The `open(..., O_CREAT, mode)' system call will check
                                                           * its `mode' for invalid bits, as opposed to simply masking them away.
                                                           * Compliance:
                                                           *   - Posix does not define an errno code for bad bits in open's mode argument.
                                                           *   - As such, full posix compliance requires this personality to be disabled.
                                                           *   - Linux always masks the mode argument and doesn't have a way of changing this.
                                                           * Effect:
                                                           *   0: When used by open(), `mode' will always be masked by `07777' (aka. `S_IALLUGO')
                                                           *   1: When used by open(), `mode' is checked for invalid bits. If at least one bit is
                                                           *      set that cannot be masked by `07777' (aka. `S_IALLUGO'), then an exception
                                                           *      `E_INVALID_ARGUMENT_UNKNOWN_FLAG:E_INVALID_ARGUMENT_CONTEXT_OPEN_MODE'
                                                           *      is thrown, that may be translated into `EINVAL'
                                                           * Affected programs:
                                                           *   - python: Whether intentional or not, python has problems updating its *.pyc
                                                           *             files when this personality is enabled. */
#define KP_COUNT                 KP_COUNT                 /* # of different personality codes. */
#else /* __COMPILER_PREFERR_ENUMS */
#define KP_INVALID               0 /* Invalid/unused personality code. */
#define KP_OPEN_CREAT_CHECK_MODE 1 /* [default=0] The `open(..., O_CREAT, mode)' system call will check
                                    * its `mode' for invalid bits, as opposed to simply masking them away.
                                    * Compliance:
                                    *   - Posix does not define an errno code for bad bits in open's mode argument.
                                    *   - As such, full posix compliance requires this personality to be disabled.
                                    *   - Linux always masks the mode argument and doesn't have a way of changing this.
                                    * Effect:
                                    *   0: When used by open(), `mode' will always be masked by `07777' (aka. `S_IALLUGO')
                                    *   1: When used by open(), `mode' is checked for invalid bits. If at least one bit is
                                    *      set that cannot be masked by `07777' (aka. `S_IALLUGO'), then an exception
                                    *      `E_INVALID_ARGUMENT_UNKNOWN_FLAG:E_INVALID_ARGUMENT_CONTEXT_OPEN_MODE'
                                    *      is thrown, that may be translated into `EINVAL'
                                    * Affected programs:
                                    *   - python: Whether intentional or not, python has problems updating its *.pyc
                                    *             files when this personality is enabled. */
#define KP_COUNT                 2 /* # of different personality codes. */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


#endif /* !_KOS_PERSONALITY_H */
