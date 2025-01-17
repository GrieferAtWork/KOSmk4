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
#ifndef GUARD_MODGDBSERVER_PACKET_C
#define GUARD_MODGDBSERVER_PACKET_C 1

/* Packet API */

#include <kernel/compiler.h>

#include <kernel/printk.h>

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "gdb.h"
#include "server.h"

DECL_BEGIN

/* Buffer used to store the contents of remote command packets. */
INTDEF char GDBRemote_CommandBuffer[CONFIG_MODGDBSERVER_PACKET_MAXLEN];

/* Buffer for out-bound packets. */
PRIVATE char GDBServer_PacketBuffer[CONFIG_MODGDBSERVER_PACKET_MAXLEN + 4];

/* Begin a new packet, returning a buffer of up to `CONFIG_MODGDBSERVER_PACKET_MAXLEN' bytes. */
INTERN ATTR_CONST char *NOTHROW(FCALL GDBPacket_Start)(void) {
	return GDBServer_PacketBuffer + 1;
}



/* @return: '+': ACK
 * @return: '-': NACK
 * @return: -1:  Error (timed out) */
LOCAL int NOTHROW(FCALL GDBPacket_WaitForResponse)(size_t previous_packet_length_with_frame) {
	/* Deal with the repeated packet sending done by GDB when it gets nervous
	 * This  happens when we don't immediately respond after QEMU connects to
	 * gdb  early on, but we need some time to initialize before we can start
	 * to  respond  to  the  packets  that  will  have  already  been send...
	 * We  need a smart  way of waiting for  +/- responses that automatically
	 * skips unexpected command packets as a whole */
	int result;
	for (;;) {
		result = GDBRemote_TimedGetByte();
		if (likely(result == '+') || unlikely(result == '-' || result < 0))
			goto done;
		if (result == '$') {
			/* This is what I was talking about above!
			 * An unexpected packet probably taken from kind of buffer. */
			char *dst = GDBRemote_CommandBuffer;
			for (;;) {
				result = GDBRemote_TimedGetByte();
				if (result < 0)
					goto done;
				if (result == '#')
					break;
				if (dst < COMPILER_ENDOF(GDBRemote_CommandBuffer))
					*dst++ = (char)result;
				if (result == '}') {
					/* Escaped byte. */
					result = GDBRemote_TimedGetByte();
					if (result < 0)
						goto done;
					if (dst < COMPILER_ENDOF(GDBRemote_CommandBuffer))
						*dst++ = (char)result;
				}
			}
			/* Read the 2 trailing checksum character following the  */
			result = GDBRemote_TimedGetByte();
			if (result < 0)
				goto done;
			result = GDBRemote_TimedGetByte();
			if (result < 0)
				goto done;
			printk(KERN_WARNING "[gdb] Unexpected command %$q received after transmitting packet %$q\n",
			       (size_t)(dst - GDBRemote_CommandBuffer), GDBRemote_CommandBuffer,
			       previous_packet_length_with_frame, GDBServer_PacketBuffer);
		} else {
			char resp[1];
			resp[0] = (char)result;
			printk(KERN_WARNING "[gdb] Unexpected response byte %$q received after transmitting packet %$q\n",
			       (size_t)1, resp, previous_packet_length_with_frame, GDBServer_PacketBuffer);
		}
	}
done:
	return result;
}

/* Calculate and return the checksum for the given memory block. */
INTERN ATTR_PURE WUNUSED NONNULL((1)) byte_t
NOTHROW(KCALL GDBPacket_GetCheckSum)(void const *__restrict buf, size_t buflen) {
	byte_t result;
	size_t i;
	for (result = 0, i = 0; i < buflen; ++i)
		result += ((byte_t *)buf)[i];
	return result;
}


PRIVATE size_t
NOTHROW(FCALL GDBPacket_TransmitAsync)(char *endptr, char firstChar) {
	byte_t checksum;
	size_t len;
	assert(endptr >= GDBServer_PacketBuffer + 1);
	assert(endptr <= (GDBServer_PacketBuffer + 1 + CONFIG_MODGDBSERVER_PACKET_MAXLEN));
	len = (size_t)(endptr - (GDBServer_PacketBuffer + 1));
	checksum = GDBPacket_GetCheckSum(GDBServer_PacketBuffer + 1, len);
	GDBServer_PacketBuffer[0]   = firstChar;
	((byte_t *)endptr)[0] = '#';
	((byte_t *)endptr)[1] = GDB_ToHex(checksum >> 4);
	((byte_t *)endptr)[2] = GDB_ToHex(checksum & 0x0f);
	COMPILER_WRITE_BARRIER();
	/* Send the packet */
	len += 4;
	GDB_DEBUG("[gdb] reply: %$q\n", len, GDBServer_PacketBuffer);
	GDBRemote_PutData(GDBServer_PacketBuffer, len);
	return len;
}


/* Max # of times to attempt to transmit a packet before giving up. */
INTERN unsigned int GDBPacket_RetryTransmitLimit = 4;

/* Transmit a packet ending at `endptr'
 * @return: true:  Packet successfully transmitted.
 * @return: false: Transmit failed (timeout, or `GDBPacket_RetryTransmitLimit' was exceeded) */
INTERN WUNUSED bool
NOTHROW(FCALL GDBPacket_Transmit)(char *endptr) {
	unsigned int retry_counter = 0;
	size_t len;
	int response;
	len = GDBPacket_TransmitAsync(endptr, '$');
	if (GDBServer_Features & GDB_SERVER_FEATURE_NOACK)
		return true; /* NOACK-mode */
wait_for_response:
	response = GDBPacket_WaitForResponse(len);
	if likely(response == '+')
		return true; /* ACK */
	if unlikely(response < 0)
		return false; /* Timeout... */
	/* NACK (try again a limited number of times) */
	if unlikely(retry_counter >= GDBPacket_RetryTransmitLimit)
		return false;
	/* Re-transmit the packet */
	++retry_counter;
	GDBRemote_PutData(GDBServer_PacketBuffer, len);
	goto wait_for_response;
}

/* Transmit a notification packet (same as `GDBPacket_Transmit()', but the first byte is `%' instead of `$') */
INTERN void
NOTHROW(FCALL GDBPacket_TransmitNotification)(char *endptr) {
	/* NOTE: We don't ever wait for ACK, since GDB's doc says that
	 *       notification   events  don't  ever  produce  +  or  - */
	GDBPacket_TransmitAsync(endptr, '%');
}


/* Escaping work by taking any `ch' for which `ESC_MUST(ch)' is true,
 * then  transmitting that character  as { ESC_BYTE,  ch ^ ESC_XMSK } */
#define ESC_BYTE     '}' /* Prefix for escape bytes */
#define ESC_XMSK     0x20 /* XOR Escaped bytes with this mask */
#define ESC_MUST(ch) ((ch) == '#' || (ch) == '$' || (ch) == '}' || (ch) == '*')

LOCAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) byte_t
NOTHROW(KCALL GDBPacket_GetCheckSumEscape)(void const *__restrict buf, size_t buflen) {
	byte_t result;
	size_t i;
	for (result = 0, i = 0; i < buflen; ++i) {
		char ch = ((char *)buf)[i];
		if (ESC_MUST(ch)) {
			result += (byte_t)ESC_BYTE;
			ch ^= ESC_XMSK;
		}
		result += (byte_t)ch;
	}
	return result;
}

PRIVATE void
NOTHROW(FCALL GDBRemote_PutDataEscape)(char *data, size_t datalen) {
	char *flush_start, *iter, *end;
	flush_start = data;
	iter = data + 1;
	end = data + datalen - 3;
	for (; iter < end; ++iter) {
		char esc[2], ch = *iter;
		if (!ESC_MUST(ch))
			continue;
		if (flush_start < iter)
			GDBRemote_PutData(flush_start, (size_t)(iter - flush_start));
		esc[0] = ESC_BYTE;
		esc[1] = ch ^ ESC_XMSK;
		GDBRemote_PutData(esc, 2);
		flush_start = iter + 1;
	}
	GDBRemote_PutData(flush_start, (size_t)(end - flush_start) + 3);
}

PRIVATE size_t
NOTHROW(FCALL GDBPacket_TransmitAsyncEscape)(char *endptr) {
	byte_t checksum;
	size_t len;
	assert(endptr >= GDBServer_PacketBuffer + 1);
	assert(endptr <= (GDBServer_PacketBuffer + 1 + CONFIG_MODGDBSERVER_PACKET_MAXLEN));
	len = (size_t)(endptr - (GDBServer_PacketBuffer + 1));
	checksum = GDBPacket_GetCheckSumEscape(GDBServer_PacketBuffer + 1, len);
	GDB_DEBUG("[gdb] reply: %$q\n", len, GDBServer_PacketBuffer + 1);
	GDBServer_PacketBuffer[0]  = '$';
	((byte_t *)endptr)[0] = '#';
	((byte_t *)endptr)[1] = GDB_ToHex(checksum >> 4);
	((byte_t *)endptr)[2] = GDB_ToHex(checksum & 0x0f);
	COMPILER_WRITE_BARRIER();
	/* Send the packet */
	len += 4;
	GDBRemote_PutDataEscape(GDBServer_PacketBuffer, len);
	return len;
}


/* Same as `GDBPacket_Transmit()', but escape special characters in the response string.
 * This is used to implement the transmission of raw binary data. */
INTERN WUNUSED bool
NOTHROW(FCALL GDBPacket_TransmitEscape)(char *endptr) {
	unsigned int retry_counter = 0;
	size_t len;
	int response;
	len = GDBPacket_TransmitAsyncEscape(endptr);
	if (GDBServer_Features & GDB_SERVER_FEATURE_NOACK)
		return true; /* NOACK-mode */
wait_for_response:
	response = GDBPacket_WaitForResponse(len);
	if likely(response == '+')
		return true; /* ACK */
	if unlikely(response < 0)
		return false; /* Timeout... */
	/* NACK (try again a limited number of times) */
	if unlikely(retry_counter >= GDBPacket_RetryTransmitLimit)
		return false;
	/* Re-transmit the packet */
	++retry_counter;
	GDBRemote_PutDataEscape(GDBServer_PacketBuffer, len);
	goto wait_for_response;
}



INTERN WUNUSED bool
NOTHROW(FCALL GDBPacket_SendEmpty)(void) {
	char *ptr = GDBPacket_Start();
	return GDBPacket_Transmit(ptr);
}

INTERN WUNUSED bool
NOTHROW(FCALL GDBPacket_Send)(char const *__restrict text) {
	char *ptr = GDBPacket_Start();
	ptr = stpcpy(ptr, text);
	return GDBPacket_Transmit(ptr);
}

INTERN WUNUSED bool
NOTHROW(FCALL GDBPacket_SendError)(u8 error_code) {
	char *ptr = GDBPacket_Start();
	*ptr++ = 'E';
	*ptr++ = GDB_ToHex(error_code >> 4);
	*ptr++ = GDB_ToHex(error_code & 0xf);
	return GDBPacket_Transmit(ptr);
}

INTERN WUNUSED bool
NOTHROW(VCALL GDBPacket_Sendf)(char const *__restrict format, ...) {
	bool result;
	va_list args;
	va_start(args, format);
	result = GDBPacket_VSendf(format, args);
	va_end(args);
	return result;
}

INTERN WUNUSED bool
NOTHROW(FCALL GDBPacket_VSendf)(char const *__restrict format, va_list args) {
	char *ptr = GDBPacket_Start();
	ptr += vsprintf(ptr, format, args);
	return GDBPacket_Transmit(ptr);
}



DECL_END

#endif /* !GUARD_MODGDBSERVER_PACKET_C */
