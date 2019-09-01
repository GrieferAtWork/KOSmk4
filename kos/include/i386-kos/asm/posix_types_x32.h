#ifndef _I386_KOS_ASM_POSIX_TYPES_X32_H
#define _I386_KOS_ASM_POSIX_TYPES_X32_H 1

#include <hybrid/typecore.h>

/* NOTE: Types in here are not actually used by the kernel!
 *       This header only mirrors what GLibC does for API compatibility. */

#ifdef __CC__
typedef __INT64_TYPE__   __kernel_long_t;
#define __kernel_long_t  __kernel_long_t
typedef __UINT64_TYPE__  __kernel_ulong_t;
#define __kernel_ulong_t __kernel_ulong_t
#endif /* __CC__ */

#include "../../asm/posix_types.h"

#endif /* _I386_KOS_ASM_POSIX_TYPES_X32_H */
