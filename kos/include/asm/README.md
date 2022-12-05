
### Public `<asm/foo.h>` headers

Normally, `<asm/...>` headers are all internal and not meant to be directly included by programs. However, a small hand full of headers fall out of this norm and are actually intended for direct inclusion. To prevent any confusion, the following are all of the official *public* asm-headers:

- `<asm/asmword.h>`
	- `.macro .word8`
	- `.macro .word16`
	- `.macro .word32`
	- `.macro .word64`
	- `.macro .wordptr`
	- `.macro .wordrel` (`#ifdef __ARCH_HAVE_wordrel')
	- `.macro .wordoff` (`#ifdef __ARCH_HAVE_wordoff')
- `<asm/cacheline.h>`
	- `#define __ARCH_CACHELINESIZE <Integer>`
- `<asm/defsym.h>`
	- `#define DEFINE_PRIVATE_SYMBOL(name, value, size)      __asm__(#name "..." #value "..." #size)
	- `#define DEFINE_PUBLIC_SYMBOL(name, value, size)       __asm__(#name "..." #value "..." #size)
	- `#define DEFINE_INTERN_SYMBOL(name, value, size)       __asm__(#name "..." #value "..." #size)
	- `#define DEFINE_PRIVATE_WEAK_SYMBOL(name, value, size) __asm__(#name "..." #value "..." #size)
	- `#define DEFINE_PUBLIC_WEAK_SYMBOL(name, value, size)  __asm__(#name "..." #value "..." #size)
	- `#define DEFINE_INTERN_WEAK_SYMBOL(name, value, size)  __asm__(#name "..." #value "..." #size)
	- Helper macros to define linker symbols from C expressions.
- `<asm/intrin.h>`
	- Arch-specific intrinsic functions
- `<asm/intrin-arith.h>`
	- Arch-specific intrinsic, arithmetic functions
- `<asm/isa.h>`
	- `#define ISA_DEFAULT ...`
	- `typedef ... isa_t;`
- `<asm/farptr.h>`
	- `T &loadfarptr(T &x);`
	- Return a pointer to a far-off symbol, regardless of the used memory model
- `<asm/gas.h>`
	- `#define __GAS_HAVE_*`
	- Feature test macros to check for custom GAS (GNU AS) extensions
- `<asm/page.h>` (not kos-specific, but rather an old (now-a-days removed) linux header)
	- `#define PAGE_MASK  <Integer>`
	- `#define PAGE_SIZE  <Integer>`
	- `#define PAGE_SHIFT <Integer>`
- `<asm/prctl.h>` (not kos-specific)
- `<asm/unistd.h>` (not kos-specific)

Some more headers also exist, but those are arch-specific (`<asm/cfi.h>`, `<asm/cpu-*.h>`, `<asm/intrin-*.h>`, `<asm/registers.h>`, ...)

Any other header may be renamed/deleted/added without warning, and as such are not part of the stable API. The same also goes for files which may be found in sub-folders. In any case, files not mentioned usually only contain escaped macros that get aliased to their unescaped counterparts by other, more appropriate headers. As such those other headers should always be included instead.
