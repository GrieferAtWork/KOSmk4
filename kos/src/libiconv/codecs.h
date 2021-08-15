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
 *  - https://en.wikipedia.org/wiki/Shift_JIS                          "shift-jis", "sjis", "ms_kanji", "csShiftJis"
 *  - https://en.wikipedia.org/wiki/Code_page_932_(Microsoft_Windows)  "windows-31j", "cp932", "ms932", "sjis-open", "sjis-win", "csWindows31J"
 *  - https://en.wikipedia.org/wiki/KOI-7                              "KOI7", "KOI7-switched", "csKOI7switched"
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

/*[[[deemon (printCodecEnums from .iconvdata.iconvdata)();]]]*/
	/* Custom codecs */
	CODEC_ASCII,      /* "ansi-x3.4-1968", "iso-ir-6", "ansi-x3.4-1986", "iso646.irv:1991", "ascii", "iso646-us", "us-ascii", "us", "ibm367", "cp367", "ansi-x3.4", "csascii", "osf10020", "cp20127", "windows-20127" */
	CODEC_ISO_8859_1, /* "iso8859-1:1987", "iso-ir-100", "iso8859-1", "latin1", "l1", "ibm819", "cp819", "iso88591", "csisolatin1", "cp28591", "windows-28591", "we8iso8859p1", "cp38591", "windows-38591", "iso8859-1-i", "8859-1", "osf10001" */
	CODEC_UTF16BE,    /* "utf16be", "utf-16be", "ucs-2be", "unicodebig" */
	CODEC_UTF16LE,    /* "utf16le", "utf-16le", "ucs-2le", "unicodelittle" */
	CODEC_UTF32BE,    /* "utf32be", "utf-32be", "ucs-4be", "cp12001", "windows-12001" */
	CODEC_UTF32LE,    /* "utf32le", "utf-32le", "ucs-4le" */
	CODEC_UTF8,       /* "utf8", "utf-8", "iso10646/utf8", "iso10646/utf-8", "iso-ir-193", "osf5010001", "cp65001", "windows-65001" */

	/* 8-bit codepage codecs */
#define CODEC_CP_MIN CODEC_CP1004
	CODEC_CP1004,           /* "cp1004", "windows-extended" */
	CODEC_CP1006,           /* "cp1006", "ibm1006", "iso-8-bit-urdu" */
	CODEC_CP1008,           /* "cp1008", "ibm1008", "cp5104", "ibm5104" */
	CODEC_CP1038,           /* "cp1038", "ibm1038", "x-mac-symbol" */
	CODEC_CP1040,           /* "cp1040" */
	CODEC_CP1041,           /* "cp1041" */
	CODEC_CP1042,           /* "cp1042" */
	CODEC_CP1043,           /* "cp1043" */
	CODEC_CP1046,           /* "cp1046" */
	CODEC_CP1050,           /* "cp1050", "hp-roman-8", "cp1051" */
	CODEC_CP1057,           /* "cp1057", "hp-pc-8" */
	CODEC_CP1088,           /* "cp1088" */
	CODEC_CP1098,           /* "cp1098", "ibm1098" */
	CODEC_CP1114,           /* "cp1114" */
	CODEC_CP1115,           /* "cp1115" */
	CODEC_CP1127,           /* "cp1127" */
	CODEC_CP1276,           /* "cp1276", "postscript-standard-encoding", "standardencoding", "postscript" */
	CODEC_CP17248,          /* "cp17248" */
	CODEC_CP437,            /* "ibm437", "cp437", "437", "cspc8codepage437", "oemus", "osf100201b5" */
	CODEC_CP864,            /* "ibm864", "cp864" */
	CODEC_CP897,            /* "cp897" */
	CODEC_CP901,            /* "cp901", "ibm901" */
	CODEC_CP902,            /* "cp902", "ibm902" */
	CODEC_CP921,            /* "cp921", "ibm921" */
	CODEC_CP922,            /* "cp922", "ibm922", "estonia-iso-8" */
	CODEC_DIN_66303,        /* "din-66303", "drv8" */
	CODEC_ISO5427,          /* "iso5427", "iso-ir-37", "koi7-n1", "koi0", "csiso5427cyrillic" */
	CODEC_ISO_IR_139,       /* "csn-369103", "iso-ir-139" */
	CODEC_ISO_IR_152,       /* "iso6937-2-25", "iso-ir-152" */
	CODEC_LY1,              /* "ly1" */
	CODEC_MACINTOSH_FONT_X, /* "macintosh-font-x" */
	CODEC_MSDOS1252,        /* "msdos-1252" */
	CODEC_X0201,            /* "jis-x201", "x201" */
#define CODEC_CP_MAX CODEC_X0201

	/* 7l codepage codecs */
#define CODEC_CP7L_MIN CODEC_BCDIC
	CODEC_BCDIC,           /* "bcdic" */
	CODEC_BURROUGHS_B5500, /* "burroughs-b5500" */
	CODEC_CP1090,          /* "cp1090", "ibm1090", "dec-special-graphics" */
	CODEC_CP353,           /* "cp353" */
	CODEC_CP355,           /* "cp355", "pttc/bcd" */
	CODEC_CP357,           /* "cp357", "pttc/bcd-h" */
	CODEC_CP358,           /* "cp358", "pttc/bcd-c" */
	CODEC_CP359,           /* "cp359", "pttc/bcd-m", "cp360", "pttc/bcd-d" */
	CODEC_CP896,           /* "cp896", "ibm896", "cp4992" */
	CODEC_CP903,           /* "cp903", "ibm903" */
	CODEC_CP904,           /* "ibm904", "cp904", "904" */
	CODEC_GBCD,            /* "gbcd" */
	CODEC_IBM1401,         /* "ibm1401" */
	CODEC_IBM704,          /* "ibm704" */
	CODEC_IBM7090,         /* "ibm7090", "ibm7094" */
	CODEC_ISO2033,         /* "iso2033", "jis-c-6229-ocr-a" */
	CODEC_ISO5426,         /* "iso5426" */
	CODEC_ISO5426_2,       /* "iso5426-2" */
	CODEC_ISO_IR_13,       /* "jis-c6220-1969-jp", "jis-c6220-1969", "iso-ir-13", "katakana", "x201-7" */
	CODEC_ISO_IR_146,      /* "jus-i.b1.3-serb", "iso-ir-146", "serbian" */
	CODEC_ISO_IR_147,      /* "jus-i.b1.3-mac", "macedonian", "iso-ir-147" */
	CODEC_ISO_IR_150,      /* "greek-ccitt", "iso-ir-150" */
	CODEC_ISO_IR_18,       /* "greek7-old", "iso-ir-18" */
	CODEC_ISO_IR_19,       /* "latin-greek", "iso-ir-19", "latingreek", "csiso19latingreek" */
	CODEC_ISO_IR_50,       /* "inis-8", "iso-ir-50" */
	CODEC_ISO_IR_51,       /* "inis-cyrillic", "iso-ir-51" */
	CODEC_ISO_IR_54,       /* "iso5427:1981", "iso-ir-54" */
	CODEC_ISO_IR_55,       /* "iso5428:1980", "iso-ir-55" */
	CODEC_ISO_IR_68,       /* "iso-ir-68" */
	CODEC_ISO_IR_88,       /* "greek7", "iso-ir-88" */
	CODEC_ISO_IR_89,       /* "asmo-449", "iso9036", "arabic7", "iso-ir-89" */
	CODEC_ISO_IR_8_2,      /* "nats-sefi-add", "iso-ir-8-2" */
	CODEC_ISO_IR_91,       /* "jis-c6229-1984-a", "iso-ir-91", "jp-ocr-a" */
	CODEC_ISO_IR_93,       /* "jis-c6229-1984-b-add", "iso-ir-93", "jp-ocr-b-add" */
	CODEC_ISO_IR_94,       /* "jis-c6229-1984-hand", "iso-ir-94", "jp-ocr-hand" */
	CODEC_ISO_IR_96,       /* "jis-c6229-1984-kana", "iso-ir-96" */
	CODEC_ISO_IR_98,       /* "iso2033-1983", "iso-ir-98", "e13b" */
	CODEC_ISO_IR_9_2,      /* "nats-dano-add", "iso-ir-9-2" */
	CODEC_KOI7_N2,         /* "koi7-n2", "short-koi" */
#define CODEC_CP7L_MAX CODEC_KOI7_N2

	/* 7h codepage codecs */
#define CODEC_CP7H_MIN CODEC_AMIGA_1251
	CODEC_AMIGA_1251,             /* "amiga-1251", "ami1251" */
	CODEC_CP10004,                /* "cp10004", "windows-10004", "x-mac-arabic", "macarabic" */
	CODEC_CP10006,                /* "cp10006", "windows-10006", "x-mac-greek" */
	CODEC_CP10007,                /* "cp10007", "windows-10007", "cp1283", "ibm1283" */
	CODEC_CP10017,                /* "cp10017", "windows-10017", "x-mac-ukrainian" */
	CODEC_CP1036,                 /* "cp1036", "ibm1036", "t.61", "t.618bit", "t.61-8bit", "cp20261", "windows-20261", "iso-ir-103", "csiso103t618bit" */
	CODEC_CP1100,                 /* "dec-mcs", "dec", "cp1100", "ibm1100", "we8dec", "csdecmcs" */
	CODEC_CP1116,                 /* "cp1116", "ibm1116" */
	CODEC_CP1117,                 /* "cp1117", "ibm1117" */
	CODEC_CP1124,                 /* "cp1124", "ibm1124" */
	CODEC_CP1125,                 /* "cp1125", "rst-2018-91", "cp866u", "cp866nav", "ruscii" */
	CODEC_CP1129,                 /* "cp1129", "ibm1129" */
	CODEC_CP1131,                 /* "cp1131", "ibm1131" */
	CODEC_CP1133,                 /* "cp1133", "ibm1133" */
	CODEC_CP1161,                 /* "cp1161", "ibm1161" */
	CODEC_CP1162,                 /* "cp1162", "ibm1162", "windows-874", "ms874", "x-windows-874" */
	CODEC_CP1163,                 /* "cp1163", "ibm1163" */
	CODEC_CP1250,                 /* "cp1250", "windows-1250" */
	CODEC_CP1251,                 /* "cp1251", "windows-1251" */
	CODEC_CP1252,                 /* "cp1252", "windows-1252" */
	CODEC_CP1253,                 /* "cp1253", "windows-1253" */
	CODEC_CP1254,                 /* "cp1254", "windows-1254" */
	CODEC_CP1255,                 /* "cp1255", "windows-1255" */
	CODEC_CP1256,                 /* "cp1256", "windows-1256" */
	CODEC_CP1257,                 /* "cp1257", "windows-1257", "lst-1590-3" */
	CODEC_CP1258,                 /* "cp1258", "windows-1258" */
	CODEC_CP1270,                 /* "cp1270", "windows-1270" */
	CODEC_CP1275,                 /* "macintosh", "mac", "cp1275", "ibm1275", "cp10000", "windows-10000", "x-mac-roman", "macroman" */
	CODEC_CP1281,                 /* "cp1281", "ibm1281", "cp10081", "windows-10081", "x-mac-turkish" */
	CODEC_CP1282,                 /* "cp1282", "ibm1282", "cp10029", "windows-10029", "x-mac-ce" */
	CODEC_CP1284,                 /* "cp1284", "ibm1284", "cp10082", "windows-10082", "x-mac-croatian" */
	CODEC_CP1285,                 /* "cp1285", "ibm1285", "cp10010", "windows-10010", "x-mac-romanian" */
	CODEC_CP1286,                 /* "cp1286", "ibm1286", "cp10079", "windows-10079", "x-mac-icelandic" */
	CODEC_CP1287,                 /* "cp1287", "dec-greek-(8-bit)", "dec-greek-8-bit", "dec-greek-8", "dec-greek", "el8dec" */
	CODEC_CP1288,                 /* "cp1288", "dec-turkish-(8-bit)", "dec-turkish-8-bit", "dec-turkish-8", "dec-turkish", "tr8dec" */
	CODEC_CP20269,                /* "cp20269", "t.51", "iso6937", "iso-ir-156", "iso6937:1992" */
	CODEC_CP3012,                 /* "cp3012", "ruslat" */
	CODEC_CP667,                  /* "mazovia", "cp667", "cp790", "cp991", "maz" */
	CODEC_CP668,                  /* "cp668" */
	CODEC_CP708,                  /* "cp708", "ibm708" */
	CODEC_CP720,                  /* "cp720", "ibm720", "oem720" */
	CODEC_CP737,                  /* "cp737", "ibm737", "oem737" */
	CODEC_CP770,                  /* "cp770" */
	CODEC_CP771,                  /* "cp771", "kbl" */
	CODEC_CP772,                  /* "cp772", "lst-1284", "lst-1284:1993", "cp1119" */
	CODEC_CP773,                  /* "cp773" */
	CODEC_CP774,                  /* "cp774", "cp1118", "ibm1118", "lst-1283" */
	CODEC_CP775,                  /* "cp775", "ibm775", "oem775" */
	CODEC_CP806,                  /* "cp806", "ibm806" */
	CODEC_CP808,                  /* "cp808" */
	CODEC_CP848,                  /* "cp848" */
	CODEC_CP849,                  /* "cp849" */
	CODEC_CP850,                  /* "ibm850", "cp850", "850", "cspc850multilingual", "oem850" */
	CODEC_CP851,                  /* "ibm851", "cp851", "851" */
	CODEC_CP852,                  /* "ibm852", "cp852", "852", "cspcp852" */
	CODEC_CP853,                  /* "cp853", "ibm853" */
	CODEC_CP855,                  /* "ibm855", "cp855", "855", "oem855" */
	CODEC_CP856,                  /* "cp856", "ibm856" */
	CODEC_CP857,                  /* "ibm857", "cp857", "857", "oem857" */
	CODEC_CP858,                  /* "cp858", "ibm858", "oem858", "pc-multilingual-850+euro" */
	CODEC_CP859,                  /* "cp859", "ibm859" */
	CODEC_CP860,                  /* "ibm860", "cp860", "860", "oem860" */
	CODEC_CP861,                  /* "ibm861", "cp861", "861", "oem861", "cp-is" */
	CODEC_CP862,                  /* "ibm862", "cp862", "862", "oem862", "cspc862latinhebrew" */
	CODEC_CP863,                  /* "ibm863", "cp863", "863", "oem863" */
	CODEC_CP865,                  /* "ibm865", "cp865", "865", "oem865" */
	CODEC_CP866,                  /* "cp866", "866", "ibm866" */
	CODEC_CP867,                  /* "cp867" */
	CODEC_CP868,                  /* "ibm868", "cp868", "cp-ar" */
	CODEC_CP869,                  /* "ibm869", "cp869", "869", "cp-gr", "oem869" */
	CODEC_CP872,                  /* "cp872" */
	CODEC_CP874,                  /* "cp874", "cp9066", "ibm874", "ibm9066", "x-ibm874" */
	CODEC_EXTENDED_LATIN_8,       /* "extended-latin-8" */
	CODEC_HP_ROMAN8,              /* "hp-roman8", "roman8", "r8" */
	CODEC_ISO5428,                /* "iso5428" */
	CODEC_ISO6438,                /* "iso6438" */
	CODEC_ISO6937_2,              /* "iso6937-2", "iso69372", "iso6937-2:1983", "iso-ir-90", "csiso90" */
	CODEC_ISO_8859_10,            /* "latin6", "iso-ir-157", "l6", "iso8859-10", "iso8859-10:1992", "iso885910", "csisolatin6", "ibm919", "cp919", "cp28600", "windows-28600", "osf1000a" */
	CODEC_ISO_8859_11,            /* "iso8859-11", "iso885911", "cp28601", "windows-28601" */
	CODEC_ISO_8859_13,            /* "iso8859-13", "iso885913", "iso-ir-179", "csisolatin7", "latin7", "l7", "baltic", "cp28603", "windows-28603" */
	CODEC_ISO_8859_14,            /* "iso8859-14", "iso8859-14:1998", "iso885914", "iso-ir-199", "iso-celtic", "latin8", "l8", "cp28604", "windows-28604" */
	CODEC_ISO_8859_15,            /* "iso8859-15", "iso8859-15:1998", "iso885915", "iso-ir-203", "latin9", "latin0", "ibm923", "cp923", "cp28605", "windows-28605" */
	CODEC_ISO_8859_16,            /* "iso8859-16", "iso8859-16:2001", "iso885916", "iso-ir-226", "latin10", "l10", "sr-14111", "cp28606", "windows-28606" */
	CODEC_ISO_8859_2,             /* "iso8859-2:1987", "iso-ir-101", "iso8859-2", "latin2", "l2", "iso88592", "csisolatin2", "ibm1111", "cp1111", "cp28592", "windows-28592", "8859-2", "osf10002", "cp912", "ibm912" */
	CODEC_ISO_8859_3,             /* "iso8859-3:1988", "iso-ir-109", "iso8859-3", "latin3", "l3", "iso88593", "csisolatin3", "ibm913", "cp913", "cp28593", "windows-28593", "8859-3", "osf10003" */
	CODEC_ISO_8859_4,             /* "iso8859-4:1988", "iso-ir-110", "iso8859-4", "latin4", "l4", "iso88594", "csisolatin4", "ibm914", "cp914", "cp28594", "windows-28594", "8859-4", "osf10004" */
	CODEC_ISO_8859_5,             /* "iso8859-5:1988", "iso-ir-144", "iso8859-5", "cyrillic", "iso88595", "csisolatincyrillic", "cp28595", "windows-28595", "8859-5", "osf10005", "cp915", "ibm915" */
	CODEC_ISO_8859_6,             /* "iso8859-6:1987", "iso-ir-127", "iso8859-6", "ecma-114", "asmo-708", "arabic", "iso88596", "csisolatinarabic", "ibm1089", "cp1089", "cp28596", "windows-28596", "cp38596", "windows-38596", "iso8859-6-i", "8859-6", "osf10006" */
	CODEC_ISO_8859_7,             /* "iso8859-7:1987", "iso-ir-126", "iso8859-7", "elot-928", "ecma-118", "greek", "greek8", "iso8859-7:2003", "csisolatingreek", "ibm813", "cp813", "cp28597", "windows-28597", "iso88597", "8859-7", "osf10007" */
	CODEC_ISO_8859_8,             /* "iso8859-8:1988", "iso-ir-138", "iso8859-8", "hebrew", "iso88598", "csisolatinhebrew", "ibm916", "cp916", "cp28598", "windows-28598", "cp38598", "windows-38598", "iso8859-8-i", "8859-8", "osf10008" */
	CODEC_ISO_8859_9,             /* "iso8859-9:1989", "iso-ir-148", "iso8859-9", "latin5", "l5", "iso88599", "csisolatin5", "ibm920", "cp920", "cp28599", "windows-28599", "8859-9", "osf10009", "ts-5881", "ecma-128" */
	CODEC_ISO_IR_123,             /* "csa-z243.4-1985-gr", "iso-ir-123" */
	CODEC_ISO_IR_143,             /* "iec-p27-1", "iso-ir-143" */
	CODEC_ISO_IR_153,             /* "gost-19768-74", "st-sev-358-88", "iso-ir-153" */
	CODEC_ISO_IR_154,             /* "iso8859-supp", "iso-ir-154", "latin1-2-5" */
	CODEC_ISO_IR_155,             /* "iso10367-box", "iso-ir-155" */
	CODEC_ISO_IR_158,             /* "latin-lap", "lap", "iso-ir-158" */
	CODEC_ISO_IR_182,             /* "iso-ir-182" */
	CODEC_ISO_IR_197,             /* "iso-ir-197" */
	CODEC_ISO_IR_200,             /* "iso-ir-200" */
	CODEC_ISO_IR_201,             /* "iso-ir-201" */
	CODEC_ISO_IR_206,             /* "iso-ir-206" */
	CODEC_KEYBCS2,                /* "nec-867", "dos-895", "keybcs2", "kamenicky" */
	CODEC_KOI8,                   /* "koi8" */
	CODEC_KOI8_B,                 /* "koi8-b" */
	CODEC_KOI8_E,                 /* "ecma-cyrillic", "iso-ir-111", "ecma-113", "koi8-e" */
	CODEC_KOI8_F,                 /* "koi8-f", "koi8-unified" */
	CODEC_KOI8_N1,                /* "koi8-n1" */
	CODEC_KOI8_N2,                /* "koi8-n2" */
	CODEC_KOI8_R,                 /* "koi8-r", "cp20866", "cp878", "ibm878", "cskoi8r" */
	CODEC_KOI8_RU,                /* "koi8-ru", "cp1167" */
	CODEC_KOI8_T,                 /* "koi8-t" */
	CODEC_KOI8_U,                 /* "koi8-u", "cp21866", "cp1168", "ibm1168" */
	CODEC_KZ_1048,                /* "kz-1048", "strk1048-2002" */
	CODEC_LICS,                   /* "lics" */
	CODEC_MACINTOSH_LATIN,        /* "macintosh-latin" */
	CODEC_MAC_OS_THAI,            /* "mac-os-thai" */
	CODEC_MIK,                    /* "mik", "bulgaria-pc" */
	CODEC_PALMOS,                 /* "palmos" */
	CODEC_X_MAC_ARMENIAN,         /* "x-mac-armenian" */
	CODEC_X_MAC_BARENTS_CYRILLIC, /* "x-mac-barents-cyrillic" */
	CODEC_X_MAC_CELTIC,           /* "x-mac-celtic" */
	CODEC_X_MAC_CYRILLIC,         /* "x-mac-cyrillic" */
	CODEC_X_MAC_DEVANAGARI,       /* "x-mac-devanagari" */
	CODEC_X_MAC_FARSI,            /* "x-mac-farsi", "macfarsi" */
	CODEC_X_MAC_GAELIC,           /* "x-mac-gaelic" */
	CODEC_X_MAC_GEORGIAN,         /* "x-mac-georgian" */
	CODEC_X_MAC_GUJARATI,         /* "x-mac-gujarati" */
	CODEC_X_MAC_GURMUKHI,         /* "x-mac-gurmukhi" */
	CODEC_X_MAC_INUIT,            /* "x-mac-inuit" */
	CODEC_X_MAC_MALTESE,          /* "x-mac-maltese", "x-mac-esperanto" */
	CODEC_X_MAC_OGHAM,            /* "x-mac-ogham" */
	CODEC_X_MAC_SAMI,             /* "x-mac-sami" */
	CODEC_X_MAC_TURKIC_CYRILLIC,  /* "x-mac-turkic-cyrillic" */
#define CODEC_CP7H_MAX CODEC_X_MAC_TURKIC_CYRILLIC

	/* iso646 codepage codecs */
#define CODEC_ISO646_MIN CODEC_ISO646_BASIC
	CODEC_ISO646_BASIC,          /* "iso646.basic:1983", "ref" */
	CODEC_ISO646_CA,             /* "csa-z243.4-1985-1", "iso-ir-121", "iso646-ca", "csa7-1", "ca", "csiso121canadian1", "csa-z243.419851", "cp1020" */
	CODEC_ISO646_CA2,            /* "csa-z243.4-1985-2", "iso-ir-122", "iso646-ca2", "csa7-2", "csiso122canadian2", "csa-z243.419852" */
	CODEC_ISO646_CN,             /* "gb-1988-80", "iso-ir-57", "cn", "iso646-cn", "csiso58gb1988", "gb-198880" */
	CODEC_ISO646_CU,             /* "nc-nc0-10:81", "cuba", "iso-ir-151", "iso646-cu", "nc-nc0-10", "csiso151cuba", "nc-nc10" */
	CODEC_ISO646_DANO_NATS,      /* "nats-dano", "iso-ir-9-1", "cp1016", "ibm1016" */
	CODEC_ISO646_DE,             /* "din-66003", "iso-ir-21", "de", "iso646-de", "ibm1011", "ms-10206", "csiso21german", "german", "d7dec", "cp1011", "cp20106", "windows-20106" */
	CODEC_ISO646_DK,             /* "ds-2089", "ds2089", "iso646-dk", "dk", "csiso646danish", "cp1017", "ibm1017" */
	CODEC_ISO646_DK_NO_ALT_NRCS, /* "cp1107", "ibm1107" */
	CODEC_ISO646_DK_NO_NRCS,     /* "cp1105", "ibm1105" */
	CODEC_ISO646_ES,             /* "es", "iso-ir-17", "iso646-es", "csiso17spanish", "cp1023", "e7dec" */
	CODEC_ISO646_ES2,            /* "es2", "iso-ir-85", "iso646-es2", "csiso85spanish2", "cp1014", "ibm1014" */
	CODEC_ISO646_FI_NRCS,        /* "cp1103", "ibm1103" */
	CODEC_ISO646_FR,             /* "nf-z-62-10", "iso-ir-69", "iso646-fr", "fr", "nf-z-62-10-1983", "nf-z-62-10-(1983)", "csiso69french", "nf-z-62010", "cp1010", "ibm1010" */
	CODEC_ISO646_FR1,            /* "nf-z-62-10-(1973)", "iso-ir-25", "iso646-fr1", "nf-z-62-10-1973", "csiso25french", "nf-z-62010-1973", "cp1104", "f7dec" */
	CODEC_ISO646_GB,             /* "bs-4730", "iso-ir-4", "iso646-gb", "gb", "uk", "csiso4unitedkingdom", "cp1013", "ibm1013" */
	CODEC_ISO646_GB_NRCS,        /* "cp1101", "ibm1101" */
	CODEC_ISO646_HU,             /* "msz-7795.3", "iso-ir-86", "iso646-hu", "hu", "csiso86hungarian" */
	CODEC_ISO646_IE,             /* "iso646-ie", "iso-ir-207" */
	CODEC_ISO646_INIS_SUBSET,    /* "inis", "iso-ir-49" */
	CODEC_ISO646_INV,            /* "iso-ir-170", "invariant" */
	CODEC_ISO646_IRV_1983,       /* "cp1009", "ibm1009", "cp20105", "windows-20105", "koi7-n0" */
	CODEC_ISO646_IS,             /* "iso646-is" */
	CODEC_ISO646_IT,             /* "it", "iso-ir-15", "iso646-it", "csiso15italian", "cp1012", "ibm1012", "i7dec" */
	CODEC_ISO646_JP,             /* "jis-c6220-1969-ro", "iso-ir-14", "jp", "iso646-jp", "csiso14jisc6220ro", "jis-c62201969ro", "cp895", "ibm895" */
	CODEC_ISO646_JP_OCR_B,       /* "jis-c6229-1984-b", "iso-ir-92", "iso646-jp-ocr-b", "jp-ocr-b", "csiso92jisc62991984b", "jis-c62291984b" */
	CODEC_ISO646_KR,             /* "ksc5636", "iso646-kr", "csksc5636", "ks-x-1003", "ksc5636-1989" */
	CODEC_ISO646_LATIN_GR_MIXED, /* "latin-greek-1", "iso-ir-27", "csiso27latingreek1" */
	CODEC_ISO646_MT,             /* "iso646-mt" */
	CODEC_ISO646_NL,             /* "iso646-nl", "cp1019", "ibm1019" */
	CODEC_ISO646_NL_NRCS,        /* "cp1102", "ibm1102" */
	CODEC_ISO646_NO,             /* "ns-4551-1", "iso-ir-60", "iso646-no", "no", "csiso60danishnorwegian", "csiso60norwegian1", "ns-45511" */
	CODEC_ISO646_NO2,            /* "ns-4551-2", "iso646-no2", "iso-ir-61", "no2", "csiso61norwegian2", "ns-45512" */
	CODEC_ISO646_PL,             /* "bn-74/3101-1" */
	CODEC_ISO646_PT,             /* "pt", "iso-ir-16", "iso646-pt", "csiso16portugese" */
	CODEC_ISO646_PT2,            /* "pt2", "iso-ir-84", "iso646-pt2", "csiso84portuguese2", "cp1015", "ibm1015" */
	CODEC_ISO646_SE,             /* "sen-850200-b", "iso-ir-10", "fi", "iso646-fi", "iso646-se", "se", "csiso10swedish", "ss636127", "cp1018", "ibm1018" */
	CODEC_ISO646_SE2,            /* "sen-850200-c", "iso-ir-11", "iso646-se2", "se2", "csiso11swedishfornames" */
	CODEC_ISO646_SEFI_NATS,      /* "iso-ir-8" */
	CODEC_ISO646_SE_NRCS,        /* "cp1106", "ibm1106" */
	CODEC_ISO646_SWI_NRCS,       /* "cp1021", "ibm1021", "ch7dec" */
	CODEC_ISO646_T_61,           /* "t.61-7bit", "iso-ir-102" */
	CODEC_ISO646_VIEWDATA,       /* "bs-viewdata", "iso-ir-47" */
	CODEC_ISO646_YU,             /* "jus-i.b1.2", "iso-ir-141", "iso646-yu", "js", "yu", "csiso141jusib1002" */
	CODEC_ISO_IR_2,              /* "iso646.irv:1983", "iso-ir-2", "irv", "csiso2intlrefversion" */
	CODEC_ISO_IR_8_1,            /* "nats-sefi", "iso-ir-8-1" */
#define CODEC_ISO646_MAX CODEC_ISO_IR_8_1
/*[[[end]]]*/
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
