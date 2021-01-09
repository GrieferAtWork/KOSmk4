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
#ifndef GUARD_MODRTM_RTM_H
#define GUARD_MODRTM_RTM_H 1

#include <kernel/compiler.h>

#include <kernel/vm/rtm.h>
#include <kernel/types.h>

#ifndef ARCH_VM_HAVE_RTM
#error "Architecture doesn't have RTM support (please don't compile this driver for this architecture)"
#endif /* !ARCH_VM_HAVE_RTM */

/* Config option: CONFIG_RTM_USERSPACE_ONLY
 * When enabled, RTM can only be used in user-space.
 * This is enforced by making all conditional is-user checks mandatory,
 * as well as simplifying a lot of code by removing is-kernel branches. */
#ifdef CONFIG_NO_RTM_USERSPACE_ONLY
#undef CONFIG_RTM_USERSPACE_ONLY
#define CONFIG_RTM_USERSPACE_ONLY 0
#elif !defined(CONFIG_RTM_USERSPACE_ONLY)
#define CONFIG_RTM_USERSPACE_ONLY 1
#elif (CONFIG_RTM_USERSPACE_ONLY + 0) == 0
#undef CONFIG_RTM_USERSPACE_ONLY
#define CONFIG_RTM_USERSPACE_ONLY 0
#else /* ... */
#undef CONFIG_RTM_USERSPACE_ONLY
#define CONFIG_RTM_USERSPACE_ONLY 1
#endif /* !... */


/* Config option: CONFIG_RTM_PENDING_SYSTEM_CALLS
 * When enabled, certain system calls will be tracked as pending,
 * such that they will be executed only upon successful completion
 * of RTM emulation. */
#ifdef CONFIG_NO_RTM_PENDING_SYSTEM_CALLS
#undef CONFIG_RTM_PENDING_SYSTEM_CALLS
#define CONFIG_RTM_PENDING_SYSTEM_CALLS 0
#elif !defined(CONFIG_RTM_PENDING_SYSTEM_CALLS)
#define CONFIG_RTM_PENDING_SYSTEM_CALLS 1
#elif (CONFIG_RTM_PENDING_SYSTEM_CALLS + 0) == 0
#undef CONFIG_RTM_PENDING_SYSTEM_CALLS
#define CONFIG_RTM_PENDING_SYSTEM_CALLS 0
#else /* ... */
#undef CONFIG_RTM_PENDING_SYSTEM_CALLS
#define CONFIG_RTM_PENDING_SYSTEM_CALLS 1
#endif /* !... */


DECL_BEGIN

/* Reminder on how transactional memory works:
 * >> extern int bar, baz;
 * >> void foo() {
 * >>     if (!transaction_atomic({
 * >>         if (bar == 7)
 * >>             baz = 3;
 * >>     })) {
 * >>         printf("Failed\n");
 * >>     }
 * >> }
 *
 * Behavior:
 * >> extern int bar, baz;
 * >> void foo() {
 * >>     for (;;) {
 * >>         uintptr_t tx_oldver_for_bar;
 * >>         int baz_newval;
 * >>         bool baz_should_set = false;
 * >>
 * >>         COMPILER_BARRIER();
 * >>         // NOTE: Anything done in here that would be ~too~ complex, such as (trying
 * >>         //       to) do a system call would instead trigger `goto tx_failed'
 * >>         //       If too much memory is accessed here, `RTM_ABORT_CAPACITY' would be returned.
 * >>         if (IS_VIO(bar))
 * >>             goto tx_failed; // VIO is _not_ allowed!
 * >>         tx_oldver_for_bar = tx_version_for_bar;
 * >>         if (bar == 7) {
 * >>             baz_should_set = true;
 * >>             baz_newval = 3;
 * >>         }
 * >>         COMPILER_BARRIER();
 * >>
 * >>         ACQUIRE_LOCK_READ(tx_lock_for_bar);
 * >>         if (tx_version_for_bar != tx_oldver_for_bar) {
 * >>             RELEASE_LOCK_READ(tx_lock_for_bar);
 * >>             continue; // Actually done by returning `RTM_ABORT_RETRY'
 * >>         }
 * >>         RELEASE_LOCK_READ(tx_lock_for_bar);
 * >>         if (baz_should_set) {
 * >>             ACQUIRE_LOCK_WRITE(tx_lock_for_baz);
 * >>             if (IS_VIO(baz)) {
 * >>                 RELEASE_LOCK_WRITE(tx_lock_for_baz);
 * >>                 goto tx_failed; // VIO is _not_ allowed!
 * >>             }
 * >>             baz = baz_newval;
 * >>             ++tx_version_for_baz;
 * >>             RELEASE_LOCK_WRITE(tx_lock_for_baz);
 * >>         }
 * >>         break;
 * >>     }
 * >>     if (0) {
 * >> tx_failed:
 * >>          // Actually done by returning `RTM_ABORT_FAILED'
 * >>         printf("Failed\n");
 * >>     }
 * >> }
 */



/*
 * How the kernel applies RTM memory modifications:
 *
 * >> @@Tuples of (addr, data, changed, version, part)
 * >> local accessedParts: {(int, Bytes, bool, int, vm_datapart)...};
 * >>
 * >> RETRY:
 * >>
 * >> // Accessed: did perform read or write (changed == true OR changed == false)
 * >> // Modified: did perform write         (changed == true)
 * >>
 * >> ...
 * >>
 * >>RETRY_FORCEFAULT:
 * >> // Prefault all modified memory locations
 * >> for (local start, data, changed, none, none: accessedParts) {
 * >>     if (changed) {
 * >>         vm_forcefault(THIS_VM, start, #data,
 * >>                       VM_FORCEFAULT_FLAG_WRITE |
 * >>                       VM_FORCEFAULT_FLAG_NOVIO);
 * >>     }
 * >> }
 * >>
 * >> // Acquire tx-locks to all of the modified data parts, and
 * >> // verify that accessed data parts are still up-to-date
 * >> for (local addr, data, changed, version, part: accessedParts) {
 * >>     if (VM_NODE_AT(min: addr, max: addr + #data - 1)->vn_part != part)
 * >>         goto RETRY;
 * >>     if (changed) {
 * >>         sync_write(part);
 * >>         if (part->dp_futex->fc_rtm_vers != version)
 * >>             goto RETRY;
 * >>     } else {
 * >>         // Have to acquire a read-lock to ensure that parts
 * >>         // that were only read aren't being modified right
 * >>         // now by another RTM context.
 * >>         sync_read(part);
 * >>         if (part->dp_futex->fc_rtm_vers != version)
 * >>             goto RETRY;
 * >>         sync_endread(part);
 * >>     }
 * >> }
 * >>
 * >> // Verify that all modified memory is still writable.
 * >> // We're currently holding write-locks to the backing vm_datapart-s
 * >> // of all areas of interest, so we know that whatever their state is
 * >> // right now, that state won't change until we release them. We also
 * >> // know that (due to our `vm_forcefault()' above), all modified parts
 * >> // had been made to be writable at one point in the past, so all we
 * >> // have to do is assert that they still are writable, and start over
 * >> // if we're too late, and they no longer are.
 * >> for (local addr, data, changed, none, none: accessedParts) {
 * >>     if (changed) {
 * >>         if (!VERIFY_WRITABLE(addr, #data))
 * >>             goto RETRY_FORCEFAULT;
 * >>     }
 * >> }
 * >>
 * >> // Apply modifications
 * >> for (local addr, data, changed, none, none: accessedParts) {
 * >>     if (changed) {
 * >>         size_t error;
 * >>         error = memcpy_nopf(addr, data.bytes(), #data);
 * >>         assert(error == 0); // We asserted this above!
 * >>         ++part->dp_futex->fc_rtm_vers;
 * >>         sync_endwrite(part);
 * >>     }
 * >> }
 */

INTDEF struct vm_rtm_driver_hooks rtm_hooks;

DECL_END

#endif /* !GUARD_MODRTM_RTM_H */
