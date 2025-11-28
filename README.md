# get_next_line

## Line-by-line file reader
A simple and efficient function to read one line at a time from a file descriptor.

---

## Project status :
This project is still in development, its structure (and perhaps behaviour) will change before the end

## 🧩 Overview

`get_next_line` reads the next line from a given file descriptor, returning a freshly allocated string **including the trailing newline** (except for the last line if no newline is present).
Its purpose is to make file reading predictable, safe, and easy to use in loops.

---

## ⚙️ Behaviour

`get_next_line` supports up to `MAX_FD` file descriptors simultaneously (1024 by default).
You can redefine this macro at compile time, for example:

```bash
-D MAX_FD=42
````

You may also change the size of the internal read buffer by setting the `BUFFER_SIZE` macro:

```bash
-D BUFFER_SIZE=42
```

### 📌 Notes

* `get_next_line` returns **NULL** at end-of-file
* `get_next_line` returns **NULL** on read or allocation failure
* `get_next_line` returns **NULL** if the file descriptor is invalid (`-1`) or closed
* `get_next_line` returns **NULL** if the file descriptor is greater than `MAX_FD`

---

## ⚠️ Undefined behaviour

`get_next_line` exhibits undefined behaviour in the following cases:

* If the file associated with the given file descriptor is **modified between calls**
* If the file descriptor refers to a **binary file**
* If you pass invalid or corrupted file descriptors from external libraries

These cases may result in memory corruption, infinite loops, unexpected return values, the release of Half Life 3, a complete collapse of the space time continuum, we don't know, it's undefined.

---

## 🧪 Example usage

```c
int     fd = open("file.txt", O_RDONLY);
char    *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

---

## 🛠️ Compilation

To compile with custom macros:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=128 your_program.c get_next_line.c get_next_line_utils.c -o gnl_test
```

---

## 📦 Usage & Licensing

You are free to download, edit, reuse, and integrate this code into any project — educational or personal.

A proper release will be uploaded *soon™*, including:

* a precompiled archive (`get_next_line.a`)
* a full header

---

## ➕ PS:
To stress-test the function, you can find the holy bible in raw text at [this url](https://www.gutenberg.org/cache/epub/7999/pg7999.txt) | [(alt)](https://ebible.org/eng-web/links.htm?utm_source=chatgpt.com)
