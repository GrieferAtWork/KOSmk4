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
#ifndef _KOS_BITS_EXCEPT_REGISTER_STATE_HELPERS_H
#define _KOS_BITS_EXCEPT_REGISTER_STATE_HELPERS_H 1

#include <kos/bits/except-register-state.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

/* Unescape IS_* macros */
#undef EXCEPT_REGISTER_STATE_TYPE_IS_UCPUSTATE
#undef EXCEPT_REGISTER_STATE_TYPE_IS_LCPUSTATE
#undef EXCEPT_REGISTER_STATE_TYPE_IS_KCPUSTATE
#undef EXCEPT_REGISTER_STATE_TYPE_IS_ICPUSTATE
#undef EXCEPT_REGISTER_STATE_TYPE_IS_SCPUSTATE
#undef EXCEPT_REGISTER_STATE_TYPE_IS_FCPUSTATE
#ifdef __EXCEPT_REGISTER_STATE_TYPE_IS_UCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_UCPUSTATE
#endif /* __EXCEPT_REGISTER_STATE_TYPE_IS_UCPUSTATE */
#ifdef __EXCEPT_REGISTER_STATE_TYPE_IS_LCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_LCPUSTATE
#endif /* __EXCEPT_REGISTER_STATE_TYPE_IS_LCPUSTATE */
#ifdef __EXCEPT_REGISTER_STATE_TYPE_IS_KCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_KCPUSTATE
#endif /* __EXCEPT_REGISTER_STATE_TYPE_IS_KCPUSTATE */
#ifdef __EXCEPT_REGISTER_STATE_TYPE_IS_ICPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_ICPUSTATE
#endif /* __EXCEPT_REGISTER_STATE_TYPE_IS_ICPUSTATE */
#ifdef __EXCEPT_REGISTER_STATE_TYPE_IS_SCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_SCPUSTATE
#endif /* __EXCEPT_REGISTER_STATE_TYPE_IS_SCPUSTATE */
#ifdef __EXCEPT_REGISTER_STATE_TYPE_IS_FCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_FCPUSTATE
#endif /* __EXCEPT_REGISTER_STATE_TYPE_IS_FCPUSTATE */



/* Determine transitive identities */
#ifdef EXCEPT_REGISTER_STATE_TYPE_IS_UCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_UCPUSTATE
#endif /* EXCEPT_REGISTER_STATE_TYPE_IS_UCPUSTATE */

#ifdef EXCEPT_REGISTER_STATE_TYPE_IS_LCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_LCPUSTATE
#ifdef LCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_UCPUSTATE
#endif /* LCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#endif /* EXCEPT_REGISTER_STATE_TYPE_IS_LCPUSTATE */

#ifdef EXCEPT_REGISTER_STATE_TYPE_IS_KCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_KCPUSTATE
#ifdef KCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_LCPUSTATE
#endif /* KCPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#ifdef KCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_UCPUSTATE
#endif /* KCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#endif /* EXCEPT_REGISTER_STATE_TYPE_IS_KCPUSTATE */

#ifdef EXCEPT_REGISTER_STATE_TYPE_IS_ICPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_ICPUSTATE
#ifdef ICPUSTATE_IS_TRANSITIVE_KCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_KCPUSTATE
#endif /* ICPUSTATE_IS_TRANSITIVE_KCPUSTATE */
#ifdef ICPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_LCPUSTATE
#endif /* ICPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#ifdef ICPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_UCPUSTATE
#endif /* ICPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#endif /* EXCEPT_REGISTER_STATE_TYPE_IS_ICPUSTATE */

#ifdef EXCEPT_REGISTER_STATE_TYPE_IS_SCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_SCPUSTATE
#ifdef SCPUSTATE_IS_TRANSITIVE_ICPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_ICPUSTATE
#endif /* SCPUSTATE_IS_TRANSITIVE_ICPUSTATE */
#ifdef SCPUSTATE_IS_TRANSITIVE_KCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_KCPUSTATE
#endif /* SCPUSTATE_IS_TRANSITIVE_KCPUSTATE */
#ifdef SCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_LCPUSTATE
#endif /* SCPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#ifdef SCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_UCPUSTATE
#endif /* SCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#endif /* EXCEPT_REGISTER_STATE_TYPE_IS_SCPUSTATE */

#ifdef EXCEPT_REGISTER_STATE_TYPE_IS_FCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_FCPUSTATE
#ifdef FCPUSTATE_IS_TRANSITIVE_SCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_SCPUSTATE
#endif /* FCPUSTATE_IS_TRANSITIVE_SCPUSTATE */
#ifdef FCPUSTATE_IS_TRANSITIVE_ICPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_ICPUSTATE
#endif /* FCPUSTATE_IS_TRANSITIVE_ICPUSTATE */
#ifdef FCPUSTATE_IS_TRANSITIVE_KCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_KCPUSTATE
#endif /* FCPUSTATE_IS_TRANSITIVE_KCPUSTATE */
#ifdef FCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_LCPUSTATE
#endif /* FCPUSTATE_IS_TRANSITIVE_LCPUSTATE */
#ifdef FCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#define EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_UCPUSTATE
#endif /* FCPUSTATE_IS_TRANSITIVE_UCPUSTATE */
#endif /* EXCEPT_REGISTER_STATE_TYPE_IS_FCPUSTATE */



#ifdef EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_UCPUSTATE
#define __PRIVATE_except_register_state_(name)  ucpustate_##name
#define __PRIVATE__except_register_state(name) name##_ucpustate
#elif defined(EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_LCPUSTATE)
#define __PRIVATE_except_register_state_(name)  lcpustate_##name
#define __PRIVATE__except_register_state(name) name##_lcpustate
#elif defined(EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_KCPUSTATE)
#define __PRIVATE_except_register_state_(name)  kcpustate_##name
#define __PRIVATE__except_register_state(name) name##_kcpustate
#elif defined(EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_ICPUSTATE)
#define __PRIVATE_except_register_state_(name)  icpustate_##name
#define __PRIVATE__except_register_state(name) name##_icpustate
#elif defined(EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_SCPUSTATE)
#define __PRIVATE_except_register_state_(name)  scpustate_##name
#define __PRIVATE__except_register_state(name) name##_scpustate
#elif defined(EXCEPT_REGISTER_STATE_TYPE_IS_TRANSITIVE_FCPUSTATE)
#define __PRIVATE_except_register_state_(name)  fcpustate_##name
#define __PRIVATE__except_register_state(name) name##_fcpustate
#endif /* !... */

#ifndef __DEEMON__
#ifndef __except_register_state_get_unwind_exception
#error "Arch did not `#define __except_register_state_get_unwind_exception'"
#endif /* !__except_register_state_get_unwind_exception */
#ifndef __except_register_state_set_unwind_exception
#error "Arch did not `#define __except_register_state_set_unwind_exception'"
#endif /* !__except_register_state_set_unwind_exception */
#endif /* !__DEEMON__ */
#define except_register_state_get_unwind_exception __except_register_state_get_unwind_exception
#define except_register_state_set_unwind_exception __except_register_state_set_unwind_exception
#ifdef __except_register_state_get_unwind_switch
#define except_register_state_get_unwind_switch __except_register_state_get_unwind_switch
#define except_register_state_set_unwind_switch __except_register_state_set_unwind_switch
#endif /* __except_register_state_get_unwind_switch */

/* Define helper macros */
/*[[[deemon
for (local name: {
	"getpc",
	"setpc",
	"getsp",
	"setsp",
	"to_ucpustate",
	"to_lcpustate",
	"to_kcpustate",
	"to_icpustate",
	"to_scpustate",
	"to_fcpustate",
	"cpu_apply",
}) {
	print("#ifdef __except_register_state_", name);
	print("#define except_register_state_", name, " __except_register_state_", name);
	print("#elif defined(__PRIVATE_except_register_state_)");
	print("#define except_register_state_", name, " __PRIVATE_except_register_state_(", name, ")");
	print("#elif !defined(__DEEMON__)");
	print("#error \"No way to `#define except_register_state_", name, "'\"");
	print("#endif /" "* !... *" "/");
}
]]]*/
#ifdef __except_register_state_getpc
#define except_register_state_getpc __except_register_state_getpc
#elif defined(__PRIVATE_except_register_state_)
#define except_register_state_getpc __PRIVATE_except_register_state_(getpc)
#elif !defined(__DEEMON__)
#error "No way to `#define except_register_state_getpc'"
#endif /* !... */
#ifdef __except_register_state_setpc
#define except_register_state_setpc __except_register_state_setpc
#elif defined(__PRIVATE_except_register_state_)
#define except_register_state_setpc __PRIVATE_except_register_state_(setpc)
#elif !defined(__DEEMON__)
#error "No way to `#define except_register_state_setpc'"
#endif /* !... */
#ifdef __except_register_state_getsp
#define except_register_state_getsp __except_register_state_getsp
#elif defined(__PRIVATE_except_register_state_)
#define except_register_state_getsp __PRIVATE_except_register_state_(getsp)
#elif !defined(__DEEMON__)
#error "No way to `#define except_register_state_getsp'"
#endif /* !... */
#ifdef __except_register_state_setsp
#define except_register_state_setsp __except_register_state_setsp
#elif defined(__PRIVATE_except_register_state_)
#define except_register_state_setsp __PRIVATE_except_register_state_(setsp)
#elif !defined(__DEEMON__)
#error "No way to `#define except_register_state_setsp'"
#endif /* !... */
#ifdef __except_register_state_to_ucpustate
#define except_register_state_to_ucpustate __except_register_state_to_ucpustate
#elif defined(__PRIVATE_except_register_state_)
#define except_register_state_to_ucpustate __PRIVATE_except_register_state_(to_ucpustate)
#elif !defined(__DEEMON__)
#error "No way to `#define except_register_state_to_ucpustate'"
#endif /* !... */
#ifdef __except_register_state_to_lcpustate
#define except_register_state_to_lcpustate __except_register_state_to_lcpustate
#elif defined(__PRIVATE_except_register_state_)
#define except_register_state_to_lcpustate __PRIVATE_except_register_state_(to_lcpustate)
#elif !defined(__DEEMON__)
#error "No way to `#define except_register_state_to_lcpustate'"
#endif /* !... */
#ifdef __except_register_state_to_kcpustate
#define except_register_state_to_kcpustate __except_register_state_to_kcpustate
#elif defined(__PRIVATE_except_register_state_)
#define except_register_state_to_kcpustate __PRIVATE_except_register_state_(to_kcpustate)
#elif !defined(__DEEMON__)
#error "No way to `#define except_register_state_to_kcpustate'"
#endif /* !... */
#ifdef __except_register_state_to_icpustate
#define except_register_state_to_icpustate __except_register_state_to_icpustate
#elif defined(__PRIVATE_except_register_state_)
#define except_register_state_to_icpustate __PRIVATE_except_register_state_(to_icpustate)
#elif !defined(__DEEMON__)
#error "No way to `#define except_register_state_to_icpustate'"
#endif /* !... */
#ifdef __except_register_state_to_scpustate
#define except_register_state_to_scpustate __except_register_state_to_scpustate
#elif defined(__PRIVATE_except_register_state_)
#define except_register_state_to_scpustate __PRIVATE_except_register_state_(to_scpustate)
#elif !defined(__DEEMON__)
#error "No way to `#define except_register_state_to_scpustate'"
#endif /* !... */
#ifdef __except_register_state_to_fcpustate
#define except_register_state_to_fcpustate __except_register_state_to_fcpustate
#elif defined(__PRIVATE_except_register_state_)
#define except_register_state_to_fcpustate __PRIVATE_except_register_state_(to_fcpustate)
#elif !defined(__DEEMON__)
#error "No way to `#define except_register_state_to_fcpustate'"
#endif /* !... */
#ifdef __except_register_state_cpu_apply
#define except_register_state_cpu_apply __except_register_state_cpu_apply
#elif defined(__PRIVATE_except_register_state_)
#define except_register_state_cpu_apply __PRIVATE_except_register_state_(cpu_apply)
#elif !defined(__DEEMON__)
#error "No way to `#define except_register_state_cpu_apply'"
#endif /* !... */
/*[[[end]]]*/

#ifdef __except_register_state_from_ucpustate
#define except_register_state_from_ucpustate __except_register_state_from_ucpustate
#elif defined(__PRIVATE__except_register_state)
#define except_register_state_from_ucpustate(self, src) __PRIVATE__except_register_state(ucpustate_to)(src, self)
#elif !defined(__DEEMON__)
#error "No way to `#define except_register_state_from_ucpustate'"
#endif /* !... */

#ifdef __except_register_state_from_lcpustate
#define except_register_state_from_lcpustate __except_register_state_from_lcpustate
#elif defined(__PRIVATE__except_register_state)
#define except_register_state_from_lcpustate(self, src) __PRIVATE__except_register_state(lcpustate_to)(src, self)
#elif !defined(__DEEMON__)
#error "No way to `#define except_register_state_from_lcpustate'"
#endif /* !... */

#ifdef __except_register_state_from_kcpustate
#define except_register_state_from_kcpustate __except_register_state_from_kcpustate
#elif defined(__PRIVATE__except_register_state)
#define except_register_state_from_kcpustate(self, src) __PRIVATE__except_register_state(kcpustate_to)(src, self)
#elif !defined(__DEEMON__)
#error "No way to `#define except_register_state_from_kcpustate'"
#endif /* !... */

#ifdef __except_register_state_from_icpustate
#define except_register_state_from_icpustate __except_register_state_from_icpustate
#elif defined(__PRIVATE__except_register_state)
#define except_register_state_from_icpustate(self, src) __PRIVATE__except_register_state(icpustate_to)(src, self)
#elif !defined(__DEEMON__)
#error "No way to `#define except_register_state_from_icpustate'"
#endif /* !... */

#ifdef __except_register_state_from_scpustate
#define except_register_state_from_scpustate __except_register_state_from_scpustate
#elif defined(__PRIVATE__except_register_state)
#define except_register_state_from_scpustate(self, src) __PRIVATE__except_register_state(scpustate_to)(src, self)
#elif !defined(__DEEMON__)
#error "No way to `#define except_register_state_from_scpustate'"
#endif /* !... */

#ifdef __except_register_state_from_fcpustate
#define except_register_state_from_fcpustate __except_register_state_from_fcpustate
#elif defined(__PRIVATE__except_register_state)
#define except_register_state_from_fcpustate(self, src) __PRIVATE__except_register_state(fcpustate_to)(src, self)
#elif !defined(__DEEMON__)
#error "No way to `#define except_register_state_from_fcpustate'"
#endif /* !... */

/* For this one, you may also need to `#include <libcpustate/apply.h>' */
#ifdef __except_register_state_cpu_apply
#define except_register_state_cpu_apply __except_register_state_cpu_apply
#elif defined(__PRIVATE__except_register_state)
#define except_register_state_cpu_apply __PRIVATE__except_register_state(cpu_apply)
#elif !defined(__DEEMON__)
#error "No way to `#define except_register_state_cpu_apply'"
#endif /* !... */


#endif /* !_KOS_BITS_EXCEPT_REGISTER_STATE_HELPERS_H */
