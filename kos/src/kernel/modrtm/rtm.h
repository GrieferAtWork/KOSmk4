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
#ifndef GUARD_MODRTM_RTM_H
#define GUARD_MODRTM_RTM_H 1

#include <kernel/compiler.h>

#include <kernel/vm/rtm.h>
#include <kernel/types.h>

#ifndef ARCH_VM_HAVE_RTM
#error "Architecture doesn't have RTM support (please don't compile this driver for this architecture)"
#endif /* !ARCH_VM_HAVE_RTM */

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
 * >>         uintptr_t tx_oldver_for_baz;
 * >>         int baz_newval;
 * >>         bool baz_should_set = false;
 * >>         tx_oldver = tx_version_for_baz;
 * >>         COMPILER_BARRIER();
 * >>         if (bar == 7) {
 * >>             baz_should_set = true;
 * >>             baz_newval = 3;
 * >>         }
 * >>         // NOTE: Anything done in here that would be ~too~ complex, such as (trying
 * >>         //       to) do a system call would instead trigger `goto tx_failed'
 * >>         COMPILER_BARRIER();
 * >>         if (!baz_should_set) {
 * >>             // Nothing modified. -> No need to change the version of do any write-back
 * >>             // Must still verify version integrity, though!
 * >>             if (tx_version_for_baz != tx_oldver_for_baz)
 * >>                 continue;
 * >>             break;
 * >>         }
 * >>         while (!sync_trywrite(&tx_lock_for_baz)) {
 * >>             if (tx_version_for_baz != tx_oldver_for_baz)
 * >>                 continue;
 * >>             task_yield();
 * >>         }
 * >>         COMPILER_BARRIER();
 * >>         FINALLY_ENDWRITE(&tx_lock_for_baz);
 * >>         if (tx_version_for_baz != tx_oldver_for_baz)
 * >>             continue;
 * >>         if (baz_should_set) {
 * >>             if (IS_VIO(baz))
 * >>                 goto tx_failed;
 * >>             baz = baz_newval;
 * >>         }
 * >>         ++tx_version_for_baz;
 * >>         break;
 * >>     }
 * >>     if (0) {
 * >> tx_failed:
 * >>         printf("Failed\n");
 * >>     }
 * >> }
 */



/*
 * How the kernel applies RTM memory modifications:
 *
 * >> local accessedDataParts: {vm_datapart: int}; // part -> versionOnFirstAccess
 * >> local modifiedMemory: {(int, Bytes, {vm_datapart...})...};
 * >>
 * >> RETRY:
 * >>
 * >> // Accessed: did perform read or write
 * >> // Modified: did perform write
 * >>
 * >> ...
 * >>
 * >> // Prefault all modified memory locations
 * >>RETRY_FORCEFAULT:
 * >> for (local start, data, none: modifiedMemory) {
 * >>     vm_forcefault(THIS_VM, start, #data,
 * >>                   VM_FORCEFAULT_FLAG_WRITE |
 * >>                   VM_FORCEFAULT_FLAG_NOVIO);
 * >> }
 * >>
 * >> // Acquire tx-locks to all of the modified data parts
 * >> for (local none, none, parts: modifiedMemory) {
 * >>     for (local part: parts)
 * >>         sync_write(&part.tx_lock);
 * >> }
 * >> #define UNLOCK()                                    \
 * >>     for (local none, none, parts: modifiedMemory) { \
 * >>         for (local part: parts)                     \
 * >>             sync_endwrite(&part.tx_lock);           \
 * >>     }
 * >>
 * >> // Verify that none of the accessed parts have been changed
 * >> for (local dataPart, datapartVersionOnFirstAccess: accessedDataParts) {
 * >>     if (dataPart.tx_version != datapartVersionOnFirstAccess) {
 * >>         UNLOCK();
 * >>         goto RETRY;
 * >>     }
 * >> }
 * >>
 * >> // Apply modifications
 * >> for (local addr, data, none: modifiedMemory) {
 * >>     if (memcpy_nopf(addr, data.bytes(), #data) != 0) {
 * >>         UNLOCK();
 * >>         goto RETRY_FORCEFAULT;
 * >>     }
 * >> }
 * >> 
 * >> for (local none, none, parts: modifiedMemory) {
 * >>     for (local part: parts) {
 * >>         ATOMIC_FETCHINC(part.tx_version);
 * >>         sync_endwrite(&part.tx_lock);
 * >>     }
 * >> }
 */

DATDEF struct vm_rtm_driver_hooks rtm_hooks;

DECL_END

#endif /* !GUARD_MODRTM_RTM_H */
