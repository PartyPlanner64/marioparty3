"""Paths for the game version being worked on.

The version comes from the VERSION environment variable (default "us"),
matching `make VERSION=...`. Each version keeps its files under ver/<version>/.
"""

import os
from pathlib import Path

DEFAULT_VERSION = "us"

ROOT = Path(__file__).resolve().parent.parent
VERSION = os.environ.get("VERSION", DEFAULT_VERSION)

VER_DIR = ROOT / "ver" / VERSION
BUILD_DIR = VER_DIR / "build"
ASM_DIR = VER_DIR / "asm"
NONMATCHINGS_DIR = ASM_DIR / "nonmatchings"

BASEROM = VER_DIR / "baserom.z64"
SPLAT_YAML = VER_DIR / "splat.yaml"
SYMBOL_ADDRS = VER_DIR / "symbol_addrs.txt"
UNDEFINED_SYMS = VER_DIR / "undefined_syms.txt"

ROM = BUILD_DIR / "marioparty3.z64"
ELF = BUILD_DIR / "marioparty3.elf"
MAP = BUILD_DIR / "marioparty3.map"

EXPECTED_DIR = ROOT / "expected"

# The C macro value for this version, e.g. "VERSION_JP_PROTO" for "jp-proto".
VERSION_MACRO = "VERSION_" + VERSION.upper().replace("-", "_")


def rel(path: Path) -> str:
    """Path relative to the repository root, as a string."""
    return str(path.relative_to(ROOT))
