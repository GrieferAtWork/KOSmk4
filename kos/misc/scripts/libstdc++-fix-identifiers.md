
### Creatign libstdc++ system header patches (for KOS) from scratch

- Replace `15.2.0` with your version number below
- Install vanilla libstdc++ headers (via `make_toolchain.sh`) to `/kos/include/i386-kos/c++/15.2.0`:
	- `bash kos/misc/make_toolchain.sh i386-kos`
	- `bash kos/misc/make_toolchain.sh x86_64-kos`
- ```sh
  cd     "kos/include/i386-kos/c++"
  mv     "./15.2.0/i686-kos" "./backup-15.2.0-i686-kos"
  mv     "./15.2.0/x86_64-kos" "./backup-15.2.0-x86_64-kos"
  cp     -R "./15.2.0" "./15.2.0-orig"
  deemon "../../../misc/scripts/libstdc++-fix-identifiers.dee" "15.2.0"
  diff   -Naur "15.2.0-orig" "15.2.0" > "../../../misc/patches/libstdc++-15.2.0.patch"
  rm     -rf "./15.2.0-orig"
  mv     "./backup-15.2.0-i686-kos" "./15.2.0/i686-kos"
  mv     "./backup-15.2.0-x86_64-kos" "./15.2.0/x86_64-kos"
  cd     "./15.2.0"
  cp     -R "./i686-kos" "./i686-kos-orig"
  deemon "../../../../misc/scripts/libstdc++-fix-identifiers.dee" "i686-kos"
  diff   -Naur "i686-kos-orig" "i686-kos" > "../../../../misc/patches/libstdc++-15.2.0-i386-kos.patch"
  rm     -rf "./i686-kos-orig"
  cp     -R "./x86_64-kos" "./x86_64-kos-orig"
  deemon "../../../../misc/scripts/libstdc++-fix-identifiers.dee" "x86_64-kos"
  diff   -Naur "x86_64-kos-orig" "x86_64-kos" > "../../../../misc/patches/libstdc++-15.2.0-x86_64-kos.patch"
  rm     -rf "./x86_64-kos-orig"
  >      "./.libstdc++.kos_patched"
  >      "./i686-kos/.libstdc++.kos_patched"
  >      "./x86_64-kos/.libstdc++.kos_patched"
  ```
- At this point, your headers should be patched properly, and you should also have been able to generate some new patches that will be picked up by `make_toolchain.sh`
- Once you've generate the patches, go through by hand and delete escaped ctype macros escapes where a macro would be allowed.

### TLDR

The `libstdc++-fix-identifiers.dee` script takes a directory which it will scan for files and double-escape SAL macro names used as identifiers, as well as replace stuff like `std::isalnum()` with `(std::isalnum)()` (so code works even if our `<ctype.h>` does `#define isalnum(ch) ...`).

