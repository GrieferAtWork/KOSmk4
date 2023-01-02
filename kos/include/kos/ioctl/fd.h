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
#ifndef _KOS_IOCTL_FD_H
#define _KOS_IOCTL_FD_H 1

/* ioctl control code that operate at the handle-level.
 * -> These can be used on _ALL_ file descriptors, without exception! */

#include <__stdinc.h>

#include <asm/ioctl.h>
#include <asm/os/block.h>
#include <asm/os/tty.h>

#include "_openfd.h"

/* NOTE: By default, trying to  invoke an ioctl with  type='T'
 *       that isn't supported has ioctl(2) return with ENOTTY! */
#define FD_IOC_NCLEX  __FIONCLEX /* Clear O_CLOEXEC / IO_CLOEXEC */
#define FD_IOC_CLEX   __FIOCLEX  /* Set O_CLOEXEC / IO_CLOEXEC */
#define FD_IOC_ASYNC  __FIOASYNC /* [int *arg] Set (*arg != 0) or clear (*arg == 0) O_ASYNC / IO_ASYNC */
#define FD_IOC_NBIO   __FIONBIO  /* [int *arg] Set (*arg != 0) or clear (*arg == 0) O_NONBLOCK / IO_NONBLOCK */
#define FD_IOC_QSIZE  __FIOQSIZE /* [loff_t *arg] Return object data-size (not supported by all types of objects) */
#define FD_IOC_GETBSZ __FIGETBSZ /* [int *arg] Return `struct stat::st_blksize' */

/* KOS-specific ioctls. */
#define FD_IOC_NOOP          _IO_KOS('f', 0x00)                /* Does nothing; ioctl(2) returns `0' */
#define FD_IOC_POLLTEST    _IOWR_KOS('f', 0x01, unsigned int)  /* do `*(poll_mode_t *)arg = handle_polltest(fd, *(poll_mode_t *)arg);' */
#define FD_IOC_DUPFD       _IOWR_KOS('f', 0x10, struct openfd) /* Duplicate the handle for this file. (ioctl(2) returns `arg->fo_hint') */
#define FD_IOC_CAST        _IOWR_KOS('f', 0x11, struct fdcast) /* Cast handle into a different type. - Usually, casting is done implicitly, but this does it explicitly. */
#define FD_IOC_DESC        _IOWR_KOS('f', 0x12, struct fddesc) /* Get description string, as also appears in `readlink("/proc/self/fd/[fdno]")' (Not NUL-terminated!) */
#define FD_IOC_DIRECTIO      _IO_KOS('f', 0x4c)                /* s.a. `_FIODIRECTIO' from `<sys/filio.h>' (NOTE: `arg' _is_ one of `FD_IOC_DIRECTIO_*'; it ISN'T a pointer to one of them!) */
#   define FD_IOC_DIRECTIO_OFF  0                              /* Disable optional direct I/O (clear O_DIRECT and IO_OPTDIRECT) */
#   define FD_IOC_DIRECTIO_ON   1                              /* Enable optional direct I/O  (set O_DIRECT and IO_OPTDIRECT) */
#   define FD_IOC_DIRECTIO_MAND 2                              /* Enable mandatory direct I/O (only set O_DIRECT; KOS-specific) */
#define FD_IOC_GETDIRECTIO _IOR_KOS('f', 0x4c, unsigned int)   /* Get current direct-IO mode (arg is a pointer) */
#define FD_IOC_SETDIRECTIO _IOW_KOS('f', 0x4c, unsigned int)   /* Set current direct-IO mode (arg is a pointer) */
#define FD_IOC_GETTYPE     _IOR_KOS('f', 0x80, __uint32_t)     /* Get handle type (one of `HANDLE_TYPE_*' from <kos/kernel/handle.h>) */
#define FD_IOC_GETKIND     _IOR_KOS('f', 0x81, __uint32_t)     /* Get handle kind (one of `HANDLE_TYPEKIND_*' from <kos/kernel/handle.h>) */
#define FD_IOC_GETMODE     _IOR_KOS('f', 0x82, __uint32_t)     /* Get handle mode (set of `IO_*' from <kos/io.h>) */
#define FD_IOC_GETADDR     _IOR_KOS('f', 0x83, __uint64_t)     /* Get handle address (skewed, but guarantied unqiue) */
#define FD_IOC_GETRADDR    _IOR_KOS('f', 0x84, __uint64_t)     /* Get handle address (non-skewed; requires `CAP_SYS_MODULE') */
#define FD_IOC_GETREFCNT   _IOR_KOS('f', 0x85, __uint64_t)     /* Get reference counter of handle (close(2) decrements; dup(2) increments; never returns `0') */
#define _FD_IOC_INCREF      _IO_KOS('f', 0xc0)                 /* increment reference counter and set `_KERNEL_POISON_NO_WARRANTY'; requires `CAP_SYS_MODULE'; not available in NDEBUG kernels. */
#define _FD_IOC_DECREF      _IO_KOS('f', 0xc1)                 /* decrement reference counter and set `_KERNEL_POISON_NO_WARRANTY'; requires `CAP_SYS_MODULE'; not available in NDEBUG kernels. */


#ifdef __CC__
__DECL_BEGIN

struct fdcast {
	/* NOTE: When a handle cannot be cast, `E_INVALID_HANDLE_FILETYPE' is thrown. */
	__uint32_t    fc_rqtyp; /* Requested handle type (one of `HANDLE_TYPE_*') */
	struct openfd fc_resfd; /* Target slot for resulting handle. */
};

struct fddesc {
	__uint64_t      fdc_len;   /* [in]  Available buffer length
	                            * [out] Required buffer length (w/o trailing NUL) */
	union {
		char       *fdc_buf;   /* [0..fdc_len] Buffer space. */
		__uint64_t _fdc_albuf; /* ... */
	};
};

__DECL_END
#endif /* __CC__ */


#endif /* !_KOS_IOCTL_FD_H */
