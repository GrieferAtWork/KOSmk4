/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBVIO_USERVIOFD_H
#define _LIBVIO_USERVIOFD_H 1

#include "api.h"

#include <features.h>

#include <hybrid/byteorder.h>
#include <hybrid/int128.h>
#include <hybrid/typecore.h>

#include <bits/types.h>
#include <compat/config.h>           /* __ARCH_HAVE_COMPAT */
#include <kos/bits/exception_data.h> /* EXCEPTION_DATA_POINTERS */


__DECL_BEGIN

#define UVIO_OPCODE_READB     0x10 /* req                   resp(value:uvio_response_readb) */
#define UVIO_OPCODE_READW     0x11 /* req                   resp(value:uvio_response_readw) */
#define UVIO_OPCODE_READL     0x12 /* req                   resp(value:uvio_response_readl) */
#define UVIO_OPCODE_READQ     0x13 /* req                   resp(value:uvio_response_readq) */
#define UVIO_OPCODE_WRITEB    0x14 /* req(value:uq_args[0].ura_b)   resp(uvio_response) */
#define UVIO_OPCODE_WRITEW    0x15 /* req(value:uq_args[0].ura_w)   resp(uvio_response) */
#define UVIO_OPCODE_WRITEL    0x16 /* req(value:uq_args[0].ura_l)   resp(uvio_response) */
#define UVIO_OPCODE_WRITEQ    0x17 /* req(value:uq_args[0].ura_q)   resp(uvio_response) */
#define UVIO_OPCODE_XCHB      0x18 /* req(value:uq_args[0].ura_b)   resp(oldval:uvio_response_readb) */
#define UVIO_OPCODE_XCHW      0x19 /* req(value:uq_args[0].ura_w)   resp(oldval:uvio_response_readw) */
#define UVIO_OPCODE_XCHL      0x1a /* req(value:uq_args[0].ura_l)   resp(oldval:uvio_response_readl) */
#define UVIO_OPCODE_XCHQ      0x1b /* req(value:uq_args[0].ura_q)   resp(oldval:uvio_response_readq) */
#define UVIO_OPCODE_ADDB      0x1c /* req(value:uq_args[0].ura_b)   resp(oldval:uvio_response_readb) */
#define UVIO_OPCODE_ADDW      0x1d /* req(value:uq_args[0].ura_w)   resp(oldval:uvio_response_readw) */
#define UVIO_OPCODE_ADDL      0x1e /* req(value:uq_args[0].ura_l)   resp(oldval:uvio_response_readl) */
#define UVIO_OPCODE_ADDQ      0x1f /* req(value:uq_args[0].ura_q)   resp(oldval:uvio_response_readq) */
#define UVIO_OPCODE_SUBB      0x20 /* req(value:uq_args[0].ura_b)   resp(oldval:uvio_response_readb) */
#define UVIO_OPCODE_SUBW      0x21 /* req(value:uq_args[0].ura_w)   resp(oldval:uvio_response_readw) */
#define UVIO_OPCODE_SUBL      0x22 /* req(value:uq_args[0].ura_l)   resp(oldval:uvio_response_readl) */
#define UVIO_OPCODE_SUBQ      0x23 /* req(value:uq_args[0].ura_q)   resp(oldval:uvio_response_readq) */
#define UVIO_OPCODE_ANDB      0x24 /* req(value:uq_args[0].ura_b)   resp(oldval:uvio_response_readb) */
#define UVIO_OPCODE_ANDW      0x25 /* req(value:uq_args[0].ura_w)   resp(oldval:uvio_response_readw) */
#define UVIO_OPCODE_ANDL      0x26 /* req(value:uq_args[0].ura_l)   resp(oldval:uvio_response_readl) */
#define UVIO_OPCODE_ANDQ      0x27 /* req(value:uq_args[0].ura_q)   resp(oldval:uvio_response_readq) */
#define UVIO_OPCODE_ORB       0x28 /* req(value:uq_args[0].ura_b)   resp(oldval:uvio_response_readb) */
#define UVIO_OPCODE_ORW       0x29 /* req(value:uq_args[0].ura_w)   resp(oldval:uvio_response_readw) */
#define UVIO_OPCODE_ORL       0x2a /* req(value:uq_args[0].ura_l)   resp(oldval:uvio_response_readl) */
#define UVIO_OPCODE_ORQ       0x2b /* req(value:uq_args[0].ura_q)   resp(oldval:uvio_response_readq) */
#define UVIO_OPCODE_XORB      0x2c /* req(value:uq_args[0].ura_b)   resp(oldval:uvio_response_readb) */
#define UVIO_OPCODE_XORW      0x2d /* req(value:uq_args[0].ura_w)   resp(oldval:uvio_response_readw) */
#define UVIO_OPCODE_XORL      0x2e /* req(value:uq_args[0].ura_l)   resp(oldval:uvio_response_readl) */
#define UVIO_OPCODE_XORQ      0x2f /* req(value:uq_args[0].ura_q)   resp(oldval:uvio_response_readq) */
#define UVIO_OPCODE_CMPXCHB   0x30 /* req(oldval:uq_args[0].ura_b, newval:uq_args[1].ura_b) resp(real_oldval:uvio_response_readb) */
#define UVIO_OPCODE_CMPXCHW   0x31 /* req(oldval:uq_args[0].ura_w, newval:uq_args[1].ura_w) resp(real_oldval:uvio_response_readw) */
#define UVIO_OPCODE_CMPXCHL   0x32 /* req(oldval:uq_args[0].ura_l, newval:uq_args[1].ura_l) resp(real_oldval:uvio_response_readl) */
#define UVIO_OPCODE_CMPXCHQ   0x33 /* req(oldval:uq_args[0].ura_q, newval:uq_args[1].ura_q) resp(real_oldval:uvio_response_readq) */
#define UVIO_OPCODE_CMPXCHX   0x34 /* req(oldval:uq_args[0].ura_x, newval:uq_args[1].ura_x) resp(real_oldval:uvio_response_readx) */
#ifdef __ARCH_HAVE_COMPAT
#define UVIO_OPCODE_EXCEPT    0xf1 /* resp(except:uvio_response_except) */
#ifdef __USE_KOS_KERNEL
#define UVIO_OPCODE_EXCEPT_COMPAT 0xf0 /* resp(except:uvio_response_except_compat) */
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#define UVIO_OPCODE_EXCEPT32  UVIO_OPCODE_EXCEPT_COMPAT /* resp(except:uvio_response_except32) */
#define UVIO_OPCODE_EXCEPT64  UVIO_OPCODE_EXCEPT        /* resp(except:uvio_response_except64) */
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
#define UVIO_OPCODE_EXCEPT32  UVIO_OPCODE_EXCEPT_COMPAT /* resp(except:uvio_response_except32) */
#define UVIO_OPCODE_EXCEPT64  UVIO_OPCODE_EXCEPT        /* resp(except:uvio_response_except64) */
#else /* __ARCH_COMPAT_SIZEOF_POINTER == ... */
#error "Unsupported compat_sizeof(void *)"
#endif /* __ARCH_COMPAT_SIZEOF_POINTER != ... */
#endif /* __USE_KOS_KERNEL */
#else /* __ARCH_HAVE_COMPAT */
#define UVIO_OPCODE_EXCEPT    0xf0 /* Raise an exception */
#endif /* !__ARCH_HAVE_COMPAT */
#define UVIO_OPCODE_GETUCMD   0xfe /* req  (user command request (don't actually respond to this!)) */
#define UVIO_OPCODE_PUTUCMD   0xff /* resp (user command trigger (causes a `UVIO_OPCODE_GETNOOP' to become readable))
                                    * NOTE:  The   `ur_respid'   field   should  be   one   of   `UVIO_OPCODE_UCMD_*' */

/* Values for `ur_respid' of `UVIO_OPCODE_PUTNOOP' responses */
#define UVIO_OPCODE_UCMD_STOP 0x01 /* Destroy the associated UVIO object.
                                    * Used internally by  `libvio.so' to terminate  the service  thread,
                                    * as well as `close(2)' the associated UVIO handle. NOTE: To prevent
                                    * some other thread from destroying a shared UVIO object,  libvio.so
                                    * checks `uq_pid' to  match `getpid(2)', and  ignores stop  requests
                                    * from processes other than its own. */
/* Range of user commands that are free for use by custom protocols.
 * aka.: These will never be used by the `libvio.so' implementation. */
#define UVIO_OPCODE_UCMD_LOUSER 0x80
#define UVIO_OPCODE_UCMD_HIUSER 0xff


/* Values for `uvio_request::uq_reqflags' */
#define UVIO_REQUEST_FLAG_NORMAL 0x00 /* Normal flags. */
#define UVIO_REQUEST_FLAG_ATOMIC 0x80 /* Force an atomic operation */

/* Values for `uvio_response::ur_respflags' */
#define UVIO_RESPONSE_FLAG_NORMAL 0x00 /* Normal flags. */


#ifdef __CC__

union uvio_request_argument {
	__hybrid_uint128_t ura_x;  /* First argument (128-bit) */
	__uint64_t ura_x_as_q[2];  /* First argument (128-bit; as 64-bit vector) */
	__uint32_t ura_x_as_l[4];  /* First argument (128-bit; as 32-bit vector) */
	__uint16_t ura_x_as_w[8];  /* First argument (128-bit; as 16-bit vector) */
	__uint8_t  ura_x_as_b[16]; /* First argument (128-bit; as 8-bit vector) */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	__uint8_t  ura_b;          /* First argument (8-bit) */
	__uint16_t ura_w;          /* First argument (16-bit) */
	__uint8_t  ura_w_as_b[2];  /* First argument (16-bit; as 8-bit vector) */
	__uint32_t ura_l;          /* First argument (32-bit) */
	__uint16_t ura_l_as_w[2];  /* First argument (32-bit; as 16-bit vector) */
	__uint8_t  ura_l_as_b[4];  /* First argument (32-bit; as 8-bit vector) */
	__uint64_t ura_q;          /* First argument (64-bit) */
	__uint32_t ura_q_as_l[2];  /* First argument (64-bit; as 32-bit vector) */
	__uint16_t ura_q_as_w[4];  /* First argument (64-bit; as 16-bit vector) */
	__uint8_t  ura_q_as_b[8];  /* First argument (64-bit; as 8-bit vector) */
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	struct {
		__uint8_t  _ura_b_pad[15]; /* ... */
		__uint8_t   ura_b;  /* First argument (8-bit) */
	}; /* TODO: #ifndef __COMPILER_HAVE_TRANSPARENT_STRUCT */
	struct {
		__uint16_t _ura_w_pad[7]; /* ... */
		union {
			__uint16_t ura_w;         /* First argument (16-bit) */
			__uint8_t  ura_w_as_b[2]; /* First argument (16-bit; as 8-bit vector) */
		}; /* TODO: #ifndef __COMPILER_HAVE_TRANSPARENT_UNION */
	}; /* TODO: #ifndef __COMPILER_HAVE_TRANSPARENT_STRUCT */
	struct {
		__uint32_t _ura_l_pad[3]; /* ... */
		union {
			__uint32_t ura_l;         /* First argument (32-bit) */
			__uint16_t ura_l_as_w[2]; /* First argument (32-bit; as 16-bit vector) */
			__uint8_t  ura_l_as_b[4]; /* First argument (32-bit; as 8-bit vector) */
		}; /* TODO: #ifndef __COMPILER_HAVE_TRANSPARENT_UNION */
	}; /* TODO: #ifndef __COMPILER_HAVE_TRANSPARENT_STRUCT */
	struct {
		__uint64_t _ura_q_pad[1]; /* ... */
		union {
			__uint64_t ura_q;         /* First argument (64-bit) */
			__uint32_t ura_q_as_l[2]; /* First argument (64-bit; as 32-bit vector) */
			__uint16_t ura_q_as_w[4]; /* First argument (64-bit; as 16-bit vector) */
			__uint8_t  ura_q_as_b[8]; /* First argument (64-bit; as 8-bit vector) */
		};
	}; /* TODO: #ifndef __COMPILER_HAVE_TRANSPARENT_STRUCT */
#else /* __BYTE_ORDER__ == ... */
#error "Unsupported endian"
#endif /* __BYTE_ORDER__ != ... */
};

/* This fixed-length structure is read() from uvio objects. */
struct uvio_request {
	/* HINT: The absolute virtual address being accessed is `uq_mapaddr + (uq_addr - uq_mapoffs)' */
	__uint64_t                  uq_addr;     /* Absolute UVIO address that is being accessed. */
	__uint64_t                  uq_mapaddr;  /* Page-aligned virtual base address of the associated mapping (s.a. `va_acmap_page') */
	__uint64_t                  uq_mapoffs;  /* Page-aligned starting offset of the VIO mapping from `uq_mapaddr'. */
	__uint32_t                  uq_pid;      /* PID of the sending process. */
	union {
		__uint16_t              uq_cmd;      /* The request command */
		struct {
			__uint8_t           uq_opcode;   /* The request opcode (one of `UVIO_OPCODE_*') */
			__uint8_t           uq_reqflags; /* Request flags (set of `UVIO_REQUEST_FLAG_*') */
		};
	};
	__uint16_t                  uq_reqid;    /* Request ID (must be echoed back in `struct uvio_response') */
	union uvio_request_argument uq_args[2];  /* Request arguments */
};


#define UVIO_RESPONSE_HEADER                                                      \
	__uint8_t  ur_opcode;    /* The response opcode (one of `UVIO_OPCODE_*') */   \
	__uint8_t  ur_respflags; /* Response flags (set of `UVIO_RESPONSE_FLAG_*') */ \
	__uint16_t ur_respid;    /* Request ID (same as `struct uvio_request::uq_reqid') */

struct uvio_response {
	UVIO_RESPONSE_HEADER
};

struct uvio_response_readb {
	UVIO_RESPONSE_HEADER
	__uint8_t ur_result; /* Return value */
};

struct uvio_response_readw {
	UVIO_RESPONSE_HEADER
	__uint16_t ur_result; /* Return value */
};

struct uvio_response_readl {
	UVIO_RESPONSE_HEADER
	__uint32_t ur_result; /* Return value */
};

struct uvio_response_readq {
	UVIO_RESPONSE_HEADER
	union {
		__uint32_t ur_lresult[2]; /* Return value */
		__uint64_t ur_result;     /* Return value */
	};
};

struct uvio_response_readx {
	UVIO_RESPONSE_HEADER
	union {
		__hybrid_uint128_t ur_result;     /* Return value */
		__uint64_t         ur_qresult[2]; /* Return value */
		__uint32_t         ur_lresult[4]; /* Return value */
	};
};

struct uvio_response_except {
	UVIO_RESPONSE_HEADER
	__uintptr_t ur_except_code;                          /* Exception code (one of `EXCEPT_CODEOF(*)') */
	__uintptr_t ur_except_ptrs[EXCEPTION_DATA_POINTERS]; /* Exception pointers */
};

#if defined(__ARCH_HAVE_COMPAT) && defined(__USE_KOS_KERNEL)
#if __SIZEOF_POINTER__ == 4
#define uvio_response_except_compat uvio_response_except64
#define uvio_response_except32      uvio_response_except
struct uvio_response_except64 {
	UVIO_RESPONSE_HEADER
	__uint64_t ur_except_code;                          /* Exception code (one of `EXCEPT_CODEOF(*)') */
	__uint64_t ur_except_ptrs[EXCEPTION_DATA_POINTERS]; /* Exception pointers */
};
#elif __SIZEOF_POINTER__ == 8
#define uvio_response_except_compat uvio_response_except32
#define uvio_response_except64      uvio_response_except
struct uvio_response_except32 {
	UVIO_RESPONSE_HEADER
	__uint32_t ur_except_code;                          /* Exception code (one of `EXCEPT_CODEOF(*)') */
	__uint32_t ur_except_ptrs[EXCEPTION_DATA_POINTERS]; /* Exception pointers */
};
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported sizeof(void *)"
#endif /* __SIZEOF_POINTER__ != ... */
#endif /* __ARCH_HAVE_COMPAT && __USE_KOS_KERNEL */


#endif /* __CC__ */

__DECL_END


#endif /* !_LIBVIO_USERVIOFD_H */
