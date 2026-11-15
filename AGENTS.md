## Repository Overview

This is a matching decompilation project for Mario Party 3 (N64). The goal is to create C code that, when compiled under the original GCC 2.7.2 compiler, produces the exact same ROM as the original game.

## Project Structure

- `src` decompiled or partially decompiled C code.
- `include` shared headers and assembly macros.
- `asm/nonmatchings` unmatched assembly functions extracted from the ROM.
- `asm/data` extracted data assembly.
- `assets` binary asset blobs extracted from the ROM.
- `symbol_addrs.txt` project symbol names and addresses.
- `marioparty3.yaml` Splat configuration for ROM extraction and segment layout.

As more matching C code is written in `src`, the MIPS code under `asm/nonmatchings` decreases.

### Source Layout

- `src/game` game engine code from the main segment. Headers are in `include/game`.
- `src/game/overlays` game overlays, grouped by area:
  - `minigames` minigames (named `<overlay index>_<name>`), the shared minigame library (`common`), instructions, and minigame result screens (`results`).
  - `party` party boards (`boards/w01_chilly_waters`, ...), the shared board library (`common`), board events, intros, and results.
  - `duel` duel boards (`boards/duel01_gate_guy`, ...), the shared duel board library (`common`), intros, and results.
  - `story`, `menus`, `debug` story mode, front-end screens, and debug tools.
- `src/2.0L`, `src/libhmath`, `src/libkmc`, `src/libleo`, `src/libm`, `src/lib` libultra and other library code. A few SDK-derived and segment-wide files remain at the top of `src`.

Overlay directories are set with `dir:` in `marioparty3.yaml`; the segment `name:` is independent and determines symbol suffixes (e.g. `_shared_board`), so moving a directory does not rename symbols.

Headers used by a single overlay live next to its source. Headers shared across overlays go in `include/game/overlays`. Include headers from other directories with paths rooted at `src/` or `include/` (e.g. `"game/overlays/party/common/FA250.h"`), not `../` relative paths.

The binary splitting tool [splat](https://github.com/ethteck/splat) is the backbone of this decompilation. It takes as input our `marioparty3.yaml`, which describes the structure of the ROM. It processes and splits out assets from the ROM into readable formats. The ROM can then be rebuilt using `splat` as well, with the C code being compiled and used in this process. If the C code is an exact match to the original game code, the resulting ROM will be identical.

The primary code committed to this repository is the C code in `src` and `include`. We do not touch the `asm/nonmatchings` or other assets that are produced from `splat`.

When you start working on this repository, assume that assets like `asm/nonmatchings` have already been produced, and the code is in a matching state, unless told otherwise.

## Tools

- `./tools/build.sh` builds the ROM and verifies the SHA1 checksum.
  - The `./tools/build.sh --splat` command is a more intensive rebuild that regenerates files based on the `marioparty3.yaml` and `symbol_addrs.txt`. This is useful if you make changes to either of those files.
  - `./tools/build.sh --clean --splat` is a variation of the above that cleans before the rebuild.
- `python3 tools/asm-differ/diff.py --no-pager <function name>` compares compiled assembly against the target for a specific function.
  - `python3 tools/asm-differ/diff.py --help` to learn all the capabilities of the diffing tool.

Do not install additional software without direct user permission.

## Code Quality Standards

Prefer existing project names, structs, typedefs, and helper macros. Before adding declarations, search `src/` and `include/` for existing definitions to avoid duplicates.

C files should be organized in this order:

- Macro definitions
- Struct definitions
- Global variables
- Function declarations
- Function implementations

C files should only be under `src/`. Header files should either be under `include/` or adjacent to code in `src/`, depending on the scope the header files are intended for.

When matching code, keep source readable and maintainable. Avoid using assembly includes, hard-coded pointer offsets, or broad `void *` typing as substitutes for understanding the data layout.

Loops can often be written multiple ways. Prefer the loop structure that is most legible and likely to be the one that the original developers used. For example, if a `for` loop and a `do...while` loop are both options, and there's a clear initialization, condition, and update that could be used in the `for` loop form, prefer the `for` loop.

Do not use compiler-specific tricks, like forcing register assignment by syntax only supported by GCC.
Do not use `__asm__` or `volatile` tricks.
