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
#include <stddef.h>
#include <string.h>

#include <libiconv/iconv.h>

#include "codecs.h"

DECL_BEGIN

typedef uint16_t codec_name_db_offset_t;

/*[[[deemon (printCodecNameDB from .iconvdata.iconvdata)();]]]*/
struct codec_name_db_struct {
	char _hdr_nul[2];

	/* CODEC_ADOBE_STANDARD_ENCODING */
	char db_ADOBE_STANDARD_ENCODING_0[24]; /* "adobe-standard-encoding" */
	char db_ADOBE_STANDARD_ENCODING_1[24]; /* "csadobestandardencoding" */
	char db_ADOBE_STANDARD_ENCODING_nul;

	/* CODEC_ADOBE_SYMBOL_ENCODING */
	char db_ADOBE_SYMBOL_ENCODING_0[10]; /* "macsymbol" */
	char db_ADOBE_SYMBOL_ENCODING_1[22]; /* "adobe-symbol-encoding" */
	char db_ADOBE_SYMBOL_ENCODING_2[11]; /* "cshppsmath" */
	char db_ADOBE_SYMBOL_ENCODING_3[7];  /* "cp1038" */
	char db_ADOBE_SYMBOL_ENCODING_4[8];  /* "ibm1038" */
	char db_ADOBE_SYMBOL_ENCODING_5[13]; /* "x-mac-symbol" */
	char db_ADOBE_SYMBOL_ENCODING_nul;

	/* CODEC_ADOBE_ZAPF_DINGBATS */
	char db_ADOBE_ZAPF_DINGBATS_0[20]; /* "adobe-zapf-dingbats" */
	char db_ADOBE_ZAPF_DINGBATS_nul;

	/* CODEC_AMIGA_1251 */
	char db_AMIGA_1251_0[11]; /* "amiga-1251" */
	char db_AMIGA_1251_1[8];  /* "ami1251" */
	char db_AMIGA_1251_2[10]; /* "amiga1251" */
	char db_AMIGA_1251_3[9];  /* "ami-1251" */
	char db_AMIGA_1251_4[12]; /* "csamiga1251" */
	char db_AMIGA_1251_nul;

	/* CODEC_ASCII */
	char db_ASCII_0[15]; /* "ansi-x3.4-1968" */
	char db_ASCII_1[9];  /* "iso-ir-6" */
	char db_ASCII_2[15]; /* "ansi-x3.4-1986" */
	char db_ASCII_3[16]; /* "iso646.irv:1991" */
	char db_ASCII_4[6];  /* "ascii" */
	char db_ASCII_5[10]; /* "iso646-us" */
	char db_ASCII_6[9];  /* "us-ascii" */
	char db_ASCII_7[3];  /* "us" */
	char db_ASCII_8[7];  /* "ibm367" */
	char db_ASCII_9[6];  /* "cp367" */
	char db_ASCII_10[10]; /* "ansi-x3.4" */
	char db_ASCII_11[8];  /* "csascii" */
	char db_ASCII_12[9];  /* "osf10020" */
	char db_ASCII_13[8];  /* "cp20127" */
	char db_ASCII_14[14]; /* "windows-20127" */
	char db_ASCII_15[7];  /* "ibm891" */
	char db_ASCII_16[6];  /* "cp891" */
	char db_ASCII_17[9];  /* "csibm891" */
	char db_ASCII_18[12]; /* "osf1002037b" */
	char db_ASCII_19[7];  /* "ibm903" */
	char db_ASCII_20[6];  /* "cp903" */
	char db_ASCII_21[9];  /* "csibm903" */
	char db_ASCII_22[12]; /* "osf10020387" */
	char db_ASCII_23[8];  /* "default" */
	char db_ASCII_24[4];  /* "646" */
	char db_ASCII_25[7];  /* "ascii7" */
	char db_ASCII_26[7];  /* "direct" */
	char db_ASCII_nul;

	/* CODEC_ATARIST */
	char db_ATARIST_0[8]; /* "atarist" */
	char db_ATARIST_nul;

	/* CODEC_BCDIC */
	char db_BCDIC_0[6]; /* "bcdic" */
	char db_BCDIC_nul;

	/* CODEC_BRF */
	char db_BRF_0[4]; /* "brf" */
	char db_BRF_1[6]; /* "csbrf" */
	char db_BRF_nul;

	/* CODEC_BURROUGHS_B5500 */
	char db_BURROUGHS_B5500_0[16]; /* "burroughs-b5500" */
	char db_BURROUGHS_B5500_nul;

	/* CODEC_CP10004 */
	char db_CP10004_0[8];  /* "cp10004" */
	char db_CP10004_1[14]; /* "windows-10004" */
	char db_CP10004_2[13]; /* "x-mac-arabic" */
	char db_CP10004_3[10]; /* "macarabic" */
	char db_CP10004_nul;

	/* CODEC_CP10006 */
	char db_CP10006_0[8];  /* "cp10006" */
	char db_CP10006_1[14]; /* "windows-10006" */
	char db_CP10006_2[12]; /* "x-mac-greek" */
	char db_CP10006_3[17]; /* "cp10006-macgreek" */
	char db_CP10006_4[9];  /* "macgreek" */
	char db_CP10006_5[8];  /* "ibm1280" */
	char db_CP10006_nul;

	/* CODEC_CP10007 */
	char db_CP10007_0[8];  /* "cp10007" */
	char db_CP10007_1[14]; /* "windows-10007" */
	char db_CP10007_2[7];  /* "cp1283" */
	char db_CP10007_3[8];  /* "ibm1283" */
	char db_CP10007_4[16]; /* "ms-mac-cyrillic" */
	char db_CP10007_5[14]; /* "msmaccyrillic" */
	char db_CP10007_6[20]; /* "cp10007-maccyrillic" */
	char db_CP10007_7[13]; /* "mac-cyrillic" */
	char db_CP10007_8[12]; /* "maccyrillic" */
	char db_CP10007_nul;

	/* CODEC_CP10017 */
	char db_CP10017_0[8];  /* "cp10017" */
	char db_CP10017_1[14]; /* "windows-10017" */
	char db_CP10017_2[16]; /* "x-mac-ukrainian" */
	char db_CP10017_3[6];  /* "macuk" */
	char db_CP10017_4[7];  /* "mac-uk" */
	char db_CP10017_5[13]; /* "macukrainian" */
	char db_CP10017_nul;

	/* CODEC_CP1004 */
	char db_CP1004_0[7];  /* "cp1004" */
	char db_CP1004_1[17]; /* "windows-extended" */
	char db_CP1004_2[8];  /* "ibm1004" */
	char db_CP1004_3[10]; /* "os2latin1" */
	char db_CP1004_nul;

	/* CODEC_CP1006 */
	char db_CP1006_0[7];  /* "cp1006" */
	char db_CP1006_1[8];  /* "ibm1006" */
	char db_CP1006_2[14]; /* "iso8-bit-urdu" */
	char db_CP1006_nul;

	/* CODEC_CP1008 */
	char db_CP1008_0[7];  /* "cp1008" */
	char db_CP1008_1[8];  /* "ibm1008" */
	char db_CP1008_2[10]; /* "csibm1008" */
	char db_CP1008_3[7];  /* "cp5104" */
	char db_CP1008_4[8];  /* "ibm5104" */
	char db_CP1008_nul;

	/* CODEC_CP1025 */
	char db_CP1025_0[7];  /* "cp1025" */
	char db_CP1025_1[8];  /* "ibm1025" */
	char db_CP1025_2[10]; /* "csibm1025" */
	char db_CP1025_nul;

	/* CODEC_CP1026 */
	char db_CP1026_0[8];  /* "ibm1026" */
	char db_CP1026_1[7];  /* "cp1026" */
	char db_CP1026_2[10]; /* "csibm1026" */
	char db_CP1026_3[5];  /* "1026" */
	char db_CP1026_4[12]; /* "osf10020402" */
	char db_CP1026_nul;

	/* CODEC_CP1036 */
	char db_CP1036_0[7];  /* "cp1036" */
	char db_CP1036_1[8];  /* "ibm1036" */
	char db_CP1036_2[5];  /* "t.61" */
	char db_CP1036_3[9];  /* "t.618bit" */
	char db_CP1036_4[10]; /* "t.61-8bit" */
	char db_CP1036_5[8];  /* "cp20261" */
	char db_CP1036_6[14]; /* "windows-20261" */
	char db_CP1036_7[11]; /* "iso-ir-103" */
	char db_CP1036_8[16]; /* "csiso103t618bit" */
	char db_CP1036_nul;

	/* CODEC_CP1040 */
	char db_CP1040_0[7]; /* "cp1040" */
	char db_CP1040_nul;

	/* CODEC_CP1041 */
	char db_CP1041_0[8]; /* "ibm1041" */
	char db_CP1041_1[7]; /* "cp1041" */
	char db_CP1041_nul;

	/* CODEC_CP1042 */
	char db_CP1042_0[7]; /* "cp1042" */
	char db_CP1042_nul;

	/* CODEC_CP1043 */
	char db_CP1043_0[8]; /* "ibm1043" */
	char db_CP1043_1[7]; /* "cp1043" */
	char db_CP1043_nul;

	/* CODEC_CP1046 */
	char db_CP1046_0[7]; /* "cp1046" */
	char db_CP1046_1[5]; /* "1046" */
	char db_CP1046_2[8]; /* "ibm1046" */
	char db_CP1046_nul;

	/* CODEC_CP1047 */
	char db_CP1047_0[7];  /* "cp1047" */
	char db_CP1047_1[8];  /* "ibm1047" */
	char db_CP1047_2[5];  /* "1047" */
	char db_CP1047_3[12]; /* "osf10020417" */
	char db_CP1047_4[10]; /* "csibm1047" */
	char db_CP1047_nul;

	/* CODEC_CP1057 */
	char db_CP1057_0[7]; /* "cp1057" */
	char db_CP1057_1[8]; /* "hp-pc-8" */
	char db_CP1057_nul;

	/* CODEC_CP1088 */
	char db_CP1088_0[8]; /* "ibm1088" */
	char db_CP1088_1[7]; /* "cp1088" */
	char db_CP1088_nul;

	/* CODEC_CP1090 */
	char db_CP1090_0[7];  /* "cp1090" */
	char db_CP1090_1[8];  /* "ibm1090" */
	char db_CP1090_2[21]; /* "dec-special-graphics" */
	char db_CP1090_nul;

	/* CODEC_CP1097 */
	char db_CP1097_0[7];  /* "cp1097" */
	char db_CP1097_1[8];  /* "ibm1097" */
	char db_CP1097_2[10]; /* "csibm1097" */
	char db_CP1097_nul;

	/* CODEC_CP1098 */
	char db_CP1098_0[7]; /* "cp1098" */
	char db_CP1098_1[8]; /* "ibm1098" */
	char db_CP1098_nul;

	/* CODEC_CP1100 */
	char db_CP1100_0[8]; /* "dec-mcs" */
	char db_CP1100_1[4]; /* "dec" */
	char db_CP1100_2[7]; /* "cp1100" */
	char db_CP1100_3[8]; /* "ibm1100" */
	char db_CP1100_4[7]; /* "we8dec" */
	char db_CP1100_5[9]; /* "csdecmcs" */
	char db_CP1100_6[7]; /* "decmcs" */
	char db_CP1100_nul;

	/* CODEC_CP1112 */
	char db_CP1112_0[7];  /* "cp1112" */
	char db_CP1112_1[8];  /* "ibm1112" */
	char db_CP1112_2[10]; /* "csibm1112" */
	char db_CP1112_nul;

	/* CODEC_CP1114 */
	char db_CP1114_0[8]; /* "ibm1114" */
	char db_CP1114_1[7]; /* "cp1114" */
	char db_CP1114_nul;

	/* CODEC_CP1115 */
	char db_CP1115_0[8]; /* "ibm1115" */
	char db_CP1115_1[7]; /* "cp1115" */
	char db_CP1115_nul;

	/* CODEC_CP1116 */
	char db_CP1116_0[7]; /* "cp1116" */
	char db_CP1116_1[8]; /* "ibm1116" */
	char db_CP1116_nul;

	/* CODEC_CP1117 */
	char db_CP1117_0[7]; /* "cp1117" */
	char db_CP1117_1[8]; /* "ibm1117" */
	char db_CP1117_nul;

	/* CODEC_CP1122 */
	char db_CP1122_0[7];  /* "cp1122" */
	char db_CP1122_1[8];  /* "ibm1122" */
	char db_CP1122_2[10]; /* "csibm1122" */
	char db_CP1122_nul;

	/* CODEC_CP1123 */
	char db_CP1123_0[7];  /* "cp1123" */
	char db_CP1123_1[8];  /* "ibm1123" */
	char db_CP1123_2[10]; /* "csibm1123" */
	char db_CP1123_nul;

	/* CODEC_CP1124 */
	char db_CP1124_0[7];  /* "cp1124" */
	char db_CP1124_1[8];  /* "ibm1124" */
	char db_CP1124_2[10]; /* "csibm1124" */
	char db_CP1124_nul;

	/* CODEC_CP1125 */
	char db_CP1125_0[7];  /* "cp1125" */
	char db_CP1125_1[12]; /* "rst-2018-91" */
	char db_CP1125_2[7];  /* "cp866u" */
	char db_CP1125_3[7];  /* "ruscii" */
	char db_CP1125_4[7];  /* "ibm848" */
	char db_CP1125_nul;

	/* CODEC_CP1127 */
	char db_CP1127_0[7]; /* "cp1127" */
	char db_CP1127_nul;

	/* CODEC_CP1130 */
	char db_CP1130_0[7];  /* "cp1130" */
	char db_CP1130_1[8];  /* "ibm1130" */
	char db_CP1130_2[10]; /* "csibm1130" */
	char db_CP1130_nul;

	/* CODEC_CP1131 */
	char db_CP1131_0[7]; /* "cp1131" */
	char db_CP1131_1[8]; /* "ibm1131" */
	char db_CP1131_nul;

	/* CODEC_CP1132 */
	char db_CP1132_0[7];  /* "cp1132" */
	char db_CP1132_1[8];  /* "ibm1132" */
	char db_CP1132_2[10]; /* "csibm1132" */
	char db_CP1132_nul;

	/* CODEC_CP1133 */
	char db_CP1133_0[7];  /* "cp1133" */
	char db_CP1133_1[8];  /* "ibm1133" */
	char db_CP1133_2[10]; /* "csibm1133" */
	char db_CP1133_nul;

	/* CODEC_CP1137 */
	char db_CP1137_0[7];  /* "cp1137" */
	char db_CP1137_1[8];  /* "ibm1137" */
	char db_CP1137_2[10]; /* "csibm1137" */
	char db_CP1137_nul;

	/* CODEC_CP1140 */
	char db_CP1140_0[7];  /* "cp1140" */
	char db_CP1140_1[8];  /* "ibm1140" */
	char db_CP1140_2[5];  /* "1140" */
	char db_CP1140_3[10]; /* "csibm1140" */
	char db_CP1140_4[10]; /* "ccsid1140" */
	char db_CP1140_5[18]; /* "ebcdic-us-37+euro" */
	char db_CP1140_nul;

	/* CODEC_CP1141 */
	char db_CP1141_0[7];  /* "cp1141" */
	char db_CP1141_1[8];  /* "ibm1141" */
	char db_CP1141_2[5];  /* "1141" */
	char db_CP1141_3[10]; /* "csibm1141" */
	char db_CP1141_4[10]; /* "ccsid1141" */
	char db_CP1141_5[19]; /* "ebcdic-de-273+euro" */
	char db_CP1141_nul;

	/* CODEC_CP1142 */
	char db_CP1142_0[7];  /* "cp1142" */
	char db_CP1142_1[8];  /* "ibm1142" */
	char db_CP1142_2[5];  /* "1142" */
	char db_CP1142_3[10]; /* "csibm1142" */
	char db_CP1142_4[10]; /* "ccsid1142" */
	char db_CP1142_5[19]; /* "ebcdic-dk-277+euro" */
	char db_CP1142_6[19]; /* "ebcdic-no-277+euro" */
	char db_CP1142_nul;

	/* CODEC_CP1143 */
	char db_CP1143_0[7];  /* "cp1143" */
	char db_CP1143_1[8];  /* "ibm1143" */
	char db_CP1143_2[5];  /* "1143" */
	char db_CP1143_3[10]; /* "csibm1143" */
	char db_CP1143_4[10]; /* "ccsid1143" */
	char db_CP1143_5[19]; /* "ebcdic-fi-278+euro" */
	char db_CP1143_6[19]; /* "ebcdic-se-278+euro" */
	char db_CP1143_nul;

	/* CODEC_CP1144 */
	char db_CP1144_0[7];  /* "cp1144" */
	char db_CP1144_1[8];  /* "ibm1144" */
	char db_CP1144_2[5];  /* "1144" */
	char db_CP1144_3[10]; /* "csibm1144" */
	char db_CP1144_4[10]; /* "ccsid1144" */
	char db_CP1144_5[19]; /* "ebcdic-it-280+euro" */
	char db_CP1144_nul;

	/* CODEC_CP1145 */
	char db_CP1145_0[7];  /* "cp1145" */
	char db_CP1145_1[8];  /* "ibm1145" */
	char db_CP1145_2[5];  /* "1145" */
	char db_CP1145_3[10]; /* "csibm1145" */
	char db_CP1145_4[10]; /* "ccsid1145" */
	char db_CP1145_5[19]; /* "ebcdic-es-284+euro" */
	char db_CP1145_nul;

	/* CODEC_CP1146 */
	char db_CP1146_0[7];  /* "cp1146" */
	char db_CP1146_1[8];  /* "ibm1146" */
	char db_CP1146_2[5];  /* "1146" */
	char db_CP1146_3[10]; /* "csibm1146" */
	char db_CP1146_4[10]; /* "ccsid1146" */
	char db_CP1146_5[19]; /* "ebcdic-gb-285+euro" */
	char db_CP1146_nul;

	/* CODEC_CP1147 */
	char db_CP1147_0[7];  /* "cp1147" */
	char db_CP1147_1[8];  /* "ibm1147" */
	char db_CP1147_2[5];  /* "1147" */
	char db_CP1147_3[10]; /* "csibm1147" */
	char db_CP1147_4[10]; /* "ccsid1147" */
	char db_CP1147_5[19]; /* "ebcdic-fr-297+euro" */
	char db_CP1147_nul;

	/* CODEC_CP1148 */
	char db_CP1148_0[7];  /* "cp1148" */
	char db_CP1148_1[8];  /* "ibm1148" */
	char db_CP1148_2[5];  /* "1148" */
	char db_CP1148_3[10]; /* "csibm1148" */
	char db_CP1148_4[10]; /* "ccsid1148" */
	char db_CP1148_5[30]; /* "ebcdic-international-500+euro" */
	char db_CP1148_nul;

	/* CODEC_CP1149 */
	char db_CP1149_0[7];  /* "cp1149" */
	char db_CP1149_1[8];  /* "ibm1149" */
	char db_CP1149_2[5];  /* "1149" */
	char db_CP1149_3[10]; /* "csibm1149" */
	char db_CP1149_4[10]; /* "ccsid1149" */
	char db_CP1149_5[19]; /* "ebcdic-is-871+euro" */
	char db_CP1149_nul;

	/* CODEC_CP1153 */
	char db_CP1153_0[7];  /* "cp1153" */
	char db_CP1153_1[8];  /* "ibm1153" */
	char db_CP1153_2[10]; /* "csibm1153" */
	char db_CP1153_nul;

	/* CODEC_CP1154 */
	char db_CP1154_0[7];  /* "cp1154" */
	char db_CP1154_1[8];  /* "ibm1154" */
	char db_CP1154_2[10]; /* "csibm1154" */
	char db_CP1154_nul;

	/* CODEC_CP1155 */
	char db_CP1155_0[7];  /* "cp1155" */
	char db_CP1155_1[8];  /* "ibm1155" */
	char db_CP1155_2[10]; /* "csibm1155" */
	char db_CP1155_nul;

	/* CODEC_CP1156 */
	char db_CP1156_0[7];  /* "cp1156" */
	char db_CP1156_1[8];  /* "ibm1156" */
	char db_CP1156_2[10]; /* "csibm1156" */
	char db_CP1156_nul;

	/* CODEC_CP1157 */
	char db_CP1157_0[7];  /* "cp1157" */
	char db_CP1157_1[8];  /* "ibm1157" */
	char db_CP1157_2[10]; /* "csibm1157" */
	char db_CP1157_nul;

	/* CODEC_CP1158 */
	char db_CP1158_0[7];  /* "cp1158" */
	char db_CP1158_1[8];  /* "ibm1158" */
	char db_CP1158_2[10]; /* "csibm1158" */
	char db_CP1158_nul;

	/* CODEC_CP1160 */
	char db_CP1160_0[7];  /* "cp1160" */
	char db_CP1160_1[8];  /* "ibm1160" */
	char db_CP1160_2[10]; /* "csibm1160" */
	char db_CP1160_nul;

	/* CODEC_CP1161 */
	char db_CP1161_0[7];  /* "cp1161" */
	char db_CP1161_1[8];  /* "ibm1161" */
	char db_CP1161_2[10]; /* "csibm1161" */
	char db_CP1161_nul;

	/* CODEC_CP1162 */
	char db_CP1162_0[7];  /* "cp1162" */
	char db_CP1162_1[8];  /* "ibm1162" */
	char db_CP1162_2[14]; /* "csibm11621162" */
	char db_CP1162_nul;

	/* CODEC_CP1163 */
	char db_CP1163_0[7];  /* "cp1163" */
	char db_CP1163_1[8];  /* "ibm1163" */
	char db_CP1163_2[10]; /* "csibm1163" */
	char db_CP1163_nul;

	/* CODEC_CP1164 */
	char db_CP1164_0[7];  /* "cp1164" */
	char db_CP1164_1[8];  /* "ibm1164" */
	char db_CP1164_2[10]; /* "csibm1164" */
	char db_CP1164_nul;

	/* CODEC_CP1166 */
	char db_CP1166_0[7];  /* "cp1166" */
	char db_CP1166_1[8];  /* "ibm1166" */
	char db_CP1166_2[10]; /* "csibm1166" */
	char db_CP1166_nul;

	/* CODEC_CP1250 */
	char db_CP1250_0[7];  /* "cp1250" */
	char db_CP1250_1[8];  /* "ibm1250" */
	char db_CP1250_2[13]; /* "windows-1250" */
	char db_CP1250_3[14]; /* "cswindows1250" */
	char db_CP1250_4[6];  /* "ms-ee" */
	char db_CP1250_nul;

	/* CODEC_CP1251 */
	char db_CP1251_0[7];  /* "cp1251" */
	char db_CP1251_1[8];  /* "ibm1251" */
	char db_CP1251_2[13]; /* "windows-1251" */
	char db_CP1251_3[14]; /* "cswindows1251" */
	char db_CP1251_4[8];  /* "ms-cyrl" */
	char db_CP1251_nul;

	/* CODEC_CP1252 */
	char db_CP1252_0[7];  /* "cp1252" */
	char db_CP1252_1[8];  /* "ibm1252" */
	char db_CP1252_2[13]; /* "windows-1252" */
	char db_CP1252_3[14]; /* "cswindows1252" */
	char db_CP1252_4[8];  /* "ms-ansi" */
	char db_CP1252_nul;

	/* CODEC_CP1253 */
	char db_CP1253_0[7];  /* "cp1253" */
	char db_CP1253_1[8];  /* "ibm1253" */
	char db_CP1253_2[13]; /* "windows-1253" */
	char db_CP1253_3[14]; /* "cswindows1253" */
	char db_CP1253_4[9];  /* "ms-greek" */
	char db_CP1253_nul;

	/* CODEC_CP1254 */
	char db_CP1254_0[7];  /* "cp1254" */
	char db_CP1254_1[8];  /* "ibm1254" */
	char db_CP1254_2[13]; /* "windows-1254" */
	char db_CP1254_3[14]; /* "cswindows1254" */
	char db_CP1254_4[8];  /* "ms-turk" */
	char db_CP1254_nul;

	/* CODEC_CP1255 */
	char db_CP1255_0[7];  /* "cp1255" */
	char db_CP1255_1[8];  /* "ibm1255" */
	char db_CP1255_2[13]; /* "windows-1255" */
	char db_CP1255_3[14]; /* "cswindows1255" */
	char db_CP1255_4[8];  /* "ms-hebr" */
	char db_CP1255_nul;

	/* CODEC_CP1256 */
	char db_CP1256_0[7];  /* "cp1256" */
	char db_CP1256_1[8];  /* "ibm1256" */
	char db_CP1256_2[13]; /* "windows-1256" */
	char db_CP1256_3[14]; /* "cswindows1256" */
	char db_CP1256_4[8];  /* "ms-arab" */
	char db_CP1256_5[7];  /* "cp9448" */
	char db_CP1256_6[8];  /* "ibm9448" */
	char db_CP1256_7[10]; /* "csibm9448" */
	char db_CP1256_nul;

	/* CODEC_CP1257 */
	char db_CP1257_0[7];  /* "cp1257" */
	char db_CP1257_1[8];  /* "ibm1257" */
	char db_CP1257_2[13]; /* "windows-1257" */
	char db_CP1257_3[11]; /* "lst-1590-3" */
	char db_CP1257_4[14]; /* "cswindows1257" */
	char db_CP1257_5[11]; /* "winbaltrim" */
	char db_CP1257_nul;

	/* CODEC_CP1258 */
	char db_CP1258_0[7];  /* "cp1258" */
	char db_CP1258_1[8];  /* "ibm1258" */
	char db_CP1258_2[13]; /* "windows-1258" */
	char db_CP1258_3[14]; /* "cswindows1258" */
	char db_CP1258_4[7];  /* "cp1129" */
	char db_CP1258_5[8];  /* "ibm1129" */
	char db_CP1258_6[10]; /* "csibm1129" */
	char db_CP1258_nul;

	/* CODEC_CP1270 */
	char db_CP1270_0[7];  /* "cp1270" */
	char db_CP1270_1[13]; /* "windows-1270" */
	char db_CP1270_2[4];  /* "ws2" */
	char db_CP1270_3[9];  /* "winsami2" */
	char db_CP1270_4[11]; /* "win-sami-2" */
	char db_CP1270_nul;

	/* CODEC_CP12712 */
	char db_CP12712_0[8];  /* "cp12712" */
	char db_CP12712_1[9];  /* "ibm12712" */
	char db_CP12712_2[11]; /* "csibm12712" */
	char db_CP12712_nul;

	/* CODEC_CP1275 */
	char db_CP1275_0[10]; /* "macintosh" */
	char db_CP1275_1[4];  /* "mac" */
	char db_CP1275_2[12]; /* "csmacintosh" */
	char db_CP1275_3[7];  /* "cp1275" */
	char db_CP1275_4[8];  /* "ibm1275" */
	char db_CP1275_5[8];  /* "cp10000" */
	char db_CP1275_6[14]; /* "windows-10000" */
	char db_CP1275_7[12]; /* "x-mac-roman" */
	char db_CP1275_8[9];  /* "macroman" */
	char db_CP1275_9[17]; /* "cp10000-macroman" */
	char db_CP1275_nul;

	/* CODEC_CP1276 */
	char db_CP1276_0[7];  /* "cp1276" */
	char db_CP1276_1[29]; /* "postscript-standard-encoding" */
	char db_CP1276_2[17]; /* "standardencoding" */
	char db_CP1276_3[11]; /* "postscript" */
	char db_CP1276_nul;

	/* CODEC_CP1281 */
	char db_CP1281_0[11]; /* "macturkish" */
	char db_CP1281_1[7];  /* "cp1281" */
	char db_CP1281_2[8];  /* "ibm1281" */
	char db_CP1281_3[8];  /* "cp10081" */
	char db_CP1281_4[14]; /* "windows-10081" */
	char db_CP1281_5[14]; /* "x-mac-turkish" */
	char db_CP1281_6[19]; /* "cp10081-macturkish" */
	char db_CP1281_nul;

	/* CODEC_CP1282 */
	char db_CP1282_0[17]; /* "maccentraleurope" */
	char db_CP1282_1[7];  /* "cp1282" */
	char db_CP1282_2[8];  /* "ibm1282" */
	char db_CP1282_3[8];  /* "cp10029" */
	char db_CP1282_4[14]; /* "windows-10029" */
	char db_CP1282_5[9];  /* "x-mac-ce" */
	char db_CP1282_6[18]; /* "mac-centraleurope" */
	char db_CP1282_7[18]; /* "cp10029-maclatin2" */
	char db_CP1282_nul;

	/* CODEC_CP1284 */
	char db_CP1284_0[12]; /* "maccroatian" */
	char db_CP1284_1[7];  /* "cp1284" */
	char db_CP1284_2[8];  /* "ibm1284" */
	char db_CP1284_3[8];  /* "cp10082" */
	char db_CP1284_4[14]; /* "windows-10082" */
	char db_CP1284_5[15]; /* "x-mac-croatian" */
	char db_CP1284_nul;

	/* CODEC_CP1285 */
	char db_CP1285_0[11]; /* "macromania" */
	char db_CP1285_1[7];  /* "cp1285" */
	char db_CP1285_2[8];  /* "ibm1285" */
	char db_CP1285_3[8];  /* "cp10010" */
	char db_CP1285_4[14]; /* "windows-10010" */
	char db_CP1285_5[15]; /* "x-mac-romanian" */
	char db_CP1285_nul;

	/* CODEC_CP1286 */
	char db_CP1286_0[11]; /* "maciceland" */
	char db_CP1286_1[7];  /* "cp1286" */
	char db_CP1286_2[8];  /* "ibm1286" */
	char db_CP1286_3[8];  /* "cp10079" */
	char db_CP1286_4[14]; /* "windows-10079" */
	char db_CP1286_5[16]; /* "x-mac-icelandic" */
	char db_CP1286_6[21]; /* "cp10079-macicelandic" */
	char db_CP1286_nul;

	/* CODEC_CP1287 */
	char db_CP1287_0[7];  /* "cp1287" */
	char db_CP1287_1[18]; /* "dec-greek-(8-bit)" */
	char db_CP1287_2[16]; /* "dec-greek-8-bit" */
	char db_CP1287_3[12]; /* "dec-greek-8" */
	char db_CP1287_4[10]; /* "dec-greek" */
	char db_CP1287_5[7];  /* "el8dec" */
	char db_CP1287_nul;

	/* CODEC_CP1288 */
	char db_CP1288_0[7];  /* "cp1288" */
	char db_CP1288_1[20]; /* "dec-turkish-(8-bit)" */
	char db_CP1288_2[18]; /* "dec-turkish-8-bit" */
	char db_CP1288_3[14]; /* "dec-turkish-8" */
	char db_CP1288_4[12]; /* "dec-turkish" */
	char db_CP1288_5[7];  /* "tr8dec" */
	char db_CP1288_nul;

	/* CODEC_CP16804 */
	char db_CP16804_0[8];  /* "cp16804" */
	char db_CP16804_1[9];  /* "ibm16804" */
	char db_CP16804_2[11]; /* "csibm16804" */
	char db_CP16804_nul;

	/* CODEC_CP17248 */
	char db_CP17248_0[8]; /* "cp17248" */
	char db_CP17248_nul;

	/* CODEC_CP20269 */
	char db_CP20269_0[8];  /* "cp20269" */
	char db_CP20269_1[5];  /* "t.51" */
	char db_CP20269_2[8];  /* "iso6937" */
	char db_CP20269_3[11]; /* "iso-ir-156" */
	char db_CP20269_4[13]; /* "iso6937:1992" */
	char db_CP20269_nul;

	/* CODEC_CP273 */
	char db_CP273_0[7];  /* "ibm273" */
	char db_CP273_1[6];  /* "cp273" */
	char db_CP273_2[9];  /* "csibm273" */
	char db_CP273_3[12]; /* "osf10020111" */
	char db_CP273_nul;

	/* CODEC_CP274 */
	char db_CP274_0[7];  /* "ibm274" */
	char db_CP274_1[10]; /* "ebcdic-be" */
	char db_CP274_2[6];  /* "cp274" */
	char db_CP274_3[9];  /* "csibm274" */
	char db_CP274_nul;

	/* CODEC_CP275 */
	char db_CP275_0[7];  /* "ibm275" */
	char db_CP275_1[10]; /* "ebcdic-br" */
	char db_CP275_2[6];  /* "cp275" */
	char db_CP275_3[9];  /* "csibm275" */
	char db_CP275_nul;

	/* CODEC_CP278 */
	char db_CP278_0[7];  /* "ibm278" */
	char db_CP278_1[6];  /* "cp278" */
	char db_CP278_2[13]; /* "ebcdic-cp-fi" */
	char db_CP278_3[13]; /* "ebcdic-cp-se" */
	char db_CP278_4[9];  /* "csibm278" */
	char db_CP278_5[12]; /* "osf10020116" */
	char db_CP278_nul;

	/* CODEC_CP280 */
	char db_CP280_0[7];  /* "ibm280" */
	char db_CP280_1[6];  /* "cp280" */
	char db_CP280_2[13]; /* "ebcdic-cp-it" */
	char db_CP280_3[9];  /* "csibm280" */
	char db_CP280_4[12]; /* "osf10020118" */
	char db_CP280_nul;

	/* CODEC_CP281 */
	char db_CP281_0[7];  /* "ibm281" */
	char db_CP281_1[12]; /* "ebcdic-jp-e" */
	char db_CP281_2[6];  /* "cp281" */
	char db_CP281_3[9];  /* "csibm281" */
	char db_CP281_nul;

	/* CODEC_CP284 */
	char db_CP284_0[7];  /* "ibm284" */
	char db_CP284_1[6];  /* "cp284" */
	char db_CP284_2[13]; /* "ebcdic-cp-es" */
	char db_CP284_3[9];  /* "csibm284" */
	char db_CP284_4[12]; /* "osf1002011c" */
	char db_CP284_5[7];  /* "cp1079" */
	char db_CP284_nul;

	/* CODEC_CP285 */
	char db_CP285_0[7];  /* "ibm285" */
	char db_CP285_1[6];  /* "cp285" */
	char db_CP285_2[13]; /* "ebcdic-cp-gb" */
	char db_CP285_3[9];  /* "csibm285" */
	char db_CP285_4[12]; /* "osf1002011d" */
	char db_CP285_nul;

	/* CODEC_CP290 */
	char db_CP290_0[7];  /* "ibm290" */
	char db_CP290_1[6];  /* "cp290" */
	char db_CP290_2[15]; /* "ebcdic-jp-kana" */
	char db_CP290_3[9];  /* "csibm290" */
	char db_CP290_4[12]; /* "osf10020122" */
	char db_CP290_nul;

	/* CODEC_CP297 */
	char db_CP297_0[7];  /* "ibm297" */
	char db_CP297_1[6];  /* "cp297" */
	char db_CP297_2[13]; /* "ebcdic-cp-fr" */
	char db_CP297_3[9];  /* "csibm297" */
	char db_CP297_4[12]; /* "osf10020129" */
	char db_CP297_5[7];  /* "cp1081" */
	char db_CP297_nul;

	/* CODEC_CP3012 */
	char db_CP3012_0[7]; /* "cp3012" */
	char db_CP3012_1[7]; /* "ruslat" */
	char db_CP3012_nul;

	/* CODEC_CP353 */
	char db_CP353_0[6]; /* "cp353" */
	char db_CP353_nul;

	/* CODEC_CP355 */
	char db_CP355_0[6]; /* "cp355" */
	char db_CP355_1[9]; /* "pttc/bcd" */
	char db_CP355_nul;

	/* CODEC_CP357 */
	char db_CP357_0[6];  /* "cp357" */
	char db_CP357_1[11]; /* "pttc/bcd-h" */
	char db_CP357_nul;

	/* CODEC_CP358 */
	char db_CP358_0[6];  /* "cp358" */
	char db_CP358_1[11]; /* "pttc/bcd-c" */
	char db_CP358_nul;

	/* CODEC_CP359 */
	char db_CP359_0[6];  /* "cp359" */
	char db_CP359_1[11]; /* "pttc/bcd-m" */
	char db_CP359_2[6];  /* "cp360" */
	char db_CP359_3[11]; /* "pttc/bcd-d" */
	char db_CP359_nul;

	/* CODEC_CP37 */
	char db_CP37_0[6];  /* "ibm37" */
	char db_CP37_1[5];  /* "cp37" */
	char db_CP37_2[13]; /* "ebcdic-cp-us" */
	char db_CP37_3[13]; /* "ebcdic-cp-ca" */
	char db_CP37_4[13]; /* "ebcdic-cp-wt" */
	char db_CP37_5[13]; /* "ebcdic-cp-nl" */
	char db_CP37_6[8];  /* "csibm37" */
	char db_CP37_7[12]; /* "osf10020025" */
	char db_CP37_8[7];  /* "cp1070" */
	char db_CP37_9[6];  /* "cp282" */
	char db_CP37_nul;

	/* CODEC_CP38 */
	char db_CP38_0[6];  /* "ibm38" */
	char db_CP38_1[11]; /* "ebcdic-int" */
	char db_CP38_2[5];  /* "cp38" */
	char db_CP38_3[8];  /* "csibm38" */
	char db_CP38_nul;

	/* CODEC_CP420 */
	char db_CP420_0[7];  /* "ibm420" */
	char db_CP420_1[6];  /* "cp420" */
	char db_CP420_2[14]; /* "ebcdic-cp-ar1" */
	char db_CP420_3[9];  /* "csibm420" */
	char db_CP420_4[12]; /* "osf100201a4" */
	char db_CP420_nul;

	/* CODEC_CP423 */
	char db_CP423_0[7];  /* "ibm423" */
	char db_CP423_1[6];  /* "cp423" */
	char db_CP423_2[13]; /* "ebcdic-cp-gr" */
	char db_CP423_3[9];  /* "csibm423" */
	char db_CP423_nul;

	/* CODEC_CP424 */
	char db_CP424_0[7];  /* "ibm424" */
	char db_CP424_1[6];  /* "cp424" */
	char db_CP424_2[13]; /* "ebcdic-cp-he" */
	char db_CP424_3[9];  /* "csibm424" */
	char db_CP424_4[12]; /* "osf100201a8" */
	char db_CP424_nul;

	/* CODEC_CP437 */
	char db_CP437_0[7];  /* "ibm437" */
	char db_CP437_1[6];  /* "cp437" */
	char db_CP437_2[4];  /* "437" */
	char db_CP437_3[17]; /* "cspc8codepage437" */
	char db_CP437_4[6];  /* "oemus" */
	char db_CP437_5[12]; /* "osf100201b5" */
	char db_CP437_nul;

	/* CODEC_CP4517 */
	char db_CP4517_0[7];  /* "cp4517" */
	char db_CP4517_1[8];  /* "ibm4517" */
	char db_CP4517_2[10]; /* "csibm4517" */
	char db_CP4517_nul;

	/* CODEC_CP4899 */
	char db_CP4899_0[7];  /* "cp4899" */
	char db_CP4899_1[8];  /* "ibm4899" */
	char db_CP4899_2[10]; /* "csibm4899" */
	char db_CP4899_nul;

	/* CODEC_CP4909 */
	char db_CP4909_0[7];  /* "cp4909" */
	char db_CP4909_1[8];  /* "ibm4909" */
	char db_CP4909_2[10]; /* "csibm4909" */
	char db_CP4909_nul;

	/* CODEC_CP4971 */
	char db_CP4971_0[7];  /* "cp4971" */
	char db_CP4971_1[8];  /* "ibm4971" */
	char db_CP4971_2[10]; /* "csibm4971" */
	char db_CP4971_nul;

	/* CODEC_CP500 */
	char db_CP500_0[7];  /* "ibm500" */
	char db_CP500_1[6];  /* "cp500" */
	char db_CP500_2[13]; /* "ebcdic-cp-be" */
	char db_CP500_3[13]; /* "ebcdic-cp-ch" */
	char db_CP500_4[9];  /* "csibm500" */
	char db_CP500_5[4];  /* "500" */
	char db_CP500_6[6];  /* "500v1" */
	char db_CP500_7[12]; /* "osf100201f4" */
	char db_CP500_8[7];  /* "cp1084" */
	char db_CP500_nul;

	/* CODEC_CP5347 */
	char db_CP5347_0[7];  /* "cp5347" */
	char db_CP5347_1[8];  /* "ibm5347" */
	char db_CP5347_2[10]; /* "csibm5347" */
	char db_CP5347_nul;

	/* CODEC_CP667 */
	char db_CP667_0[8]; /* "mazovia" */
	char db_CP667_1[6]; /* "cp667" */
	char db_CP667_2[6]; /* "cp790" */
	char db_CP667_3[6]; /* "cp991" */
	char db_CP667_4[4]; /* "maz" */
	char db_CP667_nul;

	/* CODEC_CP668 */
	char db_CP668_0[6]; /* "cp668" */
	char db_CP668_nul;

	/* CODEC_CP708 */
	char db_CP708_0[6]; /* "cp708" */
	char db_CP708_1[7]; /* "ibm708" */
	char db_CP708_nul;

	/* CODEC_CP720 */
	char db_CP720_0[6]; /* "cp720" */
	char db_CP720_1[7]; /* "ibm720" */
	char db_CP720_2[7]; /* "oem720" */
	char db_CP720_nul;

	/* CODEC_CP737 */
	char db_CP737_0[6]; /* "cp737" */
	char db_CP737_1[7]; /* "ibm737" */
	char db_CP737_2[7]; /* "oem737" */
	char db_CP737_nul;

	/* CODEC_CP770 */
	char db_CP770_0[6]; /* "cp770" */
	char db_CP770_nul;

	/* CODEC_CP771 */
	char db_CP771_0[6]; /* "cp771" */
	char db_CP771_1[4]; /* "kbl" */
	char db_CP771_nul;

	/* CODEC_CP772 */
	char db_CP772_0[6];  /* "cp772" */
	char db_CP772_1[9];  /* "lst-1284" */
	char db_CP772_2[14]; /* "lst-1284:1993" */
	char db_CP772_3[7];  /* "cp1119" */
	char db_CP772_nul;

	/* CODEC_CP773 */
	char db_CP773_0[6]; /* "cp773" */
	char db_CP773_nul;

	/* CODEC_CP774 */
	char db_CP774_0[6]; /* "cp774" */
	char db_CP774_1[7]; /* "cp1118" */
	char db_CP774_2[8]; /* "ibm1118" */
	char db_CP774_3[9]; /* "lst-1283" */
	char db_CP774_nul;

	/* CODEC_CP775 */
	char db_CP775_0[6];  /* "cp775" */
	char db_CP775_1[7];  /* "ibm775" */
	char db_CP775_2[7];  /* "oem775" */
	char db_CP775_3[14]; /* "cspc775baltic" */
	char db_CP775_nul;

	/* CODEC_CP803 */
	char db_CP803_0[6]; /* "cp803" */
	char db_CP803_1[7]; /* "ibm803" */
	char db_CP803_2[9]; /* "csibm803" */
	char db_CP803_nul;

	/* CODEC_CP806 */
	char db_CP806_0[6]; /* "cp806" */
	char db_CP806_1[7]; /* "ibm806" */
	char db_CP806_nul;

	/* CODEC_CP808 */
	char db_CP808_0[7]; /* "ibm808" */
	char db_CP808_1[6]; /* "cp808" */
	char db_CP808_nul;

	/* CODEC_CP848 */
	char db_CP848_0[6]; /* "cp848" */
	char db_CP848_nul;

	/* CODEC_CP849 */
	char db_CP849_0[6]; /* "cp849" */
	char db_CP849_nul;

	/* CODEC_CP850 */
	char db_CP850_0[7];  /* "ibm850" */
	char db_CP850_1[6];  /* "cp850" */
	char db_CP850_2[4];  /* "850" */
	char db_CP850_3[20]; /* "cspc850multilingual" */
	char db_CP850_4[7];  /* "oem850" */
	char db_CP850_5[12]; /* "osf10020352" */
	char db_CP850_nul;

	/* CODEC_CP851 */
	char db_CP851_0[7]; /* "ibm851" */
	char db_CP851_1[6]; /* "cp851" */
	char db_CP851_2[4]; /* "851" */
	char db_CP851_3[9]; /* "csibm851" */
	char db_CP851_nul;

	/* CODEC_CP852 */
	char db_CP852_0[7];  /* "ibm852" */
	char db_CP852_1[6];  /* "cp852" */
	char db_CP852_2[4];  /* "852" */
	char db_CP852_3[9];  /* "cspcp852" */
	char db_CP852_4[12]; /* "osf10020354" */
	char db_CP852_nul;

	/* CODEC_CP853 */
	char db_CP853_0[6]; /* "cp853" */
	char db_CP853_1[7]; /* "ibm853" */
	char db_CP853_nul;

	/* CODEC_CP855 */
	char db_CP855_0[7];  /* "ibm855" */
	char db_CP855_1[6];  /* "cp855" */
	char db_CP855_2[4];  /* "855" */
	char db_CP855_3[7];  /* "oem855" */
	char db_CP855_4[9];  /* "csibm855" */
	char db_CP855_5[12]; /* "osf10020357" */
	char db_CP855_nul;

	/* CODEC_CP856 */
	char db_CP856_0[6]; /* "cp856" */
	char db_CP856_1[7]; /* "ibm856" */
	char db_CP856_2[4]; /* "856" */
	char db_CP856_3[9]; /* "csibm856" */
	char db_CP856_nul;

	/* CODEC_CP857 */
	char db_CP857_0[7];  /* "ibm857" */
	char db_CP857_1[6];  /* "cp857" */
	char db_CP857_2[4];  /* "857" */
	char db_CP857_3[7];  /* "oem857" */
	char db_CP857_4[9];  /* "csibm857" */
	char db_CP857_5[12]; /* "osf10020359" */
	char db_CP857_nul;

	/* CODEC_CP858 */
	char db_CP858_0[6];  /* "cp858" */
	char db_CP858_1[7];  /* "ibm858" */
	char db_CP858_2[7];  /* "oem858" */
	char db_CP858_3[25]; /* "pc-multilingual-850+euro" */
	char db_CP858_4[9];  /* "ccsid858" */
	char db_CP858_5[9];  /* "csibm858" */
	char db_CP858_6[4];  /* "858" */
	char db_CP858_7[20]; /* "cspc858multilingual" */
	char db_CP858_nul;

	/* CODEC_CP859 */
	char db_CP859_0[6]; /* "cp859" */
	char db_CP859_1[7]; /* "ibm859" */
	char db_CP859_nul;

	/* CODEC_CP860 */
	char db_CP860_0[7]; /* "ibm860" */
	char db_CP860_1[6]; /* "cp860" */
	char db_CP860_2[4]; /* "860" */
	char db_CP860_3[7]; /* "oem860" */
	char db_CP860_4[9]; /* "csibm860" */
	char db_CP860_nul;

	/* CODEC_CP861 */
	char db_CP861_0[7];  /* "ibm861" */
	char db_CP861_1[6];  /* "cp861" */
	char db_CP861_2[4];  /* "861" */
	char db_CP861_3[7];  /* "oem861" */
	char db_CP861_4[6];  /* "cp-is" */
	char db_CP861_5[9];  /* "csibm861" */
	char db_CP861_6[9];  /* "cpibm861" */
	char db_CP861_7[12]; /* "osf1002035d" */
	char db_CP861_nul;

	/* CODEC_CP862 */
	char db_CP862_0[7];  /* "ibm862" */
	char db_CP862_1[6];  /* "cp862" */
	char db_CP862_2[4];  /* "862" */
	char db_CP862_3[7];  /* "oem862" */
	char db_CP862_4[19]; /* "cspc862latinhebrew" */
	char db_CP862_5[12]; /* "osf1002035e" */
	char db_CP862_nul;

	/* CODEC_CP863 */
	char db_CP863_0[7];  /* "ibm863" */
	char db_CP863_1[6];  /* "cp863" */
	char db_CP863_2[4];  /* "863" */
	char db_CP863_3[7];  /* "oem863" */
	char db_CP863_4[9];  /* "csibm863" */
	char db_CP863_5[12]; /* "osf1002035f" */
	char db_CP863_nul;

	/* CODEC_CP864 */
	char db_CP864_0[7];  /* "ibm864" */
	char db_CP864_1[6];  /* "cp864" */
	char db_CP864_2[9];  /* "csibm864" */
	char db_CP864_3[4];  /* "864" */
	char db_CP864_4[12]; /* "osf10020360" */
	char db_CP864_nul;

	/* CODEC_CP865 */
	char db_CP865_0[7]; /* "ibm865" */
	char db_CP865_1[6]; /* "cp865" */
	char db_CP865_2[4]; /* "865" */
	char db_CP865_3[7]; /* "oem865" */
	char db_CP865_4[9]; /* "csibm865" */
	char db_CP865_nul;

	/* CODEC_CP866 */
	char db_CP866_0[6]; /* "cp866" */
	char db_CP866_1[4]; /* "866" */
	char db_CP866_2[7]; /* "ibm866" */
	char db_CP866_3[9]; /* "csibm866" */
	char db_CP866_nul;

	/* CODEC_CP866NAV */
	char db_CP866NAV_0[9];  /* "cp866nav" */
	char db_CP866NAV_1[7];  /* "866nav" */
	char db_CP866NAV_2[10]; /* "ibm866nav" */
	char db_CP866NAV_nul;

	/* CODEC_CP867 */
	char db_CP867_0[7]; /* "ibm867" */
	char db_CP867_1[6]; /* "cp867" */
	char db_CP867_nul;

	/* CODEC_CP868 */
	char db_CP868_0[7];  /* "ibm868" */
	char db_CP868_1[6];  /* "cp868" */
	char db_CP868_2[6];  /* "cp-ar" */
	char db_CP868_3[9];  /* "csibm868" */
	char db_CP868_4[12]; /* "osf10020364" */
	char db_CP868_nul;

	/* CODEC_CP869 */
	char db_CP869_0[7];  /* "ibm869" */
	char db_CP869_1[6];  /* "cp869" */
	char db_CP869_2[4];  /* "869" */
	char db_CP869_3[6];  /* "cp-gr" */
	char db_CP869_4[7];  /* "oem869" */
	char db_CP869_5[9];  /* "csibm869" */
	char db_CP869_6[12]; /* "osf10020365" */
	char db_CP869_nul;

	/* CODEC_CP870 */
	char db_CP870_0[7];  /* "ibm870" */
	char db_CP870_1[6];  /* "cp870" */
	char db_CP870_2[16]; /* "ebcdic-cp-roece" */
	char db_CP870_3[13]; /* "ebcdic-cp-yu" */
	char db_CP870_4[9];  /* "csibm870" */
	char db_CP870_5[12]; /* "osf10020366" */
	char db_CP870_nul;

	/* CODEC_CP871 */
	char db_CP871_0[7];  /* "ibm871" */
	char db_CP871_1[6];  /* "cp871" */
	char db_CP871_2[13]; /* "ebcdic-cp-is" */
	char db_CP871_3[9];  /* "csibm871" */
	char db_CP871_4[12]; /* "osf10020367" */
	char db_CP871_nul;

	/* CODEC_CP872 */
	char db_CP872_0[6]; /* "cp872" */
	char db_CP872_nul;

	/* CODEC_CP874 */
	char db_CP874_0[6];  /* "cp874" */
	char db_CP874_1[7];  /* "ibm874" */
	char db_CP874_2[9];  /* "x-ibm874" */
	char db_CP874_3[4];  /* "874" */
	char db_CP874_4[12]; /* "windows-874" */
	char db_CP874_5[6];  /* "ms874" */
	char db_CP874_6[14]; /* "x-windows-874" */
	char db_CP874_7[13]; /* "cswindows874" */
	char db_CP874_nul;

	/* CODEC_CP875 */
	char db_CP875_0[6];  /* "cp875" */
	char db_CP875_1[7];  /* "ibm875" */
	char db_CP875_2[13]; /* "ebcdic-greek" */
	char db_CP875_3[12]; /* "osf1002036b" */
	char db_CP875_nul;

	/* CODEC_CP880 */
	char db_CP880_0[7];  /* "ibm880" */
	char db_CP880_1[6];  /* "cp880" */
	char db_CP880_2[16]; /* "ebcdic-cyrillic" */
	char db_CP880_3[9];  /* "csibm880" */
	char db_CP880_4[12]; /* "osf10020370" */
	char db_CP880_nul;

	/* CODEC_CP896 */
	char db_CP896_0[6]; /* "cp896" */
	char db_CP896_1[7]; /* "ibm896" */
	char db_CP896_2[7]; /* "cp4992" */
	char db_CP896_nul;

	/* CODEC_CP897 */
	char db_CP897_0[7]; /* "ibm897" */
	char db_CP897_1[6]; /* "cp897" */
	char db_CP897_nul;

	/* CODEC_CP901 */
	char db_CP901_0[6];  /* "cp901" */
	char db_CP901_1[7];  /* "ibm901" */
	char db_CP901_2[9];  /* "csibm901" */
	char db_CP901_3[11]; /* "iso-ir-206" */
	char db_CP901_nul;

	/* CODEC_CP902 */
	char db_CP902_0[6]; /* "cp902" */
	char db_CP902_1[7]; /* "ibm902" */
	char db_CP902_2[9]; /* "csibm902" */
	char db_CP902_nul;

	/* CODEC_CP9030 */
	char db_CP9030_0[7];  /* "cp9030" */
	char db_CP9030_1[8];  /* "ibm9030" */
	char db_CP9030_2[10]; /* "csibm9030" */
	char db_CP9030_nul;

	/* CODEC_CP904 */
	char db_CP904_0[7];  /* "ibm904" */
	char db_CP904_1[6];  /* "cp904" */
	char db_CP904_2[4];  /* "904" */
	char db_CP904_3[10]; /* "csibbm904" */
	char db_CP904_4[9];  /* "csibm904" */
	char db_CP904_5[12]; /* "osf10020388" */
	char db_CP904_nul;

	/* CODEC_CP905 */
	char db_CP905_0[7];  /* "ibm905" */
	char db_CP905_1[6];  /* "cp905" */
	char db_CP905_2[13]; /* "ebcdic-cp-tr" */
	char db_CP905_3[9];  /* "csibm905" */
	char db_CP905_nul;

	/* CODEC_CP9066 */
	char db_CP9066_0[7];  /* "cp9066" */
	char db_CP9066_1[8];  /* "ibm9066" */
	char db_CP9066_2[10]; /* "csibm9066" */
	char db_CP9066_nul;

	/* CODEC_CP918 */
	char db_CP918_0[7];  /* "ibm918" */
	char db_CP918_1[6];  /* "cp918" */
	char db_CP918_2[4];  /* "918" */
	char db_CP918_3[14]; /* "ebcdic-cp-ar2" */
	char db_CP918_4[9];  /* "csibm918" */
	char db_CP918_5[12]; /* "osf10020396" */
	char db_CP918_nul;

	/* CODEC_CP921 */
	char db_CP921_0[6];  /* "cp921" */
	char db_CP921_1[7];  /* "ibm921" */
	char db_CP921_2[9];  /* "csibm921" */
	char db_CP921_3[8];  /* "8859-13" */
	char db_CP921_4[11]; /* "iso8859-13" */
	char db_CP921_5[10]; /* "iso885913" */
	char db_CP921_6[11]; /* "iso-ir-179" */
	char db_CP921_7[12]; /* "csisolatin7" */
	char db_CP921_8[7];  /* "latin7" */
	char db_CP921_9[3];  /* "l7" */
	char db_CP921_10[7];  /* "baltic" */
	char db_CP921_11[8];  /* "cp28603" */
	char db_CP921_12[14]; /* "windows-28603" */
	char db_CP921_13[12]; /* "csiso885913" */
	char db_CP921_nul;

	/* CODEC_CP922 */
	char db_CP922_0[6];  /* "cp922" */
	char db_CP922_1[7];  /* "ibm922" */
	char db_CP922_2[9];  /* "csibm922" */
	char db_CP922_3[14]; /* "estonia-iso-8" */
	char db_CP922_nul;

	/* CODEC_CWI */
	char db_CWI_0[4]; /* "cwi" */
	char db_CWI_1[6]; /* "cwi-2" */
	char db_CWI_2[6]; /* "cp-hu" */
	char db_CWI_nul;

	/* CODEC_C_ESCAPE */
	char db_C_ESCAPE_0[9]; /* "c-escape" */
	char db_C_ESCAPE_nul;

	/* CODEC_C_ESCAPE_ALL */
	char db_C_ESCAPE_ALL_0[13]; /* "c-escape-all" */
	char db_C_ESCAPE_ALL_nul;

	/* CODEC_C_ESCAPE_BYTES */
	char db_C_ESCAPE_BYTES_0[15]; /* "c-escape-bytes" */
	char db_C_ESCAPE_BYTES_nul;

	/* CODEC_C_ESCAPE_BYTES_ALL */
	char db_C_ESCAPE_BYTES_ALL_0[19]; /* "c-escape-all-bytes" */
	char db_C_ESCAPE_BYTES_ALL_1[19]; /* "c-escape-bytes-all" */
	char db_C_ESCAPE_BYTES_ALL_nul;

	/* CODEC_C_ESCAPE_BYTES_CHR */
	char db_C_ESCAPE_BYTES_CHR_0[19]; /* "c-escape-bytes-chr" */
	char db_C_ESCAPE_BYTES_CHR_1[19]; /* "c-escape-chr-bytes" */
	char db_C_ESCAPE_BYTES_CHR_nul;

	/* CODEC_C_ESCAPE_BYTES_INCHR */
	char db_C_ESCAPE_BYTES_INCHR_0[21]; /* "c-escape-inchr-bytes" */
	char db_C_ESCAPE_BYTES_INCHR_1[21]; /* "c-escape-bytes-inchr" */
	char db_C_ESCAPE_BYTES_INCHR_nul;

	/* CODEC_C_ESCAPE_BYTES_INSTR */
	char db_C_ESCAPE_BYTES_INSTR_0[21]; /* "c-escape-instr-bytes" */
	char db_C_ESCAPE_BYTES_INSTR_1[21]; /* "c-escape-bytes-instr" */
	char db_C_ESCAPE_BYTES_INSTR_nul;

	/* CODEC_C_ESCAPE_BYTES_RAW */
	char db_C_ESCAPE_BYTES_RAW_0[19]; /* "c-escape-bytes-raw" */
	char db_C_ESCAPE_BYTES_RAW_1[19]; /* "c-escape-raw-bytes" */
	char db_C_ESCAPE_BYTES_RAW_nul;

	/* CODEC_C_ESCAPE_BYTES_STR */
	char db_C_ESCAPE_BYTES_STR_0[19]; /* "c-escape-bytes-str" */
	char db_C_ESCAPE_BYTES_STR_1[19]; /* "c-escape-str-bytes" */
	char db_C_ESCAPE_BYTES_STR_nul;

	/* CODEC_C_ESCAPE_CHR */
	char db_C_ESCAPE_CHR_0[13]; /* "c-escape-chr" */
	char db_C_ESCAPE_CHR_nul;

	/* CODEC_C_ESCAPE_INCHR */
	char db_C_ESCAPE_INCHR_0[15]; /* "c-escape-inchr" */
	char db_C_ESCAPE_INCHR_nul;

	/* CODEC_C_ESCAPE_INSTR */
	char db_C_ESCAPE_INSTR_0[15]; /* "c-escape-instr" */
	char db_C_ESCAPE_INSTR_nul;

	/* CODEC_C_ESCAPE_RAW */
	char db_C_ESCAPE_RAW_0[13]; /* "c-escape-raw" */
	char db_C_ESCAPE_RAW_nul;

	/* CODEC_C_ESCAPE_STR */
	char db_C_ESCAPE_STR_0[13]; /* "c-escape-str" */
	char db_C_ESCAPE_STR_nul;

	/* CODEC_DIN_66303 */
	char db_DIN_66303_0[10]; /* "din-66303" */
	char db_DIN_66303_1[5];  /* "drv8" */
	char db_DIN_66303_nul;

	/* CODEC_DK_US */
	char db_DK_US_0[6]; /* "dk-us" */
	char db_DK_US_1[7]; /* "csdkus" */
	char db_DK_US_nul;

	/* CODEC_EBCDIC_AT_DE */
	char db_EBCDIC_AT_DE_0[13]; /* "ebcdic-at-de" */
	char db_EBCDIC_AT_DE_1[16]; /* "csibmebcdicatde" */
	char db_EBCDIC_AT_DE_2[13]; /* "csebcdicatde" */
	char db_EBCDIC_AT_DE_3[11]; /* "ebcdicatde" */
	char db_EBCDIC_AT_DE_nul;

	/* CODEC_EBCDIC_AT_DE_A */
	char db_EBCDIC_AT_DE_A_0[15]; /* "ebcdic-at-de-a" */
	char db_EBCDIC_AT_DE_A_1[14]; /* "csebcdicatdea" */
	char db_EBCDIC_AT_DE_A_2[12]; /* "ebcdicatdea" */
	char db_EBCDIC_AT_DE_A_nul;

	/* CODEC_EBCDIC_CA_FR */
	char db_EBCDIC_CA_FR_0[13]; /* "ebcdic-ca-fr" */
	char db_EBCDIC_CA_FR_1[13]; /* "csebcdiccafr" */
	char db_EBCDIC_CA_FR_2[11]; /* "ebcdiccafr" */
	char db_EBCDIC_CA_FR_nul;

	/* CODEC_EBCDIC_CP_DK_NO */
	char db_EBCDIC_CP_DK_NO_0[7];  /* "ibm277" */
	char db_EBCDIC_CP_DK_NO_1[6];  /* "cp277" */
	char db_EBCDIC_CP_DK_NO_2[13]; /* "ebcdic-cp-dk" */
	char db_EBCDIC_CP_DK_NO_3[13]; /* "ebcdic-cp-no" */
	char db_EBCDIC_CP_DK_NO_4[9];  /* "csibm277" */
	char db_EBCDIC_CP_DK_NO_5[12]; /* "osf10020115" */
	char db_EBCDIC_CP_DK_NO_nul;

	/* CODEC_EBCDIC_DK_NO */
	char db_EBCDIC_DK_NO_0[13]; /* "ebcdic-dk-no" */
	char db_EBCDIC_DK_NO_1[13]; /* "csebcdicdkno" */
	char db_EBCDIC_DK_NO_2[11]; /* "ebcdicdkno" */
	char db_EBCDIC_DK_NO_nul;

	/* CODEC_EBCDIC_DK_NO_A */
	char db_EBCDIC_DK_NO_A_0[15]; /* "ebcdic-dk-no-a" */
	char db_EBCDIC_DK_NO_A_1[14]; /* "csebcdicdknoa" */
	char db_EBCDIC_DK_NO_A_2[12]; /* "ebcdicdknoa" */
	char db_EBCDIC_DK_NO_A_nul;

	/* CODEC_EBCDIC_ES */
	char db_EBCDIC_ES_0[10]; /* "ebcdic-es" */
	char db_EBCDIC_ES_1[11]; /* "csebcdices" */
	char db_EBCDIC_ES_2[9];  /* "ebcdices" */
	char db_EBCDIC_ES_nul;

	/* CODEC_EBCDIC_ES_A */
	char db_EBCDIC_ES_A_0[12]; /* "ebcdic-es-a" */
	char db_EBCDIC_ES_A_1[12]; /* "csebcdicesa" */
	char db_EBCDIC_ES_A_2[10]; /* "ebcdicesa" */
	char db_EBCDIC_ES_A_nul;

	/* CODEC_EBCDIC_ES_S */
	char db_EBCDIC_ES_S_0[12]; /* "ebcdic-es-s" */
	char db_EBCDIC_ES_S_1[12]; /* "csebcdicess" */
	char db_EBCDIC_ES_S_nul;

	/* CODEC_EBCDIC_FI_SE */
	char db_EBCDIC_FI_SE_0[13]; /* "ebcdic-fi-se" */
	char db_EBCDIC_FI_SE_1[13]; /* "csebcdicfise" */
	char db_EBCDIC_FI_SE_2[11]; /* "ebcdicfise" */
	char db_EBCDIC_FI_SE_nul;

	/* CODEC_EBCDIC_FI_SE_A */
	char db_EBCDIC_FI_SE_A_0[15]; /* "ebcdic-fi-se-a" */
	char db_EBCDIC_FI_SE_A_1[14]; /* "csebcdicfisea" */
	char db_EBCDIC_FI_SE_A_2[12]; /* "ebcdicfisea" */
	char db_EBCDIC_FI_SE_A_nul;

	/* CODEC_EBCDIC_FR */
	char db_EBCDIC_FR_0[10]; /* "ebcdic-fr" */
	char db_EBCDIC_FR_1[11]; /* "csebcdicfr" */
	char db_EBCDIC_FR_2[9];  /* "ebcdicfr" */
	char db_EBCDIC_FR_nul;

	/* CODEC_EBCDIC_IS_FRISS */
	char db_EBCDIC_IS_FRISS_0[16]; /* "ebcdic-is-friss" */
	char db_EBCDIC_IS_FRISS_1[14]; /* "ebcdicisfriss" */
	char db_EBCDIC_IS_FRISS_nul;

	/* CODEC_EBCDIC_IT */
	char db_EBCDIC_IT_0[10]; /* "ebcdic-it" */
	char db_EBCDIC_IT_1[11]; /* "csebcdicit" */
	char db_EBCDIC_IT_2[9];  /* "ebcdicit" */
	char db_EBCDIC_IT_nul;

	/* CODEC_EBCDIC_PT */
	char db_EBCDIC_PT_0[10]; /* "ebcdic-pt" */
	char db_EBCDIC_PT_1[11]; /* "csebcdicpt" */
	char db_EBCDIC_PT_2[9];  /* "ebcdicpt" */
	char db_EBCDIC_PT_nul;

	/* CODEC_EBCDIC_UK */
	char db_EBCDIC_UK_0[10]; /* "ebcdic-uk" */
	char db_EBCDIC_UK_1[11]; /* "csebcdicuk" */
	char db_EBCDIC_UK_2[9];  /* "ebcdicuk" */
	char db_EBCDIC_UK_nul;

	/* CODEC_EBCDIC_US */
	char db_EBCDIC_US_0[10]; /* "ebcdic-us" */
	char db_EBCDIC_US_1[11]; /* "csebcdicus" */
	char db_EBCDIC_US_2[9];  /* "ebcdicus" */
	char db_EBCDIC_US_nul;

	/* CODEC_EXTENDED_LATIN_8 */
	char db_EXTENDED_LATIN_8_0[17]; /* "extended-latin-8" */
	char db_EXTENDED_LATIN_8_nul;

	/* CODEC_GBCD */
	char db_GBCD_0[5]; /* "gbcd" */
	char db_GBCD_nul;

	/* CODEC_GEORGIAN_ACADEMY */
	char db_GEORGIAN_ACADEMY_0[17]; /* "georgian-academy" */
	char db_GEORGIAN_ACADEMY_nul;

	/* CODEC_GEORGIAN_PS */
	char db_GEORGIAN_PS_0[12]; /* "georgian-ps" */
	char db_GEORGIAN_PS_nul;

	/* CODEC_HEX_LOWER */
	char db_HEX_LOWER_0[10]; /* "hex-lower" */
	char db_HEX_LOWER_nul;

	/* CODEC_HEX_UPPER */
	char db_HEX_UPPER_0[10]; /* "hex-upper" */
	char db_HEX_UPPER_1[4];  /* "hex" */
	char db_HEX_UPPER_nul;

	/* CODEC_HP_GREEK8 */
	char db_HP_GREEK8_0[10]; /* "hp-greek8" */
	char db_HP_GREEK8_1[9];  /* "hpgreek8" */
	char db_HP_GREEK8_2[12]; /* "osf10010004" */
	char db_HP_GREEK8_nul;

	/* CODEC_HP_ROMAN8 */
	char db_HP_ROMAN8_0[10]; /* "hp-roman8" */
	char db_HP_ROMAN8_1[7];  /* "roman8" */
	char db_HP_ROMAN8_2[3];  /* "r8" */
	char db_HP_ROMAN8_3[11]; /* "cshproman8" */
	char db_HP_ROMAN8_4[12]; /* "osf10010001" */
	char db_HP_ROMAN8_5[9];  /* "hproman8" */
	char db_HP_ROMAN8_6[7];  /* "cp1050" */
	char db_HP_ROMAN8_7[8];  /* "ibm1050" */
	char db_HP_ROMAN8_8[11]; /* "hp-roman-8" */
	char db_HP_ROMAN8_9[7];  /* "cp1051" */
	char db_HP_ROMAN8_10[8];  /* "ibm1051" */
	char db_HP_ROMAN8_nul;

	/* CODEC_HP_ROMAN9 */
	char db_HP_ROMAN9_0[10]; /* "hp-roman9" */
	char db_HP_ROMAN9_1[7];  /* "roman9" */
	char db_HP_ROMAN9_2[3];  /* "r9" */
	char db_HP_ROMAN9_3[9];  /* "hproman9" */
	char db_HP_ROMAN9_nul;

	/* CODEC_HP_THAI8 */
	char db_HP_THAI8_0[9]; /* "hp-thai8" */
	char db_HP_THAI8_1[8]; /* "hpthai8" */
	char db_HP_THAI8_2[6]; /* "thai8" */
	char db_HP_THAI8_nul;

	/* CODEC_HP_TURKISH8 */
	char db_HP_TURKISH8_0[12]; /* "hp-turkish8" */
	char db_HP_TURKISH8_1[11]; /* "hpturkish8" */
	char db_HP_TURKISH8_2[9];  /* "turkish8" */
	char db_HP_TURKISH8_3[12]; /* "osf10010006" */
	char db_HP_TURKISH8_nul;

	/* CODEC_IBM1364 */
	char db_IBM1364_0[8];  /* "ibm1364" */
	char db_IBM1364_1[7];  /* "cp1364" */
	char db_IBM1364_2[10]; /* "csibm1364" */
	char db_IBM1364_nul;

	/* CODEC_IBM1371 */
	char db_IBM1371_0[8];  /* "ibm1371" */
	char db_IBM1371_1[7];  /* "cp1371" */
	char db_IBM1371_2[10]; /* "csibm1371" */
	char db_IBM1371_nul;

	/* CODEC_IBM1388 */
	char db_IBM1388_0[8];  /* "ibm1388" */
	char db_IBM1388_1[7];  /* "cp1388" */
	char db_IBM1388_2[10]; /* "csibm1388" */
	char db_IBM1388_nul;

	/* CODEC_IBM1390 */
	char db_IBM1390_0[8];  /* "ibm1390" */
	char db_IBM1390_1[7];  /* "cp1390" */
	char db_IBM1390_2[10]; /* "csibm1390" */
	char db_IBM1390_nul;

	/* CODEC_IBM1399 */
	char db_IBM1399_0[8];  /* "ibm1399" */
	char db_IBM1399_1[7];  /* "cp1399" */
	char db_IBM1399_2[10]; /* "csibm1399" */
	char db_IBM1399_nul;

	/* CODEC_IBM1401 */
	char db_IBM1401_0[8]; /* "ibm1401" */
	char db_IBM1401_nul;

	/* CODEC_IBM256 */
	char db_IBM256_0[7];  /* "ibm256" */
	char db_IBM256_1[12]; /* "ebcdic-int1" */
	char db_IBM256_nul;

	/* CODEC_IBM704 */
	char db_IBM704_0[7]; /* "ibm704" */
	char db_IBM704_nul;

	/* CODEC_IBM7090 */
	char db_IBM7090_0[8]; /* "ibm7090" */
	char db_IBM7090_1[8]; /* "ibm7094" */
	char db_IBM7090_nul;

	/* CODEC_IBM930 */
	char db_IBM930_0[7]; /* "ibm930" */
	char db_IBM930_1[6]; /* "cp930" */
	char db_IBM930_2[9]; /* "csibm930" */
	char db_IBM930_3[9]; /* "x-ibm930" */
	char db_IBM930_4[4]; /* "930" */
	char db_IBM930_nul;

	/* CODEC_IBM933 */
	char db_IBM933_0[7]; /* "ibm933" */
	char db_IBM933_1[6]; /* "cp933" */
	char db_IBM933_2[9]; /* "csibm933" */
	char db_IBM933_nul;

	/* CODEC_IBM935 */
	char db_IBM935_0[7]; /* "ibm935" */
	char db_IBM935_1[6]; /* "cp935" */
	char db_IBM935_2[9]; /* "csibm935" */
	char db_IBM935_nul;

	/* CODEC_IBM937 */
	char db_IBM937_0[7]; /* "ibm937" */
	char db_IBM937_1[6]; /* "cp937" */
	char db_IBM937_2[9]; /* "csibm937" */
	char db_IBM937_nul;

	/* CODEC_IBM939 */
	char db_IBM939_0[7]; /* "ibm939" */
	char db_IBM939_1[6]; /* "cp939" */
	char db_IBM939_2[9]; /* "csibm939" */
	char db_IBM939_3[9]; /* "x-ibm939" */
	char db_IBM939_4[4]; /* "939" */
	char db_IBM939_nul;

	/* CODEC_ISIRI3342 */
	char db_ISIRI3342_0[10]; /* "isiri3342" */
	char db_ISIRI3342_1[11]; /* "isiri-3342" */
	char db_ISIRI3342_nul;

	/* CODEC_ISO5426 */
	char db_ISO5426_0[8]; /* "iso5426" */
	char db_ISO5426_nul;

	/* CODEC_ISO5426_2 */
	char db_ISO5426_2_0[10]; /* "iso5426-2" */
	char db_ISO5426_2_nul;

	/* CODEC_ISO6438 */
	char db_ISO6438_0[8]; /* "iso6438" */
	char db_ISO6438_nul;

	/* CODEC_ISO646_BASIC */
	char db_ISO646_BASIC_0[18]; /* "iso646.basic:1983" */
	char db_ISO646_BASIC_1[4];  /* "ref" */
	char db_ISO646_BASIC_nul;

	/* CODEC_ISO646_CA */
	char db_ISO646_CA_0[18]; /* "csa-z243.4-1985-1" */
	char db_ISO646_CA_1[11]; /* "iso-ir-121" */
	char db_ISO646_CA_2[10]; /* "iso646-ca" */
	char db_ISO646_CA_3[7];  /* "csa7-1" */
	char db_ISO646_CA_4[3];  /* "ca" */
	char db_ISO646_CA_5[18]; /* "csiso121canadian1" */
	char db_ISO646_CA_6[16]; /* "csa-z243.419851" */
	char db_ISO646_CA_7[7];  /* "cp1020" */
	char db_ISO646_CA_8[6];  /* "csa71" */
	char db_ISO646_CA_nul;

	/* CODEC_ISO646_CA2 */
	char db_ISO646_CA2_0[18]; /* "csa-z243.4-1985-2" */
	char db_ISO646_CA2_1[11]; /* "iso-ir-122" */
	char db_ISO646_CA2_2[11]; /* "iso646-ca2" */
	char db_ISO646_CA2_3[7];  /* "csa7-2" */
	char db_ISO646_CA2_4[18]; /* "csiso122canadian2" */
	char db_ISO646_CA2_5[16]; /* "csa-z243.419852" */
	char db_ISO646_CA2_6[6];  /* "csa72" */
	char db_ISO646_CA2_nul;

	/* CODEC_ISO646_CN */
	char db_ISO646_CN_0[11]; /* "gb-1988-80" */
	char db_ISO646_CN_1[10]; /* "iso-ir-57" */
	char db_ISO646_CN_2[3];  /* "cn" */
	char db_ISO646_CN_3[10]; /* "iso646-cn" */
	char db_ISO646_CN_4[14]; /* "csiso57gb1988" */
	char db_ISO646_CN_5[14]; /* "csiso58gb1988" */
	char db_ISO646_CN_6[10]; /* "gb-198880" */
	char db_ISO646_CN_nul;

	/* CODEC_ISO646_CU */
	char db_ISO646_CU_0[13]; /* "nc-nc0-10:81" */
	char db_ISO646_CU_1[5];  /* "cuba" */
	char db_ISO646_CU_2[11]; /* "iso-ir-151" */
	char db_ISO646_CU_3[10]; /* "iso646-cu" */
	char db_ISO646_CU_4[10]; /* "nc-nc0-10" */
	char db_ISO646_CU_5[13]; /* "csiso151cuba" */
	char db_ISO646_CU_6[8];  /* "nc-nc10" */
	char db_ISO646_CU_nul;

	/* CODEC_ISO646_DE */
	char db_ISO646_DE_0[10]; /* "din-66003" */
	char db_ISO646_DE_1[10]; /* "iso-ir-21" */
	char db_ISO646_DE_2[3];  /* "de" */
	char db_ISO646_DE_3[10]; /* "iso646-de" */
	char db_ISO646_DE_4[8];  /* "ibm1011" */
	char db_ISO646_DE_5[9];  /* "ms-10206" */
	char db_ISO646_DE_6[14]; /* "csiso21german" */
	char db_ISO646_DE_7[7];  /* "german" */
	char db_ISO646_DE_8[6];  /* "d7dec" */
	char db_ISO646_DE_9[7];  /* "cp1011" */
	char db_ISO646_DE_10[8];  /* "cp20106" */
	char db_ISO646_DE_11[14]; /* "windows-20106" */
	char db_ISO646_DE_nul;

	/* CODEC_ISO646_DK */
	char db_ISO646_DK_0[8];  /* "ds-2089" */
	char db_ISO646_DK_1[7];  /* "ds2089" */
	char db_ISO646_DK_2[10]; /* "iso646-dk" */
	char db_ISO646_DK_3[3];  /* "dk" */
	char db_ISO646_DK_4[15]; /* "csiso646danish" */
	char db_ISO646_DK_5[7];  /* "cp1017" */
	char db_ISO646_DK_6[8];  /* "ibm1017" */
	char db_ISO646_DK_nul;

	/* CODEC_ISO646_DK_NO_ALT_NRCS */
	char db_ISO646_DK_NO_ALT_NRCS_0[7]; /* "cp1107" */
	char db_ISO646_DK_NO_ALT_NRCS_1[8]; /* "ibm1107" */
	char db_ISO646_DK_NO_ALT_NRCS_nul;

	/* CODEC_ISO646_DK_NO_NRCS */
	char db_ISO646_DK_NO_NRCS_0[7]; /* "cp1105" */
	char db_ISO646_DK_NO_NRCS_1[8]; /* "ibm1105" */
	char db_ISO646_DK_NO_NRCS_nul;

	/* CODEC_ISO646_ES */
	char db_ISO646_ES_0[3];  /* "es" */
	char db_ISO646_ES_1[10]; /* "iso-ir-17" */
	char db_ISO646_ES_2[10]; /* "iso646-es" */
	char db_ISO646_ES_3[15]; /* "csiso17spanish" */
	char db_ISO646_ES_4[7];  /* "cp1023" */
	char db_ISO646_ES_5[6];  /* "e7dec" */
	char db_ISO646_ES_nul;

	/* CODEC_ISO646_ES2 */
	char db_ISO646_ES2_0[4];  /* "es2" */
	char db_ISO646_ES2_1[10]; /* "iso-ir-85" */
	char db_ISO646_ES2_2[11]; /* "iso646-es2" */
	char db_ISO646_ES2_3[16]; /* "csiso85spanish2" */
	char db_ISO646_ES2_4[7];  /* "cp1014" */
	char db_ISO646_ES2_5[8];  /* "ibm1014" */
	char db_ISO646_ES2_nul;

	/* CODEC_ISO646_FI_NRCS */
	char db_ISO646_FI_NRCS_0[7]; /* "cp1103" */
	char db_ISO646_FI_NRCS_1[8]; /* "ibm1103" */
	char db_ISO646_FI_NRCS_nul;

	/* CODEC_ISO646_FR */
	char db_ISO646_FR_0[11]; /* "nf-z-62-10" */
	char db_ISO646_FR_1[10]; /* "iso-ir-69" */
	char db_ISO646_FR_2[10]; /* "iso646-fr" */
	char db_ISO646_FR_3[3];  /* "fr" */
	char db_ISO646_FR_4[16]; /* "nf-z-62-10-1983" */
	char db_ISO646_FR_5[18]; /* "nf-z-62-10-(1983)" */
	char db_ISO646_FR_6[14]; /* "csiso69french" */
	char db_ISO646_FR_7[11]; /* "nf-z-62010" */
	char db_ISO646_FR_8[7];  /* "cp1010" */
	char db_ISO646_FR_9[8];  /* "ibm1010" */
	char db_ISO646_FR_nul;

	/* CODEC_ISO646_FR1 */
	char db_ISO646_FR1_0[18]; /* "nf-z-62-10-(1973)" */
	char db_ISO646_FR1_1[10]; /* "iso-ir-25" */
	char db_ISO646_FR1_2[11]; /* "iso646-fr1" */
	char db_ISO646_FR1_3[16]; /* "nf-z-62-10-1973" */
	char db_ISO646_FR1_4[14]; /* "csiso25french" */
	char db_ISO646_FR1_5[16]; /* "nf-z-62010-1973" */
	char db_ISO646_FR1_6[7];  /* "cp1104" */
	char db_ISO646_FR1_7[6];  /* "f7dec" */
	char db_ISO646_FR1_nul;

	/* CODEC_ISO646_GB */
	char db_ISO646_GB_0[8];  /* "bs-4730" */
	char db_ISO646_GB_1[9];  /* "iso-ir-4" */
	char db_ISO646_GB_2[10]; /* "iso646-gb" */
	char db_ISO646_GB_3[3];  /* "gb" */
	char db_ISO646_GB_4[3];  /* "uk" */
	char db_ISO646_GB_5[20]; /* "csiso4unitedkingdom" */
	char db_ISO646_GB_6[7];  /* "cp1013" */
	char db_ISO646_GB_7[8];  /* "ibm1013" */
	char db_ISO646_GB_nul;

	/* CODEC_ISO646_GB_NRCS */
	char db_ISO646_GB_NRCS_0[7]; /* "cp1101" */
	char db_ISO646_GB_NRCS_1[8]; /* "ibm1101" */
	char db_ISO646_GB_NRCS_nul;

	/* CODEC_ISO646_HU */
	char db_ISO646_HU_0[11]; /* "msz-7795.3" */
	char db_ISO646_HU_1[10]; /* "iso-ir-86" */
	char db_ISO646_HU_2[10]; /* "iso646-hu" */
	char db_ISO646_HU_3[3];  /* "hu" */
	char db_ISO646_HU_4[17]; /* "csiso86hungarian" */
	char db_ISO646_HU_nul;

	/* CODEC_ISO646_IE */
	char db_ISO646_IE_0[10]; /* "iso646-ie" */
	char db_ISO646_IE_1[11]; /* "iso-ir-207" */
	char db_ISO646_IE_nul;

	/* CODEC_ISO646_INIS_SUBSET */
	char db_ISO646_INIS_SUBSET_0[5];  /* "inis" */
	char db_ISO646_INIS_SUBSET_1[10]; /* "iso-ir-49" */
	char db_ISO646_INIS_SUBSET_2[12]; /* "csiso49inis" */
	char db_ISO646_INIS_SUBSET_nul;

	/* CODEC_ISO646_INV */
	char db_ISO646_INV_0[11]; /* "iso-ir-170" */
	char db_ISO646_INV_1[10]; /* "invariant" */
	char db_ISO646_INV_nul;

	/* CODEC_ISO646_IRV_1983 */
	char db_ISO646_IRV_1983_0[7];  /* "cp1009" */
	char db_ISO646_IRV_1983_1[8];  /* "ibm1009" */
	char db_ISO646_IRV_1983_2[8];  /* "cp20105" */
	char db_ISO646_IRV_1983_3[14]; /* "windows-20105" */
	char db_ISO646_IRV_1983_4[8];  /* "koi7-n0" */
	char db_ISO646_IRV_1983_nul;

	/* CODEC_ISO646_IS */
	char db_ISO646_IS_0[10]; /* "iso646-is" */
	char db_ISO646_IS_nul;

	/* CODEC_ISO646_IT */
	char db_ISO646_IT_0[3];  /* "it" */
	char db_ISO646_IT_1[10]; /* "iso-ir-15" */
	char db_ISO646_IT_2[10]; /* "iso646-it" */
	char db_ISO646_IT_3[15]; /* "csiso15italian" */
	char db_ISO646_IT_4[7];  /* "cp1012" */
	char db_ISO646_IT_5[8];  /* "ibm1012" */
	char db_ISO646_IT_6[6];  /* "i7dec" */
	char db_ISO646_IT_nul;

	/* CODEC_ISO646_JP */
	char db_ISO646_JP_0[18]; /* "jis-c6220-1969-ro" */
	char db_ISO646_JP_1[10]; /* "iso-ir-14" */
	char db_ISO646_JP_2[3];  /* "jp" */
	char db_ISO646_JP_3[10]; /* "iso646-jp" */
	char db_ISO646_JP_4[18]; /* "csiso14jisc6220ro" */
	char db_ISO646_JP_5[16]; /* "jis-c62201969ro" */
	char db_ISO646_JP_6[6];  /* "cp895" */
	char db_ISO646_JP_7[7];  /* "ibm895" */
	char db_ISO646_JP_nul;

	/* CODEC_ISO646_JP_OCR_B */
	char db_ISO646_JP_OCR_B_0[17]; /* "jis-c6229-1984-b" */
	char db_ISO646_JP_OCR_B_1[10]; /* "iso-ir-92" */
	char db_ISO646_JP_OCR_B_2[16]; /* "iso646-jp-ocr-b" */
	char db_ISO646_JP_OCR_B_3[9];  /* "jp-ocr-b" */
	char db_ISO646_JP_OCR_B_4[21]; /* "csiso92jisc62991984b" */
	char db_ISO646_JP_OCR_B_5[15]; /* "jis-c62291984b" */
	char db_ISO646_JP_OCR_B_nul;

	/* CODEC_ISO646_KR */
	char db_ISO646_KR_0[8];  /* "ksc5636" */
	char db_ISO646_KR_1[10]; /* "iso646-kr" */
	char db_ISO646_KR_2[10]; /* "csksc5636" */
	char db_ISO646_KR_3[10]; /* "ks-x-1003" */
	char db_ISO646_KR_4[13]; /* "ksc5636-1989" */
	char db_ISO646_KR_nul;

	/* CODEC_ISO646_LATIN_GR_MIXED */
	char db_ISO646_LATIN_GR_MIXED_0[14]; /* "latin-greek-1" */
	char db_ISO646_LATIN_GR_MIXED_1[12]; /* "latingreek1" */
	char db_ISO646_LATIN_GR_MIXED_2[10]; /* "iso-ir-27" */
	char db_ISO646_LATIN_GR_MIXED_3[19]; /* "csiso27latingreek1" */
	char db_ISO646_LATIN_GR_MIXED_nul;

	/* CODEC_ISO646_MT */
	char db_ISO646_MT_0[10]; /* "iso646-mt" */
	char db_ISO646_MT_nul;

	/* CODEC_ISO646_NATS_DANO */
	char db_ISO646_NATS_DANO_0[10]; /* "nats-dano" */
	char db_ISO646_NATS_DANO_1[11]; /* "iso-ir-9-1" */
	char db_ISO646_NATS_DANO_2[7];  /* "cp1016" */
	char db_ISO646_NATS_DANO_3[8];  /* "ibm1016" */
	char db_ISO646_NATS_DANO_4[11]; /* "csnatsdano" */
	char db_ISO646_NATS_DANO_5[9];  /* "natsdano" */
	char db_ISO646_NATS_DANO_nul;

	/* CODEC_ISO646_NL */
	char db_ISO646_NL_0[10]; /* "iso646-nl" */
	char db_ISO646_NL_1[7];  /* "cp1019" */
	char db_ISO646_NL_2[8];  /* "ibm1019" */
	char db_ISO646_NL_nul;

	/* CODEC_ISO646_NL_NRCS */
	char db_ISO646_NL_NRCS_0[7]; /* "cp1102" */
	char db_ISO646_NL_NRCS_1[8]; /* "ibm1102" */
	char db_ISO646_NL_NRCS_nul;

	/* CODEC_ISO646_NO */
	char db_ISO646_NO_0[10]; /* "ns-4551-1" */
	char db_ISO646_NO_1[10]; /* "iso-ir-60" */
	char db_ISO646_NO_2[10]; /* "iso646-no" */
	char db_ISO646_NO_3[3];  /* "no" */
	char db_ISO646_NO_4[23]; /* "csiso60danishnorwegian" */
	char db_ISO646_NO_5[18]; /* "csiso60norwegian1" */
	char db_ISO646_NO_6[9];  /* "ns-45511" */
	char db_ISO646_NO_nul;

	/* CODEC_ISO646_NO2 */
	char db_ISO646_NO2_0[10]; /* "ns-4551-2" */
	char db_ISO646_NO2_1[11]; /* "iso646-no2" */
	char db_ISO646_NO2_2[10]; /* "iso-ir-61" */
	char db_ISO646_NO2_3[4];  /* "no2" */
	char db_ISO646_NO2_4[18]; /* "csiso61norwegian2" */
	char db_ISO646_NO2_5[9];  /* "ns-45512" */
	char db_ISO646_NO2_nul;

	/* CODEC_ISO646_PL */
	char db_ISO646_PL_0[13]; /* "bn-74/3101-1" */
	char db_ISO646_PL_nul;

	/* CODEC_ISO646_PT */
	char db_ISO646_PT_0[3];  /* "pt" */
	char db_ISO646_PT_1[10]; /* "iso-ir-16" */
	char db_ISO646_PT_2[10]; /* "iso646-pt" */
	char db_ISO646_PT_3[17]; /* "csiso16portugese" */
	char db_ISO646_PT_4[18]; /* "csiso16portuguese" */
	char db_ISO646_PT_nul;

	/* CODEC_ISO646_PT2 */
	char db_ISO646_PT2_0[4];  /* "pt2" */
	char db_ISO646_PT2_1[10]; /* "iso-ir-84" */
	char db_ISO646_PT2_2[11]; /* "iso646-pt2" */
	char db_ISO646_PT2_3[19]; /* "csiso84portuguese2" */
	char db_ISO646_PT2_4[7];  /* "cp1015" */
	char db_ISO646_PT2_5[8];  /* "ibm1015" */
	char db_ISO646_PT2_nul;

	/* CODEC_ISO646_SE */
	char db_ISO646_SE_0[13]; /* "sen-850200-b" */
	char db_ISO646_SE_1[10]; /* "iso-ir-10" */
	char db_ISO646_SE_2[3];  /* "fi" */
	char db_ISO646_SE_3[10]; /* "iso646-fi" */
	char db_ISO646_SE_4[10]; /* "iso646-se" */
	char db_ISO646_SE_5[3];  /* "se" */
	char db_ISO646_SE_6[15]; /* "csiso10swedish" */
	char db_ISO646_SE_7[9];  /* "ss636127" */
	char db_ISO646_SE_8[7];  /* "cp1018" */
	char db_ISO646_SE_9[8];  /* "ibm1018" */
	char db_ISO646_SE_nul;

	/* CODEC_ISO646_SE2 */
	char db_ISO646_SE2_0[13]; /* "sen-850200-c" */
	char db_ISO646_SE2_1[10]; /* "iso-ir-11" */
	char db_ISO646_SE2_2[11]; /* "iso646-se2" */
	char db_ISO646_SE2_3[4];  /* "se2" */
	char db_ISO646_SE2_4[23]; /* "csiso11swedishfornames" */
	char db_ISO646_SE2_nul;

	/* CODEC_ISO646_SEFI_NATS */
	char db_ISO646_SEFI_NATS_0[9]; /* "iso-ir-8" */
	char db_ISO646_SEFI_NATS_nul;

	/* CODEC_ISO646_SE_NRCS */
	char db_ISO646_SE_NRCS_0[7]; /* "cp1106" */
	char db_ISO646_SE_NRCS_1[8]; /* "ibm1106" */
	char db_ISO646_SE_NRCS_nul;

	/* CODEC_ISO646_SWI_NRCS */
	char db_ISO646_SWI_NRCS_0[7]; /* "cp1021" */
	char db_ISO646_SWI_NRCS_1[8]; /* "ibm1021" */
	char db_ISO646_SWI_NRCS_2[7]; /* "ch7dec" */
	char db_ISO646_SWI_NRCS_nul;

	/* CODEC_ISO646_T_61 */
	char db_ISO646_T_61_0[10]; /* "t.61-7bit" */
	char db_ISO646_T_61_1[11]; /* "iso-ir-102" */
	char db_ISO646_T_61_2[16]; /* "csiso102t617bit" */
	char db_ISO646_T_61_nul;

	/* CODEC_ISO646_VIEWDATA */
	char db_ISO646_VIEWDATA_0[12]; /* "bs-viewdata" */
	char db_ISO646_VIEWDATA_1[10]; /* "iso-ir-47" */
	char db_ISO646_VIEWDATA_2[18]; /* "csiso47bsviewdata" */
	char db_ISO646_VIEWDATA_nul;

	/* CODEC_ISO646_YU */
	char db_ISO646_YU_0[11]; /* "jus-i.b1.2" */
	char db_ISO646_YU_1[11]; /* "iso-ir-141" */
	char db_ISO646_YU_2[10]; /* "iso646-yu" */
	char db_ISO646_YU_3[3];  /* "js" */
	char db_ISO646_YU_4[3];  /* "yu" */
	char db_ISO646_YU_5[18]; /* "csiso141jusib1002" */
	char db_ISO646_YU_nul;

	/* CODEC_ISO_5427 */
	char db_ISO_5427_0[8];  /* "iso5427" */
	char db_ISO_5427_1[10]; /* "iso-ir-37" */
	char db_ISO_5427_2[5];  /* "koi7" */
	char db_ISO_5427_3[8];  /* "koi7-n1" */
	char db_ISO_5427_4[5];  /* "koi0" */
	char db_ISO_5427_5[18]; /* "csiso5427cyrillic" */
	char db_ISO_5427_nul;

	/* CODEC_ISO_6937_2 */
	char db_ISO_6937_2_0[10]; /* "iso6937-2" */
	char db_ISO_6937_2_1[9];  /* "iso69372" */
	char db_ISO_6937_2_2[15]; /* "iso6937-2:1983" */
	char db_ISO_6937_2_3[10]; /* "iso-ir-90" */
	char db_ISO_6937_2_4[8];  /* "csiso90" */
	char db_ISO_6937_2_nul;

	/* CODEC_ISO_8859_1 */
	char db_ISO_8859_1_0[15]; /* "iso8859-1:1987" */
	char db_ISO_8859_1_1[11]; /* "iso-ir-100" */
	char db_ISO_8859_1_2[10]; /* "iso8859-1" */
	char db_ISO_8859_1_3[7];  /* "latin1" */
	char db_ISO_8859_1_4[3];  /* "l1" */
	char db_ISO_8859_1_5[7];  /* "ibm819" */
	char db_ISO_8859_1_6[6];  /* "cp819" */
	char db_ISO_8859_1_7[9];  /* "iso88591" */
	char db_ISO_8859_1_8[12]; /* "csisolatin1" */
	char db_ISO_8859_1_9[8];  /* "cp28591" */
	char db_ISO_8859_1_10[14]; /* "windows-28591" */
	char db_ISO_8859_1_11[13]; /* "we8iso8859p1" */
	char db_ISO_8859_1_12[8];  /* "cp38591" */
	char db_ISO_8859_1_13[14]; /* "windows-38591" */
	char db_ISO_8859_1_14[12]; /* "iso8859-1-i" */
	char db_ISO_8859_1_15[7];  /* "8859-1" */
	char db_ISO_8859_1_16[9];  /* "osf10001" */
	char db_ISO_8859_1_nul;

	/* CODEC_ISO_8859_10 */
	char db_ISO_8859_10_0[7];  /* "latin6" */
	char db_ISO_8859_10_1[11]; /* "iso-ir-157" */
	char db_ISO_8859_10_2[3];  /* "l6" */
	char db_ISO_8859_10_3[8];  /* "8859-10" */
	char db_ISO_8859_10_4[11]; /* "iso8859-10" */
	char db_ISO_8859_10_5[16]; /* "iso8859-10:1992" */
	char db_ISO_8859_10_6[10]; /* "iso885910" */
	char db_ISO_8859_10_7[12]; /* "csisolatin6" */
	char db_ISO_8859_10_8[7];  /* "ibm919" */
	char db_ISO_8859_10_9[6];  /* "cp919" */
	char db_ISO_8859_10_10[8];  /* "cp28600" */
	char db_ISO_8859_10_11[14]; /* "windows-28600" */
	char db_ISO_8859_10_12[9];  /* "osf1000a" */
	char db_ISO_8859_10_nul;

	/* CODEC_ISO_8859_11 */
	char db_ISO_8859_11_0[11]; /* "iso8859-11" */
	char db_ISO_8859_11_1[10]; /* "iso885911" */
	char db_ISO_8859_11_2[8];  /* "cp28601" */
	char db_ISO_8859_11_3[14]; /* "windows-28601" */
	char db_ISO_8859_11_4[11]; /* "iso-ir-166" */
	char db_ISO_8859_11_5[8];  /* "tis-620" */
	char db_ISO_8859_11_6[9];  /* "cstis620" */
	char db_ISO_8859_11_7[7];  /* "tis620" */
	char db_ISO_8859_11_8[9];  /* "tis620-0" */
	char db_ISO_8859_11_9[14]; /* "tis620.2529-1" */
	char db_ISO_8859_11_10[14]; /* "tis620.2533-0" */
	char db_ISO_8859_11_11[14]; /* "x-iso-8859-11" */
	char db_ISO_8859_11_12[12]; /* "tis620.2533" */
	char db_ISO_8859_11_nul;

	/* CODEC_ISO_8859_14 */
	char db_ISO_8859_14_0[11]; /* "iso8859-14" */
	char db_ISO_8859_14_1[16]; /* "iso8859-14:1998" */
	char db_ISO_8859_14_2[10]; /* "iso885914" */
	char db_ISO_8859_14_3[11]; /* "iso-ir-199" */
	char db_ISO_8859_14_4[11]; /* "iso-celtic" */
	char db_ISO_8859_14_5[7];  /* "latin8" */
	char db_ISO_8859_14_6[3];  /* "l8" */
	char db_ISO_8859_14_7[8];  /* "cp28604" */
	char db_ISO_8859_14_8[14]; /* "windows-28604" */
	char db_ISO_8859_14_9[12]; /* "csiso885914" */
	char db_ISO_8859_14_10[8];  /* "8859-14" */
	char db_ISO_8859_14_11[10]; /* "isoceltic" */
	char db_ISO_8859_14_nul;

	/* CODEC_ISO_8859_15 */
	char db_ISO_8859_15_0[11]; /* "iso8859-15" */
	char db_ISO_8859_15_1[16]; /* "iso8859-15:1998" */
	char db_ISO_8859_15_2[10]; /* "iso885915" */
	char db_ISO_8859_15_3[11]; /* "iso-ir-203" */
	char db_ISO_8859_15_4[7];  /* "latin9" */
	char db_ISO_8859_15_5[7];  /* "latin0" */
	char db_ISO_8859_15_6[7];  /* "ibm923" */
	char db_ISO_8859_15_7[6];  /* "cp923" */
	char db_ISO_8859_15_8[8];  /* "cp28605" */
	char db_ISO_8859_15_9[14]; /* "windows-28605" */
	char db_ISO_8859_15_10[12]; /* "csiso885915" */
	char db_ISO_8859_15_11[3];  /* "l9" */
	char db_ISO_8859_15_12[12]; /* "csisolatin9" */
	char db_ISO_8859_15_13[16]; /* "iso8859-15-fdis" */
	char db_ISO_8859_15_nul;

	/* CODEC_ISO_8859_16 */
	char db_ISO_8859_16_0[11]; /* "iso8859-16" */
	char db_ISO_8859_16_1[16]; /* "iso8859-16:2001" */
	char db_ISO_8859_16_2[10]; /* "iso885916" */
	char db_ISO_8859_16_3[11]; /* "iso-ir-226" */
	char db_ISO_8859_16_4[8];  /* "latin10" */
	char db_ISO_8859_16_5[4];  /* "l10" */
	char db_ISO_8859_16_6[9];  /* "sr-14111" */
	char db_ISO_8859_16_7[8];  /* "cp28606" */
	char db_ISO_8859_16_8[14]; /* "windows-28606" */
	char db_ISO_8859_16_9[12]; /* "csiso885916" */
	char db_ISO_8859_16_10[8];  /* "8859-16" */
	char db_ISO_8859_16_nul;

	/* CODEC_ISO_8859_2 */
	char db_ISO_8859_2_0[15]; /* "iso8859-2:1987" */
	char db_ISO_8859_2_1[11]; /* "iso-ir-101" */
	char db_ISO_8859_2_2[10]; /* "iso8859-2" */
	char db_ISO_8859_2_3[7];  /* "latin2" */
	char db_ISO_8859_2_4[3];  /* "l2" */
	char db_ISO_8859_2_5[9];  /* "iso88592" */
	char db_ISO_8859_2_6[12]; /* "csisolatin2" */
	char db_ISO_8859_2_7[8];  /* "ibm1111" */
	char db_ISO_8859_2_8[7];  /* "cp1111" */
	char db_ISO_8859_2_9[8];  /* "cp28592" */
	char db_ISO_8859_2_10[14]; /* "windows-28592" */
	char db_ISO_8859_2_11[7];  /* "8859-2" */
	char db_ISO_8859_2_12[9];  /* "osf10002" */
	char db_ISO_8859_2_13[6];  /* "cp912" */
	char db_ISO_8859_2_14[7];  /* "ibm912" */
	char db_ISO_8859_2_nul;

	/* CODEC_ISO_8859_3 */
	char db_ISO_8859_3_0[15]; /* "iso8859-3:1988" */
	char db_ISO_8859_3_1[11]; /* "iso-ir-109" */
	char db_ISO_8859_3_2[10]; /* "iso8859-3" */
	char db_ISO_8859_3_3[7];  /* "latin3" */
	char db_ISO_8859_3_4[3];  /* "l3" */
	char db_ISO_8859_3_5[9];  /* "iso88593" */
	char db_ISO_8859_3_6[12]; /* "csisolatin3" */
	char db_ISO_8859_3_7[7];  /* "ibm913" */
	char db_ISO_8859_3_8[6];  /* "cp913" */
	char db_ISO_8859_3_9[8];  /* "cp28593" */
	char db_ISO_8859_3_10[14]; /* "windows-28593" */
	char db_ISO_8859_3_11[7];  /* "8859-3" */
	char db_ISO_8859_3_12[9];  /* "osf10003" */
	char db_ISO_8859_3_nul;

	/* CODEC_ISO_8859_4 */
	char db_ISO_8859_4_0[15]; /* "iso8859-4:1988" */
	char db_ISO_8859_4_1[11]; /* "iso-ir-110" */
	char db_ISO_8859_4_2[10]; /* "iso8859-4" */
	char db_ISO_8859_4_3[7];  /* "latin4" */
	char db_ISO_8859_4_4[3];  /* "l4" */
	char db_ISO_8859_4_5[9];  /* "iso88594" */
	char db_ISO_8859_4_6[12]; /* "csisolatin4" */
	char db_ISO_8859_4_7[7];  /* "ibm914" */
	char db_ISO_8859_4_8[6];  /* "cp914" */
	char db_ISO_8859_4_9[8];  /* "cp28594" */
	char db_ISO_8859_4_10[14]; /* "windows-28594" */
	char db_ISO_8859_4_11[7];  /* "8859-4" */
	char db_ISO_8859_4_12[9];  /* "osf10004" */
	char db_ISO_8859_4_nul;

	/* CODEC_ISO_8859_5 */
	char db_ISO_8859_5_0[15]; /* "iso8859-5:1988" */
	char db_ISO_8859_5_1[11]; /* "iso-ir-144" */
	char db_ISO_8859_5_2[10]; /* "iso8859-5" */
	char db_ISO_8859_5_3[9];  /* "cyrillic" */
	char db_ISO_8859_5_4[9];  /* "iso88595" */
	char db_ISO_8859_5_5[19]; /* "csisolatincyrillic" */
	char db_ISO_8859_5_6[8];  /* "cp28595" */
	char db_ISO_8859_5_7[14]; /* "windows-28595" */
	char db_ISO_8859_5_8[7];  /* "8859-5" */
	char db_ISO_8859_5_9[9];  /* "osf10005" */
	char db_ISO_8859_5_10[6];  /* "cp915" */
	char db_ISO_8859_5_11[7];  /* "ibm915" */
	char db_ISO_8859_5_nul;

	/* CODEC_ISO_8859_6 */
	char db_ISO_8859_6_0[15]; /* "iso8859-6:1987" */
	char db_ISO_8859_6_1[11]; /* "iso-ir-127" */
	char db_ISO_8859_6_2[10]; /* "iso8859-6" */
	char db_ISO_8859_6_3[9];  /* "ecma-114" */
	char db_ISO_8859_6_4[9];  /* "asmo-708" */
	char db_ISO_8859_6_5[7];  /* "arabic" */
	char db_ISO_8859_6_6[9];  /* "iso88596" */
	char db_ISO_8859_6_7[17]; /* "csisolatinarabic" */
	char db_ISO_8859_6_8[8];  /* "ibm1089" */
	char db_ISO_8859_6_9[7];  /* "cp1089" */
	char db_ISO_8859_6_10[8];  /* "cp28596" */
	char db_ISO_8859_6_11[14]; /* "windows-28596" */
	char db_ISO_8859_6_12[8];  /* "cp38596" */
	char db_ISO_8859_6_13[14]; /* "windows-38596" */
	char db_ISO_8859_6_14[12]; /* "iso8859-6-i" */
	char db_ISO_8859_6_15[7];  /* "8859-6" */
	char db_ISO_8859_6_16[9];  /* "osf10006" */
	char db_ISO_8859_6_nul;

	/* CODEC_ISO_8859_7 */
	char db_ISO_8859_7_0[15]; /* "iso8859-7:1987" */
	char db_ISO_8859_7_1[11]; /* "iso-ir-126" */
	char db_ISO_8859_7_2[10]; /* "iso8859-7" */
	char db_ISO_8859_7_3[9];  /* "elot-928" */
	char db_ISO_8859_7_4[9];  /* "ecma-118" */
	char db_ISO_8859_7_5[6];  /* "greek" */
	char db_ISO_8859_7_6[7];  /* "greek8" */
	char db_ISO_8859_7_7[15]; /* "iso8859-7:2003" */
	char db_ISO_8859_7_8[16]; /* "csisolatingreek" */
	char db_ISO_8859_7_9[7];  /* "ibm813" */
	char db_ISO_8859_7_10[6];  /* "cp813" */
	char db_ISO_8859_7_11[8];  /* "cp28597" */
	char db_ISO_8859_7_12[14]; /* "windows-28597" */
	char db_ISO_8859_7_13[9];  /* "iso88597" */
	char db_ISO_8859_7_14[7];  /* "8859-7" */
	char db_ISO_8859_7_15[9];  /* "osf10007" */
	char db_ISO_8859_7_nul;

	/* CODEC_ISO_8859_8 */
	char db_ISO_8859_8_0[15]; /* "iso8859-8:1988" */
	char db_ISO_8859_8_1[11]; /* "iso-ir-138" */
	char db_ISO_8859_8_2[10]; /* "iso8859-8" */
	char db_ISO_8859_8_3[7];  /* "hebrew" */
	char db_ISO_8859_8_4[9];  /* "iso88598" */
	char db_ISO_8859_8_5[17]; /* "csisolatinhebrew" */
	char db_ISO_8859_8_6[7];  /* "ibm916" */
	char db_ISO_8859_8_7[6];  /* "cp916" */
	char db_ISO_8859_8_8[8];  /* "cp28598" */
	char db_ISO_8859_8_9[14]; /* "windows-28598" */
	char db_ISO_8859_8_10[8];  /* "cp38598" */
	char db_ISO_8859_8_11[14]; /* "windows-38598" */
	char db_ISO_8859_8_12[12]; /* "iso8859-8-i" */
	char db_ISO_8859_8_13[7];  /* "8859-8" */
	char db_ISO_8859_8_14[9];  /* "osf10008" */
	char db_ISO_8859_8_nul;

	/* CODEC_ISO_8859_9 */
	char db_ISO_8859_9_0[15]; /* "iso8859-9:1989" */
	char db_ISO_8859_9_1[11]; /* "iso-ir-148" */
	char db_ISO_8859_9_2[10]; /* "iso8859-9" */
	char db_ISO_8859_9_3[7];  /* "latin5" */
	char db_ISO_8859_9_4[3];  /* "l5" */
	char db_ISO_8859_9_5[9];  /* "iso88599" */
	char db_ISO_8859_9_6[12]; /* "csisolatin5" */
	char db_ISO_8859_9_7[7];  /* "ibm920" */
	char db_ISO_8859_9_8[6];  /* "cp920" */
	char db_ISO_8859_9_9[8];  /* "cp28599" */
	char db_ISO_8859_9_10[14]; /* "windows-28599" */
	char db_ISO_8859_9_11[7];  /* "8859-9" */
	char db_ISO_8859_9_12[9];  /* "osf10009" */
	char db_ISO_8859_9_13[8];  /* "ts-5881" */
	char db_ISO_8859_9_14[9];  /* "ecma-128" */
	char db_ISO_8859_9_nul;

	/* CODEC_ISO_8859_9E */
	char db_ISO_8859_9E_0[11]; /* "iso8859-9e" */
	char db_ISO_8859_9E_1[10]; /* "iso88599e" */
	char db_ISO_8859_9E_nul;

	/* CODEC_ISO_IR_123 */
	char db_ISO_IR_123_0[19]; /* "csa-z243.4-1985-gr" */
	char db_ISO_IR_123_1[11]; /* "iso-ir-123" */
	char db_ISO_IR_123_2[23]; /* "csiso123csaz24341985gr" */
	char db_ISO_IR_123_nul;

	/* CODEC_ISO_IR_13 */
	char db_ISO_IR_13_0[18]; /* "jis-c6220-1969-jp" */
	char db_ISO_IR_13_1[15]; /* "jis-c6220-1969" */
	char db_ISO_IR_13_2[10]; /* "iso-ir-13" */
	char db_ISO_IR_13_3[9];  /* "katakana" */
	char db_ISO_IR_13_4[7];  /* "x201-7" */
	char db_ISO_IR_13_5[18]; /* "csiso13jisc6220jp" */
	char db_ISO_IR_13_nul;

	/* CODEC_ISO_IR_139 */
	char db_ISO_IR_139_0[11]; /* "csn-369103" */
	char db_ISO_IR_139_1[11]; /* "iso-ir-139" */
	char db_ISO_IR_139_2[18]; /* "csiso139csn369103" */
	char db_ISO_IR_139_nul;

	/* CODEC_ISO_IR_143 */
	char db_ISO_IR_143_0[10]; /* "iec-p27-1" */
	char db_ISO_IR_143_1[11]; /* "iso-ir-143" */
	char db_ISO_IR_143_2[16]; /* "csiso143iecp271" */
	char db_ISO_IR_143_3[9];  /* "iec-p271" */
	char db_ISO_IR_143_nul;

	/* CODEC_ISO_IR_146 */
	char db_ISO_IR_146_0[16]; /* "jus-i.b1.3-serb" */
	char db_ISO_IR_146_1[11]; /* "iso-ir-146" */
	char db_ISO_IR_146_2[8];  /* "serbian" */
	char db_ISO_IR_146_3[16]; /* "csiso146serbian" */
	char db_ISO_IR_146_nul;

	/* CODEC_ISO_IR_147 */
	char db_ISO_IR_147_0[15]; /* "jus-i.b1.3-mac" */
	char db_ISO_IR_147_1[11]; /* "macedonian" */
	char db_ISO_IR_147_2[11]; /* "iso-ir-147" */
	char db_ISO_IR_147_3[19]; /* "csiso147macedonian" */
	char db_ISO_IR_147_nul;

	/* CODEC_ISO_IR_150 */
	char db_ISO_IR_150_0[12]; /* "greek-ccitt" */
	char db_ISO_IR_150_1[11]; /* "iso-ir-150" */
	char db_ISO_IR_150_2[9];  /* "csiso150" */
	char db_ISO_IR_150_3[19]; /* "csiso150greekccitt" */
	char db_ISO_IR_150_4[11]; /* "greekccitt" */
	char db_ISO_IR_150_nul;

	/* CODEC_ISO_IR_152 */
	char db_ISO_IR_152_0[13]; /* "iso6937-2-25" */
	char db_ISO_IR_152_1[11]; /* "iso-ir-152" */
	char db_ISO_IR_152_2[13]; /* "csiso6937add" */
	char db_ISO_IR_152_nul;

	/* CODEC_ISO_IR_153 */
	char db_ISO_IR_153_0[14]; /* "gost-19768-74" */
	char db_ISO_IR_153_1[14]; /* "st-sev-358-88" */
	char db_ISO_IR_153_2[11]; /* "iso-ir-153" */
	char db_ISO_IR_153_3[20]; /* "csiso153gost1976874" */
	char db_ISO_IR_153_4[11]; /* "gost-19768" */
	char db_ISO_IR_153_5[13]; /* "gost-1976874" */
	char db_ISO_IR_153_nul;

	/* CODEC_ISO_IR_154 */
	char db_ISO_IR_154_0[13]; /* "iso8859-supp" */
	char db_ISO_IR_154_1[11]; /* "iso-ir-154" */
	char db_ISO_IR_154_2[11]; /* "latin1-2-5" */
	char db_ISO_IR_154_3[14]; /* "csiso8859supp" */
	char db_ISO_IR_154_nul;

	/* CODEC_ISO_IR_155 */
	char db_ISO_IR_155_0[13]; /* "iso10367-box" */
	char db_ISO_IR_155_1[12]; /* "iso10367box" */
	char db_ISO_IR_155_2[11]; /* "iso-ir-155" */
	char db_ISO_IR_155_3[14]; /* "csiso10367box" */
	char db_ISO_IR_155_nul;

	/* CODEC_ISO_IR_158 */
	char db_ISO_IR_158_0[10]; /* "latin-lap" */
	char db_ISO_IR_158_1[4];  /* "lap" */
	char db_ISO_IR_158_2[11]; /* "iso-ir-158" */
	char db_ISO_IR_158_3[12]; /* "csiso158lap" */
	char db_ISO_IR_158_nul;

	/* CODEC_ISO_IR_18 */
	char db_ISO_IR_18_0[11]; /* "greek7-old" */
	char db_ISO_IR_18_1[10]; /* "greek7old" */
	char db_ISO_IR_18_2[10]; /* "iso-ir-18" */
	char db_ISO_IR_18_3[17]; /* "csiso18greek7old" */
	char db_ISO_IR_18_nul;

	/* CODEC_ISO_IR_182 */
	char db_ISO_IR_182_0[11]; /* "iso-ir-182" */
	char db_ISO_IR_182_nul;

	/* CODEC_ISO_IR_19 */
	char db_ISO_IR_19_0[12]; /* "latin-greek" */
	char db_ISO_IR_19_1[10]; /* "iso-ir-19" */
	char db_ISO_IR_19_2[11]; /* "latingreek" */
	char db_ISO_IR_19_3[18]; /* "csiso19latingreek" */
	char db_ISO_IR_19_nul;

	/* CODEC_ISO_IR_197 */
	char db_ISO_IR_197_0[11]; /* "iso-ir-197" */
	char db_ISO_IR_197_nul;

	/* CODEC_ISO_IR_2 */
	char db_ISO_IR_2_0[16]; /* "iso646.irv:1983" */
	char db_ISO_IR_2_1[9];  /* "iso-ir-2" */
	char db_ISO_IR_2_2[4];  /* "irv" */
	char db_ISO_IR_2_3[21]; /* "csiso2intlrefversion" */
	char db_ISO_IR_2_nul;

	/* CODEC_ISO_IR_200 */
	char db_ISO_IR_200_0[11]; /* "iso-ir-200" */
	char db_ISO_IR_200_nul;

	/* CODEC_ISO_IR_201 */
	char db_ISO_IR_201_0[11]; /* "iso-ir-201" */
	char db_ISO_IR_201_nul;

	/* CODEC_ISO_IR_209 */
	char db_ISO_IR_209_0[11]; /* "iso-ir-209" */
	char db_ISO_IR_209_nul;

	/* CODEC_ISO_IR_50 */
	char db_ISO_IR_50_0[7];  /* "inis-8" */
	char db_ISO_IR_50_1[6];  /* "inis8" */
	char db_ISO_IR_50_2[10]; /* "iso-ir-50" */
	char db_ISO_IR_50_3[13]; /* "csiso50inis8" */
	char db_ISO_IR_50_nul;

	/* CODEC_ISO_IR_51 */
	char db_ISO_IR_51_0[14]; /* "inis-cyrillic" */
	char db_ISO_IR_51_1[13]; /* "iniscyrillic" */
	char db_ISO_IR_51_2[10]; /* "iso-ir-51" */
	char db_ISO_IR_51_3[20]; /* "csiso51iniscyrillic" */
	char db_ISO_IR_51_nul;

	/* CODEC_ISO_IR_54 */
	char db_ISO_IR_54_0[13]; /* "iso5427:1981" */
	char db_ISO_IR_54_1[10]; /* "iso-ir-54" */
	char db_ISO_IR_54_2[20]; /* "iso5427cyrillic1981" */
	char db_ISO_IR_54_3[14]; /* "csiso54271981" */
	char db_ISO_IR_54_4[12]; /* "iso5427-ext" */
	char db_ISO_IR_54_5[11]; /* "iso5427ext" */
	char db_ISO_IR_54_6[22]; /* "csiso5427cyrillic1981" */
	char db_ISO_IR_54_nul;

	/* CODEC_ISO_IR_55 */
	char db_ISO_IR_55_0[13]; /* "iso5428:1980" */
	char db_ISO_IR_55_1[8];  /* "iso5428" */
	char db_ISO_IR_55_2[10]; /* "iso-ir-55" */
	char db_ISO_IR_55_3[15]; /* "csiso5428greek" */
	char db_ISO_IR_55_nul;

	/* CODEC_ISO_IR_68 */
	char db_ISO_IR_68_0[10]; /* "iso-ir-68" */
	char db_ISO_IR_68_nul;

	/* CODEC_ISO_IR_88 */
	char db_ISO_IR_88_0[7];  /* "greek7" */
	char db_ISO_IR_88_1[10]; /* "iso-ir-88" */
	char db_ISO_IR_88_2[14]; /* "csiso88greek7" */
	char db_ISO_IR_88_nul;

	/* CODEC_ISO_IR_89 */
	char db_ISO_IR_89_0[9];  /* "asmo-449" */
	char db_ISO_IR_89_1[8];  /* "iso9036" */
	char db_ISO_IR_89_2[8];  /* "arabic7" */
	char db_ISO_IR_89_3[10]; /* "iso-ir-89" */
	char db_ISO_IR_89_nul;

	/* CODEC_ISO_IR_8_1 */
	char db_ISO_IR_8_1_0[10]; /* "nats-sefi" */
	char db_ISO_IR_8_1_1[9];  /* "natssefi" */
	char db_ISO_IR_8_1_2[11]; /* "iso-ir-8-1" */
	char db_ISO_IR_8_1_3[11]; /* "csnatssefi" */
	char db_ISO_IR_8_1_nul;

	/* CODEC_ISO_IR_8_2 */
	char db_ISO_IR_8_2_0[14]; /* "nats-sefi-add" */
	char db_ISO_IR_8_2_1[11]; /* "iso-ir-8-2" */
	char db_ISO_IR_8_2_nul;

	/* CODEC_ISO_IR_91 */
	char db_ISO_IR_91_0[17]; /* "jis-c6229-1984-a" */
	char db_ISO_IR_91_1[10]; /* "iso-ir-91" */
	char db_ISO_IR_91_2[9];  /* "jp-ocr-a" */
	char db_ISO_IR_91_3[21]; /* "csiso91jisc62291984a" */
	char db_ISO_IR_91_nul;

	/* CODEC_ISO_IR_93 */
	char db_ISO_IR_93_0[21]; /* "jis-c6229-1984-b-add" */
	char db_ISO_IR_93_1[10]; /* "iso-ir-93" */
	char db_ISO_IR_93_2[13]; /* "jp-ocr-b-add" */
	char db_ISO_IR_93_3[23]; /* "csiso93jis62291984badd" */
	char db_ISO_IR_93_nul;

	/* CODEC_ISO_IR_94 */
	char db_ISO_IR_94_0[20]; /* "jis-c6229-1984-hand" */
	char db_ISO_IR_94_1[10]; /* "iso-ir-94" */
	char db_ISO_IR_94_2[12]; /* "jp-ocr-hand" */
	char db_ISO_IR_94_3[23]; /* "csiso94jis62291984hand" */
	char db_ISO_IR_94_nul;

	/* CODEC_ISO_IR_95 */
	char db_ISO_IR_95_0[24]; /* "jis-c6229-1984-hand-add" */
	char db_ISO_IR_95_1[10]; /* "iso-ir-95" */
	char db_ISO_IR_95_2[16]; /* "jp-ocr-hand-add" */
	char db_ISO_IR_95_3[26]; /* "csiso95jis62291984handadd" */
	char db_ISO_IR_95_nul;

	/* CODEC_ISO_IR_96 */
	char db_ISO_IR_96_0[20]; /* "jis-c6229-1984-kana" */
	char db_ISO_IR_96_1[10]; /* "iso-ir-96" */
	char db_ISO_IR_96_2[24]; /* "csiso96jisc62291984kana" */
	char db_ISO_IR_96_nul;

	/* CODEC_ISO_IR_98 */
	char db_ISO_IR_98_0[13]; /* "iso2033-1983" */
	char db_ISO_IR_98_1[8];  /* "iso2033" */
	char db_ISO_IR_98_2[10]; /* "iso-ir-98" */
	char db_ISO_IR_98_3[5];  /* "e13b" */
	char db_ISO_IR_98_4[10]; /* "csiso2033" */
	char db_ISO_IR_98_nul;

	/* CODEC_ISO_IR_9_2 */
	char db_ISO_IR_9_2_0[14]; /* "nats-dano-add" */
	char db_ISO_IR_9_2_1[11]; /* "iso-ir-9-2" */
	char db_ISO_IR_9_2_nul;

	/* CODEC_JIS_C_6229_OCR_A */
	char db_JIS_C_6229_OCR_A_0[17]; /* "jis-c-6229-ocr-a" */
	char db_JIS_C_6229_OCR_A_nul;

	/* CODEC_KEYBCS2 */
	char db_KEYBCS2_0[8];  /* "nec-867" */
	char db_KEYBCS2_1[8];  /* "dos-895" */
	char db_KEYBCS2_2[8];  /* "keybcs2" */
	char db_KEYBCS2_3[10]; /* "kamenicky" */
	char db_KEYBCS2_nul;

	/* CODEC_KOI7_N2 */
	char db_KOI7_N2_0[8];  /* "koi7-n2" */
	char db_KOI7_N2_1[10]; /* "short-koi" */
	char db_KOI7_N2_nul;

	/* CODEC_KOI8_B */
	char db_KOI8_B_0[7]; /* "koi8-b" */
	char db_KOI8_B_nul;

	/* CODEC_KOI8_E */
	char db_KOI8_E_0[14]; /* "ecma-cyrillic" */
	char db_KOI8_E_1[13]; /* "ecmacyrillic" */
	char db_KOI8_E_2[11]; /* "iso-ir-111" */
	char db_KOI8_E_3[9];  /* "ecma-113" */
	char db_KOI8_E_4[7];  /* "koi8-e" */
	char db_KOI8_E_5[21]; /* "csiso111ecmacyrillic" */
	char db_KOI8_E_nul;

	/* CODEC_KOI8_F */
	char db_KOI8_F_0[7];  /* "koi8-f" */
	char db_KOI8_F_1[13]; /* "koi8-unified" */
	char db_KOI8_F_nul;

	/* CODEC_KOI8_N1 */
	char db_KOI8_N1_0[8]; /* "koi8-n1" */
	char db_KOI8_N1_nul;

	/* CODEC_KOI8_N2 */
	char db_KOI8_N2_0[8]; /* "koi8-n2" */
	char db_KOI8_N2_nul;

	/* CODEC_KOI8_R */
	char db_KOI8_R_0[7]; /* "koi8-r" */
	char db_KOI8_R_1[8]; /* "cp20866" */
	char db_KOI8_R_2[6]; /* "cp878" */
	char db_KOI8_R_3[7]; /* "ibm878" */
	char db_KOI8_R_4[8]; /* "cskoi8r" */
	char db_KOI8_R_5[5]; /* "koi8" */
	char db_KOI8_R_nul;

	/* CODEC_KOI8_RU */
	char db_KOI8_RU_0[8];  /* "koi8-ru" */
	char db_KOI8_RU_1[7];  /* "cp1167" */
	char db_KOI8_RU_2[8];  /* "ibm1167" */
	char db_KOI8_RU_3[10]; /* "csibm1167" */
	char db_KOI8_RU_nul;

	/* CODEC_KOI8_T */
	char db_KOI8_T_0[7]; /* "koi8-t" */
	char db_KOI8_T_nul;

	/* CODEC_KOI8_U */
	char db_KOI8_U_0[7]; /* "koi8-u" */
	char db_KOI8_U_1[6]; /* "koi8u" */
	char db_KOI8_U_2[8]; /* "cp21866" */
	char db_KOI8_U_3[7]; /* "cp1168" */
	char db_KOI8_U_4[8]; /* "ibm1168" */
	char db_KOI8_U_5[8]; /* "cskoi8u" */
	char db_KOI8_U_nul;

	/* CODEC_KZ_1048 */
	char db_KZ_1048_0[8];  /* "kz-1048" */
	char db_KZ_1048_1[7];  /* "kz1048" */
	char db_KZ_1048_2[14]; /* "strk1048-2002" */
	char db_KZ_1048_3[7];  /* "rk1048" */
	char db_KZ_1048_4[9];  /* "cskz1048" */
	char db_KZ_1048_nul;

	/* CODEC_LICS */
	char db_LICS_0[5]; /* "lics" */
	char db_LICS_nul;

	/* CODEC_LY1 */
	char db_LY1_0[4]; /* "ly1" */
	char db_LY1_nul;

	/* CODEC_MACINTOSH_FONT_X */
	char db_MACINTOSH_FONT_X_0[17]; /* "macintosh-font-x" */
	char db_MACINTOSH_FONT_X_nul;

	/* CODEC_MACINTOSH_LATIN */
	char db_MACINTOSH_LATIN_0[16]; /* "macintosh-latin" */
	char db_MACINTOSH_LATIN_nul;

	/* CODEC_MACIS */
	char db_MACIS_0[6]; /* "macis" */
	char db_MACIS_1[7]; /* "mac-is" */
	char db_MACIS_nul;

	/* CODEC_MAC_OS_THAI */
	char db_MAC_OS_THAI_0[12]; /* "mac-os-thai" */
	char db_MAC_OS_THAI_nul;

	/* CODEC_MAC_SAMI */
	char db_MAC_SAMI_0[9]; /* "mac-sami" */
	char db_MAC_SAMI_nul;

	/* CODEC_MIK */
	char db_MIK_0[4];  /* "mik" */
	char db_MIK_1[12]; /* "bulgaria-pc" */
	char db_MIK_nul;

	/* CODEC_MSDOS1252 */
	char db_MSDOS1252_0[11]; /* "msdos-1252" */
	char db_MSDOS1252_nul;

	/* CODEC_NEXTSTEP */
	char db_NEXTSTEP_0[9]; /* "nextstep" */
	char db_NEXTSTEP_nul;

	/* CODEC_OSD_EBCDIC_DF03_IRV */
	char db_OSD_EBCDIC_DF03_IRV_0[19]; /* "osd-ebcdic-df3-irv" */
	char db_OSD_EBCDIC_DF03_IRV_1[18]; /* "csosdebcdicdf3irv" */
	char db_OSD_EBCDIC_DF03_IRV_nul;

	/* CODEC_OSD_EBCDIC_DF04_1 */
	char db_OSD_EBCDIC_DF04_1_0[17]; /* "osd-ebcdic-df4-1" */
	char db_OSD_EBCDIC_DF04_1_1[16]; /* "csosdebcdicdf41" */
	char db_OSD_EBCDIC_DF04_1_nul;

	/* CODEC_OSD_EBCDIC_DF04_15 */
	char db_OSD_EBCDIC_DF04_15_0[18]; /* "osd-ebcdic-df4-15" */
	char db_OSD_EBCDIC_DF04_15_1[17]; /* "csosdebcdicdf415" */
	char db_OSD_EBCDIC_DF04_15_nul;

	/* CODEC_PALMOS */
	char db_PALMOS_0[7]; /* "palmos" */
	char db_PALMOS_nul;

	/* CODEC_PT154 */
	char db_PT154_0[8];  /* "ptcp154" */
	char db_PT154_1[10]; /* "csptcp154" */
	char db_PT154_2[6];  /* "pt154" */
	char db_PT154_3[6];  /* "cp154" */
	char db_PT154_4[15]; /* "cyrillic-asian" */
	char db_PT154_5[8];  /* "ibm1169" */
	char db_PT154_nul;

	/* CODEC_URI_ESCAPE */
	char db_URI_ESCAPE_0[11]; /* "uri-escape" */
	char db_URI_ESCAPE_1[11]; /* "url-escape" */
	char db_URI_ESCAPE_2[17]; /* "percent-encoding" */
	char db_URI_ESCAPE_3[13]; /* "url-encoding" */
	char db_URI_ESCAPE_nul;

	/* CODEC_US_DK */
	char db_US_DK_0[6]; /* "us-dk" */
	char db_US_DK_1[7]; /* "csusdk" */
	char db_US_DK_nul;

	/* CODEC_UTF16BE */
	char db_UTF16BE_0[8];  /* "utf16be" */
	char db_UTF16BE_1[9];  /* "utf-16be" */
	char db_UTF16BE_2[8];  /* "ucs-2be" */
	char db_UTF16BE_3[11]; /* "unicodebig" */
	char db_UTF16BE_4[10]; /* "csutf16be" */
	char db_UTF16BE_5[13]; /* "x-unicodebig" */
	char db_UTF16BE_6[19]; /* "unicodebigunmarked" */
	char db_UTF16BE_7[11]; /* "x-utf-16be" */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	char db_UTF16BE_8[6];  /* "utf16" */
	char db_UTF16BE_9[7];  /* "utf-16" */
	char db_UTF16BE_10[8];  /* "csutf16" */
	char db_UTF16BE_11[14]; /* "iso10646/ucs2" */
	char db_UTF16BE_12[15]; /* "iso10646-ucs-2" */
	char db_UTF16BE_13[8];  /* "unicode" */
	char db_UTF16BE_14[10]; /* "csunicode" */
	char db_UTF16BE_15[5];  /* "ucs2" */
	char db_UTF16BE_16[6];  /* "ucs-2" */
	char db_UTF16BE_17[9];  /* "osf10100" */
	char db_UTF16BE_18[9];  /* "osf10101" */
	char db_UTF16BE_19[9];  /* "osf10102" */
	char db_UTF16BE_20[8];  /* "cp13488" */
	char db_UTF16BE_21[14]; /* "windows-13488" */
	char db_UTF16BE_22[7];  /* "cp1200" */
	char db_UTF16BE_23[7];  /* "cp1201" */
#endif /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ && __SIZEOF_WCHAR_T__ == 2
	char db_UTF16BE_24[8];  /* "wchar-t" */
#endif /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ && __SIZEOF_WCHAR_T__ == 2 */
	char db_UTF16BE_nul;

	/* CODEC_UTF16LE */
	char db_UTF16LE_0[8];  /* "utf16le" */
	char db_UTF16LE_1[9];  /* "utf-16le" */
	char db_UTF16LE_2[8];  /* "ucs-2le" */
	char db_UTF16LE_3[14]; /* "unicodelittle" */
	char db_UTF16LE_4[10]; /* "csutf16le" */
	char db_UTF16LE_5[16]; /* "x-unicodelittle" */
	char db_UTF16LE_6[11]; /* "x-utf-16le" */
	char db_UTF16LE_7[22]; /* "unicodelittleunmarked" */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	char db_UTF16LE_8[6];  /* "utf16" */
	char db_UTF16LE_9[7];  /* "utf-16" */
	char db_UTF16LE_10[8];  /* "csutf16" */
	char db_UTF16LE_11[14]; /* "iso10646/ucs2" */
	char db_UTF16LE_12[15]; /* "iso10646-ucs-2" */
	char db_UTF16LE_13[8];  /* "unicode" */
	char db_UTF16LE_14[10]; /* "csunicode" */
	char db_UTF16LE_15[5];  /* "ucs2" */
	char db_UTF16LE_16[6];  /* "ucs-2" */
	char db_UTF16LE_17[9];  /* "osf10100" */
	char db_UTF16LE_18[9];  /* "osf10101" */
	char db_UTF16LE_19[9];  /* "osf10102" */
	char db_UTF16LE_20[8];  /* "cp13488" */
	char db_UTF16LE_21[14]; /* "windows-13488" */
	char db_UTF16LE_22[7];  /* "cp1200" */
	char db_UTF16LE_23[7];  /* "cp1201" */
#endif /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ && __SIZEOF_WCHAR_T__ == 2
	char db_UTF16LE_24[8];  /* "wchar-t" */
#endif /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ && __SIZEOF_WCHAR_T__ == 2 */
	char db_UTF16LE_nul;

	/* CODEC_UTF32BE */
	char db_UTF32BE_0[8];  /* "utf32be" */
	char db_UTF32BE_1[9];  /* "utf-32be" */
	char db_UTF32BE_2[8];  /* "ucs-4be" */
	char db_UTF32BE_3[8];  /* "cp12001" */
	char db_UTF32BE_4[14]; /* "windows-12001" */
	char db_UTF32BE_5[10]; /* "csutf32be" */
	char db_UTF32BE_6[11]; /* "x-utf-32be" */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	char db_UTF32BE_7[6];  /* "utf32" */
	char db_UTF32BE_8[7];  /* "utf-32" */
	char db_UTF32BE_9[8];  /* "csutf32" */
	char db_UTF32BE_10[14]; /* "iso10646/ucs4" */
	char db_UTF32BE_11[15]; /* "iso10646-ucs-4" */
	char db_UTF32BE_12[7];  /* "csucs4" */
	char db_UTF32BE_13[5];  /* "ucs4" */
	char db_UTF32BE_14[6];  /* "ucs-4" */
	char db_UTF32BE_15[9];  /* "iso10646" */
	char db_UTF32BE_16[13]; /* "10646-1:1993" */
	char db_UTF32BE_17[18]; /* "10646-1:1993/ucs4" */
	char db_UTF32BE_18[9];  /* "osf10104" */
	char db_UTF32BE_19[9];  /* "osf10105" */
	char db_UTF32BE_20[9];  /* "osf10106" */
	char db_UTF32BE_21[8];  /* "cp12000" */
#endif /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ && __SIZEOF_WCHAR_T__ == 4
	char db_UTF32BE_22[8];  /* "wchar-t" */
#endif /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ && __SIZEOF_WCHAR_T__ == 4 */
	char db_UTF32BE_nul;

	/* CODEC_UTF32LE */
	char db_UTF32LE_0[8];  /* "utf32le" */
	char db_UTF32LE_1[9];  /* "utf-32le" */
	char db_UTF32LE_2[8];  /* "ucs-4le" */
	char db_UTF32LE_3[10]; /* "csutf32le" */
	char db_UTF32LE_4[11]; /* "x-utf-32le" */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	char db_UTF32LE_5[6];  /* "utf32" */
	char db_UTF32LE_6[7];  /* "utf-32" */
	char db_UTF32LE_7[8];  /* "csutf32" */
	char db_UTF32LE_8[14]; /* "iso10646/ucs4" */
	char db_UTF32LE_9[15]; /* "iso10646-ucs-4" */
	char db_UTF32LE_10[7];  /* "csucs4" */
	char db_UTF32LE_11[5];  /* "ucs4" */
	char db_UTF32LE_12[6];  /* "ucs-4" */
	char db_UTF32LE_13[9];  /* "iso10646" */
	char db_UTF32LE_14[13]; /* "10646-1:1993" */
	char db_UTF32LE_15[18]; /* "10646-1:1993/ucs4" */
	char db_UTF32LE_16[9];  /* "osf10104" */
	char db_UTF32LE_17[9];  /* "osf10105" */
	char db_UTF32LE_18[9];  /* "osf10106" */
	char db_UTF32LE_19[8];  /* "cp12000" */
#endif /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ && __SIZEOF_WCHAR_T__ == 4
	char db_UTF32LE_20[8];  /* "wchar-t" */
#endif /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ && __SIZEOF_WCHAR_T__ == 4 */
	char db_UTF32LE_nul;

	/* CODEC_UTF8 */
	char db_UTF8_0[5];  /* "utf8" */
	char db_UTF8_1[6];  /* "utf-8" */
	char db_UTF8_2[14]; /* "iso10646/utf8" */
	char db_UTF8_3[15]; /* "iso10646/utf-8" */
	char db_UTF8_4[11]; /* "iso-ir-193" */
	char db_UTF8_5[11]; /* "osf5010001" */
	char db_UTF8_6[8];  /* "cp65001" */
	char db_UTF8_7[14]; /* "windows-65001" */
	char db_UTF8_8[7];  /* "csutf8" */
	char db_UTF8_nul;

	/* CODEC_UTF8_BOM */
	char db_UTF8_BOM_0[9];  /* "utf8-bom" */
	char db_UTF8_BOM_1[10]; /* "utf-8-bom" */
	char db_UTF8_BOM_2[8];  /* "utf8bom" */
	char db_UTF8_BOM_3[9];  /* "utf-8bom" */
	char db_UTF8_BOM_nul;

	/* CODEC_VENTURA_INTERNATIONAL */
	char db_VENTURA_INTERNATIONAL_0[22]; /* "ventura-international" */
	char db_VENTURA_INTERNATIONAL_1[12]; /* "ventura-int" */
	char db_VENTURA_INTERNATIONAL_2[23]; /* "csventurainternational" */
	char db_VENTURA_INTERNATIONAL_nul;

	/* CODEC_VENTURA_US */
	char db_VENTURA_US_0[11]; /* "ventura-us" */
	char db_VENTURA_US_1[12]; /* "csventuraus" */
	char db_VENTURA_US_nul;

	/* CODEC_X0201 */
	char db_X0201_0[9];  /* "jis-x201" */
	char db_X0201_1[5];  /* "x201" */
	char db_X0201_2[20]; /* "cshalfwidthkatakana" */
	char db_X0201_3[7];  /* "jis201" */
	char db_X0201_nul;

	/* CODEC_XML_ESCAPE */
	char db_XML_ESCAPE_0[11]; /* "xml-escape" */
	char db_XML_ESCAPE_1[12]; /* "html-escape" */
	char db_XML_ESCAPE_nul;

	/* CODEC_X_MAC_ARMENIAN */
	char db_X_MAC_ARMENIAN_0[15]; /* "x-mac-armenian" */
	char db_X_MAC_ARMENIAN_nul;

	/* CODEC_X_MAC_BARENTS_CYRILLIC */
	char db_X_MAC_BARENTS_CYRILLIC_0[23]; /* "x-mac-barents-cyrillic" */
	char db_X_MAC_BARENTS_CYRILLIC_nul;

	/* CODEC_X_MAC_CELTIC */
	char db_X_MAC_CELTIC_0[13]; /* "x-mac-celtic" */
	char db_X_MAC_CELTIC_nul;

	/* CODEC_X_MAC_CYRILLIC */
	char db_X_MAC_CYRILLIC_0[15]; /* "x-mac-cyrillic" */
	char db_X_MAC_CYRILLIC_nul;

	/* CODEC_X_MAC_DEVANAGARI */
	char db_X_MAC_DEVANAGARI_0[17]; /* "x-mac-devanagari" */
	char db_X_MAC_DEVANAGARI_nul;

	/* CODEC_X_MAC_FARSI */
	char db_X_MAC_FARSI_0[12]; /* "x-mac-farsi" */
	char db_X_MAC_FARSI_1[9];  /* "macfarsi" */
	char db_X_MAC_FARSI_nul;

	/* CODEC_X_MAC_GAELIC */
	char db_X_MAC_GAELIC_0[13]; /* "x-mac-gaelic" */
	char db_X_MAC_GAELIC_nul;

	/* CODEC_X_MAC_GEORGIAN */
	char db_X_MAC_GEORGIAN_0[15]; /* "x-mac-georgian" */
	char db_X_MAC_GEORGIAN_nul;

	/* CODEC_X_MAC_GUJARATI */
	char db_X_MAC_GUJARATI_0[15]; /* "x-mac-gujarati" */
	char db_X_MAC_GUJARATI_nul;

	/* CODEC_X_MAC_GURMUKHI */
	char db_X_MAC_GURMUKHI_0[15]; /* "x-mac-gurmukhi" */
	char db_X_MAC_GURMUKHI_nul;

	/* CODEC_X_MAC_INUIT */
	char db_X_MAC_INUIT_0[12]; /* "x-mac-inuit" */
	char db_X_MAC_INUIT_nul;

	/* CODEC_X_MAC_MALTESE */
	char db_X_MAC_MALTESE_0[14]; /* "x-mac-maltese" */
	char db_X_MAC_MALTESE_1[16]; /* "x-mac-esperanto" */
	char db_X_MAC_MALTESE_nul;

	/* CODEC_X_MAC_OGHAM */
	char db_X_MAC_OGHAM_0[12]; /* "x-mac-ogham" */
	char db_X_MAC_OGHAM_nul;

	/* CODEC_X_MAC_SAMI */
	char db_X_MAC_SAMI_0[11]; /* "x-mac-sami" */
	char db_X_MAC_SAMI_nul;

	/* CODEC_X_MAC_TURKIC_CYRILLIC */
	char db_X_MAC_TURKIC_CYRILLIC_0[22]; /* "x-mac-turkic-cyrillic" */
	char db_X_MAC_TURKIC_CYRILLIC_nul;
};

/* Name database */
PRIVATE struct codec_name_db_struct const codec_name_db = {
	{ 0, 0 },

	/* CODEC_ADOBE_STANDARD_ENCODING */
	"adobe-standard-encoding",
	"csadobestandardencoding",
	0,

	/* CODEC_ADOBE_SYMBOL_ENCODING */
	"macsymbol",
	"adobe-symbol-encoding",
	"cshppsmath",
	"cp1038",
	"ibm1038",
	"x-mac-symbol",
	0,

	/* CODEC_ADOBE_ZAPF_DINGBATS */
	"adobe-zapf-dingbats",
	0,

	/* CODEC_AMIGA_1251 */
	"amiga-1251",
	"ami1251",
	"amiga1251",
	"ami-1251",
	"csamiga1251",
	0,

	/* CODEC_ASCII */
	"ansi-x3.4-1968",
	"iso-ir-6",
	"ansi-x3.4-1986",
	"iso646.irv:1991",
	"ascii",
	"iso646-us",
	"us-ascii",
	"us",
	"ibm367",
	"cp367",
	"ansi-x3.4",
	"csascii",
	"osf10020",
	"cp20127",
	"windows-20127",
	"ibm891",
	"cp891",
	"csibm891",
	"osf1002037b",
	"ibm903",
	"cp903",
	"csibm903",
	"osf10020387",
	"default",
	"646",
	"ascii7",
	"direct",
	0,

	/* CODEC_ATARIST */
	"atarist",
	0,

	/* CODEC_BCDIC */
	"bcdic",
	0,

	/* CODEC_BRF */
	"brf",
	"csbrf",
	0,

	/* CODEC_BURROUGHS_B5500 */
	"burroughs-b5500",
	0,

	/* CODEC_CP10004 */
	"cp10004",
	"windows-10004",
	"x-mac-arabic",
	"macarabic",
	0,

	/* CODEC_CP10006 */
	"cp10006",
	"windows-10006",
	"x-mac-greek",
	"cp10006-macgreek",
	"macgreek",
	"ibm1280",
	0,

	/* CODEC_CP10007 */
	"cp10007",
	"windows-10007",
	"cp1283",
	"ibm1283",
	"ms-mac-cyrillic",
	"msmaccyrillic",
	"cp10007-maccyrillic",
	"mac-cyrillic",
	"maccyrillic",
	0,

	/* CODEC_CP10017 */
	"cp10017",
	"windows-10017",
	"x-mac-ukrainian",
	"macuk",
	"mac-uk",
	"macukrainian",
	0,

	/* CODEC_CP1004 */
	"cp1004",
	"windows-extended",
	"ibm1004",
	"os2latin1",
	0,

	/* CODEC_CP1006 */
	"cp1006",
	"ibm1006",
	"iso8-bit-urdu",
	0,

	/* CODEC_CP1008 */
	"cp1008",
	"ibm1008",
	"csibm1008",
	"cp5104",
	"ibm5104",
	0,

	/* CODEC_CP1025 */
	"cp1025",
	"ibm1025",
	"csibm1025",
	0,

	/* CODEC_CP1026 */
	"ibm1026",
	"cp1026",
	"csibm1026",
	"1026",
	"osf10020402",
	0,

	/* CODEC_CP1036 */
	"cp1036",
	"ibm1036",
	"t.61",
	"t.618bit",
	"t.61-8bit",
	"cp20261",
	"windows-20261",
	"iso-ir-103",
	"csiso103t618bit",
	0,

	/* CODEC_CP1040 */
	"cp1040",
	0,

	/* CODEC_CP1041 */
	"ibm1041",
	"cp1041",
	0,

	/* CODEC_CP1042 */
	"cp1042",
	0,

	/* CODEC_CP1043 */
	"ibm1043",
	"cp1043",
	0,

	/* CODEC_CP1046 */
	"cp1046",
	"1046",
	"ibm1046",
	0,

	/* CODEC_CP1047 */
	"cp1047",
	"ibm1047",
	"1047",
	"osf10020417",
	"csibm1047",
	0,

	/* CODEC_CP1057 */
	"cp1057",
	"hp-pc-8",
	0,

	/* CODEC_CP1088 */
	"ibm1088",
	"cp1088",
	0,

	/* CODEC_CP1090 */
	"cp1090",
	"ibm1090",
	"dec-special-graphics",
	0,

	/* CODEC_CP1097 */
	"cp1097",
	"ibm1097",
	"csibm1097",
	0,

	/* CODEC_CP1098 */
	"cp1098",
	"ibm1098",
	0,

	/* CODEC_CP1100 */
	"dec-mcs",
	"dec",
	"cp1100",
	"ibm1100",
	"we8dec",
	"csdecmcs",
	"decmcs",
	0,

	/* CODEC_CP1112 */
	"cp1112",
	"ibm1112",
	"csibm1112",
	0,

	/* CODEC_CP1114 */
	"ibm1114",
	"cp1114",
	0,

	/* CODEC_CP1115 */
	"ibm1115",
	"cp1115",
	0,

	/* CODEC_CP1116 */
	"cp1116",
	"ibm1116",
	0,

	/* CODEC_CP1117 */
	"cp1117",
	"ibm1117",
	0,

	/* CODEC_CP1122 */
	"cp1122",
	"ibm1122",
	"csibm1122",
	0,

	/* CODEC_CP1123 */
	"cp1123",
	"ibm1123",
	"csibm1123",
	0,

	/* CODEC_CP1124 */
	"cp1124",
	"ibm1124",
	"csibm1124",
	0,

	/* CODEC_CP1125 */
	"cp1125",
	"rst-2018-91",
	"cp866u",
	"ruscii",
	"ibm848",
	0,

	/* CODEC_CP1127 */
	"cp1127",
	0,

	/* CODEC_CP1130 */
	"cp1130",
	"ibm1130",
	"csibm1130",
	0,

	/* CODEC_CP1131 */
	"cp1131",
	"ibm1131",
	0,

	/* CODEC_CP1132 */
	"cp1132",
	"ibm1132",
	"csibm1132",
	0,

	/* CODEC_CP1133 */
	"cp1133",
	"ibm1133",
	"csibm1133",
	0,

	/* CODEC_CP1137 */
	"cp1137",
	"ibm1137",
	"csibm1137",
	0,

	/* CODEC_CP1140 */
	"cp1140",
	"ibm1140",
	"1140",
	"csibm1140",
	"ccsid1140",
	"ebcdic-us-37+euro",
	0,

	/* CODEC_CP1141 */
	"cp1141",
	"ibm1141",
	"1141",
	"csibm1141",
	"ccsid1141",
	"ebcdic-de-273+euro",
	0,

	/* CODEC_CP1142 */
	"cp1142",
	"ibm1142",
	"1142",
	"csibm1142",
	"ccsid1142",
	"ebcdic-dk-277+euro",
	"ebcdic-no-277+euro",
	0,

	/* CODEC_CP1143 */
	"cp1143",
	"ibm1143",
	"1143",
	"csibm1143",
	"ccsid1143",
	"ebcdic-fi-278+euro",
	"ebcdic-se-278+euro",
	0,

	/* CODEC_CP1144 */
	"cp1144",
	"ibm1144",
	"1144",
	"csibm1144",
	"ccsid1144",
	"ebcdic-it-280+euro",
	0,

	/* CODEC_CP1145 */
	"cp1145",
	"ibm1145",
	"1145",
	"csibm1145",
	"ccsid1145",
	"ebcdic-es-284+euro",
	0,

	/* CODEC_CP1146 */
	"cp1146",
	"ibm1146",
	"1146",
	"csibm1146",
	"ccsid1146",
	"ebcdic-gb-285+euro",
	0,

	/* CODEC_CP1147 */
	"cp1147",
	"ibm1147",
	"1147",
	"csibm1147",
	"ccsid1147",
	"ebcdic-fr-297+euro",
	0,

	/* CODEC_CP1148 */
	"cp1148",
	"ibm1148",
	"1148",
	"csibm1148",
	"ccsid1148",
	"ebcdic-international-500+euro",
	0,

	/* CODEC_CP1149 */
	"cp1149",
	"ibm1149",
	"1149",
	"csibm1149",
	"ccsid1149",
	"ebcdic-is-871+euro",
	0,

	/* CODEC_CP1153 */
	"cp1153",
	"ibm1153",
	"csibm1153",
	0,

	/* CODEC_CP1154 */
	"cp1154",
	"ibm1154",
	"csibm1154",
	0,

	/* CODEC_CP1155 */
	"cp1155",
	"ibm1155",
	"csibm1155",
	0,

	/* CODEC_CP1156 */
	"cp1156",
	"ibm1156",
	"csibm1156",
	0,

	/* CODEC_CP1157 */
	"cp1157",
	"ibm1157",
	"csibm1157",
	0,

	/* CODEC_CP1158 */
	"cp1158",
	"ibm1158",
	"csibm1158",
	0,

	/* CODEC_CP1160 */
	"cp1160",
	"ibm1160",
	"csibm1160",
	0,

	/* CODEC_CP1161 */
	"cp1161",
	"ibm1161",
	"csibm1161",
	0,

	/* CODEC_CP1162 */
	"cp1162",
	"ibm1162",
	"csibm11621162",
	0,

	/* CODEC_CP1163 */
	"cp1163",
	"ibm1163",
	"csibm1163",
	0,

	/* CODEC_CP1164 */
	"cp1164",
	"ibm1164",
	"csibm1164",
	0,

	/* CODEC_CP1166 */
	"cp1166",
	"ibm1166",
	"csibm1166",
	0,

	/* CODEC_CP1250 */
	"cp1250",
	"ibm1250",
	"windows-1250",
	"cswindows1250",
	"ms-ee",
	0,

	/* CODEC_CP1251 */
	"cp1251",
	"ibm1251",
	"windows-1251",
	"cswindows1251",
	"ms-cyrl",
	0,

	/* CODEC_CP1252 */
	"cp1252",
	"ibm1252",
	"windows-1252",
	"cswindows1252",
	"ms-ansi",
	0,

	/* CODEC_CP1253 */
	"cp1253",
	"ibm1253",
	"windows-1253",
	"cswindows1253",
	"ms-greek",
	0,

	/* CODEC_CP1254 */
	"cp1254",
	"ibm1254",
	"windows-1254",
	"cswindows1254",
	"ms-turk",
	0,

	/* CODEC_CP1255 */
	"cp1255",
	"ibm1255",
	"windows-1255",
	"cswindows1255",
	"ms-hebr",
	0,

	/* CODEC_CP1256 */
	"cp1256",
	"ibm1256",
	"windows-1256",
	"cswindows1256",
	"ms-arab",
	"cp9448",
	"ibm9448",
	"csibm9448",
	0,

	/* CODEC_CP1257 */
	"cp1257",
	"ibm1257",
	"windows-1257",
	"lst-1590-3",
	"cswindows1257",
	"winbaltrim",
	0,

	/* CODEC_CP1258 */
	"cp1258",
	"ibm1258",
	"windows-1258",
	"cswindows1258",
	"cp1129",
	"ibm1129",
	"csibm1129",
	0,

	/* CODEC_CP1270 */
	"cp1270",
	"windows-1270",
	"ws2",
	"winsami2",
	"win-sami-2",
	0,

	/* CODEC_CP12712 */
	"cp12712",
	"ibm12712",
	"csibm12712",
	0,

	/* CODEC_CP1275 */
	"macintosh",
	"mac",
	"csmacintosh",
	"cp1275",
	"ibm1275",
	"cp10000",
	"windows-10000",
	"x-mac-roman",
	"macroman",
	"cp10000-macroman",
	0,

	/* CODEC_CP1276 */
	"cp1276",
	"postscript-standard-encoding",
	"standardencoding",
	"postscript",
	0,

	/* CODEC_CP1281 */
	"macturkish",
	"cp1281",
	"ibm1281",
	"cp10081",
	"windows-10081",
	"x-mac-turkish",
	"cp10081-macturkish",
	0,

	/* CODEC_CP1282 */
	"maccentraleurope",
	"cp1282",
	"ibm1282",
	"cp10029",
	"windows-10029",
	"x-mac-ce",
	"mac-centraleurope",
	"cp10029-maclatin2",
	0,

	/* CODEC_CP1284 */
	"maccroatian",
	"cp1284",
	"ibm1284",
	"cp10082",
	"windows-10082",
	"x-mac-croatian",
	0,

	/* CODEC_CP1285 */
	"macromania",
	"cp1285",
	"ibm1285",
	"cp10010",
	"windows-10010",
	"x-mac-romanian",
	0,

	/* CODEC_CP1286 */
	"maciceland",
	"cp1286",
	"ibm1286",
	"cp10079",
	"windows-10079",
	"x-mac-icelandic",
	"cp10079-macicelandic",
	0,

	/* CODEC_CP1287 */
	"cp1287",
	"dec-greek-(8-bit)",
	"dec-greek-8-bit",
	"dec-greek-8",
	"dec-greek",
	"el8dec",
	0,

	/* CODEC_CP1288 */
	"cp1288",
	"dec-turkish-(8-bit)",
	"dec-turkish-8-bit",
	"dec-turkish-8",
	"dec-turkish",
	"tr8dec",
	0,

	/* CODEC_CP16804 */
	"cp16804",
	"ibm16804",
	"csibm16804",
	0,

	/* CODEC_CP17248 */
	"cp17248",
	0,

	/* CODEC_CP20269 */
	"cp20269",
	"t.51",
	"iso6937",
	"iso-ir-156",
	"iso6937:1992",
	0,

	/* CODEC_CP273 */
	"ibm273",
	"cp273",
	"csibm273",
	"osf10020111",
	0,

	/* CODEC_CP274 */
	"ibm274",
	"ebcdic-be",
	"cp274",
	"csibm274",
	0,

	/* CODEC_CP275 */
	"ibm275",
	"ebcdic-br",
	"cp275",
	"csibm275",
	0,

	/* CODEC_CP278 */
	"ibm278",
	"cp278",
	"ebcdic-cp-fi",
	"ebcdic-cp-se",
	"csibm278",
	"osf10020116",
	0,

	/* CODEC_CP280 */
	"ibm280",
	"cp280",
	"ebcdic-cp-it",
	"csibm280",
	"osf10020118",
	0,

	/* CODEC_CP281 */
	"ibm281",
	"ebcdic-jp-e",
	"cp281",
	"csibm281",
	0,

	/* CODEC_CP284 */
	"ibm284",
	"cp284",
	"ebcdic-cp-es",
	"csibm284",
	"osf1002011c",
	"cp1079",
	0,

	/* CODEC_CP285 */
	"ibm285",
	"cp285",
	"ebcdic-cp-gb",
	"csibm285",
	"osf1002011d",
	0,

	/* CODEC_CP290 */
	"ibm290",
	"cp290",
	"ebcdic-jp-kana",
	"csibm290",
	"osf10020122",
	0,

	/* CODEC_CP297 */
	"ibm297",
	"cp297",
	"ebcdic-cp-fr",
	"csibm297",
	"osf10020129",
	"cp1081",
	0,

	/* CODEC_CP3012 */
	"cp3012",
	"ruslat",
	0,

	/* CODEC_CP353 */
	"cp353",
	0,

	/* CODEC_CP355 */
	"cp355",
	"pttc/bcd",
	0,

	/* CODEC_CP357 */
	"cp357",
	"pttc/bcd-h",
	0,

	/* CODEC_CP358 */
	"cp358",
	"pttc/bcd-c",
	0,

	/* CODEC_CP359 */
	"cp359",
	"pttc/bcd-m",
	"cp360",
	"pttc/bcd-d",
	0,

	/* CODEC_CP37 */
	"ibm37",
	"cp37",
	"ebcdic-cp-us",
	"ebcdic-cp-ca",
	"ebcdic-cp-wt",
	"ebcdic-cp-nl",
	"csibm37",
	"osf10020025",
	"cp1070",
	"cp282",
	0,

	/* CODEC_CP38 */
	"ibm38",
	"ebcdic-int",
	"cp38",
	"csibm38",
	0,

	/* CODEC_CP420 */
	"ibm420",
	"cp420",
	"ebcdic-cp-ar1",
	"csibm420",
	"osf100201a4",
	0,

	/* CODEC_CP423 */
	"ibm423",
	"cp423",
	"ebcdic-cp-gr",
	"csibm423",
	0,

	/* CODEC_CP424 */
	"ibm424",
	"cp424",
	"ebcdic-cp-he",
	"csibm424",
	"osf100201a8",
	0,

	/* CODEC_CP437 */
	"ibm437",
	"cp437",
	"437",
	"cspc8codepage437",
	"oemus",
	"osf100201b5",
	0,

	/* CODEC_CP4517 */
	"cp4517",
	"ibm4517",
	"csibm4517",
	0,

	/* CODEC_CP4899 */
	"cp4899",
	"ibm4899",
	"csibm4899",
	0,

	/* CODEC_CP4909 */
	"cp4909",
	"ibm4909",
	"csibm4909",
	0,

	/* CODEC_CP4971 */
	"cp4971",
	"ibm4971",
	"csibm4971",
	0,

	/* CODEC_CP500 */
	"ibm500",
	"cp500",
	"ebcdic-cp-be",
	"ebcdic-cp-ch",
	"csibm500",
	"500",
	"500v1",
	"osf100201f4",
	"cp1084",
	0,

	/* CODEC_CP5347 */
	"cp5347",
	"ibm5347",
	"csibm5347",
	0,

	/* CODEC_CP667 */
	"mazovia",
	"cp667",
	"cp790",
	"cp991",
	"maz",
	0,

	/* CODEC_CP668 */
	"cp668",
	0,

	/* CODEC_CP708 */
	"cp708",
	"ibm708",
	0,

	/* CODEC_CP720 */
	"cp720",
	"ibm720",
	"oem720",
	0,

	/* CODEC_CP737 */
	"cp737",
	"ibm737",
	"oem737",
	0,

	/* CODEC_CP770 */
	"cp770",
	0,

	/* CODEC_CP771 */
	"cp771",
	"kbl",
	0,

	/* CODEC_CP772 */
	"cp772",
	"lst-1284",
	"lst-1284:1993",
	"cp1119",
	0,

	/* CODEC_CP773 */
	"cp773",
	0,

	/* CODEC_CP774 */
	"cp774",
	"cp1118",
	"ibm1118",
	"lst-1283",
	0,

	/* CODEC_CP775 */
	"cp775",
	"ibm775",
	"oem775",
	"cspc775baltic",
	0,

	/* CODEC_CP803 */
	"cp803",
	"ibm803",
	"csibm803",
	0,

	/* CODEC_CP806 */
	"cp806",
	"ibm806",
	0,

	/* CODEC_CP808 */
	"ibm808",
	"cp808",
	0,

	/* CODEC_CP848 */
	"cp848",
	0,

	/* CODEC_CP849 */
	"cp849",
	0,

	/* CODEC_CP850 */
	"ibm850",
	"cp850",
	"850",
	"cspc850multilingual",
	"oem850",
	"osf10020352",
	0,

	/* CODEC_CP851 */
	"ibm851",
	"cp851",
	"851",
	"csibm851",
	0,

	/* CODEC_CP852 */
	"ibm852",
	"cp852",
	"852",
	"cspcp852",
	"osf10020354",
	0,

	/* CODEC_CP853 */
	"cp853",
	"ibm853",
	0,

	/* CODEC_CP855 */
	"ibm855",
	"cp855",
	"855",
	"oem855",
	"csibm855",
	"osf10020357",
	0,

	/* CODEC_CP856 */
	"cp856",
	"ibm856",
	"856",
	"csibm856",
	0,

	/* CODEC_CP857 */
	"ibm857",
	"cp857",
	"857",
	"oem857",
	"csibm857",
	"osf10020359",
	0,

	/* CODEC_CP858 */
	"cp858",
	"ibm858",
	"oem858",
	"pc-multilingual-850+euro",
	"ccsid858",
	"csibm858",
	"858",
	"cspc858multilingual",
	0,

	/* CODEC_CP859 */
	"cp859",
	"ibm859",
	0,

	/* CODEC_CP860 */
	"ibm860",
	"cp860",
	"860",
	"oem860",
	"csibm860",
	0,

	/* CODEC_CP861 */
	"ibm861",
	"cp861",
	"861",
	"oem861",
	"cp-is",
	"csibm861",
	"cpibm861",
	"osf1002035d",
	0,

	/* CODEC_CP862 */
	"ibm862",
	"cp862",
	"862",
	"oem862",
	"cspc862latinhebrew",
	"osf1002035e",
	0,

	/* CODEC_CP863 */
	"ibm863",
	"cp863",
	"863",
	"oem863",
	"csibm863",
	"osf1002035f",
	0,

	/* CODEC_CP864 */
	"ibm864",
	"cp864",
	"csibm864",
	"864",
	"osf10020360",
	0,

	/* CODEC_CP865 */
	"ibm865",
	"cp865",
	"865",
	"oem865",
	"csibm865",
	0,

	/* CODEC_CP866 */
	"cp866",
	"866",
	"ibm866",
	"csibm866",
	0,

	/* CODEC_CP866NAV */
	"cp866nav",
	"866nav",
	"ibm866nav",
	0,

	/* CODEC_CP867 */
	"ibm867",
	"cp867",
	0,

	/* CODEC_CP868 */
	"ibm868",
	"cp868",
	"cp-ar",
	"csibm868",
	"osf10020364",
	0,

	/* CODEC_CP869 */
	"ibm869",
	"cp869",
	"869",
	"cp-gr",
	"oem869",
	"csibm869",
	"osf10020365",
	0,

	/* CODEC_CP870 */
	"ibm870",
	"cp870",
	"ebcdic-cp-roece",
	"ebcdic-cp-yu",
	"csibm870",
	"osf10020366",
	0,

	/* CODEC_CP871 */
	"ibm871",
	"cp871",
	"ebcdic-cp-is",
	"csibm871",
	"osf10020367",
	0,

	/* CODEC_CP872 */
	"cp872",
	0,

	/* CODEC_CP874 */
	"cp874",
	"ibm874",
	"x-ibm874",
	"874",
	"windows-874",
	"ms874",
	"x-windows-874",
	"cswindows874",
	0,

	/* CODEC_CP875 */
	"cp875",
	"ibm875",
	"ebcdic-greek",
	"osf1002036b",
	0,

	/* CODEC_CP880 */
	"ibm880",
	"cp880",
	"ebcdic-cyrillic",
	"csibm880",
	"osf10020370",
	0,

	/* CODEC_CP896 */
	"cp896",
	"ibm896",
	"cp4992",
	0,

	/* CODEC_CP897 */
	"ibm897",
	"cp897",
	0,

	/* CODEC_CP901 */
	"cp901",
	"ibm901",
	"csibm901",
	"iso-ir-206",
	0,

	/* CODEC_CP902 */
	"cp902",
	"ibm902",
	"csibm902",
	0,

	/* CODEC_CP9030 */
	"cp9030",
	"ibm9030",
	"csibm9030",
	0,

	/* CODEC_CP904 */
	"ibm904",
	"cp904",
	"904",
	"csibbm904",
	"csibm904",
	"osf10020388",
	0,

	/* CODEC_CP905 */
	"ibm905",
	"cp905",
	"ebcdic-cp-tr",
	"csibm905",
	0,

	/* CODEC_CP9066 */
	"cp9066",
	"ibm9066",
	"csibm9066",
	0,

	/* CODEC_CP918 */
	"ibm918",
	"cp918",
	"918",
	"ebcdic-cp-ar2",
	"csibm918",
	"osf10020396",
	0,

	/* CODEC_CP921 */
	"cp921",
	"ibm921",
	"csibm921",
	"8859-13",
	"iso8859-13",
	"iso885913",
	"iso-ir-179",
	"csisolatin7",
	"latin7",
	"l7",
	"baltic",
	"cp28603",
	"windows-28603",
	"csiso885913",
	0,

	/* CODEC_CP922 */
	"cp922",
	"ibm922",
	"csibm922",
	"estonia-iso-8",
	0,

	/* CODEC_CWI */
	"cwi",
	"cwi-2",
	"cp-hu",
	0,

	/* CODEC_C_ESCAPE */
	"c-escape",
	0,

	/* CODEC_C_ESCAPE_ALL */
	"c-escape-all",
	0,

	/* CODEC_C_ESCAPE_BYTES */
	"c-escape-bytes",
	0,

	/* CODEC_C_ESCAPE_BYTES_ALL */
	"c-escape-all-bytes",
	"c-escape-bytes-all",
	0,

	/* CODEC_C_ESCAPE_BYTES_CHR */
	"c-escape-bytes-chr",
	"c-escape-chr-bytes",
	0,

	/* CODEC_C_ESCAPE_BYTES_INCHR */
	"c-escape-inchr-bytes",
	"c-escape-bytes-inchr",
	0,

	/* CODEC_C_ESCAPE_BYTES_INSTR */
	"c-escape-instr-bytes",
	"c-escape-bytes-instr",
	0,

	/* CODEC_C_ESCAPE_BYTES_RAW */
	"c-escape-bytes-raw",
	"c-escape-raw-bytes",
	0,

	/* CODEC_C_ESCAPE_BYTES_STR */
	"c-escape-bytes-str",
	"c-escape-str-bytes",
	0,

	/* CODEC_C_ESCAPE_CHR */
	"c-escape-chr",
	0,

	/* CODEC_C_ESCAPE_INCHR */
	"c-escape-inchr",
	0,

	/* CODEC_C_ESCAPE_INSTR */
	"c-escape-instr",
	0,

	/* CODEC_C_ESCAPE_RAW */
	"c-escape-raw",
	0,

	/* CODEC_C_ESCAPE_STR */
	"c-escape-str",
	0,

	/* CODEC_DIN_66303 */
	"din-66303",
	"drv8",
	0,

	/* CODEC_DK_US */
	"dk-us",
	"csdkus",
	0,

	/* CODEC_EBCDIC_AT_DE */
	"ebcdic-at-de",
	"csibmebcdicatde",
	"csebcdicatde",
	"ebcdicatde",
	0,

	/* CODEC_EBCDIC_AT_DE_A */
	"ebcdic-at-de-a",
	"csebcdicatdea",
	"ebcdicatdea",
	0,

	/* CODEC_EBCDIC_CA_FR */
	"ebcdic-ca-fr",
	"csebcdiccafr",
	"ebcdiccafr",
	0,

	/* CODEC_EBCDIC_CP_DK_NO */
	"ibm277",
	"cp277",
	"ebcdic-cp-dk",
	"ebcdic-cp-no",
	"csibm277",
	"osf10020115",
	0,

	/* CODEC_EBCDIC_DK_NO */
	"ebcdic-dk-no",
	"csebcdicdkno",
	"ebcdicdkno",
	0,

	/* CODEC_EBCDIC_DK_NO_A */
	"ebcdic-dk-no-a",
	"csebcdicdknoa",
	"ebcdicdknoa",
	0,

	/* CODEC_EBCDIC_ES */
	"ebcdic-es",
	"csebcdices",
	"ebcdices",
	0,

	/* CODEC_EBCDIC_ES_A */
	"ebcdic-es-a",
	"csebcdicesa",
	"ebcdicesa",
	0,

	/* CODEC_EBCDIC_ES_S */
	"ebcdic-es-s",
	"csebcdicess",
	0,

	/* CODEC_EBCDIC_FI_SE */
	"ebcdic-fi-se",
	"csebcdicfise",
	"ebcdicfise",
	0,

	/* CODEC_EBCDIC_FI_SE_A */
	"ebcdic-fi-se-a",
	"csebcdicfisea",
	"ebcdicfisea",
	0,

	/* CODEC_EBCDIC_FR */
	"ebcdic-fr",
	"csebcdicfr",
	"ebcdicfr",
	0,

	/* CODEC_EBCDIC_IS_FRISS */
	"ebcdic-is-friss",
	"ebcdicisfriss",
	0,

	/* CODEC_EBCDIC_IT */
	"ebcdic-it",
	"csebcdicit",
	"ebcdicit",
	0,

	/* CODEC_EBCDIC_PT */
	"ebcdic-pt",
	"csebcdicpt",
	"ebcdicpt",
	0,

	/* CODEC_EBCDIC_UK */
	"ebcdic-uk",
	"csebcdicuk",
	"ebcdicuk",
	0,

	/* CODEC_EBCDIC_US */
	"ebcdic-us",
	"csebcdicus",
	"ebcdicus",
	0,

	/* CODEC_EXTENDED_LATIN_8 */
	"extended-latin-8",
	0,

	/* CODEC_GBCD */
	"gbcd",
	0,

	/* CODEC_GEORGIAN_ACADEMY */
	"georgian-academy",
	0,

	/* CODEC_GEORGIAN_PS */
	"georgian-ps",
	0,

	/* CODEC_HEX_LOWER */
	"hex-lower",
	0,

	/* CODEC_HEX_UPPER */
	"hex-upper",
	"hex",
	0,

	/* CODEC_HP_GREEK8 */
	"hp-greek8",
	"hpgreek8",
	"osf10010004",
	0,

	/* CODEC_HP_ROMAN8 */
	"hp-roman8",
	"roman8",
	"r8",
	"cshproman8",
	"osf10010001",
	"hproman8",
	"cp1050",
	"ibm1050",
	"hp-roman-8",
	"cp1051",
	"ibm1051",
	0,

	/* CODEC_HP_ROMAN9 */
	"hp-roman9",
	"roman9",
	"r9",
	"hproman9",
	0,

	/* CODEC_HP_THAI8 */
	"hp-thai8",
	"hpthai8",
	"thai8",
	0,

	/* CODEC_HP_TURKISH8 */
	"hp-turkish8",
	"hpturkish8",
	"turkish8",
	"osf10010006",
	0,

	/* CODEC_IBM1364 */
	"ibm1364",
	"cp1364",
	"csibm1364",
	0,

	/* CODEC_IBM1371 */
	"ibm1371",
	"cp1371",
	"csibm1371",
	0,

	/* CODEC_IBM1388 */
	"ibm1388",
	"cp1388",
	"csibm1388",
	0,

	/* CODEC_IBM1390 */
	"ibm1390",
	"cp1390",
	"csibm1390",
	0,

	/* CODEC_IBM1399 */
	"ibm1399",
	"cp1399",
	"csibm1399",
	0,

	/* CODEC_IBM1401 */
	"ibm1401",
	0,

	/* CODEC_IBM256 */
	"ibm256",
	"ebcdic-int1",
	0,

	/* CODEC_IBM704 */
	"ibm704",
	0,

	/* CODEC_IBM7090 */
	"ibm7090",
	"ibm7094",
	0,

	/* CODEC_IBM930 */
	"ibm930",
	"cp930",
	"csibm930",
	"x-ibm930",
	"930",
	0,

	/* CODEC_IBM933 */
	"ibm933",
	"cp933",
	"csibm933",
	0,

	/* CODEC_IBM935 */
	"ibm935",
	"cp935",
	"csibm935",
	0,

	/* CODEC_IBM937 */
	"ibm937",
	"cp937",
	"csibm937",
	0,

	/* CODEC_IBM939 */
	"ibm939",
	"cp939",
	"csibm939",
	"x-ibm939",
	"939",
	0,

	/* CODEC_ISIRI3342 */
	"isiri3342",
	"isiri-3342",
	0,

	/* CODEC_ISO5426 */
	"iso5426",
	0,

	/* CODEC_ISO5426_2 */
	"iso5426-2",
	0,

	/* CODEC_ISO6438 */
	"iso6438",
	0,

	/* CODEC_ISO646_BASIC */
	"iso646.basic:1983",
	"ref",
	0,

	/* CODEC_ISO646_CA */
	"csa-z243.4-1985-1",
	"iso-ir-121",
	"iso646-ca",
	"csa7-1",
	"ca",
	"csiso121canadian1",
	"csa-z243.419851",
	"cp1020",
	"csa71",
	0,

	/* CODEC_ISO646_CA2 */
	"csa-z243.4-1985-2",
	"iso-ir-122",
	"iso646-ca2",
	"csa7-2",
	"csiso122canadian2",
	"csa-z243.419852",
	"csa72",
	0,

	/* CODEC_ISO646_CN */
	"gb-1988-80",
	"iso-ir-57",
	"cn",
	"iso646-cn",
	"csiso57gb1988",
	"csiso58gb1988",
	"gb-198880",
	0,

	/* CODEC_ISO646_CU */
	"nc-nc0-10:81",
	"cuba",
	"iso-ir-151",
	"iso646-cu",
	"nc-nc0-10",
	"csiso151cuba",
	"nc-nc10",
	0,

	/* CODEC_ISO646_DE */
	"din-66003",
	"iso-ir-21",
	"de",
	"iso646-de",
	"ibm1011",
	"ms-10206",
	"csiso21german",
	"german",
	"d7dec",
	"cp1011",
	"cp20106",
	"windows-20106",
	0,

	/* CODEC_ISO646_DK */
	"ds-2089",
	"ds2089",
	"iso646-dk",
	"dk",
	"csiso646danish",
	"cp1017",
	"ibm1017",
	0,

	/* CODEC_ISO646_DK_NO_ALT_NRCS */
	"cp1107",
	"ibm1107",
	0,

	/* CODEC_ISO646_DK_NO_NRCS */
	"cp1105",
	"ibm1105",
	0,

	/* CODEC_ISO646_ES */
	"es",
	"iso-ir-17",
	"iso646-es",
	"csiso17spanish",
	"cp1023",
	"e7dec",
	0,

	/* CODEC_ISO646_ES2 */
	"es2",
	"iso-ir-85",
	"iso646-es2",
	"csiso85spanish2",
	"cp1014",
	"ibm1014",
	0,

	/* CODEC_ISO646_FI_NRCS */
	"cp1103",
	"ibm1103",
	0,

	/* CODEC_ISO646_FR */
	"nf-z-62-10",
	"iso-ir-69",
	"iso646-fr",
	"fr",
	"nf-z-62-10-1983",
	"nf-z-62-10-(1983)",
	"csiso69french",
	"nf-z-62010",
	"cp1010",
	"ibm1010",
	0,

	/* CODEC_ISO646_FR1 */
	"nf-z-62-10-(1973)",
	"iso-ir-25",
	"iso646-fr1",
	"nf-z-62-10-1973",
	"csiso25french",
	"nf-z-62010-1973",
	"cp1104",
	"f7dec",
	0,

	/* CODEC_ISO646_GB */
	"bs-4730",
	"iso-ir-4",
	"iso646-gb",
	"gb",
	"uk",
	"csiso4unitedkingdom",
	"cp1013",
	"ibm1013",
	0,

	/* CODEC_ISO646_GB_NRCS */
	"cp1101",
	"ibm1101",
	0,

	/* CODEC_ISO646_HU */
	"msz-7795.3",
	"iso-ir-86",
	"iso646-hu",
	"hu",
	"csiso86hungarian",
	0,

	/* CODEC_ISO646_IE */
	"iso646-ie",
	"iso-ir-207",
	0,

	/* CODEC_ISO646_INIS_SUBSET */
	"inis",
	"iso-ir-49",
	"csiso49inis",
	0,

	/* CODEC_ISO646_INV */
	"iso-ir-170",
	"invariant",
	0,

	/* CODEC_ISO646_IRV_1983 */
	"cp1009",
	"ibm1009",
	"cp20105",
	"windows-20105",
	"koi7-n0",
	0,

	/* CODEC_ISO646_IS */
	"iso646-is",
	0,

	/* CODEC_ISO646_IT */
	"it",
	"iso-ir-15",
	"iso646-it",
	"csiso15italian",
	"cp1012",
	"ibm1012",
	"i7dec",
	0,

	/* CODEC_ISO646_JP */
	"jis-c6220-1969-ro",
	"iso-ir-14",
	"jp",
	"iso646-jp",
	"csiso14jisc6220ro",
	"jis-c62201969ro",
	"cp895",
	"ibm895",
	0,

	/* CODEC_ISO646_JP_OCR_B */
	"jis-c6229-1984-b",
	"iso-ir-92",
	"iso646-jp-ocr-b",
	"jp-ocr-b",
	"csiso92jisc62991984b",
	"jis-c62291984b",
	0,

	/* CODEC_ISO646_KR */
	"ksc5636",
	"iso646-kr",
	"csksc5636",
	"ks-x-1003",
	"ksc5636-1989",
	0,

	/* CODEC_ISO646_LATIN_GR_MIXED */
	"latin-greek-1",
	"latingreek1",
	"iso-ir-27",
	"csiso27latingreek1",
	0,

	/* CODEC_ISO646_MT */
	"iso646-mt",
	0,

	/* CODEC_ISO646_NATS_DANO */
	"nats-dano",
	"iso-ir-9-1",
	"cp1016",
	"ibm1016",
	"csnatsdano",
	"natsdano",
	0,

	/* CODEC_ISO646_NL */
	"iso646-nl",
	"cp1019",
	"ibm1019",
	0,

	/* CODEC_ISO646_NL_NRCS */
	"cp1102",
	"ibm1102",
	0,

	/* CODEC_ISO646_NO */
	"ns-4551-1",
	"iso-ir-60",
	"iso646-no",
	"no",
	"csiso60danishnorwegian",
	"csiso60norwegian1",
	"ns-45511",
	0,

	/* CODEC_ISO646_NO2 */
	"ns-4551-2",
	"iso646-no2",
	"iso-ir-61",
	"no2",
	"csiso61norwegian2",
	"ns-45512",
	0,

	/* CODEC_ISO646_PL */
	"bn-74/3101-1",
	0,

	/* CODEC_ISO646_PT */
	"pt",
	"iso-ir-16",
	"iso646-pt",
	"csiso16portugese",
	"csiso16portuguese",
	0,

	/* CODEC_ISO646_PT2 */
	"pt2",
	"iso-ir-84",
	"iso646-pt2",
	"csiso84portuguese2",
	"cp1015",
	"ibm1015",
	0,

	/* CODEC_ISO646_SE */
	"sen-850200-b",
	"iso-ir-10",
	"fi",
	"iso646-fi",
	"iso646-se",
	"se",
	"csiso10swedish",
	"ss636127",
	"cp1018",
	"ibm1018",
	0,

	/* CODEC_ISO646_SE2 */
	"sen-850200-c",
	"iso-ir-11",
	"iso646-se2",
	"se2",
	"csiso11swedishfornames",
	0,

	/* CODEC_ISO646_SEFI_NATS */
	"iso-ir-8",
	0,

	/* CODEC_ISO646_SE_NRCS */
	"cp1106",
	"ibm1106",
	0,

	/* CODEC_ISO646_SWI_NRCS */
	"cp1021",
	"ibm1021",
	"ch7dec",
	0,

	/* CODEC_ISO646_T_61 */
	"t.61-7bit",
	"iso-ir-102",
	"csiso102t617bit",
	0,

	/* CODEC_ISO646_VIEWDATA */
	"bs-viewdata",
	"iso-ir-47",
	"csiso47bsviewdata",
	0,

	/* CODEC_ISO646_YU */
	"jus-i.b1.2",
	"iso-ir-141",
	"iso646-yu",
	"js",
	"yu",
	"csiso141jusib1002",
	0,

	/* CODEC_ISO_5427 */
	"iso5427",
	"iso-ir-37",
	"koi7",
	"koi7-n1",
	"koi0",
	"csiso5427cyrillic",
	0,

	/* CODEC_ISO_6937_2 */
	"iso6937-2",
	"iso69372",
	"iso6937-2:1983",
	"iso-ir-90",
	"csiso90",
	0,

	/* CODEC_ISO_8859_1 */
	"iso8859-1:1987",
	"iso-ir-100",
	"iso8859-1",
	"latin1",
	"l1",
	"ibm819",
	"cp819",
	"iso88591",
	"csisolatin1",
	"cp28591",
	"windows-28591",
	"we8iso8859p1",
	"cp38591",
	"windows-38591",
	"iso8859-1-i",
	"8859-1",
	"osf10001",
	0,

	/* CODEC_ISO_8859_10 */
	"latin6",
	"iso-ir-157",
	"l6",
	"8859-10",
	"iso8859-10",
	"iso8859-10:1992",
	"iso885910",
	"csisolatin6",
	"ibm919",
	"cp919",
	"cp28600",
	"windows-28600",
	"osf1000a",
	0,

	/* CODEC_ISO_8859_11 */
	"iso8859-11",
	"iso885911",
	"cp28601",
	"windows-28601",
	"iso-ir-166",
	"tis-620",
	"cstis620",
	"tis620",
	"tis620-0",
	"tis620.2529-1",
	"tis620.2533-0",
	"x-iso-8859-11",
	"tis620.2533",
	0,

	/* CODEC_ISO_8859_14 */
	"iso8859-14",
	"iso8859-14:1998",
	"iso885914",
	"iso-ir-199",
	"iso-celtic",
	"latin8",
	"l8",
	"cp28604",
	"windows-28604",
	"csiso885914",
	"8859-14",
	"isoceltic",
	0,

	/* CODEC_ISO_8859_15 */
	"iso8859-15",
	"iso8859-15:1998",
	"iso885915",
	"iso-ir-203",
	"latin9",
	"latin0",
	"ibm923",
	"cp923",
	"cp28605",
	"windows-28605",
	"csiso885915",
	"l9",
	"csisolatin9",
	"iso8859-15-fdis",
	0,

	/* CODEC_ISO_8859_16 */
	"iso8859-16",
	"iso8859-16:2001",
	"iso885916",
	"iso-ir-226",
	"latin10",
	"l10",
	"sr-14111",
	"cp28606",
	"windows-28606",
	"csiso885916",
	"8859-16",
	0,

	/* CODEC_ISO_8859_2 */
	"iso8859-2:1987",
	"iso-ir-101",
	"iso8859-2",
	"latin2",
	"l2",
	"iso88592",
	"csisolatin2",
	"ibm1111",
	"cp1111",
	"cp28592",
	"windows-28592",
	"8859-2",
	"osf10002",
	"cp912",
	"ibm912",
	0,

	/* CODEC_ISO_8859_3 */
	"iso8859-3:1988",
	"iso-ir-109",
	"iso8859-3",
	"latin3",
	"l3",
	"iso88593",
	"csisolatin3",
	"ibm913",
	"cp913",
	"cp28593",
	"windows-28593",
	"8859-3",
	"osf10003",
	0,

	/* CODEC_ISO_8859_4 */
	"iso8859-4:1988",
	"iso-ir-110",
	"iso8859-4",
	"latin4",
	"l4",
	"iso88594",
	"csisolatin4",
	"ibm914",
	"cp914",
	"cp28594",
	"windows-28594",
	"8859-4",
	"osf10004",
	0,

	/* CODEC_ISO_8859_5 */
	"iso8859-5:1988",
	"iso-ir-144",
	"iso8859-5",
	"cyrillic",
	"iso88595",
	"csisolatincyrillic",
	"cp28595",
	"windows-28595",
	"8859-5",
	"osf10005",
	"cp915",
	"ibm915",
	0,

	/* CODEC_ISO_8859_6 */
	"iso8859-6:1987",
	"iso-ir-127",
	"iso8859-6",
	"ecma-114",
	"asmo-708",
	"arabic",
	"iso88596",
	"csisolatinarabic",
	"ibm1089",
	"cp1089",
	"cp28596",
	"windows-28596",
	"cp38596",
	"windows-38596",
	"iso8859-6-i",
	"8859-6",
	"osf10006",
	0,

	/* CODEC_ISO_8859_7 */
	"iso8859-7:1987",
	"iso-ir-126",
	"iso8859-7",
	"elot-928",
	"ecma-118",
	"greek",
	"greek8",
	"iso8859-7:2003",
	"csisolatingreek",
	"ibm813",
	"cp813",
	"cp28597",
	"windows-28597",
	"iso88597",
	"8859-7",
	"osf10007",
	0,

	/* CODEC_ISO_8859_8 */
	"iso8859-8:1988",
	"iso-ir-138",
	"iso8859-8",
	"hebrew",
	"iso88598",
	"csisolatinhebrew",
	"ibm916",
	"cp916",
	"cp28598",
	"windows-28598",
	"cp38598",
	"windows-38598",
	"iso8859-8-i",
	"8859-8",
	"osf10008",
	0,

	/* CODEC_ISO_8859_9 */
	"iso8859-9:1989",
	"iso-ir-148",
	"iso8859-9",
	"latin5",
	"l5",
	"iso88599",
	"csisolatin5",
	"ibm920",
	"cp920",
	"cp28599",
	"windows-28599",
	"8859-9",
	"osf10009",
	"ts-5881",
	"ecma-128",
	0,

	/* CODEC_ISO_8859_9E */
	"iso8859-9e",
	"iso88599e",
	0,

	/* CODEC_ISO_IR_123 */
	"csa-z243.4-1985-gr",
	"iso-ir-123",
	"csiso123csaz24341985gr",
	0,

	/* CODEC_ISO_IR_13 */
	"jis-c6220-1969-jp",
	"jis-c6220-1969",
	"iso-ir-13",
	"katakana",
	"x201-7",
	"csiso13jisc6220jp",
	0,

	/* CODEC_ISO_IR_139 */
	"csn-369103",
	"iso-ir-139",
	"csiso139csn369103",
	0,

	/* CODEC_ISO_IR_143 */
	"iec-p27-1",
	"iso-ir-143",
	"csiso143iecp271",
	"iec-p271",
	0,

	/* CODEC_ISO_IR_146 */
	"jus-i.b1.3-serb",
	"iso-ir-146",
	"serbian",
	"csiso146serbian",
	0,

	/* CODEC_ISO_IR_147 */
	"jus-i.b1.3-mac",
	"macedonian",
	"iso-ir-147",
	"csiso147macedonian",
	0,

	/* CODEC_ISO_IR_150 */
	"greek-ccitt",
	"iso-ir-150",
	"csiso150",
	"csiso150greekccitt",
	"greekccitt",
	0,

	/* CODEC_ISO_IR_152 */
	"iso6937-2-25",
	"iso-ir-152",
	"csiso6937add",
	0,

	/* CODEC_ISO_IR_153 */
	"gost-19768-74",
	"st-sev-358-88",
	"iso-ir-153",
	"csiso153gost1976874",
	"gost-19768",
	"gost-1976874",
	0,

	/* CODEC_ISO_IR_154 */
	"iso8859-supp",
	"iso-ir-154",
	"latin1-2-5",
	"csiso8859supp",
	0,

	/* CODEC_ISO_IR_155 */
	"iso10367-box",
	"iso10367box",
	"iso-ir-155",
	"csiso10367box",
	0,

	/* CODEC_ISO_IR_158 */
	"latin-lap",
	"lap",
	"iso-ir-158",
	"csiso158lap",
	0,

	/* CODEC_ISO_IR_18 */
	"greek7-old",
	"greek7old",
	"iso-ir-18",
	"csiso18greek7old",
	0,

	/* CODEC_ISO_IR_182 */
	"iso-ir-182",
	0,

	/* CODEC_ISO_IR_19 */
	"latin-greek",
	"iso-ir-19",
	"latingreek",
	"csiso19latingreek",
	0,

	/* CODEC_ISO_IR_197 */
	"iso-ir-197",
	0,

	/* CODEC_ISO_IR_2 */
	"iso646.irv:1983",
	"iso-ir-2",
	"irv",
	"csiso2intlrefversion",
	0,

	/* CODEC_ISO_IR_200 */
	"iso-ir-200",
	0,

	/* CODEC_ISO_IR_201 */
	"iso-ir-201",
	0,

	/* CODEC_ISO_IR_209 */
	"iso-ir-209",
	0,

	/* CODEC_ISO_IR_50 */
	"inis-8",
	"inis8",
	"iso-ir-50",
	"csiso50inis8",
	0,

	/* CODEC_ISO_IR_51 */
	"inis-cyrillic",
	"iniscyrillic",
	"iso-ir-51",
	"csiso51iniscyrillic",
	0,

	/* CODEC_ISO_IR_54 */
	"iso5427:1981",
	"iso-ir-54",
	"iso5427cyrillic1981",
	"csiso54271981",
	"iso5427-ext",
	"iso5427ext",
	"csiso5427cyrillic1981",
	0,

	/* CODEC_ISO_IR_55 */
	"iso5428:1980",
	"iso5428",
	"iso-ir-55",
	"csiso5428greek",
	0,

	/* CODEC_ISO_IR_68 */
	"iso-ir-68",
	0,

	/* CODEC_ISO_IR_88 */
	"greek7",
	"iso-ir-88",
	"csiso88greek7",
	0,

	/* CODEC_ISO_IR_89 */
	"asmo-449",
	"iso9036",
	"arabic7",
	"iso-ir-89",
	0,

	/* CODEC_ISO_IR_8_1 */
	"nats-sefi",
	"natssefi",
	"iso-ir-8-1",
	"csnatssefi",
	0,

	/* CODEC_ISO_IR_8_2 */
	"nats-sefi-add",
	"iso-ir-8-2",
	0,

	/* CODEC_ISO_IR_91 */
	"jis-c6229-1984-a",
	"iso-ir-91",
	"jp-ocr-a",
	"csiso91jisc62291984a",
	0,

	/* CODEC_ISO_IR_93 */
	"jis-c6229-1984-b-add",
	"iso-ir-93",
	"jp-ocr-b-add",
	"csiso93jis62291984badd",
	0,

	/* CODEC_ISO_IR_94 */
	"jis-c6229-1984-hand",
	"iso-ir-94",
	"jp-ocr-hand",
	"csiso94jis62291984hand",
	0,

	/* CODEC_ISO_IR_95 */
	"jis-c6229-1984-hand-add",
	"iso-ir-95",
	"jp-ocr-hand-add",
	"csiso95jis62291984handadd",
	0,

	/* CODEC_ISO_IR_96 */
	"jis-c6229-1984-kana",
	"iso-ir-96",
	"csiso96jisc62291984kana",
	0,

	/* CODEC_ISO_IR_98 */
	"iso2033-1983",
	"iso2033",
	"iso-ir-98",
	"e13b",
	"csiso2033",
	0,

	/* CODEC_ISO_IR_9_2 */
	"nats-dano-add",
	"iso-ir-9-2",
	0,

	/* CODEC_JIS_C_6229_OCR_A */
	"jis-c-6229-ocr-a",
	0,

	/* CODEC_KEYBCS2 */
	"nec-867",
	"dos-895",
	"keybcs2",
	"kamenicky",
	0,

	/* CODEC_KOI7_N2 */
	"koi7-n2",
	"short-koi",
	0,

	/* CODEC_KOI8_B */
	"koi8-b",
	0,

	/* CODEC_KOI8_E */
	"ecma-cyrillic",
	"ecmacyrillic",
	"iso-ir-111",
	"ecma-113",
	"koi8-e",
	"csiso111ecmacyrillic",
	0,

	/* CODEC_KOI8_F */
	"koi8-f",
	"koi8-unified",
	0,

	/* CODEC_KOI8_N1 */
	"koi8-n1",
	0,

	/* CODEC_KOI8_N2 */
	"koi8-n2",
	0,

	/* CODEC_KOI8_R */
	"koi8-r",
	"cp20866",
	"cp878",
	"ibm878",
	"cskoi8r",
	"koi8",
	0,

	/* CODEC_KOI8_RU */
	"koi8-ru",
	"cp1167",
	"ibm1167",
	"csibm1167",
	0,

	/* CODEC_KOI8_T */
	"koi8-t",
	0,

	/* CODEC_KOI8_U */
	"koi8-u",
	"koi8u",
	"cp21866",
	"cp1168",
	"ibm1168",
	"cskoi8u",
	0,

	/* CODEC_KZ_1048 */
	"kz-1048",
	"kz1048",
	"strk1048-2002",
	"rk1048",
	"cskz1048",
	0,

	/* CODEC_LICS */
	"lics",
	0,

	/* CODEC_LY1 */
	"ly1",
	0,

	/* CODEC_MACINTOSH_FONT_X */
	"macintosh-font-x",
	0,

	/* CODEC_MACINTOSH_LATIN */
	"macintosh-latin",
	0,

	/* CODEC_MACIS */
	"macis",
	"mac-is",
	0,

	/* CODEC_MAC_OS_THAI */
	"mac-os-thai",
	0,

	/* CODEC_MAC_SAMI */
	"mac-sami",
	0,

	/* CODEC_MIK */
	"mik",
	"bulgaria-pc",
	0,

	/* CODEC_MSDOS1252 */
	"msdos-1252",
	0,

	/* CODEC_NEXTSTEP */
	"nextstep",
	0,

	/* CODEC_OSD_EBCDIC_DF03_IRV */
	"osd-ebcdic-df3-irv",
	"csosdebcdicdf3irv",
	0,

	/* CODEC_OSD_EBCDIC_DF04_1 */
	"osd-ebcdic-df4-1",
	"csosdebcdicdf41",
	0,

	/* CODEC_OSD_EBCDIC_DF04_15 */
	"osd-ebcdic-df4-15",
	"csosdebcdicdf415",
	0,

	/* CODEC_PALMOS */
	"palmos",
	0,

	/* CODEC_PT154 */
	"ptcp154",
	"csptcp154",
	"pt154",
	"cp154",
	"cyrillic-asian",
	"ibm1169",
	0,

	/* CODEC_URI_ESCAPE */
	"uri-escape",
	"url-escape",
	"percent-encoding",
	"url-encoding",
	0,

	/* CODEC_US_DK */
	"us-dk",
	"csusdk",
	0,

	/* CODEC_UTF16BE */
	"utf16be",
	"utf-16be",
	"ucs-2be",
	"unicodebig",
	"csutf16be",
	"x-unicodebig",
	"unicodebigunmarked",
	"x-utf-16be",
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	"utf16",
	"utf-16",
	"csutf16",
	"iso10646/ucs2",
	"iso10646-ucs-2",
	"unicode",
	"csunicode",
	"ucs2",
	"ucs-2",
	"osf10100",
	"osf10101",
	"osf10102",
	"cp13488",
	"windows-13488",
	"cp1200",
	"cp1201",
#endif /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ && __SIZEOF_WCHAR_T__ == 2
	"wchar-t",
#endif /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ && __SIZEOF_WCHAR_T__ == 2 */
	0,

	/* CODEC_UTF16LE */
	"utf16le",
	"utf-16le",
	"ucs-2le",
	"unicodelittle",
	"csutf16le",
	"x-unicodelittle",
	"x-utf-16le",
	"unicodelittleunmarked",
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	"utf16",
	"utf-16",
	"csutf16",
	"iso10646/ucs2",
	"iso10646-ucs-2",
	"unicode",
	"csunicode",
	"ucs2",
	"ucs-2",
	"osf10100",
	"osf10101",
	"osf10102",
	"cp13488",
	"windows-13488",
	"cp1200",
	"cp1201",
#endif /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ && __SIZEOF_WCHAR_T__ == 2
	"wchar-t",
#endif /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ && __SIZEOF_WCHAR_T__ == 2 */
	0,

	/* CODEC_UTF32BE */
	"utf32be",
	"utf-32be",
	"ucs-4be",
	"cp12001",
	"windows-12001",
	"csutf32be",
	"x-utf-32be",
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	"utf32",
	"utf-32",
	"csutf32",
	"iso10646/ucs4",
	"iso10646-ucs-4",
	"csucs4",
	"ucs4",
	"ucs-4",
	"iso10646",
	"10646-1:1993",
	"10646-1:1993/ucs4",
	"osf10104",
	"osf10105",
	"osf10106",
	"cp12000",
#endif /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ && __SIZEOF_WCHAR_T__ == 4
	"wchar-t",
#endif /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ && __SIZEOF_WCHAR_T__ == 4 */
	0,

	/* CODEC_UTF32LE */
	"utf32le",
	"utf-32le",
	"ucs-4le",
	"csutf32le",
	"x-utf-32le",
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	"utf32",
	"utf-32",
	"csutf32",
	"iso10646/ucs4",
	"iso10646-ucs-4",
	"csucs4",
	"ucs4",
	"ucs-4",
	"iso10646",
	"10646-1:1993",
	"10646-1:1993/ucs4",
	"osf10104",
	"osf10105",
	"osf10106",
	"cp12000",
#endif /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ && __SIZEOF_WCHAR_T__ == 4
	"wchar-t",
#endif /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ && __SIZEOF_WCHAR_T__ == 4 */
	0,

	/* CODEC_UTF8 */
	"utf8",
	"utf-8",
	"iso10646/utf8",
	"iso10646/utf-8",
	"iso-ir-193",
	"osf5010001",
	"cp65001",
	"windows-65001",
	"csutf8",
	0,

	/* CODEC_UTF8_BOM */
	"utf8-bom",
	"utf-8-bom",
	"utf8bom",
	"utf-8bom",
	0,

	/* CODEC_VENTURA_INTERNATIONAL */
	"ventura-international",
	"ventura-int",
	"csventurainternational",
	0,

	/* CODEC_VENTURA_US */
	"ventura-us",
	"csventuraus",
	0,

	/* CODEC_X0201 */
	"jis-x201",
	"x201",
	"cshalfwidthkatakana",
	"jis201",
	0,

	/* CODEC_XML_ESCAPE */
	"xml-escape",
	"html-escape",
	0,

	/* CODEC_X_MAC_ARMENIAN */
	"x-mac-armenian",
	0,

	/* CODEC_X_MAC_BARENTS_CYRILLIC */
	"x-mac-barents-cyrillic",
	0,

	/* CODEC_X_MAC_CELTIC */
	"x-mac-celtic",
	0,

	/* CODEC_X_MAC_CYRILLIC */
	"x-mac-cyrillic",
	0,

	/* CODEC_X_MAC_DEVANAGARI */
	"x-mac-devanagari",
	0,

	/* CODEC_X_MAC_FARSI */
	"x-mac-farsi",
	"macfarsi",
	0,

	/* CODEC_X_MAC_GAELIC */
	"x-mac-gaelic",
	0,

	/* CODEC_X_MAC_GEORGIAN */
	"x-mac-georgian",
	0,

	/* CODEC_X_MAC_GUJARATI */
	"x-mac-gujarati",
	0,

	/* CODEC_X_MAC_GURMUKHI */
	"x-mac-gurmukhi",
	0,

	/* CODEC_X_MAC_INUIT */
	"x-mac-inuit",
	0,

	/* CODEC_X_MAC_MALTESE */
	"x-mac-maltese",
	"x-mac-esperanto",
	0,

	/* CODEC_X_MAC_OGHAM */
	"x-mac-ogham",
	0,

	/* CODEC_X_MAC_SAMI */
	"x-mac-sami",
	0,

	/* CODEC_X_MAC_TURKIC_CYRILLIC */
	"x-mac-turkic-cyrillic",
	0,
};

STATIC_ASSERT((codec_name_db_offset_t)-1 >= sizeof(struct codec_name_db_struct));
#define CODE_NAME_MAXLEN 29
struct codec_db_entry {
	codec_name_db_offset_t cdbe_name;  /* Offset to name within `codec_name_db' */
	iconv_codec_t          cdbe_codec; /* The associated codec. */
};

PRIVATE struct codec_db_entry const codec_db[] = {
	{ offsetof(struct codec_name_db_struct, db_CP1026_3), /*                  "1026"                          */ CODEC_CP1026 },
	{ offsetof(struct codec_name_db_struct, db_CP1046_1), /*                  "1046"                          */ CODEC_CP1046 },
	{ offsetof(struct codec_name_db_struct, db_CP1047_2), /*                  "1047"                          */ CODEC_CP1047 },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_16), /*                "10646-1:1993"                  */ CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_14), /*                "10646-1:1993"                  */ CODEC_UTF32LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_17), /*                "10646-1:1993/ucs4"             */ CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_15), /*                "10646-1:1993/ucs4"             */ CODEC_UTF32LE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_CP1140_2), /*                  "1140"                          */ CODEC_CP1140 },
	{ offsetof(struct codec_name_db_struct, db_CP1141_2), /*                  "1141"                          */ CODEC_CP1141 },
	{ offsetof(struct codec_name_db_struct, db_CP1142_2), /*                  "1142"                          */ CODEC_CP1142 },
	{ offsetof(struct codec_name_db_struct, db_CP1143_2), /*                  "1143"                          */ CODEC_CP1143 },
	{ offsetof(struct codec_name_db_struct, db_CP1144_2), /*                  "1144"                          */ CODEC_CP1144 },
	{ offsetof(struct codec_name_db_struct, db_CP1145_2), /*                  "1145"                          */ CODEC_CP1145 },
	{ offsetof(struct codec_name_db_struct, db_CP1146_2), /*                  "1146"                          */ CODEC_CP1146 },
	{ offsetof(struct codec_name_db_struct, db_CP1147_2), /*                  "1147"                          */ CODEC_CP1147 },
	{ offsetof(struct codec_name_db_struct, db_CP1148_2), /*                  "1148"                          */ CODEC_CP1148 },
	{ offsetof(struct codec_name_db_struct, db_CP1149_2), /*                  "1149"                          */ CODEC_CP1149 },
	{ offsetof(struct codec_name_db_struct, db_CP437_2), /*                   "437"                           */ CODEC_CP437 },
	{ offsetof(struct codec_name_db_struct, db_CP500_5), /*                   "500"                           */ CODEC_CP500 },
	{ offsetof(struct codec_name_db_struct, db_CP500_6), /*                   "500v1"                         */ CODEC_CP500 },
	{ offsetof(struct codec_name_db_struct, db_ASCII_24), /*                  "646"                           */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_CP850_2), /*                   "850"                           */ CODEC_CP850 },
	{ offsetof(struct codec_name_db_struct, db_CP851_2), /*                   "851"                           */ CODEC_CP851 },
	{ offsetof(struct codec_name_db_struct, db_CP852_2), /*                   "852"                           */ CODEC_CP852 },
	{ offsetof(struct codec_name_db_struct, db_CP855_2), /*                   "855"                           */ CODEC_CP855 },
	{ offsetof(struct codec_name_db_struct, db_CP856_2), /*                   "856"                           */ CODEC_CP856 },
	{ offsetof(struct codec_name_db_struct, db_CP857_2), /*                   "857"                           */ CODEC_CP857 },
	{ offsetof(struct codec_name_db_struct, db_CP858_6), /*                   "858"                           */ CODEC_CP858 },
	{ offsetof(struct codec_name_db_struct, db_CP860_2), /*                   "860"                           */ CODEC_CP860 },
	{ offsetof(struct codec_name_db_struct, db_CP861_2), /*                   "861"                           */ CODEC_CP861 },
	{ offsetof(struct codec_name_db_struct, db_CP862_2), /*                   "862"                           */ CODEC_CP862 },
	{ offsetof(struct codec_name_db_struct, db_CP863_2), /*                   "863"                           */ CODEC_CP863 },
	{ offsetof(struct codec_name_db_struct, db_CP864_3), /*                   "864"                           */ CODEC_CP864 },
	{ offsetof(struct codec_name_db_struct, db_CP865_2), /*                   "865"                           */ CODEC_CP865 },
	{ offsetof(struct codec_name_db_struct, db_CP866_1), /*                   "866"                           */ CODEC_CP866 },
	{ offsetof(struct codec_name_db_struct, db_CP866NAV_1), /*                "866nav"                        */ CODEC_CP866NAV },
	{ offsetof(struct codec_name_db_struct, db_CP869_2), /*                   "869"                           */ CODEC_CP869 },
	{ offsetof(struct codec_name_db_struct, db_CP874_3), /*                   "874"                           */ CODEC_CP874 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_1_15), /*             "8859-1"                        */ CODEC_ISO_8859_1 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_10_3), /*             "8859-10"                       */ CODEC_ISO_8859_10 },
	{ offsetof(struct codec_name_db_struct, db_CP921_3), /*                   "8859-13"                       */ CODEC_CP921 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_14_10), /*            "8859-14"                       */ CODEC_ISO_8859_14 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_16_10), /*            "8859-16"                       */ CODEC_ISO_8859_16 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_2_11), /*             "8859-2"                        */ CODEC_ISO_8859_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_3_11), /*             "8859-3"                        */ CODEC_ISO_8859_3 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_4_11), /*             "8859-4"                        */ CODEC_ISO_8859_4 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_5_8), /*              "8859-5"                        */ CODEC_ISO_8859_5 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_6_15), /*             "8859-6"                        */ CODEC_ISO_8859_6 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_7_14), /*             "8859-7"                        */ CODEC_ISO_8859_7 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_8_13), /*             "8859-8"                        */ CODEC_ISO_8859_8 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_9_11), /*             "8859-9"                        */ CODEC_ISO_8859_9 },
	{ offsetof(struct codec_name_db_struct, db_CP904_2), /*                   "904"                           */ CODEC_CP904 },
	{ offsetof(struct codec_name_db_struct, db_CP918_2), /*                   "918"                           */ CODEC_CP918 },
	{ offsetof(struct codec_name_db_struct, db_IBM930_4), /*                  "930"                           */ CODEC_IBM930 },
	{ offsetof(struct codec_name_db_struct, db_IBM939_4), /*                  "939"                           */ CODEC_IBM939 },
	{ offsetof(struct codec_name_db_struct, db_ADOBE_STANDARD_ENCODING_0), /* "adobe-standard-encoding"       */ CODEC_ADOBE_STANDARD_ENCODING },
	{ offsetof(struct codec_name_db_struct, db_ADOBE_SYMBOL_ENCODING_1), /*   "adobe-symbol-encoding"         */ CODEC_ADOBE_SYMBOL_ENCODING },
	{ offsetof(struct codec_name_db_struct, db_ADOBE_ZAPF_DINGBATS_0), /*     "adobe-zapf-dingbats"           */ CODEC_ADOBE_ZAPF_DINGBATS },
	{ offsetof(struct codec_name_db_struct, db_AMIGA_1251_3), /*              "ami-1251"                      */ CODEC_AMIGA_1251 },
	{ offsetof(struct codec_name_db_struct, db_AMIGA_1251_1), /*              "ami1251"                       */ CODEC_AMIGA_1251 },
	{ offsetof(struct codec_name_db_struct, db_AMIGA_1251_0), /*              "amiga-1251"                    */ CODEC_AMIGA_1251 },
	{ offsetof(struct codec_name_db_struct, db_AMIGA_1251_2), /*              "amiga1251"                     */ CODEC_AMIGA_1251 },
	{ offsetof(struct codec_name_db_struct, db_ASCII_10), /*                  "ansi-x3.4"                     */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_ASCII_0), /*                   "ansi-x3.4-1968"                */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_ASCII_2), /*                   "ansi-x3.4-1986"                */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_6_5), /*              "arabic"                        */ CODEC_ISO_8859_6 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_89_2), /*               "arabic7"                       */ CODEC_ISO_IR_89 },
	{ offsetof(struct codec_name_db_struct, db_ASCII_4), /*                   "ascii"                         */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_ASCII_25), /*                  "ascii7"                        */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_89_0), /*               "asmo-449"                      */ CODEC_ISO_IR_89 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_6_4), /*              "asmo-708"                      */ CODEC_ISO_8859_6 },
	{ offsetof(struct codec_name_db_struct, db_ATARIST_0), /*                 "atarist"                       */ CODEC_ATARIST },
	{ offsetof(struct codec_name_db_struct, db_CP921_10), /*                  "baltic"                        */ CODEC_CP921 },
	{ offsetof(struct codec_name_db_struct, db_BCDIC_0), /*                   "bcdic"                         */ CODEC_BCDIC },
	{ offsetof(struct codec_name_db_struct, db_ISO646_PL_0), /*               "bn-74/3101-1"                  */ CODEC_ISO646_PL },
	{ offsetof(struct codec_name_db_struct, db_BRF_0), /*                     "brf"                           */ CODEC_BRF },
	{ offsetof(struct codec_name_db_struct, db_ISO646_GB_0), /*               "bs-4730"                       */ CODEC_ISO646_GB },
	{ offsetof(struct codec_name_db_struct, db_ISO646_VIEWDATA_0), /*         "bs-viewdata"                   */ CODEC_ISO646_VIEWDATA },
	{ offsetof(struct codec_name_db_struct, db_MIK_1), /*                     "bulgaria-pc"                   */ CODEC_MIK },
	{ offsetof(struct codec_name_db_struct, db_BURROUGHS_B5500_0), /*         "burroughs-b5500"               */ CODEC_BURROUGHS_B5500 },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_0), /*                "c-escape"                      */ CODEC_C_ESCAPE },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_ALL_0), /*            "c-escape-all"                  */ CODEC_C_ESCAPE_ALL },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_BYTES_ALL_0), /*      "c-escape-all-bytes"            */ CODEC_C_ESCAPE_BYTES_ALL },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_BYTES_0), /*          "c-escape-bytes"                */ CODEC_C_ESCAPE_BYTES },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_BYTES_ALL_1), /*      "c-escape-bytes-all"            */ CODEC_C_ESCAPE_BYTES_ALL },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_BYTES_CHR_0), /*      "c-escape-bytes-chr"            */ CODEC_C_ESCAPE_BYTES_CHR },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_BYTES_INCHR_1), /*    "c-escape-bytes-inchr"          */ CODEC_C_ESCAPE_BYTES_INCHR },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_BYTES_INSTR_1), /*    "c-escape-bytes-instr"          */ CODEC_C_ESCAPE_BYTES_INSTR },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_BYTES_RAW_0), /*      "c-escape-bytes-raw"            */ CODEC_C_ESCAPE_BYTES_RAW },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_BYTES_STR_0), /*      "c-escape-bytes-str"            */ CODEC_C_ESCAPE_BYTES_STR },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_CHR_0), /*            "c-escape-chr"                  */ CODEC_C_ESCAPE_CHR },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_BYTES_CHR_1), /*      "c-escape-chr-bytes"            */ CODEC_C_ESCAPE_BYTES_CHR },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_INCHR_0), /*          "c-escape-inchr"                */ CODEC_C_ESCAPE_INCHR },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_BYTES_INCHR_0), /*    "c-escape-inchr-bytes"          */ CODEC_C_ESCAPE_BYTES_INCHR },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_INSTR_0), /*          "c-escape-instr"                */ CODEC_C_ESCAPE_INSTR },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_BYTES_INSTR_0), /*    "c-escape-instr-bytes"          */ CODEC_C_ESCAPE_BYTES_INSTR },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_RAW_0), /*            "c-escape-raw"                  */ CODEC_C_ESCAPE_RAW },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_BYTES_RAW_1), /*      "c-escape-raw-bytes"            */ CODEC_C_ESCAPE_BYTES_RAW },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_STR_0), /*            "c-escape-str"                  */ CODEC_C_ESCAPE_STR },
	{ offsetof(struct codec_name_db_struct, db_C_ESCAPE_BYTES_STR_1), /*      "c-escape-str-bytes"            */ CODEC_C_ESCAPE_BYTES_STR },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CA_4), /*               "ca"                            */ CODEC_ISO646_CA },
	{ offsetof(struct codec_name_db_struct, db_CP1140_4), /*                  "ccsid1140"                     */ CODEC_CP1140 },
	{ offsetof(struct codec_name_db_struct, db_CP1141_4), /*                  "ccsid1141"                     */ CODEC_CP1141 },
	{ offsetof(struct codec_name_db_struct, db_CP1142_4), /*                  "ccsid1142"                     */ CODEC_CP1142 },
	{ offsetof(struct codec_name_db_struct, db_CP1143_4), /*                  "ccsid1143"                     */ CODEC_CP1143 },
	{ offsetof(struct codec_name_db_struct, db_CP1144_4), /*                  "ccsid1144"                     */ CODEC_CP1144 },
	{ offsetof(struct codec_name_db_struct, db_CP1145_4), /*                  "ccsid1145"                     */ CODEC_CP1145 },
	{ offsetof(struct codec_name_db_struct, db_CP1146_4), /*                  "ccsid1146"                     */ CODEC_CP1146 },
	{ offsetof(struct codec_name_db_struct, db_CP1147_4), /*                  "ccsid1147"                     */ CODEC_CP1147 },
	{ offsetof(struct codec_name_db_struct, db_CP1148_4), /*                  "ccsid1148"                     */ CODEC_CP1148 },
	{ offsetof(struct codec_name_db_struct, db_CP1149_4), /*                  "ccsid1149"                     */ CODEC_CP1149 },
	{ offsetof(struct codec_name_db_struct, db_CP858_4), /*                   "ccsid858"                      */ CODEC_CP858 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SWI_NRCS_2), /*         "ch7dec"                        */ CODEC_ISO646_SWI_NRCS },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CN_2), /*               "cn"                            */ CODEC_ISO646_CN },
	{ offsetof(struct codec_name_db_struct, db_CP868_2), /*                   "cp-ar"                         */ CODEC_CP868 },
	{ offsetof(struct codec_name_db_struct, db_CP869_3), /*                   "cp-gr"                         */ CODEC_CP869 },
	{ offsetof(struct codec_name_db_struct, db_CWI_2), /*                     "cp-hu"                         */ CODEC_CWI },
	{ offsetof(struct codec_name_db_struct, db_CP861_4), /*                   "cp-is"                         */ CODEC_CP861 },
	{ offsetof(struct codec_name_db_struct, db_CP1275_5), /*                  "cp10000"                       */ CODEC_CP1275 },
	{ offsetof(struct codec_name_db_struct, db_CP1275_9), /*                  "cp10000-macroman"              */ CODEC_CP1275 },
	{ offsetof(struct codec_name_db_struct, db_CP10004_0), /*                 "cp10004"                       */ CODEC_CP10004 },
	{ offsetof(struct codec_name_db_struct, db_CP10006_0), /*                 "cp10006"                       */ CODEC_CP10006 },
	{ offsetof(struct codec_name_db_struct, db_CP10006_3), /*                 "cp10006-macgreek"              */ CODEC_CP10006 },
	{ offsetof(struct codec_name_db_struct, db_CP10007_0), /*                 "cp10007"                       */ CODEC_CP10007 },
	{ offsetof(struct codec_name_db_struct, db_CP10007_6), /*                 "cp10007-maccyrillic"           */ CODEC_CP10007 },
	{ offsetof(struct codec_name_db_struct, db_CP1285_3), /*                  "cp10010"                       */ CODEC_CP1285 },
	{ offsetof(struct codec_name_db_struct, db_CP10017_0), /*                 "cp10017"                       */ CODEC_CP10017 },
	{ offsetof(struct codec_name_db_struct, db_CP1282_3), /*                  "cp10029"                       */ CODEC_CP1282 },
	{ offsetof(struct codec_name_db_struct, db_CP1282_7), /*                  "cp10029-maclatin2"             */ CODEC_CP1282 },
	{ offsetof(struct codec_name_db_struct, db_CP1004_0), /*                  "cp1004"                        */ CODEC_CP1004 },
	{ offsetof(struct codec_name_db_struct, db_CP1006_0), /*                  "cp1006"                        */ CODEC_CP1006 },
	{ offsetof(struct codec_name_db_struct, db_CP1286_3), /*                  "cp10079"                       */ CODEC_CP1286 },
	{ offsetof(struct codec_name_db_struct, db_CP1286_6), /*                  "cp10079-macicelandic"          */ CODEC_CP1286 },
	{ offsetof(struct codec_name_db_struct, db_CP1008_0), /*                  "cp1008"                        */ CODEC_CP1008 },
	{ offsetof(struct codec_name_db_struct, db_CP1281_3), /*                  "cp10081"                       */ CODEC_CP1281 },
	{ offsetof(struct codec_name_db_struct, db_CP1281_6), /*                  "cp10081-macturkish"            */ CODEC_CP1281 },
	{ offsetof(struct codec_name_db_struct, db_CP1284_3), /*                  "cp10082"                       */ CODEC_CP1284 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_IRV_1983_0), /*         "cp1009"                        */ CODEC_ISO646_IRV_1983 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FR_8), /*               "cp1010"                        */ CODEC_ISO646_FR },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DE_9), /*               "cp1011"                        */ CODEC_ISO646_DE },
	{ offsetof(struct codec_name_db_struct, db_ISO646_IT_4), /*               "cp1012"                        */ CODEC_ISO646_IT },
	{ offsetof(struct codec_name_db_struct, db_ISO646_GB_6), /*               "cp1013"                        */ CODEC_ISO646_GB },
	{ offsetof(struct codec_name_db_struct, db_ISO646_ES2_4), /*              "cp1014"                        */ CODEC_ISO646_ES2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_PT2_4), /*              "cp1015"                        */ CODEC_ISO646_PT2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NATS_DANO_2), /*        "cp1016"                        */ CODEC_ISO646_NATS_DANO },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DK_5), /*               "cp1017"                        */ CODEC_ISO646_DK },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SE_8), /*               "cp1018"                        */ CODEC_ISO646_SE },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NL_1), /*               "cp1019"                        */ CODEC_ISO646_NL },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CA_7), /*               "cp1020"                        */ CODEC_ISO646_CA },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SWI_NRCS_0), /*         "cp1021"                        */ CODEC_ISO646_SWI_NRCS },
	{ offsetof(struct codec_name_db_struct, db_ISO646_ES_4), /*               "cp1023"                        */ CODEC_ISO646_ES },
	{ offsetof(struct codec_name_db_struct, db_CP1025_0), /*                  "cp1025"                        */ CODEC_CP1025 },
	{ offsetof(struct codec_name_db_struct, db_CP1026_1), /*                  "cp1026"                        */ CODEC_CP1026 },
	{ offsetof(struct codec_name_db_struct, db_CP1036_0), /*                  "cp1036"                        */ CODEC_CP1036 },
	{ offsetof(struct codec_name_db_struct, db_ADOBE_SYMBOL_ENCODING_3), /*   "cp1038"                        */ CODEC_ADOBE_SYMBOL_ENCODING },
	{ offsetof(struct codec_name_db_struct, db_CP1040_0), /*                  "cp1040"                        */ CODEC_CP1040 },
	{ offsetof(struct codec_name_db_struct, db_CP1041_1), /*                  "cp1041"                        */ CODEC_CP1041 },
	{ offsetof(struct codec_name_db_struct, db_CP1042_0), /*                  "cp1042"                        */ CODEC_CP1042 },
	{ offsetof(struct codec_name_db_struct, db_CP1043_1), /*                  "cp1043"                        */ CODEC_CP1043 },
	{ offsetof(struct codec_name_db_struct, db_CP1046_0), /*                  "cp1046"                        */ CODEC_CP1046 },
	{ offsetof(struct codec_name_db_struct, db_CP1047_0), /*                  "cp1047"                        */ CODEC_CP1047 },
	{ offsetof(struct codec_name_db_struct, db_HP_ROMAN8_6), /*               "cp1050"                        */ CODEC_HP_ROMAN8 },
	{ offsetof(struct codec_name_db_struct, db_HP_ROMAN8_9), /*               "cp1051"                        */ CODEC_HP_ROMAN8 },
	{ offsetof(struct codec_name_db_struct, db_CP1057_0), /*                  "cp1057"                        */ CODEC_CP1057 },
	{ offsetof(struct codec_name_db_struct, db_CP37_8), /*                    "cp1070"                        */ CODEC_CP37 },
	{ offsetof(struct codec_name_db_struct, db_CP284_5), /*                   "cp1079"                        */ CODEC_CP284 },
	{ offsetof(struct codec_name_db_struct, db_CP297_5), /*                   "cp1081"                        */ CODEC_CP297 },
	{ offsetof(struct codec_name_db_struct, db_CP500_8), /*                   "cp1084"                        */ CODEC_CP500 },
	{ offsetof(struct codec_name_db_struct, db_CP1088_1), /*                  "cp1088"                        */ CODEC_CP1088 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_6_9), /*              "cp1089"                        */ CODEC_ISO_8859_6 },
	{ offsetof(struct codec_name_db_struct, db_CP1090_0), /*                  "cp1090"                        */ CODEC_CP1090 },
	{ offsetof(struct codec_name_db_struct, db_CP1097_0), /*                  "cp1097"                        */ CODEC_CP1097 },
	{ offsetof(struct codec_name_db_struct, db_CP1098_0), /*                  "cp1098"                        */ CODEC_CP1098 },
	{ offsetof(struct codec_name_db_struct, db_CP1100_2), /*                  "cp1100"                        */ CODEC_CP1100 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_GB_NRCS_0), /*          "cp1101"                        */ CODEC_ISO646_GB_NRCS },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NL_NRCS_0), /*          "cp1102"                        */ CODEC_ISO646_NL_NRCS },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FI_NRCS_0), /*          "cp1103"                        */ CODEC_ISO646_FI_NRCS },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FR1_6), /*              "cp1104"                        */ CODEC_ISO646_FR1 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DK_NO_NRCS_0), /*       "cp1105"                        */ CODEC_ISO646_DK_NO_NRCS },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SE_NRCS_0), /*          "cp1106"                        */ CODEC_ISO646_SE_NRCS },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DK_NO_ALT_NRCS_0), /*   "cp1107"                        */ CODEC_ISO646_DK_NO_ALT_NRCS },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_2_8), /*              "cp1111"                        */ CODEC_ISO_8859_2 },
	{ offsetof(struct codec_name_db_struct, db_CP1112_0), /*                  "cp1112"                        */ CODEC_CP1112 },
	{ offsetof(struct codec_name_db_struct, db_CP1114_1), /*                  "cp1114"                        */ CODEC_CP1114 },
	{ offsetof(struct codec_name_db_struct, db_CP1115_1), /*                  "cp1115"                        */ CODEC_CP1115 },
	{ offsetof(struct codec_name_db_struct, db_CP1116_0), /*                  "cp1116"                        */ CODEC_CP1116 },
	{ offsetof(struct codec_name_db_struct, db_CP1117_0), /*                  "cp1117"                        */ CODEC_CP1117 },
	{ offsetof(struct codec_name_db_struct, db_CP774_1), /*                   "cp1118"                        */ CODEC_CP774 },
	{ offsetof(struct codec_name_db_struct, db_CP772_3), /*                   "cp1119"                        */ CODEC_CP772 },
	{ offsetof(struct codec_name_db_struct, db_CP1122_0), /*                  "cp1122"                        */ CODEC_CP1122 },
	{ offsetof(struct codec_name_db_struct, db_CP1123_0), /*                  "cp1123"                        */ CODEC_CP1123 },
	{ offsetof(struct codec_name_db_struct, db_CP1124_0), /*                  "cp1124"                        */ CODEC_CP1124 },
	{ offsetof(struct codec_name_db_struct, db_CP1125_0), /*                  "cp1125"                        */ CODEC_CP1125 },
	{ offsetof(struct codec_name_db_struct, db_CP1127_0), /*                  "cp1127"                        */ CODEC_CP1127 },
	{ offsetof(struct codec_name_db_struct, db_CP1258_4), /*                  "cp1129"                        */ CODEC_CP1258 },
	{ offsetof(struct codec_name_db_struct, db_CP1130_0), /*                  "cp1130"                        */ CODEC_CP1130 },
	{ offsetof(struct codec_name_db_struct, db_CP1131_0), /*                  "cp1131"                        */ CODEC_CP1131 },
	{ offsetof(struct codec_name_db_struct, db_CP1132_0), /*                  "cp1132"                        */ CODEC_CP1132 },
	{ offsetof(struct codec_name_db_struct, db_CP1133_0), /*                  "cp1133"                        */ CODEC_CP1133 },
	{ offsetof(struct codec_name_db_struct, db_CP1137_0), /*                  "cp1137"                        */ CODEC_CP1137 },
	{ offsetof(struct codec_name_db_struct, db_CP1140_0), /*                  "cp1140"                        */ CODEC_CP1140 },
	{ offsetof(struct codec_name_db_struct, db_CP1141_0), /*                  "cp1141"                        */ CODEC_CP1141 },
	{ offsetof(struct codec_name_db_struct, db_CP1142_0), /*                  "cp1142"                        */ CODEC_CP1142 },
	{ offsetof(struct codec_name_db_struct, db_CP1143_0), /*                  "cp1143"                        */ CODEC_CP1143 },
	{ offsetof(struct codec_name_db_struct, db_CP1144_0), /*                  "cp1144"                        */ CODEC_CP1144 },
	{ offsetof(struct codec_name_db_struct, db_CP1145_0), /*                  "cp1145"                        */ CODEC_CP1145 },
	{ offsetof(struct codec_name_db_struct, db_CP1146_0), /*                  "cp1146"                        */ CODEC_CP1146 },
	{ offsetof(struct codec_name_db_struct, db_CP1147_0), /*                  "cp1147"                        */ CODEC_CP1147 },
	{ offsetof(struct codec_name_db_struct, db_CP1148_0), /*                  "cp1148"                        */ CODEC_CP1148 },
	{ offsetof(struct codec_name_db_struct, db_CP1149_0), /*                  "cp1149"                        */ CODEC_CP1149 },
	{ offsetof(struct codec_name_db_struct, db_CP1153_0), /*                  "cp1153"                        */ CODEC_CP1153 },
	{ offsetof(struct codec_name_db_struct, db_CP1154_0), /*                  "cp1154"                        */ CODEC_CP1154 },
	{ offsetof(struct codec_name_db_struct, db_CP1155_0), /*                  "cp1155"                        */ CODEC_CP1155 },
	{ offsetof(struct codec_name_db_struct, db_CP1156_0), /*                  "cp1156"                        */ CODEC_CP1156 },
	{ offsetof(struct codec_name_db_struct, db_CP1157_0), /*                  "cp1157"                        */ CODEC_CP1157 },
	{ offsetof(struct codec_name_db_struct, db_CP1158_0), /*                  "cp1158"                        */ CODEC_CP1158 },
	{ offsetof(struct codec_name_db_struct, db_CP1160_0), /*                  "cp1160"                        */ CODEC_CP1160 },
	{ offsetof(struct codec_name_db_struct, db_CP1161_0), /*                  "cp1161"                        */ CODEC_CP1161 },
	{ offsetof(struct codec_name_db_struct, db_CP1162_0), /*                  "cp1162"                        */ CODEC_CP1162 },
	{ offsetof(struct codec_name_db_struct, db_CP1163_0), /*                  "cp1163"                        */ CODEC_CP1163 },
	{ offsetof(struct codec_name_db_struct, db_CP1164_0), /*                  "cp1164"                        */ CODEC_CP1164 },
	{ offsetof(struct codec_name_db_struct, db_CP1166_0), /*                  "cp1166"                        */ CODEC_CP1166 },
	{ offsetof(struct codec_name_db_struct, db_KOI8_RU_1), /*                 "cp1167"                        */ CODEC_KOI8_RU },
	{ offsetof(struct codec_name_db_struct, db_KOI8_U_3), /*                  "cp1168"                        */ CODEC_KOI8_U },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_22), /*                "cp1200"                        */ CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_22), /*                "cp1200"                        */ CODEC_UTF16LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_21), /*                "cp12000"                       */ CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_19), /*                "cp12000"                       */ CODEC_UTF32LE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_3), /*                 "cp12001"                       */ CODEC_UTF32BE },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_23), /*                "cp1201"                        */ CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_23), /*                "cp1201"                        */ CODEC_UTF16LE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_CP1250_0), /*                  "cp1250"                        */ CODEC_CP1250 },
	{ offsetof(struct codec_name_db_struct, db_CP1251_0), /*                  "cp1251"                        */ CODEC_CP1251 },
	{ offsetof(struct codec_name_db_struct, db_CP1252_0), /*                  "cp1252"                        */ CODEC_CP1252 },
	{ offsetof(struct codec_name_db_struct, db_CP1253_0), /*                  "cp1253"                        */ CODEC_CP1253 },
	{ offsetof(struct codec_name_db_struct, db_CP1254_0), /*                  "cp1254"                        */ CODEC_CP1254 },
	{ offsetof(struct codec_name_db_struct, db_CP1255_0), /*                  "cp1255"                        */ CODEC_CP1255 },
	{ offsetof(struct codec_name_db_struct, db_CP1256_0), /*                  "cp1256"                        */ CODEC_CP1256 },
	{ offsetof(struct codec_name_db_struct, db_CP1257_0), /*                  "cp1257"                        */ CODEC_CP1257 },
	{ offsetof(struct codec_name_db_struct, db_CP1258_0), /*                  "cp1258"                        */ CODEC_CP1258 },
	{ offsetof(struct codec_name_db_struct, db_CP1270_0), /*                  "cp1270"                        */ CODEC_CP1270 },
	{ offsetof(struct codec_name_db_struct, db_CP12712_0), /*                 "cp12712"                       */ CODEC_CP12712 },
	{ offsetof(struct codec_name_db_struct, db_CP1275_3), /*                  "cp1275"                        */ CODEC_CP1275 },
	{ offsetof(struct codec_name_db_struct, db_CP1276_0), /*                  "cp1276"                        */ CODEC_CP1276 },
	{ offsetof(struct codec_name_db_struct, db_CP1281_1), /*                  "cp1281"                        */ CODEC_CP1281 },
	{ offsetof(struct codec_name_db_struct, db_CP1282_1), /*                  "cp1282"                        */ CODEC_CP1282 },
	{ offsetof(struct codec_name_db_struct, db_CP10007_2), /*                 "cp1283"                        */ CODEC_CP10007 },
	{ offsetof(struct codec_name_db_struct, db_CP1284_1), /*                  "cp1284"                        */ CODEC_CP1284 },
	{ offsetof(struct codec_name_db_struct, db_CP1285_1), /*                  "cp1285"                        */ CODEC_CP1285 },
	{ offsetof(struct codec_name_db_struct, db_CP1286_1), /*                  "cp1286"                        */ CODEC_CP1286 },
	{ offsetof(struct codec_name_db_struct, db_CP1287_0), /*                  "cp1287"                        */ CODEC_CP1287 },
	{ offsetof(struct codec_name_db_struct, db_CP1288_0), /*                  "cp1288"                        */ CODEC_CP1288 },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_20), /*                "cp13488"                       */ CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_20), /*                "cp13488"                       */ CODEC_UTF16LE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_IBM1364_1), /*                 "cp1364"                        */ CODEC_IBM1364 },
	{ offsetof(struct codec_name_db_struct, db_IBM1371_1), /*                 "cp1371"                        */ CODEC_IBM1371 },
	{ offsetof(struct codec_name_db_struct, db_IBM1388_1), /*                 "cp1388"                        */ CODEC_IBM1388 },
	{ offsetof(struct codec_name_db_struct, db_IBM1390_1), /*                 "cp1390"                        */ CODEC_IBM1390 },
	{ offsetof(struct codec_name_db_struct, db_IBM1399_1), /*                 "cp1399"                        */ CODEC_IBM1399 },
	{ offsetof(struct codec_name_db_struct, db_PT154_3), /*                   "cp154"                         */ CODEC_PT154 },
	{ offsetof(struct codec_name_db_struct, db_CP16804_0), /*                 "cp16804"                       */ CODEC_CP16804 },
	{ offsetof(struct codec_name_db_struct, db_CP17248_0), /*                 "cp17248"                       */ CODEC_CP17248 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_IRV_1983_2), /*         "cp20105"                       */ CODEC_ISO646_IRV_1983 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DE_10), /*              "cp20106"                       */ CODEC_ISO646_DE },
	{ offsetof(struct codec_name_db_struct, db_ASCII_13), /*                  "cp20127"                       */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_CP1036_5), /*                  "cp20261"                       */ CODEC_CP1036 },
	{ offsetof(struct codec_name_db_struct, db_CP20269_0), /*                 "cp20269"                       */ CODEC_CP20269 },
	{ offsetof(struct codec_name_db_struct, db_KOI8_R_1), /*                  "cp20866"                       */ CODEC_KOI8_R },
	{ offsetof(struct codec_name_db_struct, db_KOI8_U_2), /*                  "cp21866"                       */ CODEC_KOI8_U },
	{ offsetof(struct codec_name_db_struct, db_CP273_1), /*                   "cp273"                         */ CODEC_CP273 },
	{ offsetof(struct codec_name_db_struct, db_CP274_2), /*                   "cp274"                         */ CODEC_CP274 },
	{ offsetof(struct codec_name_db_struct, db_CP275_2), /*                   "cp275"                         */ CODEC_CP275 },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_CP_DK_NO_1), /*         "cp277"                         */ CODEC_EBCDIC_CP_DK_NO },
	{ offsetof(struct codec_name_db_struct, db_CP278_1), /*                   "cp278"                         */ CODEC_CP278 },
	{ offsetof(struct codec_name_db_struct, db_CP280_1), /*                   "cp280"                         */ CODEC_CP280 },
	{ offsetof(struct codec_name_db_struct, db_CP281_2), /*                   "cp281"                         */ CODEC_CP281 },
	{ offsetof(struct codec_name_db_struct, db_CP37_9), /*                    "cp282"                         */ CODEC_CP37 },
	{ offsetof(struct codec_name_db_struct, db_CP284_1), /*                   "cp284"                         */ CODEC_CP284 },
	{ offsetof(struct codec_name_db_struct, db_CP285_1), /*                   "cp285"                         */ CODEC_CP285 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_1_9), /*              "cp28591"                       */ CODEC_ISO_8859_1 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_2_9), /*              "cp28592"                       */ CODEC_ISO_8859_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_3_9), /*              "cp28593"                       */ CODEC_ISO_8859_3 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_4_9), /*              "cp28594"                       */ CODEC_ISO_8859_4 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_5_6), /*              "cp28595"                       */ CODEC_ISO_8859_5 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_6_10), /*             "cp28596"                       */ CODEC_ISO_8859_6 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_7_11), /*             "cp28597"                       */ CODEC_ISO_8859_7 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_8_8), /*              "cp28598"                       */ CODEC_ISO_8859_8 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_9_9), /*              "cp28599"                       */ CODEC_ISO_8859_9 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_10_10), /*            "cp28600"                       */ CODEC_ISO_8859_10 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_11_2), /*             "cp28601"                       */ CODEC_ISO_8859_11 },
	{ offsetof(struct codec_name_db_struct, db_CP921_11), /*                  "cp28603"                       */ CODEC_CP921 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_14_7), /*             "cp28604"                       */ CODEC_ISO_8859_14 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_15_8), /*             "cp28605"                       */ CODEC_ISO_8859_15 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_16_7), /*             "cp28606"                       */ CODEC_ISO_8859_16 },
	{ offsetof(struct codec_name_db_struct, db_CP290_1), /*                   "cp290"                         */ CODEC_CP290 },
	{ offsetof(struct codec_name_db_struct, db_CP297_1), /*                   "cp297"                         */ CODEC_CP297 },
	{ offsetof(struct codec_name_db_struct, db_CP3012_0), /*                  "cp3012"                        */ CODEC_CP3012 },
	{ offsetof(struct codec_name_db_struct, db_CP353_0), /*                   "cp353"                         */ CODEC_CP353 },
	{ offsetof(struct codec_name_db_struct, db_CP355_0), /*                   "cp355"                         */ CODEC_CP355 },
	{ offsetof(struct codec_name_db_struct, db_CP357_0), /*                   "cp357"                         */ CODEC_CP357 },
	{ offsetof(struct codec_name_db_struct, db_CP358_0), /*                   "cp358"                         */ CODEC_CP358 },
	{ offsetof(struct codec_name_db_struct, db_CP359_0), /*                   "cp359"                         */ CODEC_CP359 },
	{ offsetof(struct codec_name_db_struct, db_CP359_2), /*                   "cp360"                         */ CODEC_CP359 },
	{ offsetof(struct codec_name_db_struct, db_ASCII_9), /*                   "cp367"                         */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_CP37_1), /*                    "cp37"                          */ CODEC_CP37 },
	{ offsetof(struct codec_name_db_struct, db_CP38_2), /*                    "cp38"                          */ CODEC_CP38 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_1_12), /*             "cp38591"                       */ CODEC_ISO_8859_1 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_6_12), /*             "cp38596"                       */ CODEC_ISO_8859_6 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_8_10), /*             "cp38598"                       */ CODEC_ISO_8859_8 },
	{ offsetof(struct codec_name_db_struct, db_CP420_1), /*                   "cp420"                         */ CODEC_CP420 },
	{ offsetof(struct codec_name_db_struct, db_CP423_1), /*                   "cp423"                         */ CODEC_CP423 },
	{ offsetof(struct codec_name_db_struct, db_CP424_1), /*                   "cp424"                         */ CODEC_CP424 },
	{ offsetof(struct codec_name_db_struct, db_CP437_1), /*                   "cp437"                         */ CODEC_CP437 },
	{ offsetof(struct codec_name_db_struct, db_CP4517_0), /*                  "cp4517"                        */ CODEC_CP4517 },
	{ offsetof(struct codec_name_db_struct, db_CP4899_0), /*                  "cp4899"                        */ CODEC_CP4899 },
	{ offsetof(struct codec_name_db_struct, db_CP4909_0), /*                  "cp4909"                        */ CODEC_CP4909 },
	{ offsetof(struct codec_name_db_struct, db_CP4971_0), /*                  "cp4971"                        */ CODEC_CP4971 },
	{ offsetof(struct codec_name_db_struct, db_CP896_2), /*                   "cp4992"                        */ CODEC_CP896 },
	{ offsetof(struct codec_name_db_struct, db_CP500_1), /*                   "cp500"                         */ CODEC_CP500 },
	{ offsetof(struct codec_name_db_struct, db_CP1008_3), /*                  "cp5104"                        */ CODEC_CP1008 },
	{ offsetof(struct codec_name_db_struct, db_CP5347_0), /*                  "cp5347"                        */ CODEC_CP5347 },
	{ offsetof(struct codec_name_db_struct, db_UTF8_6), /*                    "cp65001"                       */ CODEC_UTF8 },
	{ offsetof(struct codec_name_db_struct, db_CP667_1), /*                   "cp667"                         */ CODEC_CP667 },
	{ offsetof(struct codec_name_db_struct, db_CP668_0), /*                   "cp668"                         */ CODEC_CP668 },
	{ offsetof(struct codec_name_db_struct, db_CP708_0), /*                   "cp708"                         */ CODEC_CP708 },
	{ offsetof(struct codec_name_db_struct, db_CP720_0), /*                   "cp720"                         */ CODEC_CP720 },
	{ offsetof(struct codec_name_db_struct, db_CP737_0), /*                   "cp737"                         */ CODEC_CP737 },
	{ offsetof(struct codec_name_db_struct, db_CP770_0), /*                   "cp770"                         */ CODEC_CP770 },
	{ offsetof(struct codec_name_db_struct, db_CP771_0), /*                   "cp771"                         */ CODEC_CP771 },
	{ offsetof(struct codec_name_db_struct, db_CP772_0), /*                   "cp772"                         */ CODEC_CP772 },
	{ offsetof(struct codec_name_db_struct, db_CP773_0), /*                   "cp773"                         */ CODEC_CP773 },
	{ offsetof(struct codec_name_db_struct, db_CP774_0), /*                   "cp774"                         */ CODEC_CP774 },
	{ offsetof(struct codec_name_db_struct, db_CP775_0), /*                   "cp775"                         */ CODEC_CP775 },
	{ offsetof(struct codec_name_db_struct, db_CP667_2), /*                   "cp790"                         */ CODEC_CP667 },
	{ offsetof(struct codec_name_db_struct, db_CP803_0), /*                   "cp803"                         */ CODEC_CP803 },
	{ offsetof(struct codec_name_db_struct, db_CP806_0), /*                   "cp806"                         */ CODEC_CP806 },
	{ offsetof(struct codec_name_db_struct, db_CP808_1), /*                   "cp808"                         */ CODEC_CP808 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_7_10), /*             "cp813"                         */ CODEC_ISO_8859_7 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_1_6), /*              "cp819"                         */ CODEC_ISO_8859_1 },
	{ offsetof(struct codec_name_db_struct, db_CP848_0), /*                   "cp848"                         */ CODEC_CP848 },
	{ offsetof(struct codec_name_db_struct, db_CP849_0), /*                   "cp849"                         */ CODEC_CP849 },
	{ offsetof(struct codec_name_db_struct, db_CP850_1), /*                   "cp850"                         */ CODEC_CP850 },
	{ offsetof(struct codec_name_db_struct, db_CP851_1), /*                   "cp851"                         */ CODEC_CP851 },
	{ offsetof(struct codec_name_db_struct, db_CP852_1), /*                   "cp852"                         */ CODEC_CP852 },
	{ offsetof(struct codec_name_db_struct, db_CP853_0), /*                   "cp853"                         */ CODEC_CP853 },
	{ offsetof(struct codec_name_db_struct, db_CP855_1), /*                   "cp855"                         */ CODEC_CP855 },
	{ offsetof(struct codec_name_db_struct, db_CP856_0), /*                   "cp856"                         */ CODEC_CP856 },
	{ offsetof(struct codec_name_db_struct, db_CP857_1), /*                   "cp857"                         */ CODEC_CP857 },
	{ offsetof(struct codec_name_db_struct, db_CP858_0), /*                   "cp858"                         */ CODEC_CP858 },
	{ offsetof(struct codec_name_db_struct, db_CP859_0), /*                   "cp859"                         */ CODEC_CP859 },
	{ offsetof(struct codec_name_db_struct, db_CP860_1), /*                   "cp860"                         */ CODEC_CP860 },
	{ offsetof(struct codec_name_db_struct, db_CP861_1), /*                   "cp861"                         */ CODEC_CP861 },
	{ offsetof(struct codec_name_db_struct, db_CP862_1), /*                   "cp862"                         */ CODEC_CP862 },
	{ offsetof(struct codec_name_db_struct, db_CP863_1), /*                   "cp863"                         */ CODEC_CP863 },
	{ offsetof(struct codec_name_db_struct, db_CP864_1), /*                   "cp864"                         */ CODEC_CP864 },
	{ offsetof(struct codec_name_db_struct, db_CP865_1), /*                   "cp865"                         */ CODEC_CP865 },
	{ offsetof(struct codec_name_db_struct, db_CP866_0), /*                   "cp866"                         */ CODEC_CP866 },
	{ offsetof(struct codec_name_db_struct, db_CP866NAV_0), /*                "cp866nav"                      */ CODEC_CP866NAV },
	{ offsetof(struct codec_name_db_struct, db_CP1125_2), /*                  "cp866u"                        */ CODEC_CP1125 },
	{ offsetof(struct codec_name_db_struct, db_CP867_1), /*                   "cp867"                         */ CODEC_CP867 },
	{ offsetof(struct codec_name_db_struct, db_CP868_1), /*                   "cp868"                         */ CODEC_CP868 },
	{ offsetof(struct codec_name_db_struct, db_CP869_1), /*                   "cp869"                         */ CODEC_CP869 },
	{ offsetof(struct codec_name_db_struct, db_CP870_1), /*                   "cp870"                         */ CODEC_CP870 },
	{ offsetof(struct codec_name_db_struct, db_CP871_1), /*                   "cp871"                         */ CODEC_CP871 },
	{ offsetof(struct codec_name_db_struct, db_CP872_0), /*                   "cp872"                         */ CODEC_CP872 },
	{ offsetof(struct codec_name_db_struct, db_CP874_0), /*                   "cp874"                         */ CODEC_CP874 },
	{ offsetof(struct codec_name_db_struct, db_CP875_0), /*                   "cp875"                         */ CODEC_CP875 },
	{ offsetof(struct codec_name_db_struct, db_KOI8_R_2), /*                  "cp878"                         */ CODEC_KOI8_R },
	{ offsetof(struct codec_name_db_struct, db_CP880_1), /*                   "cp880"                         */ CODEC_CP880 },
	{ offsetof(struct codec_name_db_struct, db_ASCII_16), /*                  "cp891"                         */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_ISO646_JP_6), /*               "cp895"                         */ CODEC_ISO646_JP },
	{ offsetof(struct codec_name_db_struct, db_CP896_0), /*                   "cp896"                         */ CODEC_CP896 },
	{ offsetof(struct codec_name_db_struct, db_CP897_1), /*                   "cp897"                         */ CODEC_CP897 },
	{ offsetof(struct codec_name_db_struct, db_CP901_0), /*                   "cp901"                         */ CODEC_CP901 },
	{ offsetof(struct codec_name_db_struct, db_CP902_0), /*                   "cp902"                         */ CODEC_CP902 },
	{ offsetof(struct codec_name_db_struct, db_ASCII_20), /*                  "cp903"                         */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_CP9030_0), /*                  "cp9030"                        */ CODEC_CP9030 },
	{ offsetof(struct codec_name_db_struct, db_CP904_1), /*                   "cp904"                         */ CODEC_CP904 },
	{ offsetof(struct codec_name_db_struct, db_CP905_1), /*                   "cp905"                         */ CODEC_CP905 },
	{ offsetof(struct codec_name_db_struct, db_CP9066_0), /*                  "cp9066"                        */ CODEC_CP9066 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_2_13), /*             "cp912"                         */ CODEC_ISO_8859_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_3_8), /*              "cp913"                         */ CODEC_ISO_8859_3 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_4_8), /*              "cp914"                         */ CODEC_ISO_8859_4 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_5_10), /*             "cp915"                         */ CODEC_ISO_8859_5 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_8_7), /*              "cp916"                         */ CODEC_ISO_8859_8 },
	{ offsetof(struct codec_name_db_struct, db_CP918_1), /*                   "cp918"                         */ CODEC_CP918 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_10_9), /*             "cp919"                         */ CODEC_ISO_8859_10 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_9_8), /*              "cp920"                         */ CODEC_ISO_8859_9 },
	{ offsetof(struct codec_name_db_struct, db_CP921_0), /*                   "cp921"                         */ CODEC_CP921 },
	{ offsetof(struct codec_name_db_struct, db_CP922_0), /*                   "cp922"                         */ CODEC_CP922 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_15_7), /*             "cp923"                         */ CODEC_ISO_8859_15 },
	{ offsetof(struct codec_name_db_struct, db_IBM930_1), /*                  "cp930"                         */ CODEC_IBM930 },
	{ offsetof(struct codec_name_db_struct, db_IBM933_1), /*                  "cp933"                         */ CODEC_IBM933 },
	{ offsetof(struct codec_name_db_struct, db_IBM935_1), /*                  "cp935"                         */ CODEC_IBM935 },
	{ offsetof(struct codec_name_db_struct, db_IBM937_1), /*                  "cp937"                         */ CODEC_IBM937 },
	{ offsetof(struct codec_name_db_struct, db_IBM939_1), /*                  "cp939"                         */ CODEC_IBM939 },
	{ offsetof(struct codec_name_db_struct, db_CP1256_5), /*                  "cp9448"                        */ CODEC_CP1256 },
	{ offsetof(struct codec_name_db_struct, db_CP667_3), /*                   "cp991"                         */ CODEC_CP667 },
	{ offsetof(struct codec_name_db_struct, db_CP861_6), /*                   "cpibm861"                      */ CODEC_CP861 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CA_0), /*               "csa-z243.4-1985-1"             */ CODEC_ISO646_CA },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CA2_0), /*              "csa-z243.4-1985-2"             */ CODEC_ISO646_CA2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_123_0), /*              "csa-z243.4-1985-gr"            */ CODEC_ISO_IR_123 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CA_6), /*               "csa-z243.419851"               */ CODEC_ISO646_CA },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CA2_5), /*              "csa-z243.419852"               */ CODEC_ISO646_CA2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CA_3), /*               "csa7-1"                        */ CODEC_ISO646_CA },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CA2_3), /*              "csa7-2"                        */ CODEC_ISO646_CA2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CA_8), /*               "csa71"                         */ CODEC_ISO646_CA },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CA2_6), /*              "csa72"                         */ CODEC_ISO646_CA2 },
	{ offsetof(struct codec_name_db_struct, db_ADOBE_STANDARD_ENCODING_1), /* "csadobestandardencoding"       */ CODEC_ADOBE_STANDARD_ENCODING },
	{ offsetof(struct codec_name_db_struct, db_AMIGA_1251_4), /*              "csamiga1251"                   */ CODEC_AMIGA_1251 },
	{ offsetof(struct codec_name_db_struct, db_ASCII_11), /*                  "csascii"                       */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_BRF_1), /*                     "csbrf"                         */ CODEC_BRF },
	{ offsetof(struct codec_name_db_struct, db_CP1100_5), /*                  "csdecmcs"                      */ CODEC_CP1100 },
	{ offsetof(struct codec_name_db_struct, db_DK_US_1), /*                   "csdkus"                        */ CODEC_DK_US },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_AT_DE_2), /*            "csebcdicatde"                  */ CODEC_EBCDIC_AT_DE },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_AT_DE_A_1), /*          "csebcdicatdea"                 */ CODEC_EBCDIC_AT_DE_A },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_CA_FR_1), /*            "csebcdiccafr"                  */ CODEC_EBCDIC_CA_FR },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_DK_NO_1), /*            "csebcdicdkno"                  */ CODEC_EBCDIC_DK_NO },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_DK_NO_A_1), /*          "csebcdicdknoa"                 */ CODEC_EBCDIC_DK_NO_A },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_ES_1), /*               "csebcdices"                    */ CODEC_EBCDIC_ES },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_ES_A_1), /*             "csebcdicesa"                   */ CODEC_EBCDIC_ES_A },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_ES_S_1), /*             "csebcdicess"                   */ CODEC_EBCDIC_ES_S },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_FI_SE_1), /*            "csebcdicfise"                  */ CODEC_EBCDIC_FI_SE },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_FI_SE_A_1), /*          "csebcdicfisea"                 */ CODEC_EBCDIC_FI_SE_A },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_FR_1), /*               "csebcdicfr"                    */ CODEC_EBCDIC_FR },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_IT_1), /*               "csebcdicit"                    */ CODEC_EBCDIC_IT },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_PT_1), /*               "csebcdicpt"                    */ CODEC_EBCDIC_PT },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_UK_1), /*               "csebcdicuk"                    */ CODEC_EBCDIC_UK },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_US_1), /*               "csebcdicus"                    */ CODEC_EBCDIC_US },
	{ offsetof(struct codec_name_db_struct, db_X0201_2), /*                   "cshalfwidthkatakana"           */ CODEC_X0201 },
	{ offsetof(struct codec_name_db_struct, db_ADOBE_SYMBOL_ENCODING_2), /*   "cshppsmath"                    */ CODEC_ADOBE_SYMBOL_ENCODING },
	{ offsetof(struct codec_name_db_struct, db_HP_ROMAN8_3), /*               "cshproman8"                    */ CODEC_HP_ROMAN8 },
	{ offsetof(struct codec_name_db_struct, db_CP904_3), /*                   "csibbm904"                     */ CODEC_CP904 },
	{ offsetof(struct codec_name_db_struct, db_CP1008_2), /*                  "csibm1008"                     */ CODEC_CP1008 },
	{ offsetof(struct codec_name_db_struct, db_CP1025_2), /*                  "csibm1025"                     */ CODEC_CP1025 },
	{ offsetof(struct codec_name_db_struct, db_CP1026_2), /*                  "csibm1026"                     */ CODEC_CP1026 },
	{ offsetof(struct codec_name_db_struct, db_CP1047_4), /*                  "csibm1047"                     */ CODEC_CP1047 },
	{ offsetof(struct codec_name_db_struct, db_CP1097_2), /*                  "csibm1097"                     */ CODEC_CP1097 },
	{ offsetof(struct codec_name_db_struct, db_CP1112_2), /*                  "csibm1112"                     */ CODEC_CP1112 },
	{ offsetof(struct codec_name_db_struct, db_CP1122_2), /*                  "csibm1122"                     */ CODEC_CP1122 },
	{ offsetof(struct codec_name_db_struct, db_CP1123_2), /*                  "csibm1123"                     */ CODEC_CP1123 },
	{ offsetof(struct codec_name_db_struct, db_CP1124_2), /*                  "csibm1124"                     */ CODEC_CP1124 },
	{ offsetof(struct codec_name_db_struct, db_CP1258_6), /*                  "csibm1129"                     */ CODEC_CP1258 },
	{ offsetof(struct codec_name_db_struct, db_CP1130_2), /*                  "csibm1130"                     */ CODEC_CP1130 },
	{ offsetof(struct codec_name_db_struct, db_CP1132_2), /*                  "csibm1132"                     */ CODEC_CP1132 },
	{ offsetof(struct codec_name_db_struct, db_CP1133_2), /*                  "csibm1133"                     */ CODEC_CP1133 },
	{ offsetof(struct codec_name_db_struct, db_CP1137_2), /*                  "csibm1137"                     */ CODEC_CP1137 },
	{ offsetof(struct codec_name_db_struct, db_CP1140_3), /*                  "csibm1140"                     */ CODEC_CP1140 },
	{ offsetof(struct codec_name_db_struct, db_CP1141_3), /*                  "csibm1141"                     */ CODEC_CP1141 },
	{ offsetof(struct codec_name_db_struct, db_CP1142_3), /*                  "csibm1142"                     */ CODEC_CP1142 },
	{ offsetof(struct codec_name_db_struct, db_CP1143_3), /*                  "csibm1143"                     */ CODEC_CP1143 },
	{ offsetof(struct codec_name_db_struct, db_CP1144_3), /*                  "csibm1144"                     */ CODEC_CP1144 },
	{ offsetof(struct codec_name_db_struct, db_CP1145_3), /*                  "csibm1145"                     */ CODEC_CP1145 },
	{ offsetof(struct codec_name_db_struct, db_CP1146_3), /*                  "csibm1146"                     */ CODEC_CP1146 },
	{ offsetof(struct codec_name_db_struct, db_CP1147_3), /*                  "csibm1147"                     */ CODEC_CP1147 },
	{ offsetof(struct codec_name_db_struct, db_CP1148_3), /*                  "csibm1148"                     */ CODEC_CP1148 },
	{ offsetof(struct codec_name_db_struct, db_CP1149_3), /*                  "csibm1149"                     */ CODEC_CP1149 },
	{ offsetof(struct codec_name_db_struct, db_CP1153_2), /*                  "csibm1153"                     */ CODEC_CP1153 },
	{ offsetof(struct codec_name_db_struct, db_CP1154_2), /*                  "csibm1154"                     */ CODEC_CP1154 },
	{ offsetof(struct codec_name_db_struct, db_CP1155_2), /*                  "csibm1155"                     */ CODEC_CP1155 },
	{ offsetof(struct codec_name_db_struct, db_CP1156_2), /*                  "csibm1156"                     */ CODEC_CP1156 },
	{ offsetof(struct codec_name_db_struct, db_CP1157_2), /*                  "csibm1157"                     */ CODEC_CP1157 },
	{ offsetof(struct codec_name_db_struct, db_CP1158_2), /*                  "csibm1158"                     */ CODEC_CP1158 },
	{ offsetof(struct codec_name_db_struct, db_CP1160_2), /*                  "csibm1160"                     */ CODEC_CP1160 },
	{ offsetof(struct codec_name_db_struct, db_CP1161_2), /*                  "csibm1161"                     */ CODEC_CP1161 },
	{ offsetof(struct codec_name_db_struct, db_CP1162_2), /*                  "csibm11621162"                 */ CODEC_CP1162 },
	{ offsetof(struct codec_name_db_struct, db_CP1163_2), /*                  "csibm1163"                     */ CODEC_CP1163 },
	{ offsetof(struct codec_name_db_struct, db_CP1164_2), /*                  "csibm1164"                     */ CODEC_CP1164 },
	{ offsetof(struct codec_name_db_struct, db_CP1166_2), /*                  "csibm1166"                     */ CODEC_CP1166 },
	{ offsetof(struct codec_name_db_struct, db_KOI8_RU_3), /*                 "csibm1167"                     */ CODEC_KOI8_RU },
	{ offsetof(struct codec_name_db_struct, db_CP12712_2), /*                 "csibm12712"                    */ CODEC_CP12712 },
	{ offsetof(struct codec_name_db_struct, db_IBM1364_2), /*                 "csibm1364"                     */ CODEC_IBM1364 },
	{ offsetof(struct codec_name_db_struct, db_IBM1371_2), /*                 "csibm1371"                     */ CODEC_IBM1371 },
	{ offsetof(struct codec_name_db_struct, db_IBM1388_2), /*                 "csibm1388"                     */ CODEC_IBM1388 },
	{ offsetof(struct codec_name_db_struct, db_IBM1390_2), /*                 "csibm1390"                     */ CODEC_IBM1390 },
	{ offsetof(struct codec_name_db_struct, db_IBM1399_2), /*                 "csibm1399"                     */ CODEC_IBM1399 },
	{ offsetof(struct codec_name_db_struct, db_CP16804_2), /*                 "csibm16804"                    */ CODEC_CP16804 },
	{ offsetof(struct codec_name_db_struct, db_CP273_2), /*                   "csibm273"                      */ CODEC_CP273 },
	{ offsetof(struct codec_name_db_struct, db_CP274_3), /*                   "csibm274"                      */ CODEC_CP274 },
	{ offsetof(struct codec_name_db_struct, db_CP275_3), /*                   "csibm275"                      */ CODEC_CP275 },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_CP_DK_NO_4), /*         "csibm277"                      */ CODEC_EBCDIC_CP_DK_NO },
	{ offsetof(struct codec_name_db_struct, db_CP278_4), /*                   "csibm278"                      */ CODEC_CP278 },
	{ offsetof(struct codec_name_db_struct, db_CP280_3), /*                   "csibm280"                      */ CODEC_CP280 },
	{ offsetof(struct codec_name_db_struct, db_CP281_3), /*                   "csibm281"                      */ CODEC_CP281 },
	{ offsetof(struct codec_name_db_struct, db_CP284_3), /*                   "csibm284"                      */ CODEC_CP284 },
	{ offsetof(struct codec_name_db_struct, db_CP285_3), /*                   "csibm285"                      */ CODEC_CP285 },
	{ offsetof(struct codec_name_db_struct, db_CP290_3), /*                   "csibm290"                      */ CODEC_CP290 },
	{ offsetof(struct codec_name_db_struct, db_CP297_3), /*                   "csibm297"                      */ CODEC_CP297 },
	{ offsetof(struct codec_name_db_struct, db_CP37_6), /*                    "csibm37"                       */ CODEC_CP37 },
	{ offsetof(struct codec_name_db_struct, db_CP38_3), /*                    "csibm38"                       */ CODEC_CP38 },
	{ offsetof(struct codec_name_db_struct, db_CP420_3), /*                   "csibm420"                      */ CODEC_CP420 },
	{ offsetof(struct codec_name_db_struct, db_CP423_3), /*                   "csibm423"                      */ CODEC_CP423 },
	{ offsetof(struct codec_name_db_struct, db_CP424_3), /*                   "csibm424"                      */ CODEC_CP424 },
	{ offsetof(struct codec_name_db_struct, db_CP4517_2), /*                  "csibm4517"                     */ CODEC_CP4517 },
	{ offsetof(struct codec_name_db_struct, db_CP4899_2), /*                  "csibm4899"                     */ CODEC_CP4899 },
	{ offsetof(struct codec_name_db_struct, db_CP4909_2), /*                  "csibm4909"                     */ CODEC_CP4909 },
	{ offsetof(struct codec_name_db_struct, db_CP4971_2), /*                  "csibm4971"                     */ CODEC_CP4971 },
	{ offsetof(struct codec_name_db_struct, db_CP500_4), /*                   "csibm500"                      */ CODEC_CP500 },
	{ offsetof(struct codec_name_db_struct, db_CP5347_2), /*                  "csibm5347"                     */ CODEC_CP5347 },
	{ offsetof(struct codec_name_db_struct, db_CP803_2), /*                   "csibm803"                      */ CODEC_CP803 },
	{ offsetof(struct codec_name_db_struct, db_CP851_3), /*                   "csibm851"                      */ CODEC_CP851 },
	{ offsetof(struct codec_name_db_struct, db_CP855_4), /*                   "csibm855"                      */ CODEC_CP855 },
	{ offsetof(struct codec_name_db_struct, db_CP856_3), /*                   "csibm856"                      */ CODEC_CP856 },
	{ offsetof(struct codec_name_db_struct, db_CP857_4), /*                   "csibm857"                      */ CODEC_CP857 },
	{ offsetof(struct codec_name_db_struct, db_CP858_5), /*                   "csibm858"                      */ CODEC_CP858 },
	{ offsetof(struct codec_name_db_struct, db_CP860_4), /*                   "csibm860"                      */ CODEC_CP860 },
	{ offsetof(struct codec_name_db_struct, db_CP861_5), /*                   "csibm861"                      */ CODEC_CP861 },
	{ offsetof(struct codec_name_db_struct, db_CP863_4), /*                   "csibm863"                      */ CODEC_CP863 },
	{ offsetof(struct codec_name_db_struct, db_CP864_2), /*                   "csibm864"                      */ CODEC_CP864 },
	{ offsetof(struct codec_name_db_struct, db_CP865_4), /*                   "csibm865"                      */ CODEC_CP865 },
	{ offsetof(struct codec_name_db_struct, db_CP866_3), /*                   "csibm866"                      */ CODEC_CP866 },
	{ offsetof(struct codec_name_db_struct, db_CP868_3), /*                   "csibm868"                      */ CODEC_CP868 },
	{ offsetof(struct codec_name_db_struct, db_CP869_5), /*                   "csibm869"                      */ CODEC_CP869 },
	{ offsetof(struct codec_name_db_struct, db_CP870_4), /*                   "csibm870"                      */ CODEC_CP870 },
	{ offsetof(struct codec_name_db_struct, db_CP871_3), /*                   "csibm871"                      */ CODEC_CP871 },
	{ offsetof(struct codec_name_db_struct, db_CP880_3), /*                   "csibm880"                      */ CODEC_CP880 },
	{ offsetof(struct codec_name_db_struct, db_ASCII_17), /*                  "csibm891"                      */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_CP901_2), /*                   "csibm901"                      */ CODEC_CP901 },
	{ offsetof(struct codec_name_db_struct, db_CP902_2), /*                   "csibm902"                      */ CODEC_CP902 },
	{ offsetof(struct codec_name_db_struct, db_ASCII_21), /*                  "csibm903"                      */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_CP9030_2), /*                  "csibm9030"                     */ CODEC_CP9030 },
	{ offsetof(struct codec_name_db_struct, db_CP904_4), /*                   "csibm904"                      */ CODEC_CP904 },
	{ offsetof(struct codec_name_db_struct, db_CP905_3), /*                   "csibm905"                      */ CODEC_CP905 },
	{ offsetof(struct codec_name_db_struct, db_CP9066_2), /*                  "csibm9066"                     */ CODEC_CP9066 },
	{ offsetof(struct codec_name_db_struct, db_CP918_4), /*                   "csibm918"                      */ CODEC_CP918 },
	{ offsetof(struct codec_name_db_struct, db_CP921_2), /*                   "csibm921"                      */ CODEC_CP921 },
	{ offsetof(struct codec_name_db_struct, db_CP922_2), /*                   "csibm922"                      */ CODEC_CP922 },
	{ offsetof(struct codec_name_db_struct, db_IBM930_2), /*                  "csibm930"                      */ CODEC_IBM930 },
	{ offsetof(struct codec_name_db_struct, db_IBM933_2), /*                  "csibm933"                      */ CODEC_IBM933 },
	{ offsetof(struct codec_name_db_struct, db_IBM935_2), /*                  "csibm935"                      */ CODEC_IBM935 },
	{ offsetof(struct codec_name_db_struct, db_IBM937_2), /*                  "csibm937"                      */ CODEC_IBM937 },
	{ offsetof(struct codec_name_db_struct, db_IBM939_2), /*                  "csibm939"                      */ CODEC_IBM939 },
	{ offsetof(struct codec_name_db_struct, db_CP1256_7), /*                  "csibm9448"                     */ CODEC_CP1256 },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_AT_DE_1), /*            "csibmebcdicatde"               */ CODEC_EBCDIC_AT_DE },
	{ offsetof(struct codec_name_db_struct, db_ISO646_T_61_2), /*             "csiso102t617bit"               */ CODEC_ISO646_T_61 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_155_3), /*              "csiso10367box"                 */ CODEC_ISO_IR_155 },
	{ offsetof(struct codec_name_db_struct, db_CP1036_8), /*                  "csiso103t618bit"               */ CODEC_CP1036 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SE_6), /*               "csiso10swedish"                */ CODEC_ISO646_SE },
	{ offsetof(struct codec_name_db_struct, db_KOI8_E_5), /*                  "csiso111ecmacyrillic"          */ CODEC_KOI8_E },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SE2_4), /*              "csiso11swedishfornames"        */ CODEC_ISO646_SE2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CA_5), /*               "csiso121canadian1"             */ CODEC_ISO646_CA },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CA2_4), /*              "csiso122canadian2"             */ CODEC_ISO646_CA2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_123_2), /*              "csiso123csaz24341985gr"        */ CODEC_ISO_IR_123 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_139_2), /*              "csiso139csn369103"             */ CODEC_ISO_IR_139 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_13_5), /*               "csiso13jisc6220jp"             */ CODEC_ISO_IR_13 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_YU_5), /*               "csiso141jusib1002"             */ CODEC_ISO646_YU },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_143_2), /*              "csiso143iecp271"               */ CODEC_ISO_IR_143 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_146_3), /*              "csiso146serbian"               */ CODEC_ISO_IR_146 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_147_3), /*              "csiso147macedonian"            */ CODEC_ISO_IR_147 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_JP_4), /*               "csiso14jisc6220ro"             */ CODEC_ISO646_JP },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_150_2), /*              "csiso150"                      */ CODEC_ISO_IR_150 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_150_3), /*              "csiso150greekccitt"            */ CODEC_ISO_IR_150 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CU_5), /*               "csiso151cuba"                  */ CODEC_ISO646_CU },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_153_3), /*              "csiso153gost1976874"           */ CODEC_ISO_IR_153 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_158_3), /*              "csiso158lap"                   */ CODEC_ISO_IR_158 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_IT_3), /*               "csiso15italian"                */ CODEC_ISO646_IT },
	{ offsetof(struct codec_name_db_struct, db_ISO646_PT_3), /*               "csiso16portugese"              */ CODEC_ISO646_PT },
	{ offsetof(struct codec_name_db_struct, db_ISO646_PT_4), /*               "csiso16portuguese"             */ CODEC_ISO646_PT },
	{ offsetof(struct codec_name_db_struct, db_ISO646_ES_3), /*               "csiso17spanish"                */ CODEC_ISO646_ES },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_18_3), /*               "csiso18greek7old"              */ CODEC_ISO_IR_18 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_19_3), /*               "csiso19latingreek"             */ CODEC_ISO_IR_19 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_98_4), /*               "csiso2033"                     */ CODEC_ISO_IR_98 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DE_6), /*               "csiso21german"                 */ CODEC_ISO646_DE },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FR1_4), /*              "csiso25french"                 */ CODEC_ISO646_FR1 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_LATIN_GR_MIXED_3), /*   "csiso27latingreek1"            */ CODEC_ISO646_LATIN_GR_MIXED },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_2_3), /*                "csiso2intlrefversion"          */ CODEC_ISO_IR_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_VIEWDATA_2), /*         "csiso47bsviewdata"             */ CODEC_ISO646_VIEWDATA },
	{ offsetof(struct codec_name_db_struct, db_ISO646_INIS_SUBSET_2), /*      "csiso49inis"                   */ CODEC_ISO646_INIS_SUBSET },
	{ offsetof(struct codec_name_db_struct, db_ISO646_GB_5), /*               "csiso4unitedkingdom"           */ CODEC_ISO646_GB },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_50_3), /*               "csiso50inis8"                  */ CODEC_ISO_IR_50 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_51_3), /*               "csiso51iniscyrillic"           */ CODEC_ISO_IR_51 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_54_3), /*               "csiso54271981"                 */ CODEC_ISO_IR_54 },
	{ offsetof(struct codec_name_db_struct, db_ISO_5427_5), /*                "csiso5427cyrillic"             */ CODEC_ISO_5427 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_54_6), /*               "csiso5427cyrillic1981"         */ CODEC_ISO_IR_54 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_55_3), /*               "csiso5428greek"                */ CODEC_ISO_IR_55 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CN_4), /*               "csiso57gb1988"                 */ CODEC_ISO646_CN },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CN_5), /*               "csiso58gb1988"                 */ CODEC_ISO646_CN },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NO_4), /*               "csiso60danishnorwegian"        */ CODEC_ISO646_NO },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NO_5), /*               "csiso60norwegian1"             */ CODEC_ISO646_NO },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NO2_4), /*              "csiso61norwegian2"             */ CODEC_ISO646_NO2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DK_4), /*               "csiso646danish"                */ CODEC_ISO646_DK },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_152_2), /*              "csiso6937add"                  */ CODEC_ISO_IR_152 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FR_6), /*               "csiso69french"                 */ CODEC_ISO646_FR },
	{ offsetof(struct codec_name_db_struct, db_ISO646_PT2_3), /*              "csiso84portuguese2"            */ CODEC_ISO646_PT2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_ES2_3), /*              "csiso85spanish2"               */ CODEC_ISO646_ES2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_HU_4), /*               "csiso86hungarian"              */ CODEC_ISO646_HU },
	{ offsetof(struct codec_name_db_struct, db_CP921_13), /*                  "csiso885913"                   */ CODEC_CP921 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_14_9), /*             "csiso885914"                   */ CODEC_ISO_8859_14 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_15_10), /*            "csiso885915"                   */ CODEC_ISO_8859_15 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_16_9), /*             "csiso885916"                   */ CODEC_ISO_8859_16 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_154_3), /*              "csiso8859supp"                 */ CODEC_ISO_IR_154 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_88_2), /*               "csiso88greek7"                 */ CODEC_ISO_IR_88 },
	{ offsetof(struct codec_name_db_struct, db_ISO_6937_2_4), /*              "csiso90"                       */ CODEC_ISO_6937_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_91_3), /*               "csiso91jisc62291984a"          */ CODEC_ISO_IR_91 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_JP_OCR_B_4), /*         "csiso92jisc62991984b"          */ CODEC_ISO646_JP_OCR_B },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_93_3), /*               "csiso93jis62291984badd"        */ CODEC_ISO_IR_93 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_94_3), /*               "csiso94jis62291984hand"        */ CODEC_ISO_IR_94 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_95_3), /*               "csiso95jis62291984handadd"     */ CODEC_ISO_IR_95 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_96_2), /*               "csiso96jisc62291984kana"       */ CODEC_ISO_IR_96 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_1_8), /*              "csisolatin1"                   */ CODEC_ISO_8859_1 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_2_6), /*              "csisolatin2"                   */ CODEC_ISO_8859_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_3_6), /*              "csisolatin3"                   */ CODEC_ISO_8859_3 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_4_6), /*              "csisolatin4"                   */ CODEC_ISO_8859_4 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_9_6), /*              "csisolatin5"                   */ CODEC_ISO_8859_9 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_10_7), /*             "csisolatin6"                   */ CODEC_ISO_8859_10 },
	{ offsetof(struct codec_name_db_struct, db_CP921_7), /*                   "csisolatin7"                   */ CODEC_CP921 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_15_12), /*            "csisolatin9"                   */ CODEC_ISO_8859_15 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_6_7), /*              "csisolatinarabic"              */ CODEC_ISO_8859_6 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_5_5), /*              "csisolatincyrillic"            */ CODEC_ISO_8859_5 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_7_8), /*              "csisolatingreek"               */ CODEC_ISO_8859_7 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_8_5), /*              "csisolatinhebrew"              */ CODEC_ISO_8859_8 },
	{ offsetof(struct codec_name_db_struct, db_KOI8_R_4), /*                  "cskoi8r"                       */ CODEC_KOI8_R },
	{ offsetof(struct codec_name_db_struct, db_KOI8_U_5), /*                  "cskoi8u"                       */ CODEC_KOI8_U },
	{ offsetof(struct codec_name_db_struct, db_ISO646_KR_2), /*               "csksc5636"                     */ CODEC_ISO646_KR },
	{ offsetof(struct codec_name_db_struct, db_KZ_1048_4), /*                 "cskz1048"                      */ CODEC_KZ_1048 },
	{ offsetof(struct codec_name_db_struct, db_CP1275_2), /*                  "csmacintosh"                   */ CODEC_CP1275 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_139_0), /*              "csn-369103"                    */ CODEC_ISO_IR_139 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NATS_DANO_4), /*        "csnatsdano"                    */ CODEC_ISO646_NATS_DANO },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_8_1_3), /*              "csnatssefi"                    */ CODEC_ISO_IR_8_1 },
	{ offsetof(struct codec_name_db_struct, db_OSD_EBCDIC_DF03_IRV_1), /*     "csosdebcdicdf3irv"             */ CODEC_OSD_EBCDIC_DF03_IRV },
	{ offsetof(struct codec_name_db_struct, db_OSD_EBCDIC_DF04_1_1), /*       "csosdebcdicdf41"               */ CODEC_OSD_EBCDIC_DF04_1 },
	{ offsetof(struct codec_name_db_struct, db_OSD_EBCDIC_DF04_15_1), /*      "csosdebcdicdf415"              */ CODEC_OSD_EBCDIC_DF04_15 },
	{ offsetof(struct codec_name_db_struct, db_CP775_3), /*                   "cspc775baltic"                 */ CODEC_CP775 },
	{ offsetof(struct codec_name_db_struct, db_CP850_3), /*                   "cspc850multilingual"           */ CODEC_CP850 },
	{ offsetof(struct codec_name_db_struct, db_CP858_7), /*                   "cspc858multilingual"           */ CODEC_CP858 },
	{ offsetof(struct codec_name_db_struct, db_CP862_4), /*                   "cspc862latinhebrew"            */ CODEC_CP862 },
	{ offsetof(struct codec_name_db_struct, db_CP437_3), /*                   "cspc8codepage437"              */ CODEC_CP437 },
	{ offsetof(struct codec_name_db_struct, db_CP852_3), /*                   "cspcp852"                      */ CODEC_CP852 },
	{ offsetof(struct codec_name_db_struct, db_PT154_1), /*                   "csptcp154"                     */ CODEC_PT154 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_11_6), /*             "cstis620"                      */ CODEC_ISO_8859_11 },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_12), /*                "csucs4"                        */ CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_10), /*                "csucs4"                        */ CODEC_UTF32LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_14), /*                "csunicode"                     */ CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_14), /*                "csunicode"                     */ CODEC_UTF16LE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_US_DK_1), /*                   "csusdk"                        */ CODEC_US_DK },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_10), /*                "csutf16"                       */ CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_10), /*                "csutf16"                       */ CODEC_UTF16LE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_4), /*                 "csutf16be"                     */ CODEC_UTF16BE },
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_4), /*                 "csutf16le"                     */ CODEC_UTF16LE },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_9), /*                 "csutf32"                       */ CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_7), /*                 "csutf32"                       */ CODEC_UTF32LE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_5), /*                 "csutf32be"                     */ CODEC_UTF32BE },
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_3), /*                 "csutf32le"                     */ CODEC_UTF32LE },
	{ offsetof(struct codec_name_db_struct, db_UTF8_8), /*                    "csutf8"                        */ CODEC_UTF8 },
	{ offsetof(struct codec_name_db_struct, db_VENTURA_INTERNATIONAL_2), /*   "csventurainternational"        */ CODEC_VENTURA_INTERNATIONAL },
	{ offsetof(struct codec_name_db_struct, db_VENTURA_US_1), /*              "csventuraus"                   */ CODEC_VENTURA_US },
	{ offsetof(struct codec_name_db_struct, db_CP1250_3), /*                  "cswindows1250"                 */ CODEC_CP1250 },
	{ offsetof(struct codec_name_db_struct, db_CP1251_3), /*                  "cswindows1251"                 */ CODEC_CP1251 },
	{ offsetof(struct codec_name_db_struct, db_CP1252_3), /*                  "cswindows1252"                 */ CODEC_CP1252 },
	{ offsetof(struct codec_name_db_struct, db_CP1253_3), /*                  "cswindows1253"                 */ CODEC_CP1253 },
	{ offsetof(struct codec_name_db_struct, db_CP1254_3), /*                  "cswindows1254"                 */ CODEC_CP1254 },
	{ offsetof(struct codec_name_db_struct, db_CP1255_3), /*                  "cswindows1255"                 */ CODEC_CP1255 },
	{ offsetof(struct codec_name_db_struct, db_CP1256_3), /*                  "cswindows1256"                 */ CODEC_CP1256 },
	{ offsetof(struct codec_name_db_struct, db_CP1257_4), /*                  "cswindows1257"                 */ CODEC_CP1257 },
	{ offsetof(struct codec_name_db_struct, db_CP1258_3), /*                  "cswindows1258"                 */ CODEC_CP1258 },
	{ offsetof(struct codec_name_db_struct, db_CP874_7), /*                   "cswindows874"                  */ CODEC_CP874 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CU_1), /*               "cuba"                          */ CODEC_ISO646_CU },
	{ offsetof(struct codec_name_db_struct, db_CWI_0), /*                     "cwi"                           */ CODEC_CWI },
	{ offsetof(struct codec_name_db_struct, db_CWI_1), /*                     "cwi-2"                         */ CODEC_CWI },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_5_3), /*              "cyrillic"                      */ CODEC_ISO_8859_5 },
	{ offsetof(struct codec_name_db_struct, db_PT154_4), /*                   "cyrillic-asian"                */ CODEC_PT154 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DE_8), /*               "d7dec"                         */ CODEC_ISO646_DE },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DE_2), /*               "de"                            */ CODEC_ISO646_DE },
	{ offsetof(struct codec_name_db_struct, db_CP1100_1), /*                  "dec"                           */ CODEC_CP1100 },
	{ offsetof(struct codec_name_db_struct, db_CP1287_4), /*                  "dec-greek"                     */ CODEC_CP1287 },
	{ offsetof(struct codec_name_db_struct, db_CP1287_1), /*                  "dec-greek-(8-bit)"             */ CODEC_CP1287 },
	{ offsetof(struct codec_name_db_struct, db_CP1287_3), /*                  "dec-greek-8"                   */ CODEC_CP1287 },
	{ offsetof(struct codec_name_db_struct, db_CP1287_2), /*                  "dec-greek-8-bit"               */ CODEC_CP1287 },
	{ offsetof(struct codec_name_db_struct, db_CP1100_0), /*                  "dec-mcs"                       */ CODEC_CP1100 },
	{ offsetof(struct codec_name_db_struct, db_CP1090_2), /*                  "dec-special-graphics"          */ CODEC_CP1090 },
	{ offsetof(struct codec_name_db_struct, db_CP1288_4), /*                  "dec-turkish"                   */ CODEC_CP1288 },
	{ offsetof(struct codec_name_db_struct, db_CP1288_1), /*                  "dec-turkish-(8-bit)"           */ CODEC_CP1288 },
	{ offsetof(struct codec_name_db_struct, db_CP1288_3), /*                  "dec-turkish-8"                 */ CODEC_CP1288 },
	{ offsetof(struct codec_name_db_struct, db_CP1288_2), /*                  "dec-turkish-8-bit"             */ CODEC_CP1288 },
	{ offsetof(struct codec_name_db_struct, db_CP1100_6), /*                  "decmcs"                        */ CODEC_CP1100 },
	{ offsetof(struct codec_name_db_struct, db_ASCII_23), /*                  "default"                       */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DE_0), /*               "din-66003"                     */ CODEC_ISO646_DE },
	{ offsetof(struct codec_name_db_struct, db_DIN_66303_0), /*               "din-66303"                     */ CODEC_DIN_66303 },
	{ offsetof(struct codec_name_db_struct, db_ASCII_26), /*                  "direct"                        */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DK_3), /*               "dk"                            */ CODEC_ISO646_DK },
	{ offsetof(struct codec_name_db_struct, db_DK_US_0), /*                   "dk-us"                         */ CODEC_DK_US },
	{ offsetof(struct codec_name_db_struct, db_KEYBCS2_1), /*                 "dos-895"                       */ CODEC_KEYBCS2 },
	{ offsetof(struct codec_name_db_struct, db_DIN_66303_1), /*               "drv8"                          */ CODEC_DIN_66303 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DK_0), /*               "ds-2089"                       */ CODEC_ISO646_DK },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DK_1), /*               "ds2089"                        */ CODEC_ISO646_DK },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_98_3), /*               "e13b"                          */ CODEC_ISO_IR_98 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_ES_5), /*               "e7dec"                         */ CODEC_ISO646_ES },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_AT_DE_0), /*            "ebcdic-at-de"                  */ CODEC_EBCDIC_AT_DE },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_AT_DE_A_0), /*          "ebcdic-at-de-a"                */ CODEC_EBCDIC_AT_DE_A },
	{ offsetof(struct codec_name_db_struct, db_CP274_1), /*                   "ebcdic-be"                     */ CODEC_CP274 },
	{ offsetof(struct codec_name_db_struct, db_CP275_1), /*                   "ebcdic-br"                     */ CODEC_CP275 },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_CA_FR_0), /*            "ebcdic-ca-fr"                  */ CODEC_EBCDIC_CA_FR },
	{ offsetof(struct codec_name_db_struct, db_CP420_2), /*                   "ebcdic-cp-ar1"                 */ CODEC_CP420 },
	{ offsetof(struct codec_name_db_struct, db_CP918_3), /*                   "ebcdic-cp-ar2"                 */ CODEC_CP918 },
	{ offsetof(struct codec_name_db_struct, db_CP500_2), /*                   "ebcdic-cp-be"                  */ CODEC_CP500 },
	{ offsetof(struct codec_name_db_struct, db_CP37_3), /*                    "ebcdic-cp-ca"                  */ CODEC_CP37 },
	{ offsetof(struct codec_name_db_struct, db_CP500_3), /*                   "ebcdic-cp-ch"                  */ CODEC_CP500 },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_CP_DK_NO_2), /*         "ebcdic-cp-dk"                  */ CODEC_EBCDIC_CP_DK_NO },
	{ offsetof(struct codec_name_db_struct, db_CP284_2), /*                   "ebcdic-cp-es"                  */ CODEC_CP284 },
	{ offsetof(struct codec_name_db_struct, db_CP278_2), /*                   "ebcdic-cp-fi"                  */ CODEC_CP278 },
	{ offsetof(struct codec_name_db_struct, db_CP297_2), /*                   "ebcdic-cp-fr"                  */ CODEC_CP297 },
	{ offsetof(struct codec_name_db_struct, db_CP285_2), /*                   "ebcdic-cp-gb"                  */ CODEC_CP285 },
	{ offsetof(struct codec_name_db_struct, db_CP423_2), /*                   "ebcdic-cp-gr"                  */ CODEC_CP423 },
	{ offsetof(struct codec_name_db_struct, db_CP424_2), /*                   "ebcdic-cp-he"                  */ CODEC_CP424 },
	{ offsetof(struct codec_name_db_struct, db_CP871_2), /*                   "ebcdic-cp-is"                  */ CODEC_CP871 },
	{ offsetof(struct codec_name_db_struct, db_CP280_2), /*                   "ebcdic-cp-it"                  */ CODEC_CP280 },
	{ offsetof(struct codec_name_db_struct, db_CP37_5), /*                    "ebcdic-cp-nl"                  */ CODEC_CP37 },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_CP_DK_NO_3), /*         "ebcdic-cp-no"                  */ CODEC_EBCDIC_CP_DK_NO },
	{ offsetof(struct codec_name_db_struct, db_CP870_2), /*                   "ebcdic-cp-roece"               */ CODEC_CP870 },
	{ offsetof(struct codec_name_db_struct, db_CP278_3), /*                   "ebcdic-cp-se"                  */ CODEC_CP278 },
	{ offsetof(struct codec_name_db_struct, db_CP905_2), /*                   "ebcdic-cp-tr"                  */ CODEC_CP905 },
	{ offsetof(struct codec_name_db_struct, db_CP37_2), /*                    "ebcdic-cp-us"                  */ CODEC_CP37 },
	{ offsetof(struct codec_name_db_struct, db_CP37_4), /*                    "ebcdic-cp-wt"                  */ CODEC_CP37 },
	{ offsetof(struct codec_name_db_struct, db_CP870_3), /*                   "ebcdic-cp-yu"                  */ CODEC_CP870 },
	{ offsetof(struct codec_name_db_struct, db_CP880_2), /*                   "ebcdic-cyrillic"               */ CODEC_CP880 },
	{ offsetof(struct codec_name_db_struct, db_CP1141_5), /*                  "ebcdic-de-273+euro"            */ CODEC_CP1141 },
	{ offsetof(struct codec_name_db_struct, db_CP1142_5), /*                  "ebcdic-dk-277+euro"            */ CODEC_CP1142 },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_DK_NO_0), /*            "ebcdic-dk-no"                  */ CODEC_EBCDIC_DK_NO },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_DK_NO_A_0), /*          "ebcdic-dk-no-a"                */ CODEC_EBCDIC_DK_NO_A },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_ES_0), /*               "ebcdic-es"                     */ CODEC_EBCDIC_ES },
	{ offsetof(struct codec_name_db_struct, db_CP1145_5), /*                  "ebcdic-es-284+euro"            */ CODEC_CP1145 },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_ES_A_0), /*             "ebcdic-es-a"                   */ CODEC_EBCDIC_ES_A },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_ES_S_0), /*             "ebcdic-es-s"                   */ CODEC_EBCDIC_ES_S },
	{ offsetof(struct codec_name_db_struct, db_CP1143_5), /*                  "ebcdic-fi-278+euro"            */ CODEC_CP1143 },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_FI_SE_0), /*            "ebcdic-fi-se"                  */ CODEC_EBCDIC_FI_SE },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_FI_SE_A_0), /*          "ebcdic-fi-se-a"                */ CODEC_EBCDIC_FI_SE_A },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_FR_0), /*               "ebcdic-fr"                     */ CODEC_EBCDIC_FR },
	{ offsetof(struct codec_name_db_struct, db_CP1147_5), /*                  "ebcdic-fr-297+euro"            */ CODEC_CP1147 },
	{ offsetof(struct codec_name_db_struct, db_CP1146_5), /*                  "ebcdic-gb-285+euro"            */ CODEC_CP1146 },
	{ offsetof(struct codec_name_db_struct, db_CP875_2), /*                   "ebcdic-greek"                  */ CODEC_CP875 },
	{ offsetof(struct codec_name_db_struct, db_CP38_1), /*                    "ebcdic-int"                    */ CODEC_CP38 },
	{ offsetof(struct codec_name_db_struct, db_IBM256_1), /*                  "ebcdic-int1"                   */ CODEC_IBM256 },
	{ offsetof(struct codec_name_db_struct, db_CP1148_5), /*                  "ebcdic-international-500+euro" */ CODEC_CP1148 },
	{ offsetof(struct codec_name_db_struct, db_CP1149_5), /*                  "ebcdic-is-871+euro"            */ CODEC_CP1149 },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_IS_FRISS_0), /*         "ebcdic-is-friss"               */ CODEC_EBCDIC_IS_FRISS },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_IT_0), /*               "ebcdic-it"                     */ CODEC_EBCDIC_IT },
	{ offsetof(struct codec_name_db_struct, db_CP1144_5), /*                  "ebcdic-it-280+euro"            */ CODEC_CP1144 },
	{ offsetof(struct codec_name_db_struct, db_CP281_1), /*                   "ebcdic-jp-e"                   */ CODEC_CP281 },
	{ offsetof(struct codec_name_db_struct, db_CP290_2), /*                   "ebcdic-jp-kana"                */ CODEC_CP290 },
	{ offsetof(struct codec_name_db_struct, db_CP1142_6), /*                  "ebcdic-no-277+euro"            */ CODEC_CP1142 },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_PT_0), /*               "ebcdic-pt"                     */ CODEC_EBCDIC_PT },
	{ offsetof(struct codec_name_db_struct, db_CP1143_6), /*                  "ebcdic-se-278+euro"            */ CODEC_CP1143 },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_UK_0), /*               "ebcdic-uk"                     */ CODEC_EBCDIC_UK },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_US_0), /*               "ebcdic-us"                     */ CODEC_EBCDIC_US },
	{ offsetof(struct codec_name_db_struct, db_CP1140_5), /*                  "ebcdic-us-37+euro"             */ CODEC_CP1140 },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_AT_DE_3), /*            "ebcdicatde"                    */ CODEC_EBCDIC_AT_DE },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_AT_DE_A_2), /*          "ebcdicatdea"                   */ CODEC_EBCDIC_AT_DE_A },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_CA_FR_2), /*            "ebcdiccafr"                    */ CODEC_EBCDIC_CA_FR },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_DK_NO_2), /*            "ebcdicdkno"                    */ CODEC_EBCDIC_DK_NO },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_DK_NO_A_2), /*          "ebcdicdknoa"                   */ CODEC_EBCDIC_DK_NO_A },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_ES_2), /*               "ebcdices"                      */ CODEC_EBCDIC_ES },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_ES_A_2), /*             "ebcdicesa"                     */ CODEC_EBCDIC_ES_A },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_FI_SE_2), /*            "ebcdicfise"                    */ CODEC_EBCDIC_FI_SE },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_FI_SE_A_2), /*          "ebcdicfisea"                   */ CODEC_EBCDIC_FI_SE_A },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_FR_2), /*               "ebcdicfr"                      */ CODEC_EBCDIC_FR },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_IS_FRISS_1), /*         "ebcdicisfriss"                 */ CODEC_EBCDIC_IS_FRISS },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_IT_2), /*               "ebcdicit"                      */ CODEC_EBCDIC_IT },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_PT_2), /*               "ebcdicpt"                      */ CODEC_EBCDIC_PT },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_UK_2), /*               "ebcdicuk"                      */ CODEC_EBCDIC_UK },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_US_2), /*               "ebcdicus"                      */ CODEC_EBCDIC_US },
	{ offsetof(struct codec_name_db_struct, db_KOI8_E_3), /*                  "ecma-113"                      */ CODEC_KOI8_E },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_6_3), /*              "ecma-114"                      */ CODEC_ISO_8859_6 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_7_4), /*              "ecma-118"                      */ CODEC_ISO_8859_7 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_9_14), /*             "ecma-128"                      */ CODEC_ISO_8859_9 },
	{ offsetof(struct codec_name_db_struct, db_KOI8_E_0), /*                  "ecma-cyrillic"                 */ CODEC_KOI8_E },
	{ offsetof(struct codec_name_db_struct, db_KOI8_E_1), /*                  "ecmacyrillic"                  */ CODEC_KOI8_E },
	{ offsetof(struct codec_name_db_struct, db_CP1287_5), /*                  "el8dec"                        */ CODEC_CP1287 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_7_3), /*              "elot-928"                      */ CODEC_ISO_8859_7 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_ES_0), /*               "es"                            */ CODEC_ISO646_ES },
	{ offsetof(struct codec_name_db_struct, db_ISO646_ES2_0), /*              "es2"                           */ CODEC_ISO646_ES2 },
	{ offsetof(struct codec_name_db_struct, db_CP922_3), /*                   "estonia-iso-8"                 */ CODEC_CP922 },
	{ offsetof(struct codec_name_db_struct, db_EXTENDED_LATIN_8_0), /*        "extended-latin-8"              */ CODEC_EXTENDED_LATIN_8 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FR1_7), /*              "f7dec"                         */ CODEC_ISO646_FR1 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SE_2), /*               "fi"                            */ CODEC_ISO646_SE },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FR_3), /*               "fr"                            */ CODEC_ISO646_FR },
	{ offsetof(struct codec_name_db_struct, db_ISO646_GB_3), /*               "gb"                            */ CODEC_ISO646_GB },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CN_0), /*               "gb-1988-80"                    */ CODEC_ISO646_CN },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CN_6), /*               "gb-198880"                     */ CODEC_ISO646_CN },
	{ offsetof(struct codec_name_db_struct, db_GBCD_0), /*                    "gbcd"                          */ CODEC_GBCD },
	{ offsetof(struct codec_name_db_struct, db_GEORGIAN_ACADEMY_0), /*        "georgian-academy"              */ CODEC_GEORGIAN_ACADEMY },
	{ offsetof(struct codec_name_db_struct, db_GEORGIAN_PS_0), /*             "georgian-ps"                   */ CODEC_GEORGIAN_PS },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DE_7), /*               "german"                        */ CODEC_ISO646_DE },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_153_4), /*              "gost-19768"                    */ CODEC_ISO_IR_153 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_153_0), /*              "gost-19768-74"                 */ CODEC_ISO_IR_153 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_153_5), /*              "gost-1976874"                  */ CODEC_ISO_IR_153 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_7_5), /*              "greek"                         */ CODEC_ISO_8859_7 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_150_0), /*              "greek-ccitt"                   */ CODEC_ISO_IR_150 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_88_0), /*               "greek7"                        */ CODEC_ISO_IR_88 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_18_0), /*               "greek7-old"                    */ CODEC_ISO_IR_18 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_18_1), /*               "greek7old"                     */ CODEC_ISO_IR_18 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_7_6), /*              "greek8"                        */ CODEC_ISO_8859_7 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_150_4), /*              "greekccitt"                    */ CODEC_ISO_IR_150 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_8_3), /*              "hebrew"                        */ CODEC_ISO_8859_8 },
	{ offsetof(struct codec_name_db_struct, db_HEX_UPPER_1), /*               "hex"                           */ CODEC_HEX_UPPER },
	{ offsetof(struct codec_name_db_struct, db_HEX_LOWER_0), /*               "hex-lower"                     */ CODEC_HEX_LOWER },
	{ offsetof(struct codec_name_db_struct, db_HEX_UPPER_0), /*               "hex-upper"                     */ CODEC_HEX_UPPER },
	{ offsetof(struct codec_name_db_struct, db_HP_GREEK8_0), /*               "hp-greek8"                     */ CODEC_HP_GREEK8 },
	{ offsetof(struct codec_name_db_struct, db_CP1057_1), /*                  "hp-pc-8"                       */ CODEC_CP1057 },
	{ offsetof(struct codec_name_db_struct, db_HP_ROMAN8_8), /*               "hp-roman-8"                    */ CODEC_HP_ROMAN8 },
	{ offsetof(struct codec_name_db_struct, db_HP_ROMAN8_0), /*               "hp-roman8"                     */ CODEC_HP_ROMAN8 },
	{ offsetof(struct codec_name_db_struct, db_HP_ROMAN9_0), /*               "hp-roman9"                     */ CODEC_HP_ROMAN9 },
	{ offsetof(struct codec_name_db_struct, db_HP_THAI8_0), /*                "hp-thai8"                      */ CODEC_HP_THAI8 },
	{ offsetof(struct codec_name_db_struct, db_HP_TURKISH8_0), /*             "hp-turkish8"                   */ CODEC_HP_TURKISH8 },
	{ offsetof(struct codec_name_db_struct, db_HP_GREEK8_1), /*               "hpgreek8"                      */ CODEC_HP_GREEK8 },
	{ offsetof(struct codec_name_db_struct, db_HP_ROMAN8_5), /*               "hproman8"                      */ CODEC_HP_ROMAN8 },
	{ offsetof(struct codec_name_db_struct, db_HP_ROMAN9_3), /*               "hproman9"                      */ CODEC_HP_ROMAN9 },
	{ offsetof(struct codec_name_db_struct, db_HP_THAI8_1), /*                "hpthai8"                       */ CODEC_HP_THAI8 },
	{ offsetof(struct codec_name_db_struct, db_HP_TURKISH8_1), /*             "hpturkish8"                    */ CODEC_HP_TURKISH8 },
	{ offsetof(struct codec_name_db_struct, db_XML_ESCAPE_1), /*              "html-escape"                   */ CODEC_XML_ESCAPE },
	{ offsetof(struct codec_name_db_struct, db_ISO646_HU_3), /*               "hu"                            */ CODEC_ISO646_HU },
	{ offsetof(struct codec_name_db_struct, db_ISO646_IT_6), /*               "i7dec"                         */ CODEC_ISO646_IT },
	{ offsetof(struct codec_name_db_struct, db_CP1004_2), /*                  "ibm1004"                       */ CODEC_CP1004 },
	{ offsetof(struct codec_name_db_struct, db_CP1006_1), /*                  "ibm1006"                       */ CODEC_CP1006 },
	{ offsetof(struct codec_name_db_struct, db_CP1008_1), /*                  "ibm1008"                       */ CODEC_CP1008 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_IRV_1983_1), /*         "ibm1009"                       */ CODEC_ISO646_IRV_1983 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FR_9), /*               "ibm1010"                       */ CODEC_ISO646_FR },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DE_4), /*               "ibm1011"                       */ CODEC_ISO646_DE },
	{ offsetof(struct codec_name_db_struct, db_ISO646_IT_5), /*               "ibm1012"                       */ CODEC_ISO646_IT },
	{ offsetof(struct codec_name_db_struct, db_ISO646_GB_7), /*               "ibm1013"                       */ CODEC_ISO646_GB },
	{ offsetof(struct codec_name_db_struct, db_ISO646_ES2_5), /*              "ibm1014"                       */ CODEC_ISO646_ES2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_PT2_5), /*              "ibm1015"                       */ CODEC_ISO646_PT2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NATS_DANO_3), /*        "ibm1016"                       */ CODEC_ISO646_NATS_DANO },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DK_6), /*               "ibm1017"                       */ CODEC_ISO646_DK },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SE_9), /*               "ibm1018"                       */ CODEC_ISO646_SE },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NL_2), /*               "ibm1019"                       */ CODEC_ISO646_NL },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SWI_NRCS_1), /*         "ibm1021"                       */ CODEC_ISO646_SWI_NRCS },
	{ offsetof(struct codec_name_db_struct, db_CP1025_1), /*                  "ibm1025"                       */ CODEC_CP1025 },
	{ offsetof(struct codec_name_db_struct, db_CP1026_0), /*                  "ibm1026"                       */ CODEC_CP1026 },
	{ offsetof(struct codec_name_db_struct, db_CP1036_1), /*                  "ibm1036"                       */ CODEC_CP1036 },
	{ offsetof(struct codec_name_db_struct, db_ADOBE_SYMBOL_ENCODING_4), /*   "ibm1038"                       */ CODEC_ADOBE_SYMBOL_ENCODING },
	{ offsetof(struct codec_name_db_struct, db_CP1041_0), /*                  "ibm1041"                       */ CODEC_CP1041 },
	{ offsetof(struct codec_name_db_struct, db_CP1043_0), /*                  "ibm1043"                       */ CODEC_CP1043 },
	{ offsetof(struct codec_name_db_struct, db_CP1046_2), /*                  "ibm1046"                       */ CODEC_CP1046 },
	{ offsetof(struct codec_name_db_struct, db_CP1047_1), /*                  "ibm1047"                       */ CODEC_CP1047 },
	{ offsetof(struct codec_name_db_struct, db_HP_ROMAN8_7), /*               "ibm1050"                       */ CODEC_HP_ROMAN8 },
	{ offsetof(struct codec_name_db_struct, db_HP_ROMAN8_10), /*              "ibm1051"                       */ CODEC_HP_ROMAN8 },
	{ offsetof(struct codec_name_db_struct, db_CP1088_0), /*                  "ibm1088"                       */ CODEC_CP1088 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_6_8), /*              "ibm1089"                       */ CODEC_ISO_8859_6 },
	{ offsetof(struct codec_name_db_struct, db_CP1090_1), /*                  "ibm1090"                       */ CODEC_CP1090 },
	{ offsetof(struct codec_name_db_struct, db_CP1097_1), /*                  "ibm1097"                       */ CODEC_CP1097 },
	{ offsetof(struct codec_name_db_struct, db_CP1098_1), /*                  "ibm1098"                       */ CODEC_CP1098 },
	{ offsetof(struct codec_name_db_struct, db_CP1100_3), /*                  "ibm1100"                       */ CODEC_CP1100 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_GB_NRCS_1), /*          "ibm1101"                       */ CODEC_ISO646_GB_NRCS },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NL_NRCS_1), /*          "ibm1102"                       */ CODEC_ISO646_NL_NRCS },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FI_NRCS_1), /*          "ibm1103"                       */ CODEC_ISO646_FI_NRCS },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DK_NO_NRCS_1), /*       "ibm1105"                       */ CODEC_ISO646_DK_NO_NRCS },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SE_NRCS_1), /*          "ibm1106"                       */ CODEC_ISO646_SE_NRCS },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DK_NO_ALT_NRCS_1), /*   "ibm1107"                       */ CODEC_ISO646_DK_NO_ALT_NRCS },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_2_7), /*              "ibm1111"                       */ CODEC_ISO_8859_2 },
	{ offsetof(struct codec_name_db_struct, db_CP1112_1), /*                  "ibm1112"                       */ CODEC_CP1112 },
	{ offsetof(struct codec_name_db_struct, db_CP1114_0), /*                  "ibm1114"                       */ CODEC_CP1114 },
	{ offsetof(struct codec_name_db_struct, db_CP1115_0), /*                  "ibm1115"                       */ CODEC_CP1115 },
	{ offsetof(struct codec_name_db_struct, db_CP1116_1), /*                  "ibm1116"                       */ CODEC_CP1116 },
	{ offsetof(struct codec_name_db_struct, db_CP1117_1), /*                  "ibm1117"                       */ CODEC_CP1117 },
	{ offsetof(struct codec_name_db_struct, db_CP774_2), /*                   "ibm1118"                       */ CODEC_CP774 },
	{ offsetof(struct codec_name_db_struct, db_CP1122_1), /*                  "ibm1122"                       */ CODEC_CP1122 },
	{ offsetof(struct codec_name_db_struct, db_CP1123_1), /*                  "ibm1123"                       */ CODEC_CP1123 },
	{ offsetof(struct codec_name_db_struct, db_CP1124_1), /*                  "ibm1124"                       */ CODEC_CP1124 },
	{ offsetof(struct codec_name_db_struct, db_CP1258_5), /*                  "ibm1129"                       */ CODEC_CP1258 },
	{ offsetof(struct codec_name_db_struct, db_CP1130_1), /*                  "ibm1130"                       */ CODEC_CP1130 },
	{ offsetof(struct codec_name_db_struct, db_CP1131_1), /*                  "ibm1131"                       */ CODEC_CP1131 },
	{ offsetof(struct codec_name_db_struct, db_CP1132_1), /*                  "ibm1132"                       */ CODEC_CP1132 },
	{ offsetof(struct codec_name_db_struct, db_CP1133_1), /*                  "ibm1133"                       */ CODEC_CP1133 },
	{ offsetof(struct codec_name_db_struct, db_CP1137_1), /*                  "ibm1137"                       */ CODEC_CP1137 },
	{ offsetof(struct codec_name_db_struct, db_CP1140_1), /*                  "ibm1140"                       */ CODEC_CP1140 },
	{ offsetof(struct codec_name_db_struct, db_CP1141_1), /*                  "ibm1141"                       */ CODEC_CP1141 },
	{ offsetof(struct codec_name_db_struct, db_CP1142_1), /*                  "ibm1142"                       */ CODEC_CP1142 },
	{ offsetof(struct codec_name_db_struct, db_CP1143_1), /*                  "ibm1143"                       */ CODEC_CP1143 },
	{ offsetof(struct codec_name_db_struct, db_CP1144_1), /*                  "ibm1144"                       */ CODEC_CP1144 },
	{ offsetof(struct codec_name_db_struct, db_CP1145_1), /*                  "ibm1145"                       */ CODEC_CP1145 },
	{ offsetof(struct codec_name_db_struct, db_CP1146_1), /*                  "ibm1146"                       */ CODEC_CP1146 },
	{ offsetof(struct codec_name_db_struct, db_CP1147_1), /*                  "ibm1147"                       */ CODEC_CP1147 },
	{ offsetof(struct codec_name_db_struct, db_CP1148_1), /*                  "ibm1148"                       */ CODEC_CP1148 },
	{ offsetof(struct codec_name_db_struct, db_CP1149_1), /*                  "ibm1149"                       */ CODEC_CP1149 },
	{ offsetof(struct codec_name_db_struct, db_CP1153_1), /*                  "ibm1153"                       */ CODEC_CP1153 },
	{ offsetof(struct codec_name_db_struct, db_CP1154_1), /*                  "ibm1154"                       */ CODEC_CP1154 },
	{ offsetof(struct codec_name_db_struct, db_CP1155_1), /*                  "ibm1155"                       */ CODEC_CP1155 },
	{ offsetof(struct codec_name_db_struct, db_CP1156_1), /*                  "ibm1156"                       */ CODEC_CP1156 },
	{ offsetof(struct codec_name_db_struct, db_CP1157_1), /*                  "ibm1157"                       */ CODEC_CP1157 },
	{ offsetof(struct codec_name_db_struct, db_CP1158_1), /*                  "ibm1158"                       */ CODEC_CP1158 },
	{ offsetof(struct codec_name_db_struct, db_CP1160_1), /*                  "ibm1160"                       */ CODEC_CP1160 },
	{ offsetof(struct codec_name_db_struct, db_CP1161_1), /*                  "ibm1161"                       */ CODEC_CP1161 },
	{ offsetof(struct codec_name_db_struct, db_CP1162_1), /*                  "ibm1162"                       */ CODEC_CP1162 },
	{ offsetof(struct codec_name_db_struct, db_CP1163_1), /*                  "ibm1163"                       */ CODEC_CP1163 },
	{ offsetof(struct codec_name_db_struct, db_CP1164_1), /*                  "ibm1164"                       */ CODEC_CP1164 },
	{ offsetof(struct codec_name_db_struct, db_CP1166_1), /*                  "ibm1166"                       */ CODEC_CP1166 },
	{ offsetof(struct codec_name_db_struct, db_KOI8_RU_2), /*                 "ibm1167"                       */ CODEC_KOI8_RU },
	{ offsetof(struct codec_name_db_struct, db_KOI8_U_4), /*                  "ibm1168"                       */ CODEC_KOI8_U },
	{ offsetof(struct codec_name_db_struct, db_PT154_5), /*                   "ibm1169"                       */ CODEC_PT154 },
	{ offsetof(struct codec_name_db_struct, db_CP1250_1), /*                  "ibm1250"                       */ CODEC_CP1250 },
	{ offsetof(struct codec_name_db_struct, db_CP1251_1), /*                  "ibm1251"                       */ CODEC_CP1251 },
	{ offsetof(struct codec_name_db_struct, db_CP1252_1), /*                  "ibm1252"                       */ CODEC_CP1252 },
	{ offsetof(struct codec_name_db_struct, db_CP1253_1), /*                  "ibm1253"                       */ CODEC_CP1253 },
	{ offsetof(struct codec_name_db_struct, db_CP1254_1), /*                  "ibm1254"                       */ CODEC_CP1254 },
	{ offsetof(struct codec_name_db_struct, db_CP1255_1), /*                  "ibm1255"                       */ CODEC_CP1255 },
	{ offsetof(struct codec_name_db_struct, db_CP1256_1), /*                  "ibm1256"                       */ CODEC_CP1256 },
	{ offsetof(struct codec_name_db_struct, db_CP1257_1), /*                  "ibm1257"                       */ CODEC_CP1257 },
	{ offsetof(struct codec_name_db_struct, db_CP1258_1), /*                  "ibm1258"                       */ CODEC_CP1258 },
	{ offsetof(struct codec_name_db_struct, db_CP12712_1), /*                 "ibm12712"                      */ CODEC_CP12712 },
	{ offsetof(struct codec_name_db_struct, db_CP1275_4), /*                  "ibm1275"                       */ CODEC_CP1275 },
	{ offsetof(struct codec_name_db_struct, db_CP10006_5), /*                 "ibm1280"                       */ CODEC_CP10006 },
	{ offsetof(struct codec_name_db_struct, db_CP1281_2), /*                  "ibm1281"                       */ CODEC_CP1281 },
	{ offsetof(struct codec_name_db_struct, db_CP1282_2), /*                  "ibm1282"                       */ CODEC_CP1282 },
	{ offsetof(struct codec_name_db_struct, db_CP10007_3), /*                 "ibm1283"                       */ CODEC_CP10007 },
	{ offsetof(struct codec_name_db_struct, db_CP1284_2), /*                  "ibm1284"                       */ CODEC_CP1284 },
	{ offsetof(struct codec_name_db_struct, db_CP1285_2), /*                  "ibm1285"                       */ CODEC_CP1285 },
	{ offsetof(struct codec_name_db_struct, db_CP1286_2), /*                  "ibm1286"                       */ CODEC_CP1286 },
	{ offsetof(struct codec_name_db_struct, db_IBM1364_0), /*                 "ibm1364"                       */ CODEC_IBM1364 },
	{ offsetof(struct codec_name_db_struct, db_IBM1371_0), /*                 "ibm1371"                       */ CODEC_IBM1371 },
	{ offsetof(struct codec_name_db_struct, db_IBM1388_0), /*                 "ibm1388"                       */ CODEC_IBM1388 },
	{ offsetof(struct codec_name_db_struct, db_IBM1390_0), /*                 "ibm1390"                       */ CODEC_IBM1390 },
	{ offsetof(struct codec_name_db_struct, db_IBM1399_0), /*                 "ibm1399"                       */ CODEC_IBM1399 },
	{ offsetof(struct codec_name_db_struct, db_IBM1401_0), /*                 "ibm1401"                       */ CODEC_IBM1401 },
	{ offsetof(struct codec_name_db_struct, db_CP16804_1), /*                 "ibm16804"                      */ CODEC_CP16804 },
	{ offsetof(struct codec_name_db_struct, db_IBM256_0), /*                  "ibm256"                        */ CODEC_IBM256 },
	{ offsetof(struct codec_name_db_struct, db_CP273_0), /*                   "ibm273"                        */ CODEC_CP273 },
	{ offsetof(struct codec_name_db_struct, db_CP274_0), /*                   "ibm274"                        */ CODEC_CP274 },
	{ offsetof(struct codec_name_db_struct, db_CP275_0), /*                   "ibm275"                        */ CODEC_CP275 },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_CP_DK_NO_0), /*         "ibm277"                        */ CODEC_EBCDIC_CP_DK_NO },
	{ offsetof(struct codec_name_db_struct, db_CP278_0), /*                   "ibm278"                        */ CODEC_CP278 },
	{ offsetof(struct codec_name_db_struct, db_CP280_0), /*                   "ibm280"                        */ CODEC_CP280 },
	{ offsetof(struct codec_name_db_struct, db_CP281_0), /*                   "ibm281"                        */ CODEC_CP281 },
	{ offsetof(struct codec_name_db_struct, db_CP284_0), /*                   "ibm284"                        */ CODEC_CP284 },
	{ offsetof(struct codec_name_db_struct, db_CP285_0), /*                   "ibm285"                        */ CODEC_CP285 },
	{ offsetof(struct codec_name_db_struct, db_CP290_0), /*                   "ibm290"                        */ CODEC_CP290 },
	{ offsetof(struct codec_name_db_struct, db_CP297_0), /*                   "ibm297"                        */ CODEC_CP297 },
	{ offsetof(struct codec_name_db_struct, db_ASCII_8), /*                   "ibm367"                        */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_CP37_0), /*                    "ibm37"                         */ CODEC_CP37 },
	{ offsetof(struct codec_name_db_struct, db_CP38_0), /*                    "ibm38"                         */ CODEC_CP38 },
	{ offsetof(struct codec_name_db_struct, db_CP420_0), /*                   "ibm420"                        */ CODEC_CP420 },
	{ offsetof(struct codec_name_db_struct, db_CP423_0), /*                   "ibm423"                        */ CODEC_CP423 },
	{ offsetof(struct codec_name_db_struct, db_CP424_0), /*                   "ibm424"                        */ CODEC_CP424 },
	{ offsetof(struct codec_name_db_struct, db_CP437_0), /*                   "ibm437"                        */ CODEC_CP437 },
	{ offsetof(struct codec_name_db_struct, db_CP4517_1), /*                  "ibm4517"                       */ CODEC_CP4517 },
	{ offsetof(struct codec_name_db_struct, db_CP4899_1), /*                  "ibm4899"                       */ CODEC_CP4899 },
	{ offsetof(struct codec_name_db_struct, db_CP4909_1), /*                  "ibm4909"                       */ CODEC_CP4909 },
	{ offsetof(struct codec_name_db_struct, db_CP4971_1), /*                  "ibm4971"                       */ CODEC_CP4971 },
	{ offsetof(struct codec_name_db_struct, db_CP500_0), /*                   "ibm500"                        */ CODEC_CP500 },
	{ offsetof(struct codec_name_db_struct, db_CP1008_4), /*                  "ibm5104"                       */ CODEC_CP1008 },
	{ offsetof(struct codec_name_db_struct, db_CP5347_1), /*                  "ibm5347"                       */ CODEC_CP5347 },
	{ offsetof(struct codec_name_db_struct, db_IBM704_0), /*                  "ibm704"                        */ CODEC_IBM704 },
	{ offsetof(struct codec_name_db_struct, db_CP708_1), /*                   "ibm708"                        */ CODEC_CP708 },
	{ offsetof(struct codec_name_db_struct, db_IBM7090_0), /*                 "ibm7090"                       */ CODEC_IBM7090 },
	{ offsetof(struct codec_name_db_struct, db_IBM7090_1), /*                 "ibm7094"                       */ CODEC_IBM7090 },
	{ offsetof(struct codec_name_db_struct, db_CP720_1), /*                   "ibm720"                        */ CODEC_CP720 },
	{ offsetof(struct codec_name_db_struct, db_CP737_1), /*                   "ibm737"                        */ CODEC_CP737 },
	{ offsetof(struct codec_name_db_struct, db_CP775_1), /*                   "ibm775"                        */ CODEC_CP775 },
	{ offsetof(struct codec_name_db_struct, db_CP803_1), /*                   "ibm803"                        */ CODEC_CP803 },
	{ offsetof(struct codec_name_db_struct, db_CP806_1), /*                   "ibm806"                        */ CODEC_CP806 },
	{ offsetof(struct codec_name_db_struct, db_CP808_0), /*                   "ibm808"                        */ CODEC_CP808 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_7_9), /*              "ibm813"                        */ CODEC_ISO_8859_7 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_1_5), /*              "ibm819"                        */ CODEC_ISO_8859_1 },
	{ offsetof(struct codec_name_db_struct, db_CP1125_4), /*                  "ibm848"                        */ CODEC_CP1125 },
	{ offsetof(struct codec_name_db_struct, db_CP850_0), /*                   "ibm850"                        */ CODEC_CP850 },
	{ offsetof(struct codec_name_db_struct, db_CP851_0), /*                   "ibm851"                        */ CODEC_CP851 },
	{ offsetof(struct codec_name_db_struct, db_CP852_0), /*                   "ibm852"                        */ CODEC_CP852 },
	{ offsetof(struct codec_name_db_struct, db_CP853_1), /*                   "ibm853"                        */ CODEC_CP853 },
	{ offsetof(struct codec_name_db_struct, db_CP855_0), /*                   "ibm855"                        */ CODEC_CP855 },
	{ offsetof(struct codec_name_db_struct, db_CP856_1), /*                   "ibm856"                        */ CODEC_CP856 },
	{ offsetof(struct codec_name_db_struct, db_CP857_0), /*                   "ibm857"                        */ CODEC_CP857 },
	{ offsetof(struct codec_name_db_struct, db_CP858_1), /*                   "ibm858"                        */ CODEC_CP858 },
	{ offsetof(struct codec_name_db_struct, db_CP859_1), /*                   "ibm859"                        */ CODEC_CP859 },
	{ offsetof(struct codec_name_db_struct, db_CP860_0), /*                   "ibm860"                        */ CODEC_CP860 },
	{ offsetof(struct codec_name_db_struct, db_CP861_0), /*                   "ibm861"                        */ CODEC_CP861 },
	{ offsetof(struct codec_name_db_struct, db_CP862_0), /*                   "ibm862"                        */ CODEC_CP862 },
	{ offsetof(struct codec_name_db_struct, db_CP863_0), /*                   "ibm863"                        */ CODEC_CP863 },
	{ offsetof(struct codec_name_db_struct, db_CP864_0), /*                   "ibm864"                        */ CODEC_CP864 },
	{ offsetof(struct codec_name_db_struct, db_CP865_0), /*                   "ibm865"                        */ CODEC_CP865 },
	{ offsetof(struct codec_name_db_struct, db_CP866_2), /*                   "ibm866"                        */ CODEC_CP866 },
	{ offsetof(struct codec_name_db_struct, db_CP866NAV_2), /*                "ibm866nav"                     */ CODEC_CP866NAV },
	{ offsetof(struct codec_name_db_struct, db_CP867_0), /*                   "ibm867"                        */ CODEC_CP867 },
	{ offsetof(struct codec_name_db_struct, db_CP868_0), /*                   "ibm868"                        */ CODEC_CP868 },
	{ offsetof(struct codec_name_db_struct, db_CP869_0), /*                   "ibm869"                        */ CODEC_CP869 },
	{ offsetof(struct codec_name_db_struct, db_CP870_0), /*                   "ibm870"                        */ CODEC_CP870 },
	{ offsetof(struct codec_name_db_struct, db_CP871_0), /*                   "ibm871"                        */ CODEC_CP871 },
	{ offsetof(struct codec_name_db_struct, db_CP874_1), /*                   "ibm874"                        */ CODEC_CP874 },
	{ offsetof(struct codec_name_db_struct, db_CP875_1), /*                   "ibm875"                        */ CODEC_CP875 },
	{ offsetof(struct codec_name_db_struct, db_KOI8_R_3), /*                  "ibm878"                        */ CODEC_KOI8_R },
	{ offsetof(struct codec_name_db_struct, db_CP880_0), /*                   "ibm880"                        */ CODEC_CP880 },
	{ offsetof(struct codec_name_db_struct, db_ASCII_15), /*                  "ibm891"                        */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_ISO646_JP_7), /*               "ibm895"                        */ CODEC_ISO646_JP },
	{ offsetof(struct codec_name_db_struct, db_CP896_1), /*                   "ibm896"                        */ CODEC_CP896 },
	{ offsetof(struct codec_name_db_struct, db_CP897_0), /*                   "ibm897"                        */ CODEC_CP897 },
	{ offsetof(struct codec_name_db_struct, db_CP901_1), /*                   "ibm901"                        */ CODEC_CP901 },
	{ offsetof(struct codec_name_db_struct, db_CP902_1), /*                   "ibm902"                        */ CODEC_CP902 },
	{ offsetof(struct codec_name_db_struct, db_ASCII_19), /*                  "ibm903"                        */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_CP9030_1), /*                  "ibm9030"                       */ CODEC_CP9030 },
	{ offsetof(struct codec_name_db_struct, db_CP904_0), /*                   "ibm904"                        */ CODEC_CP904 },
	{ offsetof(struct codec_name_db_struct, db_CP905_0), /*                   "ibm905"                        */ CODEC_CP905 },
	{ offsetof(struct codec_name_db_struct, db_CP9066_1), /*                  "ibm9066"                       */ CODEC_CP9066 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_2_14), /*             "ibm912"                        */ CODEC_ISO_8859_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_3_7), /*              "ibm913"                        */ CODEC_ISO_8859_3 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_4_7), /*              "ibm914"                        */ CODEC_ISO_8859_4 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_5_11), /*             "ibm915"                        */ CODEC_ISO_8859_5 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_8_6), /*              "ibm916"                        */ CODEC_ISO_8859_8 },
	{ offsetof(struct codec_name_db_struct, db_CP918_0), /*                   "ibm918"                        */ CODEC_CP918 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_10_8), /*             "ibm919"                        */ CODEC_ISO_8859_10 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_9_7), /*              "ibm920"                        */ CODEC_ISO_8859_9 },
	{ offsetof(struct codec_name_db_struct, db_CP921_1), /*                   "ibm921"                        */ CODEC_CP921 },
	{ offsetof(struct codec_name_db_struct, db_CP922_1), /*                   "ibm922"                        */ CODEC_CP922 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_15_6), /*             "ibm923"                        */ CODEC_ISO_8859_15 },
	{ offsetof(struct codec_name_db_struct, db_IBM930_0), /*                  "ibm930"                        */ CODEC_IBM930 },
	{ offsetof(struct codec_name_db_struct, db_IBM933_0), /*                  "ibm933"                        */ CODEC_IBM933 },
	{ offsetof(struct codec_name_db_struct, db_IBM935_0), /*                  "ibm935"                        */ CODEC_IBM935 },
	{ offsetof(struct codec_name_db_struct, db_IBM937_0), /*                  "ibm937"                        */ CODEC_IBM937 },
	{ offsetof(struct codec_name_db_struct, db_IBM939_0), /*                  "ibm939"                        */ CODEC_IBM939 },
	{ offsetof(struct codec_name_db_struct, db_CP1256_6), /*                  "ibm9448"                       */ CODEC_CP1256 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_143_0), /*              "iec-p27-1"                     */ CODEC_ISO_IR_143 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_143_3), /*              "iec-p271"                      */ CODEC_ISO_IR_143 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_INIS_SUBSET_0), /*      "inis"                          */ CODEC_ISO646_INIS_SUBSET },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_50_0), /*               "inis-8"                        */ CODEC_ISO_IR_50 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_51_0), /*               "inis-cyrillic"                 */ CODEC_ISO_IR_51 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_50_1), /*               "inis8"                         */ CODEC_ISO_IR_50 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_51_1), /*               "iniscyrillic"                  */ CODEC_ISO_IR_51 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_INV_1), /*              "invariant"                     */ CODEC_ISO646_INV },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_2_2), /*                "irv"                           */ CODEC_ISO_IR_2 },
	{ offsetof(struct codec_name_db_struct, db_ISIRI3342_1), /*               "isiri-3342"                    */ CODEC_ISIRI3342 },
	{ offsetof(struct codec_name_db_struct, db_ISIRI3342_0), /*               "isiri3342"                     */ CODEC_ISIRI3342 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_14_4), /*             "iso-celtic"                    */ CODEC_ISO_8859_14 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SE_1), /*               "iso-ir-10"                     */ CODEC_ISO646_SE },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_1_1), /*              "iso-ir-100"                    */ CODEC_ISO_8859_1 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_2_1), /*              "iso-ir-101"                    */ CODEC_ISO_8859_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_T_61_1), /*             "iso-ir-102"                    */ CODEC_ISO646_T_61 },
	{ offsetof(struct codec_name_db_struct, db_CP1036_7), /*                  "iso-ir-103"                    */ CODEC_CP1036 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_3_1), /*              "iso-ir-109"                    */ CODEC_ISO_8859_3 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SE2_1), /*              "iso-ir-11"                     */ CODEC_ISO646_SE2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_4_1), /*              "iso-ir-110"                    */ CODEC_ISO_8859_4 },
	{ offsetof(struct codec_name_db_struct, db_KOI8_E_2), /*                  "iso-ir-111"                    */ CODEC_KOI8_E },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CA_1), /*               "iso-ir-121"                    */ CODEC_ISO646_CA },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CA2_1), /*              "iso-ir-122"                    */ CODEC_ISO646_CA2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_123_1), /*              "iso-ir-123"                    */ CODEC_ISO_IR_123 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_7_1), /*              "iso-ir-126"                    */ CODEC_ISO_8859_7 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_6_1), /*              "iso-ir-127"                    */ CODEC_ISO_8859_6 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_13_2), /*               "iso-ir-13"                     */ CODEC_ISO_IR_13 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_8_1), /*              "iso-ir-138"                    */ CODEC_ISO_8859_8 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_139_1), /*              "iso-ir-139"                    */ CODEC_ISO_IR_139 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_JP_1), /*               "iso-ir-14"                     */ CODEC_ISO646_JP },
	{ offsetof(struct codec_name_db_struct, db_ISO646_YU_1), /*               "iso-ir-141"                    */ CODEC_ISO646_YU },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_143_1), /*              "iso-ir-143"                    */ CODEC_ISO_IR_143 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_5_1), /*              "iso-ir-144"                    */ CODEC_ISO_8859_5 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_146_1), /*              "iso-ir-146"                    */ CODEC_ISO_IR_146 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_147_2), /*              "iso-ir-147"                    */ CODEC_ISO_IR_147 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_9_1), /*              "iso-ir-148"                    */ CODEC_ISO_8859_9 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_IT_1), /*               "iso-ir-15"                     */ CODEC_ISO646_IT },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_150_1), /*              "iso-ir-150"                    */ CODEC_ISO_IR_150 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CU_2), /*               "iso-ir-151"                    */ CODEC_ISO646_CU },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_152_1), /*              "iso-ir-152"                    */ CODEC_ISO_IR_152 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_153_2), /*              "iso-ir-153"                    */ CODEC_ISO_IR_153 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_154_1), /*              "iso-ir-154"                    */ CODEC_ISO_IR_154 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_155_2), /*              "iso-ir-155"                    */ CODEC_ISO_IR_155 },
	{ offsetof(struct codec_name_db_struct, db_CP20269_3), /*                 "iso-ir-156"                    */ CODEC_CP20269 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_10_1), /*             "iso-ir-157"                    */ CODEC_ISO_8859_10 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_158_2), /*              "iso-ir-158"                    */ CODEC_ISO_IR_158 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_PT_1), /*               "iso-ir-16"                     */ CODEC_ISO646_PT },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_11_4), /*             "iso-ir-166"                    */ CODEC_ISO_8859_11 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_ES_1), /*               "iso-ir-17"                     */ CODEC_ISO646_ES },
	{ offsetof(struct codec_name_db_struct, db_ISO646_INV_0), /*              "iso-ir-170"                    */ CODEC_ISO646_INV },
	{ offsetof(struct codec_name_db_struct, db_CP921_6), /*                   "iso-ir-179"                    */ CODEC_CP921 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_18_2), /*               "iso-ir-18"                     */ CODEC_ISO_IR_18 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_182_0), /*              "iso-ir-182"                    */ CODEC_ISO_IR_182 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_19_1), /*               "iso-ir-19"                     */ CODEC_ISO_IR_19 },
	{ offsetof(struct codec_name_db_struct, db_UTF8_4), /*                    "iso-ir-193"                    */ CODEC_UTF8 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_197_0), /*              "iso-ir-197"                    */ CODEC_ISO_IR_197 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_14_3), /*             "iso-ir-199"                    */ CODEC_ISO_8859_14 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_2_1), /*                "iso-ir-2"                      */ CODEC_ISO_IR_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_200_0), /*              "iso-ir-200"                    */ CODEC_ISO_IR_200 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_201_0), /*              "iso-ir-201"                    */ CODEC_ISO_IR_201 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_15_3), /*             "iso-ir-203"                    */ CODEC_ISO_8859_15 },
	{ offsetof(struct codec_name_db_struct, db_CP901_3), /*                   "iso-ir-206"                    */ CODEC_CP901 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_IE_1), /*               "iso-ir-207"                    */ CODEC_ISO646_IE },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_209_0), /*              "iso-ir-209"                    */ CODEC_ISO_IR_209 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DE_1), /*               "iso-ir-21"                     */ CODEC_ISO646_DE },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_16_3), /*             "iso-ir-226"                    */ CODEC_ISO_8859_16 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FR1_1), /*              "iso-ir-25"                     */ CODEC_ISO646_FR1 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_LATIN_GR_MIXED_2), /*   "iso-ir-27"                     */ CODEC_ISO646_LATIN_GR_MIXED },
	{ offsetof(struct codec_name_db_struct, db_ISO_5427_1), /*                "iso-ir-37"                     */ CODEC_ISO_5427 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_GB_1), /*               "iso-ir-4"                      */ CODEC_ISO646_GB },
	{ offsetof(struct codec_name_db_struct, db_ISO646_VIEWDATA_1), /*         "iso-ir-47"                     */ CODEC_ISO646_VIEWDATA },
	{ offsetof(struct codec_name_db_struct, db_ISO646_INIS_SUBSET_1), /*      "iso-ir-49"                     */ CODEC_ISO646_INIS_SUBSET },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_50_2), /*               "iso-ir-50"                     */ CODEC_ISO_IR_50 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_51_2), /*               "iso-ir-51"                     */ CODEC_ISO_IR_51 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_54_1), /*               "iso-ir-54"                     */ CODEC_ISO_IR_54 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_55_2), /*               "iso-ir-55"                     */ CODEC_ISO_IR_55 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CN_1), /*               "iso-ir-57"                     */ CODEC_ISO646_CN },
	{ offsetof(struct codec_name_db_struct, db_ASCII_1), /*                   "iso-ir-6"                      */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NO_1), /*               "iso-ir-60"                     */ CODEC_ISO646_NO },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NO2_2), /*              "iso-ir-61"                     */ CODEC_ISO646_NO2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_68_0), /*               "iso-ir-68"                     */ CODEC_ISO_IR_68 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FR_1), /*               "iso-ir-69"                     */ CODEC_ISO646_FR },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SEFI_NATS_0), /*        "iso-ir-8"                      */ CODEC_ISO646_SEFI_NATS },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_8_1_2), /*              "iso-ir-8-1"                    */ CODEC_ISO_IR_8_1 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_8_2_1), /*              "iso-ir-8-2"                    */ CODEC_ISO_IR_8_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_PT2_1), /*              "iso-ir-84"                     */ CODEC_ISO646_PT2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_ES2_1), /*              "iso-ir-85"                     */ CODEC_ISO646_ES2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_HU_1), /*               "iso-ir-86"                     */ CODEC_ISO646_HU },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_88_1), /*               "iso-ir-88"                     */ CODEC_ISO_IR_88 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_89_3), /*               "iso-ir-89"                     */ CODEC_ISO_IR_89 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NATS_DANO_1), /*        "iso-ir-9-1"                    */ CODEC_ISO646_NATS_DANO },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_9_2_1), /*              "iso-ir-9-2"                    */ CODEC_ISO_IR_9_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_6937_2_3), /*              "iso-ir-90"                     */ CODEC_ISO_6937_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_91_1), /*               "iso-ir-91"                     */ CODEC_ISO_IR_91 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_JP_OCR_B_1), /*         "iso-ir-92"                     */ CODEC_ISO646_JP_OCR_B },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_93_1), /*               "iso-ir-93"                     */ CODEC_ISO_IR_93 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_94_1), /*               "iso-ir-94"                     */ CODEC_ISO_IR_94 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_95_1), /*               "iso-ir-95"                     */ CODEC_ISO_IR_95 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_96_1), /*               "iso-ir-96"                     */ CODEC_ISO_IR_96 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_98_2), /*               "iso-ir-98"                     */ CODEC_ISO_IR_98 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_155_0), /*              "iso10367-box"                  */ CODEC_ISO_IR_155 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_155_1), /*              "iso10367box"                   */ CODEC_ISO_IR_155 },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_15), /*                "iso10646"                      */ CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_13), /*                "iso10646"                      */ CODEC_UTF32LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_12), /*                "iso10646-ucs-2"                */ CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_12), /*                "iso10646-ucs-2"                */ CODEC_UTF16LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_11), /*                "iso10646-ucs-4"                */ CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_9), /*                 "iso10646-ucs-4"                */ CODEC_UTF32LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_11), /*                "iso10646/ucs2"                 */ CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_11), /*                "iso10646/ucs2"                 */ CODEC_UTF16LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_10), /*                "iso10646/ucs4"                 */ CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_8), /*                 "iso10646/ucs4"                 */ CODEC_UTF32LE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_UTF8_3), /*                    "iso10646/utf-8"                */ CODEC_UTF8 },
	{ offsetof(struct codec_name_db_struct, db_UTF8_2), /*                    "iso10646/utf8"                 */ CODEC_UTF8 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_98_1), /*               "iso2033"                       */ CODEC_ISO_IR_98 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_98_0), /*               "iso2033-1983"                  */ CODEC_ISO_IR_98 },
	{ offsetof(struct codec_name_db_struct, db_ISO5426_0), /*                 "iso5426"                       */ CODEC_ISO5426 },
	{ offsetof(struct codec_name_db_struct, db_ISO5426_2_0), /*               "iso5426-2"                     */ CODEC_ISO5426_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_5427_0), /*                "iso5427"                       */ CODEC_ISO_5427 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_54_4), /*               "iso5427-ext"                   */ CODEC_ISO_IR_54 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_54_0), /*               "iso5427:1981"                  */ CODEC_ISO_IR_54 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_54_2), /*               "iso5427cyrillic1981"           */ CODEC_ISO_IR_54 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_54_5), /*               "iso5427ext"                    */ CODEC_ISO_IR_54 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_55_1), /*               "iso5428"                       */ CODEC_ISO_IR_55 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_55_0), /*               "iso5428:1980"                  */ CODEC_ISO_IR_55 },
	{ offsetof(struct codec_name_db_struct, db_ISO6438_0), /*                 "iso6438"                       */ CODEC_ISO6438 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CA_2), /*               "iso646-ca"                     */ CODEC_ISO646_CA },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CA2_2), /*              "iso646-ca2"                    */ CODEC_ISO646_CA2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CN_3), /*               "iso646-cn"                     */ CODEC_ISO646_CN },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CU_3), /*               "iso646-cu"                     */ CODEC_ISO646_CU },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DE_3), /*               "iso646-de"                     */ CODEC_ISO646_DE },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DK_2), /*               "iso646-dk"                     */ CODEC_ISO646_DK },
	{ offsetof(struct codec_name_db_struct, db_ISO646_ES_2), /*               "iso646-es"                     */ CODEC_ISO646_ES },
	{ offsetof(struct codec_name_db_struct, db_ISO646_ES2_2), /*              "iso646-es2"                    */ CODEC_ISO646_ES2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SE_3), /*               "iso646-fi"                     */ CODEC_ISO646_SE },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FR_2), /*               "iso646-fr"                     */ CODEC_ISO646_FR },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FR1_2), /*              "iso646-fr1"                    */ CODEC_ISO646_FR1 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_GB_2), /*               "iso646-gb"                     */ CODEC_ISO646_GB },
	{ offsetof(struct codec_name_db_struct, db_ISO646_HU_2), /*               "iso646-hu"                     */ CODEC_ISO646_HU },
	{ offsetof(struct codec_name_db_struct, db_ISO646_IE_0), /*               "iso646-ie"                     */ CODEC_ISO646_IE },
	{ offsetof(struct codec_name_db_struct, db_ISO646_IS_0), /*               "iso646-is"                     */ CODEC_ISO646_IS },
	{ offsetof(struct codec_name_db_struct, db_ISO646_IT_2), /*               "iso646-it"                     */ CODEC_ISO646_IT },
	{ offsetof(struct codec_name_db_struct, db_ISO646_JP_3), /*               "iso646-jp"                     */ CODEC_ISO646_JP },
	{ offsetof(struct codec_name_db_struct, db_ISO646_JP_OCR_B_2), /*         "iso646-jp-ocr-b"               */ CODEC_ISO646_JP_OCR_B },
	{ offsetof(struct codec_name_db_struct, db_ISO646_KR_1), /*               "iso646-kr"                     */ CODEC_ISO646_KR },
	{ offsetof(struct codec_name_db_struct, db_ISO646_MT_0), /*               "iso646-mt"                     */ CODEC_ISO646_MT },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NL_0), /*               "iso646-nl"                     */ CODEC_ISO646_NL },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NO_2), /*               "iso646-no"                     */ CODEC_ISO646_NO },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NO2_1), /*              "iso646-no2"                    */ CODEC_ISO646_NO2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_PT_2), /*               "iso646-pt"                     */ CODEC_ISO646_PT },
	{ offsetof(struct codec_name_db_struct, db_ISO646_PT2_2), /*              "iso646-pt2"                    */ CODEC_ISO646_PT2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SE_4), /*               "iso646-se"                     */ CODEC_ISO646_SE },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SE2_2), /*              "iso646-se2"                    */ CODEC_ISO646_SE2 },
	{ offsetof(struct codec_name_db_struct, db_ASCII_5), /*                   "iso646-us"                     */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_ISO646_YU_2), /*               "iso646-yu"                     */ CODEC_ISO646_YU },
	{ offsetof(struct codec_name_db_struct, db_ISO646_BASIC_0), /*            "iso646.basic:1983"             */ CODEC_ISO646_BASIC },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_2_0), /*                "iso646.irv:1983"               */ CODEC_ISO_IR_2 },
	{ offsetof(struct codec_name_db_struct, db_ASCII_3), /*                   "iso646.irv:1991"               */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_CP20269_2), /*                 "iso6937"                       */ CODEC_CP20269 },
	{ offsetof(struct codec_name_db_struct, db_ISO_6937_2_0), /*              "iso6937-2"                     */ CODEC_ISO_6937_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_152_0), /*              "iso6937-2-25"                  */ CODEC_ISO_IR_152 },
	{ offsetof(struct codec_name_db_struct, db_ISO_6937_2_2), /*              "iso6937-2:1983"                */ CODEC_ISO_6937_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_6937_2_1), /*              "iso69372"                      */ CODEC_ISO_6937_2 },
	{ offsetof(struct codec_name_db_struct, db_CP20269_4), /*                 "iso6937:1992"                  */ CODEC_CP20269 },
	{ offsetof(struct codec_name_db_struct, db_CP1006_2), /*                  "iso8-bit-urdu"                 */ CODEC_CP1006 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_1_2), /*              "iso8859-1"                     */ CODEC_ISO_8859_1 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_1_14), /*             "iso8859-1-i"                   */ CODEC_ISO_8859_1 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_10_4), /*             "iso8859-10"                    */ CODEC_ISO_8859_10 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_10_5), /*             "iso8859-10:1992"               */ CODEC_ISO_8859_10 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_11_0), /*             "iso8859-11"                    */ CODEC_ISO_8859_11 },
	{ offsetof(struct codec_name_db_struct, db_CP921_4), /*                   "iso8859-13"                    */ CODEC_CP921 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_14_0), /*             "iso8859-14"                    */ CODEC_ISO_8859_14 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_14_1), /*             "iso8859-14:1998"               */ CODEC_ISO_8859_14 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_15_0), /*             "iso8859-15"                    */ CODEC_ISO_8859_15 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_15_13), /*            "iso8859-15-fdis"               */ CODEC_ISO_8859_15 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_15_1), /*             "iso8859-15:1998"               */ CODEC_ISO_8859_15 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_16_0), /*             "iso8859-16"                    */ CODEC_ISO_8859_16 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_16_1), /*             "iso8859-16:2001"               */ CODEC_ISO_8859_16 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_1_0), /*              "iso8859-1:1987"                */ CODEC_ISO_8859_1 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_2_2), /*              "iso8859-2"                     */ CODEC_ISO_8859_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_2_0), /*              "iso8859-2:1987"                */ CODEC_ISO_8859_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_3_2), /*              "iso8859-3"                     */ CODEC_ISO_8859_3 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_3_0), /*              "iso8859-3:1988"                */ CODEC_ISO_8859_3 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_4_2), /*              "iso8859-4"                     */ CODEC_ISO_8859_4 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_4_0), /*              "iso8859-4:1988"                */ CODEC_ISO_8859_4 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_5_2), /*              "iso8859-5"                     */ CODEC_ISO_8859_5 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_5_0), /*              "iso8859-5:1988"                */ CODEC_ISO_8859_5 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_6_2), /*              "iso8859-6"                     */ CODEC_ISO_8859_6 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_6_14), /*             "iso8859-6-i"                   */ CODEC_ISO_8859_6 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_6_0), /*              "iso8859-6:1987"                */ CODEC_ISO_8859_6 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_7_2), /*              "iso8859-7"                     */ CODEC_ISO_8859_7 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_7_0), /*              "iso8859-7:1987"                */ CODEC_ISO_8859_7 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_7_7), /*              "iso8859-7:2003"                */ CODEC_ISO_8859_7 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_8_2), /*              "iso8859-8"                     */ CODEC_ISO_8859_8 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_8_12), /*             "iso8859-8-i"                   */ CODEC_ISO_8859_8 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_8_0), /*              "iso8859-8:1988"                */ CODEC_ISO_8859_8 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_9_2), /*              "iso8859-9"                     */ CODEC_ISO_8859_9 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_9_0), /*              "iso8859-9:1989"                */ CODEC_ISO_8859_9 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_9E_0), /*             "iso8859-9e"                    */ CODEC_ISO_8859_9E },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_154_0), /*              "iso8859-supp"                  */ CODEC_ISO_IR_154 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_1_7), /*              "iso88591"                      */ CODEC_ISO_8859_1 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_10_6), /*             "iso885910"                     */ CODEC_ISO_8859_10 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_11_1), /*             "iso885911"                     */ CODEC_ISO_8859_11 },
	{ offsetof(struct codec_name_db_struct, db_CP921_5), /*                   "iso885913"                     */ CODEC_CP921 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_14_2), /*             "iso885914"                     */ CODEC_ISO_8859_14 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_15_2), /*             "iso885915"                     */ CODEC_ISO_8859_15 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_16_2), /*             "iso885916"                     */ CODEC_ISO_8859_16 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_2_5), /*              "iso88592"                      */ CODEC_ISO_8859_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_3_5), /*              "iso88593"                      */ CODEC_ISO_8859_3 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_4_5), /*              "iso88594"                      */ CODEC_ISO_8859_4 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_5_4), /*              "iso88595"                      */ CODEC_ISO_8859_5 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_6_6), /*              "iso88596"                      */ CODEC_ISO_8859_6 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_7_13), /*             "iso88597"                      */ CODEC_ISO_8859_7 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_8_4), /*              "iso88598"                      */ CODEC_ISO_8859_8 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_9_5), /*              "iso88599"                      */ CODEC_ISO_8859_9 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_9E_1), /*             "iso88599e"                     */ CODEC_ISO_8859_9E },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_89_1), /*               "iso9036"                       */ CODEC_ISO_IR_89 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_14_11), /*            "isoceltic"                     */ CODEC_ISO_8859_14 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_IT_0), /*               "it"                            */ CODEC_ISO646_IT },
	{ offsetof(struct codec_name_db_struct, db_JIS_C_6229_OCR_A_0), /*        "jis-c-6229-ocr-a"              */ CODEC_JIS_C_6229_OCR_A },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_13_1), /*               "jis-c6220-1969"                */ CODEC_ISO_IR_13 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_13_0), /*               "jis-c6220-1969-jp"             */ CODEC_ISO_IR_13 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_JP_0), /*               "jis-c6220-1969-ro"             */ CODEC_ISO646_JP },
	{ offsetof(struct codec_name_db_struct, db_ISO646_JP_5), /*               "jis-c62201969ro"               */ CODEC_ISO646_JP },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_91_0), /*               "jis-c6229-1984-a"              */ CODEC_ISO_IR_91 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_JP_OCR_B_0), /*         "jis-c6229-1984-b"              */ CODEC_ISO646_JP_OCR_B },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_93_0), /*               "jis-c6229-1984-b-add"          */ CODEC_ISO_IR_93 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_94_0), /*               "jis-c6229-1984-hand"           */ CODEC_ISO_IR_94 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_95_0), /*               "jis-c6229-1984-hand-add"       */ CODEC_ISO_IR_95 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_96_0), /*               "jis-c6229-1984-kana"           */ CODEC_ISO_IR_96 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_JP_OCR_B_5), /*         "jis-c62291984b"                */ CODEC_ISO646_JP_OCR_B },
	{ offsetof(struct codec_name_db_struct, db_X0201_0), /*                   "jis-x201"                      */ CODEC_X0201 },
	{ offsetof(struct codec_name_db_struct, db_X0201_3), /*                   "jis201"                        */ CODEC_X0201 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_JP_2), /*               "jp"                            */ CODEC_ISO646_JP },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_91_2), /*               "jp-ocr-a"                      */ CODEC_ISO_IR_91 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_JP_OCR_B_3), /*         "jp-ocr-b"                      */ CODEC_ISO646_JP_OCR_B },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_93_2), /*               "jp-ocr-b-add"                  */ CODEC_ISO_IR_93 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_94_2), /*               "jp-ocr-hand"                   */ CODEC_ISO_IR_94 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_95_2), /*               "jp-ocr-hand-add"               */ CODEC_ISO_IR_95 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_YU_3), /*               "js"                            */ CODEC_ISO646_YU },
	{ offsetof(struct codec_name_db_struct, db_ISO646_YU_0), /*               "jus-i.b1.2"                    */ CODEC_ISO646_YU },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_147_0), /*              "jus-i.b1.3-mac"                */ CODEC_ISO_IR_147 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_146_0), /*              "jus-i.b1.3-serb"               */ CODEC_ISO_IR_146 },
	{ offsetof(struct codec_name_db_struct, db_KEYBCS2_3), /*                 "kamenicky"                     */ CODEC_KEYBCS2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_13_3), /*               "katakana"                      */ CODEC_ISO_IR_13 },
	{ offsetof(struct codec_name_db_struct, db_CP771_1), /*                   "kbl"                           */ CODEC_CP771 },
	{ offsetof(struct codec_name_db_struct, db_KEYBCS2_2), /*                 "keybcs2"                       */ CODEC_KEYBCS2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_5427_4), /*                "koi0"                          */ CODEC_ISO_5427 },
	{ offsetof(struct codec_name_db_struct, db_ISO_5427_2), /*                "koi7"                          */ CODEC_ISO_5427 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_IRV_1983_4), /*         "koi7-n0"                       */ CODEC_ISO646_IRV_1983 },
	{ offsetof(struct codec_name_db_struct, db_ISO_5427_3), /*                "koi7-n1"                       */ CODEC_ISO_5427 },
	{ offsetof(struct codec_name_db_struct, db_KOI7_N2_0), /*                 "koi7-n2"                       */ CODEC_KOI7_N2 },
	{ offsetof(struct codec_name_db_struct, db_KOI8_R_5), /*                  "koi8"                          */ CODEC_KOI8_R },
	{ offsetof(struct codec_name_db_struct, db_KOI8_B_0), /*                  "koi8-b"                        */ CODEC_KOI8_B },
	{ offsetof(struct codec_name_db_struct, db_KOI8_E_4), /*                  "koi8-e"                        */ CODEC_KOI8_E },
	{ offsetof(struct codec_name_db_struct, db_KOI8_F_0), /*                  "koi8-f"                        */ CODEC_KOI8_F },
	{ offsetof(struct codec_name_db_struct, db_KOI8_N1_0), /*                 "koi8-n1"                       */ CODEC_KOI8_N1 },
	{ offsetof(struct codec_name_db_struct, db_KOI8_N2_0), /*                 "koi8-n2"                       */ CODEC_KOI8_N2 },
	{ offsetof(struct codec_name_db_struct, db_KOI8_R_0), /*                  "koi8-r"                        */ CODEC_KOI8_R },
	{ offsetof(struct codec_name_db_struct, db_KOI8_RU_0), /*                 "koi8-ru"                       */ CODEC_KOI8_RU },
	{ offsetof(struct codec_name_db_struct, db_KOI8_T_0), /*                  "koi8-t"                        */ CODEC_KOI8_T },
	{ offsetof(struct codec_name_db_struct, db_KOI8_U_0), /*                  "koi8-u"                        */ CODEC_KOI8_U },
	{ offsetof(struct codec_name_db_struct, db_KOI8_F_1), /*                  "koi8-unified"                  */ CODEC_KOI8_F },
	{ offsetof(struct codec_name_db_struct, db_KOI8_U_1), /*                  "koi8u"                         */ CODEC_KOI8_U },
	{ offsetof(struct codec_name_db_struct, db_ISO646_KR_3), /*               "ks-x-1003"                     */ CODEC_ISO646_KR },
	{ offsetof(struct codec_name_db_struct, db_ISO646_KR_0), /*               "ksc5636"                       */ CODEC_ISO646_KR },
	{ offsetof(struct codec_name_db_struct, db_ISO646_KR_4), /*               "ksc5636-1989"                  */ CODEC_ISO646_KR },
	{ offsetof(struct codec_name_db_struct, db_KZ_1048_0), /*                 "kz-1048"                       */ CODEC_KZ_1048 },
	{ offsetof(struct codec_name_db_struct, db_KZ_1048_1), /*                 "kz1048"                        */ CODEC_KZ_1048 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_1_4), /*              "l1"                            */ CODEC_ISO_8859_1 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_16_5), /*             "l10"                           */ CODEC_ISO_8859_16 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_2_4), /*              "l2"                            */ CODEC_ISO_8859_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_3_4), /*              "l3"                            */ CODEC_ISO_8859_3 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_4_4), /*              "l4"                            */ CODEC_ISO_8859_4 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_9_4), /*              "l5"                            */ CODEC_ISO_8859_9 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_10_2), /*             "l6"                            */ CODEC_ISO_8859_10 },
	{ offsetof(struct codec_name_db_struct, db_CP921_9), /*                   "l7"                            */ CODEC_CP921 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_14_6), /*             "l8"                            */ CODEC_ISO_8859_14 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_15_11), /*            "l9"                            */ CODEC_ISO_8859_15 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_158_1), /*              "lap"                           */ CODEC_ISO_IR_158 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_19_0), /*               "latin-greek"                   */ CODEC_ISO_IR_19 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_LATIN_GR_MIXED_0), /*   "latin-greek-1"                 */ CODEC_ISO646_LATIN_GR_MIXED },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_158_0), /*              "latin-lap"                     */ CODEC_ISO_IR_158 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_15_5), /*             "latin0"                        */ CODEC_ISO_8859_15 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_1_3), /*              "latin1"                        */ CODEC_ISO_8859_1 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_154_2), /*              "latin1-2-5"                    */ CODEC_ISO_IR_154 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_16_4), /*             "latin10"                       */ CODEC_ISO_8859_16 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_2_3), /*              "latin2"                        */ CODEC_ISO_8859_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_3_3), /*              "latin3"                        */ CODEC_ISO_8859_3 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_4_3), /*              "latin4"                        */ CODEC_ISO_8859_4 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_9_3), /*              "latin5"                        */ CODEC_ISO_8859_9 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_10_0), /*             "latin6"                        */ CODEC_ISO_8859_10 },
	{ offsetof(struct codec_name_db_struct, db_CP921_8), /*                   "latin7"                        */ CODEC_CP921 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_14_5), /*             "latin8"                        */ CODEC_ISO_8859_14 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_15_4), /*             "latin9"                        */ CODEC_ISO_8859_15 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_19_2), /*               "latingreek"                    */ CODEC_ISO_IR_19 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_LATIN_GR_MIXED_1), /*   "latingreek1"                   */ CODEC_ISO646_LATIN_GR_MIXED },
	{ offsetof(struct codec_name_db_struct, db_LICS_0), /*                    "lics"                          */ CODEC_LICS },
	{ offsetof(struct codec_name_db_struct, db_CP774_3), /*                   "lst-1283"                      */ CODEC_CP774 },
	{ offsetof(struct codec_name_db_struct, db_CP772_1), /*                   "lst-1284"                      */ CODEC_CP772 },
	{ offsetof(struct codec_name_db_struct, db_CP772_2), /*                   "lst-1284:1993"                 */ CODEC_CP772 },
	{ offsetof(struct codec_name_db_struct, db_CP1257_3), /*                  "lst-1590-3"                    */ CODEC_CP1257 },
	{ offsetof(struct codec_name_db_struct, db_LY1_0), /*                     "ly1"                           */ CODEC_LY1 },
	{ offsetof(struct codec_name_db_struct, db_CP1275_1), /*                  "mac"                           */ CODEC_CP1275 },
	{ offsetof(struct codec_name_db_struct, db_CP1282_6), /*                  "mac-centraleurope"             */ CODEC_CP1282 },
	{ offsetof(struct codec_name_db_struct, db_CP10007_7), /*                 "mac-cyrillic"                  */ CODEC_CP10007 },
	{ offsetof(struct codec_name_db_struct, db_MACIS_1), /*                   "mac-is"                        */ CODEC_MACIS },
	{ offsetof(struct codec_name_db_struct, db_MAC_OS_THAI_0), /*             "mac-os-thai"                   */ CODEC_MAC_OS_THAI },
	{ offsetof(struct codec_name_db_struct, db_MAC_SAMI_0), /*                "mac-sami"                      */ CODEC_MAC_SAMI },
	{ offsetof(struct codec_name_db_struct, db_CP10017_4), /*                 "mac-uk"                        */ CODEC_CP10017 },
	{ offsetof(struct codec_name_db_struct, db_CP10004_3), /*                 "macarabic"                     */ CODEC_CP10004 },
	{ offsetof(struct codec_name_db_struct, db_CP1282_0), /*                  "maccentraleurope"              */ CODEC_CP1282 },
	{ offsetof(struct codec_name_db_struct, db_CP1284_0), /*                  "maccroatian"                   */ CODEC_CP1284 },
	{ offsetof(struct codec_name_db_struct, db_CP10007_8), /*                 "maccyrillic"                   */ CODEC_CP10007 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_147_1), /*              "macedonian"                    */ CODEC_ISO_IR_147 },
	{ offsetof(struct codec_name_db_struct, db_X_MAC_FARSI_1), /*             "macfarsi"                      */ CODEC_X_MAC_FARSI },
	{ offsetof(struct codec_name_db_struct, db_CP10006_4), /*                 "macgreek"                      */ CODEC_CP10006 },
	{ offsetof(struct codec_name_db_struct, db_CP1286_0), /*                  "maciceland"                    */ CODEC_CP1286 },
	{ offsetof(struct codec_name_db_struct, db_CP1275_0), /*                  "macintosh"                     */ CODEC_CP1275 },
	{ offsetof(struct codec_name_db_struct, db_MACINTOSH_FONT_X_0), /*        "macintosh-font-x"              */ CODEC_MACINTOSH_FONT_X },
	{ offsetof(struct codec_name_db_struct, db_MACINTOSH_LATIN_0), /*         "macintosh-latin"               */ CODEC_MACINTOSH_LATIN },
	{ offsetof(struct codec_name_db_struct, db_MACIS_0), /*                   "macis"                         */ CODEC_MACIS },
	{ offsetof(struct codec_name_db_struct, db_CP1275_8), /*                  "macroman"                      */ CODEC_CP1275 },
	{ offsetof(struct codec_name_db_struct, db_CP1285_0), /*                  "macromania"                    */ CODEC_CP1285 },
	{ offsetof(struct codec_name_db_struct, db_ADOBE_SYMBOL_ENCODING_0), /*   "macsymbol"                     */ CODEC_ADOBE_SYMBOL_ENCODING },
	{ offsetof(struct codec_name_db_struct, db_CP1281_0), /*                  "macturkish"                    */ CODEC_CP1281 },
	{ offsetof(struct codec_name_db_struct, db_CP10017_3), /*                 "macuk"                         */ CODEC_CP10017 },
	{ offsetof(struct codec_name_db_struct, db_CP10017_5), /*                 "macukrainian"                  */ CODEC_CP10017 },
	{ offsetof(struct codec_name_db_struct, db_CP667_4), /*                   "maz"                           */ CODEC_CP667 },
	{ offsetof(struct codec_name_db_struct, db_CP667_0), /*                   "mazovia"                       */ CODEC_CP667 },
	{ offsetof(struct codec_name_db_struct, db_MIK_0), /*                     "mik"                           */ CODEC_MIK },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DE_5), /*               "ms-10206"                      */ CODEC_ISO646_DE },
	{ offsetof(struct codec_name_db_struct, db_CP1252_4), /*                  "ms-ansi"                       */ CODEC_CP1252 },
	{ offsetof(struct codec_name_db_struct, db_CP1256_4), /*                  "ms-arab"                       */ CODEC_CP1256 },
	{ offsetof(struct codec_name_db_struct, db_CP1251_4), /*                  "ms-cyrl"                       */ CODEC_CP1251 },
	{ offsetof(struct codec_name_db_struct, db_CP1250_4), /*                  "ms-ee"                         */ CODEC_CP1250 },
	{ offsetof(struct codec_name_db_struct, db_CP1253_4), /*                  "ms-greek"                      */ CODEC_CP1253 },
	{ offsetof(struct codec_name_db_struct, db_CP1255_4), /*                  "ms-hebr"                       */ CODEC_CP1255 },
	{ offsetof(struct codec_name_db_struct, db_CP10007_4), /*                 "ms-mac-cyrillic"               */ CODEC_CP10007 },
	{ offsetof(struct codec_name_db_struct, db_CP1254_4), /*                  "ms-turk"                       */ CODEC_CP1254 },
	{ offsetof(struct codec_name_db_struct, db_CP874_5), /*                   "ms874"                         */ CODEC_CP874 },
	{ offsetof(struct codec_name_db_struct, db_MSDOS1252_0), /*               "msdos-1252"                    */ CODEC_MSDOS1252 },
	{ offsetof(struct codec_name_db_struct, db_CP10007_5), /*                 "msmaccyrillic"                 */ CODEC_CP10007 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_HU_0), /*               "msz-7795.3"                    */ CODEC_ISO646_HU },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NATS_DANO_0), /*        "nats-dano"                     */ CODEC_ISO646_NATS_DANO },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_9_2_0), /*              "nats-dano-add"                 */ CODEC_ISO_IR_9_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_8_1_0), /*              "nats-sefi"                     */ CODEC_ISO_IR_8_1 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_8_2_0), /*              "nats-sefi-add"                 */ CODEC_ISO_IR_8_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NATS_DANO_5), /*        "natsdano"                      */ CODEC_ISO646_NATS_DANO },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_8_1_1), /*              "natssefi"                      */ CODEC_ISO_IR_8_1 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CU_4), /*               "nc-nc0-10"                     */ CODEC_ISO646_CU },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CU_0), /*               "nc-nc0-10:81"                  */ CODEC_ISO646_CU },
	{ offsetof(struct codec_name_db_struct, db_ISO646_CU_6), /*               "nc-nc10"                       */ CODEC_ISO646_CU },
	{ offsetof(struct codec_name_db_struct, db_KEYBCS2_0), /*                 "nec-867"                       */ CODEC_KEYBCS2 },
	{ offsetof(struct codec_name_db_struct, db_NEXTSTEP_0), /*                "nextstep"                      */ CODEC_NEXTSTEP },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FR_0), /*               "nf-z-62-10"                    */ CODEC_ISO646_FR },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FR1_0), /*              "nf-z-62-10-(1973)"             */ CODEC_ISO646_FR1 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FR_5), /*               "nf-z-62-10-(1983)"             */ CODEC_ISO646_FR },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FR1_3), /*              "nf-z-62-10-1973"               */ CODEC_ISO646_FR1 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FR_4), /*               "nf-z-62-10-1983"               */ CODEC_ISO646_FR },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FR_7), /*               "nf-z-62010"                    */ CODEC_ISO646_FR },
	{ offsetof(struct codec_name_db_struct, db_ISO646_FR1_5), /*              "nf-z-62010-1973"               */ CODEC_ISO646_FR1 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NO_3), /*               "no"                            */ CODEC_ISO646_NO },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NO2_3), /*              "no2"                           */ CODEC_ISO646_NO2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NO_0), /*               "ns-4551-1"                     */ CODEC_ISO646_NO },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NO2_0), /*              "ns-4551-2"                     */ CODEC_ISO646_NO2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NO_6), /*               "ns-45511"                      */ CODEC_ISO646_NO },
	{ offsetof(struct codec_name_db_struct, db_ISO646_NO2_5), /*              "ns-45512"                      */ CODEC_ISO646_NO2 },
	{ offsetof(struct codec_name_db_struct, db_CP720_2), /*                   "oem720"                        */ CODEC_CP720 },
	{ offsetof(struct codec_name_db_struct, db_CP737_2), /*                   "oem737"                        */ CODEC_CP737 },
	{ offsetof(struct codec_name_db_struct, db_CP775_2), /*                   "oem775"                        */ CODEC_CP775 },
	{ offsetof(struct codec_name_db_struct, db_CP850_4), /*                   "oem850"                        */ CODEC_CP850 },
	{ offsetof(struct codec_name_db_struct, db_CP855_3), /*                   "oem855"                        */ CODEC_CP855 },
	{ offsetof(struct codec_name_db_struct, db_CP857_3), /*                   "oem857"                        */ CODEC_CP857 },
	{ offsetof(struct codec_name_db_struct, db_CP858_2), /*                   "oem858"                        */ CODEC_CP858 },
	{ offsetof(struct codec_name_db_struct, db_CP860_3), /*                   "oem860"                        */ CODEC_CP860 },
	{ offsetof(struct codec_name_db_struct, db_CP861_3), /*                   "oem861"                        */ CODEC_CP861 },
	{ offsetof(struct codec_name_db_struct, db_CP862_3), /*                   "oem862"                        */ CODEC_CP862 },
	{ offsetof(struct codec_name_db_struct, db_CP863_3), /*                   "oem863"                        */ CODEC_CP863 },
	{ offsetof(struct codec_name_db_struct, db_CP865_3), /*                   "oem865"                        */ CODEC_CP865 },
	{ offsetof(struct codec_name_db_struct, db_CP869_4), /*                   "oem869"                        */ CODEC_CP869 },
	{ offsetof(struct codec_name_db_struct, db_CP437_4), /*                   "oemus"                         */ CODEC_CP437 },
	{ offsetof(struct codec_name_db_struct, db_CP1004_3), /*                  "os2latin1"                     */ CODEC_CP1004 },
	{ offsetof(struct codec_name_db_struct, db_OSD_EBCDIC_DF03_IRV_0), /*     "osd-ebcdic-df3-irv"            */ CODEC_OSD_EBCDIC_DF03_IRV },
	{ offsetof(struct codec_name_db_struct, db_OSD_EBCDIC_DF04_1_0), /*       "osd-ebcdic-df4-1"              */ CODEC_OSD_EBCDIC_DF04_1 },
	{ offsetof(struct codec_name_db_struct, db_OSD_EBCDIC_DF04_15_0), /*      "osd-ebcdic-df4-15"             */ CODEC_OSD_EBCDIC_DF04_15 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_1_16), /*             "osf10001"                      */ CODEC_ISO_8859_1 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_2_12), /*             "osf10002"                      */ CODEC_ISO_8859_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_3_12), /*             "osf10003"                      */ CODEC_ISO_8859_3 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_4_12), /*             "osf10004"                      */ CODEC_ISO_8859_4 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_5_9), /*              "osf10005"                      */ CODEC_ISO_8859_5 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_6_16), /*             "osf10006"                      */ CODEC_ISO_8859_6 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_7_15), /*             "osf10007"                      */ CODEC_ISO_8859_7 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_8_14), /*             "osf10008"                      */ CODEC_ISO_8859_8 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_9_12), /*             "osf10009"                      */ CODEC_ISO_8859_9 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_10_12), /*            "osf1000a"                      */ CODEC_ISO_8859_10 },
	{ offsetof(struct codec_name_db_struct, db_HP_ROMAN8_4), /*               "osf10010001"                   */ CODEC_HP_ROMAN8 },
	{ offsetof(struct codec_name_db_struct, db_HP_GREEK8_2), /*               "osf10010004"                   */ CODEC_HP_GREEK8 },
	{ offsetof(struct codec_name_db_struct, db_HP_TURKISH8_3), /*             "osf10010006"                   */ CODEC_HP_TURKISH8 },
	{ offsetof(struct codec_name_db_struct, db_ASCII_12), /*                  "osf10020"                      */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_CP37_7), /*                    "osf10020025"                   */ CODEC_CP37 },
	{ offsetof(struct codec_name_db_struct, db_CP273_3), /*                   "osf10020111"                   */ CODEC_CP273 },
	{ offsetof(struct codec_name_db_struct, db_EBCDIC_CP_DK_NO_5), /*         "osf10020115"                   */ CODEC_EBCDIC_CP_DK_NO },
	{ offsetof(struct codec_name_db_struct, db_CP278_5), /*                   "osf10020116"                   */ CODEC_CP278 },
	{ offsetof(struct codec_name_db_struct, db_CP280_4), /*                   "osf10020118"                   */ CODEC_CP280 },
	{ offsetof(struct codec_name_db_struct, db_CP284_4), /*                   "osf1002011c"                   */ CODEC_CP284 },
	{ offsetof(struct codec_name_db_struct, db_CP285_4), /*                   "osf1002011d"                   */ CODEC_CP285 },
	{ offsetof(struct codec_name_db_struct, db_CP290_4), /*                   "osf10020122"                   */ CODEC_CP290 },
	{ offsetof(struct codec_name_db_struct, db_CP297_4), /*                   "osf10020129"                   */ CODEC_CP297 },
	{ offsetof(struct codec_name_db_struct, db_CP420_4), /*                   "osf100201a4"                   */ CODEC_CP420 },
	{ offsetof(struct codec_name_db_struct, db_CP424_4), /*                   "osf100201a8"                   */ CODEC_CP424 },
	{ offsetof(struct codec_name_db_struct, db_CP437_5), /*                   "osf100201b5"                   */ CODEC_CP437 },
	{ offsetof(struct codec_name_db_struct, db_CP500_7), /*                   "osf100201f4"                   */ CODEC_CP500 },
	{ offsetof(struct codec_name_db_struct, db_CP850_5), /*                   "osf10020352"                   */ CODEC_CP850 },
	{ offsetof(struct codec_name_db_struct, db_CP852_4), /*                   "osf10020354"                   */ CODEC_CP852 },
	{ offsetof(struct codec_name_db_struct, db_CP855_5), /*                   "osf10020357"                   */ CODEC_CP855 },
	{ offsetof(struct codec_name_db_struct, db_CP857_5), /*                   "osf10020359"                   */ CODEC_CP857 },
	{ offsetof(struct codec_name_db_struct, db_CP861_7), /*                   "osf1002035d"                   */ CODEC_CP861 },
	{ offsetof(struct codec_name_db_struct, db_CP862_5), /*                   "osf1002035e"                   */ CODEC_CP862 },
	{ offsetof(struct codec_name_db_struct, db_CP863_5), /*                   "osf1002035f"                   */ CODEC_CP863 },
	{ offsetof(struct codec_name_db_struct, db_CP864_4), /*                   "osf10020360"                   */ CODEC_CP864 },
	{ offsetof(struct codec_name_db_struct, db_CP868_4), /*                   "osf10020364"                   */ CODEC_CP868 },
	{ offsetof(struct codec_name_db_struct, db_CP869_6), /*                   "osf10020365"                   */ CODEC_CP869 },
	{ offsetof(struct codec_name_db_struct, db_CP870_5), /*                   "osf10020366"                   */ CODEC_CP870 },
	{ offsetof(struct codec_name_db_struct, db_CP871_4), /*                   "osf10020367"                   */ CODEC_CP871 },
	{ offsetof(struct codec_name_db_struct, db_CP875_3), /*                   "osf1002036b"                   */ CODEC_CP875 },
	{ offsetof(struct codec_name_db_struct, db_CP880_4), /*                   "osf10020370"                   */ CODEC_CP880 },
	{ offsetof(struct codec_name_db_struct, db_ASCII_18), /*                  "osf1002037b"                   */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_ASCII_22), /*                  "osf10020387"                   */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_CP904_5), /*                   "osf10020388"                   */ CODEC_CP904 },
	{ offsetof(struct codec_name_db_struct, db_CP918_5), /*                   "osf10020396"                   */ CODEC_CP918 },
	{ offsetof(struct codec_name_db_struct, db_CP1026_4), /*                  "osf10020402"                   */ CODEC_CP1026 },
	{ offsetof(struct codec_name_db_struct, db_CP1047_3), /*                  "osf10020417"                   */ CODEC_CP1047 },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_17), /*                "osf10100"                      */ CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_17), /*                "osf10100"                      */ CODEC_UTF16LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_18), /*                "osf10101"                      */ CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_18), /*                "osf10101"                      */ CODEC_UTF16LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_19), /*                "osf10102"                      */ CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_19), /*                "osf10102"                      */ CODEC_UTF16LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_18), /*                "osf10104"                      */ CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_16), /*                "osf10104"                      */ CODEC_UTF32LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_19), /*                "osf10105"                      */ CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_17), /*                "osf10105"                      */ CODEC_UTF32LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_20), /*                "osf10106"                      */ CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_18), /*                "osf10106"                      */ CODEC_UTF32LE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_UTF8_5), /*                    "osf5010001"                    */ CODEC_UTF8 },
	{ offsetof(struct codec_name_db_struct, db_PALMOS_0), /*                  "palmos"                        */ CODEC_PALMOS },
	{ offsetof(struct codec_name_db_struct, db_CP858_3), /*                   "pc-multilingual-850+euro"      */ CODEC_CP858 },
	{ offsetof(struct codec_name_db_struct, db_URI_ESCAPE_2), /*              "percent-encoding"              */ CODEC_URI_ESCAPE },
	{ offsetof(struct codec_name_db_struct, db_CP1276_3), /*                  "postscript"                    */ CODEC_CP1276 },
	{ offsetof(struct codec_name_db_struct, db_CP1276_1), /*                  "postscript-standard-encoding"  */ CODEC_CP1276 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_PT_0), /*               "pt"                            */ CODEC_ISO646_PT },
	{ offsetof(struct codec_name_db_struct, db_PT154_2), /*                   "pt154"                         */ CODEC_PT154 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_PT2_0), /*              "pt2"                           */ CODEC_ISO646_PT2 },
	{ offsetof(struct codec_name_db_struct, db_PT154_0), /*                   "ptcp154"                       */ CODEC_PT154 },
	{ offsetof(struct codec_name_db_struct, db_CP355_1), /*                   "pttc/bcd"                      */ CODEC_CP355 },
	{ offsetof(struct codec_name_db_struct, db_CP358_1), /*                   "pttc/bcd-c"                    */ CODEC_CP358 },
	{ offsetof(struct codec_name_db_struct, db_CP359_3), /*                   "pttc/bcd-d"                    */ CODEC_CP359 },
	{ offsetof(struct codec_name_db_struct, db_CP357_1), /*                   "pttc/bcd-h"                    */ CODEC_CP357 },
	{ offsetof(struct codec_name_db_struct, db_CP359_1), /*                   "pttc/bcd-m"                    */ CODEC_CP359 },
	{ offsetof(struct codec_name_db_struct, db_HP_ROMAN8_2), /*               "r8"                            */ CODEC_HP_ROMAN8 },
	{ offsetof(struct codec_name_db_struct, db_HP_ROMAN9_2), /*               "r9"                            */ CODEC_HP_ROMAN9 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_BASIC_1), /*            "ref"                           */ CODEC_ISO646_BASIC },
	{ offsetof(struct codec_name_db_struct, db_KZ_1048_3), /*                 "rk1048"                        */ CODEC_KZ_1048 },
	{ offsetof(struct codec_name_db_struct, db_HP_ROMAN8_1), /*               "roman8"                        */ CODEC_HP_ROMAN8 },
	{ offsetof(struct codec_name_db_struct, db_HP_ROMAN9_1), /*               "roman9"                        */ CODEC_HP_ROMAN9 },
	{ offsetof(struct codec_name_db_struct, db_CP1125_1), /*                  "rst-2018-91"                   */ CODEC_CP1125 },
	{ offsetof(struct codec_name_db_struct, db_CP1125_3), /*                  "ruscii"                        */ CODEC_CP1125 },
	{ offsetof(struct codec_name_db_struct, db_CP3012_1), /*                  "ruslat"                        */ CODEC_CP3012 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SE_5), /*               "se"                            */ CODEC_ISO646_SE },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SE2_3), /*              "se2"                           */ CODEC_ISO646_SE2 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SE_0), /*               "sen-850200-b"                  */ CODEC_ISO646_SE },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SE2_0), /*              "sen-850200-c"                  */ CODEC_ISO646_SE2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_146_2), /*              "serbian"                       */ CODEC_ISO_IR_146 },
	{ offsetof(struct codec_name_db_struct, db_KOI7_N2_1), /*                 "short-koi"                     */ CODEC_KOI7_N2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_16_6), /*             "sr-14111"                      */ CODEC_ISO_8859_16 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_SE_7), /*               "ss636127"                      */ CODEC_ISO646_SE },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_153_1), /*              "st-sev-358-88"                 */ CODEC_ISO_IR_153 },
	{ offsetof(struct codec_name_db_struct, db_CP1276_2), /*                  "standardencoding"              */ CODEC_CP1276 },
	{ offsetof(struct codec_name_db_struct, db_KZ_1048_2), /*                 "strk1048-2002"                 */ CODEC_KZ_1048 },
	{ offsetof(struct codec_name_db_struct, db_CP20269_1), /*                 "t.51"                          */ CODEC_CP20269 },
	{ offsetof(struct codec_name_db_struct, db_CP1036_2), /*                  "t.61"                          */ CODEC_CP1036 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_T_61_0), /*             "t.61-7bit"                     */ CODEC_ISO646_T_61 },
	{ offsetof(struct codec_name_db_struct, db_CP1036_4), /*                  "t.61-8bit"                     */ CODEC_CP1036 },
	{ offsetof(struct codec_name_db_struct, db_CP1036_3), /*                  "t.618bit"                      */ CODEC_CP1036 },
	{ offsetof(struct codec_name_db_struct, db_HP_THAI8_2), /*                "thai8"                         */ CODEC_HP_THAI8 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_11_5), /*             "tis-620"                       */ CODEC_ISO_8859_11 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_11_7), /*             "tis620"                        */ CODEC_ISO_8859_11 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_11_8), /*             "tis620-0"                      */ CODEC_ISO_8859_11 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_11_9), /*             "tis620.2529-1"                 */ CODEC_ISO_8859_11 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_11_12), /*            "tis620.2533"                   */ CODEC_ISO_8859_11 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_11_10), /*            "tis620.2533-0"                 */ CODEC_ISO_8859_11 },
	{ offsetof(struct codec_name_db_struct, db_CP1288_5), /*                  "tr8dec"                        */ CODEC_CP1288 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_9_13), /*             "ts-5881"                       */ CODEC_ISO_8859_9 },
	{ offsetof(struct codec_name_db_struct, db_HP_TURKISH8_2), /*             "turkish8"                      */ CODEC_HP_TURKISH8 },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_16), /*                "ucs-2"                         */ CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_16), /*                "ucs-2"                         */ CODEC_UTF16LE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_2), /*                 "ucs-2be"                       */ CODEC_UTF16BE },
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_2), /*                 "ucs-2le"                       */ CODEC_UTF16LE },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_14), /*                "ucs-4"                         */ CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_12), /*                "ucs-4"                         */ CODEC_UTF32LE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_2), /*                 "ucs-4be"                       */ CODEC_UTF32BE },
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_2), /*                 "ucs-4le"                       */ CODEC_UTF32LE },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_15), /*                "ucs2"                          */ CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_15), /*                "ucs2"                          */ CODEC_UTF16LE },
#endif /* ... */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_13), /*                "ucs4"                          */ CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_11), /*                "ucs4"                          */ CODEC_UTF32LE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_ISO646_GB_4), /*               "uk"                            */ CODEC_ISO646_GB },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_13), /*                "unicode"                       */ CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_13), /*                "unicode"                       */ CODEC_UTF16LE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_3), /*                 "unicodebig"                    */ CODEC_UTF16BE },
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_6), /*                 "unicodebigunmarked"            */ CODEC_UTF16BE },
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_3), /*                 "unicodelittle"                 */ CODEC_UTF16LE },
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_7), /*                 "unicodelittleunmarked"         */ CODEC_UTF16LE },
	{ offsetof(struct codec_name_db_struct, db_URI_ESCAPE_0), /*              "uri-escape"                    */ CODEC_URI_ESCAPE },
	{ offsetof(struct codec_name_db_struct, db_URI_ESCAPE_3), /*              "url-encoding"                  */ CODEC_URI_ESCAPE },
	{ offsetof(struct codec_name_db_struct, db_URI_ESCAPE_1), /*              "url-escape"                    */ CODEC_URI_ESCAPE },
	{ offsetof(struct codec_name_db_struct, db_ASCII_7), /*                   "us"                            */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_ASCII_6), /*                   "us-ascii"                      */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_US_DK_0), /*                   "us-dk"                         */ CODEC_US_DK },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_9), /*                 "utf-16"                        */ CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_9), /*                 "utf-16"                        */ CODEC_UTF16LE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_1), /*                 "utf-16be"                      */ CODEC_UTF16BE },
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_1), /*                 "utf-16le"                      */ CODEC_UTF16LE },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_8), /*                 "utf-32"                        */ CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_6), /*                 "utf-32"                        */ CODEC_UTF32LE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_1), /*                 "utf-32be"                      */ CODEC_UTF32BE },
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_1), /*                 "utf-32le"                      */ CODEC_UTF32LE },
	{ offsetof(struct codec_name_db_struct, db_UTF8_1), /*                    "utf-8"                         */ CODEC_UTF8 },
	{ offsetof(struct codec_name_db_struct, db_UTF8_BOM_1), /*                "utf-8-bom"                     */ CODEC_UTF8_BOM },
	{ offsetof(struct codec_name_db_struct, db_UTF8_BOM_3), /*                "utf-8bom"                      */ CODEC_UTF8_BOM },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_8), /*                 "utf16"                         */ CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_8), /*                 "utf16"                         */ CODEC_UTF16LE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_0), /*                 "utf16be"                       */ CODEC_UTF16BE },
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_0), /*                 "utf16le"                       */ CODEC_UTF16LE },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_7), /*                 "utf32"                         */ CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_5), /*                 "utf32"                         */ CODEC_UTF32LE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_0), /*                 "utf32be"                       */ CODEC_UTF32BE },
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_0), /*                 "utf32le"                       */ CODEC_UTF32LE },
	{ offsetof(struct codec_name_db_struct, db_UTF8_0), /*                    "utf8"                          */ CODEC_UTF8 },
	{ offsetof(struct codec_name_db_struct, db_UTF8_BOM_0), /*                "utf8-bom"                      */ CODEC_UTF8_BOM },
	{ offsetof(struct codec_name_db_struct, db_UTF8_BOM_2), /*                "utf8bom"                       */ CODEC_UTF8_BOM },
	{ offsetof(struct codec_name_db_struct, db_VENTURA_INTERNATIONAL_1), /*   "ventura-int"                   */ CODEC_VENTURA_INTERNATIONAL },
	{ offsetof(struct codec_name_db_struct, db_VENTURA_INTERNATIONAL_0), /*   "ventura-international"         */ CODEC_VENTURA_INTERNATIONAL },
	{ offsetof(struct codec_name_db_struct, db_VENTURA_US_0), /*              "ventura-us"                    */ CODEC_VENTURA_US },
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ && __SIZEOF_WCHAR_T__ == 4
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_20), /*                "wchar-t"                       */ CODEC_UTF32LE },
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ && __SIZEOF_WCHAR_T__ == 4
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_22), /*                "wchar-t"                       */ CODEC_UTF32BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ && __SIZEOF_WCHAR_T__ == 2
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_24), /*                "wchar-t"                       */ CODEC_UTF16LE },
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ && __SIZEOF_WCHAR_T__ == 2
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_24), /*                "wchar-t"                       */ CODEC_UTF16BE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_CP1100_4), /*                  "we8dec"                        */ CODEC_CP1100 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_1_11), /*             "we8iso8859p1"                  */ CODEC_ISO_8859_1 },
	{ offsetof(struct codec_name_db_struct, db_CP1270_4), /*                  "win-sami-2"                    */ CODEC_CP1270 },
	{ offsetof(struct codec_name_db_struct, db_CP1257_5), /*                  "winbaltrim"                    */ CODEC_CP1257 },
	{ offsetof(struct codec_name_db_struct, db_CP1275_6), /*                  "windows-10000"                 */ CODEC_CP1275 },
	{ offsetof(struct codec_name_db_struct, db_CP10004_1), /*                 "windows-10004"                 */ CODEC_CP10004 },
	{ offsetof(struct codec_name_db_struct, db_CP10006_1), /*                 "windows-10006"                 */ CODEC_CP10006 },
	{ offsetof(struct codec_name_db_struct, db_CP10007_1), /*                 "windows-10007"                 */ CODEC_CP10007 },
	{ offsetof(struct codec_name_db_struct, db_CP1285_4), /*                  "windows-10010"                 */ CODEC_CP1285 },
	{ offsetof(struct codec_name_db_struct, db_CP10017_1), /*                 "windows-10017"                 */ CODEC_CP10017 },
	{ offsetof(struct codec_name_db_struct, db_CP1282_4), /*                  "windows-10029"                 */ CODEC_CP1282 },
	{ offsetof(struct codec_name_db_struct, db_CP1286_4), /*                  "windows-10079"                 */ CODEC_CP1286 },
	{ offsetof(struct codec_name_db_struct, db_CP1281_4), /*                  "windows-10081"                 */ CODEC_CP1281 },
	{ offsetof(struct codec_name_db_struct, db_CP1284_4), /*                  "windows-10082"                 */ CODEC_CP1284 },
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_4), /*                 "windows-12001"                 */ CODEC_UTF32BE },
	{ offsetof(struct codec_name_db_struct, db_CP1250_2), /*                  "windows-1250"                  */ CODEC_CP1250 },
	{ offsetof(struct codec_name_db_struct, db_CP1251_2), /*                  "windows-1251"                  */ CODEC_CP1251 },
	{ offsetof(struct codec_name_db_struct, db_CP1252_2), /*                  "windows-1252"                  */ CODEC_CP1252 },
	{ offsetof(struct codec_name_db_struct, db_CP1253_2), /*                  "windows-1253"                  */ CODEC_CP1253 },
	{ offsetof(struct codec_name_db_struct, db_CP1254_2), /*                  "windows-1254"                  */ CODEC_CP1254 },
	{ offsetof(struct codec_name_db_struct, db_CP1255_2), /*                  "windows-1255"                  */ CODEC_CP1255 },
	{ offsetof(struct codec_name_db_struct, db_CP1256_2), /*                  "windows-1256"                  */ CODEC_CP1256 },
	{ offsetof(struct codec_name_db_struct, db_CP1257_2), /*                  "windows-1257"                  */ CODEC_CP1257 },
	{ offsetof(struct codec_name_db_struct, db_CP1258_2), /*                  "windows-1258"                  */ CODEC_CP1258 },
	{ offsetof(struct codec_name_db_struct, db_CP1270_1), /*                  "windows-1270"                  */ CODEC_CP1270 },
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_21), /*                "windows-13488"                 */ CODEC_UTF16BE },
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_21), /*                "windows-13488"                 */ CODEC_UTF16LE },
#endif /* ... */
	{ offsetof(struct codec_name_db_struct, db_ISO646_IRV_1983_3), /*         "windows-20105"                 */ CODEC_ISO646_IRV_1983 },
	{ offsetof(struct codec_name_db_struct, db_ISO646_DE_11), /*              "windows-20106"                 */ CODEC_ISO646_DE },
	{ offsetof(struct codec_name_db_struct, db_ASCII_14), /*                  "windows-20127"                 */ CODEC_ASCII },
	{ offsetof(struct codec_name_db_struct, db_CP1036_6), /*                  "windows-20261"                 */ CODEC_CP1036 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_1_10), /*             "windows-28591"                 */ CODEC_ISO_8859_1 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_2_10), /*             "windows-28592"                 */ CODEC_ISO_8859_2 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_3_10), /*             "windows-28593"                 */ CODEC_ISO_8859_3 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_4_10), /*             "windows-28594"                 */ CODEC_ISO_8859_4 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_5_7), /*              "windows-28595"                 */ CODEC_ISO_8859_5 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_6_11), /*             "windows-28596"                 */ CODEC_ISO_8859_6 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_7_12), /*             "windows-28597"                 */ CODEC_ISO_8859_7 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_8_9), /*              "windows-28598"                 */ CODEC_ISO_8859_8 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_9_10), /*             "windows-28599"                 */ CODEC_ISO_8859_9 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_10_11), /*            "windows-28600"                 */ CODEC_ISO_8859_10 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_11_3), /*             "windows-28601"                 */ CODEC_ISO_8859_11 },
	{ offsetof(struct codec_name_db_struct, db_CP921_12), /*                  "windows-28603"                 */ CODEC_CP921 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_14_8), /*             "windows-28604"                 */ CODEC_ISO_8859_14 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_15_9), /*             "windows-28605"                 */ CODEC_ISO_8859_15 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_16_8), /*             "windows-28606"                 */ CODEC_ISO_8859_16 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_1_13), /*             "windows-38591"                 */ CODEC_ISO_8859_1 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_6_13), /*             "windows-38596"                 */ CODEC_ISO_8859_6 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_8_11), /*             "windows-38598"                 */ CODEC_ISO_8859_8 },
	{ offsetof(struct codec_name_db_struct, db_UTF8_7), /*                    "windows-65001"                 */ CODEC_UTF8 },
	{ offsetof(struct codec_name_db_struct, db_CP874_4), /*                   "windows-874"                   */ CODEC_CP874 },
	{ offsetof(struct codec_name_db_struct, db_CP1004_1), /*                  "windows-extended"              */ CODEC_CP1004 },
	{ offsetof(struct codec_name_db_struct, db_CP1270_3), /*                  "winsami2"                      */ CODEC_CP1270 },
	{ offsetof(struct codec_name_db_struct, db_CP1270_2), /*                  "ws2"                           */ CODEC_CP1270 },
	{ offsetof(struct codec_name_db_struct, db_CP874_2), /*                   "x-ibm874"                      */ CODEC_CP874 },
	{ offsetof(struct codec_name_db_struct, db_IBM930_3), /*                  "x-ibm930"                      */ CODEC_IBM930 },
	{ offsetof(struct codec_name_db_struct, db_IBM939_3), /*                  "x-ibm939"                      */ CODEC_IBM939 },
	{ offsetof(struct codec_name_db_struct, db_ISO_8859_11_11), /*            "x-iso-8859-11"                 */ CODEC_ISO_8859_11 },
	{ offsetof(struct codec_name_db_struct, db_CP10004_2), /*                 "x-mac-arabic"                  */ CODEC_CP10004 },
	{ offsetof(struct codec_name_db_struct, db_X_MAC_ARMENIAN_0), /*          "x-mac-armenian"                */ CODEC_X_MAC_ARMENIAN },
	{ offsetof(struct codec_name_db_struct, db_X_MAC_BARENTS_CYRILLIC_0), /*  "x-mac-barents-cyrillic"        */ CODEC_X_MAC_BARENTS_CYRILLIC },
	{ offsetof(struct codec_name_db_struct, db_CP1282_5), /*                  "x-mac-ce"                      */ CODEC_CP1282 },
	{ offsetof(struct codec_name_db_struct, db_X_MAC_CELTIC_0), /*            "x-mac-celtic"                  */ CODEC_X_MAC_CELTIC },
	{ offsetof(struct codec_name_db_struct, db_CP1284_5), /*                  "x-mac-croatian"                */ CODEC_CP1284 },
	{ offsetof(struct codec_name_db_struct, db_X_MAC_CYRILLIC_0), /*          "x-mac-cyrillic"                */ CODEC_X_MAC_CYRILLIC },
	{ offsetof(struct codec_name_db_struct, db_X_MAC_DEVANAGARI_0), /*        "x-mac-devanagari"              */ CODEC_X_MAC_DEVANAGARI },
	{ offsetof(struct codec_name_db_struct, db_X_MAC_MALTESE_1), /*           "x-mac-esperanto"               */ CODEC_X_MAC_MALTESE },
	{ offsetof(struct codec_name_db_struct, db_X_MAC_FARSI_0), /*             "x-mac-farsi"                   */ CODEC_X_MAC_FARSI },
	{ offsetof(struct codec_name_db_struct, db_X_MAC_GAELIC_0), /*            "x-mac-gaelic"                  */ CODEC_X_MAC_GAELIC },
	{ offsetof(struct codec_name_db_struct, db_X_MAC_GEORGIAN_0), /*          "x-mac-georgian"                */ CODEC_X_MAC_GEORGIAN },
	{ offsetof(struct codec_name_db_struct, db_CP10006_2), /*                 "x-mac-greek"                   */ CODEC_CP10006 },
	{ offsetof(struct codec_name_db_struct, db_X_MAC_GUJARATI_0), /*          "x-mac-gujarati"                */ CODEC_X_MAC_GUJARATI },
	{ offsetof(struct codec_name_db_struct, db_X_MAC_GURMUKHI_0), /*          "x-mac-gurmukhi"                */ CODEC_X_MAC_GURMUKHI },
	{ offsetof(struct codec_name_db_struct, db_CP1286_5), /*                  "x-mac-icelandic"               */ CODEC_CP1286 },
	{ offsetof(struct codec_name_db_struct, db_X_MAC_INUIT_0), /*             "x-mac-inuit"                   */ CODEC_X_MAC_INUIT },
	{ offsetof(struct codec_name_db_struct, db_X_MAC_MALTESE_0), /*           "x-mac-maltese"                 */ CODEC_X_MAC_MALTESE },
	{ offsetof(struct codec_name_db_struct, db_X_MAC_OGHAM_0), /*             "x-mac-ogham"                   */ CODEC_X_MAC_OGHAM },
	{ offsetof(struct codec_name_db_struct, db_CP1275_7), /*                  "x-mac-roman"                   */ CODEC_CP1275 },
	{ offsetof(struct codec_name_db_struct, db_CP1285_5), /*                  "x-mac-romanian"                */ CODEC_CP1285 },
	{ offsetof(struct codec_name_db_struct, db_X_MAC_SAMI_0), /*              "x-mac-sami"                    */ CODEC_X_MAC_SAMI },
	{ offsetof(struct codec_name_db_struct, db_ADOBE_SYMBOL_ENCODING_5), /*   "x-mac-symbol"                  */ CODEC_ADOBE_SYMBOL_ENCODING },
	{ offsetof(struct codec_name_db_struct, db_X_MAC_TURKIC_CYRILLIC_0), /*   "x-mac-turkic-cyrillic"         */ CODEC_X_MAC_TURKIC_CYRILLIC },
	{ offsetof(struct codec_name_db_struct, db_CP1281_5), /*                  "x-mac-turkish"                 */ CODEC_CP1281 },
	{ offsetof(struct codec_name_db_struct, db_CP10017_2), /*                 "x-mac-ukrainian"               */ CODEC_CP10017 },
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_5), /*                 "x-unicodebig"                  */ CODEC_UTF16BE },
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_5), /*                 "x-unicodelittle"               */ CODEC_UTF16LE },
	{ offsetof(struct codec_name_db_struct, db_UTF16BE_7), /*                 "x-utf-16be"                    */ CODEC_UTF16BE },
	{ offsetof(struct codec_name_db_struct, db_UTF16LE_6), /*                 "x-utf-16le"                    */ CODEC_UTF16LE },
	{ offsetof(struct codec_name_db_struct, db_UTF32BE_6), /*                 "x-utf-32be"                    */ CODEC_UTF32BE },
	{ offsetof(struct codec_name_db_struct, db_UTF32LE_4), /*                 "x-utf-32le"                    */ CODEC_UTF32LE },
	{ offsetof(struct codec_name_db_struct, db_CP874_6), /*                   "x-windows-874"                 */ CODEC_CP874 },
	{ offsetof(struct codec_name_db_struct, db_X0201_1), /*                   "x201"                          */ CODEC_X0201 },
	{ offsetof(struct codec_name_db_struct, db_ISO_IR_13_4), /*               "x201-7"                        */ CODEC_ISO_IR_13 },
	{ offsetof(struct codec_name_db_struct, db_XML_ESCAPE_0), /*              "xml-escape"                    */ CODEC_XML_ESCAPE },
	{ offsetof(struct codec_name_db_struct, db_ISO646_YU_4), /*               "yu"                            */ CODEC_ISO646_YU },
};
/*[[[end]]]*/

/* Return a code name string for a given offset */
#define codec_name_str(offset) ((char const *)&codec_name_db + (offset))



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
	 * prefixes  are  followed  up with  a  digit character. */
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


/* Return the internal ID of the codec associated with `name'
 * Casing   is  ignored  and  codec  aliases  are  respected.
 * @return: * :                  Internal codec ID (s.a. `iconv_getcodecnames()')
 * @return: ICONV_CODEC_UNKNOWN: Unrecognized codec. */
INTERN ATTR_PURE WUNUSED NONNULL((1)) iconv_codec_t
NOTHROW_NCX(CC libiconv_codecbyname)(char const *__restrict name) {
	size_t lo, hi;
	char normal_name[CODE_NAME_MAXLEN + 1];
again:
	lo = 0;
	hi = COMPILER_LENOF(codec_db);
	while (lo < hi) {
		size_t i;
		int cmp;
		i = (lo + hi) / 2;
		cmp = strcasecmp(name, codec_name_str(codec_db[i].cdbe_name));
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

/* Return a "\0\0"-terminated list of names for the codec `id'. The list is
 * sorted such that the most important name comes first and all other names
 * can be enumerated by use of `strend(p)+1'.
 *
 * When `id' is invalid, return `NULL'. Note that all valid codecs have at
 * least 1 valid name. As such, supported codecs as well as their names can
 * be enumerated as:
 * >> iconv_codec_t id;
 * >> for (id = ICONV_CODEC_FIRST;;) {
 * >>     char const *name;
 * >>     if ((name = iconv_getcodecnames(id)) == NULL)
 * >>         break;
 * >>     for (;;) {
 * >>         printf("%s", name);
 * >>         name = strend(name) + 1;
 * >>         if (!*name)
 * >>             break;
 * >>         putc('\t');
 * >>     }
 * >>     putc('\n');
 * >> } */
INTERN ATTR_CONST WUNUSED char const *
NOTHROW_NCX(CC libiconv_getcodecnames)(iconv_codec_t id) {
	size_t i;
	/* NOTE: If it ever becomes an issue, this function could be sped up by
	 *       pre-computing an mapping:
	 * CODEC_ID->OFFSET_OF_START_OF_STRING_LIST
	 * If done, this function could be implemented on O(1) time, though that
	 * would also add a bunch to the file size of the library, so this isn't
	 * being done (for now). */
	for (i = 0; i < COMPILER_LENOF(codec_db); ++i) {
		char const *result;
		if (codec_db[i].cdbe_codec != id)
			continue;
		/* Find the start of the string list. */
		result = codec_name_str(codec_db[i].cdbe_name);
		while (result[-2] != '\0')
			result = (char const *)rawmemrchr(result - 1, '\0');
		return result;
	}
	return NULL;
}


/* Same as `libiconv_codecbyname()', but the name has a fixed length. */
INTERN ATTR_NOINLINE ATTR_PURE WUNUSED NONNULL((1)) iconv_codec_t
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


/* Same as `iconv_codecbyname()', but  also parse possible flag-relation  options.
 * The given `*pflags' argument must already  be populated with valid data  before
 * this function is called, and should usually point to `icd_flags' or `ice_flags' */
INTERN WUNUSED NONNULL((1)) iconv_codec_t
NOTHROW_NCX(CC libiconv_codec_and_flags_byname)(char const *__restrict name,
                                                /*[in|out]*/ uintptr_half_t *__restrict pflags) {
	iconv_codec_t result;
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
NOTHROW_NCX(CC libiconv_same_codec_name)(char const *__restrict a,
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




DEFINE_PUBLIC_ALIAS(iconv_codecbyname, libiconv_codecbyname);
DEFINE_PUBLIC_ALIAS(iconv_getcodecnames, libiconv_getcodecnames);
DEFINE_PUBLIC_ALIAS(iconv_codec_and_flags_byname, libiconv_codec_and_flags_byname);
DEFINE_PUBLIC_ALIAS(iconv_same_codec_name, libiconv_same_codec_name);


DECL_END

#endif /* !GUARD_LIBICONV_CODECS_C */
