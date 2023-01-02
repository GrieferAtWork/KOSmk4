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
#ifndef _KOS_IOCTL_MOD_H
#define _KOS_IOCTL_MOD_H 1

/* KOS-specific ioctl codes for `HANDLE_TYPE_MODULE' and `HANDLE_TYPE_DRIVER_LOADLIST' */

#include <__stdinc.h>

#include <asm/ioctl.h>

#include "_openfd.h"


/* HANDLE_TYPE_MODULE:          Access the driver's vector of dependencies
 * HANDLE_TYPE_DRIVER_LOADLIST: Return drivers from the load list */
#define MOD_IOC_GETOBJECT _IOWR_KOS('m', 0x00, struct mod_object) /* Get driver by index. (throws `E_NO_SUCH_OBJECT' if slot deleted; requires `CAP_SYS_MODULE') */
#define MOD_IOC_GETCOUNT   _IOR_KOS('m', 0x01, __uint64_t)        /* Get # of drivers. */

/* Return a string, based on `ms_index'
 * HANDLE_TYPE_MODULE:          `ms_index' is one of `MOD_STR_*'
 * HANDLE_TYPE_DRIVER_LOADLIST: `ms_index' is driver index; read string is always `MOD_STR_NAME'
 *                              (throws `E_NO_SUCH_OBJECT' if driver is dead) */
#define MOD_IOC_GETSTRING _IOWR_KOS('m', 0x02, struct mod_string)

/* Possible values for `struct mod_string::ms_index' under `MOD_IOC_GETSTRING' */
#define MOD_STR_NAME     __UINT64_C(0) /* Driver name */
#define MOD_STR_FILENAME __UINT64_C(1) /* Driver filename (frealpath()-style) */
#define MOD_STR_CMDLINE  __UINT64_C(2) /* Driver commandline (arguments are \0-seperated; terminated by \0\0) */


/************************************************************************/
/* All of the remaining ioctls can only be used on drivers              */
/************************************************************************/
#define MOD_IOC_GETSTATE _IOR_KOS('m', 0x10, int)                 /* Write-back driver state.
                                                                   * - Negative value means "driver is being loaded"
                                                                   * - Zero means "driver is up and running"
                                                                   * - Positive value means "driver is being/was unloaded" */
#define MOD_IOC_LOADINFO _IOR_KOS('m', 0x11, struct mod_loadinfo) /* Return load information for the driver (requires `CAP_SYS_MODULE') */
#define MOD_IOC_INIT      _IO_KOS('m', 0x12)                      /* Initialize driver (noop when `MOD_IOC_GETSTATE >= 0'; requires `CAP_SYS_MODULE') */
#define MOD_IOC_FINI      _IO_KOS('m', 0x13)                      /* Finalize driver (noop when `MOD_IOC_GETSTATE != 0'; requires `CAP_SYS_MODULE') */


#ifdef __CC__
__DECL_BEGIN

struct mod_object {
	__uint64_t    mo_index;  /* [in] Object index. */
	struct openfd mo_result; /* Resulting object handle. */
};

struct mod_string {
	__uint64_t      ms_index; /* [in] String index. */
	__uint64_t      ms_size;  /* [in] Available buffer size (in bytes).
	                           * [out] Required buffer size (in bytes; including a trailing NUL) */
	union {
		char       *ms_buf;   /* [1..ms_size] User-space buffer to-be filled with the string. */
		__uint64_t _ms_albuf; /* Alignment... */
	};
};

struct mod_loadinfo {
	__uint64_t mli_loadaddr;  /* Load address of the driver. (ASLR delta) */
	__uint64_t mli_loadstart; /* Lowest address mapped by this driver (already adjusted for `mli_loadaddr'). */
	__uint64_t mli_loadmax;   /* Greatest address mapped by this driver (already adjusted for `mli_loadaddr'). */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_IOCTL_MOD_H */
