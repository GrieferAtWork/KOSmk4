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
#ifndef _KOS_KERNEL_HANDLE_H
#define _KOS_KERNEL_HANDLE_H 1

#include <__stdinc.h>

#ifndef __KOS__
#error "KOS-only system header"
#endif /* !__KOS__ */

/* KOS Handle type codes.
 * NOTE: Changes to this list must be updated with:
 * $ deemon -F kos/src/kernel/core/fd/router.c kos/src/kernel/include/kernel/handle-proto.h && touch kos/src/kernel/include/kernel/handle.h
 */
#define HANDLE_TYPE_UNDEFINED       0x0000 /* Undefined/unused handle */
#define HANDLE_TYPE_MFILE           0x0001 /* `struct mfile' */
#define HANDLE_TYPE_DIRENT          0x0002 /* `struct fdirent' */
#define HANDLE_TYPE_PATH            0x0003 /* `struct path'
                                            * Castable into: HANDLE_TYPE_MFILE, HANDLE_TYPE_DIRENT */
#define HANDLE_TYPE_FILEHANDLE      0x0004 /* `struct filehandle'
                                            * Castable into: HANDLE_TYPE_PATH, HANDLE_TYPE_MFILE, HANDLE_TYPE_DIRENT */
#define HANDLE_TYPE_TEMPHANDLE      0x0005 /* `struct filehandle'
                                            * Castable into: HANDLE_TYPE_PATH, HANDLE_TYPE_MFILE, HANDLE_TYPE_DIRENT
                                            * Like `HANDLE_TYPE_FILEHANDLE', but bound file is deleted on `close(2)' */
#define HANDLE_TYPE_DIRHANDLE       0x0006 /* `struct dirhandle'
                                            * Castable into: HANDLE_TYPE_PATH, HANDLE_TYPE_MFILE, HANDLE_TYPE_DIRENT */
#define HANDLE_TYPE_FIFOHANDLE      0x0007 /* `struct fifohandle' */
#define HANDLE_TYPE_SOCKET          0x0008 /* `struct socket' */
#define HANDLE_TYPE_EPOLL           0x0009 /* `struct epoll_controller' */
#define HANDLE_TYPE_PIPE            0x000a /* `struct pipe' */
#define HANDLE_TYPE_PIPE_READER     0x000b /* `struct pipe_reader' */
#define HANDLE_TYPE_PIPE_WRITER     0x000c /* `struct pipe_writer' */
#define HANDLE_TYPE_EVENTFD_FENCE   0x000d /* `struct eventfd' (without `EFD_SEMAPHORE') */
#define HANDLE_TYPE_EVENTFD_SEMA    0x000e /* `struct eventfd' (with `EFD_SEMAPHORE') */
#define HANDLE_TYPE_SIGNALFD        0x000f /* `struct signalfd' */
#define HANDLE_TYPE_FUTEXFD         0x0010 /* `struct mfutexfd' */
#define HANDLE_TYPE_PIDFD           0x0011 /* `struct taskpid' */
#define HANDLE_TYPE_MODULE          0x0012 /* `struct module' */
#define HANDLE_TYPE_DRIVER_LOADLIST 0x0013 /* `struct driver_loadlist' */
#define HANDLE_TYPE_REFCOUNTABLE    0x0014 /* `struct refcountable' */
#define HANDLE_TYPE_NOTIFYFD        0x0015 /* `struct notifyfd' */
#define HANDLE_TYPE_COUNT           0x0016 /* # of recognized handle types
                                            * NOTE: After changing  this value,  be sure  to
                                            * `touch kos/src/kernel/include/kernel/handle.h' */

/* Invoke `cb(int HANDLE_TYPE, typename T)' for each handle type with an associated struct */
#define HANDLE_FOREACH_TYPE(cb)                          \
	cb(HANDLE_TYPE_MFILE, struct mfile)                  \
	cb(HANDLE_TYPE_DIRENT, struct fdirent)               \
	cb(HANDLE_TYPE_FILEHANDLE, struct filehandle)        \
	cb(HANDLE_TYPE_DIRHANDLE, struct dirhandle)          \
	cb(HANDLE_TYPE_PATH, struct path)                    \
	cb(HANDLE_TYPE_PIDFD, struct taskpid)                \
	cb(HANDLE_TYPE_MODULE, struct driver)                \
	cb(HANDLE_TYPE_EPOLL, struct epoll_controller)       \
	cb(HANDLE_TYPE_PIPE, struct pipe)                    \
	cb(HANDLE_TYPE_PIPE_READER, struct pipe_reader)      \
	cb(HANDLE_TYPE_PIPE_WRITER, struct pipe_writer)      \
	cb(HANDLE_TYPE_DRIVER_LOADLIST, struct driver_state) \
	cb(HANDLE_TYPE_SIGNALFD, struct signalfd)            \
	cb(HANDLE_TYPE_FUTEXFD, struct mfutexfd)             \
	cb(HANDLE_TYPE_SOCKET, struct socket)                \
	cb(HANDLE_TYPE_REFCOUNTABLE, struct refcountable)    \
	cb(HANDLE_TYPE_NOTIFYFD, struct notifyfd)

/* Invoke `cb(int HANDLE_TYPE, typename T)' for each handle  type
 * that could reasonably be used for callback registrations (such
 * as `register_async_worker()' or `hisr_register()') */
#define HANDLE_FOREACH_CUSTOMTYPE(cb)     \
	cb(HANDLE_TYPE_MFILE, struct mfile)   \
	cb(HANDLE_TYPE_MODULE, struct driver) \
	cb(HANDLE_TYPE_SOCKET, struct socket) \
	cb(HANDLE_TYPE_REFCOUNTABLE, struct refcountable)



/* Handle type-kind codes (used to identify special sub-classes of handle types). */
#define HANDLE_TYPEKIND_GENERIC 0x0000 /* Generic catch-all handle-type kind */

/* Handle kinds for `HANDLE_TYPE_MFILE' */
#define HANDLE_TYPEKIND_MFILE_GENERIC   0x0000 /* The handle refers to a `struct mfile' */
#define HANDLE_TYPEKIND_MFILE_FNODE     0x0001 /* The handle refers to a `struct fnode' */
#define HANDLE_TYPEKIND_MFILE_FREGNODE  0x0002 /* The handle refers to a `struct fregnode' */
#define HANDLE_TYPEKIND_MFILE_FDIRNODE  0x0003 /* The handle refers to a `struct fdirnode' */
#define HANDLE_TYPEKIND_MFILE_FSUPER    0x0004 /* The handle refers to a `struct fsuper' */
#define HANDLE_TYPEKIND_MFILE_FLNKNODE  0x0005 /* The handle refers to a `struct flnknode' */
#define HANDLE_TYPEKIND_MFILE_FFIFONODE 0x0006 /* The handle refers to a `struct ffifonode' */
#define HANDLE_TYPEKIND_MFILE_FSOCKNODE 0x0007 /* The handle refers to a `struct fsocknode' */

/* Handle kinds for `HANDLE_TYPE_MODULE' */
#define HANDLE_TYPEKIND_MODULE_GENERIC 0x0000 /* The handle refers to a `struct module' */
#define HANDLE_TYPEKIND_MODULE_DRIVER  0x0001 /* The handle refers to a `struct driver' */


#endif /* !_KOS_KERNEL_HANDLE_H */
