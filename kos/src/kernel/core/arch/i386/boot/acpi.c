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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_BOOT_ACPI_C
#define GUARD_KERNEL_CORE_ARCH_I386_BOOT_ACPI_C 1
#define DISABLE_BRANCH_PROFILING /* Don't profile this file */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/mman/phys.h>
#include <kernel/x86/acpi.h>

#include <hybrid/align.h>
#include <hybrid/minmax.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* ACPI support by the host */
PUBLIC unsigned int acpi_mode = ACPI_MODE_NONE;

/* [valid_if(acpi_mode != ACPI_MODE_NONE)] pointer to the RSDT or XSDT (based on `acpi_mode') */
PUBLIC physaddr_t acpi_root = 0;

/* [valid_if(acpi_mode == ACPI_MODE_RSDT)] Length of the vector `((ACPISDTHeader *)acpi_root)->rsdp_sdts' */
PUBLIC size_t acpi_sdt_count = 0;

#ifdef NO_PHYS_IDENTITY
#define copyfromphys_noidentity copyfromphys
#else /* NO_PHYS_IDENTITY */
PRIVATE ATTR_FREETEXT size_t
NOTHROW(KCALL copyfromphys_noidentity_partial)(void *__restrict dst,
                                               physaddr_t src,
                                               size_t num_bytes) {
	uintptr_t offset;
	size_t result;
	byte_t *vsrc = THIS_TRAMPOLINE;
	pagedir_pushval_t pv;
	/* NOTE: We must still preserve the trampoline here, since the trampoline
	 *       for boottask is  allocated past  the end of  the kernel's  .free
	 *       section. This is  important since the  bootloader/bios may  have
	 *       placed  various  data structures  at  that location  (on  QEMU I
	 *       noticed that the kernel's  commandline is placed directly  over-
	 *       top  of  the   boottask's  page   directory  identity   mapping)
	 *       As such, we must preserve this mapping, as things such that  the
	 *       kernel commandline are  still used  by later steps  of the  boot
	 *       process. */
	pv = pagedir_push_mapone(vsrc, src & ~(PAGESIZE - 1), PAGEDIR_PROT_READ);
	pagedir_syncone(vsrc);
	offset = (uintptr_t)(src & (PAGESIZE - 1));
	result = PAGESIZE - offset;
	if (result > num_bytes)
		result = num_bytes;
	memcpy(dst, vsrc + offset, result);
	pagedir_pop_mapone(vsrc, pv);
	return result;
}

/* Because the pyhs2virt identity mapping is initialized _after_
 * ACPI,  which needs to be done this way because pyhs2virt must
 * be able to allocate physical  memory, which requires a  prior
 * call to `kernel_initialize_minfo_makezones()', which requires
 * that memory bank initialization has been finalized, which  it
 * isn't  yet  (as indicative  of  `x86_initialize_acpi()' below
 * calling `minfo_addbank()')
 * This function behaves the same as `copyfromphys()', however
 * will not  make  use  of  the  phys2virt  identity  segment. */
PRIVATE ATTR_FREETEXT void
NOTHROW(KCALL copyfromphys_noidentity)(void *__restrict dst,
                                       physaddr_t src,
                                       size_t num_bytes) {
	for (;;) {
		size_t temp;
		temp = copyfromphys_noidentity_partial(dst, src, num_bytes);
		if (temp >= num_bytes)
			break;
		dst = (byte_t *)dst + temp;
		src += temp;
		num_bytes -= temp;
	}
}
#endif /* !NO_PHYS_IDENTITY */

PRIVATE ATTR_FREETEXT ATTR_PURE byte_t
NOTHROW(KCALL acpi_memsum)(void const *__restrict p, size_t n_bytes) {
	byte_t result = 0;
	byte_t const *iter, *end;
	end = (iter = (byte_t *)p) + n_bytes;
	for (; iter != end; ++iter)
		result += *iter;
	return result;
}

PRIVATE ATTR_FREETEXT ATTR_PURE byte_t
NOTHROW(KCALL acpi_memsum_phys)(physaddr_t p, size_t n_bytes) {
	u8 buf[256];
	byte_t result = 0;
	while (n_bytes) {
		size_t cnt = MIN(n_bytes, sizeof(buf));
		copyfromphys_noidentity(buf, p, cnt);
		result += acpi_memsum(buf, cnt);
		n_bytes -= cnt;
		p += cnt;
	}
	return result;
}


PRIVATE ATTR_FREETEXT RSDPDescriptor *
NOTHROW(KCALL RSDP_LocateInRange)(VIRT uintptr_t base, size_t bytes) {
	uintptr_t iter, end;
	/* Make sure not to search unmapped memory! */
	if (base < KERNEL_CORE_BASE) {
		base += bytes;
		if (base <= KERNEL_CORE_BASE)
			return NULL;
		bytes = base - KERNEL_CORE_BASE;
		base  = KERNEL_CORE_BASE;
	}
	if ((base + bytes) < base)
		bytes = 0 - base;
	end = (iter = (uintptr_t)base) + bytes;
	printk(FREESTR(KERN_DEBUG "[acpi] Searching for RSDPDescriptor in %p...%p\n"),
	       iter - KERNEL_CORE_BASE, (end - 1) - KERNEL_CORE_BASE);
	/* Clamp the search area to a 16-byte alignment. */
	iter = CEIL_ALIGN(iter, RSDPDESCRIPTOR_ALIGN);
	end  = FLOOR_ALIGN(end, RSDPDESCRIPTOR_ALIGN);
	for (; iter < end; iter += RSDPDESCRIPTOR_ALIGN) {
		PRIVATE union {
			char c[8];
#ifdef __x86_64__
			u64  u;
#else /* __x86_64__ */
			u32  u[2];
#endif /* !__x86_64__ */
		} const signature = {
			{ 'R', 'S', 'D', ' ', 'P', 'T', 'R', ' ' }
		};
		RSDPDescriptor *result = (RSDPDescriptor *)iter;
		/* Check for the signature. */
#ifdef __x86_64__
		if (((u64 *)result->rsdp_signature)[0] != signature.u)
			continue;
#else /* __x86_64__ */
		if (((u32 *)result->rsdp_signature)[0] != signature.u[0])
			continue;
		if (((u32 *)result->rsdp_signature)[1] != signature.u[1])
			continue;
#endif /* !__x86_64__ */
		/* When found, check the checksum. */
		if (!acpi_memsum(result, offsetafter(RSDPDescriptor, rsdp_rsdtaddr)))
			return result;
	}
	return NULL;
}

PRIVATE ATTR_FREETEXT RSDPDescriptor *
NOTHROW(KCALL RSDP_LocateDescriptor)(void) {
	RSDPDescriptor *result;
	uintptr_t base;
	base   = (uintptr_t)(*(u16 volatile *)(KERNEL_CORE_BASE + 0x40e));
	result = RSDP_LocateInRange(KERNEL_CORE_BASE + base, 1024);
	if (result)
		goto done;
	result = RSDP_LocateInRange(KERNEL_CORE_BASE + 0x0e0000, 0x020000);
done:
	return result;
}




INTERN ATTR_FREETEXT void NOTHROW(KCALL x86_initialize_acpi)(void) {
	RSDPDescriptor *rsdp;
	ACPISDTHeader header;
	/* TODO: Commandline option to override address of this structure */
	/* TODO: Commandline option to disable detection of this structure */
	rsdp = RSDP_LocateDescriptor();
	if unlikely(!rsdp) {
		printk(FREESTR(KERN_DEBUG "[acpi] RSDPDescriptor not found\n"));
		return;
	}
	printk(FREESTR(KERN_DEBUG "[acpi] RSDPDescriptor located at %p [oem: %.?q, rev: %" PRIu8 "]\n"),
	       (uintptr_t)rsdp - KERNEL_CORE_BASE,
	       lengthof(rsdp->rsdp_oemid),
	       rsdp->rsdp_oemid,
	       rsdp->rsdp_revision);
	acpi_mode = ACPI_MODE_RSDT;
	acpi_root = (physaddr_t)rsdp->rsdp_rsdtaddr;
	if (rsdp->rsdp_revision >= 2) {
		/* Use XSDT (but validate it first) */
		if (rsdp->rsdp_length < offsetof(RSDPDescriptor,rsdp_reserved) ||
		    acpi_memsum(rsdp, rsdp->rsdp_length) != 0) {
			printk(FREESTR(KERN_ERR "[acpi] XSDT table extension is corrupted (using RSDT instead)\n"));
		} else {
			acpi_mode = ACPI_MODE_XSDT;
			acpi_root = (physaddr_t)rsdp->rsdp_xsdtaddr;
		}
	}
	copyfromphys_noidentity(&header, acpi_root, sizeof(ACPISDTHeader));
	/* Validate the header. */
	if unlikely(acpi_memsum_phys(acpi_root, header.rsdp_length) != 0) {
		printk(FREESTR(KERN_ERR "[acpi] Corrupted %cSDT checksum [table: "
		                        "%" PRIpN(__SIZEOF_PHYSADDR_T__) "..."
		                        "%" PRIpN(__SIZEOF_PHYSADDR_T__) "]\n"),
		       acpi_mode == ACPI_MODE_RSDT ? 'R' : 'X',
		       (physaddr_t)acpi_root,
		       (physaddr_t)acpi_root + header.rsdp_length - 1);
		return;
	}

	/* Figure out how many tables there are. */
	acpi_sdt_count = (header.rsdp_length - sizeof(ACPISDTHeader)) / ACPI_POINTER_SIZE;
	if unlikely(!acpi_sdt_count) {
		printk(FREESTR(KERN_ERR "[acpi] %cSDT contains no SDTs [table: "
		                        "%" PRIpN(__SIZEOF_PHYSADDR_T__) "..."
		                        "%" PRIpN(__SIZEOF_PHYSADDR_T__) "]\n"),
		       acpi_mode == ACPI_MODE_RSDT ? 'R' : 'X',
		       (physaddr_t)acpi_root,
		       (physaddr_t)acpi_root + header.rsdp_length - 1);
		return;
	}

	/* Preserve the contents of the RSDT table. */
	minfo_addbank(acpi_root,
	              (physaddr_t)header.rsdp_length,
	              PMEMBANK_TYPE_DEVICE);

	/* Go  through  all available  tables, enumerating  them  and validating  their checksum
	 * Each  table that checks out is then marked as PRESERVE, while each table that appears
	 * to be corrupt gets its signature overwritten with all ZEROes, so when later searching
	 * the table, we don't end up stumbling over corrupted entries.
	 * Note though, that corrupted entries in themself probably indicate a bigger problem... */
	{
		size_t i;
		for (i = 0; i < acpi_sdt_count; ++i) {
			physaddr_t addr, base;
			addr = acpi_root + sizeof(ACPISDTHeader) + i * ACPI_POINTER_SIZE;
			/* Dereference the base pointer. */
			base = 0;
			copyfromphys_noidentity(&base, addr, ACPI_POINTER_SIZE);
			/* Load the component header. */
			copyfromphys_noidentity(&header, base, sizeof(header));
			/* Validate the table. */
			if unlikely(acpi_memsum_phys(base, header.rsdp_length) != 0) {
				printk(FREESTR(KERN_ERR "[acpi:sdt:%" PRIuSIZ ":%.?q] corrupted table [table: "
				                        "%" PRIpN(__SIZEOF_PHYSADDR_T__) "..."
				                        "%" PRIpN(__SIZEOF_PHYSADDR_T__) ", "
				                        "oem: %.?q, oemtab: %.?q]\n"),
				       i, lengthof(header.rsdp_signature), header.rsdp_signature,
				       (physaddr_t)base,
				       (physaddr_t)base + header.rsdp_length - 1,
				       lengthof(header.rsdp_oemid), header.rsdp_oemid,
				       lengthof(header.rsdp_oemtableid), header.rsdp_oemtableid);
				bzero(header.rsdp_signature, sizeof(header.rsdp_signature));
				copytophys(base + offsetof(ACPISDTHeader, rsdp_signature),
				           &header.rsdp_signature[0], sizeof(header.rsdp_signature));
				continue;
			}
			printk(FREESTR(KERN_INFO "[acpi:sdt:%" PRIuSIZ ":%.?q] found table [table: "
			                         "%" PRIpN(__SIZEOF_PHYSADDR_T__) "..."
			                         "%" PRIpN(__SIZEOF_PHYSADDR_T__) ", "
			                         "oem: %.?q, oemtab: %.?q]\n"),
			       i, lengthof(header.rsdp_signature), header.rsdp_signature,
			       (physaddr_t)base,
			       (physaddr_t)base + header.rsdp_length - 1,
			       lengthof(header.rsdp_oemid), header.rsdp_oemid,
			       lengthof(header.rsdp_oemtableid), header.rsdp_oemtableid);
			minfo_addbank(base, (physaddr_t)header.rsdp_length, PMEMBANK_TYPE_DEVICE);
		}
	}

#if 0 /* TODO: Remove me */
	{
		FADT fadt;
		if (acpi_lookup("FACP", &fadt, sizeof(fadt))) {
			printk(FREESTR(KERN_DEBUG "[acpi] fadt_Dsdt = %" PRIp32 "\n"),fadt.fadt_Dsdt);
		}
	}
#endif
}


/* Lookup an ACPI table and store its contents in `buf', and return the number of required bytes
 * Note however that in the event of `return > buflen', data will have still been written to the
 * given buffer, leading up to `buflen'. Separately, in the event of `return < buflen', any data
 * that  could  not  be  derived  from  the  SDT  table  will  be  initialized  as  all  ZEROes.
 * Also  note  that  the caller  is  required to  ensure  that `buflen >= sizeof(ACPISDTHeader)'
 * @param: ptableaddr: When  non-NULL, filled with the physical base
 *                     address of the found SDT header upon success.
 * @return: 0 : Failed to find the ACPI table.
 * @return: * : Same as `((ACPISDTHeader *)buf)->rsdp_length' */
PUBLIC WUNUSED NONNULL((1, 2)) size_t
NOTHROW(KCALL acpi_lookup)(char const signature[4],
                           void *buf, size_t buflen,
                           physaddr_t *ptableaddr) {
	size_t i, result;
	assert(buflen >= sizeof(ACPISDTHeader));
	for (i = 0; i < acpi_sdt_count; ++i) {
		physaddr_t addr, base;
		size_t missing;
		ACPISDTHeader *hdr;
		addr = acpi_root + sizeof(ACPISDTHeader) + i * ACPI_POINTER_SIZE;
		base = ACPI_POINTER_SIZE == 4
		       ? (physaddr_t)peekphysl_unaligned(addr)
		       : (physaddr_t)peekphysq_unaligned(addr);
		copyfromphys(buf, base, sizeof(ACPISDTHeader));
		hdr = (ACPISDTHeader *)buf;
		if (bcmp(hdr->rsdp_signature, signature,
		         sizeof(hdr->rsdp_signature)) != 0)
			continue;
		result = hdr->rsdp_length;
		/* Make sure not to copy more than the given buffer can hold. */
		missing = buflen;
		if (buflen > result) {
			/* Zero-initialize trailing memory. */
			bzero((byte_t *)buf + result, buflen - result);
			missing = result;
		}
		if (missing > sizeof(ACPISDTHeader)) {
			/* Copy additional data. */
			copyfromphys((byte_t *)buf + sizeof(ACPISDTHeader),
			             (physaddr_t)(base + sizeof(ACPISDTHeader)),
			             missing - sizeof(ACPISDTHeader));
		}
		if (ptableaddr)
			*ptableaddr = base;
		return result;
	}
	return 0;
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_BOOT_ACPI_C */
