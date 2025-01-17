/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_APPS_BUILD_CONFIG_C
#define GUARD_KERNEL_SRC_DEBUGGER_APPS_BUILD_CONFIG_C 1
#define _GNU_SOURCE 1
#define DISABLE_BRANCH_PROFILING

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/debugger.h>
#include <debugger/io.h>
#include <kernel/fs/notify-config.h> /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
#include <kernel/fs/super.h>
#include <kernel/malloc-defs.h>
#include <kernel/uname.h>

#include <kos/config/toolchain.h>

DECL_BEGIN


/* TODO: automatically generate from `kos/misc/config/options.dat' */
PRIVATE ATTR_DBGSTRINGS char const build_config[] =
"toolchain:\n"
"	binutils: " AC_WHITE(KOS_BUILD_CONFIG_TOOLCHAIN_BINUTILS_VERSION) "\n"
"	gcc:      " AC_WHITE(KOS_BUILD_CONFIG_TOOLCHAIN_GCC_VERSION) "\n"
"	host:     " AC_WHITE(KOS_BUILD_CONFIG_TOOLCHAIN_HOST) " (" AC_WHITE(KOS_BUILD_CONFIG_TOOLCHAIN_HOST_ROOT) ")\n"
"	build:    " AC_WHITE(KOS_BUILD_CONFIG_TOOLCHAIN_BUILD) "\n"
"	arch:     " AC_WHITE(KOS_BUILD_CONFIG_TOOLCHAIN_BUILD_ARCH) "\n"
"	cpu:      " AC_WHITE(KOS_BUILD_CONFIG_TOOLCHAIN_BUILD_CPU) "\n"
"	date:     " AC_WHITE(KOS_BUILD_CONFIG_TOOLCHAIN_DATE) "\n"
"defined:\n"
/*[[[deemon
local CONFIGS = {
	"NDEBUG",
	"__OPTIMIZE__",
	"CONFIG_HAVE_KERNEL_FS_NOTIFY",
	"CONFIG_HAVE_KERNEL_DEBUGGER",
	"?CONFIG_MAX_CPU_COUNT",
	"CONFIG_HAVE_KERNEL_DEBUG_HEAP",
	"CONFIG_HAVE_KERNEL_HEAP_RANDOMIZE_OFFSETS",
	"CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE",
	"CONFIG_HAVE_KERNEL_TRACE_MALLOC",
	"CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS",
}.sorted(x -> x.lstrip("?"));

local longestNameLen = CONFIGS.each.lstrip("?").length > ...;
for (local config: CONFIGS) {
	local name = config.lstrip("?");
	print("#ifdef ", name);
	print("\"	", name, ": ", (" " * (longestNameLen - #name)), "\" AC_WHITE(\""),;
	if (config.startswith("?")) {
		print("yes (\" PP_STR(", name, ") \")"),;
	} else {
		print("yes"),;
	}
	print("\") \"\\n\"");
	print("#else /" "* ", name, " *" "/");
	print("\"	", name, ": ", (" " * (longestNameLen - #name)), "\" AC_WHITE(\"no\") \"\\n\"");
	print("#endif /" "* !", name, " *" "/");
}
]]]*/
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
"	CONFIG_HAVE_KERNEL_DEBUG_HEAP:             " AC_WHITE("yes") "\n"
#else /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
"	CONFIG_HAVE_KERNEL_DEBUG_HEAP:             " AC_WHITE("no") "\n"
#endif /* !CONFIG_HAVE_KERNEL_DEBUG_HEAP */
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
"	CONFIG_HAVE_KERNEL_DEBUGGER:          " AC_WHITE("yes") "\n"
#else /* CONFIG_HAVE_KERNEL_DEBUGGER */
"	CONFIG_HAVE_KERNEL_DEBUGGER:          " AC_WHITE("no") "\n"
#endif /* !CONFIG_HAVE_KERNEL_DEBUGGER */
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
"	CONFIG_HAVE_KERNEL_FS_NOTIFY:         " AC_WHITE("yes") "\n"
#else /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
"	CONFIG_HAVE_KERNEL_FS_NOTIFY:         " AC_WHITE("no") "\n"
#endif /* !CONFIG_HAVE_KERNEL_FS_NOTIFY */
#ifdef CONFIG_HAVE_KERNEL_HEAP_RANDOMIZE_OFFSETS
"	CONFIG_HAVE_KERNEL_HEAP_RANDOMIZE_OFFSETS: " AC_WHITE("yes") "\n"
#else /* CONFIG_HAVE_KERNEL_HEAP_RANDOMIZE_OFFSETS */
"	CONFIG_HAVE_KERNEL_HEAP_RANDOMIZE_OFFSETS: " AC_WHITE("no") "\n"
#endif /* !CONFIG_HAVE_KERNEL_HEAP_RANDOMIZE_OFFSETS */
#ifdef CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE
"	CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE:      " AC_WHITE("yes") "\n"
#else /* CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE */
"	CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE:      " AC_WHITE("no") "\n"
#endif /* !CONFIG_HAVE_KERNEL_HEAP_TRACE_DANGLE */
#ifdef CONFIG_MAX_CPU_COUNT
"	CONFIG_MAX_CPU_COUNT:          " AC_WHITE("yes (" PP_STR(CONFIG_MAX_CPU_COUNT) ")") "\n"
#else /* CONFIG_MAX_CPU_COUNT */
"	CONFIG_MAX_CPU_COUNT:          " AC_WHITE("no") "\n"
#endif /* !CONFIG_MAX_CPU_COUNT */
#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
"	CONFIG_HAVE_KERNEL_TRACE_MALLOC:           " AC_WHITE("yes") "\n"
#else /* CONFIG_HAVE_KERNEL_TRACE_MALLOC */
"	CONFIG_HAVE_KERNEL_TRACE_MALLOC:           " AC_WHITE("no") "\n"
#endif /* !CONFIG_HAVE_KERNEL_TRACE_MALLOC */
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
"	CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS:    " AC_WHITE("yes") "\n"
#else /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
"	CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS:    " AC_WHITE("no") "\n"
#endif /* !CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
#ifdef NDEBUG
"	NDEBUG:                        " AC_WHITE("yes") "\n"
#else /* NDEBUG */
"	NDEBUG:                        " AC_WHITE("no") "\n"
#endif /* !NDEBUG */
#ifdef __OPTIMIZE__
"	__OPTIMIZE__:                  " AC_WHITE("yes") "\n"
#else /* __OPTIMIZE__ */
"	__OPTIMIZE__:                  " AC_WHITE("no") "\n"
#endif /* !__OPTIMIZE__ */
/*[[[end]]]*/
;

DBG_NAMED_COMMAND(build_config, "build-config",
                  "build-config\n"
                  "\tDisplay KOS build information\n",
                  argc, argv) {
	(void)argv;
	if (argc != 1)
		return DBG_STATUS_INVALID_ARGUMENTS;
	dbg_print(build_config);
	dbg_printf(DBGSTR("uname:\n"
	                  "	sysname:    " AC_WHITE("%s") "\n"
	                  "	nodename:   " AC_WHITE("%s") "\n"
	                  "	release:    " AC_WHITE("%s") "\n"
	                  "	version:    " AC_WHITE("%s") "\n"
	                  "	machine:    " AC_WHITE("%s") "\n"
	                  "	domainname: " AC_WHITE("%s") "\n"
	                  ""),
	           kernel_uname.sysname,
	           kernel_uname.nodename,
	           kernel_uname.release,
	           kernel_uname.version,
	           kernel_uname.machine,
	           kernel_uname.domainname);
	return 0;
}

DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_APPS_BUILD_CONFIG_C */
