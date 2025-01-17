/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_DMESG_H
#define GUARD_KERNEL_INCLUDE_KERNEL_DMESG_H 1

#include <kernel/compiler.h>

#include <kernel/syslog.h>
#include <kernel/types.h>

#include <bits/crt/format-printer.h>


/*[[[config CONFIG_KERNEL_DMESG_BUFFER_SIZE! = 16384]]]*/
#ifndef CONFIG_KERNEL_DMESG_BUFFER_SIZE
#define CONFIG_KERNEL_DMESG_BUFFER_SIZE 16384
#endif /* !CONFIG_KERNEL_DMESG_BUFFER_SIZE */
/*[[[end]]]*/

#ifdef __CC__
DECL_BEGIN

/* The dmesg buffer is a wrap-around buffer of tightly packed, consecutive  packets
 * written as a continuous stream to the `dmesg_buffer' buffer, with any index that
 * would go beyond the buffer's end simply wrapping around.
 * Any given packet has the following layout.
 *   [0xc0 | a]            Seconds since `dmesg_secondsbase'
 *   [0xc0 | b]            Seconds since `dmesg_secondsbase' + (b << 6)
 *   [0xc0 | c]            Seconds since `dmesg_secondsbase' + (c << 12)
 *   [0xc0 | ...]          Seconds since `dmesg_secondsbase' + (... << (6 * X))
 *    0x80 | neg*0x20 | x  Seconds since `dmesg_secondsbase' + (x << (6 * Y))
 *    0x80 | nano0         Nano seconds
 *    0x80 | nano1         Nano seconds
 *    0x80 | nano2         Nano seconds
 *    0x80 | nano3         Nano seconds
 *    0x80 | level_nano4   Nano seconds and level
 *    message...           The log message (in ASCII and without trailing line-feeds)
 *    message_chksum       Checksum for `message' (never 0):
 *                         >> if (message_chksum != 0xff) {
 *                         >>     ok = (u8)(sum(message.bytes) + message_chksum) == 0;
 *                         >> } else {
 *                         >>     u8 temp = (u8)sum(message.bytes);
 *                         >>     ok = temp == 0 || temp == 1;
 *                         >> }
 *    0x00                 NUL packet terminator
 * >> // 30-bit nano second timer
 * >> nano = ((nano0 & 0x7f)) | ((nano1 & 0x7f) << 7) |
 * >>        ((nano2 & 0x7f) << 14) | ((nano3 & 0x7f) << 21) |
 * >>        ((level_nano4 & 0x3) << 28);
 * >> // 5-bit log level index
 * >> level = (level_nano4 & 0x7c) >> 2;
 * Note that nowhere inside of a  packet NUL-bytes can appear, meaning  that
 * the prev/next packet can be found by searching for the prev/next NUL-byte
 * within  this buffer. However, be aware that  the buffer can change at any
 * time, meaning that any packet decoding errors must be considered the same
 * as having fully wrapped around the buffer. */
DATDEF byte_t dmesg_buffer[CONFIG_KERNEL_DMESG_BUFFER_SIZE];

/* Base-line seconds for all cached dmesg packets. */
DATDEF time_t dmesg_secondsbase;

/* Total number  of bytes  ever written  to `dmesg_buffer'  in the  past.
 * A pointer to the end of the last-written packet can thus be calculated
 * as `&dmesg_buffer[dmesg_size % CONFIG_KERNEL_DMESG_BUFFER_SIZE]' */
DATDEF size_t dmesg_size;

/* Non-zero if `dmesg_buffer' may be in an inconsistent state. */
DATDEF WEAK unsigned int dmesg_consistent;

/* The syslog sink for writing to the dmesg buffer.
 * This sink is part of the default set of syslog sinks, alongside
 * the    optional,    arch-specific    `ARCH_DEFAULT_SYSLOG_SINK' */
DATDEF struct syslog_sink dmesg_sink;


/* Try to load a system log message into `buffer' and
 * validate that the  message's checksum is  in-tact.
 * WARNING: Even with the checksum check  in place, there is a  1/256
 *          chance that a corrupted system log message could be read.
 *          And  even beyond this, there is a chance that a corrupted
 *          message had previously been written to the dmesg  buffer.
 *          These chances are extremely slim, however still non-zero,
 *          so be aware that the produced message may not be what was
 *          originally written!
 * HINT: Please  note   that  while   this  function   technically  allows   you
 *       to extract messages that are longer than `CONFIG_KERNEL_SYSLOG_LINEMAX'
 *       bytes  of  raw  text  (without   the  trailing  \n-character),  it   is
 *       impossible  to  write messages  longer than  this  to the  dmesg buffer
 * @param: buffer:         The target buffer (with enough space for at least `message_length' bytes)
 * @param: message_offset: Offset into the dmesg buffer where the message starts.
 * @param: message_length: The length of the written message.
 * @return: true:  Successfully extracted the message.
 * @return: false: The message's checksum did not match (this likely means  that
 *                 the end of the dmesg backlog was reached, since another entry
 *                 was probably responsible for overwriting this one's message) */
FUNDEF bool
NOTHROW_NCX(KCALL dmesg_getmessage)(NCX char *buffer,
                                    size_t message_offset,
                                    size_t message_length);

/* Callback for `dmesg_enum()'
 * @param: arg:    The same value originally given to `dmesg_enum()'
 * @param: packet: A non-volatile and verified copy of the original system log packet.
 * @param: level:  The syslog level under which `packet' was posted.
 * @param: nth:    Specifies  the N  in N'th  most recently  posted system log
 *                 message, with counting starting with `0', but including any
 *                 messages that may have been skipped due to `offset'
 * @return: >= 0:  Success (continue enumeration)
 * @return: < 0:   Error (stop enumeration and have `dmesg_enum()' return this same value) */
typedef NONNULL_T((2)) ssize_t
(KCALL *dmesg_enum_t)(void *arg, struct syslog_packet *__restrict packet,
                      unsigned int level, unsigned int nth);

/* Enumerate up to `limit' recently written system log entries.
 * s.a. The simplified  variant of  this  function `dmesg_enum()'  with  automatically
 *      handles message extraction and checksum verification, as well as automatically
 *      stopping enumeration once a bad checksum is encountered.
 * NOTE: Log messages are enumerated from most-recent to least-recent
 * @param: callback: Enumeration callback.
 * @param: arg:      Argument to-be passed to `*callback'
 * @param: limit:    The max number of messages to enumerate
 * @param: offset:   The number of leading messages to skip
 * @return: >= 0:    The sum of all invocations of `*callback'
 *                   If `*callback' was never invoked, or always returned
 *                   `0', `0'  will also  be returned  by this  function.
 * @return: < 0:     The propagation of the first negative return value of `*callback'. */
FUNDEF NONNULL((1)) ssize_t
NOTHROW_CB(KCALL dmesg_enum)(dmesg_enum_t callback, void *arg,
                             unsigned int offset DFL(0),
                             unsigned int limit DFL((unsigned int)-1));

/* Lookup the `nth' latest dmesg packet, and store it within `buf'
 * @param: buf:        The packet buffer (must be non-NULL)
 * @param: plevel:     When non-NULL, store the level of the packet here.
 * @param: msg_buflen: The size of `buf->sp_msg' (in bytes)
 * @return: > msg_buflen:          The required buffer size for `buf->sp_msg'
 * @return: >= 0 && <= msg_buflen: [== buf->sp_len] Success
 * @return: < 0:                   No such syslog packet. */
FUNDEF s16
NOTHROW_NCX(KCALL dmesg_getpacket)(NCX struct syslog_packet *buf,
                                   NCX unsigned int *plevel,
                                   u16 msg_buflen, unsigned int nth);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_DMESG_H */
