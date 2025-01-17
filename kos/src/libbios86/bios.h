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
#ifndef GUARD_LIBBIOS86_BIOS_H
#define GUARD_LIBBIOS86_BIOS_H 1

#include "api.h"
/**/

#include <stdbool.h>

#include <libbios86/bios.h>

#ifdef __KERNEL__
#include <debugger/config.h>
#endif /* __KERNEL__ */

DECL_BEGIN

/* >> bios86_init(3)
 * Initialize a BIOS interrupt emulator `self'
 * @return:  0: Success.
 * @return: -1: Failed to initialize (s.a. `errno'). */
#ifdef __KERNEL__
INTDEF NONNULL((1)) void CC
libbios86_init(struct bios86 *__restrict self);
#else /* __KERNEL__ */
INTDEF WUNUSED NONNULL((1)) int
NOTHROW(CC libbios86_init)(struct bios86 *__restrict self);
#endif /* !__KERNEL__ */

/* >> bios86_fini(3)
 * Finalize the BIOS buffer interface. */
INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(CC libbios86_fini)(struct bios86 *__restrict self);

/* >> bios86_emulator_init(3)
 * Same as `bios86_init(3)', but also set-up a vm86 emulator
 * that uses the pointed-to memory region, as well as  makes
 * use of native I/O instructions.
 * @return:  0: Success.
 * @return: -1: Failed to initialize (s.a. `errno'). */
#ifdef __KERNEL__
INTDEF NONNULL((1)) void CC
libbios86_emulator_init(struct bios86_emulator *__restrict self);
#else /* __KERNEL__ */
INTDEF WUNUSED NONNULL((1)) int
NOTHROW(CC libbios86_emulator_init)(struct bios86_emulator *__restrict self);
#endif /* !__KERNEL__ */

/* >> bios86_emulator_fini(3)
 * Finalize the BIOS buffer interface. */
INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(CC libbios86_emulator_fini)(struct bios86_emulator *__restrict self);


/* >> bios86_emulator_int(3)
 * Do an interrupt.
 * The caller must initialize `self->b86e_vm.vr_regs.*',
 * with the  exception of  `ESP', `SS',  `EIP' and  `CS'
 *
 * @return: true:  Success.
 * @return: false: Interrupt failed (illegal instruction / bad I/O, etc...) */
INTDEF WUNUSED NONNULL((1)) bool CC
libbios86_emulator_int(struct bios86_emulator *__restrict self,
                       uint8_t intno);



#ifdef __KERNEL__
/* Same as  above,  but  must be  used  if  `dbg_onstack()'
 * Also note that `bios86_init()' becomes  NOBLOCK+NOTHROW,
 * but may return `-1' if insufficient memory is available. */
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
INTDEF NOBLOCK WUNUSED NONNULL((1)) int
NOTHROW(CC libbios86_init_for_debugger)(struct bios86_for_debugger *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(CC libbios86_fini_for_debugger)(struct bios86_for_debugger *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) int
NOTHROW(CC libbios86_emulator_init_for_debugger)(struct bios86_emulator_for_debugger *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(CC libbios86_emulator_fini_for_debugger)(struct bios86_emulator_for_debugger *__restrict self);
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
#endif /* __KERNEL__ */

DECL_END

#endif /* !GUARD_LIBBIOS86_BIOS_H */
