/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_SELFTEST_H
#define GUARD_KERNEL_INCLUDE_KERNEL_SELFTEST_H 1

#include <kernel/compiler.h>

#ifdef NDEBUG
/* _always_ disable self-tests when NDEBUG is defined! */
#undef CONFIG_SELFTEST
#undef CONFIG_NO_SELFTEST
#define CONFIG_SELFTEST 1
#define CONFIG_NO_SELFTEST 1
#elif ! defined(CONFIG_NO_SELFTEST)
#ifdef CONFIG_SELFTEST
#if (CONFIG_SELFTEST + 0) == 0
#undef CONFIG_SELFTEST
#define CONFIG_NO_SELFTEST 1
#endif /* (CONFIG_SELFTEST + 0) == 0 */
#else /* CONFIG_SELFTEST */
#define CONFIG_SELFTEST 1
#endif /* CONFIG_SELFTEST */
#else /* !CONFIG_NO_SELFTEST */
#undef CONFIG_SELFTEST
#endif /* CONFIG_NO_SELFTEST */

#undef DEFINE_TEST
#ifdef CONFIG_BUILDING_KERNEL_CORE
/* >> void KCALL func(void);
 * A self-test that gets invoked during late bootup */
#ifdef CONFIG_SELFTEST
#define DEFINE_SELFTEST_FUNCTION(func) \
	DEFINE_CALLBACK(".rodata.free.callback.selftest", func)
#define DEFINE_TEST(name)                  \
	DEFINE_SELFTEST_FUNCTION(test_##name); \
	PRIVATE ATTR_USED ATTR_FREETEXT void   \
	NOTHROW(KCALL test_##name)(void)
#else /* CONFIG_SELFTEST */
#define DEFINE_SELFTEST_FUNCTION(func) /* nothing */
#endif /* !CONFIG_SELFTEST */
#endif /* CONFIG_BUILDING_KERNEL_CORE */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_SELFTEST_H */
