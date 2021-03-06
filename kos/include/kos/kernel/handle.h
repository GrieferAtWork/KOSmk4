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
#ifndef _KOS_KERNEL_HANDLE_H
#define _KOS_KERNEL_HANDLE_H 1

#include <__stdinc.h>

#ifndef __KOS__
#error "KOS-only system header"
#endif /* !__KOS__ */

/* Special values which may be used to refer to specific handles. */
#define HANDLE_SYMBOLIC_FDCWD         __CCAST(unsigned int)(-100) /* HANDLE_TYPE_PATH (writable) */
#define HANDLE_SYMBOLIC_FDROOT        __CCAST(unsigned int)(-101) /* HANDLE_TYPE_PATH (writable) */
#define HANDLE_SYMBOLIC_THISTASK      __CCAST(unsigned int)(-180) /* HANDLE_TYPE_TASK (readonly, Equivalent of `gettid()') */
#define HANDLE_SYMBOLIC_THISPROCESS   __CCAST(unsigned int)(-181) /* HANDLE_TYPE_TASK (writable, Equivalent of `getpid()') */
#define HANDLE_SYMBOLIC_PARENTPROCESS __CCAST(unsigned int)(-182) /* HANDLE_TYPE_TASK (writable, Equivalent of `getppid()') */
#define HANDLE_SYMBOLIC_GROUPLEADER   __CCAST(unsigned int)(-183) /* HANDLE_TYPE_TASK (writable, Equivalent of `getpgid(0)') */
#define HANDLE_SYMBOLIC_SESSIONLEADER __CCAST(unsigned int)(-184) /* HANDLE_TYPE_TASK (writable, Equivalent of `getsid(0)') */
#define HANDLE_SYMBOLIC_THISVM        HANDLE_SYMBOLIC_THISTASK
#define HANDLE_SYMBOLIC_THISFS        HANDLE_SYMBOLIC_THISTASK
#define HANDLE_SYMBOLIC_THISVFS       HANDLE_SYMBOLIC_THISTASK
#define HANDLE_SYMBOLIC_THISPIDNS     HANDLE_SYMBOLIC_THISTASK

/* Symbolic handles for DOS drives */
#define HANDLE_SYMBOLIC_DDRIVECWD(drivechar)  __CCAST(unsigned int)((-350)+((drivechar)-'A')) /* HANDLE_TYPE_PATH (writable) */
#define HANDLE_SYMBOLIC_DDRIVEROOT(drivechar) __CCAST(unsigned int)((-300)+((drivechar)-'A')) /* HANDLE_TYPE_PATH (writable) */
#define HANDLE_SYMBOLIC_DDRIVEMIN             'A' /* Min valid DDrive letter */
#define HANDLE_SYMBOLIC_DDRIVEMAX             'Z' /* Max valid DDrive letter */


/* KOS Handle type codes.
 * NOTE: Changes to this list must be updated with:
 * $ deemon -F kos/src/kernel/core/user/handle-router.c kos/src/kernel/include/kernel/handle-proto.h && touch kos/src/kernel/include/kernel/handle.h
 */
#define HANDLE_TYPE_UNDEFINED              0x0000 /* Undefined/unused handle */
#define HANDLE_TYPE_FILE                   0x0001 /* `struct file'
                                                   * Castable into: HANDLE_TYPE_PATH, HANDLE_TYPE_MFILE, HANDLE_TYPE_DIRECTORYENTRY */
#define HANDLE_TYPE_SOCKET                 0x0002 /* `struct socket' */
#define HANDLE_TYPE_EPOLL                  0x0003 /* `struct epoll_controller' */
#define HANDLE_TYPE_PIPE                   0x0004 /* `struct pipe' */
#define HANDLE_TYPE_PIPE_READER            0x0005 /* `struct pipe_reader' */
#define HANDLE_TYPE_PIPE_WRITER            0x0006 /* `struct pipe_writer' */
#define HANDLE_TYPE_FIFO_USER              0x0007 /* `struct fifo_user' */
#define HANDLE_TYPE_EVENTFD_FENCE          0x0008 /* `struct eventfd' (without `EFD_SEMAPHORE') */
#define HANDLE_TYPE_EVENTFD_SEMA           0x0009 /* `struct eventfd' (with `EFD_SEMAPHORE') */
#define HANDLE_TYPE_SIGNALFD               0x000a /* `struct signalfd' */
#define HANDLE_TYPE_UAIO                   0x000b /* `struct uaio_controller' */
#define HANDLE_TYPE_FUTEX                  0x000c /* `struct mfutex' */
#define HANDLE_TYPE_FUTEXFD                0x000d /* `struct mfutexfd' */
#define HANDLE_TYPE_ONESHOT_DIRECTORY_FILE 0x000e /* `struct oneshot_directory_file'
                                                   * Castable into: HANDLE_TYPE_PATH, HANDLE_TYPE_MFILE, HANDLE_TYPE_DIRECTORYENTRY */
#define HANDLE_TYPE_MFILE                  0x000f /* `struct mfile' (also includes `struct inode') */
#define HANDLE_TYPE_BLOCKDEVICE            0x0010 /* `struct basic_block_device' */
#define HANDLE_TYPE_DIRECTORYENTRY         0x0011 /* `struct directory_entry' */
#define HANDLE_TYPE_PATH                   0x0012 /* `struct path' (also includes `struct vfs')
                                                   * Castable into: HANDLE_TYPE_MFILE, HANDLE_TYPE_DIRECTORYENTRY */
#define HANDLE_TYPE_FS                     0x0013 /* `struct fs' */
#define HANDLE_TYPE_MMAN                   0x0014 /* `struct mman' */
#define HANDLE_TYPE_TASK                   0x0015 /* `struct taskpid'
                                                   * Castable into: HANDLE_TYPE_FS, HANDLE_TYPE_MMAN, HANDLE_TYPE_PIDNS */
#define HANDLE_TYPE_MODULE                 0x0016 /* `struct module' */
#define HANDLE_TYPE_PIDNS                  0x0017 /* `struct pidns' */
#define HANDLE_TYPE_DRIVER_LOADLIST        0x0018 /* `struct driver_loadlist' */
#define HANDLE_TYPE_CHARACTERDEVICE        0x0019 /* `struct character_device'
                                                   * Castable into: HANDLE_TYPE_MFILE (if supported) */
#define HANDLE_TYPE_MPART                  0x001a /* `struct mpart' */
#define HANDLE_TYPE_MODULE_SECTION         0x001b /* `struct module_section' */
#define HANDLE_TYPE_COUNT                  0x001c /* # of recognized handle types
                                                   * NOTE: After changing  this value,  be sure  to
                                                   * `touch kos/src/kernel/include/kernel/handle.h' */

/* Invoke `cb(int HANDLE_TYPE, typename T)' for each handle type with an associated struct */
#define HANDLE_FOREACH_TYPE(cb)                                           \
	cb(HANDLE_TYPE_MFILE, struct mfile)                                   \
	cb(HANDLE_TYPE_BLOCKDEVICE, struct basic_block_device)                \
	cb(HANDLE_TYPE_DIRECTORYENTRY, struct directory_entry)                \
	cb(HANDLE_TYPE_FILE, struct file)                                     \
	cb(HANDLE_TYPE_ONESHOT_DIRECTORY_FILE, struct oneshot_directory_file) \
	cb(HANDLE_TYPE_PATH, struct path)                                     \
	cb(HANDLE_TYPE_FS, struct fs)                                         \
	cb(HANDLE_TYPE_MMAN, struct mman)                                     \
	cb(HANDLE_TYPE_TASK, struct taskpid)                                  \
	cb(HANDLE_TYPE_MODULE, struct driver)                                 \
	cb(HANDLE_TYPE_PIPE, struct pipe)                                     \
	cb(HANDLE_TYPE_PIPE_READER, struct pipe_reader)                       \
	cb(HANDLE_TYPE_PIPE_WRITER, struct pipe_writer)                       \
	cb(HANDLE_TYPE_PIDNS, struct pidns)                                   \
	cb(HANDLE_TYPE_DRIVER_LOADLIST, struct driver_state)                  \
	cb(HANDLE_TYPE_CHARACTERDEVICE, struct character_device)              \
	cb(HANDLE_TYPE_SIGNALFD, struct signalfd)                             \
	cb(HANDLE_TYPE_MPART, struct mpart)                                   \
	cb(HANDLE_TYPE_FUTEX, struct mfutex)                                  \
	cb(HANDLE_TYPE_FUTEXFD, struct mfutexfd)                              \
	cb(HANDLE_TYPE_MODULE_SECTION, struct driver_section)                 \
	cb(HANDLE_TYPE_SOCKET, struct socket)                                 \
	cb(HANDLE_TYPE_UAIO, struct uaio_controller)

/* Invoke `cb(int HANDLE_TYPE, typename T)' for each handle  type
 * that could reasonably be used for callback registrations (such
 * as `register_async_worker()' or `hisr_register()') */
#define HANDLE_FOREACH_CUSTOMTYPE(cb)                        \
	cb(HANDLE_TYPE_MFILE, struct mfile)                      \
	cb(HANDLE_TYPE_BLOCKDEVICE, struct basic_block_device)   \
	cb(HANDLE_TYPE_MMAN, struct mman)                        \
	cb(HANDLE_TYPE_MODULE, struct driver)                    \
	cb(HANDLE_TYPE_CHARACTERDEVICE, struct character_device) \
	cb(HANDLE_TYPE_SOCKET, struct socket)                    \
	cb(HANDLE_TYPE_UAIO, struct uaio_controller)



/* Handle type-kind codes (used to identify special sub-classes of handle types). */
#define HANDLE_TYPEKIND_GENERIC 0x0000 /* Generic catch-all handle-type kind */

/* Handle kinds for `HANDLE_TYPE_MFILE' */
#define HANDLE_TYPEKIND_DATABLOCK_GENERIC     0x0000 /* The handle refers to a `struct mfile' */
#define HANDLE_TYPEKIND_DATABLOCK_INODE       0x0001 /* The handle refers to a `struct inode' */
#define HANDLE_TYPEKIND_DATABLOCK_REGULARNODE 0x0002 /* The handle refers to a `struct regular_node' */
#define HANDLE_TYPEKIND_DATABLOCK_DIRECTORY   0x0003 /* The handle refers to a `struct directory_node' */
#define HANDLE_TYPEKIND_DATABLOCK_SUPERBLOCK  0x0004 /* The handle refers to a `struct superblock' */
#define HANDLE_TYPEKIND_DATABLOCK_SYMLINKNODE 0x0005 /* The handle refers to a `struct symlink_node' */
#define HANDLE_TYPEKIND_DATABLOCK_FIFONODE    0x0006 /* The handle refers to a `struct fifo_node' */
#define HANDLE_TYPEKIND_DATABLOCK_SOCKETNODE  0x0007 /* The handle refers to a `struct socket_node' */

/* Handle kinds for `HANDLE_TYPE_BLOCKDEVICE' */
#define HANDLE_TYPEKIND_BLOCKDEVICE_GENERIC   0x0000 /* The handle refers to a `struct basic_block_device' */
#define HANDLE_TYPEKIND_BLOCKDEVICE_PARTITION 0x0001 /* The handle refers to a `struct block_device_partition' */
#define HANDLE_TYPEKIND_BLOCKDEVICE_DRIVEROOT 0x0002 /* The handle refers to a `struct block_device' */

/* Handle kinds for `HANDLE_TYPE_CHARACTERDEVICE' */
#define HANDLE_TYPEKIND_CHARACTERDEVICE_GENERIC  0x0000 /* The handle refers to a `struct character_device' */
#define HANDLE_TYPEKIND_CHARACTERDEVICE_TTYBASE  0x0001 /* The handle refers to a `struct ttybase_device' */
#define HANDLE_TYPEKIND_CHARACTERDEVICE_TTY      0x0002 /* The handle refers to a `struct tty_device' and `struct ttybase_device' */
#define HANDLE_TYPEKIND_CHARACTERDEVICE_PTY      0x0003 /* The handle refers to a `struct pty_master' and `struct ttybase_device' */
#define HANDLE_TYPEKIND_CHARACTERDEVICE_KEYBOARD 0x0004 /* The handle refers to a `struct keyboard_device' */
#define HANDLE_TYPEKIND_CHARACTERDEVICE_MOUSE    0x0005 /* The handle refers to a `struct mouse_device' */

/* Handle kinds for `HANDLE_TYPE_PATH' */
#define HANDLE_TYPEKIND_PATH_GENERIC          0x0000 /* The handle refers to a `struct path' */
#define HANDLE_TYPEKIND_PATH_VFSROOT          0x0001 /* The handle refers to a `struct vfs' */

/* Handle kinds for `HANDLE_TYPE_MODULE' */
#define HANDLE_TYPEKIND_MODULE_GENERIC        0x0000 /* The handle refers to a `struct module' */
#define HANDLE_TYPEKIND_MODULE_DRIVER         0x0001 /* The handle refers to a `struct driver' */

/* Handle kinds for `HANDLE_TYPE_MODULE_SECTION' */
#define HANDLE_TYPEKIND_MODULE_SECTION_GENERIC 0x0000 /* The handle refers to a `struct module_section' */
#define HANDLE_TYPEKIND_MODULE_SECTION_DRIVER  0x0001 /* The handle refers to a `struct driver_section' */


#endif /* !_KOS_KERNEL_HANDLE_H */
