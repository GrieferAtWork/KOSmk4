/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_SMP_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_SMP_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/__asm.h>
#include <hybrid/wordbits.h>

DECL_BEGIN



/* X86 SMP control / initialization structures. */
#define MPFPS_ALIGN                   16
#define MP_FLOATING_POINTER_SIGNATURE ENCODE_INT32('_', 'M', 'P', '_')

#define APICVER_82489DX    0x00
#define APICVER_INTEGRATED 0x10

#ifdef __CC__
typedef struct ATTR_PACKED {
	char       mp_sig[4];          /* == "_MP_". */
	u32        mp_cfgtab;          /* [0..1] Physical address of the configuration table (`MpConfigurationTable'). */
	u8         mp_length;          /* Size of this structure (in 16-byte increments). */
	u8         mp_specrev;         /* MP version. */
	u8         mp_chksum;          /* memsum()-alignment to ZERO. */
	u8         mp_defcfg;          /* If this  is  not  zero, then  configuration_table  should  be
	                                * ignored and a default configuration should be loaded instead. */
	u32        mp_features;        /* If bit 7 (0x80) is set, then the IMCR is present and PIC mode is being used.
	                                * Otherwise  virtual   wire   mode   is;  all   other   bits   are   reserved. */
} MpFloatingPointerStructure;

typedef struct ATTR_PACKED {
	char       tab_sig[4];         /* == "PCMP". */
	u16        tab_length;         /* Length of this header + following vector. */
	u8         tab_specrev;        /* Specifications revision. */
	u8         tab_chksum;         /* memsum()-alignment to ZERO. */
	char       tab_oemid[8];       /* OEM ID (Padded with spaces). */
	char       tab_productid[12];  /* Product ID (Padded with spaces). */
	u32        tab_oemtab;         /* [0..1] Address of the OEM table. */
	u16        tab_oemtabsize;     /* Size of the OEM table. */
	u16        tab_entryc;         /* Amount of entries following this configuration table. */
	u32        tab_lapicaddr;      /* Memory-mapped address of local APICs. */
	u16        tab_extab_length;   /* Extended table length. */
	u8         tab_extab_checksum; /* Extended table checksum. */
	u8         tab_reserved;       /* Reserved... */
	/* Inlined  vector of MP  entries, containing `tab_entryc' entries
	 * for a total of `tab_length-sizeof(MpConfigurationTable)' bytes. */
} MpConfigurationTable;

typedef struct ATTR_PACKED {
#define MPCFG_PROCESSOR            0            /* Processor configuration entry. */
#define MPCFG_BUS                  1            /* BUS configuration entry. */
#define MPCFG_IOAPIC               2            /* IO-APIC configuration entry. */
#define MPCFG_INT_IO               3            /* IO-Interrupt configuration entry. */
#define MPCFG_INT_LOCAL            4            /* Local Interrupt configuration entry. */
	u8                 mp_type;                 /* One of `MPCFG_*'. */
	union ATTR_PACKED {
		/* Type-specific configuration data. */

		struct ATTR_PACKED {
			u8         p_lapicid;               /* Local APIC ID number. */
			u8         p_lapicver;              /* APIC versions (APICVER_*). */
#define MP_PROCESSOR_FENABLED       0x01        /* Processor is available. */
#define MP_PROCESSOR_FBOOTPROCESSOR 0x02        /* This is the boot processor (The one you're probably running on right now). */
			u8         p_cpuflag;               /* Set of `MP_PROCESSOR_F*'. */
			u32        p_cpusig;                /* Processor Type signature. */
			u32        p_features;              /* CPUID feature value. */
			u32        p_reserved[2];           /* Reserved... */
		}              mp_processor;            /* MPCFG_PROCESSOR */

		struct ATTR_PACKED {
			u8         b_busid;                 /* ID number for this bus. */
			char       b_bustype[6];            /* Identifier string. */
		}              mp_bus;                  /* MPCFG_BUS */

		struct ATTR_PACKED {
			u8         io_apicid;               /* ID of this I/O APIC. */
			u8         io_apicver;              /* This I/O APIC's version number (APICVER_*). */
#define MP_IOAPIC_FNORMAL           0x00        /* ??? */
#define MP_IOAPIC_FENABLED          0x01        /* The IOAPIC is available. */
			u8         io_flags;                /* Set of `MP_IOAPIC_F*'. */
			u32        io_apicaddr;             /* Physical address of this I/O APIC. */
		}              mp_ioapic;               /* MPCFG_IOAPIC */

		struct ATTR_PACKED {
#define MP_INT_IRQTYPE_INT          0           /* regular INTerrupt. */
#define MP_INT_IRQTYPE_NMI          1           /* Non-Maskable Interrupt */
#define MP_INT_IRQTYPE_SMI          2           /* System Management Interrupt. */
#define MP_INT_IRQTYPE_EXTINT       3           /* ??? */
			u8         i_irqtype;               /* One of `MP_INT_IRQTYPE_*' */
#define MP_INT_IRQPOL_MASK          0x03        /* Mask of IRQ Polarity options. */
#define MP_INT_IRQPOL_DEFAULT       0x00        /* ??? */
#define MP_INT_IRQPOL_HIGH          0x01        /* ??? */
#define MP_INT_IRQPOL_RESERVED      0x02        /* ??? */
#define MP_INT_IRQPOL_LOW           0x03        /* ??? */
#define MP_INT_IRQTRIGER_MASK       0x0C        /* Mask of IRQ Trigger options. */
#define MP_INT_IRQTRIGER_DEFAULT    0x00        /* ??? */
#define MP_INT_IRQTRIGER_EDGE       0x04        /* ??? */
#define MP_INT_IRQTRIGER_RESERVED   0x08        /* ??? */
#define MP_INT_IRQTRIGER_LEVEL      0x0C        /* ??? */
			u16        i_irqflag;               /* Or'd together `MP_INT_IRQPOL_MASK' and `MP_INT_IRQTRIGER_MASK'. */
			u8         i_srcbus;                /* Source bus ID number. */
			u8         i_srcbusirq;             /* Source bus IRQ signal number. */
			u8         i_dstapic;               /* ID number of the connected I/O APIC, or 0xff for all. */
			u8         i_dstirq;                /* IRQ pin number to which the signal is connected. */
		}              mp_interrupt;            /* MPCFG_INT_IO or MPCFG_INT_LOCAL */
	};
} MpConfigurationEntry;


#ifdef BUILDING_KERNEL_CORE
INTDEF u8 x86_smp_entry_page;
#endif /* BUILDING_KERNEL_CORE */

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_SMP_H */
