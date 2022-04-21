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
#ifndef GUARD_KERNEL_SRC_DEV_MOUSE_C
#define GUARD_KERNEL_SRC_DEV_MOUSE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/mouse.h>
#include <kernel/except.h>
#include <kernel/panic.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>
#include <hybrid/sched/preemption.h>

#include <kos/except/reason/inval.h>
#include <sys/stat.h>

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN


PUBLIC NOBLOCK NOPREEMPT bool
NOTHROW(KCALL mouse_buffer_putpacket_nopr)(struct mousebuf *__restrict self,
                                           mouse_packet_t packet) {
	union mousebuf_state oldstate, newstate;
	assert(!preemption_ison());
	assert(packet.mp_type != MOUSE_PACKET_TYPE_NONE);
	for (;;) {
		size_t index;
		oldstate.bs_word = ATOMIC_READ(self->mb_bufstate.bs_word);
		if (oldstate.bs_state.s_used >= CONFIG_MOUSE_BUFFER_SIZE)
			return false;
		index = (oldstate.bs_state.s_start +
		         oldstate.bs_state.s_used) %
		        CONFIG_MOUSE_BUFFER_SIZE;
		if (!ATOMIC_CMPXCH_WEAK(self->mb_buffer[index].mp_word, 0, packet.mp_word))
			continue;
		newstate = oldstate;
		++newstate.bs_state.s_used;
		if (ATOMIC_CMPXCH_WEAK(self->mb_bufstate.bs_word,
		                       oldstate.bs_word,
		                       newstate.bs_word))
			break;
#ifdef NDEBUG
		ATOMIC_WRITE(self->mb_buffer[index].mp_word, 0);
#else /* NDEBUG */
		{
			mouse_packet_t oldpacket;
			oldpacket.mp_word = ATOMIC_XCH(self->mb_buffer[index].mp_word, 0);
			assert(oldpacket.mp_word == packet.mp_word);
		}
#endif /* !NDEBUG */
	}
	/* Send the signal for every packet enqueued. */
	sig_send_nopr(&self->mb_avail);
	return true;
}

PUBLIC NOBLOCK bool
NOTHROW(KCALL mouse_buffer_putpackets_nopr)(struct mousebuf *__restrict self,
                                            mouse_packet_t *__restrict packetv,
                                            uintptr_half_t packetc) {
	union mousebuf_state oldstate, newstate;
	assert(packetc != 0);
	assert(packetc <= MOUSE_PACKET_SEQMAX);
	assert(!preemption_ison());
	assert(packetv[0].mp_type != MOUSE_PACKET_TYPE_NONE);
	for (;;) {
		size_t i, index;
		oldstate.bs_word = ATOMIC_READ(self->mb_bufstate.bs_word);
		if ((oldstate.bs_state.s_used + packetc) > CONFIG_MOUSE_BUFFER_SIZE)
			return false;
		for (i = 0; i < packetc; ++i) {
			index = (oldstate.bs_state.s_start + oldstate.bs_state.s_used + i) % CONFIG_MOUSE_BUFFER_SIZE;
			if (!ATOMIC_CMPXCH(self->mb_buffer[index].mp_word, 0, packetv[i].mp_word)) {
				while (i--) {
					index = (oldstate.bs_state.s_start + oldstate.bs_state.s_used + i) % CONFIG_MOUSE_BUFFER_SIZE;
#ifdef NDEBUG
					ATOMIC_WRITE(self->mb_buffer[index].mp_word, 0);
#else /* NDEBUG */
					{
						mouse_packet_t oldpacket;
						oldpacket.mp_word = ATOMIC_XCH(self->mb_buffer[index].mp_word, 0);
						assert(oldpacket.mp_word == packetv[i].mp_word);
					}
#endif /* !NDEBUG */
				}
				continue;
			}
		}
		newstate = oldstate;
		newstate.bs_state.s_used += packetc;
		if (ATOMIC_CMPXCH_WEAK(self->mb_bufstate.bs_word,
		                       oldstate.bs_word,
		                       newstate.bs_word))
			break;
		i = packetc;
		while (i--) {
			index = (oldstate.bs_state.s_start + oldstate.bs_state.s_used + i) % CONFIG_MOUSE_BUFFER_SIZE;
#ifdef NDEBUG
			ATOMIC_WRITE(self->mb_buffer[index].mp_word, 0);
#else /* NDEBUG */
			{
				mouse_packet_t oldpacket;
				oldpacket.mp_word = ATOMIC_XCH(self->mb_buffer[index].mp_word, 0);
				assert(oldpacket.mp_word == packetv[i].mp_word);
			}
#endif /* !NDEBUG */
		}
	}
	/* Send the signal for every packet enqueued. */
	sig_sendmany(&self->mb_avail, packetc);
	return true;
}


#define INT30_MIN (-(1 << 29))
#define INT30_MAX ((1 << 29) - 1)
#define INT24_MIN (-(1 << 23))
#define INT24_MAX ((1 << 23) - 1)
#define INT18_MIN (-(1 << 17))
#define INT18_MAX ((1 << 17) - 1)
#define INT12_MIN (-(1 << 11))
#define INT12_MAX ((1 << 11) - 1)
#define INT6_MIN  (-(1 << 5))
#define INT6_MAX  ((1 << 5) - 1)

STATIC_ASSERT((int32_t)INT24_MIN == (int32_t)0xff800000);
STATIC_ASSERT((int32_t)INT24_MAX == (int32_t)0x007fffff);
STATIC_ASSERT((int32_t)INT12_MIN == (int32_t)0xfffff800);
STATIC_ASSERT((int32_t)INT12_MAX == (int32_t)0x000007ff);
STATIC_ASSERT((int32_t)INT6_MIN  == (int32_t)0xffffffe0);
STATIC_ASSERT((int32_t)INT6_MAX  == (int32_t)0x0000001f);

PRIVATE NOBLOCK bool
NOTHROW(KCALL mouse_device_do_post_s32s32s32s32)(struct mousedev *__restrict self,
                                                 unsigned int type,
                                                 s32 data1, s32 data2,
                                                 s32 data3, s32 data4) {
	assert(MOUSE_PACKET_TYPE_IS4FIELD(type));
	if ((data1 >= INT6_MIN && data1 <= INT6_MAX) &&
	    (data2 >= INT6_MIN && data2 <= INT6_MAX) &&
	    (data3 >= INT6_MIN && data3 <= INT6_MAX) &&
	    (data4 >= INT6_MIN && data4 <= INT6_MAX)) {
		mouse_packet_t packet;
		/* Single packet. */
		packet.mp_type                  = type;
		packet.mp_seqnum                = 0;
		packet.mp_data.md_moved.mm_posx = data1;
		packet.mp_data.md_moved.mm_posy = data2;
		packet.mp_data.md_moved.mm_relx = data3;
		packet.mp_data.md_moved.mm_rely = data4;
		return mouse_buffer_putpacket_nopr(&self->md_buf, packet);
	}
	if ((data1 >= INT12_MIN && data1 <= INT12_MAX) &&
	    (data2 >= INT12_MIN && data2 <= INT12_MAX) &&
	    (data3 >= INT12_MIN && data3 <= INT12_MAX) &&
	    (data4 >= INT12_MIN && data4 <= INT12_MAX)) {
		mouse_packet_t packet[2];
		/* 2 packets. */
		packet[0].mp_type                   = type;
		packet[0].mp_seqnum                 = 1;
		packet[0].mp_data.md_moved.mm_posx  = ((s32)data1 & 0xfc0) >> 6;
		packet[0].mp_data.md_moved.mm_posy  = ((s32)data2 & 0xfc0) >> 6;
		packet[0].mp_data.md_moved.mm_relx  = ((s32)data3 & 0xfc0) >> 6;
		packet[0].mp_data.md_moved.mm_rely  = ((s32)data4 & 0xfc0) >> 6;
		packet[1].mp_type                   = type;
		packet[1].mp_seqnum                 = 0;
		packet[1].mp_data.md_moved.mm_posx  = (s32)data1 & 0x3f;
		packet[1].mp_data.md_moved.mm_posy  = (s32)data2 & 0x3f;
		packet[1].mp_data.md_moved.mm_relx  = (s32)data3 & 0x3f;
		packet[1].mp_data.md_moved.mm_rely  = (s32)data4 & 0x3f;
		return mouse_buffer_putpackets_nopr(&self->md_buf, packet, 2);
	}
	if ((data1 >= INT18_MIN && data1 <= INT18_MAX) &&
	    (data2 >= INT18_MIN && data2 <= INT18_MAX) &&
	    (data3 >= INT18_MIN && data3 <= INT18_MAX) &&
	    (data4 >= INT18_MIN && data4 <= INT18_MAX)) {
		mouse_packet_t packet[3];
		/* 3 packets. */
		packet[0].mp_type                   = type;
		packet[0].mp_seqnum                 = 2;
		packet[0].mp_data.md_moved.mm_posx  = ((s32)data1 & 0x3f000) >> 12;
		packet[0].mp_data.md_moved.mm_posy  = ((s32)data2 & 0x3f000) >> 12;
		packet[0].mp_data.md_moved.mm_relx  = ((s32)data3 & 0x3f000) >> 12;
		packet[0].mp_data.md_moved.mm_rely  = ((s32)data4 & 0x3f000) >> 12;
		packet[1].mp_type                   = type;
		packet[1].mp_seqnum                 = 1;
		packet[1].mp_data.md_moved.mm_posx  = ((s32)data1 & 0xfc0) >> 6;
		packet[1].mp_data.md_moved.mm_posy  = ((s32)data2 & 0xfc0) >> 6;
		packet[1].mp_data.md_moved.mm_relx  = ((s32)data3 & 0xfc0) >> 6;
		packet[1].mp_data.md_moved.mm_rely  = ((s32)data4 & 0xfc0) >> 6;
		packet[2].mp_type                   = type;
		packet[2].mp_seqnum                 = 0;
		packet[2].mp_data.md_moved.mm_posx  = (s32)data1 & 0x3f;
		packet[2].mp_data.md_moved.mm_posy  = (s32)data2 & 0x3f;
		packet[2].mp_data.md_moved.mm_relx  = (s32)data3 & 0x3f;
		packet[2].mp_data.md_moved.mm_rely  = (s32)data4 & 0x3f;
		return mouse_buffer_putpackets_nopr(&self->md_buf, packet, 3);
	}
	if ((data1 >= INT24_MIN && data1 <= INT24_MAX) &&
	    (data2 >= INT24_MIN && data2 <= INT24_MAX) &&
	    (data3 >= INT24_MIN && data3 <= INT24_MAX) &&
	    (data4 >= INT24_MIN && data4 <= INT24_MAX)) {
		mouse_packet_t packet[4];
		/* 4 packets. */
		packet[0].mp_type                   = type;
		packet[0].mp_seqnum                 = 3;
		packet[0].mp_data.md_moved.mm_posx  = ((s32)data1 & 0xfc0000) >> 18;
		packet[0].mp_data.md_moved.mm_posy  = ((s32)data2 & 0xfc0000) >> 18;
		packet[0].mp_data.md_moved.mm_relx  = ((s32)data3 & 0xfc0000) >> 18;
		packet[0].mp_data.md_moved.mm_rely  = ((s32)data4 & 0xfc0000) >> 18;
		packet[1].mp_type                   = type;
		packet[1].mp_seqnum                 = 2;
		packet[1].mp_data.md_moved.mm_posx  = ((s32)data1 & 0x3f000) >> 12;
		packet[1].mp_data.md_moved.mm_posy  = ((s32)data2 & 0x3f000) >> 12;
		packet[1].mp_data.md_moved.mm_relx  = ((s32)data3 & 0x3f000) >> 12;
		packet[1].mp_data.md_moved.mm_rely  = ((s32)data4 & 0x3f000) >> 12;
		packet[2].mp_type                   = type;
		packet[2].mp_seqnum                 = 1;
		packet[2].mp_data.md_moved.mm_posx  = ((s32)data1 & 0xfc0) >> 6;
		packet[2].mp_data.md_moved.mm_posy  = ((s32)data2 & 0xfc0) >> 6;
		packet[2].mp_data.md_moved.mm_relx  = ((s32)data3 & 0xfc0) >> 6;
		packet[2].mp_data.md_moved.mm_rely  = ((s32)data4 & 0xfc0) >> 6;
		packet[3].mp_type                   = type;
		packet[3].mp_seqnum                 = 0;
		packet[3].mp_data.md_moved.mm_posx  = (s32)data1 & 0x3f;
		packet[3].mp_data.md_moved.mm_posy  = (s32)data2 & 0x3f;
		packet[3].mp_data.md_moved.mm_relx  = (s32)data3 & 0x3f;
		packet[3].mp_data.md_moved.mm_rely  = (s32)data4 & 0x3f;
		return mouse_buffer_putpackets_nopr(&self->md_buf, packet, 4);
	}
	if ((data1 >= INT30_MIN && data1 <= INT30_MAX) &&
	    (data2 >= INT30_MIN && data2 <= INT30_MAX) &&
	    (data3 >= INT30_MIN && data3 <= INT30_MAX) &&
	    (data4 >= INT30_MIN && data4 <= INT30_MAX)) {
		mouse_packet_t packet[5];
		/* 5 packets. */
		packet[0].mp_type                   = type;
		packet[0].mp_seqnum                 = 4;
		packet[0].mp_data.md_moved.mm_posx  = ((s32)data1 & 0x3f000000) >> 24;
		packet[0].mp_data.md_moved.mm_posy  = ((s32)data2 & 0x3f000000) >> 24;
		packet[0].mp_data.md_moved.mm_relx  = ((s32)data3 & 0x3f000000) >> 24;
		packet[0].mp_data.md_moved.mm_rely  = ((s32)data4 & 0x3f000000) >> 24;
		packet[1].mp_type                   = type;
		packet[1].mp_seqnum                 = 3;
		packet[1].mp_data.md_moved.mm_posx  = ((s32)data1 & 0xfc0000) >> 18;
		packet[1].mp_data.md_moved.mm_posy  = ((s32)data2 & 0xfc0000) >> 18;
		packet[1].mp_data.md_moved.mm_relx  = ((s32)data3 & 0xfc0000) >> 18;
		packet[1].mp_data.md_moved.mm_rely  = ((s32)data4 & 0xfc0000) >> 18;
		packet[2].mp_type                   = type;
		packet[2].mp_seqnum                 = 2;
		packet[2].mp_data.md_moved.mm_posx  = ((s32)data1 & 0x3f000) >> 12;
		packet[2].mp_data.md_moved.mm_posy  = ((s32)data2 & 0x3f000) >> 12;
		packet[2].mp_data.md_moved.mm_relx  = ((s32)data3 & 0x3f000) >> 12;
		packet[2].mp_data.md_moved.mm_rely  = ((s32)data4 & 0x3f000) >> 12;
		packet[3].mp_type                   = type;
		packet[3].mp_seqnum                 = 1;
		packet[3].mp_data.md_moved.mm_posx  = ((s32)data1 & 0xfc0) >> 6;
		packet[3].mp_data.md_moved.mm_posy  = ((s32)data2 & 0xfc0) >> 6;
		packet[3].mp_data.md_moved.mm_relx  = ((s32)data3 & 0xfc0) >> 6;
		packet[3].mp_data.md_moved.mm_rely  = ((s32)data4 & 0xfc0) >> 6;
		packet[4].mp_type                   = type;
		packet[4].mp_seqnum                 = 0;
		packet[4].mp_data.md_moved.mm_posx  = (s32)data1 & 0x3f;
		packet[4].mp_data.md_moved.mm_posy  = (s32)data2 & 0x3f;
		packet[4].mp_data.md_moved.mm_relx  = (s32)data3 & 0x3f;
		packet[4].mp_data.md_moved.mm_rely  = (s32)data4 & 0x3f;
		return mouse_buffer_putpackets_nopr(&self->md_buf, packet, 5);
	}
	{
		mouse_packet_t packet[6];
		/* 6 packets. */
		packet[0].mp_type                   = type;
		packet[0].mp_seqnum                 = 5;
		packet[0].mp_data.md_moved.mm_posx  = ((s32)data1 & 0xc0000000) >> 30;
		packet[0].mp_data.md_moved.mm_posy  = ((s32)data2 & 0xc0000000) >> 30;
		packet[0].mp_data.md_moved.mm_relx  = ((s32)data3 & 0xc0000000) >> 30;
		packet[0].mp_data.md_moved.mm_rely  = ((s32)data4 & 0xc0000000) >> 30;
		packet[1].mp_type                   = type;
		packet[1].mp_seqnum                 = 4;
		packet[1].mp_data.md_moved.mm_posx  = ((s32)data1 & 0x3f000000) >> 24;
		packet[1].mp_data.md_moved.mm_posy  = ((s32)data2 & 0x3f000000) >> 24;
		packet[1].mp_data.md_moved.mm_relx  = ((s32)data3 & 0x3f000000) >> 24;
		packet[1].mp_data.md_moved.mm_rely  = ((s32)data4 & 0x3f000000) >> 24;
		packet[2].mp_type                   = type;
		packet[2].mp_seqnum                 = 3;
		packet[2].mp_data.md_moved.mm_posx  = ((s32)data1 & 0xfc0000) >> 18;
		packet[2].mp_data.md_moved.mm_posy  = ((s32)data2 & 0xfc0000) >> 18;
		packet[2].mp_data.md_moved.mm_relx  = ((s32)data3 & 0xfc0000) >> 18;
		packet[2].mp_data.md_moved.mm_rely  = ((s32)data4 & 0xfc0000) >> 18;
		packet[3].mp_type                   = type;
		packet[3].mp_seqnum                 = 2;
		packet[3].mp_data.md_moved.mm_posx  = ((s32)data1 & 0x3f000) >> 12;
		packet[3].mp_data.md_moved.mm_posy  = ((s32)data2 & 0x3f000) >> 12;
		packet[3].mp_data.md_moved.mm_relx  = ((s32)data3 & 0x3f000) >> 12;
		packet[3].mp_data.md_moved.mm_rely  = ((s32)data4 & 0x3f000) >> 12;
		packet[4].mp_type                   = type;
		packet[4].mp_seqnum                 = 1;
		packet[4].mp_data.md_moved.mm_posx  = ((s32)data1 & 0xfc0) >> 6;
		packet[4].mp_data.md_moved.mm_posy  = ((s32)data2 & 0xfc0) >> 6;
		packet[4].mp_data.md_moved.mm_relx  = ((s32)data3 & 0xfc0) >> 6;
		packet[4].mp_data.md_moved.mm_rely  = ((s32)data4 & 0xfc0) >> 6;
		packet[5].mp_type                   = type;
		packet[5].mp_seqnum                 = 0;
		packet[5].mp_data.md_moved.mm_posx  = (s32)data1 & 0x3f;
		packet[5].mp_data.md_moved.mm_posy  = (s32)data2 & 0x3f;
		packet[5].mp_data.md_moved.mm_relx  = (s32)data3 & 0x3f;
		packet[5].mp_data.md_moved.mm_rely  = (s32)data4 & 0x3f;
		return mouse_buffer_putpackets_nopr(&self->md_buf, packet, 6);
	}
}

PRIVATE NOBLOCK bool
NOTHROW(KCALL mouse_device_do_post_s32s32)(struct mousedev *__restrict self,
                                           unsigned int type, s32 data1, s32 data2) {
	assert(!MOUSE_PACKET_TYPE_IS4FIELD(type));
	if ((data1 >= INT12_MIN && data1 <= INT12_MAX) &&
	    (data2 >= INT12_MIN && data2 <= INT12_MAX)) {
		mouse_packet_t packet;
		/* Single packet. */
		packet.mp_type                   = type;
		packet.mp_seqnum                 = 0;
		packet.mp_data.md_motion.mm_relx = data1;
		packet.mp_data.md_motion.mm_rely = data2;
		return mouse_buffer_putpacket_nopr(&self->md_buf, packet);
	}
	if ((data1 >= INT24_MIN && data1 <= INT24_MAX) &&
	    (data2 >= INT24_MIN && data2 <= INT24_MAX)) {
		mouse_packet_t packet[2];
		/* 2 packets. */
		packet[0].mp_type                   = type;
		packet[0].mp_seqnum                 = 1;
		packet[0].mp_data.md_motion.mm_relx = ((s32)data1 & 0xfff000) >> 12;
		packet[0].mp_data.md_motion.mm_rely = ((s32)data2 & 0xfff000) >> 12;
		packet[1].mp_type                   = type;
		packet[1].mp_seqnum                 = 0;
		packet[1].mp_data.md_motion.mm_relx = (s32)data1 & 0xfff;
		packet[1].mp_data.md_motion.mm_rely = (s32)data2 & 0xfff;
		return mouse_buffer_putpackets_nopr(&self->md_buf, packet, 2);
	}
	{
		mouse_packet_t packet[3];
		/* 3 packets. */
		packet[0].mp_type                   = type;
		packet[0].mp_seqnum                 = 2;
		packet[0].mp_data.md_motion.mm_relx = ((s32)data1 & 0xfff000000) >> 24;
		packet[0].mp_data.md_motion.mm_rely = ((s32)data2 & 0xfff000000) >> 24;
		packet[1].mp_type                   = type;
		packet[1].mp_seqnum                 = 1;
		packet[1].mp_data.md_motion.mm_relx = ((s32)data1 & 0xfff000) >> 12;
		packet[1].mp_data.md_motion.mm_rely = ((s32)data2 & 0xfff000) >> 12;
		packet[2].mp_type                   = type;
		packet[2].mp_seqnum                 = 0;
		packet[2].mp_data.md_motion.mm_relx = (s32)data1 & 0xfff;
		packet[2].mp_data.md_motion.mm_rely = (s32)data2 & 0xfff;
		return mouse_buffer_putpackets_nopr(&self->md_buf, packet, 3);
	}
}

PRIVATE NOBLOCK bool
NOTHROW(KCALL mouse_device_do_motion_nopr_locked)(struct mousedev *__restrict self,
                                                  s32 relx, s32 rely) {
	bool result;
	s32 new_absx, new_absy;
	if (OVERFLOW_SADD(self->md_state.ms_abs_x, relx, &new_absx)) {
		new_absx = relx < 0 ? self->md_rect.mr_minx
		                    : self->md_rect.mr_maxx;
	} else {
		if (new_absx < self->md_rect.mr_minx)
			new_absx = self->md_rect.mr_minx;
		else if (new_absx > self->md_rect.mr_maxx)
			new_absx = self->md_rect.mr_maxx;
	}
	if (OVERFLOW_SADD(self->md_state.ms_abs_y, rely, &new_absy)) {
		new_absy = rely < 0 ? self->md_rect.mr_miny
		                    : self->md_rect.mr_maxy;
	} else {
		if (new_absy < self->md_rect.mr_miny)
			new_absy = self->md_rect.mr_miny;
		else if (new_absy > self->md_rect.mr_maxy)
			new_absy = self->md_rect.mr_maxy;
	}
	if (self->md_flags & MOUSE_DEVICE_FLAG_GENABS) {
		result = mouse_device_do_post_s32s32s32s32(self, MOUSE_PACKET_TYPE_MOVED,
		                                           relx, rely, new_absx, new_absy);
	} else {
		result = mouse_device_do_post_s32s32(self, MOUSE_PACKET_TYPE_MOTION, relx, rely);
	}
	if likely(result) {
		self->md_state.ms_abs_x = new_absx;
		self->md_state.ms_abs_y = new_absy;
	}
	return result;
}

PRIVATE NOBLOCK bool
NOTHROW(KCALL mouse_device_do_button_nopr_locked)(struct mousedev *__restrict self,
                                                  u32 new_buttons) {
	bool result;
	result = mouse_device_do_post_s32s32(self,
	                                     MOUSE_PACKET_TYPE_BUTTON,
	                                     new_buttons,
	                                     new_buttons ^ self->md_state.ms_buttons);
	if likely(result)
		self->md_state.ms_buttons = new_buttons;
	return result;
}

PRIVATE NOBLOCK bool
NOTHROW(KCALL mouse_device_do_wheel_nopr_locked)(struct mousedev *__restrict self,
                                                 unsigned int type, s32 diff) {
	return mouse_device_do_post_s32s32(self, type, 0, diff);
}

PRIVATE NOBLOCK bool
NOTHROW(KCALL mouse_device_do_moveto_nopr_locked)(struct mousedev *__restrict self,
                                                  s32 absx, s32 absy) {
	return mouse_device_do_motion_nopr_locked(self,
	                                          absx - self->md_state.ms_abs_x,
	                                          absy - self->md_state.ms_abs_y);
}


/* Read packets from a given mouse device buffer. */
PUBLIC NONNULL((1)) NOBLOCK mouse_packet_t
NOTHROW(KCALL mousebuf_trygetpacket)(struct mousebuf *__restrict self) {
	mouse_packet_t result;
	for (;;) {
		union mousebuf_state oldstate, newstate;
		oldstate.bs_word = ATOMIC_READ(self->mb_bufstate.bs_word);
		if (oldstate.bs_state.s_used == 0) {
			result.mp_word = 0;
			break;
		}
		assert(oldstate.bs_state.s_start < CONFIG_MOUSE_BUFFER_SIZE);
		newstate = oldstate;
		++newstate.bs_state.s_start;
		--newstate.bs_state.s_used;
#if IS_POWER_OF_TWO(CONFIG_MOUSE_BUFFER_SIZE)
		newstate.bs_state.s_start &= CONFIG_MOUSE_BUFFER_SIZE - 1;
#else
		if (newstate.bs_state.s_start == CONFIG_MOUSE_BUFFER_SIZE)
			newstate.bs_state.s_start = 0;
#endif
		if (!ATOMIC_CMPXCH_WEAK(self->mb_bufstate.bs_word,
		                        oldstate.bs_word,
		                        newstate.bs_word))
			continue;
		result.mp_word = ATOMIC_XCH(self->mb_buffer[oldstate.bs_state.s_start].mp_word, 0);
		if likely(result.mp_word != 0) {
			assert(result.mp_type != MOUSE_PACKET_TYPE_NONE);
			break;
		}
	}
	return result;
}

PUBLIC NONNULL((1)) mouse_packet_t KCALL
mousebuf_getpacket(struct mousebuf *__restrict self) THROWS(E_WOULDBLOCK) {
	mouse_packet_t result;
	assert(!task_wasconnected());
	for (;;) {
		result = mousebuf_trygetpacket(self);
		if (result.mp_type != MOUSE_PACKET_TYPE_NONE)
			break;
		task_connect(&self->mb_avail);
		result = mousebuf_trygetpacket(self);
		if unlikely(result.mp_type != MOUSE_PACKET_TYPE_NONE) {
			task_disconnectall();
			break;
		}
		task_waitfor();
	}
	return result;
}


/* Generate mouse input packets
 * Note  that when generating event packets, the motion
 * packets should always be created before other events */
PUBLIC NONNULL((1)) bool KCALL
mousedev_motion(struct mousedev *__restrict self,
                s32 relx, s32 rely) {
	bool result;
	if (!relx && !rely)
		return true;
	mousedev_smplock_acquire(self);
	result = mouse_device_do_motion_nopr_locked(self, relx, rely);
	mousedev_smplock_release(self);
	return result;
}

PUBLIC NONNULL((1)) bool KCALL
mousedev_moveto(struct mousedev *__restrict self,
                    s32 absx, s32 absy) {
	bool result;
	mousedev_smplock_acquire(self);
	if (self->md_state.ms_abs_x == absx &&
	    self->md_state.ms_abs_y == absy) {
		result = true;
	} else {
		result = mouse_device_do_moveto_nopr_locked(self, absx, absy);
	}
	mousedev_smplock_release(self);
	return result;
}

PUBLIC NONNULL((1)) bool KCALL
mousedev_button(struct mousedev *__restrict self,
                    u32 mask, u32 flag) {
	bool result;
	u32 new_buttons;
	mousedev_smplock_acquire(self);
	new_buttons = (self->md_state.ms_buttons & mask) | flag;
	if (self->md_state.ms_buttons == new_buttons) {
		result = true;
	} else {
		result = mouse_device_do_button_nopr_locked(self, new_buttons);
	}
	mousedev_smplock_release(self);
	return result;
}

PUBLIC NONNULL((1)) bool KCALL
mousedev_button_ex(struct mousedev *__restrict self,
                       u32 mask, u32 flag, u32 xflg,
                       u32 *__restrict pold_buttons,
                       u32 *__restrict pnew_buttons) {
	bool result;
	u32 old_buttons;
	u32 new_buttons;
	mousedev_smplock_acquire(self);
	old_buttons = self->md_state.ms_buttons;
	new_buttons = ((old_buttons & mask) | flag) ^ xflg;
	if (old_buttons == new_buttons) {
		result = true;
	} else {
		result = mouse_device_do_button_nopr_locked(self, new_buttons);
	}
	mousedev_smplock_release(self);
	*pold_buttons = old_buttons;
	*pnew_buttons = new_buttons;
	return result;
}

PUBLIC NONNULL((1)) bool KCALL
mousedev_vwheel(struct mousedev *__restrict self, s32 lines) {
	bool result;
	if unlikely(!lines)
		return true;
	mousedev_smplock_acquire(self);
	result = mouse_device_do_wheel_nopr_locked(self,
	                                           MOUSE_PACKET_TYPE_VSCROLL,
	                                           lines);
	mousedev_smplock_release(self);
	return result;
}

PUBLIC NONNULL((1)) bool KCALL
mousedev_hwheel(struct mousedev *__restrict self, s32 rows) {
	bool result;
	if unlikely(!rows)
		return true;
	mousedev_smplock_acquire(self);
	result = mouse_device_do_wheel_nopr_locked(self,
	                                           MOUSE_PACKET_TYPE_HSCROLL,
	                                           rows);
	mousedev_smplock_release(self);
	return result;
}

PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL mousedev_motion_nopr)(struct mousedev *__restrict self,
                                        s32 relx, s32 rely) {
	bool result;
	if (!relx && !rely)
		return true;
	mousedev_smplock_acquire_nopr(self);
	result = mouse_device_do_motion_nopr_locked(self, relx, rely);
	mousedev_smplock_release_nopr(self);
	return result;
}

PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL mousedev_moveto_nopr)(struct mousedev *__restrict self,
                                        s32 absx, s32 absy) {
	bool result;
	mousedev_smplock_acquire_nopr(self);
	if (self->md_state.ms_abs_x == absx &&
	    self->md_state.ms_abs_y == absy) {
		result = true;
	} else {
		result = mouse_device_do_moveto_nopr_locked(self, absx, absy);
	}
	mousedev_smplock_release_nopr(self);
	return result;
}

PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL mousedev_button_nopr)(struct mousedev *__restrict self,
                                        u32 mask, u32 flag) {
	bool result;
	u32 new_buttons;
	mousedev_smplock_acquire_nopr(self);
	new_buttons = (self->md_state.ms_buttons & mask) | flag;
	if (self->md_state.ms_buttons == new_buttons) {
		result = true;
	} else {
		result = mouse_device_do_button_nopr_locked(self, new_buttons);
	}
	mousedev_smplock_release_nopr(self);
	return result;
}

PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL mousedev_button_ex_nopr)(struct mousedev *__restrict self,
                                           u32 mask, u32 flag, u32 xflg,
                                           u32 *__restrict pold_buttons,
                                           u32 *__restrict pnew_buttons) {
	bool result;
	u32 old_buttons;
	u32 new_buttons;
	mousedev_smplock_acquire_nopr(self);
	old_buttons = self->md_state.ms_buttons;
	new_buttons = ((old_buttons & mask) | flag) ^ xflg;
	if (old_buttons == new_buttons) {
		result = true;
	} else {
		result = mouse_device_do_button_nopr_locked(self, new_buttons);
	}
	mousedev_smplock_release_nopr(self);
	*pold_buttons = old_buttons;
	*pnew_buttons = new_buttons;
	return result;
}

PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL mousedev_vwheel_nopr)(struct mousedev *__restrict self,
                                        s32 lines) {
	bool result;
	if unlikely(!lines)
		return true;
	mousedev_smplock_acquire_nopr(self);
	result = mouse_device_do_wheel_nopr_locked(self,
	                                           MOUSE_PACKET_TYPE_VSCROLL,
	                                           lines);
	mousedev_smplock_release_nopr(self);
	return result;
}

PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL mousedev_hwheel_nopr)(struct mousedev *__restrict self,
                                        s32 rows) {
	bool result;
	if unlikely(!rows)
		return true;
	mousedev_smplock_acquire_nopr(self);
	result = mouse_device_do_wheel_nopr_locked(self,
	                                           MOUSE_PACKET_TYPE_HSCROLL,
	                                           rows);
	mousedev_smplock_release_nopr(self);
	return result;
}





/* Mouse character device operators */
PUBLIC NONNULL((1)) size_t KCALL
mousedev_v_read(struct mfile *__restrict self,
                USER CHECKED void *dst, size_t num_bytes,
                iomode_t mode) THROWS(...) {
	struct mousedev *me = mfile_asmouse(self);
	mouse_packet_t packet;
	size_t result;
	if unlikely(num_bytes < sizeof(mouse_packet_t)) {
		if (num_bytes != 0)
			THROW(E_BUFFER_TOO_SMALL, sizeof(mouse_packet_t), num_bytes);
		goto empty;
	}
	if (mode & IO_NONBLOCK) {
		packet = mousebuf_trygetpacket(&me->md_buf);
		if (packet.mp_type == MOUSE_PACKET_TYPE_NONE) {
			if (mode & IO_NODATAZERO)
				goto empty;
			THROW(E_WOULDBLOCK_WAITFORSIGNAL);
		}
	} else {
		packet = mousebuf_getpacket(&me->md_buf);
		assert(packet.mp_type != MOUSE_PACKET_TYPE_NONE);
	}
	memcpy(dst, &packet, sizeof(mouse_packet_t));
	result = sizeof(mouse_packet_t);
	while (num_bytes >= 2 * sizeof(mouse_packet_t)) {
		dst = (byte_t *)dst + sizeof(mouse_packet_t);
		num_bytes -= sizeof(mouse_packet_t);
		packet = mousebuf_trygetpacket(&me->md_buf);
		if (packet.mp_type == MOUSE_PACKET_TYPE_NONE)
			break;
		COMPILER_WRITE_BARRIER();
		memcpy(dst, &packet, sizeof(mouse_packet_t));
		COMPILER_WRITE_BARRIER();
		result += sizeof(mouse_packet_t);
	}
empty:
	return 0;
}


PUBLIC NONNULL((1)) void KCALL
mousedev_v_stat(struct mfile *__restrict self,
                USER CHECKED struct stat *result) THROWS(...) {
	struct mousedev *me  = mfile_asmouse(self);
	uintptr_half_t count = ATOMIC_READ(me->md_buf.mb_bufstate.bs_state.s_used);

	/* Write info to user-space. */
	result->st_blksize = (typeof(result->st_blksize))sizeof(mouse_packet_t);
	result->st_blocks  = (typeof(result->st_blocks))count;
	result->st_size    = (typeof(result->st_size))count * sizeof(mouse_packet_t);
}

LOCAL bool KCALL
mouse_device_canread(struct mousedev *__restrict self) {
	uintptr_half_t used;
	used = ATOMIC_READ(self->md_buf.mb_bufstate.bs_state.s_used);
	return used != 0;
}


PUBLIC NONNULL((1)) void KCALL
mousedev_v_pollconnect(struct mfile *__restrict self,
                       poll_mode_t what) THROWS(...) {
	struct mousedev *me = mfile_asmouse(self);
	if (what & POLLINMASK)
		task_connect_for_poll(&me->md_buf.mb_avail);
}

PUBLIC NONNULL((1)) poll_mode_t KCALL
mousedev_v_polltest(struct mfile *__restrict self,
                    poll_mode_t what) THROWS(...) {
	struct mousedev *me = mfile_asmouse(self);
	if (what & POLLINMASK) {
		if (mouse_device_canread(me))
			return POLLINMASK;
	}
	return 0;
}


PUBLIC NONNULL((1)) syscall_slong_t KCALL
mousedev_v_ioctl(struct mfile *__restrict self,
                 ioctl_t cmd, USER UNCHECKED void *arg,
                 iomode_t mode) THROWS(...) {
	struct mousedev *me = mfile_asmouse(self);
	(void)mode;
	switch (cmd) {

	case MOUSEIO_GETABSMODE:
		validate_writable(arg, sizeof(int));
		COMPILER_WRITE_BARRIER();
		*(USER CHECKED int *)arg = (me->md_flags & MOUSE_DEVICE_FLAG_GENABS) ? 1 : 0;
		COMPILER_WRITE_BARRIER();
		break;

	case MOUSEIO_SETABSMODE: {
		int mode;
		validate_readable(arg, sizeof(int));
		COMPILER_READ_BARRIER();
		mode = *(USER CHECKED int const *)arg;
		COMPILER_READ_BARRIER();
		if (mode == 0) {
			ATOMIC_AND(me->md_flags, ~MOUSE_DEVICE_FLAG_GENABS);
		} else if (mode == 1) {
			ATOMIC_OR(me->md_flags, MOUSE_DEVICE_FLAG_GENABS);
		} else {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_IOCTL_MOUSE_SETABSMODE_BADMODE,
			      mode);
		}
	}	break;

	case MOUSEIO_GETABSRECT:
		validate_writable(arg, sizeof(struct mouse_rect));
		memcpy(arg, &me->md_rect, sizeof(struct mouse_rect));
		break;

	case MOUSEIO_SETABSRECT: {
		struct mouse_rect new_rect;
		preemption_flag_t was;
		bool was_clamped = false;
		validate_writable(arg, sizeof(struct mouse_rect));
		COMPILER_READ_BARRIER();
		memcpy(&new_rect, arg, sizeof(struct mouse_rect));
		COMPILER_READ_BARRIER();
		/* Require:
		 *   - bounds are ordered correctly
		 *   - Min->Max can be reached with a single, signed, 32-bit integer addition (without overflow) */
		if unlikely(new_rect.mr_minx > new_rect.mr_maxx ||
		            new_rect.mr_miny > new_rect.mr_maxy ||
		            new_rect.mr_minx + INT32_MAX < new_rect.mr_maxx ||
		            new_rect.mr_miny + INT32_MAX < new_rect.mr_maxy) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_IOCTL_MOUSE_SETABSRECT_BADBOUNDS,
			      new_rect.mr_minx, new_rect.mr_miny,
			      new_rect.mr_maxx, new_rect.mr_maxy);
		}
		for (;;) {
			preemption_pushoff(&was);
			if (mousedev_smplock_tryacquire(me))
				break;
			preemption_pop(&was);
			task_yield();
		}
		memcpy(&me->md_rect, &new_rect, sizeof(struct mouse_rect));
		/* Clamp cursor position to the new rect. */
		if (me->md_state.ms_abs_x < new_rect.mr_minx) {
			me->md_state.ms_abs_x = new_rect.mr_minx;
			was_clamped = true;
		} else if (me->md_state.ms_abs_x > new_rect.mr_maxx) {
			me->md_state.ms_abs_x = new_rect.mr_maxx;
			was_clamped = true;
		}
		if (me->md_state.ms_abs_y < new_rect.mr_miny) {
			me->md_state.ms_abs_y = new_rect.mr_miny;
			was_clamped = true;
		} else if (me->md_state.ms_abs_y > new_rect.mr_maxy) {
			me->md_state.ms_abs_y = new_rect.mr_maxy;
			was_clamped = true;
		}
		/* If the cursor position was clamped, and we're in ABS mouse mode, force
		 * the creation of a  sequence of motion packets  in order to update  the
		 * clamped, absolute mouse position. */
		if (was_clamped && (ATOMIC_READ(me->md_flags) & MOUSE_DEVICE_FLAG_GENABS))
			mouse_device_do_motion_nopr_locked(me, 0, 0);
		mousedev_smplock_release_nopr(me);
		preemption_pop(&was);
	}	break;

	case MOUSEIO_PUTMOTION: {
		struct mouse_fake_motion motion;
		validate_readable(arg, sizeof(struct mouse_fake_motion));
		COMPILER_READ_BARRIER();
		memcpy(&motion, arg, sizeof(struct mouse_fake_motion));
		COMPILER_READ_BARRIER();
		if (!mousedev_motion(me, motion.mfm_relx, motion.mfm_rely))
			goto err_buffer_full;
	}	break;

	case MOUSEIO_GETPOS: {
		struct mouse_position pos;
		validate_writable(arg, sizeof(struct mouse_position));
		pos.mp_absx = ATOMIC_READ(me->md_state.ms_abs_x);
		pos.mp_absy = ATOMIC_READ(me->md_state.ms_abs_y);
		COMPILER_READ_BARRIER();
		memcpy(arg, &pos, sizeof(struct mouse_position));
		COMPILER_READ_BARRIER();
	}	break;

	case MOUSEIO_SETPOS: {
		struct mouse_position moveto;
		validate_readable(arg, sizeof(struct mouse_position));
		COMPILER_READ_BARRIER();
		memcpy(&moveto, arg, sizeof(struct mouse_position));
		COMPILER_READ_BARRIER();
		if (!mousedev_moveto(me, moveto.mp_absx, moveto.mp_absy))
			goto err_buffer_full;
	}	break;

	case MOUSEIO_GETBUTTONS: {
		u32 buttons;
		validate_writable(arg, sizeof(u32));
		buttons = ATOMIC_READ(me->md_state.ms_buttons);
		COMPILER_WRITE_BARRIER();
		*(USER CHECKED u32 *)arg = buttons;
		COMPILER_WRITE_BARRIER();
	}	break;

	case MOUSEIO_SETBUTTONS: {
		u32 new_buttons;
		validate_readable(arg, sizeof(u32));
		COMPILER_READ_BARRIER();
		new_buttons = *(USER CHECKED u32 const *)arg;
		COMPILER_READ_BARRIER();
		if (!mousedev_button(me, (u32)~0, new_buttons))
			goto err_buffer_full;
	}	break;

	case MOUSEIO_PUTBUTTON: {
		struct mouse_fake_button button;
		validate_writable(arg, sizeof(struct mouse_fake_button));
		COMPILER_READ_BARRIER();
		memcpy(&button, arg, sizeof(struct mouse_fake_button));
		COMPILER_READ_BARRIER();
		if (!mousedev_button_ex(me,
		                            button.mfb_mask,
		                            button.mfb_flag,
		                            button.mfb_xflg,
		                           &button.mfb_old_buttons,
		                           &button.mfb_new_buttons))
			goto err_buffer_full;
		COMPILER_WRITE_BARRIER();
		((USER CHECKED struct mouse_fake_button *)arg)->mfb_old_buttons = button.mfb_old_buttons;
		((USER CHECKED struct mouse_fake_button *)arg)->mfb_new_buttons = button.mfb_new_buttons;
		COMPILER_WRITE_BARRIER();
	}	break;

	case MOUSEIO_PUTVWHEEL: {
		s32 relmove;
		validate_readable(arg, sizeof(s32));
		COMPILER_READ_BARRIER();
		relmove = *(USER CHECKED s32 const *)arg;
		COMPILER_READ_BARRIER();
		if (!mousedev_vwheel(me, relmove))
			goto err_buffer_full;
	}	break;

	case MOUSEIO_PUTHWHEEL: {
		s32 relmove;
		validate_readable(arg, sizeof(s32));
		COMPILER_READ_BARRIER();
		relmove = *(USER CHECKED s32 const *)arg;
		COMPILER_READ_BARRIER();
		if (!mousedev_hwheel(me, relmove))
			goto err_buffer_full;
	}	break;

	case MOUSEIO_FLUSHPENDING: {
		mouse_packet_t packet;
		for (;;) {
			packet = mousebuf_trygetpacket(&me->md_buf);
			if (packet.mp_type == MOUSE_PACKET_TYPE_NONE)
				break;
		}
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
		break;
	}
	return 0;
err_buffer_full:
	return -EAGAIN;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_MOUSE_C */
