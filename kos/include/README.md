
## KOS System headers

### Portability Notes

KOS system headers are designed and written to maximize portability with existing systems, and to aid programmers using the KOS system header suite in knowing which headers exist in which platforms.

For this purpose, many System headers begin with (after the leading copyright notice) lines such as (from `<string.h>`):  

```c
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/string.h) */
/* (#) Portability: DJGPP         (/include/string.h) */
/* (#) Portability: FreeBSD       (/include/string.h) */
/* (#) Portability: GNU C Library (/string/string.h) */
...
```

As an explaination, `(>) Standard:` lists a standard that mention/include the surrounding header, while `(#) Portability:` lists (a sub-set of) 3rd-party libc implementations or operating systems that provide a header of the same name (note though that this only means that the header exists on that system, not that it necessarily behaves the same). The filename path within parenthesis is to be interpreted as a path relative to the corresponding 3rd-party project, under which that project's version of the same header can be found. No guaranty can made as to the consistency of the header's location between different versions of 3rd-party projects, and no reference version is given so-as not to give the idea that only certain versions of 3rd-party projects support the header, even if this may be the case.

Furthermore, these notes do not mean to imply any affiliation between KOS and the named project. The list of header-portability to other projects was/is simply generated automatically from a collection of different, open-source projects I've collected over the time for the purpose of study and reference.

The only purpose of portability notes is to give the Programmer an idea of how wide-speard support for a certain system header is, and which standards exist that mandate the contents of the header, helping the decision-making process when it comes to selecting optional/mandatory interfaces used by portable programs.


#### Mentioned Standards

- [Posix](https://en.wikipedia.org/wiki/POSIX)
	- POSIX.1 (Issue 1, IEEE Std 1003.1-1988)
	- POSIX.1b (Issue 2, IEEE Std 1003.1b-1993)
	- POSIX.1c (Issue 3, IEEE Std 1003.1c-1995)
	- POSIX.2 (Issue 4, IEEE Std 1003.2-1992)
	- POSIX.1-2001 (Issue 5, IEEE Std 1003.1-2001)
	- POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004)
	- POSIX.1-2008 (Issue 7, IEEE Std 1003.1-2008)
- [ISO C](https://en.wikipedia.org/wiki/POSIX)
	- ISO C89 (ANSI X3.159-1989)
	- ISO C95 (ISO/IEC 9899:1990/AMD1:1995)
	- ISO C99 (ISO/IEC 9899:1999)
	- ISO C11 (ISO/IEC 9899:2011)


