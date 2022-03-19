
### Introduction

This file documents the semantic meaning of identifier names seen throughout KOS sources. Read this file and follow its conventions to prevent any confusion regarding the logical meaning of interface- or parameter-names, as well as accompanying documentation.

### KOS terminology and conventions

- Range limits:
	KOS consistently uses the following terms when talking about the bounds of ranges, and always uses these names to mean the following:  
	- `min`, `minimum`: In a range, this describes the lowest element or index. Same logical meaning as `begin` or `start`, but use of this term implies that the upper limit of the range is referred to as `max` or `maximum` (which *does* have a different logical meaning than `end`)
	- `max`, `maximum`: In a range, this describes the greatest element or index. This term is only used if the lowest element is referred to as `min`.
	- `first`, `last`: Same semantic meaning as `min` and `max`, but like `min` and `max` forms a pair that is always used in conjunction, so do `first` and `last`. These two terms are usually used to refer to the actual elements of arrays or vectors.
		- For example, the `get_first(array)` *probably* returns the first element of `array` (or a pointer to it), rather than that element's index, while `get_min(array)` *probably* returns the index of the first element.
		- To prevent confusion, suffixes are sometimes added to emphasize meaning:
			- `get_first_item(array)` **definitely** returns the first element of `array`
			- `get_min_index(array)` **definitely** returns the index of the first element of `array`
	- `head`, `tail`: Yet another pair of semantic identifiers, the same as `min`/`max` and `first`/`last`. The same semantic implications that apply to `first`/`last` also apply to this pair.
	- `begin`, `start`, `base`: Same logical meaning as `min` referring to the lowest element or index of a range. Use of this term implies that the upper limit of the range is referred to as `end` (which *does* have a different logical meaning than `max`).
		- This is also the default meaning when talking about buffers in general. For example, the `buf` in `void foo(void *buf, size_t size);` should be understood as `bufbase`.
	- `end`: The end of a range is either `1` plus the index of the range's last element, or a semantic/theoretical `NULL`-style placeholder representative of what *would* be an element past the range's last element. When working with indices, `end == begin + length`, and assuming that `begin == 0`, this means that the `end` of a range more often than not will equal its `length`.
	- `length`, `len`, `count`, `size`: `1` plus the delta between `max` and `min` (iow: `(max - min) + 1`), or simply the difference between `end` and `begin`. The `length` of a range equals the number of elements contained.
		- Unless otherwise documented, strings do **not** count the trailing `'\0'` to part of the string's `length`.

	Assuming integers and indices, the following invariants can be made:
	- `begin == start == base == min == first == head`
	- `end == begin + length`
	- `max == last == tail == end - 1`
	- `size == length * ELEM_SIZE` (if an `ELEM_SIZE` is implied; see below)

	If applicable, a slight semantic difference is made between `size` and `length`:
	- `length`, `len`, `count`: The number of `elements` in a range. For example:
		- ```c
		  int items[] = { 10, 20, 30 };
		  static_assert(COMPILER_LENOF(items) == 3);
		  ```
		- When taking about the length of a specifically typed object, `size` is often also used to refer to that object's `length`. For example, taking about the *vector size* or *array size* means the *number of elements*, rather than the total amount of memory taken up by those elements. Similarly, when talking about untyped, or `byte_t`-typed data-blobs, `buflen` can also be used for the same meaning as `bufsize` (since in these cases `length` either doesn't have a meaning already, or is required by constraints to equal `size`).
	- `size`: Usually the same meaning as `length`, except when referring to an untyped (usually `void`) or anonymous/opaque data blob (usually taking the form of `void [const] *data` or `void [const] *buf`).
		- ```c
		  int items[] = { 10, 20, 30 };
		  static_assert(sizeof(items) == 3 * sizeof(int));
		  ```
		- In this case, `size` (often also called `bufsize` or `datasize` to prevent ambiguity), refers to the number of elements multiplied by the size of a single element. Thus, if the `bufsize` is known, but the size of an element isn't, then the `length` isn't known either.
		- Note that a term like `datalen` or `buflen` does **NOT** mean the *size* of data-- or a buffer. Such an element refers to the `length` of some data or buffer element. (e.g. `pwformatprinter`'s `datalen` argument indicates the number of characters given by its `wchar const *data` argument)
	For historical reasons, the above rules may be broken by certain interfaces. When this is the case, such breakage must be explicitly documented alongside its occurrence. Code that does not comply with the above conventions, while also failing to document its non-adherence, may be considered a bug.


