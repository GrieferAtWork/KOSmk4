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

#include "api.h"
/**/

#include <hybrid/align.h>

#include <kos/types.h>

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
		name = name.lower();
		if (name in name2codec)
			throw Error("Duplicate mapping for " + repr name);
		name2codec[name] = codec;
		l = l.lstrip().lstrip(",").lstrip();
	}
}
local longestNameLen = (name2codec.keys.each.length > ...) + 1;
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
struct codec_db_entry {
	char         cdbe_name[CEIL_ALIGN(25, __SIZEOF_INT__)];
	unsigned int cdbe_codec; /* The associated codec. */
};

PRIVATE struct codec_db_entry codec_db[] = {
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
	{ "ansi_x3.4-1968",           CODEC_ASCII },
	{ "ansi_x3.4-1986",           CODEC_ASCII },
	{ "arabic",                   CODEC_ISO_8859_6 },
	{ "asmo-708",                 CODEC_ISO_8859_6 },
	{ "bulgaria-pc",              CODEC_MIK },
	{ "cp-ar",                    CODEC_CP868 },
	{ "cp-gr",                    CODEC_CP869 },
	{ "cp-is",                    CODEC_CP861 },
	{ "cp1041",                   CODEC_CP1041 },
	{ "cp1057",                   CODEC_CP1057 },
	{ "cp1098",                   CODEC_CP1098 },
	{ "cp1116",                   CODEC_CP1116 },
	{ "cp1117",                   CODEC_CP1117 },
	{ "cp1118",                   CODEC_CP774 },
	{ "cp1119",                   CODEC_CP772 },
	{ "cp1125",                   CODEC_CP1125 },
	{ "cp1131",                   CODEC_CP1131 },
	{ "cp17248",                  CODEC_CP17248 },
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
	{ "csiso21german",            CODEC_DIN_66003 },
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
	{ "cspc850multilingual",      CODEC_CP850 },
	{ "cspc862latinhebrew",       CODEC_CP862 },
	{ "cspc8codepage437",         CODEC_CP437 },
	{ "cspcp852",                 CODEC_CP852 },
	{ "cyrillic",                 CODEC_ISO_8859_5 },
	{ "d7dec",                    CODEC_DIN_66003 },
	{ "de",                       CODEC_DIN_66003 },
	{ "din_66003",                CODEC_DIN_66003 },
	{ "din_66303",                CODEC_DIN_66303 },
	{ "dos-895",                  CODEC_KEYBCS2 },
	{ "drv8",                     CODEC_DIN_66303 },
	{ "ecma-114",                 CODEC_ISO_8859_6 },
	{ "ecma-118",                 CODEC_ISO_8859_7 },
	{ "elot_928",                 CODEC_ISO_8859_7 },
	{ "estonia-iso-8",            CODEC_CP922 },
	{ "german",                   CODEC_DIN_66003 },
	{ "greek",                    CODEC_ISO_8859_7 },
	{ "greek8",                   CODEC_ISO_8859_7 },
	{ "hebrew",                   CODEC_ISO_8859_8 },
	{ "hp-pc-8",                  CODEC_CP1057 },
	{ "ibm-1011",                 CODEC_DIN_66003 },
	{ "ibm1098",                  CODEC_CP1098 },
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
	{ "iso-ir-006",               CODEC_ASCII },
	{ "iso-ir-100",               CODEC_ISO_8859_1 },
	{ "iso-ir-101",               CODEC_ISO_8859_2 },
	{ "iso-ir-109",               CODEC_ISO_8859_3 },
	{ "iso-ir-110",               CODEC_ISO_8859_4 },
	{ "iso-ir-126",               CODEC_ISO_8859_7 },
	{ "iso-ir-127",               CODEC_ISO_8859_6 },
	{ "iso-ir-138",               CODEC_ISO_8859_8 },
	{ "iso-ir-144",               CODEC_ISO_8859_5 },
	{ "iso-ir-148",               CODEC_ISO_8859_9 },
	{ "iso-ir-157",               CODEC_ISO_8859_10 },
	{ "iso-ir-179",               CODEC_ISO_8859_13 },
	{ "iso-ir-182",               CODEC_ISO_IR_182 },
	{ "iso-ir-197",               CODEC_ISO_IR_197 },
	{ "iso-ir-199",               CODEC_ISO_8859_14 },
	{ "iso-ir-200",               CODEC_ISO_IR_200 },
	{ "iso-ir-21",                CODEC_DIN_66003 },
	{ "iso-ir-226",               CODEC_ISO_8859_16 },
	{ "iso646-de",                CODEC_DIN_66003 },
	{ "iso646-us",                CODEC_ASCII },
	{ "iso_646.irv:1991",         CODEC_ASCII },
	{ "kamenicky",                CODEC_KEYBCS2 },
	{ "kbl",                      CODEC_CP771 },
	{ "keybcs2",                  CODEC_KEYBCS2 },
	{ "koi-8-n1",                 CODEC_KOI_8_N1 },
	{ "koi-8-n2",                 CODEC_KOI_8_N2 },
	{ "l1",                       CODEC_ISO_8859_1 },
	{ "l10",                      CODEC_ISO_8859_16 },
	{ "l2",                       CODEC_ISO_8859_2 },
	{ "l3",                       CODEC_ISO_8859_3 },
	{ "l4",                       CODEC_ISO_8859_4 },
	{ "l5",                       CODEC_ISO_8859_9 },
	{ "l6",                       CODEC_ISO_8859_10 },
	{ "l7",                       CODEC_ISO_8859_13 },
	{ "l8",                       CODEC_ISO_8859_14 },
	{ "latin-0",                  CODEC_ISO_8859_15 },
	{ "latin-9",                  CODEC_ISO_8859_15 },
	{ "latin1",                   CODEC_ISO_8859_1 },
	{ "latin10",                  CODEC_ISO_8859_16 },
	{ "latin2",                   CODEC_ISO_8859_2 },
	{ "latin3",                   CODEC_ISO_8859_3 },
	{ "latin4",                   CODEC_ISO_8859_4 },
	{ "latin5",                   CODEC_ISO_8859_9 },
	{ "latin6",                   CODEC_ISO_8859_10 },
	{ "latin7",                   CODEC_ISO_8859_13 },
	{ "latin8",                   CODEC_ISO_8859_14 },
	{ "lst-1283",                 CODEC_CP774 },
	{ "lst-1284",                 CODEC_CP772 },
	{ "lst-1284:1993",            CODEC_CP772 },
	{ "maz",                      CODEC_CP667 },
	{ "mazovia",                  CODEC_CP667 },
	{ "mik",                      CODEC_MIK },
	{ "ms-10206",                 CODEC_DIN_66003 },
	{ "nec-867",                  CODEC_KEYBCS2 },
	{ "oem-720",                  CODEC_CP720 },
	{ "oem-737",                  CODEC_CP737 },
	{ "oem-775",                  CODEC_CP775 },
	{ "oem-850",                  CODEC_CP850 },
	{ "oem-855",                  CODEC_CP855 },
	{ "oem-857",                  CODEC_CP857 },
	{ "oem-858",                  CODEC_CP858 },
	{ "oem-860",                  CODEC_CP860 },
	{ "oem-861",                  CODEC_CP861 },
	{ "oem-862",                  CODEC_CP862 },
	{ "oem-863",                  CODEC_CP863 },
	{ "oem-865",                  CODEC_CP865 },
	{ "oem-869",                  CODEC_CP869 },
	{ "oem-us",                   CODEC_CP437 },
	{ "osf100201b5",              CODEC_CP437 },
	{ "pc-multilingual-850+euro", CODEC_CP858 },
	{ "rst-2018-91 ",             CODEC_CP1125 },
	{ "ruscii",                   CODEC_CP1125 },
	{ "ruslat",                   CODEC_CP3012 },
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
};
/*[[[end]]]*/



/* Return the ID of the codec associated with `name'
 * Casing is ignored and codec aliases are respected. */
INTERN ATTR_PURE WUNUSED NONNULL((1)) unsigned int
NOTHROW_NCX(FCALL libiconv_codecbyname)(char const *__restrict name) {
	size_t lo, hi;
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
	return CODEC_UNKNOWN;
}

/* Return the nth (0-based) alphabetically sorted name for the codec `id'
 * When `id' is invalid or doesn't have an `nth' name, return `NULL' */
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



DECL_END

#endif /* !GUARD_LIBICONV_CODECS_C */
