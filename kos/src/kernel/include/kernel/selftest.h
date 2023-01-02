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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_SELFTEST_H
#define GUARD_KERNEL_INCLUDE_KERNEL_SELFTEST_H 1

#include <kernel/compiler.h>


/*[[[config CONFIG_HAVE_KERNEL_SELFTEST: bool = !defined(NDEBUG)
 * _always_ disable self-tests when NDEBUG is defined!
 * ]]]*/
#ifdef CONFIG_NO_KERNEL_SELFTEST
#undef CONFIG_HAVE_KERNEL_SELFTEST
#elif !defined(CONFIG_HAVE_KERNEL_SELFTEST)
#ifndef NDEBUG
#define CONFIG_HAVE_KERNEL_SELFTEST
#else /* !NDEBUG */
#define CONFIG_NO_KERNEL_SELFTEST
#endif /* NDEBUG */
#elif (-CONFIG_HAVE_KERNEL_SELFTEST - 1) == -1
#undef CONFIG_HAVE_KERNEL_SELFTEST
#define CONFIG_NO_KERNEL_SELFTEST
#endif /* ... */
/*[[[end]]]*/

#undef DEFINE_TEST
#ifdef BUILDING_KERNEL_CORE
/* >> void KCALL func(void);
 * A self-test that gets invoked during late bootup */
#ifdef CONFIG_HAVE_KERNEL_SELFTEST
#define DEFINE_SELFTEST_FUNCTION(func) \
	DEFINE_CALLBACK(".rodata.free.callback.selftest", func)
#define DEFINE_TEST(name)                  \
	DEFINE_SELFTEST_FUNCTION(test_##name); \
	PRIVATE ATTR_USED ATTR_FREETEXT void   \
	NOTHROW(KCALL test_##name)(void)
#else /* CONFIG_HAVE_KERNEL_SELFTEST */
#define DEFINE_SELFTEST_FUNCTION(func) /* nothing */
#endif /* !CONFIG_HAVE_KERNEL_SELFTEST */
#endif /* BUILDING_KERNEL_CORE */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_SELFTEST_H */
