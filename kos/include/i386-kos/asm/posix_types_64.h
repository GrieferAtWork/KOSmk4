#ifndef _I386_KOS_ASM_POSIX_TYPES_64_H
#define _I386_KOS_ASM_POSIX_TYPES_64_H 1

/* NOTE: Types in here are not actually used by the kernel!
 *       This header only mirrors what GLibC does for API compatibility. */

#include <hybrid/typecore.h>

#ifdef __CC__
typedef __UINT16_TYPE__    __kernel_old_uid_t;
#define __kernel_old_uid_t __kernel_old_uid_t

typedef __UINT16_TYPE__    __kernel_old_gid_t;
#define __kernel_old_gid_t __kernel_old_gid_t

typedef __UINT64_TYPE__    __kernel_old_dev_t;
#define __kernel_old_dev_t __kernel_old_dev_t
#endif

#include "../../asm/posix_types.h"

#endif /* _I386_KOS_ASM_POSIX_TYPES_64_H */
