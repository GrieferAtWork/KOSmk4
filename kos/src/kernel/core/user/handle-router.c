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
#ifndef GUARD_KERNEL_SRC_USER_HANDLE_C
#define GUARD_KERNEL_SRC_USER_HANDLE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/types.h>
#include <kernel/vm.h>
#include <assert.h>

#include <kos/kernel/handle.h>

DECL_BEGIN

#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"

INTERN NOBLOCK void NOTHROW(FCALL handle_undefined_incref)(void *__restrict UNUSED(ptr)) { }
INTDEF NOBLOCK void NOTHROW(FCALL handle_undefined_decref)(void *__restrict UNUSED(ptr));
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_undefined_refcnt)(void *__restrict UNUSED(ptr)) { return 0; }
DEFINE_INTERN_ALIAS(handle_undefined_decref,handle_undefined_incref);

/*[[[deemon
import util;
import * from deemon;

function generate_io_default_impl(name, args) {
	return
		"{{\n"
		"\tsize_t result;\n"
		"\tstruct aio_multihandle_generic aio;\n"
		"\taio_multihandle_generic_init(&aio);\n"
		"\tTRY {{\n"
		"\t\tresult = handle_{name}_" + name + "(" + args + ", &aio);\n"
		"\t}} EXCEPT {{\n"
		"\t\taio_multihandle_fail(&aio);\n"
		"\t}}\n"
		"\taio_multihandle_done(&aio);\n"
		"\taio_multihandle_generic_waitfor(&aio);\n"
		"\taio_multihandle_generic_checkerror(&aio);\n"
		"\treturn result;\n"
		"}}"
	;
}

local default_impls = {
	"readv" :
		"{{\n"
		"	size_t temp, result = 0;\n"
		"	struct aio_buffer_entry ent;\n"
		"	assert(aio_buffer_size(dst) == num_bytes);\n"
		"	(void)num_bytes;\n"
		"	AIO_BUFFER_FOREACH(ent, dst) {{\n"
		"		temp = handle_{name}_read(ptr, ent.ab_base, ent.ab_size, mode);\n"
		"		result += temp;\n"
		"		if (temp != ent.ab_size)\n"
		"			break;\n"
		"	}}\n"
		"	return result;\n"
		"}}",
	"writev" :
		"{{\n"
		"	size_t temp, result = 0;\n"
		"	struct aio_buffer_entry ent;\n"
		"	assert(aio_buffer_size(src) == num_bytes);\n"
		"	(void)num_bytes;\n"
		"	AIO_BUFFER_FOREACH(ent, src) {{\n"
		"		temp = handle_{name}_write(ptr, ent.ab_base, ent.ab_size, mode);\n"
		"		result += temp;\n"
		"		if (temp != ent.ab_size)\n"
		"			break;\n"
		"	}}\n"
		"	return result;\n"
		"}}",
	"preadv" :
		"{{\n"
		"	size_t temp, result = 0;\n"
		"	struct aio_buffer_entry ent;\n"
		"	assert(aio_buffer_size(dst) == num_bytes);\n"
		"	(void)num_bytes;\n"
		"	AIO_BUFFER_FOREACH(ent, dst) {{\n"
		"		temp = handle_{name}_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);\n"
		"		result += temp;\n"
		"		if (temp != ent.ab_size)\n"
		"			break;\n"
		"		addr += temp;\n"
		"	}}\n"
		"	return result;\n"
		"}}",
	"pwritev" :
		"{{\n"
		"	size_t temp, result = 0;\n"
		"	struct aio_buffer_entry ent;\n"
		"	assert(aio_buffer_size(src) == num_bytes);\n"
		"	(void)num_bytes;\n"
		"	AIO_BUFFER_FOREACH(ent, src) {{\n"
		"		temp = handle_{name}_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);\n"
		"		result += temp;\n"
		"		if (temp != ent.ab_size)\n"
		"			break;\n"
		"		addr += temp;\n"
		"	}}\n"
		"	return result;\n"
		"}}",
	"aread" :
		"{{\n"
		"	size_t result;\n"
		"	(void)aio;\n"
		"	result = handle_{name}_read(ptr, dst, num_bytes, mode);\n"
		"	return result;\n"
		"}}",
	"awrite" :
		"{{\n"
		"	size_t result;\n"
		"	(void)aio;\n"
		"	result = handle_{name}_write(ptr, src, num_bytes, mode);\n"
		"	return result;\n"
		"}}",
	"apread" :
		"{{\n"
		"	size_t result;\n"
		"	(void)aio;\n"
		"	result = handle_{name}_pread(ptr, dst, num_bytes, addr, mode);\n"
		"	return result;\n"
		"}}",
	"apwrite" :
		"{{\n"
		"	size_t result;\n"
		"	(void)aio;\n"
		"	result = handle_{name}_pwrite(ptr, src, num_bytes, addr, mode);\n"
		"	return result;\n"
		"}}",
	"areadv" :
		"{{\n"
		"	size_t result;\n"
		"	(void)aio;\n"
		"	result = handle_{name}_readv(ptr, dst, num_bytes, mode);\n"
		"	return result;\n"
		"}}",
	"awritev" :
		"{{\n"
		"	size_t result;\n"
		"	(void)aio;\n"
		"	result = handle_{name}_writev(ptr, src, num_bytes, mode);\n"
		"	return result;\n"
		"}}",
	"apreadv" :
		"{{\n"
		"	size_t result;\n"
		"	(void)aio;\n"
		"	result = handle_{name}_preadv(ptr, dst, num_bytes, addr, mode);\n"
		"	return result;\n"
		"}}",
	"apwritev" :
		"{{\n"
		"	size_t result;\n"
		"	(void)aio;\n"
		"	result = handle_{name}_pwritev(ptr, src, num_bytes, addr, mode);\n"
		"	return result;\n"
		"}}",
};
function get_default_impl(typnam, name) {
	return default_impls.get(name).format({ "name": typnam });
}


function split_argument_list(text: string): {(string, string)...} {
	text = text.strip();
	local i = 0,end = #text;
	while (i < end) {
		if (text.isspace(i)) {
			++i;
			continue;
		}
		local type_start = i;
		i = text.find(",", i);
		if (i < 0)
			i = end;
		local type_and_name = text.substr(type_start, i).strip();
		local name_start = #type_and_name;
		while (name_start > 0 && type_and_name.issymcont(name_start - 1))
			--name_start;
		yield (type_and_name.substr(name_start).strip(),
		       type_and_name.substr(0, name_start).strip());
		++i;
	}
}

@@Tuples of (name, cc, return_type, args)
local handle_operations: {(string, string, string, string)...} = [];
for (local l: File.open("../../include/kernel/handle.h")) {
	local pos = l.find("[HANDLE_TYPE_COUNT]");
	if (pos < 0) continue;
	local name_start = l.rindex("*", 0, pos) + 1;
	local name = l[name_start:pos].strip();
	if (name == "h_typename") continue;
	local type_end = l.rindex("(", 0, name_start);
	local cc = l[type_end + 1:name_start - 1].strip();
	local return_type = l[:type_end].strip();
	local param_start = l.index("(", pos) + 1;
	local param_end = l.indexmatch("(", ")", param_start);
	local params = l[param_start:param_end];
	handle_operations.append((name, cc, return_type, params));
}
local handle_types: {string...} = [];
for (local l: File.open("../../../../include/kos/kernel/handle.h")) {
	local name, id;
	try name, id = l.scanf(" # define HANDLE_TYPE_%[^ ] %[^ /]")...;
	catch (...) continue;
	if (name == "COUNT") continue;
	id = int(id);
	if (id >= #handle_types)
		handle_types.resize(id + 1, "undefined");
	handle_types[id] = name.lower();
}
for (local name, cc, return_type, args: handle_operations) {
	if (name.startswith("h_"))
		name = name[2:];
	if (name in ["incref", "decref", "refcnt"])
		continue;
	print "INTERN ATTR_SECTION(",;
	print repr(".text.kernel.handle_undefined." + name),;
	print ") ",;
	print return_type.strip(),;
	if (!return_type.endswith("*"))
		print " ",;
	print cc,;
	print " ",;
	print "handle_undefined_" + name,;
	print "(",;
	print ", ".join(
		for (local n, t: split_argument_list(args))
			t + (t.endswith("*") ? "" : " ") + (n in ["cmd"] ? n : ("UNUSED(" + n + ")"))
		),;
	print ") { ",;
	if (name == "ioctl")
		print "THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND, cmd);",;
	else if (name == "hop")
		print "THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND, cmd);",;
	else if ("readdir" in name)
		print "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READDIR);",;
	else if ("read" in name)
		print "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);",;
	else if ("write" in name)
		print "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);",;
	else if ("seek" in name)
		print "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SEEK);",;
	else if ("mmap" in name)
		print "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_MMAP);",;
	else if ("datasync" in name)
		print "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_DATASYNC);",;
	else if ("sync" in name)
		print "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SYNC);",;
	else if ("stat" in name)
		print "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_STAT);",;
	else if ("poll" in name)
		print "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_POLL);",;
	else if ("trunc" in name)
		print "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_TRUNC);",;
	else if ("alloc" in name)
		print "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_ALLOCATE);",;
	else {
		print "THROW(E_NOT_IMPLEMENTED_UNSUPPORTED);",;
	}
	print " }";
}

local type_names_written = HashSet();
for (local n: handle_types) {
	if (n in type_names_written)
		continue;
	if (n == "undefined") continue;
	type_names_written.insert(n);
	for (local name, cc, return_type, args: handle_operations) {
		local is_nothrow = false;
		if (return_type.endswith("/" "*NOTHROW*" "/")) {
			return_type = return_type[:#return_type - #"/" "*NOTHROW*" "/"];
			is_nothrow = true;
		}
		print "INTDEF ",;
		print return_type.strip(),;
		if (!return_type.endswith("*"))
			print " ",;
		if (is_nothrow)
			print "NOTHROW(",;
		print cc,;
		print " ",;
		if (name.startswith("h_"))
			name = name[2:];
		print "handle_" + n + "_" + name,;
		if (is_nothrow)
			print ")",;
		print "(",;
		print args,;
		print ");";
	}
}
local longest_handle_type_name = 0;
for (local n: handle_types) {
	local temp = #n;
	if (longest_handle_type_name < temp)
		longest_handle_type_name = temp;
}
print;
print "PUBLIC_CONST struct handle_types const handle_type_db = {";
print "\t/" "* .h_typename = *" "/{";
for (local i, n: util.enumerate(handle_types)) {
	print "\t\t/" "* [HANDLE_TYPE_" + n.upper() + "]",;
	print " " * (longest_handle_type_name - #n),;
	print " = *" "/" + repr(n),;
	if (i != #handle_types - 1) print ",",;
	print;
}
print "\t},";
for (local name, none, none, none: handle_operations) {
	print "\t/" "* ." + name + " = *" "/{";
	local fixed_name = name;
	if (fixed_name.startswith("h_"))
		fixed_name = fixed_name[2:];
	for (local i,n: util.enumerate(handle_types)) {
		print "\t\t/" "* [HANDLE_TYPE_" + n.upper() + "]",;
		print " " * (longest_handle_type_name - #n),;
		print " = *" "/&" + "handle_" + n + "_" + fixed_name,;
		if (i != #handle_types - 1) print ",",;
		print;
	}
	print "\t}",;
	if (name != handle_operations[#handle_operations - 1][0])
		print ",",;
	print;
}
print "};";
print;
local type_names_written = HashSet();
for (local n: handle_types) {
	if (n in type_names_written)
		continue;
	if (n == "undefined") continue;
	type_names_written.insert(n);
	for (local name, none, none, none: handle_operations) {
		if (name.startswith("h_"))
			name = name[2:];
		if (name in default_impls)
			continue;
		print "DEFINE_INTERN_WEAK_ALIAS(handle_" + n + "_" + name + ", handle_undefined_" + name + ");";
	}
}
local type_names_written = HashSet();
for (local n: handle_types) {
	if (n in type_names_written)
		continue;
	if (n == "undefined") continue;
	type_names_written.insert(n);
	for (local name, cc, return_type, args: handle_operations) {
		if (name.startswith("h_"))
			name = name[2:];
		local defl = get_default_impl(n, name);
		if (defl is none)
			continue;
		print "INTERN ATTR_WEAK ATTR_SECTION(\".text.kernel.handle_fallback.",;
		print n,;
		print ".",;
		print name,;
		print "\") ",;
		print return_type.strip(),;
		if (!return_type.endswith("*"))
			print " ",;
		print cc;
		print "handle_" + n + "_" + name,;
		print "(",;
		print ", ".join(
			for (local n, t: split_argument_list(args))
				t + (t.endswith("*") ? "" : " ") + n
			),;
		print ")", defl;
		print;
	}
}

]]]*/
INTERN ATTR_SECTION(".text.kernel.handle_undefined.read") size_t KCALL handle_undefined_read(void *__restrict UNUSED(ptr), USER CHECKED void *UNUSED(dst), size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.write") size_t KCALL handle_undefined_write(void *__restrict UNUSED(ptr), USER CHECKED void const *UNUSED(src), size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.pread") size_t KCALL handle_undefined_pread(void *__restrict UNUSED(ptr), USER CHECKED void *UNUSED(dst), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.pwrite") size_t KCALL handle_undefined_pwrite(void *__restrict UNUSED(ptr), USER CHECKED void const *UNUSED(src), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.readv") size_t KCALL handle_undefined_readv(void *__restrict UNUSED(ptr), struct aio_buffer *__restrict UNUSED(dst), size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.writev") size_t KCALL handle_undefined_writev(void *__restrict UNUSED(ptr), struct aio_buffer *__restrict UNUSED(src), size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.preadv") size_t KCALL handle_undefined_preadv(void *__restrict UNUSED(ptr), struct aio_buffer *__restrict UNUSED(dst), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.pwritev") size_t KCALL handle_undefined_pwritev(void *__restrict UNUSED(ptr), struct aio_buffer *__restrict UNUSED(src), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.aread") size_t KCALL handle_undefined_aread(void *__restrict UNUSED(ptr), USER CHECKED void *UNUSED(dst), size_t UNUSED(num_bytes), iomode_t UNUSED(mode), struct aio_multihandle *__restrict UNUSED(aio)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.awrite") size_t KCALL handle_undefined_awrite(void *__restrict UNUSED(ptr), USER CHECKED void const *UNUSED(src), size_t UNUSED(num_bytes), iomode_t UNUSED(mode), struct aio_multihandle *__restrict UNUSED(aio)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.apread") size_t KCALL handle_undefined_apread(void *__restrict UNUSED(ptr), USER CHECKED void *UNUSED(dst), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode), struct aio_multihandle *__restrict UNUSED(aio)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.apwrite") size_t KCALL handle_undefined_apwrite(void *__restrict UNUSED(ptr), USER CHECKED void const *UNUSED(src), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode), struct aio_multihandle *__restrict UNUSED(aio)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.areadv") size_t KCALL handle_undefined_areadv(void *__restrict UNUSED(ptr), struct aio_buffer *__restrict UNUSED(dst), size_t UNUSED(num_bytes), iomode_t UNUSED(mode), struct aio_multihandle *__restrict UNUSED(aio)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.awritev") size_t KCALL handle_undefined_awritev(void *__restrict UNUSED(ptr), struct aio_buffer *__restrict UNUSED(src), size_t UNUSED(num_bytes), iomode_t UNUSED(mode), struct aio_multihandle *__restrict UNUSED(aio)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.apreadv") size_t KCALL handle_undefined_apreadv(void *__restrict UNUSED(ptr), struct aio_buffer *__restrict UNUSED(dst), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode), struct aio_multihandle *__restrict UNUSED(aio)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.apwritev") size_t KCALL handle_undefined_apwritev(void *__restrict UNUSED(ptr), struct aio_buffer *__restrict UNUSED(src), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode), struct aio_multihandle *__restrict UNUSED(aio)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.readdir") size_t KCALL handle_undefined_readdir(void *__restrict UNUSED(ptr), USER CHECKED struct dirent *UNUSED(buf), size_t UNUSED(bufsize), readdir_mode_t UNUSED(readdir_mode), iomode_t UNUSED(mode)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READDIR); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.seek") pos_t KCALL handle_undefined_seek(void *__restrict UNUSED(ptr), off_t UNUSED(offset), unsigned int UNUSED(whence)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SEEK); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.ioctl") syscall_slong_t KCALL handle_undefined_ioctl(void *__restrict UNUSED(ptr), syscall_ulong_t cmd, USER UNCHECKED void *UNUSED(arg), iomode_t UNUSED(mode)) { THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND, cmd); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.truncate") void KCALL handle_undefined_truncate(void *__restrict UNUSED(ptr), pos_t UNUSED(new_size)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_TRUNC); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.mmap") REF struct vm_datablock *KCALL handle_undefined_mmap(void *__restrict UNUSED(ptr), vm_vpage64_t *__restrict UNUSED(pminpage), vm_vpage64_t *__restrict UNUSED(pmaxpage)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_MMAP); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.allocate") pos_t KCALL handle_undefined_allocate(void *__restrict UNUSED(ptr), fallocate_mode_t UNUSED(mode), pos_t UNUSED(start), pos_t UNUSED(length)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_ALLOCATE); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.sync") void KCALL handle_undefined_sync(void *__restrict UNUSED(ptr)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SYNC); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.datasync") void KCALL handle_undefined_datasync(void *__restrict UNUSED(ptr)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_DATASYNC); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.stat") void KCALL handle_undefined_stat(void *__restrict UNUSED(ptr), USER CHECKED struct stat *UNUSED(result)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_STAT); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.poll") poll_mode_t KCALL handle_undefined_poll(void *__restrict UNUSED(ptr), poll_mode_t UNUSED(what)) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_POLL); }
INTERN ATTR_SECTION(".text.kernel.handle_undefined.hop") syscall_slong_t KCALL handle_undefined_hop(void *__restrict UNUSED(ptr), syscall_ulong_t cmd, USER UNCHECKED void *UNUSED(arg), iomode_t UNUSED(mode)) { THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND, cmd); }
INTDEF NOBLOCK void NOTHROW(FCALL handle_datablock_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_datablock_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_datablock_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_datablock_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_datablock_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_datablock_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_datablock_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_datablock_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_datablock_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_datablock_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_datablock_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_datablock_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_datablock_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_datablock_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_datablock_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_datablock_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_datablock_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_datablock_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_datablock_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_datablock_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_datablock_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_datablock_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_datablock_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_datablock_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_datablock_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_datablock_sync(void *__restrict ptr);
INTDEF void KCALL handle_datablock_datasync(void *__restrict ptr);
INTDEF void KCALL handle_datablock_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_datablock_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_datablock_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_blockdevice_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_blockdevice_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_blockdevice_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_blockdevice_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_blockdevice_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_blockdevice_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_blockdevice_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_blockdevice_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_blockdevice_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_blockdevice_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_blockdevice_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_blockdevice_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_blockdevice_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_blockdevice_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_blockdevice_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_blockdevice_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_blockdevice_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_blockdevice_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_blockdevice_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_blockdevice_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_blockdevice_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_blockdevice_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_blockdevice_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_blockdevice_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_blockdevice_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_blockdevice_sync(void *__restrict ptr);
INTDEF void KCALL handle_blockdevice_datasync(void *__restrict ptr);
INTDEF void KCALL handle_blockdevice_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_blockdevice_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_blockdevice_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_directoryentry_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_directoryentry_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_directoryentry_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_directoryentry_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_directoryentry_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_directoryentry_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_directoryentry_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_directoryentry_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_directoryentry_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_directoryentry_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_directoryentry_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_directoryentry_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_directoryentry_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_directoryentry_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_directoryentry_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_directoryentry_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_directoryentry_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_directoryentry_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_directoryentry_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_directoryentry_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_directoryentry_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_directoryentry_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_directoryentry_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_directoryentry_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_directoryentry_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_directoryentry_sync(void *__restrict ptr);
INTDEF void KCALL handle_directoryentry_datasync(void *__restrict ptr);
INTDEF void KCALL handle_directoryentry_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_directoryentry_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_directoryentry_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_file_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_file_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_file_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_file_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_file_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_file_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_file_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_file_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_file_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_file_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_file_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_file_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_file_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_file_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_file_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_file_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_file_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_file_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_file_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_file_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_file_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_file_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_file_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_file_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_file_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_file_sync(void *__restrict ptr);
INTDEF void KCALL handle_file_datasync(void *__restrict ptr);
INTDEF void KCALL handle_file_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_file_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_file_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_oneshot_directory_file_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_oneshot_directory_file_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_oneshot_directory_file_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_oneshot_directory_file_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_oneshot_directory_file_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_oneshot_directory_file_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_oneshot_directory_file_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_oneshot_directory_file_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_oneshot_directory_file_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_oneshot_directory_file_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_oneshot_directory_file_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_oneshot_directory_file_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_oneshot_directory_file_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_oneshot_directory_file_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_oneshot_directory_file_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_oneshot_directory_file_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_oneshot_directory_file_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_oneshot_directory_file_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_oneshot_directory_file_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_oneshot_directory_file_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_oneshot_directory_file_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_oneshot_directory_file_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_oneshot_directory_file_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_oneshot_directory_file_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_oneshot_directory_file_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_oneshot_directory_file_sync(void *__restrict ptr);
INTDEF void KCALL handle_oneshot_directory_file_datasync(void *__restrict ptr);
INTDEF void KCALL handle_oneshot_directory_file_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_oneshot_directory_file_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_oneshot_directory_file_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_path_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_path_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_path_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_path_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_path_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_path_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_path_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_path_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_path_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_path_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_path_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_path_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_path_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_path_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_path_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_path_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_path_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_path_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_path_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_path_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_path_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_path_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_path_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_path_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_path_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_path_sync(void *__restrict ptr);
INTDEF void KCALL handle_path_datasync(void *__restrict ptr);
INTDEF void KCALL handle_path_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_path_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_path_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_fs_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_fs_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_fs_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_fs_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_fs_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_fs_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_fs_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_fs_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_fs_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_fs_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_fs_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_fs_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_fs_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_fs_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_fs_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_fs_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_fs_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_fs_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_fs_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_fs_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_fs_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_fs_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_fs_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_fs_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_fs_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_fs_sync(void *__restrict ptr);
INTDEF void KCALL handle_fs_datasync(void *__restrict ptr);
INTDEF void KCALL handle_fs_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_fs_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_fs_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_vm_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_vm_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_vm_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_vm_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_vm_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_vm_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_vm_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_vm_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_vm_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_vm_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_vm_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_vm_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_vm_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_vm_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_vm_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_vm_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_vm_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_vm_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_vm_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_vm_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_vm_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_vm_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_vm_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_vm_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_vm_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_vm_sync(void *__restrict ptr);
INTDEF void KCALL handle_vm_datasync(void *__restrict ptr);
INTDEF void KCALL handle_vm_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_vm_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_vm_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_task_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_task_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_task_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_task_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_task_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_task_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_task_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_task_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_task_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_task_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_task_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_task_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_task_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_task_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_task_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_task_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_task_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_task_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_task_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_task_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_task_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_task_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_task_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_task_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_task_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_task_sync(void *__restrict ptr);
INTDEF void KCALL handle_task_datasync(void *__restrict ptr);
INTDEF void KCALL handle_task_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_task_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_task_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_clock_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_clock_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_clock_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_clock_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_clock_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_clock_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_clock_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_clock_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_clock_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_clock_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_clock_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_clock_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_clock_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_clock_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_clock_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_clock_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_clock_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_clock_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_clock_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_clock_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_clock_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_clock_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_clock_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_clock_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_clock_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_clock_sync(void *__restrict ptr);
INTDEF void KCALL handle_clock_datasync(void *__restrict ptr);
INTDEF void KCALL handle_clock_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_clock_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_clock_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_driver_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_driver_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_driver_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_driver_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_driver_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_driver_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_driver_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_driver_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_driver_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_driver_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_driver_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_driver_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_driver_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_driver_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_driver_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_driver_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_driver_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_driver_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_driver_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_driver_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_driver_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_driver_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_driver_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_driver_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_driver_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_driver_sync(void *__restrict ptr);
INTDEF void KCALL handle_driver_datasync(void *__restrict ptr);
INTDEF void KCALL handle_driver_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_driver_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_driver_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_pipe_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_pipe_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_pipe_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_pipe_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_pipe_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_pipe_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_pipe_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_pipe_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_pipe_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_pipe_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_pipe_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_pipe_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_pipe_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_pipe_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_pipe_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_pipe_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_pipe_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_pipe_sync(void *__restrict ptr);
INTDEF void KCALL handle_pipe_datasync(void *__restrict ptr);
INTDEF void KCALL handle_pipe_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_pipe_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_pipe_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_pipe_reader_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_pipe_reader_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_pipe_reader_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_pipe_reader_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_pipe_reader_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_pipe_reader_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_pipe_reader_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_pipe_reader_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_pipe_reader_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_pipe_reader_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_pipe_reader_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_pipe_reader_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_reader_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_reader_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_reader_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_reader_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_reader_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_reader_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_reader_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_reader_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_pipe_reader_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_pipe_reader_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_pipe_reader_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_pipe_reader_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_pipe_reader_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_pipe_reader_sync(void *__restrict ptr);
INTDEF void KCALL handle_pipe_reader_datasync(void *__restrict ptr);
INTDEF void KCALL handle_pipe_reader_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_pipe_reader_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_pipe_reader_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_pipe_writer_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_pipe_writer_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_pipe_writer_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_pipe_writer_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_pipe_writer_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_pipe_writer_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_pipe_writer_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_pipe_writer_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_pipe_writer_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_pipe_writer_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_pipe_writer_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_pipe_writer_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_writer_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_writer_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_writer_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_writer_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_writer_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_writer_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_writer_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pipe_writer_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_pipe_writer_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_pipe_writer_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_pipe_writer_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_pipe_writer_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_pipe_writer_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_pipe_writer_sync(void *__restrict ptr);
INTDEF void KCALL handle_pipe_writer_datasync(void *__restrict ptr);
INTDEF void KCALL handle_pipe_writer_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_pipe_writer_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_pipe_writer_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_pidns_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_pidns_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_pidns_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_pidns_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_pidns_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_pidns_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_pidns_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_pidns_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_pidns_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_pidns_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_pidns_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_pidns_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pidns_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pidns_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pidns_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pidns_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pidns_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pidns_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pidns_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_pidns_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_pidns_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_pidns_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_pidns_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_pidns_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_pidns_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_pidns_sync(void *__restrict ptr);
INTDEF void KCALL handle_pidns_datasync(void *__restrict ptr);
INTDEF void KCALL handle_pidns_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_pidns_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_pidns_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_driver_state_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_driver_state_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_driver_state_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_driver_state_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_driver_state_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_driver_state_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_driver_state_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_driver_state_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_driver_state_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_driver_state_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_driver_state_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_driver_state_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_driver_state_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_driver_state_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_driver_state_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_driver_state_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_driver_state_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_driver_state_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_driver_state_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_driver_state_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_driver_state_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_driver_state_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_driver_state_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_driver_state_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_driver_state_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_driver_state_sync(void *__restrict ptr);
INTDEF void KCALL handle_driver_state_datasync(void *__restrict ptr);
INTDEF void KCALL handle_driver_state_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_driver_state_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_driver_state_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_characterdevice_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_characterdevice_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_characterdevice_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_characterdevice_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_characterdevice_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_characterdevice_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_characterdevice_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_characterdevice_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_characterdevice_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_characterdevice_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_characterdevice_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_characterdevice_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_characterdevice_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_characterdevice_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_characterdevice_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_characterdevice_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_characterdevice_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_characterdevice_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_characterdevice_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_characterdevice_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_characterdevice_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_characterdevice_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_characterdevice_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_characterdevice_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_characterdevice_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_characterdevice_sync(void *__restrict ptr);
INTDEF void KCALL handle_characterdevice_datasync(void *__restrict ptr);
INTDEF void KCALL handle_characterdevice_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_characterdevice_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_characterdevice_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_eventfd_fence_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_eventfd_fence_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_eventfd_fence_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_eventfd_fence_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_eventfd_fence_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_eventfd_fence_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_eventfd_fence_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_eventfd_fence_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_eventfd_fence_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_eventfd_fence_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_eventfd_fence_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_eventfd_fence_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_eventfd_fence_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_eventfd_fence_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_eventfd_fence_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_eventfd_fence_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_eventfd_fence_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_eventfd_fence_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_eventfd_fence_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_eventfd_fence_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_eventfd_fence_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_eventfd_fence_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_eventfd_fence_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_eventfd_fence_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_eventfd_fence_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_eventfd_fence_sync(void *__restrict ptr);
INTDEF void KCALL handle_eventfd_fence_datasync(void *__restrict ptr);
INTDEF void KCALL handle_eventfd_fence_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_eventfd_fence_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_eventfd_fence_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_eventfd_sema_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_eventfd_sema_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_eventfd_sema_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_eventfd_sema_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_eventfd_sema_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_eventfd_sema_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_eventfd_sema_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_eventfd_sema_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_eventfd_sema_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_eventfd_sema_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_eventfd_sema_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_eventfd_sema_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_eventfd_sema_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_eventfd_sema_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_eventfd_sema_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_eventfd_sema_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_eventfd_sema_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_eventfd_sema_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_eventfd_sema_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_eventfd_sema_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_eventfd_sema_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_eventfd_sema_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_eventfd_sema_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_eventfd_sema_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_eventfd_sema_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_eventfd_sema_sync(void *__restrict ptr);
INTDEF void KCALL handle_eventfd_sema_datasync(void *__restrict ptr);
INTDEF void KCALL handle_eventfd_sema_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_eventfd_sema_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_eventfd_sema_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF NOBLOCK void NOTHROW(FCALL handle_signalfd_incref)(void *__restrict ptr);
INTDEF NOBLOCK void NOTHROW(FCALL handle_signalfd_decref)(void *__restrict ptr);
INTDEF NOBLOCK refcnt_t NOTHROW(FCALL handle_signalfd_refcnt)(void *__restrict ptr);
INTDEF size_t KCALL handle_signalfd_read(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_signalfd_write(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_signalfd_pread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_signalfd_pwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_signalfd_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_signalfd_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode);
INTDEF size_t KCALL handle_signalfd_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_signalfd_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode);
INTDEF size_t KCALL handle_signalfd_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_signalfd_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_signalfd_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_signalfd_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_signalfd_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_signalfd_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_signalfd_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_signalfd_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio);
INTDEF size_t KCALL handle_signalfd_readdir(void *__restrict ptr, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode);
INTDEF pos_t KCALL handle_signalfd_seek(void *__restrict ptr, off_t offset, unsigned int whence);
INTDEF syscall_slong_t KCALL handle_signalfd_ioctl(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);
INTDEF void KCALL handle_signalfd_truncate(void *__restrict ptr, pos_t new_size);
INTDEF REF struct vm_datablock *KCALL handle_signalfd_mmap(void *__restrict ptr, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage);
INTDEF pos_t KCALL handle_signalfd_allocate(void *__restrict ptr, fallocate_mode_t mode, pos_t start, pos_t length);
INTDEF void KCALL handle_signalfd_sync(void *__restrict ptr);
INTDEF void KCALL handle_signalfd_datasync(void *__restrict ptr);
INTDEF void KCALL handle_signalfd_stat(void *__restrict ptr, USER CHECKED struct stat *result);
INTDEF poll_mode_t KCALL handle_signalfd_poll(void *__restrict ptr, poll_mode_t what);
INTDEF syscall_slong_t KCALL handle_signalfd_hop(void *__restrict ptr, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode);

PUBLIC_CONST struct handle_types const handle_type_db = {
	/* .h_typename = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */"undefined",
		/* [HANDLE_TYPE_DATABLOCK]              = */"datablock",
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */"blockdevice",
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */"directoryentry",
		/* [HANDLE_TYPE_FILE]                   = */"file",
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */"oneshot_directory_file",
		/* [HANDLE_TYPE_PATH]                   = */"path",
		/* [HANDLE_TYPE_FS]                     = */"fs",
		/* [HANDLE_TYPE_VM]                     = */"vm",
		/* [HANDLE_TYPE_TASK]                   = */"task",
		/* [HANDLE_TYPE_CLOCK]                  = */"clock",
		/* [HANDLE_TYPE_DRIVER]                 = */"driver",
		/* [HANDLE_TYPE_PIPE]                   = */"pipe",
		/* [HANDLE_TYPE_PIPE_READER]            = */"pipe_reader",
		/* [HANDLE_TYPE_PIPE_WRITER]            = */"pipe_writer",
		/* [HANDLE_TYPE_PIDNS]                  = */"pidns",
		/* [HANDLE_TYPE_DRIVER_STATE]           = */"driver_state",
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */"characterdevice",
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */"eventfd_fence",
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */"eventfd_sema",
		/* [HANDLE_TYPE_SIGNALFD]               = */"signalfd"
	},
	/* .h_incref = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_incref,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_incref,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_incref,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_incref,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_incref,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_incref,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_incref,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_incref,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_incref,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_incref,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_incref,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_incref,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_incref,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_incref,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_incref,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_incref,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_incref,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_incref,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_incref,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_incref,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_incref
	},
	/* .h_decref = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_decref,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_decref,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_decref,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_decref,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_decref,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_decref,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_decref,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_decref,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_decref,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_decref,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_decref,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_decref,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_decref,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_decref,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_decref,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_decref,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_decref,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_decref,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_decref,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_decref,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_decref
	},
	/* .h_refcnt = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_refcnt,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_refcnt,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_refcnt,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_refcnt,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_refcnt,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_refcnt,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_refcnt,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_refcnt,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_refcnt,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_refcnt,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_refcnt,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_refcnt,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_refcnt,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_refcnt,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_refcnt,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_refcnt,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_refcnt,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_refcnt,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_refcnt,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_refcnt,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_refcnt
	},
	/* .h_read = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_read,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_read,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_read,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_read,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_read,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_read,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_read,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_read,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_read,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_read,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_read,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_read,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_read,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_read,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_read,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_read,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_read,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_read,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_read,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_read,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_read
	},
	/* .h_write = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_write,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_write,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_write,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_write,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_write,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_write,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_write,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_write,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_write,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_write,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_write,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_write,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_write,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_write,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_write,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_write,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_write,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_write,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_write,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_write,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_write
	},
	/* .h_pread = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_pread,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_pread,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_pread,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_pread,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_pread,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_pread,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_pread,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_pread,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_pread,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_pread,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_pread,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_pread,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_pread,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_pread,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_pread,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_pread,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_pread,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_pread,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_pread,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_pread,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_pread
	},
	/* .h_pwrite = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_pwrite,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_pwrite,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_pwrite,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_pwrite,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_pwrite,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_pwrite,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_pwrite,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_pwrite,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_pwrite,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_pwrite,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_pwrite,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_pwrite,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_pwrite,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_pwrite,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_pwrite,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_pwrite,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_pwrite,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_pwrite,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_pwrite,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_pwrite,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_pwrite
	},
	/* .h_readv = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_readv,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_readv,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_readv,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_readv,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_readv,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_readv,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_readv,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_readv,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_readv,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_readv,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_readv,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_readv,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_readv,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_readv,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_readv,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_readv,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_readv,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_readv,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_readv,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_readv,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_readv
	},
	/* .h_writev = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_writev,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_writev,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_writev,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_writev,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_writev,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_writev,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_writev,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_writev,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_writev,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_writev,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_writev,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_writev,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_writev,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_writev,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_writev,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_writev,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_writev,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_writev,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_writev,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_writev,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_writev
	},
	/* .h_preadv = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_preadv,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_preadv,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_preadv,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_preadv,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_preadv,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_preadv,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_preadv,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_preadv,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_preadv,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_preadv,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_preadv,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_preadv,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_preadv,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_preadv,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_preadv,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_preadv,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_preadv,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_preadv,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_preadv,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_preadv,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_preadv
	},
	/* .h_pwritev = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_pwritev,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_pwritev,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_pwritev,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_pwritev,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_pwritev,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_pwritev,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_pwritev,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_pwritev,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_pwritev,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_pwritev,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_pwritev,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_pwritev,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_pwritev,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_pwritev,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_pwritev,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_pwritev,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_pwritev,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_pwritev,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_pwritev,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_pwritev,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_pwritev
	},
	/* .h_aread = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_aread,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_aread,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_aread,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_aread,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_aread,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_aread,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_aread,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_aread,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_aread,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_aread,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_aread,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_aread,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_aread,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_aread,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_aread,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_aread,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_aread,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_aread,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_aread,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_aread,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_aread
	},
	/* .h_awrite = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_awrite,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_awrite,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_awrite,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_awrite,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_awrite,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_awrite,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_awrite,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_awrite,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_awrite,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_awrite,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_awrite,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_awrite,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_awrite,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_awrite,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_awrite,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_awrite,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_awrite,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_awrite,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_awrite,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_awrite,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_awrite
	},
	/* .h_apread = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_apread,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_apread,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_apread,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_apread,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_apread,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_apread,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_apread,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_apread,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_apread,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_apread,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_apread,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_apread,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_apread,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_apread,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_apread,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_apread,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_apread,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_apread,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_apread,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_apread,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_apread
	},
	/* .h_apwrite = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_apwrite,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_apwrite,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_apwrite,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_apwrite,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_apwrite,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_apwrite,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_apwrite,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_apwrite,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_apwrite,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_apwrite,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_apwrite,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_apwrite,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_apwrite,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_apwrite,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_apwrite,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_apwrite,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_apwrite,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_apwrite,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_apwrite,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_apwrite,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_apwrite
	},
	/* .h_areadv = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_areadv,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_areadv,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_areadv,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_areadv,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_areadv,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_areadv,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_areadv,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_areadv,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_areadv,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_areadv,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_areadv,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_areadv,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_areadv,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_areadv,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_areadv,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_areadv,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_areadv,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_areadv,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_areadv,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_areadv,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_areadv
	},
	/* .h_awritev = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_awritev,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_awritev,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_awritev,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_awritev,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_awritev,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_awritev,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_awritev,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_awritev,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_awritev,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_awritev,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_awritev,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_awritev,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_awritev,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_awritev,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_awritev,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_awritev,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_awritev,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_awritev,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_awritev,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_awritev,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_awritev
	},
	/* .h_apreadv = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_apreadv,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_apreadv,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_apreadv,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_apreadv,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_apreadv,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_apreadv,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_apreadv,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_apreadv,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_apreadv,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_apreadv,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_apreadv,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_apreadv,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_apreadv,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_apreadv,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_apreadv,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_apreadv,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_apreadv,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_apreadv,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_apreadv,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_apreadv,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_apreadv
	},
	/* .h_apwritev = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_apwritev,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_apwritev,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_apwritev,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_apwritev,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_apwritev,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_apwritev,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_apwritev,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_apwritev,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_apwritev,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_apwritev,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_apwritev,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_apwritev,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_apwritev,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_apwritev,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_apwritev,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_apwritev,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_apwritev,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_apwritev,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_apwritev,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_apwritev,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_apwritev
	},
	/* .h_readdir = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_readdir,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_readdir,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_readdir,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_readdir,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_readdir,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_readdir,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_readdir,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_readdir,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_readdir,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_readdir,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_readdir,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_readdir,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_readdir,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_readdir,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_readdir,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_readdir,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_readdir,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_readdir,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_readdir,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_readdir,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_readdir
	},
	/* .h_seek = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_seek,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_seek,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_seek,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_seek,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_seek,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_seek,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_seek,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_seek,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_seek,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_seek,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_seek,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_seek,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_seek,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_seek,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_seek,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_seek,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_seek,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_seek,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_seek,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_seek,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_seek
	},
	/* .h_ioctl = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_ioctl,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_ioctl,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_ioctl,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_ioctl,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_ioctl,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_ioctl,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_ioctl,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_ioctl,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_ioctl,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_ioctl,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_ioctl,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_ioctl,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_ioctl,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_ioctl,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_ioctl,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_ioctl,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_ioctl,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_ioctl,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_ioctl,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_ioctl,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_ioctl
	},
	/* .h_truncate = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_truncate,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_truncate,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_truncate,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_truncate,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_truncate,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_truncate,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_truncate,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_truncate,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_truncate,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_truncate,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_truncate,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_truncate,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_truncate,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_truncate,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_truncate,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_truncate,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_truncate,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_truncate,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_truncate,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_truncate,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_truncate
	},
	/* .h_mmap = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_mmap,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_mmap,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_mmap,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_mmap,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_mmap,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_mmap,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_mmap,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_mmap,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_mmap,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_mmap,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_mmap,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_mmap,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_mmap,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_mmap,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_mmap,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_mmap,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_mmap,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_mmap,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_mmap,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_mmap,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_mmap
	},
	/* .h_allocate = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_allocate,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_allocate,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_allocate,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_allocate,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_allocate,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_allocate,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_allocate,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_allocate,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_allocate,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_allocate,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_allocate,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_allocate,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_allocate,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_allocate,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_allocate,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_allocate,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_allocate,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_allocate,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_allocate,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_allocate,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_allocate
	},
	/* .h_sync = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_sync,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_sync,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_sync,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_sync,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_sync,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_sync,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_sync,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_sync,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_sync,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_sync,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_sync,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_sync,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_sync,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_sync,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_sync,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_sync,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_sync,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_sync,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_sync,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_sync,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_sync
	},
	/* .h_datasync = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_datasync,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_datasync,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_datasync,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_datasync,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_datasync,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_datasync,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_datasync,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_datasync,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_datasync,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_datasync,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_datasync,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_datasync,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_datasync,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_datasync,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_datasync,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_datasync,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_datasync,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_datasync,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_datasync,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_datasync,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_datasync
	},
	/* .h_stat = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_stat,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_stat,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_stat,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_stat,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_stat,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_stat,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_stat,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_stat,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_stat,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_stat,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_stat,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_stat,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_stat,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_stat,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_stat,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_stat,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_stat,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_stat,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_stat,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_stat,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_stat
	},
	/* .h_poll = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_poll,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_poll,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_poll,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_poll,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_poll,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_poll,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_poll,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_poll,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_poll,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_poll,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_poll,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_poll,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_poll,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_poll,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_poll,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_poll,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_poll,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_poll,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_poll,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_poll,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_poll
	},
	/* .h_hop = */{
		/* [HANDLE_TYPE_UNDEFINED]              = */&handle_undefined_hop,
		/* [HANDLE_TYPE_DATABLOCK]              = */&handle_datablock_hop,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */&handle_blockdevice_hop,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */&handle_directoryentry_hop,
		/* [HANDLE_TYPE_FILE]                   = */&handle_file_hop,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */&handle_oneshot_directory_file_hop,
		/* [HANDLE_TYPE_PATH]                   = */&handle_path_hop,
		/* [HANDLE_TYPE_FS]                     = */&handle_fs_hop,
		/* [HANDLE_TYPE_VM]                     = */&handle_vm_hop,
		/* [HANDLE_TYPE_TASK]                   = */&handle_task_hop,
		/* [HANDLE_TYPE_CLOCK]                  = */&handle_clock_hop,
		/* [HANDLE_TYPE_DRIVER]                 = */&handle_driver_hop,
		/* [HANDLE_TYPE_PIPE]                   = */&handle_pipe_hop,
		/* [HANDLE_TYPE_PIPE_READER]            = */&handle_pipe_reader_hop,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */&handle_pipe_writer_hop,
		/* [HANDLE_TYPE_PIDNS]                  = */&handle_pidns_hop,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */&handle_driver_state_hop,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */&handle_characterdevice_hop,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */&handle_eventfd_fence_hop,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */&handle_eventfd_sema_hop,
		/* [HANDLE_TYPE_SIGNALFD]               = */&handle_signalfd_hop
	}
};

DEFINE_INTERN_WEAK_ALIAS(handle_datablock_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_file_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_file_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_file_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_file_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_file_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_file_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_file_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_file_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_file_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_file_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_file_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_file_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_file_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_file_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_file_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_file_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_file_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_file_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_path_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_path_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_path_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_path_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_path_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_path_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_path_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_path_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_path_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_path_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_path_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_path_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_path_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_path_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_path_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_path_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_path_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_path_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_task_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_task_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_task_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_task_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_task_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_task_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_task_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_task_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_task_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_task_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_task_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_task_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_task_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_task_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_task_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_task_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_task_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_task_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_hop, handle_undefined_hop);
INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.datablock.readv") size_t KCALL
handle_datablock_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_datablock_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.datablock.writev") size_t KCALL
handle_datablock_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_datablock_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.datablock.preadv") size_t KCALL
handle_datablock_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_datablock_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.datablock.pwritev") size_t KCALL
handle_datablock_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_datablock_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.datablock.aread") size_t KCALL
handle_datablock_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_datablock_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.datablock.awrite") size_t KCALL
handle_datablock_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_datablock_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.datablock.apread") size_t KCALL
handle_datablock_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_datablock_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.datablock.apwrite") size_t KCALL
handle_datablock_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_datablock_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.datablock.areadv") size_t KCALL
handle_datablock_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_datablock_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.datablock.awritev") size_t KCALL
handle_datablock_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_datablock_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.datablock.apreadv") size_t KCALL
handle_datablock_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_datablock_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.datablock.apwritev") size_t KCALL
handle_datablock_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_datablock_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.blockdevice.readv") size_t KCALL
handle_blockdevice_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_blockdevice_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.blockdevice.writev") size_t KCALL
handle_blockdevice_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_blockdevice_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.blockdevice.preadv") size_t KCALL
handle_blockdevice_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_blockdevice_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.blockdevice.pwritev") size_t KCALL
handle_blockdevice_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_blockdevice_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.blockdevice.aread") size_t KCALL
handle_blockdevice_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_blockdevice_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.blockdevice.awrite") size_t KCALL
handle_blockdevice_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_blockdevice_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.blockdevice.apread") size_t KCALL
handle_blockdevice_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_blockdevice_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.blockdevice.apwrite") size_t KCALL
handle_blockdevice_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_blockdevice_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.blockdevice.areadv") size_t KCALL
handle_blockdevice_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_blockdevice_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.blockdevice.awritev") size_t KCALL
handle_blockdevice_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_blockdevice_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.blockdevice.apreadv") size_t KCALL
handle_blockdevice_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_blockdevice_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.blockdevice.apwritev") size_t KCALL
handle_blockdevice_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_blockdevice_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.directoryentry.readv") size_t KCALL
handle_directoryentry_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_directoryentry_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.directoryentry.writev") size_t KCALL
handle_directoryentry_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_directoryentry_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.directoryentry.preadv") size_t KCALL
handle_directoryentry_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_directoryentry_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.directoryentry.pwritev") size_t KCALL
handle_directoryentry_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_directoryentry_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.directoryentry.aread") size_t KCALL
handle_directoryentry_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_directoryentry_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.directoryentry.awrite") size_t KCALL
handle_directoryentry_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_directoryentry_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.directoryentry.apread") size_t KCALL
handle_directoryentry_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_directoryentry_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.directoryentry.apwrite") size_t KCALL
handle_directoryentry_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_directoryentry_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.directoryentry.areadv") size_t KCALL
handle_directoryentry_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_directoryentry_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.directoryentry.awritev") size_t KCALL
handle_directoryentry_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_directoryentry_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.directoryentry.apreadv") size_t KCALL
handle_directoryentry_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_directoryentry_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.directoryentry.apwritev") size_t KCALL
handle_directoryentry_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_directoryentry_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.file.readv") size_t KCALL
handle_file_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_file_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.file.writev") size_t KCALL
handle_file_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_file_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.file.preadv") size_t KCALL
handle_file_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_file_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.file.pwritev") size_t KCALL
handle_file_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_file_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.file.aread") size_t KCALL
handle_file_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_file_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.file.awrite") size_t KCALL
handle_file_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_file_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.file.apread") size_t KCALL
handle_file_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_file_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.file.apwrite") size_t KCALL
handle_file_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_file_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.file.areadv") size_t KCALL
handle_file_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_file_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.file.awritev") size_t KCALL
handle_file_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_file_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.file.apreadv") size_t KCALL
handle_file_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_file_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.file.apwritev") size_t KCALL
handle_file_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_file_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.oneshot_directory_file.readv") size_t KCALL
handle_oneshot_directory_file_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_oneshot_directory_file_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.oneshot_directory_file.writev") size_t KCALL
handle_oneshot_directory_file_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_oneshot_directory_file_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.oneshot_directory_file.preadv") size_t KCALL
handle_oneshot_directory_file_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_oneshot_directory_file_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.oneshot_directory_file.pwritev") size_t KCALL
handle_oneshot_directory_file_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_oneshot_directory_file_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.oneshot_directory_file.aread") size_t KCALL
handle_oneshot_directory_file_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_oneshot_directory_file_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.oneshot_directory_file.awrite") size_t KCALL
handle_oneshot_directory_file_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_oneshot_directory_file_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.oneshot_directory_file.apread") size_t KCALL
handle_oneshot_directory_file_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_oneshot_directory_file_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.oneshot_directory_file.apwrite") size_t KCALL
handle_oneshot_directory_file_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_oneshot_directory_file_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.oneshot_directory_file.areadv") size_t KCALL
handle_oneshot_directory_file_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_oneshot_directory_file_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.oneshot_directory_file.awritev") size_t KCALL
handle_oneshot_directory_file_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_oneshot_directory_file_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.oneshot_directory_file.apreadv") size_t KCALL
handle_oneshot_directory_file_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_oneshot_directory_file_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.oneshot_directory_file.apwritev") size_t KCALL
handle_oneshot_directory_file_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_oneshot_directory_file_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.path.readv") size_t KCALL
handle_path_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_path_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.path.writev") size_t KCALL
handle_path_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_path_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.path.preadv") size_t KCALL
handle_path_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_path_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.path.pwritev") size_t KCALL
handle_path_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_path_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.path.aread") size_t KCALL
handle_path_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_path_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.path.awrite") size_t KCALL
handle_path_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_path_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.path.apread") size_t KCALL
handle_path_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_path_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.path.apwrite") size_t KCALL
handle_path_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_path_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.path.areadv") size_t KCALL
handle_path_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_path_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.path.awritev") size_t KCALL
handle_path_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_path_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.path.apreadv") size_t KCALL
handle_path_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_path_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.path.apwritev") size_t KCALL
handle_path_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_path_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.fs.readv") size_t KCALL
handle_fs_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_fs_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.fs.writev") size_t KCALL
handle_fs_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_fs_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.fs.preadv") size_t KCALL
handle_fs_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_fs_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.fs.pwritev") size_t KCALL
handle_fs_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_fs_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.fs.aread") size_t KCALL
handle_fs_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_fs_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.fs.awrite") size_t KCALL
handle_fs_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_fs_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.fs.apread") size_t KCALL
handle_fs_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_fs_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.fs.apwrite") size_t KCALL
handle_fs_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_fs_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.fs.areadv") size_t KCALL
handle_fs_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_fs_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.fs.awritev") size_t KCALL
handle_fs_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_fs_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.fs.apreadv") size_t KCALL
handle_fs_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_fs_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.fs.apwritev") size_t KCALL
handle_fs_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_fs_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.vm.readv") size_t KCALL
handle_vm_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_vm_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.vm.writev") size_t KCALL
handle_vm_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_vm_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.vm.preadv") size_t KCALL
handle_vm_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_vm_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.vm.pwritev") size_t KCALL
handle_vm_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_vm_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.vm.aread") size_t KCALL
handle_vm_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_vm_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.vm.awrite") size_t KCALL
handle_vm_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_vm_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.vm.apread") size_t KCALL
handle_vm_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_vm_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.vm.apwrite") size_t KCALL
handle_vm_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_vm_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.vm.areadv") size_t KCALL
handle_vm_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_vm_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.vm.awritev") size_t KCALL
handle_vm_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_vm_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.vm.apreadv") size_t KCALL
handle_vm_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_vm_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.vm.apwritev") size_t KCALL
handle_vm_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_vm_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.task.readv") size_t KCALL
handle_task_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_task_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.task.writev") size_t KCALL
handle_task_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_task_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.task.preadv") size_t KCALL
handle_task_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_task_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.task.pwritev") size_t KCALL
handle_task_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_task_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.task.aread") size_t KCALL
handle_task_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_task_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.task.awrite") size_t KCALL
handle_task_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_task_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.task.apread") size_t KCALL
handle_task_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_task_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.task.apwrite") size_t KCALL
handle_task_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_task_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.task.areadv") size_t KCALL
handle_task_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_task_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.task.awritev") size_t KCALL
handle_task_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_task_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.task.apreadv") size_t KCALL
handle_task_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_task_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.task.apwritev") size_t KCALL
handle_task_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_task_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.clock.readv") size_t KCALL
handle_clock_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_clock_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.clock.writev") size_t KCALL
handle_clock_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_clock_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.clock.preadv") size_t KCALL
handle_clock_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_clock_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.clock.pwritev") size_t KCALL
handle_clock_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_clock_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.clock.aread") size_t KCALL
handle_clock_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_clock_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.clock.awrite") size_t KCALL
handle_clock_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_clock_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.clock.apread") size_t KCALL
handle_clock_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_clock_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.clock.apwrite") size_t KCALL
handle_clock_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_clock_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.clock.areadv") size_t KCALL
handle_clock_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_clock_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.clock.awritev") size_t KCALL
handle_clock_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_clock_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.clock.apreadv") size_t KCALL
handle_clock_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_clock_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.clock.apwritev") size_t KCALL
handle_clock_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_clock_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver.readv") size_t KCALL
handle_driver_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_driver_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver.writev") size_t KCALL
handle_driver_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_driver_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver.preadv") size_t KCALL
handle_driver_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_driver_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver.pwritev") size_t KCALL
handle_driver_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_driver_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver.aread") size_t KCALL
handle_driver_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_driver_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver.awrite") size_t KCALL
handle_driver_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_driver_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver.apread") size_t KCALL
handle_driver_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_driver_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver.apwrite") size_t KCALL
handle_driver_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_driver_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver.areadv") size_t KCALL
handle_driver_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_driver_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver.awritev") size_t KCALL
handle_driver_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_driver_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver.apreadv") size_t KCALL
handle_driver_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_driver_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver.apwritev") size_t KCALL
handle_driver_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_driver_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe.readv") size_t KCALL
handle_pipe_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_pipe_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe.writev") size_t KCALL
handle_pipe_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_pipe_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe.preadv") size_t KCALL
handle_pipe_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_pipe_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe.pwritev") size_t KCALL
handle_pipe_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_pipe_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe.aread") size_t KCALL
handle_pipe_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe.awrite") size_t KCALL
handle_pipe_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe.apread") size_t KCALL
handle_pipe_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe.apwrite") size_t KCALL
handle_pipe_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe.areadv") size_t KCALL
handle_pipe_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe.awritev") size_t KCALL
handle_pipe_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe.apreadv") size_t KCALL
handle_pipe_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe.apwritev") size_t KCALL
handle_pipe_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_reader.readv") size_t KCALL
handle_pipe_reader_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_pipe_reader_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_reader.writev") size_t KCALL
handle_pipe_reader_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_pipe_reader_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_reader.preadv") size_t KCALL
handle_pipe_reader_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_pipe_reader_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_reader.pwritev") size_t KCALL
handle_pipe_reader_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_pipe_reader_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_reader.aread") size_t KCALL
handle_pipe_reader_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_reader_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_reader.awrite") size_t KCALL
handle_pipe_reader_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_reader_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_reader.apread") size_t KCALL
handle_pipe_reader_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_reader_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_reader.apwrite") size_t KCALL
handle_pipe_reader_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_reader_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_reader.areadv") size_t KCALL
handle_pipe_reader_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_reader_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_reader.awritev") size_t KCALL
handle_pipe_reader_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_reader_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_reader.apreadv") size_t KCALL
handle_pipe_reader_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_reader_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_reader.apwritev") size_t KCALL
handle_pipe_reader_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_reader_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_writer.readv") size_t KCALL
handle_pipe_writer_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_pipe_writer_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_writer.writev") size_t KCALL
handle_pipe_writer_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_pipe_writer_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_writer.preadv") size_t KCALL
handle_pipe_writer_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_pipe_writer_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_writer.pwritev") size_t KCALL
handle_pipe_writer_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_pipe_writer_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_writer.aread") size_t KCALL
handle_pipe_writer_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_writer_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_writer.awrite") size_t KCALL
handle_pipe_writer_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_writer_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_writer.apread") size_t KCALL
handle_pipe_writer_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_writer_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_writer.apwrite") size_t KCALL
handle_pipe_writer_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_writer_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_writer.areadv") size_t KCALL
handle_pipe_writer_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_writer_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_writer.awritev") size_t KCALL
handle_pipe_writer_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_writer_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_writer.apreadv") size_t KCALL
handle_pipe_writer_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_writer_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pipe_writer.apwritev") size_t KCALL
handle_pipe_writer_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pipe_writer_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pidns.readv") size_t KCALL
handle_pidns_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_pidns_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pidns.writev") size_t KCALL
handle_pidns_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_pidns_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pidns.preadv") size_t KCALL
handle_pidns_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_pidns_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pidns.pwritev") size_t KCALL
handle_pidns_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_pidns_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pidns.aread") size_t KCALL
handle_pidns_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pidns_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pidns.awrite") size_t KCALL
handle_pidns_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pidns_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pidns.apread") size_t KCALL
handle_pidns_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pidns_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pidns.apwrite") size_t KCALL
handle_pidns_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pidns_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pidns.areadv") size_t KCALL
handle_pidns_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pidns_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pidns.awritev") size_t KCALL
handle_pidns_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pidns_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pidns.apreadv") size_t KCALL
handle_pidns_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pidns_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.pidns.apwritev") size_t KCALL
handle_pidns_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_pidns_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver_state.readv") size_t KCALL
handle_driver_state_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_driver_state_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver_state.writev") size_t KCALL
handle_driver_state_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_driver_state_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver_state.preadv") size_t KCALL
handle_driver_state_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_driver_state_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver_state.pwritev") size_t KCALL
handle_driver_state_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_driver_state_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver_state.aread") size_t KCALL
handle_driver_state_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_driver_state_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver_state.awrite") size_t KCALL
handle_driver_state_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_driver_state_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver_state.apread") size_t KCALL
handle_driver_state_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_driver_state_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver_state.apwrite") size_t KCALL
handle_driver_state_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_driver_state_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver_state.areadv") size_t KCALL
handle_driver_state_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_driver_state_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver_state.awritev") size_t KCALL
handle_driver_state_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_driver_state_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver_state.apreadv") size_t KCALL
handle_driver_state_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_driver_state_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.driver_state.apwritev") size_t KCALL
handle_driver_state_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_driver_state_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.characterdevice.readv") size_t KCALL
handle_characterdevice_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_characterdevice_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.characterdevice.writev") size_t KCALL
handle_characterdevice_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_characterdevice_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.characterdevice.preadv") size_t KCALL
handle_characterdevice_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_characterdevice_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.characterdevice.pwritev") size_t KCALL
handle_characterdevice_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_characterdevice_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.characterdevice.aread") size_t KCALL
handle_characterdevice_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_characterdevice_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.characterdevice.awrite") size_t KCALL
handle_characterdevice_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_characterdevice_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.characterdevice.apread") size_t KCALL
handle_characterdevice_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_characterdevice_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.characterdevice.apwrite") size_t KCALL
handle_characterdevice_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_characterdevice_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.characterdevice.areadv") size_t KCALL
handle_characterdevice_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_characterdevice_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.characterdevice.awritev") size_t KCALL
handle_characterdevice_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_characterdevice_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.characterdevice.apreadv") size_t KCALL
handle_characterdevice_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_characterdevice_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.characterdevice.apwritev") size_t KCALL
handle_characterdevice_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_characterdevice_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_fence.readv") size_t KCALL
handle_eventfd_fence_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_eventfd_fence_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_fence.writev") size_t KCALL
handle_eventfd_fence_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_eventfd_fence_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_fence.preadv") size_t KCALL
handle_eventfd_fence_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_eventfd_fence_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_fence.pwritev") size_t KCALL
handle_eventfd_fence_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_eventfd_fence_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_fence.aread") size_t KCALL
handle_eventfd_fence_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_eventfd_fence_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_fence.awrite") size_t KCALL
handle_eventfd_fence_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_eventfd_fence_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_fence.apread") size_t KCALL
handle_eventfd_fence_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_eventfd_fence_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_fence.apwrite") size_t KCALL
handle_eventfd_fence_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_eventfd_fence_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_fence.areadv") size_t KCALL
handle_eventfd_fence_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_eventfd_fence_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_fence.awritev") size_t KCALL
handle_eventfd_fence_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_eventfd_fence_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_fence.apreadv") size_t KCALL
handle_eventfd_fence_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_eventfd_fence_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_fence.apwritev") size_t KCALL
handle_eventfd_fence_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_eventfd_fence_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_sema.readv") size_t KCALL
handle_eventfd_sema_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_eventfd_sema_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_sema.writev") size_t KCALL
handle_eventfd_sema_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_eventfd_sema_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_sema.preadv") size_t KCALL
handle_eventfd_sema_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_eventfd_sema_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_sema.pwritev") size_t KCALL
handle_eventfd_sema_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_eventfd_sema_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_sema.aread") size_t KCALL
handle_eventfd_sema_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_eventfd_sema_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_sema.awrite") size_t KCALL
handle_eventfd_sema_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_eventfd_sema_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_sema.apread") size_t KCALL
handle_eventfd_sema_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_eventfd_sema_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_sema.apwrite") size_t KCALL
handle_eventfd_sema_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_eventfd_sema_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_sema.areadv") size_t KCALL
handle_eventfd_sema_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_eventfd_sema_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_sema.awritev") size_t KCALL
handle_eventfd_sema_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_eventfd_sema_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_sema.apreadv") size_t KCALL
handle_eventfd_sema_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_eventfd_sema_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.eventfd_sema.apwritev") size_t KCALL
handle_eventfd_sema_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_eventfd_sema_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.signalfd.readv") size_t KCALL
handle_signalfd_readv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_signalfd_read(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.signalfd.writev") size_t KCALL
handle_signalfd_writev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_signalfd_write(ptr, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.signalfd.preadv") size_t KCALL
handle_signalfd_preadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(dst) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_signalfd_pread(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.signalfd.pwritev") size_t KCALL
handle_signalfd_pwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	assert(aio_buffer_size(src) == num_bytes);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_signalfd_pwrite(ptr, ent.ab_base, ent.ab_size, addr, mode);
		result += temp;
		if (temp != ent.ab_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.signalfd.aread") size_t KCALL
handle_signalfd_aread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_signalfd_read(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.signalfd.awrite") size_t KCALL
handle_signalfd_awrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_signalfd_write(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.signalfd.apread") size_t KCALL
handle_signalfd_apread(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_signalfd_pread(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.signalfd.apwrite") size_t KCALL
handle_signalfd_apwrite(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_signalfd_pwrite(ptr, src, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.signalfd.areadv") size_t KCALL
handle_signalfd_areadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_signalfd_readv(ptr, dst, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.signalfd.awritev") size_t KCALL
handle_signalfd_awritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_signalfd_writev(ptr, src, num_bytes, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.signalfd.apreadv") size_t KCALL
handle_signalfd_apreadv(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_signalfd_preadv(ptr, dst, num_bytes, addr, mode);
	return result;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fallback.signalfd.apwritev") size_t KCALL
handle_signalfd_apwritev(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) {
	size_t result;
	(void)aio;
	result = handle_signalfd_pwritev(ptr, src, num_bytes, addr, mode);
	return result;
}
//[[[end]]]



DECL_END

#endif /* !GUARD_KERNEL_SRC_USER_HANDLE_C */
