
### Source file inclusion in kernel-/user-space

- `./auto`
	- `./auto/*.c`:
		- Kernel:yes
		- Fully automatically generated source files and headers
- `./hybrid`
	- `./hybrid/*.c`:
		- Kernel:yes
		- Hand-written libc-APIs that can't (easily) be generated automatically, but should appear in both the kernel- and userspace
	- `./hybrid/arch/$TARGET/*.c`, `./hybrid/arch/$TARGET/*.S`:
		- Kernel:yes
		- Arch-specific functions and hand-written, optimized assembly (for things such as `memcpy`)
	- `./hybrid/arch/$TARGET/config.h`
		- Included by the main `./api.h` header to define arch-specific features (mainly used for `#define LIBC_ARCH_HAVE_* 1` to specify which normally auto-generated functions are actually implemented via hand-written assembly; s.a. `magic/*.c`)
- `./libc`
	- `./libc/*.c`, `./libc/arch/$TARGET/*.c`, `./libc/arch/$TARGET/*.S`:
		- Kernel:no
		- Libc internal meta-APIs and functions not controlled by magic generators.
		- Contains things such as library intializers, system call exports and bindings, system tests, global variable interfaces, etc...
- `./magic`
	- `./magic/*.c`:
		- Kernel:no (meta definition files: parsed to generated other files, but not actually compiled in a traditional sense)
		- Input/Definition files for magic headers
- `./user`
	- `./user/*.c`:
		- Kernel:no
		- (partially) auto-generated source files for magic-generated functions that can't be implemented automatically. (i.e. are marked as `[[userimpl]]` or don't have a body in the associated `./magic/*.c` file)





