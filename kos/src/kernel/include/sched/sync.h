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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SYNC_H
#define GUARD_KERNEL_INCLUDE_SCHED_SYNC_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>

DECL_BEGIN

#define SYNC_ACQUIRE2(trya, geta, enda, tryb, getb, endb) \
	do {                                                  \
		geta;                                             \
		if likely(tryb)                                   \
			break;                                        \
		enda;                                             \
		getb;                                             \
		if likely(trya)                                   \
			break;                                        \
		endb;                                             \
	} __WHILE1

#define __LINEID3(x, y) x##y
#define __LINEID2(x, y) __LINEID3(x, y)
#define __LINEID(x) __LINEID2(x, __LINE__)

#define SYNC_ACQUIRE3(trya, geta, enda, tryb, getb, endb, tryc, getc, endc) \
	do {                                                                    \
		geta;                                                               \
		if likely(tryb) {                                                   \
			if likely(tryc)                                                 \
				break;                                                      \
__LINEID(continue_c):                                                       \
			endb;                                                           \
			enda;                                                           \
			getc;                                                           \
			if likely(trya) {                                               \
				if likely(tryb)                                             \
					break;                                                  \
				enda;                                                       \
				endc;                                                       \
				goto __LINEID(continue_b);                                  \
			}                                                               \
			endc;                                                           \
			continue;                                                       \
		}                                                                   \
		enda;                                                               \
__LINEID(continue_b):                                                       \
		getb;                                                               \
		if likely(trya) {                                                   \
			if likely(tryc)                                                 \
				break;                                                      \
			goto __LINEID(continue_c);                                      \
		}                                                                   \
		endb;                                                               \
	} __WHILE1



#ifdef __cplusplus
extern "C++" {

#define __DEFINE_SYNCALL(name)                                                                                     \
	template<class T1, class T2>                                                                                   \
	NONNULL((1, 2))                                                                                                \
	void(KCALL sync_##name##all)(T1 *__restrict a, T2 *__restrict b) THROWS(E_WOULDBLOCK, ...) {                   \
		SYNC_ACQUIRE2(sync_methods<T1>::try##name(a), sync_methods<T1>::name(a), sync_methods<T1>::end##name(a),   \
		              sync_methods<T2>::try##name(b), sync_methods<T2>::name(b), sync_methods<T2>::end##name(b));  \
	}                                                                                                              \
	template<class T1, class T2, class T3>                                                                         \
	NONNULL((1, 2, 3))                                                                                             \
	void(KCALL sync_##name##all)(T1 *__restrict a, T2 *__restrict b, T3 *__restrict c) THROWS(E_WOULDBLOCK, ...) { \
		SYNC_ACQUIRE3(sync_methods<T1>::try##name(a), sync_methods<T1>::name(a), sync_methods<T1>::end##name(a),   \
		              sync_methods<T2>::try##name(b), sync_methods<T2>::name(b), sync_methods<T2>::end##name(b),   \
		              sync_methods<T3>::try##name(c), sync_methods<T3>::name(c), sync_methods<T3>::end##name(c));  \
	}
__DEFINE_SYNCALL(read)
__DEFINE_SYNCALL(write)
#undef __DEFINE_SYNCALL


}
#endif /* __cplusplus */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SYNC_H */
