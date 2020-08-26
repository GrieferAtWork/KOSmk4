
## Files in this folder

KOS IDE/project/development configuration files


### What is `usertype.dat`?

This is a file which contains some g++-specific C/C++ language keywords that may occasionally be used in KOS source files. It's meant to-be used to aid Visual Studio in doing proper syntax highlighting for these keywords, as it's IDE (despite being able to understand these keywords) doesn't highlight them properly.

### What to do with `usertype.dat`?

Firstly, I'd like to emphasize that doing anything with this file is entirely optional, as installing it properly involves a slight modification to your installation of Visual Studio.

Anyways: You simply drop a copy the file into the same folder that your `devenv.exe` is stored in. To find this folder:

- Start *Visual Studio*
- Open *Task Manager*
- Go to *details*
- Right-click *devenv.exe*
- Click on *Open File Location* (or whatever it's called in your locale)
- Copy *usertype.dat* into the folder that just opened up
	- Unless you've done something like this before, no such file should already exist.
- Restart *Visual Studio*

At this point, all of the keywords from `usertype.dat` should be highlighted the same way that other, normal keywords (like `if` or `switch`) are.

Sadly, there is no way to do something like this on a per-project basis...

### Why should I care about `usertype.dat`?

You don't have to. - This is only about making gcc code in Visual Studio look better.

