#!/usr/bin/env python3
"""
Re-apply the libleo LeoBootGame code obfuscation to a linked ROM.

__LeoBootGame2 is stored obfuscated in the original ROM. At runtime,
LeoBootGame (src/libleo/bootgame.c) subtracts a key from byte 2 and adds it to
byte 3 of every word. The key is the sum of the bytes of __LeoBootGame2's
address. This script performs the inverse operation on the built ROM.

usage: leo_encrypt.py <rom.z64> <linker.map>
"""

import re
import sys

SYMBOL = "__LeoBootGame2"
SIZE = 0x344


def read_map_symbols(map_path, names):
    found = {}
    pattern = re.compile(r"^\s+0x([0-9a-fA-F]+)\s+(\S+)(?:\s*=.*)?$")
    with open(map_path) as f:
        for line in f:
            m = pattern.match(line)
            if m and m.group(2) in names and m.group(2) not in found:
                found[m.group(2)] = int(m.group(1), 16)
    missing = [n for n in names if n not in found]
    if missing:
        sys.exit(f"leo_encrypt.py: symbols not found in map: {', '.join(missing)}")
    return found


def main():
    rom_path, map_path = sys.argv[1], sys.argv[2]
    syms = read_map_symbols(map_path, [SYMBOL, "main_ROM_START", "main_VRAM"])

    addr = syms[SYMBOL]
    rom_offset = addr - syms["main_VRAM"] + syms["main_ROM_START"]
    key = sum(addr.to_bytes(4, "big")) & 0xFF

    with open(rom_path, "r+b") as f:
        f.seek(rom_offset)
        data = bytearray(f.read(SIZE))
        for i in range(0, SIZE, 4):
            data[i + 2] = (data[i + 2] + key) & 0xFF
            data[i + 3] = (data[i + 3] - key) & 0xFF
        f.seek(rom_offset)
        f.write(data)


if __name__ == "__main__":
    main()
