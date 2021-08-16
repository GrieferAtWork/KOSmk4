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
#ifndef GUARD_LIBICONV_CODECS_C
#define GUARD_LIBICONV_CODECS_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/align.h>

#include <kos/types.h>

#include <alloca.h>
#include <ctype.h>
#include <string.h>

#include <libiconv/iconv.h>

#include "codecs.h"

DECL_BEGIN

/*[[[deemon (printCodecNameDB from .iconvdata.iconvdata)();]]]*/
#define CODE_NAME_MAXLEN 28
struct codec_db_entry {
	char         cdbe_name[CEIL_ALIGN(29, __SIZEOF_INT__)];
	unsigned int cdbe_codec; /* The associated codec. */
};

PRIVATE struct codec_db_entry codec_db[] = {
	{ "1026",                         CODEC_CP1026 },
	{ "1046",                         CODEC_CP1046 },
	{ "1047",                         CODEC_CP1047 },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "10646-1:1993",                 CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "10646-1:1993",                 CODEC_UTF32LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "10646-1:1993/ucs4",            CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "10646-1:1993/ucs4",            CODEC_UTF32LE },
#endif /* ... */
	{ "437",                          CODEC_CP437 },
	{ "500",                          CODEC_CP500 },
	{ "500v1",                        CODEC_CP500 },
	{ "850",                          CODEC_CP850 },
	{ "851",                          CODEC_CP851 },
	{ "852",                          CODEC_CP852 },
	{ "855",                          CODEC_CP855 },
	{ "856",                          CODEC_CP856 },
	{ "857",                          CODEC_CP857 },
	{ "858",                          CODEC_CP858 },
	{ "860",                          CODEC_CP860 },
	{ "861",                          CODEC_CP861 },
	{ "862",                          CODEC_CP862 },
	{ "863",                          CODEC_CP863 },
	{ "864",                          CODEC_CP864 },
	{ "865",                          CODEC_CP865 },
	{ "866",                          CODEC_CP866 },
	{ "866nav",                       CODEC_CP866NAV },
	{ "869",                          CODEC_CP869 },
	{ "874",                          CODEC_CP874 },
	{ "8859-1",                       CODEC_ISO_8859_1 },
	{ "8859-2",                       CODEC_ISO_8859_2 },
	{ "8859-3",                       CODEC_ISO_8859_3 },
	{ "8859-4",                       CODEC_ISO_8859_4 },
	{ "8859-5",                       CODEC_ISO_8859_5 },
	{ "8859-6",                       CODEC_ISO_8859_6 },
	{ "8859-7",                       CODEC_ISO_8859_7 },
	{ "8859-8",                       CODEC_ISO_8859_8 },
	{ "8859-9",                       CODEC_ISO_8859_9 },
	{ "904",                          CODEC_CP904 },
	{ "adobe-standard-encoding",      CODEC_ADOBE_STANDARD_ENCODING },
	{ "adobe-symbol-encoding",        CODEC_ADOBE_SYMBOL_ENCODING },
	{ "adobe-zapf-dingbats",          CODEC_ADOBE_ZAPF_DINGBATS },
	{ "ami-1251",                     CODEC_AMIGA_1251 },
	{ "ami1251",                      CODEC_AMIGA_1251 },
	{ "amiga-1251",                   CODEC_AMIGA_1251 },
	{ "amiga1251",                    CODEC_AMIGA_1251 },
	{ "ansi-x3.4",                    CODEC_ASCII },
	{ "ansi-x3.4-1968",               CODEC_ASCII },
	{ "ansi-x3.4-1986",               CODEC_ASCII },
	{ "arabic",                       CODEC_ISO_8859_6 },
	{ "arabic7",                      CODEC_ISO_IR_89 },
	{ "ascii",                        CODEC_ASCII },
	{ "asmo-449",                     CODEC_ISO_IR_89 },
	{ "asmo-708",                     CODEC_ISO_8859_6 },
	{ "baltic",                       CODEC_CP921 },
	{ "bcdic",                        CODEC_BCDIC },
	{ "bn-74/3101-1",                 CODEC_ISO646_PL },
	{ "brf",                          CODEC_BRF },
	{ "bs-4730",                      CODEC_ISO646_GB },
	{ "bs-viewdata",                  CODEC_ISO646_VIEWDATA },
	{ "bulgaria-pc",                  CODEC_MIK },
	{ "burroughs-b5500",              CODEC_BURROUGHS_B5500 },
	{ "ca",                           CODEC_ISO646_CA },
	{ "ccsid858",                     CODEC_CP858 },
	{ "ch7dec",                       CODEC_ISO646_SWI_NRCS },
	{ "cn",                           CODEC_ISO646_CN },
	{ "cp-ar",                        CODEC_CP868 },
	{ "cp-gr",                        CODEC_CP869 },
	{ "cp-hu",                        CODEC_CWI },
	{ "cp-is",                        CODEC_CP861 },
	{ "cp10000",                      CODEC_CP1275 },
	{ "cp10004",                      CODEC_CP10004 },
	{ "cp10006",                      CODEC_CP10006 },
	{ "cp10007",                      CODEC_CP10007 },
	{ "cp10010",                      CODEC_CP1285 },
	{ "cp10017",                      CODEC_CP10017 },
	{ "cp10029",                      CODEC_CP1282 },
	{ "cp1004",                       CODEC_CP1004 },
	{ "cp1006",                       CODEC_CP1006 },
	{ "cp10079",                      CODEC_CP1286 },
	{ "cp1008",                       CODEC_CP1008 },
	{ "cp10081",                      CODEC_CP1281 },
	{ "cp10082",                      CODEC_CP1284 },
	{ "cp1009",                       CODEC_ISO646_IRV_1983 },
	{ "cp1010",                       CODEC_ISO646_FR },
	{ "cp1011",                       CODEC_ISO646_DE },
	{ "cp1012",                       CODEC_ISO646_IT },
	{ "cp1013",                       CODEC_ISO646_GB },
	{ "cp1014",                       CODEC_ISO646_ES2 },
	{ "cp1015",                       CODEC_ISO646_PT2 },
	{ "cp1016",                       CODEC_ISO646_NATS_DANO },
	{ "cp1017",                       CODEC_ISO646_DK },
	{ "cp1018",                       CODEC_ISO646_SE },
	{ "cp1019",                       CODEC_ISO646_NL },
	{ "cp1020",                       CODEC_ISO646_CA },
	{ "cp1021",                       CODEC_ISO646_SWI_NRCS },
	{ "cp1023",                       CODEC_ISO646_ES },
	{ "cp1025",                       CODEC_CP1025 },
	{ "cp1026",                       CODEC_CP1026 },
	{ "cp1036",                       CODEC_CP1036 },
	{ "cp1038",                       CODEC_CP1038 },
	{ "cp1040",                       CODEC_CP1040 },
	{ "cp1041",                       CODEC_CP1041 },
	{ "cp1042",                       CODEC_CP1042 },
	{ "cp1043",                       CODEC_CP1043 },
	{ "cp1046",                       CODEC_CP1046 },
	{ "cp1047",                       CODEC_CP1047 },
	{ "cp1050",                       CODEC_HP_ROMAN8 },
	{ "cp1051",                       CODEC_HP_ROMAN8 },
	{ "cp1057",                       CODEC_CP1057 },
	{ "cp1070",                       CODEC_CP37 },
	{ "cp1079",                       CODEC_CP284 },
	{ "cp1081",                       CODEC_CP297 },
	{ "cp1084",                       CODEC_CP500 },
	{ "cp1088",                       CODEC_CP1088 },
	{ "cp1089",                       CODEC_ISO_8859_6 },
	{ "cp1090",                       CODEC_CP1090 },
	{ "cp1097",                       CODEC_CP1097 },
	{ "cp1098",                       CODEC_CP1098 },
	{ "cp1100",                       CODEC_CP1100 },
	{ "cp1101",                       CODEC_ISO646_GB_NRCS },
	{ "cp1102",                       CODEC_ISO646_NL_NRCS },
	{ "cp1103",                       CODEC_ISO646_FI_NRCS },
	{ "cp1104",                       CODEC_ISO646_FR1 },
	{ "cp1105",                       CODEC_ISO646_DK_NO_NRCS },
	{ "cp1106",                       CODEC_ISO646_SE_NRCS },
	{ "cp1107",                       CODEC_ISO646_DK_NO_ALT_NRCS },
	{ "cp1111",                       CODEC_ISO_8859_2 },
	{ "cp1112",                       CODEC_CP1112 },
	{ "cp1114",                       CODEC_CP1114 },
	{ "cp1115",                       CODEC_CP1115 },
	{ "cp1116",                       CODEC_CP1116 },
	{ "cp1117",                       CODEC_CP1117 },
	{ "cp1118",                       CODEC_CP774 },
	{ "cp1119",                       CODEC_CP772 },
	{ "cp1122",                       CODEC_CP1122 },
	{ "cp1123",                       CODEC_CP1123 },
	{ "cp1124",                       CODEC_CP1124 },
	{ "cp1125",                       CODEC_CP1125 },
	{ "cp1127",                       CODEC_CP1127 },
	{ "cp1129",                       CODEC_CP1129 },
	{ "cp1130",                       CODEC_CP1130 },
	{ "cp1131",                       CODEC_CP1131 },
	{ "cp1132",                       CODEC_CP1132 },
	{ "cp1133",                       CODEC_CP1133 },
	{ "cp1137",                       CODEC_CP1137 },
	{ "cp1140",                       CODEC_CP1140 },
	{ "cp1141",                       CODEC_CP1141 },
	{ "cp1142",                       CODEC_CP1142 },
	{ "cp1143",                       CODEC_CP1143 },
	{ "cp1144",                       CODEC_CP1144 },
	{ "cp1145",                       CODEC_CP1145 },
	{ "cp1146",                       CODEC_CP1146 },
	{ "cp1147",                       CODEC_CP1147 },
	{ "cp1148",                       CODEC_CP1148 },
	{ "cp1149",                       CODEC_CP1149 },
	{ "cp1153",                       CODEC_CP1153 },
	{ "cp1154",                       CODEC_CP1154 },
	{ "cp1155",                       CODEC_CP1155 },
	{ "cp1156",                       CODEC_CP1156 },
	{ "cp1157",                       CODEC_CP1157 },
	{ "cp1158",                       CODEC_CP1158 },
	{ "cp1160",                       CODEC_CP1160 },
	{ "cp1161",                       CODEC_CP1161 },
	{ "cp1162",                       CODEC_CP1162 },
	{ "cp1163",                       CODEC_CP1163 },
	{ "cp1164",                       CODEC_CP1164 },
	{ "cp1166",                       CODEC_CP1166 },
	{ "cp1167",                       CODEC_KOI8_RU },
	{ "cp1168",                       CODEC_KOI8_U },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "cp1200",                       CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "cp1200",                       CODEC_UTF16LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "cp12000",                      CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "cp12000",                      CODEC_UTF32LE },
#endif /* ... */
	{ "cp12001",                      CODEC_UTF32BE },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "cp1201",                       CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "cp1201",                       CODEC_UTF16LE },
#endif /* ... */
	{ "cp1250",                       CODEC_CP1250 },
	{ "cp1251",                       CODEC_CP1251 },
	{ "cp1252",                       CODEC_CP1252 },
	{ "cp1253",                       CODEC_CP1253 },
	{ "cp1254",                       CODEC_CP1254 },
	{ "cp1255",                       CODEC_CP1255 },
	{ "cp1256",                       CODEC_CP1256 },
	{ "cp1257",                       CODEC_CP1257 },
	{ "cp1258",                       CODEC_CP1258 },
	{ "cp1270",                       CODEC_CP1270 },
	{ "cp12712",                      CODEC_CP12712 },
	{ "cp1275",                       CODEC_CP1275 },
	{ "cp1276",                       CODEC_CP1276 },
	{ "cp1281",                       CODEC_CP1281 },
	{ "cp1282",                       CODEC_CP1282 },
	{ "cp1283",                       CODEC_CP10007 },
	{ "cp1284",                       CODEC_CP1284 },
	{ "cp1285",                       CODEC_CP1285 },
	{ "cp1286",                       CODEC_CP1286 },
	{ "cp1287",                       CODEC_CP1287 },
	{ "cp1288",                       CODEC_CP1288 },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "cp13488",                      CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "cp13488",                      CODEC_UTF16LE },
#endif /* ... */
	{ "cp154",                        CODEC_PT154 },
	{ "cp16804",                      CODEC_CP16804 },
	{ "cp17248",                      CODEC_CP17248 },
	{ "cp20105",                      CODEC_ISO646_IRV_1983 },
	{ "cp20106",                      CODEC_ISO646_DE },
	{ "cp20127",                      CODEC_ASCII },
	{ "cp20261",                      CODEC_CP1036 },
	{ "cp20269",                      CODEC_CP20269 },
	{ "cp20866",                      CODEC_KOI8_R },
	{ "cp21866",                      CODEC_KOI8_U },
	{ "cp273",                        CODEC_CP273 },
	{ "cp274",                        CODEC_CP274 },
	{ "cp275",                        CODEC_CP275 },
	{ "cp278",                        CODEC_CP278 },
	{ "cp280",                        CODEC_CP280 },
	{ "cp281",                        CODEC_CP281 },
	{ "cp282",                        CODEC_CP37 },
	{ "cp284",                        CODEC_CP284 },
	{ "cp285",                        CODEC_CP285 },
	{ "cp28591",                      CODEC_ISO_8859_1 },
	{ "cp28592",                      CODEC_ISO_8859_2 },
	{ "cp28593",                      CODEC_ISO_8859_3 },
	{ "cp28594",                      CODEC_ISO_8859_4 },
	{ "cp28595",                      CODEC_ISO_8859_5 },
	{ "cp28596",                      CODEC_ISO_8859_6 },
	{ "cp28597",                      CODEC_ISO_8859_7 },
	{ "cp28598",                      CODEC_ISO_8859_8 },
	{ "cp28599",                      CODEC_ISO_8859_9 },
	{ "cp28600",                      CODEC_ISO_8859_10 },
	{ "cp28601",                      CODEC_ISO_8859_11 },
	{ "cp28603",                      CODEC_CP921 },
	{ "cp28604",                      CODEC_ISO_8859_14 },
	{ "cp28605",                      CODEC_ISO_8859_15 },
	{ "cp28606",                      CODEC_ISO_8859_16 },
	{ "cp290",                        CODEC_CP290 },
	{ "cp297",                        CODEC_CP297 },
	{ "cp3012",                       CODEC_CP3012 },
	{ "cp353",                        CODEC_CP353 },
	{ "cp355",                        CODEC_CP355 },
	{ "cp357",                        CODEC_CP357 },
	{ "cp358",                        CODEC_CP358 },
	{ "cp359",                        CODEC_CP359 },
	{ "cp360",                        CODEC_CP359 },
	{ "cp367",                        CODEC_ASCII },
	{ "cp37",                         CODEC_CP37 },
	{ "cp38",                         CODEC_CP38 },
	{ "cp38591",                      CODEC_ISO_8859_1 },
	{ "cp38596",                      CODEC_ISO_8859_6 },
	{ "cp38598",                      CODEC_ISO_8859_8 },
	{ "cp420",                        CODEC_CP420 },
	{ "cp423",                        CODEC_CP423 },
	{ "cp424",                        CODEC_CP424 },
	{ "cp437",                        CODEC_CP437 },
	{ "cp4517",                       CODEC_CP4517 },
	{ "cp4899",                       CODEC_CP4899 },
	{ "cp4909",                       CODEC_CP4909 },
	{ "cp4971",                       CODEC_CP4971 },
	{ "cp4992",                       CODEC_CP896 },
	{ "cp500",                        CODEC_CP500 },
	{ "cp5104",                       CODEC_CP1008 },
	{ "cp5347",                       CODEC_CP5347 },
	{ "cp65001",                      CODEC_UTF8 },
	{ "cp667",                        CODEC_CP667 },
	{ "cp668",                        CODEC_CP668 },
	{ "cp708",                        CODEC_CP708 },
	{ "cp720",                        CODEC_CP720 },
	{ "cp737",                        CODEC_CP737 },
	{ "cp770",                        CODEC_CP770 },
	{ "cp771",                        CODEC_CP771 },
	{ "cp772",                        CODEC_CP772 },
	{ "cp773",                        CODEC_CP773 },
	{ "cp774",                        CODEC_CP774 },
	{ "cp775",                        CODEC_CP775 },
	{ "cp790",                        CODEC_CP667 },
	{ "cp803",                        CODEC_CP803 },
	{ "cp806",                        CODEC_CP806 },
	{ "cp808",                        CODEC_CP808 },
	{ "cp813",                        CODEC_ISO_8859_7 },
	{ "cp819",                        CODEC_ISO_8859_1 },
	{ "cp848",                        CODEC_CP848 },
	{ "cp849",                        CODEC_CP849 },
	{ "cp850",                        CODEC_CP850 },
	{ "cp851",                        CODEC_CP851 },
	{ "cp852",                        CODEC_CP852 },
	{ "cp853",                        CODEC_CP853 },
	{ "cp855",                        CODEC_CP855 },
	{ "cp856",                        CODEC_CP856 },
	{ "cp857",                        CODEC_CP857 },
	{ "cp858",                        CODEC_CP858 },
	{ "cp859",                        CODEC_CP859 },
	{ "cp860",                        CODEC_CP860 },
	{ "cp861",                        CODEC_CP861 },
	{ "cp862",                        CODEC_CP862 },
	{ "cp863",                        CODEC_CP863 },
	{ "cp864",                        CODEC_CP864 },
	{ "cp865",                        CODEC_CP865 },
	{ "cp866",                        CODEC_CP866 },
	{ "cp866nav",                     CODEC_CP866NAV },
	{ "cp866u",                       CODEC_CP1125 },
	{ "cp867",                        CODEC_CP867 },
	{ "cp868",                        CODEC_CP868 },
	{ "cp869",                        CODEC_CP869 },
	{ "cp870",                        CODEC_CP870 },
	{ "cp871",                        CODEC_CP871 },
	{ "cp872",                        CODEC_CP872 },
	{ "cp874",                        CODEC_CP874 },
	{ "cp875",                        CODEC_CP875 },
	{ "cp878",                        CODEC_KOI8_R },
	{ "cp880",                        CODEC_CP880 },
	{ "cp891",                        CODEC_ASCII },
	{ "cp895",                        CODEC_ISO646_JP },
	{ "cp896",                        CODEC_CP896 },
	{ "cp897",                        CODEC_CP897 },
	{ "cp901",                        CODEC_CP901 },
	{ "cp902",                        CODEC_CP902 },
	{ "cp903",                        CODEC_ASCII },
	{ "cp9030",                       CODEC_CP9030 },
	{ "cp904",                        CODEC_CP904 },
	{ "cp905",                        CODEC_CP905 },
	{ "cp9066",                       CODEC_CP9066 },
	{ "cp912",                        CODEC_ISO_8859_2 },
	{ "cp913",                        CODEC_ISO_8859_3 },
	{ "cp914",                        CODEC_ISO_8859_4 },
	{ "cp915",                        CODEC_ISO_8859_5 },
	{ "cp916",                        CODEC_ISO_8859_8 },
	{ "cp918",                        CODEC_CP918 },
	{ "cp919",                        CODEC_ISO_8859_10 },
	{ "cp920",                        CODEC_ISO_8859_9 },
	{ "cp921",                        CODEC_CP921 },
	{ "cp922",                        CODEC_CP922 },
	{ "cp923",                        CODEC_ISO_8859_15 },
	{ "cp9448",                       CODEC_CP1256 },
	{ "cp991",                        CODEC_CP667 },
	{ "cpibm861",                     CODEC_CP861 },
	{ "csa-z243.4-1985-1",            CODEC_ISO646_CA },
	{ "csa-z243.4-1985-2",            CODEC_ISO646_CA2 },
	{ "csa-z243.4-1985-gr",           CODEC_ISO_IR_123 },
	{ "csa-z243.419851",              CODEC_ISO646_CA },
	{ "csa-z243.419852",              CODEC_ISO646_CA2 },
	{ "csa7-1",                       CODEC_ISO646_CA },
	{ "csa7-2",                       CODEC_ISO646_CA2 },
	{ "csa71",                        CODEC_ISO646_CA },
	{ "csa72",                        CODEC_ISO646_CA2 },
	{ "csadobestandardencoding",      CODEC_ADOBE_STANDARD_ENCODING },
	{ "csamiga1251",                  CODEC_AMIGA_1251 },
	{ "csascii",                      CODEC_ASCII },
	{ "csbrf",                        CODEC_BRF },
	{ "csdecmcs",                     CODEC_CP1100 },
	{ "csdkus",                       CODEC_DK_US },
	{ "csebcdicatde",                 CODEC_EBCDIC_AT_DE },
	{ "csebcdicatdea",                CODEC_EBCDIC_AT_DE_A },
	{ "csebcdiccafr",                 CODEC_EBCDIC_CA_FR },
	{ "csebcdicdkno",                 CODEC_EBCDIC_DK_NO },
	{ "csebcdicdknoa",                CODEC_EBCDIC_DK_NO_A },
	{ "csebcdices",                   CODEC_EBCDIC_ES },
	{ "csebcdicesa",                  CODEC_EBCDIC_ES_A },
	{ "csebcdicess",                  CODEC_EBCDIC_ES_S },
	{ "csebcdicfise",                 CODEC_EBCDIC_FI_SE },
	{ "csebcdicfisea",                CODEC_EBCDIC_FI_SE_A },
	{ "csebcdicfr",                   CODEC_EBCDIC_FR },
	{ "csebcdicit",                   CODEC_EBCDIC_IT },
	{ "csebcdicpt",                   CODEC_EBCDIC_PT },
	{ "csebcdicuk",                   CODEC_EBCDIC_UK },
	{ "csebcdicus",                   CODEC_EBCDIC_US },
	{ "cshalfwidthkatakana",          CODEC_X0201 },
	{ "cshppsmath",                   CODEC_ADOBE_SYMBOL_ENCODING },
	{ "cshproman8",                   CODEC_HP_ROMAN8 },
	{ "csibbm904",                    CODEC_CP904 },
	{ "csibm1008",                    CODEC_CP1008 },
	{ "csibm1025",                    CODEC_CP1025 },
	{ "csibm1026",                    CODEC_CP1026 },
	{ "csibm1097",                    CODEC_CP1097 },
	{ "csibm1112",                    CODEC_CP1112 },
	{ "csibm1122",                    CODEC_CP1122 },
	{ "csibm1123",                    CODEC_CP1123 },
	{ "csibm1124",                    CODEC_CP1124 },
	{ "csibm1129",                    CODEC_CP1129 },
	{ "csibm1130",                    CODEC_CP1130 },
	{ "csibm1132",                    CODEC_CP1132 },
	{ "csibm1133",                    CODEC_CP1133 },
	{ "csibm1137",                    CODEC_CP1137 },
	{ "csibm1140",                    CODEC_CP1140 },
	{ "csibm1141",                    CODEC_CP1141 },
	{ "csibm1142",                    CODEC_CP1142 },
	{ "csibm1143",                    CODEC_CP1143 },
	{ "csibm1144",                    CODEC_CP1144 },
	{ "csibm1145",                    CODEC_CP1145 },
	{ "csibm1146",                    CODEC_CP1146 },
	{ "csibm1147",                    CODEC_CP1147 },
	{ "csibm1148",                    CODEC_CP1148 },
	{ "csibm1149",                    CODEC_CP1149 },
	{ "csibm1153",                    CODEC_CP1153 },
	{ "csibm1154",                    CODEC_CP1154 },
	{ "csibm1155",                    CODEC_CP1155 },
	{ "csibm1156",                    CODEC_CP1156 },
	{ "csibm1157",                    CODEC_CP1157 },
	{ "csibm1158",                    CODEC_CP1158 },
	{ "csibm1160",                    CODEC_CP1160 },
	{ "csibm1161",                    CODEC_CP1161 },
	{ "csibm11621162",                CODEC_CP1162 },
	{ "csibm1163",                    CODEC_CP1163 },
	{ "csibm1164",                    CODEC_CP1164 },
	{ "csibm1166",                    CODEC_CP1166 },
	{ "csibm1167",                    CODEC_KOI8_RU },
	{ "csibm12712",                   CODEC_CP12712 },
	{ "csibm16804",                   CODEC_CP16804 },
	{ "csibm273",                     CODEC_CP273 },
	{ "csibm274",                     CODEC_CP274 },
	{ "csibm275",                     CODEC_CP275 },
	{ "csibm277",                     CODEC_EBCDIC_CP_DK_NO },
	{ "csibm278",                     CODEC_CP278 },
	{ "csibm280",                     CODEC_CP280 },
	{ "csibm281",                     CODEC_CP281 },
	{ "csibm284",                     CODEC_CP284 },
	{ "csibm285",                     CODEC_CP285 },
	{ "csibm290",                     CODEC_CP290 },
	{ "csibm297",                     CODEC_CP297 },
	{ "csibm37",                      CODEC_CP37 },
	{ "csibm38",                      CODEC_CP38 },
	{ "csibm420",                     CODEC_CP420 },
	{ "csibm423",                     CODEC_CP423 },
	{ "csibm424",                     CODEC_CP424 },
	{ "csibm4517",                    CODEC_CP4517 },
	{ "csibm4899",                    CODEC_CP4899 },
	{ "csibm4909",                    CODEC_CP4909 },
	{ "csibm4971",                    CODEC_CP4971 },
	{ "csibm500",                     CODEC_CP500 },
	{ "csibm5347",                    CODEC_CP5347 },
	{ "csibm803",                     CODEC_CP803 },
	{ "csibm851",                     CODEC_CP851 },
	{ "csibm855",                     CODEC_CP855 },
	{ "csibm856",                     CODEC_CP856 },
	{ "csibm857",                     CODEC_CP857 },
	{ "csibm858",                     CODEC_CP858 },
	{ "csibm860",                     CODEC_CP860 },
	{ "csibm861",                     CODEC_CP861 },
	{ "csibm863",                     CODEC_CP863 },
	{ "csibm864",                     CODEC_CP864 },
	{ "csibm865",                     CODEC_CP865 },
	{ "csibm866",                     CODEC_CP866 },
	{ "csibm868",                     CODEC_CP868 },
	{ "csibm869",                     CODEC_CP869 },
	{ "csibm870",                     CODEC_CP870 },
	{ "csibm871",                     CODEC_CP871 },
	{ "csibm880",                     CODEC_CP880 },
	{ "csibm891",                     CODEC_ASCII },
	{ "csibm901",                     CODEC_CP901 },
	{ "csibm902",                     CODEC_CP902 },
	{ "csibm903",                     CODEC_ASCII },
	{ "csibm9030",                    CODEC_CP9030 },
	{ "csibm904",                     CODEC_CP904 },
	{ "csibm905",                     CODEC_CP905 },
	{ "csibm9066",                    CODEC_CP9066 },
	{ "csibm918",                     CODEC_CP918 },
	{ "csibm921",                     CODEC_CP921 },
	{ "csibm922",                     CODEC_CP922 },
	{ "csibm9448",                    CODEC_CP1256 },
	{ "csibmebcdicatde",              CODEC_EBCDIC_AT_DE },
	{ "csiso102t617bit",              CODEC_ISO646_T_61 },
	{ "csiso10367box",                CODEC_ISO_IR_155 },
	{ "csiso103t618bit",              CODEC_CP1036 },
	{ "csiso10swedish",               CODEC_ISO646_SE },
	{ "csiso111ecmacyrillic",         CODEC_KOI8_E },
	{ "csiso11swedishfornames",       CODEC_ISO646_SE2 },
	{ "csiso121canadian1",            CODEC_ISO646_CA },
	{ "csiso122canadian2",            CODEC_ISO646_CA2 },
	{ "csiso123csaz24341985gr",       CODEC_ISO_IR_123 },
	{ "csiso139csn369103",            CODEC_ISO_IR_139 },
	{ "csiso13jisc6220jp",            CODEC_ISO_IR_13 },
	{ "csiso141jusib1002",            CODEC_ISO646_YU },
	{ "csiso143iecp271",              CODEC_ISO_IR_143 },
	{ "csiso146serbian",              CODEC_ISO_IR_146 },
	{ "csiso147macedonian",           CODEC_ISO_IR_147 },
	{ "csiso14jisc6220ro",            CODEC_ISO646_JP },
	{ "csiso150",                     CODEC_ISO_IR_150 },
	{ "csiso150greekccitt",           CODEC_ISO_IR_150 },
	{ "csiso151cuba",                 CODEC_ISO646_CU },
	{ "csiso153gost1976874",          CODEC_ISO_IR_153 },
	{ "csiso158lap",                  CODEC_ISO_IR_158 },
	{ "csiso15italian",               CODEC_ISO646_IT },
	{ "csiso16portugese",             CODEC_ISO646_PT },
	{ "csiso16portuguese",            CODEC_ISO646_PT },
	{ "csiso17spanish",               CODEC_ISO646_ES },
	{ "csiso18greek7old",             CODEC_ISO_IR_18 },
	{ "csiso19latingreek",            CODEC_ISO_IR_19 },
	{ "csiso2033",                    CODEC_ISO_IR_98 },
	{ "csiso21german",                CODEC_ISO646_DE },
	{ "csiso25french",                CODEC_ISO646_FR1 },
	{ "csiso27latingreek1",           CODEC_ISO646_LATIN_GR_MIXED },
	{ "csiso2intlrefversion",         CODEC_ISO_IR_2 },
	{ "csiso47bsviewdata",            CODEC_ISO646_VIEWDATA },
	{ "csiso49inis",                  CODEC_ISO646_INIS_SUBSET },
	{ "csiso4unitedkingdom",          CODEC_ISO646_GB },
	{ "csiso50inis8",                 CODEC_ISO_IR_50 },
	{ "csiso51iniscyrillic",          CODEC_ISO_IR_51 },
	{ "csiso54271981",                CODEC_ISO_IR_54 },
	{ "csiso5427cyrillic",            CODEC_ISO_5427 },
	{ "csiso5427cyrillic1981",        CODEC_ISO_IR_54 },
	{ "csiso5428greek",               CODEC_ISO_IR_55 },
	{ "csiso57gb1988",                CODEC_ISO646_CN },
	{ "csiso58gb1988",                CODEC_ISO646_CN },
	{ "csiso60danishnorwegian",       CODEC_ISO646_NO },
	{ "csiso60norwegian1",            CODEC_ISO646_NO },
	{ "csiso61norwegian2",            CODEC_ISO646_NO2 },
	{ "csiso646danish",               CODEC_ISO646_DK },
	{ "csiso6937add",                 CODEC_ISO_IR_152 },
	{ "csiso69french",                CODEC_ISO646_FR },
	{ "csiso84portuguese2",           CODEC_ISO646_PT2 },
	{ "csiso85spanish2",              CODEC_ISO646_ES2 },
	{ "csiso86hungarian",             CODEC_ISO646_HU },
	{ "csiso885913",                  CODEC_CP921 },
	{ "csiso885914",                  CODEC_ISO_8859_14 },
	{ "csiso885915",                  CODEC_ISO_8859_15 },
	{ "csiso885916",                  CODEC_ISO_8859_16 },
	{ "csiso8859supp",                CODEC_ISO_IR_154 },
	{ "csiso88greek7",                CODEC_ISO_IR_88 },
	{ "csiso90",                      CODEC_ISO_6937_2 },
	{ "csiso91jisc62291984a",         CODEC_ISO_IR_91 },
	{ "csiso92jisc62991984b",         CODEC_ISO646_JP_OCR_B },
	{ "csiso93jis62291984badd",       CODEC_ISO_IR_93 },
	{ "csiso94jis62291984hand",       CODEC_ISO_IR_94 },
	{ "csiso95jis62291984handadd",    CODEC_ISO_IR_95 },
	{ "csiso96jisc62291984kana",      CODEC_ISO_IR_96 },
	{ "csisolatin1",                  CODEC_ISO_8859_1 },
	{ "csisolatin2",                  CODEC_ISO_8859_2 },
	{ "csisolatin3",                  CODEC_ISO_8859_3 },
	{ "csisolatin4",                  CODEC_ISO_8859_4 },
	{ "csisolatin5",                  CODEC_ISO_8859_9 },
	{ "csisolatin6",                  CODEC_ISO_8859_10 },
	{ "csisolatin7",                  CODEC_CP921 },
	{ "csisolatinarabic",             CODEC_ISO_8859_6 },
	{ "csisolatincyrillic",           CODEC_ISO_8859_5 },
	{ "csisolatingreek",              CODEC_ISO_8859_7 },
	{ "csisolatinhebrew",             CODEC_ISO_8859_8 },
	{ "cskoi8r",                      CODEC_KOI8_R },
	{ "cskoi8u",                      CODEC_KOI8_U },
	{ "csksc5636",                    CODEC_ISO646_KR },
	{ "cskz1048",                     CODEC_KZ_1048 },
	{ "csmacintosh",                  CODEC_CP1275 },
	{ "csn-369103",                   CODEC_ISO_IR_139 },
	{ "csnatsdano",                   CODEC_ISO646_NATS_DANO },
	{ "csnatssefi",                   CODEC_ISO_IR_8_1 },
	{ "csosdebcdicdf3irv",            CODEC_OSD_EBCDIC_DF03_IRV },
	{ "csosdebcdicdf41",              CODEC_OSD_EBCDIC_DF04_1 },
	{ "csosdebcdicdf415",             CODEC_OSD_EBCDIC_DF04_15 },
	{ "cspc775baltic",                CODEC_CP775 },
	{ "cspc850multilingual",          CODEC_CP850 },
	{ "cspc858multilingual",          CODEC_CP858 },
	{ "cspc862latinhebrew",           CODEC_CP862 },
	{ "cspc8codepage437",             CODEC_CP437 },
	{ "cspcp852",                     CODEC_CP852 },
	{ "csptcp154",                    CODEC_PT154 },
	{ "cstis620",                     CODEC_ISO_8859_11 },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "csucs4",                       CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "csucs4",                       CODEC_UTF32LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "csunicode",                    CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "csunicode",                    CODEC_UTF16LE },
#endif /* ... */
	{ "csusdk",                       CODEC_US_DK },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "csutf16",                      CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "csutf16",                      CODEC_UTF16LE },
#endif /* ... */
	{ "csutf16be",                    CODEC_UTF16BE },
	{ "csutf16le",                    CODEC_UTF16LE },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "csutf32",                      CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "csutf32",                      CODEC_UTF32LE },
#endif /* ... */
	{ "csutf32be",                    CODEC_UTF32BE },
	{ "csutf32le",                    CODEC_UTF32LE },
	{ "csutf8",                       CODEC_UTF8 },
	{ "csventurainternational",       CODEC_VENTURA_INTERNATIONAL },
	{ "csventuraus",                  CODEC_VENTURA_US },
	{ "cswindows1250",                CODEC_CP1250 },
	{ "cswindows1251",                CODEC_CP1251 },
	{ "cswindows1252",                CODEC_CP1252 },
	{ "cswindows1253",                CODEC_CP1253 },
	{ "cswindows1254",                CODEC_CP1254 },
	{ "cswindows1255",                CODEC_CP1255 },
	{ "cswindows1256",                CODEC_CP1256 },
	{ "cswindows1257",                CODEC_CP1257 },
	{ "cswindows1258",                CODEC_CP1258 },
	{ "cswindows874",                 CODEC_CP874 },
	{ "cuba",                         CODEC_ISO646_CU },
	{ "cwi",                          CODEC_CWI },
	{ "cwi-2",                        CODEC_CWI },
	{ "cyrillic",                     CODEC_ISO_8859_5 },
	{ "cyrillic-asian",               CODEC_PT154 },
	{ "d7dec",                        CODEC_ISO646_DE },
	{ "de",                           CODEC_ISO646_DE },
	{ "dec",                          CODEC_CP1100 },
	{ "dec-greek",                    CODEC_CP1287 },
	{ "dec-greek-(8-bit)",            CODEC_CP1287 },
	{ "dec-greek-8",                  CODEC_CP1287 },
	{ "dec-greek-8-bit",              CODEC_CP1287 },
	{ "dec-mcs",                      CODEC_CP1100 },
	{ "dec-special-graphics",         CODEC_CP1090 },
	{ "dec-turkish",                  CODEC_CP1288 },
	{ "dec-turkish-(8-bit)",          CODEC_CP1288 },
	{ "dec-turkish-8",                CODEC_CP1288 },
	{ "dec-turkish-8-bit",            CODEC_CP1288 },
	{ "decmcs",                       CODEC_CP1100 },
	{ "din-66003",                    CODEC_ISO646_DE },
	{ "din-66303",                    CODEC_DIN_66303 },
	{ "dk",                           CODEC_ISO646_DK },
	{ "dk-us",                        CODEC_DK_US },
	{ "dos-895",                      CODEC_KEYBCS2 },
	{ "drv8",                         CODEC_DIN_66303 },
	{ "ds-2089",                      CODEC_ISO646_DK },
	{ "ds2089",                       CODEC_ISO646_DK },
	{ "e13b",                         CODEC_ISO_IR_98 },
	{ "e7dec",                        CODEC_ISO646_ES },
	{ "ebcdic-at-de",                 CODEC_EBCDIC_AT_DE },
	{ "ebcdic-at-de-a",               CODEC_EBCDIC_AT_DE_A },
	{ "ebcdic-be",                    CODEC_CP274 },
	{ "ebcdic-br",                    CODEC_CP275 },
	{ "ebcdic-ca-fr",                 CODEC_EBCDIC_CA_FR },
	{ "ebcdic-cp-ar1",                CODEC_CP420 },
	{ "ebcdic-cp-ar2",                CODEC_CP918 },
	{ "ebcdic-cp-be",                 CODEC_CP500 },
	{ "ebcdic-cp-ca",                 CODEC_CP37 },
	{ "ebcdic-cp-ch",                 CODEC_CP500 },
	{ "ebcdic-cp-dk",                 CODEC_EBCDIC_CP_DK_NO },
	{ "ebcdic-cp-es",                 CODEC_CP284 },
	{ "ebcdic-cp-fi",                 CODEC_CP278 },
	{ "ebcdic-cp-fr",                 CODEC_CP297 },
	{ "ebcdic-cp-gb",                 CODEC_CP285 },
	{ "ebcdic-cp-gr",                 CODEC_CP423 },
	{ "ebcdic-cp-he",                 CODEC_CP424 },
	{ "ebcdic-cp-is",                 CODEC_CP871 },
	{ "ebcdic-cp-it",                 CODEC_CP280 },
	{ "ebcdic-cp-nl",                 CODEC_CP37 },
	{ "ebcdic-cp-no",                 CODEC_EBCDIC_CP_DK_NO },
	{ "ebcdic-cp-roece",              CODEC_CP870 },
	{ "ebcdic-cp-se",                 CODEC_CP278 },
	{ "ebcdic-cp-tr",                 CODEC_CP905 },
	{ "ebcdic-cp-us",                 CODEC_CP37 },
	{ "ebcdic-cp-wt",                 CODEC_CP37 },
	{ "ebcdic-cp-yu",                 CODEC_CP870 },
	{ "ebcdic-cyrillic",              CODEC_CP880 },
	{ "ebcdic-dk-no",                 CODEC_EBCDIC_DK_NO },
	{ "ebcdic-dk-no-a",               CODEC_EBCDIC_DK_NO_A },
	{ "ebcdic-es",                    CODEC_EBCDIC_ES },
	{ "ebcdic-es-a",                  CODEC_EBCDIC_ES_A },
	{ "ebcdic-es-s",                  CODEC_EBCDIC_ES_S },
	{ "ebcdic-fi-se",                 CODEC_EBCDIC_FI_SE },
	{ "ebcdic-fi-se-a",               CODEC_EBCDIC_FI_SE_A },
	{ "ebcdic-fr",                    CODEC_EBCDIC_FR },
	{ "ebcdic-greek",                 CODEC_CP875 },
	{ "ebcdic-int",                   CODEC_CP38 },
	{ "ebcdic-int1",                  CODEC_IBM256 },
	{ "ebcdic-is-friss",              CODEC_EBCDIC_IS_FRISS },
	{ "ebcdic-it",                    CODEC_EBCDIC_IT },
	{ "ebcdic-jp-e",                  CODEC_CP281 },
	{ "ebcdic-jp-kana",               CODEC_CP290 },
	{ "ebcdic-pt",                    CODEC_EBCDIC_PT },
	{ "ebcdic-uk",                    CODEC_EBCDIC_UK },
	{ "ebcdic-us",                    CODEC_EBCDIC_US },
	{ "ebcdicatde",                   CODEC_EBCDIC_AT_DE },
	{ "ebcdicatdea",                  CODEC_EBCDIC_AT_DE_A },
	{ "ebcdiccafr",                   CODEC_EBCDIC_CA_FR },
	{ "ebcdicdkno",                   CODEC_EBCDIC_DK_NO },
	{ "ebcdicdknoa",                  CODEC_EBCDIC_DK_NO_A },
	{ "ebcdices",                     CODEC_EBCDIC_ES },
	{ "ebcdicesa",                    CODEC_EBCDIC_ES_A },
	{ "ebcdicfise",                   CODEC_EBCDIC_FI_SE },
	{ "ebcdicfisea",                  CODEC_EBCDIC_FI_SE_A },
	{ "ebcdicfr",                     CODEC_EBCDIC_FR },
	{ "ebcdicisfriss",                CODEC_EBCDIC_IS_FRISS },
	{ "ebcdicit",                     CODEC_EBCDIC_IT },
	{ "ebcdicpt",                     CODEC_EBCDIC_PT },
	{ "ebcdicuk",                     CODEC_EBCDIC_UK },
	{ "ebcdicus",                     CODEC_EBCDIC_US },
	{ "ecma-113",                     CODEC_KOI8_E },
	{ "ecma-114",                     CODEC_ISO_8859_6 },
	{ "ecma-118",                     CODEC_ISO_8859_7 },
	{ "ecma-128",                     CODEC_ISO_8859_9 },
	{ "ecma-cyrillic",                CODEC_KOI8_E },
	{ "ecmacyrillic",                 CODEC_KOI8_E },
	{ "el8dec",                       CODEC_CP1287 },
	{ "elot-928",                     CODEC_ISO_8859_7 },
	{ "es",                           CODEC_ISO646_ES },
	{ "es2",                          CODEC_ISO646_ES2 },
	{ "estonia-iso-8",                CODEC_CP922 },
	{ "extended-latin-8",             CODEC_EXTENDED_LATIN_8 },
	{ "f7dec",                        CODEC_ISO646_FR1 },
	{ "fi",                           CODEC_ISO646_SE },
	{ "fr",                           CODEC_ISO646_FR },
	{ "gb",                           CODEC_ISO646_GB },
	{ "gb-1988-80",                   CODEC_ISO646_CN },
	{ "gb-198880",                    CODEC_ISO646_CN },
	{ "gbcd",                         CODEC_GBCD },
	{ "georgian-academy",             CODEC_GEORGIAN_ACADEMY },
	{ "georgian-ps",                  CODEC_GEORGIAN_PS },
	{ "german",                       CODEC_ISO646_DE },
	{ "gost-19768",                   CODEC_ISO_IR_153 },
	{ "gost-19768-74",                CODEC_ISO_IR_153 },
	{ "gost-1976874",                 CODEC_ISO_IR_153 },
	{ "greek",                        CODEC_ISO_8859_7 },
	{ "greek-ccitt",                  CODEC_ISO_IR_150 },
	{ "greek7",                       CODEC_ISO_IR_88 },
	{ "greek7-old",                   CODEC_ISO_IR_18 },
	{ "greek7old",                    CODEC_ISO_IR_18 },
	{ "greek8",                       CODEC_ISO_8859_7 },
	{ "greekccitt",                   CODEC_ISO_IR_150 },
	{ "hebrew",                       CODEC_ISO_8859_8 },
	{ "hp-greek8",                    CODEC_HP_GREEK8 },
	{ "hp-pc-8",                      CODEC_CP1057 },
	{ "hp-roman-8",                   CODEC_HP_ROMAN8 },
	{ "hp-roman8",                    CODEC_HP_ROMAN8 },
	{ "hp-roman9",                    CODEC_HP_ROMAN9 },
	{ "hp-thai8",                     CODEC_HP_THAI8 },
	{ "hp-turkish8",                  CODEC_HP_TURKISH8 },
	{ "hpgreek8",                     CODEC_HP_GREEK8 },
	{ "hproman8",                     CODEC_HP_ROMAN8 },
	{ "hproman9",                     CODEC_HP_ROMAN9 },
	{ "hpthai8",                      CODEC_HP_THAI8 },
	{ "hpturkish8",                   CODEC_HP_TURKISH8 },
	{ "hu",                           CODEC_ISO646_HU },
	{ "i7dec",                        CODEC_ISO646_IT },
	{ "ibm1004",                      CODEC_CP1004 },
	{ "ibm1006",                      CODEC_CP1006 },
	{ "ibm1008",                      CODEC_CP1008 },
	{ "ibm1009",                      CODEC_ISO646_IRV_1983 },
	{ "ibm1010",                      CODEC_ISO646_FR },
	{ "ibm1011",                      CODEC_ISO646_DE },
	{ "ibm1012",                      CODEC_ISO646_IT },
	{ "ibm1013",                      CODEC_ISO646_GB },
	{ "ibm1014",                      CODEC_ISO646_ES2 },
	{ "ibm1015",                      CODEC_ISO646_PT2 },
	{ "ibm1016",                      CODEC_ISO646_NATS_DANO },
	{ "ibm1017",                      CODEC_ISO646_DK },
	{ "ibm1018",                      CODEC_ISO646_SE },
	{ "ibm1019",                      CODEC_ISO646_NL },
	{ "ibm1021",                      CODEC_ISO646_SWI_NRCS },
	{ "ibm1025",                      CODEC_CP1025 },
	{ "ibm1026",                      CODEC_CP1026 },
	{ "ibm1036",                      CODEC_CP1036 },
	{ "ibm1038",                      CODEC_CP1038 },
	{ "ibm1046",                      CODEC_CP1046 },
	{ "ibm1047",                      CODEC_CP1047 },
	{ "ibm1050",                      CODEC_HP_ROMAN8 },
	{ "ibm1051",                      CODEC_HP_ROMAN8 },
	{ "ibm1089",                      CODEC_ISO_8859_6 },
	{ "ibm1090",                      CODEC_CP1090 },
	{ "ibm1097",                      CODEC_CP1097 },
	{ "ibm1098",                      CODEC_CP1098 },
	{ "ibm1100",                      CODEC_CP1100 },
	{ "ibm1101",                      CODEC_ISO646_GB_NRCS },
	{ "ibm1102",                      CODEC_ISO646_NL_NRCS },
	{ "ibm1103",                      CODEC_ISO646_FI_NRCS },
	{ "ibm1105",                      CODEC_ISO646_DK_NO_NRCS },
	{ "ibm1106",                      CODEC_ISO646_SE_NRCS },
	{ "ibm1107",                      CODEC_ISO646_DK_NO_ALT_NRCS },
	{ "ibm1111",                      CODEC_ISO_8859_2 },
	{ "ibm1112",                      CODEC_CP1112 },
	{ "ibm1116",                      CODEC_CP1116 },
	{ "ibm1117",                      CODEC_CP1117 },
	{ "ibm1118",                      CODEC_CP774 },
	{ "ibm1122",                      CODEC_CP1122 },
	{ "ibm1123",                      CODEC_CP1123 },
	{ "ibm1124",                      CODEC_CP1124 },
	{ "ibm1129",                      CODEC_CP1129 },
	{ "ibm1130",                      CODEC_CP1130 },
	{ "ibm1131",                      CODEC_CP1131 },
	{ "ibm1132",                      CODEC_CP1132 },
	{ "ibm1133",                      CODEC_CP1133 },
	{ "ibm1137",                      CODEC_CP1137 },
	{ "ibm1140",                      CODEC_CP1140 },
	{ "ibm1141",                      CODEC_CP1141 },
	{ "ibm1142",                      CODEC_CP1142 },
	{ "ibm1143",                      CODEC_CP1143 },
	{ "ibm1144",                      CODEC_CP1144 },
	{ "ibm1145",                      CODEC_CP1145 },
	{ "ibm1146",                      CODEC_CP1146 },
	{ "ibm1147",                      CODEC_CP1147 },
	{ "ibm1148",                      CODEC_CP1148 },
	{ "ibm1149",                      CODEC_CP1149 },
	{ "ibm1153",                      CODEC_CP1153 },
	{ "ibm1154",                      CODEC_CP1154 },
	{ "ibm1155",                      CODEC_CP1155 },
	{ "ibm1156",                      CODEC_CP1156 },
	{ "ibm1157",                      CODEC_CP1157 },
	{ "ibm1158",                      CODEC_CP1158 },
	{ "ibm1160",                      CODEC_CP1160 },
	{ "ibm1161",                      CODEC_CP1161 },
	{ "ibm1162",                      CODEC_CP1162 },
	{ "ibm1163",                      CODEC_CP1163 },
	{ "ibm1164",                      CODEC_CP1164 },
	{ "ibm1166",                      CODEC_CP1166 },
	{ "ibm1167",                      CODEC_KOI8_RU },
	{ "ibm1168",                      CODEC_KOI8_U },
	{ "ibm12712",                     CODEC_CP12712 },
	{ "ibm1275",                      CODEC_CP1275 },
	{ "ibm1281",                      CODEC_CP1281 },
	{ "ibm1282",                      CODEC_CP1282 },
	{ "ibm1283",                      CODEC_CP10007 },
	{ "ibm1284",                      CODEC_CP1284 },
	{ "ibm1285",                      CODEC_CP1285 },
	{ "ibm1286",                      CODEC_CP1286 },
	{ "ibm1401",                      CODEC_IBM1401 },
	{ "ibm16804",                     CODEC_CP16804 },
	{ "ibm256",                       CODEC_IBM256 },
	{ "ibm273",                       CODEC_CP273 },
	{ "ibm274",                       CODEC_CP274 },
	{ "ibm275",                       CODEC_CP275 },
	{ "ibm277",                       CODEC_EBCDIC_CP_DK_NO },
	{ "ibm278",                       CODEC_CP278 },
	{ "ibm280",                       CODEC_CP280 },
	{ "ibm281",                       CODEC_CP281 },
	{ "ibm284",                       CODEC_CP284 },
	{ "ibm285",                       CODEC_CP285 },
	{ "ibm290",                       CODEC_CP290 },
	{ "ibm297",                       CODEC_CP297 },
	{ "ibm367",                       CODEC_ASCII },
	{ "ibm37",                        CODEC_CP37 },
	{ "ibm38",                        CODEC_CP38 },
	{ "ibm420",                       CODEC_CP420 },
	{ "ibm423",                       CODEC_CP423 },
	{ "ibm424",                       CODEC_CP424 },
	{ "ibm437",                       CODEC_CP437 },
	{ "ibm4517",                      CODEC_CP4517 },
	{ "ibm4899",                      CODEC_CP4899 },
	{ "ibm4909",                      CODEC_CP4909 },
	{ "ibm4971",                      CODEC_CP4971 },
	{ "ibm500",                       CODEC_CP500 },
	{ "ibm5104",                      CODEC_CP1008 },
	{ "ibm5347",                      CODEC_CP5347 },
	{ "ibm704",                       CODEC_IBM704 },
	{ "ibm708",                       CODEC_CP708 },
	{ "ibm7090",                      CODEC_IBM7090 },
	{ "ibm7094",                      CODEC_IBM7090 },
	{ "ibm720",                       CODEC_CP720 },
	{ "ibm737",                       CODEC_CP737 },
	{ "ibm775",                       CODEC_CP775 },
	{ "ibm803",                       CODEC_CP803 },
	{ "ibm806",                       CODEC_CP806 },
	{ "ibm813",                       CODEC_ISO_8859_7 },
	{ "ibm819",                       CODEC_ISO_8859_1 },
	{ "ibm848",                       CODEC_CP1125 },
	{ "ibm850",                       CODEC_CP850 },
	{ "ibm851",                       CODEC_CP851 },
	{ "ibm852",                       CODEC_CP852 },
	{ "ibm853",                       CODEC_CP853 },
	{ "ibm855",                       CODEC_CP855 },
	{ "ibm856",                       CODEC_CP856 },
	{ "ibm857",                       CODEC_CP857 },
	{ "ibm858",                       CODEC_CP858 },
	{ "ibm859",                       CODEC_CP859 },
	{ "ibm860",                       CODEC_CP860 },
	{ "ibm861",                       CODEC_CP861 },
	{ "ibm862",                       CODEC_CP862 },
	{ "ibm863",                       CODEC_CP863 },
	{ "ibm864",                       CODEC_CP864 },
	{ "ibm865",                       CODEC_CP865 },
	{ "ibm866",                       CODEC_CP866 },
	{ "ibm866nav",                    CODEC_CP866NAV },
	{ "ibm868",                       CODEC_CP868 },
	{ "ibm869",                       CODEC_CP869 },
	{ "ibm870",                       CODEC_CP870 },
	{ "ibm871",                       CODEC_CP871 },
	{ "ibm874",                       CODEC_CP874 },
	{ "ibm875",                       CODEC_CP875 },
	{ "ibm878",                       CODEC_KOI8_R },
	{ "ibm880",                       CODEC_CP880 },
	{ "ibm891",                       CODEC_ASCII },
	{ "ibm895",                       CODEC_ISO646_JP },
	{ "ibm896",                       CODEC_CP896 },
	{ "ibm901",                       CODEC_CP901 },
	{ "ibm902",                       CODEC_CP902 },
	{ "ibm903",                       CODEC_ASCII },
	{ "ibm9030",                      CODEC_CP9030 },
	{ "ibm904",                       CODEC_CP904 },
	{ "ibm905",                       CODEC_CP905 },
	{ "ibm9066",                      CODEC_CP9066 },
	{ "ibm912",                       CODEC_ISO_8859_2 },
	{ "ibm913",                       CODEC_ISO_8859_3 },
	{ "ibm914",                       CODEC_ISO_8859_4 },
	{ "ibm915",                       CODEC_ISO_8859_5 },
	{ "ibm916",                       CODEC_ISO_8859_8 },
	{ "ibm918",                       CODEC_CP918 },
	{ "ibm919",                       CODEC_ISO_8859_10 },
	{ "ibm920",                       CODEC_ISO_8859_9 },
	{ "ibm921",                       CODEC_CP921 },
	{ "ibm922",                       CODEC_CP922 },
	{ "ibm923",                       CODEC_ISO_8859_15 },
	{ "ibm9448",                      CODEC_CP1256 },
	{ "iec-p27-1",                    CODEC_ISO_IR_143 },
	{ "iec-p271",                     CODEC_ISO_IR_143 },
	{ "inis",                         CODEC_ISO646_INIS_SUBSET },
	{ "inis-8",                       CODEC_ISO_IR_50 },
	{ "inis-cyrillic",                CODEC_ISO_IR_51 },
	{ "inis8",                        CODEC_ISO_IR_50 },
	{ "iniscyrillic",                 CODEC_ISO_IR_51 },
	{ "invariant",                    CODEC_ISO646_INV },
	{ "irv",                          CODEC_ISO_IR_2 },
	{ "isiri-3342",                   CODEC_ISIRI3342 },
	{ "isiri3342",                    CODEC_ISIRI3342 },
	{ "iso-celtic",                   CODEC_ISO_8859_14 },
	{ "iso-ir-10",                    CODEC_ISO646_SE },
	{ "iso-ir-100",                   CODEC_ISO_8859_1 },
	{ "iso-ir-101",                   CODEC_ISO_8859_2 },
	{ "iso-ir-102",                   CODEC_ISO646_T_61 },
	{ "iso-ir-103",                   CODEC_CP1036 },
	{ "iso-ir-109",                   CODEC_ISO_8859_3 },
	{ "iso-ir-11",                    CODEC_ISO646_SE2 },
	{ "iso-ir-110",                   CODEC_ISO_8859_4 },
	{ "iso-ir-111",                   CODEC_KOI8_E },
	{ "iso-ir-121",                   CODEC_ISO646_CA },
	{ "iso-ir-122",                   CODEC_ISO646_CA2 },
	{ "iso-ir-123",                   CODEC_ISO_IR_123 },
	{ "iso-ir-126",                   CODEC_ISO_8859_7 },
	{ "iso-ir-127",                   CODEC_ISO_8859_6 },
	{ "iso-ir-13",                    CODEC_ISO_IR_13 },
	{ "iso-ir-138",                   CODEC_ISO_8859_8 },
	{ "iso-ir-139",                   CODEC_ISO_IR_139 },
	{ "iso-ir-14",                    CODEC_ISO646_JP },
	{ "iso-ir-141",                   CODEC_ISO646_YU },
	{ "iso-ir-143",                   CODEC_ISO_IR_143 },
	{ "iso-ir-144",                   CODEC_ISO_8859_5 },
	{ "iso-ir-146",                   CODEC_ISO_IR_146 },
	{ "iso-ir-147",                   CODEC_ISO_IR_147 },
	{ "iso-ir-148",                   CODEC_ISO_8859_9 },
	{ "iso-ir-15",                    CODEC_ISO646_IT },
	{ "iso-ir-150",                   CODEC_ISO_IR_150 },
	{ "iso-ir-151",                   CODEC_ISO646_CU },
	{ "iso-ir-152",                   CODEC_ISO_IR_152 },
	{ "iso-ir-153",                   CODEC_ISO_IR_153 },
	{ "iso-ir-154",                   CODEC_ISO_IR_154 },
	{ "iso-ir-155",                   CODEC_ISO_IR_155 },
	{ "iso-ir-156",                   CODEC_CP20269 },
	{ "iso-ir-157",                   CODEC_ISO_8859_10 },
	{ "iso-ir-158",                   CODEC_ISO_IR_158 },
	{ "iso-ir-16",                    CODEC_ISO646_PT },
	{ "iso-ir-166",                   CODEC_ISO_8859_11 },
	{ "iso-ir-17",                    CODEC_ISO646_ES },
	{ "iso-ir-170",                   CODEC_ISO646_INV },
	{ "iso-ir-179",                   CODEC_CP921 },
	{ "iso-ir-18",                    CODEC_ISO_IR_18 },
	{ "iso-ir-182",                   CODEC_ISO_IR_182 },
	{ "iso-ir-19",                    CODEC_ISO_IR_19 },
	{ "iso-ir-193",                   CODEC_UTF8 },
	{ "iso-ir-197",                   CODEC_ISO_IR_197 },
	{ "iso-ir-199",                   CODEC_ISO_8859_14 },
	{ "iso-ir-2",                     CODEC_ISO_IR_2 },
	{ "iso-ir-200",                   CODEC_ISO_IR_200 },
	{ "iso-ir-201",                   CODEC_ISO_IR_201 },
	{ "iso-ir-203",                   CODEC_ISO_8859_15 },
	{ "iso-ir-206",                   CODEC_CP901 },
	{ "iso-ir-207",                   CODEC_ISO646_IE },
	{ "iso-ir-209",                   CODEC_ISO_IR_209 },
	{ "iso-ir-21",                    CODEC_ISO646_DE },
	{ "iso-ir-226",                   CODEC_ISO_8859_16 },
	{ "iso-ir-25",                    CODEC_ISO646_FR1 },
	{ "iso-ir-27",                    CODEC_ISO646_LATIN_GR_MIXED },
	{ "iso-ir-37",                    CODEC_ISO_5427 },
	{ "iso-ir-4",                     CODEC_ISO646_GB },
	{ "iso-ir-47",                    CODEC_ISO646_VIEWDATA },
	{ "iso-ir-49",                    CODEC_ISO646_INIS_SUBSET },
	{ "iso-ir-50",                    CODEC_ISO_IR_50 },
	{ "iso-ir-51",                    CODEC_ISO_IR_51 },
	{ "iso-ir-54",                    CODEC_ISO_IR_54 },
	{ "iso-ir-55",                    CODEC_ISO_IR_55 },
	{ "iso-ir-57",                    CODEC_ISO646_CN },
	{ "iso-ir-6",                     CODEC_ASCII },
	{ "iso-ir-60",                    CODEC_ISO646_NO },
	{ "iso-ir-61",                    CODEC_ISO646_NO2 },
	{ "iso-ir-68",                    CODEC_ISO_IR_68 },
	{ "iso-ir-69",                    CODEC_ISO646_FR },
	{ "iso-ir-8",                     CODEC_ISO646_SEFI_NATS },
	{ "iso-ir-8-1",                   CODEC_ISO_IR_8_1 },
	{ "iso-ir-8-2",                   CODEC_ISO_IR_8_2 },
	{ "iso-ir-84",                    CODEC_ISO646_PT2 },
	{ "iso-ir-85",                    CODEC_ISO646_ES2 },
	{ "iso-ir-86",                    CODEC_ISO646_HU },
	{ "iso-ir-88",                    CODEC_ISO_IR_88 },
	{ "iso-ir-89",                    CODEC_ISO_IR_89 },
	{ "iso-ir-9-1",                   CODEC_ISO646_NATS_DANO },
	{ "iso-ir-9-2",                   CODEC_ISO_IR_9_2 },
	{ "iso-ir-90",                    CODEC_ISO_6937_2 },
	{ "iso-ir-91",                    CODEC_ISO_IR_91 },
	{ "iso-ir-92",                    CODEC_ISO646_JP_OCR_B },
	{ "iso-ir-93",                    CODEC_ISO_IR_93 },
	{ "iso-ir-94",                    CODEC_ISO_IR_94 },
	{ "iso-ir-95",                    CODEC_ISO_IR_95 },
	{ "iso-ir-96",                    CODEC_ISO_IR_96 },
	{ "iso-ir-98",                    CODEC_ISO_IR_98 },
	{ "iso10367-box",                 CODEC_ISO_IR_155 },
	{ "iso10367box",                  CODEC_ISO_IR_155 },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "iso10646",                     CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "iso10646",                     CODEC_UTF32LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "iso10646-ucs-2",               CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "iso10646-ucs-2",               CODEC_UTF16LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "iso10646-ucs-4",               CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "iso10646-ucs-4",               CODEC_UTF32LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "iso10646/ucs2",                CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "iso10646/ucs2",                CODEC_UTF16LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "iso10646/ucs4",                CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "iso10646/ucs4",                CODEC_UTF32LE },
#endif /* ... */
	{ "iso10646/utf-8",               CODEC_UTF8 },
	{ "iso10646/utf8",                CODEC_UTF8 },
	{ "iso2033",                      CODEC_ISO_IR_98 },
	{ "iso2033-1983",                 CODEC_ISO_IR_98 },
	{ "iso5426",                      CODEC_ISO5426 },
	{ "iso5426-2",                    CODEC_ISO5426_2 },
	{ "iso5427",                      CODEC_ISO_5427 },
	{ "iso5427-ext",                  CODEC_ISO_IR_54 },
	{ "iso5427:1981",                 CODEC_ISO_IR_54 },
	{ "iso5427cyrillic1981",          CODEC_ISO_IR_54 },
	{ "iso5427ext",                   CODEC_ISO_IR_54 },
	{ "iso5428",                      CODEC_ISO_IR_55 },
	{ "iso5428:1980",                 CODEC_ISO_IR_55 },
	{ "iso6438",                      CODEC_ISO6438 },
	{ "iso646-ca",                    CODEC_ISO646_CA },
	{ "iso646-ca2",                   CODEC_ISO646_CA2 },
	{ "iso646-cn",                    CODEC_ISO646_CN },
	{ "iso646-cu",                    CODEC_ISO646_CU },
	{ "iso646-de",                    CODEC_ISO646_DE },
	{ "iso646-dk",                    CODEC_ISO646_DK },
	{ "iso646-es",                    CODEC_ISO646_ES },
	{ "iso646-es2",                   CODEC_ISO646_ES2 },
	{ "iso646-fi",                    CODEC_ISO646_SE },
	{ "iso646-fr",                    CODEC_ISO646_FR },
	{ "iso646-fr1",                   CODEC_ISO646_FR1 },
	{ "iso646-gb",                    CODEC_ISO646_GB },
	{ "iso646-hu",                    CODEC_ISO646_HU },
	{ "iso646-ie",                    CODEC_ISO646_IE },
	{ "iso646-is",                    CODEC_ISO646_IS },
	{ "iso646-it",                    CODEC_ISO646_IT },
	{ "iso646-jp",                    CODEC_ISO646_JP },
	{ "iso646-jp-ocr-b",              CODEC_ISO646_JP_OCR_B },
	{ "iso646-kr",                    CODEC_ISO646_KR },
	{ "iso646-mt",                    CODEC_ISO646_MT },
	{ "iso646-nl",                    CODEC_ISO646_NL },
	{ "iso646-no",                    CODEC_ISO646_NO },
	{ "iso646-no2",                   CODEC_ISO646_NO2 },
	{ "iso646-pt",                    CODEC_ISO646_PT },
	{ "iso646-pt2",                   CODEC_ISO646_PT2 },
	{ "iso646-se",                    CODEC_ISO646_SE },
	{ "iso646-se2",                   CODEC_ISO646_SE2 },
	{ "iso646-us",                    CODEC_ASCII },
	{ "iso646-yu",                    CODEC_ISO646_YU },
	{ "iso646.basic:1983",            CODEC_ISO646_BASIC },
	{ "iso646.irv:1983",              CODEC_ISO_IR_2 },
	{ "iso646.irv:1991",              CODEC_ASCII },
	{ "iso6937",                      CODEC_CP20269 },
	{ "iso6937-2",                    CODEC_ISO_6937_2 },
	{ "iso6937-2-25",                 CODEC_ISO_IR_152 },
	{ "iso6937-2:1983",               CODEC_ISO_6937_2 },
	{ "iso69372",                     CODEC_ISO_6937_2 },
	{ "iso6937:1992",                 CODEC_CP20269 },
	{ "iso8-bit-urdu",                CODEC_CP1006 },
	{ "iso8859-1",                    CODEC_ISO_8859_1 },
	{ "iso8859-1-i",                  CODEC_ISO_8859_1 },
	{ "iso8859-10",                   CODEC_ISO_8859_10 },
	{ "iso8859-10:1992",              CODEC_ISO_8859_10 },
	{ "iso8859-11",                   CODEC_ISO_8859_11 },
	{ "iso8859-13",                   CODEC_CP921 },
	{ "iso8859-14",                   CODEC_ISO_8859_14 },
	{ "iso8859-14:1998",              CODEC_ISO_8859_14 },
	{ "iso8859-15",                   CODEC_ISO_8859_15 },
	{ "iso8859-15:1998",              CODEC_ISO_8859_15 },
	{ "iso8859-16",                   CODEC_ISO_8859_16 },
	{ "iso8859-16:2001",              CODEC_ISO_8859_16 },
	{ "iso8859-1:1987",               CODEC_ISO_8859_1 },
	{ "iso8859-2",                    CODEC_ISO_8859_2 },
	{ "iso8859-2:1987",               CODEC_ISO_8859_2 },
	{ "iso8859-3",                    CODEC_ISO_8859_3 },
	{ "iso8859-3:1988",               CODEC_ISO_8859_3 },
	{ "iso8859-4",                    CODEC_ISO_8859_4 },
	{ "iso8859-4:1988",               CODEC_ISO_8859_4 },
	{ "iso8859-5",                    CODEC_ISO_8859_5 },
	{ "iso8859-5:1988",               CODEC_ISO_8859_5 },
	{ "iso8859-6",                    CODEC_ISO_8859_6 },
	{ "iso8859-6-i",                  CODEC_ISO_8859_6 },
	{ "iso8859-6:1987",               CODEC_ISO_8859_6 },
	{ "iso8859-7",                    CODEC_ISO_8859_7 },
	{ "iso8859-7:1987",               CODEC_ISO_8859_7 },
	{ "iso8859-7:2003",               CODEC_ISO_8859_7 },
	{ "iso8859-8",                    CODEC_ISO_8859_8 },
	{ "iso8859-8-i",                  CODEC_ISO_8859_8 },
	{ "iso8859-8:1988",               CODEC_ISO_8859_8 },
	{ "iso8859-9",                    CODEC_ISO_8859_9 },
	{ "iso8859-9:1989",               CODEC_ISO_8859_9 },
	{ "iso8859-9e",                   CODEC_ISO_8859_9E },
	{ "iso8859-supp",                 CODEC_ISO_IR_154 },
	{ "iso88591",                     CODEC_ISO_8859_1 },
	{ "iso885910",                    CODEC_ISO_8859_10 },
	{ "iso885911",                    CODEC_ISO_8859_11 },
	{ "iso885913",                    CODEC_CP921 },
	{ "iso885914",                    CODEC_ISO_8859_14 },
	{ "iso885915",                    CODEC_ISO_8859_15 },
	{ "iso885916",                    CODEC_ISO_8859_16 },
	{ "iso88592",                     CODEC_ISO_8859_2 },
	{ "iso88593",                     CODEC_ISO_8859_3 },
	{ "iso88594",                     CODEC_ISO_8859_4 },
	{ "iso88595",                     CODEC_ISO_8859_5 },
	{ "iso88596",                     CODEC_ISO_8859_6 },
	{ "iso88597",                     CODEC_ISO_8859_7 },
	{ "iso88598",                     CODEC_ISO_8859_8 },
	{ "iso88599",                     CODEC_ISO_8859_9 },
	{ "iso88599e",                    CODEC_ISO_8859_9E },
	{ "iso9036",                      CODEC_ISO_IR_89 },
	{ "it",                           CODEC_ISO646_IT },
	{ "jis-c-6229-ocr-a",             CODEC_JIS_C_6229_OCR_A },
	{ "jis-c6220-1969",               CODEC_ISO_IR_13 },
	{ "jis-c6220-1969-jp",            CODEC_ISO_IR_13 },
	{ "jis-c6220-1969-ro",            CODEC_ISO646_JP },
	{ "jis-c62201969ro",              CODEC_ISO646_JP },
	{ "jis-c6229-1984-a",             CODEC_ISO_IR_91 },
	{ "jis-c6229-1984-b",             CODEC_ISO646_JP_OCR_B },
	{ "jis-c6229-1984-b-add",         CODEC_ISO_IR_93 },
	{ "jis-c6229-1984-hand",          CODEC_ISO_IR_94 },
	{ "jis-c6229-1984-hand-add",      CODEC_ISO_IR_95 },
	{ "jis-c6229-1984-kana",          CODEC_ISO_IR_96 },
	{ "jis-c62291984b",               CODEC_ISO646_JP_OCR_B },
	{ "jis-x201",                     CODEC_X0201 },
	{ "jp",                           CODEC_ISO646_JP },
	{ "jp-ocr-a",                     CODEC_ISO_IR_91 },
	{ "jp-ocr-b",                     CODEC_ISO646_JP_OCR_B },
	{ "jp-ocr-b-add",                 CODEC_ISO_IR_93 },
	{ "jp-ocr-hand",                  CODEC_ISO_IR_94 },
	{ "jp-ocr-hand-add",              CODEC_ISO_IR_95 },
	{ "js",                           CODEC_ISO646_YU },
	{ "jus-i.b1.2",                   CODEC_ISO646_YU },
	{ "jus-i.b1.3-mac",               CODEC_ISO_IR_147 },
	{ "jus-i.b1.3-serb",              CODEC_ISO_IR_146 },
	{ "kamenicky",                    CODEC_KEYBCS2 },
	{ "katakana",                     CODEC_ISO_IR_13 },
	{ "kbl",                          CODEC_CP771 },
	{ "keybcs2",                      CODEC_KEYBCS2 },
	{ "koi0",                         CODEC_ISO_5427 },
	{ "koi7",                         CODEC_ISO_5427 },
	{ "koi7-n0",                      CODEC_ISO646_IRV_1983 },
	{ "koi7-n1",                      CODEC_ISO_5427 },
	{ "koi7-n2",                      CODEC_KOI7_N2 },
	{ "koi8",                         CODEC_KOI8 },
	{ "koi8-b",                       CODEC_KOI8_B },
	{ "koi8-e",                       CODEC_KOI8_E },
	{ "koi8-f",                       CODEC_KOI8_F },
	{ "koi8-n1",                      CODEC_KOI8_N1 },
	{ "koi8-n2",                      CODEC_KOI8_N2 },
	{ "koi8-r",                       CODEC_KOI8_R },
	{ "koi8-ru",                      CODEC_KOI8_RU },
	{ "koi8-t",                       CODEC_KOI8_T },
	{ "koi8-u",                       CODEC_KOI8_U },
	{ "koi8-unified",                 CODEC_KOI8_F },
	{ "koi8u",                        CODEC_KOI8_U },
	{ "ks-x-1003",                    CODEC_ISO646_KR },
	{ "ksc5636",                      CODEC_ISO646_KR },
	{ "ksc5636-1989",                 CODEC_ISO646_KR },
	{ "kz-1048",                      CODEC_KZ_1048 },
	{ "l1",                           CODEC_ISO_8859_1 },
	{ "l10",                          CODEC_ISO_8859_16 },
	{ "l2",                           CODEC_ISO_8859_2 },
	{ "l3",                           CODEC_ISO_8859_3 },
	{ "l4",                           CODEC_ISO_8859_4 },
	{ "l5",                           CODEC_ISO_8859_9 },
	{ "l6",                           CODEC_ISO_8859_10 },
	{ "l7",                           CODEC_CP921 },
	{ "l8",                           CODEC_ISO_8859_14 },
	{ "lap",                          CODEC_ISO_IR_158 },
	{ "latin-greek",                  CODEC_ISO_IR_19 },
	{ "latin-greek-1",                CODEC_ISO646_LATIN_GR_MIXED },
	{ "latin-lap",                    CODEC_ISO_IR_158 },
	{ "latin0",                       CODEC_ISO_8859_15 },
	{ "latin1",                       CODEC_ISO_8859_1 },
	{ "latin1-2-5",                   CODEC_ISO_IR_154 },
	{ "latin10",                      CODEC_ISO_8859_16 },
	{ "latin2",                       CODEC_ISO_8859_2 },
	{ "latin3",                       CODEC_ISO_8859_3 },
	{ "latin4",                       CODEC_ISO_8859_4 },
	{ "latin5",                       CODEC_ISO_8859_9 },
	{ "latin6",                       CODEC_ISO_8859_10 },
	{ "latin7",                       CODEC_CP921 },
	{ "latin8",                       CODEC_ISO_8859_14 },
	{ "latin9",                       CODEC_ISO_8859_15 },
	{ "latingreek",                   CODEC_ISO_IR_19 },
	{ "latingreek1",                  CODEC_ISO646_LATIN_GR_MIXED },
	{ "lics",                         CODEC_LICS },
	{ "lst-1283",                     CODEC_CP774 },
	{ "lst-1284",                     CODEC_CP772 },
	{ "lst-1284:1993",                CODEC_CP772 },
	{ "lst-1590-3",                   CODEC_CP1257 },
	{ "ly1",                          CODEC_LY1 },
	{ "mac",                          CODEC_CP1275 },
	{ "mac-centraleurope",            CODEC_CP1282 },
	{ "mac-cyrillic",                 CODEC_CP10017 },
	{ "mac-is",                       CODEC_MACIS },
	{ "mac-os-thai",                  CODEC_MAC_OS_THAI },
	{ "mac-sami",                     CODEC_MAC_SAMI },
	{ "mac-uk",                       CODEC_CP10017 },
	{ "macarabic",                    CODEC_CP10004 },
	{ "maccyrillic",                  CODEC_CP10017 },
	{ "macedonian",                   CODEC_ISO_IR_147 },
	{ "macfarsi",                     CODEC_X_MAC_FARSI },
	{ "macintosh",                    CODEC_CP1275 },
	{ "macintosh-font-x",             CODEC_MACINTOSH_FONT_X },
	{ "macintosh-latin",              CODEC_MACINTOSH_LATIN },
	{ "macis",                        CODEC_MACIS },
	{ "macroman",                     CODEC_CP1275 },
	{ "macuk",                        CODEC_CP10017 },
	{ "macukrainian",                 CODEC_CP10017 },
	{ "maz",                          CODEC_CP667 },
	{ "mazovia",                      CODEC_CP667 },
	{ "mik",                          CODEC_MIK },
	{ "ms-10206",                     CODEC_ISO646_DE },
	{ "ms-ansi",                      CODEC_CP1252 },
	{ "ms-arab",                      CODEC_CP1256 },
	{ "ms-cyrl",                      CODEC_CP1251 },
	{ "ms-ee",                        CODEC_CP1250 },
	{ "ms-greek",                     CODEC_CP1253 },
	{ "ms-hebr",                      CODEC_CP1255 },
	{ "ms-mac-cyrillic",              CODEC_CP10007 },
	{ "ms-turk",                      CODEC_CP1254 },
	{ "ms874",                        CODEC_CP874 },
	{ "msdos-1252",                   CODEC_MSDOS1252 },
	{ "msmaccyrillic",                CODEC_CP10007 },
	{ "msz-7795.3",                   CODEC_ISO646_HU },
	{ "nats-dano",                    CODEC_ISO646_NATS_DANO },
	{ "nats-dano-add",                CODEC_ISO_IR_9_2 },
	{ "nats-sefi",                    CODEC_ISO_IR_8_1 },
	{ "nats-sefi-add",                CODEC_ISO_IR_8_2 },
	{ "natsdano",                     CODEC_ISO646_NATS_DANO },
	{ "natssefi",                     CODEC_ISO_IR_8_1 },
	{ "nc-nc0-10",                    CODEC_ISO646_CU },
	{ "nc-nc0-10:81",                 CODEC_ISO646_CU },
	{ "nc-nc10",                      CODEC_ISO646_CU },
	{ "nec-867",                      CODEC_KEYBCS2 },
	{ "nf-z-62-10",                   CODEC_ISO646_FR },
	{ "nf-z-62-10-(1973)",            CODEC_ISO646_FR1 },
	{ "nf-z-62-10-(1983)",            CODEC_ISO646_FR },
	{ "nf-z-62-10-1973",              CODEC_ISO646_FR1 },
	{ "nf-z-62-10-1983",              CODEC_ISO646_FR },
	{ "nf-z-62010",                   CODEC_ISO646_FR },
	{ "nf-z-62010-1973",              CODEC_ISO646_FR1 },
	{ "no",                           CODEC_ISO646_NO },
	{ "no2",                          CODEC_ISO646_NO2 },
	{ "ns-4551-1",                    CODEC_ISO646_NO },
	{ "ns-4551-2",                    CODEC_ISO646_NO2 },
	{ "ns-45511",                     CODEC_ISO646_NO },
	{ "ns-45512",                     CODEC_ISO646_NO2 },
	{ "oem720",                       CODEC_CP720 },
	{ "oem737",                       CODEC_CP737 },
	{ "oem775",                       CODEC_CP775 },
	{ "oem850",                       CODEC_CP850 },
	{ "oem855",                       CODEC_CP855 },
	{ "oem857",                       CODEC_CP857 },
	{ "oem858",                       CODEC_CP858 },
	{ "oem860",                       CODEC_CP860 },
	{ "oem861",                       CODEC_CP861 },
	{ "oem862",                       CODEC_CP862 },
	{ "oem863",                       CODEC_CP863 },
	{ "oem865",                       CODEC_CP865 },
	{ "oem869",                       CODEC_CP869 },
	{ "oemus",                        CODEC_CP437 },
	{ "os2latin1",                    CODEC_CP1004 },
	{ "osd-ebcdic-df3-irv",           CODEC_OSD_EBCDIC_DF03_IRV },
	{ "osd-ebcdic-df4-1",             CODEC_OSD_EBCDIC_DF04_1 },
	{ "osd-ebcdic-df4-15",            CODEC_OSD_EBCDIC_DF04_15 },
	{ "osf10001",                     CODEC_ISO_8859_1 },
	{ "osf10002",                     CODEC_ISO_8859_2 },
	{ "osf10003",                     CODEC_ISO_8859_3 },
	{ "osf10004",                     CODEC_ISO_8859_4 },
	{ "osf10005",                     CODEC_ISO_8859_5 },
	{ "osf10006",                     CODEC_ISO_8859_6 },
	{ "osf10007",                     CODEC_ISO_8859_7 },
	{ "osf10008",                     CODEC_ISO_8859_8 },
	{ "osf10009",                     CODEC_ISO_8859_9 },
	{ "osf1000a",                     CODEC_ISO_8859_10 },
	{ "osf10010001",                  CODEC_HP_ROMAN8 },
	{ "osf10010004",                  CODEC_HP_GREEK8 },
	{ "osf10010006",                  CODEC_HP_TURKISH8 },
	{ "osf10020",                     CODEC_ASCII },
	{ "osf10020025",                  CODEC_CP37 },
	{ "osf10020111",                  CODEC_CP273 },
	{ "osf10020115",                  CODEC_EBCDIC_CP_DK_NO },
	{ "osf10020116",                  CODEC_CP278 },
	{ "osf10020118",                  CODEC_CP280 },
	{ "osf1002011c",                  CODEC_CP284 },
	{ "osf1002011d",                  CODEC_CP285 },
	{ "osf10020122",                  CODEC_CP290 },
	{ "osf10020129",                  CODEC_CP297 },
	{ "osf100201a4",                  CODEC_CP420 },
	{ "osf100201a8",                  CODEC_CP424 },
	{ "osf100201b5",                  CODEC_CP437 },
	{ "osf100201f4",                  CODEC_CP500 },
	{ "osf10020352",                  CODEC_CP850 },
	{ "osf10020354",                  CODEC_CP852 },
	{ "osf10020357",                  CODEC_CP855 },
	{ "osf10020359",                  CODEC_CP857 },
	{ "osf1002035d",                  CODEC_CP861 },
	{ "osf1002035e",                  CODEC_CP862 },
	{ "osf1002035f",                  CODEC_CP863 },
	{ "osf10020360",                  CODEC_CP864 },
	{ "osf10020364",                  CODEC_CP868 },
	{ "osf10020365",                  CODEC_CP869 },
	{ "osf10020366",                  CODEC_CP870 },
	{ "osf10020367",                  CODEC_CP871 },
	{ "osf1002036b",                  CODEC_CP875 },
	{ "osf10020370",                  CODEC_CP880 },
	{ "osf1002037b",                  CODEC_ASCII },
	{ "osf10020387",                  CODEC_ASCII },
	{ "osf10020388",                  CODEC_CP904 },
	{ "osf10020396",                  CODEC_CP918 },
	{ "osf10020402",                  CODEC_CP1026 },
	{ "osf10020417",                  CODEC_CP1047 },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "osf10100",                     CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "osf10100",                     CODEC_UTF16LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "osf10101",                     CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "osf10101",                     CODEC_UTF16LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "osf10102",                     CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "osf10102",                     CODEC_UTF16LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "osf10104",                     CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "osf10104",                     CODEC_UTF32LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "osf10105",                     CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "osf10105",                     CODEC_UTF32LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "osf10106",                     CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "osf10106",                     CODEC_UTF32LE },
#endif /* ... */
	{ "osf5010001",                   CODEC_UTF8 },
	{ "palmos",                       CODEC_PALMOS },
	{ "pc-multilingual-850+euro",     CODEC_CP858 },
	{ "postscript",                   CODEC_CP1276 },
	{ "postscript-standard-encoding", CODEC_CP1276 },
	{ "pt",                           CODEC_ISO646_PT },
	{ "pt154",                        CODEC_PT154 },
	{ "pt2",                          CODEC_ISO646_PT2 },
	{ "ptcp154",                      CODEC_PT154 },
	{ "pttc/bcd",                     CODEC_CP355 },
	{ "pttc/bcd-c",                   CODEC_CP358 },
	{ "pttc/bcd-d",                   CODEC_CP359 },
	{ "pttc/bcd-h",                   CODEC_CP357 },
	{ "pttc/bcd-m",                   CODEC_CP359 },
	{ "r8",                           CODEC_HP_ROMAN8 },
	{ "r9",                           CODEC_HP_ROMAN9 },
	{ "ref",                          CODEC_ISO646_BASIC },
	{ "rk1048",                       CODEC_KZ_1048 },
	{ "roman8",                       CODEC_HP_ROMAN8 },
	{ "roman9",                       CODEC_HP_ROMAN9 },
	{ "rst-2018-91",                  CODEC_CP1125 },
	{ "ruscii",                       CODEC_CP1125 },
	{ "ruslat",                       CODEC_CP3012 },
	{ "se",                           CODEC_ISO646_SE },
	{ "se2",                          CODEC_ISO646_SE2 },
	{ "sen-850200-b",                 CODEC_ISO646_SE },
	{ "sen-850200-c",                 CODEC_ISO646_SE2 },
	{ "serbian",                      CODEC_ISO_IR_146 },
	{ "short-koi",                    CODEC_KOI7_N2 },
	{ "sr-14111",                     CODEC_ISO_8859_16 },
	{ "ss636127",                     CODEC_ISO646_SE },
	{ "st-sev-358-88",                CODEC_ISO_IR_153 },
	{ "standardencoding",             CODEC_CP1276 },
	{ "strk1048-2002",                CODEC_KZ_1048 },
	{ "t.51",                         CODEC_CP20269 },
	{ "t.61",                         CODEC_CP1036 },
	{ "t.61-7bit",                    CODEC_ISO646_T_61 },
	{ "t.61-8bit",                    CODEC_CP1036 },
	{ "t.618bit",                     CODEC_CP1036 },
	{ "thai8",                        CODEC_HP_THAI8 },
	{ "tis-620",                      CODEC_ISO_8859_11 },
	{ "tis620",                       CODEC_ISO_8859_11 },
	{ "tis620-0",                     CODEC_ISO_8859_11 },
	{ "tis620.2529-1",                CODEC_ISO_8859_11 },
	{ "tis620.2533-0",                CODEC_ISO_8859_11 },
	{ "tr8dec",                       CODEC_CP1288 },
	{ "ts-5881",                      CODEC_ISO_8859_9 },
	{ "turkish8",                     CODEC_HP_TURKISH8 },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "ucs-2",                        CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "ucs-2",                        CODEC_UTF16LE },
#endif /* ... */
	{ "ucs-2be",                      CODEC_UTF16BE },
	{ "ucs-2le",                      CODEC_UTF16LE },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "ucs-4",                        CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "ucs-4",                        CODEC_UTF32LE },
#endif /* ... */
	{ "ucs-4be",                      CODEC_UTF32BE },
	{ "ucs-4le",                      CODEC_UTF32LE },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "ucs2",                         CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "ucs2",                         CODEC_UTF16LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "ucs4",                         CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "ucs4",                         CODEC_UTF32LE },
#endif /* ... */
	{ "uk",                           CODEC_ISO646_GB },
	{ "unicodebig",                   CODEC_UTF16BE },
	{ "unicodelittle",                CODEC_UTF16LE },
	{ "us",                           CODEC_ASCII },
	{ "us-ascii",                     CODEC_ASCII },
	{ "us-dk",                        CODEC_US_DK },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "utf-16",                       CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "utf-16",                       CODEC_UTF16LE },
#endif /* ... */
	{ "utf-16be",                     CODEC_UTF16BE },
	{ "utf-16le",                     CODEC_UTF16LE },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "utf-32",                       CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "utf-32",                       CODEC_UTF32LE },
#endif /* ... */
	{ "utf-32be",                     CODEC_UTF32BE },
	{ "utf-32le",                     CODEC_UTF32LE },
	{ "utf-8",                        CODEC_UTF8 },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "utf16",                        CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "utf16",                        CODEC_UTF16LE },
#endif /* ... */
	{ "utf16be",                      CODEC_UTF16BE },
	{ "utf16le",                      CODEC_UTF16LE },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "utf32",                        CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "utf32",                        CODEC_UTF32LE },
#endif /* ... */
	{ "utf32be",                      CODEC_UTF32BE },
	{ "utf32le",                      CODEC_UTF32LE },
	{ "utf8",                         CODEC_UTF8 },
	{ "ventura-int",                  CODEC_VENTURA_INTERNATIONAL },
	{ "ventura-international",        CODEC_VENTURA_INTERNATIONAL },
	{ "ventura-us",                   CODEC_VENTURA_US },
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ && __SIZEOF_WCHAR_T__ == 4
	{ "wchar-t",                      CODEC_UTF32LE },
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ && __SIZEOF_WCHAR_T__ == 4
	{ "wchar-t",                      CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ && __SIZEOF_WCHAR_T__ == 2
	{ "wchar-t",                      CODEC_UTF16LE },
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ && __SIZEOF_WCHAR_T__ == 2
	{ "wchar-t",                      CODEC_UTF16BE },
#endif /* ... */
	{ "we8dec",                       CODEC_CP1100 },
	{ "we8iso8859p1",                 CODEC_ISO_8859_1 },
	{ "win-sami-2",                   CODEC_CP1270 },
	{ "winbaltrim",                   CODEC_CP1257 },
	{ "windows-10000",                CODEC_CP1275 },
	{ "windows-10004",                CODEC_CP10004 },
	{ "windows-10006",                CODEC_CP10006 },
	{ "windows-10007",                CODEC_CP10007 },
	{ "windows-10010",                CODEC_CP1285 },
	{ "windows-10017",                CODEC_CP10017 },
	{ "windows-10029",                CODEC_CP1282 },
	{ "windows-10079",                CODEC_CP1286 },
	{ "windows-10081",                CODEC_CP1281 },
	{ "windows-10082",                CODEC_CP1284 },
	{ "windows-12001",                CODEC_UTF32BE },
	{ "windows-1250",                 CODEC_CP1250 },
	{ "windows-1251",                 CODEC_CP1251 },
	{ "windows-1252",                 CODEC_CP1252 },
	{ "windows-1253",                 CODEC_CP1253 },
	{ "windows-1254",                 CODEC_CP1254 },
	{ "windows-1255",                 CODEC_CP1255 },
	{ "windows-1256",                 CODEC_CP1256 },
	{ "windows-1257",                 CODEC_CP1257 },
	{ "windows-1258",                 CODEC_CP1258 },
	{ "windows-1270",                 CODEC_CP1270 },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ "windows-13488",                CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ "windows-13488",                CODEC_UTF16LE },
#endif /* ... */
	{ "windows-20105",                CODEC_ISO646_IRV_1983 },
	{ "windows-20106",                CODEC_ISO646_DE },
	{ "windows-20127",                CODEC_ASCII },
	{ "windows-20261",                CODEC_CP1036 },
	{ "windows-28591",                CODEC_ISO_8859_1 },
	{ "windows-28592",                CODEC_ISO_8859_2 },
	{ "windows-28593",                CODEC_ISO_8859_3 },
	{ "windows-28594",                CODEC_ISO_8859_4 },
	{ "windows-28595",                CODEC_ISO_8859_5 },
	{ "windows-28596",                CODEC_ISO_8859_6 },
	{ "windows-28597",                CODEC_ISO_8859_7 },
	{ "windows-28598",                CODEC_ISO_8859_8 },
	{ "windows-28599",                CODEC_ISO_8859_9 },
	{ "windows-28600",                CODEC_ISO_8859_10 },
	{ "windows-28601",                CODEC_ISO_8859_11 },
	{ "windows-28603",                CODEC_CP921 },
	{ "windows-28604",                CODEC_ISO_8859_14 },
	{ "windows-28605",                CODEC_ISO_8859_15 },
	{ "windows-28606",                CODEC_ISO_8859_16 },
	{ "windows-38591",                CODEC_ISO_8859_1 },
	{ "windows-38596",                CODEC_ISO_8859_6 },
	{ "windows-38598",                CODEC_ISO_8859_8 },
	{ "windows-65001",                CODEC_UTF8 },
	{ "windows-874",                  CODEC_CP874 },
	{ "windows-extended",             CODEC_CP1004 },
	{ "winsami2",                     CODEC_CP1270 },
	{ "ws2",                          CODEC_CP1270 },
	{ "x-ibm874",                     CODEC_CP874 },
	{ "x-mac-arabic",                 CODEC_CP10004 },
	{ "x-mac-armenian",               CODEC_X_MAC_ARMENIAN },
	{ "x-mac-barents-cyrillic",       CODEC_X_MAC_BARENTS_CYRILLIC },
	{ "x-mac-ce",                     CODEC_CP1282 },
	{ "x-mac-celtic",                 CODEC_X_MAC_CELTIC },
	{ "x-mac-croatian",               CODEC_CP1284 },
	{ "x-mac-cyrillic",               CODEC_X_MAC_CYRILLIC },
	{ "x-mac-devanagari",             CODEC_X_MAC_DEVANAGARI },
	{ "x-mac-esperanto",              CODEC_X_MAC_MALTESE },
	{ "x-mac-farsi",                  CODEC_X_MAC_FARSI },
	{ "x-mac-gaelic",                 CODEC_X_MAC_GAELIC },
	{ "x-mac-georgian",               CODEC_X_MAC_GEORGIAN },
	{ "x-mac-greek",                  CODEC_CP10006 },
	{ "x-mac-gujarati",               CODEC_X_MAC_GUJARATI },
	{ "x-mac-gurmukhi",               CODEC_X_MAC_GURMUKHI },
	{ "x-mac-icelandic",              CODEC_CP1286 },
	{ "x-mac-inuit",                  CODEC_X_MAC_INUIT },
	{ "x-mac-maltese",                CODEC_X_MAC_MALTESE },
	{ "x-mac-ogham",                  CODEC_X_MAC_OGHAM },
	{ "x-mac-roman",                  CODEC_CP1275 },
	{ "x-mac-romanian",               CODEC_CP1285 },
	{ "x-mac-sami",                   CODEC_X_MAC_SAMI },
	{ "x-mac-symbol",                 CODEC_CP1038 },
	{ "x-mac-turkic-cyrillic",        CODEC_X_MAC_TURKIC_CYRILLIC },
	{ "x-mac-turkish",                CODEC_CP1281 },
	{ "x-mac-ukrainian",              CODEC_CP10017 },
	{ "x-windows-874",                CODEC_CP874 },
	{ "x201",                         CODEC_X0201 },
	{ "x201-7",                       CODEC_ISO_IR_13 },
	{ "yu",                           CODEC_ISO646_YU },
};
/*[[[end]]]*/


PRIVATE char const remove_sep_prefixes[][6] = {
	"oem", "ibm", "iso", "cp", "latin", "koi", "l"
};


/* Try to normalize the name of the given codec:
 *
 * - If the name starts with one of <PFX> <SEP> <DIGIT>, then <SEP>
 *   is removed, where <DIGIT> must be one of 0123456789, and <SEP>
 *   is one of "_- ", and <PFX> is one of:
 *      "OEM", "IBM", "ISO", "CP", "LATIN", "KOI", "L"
 *
 * - Replace "_" and " " with "-"; <SEP> can be one of "_", "-" or " "
 * - Leading 0s are removed from embedded digit-sequences:
 *    - "abc1002def" --> "abc1002def"
 *    - "abc0123def" --> "abc123def"
 *    - "abc0000def" --> "abc0def"
 *    - "abc0def"    --> "abc0def"
 *
 * Examples:
 *   - "OEM-0123"  --->  "OEM123"
 *   - "OEM_0123"  --->  "OEM123"
 *   - "OEM 0123"  --->  "OEM123"
 *
 *
 * NOTE: This function assumes that `name[namelen]' is either '\0' or '/'
 */
PRIVATE WUNUSED NONNULL((1, 2)) bool
NOTHROW_NCX(FCALL libiconv_normalize_codec_name)(char buf[CODE_NAME_MAXLEN + 1],
                                                 char const *__restrict name,
                                                 size_t namelen) {
#define issep(ch) ((ch) == '-' || (ch) == '_' || (ch) == ' ')
	char *ptr, *end;
	char const *nameend;
	unsigned int i;
	ptr     = buf;
	end     = buf + CODE_NAME_MAXLEN;
	nameend = name + namelen;

	/* Skip leading space. */
	while (isspace(*name))
		++name;

	/* Remove <SEP> characters are certain prefixes if those
	 * prefixes are followed up with a digit character. */
	for (i = 0; i < COMPILER_LENOF(remove_sep_prefixes); ++i) {
		size_t len = strlen(remove_sep_prefixes[i]);
		if (memcasecmp(name, remove_sep_prefixes[i], len * sizeof(char)) == 0 &&
		    issep(name[len]) && isdigit(name[len + 1])) {
			ptr = (char *)mempcpy(ptr, remove_sep_prefixes[i], len, sizeof(char));
			name += len + 1; /* Skip the <SEP> character. */
			break;
		}
	}

	/* Strip trailing spaces. */
	while (nameend > name && isspace(nameend[-1]))
		--nameend;

	/* Convert the rest of the name. */
	while (name < nameend) {
		char ch;
		ch = *name++;
		/* Generally, if `name' contains a sequence of numbers that starts
		 * with at least  one leading `0',  re-attempt the search  without
		 * those leading zero-digits. */
		if (ch == '0' && isdigit(*name) &&
		    (ptr == buf || !isdigit(ptr[-1])))
			continue; /* Skip leading 0s in number-strings. */
		/* '-', '_' and ' ' work interchangeably. */
		if (ch == '_' || ch == ' ')
			ch = '-';
		if (ptr >= end)
			return false; /* Name too long */
		*ptr++ = ch;
	}

	/* NUL-terminate the normalized name. */
	*ptr = '\0';

	/* Success! */
	return true;
}


/* Return the ID of the codec associated with  `name'
 * Casing is ignored and codec aliases are respected. */
INTERN ATTR_PURE WUNUSED NONNULL((1)) unsigned int
NOTHROW_NCX(FCALL libiconv_codecbyname)(char const *__restrict name) {
	size_t lo, hi;
	char normal_name[CODE_NAME_MAXLEN + 1];
again:
	lo = 0;
	hi = COMPILER_LENOF(codec_db);
	while (lo < hi) {
		size_t i;
		int cmp;
		i = (lo + hi) / 2;
		cmp = strcasecmp(name, codec_db[i].cdbe_name);
		if (cmp < 0) {
			hi = i;
		} else if (cmp > 0) {
			lo = i + 1;
		} else {
			/* Found it! */
			return codec_db[i].cdbe_codec;
		}
	}

	/* If not done already, try to normalize the codec name */
	if (name != normal_name) {
		if (libiconv_normalize_codec_name(normal_name, name,
		                                  strlen(name))) {
			name = normal_name;
			goto again;
		}
	}
	return CODEC_UNKNOWN;
}

/* Return the nth (0-based) alphabetically sorted name for the codec `id'
 * When `id' is  invalid or  doesn't have  an `nth'  name, return  `NULL' */
INTERN ATTR_CONST WUNUSED char const *
NOTHROW_NCX(FCALL libiconv_getcodecname)(unsigned int id, unsigned int nth) {
	size_t i;
	for (i = 0; i < COMPILER_LENOF(codec_db); ++i) {
		if (codec_db[i].cdbe_codec != id)
			continue;
		if (nth == 0)
			return codec_db[i].cdbe_name;
		--nth;
	}
	return NULL;
}


/* Same as `libiconv_codecbyname()', but the name has a fixed length. */
PRIVATE ATTR_NOINLINE ATTR_PURE WUNUSED NONNULL((1)) unsigned int
NOTHROW_NCX(FCALL libiconv_codecbynamez)(char const *__restrict name,
                                         size_t namelen) {
	char *buf;
	/* For  simplicity,  just  create  a  stack-copy  of the
	 * string that is NUL-terminated at the proper position. */
	if likely(namelen <= CODE_NAME_MAXLEN) {
		buf = (char *)alloca((namelen + 1) * sizeof(char));
		*(char *)mempcpy(buf, name, namelen, sizeof(char)) = '\0';
	} else {
		/* In this case we know that the name won't be found as-is.
		 * So rather than risk allocating a lot of stack memory, we
		 * just try to normalize it for the purpose of limiting its
		 * max length.
		 * If that fails, then we know no such codec can possibly
		 * exist since the name would be too long. */
		buf = (char *)alloca((CODE_NAME_MAXLEN + 1) * sizeof(char));
		if (!libiconv_normalize_codec_name(buf, name, namelen))
			return CODEC_UNKNOWN; /* Can't possibly be a supported codec. */
	}
	return libiconv_codecbyname(buf);
}


/* Same as `libiconv_codecbyname()', but also parse possible flag-relation options. */
INTERN WUNUSED NONNULL((1)) unsigned int
NOTHROW_NCX(FCALL libiconv_codec_and_flags_byname)(char const *__restrict name,
                                                   /*[in|out]*/ uintptr_half_t *__restrict pflags) {
	unsigned int result;
	/* Check for the simple case where the name doesn't contain any flags. */
	result = libiconv_codecbyname(name);
	if (result == CODEC_UNKNOWN) {
		/* The codec couldn't be found. This  might be because the give  name
		 * contains flags. If that's the  case, figure out where flags  begin
		 * and re-try the lookup the the part before their starting position. */
		char const *flags_start = strstr(name, "//");
		if (flags_start) {
			result = libiconv_codecbynamez(name, (size_t)(flags_start - name));
			if unlikely(result == CODEC_UNKNOWN)
				goto done; /* Still an unknown codec. :( */
			do {
				char const *next_flag;
				size_t flaglen;
				flags_start += 2;
				next_flag = strstr(flags_start, "//");
				if (!next_flag)
					next_flag = strend(flags_start);
				/* Strip leading and trailing spaces from the flag name. */
				while (isspace(*flags_start))
					++flags_start;
				flaglen = (size_t)(next_flag - flags_start);
				while (flaglen && isspace(flags_start[flaglen - 1]))
					--flaglen;

				/* Check which flag has been given. */
#ifdef __OPTIMIZE_SIZE__
#define ISFLAG(str) (memcasecmp(flags_start, str, COMPILER_STRLEN(str) * sizeof(char)) == 0)
#else /* __OPTIMIZE_SIZE__ */
#define ISFLAG(str) (flaglen == COMPILER_STRLEN(str) && memcasecmp(flags_start, str, COMPILER_STRLEN(str) * sizeof(char)) == 0)
#endif /* !__OPTIMIZE_SIZE__ */
				if (ISFLAG("ignore")) {
					/* "//IGNORE" Means to discard invalid characters. */
					*pflags &= ~ICONV_ERRMASK;
					*pflags |= ICONV_ERR_DISCARD;
				} else if (ISFLAG("translit")) {
					/* "//TRANSLIT" Means to try and transliterate characters that can't be encoded. */
					*pflags |= ICONV_ERR_TRANSLIT;
				} else {
					/* Unknown flag. (error out) */
					return CODEC_UNKNOWN;
				}
#undef ISFLAG
				flags_start = next_flag;
			} while (*flags_start);
		}
	}
done:
	return result;
}


/* Check  if  the 2  given strings  reference  the same  codec name.
 * This differs from same codec ID as this function doesn't actually
 * search the codec database but will simply strip potential  flags,
 * normalize the underlying codec names, and check if the  resulting
 * strings strcasecmp(3) to be equal. */
INTERN ATTR_CONST WUNUSED NONNULL((1, 2)) bool
NOTHROW_NCX(FCALL libiconv_same_codec_name)(char const *__restrict a,
                                            char const *__restrict b) {
	size_t lena, lenb;
	char norm_a[CODE_NAME_MAXLEN + 1];
	char norm_b[CODE_NAME_MAXLEN + 1];

	/* Quick check: are they identical. */
	if (strcasecmp(a, b) == 0)
		return true;

	/* Figure out how long the actual codec names are (without possible flags) */
	lena = strlen(a);
	lenb = strlen(b);
	{
		char const *temp;
		temp = strstr(a, "//");
		if (temp)
			lena = (size_t)(temp - a);
		temp = strstr(b, "//");
		if (temp)
			lenb = (size_t)(temp - b);
	}

	/* Normalize the codec names. */
	if (!libiconv_normalize_codec_name(norm_a, a, lena))
		goto nope;
	if (!libiconv_normalize_codec_name(norm_b, b, lenb))
		goto nope;

	/* Check of the normalized names are identical. */
	return strcasecmp(norm_a, norm_b) == 0;
nope:
	return false;
}



DECL_END

#endif /* !GUARD_LIBICONV_CODECS_C */
