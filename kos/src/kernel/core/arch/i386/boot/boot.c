/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_BOOT_BOOT_C
#define GUARD_KERNEL_CORE_ARCH_I386_BOOT_BOOT_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/boot.h>
#include <kernel/driver-param.h>
#include <kernel/fpu.h> /* CONFIG_FPU */
#include <kernel/memory.h>
#include <kernel/printk.h>
#include <kernel/rand.h>
#include <kernel/types.h>
#include <kernel/vboxgdb.h>
#include <kernel/x86/cpuid.h>
#include <kernel/x86/gdt.h>
#include <kernel/x86/multiboot.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

/**/
#include <dev/block.h>    /* TODO: Remove me; Only used for boot_partition-init */
#include <fs/node.h>      /* TODO: Remove me; Only used for boot_partition-init */
#include <fs/vfs.h>       /* TODO: Remove me; Only used for boot_partition-init */
#include <kernel/panic.h> /* TODO: Remove me; Only used for boot_partition-init */

DECL_BEGIN

PUBLIC ATTR_USED ATTR_SECTION(".bss")
struct fcpustate32 boot_cpustate;
PUBLIC ATTR_USED ATTR_SECTION(".data.cold")
struct boot_device_info boot_device = { 0xff, 0xff, 0xff, 0xff };

INTDEF port_t x86_syslog_port;

#define MAKE_DWORD(a, b, c, d) \
	((u32)(a) | ((u32)(b) << 8) | ((u32)(c) << 16) | ((u32)(d) << 24))


INTERN ATTR_FREEBSS bool x86_force_detect_moreram = false;
DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION(x86_force_detect_moreram,
                                            KERNEL_COMMANDLINE_OPTION_TYPE_BOOL,
                                            "force-detect-moreram");


#ifndef CONFIG_NO_DEBUGGER
/* Define options for entering debugger mode at various stages, rather than booting normally. */
DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION(dbg, KERNEL_COMMANDLINE_OPTION_TYPE_PRESENT, "dbg-very-early");
/**/ DEFINE_EARLY_KERNEL_COMMANDLINE_OPTION(dbg, KERNEL_COMMANDLINE_OPTION_TYPE_PRESENT, "dbg-early");
/*      */ DEFINE_KERNEL_COMMANDLINE_OPTION(dbg, KERNEL_COMMANDLINE_OPTION_TYPE_PRESENT, "dbg");
/* */ DEFINE_LATE_KERNEL_COMMANDLINE_OPTION(dbg, KERNEL_COMMANDLINE_OPTION_TYPE_PRESENT, "dbg-late");
#endif /* !CONFIG_NO_DEBUGGER */


#if 0
#include <format-printer.h>
#include <libdebuginfo/api.h>
#include <kernel/syslog.h>
INTDEF NONNULL((1)) ssize_t LIBDEBUGINFO_CC
libdi_debug_repr_dump(pformatprinter printer, void *arg,
                      byte_t *debug_info_start, byte_t *debug_info_end,
                      byte_t *debug_abbrev_start, byte_t *debug_abbrev_end,
                      byte_t *debug_loc_start, byte_t *debug_loc_end,
                      byte_t *debug_str_start, byte_t *debug_str_end);

PRIVATE void dump_debuginfo() {
	byte_t *di, *da, *dl, *ds;
	di = (byte_t *)driver_section_cdata(&kernel_section_debug_info);
	da = (byte_t *)driver_section_cdata(&kernel_section_debug_abbrev);
	dl = (byte_t *)driver_section_cdata(&kernel_section_debug_loc);
	ds = (byte_t *)driver_section_cdata(&kernel_section_debug_str);
	libdi_debug_repr_dump(&syslog_printer,
	                      SYSLOG_LEVEL_RAW,
	                      di, di + kernel_section_debug_info.ds_csize,
	                      da, da + kernel_section_debug_abbrev.ds_csize,
	                      dl, dl + kernel_section_debug_loc.ds_csize,
	                      ds, ds + kernel_section_debug_str.ds_csize);
}
#endif


INTERN ATTR_FREETEXT struct icpustate *
NOTHROW(KCALL __i386_kernel_main)(struct icpustate *__restrict state) {
	/* Figure out how we can output data to an emulator's STDOUT (if we're being hosted by one)
	 * NOTE: QEMU can consistently be detected via `CPUID[0x80000002].EAX',
	 *       but in order to allow KOS to properly detect BOCHS, you must change
	 *      <cpuid: brand_string="BOCHS         Intel(R) Pentium(R) 4 CPU        ">
	 *       in your .bxrc file
	 */
	if (bootcpu_x86_cpuid.ci_80000002a == MAKE_DWORD('Q', 'E', 'M', 'U'))
		x86_syslog_port = (port_t)0x3f8;
	else if (bootcpu_x86_cpuid.ci_80000002a == MAKE_DWORD('B', 'O', 'C', 'H'))
		x86_syslog_port = (port_t)0xe9;
	else if (bootcpu_x86_cpuid.ci_80000002a == MAKE_DWORD('V', 'B', 'o', 'x')) {
		x86_syslog_port = (port_t)0x504;
#ifdef CONFIG_VBOXGDB
		if (bootcpu_x86_cpuid.ci_80000002b == MAKE_DWORD(' ', 'G', 'D', 'B'))
			x86_initialize_vboxgdb();
#endif /* CONFIG_VBOXGDB */
	}
	x86_initialize_cmos();

	printk(FREESTR(KERN_NOTICE "[boot] Begin kernel initialization\n"));
	printk(FREESTR(KERN_INFO "[boot] CPU brand: %q\n"), bootcpu_x86_cpuid.ci_brand);

#ifdef __x86_64__
	/* Initialize (rd|wr)(fs|gs)base support and (if necessary)
	 * patch the kernel to use (rd|wr)msr if unavailable. */
	x86_initialize_fsgsbase();
#endif /* __x86_64__ */

#ifndef __x86_64__
	/* Initialize the atomic64 configuration */
	x86_initialize_atomic64();
#endif /* !__x86_64__ */

	/* Initialize the paging configuration */
	x86_initialize_paging();

	/* Initialize per-task/per-cpu structures */
	kernel_initialize_scheduler();

	/* Load default memory banks. */
	x86_initialize_default_memory_banks();

	/* Run task initialization callbacks on the boot task, initializing
	 * important structures such as the r/w-lock descriptor and the task
	 * signal connection manager.
	 * NOTE: We do this now since r/w-locks and signal connections are
	 *       required by the Unwind-FDE cache sub-system, meaning that
	 *       they are also required for us to be able to handle exceptions.
	 * In other words: Only once this function has been called can we
	 *                 start making use of exceptions safely. */
	kernel_initialize_scheduler_callbacks();

	/* Load multiboot information.
	 * NOTE: All information provided by the bootloader is assumed
	 *       to be located within the first 1Gb of physical memory! */
	{
		size_t total_pages;
		u32 boot_eax = boot_cpustate.fcs_gpregs.gp_eax;
		u32 boot_ebx = boot_cpustate.fcs_gpregs.gp_ebx;

		/* Multiboot support */
		if (boot_eax == MB_BOOTLOADER_MAGIC) {
			/* Multiboot Mk#1 */
			printk(FREESTR(KERN_INFO "[boot] Booting via Multiboot-compliant bootloader\n"));
			x86_load_mb1info(boot_ebx);
		} else if (boot_eax == MB2_BOOTLOADER_MAGIC) {
			/* Multiboot Mk#2 */
			printk(FREESTR(KERN_INFO "[boot] Booting via Multiboot2-compliant bootloader\n"));
			x86_load_mb2info(boot_ebx);
		}

		/* Evaluate commandline options defined as `DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION()' */
		kernel_initialize_commandline_options_very_early();

		/* If we didn't gather at least 1MB, try to consult the bios to find more. */
		total_pages = minfo_usable_ram_pages();
		if (total_pages < X86_BOOT_MINIMUM_AVAILABLE_RAM || x86_force_detect_moreram) { /* Less than 1MB */
			x86_initialize_memory_via_bios();
			total_pages = minfo_usable_ram_pages();
		}
		printk(FREESTR(KERN_INFO "[mem] Located %Iu (%#Ix) bytes (%Iu %s) of usable RAM\n"),
		       total_pages * PAGESIZE,
		       total_pages * PAGESIZE,
		       total_pages >= (0x100000 / PAGESIZE)
		       ? (total_pages / (0x100000 / PAGESIZE))
		       : (total_pages * PAGESIZE) / 0x400,
		       total_pages >= (0x100000 / PAGESIZE)
		       ? FREESTR("MiB")
		       : FREESTR("KiB"));
	}

	/* Load support for the sysenter instruction. */
	x86_initialize_sysenter();

	/* Initialize SMP.
	 * NOTE: This must be done while the physical identity mapping is still
	 *       in effect (aka: before `x86_initialize_kernel_vm()' is called)
	 *       Additionally, do this before memory zones have been finalized,
	 *       so we can manually add SMP descriptor memory regions as available
	 *       physical memory, while still preventing them from being overwritten
	 *       by zone initialization, regardless of what the bootloader/BIOS did
	 *       about them in terms of telling. */
	x86_initialize_smp();

	/* Same as SMP, ACPI needs access to the physical identity mapping. */
	x86_initialize_acpi();

#if 0
	{
		size_t i;
		for (i = 0; i < minfo.mb_bankc; ++i) {
			printk(KERN_DEBUG "[boot] MEMORY: %I64p...%I64p (%s)\n",
			       (u64)PMEMBANK_MINADDR(minfo.mb_banks[i]),
			       (u64)PMEMBANK_MAXADDR(minfo.mb_banks[i]),
			       pmembank_type_names[minfo.mb_banks[i].mb_type]);
		}
	}
#endif

	/* Generate physical memory zones from collected memory information. */
	kernel_initialize_minfo_makezones();

	/* Since we're about to evaluate the kernel commandline
	 * for the first time (which parses the seed=... option),
	 * we have to fill in the initial PRNG seed before then,
	 * so that when not receiving that option, we'll end up
	 * truly random initial seed.
	 * So we're just going to read the CMOS RTC state and use
	 * it to set the initial kernel seed. */
	x86_initialize_rand_entropy(); /* TODO: Do this portably through use of `realtime()' */

	/* Evaluate commandline options defined as `DEFINE_EARLY_KERNEL_COMMANDLINE_OPTION()' */
	kernel_initialize_commandline_options_early();

	/* Since `kernel_initialize_commandline_options_early()' may have overwritten
	 * the initial seed set by `x86_initialize_rand_entropy()', only log the actually
	 * used seed now so that the system logs remain consistent with the user's expectation. */
	printk(FREESTR(KERN_INFO "[rand] Set pseudo RNG seed to %#.8I32x\n"), krand_seed);

	/* Initialize the x86_64 physical memory identity memory mapping.
	 * This can only be done _after_ we've loaded available RAM, since
	 * this function may need to allocate some of that memory... */
#ifdef CONFIG_PHYS2VIRT_IDENTITY_MAXALLOC
	x86_initialize_phys2virt64();
#endif /* !ONFIG_PHYS2VIRT_IDENTITY_MAXALLOC */

	/* Initialize the kernel VM, and instigate strict memory protection,
	 * unmapping virtual memory that isn't being used by the kernel, while
	 * also removing write permissions for .text and .rodata, as well as
	 * (if supported) setting the NOEXECUTE bit for anything but `.text'
	 * and `.xdata' / `.xbss'
	 * NOTE: This also unmaps the physical identity mapping found surrounding
	 *       the kernel, which was left in tact until this point in order to
	 *       simplify initialization of SMP control structures (or anything
	 *       left in physical memory below the 1GiB mark). */
	x86_initialize_kernel_vm();

	/* Relocate memory information into higher memory, moving it away from
	 * being somewhere where it could cause problems, or be accidentally
	 * corrupted. */
	kernel_initialize_minfo_relocate();

	/* Initialize the ioperm() sub-system. */
	x86_initialize_iobm();

	/* Flush the entire TLB buffer, now that we're finished setting up the page directory.
	 * NOTE: Technically, this should be unnecessary, but it may still clean up some
	 *       caches that had become clobbered by our incessant modifications above. */
	pagedir_syncall();

	/* Initialize the APIC / PIC, as well as secondary CPUs when SMP is enabled. */
	x86_initialize_apic();

	/* XXX: ioapic support (ioapic is the modern equivalent of the pic) */

#ifdef CONFIG_FPU
	/* Initialize the FPU sub-system. */
	x86_initialize_fpu();
#endif /* CONFIG_FPU */

	/* Make the kernel's .text and .rodata sections read-only. */
	x86_initialize_kernel_vm_readonly();

	/* Initialize the PID sub-system for the boot task. */
	kernel_initialize_bootpid();

	/* Copy the kernel commandline into high memory. */
	x86_initialize_commandline_himem();

	/* Allocate and set the user-space VM for /bin/init */
	kernel_initialize_user_vm();

	/* Evaluate commandline options defined as `DEFINE_KERNEL_COMMANDLINE_OPTION()' */
	kernel_initialize_commandline_options_stable();

#ifndef CONFIG_NO_DEBUGGER
	/* Before loading drivers proper, copy the BIOS's VGA font. */
	x86_initialize_debugger_textfont();
#endif /* !CONFIG_NO_DEBUGGER */

	/* Initialize builtin core drivers. */
	kernel_initialize_devfs_driver();
	kernel_initialize_pci_driver();
	kernel_initialize_ide_driver();
	kernel_initialize_fat_driver();

	/* Load drivers provided by the bootloader */
	x86_initialize_bootloader_drivers();

	/* Release physical memory from minfo that was marked as `PMEMBANK_TYPE_PRESERVE'
	 * NOTE: This can only be done after bootloader drivers, since drivers provided
	 *       by the bootloader are themself mapped as preserved memory. */
	minfo_release_presevations();

	/* Initialize special builtin character devices (/dev/null, /dev/zero, etc.) */
	kernel_initialize_null_devices();

	/* Initialize the /dev/tty alias device */
	kernel_initialize_ctty_device();

	/* Initialize (load dependencies, apply relocations & call constructors)
	 * all of the drivers provided by the bootloader. */
	kernel_initialize_loaded_drivers();

	/* Load late commandline options. */
	kernel_initialize_commandline_options_late();

	/* TODO: libdebuginfo freezes with -gdwarf-2
	 * TODO: Check if it still does this (it's been quite a while since I wrote that TODO) */

	/* TODO: If we weren't able to figure out the boot device, check if we can
	 *       somehow make use of the `boot_device' information which was given
	 *       to us by the bootloader... */
	printk(KERN_INFO "boot_device = { %#I8x, %#I8x, %#I8x, %#I8x }\n",
	       boot_device.bdi_biosdev,
	       boot_device.bdi_partition,
	       boot_device.bdi_sub_partition,
	       boot_device.bdi_sub_sub_partition);

	/* Make sure that we've managed to detect a single, valid boot partition, or
	 * that the user started the kernel with a boot=... commandline parameter. */
	if unlikely(boot_partition == NULL)
		kernel_panic(FREESTR("Unable to detect boot partition (reboot with `boot=...')"));
	if unlikely(boot_partition == (struct basic_block_device *)-1)
		kernel_panic(FREESTR("Detected boot partition is ambiguous (reboot with `boot=...')"));

	/* TODO: Don't hard-code fat here. - Instead, try every currently loaded filesystem driver.
	 *       After all: The bootloader may have loaded additional drivers... */
	/* TODO: Move this mount() call into a different file. */
	path_mount(THIS_VFS, "fat", boot_partition, SUPERBLOCK_FNORMAL, NULL, NULL, true);

	mall_dump_leaks(GFP_NORMAL);

#if 0
	decref(driver_insmod("iso9660", "a b foobar bazbaz"));
	{
		REF struct superblock *cd;
		cd = superblock_open("iso9660", "/dev/hdb");
		{
			SCOPED_READLOCK((struct vm_datablock *)cd);
			REF struct directory_entry *ent;
			while ((ent = directory_readnext(cd)) != NULL) {
				printk("ENTRY: %$q, %u, %I64u\n",
				       (size_t)ent->de_namelen,
				       ent->de_name,
				       (unsigned int)ent->de_type,
				       (u64)ent->de_ino);
			}
		}
		superblock_set_unmounted(cd);
		decref(cd);
	}
	driver_delmod("iso9660");
#endif

	/* Update the given initial user-state to start
	 * executing /bin/init (or whatever was passed as `init=...') */
	state = kernel_initialize_exec_init(state);

	printk(FREESTR(KERN_INFO "Initial jump to user-space [pc=%p] [sp=%p]\n"),
	       icpustate_getpc(state),
	       icpustate_getsp(state));

	/* TODO: deemon's module system appears somewhat broken on KOS.
	 *       Fix stuff both in KOS, and DEEMON itself until the following works from within KOS:
	 *       $ deemon --help /deemon/string
	 *
	 *       >> IllegalInstruction: Illegal instruction at <anonymous>+001A
	 *       /usr/lib/deemon/doctext.dee(148,1) : <anonymous>+001A
	 *       /usr/lib/deemon/doc.dee(2537,34) : __str__+0002
	 *       /usr/lib/deemon/doc.dee(3823,33) : __str__+0051
	 *       Also: In certain cases, this causes both the doc and doctext module's dec
	 *             files to constantly get re-compiled (though in other cases, these
	 *             exact dec files also get accepted as valid, possibly related to how
	 *             they've been imported, implying a problem within the deemon core)
	 *       NOTE: I'm assuming that the IllegalInstruction is caused by some discrepancy
	 *             between the hand-written assembly RT engine, and the one written in C
	 *
	 *       >> UnicodeDecodeError: Invalid utf-8 character byte 0x85
	 *       /usr/lib/deemon/doc.dee(2537,34) : __str__+0002
	 *       /usr/lib/deemon/doc.dee(3823,33) : __str__+0051
	 *       When the dec files already exist, this error is thrown instead.
	 *
	 * TODO: Deemon's SystemFile.size() function always uses lseek64()
	 *       Change this to where it first attempts to use fstat() (if available)
	 * TODO: Deemon's main() function should try to re-configure mallopt() during
	 *       init in order to optimize itself for using large amounts of memory.
	 *       Currently, running deemon causes the system log to be spammed with
	 *       calls to mmap() (an overallocation of 32768 bytes might work well...)
	 * TODO: When opening a dec file, use mmap() (if available) and malloc()+read()
	 *       as fall-back, rather than always using malloc()+read() */

	/* TODO: HOP_HANDLE_CREATE_STREAM
	 *       Constructs a wrapper for another handle object that includes a `pos_t'
	 *       file offset to implement read(), write() and lseek() by dispatching these
	 *       operators through pread(), pwrite() and fstat() (fstat for `stat::st_size'
	 *       with lseek(SEEK_END))
	 *       -> Useful for turning UVIO objects into file-like objects.
	 */

	/* TODO: Play around with `no_caller_saved_registers'
	 *       It may be possible to cut down on boiler-plate assembly needed to wrap
	 *       simple C-level interrupt handlers and/or system calls, by not needing
	 *       to save registers that wouldn't be used in any case! */

	/* TODO: Create another separate driver (that makes use of the transactional
	 *       instruction emulator) to emulate instruction execution for the child-
	 *       process branch after a call to fork().
	 *       By doing this (and doing it in a transactional environment), we could
	 *       be on the lookout for calls to exec(), allowing us to detect the usual
	 *       fork()+exec() pattern without having to actually clone anything (but
	 *       instead we'd be able to spawn() a new process!) */

	/* TODO: renameat2() is missing from <stdio.h> */

	/* TODO: Refactor <local/...> to <libc/local/...> */

	/* TODO: Decompressed driver section data should be reference counted, such that (then)
	 *       unused sections can be lazily unloaded during calls to `system_clearcache()' */

	/* TODO: Add auto-completion to the `cpuid' debugger command.
	 *       We can easily determine valid leafs by looking at the value of CPUID[0].EAX! */


	/* Xorg X-Window server support roadmap.
	 *
	 * Latest milestone:
	 *     - Starting the Xorg server will actually go so far as to:
	 *       - Switch to graphics mode
	 *       - Resize the monitor to a resolution much larger than my vga driver is capable of
	 *       - But that's also where it ends...
	 *
	 * Blocker:
	 *     - "Keyboard initialization failed. This could be a missing or incorrect setup of xkeyboard-config"
	 *       - Solution: It's fairly accurate on the "missing [...] setup of xkeyboard-config".
	 *                   The solution will be to port whatever X11 uses for keyboard input!
	 *
	 * TODO:
	 *     - Implement proper libsctrace support for arguments names of sys_socket
	 *     - Finish implementing support for unix domain sockets
	 *     - Properly implement libc's regex functions
	 *     - Patch Xorg-server to not try to make use of "/dev/ptmx"
	 *       KOS has an `sys_openpty(2)' system call for this purpose
	 *       Although I have to wonder why Xorg even needs PTYs...
	 *
	 * Current behavior:
	 *     $ Xorg
	 *     | ...
	 *
	 *     $ cat /var/log/Xorg.0.log
	 *     | [3910736.390] _XSERVTransPTSOpenServer: Unable to open /dev/ptmx
	 *     | [3910736.394] _XSERVTransOpen: transport open failed for pts/(none):0
	 *     | [3910736.397] _XSERVTransMakeAllCOTSServerListeners: failed to open listener for pts
	 *     | [3910736.461] 
	 *     | X.Org X Server 1.12.2
	 *     | Release Date: 2012-05-29
	 *     | [3910736.464] X Protocol Version 11, Revision 0
	 *     | [3910736.465] Build Operating System: KOS Griefer@Work
	 *     | [3910736.469] Current Operating System: KOS (none) KOS Mk4 - yakal 4.0.0 i386
	 *     | [3910736.471]  
	 *     | [3910736.474] Current version of pixman: 0.40.0
	 *     | [3910736.476] 	Before reporting problems, check https://github.com/GrieferAtWork/KOSmk4
	 *     | 	to make sure that you have the latest version.
	 *     | [3910736.478] Markers: (--) probed, (**) from config file, (==) default setting,
	 *     | 	(++) from command line, (!!) notice, (II) informational,
	 *     | 	(WW) warning, (EE) error, (NI) not implemented, (??) unknown.
	 *     | [3910736.486] (==) Log file: "/var/log/Xorg.0.log", Time: Thu Aug 13 18:33:23 2020
	 *     | [3910736.508] (II) Loader magic: 082349C0
	 *     | [3910736.510] (II) Module ABI versions:
	 *     | [3910736.511] 	X.Org ANSI C Emulation: 0.4
	 *     | [3910736.513] 	X.Org Video Driver: 12.0
	 *     | [3910736.514] 	X.Org XInput driver : 16.0
	 *     | [3910736.515] 	X.Org Server Extension : 6.0
	 *     | [3910736.552] (--) PCI:*(0:0:2:0) 1234:1111:1af4:1100 rev 2, Mem @ 0xfd000000/16777216, 0xfebd0000/4096, BIOS @ 0x????????/65536
	 *     | [3910736.562] (==) Using default built-in configuration (21 lines)
	 *     | [3910736.563] (==) --- Start of built-in configuration ---
	 *     | [3910736.564] 	Section "Device"
	 *     | [3910736.565] 		Identifier	"Builtin Default vesa Device 0"
	 *     | [3910736.566] 		Driver	"vesa"
	 *     | [3910736.567] 	EndSection
	 *     | [3910736.568] 	Section "Screen"
	 *     | [3910736.569] 		Identifier	"Builtin Default vesa Screen 0"
	 *     | [3910736.571] 		Device	"Builtin Default vesa Device 0"
	 *     | [3910736.572] 	EndSection
	 *     | [3910736.573] 	Section "Device"
	 *     | [3910736.574] 		Identifier	"Builtin Default fbdev Device 0"
	 *     | [3910736.575] 		Driver	"fbdev"
	 *     | [3910736.576] 	EndSection
	 *     | [3910736.577] 	Section "Screen"
	 *     | [3910736.579] 		Identifier	"Builtin Default fbdev Screen 0"
	 *     | [3910736.580] 		Device	"Builtin Default fbdev Device 0"
	 *     | [3910736.581] 	EndSection
	 *     | [3910736.582] 	Section "ServerLayout"
	 *     | [3910736.583] 		Identifier	"Builtin Default Layout"
	 *     | [3910736.584] 		Screen	"Builtin Default vesa Screen 0"
	 *     | [3910736.588] 		Screen	"Builtin Default fbdev Screen 0"
	 *     | [3910736.589] 	EndSection
	 *     | [3910736.590] (==) --- End of built-in configuration ---
	 *     | [3910736.596] (==) ServerLayout "Builtin Default Layout"
	 *     | [3910736.597] (**) |-->Screen "Builtin Default vesa Screen 0" (0)
	 *     | [3910736.599] (**) |   |-->Monitor "<default monitor>"
	 *     | [3910736.606] (**) |   |-->Device "Builtin Default vesa Device 0"
	 *     | [3910736.607] (==) No monitor specified for screen "Builtin Default vesa Screen 0".
	 *     | 	Using a default monitor configuration.
	 *     | [3910736.608] (**) |-->Screen "Builtin Default fbdev Screen 0" (1)
	 *     | [3910736.609] (**) |   |-->Monitor "<default monitor>"
	 *     | [3910736.613] (**) |   |-->Device "Builtin Default fbdev Device 0"
	 *     | [3910736.614] (==) No monitor specified for screen "Builtin Default fbdev Screen 0".
	 *     | 	Using a default monitor configuration.
	 *     | [3910736.617] (==) Disabling SIGIO handlers for input devices
	 *     | [3910736.619] (==) Not automatically adding devices
	 *     | [3910736.620] (==) Not automatically enabling devices
	 *     | [3910736.624] (WW) The directory "/usr/share/fonts/X11/misc/" does not exist.
	 *     | [3910736.625] 	Entry deleted from font path.
	 *     | [3910736.626] (WW) The directory "/usr/share/fonts/X11/ttf/" does not exist.
	 *     | [3910736.627] 	Entry deleted from font path.
	 *     | [3910736.629] (WW) The directory "/usr/share/fonts/X11/otf/" does not exist.
	 *     | [3910736.630] 	Entry deleted from font path.
	 *     | [3910736.632] (WW) The directory "/usr/share/fonts/X11/Type1/" does not exist.
	 *     | [3910736.633] 	Entry deleted from font path.
	 *     | [3910736.635] (WW) The directory "/usr/share/fonts/X11/100dpi/" does not exist.
	 *     | [3910736.636] 	Entry deleted from font path.
	 *     | [3910736.638] (WW) The directory "/usr/share/fonts/X11/75dpi/" does not exist.
	 *     | [3910736.639] 	Entry deleted from font path.
	 *     | [3910736.640] (==) FontPath set to:
	 *     | 	built-ins
	 *     | [3910736.642] (==) ModulePath set to "/lib/xorg/modules"
	 *     | [3910736.645] (==) |-->Input Device "<default pointer>"
	 *     | [3910736.647] (==) |-->Input Device "<default keyboard>"
	 *     | [3910736.648] (==) The core pointer device wasn't specified explicitly in the layout.
	 *     | 	Using the default mouse configuration.
	 *     | [3910736.649] (==) The core keyboard device wasn't specified explicitly in the layout.
	 *     | 	Using the default keyboard configuration.
	 *     | [3910736.652] (II) LoadModule: "extmod"
	 *     | [3910736.670] (II) Loading /lib/xorg/modules/extensions/libextmod.so
	 *     | [3910736.691] (II) Module extmod: vendor="X.Org Foundation"
	 *     | [3910736.692] 	compiled for 1.12.2, module version = 1.0.0
	 *     | [3910736.694] 	Module class: X.Org Server Extension
	 *     | [3910736.695] 	ABI class: X.Org Server Extension, version 6.0
	 *     | [3910736.697] (II) Loading extension MIT-SCREEN-SAVER
	 *     | [3910736.698] (II) Loading extension XFree86-VidModeExtension
	 *     | [3910736.699] (II) Loading extension XFree86-DGA
	 *     | [3910736.701] (II) Loading extension DPMS
	 *     | [3910736.702] (II) Loading extension XVideo
	 *     | [3910736.704] (II) Loading extension XVideo-MotionCompensation
	 *     | [3910736.705] (II) Loading extension X-Resource
	 *     | [3910736.706] (II) LoadModule: "dbe"
	 *     | [3910736.712] (II) Loading /lib/xorg/modules/extensions/libdbe.so
	 *     | [3910736.716] (II) Module dbe: vendor="X.Org Foundation"
	 *     | [3910736.718] 	compiled for 1.12.2, module version = 1.0.0
	 *     | [3910736.719] 	Module class: X.Org Server Extension
	 *     | [3910736.720] 	ABI class: X.Org Server Extension, version 6.0
	 *     | [3910736.722] (II) Loading extension DOUBLE-BUFFER
	 *     | [3910736.723] (II) LoadModule: "record"
	 *     | [3910736.729] (II) Loading /lib/xorg/modules/extensions/librecord.so
	 *     | [3910736.737] (II) Module record: vendor="X.Org Foundation"
	 *     | [3910736.738] 	compiled for 1.12.2, module version = 1.13.0
	 *     | [3910736.740] 	Module class: X.Org Server Extension
	 *     | [3910736.742] 	ABI class: X.Org Server Extension, version 6.0
	 *     | [3910736.743] (II) Loading extension RECORD
	 *     | [3910736.744] (II) LoadModule: "vesa"
	 *     | [3910736.781] (II) Loading /lib/xorg/modules/drivers/vesa_drv.so
	 *     | [3910736.788] (II) Module vesa: vendor="X.Org Foundation"
	 *     | [3910736.789] 	compiled for 1.12.2, module version = 2.3.1
	 *     | [3910736.791] 	Module class: X.Org Video Driver
	 *     | [3910736.793] 	ABI class: X.Org Video Driver, version 12.0
	 *     | [3910736.795] (II) LoadModule: "fbdev"
	 *     | [3910736.829] (WW) Warning, couldn't open module fbdev
	 *     | [3910736.830] (II) UnloadModule: "fbdev"
	 *     | [3910736.832] (II) Unloading fbdev
	 *     | [3910736.833] (EE) Failed to load module "fbdev" (module does not exist, 0)
	 *     | [3910736.834] (II) LoadModule: "mouse"
	 *     | [3910736.869] (WW) Warning, couldn't open module mouse
	 *     | [3910736.870] (II) UnloadModule: "mouse"
	 *     | [3910736.872] (II) Unloading mouse
	 *     | [3910736.873] (EE) Failed to load module "mouse" (module does not exist, 0)
	 *     | [3910736.874] (II) LoadModule: "kbd"
	 *     | [3910736.909] (WW) Warning, couldn't open module kbd
	 *     | [3910736.910] (II) UnloadModule: "kbd"
	 *     | [3910736.911] (II) Unloading kbd
	 *     | [3910736.912] (EE) Failed to load module "kbd" (module does not exist, 0)
	 *     | [3910736.916] (II) VESA: driver for VESA chipsets: vesa
	 *     | [3910736.919] (--) using VT number 0
	 *     | 
	 *     | [3910736.924] (WW) xf86OpenConsole: setpgid failed: Operation not permitted
	 *     | [3910736.958] (WW) VGA arbiter: cannot open kernel arbiter, no multi-card support
	 *     | [3910736.960] (II) Loading sub module "vbe"
	 *     | [3910736.962] (II) LoadModule: "vbe"
	 *     | [3910736.973] (II) Loading /lib/xorg/modules/libvbe.so
	 *     | [3910736.981] (II) Module vbe: vendor="X.Org Foundation"
	 *     | [3910736.982] 	compiled for 1.12.2, module version = 1.1.0
	 *     | [3910736.983] 	ABI class: X.Org Video Driver, version 12.0
	 *     | [3910736.986] (II) Loading sub module "int10"
	 *     | [3910736.988] (II) LoadModule: "int10"
	 *     | [3910736.996] (II) Loading /lib/xorg/modules/libint10.so
	 *     | [3910737.200] (II) Module int10: vendor="X.Org Foundation"
	 *     | [3910737.400] 	compiled for 1.12.2, module version = 1.0.0
	 *     | [3910737.500] 	ABI class: X.Org Video Driver, version 12.0
	 *     | [3910737.700] (II) VESA(0): initializing int10
	 *     | [3910737.250] (II) VESA(0): Primary V_BIOS segment is: 0xc000
	 *     | [3910737.510] (II) VESA(0): VESA BIOS detected
	 *     | [3910737.530] (II) VESA(0): VESA VBE Version 3.0
	 *     | [3910737.540] (II) VESA(0): VESA VBE Total Mem: 16384 kB
	 *     | [3910737.560] (II) VESA(0): VESA VBE OEM: SeaBIOS VBE(C) 2011
	 *     | [3910737.580] (II) VESA(0): VESA VBE OEM Software Rev: 0.0
	 *     | [3910737.610] (II) VESA(0): VESA VBE OEM Vendor: SeaBIOS Developers
	 *     | [3910737.630] (II) VESA(0): VESA VBE OEM Product: SeaBIOS VBE Adapter
	 *     | [3910737.640] (II) VESA(0): VESA VBE OEM Product Rev: Rev. 1
	 *     | [3910737.395] (II) VESA(0): Creating default Display subsection in Screen section
	 *     | 	"Builtin Default vesa Screen 0" for depth/fbbpp 24/32
	 *     | [3910737.397] (==) VESA(0): Depth 24, (--) framebuffer bpp 32
	 *     | [3910737.398] (==) VESA(0): RGB weight 888
	 *     | [3910737.400] (==) VESA(0): Default visual is TrueColor
	 *     | [3910737.402] (==) VESA(0): Using gamma correction (1.0, 1.0, 1.0)
	 *     | [3910737.403] (II) Loading sub module "ddc"
	 *     | [3910737.404] (II) LoadModule: "ddc"
	 *     | [3910737.407] (II) Module "ddc" already built-in
	 *     | [3910737.416] (II) VESA(0): VESA VBE DDC not supported
	 *     | [3910737.425] (II) VESA(0): VESA VBE PanelID invalid
	 *     | [3910737.427] (II) VESA(0): Searching for matching VESA mode(s):
	 *     | [3910737.749] 
	 *     | [3910737.750] (II) VESA(0): Total Memory: 256 64KB banks (16384kB)
	 *     | [3910737.754] (II) VESA(0): <default monitor>: Using default hsync range of 31.50-48.00 kHz
	 *     | [3910737.755] (II) VESA(0): <default monitor>: Using default vrefresh range of 50.00-70.00 Hz
	 *     | [3910737.756] (II) VESA(0): <default monitor>: Using default maximum pixel clock of 65.00 MHz
	 *     | [3910737.757] (WW) VESA(0): Unable to estimate virtual size
	 *     | [3910737.760] (II) VESA(0): Not using built-in mode "2560x1600" (no mode of this name)
	 *     | [3910737.762] (II) VESA(0): Not using built-in mode "1920x1200" (no mode of this name)
	 *     | [3910737.763] (II) VESA(0): Not using built-in mode "1920x1080" (no mode of this name)
	 *     | [3910737.764] (II) VESA(0): Not using built-in mode "1600x1200" (no mode of this name)
	 *     | [3910737.765] (II) VESA(0): Not using built-in mode "1680x1050" (no mode of this name)
	 *     | [3910737.767] (II) VESA(0): Not using built-in mode "1400x1050" (no mode of this name)
	 *     | [3910737.768] (II) VESA(0): Not using built-in mode "1280x1024" (no mode of this name)
	 *     | [3910737.771] (II) VESA(0): Not using built-in mode "1440x900" (no mode of this name)
	 *     | [3910737.772] (II) VESA(0): Not using built-in mode "1280x960" (no mode of this name)
	 *     | [3910737.774] (II) VESA(0): Not using built-in mode "1280x800" (no mode of this name)
	 *     | [3910737.775] (II) VESA(0): Not using built-in mode "1152x864" (no mode of this name)
	 *     | [3910737.777] (II) VESA(0): Not using built-in mode "1280x768" (no mode of this name)
	 *     | [3910737.778] (II) VESA(0): Not using built-in mode "1280x720" (no mode of this name)
	 *     | [3910737.779] (II) VESA(0): Not using built-in mode "1024x768" (no mode of this name)
	 *     | [3910737.780] (II) VESA(0): Not using built-in mode "800x600" (no mode of this name)
	 *     | [3910737.782] (II) VESA(0): Not using built-in mode "640x480" (no mode of this name)
	 *     | [3910737.783] (II) VESA(0): Not using built-in mode "640x400" (no mode of this name)
	 *     | [3910737.784] (II) VESA(0): Not using built-in mode "320x200" (no mode of this name)
	 *     | [3910737.786] (WW) VESA(0): No valid modes left. Trying less strict filter...
	 *     | [3910737.787] (II) VESA(0): <default monitor>: Using hsync range of 31.50-48.00 kHz
	 *     | [3910737.788] (II) VESA(0): <default monitor>: Using vrefresh range of 50.00-70.00 Hz
	 *     | [3910737.789] (II) VESA(0): <default monitor>: Using maximum pixel clock of 65.00 MHz
	 *     | [3910737.790] (WW) VESA(0): Unable to estimate virtual size
	 *     | [3910737.794] (II) VESA(0): Not using built-in mode "2560x1600" (hsync out of range)
	 *     | [3910737.796] (II) VESA(0): Not using built-in mode "1920x1200" (hsync out of range)
	 *     | [3910737.797] (II) VESA(0): Not using built-in mode "1920x1080" (hsync out of range)
	 *     | [3910737.798] (II) VESA(0): Not using built-in mode "1600x1200" (hsync out of range)
	 *     | [3910737.800] (II) VESA(0): Not using built-in mode "1680x1050" (hsync out of range)
	 *     | [3910737.802] (II) VESA(0): Not using built-in mode "1400x1050" (hsync out of range)
	 *     | [3910737.803] (II) VESA(0): Not using built-in mode "1280x1024" (hsync out of range)
	 *     | [3910737.805] (II) VESA(0): Not using built-in mode "1440x900" (hsync out of range)
	 *     | [3910737.806] (II) VESA(0): Not using built-in mode "1280x960" (hsync out of range)
	 *     | [3910737.807] (II) VESA(0): Not using built-in mode "1280x800" (hsync out of range)
	 *     | [3910737.808] (II) VESA(0): Not using built-in mode "1152x864" (hsync out of range)
	 *     | [3910737.810] (II) VESA(0): Not using built-in mode "1280x768" (hsync out of range)
	 *     | [3910737.812] (II) VESA(0): Not using built-in mode "640x400" (hsync out of range)
	 *     | [3910737.813] (II) VESA(0): Not using built-in mode "320x200" (illegal horizontal timings)
	 *     | [3910737.815] (--) VESA(0): Virtual size is 1280x768 (pitch 1280)
	 *     | [3910737.817] (**) VESA(0): *Built-in mode "1280x720"
	 *     | [3910737.818] (**) VESA(0): *Built-in mode "1024x768"
	 *     | [3910737.819] (**) VESA(0): *Built-in mode "800x600"
	 *     | [3910737.819] (**) VESA(0): *Built-in mode "640x480"
	 *     | [3910737.821] (==) VESA(0): DPI set to (96, 96)
	 *     | [3910737.826] (II) VESA(0): Attempting to use 60Hz refresh for mode "1024x768" (144)
	 *     | [3910737.835] (II) VESA(0): Attempting to use 60Hz refresh for mode "800x600" (143)
	 *     | [3910737.842] (II) VESA(0): Attempting to use 60Hz refresh for mode "640x480" (142)
	 *     | [3910737.850] (**) VESA(0): Using "Shadow Framebuffer"
	 *     | [3910737.852] (II) Loading sub module "shadow"
	 *     | [3910737.853] (II) LoadModule: "shadow"
	 *     | [3910737.885] (II) Loading /lib/xorg/modules/libshadow.so
	 *     | [3910737.897] (II) Module shadow: vendor="X.Org Foundation"
	 *     | [3910737.898] 	compiled for 1.12.2, module version = 1.1.0
	 *     | [3910737.900] 	ABI class: X.Org ANSI C Emulation, version 0.4
	 *     | [3910737.901] (II) Loading sub module "fb"
	 *     | [3910737.902] (II) LoadModule: "fb"
	 *     | [3910737.910] (II) Loading /lib/xorg/modules/libfb.so
	 *     | [3910737.917] (II) Module fb: vendor="X.Org Foundation"
	 *     | [3910737.918] 	compiled for 1.12.2, module version = 1.0.0
	 *     | [3910737.920] 	ABI class: X.Org ANSI C Emulation, version 0.4
	 *     | [3910737.927] (==) Depth 24 pixmap format is 32 bpp
	 *     | [3910737.929] (II) Loading sub module "int10"
	 *     | [3910737.930] (II) LoadModule: "int10"
	 *     | [3910737.939] (II) Loading /lib/xorg/modules/libint10.so
	 *     | [3910737.940] (II) Module int10: vendor="X.Org Foundation"
	 *     | [3910737.941] 	compiled for 1.12.2, module version = 1.0.0
	 *     | [3910737.943] 	ABI class: X.Org Video Driver, version 12.0
	 *     | [3910737.944] (II) VESA(0): initializing int10
	 *     | [3910737.949] (II) VESA(0): Primary V_BIOS segment is: 0xc000
	 *     | [3910737.955] (II) VESA(0): VESA BIOS detected
	 *     | [3910737.956] (II) VESA(0): VESA VBE Version 3.0
	 *     | [3910737.958] (II) VESA(0): VESA VBE Total Mem: 16384 kB
	 *     | [3910737.959] (II) VESA(0): VESA VBE OEM: SeaBIOS VBE(C) 2011
	 *     | [3910737.960] (II) VESA(0): VESA VBE OEM Software Rev: 0.0
	 *     | [3910737.961] (II) VESA(0): VESA VBE OEM Vendor: SeaBIOS Developers
	 *     | [3910737.962] (II) VESA(0): VESA VBE OEM Product: SeaBIOS VBE Adapter
	 *     | [3910737.963] (II) VESA(0): VESA VBE OEM Product Rev: Rev. 1
	 *     | [3910737.965] (II) VESA(0): virtual address = 00000000,
	 *     | 	physical address = 0xfd000000, size = 16777216
	 *     | [3910737.968] (II) VESA(0): virtual address = 100A8000,
	 *     | 	physical address = 0xa0000, size = 65536
	 *     | [3910738.200] (II) VESA(0): Setting up VESA Mode 0x18F (1280x720)
	 *     | [3910738.270] (==) VESA(0): Default visual is TrueColor
	 *     | [3910738.630] (==) VESA(0): Backing store disabled
	 *     | [3910738.840] (==) VESA(0): DPMS enabled
	 *     | [3910738.880] (==) RandR enabled
	 *     | [3910738.920] (II) Initializing built-in extension Generic Event Extension
	 *     | [3910738.940] (II) Initializing built-in extension SHAPE
	 *     | [3910738.950] (II) Initializing built-in extension MIT-SHM
	 *     | [3910738.970] (II) Initializing built-in extension XInputExtension
	 *     | [3910738.980] (II) Initializing built-in extension XTEST
	 *     | [3910738.100] (II) Initializing built-in extension BIG-REQUESTS
	 *     | [3910738.101] (II) Initializing built-in extension SYNC
	 *     | [3910738.102] (II) Initializing built-in extension XKEYBOARD
	 *     | [3910738.103] (II) Initializing built-in extension XC-MISC
	 *     | [3910738.104] (II) Initializing built-in extension XFIXES
	 *     | [3910738.105] (II) Initializing built-in extension XFree86-Bigfont
	 *     | [3910738.107] (II) Initializing built-in extension RENDER
	 *     | [3910738.108] (II) Initializing built-in extension RANDR
	 *     | [3910738.109] (II) Initializing built-in extension COMPOSITE
	 *     | [3910738.110] (II) Initializing built-in extension DAMAGE
	 *     | [3910738.404] (EE) XKB: Couldn't open rules file /usr/share/X11/xkb/rules/base
	 *     | [3910738.406] (EE) XKB: Failed to load keymap. Loading default keymap instead.
	 *     | [3910738.408] (EE) XKB: Couldn't open rules file /usr/share/X11/xkb/rules/base
	 *     | [3910738.409] XKB: Failed to compile keymap
	 *     | [3910738.411] Keyboard initialization failed. This could be a missing or incorrect setup of xkeyboard-config.
	 *     | [3910738.413] 
	 *     | Fatal server error:
	 *     | [3910738.414] Failed to activate core devices.
	 *     | [3910738.416] 
	 *     | Please consult the Griefer@Work support 
	 *     | 	 at https://github.com/GrieferAtWork/KOSmk4
	 *     |  for help. 
	 *     | [3910738.417] Please also check the log file at "/var/log/Xorg.0.log" for additional information.
	 *     | [3910738.419] 
	 *     | [3910738.503] Server terminated with error (1). Closing log file.
	 */

	return state;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_BOOT_BOOT_C */
