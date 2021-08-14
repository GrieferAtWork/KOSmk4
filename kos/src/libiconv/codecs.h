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



/* TODO:
 *  - cp776: https://en.wikipedia.org/wiki/Code_page_776
 *  - cp777: https://en.wikipedia.org/wiki/Code_page_777
 *  - cp778: https://en.wikipedia.org/wiki/Code_page_778
 *  - cp907: https://en.wikipedia.org/wiki/Code_page_907
 *  - cp907: https://en.wikipedia.org/wiki/CSX%2B_Indic_character_set
 *  - https://en.wikipedia.org/wiki/HP_Roman
 *  - https://en.wikipedia.org/wiki/GBK_(character_encoding)
 *  - https://www.iana.org/assignments/character-sets/character-sets.xhtml
 *  - https://en.wikipedia.org/wiki/LST_1564
 *  - https://en.wikipedia.org/wiki/LST_1590-4
 *  - https://en.wikipedia.org/wiki/JIS_X_0208
 *  - https://en.wikipedia.org/wiki/ArmSCII
 *  - https://en.wikipedia.org/wiki/Mac_OS_Hebrew
 *  - https://en.wikipedia.org/wiki/Mac_OS_Keyboard_encoding
 *  - https://en.wikipedia.org/wiki/ISO/IEC_2022
 *  - https://en.wikipedia.org/wiki/ISO-IR-165
 *  - https://en.wikipedia.org/wiki/ISO-IR-169
 *  - https://en.wikipedia.org/wiki/KOI-7 ("KOI7", "KOI7-switched", "csKOI7switched")
 */

/* TODO: Still more code pages can be found here:
 *  - https://en.wikipedia.org/wiki/Category:Character_sets
 *  - https://ftp.unicode.org/Public/MAPPINGS/
 *  - https://en.wikipedia.org/wiki/Category:Windows_code_pages
 */


/* TODO:
 *   - Codec "c-escape" for encoding/decoding using the C \-notation
 *     - Also  2  sub-codecs "c-escape-chr"  and c-escape-str"  that add
 *       additional  '  or "  pairs during  encoding,  as well  as parse
 *       surrounding pairs during decoding (and stop decoding data  with
 *       an error when more input data is fed after the trailing ' or ")
 *   - Codec "xml-escape" for &lt;xml-style&gt; escaping (https://en.wikipedia.org/wiki/XML)
 *   - Codec "uri-escape" for %3Curi-style%3E escaping (https://en.wikipedia.org/wiki/Percent-encoding)
 */


/* Codec IDs. */
enum {
	CODEC_UNKNOWN, /* Invalid codec */
/*[[[begin:codecs]]]*/
	CODEC_ASCII,       /* "iso-ir-6", "ANSI_X3.4", "ANSI_X3.4-1968", "ANSI_X3.4-1986", "ISO646.irv:1991", "ISO646-US", "us", "IBM367", "cp367", "us-ascii", "ascii", "CSASCII", "OSF00010020", "cp20127", "Windows-20127" */
	CODEC_UTF8,        /* "UTF8", "UTF-8", "ISO10646/UTF8", "ISO10646/UTF-8", "iso-ir-193", "OSF05010001", "cp65001", "Windows-65001" */
	CODEC_UTF16LE,     /* "UTF16LE", "UTF-16LE", "UCS-2LE", "UNICODELITTLE" */
	CODEC_UTF16BE,     /* "UTF16BE", "UTF-16BE", "UCS-2BE", "UNICODEBIG" */
	CODEC_UTF32LE,     /* "UTF32LE", "UTF-32LE", "UCS-4LE" */
	CODEC_UTF32BE,     /* "UTF32BE", "UTF-32BE", "UCS-4BE", "cp12001", "Windows-12001" */
	CODEC_ISO_8859_1,  /* "ISO8859-1", "iso-ir-100", "csISOLatin1", "latin1", "l1", "IBM819", "cp819", "cp28591", "Windows-28591", "WE8ISO8859P1", "cp38591", "Windows-38591", "ISO8859-1-I" */

	/* 8-bit codepage codecs (IMPORTANT: keep these sorted lexicographically!) */
#define CODEC_CP_MIN CODEC_CP1004
	CODEC_CP1004,      /* "cp1004", "Windows-Extended" */
	CODEC_CP1006,      /* "cp1006", "IBM1006", "ISO-8-bit-Urdu" */
	CODEC_CP1008,      /* "cp1008", "IBM1008", "cp5104", "IBM5104" */
	CODEC_CP1038,      /* "cp1038", "IBM1038", "x-mac-symbol" */
	CODEC_CP1040,      /* "cp1040" */
	CODEC_CP1041,      /* "cp1041" */
	CODEC_CP1042,      /* "cp1042" */
	CODEC_CP1043,      /* "cp1043" */
	CODEC_CP1046,      /* "cp1046" */
	CODEC_CP1050,      /* "cp1050", "HP-Roman-8", "cp1051" */
	CODEC_CP1057,      /* "cp1057", "HP-PC-8" */
	CODEC_CP1088,      /* "cp1088" */
	CODEC_CP1098,      /* "cp1098", "IBM1098" */
	CODEC_CP1114,      /* "cp1114" */
	CODEC_CP1115,      /* "cp1115" */
	CODEC_CP1127,      /* "cp1127" */
	CODEC_CP1276,      /* "cp1276", "PostScript-Standard-Encoding", "StandardEncoding", "PostScript" */
	CODEC_CP17248,     /* "cp17248" */
	CODEC_CP864,       /* "cp864", "IBM864" */
	CODEC_CP897,       /* "cp897" */
	CODEC_CP901,       /* "cp901", "IBM901" */
	CODEC_CP902,       /* "cp902", "IBM902" */
	CODEC_CP921,       /* "cp921", "IBM921" */
	CODEC_CP922,       /* "cp922", "IBM922", "Estonia-ISO-8" */
	CODEC_DIN_66303,   /* "DIN_66303", "DRV8" */
	CODEC_ISO5427,     /* "ISO5427" */
	CODEC_LY1,         /* "LY1" */
	CODEC_MACINTOSH_FONT_X, /* "Macintosh-Font-X" */
	CODEC_MSDOS1252,   /* "MSDOS-1252" */
	CODEC_NEC_APC,     /* "NEC-APC" */
#define CODEC_CP_MAX CODEC_NEC_APC

	/* 7h codepage codecs (IMPORTANT: keep these sorted lexicographically!) */
#define CODEC_CP7H_MIN CODEC_AMIGA_1251
	CODEC_AMIGA_1251,  /* "Amiga-1251", "Ami1251" */
	CODEC_CP10004,     /* "cp10004", "Windows-10004", "x-mac-arabic", "MacArabic" */
	CODEC_CP10006,     /* "cp10006", "Windows-10006", "x-mac-greek" */
	CODEC_CP10007,     /* "cp10007", "Windows-10007", "cp1283", "IBM1283" */
	CODEC_CP10017,     /* "cp10017", "Windows-10017", "x-mac-ukrainian" */
	CODEC_CP1036,      /* "cp1036", "IBM1036", "T.61", "cp20261", "Windows-20261" */
	CODEC_CP1100,      /* "cp1100", "DEC-MCS", "IBM1100", "WE8DEC", "csDECMCS", "dec" */
	CODEC_CP1116,      /* "cp1116", "IBM1116" */
	CODEC_CP1117,      /* "cp1117", "IBM1117" */
	CODEC_CP1124,      /* "cp1124", "IBM1124" */
	CODEC_CP1125,      /* "cp1125", "RST-2018-91", "CP866U", "CP866NAV", "RUSCII" */
	CODEC_CP1129,      /* "cp1129", "IBM1129" */
	CODEC_CP1131,      /* "cp1131", "IBM1131" */
	CODEC_CP1133,      /* "cp1133", "IBM1133" */
	CODEC_CP1161,      /* "cp1161", "IBM1161" */
	CODEC_CP1162,      /* "cp1162", "IBM1162", "windows-874", "MS874", "x-windows-874" */
	CODEC_CP1163,      /* "cp1163", "IBM1163" */
	CODEC_CP1250,      /* "cp1250", "Windows-1250" */
	CODEC_CP1251,      /* "cp1251", "Windows-1251" */
	CODEC_CP1252,      /* "cp1252", "Windows-1252" */
	CODEC_CP1253,      /* "cp1253", "Windows-1253" */
	CODEC_CP1254,      /* "cp1254", "Windows-1254" */
	CODEC_CP1255,      /* "cp1255", "Windows-1255" */
	CODEC_CP1256,      /* "cp1256", "Windows-1256" */
	CODEC_CP1257,      /* "cp1257", "Windows-1257", "LST-1590-3" */
	CODEC_CP1258,      /* "cp1258", "Windows-1258" */
	CODEC_CP1270,      /* "cp1270", "Windows-1270" */
	CODEC_CP1275,      /* "cp1275", "IBM1275", "cp10000", "Windows-10000", "x-mac-roman", "macintosh", "mac", "MacRoman" */
	CODEC_CP1281,      /* "cp1281", "IBM1281", "cp10081", "Windows-10081", "x-mac-turkish" */
	CODEC_CP1282,      /* "cp1282", "IBM1282", "cp10029", "Windows-10029", "x-mac-ce" */
	CODEC_CP1284,      /* "cp1284", "IBM1284", "cp10082", "Windows-10082", "x-mac-croatian" */
	CODEC_CP1285,      /* "cp1285", "IBM1285", "cp10010", "Windows-10010", "x-mac-romanian" */
	CODEC_CP1286,      /* "cp1286", "IBM1286", "cp10079", "Windows-10079", "x-mac-icelandic" */
	CODEC_CP1287,      /* "cp1287", "DEC-Greek-(8-bit)", "DEC-Greek-8-bit", "DEC-Greek-8", "DEC-Greek", "EL8DEC" */
	CODEC_CP1288,      /* "cp1288", "DEC-Turkish-(8-bit)", "DEC-Turkish-8-bit", "DEC-Turkish-8", "DEC-Turkish", "TR8DEC" */
	CODEC_CP20269,     /* "cp20269", "ISO6937-2-25", "ISO6937-2-add", "T.51", "ISO6937" */
	CODEC_CP3012,      /* "cp3012", "RusLat" */
	CODEC_CP437,       /* "IBM437", "cp437", "437", "csPC8CodePage437", "OEMUS", "OSF100201B5" */
	CODEC_CP667,       /* "MAZOVIA", "cp667", "cp790", "cp991", "MAZ" */
	CODEC_CP668,       /* "cp668" */
	CODEC_CP708,       /* "cp708", "IBM708" */
	CODEC_CP720,       /* "cp720", "IBM720", "OEM720" */
	CODEC_CP737,       /* "cp737", "IBM737", "OEM737" */
	CODEC_CP770,       /* "cp770" */
	CODEC_CP771,       /* "cp771", "KBL" */
	CODEC_CP772,       /* "cp772", "LST-1284", "LST-1284:1993", "cp1119" */
	CODEC_CP773,       /* "cp773" */
	CODEC_CP774,       /* "cp774", "cp1118", "IBM1118", "LST-1283" */
	CODEC_CP775,       /* "cp775", "IBM775", "OEM775" */
	CODEC_CP806,       /* "cp806", "IBM806" */
	CODEC_CP808,       /* "cp808" */
	CODEC_CP848,       /* "cp848" */
	CODEC_CP849,       /* "cp849" */
	CODEC_CP850,       /* "cp850", "IBM850", "850", "csPC850Multilingual", "OEM850" */
	CODEC_CP851,       /* "cp851", "IBM851", "851" */
	CODEC_CP852,       /* "cp852", "IBM852", "852", "csPCp852" */
	CODEC_CP853,       /* "cp853", "IBM853" */
	CODEC_CP855,       /* "cp855", "IBM855", "855", "OEM855" */
	CODEC_CP856,       /* "cp856", "IBM856" */
	CODEC_CP857,       /* "cp857", "IBM857", "857", "OEM857" */
	CODEC_CP858,       /* "cp858", "IBM858", "OEM858", "PC-Multilingual-850+euro" */
	CODEC_CP859,       /* "cp859", "IBM859" */
	CODEC_CP860,       /* "cp860", "IBM860", "860", "OEM860" */
	CODEC_CP861,       /* "cp861", "IBM861", "861", "OEM861", "cp-is" */
	CODEC_CP862,       /* "cp862", "IBM862", "862", "OEM862", "csPC862LatinHebrew" */
	CODEC_CP863,       /* "cp863", "IBM863", "863", "OEM863" */
	CODEC_CP865,       /* "cp865", "IBM865", "865", "OEM865" */
	CODEC_CP866,       /* "cp866", "866", "IBM866" */
	CODEC_CP867,       /* "cp867" */
	CODEC_CP868,       /* "cp868", "IBM868", "cp-ar" */
	CODEC_CP869,       /* "cp869", "IBM869", "OEM869", "869", "cp-gr" */
	CODEC_CP872,       /* "cp872" */
	CODEC_CP874,       /* "cp874", "cp9066", "IBM874", "IBM9066", "x-IBM874" */
	CODEC_CP912,       /* "cp912", "IBM912" */
	CODEC_CP915,       /* "cp915", "IBM915" */
	CODEC_EXTENDED_LATIN_8, /* "Extended-Latin-8" */
	CODEC_ISO5428,     /* "iso5428" */
	CODEC_ISO6438,     /* "iso6438" */
	CODEC_ISO_8859_10, /* "ISO8859-10", "iso-ir-157", "csISOLatin6", "latin6", "l6", "IBM919", "cp919", "cp28600", "Windows-28600" */
	CODEC_ISO_8859_11, /* "ISO8859-11", "cp28601", "Windows-28601" */
	CODEC_ISO_8859_13, /* "ISO8859-13", "iso-ir-179", "csISOLatin7", "latin7", "l7", "cp28603", "Windows-28603" */
	CODEC_ISO_8859_14, /* "ISO8859-14", "iso-ir-199", "iso-celtic", "latin8", "l8", "cp28604", "Windows-28604" */
	CODEC_ISO_8859_15, /* "ISO8859-15", "latin9", "latin0", "IBM923", "cp923", "cp28605", "Windows-28605" */
	CODEC_ISO_8859_16, /* "ISO8859-16", "iso-ir-226", "latin10", "l10", "SR-14111", "cp28606", "Windows-28606" */
	CODEC_ISO_8859_2,  /* "ISO8859-2", "iso-ir-101", "csISOLatin2", "latin2", "l2", "IBM1111", "cp1111", "cp28592", "Windows-28592" */
	CODEC_ISO_8859_3,  /* "ISO8859-3", "iso-ir-109", "csISOLatin3", "latin3", "l3", "IBM913", "cp913", "cp28593", "Windows-28593" */
	CODEC_ISO_8859_4,  /* "ISO8859-4", "iso-ir-110", "csISOLatin4", "latin4", "l4", "IBM914", "cp914", "cp28594", "Windows-28594" */
	CODEC_ISO_8859_5,  /* "ISO8859-5", "iso-ir-144", "csISOLatinCyrillic", "cyrillic", "cp28595", "Windows-28595" */
	CODEC_ISO_8859_6,  /* "ISO8859-6", "iso-ir-127", "csISOLatinArabic", "ECMA-114", "ASMO-708", "arabic", "IBM1089", "cp1089", "cp28596", "Windows-28596", "cp38596", "Windows-38596", "ISO8859-6-I" */
	CODEC_ISO_8859_7,  /* "ISO8859-7", "iso-ir-126", "csISOLatinGreek", "ELOT_928", "ECMA-118", "greek", "greek8", "IBM813", "cp813", "cp28597", "Windows-28597" */
	CODEC_ISO_8859_8,  /* "ISO8859-8", "iso-ir-138", "csISOLatinHebrew", "hebrew", "IBM916", "cp916", "cp28598", "Windows-28598", "cp38598", "Windows-38598", "ISO8859-8-I" */
	CODEC_ISO_8859_9,  /* "ISO8859-9", "iso-ir-148", "csISOLatin5", "latin5", "l5", "IBM920", "cp920", "cp28599", "Windows-28599" */
	CODEC_ISO_IR_153,  /* "iso-ir-153", "st-sev-358-88" */
	CODEC_ISO_IR_182,  /* "iso-ir-182" */
	CODEC_ISO_IR_197,  /* "iso-ir-197" */
	CODEC_ISO_IR_200,  /* "iso-ir-200" */
	CODEC_ISO_IR_201,  /* "iso-ir-201" */
	CODEC_ISO_IR_206,  /* "iso-ir-206" */
	CODEC_KEYBCS2,     /* "NEC-867", "DOS-895", "KEYBCS2", "KAMENICKY" */
	CODEC_KOI8,        /* "KOI8" */
	CODEC_KOI8_B,      /* "KOI8-B" */
	CODEC_KOI8_E,      /* "KOI8-E", "iso-ir-111" */
	CODEC_KOI8_F,      /* "KOI8-F", "KOI8-Unified" */
	CODEC_KOI8_N1,     /* "KOI8-N1" */
	CODEC_KOI8_N2,     /* "KOI8-N2" */
	CODEC_KOI8_R,      /* "KOI8-R", "cp20866", "cp878", "IBM878" */
	CODEC_KOI8_RU,     /* "KOI8-RU", "cp1167" */
	CODEC_KOI8_T,      /* "KOI8-T" */
	CODEC_KOI8_U,      /* "KOI8-U", "cp21866", "cp1168", "IBM1168" */
	CODEC_KZ_1048,     /* "KZ-1048", "STRK1048-2002" */
	CODEC_LICS,        /* "LICS" */
	CODEC_MACINTOSH_LATIN, /* "MACINTOSH-LATIN" */
	CODEC_MAC_OS_THAI, /* "Mac-OS-Thai" */
	CODEC_MIK,         /* "MIK", "BULGARIA-PC" */
	CODEC_PALMOS,      /* "palmos" */
	CODEC_X_MAC_ARMENIAN,         /* "x-mac-armenian" */
	CODEC_X_MAC_BARENTS_CYRILLIC, /* "x-mac-barents-cyrillic" */
	CODEC_X_MAC_CELTIC,           /* "x-mac-celtic" */
	CODEC_X_MAC_CYRILLIC,         /* "x-mac-cyrillic" */
	CODEC_X_MAC_DEVANAGARI,       /* "x-mac-devanagari" */
	CODEC_X_MAC_FARSI,            /* "x-mac-farsi", "MacFarsi" */
	CODEC_X_MAC_GAELIC,           /* "x-mac-gaelic" */
	CODEC_X_MAC_GEORGIAN,         /* "x-mac-georgian" */
	CODEC_X_MAC_GUJARATI,         /* "x-mac-gujarati" */
	CODEC_X_MAC_GURMUKHI,         /* "x-mac-gurmukhi" */
	CODEC_X_MAC_INUIT,            /* "x-mac-inuit" */
	CODEC_X_MAC_MALTESE,          /* "x-mac-maltese", "x-mac-esperanto" */
	CODEC_X_MAC_OGHAM,            /* "x-mac-ogham" */
	CODEC_X_MAC_SAMI,             /* "x-mac-sami" */
	CODEC_X_MAC_TURKIC_CYRILLIC,  /* "x-mac-turkic-cyrillic" */

/*
MacFarsi encoding*/

#define CODEC_CP7H_MAX CODEC_X_MAC_SAMI

	/* 7l codepage codecs (IMPORTANT: keep these sorted lexicographically!) */
#define CODEC_CP7L_MIN CODEC_BCDIC
	CODEC_BCDIC,           /* "BCDIC" */
	CODEC_BURROUGHS_B5500, /* "Burroughs-B5500" */
	CODEC_CP1010,          /* "cp1010", "IBM1010" */
	CODEC_CP1012,          /* "cp1012", "IBM1012", "I7DEC" */
	CODEC_CP1090,          /* "cp1090", "IBM1090", "DEC-Special-Graphics" */
	CODEC_CP353,           /* "cp353" */
	CODEC_CP355,           /* "cp355", "PTTC/BCD" */
	CODEC_CP357,           /* "cp357", "PTTC/BCD-H" */
	CODEC_CP358,           /* "cp358", "PTTC/BCD-C" */
	CODEC_CP359,           /* "cp359", "PTTC/BCD-M", "cp360", "PTTC/BCD-D" */
	CODEC_CP895,           /* "cp895", "IBM895" */
	CODEC_CP896,           /* "cp896", "IBM896", "cp4992" */
	CODEC_CP903,           /* "cp903", "IBM903" */
	CODEC_CP904,           /* "cp904", "IBM904", "904" */
	CODEC_GBCD,            /* "GBCD" */
	CODEC_IBM1401,         /* "IBM1401" */
	CODEC_IBM704,          /* "IBM704" */
	CODEC_IBM7090,         /* "IBM7090", "IBM7094" */
	CODEC_ISO2033,         /* "ISO2033", "JIS-C-6229-OCR-A" */
	CODEC_ISO5426,         /* "ISO5426" */
	CODEC_ISO5426_2,       /* "ISO5426-2" */
	CODEC_ISO_IR_68,       /* "ISO-IR-68" */
	CODEC_KOI7,            /* "KOI7-N0" */
	CODEC_KOI7_N1,         /* "KOI7-N1", "koi0" */
	CODEC_KOI7_N2,         /* "KOI7-N2", "SHORT-KOI" */
#define CODEC_CP7L_MAX CODEC_KOI7_N2

	/* iso646 code pages (IMPORTANT: keep these sorted lexicographically!) */
#define CODEC_ISO646_MIN CODEC_ISO646_CA
	CODEC_ISO646_CA,             /* "ISO646-CA", "iso-ir-121", "CSA_Z243.4-1985-1", "CSA7-1", "CA", "csISO121Canadian1", "CSA_Z243.419851", "cp1020" */
	CODEC_ISO646_CA2,            /* "ISO646-CA2", "iso-ir-122", "CSA_Z243.4-1985-2", "CSA7-2", "csISO122Canadian2", "CSA_Z243.419852" */
	CODEC_ISO646_CN,             /* "ISO646-CN", "iso-ir-57", "CN", "csISO58GB1988", "GB_1988-80", "GB_198880" */
	CODEC_ISO646_CU,             /* "ISO646-CU", "CUBA", "NC_NC00-10", "NC_NC00-10:81", "iso-ir-151", "csISO151Cuba", "NC_NC0010" */
	CODEC_ISO646_DANO_NATS,      /* "ISO-IR-9-1", "cp1016", "IBM1016" */
	CODEC_ISO646_DE,             /* "ISO646-DE", "iso-ir-21", "DIN_66003", "IBM1011", "MS-10206", "csISO21German", "GERMAN", "DE", "D7DEC", "cp1011", "cp20106", "Windows-20106" */
	CODEC_ISO646_DK,             /* "ISO646-DK", "DS2089", "DS_2089", "DK", "csISO646Danish", "cp1017", "IBM1017" */
	CODEC_ISO646_DK_NO_ALT_NRCS, /* "cp1107", "IBM1107" */
	CODEC_ISO646_DK_NO_NRCS,     /* "cp1105", "IBM1105" */
	CODEC_ISO646_ES,             /* "ISO646-ES", "iso-ir-17", "ES", "csISO17Spanish", "cp1023", "E7DEC" */
	CODEC_ISO646_ES2,            /* "ISO646-ES2", "iso-ir-85", "ES2", "csISO85Spanish2", "cp1014", "IBM1014" */
	CODEC_ISO646_FI_NRCS,        /* "cp1103", "IBM1103" */
	CODEC_ISO646_FR,             /* "ISO646-FR", "iso-ir-69", "NF_Z_62-010", "NF_Z_62-010_1983", "NF_Z_62-010_(1983)", "FR", "csISO69French", "NF_Z_62010" */
	CODEC_ISO646_FR1,            /* "ISO646-FR1", "iso-ir-25", "NF_Z_62-010_1973", "NF_Z_62-010_(1973)", "csISO25French", "NF_Z_62010_1973", "cp1104", "F7DEC" */
	CODEC_ISO646_GB,             /* "ISO646-GB", "iso-ir-4", "BS_4730", "GB", "UK", "csISO4Unitedkingdom", "cp1013", "IBM1013" */
	CODEC_ISO646_GB_NRCS,        /* "cp1101", "IBM1101" */
	CODEC_ISO646_HU,             /* "ISO646-HU", "iso-ir-86", "MSZ_7795.3", "HU", "csISO86Hungarian" */
	CODEC_ISO646_IE,             /* "ISO646-IE", "iso-ir-207" */
	CODEC_ISO646_INIS_SUBSET,    /* "ISO-IR-49" */
	CODEC_ISO646_INV,            /* "ISO-IR-170" */
	CODEC_ISO646_IRV_1973,       /* "ISO-IR-2" */
	CODEC_ISO646_IRV_1983,       /* "cp1009", "IBM1009", "cp20105", "Windows-20105" */
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
	CODEC_ISO646_PT2,            /* "ISO646-PT2", "iso-ir-84", "PT2", "csISO84Portuguese2", "cp1015", "IBM1015" */
	CODEC_ISO646_SE,             /* "ISO646-SE", "iso-ir-10", "SEN_850200_B", "FI", "ISO646-FI", "SE", "csISO10Swedish", "SS636127", "cp1018", "IBM1018" */
	CODEC_ISO646_SE2,            /* "ISO646-SE2", "iso-ir-11", "SEN_850200_C", "SE2", "csISO11Swedishfornames" */
	CODEC_ISO646_SEFI_NATS,      /* "ISO-IR-8" */
	CODEC_ISO646_SE_NRCS,        /* "cp1106", "IBM1106" */
	CODEC_ISO646_SWI_NRCS,       /* "cp1021", "IBM1021", "CH7DEC" */
	CODEC_ISO646_T_61,           /* "ISO-IR-102" */
	CODEC_ISO646_VIEWDATA,       /* "ISO-IR-47" */
	CODEC_ISO646_YU,             /* "ISO646-YU", "JUS_I.B1.002", "JS", "YU", "csISO141Jusib1002" */
#define CODEC_ISO646_MAX CODEC_ISO646_YU

	/* Aliases */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	CODEC_UTF16 = CODEC_UTF16LE, /* "UTF16", "UTF-16", "ISO10646/UCS2", "UCS2", "UCS-2", "OSF00010100", "OSF00010101", "OSF00010102", "cp13488", "Windows-13488", "cp1200", "cp1201" */
	CODEC_UTF32 = CODEC_UTF32LE, /* "UTF32", "UTF-32", "ISO10646/UCS4", "UCS4", "UCS-4", "CSUCS4", "ISO10646", "10646-1:1993", "10646-1:1993/UCS4", "OSF00010104", "OSF00010105", "OSF00010106", "cp12000" */
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

/* Return the ID of the codec associated with  `name'
 * Casing is ignored and codec aliases are respected. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) unsigned int
NOTHROW_NCX(FCALL libiconv_codecbyname)(char const *__restrict name);

/* Return the nth (0-based) lexicographically sorted name for the codec `id'
 * When `id'  is  invalid or  doesn't  have  an `nth'  name,  return  `NULL' */
INTDEF ATTR_CONST WUNUSED char const *
NOTHROW_NCX(FCALL libiconv_getcodecname)(unsigned int id, unsigned int nth);


/* Same as `libiconv_codecbyname()', but also parse possible flag-relation options. */
INTDEF WUNUSED NONNULL((1)) unsigned int
NOTHROW_NCX(FCALL libiconv_codec_and_flags_byname)(char const *__restrict name,
                                                   /*[in|out]*/ uintptr_half_t *__restrict pflags);

DECL_END

#endif /* !GUARD_LIBICONV_CODECS_H */
