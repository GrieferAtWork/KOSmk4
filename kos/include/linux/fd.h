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
/* (#) Portability: Linux     (/usr/include/linux/fd.h) */
/* (#) Portability: diet libc (/include/linux/fd.h) */
#ifndef _LINUX_FD_H
#define _LINUX_FD_H 1

#include <__stdinc.h>

#include <hybrid/__bitfield.h>
#include <hybrid/typecore.h>

#include <asm/ioctl.h>

/* Taken from /usr/include/linux/fd.h
 * This file is needed for busybox  mkfs_vfat.c, but KOS doesn't (currently)  implement
 * the command codes from this file (and probably never will because who the hell still
 * uses floppies in 2019?) */

__DECL_BEGIN

#ifdef __CC__
struct floppy_struct {
	__UINT32_TYPE__ size;    /* nr of sectors total */
	__UINT32_TYPE__ sect;    /* sectors per track */
	__UINT32_TYPE__ head;    /* nr of heads */
	__UINT32_TYPE__ track;   /* nr of tracks */
	__UINT32_TYPE__ stretch; /* bit 0 != 0 means double track steps */
	                         /* bit 1 != 0 means swap sides */
	                         /* bits 2..9 give the first sector number (the LSB is flipped) */
#define FD_STRETCH          1
#define FD_SWAPSIDES        2
#define FD_ZEROBASED        4
#define FD_SECTBASEMASK     0x3fc
#define FD_MKSECTBASE(s)    (((s) ^ 1) << 2)
#define FD_SECTBASE(floppy) ((((floppy)->stretch & FD_SECTBASEMASK) >> 2) ^ 1)
	__UINT8_TYPE__ gap;     /* gap1 size */
	__UINT8_TYPE__ rate;    /* data rate. |= 0x40 for perpendicular */
#define FD_2M 0x4
#define FD_SIZECODEMASK 0x38
#define FD_SIZECODE(floppy) (((((floppy)->rate & FD_SIZECODEMASK) >> 3) + 2) % 8)
#define FD_SECTSIZE(floppy) ((floppy)->rate & FD_2M ? 512 : 128 << FD_SIZECODE(floppy))
#define FD_PERP 0x40
	__UINT8_TYPE__ spec1;   /* stepping rate, head unload time */
	__UINT8_TYPE__ fmt_gap; /* gap2 size */
	const char    *name;    /* used only for predefined formats */
};

struct format_descr {
	__UINT32_TYPE__ device;
	__UINT32_TYPE__ head;
	__UINT32_TYPE__ track;
};

struct floppy_max_errors {
	__UINT32_TYPE__ abort;      /* number of errors to be reached before aborting */
	__UINT32_TYPE__ read_track; /* maximal number of errors permitted to read an entire track at once */
	__UINT32_TYPE__ reset;      /* maximal number of errors before a reset is tried */
	__UINT32_TYPE__ recal;      /* maximal number of errors before a recalibrate is tried */
	__UINT32_TYPE__ reporting;  /* Threshold for reporting  FDC errors  to the  console.
	                             * Setting this to zero may flood your screen when using
	                             * ultra cheap floppies ;-) */
};

typedef char floppy_drive_name[16];

struct floppy_drive_params {
	__INT8_TYPE__            cmos; /* CMOS type */
	/* Spec2  is (HLD<<1 | ND), where HLD is head load time (1=2ms, 2=4 ms
	 * etc) and ND is set means no DMA. Hardcoded to 6 (HLD=6ms, use DMA). */
	__ULONGPTR_TYPE__        max_dtr;         /* Step rate, usec */
	__ULONGPTR_TYPE__        hlt;             /* Head load/settle time, msec */
	__ULONGPTR_TYPE__        hut;             /* Head unload time (remnant of 8" drives) */
	__ULONGPTR_TYPE__        srt;             /* Step rate, usec */
	__ULONGPTR_TYPE__        spinup;          /* time needed for spinup (expressed in jiffies) */
	__ULONGPTR_TYPE__        spindown;        /* timeout needed for spindown */
	__UINT8_TYPE__           spindown_offset; /* decides in which position the disk will stop */
	__UINT8_TYPE__           select_delay;    /* delay to wait after select */
	__UINT8_TYPE__           rps;             /* rotations per second */
	__UINT8_TYPE__           tracks;          /* maximum number of tracks */
	__ULONGPTR_TYPE__        timeout;         /* timeout for interrupt requests */
	__UINT8_TYPE__           interleave_sect; /* if there are more sectors, use interleave */
	struct floppy_max_errors max_errors;
	__UINT8_TYPE__           flags; /* various flags, including ftd_msg */
	/* Announce successful media type detection and media information loss after disk changes.
	 * Also used to enable/disable printing of overrun warnings. */
#define FTD_MSG             0x10
#define FD_BROKEN_DCL       0x20
#define FD_DEBUG            0x02
#define FD_SILENT_DCL_CLEAR 0x4
#define FD_INVERTED_DCL     0x80 /* must be 0x80, because of hardware considerations */
	__UINT8_TYPE__ read_track; /* use readtrack during probing? */
	/* Auto-detection.  Each   drive  type   has  eight   formats  which   are
	 * used in succession to try to read the disk. If the FDC cannot lock onto
	 * the disk, the next format is  tried. This uses the variable  'probing'. */
	__INT16_TYPE__ autodetect[8]; /* autodetected formats */
	__INT32_TYPE__ checkfreq;     /* how often should the drive be checked for disk changes */
	__INT32_TYPE__ native_format; /* native format of this drive */
};

enum {
	FD_NEED_TWADDLE_BIT,   /* more magic */
	FD_VERIFY_BIT,         /* inquire for write protection */
	FD_DISK_NEWCHANGE_BIT, /* change detected, and no action undertaken yet to clear media change status */
	FD_UNUSED_BIT,
	FD_DISK_CHANGED_BIT,  /* disk has been changed since last i/o */
	FD_DISK_WRITABLE_BIT, /* disk is writable */
	FD_OPEN_SHOULD_FAIL_BIT
};

struct floppy_drive_struct {
	__ULONGPTR_TYPE__ flags;
/* values for these flags */
#define FD_NEED_TWADDLE   (1 << FD_NEED_TWADDLE_BIT)
#define FD_VERIFY         (1 << FD_VERIFY_BIT)
#define FD_DISK_NEWCHANGE (1 << FD_DISK_NEWCHANGE_BIT)
#define FD_DISK_CHANGED   (1 << FD_DISK_CHANGED_BIT)
#define FD_DISK_WRITABLE  (1 << FD_DISK_WRITABLE_BIT)
	__ULONGPTR_TYPE__ spinup_date;
	__ULONGPTR_TYPE__ select_date;
	__ULONGPTR_TYPE__ first_read_date;
	__INT16_TYPE__    probed_format;
	__INT16_TYPE__    track;      /* current track */
	__INT16_TYPE__    maxblock;   /* id of highest block read */
	__INT16_TYPE__    maxtrack;   /* id of highest half track read */
	__INT32_TYPE__    generation; /* how many diskchanges? */
	__INT32_TYPE__    keep_data;  /* (User-provided) media information is _not_ discarded after a media change
	                               * if the  corresponding keep_data  flag is  non-zero. Positive  values  are
	                               * decremented after each probe. */
	__INT32_TYPE__    fd_ref;     /* Prevent "aliased" accesses. */
	__INT32_TYPE__    fd_device;
	__ULONGPTR_TYPE__ last_checked; /* when was the drive last checked for a disk change? */
	char             *dmabuf;
	__INT32_TYPE__    bufblocks;
};

enum reset_mode {
	FD_RESET_IF_NEEDED, /* reset only if the reset flags is set */
	FD_RESET_IF_RAWCMD, /* obsolete */
	FD_RESET_ALWAYS     /* reset always */
};

struct floppy_fdc_state {
	__INT32_TYPE__       spec1; /* spec1 value last used */
	__INT32_TYPE__       spec2; /* spec2 value last used */
	__INT32_TYPE__       dtr;
	__UINT8_TYPE__       version; /* FDC version code */
	__UINT8_TYPE__       dor;
	__ULONGPTR_TYPE__    address; /* io address */
	__HYBRID_BITFIELD8_T rawcmd : 2;
	__HYBRID_BITFIELD8_T reset : 1;
	__HYBRID_BITFIELD8_T need_configure : 1;
	__HYBRID_BITFIELD8_T perp_mode : 2;
	__HYBRID_BITFIELD8_T has_fifo : 1;
	__UINT32_TYPE__      driver_version; /* version code for floppy driver */
#define FD_DRIVER_VERSION 0x100
	/* user programs using the floppy  API should use floppy_fdc_state  to
	 * get the version number of the  floppy driver that they are  running
	 * on. If this version number is bigger than the one compiled into the
	 * user program (the FD_DRIVER_VERSION define), it should be  prepared
	 * to bigger structures */
	unsigned char        track[4];
	/* Position of the heads of the 4 units attached to this  FDC,
	 * as stored on the FDC. In the future, the position as stored
	 * on  the  FDC  might  not  agree  with  the  actual physical
	 * position of these drive heads. By allowing such
	 * disagreement, it will be possible to reset the FDC without
	 * incurring  the expensive cost  of repositioning all heads.
	 * Right now, these positions are hard wired to 0. */
};

struct floppy_write_errors {
	/* Write error logging.
	 * These  fields   can  be   cleared  with   the  FDWERRORCLR   ioctl.
	 * Only writes that were attempted but failed due to a physical  media
	 * error are logged. write(2) calls that fail and return an error code
	 * to the user process are not counted. */
	__UINT32_TYPE__   write_errors;       /* number of physical write errors encountered */
	__ULONGPTR_TYPE__ first_error_sector; /* position of first and last write errors */
	__INT32_TYPE__    first_error_generation;
	__ULONGPTR_TYPE__ last_error_sector;
	__INT32_TYPE__    last_error_generation;
	__UINT32_TYPE__   badness; /* highest retry count for a read or write operation */
};

struct floppy_raw_cmd {
	__UINT32_TYPE__ flags;
#define FD_RAW_READ            0x01
#define FD_RAW_WRITE           0x02
#define FD_RAW_NO_MOTOR        0x04
#define FD_RAW_DISK_CHANGE     0x04 /* out: disk change flag was set */
#define FD_RAW_INTR            0x08 /* wait for an interrupt */
#define FD_RAW_SPIN            0x10 /* spin up the disk for this command */
#define FD_RAW_NO_MOTOR_AFTER  0x20 /* switch the motor off after command completion */
#define FD_RAW_NEED_DISK       0x40 /* this command needs a disk to be present */
#define FD_RAW_NEED_SEEK       0x80 /* this command uses an implied seek (soft) */
	/* more "in" flags */
#define FD_RAW_MORE            0x100 /* more records follow */
#define FD_RAW_STOP_IF_FAILURE 0x200 /* stop if we encounter a failure */
#define FD_RAW_STOP_IF_SUCCESS 0x400 /* stop if command successful */
#define FD_RAW_SOFTFAILURE     0x800 /* consider the return value for failure detection too */
	/* more "out" flags */
#define FD_RAW_FAILURE     0x10000 /* command sent to fdc, fdc returned error */
#define FD_RAW_HARDFAILURE 0x20000 /* fdc had to be reset, or timed out */
	void                  *data;
	char                  *kernel_data;   /* location of data buffer in the kernel */
	struct floppy_raw_cmd *next;          /* used for chaining of raw cmd's within the kernel */
	__LONGPTR_TYPE__       length;        /* in: length of dma transfer. out: remaining bytes */
	__LONGPTR_TYPE__       phys_length;   /* physical length, if different from dma length */
	__INT32_TYPE__         buffer_length; /* length of allocated buffer */
	__UINT8_TYPE__         rate;
	__UINT8_TYPE__         cmd_count;
	__UINT8_TYPE__         cmd[16];
	__UINT8_TYPE__         reply_count;
	__UINT8_TYPE__         reply[16];
	__INT32_TYPE__         track;
	__INT32_TYPE__         resultcode;
	__INT32_TYPE__         reserved1;
	__INT32_TYPE__         reserved2;
};


#endif /* __CC__ */

#define FD_FILL_BYTE 0xf6 /* format fill byte. */
#define FDHAVEBATCHEDRAWCMD

#define FDCLRPRM       _IO(2, 0x41)
#define FDSETPRM       _IOW(2, 0x42, struct floppy_struct)
#define FDSETMEDIAPRM  FDSETPRM
#define FDDEFPRM       _IOW(2, 0x43, struct floppy_struct)
#define FDGETPRM       _IOR(2, 0x04, struct floppy_struct)
#define FDDEFMEDIAPRM  FDDEFPRM
#define FDGETMEDIAPRM  FDGETPRM
#define FDMSGON        _IO(2, 0x45)
#define FDMSGOFF       _IO(2, 0x46)
#define FDFMTBEG       _IO(2, 0x47)
#define FDFMTTRK       _IOW(2, 0x48, struct format_descr)
#define FDFMTEND       _IO(2, 0x49)
#define FDSETEMSGTRESH _IO(2, 0x4a)
#define FDFLUSH        _IO(2, 0x4b)
#define FDSETMAXERRS   _IOW(2, 0x4c, struct floppy_max_errors)
#define FDGETMAXERRS   _IOR(2, 0x0e, struct floppy_max_errors)
#define FDGETDRVTYP    _IOR(2, 0x0f, floppy_drive_name)
#define FDSETDRVPRM    _IOW(2, 0x90, struct floppy_drive_params)
#define FDGETDRVPRM    _IOR(2, 0x11, struct floppy_drive_params)
#define FDGETDRVSTAT   _IOR(2, 0x12, struct floppy_drive_struct)
#define FDPOLLDRVSTAT  _IOR(2, 0x13, struct floppy_drive_struct)
#define FDRESET        _IO(2, 0x54)
#define FDGETFDCSTAT   _IOR(2, 0x15, struct floppy_fdc_state)
#define FDWERRORCLR    _IO(2, 0x56)
#define FDWERRORGET    _IOR(2, 0x17, struct floppy_write_errors)
#define FDRAWCMD       _IO(2, 0x58)
#define FDTWADDLE      _IO(2, 0x59)
#define FDEJECT        _IO(2, 0x5a)

__DECL_END

#endif /* _LINUX_FD_H */
