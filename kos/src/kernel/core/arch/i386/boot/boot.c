/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#include <stddef.h>

#include <libpciaccess/pciaccess.h> /* pci_system_init() */

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
	 * NOTE: QEMU can  consistently  be  detected  via  `CPUID[0x80000002].EAX',
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
	 * patch  the  kernel  to  use  (rd|wr)msr  if unavailable. */
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

	/* Run task initialization callbacks on the boot task,  initializing
	 * important structures such as the r/w-lock descriptor and the task
	 * signal connection manager.
	 * NOTE: We do  this now  since r/w-locks  and signal  connections  are
	 *       required  by  the  Unwind-FDE cache  sub-system,  meaning that
	 *       they are also required for us to be able to handle exceptions.
	 * In other words: Only once this function has been called can we
	 *                 start   making   use  of   exceptions  safely. */
	kernel_initialize_scheduler_callbacks();

	/* Load multiboot information.
	 * NOTE: All  information provided by the bootloader is assumed
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
	 * NOTE: This must  be done  while the  physical identity  mapping is  still
	 *       in effect  (aka: before  `x86_initialize_mman_kernel()' is  called)
	 *       Additionally, do  this before  memory  zones have  been  finalized,
	 *       so we can manually add  SMP descriptor memory regions as  available
	 *       physical memory, while still preventing them from being overwritten
	 *       by zone initialization, regardless of what the bootloader/BIOS  did
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

	/* Since  we're about to  evaluate the kernel commandline
	 * for the first time (which parses the seed=... option),
	 * we  have to fill in the initial PRNG seed before then,
	 * so that when not receiving  that option, we'll end  up
	 * truly random initial seed.
	 * So we're just going to read the CMOS RTC state and use
	 * it to set the initial kernel seed. */
	x86_initialize_rand_entropy();

	/* Evaluate commandline options defined as `DEFINE_EARLY_KERNEL_COMMANDLINE_OPTION()' */
	kernel_initialize_commandline_options_early();

	/* Since `kernel_initialize_commandline_options_early()' may have overwritten  the
	 * initial seed set by `x86_initialize_rand_entropy()', only log the actually used
	 * seed now so that the system logs remain consistent with the user's expectation. */
	printk(FREESTR(KERN_INFO "[rand] Set pseudo RNG seed to %#.8" PRIx32 "\n"), krand_seed);

	/* Initialize  the x86_64 physical memory identity memory mapping.
	 * This can only be done _after_ we've loaded available RAM, since
	 * this function may need to allocate some of that memory... */
#ifdef CONFIG_PHYS2VIRT_IDENTITY_MAXALLOC
	x86_initialize_phys2virt64();
#endif /* !ONFIG_PHYS2VIRT_IDENTITY_MAXALLOC */

	/* Initialize the kernel mman, and instigate strict memory protection,
	 * unmapping virtual memory that isn't being used by the kernel, while
	 * also removing write permissions for  .text and .rodata, as well  as
	 * (if supported) setting the NOEXECUTE  bit for anything but  `.text'
	 * and `.xdata' / `.xbss'
	 * NOTE: This also unmaps the physical identity mapping found surrounding
	 *       the kernel, which was left in tact until this point in order  to
	 *       simplify  initialization of SMP  control structures (or anything
	 *       left in physical memory below the 1GiB mark). */
	x86_initialize_mman_kernel();

	/* Load generic text alternatives.
	 * Must happen after  `x86_initialize_mman_kernel', since this  one checks  for
	 * the presence of a LAPIC, which gets mapped in `x86_initialize_mman_kernel()' */
	x86_initialize_alternatives();

	/* Relocate memory information into higher memory, moving it away from
	 * being somewhere where it could  cause problems, or be  accidentally
	 * corrupted. */
	kernel_initialize_minfo_relocate();

	/* Initialize the ioperm() sub-system. */
	x86_initialize_iobm();

	/* Flush the entire TLB buffer, now that we're finished setting up the page directory.
	 * NOTE: Technically, this should be unnecessary, but it may still clean up some
	 *       caches that had become clobbered by our incessant modifications  above. */
	pagedir_syncall();

	/* Figure out how we want to implement the TSC (APIC+TSC, APIC or PIC) */
	x86_initialize_tsc();

	/* Initialize the APIC / PIC, as well as secondary CPUs when SMP is enabled. */
	x86_initialize_apic();

	/* Set-up the realtime clock resync interrupt */
	x86_initialize_tsc_resync();

	/* XXX: ioapic support (ioapic is the modern equivalent of the pic) */

#ifdef CONFIG_FPU
	/* Initialize the FPU sub-system. */
	x86_initialize_fpu();
#endif /* CONFIG_FPU */

	/* Make the kernel's .text and .rodata sections read-only. */
	x86_initialize_mman_kernel_rdonly();

	/* Initialize the PID sub-system for the boot task. */
	kernel_initialize_bootpid();

	/* Copy the kernel commandline into high memory. */
	x86_initialize_commandline_himem();

	/* Allocate and set the user-space mman for /bin/init */
	kernel_initialize_user_mman();

	/* Evaluate commandline options defined as `DEFINE_KERNEL_COMMANDLINE_OPTION()' */
	kernel_initialize_commandline_options_stable();

	/* Initialize builtin core drivers. */
	kernel_initialize_devfs_driver();
	pci_system_init();
	kernel_initialize_ide_driver();
	kernel_initialize_fat_driver();

	/* Load drivers provided by the bootloader */
	x86_initialize_bootloader_drivers();

	/* Release physical memory from minfo that was marked as `PMEMBANK_TYPE_PRESERVE'
	 * NOTE: This can only be done after bootloader drivers, since drivers provided
	 *       by  the   bootloader  are   themself  mapped   as  preserved   memory. */
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
	 * that the user started the  kernel with a boot=... commandline  parameter. */
	if unlikely(boot_partition == NULL)
		kernel_panic(FREESTR("Unable to detect boot partition (reboot with `boot=...')"));
	if unlikely(boot_partition == (struct basic_block_device *)-1)
		kernel_panic(FREESTR("Detected boot partition is ambiguous (reboot with `boot=...')"));

	/* TODO: Don't hard-code fat here. - Instead, try every currently loaded filesystem driver.
	 *       After   all:   The    bootloader   may   have    loaded   additional    drivers... */
	/* TODO: Move this mount() call into a different file. */
	path_mount(THIS_VFS, "fat", boot_partition, SUPERBLOCK_FNORMAL, NULL, NULL, true);

	/* Run self-tests. (if enabled) */
#ifdef CONFIG_SELFTEST
	kernel_initialize_selftest();
#endif /* CONFIG_SELFTEST */

	__hybrid_assert(!kmalloc_leaks());

#if 0
	decref(driver_insmod("iso9660", "a b foobar bazbaz"));
	{
		REF struct superblock *cd;
		cd = superblock_open("iso9660", "/dev/hdb");
		{
			SCOPED_READLOCK((struct mfile *)cd);
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

	/* TODO: In the kernel assertion check handler, add a hook that is set
	 *       by moddbx to print additional information about the values of
	 *       variables referenced by the assertion-expr.
	 *       Essentially, have moddbx look at the assertion expression and
	 *       scan it for  referenced variables/fields/array-elements,  and
	 *       print their values right there.
	 *       e.g.: assert(self->foo == 42);
	 *       Will automatically display the value of `self->foo' as part of
	 *       the initial assertion check screen.
	 *       Recognized expression token sequences should match:
	 *          EXPR      ::= UNARY [SUFFIX...]
	 *          UNARY     ::= KEYWORD | '(' TYPE_EXPR ')' EXPR | '(' EXPR ')' | '*' UNARY
	 *          SUFFIX    ::= '->' KEYWORD | '.' KEYWORD | '[' FULL_EXPR ']'
	 *          TYPE_EXPR ::= <Full, regular C type expression>
	 *          FULL_EXPR ::= <Full, regular C expression>
	 */

	/* TODO: Add  a user-space interface  for reading the  dmesg backlog, as well
	 *       as  establishing custom, pre-allocated  buffers for syslog messages,
	 *       essentially allowing user-space to register additional syslog sinks.
	 * Once added, make  use of  this API to  pipe syslog  messages written  by
	 * insmod(1) and rmmod(1) to stdout and stderr (based on message severity). */

	/* TODO: Alter all instances  where the kernel  currently uses <hybrid/sequence/atree.h>  to
	 *       instead make use of <hybrid/sequence/rbtree.h>. Doing this consistently may greatly
	 *       improve performance throughout the kernel:
	 *        - block_device_tree
	 *        - character_device_tree
	 *        - struct driver::d_eh_frame_cache
	 *        - struct superblock::s_nodes
	 * TODO: Also make use of RB-trees to implement `struct epoll_controller::ec_list' */

	/* TODO: Add `__USE_ISOC2X' to <features.h> */
	/* TODO: Add FLT_NORM_MAX, DBL_NORM_MAX and LDBL_NORM_MAX to <float.h> under #ifdef __USE_ISOC2X
	 *       Also add DEC32_TRUE_MIN, DEC64_TRUE_MIN and DEC128_TRUE_MIN, alongside everything  from
	 *       `__STDC_WANT_DEC_FP__'  under  `__USE_ISOC2X' (for  this  purpose, <hybrid/floatcore.h>
	 *       will also have to be adjusted) */

	/* TODO: The kernel->user-space exception/posix-signal system needs a re-write.
	 *       Right now, way too much of it resides in arch-specific code, and  it's
	 *       way too hard to understand the actual control-flow! */

	/* TODO: User-space VIO  callback  functions  should  only  be  allowed  to
	 *       throw  a  white-listed  sub-set  of  exceptions.  Or  better  yet:
	 *       user-space  VIO  exceptions  should  be  encapsulated  differently
	 *       whilst in kernel-space, such that they always appear as E_SEGFAULT
	 *       for as long as  a thread is in  kernel-space, but will be  changed
	 *       to  the original error code prior to returning back to user-space. */

	/* TODO: Now that we've got signal  completion callbacks, it's also possible  to
	 *       implement `SIGIO' and `O_ASYNC'.  Note that linux documentation  states
	 *       that O_ASYNC should work for ttys, ptys, sockets, pipes and fifos,  all
	 *       of which KOS is already implementing, but currently does so w/o support
	 *       for SIGIO.
	 *       Note that in  all of  these cases,  we can make  the jump  from the  NOBLOCK
	 *       world that  `sig_postcompletion_t' would  still be  stuck in  by posting  an
	 *       event to an async worker that is registered using  `register_async_worker()'
	 *       on a per-object basis. (and gets enabled/disabled as O_ASYNC is set/cleared)
	 *       Essentially, SIGIO should be send  whenever there's a rising-edge event  for
	 *       either readable or writable in the associated object. */

	/* TODO: Add drivers for loading binaries:
	 *   - binfmt_misc   Allows user-space to register custom interpreters
	 *                   for arbitrary magic byte sequences.
	 *                   s.a. linux:/proc/sys/fs/binfmt_misc
	 *   - a.out
	 *   - PE            maybe even implement this one as a user-space interpreter using
	 *                   `binfmt_misc'.  - That way it would be much safer to implement,
	 *                   as well as greatly reduce  future maintenance when kernel  APIs
	 *                   change (since it would use  the syscall apis, which are  _much_
	 *                   more stable in comparison)
	 *                   Also: portability,  and  would make  it easier  to pre-configure
	 *                   other aspects of the process state to enable windows  emulation,
	 *                   such  as changing the fsmode, binding DOS drives, and the direct
	 *                   integration of both the regular libdl.so, as well as a secondary
	 *                   program loader for dlls.
	 *                #1: /bin/peloader MyPeProgram
	 *                #2: Load    /bin/peloader   as   an   ELF   binary   like   normal,
	 *                    including  mapping  of   libdl.so  into   the  address   space.
	 *                    Note that /bin/peloader depends on libdl.so, but _NOT_ libc.so!
	 *                #3: In /bin/peloader, figure out what address ranges need to be
	 *                    preserved in order to be able to load the given PE  binary.
	 *                #4: If  the load-address of libdl overlaps with this range, make use
	 *                    of `DLAUXCTRL_RELOC_LIBDL' to move libdl to a different location
	 *                #5: Load  both libc.so and a helper library libpe.so using a custom
	 *                    dlauxctrl() command code that allows  one to load libraries  at
	 *                    custom addresses. (the load addresses used get calculated  such
	 *                    that they don't overlap with where the ranges used by the given
	 *                    PE binary)
	 *                #6: Jump to the primary entry point in libpe.so, and load the PE
	 *                    binary from there.
	 *             ... Thinking this over, I think it's better to just write a driver to
	 *                 load the PE binary in-place, and have a user-space shared library
	 *                 libpe.so  that does all  of the user-space initialization/dynamic
	 *                 linking (libpe.so would then depend on libdl.so and libc.so)
	 */

	/* TODO: Add a way for user-space to manually mmap() the kernel's libdl.so into  their
	 *       address space. Using this functionality, add `DLAUXCTRL_RELOC_LIBDL' to libdl
	 *       which can be used  to relocate libdl itself  within one's own address  space.
	 *       This control function would then do the following:
	 *        - Map a  new copy  of libdl.so  at the  specified location  (if that  location
	 *          overlaps with the current location, recursively call `DLAUXCTRL_RELOC_LIBDL'
	 *          with yet another location that doesn't overlap, thus essentially  relocating
	 *          the library twice in order to prevent overlaps every time)
	 *        - Go  through the relocations  of all loaded libraries  and recalculate them if
	 *          those relocations reference symbols from / point into the old libdl's address
	 *          space.
	 *        - Directly jump into the secondary copy  of libdl (aside from changing  the
	 *          absolute program counter position, this jump should be entirely seamless)
	 *        - munmap() the old instance of libdl
	 * XXX: This seems like a rather large function (at least the part about having to re-do
	 *      all of the relocations does).  - Maybe not implement this  as part of the  libdl
	 *      core, but rather within some auxiliary helper library? */

	/* TODO: Make the x86 LDT object ATTR_PERMMAN, and reload LDT registers during an mman
	 *       switch. On linux,  they're PERMMAN,  too, so we  really should  do the  same. */

	/* TODO: deemon's module system appears somewhat broken on KOS.
	 *       Fix stuff both in KOS, and DEEMON itself until the following works from within KOS:
	 *       $ deemon --help /deemon/string
	 *
	 *       >> IllegalInstruction: Illegal instruction at <anonymous>+001A
	 *       >> /usr/lib/deemon/doctext.dee(148,1) : <anonymous>+001A
	 *       >> /usr/lib/deemon/doc.dee(2537,34) : __str__+0002
	 *       >> /usr/lib/deemon/doc.dee(3823,33) : __str__+0051
	 *       Also: In certain cases, this causes both the doc and doctext module's dec
	 *             files to constantly get re-compiled  (though in other cases,  these
	 *             exact dec files also get accepted as valid, possibly related to how
	 *             they've been imported, implying a problem within the deemon core)
	 *       NOTE: I'm assuming that the IllegalInstruction is caused by some discrepancy
	 *             between the hand-written assembly RT engine, and the one written in  C
	 *
	 *       >> UnicodeDecodeError: Invalid utf-8 character byte 0x85
	 *       >> /usr/lib/deemon/doc.dee(2537,34) : __str__+0002
	 *       >> /usr/lib/deemon/doc.dee(3823,33) : __str__+0051
	 *       When the dec files already exist, this error is thrown instead.
	 *
	 * TODO: Deemon's   SystemFile.size()   function   always   uses    lseek64()
	 *       Change this to where it first attempts to use fstat() (if available)
	 * TODO: Deemon's main() function should try to re-configure mallopt()  during
	 *       init in order to optimize itself  for using large amounts of  memory.
	 *       Currently,  running deemon causes  the system log  to be spammed with
	 *       calls to mmap() (an overallocation of 32768 bytes might work well...)
	 * TODO: When opening a dec file, use mmap() (if available) and malloc()+read()
	 *       as    fall-back,    rather   than    always    using   malloc()+read() */

	/* TODO: HOP_HANDLE_CREATE_STREAM
	 *       Constructs a wrapper  for another  handle object that  includes a  `pos_t'
	 *       file  offset to implement read(), write() and lseek() by dispatching these
	 *       operators through pread(), pwrite() and fstat() (fstat for `stat::st_size'
	 *       with lseek(SEEK_END))
	 *       -> Useful for turning UVIO objects into file-like objects. */

	/* TODO: Play around with `no_caller_saved_registers'
	 *       It may be possible to cut down on boiler-plate assembly needed to wrap
	 *       simple C-level interrupt handlers and/or system calls, by not  needing
	 *       to save registers that wouldn't be used in any case! */

	/* TODO: renameat2() is missing from <stdio.h> */

	/* TODO: Add auto-completion to the `cpuid' debugger command.
	 *       We can easily determine valid leafs by looking at the value of CPUID[0].EAX! */

	/* TODO: Now that there's once again a packet-buffer controller,
	 *       add  support  for  pipe2(O_DIRECT)  (aka.  packet-mode)
	 *       Do this via new handle types:
	 *        - HANDLE_TYPE_PACKET_PIPE
	 *        - HANDLE_TYPE_PACKET_PIPE_READER
	 *        - HANDLE_TYPE_PACKET_PIPE_WRITER */

	/* TODO: `x86_64-kos-gcc -mno-red-zone -print-libgcc-file-name'
	 *       This will still print the normal libgcc.a filename, which
	 *       wasn't built with support for -mno-red-zone.
	 * >> https://wiki.osdev.org/Libgcc_without_red_zone */

	/* TODO: The builtin  debugger's disassembler  should  show the  values  of
	 *       registers used in the current instruction, as well as the contents
	 *       of memory operands. */

	/* TODO: The builtin debugger should contain a graphical applet that combines
	 *       the functionality of the `lsthread', `thread', `trace', `l' and  `r'
	 *       commands. */

	/* TODO: Trigger `DEBUGTRAP_REASON_VFORK' and `DEBUGTRAP_REASON_VFORKDONE'
	 *       at appropriate locations within the kernel. */

	/* TODO: System calls that we're never going to implement (because linux doesn't
	 *       implement them either) should all get routed to `sys_break', instead of
	 *       having their own routing function each.
	 *       Furthermore, these system calls should not be exported by-name from libc */

	/* TODO: System calls that are called extremely rarely (e.g.  sethostname(2))
	 *       should  not have a  fast-pass function each.  Instead, only a single
	 *       wrapper should exist for them, and that wrapper should then dispatch
	 *       the system call via `x86_sysrouteN_c[32|64]'
	 *       This way, we may be able to reduce the kernel's binary size. */

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

	/* XXX: Add a smart, arch-specific unwinder to libdebuginfo that will inspect
	 *      the instruction  stream  to  figure  out how  to  unwind  the  stack.
	 *      This unwinder should assume the default calling convention for  every
	 *      possible  case, and  should indicate  unwind success  once a ret-like
	 *      instruction is encountered: `ret', `lret' or `iret'
	 *
	 *      Conditional branch instruction should be unwound by remembering  the
	 *      current CPU state,  and recursively  unwinding on both  ends of  the
	 *      jump. Only if both  ends end up with  a successful unwind, and  only
	 *      if both ends  result in all-identical  callee-preserve registers  is
	 *      the unwind to-be considered successful. If a jump ends up going back
	 *      on itself, its branch should simply be ignored (but if all  branches
	 *      end up being ignored, unwinding also fails) */

	/* Xorg X-Window server support roadmap.
	 *
	 * from inside KOS:
	 *     $ xinit /bin/xclock -- -dumbSched
	 *
	 * TODO:
	 *     - Finish implementing ancillary data support for unix domain sockets
	 *     - Properly implement libc's regex functions
	 */

	/* TODO: libgen/c  should insert 1 blank line prior to the comment block
	 *       of a function if that block is immediately preceded by a #endif
	 *       or another function's declaration. */

	/* TODO: Don't #define __builtin_unreachable() in <__crt.h> to __crt_unreachable()
	 *       Instead  look into `-fsanitize=unreachable' (which does something similar
	 *       on  a compiler-basis  and won't make  the library call  mandatory for all
	 *       code compiled with debug enabled) */

	/* TODO: Look into enabling `-fsanitize=signed-integer-overflow' for all code... */

	/* TODO: Add a KOS-specific libcrypt */

	/* FIXME: There is a design flaw in how the builtin debugger behaves when
	 *        entered while another thread is currently initializing parts of
	 *        a mem-part.
	 * When this happens, said part contains `MPART_BLOCK_ST_INIT' blocks, but
	 * those blocks won't actually end up being properly initialized until the
	 * debugger is exited once again and the thread that was doing the init is
	 * allowed to finish.
	 * However, if the debugger ends up  accessing that same region of  memory,
	 * it will begin to wait for the initialization to be completed or aborted,
	 * neither of which will ever happen  since the thread that is  responsible
	 * is currently suspended.
	 *
	 * Solution: alter  `mo_loadblocks' and `mo_saveblocks' such that they will
	 * return immediately but take an aio_handle that is invoked asynchronously
	 * once  initialization is completed.  That callback could  then be made to
	 * undo the `MPART_BLOCK_ST_INIT' status  and broadcast the finish  signal.
	 * After all: async stuff continues to work within the debugger!
	 * Problem: This would still leave a race when the debugger is entered before
	 *          the  async job is  started, but after INIT  states have been set.
	 *          Admittedly, this is a small time  frame, but it could happen  and
	 *          would result in  the same deadlock  scenario that's happening  at
	 *          the moment already.
	 *
	 * Functions that set (and eventually clear) `MPART_BLOCK_ST_INIT':
	 *   - mpart_memload_and_unlock   (Blocking call is `file->mf_ops->mo_loadblocks')
	 *   - mpart_hinted_mmap          (Unaffected; is NOBLOCK+NOPREEMPT; iow: debugger can't be entered in here)
	 *   - mpart_setcore_or_unlock    (Blocking call is `setcore_ex_load_from_swap()')
	 *   - mpart_load_or_unlock       (Blocking call is `file->mf_ops->mo_loadblocks')
	 *   - mpart_sync_impl            (Blocking call is `file->mf_ops->mo_saveblocks')
	 *
	 */

	/* TODO: Finish implementing support for .eh_frame_hdr.
	 * Done:
	 *   - The section is being loaded alongside .eh_frame (if necessary)
	 * Missing:
	 *   - Like `libdl.so', `struct userelf_module' must also include special handling
	 *     when trying to  lock a section  named ".eh_frame_hdr", in  that if no  such
	 *     section exists in SHDRS, check if a PHDR of type `PT_GNU_EH_FRAME'  exists.
	 *     If so, use that  header to create  a faux section  object that is  returned
	 *     when requesting ".eh_frame_hdr"
	 *   - The .eh_frame_hdr section isn't being processed / parsed. Note that
	 *     it  behaves similar to  .eh_frame, but differs  in that it contains
	 *     a lookup-table like:
	 *         >> [{ pc_min: pointer, pc_max: pointer, eh_frame_data: pointer }...]
	 *     I couldn't find documentation on  the actual format, but glibc  has
	 *     a file that is used to parse this header, so it can tell how that's
	 *     supposed to be done.
	 */

	/* TODO: When system memory gets low, unload unused (iow: not currently mapped)
	 *       portions  of mem-parts. This is why we have the `mpart_all_list' list!
	 * Also: When unloading unused parts isn't enough, we could also try to
	 *       off-load    not-recently-accessed     parts     into     swap. */

	/* TODO: iconv extensions (take a look at FreeBSD's <iconv.h> header) */

	/* TODO: The "include-everything.h" test has grown so large that there might be
	 *       a  risk of getting out-of-memory compiler errors when trying to build.
	 * Solution: The act of building these files should be opt-in, probably based
	 *           on the presence of some kind of  file not part of the git.  That
	 *           way,  someone trying to  build KOS for the  first time won't run
	 *           into  this  issue, and  I can  continue to  have this  test run,
	 *           knowing how to deal with the out-of-memory issue. */

	/* TODO: Look into how  best to protect  from "over-long" utf-8  encodings
	 *       when it comes to our implementation of functions from <unicode.h> */

	/* TODO: Kernel functions that return `struct heapptr' should be altered
	 *       to use the same return-through-register  trick as is also  used
	 *       in  `/kos/src/libservice/com.h'  for  `service_buf_t',  as   it
	 *       allows GCC to make better use of registers! */

	/* TODO: Change `format_escape()' to include explicit configuration options
	 *       for  data being UTF-8 or raw bytes, with the default configuration
	 *       being to determine automatically (that is: assume utf-8 unless the
	 *       string contains byte-sequences  not allowed  for utf-8,  including
	 *       incorrect multi-character sequences, as well as overly long chars) */

	/* TODO: Support for `PT_GNU_STACK'
	 *   - Add handling in modelfexec
	 *   - Keep  track of requirements  in libdl during  the initial load phase
	 *     If requirements change while the initial set of libraries is loaded,
	 *     then mprotect() the main thread's stack to alter protection.
	 *   - Expose a dlauxctrl() code to query needed stack protection (with
	 *     a default of PROT_READ|PROT_WRITE)
	 *   - pthread_create must use that control code to figure out to map
	 *     new thread stacks. */

	/* TODO: Look into enabling `-fsanitize=undefined' for all code. */

	/* TODO: The raiseat(2) system call should be removed. Instead, it can be emulated
	 *       by  chaining `sigreturn(2)' with  `rt_tgsigqueueinfo(2)', where the later
	 *       is made to point at the calling thread. */

	/* TODO: All places  that clear  the current  exception by  means of  setting
	 *       this_exception_code to E_OK should also include a call to DBG_memset
	 *       for filling the remainder  of exception_info (except for  ei_nesting
	 *       and ei_flags) with 0xcc bytes. */

	/* TODO: Create an assembler similar to /kos/misc/libgen/cfi/comp.dee for RPC
	 *       programs. As a matter of fact, the CFI compiler can pretty much just
	 *       be copied verbatim, and the RPC compiler can then be modified to get
	 *       rid of the operand-range checks while being given support for all of
	 *       the instructions not found in CFI. */

	return state;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_BOOT_BOOT_C */
