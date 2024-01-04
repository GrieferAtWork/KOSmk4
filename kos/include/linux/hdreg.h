/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Linux (/usr/include/linux/hdreg.h) */
#ifndef _LINUX_HDREG_H
#define _LINUX_HDREG_H 1

#include <__stdinc.h>

#include <hybrid/__bitfield.h>
#include <hybrid/typecore.h>

#include <asm/ioctl.h>
#include <compat/config.h>

__DECL_BEGIN

/* Taken/Derived from /usr/include/linux/hdreg.h */


/*efine HDIO_                  _IO(0x03, 0x00)  * ... */
#define HDIO_GETGEO            _IO(0x03, 0x01) /* [TYPE(struct hd_geometry)] Get device geometry */
#define HDIO_GET_UNMASKINTR    _IO(0x03, 0x02) /* ??? */
#define HDIO_GET_MULTCOUNT     _IO(0x03, 0x04) /* ??? */
#define HDIO_GET_QDMA          _IO(0x03, 0x05) /* ??? */
#define HDIO_SET_XFER          _IO(0x03, 0x06) /* ??? */
#define HDIO_OBSOLETE_IDENTITY _IO(0x03, 0x07) /* ??? */
#define HDIO_GET_KEEPSETTINGS  _IO(0x03, 0x08) /* ??? */
#define HDIO_GET_32BIT         _IO(0x03, 0x09) /* ??? */
#define HDIO_GET_NOWERR        _IO(0x03, 0x0a) /* ??? */
#define HDIO_GET_DMA           _IO(0x03, 0x0b) /* [TYPE(int)] Get use-dma flag */
#define HDIO_GET_NICE          _IO(0x03, 0x0c) /* ??? */
#define HDIO_GET_IDENTITY      _IO(0x03, 0x0d) /* [TYPE(struct hd_driveid)] Get IDE identification info */
#define HDIO_GET_WCACHE        _IO(0x03, 0x0e) /* [TYPE(int)] Get write cache mode on|off */
#define HDIO_GET_ACOUSTIC      _IO(0x03, 0x0f) /* ??? */
#define HDIO_GET_ADDRESS       _IO(0x03, 0x10) /* ??? */
#define HDIO_GET_BUSSTATE      _IO(0x03, 0x1a) /* [TYPE(int)] get the bus state of the hwif (One of `BUSSTATE_*') */
#define HDIO_TRISTATE_HWIF     _IO(0x03, 0x1b) /* ??? */
#define HDIO_DRIVE_RESET       _IO(0x03, 0x1c) /* Execute a device reset */
#define HDIO_DRIVE_TASKFILE    _IO(0x03, 0x1d) /* ??? */
#define HDIO_DRIVE_TASK        _IO(0x03, 0x1e) /* ??? */
#define HDIO_DRIVE_CMD_AEB     HDIO_DRIVE_TASK
#define HDIO_DRIVE_CMD         _IO(0x03, 0x1f) /* ??? */
/*efine HDIO_                  _IO(0x03, 0x20)  * ... */
#define HDIO_SET_MULTCOUNT     _IO(0x03, 0x21) /* ??? */
#define HDIO_SET_UNMASKINTR    _IO(0x03, 0x22) /* ??? */
#define HDIO_SET_KEEPSETTINGS  _IO(0x03, 0x23) /* ??? */
#define HDIO_SET_32BIT         _IO(0x03, 0x24) /* ??? */
#define HDIO_SET_NOWERR        _IO(0x03, 0x25) /* ??? */
#define HDIO_SET_DMA           _IO(0x03, 0x26) /* ??? */
#define HDIO_SET_PIO_MODE      _IO(0x03, 0x27) /* ??? */
#define HDIO_SCAN_HWIF         _IO(0x03, 0x28) /* ??? */
#define HDIO_UNREGISTER_HWIF   _IO(0x03, 0x2a) /* ??? */
#define HDIO_SET_WCACHE        _IO(0x03, 0x2b) /* [TYPE(int)] change write cache enable-disable */
#define HDIO_SET_NICE          _IO(0x03, 0x29) /* ??? */
#define HDIO_SET_ACOUSTIC      _IO(0x03, 0x2c) /* ??? */
#define HDIO_SET_BUSSTATE      _IO(0x03, 0x2d) /* ??? */
#define HDIO_SET_QDMA          _IO(0x03, 0x2e) /* ??? */
#define HDIO_SET_ADDRESS       _IO(0x03, 0x2f) /* ??? */
/*efine HDIO_                  _IO(0x03, 0x30)  * ... */
/*efine HDIO_                  _IO(0x03, 0x31)  * ... */
/*efine HDIO_                  _IO(0x03, 0x32)  * ... */
/*efine HDIO_                  _IO(0x03, 0x33)  * ... */
/*efine HDIO_                  _IO(0x03, 0x34)  * ... */
/*efine HDIO_                  _IO(0x03, 0x35)  * ... */
/*efine HDIO_                  _IO(0x03, 0x36)  * ... */
/*efine HDIO_                  _IO(0x03, 0x37)  * ... */
/*efine HDIO_                  _IO(0x03, 0x38)  * ... */
/*efine HDIO_                  _IO(0x03, 0x39)  * ... */


/* Bus states (s.a. `HDIO_GET_BUSSTATE') */
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


/* ??? */
#define HDIO_DRIVE_CMD_HDR_SIZE  4 /* ??? */
#define HDIO_DRIVE_HOB_HDR_SIZE  8 /* ??? */
#define HDIO_DRIVE_TASK_HDR_SIZE 8 /* ??? */

/* ??? */
#define IDE_DRIVE_TASK_NO_DATA   0    /* ??? */
#define IDE_DRIVE_TASK_INVALID   (-1) /* ??? */
#define IDE_DRIVE_TASK_SET_XFER  1    /* ??? */
#define IDE_DRIVE_TASK_IN        2    /* ??? */
#define IDE_DRIVE_TASK_OUT       3    /* ??? */
#define IDE_DRIVE_TASK_RAW_WRITE 4    /* ??? */

/* ??? */
#define IDE_TASKFILE_STD_IN_FLAGS  0xfe /* ??? */
#define IDE_TASKFILE_STD_OUT_FLAGS 0xfe /* ??? */
#define IDE_HOB_STD_IN_FLAGS       0x3c /* ??? */
#define IDE_HOB_STD_OUT_FLAGS      0x3c /* ??? */


/* ??? */
#define TASKFILE_NO_DATA    0x0000 /* ??? */
#define TASKFILE_IN         0x0001 /* ??? */
#define TASKFILE_MULTI_IN   0x0002 /* ??? */
#define TASKFILE_OUT        0x0004 /* ??? */
#define TASKFILE_MULTI_OUT  0x0008 /* ??? */
#define TASKFILE_IN_OUT     0x0010 /* ??? */
#define TASKFILE_IN_DMA     0x0020 /* ??? */
#define TASKFILE_OUT_DMA    0x0040 /* ??? */
#define TASKFILE_IN_DMAQ    0x0080 /* ??? */
#define TASKFILE_OUT_DMAQ   0x0100 /* ??? */
#define TASKFILE_P_IN       0x0200 /* ??? */
#define TASKFILE_P_OUT      0x0400 /* ??? */
#define TASKFILE_P_IN_DMA   0x0800 /* ??? */
#define TASKFILE_P_OUT_DMA  0x1000 /* ??? */
#define TASKFILE_P_IN_DMAQ  0x2000 /* ??? */
#define TASKFILE_P_OUT_DMAQ 0x4000 /* ??? */
#define TASKFILE_48         0x8000 /* ??? */
#define TASKFILE_INVALID    0x7fff /* ??? */


/* Drive commands (for `ATA_COMMAND' from <hw/disk/ata.h>) */
#define WIN_NOP                    0x00 /* ??? */
/*efine WIN_                       0x01  * ... */
/*efine WIN_                       0x02  * ... */
#define CFA_REQ_EXT_ERROR_CODE     0x03 /* ??? */
/*efine WIN_                       0x04  * ... */
/*efine WIN_                       ....  * ... */
/*efine WIN_                       0x07  * ... */
#define WIN_SRST                   0x08 /* ??? */
#define WIN_DEVICE_RESET           0x08 /* ??? */
/*efine WIN_                       0x09  * ... */
/*efine WIN_                       ....  * ... */
/*efine WIN_                       0x0f  * ... */
#define WIN_RECAL                  0x10 /* ??? */
#define WIN_RESTORE                WIN_RECAL
/*efine WIN_                       0x11  * ... */
/*efine WIN_                       ....  * ... */
/*efine WIN_                       0x1f  * ... */
#define WIN_READ                   0x20 /* ??? */
#define WIN_READ_ONCE              0x21 /* ??? */
#define WIN_READ_LONG              0x22 /* ??? */
#define WIN_READ_LONG_ONCE         0x23 /* ??? */
#define WIN_READ_EXT               0x24 /* ??? */
#define WIN_READDMA_EXT            0x25 /* ??? */
#define WIN_READDMA_QUEUED_EXT     0x26 /* ??? */
#define WIN_READ_NATIVE_MAX_EXT    0x27 /* ??? */
#define WIN_MULTREAD_EXT           0x29 /* ??? */
/*efine WIN_                       0x2a  * ... */
/*efine WIN_                       ....  * ... */
/*efine WIN_                       0x2f  * ... */
#define WIN_WRITE                  0x30 /* ??? */
#define WIN_WRITE_ONCE             0x31 /* ??? */
#define WIN_WRITE_LONG             0x32 /* ??? */
#define WIN_WRITE_LONG_ONCE        0x33 /* ??? */
#define WIN_WRITE_EXT              0x34 /* ??? */
#define WIN_WRITEDMA_EXT           0x35 /* ??? */
#define WIN_WRITEDMA_QUEUED_EXT    0x36 /* ??? */
#define WIN_SET_MAX_EXT            0x37 /* ??? */
#define CFA_WRITE_SECT_WO_ERASE    0x38 /* ??? */
#define WIN_MULTWRITE_EXT          0x39 /* ??? */
/*efine WIN_                       0x3a  * ... */
/*efine WIN_                       0x3b  * ... */
#define WIN_WRITE_VERIFY           0x3c /* ??? */
/*efine WIN_                       0x3d  * ... */
/*efine WIN_                       0x3e  * ... */
/*efine WIN_                       0x3f  * ... */
#define WIN_VERIFY                 0x40 /* ??? */
#define WIN_VERIFY_ONCE            0x41 /* ??? */
#define WIN_VERIFY_EXT             0x42 /* ??? */
/*efine WIN_                       0x43  * ... */
/*efine WIN_                       ....  * ... */
/*efine WIN_                       0x4f  * ... */
#define WIN_FORMAT                 0x50 /* ??? */
/*efine WIN_                       0x51  * ... */
/*efine WIN_                       ....  * ... */
/*efine WIN_                       0x5f  * ... */
#define WIN_INIT                   0x60 /* ??? */
/*efine WIN_                       0x61  * ... */
/*efine WIN_                       ....  * ... */
/*efine WIN_                       0x6f  * ... */
#define WIN_SEEK                   0x70 /* ??? */
/*efine WIN_                       0x71  * ... */
/*efine WIN_                       ....  * ... */
/*efine WIN_                       0x86  * ... */
#define CFA_TRANSLATE_SECTOR       0x87 /* ??? */
/*efine WIN_                       0x88  * ... */
/*efine WIN_                       ....  * ... */
/*efine WIN_                       0x8f  * ... */
#define WIN_DIAGNOSE               0x90 /* ??? */
#define WIN_SPECIFY                0x91 /* ??? */
#define WIN_DOWNLOAD_MICROCODE     0x92 /* ??? */
#define WIN_STANDBYNOW2            0x94 /* ??? */
#define WIN_STANDBY2               0x96 /* ??? */
#define WIN_SETIDLE2               0x97 /* ??? */
#define WIN_CHECKPOWERMODE2        0x98 /* ??? */
#define WIN_SLEEPNOW2              0x99 /* ??? */
/*efine WIN_                       0x9a  * ... */
/*efine WIN_                       ....  * ... */
/*efine WIN_                       0x9f  * ... */
#define WIN_PACKETCMD              0xa0 /* ??? */
#define WIN_PIDENTIFY              0xa1 /* ??? */
#define WIN_QUEUED_SERVICE         0xa2 /* ??? */
/*efine WIN_                       0xa3  * ... */
/*efine WIN_                       ....  * ... */
/*efine WIN_                       0xaf  * ... */
#define WIN_SMART                  0xb0 /* ??? */
/*efine WIN_                       0xb1  * ... */
/*efine WIN_                       ....  * ... */
/*efine WIN_                       0xbf  * ... */
#define CFA_ERASE_SECTORS          0xc0 /* ??? */
/*efine WIN_                       0xc1  * ... */
/*efine WIN_                       0xc2  * ... */
/*efine WIN_                       0xc3  * ... */
#define WIN_MULTREAD               0xc4 /* ??? */
#define WIN_MULTWRITE              0xc5 /* ??? */
#define WIN_SETMULT                0xc6 /* ??? */
#define WIN_READDMA_QUEUED         0xc7 /* ??? */
#define WIN_READDMA                0xc8 /* ??? */
#define WIN_READDMA_ONCE           0xc9 /* ??? */
#define WIN_WRITEDMA               0xca /* ??? */
#define WIN_WRITEDMA_ONCE          0xcb /* ??? */
#define WIN_WRITEDMA_QUEUED        0xcc /* ??? */
#define CFA_WRITE_MULTI_WO_ERASE   0xcd /* ??? */
/*efine WIN_                       0xce  * ... */
/*efine WIN_                       ....  * ... */
/*efine WIN_                       0xd9  * ... */
#define WIN_GETMEDIASTATUS         0xda /* ??? */
#define WIN_ACKMEDIACHANGE         0xdb /* ??? */
#define WIN_POSTBOOT               0xdc /* ??? */
#define WIN_PREBOOT                0xdd /* ??? */
#define WIN_DOORLOCK               0xde /* ??? */
#define WIN_DOORUNLOCK             0xdf /* ??? */
#define WIN_STANDBYNOW1            0xe0 /* ??? */
#define WIN_IDLEIMMEDIATE          0xe1 /* ??? */
#define WIN_STANDBY                0xe2 /* ??? */
#define WIN_SETIDLE1               0xe3 /* ??? */
#define WIN_READ_BUFFER            0xe4 /* ??? */
#define WIN_CHECKPOWERMODE1        0xe5 /* ??? */
#define WIN_SLEEPNOW1              0xe6 /* ??? */
#define WIN_FLUSH_CACHE            0xe7 /* ??? */
#define WIN_WRITE_BUFFER           0xe8 /* ??? */
#define WIN_WRITE_SAME             0xe9 /* ??? */
#define WIN_FLUSH_CACHE_EXT        0xea /* ??? */
#define WIN_IDENTIFY               0xec /* ??? */
#define WIN_MEDIAEJECT             0xed /* ??? */
#define WIN_IDENTIFY_DMA           0xee /* ??? */
#define WIN_SETFEATURES            0xef /* ??? */
#define EXABYTE_ENABLE_NEST        0xf0 /* ??? */
#define WIN_SECURITY_SET_PASS      0xf1 /* ??? */
#define WIN_SECURITY_UNLOCK        0xf2 /* ??? */
#define WIN_SECURITY_ERASE_PREPARE 0xf3 /* ??? */
#define WIN_SECURITY_ERASE_UNIT    0xf4 /* ??? */
#define WIN_SECURITY_FREEZE_LOCK   0xf5 /* ??? */
#define WIN_SECURITY_DISABLE       0xf6 /* ??? */
#define WIN_READ_NATIVE_MAX        0xf8 /* ??? */
#define WIN_SET_MAX                0xf9 /* ??? */
/*efine WIN_                       0xfa  * ... */
#define DISABLE_SEAGATE            0xfb /* ??? */
/*efine WIN_                       0xfc  * ... */
/*efine WIN_                       ....  * ... */
/*efine WIN_                       0xff  * ... */

/* Sub-commands for `WIN_SMART' */
#define SMART_READ_VALUES       0xd0 /* ??? */
#define SMART_READ_THRESHOLDS   0xd1 /* ??? */
#define SMART_AUTOSAVE          0xd2 /* ??? */
#define SMART_SAVE              0xd3 /* ??? */
#define SMART_IMMEDIATE_OFFLINE 0xd4 /* ??? */
#define SMART_READ_LOG_SECTOR   0xd5 /* ??? */
#define SMART_WRITE_LOG_SECTOR  0xd6 /* ??? */
#define SMART_WRITE_THRESHOLDS  0xd7 /* ??? */
#define SMART_ENABLE            0xd8 /* ??? */
#define SMART_DISABLE           0xd9 /* ??? */
#define SMART_STATUS            0xda /* ??? */
#define SMART_AUTO_OFFLINE      0xdb /* ??? */

/* ??? */
#define SMART_LCYL_PASS 0x4f /* ??? */
#define SMART_HCYL_PASS 0xc2 /* ??? */

/* Sub-commands for `WIN_SETFEATURES' */
#define SETFEATURES_EN_8BIT    0x01 /* ??? */
#define SETFEATURES_EN_WCACHE  0x02 /* ??? */
#define SETFEATURES_DIS_DEFECT 0x04 /* ??? */
#define SETFEATURES_EN_APM     0x05 /* ??? */
#define SETFEATURES_EN_SAME_R  0x22 /* ??? */
#define SETFEATURES_DIS_MSN    0x31 /* ??? */
#define SETFEATURES_DIS_RETRY  0x33 /* ??? */
#define SETFEATURES_EN_AAM     0x42 /* ??? */
#define SETFEATURES_RW_LONG    0x44 /* ??? */
#define SETFEATURES_SET_CACHE  0x54 /* ??? */
#define SETFEATURES_DIS_RLA    0x55 /* ??? */
#define SETFEATURES_EN_RI      0x5d /* ??? */
#define SETFEATURES_EN_SI      0x5e /* ??? */
#define SETFEATURES_DIS_RPOD   0x66 /* ??? */
#define SETFEATURES_DIS_ECC    0x77 /* ??? */
#define SETFEATURES_DIS_8BIT   0x81 /* ??? */
#define SETFEATURES_DIS_WCACHE 0x82 /* ??? */
#define SETFEATURES_EN_DEFECT  0x84 /* ??? */
#define SETFEATURES_DIS_APM    0x85 /* ??? */
#define SETFEATURES_EN_ECC     0x88 /* ??? */
#define SETFEATURES_EN_MSN     0x95 /* ??? */
#define SETFEATURES_EN_RETRY   0x99 /* ??? */
#define SETFEATURES_EN_RLA     0xaa /* ??? */
#define SETFEATURES_PREFETCH   0xab /* ??? */
#define SETFEATURES_EN_REST    0xac /* ??? */
#define SETFEATURES_4B_RW_LONG 0xbb /* ??? */
#define SETFEATURES_DIS_AAM    0xc2 /* ??? */
#define SETFEATURES_EN_RPOD    0xcc /* ??? */
#define SETFEATURES_DIS_RI     0xdd /* ??? */
#define SETFEATURES_EN_SAME_M  0xdd /* ??? */
#define SETFEATURES_DIS_SI     0xde /* ??? */

/* ??? */
#define SECURITY_SET_PASSWORD     0xba /* ??? */
#define SECURITY_UNLOCK           0xbb /* ??? */
#define SECURITY_ERASE_PREPARE    0xbc /* ??? */
#define SECURITY_ERASE_UNIT       0xbd /* ??? */
#define SECURITY_FREEZE_LOCK      0xbe /* ??? */
#define SECURITY_DISABLE_PASSWORD 0xbf /* ??? */

/* ??? */
#define IDE_NICE_DSC_OVERLAP   0 /* ??? */
#define IDE_NICE_ATAPI_OVERLAP 1 /* ??? */
#define IDE_NICE_1             3 /* ??? */
#define IDE_NICE_0             2 /* ??? */
#define IDE_NICE_2             4 /* ??? */



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

#define __NEW_HD_DRIVE_ID
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
#ifdef __USE_KOS_ALTERATIONS
	char                serial_no[20];    /* 0 = not_specified */
#else /* __USE_KOS_ALTERATIONS */
	__UINT8_TYPE__      serial_no[20];    /* 0 = not_specified */
#endif /* !__USE_KOS_ALTERATIONS */
	__UINT16_TYPE__     buf_type;         /* Retired */
	__UINT16_TYPE__     buf_size;         /* Retired, 512 byte increments
	                                       * 0 = not_specified */
	__UINT16_TYPE__     ecc_bytes;        /* for r/w long cmds; 0 = not_specified */
#ifdef __USE_KOS_ALTERATIONS
	char                fw_rev[8];        /* 0 = not_specified */
	char                model[40];        /* 0 = not_specified */
#else /* __USE_KOS_ALTERATIONS */
	__UINT8_TYPE__      fw_rev[8];        /* 0 = not_specified */
	__UINT8_TYPE__      model[40];        /* 0 = not_specified */
#endif /* !__USE_KOS_ALTERATIONS */
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
	                                       * 15:2:  reserved
	                                       *  1:0:  00: not supported
	                                       *        01: supported
	                                       *        10: reserved
	                                       *        11: reserved */
	__UINT16_TYPE__     dlf;              /* (word 128)
	                                       * device lock function
	                                       * 15:9:  reserved
	                                       *  8:    security level 1:max 0:high
	                                       *  7:6:  reserved
	                                       *  5:    enhanced erase
	                                       *  4:    expire
	                                       *  3:    frozen
	                                       *  2:    locked
	                                       *  1:    en/disabled
	                                       *  0:    capability */
	__UINT16_TYPE__     csfo;             /*  (word 129)
	                                       * current set features options
	                                       * 15:4:  reserved
	                                       *  3:    auto reassign
	                                       *  2:    reverting
	                                       *  1:    read-look-ahead
	                                       *  0:    write cache */
	__UINT16_TYPE__     words130_155[26]; /* reserved vendor words 130-155 */
	__UINT16_TYPE__     word156;          /* reserved vendor word 156 */
	__UINT16_TYPE__     words157_159[3];  /* reserved vendor words 157-159 */
	__UINT16_TYPE__     cfa_power;        /* (word 160) CFA Power Mode
	                                       * 15:   word 160 supported
	                                       * 14:   reserved
	                                       * 13:   reserved
	                                       * 12:   reserved
	                                       * 11:0: reserved */
	__UINT16_TYPE__     words161_175[15]; /* Reserved for CFA */
	__UINT16_TYPE__     words176_205[30]; /* Current Media Serial Number */
	__UINT16_TYPE__     words206_254[49]; /* reserved words 206-254 */
	__UINT16_TYPE__     integrity_word;   /* (word 255)
	                                       * 15:8: Checksum
	                                       *  7:0: Signature */
};

typedef __UINT8_TYPE__ task_ioreg_t;
typedef __ULONGPTR_TYPE__ sata_ioreg_t;

typedef union ide_reg_valid_s {
	__UINT16_TYPE__ all;
	struct {
		__HYBRID_BITFIELD8_T data : 1;
		__HYBRID_BITFIELD8_T error_feature : 1;
		__HYBRID_BITFIELD8_T sector : 1;
		__HYBRID_BITFIELD8_T nsector : 1;
		__HYBRID_BITFIELD8_T lcyl : 1;
		__HYBRID_BITFIELD8_T hcyl : 1;
		__HYBRID_BITFIELD8_T select : 1;
		__HYBRID_BITFIELD8_T status_command : 1;

		__HYBRID_BITFIELD8_T data_hob : 1;
		__HYBRID_BITFIELD8_T error_feature_hob : 1;
		__HYBRID_BITFIELD8_T sector_hob : 1;
		__HYBRID_BITFIELD8_T nsector_hob : 1;
		__HYBRID_BITFIELD8_T lcyl_hob : 1;
		__HYBRID_BITFIELD8_T hcyl_hob : 1;
		__HYBRID_BITFIELD8_T select_hob : 1;
		__HYBRID_BITFIELD8_T control_hob : 1;
	} b;
} ide_reg_valid_t;

typedef struct ide_task_request_s {
	__UINT8_TYPE__ io_ports[8];
	__UINT8_TYPE__ hob_ports[8];
	ide_reg_valid_t out_flags;
	ide_reg_valid_t in_flags;
	__INT32_TYPE__ data_phase;
	__INT32_TYPE__ req_cmd;
	__ULONGPTR_TYPE__ out_size;
	__ULONGPTR_TYPE__ in_size;
} ide_task_request_t;

typedef struct ide_ioctl_request_s {
	ide_task_request_t *task_request;
	__BYTE_TYPE__ *out_buffer;
	__BYTE_TYPE__ *in_buffer;
} ide_ioctl_request_t;

struct hd_drive_cmd_hdr {
	__UINT8_TYPE__ command;
	__UINT8_TYPE__ sector_number;
	__UINT8_TYPE__ feature;
	__UINT8_TYPE__ sector_count;
};

typedef struct hd_drive_task_hdr {
	__UINT8_TYPE__ data;
	__UINT8_TYPE__ feature;
	__UINT8_TYPE__ sector_count;
	__UINT8_TYPE__ sector_number;
	__UINT8_TYPE__ low_cylinder;
	__UINT8_TYPE__ high_cylinder;
	__UINT8_TYPE__ device_head;
	__UINT8_TYPE__ command;
} task_struct_t;

typedef struct hd_drive_hob_hdr {
	__UINT8_TYPE__ data;
	__UINT8_TYPE__ feature;
	__UINT8_TYPE__ sector_count;
	__UINT8_TYPE__ sector_number;
	__UINT8_TYPE__ low_cylinder;
	__UINT8_TYPE__ high_cylinder;
	__UINT8_TYPE__ device_head;
	__UINT8_TYPE__ control;
} hob_struct_t;
#endif /* __CC__ */

__DECL_END

#endif /* !_LINUX_HDREG_H */
