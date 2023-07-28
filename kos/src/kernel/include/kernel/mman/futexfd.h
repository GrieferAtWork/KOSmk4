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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_FUTEXFD_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_FUTEXFD_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <compat/config.h>
#include <kos/asm/futex.h>
#include <kos/bits/futex-expr.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/bits/futex-expr.h>
#endif /* __ARCH_HAVE_COMPAT */

#ifdef __CC__
DECL_BEGIN

/* Operand size flags for `lfutexexpr::fe_condition' in `struct mfutexfd' */
#if (defined(__ARCH_HAVE_COMPAT) && __SIZEOF_POINTER__ != __ARCH_COMPAT_SIZEOF_POINTER)
#if __SIZEOF_POINTER__ >= 8
#define LFUTEX_WAIT_32BIT 0x80 /* `fe_offset' points at a `uint32_t' */
#define LFUTEX_WAIT_64BIT 0x00 /* `fe_offset' points at a `uint64_t' */
#else /* __SIZEOF_POINTER__ > 4 */
#define LFUTEX_WAIT_32BIT 0x00 /* `fe_offset' points at a `uint32_t' */
#define LFUTEX_WAIT_64BIT 0x80 /* `fe_offset' points at a `uint64_t' */
#endif /* __SIZEOF_POINTER__ <= 4 */
#define LFUTEX_WAIT_BITMASK 0x80 /* Mask for operand size */
#define LFUTEX_WAIT_IS32(x) (((x) & LFUTEX_WAIT_BITMASK) == LFUTEX_WAIT_32BIT)
#define LFUTEX_WAIT_IS64(x) (((x) & LFUTEX_WAIT_BITMASK) == LFUTEX_WAIT_64BIT)
#endif /* __ARCH_HAVE_COMPAT && __SIZEOF_POINTER__ != __ARCH_COMPAT_SIZEOF_POINTER */

/* Default operand size flags. */
#if (!defined(LFUTEX_WAIT_32BIT) && __SIZEOF_POINTER__ == 4)
#define LFUTEX_WAIT_32BIT 0
#endif /* !LFUTEX_WAIT_32BIT && __SIZEOF_POINTER__ == 4 */
#if (!defined(LFUTEX_WAIT_64BIT) && __SIZEOF_POINTER__ == 8)
#define LFUTEX_WAIT_64BIT 0
#endif /* !LFUTEX_WAIT_64BIT && __SIZEOF_POINTER__ == 8 */


#ifdef LFUTEX_WAIT_IS64
#define LFUTEXEXPR_CMD_SIZEOF(x) (LFUTEX_WAIT_IS64(x) ? 8 : 4)
#else /* LFUTEX_WAIT_IS64 */
#define LFUTEXEXPR_CMD_SIZEOF(x) __SIZEOF_POINTER__
#endif /* !LFUTEX_WAIT_IS64 */


struct mfutex;
struct mman;
struct mfutexfd {
	/* Handle type: `HANDLE_TYPE_FUTEXFD' */
	WEAK refcnt_t                              mfd_refcnt; /* Reference counter. */
	REF struct mfutex                         *mfd_futex;  /* [1..1][const] The futex used for poll. */
	WEAK REF struct mman                      *mfd_mman;   /* [1..1][const] Weak reference to mman used for expressions. */
	COMPILER_FLEXIBLE_ARRAY(struct lfutexexpr, mfd_expr);  /* [const] Poll-test expression. (`fe_offset' are absolute  addresses)
	                                                        * If defined, `fe_condition' includes bits from `LFUTEX_WAIT_BITMASK' */
};

/* Destroy a given mem-futex-fd object. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfutexfd_destroy)(struct mfutexfd *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct mfutexfd, mfd_refcnt, mfutexfd_destroy);

/* Create a new futexfd object.
 * @throw: E_INSUFFICIENT_RIGHTS: Tried to exceed `mfutexfd_maxexpr' w/o `CAP_SYS_RESOURCE' */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mfutexfd *FCALL
mfutexfd_new(REF struct mfutex *__restrict futex,
             NCX UNCHECKED void *base,
             NCX struct lfutexexpr const *expr)
		THROWS(E_BADALLOC, E_SEGFAULT, E_INSUFFICIENT_RIGHTS);
#ifdef __ARCH_HAVE_COMPAT
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mfutexfd *FCALL
compat_mfutexfd_new(REF struct mfutex *__restrict futex,
                    NCX UNCHECKED void *base,
                    NCX struct compat_lfutexexpr const *expr)
		THROWS(E_BADALLOC, E_SEGFAULT, E_INSUFFICIENT_RIGHTS);
#endif /* __ARCH_HAVE_COMPAT */

/* Max # of expressions in `lfutexexpr()' when using `LFUTEX_FDBIT'
 * - The limit can be overwritten system-wide by use of "/proc/kos/futexfd-maxexpr"
 * - A thread with `CAP_SYS_RESOURCE' is always allowed to exceed this limit. */
DATDEF size_t mfutexfd_maxexpr;


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_FUTEXFD_H */
