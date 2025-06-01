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
#ifndef _KOS_IOCTL_MOUSE_H
#define _KOS_IOCTL_MOUSE_H 1

/* KOS-specific mouse-device system interface. */

#include <__stdinc.h>

#include <hybrid/__bitfield.h>

#include <asm/ioctl.h>
#include <bits/types.h>

#define MOUSE_BUTTON_LEFT    0x01 /* Left mouse button */
#define MOUSE_BUTTON_MIDDLE  0x02 /* Middle mouse button */
#define MOUSE_BUTTON_RIGHT   0x04 /* Right mouse button */
#define MOUSE_BUTTON_BACK    0x08 /* Back-button */
#define MOUSE_BUTTON_FORWARD 0x10 /* Forward-button */

#define MOUSE_PACKET_TYPE_NONE    0x0 /* No packet (never returned by the kernel) */
#define MOUSE_PACKET_TYPE_MOTION  0x1 /* A mouse was moved. */
#define MOUSE_PACKET_TYPE_BUTTON  0x2 /* A mouse button was pressed/released */
#define MOUSE_PACKET_TYPE_VSCROLL 0x3 /* The vertical scroll-wheel was moved */
#define MOUSE_PACKET_TYPE_HSCROLL 0x4 /* The horizontal scroll-wheel was moved */
#define MOUSE_PACKET_TYPE_MOVED   0x9 /* The mouse's absolute position has changed (only generated if abs-packets are enabled).
                                       * When  abs-packets  are  disabled,  `MOUSE_PACKET_TYPE_MOTION'  is  generated  instead. */
#define MOUSE_PACKET_TYPE_IS4FIELD(x) ((x) & 8) /* The packet has 4 6-bit signed integer fields. (else: 2 12-bit signed integer fields) */

#define MOUSE_PACKET_SEQMAX  6 /* Limit on the number of packets apart of the same sequence.
                                * Calculated as: X  = 6 FOR  X in 12*X  >= 64 &&  6*X >=  32 */

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("mp_word")
#pragma push_macro("mp_type")
#pragma push_macro("mp_seqnum")
#pragma push_macro("mm_relx")
#pragma push_macro("mm_rely")
#pragma push_macro("md_motion")
#pragma push_macro("mb_pressed")
#pragma push_macro("mb_changed")
#pragma push_macro("md_button")
#pragma push_macro("ms_pad")
#pragma push_macro("ms_lines")
#pragma push_macro("md_scroll")
#pragma push_macro("mm_posx")
#pragma push_macro("mm_posy")
#pragma push_macro("md_moved")
#pragma push_macro("mp_data")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef mp_word
#undef mp_type
#undef mp_seqnum
#undef mm_relx
#undef mm_rely
#undef md_motion
#undef mb_pressed
#undef mb_changed
#undef md_button
#undef ms_pad
#undef ms_lines
#undef md_scroll
#undef mm_posx
#undef mm_posy
#undef md_moved
#undef mp_data

typedef union __ATTR_ALIGNED(2) __ATTR_PACKED {
	__uint32_t mp_word; /* Packet control word */
	struct __ATTR_PACKED {
		/* Mouse packet. - This is the structure that is returned when `read(2)'-ing from a mouse device.
		 * Prior to being usable, this structure should be processed using `mouse_packet_sequence()',  in
		 * order to safely handle packet sequences. */
		__HYBRID_BITFIELD8_T mp_type   : 4; /* Mouse packet type. */
		__HYBRID_BITFIELD8_T mp_seqnum : 4; /* Packet sequence number.
		                                     * 0: The last packet of a sequence
		                                     * N: This packet is followed by N-1 more packets
		                                     * NOTE: The current implementation never produces more than `MOUSE_PACKET_SEQMAX'
		                                     *       packets within the same sequence, however KOS reserves the right to later
		                                     *       define additional meaning for sequence numbers that are greater.
		                                     * Example: { 3, 2, 1, 0 } (4-packet sequence) */
		union __ATTR_PACKED {

			/* NOTE: Sign-extension is done based on the most significant  bit
			 *       of the sequence packet with the greatest sequence number. */
			struct __ATTR_PACKED {
				/* PACKET: RELX |= mm_relx << (mp_seqnum * 12);
				 *         RELY |= mm_rely << (mp_seqnum * 12); */
				signed int mm_relx : 12; /* Relative mouse movement in X (negative: left; positive: right) */
				signed int mm_rely : 12; /* Relative mouse movement in Y (negative: down; positive: up) */
			} md_motion; /* MOUSE_PACKET_TYPE_MOTION */

			struct __ATTR_PACKED {
				/* PACKET: PRESSED |= mb_pressed << (mp_seqnum * 12);
				 *         CHANGED |= mb_changed << (mp_seqnum * 12); */
				signed int mb_pressed : 12; /* Set of `MOUSE_BUTTON_*', describing which buttons are currently being held down */
				signed int mb_changed : 12; /* Set of `MOUSE_BUTTON_*', describing which buttons have changed state. */
			} md_button; /* MOUSE_PACKET_TYPE_BUTTON */

			struct __ATTR_PACKED {
				/* PACKET: LINES |= ms_lines << (mp_seqnum * 12); */
				signed int ms_pad   : 12; /* ... */
				signed int ms_lines : 12; /* Number of lines scrolled (negative: scroll-up/left, positive: scroll-down/right) */
			} md_scroll; /* MOUSE_PACKET_TYPE_(V|H)SCROLL */

			struct __ATTR_PACKED {
				/* PACKET: POSX |= mm_posx << (mp_seqnum * 6);
				 *         POSY |= mm_posy << (mp_seqnum * 6);
				 *         RELX |= mm_relx << (mp_seqnum * 6);
				 *         RELY |= mm_rely << (mp_seqnum * 6); */
				signed int mm_posx : 6; /* Absolute mouse position in X (0: left screen border; N-1: right screen border) */
				signed int mm_posy : 6; /* Absolute mouse position in Y (0: lower screen border; N-1: upper screen border) */
				signed int mm_relx : 6; /* Relative mouse movement in X (negative: left; positive: right) */
				signed int mm_rely : 6; /* Relative mouse movement in Y (negative: down; positive: up) */
			} md_moved; /* MOUSE_PACKET_TYPE_MOVED */

		} mp_data;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("mp_data")
#pragma pop_macro("mp_seqnum")
#pragma pop_macro("mp_type")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
	}
#ifndef __COMPILER_HAVE_TRANSPARENT_STRUCT
	__mp_fields
#undef mp_data
#undef mp_seqnum
#undef mp_type
#define mp_type   __mp_fields.mp_type
#define mp_seqnum __mp_fields.mp_seqnum
#define mp_data   __mp_fields.mp_data
#endif /* !__COMPILER_HAVE_TRANSPARENT_STRUCT */
	;
} mouse_packet_t;

typedef union {
	__int64_t   psd_data64[2]; /* MOUSE_PACKET_TYPE_MOTION,  MOUSE_PACKET_TYPE_BUTTON,
	                            * MOUSE_PACKET_TYPE_VSCROLL, MOUSE_PACKET_TYPE_HSCROLL */
	__int32_t   psd_data32[4]; /* MOUSE_PACKET_TYPE_MOVED { posx, posy, relx, rely } */
	__intptr_t _psd_ptr[16 / __SIZEOF_POINTER__];
} mouse_packet_sequence_data_t;

/* Add a given `packet' to a mouse packet sequence
 * @param: data:         Combined sequence data.
 * @param: first_packet: True if `packet' is the first part of a sequence
 * @return: true:        Sequence is complete
 * @return: false:       Sequence is incomplete */
__LOCAL __BOOL
mouse_packet_sequence(mouse_packet_sequence_data_t *__restrict data,
                      mouse_packet_t const *__restrict packet,
                      __BOOL first_packet) {
	unsigned int seqnum = packet->mp_seqnum;
	if (MOUSE_PACKET_TYPE_IS4FIELD(packet->mp_type)) {
		seqnum *= 6;
		if (first_packet) {
			unsigned shift = 32 - seqnum;
#define __PRIVATE_SIGN_EXTEND(x) (((__int32_t)((__uint32_t)(x) << (32 - 6))) >> shift)
			data->psd_data32[0] = __PRIVATE_SIGN_EXTEND(packet->mp_data.md_moved.mm_posx);
			data->psd_data32[1] = __PRIVATE_SIGN_EXTEND(packet->mp_data.md_moved.mm_posy);
			data->psd_data32[2] = __PRIVATE_SIGN_EXTEND(packet->mp_data.md_moved.mm_relx);
			data->psd_data32[3] = __PRIVATE_SIGN_EXTEND(packet->mp_data.md_moved.mm_rely);
#undef __PRIVATE_SIGN_EXTEND
		} else {
			data->psd_data32[0] |= (__int32_t)((__uint32_t)packet->mp_data.md_moved.mm_posx << seqnum);
			data->psd_data32[1] |= (__int32_t)((__uint32_t)packet->mp_data.md_moved.mm_posy << seqnum);
			data->psd_data32[2] |= (__int32_t)((__uint32_t)packet->mp_data.md_moved.mm_relx << seqnum);
			data->psd_data32[3] |= (__int32_t)((__uint32_t)packet->mp_data.md_moved.mm_rely << seqnum);
		}
	} else {
		seqnum *= 12;
		if (first_packet) {
			unsigned shift = 64 - seqnum;
#define __PRIVATE_SIGN_EXTEND(x) (((__int64_t)((__uint64_t)(x) << (32 - 6))) >> shift)
			data->psd_data64[0] = __PRIVATE_SIGN_EXTEND(packet->mp_data.md_motion.mm_relx);
			data->psd_data64[1] = __PRIVATE_SIGN_EXTEND(packet->mp_data.md_motion.mm_rely);
#undef __PRIVATE_SIGN_EXTEND
		} else {
			data->psd_data64[0] |= (__int64_t)((__uint64_t)packet->mp_data.md_motion.mm_relx << seqnum);
			data->psd_data64[1] |= (__int64_t)((__uint64_t)packet->mp_data.md_motion.mm_rely << seqnum);
		}
	}
	return seqnum == 0;
}

struct mouse_rect {
	__int32_t mr_minx; /* Lowest allowed value for `mm_posx' */
	__int32_t mr_miny; /* Lowest allowed value for `mm_posy' */
	__int32_t mr_maxx; /* Greatest allowed value for `mm_posx' */
	__int32_t mr_maxy; /* Greatest allowed value for `mm_posy' */
};

struct mouse_fake_motion {
	__int32_t mfm_relx; /* Relative movement in X */
	__int32_t mfm_rely; /* Relative movement in Y */
};

struct mouse_position {
	__int32_t mp_absx; /* Absolute position in X */
	__int32_t mp_absy; /* Absolute position in Y */
};

struct mouse_fake_button {
	/* Set pressed mouse buttons:
	 * >> mfb_old_buttons = HW_BUTTONS;
	 * >> mfb_new_buttons = ((mfb_old_buttons & mfb_mask) | mfb_flag) ^ mfb_xflg;
	 * >> HW_BUTTONS = mfb_new_buttons; */
	__uint32_t mfb_mask;        /* [IN] Mask of mouse buttons who's state should be kept */
	__uint32_t mfb_flag;        /* [IN] Set of mouse buttons that should become pressed */
	__uint32_t mfb_xflg;        /* [IN] Set of mouse buttons who should change state */
	__uint32_t mfb_old_buttons; /* [OUT] The set of mouse buttons pressed prior to the call */
	__uint32_t mfb_new_buttons; /* [OUT] The set of mouse buttons pressed following the call */
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("md_moved")
#pragma pop_macro("mm_posy")
#pragma pop_macro("mm_posx")
#pragma pop_macro("md_scroll")
#pragma pop_macro("ms_lines")
#pragma pop_macro("ms_pad")
#pragma pop_macro("md_button")
#pragma pop_macro("mb_changed")
#pragma pop_macro("mb_pressed")
#pragma pop_macro("md_motion")
#pragma pop_macro("mm_rely")
#pragma pop_macro("mm_relx")
#pragma pop_macro("mp_seqnum")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

/* Mouse device I/O functions. */
#define MOUSE_IOC_GETABSMODE      _IOR_KOS('M', 0x00, int)  /* Get absolute mouse mode (`MOUSE_PACKET_TYPE_MOVED' are produced) (0: disabled; 1: enabled) */
#define MOUSE_IOC_SETABSMODE      _IOW_KOS('M', 0x00, int)  /* Set absolute mouse mode (`MOUSE_PACKET_TYPE_MOVED' are produced) (0: disabled; 1: enabled) */
#define MOUSE_IOC_GETABSRECT      _IOR_KOS('M', 0x01, struct mouse_rect) /* Get clip rectangle for absolute mouse mode. */
#define MOUSE_IOC_SETABSRECT      _IOW_KOS('M', 0x01, struct mouse_rect) /* Set clip rectangle for absolute mouse mode. */
/* Inject fake inputs. */
#define MOUSE_IOC_PUTMOTION       _IOW_KOS('M', 0x02, struct mouse_fake_motion) /* Inject relative-motion inputs. (errno=EAGAIN: Buffer was full) */
#define MOUSE_IOC_GETPOS          _IOR_KOS('M', 0x03, struct mouse_position) /* Return the current, absolute mouse position */
#define MOUSE_IOC_SETPOS          _IOW_KOS('M', 0x03, struct mouse_position) /* Inject move-to inputs. (errno=EAGAIN: Buffer was full) */
#define MOUSE_IOC_PUTMOVETO       MOUSE_IOC_SETPOS
#define MOUSE_IOC_GETBUTTONS      _IOR_KOS('M', 0x04, __uint32_t) /* Get the set of currently pressed buttons. */
#define MOUSE_IOC_SETBUTTONS      _IOW_KOS('M', 0x04, __uint32_t) /* Set the set of currently pressed buttons. */
#define MOUSE_IOC_PUTBUTTON       _IOW_KOS('M', 0x04, struct mouse_fake_button) /* Inject button inputs. (errno=EAGAIN: Buffer was full) */
#define MOUSE_IOC_PUTVWHEEL       _IOW_KOS('M', 0x05, __int32_t) /* Inject vertical wheel inputs. (errno=EAGAIN: Buffer was full) */
#define MOUSE_IOC_PUTHWHEEL       _IOW_KOS('M', 0x06, __int32_t) /* Inject horizontal wheel inputs. (errno=EAGAIN: Buffer was full) */
#define MOUSE_IOC_FLUSHPENDING     _IO_KOS('M', 0x07) /* Clear the buffer of pending mouse packets */

#endif /* !_KOS_IOCTL_MOUSE_H */
