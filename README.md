# Lant

Visualisation of
[Langton's\_ant](https://en.wikipedia.org/wiki/Langton%27s_ant).

    ... a two-dimensional universal Turing machine with a very simple set of rules
    but complex emergent behavior.

## Build an run

**You will need:**

* A C++20 compiler (tested on Clang 14 and GCC 12.2).
* Cmake (requires 3.18, tested with 3.24.1)

Run the following from the `lant` directory.

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/bin/lant
```
