/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Linux (/usr/include/[...]/asm/ioctl.h) */
/*!replace_with_include <sys/ioctl.h>*/
#ifndef _ASM_IOCTL_H
#define _ASM_IOCTL_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/types.h>

/* IOCTL format layout:
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
 */

/*
 * The following "type" codes are defined:
 *
 * Domain  Type        Name                Header                    Comment
 * ======  ====        ====                ======                    =======
 *  Linux  0x12        BLK*                <linux/fs.h>
 *  Linux  0x54 ('T')  T*                  <sys/ioctl.h>             TTY & standard
 *  Linux  0x58 ('X')  FI*                 <linux/fs.h>
 *  KOS    0x46 ('F')  FILE_IOC_*          <kos/ioctl/file.h>
 *  KOS    0x4B ('K')  KBD_IOC_*           <kos/ioctl/kbd.h>
 *  KOS    0x4C ('L')  LEAKS_IOC_*         <kos/ioctl/leaks.h>
 *  KOS    0x4D ('M')  MOUSEIO_*           <kos/ioctl/mouse.h>
 *  KOS    0x50 ('P')  PIPE_IOC_*          <kos/ioctl/pipe.h>
 *  KOS    0x53 ('S')  SVGA_IOC_*          <kos/ioctl/svga.h>
 *  KOS    0x54 ('T')  TTYIO_*             <kos/ioctl/tty.h>
 *  KOS    0x56 ('V')  VID_IOC_*           <kos/ioctl/video.h>
 *  KOS    0x66 ('f')  FD_IOC_*            <kos/ioctl/fd.h>
 *  KOS    0x6D ('m')  MOD_IOC_*           <kos/ioctl/mod.h>
 *  KOS    0x70 ('p')  PIDFD_IOC_*         <kos/ioctl/pidfd.h>
 *
 * TODO: The above list is incomplete
 */



/************************************************************************/
/* Descriptions for how ioctl(2) command codes are constructed.         */
/************************************************************************/

/* Bit counts and 0-based masks. */
#ifndef _IOC_NRBITS
#define _IOC_NRBITS   8    /* # of bits for `nr' */
#define _IOC_NRMASK   0xff /* (1 << _IOC_NRBITS) - 1 */
#define _IOC_TYPEBITS 8    /* # of bits for `type' */
#define _IOC_TYPEMASK 0xff /* (1 << _IOC_TYPEBITS) - 1 */
#ifdef __KOS__
#define _IOC_SIZEBITS 13     /* # of bits for `size' */
#define _IOC_SIZEMASK 0x1fff /* (1 << _IOC_SIZEBITS) - 1 */
#define _IOC_KOSBITS  1      /* # of bits for the KOS extension bit */
#define _IOC_KOSMASK  1      /* (1 << _IOC_KOSBITS) - 1 */
#else /* __KOS__ */
#define _IOC_SIZEBITS 14     /* # of bits for `size' */
#define _IOC_SIZEMASK 0x3fff /* (1 << _IOC_SIZEBITS) - 1 */
#endif /* !__KOS__ */
#define _IOC_DIRBITS  2      /* # of bits for `dir' */
#define _IOC_DIRMASK  0x3    /* (1 << _IOC_DIRBITS) - 1 */

/* In-word shifts. */
#define _IOC_NRSHIFT   0  /* Shift for `nr' */
#define _IOC_TYPESHIFT 8  /* Shift for `type' (_IOC_NRSHIFT + _IOC_NRBITS) */
#define _IOC_SIZESHIFT 16 /* Shift for `size' (_IOC_TYPESHIFT + _IOC_TYPEBITS) */
#ifdef _IOC_KOSBITS
#define _IOC_KOSSHIFT  29 /* Shift for `kos'  (_IOC_SIZESHIFT + _IOC_SIZEBITS) */
#define _IOC_DIRSHIFT  30 /* Shift for `dir'  (_IOC_KOSSHIFT + _IOC_KOSBITS) */
#else /* _IOC_KOSBITS */
#define _IOC_DIRSHIFT  30 /* Shift for `dir'  (_IOC_SIZESHIFT + _IOC_SIZEBITS) */
#endif /* !_IOC_KOSBITS */

/* Command direction */
#define _IOC_NONE  0 /* No direction (usually used for commands that don't take an argument). */
#define _IOC_WRITE 1 /* Write to property; read from `arg' */
#define _IOC_READ  2 /* Read from property; write to `arg' */
#define _IOC_RDWR  3 /* read+write to/from argument (== _IOC_WRITE | _IOC_READ) */

/* Pre-calculated masks for directions. */
#define _IOC_IN        __UINT32_C(0x40000000) /* _IOC_WRITE << _IOC_DIRSHIFT */
#define _IOC_OUT       __UINT32_C(0x80000000) /* _IOC_READ << _IOC_DIRSHIFT */
#define _IOC_INOUT     __UINT32_C(0xc0000000) /* _IOC_RDWR << _IOC_DIRSHIFT */

/* Shifts and global masks. */
#define _IOCNR_SHIFT   _IOC_NRSHIFT           /* ... */
#define _IOCNR_MASK    __UINT32_C(0xff)       /* _IOC_NRMASK << _IOC_NRSHIFT */
#define _IOCTYPE_SHIFT _IOC_TYPESHIFT         /* ... */
#define _IOCTYPE_MASK  __UINT32_C(0xff00)     /* _IOC_TYPEMASK << _IOC_TYPESHIFT */
#define _IOCSIZE_SHIFT _IOC_SIZESHIFT         /* ... */
#ifdef _IOC_KOSSHIFT
#define _IOCSIZE_MASK  __UINT32_C(0x1fff0000) /* _IOC_SIZEMASK << _IOC_SIZESHIFT */
#define _IOCKOS_SHIFT  _IOC_KOSSHIFT          /* ... */
#define _IOCKOS_MASK   __UINT32_C(0x20000000) /* _IOC_KOSMASK << _IOC_KOSSHIFT */
#else /* _IOC_KOSSHIFT */
#define _IOCSIZE_MASK  __UINT32_C(0x3fff0000) /* _IOC_SIZEMASK << _IOC_SIZESHIFT */
#endif /* !_IOC_KOSSHIFT */
#define _IOCDIR_SHIFT  _IOC_DIRSHIFT          /* ... */
#define _IOCDIR_MASK   __UINT32_C(0xc0000000) /* _IOC_DIRMASK << _IOC_DIRSHIFT */
#endif /* !_IOC_NRBITS */



/* Substitute missing constants */
#if (!defined(_IOC_NRBITS) || !defined(_IOC_TYPEBITS) || \
     !defined(_IOC_SIZEBITS) || !defined(_IOC_DIRBITS))
#error "Missing macros"
#endif /* ... */
#ifndef _IOC_NRMASK
#define _IOC_NRMASK   ((1 << _IOC_NRBITS) - 1)
#endif /* !_IOC_NRMASK */
#ifndef _IOC_TYPEMASK
#define _IOC_TYPEMASK ((1 << _IOC_TYPEBITS) - 1)
#endif /* !_IOC_TYPEMASK */
#ifndef _IOC_SIZEMASK
#define _IOC_SIZEMASK ((1 << _IOC_SIZEBITS) - 1)
#endif /* !_IOC_SIZEMASK */
#if !defined(_IOC_KOSMASK) && defined(_IOC_KOSBITS)
#define _IOC_KOSMASK ((1 << _IOC_KOSBITS) - 1)
#endif /* !_IOC_KOSMASK && _IOC_KOSBITS */
#ifndef _IOC_DIRMASK
#define _IOC_DIRMASK  ((1 << _IOC_DIRBITS) - 1)
#endif /* !_IOC_DIRMASK */
#ifndef _IOC_NRSHIFT
#define _IOC_NRSHIFT 0
#endif /* !_IOC_NRSHIFT */
#ifndef _IOC_TYPESHIFT
#define _IOC_TYPESHIFT (_IOC_NRSHIFT + _IOC_NRBITS)
#endif /* !_IOC_TYPESHIFT */
#ifndef _IOC_SIZESHIFT
#define _IOC_SIZESHIFT (_IOC_TYPESHIFT + _IOC_TYPEBITS)
#endif /* !_IOC_SIZESHIFT */
#if !defined(_IOC_KOSSHIFT) && defined(_IOC_KOSBITS)
#define _IOC_KOSSHIFT  (_IOC_SIZESHIFT + _IOC_SIZEBITS)
#endif /* !_IOC_KOSSHIFT && _IOC_KOSBITS */
#ifndef _IOC_DIRSHIFT
#ifdef _IOC_KOSSHIFT
#define _IOC_DIRSHIFT (_IOC_KOSSHIFT + _IOC_KOSBITS)
#else /* _IOC_KOSSHIFT */
#define _IOC_DIRSHIFT (_IOC_SIZESHIFT + _IOC_SIZEBITS)
#endif /* !_IOC_KOSSHIFT */
#endif /* !_IOC_DIRSHIFT */
#ifndef _IOC_NONE
#define _IOC_NONE  0 /* No direction (usually used for commands that don't take an argument). */
#define _IOC_WRITE 1 /* Write to property; read from `arg' */
#define _IOC_READ  2 /* Read from property; write to `arg' */
#endif /* !_IOC_NONE */
#ifndef _IOC_RDWR
#define _IOC_RDWR (_IOC_WRITE | _IOC_READ)
#endif /* !_IOC_RDWR */
#ifndef _IOC_IN
#define _IOC_IN (_IOC_WRITE << _IOC_DIRSHIFT)
#endif /* !_IOC_IN */
#ifndef _IOC_OUT
#define _IOC_OUT (_IOC_READ << _IOC_DIRSHIFT)
#endif /* !_IOC_OUT */
#ifndef _IOC_INOUT
#define _IOC_INOUT (_IOC_RDWR << _IOC_DIRSHIFT)
#endif /* !_IOC_INOUT */
#ifndef _IOCNR_SHIFT
#define _IOCNR_SHIFT _IOC_NRSHIFT
#endif /* !_IOCNR_SHIFT */
#ifndef _IOCNR_MASK
#define _IOCNR_MASK (_IOC_NRMASK << _IOC_NRSHIFT)
#endif /* !_IOCNR_MASK */
#ifndef _IOCTYPE_SHIFT
#define _IOCTYPE_SHIFT _IOC_TYPESHIFT
#endif /* !_IOCTYPE_SHIFT */
#ifndef _IOCTYPE_MASK
#define _IOCTYPE_MASK (_IOC_TYPEMASK << _IOC_TYPESHIFT)
#endif /* !_IOCTYPE_MASK */
#ifndef _IOCSIZE_SHIFT
#define _IOCSIZE_SHIFT _IOC_SIZESHIFT
#endif /* !_IOCSIZE_SHIFT */
#ifndef _IOCSIZE_MASK
#define _IOCSIZE_MASK (_IOC_SIZEMASK << _IOC_SIZESHIFT)
#endif /* !_IOCSIZE_MASK */
#if !defined(_IOCKOS_SHIFT) && defined(_IOC_KOSSHIFT)
#define _IOCKOS_SHIFT  _IOC_KOSSHIFT
#endif /* !_IOCKOS_SHIFT && _IOC_KOSSHIFT */
#if !defined(_IOCKOS_MASK) && defined(_IOC_KOSMASK)
#define _IOCKOS_MASK (_IOC_KOSMASK << _IOC_KOSSHIFT)
#endif /* !_IOCKOS_MASK && _IOC_KOSMASK */
#ifndef _IOCDIR_SHIFT
#define _IOCDIR_SHIFT _IOC_DIRSHIFT
#endif /* !_IOCDIR_SHIFT */
#ifndef _IOCDIR_MASK
#define _IOCDIR_MASK (_IOC_DIRMASK << _IOC_DIRSHIFT)
#endif /* !_IOCDIR_MASK */





/* Construct an I/O control code. */
#ifndef _IOC
#if _IOC_NRSHIFT == 0
#define _IOC(dir, type, nr, size) __CCAST(__ioctl_t)(((dir) << _IOC_DIRSHIFT) | ((size) << _IOC_SIZESHIFT) | ((type) << _IOC_TYPESHIFT) | (nr))
#else /* _IOC_NRSHIFT == 0 */
#define _IOC(dir, type, nr, size) __CCAST(__ioctl_t)(((dir) << _IOC_DIRSHIFT) | ((size) << _IOC_SIZESHIFT) | ((type) << _IOC_TYPESHIFT) | ((nr) << _IOC_NRSHIFT))
#endif /* _IOC_NRSHIFT != 0 */
#endif /* !_IOC */

/* Construct an kos-specific control code. */
#if !defined(_IOC_KOS) && defined(_IOCKOS_MASK)
#if _IOC_NRSHIFT == 0
#define _IOC_KOS(dir, type, nr, size) __CCAST(__ioctl_t)(_IOCKOS_MASK | ((dir) << _IOC_DIRSHIFT) | ((size) << _IOC_SIZESHIFT) | ((type) << _IOC_TYPESHIFT) | (nr))
#else /* _IOC_NRSHIFT == 0 */
#define _IOC_KOS(dir, type, nr, size) __CCAST(__ioctl_t)(_IOCKOS_MASK | ((dir) << _IOC_DIRSHIFT) | ((size) << _IOC_SIZESHIFT) | ((type) << _IOC_TYPESHIFT) | ((nr) << _IOC_NRSHIFT))
#endif /* _IOC_NRSHIFT != 0 */
#endif /* !_IOC_KOS && _IOCKOS_MASK */

#ifndef _IOC_TYPECHECK
#if defined(__USE_KOS_ALTERATIONS) && defined(__COMPILER_HAVE_TYPEOF)
#define _IOC_TYPECHECK(t) sizeof(*(__typeof__(t) *)0)
#else /* __USE_KOS_ALTERATIONS && __COMPILER_HAVE_TYPEOF */
#define _IOC_TYPECHECK(t) sizeof(t)
#endif /* !__USE_KOS_ALTERATIONS || !__COMPILER_HAVE_TYPEOF */
#endif /* !_IOC_TYPECHECK */
#ifndef _IOC_TYPECHECK_BAD
#define _IOC_TYPECHECK_BAD sizeof
#endif /* !_IOC_TYPECHECK_BAD */


/* High-level helper macros for creating I/O control codes */
#if _IOC_NONE == 0 && _IOC_NRSHIFT == 0
#define _IO(type, nr)          __CCAST(__ioctl_t)(((type) << _IOC_TYPESHIFT) | (nr))
#define _IOR(type, nr, T)      __CCAST(__ioctl_t)(_IOC_OUT | ((type) << _IOC_TYPESHIFT) | (_IOC_TYPECHECK(T) << _IOC_SIZESHIFT) | (nr))
#define _IOR_BAD(type, nr, T)  __CCAST(__ioctl_t)(_IOC_OUT | ((type) << _IOC_TYPESHIFT) | (_IOC_TYPECHECK_BAD(T) << _IOC_SIZESHIFT) | (nr))
#define _IOW(type, nr, T)      __CCAST(__ioctl_t)(_IOC_IN | ((type) << _IOC_TYPESHIFT) | (_IOC_TYPECHECK(T) << _IOC_SIZESHIFT) | (nr))
#define _IOW_BAD(type, nr, T)  __CCAST(__ioctl_t)(_IOC_IN | ((type) << _IOC_TYPESHIFT) | (_IOC_TYPECHECK_BAD(T) << _IOC_SIZESHIFT) | (nr))
#define _IOWR(type, nr, T)     __CCAST(__ioctl_t)(_IOC_INOUT | ((type) << _IOC_TYPESHIFT) | (_IOC_TYPECHECK(T) << _IOC_SIZESHIFT) | (nr))
#define _IOWR_BAD(type, nr, T) __CCAST(__ioctl_t)(_IOC_INOUT | ((type) << _IOC_TYPESHIFT) | (_IOC_TYPECHECK_BAD(T) << _IOC_SIZESHIFT) | (nr))
#ifdef _IOC_KOS
#define _IO_KOS(type, nr)      __CCAST(__ioctl_t)(_IOCKOS_MASK | ((type) << _IOC_TYPESHIFT) | (nr))
#define _IOR_KOS(type, nr, T)  __CCAST(__ioctl_t)(_IOCKOS_MASK | _IOC_OUT | ((type) << _IOC_TYPESHIFT) | (_IOC_TYPECHECK(T) << _IOC_SIZESHIFT) | (nr))
#define _IOW_KOS(type, nr, T)  __CCAST(__ioctl_t)(_IOCKOS_MASK | _IOC_IN | ((type) << _IOC_TYPESHIFT) | (_IOC_TYPECHECK(T) << _IOC_SIZESHIFT) | (nr))
#define _IOWR_KOS(type, nr, T) __CCAST(__ioctl_t)(_IOCKOS_MASK | _IOC_INOUT | ((type) << _IOC_TYPESHIFT) | (_IOC_TYPECHECK(T) << _IOC_SIZESHIFT) | (nr))
#endif /* _IOC_KOS */
#else /* ... */
#define _IO(type, nr)          _IOC(_IOC_NONE, type, nr, 0)
#define _IOR(type, nr, T)      _IOC(_IOC_READ, type, nr, _IOC_TYPECHECK(T))
#define _IOR_BAD(type, nr, T)  _IOC(_IOC_READ, type, nr, _IOC_TYPECHECK_BAD(T))
#define _IOW(type, nr, T)      _IOC(_IOC_WRITE, type, nr, _IOC_TYPECHECK(T))
#define _IOW_BAD(type, nr, T)  _IOC(_IOC_WRITE, type, nr, _IOC_TYPECHECK_BAD(T))
#define _IOWR(type, nr, T)     _IOC(_IOC_RDWR, type, nr, _IOC_TYPECHECK(T))
#define _IOWR_BAD(type, nr, T) _IOC(_IOC_RDWR, type, nr, _IOC_TYPECHECK_BAD(T))
#ifdef _IOC_KOS
#define _IO_KOS(type, nr)      _IOC_KOS(_IOC_NONE, (type), (nr), 0)
#define _IOR_KOS(type, nr, T)  _IOC_KOS(_IOC_READ, (type), (nr), _IOC_TYPECHECK(T))
#define _IOW_KOS(type, nr, T)  _IOC_KOS(_IOC_WRITE, (type), (nr), _IOC_TYPECHECK(T))
#define _IOWR_KOS(type, nr, T) _IOC_KOS(_IOC_RDWR, (type), (nr), _IOC_TYPECHECK(T))
#endif /* _IOC_KOS */
#endif /* !... */
#define _IO_WITHSIZE(base, sz) __CCAST(__ioctl_t)(((base) & ~_IOCSIZE_MASK) | ((sz) << _IOC_SIZESHIFT))
#define _IO_WITHTYPE(base, T)  __CCAST(__ioctl_t)(((base) & ~_IOCSIZE_MASK) | (_IOC_TYPECHECK(T) << _IOC_SIZESHIFT))

/* Decode a given ioctl() command `nr', splitting it into its base components. */
#define _IOC_NR(nr)    (((nr) >> _IOC_NRSHIFT) & _IOC_NRMASK)
#define _IOC_TYPE(nr)  (((nr) >> _IOC_TYPESHIFT) & _IOC_TYPEMASK)
#define _IOC_SIZE(nr)  (((nr) >> _IOC_SIZESHIFT) & _IOC_SIZEMASK)
#define _IOC_DIR(nr)   (((nr) >> _IOC_DIRSHIFT) & _IOC_DIRMASK)
#ifdef _IOC_KOSSHIFT
#define _IOC_ISKOS(nr) (((nr) >> _IOC_KOSSHIFT) & _IOC_KOSMASK)
#endif /* _IOC_KOSSHIFT */


/* Define a couple of unescaped symbols for compatibility */
#if defined(__USE_KOS_KERNEL) || !defined(__USE_KOS_PURE)
#define IOC_IN        _IOC_IN
#define IOC_OUT       _IOC_OUT
#define IOC_INOUT     _IOC_INOUT
#define IOCSIZE_MASK  _IOCSIZE_MASK
#define IOCSIZE_SHIFT _IOCSIZE_SHIFT
#endif /* __USE_KOS_KERNEL || !__USE_KOS_PURE */

#endif /* !_ASM_IOCTL_H */
