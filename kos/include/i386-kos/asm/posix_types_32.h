#ifndef _I386_KOS_ASM_POSIX_TYPES_32_H
#define _I386_KOS_ASM_POSIX_TYPES_32_H 1

#include <hybrid/typecore.h>

/* NOTE: Types in here are not actually used by the kernel!
 *       This header only mirrors what GLibC does for API compatibility. */

#ifdef __CC__
typedef __UINT16_TYPE__    __kernel_mode_t;
#define __kernel_mode_t    __kernel_mode_t

typedef __UINT16_TYPE__    __kernel_ipc_pid_t;
#define __kernel_ipc_pid_t __kernel_ipc_pid_t

typedef __UINT16_TYPE__    __kernel_uid_t;
#define __kernel_uid_t     __kernel_uid_t

typedef __UINT16_TYPE__    __kernel_gid_t;
#define __kernel_gid_t     __kernel_gid_t

typedef __UINT16_TYPE__    __kernel_old_dev_t;
#define __kernel_old_dev_t __kernel_old_dev_t
#endif /* __CC__ */

#include "../../asm/posix_types.h"

#endif /* _I386_KOS_ASM_POSIX_TYPES_32_H */
