/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID___ALTINT_H
#define __GUARD_HYBRID___ALTINT_H 1

/* Alternative integer type
 * For use with Intellisense to aid in highlighting unwanted use of types */
#include "../__stdinc.h"

#if defined(__INTELLISENSE__) && defined(__CC__) && defined(__cplusplus)
#include "typecore.h"

#define __HYBRID_ALTINT_UID(UID)     \
	__NAMESPACE_INT_BEGIN            \
	struct __hybrid_altint_##UID {}; \
	__NAMESPACE_INT_END
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __HYBRID_ALTINT(UID, allow_int_ops, ...) \
	__NAMESPACE_INT_SYM ____intellisense_altint< __NAMESPACE_INT_SYM __hybrid_altint_##UID, allow_int_ops, __VA_ARGS__ >
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define __HYBRID_ALTINT(UID, allow_int_ops, T) \
	__NAMESPACE_INT_SYM ____intellisense_altint< __NAMESPACE_INT_SYM UID, allow_int_ops, T >
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */

/* Allow the use  of Ta  and Tb  in integer  expressions (except  for shift  and compare  operations)
 * NOTE: For this purpose, `Ta' is only allowed on the left-hand-side and `Tb' only on the right one. */
#define __HYBRID_ALTINT_COMPAT(Ta, Tb)            \
	extern "C++" {                                \
	Ta operator+(Ta const &, Tb const &) throw(); \
	Ta operator-(Ta const &, Tb const &) throw(); \
	Ta operator*(Ta const &, Tb const &) throw(); \
	Ta operator/(Ta const &, Tb const &) throw(); \
	Ta operator%(Ta const &, Tb const &) throw(); \
	Ta operator|(Ta const &, Tb const &) throw(); \
	Ta operator&(Ta const &, Tb const &) throw(); \
	Ta operator^(Ta const &, Tb const &) throw(); \
	Ta &operator+=(Ta &, Tb const &) throw();     \
	Ta &operator-=(Ta &, Tb const &) throw();     \
	Ta &operator*=(Ta &, Tb const &) throw();     \
	Ta &operator/=(Ta &, Tb const &) throw();     \
	Ta &operator%=(Ta &, Tb const &) throw();     \
	Ta &operator|=(Ta &, Tb const &) throw();     \
	Ta &operator&=(Ta &, Tb const &) throw();     \
	Ta &operator^=(Ta &, Tb const &) throw();     \
	}
#define __HYBRID_ALTINT_TYPEDEF(Told, Tnew, allow_int_ops) \
	__HYBRID_ALTINT_UID(Tnew)                              \
	typedef __HYBRID_ALTINT(Tnew, allow_int_ops, Told) Tnew
#else /* __INTELLISENSE__ */
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __HYBRID_ALTINT(UID, allow_int_ops, ...) __VA_ARGS__
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define __HYBRID_ALTINT(UID, allow_int_ops, T) T
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */
#define __HYBRID_ALTINT_UID(UID)                           /* nothing */
#define __HYBRID_ALTINT_COMPAT(Ta, Tb)                     /* nothing */
#define __HYBRID_ALTINT_TYPEDEF(Told, Tnew, allow_int_ops) typedef Told Tnew
#endif /* !__INTELLISENSE__ */

#endif /* !__GUARD_HYBRID___ALTINT_H */
