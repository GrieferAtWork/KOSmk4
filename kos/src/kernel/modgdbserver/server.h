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
#ifndef GUARD_MODGDBSERVER_SERVER_H
#define GUARD_MODGDBSERVER_SERVER_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h> /* KERNELSPACE_HIGHMEM */

#include <hybrid/typecore.h>

#include "gdb.h"

/* To function properly with this driver (and the way it is designed  to
 * debug  an entire operating system in a way that makes GDB think it is
 * debugging a process that has fork()+exec()'ed itself a whole bunch of
 * times), GDB must be initialized as:
 * >> set schedule-multiple on     # Allow multiple processes to run at the same time
 * >> set detach-on-fork off       # Don't detach the child/parent process after fork()
 * >> set follow-fork-mode child   # (Might be a bug in gdb): Required to prevent GDB from
 * >>                              # removing breakpoints from the child process after fork()
 * >>                              # The documentation says that it would, however it also
 * >>                              # seems to assume that `schedule-multiple' is `off', so
 * >>                              # I'm just happy that setting `child' here works in my
 * >>                              # favor. (And I hope that there aren't any cases where
 * >>                              # GDB would still silently discard breakpoints...)
 */

#undef HAVE_GDB_DEBUG
#if 0
#include <kernel/printk.h>
#define HAVE_GDB_DEBUG 1
#define GDB_DEBUG(...) printk(KERN_DEBUG __VA_ARGS__)
#else
#define GDB_DEBUG(...) (void)0
#endif


DECL_BEGIN

#define GDB_REMOTE_FEATURE_FORKEVENTS   0x0001 /* Enable reporting of fork events. */
#define GDB_REMOTE_FEATURE_VFORKEVENTS  0x0002 /* Enable reporting of vfork events. */
#define GDB_REMOTE_FEATURE_EXECEVENTS   0x0004 /* Enable reporting of exec events. */
#define GDB_REMOTE_FEATURE_THREADEVENTS 0x0008 /* Enable reporting of thread events. */
#define GDB_REMOTE_FEATURE_SWBREAK      0x0010 /* `swbreak+' */
#define GDB_REMOTE_FEATURE_HWBREAK      0x0020 /* `hwbreak+' */
INTDEF uintptr_t GDBRemote_Features; /* Set of `GDB_REMOTE_FEATURE_*' */

#define GDB_SERVER_FEATURE_MULTIPROCESS 0x0001 /* Enable (and use) multiprocess extensions. */
#define GDB_SERVER_FEATURE_NONSTOP      0x0002 /* GDB_Main() should  be invoked  in non-stop  mode.
                                                * (`GDBThread_IsNonStopModeActive' is set to `true'
                                                * at the start of a session)
                                                * FIXME: Somewhere, QNonStop:1 is leaking references to `struct task's
                                                * When  it's  enabled,  processes  no  longer  disappear  from  /proc! */
#define GDB_SERVER_FEATURE_ATTACHED     0x0004 /* A GDB remote has been attached. */
#define GDB_SERVER_FEATURE_NOACK        0x0008 /* No-ack mode is enabled */
#define GDB_SERVER_FEATURE_SHOWKERNEL   0x0010 /* Show the kernel core process to the GDB remote */
INTDEF uintptr_t GDBServer_Features; /* Set of `GDB_SERVER_FEATURE_*' */


/* The main GDB function
 * This function is called from the GDB host thread once locking is done. */
/* TODO: This function also needs to save+restore the current exception! (read/write memory may clobber it) */
INTDEF void NOTHROW(FCALL GDB_Main)(void);

/* Wrapper for `GDB_Main()' that will invoke said function
 * using   an   alternate,  statically   allocated  stack. */
INTDEF void NOTHROW(FCALL GDB_MainWithAlternateStack)(void);


/*[[[config CONFIG_MODGDBSERVER_PACKET_MAXLEN = (1 << 14)
 * Max length of packet data (number of writable bytes returned by `GDBPacket_Start()')
 * ]]]*/
#ifdef CONFIG_NO_MODGDBSERVER_PACKET_MAXLEN
#undef CONFIG_MODGDBSERVER_PACKET_MAXLEN
#define CONFIG_MODGDBSERVER_PACKET_MAXLEN 0
#elif !defined(CONFIG_MODGDBSERVER_PACKET_MAXLEN)
#define CONFIG_MODGDBSERVER_PACKET_MAXLEN (1 << 14)
#elif (CONFIG_MODGDBSERVER_PACKET_MAXLEN + 0) <= 0
#undef CONFIG_MODGDBSERVER_PACKET_MAXLEN
#define CONFIG_NO_MODGDBSERVER_PACKET_MAXLEN
#define CONFIG_MODGDBSERVER_PACKET_MAXLEN 0
#endif /* ... */
/*[[[end]]]*/

/* Packet API */

/* Max # of times to attempt to transmit a packet before giving up. */
INTDEF unsigned int GDBPacket_RetryTransmitLimit;

/* Begin a new packet, returning a buffer of up to `CONFIG_MODGDBSERVER_PACKET_MAXLEN' bytes. */
INTERN char *NOTHROW(FCALL GDBPacket_Start)(void);

/* Transmit a packet ending at `endptr'
 * @return: true:  Packet successfully transmitted.
 * @return: false: Transmit failed (timeout, or `GDBPacket_RetryTransmitLimit' was exceeded) */
INTDEF WUNUSED bool NOTHROW(FCALL GDBPacket_Transmit)(char *endptr);

/* Same as `GDBPacket_Transmit()', but escape special characters in the response string.
 * This is used to implement the transmission of raw binary data. */
INTDEF WUNUSED bool NOTHROW(FCALL GDBPacket_TransmitEscape)(char *endptr);

/* Transmit a notification packet (same as `GDBPacket_Transmit()', but the first byte is `%' instead of `$') */
INTDEF void NOTHROW(FCALL GDBPacket_TransmitNotification)(char *endptr);

/* Calculate and return the checksum for the given memory block. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) byte_t
NOTHROW(KCALL GDBPacket_GetCheckSum)(void const *__restrict buf, size_t buflen);

/* Convenience wrappers for sending packets. */
INTDEF WUNUSED bool NOTHROW(FCALL GDBPacket_SendEmpty)(void);
INTDEF WUNUSED NONNULL((1)) bool NOTHROW(FCALL GDBPacket_Send)(char const *__restrict text);
INTDEF WUNUSED NONNULL((1)) bool NOTHROW(VCALL GDBPacket_Sendf)(char const *__restrict format, ...);
INTDEF WUNUSED NONNULL((1)) bool NOTHROW(FCALL GDBPacket_VSendf)(char const *__restrict format, __builtin_va_list args);
INTDEF WUNUSED bool NOTHROW(FCALL GDBPacket_SendError)(u8 error_code);

/* Print a message while in non-stop or all-stop mode.
 * @return: * : The total number of printed bytes. */
INTDEF size_t FCALL GDBServer_PrintMessageInNonStopMode(USER CHECKED char const *message, size_t message_length);
INTDEF size_t FCALL GDBServer_PrintMessageInAllStopMode(USER CHECKED char const *message, size_t message_length);


#undef fromhex
#undef tohex
INTDEF char const GDB_HexChars[16];
INTDEF u8 const GDB_HexValues[256];
#define GDB_FromHex(ch) GDB_HexValues[(u8)(ch)]
#define GDB_ToHex(ord)  GDB_HexChars[(u8)(ord)]



/* TID management. */
#if __SIZEOF_POINTER__ > 4
#define GDB_KERNEL_PID          ((intptr_t)__INT64_C(0x7fffffffffffffff))
#else /* __SIZEOF_POINTER__ > 4 */
#define GDB_KERNEL_PID          ((intptr_t)__INT32_C(0x7fffffff))
#endif /* __SIZEOF_POINTER__ <= 4 */
#ifdef KERNELSPACE_HIGHMEM
#define GDB_KERNEL_TID(thread)  ((intptr_t)(thread) - KERNELSPACE_BASE)
#define GDB_KERNEL_TID_GET(tid) ((struct task *)((intptr_t)(tid) + KERNELSPACE_BASE))
#define GDB_KERNEL_TID_CHK(tid) ADDR_ISKERN((intptr_t)(tid) + KERNELSPACE_BASE)
/* 123456789ABCDEF0 */
/*     56789ABCDEF0 */
#else /* KERNELSPACE_HIGHMEM */
#define GDB_KERNEL_TID(thread)  ((intptr_t)(thread))
#define GDB_KERNEL_TID_GET(tid) ((struct task *)(intptr_t)(tid))
#define GDB_KERNEL_TID_CHK(tid) ADDR_ISKERN(intptr_t)(tid))
#endif /* !KERNELSPACE_HIGHMEM */


DECL_END

#endif /* !GUARD_MODGDBSERVER_GDB_H */
