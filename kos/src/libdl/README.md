
### Base ELF specs
- [elf-64-gen.pdf](https://uclibc.org/docs/elf-64-gen.pdf)
- [psABI-i386.pdf](https://uclibc.org/docs/psABI-i386.pdf)
- [psABI-x86_64.pdf](https://uclibc.org/docs/psABI-x86_64.pdf)
- [amd64-elf-abi.pdf](https://people.freebsd.org/~obrien/amd64-elf-abi.pdf)

### Changes/Extensions to ELF specs (all architectures)
- When execution is passed to an application's `main()` function, `libdl.so` does not make any provisions for a pre-initialized auxiliary information vector. For binary compatibility, an empty Aux-vector may be passed, but aux information in general is instead calculated/initialized on-demand, and must be accessed through use of `libc`'s `getauxval(3)` function, as found in `<sys/auxv.h>` (this header and its function `getauxval(3)` also exist in Glibc and may therefor be considered portable)
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
				- ... `RTLD_NOW` is passed to `dlopen(3D)` (as opposed to `RTLD_LAZY`)
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
	- The times at which configuration variables are parsed are chosen at the discretion of `libdl` itself and may not be relied upon (they may be parsed during initial program initialization, only upon first being used, or every time they are used)
		- As such, changes made to `__peb.pp_envp` and/or `__peb.pp_envp[argi]` and/or `__peb.pp_envp[argi][chari]` may or may not affect later calls made to any of the RTLD functions exposed through `<dlfcn.h>` (with or without `defined(_KOS_SOURCE)`)
- A new symbol type `STT_KOS_IDATA` has been added that allows for data-symbols to be exported from shared libraries, whilst providing a custom callback to initialize said data. This callback will only be invoked if the symbol is actually being used (i.e. as part of a dynamic relocation, or when directly addressed by a call to `dlsym(3)`).
	- In this regard, this new symbol type behaves the same as `STT_GNU_IFUNC`, however unlike that extension, this one can only be used for data symbols (whereas `STT_GNU_IFUNC` can only be used for function symbols), and can only be used to export data-symbols from shared libraries (or rather: a `.dynsym`-symbol-table to be exact). As such, `STT_KOS_IDATA` cannot be used to declare data objects of `INTERN` or `PRIVATE` visibility.
	- The intended use of this symbol type is to enable (seemingly) pre-initialized data-symbols to be exported from libraries without any additinoal relocations, such as for example:  

	  ```c
	  extern pid_t procpid;
	  ```

	  Note that no such symbol exists in libc, but it could easily be added as:  

	  ```c
	  #include <hybrid/compiler.h>
	  #include <kos/exec/idata.h>
	  #include <pthread.h>
	  #include <unistd.h>
	  
	  DECL_BEGIN
	  
	  PRIVATE pid_t intern_procpid = 0;
	  PRIVATE void init_procpid(void) {
	      intern_procpid = getpid();
	  }

	  DEFINE_PUBLIC_IDATA(procpid, get_procpid_addr, __SIZEOF_PID_T__);
	  PRIVATE ATTR_USED pid_t *get_procpid_addr(void) {
	      static pthread_once_t didinit = PTHREAD_ONCE_INIT;
	      pthread_once(&didinit, &init_procpid);
	      return &intern_procpid;
	  }
	  
	  DECL_END
	  ```

	- Currently, `STT_KOS_IDATA` is used by KOS's `libc.so` to export `sys_errlist` without the need of additional relocations, by simply having the `STT_KOS_IDATA`-callback fill in the array elements, such that no overhead exists for initializing the vector for programs that do not actually make use of the symbol (by now, it is also used to initialize various other symbols, but `sys_errlist` was the first).
	- Behavior:
		- No guaranty is made that a callback will only be invoked once:
			- Subsequent calls to `dlsym(3)` may each re-invoke the callback once again (the same also goes for later-loaded modules with relocations to the same symbol, or even a single module with more than 1 relocation addressing the same symbol)
		- The callback may be invoked simultaniously from multiple threads
		- The size-field of the associated symbol cannot be dynamically calculated, and remains fixed at the value defined by the `st_size` field. This decision is intentional and required because symbol sizes must already be known for the puprpose of COPY-relocations when a program is linked, and changing the size of a data-symbol once linking was already done would mean that COPY-relocations using the old size would also break.


### Changes to ELF specs (i386/x86_64)
- Though not required, the KOS RLTD link driver (`libdl.so`) accepts the following relocation types in shared libraries and application binaries alike
	- `R_386_8`, `R_X86_64_8` (unsigned 8-bit integer)
	- `R_386_PC8`, `R_X86_64_PC8` (signed, relocation-relative 8-bit integer)
	- `R_386_16`, `R_X86_64_16` (unsigned 16-bit integer)
	- `R_386_PC16`, `R_X86_64_PC16` (signed, relocation-relative 16-bit integer)
	- Whether or not the RLTD link driver considers it a fatal error for these relocations to over- or under-flow following zero-/sign-extension is undefined.
- The value written by relocations `R_386_TLS_DTPMOD32` and `R_X86_64_DTPMOD64` is equal to the value stored in `GOT[1]` (as used by lazy relocation). Additionally, such a value may be used as a `handle`-value normally returned by `dlopen(3D)`, and accepted by a number of functions such as `dlsym(3)` or `dlmodulename(3)` (a KOS-specific `<dlfcn.h>` extension)
- i386 only:
	- ...
- x86_64 only:
	- No code apart of the KOS RLTD link driver relies on the presence of the *red zone* (unlike other libraries such as `libc.so`), and can thus be used by code compiled with and without *red zone* support
