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
#ifndef GUARD_MODPROCFS_FILES_SYS_NET_CORE_RWMEM_C
#define GUARD_MODPROCFS_FILES_SYS_NET_CORE_RWMEM_C 1
#define _KOS_SOURCE 1 /* snprintf returns size_t */

#include <kernel/compiler.h>

#include <sched/task.h>

#include <hybrid/atomic.h>

#include <kos/except/reason/inval.h>
#include <network/socket.h>

#include <unicode.h>

#include "../procfs.h"
#include "../util.h"

DECL_BEGIN

INTERN NONNULL((1)) ssize_t KCALL
ProcFS_Sys_Net_Core_RmemDefault_Print(struct regular_node *__restrict UNUSED(self),
                                      pformatprinter printer, void *arg) {
	return ProcFS_PrintSize(printer, arg, socket_default_rcvbufsiz);
}

INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Net_Core_RmemDefault_Write(struct regular_node *__restrict UNUSED(self),
                                      USER CHECKED void const *buf, size_t bufsize) {
	size_t newval;
	newval = ProcFS_ParseSize(buf, bufsize, SOCKET_RCVBUFMIN, socket_default_rcvbufmax);
	ATOMIC_WRITE(socket_default_rcvbufsiz, newval);
}

INTERN NONNULL((1)) ssize_t KCALL
ProcFS_Sys_Net_Core_WmemDefault_Print(struct regular_node *__restrict UNUSED(self),
                                      pformatprinter printer, void *arg) {
	return ProcFS_PrintSize(printer, arg, socket_default_sndbufsiz);
}

INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Net_Core_WmemDefault_Write(struct regular_node *__restrict UNUSED(self),
                                      USER CHECKED void const *buf, size_t bufsize) {
	size_t newval;
	newval = ProcFS_ParseSize(buf, bufsize, SOCKET_SNDBUFMIN, socket_default_sndbufmax);
	ATOMIC_WRITE(socket_default_sndbufsiz, newval);
}

INTERN NONNULL((1)) ssize_t KCALL
ProcFS_Sys_Net_Core_RmemMax_Print(struct regular_node *__restrict UNUSED(self),
                                  pformatprinter printer, void *arg) {
	return ProcFS_PrintSize(printer, arg, socket_default_rcvbufmax);
}

INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Net_Core_RmemMax_Write(struct regular_node *__restrict UNUSED(self),
                                  USER CHECKED void const *buf, size_t bufsize) {
	size_t newval, old_dfl;
	newval = ProcFS_ParseSize(buf, bufsize, SOCKET_RCVBUFMIN);
	ATOMIC_WRITE(socket_default_rcvbufmax, newval);
	do {
		old_dfl = ATOMIC_READ(socket_default_rcvbufsiz);
		if (old_dfl <= newval)
			break;
	} while (!ATOMIC_CMPXCH_WEAK(socket_default_rcvbufsiz,
	                             old_dfl, newval));
}

INTERN NONNULL((1)) ssize_t KCALL
ProcFS_Sys_Net_Core_WmemMax_Print(struct regular_node *__restrict UNUSED(self),
                                  pformatprinter printer, void *arg) {
	return ProcFS_PrintSize(printer, arg, socket_default_sndbufmax);
}

INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Net_Core_WmemMax_Write(struct regular_node *__restrict UNUSED(self),
                                  USER CHECKED void const *buf, size_t bufsize) {
	size_t newval, old_dfl;
	newval = ProcFS_ParseSize(buf, bufsize, SOCKET_SNDBUFMIN);
	ATOMIC_WRITE(socket_default_sndbufmax, newval);
	do {
		old_dfl = ATOMIC_READ(socket_default_sndbufsiz);
		if (old_dfl <= newval)
			break;
	} while (!ATOMIC_CMPXCH_WEAK(socket_default_sndbufsiz,
	                             old_dfl, newval));
}


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_SYS_NET_CORE_RWMEM_C */
