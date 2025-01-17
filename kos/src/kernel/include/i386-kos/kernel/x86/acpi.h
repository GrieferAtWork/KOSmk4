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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_ACPI_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_ACPI_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

DECL_BEGIN

#ifdef __CC__

#define RSDPDESCRIPTOR_ALIGN 16

typedef struct ATTR_PACKED {
	char     rsdp_signature[8];
	u8       rsdp_checksum;
	char     rsdp_oemid[6];
	u8       rsdp_revision;
	u32      rsdp_rsdtaddr; /* Physical pointer to `ACPISDTHeader' */
	/* Added in version 2.0 (`rsdp_revision >= 2'): */
	u32      rsdp_length;
	u64      rsdp_xsdtaddr;
	u8       rsdp_extchecksum;
	u8       rsdp_reserved[3];
} RSDPDescriptor;

typedef struct ATTR_PACKED {
	char                  rsdp_signature[4];
	u32                   rsdp_length;
	u8                    rsdp_revision;
	u8                    rsdp_checksum;
	char                  rsdp_oemid[6];
	char                  rsdp_oemtableid[8];
	u32                   rsdp_oemrevision;
	u32                   rsdp_creatorid;
	u32                   rsdp_creatorrevision;
/*#if acpi_mode == ACPI_MODE_RSDT*/
/*	PHYS32 ACPISDTHeader *rsdp_sdts[(rsdp_length - offsetof(ACPISDTHeader, rsdp_sdts)) / 4]; */
/*#elif acpi_mode == ACPI_MODE_XSDT*/
/*	PHYS64 ACPISDTHeader *xsdp_sdts[(rsdp_length - offsetof(ACPISDTHeader, xsdp_sdts)) / 8]; */
/*#endif*/
} ACPISDTHeader;

typedef struct ATTR_PACKED {
	uint8_t  gas_AddressSpace;
	uint8_t  gas_BitWidth;
	uint8_t  gas_BitOffset;
	uint8_t  gas_AccessSize;
	uint64_t gas_Address;
} GAS; /* GenericAddressStructure */

typedef struct ATTR_PACKED {
	ACPISDTHeader fadt_Header;   /* Signature == "FACP" */
	uint32_t      fadt_FirmwareCtrl;
	uint32_t      fadt_Dsdt;
	uint8_t       fadt_Reserved; /* field used in ACPI 1.0; no longer in use, for compatibility only */
	uint8_t       fadt_PreferredPowerManagementProfile;
	uint16_t      fadt_SCI_Interrupt;
	uint32_t      fadt_SMI_CommandPort;
	uint8_t       fadt_AcpiEnable;
	uint8_t       fadt_AcpiDisable;
	uint8_t       fadt_S4BIOS_REQ;
	uint8_t       fadt_PSTATE_Control;
	uint32_t      fadt_PM1aEventBlock;
	uint32_t      fadt_PM1bEventBlock;
	uint32_t      fadt_PM1aControlBlock;
	uint32_t      fadt_PM1bControlBlock;
	uint32_t      fadt_PM2ControlBlock;
	uint32_t      fadt_PMTimerBlock;
	uint32_t      fadt_GPE0Block;
	uint32_t      fadt_GPE1Block;
	uint8_t       fadt_PM1EventLength;
	uint8_t       fadt_PM1ControlLength;
	uint8_t       fadt_PM2ControlLength;
	uint8_t       fadt_PMTimerLength;
	uint8_t       fadt_GPE0Length;
	uint8_t       fadt_GPE1Length;
	uint8_t       fadt_GPE1Base;
	uint8_t       fadt_CStateControl;
	uint16_t      fadt_WorstC2Latency;
	uint16_t      fadt_WorstC3Latency;
	uint16_t      fadt_FlushSize;
	uint16_t      fadt_FlushStride;
	uint8_t       fadt_DutyOffset;
	uint8_t       fadt_DutyWidth;
	uint8_t       fadt_DayAlarm;
	uint8_t       fadt_MonthAlarm;
	uint8_t       fadt_Century;
	uint16_t      fadt_BootArchitectureFlags;     /* reserved in ACPI 1.0; used since ACPI 2.0+ */
	uint8_t       fadt_Reserved2;
	uint32_t      fadt_Flags;
	GAS           fadt_ResetReg;
	uint8_t       fadt_ResetValue;
	uint8_t       fadt_Reserved3[3];
	uint64_t      fadt_X_FirmwareControl;    /* 64bit pointer - Available on ACPI 2.0+ */
	uint64_t      fadt_X_Dsdt;               /* 64bit pointer - Available on ACPI 2.0+ */
	GAS           fadt_X_PM1aEventBlock;
	GAS           fadt_X_PM1bEventBlock;
	GAS           fadt_X_PM1aControlBlock;
	GAS           fadt_X_PM1bControlBlock;
	GAS           fadt_X_PM2ControlBlock;
	GAS           fadt_X_PMTimerBlock;
	GAS           fadt_X_GPE0Block;
	GAS           fadt_X_GPE1Block;
} FADT;


/* ACPI support by the host */
#define ACPI_MODE_NONE 0 /* No ACPI information available. */
#define ACPI_MODE_RSDT 4 /* RSDT was found. */
#define ACPI_MODE_XSDT 8 /* XSDT was found (preferred over `ACPI_MODE_RSDT'). */
DATDEF unsigned int acpi_mode;
DATDEF physaddr_t   acpi_root; /* [valid_if(acpi_mode != ACPI_MODE_NONE)]
                                * pointer to the RSDT or XSDT (based on `acpi_mode') */
DATDEF size_t acpi_sdt_count;  /* Length of the vector `((ACPISDTHeader *)acpi_root)->rsdp_sdts' */
#define ACPI_POINTER_SIZE  ((size_t)acpi_mode)


/* Lookup an ACPI table and store its contents in `buf', and return the number of required bytes
 * Note however that in the event of `return > buflen', data will have still been written to the
 * given buffer, leading up to `buflen'. Separately, in the event of `return < buflen', any data
 * that  could  not  be  derived  from  the  SDT  table  will  be  initialized  as  all  ZEROes.
 * Also  note  that  the caller  is  required to  ensure  that `buflen >= sizeof(ACPISDTHeader)'
 * @param: ptableaddr: When  non-NULL, filled with the physical base
 *                     address of the found SDT header upon success.
 * @return: 0 : Failed to find the ACPI table.
 * @return: * : Same as `((ACPISDTHeader *)buf)->rsdp_length' */
FUNDEF WUNUSED NONNULL((1, 2)) size_t
NOTHROW(KCALL acpi_lookup)(char const signature[4],
                           void *buf, size_t buflen,
                           physaddr_t *ptableaddr DFL(__NULLPTR));

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_ACPI_H */
