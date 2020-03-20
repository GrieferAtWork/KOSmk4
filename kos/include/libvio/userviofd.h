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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBVIO_USERVIOFD_H
#define _LIBVIO_USERVIOFD_H 1

#include "api.h"

#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>
#include <compat/config.h>
#include <kos/bits/exception_data.h> /* EXCEPTION_DATA_POINTERS */


__DECL_BEGIN

#define UVIO_OPCODE_READB     0x10 /* req                      resp(value:uvio_response_readb) */
#define UVIO_OPCODE_READW     0x11 /* req                      resp(value:uvio_response_readw) */
#define UVIO_OPCODE_READL     0x12 /* req                      resp(value:uvio_response_readl) */
#define UVIO_OPCODE_READQ     0x13 /* req                      resp(value:uvio_response_readq) */
#define UVIO_OPCODE_WRITEB    0x14 /* req(value:uq_bdata[0])   resp(uvio_response) */
#define UVIO_OPCODE_WRITEW    0x15 /* req(value:uq_wdata[0])   resp(uvio_response) */
#define UVIO_OPCODE_WRITEL    0x16 /* req(value:uq_ldata[0])   resp(uvio_response) */
#define UVIO_OPCODE_WRITEQ    0x17 /* req(value:uq_qdata[0])   resp(uvio_response) */
#define UVIO_OPCODE_XCHB      0x18 /* req(value:uq_bdata[0])   resp(oldval:uvio_response_readb) */
#define UVIO_OPCODE_XCHW      0x19 /* req(value:uq_wdata[0])   resp(oldval:uvio_response_readw) */
#define UVIO_OPCODE_XCHL      0x1a /* req(value:uq_ldata[0])   resp(oldval:uvio_response_readl) */
#define UVIO_OPCODE_XCHQ      0x1b /* req(value:uq_qdata[0])   resp(oldval:uvio_response_readq) */
#define UVIO_OPCODE_ADDB      0x1c /* req(value:uq_bdata[0])   resp(oldval:uvio_response_readb) */
#define UVIO_OPCODE_ADDW      0x1d /* req(value:uq_wdata[0])   resp(oldval:uvio_response_readw) */
#define UVIO_OPCODE_ADDL      0x1e /* req(value:uq_ldata[0])   resp(oldval:uvio_response_readl) */
#define UVIO_OPCODE_ADDQ      0x1f /* req(value:uq_qdata[0])   resp(oldval:uvio_response_readq) */
#define UVIO_OPCODE_SUBB      0x20 /* req(value:uq_bdata[0])   resp(oldval:uvio_response_readb) */
#define UVIO_OPCODE_SUBW      0x21 /* req(value:uq_wdata[0])   resp(oldval:uvio_response_readw) */
#define UVIO_OPCODE_SUBL      0x22 /* req(value:uq_ldata[0])   resp(oldval:uvio_response_readl) */
#define UVIO_OPCODE_SUBQ      0x23 /* req(value:uq_qdata[0])   resp(oldval:uvio_response_readq) */
#define UVIO_OPCODE_ANDB      0x24 /* req(value:uq_bdata[0])   resp(oldval:uvio_response_readb) */
#define UVIO_OPCODE_ANDW      0x25 /* req(value:uq_wdata[0])   resp(oldval:uvio_response_readw) */
#define UVIO_OPCODE_ANDL      0x26 /* req(value:uq_ldata[0])   resp(oldval:uvio_response_readl) */
#define UVIO_OPCODE_ANDQ      0x27 /* req(value:uq_qdata[0])   resp(oldval:uvio_response_readq) */
#define UVIO_OPCODE_ORB       0x28 /* req(value:uq_bdata[0])   resp(oldval:uvio_response_readb) */
#define UVIO_OPCODE_ORW       0x29 /* req(value:uq_wdata[0])   resp(oldval:uvio_response_readw) */
#define UVIO_OPCODE_ORL       0x2a /* req(value:uq_ldata[0])   resp(oldval:uvio_response_readl) */
#define UVIO_OPCODE_ORQ       0x2b /* req(value:uq_qdata[0])   resp(oldval:uvio_response_readq) */
#define UVIO_OPCODE_XORB      0x2c /* req(value:uq_bdata[0])   resp(oldval:uvio_response_readb) */
#define UVIO_OPCODE_XORW      0x2d /* req(value:uq_wdata[0])   resp(oldval:uvio_response_readw) */
#define UVIO_OPCODE_XORL      0x2e /* req(value:uq_ldata[0])   resp(oldval:uvio_response_readl) */
#define UVIO_OPCODE_XORQ      0x2f /* req(value:uq_qdata[0])   resp(oldval:uvio_response_readq) */
#define UVIO_OPCODE_CMPXCHB   0x30 /* req(oldval:uq_bdata[0], newval:uq_bdata[16])    resp(real_oldval:uvio_response_readb) */
#define UVIO_OPCODE_CMPXCHW   0x31 /* req(oldval:uq_wdata[0], newval:uq_wdata[8])     resp(real_oldval:uvio_response_readw) */
#define UVIO_OPCODE_CMPXCHL   0x32 /* req(oldval:uq_ldata[0], newval:uq_ldata[4])     resp(real_oldval:uvio_response_readl) */
#define UVIO_OPCODE_CMPXCHQ   0x33 /* req(oldval:uq_qdata[0], newval:uq_qdata[2])     resp(real_oldval:uvio_response_readq) */
#define UVIO_OPCODE_CMPXCH128 0x34 /* req(oldval:uq_data128[0], newval:uq_data128[1]) resp(real_oldval:uvio_response_read128) */
#ifdef __ARCH_HAVE_COMPAT
#define UVIO_OPCODE_EXCEPT    0xf1 /* resp(except:uvio_response_except) */
#ifdef __USE_KOS_KERNEL
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#define UVIO_OPCODE_EXCEPT32  0xf0 /* resp(except:uvio_response_except32) */
#define UVIO_OPCODE_EXCEPT64  0xf1 /* resp(except:uvio_response_except64) */
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
#define UVIO_OPCODE_EXCEPT32  0xf1 /* resp(except:uvio_response_except32) */
#define UVIO_OPCODE_EXCEPT64  0xf0 /* resp(except:uvio_response_except64) */
#else
#error "Unsupported compat_sizeof(void *)"
#endif
#endif /* __USE_KOS_KERNEL */
#else /* __ARCH_HAVE_COMPAT */
#define UVIO_OPCODE_EXCEPT    0xf0 /* Raise an exception */
#endif /* !__ARCH_HAVE_COMPAT */
#define UVIO_OPCODE_GETUCMD   0xfe /* req  (user command request (don't actually respond to this!)) */
#define UVIO_OPCODE_PUTUCMD   0xff /* resp (user command trigger (causes a `UVIO_OPCODE_GETNOOP' to become readable))
                                    * NOTE: The `ur_respid' field should be one of `UVIO_OPCODE_UCMD_*' */

/* Values for `ur_respid' of `UVIO_OPCODE_PUTNOOP' responses */
#define UVIO_OPCODE_UCMD_STOP 0x01 /* Destroy the associated UVIO object.
                                    * Used internally by `libvio.so' to terminate the service thread,
                                    * as well as `close(2)' the associated UVIO handle. NOTE: To prevent
                                    * some other thread from destroying a shared UVIO object, libvio.so
                                    * checks `uq_pid' to match `getpid(2)', and ignores stop requests
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
/* This fixed-length structure is read() from uvio objects. */
struct uvio_request {
	__uint64_t uq_addr;     /* Absolute UVIO address that is being accessed. */
	__uint64_t uq_mapaddr;  /* Page-aligned virtual base address of the associated mapping (s.a. `va_acmap_page') */
	__uint64_t uq_mapoffs;  /* Page-aligned starting offset of . */
	__uint32_t uq_pid;      /* PID of the sending process. */
	__uint8_t  uq_opcode;   /* The request opcode (one of `UVIO_OPCODE_*') */
	__uint8_t  uq_reqflags; /* Request flags (set of `UVIO_REQUEST_FLAG_*') */
	__uint16_t uq_reqid;    /* Request ID (must be echoed back in `struct uvio_response') */
	union {
		__uint8_t  uq_bdata[32]; /* Data bytes */
		__uint16_t uq_wdata[16]; /* Data words */
		__uint32_t uq_ldata[8];  /* Data dwords */
		__uint64_t uq_qdata[4];  /* Data qwords */
#ifdef __UINT128_TYPE__
		__UINT128_TYPE__ uq_data128[4];  /* Data 128-bit words */
#endif /* __UINT128_TYPE__ */
	};
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

struct uvio_response_read128 {
	UVIO_RESPONSE_HEADER
	union {
#ifdef __UINT128_TYPE__
		__UINT128_TYPE__ ur_result;     /* Return value */
#endif /* __UINT128_TYPE__ */
		__uint64_t       ur_qresult[2]; /* Return value */
		__uint32_t       ur_lresult[4]; /* Return value */
	};
};

struct uvio_response_except {
	UVIO_RESPONSE_HEADER
	__uintptr_t ur_except_code;                          /* Exception code (one of `ERROR_CODEOF(*)') */
	__uintptr_t ur_except_ptrs[EXCEPTION_DATA_POINTERS]; /* Exception pointers */
};

#if defined(__ARCH_HAVE_COMPAT) && defined(__USE_KOS_KERNEL)
#if __SIZEOF_POINTER__ == 4
#define uvio_response_except32 uvio_response_except
struct uvio_response_except64 {
	UVIO_RESPONSE_HEADER
	__uint64_t ur_except_code;                          /* Exception code (one of `ERROR_CODEOF(*)') */
	__uint64_t ur_except_ptrs[EXCEPTION_DATA_POINTERS]; /* Exception pointers */
};
#elif __SIZEOF_POINTER__ == 8
#define uvio_response_except64 uvio_response_except
struct uvio_response_except32 {
	UVIO_RESPONSE_HEADER
	__uint32_t ur_except_code;                          /* Exception code (one of `ERROR_CODEOF(*)') */
	__uint32_t ur_except_ptrs[EXCEPTION_DATA_POINTERS]; /* Exception pointers */
};
#else
#error "Unsupported sizeof(void *)"
#endif
#endif /* __ARCH_HAVE_COMPAT && __USE_KOS_KERNEL */


#endif /* __CC__ */

__DECL_END


#endif /* !_LIBVIO_USERVIOFD_H */
