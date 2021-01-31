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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VM_EXEC_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VM_EXEC_H 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_VM
#include <kernel/mman/mm-execinfo.h>
#define vm_execinfo_struct mexecinfo
#define ei_node            mei_node
#define ei_dent            mei_dent
#define ei_path            mei_path
#define thisvm_execinfo    thismman_execinfo
#else /* CONFIG_USE_NEW_VM */
#include <kernel/types.h>
#include <kernel/vm.h>

#define mexecinfo         vm_execinfo_struct
#define mei_node          ei_node
#define mei_dent          ei_dent
#define mei_path          ei_path
#define thismman_execinfo thisvm_execinfo

DECL_BEGIN

struct inode;
struct directory_entry;
struct path;

struct vm_execinfo_struct {
	REF struct inode           *ei_node; /* [0..1][lock(:THIS_MMAN)] Exec INode */
	REF struct directory_entry *ei_dent; /* [0..1][lock(:THIS_MMAN)] Exec directory entry */
	REF struct path            *ei_path; /* [0..1][lock(:THIS_MMAN)] Exec path */
};

/* VM exec() information */
DATDEF ATTR_PERMMAN struct vm_execinfo_struct thisvm_execinfo;

DECL_END
#endif /* !CONFIG_USE_NEW_VM */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VM_EXEC_H */
