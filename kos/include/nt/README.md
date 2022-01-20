## Sources of NT function prototypes, macros, etc...

All information found in headers located in this folder has been retrieved from the `mingw-w64 runtime package`. The following is a copy of the license statement found at the top of these files:

```c
/**
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */
```

I'm sadly unable to find this `DISCLAIMER` file (these headers came with my installation of cygwin and are found in `cygpath  -w /usr/include/w32api`), but that shouldn't really be a problem. Because files have **NOT** been blindly copied, but prototypes and dependencies of individual functions have been taken on a per-function basis, such that functions declared in headers found in this (`/kos/include/nt/`) folder only include those which are exported by-name from the KOS NT emulation library `libkernel32.so` (whose source files can be found in `/kos/src/libkernel32/`).

In turn, this folder does not (and will not) represent the full set of NT system headers. So if you're looking for them, keep searching elsewhere.
