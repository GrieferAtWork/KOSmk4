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
#ifdef __INTELLISENSE__
#include "access.c"

#define WRITE_METHOD vo_cmpxch
#endif /* __INTELLISENSE__ */

DECL_BEGIN

#ifndef _WRITE_METHOD
#define _WRITE_METHOD_vo_write  0
#define _WRITE_METHOD_vo_xch    1
#define _WRITE_METHOD_vo_cmpxch 2
#define _WRITE_METHOD3(x)       _WRITE_METHOD_##x
#define _WRITE_METHOD2(x)       _WRITE_METHOD3(x)
#define _WRITE_METHOD           _WRITE_METHOD2(WRITE_METHOD)
#endif /* !_WRITE_METHOD */

#ifndef APPEND__METHOD
#define _APPEND__METHOD2(x, method) x##_##method
#define _APPEND__METHOD(x, method)  _APPEND__METHOD2(x, method)
#define APPEND__METHOD(x)           _APPEND__METHOD(x, WRITE_METHOD)
#endif /* !APPEND__METHOD */

#ifndef WRITE_FUNC
#define _WRITE_FUNC2(name, method) name##_##method
#define _WRITE_FUNC(name, method)  _WRITE_FUNC2(name, method)
#define WRITE_FUNC(name)           _WRITE_FUNC(name, WRITE_METHOD)
#endif /* !WRITE_FUNC */

#undef HAVE_QWORD
#undef HAVE_XWORD
#if (defined(LIBVIO_CONFIG_HAVE_QWORD) || \
     (defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH) && _WRITE_METHOD == _WRITE_METHOD_vo_cmpxch))
#define HAVE_QWORD
#endif /* ... */
#if (defined(LIBVIO_CONFIG_HAVE_XWORD_CMPXCH) && _WRITE_METHOD == _WRITE_METHOD_vo_cmpxch)
#define HAVE_XWORD
#endif /* ... */

#define do_writeb APPEND__METHOD(do_writeb)
#define do_writew APPEND__METHOD(do_writew)
#define do_writel APPEND__METHOD(do_writel)
#ifdef HAVE_QWORD
#define do_writeq APPEND__METHOD(do_writeq)
#endif /* HAVE_QWORD */
#ifdef HAVE_XWORD
#define do_writex APPEND__METHOD(do_writex)
#endif /* HAVE_XWORD */


/************************************************************************/
/* BYTE-SIZED WRITES                                                    */
/************************************************************************/
LOCAL WUNUSED NONNULL((1, 2)) bool CC
WRITE_FUNC(libvio_writeb)(struct vio_ops const *__restrict ops,
                          struct vioargs *__restrict args,
                          vio_addr_t addr, u8 value) {
	if (ops->WRITE_METHOD.f_byte) {
		do_writeb(addr, value);
		return true;
	}
	if (ops->WRITE_METHOD.f_word) {
		word x;
		BX1 = libvio_readb(args, addr ^ 1);
		B1  = value;
		do_writew(addr & ~1, x.w);
		return true;
	}
	if (ops->WRITE_METHOD.f_dword) {
		dword x = { libvio_readl_aligned(args, AL) };
		B3 = value;
		do_writel(AL, x.l);
		return true;
	}
#ifdef HAVE_QWORD
	if (ops->WRITE_METHOD.f_qword) {
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		qword x = { libvio_readq_aligned(args, AQ) };
#else /* LIBVIO_CONFIG_HAVE_QWORD */
		qword x;
		x.l[0] = libvio_readl_aligned(args, AQ + 0);
		x.l[1] = libvio_readl_aligned(args, AQ + 4);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
		B7 = value;
		do_writeq(AQ, x.q);
		return true;
	}
#endif /* HAVE_QWORD */
#ifdef HAVE_XWORD
	if (ops->WRITE_METHOD.f_xword) {
		xword x;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		x.q[0] = libvio_readq_aligned(args, AX + 0);
		x.q[1] = libvio_readq_aligned(args, AX + 8);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
		x.l[0] = libvio_readl_aligned(args, AX + 0);
		x.l[1] = libvio_readl_aligned(args, AX + 4);
		x.l[2] = libvio_readl_aligned(args, AX + 8);
		x.l[3] = libvio_readl_aligned(args, AX + 12);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
		B15 = value;
		do_writex(AX, x.x);
		return true;
	}
#endif /* HAVE_XWORD */
	return false;
}


/************************************************************************/
/* ALIGNED WORD-SIZED WRITES                                            */
/************************************************************************/
LOCAL WUNUSED NONNULL((1, 2)) bool CC
WRITE_FUNC(libvio_writew_aligned)(struct vio_ops const *__restrict ops,
                                  struct vioargs *__restrict args,
                                  vio_addr_t addr, u16 value) {
	assert((addr & 1) == 0);
	if (ops->WRITE_METHOD.f_word) {
		do_writew(addr, value);
		return true;
	}
	if (ops->WRITE_METHOD.f_byte) {
		word x = { value };
		do_writeb(addr + 0, x.b[0]);
		do_writeb(addr + 1, x.b[1]);
		return true;
	}
	if (ops->WRITE_METHOD.f_dword) {
		dword x;
		WX2 = libvio_readw_aligned(args, addr ^ 2);
		W2  = value;
		do_writel(AL, x.l);
		return true;
	}
#ifdef HAVE_QWORD
	if (ops->WRITE_METHOD.f_qword) {
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		qword x = { libvio_readq_aligned(args, AQ) };
#else /* LIBVIO_CONFIG_HAVE_QWORD */
		qword x;
		x.l[0] = libvio_readl_aligned(args, AQ + 0);
		x.l[1] = libvio_readl_aligned(args, AQ + 4);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
		W6 = value;
		do_writeq(AQ, x.q);
		return true;
	}
#endif /* HAVE_QWORD */
#ifdef HAVE_XWORD
	if (ops->WRITE_METHOD.f_xword) {
		xword x;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		x.q[0] = libvio_readq_aligned(args, AX + 0);
		x.q[1] = libvio_readq_aligned(args, AX + 8);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
		x.l[0] = libvio_readl_aligned(args, AX + 0);
		x.l[1] = libvio_readl_aligned(args, AX + 4);
		x.l[2] = libvio_readl_aligned(args, AX + 8);
		x.l[3] = libvio_readl_aligned(args, AX + 12);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
		W14 = value;
		do_writex(AX, x.x);
		return true;
	}
#endif /* HAVE_XWORD */
	return false;
}


/************************************************************************/
/* UNALIGNED WORD-SIZED WRITES                                          */
/************************************************************************/
LOCAL WUNUSED NONNULL((1, 2)) bool CC
WRITE_FUNC(libvio_writew)(struct vio_ops const *__restrict ops,
                          struct vioargs *__restrict args,
                          vio_addr_t addr, u16 value) {
	if ((addr & 1) == 0) {
		return WRITE_FUNC(libvio_writew_aligned)(ops, args, addr, value);
	} else {
		/* assume((addr & 1) == 1); */
		if (ops->WRITE_METHOD.f_byte) {
			word x = { value };
			do_writeb(addr + 0, x.b[0]);
			do_writeb(addr + 1, x.b[1]);
			return true;
		}
		if (ops->WRITE_METHOD.f_dword && !(addr & 2) /* aka. `(addr & 3) != 3' */) {
			/* assume((addr & 3) == 1); */
			dword x;
			x.l   = libvio_readl_aligned(args, addr - 1);
			x.w_1 = value;
			do_writel(addr - 1, x.l);
			return true;
		}
#ifdef HAVE_QWORD
		if (ops->WRITE_METHOD.f_qword && (addr & 7) != 7) {
			/* assume((addr & 7) <= 6); */
#ifdef LIBVIO_CONFIG_HAVE_QWORD
			qword x = { libvio_readq_aligned(args, AQ) };
#else /* LIBVIO_CONFIG_HAVE_QWORD */
			qword x;
			x.l[0] = libvio_readl_aligned(args, AQ + 0);
			x.l[1] = libvio_readl_aligned(args, AQ + 4);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
			W7 = value;
			do_writeq(AQ, x.q);
			return true;
		}
#endif /* HAVE_QWORD */
#if defined(HAVE_XWORD) && !defined(LIBVIO_CONFIG_HAVE_QWORD)
		if (ops->WRITE_METHOD.f_word) {
			word x = { value };
			word w0, w1;
			w0.b[0] = libvio_readb_aligned(args, addr - 1);
			w0.b[1] = x.b[0];
			w1.b[0] = x.b[1];
			w1.b[1] = libvio_readb_aligned(args, addr + 2);
			do_writew(addr - 1, w0.w);
			do_writew(addr + 1, w1.w);
			return true;
		}
#endif /* HAVE_XWORD && !LIBVIO_CONFIG_HAVE_QWORD */
#ifdef HAVE_XWORD
		if (ops->WRITE_METHOD.f_xword && (addr & 15) != 15) {
			/* assume((addr & 15) == 15); */
			xword x;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
			x.q[0] = libvio_readq_aligned(args, AX + 0);
			x.q[1] = libvio_readq_aligned(args, AX + 8);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
			x.l[0] = libvio_readl_aligned(args, AX + 0);
			x.l[1] = libvio_readl_aligned(args, AX + 4);
			x.l[2] = libvio_readl_aligned(args, AX + 8);
			x.l[3] = libvio_readl_aligned(args, AX + 12);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
			W15 = value;
			do_writex(AX, x.x);
			return true;
		}
#endif /* HAVE_XWORD */
#if !defined(HAVE_XWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD)
		if (ops->WRITE_METHOD.f_word) {
			word x = { value };
			word w0, w1;
			w0.b[0] = libvio_readb_aligned(args, addr - 1);
			w0.b[1] = x.b[0];
			w1.b[0] = x.b[1];
			w1.b[1] = libvio_readb_aligned(args, addr + 2);
			do_writew(addr - 1, w0.w);
			do_writew(addr + 1, w1.w);
			return true;
		}
#endif /* !HAVE_XWORD || LIBVIO_CONFIG_HAVE_QWORD */
		if (ops->WRITE_METHOD.f_dword/* && (addr & 2)*/ /* aka. `(addr & 3) == 3' */) {
			/* assume((addr & 3) == 3); */
			word x = { value };
			dword l0, l1;
			l0.l    = libvio_readl_aligned(args, addr - 3);
			l1.l    = libvio_readl_aligned(args, addr + 1);
			l0.b[3] = x.b[0];
			l1.b[0] = x.b[1];
			do_writel(addr - 3, l0.l);
			do_writel(addr + 1, l1.l);
			return true;
		}
#ifdef HAVE_QWORD
		if (ops->WRITE_METHOD.f_qword && (addr & 7) == 7) {
			/* assume((addr & 7) == 7); */
			word x = { value };
			qword q0, q1;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
			q0.q    = libvio_readq_aligned(args, addr - 7);
			q1.q    = libvio_readq_aligned(args, addr + 1);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
			q0.l[0] = libvio_readl_aligned(args, (addr - 7) + 0);
			q0.l[1] = libvio_readl_aligned(args, (addr - 7) + 4);
			q1.l[0] = libvio_readl_aligned(args, (addr + 1) + 0);
			q1.l[1] = libvio_readl_aligned(args, (addr + 1) + 4);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
			q0.b[7] = x.b[0];
			q1.b[0] = x.b[1];
			do_writeq(addr - 7, q0.q);
			do_writeq(addr + 1, q1.q);
			return true;
		}
#endif /* HAVE_QWORD */
#ifdef HAVE_XWORD
		if (ops->WRITE_METHOD.f_xword && (addr & 15) == 15) {
			/* assume((addr & 15) == 15); */
			word x = { value };
			xword x0, x1;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
			x0.q[0] = libvio_readq_aligned(args, (addr - 15) + 0);
			x0.q[1] = libvio_readq_aligned(args, (addr - 15) + 8);
			x1.q[0] = libvio_readq_aligned(args, (addr + 1) + 0);
			x1.q[1] = libvio_readq_aligned(args, (addr + 1) + 8);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
			x0.l[0] = libvio_readl_aligned(args, (addr - 15) + 0);
			x0.l[1] = libvio_readl_aligned(args, (addr - 15) + 4);
			x0.l[2] = libvio_readl_aligned(args, (addr - 15) + 8);
			x0.l[3] = libvio_readl_aligned(args, (addr - 15) + 12);
			x1.l[0] = libvio_readl_aligned(args, (addr + 1) + 0);
			x1.l[1] = libvio_readl_aligned(args, (addr + 1) + 4);
			x1.l[2] = libvio_readl_aligned(args, (addr + 1) + 8);
			x1.l[3] = libvio_readl_aligned(args, (addr + 1) + 12);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
			x0.b[15] = x.b[0];
			x1.b[0]  = x.b[1];
			do_writex(addr - 15, x0.x);
			do_writex(addr + 1, x1.x);
			return true;
		}
#endif /* HAVE_XWORD */
	}
	return false;
}



/************************************************************************/
/* ALIGNED DWORD-SIZED WRITES                                           */
/************************************************************************/
LOCAL WUNUSED NONNULL((1, 2)) bool CC
WRITE_FUNC(libvio_writel_aligned)(struct vio_ops const *__restrict ops,
                                  struct vioargs *__restrict args,
                                  vio_addr_t addr, u32 value) {
	assert((addr & 3) == 0);
	if (ops->WRITE_METHOD.f_dword) {
		do_writel(addr, value);
		return true;
	}
	if (ops->WRITE_METHOD.f_word) {
		dword x = { value };
		do_writew(addr + 0, x.w[0]);
		do_writew(addr + 2, x.w[1]);
		return true;
	}
	if (ops->WRITE_METHOD.f_byte) {
		dword x = { value };
		do_writeb(addr + 0, x.b[0]);
		do_writeb(addr + 1, x.b[1]);
		do_writeb(addr + 2, x.b[2]);
		do_writeb(addr + 3, x.b[3]);
		return true;
	}
#ifdef HAVE_QWORD
	if (ops->WRITE_METHOD.f_qword) {
		qword x;
		LX4 = libvio_readl_aligned(args, addr ^ 4);
		L4  = value;
		do_writeq(AQ, x.q);
		return true;
	}
#endif /* HAVE_QWORD */
#ifdef HAVE_XWORD
	if (ops->WRITE_METHOD.f_xword) {
		xword x;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		x.q[0] = libvio_readq_aligned(args, AX + 0);
		x.q[1] = libvio_readq_aligned(args, AX + 8);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
		if ((addr & 12) != 0)
			x.l[0] = libvio_readl_aligned(args, AX + 0);
		if ((addr & 12) != 4)
			x.l[1] = libvio_readl_aligned(args, AX + 4);
		if ((addr & 12) != 8)
			x.l[2] = libvio_readl_aligned(args, AX + 8);
		if ((addr & 12) != 12)
			x.l[3] = libvio_readl_aligned(args, AX + 12);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
		L12 = value;
		do_writex(AX, x.x);
		return true;
	}
#endif /* HAVE_XWORD */
	return false;
}



/************************************************************************/
/* UNALIGNED DWORD-SIZED WRITES                                         */
/************************************************************************/
LOCAL WUNUSED NONNULL((1, 2)) bool CC
WRITE_FUNC(libvio_writel)(struct vio_ops const *__restrict ops,
                          struct vioargs *__restrict args,
                          vio_addr_t addr, u32 value) {
	if ((addr & 3) == 0) {
		/* assume((addr & 3) == 0); */
		return WRITE_FUNC(libvio_writel_aligned)(ops, args, addr, value);
	} else {
		/* assume((addr & 3) != 0); */
		if (ops->WRITE_METHOD.f_word && !(addr & 1)) {
			/* assume((addr & 3) == 2); */
			dword x = { value };
			do_writew(addr + 0, x.w[0]);
			do_writew(addr + 2, x.w[1]);
			return true;
		}
#ifdef HAVE_QWORD
		if (ops->WRITE_METHOD.f_qword && (addr & 7) <= 4) {
			/* assume((addr & 7) in [1, 2, 3, 4]); */
			qword x;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
			x.q = libvio_readq_aligned(args, AQ);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
			x.l[0] = libvio_readl_aligned(args, AQ + 0);
			if ((addr & 7) != 4)
				x.l[1] = libvio_readl_aligned(args, AQ + 4);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
			L7 = value;
			do_writeq(AQ, x.q);
			return true;
		}
#endif /* HAVE_QWORD */
		if (ops->WRITE_METHOD.f_dword) {
			qword x;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
			if (!(addr & 4)) {
				x.q = libvio_readq_aligned(args, AL);
			} else
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
			{
				x.l[0] = libvio_readl_aligned(args, AL + 0);
				x.l[1] = libvio_readl_aligned(args, AL + 4);
			}
			L7     = value;
			do_writel(AL + 0, x.l[0]);
			do_writel(AL + 4, x.l[1]);
			return true;
		}
#ifdef HAVE_XWORD
		if (ops->WRITE_METHOD.f_xword && (addr & 15) <= 12) {
			/* assume((addr & 15) in [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]); */
			xword x;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
			x.q[0] = libvio_readq_aligned(args, AQ + 0);
			x.q[0] = libvio_readq_aligned(args, AQ + 8);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
			x.l[0] = libvio_readl_aligned(args, AQ + 0);
			x.l[1] = libvio_readl_aligned(args, AQ + 4);
			x.l[2] = libvio_readl_aligned(args, AQ + 8);
			x.l[3] = libvio_readl_aligned(args, AQ + 12);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
			L15 = value;
			do_writex(AX, x.x);
			return true;
		}
#endif /* HAVE_XWORD */
		if (ops->WRITE_METHOD.f_byte) {
			dword x = { value };
			do_writeb(addr + 0, x.b[0]);
			do_writeb(addr + 1, x.b[1]);
			do_writeb(addr + 2, x.b[2]);
			do_writeb(addr + 3, x.b[3]);
			return true;
		}
		if (ops->WRITE_METHOD.f_word/* && (addr & 1)*/) {
			/* assume((addr & 1) == 1); */
			dword x = { value };
			word w0, w1, w2;
			w0.b[0] = libvio_readb_aligned(args, addr - 1);
			w0.b[1] = x.b[0];
			w1.b[0] = x.b[1];
			w1.b[1] = x.b[2];
			w2.b[0] = x.b[3];
			w2.b[1] = libvio_readb_aligned(args, addr + 4);
			do_writew(addr - 1, w0.w);
			do_writew(addr + 1, w1.w);
			do_writew(addr + 3, w2.w);
			return true;
		}
#ifdef HAVE_QWORD
		if (ops->WRITE_METHOD.f_qword/* && (addr & 7) > 4*/) {
			/* assume((addr & 7) in [5, 6, 7]); */
			xword x;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
			x.q[0] = libvio_readq_aligned(args, AQ + 0);
			x.q[0] = libvio_readq_aligned(args, AQ + 8);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
			x.l[0] = libvio_readl_aligned(args, AQ + 0);
			x.l[1] = libvio_readl_aligned(args, AQ + 4);
			x.l[2] = libvio_readl_aligned(args, AQ + 8);
			x.l[3] = libvio_readl_aligned(args, AQ + 12);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
			L15 = value;
			do_writeq(AQ + 0, x.q[0]);
			do_writeq(AQ + 8, x.q[1]);
			return true;
		}
#endif /* HAVE_QWORD */
#ifdef HAVE_XWORD
		if (ops->WRITE_METHOD.f_xword/* && (addr & 15) > 12*/) {
			/* assume((addr & 15) in [13, 14, 15]); */
			dword x = { value };
			xword x0, x1;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
			x0.q[0] = libvio_readq_aligned(args, AX + 0);
			x0.q[1] = libvio_readq_aligned(args, AX + 8);
			x1.q[0] = libvio_readq_aligned(args, AX + 16);
			x1.q[1] = libvio_readq_aligned(args, AX + 24);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
			x0.l[0] = libvio_readl_aligned(args, AX + 0);
			x0.l[1] = libvio_readl_aligned(args, AX + 4);
			x0.l[2] = libvio_readl_aligned(args, AX + 8);
			x0.l[3] = libvio_readl_aligned(args, AX + 12);
			x1.l[0] = libvio_readl_aligned(args, AX + 16);
			x1.l[1] = libvio_readl_aligned(args, AX + 20);
			x1.l[2] = libvio_readl_aligned(args, AX + 24);
			x1.l[3] = libvio_readl_aligned(args, AX + 28);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
			switch (addr & 15) {

			case 13:
				/* ...aaaaAAAABBBBbbbb... */
				/* ...aaaaA....BBBbbbb... */
				x0.b[13] = x.b[0];
				x0.b[14] = x.b[1];
				x0.b[15] = x.b[2];
				x1.b[0]  = x.b[3];
				break;

			case 14:
				/* ...aaaaAAAABBBBbbbb... */
				/* ...aaaaAA....BBbbbb... */
				x0.b[14] = x.b[0];
				x0.b[15] = x.b[1];
				x1.b[0]  = x.b[2];
				x1.b[1]  = x.b[3];
				break;

			case 15:
				/* ...aaaaAAAABBBBbbbb... */
				/* ...aaaaAAA....Bbbbb... */
				x0.b[15] = x.b[0];
				x1.b[0]  = x.b[1];
				x1.b[1]  = x.b[2];
				x1.b[2]  = x.b[3];
				break;

			default: __builtin_unreachable();
			}
			do_writex(AX + 0, x0.x);
			do_writex(AX + 16, x1.x);
			return true;
		}
#endif /* HAVE_XWORD */
	}
	return false;
}







#ifdef LIBVIO_CONFIG_HAVE_QWORD

/************************************************************************/
/* ALIGNED QWORD-SIZED WRITES                                           */
/************************************************************************/
LOCAL WUNUSED NONNULL((1, 2)) bool CC
WRITE_FUNC(libvio_writeq_aligned)(struct vio_ops const *__restrict ops,
                                  struct vioargs *__restrict args,
                                  vio_addr_t addr, u64 value) {
	assert((addr & 7) == 0);
#ifdef HAVE_QWORD
	if (ops->WRITE_METHOD.f_qword) {
		do_writeq(AQ, value);
		return true;
	}
#endif /* HAVE_QWORD */
	if (ops->WRITE_METHOD.f_dword) {
		qword x = { value };
		do_writel(addr + 0, x.l[0]);
		do_writel(addr + 4, x.l[1]);
		return true;
	}
	if (ops->WRITE_METHOD.f_word) {
		qword x = { value };
		do_writew(addr + 0, x.w[0]);
		do_writew(addr + 2, x.w[1]);
		do_writew(addr + 4, x.w[2]);
		do_writew(addr + 6, x.w[3]);
		return true;
	}
	if (ops->WRITE_METHOD.f_byte) {
		qword x = { value };
		do_writeb(addr + 0, x.b[0]);
		do_writeb(addr + 1, x.b[1]);
		do_writeb(addr + 2, x.b[2]);
		do_writeb(addr + 3, x.b[3]);
		do_writeb(addr + 4, x.b[4]);
		do_writeb(addr + 5, x.b[5]);
		do_writeb(addr + 6, x.b[6]);
		do_writeb(addr + 7, x.b[7]);
		return true;
	}
#ifdef HAVE_XWORD
	if (ops->WRITE_METHOD.f_xword) {
		xword x;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
		QX8 = libvio_readq_aligned(args, addr ^ 8);
		Q8  = value;
#else /* LIBVIO_CONFIG_HAVE_QWORD */
		if (!(addr & 8)) {
			x.q[0] = value;
			x.l[2] = libvio_readl_aligned(args, addr + 8);
			x.l[3] = libvio_readl_aligned(args, addr + 12);
		} else {
			x.l[0] = libvio_readl_aligned(args, addr - 8);
			x.l[1] = libvio_readl_aligned(args, addr - 4);
			x.q[1] = value;
		}
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
		do_writex(AX, x.x);
		return true;
	}
#endif /* HAVE_XWORD */
	return false;
}



/************************************************************************/
/* UNALIGNED DWORD-SIZED WRITES                                         */
/************************************************************************/
LOCAL WUNUSED NONNULL((1, 2)) bool CC
WRITE_FUNC(libvio_writeq)(struct vio_ops const *__restrict ops,
                          struct vioargs *__restrict args,
                          vio_addr_t addr, u64 value) {
	if ((addr & 7) == 0) {
		/* assume((addr & 7) == 0); */
		return WRITE_FUNC(libvio_writeq_aligned)(ops, args, addr, value);
	} else {
		/* assume((addr & 7) != 0); */
		if (ops->WRITE_METHOD.f_dword && !(addr & 3)) {
			/* assume((addr & 7) == 4); */
			qword x = { value };
			do_writel(addr + 0, x.l[0]);
			do_writel(addr + 4, x.l[1]);
			return true;
		}
#ifdef HAVE_XWORD
		if (ops->WRITE_METHOD.f_xword && (addr & 15) <= 8) {
			/* assume((addr & 15) in [1, 2, 3, 4, 5, 6, 7, 8]); */
			xword x;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
			x.q[0] = libvio_readq_aligned(args, AX + 0);
			if ((addr & 15) != 8)
				x.q[1] = libvio_readq_aligned(args, AX + 8);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
			/*if ((addr & 15) > 0)*/ {
				x.l[0] = libvio_readl_aligned(args, AX + 0);
			}
			if ((addr & 15) > 4)
				x.l[1] = libvio_readl_aligned(args, AX + 4);
			if ((addr & 15) > 6)
				x.l[2] = libvio_readl_aligned(args, AX + 8);
			if ((addr & 15) != 8)
				x.l[3] = libvio_readl_aligned(args, AX + 12);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
			Q15 = value;
			do_writex(AX, x.x);
			return true;
		}
#endif /* HAVE_XWORD */
		if (ops->WRITE_METHOD.f_word && !(addr & 1)) {
			/* assume((addr & 7) in [2, 4, 6]); */
			qword x = { value };
			do_writew(addr + 0, x.w[0]);
			do_writew(addr + 2, x.w[1]);
			do_writew(addr + 4, x.w[2]);
			do_writew(addr + 6, x.w[3]);
			return true;
		}
#ifdef HAVE_QWORD
		if (ops->WRITE_METHOD.f_qword) {
			xword x;
			x.q[0] = libvio_readq_aligned(args, AQ + 0);
			x.q[1] = libvio_readq_aligned(args, AQ + 8);
			Q15    = value;
			do_writeq(AQ + 0, x.q[0]);
			do_writeq(AQ + 8, x.q[1]);
			return true;
		}
#endif /* HAVE_QWORD */
		if (ops->WRITE_METHOD.f_byte) {
			qword x = { value };
			do_writeb(addr + 0, x.b[0]);
			do_writeb(addr + 1, x.b[1]);
			do_writeb(addr + 2, x.b[2]);
			do_writeb(addr + 3, x.b[3]);
			do_writeb(addr + 4, x.b[4]);
			do_writeb(addr + 5, x.b[5]);
			do_writeb(addr + 6, x.b[6]);
			do_writeb(addr + 7, x.b[7]);
			return true;
		}
		if (ops->WRITE_METHOD.f_dword/* && (addr & 3)*/) {
			qword x = { value };
			dword l0, l1, l2;
			/* assume((addr & 7) in [1, 2, 3, 5, 6, 7]); */
			/* assume((addr & 3) in [1, 2, 3]); */
			switch (addr & 3) {

			case 1:
				/* ....AAAABBBBCCCC.... */
				/* ....A........CCC.... */
				l0.b[0] = libvio_readb_aligned(args, addr - 1);
				l0.b[1] = x.b[0];
				l0.b[2] = x.b[1];
				l0.b[3] = x.b[2];
				l1.l    = x.l_3;
				l2.l    = libvio_readl_aligned(args, addr + 7);
				l2.b[0] = x.b[7];
				break;

			case 2:
				/* ....AAAABBBBCCCC.... */
				/* ....AA........CC.... */
				l0.w[0] = libvio_readw_aligned(args, addr - 2);
				l0.w[1] = x.w[0];
				l1.l    = x.l_2;
				l2.w[0] = x.w_6;
				l2.w[1] = libvio_readw_aligned(args, addr + 8);
				break;

			case 3:
				/* ....AAAABBBBCCCC.... */
				/* ....AAA........C.... */
				l0.l    = libvio_readl_aligned(args, addr - 3);
				l0.b[3] = x.b[0];
				l1.l    = x.l_1;
				l2.b[0] = x.b[5];
				l2.b[1] = x.b[6];
				l2.b[2] = x.b[7];
				l2.b[3] = libvio_readb_aligned(args, addr + 8);
				break;

			default: __builtin_unreachable();
			}
			do_writel(AL + 0, l0.l);
			do_writel(AL + 4, l1.l);
			do_writel(AL + 8, l2.l);
			return true;
		}
		if (ops->WRITE_METHOD.f_word/* && (addr & 1)*/) {
			/* assume((addr & 7) in [1, 3, 5, 7]); */
			qword x = { value };
			word w0, w1, w2, w3, w4;
			/* ..AABBCCDDEEFF.. */
			/* ..A..........F.. */
			w0.b[0] = libvio_readb_aligned(args, addr - 1);
			w0.b[1] = x.b[0];
			w1.w    = x.w_1;
			w2.w    = x.w_3;
			w3.w    = x.w_5;
			w4.b[0] = x.b[7];
			w4.b[1] = libvio_readb_aligned(args, addr + 8);
			do_writew(addr - 1, w0.w);
			do_writew(addr + 1, w1.w);
			do_writew(addr + 3, w2.w);
			do_writew(addr + 5, w3.w);
			do_writew(addr + 7, w4.w);
			return true;
		}
#ifdef HAVE_XWORD
		if (ops->WRITE_METHOD.f_xword/* && (addr & 15) > 8*/) {
			/* assume((addr & 15) in [9, 10, 11, 12, 13, 14, 15]); */
			qword x = { value };
			xword x0, x1;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
			x0.q[0] = libvio_readq_aligned(args, AX + 0);
			x0.q[1] = libvio_readq_aligned(args, AX + 8);
			x1.q[0] = libvio_readq_aligned(args, AX + 16);
			x1.q[1] = libvio_readq_aligned(args, AX + 24);
#else /* LIBVIO_CONFIG_HAVE_QWORD */
			x0.l[0] = libvio_readl_aligned(args, AX + 0);
			x0.l[1] = libvio_readl_aligned(args, AX + 4);
			x0.l[2] = libvio_readl_aligned(args, AX + 8);
			x0.l[3] = libvio_readl_aligned(args, AX + 12);
			x1.l[0] = libvio_readl_aligned(args, AX + 16);
			x1.l[1] = libvio_readl_aligned(args, AX + 20);
			x1.l[2] = libvio_readl_aligned(args, AX + 24);
			x1.l[3] = libvio_readl_aligned(args, AX + 28);
#endif /* !LIBVIO_CONFIG_HAVE_QWORD */
			switch (addr & 15) {

			case 9:
				/* ........AAAAAAAABBBBBBBBCCCCCCCCDDDDDDDD........ */
				/* ........AAAAAAAAB........CCCCCCCDDDDDDDD........ */
				x0.b[9]  = x.b[0];
				x0.l_10  = x.l_1;
				x0.w_14  = x.w_5;
				x0.b[15] = x.b[6];
				x1.b[0]  = x.b[7];
				break;

			case 10:
				/* ........AAAAAAAABBBBBBBBCCCCCCCCDDDDDDDD........ */
				/* ........AAAAAAAABB........CCCCCCDDDDDDDD........ */
				x0.l_10  = x.l[0];
				x0.w_14  = x.w_4;
				x0.b[15] = x.b[5];
				x1.w[0]  = x.w_6;
				break;

			case 11:
				/* ........AAAAAAAABBBBBBBBCCCCCCCCDDDDDDDD........ */
				/* ........AAAAAAAABBB........CCCCCDDDDDDDD........ */
				x0.b[11] = x.b[0];
				x0.l_12  = x.l_1;
				x1.w[0]  = x.w_5;
				x1.b[2]  = x.b[7];
				break;

			case 12:
				/* ........AAAAAAAABBBBBBBBCCCCCCCCDDDDDDDD........ */
				/* ........AAAAAAAABBBB........CCCCDDDDDDDD........ */
				x0.l_12 = x.l[0];
				x1.l[0] = x.l[1];
				break;

			case 13:
				/* ........AAAAAAAABBBBBBBBCCCCCCCCDDDDDDDD........ */
				/* ........AAAAAAAABBBBB........CCCDDDDDDDD........ */
				x0.b[13] = x.b[0];
				x0.w_14  = x.w_1;
				x1.l[0]  = x.l_3;
				x1.b[4]  = x.b[7];
				break;

			case 14:
				/* ........AAAAAAAABBBBBBBBCCCCCCCCDDDDDDDD........ */
				/* ........AAAAAAAABBBBBB........CCDDDDDDDD........ */
				x0.w_14 = x.w[0];
				x1.l[0] = x.l_2;
				x1.w_4  = x.w_6;
				break;

			case 15:
				/* ........AAAAAAAABBBBBBBBCCCCCCCCDDDDDDDD........ */
				/* ........AAAAAAAABBBBBBB........CDDDDDDDD........ */
				x0.b[15] = x.b[0];
				x1.l[0]  = x.l_1;
				x1.w_4   = x.w_5;
				x1.b[6]  = x.b[7];
				break;

			default: __builtin_unreachable();
			}
			do_writex(AX + 0, x0.x);
			do_writex(AX + 16, x1.x);
			return true;
		}
#endif /* HAVE_XWORD */
	}
	return false;
}
#endif /* LIBVIO_CONFIG_HAVE_QWORD */




#undef do_writeb
#undef do_writew
#undef do_writel
#undef do_writeq
#undef do_writex

#undef HAVE_QWORD
#undef HAVE_XWORD
#undef WRITE_METHOD

DECL_END
