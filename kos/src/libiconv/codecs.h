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

#include <stdbool.h>

#include <libiconv/codec.h>
#include <libiconv/iconv.h>

DECL_BEGIN

/* Codec IDs. */
STATIC_ASSERT(ICONV_CODEC_FIRST == ICONV_CODEC_UNKNOWN + 1);
enum {
	CODEC_UNKNOWN = ICONV_CODEC_UNKNOWN, /* Invalid codec */

/*[[[deemon (printCodecEnums from .iconvdata.iconvdata)();]]]*/
	/* Custom codecs */
	CODEC_ASCII,      /* "ansi-x3.4-1968", "iso-ir-6", "ansi-x3.4-1986", "iso646.irv:1991", "ascii", "iso646-us", "us-ascii", "us", "ibm367", "cp367", "ansi-x3.4", "csascii", "osf10020", "cp20127", "windows-20127", "ibm891", "cp891", "csibm891", "osf1002037b", "ibm903", "cp903", "csibm903", "osf10020387" */
	CODEC_ISO_8859_1, /* "iso8859-1:1987", "iso-ir-100", "iso8859-1", "latin1", "l1", "ibm819", "cp819", "iso88591", "csisolatin1", "cp28591", "windows-28591", "we8iso8859p1", "cp38591", "windows-38591", "iso8859-1-i", "8859-1", "osf10001" */
	CODEC_UTF16BE,    /* "utf16be", "utf-16be", "ucs-2be", "unicodebig", "csutf16be" */
	CODEC_UTF16LE,    /* "utf16le", "utf-16le", "ucs-2le", "unicodelittle", "csutf16le" */
	CODEC_UTF32BE,    /* "utf32be", "utf-32be", "ucs-4be", "cp12001", "windows-12001", "csutf32be" */
	CODEC_UTF32LE,    /* "utf32le", "utf-32le", "ucs-4le", "csutf32le" */
	CODEC_UTF8,       /* "utf8", "utf-8", "iso10646/utf8", "iso10646/utf-8", "iso-ir-193", "osf5010001", "cp65001", "windows-65001", "csutf8" */

	/* 8-bit codepage codecs */
#define CODEC_CP_MIN CODEC_ADOBE_STANDARD_ENCODING
	CODEC_ADOBE_STANDARD_ENCODING, /* "adobe-standard-encoding", "csadobestandardencoding" */
	CODEC_ADOBE_SYMBOL_ENCODING,   /* "adobe-symbol-encoding", "cshppsmath" */
	CODEC_ADOBE_ZAPF_DINGBATS,     /* "adobe-zapf-dingbats" */
	CODEC_CP1006,                  /* "cp1006", "ibm1006", "iso8-bit-urdu" */
	CODEC_CP1008,                  /* "cp1008", "ibm1008", "csibm1008", "cp5104", "ibm5104" */
	CODEC_CP1025,                  /* "cp1025", "ibm1025", "csibm1025" */
	CODEC_CP1026,                  /* "ibm1026", "cp1026", "csibm1026", "1026", "osf10020402" */
	CODEC_CP1038,                  /* "cp1038", "ibm1038", "x-mac-symbol" */
	CODEC_CP1040,                  /* "cp1040" */
	CODEC_CP1041,                  /* "cp1041" */
	CODEC_CP1042,                  /* "cp1042" */
	CODEC_CP1043,                  /* "cp1043" */
	CODEC_CP1046,                  /* "cp1046", "1046", "ibm1046" */
	CODEC_CP1047,                  /* "cp1047", "ibm1047", "1047", "osf10020417", "csibm1047" */
	CODEC_CP1057,                  /* "cp1057", "hp-pc-8" */
	CODEC_CP1088,                  /* "cp1088" */
	CODEC_CP1097,                  /* "cp1097", "ibm1097", "csibm1097" */
	CODEC_CP1098,                  /* "cp1098", "ibm1098" */
	CODEC_CP1112,                  /* "cp1112", "ibm1112", "csibm1112" */
	CODEC_CP1114,                  /* "cp1114" */
	CODEC_CP1115,                  /* "cp1115" */
	CODEC_CP1122,                  /* "cp1122", "ibm1122", "csibm1122" */
	CODEC_CP1123,                  /* "cp1123", "ibm1123", "csibm1123" */
	CODEC_CP1127,                  /* "cp1127" */
	CODEC_CP1130,                  /* "cp1130", "ibm1130", "csibm1130" */
	CODEC_CP1137,                  /* "cp1137", "ibm1137", "csibm1137" */
	CODEC_CP1140,                  /* "cp1140", "ibm1140", "csibm1140", "ccsid1140", "ebcdic-us-37+euro" */
	CODEC_CP1141,                  /* "cp1141", "ibm1141", "csibm1141", "ccsid1141", "ebcdic-de-273+euro" */
	CODEC_CP1142,                  /* "cp1142", "ibm1142", "csibm1142", "ccsid1142", "ebcdic-dk-277+euro", "ebcdic-no-277+euro" */
	CODEC_CP1143,                  /* "cp1143", "ibm1143", "csibm1143", "ccsid1143", "ebcdic-fi-278+euro", "ebcdic-se-278+euro" */
	CODEC_CP1144,                  /* "cp1144", "ibm1144", "csibm1144", "ccsid1144", "ebcdic-it-280+euro" */
	CODEC_CP1145,                  /* "cp1145", "ibm1145", "csibm1145", "ccsid1145", "ebcdic-es-284+euro" */
	CODEC_CP1146,                  /* "cp1146", "ibm1146", "csibm1146", "ccsid1146", "ebcdic-gb-285+euro" */
	CODEC_CP1147,                  /* "cp1147", "ibm1147", "csibm1147", "ccsid1147", "ebcdic-fr-297+euro" */
	CODEC_CP1148,                  /* "cp1148", "ibm1148", "csibm1148", "ccsid1148", "ebcdic-international-500+euro" */
	CODEC_CP1149,                  /* "cp1149", "ibm1149", "csibm1149", "ccsid1149", "ebcdic-is-871+euro" */
	CODEC_CP1153,                  /* "cp1153", "ibm1153", "csibm1153" */
	CODEC_CP1154,                  /* "cp1154", "ibm1154", "csibm1154" */
	CODEC_CP1155,                  /* "cp1155", "ibm1155", "csibm1155" */
	CODEC_CP1156,                  /* "cp1156", "ibm1156", "csibm1156" */
	CODEC_CP1157,                  /* "cp1157", "ibm1157", "csibm1157" */
	CODEC_CP1158,                  /* "cp1158", "ibm1158", "csibm1158" */
	CODEC_CP1160,                  /* "cp1160", "ibm1160", "csibm1160" */
	CODEC_CP1164,                  /* "cp1164", "ibm1164", "csibm1164" */
	CODEC_CP1166,                  /* "cp1166", "ibm1166", "csibm1166" */
	CODEC_CP12712,                 /* "cp12712", "ibm12712", "csibm12712" */
	CODEC_CP1276,                  /* "cp1276", "postscript-standard-encoding", "standardencoding", "postscript" */
	CODEC_CP16804,                 /* "cp16804", "ibm16804", "csibm16804" */
	CODEC_CP17248,                 /* "cp17248" */
	CODEC_CP273,                   /* "ibm273", "cp273", "csibm273", "osf10020111" */
	CODEC_CP274,                   /* "ibm274", "ebcdic-be", "cp274", "csibm274" */
	CODEC_CP275,                   /* "ibm275", "ebcdic-br", "cp275", "csibm275" */
	CODEC_CP278,                   /* "ibm278", "cp278", "ebcdic-cp-fi", "ebcdic-cp-se", "csibm278", "osf10020116" */
	CODEC_CP280,                   /* "ibm280", "cp280", "ebcdic-cp-it", "csibm280", "osf10020118" */
	CODEC_CP281,                   /* "ibm281", "ebcdic-jp-e", "cp281", "csibm281" */
	CODEC_CP284,                   /* "ibm284", "cp284", "ebcdic-cp-es", "csibm284", "osf1002011c", "cp1079" */
	CODEC_CP285,                   /* "ibm285", "cp285", "ebcdic-cp-gb", "csibm285", "osf1002011d" */
	CODEC_CP290,                   /* "ibm290", "cp290", "ebcdic-jp-kana", "csibm290", "osf10020122" */
	CODEC_CP297,                   /* "ibm297", "cp297", "ebcdic-cp-fr", "csibm297", "osf10020129", "cp1081" */
	CODEC_CP37,                    /* "ibm37", "cp37", "ebcdic-cp-us", "ebcdic-cp-ca", "ebcdic-cp-wt", "ebcdic-cp-nl", "csibm37", "osf10020025", "cp1070", "cp282" */
	CODEC_CP38,                    /* "ibm38", "ebcdic-int", "cp38", "csibm38" */
	CODEC_CP420,                   /* "ibm420", "cp420", "ebcdic-cp-ar1", "csibm420", "osf100201a4" */
	CODEC_CP423,                   /* "ibm423", "cp423", "ebcdic-cp-gr", "csibm423" */
	CODEC_CP424,                   /* "ibm424", "cp424", "ebcdic-cp-he", "csibm424", "osf100201a8" */
	CODEC_CP437,                   /* "ibm437", "cp437", "437", "cspc8codepage437", "oemus", "osf100201b5" */
	CODEC_CP4517,                  /* "cp4517", "ibm4517", "csibm4517" */
	CODEC_CP4899,                  /* "cp4899", "ibm4899", "csibm4899" */
	CODEC_CP4971,                  /* "cp4971", "ibm4971", "csibm4971" */
	CODEC_CP500,                   /* "ibm500", "cp500", "ebcdic-cp-be", "ebcdic-cp-ch", "csibm500", "500", "500v1", "osf100201f4", "cp1084" */
	CODEC_CP803,                   /* "cp803", "ibm803", "csibm803" */
	CODEC_CP864,                   /* "ibm864", "cp864", "csibm864", "864", "osf10020360" */
	CODEC_CP870,                   /* "ibm870", "cp870", "ebcdic-cp-roece", "ebcdic-cp-yu", "csibm870", "osf10020366" */
	CODEC_CP871,                   /* "ibm871", "cp871", "ebcdic-cp-is", "csibm871", "osf10020367" */
	CODEC_CP875,                   /* "cp875", "ibm875", "ebcdic-greek", "osf1002036b" */
	CODEC_CP880,                   /* "ibm880", "cp880", "ebcdic-cyrillic", "csibm880", "osf10020370" */
	CODEC_CP897,                   /* "cp897" */
	CODEC_CP9030,                  /* "cp9030", "ibm9030", "csibm9030" */
	CODEC_CP905,                   /* "ibm905", "cp905", "ebcdic-cp-tr", "csibm905" */
	CODEC_CP9066,                  /* "cp9066", "ibm9066", "csibm9066" */
	CODEC_CP918,                   /* "ibm918", "cp918", "ebcdic-cp-ar2", "csibm918", "osf10020396" */
	CODEC_DIN_66303,               /* "din-66303", "drv8" */
	CODEC_EBCDIC_AT_DE,            /* "ebcdic-at-de", "csibmebcdicatde", "csebcdicatde", "ebcdicatde" */
	CODEC_EBCDIC_AT_DE_A,          /* "ebcdic-at-de-a", "csebcdicatdea", "ebcdicatdea" */
	CODEC_EBCDIC_CA_FR,            /* "ebcdic-ca-fr", "csebcdiccafr", "ebcdiccafr" */
	CODEC_EBCDIC_CP_DK_NO,         /* "ibm277", "ebcdic-cp-dk", "ebcdic-cp-no", "csibm277", "osf10020115" */
	CODEC_EBCDIC_DK_NO,            /* "ebcdic-dk-no", "csebcdicdkno", "ebcdicdkno" */
	CODEC_EBCDIC_DK_NO_A,          /* "ebcdic-dk-no-a", "csebcdicdknoa", "ebcdicdknoa" */
	CODEC_EBCDIC_ES,               /* "ebcdic-es", "csebcdices", "ebcdices" */
	CODEC_EBCDIC_ES_A,             /* "ebcdic-es-a", "csebcdicesa", "ebcdicesa" */
	CODEC_EBCDIC_ES_S,             /* "ebcdic-es-s", "csebcdicess" */
	CODEC_EBCDIC_FI_SE,            /* "ebcdic-fi-se", "csebcdicfise", "ebcdicfise" */
	CODEC_EBCDIC_FI_SE_A,          /* "ebcdic-fi-se-a", "csebcdicfisea", "ebcdicfisea" */
	CODEC_EBCDIC_FR,               /* "ebcdic-fr", "csebcdicfr", "ebcdicfr" */
	CODEC_EBCDIC_IS_FRISS,         /* "ebcdic-is-friss", "ebcdicisfriss" */
	CODEC_EBCDIC_IT,               /* "ebcdic-it", "csebcdicit", "ebcdicit" */
	CODEC_EBCDIC_PT,               /* "ebcdic-pt", "csebcdicpt", "ebcdicpt" */
	CODEC_EBCDIC_UK,               /* "ebcdic-uk", "csebcdicuk", "ebcdicuk" */
	CODEC_EBCDIC_US,               /* "ebcdic-us", "csebcdicus", "ebcdicus" */
	CODEC_IBM256,                  /* "ibm256", "ebcdic-int1" */
	CODEC_ISO_5427,                /* "iso5427", "iso-ir-37", "koi7", "koi7-n1", "koi0", "csiso5427cyrillic" */
	CODEC_ISO_IR_139,              /* "csn-369103", "iso-ir-139", "csiso139csn369103" */
	CODEC_ISO_IR_152,              /* "iso6937-2-25", "iso-ir-152", "csiso6937add" */
	CODEC_LY1,                     /* "ly1" */
	CODEC_MACINTOSH_FONT_X,        /* "macintosh-font-x" */
	CODEC_MSDOS1252,               /* "msdos-1252" */
	CODEC_OSD_EBCDIC_DF03_IRV,     /* "osd-ebcdic-df3-irv", "csosdebcdicdf3irv" */
	CODEC_OSD_EBCDIC_DF04_1,       /* "osd-ebcdic-df4-1", "csosdebcdicdf41" */
	CODEC_OSD_EBCDIC_DF04_15,      /* "osd-ebcdic-df4-15", "csosdebcdicdf415" */
	CODEC_VENTURA_INTERNATIONAL,   /* "ventura-international", "ventura-int", "csventurainternational" */
	CODEC_VENTURA_US,              /* "ventura-us", "csventuraus" */
	CODEC_X0201,                   /* "jis-x201", "x201", "cshalfwidthkatakana" */
#define CODEC_CP_MAX CODEC_X0201

	/* 7l codepage codecs */
#define CODEC_CP7L_MIN CODEC_BCDIC
	CODEC_BCDIC,            /* "bcdic" */
	CODEC_BRF,              /* "brf", "csbrf" */
	CODEC_BURROUGHS_B5500,  /* "burroughs-b5500" */
	CODEC_CP1090,           /* "cp1090", "ibm1090", "dec-special-graphics" */
	CODEC_CP353,            /* "cp353" */
	CODEC_CP355,            /* "cp355", "pttc/bcd" */
	CODEC_CP357,            /* "cp357", "pttc/bcd-h" */
	CODEC_CP358,            /* "cp358", "pttc/bcd-c" */
	CODEC_CP359,            /* "cp359", "pttc/bcd-m", "cp360", "pttc/bcd-d" */
	CODEC_CP896,            /* "cp896", "ibm896", "cp4992" */
	CODEC_CP904,            /* "ibm904", "cp904", "904", "csibbm904", "csibm904", "osf10020388" */
	CODEC_GBCD,             /* "gbcd" */
	CODEC_IBM1401,          /* "ibm1401" */
	CODEC_IBM704,           /* "ibm704" */
	CODEC_IBM7090,          /* "ibm7090", "ibm7094" */
	CODEC_ISO5426,          /* "iso5426" */
	CODEC_ISO5426_2,        /* "iso5426-2" */
	CODEC_ISO_IR_13,        /* "jis-c6220-1969-jp", "jis-c6220-1969", "iso-ir-13", "katakana", "x201-7", "csiso13jisc6220jp" */
	CODEC_ISO_IR_146,       /* "jus-i.b1.3-serb", "iso-ir-146", "serbian", "csiso146serbian" */
	CODEC_ISO_IR_147,       /* "jus-i.b1.3-mac", "macedonian", "iso-ir-147", "csiso147macedonian" */
	CODEC_ISO_IR_150,       /* "greek-ccitt", "iso-ir-150", "csiso150", "csiso150greekccitt", "greekccitt" */
	CODEC_ISO_IR_18,        /* "greek7-old", "greek7old", "iso-ir-18", "csiso18greek7old" */
	CODEC_ISO_IR_19,        /* "latin-greek", "iso-ir-19", "latingreek", "csiso19latingreek" */
	CODEC_ISO_IR_50,        /* "inis-8", "inis8", "iso-ir-50", "csiso50inis8" */
	CODEC_ISO_IR_51,        /* "inis-cyrillic", "iniscyrillic", "iso-ir-51", "csiso51iniscyrillic" */
	CODEC_ISO_IR_54,        /* "iso5427:1981", "iso-ir-54", "iso5427cyrillic1981", "csiso54271981", "iso5427-ext", "iso5427ext", "csiso5427cyrillic1981" */
	CODEC_ISO_IR_55,        /* "iso5428:1980", "iso5428", "iso-ir-55", "csiso5428greek" */
	CODEC_ISO_IR_68,        /* "iso-ir-68" */
	CODEC_ISO_IR_88,        /* "greek7", "iso-ir-88", "csiso88greek7" */
	CODEC_ISO_IR_89,        /* "asmo-449", "iso9036", "arabic7", "iso-ir-89" */
	CODEC_ISO_IR_8_2,       /* "nats-sefi-add", "iso-ir-8-2" */
	CODEC_ISO_IR_91,        /* "jis-c6229-1984-a", "iso-ir-91", "jp-ocr-a", "csiso91jisc62291984a" */
	CODEC_ISO_IR_93,        /* "jis-c6229-1984-b-add", "iso-ir-93", "jp-ocr-b-add", "csiso93jis62291984badd" */
	CODEC_ISO_IR_94,        /* "jis-c6229-1984-hand", "iso-ir-94", "jp-ocr-hand", "csiso94jis62291984hand" */
	CODEC_ISO_IR_95,        /* "jis-c6229-1984-hand-add", "iso-ir-95", "jp-ocr-hand-add", "csiso95jis62291984handadd" */
	CODEC_ISO_IR_96,        /* "jis-c6229-1984-kana", "iso-ir-96", "csiso96jisc62291984kana" */
	CODEC_ISO_IR_98,        /* "iso2033-1983", "iso2033", "iso-ir-98", "e13b", "csiso2033" */
	CODEC_ISO_IR_9_2,       /* "nats-dano-add", "iso-ir-9-2" */
	CODEC_JIS_C_6229_OCR_A, /* "jis-c-6229-ocr-a" */
	CODEC_KOI7_N2,          /* "koi7-n2", "short-koi" */
#define CODEC_CP7L_MAX CODEC_KOI7_N2

	/* 7h codepage codecs */
#define CODEC_CP7H_MIN CODEC_AMIGA_1251
	CODEC_AMIGA_1251,             /* "amiga-1251", "ami1251", "amiga1251", "ami-1251", "csamiga1251" */
	CODEC_ATARIST,                /* "atarist" */
	CODEC_CP10004,                /* "cp10004", "windows-10004", "x-mac-arabic", "macarabic" */
	CODEC_CP10006,                /* "cp10006", "windows-10006", "x-mac-greek" */
	CODEC_CP10007,                /* "cp10007", "windows-10007", "cp1283", "ibm1283", "ms-mac-cyrillic", "msmaccyrillic" */
	CODEC_CP10017,                /* "cp10017", "windows-10017", "x-mac-ukrainian", "macuk", "mac-uk", "macukrainian", "mac-cyrillic", "maccyrillic" */
	CODEC_CP1004,                 /* "cp1004", "windows-extended", "ibm1004", "os2latin1" */
	CODEC_CP1036,                 /* "cp1036", "ibm1036", "t.61", "t.618bit", "t.61-8bit", "cp20261", "windows-20261", "iso-ir-103", "csiso103t618bit" */
	CODEC_CP1100,                 /* "dec-mcs", "dec", "cp1100", "ibm1100", "we8dec", "csdecmcs", "decmcs" */
	CODEC_CP1116,                 /* "cp1116", "ibm1116" */
	CODEC_CP1117,                 /* "cp1117", "ibm1117" */
	CODEC_CP1124,                 /* "cp1124", "ibm1124", "csibm1124" */
	CODEC_CP1125,                 /* "cp1125", "rst-2018-91", "cp866u", "ruscii", "ibm848" */
	CODEC_CP1129,                 /* "cp1129", "ibm1129", "csibm1129" */
	CODEC_CP1131,                 /* "cp1131", "ibm1131" */
	CODEC_CP1132,                 /* "cp1132", "ibm1132", "csibm1132" */
	CODEC_CP1133,                 /* "cp1133", "ibm1133", "csibm1133" */
	CODEC_CP1161,                 /* "cp1161", "ibm1161", "csibm1161" */
	CODEC_CP1162,                 /* "cp1162", "ibm1162", "csibm11621162" */
	CODEC_CP1163,                 /* "cp1163", "ibm1163", "csibm1163" */
	CODEC_CP1250,                 /* "cp1250", "windows-1250", "cswindows1250", "ms-ee" */
	CODEC_CP1251,                 /* "cp1251", "windows-1251", "cswindows1251", "ms-cyrl" */
	CODEC_CP1252,                 /* "cp1252", "windows-1252", "cswindows1252", "ms-ansi" */
	CODEC_CP1253,                 /* "cp1253", "windows-1253", "cswindows1253", "ms-greek" */
	CODEC_CP1254,                 /* "cp1254", "windows-1254", "cswindows1254", "ms-turk" */
	CODEC_CP1255,                 /* "cp1255", "windows-1255", "cswindows1255", "ms-hebr" */
	CODEC_CP1256,                 /* "cp1256", "windows-1256", "cswindows1256", "ms-arab", "cp9448", "ibm9448", "csibm9448" */
	CODEC_CP1257,                 /* "cp1257", "windows-1257", "lst-1590-3", "cswindows1257", "winbaltrim" */
	CODEC_CP1258,                 /* "cp1258", "windows-1258", "cswindows1258" */
	CODEC_CP1270,                 /* "cp1270", "windows-1270", "ws2", "winsami2", "win-sami-2" */
	CODEC_CP1275,                 /* "macintosh", "mac", "csmacintosh", "cp1275", "ibm1275", "cp10000", "windows-10000", "x-mac-roman", "macroman" */
	CODEC_CP1281,                 /* "cp1281", "ibm1281", "cp10081", "windows-10081", "x-mac-turkish" */
	CODEC_CP1282,                 /* "cp1282", "ibm1282", "cp10029", "windows-10029", "x-mac-ce", "mac-centraleurope" */
	CODEC_CP1284,                 /* "cp1284", "ibm1284", "cp10082", "windows-10082", "x-mac-croatian" */
	CODEC_CP1285,                 /* "cp1285", "ibm1285", "cp10010", "windows-10010", "x-mac-romanian" */
	CODEC_CP1286,                 /* "cp1286", "ibm1286", "cp10079", "windows-10079", "x-mac-icelandic" */
	CODEC_CP1287,                 /* "cp1287", "dec-greek-(8-bit)", "dec-greek-8-bit", "dec-greek-8", "dec-greek", "el8dec" */
	CODEC_CP1288,                 /* "cp1288", "dec-turkish-(8-bit)", "dec-turkish-8-bit", "dec-turkish-8", "dec-turkish", "tr8dec" */
	CODEC_CP20269,                /* "cp20269", "t.51", "iso6937", "iso-ir-156", "iso6937:1992" */
	CODEC_CP3012,                 /* "cp3012", "ruslat" */
	CODEC_CP4909,                 /* "cp4909", "ibm4909", "csibm4909" */
	CODEC_CP5347,                 /* "cp5347", "ibm5347", "csibm5347" */
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
	CODEC_CP775,                  /* "cp775", "ibm775", "oem775", "cspc775baltic" */
	CODEC_CP806,                  /* "cp806", "ibm806" */
	CODEC_CP808,                  /* "cp808" */
	CODEC_CP848,                  /* "cp848" */
	CODEC_CP849,                  /* "cp849" */
	CODEC_CP850,                  /* "ibm850", "cp850", "850", "cspc850multilingual", "oem850", "osf10020352" */
	CODEC_CP851,                  /* "ibm851", "cp851", "851", "csibm851" */
	CODEC_CP852,                  /* "ibm852", "cp852", "852", "cspcp852", "osf10020354" */
	CODEC_CP853,                  /* "cp853", "ibm853" */
	CODEC_CP855,                  /* "ibm855", "cp855", "855", "oem855", "csibm855", "osf10020357" */
	CODEC_CP856,                  /* "cp856", "ibm856", "856", "csibm856" */
	CODEC_CP857,                  /* "ibm857", "cp857", "857", "oem857", "csibm857", "osf10020359" */
	CODEC_CP858,                  /* "cp858", "ibm858", "oem858", "pc-multilingual-850+euro", "ccsid858", "csibm858", "858", "cspc858multilingual" */
	CODEC_CP859,                  /* "cp859", "ibm859" */
	CODEC_CP860,                  /* "ibm860", "cp860", "860", "oem860", "csibm860" */
	CODEC_CP861,                  /* "ibm861", "cp861", "861", "oem861", "cp-is", "csibm861", "cpibm861", "osf1002035d" */
	CODEC_CP862,                  /* "ibm862", "cp862", "862", "oem862", "cspc862latinhebrew", "osf1002035e" */
	CODEC_CP863,                  /* "ibm863", "cp863", "863", "oem863", "csibm863", "osf1002035f" */
	CODEC_CP865,                  /* "ibm865", "cp865", "865", "oem865", "csibm865" */
	CODEC_CP866,                  /* "cp866", "866", "ibm866", "csibm866" */
	CODEC_CP866NAV,               /* "cp866nav", "866nav", "ibm866nav" */
	CODEC_CP867,                  /* "cp867" */
	CODEC_CP868,                  /* "ibm868", "cp868", "cp-ar", "csibm868", "osf10020364" */
	CODEC_CP869,                  /* "ibm869", "cp869", "869", "cp-gr", "oem869", "csibm869", "osf10020365" */
	CODEC_CP872,                  /* "cp872" */
	CODEC_CP874,                  /* "cp874", "ibm874", "x-ibm874", "874", "windows-874", "ms874", "x-windows-874", "cswindows874" */
	CODEC_CP901,                  /* "cp901", "ibm901", "csibm901", "iso-ir-206" */
	CODEC_CP902,                  /* "cp902", "ibm902", "csibm902" */
	CODEC_CP921,                  /* "cp921", "ibm921", "csibm921", "iso8859-13", "iso885913", "iso-ir-179", "csisolatin7", "latin7", "l7", "baltic", "cp28603", "windows-28603", "csiso885913" */
	CODEC_CP922,                  /* "cp922", "ibm922", "csibm922", "estonia-iso-8" */
	CODEC_CWI,                    /* "cwi", "cwi-2", "cp-hu" */
	CODEC_EXTENDED_LATIN_8,       /* "extended-latin-8" */
	CODEC_GEORGIAN_ACADEMY,       /* "georgian-academy" */
	CODEC_GEORGIAN_PS,            /* "georgian-ps" */
	CODEC_HP_GREEK8,              /* "hp-greek8", "hpgreek8", "osf10010004" */
	CODEC_HP_ROMAN8,              /* "hp-roman8", "roman8", "r8", "cshproman8", "osf10010001", "hproman8", "cp1050", "ibm1050", "hp-roman-8", "cp1051", "ibm1051" */
	CODEC_HP_ROMAN9,              /* "hp-roman9", "roman9", "r9", "hproman9" */
	CODEC_HP_THAI8,               /* "hp-thai8", "hpthai8", "thai8" */
	CODEC_HP_TURKISH8,            /* "hp-turkish8", "hpturkish8", "turkish8", "osf10010006" */
	CODEC_ISIRI3342,              /* "isiri3342", "isiri-3342" */
	CODEC_ISO6438,                /* "iso6438" */
	CODEC_ISO_6937_2,             /* "iso6937-2", "iso69372", "iso6937-2:1983", "iso-ir-90", "csiso90" */
	CODEC_ISO_8859_10,            /* "latin6", "iso-ir-157", "l6", "iso8859-10", "iso8859-10:1992", "iso885910", "csisolatin6", "ibm919", "cp919", "cp28600", "windows-28600", "osf1000a" */
	CODEC_ISO_8859_11,            /* "iso8859-11", "iso885911", "cp28601", "windows-28601", "iso-ir-166", "tis-620", "cstis620", "tis620", "tis620-0", "tis620.2529-1", "tis620.2533-0" */
	CODEC_ISO_8859_14,            /* "iso8859-14", "iso8859-14:1998", "iso885914", "iso-ir-199", "iso-celtic", "latin8", "l8", "cp28604", "windows-28604", "csiso885914" */
	CODEC_ISO_8859_15,            /* "iso8859-15", "iso8859-15:1998", "iso885915", "iso-ir-203", "latin9", "latin0", "ibm923", "cp923", "cp28605", "windows-28605", "csiso885915" */
	CODEC_ISO_8859_16,            /* "iso8859-16", "iso8859-16:2001", "iso885916", "iso-ir-226", "latin10", "l10", "sr-14111", "cp28606", "windows-28606", "csiso885916" */
	CODEC_ISO_8859_2,             /* "iso8859-2:1987", "iso-ir-101", "iso8859-2", "latin2", "l2", "iso88592", "csisolatin2", "ibm1111", "cp1111", "cp28592", "windows-28592", "8859-2", "osf10002", "cp912", "ibm912" */
	CODEC_ISO_8859_3,             /* "iso8859-3:1988", "iso-ir-109", "iso8859-3", "latin3", "l3", "iso88593", "csisolatin3", "ibm913", "cp913", "cp28593", "windows-28593", "8859-3", "osf10003" */
	CODEC_ISO_8859_4,             /* "iso8859-4:1988", "iso-ir-110", "iso8859-4", "latin4", "l4", "iso88594", "csisolatin4", "ibm914", "cp914", "cp28594", "windows-28594", "8859-4", "osf10004" */
	CODEC_ISO_8859_5,             /* "iso8859-5:1988", "iso-ir-144", "iso8859-5", "cyrillic", "iso88595", "csisolatincyrillic", "cp28595", "windows-28595", "8859-5", "osf10005", "cp915", "ibm915" */
	CODEC_ISO_8859_6,             /* "iso8859-6:1987", "iso-ir-127", "iso8859-6", "ecma-114", "asmo-708", "arabic", "iso88596", "csisolatinarabic", "ibm1089", "cp1089", "cp28596", "windows-28596", "cp38596", "windows-38596", "iso8859-6-i", "8859-6", "osf10006" */
	CODEC_ISO_8859_7,             /* "iso8859-7:1987", "iso-ir-126", "iso8859-7", "elot-928", "ecma-118", "greek", "greek8", "iso8859-7:2003", "csisolatingreek", "ibm813", "cp813", "cp28597", "windows-28597", "iso88597", "8859-7", "osf10007" */
	CODEC_ISO_8859_8,             /* "iso8859-8:1988", "iso-ir-138", "iso8859-8", "hebrew", "iso88598", "csisolatinhebrew", "ibm916", "cp916", "cp28598", "windows-28598", "cp38598", "windows-38598", "iso8859-8-i", "8859-8", "osf10008" */
	CODEC_ISO_8859_9,             /* "iso8859-9:1989", "iso-ir-148", "iso8859-9", "latin5", "l5", "iso88599", "csisolatin5", "ibm920", "cp920", "cp28599", "windows-28599", "8859-9", "osf10009", "ts-5881", "ecma-128" */
	CODEC_ISO_8859_9E,            /* "iso8859-9e", "iso88599e" */
	CODEC_ISO_IR_123,             /* "csa-z243.4-1985-gr", "iso-ir-123", "csiso123csaz24341985gr" */
	CODEC_ISO_IR_143,             /* "iec-p27-1", "iso-ir-143", "csiso143iecp271", "iec-p271" */
	CODEC_ISO_IR_153,             /* "gost-19768-74", "st-sev-358-88", "iso-ir-153", "csiso153gost1976874", "gost-19768", "gost-1976874" */
	CODEC_ISO_IR_154,             /* "iso8859-supp", "iso-ir-154", "latin1-2-5", "csiso8859supp" */
	CODEC_ISO_IR_155,             /* "iso10367-box", "iso10367box", "iso-ir-155", "csiso10367box" */
	CODEC_ISO_IR_158,             /* "latin-lap", "lap", "iso-ir-158", "csiso158lap" */
	CODEC_ISO_IR_182,             /* "iso-ir-182" */
	CODEC_ISO_IR_197,             /* "iso-ir-197" */
	CODEC_ISO_IR_200,             /* "iso-ir-200" */
	CODEC_ISO_IR_201,             /* "iso-ir-201" */
	CODEC_ISO_IR_209,             /* "iso-ir-209" */
	CODEC_KEYBCS2,                /* "nec-867", "dos-895", "keybcs2", "kamenicky" */
	CODEC_KOI8,                   /* "koi8" */
	CODEC_KOI8_B,                 /* "koi8-b" */
	CODEC_KOI8_E,                 /* "ecma-cyrillic", "ecmacyrillic", "iso-ir-111", "ecma-113", "koi8-e", "csiso111ecmacyrillic" */
	CODEC_KOI8_F,                 /* "koi8-f", "koi8-unified" */
	CODEC_KOI8_N1,                /* "koi8-n1" */
	CODEC_KOI8_N2,                /* "koi8-n2" */
	CODEC_KOI8_R,                 /* "koi8-r", "cp20866", "cp878", "ibm878", "cskoi8r" */
	CODEC_KOI8_RU,                /* "koi8-ru", "cp1167", "ibm1167", "csibm1167" */
	CODEC_KOI8_T,                 /* "koi8-t" */
	CODEC_KOI8_U,                 /* "koi8-u", "koi8u", "cp21866", "cp1168", "ibm1168", "cskoi8u" */
	CODEC_KZ_1048,                /* "kz-1048", "kz1048", "strk1048-2002", "rk1048", "cskz1048" */
	CODEC_LICS,                   /* "lics" */
	CODEC_MACINTOSH_LATIN,        /* "macintosh-latin" */
	CODEC_MACIS,                  /* "macis", "mac-is" */
	CODEC_MAC_OS_THAI,            /* "mac-os-thai" */
	CODEC_MAC_SAMI,               /* "mac-sami" */
	CODEC_MIK,                    /* "mik", "bulgaria-pc" */
	CODEC_NEXTSTEP,               /* "nextstep" */
	CODEC_PALMOS,                 /* "palmos" */
	CODEC_PT154,                  /* "ptcp154", "csptcp154", "pt154", "cp154", "cyrillic-asian" */
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
#define CODEC_ISO646_MIN CODEC_DK_US
	CODEC_DK_US,                 /* "dk-us", "csdkus" */
	CODEC_ISO646_BASIC,          /* "iso646.basic:1983", "ref" */
	CODEC_ISO646_CA,             /* "csa-z243.4-1985-1", "iso-ir-121", "iso646-ca", "csa7-1", "ca", "csiso121canadian1", "csa-z243.419851", "cp1020", "csa71" */
	CODEC_ISO646_CA2,            /* "csa-z243.4-1985-2", "iso-ir-122", "iso646-ca2", "csa7-2", "csiso122canadian2", "csa-z243.419852", "csa72" */
	CODEC_ISO646_CN,             /* "gb-1988-80", "iso-ir-57", "cn", "iso646-cn", "csiso57gb1988", "csiso58gb1988", "gb-198880" */
	CODEC_ISO646_CU,             /* "nc-nc0-10:81", "cuba", "iso-ir-151", "iso646-cu", "nc-nc0-10", "csiso151cuba", "nc-nc10" */
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
	CODEC_ISO646_INIS_SUBSET,    /* "inis", "iso-ir-49", "csiso49inis" */
	CODEC_ISO646_INV,            /* "iso-ir-170", "invariant" */
	CODEC_ISO646_IRV_1983,       /* "cp1009", "ibm1009", "cp20105", "windows-20105", "koi7-n0" */
	CODEC_ISO646_IS,             /* "iso646-is" */
	CODEC_ISO646_IT,             /* "it", "iso-ir-15", "iso646-it", "csiso15italian", "cp1012", "ibm1012", "i7dec" */
	CODEC_ISO646_JP,             /* "jis-c6220-1969-ro", "iso-ir-14", "jp", "iso646-jp", "csiso14jisc6220ro", "jis-c62201969ro", "cp895", "ibm895" */
	CODEC_ISO646_JP_OCR_B,       /* "jis-c6229-1984-b", "iso-ir-92", "iso646-jp-ocr-b", "jp-ocr-b", "csiso92jisc62991984b", "jis-c62291984b" */
	CODEC_ISO646_KR,             /* "ksc5636", "iso646-kr", "csksc5636", "ks-x-1003", "ksc5636-1989" */
	CODEC_ISO646_LATIN_GR_MIXED, /* "latin-greek-1", "latingreek1", "iso-ir-27", "csiso27latingreek1" */
	CODEC_ISO646_MT,             /* "iso646-mt" */
	CODEC_ISO646_NATS_DANO,      /* "nats-dano", "iso-ir-9-1", "cp1016", "ibm1016", "csnatsdano", "natsdano" */
	CODEC_ISO646_NL,             /* "iso646-nl", "cp1019", "ibm1019" */
	CODEC_ISO646_NL_NRCS,        /* "cp1102", "ibm1102" */
	CODEC_ISO646_NO,             /* "ns-4551-1", "iso-ir-60", "iso646-no", "no", "csiso60danishnorwegian", "csiso60norwegian1", "ns-45511" */
	CODEC_ISO646_NO2,            /* "ns-4551-2", "iso646-no2", "iso-ir-61", "no2", "csiso61norwegian2", "ns-45512" */
	CODEC_ISO646_PL,             /* "bn-74/3101-1" */
	CODEC_ISO646_PT,             /* "pt", "iso-ir-16", "iso646-pt", "csiso16portugese", "csiso16portuguese" */
	CODEC_ISO646_PT2,            /* "pt2", "iso-ir-84", "iso646-pt2", "csiso84portuguese2", "cp1015", "ibm1015" */
	CODEC_ISO646_SE,             /* "sen-850200-b", "iso-ir-10", "fi", "iso646-fi", "iso646-se", "se", "csiso10swedish", "ss636127", "cp1018", "ibm1018" */
	CODEC_ISO646_SE2,            /* "sen-850200-c", "iso-ir-11", "iso646-se2", "se2", "csiso11swedishfornames" */
	CODEC_ISO646_SEFI_NATS,      /* "iso-ir-8" */
	CODEC_ISO646_SE_NRCS,        /* "cp1106", "ibm1106" */
	CODEC_ISO646_SWI_NRCS,       /* "cp1021", "ibm1021", "ch7dec" */
	CODEC_ISO646_T_61,           /* "t.61-7bit", "iso-ir-102", "csiso102t617bit" */
	CODEC_ISO646_VIEWDATA,       /* "bs-viewdata", "iso-ir-47", "csiso47bsviewdata" */
	CODEC_ISO646_YU,             /* "jus-i.b1.2", "iso-ir-141", "iso646-yu", "js", "yu", "csiso141jusib1002" */
	CODEC_ISO_IR_2,              /* "iso646.irv:1983", "iso-ir-2", "irv", "csiso2intlrefversion" */
	CODEC_ISO_IR_8_1,            /* "nats-sefi", "natssefi", "iso-ir-8-1", "csnatssefi" */
	CODEC_US_DK,                 /* "us-dk", "csusdk" */
#define CODEC_ISO646_MAX CODEC_US_DK
/*[[[end]]]*/
};

/* Return the internal ID of the codec associated with `name'
 * Casing   is  ignored  and  codec  aliases  are  respected.
 * @return: * :                  Internal codec ID (s.a. `iconv_getcodecname()')
 * @return: ICONV_CODEC_UNKNOWN: Unrecognized codec. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) iconv_codec_t
NOTHROW_NCX(CC libiconv_codecbyname)(char const *__restrict name);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) iconv_codec_t
NOTHROW_NCX(CC libiconv_codecbynamez)(char const *__restrict name, size_t namelen);

/* Return the nth (0-based) lexicographically sorted name for the codec `id'
 * When `id'  is  invalid or  doesn't  have  an `nth'  name,  return  `NULL'
 * Note  that all valid codecs have at least 1 (iow: `nth=0') valid name. As
 * such,  supported  codecs as  well as  their names  can be  enumerated as:
 * >> iconv_codec_t id;
 * >> for (id = ICONV_CODEC_FIRST;;) {
 * >>     unsigned int nth = 0;
 * >>     char const *name;
 * >>     for (nth = 0; (name = iconv_getcodecname(id, nth)) != NULL; ++nth) {
 * >>         if (nth != 0)
 * >>             putc('\t');
 * >>         printf("%s", name);
 * >>     }
 * >>     putc('\n');
 * >>     if (nth == 0)
 * >>         break;
 * >> } */
INTDEF ATTR_CONST WUNUSED char const *
NOTHROW_NCX(CC libiconv_getcodecname)(iconv_codec_t id, unsigned int nth);


/* Same as `iconv_codecbyname()', but also parse possible flag-relation options.
 * The given `*pflags' argument must already be populated with valid data before
 * this function is called, and should usually point to `icd_flags' or `ice_flags' */
INTDEF WUNUSED NONNULL((1)) iconv_codec_t
NOTHROW_NCX(CC libiconv_codec_and_flags_byname)(char const *__restrict name,
                                                /*[in|out]*/ uintptr_half_t *__restrict pflags);

/* Check  if  the 2  given strings  reference  the same  codec name.
 * This differs from same codec ID as this function doesn't actually
 * search the codec database but will simply strip potential  flags,
 * normalize the underlying codec names, and check if the  resulting
 * strings strcasecmp(3) to be equal. */
INTDEF ATTR_CONST WUNUSED NONNULL((1, 2)) bool
NOTHROW_NCX(CC libiconv_same_codec_name)(char const *__restrict a,
                                         char const *__restrict b);


DECL_END

#endif /* !GUARD_LIBICONV_CODECS_H */
