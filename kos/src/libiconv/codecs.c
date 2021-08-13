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
print("PRIVATE struct codec_db_entry codec_db[] = {");
local longestNameReprLen = name2codec.keys.each.encode("c-escape").length > ...;
for (local name: name2codec.keys.sorted()) {
	local nameRepr = name.encode("c-escape");
	print("	{ \"", nameRepr, "\", ", " " * (longestNameReprLen - #nameRepr), name2codec[name], " },");
}
print("};");
]]]*/
#define CODE_NAME_MAXLEN 24
struct codec_db_entry {
	char         cdbe_name[CEIL_ALIGN(25, __SIZEOF_INT__)];
	unsigned int cdbe_codec; /* The associated codec. */
};

PRIVATE struct codec_db_entry codec_db[] = {
	{ "10646-1:1993",             CODEC_UTF32 },
	{ "10646-1:1993/ucs4",        CODEC_UTF32 },
	{ "437",                      CODEC_CP437 },
	{ "850",                      CODEC_CP850 },
	{ "851",                      CODEC_CP851 },
	{ "852",                      CODEC_CP852 },
	{ "855",                      CODEC_CP855 },
	{ "857",                      CODEC_CP857 },
	{ "860",                      CODEC_CP860 },
	{ "861",                      CODEC_CP861 },
	{ "862",                      CODEC_CP862 },
	{ "863",                      CODEC_CP863 },
	{ "865",                      CODEC_CP865 },
	{ "866",                      CODEC_CP866 },
	{ "869",                      CODEC_CP869 },
	{ "ansi-x3.4",                CODEC_ASCII },
	{ "ansi-x3.4-1968",           CODEC_ASCII },
	{ "ansi-x3.4-1986",           CODEC_ASCII },
	{ "arabic",                   CODEC_ISO_8859_6 },
	{ "ascii",                    CODEC_ASCII },
	{ "asmo-708",                 CODEC_ISO_8859_6 },
	{ "bn-74/3101-1",             CODEC_ISO646_PL },
	{ "bs-4730",                  CODEC_ISO646_GB },
	{ "bulgaria-pc",              CODEC_MIK },
	{ "ca",                       CODEC_ISO646_CA },
	{ "cn",                       CODEC_ISO646_CN },
	{ "cp-ar",                    CODEC_CP868 },
	{ "cp-gr",                    CODEC_CP869 },
	{ "cp-is",                    CODEC_CP861 },
	{ "cp1009",                   CODEC_ISO646_IRV_1983 },
	{ "cp1011",                   CODEC_ISO646_DE },
	{ "cp1014",                   CODEC_ISO646_ES2 },
	{ "cp1017",                   CODEC_ISO646_DK },
	{ "cp1019",                   CODEC_ISO646_NL },
	{ "cp1020",                   CODEC_ISO646_CA },
	{ "cp1021",                   CODEC_ISO646_SWI_NRCS },
	{ "cp1023",                   CODEC_ISO646_ES },
	{ "cp1041",                   CODEC_CP1041 },
	{ "cp1057",                   CODEC_CP1057 },
	{ "cp1098",                   CODEC_CP1098 },
	{ "cp1101",                   CODEC_ISO646_GB_NRCS },
	{ "cp1102",                   CODEC_ISO646_NL_NRCS },
	{ "cp1103",                   CODEC_ISO646_FI_NRCS },
	{ "cp1105",                   CODEC_ISO646_DK_NO_NRCS },
	{ "cp1106",                   CODEC_ISO646_SE_NRCS },
	{ "cp1107",                   CODEC_ISO646_DK_NO_ALT_NRCS },
	{ "cp1116",                   CODEC_CP1116 },
	{ "cp1117",                   CODEC_CP1117 },
	{ "cp1118",                   CODEC_CP774 },
	{ "cp1119",                   CODEC_CP772 },
	{ "cp1125",                   CODEC_CP1125 },
	{ "cp1131",                   CODEC_CP1131 },
	{ "cp17248",                  CODEC_CP17248 },
	{ "cp20106",                  CODEC_ISO646_DE },
	{ "cp3012",                   CODEC_CP3012 },
	{ "cp367",                    CODEC_ASCII },
	{ "cp437",                    CODEC_CP437 },
	{ "cp667",                    CODEC_CP667 },
	{ "cp668",                    CODEC_CP668 },
	{ "cp708",                    CODEC_CP708 },
	{ "cp720",                    CODEC_CP720 },
	{ "cp737",                    CODEC_CP737 },
	{ "cp770",                    CODEC_CP770 },
	{ "cp771",                    CODEC_CP771 },
	{ "cp772",                    CODEC_CP772 },
	{ "cp773",                    CODEC_CP773 },
	{ "cp774",                    CODEC_CP774 },
	{ "cp775",                    CODEC_CP775 },
	{ "cp790",                    CODEC_CP667 },
	{ "cp808",                    CODEC_CP808 },
	{ "cp819",                    CODEC_ISO_8859_1 },
	{ "cp848",                    CODEC_CP848 },
	{ "cp849",                    CODEC_CP849 },
	{ "cp850",                    CODEC_CP850 },
	{ "cp851",                    CODEC_CP851 },
	{ "cp852",                    CODEC_CP852 },
	{ "cp853",                    CODEC_CP853 },
	{ "cp855",                    CODEC_CP855 },
	{ "cp856",                    CODEC_CP856 },
	{ "cp857",                    CODEC_CP857 },
	{ "cp858",                    CODEC_CP858 },
	{ "cp859",                    CODEC_CP859 },
	{ "cp860",                    CODEC_CP860 },
	{ "cp861",                    CODEC_CP861 },
	{ "cp862",                    CODEC_CP862 },
	{ "cp863",                    CODEC_CP863 },
	{ "cp864",                    CODEC_CP864 },
	{ "cp865",                    CODEC_CP865 },
	{ "cp866",                    CODEC_CP866 },
	{ "cp866nav",                 CODEC_CP1125 },
	{ "cp866u",                   CODEC_CP1125 },
	{ "cp867",                    CODEC_CP867 },
	{ "cp868",                    CODEC_CP868 },
	{ "cp869",                    CODEC_CP869 },
	{ "cp872",                    CODEC_CP872 },
	{ "cp897",                    CODEC_CP897 },
	{ "cp901",                    CODEC_CP901 },
	{ "cp902",                    CODEC_CP902 },
	{ "cp912",                    CODEC_CP912 },
	{ "cp915",                    CODEC_CP915 },
	{ "cp921",                    CODEC_CP921 },
	{ "cp922",                    CODEC_CP922 },
	{ "cp991",                    CODEC_CP667 },
	{ "csa-z243.4-1985-1",        CODEC_ISO646_CA },
	{ "csa-z243.4-1985-2",        CODEC_ISO646_CA2 },
	{ "csa-z243.419851",          CODEC_ISO646_CA },
	{ "csa-z243.419852",          CODEC_ISO646_CA2 },
	{ "csa7-1",                   CODEC_ISO646_CA },
	{ "csa7-2",                   CODEC_ISO646_CA2 },
	{ "csascii",                  CODEC_ASCII },
	{ "csiso10swedish",           CODEC_ISO646_SE },
	{ "csiso11swedishfornames",   CODEC_ISO646_SE2 },
	{ "csiso121canadian1",        CODEC_ISO646_CA },
	{ "csiso122canadian2",        CODEC_ISO646_CA2 },
	{ "csiso141jusib1002",        CODEC_ISO646_YU },
	{ "csiso14jisc6220ro",        CODEC_ISO646_JP },
	{ "csiso151cuba",             CODEC_ISO646_CU },
	{ "csiso15italian",           CODEC_ISO646_IT },
	{ "csiso16portugese",         CODEC_ISO646_PT },
	{ "csiso17spanish",           CODEC_ISO646_ES },
	{ "csiso21german",            CODEC_ISO646_DE },
	{ "csiso25french",            CODEC_ISO646_FR1 },
	{ "csiso4unitedkingdom",      CODEC_ISO646_GB },
	{ "csiso58gb1988",            CODEC_ISO646_CN },
	{ "csiso60danishnorwegian",   CODEC_ISO646_NO },
	{ "csiso60norwegian1",        CODEC_ISO646_NO },
	{ "csiso61norwegian2",        CODEC_ISO646_NO2 },
	{ "csiso646danish",           CODEC_ISO646_DK },
	{ "csiso69french",            CODEC_ISO646_FR },
	{ "csiso84portuguese2",       CODEC_ISO646_PT2 },
	{ "csiso85spanish2",          CODEC_ISO646_ES2 },
	{ "csiso86hungarian",         CODEC_ISO646_HU },
	{ "csiso92jisc62991984b",     CODEC_ISO646_JP_OCR_B },
	{ "csisolatin1",              CODEC_ISO_8859_1 },
	{ "csisolatin2",              CODEC_ISO_8859_2 },
	{ "csisolatin3",              CODEC_ISO_8859_3 },
	{ "csisolatin4",              CODEC_ISO_8859_4 },
	{ "csisolatin5",              CODEC_ISO_8859_9 },
	{ "csisolatin6",              CODEC_ISO_8859_10 },
	{ "csisolatin7",              CODEC_ISO_8859_13 },
	{ "csisolatinarabic",         CODEC_ISO_8859_6 },
	{ "csisolatincyrillic",       CODEC_ISO_8859_5 },
	{ "csisolatingreek",          CODEC_ISO_8859_7 },
	{ "csisolatinhebrew",         CODEC_ISO_8859_8 },
	{ "csksc5636",                CODEC_ISO646_KR },
	{ "cspc850multilingual",      CODEC_CP850 },
	{ "cspc862latinhebrew",       CODEC_CP862 },
	{ "cspc8codepage437",         CODEC_CP437 },
	{ "cspcp852",                 CODEC_CP852 },
	{ "csucs4",                   CODEC_UTF32 },
	{ "cuba",                     CODEC_ISO646_CU },
	{ "cyrillic",                 CODEC_ISO_8859_5 },
	{ "d7dec",                    CODEC_ISO646_DE },
	{ "de",                       CODEC_ISO646_DE },
	{ "din-66003",                CODEC_ISO646_DE },
	{ "din-66303",                CODEC_DIN_66303 },
	{ "dk",                       CODEC_ISO646_DK },
	{ "dos-895",                  CODEC_KEYBCS2 },
	{ "drv8",                     CODEC_DIN_66303 },
	{ "ds-2089",                  CODEC_ISO646_DK },
	{ "ds2089",                   CODEC_ISO646_DK },
	{ "ecma-114",                 CODEC_ISO_8859_6 },
	{ "ecma-118",                 CODEC_ISO_8859_7 },
	{ "elot-928",                 CODEC_ISO_8859_7 },
	{ "es",                       CODEC_ISO646_ES },
	{ "es2",                      CODEC_ISO646_ES2 },
	{ "estonia-iso-8",            CODEC_CP922 },
	{ "fi",                       CODEC_ISO646_SE },
	{ "fr",                       CODEC_ISO646_FR },
	{ "gb",                       CODEC_ISO646_GB },
	{ "gb-1988-80",               CODEC_ISO646_CN },
	{ "gb-198880",                CODEC_ISO646_CN },
	{ "german",                   CODEC_ISO646_DE },
	{ "greek",                    CODEC_ISO_8859_7 },
	{ "greek8",                   CODEC_ISO_8859_7 },
	{ "hebrew",                   CODEC_ISO_8859_8 },
	{ "hp-pc-8",                  CODEC_CP1057 },
	{ "hu",                       CODEC_ISO646_HU },
	{ "ibm1009",                  CODEC_ISO646_IRV_1983 },
	{ "ibm1011",                  CODEC_ISO646_DE },
	{ "ibm1019",                  CODEC_ISO646_NL },
	{ "ibm1021",                  CODEC_ISO646_SWI_NRCS },
	{ "ibm1098",                  CODEC_CP1098 },
	{ "ibm1101",                  CODEC_ISO646_GB_NRCS },
	{ "ibm1102",                  CODEC_ISO646_NL_NRCS },
	{ "ibm1103",                  CODEC_ISO646_FI_NRCS },
	{ "ibm1105",                  CODEC_ISO646_DK_NO_NRCS },
	{ "ibm1106",                  CODEC_ISO646_SE_NRCS },
	{ "ibm1107",                  CODEC_ISO646_DK_NO_ALT_NRCS },
	{ "ibm1111",                  CODEC_ISO_8859_2 },
	{ "ibm1116",                  CODEC_CP1116 },
	{ "ibm1117",                  CODEC_CP1117 },
	{ "ibm1118",                  CODEC_CP774 },
	{ "ibm367",                   CODEC_ASCII },
	{ "ibm437",                   CODEC_CP437 },
	{ "ibm708",                   CODEC_CP708 },
	{ "ibm720",                   CODEC_CP720 },
	{ "ibm737",                   CODEC_CP737 },
	{ "ibm775",                   CODEC_CP775 },
	{ "ibm819",                   CODEC_ISO_8859_1 },
	{ "ibm850",                   CODEC_CP850 },
	{ "ibm851",                   CODEC_CP851 },
	{ "ibm852",                   CODEC_CP852 },
	{ "ibm853",                   CODEC_CP853 },
	{ "ibm855",                   CODEC_CP855 },
	{ "ibm856",                   CODEC_CP856 },
	{ "ibm857",                   CODEC_CP857 },
	{ "ibm858",                   CODEC_CP858 },
	{ "ibm859",                   CODEC_CP859 },
	{ "ibm860",                   CODEC_CP860 },
	{ "ibm861",                   CODEC_CP861 },
	{ "ibm862",                   CODEC_CP862 },
	{ "ibm863",                   CODEC_CP863 },
	{ "ibm864",                   CODEC_CP864 },
	{ "ibm865",                   CODEC_CP865 },
	{ "ibm866",                   CODEC_CP866 },
	{ "ibm868",                   CODEC_CP868 },
	{ "ibm869",                   CODEC_CP869 },
	{ "ibm902",                   CODEC_CP902 },
	{ "ibm912",                   CODEC_CP912 },
	{ "ibm915",                   CODEC_CP915 },
	{ "ibm921",                   CODEC_CP921 },
	{ "ibm922",                   CODEC_CP922 },
	{ "iso-10646",                CODEC_UTF32 },
	{ "iso-10646/ucs2",           CODEC_UTF16 },
	{ "iso-10646/ucs4",           CODEC_UTF32 },
	{ "iso-10646/utf-8",          CODEC_UTF8 },
	{ "iso-10646/utf8",           CODEC_UTF8 },
	{ "iso-646.irv:1991",         CODEC_ASCII },
	{ "iso-8859-1",               CODEC_ISO_8859_1 },
	{ "iso-8859-10",              CODEC_ISO_8859_10 },
	{ "iso-8859-11",              CODEC_ISO_8859_11 },
	{ "iso-8859-13",              CODEC_ISO_8859_13 },
	{ "iso-8859-14",              CODEC_ISO_8859_14 },
	{ "iso-8859-15",              CODEC_ISO_8859_15 },
	{ "iso-8859-16",              CODEC_ISO_8859_16 },
	{ "iso-8859-2",               CODEC_ISO_8859_2 },
	{ "iso-8859-3",               CODEC_ISO_8859_3 },
	{ "iso-8859-4",               CODEC_ISO_8859_4 },
	{ "iso-8859-5",               CODEC_ISO_8859_5 },
	{ "iso-8859-6",               CODEC_ISO_8859_6 },
	{ "iso-8859-7",               CODEC_ISO_8859_7 },
	{ "iso-8859-8",               CODEC_ISO_8859_8 },
	{ "iso-8859-9",               CODEC_ISO_8859_9 },
	{ "iso-celtic",               CODEC_ISO_8859_14 },
	{ "iso-ir-10",                CODEC_ISO646_SE },
	{ "iso-ir-100",               CODEC_ISO_8859_1 },
	{ "iso-ir-101",               CODEC_ISO_8859_2 },
	{ "iso-ir-102",               CODEC_ISO646_T_61 },
	{ "iso-ir-109",               CODEC_ISO_8859_3 },
	{ "iso-ir-11",                CODEC_ISO646_SE2 },
	{ "iso-ir-110",               CODEC_ISO_8859_4 },
	{ "iso-ir-121",               CODEC_ISO646_CA },
	{ "iso-ir-122",               CODEC_ISO646_CA2 },
	{ "iso-ir-126",               CODEC_ISO_8859_7 },
	{ "iso-ir-127",               CODEC_ISO_8859_6 },
	{ "iso-ir-138",               CODEC_ISO_8859_8 },
	{ "iso-ir-14",                CODEC_ISO646_JP },
	{ "iso-ir-144",               CODEC_ISO_8859_5 },
	{ "iso-ir-148",               CODEC_ISO_8859_9 },
	{ "iso-ir-15",                CODEC_ISO646_IT },
	{ "iso-ir-151",               CODEC_ISO646_CU },
	{ "iso-ir-157",               CODEC_ISO_8859_10 },
	{ "iso-ir-16",                CODEC_ISO646_PT },
	{ "iso-ir-17",                CODEC_ISO646_ES },
	{ "iso-ir-170",               CODEC_ISO646_INV },
	{ "iso-ir-179",               CODEC_ISO_8859_13 },
	{ "iso-ir-182",               CODEC_ISO_IR_182 },
	{ "iso-ir-193",               CODEC_UTF8 },
	{ "iso-ir-197",               CODEC_ISO_IR_197 },
	{ "iso-ir-199",               CODEC_ISO_8859_14 },
	{ "iso-ir-2",                 CODEC_ISO646_IRV_1973 },
	{ "iso-ir-200",               CODEC_ISO_IR_200 },
	{ "iso-ir-207",               CODEC_ISO646_IE },
	{ "iso-ir-21",                CODEC_ISO646_DE },
	{ "iso-ir-226",               CODEC_ISO_8859_16 },
	{ "iso-ir-25",                CODEC_ISO646_FR1 },
	{ "iso-ir-27",                CODEC_ISO646_LATIN_GR_MIXED },
	{ "iso-ir-4",                 CODEC_ISO646_GB },
	{ "iso-ir-47",                CODEC_ISO646_VIEWDATA },
	{ "iso-ir-49",                CODEC_ISO646_INIS_SUBSET },
	{ "iso-ir-57",                CODEC_ISO646_CN },
	{ "iso-ir-6",                 CODEC_ASCII },
	{ "iso-ir-60",                CODEC_ISO646_NO },
	{ "iso-ir-61",                CODEC_ISO646_NO2 },
	{ "iso-ir-69",                CODEC_ISO646_FR },
	{ "iso-ir-8",                 CODEC_ISO646_SEFI_NATS },
	{ "iso-ir-84",                CODEC_ISO646_PT2 },
	{ "iso-ir-85",                CODEC_ISO646_ES2 },
	{ "iso-ir-86",                CODEC_ISO646_HU },
	{ "iso-ir-9",                 CODEC_ISO646_DANO_NATS },
	{ "iso-ir-92",                CODEC_ISO646_JP_OCR_B },
	{ "iso646-ca",                CODEC_ISO646_CA },
	{ "iso646-ca2",               CODEC_ISO646_CA2 },
	{ "iso646-cn",                CODEC_ISO646_CN },
	{ "iso646-cu",                CODEC_ISO646_CU },
	{ "iso646-de",                CODEC_ISO646_DE },
	{ "iso646-dk",                CODEC_ISO646_DK },
	{ "iso646-es",                CODEC_ISO646_ES },
	{ "iso646-es2",               CODEC_ISO646_ES2 },
	{ "iso646-fi",                CODEC_ISO646_SE },
	{ "iso646-fr",                CODEC_ISO646_FR },
	{ "iso646-fr1",               CODEC_ISO646_FR1 },
	{ "iso646-gb",                CODEC_ISO646_GB },
	{ "iso646-hu",                CODEC_ISO646_HU },
	{ "iso646-ie",                CODEC_ISO646_IE },
	{ "iso646-is",                CODEC_ISO646_IS },
	{ "iso646-it",                CODEC_ISO646_IT },
	{ "iso646-jp",                CODEC_ISO646_JP },
	{ "iso646-jp-ocr-b",          CODEC_ISO646_JP_OCR_B },
	{ "iso646-kr",                CODEC_ISO646_KR },
	{ "iso646-mt",                CODEC_ISO646_MT },
	{ "iso646-nl",                CODEC_ISO646_NL },
	{ "iso646-no",                CODEC_ISO646_NO },
	{ "iso646-no2",               CODEC_ISO646_NO2 },
	{ "iso646-pt",                CODEC_ISO646_PT },
	{ "iso646-pt2",               CODEC_ISO646_PT2 },
	{ "iso646-se",                CODEC_ISO646_SE },
	{ "iso646-se2",               CODEC_ISO646_SE2 },
	{ "iso646-us",                CODEC_ASCII },
	{ "iso646-yu",                CODEC_ISO646_YU },
	{ "it",                       CODEC_ISO646_IT },
	{ "jis-c6220-1969-ro",        CODEC_ISO646_JP },
	{ "jis-c62201969ro",          CODEC_ISO646_JP },
	{ "jis-c6229-1984-b",         CODEC_ISO646_JP_OCR_B },
	{ "jis-c62291984b",           CODEC_ISO646_JP_OCR_B },
	{ "jp",                       CODEC_ISO646_JP },
	{ "jp-ocr-b",                 CODEC_ISO646_JP_OCR_B },
	{ "js",                       CODEC_ISO646_YU },
	{ "jus-i.b1.2",               CODEC_ISO646_YU },
	{ "kamenicky",                CODEC_KEYBCS2 },
	{ "kbl",                      CODEC_CP771 },
	{ "keybcs2",                  CODEC_KEYBCS2 },
	{ "koi-8-n1",                 CODEC_KOI_8_N1 },
	{ "koi-8-n2",                 CODEC_KOI_8_N2 },
	{ "ks-x-1003",                CODEC_ISO646_KR },
	{ "ksc5636",                  CODEC_ISO646_KR },
	{ "ksc5636-1989",             CODEC_ISO646_KR },
	{ "l1",                       CODEC_ISO_8859_1 },
	{ "l10",                      CODEC_ISO_8859_16 },
	{ "l2",                       CODEC_ISO_8859_2 },
	{ "l3",                       CODEC_ISO_8859_3 },
	{ "l4",                       CODEC_ISO_8859_4 },
	{ "l5",                       CODEC_ISO_8859_9 },
	{ "l6",                       CODEC_ISO_8859_10 },
	{ "l7",                       CODEC_ISO_8859_13 },
	{ "l8",                       CODEC_ISO_8859_14 },
	{ "latin0",                   CODEC_ISO_8859_15 },
	{ "latin1",                   CODEC_ISO_8859_1 },
	{ "latin10",                  CODEC_ISO_8859_16 },
	{ "latin2",                   CODEC_ISO_8859_2 },
	{ "latin3",                   CODEC_ISO_8859_3 },
	{ "latin4",                   CODEC_ISO_8859_4 },
	{ "latin5",                   CODEC_ISO_8859_9 },
	{ "latin6",                   CODEC_ISO_8859_10 },
	{ "latin7",                   CODEC_ISO_8859_13 },
	{ "latin8",                   CODEC_ISO_8859_14 },
	{ "latin9",                   CODEC_ISO_8859_15 },
	{ "lst-1283",                 CODEC_CP774 },
	{ "lst-1284",                 CODEC_CP772 },
	{ "lst-1284:1993",            CODEC_CP772 },
	{ "maz",                      CODEC_CP667 },
	{ "mazovia",                  CODEC_CP667 },
	{ "mik",                      CODEC_MIK },
	{ "ms-10206",                 CODEC_ISO646_DE },
	{ "msz-7795.3",               CODEC_ISO646_HU },
	{ "nc-nc0-10",                CODEC_ISO646_CU },
	{ "nc-nc0-10:81",             CODEC_ISO646_CU },
	{ "nc-nc10",                  CODEC_ISO646_CU },
	{ "nec-867",                  CODEC_KEYBCS2 },
	{ "nf-z-62-10",               CODEC_ISO646_FR },
	{ "nf-z-62-10-(1973)",        CODEC_ISO646_FR1 },
	{ "nf-z-62-10-(1983)",        CODEC_ISO646_FR },
	{ "nf-z-62-10-1973",          CODEC_ISO646_FR1 },
	{ "nf-z-62-10-1983",          CODEC_ISO646_FR },
	{ "nf-z-62010",               CODEC_ISO646_FR },
	{ "nf-z-62010-1973",          CODEC_ISO646_FR1 },
	{ "no",                       CODEC_ISO646_NO },
	{ "no2",                      CODEC_ISO646_NO2 },
	{ "ns-4551-1",                CODEC_ISO646_NO },
	{ "ns-4551-2",                CODEC_ISO646_NO2 },
	{ "ns-45511",                 CODEC_ISO646_NO },
	{ "ns-45512",                 CODEC_ISO646_NO2 },
	{ "oem720",                   CODEC_CP720 },
	{ "oem737",                   CODEC_CP737 },
	{ "oem775",                   CODEC_CP775 },
	{ "oem850",                   CODEC_CP850 },
	{ "oem855",                   CODEC_CP855 },
	{ "oem857",                   CODEC_CP857 },
	{ "oem858",                   CODEC_CP858 },
	{ "oem860",                   CODEC_CP860 },
	{ "oem861",                   CODEC_CP861 },
	{ "oem862",                   CODEC_CP862 },
	{ "oem863",                   CODEC_CP863 },
	{ "oem865",                   CODEC_CP865 },
	{ "oem869",                   CODEC_CP869 },
	{ "oemus",                    CODEC_CP437 },
	{ "osf10020",                 CODEC_ASCII },
	{ "osf100201b5",              CODEC_CP437 },
	{ "osf10100",                 CODEC_UTF16 },
	{ "osf10101",                 CODEC_UTF16 },
	{ "osf10102",                 CODEC_UTF16 },
	{ "osf10104",                 CODEC_UTF32 },
	{ "osf10105",                 CODEC_UTF32 },
	{ "osf10106",                 CODEC_UTF32 },
	{ "osf5010001",               CODEC_UTF8 },
	{ "pc-multilingual-850+euro", CODEC_CP858 },
	{ "pt",                       CODEC_ISO646_PT },
	{ "pt2",                      CODEC_ISO646_PT2 },
	{ "rst-2018-91",              CODEC_CP1125 },
	{ "ruscii",                   CODEC_CP1125 },
	{ "ruslat",                   CODEC_CP3012 },
	{ "se",                       CODEC_ISO646_SE },
	{ "se2",                      CODEC_ISO646_SE2 },
	{ "sen-850200-b",             CODEC_ISO646_SE },
	{ "sen-850200-c",             CODEC_ISO646_SE2 },
	{ "ss636127",                 CODEC_ISO646_SE },
	{ "ucs-2",                    CODEC_UTF16 },
	{ "ucs-2be",                  CODEC_UTF16BE },
	{ "ucs-2le",                  CODEC_UTF16LE },
	{ "ucs-4",                    CODEC_UTF32 },
	{ "ucs-4be",                  CODEC_UTF32BE },
	{ "ucs-4le",                  CODEC_UTF32LE },
	{ "ucs2",                     CODEC_UTF16 },
	{ "ucs4",                     CODEC_UTF32 },
	{ "uk",                       CODEC_ISO646_GB },
	{ "unicodebig",               CODEC_UTF16BE },
	{ "unicodelittle",            CODEC_UTF16LE },
	{ "us",                       CODEC_ASCII },
	{ "us-ascii",                 CODEC_ASCII },
	{ "utf-16",                   CODEC_UTF16 },
	{ "utf-16be",                 CODEC_UTF16BE },
	{ "utf-16le",                 CODEC_UTF16LE },
	{ "utf-32",                   CODEC_UTF32 },
	{ "utf-32be",                 CODEC_UTF32BE },
	{ "utf-32le",                 CODEC_UTF32LE },
	{ "utf-8",                    CODEC_UTF8 },
	{ "utf16",                    CODEC_UTF16 },
	{ "utf16be",                  CODEC_UTF16BE },
	{ "utf16le",                  CODEC_UTF16LE },
	{ "utf32",                    CODEC_UTF32 },
	{ "utf32be",                  CODEC_UTF32BE },
	{ "utf32le",                  CODEC_UTF32LE },
	{ "utf8",                     CODEC_UTF8 },
	{ "wchar-t",                  CODEC_WCHAR_T },
	{ "yu",                       CODEC_ISO646_YU },
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
 */
PRIVATE WUNUSED NONNULL((1, 2)) bool
NOTHROW_NCX(FCALL libiconv_normalize_codec_name)(char buf[CODE_NAME_MAXLEN + 1],
                                                 char const *__restrict name) {
#define issep(ch) ((ch) == '-' || (ch) == '_' || (ch) == ' ')
	char *ptr, *end;
	char const *nameend;
	ptr = buf;
	end = buf + CODE_NAME_MAXLEN;
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
	} else if ((name[0] == 'L' || name[0] == 'l') &&
	           issep(name[1]) && isdigit(name[2])) {
		/* Convert: `l-xxx' | `l_xxx' -> `lxxx' */
		*ptr++ = 'l';
		name += 2;
	}

	/* Strip trailing spaces. */
	nameend = strend(name);
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
		if (libiconv_normalize_codec_name(normal_name, name)) {
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
	buf = (char *)alloca((namelen + 1) * sizeof(char));
	*(char *)mempcpy(buf, name, namelen, sizeof(char)) = '\0';
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
