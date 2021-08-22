/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.removeif([](x) -> x.startswith("-O"));
gcc_opt.append("-O3"); // Force _all_ optimizations because stuff in here is performance-critical
]]]*/
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
#ifndef GUARD_LIBICONV_CONVERT_XML_C
#define GUARD_LIBICONV_CONVERT_XML_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/overflow.h>

#include <kos/types.h>

#include <alloca.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unicode.h>

#include <libiconv/iconv.h>

#include "convert.h"

DECL_BEGIN

#ifdef CONFIG_NO_XML_FANCY_ENCODE
#undef CONFIG_XML_FANCY_ENCODE
#elif !defined(CONFIG_XML_FANCY_ENCODE)
#ifndef __OPTIMIZE_SIZE__
#define CONFIG_XML_FANCY_ENCODE
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* ... */


#define IS_ICONV_ERR_ERRNO(flags)                     (((flags) & ICONV_ERRMASK) == ICONV_ERR_ERRNO)
#define IS_ICONV_ERR_ERROR_OR_ERRNO(flags)            (((flags) & ICONV_ERRMASK) <= ICONV_ERR_ERROR)
#define IS_ICONV_ERR_ERROR_OR_ERRNO_OR_DISCARD(flags) (((flags) & ICONV_ERRMASK) <= ICONV_ERR_DISCARD)
#define IS_ICONV_ERR_DISCARD(flags)                   (((flags) & ICONV_ERRMASK) == ICONV_ERR_DISCARD)
#define IS_ICONV_ERR_REPLACE(flags)                   (((flags) & ICONV_ERRMASK) == ICONV_ERR_REPLACE)
#define IS_ICONV_ERR_IGNORE(flags)                    (((flags) & ICONV_ERRMASK) == ICONV_ERR_IGNORE)

#define decode_output_printer self->icd_output.ii_printer
#define decode_output_arg     self->icd_output.ii_arg
#define decode_output(p, s)   (*decode_output_printer)(decode_output_arg, p, s)
#define encode_output_printer self->ice_output.ii_printer
#define encode_output_arg     self->ice_output.ii_arg
#define encode_output(p, s)   (*encode_output_printer)(encode_output_arg, p, s)
#define DO(expr)                         \
	do {                                 \
		if unlikely((temp = (expr)) < 0) \
			goto err;                    \
		result += temp;                  \
	}	__WHILE0
#define DO_encode_output(p, s) DO(encode_output(p, s))
#define DO_decode_output(p, s) DO(decode_output(p, s))


/*****************************************************************************
 *
 * Entity database format (tightly packed and sorted lexicographically):
 *    [0x00]       // Only if the first entry has a mandatory ";"
 *    {
 *        [0x01]   // Only iff the trailing ";" is optional for this entry
 *        <name>   // Name, with the leading "&" removed and no trailing ";"
 *        0x00     // NUL
 *        <ord>    // Ordinal replacement, encoded as UTF-8. When parsed
 *                 // as  unicode,  this  is a  1-character  long string
 *        0x00     // NUL
 *    } [Repeat for every entity, sorted by <name>]
 *    0x2E         // '.'
 *    0x2E         // '.'
 *    0x00         // NUL
 *    0x2E         // '.'
 *    0x00         // NUL
 *
 * Even  though entries are variable-length, it is possible to find the
 * start/end of any entry if given the pointer to any part within. This
 * is because every entry consists of 2 C-strings, meaning that the end
 * of both strings can always be located (in the above graphic, that is
 * one of the 0x00 aka  NUL fields). The two  strings can then be  told
 * apart from each other by the fact  that <name> is always at least  2
 * characters long, and <ord> is always exactly 1 character long. Thus,
 * it's also always possible  to find the start  of an entry (for  this
 * purpose, said start is considered to be the beginning of <name>)
 *
 * Because the entire database is sorted lexicographically by <name>,
 * it now becomes possible to perform a binary search where each step
 * is adjusted to located the start of the center-most entry.
 *
 * In turn, searching the database still only takes O(log2(N)), where
 * N is the total size (in bytes) of the database.
 *
 * NOTES:
 *  - The offset to <name> of the first entry is always `1'
 *  - The offset to the end of the last entry is always `sizeof(db) - 5'
 *
 *****************************************************************************/




/*[[[deemon
import * from deemon;
import xe = XML_ENTITIES from ".iconvdata.xml-entities";

// In order for the special database encoding we're using
// to work, all keys must have a length of at least 2!
local keys = xe.keys.sorted();
assert (keys.each.length < ...) >= 2;
local longestKeyLen = keys.each.length > ...;

local stringToOffset: {string: int} = Dict();

local fp = File.Writer();
local offset = 0;
if (!xe[keys.first].last) {
	fp << "\0";
	++offset;
}
for (local key: keys) {
	local ord, semicolonIsOptional = xe[key]...;
	if (semicolonIsOptional) {
		fp << "\1";
		++offset;
	}
	stringToOffset[key] = offset;
	local utf8 = string.chr(ord).encode("utf-8");
	fp << key << "\0" << utf8 << "\0";
	offset += #key + #utf8 + 2;
}

fp << "..\0.\0";
fp = fp.string[:-1]; // Implicit trailing NUL isn't needed
local dbSize = #fp + 1;
print("PRIVATE char const xml_entity_db[", dbSize.hex(), "] = \"\\");
for (local line: fp.segments(32))
	print(line.encode("c-escape"), "\\");
print("\";");


//
// In order to (efficiently) use the database for encoding,
// we need another lookup table. However, because encoding can
// also be done via "&#123;", this is an optional feature.
//
// This database encodes unicode ordinals --> offsets into the string table.
//

local dbOffsetType;
if (dbSize > 0xffff) {
	dbOffsetType = "uint32_t";
} else if (dbSize > 0xff) {
	dbOffsetType = "uint16_t";
} else {
	dbOffsetType = "uint8_t";
}
local uni16ToEntity: {int: string} = Dict(); // For U+0000 - U+FFFF
local uni32ToEntity: {int: string} = Dict(); // For U+10000 - ...
for (local key: keys) {
	local ord = xe[key].first;
	local tab = ord <= 0xffff ? uni16ToEntity : uni32ToEntity;
	local exist = tab.get(ord);
	if (exist !is none && #exist <= #key)
		continue; // Already defined as a shorter string (we prefer short names during encoding)
	tab[ord] = key;
}

// For compatibility, we force specific names for XML 1.0 entities
uni16ToEntity[0x0022] = "quot";
uni16ToEntity[0x0026] = "amp";
uni16ToEntity[0x0027] = "apos";
uni16ToEntity[0x003C] = "lt";
uni16ToEntity[0x003E] = "gt";

// Generate the encode database
print;
print("#ifdef CONFIG_XML_FANCY_ENCODE");
print("struct xml_encode16_entry {");
print("	char16_t xe16_chr; /" "* Unicode character. *" "/");
print("	", dbOffsetType, " xe16_offset; /" "* Offset into `xml_entity_db' *" "/");
print("};");
print("struct xml_encode32_entry {");
print("	char32_t xe32_chr; /" "* Unicode character. *" "/");
print("	", dbOffsetType, " xe32_offset; /" "* Offset into `xml_entity_db' *" "/");
print("};");
print("PRIVATE struct xml_encode16_entry const xml_encode16_db[", #uni16ToEntity, "] = {");
local largestStringOffsetLen = #(stringToOffset.values > ...).hex();
for (local ord: uni16ToEntity.keys.sorted()) {
	local name = uni16ToEntity[ord];
	local offset = stringToOffset[name].hex();
	print("	{ 0x", ord.hex()[2:].upper().zfill(4), ", ", offset, " }, ",
		" " * (largestStringOffsetLen - #offset),
		"/" "* ", repr(name), " *" "/");
}
print("};");
print("PRIVATE struct xml_encode32_entry const xml_encode32_db[", #uni32ToEntity, "] = {");
local largestOrd32Len = #(uni32ToEntity.keys > ...).hex() - 2;
local largestStringOffsetLen = #(stringToOffset.values > ...).hex();
for (local ord: uni32ToEntity.keys.sorted()) {
	local name = uni32ToEntity[ord];
	local offset = stringToOffset[name].hex();
	print("	{ 0x", ord.hex()[2:].upper().zfill(largestOrd32Len), ", ", offset, " }, ",
		" " * (largestStringOffsetLen - #offset),
		"/" "* ", repr(name), " *" "/");
}
print("};");


print("#endif /" "* CONFIG_XML_FANCY_ENCODE *" "/");
]]]*/
PRIVATE char const xml_entity_db[0x5f23] = "\
\1AElig\0\xC3\x86\0\1AMP\0&\0\1Aacute\0\xC3\x81\0Abre\
ve\0\xC4\x82\0\1Acirc\0\xC3\x82\0Acy\0\xD0\x90\0Afr\0\xF0\x9D\x94\x84\0\
\1Agrave\0\xC3\x80\0Alpha\0\xCE\x91\0Amacr\0\xC4\x80\0And\
\0\xE2\xA9\x93\0Aogon\0\xC4\x84\0Aopf\0\xF0\x9D\x94\xB8\0ApplyFun\
ction\0\xE2\x81\xA1\0\1Aring\0\xC3\x85\0Ascr\0\xF0\x9D\x92\x9C\0As\
sign\0\xE2\x89\x94\0\1Atilde\0\xC3\x83\0\1Auml\0\xC3\x84\0Bac\
kslash\0\xE2\x88\x96\0Barv\0\xE2\xAB\xA7\0Barwed\0\xE2\x8C\x86\0B\
cy\0\xD0\x91\0Because\0\xE2\x88\xB5\0Bernoullis\0\xE2\x84\xAC\
\0Beta\0\xCE\x92\0Bfr\0\xF0\x9D\x94\x85\0Bopf\0\xF0\x9D\x94\xB9\0Brev\
e\0\xCB\x98\0Bscr\0\xE2\x84\xAC\0Bumpeq\0\xE2\x89\x8E\0CHcy\0\xD0\xA7\
\0\1COPY\0\xC2\xA9\0Cacute\0\xC4\x86\0Cap\0\xE2\x8B\x92\0Capi\
talDifferentialD\0\xE2\x85\x85\0Cayleys\0\xE2\x84\xAD\
\0Ccaron\0\xC4\x8C\0\1Ccedil\0\xC3\x87\0Ccirc\0\xC4\x88\0C\
conint\0\xE2\x88\xB0\0Cdot\0\xC4\x8A\0Cedilla\0\xC2\xB8\0Ce\
nterDot\0\xC2\xB7\0Cfr\0\xE2\x84\xAD\0Chi\0\xCE\xA7\0Circle\
Dot\0\xE2\x8A\x99\0CircleMinus\0\xE2\x8A\x96\0CirclePl\
us\0\xE2\x8A\x95\0CircleTimes\0\xE2\x8A\x97\0Clockwise\
ContourIntegral\0\xE2\x88\xB2\0CloseCurlyDo\
ubleQuote\0\xE2\x80\x9D\0CloseCurlyQuote\0\xE2\x80\
\x99\0Colon\0\xE2\x88\xB7\0Colone\0\xE2\xA9\xB4\0Congruent\
\0\xE2\x89\xA1\0Conint\0\xE2\x88\xAF\0ContourIntegral\0\
\xE2\x88\xAE\0Copf\0\xE2\x84\x82\0Coproduct\0\xE2\x88\x90\0Count\
erClockwiseContourIntegral\0\xE2\x88\xB3\0C\
ross\0\xE2\xA8\xAF\0Cscr\0\xF0\x9D\x92\x9E\0Cup\0\xE2\x8B\x93\0CupCa\
p\0\xE2\x89\x8D\0DD\0\xE2\x85\x85\0DDotrahd\0\xE2\xA4\x91\0DJcy\0\xD0\
\x82\0DScy\0\xD0\x85\0DZcy\0\xD0\x8F\0Dagger\0\xE2\x80\xA1\0Dar\
r\0\xE2\x86\xA1\0Dashv\0\xE2\xAB\xA4\0Dcaron\0\xC4\x8E\0Dcy\0\xD0\x94\
\0Del\0\xE2\x88\x87\0Delta\0\xCE\x94\0Dfr\0\xF0\x9D\x94\x87\0Diacr\
iticalAcute\0\xC2\xB4\0DiacriticalDot\0\xCB\x99\
\0DiacriticalDoubleAcute\0\xCB\x9D\0Diacr\
iticalGrave\0`\0DiacriticalTilde\0\xCB\
\x9C\0Diamond\0\xE2\x8B\x84\0DifferentialD\0\xE2\x85\x86\0\
Dopf\0\xF0\x9D\x94\xBB\0Dot\0\xC2\xA8\0DotDot\0\xE2\x83\x9C\0DotE\
qual\0\xE2\x89\x90\0DoubleContourIntegral\0\xE2\
\x88\xAF\0DoubleDot\0\xC2\xA8\0DoubleDownArrow\0\
\xE2\x87\x93\0DoubleLeftArrow\0\xE2\x87\x90\0DoubleLe\
ftRightArrow\0\xE2\x87\x94\0DoubleLeftTee\0\xE2\
\xAB\xA4\0DoubleLongLeftArrow\0\xE2\x9F\xB8\0Doubl\
eLongLeftRightArrow\0\xE2\x9F\xBA\0DoubleLo\
ngRightArrow\0\xE2\x9F\xB9\0DoubleRightArro\
w\0\xE2\x87\x92\0DoubleRightTee\0\xE2\x8A\xA8\0DoubleU\
pArrow\0\xE2\x87\x91\0DoubleUpDownArrow\0\xE2\x87\x95\
\0DoubleVerticalBar\0\xE2\x88\xA5\0DownArrow\
\0\xE2\x86\x93\0DownArrowBar\0\xE2\xA4\x93\0DownArrowU\
pArrow\0\xE2\x87\xB5\0DownBreve\0\xCC\x91\0DownLeft\
RightVector\0\xE2\xA5\x90\0DownLeftTeeVecto\
r\0\xE2\xA5\x9E\0DownLeftVector\0\xE2\x86\xBD\0DownLef\
tVectorBar\0\xE2\xA5\x96\0DownRightTeeVecto\
r\0\xE2\xA5\x9F\0DownRightVector\0\xE2\x87\x81\0DownRi\
ghtVectorBar\0\xE2\xA5\x97\0DownTee\0\xE2\x8A\xA4\0Dow\
nTeeArrow\0\xE2\x86\xA7\0Downarrow\0\xE2\x87\x93\0Dscr\
\0\xF0\x9D\x92\x9F\0Dstrok\0\xC4\x90\0ENG\0\xC5\x8A\0\1ETH\0\xC3\x90\0\1\
Eacute\0\xC3\x89\0Ecaron\0\xC4\x9A\0\1Ecirc\0\xC3\x8A\0Ec\
y\0\xD0\xAD\0Edot\0\xC4\x96\0Efr\0\xF0\x9D\x94\x88\0\1Egrave\0\xC3\x88\
\0Element\0\xE2\x88\x88\0Emacr\0\xC4\x92\0EmptySmall\
Square\0\xE2\x97\xBB\0EmptyVerySmallSquare\0\
\xE2\x96\xAB\0Eogon\0\xC4\x98\0Eopf\0\xF0\x9D\x94\xBC\0Epsilon\0\xCE\
\x95\0Equal\0\xE2\xA9\xB5\0EqualTilde\0\xE2\x89\x82\0Equil\
ibrium\0\xE2\x87\x8C\0Escr\0\xE2\x84\xB0\0Esim\0\xE2\xA9\xB3\0Eta\
\0\xCE\x97\0\1Euml\0\xC3\x8B\0Exists\0\xE2\x88\x83\0Exponent\
ialE\0\xE2\x85\x87\0Fcy\0\xD0\xA4\0Ffr\0\xF0\x9D\x94\x89\0FilledS\
mallSquare\0\xE2\x97\xBC\0FilledVerySmallSq\
uare\0\xE2\x96\xAA\0Fopf\0\xF0\x9D\x94\xBD\0ForAll\0\xE2\x88\x80\0Fo\
uriertrf\0\xE2\x84\xB1\0Fscr\0\xE2\x84\xB1\0GJcy\0\xD0\x83\0\1G\
T\0>\0Gamma\0\xCE\x93\0Gammad\0\xCF\x9C\0Gbreve\0\xC4\x9E\
\0Gcedil\0\xC4\xA2\0Gcirc\0\xC4\x9C\0Gcy\0\xD0\x93\0Gdot\0\
\xC4\xA0\0Gfr\0\xF0\x9D\x94\x8A\0Gg\0\xE2\x8B\x99\0Gopf\0\xF0\x9D\x94\xBE\0Gre\
aterEqual\0\xE2\x89\xA5\0GreaterEqualLess\0\xE2\
\x8B\x9B\0GreaterFullEqual\0\xE2\x89\xA7\0GreaterG\
reater\0\xE2\xAA\xA2\0GreaterLess\0\xE2\x89\xB7\0Great\
erSlantEqual\0\xE2\xA9\xBE\0GreaterTilde\0\xE2\x89\
\xB3\0Gscr\0\xF0\x9D\x92\xA2\0Gt\0\xE2\x89\xAB\0HARDcy\0\xD0\xAA\0Hac\
ek\0\xCB\x87\0Hat\0^\0Hcirc\0\xC4\xA4\0Hfr\0\xE2\x84\x8C\0Hil\
bertSpace\0\xE2\x84\x8B\0Hopf\0\xE2\x84\x8D\0Horizonta\
lLine\0\xE2\x94\x80\0Hscr\0\xE2\x84\x8B\0Hstrok\0\xC4\xA6\0Hum\
pDownHump\0\xE2\x89\x8E\0HumpEqual\0\xE2\x89\x8F\0IEcy\
\0\xD0\x95\0IJlig\0\xC4\xB2\0IOcy\0\xD0\x81\0\1Iacute\0\xC3\x8D\0\
\1Icirc\0\xC3\x8E\0Icy\0\xD0\x98\0Idot\0\xC4\xB0\0Ifr\0\xE2\x84\x91\
\0\1Igrave\0\xC3\x8C\0Im\0\xE2\x84\x91\0Imacr\0\xC4\xAA\0Imag\
inaryI\0\xE2\x85\x88\0Implies\0\xE2\x87\x92\0Int\0\xE2\x88\xAC\0I\
ntegral\0\xE2\x88\xAB\0Intersection\0\xE2\x8B\x82\0Inv\
isibleComma\0\xE2\x81\xA3\0InvisibleTimes\0\xE2\
\x81\xA2\0Iogon\0\xC4\xAE\0Iopf\0\xF0\x9D\x95\x80\0Iota\0\xCE\x99\0Is\
cr\0\xE2\x84\x90\0Itilde\0\xC4\xA8\0Iukcy\0\xD0\x86\0\1Iuml\0\
\xC3\x8F\0Jcirc\0\xC4\xB4\0Jcy\0\xD0\x99\0Jfr\0\xF0\x9D\x94\x8D\0Jopf\
\0\xF0\x9D\x95\x81\0Jscr\0\xF0\x9D\x92\xA5\0Jsercy\0\xD0\x88\0Jukcy\0\
\xD0\x84\0KHcy\0\xD0\xA5\0KJcy\0\xD0\x8C\0Kappa\0\xCE\x9A\0Kced\
il\0\xC4\xB6\0Kcy\0\xD0\x9A\0Kfr\0\xF0\x9D\x94\x8E\0Kopf\0\xF0\x9D\x95\x82\0\
Kscr\0\xF0\x9D\x92\xA6\0LJcy\0\xD0\x89\0\1LT\0<\0Lacute\0\xC4\
\xB9\0Lambda\0\xCE\x9B\0Lang\0\xE2\x9F\xAA\0Laplacetrf\0\
\xE2\x84\x92\0Larr\0\xE2\x86\x9E\0Lcaron\0\xC4\xBD\0Lcedil\0\xC4\xBB\
\0Lcy\0\xD0\x9B\0LeftAngleBracket\0\xE2\x9F\xA8\0Lef\
tArrow\0\xE2\x86\x90\0LeftArrowBar\0\xE2\x87\xA4\0Left\
ArrowRightArrow\0\xE2\x87\x86\0LeftCeiling\0\
\xE2\x8C\x88\0LeftDoubleBracket\0\xE2\x9F\xA6\0LeftDo\
wnTeeVector\0\xE2\xA5\xA1\0LeftDownVector\0\xE2\
\x87\x83\0LeftDownVectorBar\0\xE2\xA5\x99\0LeftFlo\
or\0\xE2\x8C\x8A\0LeftRightArrow\0\xE2\x86\x94\0LeftRi\
ghtVector\0\xE2\xA5\x8E\0LeftTee\0\xE2\x8A\xA3\0LeftTe\
eArrow\0\xE2\x86\xA4\0LeftTeeVector\0\xE2\xA5\x9A\0Lef\
tTriangle\0\xE2\x8A\xB2\0LeftTriangleBar\0\xE2\xA7\
\x8F\0LeftTriangleEqual\0\xE2\x8A\xB4\0LeftUpDo\
wnVector\0\xE2\xA5\x91\0LeftUpTeeVector\0\xE2\xA5\xA0\
\0LeftUpVector\0\xE2\x86\xBF\0LeftUpVectorBa\
r\0\xE2\xA5\x98\0LeftVector\0\xE2\x86\xBC\0LeftVectorB\
ar\0\xE2\xA5\x92\0Leftarrow\0\xE2\x87\x90\0Leftrightar\
row\0\xE2\x87\x94\0LessEqualGreater\0\xE2\x8B\x9A\0Les\
sFullEqual\0\xE2\x89\xA6\0LessGreater\0\xE2\x89\xB6\0L\
essLess\0\xE2\xAA\xA1\0LessSlantEqual\0\xE2\xA9\xBD\0L\
essTilde\0\xE2\x89\xB2\0Lfr\0\xF0\x9D\x94\x8F\0Ll\0\xE2\x8B\x98\0Lle\
ftarrow\0\xE2\x87\x9A\0Lmidot\0\xC4\xBF\0LongLeftAr\
row\0\xE2\x9F\xB5\0LongLeftRightArrow\0\xE2\x9F\xB7\0L\
ongRightArrow\0\xE2\x9F\xB6\0Longleftarrow\0\
\xE2\x9F\xB8\0Longleftrightarrow\0\xE2\x9F\xBA\0Longr\
ightarrow\0\xE2\x9F\xB9\0Lopf\0\xF0\x9D\x95\x83\0LowerLef\
tArrow\0\xE2\x86\x99\0LowerRightArrow\0\xE2\x86\x98\0L\
scr\0\xE2\x84\x92\0Lsh\0\xE2\x86\xB0\0Lstrok\0\xC5\x81\0Lt\0\xE2\x89\xAA\
\0Map\0\xE2\xA4\x85\0Mcy\0\xD0\x9C\0MediumSpace\0\xE2\x81\x9F\0\
Mellintrf\0\xE2\x84\xB3\0Mfr\0\xF0\x9D\x94\x90\0MinusPlus\
\0\xE2\x88\x93\0Mopf\0\xF0\x9D\x95\x84\0Mscr\0\xE2\x84\xB3\0Mu\0\xCE\x9C\0NJ\
cy\0\xD0\x8A\0Nacute\0\xC5\x83\0Ncaron\0\xC5\x87\0Ncedil\
\0\xC5\x85\0Ncy\0\xD0\x9D\0NegativeMediumSpace\0\xE2\
\x80\x8B\0NegativeThickSpace\0\xE2\x80\x8B\0Negati\
veThinSpace\0\xE2\x80\x8B\0NegativeVeryThin\
Space\0\xE2\x80\x8B\0NestedGreaterGreater\0\xE2\
\x89\xAB\0NestedLessLess\0\xE2\x89\xAA\0NewLine\0\n\0\
Nfr\0\xF0\x9D\x94\x91\0NoBreak\0\xE2\x81\xA0\0NonBreaking\
Space\0\xC2\xA0\0Nopf\0\xE2\x84\x95\0Not\0\xE2\xAB\xAC\0NotCon\
gruent\0\xE2\x89\xA2\0NotCupCap\0\xE2\x89\xAD\0NotDoub\
leVerticalBar\0\xE2\x88\xA6\0NotElement\0\xE2\x88\x89\
\0NotEqual\0\xE2\x89\xA0\0NotEqualTilde\0\xE2\x89\x82\0\
NotExists\0\xE2\x88\x84\0NotGreater\0\xE2\x89\xAF\0Not\
GreaterEqual\0\xE2\x89\xB1\0NotGreaterFullE\
qual\0\xE2\x89\xA7\0NotGreaterGreater\0\xE2\x89\xAB\0N\
otGreaterLess\0\xE2\x89\xB9\0NotGreaterSlan\
tEqual\0\xE2\xA9\xBE\0NotGreaterTilde\0\xE2\x89\xB5\0N\
otHumpDownHump\0\xE2\x89\x8E\0NotHumpEqual\0\
\xE2\x89\x8F\0NotLeftTriangle\0\xE2\x8B\xAA\0NotLeftT\
riangleBar\0\xE2\xA7\x8F\0NotLeftTriangleEq\
ual\0\xE2\x8B\xAC\0NotLess\0\xE2\x89\xAE\0NotLessEqual\
\0\xE2\x89\xB0\0NotLessGreater\0\xE2\x89\xB8\0NotLessL\
ess\0\xE2\x89\xAA\0NotLessSlantEqual\0\xE2\xA9\xBD\0No\
tLessTilde\0\xE2\x89\xB4\0NotNestedGreaterG\
reater\0\xE2\xAA\xA2\0NotNestedLessLess\0\xE2\xAA\xA1\
\0NotPrecedes\0\xE2\x8A\x80\0NotPrecedesEqua\
l\0\xE2\xAA\xAF\0NotPrecedesSlantEqual\0\xE2\x8B\xA0\0\
NotReverseElement\0\xE2\x88\x8C\0NotRightTr\
iangle\0\xE2\x8B\xAB\0NotRightTriangleBar\0\xE2\
\xA7\x90\0NotRightTriangleEqual\0\xE2\x8B\xAD\0Not\
SquareSubset\0\xE2\x8A\x8F\0NotSquareSubset\
Equal\0\xE2\x8B\xA2\0NotSquareSuperset\0\xE2\x8A\x90\0\
NotSquareSupersetEqual\0\xE2\x8B\xA3\0NotSu\
bset\0\xE2\x8A\x82\0NotSubsetEqual\0\xE2\x8A\x88\0NotS\
ucceeds\0\xE2\x8A\x81\0NotSucceedsEqual\0\xE2\xAA\xB0\
\0NotSucceedsSlantEqual\0\xE2\x8B\xA1\0NotSu\
cceedsTilde\0\xE2\x89\xBF\0NotSuperset\0\xE2\x8A\x83\0\
NotSupersetEqual\0\xE2\x8A\x89\0NotTilde\0\xE2\x89\
\x81\0NotTildeEqual\0\xE2\x89\x84\0NotTildeFull\
Equal\0\xE2\x89\x87\0NotTildeTilde\0\xE2\x89\x89\0NotV\
erticalBar\0\xE2\x88\xA4\0Nscr\0\xF0\x9D\x92\xA9\0\1Ntilde\
\0\xC3\x91\0Nu\0\xCE\x9D\0OElig\0\xC5\x92\0\1Oacute\0\xC3\x93\0\1O\
circ\0\xC3\x94\0Ocy\0\xD0\x9E\0Odblac\0\xC5\x90\0Ofr\0\xF0\x9D\x94\
\x92\0\1Ograve\0\xC3\x92\0Omacr\0\xC5\x8C\0Omega\0\xCE\xA9\0O\
micron\0\xCE\x9F\0Oopf\0\xF0\x9D\x95\x86\0OpenCurlyDou\
bleQuote\0\xE2\x80\x9C\0OpenCurlyQuote\0\xE2\x80\x98\0\
Or\0\xE2\xA9\x94\0Oscr\0\xF0\x9D\x92\xAA\0\1Oslash\0\xC3\x98\0\1Oti\
lde\0\xC3\x95\0Otimes\0\xE2\xA8\xB7\0\1Ouml\0\xC3\x96\0OverB\
ar\0\xE2\x80\xBE\0OverBrace\0\xE2\x8F\x9E\0OverBracket\
\0\xE2\x8E\xB4\0OverParenthesis\0\xE2\x8F\x9C\0Partial\
D\0\xE2\x88\x82\0Pcy\0\xD0\x9F\0Pfr\0\xF0\x9D\x94\x93\0Phi\0\xCE\xA6\0Pi\0\
\xCE\xA0\0PlusMinus\0\xC2\xB1\0Poincareplane\0\xE2\x84\
\x8C\0Popf\0\xE2\x84\x99\0Pr\0\xE2\xAA\xBB\0Precedes\0\xE2\x89\xBA\0P\
recedesEqual\0\xE2\xAA\xAF\0PrecedesSlantEq\
ual\0\xE2\x89\xBC\0PrecedesTilde\0\xE2\x89\xBE\0Prime\0\
\xE2\x80\xB3\0Product\0\xE2\x88\x8F\0Proportion\0\xE2\x88\xB7\0P\
roportional\0\xE2\x88\x9D\0Pscr\0\xF0\x9D\x92\xAB\0Psi\0\xCE\xA8\
\0\1QUOT\0\"\0Qfr\0\xF0\x9D\x94\x94\0Qopf\0\xE2\x84\x9A\0Qscr\0\
\xF0\x9D\x92\xAC\0RBarr\0\xE2\xA4\x90\0\1REG\0\xC2\xAE\0Racute\0\xC5\x94\
\0Rang\0\xE2\x9F\xAB\0Rarr\0\xE2\x86\xA0\0Rarrtl\0\xE2\xA4\x96\0Rc\
aron\0\xC5\x98\0Rcedil\0\xC5\x96\0Rcy\0\xD0\xA0\0Re\0\xE2\x84\x9C\0\
ReverseElement\0\xE2\x88\x8B\0ReverseEquili\
brium\0\xE2\x87\x8B\0ReverseUpEquilibrium\0\xE2\
\xA5\xAF\0Rfr\0\xE2\x84\x9C\0Rho\0\xCE\xA1\0RightAngleBrac\
ket\0\xE2\x9F\xA9\0RightArrow\0\xE2\x86\x92\0RightArro\
wBar\0\xE2\x87\xA5\0RightArrowLeftArrow\0\xE2\x87\x84\
\0RightCeiling\0\xE2\x8C\x89\0RightDoubleBra\
cket\0\xE2\x9F\xA7\0RightDownTeeVector\0\xE2\xA5\x9D\0\
RightDownVector\0\xE2\x87\x82\0RightDownVec\
torBar\0\xE2\xA5\x95\0RightFloor\0\xE2\x8C\x8B\0RightT\
ee\0\xE2\x8A\xA2\0RightTeeArrow\0\xE2\x86\xA6\0RightTe\
eVector\0\xE2\xA5\x9B\0RightTriangle\0\xE2\x8A\xB3\0Ri\
ghtTriangleBar\0\xE2\xA7\x90\0RightTriangle\
Equal\0\xE2\x8A\xB5\0RightUpDownVector\0\xE2\xA5\x8F\0\
RightUpTeeVector\0\xE2\xA5\x9C\0RightUpVect\
or\0\xE2\x86\xBE\0RightUpVectorBar\0\xE2\xA5\x94\0Righ\
tVector\0\xE2\x87\x80\0RightVectorBar\0\xE2\xA5\x93\0R\
ightarrow\0\xE2\x87\x92\0Ropf\0\xE2\x84\x9D\0RoundImpl\
ies\0\xE2\xA5\xB0\0Rrightarrow\0\xE2\x87\x9B\0Rscr\0\xE2\x84\x9B\
\0Rsh\0\xE2\x86\xB1\0RuleDelayed\0\xE2\xA7\xB4\0SHCHcy\0\
\xD0\xA9\0SHcy\0\xD0\xA8\0SOFTcy\0\xD0\xAC\0Sacute\0\xC5\x9A\0S\
c\0\xE2\xAA\xBC\0Scaron\0\xC5\xA0\0Scedil\0\xC5\x9E\0Scirc\0\
\xC5\x9C\0Scy\0\xD0\xA1\0Sfr\0\xF0\x9D\x94\x96\0ShortDownArro\
w\0\xE2\x86\x93\0ShortLeftArrow\0\xE2\x86\x90\0ShortRi\
ghtArrow\0\xE2\x86\x92\0ShortUpArrow\0\xE2\x86\x91\0Si\
gma\0\xCE\xA3\0SmallCircle\0\xE2\x88\x98\0Sopf\0\xF0\x9D\x95\x8A\
\0Sqrt\0\xE2\x88\x9A\0Square\0\xE2\x96\xA1\0SquareInter\
section\0\xE2\x8A\x93\0SquareSubset\0\xE2\x8A\x8F\0Squ\
areSubsetEqual\0\xE2\x8A\x91\0SquareSuperse\
t\0\xE2\x8A\x90\0SquareSupersetEqual\0\xE2\x8A\x92\0Sq\
uareUnion\0\xE2\x8A\x94\0Sscr\0\xF0\x9D\x92\xAE\0Star\0\xE2\x8B\x86\
\0Sub\0\xE2\x8B\x90\0Subset\0\xE2\x8B\x90\0SubsetEqual\0\
\xE2\x8A\x86\0Succeeds\0\xE2\x89\xBB\0SucceedsEqual\0\xE2\
\xAA\xB0\0SucceedsSlantEqual\0\xE2\x89\xBD\0Succee\
dsTilde\0\xE2\x89\xBF\0SuchThat\0\xE2\x88\x8B\0Sum\0\xE2\x88\x91\
\0Sup\0\xE2\x8B\x91\0Superset\0\xE2\x8A\x83\0SupersetEq\
ual\0\xE2\x8A\x87\0Supset\0\xE2\x8B\x91\0\1THORN\0\xC3\x9E\0TRA\
DE\0\xE2\x84\xA2\0TSHcy\0\xD0\x8B\0TScy\0\xD0\xA6\0Tab\0\t\0Ta\
u\0\xCE\xA4\0Tcaron\0\xC5\xA4\0Tcedil\0\xC5\xA2\0Tcy\0\xD0\xA2\0\
Tfr\0\xF0\x9D\x94\x97\0Therefore\0\xE2\x88\xB4\0Theta\0\xCE\x98\0\
ThickSpace\0\xE2\x81\x9F\0ThinSpace\0\xE2\x80\x89\0Til\
de\0\xE2\x88\xBC\0TildeEqual\0\xE2\x89\x83\0TildeFullE\
qual\0\xE2\x89\x85\0TildeTilde\0\xE2\x89\x88\0Topf\0\xF0\x9D\x95\
\x8B\0TripleDot\0\xE2\x83\x9B\0Tscr\0\xF0\x9D\x92\xAF\0Tstrok\
\0\xC5\xA6\0\1Uacute\0\xC3\x9A\0Uarr\0\xE2\x86\x9F\0Uarrocir\
\0\xE2\xA5\x89\0Ubrcy\0\xD0\x8E\0Ubreve\0\xC5\xAC\0\1Ucirc\0\xC3\
\x9B\0Ucy\0\xD0\xA3\0Udblac\0\xC5\xB0\0Ufr\0\xF0\x9D\x94\x98\0\1Ugr\
ave\0\xC3\x99\0Umacr\0\xC5\xAA\0UnderBar\0_\0Under\
Brace\0\xE2\x8F\x9F\0UnderBracket\0\xE2\x8E\xB5\0Under\
Parenthesis\0\xE2\x8F\x9D\0Union\0\xE2\x8B\x83\0UnionP\
lus\0\xE2\x8A\x8E\0Uogon\0\xC5\xB2\0Uopf\0\xF0\x9D\x95\x8C\0UpArr\
ow\0\xE2\x86\x91\0UpArrowBar\0\xE2\xA4\x92\0UpArrowDow\
nArrow\0\xE2\x87\x85\0UpDownArrow\0\xE2\x86\x95\0UpEqu\
ilibrium\0\xE2\xA5\xAE\0UpTee\0\xE2\x8A\xA5\0UpTeeArro\
w\0\xE2\x86\xA5\0Uparrow\0\xE2\x87\x91\0Updownarrow\0\xE2\x87\
\x95\0UpperLeftArrow\0\xE2\x86\x96\0UpperRightA\
rrow\0\xE2\x86\x97\0Upsi\0\xCF\x92\0Upsilon\0\xCE\xA5\0Urin\
g\0\xC5\xAE\0Uscr\0\xF0\x9D\x92\xB0\0Utilde\0\xC5\xA8\0\1Uuml\0\xC3\
\x9C\0VDash\0\xE2\x8A\xAB\0Vbar\0\xE2\xAB\xAB\0Vcy\0\xD0\x92\0Vdas\
h\0\xE2\x8A\xA9\0Vdashl\0\xE2\xAB\xA6\0Vee\0\xE2\x8B\x81\0Verbar\0\
\xE2\x80\x96\0Vert\0\xE2\x80\x96\0VerticalBar\0\xE2\x88\xA3\0Ver\
ticalLine\0|\0VerticalSeparator\0\xE2\x9D\
\x98\0VerticalTilde\0\xE2\x89\x80\0VeryThinSpac\
e\0\xE2\x80\x8A\0Vfr\0\xF0\x9D\x94\x99\0Vopf\0\xF0\x9D\x95\x8D\0Vscr\0\xF0\x9D\
\x92\xB1\0Vvdash\0\xE2\x8A\xAA\0Wcirc\0\xC5\xB4\0Wedge\0\xE2\x8B\x80\
\0Wfr\0\xF0\x9D\x94\x9A\0Wopf\0\xF0\x9D\x95\x8E\0Wscr\0\xF0\x9D\x92\xB2\0Xf\
r\0\xF0\x9D\x94\x9B\0Xi\0\xCE\x9E\0Xopf\0\xF0\x9D\x95\x8F\0Xscr\0\xF0\x9D\x92\xB3\
\0YAcy\0\xD0\xAF\0YIcy\0\xD0\x87\0YUcy\0\xD0\xAE\0\1Yacute\
\0\xC3\x9D\0Ycirc\0\xC5\xB6\0Ycy\0\xD0\xAB\0Yfr\0\xF0\x9D\x94\x9C\0Yop\
f\0\xF0\x9D\x95\x90\0Yscr\0\xF0\x9D\x92\xB4\0Yuml\0\xC5\xB8\0ZHcy\0\xD0\x96\
\0Zacute\0\xC5\xB9\0Zcaron\0\xC5\xBD\0Zcy\0\xD0\x97\0Zdot\
\0\xC5\xBB\0ZeroWidthSpace\0\xE2\x80\x8B\0Zeta\0\xCE\x96\0Z\
fr\0\xE2\x84\xA8\0Zopf\0\xE2\x84\xA4\0Zscr\0\xF0\x9D\x92\xB5\0\1aacut\
e\0\xC3\xA1\0abreve\0\xC4\x83\0ac\0\xE2\x88\xBE\0acE\0\xE2\x88\xBE\0ac\
d\0\xE2\x88\xBF\0\1acirc\0\xC3\xA2\0\1acute\0\xC2\xB4\0acy\0\xD0\xB0\
\0\1aelig\0\xC3\xA6\0af\0\xE2\x81\xA1\0afr\0\xF0\x9D\x94\x9E\0\1agra\
ve\0\xC3\xA0\0alefsym\0\xE2\x84\xB5\0aleph\0\xE2\x84\xB5\0alph\
a\0\xCE\xB1\0amacr\0\xC4\x81\0amalg\0\xE2\xA8\xBF\0\1amp\0&\0a\
nd\0\xE2\x88\xA7\0andand\0\xE2\xA9\x95\0andd\0\xE2\xA9\x9C\0andsl\
ope\0\xE2\xA9\x98\0andv\0\xE2\xA9\x9A\0ang\0\xE2\x88\xA0\0ange\0\xE2\xA6\
\xA4\0angle\0\xE2\x88\xA0\0angmsd\0\xE2\x88\xA1\0angmsdaa\0\
\xE2\xA6\xA8\0angmsdab\0\xE2\xA6\xA9\0angmsdac\0\xE2\xA6\xAA\0an\
gmsdad\0\xE2\xA6\xAB\0angmsdae\0\xE2\xA6\xAC\0angmsdaf\
\0\xE2\xA6\xAD\0angmsdag\0\xE2\xA6\xAE\0angmsdah\0\xE2\xA6\xAF\0a\
ngrt\0\xE2\x88\x9F\0angrtvb\0\xE2\x8A\xBE\0angrtvbd\0\xE2\xA6\
\x9D\0angsph\0\xE2\x88\xA2\0angst\0\xC3\x85\0angzarr\0\xE2\x8D\
\xBC\0aogon\0\xC4\x85\0aopf\0\xF0\x9D\x95\x92\0ap\0\xE2\x89\x88\0apE\0\
\xE2\xA9\xB0\0apacir\0\xE2\xA9\xAF\0ape\0\xE2\x89\x8A\0apid\0\xE2\x89\x8B\0\
apos\0\'\0approx\0\xE2\x89\x88\0approxeq\0\xE2\x89\x8A\0\1\
aring\0\xC3\xA5\0ascr\0\xF0\x9D\x92\xB6\0ast\0*\0asymp\0\xE2\
\x89\x88\0asympeq\0\xE2\x89\x8D\0\1atilde\0\xC3\xA3\0\1auml\0\
\xC3\xA4\0awconint\0\xE2\x88\xB3\0awint\0\xE2\xA8\x91\0bNot\0\xE2\
\xAB\xAD\0backcong\0\xE2\x89\x8C\0backepsilon\0\xCF\xB6\0b\
ackprime\0\xE2\x80\xB5\0backsim\0\xE2\x88\xBD\0backsim\
eq\0\xE2\x8B\x8D\0barvee\0\xE2\x8A\xBD\0barwed\0\xE2\x8C\x85\0bar\
wedge\0\xE2\x8C\x85\0bbrk\0\xE2\x8E\xB5\0bbrktbrk\0\xE2\x8E\xB6\0\
bcong\0\xE2\x89\x8C\0bcy\0\xD0\xB1\0bdquo\0\xE2\x80\x9E\0becau\
s\0\xE2\x88\xB5\0because\0\xE2\x88\xB5\0bemptyv\0\xE2\xA6\xB0\0be\
psi\0\xCF\xB6\0bernou\0\xE2\x84\xAC\0beta\0\xCE\xB2\0beth\0\xE2\
\x84\xB6\0between\0\xE2\x89\xAC\0bfr\0\xF0\x9D\x94\x9F\0bigcap\0\xE2\
\x8B\x82\0bigcirc\0\xE2\x97\xAF\0bigcup\0\xE2\x8B\x83\0bigodo\
t\0\xE2\xA8\x80\0bigoplus\0\xE2\xA8\x81\0bigotimes\0\xE2\xA8\x82\
\0bigsqcup\0\xE2\xA8\x86\0bigstar\0\xE2\x98\x85\0bigtri\
angledown\0\xE2\x96\xBD\0bigtriangleup\0\xE2\x96\xB3\0\
biguplus\0\xE2\xA8\x84\0bigvee\0\xE2\x8B\x81\0bigwedge\
\0\xE2\x8B\x80\0bkarow\0\xE2\xA4\x8D\0blacklozenge\0\xE2\xA7\xAB\
\0blacksquare\0\xE2\x96\xAA\0blacktriangle\0\xE2\
\x96\xB4\0blacktriangledown\0\xE2\x96\xBE\0blacktr\
iangleleft\0\xE2\x97\x82\0blacktrianglerigh\
t\0\xE2\x96\xB8\0blank\0\xE2\x90\xA3\0blk12\0\xE2\x96\x92\0blk14\0\
\xE2\x96\x91\0blk34\0\xE2\x96\x93\0block\0\xE2\x96\x88\0bne\0=\0bn\
equiv\0\xE2\x89\xA1\0bnot\0\xE2\x8C\x90\0bopf\0\xF0\x9D\x95\x93\0bot\
\0\xE2\x8A\xA5\0bottom\0\xE2\x8A\xA5\0bowtie\0\xE2\x8B\x88\0boxDL\
\0\xE2\x95\x97\0boxDR\0\xE2\x95\x94\0boxDl\0\xE2\x95\x96\0boxDr\0\xE2\
\x95\x93\0boxH\0\xE2\x95\x90\0boxHD\0\xE2\x95\xA6\0boxHU\0\xE2\x95\xA9\0\
boxHd\0\xE2\x95\xA4\0boxHu\0\xE2\x95\xA7\0boxUL\0\xE2\x95\x9D\0bo\
xUR\0\xE2\x95\x9A\0boxUl\0\xE2\x95\x9C\0boxUr\0\xE2\x95\x99\0boxV\
\0\xE2\x95\x91\0boxVH\0\xE2\x95\xAC\0boxVL\0\xE2\x95\xA3\0boxVR\0\xE2\
\x95\xA0\0boxVh\0\xE2\x95\xAB\0boxVl\0\xE2\x95\xA2\0boxVr\0\xE2\x95\x9F\
\0boxbox\0\xE2\xA7\x89\0boxdL\0\xE2\x95\x95\0boxdR\0\xE2\x95\x92\0\
boxdl\0\xE2\x94\x90\0boxdr\0\xE2\x94\x8C\0boxh\0\xE2\x94\x80\0box\
hD\0\xE2\x95\xA5\0boxhU\0\xE2\x95\xA8\0boxhd\0\xE2\x94\xAC\0boxhu\
\0\xE2\x94\xB4\0boxminus\0\xE2\x8A\x9F\0boxplus\0\xE2\x8A\x9E\0bo\
xtimes\0\xE2\x8A\xA0\0boxuL\0\xE2\x95\x9B\0boxuR\0\xE2\x95\x98\0b\
oxul\0\xE2\x94\x98\0boxur\0\xE2\x94\x94\0boxv\0\xE2\x94\x82\0boxv\
H\0\xE2\x95\xAA\0boxvL\0\xE2\x95\xA1\0boxvR\0\xE2\x95\x9E\0boxvh\0\
\xE2\x94\xBC\0boxvl\0\xE2\x94\xA4\0boxvr\0\xE2\x94\x9C\0bprime\0\xE2\
\x80\xB5\0breve\0\xCB\x98\0\1brvbar\0\xC2\xA6\0bscr\0\xF0\x9D\x92\xB7\
\0bsemi\0\xE2\x81\x8F\0bsim\0\xE2\x88\xBD\0bsime\0\xE2\x8B\x8D\0bs\
ol\0\\\0bsolb\0\xE2\xA7\x85\0bsolhsub\0\xE2\x9F\x88\0bull\
\0\xE2\x80\xA2\0bullet\0\xE2\x80\xA2\0bump\0\xE2\x89\x8E\0bumpE\0\xE2\
\xAA\xAE\0bumpe\0\xE2\x89\x8F\0bumpeq\0\xE2\x89\x8F\0cacute\0\xC4\
\x87\0cap\0\xE2\x88\xA9\0capand\0\xE2\xA9\x84\0capbrcup\0\xE2\xA9\
\x89\0capcap\0\xE2\xA9\x8B\0capcup\0\xE2\xA9\x87\0capdot\0\xE2\
\xA9\x80\0caps\0\xE2\x88\xA9\0caret\0\xE2\x81\x81\0caron\0\xCB\x87\0c\
caps\0\xE2\xA9\x8D\0ccaron\0\xC4\x8D\0\1ccedil\0\xC3\xA7\0cc\
irc\0\xC4\x89\0ccups\0\xE2\xA9\x8C\0ccupssm\0\xE2\xA9\x90\0cdo\
t\0\xC4\x8B\0\1cedil\0\xC2\xB8\0cemptyv\0\xE2\xA6\xB2\0\1cent\
\0\xC2\xA2\0centerdot\0\xC2\xB7\0cfr\0\xF0\x9D\x94\xA0\0chcy\0\xD1\
\x87\0check\0\xE2\x9C\x93\0checkmark\0\xE2\x9C\x93\0chi\0\xCF\x87\
\0cir\0\xE2\x97\x8B\0cirE\0\xE2\xA7\x83\0circ\0\xCB\x86\0circeq\
\0\xE2\x89\x97\0circlearrowleft\0\xE2\x86\xBA\0circlea\
rrowright\0\xE2\x86\xBB\0circledR\0\xC2\xAE\0circle\
dS\0\xE2\x93\x88\0circledast\0\xE2\x8A\x9B\0circledcir\
c\0\xE2\x8A\x9A\0circleddash\0\xE2\x8A\x9D\0cire\0\xE2\x89\x97\0c\
irfnint\0\xE2\xA8\x90\0cirmid\0\xE2\xAB\xAF\0cirscir\0\xE2\
\xA7\x82\0clubs\0\xE2\x99\xA3\0clubsuit\0\xE2\x99\xA3\0colon\0\
:\0colone\0\xE2\x89\x94\0coloneq\0\xE2\x89\x94\0comma\0,\
\0commat\0@\0comp\0\xE2\x88\x81\0compfn\0\xE2\x88\x98\0co\
mplement\0\xE2\x88\x81\0complexes\0\xE2\x84\x82\0cong\0\
\xE2\x89\x85\0congdot\0\xE2\xA9\xAD\0conint\0\xE2\x88\xAE\0copf\0\
\xF0\x9D\x95\x94\0coprod\0\xE2\x88\x90\0\1copy\0\xC2\xA9\0copysr\0\
\xE2\x84\x97\0crarr\0\xE2\x86\xB5\0cross\0\xE2\x9C\x97\0cscr\0\xF0\x9D\x92\
\xB8\0csub\0\xE2\xAB\x8F\0csube\0\xE2\xAB\x91\0csup\0\xE2\xAB\x90\0cs\
upe\0\xE2\xAB\x92\0ctdot\0\xE2\x8B\xAF\0cudarrl\0\xE2\xA4\xB8\0cu\
darrr\0\xE2\xA4\xB5\0cuepr\0\xE2\x8B\x9E\0cuesc\0\xE2\x8B\x9F\0cu\
larr\0\xE2\x86\xB6\0cularrp\0\xE2\xA4\xBD\0cup\0\xE2\x88\xAA\0cup\
brcap\0\xE2\xA9\x88\0cupcap\0\xE2\xA9\x86\0cupcup\0\xE2\xA9\x8A\0\
cupdot\0\xE2\x8A\x8D\0cupor\0\xE2\xA9\x85\0cups\0\xE2\x88\xAA\0cu\
rarr\0\xE2\x86\xB7\0curarrm\0\xE2\xA4\xBC\0curlyeqprec\
\0\xE2\x8B\x9E\0curlyeqsucc\0\xE2\x8B\x9F\0curlyvee\0\xE2\x8B\
\x8E\0curlywedge\0\xE2\x8B\x8F\0\1curren\0\xC2\xA4\0curv\
earrowleft\0\xE2\x86\xB6\0curvearrowright\0\xE2\
\x86\xB7\0cuvee\0\xE2\x8B\x8E\0cuwed\0\xE2\x8B\x8F\0cwconint\0\
\xE2\x88\xB2\0cwint\0\xE2\x88\xB1\0cylcty\0\xE2\x8C\xAD\0dArr\0\xE2\x87\
\x93\0dHar\0\xE2\xA5\xA5\0dagger\0\xE2\x80\xA0\0daleth\0\xE2\x84\xB8\
\0darr\0\xE2\x86\x93\0dash\0\xE2\x80\x90\0dashv\0\xE2\x8A\xA3\0dbk\
arow\0\xE2\xA4\x8F\0dblac\0\xCB\x9D\0dcaron\0\xC4\x8F\0dcy\0\
\xD0\xB4\0dd\0\xE2\x85\x86\0ddagger\0\xE2\x80\xA1\0ddarr\0\xE2\x87\x8A\0\
ddotseq\0\xE2\xA9\xB7\0\1deg\0\xC2\xB0\0delta\0\xCE\xB4\0dem\
ptyv\0\xE2\xA6\xB1\0dfisht\0\xE2\xA5\xBF\0dfr\0\xF0\x9D\x94\xA1\0dha\
rl\0\xE2\x87\x83\0dharr\0\xE2\x87\x82\0diam\0\xE2\x8B\x84\0diamon\
d\0\xE2\x8B\x84\0diamondsuit\0\xE2\x99\xA6\0diams\0\xE2\x99\xA6\0\
die\0\xC2\xA8\0digamma\0\xCF\x9D\0disin\0\xE2\x8B\xB2\0div\0\
\xC3\xB7\0\1divide\0\xC3\xB7\0divideontimes\0\xE2\x8B\x87\0\
divonx\0\xE2\x8B\x87\0djcy\0\xD1\x92\0dlcorn\0\xE2\x8C\x9E\0dl\
crop\0\xE2\x8C\x8D\0dollar\0$\0dopf\0\xF0\x9D\x95\x95\0dot\0\
\xCB\x99\0doteq\0\xE2\x89\x90\0doteqdot\0\xE2\x89\x91\0dotmin\
us\0\xE2\x88\xB8\0dotplus\0\xE2\x88\x94\0dotsquare\0\xE2\x8A\xA1\
\0doublebarwedge\0\xE2\x8C\x86\0downarrow\0\xE2\x86\
\x93\0downdownarrows\0\xE2\x87\x8A\0downharpoon\
left\0\xE2\x87\x83\0downharpoonright\0\xE2\x87\x82\0dr\
bkarow\0\xE2\xA4\x90\0drcorn\0\xE2\x8C\x9F\0drcrop\0\xE2\x8C\x8C\
\0dscr\0\xF0\x9D\x92\xB9\0dscy\0\xD1\x95\0dsol\0\xE2\xA7\xB6\0dstr\
ok\0\xC4\x91\0dtdot\0\xE2\x8B\xB1\0dtri\0\xE2\x96\xBF\0dtrif\0\xE2\
\x96\xBE\0duarr\0\xE2\x87\xB5\0duhar\0\xE2\xA5\xAF\0dwangle\0\xE2\
\xA6\xA6\0dzcy\0\xD1\x9F\0dzigrarr\0\xE2\x9F\xBF\0eDDot\0\xE2\xA9\
\xB7\0eDot\0\xE2\x89\x91\0\1eacute\0\xC3\xA9\0easter\0\xE2\xA9\xAE\
\0ecaron\0\xC4\x9B\0ecir\0\xE2\x89\x96\0\1ecirc\0\xC3\xAA\0ec\
olon\0\xE2\x89\x95\0ecy\0\xD1\x8D\0edot\0\xC4\x97\0ee\0\xE2\x85\x87\0e\
fDot\0\xE2\x89\x92\0efr\0\xF0\x9D\x94\xA2\0eg\0\xE2\xAA\x9A\0\1egrave\
\0\xC3\xA8\0egs\0\xE2\xAA\x96\0egsdot\0\xE2\xAA\x98\0el\0\xE2\xAA\x99\0el\
inters\0\xE2\x8F\xA7\0ell\0\xE2\x84\x93\0els\0\xE2\xAA\x95\0elsdo\
t\0\xE2\xAA\x97\0emacr\0\xC4\x93\0empty\0\xE2\x88\x85\0emptyse\
t\0\xE2\x88\x85\0emptyv\0\xE2\x88\x85\0emsp\0\xE2\x80\x83\0emsp13\
\0\xE2\x80\x84\0emsp14\0\xE2\x80\x85\0eng\0\xC5\x8B\0ensp\0\xE2\x80\x82\0\
eogon\0\xC4\x99\0eopf\0\xF0\x9D\x95\x96\0epar\0\xE2\x8B\x95\0epar\
sl\0\xE2\xA7\xA3\0eplus\0\xE2\xA9\xB1\0epsi\0\xCE\xB5\0epsilon\
\0\xCE\xB5\0epsiv\0\xCF\xB5\0eqcirc\0\xE2\x89\x96\0eqcolon\0\
\xE2\x89\x95\0eqsim\0\xE2\x89\x82\0eqslantgtr\0\xE2\xAA\x96\0eqs\
lantless\0\xE2\xAA\x95\0equals\0=\0equest\0\xE2\x89\x9F\
\0equiv\0\xE2\x89\xA1\0equivDD\0\xE2\xA9\xB8\0eqvparsl\0\
\xE2\xA7\xA5\0erDot\0\xE2\x89\x93\0erarr\0\xE2\xA5\xB1\0escr\0\xE2\x84\xAF\
\0esdot\0\xE2\x89\x90\0esim\0\xE2\x89\x82\0eta\0\xCE\xB7\0\1eth\0\
\xC3\xB0\0\1euml\0\xC3\xAB\0euro\0\xE2\x82\xAC\0excl\0!\0exis\
t\0\xE2\x88\x83\0expectation\0\xE2\x84\xB0\0exponentia\
le\0\xE2\x85\x87\0fallingdotseq\0\xE2\x89\x92\0fcy\0\xD1\x84\0\
female\0\xE2\x99\x80\0ffilig\0\xEF\xAC\x83\0fflig\0\xEF\xAC\x80\0\
ffllig\0\xEF\xAC\x84\0ffr\0\xF0\x9D\x94\xA3\0filig\0\xEF\xAC\x81\0fj\
lig\0f\0flat\0\xE2\x99\xAD\0fllig\0\xEF\xAC\x82\0fltns\0\xE2\
\x96\xB1\0fnof\0\xC6\x92\0fopf\0\xF0\x9D\x95\x97\0forall\0\xE2\x88\x80\0\
fork\0\xE2\x8B\x94\0forkv\0\xE2\xAB\x99\0fpartint\0\xE2\xA8\x8D\0\
\1frac12\0\xC2\xBD\0frac13\0\xE2\x85\x93\0\1frac14\0\xC2\xBC\
\0frac15\0\xE2\x85\x95\0frac16\0\xE2\x85\x99\0frac18\0\xE2\x85\
\x9B\0frac23\0\xE2\x85\x94\0frac25\0\xE2\x85\x96\0\1frac34\0\
\xC2\xBE\0frac35\0\xE2\x85\x97\0frac38\0\xE2\x85\x9C\0frac45\0\
\xE2\x85\x98\0frac56\0\xE2\x85\x9A\0frac58\0\xE2\x85\x9D\0frac78\
\0\xE2\x85\x9E\0frasl\0\xE2\x81\x84\0frown\0\xE2\x8C\xA2\0fscr\0\xF0\x9D\
\x92\xBB\0gE\0\xE2\x89\xA7\0gEl\0\xE2\xAA\x8C\0gacute\0\xC7\xB5\0gamm\
a\0\xCE\xB3\0gammad\0\xCF\x9D\0gap\0\xE2\xAA\x86\0gbreve\0\xC4\x9F\
\0gcirc\0\xC4\x9D\0gcy\0\xD0\xB3\0gdot\0\xC4\xA1\0ge\0\xE2\x89\xA5\0\
gel\0\xE2\x8B\x9B\0geq\0\xE2\x89\xA5\0geqq\0\xE2\x89\xA7\0geqslan\
t\0\xE2\xA9\xBE\0ges\0\xE2\xA9\xBE\0gescc\0\xE2\xAA\xA9\0gesdot\0\xE2\
\xAA\x80\0gesdoto\0\xE2\xAA\x82\0gesdotol\0\xE2\xAA\x84\0gesl\
\0\xE2\x8B\x9B\0gesles\0\xE2\xAA\x94\0gfr\0\xF0\x9D\x94\xA4\0gg\0\xE2\x89\xAB\0\
ggg\0\xE2\x8B\x99\0gimel\0\xE2\x84\xB7\0gjcy\0\xD1\x93\0gl\0\xE2\x89\xB7\
\0glE\0\xE2\xAA\x92\0gla\0\xE2\xAA\xA5\0glj\0\xE2\xAA\xA4\0gnE\0\xE2\x89\xA9\
\0gnap\0\xE2\xAA\x8A\0gnapprox\0\xE2\xAA\x8A\0gne\0\xE2\xAA\x88\0g\
neq\0\xE2\xAA\x88\0gneqq\0\xE2\x89\xA9\0gnsim\0\xE2\x8B\xA7\0gopf\
\0\xF0\x9D\x95\x98\0grave\0`\0gscr\0\xE2\x84\x8A\0gsim\0\xE2\x89\xB3\0\
gsime\0\xE2\xAA\x8E\0gsiml\0\xE2\xAA\x90\0\1gt\0>\0gtcc\0\xE2\
\xAA\xA7\0gtcir\0\xE2\xA9\xBA\0gtdot\0\xE2\x8B\x97\0gtlPar\0\xE2\xA6\
\x95\0gtquest\0\xE2\xA9\xBC\0gtrapprox\0\xE2\xAA\x86\0gtra\
rr\0\xE2\xA5\xB8\0gtrdot\0\xE2\x8B\x97\0gtreqless\0\xE2\x8B\x9B\0\
gtreqqless\0\xE2\xAA\x8C\0gtrless\0\xE2\x89\xB7\0gtrsi\
m\0\xE2\x89\xB3\0gvertneqq\0\xE2\x89\xA9\0gvnE\0\xE2\x89\xA9\0hAr\
r\0\xE2\x87\x94\0hairsp\0\xE2\x80\x8A\0half\0\xC2\xBD\0hamilt\0\
\xE2\x84\x8B\0hardcy\0\xD1\x8A\0harr\0\xE2\x86\x94\0harrcir\0\xE2\
\xA5\x88\0harrw\0\xE2\x86\xAD\0hbar\0\xE2\x84\x8F\0hcirc\0\xC4\xA5\0h\
earts\0\xE2\x99\xA5\0heartsuit\0\xE2\x99\xA5\0hellip\0\xE2\
\x80\xA6\0hercon\0\xE2\x8A\xB9\0hfr\0\xF0\x9D\x94\xA5\0hksearow\0\
\xE2\xA4\xA5\0hkswarow\0\xE2\xA4\xA6\0hoarr\0\xE2\x87\xBF\0homth\
t\0\xE2\x88\xBB\0hookleftarrow\0\xE2\x86\xA9\0hookrigh\
tarrow\0\xE2\x86\xAA\0hopf\0\xF0\x9D\x95\x99\0horbar\0\xE2\x80\x95\0\
hscr\0\xF0\x9D\x92\xBD\0hslash\0\xE2\x84\x8F\0hstrok\0\xC4\xA7\0h\
ybull\0\xE2\x81\x83\0hyphen\0\xE2\x80\x90\0\1iacute\0\xC3\xAD\0\
ic\0\xE2\x81\xA3\0\1icirc\0\xC3\xAE\0icy\0\xD0\xB8\0iecy\0\xD0\xB5\0\
\1iexcl\0\xC2\xA1\0iff\0\xE2\x87\x94\0ifr\0\xF0\x9D\x94\xA6\0\1igra\
ve\0\xC3\xAC\0ii\0\xE2\x85\x88\0iiiint\0\xE2\xA8\x8C\0iiint\0\xE2\x88\
\xAD\0iinfin\0\xE2\xA7\x9C\0iiota\0\xE2\x84\xA9\0ijlig\0\xC4\xB3\0\
imacr\0\xC4\xAB\0image\0\xE2\x84\x91\0imagline\0\xE2\x84\x90\0\
imagpart\0\xE2\x84\x91\0imath\0\xC4\xB1\0imof\0\xE2\x8A\xB7\0i\
mped\0\xC6\xB5\0in\0\xE2\x88\x88\0incare\0\xE2\x84\x85\0infin\0\
\xE2\x88\x9E\0infintie\0\xE2\xA7\x9D\0inodot\0\xC4\xB1\0int\0\xE2\
\x88\xAB\0intcal\0\xE2\x8A\xBA\0integers\0\xE2\x84\xA4\0inter\
cal\0\xE2\x8A\xBA\0intlarhk\0\xE2\xA8\x97\0intprod\0\xE2\xA8\xBC\
\0iocy\0\xD1\x91\0iogon\0\xC4\xAF\0iopf\0\xF0\x9D\x95\x9A\0iota\
\0\xCE\xB9\0iprod\0\xE2\xA8\xBC\0\1iquest\0\xC2\xBF\0iscr\0\xF0\x9D\
\x92\xBE\0isin\0\xE2\x88\x88\0isinE\0\xE2\x8B\xB9\0isindot\0\xE2\x8B\
\xB5\0isins\0\xE2\x8B\xB4\0isinsv\0\xE2\x8B\xB3\0isinv\0\xE2\x88\x88\
\0it\0\xE2\x81\xA2\0itilde\0\xC4\xA9\0iukcy\0\xD1\x96\0\1iuml\
\0\xC3\xAF\0jcirc\0\xC4\xB5\0jcy\0\xD0\xB9\0jfr\0\xF0\x9D\x94\xA7\0jma\
th\0\xC8\xB7\0jopf\0\xF0\x9D\x95\x9B\0jscr\0\xF0\x9D\x92\xBF\0jsercy\
\0\xD1\x98\0jukcy\0\xD1\x94\0kappa\0\xCE\xBA\0kappav\0\xCF\xB0\0\
kcedil\0\xC4\xB7\0kcy\0\xD0\xBA\0kfr\0\xF0\x9D\x94\xA8\0kgreen\
\0\xC4\xB8\0khcy\0\xD1\x85\0kjcy\0\xD1\x9C\0kopf\0\xF0\x9D\x95\x9C\0ks\
cr\0\xF0\x9D\x93\x80\0lAarr\0\xE2\x87\x9A\0lArr\0\xE2\x87\x90\0lAtai\
l\0\xE2\xA4\x9B\0lBarr\0\xE2\xA4\x8E\0lE\0\xE2\x89\xA6\0lEg\0\xE2\xAA\x8B\0l\
Har\0\xE2\xA5\xA2\0lacute\0\xC4\xBA\0laemptyv\0\xE2\xA6\xB4\0l\
agran\0\xE2\x84\x92\0lambda\0\xCE\xBB\0lang\0\xE2\x9F\xA8\0lan\
gd\0\xE2\xA6\x91\0langle\0\xE2\x9F\xA8\0lap\0\xE2\xAA\x85\0\1laquo\
\0\xC2\xAB\0larr\0\xE2\x86\x90\0larrb\0\xE2\x87\xA4\0larrbfs\0\xE2\
\xA4\x9F\0larrfs\0\xE2\xA4\x9D\0larrhk\0\xE2\x86\xA9\0larrlp\0\
\xE2\x86\xAB\0larrpl\0\xE2\xA4\xB9\0larrsim\0\xE2\xA5\xB3\0larrt\
l\0\xE2\x86\xA2\0lat\0\xE2\xAA\xAB\0latail\0\xE2\xA4\x99\0late\0\xE2\xAA\
\xAD\0lates\0\xE2\xAA\xAD\0lbarr\0\xE2\xA4\x8C\0lbbrk\0\xE2\x9D\xB2\0\
lbrace\0{\0lbrack\0[\0lbrke\0\xE2\xA6\x8B\0lbrk\
sld\0\xE2\xA6\x8F\0lbrkslu\0\xE2\xA6\x8D\0lcaron\0\xC4\xBE\0lc\
edil\0\xC4\xBC\0lceil\0\xE2\x8C\x88\0lcub\0{\0lcy\0\xD0\xBB\0\
ldca\0\xE2\xA4\xB6\0ldquo\0\xE2\x80\x9C\0ldquor\0\xE2\x80\x9E\0ld\
rdhar\0\xE2\xA5\xA7\0ldrushar\0\xE2\xA5\x8B\0ldsh\0\xE2\x86\xB2\0\
le\0\xE2\x89\xA4\0leftarrow\0\xE2\x86\x90\0leftarrowta\
il\0\xE2\x86\xA2\0leftharpoondown\0\xE2\x86\xBD\0lefth\
arpoonup\0\xE2\x86\xBC\0leftleftarrows\0\xE2\x87\x87\0\
leftrightarrow\0\xE2\x86\x94\0leftrightarro\
ws\0\xE2\x87\x86\0leftrightharpoons\0\xE2\x87\x8B\0lef\
trightsquigarrow\0\xE2\x86\xAD\0leftthreeti\
mes\0\xE2\x8B\x8B\0leg\0\xE2\x8B\x9A\0leq\0\xE2\x89\xA4\0leqq\0\xE2\x89\xA6\
\0leqslant\0\xE2\xA9\xBD\0les\0\xE2\xA9\xBD\0lescc\0\xE2\xAA\xA8\0\
lesdot\0\xE2\xA9\xBF\0lesdoto\0\xE2\xAA\x81\0lesdotor\0\
\xE2\xAA\x83\0lesg\0\xE2\x8B\x9A\0lesges\0\xE2\xAA\x93\0lessappr\
ox\0\xE2\xAA\x85\0lessdot\0\xE2\x8B\x96\0lesseqgtr\0\xE2\x8B\x9A\
\0lesseqqgtr\0\xE2\xAA\x8B\0lessgtr\0\xE2\x89\xB6\0less\
sim\0\xE2\x89\xB2\0lfisht\0\xE2\xA5\xBC\0lfloor\0\xE2\x8C\x8A\0lf\
r\0\xF0\x9D\x94\xA9\0lg\0\xE2\x89\xB6\0lgE\0\xE2\xAA\x91\0lhard\0\xE2\x86\xBD\0\
lharu\0\xE2\x86\xBC\0lharul\0\xE2\xA5\xAA\0lhblk\0\xE2\x96\x84\0l\
jcy\0\xD1\x99\0ll\0\xE2\x89\xAA\0llarr\0\xE2\x87\x87\0llcorner\
\0\xE2\x8C\x9E\0llhard\0\xE2\xA5\xAB\0lltri\0\xE2\x97\xBA\0lmidot\
\0\xC5\x80\0lmoust\0\xE2\x8E\xB0\0lmoustache\0\xE2\x8E\xB0\0ln\
E\0\xE2\x89\xA8\0lnap\0\xE2\xAA\x89\0lnapprox\0\xE2\xAA\x89\0lne\0\
\xE2\xAA\x87\0lneq\0\xE2\xAA\x87\0lneqq\0\xE2\x89\xA8\0lnsim\0\xE2\x8B\xA6\
\0loang\0\xE2\x9F\xAC\0loarr\0\xE2\x87\xBD\0lobrk\0\xE2\x9F\xA6\0l\
ongleftarrow\0\xE2\x9F\xB5\0longleftrightar\
row\0\xE2\x9F\xB7\0longmapsto\0\xE2\x9F\xBC\0longright\
arrow\0\xE2\x9F\xB6\0looparrowleft\0\xE2\x86\xAB\0loop\
arrowright\0\xE2\x86\xAC\0lopar\0\xE2\xA6\x85\0lopf\0\xF0\x9D\
\x95\x9D\0loplus\0\xE2\xA8\xAD\0lotimes\0\xE2\xA8\xB4\0lowast\
\0\xE2\x88\x97\0lowbar\0_\0loz\0\xE2\x97\x8A\0lozenge\0\xE2\x97\
\x8A\0lozf\0\xE2\xA7\xAB\0lpar\0(\0lparlt\0\xE2\xA6\x93\0lra\
rr\0\xE2\x87\x86\0lrcorner\0\xE2\x8C\x9F\0lrhar\0\xE2\x87\x8B\0lr\
hard\0\xE2\xA5\xAD\0lrm\0\xE2\x80\x8E\0lrtri\0\xE2\x8A\xBF\0lsaqu\
o\0\xE2\x80\xB9\0lscr\0\xF0\x9D\x93\x81\0lsh\0\xE2\x86\xB0\0lsim\0\xE2\x89\xB2\
\0lsime\0\xE2\xAA\x8D\0lsimg\0\xE2\xAA\x8F\0lsqb\0[\0lsqu\
o\0\xE2\x80\x98\0lsquor\0\xE2\x80\x9A\0lstrok\0\xC5\x82\0\1lt\0<\
\0ltcc\0\xE2\xAA\xA6\0ltcir\0\xE2\xA9\xB9\0ltdot\0\xE2\x8B\x96\0lt\
hree\0\xE2\x8B\x8B\0ltimes\0\xE2\x8B\x89\0ltlarr\0\xE2\xA5\xB6\0l\
tquest\0\xE2\xA9\xBB\0ltrPar\0\xE2\xA6\x96\0ltri\0\xE2\x97\x83\0l\
trie\0\xE2\x8A\xB4\0ltrif\0\xE2\x97\x82\0lurdshar\0\xE2\xA5\x8A\0\
luruhar\0\xE2\xA5\xA6\0lvertneqq\0\xE2\x89\xA8\0lvnE\0\xE2\
\x89\xA8\0mDDot\0\xE2\x88\xBA\0\1macr\0\xC2\xAF\0male\0\xE2\x99\x82\0m\
alt\0\xE2\x9C\xA0\0maltese\0\xE2\x9C\xA0\0map\0\xE2\x86\xA6\0maps\
to\0\xE2\x86\xA6\0mapstodown\0\xE2\x86\xA7\0mapstoleft\
\0\xE2\x86\xA4\0mapstoup\0\xE2\x86\xA5\0marker\0\xE2\x96\xAE\0mco\
mma\0\xE2\xA8\xA9\0mcy\0\xD0\xBC\0mdash\0\xE2\x80\x94\0measure\
dangle\0\xE2\x88\xA1\0mfr\0\xF0\x9D\x94\xAA\0mho\0\xE2\x84\xA7\0\1mic\
ro\0\xC2\xB5\0mid\0\xE2\x88\xA3\0midast\0*\0midcir\0\xE2\xAB\
\xB0\0\1middot\0\xC2\xB7\0minus\0\xE2\x88\x92\0minusb\0\xE2\x8A\
\x9F\0minusd\0\xE2\x88\xB8\0minusdu\0\xE2\xA8\xAA\0mlcp\0\xE2\xAB\
\x9B\0mldr\0\xE2\x80\xA6\0mnplus\0\xE2\x88\x93\0models\0\xE2\x8A\xA7\
\0mopf\0\xF0\x9D\x95\x9E\0mp\0\xE2\x88\x93\0mscr\0\xF0\x9D\x93\x82\0mstp\
os\0\xE2\x88\xBE\0mu\0\xCE\xBC\0multimap\0\xE2\x8A\xB8\0mumap\0\
\xE2\x8A\xB8\0nGg\0\xE2\x8B\x99\0nGt\0\xE2\x89\xAB\0nGtv\0\xE2\x89\xAB\0nLe\
ftarrow\0\xE2\x87\x8D\0nLeftrightarrow\0\xE2\x87\x8E\0\
nLl\0\xE2\x8B\x98\0nLt\0\xE2\x89\xAA\0nLtv\0\xE2\x89\xAA\0nRighta\
rrow\0\xE2\x87\x8F\0nVDash\0\xE2\x8A\xAF\0nVdash\0\xE2\x8A\xAE\0n\
abla\0\xE2\x88\x87\0nacute\0\xC5\x84\0nang\0\xE2\x88\xA0\0nap\0\
\xE2\x89\x89\0napE\0\xE2\xA9\xB0\0napid\0\xE2\x89\x8B\0napos\0\xC5\x89\0\
napprox\0\xE2\x89\x89\0natur\0\xE2\x99\xAE\0natural\0\xE2\x99\
\xAE\0naturals\0\xE2\x84\x95\0\1nbsp\0\xC2\xA0\0nbump\0\xE2\x89\
\x8E\0nbumpe\0\xE2\x89\x8F\0ncap\0\xE2\xA9\x83\0ncaron\0\xC5\x88\0\
ncedil\0\xC5\x86\0ncong\0\xE2\x89\x87\0ncongdot\0\xE2\xA9\xAD\
\0ncup\0\xE2\xA9\x82\0ncy\0\xD0\xBD\0ndash\0\xE2\x80\x93\0ne\0\xE2\x89\
\xA0\0neArr\0\xE2\x87\x97\0nearhk\0\xE2\xA4\xA4\0nearr\0\xE2\x86\x97\
\0nearrow\0\xE2\x86\x97\0nedot\0\xE2\x89\x90\0nequiv\0\xE2\x89\
\xA2\0nesear\0\xE2\xA4\xA8\0nesim\0\xE2\x89\x82\0nexist\0\xE2\x88\
\x84\0nexists\0\xE2\x88\x84\0nfr\0\xF0\x9D\x94\xAB\0ngE\0\xE2\x89\xA7\0n\
ge\0\xE2\x89\xB1\0ngeq\0\xE2\x89\xB1\0ngeqq\0\xE2\x89\xA7\0ngeqsl\
ant\0\xE2\xA9\xBE\0nges\0\xE2\xA9\xBE\0ngsim\0\xE2\x89\xB5\0ngt\0\xE2\
\x89\xAF\0ngtr\0\xE2\x89\xAF\0nhArr\0\xE2\x87\x8E\0nharr\0\xE2\x86\xAE\0\
nhpar\0\xE2\xAB\xB2\0ni\0\xE2\x88\x8B\0nis\0\xE2\x8B\xBC\0nisd\0\xE2\x8B\
\xBA\0niv\0\xE2\x88\x8B\0njcy\0\xD1\x9A\0nlArr\0\xE2\x87\x8D\0nlE\0\
\xE2\x89\xA6\0nlarr\0\xE2\x86\x9A\0nldr\0\xE2\x80\xA5\0nle\0\xE2\x89\xB0\0n\
leftarrow\0\xE2\x86\x9A\0nleftrightarrow\0\xE2\x86\
\xAE\0nleq\0\xE2\x89\xB0\0nleqq\0\xE2\x89\xA6\0nleqslant\0\xE2\
\xA9\xBD\0nles\0\xE2\xA9\xBD\0nless\0\xE2\x89\xAE\0nlsim\0\xE2\x89\xB4\0\
nlt\0\xE2\x89\xAE\0nltri\0\xE2\x8B\xAA\0nltrie\0\xE2\x8B\xAC\0nmi\
d\0\xE2\x88\xA4\0nopf\0\xF0\x9D\x95\x9F\0\1not\0\xC2\xAC\0notin\0\xE2\x88\
\x89\0notinE\0\xE2\x8B\xB9\0notindot\0\xE2\x8B\xB5\0notinv\
a\0\xE2\x88\x89\0notinvb\0\xE2\x8B\xB7\0notinvc\0\xE2\x8B\xB6\0no\
tni\0\xE2\x88\x8C\0notniva\0\xE2\x88\x8C\0notnivb\0\xE2\x8B\xBE\0\
notnivc\0\xE2\x8B\xBD\0npar\0\xE2\x88\xA6\0nparallel\0\xE2\
\x88\xA6\0nparsl\0\xE2\xAB\xBD\0npart\0\xE2\x88\x82\0npolint\0\
\xE2\xA8\x94\0npr\0\xE2\x8A\x80\0nprcue\0\xE2\x8B\xA0\0npre\0\xE2\xAA\xAF\0\
nprec\0\xE2\x8A\x80\0npreceq\0\xE2\xAA\xAF\0nrArr\0\xE2\x87\x8F\0\
nrarr\0\xE2\x86\x9B\0nrarrc\0\xE2\xA4\xB3\0nrarrw\0\xE2\x86\x9D\0\
nrightarrow\0\xE2\x86\x9B\0nrtri\0\xE2\x8B\xAB\0nrtrie\
\0\xE2\x8B\xAD\0nsc\0\xE2\x8A\x81\0nsccue\0\xE2\x8B\xA1\0nsce\0\xE2\xAA\xB0\
\0nscr\0\xF0\x9D\x93\x83\0nshortmid\0\xE2\x88\xA4\0nshortp\
arallel\0\xE2\x88\xA6\0nsim\0\xE2\x89\x81\0nsime\0\xE2\x89\x84\0n\
simeq\0\xE2\x89\x84\0nsmid\0\xE2\x88\xA4\0nspar\0\xE2\x88\xA6\0ns\
qsube\0\xE2\x8B\xA2\0nsqsupe\0\xE2\x8B\xA3\0nsub\0\xE2\x8A\x84\0n\
subE\0\xE2\xAB\x85\0nsube\0\xE2\x8A\x88\0nsubset\0\xE2\x8A\x82\0n\
subseteq\0\xE2\x8A\x88\0nsubseteqq\0\xE2\xAB\x85\0nsuc\
c\0\xE2\x8A\x81\0nsucceq\0\xE2\xAA\xB0\0nsup\0\xE2\x8A\x85\0nsupE\
\0\xE2\xAB\x86\0nsupe\0\xE2\x8A\x89\0nsupset\0\xE2\x8A\x83\0nsups\
eteq\0\xE2\x8A\x89\0nsupseteqq\0\xE2\xAB\x86\0ntgl\0\xE2\x89\xB9\
\0\1ntilde\0\xC3\xB1\0ntlg\0\xE2\x89\xB8\0ntrianglele\
ft\0\xE2\x8B\xAA\0ntrianglelefteq\0\xE2\x8B\xAC\0ntria\
ngleright\0\xE2\x8B\xAB\0ntrianglerighteq\0\xE2\
\x8B\xAD\0nu\0\xCE\xBD\0num\0#\0numero\0\xE2\x84\x96\0numsp\0\
\xE2\x80\x87\0nvDash\0\xE2\x8A\xAD\0nvHarr\0\xE2\xA4\x84\0nvap\0\xE2\
\x89\x8D\0nvdash\0\xE2\x8A\xAC\0nvge\0\xE2\x89\xA5\0nvgt\0>\0nv\
infin\0\xE2\xA7\x9E\0nvlArr\0\xE2\xA4\x82\0nvle\0\xE2\x89\xA4\0nv\
lt\0<\0nvltrie\0\xE2\x8A\xB4\0nvrArr\0\xE2\xA4\x83\0nvrt\
rie\0\xE2\x8A\xB5\0nvsim\0\xE2\x88\xBC\0nwArr\0\xE2\x87\x96\0nwar\
hk\0\xE2\xA4\xA3\0nwarr\0\xE2\x86\x96\0nwarrow\0\xE2\x86\x96\0nwn\
ear\0\xE2\xA4\xA7\0oS\0\xE2\x93\x88\0\1oacute\0\xC3\xB3\0oast\0\xE2\
\x8A\x9B\0ocir\0\xE2\x8A\x9A\0\1ocirc\0\xC3\xB4\0ocy\0\xD0\xBE\0oda\
sh\0\xE2\x8A\x9D\0odblac\0\xC5\x91\0odiv\0\xE2\xA8\xB8\0odot\0\xE2\
\x8A\x99\0odsold\0\xE2\xA6\xBC\0oelig\0\xC5\x93\0ofcir\0\xE2\xA6\xBF\
\0ofr\0\xF0\x9D\x94\xAC\0ogon\0\xCB\x9B\0\1ograve\0\xC3\xB2\0ogt\
\0\xE2\xA7\x81\0ohbar\0\xE2\xA6\xB5\0ohm\0\xCE\xA9\0oint\0\xE2\x88\xAE\0o\
larr\0\xE2\x86\xBA\0olcir\0\xE2\xA6\xBE\0olcross\0\xE2\xA6\xBB\0o\
line\0\xE2\x80\xBE\0olt\0\xE2\xA7\x80\0omacr\0\xC5\x8D\0omega\0\
\xCF\x89\0omicron\0\xCE\xBF\0omid\0\xE2\xA6\xB6\0ominus\0\xE2\x8A\
\x96\0oopf\0\xF0\x9D\x95\xA0\0opar\0\xE2\xA6\xB7\0operp\0\xE2\xA6\xB9\0o\
plus\0\xE2\x8A\x95\0or\0\xE2\x88\xA8\0orarr\0\xE2\x86\xBB\0ord\0\xE2\xA9\
\x9D\0order\0\xE2\x84\xB4\0orderof\0\xE2\x84\xB4\0\1ordf\0\xC2\xAA\
\0\1ordm\0\xC2\xBA\0origof\0\xE2\x8A\xB6\0oror\0\xE2\xA9\x96\0or\
slope\0\xE2\xA9\x97\0orv\0\xE2\xA9\x9B\0oscr\0\xE2\x84\xB4\0\1osla\
sh\0\xC3\xB8\0osol\0\xE2\x8A\x98\0\1otilde\0\xC3\xB5\0otimes\
\0\xE2\x8A\x97\0otimesas\0\xE2\xA8\xB6\0\1ouml\0\xC3\xB6\0ovbar\
\0\xE2\x8C\xBD\0par\0\xE2\x88\xA5\0\1para\0\xC2\xB6\0parallel\0\xE2\
\x88\xA5\0parsim\0\xE2\xAB\xB3\0parsl\0\xE2\xAB\xBD\0part\0\xE2\x88\x82\
\0pcy\0\xD0\xBF\0percnt\0%\0period\0.\0permil\
\0\xE2\x80\xB0\0perp\0\xE2\x8A\xA5\0pertenk\0\xE2\x80\xB1\0pfr\0\xF0\x9D\
\x94\xAD\0phi\0\xCF\x86\0phiv\0\xCF\x95\0phmmat\0\xE2\x84\xB3\0pho\
ne\0\xE2\x98\x8E\0pi\0\xCF\x80\0pitchfork\0\xE2\x8B\x94\0piv\0\xCF\
\x96\0planck\0\xE2\x84\x8F\0planckh\0\xE2\x84\x8E\0plankv\0\
\xE2\x84\x8F\0plus\0+\0plusacir\0\xE2\xA8\xA3\0plusb\0\xE2\x8A\
\x9E\0pluscir\0\xE2\xA8\xA2\0plusdo\0\xE2\x88\x94\0plusdu\0\
\xE2\xA8\xA5\0pluse\0\xE2\xA9\xB2\0\1plusmn\0\xC2\xB1\0plussim\
\0\xE2\xA8\xA6\0plustwo\0\xE2\xA8\xA7\0pm\0\xC2\xB1\0pointint\0\
\xE2\xA8\x95\0popf\0\xF0\x9D\x95\xA1\0\1pound\0\xC2\xA3\0pr\0\xE2\x89\xBA\0p\
rE\0\xE2\xAA\xB3\0prap\0\xE2\xAA\xB7\0prcue\0\xE2\x89\xBC\0pre\0\xE2\xAA\
\xAF\0prec\0\xE2\x89\xBA\0precapprox\0\xE2\xAA\xB7\0preccu\
rlyeq\0\xE2\x89\xBC\0preceq\0\xE2\xAA\xAF\0precnapprox\
\0\xE2\xAA\xB9\0precneqq\0\xE2\xAA\xB5\0precnsim\0\xE2\x8B\xA8\0p\
recsim\0\xE2\x89\xBE\0prime\0\xE2\x80\xB2\0primes\0\xE2\x84\x99\0\
prnE\0\xE2\xAA\xB5\0prnap\0\xE2\xAA\xB9\0prnsim\0\xE2\x8B\xA8\0pr\
od\0\xE2\x88\x8F\0profalar\0\xE2\x8C\xAE\0profline\0\xE2\x8C\x92\
\0profsurf\0\xE2\x8C\x93\0prop\0\xE2\x88\x9D\0propto\0\xE2\x88\
\x9D\0prsim\0\xE2\x89\xBE\0prurel\0\xE2\x8A\xB0\0pscr\0\xF0\x9D\x93\x85\
\0psi\0\xCF\x88\0puncsp\0\xE2\x80\x88\0qfr\0\xF0\x9D\x94\xAE\0qint\
\0\xE2\xA8\x8C\0qopf\0\xF0\x9D\x95\xA2\0qprime\0\xE2\x81\x97\0qscr\0\xF0\
\x9D\x93\x86\0quaternions\0\xE2\x84\x8D\0quatint\0\xE2\xA8\x96\0\
quest\0?\0questeq\0\xE2\x89\x9F\0\1quot\0\"\0rAar\
r\0\xE2\x87\x9B\0rArr\0\xE2\x87\x92\0rAtail\0\xE2\xA4\x9C\0rBarr\0\
\xE2\xA4\x8F\0rHar\0\xE2\xA5\xA4\0race\0\xE2\x88\xBD\0racute\0\xC5\x95\0\
radic\0\xE2\x88\x9A\0raemptyv\0\xE2\xA6\xB3\0rang\0\xE2\x9F\xA9\0\
rangd\0\xE2\xA6\x92\0range\0\xE2\xA6\xA5\0rangle\0\xE2\x9F\xA9\0\1\
raquo\0\xC2\xBB\0rarr\0\xE2\x86\x92\0rarrap\0\xE2\xA5\xB5\0rar\
rb\0\xE2\x87\xA5\0rarrbfs\0\xE2\xA4\xA0\0rarrc\0\xE2\xA4\xB3\0rar\
rfs\0\xE2\xA4\x9E\0rarrhk\0\xE2\x86\xAA\0rarrlp\0\xE2\x86\xAC\0ra\
rrpl\0\xE2\xA5\x85\0rarrsim\0\xE2\xA5\xB4\0rarrtl\0\xE2\x86\xA3\0\
rarrw\0\xE2\x86\x9D\0ratail\0\xE2\xA4\x9A\0ratio\0\xE2\x88\xB6\0r\
ationals\0\xE2\x84\x9A\0rbarr\0\xE2\xA4\x8D\0rbbrk\0\xE2\x9D\xB3\
\0rbrace\0}\0rbrack\0]\0rbrke\0\xE2\xA6\x8C\0rbr\
ksld\0\xE2\xA6\x8E\0rbrkslu\0\xE2\xA6\x90\0rcaron\0\xC5\x99\0r\
cedil\0\xC5\x97\0rceil\0\xE2\x8C\x89\0rcub\0}\0rcy\0\xD1\x80\
\0rdca\0\xE2\xA4\xB7\0rdldhar\0\xE2\xA5\xA9\0rdquo\0\xE2\x80\x9D\0\
rdquor\0\xE2\x80\x9D\0rdsh\0\xE2\x86\xB3\0real\0\xE2\x84\x9C\0rea\
line\0\xE2\x84\x9B\0realpart\0\xE2\x84\x9C\0reals\0\xE2\x84\x9D\0\
rect\0\xE2\x96\xAD\0\1reg\0\xC2\xAE\0rfisht\0\xE2\xA5\xBD\0rflo\
or\0\xE2\x8C\x8B\0rfr\0\xF0\x9D\x94\xAF\0rhard\0\xE2\x87\x81\0rharu\0\
\xE2\x87\x80\0rharul\0\xE2\xA5\xAC\0rho\0\xCF\x81\0rhov\0\xCF\xB1\0ri\
ghtarrow\0\xE2\x86\x92\0rightarrowtail\0\xE2\x86\xA3\0\
rightharpoondown\0\xE2\x87\x81\0rightharpoo\
nup\0\xE2\x87\x80\0rightleftarrows\0\xE2\x87\x84\0righ\
tleftharpoons\0\xE2\x87\x8C\0rightrightarro\
ws\0\xE2\x87\x89\0rightsquigarrow\0\xE2\x86\x9D\0right\
threetimes\0\xE2\x8B\x8C\0ring\0\xCB\x9A\0risingdot\
seq\0\xE2\x89\x93\0rlarr\0\xE2\x87\x84\0rlhar\0\xE2\x87\x8C\0rlm\0\
\xE2\x80\x8F\0rmoust\0\xE2\x8E\xB1\0rmoustache\0\xE2\x8E\xB1\0rn\
mid\0\xE2\xAB\xAE\0roang\0\xE2\x9F\xAD\0roarr\0\xE2\x87\xBE\0robr\
k\0\xE2\x9F\xA7\0ropar\0\xE2\xA6\x86\0ropf\0\xF0\x9D\x95\xA3\0roplus\
\0\xE2\xA8\xAE\0rotimes\0\xE2\xA8\xB5\0rpar\0)\0rpargt\0\xE2\
\xA6\x94\0rppolint\0\xE2\xA8\x92\0rrarr\0\xE2\x87\x89\0rsaquo\
\0\xE2\x80\xBA\0rscr\0\xF0\x9D\x93\x87\0rsh\0\xE2\x86\xB1\0rsqb\0]\0rs\
quo\0\xE2\x80\x99\0rsquor\0\xE2\x80\x99\0rthree\0\xE2\x8B\x8C\0rt\
imes\0\xE2\x8B\x8A\0rtri\0\xE2\x96\xB9\0rtrie\0\xE2\x8A\xB5\0rtri\
f\0\xE2\x96\xB8\0rtriltri\0\xE2\xA7\x8E\0ruluhar\0\xE2\xA5\xA8\0r\
x\0\xE2\x84\x9E\0sacute\0\xC5\x9B\0sbquo\0\xE2\x80\x9A\0sc\0\xE2\x89\xBB\
\0scE\0\xE2\xAA\xB4\0scap\0\xE2\xAA\xB8\0scaron\0\xC5\xA1\0sccu\
e\0\xE2\x89\xBD\0sce\0\xE2\xAA\xB0\0scedil\0\xC5\x9F\0scirc\0\xC5\x9D\
\0scnE\0\xE2\xAA\xB6\0scnap\0\xE2\xAA\xBA\0scnsim\0\xE2\x8B\xA9\0s\
cpolint\0\xE2\xA8\x93\0scsim\0\xE2\x89\xBF\0scy\0\xD1\x81\0sdo\
t\0\xE2\x8B\x85\0sdotb\0\xE2\x8A\xA1\0sdote\0\xE2\xA9\xA6\0seArr\0\
\xE2\x87\x98\0searhk\0\xE2\xA4\xA5\0searr\0\xE2\x86\x98\0searrow\
\0\xE2\x86\x98\0\1sect\0\xC2\xA7\0semi\0;\0seswar\0\xE2\xA4\xA9\0\
setminus\0\xE2\x88\x96\0setmn\0\xE2\x88\x96\0sext\0\xE2\x9C\xB6\0\
sfr\0\xF0\x9D\x94\xB0\0sfrown\0\xE2\x8C\xA2\0sharp\0\xE2\x99\xAF\0sh\
chcy\0\xD1\x89\0shcy\0\xD1\x88\0shortmid\0\xE2\x88\xA3\0sho\
rtparallel\0\xE2\x88\xA5\0\1shy\0\xC2\xAD\0sigma\0\xCF\x83\0\
sigmaf\0\xCF\x82\0sigmav\0\xCF\x82\0sim\0\xE2\x88\xBC\0simd\
ot\0\xE2\xA9\xAA\0sime\0\xE2\x89\x83\0simeq\0\xE2\x89\x83\0simg\0\xE2\
\xAA\x9E\0simgE\0\xE2\xAA\xA0\0siml\0\xE2\xAA\x9D\0simlE\0\xE2\xAA\x9F\0\
simne\0\xE2\x89\x86\0simplus\0\xE2\xA8\xA4\0simrarr\0\xE2\xA5\
\xB2\0slarr\0\xE2\x86\x90\0smallsetminus\0\xE2\x88\x96\0sm\
ashp\0\xE2\xA8\xB3\0smeparsl\0\xE2\xA7\xA4\0smid\0\xE2\x88\xA3\0s\
mile\0\xE2\x8C\xA3\0smt\0\xE2\xAA\xAA\0smte\0\xE2\xAA\xAC\0smtes\0\
\xE2\xAA\xAC\0softcy\0\xD1\x8C\0sol\0/\0solb\0\xE2\xA7\x84\0sol\
bar\0\xE2\x8C\xBF\0sopf\0\xF0\x9D\x95\xA4\0spades\0\xE2\x99\xA0\0spa\
desuit\0\xE2\x99\xA0\0spar\0\xE2\x88\xA5\0sqcap\0\xE2\x8A\x93\0sq\
caps\0\xE2\x8A\x93\0sqcup\0\xE2\x8A\x94\0sqcups\0\xE2\x8A\x94\0sq\
sub\0\xE2\x8A\x8F\0sqsube\0\xE2\x8A\x91\0sqsubset\0\xE2\x8A\x8F\0\
sqsubseteq\0\xE2\x8A\x91\0sqsup\0\xE2\x8A\x90\0sqsupe\0\
\xE2\x8A\x92\0sqsupset\0\xE2\x8A\x90\0sqsupseteq\0\xE2\x8A\x92\0\
squ\0\xE2\x96\xA1\0square\0\xE2\x96\xA1\0squarf\0\xE2\x96\xAA\0sq\
uf\0\xE2\x96\xAA\0srarr\0\xE2\x86\x92\0sscr\0\xF0\x9D\x93\x88\0ssetm\
n\0\xE2\x88\x96\0ssmile\0\xE2\x8C\xA3\0sstarf\0\xE2\x8B\x86\0star\
\0\xE2\x98\x86\0starf\0\xE2\x98\x85\0straightepsilon\0\xCF\
\xB5\0straightphi\0\xCF\x95\0strns\0\xC2\xAF\0sub\0\xE2\x8A\
\x82\0subE\0\xE2\xAB\x85\0subdot\0\xE2\xAA\xBD\0sube\0\xE2\x8A\x86\0s\
ubedot\0\xE2\xAB\x83\0submult\0\xE2\xAB\x81\0subnE\0\xE2\xAB\x8B\
\0subne\0\xE2\x8A\x8A\0subplus\0\xE2\xAA\xBF\0subrarr\0\xE2\
\xA5\xB9\0subset\0\xE2\x8A\x82\0subseteq\0\xE2\x8A\x86\0subse\
teqq\0\xE2\xAB\x85\0subsetneq\0\xE2\x8A\x8A\0subsetneq\
q\0\xE2\xAB\x8B\0subsim\0\xE2\xAB\x87\0subsub\0\xE2\xAB\x95\0subs\
up\0\xE2\xAB\x93\0succ\0\xE2\x89\xBB\0succapprox\0\xE2\xAA\xB8\0s\
ucccurlyeq\0\xE2\x89\xBD\0succeq\0\xE2\xAA\xB0\0succna\
pprox\0\xE2\xAA\xBA\0succneqq\0\xE2\xAA\xB6\0succnsim\0\
\xE2\x8B\xA9\0succsim\0\xE2\x89\xBF\0sum\0\xE2\x88\x91\0sung\0\xE2\x99\xAA\
\0sup\0\xE2\x8A\x83\0\1sup1\0\xC2\xB9\0\1sup2\0\xC2\xB2\0\1sup3\
\0\xC2\xB3\0supE\0\xE2\xAB\x86\0supdot\0\xE2\xAA\xBE\0supdsub\0\
\xE2\xAB\x98\0supe\0\xE2\x8A\x87\0supedot\0\xE2\xAB\x84\0suphsol\
\0\xE2\x9F\x89\0suphsub\0\xE2\xAB\x97\0suplarr\0\xE2\xA5\xBB\0sup\
mult\0\xE2\xAB\x82\0supnE\0\xE2\xAB\x8C\0supne\0\xE2\x8A\x8B\0sup\
plus\0\xE2\xAB\x80\0supset\0\xE2\x8A\x83\0supseteq\0\xE2\x8A\x87\
\0supseteqq\0\xE2\xAB\x86\0supsetneq\0\xE2\x8A\x8B\0sup\
setneqq\0\xE2\xAB\x8C\0supsim\0\xE2\xAB\x88\0supsub\0\xE2\xAB\
\x94\0supsup\0\xE2\xAB\x96\0swArr\0\xE2\x87\x99\0swarhk\0\xE2\xA4\
\xA6\0swarr\0\xE2\x86\x99\0swarrow\0\xE2\x86\x99\0swnwar\0\xE2\
\xA4\xAA\0\1szlig\0\xC3\x9F\0target\0\xE2\x8C\x96\0tau\0\xCF\x84\0t\
brk\0\xE2\x8E\xB4\0tcaron\0\xC5\xA5\0tcedil\0\xC5\xA3\0tcy\0\
\xD1\x82\0tdot\0\xE2\x83\x9B\0telrec\0\xE2\x8C\x95\0tfr\0\xF0\x9D\x94\xB1\0\
there4\0\xE2\x88\xB4\0therefore\0\xE2\x88\xB4\0theta\0\xCE\
\xB8\0thetasym\0\xCF\x91\0thetav\0\xCF\x91\0thickapp\
rox\0\xE2\x89\x88\0thicksim\0\xE2\x88\xBC\0thinsp\0\xE2\x80\x89\0\
thkap\0\xE2\x89\x88\0thksim\0\xE2\x88\xBC\0\1thorn\0\xC3\xBE\0t\
ilde\0\xCB\x9C\0\1times\0\xC3\x97\0timesb\0\xE2\x8A\xA0\0tim\
esbar\0\xE2\xA8\xB1\0timesd\0\xE2\xA8\xB0\0tint\0\xE2\x88\xAD\0to\
ea\0\xE2\xA4\xA8\0top\0\xE2\x8A\xA4\0topbot\0\xE2\x8C\xB6\0topcir\
\0\xE2\xAB\xB1\0topf\0\xF0\x9D\x95\xA5\0topfork\0\xE2\xAB\x9A\0tosa\0\
\xE2\xA4\xA9\0tprime\0\xE2\x80\xB4\0trade\0\xE2\x84\xA2\0triangl\
e\0\xE2\x96\xB5\0triangledown\0\xE2\x96\xBF\0trianglel\
eft\0\xE2\x97\x83\0trianglelefteq\0\xE2\x8A\xB4\0trian\
gleq\0\xE2\x89\x9C\0triangleright\0\xE2\x96\xB9\0trian\
glerighteq\0\xE2\x8A\xB5\0tridot\0\xE2\x97\xAC\0trie\0\xE2\
\x89\x9C\0triminus\0\xE2\xA8\xBA\0triplus\0\xE2\xA8\xB9\0tris\
b\0\xE2\xA7\x8D\0tritime\0\xE2\xA8\xBB\0trpezium\0\xE2\x8F\xA2\0t\
scr\0\xF0\x9D\x93\x89\0tscy\0\xD1\x86\0tshcy\0\xD1\x9B\0tstrok\
\0\xC5\xA7\0twixt\0\xE2\x89\xAC\0twoheadleftarrow\0\xE2\
\x86\x9E\0twoheadrightarrow\0\xE2\x86\xA0\0uArr\0\xE2\x87\
\x91\0uHar\0\xE2\xA5\xA3\0\1uacute\0\xC3\xBA\0uarr\0\xE2\x86\x91\0u\
brcy\0\xD1\x9E\0ubreve\0\xC5\xAD\0\1ucirc\0\xC3\xBB\0ucy\0\
\xD1\x83\0udarr\0\xE2\x87\x85\0udblac\0\xC5\xB1\0udhar\0\xE2\xA5\xAE\
\0ufisht\0\xE2\xA5\xBE\0ufr\0\xF0\x9D\x94\xB2\0\1ugrave\0\xC3\xB9\0\
uharl\0\xE2\x86\xBF\0uharr\0\xE2\x86\xBE\0uhblk\0\xE2\x96\x80\0ul\
corn\0\xE2\x8C\x9C\0ulcorner\0\xE2\x8C\x9C\0ulcrop\0\xE2\x8C\x8F\
\0ultri\0\xE2\x97\xB8\0umacr\0\xC5\xAB\0\1uml\0\xC2\xA8\0uogo\
n\0\xC5\xB3\0uopf\0\xF0\x9D\x95\xA6\0uparrow\0\xE2\x86\x91\0updow\
narrow\0\xE2\x86\x95\0upharpoonleft\0\xE2\x86\xBF\0uph\
arpoonright\0\xE2\x86\xBE\0uplus\0\xE2\x8A\x8E\0upsi\0\xCF\
\x85\0upsih\0\xCF\x92\0upsilon\0\xCF\x85\0upuparrows\
\0\xE2\x87\x88\0urcorn\0\xE2\x8C\x9D\0urcorner\0\xE2\x8C\x9D\0urc\
rop\0\xE2\x8C\x8E\0uring\0\xC5\xAF\0urtri\0\xE2\x97\xB9\0uscr\0\
\xF0\x9D\x93\x8A\0utdot\0\xE2\x8B\xB0\0utilde\0\xC5\xA9\0utri\0\xE2\x96\
\xB5\0utrif\0\xE2\x96\xB4\0uuarr\0\xE2\x87\x88\0\1uuml\0\xC3\xBC\0u\
wangle\0\xE2\xA6\xA7\0vArr\0\xE2\x87\x95\0vBar\0\xE2\xAB\xA8\0vBa\
rv\0\xE2\xAB\xA9\0vDash\0\xE2\x8A\xA8\0vangrt\0\xE2\xA6\x9C\0vare\
psilon\0\xCF\xB5\0varkappa\0\xCF\xB0\0varnothing\
\0\xE2\x88\x85\0varphi\0\xCF\x95\0varpi\0\xCF\x96\0varpropt\
o\0\xE2\x88\x9D\0varr\0\xE2\x86\x95\0varrho\0\xCF\xB1\0varsigm\
a\0\xCF\x82\0varsubsetneq\0\xE2\x8A\x8A\0varsubsetn\
eqq\0\xE2\xAB\x8B\0varsupsetneq\0\xE2\x8A\x8B\0varsups\
etneqq\0\xE2\xAB\x8C\0vartheta\0\xCF\x91\0vartriang\
leleft\0\xE2\x8A\xB2\0vartriangleright\0\xE2\x8A\xB3\0\
vcy\0\xD0\xB2\0vdash\0\xE2\x8A\xA2\0vee\0\xE2\x88\xA8\0veebar\0\
\xE2\x8A\xBB\0veeeq\0\xE2\x89\x9A\0vellip\0\xE2\x8B\xAE\0verbar\0\
|\0vert\0|\0vfr\0\xF0\x9D\x94\xB3\0vltri\0\xE2\x8A\xB2\0vnsu\
b\0\xE2\x8A\x82\0vnsup\0\xE2\x8A\x83\0vopf\0\xF0\x9D\x95\xA7\0vprop\0\
\xE2\x88\x9D\0vrtri\0\xE2\x8A\xB3\0vscr\0\xF0\x9D\x93\x8B\0vsubnE\0\xE2\
\xAB\x8B\0vsubne\0\xE2\x8A\x8A\0vsupnE\0\xE2\xAB\x8C\0vsupne\0\
\xE2\x8A\x8B\0vzigzag\0\xE2\xA6\x9A\0wcirc\0\xC5\xB5\0wedbar\0\
\xE2\xA9\x9F\0wedge\0\xE2\x88\xA7\0wedgeq\0\xE2\x89\x99\0weierp\0\
\xE2\x84\x98\0wfr\0\xF0\x9D\x94\xB4\0wopf\0\xF0\x9D\x95\xA8\0wp\0\xE2\x84\x98\0wr\
\0\xE2\x89\x80\0wreath\0\xE2\x89\x80\0wscr\0\xF0\x9D\x93\x8C\0xcap\0\xE2\
\x8B\x82\0xcirc\0\xE2\x97\xAF\0xcup\0\xE2\x8B\x83\0xdtri\0\xE2\x96\xBD\0\
xfr\0\xF0\x9D\x94\xB5\0xhArr\0\xE2\x9F\xBA\0xharr\0\xE2\x9F\xB7\0xi\0\
\xCE\xBE\0xlArr\0\xE2\x9F\xB8\0xlarr\0\xE2\x9F\xB5\0xmap\0\xE2\x9F\xBC\0\
xnis\0\xE2\x8B\xBB\0xodot\0\xE2\xA8\x80\0xopf\0\xF0\x9D\x95\xA9\0xop\
lus\0\xE2\xA8\x81\0xotime\0\xE2\xA8\x82\0xrArr\0\xE2\x9F\xB9\0xra\
rr\0\xE2\x9F\xB6\0xscr\0\xF0\x9D\x93\x8D\0xsqcup\0\xE2\xA8\x86\0xupl\
us\0\xE2\xA8\x84\0xutri\0\xE2\x96\xB3\0xvee\0\xE2\x8B\x81\0xwedge\
\0\xE2\x8B\x80\0\1yacute\0\xC3\xBD\0yacy\0\xD1\x8F\0ycirc\0\xC5\xB7\
\0ycy\0\xD1\x8B\0\1yen\0\xC2\xA5\0yfr\0\xF0\x9D\x94\xB6\0yicy\0\xD1\x97\
\0yopf\0\xF0\x9D\x95\xAA\0yscr\0\xF0\x9D\x93\x8E\0yucy\0\xD1\x8E\0\1yu\
ml\0\xC3\xBF\0zacute\0\xC5\xBA\0zcaron\0\xC5\xBE\0zcy\0\xD0\xB7\
\0zdot\0\xC5\xBC\0zeetrf\0\xE2\x84\xA8\0zeta\0\xCE\xB6\0zfr\0\
\xF0\x9D\x94\xB7\0zhcy\0\xD0\xB6\0zigrarr\0\xE2\x87\x9D\0zopf\0\xF0\x9D\
\x95\xAB\0zscr\0\xF0\x9D\x93\x8F\0zwj\0\xE2\x80\x8D\0zwnj\0\xE2\x80\x8C\0..\
\0.\
";

#ifdef CONFIG_XML_FANCY_ENCODE
struct xml_encode16_entry {
	char16_t xe16_chr; /* Unicode character. */
	uint16_t xe16_offset; /* Offset into `xml_entity_db' */
};
struct xml_encode32_entry {
	char32_t xe32_chr; /* Unicode character. */
	uint16_t xe32_offset; /* Offset into `xml_entity_db' */
};
PRIVATE struct xml_encode16_entry const xml_encode16_db[1314] = {
	{ 0x0009, 0x1b18 }, /* "Tab" */
	{ 0x000A, 0xfb6 },  /* "NewLine" */
	{ 0x0021, 0x2ff5 }, /* "excl" */
	{ 0x0022, 0x4bb5 }, /* "quot" */
	{ 0x0023, 0x45c9 }, /* "num" */
	{ 0x0024, 0x2c69 }, /* "dollar" */
	{ 0x0025, 0x48e8 }, /* "percnt" */
	{ 0x0026, 0x2019 }, /* "amp" */
	{ 0x0027, 0x2160 }, /* "apos" */
	{ 0x0028, 0x3ceb }, /* "lpar" */
	{ 0x0029, 0x4f71 }, /* "rpar" */
	{ 0x002A, 0x2193 }, /* "ast" */
	{ 0x002B, 0x4984 }, /* "plus" */
	{ 0x002C, 0x28d9 }, /* "comma" */
	{ 0x002E, 0x48f1 }, /* "period" */
	{ 0x002F, 0x528e }, /* "sol" */
	{ 0x003A, 0x28ba }, /* "colon" */
	{ 0x003B, 0x510e }, /* "semi" */
	{ 0x003C, 0x3d9c }, /* "lt" */
	{ 0x003D, 0x2438 }, /* "bne" */
	{ 0x003E, 0x3335 }, /* "gt" */
	{ 0x003F, 0x4ba0 }, /* "quest" */
	{ 0x0040, 0x28e1 }, /* "commat" */
	{ 0x005B, 0x3d75 }, /* "lsqb" */
	{ 0x005C, 0x267e }, /* "bsol" */
	{ 0x005D, 0x4fb7 }, /* "rsqb" */
	{ 0x005E, 0x906 },  /* "Hat" */
	{ 0x005F, 0x3cc5 }, /* "lowbar" */
	{ 0x0060, 0x3306 }, /* "grave" */
	{ 0x0066, 0x307e }, /* "fjlig" */
	{ 0x007B, 0x3932 }, /* "lcub" */
	{ 0x007C, 0x5c62 }, /* "vert" */
	{ 0x007D, 0x4d53 }, /* "rcub" */
	{ 0x00A0, 0x40b0 }, /* "nbsp" */
	{ 0x00A1, 0x3541 }, /* "iexcl" */
	{ 0x00A2, 0x279c }, /* "cent" */
	{ 0x00A3, 0x4a0f }, /* "pound" */
	{ 0x00A4, 0x2a92 }, /* "curren" */
	{ 0x00A5, 0x5e69 }, /* "yen" */
	{ 0x00A6, 0x264d }, /* "brvbar" */
	{ 0x00A7, 0x5106 }, /* "sect" */
	{ 0x00A8, 0x40a },  /* "Dot" */
	{ 0x00A9, 0x142 },  /* "COPY" */
	{ 0x00AA, 0x4819 }, /* "ordf" */
	{ 0x00AB, 0x383b }, /* "laquo" */
	{ 0x00AC, 0x42f1 }, /* "not" */
	{ 0x00AD, 0x5190 }, /* "shy" */
	{ 0x00AE, 0x1630 }, /* "REG" */
	{ 0x00AF, 0x3e4e }, /* "macr" */
	{ 0x00B0, 0x2b8d }, /* "deg" */
	{ 0x00B1, 0x49f1 }, /* "pm" */
	{ 0x00B2, 0x5553 }, /* "sup2" */
	{ 0x00B3, 0x555c }, /* "sup3" */
	{ 0x00B4, 0x1fb1 }, /* "acute" */
	{ 0x00B5, 0x3efd }, /* "micro" */
	{ 0x00B6, 0x48ae }, /* "para" */
	{ 0x00B7, 0x3f23 }, /* "middot" */
	{ 0x00B8, 0x2786 }, /* "cedil" */
	{ 0x00B9, 0x554a }, /* "sup1" */
	{ 0x00BA, 0x4822 }, /* "ordm" */
	{ 0x00BB, 0x4c40 }, /* "raquo" */
	{ 0x00BC, 0x30f7 }, /* "frac14" */
	{ 0x00BD, 0x33f1 }, /* "half" */
	{ 0x00BE, 0x3139 }, /* "frac34" */
	{ 0x00BF, 0x368f }, /* "iquest" */
	{ 0x00C0, 0x41 },   /* "Agrave" */
	{ 0x00C1, 0x12 },   /* "Aacute" */
	{ 0x00C2, 0x27 },   /* "Acirc" */
	{ 0x00C3, 0xaa },   /* "Atilde" */
	{ 0x00C4, 0xb5 },   /* "Auml" */
	{ 0x00C5, 0x8b },   /* "Aring" */
	{ 0x00C6, 0x1 },    /* "AElig" */
	{ 0x00C7, 0x18c },  /* "Ccedil" */
	{ 0x00C8, 0x6b7 },  /* "Egrave" */
	{ 0x00C9, 0x680 },  /* "Eacute" */
	{ 0x00CA, 0x695 },  /* "Ecirc" */
	{ 0x00CB, 0x765 },  /* "Euml" */
	{ 0x00CC, 0x9c2 },  /* "Igrave" */
	{ 0x00CD, 0x996 },  /* "Iacute" */
	{ 0x00CE, 0x9a1 },  /* "Icirc" */
	{ 0x00CF, 0xa7b },  /* "Iuml" */
	{ 0x00D0, 0x678 },  /* "ETH" */
	{ 0x00D1, 0x13fa }, /* "Ntilde" */
	{ 0x00D2, 0x1443 }, /* "Ograve" */
	{ 0x00D3, 0x1414 }, /* "Oacute" */
	{ 0x00D4, 0x141f }, /* "Ocirc" */
	{ 0x00D5, 0x14bd }, /* "Otilde" */
	{ 0x00D6, 0x14d3 }, /* "Ouml" */
	{ 0x00D7, 0x5769 }, /* "times" */
	{ 0x00D8, 0x14b2 }, /* "Oslash" */
	{ 0x00D9, 0x1c3d }, /* "Ugrave" */
	{ 0x00DA, 0x1be5 }, /* "Uacute" */
	{ 0x00DB, 0x1c19 }, /* "Ucirc" */
	{ 0x00DC, 0x1d9a }, /* "Uuml" */
	{ 0x00DD, 0x1eda }, /* "Yacute" */
	{ 0x00DE, 0x1af4 }, /* "THORN" */
	{ 0x00DF, 0x5684 }, /* "szlig" */
	{ 0x00E0, 0x1fdc }, /* "agrave" */
	{ 0x00E1, 0x1f7b }, /* "aacute" */
	{ 0x00E2, 0x1fa7 }, /* "acirc" */
	{ 0x00E3, 0x21b0 }, /* "atilde" */
	{ 0x00E4, 0x21bb }, /* "auml" */
	{ 0x00E5, 0x2180 }, /* "aring" */
	{ 0x00E6, 0x1fc2 }, /* "aelig" */
	{ 0x00E7, 0x2754 }, /* "ccedil" */
	{ 0x00E8, 0x2e3a }, /* "egrave" */
	{ 0x00E9, 0x2dcc }, /* "eacute" */
	{ 0x00EA, 0x2df5 }, /* "ecirc" */
	{ 0x00EB, 0x2fe4 }, /* "euml" */
	{ 0x00EC, 0x355c }, /* "igrave" */
	{ 0x00ED, 0x3516 }, /* "iacute" */
	{ 0x00EE, 0x3528 }, /* "icirc" */
	{ 0x00EF, 0x36fc }, /* "iuml" */
	{ 0x00F0, 0x2fdc }, /* "eth" */
	{ 0x00F1, 0x4562 }, /* "ntilde" */
	{ 0x00F2, 0x4733 }, /* "ograve" */
	{ 0x00F3, 0x46b0 }, /* "oacute" */
	{ 0x00F4, 0x46cd }, /* "ocirc" */
	{ 0x00F5, 0x4870 }, /* "otilde" */
	{ 0x00F6, 0x4893 }, /* "ouml" */
	{ 0x00F7, 0x2c1c }, /* "div" */
	{ 0x00F8, 0x485c }, /* "oslash" */
	{ 0x00F9, 0x5996 }, /* "ugrave" */
	{ 0x00FA, 0x592c }, /* "uacute" */
	{ 0x00FB, 0x5953 }, /* "ucirc" */
	{ 0x00FC, 0x5af7 }, /* "uuml" */
	{ 0x00FD, 0x5e46 }, /* "yacute" */
	{ 0x00FE, 0x5756 }, /* "thorn" */
	{ 0x00FF, 0x5e9e }, /* "yuml" */
	{ 0x0100, 0x54 },   /* "Amacr" */
	{ 0x0101, 0x2005 }, /* "amacr" */
	{ 0x0102, 0x1c },   /* "Abreve" */
	{ 0x0103, 0x1f85 }, /* "abreve" */
	{ 0x0104, 0x65 },   /* "Aogon" */
	{ 0x0105, 0x2122 }, /* "aogon" */
	{ 0x0106, 0x14a },  /* "Cacute" */
	{ 0x0107, 0x26d8 }, /* "cacute" */
	{ 0x0108, 0x196 },  /* "Ccirc" */
	{ 0x0109, 0x275e }, /* "ccirc" */
	{ 0x010A, 0x1ab },  /* "Cdot" */
	{ 0x010B, 0x277d }, /* "cdot" */
	{ 0x010C, 0x181 },  /* "Ccaron" */
	{ 0x010D, 0x2749 }, /* "ccaron" */
	{ 0x010E, 0x350 },  /* "Dcaron" */
	{ 0x010F, 0x2b52 }, /* "dcaron" */
	{ 0x0110, 0x666 },  /* "Dstrok" */
	{ 0x0111, 0x2d5c }, /* "dstrok" */
	{ 0x0112, 0x6cd },  /* "Emacr" */
	{ 0x0113, 0x2e86 }, /* "emacr" */
	{ 0x0116, 0x6a5 },  /* "Edot" */
	{ 0x0117, 0x2e10 }, /* "edot" */
	{ 0x0118, 0x704 },  /* "Eogon" */
	{ 0x0119, 0x2ee0 }, /* "eogon" */
	{ 0x011A, 0x68a },  /* "Ecaron" */
	{ 0x011B, 0x2de1 }, /* "ecaron" */
	{ 0x011C, 0x82b },  /* "Gcirc" */
	{ 0x011D, 0x31e1 }, /* "gcirc" */
	{ 0x011E, 0x817 },  /* "Gbreve" */
	{ 0x011F, 0x31d7 }, /* "gbreve" */
	{ 0x0120, 0x83b },  /* "Gdot" */
	{ 0x0121, 0x31f1 }, /* "gdot" */
	{ 0x0122, 0x821 },  /* "Gcedil" */
	{ 0x0124, 0x90c },  /* "Hcirc" */
	{ 0x0125, 0x3436 }, /* "hcirc" */
	{ 0x0126, 0x953 },  /* "Hstrok" */
	{ 0x0127, 0x34f5 }, /* "hstrok" */
	{ 0x0128, 0xa67 },  /* "Itilde" */
	{ 0x0129, 0x36e8 }, /* "itilde" */
	{ 0x012A, 0x9d3 },  /* "Imacr" */
	{ 0x012B, 0x35a0 }, /* "imacr" */
	{ 0x012E, 0xa43 },  /* "Iogon" */
	{ 0x012F, 0x3669 }, /* "iogon" */
	{ 0x0130, 0x9b1 },  /* "Idot" */
	{ 0x0131, 0x35cd }, /* "imath" */
	{ 0x0132, 0x984 },  /* "IJlig" */
	{ 0x0133, 0x3597 }, /* "ijlig" */
	{ 0x0134, 0xa83 },  /* "Jcirc" */
	{ 0x0135, 0x3704 }, /* "jcirc" */
	{ 0x0136, 0xadc },  /* "Kcedil" */
	{ 0x0137, 0x3760 }, /* "kcedil" */
	{ 0x0138, 0x377a }, /* "kgreen" */
	{ 0x0139, 0xb18 },  /* "Lacute" */
	{ 0x013A, 0x37e8 }, /* "lacute" */
	{ 0x013B, 0xb57 },  /* "Lcedil" */
	{ 0x013C, 0x391e }, /* "lcedil" */
	{ 0x013D, 0xb4d },  /* "Lcaron" */
	{ 0x013E, 0x3914 }, /* "lcaron" */
	{ 0x013F, 0xdcc },  /* "Lmidot" */
	{ 0x0140, 0x3b9a }, /* "lmidot" */
	{ 0x0141, 0xe90 },  /* "Lstrok" */
	{ 0x0142, 0x3d91 }, /* "lstrok" */
	{ 0x0143, 0xf06 },  /* "Nacute" */
	{ 0x0144, 0x4049 }, /* "nacute" */
	{ 0x0145, 0xf1a },  /* "Ncedil" */
	{ 0x0146, 0x40e0 }, /* "ncedil" */
	{ 0x0147, 0xf10 },  /* "Ncaron" */
	{ 0x0148, 0x40d6 }, /* "ncaron" */
	{ 0x0149, 0x4077 }, /* "napos" */
	{ 0x014A, 0x670 },  /* "ENG" */
	{ 0x014B, 0x2ed0 }, /* "eng" */
	{ 0x014C, 0x144d }, /* "Omacr" */
	{ 0x014D, 0x4791 }, /* "omacr" */
	{ 0x0150, 0x142f }, /* "Odblac" */
	{ 0x0151, 0x46e7 }, /* "odblac" */
	{ 0x0152, 0x140a }, /* "OElig" */
	{ 0x0153, 0x470e }, /* "oelig" */
	{ 0x0154, 0x1637 }, /* "Racute" */
	{ 0x0155, 0x4bf6 }, /* "racute" */
	{ 0x0156, 0x1668 }, /* "Rcedil" */
	{ 0x0157, 0x4d3f }, /* "rcedil" */
	{ 0x0158, 0x165e }, /* "Rcaron" */
	{ 0x0159, 0x4d35 }, /* "rcaron" */
	{ 0x015A, 0x18f5 }, /* "Sacute" */
	{ 0x015B, 0x5026 }, /* "sacute" */
	{ 0x015C, 0x191a }, /* "Scirc" */
	{ 0x015D, 0x5078 }, /* "scirc" */
	{ 0x015E, 0x1910 }, /* "Scedil" */
	{ 0x015F, 0x506e }, /* "scedil" */
	{ 0x0160, 0x1906 }, /* "Scaron" */
	{ 0x0161, 0x5052 }, /* "scaron" */
	{ 0x0162, 0x1b2f }, /* "Tcedil" */
	{ 0x0163, 0x56b2 }, /* "tcedil" */
	{ 0x0164, 0x1b25 }, /* "Tcaron" */
	{ 0x0165, 0x56a8 }, /* "tcaron" */
	{ 0x0166, 0x1bda }, /* "Tstrok" */
	{ 0x0167, 0x58da }, /* "tstrok" */
	{ 0x0168, 0x1d8f }, /* "Utilde" */
	{ 0x0169, 0x5acf }, /* "utilde" */
	{ 0x016A, 0x1c47 }, /* "Umacr" */
	{ 0x016B, 0x59eb }, /* "umacr" */
	{ 0x016C, 0x1c0e }, /* "Ubreve" */
	{ 0x016D, 0x5948 }, /* "ubreve" */
	{ 0x016E, 0x1d7c }, /* "Uring" */
	{ 0x016F, 0x5aa8 }, /* "uring" */
	{ 0x0170, 0x1c29 }, /* "Udblac" */
	{ 0x0171, 0x596d }, /* "udblac" */
	{ 0x0172, 0x1ca8 }, /* "Uogon" */
	{ 0x0173, 0x59fc }, /* "uogon" */
	{ 0x0174, 0x1e6e }, /* "Wcirc" */
	{ 0x0175, 0x5cf0 }, /* "wcirc" */
	{ 0x0176, 0x1ee4 }, /* "Ycirc" */
	{ 0x0177, 0x5e58 }, /* "ycirc" */
	{ 0x0178, 0x1f11 }, /* "Yuml" */
	{ 0x0179, 0x1f21 }, /* "Zacute" */
	{ 0x017A, 0x5ea6 }, /* "zacute" */
	{ 0x017B, 0x1f3c }, /* "Zdot" */
	{ 0x017C, 0x5ec1 }, /* "zdot" */
	{ 0x017D, 0x1f2b }, /* "Zcaron" */
	{ 0x017E, 0x5eb0 }, /* "zcaron" */
	{ 0x0192, 0x30a3 }, /* "fnof" */
	{ 0x01B5, 0x35df }, /* "imped" */
	{ 0x01F5, 0x31b2 }, /* "gacute" */
	{ 0x0237, 0x371d }, /* "jmath" */
	{ 0x02C6, 0x27f2 }, /* "circ" */
	{ 0x02C7, 0x8fd },  /* "Hacek" */
	{ 0x02D8, 0x11c },  /* "Breve" */
	{ 0x02D9, 0x2c7c }, /* "dot" */
	{ 0x02DA, 0x4ecf }, /* "ring" */
	{ 0x02DB, 0x472a }, /* "ogon" */
	{ 0x02DC, 0x575f }, /* "tilde" */
	{ 0x02DD, 0x2b49 }, /* "dblac" */
	{ 0x0311, 0x58b },  /* "DownBreve" */
	{ 0x0391, 0x4b },   /* "Alpha" */
	{ 0x0392, 0x101 },  /* "Beta" */
	{ 0x0393, 0x804 },  /* "Gamma" */
	{ 0x0394, 0x369 },  /* "Delta" */
	{ 0x0395, 0x717 },  /* "Epsilon" */
	{ 0x0396, 0x1f57 }, /* "Zeta" */
	{ 0x0397, 0x75d },  /* "Eta" */
	{ 0x0398, 0x1b57 }, /* "Theta" */
	{ 0x0399, 0xa56 },  /* "Iota" */
	{ 0x039A, 0xad3 },  /* "Kappa" */
	{ 0x039B, 0xb22 },  /* "Lambda" */
	{ 0x039C, 0xef8 },  /* "Mu" */
	{ 0x039D, 0x1404 }, /* "Nu" */
	{ 0x039E, 0x1ea7 }, /* "Xi" */
	{ 0x039F, 0x145f }, /* "Omicron" */
	{ 0x03A0, 0x153d }, /* "Pi" */
	{ 0x03A1, 0x16cb }, /* "Rho" */
	{ 0x03A3, 0x197e }, /* "Sigma" */
	{ 0x03A4, 0x1b1e }, /* "Tau" */
	{ 0x03A5, 0x1d71 }, /* "Upsilon" */
	{ 0x03A6, 0x1536 }, /* "Phi" */
	{ 0x03A7, 0x1d3 },  /* "Chi" */
	{ 0x03A8, 0x15fa }, /* "Psi" */
	{ 0x03A9, 0x474f }, /* "ohm" */
	{ 0x03B1, 0x1ffc }, /* "alpha" */
	{ 0x03B2, 0x22b2 }, /* "beta" */
	{ 0x03B3, 0x31bc }, /* "gamma" */
	{ 0x03B4, 0x2b94 }, /* "delta" */
	{ 0x03B5, 0x2f11 }, /* "epsi" */
	{ 0x03B6, 0x5ed4 }, /* "zeta" */
	{ 0x03B7, 0x2fd4 }, /* "eta" */
	{ 0x03B8, 0x56f9 }, /* "theta" */
	{ 0x03B9, 0x367c }, /* "iota" */
	{ 0x03BA, 0x374d }, /* "kappa" */
	{ 0x03BB, 0x380a }, /* "lambda" */
	{ 0x03BC, 0x3fa7 }, /* "mu" */
	{ 0x03BD, 0x45c3 }, /* "nu" */
	{ 0x03BE, 0x5d9d }, /* "xi" */
	{ 0x03BF, 0x47a3 }, /* "omicron" */
	{ 0x03C0, 0x4947 }, /* "pi" */
	{ 0x03C1, 0x4e0f }, /* "rho" */
	{ 0x03C2, 0x51a0 }, /* "sigmaf" */
	{ 0x03C3, 0x5197 }, /* "sigma" */
	{ 0x03C4, 0x5698 }, /* "tau" */
	{ 0x03C5, 0x5a5a }, /* "upsi" */
	{ 0x03C6, 0x4923 }, /* "phi" */
	{ 0x03C7, 0x27da }, /* "chi" */
	{ 0x03C8, 0x4b41 }, /* "psi" */
	{ 0x03C9, 0x479a }, /* "omega" */
	{ 0x03D1, 0x570e }, /* "thetav" */
	{ 0x03D2, 0x1d69 }, /* "Upsi" */
	{ 0x03D5, 0x492a }, /* "phiv" */
	{ 0x03D6, 0x495b }, /* "piv" */
	{ 0x03DC, 0x80d },  /* "Gammad" */
	{ 0x03DD, 0x31c5 }, /* "gammad" */
	{ 0x03F0, 0x3756 }, /* "kappav" */
	{ 0x03F1, 0x4e16 }, /* "rhov" */
	{ 0x03F5, 0x2f24 }, /* "epsiv" */
	{ 0x03F6, 0x229e }, /* "bepsi" */
	{ 0x0401, 0x98d },  /* "IOcy" */
	{ 0x0402, 0x31a },  /* "DJcy" */
	{ 0x0403, 0x7f6 },  /* "GJcy" */
	{ 0x0404, 0xaba },  /* "Jukcy" */
	{ 0x0405, 0x322 },  /* "DScy" */
	{ 0x0406, 0xa71 },  /* "Iukcy" */
	{ 0x0407, 0x1ec9 }, /* "YIcy" */
	{ 0x0408, 0xab0 },  /* "Jsercy" */
	{ 0x0409, 0xb0a },  /* "LJcy" */
	{ 0x040A, 0xefe },  /* "NJcy" */
	{ 0x040B, 0x1b07 }, /* "TSHcy" */
	{ 0x040C, 0xacb },  /* "KJcy" */
	{ 0x040E, 0x1c05 }, /* "Ubrcy" */
	{ 0x040F, 0x32a },  /* "DZcy" */
	{ 0x0410, 0x30 },   /* "Acy" */
	{ 0x0411, 0xdf },   /* "Bcy" */
	{ 0x0412, 0x1db5 }, /* "Vcy" */
	{ 0x0413, 0x834 },  /* "Gcy" */
	{ 0x0414, 0x35a },  /* "Dcy" */
	{ 0x0415, 0x97c },  /* "IEcy" */
	{ 0x0416, 0x1f19 }, /* "ZHcy" */
	{ 0x0417, 0x1f35 }, /* "Zcy" */
	{ 0x0418, 0x9aa },  /* "Icy" */
	{ 0x0419, 0xa8c },  /* "Jcy" */
	{ 0x041A, 0xae6 },  /* "Kcy" */
	{ 0x041B, 0xb61 },  /* "Lcy" */
	{ 0x041C, 0xea9 },  /* "Mcy" */
	{ 0x041D, 0xf24 },  /* "Ncy" */
	{ 0x041E, 0x1428 }, /* "Ocy" */
	{ 0x041F, 0x1526 }, /* "Pcy" */
	{ 0x0420, 0x1672 }, /* "Rcy" */
	{ 0x0421, 0x1923 }, /* "Scy" */
	{ 0x0422, 0x1b39 }, /* "Tcy" */
	{ 0x0423, 0x1c22 }, /* "Ucy" */
	{ 0x0424, 0x789 },  /* "Fcy" */
	{ 0x0425, 0xac3 },  /* "KHcy" */
	{ 0x0426, 0x1b10 }, /* "TScy" */
	{ 0x0427, 0x139 },  /* "CHcy" */
	{ 0x0428, 0x18e3 }, /* "SHcy" */
	{ 0x0429, 0x18d9 }, /* "SHCHcy" */
	{ 0x042A, 0x8f3 },  /* "HARDcy" */
	{ 0x042B, 0x1eed }, /* "Ycy" */
	{ 0x042C, 0x18eb }, /* "SOFTcy" */
	{ 0x042D, 0x69e },  /* "Ecy" */
	{ 0x042E, 0x1ed1 }, /* "YUcy" */
	{ 0x042F, 0x1ec1 }, /* "YAcy" */
	{ 0x0430, 0x1fba }, /* "acy" */
	{ 0x0431, 0x226a }, /* "bcy" */
	{ 0x0432, 0x5c20 }, /* "vcy" */
	{ 0x0433, 0x31ea }, /* "gcy" */
	{ 0x0434, 0x2b5c }, /* "dcy" */
	{ 0x0435, 0x3538 }, /* "iecy" */
	{ 0x0436, 0x5ee5 }, /* "zhcy" */
	{ 0x0437, 0x5eba }, /* "zcy" */
	{ 0x0438, 0x3531 }, /* "icy" */
	{ 0x0439, 0x370d }, /* "jcy" */
	{ 0x043A, 0x376a }, /* "kcy" */
	{ 0x043B, 0x3939 }, /* "lcy" */
	{ 0x043C, 0x3ec8 }, /* "mcy" */
	{ 0x043D, 0x410a }, /* "ncy" */
	{ 0x043E, 0x46d6 }, /* "ocy" */
	{ 0x043F, 0x48e1 }, /* "pcy" */
	{ 0x0440, 0x4d5a }, /* "rcy" */
	{ 0x0441, 0x50b6 }, /* "scy" */
	{ 0x0442, 0x56bc }, /* "tcy" */
	{ 0x0443, 0x595c }, /* "ucy" */
	{ 0x0444, 0x3039 }, /* "fcy" */
	{ 0x0445, 0x3784 }, /* "khcy" */
	{ 0x0446, 0x58c9 }, /* "tscy" */
	{ 0x0447, 0x27ba }, /* "chcy" */
	{ 0x0448, 0x5168 }, /* "shcy" */
	{ 0x0449, 0x515e }, /* "shchcy" */
	{ 0x044A, 0x3404 }, /* "hardcy" */
	{ 0x044B, 0x5e61 }, /* "ycy" */
	{ 0x044C, 0x5284 }, /* "softcy" */
	{ 0x044D, 0x2e09 }, /* "ecy" */
	{ 0x044E, 0x5e95 }, /* "yucy" */
	{ 0x044F, 0x5e50 }, /* "yacy" */
	{ 0x0451, 0x3661 }, /* "iocy" */
	{ 0x0452, 0x2c4b }, /* "djcy" */
	{ 0x0453, 0x3292 }, /* "gjcy" */
	{ 0x0454, 0x3744 }, /* "jukcy" */
	{ 0x0455, 0x2d4b }, /* "dscy" */
	{ 0x0456, 0x36f2 }, /* "iukcy" */
	{ 0x0457, 0x5e79 }, /* "yicy" */
	{ 0x0458, 0x373a }, /* "jsercy" */
	{ 0x0459, 0x3b5f }, /* "ljcy" */
	{ 0x045A, 0x422a }, /* "njcy" */
	{ 0x045B, 0x58d1 }, /* "tshcy" */
	{ 0x045C, 0x378c }, /* "kjcy" */
	{ 0x045E, 0x593f }, /* "ubrcy" */
	{ 0x045F, 0x2da3 }, /* "dzcy" */
	{ 0x2002, 0x2ed7 }, /* "ensp" */
	{ 0x2003, 0x2eb1 }, /* "emsp" */
	{ 0x2004, 0x2eba }, /* "emsp13" */
	{ 0x2005, 0x2ec5 }, /* "emsp14" */
	{ 0x2007, 0x45da }, /* "numsp" */
	{ 0x2008, 0x4b48 }, /* "puncsp" */
	{ 0x2009, 0x5735 }, /* "thinsp" */
	{ 0x200A, 0x33e6 }, /* "hairsp" */
	{ 0x200B, 0x1f44 }, /* "ZeroWidthSpace" */
	{ 0x200C, 0x5f15 }, /* "zwnj" */
	{ 0x200D, 0x5f0d }, /* "zwj" */
	{ 0x200E, 0x3d29 }, /* "lrm" */
	{ 0x200F, 0x4efc }, /* "rlm" */
	{ 0x2010, 0x2b2a }, /* "dash" */
	{ 0x2013, 0x4111 }, /* "ndash" */
	{ 0x2014, 0x3ecf }, /* "mdash" */
	{ 0x2015, 0x34d5 }, /* "horbar" */
	{ 0x2016, 0x1de4 }, /* "Vert" */
	{ 0x2018, 0x3d7c }, /* "lsquo" */
	{ 0x2019, 0x4fbe }, /* "rsquo" */
	{ 0x201A, 0x5030 }, /* "sbquo" */
	{ 0x201C, 0x3949 }, /* "ldquo" */
	{ 0x201D, 0x4d76 }, /* "rdquo" */
	{ 0x201E, 0x2271 }, /* "bdquo" */
	{ 0x2020, 0x2b0b }, /* "dagger" */
	{ 0x2021, 0x332 },  /* "Dagger" */
	{ 0x2022, 0x269c }, /* "bull" */
	{ 0x2025, 0x424e }, /* "nldr" */
	{ 0x2026, 0x3f62 }, /* "mldr" */
	{ 0x2030, 0x48fa }, /* "permil" */
	{ 0x2031, 0x490e }, /* "pertenk" */
	{ 0x2032, 0x4aab }, /* "prime" */
	{ 0x2033, 0x15ba }, /* "Prime" */
	{ 0x2034, 0x57e4 }, /* "tprime" */
	{ 0x2035, 0x2638 }, /* "bprime" */
	{ 0x2039, 0x3d3b }, /* "lsaquo" */
	{ 0x203A, 0x4f9a }, /* "rsaquo" */
	{ 0x203E, 0x477f }, /* "oline" */
	{ 0x2041, 0x272c }, /* "caret" */
	{ 0x2043, 0x34ff }, /* "hybull" */
	{ 0x2044, 0x3185 }, /* "frasl" */
	{ 0x204F, 0x2661 }, /* "bsemi" */
	{ 0x2057, 0x4b6f }, /* "qprime" */
	{ 0x205F, 0x1b60 }, /* "ThickSpace" */
	{ 0x2060, 0xfc9 },  /* "NoBreak" */
	{ 0x2061, 0x1fcb }, /* "af" */
	{ 0x2062, 0x36e1 }, /* "it" */
	{ 0x2063, 0x3520 }, /* "ic" */
	{ 0x20AC, 0x2fec }, /* "euro" */
	{ 0x20DB, 0x56c3 }, /* "tdot" */
	{ 0x20DC, 0x411 },  /* "DotDot" */
	{ 0x2102, 0x2a4 },  /* "Copf" */
	{ 0x2105, 0x35ef }, /* "incare" */
	{ 0x210A, 0x330e }, /* "gscr" */
	{ 0x210B, 0x94a },  /* "Hscr" */
	{ 0x210C, 0x915 },  /* "Hfr" */
	{ 0x210D, 0x92e },  /* "Hopf" */
	{ 0x210E, 0x496d }, /* "planckh" */
	{ 0x210F, 0x342d }, /* "hbar" */
	{ 0x2110, 0xa5e },  /* "Iscr" */
	{ 0x2111, 0x9cc },  /* "Im" */
	{ 0x2112, 0xe7f },  /* "Lscr" */
	{ 0x2113, 0x2e6b }, /* "ell" */
	{ 0x2115, 0xfe9 },  /* "Nopf" */
	{ 0x2116, 0x45cf }, /* "numero" */
	{ 0x2117, 0x2959 }, /* "copysr" */
	{ 0x2118, 0x5d37 }, /* "wp" */
	{ 0x2119, 0x1562 }, /* "Popf" */
	{ 0x211A, 0x1612 }, /* "Qopf" */
	{ 0x211B, 0x18b8 }, /* "Rscr" */
	{ 0x211C, 0x1679 }, /* "Re" */
	{ 0x211D, 0x188e }, /* "Ropf" */
	{ 0x211E, 0x501f }, /* "rx" */
	{ 0x2122, 0x1afd }, /* "TRADE" */
	{ 0x2124, 0x1f67 }, /* "Zopf" */
	{ 0x2127, 0x3ef4 }, /* "mho" */
	{ 0x2128, 0x1f5f }, /* "Zfr" */
	{ 0x2129, 0x358d }, /* "iiota" */
	{ 0x212C, 0x125 },  /* "Bscr" */
	{ 0x212D, 0x1cb },  /* "Cfr" */
	{ 0x212F, 0x2fb8 }, /* "escr" */
	{ 0x2130, 0x74b },  /* "Escr" */
	{ 0x2131, 0x7ed },  /* "Fscr" */
	{ 0x2133, 0xeef },  /* "Mscr" */
	{ 0x2134, 0x4852 }, /* "oscr" */
	{ 0x2135, 0x1ff2 }, /* "aleph" */
	{ 0x2136, 0x22ba }, /* "beth" */
	{ 0x2137, 0x3288 }, /* "gimel" */
	{ 0x2138, 0x2b16 }, /* "daleth" */
	{ 0x2145, 0x306 },  /* "DD" */
	{ 0x2146, 0x2b63 }, /* "dd" */
	{ 0x2147, 0x2e18 }, /* "ee" */
	{ 0x2148, 0x3566 }, /* "ii" */
	{ 0x2153, 0x30eb }, /* "frac13" */
	{ 0x2154, 0x3122 }, /* "frac23" */
	{ 0x2155, 0x3101 }, /* "frac15" */
	{ 0x2156, 0x312d }, /* "frac25" */
	{ 0x2157, 0x3143 }, /* "frac35" */
	{ 0x2158, 0x3159 }, /* "frac45" */
	{ 0x2159, 0x310c }, /* "frac16" */
	{ 0x215A, 0x3164 }, /* "frac56" */
	{ 0x215B, 0x3117 }, /* "frac18" */
	{ 0x215C, 0x314e }, /* "frac38" */
	{ 0x215D, 0x316f }, /* "frac58" */
	{ 0x215E, 0x317a }, /* "frac78" */
	{ 0x2190, 0x3844 }, /* "larr" */
	{ 0x2191, 0x5936 }, /* "uarr" */
	{ 0x2192, 0x4c49 }, /* "rarr" */
	{ 0x2193, 0x2b21 }, /* "darr" */
	{ 0x2194, 0x340e }, /* "harr" */
	{ 0x2195, 0x5b86 }, /* "varr" */
	{ 0x2196, 0x4687 }, /* "nwarr" */
	{ 0x2197, 0x4137 }, /* "nearr" */
	{ 0x2198, 0x50ef }, /* "searr" */
	{ 0x2199, 0x5662 }, /* "swarr" */
	{ 0x219A, 0x4244 }, /* "nlarr" */
	{ 0x219B, 0x43e0 }, /* "nrarr" */
	{ 0x219D, 0x4cc0 }, /* "rarrw" */
	{ 0x219E, 0xb44 },  /* "Larr" */
	{ 0x219F, 0x1bef }, /* "Uarr" */
	{ 0x21A0, 0x164a }, /* "Rarr" */
	{ 0x21A1, 0x33d },  /* "Darr" */
	{ 0x21A2, 0x389b }, /* "larrtl" */
	{ 0x21A3, 0x4cb5 }, /* "rarrtl" */
	{ 0x21A4, 0x3e96 }, /* "mapstoleft" */
	{ 0x21A5, 0x3ea5 }, /* "mapstoup" */
	{ 0x21A6, 0x3e74 }, /* "map" */
	{ 0x21A7, 0x3e87 }, /* "mapstodown" */
	{ 0x21A9, 0x386e }, /* "larrhk" */
	{ 0x21AA, 0x4c88 }, /* "rarrhk" */
	{ 0x21AB, 0x3879 }, /* "larrlp" */
	{ 0x21AC, 0x4c93 }, /* "rarrlp" */
	{ 0x21AD, 0x3423 }, /* "harrw" */
	{ 0x21AE, 0x41f6 }, /* "nharr" */
	{ 0x21B0, 0xe88 },  /* "Lsh" */
	{ 0x21B1, 0x18c1 }, /* "Rsh" */
	{ 0x21B2, 0x3977 }, /* "ldsh" */
	{ 0x21B3, 0x4d8b }, /* "rdsh" */
	{ 0x21B5, 0x2964 }, /* "crarr" */
	{ 0x21B6, 0x29de }, /* "cularr" */
	{ 0x21B7, 0x2a3e }, /* "curarr" */
	{ 0x21BA, 0x475f }, /* "olarr" */
	{ 0x21BB, 0x47f0 }, /* "orarr" */
	{ 0x21BC, 0x3b40 }, /* "lharu" */
	{ 0x21BD, 0x3b36 }, /* "lhard" */
	{ 0x21BE, 0x59aa }, /* "uharr" */
	{ 0x21BF, 0x59a0 }, /* "uharl" */
	{ 0x21C0, 0x4dfa }, /* "rharu" */
	{ 0x21C1, 0x4df0 }, /* "rhard" */
	{ 0x21C2, 0x2bc7 }, /* "dharr" */
	{ 0x21C3, 0x2bbd }, /* "dharl" */
	{ 0x21C4, 0x4ee8 }, /* "rlarr" */
	{ 0x21C5, 0x5963 }, /* "udarr" */
	{ 0x21C6, 0x3cfd }, /* "lrarr" */
	{ 0x21C7, 0x3b6e }, /* "llarr" */
	{ 0x21C8, 0x5aec }, /* "uuarr" */
	{ 0x21C9, 0x4f90 }, /* "rrarr" */
	{ 0x21CA, 0x2b76 }, /* "ddarr" */
	{ 0x21CB, 0x3d14 }, /* "lrhar" */
	{ 0x21CC, 0x4ef2 }, /* "rlhar" */
	{ 0x21CD, 0x4232 }, /* "nlArr" */
	{ 0x21CE, 0x41ec }, /* "nhArr" */
	{ 0x21CF, 0x43d6 }, /* "nrArr" */
	{ 0x21D0, 0x37b2 }, /* "lArr" */
	{ 0x21D1, 0x5919 }, /* "uArr" */
	{ 0x21D2, 0x4bc6 }, /* "rArr" */
	{ 0x21D3, 0x2af9 }, /* "dArr" */
	{ 0x21D4, 0x354a }, /* "iff" */
	{ 0x21D5, 0x5b0b }, /* "vArr" */
	{ 0x21D6, 0x4672 }, /* "nwArr" */
	{ 0x21D7, 0x4122 }, /* "neArr" */
	{ 0x21D8, 0x50da }, /* "seArr" */
	{ 0x21D9, 0x564d }, /* "swArr" */
	{ 0x21DA, 0x37a8 }, /* "lAarr" */
	{ 0x21DB, 0x4bbc }, /* "rAarr" */
	{ 0x21DD, 0x5eed }, /* "zigrarr" */
	{ 0x21E4, 0x384d }, /* "larrb" */
	{ 0x21E5, 0x4c5d }, /* "rarrb" */
	{ 0x21F5, 0x2d83 }, /* "duarr" */
	{ 0x21FD, 0x3c0b }, /* "loarr" */
	{ 0x21FE, 0x4f32 }, /* "roarr" */
	{ 0x21FF, 0x3491 }, /* "hoarr" */
	{ 0x2200, 0x7d3 },  /* "ForAll" */
	{ 0x2201, 0x28ea }, /* "comp" */
	{ 0x2202, 0x48d8 }, /* "part" */
	{ 0x2203, 0x2ffc }, /* "exist" */
	{ 0x2204, 0x4177 }, /* "nexist" */
	{ 0x2205, 0x2e8f }, /* "empty" */
	{ 0x2207, 0x361 },  /* "Del" */
	{ 0x2208, 0x35e8 }, /* "in" */
	{ 0x2209, 0x42f8 }, /* "notin" */
	{ 0x220B, 0x420a }, /* "ni" */
	{ 0x220C, 0x433e }, /* "notni" */
	{ 0x220F, 0x4ade }, /* "prod" */
	{ 0x2210, 0x2945 }, /* "coprod" */
	{ 0x2211, 0x1ab9 }, /* "Sum" */
	{ 0x2212, 0x3f2d }, /* "minus" */
	{ 0x2213, 0x3f8b }, /* "mp" */
	{ 0x2214, 0x49ae }, /* "plusdo" */
	{ 0x2216, 0x512d }, /* "setmn" */
	{ 0x2217, 0x3cba }, /* "lowast" */
	{ 0x2218, 0x28f3 }, /* "compfn" */
	{ 0x221A, 0x19a1 }, /* "Sqrt" */
	{ 0x221D, 0x4b0e }, /* "prop" */
	{ 0x221E, 0x35fa }, /* "infin" */
	{ 0x221F, 0x20df }, /* "angrt" */
	{ 0x2220, 0x2051 }, /* "ang" */
	{ 0x2221, 0x206c }, /* "angmsd" */
	{ 0x2222, 0x2102 }, /* "angsph" */
	{ 0x2223, 0x3f06 }, /* "mid" */
	{ 0x2224, 0x42dd }, /* "nmid" */
	{ 0x2225, 0x48a5 }, /* "par" */
	{ 0x2226, 0x436c }, /* "npar" */
	{ 0x2227, 0x201f }, /* "and" */
	{ 0x2228, 0x47e9 }, /* "or" */
	{ 0x2229, 0x26e2 }, /* "cap" */
	{ 0x222A, 0x29f5 }, /* "cup" */
	{ 0x222B, 0x361b }, /* "int" */
	{ 0x222C, 0x9f7 },  /* "Int" */
	{ 0x222D, 0x5795 }, /* "tint" */
	{ 0x222E, 0x4756 }, /* "oint" */
	{ 0x222F, 0x285 },  /* "Conint" */
	{ 0x2230, 0x19f },  /* "Cconint" */
	{ 0x2231, 0x2ae4 }, /* "cwint" */
	{ 0x2232, 0x2ad7 }, /* "cwconint" */
	{ 0x2233, 0x21c3 }, /* "awconint" */
	{ 0x2234, 0x56e0 }, /* "there4" */
	{ 0x2235, 0x227b }, /* "becaus" */
	{ 0x2236, 0x4cd5 }, /* "ratio" */
	{ 0x2237, 0x262 },  /* "Colon" */
	{ 0x2238, 0x3f42 }, /* "minusd" */
	{ 0x223A, 0x3e43 }, /* "mDDot" */
	{ 0x223B, 0x349b }, /* "homtht" */
	{ 0x223C, 0x51b4 }, /* "sim" */
	{ 0x223D, 0x266b }, /* "bsim" */
	{ 0x223E, 0x1f8f }, /* "ac" */
	{ 0x223F, 0x1f9e }, /* "acd" */
	{ 0x2240, 0x5d3e }, /* "wr" */
	{ 0x2241, 0x446c }, /* "nsim" */
	{ 0x2242, 0x2fcb }, /* "esim" */
	{ 0x2243, 0x51c7 }, /* "sime" */
	{ 0x2244, 0x4475 }, /* "nsime" */
	{ 0x2245, 0x291b }, /* "cong" */
	{ 0x2246, 0x5200 }, /* "simne" */
	{ 0x2247, 0x40ea }, /* "ncong" */
	{ 0x2248, 0x2135 }, /* "ap" */
	{ 0x2249, 0x405c }, /* "nap" */
	{ 0x224A, 0x214f }, /* "ape" */
	{ 0x224B, 0x2157 }, /* "apid" */
	{ 0x224C, 0x2260 }, /* "bcong" */
	{ 0x224D, 0x45fa }, /* "nvap" */
	{ 0x224E, 0x26b0 }, /* "bump" */
	{ 0x224F, 0x26c3 }, /* "bumpe" */
	{ 0x2250, 0x2c83 }, /* "doteq" */
	{ 0x2251, 0x2dc2 }, /* "eDot" */
	{ 0x2252, 0x2e1f }, /* "efDot" */
	{ 0x2253, 0x2fa4 }, /* "erDot" */
	{ 0x2254, 0x9e },   /* "Assign" */
	{ 0x2255, 0x2dfe }, /* "ecolon" */
	{ 0x2256, 0x2deb }, /* "ecir" */
	{ 0x2257, 0x2876 }, /* "cire" */
	{ 0x2259, 0x5d0e }, /* "wedgeq" */
	{ 0x225A, 0x5c44 }, /* "veeeq" */
	{ 0x225C, 0x587a }, /* "trie" */
	{ 0x225F, 0x2f76 }, /* "equest" */
	{ 0x2260, 0x411b }, /* "ne" */
	{ 0x2261, 0x2f81 }, /* "equiv" */
	{ 0x2262, 0x4157 }, /* "nequiv" */
	{ 0x2264, 0x3980 }, /* "le" */
	{ 0x2265, 0x31f9 }, /* "ge" */
	{ 0x2266, 0x37d0 }, /* "lE" */
	{ 0x2267, 0x31a3 }, /* "gE" */
	{ 0x2268, 0x3bbe }, /* "lnE" */
	{ 0x2269, 0x32b9 }, /* "gnE" */
	{ 0x226A, 0xe9a },  /* "Lt" */
	{ 0x226B, 0x8ec },  /* "Gt" */
	{ 0x226C, 0x58e4 }, /* "twixt" */
	{ 0x226D, 0x100b }, /* "NotCupCap" */
	{ 0x226E, 0x42c0 }, /* "nlt" */
	{ 0x226F, 0x41db }, /* "ngt" */
	{ 0x2270, 0x4257 }, /* "nle" */
	{ 0x2271, 0x419f }, /* "nge" */
	{ 0x2272, 0x3d58 }, /* "lsim" */
	{ 0x2273, 0x3317 }, /* "gsim" */
	{ 0x2274, 0x42b6 }, /* "nlsim" */
	{ 0x2275, 0x41d1 }, /* "ngsim" */
	{ 0x2276, 0x3b27 }, /* "lg" */
	{ 0x2277, 0x329a }, /* "gl" */
	{ 0x2278, 0x456c }, /* "ntlg" */
	{ 0x2279, 0x4558 }, /* "ntgl" */
	{ 0x227A, 0x4a18 }, /* "pr" */
	{ 0x227B, 0x503a }, /* "sc" */
	{ 0x227C, 0x4a30 }, /* "prcue" */
	{ 0x227D, 0x505c }, /* "sccue" */
	{ 0x227E, 0x4b22 }, /* "prsim" */
	{ 0x227F, 0x50ac }, /* "scsim" */
	{ 0x2280, 0x43a4 }, /* "npr" */
	{ 0x2281, 0x4425 }, /* "nsc" */
	{ 0x2282, 0x53fa }, /* "sub" */
	{ 0x2283, 0x5541 }, /* "sup" */
	{ 0x2284, 0x44b6 }, /* "nsub" */
	{ 0x2285, 0x4512 }, /* "nsup" */
	{ 0x2286, 0x5416 }, /* "sube" */
	{ 0x2287, 0x5584 }, /* "supe" */
	{ 0x2288, 0x44c9 }, /* "nsube" */
	{ 0x2289, 0x4525 }, /* "nsupe" */
	{ 0x228A, 0x5441 }, /* "subne" */
	{ 0x228B, 0x55d3 }, /* "supne" */
	{ 0x228D, 0x2a20 }, /* "cupdot" */
	{ 0x228E, 0x5a50 }, /* "uplus" */
	{ 0x228F, 0x52fe }, /* "sqsub" */
	{ 0x2290, 0x532f }, /* "sqsup" */
	{ 0x2291, 0x5308 }, /* "sqsube" */
	{ 0x2292, 0x5339 }, /* "sqsupe" */
	{ 0x2293, 0x52d4 }, /* "sqcap" */
	{ 0x2294, 0x52e9 }, /* "sqcup" */
	{ 0x2295, 0x47df }, /* "oplus" */
	{ 0x2296, 0x47b7 }, /* "ominus" */
	{ 0x2297, 0x487a }, /* "otimes" */
	{ 0x2298, 0x4866 }, /* "osol" */
	{ 0x2299, 0x46fa }, /* "odot" */
	{ 0x229A, 0x46c3 }, /* "ocir" */
	{ 0x229B, 0x46ba }, /* "oast" */
	{ 0x229D, 0x46dd }, /* "odash" */
	{ 0x229E, 0x4998 }, /* "plusb" */
	{ 0x229F, 0x3f37 }, /* "minusb" */
	{ 0x22A0, 0x5772 }, /* "timesb" */
	{ 0x22A1, 0x50c6 }, /* "sdotb" */
	{ 0x22A2, 0x5c27 }, /* "vdash" */
	{ 0x22A3, 0x2b33 }, /* "dashv" */
	{ 0x22A4, 0x57a7 }, /* "top" */
	{ 0x22A5, 0x245d }, /* "bot" */
	{ 0x22A7, 0x3f76 }, /* "models" */
	{ 0x22A8, 0x5b27 }, /* "vDash" */
	{ 0x22A9, 0x1dbc }, /* "Vdash" */
	{ 0x22AA, 0x1e63 }, /* "Vvdash" */
	{ 0x22AB, 0x1da2 }, /* "VDash" */
	{ 0x22AC, 0x4603 }, /* "nvdash" */
	{ 0x22AD, 0x45e4 }, /* "nvDash" */
	{ 0x22AE, 0x4034 }, /* "nVdash" */
	{ 0x22AF, 0x4029 }, /* "nVDash" */
	{ 0x22B0, 0x4b2c }, /* "prurel" */
	{ 0x22B2, 0x5c72 }, /* "vltri" */
	{ 0x22B3, 0x5ca4 }, /* "vrtri" */
	{ 0x22B4, 0x3dff }, /* "ltrie" */
	{ 0x22B5, 0x4ff2 }, /* "rtrie" */
	{ 0x22B6, 0x482a }, /* "origof" */
	{ 0x22B7, 0x35d6 }, /* "imof" */
	{ 0x22B8, 0x3fba }, /* "mumap" */
	{ 0x22B9, 0x3463 }, /* "hercon" */
	{ 0x22BA, 0x3623 }, /* "intcal" */
	{ 0x22BB, 0x5c39 }, /* "veebar" */
	{ 0x22BD, 0x2227 }, /* "barvee" */
	{ 0x22BE, 0x20e9 }, /* "angrtvb" */
	{ 0x22BF, 0x3d31 }, /* "lrtri" */
	{ 0x22C0, 0x1e77 }, /* "Wedge" */
	{ 0x22C1, 0x1dd1 }, /* "Vee" */
	{ 0x22C2, 0x5d5a }, /* "xcap" */
	{ 0x22C3, 0x5d6d }, /* "xcup" */
	{ 0x22C4, 0x2bd1 }, /* "diam" */
	{ 0x22C5, 0x50bd }, /* "sdot" */
	{ 0x22C6, 0x1a38 }, /* "Star" */
	{ 0x22C7, 0x2c40 }, /* "divonx" */
	{ 0x22C8, 0x2470 }, /* "bowtie" */
	{ 0x22C9, 0x3dc9 }, /* "ltimes" */
	{ 0x22CA, 0x4fde }, /* "rtimes" */
	{ 0x22CB, 0x3dbe }, /* "lthree" */
	{ 0x22CC, 0x4fd3 }, /* "rthree" */
	{ 0x22CD, 0x2674 }, /* "bsime" */
	{ 0x22CE, 0x2ac3 }, /* "cuvee" */
	{ 0x22CF, 0x2acd }, /* "cuwed" */
	{ 0x22D0, 0x1a41 }, /* "Sub" */
	{ 0x22D1, 0x1ac1 }, /* "Sup" */
	{ 0x22D2, 0x154 },  /* "Cap" */
	{ 0x22D3, 0x2f3 },  /* "Cup" */
	{ 0x22D4, 0x30c0 }, /* "fork" */
	{ 0x22D5, 0x2ef3 }, /* "epar" */
	{ 0x22D6, 0x3db4 }, /* "ltdot" */
	{ 0x22D7, 0x334d }, /* "gtdot" */
	{ 0x22D8, 0xdb6 },  /* "Ll" */
	{ 0x22D9, 0x84c },  /* "Gg" */
	{ 0x22DA, 0x3a48 }, /* "leg" */
	{ 0x22DB, 0x3200 }, /* "gel" */
	{ 0x22DE, 0x29ca }, /* "cuepr" */
	{ 0x22DF, 0x29d4 }, /* "cuesc" */
	{ 0x22E0, 0x43ac }, /* "nprcue" */
	{ 0x22E1, 0x442d }, /* "nsccue" */
	{ 0x22E2, 0x449e }, /* "nsqsube" */
	{ 0x22E3, 0x44aa }, /* "nsqsupe" */
	{ 0x22E6, 0x3bf7 }, /* "lnsim" */
	{ 0x22E7, 0x32f2 }, /* "gnsim" */
	{ 0x22E8, 0x4ad3 }, /* "prnsim" */
	{ 0x22E9, 0x5094 }, /* "scnsim" */
	{ 0x22EA, 0x42c8 }, /* "nltri" */
	{ 0x22EB, 0x4410 }, /* "nrtri" */
	{ 0x22EC, 0x42d2 }, /* "nltrie" */
	{ 0x22ED, 0x441a }, /* "nrtrie" */
	{ 0x22EE, 0x5c4e }, /* "vellip" */
	{ 0x22EF, 0x29a8 }, /* "ctdot" */
	{ 0x22F0, 0x5ac5 }, /* "utdot" */
	{ 0x22F1, 0x2d66 }, /* "dtdot" */
	{ 0x22F2, 0x2c12 }, /* "disin" */
	{ 0x22F3, 0x36cc }, /* "isinsv" */
	{ 0x22F4, 0x36c2 }, /* "isins" */
	{ 0x22F5, 0x36b6 }, /* "isindot" */
	{ 0x22F6, 0x4332 }, /* "notinvc" */
	{ 0x22F7, 0x4326 }, /* "notinvb" */
	{ 0x22F9, 0x36ac }, /* "isinE" */
	{ 0x22FA, 0x4219 }, /* "nisd" */
	{ 0x22FB, 0x5dc0 }, /* "xnis" */
	{ 0x22FC, 0x4211 }, /* "nis" */
	{ 0x22FD, 0x4360 }, /* "notnivc" */
	{ 0x22FE, 0x4354 }, /* "notnivb" */
	{ 0x2305, 0x2232 }, /* "barwed" */
	{ 0x2306, 0xd4 },   /* "Barwed" */
	{ 0x2308, 0x3928 }, /* "lceil" */
	{ 0x2309, 0x4d49 }, /* "rceil" */
	{ 0x230A, 0x3b13 }, /* "lfloor" */
	{ 0x230B, 0x4ddc }, /* "rfloor" */
	{ 0x230C, 0x2d36 }, /* "drcrop" */
	{ 0x230D, 0x2c5e }, /* "dlcrop" */
	{ 0x230E, 0x5a9d }, /* "urcrop" */
	{ 0x230F, 0x59d6 }, /* "ulcrop" */
	{ 0x2310, 0x244a }, /* "bnot" */
	{ 0x2312, 0x4af4 }, /* "profline" */
	{ 0x2313, 0x4b01 }, /* "profsurf" */
	{ 0x2315, 0x56cc }, /* "telrec" */
	{ 0x2316, 0x568d }, /* "target" */
	{ 0x231C, 0x59be }, /* "ulcorn" */
	{ 0x231D, 0x5a85 }, /* "urcorn" */
	{ 0x231E, 0x2c53 }, /* "dlcorn" */
	{ 0x231F, 0x2d2b }, /* "drcorn" */
	{ 0x2322, 0x318f }, /* "frown" */
	{ 0x2323, 0x525f }, /* "smile" */
	{ 0x232D, 0x2aee }, /* "cylcty" */
	{ 0x232E, 0x4ae7 }, /* "profalar" */
	{ 0x2336, 0x57af }, /* "topbot" */
	{ 0x233D, 0x489b }, /* "ovbar" */
	{ 0x233F, 0x529d }, /* "solbar" */
	{ 0x237C, 0x2116 }, /* "angzarr" */
	{ 0x23B0, 0x3ba4 }, /* "lmoust" */
	{ 0x23B1, 0x4f04 }, /* "rmoust" */
	{ 0x23B4, 0x569f }, /* "tbrk" */
	{ 0x23B5, 0x224a }, /* "bbrk" */
	{ 0x23B6, 0x2253 }, /* "bbrktbrk" */
	{ 0x23DC, 0x1505 }, /* "OverParenthesis" */
	{ 0x23DD, 0x1c7b }, /* "UnderParenthesis" */
	{ 0x23DE, 0x14e7 }, /* "OverBrace" */
	{ 0x23DF, 0x1c5b }, /* "UnderBrace" */
	{ 0x23E2, 0x58b2 }, /* "trpezium" */
	{ 0x23E7, 0x2e5e }, /* "elinters" */
	{ 0x2423, 0x2406 }, /* "blank" */
	{ 0x24C8, 0x46a8 }, /* "oS" */
	{ 0x2500, 0x2574 }, /* "boxh" */
	{ 0x2502, 0x25f3 }, /* "boxv" */
	{ 0x250C, 0x256a }, /* "boxdr" */
	{ 0x2510, 0x2560 }, /* "boxdl" */
	{ 0x2514, 0x25e9 }, /* "boxur" */
	{ 0x2518, 0x25df }, /* "boxul" */
	{ 0x251C, 0x262e }, /* "boxvr" */
	{ 0x2524, 0x2624 }, /* "boxvl" */
	{ 0x252C, 0x2591 }, /* "boxhd" */
	{ 0x2534, 0x259b }, /* "boxhu" */
	{ 0x253C, 0x261a }, /* "boxvh" */
	{ 0x2550, 0x24a3 }, /* "boxH" */
	{ 0x2551, 0x24fc }, /* "boxV" */
	{ 0x2552, 0x2556 }, /* "boxdR" */
	{ 0x2553, 0x2499 }, /* "boxDr" */
	{ 0x2554, 0x2485 }, /* "boxDR" */
	{ 0x2555, 0x254c }, /* "boxdL" */
	{ 0x2556, 0x248f }, /* "boxDl" */
	{ 0x2557, 0x247b }, /* "boxDL" */
	{ 0x2558, 0x25d5 }, /* "boxuR" */
	{ 0x2559, 0x24f2 }, /* "boxUr" */
	{ 0x255A, 0x24de }, /* "boxUR" */
	{ 0x255B, 0x25cb }, /* "boxuL" */
	{ 0x255C, 0x24e8 }, /* "boxUl" */
	{ 0x255D, 0x24d4 }, /* "boxUL" */
	{ 0x255E, 0x2610 }, /* "boxvR" */
	{ 0x255F, 0x2537 }, /* "boxVr" */
	{ 0x2560, 0x2519 }, /* "boxVR" */
	{ 0x2561, 0x2606 }, /* "boxvL" */
	{ 0x2562, 0x252d }, /* "boxVl" */
	{ 0x2563, 0x250f }, /* "boxVL" */
	{ 0x2564, 0x24c0 }, /* "boxHd" */
	{ 0x2565, 0x257d }, /* "boxhD" */
	{ 0x2566, 0x24ac }, /* "boxHD" */
	{ 0x2567, 0x24ca }, /* "boxHu" */
	{ 0x2568, 0x2587 }, /* "boxhU" */
	{ 0x2569, 0x24b6 }, /* "boxHU" */
	{ 0x256A, 0x25fc }, /* "boxvH" */
	{ 0x256B, 0x2523 }, /* "boxVh" */
	{ 0x256C, 0x2505 }, /* "boxVH" */
	{ 0x2580, 0x59b4 }, /* "uhblk" */
	{ 0x2584, 0x3b55 }, /* "lhblk" */
	{ 0x2588, 0x242e }, /* "block" */
	{ 0x2591, 0x241a }, /* "blk14" */
	{ 0x2592, 0x2410 }, /* "blk12" */
	{ 0x2593, 0x2424 }, /* "blk34" */
	{ 0x25A1, 0x5360 }, /* "squ" */
	{ 0x25AA, 0x537e }, /* "squf" */
	{ 0x25AB, 0x6eb },  /* "EmptyVerySmallSquare" */
	{ 0x25AD, 0x4dc0 }, /* "rect" */
	{ 0x25AE, 0x3eb2 }, /* "marker" */
	{ 0x25B1, 0x3099 }, /* "fltns" */
	{ 0x25B3, 0x5e27 }, /* "xutri" */
	{ 0x25B4, 0x5ae2 }, /* "utrif" */
	{ 0x25B5, 0x5ad9 }, /* "utri" */
	{ 0x25B8, 0x4ffc }, /* "rtrif" */
	{ 0x25B9, 0x4fe9 }, /* "rtri" */
	{ 0x25BD, 0x5d76 }, /* "xdtri" */
	{ 0x25BE, 0x2d79 }, /* "dtrif" */
	{ 0x25BF, 0x2d70 }, /* "dtri" */
	{ 0x25C2, 0x3e09 }, /* "ltrif" */
	{ 0x25C3, 0x3df6 }, /* "ltri" */
	{ 0x25CA, 0x3cce }, /* "loz" */
	{ 0x25CB, 0x27e1 }, /* "cir" */
	{ 0x25EC, 0x586f }, /* "tridot" */
	{ 0x25EF, 0x5d63 }, /* "xcirc" */
	{ 0x25F8, 0x59e1 }, /* "ultri" */
	{ 0x25F9, 0x5ab1 }, /* "urtri" */
	{ 0x25FA, 0x3b90 }, /* "lltri" */
	{ 0x25FB, 0x6d6 },  /* "EmptySmallSquare" */
	{ 0x25FC, 0x799 },  /* "FilledSmallSquare" */
	{ 0x2605, 0x53c5 }, /* "starf" */
	{ 0x2606, 0x53bc }, /* "star" */
	{ 0x260E, 0x493d }, /* "phone" */
	{ 0x2640, 0x3040 }, /* "female" */
	{ 0x2642, 0x3e56 }, /* "male" */
	{ 0x2660, 0x52b2 }, /* "spades" */
	{ 0x2663, 0x28a3 }, /* "clubs" */
	{ 0x2665, 0x343f }, /* "hearts" */
	{ 0x2666, 0x2bf6 }, /* "diams" */
	{ 0x266A, 0x5538 }, /* "sung" */
	{ 0x266D, 0x3086 }, /* "flat" */
	{ 0x266E, 0x408c }, /* "natur" */
	{ 0x266F, 0x5154 }, /* "sharp" */
	{ 0x2713, 0x27c2 }, /* "check" */
	{ 0x2717, 0x296e }, /* "cross" */
	{ 0x2720, 0x3e5f }, /* "malt" */
	{ 0x2736, 0x5137 }, /* "sext" */
	{ 0x2758, 0x1e0c }, /* "VerticalSeparator" */
	{ 0x2772, 0x38d6 }, /* "lbbrk" */
	{ 0x2773, 0x4cf7 }, /* "rbbrk" */
	{ 0x27C8, 0x268f }, /* "bsolhsub" */
	{ 0x27C9, 0x5599 }, /* "suphsol" */
	{ 0x27E6, 0x3c15 }, /* "lobrk" */
	{ 0x27E7, 0x4f3c }, /* "robrk" */
	{ 0x27E8, 0x3814 }, /* "lang" */
	{ 0x27E9, 0x4c17 }, /* "rang" */
	{ 0x27EA, 0xb2c },  /* "Lang" */
	{ 0x27EB, 0x1641 }, /* "Rang" */
	{ 0x27EC, 0x3c01 }, /* "loang" */
	{ 0x27ED, 0x4f28 }, /* "roang" */
	{ 0x27F5, 0x5dad }, /* "xlarr" */
	{ 0x27F6, 0x5dfd }, /* "xrarr" */
	{ 0x27F7, 0x5d93 }, /* "xharr" */
	{ 0x27F8, 0x5da3 }, /* "xlArr" */
	{ 0x27F9, 0x5df3 }, /* "xrArr" */
	{ 0x27FA, 0x5d89 }, /* "xhArr" */
	{ 0x27FC, 0x5db7 }, /* "xmap" */
	{ 0x27FF, 0x2dab }, /* "dzigrarr" */
	{ 0x2902, 0x462a }, /* "nvlArr" */
	{ 0x2903, 0x4651 }, /* "nvrArr" */
	{ 0x2904, 0x45ef }, /* "nvHarr" */
	{ 0x2905, 0xea1 },  /* "Map" */
	{ 0x290C, 0x38cc }, /* "lbarr" */
	{ 0x290D, 0x4ced }, /* "rbarr" */
	{ 0x290E, 0x37c6 }, /* "lBarr" */
	{ 0x290F, 0x4bda }, /* "rBarr" */
	{ 0x2910, 0x1625 }, /* "RBarr" */
	{ 0x2911, 0x30d },  /* "DDotrahd" */
	{ 0x2912, 0x1cc7 }, /* "UpArrowBar" */
	{ 0x2913, 0x565 },  /* "DownArrowBar" */
	{ 0x2916, 0x1653 }, /* "Rarrtl" */
	{ 0x2919, 0x38ae }, /* "latail" */
	{ 0x291A, 0x4cca }, /* "ratail" */
	{ 0x291B, 0x37bb }, /* "lAtail" */
	{ 0x291C, 0x4bcf }, /* "rAtail" */
	{ 0x291D, 0x3863 }, /* "larrfs" */
	{ 0x291E, 0x4c7d }, /* "rarrfs" */
	{ 0x291F, 0x3857 }, /* "larrbfs" */
	{ 0x2920, 0x4c67 }, /* "rarrbfs" */
	{ 0x2923, 0x467c }, /* "nwarhk" */
	{ 0x2924, 0x412c }, /* "nearhk" */
	{ 0x2925, 0x50e4 }, /* "searhk" */
	{ 0x2926, 0x5657 }, /* "swarhk" */
	{ 0x2927, 0x469d }, /* "nwnear" */
	{ 0x2928, 0x579e }, /* "toea" */
	{ 0x2929, 0x57db }, /* "tosa" */
	{ 0x292A, 0x5678 }, /* "swnwar" */
	{ 0x2933, 0x4c73 }, /* "rarrc" */
	{ 0x2935, 0x29be }, /* "cudarrr" */
	{ 0x2936, 0x3940 }, /* "ldca" */
	{ 0x2937, 0x4d61 }, /* "rdca" */
	{ 0x2938, 0x29b2 }, /* "cudarrl" */
	{ 0x2939, 0x3884 }, /* "larrpl" */
	{ 0x293C, 0x2a49 }, /* "curarrm" */
	{ 0x293D, 0x29e9 }, /* "cularrp" */
	{ 0x2945, 0x4c9e }, /* "rarrpl" */
	{ 0x2948, 0x3417 }, /* "harrcir" */
	{ 0x2949, 0x1bf8 }, /* "Uarrocir" */
	{ 0x294A, 0x3e13 }, /* "lurdshar" */
	{ 0x294B, 0x396a }, /* "ldrushar" */
	{ 0x294E, 0xc3a },  /* "LeftRightVector" */
	{ 0x294F, 0x180a }, /* "RightUpDownVector" */
	{ 0x2950, 0x598 },  /* "DownLeftRightVector" */
	{ 0x2951, 0xcb8 },  /* "LeftUpDownVector" */
	{ 0x2952, 0xd15 },  /* "LeftVectorBar" */
	{ 0x2953, 0x186c }, /* "RightVectorBar" */
	{ 0x2954, 0x1847 }, /* "RightUpVectorBar" */
	{ 0x2955, 0x1774 }, /* "RightDownVectorBar" */
	{ 0x2956, 0x5d9 },  /* "DownLeftVectorBar" */
	{ 0x2957, 0x61a },  /* "DownRightVectorBar" */
	{ 0x2958, 0xcf2 },  /* "LeftUpVectorBar" */
	{ 0x2959, 0xc03 },  /* "LeftDownVectorBar" */
	{ 0x295A, 0xc6b },  /* "LeftTeeVector" */
	{ 0x295B, 0x17b9 }, /* "RightTeeVector" */
	{ 0x295C, 0x1820 }, /* "RightUpTeeVector" */
	{ 0x295D, 0x1749 }, /* "RightDownTeeVector" */
	{ 0x295E, 0x5b0 },  /* "DownLeftTeeVector" */
	{ 0x295F, 0x5ef },  /* "DownRightTeeVector" */
	{ 0x2960, 0xccd },  /* "LeftUpTeeVector" */
	{ 0x2961, 0xbda },  /* "LeftDownTeeVector" */
	{ 0x2962, 0x37df }, /* "lHar" */
	{ 0x2963, 0x5922 }, /* "uHar" */
	{ 0x2964, 0x4be4 }, /* "rHar" */
	{ 0x2965, 0x2b02 }, /* "dHar" */
	{ 0x2966, 0x3e20 }, /* "luruhar" */
	{ 0x2967, 0x395e }, /* "ldrdhar" */
	{ 0x2968, 0x5013 }, /* "ruluhar" */
	{ 0x2969, 0x4d6a }, /* "rdldhar" */
	{ 0x296A, 0x3b4a }, /* "lharul" */
	{ 0x296B, 0x3b85 }, /* "llhard" */
	{ 0x296C, 0x4e04 }, /* "rharul" */
	{ 0x296D, 0x3d1e }, /* "lrhard" */
	{ 0x296E, 0x5977 }, /* "udhar" */
	{ 0x296F, 0x2d8d }, /* "duhar" */
	{ 0x2970, 0x1897 }, /* "RoundImplies" */
	{ 0x2971, 0x2fae }, /* "erarr" */
	{ 0x2972, 0x5216 }, /* "simrarr" */
	{ 0x2973, 0x388f }, /* "larrsim" */
	{ 0x2974, 0x4ca9 }, /* "rarrsim" */
	{ 0x2975, 0x4c52 }, /* "rarrap" */
	{ 0x2976, 0x3dd4 }, /* "ltlarr" */
	{ 0x2978, 0x337c }, /* "gtrarr" */
	{ 0x2979, 0x5457 }, /* "subrarr" */
	{ 0x297B, 0x55b1 }, /* "suplarr" */
	{ 0x297C, 0x3b08 }, /* "lfisht" */
	{ 0x297D, 0x4dd1 }, /* "rfisht" */
	{ 0x297E, 0x5981 }, /* "ufisht" */
	{ 0x297F, 0x2ba9 }, /* "dfisht" */
	{ 0x2985, 0x3c8f }, /* "lopar" */
	{ 0x2986, 0x4f46 }, /* "ropar" */
	{ 0x298B, 0x38f2 }, /* "lbrke" */
	{ 0x298C, 0x4d13 }, /* "rbrke" */
	{ 0x298D, 0x3908 }, /* "lbrkslu" */
	{ 0x298E, 0x4d1d }, /* "rbrksld" */
	{ 0x298F, 0x38fc }, /* "lbrksld" */
	{ 0x2990, 0x4d29 }, /* "rbrkslu" */
	{ 0x2991, 0x381d }, /* "langd" */
	{ 0x2992, 0x4c20 }, /* "rangd" */
	{ 0x2993, 0x3cf2 }, /* "lparlt" */
	{ 0x2994, 0x4f78 }, /* "rpargt" */
	{ 0x2995, 0x3357 }, /* "gtlPar" */
	{ 0x2996, 0x3deb }, /* "ltrPar" */
	{ 0x299A, 0x5ce4 }, /* "vzigzag" */
	{ 0x299C, 0x5b31 }, /* "vangrt" */
	{ 0x299D, 0x20f5 }, /* "angrtvbd" */
	{ 0x29A4, 0x2059 }, /* "ange" */
	{ 0x29A5, 0x4c2a }, /* "range" */
	{ 0x29A6, 0x2d97 }, /* "dwangle" */
	{ 0x29A7, 0x5aff }, /* "uwangle" */
	{ 0x29A8, 0x2077 }, /* "angmsdaa" */
	{ 0x29A9, 0x2084 }, /* "angmsdab" */
	{ 0x29AA, 0x2091 }, /* "angmsdac" */
	{ 0x29AB, 0x209e }, /* "angmsdad" */
	{ 0x29AC, 0x20ab }, /* "angmsdae" */
	{ 0x29AD, 0x20b8 }, /* "angmsdaf" */
	{ 0x29AE, 0x20c5 }, /* "angmsdag" */
	{ 0x29AF, 0x20d2 }, /* "angmsdah" */
	{ 0x29B0, 0x2292 }, /* "bemptyv" */
	{ 0x29B1, 0x2b9d }, /* "demptyv" */
	{ 0x29B2, 0x278f }, /* "cemptyv" */
	{ 0x29B3, 0x4c0a }, /* "raemptyv" */
	{ 0x29B4, 0x37f2 }, /* "laemptyv" */
	{ 0x29B5, 0x4745 }, /* "ohbar" */
	{ 0x29B6, 0x47ae }, /* "omid" */
	{ 0x29B7, 0x47cc }, /* "opar" */
	{ 0x29B9, 0x47d5 }, /* "operp" */
	{ 0x29BB, 0x4773 }, /* "olcross" */
	{ 0x29BC, 0x4703 }, /* "odsold" */
	{ 0x29BE, 0x4769 }, /* "olcir" */
	{ 0x29BF, 0x4717 }, /* "ofcir" */
	{ 0x29C0, 0x4789 }, /* "olt" */
	{ 0x29C1, 0x473d }, /* "ogt" */
	{ 0x29C2, 0x2897 }, /* "cirscir" */
	{ 0x29C3, 0x27e9 }, /* "cirE" */
	{ 0x29C4, 0x5294 }, /* "solb" */
	{ 0x29C5, 0x2685 }, /* "bsolb" */
	{ 0x29C9, 0x2541 }, /* "boxbox" */
	{ 0x29CD, 0x589c }, /* "trisb" */
	{ 0x29CE, 0x5006 }, /* "rtriltri" */
	{ 0x29CF, 0xc8e },  /* "LeftTriangleBar" */
	{ 0x29D0, 0x17de }, /* "RightTriangleBar" */
	{ 0x29DC, 0x3582 }, /* "iinfin" */
	{ 0x29DD, 0x3604 }, /* "infintie" */
	{ 0x29DE, 0x461e }, /* "nvinfin" */
	{ 0x29E3, 0x2efc }, /* "eparsl" */
	{ 0x29E4, 0x5249 }, /* "smeparsl" */
	{ 0x29E5, 0x2f97 }, /* "eqvparsl" */
	{ 0x29EB, 0x3ce2 }, /* "lozf" */
	{ 0x29F4, 0x18c9 }, /* "RuleDelayed" */
	{ 0x29F6, 0x2d53 }, /* "dsol" */
	{ 0x2A00, 0x5dc9 }, /* "xodot" */
	{ 0x2A01, 0x5ddd }, /* "xoplus" */
	{ 0x2A02, 0x5de8 }, /* "xotime" */
	{ 0x2A04, 0x5e1c }, /* "xuplus" */
	{ 0x2A06, 0x5e11 }, /* "xsqcup" */
	{ 0x2A0C, 0x4b5c }, /* "qint" */
	{ 0x2A0D, 0x30d3 }, /* "fpartint" */
	{ 0x2A10, 0x287f }, /* "cirfnint" */
	{ 0x2A11, 0x21d0 }, /* "awint" */
	{ 0x2A12, 0x4f83 }, /* "rppolint" */
	{ 0x2A13, 0x509f }, /* "scpolint" */
	{ 0x2A14, 0x4398 }, /* "npolint" */
	{ 0x2A15, 0x49f7 }, /* "pointint" */
	{ 0x2A16, 0x4b94 }, /* "quatint" */
	{ 0x2A17, 0x3648 }, /* "intlarhk" */
	{ 0x2A22, 0x49a2 }, /* "pluscir" */
	{ 0x2A23, 0x498b }, /* "plusacir" */
	{ 0x2A24, 0x520a }, /* "simplus" */
	{ 0x2A25, 0x49b9 }, /* "plusdu" */
	{ 0x2A26, 0x49d9 }, /* "plussim" */
	{ 0x2A27, 0x49e5 }, /* "plustwo" */
	{ 0x2A29, 0x3ebd }, /* "mcomma" */
	{ 0x2A2A, 0x3f4d }, /* "minusdu" */
	{ 0x2A2D, 0x3ca3 }, /* "loplus" */
	{ 0x2A2E, 0x4f5a }, /* "roplus" */
	{ 0x2A2F, 0x2df },  /* "Cross" */
	{ 0x2A30, 0x578a }, /* "timesd" */
	{ 0x2A31, 0x577d }, /* "timesbar" */
	{ 0x2A33, 0x523e }, /* "smashp" */
	{ 0x2A34, 0x3cae }, /* "lotimes" */
	{ 0x2A35, 0x4f65 }, /* "rotimes" */
	{ 0x2A36, 0x4885 }, /* "otimesas" */
	{ 0x2A37, 0x14c7 }, /* "Otimes" */
	{ 0x2A38, 0x46f1 }, /* "odiv" */
	{ 0x2A39, 0x5890 }, /* "triplus" */
	{ 0x2A3A, 0x5883 }, /* "triminus" */
	{ 0x2A3B, 0x58a6 }, /* "tritime" */
	{ 0x2A3C, 0x3684 }, /* "iprod" */
	{ 0x2A3F, 0x200e }, /* "amalg" */
	{ 0x2A40, 0x2718 }, /* "capdot" */
	{ 0x2A42, 0x4101 }, /* "ncup" */
	{ 0x2A43, 0x40cd }, /* "ncap" */
	{ 0x2A44, 0x26ea }, /* "capand" */
	{ 0x2A45, 0x2a2b }, /* "cupor" */
	{ 0x2A46, 0x2a0a }, /* "cupcap" */
	{ 0x2A47, 0x270d }, /* "capcup" */
	{ 0x2A48, 0x29fd }, /* "cupbrcap" */
	{ 0x2A49, 0x26f5 }, /* "capbrcup" */
	{ 0x2A4A, 0x2a15 }, /* "cupcup" */
	{ 0x2A4B, 0x2702 }, /* "capcap" */
	{ 0x2A4C, 0x2767 }, /* "ccups" */
	{ 0x2A4D, 0x273f }, /* "ccaps" */
	{ 0x2A50, 0x2771 }, /* "ccupssm" */
	{ 0x2A53, 0x5d },   /* "And" */
	{ 0x2A54, 0x14a0 }, /* "Or" */
	{ 0x2A55, 0x2027 }, /* "andand" */
	{ 0x2A56, 0x4835 }, /* "oror" */
	{ 0x2A57, 0x483e }, /* "orslope" */
	{ 0x2A58, 0x203b }, /* "andslope" */
	{ 0x2A5A, 0x2048 }, /* "andv" */
	{ 0x2A5B, 0x484a }, /* "orv" */
	{ 0x2A5C, 0x2032 }, /* "andd" */
	{ 0x2A5D, 0x47fa }, /* "ord" */
	{ 0x2A5F, 0x5cf9 }, /* "wedbar" */
	{ 0x2A66, 0x50d0 }, /* "sdote" */
	{ 0x2A6A, 0x51bc }, /* "simdot" */
	{ 0x2A6D, 0x2924 }, /* "congdot" */
	{ 0x2A6E, 0x2dd6 }, /* "easter" */
	{ 0x2A6F, 0x2144 }, /* "apacir" */
	{ 0x2A70, 0x213c }, /* "apE" */
	{ 0x2A71, 0x2f07 }, /* "eplus" */
	{ 0x2A72, 0x49c4 }, /* "pluse" */
	{ 0x2A73, 0x754 },  /* "Esim" */
	{ 0x2A74, 0x26c },  /* "Colone" */
	{ 0x2A75, 0x722 },  /* "Equal" */
	{ 0x2A77, 0x2db8 }, /* "eDDot" */
	{ 0x2A78, 0x2f8b }, /* "equivDD" */
	{ 0x2A79, 0x3daa }, /* "ltcir" */
	{ 0x2A7A, 0x3343 }, /* "gtcir" */
	{ 0x2A7B, 0x3ddf }, /* "ltquest" */
	{ 0x2A7C, 0x3362 }, /* "gtquest" */
	{ 0x2A7D, 0x3a6e }, /* "les" */
	{ 0x2A7E, 0x3226 }, /* "ges" */
	{ 0x2A7F, 0x3a80 }, /* "lesdot" */
	{ 0x2A80, 0x3238 }, /* "gesdot" */
	{ 0x2A81, 0x3a8b }, /* "lesdoto" */
	{ 0x2A82, 0x3243 }, /* "gesdoto" */
	{ 0x2A83, 0x3a97 }, /* "lesdotor" */
	{ 0x2A84, 0x324f }, /* "gesdotol" */
	{ 0x2A85, 0x3832 }, /* "lap" */
	{ 0x2A86, 0x31cf }, /* "gap" */
	{ 0x2A87, 0x3bdc }, /* "lne" */
	{ 0x2A88, 0x32d7 }, /* "gne" */
	{ 0x2A89, 0x3bc6 }, /* "lnap" */
	{ 0x2A8A, 0x32c1 }, /* "gnap" */
	{ 0x2A8B, 0x37d7 }, /* "lEg" */
	{ 0x2A8C, 0x31aa }, /* "gEl" */
	{ 0x2A8D, 0x3d61 }, /* "lsime" */
	{ 0x2A8E, 0x3320 }, /* "gsime" */
	{ 0x2A8F, 0x3d6b }, /* "lsimg" */
	{ 0x2A90, 0x332a }, /* "gsiml" */
	{ 0x2A91, 0x3b2e }, /* "lgE" */
	{ 0x2A92, 0x32a1 }, /* "glE" */
	{ 0x2A93, 0x3aad }, /* "lesges" */
	{ 0x2A94, 0x3265 }, /* "gesles" */
	{ 0x2A95, 0x2e73 }, /* "els" */
	{ 0x2A96, 0x2e44 }, /* "egs" */
	{ 0x2A97, 0x2e7b }, /* "elsdot" */
	{ 0x2A98, 0x2e4c }, /* "egsdot" */
	{ 0x2A99, 0x2e57 }, /* "el" */
	{ 0x2A9A, 0x2e32 }, /* "eg" */
	{ 0x2A9D, 0x51ed }, /* "siml" */
	{ 0x2A9E, 0x51da }, /* "simg" */
	{ 0x2A9F, 0x51f6 }, /* "simlE" */
	{ 0x2AA0, 0x51e3 }, /* "simgE" */
	{ 0x2AA1, 0xd7f },  /* "LessLess" */
	{ 0x2AA2, 0x898 },  /* "GreaterGreater" */
	{ 0x2AA4, 0x32b1 }, /* "glj" */
	{ 0x2AA5, 0x32a9 }, /* "gla" */
	{ 0x2AA6, 0x3da1 }, /* "ltcc" */
	{ 0x2AA7, 0x333a }, /* "gtcc" */
	{ 0x2AA8, 0x3a76 }, /* "lescc" */
	{ 0x2AA9, 0x322e }, /* "gescc" */
	{ 0x2AAA, 0x5269 }, /* "smt" */
	{ 0x2AAB, 0x38a6 }, /* "lat" */
	{ 0x2AAC, 0x5271 }, /* "smte" */
	{ 0x2AAD, 0x38b9 }, /* "late" */
	{ 0x2AAE, 0x26b9 }, /* "bumpE" */
	{ 0x2AAF, 0x4a3a }, /* "pre" */
	{ 0x2AB0, 0x5066 }, /* "sce" */
	{ 0x2AB3, 0x4a1f }, /* "prE" */
	{ 0x2AB4, 0x5041 }, /* "scE" */
	{ 0x2AB5, 0x4ac0 }, /* "prnE" */
	{ 0x2AB6, 0x5081 }, /* "scnE" */
	{ 0x2AB7, 0x4a27 }, /* "prap" */
	{ 0x2AB8, 0x5049 }, /* "scap" */
	{ 0x2AB9, 0x4ac9 }, /* "prnap" */
	{ 0x2ABA, 0x508a }, /* "scnap" */
	{ 0x2ABB, 0x156b }, /* "Pr" */
	{ 0x2ABC, 0x18ff }, /* "Sc" */
	{ 0x2ABD, 0x540b }, /* "subdot" */
	{ 0x2ABE, 0x556d }, /* "supdot" */
	{ 0x2ABF, 0x544b }, /* "subplus" */
	{ 0x2AC0, 0x55dd }, /* "supplus" */
	{ 0x2AC1, 0x542b }, /* "submult" */
	{ 0x2AC2, 0x55bd }, /* "supmult" */
	{ 0x2AC3, 0x541f }, /* "subedot" */
	{ 0x2AC4, 0x558d }, /* "supedot" */
	{ 0x2AC5, 0x5402 }, /* "subE" */
	{ 0x2AC6, 0x5564 }, /* "supE" */
	{ 0x2AC7, 0x54a6 }, /* "subsim" */
	{ 0x2AC8, 0x562c }, /* "supsim" */
	{ 0x2ACB, 0x5437 }, /* "subnE" */
	{ 0x2ACC, 0x55c9 }, /* "supnE" */
	{ 0x2ACF, 0x2982 }, /* "csub" */
	{ 0x2AD0, 0x2995 }, /* "csup" */
	{ 0x2AD1, 0x298b }, /* "csube" */
	{ 0x2AD2, 0x299e }, /* "csupe" */
	{ 0x2AD3, 0x54bc }, /* "subsup" */
	{ 0x2AD4, 0x5637 }, /* "supsub" */
	{ 0x2AD5, 0x54b1 }, /* "subsub" */
	{ 0x2AD6, 0x5642 }, /* "supsup" */
	{ 0x2AD7, 0x55a5 }, /* "suphsub" */
	{ 0x2AD8, 0x5578 }, /* "supdsub" */
	{ 0x2AD9, 0x30c9 }, /* "forkv" */
	{ 0x2ADA, 0x57cf }, /* "topfork" */
	{ 0x2ADB, 0x3f59 }, /* "mlcp" */
	{ 0x2AE4, 0x346 },  /* "Dashv" */
	{ 0x2AE6, 0x1dc6 }, /* "Vdashl" */
	{ 0x2AE7, 0xcb },   /* "Barv" */
	{ 0x2AE8, 0x5b14 }, /* "vBar" */
	{ 0x2AE9, 0x5b1d }, /* "vBarv" */
	{ 0x2AEB, 0x1dac }, /* "Vbar" */
	{ 0x2AEC, 0xff2 },  /* "Not" */
	{ 0x2AED, 0x21da }, /* "bNot" */
	{ 0x2AEE, 0x4f1e }, /* "rnmid" */
	{ 0x2AEF, 0x288c }, /* "cirmid" */
	{ 0x2AF0, 0x3f17 }, /* "midcir" */
	{ 0x2AF1, 0x57ba }, /* "topcir" */
	{ 0x2AF2, 0x4200 }, /* "nhpar" */
	{ 0x2AF3, 0x48c3 }, /* "parsim" */
	{ 0x2AFD, 0x48ce }, /* "parsl" */
	{ 0xFB00, 0x3056 }, /* "fflig" */
	{ 0xFB01, 0x3074 }, /* "filig" */
	{ 0xFB02, 0x308f }, /* "fllig" */
	{ 0xFB03, 0x304b }, /* "ffilig" */
	{ 0xFB04, 0x3060 }, /* "ffllig" */
};
PRIVATE struct xml_encode32_entry const xml_encode32_db[133] = {
	{ 0x1D49C, 0x94 },   /* "Ascr" */
	{ 0x1D49E, 0x2e9 },  /* "Cscr" */
	{ 0x1D49F, 0x65c },  /* "Dscr" */
	{ 0x1D4A2, 0x8e2 },  /* "Gscr" */
	{ 0x1D4A5, 0xaa6 },  /* "Jscr" */
	{ 0x1D4A6, 0xb00 },  /* "Kscr" */
	{ 0x1D4A9, 0x13ef }, /* "Nscr" */
	{ 0x1D4AA, 0x14a7 }, /* "Oscr" */
	{ 0x1D4AB, 0x15f0 }, /* "Pscr" */
	{ 0x1D4AC, 0x161b }, /* "Qscr" */
	{ 0x1D4AE, 0x1a2e }, /* "Sscr" */
	{ 0x1D4AF, 0x1bd0 }, /* "Tscr" */
	{ 0x1D4B0, 0x1d85 }, /* "Uscr" */
	{ 0x1D4B1, 0x1e59 }, /* "Vscr" */
	{ 0x1D4B2, 0x1e94 }, /* "Wscr" */
	{ 0x1D4B3, 0x1eb7 }, /* "Xscr" */
	{ 0x1D4B4, 0x1f07 }, /* "Yscr" */
	{ 0x1D4B5, 0x1f70 }, /* "Zscr" */
	{ 0x1D4B6, 0x2189 }, /* "ascr" */
	{ 0x1D4B7, 0x2657 }, /* "bscr" */
	{ 0x1D4B8, 0x2978 }, /* "cscr" */
	{ 0x1D4B9, 0x2d41 }, /* "dscr" */
	{ 0x1D4BB, 0x3199 }, /* "fscr" */
	{ 0x1D4BD, 0x34e0 }, /* "hscr" */
	{ 0x1D4BE, 0x3699 }, /* "iscr" */
	{ 0x1D4BF, 0x3730 }, /* "jscr" */
	{ 0x1D4C0, 0x379e }, /* "kscr" */
	{ 0x1D4C1, 0x3d46 }, /* "lscr" */
	{ 0x1D4C2, 0x3f92 }, /* "mscr" */
	{ 0x1D4C3, 0x4441 }, /* "nscr" */
	{ 0x1D4C5, 0x4b37 }, /* "pscr" */
	{ 0x1D4C6, 0x4b7a }, /* "qscr" */
	{ 0x1D4C7, 0x4fa5 }, /* "rscr" */
	{ 0x1D4C8, 0x5391 }, /* "sscr" */
	{ 0x1D4C9, 0x58bf }, /* "tscr" */
	{ 0x1D4CA, 0x5abb }, /* "uscr" */
	{ 0x1D4CB, 0x5cae }, /* "vscr" */
	{ 0x1D4CC, 0x5d50 }, /* "wscr" */
	{ 0x1D4CD, 0x5e07 }, /* "xscr" */
	{ 0x1D4CE, 0x5e8b }, /* "yscr" */
	{ 0x1D4CF, 0x5f03 }, /* "zscr" */
	{ 0x1D504, 0x37 },   /* "Afr" */
	{ 0x1D505, 0x109 },  /* "Bfr" */
	{ 0x1D507, 0x372 },  /* "Dfr" */
	{ 0x1D508, 0x6ad },  /* "Efr" */
	{ 0x1D509, 0x790 },  /* "Ffr" */
	{ 0x1D50A, 0x843 },  /* "Gfr" */
	{ 0x1D50D, 0xa93 },  /* "Jfr" */
	{ 0x1D50E, 0xaed },  /* "Kfr" */
	{ 0x1D50F, 0xdad },  /* "Lfr" */
	{ 0x1D510, 0xece },  /* "Mfr" */
	{ 0x1D511, 0xfc0 },  /* "Nfr" */
	{ 0x1D512, 0x1439 }, /* "Ofr" */
	{ 0x1D513, 0x152d }, /* "Pfr" */
	{ 0x1D514, 0x1609 }, /* "Qfr" */
	{ 0x1D516, 0x192a }, /* "Sfr" */
	{ 0x1D517, 0x1b40 }, /* "Tfr" */
	{ 0x1D518, 0x1c33 }, /* "Ufr" */
	{ 0x1D519, 0x1e46 }, /* "Vfr" */
	{ 0x1D51A, 0x1e81 }, /* "Wfr" */
	{ 0x1D51B, 0x1e9e }, /* "Xfr" */
	{ 0x1D51C, 0x1ef4 }, /* "Yfr" */
	{ 0x1D51E, 0x1fd2 }, /* "afr" */
	{ 0x1D51F, 0x22cf }, /* "bfr" */
	{ 0x1D520, 0x27b1 }, /* "cfr" */
	{ 0x1D521, 0x2bb4 }, /* "dfr" */
	{ 0x1D522, 0x2e29 }, /* "efr" */
	{ 0x1D523, 0x306b }, /* "ffr" */
	{ 0x1D524, 0x3270 }, /* "gfr" */
	{ 0x1D525, 0x346e }, /* "hfr" */
	{ 0x1D526, 0x3552 }, /* "ifr" */
	{ 0x1D527, 0x3714 }, /* "jfr" */
	{ 0x1D528, 0x3771 }, /* "kfr" */
	{ 0x1D529, 0x3b1e }, /* "lfr" */
	{ 0x1D52A, 0x3eeb }, /* "mfr" */
	{ 0x1D52B, 0x418e }, /* "nfr" */
	{ 0x1D52C, 0x4721 }, /* "ofr" */
	{ 0x1D52D, 0x491a }, /* "pfr" */
	{ 0x1D52E, 0x4b53 }, /* "qfr" */
	{ 0x1D52F, 0x4de7 }, /* "rfr" */
	{ 0x1D530, 0x5140 }, /* "sfr" */
	{ 0x1D531, 0x56d7 }, /* "tfr" */
	{ 0x1D532, 0x598c }, /* "ufr" */
	{ 0x1D533, 0x5c69 }, /* "vfr" */
	{ 0x1D534, 0x5d24 }, /* "wfr" */
	{ 0x1D535, 0x5d80 }, /* "xfr" */
	{ 0x1D536, 0x5e70 }, /* "yfr" */
	{ 0x1D537, 0x5edc }, /* "zfr" */
	{ 0x1D538, 0x6e },   /* "Aopf" */
	{ 0x1D539, 0x112 },  /* "Bopf" */
	{ 0x1D53B, 0x400 },  /* "Dopf" */
	{ 0x1D53C, 0x70d },  /* "Eopf" */
	{ 0x1D53D, 0x7c9 },  /* "Fopf" */
	{ 0x1D53E, 0x853 },  /* "Gopf" */
	{ 0x1D540, 0xa4c },  /* "Iopf" */
	{ 0x1D541, 0xa9c },  /* "Jopf" */
	{ 0x1D542, 0xaf6 },  /* "Kopf" */
	{ 0x1D543, 0xe4e },  /* "Lopf" */
	{ 0x1D544, 0xee5 },  /* "Mopf" */
	{ 0x1D546, 0x146a }, /* "Oopf" */
	{ 0x1D54A, 0x1997 }, /* "Sopf" */
	{ 0x1D54B, 0x1bb8 }, /* "Topf" */
	{ 0x1D54C, 0x1cb1 }, /* "Uopf" */
	{ 0x1D54D, 0x1e4f }, /* "Vopf" */
	{ 0x1D54E, 0x1e8a }, /* "Wopf" */
	{ 0x1D54F, 0x1ead }, /* "Xopf" */
	{ 0x1D550, 0x1efd }, /* "Yopf" */
	{ 0x1D552, 0x212b }, /* "aopf" */
	{ 0x1D553, 0x2453 }, /* "bopf" */
	{ 0x1D554, 0x293b }, /* "copf" */
	{ 0x1D555, 0x2c72 }, /* "dopf" */
	{ 0x1D556, 0x2ee9 }, /* "eopf" */
	{ 0x1D557, 0x30ab }, /* "fopf" */
	{ 0x1D558, 0x32fc }, /* "gopf" */
	{ 0x1D559, 0x34cb }, /* "hopf" */
	{ 0x1D55A, 0x3672 }, /* "iopf" */
	{ 0x1D55B, 0x3726 }, /* "jopf" */
	{ 0x1D55C, 0x3794 }, /* "kopf" */
	{ 0x1D55D, 0x3c99 }, /* "lopf" */
	{ 0x1D55E, 0x3f81 }, /* "mopf" */
	{ 0x1D55F, 0x42e6 }, /* "nopf" */
	{ 0x1D560, 0x47c2 }, /* "oopf" */
	{ 0x1D561, 0x4a04 }, /* "popf" */
	{ 0x1D562, 0x4b65 }, /* "qopf" */
	{ 0x1D563, 0x4f50 }, /* "ropf" */
	{ 0x1D564, 0x52a8 }, /* "sopf" */
	{ 0x1D565, 0x57c5 }, /* "topf" */
	{ 0x1D566, 0x5a05 }, /* "uopf" */
	{ 0x1D567, 0x5c90 }, /* "vopf" */
	{ 0x1D568, 0x5d2d }, /* "wopf" */
	{ 0x1D569, 0x5dd3 }, /* "xopf" */
	{ 0x1D56A, 0x5e81 }, /* "yopf" */
	{ 0x1D56B, 0x5ef9 }, /* "zopf" */
};
#endif /* CONFIG_XML_FANCY_ENCODE */
/*[[[end]]]*/


/* Helpers for working XML Entity database entries. */
typedef char xml_entity_t;
#define xml_entity_semiopt(self) ((self)[-1] == 1)  /* non-zero iff the trailing ';' is optional */
#define xml_entity_name(self)    (self)             /* String that must appear in '&<str>;' */
#define xml_entity_utf8(self)    (strend(self) + 1) /* utf-8 sequence used for replacement. */


/* Find the start of the given entry. */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) xml_entity_t const *
NOTHROW_NCX(CC xml_entity_fromptr)(char const *__restrict ptr) {
	char const *iter;
	iter = strend(ptr) + 1;
	unicode_readutf8(&iter);
	if (*iter == '\0') {
		/* `ptr' points into the first string! */
		if (*ptr == 0x01)
			return ptr + 1;
		while ((unsigned char)ptr[-1] >= 0x02)
			--ptr;
		return ptr;
	}
	/* `ptr' points into the second string! */
	while (ptr[-1] != '\0')
		--ptr;
	/* `ptr' now points at the start of the second string. */
	--ptr;
	/* `ptr' now points at the nul after the first string. */
	while ((unsigned char)ptr[-1] >= 0x02)
		--ptr;
	/* `ptr' now points at the start of the first string. */
	return ptr;
}


/* Lookup an XML entity from the database, given its name as it  would
 * appear within escaped text. If  not found, return NULL.  Otherwise,
 * return a pointer to the database entry which is associated with the
 * given name.
 * Upon success, you may use the `xml_entity_*' functions to
 * interact with the database entry. */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) xml_entity_t const *
NOTHROW_NCX(CC xml_entity_lookup)(char const *__restrict name, size_t namelen) {
	size_t lo, hi;
	lo = 1;
	hi = sizeof(xml_entity_db) - 5;
	while (lo < hi) {
		xml_entity_t const *entry;
		size_t i = (lo + hi) / 2;
		int cmp;
		entry = xml_entity_fromptr(xml_entity_db + i);
		cmp   = strcmpz(entry, name, namelen);
		if (cmp > 0) {
			hi = i;
		} else if (cmp < 0) {
			lo = i + 1;
		} else {
			/* Found it! */
			return entry;
		}
	}
	return NULL;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) xml_entity_t const *
NOTHROW_NCX(CC xml_entity_lookup_startswith)(char const *__restrict name, size_t namelen) {
	size_t lo, hi;
	lo = 1;
	hi = sizeof(xml_entity_db) - 5;
	while (lo < hi) {
		xml_entity_t const *entry;
		size_t i = (lo + hi) / 2;
		int cmp;
		entry = xml_entity_fromptr(xml_entity_db + i);
		cmp   = memcmp(entry, name, namelen * sizeof(char));
		if (cmp > 0) {
			hi = i;
		} else if (cmp < 0) {
			lo = i + 1;
		} else {
			/* Found it! */
			return entry;
		}
	}
	return NULL;
}

PRIVATE ATTR_NOINLINE ATTR_PURE WUNUSED NONNULL((1)) xml_entity_t const *
NOTHROW_NCX(CC xml_entity_lookup_startswith_plus1)(char const *__restrict name,
                                                   size_t namelen, char next_ch) {
	char *buf;
	buf = (char *)alloca((namelen + 1) * sizeof(char));
	*(char *)mempcpy(buf, name, namelen, sizeof(char)) = next_ch;
	return xml_entity_lookup_startswith(buf, namelen + 1);
}


#ifdef CONFIG_XML_FANCY_ENCODE
PRIVATE ATTR_CONST WUNUSED xml_entity_t const *
NOTHROW_NCX(CC xml_entity_bychr16)(char16_t ch) {
	size_t lo, hi;
	lo = 0;
	hi = COMPILER_LENOF(xml_encode16_db);
	while (lo < hi) {
		size_t i;
		char16_t ord;
		i   = (lo + hi) / 2;
		ord = xml_encode16_db[i].xe16_chr;
		if (ch < ord) {
			hi = i;
		} else if (ch > ord) {
			lo = i + 1;
		} else {
			/* Found it! */
			return xml_entity_db + xml_encode16_db[i].xe16_offset;
		}
	}
	return NULL;
}

PRIVATE ATTR_CONST WUNUSED xml_entity_t const *
NOTHROW_NCX(CC xml_entity_bychr32)(char32_t ch) {
	size_t lo, hi;
	lo = 0;
	hi = COMPILER_LENOF(xml_encode32_db);
	while (lo < hi) {
		size_t i;
		char32_t ord;
		i   = (lo + hi) / 2;
		ord = xml_encode32_db[i].xe32_chr;
		if (ch < ord) {
			hi = i;
		} else if (ch > ord) {
			lo = i + 1;
		} else {
			/* Found it! */
			return xml_entity_db + xml_encode32_db[i].xe32_offset;
		}
	}
	return NULL;
}
#endif /* CONFIG_XML_FANCY_ENCODE */



/* Escape the given `ch' in XML */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) char const *
NOTHROW_NCX(CC xml_escape)(char *__restrict buf, char32_t ch) {
	/* Check for special case: don't need to escape! */
	if (ch >= 0x20 && ch <= 0x7e &&
	    ch != '<' && ch != '>' && ch != '&' &&
	    ch != '\'' && ch != '\"') {
		buf[0] = (char)(unsigned char)ch;
		buf[1] = '\0';
		return buf;
	}

#ifdef CONFIG_XML_FANCY_ENCODE
	/* If we have fancy encode escapes, then use actual strings! */
	{
		xml_entity_t const *ent;
		ent = ch > 0xffff ? xml_entity_bychr32(ch)
		                  : xml_entity_bychr16(ch);
		if (ent != NULL)
			return xml_entity_name(ent);
	}
#endif /* CONFIG_XML_FANCY_ENCODE */

	/* Manually escape as either decimal or hex. */
	if (ch <= 9 || (ch >= 16 && ch <= 99) || (ch >= 256 && ch <= 999) ||
		(ch >= 4096 && ch <= 9999) || (ch >= 65536 && ch <= 99999)) {
		/* For all these ordinals, using decimal encoding is smaller:
		 *  0...9         -->  &#0;  ... &#9;
		 *                     &#x0; ... &#x9;
		 *
		 *  16...99       -->  &#16;  ...  &#99;
		 *                     &#x10; ...  &#x63;
		 *
		 *  256...999     -->  &#256;  ...  &#999;
		 *                     &#x100; ...  &#x3E7;
		 *
		 *  4096...9999   -->  &#4096;  ...  &#9999;
		 *                     &#x1000; ...  &#x270F;
		 *
		 *  65536...99999 -->  &#65536;  ...  &#99999;
		 *                     &#x10000; ...  &#x1869F;
		 *
		 * For everything larger in this sequence, hex is always
		 * more compact, even when accounting for the additional
		 * leading "x" which it requires! */
		sprintf(buf, "#%u", (unsigned int)ch);
	} else {
		/* For everything else, hex is just as long, or even shorter.
		 * Because hex is easier to read we use it unless decimal  is
		 * more efficient. */
		sprintf(buf, "#x%" PRIX32, (uint32_t)ch);
	}
	return buf;
}



INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_xml_escape_encode(struct iconv_encode *__restrict self,
                           /*utf-8*/ char const *__restrict data, size_t size) {
	char esc_buf[COMPILER_STRLEN("#xFFFFFFFF\0")];
	char const *esc;
	ssize_t temp, result = 0;
	char const *end, *flush_start;
	flush_start = data;
	end         = data + size;
	if unlikely(self->ice_flags & ICONV_HASERR)
		goto err_ilseq;
	if (!mbstate_isempty(&self->ice_data.ied_utf8))
		goto parse_unicode;
	while (data < end) {
		unsigned char ch;
		ch = (unsigned char)*data;
		if (ch >= 0x80) {
			char32_t ch32;
			size_t status;
			DO_encode_output(flush_start, (size_t)(data - flush_start));
parse_unicode:
			status = unicode_c8toc32(&ch32, data, (size_t)(end - data),
			                         &self->ice_data.ied_utf8);
			if ((ssize_t)status < 0) {
				if (status == (size_t)-1) {
					ch = (unsigned char)*data;
					if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->ice_flags))
						goto err_ilseq;
					if (IS_ICONV_ERR_DISCARD(self->ice_flags)) {
						mbstate_init(&self->ice_data.ied_utf8);
						flush_start = data + 1;
						goto next_data;
					}
					ch32 = ch;
					if (!IS_ICONV_ERR_IGNORE(self->ice_flags))
						ch32 = '?';
					status = 1;
				} else if (status == (size_t)-2) {
					return result; /* Everything parsed! */
				}
			}
			if unlikely(ch32 == 0) {
				/* NUL cannot be encoded in XML */
				if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->ice_flags))
					goto err_ilseq;
				if (IS_ICONV_ERR_DISCARD(self->ice_flags)) {
					data += status;
					flush_start = data;
					continue;
				}
				if (IS_ICONV_ERR_REPLACE(self->ice_flags))
					ch32 = '?';
				/* In IS_ICONV_ERR_IGNORE-mode, we do allow NUL to be encoded. */
			}
			data += status;
			flush_start = data;
			/* Output `ch32' in its escaped form. */
			esc = xml_escape(esc_buf, ch32);
do_print_esc:
			DO_encode_output("&", 1);
			DO_encode_output(esc, strlen(esc));
			DO_encode_output(";", 1);
		} else {
			/* During encoding, we only allow printable ASCII and  space.
			 * All other characters we _always_ escape. That way, the xml
			 * codec will encode data that is pure ASCII without  relying
			 * on unicode support during transmit!
			 *
			 * Additionally, we always encode <>&'" */
			if (ch >= 0x20 && ch <= 0x7e &&
			    ch != '<' && ch != '>' && ch != '&' &&
			    ch != '\'' && ch != '\"') {
				/* Can just output as-is! */
			} else {
				/* Must escape! */
				DO_encode_output(flush_start, (size_t)(data - flush_start));
				flush_start = ++data;
				if unlikely(ch == 0) {
					/* NUL cannot be encoded in XML */
					if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->ice_flags)) {
						--data;
						goto err_ilseq;
					}
					if (IS_ICONV_ERR_DISCARD(self->ice_flags))
						continue;
					if (IS_ICONV_ERR_REPLACE(self->ice_flags))
						ch = '?';
					/* In IS_ICONV_ERR_IGNORE-mode, we do allow NUL to be encoded. */
				}
				esc = xml_escape(esc_buf, ch);
				goto do_print_esc;
			}
next_data:
			++data;
		}
	}
	DO_encode_output(flush_start, (size_t)(end - flush_start));
	return result;
err:
	return temp;
err_ilseq:
	self->ice_flags |= ICONV_HASERR;
	if (IS_ICONV_ERR_ERRNO(self->ice_flags))
		errno = EILSEQ;
	return -(ssize_t)(size_t)(end - data);
}


INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_xml_escape_decode(struct iconv_decode *__restrict self,
                           /*utf-8*/ char const *__restrict data, size_t size) {
	ssize_t temp, result = 0;
	char const *ch_start;
	char const *end, *flush_start;
	flush_start = data;
	end         = data + size;
	if unlikely(self->icd_flags & ICONV_HASERR)
		goto err_ilseq;
	if (!mbstate_isempty(&self->icd_data.idd_xml.xe_utf8)) {
		ch_start = data;
		goto parse_unicode;
	}
	while (data < end) {
		char32_t ch;
		ch_start = data;
		ch       = (char32_t)(unsigned char)*data;
		if (ch >= 0x80) {
			size_t status;
parse_unicode:
			status = unicode_c8toc32(&ch, data, (size_t)(end - data),
			                         &self->icd_data.idd_xml.xe_utf8);
			if ((ssize_t)status < 0) {
				if (status == (size_t)-1) {
					if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->icd_flags))
						goto err_ilseq;
					if (IS_ICONV_ERR_DISCARD(self->icd_flags)) {
						mbstate_init(&self->icd_data.idd_xml.xe_utf8);
						if (self->icd_data.idd_xml.xe_mode == _ICONV_DECODE_XML_TXT) {
							DO_decode_output(flush_start, (size_t)(end - flush_start));
							flush_start = data + 1;
						}
						++data;
						continue;
					}
					if (!IS_ICONV_ERR_IGNORE(self->icd_flags))
						ch = '?';
					status = 1;
				} else if (status == (size_t)-2) {
					goto done; /* Everything parsed! */
				}
			}
			data += status;
		} else {
			++data;
		}

		/* Process `ch' */
		switch (__builtin_expect(self->icd_data.idd_xml.xe_mode, _ICONV_DECODE_XML_TXT)) {

		case _ICONV_DECODE_XML_TXT:
handle_txt_char:
			/* XML doesn't allow these characters without them being escaped.
			 * Additionally,  NUL  isn't  allowed  even  when  it's  escaped! */
			if unlikely((ch == 0 || ch == '<') && !IS_ICONV_ERR_IGNORE(self->icd_flags)) {
				DO_decode_output(flush_start, (size_t)(ch_start - flush_start));
err_ilseq_ch_start:
				if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->icd_flags)) {
					data = ch_start;
					goto err_ilseq;
				}
				flush_start                    = ch_start;
				self->icd_data.idd_xml.xe_mode = _ICONV_DECODE_XML_TXT;
				if (IS_ICONV_ERR_DISCARD(self->icd_flags)) {
					flush_start = data;
				} else if (IS_ICONV_ERR_REPLACE(self->icd_flags)) {
					DO_decode_output("?", 1);
					flush_start = data;
				}
				continue;
			}
			if (ch == '&') {
				/* Enter escape mode. */
				DO_decode_output(flush_start, (size_t)(ch_start - flush_start));
				self->icd_data.idd_xml.xe_mode = _ICONV_DECODE_XML_AND;
			}
			break;

		case _ICONV_DECODE_XML_OSM: /* OptionalSeMicollon */
			self->icd_data.idd_xml.xe_mode = _ICONV_DECODE_XML_TXT;
			if (ch != ';') {
				/* Not a semicolon -> just handle it as a text character. */
				flush_start = ch_start;
				goto handle_txt_char;
			}
			/* Consume the ';' */
			flush_start = data;
			break;

		case _ICONV_DECODE_XML_AND:
			if (ch == '#') {
				self->icd_data.idd_xml.xe_mode = _ICONV_DECODE_XML_PND;
			} else if (ch <= 0x7f) { /* Only ASCII allowed in entity names! */
				xml_entity_t const *ent;
				char firstchar[1];
				/* Technically, we'd need to check that `isalnum(ch)', but if that's
				 * not the case,  then `xml_entity_lookup_startswith()' will  return
				 * NULL so it would be a redundant check! */
				firstchar[0] = (char)(unsigned char)ch;
				ent = xml_entity_lookup_startswith(firstchar, 1);
				if unlikely(!ent)
					goto illegal_after_and;
				self->icd_data.idd_xml.xe_ent.e_str = ent;
				self->icd_data.idd_xml.xe_ent.e_len = 1;
				self->icd_data.idd_xml.xe_mode      = _ICONV_DECODE_XML_ENT;
			} else {
				/* Anything else isn't allowed after '&' */
illegal_after_and:
				if (IS_ICONV_ERR_IGNORE(self->icd_flags)) {
					DO_decode_output("&", 1);
					flush_start                    = ch_start;
					self->icd_data.idd_xml.xe_mode = _ICONV_DECODE_XML_TXT;
					continue;
				}
				goto err_ilseq_ch_start;
			}
			break;

		case _ICONV_DECODE_XML_PND:
			if (ch == 'x') { /* Only lowercase 'x' is allowed here! */
				self->icd_data.idd_xml.xe_mode = _ICONV_DECODE_XML_HEX;
				self->icd_data.idd_xml.xe_chr  = 0;
			} else if (ch >= '0' && ch <= '9') {
				self->icd_data.idd_xml.xe_mode = _ICONV_DECODE_XML_DEC;
				self->icd_data.idd_xml.xe_chr  = ch - '0';
			} else {
				/* Anything else isn't allowed after '&#' */
				if (IS_ICONV_ERR_IGNORE(self->icd_flags)) {
					DO_decode_output("&#", 2);
					flush_start                    = ch_start;
					self->icd_data.idd_xml.xe_mode = _ICONV_DECODE_XML_TXT;
					continue;
				}
				goto err_ilseq_ch_start;
			}
			break;

		case _ICONV_DECODE_XML_DEC:
			if (ch == ';') {
				char utf[UNICODE_UTF8_CURLEN];
				size_t len;
				/* Escape character sequence end. */
output_escape_character:
				if unlikely(self->icd_data.idd_xml.xe_chr == 0 && !IS_ICONV_ERR_IGNORE(self->icd_flags))
					goto err_ilseq_ch_start; /* Nope: you're not even allowed to encode NUL here! */
				len = (size_t)(unicode_writeutf8(utf, self->icd_data.idd_xml.xe_chr) - utf);
				DO_decode_output(utf, len);
				self->icd_data.idd_xml.xe_mode = _ICONV_DECODE_XML_TXT;
				flush_start                    = data;
				break;
			} else if (ch >= '0' && ch <= '9') {
				uint32_t newchr;
				if (OVERFLOW_UMUL((uint32_t)self->icd_data.idd_xml.xe_chr, 10, &newchr) ||
				    OVERFLOW_UADD(newchr, (uint8_t)(ch - '0'), &newchr)) {
					if (IS_ICONV_ERR_IGNORE(self->icd_flags)) {
						DO(format_printf(decode_output_printer, decode_output_arg,
						                 "&#%" PRIu32, self->icd_data.idd_xml.xe_chr));
						flush_start                    = ch_start;
						self->icd_data.idd_xml.xe_mode = _ICONV_DECODE_XML_TXT;
						continue;
					}
					goto err_ilseq_ch_start; /* Overflow */
				}
				self->icd_data.idd_xml.xe_chr = (char32_t)newchr;
			} else {
				goto err_ilseq_ch_start;
			}
			break;

		case _ICONV_DECODE_XML_HEX: {
			uint32_t newchr;
			uint8_t digit;
			if (ch == ';') {
				goto output_escape_character;
			} else if (ch >= '0' && ch <= '9') {
				digit = ch - '0';
			} else if (ch >= 'A' && ch <= 'F') {
				digit = 10 + ch - 'A';
			} else if (ch >= 'a' && ch <= 'f') {
				digit = 10 + ch - 'a';
			} else {
				goto err_ilseq_ch_start;
			}
			if (OVERFLOW_UMUL((uint32_t)self->icd_data.idd_xml.xe_chr, 16, &newchr) ||
			    OVERFLOW_UADD(newchr, digit, &newchr)) {
				if (IS_ICONV_ERR_IGNORE(self->icd_flags)) {
					DO(format_printf(decode_output_printer, decode_output_arg,
					                 "&#x%" PRIX32, self->icd_data.idd_xml.xe_chr));
					flush_start                    = ch_start;
					self->icd_data.idd_xml.xe_mode = _ICONV_DECODE_XML_TXT;
					continue;
				}
				goto err_ilseq_ch_start; /* Overflow */
			}
			self->icd_data.idd_xml.xe_chr = (char32_t)newchr;
		}	break;

		case _ICONV_DECODE_XML_ENT: {
			xml_entity_t const *ent;
			if (ch == ';') {
				char const *utf;
				/* End of sequence. Check that our entry also ends. */
				ent = self->icd_data.idd_xml.xe_ent.e_str;
				if (xml_entity_name(ent)[self->icd_data.idd_xml.xe_ent.e_len] != '\0') {
					/* If our entity doesn't end at the specified position, then there may
					 * be another one that does. To handle this case, search the  database
					 * once again but look for the exact string (instead of starts-with) */
					ent = xml_entity_lookup(xml_entity_name(ent), self->icd_data.idd_xml.xe_ent.e_len);
					if unlikely(!ent)
						goto handle_unknown_entity_name;
				}
				self->icd_data.idd_xml.xe_mode = _ICONV_DECODE_XML_TXT;
output_entity_utf8_and_break:
				/* Load the utf replacement for this entry. */
				utf = xml_entity_utf8(ent);
				/* Output the utf replacement. */
				DO_decode_output(utf, strlen(utf));
				flush_start = data;
				break;
			} else if (isalnum(ch) && ch <= 0x7f) {
				/* Another character apart of the entity name. */
				ent = self->icd_data.idd_xml.xe_ent.e_str;
				if (xml_entity_name(ent)[self->icd_data.idd_xml.xe_ent.e_len] != (char)(unsigned char)ch) {
					ent = xml_entity_lookup_startswith_plus1(xml_entity_name(ent),
					                                         self->icd_data.idd_xml.xe_ent.e_len,
					                                         (char)(unsigned char)ch);
					if unlikely(!ent)
						goto handle_unknown_entity_name;
					self->icd_data.idd_xml.xe_ent.e_str = ent;
				}
				++self->icd_data.idd_xml.xe_ent.e_len;
				/* Check if the entry has been completed and it has an optional trailing ';'
				 * If this is the case, then we must immediately output the replacement  and
				 * switch to a mode where we consume the optional ';' */
				if (xml_entity_name(ent)[self->icd_data.idd_xml.xe_ent.e_len] == '\0' && xml_entity_semiopt(ent)) {
					self->icd_data.idd_xml.xe_mode = _ICONV_DECODE_XML_OSM;
					goto output_entity_utf8_and_break;
				}
			} else {
handle_unknown_entity_name:
				if (IS_ICONV_ERR_IGNORE(self->icd_flags)) {
					ent = self->icd_data.idd_xml.xe_ent.e_str;
					DO_decode_output("&", 1);
					DO_decode_output(xml_entity_name(ent), self->icd_data.idd_xml.xe_ent.e_len);
					flush_start                    = ch_start;
					self->icd_data.idd_xml.xe_mode = _ICONV_DECODE_XML_TXT;
					continue;
				}
				goto err_ilseq_ch_start; /* No sequence starts with this prefix. */
			}
		}	break;

		default:
			break;
		}
	}
done:
	if (self->icd_data.idd_xml.xe_mode == _ICONV_DECODE_XML_TXT)
		DO_decode_output(flush_start, (size_t)(end - flush_start));
	return result;
err:
	return temp;
err_ilseq:
	self->icd_flags |= ICONV_HASERR;
	if (IS_ICONV_ERR_ERRNO(self->icd_flags))
		errno = EILSEQ;
	return -(ssize_t)(size_t)(end - data);
}



DECL_END

#endif /* !GUARD_LIBICONV_CONVERT_XML_C */
