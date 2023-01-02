/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_MULTIBOOT_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_MULTIBOOT_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>

DECL_BEGIN

/* Disclaimer: Modifications were made to the below code! */

/*  multiboot.h - Multiboot header file.  */
/*  Copyright (C) 1999,2003,2007,2008,2009,2010  Free Software Foundation, Inc.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of  this software  and associated  documentation files  (the "Software"), to
 *  deal in the Software without  restriction, including without limitation  the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense,  and/or
 *  sell copies of the Software, and to  permit persons to whom the Software  is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE  SOFTWARE IS PROVIDED  "AS IS", WITHOUT WARRANTY OF  ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING  BUT NOT  LIMITED TO  THE WARRANTIES  OF  MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT SHALL  ANY
 *  DEVELOPER OR DISTRIBUTOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 *  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#define MB_SEARCH                8192 /* How many bytes from the start of the file we search for the header.  */
#define MB_HEADER_ALIGN          4
#define MB_HEADER_MAGIC          0x1BADB002 /* The magic field should contain this.  */
#define MB_BOOTLOADER_MAGIC      0x2BADB002 /* This should be in %eax.  */
#define MB_MOD_ALIGN             0x00001000 /* Alignment of multiboot modules.  */
#define MB_INFO_ALIGN            0x00000004 /* Alignment of the multiboot info structure.  */
/* Flags set in the `flags' member of the multiboot header.  */
#define MB_PAGE_ALIGN            0x00000001 /* Align all boot modules on i386 page (4KB) boundaries.  */
#define MB_MEMORY_INFO           0x00000002 /* Must pass memory information to OS.  */
#define MB_VIDEO_MODE            0x00000004 /* Must pass video information to OS.  */
#define MB_AOUT_KLUDGE           0x00010000 /* This flag indicates the use of the address fields in the header.  */
/* Flags to be set in the `flags' member of the multiboot info structure.  */
#define MB_INFO_MEMORY           0x00000001 /* is there basic lower/upper memory information? */
#define MB_INFO_BOOTDEV          0x00000002 /* is there a boot device set? */
#define MB_INFO_CMDLINE          0x00000004 /* is the command-line defined? */
#define MB_INFO_MODS             0x00000008 /* are there modules to do something with? */
/* These next two are mutually exclusive */
#define MB_INFO_AOUT_SYMS        0x00000010 /* is there a symbol table loaded? */
#define MB_INFO_ELF_SHDR         0X00000020 /* is there an ELF section header table? */
#define MB_INFO_MEM_MAP          0x00000040 /* is there a full memory map? */
#define MB_INFO_DRIVE_INFO       0x00000080 /* Is there drive info?  */
#define MB_INFO_CONFIG_TABLE     0x00000100 /* Is there a config table?  */
#define MB_INFO_BOOT_LOADER_NAME 0x00000200 /* Is there a boot loader name?  */
#define MB_INFO_APM_TABLE        0x00000400 /* Is there a APM table?  */
#define MB_INFO_VBE_INFO         0x00000800 /* Is there video information?  */
#define MB_INFO_FRAMEBUFFER_INFO 0x00001000

#ifdef __CC__

struct mb_header {
	u32 magic;    /* Must be MB_MAGIC - see above.  */
	u32 flags;    /* Feature flags.  */
	u32 checksum; /* The above fields plus this one must equal 0 mod 2^32. */
	/* These are only valid if MB_AOUT_KLUDGE is set.  */
	u32 header_addr;
	u32 load_addr;
	u32 load_end_addr;
	u32 bss_end_addr;
	u32 entry_addr;
	/* These are only valid if MB_VIDEO_MODE is set.  */
	u32 mode_type;
	u32 width;
	u32 height;
	u32 depth;
};

/* The symbol table for a.out.  */
typedef struct mb_aout_symbol_table {
	u32 tabsize;
	u32 strsize;
	u32 addr;
	u32 reserved;
} mb_aout_symbol_table_t;
/* The section header table for ELF.  */
typedef struct mb_elf_section_header_table {
	u32 num;
	u32 size;
	u32 addr;
	u32 shndx;
} mb_elf_section_header_table_t;

typedef struct mb_info {
	u32 flags;     /* Multiboot info version number */
	u32 mem_lower; /* Available memory from BIOS */
	u32 mem_upper;
	u32 boot_device; /* "root" partition */
	u32 cmdline;     /* Kernel command line */
	u32 mods_count;  /* Boot-Module list */
	u32 mods_addr;   /* Pointer to `mods_count' elements long vector of `mb_module_t' */
	union {
		mb_aout_symbol_table_t aout_sym;
		mb_elf_section_header_table_t elf_sec;
	} u;
	u32 mmap_length; /* Memory Mapping buffer */
	u32 mmap_addr;
	u32 drives_length; /* Drive Info buffer */
	u32 drives_addr;
	u32 config_table;     /* ROM configuration table */
	u32 boot_loader_name; /* Boot Loader Name */
	u32 apm_table;        /* APM table */
	u32 vbe_control_info; /* Video */
	u32 vbe_mode_info;
	u16 vbe_mode;
	u16 vbe_interface_seg;
	u16 vbe_interface_off;
	u16 vbe_interface_len;
	u64 framebuffer_addr;
	u32 framebuffer_pitch;
	u32 framebuffer_width;
	u32 framebuffer_height;
	u8 framebuffer_bpp;
#define MB_FRAMEBUFFER_TYPE_INDEXED 0
#define MB_FRAMEBUFFER_TYPE_RGB 1
#define MB_FRAMEBUFFER_TYPE_EGA_TEXT 2
	u8 framebuffer_type;
	union {
		struct {
			u32 framebuffer_palette_addr;
			u16 framebuffer_palette_num_colors;
		};
		struct {
			u8 framebuffer_red_field_position;
			u8 framebuffer_red_mask_size;
			u8 framebuffer_green_field_position;
			u8 framebuffer_green_mask_size;
			u8 framebuffer_blue_field_position;
			u8 framebuffer_blue_mask_size;
		};
	};
} mb_info_t;

struct mb_color {
	u8 red;
	u8 green;
	u8 blue;
};

typedef struct ATTR_PACKED mb_mmap_entry {
	u32 size;
	u64 addr;
	u64 len;
#define MB_MEMORY_AVAILABLE        1
#define MB_MEMORY_RESERVED         2
#define MB_MEMORY_ACPI_RECLAIMABLE 3
#define MB_MEMORY_NVS              4
#define MB_MEMORY_BADRAM           5
	u32 type;
} mb_memory_map_t;

typedef struct mb_mod_list {
	u32 mod_start; /* the memory used goes from bytes `mod_start' to `mod_end-1' inclusive */
	u32 mod_end;
	u32 cmdline; /* Module command line */
	u32 pad;     /* padding to take it to 16 bytes (must be zero) */
} mb_module_t;

/* APM BIOS info.  */
struct mb_apm_info {
	u16 version;
	u16 cseg;
	u32 offset;
	u16 cseg_16;
	u16 dseg;
	u16 flags;
	u16 cseg_len;
	u16 cseg_16_len;
	u16 dseg_len;
};

#endif /* __CC__ */





/* Disclaimer: Modifications were made to the below code! */

/*  multiboot2.h - Multiboot 2 header file.  */
/*  Copyright (C) 1999,2003,2007,2008,2009,2010  Free Software Foundation, Inc.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of  this software  and associated  documentation files  (the "Software"), to
 *  deal in the Software without  restriction, including without limitation  the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense,  and/or
 *  sell copies of the Software, and to  permit persons to whom the Software  is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE  SOFTWARE IS PROVIDED  "AS IS", WITHOUT WARRANTY OF  ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING  BUT NOT  LIMITED TO  THE WARRANTIES  OF  MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT SHALL  ANY
 *  DEVELOPER OR DISTRIBUTOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 *  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#define MB2_SEARCH                           32768      /* How many bytes from the start of the file we search for the header.  */
#define MB2_HEADER_ALIGN                     8
#define MB2_HEADER_MAGIC                     0xe85250d6 /* The magic field should contain this.  */
#define MB2_BOOTLOADER_MAGIC                 0x36d76289 /* This should be in %eax.  */
#define MB2_MOD_ALIGN                        0x00001000 /* Alignment of multiboot modules.  */
#define MB2_INFO_ALIGN                       0x00000008 /* Alignment of the multiboot info structure.  */

/* Flags set in the `flags' member of the multiboot header.  */
#define MB2_TAG_ALIGN                        8
#define MB2_TAG_TYPE_END                     0
#define MB2_TAG_TYPE_CMDLINE                 1
#define MB2_TAG_TYPE_BOOT_LOADER_NAME        2
#define MB2_TAG_TYPE_MODULE                  3
#define MB2_TAG_TYPE_BASIC_MEMINFO           4
#define MB2_TAG_TYPE_BOOTDEV                 5
#define MB2_TAG_TYPE_MMAP                    6
#define MB2_TAG_TYPE_VBE                     7
#define MB2_TAG_TYPE_FRAMEBUFFER             8
#define MB2_TAG_TYPE_ELF_SECTIONS            9
#define MB2_TAG_TYPE_APM                     10
#define MB2_TAG_TYPE_EFI32                   11
#define MB2_TAG_TYPE_EFI64                   12
#define MB2_TAG_TYPE_SMBIOS                  13
#define MB2_TAG_TYPE_ACPI_OLD                14
#define MB2_TAG_TYPE_ACPI_NEW                15
#define MB2_TAG_TYPE_NETWORK                 16
#define MB2_TAG_TYPE_EFI_MMAP                17
#define MB2_TAG_TYPE_EFI_BS                  18
#define MB2_TAG_TYPE_EFI32_IH                19
#define MB2_TAG_TYPE_EFI64_IH                20
#define MB2_TAG_TYPE_LOAD_BASE_ADDR          21

#define MB2_HEADER_TAG_END                   0
#define MB2_HEADER_TAG_INFORMATION_REQUEST   1
#define MB2_HEADER_TAG_ADDRESS               2
#define MB2_HEADER_TAG_ENTRY_ADDRESS         3
#define MB2_HEADER_TAG_CONSOLE_FLAGS         4
#define MB2_HEADER_TAG_FRAMEBUFFER           5
#define MB2_HEADER_TAG_MODULE_ALIGN          6
#define MB2_HEADER_TAG_EFI_BS                7
#define MB2_HEADER_TAG_ENTRY_ADDRESS_EFI32   8
#define MB2_HEADER_TAG_ENTRY_ADDRESS_EFI64   9
#define MB2_HEADER_TAG_RELOCATABLE           10

#define MB2_ARCHITECTURE_I386                0
#define MB2_ARCHITECTURE_MIPS32              4

#define MB2_HEADER_TAG_OPTIONAL              1

#define MB2_LOAD_PREFERENCE_NONE             0
#define MB2_LOAD_PREFERENCE_LOW              1
#define MB2_LOAD_PREFERENCE_HIGH             2

#define MB2_CONSOLE_FLAGS_CONSOLE_REQUIRED   1
#define MB2_CONSOLE_FLAGS_EGA_TEXT_SUPPORTED 2

#ifdef __CC__

struct mb2_header {
	u32 magic;        /* Must be MB2_MAGIC - see above.  */
	u32 architecture; /* ISA */
	union ATTR_PACKED {
#if __SIZEOF_POINTER__ >= 8
		u64 header_length_and_checksum;
		struct ATTR_PACKED {
			u32 header_length; /* Total header length.  */
			u32 checksum;      /* The above fields plus this one must equal 0 mod 2^32. */
		};
#else /* __SIZEOF_POINTER__ >= 8 */
		struct ATTR_PACKED {
			u32 header_length; /* Total header length.  */
			u32 checksum;      /* The above fields plus this one must equal 0 mod 2^32. */
		};
		u64 header_length_and_checksum;
#endif /* __SIZEOF_POINTER__ < 8 */
	};
};

struct mb2_header_tag {
	u16 type;
	u16 flags;
	u32 size;
};

struct mb2_header_tag_information_request {
	u16 type;
	u16 flags;
	u32 size;
	COMPILER_FLEXIBLE_ARRAY(u32, requests);
};

struct mb2_header_tag_address {
	u16 type;
	u16 flags;
	u32 size;
	u32 header_addr;
	u32 load_addr;
	u32 load_end_addr;
	u32 bss_end_addr;
};

struct mb2_header_tag_entry_address {
	u16 type;
	u16 flags;
	u32 size;
	u32 entry_addr;
};

struct mb2_header_tag_console_flags {
	u16 type;
	u16 flags;
	u32 size;
	u32 console_flags;
};

struct mb2_header_tag_framebuffer {
	u16 type;
	u16 flags;
	u32 size;
	u32 width;
	u32 height;
	u32 depth;
};

struct mb2_header_tag_module_align {
	u16 type;
	u16 flags;
	u32 size;
};

struct mb2_header_tag_relocatable {
	u16 type;
	u16 flags;
	u32 size;
	u32 min_addr;
	u32 max_addr;
	u32 align;
	u32 preference;
};

struct mb2_color {
	u8 red;
	u8 green;
	u8 blue;
};

typedef struct mb2_mmap_entry {
	u64 addr;
	u64 len;
#define MB2_MEMORY_AVAILABLE        1
#define MB2_MEMORY_RESERVED         2
#define MB2_MEMORY_ACPI_RECLAIMABLE 3
#define MB2_MEMORY_NVS              4
#define MB2_MEMORY_BADRAM           5
	u32 type;
	u32 zero;
} mb2_memory_map_t;

struct mb2_tag {
	u32 type;
	u32 size;
};
struct mb2_tag_string {
	u32 type;
	u32 size;
	COMPILER_FLEXIBLE_ARRAY(char, string);
};
struct mb2_tag_module {
	u32 type;
	u32 size;
	u32 mod_start;
	u32 mod_end;
	COMPILER_FLEXIBLE_ARRAY(char, cmdline);
};
struct mb2_tag_module_no_cmdline {
	u32 type;
	u32 size;
	u32 mod_start;
	u32 mod_end;
};
struct mb2_tag_basic_meminfo {
	u32 type;
	u32 size;
	u32 mem_lower;
	u32 mem_upper;
};
struct mb2_tag_bootdev {
	u32 type;
	u32 size;
	u32 biosdev;
	u32 partition;
	u32 sub_partition;
};
struct mb2_tag_mmap {
	u32 type;
	u32 size;
	u32 entry_size;
	u32 entry_version;
	COMPILER_FLEXIBLE_ARRAY(struct mb2_mmap_entry, entries);
};
struct mb2_vbe_info_block {
	u8 external_specification[512];
};
struct mb2_vbe_mode_info_block {
	u8 external_specification[256];
};
struct mb2_tag_vbe {
	u32 type;
	u32 size;
	u16 vbe_mode;
	u16 vbe_interface_seg;
	u16 vbe_interface_off;
	u16 vbe_interface_len;
	struct mb2_vbe_info_block vbe_control_info;
	struct mb2_vbe_mode_info_block vbe_mode_info;
};
struct mb2_tag_framebuffer_common {
	u32 type;
	u32 size;
	u64 framebuffer_addr;
	u32 framebuffer_pitch;
	u32 framebuffer_width;
	u32 framebuffer_height;
	u8 framebuffer_bpp;
#define MB2_FRAMEBUFFER_TYPE_INDEXED  0
#define MB2_FRAMEBUFFER_TYPE_RGB      1
#define MB2_FRAMEBUFFER_TYPE_EGA_TEXT 2
	u8 framebuffer_type;
	u16 reserved;
};

struct mb2_tag_framebuffer {
	struct mb2_tag_framebuffer_common common;
	union ATTR_PACKED {
		struct ATTR_PACKED {
			u8 framebuffer_red_field_position;
			u8 framebuffer_red_mask_size;
			u8 framebuffer_green_field_position;
			u8 framebuffer_green_mask_size;
			u8 framebuffer_blue_field_position;
			u8 framebuffer_blue_mask_size;
		};
		struct ATTR_PACKED {
			u16 framebuffer_palette_num_colors;
			COMPILER_FLEXIBLE_ARRAY(struct mb2_color, framebuffer_palette);
		};
	};
};
struct mb2_tag_elf_sections {
	u32 type;
	u32 size;
	u32 num;
	u32 entsize;
	u32 shndx;
	COMPILER_FLEXIBLE_ARRAY(char, sections);
};
struct mb2_tag_apm {
	u32 type;
	u32 size;
	u16 version;
	u16 cseg;
	u32 offset;
	u16 cseg_16;
	u16 dseg;
	u16 flags;
	u16 cseg_len;
	u16 cseg_16_len;
	u16 dseg_len;
};
struct mb2_tag_efi32 {
	u32 type;
	u32 size;
	u32 pointer;
};
struct mb2_tag_efi64 {
	u32 type;
	u32 size;
	u64 pointer;
};
struct mb2_tag_smbios {
	u32 type;
	u32 size;
	u8 major;
	u8 minor;
	u8 reserved[6];
	COMPILER_FLEXIBLE_ARRAY(u8, tables);
};
struct mb2_tag_old_acpi {
	u32 type;
	u32 size;
	COMPILER_FLEXIBLE_ARRAY(u8, rsdp);
};
struct mb2_tag_new_acpi {
	u32 type;
	u32 size;
	COMPILER_FLEXIBLE_ARRAY(u8, rsdp);
};
struct mb2_tag_network {
	u32 type;
	u32 size;
	COMPILER_FLEXIBLE_ARRAY(u8, dhcpack);
};
struct mb2_tag_efi_mmap {
	u32 type;
	u32 size;
	u32 descr_size;
	u32 descr_vers;
	COMPILER_FLEXIBLE_ARRAY(u8, efi_mmap);
};
struct mb2_tag_efi32_ih {
	u32 type;
	u32 size;
	u32 pointer;
};
struct mb2_tag_efi64_ih {
	u32 type;
	u32 size;
	u64 pointer;
};
struct mb2_tag_load_base_addr {
	u32 type;
	u32 size;
	u32 load_base_addr;
};

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_MULTIBOOT_H */
