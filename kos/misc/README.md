
### Sub-folders

- `./config`
	- KOS System configurations API and database of available configuration options
- `./doc`
	- Misc system documentations
- `./gallery`
	- Images showing off KOS while it is running
- `./gdbridge`
	- A bridging program to resolve conflicts between Visual Studio and GDB
- `./git-hooks`
	- Folder registered with `/.git` to contain hooks invoked when performing special git operations. Primarily used to automatically prettify and normalize files during commit.
- `./libgen`
	- Collection of utility APIs used for the purpose of automatically generating code
- `./libmagic`
	- The backbone of the compile-driver used by `/magic.dee`
- `./magicemulator`
	- Wrappers/helper scripts for launching KOS in various emulators
- `./magicgenerator`
	- Programs for magically generating system headers and system call tables
- `./patches`
	- A collection of patches for getting 3rd party software to run under KOS
- `./scripts`
	- Misc collection of useful/helpful scripts (mostly taking the form of deemon scripts)
- `./targets`
	- Deemon module files representing target architectures supported by KOS.
	- The names of the files in this folder are what's passed in `deemon magic.dee --target=...`
- `./tool-configs`
	- Configuration files needed to interface with misc. 3rd party tools
- `./utilities`
	- Collection of shell scripts used by `./make_utility.sh` in order to build+install 3rd-party software

### Files

- `./make_tool.sh`
	- Locally build a tool which may be needed for building/running KOS itself
- `./make_toolchain.sh`
	- Probably the first thing you want to run after cloning KOS. This shell-script will download+configure+build all of the necessary build tools needed so you're able to build KOS for yourself.
	- This includes downloading the GCC source code and setting up a KOS cross-compiler.
	- Used like `bash kos/misc/make_toolchain.sh i386-kos`
- `./make_utility.sh`
	- Used to download+configure+build+install 3rd party software onto your KOS disk image(s)
	- Used like `bash kos/misc/make_utility.sh i386 busybox`
