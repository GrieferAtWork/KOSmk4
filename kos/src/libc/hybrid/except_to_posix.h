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
#ifndef GUARD_LIBC_HYBRID_EXCEPT_TO_POSIX_H
#define GUARD_LIBC_HYBRID_EXCEPT_TO_POSIX_H 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <kos/except.h>
#include <stdbool.h>

#ifdef __KERNEL__
#define NOTHROW_NCX_KERNEL  __NOTHROW_NCX
#else /* __KERNEL__ */
#define NOTHROW_NCX_KERNEL  __NOTHROW
#endif /* !__KERNEL__ */


DECL_BEGIN

struct __siginfo_struct;

/* Transform the given exception into a posix errno value. */
INTDEF WUNUSED errno_t
NOTHROW_NCX_KERNEL(LIBCCALL libc_error_as_errno)(struct exception_data const *__restrict data);

/* Transform the currently thrown exception into a posix signal.
 * If doing this is possible, fill in `*result' and return `true'.
 * Otherwise, `*result' is left in an undefined state, and `false' is returned. */
INTDEF WUNUSED bool 
NOTHROW_NCX_KERNEL(LIBCCALL libc_error_as_signal)(struct exception_data const *__restrict data,
                                                  struct __siginfo_struct *__restrict result);


DECL_END

#endif /* !GUARD_LIBC_HYBRID_EXCEPT_TO_POSIX_H */
