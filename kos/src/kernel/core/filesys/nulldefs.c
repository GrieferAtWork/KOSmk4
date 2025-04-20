/*[[[magic
options["COMPILE.language"] = "c";
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.remove("-fno-rtti");
gcc_opt.remove("-g"); // Disable debug informations for this file!
]]]*/
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
#ifndef GUARD_KERNEL_CORE_FILESYS_NULLDEFS_C
#define GUARD_KERNEL_CORE_FILESYS_NULLDEFS_C 1
#define __WANT_FS_INIT
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/fs/allnodes.h>
#include <kernel/fs/chrdev.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/null.h>
#include <kernel/fs/ramfs.h>
#include <kernel/mman/driver.h>

#include <sys/io.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include <libvio/api.h>

DECL_BEGIN

#ifdef __arm__
/* FIXME: Ugly, hacky work-around */
#define port_t unsigned short
#endif /* __arm__ */


/* NOTE: Don't  set `MFILE_FN_ATTRREADONLY' for these files, even though
 *       they've got a custom stat operator that overrides the timestamp
 *       values.
 *
 * Reason: Otherwise chmod() and chown() would fail to change permissions! */


#ifndef __DEEMON__
#if (S_IFCHR == 0x2000 && S_IFBLK == 0x6000) && __SIZEOF_INO_T__ == 8
#define _SELECT_INO(ino4, ino8) ino8
#elif (S_IFCHR == 0x2000 && S_IFBLK == 0x6000) && __SIZEOF_INO_T__ == 4
#define _SELECT_INO(ino4, ino8) ino4
#else /* ... */
#error "Unsupported configuration"
#endif /* !... */
#endif /* !__DEEMON__ */

#ifdef LIBVIO_CONFIG_ENABLED
#define NO_USER_IO_WITHOUT_VIO 0
#else /* LIBVIO_CONFIG_ENABLED */
#define NO_USER_IO_WITHOUT_VIO (MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO)
#endif /* !LIBVIO_CONFIG_ENABLED */

/*[[[deemon
import * from deemon;
import fdirent_hash from .....misc.libgen.fdirent_hash;
import llrbtree = .....misc.libgen.llrbtree;
import rbtree = .....misc.libgen.rbtree;
#undef __CCAST
#define __KOS__
#define __KERNEL__
#define __CCAST(T)

// For makedev
#include "../../../../include/asm/os/kos/mkdev.h"
#include "../../../../include/asm/os/mkdev.h"
#include "../../../../include/sys/mkdev.h"

// For __S_IFBLK, __S_IFCHR
#include "../../../../include/asm/os/stat.h"
#ifndef __MKDEV_CURRENT_VERSION
#error WTF?
#endif


local DEVICE_EXTFLAGS = {
	"mem":     none,
	"kmem":    "NO_USER_IO_WITHOUT_VIO",
	"null":    "MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO", // mmap() is forwarded to dev_zero, and I/O has special behavior
	"port":    "NO_USER_IO_WITHOUT_VIO",
	"zero":    none,
	"full":    "MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO", // mmap() is forwarded to dev_zero, and I/O has special behavior
	"random":  "NO_USER_IO_WITHOUT_VIO",
	"urandom": "NO_USER_IO_WITHOUT_VIO",
	"kmsg":    "MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO", // mmap() isn't allowed, and I/O has special behavior
	"tty":     "MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO", // It's a TTY, so no mmap() or "normal" I/O
};

local DEVICE_SIZES = {
	"mem":     "(uint64_t)(physaddr_t)-1",
	"kmem":    "(uint64_t)(size_t)-1",
	"null":    "0",
	"port":    "(uint64_t)(port_t)-1",
	"zero":    "0",
	"full":    "0",
	"random":  "0", // Has a custom stat function
	"urandom": "(uint64_t)-1",
	"kmsg":    "0",
	"tty":     "0", // Has a custom stat function
};

local DEVICES = {
	("mem",     0640 | __S_IFCHR, makedev(1, 1)),
	("kmem",    0640 | __S_IFCHR, makedev(1, 2)),
	("null",    0666 | __S_IFCHR, makedev(1, 3)),
	("port",    0640 | __S_IFCHR, makedev(1, 4)),
	("zero",    0666 | __S_IFCHR, makedev(1, 5)),
	("full",    0666 | __S_IFCHR, makedev(1, 7)),
	("random",  0666 | __S_IFCHR, makedev(1, 8)),
	("urandom", 0666 | __S_IFCHR, makedev(1, 9)),
	("kmsg",    0644 | __S_IFCHR, makedev(1, 11)),
	("tty",     0666 | __S_IFCHR, makedev(5, 0)),
};
local STMODE_MAP = { __S_IFCHR: "S_IFCHR", __S_IFBLK: "S_IFBLK" };

local byNameTree = Cell(none);
for (local name, none, none: DEVICES)
	rbtree.insert(byNameTree, rbtree.RbNode(minkey: name, maxkey: name, val: "dev_" + name));
function devfs_devnode_makeino_4(st_mode, st_rdev) -> (st_rdev << 3) | ((st_mode & 0x4000) << 49) | 7;
function devfs_devnode_makeino_8(st_mode, st_rdev) -> (st_rdev << 3) | ((st_mode & 0x4000) << 17) | 7;

@@Possible encoding mechanisms for ino_t. The elements of this list must
@@correspond to the arguments of `_SELECT_INO`, using the same order.
local MAKEINO_FUNCTIONS = {
	("UINT32_C", devfs_devnode_makeino_4),
	("UINT64_C", devfs_devnode_makeino_8)
};


function generateInoTree(fun): Cell with llrbtree.RbNode {
	local result = Cell(none);
	for (local name, st_mode, st_rdev: DEVICES) {
		local ino = fun(st_mode, st_rdev);
		llrbtree.insert(result, llrbtree.RbNode(minkey: ino, maxkey: ino, val: "dev_" + name + ".dv_devnode.dn_node"));
	}
	return result;
}
local byInoTrees: {(string, Callable, Cell with llrbtree.RbNode)...} = List(
	for (local c, fun: MAKEINO_FUNCTIONS)
		(c, fun, generateInoTree(fun)));

print("static_assert(offsetof(struct ramfs_dirnode, rdn_dir.dn_node) == 0);");
print("static_assert(offsetof(struct device, dv_devnode.dn_node) == 0);");
print("#undef __CCAST");
print("#define __CCAST(T) (uint64_t)");
// Assert that our generated INO numbers are correct
for (local name, st_mode, st_rdev: DEVICES) {
	print("static_assert(devfs_devnode_makeino(", STMODE_MAP[st_mode & ~07777],
		", makedev(", major(st_rdev), ", ", minor(st_rdev), ")) == (__ino_t)_SELECT_INO(",
		", ".join(for (local c, fun: MAKEINO_FUNCTIONS) f"{c}({fun(st_mode, st_rdev).hex()})"),
	"));");
}
print("#undef __CCAST");
print("#define __CCAST");

// Print directory entries.
for (local name, st_mode, st_rdev: DEVICES) {
	print("PRIVATE struct devdirent dirent_dev_", name, " = {");
	print("	.dd_dev = AWREF_INIT(&dev_", name, "),");
	print("	.dd_dirent = {");
	print("		.fd_refcnt  = 2, /" "* +1: dirent_dev_", name, ", +1: dev_", name, ".dv_dirent *" "/");
	print("		.fd_ops     = &devdirent_ops,");
	print("		.fd_ino     = (ino_t)_SELECT_INO(", ", ".join(
		for (local c, fun: MAKEINO_FUNCTIONS)
			f"{c}({fun(st_mode, st_rdev).hex()})"),
	"),");
	print("		.fd_hash    = ", fdirent_hash(name), ",");
	print("		.fd_namelen = ", #name, ",");
	print("		.fd_type    = IFTODT(", STMODE_MAP[st_mode & ~07777], "),");
	print("		.fd_name    = ", repr name);
	print("	}");
	print("};");
}

// Print static initialization symbols
print("_SELECT_INO(", ",\n             ".join(
	for (local none, none, tree: byInoTrees)
		f"DEFINE_INTERN_ALIAS(_devfs__fs_nodes__INIT, {tree.value.val.partition(".").first})"
), ");");
print("DEFINE_INTERN_ALIAS(_devfs_byname_tree__INIT, ", byNameTree.value.val, ");");

// Print device objects
for (local name, none, none: DEVICES)
	print("INTDEF struct chrdev_ops const dev_", name, "_ops;");

for (local name, st_mode, st_rdev: DEVICES) {
	local byNameNode = rbtree.locate(byNameTree.value, name);
	assert byNameNode !is none;
	local inoNodes = List([]{
		for (local c, fun, tree: byInoTrees) {
			local node = llrbtree.locate(tree.value, fun(st_mode, st_rdev));
			assert node !is none;
			yield (c, node);
		}
	}());
	print;
	print("/" "* Device: `/dev/", name, "' *" "/");
	print("PUBLIC struct device dev_", name, " = {");
	print("	.dv_devnode = {");
	print("		.dn_node = {");
	print("			.fn_file = {");
	print("				MFILE_INIT_mf_refcnt(1), /" "* +1: dev_", name, " *" "/");
	print("				MFILE_INIT_mf_ops(&dev_", name, "_ops.cdo_dev.do_node.dvno_node.no_file),");
	print("				MFILE_INIT_mf_lock,");
	print("				MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),");
	print("				MFILE_INIT_mf_initdone,");
	print("				MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),");
	print("				MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),");
	print("				MFILE_INIT_mf_meta,");
	print("				MFILE_INIT_mf_flags(MFILE_F_ATTRCHANGED | MFILE_F_CHANGED |");
	print("				                    MFILE_F_NOATIME | MFILE_F_NOMTIME |");
	print("				                    MFILE_F_FIXEDFILESIZE |");
	local extFlags = DEVICE_EXTFLAGS.get(name);
	if (extFlags !is none)
		print("				                    ", extFlags, " |");
	if (byNameNode.isred)
		print("				                    _MFILE_DEVFS_BYNAME_RED |");
	print("				                    _SELECT_INO(", ", ".join(
		for (local c, node: inoNodes) node.isred ? "_MFILE_FN__RBRED" : "0"),
	")),");
	print("				MFILE_INIT_mf_trunclock,");
	print("				MFILE_INIT_mf_filesize(", DEVICE_SIZES.get(name, "0"), "),");
	print("				MFILE_INIT_mf_atime(0, 0),");
	print("				MFILE_INIT_mf_mtime(0, 0),");
	print("				MFILE_INIT_mf_ctime(0, 0),");
	print("				MFILE_INIT_mf_btime(0, 0),");
	print("				MFILE_INIT_mf_msalign(NULL)");
	print("			},");
	print("			.fn_nlink = 1,");
	print("			.fn_mode  = ", (st_mode & 07777).oct(), " | ", STMODE_MAP[st_mode & ~07777], ",");
	print("			.fn_uid   = 0,");
	print("			.fn_gid   = 0,");
	print("			.fn_ino   = (ino_t)_SELECT_INO(", ", ".join(
		for (local c, node: inoNodes)
			f"{c}({node.minkey.hex()})"
	), "),");
	print("			.fn_super = &devfs.rs_sup,");
	print("			FNODE_INIT_fn_changed,");
	print("			.fn_supent = {");
	print("				.rb_lhs = _SELECT_INO(", ", ".join(for (local none, node: inoNodes) node.lhs is none ? "NULL" : ("&" + node.lhs.val)), "),");
	print("				.rb_rhs = _SELECT_INO(", ", ".join(for (local none, node: inoNodes) node.rhs is none ? "NULL" : ("&" + node.rhs.val)), "),");
	print("			},");
	print("			FNODE_INIT_fn_allnodes,");
	print("		},");
	print("		.dn_devno = makedev(", major(st_rdev), ", ", minor(st_rdev), ")");
	print("	},");
	print("	.dv_driver = &drv_self,");
	print("	.dv_dirent = &dirent_dev_", name, ",");
	print("	.dv_byname_node = {");
	print("		.rb_par = ", byNameNode.par is none ? "NULL" : ("&" + byNameNode.par.val), ",");
	print("		.rb_lhs = ", byNameNode.lhs is none ? "NULL" : ("&" + byNameNode.lhs.val), ",");
	print("		.rb_rhs = ", byNameNode.rhs is none ? "NULL" : ("&" + byNameNode.rhs.val));
	print("	}");
	print("};");
}

]]]*/
static_assert(offsetof(struct ramfs_dirnode, rdn_dir.dn_node) == 0);
static_assert(offsetof(struct device, dv_devnode.dn_node) == 0);
#undef __CCAST
#define __CCAST(T) (uint64_t)
static_assert(devfs_devnode_makeino(S_IFCHR, makedev(1, 1)) == (__ino_t)_SELECT_INO(UINT32_C(0x80000f), UINT64_C(0x80000f)));
static_assert(devfs_devnode_makeino(S_IFCHR, makedev(1, 2)) == (__ino_t)_SELECT_INO(UINT32_C(0x800017), UINT64_C(0x800017)));
static_assert(devfs_devnode_makeino(S_IFCHR, makedev(1, 3)) == (__ino_t)_SELECT_INO(UINT32_C(0x80001f), UINT64_C(0x80001f)));
static_assert(devfs_devnode_makeino(S_IFCHR, makedev(1, 4)) == (__ino_t)_SELECT_INO(UINT32_C(0x800027), UINT64_C(0x800027)));
static_assert(devfs_devnode_makeino(S_IFCHR, makedev(1, 5)) == (__ino_t)_SELECT_INO(UINT32_C(0x80002f), UINT64_C(0x80002f)));
static_assert(devfs_devnode_makeino(S_IFCHR, makedev(1, 7)) == (__ino_t)_SELECT_INO(UINT32_C(0x80003f), UINT64_C(0x80003f)));
static_assert(devfs_devnode_makeino(S_IFCHR, makedev(1, 8)) == (__ino_t)_SELECT_INO(UINT32_C(0x800047), UINT64_C(0x800047)));
static_assert(devfs_devnode_makeino(S_IFCHR, makedev(1, 9)) == (__ino_t)_SELECT_INO(UINT32_C(0x80004f), UINT64_C(0x80004f)));
static_assert(devfs_devnode_makeino(S_IFCHR, makedev(1, 11)) == (__ino_t)_SELECT_INO(UINT32_C(0x80005f), UINT64_C(0x80005f)));
static_assert(devfs_devnode_makeino(S_IFCHR, makedev(5, 0)) == (__ino_t)_SELECT_INO(UINT32_C(0x2800007), UINT64_C(0x2800007)));
#undef __CCAST
#define __CCAST
PRIVATE struct devdirent dirent_dev_mem = {
	.dd_dev = AWREF_INIT(&dev_mem),
	.dd_dirent = {
		.fd_refcnt  = 2, /* +1: dirent_dev_mem, +1: dev_mem.dv_dirent */
		.fd_ops     = &devdirent_ops,
		.fd_ino     = (ino_t)_SELECT_INO(UINT32_C(0x80000f), UINT64_C(0x80000f)),
		.fd_hash    = 0x6d656d,
		.fd_namelen = 3,
		.fd_type    = IFTODT(S_IFCHR),
		.fd_name    = "mem"
	}
};
PRIVATE struct devdirent dirent_dev_kmem = {
	.dd_dev = AWREF_INIT(&dev_kmem),
	.dd_dirent = {
		.fd_refcnt  = 2, /* +1: dirent_dev_kmem, +1: dev_kmem.dv_dirent */
		.fd_ops     = &devdirent_ops,
		.fd_ino     = (ino_t)_SELECT_INO(UINT32_C(0x800017), UINT64_C(0x800017)),
		.fd_hash    = FDIRENT_HASH_INIT(0xd890d8c3, 0x6d656d6b, 0xc6d890d5, 0x6d656d6b),
		.fd_namelen = 4,
		.fd_type    = IFTODT(S_IFCHR),
		.fd_name    = "kmem"
	}
};
PRIVATE struct devdirent dirent_dev_null = {
	.dd_dev = AWREF_INIT(&dev_null),
	.dd_dirent = {
		.fd_refcnt  = 2, /* +1: dirent_dev_null, +1: dev_null.dv_dirent */
		.fd_ops     = &devdirent_ops,
		.fd_ino     = (ino_t)_SELECT_INO(UINT32_C(0x80001f), UINT64_C(0x80001f)),
		.fd_hash    = FDIRENT_HASH_INIT(0xcfd020de, 0x6c6c756e, 0xe220cfcc, 0x6c6c756e),
		.fd_namelen = 4,
		.fd_type    = IFTODT(S_IFCHR),
		.fd_name    = "null"
	}
};
PRIVATE struct devdirent dirent_dev_port = {
	.dd_dev = AWREF_INIT(&dev_port),
	.dd_dirent = {
		.fd_refcnt  = 2, /* +1: dirent_dev_port, +1: dev_port.dv_dirent */
		.fd_ops     = &devdirent_ops,
		.fd_ino     = (ino_t)_SELECT_INO(UINT32_C(0x800027), UINT64_C(0x800027)),
		.fd_hash    = FDIRENT_HASH_INIT(0x1805eaf0, 0x74726f70, 0xf3eb0614, 0x74726f70),
		.fd_namelen = 4,
		.fd_type    = IFTODT(S_IFCHR),
		.fd_name    = "port"
	}
};
PRIVATE struct devdirent dirent_dev_zero = {
	.dd_dev = AWREF_INIT(&dev_zero),
	.dd_dirent = {
		.fd_refcnt  = 2, /* +1: dirent_dev_zero, +1: dev_zero.dv_dirent */
		.fd_ops     = &devdirent_ops,
		.fd_ino     = (ino_t)_SELECT_INO(UINT32_C(0x80002f), UINT64_C(0x80002f)),
		.fd_hash    = FDIRENT_HASH_INIT(0xeb05914a, 0x6f72657a, 0x4d9105e7, 0x6f72657a),
		.fd_namelen = 4,
		.fd_type    = IFTODT(S_IFCHR),
		.fd_name    = "zero"
	}
};
PRIVATE struct devdirent dirent_dev_full = {
	.dd_dev = AWREF_INIT(&dev_full),
	.dd_dirent = {
		.fd_refcnt  = 2, /* +1: dirent_dev_full, +1: dev_full.dv_dirent */
		.fd_ops     = &devdirent_ops,
		.fd_ino     = (ino_t)_SELECT_INO(UINT32_C(0x80003f), UINT64_C(0x80003f)),
		.fd_hash    = FDIRENT_HASH_INIT(0xcfd02096, 0x6c6c7566, 0x9a20cfcc, 0x6c6c7566),
		.fd_namelen = 4,
		.fd_type    = IFTODT(S_IFCHR),
		.fd_name    = "full"
	}
};
PRIVATE struct devdirent dirent_dev_random = {
	.dd_dev = AWREF_INIT(&dev_random),
	.dd_dirent = {
		.fd_refcnt  = 2, /* +1: dirent_dev_random, +1: dev_random.dv_dirent */
		.fd_ops     = &devdirent_ops,
		.fd_ino     = (ino_t)_SELECT_INO(UINT32_C(0x800047), UINT64_C(0x800047)),
		.fd_hash    = FDIRENT_HASH_INIT(0x87e1da71, 0x6d6f646e6172, 0x56d4ef3, 0x6d6f646e6172),
		.fd_namelen = 6,
		.fd_type    = IFTODT(S_IFCHR),
		.fd_name    = "random"
	}
};
PRIVATE struct devdirent dirent_dev_urandom = {
	.dd_dev = AWREF_INIT(&dev_urandom),
	.dd_dirent = {
		.fd_refcnt  = 2, /* +1: dirent_dev_urandom, +1: dev_urandom.dv_dirent */
		.fd_ops     = &devdirent_ops,
		.fd_ino     = (ino_t)_SELECT_INO(UINT32_C(0x80004f), UINT64_C(0x80004f)),
		.fd_hash    = FDIRENT_HASH_INIT(0xe1da7581, 0x6d6f646e617275, 0x2172dc42, 0x6d6f646e617275),
		.fd_namelen = 7,
		.fd_type    = IFTODT(S_IFCHR),
		.fd_name    = "urandom"
	}
};
PRIVATE struct devdirent dirent_dev_kmsg = {
	.dd_dev = AWREF_INIT(&dev_kmsg),
	.dd_dirent = {
		.fd_refcnt  = 2, /* +1: dirent_dev_kmsg, +1: dev_kmsg.dv_dirent */
		.fd_ops     = &devdirent_ops,
		.fd_ino     = (ino_t)_SELECT_INO(UINT32_C(0x80005f), UINT64_C(0x80005f)),
		.fd_hash    = FDIRENT_HASH_INIT(0xa30ed8c3, 0x67736d6b, 0xc6d90e9f, 0x67736d6b),
		.fd_namelen = 4,
		.fd_type    = IFTODT(S_IFCHR),
		.fd_name    = "kmsg"
	}
};
PRIVATE struct devdirent dirent_dev_tty = {
	.dd_dev = AWREF_INIT(&dev_tty),
	.dd_dirent = {
		.fd_refcnt  = 2, /* +1: dirent_dev_tty, +1: dev_tty.dv_dirent */
		.fd_ops     = &devdirent_ops,
		.fd_ino     = (ino_t)_SELECT_INO(UINT32_C(0x2800007), UINT64_C(0x2800007)),
		.fd_hash    = 0x797474,
		.fd_namelen = 3,
		.fd_type    = IFTODT(S_IFCHR),
		.fd_name    = "tty"
	}
};
_SELECT_INO(DEFINE_INTERN_ALIAS(_devfs__fs_nodes__INIT, dev_port),
             DEFINE_INTERN_ALIAS(_devfs__fs_nodes__INIT, dev_port));
DEFINE_INTERN_ALIAS(_devfs_byname_tree__INIT, dev_port);
INTDEF struct chrdev_ops const dev_mem_ops;
INTDEF struct chrdev_ops const dev_kmem_ops;
INTDEF struct chrdev_ops const dev_null_ops;
INTDEF struct chrdev_ops const dev_port_ops;
INTDEF struct chrdev_ops const dev_zero_ops;
INTDEF struct chrdev_ops const dev_full_ops;
INTDEF struct chrdev_ops const dev_random_ops;
INTDEF struct chrdev_ops const dev_urandom_ops;
INTDEF struct chrdev_ops const dev_kmsg_ops;
INTDEF struct chrdev_ops const dev_tty_ops;

/* Device: `/dev/mem' */
PUBLIC struct device dev_mem = {
	.dv_devnode = {
		.dn_node = {
			.fn_file = {
				MFILE_INIT_mf_refcnt(1), /* +1: dev_mem */
				MFILE_INIT_mf_ops(&dev_mem_ops.cdo_dev.do_node.dvno_node.no_file),
				MFILE_INIT_mf_lock,
				MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_initdone,
				MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
				MFILE_INIT_mf_meta,
				MFILE_INIT_mf_flags(MFILE_F_ATTRCHANGED | MFILE_F_CHANGED |
				                    MFILE_F_NOATIME | MFILE_F_NOMTIME |
				                    MFILE_F_FIXEDFILESIZE |
				                    _MFILE_DEVFS_BYNAME_RED |
				                    _SELECT_INO(0, 0)),
				MFILE_INIT_mf_trunclock,
				MFILE_INIT_mf_filesize((uint64_t)(physaddr_t)-1),
				MFILE_INIT_mf_atime(0, 0),
				MFILE_INIT_mf_mtime(0, 0),
				MFILE_INIT_mf_ctime(0, 0),
				MFILE_INIT_mf_btime(0, 0),
				MFILE_INIT_mf_msalign(NULL)
			},
			.fn_nlink = 1,
			.fn_mode  = 0640 | S_IFCHR,
			.fn_uid   = 0,
			.fn_gid   = 0,
			.fn_ino   = (ino_t)_SELECT_INO(UINT32_C(0x80000f), UINT64_C(0x80000f)),
			.fn_super = &devfs.rs_sup,
			FNODE_INIT_fn_changed,
			.fn_supent = {
				.rb_lhs = _SELECT_INO(NULL, NULL),
				.rb_rhs = _SELECT_INO(NULL, NULL),
			},
			FNODE_INIT_fn_allnodes,
		},
		.dn_devno = makedev(1, 1)
	},
	.dv_driver = &drv_self,
	.dv_dirent = &dirent_dev_mem,
	.dv_byname_node = {
		.rb_par = &dev_port,
		.rb_lhs = &dev_kmem,
		.rb_rhs = &dev_null
	}
};

/* Device: `/dev/kmem' */
PUBLIC struct device dev_kmem = {
	.dv_devnode = {
		.dn_node = {
			.fn_file = {
				MFILE_INIT_mf_refcnt(1), /* +1: dev_kmem */
				MFILE_INIT_mf_ops(&dev_kmem_ops.cdo_dev.do_node.dvno_node.no_file),
				MFILE_INIT_mf_lock,
				MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_initdone,
				MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
				MFILE_INIT_mf_meta,
				MFILE_INIT_mf_flags(MFILE_F_ATTRCHANGED | MFILE_F_CHANGED |
				                    MFILE_F_NOATIME | MFILE_F_NOMTIME |
				                    MFILE_F_FIXEDFILESIZE |
				                    NO_USER_IO_WITHOUT_VIO |
				                    _SELECT_INO(0, 0)),
				MFILE_INIT_mf_trunclock,
				MFILE_INIT_mf_filesize((uint64_t)(size_t)-1),
				MFILE_INIT_mf_atime(0, 0),
				MFILE_INIT_mf_mtime(0, 0),
				MFILE_INIT_mf_ctime(0, 0),
				MFILE_INIT_mf_btime(0, 0),
				MFILE_INIT_mf_msalign(NULL)
			},
			.fn_nlink = 1,
			.fn_mode  = 0640 | S_IFCHR,
			.fn_uid   = 0,
			.fn_gid   = 0,
			.fn_ino   = (ino_t)_SELECT_INO(UINT32_C(0x800017), UINT64_C(0x800017)),
			.fn_super = &devfs.rs_sup,
			FNODE_INIT_fn_changed,
			.fn_supent = {
				.rb_lhs = _SELECT_INO(&dev_mem.dv_devnode.dn_node, &dev_mem.dv_devnode.dn_node),
				.rb_rhs = _SELECT_INO(&dev_null.dv_devnode.dn_node, &dev_null.dv_devnode.dn_node),
			},
			FNODE_INIT_fn_allnodes,
		},
		.dn_devno = makedev(1, 2)
	},
	.dv_driver = &drv_self,
	.dv_dirent = &dirent_dev_kmem,
	.dv_byname_node = {
		.rb_par = &dev_mem,
		.rb_lhs = &dev_full,
		.rb_rhs = &dev_kmsg
	}
};

/* Device: `/dev/null' */
PUBLIC struct device dev_null = {
	.dv_devnode = {
		.dn_node = {
			.fn_file = {
				MFILE_INIT_mf_refcnt(1), /* +1: dev_null */
				MFILE_INIT_mf_ops(&dev_null_ops.cdo_dev.do_node.dvno_node.no_file),
				MFILE_INIT_mf_lock,
				MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_initdone,
				MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
				MFILE_INIT_mf_meta,
				MFILE_INIT_mf_flags(MFILE_F_ATTRCHANGED | MFILE_F_CHANGED |
				                    MFILE_F_NOATIME | MFILE_F_NOMTIME |
				                    MFILE_F_FIXEDFILESIZE |
				                    MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
				                    _SELECT_INO(0, 0)),
				MFILE_INIT_mf_trunclock,
				MFILE_INIT_mf_filesize(0),
				MFILE_INIT_mf_atime(0, 0),
				MFILE_INIT_mf_mtime(0, 0),
				MFILE_INIT_mf_ctime(0, 0),
				MFILE_INIT_mf_btime(0, 0),
				MFILE_INIT_mf_msalign(NULL)
			},
			.fn_nlink = 1,
			.fn_mode  = 0666 | S_IFCHR,
			.fn_uid   = 0,
			.fn_gid   = 0,
			.fn_ino   = (ino_t)_SELECT_INO(UINT32_C(0x80001f), UINT64_C(0x80001f)),
			.fn_super = &devfs.rs_sup,
			FNODE_INIT_fn_changed,
			.fn_supent = {
				.rb_lhs = _SELECT_INO(NULL, NULL),
				.rb_rhs = _SELECT_INO(NULL, NULL),
			},
			FNODE_INIT_fn_allnodes,
		},
		.dn_devno = makedev(1, 3)
	},
	.dv_driver = &drv_self,
	.dv_dirent = &dirent_dev_null,
	.dv_byname_node = {
		.rb_par = &dev_mem,
		.rb_lhs = NULL,
		.rb_rhs = NULL
	}
};

/* Device: `/dev/port' */
PUBLIC struct device dev_port = {
	.dv_devnode = {
		.dn_node = {
			.fn_file = {
				MFILE_INIT_mf_refcnt(1), /* +1: dev_port */
				MFILE_INIT_mf_ops(&dev_port_ops.cdo_dev.do_node.dvno_node.no_file),
				MFILE_INIT_mf_lock,
				MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_initdone,
				MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
				MFILE_INIT_mf_meta,
				MFILE_INIT_mf_flags(MFILE_F_ATTRCHANGED | MFILE_F_CHANGED |
				                    MFILE_F_NOATIME | MFILE_F_NOMTIME |
				                    MFILE_F_FIXEDFILESIZE |
				                    NO_USER_IO_WITHOUT_VIO |
				                    _SELECT_INO(0, 0)),
				MFILE_INIT_mf_trunclock,
				MFILE_INIT_mf_filesize((uint64_t)(port_t)-1),
				MFILE_INIT_mf_atime(0, 0),
				MFILE_INIT_mf_mtime(0, 0),
				MFILE_INIT_mf_ctime(0, 0),
				MFILE_INIT_mf_btime(0, 0),
				MFILE_INIT_mf_msalign(NULL)
			},
			.fn_nlink = 1,
			.fn_mode  = 0640 | S_IFCHR,
			.fn_uid   = 0,
			.fn_gid   = 0,
			.fn_ino   = (ino_t)_SELECT_INO(UINT32_C(0x800027), UINT64_C(0x800027)),
			.fn_super = &devfs.rs_sup,
			FNODE_INIT_fn_changed,
			.fn_supent = {
				.rb_lhs = _SELECT_INO(&dev_kmem.dv_devnode.dn_node, &dev_kmem.dv_devnode.dn_node),
				.rb_rhs = _SELECT_INO(&dev_urandom.dv_devnode.dn_node, &dev_urandom.dv_devnode.dn_node),
			},
			FNODE_INIT_fn_allnodes,
		},
		.dn_devno = makedev(1, 4)
	},
	.dv_driver = &drv_self,
	.dv_dirent = &dirent_dev_port,
	.dv_byname_node = {
		.rb_par = NULL,
		.rb_lhs = &dev_mem,
		.rb_rhs = &dev_urandom
	}
};

/* Device: `/dev/zero' */
PUBLIC struct device dev_zero = {
	.dv_devnode = {
		.dn_node = {
			.fn_file = {
				MFILE_INIT_mf_refcnt(1), /* +1: dev_zero */
				MFILE_INIT_mf_ops(&dev_zero_ops.cdo_dev.do_node.dvno_node.no_file),
				MFILE_INIT_mf_lock,
				MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_initdone,
				MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
				MFILE_INIT_mf_meta,
				MFILE_INIT_mf_flags(MFILE_F_ATTRCHANGED | MFILE_F_CHANGED |
				                    MFILE_F_NOATIME | MFILE_F_NOMTIME |
				                    MFILE_F_FIXEDFILESIZE |
				                    _SELECT_INO(0, 0)),
				MFILE_INIT_mf_trunclock,
				MFILE_INIT_mf_filesize(0),
				MFILE_INIT_mf_atime(0, 0),
				MFILE_INIT_mf_mtime(0, 0),
				MFILE_INIT_mf_ctime(0, 0),
				MFILE_INIT_mf_btime(0, 0),
				MFILE_INIT_mf_msalign(NULL)
			},
			.fn_nlink = 1,
			.fn_mode  = 0666 | S_IFCHR,
			.fn_uid   = 0,
			.fn_gid   = 0,
			.fn_ino   = (ino_t)_SELECT_INO(UINT32_C(0x80002f), UINT64_C(0x80002f)),
			.fn_super = &devfs.rs_sup,
			FNODE_INIT_fn_changed,
			.fn_supent = {
				.rb_lhs = _SELECT_INO(NULL, NULL),
				.rb_rhs = _SELECT_INO(NULL, NULL),
			},
			FNODE_INIT_fn_allnodes,
		},
		.dn_devno = makedev(1, 5)
	},
	.dv_driver = &drv_self,
	.dv_dirent = &dirent_dev_zero,
	.dv_byname_node = {
		.rb_par = &dev_urandom,
		.rb_lhs = NULL,
		.rb_rhs = NULL
	}
};

/* Device: `/dev/full' */
PUBLIC struct device dev_full = {
	.dv_devnode = {
		.dn_node = {
			.fn_file = {
				MFILE_INIT_mf_refcnt(1), /* +1: dev_full */
				MFILE_INIT_mf_ops(&dev_full_ops.cdo_dev.do_node.dvno_node.no_file),
				MFILE_INIT_mf_lock,
				MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_initdone,
				MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
				MFILE_INIT_mf_meta,
				MFILE_INIT_mf_flags(MFILE_F_ATTRCHANGED | MFILE_F_CHANGED |
				                    MFILE_F_NOATIME | MFILE_F_NOMTIME |
				                    MFILE_F_FIXEDFILESIZE |
				                    MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
				                    _MFILE_DEVFS_BYNAME_RED |
				                    _SELECT_INO(_MFILE_FN__RBRED, _MFILE_FN__RBRED)),
				MFILE_INIT_mf_trunclock,
				MFILE_INIT_mf_filesize(0),
				MFILE_INIT_mf_atime(0, 0),
				MFILE_INIT_mf_mtime(0, 0),
				MFILE_INIT_mf_ctime(0, 0),
				MFILE_INIT_mf_btime(0, 0),
				MFILE_INIT_mf_msalign(NULL)
			},
			.fn_nlink = 1,
			.fn_mode  = 0666 | S_IFCHR,
			.fn_uid   = 0,
			.fn_gid   = 0,
			.fn_ino   = (ino_t)_SELECT_INO(UINT32_C(0x80003f), UINT64_C(0x80003f)),
			.fn_super = &devfs.rs_sup,
			FNODE_INIT_fn_changed,
			.fn_supent = {
				.rb_lhs = _SELECT_INO(&dev_zero.dv_devnode.dn_node, &dev_zero.dv_devnode.dn_node),
				.rb_rhs = _SELECT_INO(&dev_random.dv_devnode.dn_node, &dev_random.dv_devnode.dn_node),
			},
			FNODE_INIT_fn_allnodes,
		},
		.dn_devno = makedev(1, 7)
	},
	.dv_driver = &drv_self,
	.dv_dirent = &dirent_dev_full,
	.dv_byname_node = {
		.rb_par = &dev_kmem,
		.rb_lhs = NULL,
		.rb_rhs = NULL
	}
};

/* Device: `/dev/random' */
PUBLIC struct device dev_random = {
	.dv_devnode = {
		.dn_node = {
			.fn_file = {
				MFILE_INIT_mf_refcnt(1), /* +1: dev_random */
				MFILE_INIT_mf_ops(&dev_random_ops.cdo_dev.do_node.dvno_node.no_file),
				MFILE_INIT_mf_lock,
				MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_initdone,
				MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
				MFILE_INIT_mf_meta,
				MFILE_INIT_mf_flags(MFILE_F_ATTRCHANGED | MFILE_F_CHANGED |
				                    MFILE_F_NOATIME | MFILE_F_NOMTIME |
				                    MFILE_F_FIXEDFILESIZE |
				                    NO_USER_IO_WITHOUT_VIO |
				                    _SELECT_INO(0, 0)),
				MFILE_INIT_mf_trunclock,
				MFILE_INIT_mf_filesize(0),
				MFILE_INIT_mf_atime(0, 0),
				MFILE_INIT_mf_mtime(0, 0),
				MFILE_INIT_mf_ctime(0, 0),
				MFILE_INIT_mf_btime(0, 0),
				MFILE_INIT_mf_msalign(NULL)
			},
			.fn_nlink = 1,
			.fn_mode  = 0666 | S_IFCHR,
			.fn_uid   = 0,
			.fn_gid   = 0,
			.fn_ino   = (ino_t)_SELECT_INO(UINT32_C(0x800047), UINT64_C(0x800047)),
			.fn_super = &devfs.rs_sup,
			FNODE_INIT_fn_changed,
			.fn_supent = {
				.rb_lhs = _SELECT_INO(NULL, NULL),
				.rb_rhs = _SELECT_INO(NULL, NULL),
			},
			FNODE_INIT_fn_allnodes,
		},
		.dn_devno = makedev(1, 8)
	},
	.dv_driver = &drv_self,
	.dv_dirent = &dirent_dev_random,
	.dv_byname_node = {
		.rb_par = &dev_urandom,
		.rb_lhs = NULL,
		.rb_rhs = &dev_tty
	}
};

/* Device: `/dev/urandom' */
PUBLIC struct device dev_urandom = {
	.dv_devnode = {
		.dn_node = {
			.fn_file = {
				MFILE_INIT_mf_refcnt(1), /* +1: dev_urandom */
				MFILE_INIT_mf_ops(&dev_urandom_ops.cdo_dev.do_node.dvno_node.no_file),
				MFILE_INIT_mf_lock,
				MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_initdone,
				MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
				MFILE_INIT_mf_meta,
				MFILE_INIT_mf_flags(MFILE_F_ATTRCHANGED | MFILE_F_CHANGED |
				                    MFILE_F_NOATIME | MFILE_F_NOMTIME |
				                    MFILE_F_FIXEDFILESIZE |
				                    NO_USER_IO_WITHOUT_VIO |
				                    _MFILE_DEVFS_BYNAME_RED |
				                    _SELECT_INO(0, 0)),
				MFILE_INIT_mf_trunclock,
				MFILE_INIT_mf_filesize((uint64_t)-1),
				MFILE_INIT_mf_atime(0, 0),
				MFILE_INIT_mf_mtime(0, 0),
				MFILE_INIT_mf_ctime(0, 0),
				MFILE_INIT_mf_btime(0, 0),
				MFILE_INIT_mf_msalign(NULL)
			},
			.fn_nlink = 1,
			.fn_mode  = 0666 | S_IFCHR,
			.fn_uid   = 0,
			.fn_gid   = 0,
			.fn_ino   = (ino_t)_SELECT_INO(UINT32_C(0x80004f), UINT64_C(0x80004f)),
			.fn_super = &devfs.rs_sup,
			FNODE_INIT_fn_changed,
			.fn_supent = {
				.rb_lhs = _SELECT_INO(&dev_full.dv_devnode.dn_node, &dev_full.dv_devnode.dn_node),
				.rb_rhs = _SELECT_INO(&dev_tty.dv_devnode.dn_node, &dev_tty.dv_devnode.dn_node),
			},
			FNODE_INIT_fn_allnodes,
		},
		.dn_devno = makedev(1, 9)
	},
	.dv_driver = &drv_self,
	.dv_dirent = &dirent_dev_urandom,
	.dv_byname_node = {
		.rb_par = &dev_port,
		.rb_lhs = &dev_random,
		.rb_rhs = &dev_zero
	}
};

/* Device: `/dev/kmsg' */
PUBLIC struct device dev_kmsg = {
	.dv_devnode = {
		.dn_node = {
			.fn_file = {
				MFILE_INIT_mf_refcnt(1), /* +1: dev_kmsg */
				MFILE_INIT_mf_ops(&dev_kmsg_ops.cdo_dev.do_node.dvno_node.no_file),
				MFILE_INIT_mf_lock,
				MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_initdone,
				MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
				MFILE_INIT_mf_meta,
				MFILE_INIT_mf_flags(MFILE_F_ATTRCHANGED | MFILE_F_CHANGED |
				                    MFILE_F_NOATIME | MFILE_F_NOMTIME |
				                    MFILE_F_FIXEDFILESIZE |
				                    MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
				                    _MFILE_DEVFS_BYNAME_RED |
				                    _SELECT_INO(_MFILE_FN__RBRED, _MFILE_FN__RBRED)),
				MFILE_INIT_mf_trunclock,
				MFILE_INIT_mf_filesize(0),
				MFILE_INIT_mf_atime(0, 0),
				MFILE_INIT_mf_mtime(0, 0),
				MFILE_INIT_mf_ctime(0, 0),
				MFILE_INIT_mf_btime(0, 0),
				MFILE_INIT_mf_msalign(NULL)
			},
			.fn_nlink = 1,
			.fn_mode  = 0644 | S_IFCHR,
			.fn_uid   = 0,
			.fn_gid   = 0,
			.fn_ino   = (ino_t)_SELECT_INO(UINT32_C(0x80005f), UINT64_C(0x80005f)),
			.fn_super = &devfs.rs_sup,
			FNODE_INIT_fn_changed,
			.fn_supent = {
				.rb_lhs = _SELECT_INO(NULL, NULL),
				.rb_rhs = _SELECT_INO(NULL, NULL),
			},
			FNODE_INIT_fn_allnodes,
		},
		.dn_devno = makedev(1, 11)
	},
	.dv_driver = &drv_self,
	.dv_dirent = &dirent_dev_kmsg,
	.dv_byname_node = {
		.rb_par = &dev_kmem,
		.rb_lhs = NULL,
		.rb_rhs = NULL
	}
};

/* Device: `/dev/tty' */
PUBLIC struct device dev_tty = {
	.dv_devnode = {
		.dn_node = {
			.fn_file = {
				MFILE_INIT_mf_refcnt(1), /* +1: dev_tty */
				MFILE_INIT_mf_ops(&dev_tty_ops.cdo_dev.do_node.dvno_node.no_file),
				MFILE_INIT_mf_lock,
				MFILE_INIT_mf_parts(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_initdone,
				MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
				MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
				MFILE_INIT_mf_meta,
				MFILE_INIT_mf_flags(MFILE_F_ATTRCHANGED | MFILE_F_CHANGED |
				                    MFILE_F_NOATIME | MFILE_F_NOMTIME |
				                    MFILE_F_FIXEDFILESIZE |
				                    MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO |
				                    _MFILE_DEVFS_BYNAME_RED |
				                    _SELECT_INO(0, 0)),
				MFILE_INIT_mf_trunclock,
				MFILE_INIT_mf_filesize(0),
				MFILE_INIT_mf_atime(0, 0),
				MFILE_INIT_mf_mtime(0, 0),
				MFILE_INIT_mf_ctime(0, 0),
				MFILE_INIT_mf_btime(0, 0),
				MFILE_INIT_mf_msalign(NULL)
			},
			.fn_nlink = 1,
			.fn_mode  = 0666 | S_IFCHR,
			.fn_uid   = 0,
			.fn_gid   = 0,
			.fn_ino   = (ino_t)_SELECT_INO(UINT32_C(0x2800007), UINT64_C(0x2800007)),
			.fn_super = &devfs.rs_sup,
			FNODE_INIT_fn_changed,
			.fn_supent = {
				.rb_lhs = _SELECT_INO(&dev_kmsg.dv_devnode.dn_node, &dev_kmsg.dv_devnode.dn_node),
				.rb_rhs = _SELECT_INO(NULL, NULL),
			},
			FNODE_INIT_fn_allnodes,
		},
		.dn_devno = makedev(5, 0)
	},
	.dv_driver = &drv_self,
	.dv_dirent = &dirent_dev_tty,
	.dv_byname_node = {
		.rb_par = &dev_random,
		.rb_lhs = NULL,
		.rb_rhs = NULL
	}
};
/*[[[end]]]*/


/* Special mem-files are unconditional aliases here! */
static_assert(offsetof(struct device, dv_devnode.dn_node.fn_file) == 0);
DEFINE_PUBLIC_ALIAS(mfile_phys, dev_mem);
DEFINE_PUBLIC_ALIAS(mfile_zero, dev_zero);


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_NULLDEFS_C */
