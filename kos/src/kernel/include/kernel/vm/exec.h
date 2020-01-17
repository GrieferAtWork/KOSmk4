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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VM_EXEC_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VM_EXEC_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <kernel/vm.h>

DECL_BEGIN

struct inode;
struct directory_entry;
struct path;

struct vm_execinfo_struct {
	REF struct inode           *ei_node; /* [0..1][lock(:THIS_VM)] Exec INode */
	REF struct directory_entry *ei_dent; /* [0..1][lock(:THIS_VM)] Exec directory entry */
	REF struct path            *ei_path; /* [0..1][lock(:THIS_VM)] Exec path */
};

/* VM exec() information */
DATDEF ATTR_PERVM struct vm_execinfo_struct thisvm_execinfo;


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VM_EXEC_H */
