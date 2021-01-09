/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LINUX_HDREG_H
#define _LINUX_HDREG_H 1

#include <__stdinc.h>
#include <asm/ioctl.h>
#include <compat/config.h>
#include <hybrid/typecore.h>

__DECL_BEGIN

/* Taken/Derived from /usr/include/linux/hdreg.h */


#ifdef __CC__
struct hd_geometry {
	__UINT8_TYPE__    heads;
	__UINT8_TYPE__    sectors;
	__UINT16_TYPE__   cylinders;
	__ULONGPTR_TYPE__ start;
};
#ifdef __ARCH_HAVE_COMPAT
struct hd_geometry_compat {
	__UINT8_TYPE__             heads;
	__UINT8_TYPE__             sectors;
	__UINT16_TYPE__            cylinders;
	__ARCH_COMPAT_LONGPTR_TYPE start;
};
#endif /* __ARCH_HAVE_COMPAT */
#endif /* __CC__ */

#define HDIO_GETGEO       _IO(0x03, 0x01) /* [TYPE(struct hd_geometry)] Get device geometry */
#define HDIO_GET_DMA      _IO(0x03, 0x0b) /* [TYPE(int)] Get use-dma flag */
#define HDIO_GET_IDENTITY _IO(0x03, 0x0d) /* [TYPE(struct hd_driveid)] Get IDE identification info */
#define HDIO_GET_WCACHE   _IO(0x03, 0x0e) /* [TYPE(int)] Get write cache mode on|off */
#define HDIO_DRIVE_RESET  _IO(0x03, 0x1c) /* Execute a device reset */
#define HDIO_GET_BUSSTATE _IO(0x03, 0x1a) /* [TYPE(int)] get the bus state of the hwif (One of `BUSSTATE_*') */
#define HDIO_SET_WCACHE   _IO(0x03, 0x2b) /* [TYPE(int)] change write cache enable-disable */


/* bus states */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	BUSSTATE_OFF = 0,
	BUSSTATE_ON,
	BUSSTATE_TRISTATE
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define BUSSTATE_OFF      BUSSTATE_OFF
#define BUSSTATE_ON       BUSSTATE_ON
#define BUSSTATE_TRISTATE BUSSTATE_TRISTATE
#else /* __COMPILER_PREFERR_ENUMS */
#define BUSSTATE_OFF      0
#define BUSSTATE_ON       1
#define BUSSTATE_TRISTATE 2
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

#ifdef __CC__
struct hd_driveid {
	__UINT16_TYPE__     config;           /* lots of obsolete bit flags */
	__UINT16_TYPE__     cyls;             /* Obsolete, "physical" cyls */
	__UINT16_TYPE__     reserved2;        /* reserved (word 2) */
	__UINT16_TYPE__     heads;            /* Obsolete, "physical" heads */
	__UINT16_TYPE__     track_bytes;      /* unformatted bytes per track */
	__UINT16_TYPE__     sector_bytes;     /* unformatted bytes per sector */
	__UINT16_TYPE__     sectors;          /* Obsolete, "physical" sectors per track */
	__UINT16_TYPE__     vendor0;          /* vendor unique */
	__UINT16_TYPE__     vendor1;          /* vendor unique */
	__UINT16_TYPE__     vendor2;          /* Retired vendor unique */
	__UINT8_TYPE__      serial_no[20];    /* 0 = not_specified */
	__UINT16_TYPE__     buf_type;         /* Retired */
	__UINT16_TYPE__     buf_size;         /* Retired, 512 byte increments
	                                       * 0 = not_specified */
	__UINT16_TYPE__     ecc_bytes;        /* for r/w long cmds; 0 = not_specified */
	__UINT8_TYPE__      fw_rev[8];        /* 0 = not_specified */
	__UINT8_TYPE__      model[40];        /* 0 = not_specified */
	__UINT8_TYPE__      max_multsect;     /* 0=not_implemented */
	__UINT8_TYPE__      vendor3;          /* vendor unique */
	__UINT16_TYPE__     dword_io;         /* 0=not_implemented; 1=implemented */
	__UINT8_TYPE__      vendor4;          /* vendor unique */
	__UINT8_TYPE__      capability;       /* (upper byte of word 49)
	                                       *  3: IORDYsup
	                                       *  2: IORDYsw
	                                       *  1: LBA
	                                       *  0: DMA */
#define HD_DRIVEID_CAPABILITY_DMA      0x01
#define HD_DRIVEID_CAPABILITY_LBA      0x02
#define HD_DRIVEID_CAPABILITY_IORDYSW  0x04
#define HD_DRIVEID_CAPABILITY_IORDYSUP 0x08
	__UINT16_TYPE__     reserved50;       /* reserved (word 50) */
	__UINT8_TYPE__      vendor5;          /* Obsolete, vendor unique */
	__UINT8_TYPE__      tPIO;             /* Obsolete, 0=slow, 1=medium, 2=fast */
	__UINT8_TYPE__      vendor6;          /* Obsolete, vendor unique */
	__UINT8_TYPE__      tDMA;             /* Obsolete, 0=slow, 1=medium, 2=fast */
	__UINT16_TYPE__     field_valid;      /* (word 53)
	                                       *  2: ultra_ok  word  88
	                                       *  1: eide_ok   words 64-70
	                                       *  0: cur_ok    words 54-58 */
	__UINT16_TYPE__     cur_cyls;         /* Obsolete, logical cylinders */
	__UINT16_TYPE__     cur_heads;        /* Obsolete, l heads */
	__UINT16_TYPE__     cur_sectors;      /* Obsolete, l sectors per track */
	__UINT16_TYPE__     cur_capacity0;    /* Obsolete, l total sectors on drive */
	__UINT16_TYPE__     cur_capacity1;    /* Obsolete, (2 words, misaligned int) */
	__UINT8_TYPE__      multsect;         /* current multiple sector count */
	__UINT8_TYPE__      multsect_valid;   /* when (bit0==1) multsect is ok */
	__UINT32_TYPE__     lba_capacity;     /* Obsolete, total number of sectors */
	__UINT16_TYPE__     dma_1word;        /* Obsolete, single-word dma info */
	__UINT16_TYPE__     dma_mword;        /* multiple-word dma info */
	__UINT16_TYPE__     eide_pio_modes;   /* bits 0:mode3 1:mode4 */
	__UINT16_TYPE__     eide_dma_min;     /* min mword dma cycle time (ns) */
	__UINT16_TYPE__     eide_dma_time;    /* recommended mword dma cycle time (ns) */
	__UINT16_TYPE__     eide_pio;         /* min cycle time (ns), no IORDY  */
	__UINT16_TYPE__     eide_pio_iordy;   /* min cycle time (ns), with IORDY */
	__UINT16_TYPE__     words69_70[2];    /* reserved words 69-70
	                                       * future command overlap and queuing */
	__UINT16_TYPE__     words71_74[4];    /* reserved words 71-74
	                                       * for IDENTIFY PACKET DEVICE command */
	__UINT16_TYPE__     queue_depth;      /* (word 75)
	                                       * 15:5   reserved
	                                       *  4:0   Maximum queue depth -1 */
	__UINT16_TYPE__     words76_79[4];    /* reserved words 76-79 */
	__UINT16_TYPE__     major_rev_num;    /* (word 80) */
	__UINT16_TYPE__     minor_rev_num;    /* (word 81) */
	__UINT16_TYPE__     command_set_1;    /* (word 82) supported
	                                       * 15: Obsolete
	                                       * 14: NOP command
	                                       * 13: READ_BUFFER
	                                       * 12: WRITE_BUFFER
	                                       * 11: Obsolete
	                                       * 10: Host Protected Area
	                                       *  9: DEVICE Reset
	                                       *  8: SERVICE Interrupt
	                                       *  7: Release Interrupt
	                                       *  6: look-ahead
	                                       *  5: write cache
	                                       *  4: PACKET Command
	                                       *  3: Power Management Feature Set
	                                       *  2: Removable Feature Set
	                                       *  1: Security Feature Set
	                                       *  0: SMART Feature Set */
	__UINT16_TYPE__     command_set_2;    /* (word 83)
	                                       * 15: Shall be ZERO
	                                       * 14: Shall be ONE
	                                       * 13: FLUSH CACHE EXT
	                                       * 12: FLUSH CACHE
	                                       * 11: Device Configuration Overlay
	                                       * 10: 48-bit Address Feature Set
	                                       *  9: Automatic Acoustic Management
	                                       *  8: SET MAX security
	                                       *  7: reserved 1407DT PARTIES
	                                       *  6: SetF sub-command Power-Up
	                                       *  5: Power-Up in Standby Feature Set
	                                       *  4: Removable Media Notification
	                                       *  3: APM Feature Set
	                                       *  2: CFA Feature Set
	                                       *  1: READ/WRITE DMA QUEUED
	                                       *  0: Download MicroCode */
#define HD_DRIVEID_COMMAND_SET_2_LBA48     0x0400 /* 48-bit Address Feature Set */
#define HD_DRIVEID_COMMAND_SET_2_FLUSH     0x1000 /* FLUSH CACHE */
#define HD_DRIVEID_COMMAND_SET_2_FLUSH_EXT 0x2000 /* FLUSH CACHE EXT */
	__UINT16_TYPE__     cfsse;            /* (word 84)
	                                       * cmd set-feature supported extensions
	                                       * 15:  Shall be ZERO
	                                       * 14:  Shall be ONE
	                                       * 13:6 reserved
	                                       *  5:  General Purpose Logging
	                                       *  4:  Streaming Feature Set
	                                       *  3:  Media Card Pass Through
	                                       *  2:  Media Serial Number Valid
	                                       *  1:  SMART selt-test supported
	                                       *  0:  SMART error logging */
	__UINT16_TYPE__     cfs_enable_1;     /* (word 85)
	                                       * command set-feature enabled
	                                       * 15: Obsolete
	                                       * 14: NOP command
	                                       * 13: READ_BUFFER
	                                       * 12: WRITE_BUFFER
	                                       * 11: Obsolete
	                                       * 10: Host Protected Area
	                                       *  9: DEVICE Reset
	                                       *  8: SERVICE Interrupt
	                                       *  7: Release Interrupt
	                                       *  6: look-ahead
	                                       *  5: write cache
	                                       *  4: PACKET Command
	                                       *  3: Power Management Feature Set
	                                       *  2: Removable Feature Set
	                                       *  1: Security Feature Set
	                                       *  0: SMART Feature Set */
	__UINT16_TYPE__     cfs_enable_2;     /* (word 86)
	                                       * command set-feature enabled
	                                       * 15: Shall be ZERO
	                                       * 14: Shall be ONE
	                                       * 13: FLUSH CACHE EXT
	                                       * 12: FLUSH CACHE
	                                       * 11: Device Configuration Overlay
	                                       * 10: 48-bit Address Feature Set
	                                       *  9: Automatic Acoustic Management
	                                       *  8: SET MAX security
	                                       *  7: reserved 1407DT PARTIES
	                                       *  6: SetF sub-command Power-Up
	                                       *  5: Power-Up in Standby Feature Set
	                                       *  4: Removable Media Notification
	                                       *  3: APM Feature Set
	                                       *  2: CFA Feature Set
	                                       *  1: READ/WRITE DMA QUEUED
	                                       *  0: Download MicroCode */
	__UINT16_TYPE__     csf_default;      /* (word 87)
	                                       * command set-feature default
	                                       * 15:  Shall be ZERO
	                                       * 14:  Shall be ONE
	                                       * 13:6 reserved
	                                       *  5:  General Purpose Logging enabled
	                                       *  4:  Valid CONFIGURE STREAM executed
	                                       *  3:  Media Card Pass Through enabled
	                                       *  2:  Media Serial Number Valid
	                                       *  1:  SMART selt-test supported
	                                       *  0:  SMART error logging */
	__UINT16_TYPE__     dma_ultra;        /* (word 88) */
	__UINT16_TYPE__     trseuc;           /* time required for security erase */
	__UINT16_TYPE__     trsEuc;           /* time required for enhanced erase */
	__UINT16_TYPE__     CurAPMvalues;     /* current APM values */
	__UINT16_TYPE__     mprc;             /* master password revision code */
	__UINT16_TYPE__     hw_config;        /* hardware config (word 93)
	                                       * 15: Shall be ZERO
	                                       * 14: Shall be ONE
	                                       * 13:
	                                       * 12:
	                                       * 11:
	                                       * 10:
	                                       *  9:
	                                       *  8:
	                                       *  7:
	                                       *  6:
	                                       *  5:
	                                       *  4:
	                                       *  3:
	                                       *  2:
	                                       *  1:
	                                       *  0: Shall be ONE */
	__UINT16_TYPE__     acoustic;         /* (word 94)
	                                       * 15:8 Vendor's recommended value
	                                       *  7:0 current value */
	__UINT16_TYPE__     msrqs;            /* min stream request size */
	__UINT16_TYPE__     sxfert;           /* stream transfer time */
	__UINT16_TYPE__     sal;              /* stream access latency */
	__UINT32_TYPE__     spg;              /* stream performance granularity */
	__UINT64_TYPE__     lba_capacity_2;   /* 48-bit total number of sectors */
	__UINT16_TYPE__     words104_125[22]; /* reserved words 104-125 */
	__UINT16_TYPE__     last_lun;         /* (word 126) */
	__UINT16_TYPE__     word127;          /* (word 127) Feature Set
	                                       * Removable Media Notification
	                                       * 15:2  reserved
	                                       *  1:0  00 = not supported
	                                       *       01 = supported
	                                       *       10 = reserved
	                                       *       11 = reserved */
	__UINT16_TYPE__     dlf;              /* (word 128)
	                                       * device lock function
	                                       * 15:9  reserved
	                                       *  8    security level 1:max 0:high
	                                       *  7:6  reserved
	                                       *  5    enhanced erase
	                                       *  4    expire
	                                       *  3    frozen
	                                       *  2    locked
	                                       *  1    en/disabled
	                                       *  0    capability */
	__UINT16_TYPE__     csfo;             /*  (word 129)
	                                       * current set features options
	                                       * 15:4  reserved
	                                       *  3:   auto reassign
	                                       *  2:   reverting
	                                       *  1:   read-look-ahead
	                                       *  0:   write cache */
	__UINT16_TYPE__     words130_155[26]; /* reserved vendor words 130-155 */
	__UINT16_TYPE__     word156;          /* reserved vendor word 156 */
	__UINT16_TYPE__     words157_159[3];  /* reserved vendor words 157-159 */
	__UINT16_TYPE__     cfa_power;        /* (word 160) CFA Power Mode
	                                       * 15 word 160 supported
	                                       * 14 reserved
	                                       * 13
	                                       * 12
	                                       * 11:0 */
	__UINT16_TYPE__     words161_175[15]; /* Reserved for CFA */
	__UINT16_TYPE__     words176_205[30]; /* Current Media Serial Number */
	__UINT16_TYPE__     words206_254[49]; /* reserved words 206-254 */
	__UINT16_TYPE__     integrity_word;   /* (word 255)
	                                       * 15:8 Checksum
	                                       *  7:0 Signature */
};
#endif /* __CC__ */

__DECL_END

#endif /* !_LINUX_HDREG_H */
