
## Custom KOS system configurations

Custom KOS system configurations consist of 2 parts:

- Macro overrides
- An optional magic configuration script



### Macro overrides

Since the header is included as-is by anything that depends on system configurations, you can simply define macros in order to re-configure system features. For a list of macros intended to-be used for this purpose, see `/kos/misc/config/options-db.txt`.

A couple of special macros can/must be defined:

- `#define CONFIG_NAME "{NAME_OF_CONFIG}"`
	- This macro must always be defined to a string matching the name of the containing file (with the trailing `.h` removed)
	- Consumers of this macro expect it to represent the value passed to magic via its `--config={NAME_OF_CONFIG}` option
- `#define CONFIG_PRETTY_NAME "Pretty description of configuration"`
	- An optional, pretty description of the configuration (meant to be human-readable).
	- If defined, this description is used to name the configuration within IDEs.
		- e.g. This is the name that is used to identify the configuration in Visual Studio or VSCode
	- If omitted, `CONFIG_NAME` is instead used for this purpose.




### Magic configuration script

The magic configuration script looks like this:

```c
/*[[[magic
options["GCC.options"] = ["-O2", "-fstack-protector-strong"];
]]]*/
```

It is executed as deemon code whenever `magic.dee` is invoked. It is called in a context of a global variable `options` that represents a dict of additional `libmagic` compile options which will later be overlayed on-top of previously defined options originating from `.sources` files. Note that the overlay created here can be overwritten yet again through use of per-sourcefile `/*[[[magic ...]]]*/` scripts (e.g. `/kos/src/libdebuginfo/addr2line.c`).

As such, the full priority-order of compiler option sources is:

1. Definitions from `.sources` files
2. Overrides from `/*[[[magic ...]]]*/` scripts of custom configurations
3. Overrides from `/*[[[magic ...]]]*/` scripts of individual source files



### Notes

Except for the cases of the 4 builtin configurations, `magic.dee` will always inject a macro `'-DCONFIG_HEADER="configurations/{NAME_OF_CONFIG}.h"'`. This is needed so that the inclusion of `#include <kos/config/config.h>` is able to find your custom configuration header.

The macro is injected as would be done by a magic script:

```c
/*[[[magic
local macros = options.setdefault("COMPILE.macros", import("deemon").Dict());
macros["CONFIG_HEADER"] = f'"configurations/{NAME_OF_CONFIG}.h"';
]]]*/
```
