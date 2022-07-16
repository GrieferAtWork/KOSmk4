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
#ifndef _KOS_IOCTL_LEAKS_H
#define _KOS_IOCTL_LEAKS_H 1

/* KOS-specific ioctl codes for `/proc/kos/leaks' */

#include <__stdinc.h>

#include <asm/ioctl.h>
#include <bits/types.h>

/* Action to-be performed on gathered leaks when the file is close(2)ed */
#define LEAKS_ONCLOSE_RESTORE 0 /* Restore leaks; a future open() of `/proc/kos/leaks' will re-yield them. (default) */
#define LEAKS_ONCLOSE_DISCARD 1 /* Discard leaks but don't free leaked memory. */
#define LEAKS_ONCLOSE_FREE    2 /* Discard leaks and free leaked memory. (Only possible for `kmalloc()'; not possible for `heap_alloc()') */

/* Memory leak ioctl codes. */
#define LEAKS_IOC_GETONCLOSE   _IOR_KOS('L', 0x01, __uint32_t)      /* Get close mode (one of `LEAKS_ONCLOSE_*') */
#define LEAKS_IOC_SETONCLOSE   _IOW_KOS('L', 0x01, __uint32_t)      /* Set close mode (one of `LEAKS_ONCLOSE_*') */
#define LEAKS_IOC_GETCOUNT     _IOR_KOS('L', 0x02, __uint64_t)      /* Return the # of memory leaks captured */
#define LEAKS_IOC_LEAKATTR     _IOR_KOS('L', 0x03, struct leakattr) /* Query attribute values. */
#define LEAKS_IOC_LEAKTB       _IOR_KOS('L', 0x04, struct leaktb)   /* Query memory leak traceback. */
#define LEAKS_IOC_READLEAKMEM  _IOR_KOS('L', 0x05, struct leakmem)  /* Read memory leak contents (LEAK_ATTR_MINADDR...LEAK_ATTR_MAXADDR) */
#define LEAKS_IOC_READUSERMEM  _IOR_KOS('L', 0x06, struct leakmem)  /* Read memory leak contents (LEAK_ATTR_MINUSER...LEAK_ATTR_MAXUSER) */

/* Memory leak attributes. (for `struct leakattr::la_attr') */
#define LEAK_ATTR_MINADDR  1 /* The lowest memory address apart of the leak */
#define LEAK_ATTR_MAXADDR  2 /* The greatest memory address apart of the leak */
#define LEAK_ATTR_LEAKSIZE 3 /* Total leak size (in bytes) */
#define LEAK_ATTR_MINUSER  4 /* The lowest memory address apart of the leak's user-data area (following a possible `CONFIG_KERNEL_MALL_HEAD_SIZE') */
#define LEAK_ATTR_MAXUSER  5 /* The greatest memory address apart of the leak's user-data area (ending before a possible `CONFIG_KERNEL_MALL_TAIL_SIZE') */
#define LEAK_ATTR_USERSIZE 6 /* Total user-data area size (in bytes; w/o `CONFIG_KERNEL_MALL_HEAD_SIZE' or `CONFIG_KERNEL_MALL_TAIL_SIZE') */
#define LEAK_ATTR_TID      7 /* Root-namespace TID of the original allocator thread. */
#define LEAK_ATTR_TBSIZE   8 /* # of addresses within the traceback (enumerate through `LEAKS_IOC_LEAKTB') */
#define LEAK_ATTR_NOWALK   9 /* Returns non-zero if `GFP_NOWALK' was set during the original allocation. */

#ifdef __CC__
__DECL_BEGIN

struct leakattr {
	__uint64_t la_index; /* [in] Memory leak index */
	__uint64_t la_attr;  /* [in] Attribute name (one of `LEAK_ATTR_*') */
	__uint64_t la_value; /* [out] Attribute value */
};

struct leaktb {
	__uint64_t      lt_index; /* [in] Memory leak index */
	__uint64_t      lt_count; /* [in]  Available buffer size (in # of elements)
	                           * [out] Required buffer size (in # of elements) */
	union {
		__uint64_t *lt_elemp; /* [0..lt_count] Traceback address buffer. */
		__uint64_t _lt_elem;  /* Force zero-padding. */
	};
};

struct leakmem {
	__uint64_t      lm_index;  /* [in] Memory leak index */
	__uint64_t      lm_offset; /* [in] Offset into memory leak */
	__uint64_t      lm_size;   /* [in]  # of bytes to read
	                            * [out] # of bytes read (less than `lm_size' if trying to read past leak bounds) */
	union {
		__byte_t   *lm_buf;    /* [0..lm_size] Destination buffer. */
		__uint64_t _lm_buf;    /* Force zero-padding. */
	};
};

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_IOCTL_LEAKS_H */
