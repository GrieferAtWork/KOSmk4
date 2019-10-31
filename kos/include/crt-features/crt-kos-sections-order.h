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


/* NOTE: Section ordering follows special matching order rules, in that 2 rules...
 *       .text.*
 *       .text.my_part.*
 *       ... are handled properly in that `.text.my_part.*' is applied to all known
 *       sections before `.text.*' is then applied to all unmatched, remaining sections.
 *       The order used is that rules are applied in order of longest --> shortest.
 */

/*[[[order

# The ordering should be repeated for every section starting with one of these prefixes
# Repeats are performed after the initial section match, at which point all unmatched
# sections will be re-applied to previously given rules after being stripped of their
# prefix, before later being added to the back of the previous sections list
# Rules that appear on the same line are interchangeable/interleaved
	@REPEAT    .wchar*
	@REPEAT    .dos*
	@REPEAT    .dos.wchar*
	@REPEAT    .except*


# Core-application components
	.application.exit* .errno_access* # Keep exit-functions and errno together (both are likely to be used)
	.application*                     # Other application components

# Process sub-system
	.fs.exec.exec*  .sched.access*    # Keep fork() and exec() functions together
	.sched.thread*
	.sched.pthread*
	.sched.futex* .sched.futexlock* .sched.futexexpr* .sched.futexlockexpr*
	.sched.semaphore*
	.sched.param*
	.sched.process*
	.sched.signal*
	.sched.utility*
	.sched.user*
	.sched*

# Time sub-system
	.time*

# Heap sub-system
	.heap.mman*                       # Keep mmap() and malloc() close together
	.heap.malloc*
	.heap.helpers*
	.heap.strdup*
	.heap.rare_helpers*
	.heap.utility*
	.heap*

# File sub-system
	.io.read* .io.large.read*  \
	.io.write* .io.large.write*       # Keep basic read/write functions intermingled
	.io.access*                       # I/O accessor functions (open(), close(), etc.)
	.FILE.core.read*
	.FILE.core.write*
	.FILE.core.utility*
	.FILE.core*
	.FILE.locked.access*
	.FILE.locked.read.read*
	.FILE.locked.read.scanf*
	.FILE.locked.read*
	.FILE.locked.write.write*
	.FILE.locked.write.printf*
	.FILE.locked.write*
	.FILE.locked.seek*
	.FILE.locked*
	.FILE.unlocked.access*
	.FILE.unlocked.read.read*
	.FILE.unlocked.read.scanf*
	.FILE.unlocked.read*
	.FILE.unlocked.write.write*
	.FILE.unlocked.write.printf*
	.FILE.unlocked.write*
	.FILE.unlocked.seek*
	.FILE.unlocked*
	.FILE.utility*
	.io*                              # All other I/O operations
	.fs.basic_property* .fs.property* # Basic filesystem operations
	.fs.environ*                      # Environment variables
	.fs.exec*                         # Exec functions
	.fs.modify*                       # Filesystem modifications
	.fs.dir*                          # Directory functions
	.fs.stat*                         # Stat functions
	.fs.utility* .fs*                 # Misc. utility

# String functions
	.string.memory* .string*          # Memory functions

# Character information
	.unicode.UTF*
	.unicode.static.memory*
	.unicode.static.ctype*
	.unicode.static.convert*
	.unicode.static.format.printf* .string.format*   # Keep string format helpers together with format_printf()
	.unicode.static.format.scanf*
	.unicode.static.format.strftime*
	.unicode.locale.memory*
	.unicode.locale.ctype*
	.unicode.locale.convert*
	.unicode.locale.format.printf*
	.unicode.locale.format.scanf*
	.unicode.locale.format.strftime*
	.unicode.static.mbs*
	.unicode.locale.mbs*
	.unicode*

# Networking
	.net.socket*
	.net.inet*
	.net.ether*
	.net.rpc*
	.net.db*
	.net.interface*
	.net*

# Misc sub-systems

	.application.options*             # getopt()
	.io.tty*                          # tty / pty
	.random*                          # rand()
	.math*                            # math-functions
	.fs.swap* .fs.mount* .fs.modify_time* \
	                                  # Rarely used filesystem functions
	.fs.statfs*                       # Rarely used filesystem stat functions
	.timer*                           # Timer functions

	# strerror(), etc...
	.errno*

	# Databases
	.database.shell*
	.database.group*
	.database.shadow*
	.database.pwd*
	.database.aliases*
	.database.mntent*
	.database.utmp*
	.database.utmpx*
	.database*

	.io.stropts*                      # stream operations
	.io.sgtty*                        # gtty / stty
	.obstack*                         # obstack
	.utility*                         # Misc. utility functions
	.system*                          # Misc. system functions
	.fs*                              # All other filesystem functions
	.sched.resource*                  # Resource limit functions
	.sched.msg*                       # <sys/msg.h>
	.string.encrypt*                  # String encryption
	.string.match*                    # String matching functions
	.unsorted*                        # Everything else...

]]]*/
#define __CRT_LINKORDER_SECTIONS(CB, PREFIX) \
	CB(PREFIX.errno_access.* PREFIX.application.exit.*) \
	CB(PREFIX.sched.access.* PREFIX.fs.exec.exec.*) \
	CB(PREFIX.sched.thread.*) \
	CB(PREFIX.sched.pthread.*) \
	CB(PREFIX.sched.futex.* PREFIX.sched.futexexpr.* PREFIX.sched.futexlock.* PREFIX.sched.futexlockexpr.*) \
	CB(PREFIX.sched.semaphore.*) \
	CB(PREFIX.sched.param.*) \
	CB(PREFIX.sched.process.*) \
	CB(PREFIX.sched.signalfd.* PREFIX.sched.signal.*) \
	CB(PREFIX.sched.utility.*) \
	CB(PREFIX.sched.user.*) \
	CB(PREFIX.sched.eventfd.*) \
	CB(PREFIX.time.*) \
	CB(PREFIX.heap.mman.*) \
	CB(PREFIX.heap.malloc.*) \
	CB(PREFIX.heap.helpers.*) \
	CB(PREFIX.heap.strdup.*) \
	CB(PREFIX.heap.rare_helpers.*) \
	CB(PREFIX.heap.utility.*) \
	CB(PREFIX.io.large.read.* PREFIX.io.large.write.* PREFIX.io.read.* PREFIX.io.write.*) \
	CB(PREFIX.io.access.*) \
	CB(PREFIX.FILE.core.read.*) \
	CB(PREFIX.FILE.core.write.*) \
	CB(PREFIX.FILE.core.utility.*) \
	CB(PREFIX.FILE.core.seek.*) \
	CB(PREFIX.FILE.locked.access.*) \
	CB(PREFIX.FILE.locked.read.read.*) \
	CB(PREFIX.FILE.locked.read.scanf.*) \
	CB(PREFIX.FILE.locked.read.utility.* PREFIX.FILE.locked.read.getc.*) \
	CB(PREFIX.FILE.locked.write.write.*) \
	CB(PREFIX.FILE.locked.write.printf.*) \
	CB(PREFIX.FILE.locked.write.utility.* PREFIX.FILE.locked.write.putc.*) \
	CB(PREFIX.FILE.locked.seek.pos.* PREFIX.FILE.locked.seek.seek.* PREFIX.FILE.locked.seek.utility.*) \
	CB(PREFIX.FILE.locked.utility.*) \
	CB(PREFIX.FILE.unlocked.access.*) \
	CB(PREFIX.FILE.unlocked.read.read.*) \
	CB(PREFIX.FILE.unlocked.read.scanf.*) \
	CB(PREFIX.FILE.unlocked.read.utility.* PREFIX.FILE.unlocked.read.getc.*) \
	CB(PREFIX.FILE.unlocked.write.write.*) \
	CB(PREFIX.FILE.unlocked.write.printf.*) \
	CB(PREFIX.FILE.unlocked.write.utility.* PREFIX.FILE.unlocked.write.putc.*) \
	CB(PREFIX.FILE.unlocked.seek.pos.* PREFIX.FILE.unlocked.seek.seek.* PREFIX.FILE.unlocked.seek.utility.*) \
	CB(PREFIX.FILE.unlocked.utility.*) \
	CB(PREFIX.FILE.utility.ext.*) \
	CB(PREFIX.io.large.lock.* PREFIX.io.large.seek.* PREFIX.io.large.utility.* PREFIX.io.lock.* PREFIX.io.poll.* PREFIX.io.seek.* PREFIX.io.sync.* PREFIX.io.utility.*) \
	CB(PREFIX.fs.property.* PREFIX.fs.basic_property.*) \
	CB(PREFIX.fs.environ.*) \
	CB(PREFIX.fs.exec.posix_spawn.* PREFIX.fs.exec.spawn.* PREFIX.fs.exec.system.*) \
	CB(PREFIX.fs.modify.*) \
	CB(PREFIX.fs.dir.*) \
	CB(PREFIX.fs.stat_glc.* PREFIX.fs.stat.*) \
	CB(PREFIX.fs.utility.*) \
	CB(PREFIX.string.memory.*) \
	CB(PREFIX.unicode.UTF.*) \
	CB(PREFIX.unicode.static.memory.*) \
	CB(PREFIX.unicode.static.ctype.*) \
	CB(PREFIX.unicode.static.convert.*) \
	CB(PREFIX.unicode.static.format.printf.* PREFIX.string.format.*) \
	CB(PREFIX.unicode.static.format.scanf.*) \
	CB(PREFIX.unicode.locale.memory.*) \
	CB(PREFIX.unicode.locale.ctype.*) \
	CB(PREFIX.unicode.locale.convert.*) \
	CB(PREFIX.unicode.mbr.*) \
	CB(PREFIX.net.socket.*) \
	CB(PREFIX.net.inet.*) \
	CB(PREFIX.net.ether.*) \
	CB(PREFIX.net.rpc.*) \
	CB(PREFIX.net.db.*) \
	CB(PREFIX.net.interface.*) \
	CB(PREFIX.net.convert.*) \
	CB(PREFIX.application.options.*) \
	CB(PREFIX.io.tty.*) \
	CB(PREFIX.random.*) \
	CB(PREFIX.math.fenv.* PREFIX.math.float.* PREFIX.math.math.* PREFIX.math.utility.*) \
	CB(PREFIX.fs.modify_time.* PREFIX.fs.mount.* PREFIX.fs.swap.*) \
	CB(PREFIX.fs.statfs.statvfs.* PREFIX.fs.statfs.statfs.*) \
	CB(PREFIX.timer.*) \
	CB(PREFIX.errno.*) \
	CB(PREFIX.database.shell.*) \
	CB(PREFIX.database.group.*) \
	CB(PREFIX.database.shadow.*) \
	CB(PREFIX.database.pwd.*) \
	CB(PREFIX.database.aliases.*) \
	CB(PREFIX.database.mntent.*) \
	CB(PREFIX.database.utmp.*) \
	CB(PREFIX.database.utmpx.*) \
	CB(PREFIX.io.stropts.*) \
	CB(PREFIX.obstack.*) \
	CB(PREFIX.utility.glob.* PREFIX.utility.klog.* PREFIX.utility.regex.* PREFIX.utility.search.* PREFIX.utility.shm.* PREFIX.utility.stdlib.*) \
	CB(PREFIX.system.*) \
	CB(PREFIX.sched.resource.*) \
	CB(PREFIX.sched.msg.*) \
	CB(PREFIX.string.encrypt.*) \
	CB(PREFIX.string.match.*) \
	CB(PREFIX.unsorted.*) \
	CB(PREFIX.wchar.fs.exec.exec.*) \
	CB(PREFIX.wchar.heap.strdup.*) \
	CB(PREFIX.wchar.FILE.locked.access.*) \
	CB(PREFIX.wchar.FILE.locked.read.read.*) \
	CB(PREFIX.wchar.FILE.locked.read.scanf.*) \
	CB(PREFIX.wchar.FILE.locked.read.getc.*) \
	CB(PREFIX.wchar.FILE.locked.write.write.*) \
	CB(PREFIX.wchar.FILE.locked.write.printf.*) \
	CB(PREFIX.wchar.FILE.locked.write.putc.*) \
	CB(PREFIX.wchar.FILE.locked.utility.*) \
	CB(PREFIX.wchar.FILE.unlocked.read.read.*) \
	CB(PREFIX.wchar.FILE.unlocked.read.scanf.*) \
	CB(PREFIX.wchar.FILE.unlocked.read.getc.*) \
	CB(PREFIX.wchar.FILE.unlocked.write.write.*) \
	CB(PREFIX.wchar.FILE.unlocked.write.printf.*) \
	CB(PREFIX.wchar.FILE.unlocked.write.putc.*) \
	CB(PREFIX.wchar.fs.exec.system.* PREFIX.wchar.fs.exec.spawn.*) \
	CB(PREFIX.wchar.string.memory.*) \
	CB(PREFIX.wchar.unicode.static.memory.*) \
	CB(PREFIX.wchar.unicode.static.ctype.*) \
	CB(PREFIX.wchar.unicode.static.convert.*) \
	CB(PREFIX.wchar.unicode.static.format.printf.* PREFIX.wchar.string.format.*) \
	CB(PREFIX.wchar.unicode.static.format.scanf.*) \
	CB(PREFIX.wchar.unicode.static.format.strftime.*) \
	CB(PREFIX.wchar.unicode.locale.memory.*) \
	CB(PREFIX.wchar.unicode.locale.ctype.*) \
	CB(PREFIX.wchar.unicode.locale.convert.*) \
	CB(PREFIX.wchar.unicode.locale.format.strftime.*) \
	CB(PREFIX.wchar.unicode.static.mbs.*) \
	CB(PREFIX.wchar.unicode.locale.mbs.*) \
	CB(PREFIX.wchar.unicode.convert.*) \
	CB(PREFIX.wchar.fs.modify_time.*) \
	CB(PREFIX.dos.application.init.*) \
	CB(PREFIX.dos.sched.thread.*) \
	CB(PREFIX.dos.sched.signal.*) \
	CB(PREFIX.dos.heap.debug_malloc.* PREFIX.dos.heap.*) \
	CB(PREFIX.dos.FILE.locked.access.*) \
	CB(PREFIX.dos.FILE.locked.read.read.*) \
	CB(PREFIX.dos.FILE.locked.read.scanf.*) \
	CB(PREFIX.dos.FILE.locked.write.write.*) \
	CB(PREFIX.dos.FILE.locked.write.utility.*) \
	CB(PREFIX.dos.FILE.locked.utility.*) \
	CB(PREFIX.dos.FILE.unlocked.read.read.*) \
	CB(PREFIX.dos.FILE.utility.*) \
	CB(PREFIX.dos.fs.property.*) \
	CB(PREFIX.dos.fs.environ.*) \
	CB(PREFIX.dos.fs.exec.spawn.*) \
	CB(PREFIX.dos.fs.modify.*) \
	CB(PREFIX.dos.fs.utility.* PREFIX.dos.fs.dlfcn.*) \
	CB(PREFIX.dos.string.memory.*) \
	CB(PREFIX.dos.unicode.static.memory.*) \
	CB(PREFIX.dos.unicode.static.convert.*) \
	CB(PREFIX.dos.unicode.static.format.printf.*) \
	CB(PREFIX.dos.unicode.static.format.scanf.*) \
	CB(PREFIX.dos.unicode.locale.memory.*) \
	CB(PREFIX.dos.unicode.locale.convert.*) \
	CB(PREFIX.dos.unicode.locale.format.printf.*) \
	CB(PREFIX.dos.unicode.locale.format.scanf.*) \
	CB(PREFIX.dos.random.*) \
	CB(PREFIX.dos.math.utility.*) \
	CB(PREFIX.dos.errno.*) \
	CB(PREFIX.dos.utility.*) \
	CB(PREFIX.dos.system.utility.* PREFIX.dos.system.*) \
	CB(PREFIX.dos.unsorted.*) \
	CB(PREFIX.dos.wchar.fs.exec.exec.*) \
	CB(PREFIX.dos.wchar.heap.strdup.*) \
	CB(PREFIX.dos.wchar.FILE.locked.access.*) \
	CB(PREFIX.dos.wchar.FILE.locked.read.read.*) \
	CB(PREFIX.dos.wchar.FILE.locked.read.scanf.*) \
	CB(PREFIX.dos.wchar.FILE.locked.read.getc.*) \
	CB(PREFIX.dos.wchar.FILE.locked.write.write.*) \
	CB(PREFIX.dos.wchar.FILE.locked.write.printf.*) \
	CB(PREFIX.dos.wchar.FILE.locked.write.putc.*) \
	CB(PREFIX.dos.wchar.FILE.unlocked.read.read.*) \
	CB(PREFIX.dos.wchar.FILE.unlocked.read.scanf.*) \
	CB(PREFIX.dos.wchar.FILE.unlocked.read.getc.*) \
	CB(PREFIX.dos.wchar.FILE.unlocked.write.write.*) \
	CB(PREFIX.dos.wchar.FILE.unlocked.write.printf.*) \
	CB(PREFIX.dos.wchar.FILE.unlocked.write.putc.*) \
	CB(PREFIX.dos.wchar.fs.exec.system.* PREFIX.dos.wchar.fs.exec.spawn.*) \
	CB(PREFIX.dos.wchar.fs.stat.*) \
	CB(PREFIX.dos.wchar.string.memory.*) \
	CB(PREFIX.dos.wchar.unicode.static.memory.*) \
	CB(PREFIX.dos.wchar.unicode.static.convert.*) \
	CB(PREFIX.dos.wchar.unicode.static.format.printf.* PREFIX.dos.wchar.string.format.*) \
	CB(PREFIX.dos.wchar.unicode.static.format.scanf.*) \
	CB(PREFIX.dos.wchar.unicode.static.format.strftime.*) \
	CB(PREFIX.dos.wchar.unicode.locale.memory.*) \
	CB(PREFIX.dos.wchar.unicode.locale.convert.*) \
	CB(PREFIX.dos.wchar.unicode.locale.format.strftime.*) \
	CB(PREFIX.dos.wchar.unicode.static.mbs.*) \
	CB(PREFIX.dos.wchar.unicode.convert.*) \
	CB(PREFIX.dos.wchar.fs.modify_time.*) \
	CB(PREFIX.dos.wchar.errno.*) \
	CB(PREFIX.except.sched.access.* PREFIX.except.fs.exec.exec.*) \
	CB(PREFIX.except.sched.param.*) \
	CB(PREFIX.except.sched.process.*) \
	CB(PREFIX.except.sched.user.*) \
	CB(PREFIX.except.heap.malloc.*) \
	CB(PREFIX.except.heap.rare_helpers.*) \
	CB(PREFIX.except.io.large.read.* PREFIX.except.io.large.write.* PREFIX.except.io.read.* PREFIX.except.io.write.*) \
	CB(PREFIX.except.io.access.*) \
	CB(PREFIX.except.io.large.seek.* PREFIX.except.io.seek.* PREFIX.except.io.sync.* PREFIX.except.io.utility.*) \
	CB(PREFIX.except.fs.property.* PREFIX.except.fs.basic_property.*) \
	CB(PREFIX.except.fs.modify.*) \
	CB(PREFIX.except.fs.stat.*) \
	CB(PREFIX.except.fs.utility.*) \
	CB(PREFIX.except.fs.modify_time.*) \
	CB(PREFIX.except.system.utility.* PREFIX.except.system.configuration.*) \
/**/
//[[[end]]]



