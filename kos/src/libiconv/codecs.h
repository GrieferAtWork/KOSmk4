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
#ifndef GUARD_LIBICONV_CODECS_H
#define GUARD_LIBICONV_CODECS_H 1

#include "api.h"
/**/

#include <hybrid/byteorder.h>

#include <kos/types.h>

#include <libiconv/iconv.h>

DECL_BEGIN

/* Sources:
 *   - https://en.wikipedia.org/wiki/Category:DOS_code_pages
 *   - https://en.wikipedia.org/wiki/Category:ISO/IEC_8859
 *   - https://en.wikipedia.org/wiki/ISO/IEC_646
 *   - GLibc
 */


/* Codec IDs. */
enum {
	CODEC_UNKNOWN, /* Invalid codec */
/*[[[begin:codecs]]]*/
	CODEC_ASCII,       /* "iso-ir-6", "ANSI_X3.4", "ANSI_X3.4-1968", "ANSI_X3.4-1986", "ISO_646.irv:1991", "ISO646-US", "us", "IBM367", "cp367", "us-ascii", "ascii", "CSASCII", "OSF00010020" */
	CODEC_UTF8,        /* "UTF8", "UTF-8", "ISO-10646/UTF8", "ISO-10646/UTF-8", "iso-ir-193", "OSF05010001" */
	CODEC_UTF16LE,     /* "UTF16LE", "UTF-16LE", "UCS-2LE", "UNICODELITTLE" */
	CODEC_UTF16BE,     /* "UTF16BE", "UTF-16BE", "UCS-2BE", "UNICODEBIG" */
	CODEC_UTF32LE,     /* "UTF32LE", "UTF-32LE", "UCS-4LE" */
	CODEC_UTF32BE,     /* "UTF32BE", "UTF-32BE", "UCS-4BE" */
	CODEC_CP437,       /* "IBM437", "cp437", "437", "csPC8CodePage437", "OEM-US", "OSF100201B5" */
	CODEC_CP667,       /* "MAZOVIA", "cp667", "cp790", "cp991", "MAZ" */
	CODEC_CP668,       /* "cp668" */
	CODEC_CP708,       /* "cp708", "IBM708" */
	CODEC_CP720,       /* "cp720", "IBM720", "OEM-720" */
	CODEC_CP737,       /* "cp737", "IBM737", "OEM-737" */
	CODEC_CP770,       /* "cp770" */
	CODEC_CP771,       /* "cp771", "KBL" */
	CODEC_CP772,       /* "cp772", "LST-1284", "LST-1284:1993", "cp1119" */
	CODEC_CP773,       /* "cp773" */
	CODEC_CP774,       /* "cp774", "cp1118", "IBM1118", "LST-1283" */
	CODEC_CP775,       /* "cp775", "IBM775", "OEM-775" */
	CODEC_CP808,       /* "cp808" */
	CODEC_CP848,       /* "cp848" */
	CODEC_CP849,       /* "cp849" */
	CODEC_CP850,       /* "cp850", "IBM850", "850", "csPC850Multilingual", "OEM-850" */
	CODEC_CP851,       /* "cp851", "IBM851", "851" */
	CODEC_CP852,       /* "cp852", "IBM852", "852", "csPCp852" */
	CODEC_CP853,       /* "cp853", "IBM853" */
	CODEC_CP855,       /* "cp855", "IBM855", "855", "OEM-855" */
	CODEC_CP856,       /* "cp856", "IBM856" */
	CODEC_CP857,       /* "cp857", "IBM857", "857", "OEM-857" */
	CODEC_CP858,       /* "cp858", "IBM858", "OEM-858", "PC-Multilingual-850+euro" */
	CODEC_CP859,       /* "cp859", "IBM859" */
	CODEC_CP860,       /* "cp860", "IBM860", "860", "OEM-860" */
	CODEC_CP861,       /* "cp861", "IBM861", "861", "OEM-861", "cp-is" */
	CODEC_CP862,       /* "cp862", "IBM862", "862", "OEM-862", "csPC862LatinHebrew" */
	CODEC_CP863,       /* "cp863", "IBM863", "863", "OEM-863" */
	CODEC_CP864,       /* "cp864", "IBM864" */
	CODEC_CP865,       /* "cp865", "IBM865", "865", "OEM-865" */
	CODEC_CP866,       /* "cp866", "866", "IBM866" */
	CODEC_CP867,       /* "cp867" */
	CODEC_CP868,       /* "cp868", "IBM868", "cp-ar" */
	CODEC_CP869,       /* "cp869", "IBM869", "OEM-869", "869", "cp-gr" */
	CODEC_CP872,       /* "cp872" */
	CODEC_CP897,       /* "cp897" */
	CODEC_CP901,       /* "cp901" */
	CODEC_CP902,       /* "cp902", "IBM902" */
	CODEC_CP912,       /* "cp912", "IBM912" */
	CODEC_CP915,       /* "cp915", "IBM915" */
	CODEC_CP921,       /* "cp921", "IBM921" */
	CODEC_CP922,       /* "cp922", "IBM922", "Estonia-ISO-8" */
	CODEC_CP1041,      /* "cp1041" */
	CODEC_CP1057,      /* "cp1057", "HP-PC-8" */
	CODEC_CP1098,      /* "cp1098", "IBM1098" */
	CODEC_CP1116,      /* "cp1116", "IBM1116" */
	CODEC_CP1117,      /* "cp1117", "IBM1117" */
	CODEC_CP1125,      /* "cp1125", "RST-2018-91 ", "CP866U", "CP866NAV", "RUSCII" */
	CODEC_CP1131,      /* "cp1131" */
	CODEC_CP17248,     /* "cp17248" */
	CODEC_KOI_8_N1,    /* "KOI-8-N1" */
	CODEC_KOI_8_N2,    /* "KOI-8-N2" */
	CODEC_CP3012,      /* "cp3012", "RusLat" */
	CODEC_KEYBCS2,     /* "NEC-867", "DOS-895", "KEYBCS2", "KAMENICKY" */
	CODEC_MIK,         /* "MIK", "BULGARIA-PC" */
	CODEC_DIN_66303,   /* "DIN_66303", "DRV8" */
	CODEC_ISO_8859_1,  /* "ISO-8859-1", "iso-ir-100", "csISOLatin1", "latin1", "l1", "IBM819", "CP819" */
	CODEC_ISO_8859_2,  /* "ISO-8859-2", "iso-ir-101", "csISOLatin2", "latin2", "l2", "IBM1111" */
	CODEC_ISO_8859_3,  /* "ISO-8859-3", "iso-ir-109", "csISOLatin3", "latin3", "l3" */
	CODEC_ISO_8859_4,  /* "ISO-8859-4", "iso-ir-110", "csISOLatin4", "latin4", "l4" */
	CODEC_ISO_8859_5,  /* "ISO-8859-5", "iso-ir-144", "csISOLatinCyrillic", "cyrillic" */
	CODEC_ISO_8859_6,  /* "ISO-8859-6", "iso-ir-127", "csISOLatinArabic", "ECMA-114", "ASMO-708", "arabic" */
	CODEC_ISO_8859_7,  /* "ISO-8859-7", "iso-ir-126", "csISOLatinGreek", "ELOT_928", "ECMA-118", "greek", "greek8" */
	CODEC_ISO_8859_8,  /* "ISO-8859-8", "iso-ir-138", "csISOLatinHebrew", "hebrew" */
	CODEC_ISO_8859_9,  /* "ISO-8859-9", "iso-ir-148", "csISOLatin5", "latin5", "l5" */
	CODEC_ISO_8859_10, /* "ISO-8859-10", "iso-ir-157", "csISOLatin6", "latin6", "l6" */
	CODEC_ISO_8859_11, /* "ISO-8859-11" */
	CODEC_ISO_8859_13, /* "ISO-8859-13", "iso-ir-179", "csISOLatin7", "latin7", "l7" */
	CODEC_ISO_8859_14, /* "ISO-8859-14", "iso-ir-199", "iso-celtic", "latin8", "l8" */
	CODEC_ISO_8859_15, /* "ISO-8859-15", "latin-9", "latin-0" */
	CODEC_ISO_8859_16, /* "ISO-8859-16", "iso-ir-226", "latin10", "l10" */
	CODEC_ISO_IR_182,  /* "iso-ir-182" */
	CODEC_ISO_IR_197,  /* "iso-ir-197" */
	CODEC_ISO_IR_200,  /* "iso-ir-200" */

	/* iso646 (keep these sorted alphabetically!) */
#define CODEC_ISO646_MIN CODEC_ISO646_CA
	CODEC_ISO646_CA,             /* "ISO646-CA", "iso-ir-121", "CSA_Z243.4-1985-1", "CSA7-1", "CA", "csISO121Canadian1", "CSA_Z243.419851", "cp1020" */
	CODEC_ISO646_CA2,            /* "ISO646-CA2", "iso-ir-122", "CSA_Z243.4-1985-2", "CSA7-2", "csISO122Canadian2", "CSA_Z243.419852" */
	CODEC_ISO646_CN,             /* "ISO646-CN", "iso-ir-57", "CN", "csISO58GB1988", "GB_1988-80", "GB_198880" */
	CODEC_ISO646_CU,             /* "ISO646-CU", "CUBA", "NC_NC00-10", "NC_NC00-10:81", "iso-ir-151", "csISO151Cuba", "NC_NC0010" */
	CODEC_ISO646_DANO_NATS,      /* "ISO-IR-9" */
	CODEC_ISO646_DE,             /* "ISO646-DE", "iso-ir-21", "DIN_66003", "IBM1011", "MS-10206", "csISO21German", "GERMAN", "DE", "D7DEC", "cp1011", "cp20106" */
	CODEC_ISO646_DK,             /* "ISO646-DK", "DS2089", "DS_2089", "DK", "csISO646Danish", "cp1017" */
	CODEC_ISO646_DK_NO_ALT_NRCS, /* "cp1107", "IBM1107" */
	CODEC_ISO646_DK_NO_NRCS,     /* "cp1105", "IBM1105" */
	CODEC_ISO646_ES,             /* "ISO646-ES", "iso-ir-17", "ES", "csISO17Spanish", "cp1023" */
	CODEC_ISO646_ES2,            /* "ISO646-ES2", "iso-ir-85", "ES2", "csISO85Spanish2", "cp1014" */
	CODEC_ISO646_FI_NRCS,        /* "cp1103", "IBM1103" */
	CODEC_ISO646_FR,             /* "ISO646-FR", "iso-ir-69", "NF_Z_62-010", "NF_Z_62-010_1983", "NF_Z_62-010_(1983)", "FR", "csISO69French", "NF_Z_62010" */
	CODEC_ISO646_FR1,            /* "ISO646-FR1", "iso-ir-25", "NF_Z_62-010_1973", "NF_Z_62-010_(1973)", "csISO25French", "NF_Z_62010_1973" */
	CODEC_ISO646_GB,             /* "ISO646-GB", "iso-ir-4", "BS_4730", "GB", "UK", "csISO4Unitedkingdom" */
	CODEC_ISO646_GB_NRCS,        /* "cp1101", "IBM1101" */
	CODEC_ISO646_HU,             /* "ISO646-HU", "iso-ir-86", "MSZ_7795.3", "HU", "csISO86Hungarian" */
	CODEC_ISO646_IE,             /* "ISO646-IE", "iso-ir-207" */
	CODEC_ISO646_INIS_SUBSET,    /* "ISO-IR-49" */
	CODEC_ISO646_INV,            /* "ISO-IR-170" */
	CODEC_ISO646_IRV_1973,       /* "ISO-IR-2" */
	CODEC_ISO646_IRV_1983,       /* "cp1009", "IBM1009" */
	CODEC_ISO646_IS,             /* "ISO646-IS" */
	CODEC_ISO646_IT,             /* "ISO646-IT", "iso-ir-15", "IT", "csISO15Italian" */
	CODEC_ISO646_JP,             /* "ISO646-JP", "iso-ir-14", "JIS_C6220-1969-RO", "JP", "csISO14JISC6220RO", "JIS_C62201969RO" */
	CODEC_ISO646_JP_OCR_B,       /* "ISO646-JP-OCR-B", "iso-ir-92", "JIS_C6229-1984-B", "JP-OCR-B", "csISO92JISC62991984B", "JIS_C62291984B" */
	CODEC_ISO646_KR,             /* "ISO646-KR", "KSC5636", "CSKSC5636", "KS-X-1003", "KSC5636-1989" */
	CODEC_ISO646_LATIN_GR_MIXED, /* "ISO-IR-27" */
	CODEC_ISO646_MT,             /* "ISO646-MT" */
	CODEC_ISO646_NL,             /* "ISO646-NL", "cp1019", "IBM1019" */
	CODEC_ISO646_NL_NRCS,        /* "cp1102", "IBM1102" */
	CODEC_ISO646_NO,             /* "ISO646-NO", "iso-ir-60", "NS_4551-1", "NO", "csISO60DanishNorwegian", "csISO60Norwegian1", "NS_45511" */
	CODEC_ISO646_NO2,            /* "ISO646-NO2", "NS_4551-2", "iso-ir-61", "NO2", "csISO61Norwegian2", "NS_45512" */
	CODEC_ISO646_PL,             /* "BN-74/3101-01" */
	CODEC_ISO646_PT,             /* "ISO646-PT", "iso-ir-16", "PT", "csISO16Portugese" */
	CODEC_ISO646_PT2,            /* "ISO646-PT2", "iso-ir-84", "PT2", "csISO84Portuguese2" */
	CODEC_ISO646_SE,             /* "ISO646-SE", "iso-ir-10", "SEN_850200_B", "FI", "ISO646-FI", "SE", "csISO10Swedish", "SS636127" */
	CODEC_ISO646_SE2,            /* "ISO646-SE2", "iso-ir-11", "SEN_850200_C", "SE2", "csISO11Swedishfornames" */
	CODEC_ISO646_SEFI_NATS,      /* "ISO-IR-8" */
	CODEC_ISO646_SE_NRCS,        /* "cp1106", "IBM1106" */
	CODEC_ISO646_SWI_NRCS,       /* "cp1021", "IBM1021" */
	CODEC_ISO646_T_61,           /* "ISO-IR-102" */
	CODEC_ISO646_VIEWDATA,       /* "ISO-IR-47" */
	CODEC_ISO646_YU,             /* "ISO646-YU", "JUS_I.B1.002", "JS", "YU", "csISO141Jusib1002" */
#define CODEC_ISO646_MAX CODEC_ISO646_YU
#define CODEC_ISISO646(x) ((x) >= CODEC_ISO646_MIN && (x) <= CODEC_ISO646_MAX)


	/* Aliases */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	CODEC_UTF16 = CODEC_UTF16LE, /* "UTF16", "UTF-16", "ISO-10646/UCS2", "UCS2", "UCS-2", "OSF00010100", "OSF00010101", "OSF00010102" */
	CODEC_UTF32 = CODEC_UTF32LE, /* "UTF32", "UTF-32", "ISO-10646/UCS4", "UCS4", "UCS-4", "CSUCS4", "ISO-10646", "10646-1:1993", "10646-1:1993/UCS4", "OSF00010104", "OSF00010105", "OSF00010106" */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
/**/CODEC_UTF16 = CODEC_UTF16BE,
/**/CODEC_UTF32 = CODEC_UTF32BE,
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
#if __SIZEOF_WCHAR_T__ == 2
	CODEC_WCHAR_T = CODEC_UTF16, /* "WCHAR_T" */
#else /* __SIZEOF_WCHAR_T__ == 2 */
/**/CODEC_WCHAR_T = CODEC_UTF32,
#endif /* __SIZEOF_WCHAR_T__ != 2 */

/*[[[end:codecs]]]*/
};

/* Return the ID of the codec associated with `name'
 * Casing is ignored and codec aliases are respected. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) unsigned int
NOTHROW_NCX(FCALL libiconv_codecbyname)(char const *__restrict name);

/* Return the nth (0-based) alphabetically sorted name for the codec `id'
 * When `id' is invalid or doesn't have an `nth' name, return `NULL' */
INTDEF ATTR_CONST WUNUSED char const *
NOTHROW_NCX(FCALL libiconv_getcodecname)(unsigned int id, unsigned int nth);



DECL_END

#endif /* !GUARD_LIBICONV_CODECS_H */
