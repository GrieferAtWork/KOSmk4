# Copyright (c) 2019-2022 Griefer@Work
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgement (see the following) in the product
#    documentation is required:
#    Portions Copyright (c) 2019-2022 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

SRCPATH="$KOS_ROOT/binutils/src/testexe"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/testexe"
cmd mkdir -p "$SRCPATH"
cmd mkdir -p "$OPTPATH"
cmd cat > "$SRCPATH/main.c" <<EOF
#include <stdio.h>

int main(int argc, char *argv[]) {
	printf("Hello World!\n");
	printf("argc = %d\n", argc);
	for (int i = 0; i < argc; ++i) {
		printf("argv[%d] = %p:%q\n", i, argv[i], argv[i]);
	}
	return 0;
}
EOF

# NOTE: This only works if you're using cygwin!!!
if /bin/i686-w64-mingw32-gcc -m32 -o "$OPTPATH/pe-wingw32.exe" "$SRCPATH/main.c"; then
	install_file /bin/pe-wingw32.exe "$OPTPATH/pe-wingw32.exe"
fi

# NOTE: This only works if you've got tcc (32-bit) installed
if tcc -o "$(cygpath -w "$OPTPATH/pe-tcc32.exe")" "$(cygpath -w "$SRCPATH/main.c")"; then
	install_file /bin/pe-tcc32.exe "$OPTPATH/pe-tcc32.exe"
fi

if [ "$TARGET_CPUNAME" == "x86_64" ]; then
	if tcc64 -o "$(cygpath -w "$OPTPATH/pe-tcc64.exe")" "$(cygpath -w "$SRCPATH/main.c")"; then
		install_file /bin/pe-tcc64.exe "$OPTPATH/pe-tcc64.exe"
	fi
	if /bin/x86_64-w64-mingw32-gcc -o "$OPTPATH/pe-wingw64.exe" "$SRCPATH/main.c"; then
		install_file /bin/pe-wingw64.exe "$OPTPATH/pe-wingw64.exe"
	fi
fi
