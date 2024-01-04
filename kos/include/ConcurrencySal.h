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
/* (#) Portability: MSVC         (/include/ConcurrencySal.h) */
/* (#) Portability: Windows Kits (/shared/ConcurrencySal.h) */
#ifndef _CONCURRENCYSAL_H
#define _CONCURRENCYSAL_H 1

#define _Acquires_exclusive_lock_(lock)
#define _Acquires_lock_(lock)
#define _Acquires_nonreentrant_lock_(lock)
#define _Acquires_shared_lock_(lock)
#define _Analysis_assume_lock_acquired_(lock)
#define _Analysis_assume_lock_held_(lock)
#define _Analysis_assume_lock_not_held_(lock)
#define _Analysis_assume_lock_released_(lock)
#define _Analysis_assume_same_lock_(lock1, lock2)
#define _Analysis_suppress_lock_checking_(lock)
#define _Create_lock_level_(level)
#define _Csalcat1_(x, y)
#define _Csalcat2_(x, y)
#define _Function_ignore_lock_checking_(lock)
#define _Guarded_by_(lock)
#define _Has_lock_kind_(kind)
#define _Has_lock_level_(level)
#define _Interlocked_
#define _Internal_lock_level_order_(a, b)
#define _Internal_set_lock_count_(lock, count)
#define _Lock_level_order_(a, b)
#define _No_competing_thread_
#define _Post_same_lock_(lock1, lock2)
#define _Releases_exclusive_lock_(lock)
#define _Releases_lock_(lock)
#define _Releases_nonreentrant_lock_(lock)
#define _Releases_shared_lock_(lock)
#define _Requires_exclusive_lock_held_(lock)
#define _Requires_lock_held_(lock)
#define _Requires_lock_not_held_(lock)
#define _Requires_no_locks_held_
#define _Requires_shared_lock_held_(lock)
#define _Write_guarded_by_(lock)
#define __acquires_exclusive_lock(lock)
#define __acquires_lock(lock)
#define __acquires_shared_lock(lock)
#define __analysis_assume_lock_acquired(lock)
#define __analysis_assume_lock_released(lock)
#define __analysis_suppress_lock_checking(lock)
#define __declare_lock_level(level)
#define __function_ignore_lock_checking(lock)
#ifndef __guarded_by /* Defined differently in <sys/cdefs.h> */
#define __guarded_by(lock)
#endif /* !__guarded_by */
#define __has_lock_level(level)
#define __has_lock_property(kind)
#define __interlocked
#define __internal_lock_level_order(a, b)
#define __lock_level_order(a, b)
#define __no_competing_thread
#define __releases_exclusive_lock(lock)
#define __releases_lock(lock)
#define __releases_shared_lock(lock)
#define __requires_exclusive_lock_held(lock)
#define __requires_lock_held(lock)
#define __requires_lock_not_held(lock)
#define __requires_no_locks_held
#define __requires_shared_lock_held(lock)
#define __write_guarded_by(lock)

#ifndef _Interlocked_operand_
#define _Interlocked_operand_
#endif /* !_Interlocked_operand_ */

//#define CSALCAT1(x,y)
//#define CSALCAT2(x,y)

#ifdef _MSC_VER
#define BENIGN_RACE_BEGIN __pragma(warning(push))
#define BENIGN_RACE_END __pragma(warning(pop))
#define NO_COMPETING_THREAD_BEGIN __pragma(warning(push))
#define NO_COMPETING_THREAD_END __pragma(warning(pop))
#define _Benign_race_begin_ __pragma(warning(push))
#define _Benign_race_end_ __pragma(warning(pop))
#define _No_competing_thread_begin_ __pragma(warning(push))
#define _No_competing_thread_end_ __pragma(warning(pop))
#else /* _MSC_VER */
#define BENIGN_RACE_BEGIN
#define BENIGN_RACE_END
#define NO_COMPETING_THREAD_BEGIN
#define NO_COMPETING_THREAD_END
#define _Benign_race_begin_
#define _Benign_race_end_
#define _No_competing_thread_begin_
#define _No_competing_thread_end_
#endif /* !_MSC_VER */

#endif /* !_CONCURRENCYSAL_H */
