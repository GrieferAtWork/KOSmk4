/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBUNWIND_ERRNO_H
#define _LIBUNWIND_ERRNO_H 1

#include "api.h"

#include <hybrid/typecore.h>

/* Unwind error codes. */
#define UNWIND_SUCCESS                       0 /* Success */
#define UNWIND_NO_FRAME                      1 /* No FDE descriptor is associated with the given PC */
#define UNWIND_INVALID_REGISTER              2 /* Invalid register accessed. */
#define UNWIND_SEGFAULT                      3 /* Segfault when reading memory. */
#define UNWIND_BADALLOC                      4 /* Failed to process `.cfi_remember_state' (encountered too often). */
#define UNWIND_EMULATOR_UNKNOWN_INSTRUCTION  5 /* Unknown instruction encountered. */
#define UNWIND_EMULATOR_ILLEGAL_INSTRUCTION  6 /* Malformed instruction encountered. */
#define UNWIND_EMULATOR_STACK_OVERFLOW       7 /* Expression stack overflow. */
#define UNWIND_EMULATOR_STACK_UNDERFLOW      8 /* Expression stack underflow. */
#define UNWIND_EMULATOR_BADJMP               9 /* Attempted to jump outside the valid code segment. */
#define UNWIND_EMULATOR_LOOP                10 /* Too many backwards jumps. */
#define UNWIND_EMULATOR_BUFFER_TOO_SMALL    11 /* The given `sm_piecebuf' buffer is too small. */
#define UNWIND_EMULATOR_DIVIDE_BY_ZERO      12 /* Attempted to divide or do module by zero(0) */
#define UNWIND_EMULATOR_NO_FUNCTION         13 /* An addressed function isn't available for the associated PC. */
#define UNWIND_EMULATOR_INVALID_FUNCTION    14 /* Attempted to call an invalid CFI function. */
#define UNWIND_EMULATOR_NO_CFA              15 /* Failed to calculate the CFA at the current PC */
#define UNWIND_EMULATOR_NO_RETURN_VALUE     16 /* Value stack was empty upon expression return. */
#define UNWIND_EMULATOR_NOT_WRITABLE        17 /* Attempted to write a data-piece to a CONST or RO_LVALUE stack entry. */
#define UNWIND_CFA_UNKNOWN_INSTRUCTION      18 /* Unknown CFA instruction encountered. */
#define UNWIND_CFA_ILLEGAL_INSTRUCTION      19 /* Illegal CFA instruction encountered. */
#define UNWIND_APPLY_NOADDR_REGISTER        20 /* Attempted to use a non-address (e.g. FPU) register as a memory location */
#define UNWIND_PERSONALITY_ERROR            21 /* A personality function returned an error. */
#define UNWIND_OPTIMIZED_AWAY               22 /* The requested information has been optimized away. */
#define UNWIND_CORRUPTED                    23 /* Corrupted debug information. */
/*...*/
#define UNWIND_USER_DISABLED                64 /* (Used internally by the kernel): User-space exception handling is disabled. */
#define UNWIND_USER_NOTHROW                 65 /* (Used internally by libc): Unable to unwind a function marked as NOTHROW */
#define UNWIND_USER_RECURSION               66 /* (Used internally by libc): At least 2 additional exceptions were thrown whilst already in the process of unwinding another exception. */
#define UNWIND_USER_DLERROR                 67 /* (Used internally by libc): Mode#4 unwinding failed because libdl returned an error (s.a. `dlerror()' and `eval dl_globals.dg_errmsg') */
#define UNWIND_USER_ABORT                   68 /* (Used internally by libc): `abort()' or `std::terminate()' was called. */
#define UNWIND_USER_ASSERT                  69 /* (Used internally by libc): Assertion failure (s.a. `assert_failed()') */
#define UNWIND_USER_ACHECK                  70 /* (Used internally by libc): Assertion check failure (restartable assertion failure; aka. the one w/ the "retry" button). */
#define UNWIND_USER_SSP                     71 /* (Used internally by libc): Stack smash protection fault (`__stack_chk_fail()' was called). */
#define UNWIND_USER_BADTLS                  72 /* (Used internally by libc): Bad TLS pointer (cannot load exception context). */


#define __SIZEOF_UNWIND_ERRNO_T__ __SIZEOF_INT__

#ifdef __CC__
__DECL_BEGIN

/* Unwind error code (one of the `UNWIND_*' macros above) */
typedef unsigned int unwind_errno_t;

__DECL_END
#endif /* __CC__ */


#endif /* !_LIBUNWIND_ERRNO_H */
