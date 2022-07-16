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
#ifndef GUARD_LIBUNWIND_EH_FRAME_C
#define GUARD_LIBUNWIND_EH_FRAME_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/byteorder.h>
#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <compat/config.h>
#include <kos/thread.h>
#include <kos/types.h>
#include <sys/param.h> /* NBBY */

#include <assert.h>
#include <inttypes.h>
#include <malloc.h>
#include <string.h>

#include <libunwind/cfi.h>
#include <libunwind/eh_frame.h>

#include "cfi.h"
#include "dwarf.h"
#include "eh_frame.h"

#ifndef __KERNEL__
#include <dlfcn.h>
#endif /* !__KERNEL__ */

/* Relaxed  CFA rules aren't currently needed (and as
 * a matter of fact: aren't anything that you'll find
 * apart of any standard. - I only though this is how
 * CFA was supposed to work at one point...) */
#undef CONFIG_DW_RELAXED_CFA_INITIALIZATION_RULES

#undef DEBUG_FRAME /* Build the .eh_frame parser! */


DECL_BEGIN

static_assert(NBBY == __CHAR_BIT__);

/* Helper macros for working with bitsets */
#define _bitset_word(base, i)       ((base)[(i) / NBBY])
#define _bitset_mask(i)             (1 << ((i) % NBBY))
#define bitset_contains(base, i)    (_bitset_word(base, i) & _bitset_mask(i))
#define bitset_insert(base, i)      (void)(_bitset_word(base, i) |= _bitset_mask(i))
#define bitset_remove(base, i)      (void)(_bitset_word(base, i) &= ~_bitset_mask(i))
#define bitset_insert_from(dst, src, i) (void)(_bitset_word(dst, i) |= (_bitset_word(src, i) & _bitset_mask(i)))
#define bitset_inherit(dst, src, i)     (void)(_bitset_word(dst, i) = (_bitset_word(dst, i) & ~_bitset_mask(i)) | (_bitset_word(src, i) & _bitset_mask(i)))


/* Helper macros for optional code */
/*[[[deemon
for (local name: [
	"CFI_UNWIND_COMMON_REGISTER_MAXCOUNT",
	"CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT",
	"CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT",
	"CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT",
	"CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT",
	"CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT",
]) {
	print("#if ", name, " != 0");
	print("#define IF_", name, "(...) __VA_ARGS__");
	print("#else /" "* ", name, " != 0 *" "/");
	print("#define IF_", name, "(...) /" "* nothing *" "/");
	print("#endif /" "* ", name, " == 0 *" "/");
}
]]]*/
#if CFI_UNWIND_COMMON_REGISTER_MAXCOUNT != 0
#define IF_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT(...) __VA_ARGS__
#else /* CFI_UNWIND_COMMON_REGISTER_MAXCOUNT != 0 */
#define IF_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT(...) /* nothing */
#endif /* CFI_UNWIND_COMMON_REGISTER_MAXCOUNT == 0 */
#if CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0
#define IF_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT(...) __VA_ARGS__
#else /* CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0 */
#define IF_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT(...) /* nothing */
#endif /* CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT == 0 */
#if CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT != 0
#define IF_CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT(...) __VA_ARGS__
#else /* CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT != 0 */
#define IF_CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT(...) /* nothing */
#endif /* CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT == 0 */
#if CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT != 0
#define IF_CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT(...) __VA_ARGS__
#else /* CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT != 0 */
#define IF_CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT(...) /* nothing */
#endif /* CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT == 0 */
#if CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT != 0
#define IF_CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT(...) __VA_ARGS__
#else /* CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT != 0 */
#define IF_CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT(...) /* nothing */
#endif /* CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT == 0 */
#if CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT != 0
#define IF_CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT(...) __VA_ARGS__
#else /* CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT != 0 */
#define IF_CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT(...) /* nothing */
#endif /* CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT == 0 */
/*[[[end]]]*/



/*[[[config CONFIG_HAVE_LIBUNWIND_CFA_SIGFRAME_STATE: bool = !defined(__OPTIMIZE_SIZE__)
 * Implement `unwind_fde_sigframe_exec(3)' and `unwind_cfa_sigframe_apply(3)' as
 * dedicated functions, rather than aliases for the non-sigframe variants.
 * ]]]*/
#ifdef CONFIG_NO_LIBUNWIND_CFA_SIGFRAME_STATE
#undef CONFIG_HAVE_LIBUNWIND_CFA_SIGFRAME_STATE
#elif !defined(CONFIG_HAVE_LIBUNWIND_CFA_SIGFRAME_STATE)
#ifndef __OPTIMIZE_SIZE__
#define CONFIG_HAVE_LIBUNWIND_CFA_SIGFRAME_STATE
#else /* !__OPTIMIZE_SIZE__ */
#define CONFIG_NO_LIBUNWIND_CFA_SIGFRAME_STATE
#endif /* __OPTIMIZE_SIZE__ */
#elif (-CONFIG_HAVE_LIBUNWIND_CFA_SIGFRAME_STATE - 1) == -1
#undef CONFIG_HAVE_LIBUNWIND_CFA_SIGFRAME_STATE
#define CONFIG_NO_LIBUNWIND_CFA_SIGFRAME_STATE
#endif /* ... */
/*[[[end]]]*/
#ifdef CFI_UNWIND_NO_SIGFRAME_COMMON_UNCOMMON_REGISTERS
#undef CONFIG_NO_LIBUNWIND_CFA_SIGFRAME_STATE
#undef CONFIG_HAVE_LIBUNWIND_CFA_SIGFRAME_STATE
#define CONFIG_NO_LIBUNWIND_CFA_SIGFRAME_STATE
#endif /* CFI_UNWIND_NO_SIGFRAME_COMMON_UNCOMMON_REGISTERS */

#define _convert_with_array(arr, index, error) \
	((index) >= COMPILER_LENOF(arr) ? (error) : arr[index])

/* Load register index convert arrays. */

/* Normal common/uncommon */
#ifndef cfi_unwind_register_dw2common
PRIVATE DEFINE_cfi_unwind_register_dw2common(__SIZEOF_POINTER__, _cur_dw2common);
#ifdef LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER
PRIVATE DEFINE_cfi_unwind_register_dw2common(__ARCH_COMPAT_SIZEOF_POINTER, _compat_cur_dw2common);
#define cfi_unwind_register_dw2common(addrsize, dw_regno)                                                                        \
	(CFI_ADDRSIZE_ISCOMPAT(addrsize) ? _convert_with_array(_compat_cur_dw2common, dw_regno, CFI_UNWIND_COMMON_REGISTER_MAXCOUNT) \
	                                 : _convert_with_array(_cur_dw2common, dw_regno, CFI_UNWIND_COMMON_REGISTER_MAXCOUNT))
#else /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#define cfi_unwind_register_dw2common(addrsize, dw_regno) \
	_convert_with_array(_cur_dw2common, dw_regno, CFI_UNWIND_COMMON_REGISTER_MAXCOUNT)
#endif /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#endif /* !cfi_unwind_register_dw2common */

#ifndef cfi_unwind_register_dw2uncommon
PRIVATE DEFINE_cfi_unwind_register_dw2uncommon(__SIZEOF_POINTER__, _cur_dw2uncommon);
#ifdef LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER
PRIVATE DEFINE_cfi_unwind_register_dw2uncommon(__ARCH_COMPAT_SIZEOF_POINTER, _compat_cur_dw2uncommon);
#define cfi_unwind_register_dw2uncommon(addrsize, dw_regno)                                                                          \
	(CFI_ADDRSIZE_ISCOMPAT(addrsize) ? _convert_with_array(_compat_cur_dw2uncommon, dw_regno, CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT) \
	                                 : _convert_with_array(_cur_dw2uncommon, dw_regno, CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT))
#else /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#define cfi_unwind_register_dw2uncommon(addrsize, dw_regno) \
	_convert_with_array(_cur_dw2uncommon, dw_regno, CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT)
#endif /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#endif /* !cfi_unwind_register_dw2uncommon */

#ifndef cfi_unwind_register_common2dw
PRIVATE DEFINE_cfi_unwind_register_common2dw(__SIZEOF_POINTER__, _cur_common2dw);
#ifdef LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER
PRIVATE DEFINE_cfi_unwind_register_common2dw(__ARCH_COMPAT_SIZEOF_POINTER, _compat_cur_common2dw);
#define cfi_unwind_register_common2dw(addrsize, common_regno)                                                                 \
	(CFI_ADDRSIZE_ISCOMPAT(addrsize) ? _convert_with_array(_compat_cur_common2dw, common_regno, CFI_UNWIND_REGISTER_MAXCOUNT) \
	                                 : _convert_with_array(_cur_common2dw, common_regno, CFI_UNWIND_REGISTER_MAXCOUNT))
#else /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#define cfi_unwind_register_common2dw(addrsize, common_regno) \
	_convert_with_array(_cur_common2dw, common_regno, CFI_UNWIND_REGISTER_MAXCOUNT)
#endif /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#endif /* !cfi_unwind_register_common2dw */

#ifndef cfi_unwind_register_uncommon2dw
PRIVATE DEFINE_cfi_unwind_register_uncommon2dw(__SIZEOF_POINTER__, _cur_uncommon2dw);
#ifdef LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER
PRIVATE DEFINE_cfi_unwind_register_uncommon2dw(__ARCH_COMPAT_SIZEOF_POINTER, _compat_cur_uncommon2dw);
#define cfi_unwind_register_uncommon2dw(addrsize, uncommon_regno)                                                                 \
	(CFI_ADDRSIZE_ISCOMPAT(addrsize) ? _convert_with_array(_compat_cur_uncommon2dw, uncommon_regno, CFI_UNWIND_REGISTER_MAXCOUNT) \
	                                 : _convert_with_array(_cur_uncommon2dw, uncommon_regno, CFI_UNWIND_REGISTER_MAXCOUNT))
#else /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#define cfi_unwind_register_uncommon2dw(addrsize, uncommon_regno) \
	_convert_with_array(_cur_uncommon2dw, uncommon_regno, CFI_UNWIND_REGISTER_MAXCOUNT)
#endif /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#endif /* !cfi_unwind_register_uncommon2dw */


/* Sigframe common/uncommon */
#ifndef cfi_unwind_sigframe_register_dw2common
PRIVATE DEFINE_cfi_unwind_sigframe_register_dw2common(__SIZEOF_POINTER__, _cur_sigframe_dw2common);
#ifdef LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER
PRIVATE DEFINE_cfi_unwind_sigframe_register_dw2common(__ARCH_COMPAT_SIZEOF_POINTER, _compat_cur_sigframe_dw2common);
#define cfi_unwind_sigframe_register_dw2common(addrsize, dw_regno)                                                                                 \
	(CFI_ADDRSIZE_ISCOMPAT(addrsize) ? _convert_with_array(_compat_cur_sigframe_dw2common, dw_regno, CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT) \
	                                 : _convert_with_array(_cur_sigframe_dw2common, dw_regno, CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT))
#else /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#define cfi_unwind_sigframe_register_dw2common(addrsize, dw_regno) \
	_convert_with_array(_cur_sigframe_dw2common, dw_regno, CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT)
#endif /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#endif /* !cfi_unwind_sigframe_register_dw2common */

#ifndef cfi_unwind_sigframe_register_dw2uncommon
PRIVATE DEFINE_cfi_unwind_sigframe_register_dw2uncommon(__SIZEOF_POINTER__, _cur_sigframe_dw2uncommon);
#ifdef LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER
PRIVATE DEFINE_cfi_unwind_sigframe_register_dw2uncommon(__ARCH_COMPAT_SIZEOF_POINTER, _compat_cur_sigframe_dw2uncommon);
#define cfi_unwind_sigframe_register_dw2uncommon(addrsize, dw_regno)                                                                                   \
	(CFI_ADDRSIZE_ISCOMPAT(addrsize) ? _convert_with_array(_compat_cur_sigframe_dw2uncommon, dw_regno, CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT) \
	                                 : _convert_with_array(_cur_sigframe_dw2uncommon, dw_regno, CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT))
#else /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#define cfi_unwind_sigframe_register_dw2uncommon(addrsize, dw_regno) \
	_convert_with_array(_cur_sigframe_dw2uncommon, dw_regno, CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT)
#endif /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#endif /* !cfi_unwind_sigframe_register_dw2uncommon */

#ifndef cfi_unwind_sigframe_register_common2dw
PRIVATE DEFINE_cfi_unwind_sigframe_register_common2dw(__SIZEOF_POINTER__, _cur_sigframe_common2dw);
#ifdef LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER
PRIVATE DEFINE_cfi_unwind_sigframe_register_common2dw(__ARCH_COMPAT_SIZEOF_POINTER, _compat_cur_sigframe_common2dw);
#define cfi_unwind_sigframe_register_common2dw(addrsize, common_regno)                                                                 \
	(CFI_ADDRSIZE_ISCOMPAT(addrsize) ? _convert_with_array(_compat_cur_sigframe_common2dw, common_regno, CFI_UNWIND_REGISTER_MAXCOUNT) \
	                                 : _convert_with_array(_cur_sigframe_common2dw, common_regno, CFI_UNWIND_REGISTER_MAXCOUNT))
#else /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#define cfi_unwind_sigframe_register_common2dw(addrsize, common_regno) \
	_convert_with_array(_cur_sigframe_common2dw, common_regno, CFI_UNWIND_REGISTER_MAXCOUNT)
#endif /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#endif /* !cfi_unwind_sigframe_register_common2dw */

#ifndef cfi_unwind_sigframe_register_uncommon2dw
PRIVATE DEFINE_cfi_unwind_sigframe_register_uncommon2dw(__SIZEOF_POINTER__, _cur_sigframe_uncommon2dw);
#ifdef LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER
PRIVATE DEFINE_cfi_unwind_sigframe_register_uncommon2dw(__ARCH_COMPAT_SIZEOF_POINTER, _compat_cur_sigframe_uncommon2dw);
#define cfi_unwind_sigframe_register_uncommon2dw(addrsize, uncommon_regno)                                                                 \
	(CFI_ADDRSIZE_ISCOMPAT(addrsize) ? _convert_with_array(_compat_cur_sigframe_uncommon2dw, uncommon_regno, CFI_UNWIND_REGISTER_MAXCOUNT) \
	                                 : _convert_with_array(_cur_sigframe_uncommon2dw, uncommon_regno, CFI_UNWIND_REGISTER_MAXCOUNT))
#else /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#define cfi_unwind_sigframe_register_uncommon2dw(addrsize, uncommon_regno) \
	_convert_with_array(_cur_sigframe_uncommon2dw, uncommon_regno, CFI_UNWIND_REGISTER_MAXCOUNT)
#endif /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#endif /* !cfi_unwind_sigframe_register_uncommon2dw */


/* Landing-pad common/uncommon */
#ifndef cfi_unwind_landing_register_dw2common
PRIVATE DEFINE_cfi_unwind_landing_register_dw2common(__SIZEOF_POINTER__, _cur_landing_dw2common);
#ifdef LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER
PRIVATE DEFINE_cfi_unwind_landing_register_dw2common(__ARCH_COMPAT_SIZEOF_POINTER, _compat_cur_landing_dw2common);
#define cfi_unwind_landing_register_dw2common(addrsize, dw_regno)                                                                                \
	(CFI_ADDRSIZE_ISCOMPAT(addrsize) ? _convert_with_array(_compat_cur_landing_dw2common, dw_regno, CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT) \
	                                 : _convert_with_array(_cur_landing_dw2common, dw_regno, CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT))
#else /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#define cfi_unwind_landing_register_dw2common(addrsize, dw_regno) \
	_convert_with_array(_cur_landing_dw2common, dw_regno, CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT)
#endif /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#endif /* !cfi_unwind_landing_register_dw2common */

#ifndef cfi_unwind_landing_register_dw2uncommon
PRIVATE DEFINE_cfi_unwind_landing_register_dw2uncommon(__SIZEOF_POINTER__, _cur_landing_dw2uncommon);
#ifdef LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER
PRIVATE DEFINE_cfi_unwind_landing_register_dw2uncommon(__ARCH_COMPAT_SIZEOF_POINTER, _compat_cur_landing_dw2uncommon);
#define cfi_unwind_landing_register_dw2uncommon(addrsize, dw_regno)                                                                                  \
	(CFI_ADDRSIZE_ISCOMPAT(addrsize) ? _convert_with_array(_compat_cur_landing_dw2uncommon, dw_regno, CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT) \
	                                 : _convert_with_array(_cur_landing_dw2uncommon, dw_regno, CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT))
#else /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#define cfi_unwind_landing_register_dw2uncommon(addrsize, dw_regno) \
	_convert_with_array(_cur_landing_dw2uncommon, dw_regno, CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT)
#endif /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#endif /* !cfi_unwind_landing_register_dw2uncommon */

#ifndef cfi_unwind_landing_register_common2dw
PRIVATE DEFINE_cfi_unwind_landing_register_common2dw(__SIZEOF_POINTER__, _cur_landing_common2dw);
#ifdef LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER
PRIVATE DEFINE_cfi_unwind_landing_register_common2dw(__ARCH_COMPAT_SIZEOF_POINTER, _compat_cur_landing_common2dw);
#define cfi_unwind_landing_register_common2dw(addrsize, common_regno)                                                                 \
	(CFI_ADDRSIZE_ISCOMPAT(addrsize) ? _convert_with_array(_compat_cur_landing_common2dw, common_regno, CFI_UNWIND_REGISTER_MAXCOUNT) \
	                                 : _convert_with_array(_cur_landing_common2dw, common_regno, CFI_UNWIND_REGISTER_MAXCOUNT))
#else /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#define cfi_unwind_landing_register_common2dw(addrsize, common_regno) \
	_convert_with_array(_cur_landing_common2dw, common_regno, CFI_UNWIND_REGISTER_MAXCOUNT)
#endif /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#endif /* !cfi_unwind_landing_register_common2dw */

#ifndef cfi_unwind_landing_register_uncommon2dw
PRIVATE DEFINE_cfi_unwind_landing_register_uncommon2dw(__SIZEOF_POINTER__, _cur_landing_uncommon2dw);
#ifdef LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER
PRIVATE DEFINE_cfi_unwind_landing_register_uncommon2dw(__ARCH_COMPAT_SIZEOF_POINTER, _compat_cur_landing_uncommon2dw);
#define cfi_unwind_landing_register_uncommon2dw(addrsize, uncommon_regno)                                                                 \
	(CFI_ADDRSIZE_ISCOMPAT(addrsize) ? _convert_with_array(_compat_cur_landing_uncommon2dw, uncommon_regno, CFI_UNWIND_REGISTER_MAXCOUNT) \
	                                 : _convert_with_array(_cur_landing_uncommon2dw, uncommon_regno, CFI_UNWIND_REGISTER_MAXCOUNT))
#else /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#define cfi_unwind_landing_register_uncommon2dw(addrsize, uncommon_regno) \
	_convert_with_array(_cur_landing_uncommon2dw, uncommon_regno, CFI_UNWIND_REGISTER_MAXCOUNT)
#endif /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */
#endif /* !cfi_unwind_landing_register_uncommon2dw */





#ifndef __INTELLISENSE__
DECL_END
#define FIND_SPECIFIC_ADDRESS
#include "eh_frame-find_fde.c.inl"
/**/
#include "eh_frame-find_fde.c.inl"

#define EH_FRAME_FDE_EXEC_CFA_STATE 1
#include "eh_frame-fde_exec.c.inl"

#ifndef CONFIG_NO_LIBUNWIND_CFA_SIGFRAME_STATE
#define EH_FRAME_FDE_EXEC_CFA_SIGFRAME_STATE 1
#include "eh_frame-fde_exec.c.inl"
#endif /* !CONFIG_NO_LIBUNWIND_CFA_SIGFRAME_STATE */

#ifdef LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES
#define EH_FRAME_FDE_EXEC_CFA_LANDING_STATE 1
#include "eh_frame-fde_exec.c.inl"
#endif /* LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES */

#define EH_FRAME_FDE_EXEC_CFA_VALUE 1
#include "eh_frame-fde_exec.c.inl"
#define EH_FRAME_FDE_EXEC_CFA_RULE 1
#include "eh_frame-fde_exec.c.inl"

DECL_BEGIN
#else /* !__INTELLISENSE__ */

PRIVATE
#if CFI_UNWIND_COMMON_REGISTER_MAXCOUNT != 0 && CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0
	NONNULL((1, 4, 5, 6))
#elif CFI_UNWIND_COMMON_REGISTER_MAXCOUNT != 0 || CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT != 0
	NONNULL((1, 3, 4, 5))
#else /* ... */
	NONNULL((1, 2, 3, 4))
#endif /* !... */
	unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_exec_until)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                            IF_CFI_UNWIND_COMMON_REGISTER_MAXCOUNT(unwind_cfa_register_t *common_init_regs,)
                                            IF_CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT(byte_t *uncommon_init_regs,)
                                            byte_t const *reader,
                                            byte_t const *end,
                                            unwind_cfa_state_t *__restrict result,
                                            void const *absolute_pc);

#ifndef CONFIG_NO_LIBUNWIND_CFA_SIGFRAME_STATE
PRIVATE
#if CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT != 0 && CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT != 0
	NONNULL((1, 4, 5, 6))
#elif CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT != 0 || CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT != 0
	NONNULL((1, 3, 4, 5))
#else /* ... */
	NONNULL((1, 2, 3, 4))
#endif /* !... */
	unsigned int
NOTHROW_NCX(CC libuw_unwind_sigframe_fde_exec_until)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                                     IF_CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT(unwind_cfa_register_t *common_init_regs,)
                                                     IF_CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT(byte_t *uncommon_init_regs,)
                                                     byte_t const *reader,
                                                     byte_t const *end,
                                                     unwind_cfa_sigframe_state_t *__restrict result,
                                                     void const *absolute_pc);
#endif /* !CONFIG_NO_LIBUNWIND_CFA_SIGFRAME_STATE */

/* Internal helper for calculating landing-pad rules. */
#ifdef LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES
PRIVATE
#if CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT != 0 && CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT != 0
	NONNULL((1, 4, 5, 6))
#elif CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT != 0 || CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT != 0
	NONNULL((1, 3, 4, 5))
#else /* ... */
	NONNULL((1, 2, 3, 4))
#endif /* !... */
	unsigned int
NOTHROW_NCX(CC libuw_unwind_landing_fde_exec_until)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                                    IF_CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT(unwind_cfa_register_t *common_init_regs,)
                                                    IF_CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT(byte_t *uncommon_init_regs,)
                                                    byte_t const *reader,
                                                    byte_t const *landing_start_reader,
                                                    byte_t const *end,
                                                    _unwind_cfa_landing_state_t *__restrict result,
                                                    void const *absolute_pc);
#endif /* LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES */

PRIVATE NONNULL((1, 2, 3, 4)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_exec_cfa_until)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                                byte_t const *reader,
                                                byte_t const *end,
                                                unwind_cfa_value_t *__restrict result,
                                                void const *absolute_pc);

PRIVATE NONNULL((1, 2, 3, 4)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_exec_rule_until)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                                 byte_t const *reader,
                                                 byte_t const *end,
                                                 unwind_cfa_register_t *__restrict rule,
                                                 unwind_regno_t dw_regno,
                                                 void const *absolute_pc);
#endif /* __INTELLISENSE__ */




/* Similar to `unwind_fde_exec()', but used to calculate the unwind rule
 * for `dw_regno' at the given text location. This is used to  implement
 * unwinding  for uncommon registers, since `unwind_fde_exec()' will not
 * already  calculate these during the first pass (thus keeping down the
 * memory requirements  imposed on  the one  responsible for  allocating
 * `unwind_cfa_state_t')
 * @param: self:   The FDE to execute in search of `absolute_pc'
 * @param: result: The CFA register result controller to-be filled.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTERN NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_rule)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                      unwind_cfa_register_t *__restrict result,
                                      unwind_regno_t dw_regno,
                                      void const *absolute_pc) {
	unsigned int error;
	/* `libuw_unwind_fde_exec_rule_until()'  won't  initialize
	 * the result, so pre-initialize it to an undefined state. */
	result->cr_rule = DW_CFA_register_rule_undefined;
	/* Start out by  scanning the evaluation-body,  as it's  most
	 * likely to contain the unwind rule requested by the caller. */
	error = libuw_unwind_fde_exec_rule_until(self,
	                                         self->f_evaltext,
	                                         self->f_evaltextend,
	                                         result,
	                                         dw_regno,
	                                         absolute_pc);
	if (error == UNWIND_SUCCESS && result->cr_rule == DW_CFA_register_rule_undefined) {
		/* If we couldn't find it in the init-body, try the eval-body. */
		error = libuw_unwind_fde_exec_rule_until(self,
		                                         self->f_inittext,
		                                         self->f_inittextend,
		                                         result,
		                                         dw_regno,
		                                         absolute_pc);
	}
	return error;
}



/* Same as `unwind_fde_exec()', however only calculate the CFA restore descriptor.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTERN NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_exec_cfa)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                          unwind_cfa_value_t *__restrict result,
                                          void const *absolute_pc) {
	unsigned int error;
	bzero(result, sizeof(*result));
	error = libuw_unwind_fde_exec_cfa_until(self,
	                                        self->f_inittext,
	                                        self->f_inittextend,
	                                        result,
	                                        (void *)-1);
	if likely(error == UNWIND_SUCCESS) {
		error = libuw_unwind_fde_exec_cfa_until(self,
		                                        self->f_evaltext,
		                                        self->f_evaltextend,
		                                        result,
		                                        absolute_pc);
	}
	TRACE("unwind_fde_exec_cfa() -> %u\n", error);
	return error;
}

PRIVATE NONNULL((1, 2, 3, 5)) unsigned int CC
execute_eh_frame_expression(unwind_fde_t *__restrict fde, /* Only non-const for lazy initialized fields! */
                            byte_t const *__restrict expression_pointer,
                            unwind_getreg_t reg_getter,
                            void const *reg_callback_arg,
                            uintptr_t *__restrict presult,
                            uintptr_t cfa_value) {
	unsigned int result;
	unwind_ste_t top;
	unwind_emulator_t emulator;
	size_t expr_length;
	expr_length = dwarf_decode_uleb128((byte_t const **)&expression_pointer);
	bzero(&emulator, sizeof(emulator));
	emulator.ue_pc             = expression_pointer;
	emulator.ue_pc_start       = expression_pointer;
	emulator.ue_pc_end         = expression_pointer + expr_length;
	emulator.ue_regget         = reg_getter;
	emulator.ue_regget_arg     = reg_callback_arg;
	emulator.ue_addrsize       = fde->f_addrsize;
	emulator.ue_bjmprem        = UNWIND_EMULATOR_BJMPREM_DEFAULT;
	emulator.ue_call_frame_cfa = cfa_value;
	emulator.ue_bases          = fde->f_bases;
	emulator.ue_tlsbase        = (byte_t *)-1;
	top.s_type                 = UNWIND_STE_CONSTANT;
	top.s_uconst               = cfa_value;

	/* Do the exec. */
	result = libuw_unwind_emulator_exec_autostack(&emulator,
	                                              &top,
	                                              NULL,
	                                              presult);

#if 0 /* Could be done, but isn't really necessary... */
	fde->f_bases = emulator.ue_bases;
#endif

	/* Return success/error */
	return result;
}

static_assert(CFI_REGISTER_SIZE(sizeof(void *), CFI_UNWIND_REGISTER_SP(sizeof(void *))) == sizeof(uintptr_t));
static_assert(CFI_REGISTER_SIZE(sizeof(void *), CFI_UNWIND_REGISTER_PC(sizeof(void *))) == sizeof(void *));
static_assert(CFI_REGISTER_MEMSIZE(sizeof(void *), CFI_UNWIND_REGISTER_SP(sizeof(void *))) == sizeof(uintptr_t));
static_assert(CFI_REGISTER_MEMSIZE(sizeof(void *), CFI_UNWIND_REGISTER_PC(sizeof(void *))) == sizeof(void *));
#ifdef LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER
static_assert(CFI_REGISTER_SIZE(__ARCH_COMPAT_SIZEOF_POINTER, CFI_UNWIND_REGISTER_SP(__ARCH_COMPAT_SIZEOF_POINTER)) == sizeof(uintptr_t));
static_assert(CFI_REGISTER_SIZE(__ARCH_COMPAT_SIZEOF_POINTER, CFI_UNWIND_REGISTER_PC(__ARCH_COMPAT_SIZEOF_POINTER)) == sizeof(void *));
static_assert(CFI_REGISTER_MEMSIZE(__ARCH_COMPAT_SIZEOF_POINTER, CFI_UNWIND_REGISTER_SP(__ARCH_COMPAT_SIZEOF_POINTER)) == __ARCH_COMPAT_SIZEOF_POINTER);
static_assert(CFI_REGISTER_MEMSIZE(__ARCH_COMPAT_SIZEOF_POINTER, CFI_UNWIND_REGISTER_PC(__ARCH_COMPAT_SIZEOF_POINTER)) == __ARCH_COMPAT_SIZEOF_POINTER);
#endif /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */



/* Calculate the CFA (CanonicalFrameAddress) of the given CFA restore descriptor.
 * @param: self: The CFA state to-be used to calculate the CFA
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
INTERN NONNULL((1, 2, 3, 5)) unsigned int CC
libuw_unwind_fde_calculate_cfa(unwind_fde_t *__restrict fde, /* Only non-const for lazy initialized fields! */
                               unwind_cfa_value_t const *__restrict self,
                               unwind_getreg_t reg_getter,
                               void const *reg_callback_arg,
                               uintptr_t *__restrict presult) {
	unsigned int error;
	/* Calculate the CFA value. */
	if (self->cv_type == UNWIND_CFA_VALUE_REGISTER) {
		if unlikely(CFI_REGISTER_SIZE(fde->f_addrsize, self->cv_reg) != sizeof(uintptr_t))
			ERRORF(err_noaddr_register, "regno=%u", (unsigned int)self->cv_reg);
		error = (*reg_getter)(reg_callback_arg, self->cv_reg, presult);
		if unlikely(error != UNWIND_SUCCESS)
			ERRORF(err, "regno=%u (%u)", (unsigned int)self->cv_reg, error);
		*presult += self->cv_value;
	} else if (self->cv_type == UNWIND_CFA_VALUE_EXPRESSION) {
		/* Use a CFI emulator to calculate the CFA base value. */
		return execute_eh_frame_expression(fde, self->cv_expr,
		                                   reg_getter,
		                                   reg_callback_arg,
		                                   presult, 0);
	} else {
		*presult = 0;
	}
	return UNWIND_SUCCESS;
err_noaddr_register:
	return UNWIND_APPLY_NOADDR_REGISTER;
err:
	return error;
}

#ifdef __INTELLISENSE__

#ifdef LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES
/* For use with `unwind_fde_landing_exec()': Apply register rules previously calculated.
 * @param: self:        The CFA state to-be used when applying registers
 * @param: absolute_pc: Same value as was previously used to calculate `fde' from `self'
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
PRIVATE NONNULL((1, 2, 4, 6)) unsigned int CC
_unwind_cfa_landing_apply(_unwind_cfa_landing_state_t *__restrict self,
                          unwind_fde_t *__restrict fde, /* Only non-const for lazy initialized fields! */
                          void const *absolute_pc,
                          unwind_getreg_t reg_getter, void const *reg_getter_arg,
                          unwind_setreg_t reg_setter, void *reg_setter_arg);
#endif /* LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES */


#else /* __INTELLISENSE__ */
DECL_END

#define EH_FRAME_CFA_APPLY 1
#include "eh_frame-cfa_apply.c.inl"

#ifndef CONFIG_NO_LIBUNWIND_CFA_SIGFRAME_STATE
#define EH_FRAME_CFA_SIGFRAME_APPLY 1
#include "eh_frame-cfa_apply.c.inl"
#endif /* !CONFIG_NO_LIBUNWIND_CFA_SIGFRAME_STATE */

#ifdef LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES
#define EH_FRAME_CFA_LANDING_APPLY 1
#include "eh_frame-cfa_apply.c.inl"
#endif /* LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES */

DECL_BEGIN
#endif /* !__INTELLISENSE__ */




/************************************************************************/
/* CFI LANDING PAD & CAPSULES                                           */
/************************************************************************/

typedef struct landing1_backup landing1_backup_t;
struct landing1_backup {
	uintptr_t          l1b_backup; /* Old value for `DW_CFA_GNU_args_size'. */
	landing1_backup_t *l1b_prev;   /* [0..1] Previous backup */
};

#ifndef __KERNEL__
PRIVATE void
NOTHROW_NCX(CC landing1_backup_freechain)(landing1_backup_t *base) {
	landing1_backup_t *next;
	while (base) {
		next = base->l1b_prev;
		free(base);
		base = next;
	}
}
#endif /* !__KERNEL__ */

#ifdef LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES

struct cfa_parser {
	unwind_fde_t *cp_fde;    /* [1..1][const] Associated FDE. Only non-const for lazy initialized fields! */
	uintptr_t     cp_pc;     /* Program counter position (absolute) */
	byte_t const *cp_reader; /* [1..1] CFA instruction program counter. */
	byte_t const *cp_end;    /* [1..1][const] End of CFA instructions. */
};

#define READ_CFA_INSTRUCTION_STARTCAPSULE ((unsigned int)-1)
#define READ_CFA_INSTRUCTION_ENDCAPSULE   ((unsigned int)-2)

/* Yield the next capsule instruction and advance the parser.
 * @return: READ_CFA_INSTRUCTION_STARTCAPSULE: `parser->cp_reader' points after a `DW_CFA_KOS_startcapsule' instruction
 * @return: READ_CFA_INSTRUCTION_ENDCAPSULE:   `parser->cp_reader' points after a `DW_CFA_KOS_endcapsule' instruction
 * @return: UNWIND_NO_FRAME:                   End-of-text, or `absolute_pc' has been reached.
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION:    [...]
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION:    [...] */
PRIVATE NONNULL((1)) unsigned int
NOTHROW_NCX(CC read_capsule_instruction)(struct cfa_parser *__restrict parser) {
	unsigned int result = UNWIND_NO_FRAME;
	byte_t const *cfa_reader = parser->cp_reader;
	uintptr_t current_pc = parser->cp_pc;
	while (cfa_reader < parser->cp_end/* &&
	       current_pc <= (uintptr_t)parser->cp_maxpc*/) {
		uint8_t opcode, operand;
		opcode  = *cfa_reader++;
		operand = opcode & 0x3f;
		opcode  = opcode & 0xc0;
		if (opcode == DW_CFA_advance_loc) {
			TRACE("DW_CFA_advance_loc\n");
			current_pc += (uintptr_t)operand * parser->cp_fde->f_codealign;
		} else if (opcode == DW_CFA_offset) {
			TRACE("DW_CFA_offset(%" PRIu8 ")\n", operand);
			dwarf_decode_uleb128((byte_t const **)&cfa_reader);
		} else if (opcode == DW_CFA_restore) {
			TRACE("DW_CFA_restore\n");
		} else {
			switch (operand) {

			CASE(DW_CFA_set_loc)
				/* Decode the PC pointer according to FDE pointer encoding. */
				current_pc = (uintptr_t)dwarf_decode_pointer((byte_t const **)&cfa_reader,
				                                             parser->cp_fde->f_ptrenc,
				                                             parser->cp_fde->f_addrsize,
				                                             &parser->cp_fde->f_bases);
				current_pc += (uintptr_t)parser->cp_fde->f_pcstart;
				break;

			CASE(DW_CFA_advance_loc1)
				current_pc += (uintptr_t)(*(uint8_t const *)cfa_reader *
				                          parser->cp_fde->f_codealign);
				cfa_reader += 1;
				break;

			CASE(DW_CFA_advance_loc2)
				current_pc += (uintptr_t)UNALIGNED_GET16((uint16_t const *)cfa_reader) *
				              parser->cp_fde->f_codealign;
				cfa_reader += 2;
				break;

			CASE(DW_CFA_advance_loc4)
				current_pc += (uintptr_t)UNALIGNED_GET32((uint32_t const *)cfa_reader) *
				              parser->cp_fde->f_codealign;
				cfa_reader += 4;
				break;

			CASE(DW_CFA_offset_extended)
			CASE(DW_CFA_register)
			CASE(DW_CFA_def_cfa)
			CASE(DW_CFA_val_offset)
			CASE(DW_CFA_GNU_negative_offset_extended)
				dwarf_decode_uleb128((byte_t const **)&cfa_reader);
				ATTR_FALLTHROUGH
			CASE(DW_CFA_restore_extended)
			CASE(DW_CFA_undefined)
			CASE(DW_CFA_same_value)
			CASE(DW_CFA_def_cfa_register)
			CASE(DW_CFA_def_cfa_offset)
			CASE(DW_CFA_GNU_args_size)
				dwarf_decode_uleb128((byte_t const **)&cfa_reader);
				break;

			CASE(DW_CFA_def_cfa_sf)
			CASE(DW_CFA_offset_extended_sf)
			CASE(DW_CFA_val_offset_sf)
				dwarf_decode_uleb128((byte_t const **)&cfa_reader);
				ATTR_FALLTHROUGH
			CASE(DW_CFA_def_cfa_offset_sf)
				dwarf_decode_sleb128((byte_t const **)&cfa_reader);
				break;

			CASE(DW_CFA_def_cfa_expression) {
				size_t expr_size;
skip_expression:
				expr_size = dwarf_decode_uleb128((byte_t const **)&cfa_reader);
				if unlikely(OVERFLOW_UADD((uintptr_t)cfa_reader, expr_size,
				                          (uintptr_t *)(byte_t const **)&cfa_reader) ||
				            cfa_reader > parser->cp_end) {
					ERRORF(err_illegal_instruction,
					       "cfa_reader=%p, expr_size=%" PRIuSIZ "(%#" PRIxSIZ "), cfa_end=%p",
					       (uintptr_t)cfa_reader - expr_size,
					       expr_size, expr_size, parser->cp_end);
				}
			}	break;

			CASE(DW_CFA_expression)
			CASE(DW_CFA_val_expression)
				dwarf_decode_uleb128((byte_t const **)&cfa_reader);
				goto skip_expression;

			CASE(DW_CFA_nop)
			CASE(DW_CFA_remember_state)
			CASE(DW_CFA_restore_state)
				break;

			CASE(DW_CFA_KOS_startcapsule)
				result = READ_CFA_INSTRUCTION_STARTCAPSULE;
				goto done;

			CASE(DW_CFA_KOS_endcapsule)
				result = READ_CFA_INSTRUCTION_ENDCAPSULE;
				goto done;

			default:
				ERRORF(err_unknown_instruction, "operand=%#.2" PRIx8 "\n", operand);
			}
		}
	}
done:
	parser->cp_reader = cfa_reader;
	parser->cp_pc     = current_pc;
	return result;
err_illegal_instruction:
	result = UNWIND_CFA_ILLEGAL_INSTRUCTION;
	goto done;
err_unknown_instruction:
	result = UNWIND_CFA_UNKNOWN_INSTRUCTION;
	goto done;
}

/* Find the end (that is: a pointer after the `DW_CFA_KOS_endcapsule' opcode)
 * of the capsule containing `cfa_reader'. This function accounts for  nested
 * capsules by essentially search for the first unmatched endcapsule opcode.
 * @return: READ_CFA_INSTRUCTION_ENDCAPSULE: Success
 * @return: * :                              Error */
PRIVATE NONNULL((1)) unsigned int
NOTHROW_NCX(CC find_capsule_end)(struct cfa_parser *__restrict parser) {
	unsigned int result;
	unsigned int recursion = 0;
	for (;;) {
		result = read_capsule_instruction(parser);
		if (result == READ_CFA_INSTRUCTION_STARTCAPSULE) {
			++recursion;
		} else if (result == READ_CFA_INSTRUCTION_ENDCAPSULE) {
			if (!recursion)
				break;
			--recursion;
		} else {
			break;
		}
	}
	return result;
}


PRIVATE NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC unwind_capsules)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                unwind_cfa_landing_state_t *__restrict result,
                                void const *absolute_pc, void const *landingpad_pc) {
	unsigned int error;
	struct cfa_parser capsule_start;
	struct cfa_parser capsule_end;
	capsule_start.cp_fde    = self;
	capsule_start.cp_reader = self->f_evaltext;
	capsule_start.cp_end    = self->f_evaltextend;
	capsule_start.cp_pc     = (uintptr_t)self->f_pcstart;

	for (;;) {
		/* Find the start of the next capsule. */
		error = read_capsule_instruction(&capsule_start);
		if unlikely(error != READ_CFA_INSTRUCTION_STARTCAPSULE ||
		            capsule_start.cp_pc > (uintptr_t)absolute_pc) {
			/* This really shouldn't happen, unless CFA data changes under our noses... */
			ERRORF(no_capsules,
			       "error               = %u\n"
			       "capsule_start.cp_pc = %p\n"
			       "absolute_pc         = %p",
			       error, capsule_start.cp_pc,
			       absolute_pc);
		}
		memcpy(&capsule_end, &capsule_start, sizeof(struct cfa_parser));
		error = find_capsule_end(&capsule_end);
		if (error != READ_CFA_INSTRUCTION_ENDCAPSULE)
			goto err;
		/* Check if `absolute_pc' is contained inside of `capsule_start...capsule_end' */
		if ((uintptr_t)absolute_pc >= capsule_start.cp_pc &&
		    (uintptr_t)absolute_pc < capsule_end.cp_pc)
			break;
		memcpy(&capsule_start, &capsule_end, sizeof(struct cfa_parser));
	}
	/* At this point, we've found the outer-most capsule that `absolute_pc' is apart of.
	 * With that in  mind, if `landingpad_pc'  is also  apart of this  capsule, then  we
	 * must narrow down our capsule range:
	 * >> capsule_start:[
	 * >>                   [
	 * >>                       ...
	 * >>                   ]
	 * >>                   [                 -- Innermost capsule to unwind starts here
	 * >>                       absolute_pc
	 * >>                   ]
	 * >>                   [
	 * >>                       except_pc
	 * >>                   ]
	 * >> capsule_end:  ]
	 *
	 * But also consider this example:
	 * >> capsule_start:[
	 * >>                   absolute_pc
	 * >>                   [
	 * >>                       except_pc
	 * >>                   ]
	 * >> capsule_end:  ]
	 * In  this case,  we mustn't unwind  anything before jumping  to `except_pc', which
	 * is a case we can easily detect when ending up with a capsule range that no longer
	 * includes `absolute_pc' */
	while ((uintptr_t)landingpad_pc >= capsule_start.cp_pc &&
	       (uintptr_t)landingpad_pc < capsule_end.cp_pc) {
		/* Landing pad is apart of our capsule range. -> Must narrow down the search! */
		capsule_start.cp_end = capsule_end.cp_reader - 1; /* Point at the endcapsule opcode */
		for (;;) {
			error = read_capsule_instruction(&capsule_start);
			if (error != READ_CFA_INSTRUCTION_STARTCAPSULE) { /* No nested capsules. */
no_capsules:
				return UNWIND_SUCCESS;
			}
			memcpy(&capsule_end, &capsule_start, sizeof(struct cfa_parser));
			error = find_capsule_end(&capsule_end);
			if unlikely(error != READ_CFA_INSTRUCTION_ENDCAPSULE)
				ERRORF(no_capsules, "error=%u", error); /* This really shouldn't happen, unless CFA data changes under our noses... */
			if ((uintptr_t)absolute_pc >= capsule_start.cp_pc &&
			    (uintptr_t)absolute_pc < capsule_end.cp_pc)
				break; /* Found the next more-inner capsule that contains the exception PC */
			/* This capsule doesn't  contain our  exception PC anymore,  but that  doesn't
			 * necessarily mean that there's no sibling capsule that might contain our PC! */
			memcpy(&capsule_start, &capsule_end, sizeof(struct cfa_parser));
		}
	}
	/* All right! at  this point we've  found the range  of capsules we  were looking  for,
	 * such  that the exception PC is located within the capsule range, but the landing-pad
	 * PC is located outside of it. With this in mind, we must now execute CFA instructions
	 * from within this range in order to build the unwind rule table. */
	assert((uintptr_t)absolute_pc >= capsule_start.cp_pc &&
	       (uintptr_t)absolute_pc < capsule_end.cp_pc);
	assert(!((uintptr_t)landingpad_pc >= capsule_start.cp_pc &&
	         (uintptr_t)landingpad_pc < capsule_end.cp_pc));

	/* Scan our capsule for unwinding rules. */
	/* Execute the init-body */
	error = libuw_unwind_landing_fde_exec_until(self,
	                                            IF_CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT(NULL,)
	                                            IF_CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT(NULL,)
	                                            self->f_inittext,
	                                            self->f_inittextend,
	                                            self->f_inittextend,
	                                            &result->cs_state,
	                                            (void *)-1);
	if likely(error == UNWIND_SUCCESS) {
		IF_CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT(unwind_cfa_register_t common_init_regs[CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT];)
		IF_CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT(byte_t uncommon_init_regs[(CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT + NBBY) / NBBY];)
		IF_CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT(static_assert(sizeof(common_init_regs) == sizeof(result->cs_state.cs_regs));)
		IF_CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT(static_assert(sizeof(uncommon_init_regs) == sizeof(result->cs_state.cs_uncommon));)
		IF_CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT(memcpy(common_init_regs, result->cs_state.cs_regs, sizeof(result->cs_state.cs_regs));)
		IF_CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT(memcpy(uncommon_init_regs, result->cs_state.cs_uncommon, sizeof(result->cs_state.cs_uncommon));)
		/* Execute the eval-body */
		error = libuw_unwind_landing_fde_exec_until(self,
		                                            IF_CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT(common_init_regs,)
		                                            IF_CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT(uncommon_init_regs,)
		                                            self->f_evaltext,
		                                            capsule_start.cp_reader,
		                                            capsule_end.cp_reader - 1,
		                                            &result->cs_state,
		                                            absolute_pc);
	}
	/* Indicate that (probably) are capsules that must be unwound. */
	result->cs_has_capsules = 1;
	return error;
err:
	/* If  we  get here  due  to a  specific  instruction, then
	 * that instruction wasn't allowed wherever it appeared at. */
	if (error >= (uintptr_t)-16)
		error = UNWIND_CFA_ILLEGAL_INSTRUCTION;
	return error;
}
#endif /* LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES */



/* Behaves similar to `unwind_fde_exec()', but must  be used to calculate the  CFA
 * for the purpose of jumping to a  custom `landingpad_pc' as part of handling  an
 * exceptions which  originates from  `absolute_pc' within  the current  cfi-proc.
 * This function calculates the relative CFI-capsule offset between `absolute_pc',
 * and `landingpad_pc', as well as the GNU-argsize adjustment. Once this is  done,
 * the caller must use `unwind_cfa_landing_apply()' to apply these transformations
 * onto some given register state, which may then be used to resume execution.
 * @param: self:   The FDE to execute in search of `absolute_pc'
 * @param: result: CFA state descriptor, to-be filled with restore information upon success.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTERN NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_landing_exec)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                              unwind_cfa_landing_state_t *__restrict result,
                                              void const *absolute_pc, void const *landingpad_pc) {
	uintptr_t current_pc;
	byte_t const *cfa_reader;
	byte_t const *cfa_end;
	landing1_backup_t *state_backup_list = NULL;
	landing1_backup_t *state_backup_free = NULL; /* Free list of state backups. */
#ifdef LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES
	unsigned int capsule_recursion = 0;
#endif /* LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES */
	(void)landingpad_pc;
	bzero(result, sizeof(*result));
	cfa_reader = self->f_evaltext;
	cfa_end    = self->f_evaltextend;
	assertf(((uintptr_t)absolute_pc >= (uintptr_t)self->f_pcstart &&
	         (uintptr_t)absolute_pc <= (uintptr_t)self->f_pcend) ||
	        (absolute_pc == (void *)-1),
	        "self->f_pcstart = %p\n"
	        "self->f_pcend   = %p\n"
	        "absolute_pc     = %p\n",
	        self->f_pcstart, self->f_pcend, absolute_pc);
	/* First round: Calculate the GNU adjustment, but assume there's not  going
	 *              to be any CFI capsules (at least not for `absolute_pc'). If
	 *              we end up with a  non-zero `capsule_recursion' in the  end,
	 *              then  we know we have a lot of work ahead of us in order to
	 *              figure out what exactly is affected by the capsule. */
	current_pc = (uintptr_t)self->f_pcstart;
	while (cfa_reader < cfa_end && current_pc <= (uintptr_t)absolute_pc) {
		uint8_t opcode, operand;
		opcode  = *cfa_reader++;
		operand = opcode & 0x3f;
		opcode  = opcode & 0xc0;
		if (opcode == DW_CFA_advance_loc) {
			TRACE("DW_CFA_advance_loc\n");
			current_pc += (uintptr_t)operand * self->f_codealign;
		} else if (opcode == DW_CFA_offset) {
			TRACE("DW_CFA_offset(%" PRIu8 ")\n", operand);
			dwarf_decode_uleb128((byte_t const **)&cfa_reader);
		} else if (opcode == DW_CFA_restore) {
			TRACE("DW_CFA_restore\n");
		} else {
			switch (operand) {

			CASE(DW_CFA_set_loc)
				/* Decode the PC pointer according to FDE pointer encoding. */
				current_pc = (uintptr_t)dwarf_decode_pointer((byte_t const **)&cfa_reader,
				                                             self->f_ptrenc,
				                                             self->f_addrsize,
				                                             &self->f_bases);
				current_pc += (uintptr_t)self->f_pcstart;
				break;

			CASE(DW_CFA_advance_loc1)
				current_pc += (uintptr_t)(*(uint8_t const *)cfa_reader) * self->f_codealign;
				cfa_reader += 1;
				break;

			CASE(DW_CFA_advance_loc2)
				current_pc += (uintptr_t)UNALIGNED_GET16((uint16_t const *)cfa_reader) * self->f_codealign;
				cfa_reader += 2;
				break;

			CASE(DW_CFA_advance_loc4)
				current_pc += (uintptr_t)UNALIGNED_GET32((uint32_t const *)cfa_reader) * self->f_codealign;
				cfa_reader += 4;
				break;

			CASE(DW_CFA_offset_extended)
			CASE(DW_CFA_register)
			CASE(DW_CFA_def_cfa)
			CASE(DW_CFA_val_offset)
			CASE(DW_CFA_GNU_negative_offset_extended)
				dwarf_decode_uleb128((byte_t const **)&cfa_reader);
				ATTR_FALLTHROUGH
			CASE(DW_CFA_restore_extended)
			CASE(DW_CFA_undefined)
			CASE(DW_CFA_same_value)
			CASE(DW_CFA_def_cfa_register)
			CASE(DW_CFA_def_cfa_offset)
				dwarf_decode_uleb128((byte_t const **)&cfa_reader);
				break;

			CASE(DW_CFA_def_cfa_sf)
			CASE(DW_CFA_offset_extended_sf)
			CASE(DW_CFA_val_offset_sf)
				dwarf_decode_uleb128((byte_t const **)&cfa_reader);
				ATTR_FALLTHROUGH
			CASE(DW_CFA_def_cfa_offset_sf)
				dwarf_decode_sleb128((byte_t const **)&cfa_reader);
				break;

			CASE(DW_CFA_remember_state) {
				landing1_backup_t *backup;
				backup = state_backup_free;
				if (backup) {
					state_backup_free = backup->l1b_prev;
				} else {
					/* Check if we have enough stack space left to create a backup. */
#ifdef __KERNEL__
					if (get_stack_avail() < ((256 * sizeof(void *)) + sizeof(landing1_backup_t)))
						ERRORF(err_nomem, "get_stack_avail()=%" PRIuSIZ "", get_stack_avail());
					backup = (landing1_backup_t *)alloca(sizeof(landing1_backup_t));
#else /* __KERNEL__ */
					backup = (landing1_backup_t *)malloc(sizeof(landing1_backup_t));
					if unlikely(!backup)
						ERROR(err_nomem);
#endif /* !__KERNEL__ */
				}
				backup->l1b_backup = result->cs_lp_adjustment;
				backup->l1b_prev   = state_backup_list;
				state_backup_list  = backup;
			}	break;

			CASE(DW_CFA_restore_state) {
				landing1_backup_t *backup;
				backup = state_backup_list;
				if unlikely(!backup)
					ERROR(err_illegal_instruction);
				result->cs_lp_adjustment = backup->l1b_backup;
				/* Delete the backup descriptor (and add it to the free-list) */
				state_backup_list = backup->l1b_prev;
				backup->l1b_prev  = state_backup_free;
				state_backup_free = backup;
			}	break;

#ifdef LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES
			CASE(DW_CFA_KOS_startcapsule)
				++capsule_recursion;
				break;

			CASE(DW_CFA_KOS_endcapsule)
				if likely(capsule_recursion) /* This should never fail... */
					--capsule_recursion;
				break;
#endif /* LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES */

			CASE(DW_CFA_def_cfa_expression) {
				size_t expr_size;
skip_expression:
				expr_size = dwarf_decode_uleb128((byte_t const **)&cfa_reader);
				if unlikely(OVERFLOW_UADD((uintptr_t)cfa_reader, expr_size,
				                          (uintptr_t *)(byte_t const **)&cfa_reader) ||
				            cfa_reader > cfa_end) {
					ERRORF(err_illegal_instruction,
					       "cfa_reader=%p, expr_size=%" PRIuSIZ "(%#" PRIxSIZ "), cfa_end=%p",
					       (uintptr_t)cfa_reader - expr_size,
					       expr_size, expr_size, cfa_end);
				}
			}	break;

			CASE(DW_CFA_expression)
			CASE(DW_CFA_val_expression)
				dwarf_decode_uleb128((byte_t const **)&cfa_reader);
				goto skip_expression;

			CASE(DW_CFA_GNU_args_size)
				/* Landing pad stack adjustment */
				result->cs_lp_adjustment = dwarf_decode_uleb128((byte_t const **)&cfa_reader);
				break;

			CASE(DW_CFA_nop) /* no-op. */
				break;

			default:
				ERRORF(err_unknown_instruction, "operand=%#.2" PRIx8 "\n", operand);
			}
		}
	}
#ifndef __KERNEL__
	landing1_backup_freechain(state_backup_free);
	landing1_backup_freechain(state_backup_list);
#endif /* !__KERNEL__ */
#ifdef LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES
	if unlikely(capsule_recursion != 0) {
		/* Scan capsules for rules. */
		return unwind_capsules(self, result,
		                       absolute_pc,
		                       landingpad_pc);
	}
#endif /* LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES */
	return UNWIND_SUCCESS;
#ifndef __KERNEL__
	{
		unsigned int error;
err_unknown_instruction:
		error = UNWIND_CFA_UNKNOWN_INSTRUCTION;
		goto err_common;
err_nomem:
		error = UNWIND_BADALLOC;
		goto err_common;
err_illegal_instruction:
		error = UNWIND_CFA_ILLEGAL_INSTRUCTION;
err_common:
		landing1_backup_freechain(state_backup_free);
		landing1_backup_freechain(state_backup_list);
		return error;
	}
#else /* !__KERNEL__ */
err_unknown_instruction:
	return UNWIND_CFA_UNKNOWN_INSTRUCTION;
err_nomem:
	return UNWIND_BADALLOC;
err_illegal_instruction:
	return UNWIND_CFA_ILLEGAL_INSTRUCTION;
#endif /* __KERNEL__ */
}



/* For use with `unwind_fde_landing_exec()': Apply register rules previously calculated.
 * @param: self:        The CFA state to-be used when applying registers
 * @param: absolute_pc: Same value as was previously used to calculate `fde' from `self'
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
INTERN NONNULL((1, 2, 4, 6)) unsigned int CC
libuw_unwind_cfa_landing_apply(unwind_cfa_landing_state_t *__restrict self,
                               unwind_fde_t *__restrict fde, /* Only non-const for lazy initialized fields! */
                               void const *absolute_pc,
                               unwind_getreg_t reg_getter, void const *reg_getter_arg,
                               unwind_setreg_t reg_setter, void *reg_setter_arg) {
	unsigned int error;
#ifdef LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES
	/* Quick check: If  no capsules were used, then only
	 *              apply the LPA (LandingPadAdjustment) */
	if unlikely(self->cs_has_capsules) {
		error = _unwind_cfa_landing_apply(&self->cs_state, fde, absolute_pc,
		                                  reg_getter, reg_getter_arg,
		                                  reg_setter, reg_setter_arg);
		if unlikely(error != UNWIND_SUCCESS)
			ERRORF(err, "%u\n", error);
	}
#else /* LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES */
	(void)fde;         /* Unused... */
	(void)absolute_pc; /* Unused... */
#endif /* !LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES */
	if (self->cs_lp_adjustment != 0) {
		uintptr_t sp;
		error = (*reg_getter)(reg_getter_arg, CFI_UNWIND_REGISTER_SP(fde->f_addrsize), &sp);
		if unlikely(error != UNWIND_SUCCESS)
			ERRORF(err, "%u\n", error);
		/* Adjust the stack-pointer. */
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
		sp += self->cs_lp_adjustment;
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
		sp -= self->cs_lp_adjustment;
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
		error = (*reg_setter)(reg_setter_arg, CFI_UNWIND_REGISTER_SP(fde->f_addrsize), &sp);
		if unlikely(error != UNWIND_SUCCESS)
			ERRORF(err, "%u\n", error);
	}
	return UNWIND_SUCCESS;
err:
	return error;
}







/* Alias the sigframe variants on-top of the regular ones. */
#ifdef CONFIG_NO_LIBUNWIND_CFA_SIGFRAME_STATE
DEFINE_INTERN_ALIAS(libuw_unwind_fde_sigframe_exec, libuw_unwind_fde_exec);
DEFINE_INTERN_ALIAS(libuw_unwind_cfa_sigframe_apply, libuw_unwind_cfa_apply);
#endif /* CONFIG_NO_LIBUNWIND_CFA_SIGFRAME_STATE */

DEFINE_PUBLIC_ALIAS(unwind_fde_load, libuw_unwind_fde_load);
DEFINE_PUBLIC_ALIAS(unwind_fde_scan, libuw_unwind_fde_scan);
DEFINE_PUBLIC_ALIAS(unwind_fde_exec, libuw_unwind_fde_exec);
DEFINE_PUBLIC_ALIAS(unwind_fde_landing_exec, libuw_unwind_fde_landing_exec);
DEFINE_PUBLIC_ALIAS(unwind_fde_sigframe_exec, libuw_unwind_fde_sigframe_exec);
DEFINE_PUBLIC_ALIAS(unwind_fde_rule, libuw_unwind_fde_rule);
DEFINE_PUBLIC_ALIAS(unwind_fde_exec_cfa, libuw_unwind_fde_exec_cfa);
DEFINE_PUBLIC_ALIAS(unwind_cfa_apply, libuw_unwind_cfa_apply);
DEFINE_PUBLIC_ALIAS(unwind_cfa_landing_apply, libuw_unwind_cfa_landing_apply);
DEFINE_PUBLIC_ALIAS(unwind_cfa_sigframe_apply, libuw_unwind_cfa_sigframe_apply);
DEFINE_PUBLIC_ALIAS(unwind_fde_calculate_cfa, libuw_unwind_fde_calculate_cfa);

DECL_END

#endif /* !GUARD_LIBUNWIND_EH_FRAME_C */
