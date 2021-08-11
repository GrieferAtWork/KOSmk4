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
	char         cdbe_name[CEIL_ALIGN(17, __SIZEOF_INT__)];
	unsigned int cdbe_codec; /* The associated codec. */
};

PRIVATE struct codec_db_entry codec_db[] = {
	{ "ansi_x3.4-1968",   CODEC_ASCII },
	{ "ansi_x3.4-1986",   CODEC_ASCII },
	{ "cp367",            CODEC_ASCII },
	{ "ibm367",           CODEC_ASCII },
	{ "iso-ir-006",       CODEC_ASCII },
	{ "iso646-us",        CODEC_ASCII },
	{ "iso_646.irv:1991", CODEC_ASCII },
	{ "us",               CODEC_ASCII },
	{ "utf-16",           CODEC_UTF16 },
	{ "utf-16be",         CODEC_UTF16BE },
	{ "utf-16le",         CODEC_UTF16LE },
	{ "utf-32",           CODEC_UTF32 },
	{ "utf-32be",         CODEC_UTF32BE },
	{ "utf-32le",         CODEC_UTF32LE },
	{ "utf-8",            CODEC_UTF8 },
	{ "utf16",            CODEC_UTF16 },
	{ "utf16be",          CODEC_UTF16BE },
	{ "utf16le",          CODEC_UTF16LE },
	{ "utf32",            CODEC_UTF32 },
	{ "utf32be",          CODEC_UTF32BE },
	{ "utf32le",          CODEC_UTF32LE },
	{ "utf8",             CODEC_UTF8 },
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
