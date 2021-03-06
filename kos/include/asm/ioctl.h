#ifndef _ASM_IOCTL_H
#define _ASM_IOCTL_H 1

/* DISCLAIMER: _STRONGLY_ Based on '/usr/include/asm-generic/ioctl.h'
 * NOTE: Do not add a license header to this file! */

#include <__stdinc.h>
#include <features.h>

/* ioctl  command  encoding:  32  bits  total,  command  in  lower  16  bits,
 * size of the parameter structure in the lower 14 bits of the upper 16 bits.
 * Encoding  the  size  of  the  parameter  structure  in  the  ioctl request
 * is   useful   for   catching   programs   compiled   with   old   versions
 * and  to  avoid  overwriting  user  space  outside  the  user  buffer area.
 * The highest  2  bits  are reserved  for  indicating  the  ``access mode''.
 * NOTE: This limits the max parameter size to 16kB -1 !
 *
 * IOCTL format layout:
 *
 * 0xc0000000
 * | 0x40000000
 * | |0x3fff0000
 * | ||            0x0000ff00
 * | ||            |       0x000000ff
 * | ||            |       |
 * DDKSSSSSSSSSSSSSTTTTTTTTNNNNNNNN
 * | ||            |       |
 * | ||            |       nr
 * | ||            type
 * | |size
 * | |
 * | KOS-extension-bit
 * |
 * dir
 *
 *  _IOC(dir, type, nr, size)
 *
 *
 */

#define _IOC_NRBITS   8
#define _IOC_TYPEBITS 8
#ifdef __KOS__
#define _IOC_SIZEBITS 13
#define _IOC_KOSBITS  1
#else /* __KOS__ */
#define _IOC_SIZEBITS 14
#endif /* !__KOS__ */
#define _IOC_DIRBITS  2

#define _IOC_NRMASK   ((1 << _IOC_NRBITS) - 1)
#define _IOC_TYPEMASK ((1 << _IOC_TYPEBITS) - 1)
#define _IOC_SIZEMASK ((1 << _IOC_SIZEBITS) - 1)
#ifdef _IOC_KOSBITS
#define _IOC_KOSMASK  ((1 << _IOC_KOSBITS) - 1)
#endif /* _IOC_KOSBITS */
#define _IOC_DIRMASK  ((1 << _IOC_DIRBITS) - 1)

#define _IOC_NRSHIFT   0
#define _IOC_TYPESHIFT (_IOC_NRSHIFT + _IOC_NRBITS)
#define _IOC_SIZESHIFT (_IOC_NRSHIFT + _IOC_NRBITS + _IOC_TYPEBITS)
#ifdef _IOC_KOSBITS
#define _IOC_KOSSHIFT  (_IOC_NRSHIFT + _IOC_NRBITS + _IOC_TYPEBITS + _IOC_SIZEBITS)
#define _IOC_DIRSHIFT  (_IOC_NRSHIFT + _IOC_NRBITS + _IOC_TYPEBITS + _IOC_SIZEBITS + _IOC_KOSBITS)
#else /* _IOC_KOSBITS */
#define _IOC_DIRSHIFT  (_IOC_NRSHIFT + _IOC_NRBITS + _IOC_TYPEBITS + _IOC_SIZEBITS)
#endif /* !_IOC_KOSBITS */


#define _IOC_NONE  0 /* No special direction. */
#define _IOC_WRITE 1 /* Write to property; read from arg */
#define _IOC_READ  2 /* Read from property; write to arg */

#define _IOC(dir, type, nr, size) \
	(((dir) << _IOC_DIRSHIFT) |     \
	 ((size) << _IOC_SIZESHIFT) |   \
	 ((type) << _IOC_TYPESHIFT) | \
	 ((nr) << _IOC_NRSHIFT))
#ifdef _IOC_KOSSHIFT
#define _IOC_KOS(dir, type, nr, size) \
	((1 << _IOC_KOSSHIFT) | _IOC(dir, type, nr, size))
#endif /* _IOC_KOSSHIFT */

#ifdef __USE_KOS_ALTERATIONS
#define _IOC_TYPECHECK(t) sizeof(*(t *)0)
#else /* __USE_KOS_ALTERATIONS */
#define _IOC_TYPECHECK(t) sizeof(t)
#endif /* !__USE_KOS_ALTERATIONS */

/* used to create numbers */
#define _IO(type, nr)          _IOC(_IOC_NONE, (type), (nr), 0)
#define _IOR(type, nr, T)      _IOC(_IOC_READ, (type), (nr), _IOC_TYPECHECK(T))
#define _IOW(type, nr, T)      _IOC(_IOC_WRITE, (type), (nr), _IOC_TYPECHECK(T))
#define _IOWR(type, nr, T)     _IOC(_IOC_READ | _IOC_WRITE, (type), (nr), _IOC_TYPECHECK(T))
#define _IOR_BAD(type, nr, T)  _IOC(_IOC_READ, (type), (nr), sizeof(T))
#define _IOW_BAD(type, nr, T)  _IOC(_IOC_WRITE, (type), (nr), sizeof(T))
#define _IOWR_BAD(type, nr, T) _IOC(_IOC_READ | _IOC_WRITE, (type), (nr), sizeof(T))
#ifdef _IOC_KOS
#define _IO_KOS(type, nr)      _IOC_KOS(_IOC_NONE, (type), (nr), 0)
#define _IOR_KOS(type, nr, T)  _IOC_KOS(_IOC_READ, (type), (nr), _IOC_TYPECHECK(T))
#define _IOW_KOS(type, nr, T)  _IOC_KOS(_IOC_WRITE, (type), (nr), _IOC_TYPECHECK(T))
#define _IOWR_KOS(type, nr, T) _IOC_KOS(_IOC_READ | _IOC_WRITE, (type), (nr), _IOC_TYPECHECK(T))
#endif /* _IOC_KOS */
#define _IO_WITHTYPE(base, T)  (((base) & ~(_IOC_TYPEMASK << _IOC_TYPESHIFT)) | (_IOC_TYPECHECK(T) << _IOC_TYPESHIFT))

/* used to decode ioctl numbers.. */
#define _IOC_NR(nr)    (((nr) >> _IOC_NRSHIFT) & _IOC_NRMASK)
#define _IOC_TYPE(nr)  (((nr) >> _IOC_TYPESHIFT) & _IOC_TYPEMASK)
#define _IOC_SIZE(nr)  (((nr) >> _IOC_SIZESHIFT) & _IOC_SIZEMASK)
#ifdef _IOC_KOSSHIFT
#define _IOC_ISKOS(nr) (((nr) >> _IOC_KOSSHIFT) & _IOC_KOSMASK)
#endif /* _IOC_KOSSHIFT */
#define _IOC_DIR(nr)   (((nr) >> _IOC_DIRSHIFT) & _IOC_DIRMASK)

/* ...and for the drivers/sound files... */
#define _IOC_IN        (_IOC_WRITE << _IOC_DIRSHIFT)
#define _IOC_OUT       (_IOC_READ << _IOC_DIRSHIFT)
#define _IOC_INOUT     ((_IOC_WRITE | _IOC_READ) << _IOC_DIRSHIFT)
#define _IOCSIZE_MASK  (_IOC_SIZEMASK << _IOC_SIZESHIFT)
#define _IOCSIZE_SHIFT (_IOC_SIZESHIFT)
#if defined(__USE_KOS_KERNEL) || !defined(__USE_KOS_PURE)
#define IOC_IN         _IOC_IN
#define IOC_OUT        _IOC_OUT
#define IOC_INOUT      _IOC_INOUT
#define IOCSIZE_MASK   _IOCSIZE_MASK
#define IOCSIZE_SHIFT  _IOCSIZE_SHIFT
#endif /* __USE_KOS_KERNEL || !__USE_KOS_PURE */

#endif /* !_ASM_IOCTL_H */
