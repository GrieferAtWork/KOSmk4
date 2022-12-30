/* (#) Portability: Linux (/usr/include/linux/kernel.h) */
#ifndef _LINUX_KERNEL_H
#define _LINUX_KERNEL_H 1

#include <linux/sysinfo.h>
#define __ALIGN_KERNEL(x, a) __ALIGN_KERNEL_MASK(x, (__typeof__(x))(a)-1)
#define __ALIGN_KERNEL_MASK(x, mask) (((x) + (mask)) & ~(mask))

#endif /* !_LINUX_KERNEL_H */
