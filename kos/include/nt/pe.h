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
#ifndef _NT_PE_H
#define _NT_PE_H 1

#include "__stdinc.h"
/**/

#include "guid.h"
#include "types.h"

/**/
#include <hybrid/typecore.h>


/************************************************************************/
/* Structures relating to PE (Portable Executable) files                */
/************************************************************************/

#ifdef __CC__
__DECL_BEGIN

#define IMAGE_DOS_SIGNATURE    0x5A4D
#define IMAGE_OS2_SIGNATURE    0x454E
#define IMAGE_OS2_SIGNATURE_LE 0x454C
#define IMAGE_VXD_SIGNATURE    0x454C
#define IMAGE_NT_SIGNATURE     0x00004550

#include "pshpack2.h"

typedef struct _IMAGE_DOS_HEADER {
	WORD e_magic;
	WORD e_cblp;
	WORD e_cp;
	WORD e_crlc;
	WORD e_cparhdr;
	WORD e_minalloc;
	WORD e_maxalloc;
	WORD e_ss;
	WORD e_sp;
	WORD e_csum;
	WORD e_ip;
	WORD e_cs;
	WORD e_lfarlc;
	WORD e_ovno;
	WORD e_res[4];
	WORD e_oemid;
	WORD e_oeminfo;
	WORD e_res2[10];
	LONG e_lfanew;
} IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;

typedef struct _IMAGE_OS2_HEADER {
	WORD ne_magic;
	CHAR ne_ver;
	CHAR ne_rev;
	WORD ne_enttab;
	WORD ne_cbenttab;
	LONG ne_crc;
	WORD ne_flags;
	WORD ne_autodata;
	WORD ne_heap;
	WORD ne_stack;
	LONG ne_csip;
	LONG ne_sssp;
	WORD ne_cseg;
	WORD ne_cmod;
	WORD ne_cbnrestab;
	WORD ne_segtab;
	WORD ne_rsrctab;
	WORD ne_restab;
	WORD ne_modtab;
	WORD ne_imptab;
	LONG ne_nrestab;
	WORD ne_cmovent;
	WORD ne_align;
	WORD ne_cres;
	BYTE ne_exetyp;
	BYTE ne_flagsothers;
	WORD ne_pretthunks;
	WORD ne_psegrefbytes;
	WORD ne_swaparea;
	WORD ne_expver;
} IMAGE_OS2_HEADER, *PIMAGE_OS2_HEADER;

typedef struct _IMAGE_VXD_HEADER {
	WORD e32_magic;
	BYTE e32_border;
	BYTE e32_worder;
	DWORD e32_level;
	WORD e32_cpu;
	WORD e32_os;
	DWORD e32_ver;
	DWORD e32_mflags;
	DWORD e32_mpages;
	DWORD e32_startobj;
	DWORD e32_eip;
	DWORD e32_stackobj;
	DWORD e32_esp;
	DWORD e32_pagesize;
	DWORD e32_lastpagesize;
	DWORD e32_fixupsize;
	DWORD e32_fixupsum;
	DWORD e32_ldrsize;
	DWORD e32_ldrsum;
	DWORD e32_objtab;
	DWORD e32_objcnt;
	DWORD e32_objmap;
	DWORD e32_itermap;
	DWORD e32_rsrctab;
	DWORD e32_rsrccnt;
	DWORD e32_restab;
	DWORD e32_enttab;
	DWORD e32_dirtab;
	DWORD e32_dircnt;
	DWORD e32_fpagetab;
	DWORD e32_frectab;
	DWORD e32_impmod;
	DWORD e32_impmodcnt;
	DWORD e32_impproc;
	DWORD e32_pagesum;
	DWORD e32_datapage;
	DWORD e32_preload;
	DWORD e32_nrestab;
	DWORD e32_cbnrestab;
	DWORD e32_nressum;
	DWORD e32_autodata;
	DWORD e32_debuginfo;
	DWORD e32_debuglen;
	DWORD e32_instpreload;
	DWORD e32_instdemand;
	DWORD e32_heapsize;
	BYTE e32_res3[12];
	DWORD e32_winresoff;
	DWORD e32_winreslen;
	WORD e32_devid;
	WORD e32_ddkver;
} IMAGE_VXD_HEADER, *PIMAGE_VXD_HEADER;

#include "poppack.h"

typedef struct _IMAGE_FILE_HEADER {
	WORD Machine;
	WORD NumberOfSections;
	DWORD TimeDateStamp;
	DWORD PointerToSymbolTable;
	DWORD NumberOfSymbols;
	WORD SizeOfOptionalHeader;
	WORD Characteristics;
} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

#define IMAGE_SIZEOF_FILE_HEADER 20

#define IMAGE_FILE_RELOCS_STRIPPED         0x0001
#define IMAGE_FILE_EXECUTABLE_IMAGE        0x0002
#define IMAGE_FILE_LINE_NUMS_STRIPPED      0x0004
#define IMAGE_FILE_LOCAL_SYMS_STRIPPED     0x0008
#define IMAGE_FILE_AGGRESIVE_WS_TRIM       0x0010
#define IMAGE_FILE_LARGE_ADDRESS_AWARE     0x0020
#define IMAGE_FILE_BYTES_REVERSED_LO       0x0080
#define IMAGE_FILE_32BIT_MACHINE           0x0100
#define IMAGE_FILE_DEBUG_STRIPPED          0x0200
#define IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP 0x0400
#define IMAGE_FILE_NET_RUN_FROM_SWAP       0x0800
#define IMAGE_FILE_SYSTEM                  0x1000
#define IMAGE_FILE_DLL                     0x2000
#define IMAGE_FILE_UP_SYSTEM_ONLY          0x4000
#define IMAGE_FILE_BYTES_REVERSED_HI       0x8000

#define IMAGE_FILE_MACHINE_UNKNOWN   0
#define IMAGE_FILE_MACHINE_I386      0x014c
#define IMAGE_FILE_MACHINE_R3000     0x0162
#define IMAGE_FILE_MACHINE_R4000     0x0166
#define IMAGE_FILE_MACHINE_R10000    0x0168
#define IMAGE_FILE_MACHINE_WCEMIPSV2 0x0169
#define IMAGE_FILE_MACHINE_ALPHA     0x0184
#define IMAGE_FILE_MACHINE_SH3       0x01a2
#define IMAGE_FILE_MACHINE_SH3DSP    0x01a3
#define IMAGE_FILE_MACHINE_SH3E      0x01a4
#define IMAGE_FILE_MACHINE_SH4       0x01a6
#define IMAGE_FILE_MACHINE_SH5       0x01a8
#define IMAGE_FILE_MACHINE_ARM       0x01c0
#define IMAGE_FILE_MACHINE_ARMV7     0x01c4
#define IMAGE_FILE_MACHINE_ARMNT     0x01c4
#define IMAGE_FILE_MACHINE_ARM64     0xaa64
#define IMAGE_FILE_MACHINE_THUMB     0x01c2
#define IMAGE_FILE_MACHINE_AM33      0x01d3
#define IMAGE_FILE_MACHINE_POWERPC   0x01F0
#define IMAGE_FILE_MACHINE_POWERPCFP 0x01f1
#define IMAGE_FILE_MACHINE_IA64      0x0200
#define IMAGE_FILE_MACHINE_MIPS16    0x0266
#define IMAGE_FILE_MACHINE_ALPHA64   0x0284
#define IMAGE_FILE_MACHINE_MIPSFPU   0x0366
#define IMAGE_FILE_MACHINE_MIPSFPU16 0x0466
#define IMAGE_FILE_MACHINE_AXP64     IMAGE_FILE_MACHINE_ALPHA64
#define IMAGE_FILE_MACHINE_TRICORE   0x0520
#define IMAGE_FILE_MACHINE_CEF       0x0CEF
#define IMAGE_FILE_MACHINE_EBC       0x0EBC
#define IMAGE_FILE_MACHINE_AMD64     0x8664
#define IMAGE_FILE_MACHINE_M32R      0x9041
#define IMAGE_FILE_MACHINE_CEE       0xc0ee

typedef struct _IMAGE_DATA_DIRECTORY {
	DWORD VirtualAddress;
	DWORD Size;
} IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES 16

typedef struct _IMAGE_OPTIONAL_HEADER {
	WORD Magic;
	BYTE MajorLinkerVersion;
	BYTE MinorLinkerVersion;
	DWORD SizeOfCode;
	DWORD SizeOfInitializedData;
	DWORD SizeOfUninitializedData;
	DWORD AddressOfEntryPoint;
	DWORD BaseOfCode;
	DWORD BaseOfData;
	DWORD ImageBase;
	DWORD SectionAlignment;
	DWORD FileAlignment;
	WORD MajorOperatingSystemVersion;
	WORD MinorOperatingSystemVersion;
	WORD MajorImageVersion;
	WORD MinorImageVersion;
	WORD MajorSubsystemVersion;
	WORD MinorSubsystemVersion;
	DWORD Win32VersionValue;
	DWORD SizeOfImage;
	DWORD SizeOfHeaders;
	DWORD CheckSum;
	WORD Subsystem;
	WORD DllCharacteristics;
	DWORD SizeOfStackReserve;
	DWORD SizeOfStackCommit;
	DWORD SizeOfHeapReserve;
	DWORD SizeOfHeapCommit;
	DWORD LoaderFlags;
	DWORD NumberOfRvaAndSizes;
	IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;

typedef struct _IMAGE_ROM_OPTIONAL_HEADER {
	WORD Magic;
	BYTE MajorLinkerVersion;
	BYTE MinorLinkerVersion;
	DWORD SizeOfCode;
	DWORD SizeOfInitializedData;
	DWORD SizeOfUninitializedData;
	DWORD AddressOfEntryPoint;
	DWORD BaseOfCode;
	DWORD BaseOfData;
	DWORD BaseOfBss;
	DWORD GprMask;
	DWORD CprMask[4];
	DWORD GpValue;
} IMAGE_ROM_OPTIONAL_HEADER, *PIMAGE_ROM_OPTIONAL_HEADER;

typedef struct _IMAGE_OPTIONAL_HEADER64 {
	WORD Magic;
	BYTE MajorLinkerVersion;
	BYTE MinorLinkerVersion;
	DWORD SizeOfCode;
	DWORD SizeOfInitializedData;
	DWORD SizeOfUninitializedData;
	DWORD AddressOfEntryPoint;
	DWORD BaseOfCode;
	ULONGLONG ImageBase;
	DWORD SectionAlignment;
	DWORD FileAlignment;
	WORD MajorOperatingSystemVersion;
	WORD MinorOperatingSystemVersion;
	WORD MajorImageVersion;
	WORD MinorImageVersion;
	WORD MajorSubsystemVersion;
	WORD MinorSubsystemVersion;
	DWORD Win32VersionValue;
	DWORD SizeOfImage;
	DWORD SizeOfHeaders;
	DWORD CheckSum;
	WORD Subsystem;
	WORD DllCharacteristics;
	ULONGLONG SizeOfStackReserve;
	ULONGLONG SizeOfStackCommit;
	ULONGLONG SizeOfHeapReserve;
	ULONGLONG SizeOfHeapCommit;
	DWORD LoaderFlags;
	DWORD NumberOfRvaAndSizes;
	IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER64, *PIMAGE_OPTIONAL_HEADER64;

#define IMAGE_SIZEOF_ROM_OPTIONAL_HEADER  56
#define IMAGE_SIZEOF_STD_OPTIONAL_HEADER  28
#define IMAGE_SIZEOF_NT_OPTIONAL32_HEADER 224
#define IMAGE_SIZEOF_NT_OPTIONAL64_HEADER 240

#define IMAGE_NT_OPTIONAL_HDR32_MAGIC 0x10b
#define IMAGE_NT_OPTIONAL_HDR64_MAGIC 0x20b
#define IMAGE_ROM_OPTIONAL_HDR_MAGIC  0x107

typedef struct _IMAGE_NT_HEADERS64 {
	DWORD Signature;
	IMAGE_FILE_HEADER FileHeader;
	IMAGE_OPTIONAL_HEADER64 OptionalHeader;
} IMAGE_NT_HEADERS64, *PIMAGE_NT_HEADERS64;

typedef struct _IMAGE_NT_HEADERS {
	DWORD Signature;
	IMAGE_FILE_HEADER FileHeader;
	IMAGE_OPTIONAL_HEADER32 OptionalHeader;
} IMAGE_NT_HEADERS32, *PIMAGE_NT_HEADERS32;

typedef struct _IMAGE_ROM_HEADERS {
	IMAGE_FILE_HEADER FileHeader;
	IMAGE_ROM_OPTIONAL_HEADER OptionalHeader;
} IMAGE_ROM_HEADERS, *PIMAGE_ROM_HEADERS;

#define IMAGE_FIRST_SECTION(ntheader) ((PIMAGE_SECTION_HEADER)((ULONG_PTR)ntheader + FIELD_OFFSET(IMAGE_NT_HEADERS, OptionalHeader) + ((PIMAGE_NT_HEADERS)(ntheader))->FileHeader.SizeOfOptionalHeader))

#define IMAGE_SUBSYSTEM_UNKNOWN                  0
#define IMAGE_SUBSYSTEM_NATIVE                   1
#define IMAGE_SUBSYSTEM_WINDOWS_GUI              2
#define IMAGE_SUBSYSTEM_WINDOWS_CUI              3
#define IMAGE_SUBSYSTEM_OS2_CUI                  5
#define IMAGE_SUBSYSTEM_POSIX_CUI                7
#define IMAGE_SUBSYSTEM_NATIVE_WINDOWS           8
#define IMAGE_SUBSYSTEM_WINDOWS_CE_GUI           9
#define IMAGE_SUBSYSTEM_EFI_APPLICATION          10
#define IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER  11
#define IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER       12
#define IMAGE_SUBSYSTEM_EFI_ROM                  13
#define IMAGE_SUBSYSTEM_XBOX                     14
#define IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION 16

#define IMAGE_DLLCHARACTERISTICS_HIGH_ENTROPY_VA       0x0020
#define IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE          0x0040
#define IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY       0x0080
#define IMAGE_DLLCHARACTERISTICS_NX_COMPAT             0x0100
#define IMAGE_DLLCHARACTERISTICS_NO_ISOLATION          0x0200
#define IMAGE_DLLCHARACTERISTICS_NO_SEH                0x0400
#define IMAGE_DLLCHARACTERISTICS_NO_BIND               0x0800
#define IMAGE_DLLCHARACTERISTICS_APPCONTAINER          0x1000
#define IMAGE_DLLCHARACTERISTICS_WDM_DRIVER            0x2000
#define IMAGE_DLLCHARACTERISTICS_GUARD_CF              0x4000
#define IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE 0x8000

#define IMAGE_DIRECTORY_ENTRY_EXPORT         0
#define IMAGE_DIRECTORY_ENTRY_IMPORT         1
#define IMAGE_DIRECTORY_ENTRY_RESOURCE       2
#define IMAGE_DIRECTORY_ENTRY_EXCEPTION      3
#define IMAGE_DIRECTORY_ENTRY_SECURITY       4
#define IMAGE_DIRECTORY_ENTRY_BASERELOC      5
#define IMAGE_DIRECTORY_ENTRY_DEBUG          6
#define IMAGE_DIRECTORY_ENTRY_ARCHITECTURE   7
#define IMAGE_DIRECTORY_ENTRY_GLOBALPTR      8
#define IMAGE_DIRECTORY_ENTRY_TLS            9
#define IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG    10
#define IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT   11
#define IMAGE_DIRECTORY_ENTRY_IAT            12
#define IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT   13
#define IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR 14

typedef struct ANON_OBJECT_HEADER {
	WORD Sig1;
	WORD Sig2;
	WORD Version;
	WORD Machine;
	DWORD TimeDateStamp;
	CLSID ClassID;
	DWORD SizeOfData;
} ANON_OBJECT_HEADER;

typedef struct ANON_OBJECT_HEADER_V2 {
	WORD Sig1;
	WORD Sig2;
	WORD Version;
	WORD Machine;
	DWORD TimeDateStamp;
	CLSID ClassID;
	DWORD SizeOfData;
	DWORD Flags;
	DWORD MetaDataSize;
	DWORD MetaDataOffset;
} ANON_OBJECT_HEADER_V2;

typedef struct ANON_OBJECT_HEADER_BIGOBJ {
	WORD Sig1;
	WORD Sig2;
	WORD Version;
	WORD Machine;
	DWORD TimeDateStamp;
	CLSID ClassID;
	DWORD SizeOfData;
	DWORD Flags;
	DWORD MetaDataSize;
	DWORD MetaDataOffset;
	DWORD NumberOfSections;
	DWORD PointerToSymbolTable;
	DWORD NumberOfSymbols;
} ANON_OBJECT_HEADER_BIGOBJ;

#define IMAGE_SIZEOF_SHORT_NAME 8

typedef struct _IMAGE_SECTION_HEADER {
	BYTE Name[IMAGE_SIZEOF_SHORT_NAME];
	union {
		DWORD PhysicalAddress;
		DWORD VirtualSize;
	} Misc;
	DWORD VirtualAddress;
	DWORD SizeOfRawData;
	DWORD PointerToRawData;
	DWORD PointerToRelocations;
	DWORD PointerToLinenumbers;
	WORD NumberOfRelocations;
	WORD NumberOfLinenumbers;
	DWORD Characteristics;
} IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;

#define IMAGE_SIZEOF_SECTION_HEADER 40

#define IMAGE_SCN_SCALE_INDEX            0x00000001
#define IMAGE_SCN_TYPE_NO_PAD            0x00000008
#define IMAGE_SCN_CNT_CODE               0x00000020
#define IMAGE_SCN_CNT_INITIALIZED_DATA   0x00000040
#define IMAGE_SCN_CNT_UNINITIALIZED_DATA 0x00000080
#define IMAGE_SCN_LNK_OTHER              0x00000100
#define IMAGE_SCN_LNK_INFO               0x00000200
#define IMAGE_SCN_LNK_REMOVE             0x00000800
#define IMAGE_SCN_LNK_COMDAT             0x00001000
#define IMAGE_SCN_NO_DEFER_SPEC_EXC      0x00004000
#define IMAGE_SCN_GPREL                  0x00008000
#define IMAGE_SCN_MEM_FARDATA            0x00008000
#define IMAGE_SCN_MEM_PURGEABLE          0x00020000
#define IMAGE_SCN_MEM_16BIT              0x00020000
#define IMAGE_SCN_MEM_LOCKED             0x00040000
#define IMAGE_SCN_MEM_PRELOAD            0x00080000
#define IMAGE_SCN_ALIGN_1BYTES           0x00100000
#define IMAGE_SCN_ALIGN_2BYTES           0x00200000
#define IMAGE_SCN_ALIGN_4BYTES           0x00300000
#define IMAGE_SCN_ALIGN_8BYTES           0x00400000
#define IMAGE_SCN_ALIGN_16BYTES          0x00500000
#define IMAGE_SCN_ALIGN_32BYTES          0x00600000
#define IMAGE_SCN_ALIGN_64BYTES          0x00700000
#define IMAGE_SCN_ALIGN_128BYTES         0x00800000
#define IMAGE_SCN_ALIGN_256BYTES         0x00900000
#define IMAGE_SCN_ALIGN_512BYTES         0x00A00000
#define IMAGE_SCN_ALIGN_1024BYTES        0x00B00000
#define IMAGE_SCN_ALIGN_2048BYTES        0x00C00000
#define IMAGE_SCN_ALIGN_4096BYTES        0x00D00000
#define IMAGE_SCN_ALIGN_8192BYTES        0x00E00000
#define IMAGE_SCN_ALIGN_MASK             0x00F00000
#define IMAGE_SCN_LNK_NRELOC_OVFL        0x01000000
#define IMAGE_SCN_MEM_DISCARDABLE        0x02000000
#define IMAGE_SCN_MEM_NOT_CACHED         0x04000000
#define IMAGE_SCN_MEM_NOT_PAGED          0x08000000
#define IMAGE_SCN_MEM_SHARED             0x10000000
#define IMAGE_SCN_MEM_EXECUTE            0x20000000
#define IMAGE_SCN_MEM_READ               0x40000000
#define IMAGE_SCN_MEM_WRITE              0x80000000

#ifdef __KOS__
#include <asm/os/mman.h>

/* Convert `IMAGE_SCN_*' into a set of `PROT_*' */
#define IMAGE_SCN_ASPROT(image_scn)                                \
	(((image_scn) & (IMAGE_SCN_LNK_REMOVE | IMAGE_SCN_LNK_INFO))   \
	 ? __PROT_NONE                                                 \
	 : ((((image_scn)&IMAGE_SCN_MEM_SHARED) ? __PROT_SHARED : 0) | \
	    (((image_scn)&IMAGE_SCN_MEM_EXECUTE) ? __PROT_EXEC : 0) |  \
	    (((image_scn)&IMAGE_SCN_MEM_READ) ? __PROT_READ : 0) |     \
	    (((image_scn)&IMAGE_SCN_MEM_WRITE) ? __PROT_WRITE : 0)))
#endif /* __KOS__ */



#include "pshpack2.h"
typedef struct _IMAGE_SYMBOL {
	union {
		BYTE ShortName[8];
		struct {
			DWORD Short;
			DWORD Long;
		} Name;
		DWORD LongName[2];
	} N;
	DWORD Value;
	SHORT SectionNumber;
	WORD Type;
	BYTE StorageClass;
	BYTE NumberOfAuxSymbols;
} IMAGE_SYMBOL;
typedef IMAGE_SYMBOL UNALIGNED *PIMAGE_SYMBOL;

#define IMAGE_SIZEOF_SYMBOL 18

typedef struct _IMAGE_SYMBOL_EX {
	union {
		BYTE ShortName[8];
		struct {
			DWORD Short;
			DWORD Long;
		} Name;
		DWORD LongName[2];
	} N;
	DWORD Value;
	LONG SectionNumber;
	WORD Type;
	BYTE StorageClass;
	BYTE NumberOfAuxSymbols;
} IMAGE_SYMBOL_EX, UNALIGNED *PIMAGE_SYMBOL_EX;

#define IMAGE_SYM_UNDEFINED      ((SHORT)0)
#define IMAGE_SYM_ABSOLUTE       ((SHORT)-1)
#define IMAGE_SYM_DEBUG          ((SHORT)-2)
#define IMAGE_SYM_SECTION_MAX    0xFEFF
#define IMAGE_SYM_SECTION_MAX_EX MAXLONG

#define IMAGE_SYM_TYPE_NULL   0x0000
#define IMAGE_SYM_TYPE_VOID   0x0001
#define IMAGE_SYM_TYPE_CHAR   0x0002
#define IMAGE_SYM_TYPE_SHORT  0x0003
#define IMAGE_SYM_TYPE_INT    0x0004
#define IMAGE_SYM_TYPE_LONG   0x0005
#define IMAGE_SYM_TYPE_FLOAT  0x0006
#define IMAGE_SYM_TYPE_DOUBLE 0x0007
#define IMAGE_SYM_TYPE_STRUCT 0x0008
#define IMAGE_SYM_TYPE_UNION  0x0009
#define IMAGE_SYM_TYPE_ENUM   0x000A
#define IMAGE_SYM_TYPE_MOE    0x000B
#define IMAGE_SYM_TYPE_BYTE   0x000C
#define IMAGE_SYM_TYPE_WORD   0x000D
#define IMAGE_SYM_TYPE_UINT   0x000E
#define IMAGE_SYM_TYPE_DWORD  0x000F
#define IMAGE_SYM_TYPE_PCODE  0x8000

#define IMAGE_SYM_DTYPE_NULL     0
#define IMAGE_SYM_DTYPE_POINTER  1
#define IMAGE_SYM_DTYPE_FUNCTION 2
#define IMAGE_SYM_DTYPE_ARRAY    3

#define IMAGE_SYM_CLASS_END_OF_FUNCTION  ((BYTE)-1)
#define IMAGE_SYM_CLASS_NULL             0x0000
#define IMAGE_SYM_CLASS_AUTOMATIC        0x0001
#define IMAGE_SYM_CLASS_EXTERNAL         0x0002
#define IMAGE_SYM_CLASS_STATIC           0x0003
#define IMAGE_SYM_CLASS_REGISTER         0x0004
#define IMAGE_SYM_CLASS_EXTERNAL_DEF     0x0005
#define IMAGE_SYM_CLASS_LABEL            0x0006
#define IMAGE_SYM_CLASS_UNDEFINED_LABEL  0x0007
#define IMAGE_SYM_CLASS_MEMBER_OF_STRUCT 0x0008
#define IMAGE_SYM_CLASS_ARGUMENT         0x0009
#define IMAGE_SYM_CLASS_STRUCT_TAG       0x000A
#define IMAGE_SYM_CLASS_MEMBER_OF_UNION  0x000B
#define IMAGE_SYM_CLASS_UNION_TAG        0x000C
#define IMAGE_SYM_CLASS_TYPE_DEFINITION  0x000D
#define IMAGE_SYM_CLASS_UNDEFINED_STATIC 0x000E
#define IMAGE_SYM_CLASS_ENUM_TAG         0x000F
#define IMAGE_SYM_CLASS_MEMBER_OF_ENUM   0x0010
#define IMAGE_SYM_CLASS_REGISTER_PARAM   0x0011
#define IMAGE_SYM_CLASS_BIT_FIELD        0x0012
#define IMAGE_SYM_CLASS_FAR_EXTERNAL     0x0044
#define IMAGE_SYM_CLASS_BLOCK            0x0064
#define IMAGE_SYM_CLASS_FUNCTION         0x0065
#define IMAGE_SYM_CLASS_END_OF_STRUCT    0x0066
#define IMAGE_SYM_CLASS_FILE             0x0067
#define IMAGE_SYM_CLASS_SECTION          0x0068
#define IMAGE_SYM_CLASS_WEAK_EXTERNAL    0x0069
#define IMAGE_SYM_CLASS_CLR_TOKEN        0x006B

#define N_BTMASK 0x000F
#define N_TMASK  0x0030
#define N_TMASK1 0x00C0
#define N_TMASK2 0x00F0
#define N_BTSHFT 4
#define N_TSHIFT 2

#define BTYPE(x) ((x)&N_BTMASK)

#ifndef ISPTR
#define ISPTR(x) (((x)&N_TMASK) == (IMAGE_SYM_DTYPE_POINTER << N_BTSHFT))
#endif

#ifndef ISFCN
#define ISFCN(x) (((x)&N_TMASK) == (IMAGE_SYM_DTYPE_FUNCTION << N_BTSHFT))
#endif

#ifndef ISARY
#define ISARY(x) (((x)&N_TMASK) == (IMAGE_SYM_DTYPE_ARRAY << N_BTSHFT))
#endif

#ifndef ISTAG
#define ISTAG(x) ((x) == IMAGE_SYM_CLASS_STRUCT_TAG || (x) == IMAGE_SYM_CLASS_UNION_TAG || (x) == IMAGE_SYM_CLASS_ENUM_TAG)
#endif

#ifndef INCREF
#define INCREF(x) ((((x) & ~N_BTMASK) << N_TSHIFT) | (IMAGE_SYM_DTYPE_POINTER << N_BTSHFT) | ((x)&N_BTMASK))
#endif
#ifndef DECREF
#define DECREF(x) ((((x) >> N_TSHIFT) & ~N_BTMASK) | ((x)&N_BTMASK))
#endif

#include "pshpack2.h"
typedef struct IMAGE_AUX_SYMBOL_TOKEN_DEF {
	BYTE bAuxType;
	BYTE bReserved;
	DWORD SymbolTableIndex;
	BYTE rgbReserved[12];
} IMAGE_AUX_SYMBOL_TOKEN_DEF, UNALIGNED *PIMAGE_AUX_SYMBOL_TOKEN_DEF;
#include "poppack.h"

typedef union _IMAGE_AUX_SYMBOL {
	struct {
		DWORD TagIndex;
		union {
			struct {
				WORD Linenumber;
				WORD Size;
			} LnSz;
			DWORD TotalSize;
		} Misc;
		union {
			struct {
				DWORD PointerToLinenumber;
				DWORD PointerToNextFunction;
			} Function;
			struct {
				WORD Dimension[4];
			} Array;
		} FcnAry;
		WORD TvIndex;
	} Sym;
	struct {
		BYTE Name[IMAGE_SIZEOF_SYMBOL];
	} File;
	struct {
		DWORD Length;
		WORD NumberOfRelocations;
		WORD NumberOfLinenumbers;
		DWORD CheckSum;
		SHORT Number;
		BYTE Selection;
	} Section;
	IMAGE_AUX_SYMBOL_TOKEN_DEF TokenDef;
	struct {
		DWORD crc;
		BYTE rgbReserved[14];
	} CRC;
} IMAGE_AUX_SYMBOL, UNALIGNED *PIMAGE_AUX_SYMBOL;

typedef union _IMAGE_AUX_SYMBOL_EX {
	struct {
		DWORD WeakDefaultSymIndex;
		DWORD WeakSearchType;
		BYTE rgbReserved[12];
	} Sym;
	struct {
		BYTE Name[sizeof(IMAGE_SYMBOL_EX)];
	} File;
	struct {
		DWORD Length;
		WORD NumberOfRelocations;
		WORD NumberOfLinenumbers;
		DWORD CheckSum;
		SHORT Number;
		BYTE Selection;
		BYTE bReserved;
		SHORT HighNumber;
		BYTE rgbReserved[2];
	} Section;
	__C89_NAMELESS struct {
		IMAGE_AUX_SYMBOL_TOKEN_DEF TokenDef;
		BYTE rgbReserved[2];
	};
	struct {
		DWORD crc;
		BYTE rgbReserved[16];
	} CRC;
} IMAGE_AUX_SYMBOL_EX, UNALIGNED *PIMAGE_AUX_SYMBOL_EX;

#define IMAGE_SIZEOF_AUX_SYMBOL 18

typedef enum IMAGE_AUX_SYMBOL_TYPE {
	IMAGE_AUX_SYMBOL_TYPE_TOKEN_DEF = 1
} IMAGE_AUX_SYMBOL_TYPE;

#define IMAGE_COMDAT_SELECT_NODUPLICATES 1
#define IMAGE_COMDAT_SELECT_ANY          2
#define IMAGE_COMDAT_SELECT_SAME_SIZE    3
#define IMAGE_COMDAT_SELECT_EXACT_MATCH  4
#define IMAGE_COMDAT_SELECT_ASSOCIATIVE  5
#define IMAGE_COMDAT_SELECT_LARGEST      6
#define IMAGE_COMDAT_SELECT_NEWEST       7

#define IMAGE_WEAK_EXTERN_SEARCH_NOLIBRARY 1
#define IMAGE_WEAK_EXTERN_SEARCH_LIBRARY   2
#define IMAGE_WEAK_EXTERN_SEARCH_ALIAS     3

typedef struct _IMAGE_RELOCATION {
	__C89_NAMELESS union {
		DWORD VirtualAddress;
		DWORD RelocCount;
	} DUMMYUNIONNAME;
	DWORD SymbolTableIndex;
	WORD Type;
} IMAGE_RELOCATION;
typedef IMAGE_RELOCATION UNALIGNED *PIMAGE_RELOCATION;

#define IMAGE_SIZEOF_RELOCATION 10

#define IMAGE_REL_I386_ABSOLUTE 0x0000
#define IMAGE_REL_I386_DIR16    0x0001
#define IMAGE_REL_I386_REL16    0x0002
#define IMAGE_REL_I386_DIR32    0x0006
#define IMAGE_REL_I386_DIR32NB  0x0007
#define IMAGE_REL_I386_SEG12    0x0009
#define IMAGE_REL_I386_SECTION  0x000A
#define IMAGE_REL_I386_SECREL   0x000B
#define IMAGE_REL_I386_TOKEN    0x000C
#define IMAGE_REL_I386_SECREL7  0x000D
#define IMAGE_REL_I386_REL32    0x0014

#define IMAGE_REL_MIPS_ABSOLUTE  0x0000
#define IMAGE_REL_MIPS_REFHALF   0x0001
#define IMAGE_REL_MIPS_REFWORD   0x0002
#define IMAGE_REL_MIPS_JMPADDR   0x0003
#define IMAGE_REL_MIPS_REFHI     0x0004
#define IMAGE_REL_MIPS_REFLO     0x0005
#define IMAGE_REL_MIPS_GPREL     0x0006
#define IMAGE_REL_MIPS_LITERAL   0x0007
#define IMAGE_REL_MIPS_SECTION   0x000A
#define IMAGE_REL_MIPS_SECREL    0x000B
#define IMAGE_REL_MIPS_SECRELLO  0x000C
#define IMAGE_REL_MIPS_SECRELHI  0x000D
#define IMAGE_REL_MIPS_TOKEN     0x000E
#define IMAGE_REL_MIPS_JMPADDR16 0x0010
#define IMAGE_REL_MIPS_REFWORDNB 0x0022
#define IMAGE_REL_MIPS_PAIR      0x0025

#define IMAGE_REL_ALPHA_ABSOLUTE       0x0000
#define IMAGE_REL_ALPHA_REFLONG        0x0001
#define IMAGE_REL_ALPHA_REFQUAD        0x0002
#define IMAGE_REL_ALPHA_GPREL32        0x0003
#define IMAGE_REL_ALPHA_LITERAL        0x0004
#define IMAGE_REL_ALPHA_LITUSE         0x0005
#define IMAGE_REL_ALPHA_GPDISP         0x0006
#define IMAGE_REL_ALPHA_BRADDR         0x0007
#define IMAGE_REL_ALPHA_HINT           0x0008
#define IMAGE_REL_ALPHA_INLINE_REFLONG 0x0009
#define IMAGE_REL_ALPHA_REFHI          0x000A
#define IMAGE_REL_ALPHA_REFLO          0x000B
#define IMAGE_REL_ALPHA_PAIR           0x000C
#define IMAGE_REL_ALPHA_MATCH          0x000D
#define IMAGE_REL_ALPHA_SECTION        0x000E
#define IMAGE_REL_ALPHA_SECREL         0x000F
#define IMAGE_REL_ALPHA_REFLONGNB      0x0010
#define IMAGE_REL_ALPHA_SECRELLO       0x0011
#define IMAGE_REL_ALPHA_SECRELHI       0x0012
#define IMAGE_REL_ALPHA_REFQ3          0x0013
#define IMAGE_REL_ALPHA_REFQ2          0x0014
#define IMAGE_REL_ALPHA_REFQ1          0x0015
#define IMAGE_REL_ALPHA_GPRELLO        0x0016
#define IMAGE_REL_ALPHA_GPRELHI        0x0017

#define IMAGE_REL_PPC_ABSOLUTE 0x0000
#define IMAGE_REL_PPC_ADDR64   0x0001
#define IMAGE_REL_PPC_ADDR32   0x0002
#define IMAGE_REL_PPC_ADDR24   0x0003
#define IMAGE_REL_PPC_ADDR16   0x0004
#define IMAGE_REL_PPC_ADDR14   0x0005
#define IMAGE_REL_PPC_REL24    0x0006
#define IMAGE_REL_PPC_REL14    0x0007
#define IMAGE_REL_PPC_TOCREL16 0x0008
#define IMAGE_REL_PPC_TOCREL14 0x0009
#define IMAGE_REL_PPC_ADDR32NB 0x000A
#define IMAGE_REL_PPC_SECREL   0x000B
#define IMAGE_REL_PPC_SECTION  0x000C
#define IMAGE_REL_PPC_IFGLUE   0x000D
#define IMAGE_REL_PPC_IMGLUE   0x000E
#define IMAGE_REL_PPC_SECREL16 0x000F
#define IMAGE_REL_PPC_REFHI    0x0010
#define IMAGE_REL_PPC_REFLO    0x0011
#define IMAGE_REL_PPC_PAIR     0x0012
#define IMAGE_REL_PPC_SECRELLO 0x0013
#define IMAGE_REL_PPC_SECRELHI 0x0014
#define IMAGE_REL_PPC_GPREL    0x0015
#define IMAGE_REL_PPC_TOKEN    0x0016
#define IMAGE_REL_PPC_TYPEMASK 0x00FF
#define IMAGE_REL_PPC_NEG      0x0100
#define IMAGE_REL_PPC_BRTAKEN  0x0200
#define IMAGE_REL_PPC_BRNTAKEN 0x0400
#define IMAGE_REL_PPC_TOCDEFN  0x0800

#define IMAGE_REL_SH3_ABSOLUTE        0x0000
#define IMAGE_REL_SH3_DIRECT16        0x0001
#define IMAGE_REL_SH3_DIRECT32        0x0002
#define IMAGE_REL_SH3_DIRECT8         0x0003
#define IMAGE_REL_SH3_DIRECT8_WORD    0x0004
#define IMAGE_REL_SH3_DIRECT8_LONG    0x0005
#define IMAGE_REL_SH3_DIRECT4         0x0006
#define IMAGE_REL_SH3_DIRECT4_WORD    0x0007
#define IMAGE_REL_SH3_DIRECT4_LONG    0x0008
#define IMAGE_REL_SH3_PCREL8_WORD     0x0009
#define IMAGE_REL_SH3_PCREL8_LONG     0x000A
#define IMAGE_REL_SH3_PCREL12_WORD    0x000B
#define IMAGE_REL_SH3_STARTOF_SECTION 0x000C
#define IMAGE_REL_SH3_SIZEOF_SECTION  0x000D
#define IMAGE_REL_SH3_SECTION         0x000E
#define IMAGE_REL_SH3_SECREL          0x000F
#define IMAGE_REL_SH3_DIRECT32_NB     0x0010
#define IMAGE_REL_SH3_GPREL4_LONG     0x0011
#define IMAGE_REL_SH3_TOKEN           0x0012

#define IMAGE_REL_SHM_PCRELPT 0x0013
#define IMAGE_REL_SHM_REFLO   0x0014
#define IMAGE_REL_SHM_REFHALF 0x0015
#define IMAGE_REL_SHM_RELLO   0x0016
#define IMAGE_REL_SHM_RELHALF 0x0017
#define IMAGE_REL_SHM_PAIR    0x0018

#define IMAGE_REL_SH_NOMODE 0x8000

#define IMAGE_REL_ARM_ABSOLUTE   0x0000
#define IMAGE_REL_ARM_ADDR32     0x0001
#define IMAGE_REL_ARM_ADDR32NB   0x0002
#define IMAGE_REL_ARM_BRANCH24   0x0003
#define IMAGE_REL_ARM_BRANCH11   0x0004
#define IMAGE_REL_ARM_TOKEN      0x0005
#define IMAGE_REL_ARM_GPREL12    0x0006
#define IMAGE_REL_ARM_GPREL7     0x0007
#define IMAGE_REL_ARM_BLX24      0x0008
#define IMAGE_REL_ARM_BLX11      0x0009
#define IMAGE_REL_ARM_SECTION    0x000E
#define IMAGE_REL_ARM_SECREL     0x000F
#define IMAGE_REL_ARM_MOV32A     0x0010
#define IMAGE_REL_ARM_MOV32      0x0010
#define IMAGE_REL_ARM_MOV32T     0x0011
#define IMAGE_REL_THUMB_MOV32    0x0011
#define IMAGE_REL_ARM_BRANCH20T  0x0012
#define IMAGE_REL_THUMB_BRANCH20 0x0012
#define IMAGE_REL_ARM_BRANCH24T  0x0014
#define IMAGE_REL_THUMB_BRANCH24 0x0014
#define IMAGE_REL_ARM_BLX23T     0x0015
#define IMAGE_REL_THUMB_BLX23    0x0015

#define IMAGE_REL_AM_ABSOLUTE 0x0000
#define IMAGE_REL_AM_ADDR32   0x0001
#define IMAGE_REL_AM_ADDR32NB 0x0002
#define IMAGE_REL_AM_CALL32   0x0003
#define IMAGE_REL_AM_FUNCINFO 0x0004
#define IMAGE_REL_AM_REL32_1  0x0005
#define IMAGE_REL_AM_REL32_2  0x0006
#define IMAGE_REL_AM_SECREL   0x0007
#define IMAGE_REL_AM_SECTION  0x0008
#define IMAGE_REL_AM_TOKEN    0x0009

#define IMAGE_REL_AMD64_ABSOLUTE 0x0000
#define IMAGE_REL_AMD64_ADDR64   0x0001
#define IMAGE_REL_AMD64_ADDR32   0x0002
#define IMAGE_REL_AMD64_ADDR32NB 0x0003
#define IMAGE_REL_AMD64_REL32    0x0004
#define IMAGE_REL_AMD64_REL32_1  0x0005
#define IMAGE_REL_AMD64_REL32_2  0x0006
#define IMAGE_REL_AMD64_REL32_3  0x0007
#define IMAGE_REL_AMD64_REL32_4  0x0008
#define IMAGE_REL_AMD64_REL32_5  0x0009
#define IMAGE_REL_AMD64_SECTION  0x000A
#define IMAGE_REL_AMD64_SECREL   0x000B
#define IMAGE_REL_AMD64_SECREL7  0x000C
#define IMAGE_REL_AMD64_TOKEN    0x000D
#define IMAGE_REL_AMD64_SREL32   0x000E
#define IMAGE_REL_AMD64_PAIR     0x000F
#define IMAGE_REL_AMD64_SSPAN32  0x0010

#define IMAGE_REL_IA64_ABSOLUTE  0x0000
#define IMAGE_REL_IA64_IMM14     0x0001
#define IMAGE_REL_IA64_IMM22     0x0002
#define IMAGE_REL_IA64_IMM64     0x0003
#define IMAGE_REL_IA64_DIR32     0x0004
#define IMAGE_REL_IA64_DIR64     0x0005
#define IMAGE_REL_IA64_PCREL21B  0x0006
#define IMAGE_REL_IA64_PCREL21M  0x0007
#define IMAGE_REL_IA64_PCREL21F  0x0008
#define IMAGE_REL_IA64_GPREL22   0x0009
#define IMAGE_REL_IA64_LTOFF22   0x000A
#define IMAGE_REL_IA64_SECTION   0x000B
#define IMAGE_REL_IA64_SECREL22  0x000C
#define IMAGE_REL_IA64_SECREL64I 0x000D
#define IMAGE_REL_IA64_SECREL32  0x000E

#define IMAGE_REL_IA64_DIR32NB    0x0010
#define IMAGE_REL_IA64_SREL14     0x0011
#define IMAGE_REL_IA64_SREL22     0x0012
#define IMAGE_REL_IA64_SREL32     0x0013
#define IMAGE_REL_IA64_UREL32     0x0014
#define IMAGE_REL_IA64_PCREL60X   0x0015
#define IMAGE_REL_IA64_PCREL60B   0x0016
#define IMAGE_REL_IA64_PCREL60F   0x0017
#define IMAGE_REL_IA64_PCREL60I   0x0018
#define IMAGE_REL_IA64_PCREL60M   0x0019
#define IMAGE_REL_IA64_IMMGPREL64 0x001A
#define IMAGE_REL_IA64_TOKEN      0x001B
#define IMAGE_REL_IA64_GPREL32    0x001C
#define IMAGE_REL_IA64_ADDEND     0x001F

#define IMAGE_REL_CEF_ABSOLUTE 0x0000
#define IMAGE_REL_CEF_ADDR32   0x0001
#define IMAGE_REL_CEF_ADDR64   0x0002
#define IMAGE_REL_CEF_ADDR32NB 0x0003
#define IMAGE_REL_CEF_SECTION  0x0004
#define IMAGE_REL_CEF_SECREL   0x0005
#define IMAGE_REL_CEF_TOKEN    0x0006

#define IMAGE_REL_CEE_ABSOLUTE 0x0000
#define IMAGE_REL_CEE_ADDR32   0x0001
#define IMAGE_REL_CEE_ADDR64   0x0002
#define IMAGE_REL_CEE_ADDR32NB 0x0003
#define IMAGE_REL_CEE_SECTION  0x0004
#define IMAGE_REL_CEE_SECREL   0x0005
#define IMAGE_REL_CEE_TOKEN    0x0006

#define IMAGE_REL_M32R_ABSOLUTE 0x0000
#define IMAGE_REL_M32R_ADDR32   0x0001
#define IMAGE_REL_M32R_ADDR32NB 0x0002
#define IMAGE_REL_M32R_ADDR24   0x0003
#define IMAGE_REL_M32R_GPREL16  0x0004
#define IMAGE_REL_M32R_PCREL24  0x0005
#define IMAGE_REL_M32R_PCREL16  0x0006
#define IMAGE_REL_M32R_PCREL8   0x0007
#define IMAGE_REL_M32R_REFHALF  0x0008
#define IMAGE_REL_M32R_REFHI    0x0009
#define IMAGE_REL_M32R_REFLO    0x000A
#define IMAGE_REL_M32R_PAIR     0x000B
#define IMAGE_REL_M32R_SECTION  0x000C
#define IMAGE_REL_M32R_SECREL32 0x000D
#define IMAGE_REL_M32R_TOKEN    0x000E

#define IMAGE_REL_EBC_ABSOLUTE 0x0000
#define IMAGE_REL_EBC_ADDR32NB 0x0001
#define IMAGE_REL_EBC_REL32    0x0002
#define IMAGE_REL_EBC_SECTION  0x0003
#define IMAGE_REL_EBC_SECREL   0x0004

#define EXT_IMM64(Value, Address, Size, InstPos, ValPos) Value |= (((ULONGLONG)((*(Address) >> InstPos) & (((ULONGLONG)1 << Size) - 1))) << ValPos)
#define INS_IMM64(Value, Address, Size, InstPos, ValPos) *(PDWORD)Address = (*(PDWORD)Address & ~(((1 << Size) - 1) << InstPos)) | ((DWORD)((((ULONGLONG)Value >> ValPos) & (((ULONGLONG)1 << Size) - 1))) << InstPos)

#define EMARCH_ENC_I17_IMM7B_INST_WORD_X     3
#define EMARCH_ENC_I17_IMM7B_SIZE_X          7
#define EMARCH_ENC_I17_IMM7B_INST_WORD_POS_X 4
#define EMARCH_ENC_I17_IMM7B_VAL_POS_X       0

#define EMARCH_ENC_I17_IMM9D_INST_WORD_X     3
#define EMARCH_ENC_I17_IMM9D_SIZE_X          9
#define EMARCH_ENC_I17_IMM9D_INST_WORD_POS_X 18
#define EMARCH_ENC_I17_IMM9D_VAL_POS_X       7

#define EMARCH_ENC_I17_IMM5C_INST_WORD_X     3
#define EMARCH_ENC_I17_IMM5C_SIZE_X          5
#define EMARCH_ENC_I17_IMM5C_INST_WORD_POS_X 13
#define EMARCH_ENC_I17_IMM5C_VAL_POS_X       16

#define EMARCH_ENC_I17_IC_INST_WORD_X     3
#define EMARCH_ENC_I17_IC_SIZE_X          1
#define EMARCH_ENC_I17_IC_INST_WORD_POS_X 12
#define EMARCH_ENC_I17_IC_VAL_POS_X       21

#define EMARCH_ENC_I17_IMM41a_INST_WORD_X     1
#define EMARCH_ENC_I17_IMM41a_SIZE_X          10
#define EMARCH_ENC_I17_IMM41a_INST_WORD_POS_X 14
#define EMARCH_ENC_I17_IMM41a_VAL_POS_X       22

#define EMARCH_ENC_I17_IMM41b_INST_WORD_X     1
#define EMARCH_ENC_I17_IMM41b_SIZE_X          8
#define EMARCH_ENC_I17_IMM41b_INST_WORD_POS_X 24
#define EMARCH_ENC_I17_IMM41b_VAL_POS_X       32

#define EMARCH_ENC_I17_IMM41c_INST_WORD_X     2
#define EMARCH_ENC_I17_IMM41c_SIZE_X          23
#define EMARCH_ENC_I17_IMM41c_INST_WORD_POS_X 0
#define EMARCH_ENC_I17_IMM41c_VAL_POS_X       40

#define EMARCH_ENC_I17_SIGN_INST_WORD_X     3
#define EMARCH_ENC_I17_SIGN_SIZE_X          1
#define EMARCH_ENC_I17_SIGN_INST_WORD_POS_X 27
#define EMARCH_ENC_I17_SIGN_VAL_POS_X       63

#define X3_OPCODE_INST_WORD_X     3
#define X3_OPCODE_SIZE_X          4
#define X3_OPCODE_INST_WORD_POS_X 28
#define X3_OPCODE_SIGN_VAL_POS_X  0

#define X3_I_INST_WORD_X     3
#define X3_I_SIZE_X          1
#define X3_I_INST_WORD_POS_X 27
#define X3_I_SIGN_VAL_POS_X  59

#define X3_D_WH_INST_WORD_X     3
#define X3_D_WH_SIZE_X          3
#define X3_D_WH_INST_WORD_POS_X 24
#define X3_D_WH_SIGN_VAL_POS_X  0

#define X3_IMM20_INST_WORD_X     3
#define X3_IMM20_SIZE_X          20
#define X3_IMM20_INST_WORD_POS_X 4
#define X3_IMM20_SIGN_VAL_POS_X  0

#define X3_IMM39_1_INST_WORD_X     2
#define X3_IMM39_1_SIZE_X          23
#define X3_IMM39_1_INST_WORD_POS_X 0
#define X3_IMM39_1_SIGN_VAL_POS_X  36

#define X3_IMM39_2_INST_WORD_X     1
#define X3_IMM39_2_SIZE_X          16
#define X3_IMM39_2_INST_WORD_POS_X 16
#define X3_IMM39_2_SIGN_VAL_POS_X  20

#define X3_P_INST_WORD_X     3
#define X3_P_SIZE_X          4
#define X3_P_INST_WORD_POS_X 0
#define X3_P_SIGN_VAL_POS_X  0

#define X3_TMPLT_INST_WORD_X     0
#define X3_TMPLT_SIZE_X          4
#define X3_TMPLT_INST_WORD_POS_X 0
#define X3_TMPLT_SIGN_VAL_POS_X  0

#define X3_BTYPE_QP_INST_WORD_X     2
#define X3_BTYPE_QP_SIZE_X          9
#define X3_BTYPE_QP_INST_WORD_POS_X 23
#define X3_BTYPE_QP_INST_VAL_POS_X  0

#define X3_EMPTY_INST_WORD_X     1
#define X3_EMPTY_SIZE_X          2
#define X3_EMPTY_INST_WORD_POS_X 14
#define X3_EMPTY_INST_VAL_POS_X  0

typedef struct _IMAGE_LINENUMBER {
	union {
		DWORD SymbolTableIndex;
		DWORD VirtualAddress;
	} Type;
	WORD Linenumber;
} IMAGE_LINENUMBER;
typedef IMAGE_LINENUMBER UNALIGNED *PIMAGE_LINENUMBER;

#define IMAGE_SIZEOF_LINENUMBER 6

#include "poppack.h"

typedef struct _IMAGE_BASE_RELOCATION {
	DWORD VirtualAddress;
	DWORD SizeOfBlock;
} IMAGE_BASE_RELOCATION;
typedef IMAGE_BASE_RELOCATION UNALIGNED *PIMAGE_BASE_RELOCATION;

#define IMAGE_SIZEOF_BASE_RELOCATION 8

#define IMAGE_REL_BASED_ABSOLUTE       0
#define IMAGE_REL_BASED_HIGH           1
#define IMAGE_REL_BASED_LOW            2
#define IMAGE_REL_BASED_HIGHLOW        3
#define IMAGE_REL_BASED_HIGHADJ        4
#define IMAGE_REL_BASED_MIPS_JMPADDR   5
#define IMAGE_REL_BASED_ARM_MOV32      5
#define IMAGE_REL_BASED_THUMB_MOV32    7
#define IMAGE_REL_BASED_MIPS_JMPADDR16 9
#define IMAGE_REL_BASED_IA64_IMM64     9
#define IMAGE_REL_BASED_DIR64          10

#define IMAGE_ARCHIVE_START_SIZE       8
#define IMAGE_ARCHIVE_START            "!<arch>\n"
#define IMAGE_ARCHIVE_END              "`\n"
#define IMAGE_ARCHIVE_PAD              "\n"
#define IMAGE_ARCHIVE_LINKER_MEMBER    "/               "
#define IMAGE_ARCHIVE_LONGNAMES_MEMBER "//              "

typedef struct _IMAGE_ARCHIVE_MEMBER_HEADER {
	BYTE Name[16];
	BYTE Date[12];
	BYTE UserID[6];
	BYTE GroupID[6];
	BYTE Mode[8];
	BYTE Size[10];
	BYTE EndHeader[2];
} IMAGE_ARCHIVE_MEMBER_HEADER, *PIMAGE_ARCHIVE_MEMBER_HEADER;

#define IMAGE_SIZEOF_ARCHIVE_MEMBER_HDR 60

typedef struct _IMAGE_EXPORT_DIRECTORY {
	DWORD Characteristics;
	DWORD TimeDateStamp;
	WORD MajorVersion;
	WORD MinorVersion;
	DWORD Name;
	DWORD Base;
	DWORD NumberOfFunctions;
	DWORD NumberOfNames;
	DWORD AddressOfFunctions;
	DWORD AddressOfNames;
	DWORD AddressOfNameOrdinals;
} IMAGE_EXPORT_DIRECTORY, *PIMAGE_EXPORT_DIRECTORY;

typedef struct _IMAGE_IMPORT_BY_NAME {
	WORD Hint;
	CHAR Name[1];
} IMAGE_IMPORT_BY_NAME, *PIMAGE_IMPORT_BY_NAME;

#include "pshpack8.h"

typedef struct _IMAGE_THUNK_DATA64 {
	union {
		ULONGLONG ForwarderString;
		ULONGLONG Function;
		ULONGLONG Ordinal;
		ULONGLONG AddressOfData;
	} u1;
} IMAGE_THUNK_DATA64;
typedef IMAGE_THUNK_DATA64 *PIMAGE_THUNK_DATA64;

#include "poppack.h"

typedef struct _IMAGE_THUNK_DATA32 {
	union {
		DWORD ForwarderString;
		DWORD Function;
		DWORD Ordinal;
		DWORD AddressOfData;
	} u1;
} IMAGE_THUNK_DATA32;
typedef IMAGE_THUNK_DATA32 *PIMAGE_THUNK_DATA32;

#define IMAGE_ORDINAL_FLAG64             0x8000000000000000ull
#define IMAGE_ORDINAL_FLAG32             0x80000000
#define IMAGE_ORDINAL64(Ordinal)         (Ordinal & 0xffffull)
#define IMAGE_ORDINAL32(Ordinal)         (Ordinal & 0xffff)
#define IMAGE_SNAP_BY_ORDINAL64(Ordinal) ((Ordinal & IMAGE_ORDINAL_FLAG64) != 0)
#define IMAGE_SNAP_BY_ORDINAL32(Ordinal) ((Ordinal & IMAGE_ORDINAL_FLAG32) != 0)

typedef VOID(NTAPI *PIMAGE_TLS_CALLBACK)(PVOID pDllHandle, DWORD dwReason, PVOID pReserved);

typedef struct _IMAGE_TLS_DIRECTORY64 {
	ULONGLONG StartAddressOfRawData;
	ULONGLONG EndAddressOfRawData;
	ULONGLONG AddressOfIndex;
	ULONGLONG AddressOfCallBacks;
	DWORD SizeOfZeroFill;
	DWORD Characteristics;
} IMAGE_TLS_DIRECTORY64;
typedef IMAGE_TLS_DIRECTORY64 *PIMAGE_TLS_DIRECTORY64;

typedef struct _IMAGE_TLS_DIRECTORY32 {
	DWORD StartAddressOfRawData;
	DWORD EndAddressOfRawData;
	DWORD AddressOfIndex;
	DWORD AddressOfCallBacks;
	DWORD SizeOfZeroFill;
	DWORD Characteristics;
} IMAGE_TLS_DIRECTORY32;
typedef IMAGE_TLS_DIRECTORY32 *PIMAGE_TLS_DIRECTORY32;

typedef struct _IMAGE_IMPORT_DESCRIPTOR {
	__C89_NAMELESS union {
		DWORD Characteristics;
		DWORD OriginalFirstThunk;
	} DUMMYUNIONNAME;
	DWORD TimeDateStamp;

	DWORD ForwarderChain;
	DWORD Name;
	DWORD FirstThunk;
} IMAGE_IMPORT_DESCRIPTOR;
typedef IMAGE_IMPORT_DESCRIPTOR UNALIGNED *PIMAGE_IMPORT_DESCRIPTOR;

typedef struct _IMAGE_BOUND_IMPORT_DESCRIPTOR {
	DWORD TimeDateStamp;
	WORD OffsetModuleName;
	WORD NumberOfModuleForwarderRefs;
} IMAGE_BOUND_IMPORT_DESCRIPTOR, *PIMAGE_BOUND_IMPORT_DESCRIPTOR;

typedef struct _IMAGE_BOUND_FORWARDER_REF {
	DWORD TimeDateStamp;
	WORD OffsetModuleName;
	WORD Reserved;
} IMAGE_BOUND_FORWARDER_REF, *PIMAGE_BOUND_FORWARDER_REF;

typedef struct _IMAGE_DELAYLOAD_DESCRIPTOR {
	union {
		DWORD AllAttributes;
		__C89_NAMELESS struct {
			DWORD RvaBased : 1;
			DWORD ReservedAttributes : 31;
		};
	} Attributes;
	DWORD DllNameRVA;
	DWORD ModuleHandleRVA;
	DWORD ImportAddressTableRVA;
	DWORD ImportNameTableRVA;
	DWORD BoundImportAddressTableRVA;
	DWORD UnloadInformationTableRVA;
	DWORD TimeDateStamp;
} IMAGE_DELAYLOAD_DESCRIPTOR, *PIMAGE_DELAYLOAD_DESCRIPTOR;
typedef const IMAGE_DELAYLOAD_DESCRIPTOR *PCIMAGE_DELAYLOAD_DESCRIPTOR;

typedef struct _IMAGE_RESOURCE_DIRECTORY {
	DWORD Characteristics;
	DWORD TimeDateStamp;
	WORD MajorVersion;
	WORD MinorVersion;
	WORD NumberOfNamedEntries;
	WORD NumberOfIdEntries;
} IMAGE_RESOURCE_DIRECTORY, *PIMAGE_RESOURCE_DIRECTORY;

#define IMAGE_RESOURCE_NAME_IS_STRING    0x80000000
#define IMAGE_RESOURCE_DATA_IS_DIRECTORY 0x80000000

typedef struct _IMAGE_RESOURCE_DIRECTORY_ENTRY {
	__C89_NAMELESS union {
		__C89_NAMELESS struct {
			DWORD NameOffset : 31;
			DWORD NameIsString : 1;
		} DUMMYSTRUCTNAME;
		DWORD Name;
		WORD Id;
	} DUMMYUNIONNAME;
	__C89_NAMELESS union {
		DWORD OffsetToData;
		__C89_NAMELESS struct {
			DWORD OffsetToDirectory : 31;
			DWORD DataIsDirectory : 1;
		} DUMMYSTRUCTNAME2;
	} DUMMYUNIONNAME2;
} IMAGE_RESOURCE_DIRECTORY_ENTRY, *PIMAGE_RESOURCE_DIRECTORY_ENTRY;

typedef struct _IMAGE_RESOURCE_DIRECTORY_STRING {
	WORD Length;
	CHAR NameString[1];
} IMAGE_RESOURCE_DIRECTORY_STRING, *PIMAGE_RESOURCE_DIRECTORY_STRING;

typedef struct _IMAGE_RESOURCE_DIR_STRING_U {
	WORD Length;
	WCHAR NameString[1];
} IMAGE_RESOURCE_DIR_STRING_U, *PIMAGE_RESOURCE_DIR_STRING_U;

typedef struct _IMAGE_RESOURCE_DATA_ENTRY {
	DWORD OffsetToData;
	DWORD Size;
	DWORD CodePage;
	DWORD Reserved;
} IMAGE_RESOURCE_DATA_ENTRY, *PIMAGE_RESOURCE_DATA_ENTRY;

typedef struct {
	DWORD Size;
	DWORD TimeDateStamp;
	WORD MajorVersion;
	WORD MinorVersion;
	DWORD GlobalFlagsClear;
	DWORD GlobalFlagsSet;
	DWORD CriticalSectionDefaultTimeout;
	DWORD DeCommitFreeBlockThreshold;
	DWORD DeCommitTotalFreeThreshold;
	DWORD LockPrefixTable;
	DWORD MaximumAllocationSize;
	DWORD VirtualMemoryThreshold;
	DWORD ProcessHeapFlags;
	DWORD ProcessAffinityMask;
	WORD CSDVersion;
	WORD Reserved1;
	DWORD EditList;
	DWORD SecurityCookie;
	DWORD SEHandlerTable;
	DWORD SEHandlerCount;
} IMAGE_LOAD_CONFIG_DIRECTORY32, *PIMAGE_LOAD_CONFIG_DIRECTORY32;

typedef struct {
	DWORD Size;
	DWORD TimeDateStamp;
	WORD MajorVersion;
	WORD MinorVersion;
	DWORD GlobalFlagsClear;
	DWORD GlobalFlagsSet;
	DWORD CriticalSectionDefaultTimeout;
	ULONGLONG DeCommitFreeBlockThreshold;
	ULONGLONG DeCommitTotalFreeThreshold;
	ULONGLONG LockPrefixTable;
	ULONGLONG MaximumAllocationSize;
	ULONGLONG VirtualMemoryThreshold;
	ULONGLONG ProcessAffinityMask;
	DWORD ProcessHeapFlags;
	WORD CSDVersion;
	WORD Reserved1;
	ULONGLONG EditList;
	ULONGLONG SecurityCookie;
	ULONGLONG SEHandlerTable;
	ULONGLONG SEHandlerCount;
} IMAGE_LOAD_CONFIG_DIRECTORY64, *PIMAGE_LOAD_CONFIG_DIRECTORY64;

typedef struct _IMAGE_CE_RUNTIME_FUNCTION_ENTRY {
	DWORD FuncStart;
	DWORD PrologLen : 8;
	DWORD FuncLen : 22;
	DWORD ThirtyTwoBit : 1;
	DWORD ExceptionFlag : 1;
} IMAGE_CE_RUNTIME_FUNCTION_ENTRY, *PIMAGE_CE_RUNTIME_FUNCTION_ENTRY;

typedef struct _IMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY {
	ULONGLONG BeginAddress;
	ULONGLONG EndAddress;
	ULONGLONG ExceptionHandler;
	ULONGLONG HandlerData;
	ULONGLONG PrologEndAddress;
} IMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY, *PIMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY;

typedef struct _IMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY {
	DWORD BeginAddress;
	DWORD EndAddress;
	DWORD ExceptionHandler;
	DWORD HandlerData;
	DWORD PrologEndAddress;
} IMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY, *PIMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY;

typedef struct _IMAGE_ARM_RUNTIME_FUNCTION_ENTRY {
	DWORD BeginAddress;
	__C89_NAMELESS union {
		DWORD UnwindData;
		__C89_NAMELESS struct {
			DWORD Flag : 2;
			DWORD FunctionLength : 11;
			DWORD Ret : 2;
			DWORD H : 1;
			DWORD Reg : 3;
			DWORD R : 1;
			DWORD L : 1;
			DWORD C : 1;
			DWORD StackAdjust : 10;
		} DUMMYSTRUCTNAME;
	} DUMMYUNIONNAME;
} IMAGE_ARM_RUNTIME_FUNCTION_ENTRY, *PIMAGE_ARM_RUNTIME_FUNCTION_ENTRY;

typedef struct _IMAGE_ARM64_RUNTIME_FUNCTION_ENTRY {
	DWORD BeginAddress;
	__C89_NAMELESS union {
		DWORD UnwindData;
		__C89_NAMELESS struct {
			DWORD Flag : 2;
			DWORD FunctionLength : 11;
			DWORD RegF : 3;
			DWORD RegI : 4;
			DWORD H : 1;
			DWORD CR : 2;
			DWORD FrameSize : 9;
		} DUMMYSTRUCTNAME;
	} DUMMYUNIONNAME;
} IMAGE_ARM64_RUNTIME_FUNCTION_ENTRY, *PIMAGE_ARM64_RUNTIME_FUNCTION_ENTRY;

typedef struct _IMAGE_RUNTIME_FUNCTION_ENTRY {
	DWORD BeginAddress;
	DWORD EndAddress;
	__C89_NAMELESS union {
		DWORD UnwindInfoAddress;
		DWORD UnwindData;
	} DUMMYUNIONNAME;
} _IMAGE_RUNTIME_FUNCTION_ENTRY, *_PIMAGE_RUNTIME_FUNCTION_ENTRY;

typedef _IMAGE_RUNTIME_FUNCTION_ENTRY IMAGE_IA64_RUNTIME_FUNCTION_ENTRY;
typedef _PIMAGE_RUNTIME_FUNCTION_ENTRY PIMAGE_IA64_RUNTIME_FUNCTION_ENTRY;

#if defined(_AXP64_)
typedef IMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY IMAGE_AXP64_RUNTIME_FUNCTION_ENTRY;
typedef PIMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY PIMAGE_AXP64_RUNTIME_FUNCTION_ENTRY;
typedef IMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY IMAGE_RUNTIME_FUNCTION_ENTRY;
typedef PIMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY PIMAGE_RUNTIME_FUNCTION_ENTRY;
#elif defined(_ALPHA_)
typedef IMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY IMAGE_RUNTIME_FUNCTION_ENTRY;
typedef PIMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY PIMAGE_RUNTIME_FUNCTION_ENTRY;
#elif defined(__arm__)
typedef IMAGE_ARM_RUNTIME_FUNCTION_ENTRY IMAGE_RUNTIME_FUNCTION_ENTRY;
typedef PIMAGE_ARM_RUNTIME_FUNCTION_ENTRY PIMAGE_RUNTIME_FUNCTION_ENTRY;
#else
typedef _IMAGE_RUNTIME_FUNCTION_ENTRY IMAGE_RUNTIME_FUNCTION_ENTRY;
typedef _PIMAGE_RUNTIME_FUNCTION_ENTRY PIMAGE_RUNTIME_FUNCTION_ENTRY;
#endif

typedef struct _IMAGE_DEBUG_DIRECTORY {
	DWORD Characteristics;
	DWORD TimeDateStamp;
	WORD MajorVersion;
	WORD MinorVersion;
	DWORD Type;
	DWORD SizeOfData;
	DWORD AddressOfRawData;
	DWORD PointerToRawData;
} IMAGE_DEBUG_DIRECTORY, *PIMAGE_DEBUG_DIRECTORY;

#define IMAGE_DEBUG_TYPE_UNKNOWN       0
#define IMAGE_DEBUG_TYPE_COFF          1
#define IMAGE_DEBUG_TYPE_CODEVIEW      2
#define IMAGE_DEBUG_TYPE_FPO           3
#define IMAGE_DEBUG_TYPE_MISC          4
#define IMAGE_DEBUG_TYPE_EXCEPTION     5
#define IMAGE_DEBUG_TYPE_FIXUP         6
#define IMAGE_DEBUG_TYPE_OMAP_TO_SRC   7
#define IMAGE_DEBUG_TYPE_OMAP_FROM_SRC 8
#define IMAGE_DEBUG_TYPE_BORLAND       9
#define IMAGE_DEBUG_TYPE_RESERVED10    10
#define IMAGE_DEBUG_TYPE_CLSID         11

typedef struct _IMAGE_COFF_SYMBOLS_HEADER {
	DWORD NumberOfSymbols;
	DWORD LvaToFirstSymbol;
	DWORD NumberOfLinenumbers;
	DWORD LvaToFirstLinenumber;
	DWORD RvaToFirstByteOfCode;
	DWORD RvaToLastByteOfCode;
	DWORD RvaToFirstByteOfData;
	DWORD RvaToLastByteOfData;
} IMAGE_COFF_SYMBOLS_HEADER, *PIMAGE_COFF_SYMBOLS_HEADER;

#define FRAME_FPO    0
#define FRAME_TRAP   1
#define FRAME_TSS    2
#define FRAME_NONFPO 3

typedef struct _FPO_DATA {
	DWORD ulOffStart;
	DWORD cbProcSize;
	DWORD cdwLocals;
	WORD cdwParams;
	WORD cbProlog : 8;
	WORD cbRegs : 3;
	WORD fHasSEH : 1;
	WORD fUseBP : 1;
	WORD reserved : 1;
	WORD cbFrame : 2;
} FPO_DATA, *PFPO_DATA;
#define SIZEOF_RFPO_DATA 16

#define IMAGE_DEBUG_MISC_EXENAME 1

typedef struct _IMAGE_DEBUG_MISC {
	DWORD DataType;
	DWORD Length;
	BOOLEAN Unicode;
	BYTE Reserved[3];
	BYTE Data[1];
} IMAGE_DEBUG_MISC, *PIMAGE_DEBUG_MISC;

typedef struct _IMAGE_FUNCTION_ENTRY {
	DWORD StartingAddress;
	DWORD EndingAddress;
	DWORD EndOfPrologue;
} IMAGE_FUNCTION_ENTRY, *PIMAGE_FUNCTION_ENTRY;

typedef struct _IMAGE_FUNCTION_ENTRY64 {
	ULONGLONG StartingAddress;
	ULONGLONG EndingAddress;
	__C89_NAMELESS union {
		ULONGLONG EndOfPrologue;
		ULONGLONG UnwindInfoAddress;
	} DUMMYUNIONNAME;
} IMAGE_FUNCTION_ENTRY64, *PIMAGE_FUNCTION_ENTRY64;

typedef struct _IMAGE_SEPARATE_DEBUG_HEADER {
	WORD Signature;
	WORD Flags;
	WORD Machine;
	WORD Characteristics;
	DWORD TimeDateStamp;
	DWORD CheckSum;
	DWORD ImageBase;
	DWORD SizeOfImage;
	DWORD NumberOfSections;
	DWORD ExportedNamesSize;
	DWORD DebugDirectorySize;
	DWORD SectionAlignment;
	DWORD Reserved[2];
} IMAGE_SEPARATE_DEBUG_HEADER, *PIMAGE_SEPARATE_DEBUG_HEADER;

typedef struct _NON_PAGED_DEBUG_INFO {
	WORD Signature;
	WORD Flags;
	DWORD Size;
	WORD Machine;
	WORD Characteristics;
	DWORD TimeDateStamp;
	DWORD CheckSum;
	DWORD SizeOfImage;
	ULONGLONG ImageBase;
} NON_PAGED_DEBUG_INFO, *PNON_PAGED_DEBUG_INFO;

#define IMAGE_SEPARATE_DEBUG_SIGNATURE 0x4944
#define NON_PAGED_DEBUG_SIGNATURE      0x494E

#define IMAGE_SEPARATE_DEBUG_FLAGS_MASK 0x8000
#define IMAGE_SEPARATE_DEBUG_MISMATCH   0x8000

typedef struct _ImageArchitectureHeader {
	unsigned int AmaskValue : 1;
	int Adummy1 : 7;
	unsigned int AmaskShift : 8;
	int Adummy2 : 16;
	DWORD FirstEntryRVA;
} IMAGE_ARCHITECTURE_HEADER, *PIMAGE_ARCHITECTURE_HEADER;

typedef struct _ImageArchitectureEntry {
	DWORD FixupInstRVA;
	DWORD NewInst;
} IMAGE_ARCHITECTURE_ENTRY, *PIMAGE_ARCHITECTURE_ENTRY;

#define IMPORT_OBJECT_HDR_SIG2 0xffff

typedef struct IMPORT_OBJECT_HEADER {
	WORD Sig1;
	WORD Sig2;
	WORD Version;
	WORD Machine;
	DWORD TimeDateStamp;
	DWORD SizeOfData;
	__C89_NAMELESS union {
		WORD Ordinal;
		WORD Hint;
	};
	WORD Type : 2;
	WORD NameType : 3;
	WORD Reserved : 11;
} IMPORT_OBJECT_HEADER;

typedef enum IMPORT_OBJECT_TYPE {
	IMPORT_OBJECT_CODE  = 0,
	IMPORT_OBJECT_DATA  = 1,
	IMPORT_OBJECT_CONST = 2
} IMPORT_OBJECT_TYPE;

typedef enum IMPORT_OBJECT_NAME_TYPE {
	IMPORT_OBJECT_ORDINAL         = 0,
	IMPORT_OBJECT_NAME            = 1,
	IMPORT_OBJECT_NAME_NO_PREFIX  = 2,
	IMPORT_OBJECT_NAME_UNDECORATE = 3
} IMPORT_OBJECT_NAME_TYPE;

#ifndef __IMAGE_COR20_HEADER_DEFINED__
#define __IMAGE_COR20_HEADER_DEFINED__
typedef enum ReplacesCorHdrNumericDefines {
	COMIMAGE_FLAGS_ILONLY                = 0x00000001,
	COMIMAGE_FLAGS_32BITREQUIRED         = 0x00000002,
	COMIMAGE_FLAGS_IL_LIBRARY            = 0x00000004,
	COMIMAGE_FLAGS_STRONGNAMESIGNED      = 0x00000008,
	COMIMAGE_FLAGS_TRACKDEBUGDATA        = 0x00010000,
	COR_VERSION_MAJOR_V2                 = 2,
	COR_VERSION_MAJOR                    = COR_VERSION_MAJOR_V2,
	COR_VERSION_MINOR                    = 0,
	COR_DELETED_NAME_LENGTH              = 8,
	COR_VTABLEGAP_NAME_LENGTH            = 8,
	NATIVE_TYPE_MAX_CB                   = 1,
	COR_ILMETHOD_SECT_SMALL_MAX_DATASIZE = 0xFF,
	IMAGE_COR_MIH_METHODRVA              = 0x01,
	IMAGE_COR_MIH_EHRVA                  = 0x02,
	IMAGE_COR_MIH_BASICBLOCK             = 0x08,
	COR_VTABLE_32BIT                     = 0x01,
	COR_VTABLE_64BIT                     = 0x02,
	COR_VTABLE_FROM_UNMANAGED            = 0x04,
	COR_VTABLE_CALL_MOST_DERIVED         = 0x10,
	IMAGE_COR_EATJ_THUNK_SIZE            = 32,
	MAX_CLASS_NAME                       = 1024,
	MAX_PACKAGE_NAME                     = 1024
} ReplacesCorHdrNumericDefines;

typedef struct IMAGE_COR20_HEADER {
	DWORD cb;
	WORD MajorRuntimeVersion;
	WORD MinorRuntimeVersion;
	IMAGE_DATA_DIRECTORY MetaData;
	DWORD Flags;
	__C89_NAMELESS union {
		DWORD EntryPointToken;
		DWORD EntryPointRVA;
	} DUMMYUNIONNAME;
	IMAGE_DATA_DIRECTORY Resources;
	IMAGE_DATA_DIRECTORY StrongNameSignature;
	IMAGE_DATA_DIRECTORY CodeManagerTable;
	IMAGE_DATA_DIRECTORY VTableFixups;
	IMAGE_DATA_DIRECTORY ExportAddressTableJumps;
	IMAGE_DATA_DIRECTORY ManagedNativeHeader;
} IMAGE_COR20_HEADER, *PIMAGE_COR20_HEADER;
#endif



#if __SIZEOF_POINTER__ >= 8
typedef IMAGE_OPTIONAL_HEADER64 IMAGE_OPTIONAL_HEADER;
typedef PIMAGE_OPTIONAL_HEADER64 PIMAGE_OPTIONAL_HEADER;
#define IMAGE_SIZEOF_NT_OPTIONAL_HEADER IMAGE_SIZEOF_NT_OPTIONAL64_HEADER
#define IMAGE_NT_OPTIONAL_HDR_MAGIC     IMAGE_NT_OPTIONAL_HDR64_MAGIC

typedef IMAGE_NT_HEADERS64 IMAGE_NT_HEADERS;
typedef PIMAGE_NT_HEADERS64 PIMAGE_NT_HEADERS;

#define IMAGE_ORDINAL_FLAG     IMAGE_ORDINAL_FLAG64
#define IMAGE_ORDINAL(Ordinal) IMAGE_ORDINAL64(Ordinal)
typedef IMAGE_THUNK_DATA64 IMAGE_THUNK_DATA;
typedef PIMAGE_THUNK_DATA64 PIMAGE_THUNK_DATA;
#define IMAGE_SNAP_BY_ORDINAL(Ordinal) IMAGE_SNAP_BY_ORDINAL64(Ordinal)
typedef IMAGE_TLS_DIRECTORY64 IMAGE_TLS_DIRECTORY;
typedef PIMAGE_TLS_DIRECTORY64 PIMAGE_TLS_DIRECTORY;

typedef IMAGE_LOAD_CONFIG_DIRECTORY64 IMAGE_LOAD_CONFIG_DIRECTORY;
typedef PIMAGE_LOAD_CONFIG_DIRECTORY64 PIMAGE_LOAD_CONFIG_DIRECTORY;
#else /* __SIZEOF_POINTER__ >= 8 */

typedef IMAGE_OPTIONAL_HEADER32 IMAGE_OPTIONAL_HEADER;
typedef PIMAGE_OPTIONAL_HEADER32 PIMAGE_OPTIONAL_HEADER;
#define IMAGE_SIZEOF_NT_OPTIONAL_HEADER IMAGE_SIZEOF_NT_OPTIONAL32_HEADER
#define IMAGE_NT_OPTIONAL_HDR_MAGIC     IMAGE_NT_OPTIONAL_HDR32_MAGIC

typedef IMAGE_NT_HEADERS32 IMAGE_NT_HEADERS;
typedef PIMAGE_NT_HEADERS32 PIMAGE_NT_HEADERS;

#define IMAGE_ORDINAL_FLAG             IMAGE_ORDINAL_FLAG32
#define IMAGE_ORDINAL(Ordinal)         IMAGE_ORDINAL32(Ordinal)
typedef IMAGE_THUNK_DATA32 IMAGE_THUNK_DATA;
typedef PIMAGE_THUNK_DATA32 PIMAGE_THUNK_DATA;
#define IMAGE_SNAP_BY_ORDINAL(Ordinal) IMAGE_SNAP_BY_ORDINAL32(Ordinal)
typedef IMAGE_TLS_DIRECTORY32 IMAGE_TLS_DIRECTORY;
typedef PIMAGE_TLS_DIRECTORY32 PIMAGE_TLS_DIRECTORY;

typedef IMAGE_LOAD_CONFIG_DIRECTORY32 IMAGE_LOAD_CONFIG_DIRECTORY;
typedef PIMAGE_LOAD_CONFIG_DIRECTORY32 PIMAGE_LOAD_CONFIG_DIRECTORY;
#endif /* __SIZEOF_POINTER__ < 8 */


__DECL_END
#endif /* __CC__ */

#endif /* !_NT_PE_H */
