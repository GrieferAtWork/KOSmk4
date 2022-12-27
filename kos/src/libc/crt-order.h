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


/* NOTE: Section ordering follows special matching order rules, in that 2 rules...
 *       .text.*
 *       .text.my_part.*
 *       ... are handled  properly in  that `.text.my_part.*'  is applied  to all  known
 *       sections before `.text.*' is then applied to all unmatched, remaining sections.
 *       The order used is that rules are applied in order of longest --> shortest.
 */

/* TODO: Now that generate_headers.dee literally scans source files for
 *       mentions of section names, there is no longer a need to  limit
 *       ourselves to the .text, .rodata, .data and .bss prefixes.
 * Instead, generate_headers.dee could keep track of full section names
 * and we could have 4 distinct order macros be generated, one for each
 * of the traditional base sections. */


/*[[[order

# The ordering should be repeated for every section starting with one of these prefixes
# Repeats are performed after the initial section match, at which point all unmatched
# sections will be re-applied to previously given rules after being stripped of their
# prefix, before later being added to the back of the previous sections list
# Rules that appear on the same line are interchangeable/interleaved
	@REPEAT    .crt
	@REPEAT    .crt.wchar
	@REPEAT    .crt.except
	@REPEAT    .crt.dos
	@REPEAT    .crt.dos.wchar
	@REPEAT    .crt.dos.except


# Core-application components
	.application.init
	.errno_access.core                # Keep core errno access functions together
	.errno_access
	.application.exit                 # Keep exit-functions and errno together (both are likely to be used)
	.application.* .application       # Other application components

# Process sub-system
	.fs.exec.exec  .sched.access      # Keep fork() and exec() functions together
	.sched.thread
	.sched.pthread
	.sched.futex .sched.futexlock .sched.futexexpr .sched.futexlockexpr
	.sched.semaphore
	.sched.lockop
	.sched.param
	.sched.process
	.sched.signal
	.sched.utility
	.sched.user
	.sched.wait
	.sched.*  .sched

# Time sub-system
	.time
	.time.timezone

# Heap sub-system
	.heap.mman                        # Keep mmap() and malloc() close together
	.heap.malloc
	.heap.helpers
	.heap.strdup
	.heap.rare_helpers
	.heap.utility
	.heap.obstack
	.heap.*
	.heap

# File sub-system
	.io.read .io.large.read .io.write .io.large.write   # Keep basic read/write functions intermingled
	.io.access                                          # I/O accessor functions (open(), close(), etc.)
	.FILE.core.read
	.FILE.core.write
	.FILE.core.seek
	.FILE.core.utility
	.FILE.core
	.FILE.std_files
	.FILE.locked.access
	.FILE.locked.read.read
	.FILE.locked.read.scanf
	.FILE.locked.read.* .FILE.locked.read
	.FILE.locked.write.write
	.FILE.locked.write.printf
	.FILE.locked.write.* .FILE.locked.write
	.FILE.locked.seek.* .FILE.locked.seek
	.FILE.locked.utility
	.FILE.locked
	.FILE.unlocked.access
	.FILE.unlocked.read.read
	.FILE.unlocked.read.scanf
	.FILE.unlocked.read.* .FILE.unlocked.read
	.FILE.unlocked.write.write
	.FILE.unlocked.write.printf
	.FILE.unlocked.write.* .FILE.unlocked.write
	.FILE.unlocked.seek.* .FILE.unlocked.seek
	.FILE.unlocked.utility
	.FILE.unlocked
	.FILE.utility
	.FILE.utility.memopen
	.FILE.utility.memstream
	.FILE.utility.ext
	.FILE.utility.popen

	.io.* .io                       # All other I/O operations
	.fs.basic_property .fs.property # Basic filesystem operations
	.fs.environ                     # Environment variables
	.fs.exec                        # Exec functions
	.fs.modify                      # Filesystem modifications
	.fs.dir                         # Directory functions
	.fs.stat                        # Stat functions
	.fs.utility .fs                 # Misc. utility

# String functions
	.string.memory .string          # Memory functions

# Character information
	.unicode.UTF
	.unicode.static.memory
	.unicode.static.ctype
	.unicode.static.convert
	.unicode.static.format.printf .string.format   # Keep string format helpers together with format_printf()
	.unicode.static.format.scanf
	.unicode.static.format.strftime
	.unicode.locale.memory
	.unicode.locale.ctype
	.unicode.locale.convert
	.unicode.locale.format.printf
	.unicode.locale.format.scanf
	.unicode.locale.format.strftime
	.unicode.static.mbs
	.unicode.locale.mbs
	.unicode.* .unicode

# Exception sub-system
	.except

# Networking
	.net.socket
	.net.inet
	.net.ether
	.net.rpc
	.net.db
	.net.interface
	.net.* .net

# Misc sub-systems

	.application.options               # getopt()
	.io.tty                            # tty / pty
	.random.* .random                  # rand()
	.math.*  .math                     # math-functions
	.fs.swap .fs.mount .fs.modify_time # Rarely used filesystem functions
	.fs.statfs                         # Rarely used filesystem stat functions
	.timer                             # Timer functions

	# strerror(), etc...
	.errno.*   .errno
	.error.*   .error

	# System call wrappers
	.kos.syscalls
	.syscalls.*
	.syscalls

	# Databases
	.database.fstab
	.database.mntent
	.database.grp
	.database.pwd
	.database.shadow
	.database.utmp
	.database.utmpx
	.database.aliases
	.database.shell
	.database.tty

	.io.stropts                       # stream operations
	.io.sgtty                         # gtty / stty
	.string.memory.strsignal          # strsignal()
	.system.auxv                      # <sys/auxv.h>
	.utility.* .utility               # Misc. utility functions
	.i18n.* .i18n                     # <libintl.h>
	.system.* .system                 # Misc. system functions
	.debug                            # Misc. debug functions
	.assert                           # Assertion functions
	.ssp.* .ssp                       # Stack smash protection
	.fs.* .fs                         # All other filesystem functions
	.sched.resource                   # Resource limit functions
	.sched.msg                        # <sys/msg.h>
	.string.nopf                      # No page-fault functions
	.string.encrypt                   # String encryption
	.string.match                     # String matching functions
	.string.argz   .string.envz       # <argz.h> and <envz.h>
	.sched.pthread_ext                # Pthread extensions
	.system.configuration             # confstr(), sysconf(), etc...
	.system.random                    # <sys/random.h>
	.cpu.ucontext                     # <ucontext.h>
	.wordexp                          # <wordexp.h>
	.libattr                          # <attr/libattr.h>
	.glibc.* .glibc                   # Glibc-specific stuff
	.bsd.stringlist                   # BSD's <stringlist.h> header
	.bsd.* .bsd                       # Misc BSD functions
	.solaris.* .solaris               # Misc Solaris functions
	.mbstring.* .mbstring             # <mbstring.h>, <mbctype.h>
	.conio.* .conio                   # <conio.h>, `stdtty'
	.capability                       # <sys/capability.h>
	.libiberty                        # <libiberty.h>
	.unsorted                         # Everything else...

	# Compatibility stuff
	.compat.cyg.*    .compat.cyg
	.compat.dos.*    .compat.dos
	.compat.linux.*  .compat.linux
	.compat.glibc.*  .compat.glibc
]]]*/
#define CRT_SECTIONS_LINKORDER(CB, PREFIX) \
	CB(PREFIX.math.math) \
	CB(PREFIX.string.nopf) \
	CB(PREFIX.crt.application.init) \
	CB(PREFIX.crt.errno_access.core) \
	CB(PREFIX.crt.errno_access) \
	CB(PREFIX.crt.application.exit) \
	CB(PREFIX.crt.fs.exec.exec PREFIX.crt.sched.access) \
	CB(PREFIX.crt.sched.thread) \
	CB(PREFIX.crt.sched.pthread) \
	CB(PREFIX.crt.sched.futex PREFIX.crt.sched.futexlockexpr) \
	CB(PREFIX.crt.sched.semaphore) \
	CB(PREFIX.crt.sched.lockop) \
	CB(PREFIX.crt.sched.param) \
	CB(PREFIX.crt.sched.process) \
	CB(PREFIX.crt.sched.signal) \
	CB(PREFIX.crt.sched.utility) \
	CB(PREFIX.crt.sched.user) \
	CB(PREFIX.crt.sched.wait) \
	CB(PREFIX.crt.sched.eventfd PREFIX.crt.sched.rpc PREFIX.crt.sched.signalfd PREFIX.crt.sched.threads) \
	CB(PREFIX.crt.time) \
	CB(PREFIX.crt.time.timezone) \
	CB(PREFIX.crt.heap.mman) \
	CB(PREFIX.crt.heap.malloc) \
	CB(PREFIX.crt.heap.helpers) \
	CB(PREFIX.crt.heap.strdup) \
	CB(PREFIX.crt.heap.rare_helpers) \
	CB(PREFIX.crt.heap.utility) \
	CB(PREFIX.crt.heap.obstack) \
	CB(PREFIX.crt.io.read PREFIX.crt.io.large.read PREFIX.crt.io.write PREFIX.crt.io.large.write) \
	CB(PREFIX.crt.io.access) \
	CB(PREFIX.crt.FILE.core.read) \
	CB(PREFIX.crt.FILE.core.write) \
	CB(PREFIX.crt.FILE.core.seek) \
	CB(PREFIX.crt.FILE.core.utility) \
	CB(PREFIX.crt.FILE.std_files) \
	CB(PREFIX.crt.FILE.locked.access) \
	CB(PREFIX.crt.FILE.locked.read.read) \
	CB(PREFIX.crt.FILE.locked.read.scanf) \
	CB(PREFIX.crt.FILE.locked.read.getc PREFIX.crt.FILE.locked.read.utility) \
	CB(PREFIX.crt.FILE.locked.write.write) \
	CB(PREFIX.crt.FILE.locked.write.printf) \
	CB(PREFIX.crt.FILE.locked.write.putc PREFIX.crt.FILE.locked.write.utility) \
	CB(PREFIX.crt.FILE.locked.seek.pos PREFIX.crt.FILE.locked.seek.seek PREFIX.crt.FILE.locked.seek.utility) \
	CB(PREFIX.crt.FILE.locked.utility) \
	CB(PREFIX.crt.FILE.unlocked.access) \
	CB(PREFIX.crt.FILE.unlocked.read.read) \
	CB(PREFIX.crt.FILE.unlocked.read.scanf) \
	CB(PREFIX.crt.FILE.unlocked.read.getc PREFIX.crt.FILE.unlocked.read.utility) \
	CB(PREFIX.crt.FILE.unlocked.write.write) \
	CB(PREFIX.crt.FILE.unlocked.write.printf) \
	CB(PREFIX.crt.FILE.unlocked.write.putc PREFIX.crt.FILE.unlocked.write.utility) \
	CB(PREFIX.crt.FILE.unlocked.seek.pos PREFIX.crt.FILE.unlocked.seek.seek PREFIX.crt.FILE.unlocked.seek.utility) \
	CB(PREFIX.crt.FILE.unlocked.utility) \
	CB(PREFIX.crt.FILE.utility.ext) \
	CB(PREFIX.crt.FILE.utility.popen) \
	CB(PREFIX.crt.io.large.lock PREFIX.crt.io.large.seek PREFIX.crt.io.large.utility PREFIX.crt.io.lock PREFIX.crt.io.poll PREFIX.crt.io.seek PREFIX.crt.io.sync PREFIX.crt.io.utility) \
	CB(PREFIX.crt.fs.basic_property PREFIX.crt.fs.property) \
	CB(PREFIX.crt.fs.environ) \
	CB(PREFIX.crt.fs.modify) \
	CB(PREFIX.crt.fs.dir) \
	CB(PREFIX.crt.fs.stat) \
	CB(PREFIX.crt.fs.utility) \
	CB(PREFIX.crt.string.memory) \
	CB(PREFIX.crt.unicode.UTF) \
	CB(PREFIX.crt.unicode.static.memory) \
	CB(PREFIX.crt.unicode.static.ctype) \
	CB(PREFIX.crt.unicode.static.convert) \
	CB(PREFIX.crt.unicode.static.format.printf PREFIX.crt.string.format) \
	CB(PREFIX.crt.unicode.static.format.scanf) \
	CB(PREFIX.crt.unicode.locale.memory) \
	CB(PREFIX.crt.unicode.locale.ctype) \
	CB(PREFIX.crt.unicode.locale.convert) \
	CB(PREFIX.crt.except) \
	CB(PREFIX.crt.net.socket) \
	CB(PREFIX.crt.net.inet) \
	CB(PREFIX.crt.net.ether) \
	CB(PREFIX.crt.net.rpc) \
	CB(PREFIX.crt.net.db) \
	CB(PREFIX.crt.net.interface) \
	CB(PREFIX.crt.net.convert PREFIX.crt.net.inet.6 PREFIX.crt.net.inet.6.RFC_2292 PREFIX.crt.net.inet.6.RFC_3542 PREFIX.crt.net.inet.6.bind_reserved PREFIX.crt.net.inet.6.ipv4_source_filter PREFIX.crt.net.inet.6.source_filter PREFIX.crt.net.nameser) \
	CB(PREFIX.crt.application.options) \
	CB(PREFIX.crt.io.tty) \
	CB(PREFIX.crt.random.random PREFIX.crt.random.srandom PREFIX.crt.random) \
	CB(PREFIX.crt.math.complex PREFIX.crt.math.fenv PREFIX.crt.math.float PREFIX.crt.math.math PREFIX.crt.math.utility) \
	CB(PREFIX.crt.fs.swap PREFIX.crt.fs.mount PREFIX.crt.fs.modify_time) \
	CB(PREFIX.crt.timer) \
	CB(PREFIX.crt.errno.sys_siglist PREFIX.crt.errno.utility PREFIX.crt.errno) \
	CB(PREFIX.crt.error) \
	CB(PREFIX.crt.kos.syscalls) \
	CB(PREFIX.crt.syscalls.selector PREFIX.crt.syscalls.x86_sysenter_common) \
	CB(PREFIX.crt.syscalls) \
	CB(PREFIX.crt.database.fstab) \
	CB(PREFIX.crt.database.mntent) \
	CB(PREFIX.crt.database.grp) \
	CB(PREFIX.crt.database.pwd) \
	CB(PREFIX.crt.database.shadow) \
	CB(PREFIX.crt.database.utmp) \
	CB(PREFIX.crt.database.utmpx) \
	CB(PREFIX.crt.database.aliases) \
	CB(PREFIX.crt.database.shell) \
	CB(PREFIX.crt.database.tty) \
	CB(PREFIX.crt.io.stropts) \
	CB(PREFIX.crt.string.memory.strsignal) \
	CB(PREFIX.crt.system.auxv) \
	CB(PREFIX.crt.utility.aio PREFIX.crt.utility.glob PREFIX.crt.utility.klog PREFIX.crt.utility.locale PREFIX.crt.utility.monetary PREFIX.crt.utility.mqueue PREFIX.crt.utility.regex PREFIX.crt.utility.search PREFIX.crt.utility.setjmp PREFIX.crt.utility.shm PREFIX.crt.utility.stdlib PREFIX.crt.utility) \
	CB(PREFIX.crt.i18n) \
	CB(PREFIX.crt.system.adjtime PREFIX.crt.system.getauxval PREFIX.crt.system.info PREFIX.crt.system.ioperm PREFIX.crt.system.mman PREFIX.crt.system.ptrace PREFIX.crt.system.reboot PREFIX.crt.system.rtm PREFIX.crt.system.syslog PREFIX.crt.system.utility) \
	CB(PREFIX.crt.debug) \
	CB(PREFIX.crt.assert) \
	CB(PREFIX.crt.ssp.string.memory) \
	CB(PREFIX.crt.fs.environ.heap PREFIX.crt.fs.exec.posix_spawn PREFIX.crt.fs.exec.spawn PREFIX.crt.fs.exec.system PREFIX.crt.fs.fts PREFIX.crt.fs.ftw PREFIX.crt.fs.statfs.statfs PREFIX.crt.fs.statfs.statvfs) \
	CB(PREFIX.crt.sched.resource) \
	CB(PREFIX.crt.sched.msg) \
	CB(PREFIX.crt.string.nopf) \
	CB(PREFIX.crt.string.encrypt) \
	CB(PREFIX.crt.string.match) \
	CB(PREFIX.crt.string.argz PREFIX.crt.string.envz) \
	CB(PREFIX.crt.sched.pthread_ext) \
	CB(PREFIX.crt.system.configuration) \
	CB(PREFIX.crt.system.random) \
	CB(PREFIX.crt.cpu.ucontext) \
	CB(PREFIX.crt.wordexp) \
	CB(PREFIX.crt.libattr) \
	CB(PREFIX.crt.glibc.application.init PREFIX.crt.glibc.assert PREFIX.crt.glibc.fs.stat) \
	CB(PREFIX.crt.bsd.stringlist) \
	CB(PREFIX.crt.bsd.io.access PREFIX.crt.bsd.sched.signal PREFIX.crt.bsd.strstat PREFIX.crt.bsd.user PREFIX.crt.bsd) \
	CB(PREFIX.crt.solaris.io PREFIX.crt.solaris) \
	CB(PREFIX.crt.capability) \
	CB(PREFIX.crt.libiberty) \
	CB(PREFIX.crt.unsorted) \
	CB(PREFIX.crt.compat.dos.msabi64.msabi64_RRRR PREFIX.crt.compat.dos.msabi64.msabi64_RRRRR PREFIX.crt.compat.dos.msabi64.msabi64_RRRRRRn) \
	CB(PREFIX.crt.compat.linux.__register_frame PREFIX.crt.compat.linux.dirent PREFIX.crt.compat.linux.except PREFIX.crt.compat.linux.heap PREFIX.crt.compat.linux.init PREFIX.crt.compat.linux.misc PREFIX.crt.compat.linux.signal PREFIX.crt.compat.linux.stdio PREFIX.crt.compat.linux) \
	CB(PREFIX.crt.compat.glibc.printf PREFIX.crt.compat.glibc.regex PREFIX.crt.compat.glibc) \
	CB(PREFIX.crt.wchar.fs.exec.exec) \
	CB(PREFIX.crt.wchar.heap.strdup) \
	CB(PREFIX.crt.wchar.FILE.locked.access) \
	CB(PREFIX.crt.wchar.FILE.locked.read.read) \
	CB(PREFIX.crt.wchar.FILE.locked.read.scanf) \
	CB(PREFIX.crt.wchar.FILE.locked.read.getc) \
	CB(PREFIX.crt.wchar.FILE.locked.write.write) \
	CB(PREFIX.crt.wchar.FILE.locked.write.printf) \
	CB(PREFIX.crt.wchar.FILE.locked.write.putc) \
	CB(PREFIX.crt.wchar.FILE.locked.utility) \
	CB(PREFIX.crt.wchar.FILE.unlocked.read.read) \
	CB(PREFIX.crt.wchar.FILE.unlocked.read.scanf) \
	CB(PREFIX.crt.wchar.FILE.unlocked.read.getc) \
	CB(PREFIX.crt.wchar.FILE.unlocked.write.write) \
	CB(PREFIX.crt.wchar.FILE.unlocked.write.printf) \
	CB(PREFIX.crt.wchar.FILE.unlocked.write.putc) \
	CB(PREFIX.crt.wchar.io.utility) \
	CB(PREFIX.crt.wchar.fs.basic_property PREFIX.crt.wchar.fs.property) \
	CB(PREFIX.crt.wchar.fs.modify) \
	CB(PREFIX.crt.wchar.fs.utility) \
	CB(PREFIX.crt.wchar.string.memory) \
	CB(PREFIX.crt.wchar.unicode.static.memory) \
	CB(PREFIX.crt.wchar.unicode.static.ctype) \
	CB(PREFIX.crt.wchar.unicode.static.convert) \
	CB(PREFIX.crt.wchar.unicode.static.format.printf PREFIX.crt.wchar.string.format) \
	CB(PREFIX.crt.wchar.unicode.static.format.scanf) \
	CB(PREFIX.crt.wchar.unicode.static.format.strftime) \
	CB(PREFIX.crt.wchar.unicode.locale.memory) \
	CB(PREFIX.crt.wchar.unicode.locale.ctype) \
	CB(PREFIX.crt.wchar.unicode.locale.convert) \
	CB(PREFIX.crt.wchar.unicode.locale.format.strftime) \
	CB(PREFIX.crt.wchar.unicode.static.mbs) \
	CB(PREFIX.crt.wchar.unicode.locale.mbs) \
	CB(PREFIX.crt.wchar.unicode.convert) \
	CB(PREFIX.crt.wchar.io.tty) \
	CB(PREFIX.crt.wchar.fs.modify_time) \
	CB(PREFIX.crt.wchar.fs.exec.spawn PREFIX.crt.wchar.fs.exec.system) \
	CB(PREFIX.crt.wchar.system.configuration) \
	CB(PREFIX.crt.except.fs.exec.exec PREFIX.crt.except.sched.access) \
	CB(PREFIX.crt.except.sched.param) \
	CB(PREFIX.crt.except.sched.process) \
	CB(PREFIX.crt.except.sched.user) \
	CB(PREFIX.crt.except.heap.mman) \
	CB(PREFIX.crt.except.heap.malloc) \
	CB(PREFIX.crt.except.heap.rare_helpers) \
	CB(PREFIX.crt.except.io.read PREFIX.crt.except.io.large.read PREFIX.crt.except.io.write PREFIX.crt.except.io.large.write) \
	CB(PREFIX.crt.except.io.access) \
	CB(PREFIX.crt.except.io.large.seek PREFIX.crt.except.io.seek PREFIX.crt.except.io.sync PREFIX.crt.except.io.utility) \
	CB(PREFIX.crt.except.fs.basic_property PREFIX.crt.except.fs.property) \
	CB(PREFIX.crt.except.fs.modify) \
	CB(PREFIX.crt.except.fs.utility) \
	CB(PREFIX.crt.except.net.socket) \
	CB(PREFIX.crt.except.fs.modify_time) \
	CB(PREFIX.crt.except.system.mman PREFIX.crt.except.system.utility) \
	CB(PREFIX.crt.except.system.configuration) \
	CB(PREFIX.crt.dos.application.init) \
	CB(PREFIX.crt.dos.errno_access) \
	CB(PREFIX.crt.dos.application.exit) \
	CB(PREFIX.crt.dos.fs.exec.exec PREFIX.crt.dos.sched.access) \
	CB(PREFIX.crt.dos.sched.thread) \
	CB(PREFIX.crt.dos.sched.pthread) \
	CB(PREFIX.crt.dos.sched.semaphore) \
	CB(PREFIX.crt.dos.sched.param) \
	CB(PREFIX.crt.dos.sched.process) \
	CB(PREFIX.crt.dos.sched.signal) \
	CB(PREFIX.crt.dos.sched.utility) \
	CB(PREFIX.crt.dos.sched.user) \
	CB(PREFIX.crt.dos.sched.wait) \
	CB(PREFIX.crt.dos.sched.eventfd PREFIX.crt.dos.sched.rpc PREFIX.crt.dos.sched.signalfd PREFIX.crt.dos.sched.threads) \
	CB(PREFIX.crt.dos.time) \
	CB(PREFIX.crt.dos.time.timezone) \
	CB(PREFIX.crt.dos.heap.mman) \
	CB(PREFIX.crt.dos.heap.malloc) \
	CB(PREFIX.crt.dos.heap.helpers) \
	CB(PREFIX.crt.dos.heap.strdup) \
	CB(PREFIX.crt.dos.heap.rare_helpers) \
	CB(PREFIX.crt.dos.heap.utility) \
	CB(PREFIX.crt.dos.heap.obstack) \
	CB(PREFIX.crt.dos.heap.debug_malloc) \
	CB(PREFIX.crt.dos.heap) \
	CB(PREFIX.crt.dos.io.read PREFIX.crt.dos.io.large.read PREFIX.crt.dos.io.write PREFIX.crt.dos.io.large.write) \
	CB(PREFIX.crt.dos.io.access) \
	CB(PREFIX.crt.dos.FILE.std_files) \
	CB(PREFIX.crt.dos.FILE.locked.access) \
	CB(PREFIX.crt.dos.FILE.locked.read.read) \
	CB(PREFIX.crt.dos.FILE.locked.read.scanf) \
	CB(PREFIX.crt.dos.FILE.locked.read.getc PREFIX.crt.dos.FILE.locked.read.utility) \
	CB(PREFIX.crt.dos.FILE.locked.write.write) \
	CB(PREFIX.crt.dos.FILE.locked.write.printf) \
	CB(PREFIX.crt.dos.FILE.locked.write.putc PREFIX.crt.dos.FILE.locked.write.utility) \
	CB(PREFIX.crt.dos.FILE.locked.seek.pos PREFIX.crt.dos.FILE.locked.seek.seek PREFIX.crt.dos.FILE.locked.seek.utility) \
	CB(PREFIX.crt.dos.FILE.locked.utility) \
	CB(PREFIX.crt.dos.FILE.unlocked.access) \
	CB(PREFIX.crt.dos.FILE.unlocked.read.read) \
	CB(PREFIX.crt.dos.FILE.unlocked.read.scanf) \
	CB(PREFIX.crt.dos.FILE.unlocked.read.getc PREFIX.crt.dos.FILE.unlocked.read.utility) \
	CB(PREFIX.crt.dos.FILE.unlocked.write.write) \
	CB(PREFIX.crt.dos.FILE.unlocked.write.printf) \
	CB(PREFIX.crt.dos.FILE.unlocked.write.putc PREFIX.crt.dos.FILE.unlocked.write.utility) \
	CB(PREFIX.crt.dos.FILE.unlocked.seek.pos PREFIX.crt.dos.FILE.unlocked.seek.seek PREFIX.crt.dos.FILE.unlocked.seek.utility) \
	CB(PREFIX.crt.dos.FILE.unlocked.utility) \
	CB(PREFIX.crt.dos.FILE.utility) \
	CB(PREFIX.crt.dos.FILE.utility.ext) \
	CB(PREFIX.crt.dos.FILE.utility.popen) \
	CB(PREFIX.crt.dos.io.large.lock PREFIX.crt.dos.io.large.seek PREFIX.crt.dos.io.large.utility PREFIX.crt.dos.io.lock PREFIX.crt.dos.io.poll PREFIX.crt.dos.io.seek PREFIX.crt.dos.io.sync PREFIX.crt.dos.io.utility) \
	CB(PREFIX.crt.dos.fs.basic_property PREFIX.crt.dos.fs.property) \
	CB(PREFIX.crt.dos.fs.environ) \
	CB(PREFIX.crt.dos.fs.modify) \
	CB(PREFIX.crt.dos.fs.dir) \
	CB(PREFIX.crt.dos.fs.stat) \
	CB(PREFIX.crt.dos.fs.utility) \
	CB(PREFIX.crt.dos.string.memory) \
	CB(PREFIX.crt.dos.unicode.UTF) \
	CB(PREFIX.crt.dos.unicode.static.memory) \
	CB(PREFIX.crt.dos.unicode.static.ctype) \
	CB(PREFIX.crt.dos.unicode.static.convert) \
	CB(PREFIX.crt.dos.unicode.static.format.printf PREFIX.crt.dos.string.format) \
	CB(PREFIX.crt.dos.unicode.static.format.scanf) \
	CB(PREFIX.crt.dos.unicode.locale.memory) \
	CB(PREFIX.crt.dos.unicode.locale.ctype) \
	CB(PREFIX.crt.dos.unicode.locale.convert) \
	CB(PREFIX.crt.dos.unicode.locale.format.printf) \
	CB(PREFIX.crt.dos.net.socket) \
	CB(PREFIX.crt.dos.net.inet) \
	CB(PREFIX.crt.dos.net.ether) \
	CB(PREFIX.crt.dos.net.rpc) \
	CB(PREFIX.crt.dos.net.db) \
	CB(PREFIX.crt.dos.net.interface) \
	CB(PREFIX.crt.dos.net.convert PREFIX.crt.dos.net.inet.6.RFC_2292 PREFIX.crt.dos.net.inet.6.RFC_3542 PREFIX.crt.dos.net.inet.6.bind_reserved PREFIX.crt.dos.net.inet.6.ipv4_source_filter PREFIX.crt.dos.net.inet.6.source_filter PREFIX.crt.dos.net.nameser) \
	CB(PREFIX.crt.dos.application.options) \
	CB(PREFIX.crt.dos.io.tty) \
	CB(PREFIX.crt.dos.random) \
	CB(PREFIX.crt.dos.math.complex PREFIX.crt.dos.math.fenv PREFIX.crt.dos.math.float PREFIX.crt.dos.math.math PREFIX.crt.dos.math.utility) \
	CB(PREFIX.crt.dos.fs.swap PREFIX.crt.dos.fs.mount PREFIX.crt.dos.fs.modify_time) \
	CB(PREFIX.crt.dos.timer) \
	CB(PREFIX.crt.dos.errno.utility PREFIX.crt.dos.errno) \
	CB(PREFIX.crt.dos.error) \
	CB(PREFIX.crt.dos.database.fstab) \
	CB(PREFIX.crt.dos.database.mntent) \
	CB(PREFIX.crt.dos.database.grp) \
	CB(PREFIX.crt.dos.database.pwd) \
	CB(PREFIX.crt.dos.database.shadow) \
	CB(PREFIX.crt.dos.database.utmp) \
	CB(PREFIX.crt.dos.database.utmpx) \
	CB(PREFIX.crt.dos.database.aliases) \
	CB(PREFIX.crt.dos.database.tty) \
	CB(PREFIX.crt.dos.io.stropts) \
	CB(PREFIX.crt.dos.string.memory.strsignal) \
	CB(PREFIX.crt.dos.system.auxv) \
	CB(PREFIX.crt.dos.utility.aio PREFIX.crt.dos.utility.klog PREFIX.crt.dos.utility.locale PREFIX.crt.dos.utility.monetary PREFIX.crt.dos.utility.mqueue PREFIX.crt.dos.utility.regex PREFIX.crt.dos.utility.search PREFIX.crt.dos.utility.shm PREFIX.crt.dos.utility.stdlib PREFIX.crt.dos.utility) \
	CB(PREFIX.crt.dos.i18n) \
	CB(PREFIX.crt.dos.system.adjtime PREFIX.crt.dos.system.info PREFIX.crt.dos.system.ioperm PREFIX.crt.dos.system.mman PREFIX.crt.dos.system.ptrace PREFIX.crt.dos.system.reboot PREFIX.crt.dos.system.syslog PREFIX.crt.dos.system.utility PREFIX.crt.dos.system) \
	CB(PREFIX.crt.dos.debug) \
	CB(PREFIX.crt.dos.assert) \
	CB(PREFIX.crt.dos.ssp.string.memory) \
	CB(PREFIX.crt.dos.fs.dlfcn PREFIX.crt.dos.fs.exec.posix_spawn PREFIX.crt.dos.fs.exec.spawn PREFIX.crt.dos.fs.exec.system PREFIX.crt.dos.fs.fts PREFIX.crt.dos.fs.io PREFIX.crt.dos.fs.statfs.statfs PREFIX.crt.dos.fs.statfs.statvfs) \
	CB(PREFIX.crt.dos.sched.resource) \
	CB(PREFIX.crt.dos.sched.msg) \
	CB(PREFIX.crt.dos.string.encrypt) \
	CB(PREFIX.crt.dos.string.match) \
	CB(PREFIX.crt.dos.string.argz PREFIX.crt.dos.string.envz) \
	CB(PREFIX.crt.dos.sched.pthread_ext) \
	CB(PREFIX.crt.dos.system.configuration) \
	CB(PREFIX.crt.dos.system.random) \
	CB(PREFIX.crt.dos.wordexp) \
	CB(PREFIX.crt.dos.libattr) \
	CB(PREFIX.crt.dos.bsd.stringlist) \
	CB(PREFIX.crt.dos.bsd.io.access PREFIX.crt.dos.bsd.strstat PREFIX.crt.dos.bsd.user PREFIX.crt.dos.bsd) \
	CB(PREFIX.crt.dos.solaris.io PREFIX.crt.dos.solaris) \
	CB(PREFIX.crt.dos.mbstring) \
	CB(PREFIX.crt.dos.conio) \
	CB(PREFIX.crt.dos.capability) \
	CB(PREFIX.crt.dos.libiberty) \
	CB(PREFIX.crt.dos.unsorted) \
	CB(PREFIX.crt.dos.compat.cyg.errno PREFIX.crt.dos.compat.cyg.fs.stat) \
	CB(PREFIX.crt.dos.compat.dos.errno PREFIX.crt.dos.compat.dos.except PREFIX.crt.dos.compat.dos.fs.stat PREFIX.crt.dos.compat.dos.msabi64 PREFIX.crt.dos.compat.dos) \
	CB(PREFIX.crt.dos.compat.glibc.regex) \
	CB(PREFIX.crt.dos.wchar.application.init) \
	CB(PREFIX.crt.dos.wchar.fs.exec.exec) \
	CB(PREFIX.crt.dos.wchar.time) \
	CB(PREFIX.crt.dos.wchar.heap.strdup) \
	CB(PREFIX.crt.dos.wchar.FILE.locked.access) \
	CB(PREFIX.crt.dos.wchar.FILE.locked.read.read) \
	CB(PREFIX.crt.dos.wchar.FILE.locked.read.scanf) \
	CB(PREFIX.crt.dos.wchar.FILE.locked.read.getc) \
	CB(PREFIX.crt.dos.wchar.FILE.locked.write.write) \
	CB(PREFIX.crt.dos.wchar.FILE.locked.write.printf) \
	CB(PREFIX.crt.dos.wchar.FILE.locked.write.putc) \
	CB(PREFIX.crt.dos.wchar.FILE.locked.utility) \
	CB(PREFIX.crt.dos.wchar.FILE.unlocked.read.read) \
	CB(PREFIX.crt.dos.wchar.FILE.unlocked.read.scanf) \
	CB(PREFIX.crt.dos.wchar.FILE.unlocked.read.getc) \
	CB(PREFIX.crt.dos.wchar.FILE.unlocked.write.write) \
	CB(PREFIX.crt.dos.wchar.FILE.unlocked.write.printf) \
	CB(PREFIX.crt.dos.wchar.FILE.unlocked.write.putc) \
	CB(PREFIX.crt.dos.wchar.io.utility) \
	CB(PREFIX.crt.dos.wchar.fs.basic_property PREFIX.crt.dos.wchar.fs.property) \
	CB(PREFIX.crt.dos.wchar.fs.environ) \
	CB(PREFIX.crt.dos.wchar.fs.modify) \
	CB(PREFIX.crt.dos.wchar.fs.stat) \
	CB(PREFIX.crt.dos.wchar.fs.utility) \
	CB(PREFIX.crt.dos.wchar.string.memory) \
	CB(PREFIX.crt.dos.wchar.unicode.static.memory) \
	CB(PREFIX.crt.dos.wchar.unicode.static.ctype) \
	CB(PREFIX.crt.dos.wchar.unicode.static.convert) \
	CB(PREFIX.crt.dos.wchar.unicode.static.format.printf PREFIX.crt.dos.wchar.string.format) \
	CB(PREFIX.crt.dos.wchar.unicode.static.format.scanf) \
	CB(PREFIX.crt.dos.wchar.unicode.static.format.strftime) \
	CB(PREFIX.crt.dos.wchar.unicode.locale.memory) \
	CB(PREFIX.crt.dos.wchar.unicode.locale.ctype) \
	CB(PREFIX.crt.dos.wchar.unicode.locale.convert) \
	CB(PREFIX.crt.dos.wchar.unicode.locale.format.printf) \
	CB(PREFIX.crt.dos.wchar.unicode.locale.format.strftime) \
	CB(PREFIX.crt.dos.wchar.unicode.static.mbs) \
	CB(PREFIX.crt.dos.wchar.unicode.locale.mbs) \
	CB(PREFIX.crt.dos.wchar.unicode.convert) \
	CB(PREFIX.crt.dos.wchar.io.tty) \
	CB(PREFIX.crt.dos.wchar.fs.modify_time) \
	CB(PREFIX.crt.dos.wchar.errno.utility PREFIX.crt.dos.wchar.errno) \
	CB(PREFIX.crt.dos.wchar.fs.exec.spawn PREFIX.crt.dos.wchar.fs.exec.system PREFIX.crt.dos.wchar.fs.io) \
	CB(PREFIX.crt.dos.wchar.system.configuration) \
	CB(PREFIX.crt.dos.wchar.conio)
/*[[[end]]]*/
