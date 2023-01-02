/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_IDT_FOREACH_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_IDT_FOREACH_H 1

/* Invoke `callback()' with `00, 01, 02, ..., 0a, 0b, ..., ff' */
/*[[[deemon
print "#define IDT_X86_FOREACH(callback)"
      "                                 "
      "                                 "
      "         \\";
local tohex = "0123456789abcdef";
for (local x: [:16]) {
	print "\t",;
	for (local y: [:16]) {
		print "callback(",;
		print tohex[x],;
		print tohex[y],;
		print ") ",;
		if (y == 7)
			print "\\\n\t",;
	}
	if (x != 15)
		print "\\",;
	print;
}
]]]*/
#define IDT_X86_FOREACH(callback)                                                                           \
	callback(00) callback(01) callback(02) callback(03) callback(04) callback(05) callback(06) callback(07) \
	callback(08) callback(09) callback(0a) callback(0b) callback(0c) callback(0d) callback(0e) callback(0f) \
	callback(10) callback(11) callback(12) callback(13) callback(14) callback(15) callback(16) callback(17) \
	callback(18) callback(19) callback(1a) callback(1b) callback(1c) callback(1d) callback(1e) callback(1f) \
	callback(20) callback(21) callback(22) callback(23) callback(24) callback(25) callback(26) callback(27) \
	callback(28) callback(29) callback(2a) callback(2b) callback(2c) callback(2d) callback(2e) callback(2f) \
	callback(30) callback(31) callback(32) callback(33) callback(34) callback(35) callback(36) callback(37) \
	callback(38) callback(39) callback(3a) callback(3b) callback(3c) callback(3d) callback(3e) callback(3f) \
	callback(40) callback(41) callback(42) callback(43) callback(44) callback(45) callback(46) callback(47) \
	callback(48) callback(49) callback(4a) callback(4b) callback(4c) callback(4d) callback(4e) callback(4f) \
	callback(50) callback(51) callback(52) callback(53) callback(54) callback(55) callback(56) callback(57) \
	callback(58) callback(59) callback(5a) callback(5b) callback(5c) callback(5d) callback(5e) callback(5f) \
	callback(60) callback(61) callback(62) callback(63) callback(64) callback(65) callback(66) callback(67) \
	callback(68) callback(69) callback(6a) callback(6b) callback(6c) callback(6d) callback(6e) callback(6f) \
	callback(70) callback(71) callback(72) callback(73) callback(74) callback(75) callback(76) callback(77) \
	callback(78) callback(79) callback(7a) callback(7b) callback(7c) callback(7d) callback(7e) callback(7f) \
	callback(80) callback(81) callback(82) callback(83) callback(84) callback(85) callback(86) callback(87) \
	callback(88) callback(89) callback(8a) callback(8b) callback(8c) callback(8d) callback(8e) callback(8f) \
	callback(90) callback(91) callback(92) callback(93) callback(94) callback(95) callback(96) callback(97) \
	callback(98) callback(99) callback(9a) callback(9b) callback(9c) callback(9d) callback(9e) callback(9f) \
	callback(a0) callback(a1) callback(a2) callback(a3) callback(a4) callback(a5) callback(a6) callback(a7) \
	callback(a8) callback(a9) callback(aa) callback(ab) callback(ac) callback(ad) callback(ae) callback(af) \
	callback(b0) callback(b1) callback(b2) callback(b3) callback(b4) callback(b5) callback(b6) callback(b7) \
	callback(b8) callback(b9) callback(ba) callback(bb) callback(bc) callback(bd) callback(be) callback(bf) \
	callback(c0) callback(c1) callback(c2) callback(c3) callback(c4) callback(c5) callback(c6) callback(c7) \
	callback(c8) callback(c9) callback(ca) callback(cb) callback(cc) callback(cd) callback(ce) callback(cf) \
	callback(d0) callback(d1) callback(d2) callback(d3) callback(d4) callback(d5) callback(d6) callback(d7) \
	callback(d8) callback(d9) callback(da) callback(db) callback(dc) callback(dd) callback(de) callback(df) \
	callback(e0) callback(e1) callback(e2) callback(e3) callback(e4) callback(e5) callback(e6) callback(e7) \
	callback(e8) callback(e9) callback(ea) callback(eb) callback(ec) callback(ed) callback(ee) callback(ef) \
	callback(f0) callback(f1) callback(f2) callback(f3) callback(f4) callback(f5) callback(f6) callback(f7) \
	callback(f8) callback(f9) callback(fa) callback(fb) callback(fc) callback(fd) callback(fe) callback(ff)
/*[[[end]]]*/

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_IDT_FOREACH_H */
