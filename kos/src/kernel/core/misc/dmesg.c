/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MISC_DMESG_C
#define GUARD_KERNEL_SRC_MISC_DMESG_C 1
#define DISABLE_BRANCH_PROFILING /* Don't profile this file */
#define _KOS_SOURCE 1
#define SYSLOG_LINEMAX CONFIG_KERNEL_SYSLOG_LINEMAX

/* NOTE: Don't add any assertion checks to this file!
 *       Because the syslog is used excessively by all kernel panic/assert/check
 *       mechanisms, everything in here that may be called by `syslog_printer()'
 *       must be fully re-entrant, non-blocking, fail-safe and fault-tolerant! */

#include <kernel/compiler.h>

#include <debugger/hook.h>
#include <kernel/dmesg.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/sched/atomic-rwlock.h>

#include <inttypes.h>
#include <stddef.h>
#include <string.h>
#include <time.h> /* NSEC_PER_SEC */

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
 *    0xc0 | tid.0         (tid >> 0) & 0x3f
 *    0xc0 | tid.1         (tid >> 6) & 0x3f
 *    0xc0 | tid.2         (tid >> 12) & 0x3f
 *    0xc0 | tid.n         (tid >> (n * 6)) & 0x3f
 *    0x80 | tid.n-1       (tid >> ((n-1) * 6)) & 0x3f
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
PUBLIC ATTR_BSS ATTR_ALIGNED(1) byte_t dmesg_buffer[CONFIG_KERNEL_DMESG_BUFFER_SIZE] = {};

/* Base-line seconds for all cached dmesg packets. */
PUBLIC ATTR_BSS time_t dmesg_secondsbase = 0;

/* Non-zero if `dmesg_buffer' may be in an inconsistent state. */
PUBLIC ATTR_BSS WEAK unsigned int dmesg_consistent = 0;

/* Total number  of bytes  ever written  to `dmesg_buffer'  in the  past.
 * A pointer to the end of the last-written packet can thus be calculated
 * as `&dmesg_buffer[dmesg_size % CONFIG_KERNEL_DMESG_BUFFER_SIZE]' */
PUBLIC ATTR_BSS size_t dmesg_size = 0;

#define getb() (dmesg_buffer[(offset++) % CONFIG_KERNEL_DMESG_BUFFER_SIZE])
PRIVATE NOBLOCK ATTR_COLD ATTR_COLDTEXT ATTR_NOINLINE size_t
NOTHROW(FCALL decode_rel_seconds)(size_t offset, s64 *__restrict presult) {
	shift_t shift = 0;
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

PRIVATE NOBLOCK ATTR_COLD ATTR_COLDTEXT ATTR_NOINLINE void
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
#define getb()                               \
	(++offset_from_end, --offset_from_start, \
	 dmesg_buffer[offset_from_start % CONFIG_KERNEL_DMESG_BUFFER_SIZE])
	while (offset_from_end < CONFIG_KERNEL_DMESG_BUFFER_SIZE) {
		byte_t b = getb();
		if (b != 0)
			continue;
		oldest_packet_start = offset_from_start + 1;
	}
#undef getb
	if unlikely(oldest_packet_start >= total_size)
		return;
	/* Decode the seconds offset of the oldest packet. */
	decode_rel_seconds(oldest_packet_start, &seconds_diff);
	if (seconds_diff >= -0x3f && seconds_diff <= 0x3f)
		return;
	if unlikely(total_size != ATOMIC_READ(dmesg_size))
		goto again;
	/* Subtract `rel_seconds' form all packet timestamps and add it to `dmesg_secondsbase' */
	ATOMIC_INC(dmesg_consistent);
	COMPILER_BARRIER();
	read_offset  = oldest_packet_start;
	write_offset = oldest_packet_start;
#define getb()     (dmesg_buffer[(read_offset++) % CONFIG_KERNEL_DMESG_BUFFER_SIZE])
#define putb(byte) (dmesg_buffer[write_offset % CONFIG_KERNEL_DMESG_BUFFER_SIZE] = (byte), ++write_offset)
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
	ATOMIC_DEC(dmesg_consistent);
}

INTERN NOBLOCK void
NOTHROW(FCALL dmesg_post)(struct syslog_packet const *__restrict packet,
                          unsigned int level) {
	s64 rel_seconds;
	u8 rel_seconds_neg;
	u8 checksum;
	u32 tid;
	u32 nano;
	size_t offset = dmesg_size;
	u16 i, len;
	i   = 0;
	len = packet->sp_len;
	if unlikely(!len)
		return; /* Ignore empty messages. */
	--len; /* Trim the trailing \n-character. */
	if unlikely(len > CONFIG_KERNEL_SYSLOG_LINEMAX)
		return; /* Disallow messages longer than `CONFIG_KERNEL_SYSLOG_LINEMAX' */
	COMPILER_BARRIER();
#define putb(byte) (dmesg_buffer[offset % CONFIG_KERNEL_DMESG_BUFFER_SIZE] = (byte), ++offset)
again_header:
	rel_seconds = (s64)(packet->sp_time - dmesg_secondsbase);
	rel_seconds_neg = 0;
	if unlikely(rel_seconds < 0) {
		rel_seconds     = -rel_seconds;
		rel_seconds_neg = 0x20;
	}
	if unlikely((u64)rel_seconds > 0x7fffff) {
		if unlikely(!offset) { /* This should only happen once. */
			dmesg_secondsbase = packet->sp_time;
		} else {
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
	/* Encode the sender TID */
	tid = (u32)packet->sp_tid;
	while (tid > 0x3f) {
		putb(0xc0 | (tid & 0x3f));
		tid >>= 6;
	}
	putb(0x80 | tid);
	checksum = 0;
	for (; i < len; ++i) {
		char ch = packet->sp_msg[i];
		if (ch == '\n')
			break; /* Don't include the trailing line-feed characters in dmesg */
		putb(ch);
		if unlikely(!ch) {
			++i;
			goto again_header; /* May happen due to race conditions (just write another header) */
		}
		checksum += (u8)ch;
	}
	checksum = 0xff - checksum;
	if (!checksum)
		checksum = 0xff;
	putb(checksum); /* Checksum */
	putb(0); /* Terminate the message */

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
 * the    optional,    arch-specific    `ARCH_DEFAULT_SYSLOG_SINK' */
PUBLIC struct syslog_sink dmesg_sink = {
	.ss_refcnt = 2, /* +1: dmesg_sink, +1: default_syslog_sink_array */
	.ss_levels = (uintptr_t)-1,
	.ss_sink   = &dmesg_sink_impl,
	.ss_fini   = NULL,
};

/* While running  the builtin  debugger, don't  write log  messages to  dmesg.
 * This way, dmesg doesn't get flooded with messages from within the debugger,
 * which could otherwise pose problems  when attempting to inspect dmesg  logs
 * from within the debugger: more messages get added, maybe even override  the
 * ones you were trying to look at. */
DEFINE_DBG_BZERO_OBJECT(dmesg_sink.ss_levels);
/* While inside of the debugger, don't make dmesg appear inconsistent. */
DEFINE_DBG_BZERO_OBJECT(dmesg_consistent);


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
 *       bytes  of  raw text,  it is  impossible to  write messages  longer than
 *       this to the dmesg buffer
 * @param: buffer:         The target buffer (with enough space for at least `message_length' bytes)
 * @param: message_offset: Offset into the dmesg buffer where the message starts.
 * @param: message_length: The length of the written message.
 * @return: true:  Successfully extracted the message.
 * @return: false: The message's checksum did not match (this likely means  that
 *                 the end of the dmesg backlog was reached, since another entry
 *                 was probably responsible for overwriting this one's message) */
PUBLIC bool KCALL
dmesg_getmessage(USER CHECKED char *buffer,
                 size_t message_offset,
                 size_t message_length)
		THROWS(E_SEGFAULT) {
	size_t i;
	u8 nul, chksum, real_chksum = 0;
	for (i = 0; i < message_length; ++i, ++message_offset) {
		byte_t b;
		b = dmesg_buffer[message_offset % CONFIG_KERNEL_DMESG_BUFFER_SIZE];
		real_chksum += b;
		buffer[i] = (char)b;
	}
	chksum = dmesg_buffer[(message_offset++) % CONFIG_KERNEL_DMESG_BUFFER_SIZE]; /* checksum */
	nul    = dmesg_buffer[(message_offset++) % CONFIG_KERNEL_DMESG_BUFFER_SIZE]; /* trailing NUL-byte */
	if unlikely(nul != '\0')
		return false; /* Missing trailing NUL-byte */
	real_chksum = 0xff - real_chksum;
	if (!real_chksum)
		real_chksum = 0xff;
	if unlikely(chksum != real_chksum)
		return false; /* Miss-matching checksums. */
	return true; /* Success! */
}


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
PUBLIC NONNULL((1)) ssize_t KCALL
dmesg_enum(dmesg_enum_t callback, void *arg,
           unsigned int offset, unsigned int limit) {
	ssize_t callback_temp, result = 0;
	struct syslog_packet packet;
	size_t message_end_offset;
	size_t message_start_offset;
	size_t packet_start_offset;
	size_t offset_from_end = 0;
	size_t message_length;
	unsigned int level, nth;
	byte_t temp, nano[5];
	s64 rel_seconds;
	/* Try to wait for inconsistencies to go away. */
	while (ATOMIC_READ(dmesg_consistent)) {
		if (task_tryyield_or_pause() != TASK_TRYYIELD_SUCCESS)
			break;
	}
	limit += offset;
	message_end_offset = ATOMIC_READ(dmesg_size);
#define getb()                                \
	(++offset_from_end, --message_end_offset, \
	 dmesg_buffer[message_end_offset % CONFIG_KERNEL_DMESG_BUFFER_SIZE])
	temp = getb(); /* NUL-temrinator */
	if (temp != 0)
		goto done; /* Missing NUL packet-terminator. */
	for (nth = 0; limit; --limit, ++nth) {
		getb(); /* checksum */
		if (offset_from_end >= CONFIG_KERNEL_DMESG_BUFFER_SIZE)
			goto done;
#undef getb
		packet_start_offset = message_end_offset;
#define getb()                                 \
	(++offset_from_end, --packet_start_offset, \
	 dmesg_buffer[packet_start_offset % CONFIG_KERNEL_DMESG_BUFFER_SIZE])
		for (;;) {
			byte_t b;
			b = getb();
			if (!b)
				break;
			if (offset_from_end >= CONFIG_KERNEL_DMESG_BUFFER_SIZE)
				goto done;
		}
		++packet_start_offset;
		message_start_offset = packet_start_offset;
		/* Decode the message's timestamp. */
		message_start_offset = decode_rel_seconds(message_start_offset, &rel_seconds);
		packet.sp_time = dmesg_secondsbase + rel_seconds;
		nano[0] = dmesg_buffer[(message_start_offset++) % CONFIG_KERNEL_DMESG_BUFFER_SIZE];
		nano[1] = dmesg_buffer[(message_start_offset++) % CONFIG_KERNEL_DMESG_BUFFER_SIZE];
		nano[2] = dmesg_buffer[(message_start_offset++) % CONFIG_KERNEL_DMESG_BUFFER_SIZE];
		nano[3] = dmesg_buffer[(message_start_offset++) % CONFIG_KERNEL_DMESG_BUFFER_SIZE];
		nano[4] = dmesg_buffer[(message_start_offset++) % CONFIG_KERNEL_DMESG_BUFFER_SIZE];
		/* Decode the message's level. */
		level = (nano[4] & 0x7c) >> 2;
		if (level > SYSLOG_LEVEL_COUNT)
			goto done; /* Invalid syslog level */
		/* Decode the message's nanosecond timestamp. */
		packet.sp_nsec = ((u32)(nano[0] & 0x7f)) |
		                 ((u32)(nano[1] & 0x7f) << 7) |
		                 ((u32)(nano[2] & 0x7f) << 14) |
		                 ((u32)(nano[3] & 0x7f) << 21) |
		                 ((u32)(nano[4] & 0x3) << 28);
		if unlikely(packet.sp_nsec >= NSEC_PER_SEC)
			goto done; /* Invalid nano seconds timestamp. */
		/* Decode the sender TID of the packet. */
		{
			u32 tid = 0;
			unsigned int i = 0;
			for (;; i += 6) {
				uint8_t b;
				b = dmesg_buffer[(message_start_offset++) % CONFIG_KERNEL_DMESG_BUFFER_SIZE];
				tid |= (u32)(b & 0x3f) << i;
				if ((b & 0xc0) != 0xc0)
					break;
			}
			packet.sp_tid = tid;
		}
		message_length = message_end_offset - message_start_offset;
		if unlikely(message_length > CONFIG_KERNEL_SYSLOG_LINEMAX)
			goto done; /* Message too long */
		/* Extract the entry's message and verify its checksum. */
		if (!dmesg_getmessage(packet.sp_msg,
		                      message_start_offset,
		                      message_length))
			goto done;
#undef getb
		message_end_offset = packet_start_offset - 1;
		if (offset) {
			--offset;
			continue;
		}
		/* Enumerate this packet. */
		packet.sp_len = (u16)message_length;
		callback_temp = (*callback)(arg, &packet, level, nth);
		if unlikely(callback_temp < 0)
			goto err;
		result += callback_temp;
	}
done:
	return result;
err:
	return callback_temp;
}




struct dmesg_getpacket_data {
	USER CHECKED struct syslog_packet *dg_buf;        /* [1..1] Buffer */
	USER CHECKED unsigned int         *dp_plevel;     /* [0..1] Level pointer. */
	u16                                dg_msg_buflen; /* Message buffer length. */
};

PRIVATE NONNULL((2)) ssize_t KCALL
dmesg_getpacket_callback(void *arg, struct syslog_packet *__restrict packet,
                         unsigned int level, unsigned int UNUSED(nth)) {
	struct dmesg_getpacket_data *data;
	data = (struct dmesg_getpacket_data *)arg;
	if (data->dg_msg_buflen >= packet->sp_len) {
		memcpy(data->dg_buf, packet,
		       offsetof(struct syslog_packet, sp_msg) +
		       packet->sp_len);
		if (data->dp_plevel)
			*data->dp_plevel = level;
	}
	return (ssize_t)packet->sp_len + 1;
}

/* Lookup the `nth' latest dmesg packet, and store it within `buf'
 * @param: buf:        The packet buffer (must be non-NULL)
 * @param: plevel:     When non-NULL, store the level of the packet here.
 * @param: msg_buflen: The size of `buf->sp_msg' (in bytes)
 * @return: > msg_buflen:          The required buffer size for `buf->sp_msg'
 * @return: >= 0 && <= msg_buflen: [== buf->sp_len] Success
 * @return: < 0:                   No such syslog packet. */
PUBLIC s16 KCALL
dmesg_getpacket(USER CHECKED struct syslog_packet *buf,
                USER CHECKED unsigned int *plevel,
                u16 msg_buflen, unsigned int nth) {
	ssize_t error;
	struct dmesg_getpacket_data data;
	data.dg_buf        = buf;
	data.dp_plevel     = plevel;
	data.dg_msg_buflen = msg_buflen;
	error = dmesg_enum(&dmesg_getpacket_callback, &data, nth, 1);
	if (error <= 0)
		return -1; /* No such packet. */
	return (s16)(u16)(error - 1);
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_DMESG_C */
