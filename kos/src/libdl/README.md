
### Base ELF specs
- [elf-64-gen.pdf](https://uclibc.org/docs/elf-64-gen.pdf)
- [psABI-i386.pdf](https://uclibc.org/docs/psABI-i386.pdf)
- [psABI-x86_64.pdf](https://uclibc.org/docs/psABI-x86_64.pdf)
- [amd64-elf-abi.pdf](https://people.freebsd.org/~obrien/amd64-elf-abi.pdf)

### Changes to ELF specs (all architectures)
- When execution is passed to an application's `main()` function, `libdl.so` does not make any provisions for a pre-initialized auxiliary information vector. For binary compatibility, an empty Aux-vector may be passed, but aux information in general is instead calculated/initialized on-demand, and must be accessed through use of `libc`'s `getauxval(3)` function, as found in `<sys/auxv.h>` (this header and its function `getauxval(3)` also exist in glibc and may therefor be considered portable)
	- Similarly, an application linked without need for dynamic linking also will not have an auxiliary vector made available by the kernel
- Runtime configuration options
	- Supported LD environment variables
		- `LD_LIBRARY_PATH`
			- `:`-seperated list of library search paths (defaults to `/usr/lib:/lib` (or `/usr/lib64:/lib64` on x86_64))
		- `LD_BIND_NOW`
			- Disable support for lazy relocations
			- Same as...
				- ... `DT_BIND_NOW` appears in the `.dynamic` section of a module
				- ... `DF_BIND_NOW` is set in `DT_FLAGS` in `.dynamic`
				- ... `RTLD_NOW` is passed to `dlopen(3)` (as opposed to `RTLD_LAZY`)
	- Unsupported LD environment variables (with no intention of support being added)
		- `LD_SHOW_AUXV`
		- `LD_TRACE_LOADED_OBJECTS`
		- `LD_AOUT_LIBRARY_PATH` / `LD_ELF_LIBRARY_PATH`
		- `LD_AOUT_PRELOAD` / `LD_ELF_PRELOAD`
	- Other environment variables may become supported/unsupported in the future at my discretion
- While the standards specify that RTLD's use of environment variables for configuration should not be vulnerable to modifications made, this does not *fully* apply under KOS.
	- RTLD will not pre-scan environment variables for any possible configuration option it *may* make use of.
	- Changes made to `environ` by `libc` functions such as `setenv(3)` *may* or *may* *not* have any affect.
		- Since this is the least standard-complying fact, this may be changed in the future if it is found to cause problems that cannot be worked around. Such a change would affect environ-modifying functions from `libc` to never allow the modifying of pointers/strings from `__initenv`, or at the very least, never do so for variables with names matching `LD_*`
	- RTLD will always make use of the initial process environment (as available through `__peb` (from `<kos/exec/peb.h>`) and aliased by `__initenv` (from `<stdlib.h>` with `defined(_DOS_SOURCE)`))
	- The times at which configuration variables are passed are chosen at the discretion of `libdl` itself and may not be relied upon (they may be parsed during initial program initialization, only upon first being used, or every time they are used)
		- As such, changes made to `__peb.pp_envp` and/or `__peb.pp_envp[argi]` and/or `__peb.pp_envp[argi][chari]` may or may not affect later calls made to any of the RTLD functions exposed through `<dlfcn.h>` (with or without `defined(_KOS_SOURCE)`)

### Changes to ELF specs (i386/x86_64)
- Though not required, the KOS RLTD link driver (`libdl.so`) accepts the following relocation types in shared libraries and application binaries alike
	- `R_386_8`, `R_X86_64_8` (signed 8-bit integer)
	- `R_386_PC8`, `R_X86_64_PC8` (signed, relocation-relative 8-bit integer)
	- `R_386_16`, `R_X86_64_16` (unsigned 16-bit integer)
	- `R_386_PC16`, `R_X86_64_PC16` (signed, relocation-relative 16-bit integer)
	- Whether or not the RLTD link driver considers it a fatal error for these relocations to over- or under-flow following zero-/sign-extension is undefined.
- The value written by relocations `R_386_TLS_DTPMOD32` and `R_X86_64_DTPMOD64` is equal to the value stored in `GOT[1]` (as used by lazy relocation). Additionally, such a value may be used as a `handle`-value normally returned by `dlopen(3)`, and accepted by a number of functions such as `dlsym(3)` or `dlmodulename(3)` (a KOS-specific `<dlfcn.h>` extension)
- i386 only:
	- ...
- x86_64 only:
	- No code apart of the KOS RLTD link driver relies on the presence of the *red zone* (unlike other libraries such as `libc.so`), and can thus be used by code compiled with and without *red zone* support
