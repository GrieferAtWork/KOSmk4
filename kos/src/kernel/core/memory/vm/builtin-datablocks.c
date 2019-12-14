/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_BUILTIN_DATABLOCKS_C
#define GUARD_KERNEL_SRC_MEMORY_VM_BUILTIN_DATABLOCKS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/printk.h>
#include <kernel/vm.h>

#include <string.h>


/*[[[deemon
local max_n = 32;
function print_ent(n) {
	print "#define DATAPAGE_SHIFT",n;
	print "#include \"vm-builtin-datablocks-zero.c.inl\"";
}
print_ent(0);
local max_n = 32;
for (local n: [1:max_n]) {
	print "#if PAGESHIFT >=",n;
	print_ent(n);
}
for (local n: [max_n - 1:0,-1]) {
	print "#endif /" "* PAGESHIFT >=",n,"*" "/";
}
]]]*/
#define DATAPAGE_SHIFT 0
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 1
#define DATAPAGE_SHIFT 1
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 2
#define DATAPAGE_SHIFT 2
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 3
#define DATAPAGE_SHIFT 3
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 4
#define DATAPAGE_SHIFT 4
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 5
#define DATAPAGE_SHIFT 5
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 6
#define DATAPAGE_SHIFT 6
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 7
#define DATAPAGE_SHIFT 7
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 8
#define DATAPAGE_SHIFT 8
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 9
#define DATAPAGE_SHIFT 9
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 10
#define DATAPAGE_SHIFT 10
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 11
#define DATAPAGE_SHIFT 11
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 12
#define DATAPAGE_SHIFT 12
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 13
#define DATAPAGE_SHIFT 13
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 14
#define DATAPAGE_SHIFT 14
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 15
#define DATAPAGE_SHIFT 15
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 16
#define DATAPAGE_SHIFT 16
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 17
#define DATAPAGE_SHIFT 17
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 18
#define DATAPAGE_SHIFT 18
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 19
#define DATAPAGE_SHIFT 19
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 20
#define DATAPAGE_SHIFT 20
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 21
#define DATAPAGE_SHIFT 21
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 22
#define DATAPAGE_SHIFT 22
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 23
#define DATAPAGE_SHIFT 23
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 24
#define DATAPAGE_SHIFT 24
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 25
#define DATAPAGE_SHIFT 25
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 26
#define DATAPAGE_SHIFT 26
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 27
#define DATAPAGE_SHIFT 27
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 28
#define DATAPAGE_SHIFT 28
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 29
#define DATAPAGE_SHIFT 29
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 30
#define DATAPAGE_SHIFT 30
#include "vm-builtin-datablocks-zero.c.inl"
#if PAGESHIFT >= 31
#define DATAPAGE_SHIFT 31
#include "vm-builtin-datablocks-zero.c.inl"
#endif /* PAGESHIFT >= 31 */
#endif /* PAGESHIFT >= 30 */
#endif /* PAGESHIFT >= 29 */
#endif /* PAGESHIFT >= 28 */
#endif /* PAGESHIFT >= 27 */
#endif /* PAGESHIFT >= 26 */
#endif /* PAGESHIFT >= 25 */
#endif /* PAGESHIFT >= 24 */
#endif /* PAGESHIFT >= 23 */
#endif /* PAGESHIFT >= 22 */
#endif /* PAGESHIFT >= 21 */
#endif /* PAGESHIFT >= 20 */
#endif /* PAGESHIFT >= 19 */
#endif /* PAGESHIFT >= 18 */
#endif /* PAGESHIFT >= 17 */
#endif /* PAGESHIFT >= 16 */
#endif /* PAGESHIFT >= 15 */
#endif /* PAGESHIFT >= 14 */
#endif /* PAGESHIFT >= 13 */
#endif /* PAGESHIFT >= 12 */
#endif /* PAGESHIFT >= 11 */
#endif /* PAGESHIFT >= 10 */
#endif /* PAGESHIFT >= 9 */
#endif /* PAGESHIFT >= 8 */
#endif /* PAGESHIFT >= 7 */
#endif /* PAGESHIFT >= 6 */
#endif /* PAGESHIFT >= 5 */
#endif /* PAGESHIFT >= 4 */
#endif /* PAGESHIFT >= 3 */
#endif /* PAGESHIFT >= 2 */
#endif /* PAGESHIFT >= 1 */
//[[[end]]]



DECL_BEGIN

/* Builtin data blocks */
PUBLIC struct vm_datablock_type vm_datablock_anonymous_type = {
	/* .dt_destroy  = */ NULL,
	/* .dt_initpart = */ NULL,
	/* .dt_loadpart = */ NULL,
	/* .dt_savepart = */ NULL,
	/* .dt_changed  = */ NULL
};
PUBLIC struct vm_datablock vm_datablock_anonymous = {
	/* .db_refcnt = */ ((refcnt_t)-1)/2, /* Very high reference counter, because
	                                     * used by _a_ _lot_ of static structures! */
	/* .db_lock   = */ RWLOCK_INIT,
	/* .db_type   = */ &vm_datablock_anonymous_type,
#ifdef CONFIG_VIO
	/* .db_vio    = */ NULL,
#endif
	/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
	VM_DATABLOCK_INIT_PAGEINFO(0)
};



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datablock_physical_initpart)(struct vm_datapart *__restrict self) {
	self->dp_state = VM_DATAPART_STATE_LOCKED;
	self->dp_flags |= (VM_DATAPART_FLAG_LOCKED | VM_DATAPART_FLAG_KEEPRAM);
	self->dp_ramdata.rd_blockv          = &self->dp_ramdata.rd_block0;
	self->dp_ramdata.rd_block0.rb_start = (pageptr_t)self->dp_tree.a_vmin;
	self->dp_ramdata.rd_block0.rb_size  = (size_t)(self->dp_tree.a_vmax - self->dp_tree.a_vmin) + 1;
}


PUBLIC struct vm_datablock_type vm_datablock_physical_type = {
	/* .dt_destroy  = */ NULL,
	/* .dt_initpart = */ &vm_datablock_physical_initpart,
	/* .dt_loadpart = */ NULL,
	/* .dt_savepart = */ NULL,
	/* .dt_changed  = */ NULL
};

PUBLIC struct vm_datablock vm_datablock_physical = {
	/* .db_refcnt = */ ((refcnt_t)-1)/2, /* Very high reference counter, because
	                                     * used by some static structures! */
	/* .db_lock   = */ RWLOCK_INIT,
	/* .db_type   = */ &vm_datablock_physical_type,
#ifdef CONFIG_VIO
	/* .db_vio    = */ NULL,
#endif
	/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT, /* No need to track page properties here... */
	VM_DATABLOCK_INIT_PAGEINFO(0)
};


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_ramfile_initpart)(struct vm_datapart *__restrict self) {
	struct vm_ramfile *file;
	assert(self->dp_state == VM_DATAPART_STATE_ABSENT);
	file = (struct vm_ramfile *)self->dp_block;
	if (self->dp_tree.a_vmax < (datapage_t)file->rf_data.rb_size) {
		self->dp_state = VM_DATAPART_STATE_LOCKED;
		self->dp_flags |= (VM_DATAPART_FLAG_LOCKED | VM_DATAPART_FLAG_KEEPRAM);
		self->dp_ramdata.rd_blockv          = &self->dp_ramdata.rd_block0;
		self->dp_ramdata.rd_block0.rb_start = file->rf_data.rb_start + (pageptr_t)self->dp_tree.a_vmin;
		self->dp_ramdata.rd_block0.rb_size  = (size_t)(self->dp_tree.a_vmax - self->dp_tree.a_vmin) + 1;
	}
}

PUBLIC struct vm_datablock_type vm_ramfile_type = {
	/* .dt_destroy  = */ NULL,
	/* .dt_initpart = */ &vm_ramfile_initpart,
	/* .dt_loadpart = */ NULL,
	/* .dt_savepart = */ NULL,
	/* .dt_changed  = */ NULL
};



/* Define symbol aliases */
DEFINE_PUBLIC_WEAK_ALIAS(vm_datablock_debugheap, vm_datablock_anonymous);
DEFINE_PUBLIC_WEAK_ALIAS(vm_datablock_debugheap_type, vm_datablock_anonymous_type);
DEFINE_PUBLIC_ALIAS(vm_datablock_anonymous_zero, vm_datablock_anonymous_zero_vec);
DEFINE_PUBLIC_ALIAS(vm_datablock_anonymous_zero_type, vm_datablock_anonymous_zero_type_vec);


PUBLIC struct vm_datablock_type
vm_datablock_anonymous_zero_type_vec[PAGESHIFT + 1] = {
/*[[[deemon
function print_ent(n) {
	print "\t{\t/" "* .dt_destroy  = *" "/ NULL,";
	print "\t\t/" "* .dt_initpart = *" "/ NULL,";
	print "\t\t/" "* .dt_loadpart = *" "/ &anon_zero_loadpart" + n + ",";
	print "\t\t/" "* .dt_savepart = *" "/ NULL,";
	print "\t\t/" "* .dt_changed  = *" "/ NULL";
	print "\t}";
}
print_ent(0);
local max_n = 32;
for (local n: [1:max_n]) {
	print "#if PAGESHIFT >=",n;
	print "\t,";
	print_ent(n);
}
for (local n: [max_n - 1:0,-1]) {
	print "#endif /" "* PAGESHIFT >=",n,"*" "/";
}
]]]*/
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart0,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 1
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart1,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 2
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart2,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 3
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart3,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 4
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart4,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 5
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart5,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 6
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart6,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 7
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart7,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 8
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart8,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 9
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart9,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 10
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart10,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 11
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart11,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 12
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart12,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 13
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart13,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 14
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart14,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 15
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart15,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 16
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart16,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 17
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart17,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 18
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart18,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 19
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart19,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 20
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart20,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 21
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart21,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 22
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart22,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 23
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart23,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 24
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart24,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 25
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart25,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 26
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart26,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 27
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart27,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 28
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart28,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 29
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart29,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 30
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart30,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#if PAGESHIFT >= 31
	,
	{	/* .dt_destroy  = */ NULL,
		/* .dt_initpart = */ NULL,
		/* .dt_loadpart = */ &anon_zero_loadpart31,
		/* .dt_savepart = */ NULL,
		/* .dt_changed  = */ NULL
	}
#endif /* PAGESHIFT >= 31 */
#endif /* PAGESHIFT >= 30 */
#endif /* PAGESHIFT >= 29 */
#endif /* PAGESHIFT >= 28 */
#endif /* PAGESHIFT >= 27 */
#endif /* PAGESHIFT >= 26 */
#endif /* PAGESHIFT >= 25 */
#endif /* PAGESHIFT >= 24 */
#endif /* PAGESHIFT >= 23 */
#endif /* PAGESHIFT >= 22 */
#endif /* PAGESHIFT >= 21 */
#endif /* PAGESHIFT >= 20 */
#endif /* PAGESHIFT >= 19 */
#endif /* PAGESHIFT >= 18 */
#endif /* PAGESHIFT >= 17 */
#endif /* PAGESHIFT >= 16 */
#endif /* PAGESHIFT >= 15 */
#endif /* PAGESHIFT >= 14 */
#endif /* PAGESHIFT >= 13 */
#endif /* PAGESHIFT >= 12 */
#endif /* PAGESHIFT >= 11 */
#endif /* PAGESHIFT >= 10 */
#endif /* PAGESHIFT >= 9 */
#endif /* PAGESHIFT >= 8 */
#endif /* PAGESHIFT >= 7 */
#endif /* PAGESHIFT >= 6 */
#endif /* PAGESHIFT >= 5 */
#endif /* PAGESHIFT >= 4 */
#endif /* PAGESHIFT >= 3 */
#endif /* PAGESHIFT >= 2 */
#endif /* PAGESHIFT >= 1 */
//[[[end]]]
};

PUBLIC struct vm_datablock vm_datablock_anonymous_zero_vec[PAGESHIFT + 1] = {
/*[[[deemon
function print_ent(n) {
	print "\t{\t/" "* .db_refcnt = *" "/ ((refcnt_t)-1)/2,";
	print "\t\t/" "* .db_lock   = *" "/ RWLOCK_INIT,";
	print "\t\t/" "* .db_type   = *" "/ &vm_datablock_anonymous_zero_type_vec[" + n + "],";
	print "#ifdef CONFIG_VIO";
	print "\t\t/" "* .db_vio    = *" "/ NULL,";
	print "#endif";
	print "\t\t/" "* .db_parts  = *" "/ VM_DATABLOCK_ANONPARTS_INIT,";
	print "\t\tVM_DATABLOCK_INIT_PAGEINFO(" + n + ")";
	print "\t}";
}
print_ent(0);
local max_n = 32;
for (local n: [1:max_n]) {
	print "#if PAGESHIFT >=",n;
	print "\t,";
	print_ent(n);
}
for (local n: [max_n - 1:0,-1]) {
	print "#endif /" "* PAGESHIFT >=",n,"*" "/";
}
]]]*/
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[0],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(0)
	}
#if PAGESHIFT >= 1
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[1],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(1)
	}
#if PAGESHIFT >= 2
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[2],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(2)
	}
#if PAGESHIFT >= 3
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[3],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(3)
	}
#if PAGESHIFT >= 4
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[4],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(4)
	}
#if PAGESHIFT >= 5
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[5],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(5)
	}
#if PAGESHIFT >= 6
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[6],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(6)
	}
#if PAGESHIFT >= 7
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[7],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(7)
	}
#if PAGESHIFT >= 8
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[8],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(8)
	}
#if PAGESHIFT >= 9
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[9],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(9)
	}
#if PAGESHIFT >= 10
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[10],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(10)
	}
#if PAGESHIFT >= 11
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[11],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(11)
	}
#if PAGESHIFT >= 12
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[12],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(12)
	}
#if PAGESHIFT >= 13
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[13],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(13)
	}
#if PAGESHIFT >= 14
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[14],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(14)
	}
#if PAGESHIFT >= 15
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[15],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(15)
	}
#if PAGESHIFT >= 16
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[16],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(16)
	}
#if PAGESHIFT >= 17
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[17],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(17)
	}
#if PAGESHIFT >= 18
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[18],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(18)
	}
#if PAGESHIFT >= 19
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[19],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(19)
	}
#if PAGESHIFT >= 20
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[20],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(20)
	}
#if PAGESHIFT >= 21
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[21],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(21)
	}
#if PAGESHIFT >= 22
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[22],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(22)
	}
#if PAGESHIFT >= 23
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[23],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(23)
	}
#if PAGESHIFT >= 24
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[24],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(24)
	}
#if PAGESHIFT >= 25
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[25],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(25)
	}
#if PAGESHIFT >= 26
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[26],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(26)
	}
#if PAGESHIFT >= 27
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[27],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(27)
	}
#if PAGESHIFT >= 28
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[28],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(28)
	}
#if PAGESHIFT >= 29
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[29],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(29)
	}
#if PAGESHIFT >= 30
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[30],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(30)
	}
#if PAGESHIFT >= 31
	,
	{	/* .db_refcnt = */ ((refcnt_t)-1)/2,
		/* .db_lock   = */ RWLOCK_INIT,
		/* .db_type   = */ &vm_datablock_anonymous_zero_type_vec[31],
#ifdef CONFIG_VIO
		/* .db_vio    = */ NULL,
#endif
		/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
		VM_DATABLOCK_INIT_PAGEINFO(31)
	}
#endif /* PAGESHIFT >= 31 */
#endif /* PAGESHIFT >= 30 */
#endif /* PAGESHIFT >= 29 */
#endif /* PAGESHIFT >= 28 */
#endif /* PAGESHIFT >= 27 */
#endif /* PAGESHIFT >= 26 */
#endif /* PAGESHIFT >= 25 */
#endif /* PAGESHIFT >= 24 */
#endif /* PAGESHIFT >= 23 */
#endif /* PAGESHIFT >= 22 */
#endif /* PAGESHIFT >= 21 */
#endif /* PAGESHIFT >= 20 */
#endif /* PAGESHIFT >= 19 */
#endif /* PAGESHIFT >= 18 */
#endif /* PAGESHIFT >= 17 */
#endif /* PAGESHIFT >= 16 */
#endif /* PAGESHIFT >= 15 */
#endif /* PAGESHIFT >= 14 */
#endif /* PAGESHIFT >= 13 */
#endif /* PAGESHIFT >= 12 */
#endif /* PAGESHIFT >= 11 */
#endif /* PAGESHIFT >= 10 */
#endif /* PAGESHIFT >= 9 */
#endif /* PAGESHIFT >= 8 */
#endif /* PAGESHIFT >= 7 */
#endif /* PAGESHIFT >= 6 */
#endif /* PAGESHIFT >= 5 */
#endif /* PAGESHIFT >= 4 */
#endif /* PAGESHIFT >= 3 */
#endif /* PAGESHIFT >= 2 */
#endif /* PAGESHIFT >= 1 */
//[[[end]]]
};


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_BUILTIN_DATABLOCKS_C */
