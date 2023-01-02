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

/*[[[deemon
local n = 16;
print "#define __CXX_VARARGS_TEMPLATE_ARGS(class,name) \\";
print "\t",;
for (local i: [:n]) {
	print "class name##_",;
	print i,;
	if (i != n-1)
		print ",",;
	print " ",;
	if ((i % 4) == 3) {
		print "\\";
		if (i != n-1)
			print "\t",;
	}
}
print "/" "**" "/";

print "#define __CXX_VARARGS_TEMPLATE_ARGS_DEF(class,name,defl) \\";
print "\t",;
for (local i: [:n]) {
	print "class name##_",;
	print i,;
	print " = defl",;
	if (i != n-1)
		print ",",;
	print " ",;
	if ((i % 4) == 3) {
		print "\\";
		if (i != n-1)
			print "\t",;
	}
}
print "/" "**" "/";

print "#define __CXX_VARARGS_TYPENAME_ARGS(name) \\";
print "\t",;
for (local i: [:n]) {
	print "name##_",;
	print i,;
	if (i != n-1)
		print ",",;
	print " ",;
	if ((i % 4) == 3) {
		print "\\";
		if (i != n-1)
			print "\t",;
	}
}
print "/" "**" "/";


]]]*/
#define __CXX_VARARGS_TEMPLATE_ARGS(class,name) \
	class name##_0, class name##_1, class name##_2, class name##_3, \
	class name##_4, class name##_5, class name##_6, class name##_7, \
	class name##_8, class name##_9, class name##_10, class name##_11, \
	class name##_12, class name##_13, class name##_14, class name##_15 \
/**/
#define __CXX_VARARGS_TEMPLATE_ARGS_DEF(class,name,defl) \
	class name##_0 = defl, class name##_1 = defl, class name##_2 = defl, class name##_3 = defl, \
	class name##_4 = defl, class name##_5 = defl, class name##_6 = defl, class name##_7 = defl, \
	class name##_8 = defl, class name##_9 = defl, class name##_10 = defl, class name##_11 = defl, \
	class name##_12 = defl, class name##_13 = defl, class name##_14 = defl, class name##_15 = defl \
/**/
#define __CXX_VARARGS_TYPENAME_ARGS(name) \
	name##_0, name##_1, name##_2, name##_3, \
	name##_4, name##_5, name##_6, name##_7, \
	name##_8, name##_9, name##_10, name##_11, \
	name##_12, name##_13, name##_14, name##_15 \
/**/
//[[[end]]]
