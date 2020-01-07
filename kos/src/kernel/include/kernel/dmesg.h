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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_DMESG_H
#define GUARD_KERNEL_INCLUDE_KERNEL_DMESG_H 1

#include <kernel/compiler.h>

#include <kernel/syslog.h>
#include <kernel/types.h>

DECL_BEGIN

#ifdef __CC__

#ifndef CONFIG_DMESG_BUFFER_SIZE
#define CONFIG_DMESG_BUFFER_SIZE 16384
#endif /* !CONFIG_DMESG_BUFFER_SIZE */

/* The dmesg buffer is a wrap-around buffer of tightly packed, consecutive packets
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
 *    0x00                 NUL packet terminator (you )
 * >> // 30-bit nano second timer
 * >> nano = ((nano0 & 0x7f)) | ((nano1 & 0x7f) << 7) |
 * >>        ((nano2 & 0x7f) << 14) | ((nano3 & 0x7f) << 21) |
 * >>        ((level_nano4 & 0x3) << 28);
 * >> // 5-bit log level index
 * >> level = (level_nano4 & 0x7c) >> 2;
 * Note that nowhere inside of a packet NUL-bytes can appear, meaning that
 * the prev/next packet can be found by searching for the prev/next NUL-byte
 * within this buffer. However, be aware that the buffer can change at any
 * time, meaning that any packet decoding errors must be considered the same
 * as having fully wrapped around the buffer. */
DATDEF byte_t dmesg_buffer[CONFIG_DMESG_BUFFER_SIZE];

/* Base-line seconds for all cached dmesg packets. */
DATDEF time_t dmesg_secondsbase;

/* Total number of bytes ever written to `dmesg_buffer' in the past.
 * A pointer to the end of the last-written packet can thus be calculated
 * as `&dmesg_buffer[dmesg_size % CONFIG_DMESG_BUFFER_SIZE]' */
DATDEF size_t dmesg_size;

/* Non-zero if `dmesg_buffer' may be in an inconsistent state. */
DATDEF WEAK unsigned int dmesg_consistent;

/* The syslog sink for writing to the dmesg buffer.
 * This sink is part of the default set of syslog sinks, alongside
 * the optional, arch-specific `ARCH_DEFAULT_SYSLOG_SINK' */
DATDEF struct syslog_sink dmesg_sink;


#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_DMESG_H */
