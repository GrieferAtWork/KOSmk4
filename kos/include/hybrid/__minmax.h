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
#ifndef __GUARD_HYBRID___MINMAX_H
#define __GUARD_HYBRID___MINMAX_H 1

#include "../__stdinc.h"
#include "pp/__va_nargs.h"

#define __hybrid_min_c2(a, b) ((a) < (b) ? (a) : (b))
#define __hybrid_max_c2(a, b) ((b) < (a) ? (a) : (b))

#if (defined(__DCC_VERSION__) || \
     (__has_builtin(__builtin_min) && __has_builtin(__builtin_max)))
#define __hybrid_min_r2(a, b) __builtin_min(a, b)
#define __hybrid_max_r2(a, b) __builtin_max(a, b)
#define __hybrid_min2(a, b)   __builtin_min(a, b)
#define __hybrid_max2(a, b)   __builtin_max(a, b)
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __hybrid_min_c(...) __builtin_min(__VA_ARGS__)
#define __hybrid_max_c(...) __builtin_max(__VA_ARGS__)
#define __hybrid_min(...)   __builtin_min(__VA_ARGS__)
#define __hybrid_max(...)   __builtin_max(__VA_ARGS__)
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define __hybrid_min_c __builtin_min
#define __hybrid_max_c __builtin_max
#define __hybrid_min   __builtin_min
#define __hybrid_max   __builtin_max
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */
#elif defined(__COMPILER_HAVE_AUTOTYPE) && !defined(__NO_XBLOCK)
#define __hybrid_min_r2(a, b) __XBLOCK({ __auto_type _a = (a); __auto_type _b = (b); __XRETURN _a < _b ? _a : _b; })
#define __hybrid_max_r2(a, b) __XBLOCK({ __auto_type _a = (a); __auto_type _b = (b); __XRETURN _b < _a ? _a : _b; })
#define __hybrid_min2(a, b)   __XBLOCK({ __auto_type _a = (a); __auto_type _b = (b); __XRETURN _a < _b ? _a : _b; })
#define __hybrid_max2(a, b)   __XBLOCK({ __auto_type _a = (a); __auto_type _b = (b); __XRETURN _b < _a ? _a : _b; })
#elif defined(__COMPILER_HAVE_TYPEOF) && !defined(__NO_XBLOCK)
#define __hybrid_min_r2(a, b) __XBLOCK({ __typeof__(a) _a = (a); __typeof__(b) _b = (b); __XRETURN _a < _b ? _a : _b; })
#define __hybrid_max_r2(a, b) __XBLOCK({ __typeof__(a) _a = (a); __typeof__(b) _b = (b); __XRETURN _b < _a ? _a : _b; })
#define __hybrid_min2(a, b)   __XBLOCK({ __typeof__(a) _a = (a); __typeof__(b) _b = (b); __XRETURN _a < _b ? _a : _b; })
#define __hybrid_max2(a, b)   __XBLOCK({ __typeof__(a) _a = (a); __typeof__(b) _b = (b); __XRETURN _b < _a ? _a : _b; })
#endif /* ... */

#ifndef __hybrid_min2
#ifndef __hybrid_min_r2
#define __hybrid_min2(a, b) __hybrid_min_c2(a, b)
#define __hybrid_max2(a, b) __hybrid_max_c2(a, b)
#elif !defined(__NO_builtin_constant_p)
#ifndef __NO_builtin_choose_expr
#define __hybrid_min2(a, b)                                                   \
	__builtin_choose_expr(__builtin_constant_p(a) && __builtin_constant_p(b), \
	                      __hybrid_min_c2(a, b), __hybrid_min_r2(a, b))
#define __hybrid_max2(a, b)                                                   \
	__builtin_choose_expr(__builtin_constant_p(a) && __builtin_constant_p(b), \
	                      __hybrid_max_c2(a, b), __hybrid_max_r2(a, b))
#else /* !__NO_builtin_choose_expr */
#define __hybrid_min2(a, b)                               \
	((__builtin_constant_p(a) && __builtin_constant_p(b)) \
	 ? __hybrid_min_c2(a, b)                              \
	 : __hybrid_min_r2(a, b))
#define __hybrid_max2(a, b)                               \
	((__builtin_constant_p(a) && __builtin_constant_p(b)) \
	 ? __hybrid_max_c2(a, b)                              \
	 : __hybrid_max_r2(a, b))
#endif /* __NO_builtin_choose_expr */
#else  /* ... */
#define __hybrid_min2(a, b) __hybrid_min_r2(a, b)
#define __hybrid_max2(a, b) __hybrid_max_r2(a, b)
#endif /* !... */
#endif /* !__hybrid_min */

/*[[[deemon
import * from deemon;
function ai(i: int): string {
	return string.chr("a".ord() + i);
}
for (local name: ["__hybrid_min", "__hybrid_max", "__hybrid_min_c", "__hybrid_max_c"]) {
	for (local n: [1:20+1]) {
		if (n == 2)
			continue;
		print("#define ", name, n, "("),;
		local args = [];
		for (local i: [:n]) {
			if (i)
				print(", "),;
			local a = ai(i);
			print(a),;
			args.append(a);
		}
		print(") "),;
		if (n == 1)
			print("a");
		else {
#define IS_POWER_OF_TWO(x)    (((x) & ((x)-1)) == 0)
			local secondHalf = (n * 2) / 3;
			while (!IS_POWER_OF_TWO(secondHalf))
				--secondHalf;

			local firstHalf = n - secondHalf;
			print(name, "2("),;
			if (firstHalf == 1) {
				print(args.first),;
			} else {
				print(name, firstHalf, "(", ", ".join(args[:firstHalf]), ")"),;
			}
			print(", "),;
			if (secondHalf == 1) {
				print(args.last),;
			} else {
				print(name, secondHalf, "(", ", ".join(args[firstHalf:]), ")"),;
			}
			print(")");
		}
	}
}
]]]*/
#define __hybrid_min1(a) a
#define __hybrid_min3(a, b, c) __hybrid_min2(a, __hybrid_min2(b, c))
#define __hybrid_min4(a, b, c, d) __hybrid_min2(__hybrid_min2(a, b), __hybrid_min2(c, d))
#define __hybrid_min5(a, b, c, d, e) __hybrid_min2(__hybrid_min3(a, b, c), __hybrid_min2(d, e))
#define __hybrid_min6(a, b, c, d, e, f) __hybrid_min2(__hybrid_min2(a, b), __hybrid_min4(c, d, e, f))
#define __hybrid_min7(a, b, c, d, e, f, g) __hybrid_min2(__hybrid_min3(a, b, c), __hybrid_min4(d, e, f, g))
#define __hybrid_min8(a, b, c, d, e, f, g, h) __hybrid_min2(__hybrid_min4(a, b, c, d), __hybrid_min4(e, f, g, h))
#define __hybrid_min9(a, b, c, d, e, f, g, h, i) __hybrid_min2(__hybrid_min5(a, b, c, d, e), __hybrid_min4(f, g, h, i))
#define __hybrid_min10(a, b, c, d, e, f, g, h, i, j) __hybrid_min2(__hybrid_min6(a, b, c, d, e, f), __hybrid_min4(g, h, i, j))
#define __hybrid_min11(a, b, c, d, e, f, g, h, i, j, k) __hybrid_min2(__hybrid_min7(a, b, c, d, e, f, g), __hybrid_min4(h, i, j, k))
#define __hybrid_min12(a, b, c, d, e, f, g, h, i, j, k, l) __hybrid_min2(__hybrid_min4(a, b, c, d), __hybrid_min8(e, f, g, h, i, j, k, l))
#define __hybrid_min13(a, b, c, d, e, f, g, h, i, j, k, l, m) __hybrid_min2(__hybrid_min5(a, b, c, d, e), __hybrid_min8(f, g, h, i, j, k, l, m))
#define __hybrid_min14(a, b, c, d, e, f, g, h, i, j, k, l, m, n) __hybrid_min2(__hybrid_min6(a, b, c, d, e, f), __hybrid_min8(g, h, i, j, k, l, m, n))
#define __hybrid_min15(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o) __hybrid_min2(__hybrid_min7(a, b, c, d, e, f, g), __hybrid_min8(h, i, j, k, l, m, n, o))
#define __hybrid_min16(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) __hybrid_min2(__hybrid_min8(a, b, c, d, e, f, g, h), __hybrid_min8(i, j, k, l, m, n, o, p))
#define __hybrid_min17(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q) __hybrid_min2(__hybrid_min9(a, b, c, d, e, f, g, h, i), __hybrid_min8(j, k, l, m, n, o, p, q))
#define __hybrid_min18(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r) __hybrid_min2(__hybrid_min10(a, b, c, d, e, f, g, h, i, j), __hybrid_min8(k, l, m, n, o, p, q, r))
#define __hybrid_min19(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s) __hybrid_min2(__hybrid_min11(a, b, c, d, e, f, g, h, i, j, k), __hybrid_min8(l, m, n, o, p, q, r, s))
#define __hybrid_min20(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t) __hybrid_min2(__hybrid_min12(a, b, c, d, e, f, g, h, i, j, k, l), __hybrid_min8(m, n, o, p, q, r, s, t))
#define __hybrid_max1(a) a
#define __hybrid_max3(a, b, c) __hybrid_max2(a, __hybrid_max2(b, c))
#define __hybrid_max4(a, b, c, d) __hybrid_max2(__hybrid_max2(a, b), __hybrid_max2(c, d))
#define __hybrid_max5(a, b, c, d, e) __hybrid_max2(__hybrid_max3(a, b, c), __hybrid_max2(d, e))
#define __hybrid_max6(a, b, c, d, e, f) __hybrid_max2(__hybrid_max2(a, b), __hybrid_max4(c, d, e, f))
#define __hybrid_max7(a, b, c, d, e, f, g) __hybrid_max2(__hybrid_max3(a, b, c), __hybrid_max4(d, e, f, g))
#define __hybrid_max8(a, b, c, d, e, f, g, h) __hybrid_max2(__hybrid_max4(a, b, c, d), __hybrid_max4(e, f, g, h))
#define __hybrid_max9(a, b, c, d, e, f, g, h, i) __hybrid_max2(__hybrid_max5(a, b, c, d, e), __hybrid_max4(f, g, h, i))
#define __hybrid_max10(a, b, c, d, e, f, g, h, i, j) __hybrid_max2(__hybrid_max6(a, b, c, d, e, f), __hybrid_max4(g, h, i, j))
#define __hybrid_max11(a, b, c, d, e, f, g, h, i, j, k) __hybrid_max2(__hybrid_max7(a, b, c, d, e, f, g), __hybrid_max4(h, i, j, k))
#define __hybrid_max12(a, b, c, d, e, f, g, h, i, j, k, l) __hybrid_max2(__hybrid_max4(a, b, c, d), __hybrid_max8(e, f, g, h, i, j, k, l))
#define __hybrid_max13(a, b, c, d, e, f, g, h, i, j, k, l, m) __hybrid_max2(__hybrid_max5(a, b, c, d, e), __hybrid_max8(f, g, h, i, j, k, l, m))
#define __hybrid_max14(a, b, c, d, e, f, g, h, i, j, k, l, m, n) __hybrid_max2(__hybrid_max6(a, b, c, d, e, f), __hybrid_max8(g, h, i, j, k, l, m, n))
#define __hybrid_max15(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o) __hybrid_max2(__hybrid_max7(a, b, c, d, e, f, g), __hybrid_max8(h, i, j, k, l, m, n, o))
#define __hybrid_max16(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) __hybrid_max2(__hybrid_max8(a, b, c, d, e, f, g, h), __hybrid_max8(i, j, k, l, m, n, o, p))
#define __hybrid_max17(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q) __hybrid_max2(__hybrid_max9(a, b, c, d, e, f, g, h, i), __hybrid_max8(j, k, l, m, n, o, p, q))
#define __hybrid_max18(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r) __hybrid_max2(__hybrid_max10(a, b, c, d, e, f, g, h, i, j), __hybrid_max8(k, l, m, n, o, p, q, r))
#define __hybrid_max19(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s) __hybrid_max2(__hybrid_max11(a, b, c, d, e, f, g, h, i, j, k), __hybrid_max8(l, m, n, o, p, q, r, s))
#define __hybrid_max20(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t) __hybrid_max2(__hybrid_max12(a, b, c, d, e, f, g, h, i, j, k, l), __hybrid_max8(m, n, o, p, q, r, s, t))
#define __hybrid_min_c1(a) a
#define __hybrid_min_c3(a, b, c) __hybrid_min_c2(a, __hybrid_min_c2(b, c))
#define __hybrid_min_c4(a, b, c, d) __hybrid_min_c2(__hybrid_min_c2(a, b), __hybrid_min_c2(c, d))
#define __hybrid_min_c5(a, b, c, d, e) __hybrid_min_c2(__hybrid_min_c3(a, b, c), __hybrid_min_c2(d, e))
#define __hybrid_min_c6(a, b, c, d, e, f) __hybrid_min_c2(__hybrid_min_c2(a, b), __hybrid_min_c4(c, d, e, f))
#define __hybrid_min_c7(a, b, c, d, e, f, g) __hybrid_min_c2(__hybrid_min_c3(a, b, c), __hybrid_min_c4(d, e, f, g))
#define __hybrid_min_c8(a, b, c, d, e, f, g, h) __hybrid_min_c2(__hybrid_min_c4(a, b, c, d), __hybrid_min_c4(e, f, g, h))
#define __hybrid_min_c9(a, b, c, d, e, f, g, h, i) __hybrid_min_c2(__hybrid_min_c5(a, b, c, d, e), __hybrid_min_c4(f, g, h, i))
#define __hybrid_min_c10(a, b, c, d, e, f, g, h, i, j) __hybrid_min_c2(__hybrid_min_c6(a, b, c, d, e, f), __hybrid_min_c4(g, h, i, j))
#define __hybrid_min_c11(a, b, c, d, e, f, g, h, i, j, k) __hybrid_min_c2(__hybrid_min_c7(a, b, c, d, e, f, g), __hybrid_min_c4(h, i, j, k))
#define __hybrid_min_c12(a, b, c, d, e, f, g, h, i, j, k, l) __hybrid_min_c2(__hybrid_min_c4(a, b, c, d), __hybrid_min_c8(e, f, g, h, i, j, k, l))
#define __hybrid_min_c13(a, b, c, d, e, f, g, h, i, j, k, l, m) __hybrid_min_c2(__hybrid_min_c5(a, b, c, d, e), __hybrid_min_c8(f, g, h, i, j, k, l, m))
#define __hybrid_min_c14(a, b, c, d, e, f, g, h, i, j, k, l, m, n) __hybrid_min_c2(__hybrid_min_c6(a, b, c, d, e, f), __hybrid_min_c8(g, h, i, j, k, l, m, n))
#define __hybrid_min_c15(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o) __hybrid_min_c2(__hybrid_min_c7(a, b, c, d, e, f, g), __hybrid_min_c8(h, i, j, k, l, m, n, o))
#define __hybrid_min_c16(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) __hybrid_min_c2(__hybrid_min_c8(a, b, c, d, e, f, g, h), __hybrid_min_c8(i, j, k, l, m, n, o, p))
#define __hybrid_min_c17(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q) __hybrid_min_c2(__hybrid_min_c9(a, b, c, d, e, f, g, h, i), __hybrid_min_c8(j, k, l, m, n, o, p, q))
#define __hybrid_min_c18(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r) __hybrid_min_c2(__hybrid_min_c10(a, b, c, d, e, f, g, h, i, j), __hybrid_min_c8(k, l, m, n, o, p, q, r))
#define __hybrid_min_c19(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s) __hybrid_min_c2(__hybrid_min_c11(a, b, c, d, e, f, g, h, i, j, k), __hybrid_min_c8(l, m, n, o, p, q, r, s))
#define __hybrid_min_c20(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t) __hybrid_min_c2(__hybrid_min_c12(a, b, c, d, e, f, g, h, i, j, k, l), __hybrid_min_c8(m, n, o, p, q, r, s, t))
#define __hybrid_max_c1(a) a
#define __hybrid_max_c3(a, b, c) __hybrid_max_c2(a, __hybrid_max_c2(b, c))
#define __hybrid_max_c4(a, b, c, d) __hybrid_max_c2(__hybrid_max_c2(a, b), __hybrid_max_c2(c, d))
#define __hybrid_max_c5(a, b, c, d, e) __hybrid_max_c2(__hybrid_max_c3(a, b, c), __hybrid_max_c2(d, e))
#define __hybrid_max_c6(a, b, c, d, e, f) __hybrid_max_c2(__hybrid_max_c2(a, b), __hybrid_max_c4(c, d, e, f))
#define __hybrid_max_c7(a, b, c, d, e, f, g) __hybrid_max_c2(__hybrid_max_c3(a, b, c), __hybrid_max_c4(d, e, f, g))
#define __hybrid_max_c8(a, b, c, d, e, f, g, h) __hybrid_max_c2(__hybrid_max_c4(a, b, c, d), __hybrid_max_c4(e, f, g, h))
#define __hybrid_max_c9(a, b, c, d, e, f, g, h, i) __hybrid_max_c2(__hybrid_max_c5(a, b, c, d, e), __hybrid_max_c4(f, g, h, i))
#define __hybrid_max_c10(a, b, c, d, e, f, g, h, i, j) __hybrid_max_c2(__hybrid_max_c6(a, b, c, d, e, f), __hybrid_max_c4(g, h, i, j))
#define __hybrid_max_c11(a, b, c, d, e, f, g, h, i, j, k) __hybrid_max_c2(__hybrid_max_c7(a, b, c, d, e, f, g), __hybrid_max_c4(h, i, j, k))
#define __hybrid_max_c12(a, b, c, d, e, f, g, h, i, j, k, l) __hybrid_max_c2(__hybrid_max_c4(a, b, c, d), __hybrid_max_c8(e, f, g, h, i, j, k, l))
#define __hybrid_max_c13(a, b, c, d, e, f, g, h, i, j, k, l, m) __hybrid_max_c2(__hybrid_max_c5(a, b, c, d, e), __hybrid_max_c8(f, g, h, i, j, k, l, m))
#define __hybrid_max_c14(a, b, c, d, e, f, g, h, i, j, k, l, m, n) __hybrid_max_c2(__hybrid_max_c6(a, b, c, d, e, f), __hybrid_max_c8(g, h, i, j, k, l, m, n))
#define __hybrid_max_c15(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o) __hybrid_max_c2(__hybrid_max_c7(a, b, c, d, e, f, g), __hybrid_max_c8(h, i, j, k, l, m, n, o))
#define __hybrid_max_c16(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) __hybrid_max_c2(__hybrid_max_c8(a, b, c, d, e, f, g, h), __hybrid_max_c8(i, j, k, l, m, n, o, p))
#define __hybrid_max_c17(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q) __hybrid_max_c2(__hybrid_max_c9(a, b, c, d, e, f, g, h, i), __hybrid_max_c8(j, k, l, m, n, o, p, q))
#define __hybrid_max_c18(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r) __hybrid_max_c2(__hybrid_max_c10(a, b, c, d, e, f, g, h, i, j), __hybrid_max_c8(k, l, m, n, o, p, q, r))
#define __hybrid_max_c19(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s) __hybrid_max_c2(__hybrid_max_c11(a, b, c, d, e, f, g, h, i, j, k), __hybrid_max_c8(l, m, n, o, p, q, r, s))
#define __hybrid_max_c20(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t) __hybrid_max_c2(__hybrid_max_c12(a, b, c, d, e, f, g, h, i, j, k, l), __hybrid_max_c8(m, n, o, p, q, r, s, t))
/*[[[end]]]*/

#ifndef __hybrid_min
#ifdef __HYBRID_PP_VA_OVERLOAD
#define __hybrid_min_c(...) __HYBRID_PP_VA_OVERLOAD(__hybrid_min_c, (__VA_ARGS__))(__VA_ARGS__)
#define __hybrid_max_c(...) __HYBRID_PP_VA_OVERLOAD(__hybrid_max_c, (__VA_ARGS__))(__VA_ARGS__)
#define __hybrid_min(...)   __HYBRID_PP_VA_OVERLOAD(__hybrid_min, (__VA_ARGS__))(__VA_ARGS__)
#define __hybrid_max(...)   __HYBRID_PP_VA_OVERLOAD(__hybrid_max, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
#define __hybrid_min_c __hybrid_min_c2
#define __hybrid_max_c __hybrid_max_c2
#define __hybrid_min   __hybrid_min2
#define __hybrid_max   __hybrid_max2
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#endif /* !__hybrid_min */

#endif /* !__GUARD_HYBRID___MINMAX_H */
