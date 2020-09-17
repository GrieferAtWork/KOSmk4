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

#include <inttypes.h>

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
		printk(FREESTR(KERN_INFO "[mem] Located %" PRIuSIZ " (%#" PRIxSIZ ") "
		                         "bytes (%" PRIuSIZ " %s) of usable RAM\n"),
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
			printk(KERN_DEBUG "[boot] MEMORY: "
			                  "%" PRIpN(__SIZEOF_PHYSADDR_T__) "..."
			                  "%" PRIpN(__SIZEOF_PHYSADDR_T__) " (%s)\n",
			       (physaddr_t)PMEMBANK_MINADDR(minfo.mb_banks[i]),
			       (physaddr_t)PMEMBANK_MAXADDR(minfo.mb_banks[i]),
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
	x86_initialize_rand_entropy();

	/* Evaluate commandline options defined as `DEFINE_EARLY_KERNEL_COMMANDLINE_OPTION()' */
	kernel_initialize_commandline_options_early();

	/* Since `kernel_initialize_commandline_options_early()' may have overwritten
	 * the initial seed set by `x86_initialize_rand_entropy()', only log the actually
	 * used seed now so that the system logs remain consistent with the user's expectation. */
	printk(FREESTR(KERN_INFO "[rand] Set pseudo RNG seed to %#.8" PRIx32 "\n"), krand_seed);

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
	minfo_release_preservations();

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
	printk(KERN_INFO "boot_device = { %#" PRIx8 ", %#" PRIx8 ", %#" PRIx8 ", %#" PRIx8 " }\n",
	       (u8)boot_device.bdi_biosdev,
	       (u8)boot_device.bdi_partition,
	       (u8)boot_device.bdi_sub_partition,
	       (u8)boot_device.bdi_sub_sub_partition);

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
				printk("ENTRY: %$q, %u, %" PRIuN(__SIZEOF_INO_T__) "\n",
				       (size_t)ent->de_namelen,
				       ent->de_name,
				       (unsigned int)ent->de_type,
				       (ino_t)ent->de_ino);
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

	/* TODO: Decompressed driver section data should be reference counted, such that (then)
	 *       unused sections can be lazily unloaded during calls to `system_clearcache()' */

	/* TODO: Add auto-completion to the `cpuid' debugger command.
	 *       We can easily determine valid leafs by looking at the value of CPUID[0].EAX! */

	/* TODO: Now that there's once again a packet-buffer controller,
	 *       add support for pipe2(O_DIRECT) (aka. packet-mode)
	 *       Do this via new handle types:
	 *        - HANDLE_TYPE_PACKET_PIPE
	 *        - HANDLE_TYPE_PACKET_PIPE_READER
	 *        - HANDLE_TYPE_PACKET_PIPE_WRITER */

	/* TODO: `x86_64-kos-gcc -mno-red-zone -print-libgcc-file-name'
	 *       This will still print the normal libgcc.a filename, which
	 *       wasn't built with support for -mno-red-zone.
	 * >> https://wiki.osdev.org/Libgcc_without_red_zone */

	/* TODO: The builtin debugger's disassembler should show the values of
	 *       registers used in the current instruction, as well as the contents
	 *       of memory operands. */

	/* TODO: The builtin debugger should contain a graphical applet that combines
	 *       the functionality of the `lsthread', `thread', `trace', `l' and `r'
	 *       commands. */

	/* TODO: Trigger `DEBUGTRAP_REASON_VFORK' and `DEBUGTRAP_REASON_VFORKDONE'
	 *       at appropriate locations within the kernel. */

	/* TODO: Add special files to /proc, and add symlinks to /dev to implement:
	 *       /dev/                   -- Just like right now, contains system devices by-name
	 *       /dev/block/             -- Contains symlinks for the /dev device, such as 8:0 -> ../sda
	 *       /dev/char/              -- Contains symlinks for the /dev device, such as 1:1 -> ../mem
	 *       /dev/cpu/[id]/cpuid     -- A readable file to access `cpuid' data for a given CPU.
	 *       /dev/disk/by-id/        -- Symlinks for block-devices
	 *       /dev/disk/by-label/     -- Symlinks for block-devices
	 *       /dev/disk/by-partlabel/ -- Symlinks for block-devices
	 *       /dev/disk/by-partuuid/  -- Symlinks for block-devices
	 *       /dev/disk/by-path/      -- Symlinks for block-devices
	 *       /dev/disk/by-uuid/      -- Symlinks for block-devices
	 * Alternatively (and arguably even better), make /dev a dynamic file system, similar to /proc */

	/* XXX: Add a smart, arch-specific unwinder to libunwind that will inspect
	 *      the instruction stream to figure out how to unwind the stack.
	 *      This unwinder should assume the default calling convention for every
	 *      possible case, and should indicate unwind success once a ret-like
	 *      instruction is encountered: `ret', `lret' or `iret'
	 *
	 *      Conditional branch instruction should be unwound by remembering the
	 *      current CPU state, and recursively unwinding on both ends of the
	 *      jump. Only if both ends end up with a successful unwind, and only
	 *      if both ends result in all-identical callee-preserve registers is
	 *      the unwind to-be considered successful.
	 */

	/* TODO: A new system call and ABI for a user-space-controlled sigprocmask()
	 *       using this, user-space could block/unblock signals without having to do
	 *       any system calls in case where no signal arrived in the mean time, and
	 *       in the case where a signal did arrive in the mean time, only 1 system
	 *       call (`sys_sigmask_check()') would be required.
	 *
	 * Purpose:
	 *    - A lot of kernel-space code makes use of `PREEMPTION_PUSHOFF()' / `PREEMPTION_POP()'
	 *      in order to ensure reentrancy for small sections of code. The equivalent user-space
	 *      API for this is `sigprocmask()', however that function is anything but efficient in
	 *      what it does, having to unconditionally employ a system call when used, and
	 *      furthermore, that system call isn't the fastest one out there, either.
	 *    - Solve this problem by designing a sigprocmask() function that can be implemented
	 *      entirely within the confines of user-space (only needing to perform a system call
	 *      in the scenario where a (potentially) pending signal has become unmask)
	 *
	 * Notes:
	 *    - The race condition caused by the thread exiting, and its reaper destroying the
	 *      backing memory of the userprocmask structure is solved by merging this new system
	 *      call with the exiting `set_tid_address(2)' API, which already solves this problem
	 *      by requiring that the backing storage of the TID address may only be freed once
	 *      the kernel has written `0' to the TID address.
	 *    - The `pm_sigsize' field must not be changed by user-space. The kernel only guaranties that
	 *      it will check that field once (during the initial call to `sys_set_userprocmask_address()')
	 *      If the field is altered at any point after that, the kernel will most likely just ignore
	 *      that change, continuing to work under the assumption of the original value.
	 *    - When the kernel needs to modify a thread's signal mask, this is handled by:
	 *       - In the case of calling a signal handler with a non-empty `sigaction::sa_mask',
	 *         the kernel will load the `pm_sigmask' pointer, and or' the pointed-to signal
	 *         set with `sigaction::sa_mask'. Note though that this could only happen when
	 *         `*pm_sigmask' contained any 0-bits before, meaning that an all-1s signal mask
	 *         will never be modified in this case.
	 *       - A call to the actual `sys_sigprocmask(2)' system call (_NOT_ the libc variant
	 *         described further below).
	 *         In this case, rather than modifying its own, original signal mask, the kernel
	 *         will instead load the `pm_sigmask' point, and apply the same modifications it
	 *         would have applied to the thread's internal (kernel-space) signal mask the
	 *         signal set pointed-to by user-space.
	 *
	 * Semantics:
	 *
	 *    - When using `sys_set_userprocmask_address(2)', the pointed-to `struct userprocmask'
	 *      structure must have thread-local storage duration (that is: may not be destroyed
	 *      until _after_ the thread that called `sys_set_userprocmask_address()' has exited,
	 *      or until another call to `sys_set_userprocmask_address(2)' or `set_tid_address(2)')
	 *
	 *    - Kernel-space checks for is-signal-masked are only ever performed in the context of the
	 *      thread in question itself. When some other thread wishes to know if a userprocmask'd
	 *      thread is masking some signal, they must simply assume that the thread isn't, and send
	 *      an RPC that should confirm this for them. This is required, due to the indirection of
	 *      the `pm_sigmask' field, which allows user-space to switch between signal mask pointers,
	 *      rather than having to copy around signal sets as a whole. Also, this is required to
	 *      ensure that modifications made by libc's sigprocmask() are applied atomically for all
	 *      signals, rather than individually for each signal (which would result in race conditions
	 *      when unmasking one signal triggers a signal handler that would get executed in an
	 *      inconsistent context)
	 *      As such, user-space making use of userprocmask somewhat increases the overhead needed
	 *      for raising signals, however given that signals in general aren't something that is
	 *      done by programs with the intend of using them for performance-critical purposes, this
	 *      is completely acceptable.
	 *
	 *    - During a (successful) call to exec(), userprocmask-mode is disabled, the same way it
	 *      would also be disabled from user-space calling `sys_set_userprocmask_address(NULL)'
	 *      As such, the final contents of `pm_sigmask' from the thread calling exec() will be
	 *      loaded into the kernel's internal (legacy) sigprocmask buffer, such that the signal
	 *      mask itself is inherited by a new process the same way it would be if userprocmask
	 *      hadn't been using by the original process.
	 *
	 *    - During a call to fork() or clone() (w/o CLONE_VM, or w/ CLONE_VFORK), the
	 *      parent thread's IS_A_USERPROCMASK_THREAD attribute is inherited unconditionally.
	 *      During a call to clone(CLONE_VM), where the parent is a userprocmask thread,
	 *      prior to clone() returning in either the parent or child, the parent thread's
	 *      user-space `pm_sigmask' is copied into the kernel-space buffer of the child
	 *      thread, while the child thread itself will not be started in userprocmask mode.
	 *
	 *    - One caveat exists with userprocmask that cannot be resolved by the kernel being smart:
	 *      In a vfork() szenario, both the parent and child processes will continue to share VMs,
	 *      meaning that if the parent has the IS_A_USERPROCMASK_THREAD attribute set, the child
	 *      will also have the IS_A_USERPROCMASK_THREAD attribute set (see above). We can't simply
	 *      clear the IS_A_USERPROCMASK_THREAD attribute since user-space's libc will not have set
	 *      up a new TLS context for the vfork()'d child, meaning that the child will share its TLS
	 *      state with its parent (and as such, also has to share its IS_A_USERPROCMASK_THREAD).
	 *      As such, if a vfork()'d child makes use of sigprocmask(), the changes will be mirrored
	 *      in the parent thread as well.
	 *      The user-space `posix_spawn(3)' function from kos's libc.so is aware of this caveat and
	 *      can still be used execute a new program with an altered signal mask, however 3rd party
	 *      programs using vfork(), where the child process then calls sigprocmask() must be modified:
	 *      Old (unmodified) code:
	 *          >> ...
	 *          >> if ((cpid = vfork()) == 0) {
	 *          >>     ...
	 *          >>     sigprocmask(SIG_SETMASK, &child_mask, NULL);
	 *          >>     ...
	 *          >>     execl("/bin/some-program", "some-program", (char *)0);
	 *          >>     _Exit(127);
	 *          >> }
	 *          >> ...
	 *      New (fixed) code:
	 *          >> ...
	 *          >> sigset_t saved;
	 *          >> sigprocmask(0, NULL, &saved);
	 *          >> if ((cpid = vfork()) == 0) {
	 *          >>     ...
	 *          >>     sigprocmask(SIG_SETMASK, &child_mask, NULL);
	 *          >>     ...
	 *          >>     execl("/bin/some-program", "some-program", (char *)0);
	 *          >>     _Exit(127);
	 *          >> }
	 *          >> sigprocmask(SIG_SETMASK, &saved, NULL);
	 *          >> ...
	 *      Essentially, you just have to preserve the parent process's signal mask
	 *      before/after a call to vfork(2), essentially matching the assumption that
	 *      you're sharing your signal mask with the child process until it performs
	 *      a successful call to exec(2), or simply _Exit(2)'s
	 *      Portable code may also test if a macro `__ARCH_HAVE_SHARED_SIGMASK_VFORK'
	 *      is defined before using `vfork(2)', if they wish to support both types of
	 *      vfork flavors without having to include workarounds for one with the other.
	 *
	 *
	 * Example code:
	 * >> sigset_t os, ns;
	 * >> sigfillset(&ns);
	 * >> sigprocmask(SIG_SETMASK, &ns, &os);
	 * >> ...
	 * >> sigprocmask(SIG_SETMASK, &os, NULL);
	 *
	 * Implementation of libc's `sigprocmask()':
	 * >> struct userprocmask {
	 * >>     pid_t     pm_mytid;    // [const] TID of the thread (same as `set_tid_address(2)')
	 * >>     size_t    pm_sigsize;  // [const] == sizeof(sigset_t)
	 * >>     sigset_t *pm_sigmask;  // [KERNEL:READ|WRITE(1), USER:WRITE] Pointer to the current signal mask
	 * >>                            // The kernel may or' this with another mask when a signal handler
	 * >>                            // is invoked that contains a non-empty `sa_mask'
	 * >>     sigset_t  pm_pending;  // [KERNEL:WRITE,     USER:READWRITE] Set of pending signals
	 * >>                            // When a currently masked signal arrives, it's associated
	 * >>                            // bit is set to 1 in here.
	 * >>     // === End of user-kernel-ABI (below is only used by libc!)
	 * >>     sigset_t  pm_masks[2]; // Buffer for user-space signal masks
	 * >> };
	 * >>
	 * >>
	 * >> // New system calls
	 * >>
	 * >> // Register the address of the calling thread's userprocmask controller.
	 * >> // This also initializes `*pm_sigmask' and `pm_pending', such that
	 * >> // `*pm_sigmask' is filled with the current kernel-level signal mask,
	 * >> // as would be returned by `sigprocmask(2)', while `pm_pending' is
	 * >> // filled in with the equivalent of `sigpending(2)'
	 * >> // Additionally, the address of `&mymask' is stored alongside other
	 * >> // user-space TLS state pointers such as `set_tid_address(2)', and
	 * >> // the kernel may read from `*(&mymask)->pm_sigmask', and write to
	 * >> // `(&mymask)->pm_pending' (using atomic-or for the later) from this
	 * >> // point forth.
	 * >> // NOTE: Passing `NULL' for `ctl' disables userprocmask-mode, though
	 * >> //       before this is done, the kernel will copy the `pm_sigmask'
	 * >> //       of the previously set controller into its internal signal
	 * >> //       mask. (i.e. the one used outside of userprocmask-mode)
	 * >> // Note though that `pm_sigmask' is ignored for `SIGKILL' and `SIGSTOP'
	 * >> // Note also that this function replaces `set_tid_address(2)', such that
	 * >> // it negates a prior call to said function, while a future call to said
	 * >> // function will disable userprocmask, similar to passing `NULL'
	 * >> errno_t sys_set_userprocmask_address(struct userprocmask *ctl);
	 * >>
	 * >> // Check for pending signals, and keep on handling them until none are left
	 * >> // The [restart(must)] is necessary in order to ensure that _all_ unmasked
	 * >> // signals get handled until none are left, in case more than one signal
	 * >> // became available.
	 * >> [restart(must)] errno_t sys_sigmask_check(void);
	 * >>
	 * >>
	 * >> // Per-thread user-space signal mask controller
	 * >> __thread struct userprocmask mymask;
	 * >>
	 * >> // Run during startup, or lazily on first call to `libc:sigprocmask()'
	 * >> mymask.pm_sigsize = sizeof(sigset_t);
	 * >> mymask.pm_sigmask = &mymask.pm_masks[0];
	 * >> sys_set_userprocmask_address(&mymask);
	 * >>
	 * >> int sigprocmask(int how, sigset_t *ns, sigset_t *os) {
	 * >>     sigset_t *oldset, *newset;
	 * >>     oldset = mymask.pm_sigmask;
	 * >>
	 * >>     // Select a storage location for the new mask
	 * >>     newset = oldset + 1;
	 * >>     if (newset != &mymask.pm_masks[0] &&
	 * >>         newset != &mymask.pm_masks[1])
	 * >>         newset = &mymask.pm_masks[0];
	 * >>
	 * >>     if (os)
	 * >>         memcpy(os, oldset, sizeof(sigset_t));
	 * >>
	 * >>     // Initialize a new signal mask from the old one, `how', and the new one
	 * >>     init_sigset_for_sigprocmask(newset, how, oldset, ns);
	 * >>
	 * >>     // Atomically enable use of the new, updated mask
	 * >>     // From this point forth, signals sent to our thread will be masked by `newset'
	 * >>     ATOMIC_WRITE(mymask.pm_sigmask, newset);
	 * >>
	 * >>     // Optimization: If we know that no signal became unmasked, we don't
	 * >>     //               have to search for any pending, unmasked signals!
	 * >>     if (how == SIG_BLOCK)
	 * >>         return 0;
	 * >>
	 * >>     // Check previously pending signals became available
	 * >>     for (signo_t i = 1; i < NSIG; ++i) {
	 * >>
	 * >>         // HINT: Instead of testing each signal individually, this can be made
	 * >>         //       faster by first checking for non-zero words in `pm_pending',
	 * >>         //       which would test 32/64 signals at once, before checking if
	 * >>         //       any of them are unmasked!
	 * >>         if (sigismember(&mymask.pm_pending, i) && !sigismember(newset, i)) {
	 * >>
	 * >>             // Clear the set of pending signals (because the kernel won't do this)
	 * >>             // Also note that there is no guaranty that the signal that became
	 * >>             // avilable in the mean time is still available now. - The signal may
	 * >>             // have been directed at our process as a whole, and another thread
	 * >>             // may have already handled it.
	 * >>             sigemptyset(&mymask.pm_pending);
	 * >>
	 * >>             // Calls the kernel's `sigmask_check()' function
	 * >>             sys_sigmask_check();
	 * >>         }
	 * >>     }
	 * >>     return 0;
	 * >> }
	 *
	 * Additionally, libc can expose a pair of new, better-optimized signal mask
	 * functions that can be used to directly set the address of the used signal
	 * mask, allowing a program to pre-define/initialize a number of special-purpose
	 * signal masks, which it can then switch to/from, with the only remaining
	 * overhead being the checking for pending signals
	 * 
	 * >> // New user-space function:
	 * >> sigset_t *getsigmaskptr(void) {
	 * >>     return mymask.pm_sigmask;
	 * >> }
	 * >>
	 * >> // New user-space function:
	 * >> sigset_t *setsigmaskptr(sigset_t *ptr) {
	 * >>     sigset_t *result = mymask.pm_sigmask;
	 * >>     mymask.pm_sigmask = ptr;
	 * >>     for (signo_t i = 1; i < NSIG; ++i) {
	 * >>         if (sigismember(&mymask.pm_pending, i) && !sigismember(ptr, i)) {
	 * >>             sigemptyset(&mymask.pm_pending);
	 * >>             sys_sigmask_check();
	 * >>         }
	 * >>     }
	 * >>     return result;
	 * >> }
	 *
	 * Example usage:
	 * >> static sigset_t const fullmask = SIGSET_INIT_FULL;
	 * >> void my_function_that_mustnt_get_interrupted(void);
	 * >> void my_function(void) {
	 * >>     sigset_t *oldset;
	 * >>
	 * >>     // Mask all signals
	 * >>     // NOTE: `fullmask' can be const, since all of its bits are already 1,
	 * >>     //       and the kernel will only ever write to the current mask in
	 * >>     //       order to turn 0-bits into 1s (so no write would ever be done)
	 * >>     // However, this also assumes that `my_function_that_mustnt_get_interrupted()'
	 * >>     // doesn't include a call to `sys_sigprocmask(2)' (i.e. _NOT_ the library
	 * >>     // variant), since such a call would also try to write to `fullmask'
	 * >>     oldset = setsigmaskptr((sigset_t *)&fullmask);
	 * >>
	 * >>     my_function_that_mustnt_get_interrupted();
	 * >>
	 * >>     // Restore the old signal mask
	 * >>     setsigmaskptr(oldset);
	 * >> }
	 *
	 */


	/* Xorg X-Window server support roadmap.
	 *
	 * Run x as (from inside KOS):
	 *     $ xinit /bin/twm -- -dumbSched
	 *
	 * Current Blocker:
	 *     twm exits, saying it's lost the server connection once a key is pressed
	 *     following its startup, after which one gets dropped back to the text-mode
	 *     shell.
	 *     Looking at the logs, this seems to be the result of an X client timeout,
	 *     following the server ending up in a loop:
	 *     [2020-08-25T17:51:34.191668670:trace ] task[4].sys_sigprocmask(how: 00000001, set: 3EBB4B50, oset: NULL)
	 *     [2020-08-25T17:51:34.191864155:trace ] task[4].sys_gettimeofday(tv: 0x3ebb4cd8, tz: NULL)
	 *     [2020-08-25T17:51:34.192020225:trace ] task[4].sys_gettimeofday(tv: 0x3ebb4cd8, tz: NULL)
	 *     [2020-08-25T17:51:34.192173205:trace ] task[4].sys_select(nfds: 256, readfds: [16, 24, 29, 30], writefds: NULL, exceptfds: NULL, timeout: {tv_sec:588,tv_usec:689000})
	 *     [2020-08-25T17:51:34.192572138:trace ] task[4].sys_sigprocmask(how: 00000000, set: 3EBB4B5C, oset: 0x3ebb4adc)
	 *     [2020-08-25T17:51:34.192825751:trace ] task[4].sys_read(fd: 24, buf: 0x3ebb4b84, bufsize: 64)
	 *     [2020-08-25T17:51:34.193069713:info  ][tty:"console"] Background process group E120B55C [tid=4], thread E1A105BC [tid=4] tried to read
	 *     With the obvious problem that the server can't read from the terminal
	 *     input device, whilst being part of a background process group...
	 *     Problem here is that I don't really know what's wrong here. - POSIX
	 *     says that I'm not supposed to let background processes read from a
	 *     terminal, and X obviously tries to do exactly that (KOS implements
	 *     all of the standardized interfaces to change process groups, as well
	 *     as the groups bound to some TTY...)
	 *
	 * Additionally, the following happens (which is probably the actual cause):
[...]
[2020-08-25T17:51:23.384328892:trace ] task[3].sys_open(filename: "/lib/libX11.so.6", oflags: O_RDONLY|O_CLOEXEC)
[2020-08-25T17:51:23.384706517:trace ] task[3].sys_frealpath4(fd: 4, resolved: 0x1508b300, buflen: 256, flags: AT_REMOVEDIR|AT_READLINK_REQSIZE)
[2020-08-25T17:51:23.384984815:trace ] task[3].sys_pread64(fd: 4, buf: 0x7f7779c8, bufsize: 52, offset: 0)
[2020-08-25T17:51:23.385220018:trace ] task[3].sys_pread64(fd: 4, buf: 0x1508b3d0, bufsize: 96, offset: 52)
[2020-08-25T17:51:23.385430330:trace ] task[3].sys_maplibrary(addr: NULL, flags: 00000000, fd: 4, hdrv: 1508B3D0, hdrc: 3)
[2020-08-25T17:51:23.385750639:debug ][vm] Map 0DB16000...0DC4EFFF against 2 data parts
[2020-08-25T17:51:23.386458828:debug ][vm] Map 0DC4F000...0DC52FFF against 4 data parts
[...]
[2020-08-25T17:51:32.156885360:debug ][segfault] Fault at 100366AC (page 10036000) [pc=0DBB0890,0DBB0892] [ecode=0x6] [tid=3]
[2020-08-25T17:51:32.157267460:trace ][except] Propagate exception 0xff0e:0x1[0x100366ac,0x7] hand:[pc=DDFC2CD,sp=7F777C88] orig:[pc=DBB0892,sp=7F777CD8] fault:[pc=DBB0890] [mode=0x4003,tid=3]
[...]
[2020-08-25T17:51:34.127421459:trace ] task[3].sys_coredump(curr_state: 7F777924, orig_state: 7F777964, traceback_vector: 1508C044, traceback_length: 1, exception: 1508C088, unwind_error: 00000001)
[2020-08-25T17:51:34.129723581:error ][coredump] Creating coredump...
[2020-08-25T17:51:34.129851287:error ] exception 0xff0e:0x1 [E_SEGFAULT_UNMAPPED] [cr2=100366AC] [fwu-]
[2020-08-25T17:51:34.130122912:error ] 	pointer[0] = 100366AC
[2020-08-25T17:51:34.130228323:error ] 	pointer[1] = 00000007
[2020-08-25T17:51:34.130337412:error ] signal 11
[2020-08-25T17:51:34.130450881:error ] 	code:  1
DBB0890 [???:0,0:???] faultaddr
DBB0892 [???:0,0:???] orig_ustate
[2020-08-25T17:51:34.133526376:trace ][sched] Exiting thread E1A2A504 [tid=3]
	 *
	 * $ addr2line -ife bin/i386-kos-OD/lib/libX11.so 9A890
	 * _XkbReadCopyKeySyms
	 * /binutils/src/x/libX11-1.5.0/src/xkb/XKBRdBuf.c:84
	 *
	 *
	 * TODO:
	 *     - Finish implementing ancillary data support for unix domain sockets
	 *     - Properly implement libc's regex functions
	 *     - Patch Xorg-server to not try to make use of "/dev/ptmx"
	 *       KOS has an `sys_openpty(2)' system call for this purpose
	 *       Although I have to wonder why Xorg even needs PTYs...
	 */

	return state;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_BOOT_BOOT_C */
