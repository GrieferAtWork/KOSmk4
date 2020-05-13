/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.remove("-O3"))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_DEBUGGER_C
#define GUARD_KERNEL_SRC_MEMORY_VM_DEBUGGER_C 1
#define DISABLE_BRANCH_PROFILING 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_DEBUGGER
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <fs/node.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/vm.h>

#include <kos/dev.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>

DECL_BEGIN

PRIVATE ATTR_DBGRODATA char const lsvm_str_kernel[] = "kernel";
PRIVATE ATTR_DBGRODATA char const lsvm_str_user[] = "user";

DBG_AUTOCOMPLETE(lsvm,
                 /*size_t*/ argc, /*char **/ argv /*[]*/,
                 /*dbg_autocomplete_cb_t*/ cb, /*void **/arg) {
	(void)argv;
	if (argc == 1) {
		(*cb)(arg, lsvm_str_kernel, COMPILER_STRLEN(lsvm_str_kernel));
		(*cb)(arg, lsvm_str_user, COMPILER_STRLEN(lsvm_str_user));
	}
}

DBG_COMMAND_AUTO(lsvm, DBG_HOOKFLAG_NORMAL,
                 "lsvm [NAME=kernel|user] [MINADDR=0] [MAXADDR=...]\n"
                 "\tList all VM mappings with the given VM. " DF_WHITE("NAME") " must be done of " DF_WHITE("kern")
                    ", " DF_WHITE("user") " or the hex-base address of a " DF_BLUE("struct vm") "\n"
                 "Nodes are enumerated as:\n\n"
                 "Min      Max       Prot  NodeF.   PartF. State     Target Min      Max \n"
                 "003BC000-003BCFFF [rwxs] [p---Mk] [---k] locked -> anonR @003BC000-003BCFFF\n"
                 "Prot:\n"
                 "\t" DF_WHITE("r") " Mapped as readable\n"
                 "\t" DF_WHITE("w") " Mapped as writable\n"
                 "\t" DF_WHITE("x") " Mapped as executable\n"
                 "\t" DF_WHITE("s") " Mapped as shared\n"
                 "NodeF.: (Node flags)\n"
                 "\t" DF_WHITE("p") " The page directory mapping has been prepared\n"
                 "\t" DF_WHITE("P") " The node has been partitioned (split)\n"
                 "\t" DF_WHITE("G") " The node grows up (affects the direction of guard expansion)\n"
                 "\t" DF_WHITE("h") " The node is hinted by the page directory\n"
                 "\t" DF_WHITE("M") " The node should not be merged with other nodes\n"
                 "\t" DF_WHITE("k") " The node is an intrinsic kernel mapping that cannot be unmapped normally\n"
                 "PartF.: (Data part flags)\n"
                 "\t" DF_WHITE("l") " The part will become locked once loaded into the core\n"
                 "\t" DF_WHITE("c") " The contents of the part have changed\n"
                 "\t" DF_WHITE("t") " Changes to the contents of the part are tracked\n"
                 "\t" DF_WHITE("k") " The part is an intrinsic kernel component that cannot be deleted normally\n",
                 argc, argv) {
	struct vm *v = &vm_kernel;
	struct vm_node *iter;
	void *minaddr = (void *)0;
	void *maxaddr = (void *)-1;
	--argc;
	++argv;
	if (argc) {
		if (strcmp(argv[0], lsvm_str_kernel) == 0)
			;
		else if (strcmp(argv[0], lsvm_str_user) == 0)
			v = dbg_current->t_vm;
		else if (!sscanf(argv[0], DBGSTR("%p"), &v))
			return DBG_STATUS_INVALID_ARGUMENTS;
		--argc, ++argv;
	}
	if (argc) {
		if (!sscanf(argv[0], DBGSTR("%p"), &minaddr))
			return DBG_STATUS_INVALID_ARGUMENTS;
		--argc, ++argv;
		maxaddr = minaddr;
	}
	if (argc) {
		if (!sscanf(argv[0], DBGSTR("%p"), &maxaddr))
			return DBG_STATUS_INVALID_ARGUMENTS;
		--argc, ++argv;
	}

	for (iter = v->v_byaddr; iter != NULL;
	     iter = iter->vn_byaddr.ln_next) {
		struct vm_datapart *part;
		struct vm_datablock *block;
		char const *state_name;
		if (vm_node_getmax(iter) < minaddr)
			continue;
		if (vm_node_getmin(iter) > maxaddr)
			break;
		part = iter->vn_part;
		if (!part) {
			dbg_printf(DBGSTR("%p-%p [%c%c%c%c] [%c%c%c%c%c%c] reserved\n"),
			           vm_node_getmin(iter),
			           vm_node_getmax(iter),
			           (iter->vn_prot & VM_PROT_READ) ? 'r' : '-',
			           (iter->vn_prot & VM_PROT_WRITE) ? 'w' : '-',
			           (iter->vn_prot & VM_PROT_EXEC) ? 'x' : '-',
			           (iter->vn_prot & VM_PROT_SHARED) ? 's' : '-',
			           (iter->vn_flags & VM_NODE_FLAG_PREPARED) ? 'p' : '-',
			           (iter->vn_flags & VM_NODE_FLAG_PARTITIONED) ? 'P' : '-',
			           (iter->vn_flags & VM_NODE_FLAG_GROWSUP) ? 'G' : '-',
			           (iter->vn_flags & VM_NODE_FLAG_HINTED) ? 'h' : '-',
			           (iter->vn_flags & VM_NODE_FLAG_NOMERGE) ? 'M' : '-',
			           (iter->vn_flags & VM_NODE_FLAG_KERNPRT) ? 'k' : '-');
			continue;
		}
		block = iter->vn_block;
		dbg_printf(DBGSTR("%p-%p [%c%c%c%c] [%c%c%c%c%c%c] [%c%c%c%c] "),
		           vm_node_getmin(iter),
		           vm_node_getmax(iter),
		           (iter->vn_prot & VM_PROT_READ) ? 'r' : '-',
		           (iter->vn_prot & VM_PROT_WRITE) ? 'w' : '-',
		           (iter->vn_prot & VM_PROT_EXEC) ? 'x' : '-',
		           (iter->vn_prot & VM_PROT_SHARED) ? 's' : '-',
		           (iter->vn_flags & VM_NODE_FLAG_PREPARED) ? 'p' : '-',
		           (iter->vn_flags & VM_NODE_FLAG_PARTITIONED) ? 'P' : '-',
		           (iter->vn_flags & VM_NODE_FLAG_GROWSUP) ? 'G' : '-',
		           (iter->vn_flags & VM_NODE_FLAG_HINTED) ? 'h' : '-',
		           (iter->vn_flags & VM_NODE_FLAG_NOMERGE) ? 'M' : '-',
		           (iter->vn_flags & VM_NODE_FLAG_KERNPRT) ? 'k' : '-',
		           (part->dp_flags & VM_DATAPART_FLAG_LOCKED) ? 'l' : '-',
		           (part->dp_flags & VM_DATAPART_FLAG_CHANGED) ? 'c' : '-',
		           (part->dp_flags & VM_DATAPART_FLAG_TRKCHNG) ? 't' : '-',
		           (part->dp_flags & VM_DATAPART_FLAG_KERNPRT) ? 'k' : '-');
		switch (part->dp_state) {
		case VM_DATAPART_STATE_ABSENT: state_name = DBGSTR("absent"); break;
		case VM_DATAPART_STATE_INCORE: state_name = DBGSTR("incore"); break;
		case VM_DATAPART_STATE_LOCKED: state_name = DBGSTR("locked"); break;
#ifdef VM_DATAPART_STATE_INSWAP
		case VM_DATAPART_STATE_INSWAP: state_name = DBGSTR("inswap"); break;
#endif /* VM_DATAPART_STATE_INSWAP */
#ifdef VM_DATAPART_STATE_VIOPRT
		case VM_DATAPART_STATE_VIOPRT: state_name = DBGSTR("vioprt"); break;
#endif /* VM_DATAPART_STATE_VIOPRT */
		default: state_name = NULL; break;
		}
		if (state_name) {
			dbg_print(state_name);
		} else {
			dbg_printf(DBGSTR(DF_COLOR(DBG_COLOR_LIGHT_GRAY, DBG_COLOR_MAROON, "UNKNOWN_STATE:%u")),
			           part->dp_state);
		}
		if (vm_datablock_isinode(block)) {
			struct superblock *super = ((struct inode *)block)->i_super;
			dbg_printf(DBGSTR("\n\t-> "
			                  "%s-inode[%.2x:%.2x,%#I64x]"),
			           super->s_type->st_name,
			           MAJOR(block_device_devno(super->s_device)),
			           MINOR(block_device_devno(super->s_device)),
			           (u64)((struct inode *)block)->i_fileino);
			goto do_print_part_position;
		} else if (block->db_type == &vm_datablock_anonymous_type) {
			dbg_print(DBGSTR(" -> anonR"));
		} else if (block->db_type == &vm_datablock_anonymous_zero_type) {
			dbg_print(DBGSTR(" -> anonZ"));
		} else if (block->db_type == &vm_datablock_debugheap_type) {
			dbg_print(DBGSTR(" -> dheap"));
		} else {
			dbg_printf(DBGSTR(" -> db:%p"), block);
do_print_part_position:
			dbg_printf(DBGSTR("@%I64x-%I64x"),
			           (u64)vm_datapart_minbyte(part),
			           (u64)vm_datapart_maxbyte(part));
		}
		switch (part->dp_state) {

		case VM_DATAPART_STATE_INCORE:
		case VM_DATAPART_STATE_LOCKED:
			if (part->dp_ramdata.rd_blockv == &part->dp_ramdata.rd_block0) {
				vm_phys_t maxphys;
				maxphys = page2addr(part->dp_ramdata.rd_block0.rb_start +
				                    part->dp_ramdata.rd_block0.rb_size) -
				          1;
#if __SIZEOF_VM_PHYS_T__ > __SIZEOF_POINTER__
				if (maxphys > (vm_phys_t)UINTPTR_MAX) {
					dbg_printf(DBGSTR(" @%I64p-%I64p\n"),
					           (u64)page2addr(part->dp_ramdata.rd_block0.rb_start),
					           (u64)maxphys);
				} else
#endif /* __SIZEOF_VM_PHYS_T__ > __SIZEOF_POINTER__ */
				{
					dbg_printf(DBGSTR(" @%p-%p\n"),
					           (uintptr_t)page2addr(part->dp_ramdata.rd_block0.rb_start),
					           maxphys);
				}
			} else {
				size_t i;
				dbg_putc('\n');
				for (i = 0; i < part->dp_ramdata.rd_blockc; ++i) {
					struct vm_ramblock *b;
					b = &part->dp_ramdata.rd_blockv[i];
					dbg_printf(DBGSTR("\tphys:%I64p-%I64p (%Iu pages)\n"),
					           (u64)page2addr(b->rb_start),
					           (u64)page2addr(b->rb_start + b->rb_size) - 1,
					           (size_t)b->rb_size);
				}
			}
			break;

		default:
			dbg_putc('\n');
			break;
		}
	}
	return 0;
}


PRIVATE ATTR_DBGRODATA char const aslr_str_0[] = "0";
PRIVATE ATTR_DBGRODATA char const aslr_str_1[] = "1";

DBG_AUTOCOMPLETE(aslr,
                 /*size_t*/ argc, /*char **/ argv /*[]*/,
                 /*dbg_autocomplete_cb_t*/ cb, /*void **/arg) {
	(void)argv;
	if (argc == 1) {
		(*cb)(arg, aslr_str_0, COMPILER_STRLEN(aslr_str_0));
		(*cb)(arg, aslr_str_1, COMPILER_STRLEN(aslr_str_1));
	}
}

DBG_COMMAND_AUTO(aslr, DBG_COMMANDHOOK_FLAG_AUTOEXCLUSIVE,
                 "aslr [0|1]\n"
                 "\tView or enable/disable AddressSpaceLayoutRandomization\n",
                 argc, argv) {
	bool enabled;
	if (argc == 1) {
		enabled = !vm_get_aslr_disabled();
		dbg_print(enabled ? DBGSTR("enabled\n") : DBGSTR("disabled\n"));
		return enabled ? 0 : 1;
	}
	if (argc != 2)
		return DBG_STATUS_INVALID_ARGUMENTS;
	if (strcmp(argv[1], aslr_str_1) == 0) {
		enabled = true;
	} else if (strcmp(argv[1], aslr_str_0) == 0) {
		enabled = false;
	} else {
		return DBG_STATUS_INVALID_ARGUMENTS;
	}
	vm_set_aslr_disabled(!enabled);
	return 0;
}

DECL_END

#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_DEBUGGER_C */
