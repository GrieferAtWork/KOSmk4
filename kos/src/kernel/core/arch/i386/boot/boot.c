/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_BOOT_BOOT_C
#define GUARD_KERNEL_CORE_ARCH_I386_BOOT_BOOT_C 1
#define DISABLE_BRANCH_PROFILING /* Don't profile this file */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/boot.h>
#include <kernel/driver-param.h>
#include <kernel/fpu.h> /* CONFIG_FPU */
#include <kernel/malloc.h>
#include <kernel/mman/driver.h>
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

DECL_BEGIN

PUBLIC ATTR_USED ATTR_SECTION(".bss")
struct fcpustate32 boot_cpustate;
PUBLIC ATTR_USED ATTR_SECTION(".data.cold")
struct boot_device_info boot_device = { 0xff, 0xff, 0xff, 0xff };

INTDEF port_t x86_syslog_port;

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
	if (/* Normal QEMU                         */ sys86_isqemu() ||
	    /* QEMU when running with `-accel hax' */ sys86_isqemu_accel()) {
		x86_syslog_port = (port_t)0x3f8;
	} else if (sys86_isbochs()) {
		x86_syslog_port = (port_t)0xe9;
	} else if (sys86_isvbox()) {
		x86_syslog_port = (port_t)0x504;
#ifdef CONFIG_VBOXGDB
		if (_sys86_isvboxgdb())
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

	/* Do some more initialization of the scheduling system that can only
	 * be done after everything SMP-related has already been initialized. */
	kernel_initialize_scheduler_after_smp();

	/* XXX: ioapic support (ioapic is the modern equivalent of the pic) */

#ifdef CONFIG_FPU
	/* Initialize the FPU sub-system. */
	x86_initialize_fpu();
#endif /* CONFIG_FPU */

	/* Make the kernel's .text and .rodata sections read-only. */
	x86_initialize_mman_kernel_rdonly();

	/* Copy the kernel commandline into high memory. */
	x86_initialize_commandline_himem();

	/* Allocate and set the user-space mman for /bin/init */
	kernel_initialize_user_mman();

	/* Evaluate commandline options defined as `DEFINE_KERNEL_COMMANDLINE_OPTION()' */
	kernel_initialize_commandline_options_stable();

	/* Initialize builtin core drivers. */
	pci_system_init();
	kernel_initialize_ide_driver();
	kernel_initialize_fat_driver(); /* TODO: This can be done with static init! */

	/* Load drivers provided by the bootloader */
	x86_initialize_bootloader_drivers();

	/* Release physical memory from minfo that was marked as `PMEMBANK_TYPE_PRESERVE'
	 * NOTE: This can only be done after bootloader drivers, since drivers provided
	 *       by  the   bootloader  are   themself  mapped   as  preserved   memory. */
	minfo_release_preservations();

	/* Initialize (load dependencies, apply relocations & call constructors)
	 * all of the drivers provided by the bootloader. */
	kernel_initialize_loaded_drivers();

	/* Load late commandline options. */
	kernel_initialize_commandline_options_late();

	/* TODO: If we weren't able to figure out the boot device, check if we can
	 *       somehow make use of the `boot_device' information which was given
	 *       to us by the bootloader... */
	printk(KERN_INFO "boot_device = { %#" PRIx8 ", %#" PRIx8 ", %#" PRIx8 ", %#" PRIx8 " }\n",
	       (u8)boot_device.bdi_biosdev,
	       (u8)boot_device.bdi_partition,
	       (u8)boot_device.bdi_sub_partition,
	       (u8)boot_device.bdi_sub_sub_partition);

	/* Mount the root filesystem. */
	kernel_initialize_rootfs();

	/* Run self-tests. (if enabled) */
#ifdef CONFIG_SELFTEST
	kernel_initialize_selftest();
#endif /* CONFIG_SELFTEST */

	__hybrid_assert(!kmalloc_leaks());

	decref(driver_insmod("sctrace"));

	/* Update the given initial user-state to start
	 * executing /bin/init (or whatever was passed as `init=...') */
	state = kernel_initialize_exec_init(state);

	printk(FREESTR(KERN_INFO "Initial jump to user-space [pc=%p] [sp=%p]\n"),
	       icpustate_getpc(state),
	       icpustate_getsp(state));

	/* TODO: libdebuginfo freezes with -gdwarf-2
	 * TODO: Check if it still does this (it's been quite a while since I wrote that TODO) */

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

	/* TODO: Add `__USE_ISOC2X' to <features.h> */
	/* TODO: Add FLT_NORM_MAX, DBL_NORM_MAX and LDBL_NORM_MAX to <float.h> under #ifdef __USE_ISOC2X
	 *       Also add DEC32_TRUE_MIN, DEC64_TRUE_MIN and DEC128_TRUE_MIN, alongside everything  from
	 *       `__STDC_WANT_DEC_FP__'  under  `__USE_ISOC2X' (for  this  purpose, <hybrid/floatcore.h>
	 *       will also have to be adjusted) */

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
	 *   - a.out */

	/* TODO: Once PE works, also add  a library `libpdb' for  extracting
	 *       file/line  information  from *.pdb  files, as  generated by
	 *       vc/vc++. One of the old KOSmk* was already able to do this. */

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

	/* TODO: Deemon's   SystemFile.size()   function   always   uses    lseek64()
	 *       Change this to where it first attempts to use fstat() (if available)
	 * TODO: Deemon's main() function should try to re-configure mallopt()  during
	 *       init in order to optimize itself  for using large amounts of  memory.
	 *       Currently,  running deemon causes  the system log  to be spammed with
	 *       calls to mmap() (an overallocation of 32768 bytes might work well...)
	 * TODO: When opening a dec file, use mmap() (if available) and malloc()+read()
	 *       as    fall-back,    rather   than    always    using   malloc()+read() */

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

	/* XXX: Add a smart, arch-specific unwinder to libdebuginfo that will inspect
	 *      the instruction  stream  to  figure  out how  to  unwind  the  stack.
	 *      This unwinder should assume the default calling convention for  every
	 *      possible  case, and  should indicate  unwind success  once a ret-like
	 *      instruction is encountered: `ret', `lret' or `iret'
	 *
	 *      Conditional branch instruction should be unwound by remembering  the
	 *      current CPU state,  and recursively  unwinding on both  ends of  the
	 *      jump. Only if both  ends end up with  a successful unwind, and  only
	 *      if both ends  result in all-identical  callee-preserve registers, is
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

	/* TODO: Don't #define __builtin_unreachable() in <__crt.h> to __crt_unreachable()
	 *       Instead  look into `-fsanitize=unreachable' (which does something similar
	 *       on  a compiler-basis  and won't make  the library call  mandatory for all
	 *       code compiled with debug enabled) */

	/* TODO: Look into enabling `-fsanitize=signed-integer-overflow' for all code... */

	/* TODO: Add a KOS-specific libcrypt */

	/* TODO: Investigate into an execution-time profiling system (using some kind
	 *       of hardware timer interrupt) that can be used to collect the program
	 *       counter positions where the system spends most of its time, so  that
	 *       those sub-routines can get more love & care for optimization. */

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
	 *     I  couldn't find documentation on the actual format, but glibc has
	 *     a file that is used to parse this table, so it can tell how that's
	 *     supposed to be done.
	 */

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

	/* TODO: Change `format_escape()' to include explicit configuration options
	 *       for  data being UTF-8 or raw bytes, with the default configuration
	 *       being to determine automatically (that is: assume utf-8 unless the
	 *       string contains byte-sequences  not allowed  for utf-8,  including
	 *       incorrect multi-character sequences, as well as overly long chars) */

	/* TODO: Support for `PT_GNU_STACK'
	 *   - Add handling in modelf
	 *   - Keep  track of requirements  in libdl during  the initial load phase
	 *     If requirements change while the initial set of libraries is loaded,
	 *     then mprotect() the main thread's stack to alter protection.
	 *   - Expose a dlauxctrl() code to query needed stack protection (with
	 *     a default of PROT_READ|PROT_WRITE)
	 *   - pthread_create must use that control code to figure out how to map
	 *     new thread stacks. */

	/* TODO: Look into enabling `-fsanitize=undefined' for all code. */

	/* TODO: All places  that clear  the current  exception by  means of  setting
	 *       this_exception_code to E_OK should also include a call to DBG_memset
	 *       for filling the remainder  of exception_info (except for  ei_nesting
	 *       and ei_flags) with 0xcc bytes. */

	/* TODO: During unwinding, .cfi_signal_frame must result in the NEXT stack-frame
	 *       searching for the associated FDE _NOT_  decrementing its PC by 1.  Note
	 *       that this should only affect  the _NEXT_ stack-frame, as signal  frames
	 *       are meant to be used for  interrupt/signal handlers, in which case  the
	 *       return  PC may already point to the start of a function (as is the case
	 *       when an interrupt arrives during execution of a function's first instr,
	 *       which then has to be restarted after the interrupt completes, which  is
	 *       done  by having the interrupt return to  the start of said first instr,
	 *       meaning that decrementing mustn't be done) */

	/* TODO: Figure out when `struct mfile::mf_atime' needs to be updated.
	 *  - Every time read(2) is called?
	 *  - Only when open(2)-ing the file?
	 *  - And what about mmap(2)?
	 *  - Path traversal when the directory doesn't have `MS_NODIRATIME' set.
	 * Also:
	 *  - MS_STRICTATIME -- what exactly does this one do?
	 *  - MS_LAZYTIME    -- I do get this one, but it might be kind-of hard for KOS to support
	 * Idea: Add to `struct fsuper': `uintptr_t fs_filexflags'
	 *       When  adding nodes to  the super's node-tree, do:
	 *       >> `node->mf_flags |= super->fs_filexflags;'
	 */

	/* TODO: `MFILE_F_NOATIME' and `MFILE_F_NOMTIME' can only be inherited from
	 *       the associated superblock _AFTER_ acquiring `fsuper_nodes_write()'
	 *       for the purpose of adding the node to the superblock. */

	/* TODO: Properly implement the system for changing superblock flags (as can
	 *       be done by `mount(2)'). Note that some of the flags need to cascade
	 *       down to every  file-node of the  superblock (`MFILE_F_NOATIME'  and
	 *       `MFILE_F_NOMTIME'),  which  may  only  be  done  (atomically) while
	 *       enumerating the super's node-tree and holding `fsuper_nodes_read()' */

	/* TODO: Re-write `struct heap' with lockop support */

	/* TODO: Re-write `kram-unmap.c' to support all types of file mappings, as well as
	 *       to make use of lockops  in heap structures for  the purpose of doing  new
	 *       allocations needed for unmapping memory. */

	/* TODO: mfile_truncate() needs some  kind of fs-level  operator for the  purpose
	 *       of deallocating file data beyond a certain point within the file stream.
	 * e.g.: On FAT, truncate the cluster chain to a certain length.
	 * XXX:  I  think the  solution here would  be to override  streams-truncate on the
	 *       fs-layer, acquire fs-specific locks (which already need to be non-atomic),
	 *       prepare for  fs-specific  truncation,  do  `mfile_truncate',  do  the  fs-
	 *       specific truncation, then release locks. */

	/* TODO: The devfs root directory rename() operator should really be  re-written
	 *       from scratch (and the ramfs one should be, too). Both don't really work
	 *       correctly  with all of  the special AT_RENAME_*  flags, since they were
	 *       implemented before I learned about unix rename() semantics... */

	/* TODO: `system_clearcache()' needs to be a blocking function (and can be
	 *       as well, since it only  gets called automatically in the  context
	 *       of allocating operations)
	 * This sort of change is also needed in order to allow known-blocking  ops
	 * that  need to happen inside, including the synchronous unloading of mem-
	 * parts (which if you at it in an objective way, is the _main_ way through
	 * which  an OS can reclaim memory, as  this includes the unloading of file
	 * buffers)
	 *
	 * Solution: there are still situations where system_clearcache() _should_
	 *           be  atomic. As such, it'd probably be  best to just add a new
	 *           param: `gfp_t flags', which is allowed to include GFP_ATOMIC.
	 *
	 * It may also  be a  good idea  to add  2 more  arguments:
	 * >> void (FCALL *retry_alloc)(void *cookie), void *cookie
	 *
	 * that represent a pair  of functions occasionally called  in-between
	 * having done different things to free up memory. This function could
	 * then  be used to stop the clearing  of caches as soon as sufficient
	 * system resources have  become available to  satisfy the  allocation
	 * attempted by the caller. */

	/* TODO: `struct epoll_controller::ec_lock' must be an atomic lock.
	 *       Otherwise, anything that wants to acquire this lock  would
	 *       have to be marked as `BLOCKING' */

	/* TODO: `uvio_create()'  should take the initial-size argument that
	 *       is passed to `sys_userviofd(2)' (with the new FS, that size
	 *       becomes relevant and must be stored in `mf_filesize') */

	/* TODO: Lots of places throughout the kernel still talk about  "datablock"s;
	 *       they're called "mfile"s. The same also goes for "datapart" ("mpart") */

	/* TODO: Refactor `vio_operators' -> `vio_ops' */

	/* TODO: Add support for /proc/[PID]/mem,  including the ability to  mmap
	 *       the resulting file (by having the special node object  implement
	 *       a custom mmap operator! _NOT_ by providing a loadblocks operator
	 *       that will copy data from the other process).
	 * For this, the mmap() operator needs  to be expanded with an  address-hint
	 * argument that will be the verbatim  `pos' passed to `mmap(2)' (the  other
	 * `maplibrary(2)' system call always passes `0' for this argument), and the
	 * mmap operator itself is also allowed  to modify this position, with  mmap
	 * then using the modified value.
	 * As such, it should probably be added to the handle_mmap_info structure.
	 *
	 * The /proc/[PID]/mem file's mmap operator then uses that hint in order  to
	 * select the mnode who's mn_part->mp_file should be mmap'd in the new proc,
	 * before adjusting the file-offset to-be mapped such that the  file-address
	 * to map will equal the file-address that was mapped at the specified  addr
	 * within the original mman:
	 *
	 * >> fd_t fd = open("/path/to/some/file", O_RDONLY);
	 * >> struct stat st;
	 * >> fstat(fd, &st);
	 * >> void *addr = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
	 * >>
	 * >> // This is where the magic happens: create a new mapping of at
	 * >> // least 1 byte that is an alias for the mapping at "addr + 42"
	 * >> fd_t mymaps = open("/proc/self/maps", O_RDONLY);
	 * >> void *alias = mmap(NULL, 1, PROT_READ, MAP_SHARED, mymaps, (pos_t)addr + 42);
	 * >> assert(*(byte_t *)alias == *((byte_t *)addr + 42));
	 *
	 * Note that this really only works if the original mapping was  MAP_SHARED
	 * and  not backed by an anonymous file. Try to mmap an anonymous file such
	 * as a /dev/zero mapping will just give you another anonymous (and totally
	 * unrelated) mapping. */

	/* TODO: We can emulate banked video memory as linear by using a
	 *       custom mfile that maps overrides a new operator  that's
	 *       yet to  be added  but will  behave similar  to what  is
	 *       currently  being done for  physical identity on x86_64,
	 *       in that it allows for  custom behavior routing of  phys
	 *       addresses.
	 * Combined with a modified version of `mfile_parts_denywrite_or_unlock'
	 * that  not only  denies write but  also reads, it  becomes possible to
	 * do  lazy  bank switching  as linear  memory  of different  banks gets
	 * accessed!
	 *
	 * For this purpose, we need 3 operators:
	 *  - BEFORE_FAULT_OR_UNLOCK: Called at the start of `mfault_or_unlock'
	 *                            while already holding a lock to the mpart
	 *                            This operator is allowed to release locks
	 *                            to indicate a restart request
	 *  - AFTER_FAULT_ABORT:      NOBLOCK+NOTHROW; called after BEFORE_FAULT_OR_UNLOCK
	 *                            already succeeded, but some later set failed and the
	 *                            fault is either aborted or restarted.
	 *  - AFTER_FAULT_COMMIT:     NOBLOCK+NOTHROW; called after pagedir_mmap() of the
	 *                            faulted area.
	 */

	/* TODO: Add a way for driver parameters to be supplemented by the kernel commandline.
	 *       Drivers loaded later should  still be able to  take parameters from the  boot
	 *       commandline, such as the default-resolution arguments of modsvga which should
	 *       really also be read from the that source! */

	/* TODO: vesa exposes the preferred resolution via a command:
	 *       https://wiki.osdev.org/EDID
	 * Use this as default values in modsvga! */

	/* TODO: Check out `readelf kernel.bin' for .text.local.* sections that:
	 *  #1: Indicate function that should be marked as [kernel] in libc/magic
	 *  #2: Need to be inlined into .text */

	/* TODO: Refactor all of the ioctls from <kos/ioctl/...> to use the <SYSTEM>_IOC_<COMMAND> format. */

	/* TODO: Add SVGA_IOC_* ioctls for:
	 *  - sco_setdisplaystart
	 *  - sco_setlogicalwidth
	 * Also add corresponding read-ioctls that will read the relevant properties.
	 */

	/* TODO: `HANDLE_TYPEKIND_MFILE_*' needs to be expanded with all of the new sub-classes of MFILE,
	 *       as well as all of the subclasses of those types. The system should be designed such that
	 *       sub-class  type IDs can easily be used to test for parent classes, given a precise child
	 *       class ID; e.g. `HANDLE_TYPEKIND_MFILE_ISNODE(x)' checks for FNODE and all fnode-subs. */

	/* TODO: mo_loadblocks/mo_saveblocks document:
	 * >> @assume(addr + num_bytes <= mfile_partaddr_ceilalign(self, self->mf_filesize));
	 * This assertion is being adhered  to, but if you think  about it, this is  actually
	 * incorrect. Instead, what should really be the requirement is:
	 * >> @assume(addr + num_bytes <= mfile_blockaddr_ceilalign(self, self->mf_filesize));
	 *
	 * iow: it should be the BLOCK-ceil-aligned size of the file that represents the upper
	 *      limit for up to where I/O is allowed, and not the PART-ceil-aligned file size,
	 *      which may be larger because PART-aligned also implies page-aligned.
	 *
	 * Because of this, up to  PAGESIZE-SECTOR_SIZE out-of-bounds bytes might be  accessed
	 * on a (theoretical) hdd who's size isn't divisible by PAGESIZE. Granted, this likely
	 * isn't something that exists, but it's still a design flaw...
	 *
	 * As a counter-example, the O_DIRECT implementation  makes proper use of the  file's
	 * block-aligned size, and thus will not attempt block-level access beyond the block-
	 * aligned file size. */

	/* TODO: Mounting  points shouldn't be  holding those hacky references  to drivers in order
	 *       to keep potential statically allocated  structures alive. - Instead, drivers  such
	 *       as procfs must  set the  destructor of their  singleton superblock  to a  function
	 *       exported by the kernel which will decref() the associated driver when the struct's
	 *       refcnt hits zero.
	 * Furthermore, registration of the filesystem type sets the singleton superblock's refcnt
	 * to `1', and unregistering the filesystem  type decrements the superblock's refcnt  like
	 * normal.
	 *
	 * When mounting a singleton superblock, you'll have to tryincref() the singleton pointer,
	 * and  if that fails, you may assume that the driver is currently being unloaded, and act
	 * like the requested type didn't exist.
	 *
	 * XXX: The  above is technically  the correct way of  doing this, but  it leaves a problem
	 *      when there are other statically allocated structures that reference the superblock,
	 *      which is the case for all of the static files from procfs.
	 * Technically, each of those files would also need to be holding its own reference to the
	 * superblock,  though only do so for as long  as outside references exist to those parts.
	 * Once  such references no longer exist, the static object must be considered as invalid.
	 * As such,  constructing  the  initial  reference to  static  objects  would  work  like:
	 * >> for (;;) {
	 * >>     if (tryincref(obj))
	 * >>         return obj;
	 * >>     static_init_lock_acquire();
	 * >>     if (obj->refcnt == 0) {
	 * >>         REINITIALIZE(obj);
	 * >>         incref(superblock);
	 * >>         obj->refcnt = 1;
	 * >>         static_init_lock_release();
	 * >>         return obj;
	 * >>     }
	 * >>     static_init_lock_release();
	 * >> }
	 *
	 */

	/* TODO: According  to  this:  https://sourceware.org/bugzilla/show_bug.cgi?id=18228
	 * The combination of O_PATH|O_NOFOLLOW can be used to directly open flnknode nodes,
	 * similar to the (now abandoned  and now longer available) KOS-specific  O_SYMLINK. */

	/* TODO: As per `man 2 open', O_PATH is also allowed to return regular files (in the
	 *       case of KOS, that would be the raw `struct mfile' objects). Currently,  our
	 *       implementation restricts O_PATH to only work for directories. */

	/* TODO: Update the toolchain gcc to the latest version.
	 *       Afterwards, add `__attribute__((access(...)))' support to magic:
	 * >> void foo([[in]] char const *buf);                       --> __attribute__((access(read_only, 1), nonnull(1))) void foo(char const *buf);
	 * >> void foo([[out]] char *buf);                            --> __attribute__((access(write_only, 1), nonnull(1))) void foo(char *buf);
	 * >> void foo([[inout]] char *buf);                          --> __attribute__((access(read_write, 1), nonnull(1))) void foo(char *buf);
	 * >> void foo([[in_opt]] char const *buf);                   --> __attribute__((access(read_only, 1))) void foo(char const *buf);
	 * >> void foo([[out_opt]] char *buf);                        --> __attribute__((access(write_only, 1))) void foo(char *buf);
	 * >> void foo([[inout_opt]] char *buf);                      --> __attribute__((access(read_write, 1))) void foo(char *buf);
	 * >> void foo([[in(count)]] void const *buf, size_t count);  --> __attribute__((access(read_only, 1, 2))) void foo(void const *buf, size_t count);
	 * >> void foo([[out(count)]] void *buf, size_t count);       --> __attribute__((access(write_only, 1, 2))) void foo(void *buf, size_t count);
	 * >> void foo([[inout(count)]] void *buf, size_t count);     --> __attribute__((access(read_write, 1, 2))) void foo(void *buf, size_t count);
	 */

	/* TODO: Enable `-Wpadded' (warns about implicit padding in structures; on KOS,
	 *       structs should be  declared with hidden  padding made visible  through
	 *       explicitly declared fields) */

	/* TODO: When a thread changes CPUs, it must call `userexcept_sysret_inject_self()'
	 *       s.a. explaination in `userexcept_sysret_inject_safe()' */

	/* TODO: Add futex support to pthread_once() (via an alternate [[userimpl]]) */

	/* TODO: Add support for preadv2(2) and pwritev2(2)
	 * XXX:  On  that note, maybe also get rid of preadvf(2) / pwritevf(2),
	 *       since  these  2  system  calls  kind-of  do  the  same  thing?
	 *       If so, also  consider getting rid  of preadf() and  pwritef(),
	 *       as well as  readf(2) and writef(2).  Additionally, maybe  also
	 *       change ioctlf() to use the RWF_* flags, rather than `iomode_t'
	 * Also: When offset=(pos_t)-1 should behave like read(2) / write(2) */

	/* TODO: Calls to `initscr(3)' (from libncurses) after `unset TERM' crash:
	 * $ unset TERM
	 * $ /usr/bin/rain
	 * Coredump /usr/bin/rain tid:15
	 * assert.expr: "abort()"
	 * assert.file: "kos/src/libc/libc/../../libdlmalloc/dlmalloc.c"
	 * assert.line: 4785
	 * assert.func: "dlfree"
	 * kos/src/libdlmalloc/dlmalloc.c(4723,17) : 0E061D51+4[/lib/libc.so][dlfree+1937] [orig_ustate]
	 * > trace
	 * kos/src/libdlmalloc/dlmalloc.c(4759,15) : 0E061D4C+5[/lib/libc.so][dlfree+1932]
	 * binutils/src/libncurses-6.1/ncurses/tinfo/free_ttype.c(55,5) : 0E0315D2+5[/lib/libncursesw.so.6][really_free_termtype+78]
	 * binutils/src/libncurses-6.1/ncurses/tinfo/free_ttype.c(74,5) : 0E031659+5[/lib/libncursesw.so.6][_nc_free_termtype+24]
	 * binutils/src/libncurses-6.1/ncurses/tinfo/lib_cur_term.c(150,2) : 0E0321EB+5[/lib/libncursesw.so.6][del_curterm_sp+49]
	 * binutils/src/libncurses-6.1/ncurses/tinfo/lib_cur_term.c(182,10) : 0E03226C+5[/lib/libncursesw.so.6][del_curterm+34]
	 * binutils/src/libncurses-6.1/ncurses/tinfo/lib_setup.c(812,6) : 0E0349D9+5[/lib/libncursesw.so.6][_nc_setupterm+1186]
	 * binutils/src/libncurses-6.1/ncurses/base/lib_newterm.c(200,5) : 0E01B1DD+5[/lib/libncursesw.so.6][newterm_sp+149]
	 * binutils/src/libncurses-6.1/ncurses/base/lib_newterm.c(355,10) : 0E01B616+5[/lib/libncursesw.so.6][newterm+71]
	 * binutils/src/libncurses-6.1/ncurses/base/lib_initscr.c(89,6) : 0E016C8E+5[/lib/libncursesw.so.6][initscr+119]
	 * binutils/i386-kos/opt/bsdgames/rain/rain.c(100,2) : 080487A6+5[/usr/bin/rain][main+182]
	 */

	return state;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_BOOT_BOOT_C */
