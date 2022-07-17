
### Files in this folder

- `./configs.dee`
	- API for enumeration & loading of defined system configurations
	- By default, 4 configurations are defined (`OD`, `OnD`, `nOD` and `nOnD`)
- `./files.dee`
	- Primarily meant to be executed as a stand-alone program
	- Invoked during `make_toolchain.sh`
	- This program defines a function `generateAllProjectFiles()` that can be invoked in order to generate:
		- The `CppProperties.json` files needed by Visual Studio's `Open Folder` function in order to understand available KOS configurations and targets.
		- The `/kos/.vscode/c_cpp_properties.json`, which serves the same job, but does so for VS-Code
- `./options.dee`
	- List available config options from the database (`./options-db.txt`) and query associated metadata.
	- This module doesn't define functionality used to add/remove entries from the database (those are defined by `./options-db.dee`)
	- Functions from this module can be used in order to list available options (including associated documentation (if any)), as well as their typing, default value, and declaring source file.
- `./options-db.dee`
	- This module offers write-access to the options database (`./options-db.txt`)
	- It is used by `/kos/misc/libgen/autom8/config.dee` (the driver for `/*[[[config ...]]]*/` annotations) in order to keep the options database up-to-date whenever files are post-processed via autom8 (which is also done forcibly whenever you try to commit something)
	- Accessing the database for the purpose of queries should be done via `./options.dee`
- `./options-db.txt`
	- The options database itself. This file lists other source files which include `/*[[[config ...]]]*/` annotations, as well as the actual configurations defined by these files.
	- This database is used by `./options.dee` and `./options-db.dee`
- `./utils.dee`
	- Misc. utilities used by all of the other programs in this folder.

