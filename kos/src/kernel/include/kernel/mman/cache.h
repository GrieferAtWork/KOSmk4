/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_CACHE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_CACHE_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>

#ifdef __CC__
DECL_BEGIN

/* Invoke cache clear callbacks for each and every globally reachable
 * component within the entire kernel.
 * This function is  called when  the kernel  has run  out of  physical/virtual
 * memory, or some other kind of limited, and dynamically allocatable resource.
 * @return: * : At  least some amount of some kind of resource was released.
 *              In this case the caller should re-attempt whatever lead them
 *              to try and clear caches to reclaim resource (usually memory)
 * @return: 0 : Nothing was released/freed.
 *              In this case, the caller should indicate failure due to
 *              lack of some necessary resource. */
FUNDEF NOBLOCK size_t NOTHROW(KCALL system_clearcaches)(void);

/* multi-thread-corrected version of `system_clearcaches()'.
 * This function should always be used in favor of `system_clearcaches()', as it
 * solves the scenario of multiple threads calling `system_clearcaches()' at the
 * same time, in which case resources may only get freed by one thread, with the
 * other thread never getting informed about that fact.
 * In this case,  `system_clearcaches()' would  normally (and correctly  I might  add)
 * return `0' for some threads, since that thread really didn't release any resources.
 * However, the intended use of  this function is inform a  caller who just failed  to
 * allocate some optional  resource, that  their resource may  have become  available,
 * and that they  should try again  (which is  something that isn't  fulfilled by  the
 * regular     `system_clearcaches()'     in     a     multi-threaded     environment)
 * That is where this function comes in:
 * >> void *my_alloc_tryhard() {
 * >>     void *result;
 * >>     result = my_alloc();
 * >>     if unlikely(!result) {
 * >>         uintptr_t cache_version;
 * >>         cache_version = 0;
 * >>         for (;;) {
 * >>             result = my_alloc();
 * >>             if (result)
 * >>                 break;
 * >>             if (!system_clearcaches_s(&cache_version))
 * >>                 break;
 * >>         }
 * >>     }
 * >>     return result;
 * >> }
 * WARNING: Do  _NOT_ write to  `*pversion' after a  non-zero value was returned!
 *          In  this  case, re-attempt  your  allocation and  upon  failure, call
 *          `system_clearcaches_s()'  again with an unmodified `*pversion' value.
 *          This function makes use of the  version number for tracking how  many
 *          more times the caller is allowed to make an attempt before giving up.
 * @return: * : At  least  some amount  of  some kind  of  resource (may  have) been
 *              released by some thread since the last time the function was called.
 *              In  this  case  the  caller  should  re-attempt  whatever  lead them
 *              to try and clear caches to reclaim resource (usually memory)
 * @return: 0 : Nothing was released/freed.
 *              In this case, the caller should indicate failure due to
 *              lack of some necessary resource. */
FUNDEF NOBLOCK NONNULL((1)) size_t
NOTHROW(KCALL system_clearcaches_s)(uintptr_t *__restrict pversion);


#ifdef CONFIG_BUILDING_KERNEL_CORE
#ifndef DEFINE_SYSTEM_CACHE_CLEAR
/* >> NOBLOCK size_t NOTHROW(KCALL func)(void);
 * Define a function that should be called when `system_clearcaches()' is invoked. */
#define DEFINE_SYSTEM_CACHE_CLEAR(func) DEFINE_CALLBACK(".rodata.cold.callback.system_clearcaches", func)
#endif /* !DEFINE_SYSTEM_CACHE_CLEAR */
#endif /* CONFIG_BUILDING_KERNEL_CORE */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_CACHE_H */
