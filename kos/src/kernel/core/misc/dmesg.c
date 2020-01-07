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
#ifndef GUARD_KERNEL_SRC_MISC_DMESG_C
#define GUARD_KERNEL_SRC_MISC_DMESG_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */
#define _KOS_SOURCE 1

/* NOTE: Don't add any assertion checks to this file!
 *       The syslog is used excessively by all kernel panic/assert/check
 *       mechanisms, everything in here that may be called by `syslog_printer()'
 *       must be fully re-entrant and non-blocking! */

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/function.h>
#include <kernel/dmesg.h>

#include <hybrid/atomic.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <stddef.h>

DECL_BEGIN


/* The dmesg buffer is a wrap-around buffer of tightly packed, consecutive packets
 * written as a continuous stream to the `dmesg_buffer' buffer, with any index that
 * would go beyond the buffer's end simply wrapping around.
 * Any given packet has the following layout.
 *   [0xc0 | a]            Seconds since `dmesg_secondsbase'
 *   [0xc0 | b]            Seconds since `dmesg_secondsbase' + (b << 6)
 *   [0xc0 | c]            Seconds since `dmesg_secondsbase' + (c << 12)
 *   [0xc0 | ...]          Seconds since `dmesg_secondsbase' + (... << (6 * X))
 *    0x80 | x             Seconds since `dmesg_secondsbase' + (x << (6 * Y))
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
PUBLIC ATTR_BSS byte_t dmesg_buffer[CONFIG_DMESG_BUFFER_SIZE] = {};

/* Base-line seconds for all cached dmesg packets. */
PUBLIC ATTR_BSS time_t dmesg_secondsbase = 0;

/* Non-zero if `dmesg_buffer' may be in an inconsistent state. */
PUBLIC ATTR_BSS WEAK unsigned int dmesg_consistent = 0;

/* Total number of bytes ever written to `dmesg_buffer' in the past.
 * A pointer to the end of the last-written packet can thus be calculated
 * as `&dmesg_buffer[dmesg_size % CONFIG_DMESG_BUFFER_SIZE]' */
PUBLIC ATTR_BSS size_t dmesg_size = 0;

#define getb() (dmesg_buffer[(offset++) % CONFIG_DMESG_BUFFER_SIZE])
PRIVATE ATTR_COLDTEXT ATTR_COLD ATTR_NOINLINE NOBLOCK size_t
NOTHROW(FCALL decode_rel_seconds)(size_t offset, s64 *__restrict presult) {
	unsigned int shift = 0;
	*presult = 0;
	while (shift < 64) {
		byte_t b = getb();
		if ((b & 0xc0) == 0x80) {
			*presult |= (s64)(b & 0x1f) << shift;
			if (b & 0x20)
				*presult = -*presult;
			break;
		}
		*presult |= (s64)(b & 0x3f) << shift;
		shift += 6;
	}
	return offset;
}
#undef getb

PRIVATE ATTR_COLDTEXT ATTR_COLD ATTR_NOINLINE NOBLOCK void
NOTHROW(FCALL dmesg_compress_timestamps)(void) {
	s64 seconds_diff;
	size_t total_size, offset_from_end;
	size_t offset_from_start, oldest_packet_start;
	size_t read_offset, write_offset;
again:
	total_size          = ATOMIC_READ(dmesg_size);
	offset_from_end     = 0;
	oldest_packet_start = (size_t)-1;
	offset_from_start   = total_size;
#define getb() (++offset_from_end, --offset_from_start, dmesg_buffer[offset_from_start % CONFIG_DMESG_BUFFER_SIZE])
	while (offset_from_end < CONFIG_DMESG_BUFFER_SIZE) {
		byte_t b = getb();
		if (b != 0)
			continue;
		oldest_packet_start = offset_from_start + 1;
	}
#undef getb
	if unlikely(oldest_packet_start == (size_t)-1)
		return;
	/* Decode the seconds offset of the oldest packet. */
	decode_rel_seconds(oldest_packet_start, &seconds_diff);
	if (seconds_diff >= -0x3f && seconds_diff <= 0x3f)
		return;
	if unlikely(total_size != ATOMIC_READ(dmesg_size))
		goto again;
	/* Subtract `rel_seconds' form all packet timestamps and add it to `dmesg_secondsbase' */
	ATOMIC_FETCHINC(dmesg_consistent);
	COMPILER_BARRIER();
	read_offset  = oldest_packet_start;
	write_offset = oldest_packet_start;
#define getb()     (dmesg_buffer[(read_offset++) % CONFIG_DMESG_BUFFER_SIZE])
#define putb(byte) (dmesg_buffer[write_offset % CONFIG_DMESG_BUFFER_SIZE] = (byte), ++write_offset)
	for (;;) {
		s64 seconds;
		u8 seconds_neg;
		read_offset = decode_rel_seconds(read_offset, &seconds);
		if unlikely(read_offset >= total_size)
			break;
		seconds -= seconds_diff;
		seconds_neg = 0;
		if unlikely(seconds < 0) {
			seconds = -seconds;
			seconds_neg = 0x20;
		}
		while (seconds > 0x1f) {
			putb(0xc0 | (u8)(seconds & 0x3f));
			seconds = (s64)((u64)seconds >> 6);
		}
		putb(0x80 | seconds_neg | (u8)seconds);
		/* Copy data until the next the next NUL-byte or `total_size' is reached. */
		for (;;) {
			byte_t b;
			if (read_offset >= total_size)
				goto done;
			b = getb();
			putb(b);
			if (!b)
				break; /* NUL byte was copied. */
		}
	}
#undef putb
#undef getb
done:
	dmesg_size = write_offset;
	dmesg_secondsbase += seconds_diff;
	COMPILER_BARRIER();
	ATOMIC_FETCHDEC(dmesg_consistent);
}

INTERN NOBLOCK void
NOTHROW(FCALL dmesg_post)(struct syslog_packet const *__restrict packet,
                          unsigned int level) {
	s64 rel_seconds;
	u8 rel_seconds_neg;
	u32 nano;
	size_t offset = dmesg_size;
	u16 i, len;
	i   = 0;
	len = packet->sp_len;
	COMPILER_BARRIER();
#define putb(byte) (dmesg_buffer[offset % CONFIG_DMESG_BUFFER_SIZE] = (byte), ++offset)
again_header:
	rel_seconds = (s64)(packet->sp_time - dmesg_secondsbase);
	rel_seconds_neg = 0;
	if unlikely(rel_seconds < 0) {
		rel_seconds     = -rel_seconds;
		rel_seconds_neg = 0x20;
	}
	if unlikely((u64)rel_seconds > 0x7fffff) {
		if unlikely(!offset) /* This should only happen once. */
			dmesg_secondsbase = packet->sp_time;
		else {
			dmesg_compress_timestamps();
		}
		rel_seconds = (u64)(packet->sp_time - dmesg_secondsbase);
		rel_seconds_neg = 0;
		if unlikely(rel_seconds < 0) {
			rel_seconds     = -rel_seconds;
			rel_seconds_neg = 0x20;
		}
	}
	while (rel_seconds > 0x1f) {
		putb(0xc0 | (u8)(rel_seconds & 0x3f));
		rel_seconds = (s64)((u64)rel_seconds >> 6);
	}
	putb(0x80 | rel_seconds_neg | (u8)rel_seconds);
	nano = packet->sp_nsec;
	putb(0x80 | (nano & 0x7f));
	putb(0x80 | ((nano >> 7) & 0x7f));
	putb(0x80 | ((nano >> 14) & 0x7f));
	putb(0x80 | ((nano >> 21) & 0x7f));
	putb(0x80 | ((nano >> 28) & 0x3) | ((level << 2) & 0x7c));
	for (; i < len; ++i) {
		char ch = packet->sp_msg[i];
		if (ch == '\n')
			break; /* Don't include the trailing line-feed characters in dmesg */
		putb(ch);
		if unlikely(!ch)
			goto again_header; /* May happen due to race conditions (just write another header) */
	}
	putb(0); /* Terminate the packet */
#undef putb
	COMPILER_BARRIER();
	dmesg_size = offset;
}


PRIVATE NOBLOCK void
NOTHROW(FCALL dmesg_sink_impl)(struct syslog_sink *__restrict UNUSED(self),
                               struct syslog_packet const *__restrict packet,
                               unsigned int level) {
	dmesg_post(packet, level);
}

/* The syslog sink for writing to the dmesg buffer.
 * This sink is part of the default set of syslog sinks, alongside
 * the optional, arch-specific `ARCH_DEFAULT_SYSLOG_SINK' */
PUBLIC struct syslog_sink dmesg_sink = {
	/* .ss_refcnt = */ 2, /* +1: dmesg_sink, +1: default_syslog_sink_array */
	/* .ss_levels = */ SYSLOG_SINK_DEFAULT_LEVELS,
	/* .ss_sink   = */ &dmesg_sink_impl,
	/* .ss_fini   = */ NULL
};

/* While running the builtin debugger, don't write log messages to dmesg.
 * This way, dmesg doesn't get flooded with messages from within the debugger,
 * which could otherwise pose problems when attempting to inspect dmesg logs
 * from within the debugger, more messages get added, maybe even override the
 * ones you were attempting to look at. */
DEFINE_DBG_BZERO_OBJECT(dmesg_sink.ss_levels);


DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_DMESG_C */
