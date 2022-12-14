
### Sub-folders

- `./include`
	- The primary KOS system header folder
- `./misc`
	- Build tools and scripts needed for compiling/maintaining KOS
- `./src`
	- Root folder for system library- and kernel sources


### Files

- `./.clang-format`
	- Format specifications used by `clang-format` to auto-format source code to comply with KOS specifications (but note the corner-cases documented at the top of this file)
- `./.clang-tidy`
	- Configuration used when using `clang-tidy` to perform static analysis on KOS source files
- `./.sources`
	- Used by `/magic.dee`
- `./cpp.hint`
	- Needed by Visual Studio's declaration parser in order to understand attribute macros used in headers

