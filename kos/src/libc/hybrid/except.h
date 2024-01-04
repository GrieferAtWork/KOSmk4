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
#ifndef GUARD_LIBC_HYBRID_EXCEPT_H
#define GUARD_LIBC_HYBRID_EXCEPT_H 1

#include "../api.h"
/**/

#include <kos/except.h>
#include <stdarg.h>

/* User-/Kernel-space hybrid exception API. */

#ifdef __CC__
DECL_BEGIN

#ifndef FCALL
#define FCALL __FCALL
#endif /* !FCALL */

#define CXA_CC /* nothing */

#ifdef __KERNEL__
typedef void cxa_unwind_exception_t;
#else /* __KERNEL__ */
struct _Unwind_Exception;
typedef struct _Unwind_Exception cxa_unwind_exception_t;
#endif /* !__KERNEL__ */



INTDEF void *CXA_CC libc_cxa_begin_catch(cxa_unwind_exception_t *ptr);
INTDEF void CXA_CC libc_cxa_end_catch(void);

/* Bad usage: missing nesting for TRY. */
INTDEF ATTR_COLD ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL libc_except_badusage_no_nesting)(except_register_state_t const *state);

#ifndef NDEBUG
/* Bad usage: Attempted to call `RETHROW()' from outside of a catch-block. */
INTDEF ATTR_COLD ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL libc_except_badusage_rethrow_outside_catch)(except_register_state_t const *state);

/* Bad usage: Attempted to  call `THROW()'  from inside  of a  catch-block,
 *            without wrapping the throwing code location inside of another
 *            NESTED_TRY-block. */
INTDEF ATTR_COLD ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL libc_except_badusage_throw_inside_catch)(except_register_state_t const *state,
                                                       except_code_t code, size_t argc,
                                                       va_list args);
#endif /* !NDEBUG */

DECL_END
#endif /* __CC__ */


#endif /* !GUARD_LIBC_HYBRID_EXCEPT_H */
