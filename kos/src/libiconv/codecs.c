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

/*[[[deemon
import * from deemon;
local inCodecs = false;
local name2codec = Dict();
for (local l: File.open("./codecs.h")) {
	l = l.strip();
	if (l == "/" "*[[[begin:codecs]]]*" "/") {
		inCodecs = true;
		continue;
	}
	if (!inCodecs)
		continue;
	if (l == "/" "*[[[end:codecs]]]*" "/")
		break;
	if (!l || !l.issymstrt(0))
		continue;
	local codecEnd = 1;
	while (codecEnd < #l && l.issymcont(codecEnd))
		++codecEnd;
	local codec = l[:codecEnd];
	local i = l.find("/" "*");
	if (i < 0)
		continue;
	l = l[i+2:].rsstrip("*" "/").strip();
	while (l) {
		local name;
		if (l.startswith("\"")) {
			local nameEnd = l.index("\"", 1) + 1;
			name = l[:nameEnd].decode("c-escape");
			l = l[nameEnd:];
		} else {
			local nameEnd = l.find(",");
			if (nameEnd < 0)
				nameEnd = #l;
			name = l[:nameEnd].strip();
			l = l[nameEnd:];
		}
		name = name.lower().replace("_", "-");
		assert " " !in name, repr name;
		assert "--" !in name, repr name;
		local i = 0;
		for (;;) {
			i = name.find("0", i);
			if (i < 0)
				break;
			if (i + 1 < #name && name.isdigit(i + 1) &&
			    (i == 0 || !name.isdigit(i - 1)))
				name = name[:i] + name[i+1:];
			else {
				++i;
			}
		}
		if (name in name2codec)
			throw Error("Duplicate mapping for " + repr name);
		name2codec[name] = codec;
		l = l.lstrip().lstrip(",").lstrip();
	}
}
local longestNameLen = (name2codec.keys.each.length > ...) + 1;
print("#define CODE_NAME_MAXLEN ", longestNameLen-1);
print("struct codec_db_entry {");
print("	char         cdbe_name[CEIL_ALIGN(", longestNameLen, ", __SIZEOF_INT__)];");
print("	unsigned int cdbe_codec; /" "* The associated codec. *" "/");
print("};");
print();
print("PRIVATE struct codec_db_entry codec_db[", #name2codec, "] = {");
local longestNameReprLen = name2codec.keys.each.encode("c-escape").length > ...;
for (local name: name2codec.keys.sorted()) {
	local nameRepr = name.encode("c-escape");
	print("	{ \"", nameRepr, "\", ", " " * (longestNameReprLen - #nameRepr), name2codec[name], " },");
}
print("};");
]]]*/
#define CODE_NAME_MAXLEN 28
struct codec_db_entry {
	char         cdbe_name[CEIL_ALIGN(29, __SIZEOF_INT__)];
	unsigned int cdbe_codec; /* The associated codec. */
};

PRIVATE struct codec_db_entry codec_db[779] = {
	{ "10646-1:1993",                 CODEC_UTF32 },
	{ "10646-1:1993/ucs4",            CODEC_UTF32 },
	{ "437",                          CODEC_CP437 },
	{ "850",                          CODEC_CP850 },
	{ "851",                          CODEC_CP851 },
	{ "852",                          CODEC_CP852 },
	{ "855",                          CODEC_CP855 },
	{ "857",                          CODEC_CP857 },
	{ "860",                          CODEC_CP860 },
	{ "861",                          CODEC_CP861 },
	{ "862",                          CODEC_CP862 },
	{ "863",                          CODEC_CP863 },
	{ "865",                          CODEC_CP865 },
	{ "866",                          CODEC_CP866 },
	{ "869",                          CODEC_CP869 },
	{ "904",                          CODEC_CP904 },
	{ "ami1251",                      CODEC_AMIGA_1251 },
	{ "amiga-1251",                   CODEC_AMIGA_1251 },
	{ "ansi-x3.4",                    CODEC_ASCII },
	{ "ansi-x3.4-1968",               CODEC_ASCII },
	{ "ansi-x3.4-1986",               CODEC_ASCII },
	{ "arabic",                       CODEC_ISO_8859_6 },
	{ "ascii",                        CODEC_ASCII },
	{ "asmo-708",                     CODEC_ISO_8859_6 },
	{ "bcdic",                        CODEC_BCDIC },
	{ "bn-74/3101-1",                 CODEC_ISO646_PL },
	{ "bs-4730",                      CODEC_ISO646_GB },
	{ "bulgaria-pc",                  CODEC_MIK },
	{ "burroughs-b5500",              CODEC_BURROUGHS_B5500 },
	{ "ca",                           CODEC_ISO646_CA },
	{ "ch7dec",                       CODEC_ISO646_SWI_NRCS },
	{ "cn",                           CODEC_ISO646_CN },
	{ "cp-ar",                        CODEC_CP868 },
	{ "cp-gr",                        CODEC_CP869 },
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
	{ "cp1010",                       CODEC_CP1010 },
	{ "cp1011",                       CODEC_ISO646_DE },
	{ "cp1012",                       CODEC_CP1012 },
	{ "cp1013",                       CODEC_ISO646_GB },
	{ "cp1014",                       CODEC_ISO646_ES2 },
	{ "cp1015",                       CODEC_ISO646_PT2 },
	{ "cp1016",                       CODEC_ISO646_DANO_NATS },
	{ "cp1017",                       CODEC_ISO646_DK },
	{ "cp1018",                       CODEC_ISO646_SE },
	{ "cp1019",                       CODEC_ISO646_NL },
	{ "cp1020",                       CODEC_ISO646_CA },
	{ "cp1021",                       CODEC_ISO646_SWI_NRCS },
	{ "cp1023",                       CODEC_ISO646_ES },
	{ "cp1036",                       CODEC_CP1036 },
	{ "cp1038",                       CODEC_CP1038 },
	{ "cp1040",                       CODEC_CP1040 },
	{ "cp1041",                       CODEC_CP1041 },
	{ "cp1042",                       CODEC_CP1042 },
	{ "cp1043",                       CODEC_CP1043 },
	{ "cp1046",                       CODEC_CP1046 },
	{ "cp1050",                       CODEC_CP1050 },
	{ "cp1051",                       CODEC_CP1050 },
	{ "cp1057",                       CODEC_CP1057 },
	{ "cp1088",                       CODEC_CP1088 },
	{ "cp1089",                       CODEC_ISO_8859_6 },
	{ "cp1090",                       CODEC_CP1090 },
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
	{ "cp1114",                       CODEC_CP1114 },
	{ "cp1115",                       CODEC_CP1115 },
	{ "cp1116",                       CODEC_CP1116 },
	{ "cp1117",                       CODEC_CP1117 },
	{ "cp1118",                       CODEC_CP774 },
	{ "cp1119",                       CODEC_CP772 },
	{ "cp1124",                       CODEC_CP1124 },
	{ "cp1125",                       CODEC_CP1125 },
	{ "cp1127",                       CODEC_CP1127 },
	{ "cp1129",                       CODEC_CP1129 },
	{ "cp1131",                       CODEC_CP1131 },
	{ "cp1133",                       CODEC_CP1133 },
	{ "cp1161",                       CODEC_CP1161 },
	{ "cp1162",                       CODEC_CP1162 },
	{ "cp1163",                       CODEC_CP1163 },
	{ "cp1167",                       CODEC_KOI8_RU },
	{ "cp1168",                       CODEC_KOI8_U },
	{ "cp1200",                       CODEC_UTF16 },
	{ "cp12000",                      CODEC_UTF32 },
	{ "cp12001",                      CODEC_UTF32BE },
	{ "cp1201",                       CODEC_UTF16 },
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
	{ "cp13488",                      CODEC_UTF16 },
	{ "cp17248",                      CODEC_CP17248 },
	{ "cp20105",                      CODEC_ISO646_IRV_1983 },
	{ "cp20106",                      CODEC_ISO646_DE },
	{ "cp20127",                      CODEC_ASCII },
	{ "cp20261",                      CODEC_CP1036 },
	{ "cp20269",                      CODEC_CP20269 },
	{ "cp20866",                      CODEC_KOI8_R },
	{ "cp21866",                      CODEC_KOI8_U },
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
	{ "cp28603",                      CODEC_ISO_8859_13 },
	{ "cp28604",                      CODEC_ISO_8859_14 },
	{ "cp28605",                      CODEC_ISO_8859_15 },
	{ "cp28606",                      CODEC_ISO_8859_16 },
	{ "cp3012",                       CODEC_CP3012 },
	{ "cp353",                        CODEC_CP353 },
	{ "cp355",                        CODEC_CP355 },
	{ "cp357",                        CODEC_CP357 },
	{ "cp358",                        CODEC_CP358 },
	{ "cp359",                        CODEC_CP359 },
	{ "cp360",                        CODEC_CP359 },
	{ "cp367",                        CODEC_ASCII },
	{ "cp38591",                      CODEC_ISO_8859_1 },
	{ "cp38596",                      CODEC_ISO_8859_6 },
	{ "cp38598",                      CODEC_ISO_8859_8 },
	{ "cp437",                        CODEC_CP437 },
	{ "cp4992",                       CODEC_CP896 },
	{ "cp5104",                       CODEC_CP1008 },
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
	{ "cp866nav",                     CODEC_CP1125 },
	{ "cp866u",                       CODEC_CP1125 },
	{ "cp867",                        CODEC_CP867 },
	{ "cp868",                        CODEC_CP868 },
	{ "cp869",                        CODEC_CP869 },
	{ "cp872",                        CODEC_CP872 },
	{ "cp874",                        CODEC_CP874 },
	{ "cp878",                        CODEC_KOI8_R },
	{ "cp895",                        CODEC_CP895 },
	{ "cp896",                        CODEC_CP896 },
	{ "cp897",                        CODEC_CP897 },
	{ "cp901",                        CODEC_CP901 },
	{ "cp902",                        CODEC_CP902 },
	{ "cp903",                        CODEC_CP903 },
	{ "cp904",                        CODEC_CP904 },
	{ "cp9066",                       CODEC_CP874 },
	{ "cp912",                        CODEC_CP912 },
	{ "cp913",                        CODEC_ISO_8859_3 },
	{ "cp914",                        CODEC_ISO_8859_4 },
	{ "cp915",                        CODEC_CP915 },
	{ "cp916",                        CODEC_ISO_8859_8 },
	{ "cp919",                        CODEC_ISO_8859_10 },
	{ "cp920",                        CODEC_ISO_8859_9 },
	{ "cp921",                        CODEC_CP921 },
	{ "cp922",                        CODEC_CP922 },
	{ "cp923",                        CODEC_ISO_8859_15 },
	{ "cp991",                        CODEC_CP667 },
	{ "csa-z243.4-1985-1",            CODEC_ISO646_CA },
	{ "csa-z243.4-1985-2",            CODEC_ISO646_CA2 },
	{ "csa-z243.419851",              CODEC_ISO646_CA },
	{ "csa-z243.419852",              CODEC_ISO646_CA2 },
	{ "csa7-1",                       CODEC_ISO646_CA },
	{ "csa7-2",                       CODEC_ISO646_CA2 },
	{ "csascii",                      CODEC_ASCII },
	{ "csdecmcs",                     CODEC_CP1100 },
	{ "csiso10swedish",               CODEC_ISO646_SE },
	{ "csiso11swedishfornames",       CODEC_ISO646_SE2 },
	{ "csiso121canadian1",            CODEC_ISO646_CA },
	{ "csiso122canadian2",            CODEC_ISO646_CA2 },
	{ "csiso141jusib1002",            CODEC_ISO646_YU },
	{ "csiso14jisc6220ro",            CODEC_ISO646_JP },
	{ "csiso151cuba",                 CODEC_ISO646_CU },
	{ "csiso15italian",               CODEC_ISO646_IT },
	{ "csiso16portugese",             CODEC_ISO646_PT },
	{ "csiso17spanish",               CODEC_ISO646_ES },
	{ "csiso21german",                CODEC_ISO646_DE },
	{ "csiso25french",                CODEC_ISO646_FR1 },
	{ "csiso4unitedkingdom",          CODEC_ISO646_GB },
	{ "csiso58gb1988",                CODEC_ISO646_CN },
	{ "csiso60danishnorwegian",       CODEC_ISO646_NO },
	{ "csiso60norwegian1",            CODEC_ISO646_NO },
	{ "csiso61norwegian2",            CODEC_ISO646_NO2 },
	{ "csiso646danish",               CODEC_ISO646_DK },
	{ "csiso69french",                CODEC_ISO646_FR },
	{ "csiso84portuguese2",           CODEC_ISO646_PT2 },
	{ "csiso85spanish2",              CODEC_ISO646_ES2 },
	{ "csiso86hungarian",             CODEC_ISO646_HU },
	{ "csiso92jisc62991984b",         CODEC_ISO646_JP_OCR_B },
	{ "csisolatin1",                  CODEC_ISO_8859_1 },
	{ "csisolatin2",                  CODEC_ISO_8859_2 },
	{ "csisolatin3",                  CODEC_ISO_8859_3 },
	{ "csisolatin4",                  CODEC_ISO_8859_4 },
	{ "csisolatin5",                  CODEC_ISO_8859_9 },
	{ "csisolatin6",                  CODEC_ISO_8859_10 },
	{ "csisolatin7",                  CODEC_ISO_8859_13 },
	{ "csisolatinarabic",             CODEC_ISO_8859_6 },
	{ "csisolatincyrillic",           CODEC_ISO_8859_5 },
	{ "csisolatingreek",              CODEC_ISO_8859_7 },
	{ "csisolatinhebrew",             CODEC_ISO_8859_8 },
	{ "csksc5636",                    CODEC_ISO646_KR },
	{ "cspc850multilingual",          CODEC_CP850 },
	{ "cspc862latinhebrew",           CODEC_CP862 },
	{ "cspc8codepage437",             CODEC_CP437 },
	{ "cspcp852",                     CODEC_CP852 },
	{ "csucs4",                       CODEC_UTF32 },
	{ "cuba",                         CODEC_ISO646_CU },
	{ "cyrillic",                     CODEC_ISO_8859_5 },
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
	{ "din-66003",                    CODEC_ISO646_DE },
	{ "din-66303",                    CODEC_DIN_66303 },
	{ "dk",                           CODEC_ISO646_DK },
	{ "dos-895",                      CODEC_KEYBCS2 },
	{ "drv8",                         CODEC_DIN_66303 },
	{ "ds-2089",                      CODEC_ISO646_DK },
	{ "ds2089",                       CODEC_ISO646_DK },
	{ "e7dec",                        CODEC_ISO646_ES },
	{ "ecma-114",                     CODEC_ISO_8859_6 },
	{ "ecma-118",                     CODEC_ISO_8859_7 },
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
	{ "german",                       CODEC_ISO646_DE },
	{ "greek",                        CODEC_ISO_8859_7 },
	{ "greek8",                       CODEC_ISO_8859_7 },
	{ "hebrew",                       CODEC_ISO_8859_8 },
	{ "hp-pc-8",                      CODEC_CP1057 },
	{ "hp-roman-8",                   CODEC_CP1050 },
	{ "hu",                           CODEC_ISO646_HU },
	{ "i7dec",                        CODEC_CP1012 },
	{ "ibm1006",                      CODEC_CP1006 },
	{ "ibm1008",                      CODEC_CP1008 },
	{ "ibm1009",                      CODEC_ISO646_IRV_1983 },
	{ "ibm1010",                      CODEC_CP1010 },
	{ "ibm1011",                      CODEC_ISO646_DE },
	{ "ibm1012",                      CODEC_CP1012 },
	{ "ibm1013",                      CODEC_ISO646_GB },
	{ "ibm1014",                      CODEC_ISO646_ES2 },
	{ "ibm1015",                      CODEC_ISO646_PT2 },
	{ "ibm1016",                      CODEC_ISO646_DANO_NATS },
	{ "ibm1017",                      CODEC_ISO646_DK },
	{ "ibm1018",                      CODEC_ISO646_SE },
	{ "ibm1019",                      CODEC_ISO646_NL },
	{ "ibm1021",                      CODEC_ISO646_SWI_NRCS },
	{ "ibm1036",                      CODEC_CP1036 },
	{ "ibm1038",                      CODEC_CP1038 },
	{ "ibm1089",                      CODEC_ISO_8859_6 },
	{ "ibm1090",                      CODEC_CP1090 },
	{ "ibm1098",                      CODEC_CP1098 },
	{ "ibm1100",                      CODEC_CP1100 },
	{ "ibm1101",                      CODEC_ISO646_GB_NRCS },
	{ "ibm1102",                      CODEC_ISO646_NL_NRCS },
	{ "ibm1103",                      CODEC_ISO646_FI_NRCS },
	{ "ibm1105",                      CODEC_ISO646_DK_NO_NRCS },
	{ "ibm1106",                      CODEC_ISO646_SE_NRCS },
	{ "ibm1107",                      CODEC_ISO646_DK_NO_ALT_NRCS },
	{ "ibm1111",                      CODEC_ISO_8859_2 },
	{ "ibm1116",                      CODEC_CP1116 },
	{ "ibm1117",                      CODEC_CP1117 },
	{ "ibm1118",                      CODEC_CP774 },
	{ "ibm1124",                      CODEC_CP1124 },
	{ "ibm1129",                      CODEC_CP1129 },
	{ "ibm1131",                      CODEC_CP1131 },
	{ "ibm1133",                      CODEC_CP1133 },
	{ "ibm1161",                      CODEC_CP1161 },
	{ "ibm1162",                      CODEC_CP1162 },
	{ "ibm1163",                      CODEC_CP1163 },
	{ "ibm1168",                      CODEC_KOI8_U },
	{ "ibm1275",                      CODEC_CP1275 },
	{ "ibm1281",                      CODEC_CP1281 },
	{ "ibm1282",                      CODEC_CP1282 },
	{ "ibm1283",                      CODEC_CP10007 },
	{ "ibm1284",                      CODEC_CP1284 },
	{ "ibm1285",                      CODEC_CP1285 },
	{ "ibm1286",                      CODEC_CP1286 },
	{ "ibm1401",                      CODEC_IBM1401 },
	{ "ibm367",                       CODEC_ASCII },
	{ "ibm437",                       CODEC_CP437 },
	{ "ibm5104",                      CODEC_CP1008 },
	{ "ibm704",                       CODEC_IBM704 },
	{ "ibm708",                       CODEC_CP708 },
	{ "ibm7090",                      CODEC_IBM7090 },
	{ "ibm7094",                      CODEC_IBM7090 },
	{ "ibm720",                       CODEC_CP720 },
	{ "ibm737",                       CODEC_CP737 },
	{ "ibm775",                       CODEC_CP775 },
	{ "ibm806",                       CODEC_CP806 },
	{ "ibm813",                       CODEC_ISO_8859_7 },
	{ "ibm819",                       CODEC_ISO_8859_1 },
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
	{ "ibm868",                       CODEC_CP868 },
	{ "ibm869",                       CODEC_CP869 },
	{ "ibm874",                       CODEC_CP874 },
	{ "ibm878",                       CODEC_KOI8_R },
	{ "ibm895",                       CODEC_CP895 },
	{ "ibm896",                       CODEC_CP896 },
	{ "ibm901",                       CODEC_CP901 },
	{ "ibm902",                       CODEC_CP902 },
	{ "ibm903",                       CODEC_CP903 },
	{ "ibm904",                       CODEC_CP904 },
	{ "ibm9066",                      CODEC_CP874 },
	{ "ibm912",                       CODEC_CP912 },
	{ "ibm913",                       CODEC_ISO_8859_3 },
	{ "ibm914",                       CODEC_ISO_8859_4 },
	{ "ibm915",                       CODEC_CP915 },
	{ "ibm916",                       CODEC_ISO_8859_8 },
	{ "ibm919",                       CODEC_ISO_8859_10 },
	{ "ibm920",                       CODEC_ISO_8859_9 },
	{ "ibm921",                       CODEC_CP921 },
	{ "ibm922",                       CODEC_CP922 },
	{ "ibm923",                       CODEC_ISO_8859_15 },
	{ "iso-8-bit-urdu",               CODEC_CP1006 },
	{ "iso-celtic",                   CODEC_ISO_8859_14 },
	{ "iso-ir-10",                    CODEC_ISO646_SE },
	{ "iso-ir-100",                   CODEC_ISO_8859_1 },
	{ "iso-ir-101",                   CODEC_ISO_8859_2 },
	{ "iso-ir-102",                   CODEC_ISO646_T_61 },
	{ "iso-ir-109",                   CODEC_ISO_8859_3 },
	{ "iso-ir-11",                    CODEC_ISO646_SE2 },
	{ "iso-ir-110",                   CODEC_ISO_8859_4 },
	{ "iso-ir-111",                   CODEC_KOI8_E },
	{ "iso-ir-121",                   CODEC_ISO646_CA },
	{ "iso-ir-122",                   CODEC_ISO646_CA2 },
	{ "iso-ir-126",                   CODEC_ISO_8859_7 },
	{ "iso-ir-127",                   CODEC_ISO_8859_6 },
	{ "iso-ir-138",                   CODEC_ISO_8859_8 },
	{ "iso-ir-14",                    CODEC_ISO646_JP },
	{ "iso-ir-144",                   CODEC_ISO_8859_5 },
	{ "iso-ir-148",                   CODEC_ISO_8859_9 },
	{ "iso-ir-15",                    CODEC_ISO646_IT },
	{ "iso-ir-151",                   CODEC_ISO646_CU },
	{ "iso-ir-153",                   CODEC_ISO_IR_153 },
	{ "iso-ir-157",                   CODEC_ISO_8859_10 },
	{ "iso-ir-16",                    CODEC_ISO646_PT },
	{ "iso-ir-17",                    CODEC_ISO646_ES },
	{ "iso-ir-170",                   CODEC_ISO646_INV },
	{ "iso-ir-179",                   CODEC_ISO_8859_13 },
	{ "iso-ir-182",                   CODEC_ISO_IR_182 },
	{ "iso-ir-193",                   CODEC_UTF8 },
	{ "iso-ir-197",                   CODEC_ISO_IR_197 },
	{ "iso-ir-199",                   CODEC_ISO_8859_14 },
	{ "iso-ir-2",                     CODEC_ISO646_IRV_1973 },
	{ "iso-ir-200",                   CODEC_ISO_IR_200 },
	{ "iso-ir-201",                   CODEC_ISO_IR_201 },
	{ "iso-ir-206",                   CODEC_ISO_IR_206 },
	{ "iso-ir-207",                   CODEC_ISO646_IE },
	{ "iso-ir-21",                    CODEC_ISO646_DE },
	{ "iso-ir-226",                   CODEC_ISO_8859_16 },
	{ "iso-ir-25",                    CODEC_ISO646_FR1 },
	{ "iso-ir-27",                    CODEC_ISO646_LATIN_GR_MIXED },
	{ "iso-ir-4",                     CODEC_ISO646_GB },
	{ "iso-ir-47",                    CODEC_ISO646_VIEWDATA },
	{ "iso-ir-49",                    CODEC_ISO646_INIS_SUBSET },
	{ "iso-ir-57",                    CODEC_ISO646_CN },
	{ "iso-ir-6",                     CODEC_ASCII },
	{ "iso-ir-60",                    CODEC_ISO646_NO },
	{ "iso-ir-61",                    CODEC_ISO646_NO2 },
	{ "iso-ir-68",                    CODEC_ISO_IR_68 },
	{ "iso-ir-69",                    CODEC_ISO646_FR },
	{ "iso-ir-8",                     CODEC_ISO646_SEFI_NATS },
	{ "iso-ir-84",                    CODEC_ISO646_PT2 },
	{ "iso-ir-85",                    CODEC_ISO646_ES2 },
	{ "iso-ir-86",                    CODEC_ISO646_HU },
	{ "iso-ir-9-1",                   CODEC_ISO646_DANO_NATS },
	{ "iso-ir-92",                    CODEC_ISO646_JP_OCR_B },
	{ "iso10646",                     CODEC_UTF32 },
	{ "iso10646/ucs2",                CODEC_UTF16 },
	{ "iso10646/ucs4",                CODEC_UTF32 },
	{ "iso10646/utf-8",               CODEC_UTF8 },
	{ "iso10646/utf8",                CODEC_UTF8 },
	{ "iso2033",                      CODEC_ISO2033 },
	{ "iso5426",                      CODEC_ISO5426 },
	{ "iso5426-2",                    CODEC_ISO5426_2 },
	{ "iso5427",                      CODEC_ISO5427 },
	{ "iso5428",                      CODEC_ISO5428 },
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
	{ "iso646.irv:1991",              CODEC_ASCII },
	{ "iso6937",                      CODEC_CP20269 },
	{ "iso6937-2-25",                 CODEC_CP20269 },
	{ "iso6937-2-add",                CODEC_CP20269 },
	{ "iso8859-1",                    CODEC_ISO_8859_1 },
	{ "iso8859-1-i",                  CODEC_ISO_8859_1 },
	{ "iso8859-10",                   CODEC_ISO_8859_10 },
	{ "iso8859-11",                   CODEC_ISO_8859_11 },
	{ "iso8859-13",                   CODEC_ISO_8859_13 },
	{ "iso8859-14",                   CODEC_ISO_8859_14 },
	{ "iso8859-15",                   CODEC_ISO_8859_15 },
	{ "iso8859-16",                   CODEC_ISO_8859_16 },
	{ "iso8859-2",                    CODEC_ISO_8859_2 },
	{ "iso8859-3",                    CODEC_ISO_8859_3 },
	{ "iso8859-4",                    CODEC_ISO_8859_4 },
	{ "iso8859-5",                    CODEC_ISO_8859_5 },
	{ "iso8859-6",                    CODEC_ISO_8859_6 },
	{ "iso8859-6-i",                  CODEC_ISO_8859_6 },
	{ "iso8859-7",                    CODEC_ISO_8859_7 },
	{ "iso8859-8",                    CODEC_ISO_8859_8 },
	{ "iso8859-8-i",                  CODEC_ISO_8859_8 },
	{ "iso8859-9",                    CODEC_ISO_8859_9 },
	{ "it",                           CODEC_ISO646_IT },
	{ "jis-c-6229-ocr-a",             CODEC_ISO2033 },
	{ "jis-c6220-1969-ro",            CODEC_ISO646_JP },
	{ "jis-c62201969ro",              CODEC_ISO646_JP },
	{ "jis-c6229-1984-b",             CODEC_ISO646_JP_OCR_B },
	{ "jis-c62291984b",               CODEC_ISO646_JP_OCR_B },
	{ "jp",                           CODEC_ISO646_JP },
	{ "jp-ocr-b",                     CODEC_ISO646_JP_OCR_B },
	{ "js",                           CODEC_ISO646_YU },
	{ "jus-i.b1.2",                   CODEC_ISO646_YU },
	{ "kamenicky",                    CODEC_KEYBCS2 },
	{ "kbl",                          CODEC_CP771 },
	{ "keybcs2",                      CODEC_KEYBCS2 },
	{ "koi0",                         CODEC_KOI7_N1 },
	{ "koi7-n0",                      CODEC_KOI7 },
	{ "koi7-n1",                      CODEC_KOI7_N1 },
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
	{ "l7",                           CODEC_ISO_8859_13 },
	{ "l8",                           CODEC_ISO_8859_14 },
	{ "latin0",                       CODEC_ISO_8859_15 },
	{ "latin1",                       CODEC_ISO_8859_1 },
	{ "latin10",                      CODEC_ISO_8859_16 },
	{ "latin2",                       CODEC_ISO_8859_2 },
	{ "latin3",                       CODEC_ISO_8859_3 },
	{ "latin4",                       CODEC_ISO_8859_4 },
	{ "latin5",                       CODEC_ISO_8859_9 },
	{ "latin6",                       CODEC_ISO_8859_10 },
	{ "latin7",                       CODEC_ISO_8859_13 },
	{ "latin8",                       CODEC_ISO_8859_14 },
	{ "latin9",                       CODEC_ISO_8859_15 },
	{ "lics",                         CODEC_LICS },
	{ "lst-1283",                     CODEC_CP774 },
	{ "lst-1284",                     CODEC_CP772 },
	{ "lst-1284:1993",                CODEC_CP772 },
	{ "lst-1590-3",                   CODEC_CP1257 },
	{ "ly1",                          CODEC_LY1 },
	{ "mac",                          CODEC_CP1275 },
	{ "mac-os-thai",                  CODEC_MAC_OS_THAI },
	{ "macarabic",                    CODEC_CP10004 },
	{ "macfarsi",                     CODEC_X_MAC_FARSI },
	{ "macintosh",                    CODEC_CP1275 },
	{ "macintosh-font-x",             CODEC_MACINTOSH_FONT_X },
	{ "macintosh-latin",              CODEC_MACINTOSH_LATIN },
	{ "macroman",                     CODEC_CP1275 },
	{ "maz",                          CODEC_CP667 },
	{ "mazovia",                      CODEC_CP667 },
	{ "mik",                          CODEC_MIK },
	{ "ms-10206",                     CODEC_ISO646_DE },
	{ "ms874",                        CODEC_CP1162 },
	{ "msdos-1252",                   CODEC_MSDOS1252 },
	{ "msz-7795.3",                   CODEC_ISO646_HU },
	{ "nc-nc0-10",                    CODEC_ISO646_CU },
	{ "nc-nc0-10:81",                 CODEC_ISO646_CU },
	{ "nc-nc10",                      CODEC_ISO646_CU },
	{ "nec-867",                      CODEC_KEYBCS2 },
	{ "nec-apc",                      CODEC_NEC_APC },
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
	{ "osf10020",                     CODEC_ASCII },
	{ "osf100201b5",                  CODEC_CP437 },
	{ "osf10100",                     CODEC_UTF16 },
	{ "osf10101",                     CODEC_UTF16 },
	{ "osf10102",                     CODEC_UTF16 },
	{ "osf10104",                     CODEC_UTF32 },
	{ "osf10105",                     CODEC_UTF32 },
	{ "osf10106",                     CODEC_UTF32 },
	{ "osf5010001",                   CODEC_UTF8 },
	{ "palmos",                       CODEC_PALMOS },
	{ "pc-multilingual-850+euro",     CODEC_CP858 },
	{ "postscript",                   CODEC_CP1276 },
	{ "postscript-standard-encoding", CODEC_CP1276 },
	{ "pt",                           CODEC_ISO646_PT },
	{ "pt2",                          CODEC_ISO646_PT2 },
	{ "pttc/bcd",                     CODEC_CP355 },
	{ "pttc/bcd-c",                   CODEC_CP358 },
	{ "pttc/bcd-d",                   CODEC_CP359 },
	{ "pttc/bcd-h",                   CODEC_CP357 },
	{ "pttc/bcd-m",                   CODEC_CP359 },
	{ "rst-2018-91",                  CODEC_CP1125 },
	{ "ruscii",                       CODEC_CP1125 },
	{ "ruslat",                       CODEC_CP3012 },
	{ "se",                           CODEC_ISO646_SE },
	{ "se2",                          CODEC_ISO646_SE2 },
	{ "sen-850200-b",                 CODEC_ISO646_SE },
	{ "sen-850200-c",                 CODEC_ISO646_SE2 },
	{ "short-koi",                    CODEC_KOI7_N2 },
	{ "sr-14111",                     CODEC_ISO_8859_16 },
	{ "ss636127",                     CODEC_ISO646_SE },
	{ "st-sev-358-88",                CODEC_ISO_IR_153 },
	{ "standardencoding",             CODEC_CP1276 },
	{ "strk1048-2002",                CODEC_KZ_1048 },
	{ "t.51",                         CODEC_CP20269 },
	{ "t.61",                         CODEC_CP1036 },
	{ "tr8dec",                       CODEC_CP1288 },
	{ "ucs-2",                        CODEC_UTF16 },
	{ "ucs-2be",                      CODEC_UTF16BE },
	{ "ucs-2le",                      CODEC_UTF16LE },
	{ "ucs-4",                        CODEC_UTF32 },
	{ "ucs-4be",                      CODEC_UTF32BE },
	{ "ucs-4le",                      CODEC_UTF32LE },
	{ "ucs2",                         CODEC_UTF16 },
	{ "ucs4",                         CODEC_UTF32 },
	{ "uk",                           CODEC_ISO646_GB },
	{ "unicodebig",                   CODEC_UTF16BE },
	{ "unicodelittle",                CODEC_UTF16LE },
	{ "us",                           CODEC_ASCII },
	{ "us-ascii",                     CODEC_ASCII },
	{ "utf-16",                       CODEC_UTF16 },
	{ "utf-16be",                     CODEC_UTF16BE },
	{ "utf-16le",                     CODEC_UTF16LE },
	{ "utf-32",                       CODEC_UTF32 },
	{ "utf-32be",                     CODEC_UTF32BE },
	{ "utf-32le",                     CODEC_UTF32LE },
	{ "utf-8",                        CODEC_UTF8 },
	{ "utf16",                        CODEC_UTF16 },
	{ "utf16be",                      CODEC_UTF16BE },
	{ "utf16le",                      CODEC_UTF16LE },
	{ "utf32",                        CODEC_UTF32 },
	{ "utf32be",                      CODEC_UTF32BE },
	{ "utf32le",                      CODEC_UTF32LE },
	{ "utf8",                         CODEC_UTF8 },
	{ "wchar-t",                      CODEC_WCHAR_T },
	{ "we8dec",                       CODEC_CP1100 },
	{ "we8iso8859p1",                 CODEC_ISO_8859_1 },
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
	{ "windows-13488",                CODEC_UTF16 },
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
	{ "windows-28603",                CODEC_ISO_8859_13 },
	{ "windows-28604",                CODEC_ISO_8859_14 },
	{ "windows-28605",                CODEC_ISO_8859_15 },
	{ "windows-28606",                CODEC_ISO_8859_16 },
	{ "windows-38591",                CODEC_ISO_8859_1 },
	{ "windows-38596",                CODEC_ISO_8859_6 },
	{ "windows-38598",                CODEC_ISO_8859_8 },
	{ "windows-65001",                CODEC_UTF8 },
	{ "windows-874",                  CODEC_CP1162 },
	{ "windows-extended",             CODEC_CP1004 },
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
	{ "x-windows-874",                CODEC_CP1162 },
	{ "yu",                           CODEC_ISO646_YU },
};
/*[[[end]]]*/


/* Try to normalize the name of the given codec:
 *
 * - Prefix: "OEM" <SEP> <NUMBER>    --> "OEM" <NUMBER>
 * - Prefix: "IBM" <SEP> <NUMBER>    --> "IBM" <NUMBER>
 * - Prefix: "CP" <SEP> <NUMBER>     --> "CP" <NUMBER>
 * - Prefix: "LATIN" <SEP> <NUMBER>  --> "LATIN" <NUMBER>
 * - Prefix: "L" <SEP> <NUMBER>      --> "L" <NUMBER>
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
	ptr = buf;
	end = buf + CODE_NAME_MAXLEN;
	nameend = name + namelen;
	while (isspace(*name))
		++name;
	if ((name[0] == 'O' || name[0] == 'o') &&
	    (name[1] == 'E' || name[1] == 'e') &&
	    (name[2] == 'M' || name[2] == 'm') &&
	    issep(name[3]) && isdigit(name[4])) {
		/* Convert: `OEM-xxx' | `OEM_xxx' -> `OEMxxx' */
		*ptr++ = 'o';
		*ptr++ = 'e';
		*ptr++ = 'm';
		name += 4;
	} else if ((name[0] == 'I' || name[0] == 'i') &&
	           (name[1] == 'B' || name[1] == 'b') &&
	           (name[2] == 'M' || name[2] == 'm') &&
	           issep(name[3]) && isdigit(name[4])) {
		/* Convert: `IBM-xxx' | `IBM_xxx' -> `IBMxxx' */
		*ptr++ = 'i';
		*ptr++ = 'b';
		*ptr++ = 'm';
		name += 4;
	} else if ((name[0] == 'I' || name[0] == 'i') &&
	           (name[1] == 'S' || name[1] == 's') &&
	           (name[2] == 'O' || name[2] == 'o') &&
	           issep(name[3]) && isdigit(name[4])) {
		/* Convert: `ISO-xxx' | `ISO_xxx' -> `ISOxxx' */
		*ptr++ = 'i';
		*ptr++ = 's';
		*ptr++ = 'o';
		name += 4;
	} else if ((name[0] == 'C' || name[0] == 'c') &&
	           (name[1] == 'P' || name[1] == 'p') &&
	           issep(name[2]) && isdigit(name[3])) {
		/* Convert: `CP-xxx' | `CP_xxx' -> `CPxxx' */
		*ptr++ = 'c';
		*ptr++ = 'p';
		name += 3;
	} else if ((name[0] == 'L' || name[0] == 'l') &&
	           (name[1] == 'A' || name[1] == 'a') &&
	           (name[2] == 'T' || name[2] == 't') &&
	           (name[3] == 'I' || name[3] == 'i') &&
	           (name[4] == 'N' || name[4] == 'n') &&
	           issep(name[5]) && isdigit(name[6])) {
		/* Convert: `LATIN-xxx' | `LATIN_xxx' -> `LATINxxx' */
		*ptr++ = 'l';
		*ptr++ = 'a';
		*ptr++ = 't';
		*ptr++ = 'i';
		*ptr++ = 'n';
		name += 6;
	} else if ((name[0] == 'K' || name[0] == 'k') &&
	           (name[1] == 'O' || name[1] == 'o') &&
	           (name[2] == 'I' || name[2] == 'i') &&
	           issep(name[3]) && name[4] == '8') {
		/* Convert: `KOI-8xxx' -> `KOI8xxx' */
		*ptr++ = 'k';
		*ptr++ = 'o';
		*ptr++ = 'i';
		*ptr++ = '8';
		name += 5;
	} else if ((name[0] == 'L' || name[0] == 'l') &&
	           issep(name[1]) && isdigit(name[2])) {
		/* Convert: `l-xxx' | `l_xxx' -> `lxxx' */
		*ptr++ = 'l';
		name += 2;
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
                                                   /*[in|out]*/ uintptr_t *__restrict pflags) {
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


DECL_END

#endif /* !GUARD_LIBICONV_CODECS_C */
