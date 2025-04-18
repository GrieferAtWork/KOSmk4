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
#ifndef GUARD_MODGDBSERVER_MEMORY_C
#define GUARD_MODGDBSERVER_MEMORY_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/mman.h>
#include <kernel/mman/rw.h>
#include <sched/task.h>

#include <assert.h>
#include <string.h>

#include "gdb.h"
#include "server.h" /* CONFIG_MODGDBSERVER_PACKET_MAXLEN, GDBPacket_Start() */

DECL_BEGIN

/* Read/Write memory
 * WARNING: `GDB_WriteMemory()' and `GDB_MMan_WriteMemory()' may modify the contents of the given `buf'!
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transferred.
 *              The affected memory ranges are:
 *               - `addr + num_bytes - return ... addr + num_bytes - 1'
 *               - `buf + num_bytes - return ... buf + num_bytes - 1' */
INTERN NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_ReadMemory)(struct task *__restrict thread,
                              VIRT void const *addr, void *buf, size_t num_bytes) {
	size_t result;
	if (ADDR_ISKERN(addr)) {
		result = GDB_MMan_ReadMemory(&mman_kernel, addr, buf, num_bytes);
	} else {
		REF struct mman *effective_mm;
		effective_mm = task_getmman(thread);
		result = GDB_MMan_ReadMemory(effective_mm, addr, buf, num_bytes);
		decref_unlikely(effective_mm);
	}
	return result;
}

INTERN NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_WriteMemory)(struct task *__restrict thread,
                               VIRT void *addr, void *buf, size_t num_bytes) {
	size_t result;
	if (ADDR_ISKERN(addr)) {
		result = GDB_MMan_WriteMemory(&mman_kernel, addr, buf, num_bytes);
	} else {
		REF struct mman *effective_mm;
		effective_mm = task_getmman(thread);
		result = GDB_MMan_WriteMemory(effective_mm, addr, buf, num_bytes);
		decref_unlikely(effective_mm);
	}
	return result;
}

INTERN NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_ReadMemoryWithoutSwBreak)(struct task *__restrict thread,
                                            VIRT void const *addr,
                                            void *buf, size_t num_bytes) {
	size_t result;
	if (ADDR_ISKERN(addr)) {
		result = GDB_MMan_ReadMemoryWithoutSwBreak(&mman_kernel, addr, buf, num_bytes);
	} else {
		REF struct mman *effective_mm;
		effective_mm = task_getmman(thread);
		result = GDB_MMan_ReadMemoryWithoutSwBreak(effective_mm, addr, buf, num_bytes);
		decref_unlikely(effective_mm);
	}
	return result;
}

INTERN NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_WriteMemoryWithoutSwBreak)(struct task *__restrict thread,
                                             VIRT void *addr,
                                             void const *buf, size_t num_bytes) {
	size_t result;
	if (ADDR_ISKERN(addr)) {
		result = GDB_MMan_WriteMemoryWithoutSwBreak(&mman_kernel, addr, buf, num_bytes);
	} else {
		REF struct mman *effective_mm;
		effective_mm = task_getmman(thread);
		result = GDB_MMan_WriteMemoryWithoutSwBreak(effective_mm, addr, buf, num_bytes);
		decref_unlikely(effective_mm);
	}
	return result;
}

INTERN NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_MMan_ReadMemory)(struct mman *__restrict effective_mm,
                                   VIRT void const *addr,
                                   void *buf, size_t num_bytes) {
	size_t result;
	result = GDB_MMan_ReadMemoryWithoutSwBreak(effective_mm, addr, buf, num_bytes);
	GDB_ExcludeSwBreak(effective_mm, addr, buf, num_bytes - __builtin_expect(result, 0));
	return result;
}

INTERN NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_MMan_WriteMemory)(struct mman *__restrict effective_mm,
                                  VIRT void *addr, void *buf, size_t num_bytes) {
	size_t result;
	GDB_IncludeSwBreak(effective_mm, addr, buf, num_bytes);
	result = GDB_MMan_WriteMemoryWithoutSwBreak(effective_mm, addr, buf, num_bytes);
	return result;
}

INTERN NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_MMan_ReadMemoryWithoutSwBreak)(struct mman *__restrict effective_mm,
                                                 VIRT void const *addr, void *buf, size_t num_bytes) {
	size_t result;
	result = mman_read_nopf(effective_mm, (void const *)addr, buf, num_bytes);
	if (result) {
		TRY {
			/* TODO: mman_read()  may invoke RPC callbacks, which may
			 *       in turn throw exceptions such as `E_EXIT_THREAD' */
			mman_read(effective_mm, (void const *)addr, buf, num_bytes, true);
			result = 0;
		} EXCEPT {
		}
	}
	return result;
}

INTERN NONNULL((1, 3)) size_t
NOTHROW(FCALL GDB_MMan_WriteMemoryWithoutSwBreak)(struct mman *__restrict effective_mm,
                                                VIRT void *addr, void const *buf, size_t num_bytes) {
	size_t result;
	result = mman_write_nopf(effective_mm, (void *)addr, buf, num_bytes);
	if (result) {
		TRY {
			/* TODO: mman_write() may invoke RPC callbacks, which may
			 *       in turn throw exceptions such as `E_EXIT_THREAD' */
			mman_write(effective_mm, (void *)addr, buf, num_bytes, true);
			result = 0;
		} EXCEPT {
		}
	}
	return result;
}



/* Search memory for a specific need
 * This function behaves identical to `memmem()'
 * @return: true:  Found the needle at `*presult'
 * @return: false: The needle wasn't found. */
INTERN NONNULL((1, 4)) bool
NOTHROW(FCALL GDB_FindMemory)(struct task *__restrict thread,
                              VIRT void const *haystack, size_t haystack_length,
                              void const *needle, size_t needle_length,
                              VIRT void const **__restrict presult) {
	/* Since the length  of `needle' is  restricted by  the max length  of a  packet,
	 * we can assume that `needle_length < CONFIG_MODGDBSERVER_PACKET_MAXLEN / 2', as
	 * well as that  we are free  to use `GDBPacket_Start()'  as a temporary  buffer. */
	byte_t *buf;
	byte_t firstbyte;
	assert(needle_length < CONFIG_MODGDBSERVER_PACKET_MAXLEN / 2);
	if unlikely(!needle_length) {
		*presult = haystack;
		return true;
	}
	buf = (byte_t *)GDBPacket_Start();
	firstbyte = ((byte_t *)needle)[0];
	for (;;) {
		size_t maxcount, realcount;
		if (needle_length > haystack_length)
			break;
		maxcount = CONFIG_MODGDBSERVER_PACKET_MAXLEN;
		if (maxcount > haystack_length)
			maxcount = haystack_length;
		realcount = maxcount;
		realcount -= GDB_ReadMemory(thread, haystack, buf, maxcount);
		if likely(realcount >= needle_length) {
			/* Scan `buf...+=realcount' for the needle */
			byte_t *pos, *end;
			size_t avail;
			pos   = buf;
			end   = buf + realcount;
continue_scanning:
			avail = (size_t)(end - pos);
			for (;;) {
				pos = (byte_t *)memchr(pos, firstbyte, avail);
				if (!pos)
					break;
				/* Check if the needle would already be fully contained in the buffer. */
				avail = (size_t)(end - pos);
				if (avail >= needle_length) {
					/* If this _is_ the match, then we've already got all the data we need. */
					if (bcmp(pos + 1, (byte_t *)needle + 1, needle_length - 1) != 0) {
						/* Continue searching... */
						++pos;
						--avail;
						continue;
					}
found_it_at_pos:
					/* Found it! */
					*presult = (byte_t *)haystack + (size_t)(pos - buf);
					return true;
				} else {
					size_t missing_bytes;
					/* We may still have a partial match that may
					 * cross  over into the next block of memory. */
					if (bcmp(pos + 1, (byte_t *)needle + 1, avail - 1) != 0) {
						/* Not this one... */
						++pos;
						--avail;
						continue;
					}
					/* All the data we have right now indicate that  this
					 * can still be  the match we're  looking for,  since
					 * the following (but incomplete) range _does_ match:
					 * >> haystack + (size_t)(pos - buf)...+=avail
					 * Same as:
					 * >> needle...+=avail
					 * Since  we're allowed  to assume  that our  buffer is always
					 * at least as large as a max-sized needle, we can also assume
					 * that reading the next block of memory will yield all of the
					 * remaining data left to-be matched. */
					missing_bytes = needle_length - avail;
					haystack = (VIRT byte_t const *)haystack + maxcount;
					haystack_length -= maxcount;
					if (missing_bytes > haystack_length)
						goto not_found;
					maxcount = CONFIG_MODGDBSERVER_PACKET_MAXLEN;
					if (maxcount > haystack_length)
						maxcount = haystack_length;
					realcount = maxcount;
					realcount -= GDB_ReadMemory(thread, haystack, buf, maxcount);
					if unlikely(realcount < missing_bytes)
						goto advance_to_next_haystack;
					/* Compare the remaining data. */
					if (bcmp(buf, (byte_t *)needle + avail, missing_bytes) == 0)
						goto found_it_at_pos; /* Found it! (as `haystack + (size_t)(pos - buf)') */
					pos = buf + missing_bytes;
					end = buf + realcount;
					goto continue_scanning;
				}
			}
		}
advance_to_next_haystack:
		if (maxcount >= haystack_length)
			break;
		haystack = (VIRT byte_t const *)haystack + maxcount;
		haystack_length -= maxcount;
	}
not_found:
	return false;
}

/* See `memory-crc32.c' for the implementation. */
INTDEF u32 FCALL libiberty_xcrc32(byte_t const *buf, size_t len, u32 crc);

/* Calculate  the CRC32  checksum for  the given  region of memory.
 * If access to anything with the given range fail, return `false'.
 * Otherwise, return `true' and store  the CRC value in  `*presult' */
INTERN NONNULL((1, 4)) bool
NOTHROW(FCALL GDB_CalculateCRC32)(struct task *__restrict thread,
                                  VIRT void const *addr, size_t length,
                                  u32 *__restrict presult) {
	u32 result = 0xffffffff;
	if likely(length != 0) {
		byte_t *buf;
		buf = (byte_t *)GDBPacket_Start();
		for (;;) {
			size_t maxlen = length;
			if (maxlen > CONFIG_MODGDBSERVER_PACKET_MAXLEN)
				maxlen = CONFIG_MODGDBSERVER_PACKET_MAXLEN;
			if (!GDB_ReadMemory(thread, addr, buf, maxlen))
				return false;
			result = libiberty_xcrc32(buf, maxlen, result);
			if (maxlen >= length)
				break;
			length -= maxlen;
			addr = (VIRT byte_t const *)addr + maxlen;
		}
	}
	*presult = result;
	return true;
}


DECL_END

#endif /* !GUARD_MODGDBSERVER_MEMORY_C */
