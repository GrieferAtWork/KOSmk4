#ifndef _ASM_IOCTL_H
#define _ASM_IOCTL_H 1

/* DISCLAIMER: _STRONGLY_ Based on '/usr/include/asm-generic/ioctl.h'
 * NOTE: Do not add a license header to this file!*/

#include <__stdinc.h>

/* ioctl command encoding: 32 bits total, command in lower 16 bits,
 * size of the parameter structure in the lower 14 bits of the upper 16 bits.
 * Encoding the size of the parameter structure in the ioctl request
 * is useful for catching programs compiled with old versions
 * and to avoid overwriting user space outside the user buffer area.
 * The highest 2 bits are reserved for indicating the ``access mode''.
 * NOTE: This limits the max parameter size to 16kB -1 !
 *
 * IOCTL format layout:
 *
 * 0xc0000000
 * | 0x7fff0000
 * | |             0x0000ff00
 * | |             |       0x000000ff
 * | |             |       |
 * DDSSSSSSSSSSSSSSTTTTTTTTNNNNNNNN
 * | |             |       |
 * | |             |       nr
 * | |             type
 * | size
 * dir
 *
 *  _IOC(dir, type, nr, size)
 *
 *
 */

#define _IOC_NRBITS        8
#define _IOC_TYPEBITS      8
#ifndef _IOC_SIZEBITS
#define _IOC_SIZEBITS      14
#endif /* !_IOC_SIZEBITS */
#ifndef _IOC_DIRBITS
#define _IOC_DIRBITS       2
#endif /* !_IOC_DIRBITS */

#define _IOC_NRMASK   ((1 << _IOC_NRBITS) - 1)
#define _IOC_TYPEMASK ((1 << _IOC_TYPEBITS) - 1)
#define _IOC_SIZEMASK ((1 << _IOC_SIZEBITS) - 1)
#define _IOC_DIRMASK  ((1 << _IOC_DIRBITS) - 1)

#define _IOC_NRSHIFT   0
#define _IOC_TYPESHIFT (_IOC_NRSHIFT + _IOC_NRBITS)
#define _IOC_SIZESHIFT (_IOC_TYPESHIFT + _IOC_TYPEBITS)
#define _IOC_DIRSHIFT  (_IOC_SIZESHIFT + _IOC_SIZEBITS)

#ifndef _IOC_NONE
#define _IOC_NONE 0U
#endif /* !_IOC_NONE */
#ifndef _IOC_WRITE
#define _IOC_WRITE 1U /* Write to property; read from arg */
#endif /* !_IOC_WRITE */
#ifndef _IOC_READ
#define _IOC_READ 2U /* Read from property; write to arg */
#endif /* !_IOC_READ */

#define _IOC(dir, type, nr, size) \
	(((dir) << _IOC_DIRSHIFT) |   \
	 ((type) << _IOC_TYPESHIFT) | \
	 ((nr) << _IOC_NRSHIFT) |     \
	 ((size) << _IOC_SIZESHIFT))

#define _IOC_KOS(dir, type, nr, size) \
	(_IOC(dir, type, nr, size) | (1 << (_IOC_SIZESHIFT + _IOC_SIZEBITS - 1)))

#define _IOC_TYPECHECK(t) sizeof(t)

/* used to create numbers */
#define _IO(type, nr)          _IOC(_IOC_NONE, (type), (nr), 0)
#define _IOR(type, nr, T)      _IOC(_IOC_READ, (type), (nr), _IOC_TYPECHECK(T))
#define _IOW(type, nr, T)      _IOC(_IOC_WRITE, (type), (nr), _IOC_TYPECHECK(T))
#define _IOWR(type, nr, T)     _IOC(_IOC_READ|_IOC_WRITE, (type), (nr), _IOC_TYPECHECK(T))
#define _IOR_BAD(type, nr, T)  _IOC(_IOC_READ, (type), (nr), sizeof(T))
#define _IOW_BAD(type, nr, T)  _IOC(_IOC_WRITE, (type), (nr), sizeof(T))
#define _IOWR_BAD(type, nr, T) _IOC(_IOC_READ|_IOC_WRITE, (type), (nr), sizeof(T))
#define _IO_KOS(type, nr)      _IOC_KOS(_IOC_NONE, (type), (nr), 0)
#define _IOR_KOS(type, nr, T)  _IOC_KOS(_IOC_READ, (type), (nr), _IOC_TYPECHECK(T))
#define _IOW_KOS(type, nr, T)  _IOC_KOS(_IOC_WRITE, (type), (nr), _IOC_TYPECHECK(T))
#define _IOWR_KOS(type, nr, T) _IOC_KOS(_IOC_READ|_IOC_WRITE, (type), (nr), _IOC_TYPECHECK(T))

/* used to decode ioctl numbers.. */
#define _IOC_DIR(nr)   (((nr) >> _IOC_DIRSHIFT) & _IOC_DIRMASK)
#define _IOC_TYPE(nr)  (((nr) >> _IOC_TYPESHIFT) & _IOC_TYPEMASK)
#define _IOC_NR(nr)    (((nr) >> _IOC_NRSHIFT) & _IOC_NRMASK)
#define _IOC_SIZE(nr)  (((nr) >> _IOC_SIZESHIFT) & _IOC_SIZEMASK)
#define _IOC_ISKOS(nr) ((nr) & (1 << (_IOC_SIZESHIFT + _IOC_SIZEBITS - 1)))

/* ...and for the drivers/sound files... */
#define IOC_IN        (_IOC_WRITE << _IOC_DIRSHIFT)
#define IOC_OUT       (_IOC_READ << _IOC_DIRSHIFT)
#define IOC_INOUT     ((_IOC_WRITE | _IOC_READ) << _IOC_DIRSHIFT)
#define IOCSIZE_MASK  (_IOC_SIZEMASK << _IOC_SIZESHIFT)
#define IOCSIZE_SHIFT (_IOC_SIZESHIFT)

#endif /* !_ASM_IOCTL_H */
