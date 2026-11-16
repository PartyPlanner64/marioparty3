#!/usr/bin/env python3
"""Bulk-rename placeholder symbols (func_80XXXXXX_seg / D_80XXXXXX_seg).

Usage:
    python3 tools/rename_symbols.py MAPFILE [--dry-run]

MAPFILE contains one rename per line: `old_name new_name`. Blank lines and
lines starting with `#` are ignored.

For each rename this tool:
  * replaces whole-word occurrences in src/, include/ and undefined_syms.txt
  * renames an existing symbol_addrs.txt entry in place, or adds a new entry
    (with segment: and, when inside the segment's ROM range, rom:) to a
    per-segment block at the end of symbol_addrs.txt

Afterwards run `./tools/build.sh --splat` to verify the ROM still matches.
"""

import argparse
import re
import sys
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent
SYMBOL_ADDRS = ROOT / "symbol_addrs.txt"
YAML_PATH = ROOT / "marioparty3.yaml"
TEXT_DIRS = [ROOT / "src", ROOT / "include"]
EXTRA_FILES = [ROOT / "undefined_syms.txt"]
SOURCE_EXTS = {".c", ".h", ".inc"}

PLACEHOLDER_RE = re.compile(r"^(func|D)_([0-9A-F]{8})(?:_([A-Za-z0-9_]+))?$")
IDENT_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
ENTRY_RE = re.compile(r"^\s*([A-Za-z_][A-Za-z0-9_$.]*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;(.*)$")


def load_segments():
    """Return {name: (rom_start, rom_end, vram_start)} for named code segments."""
    data = yaml.safe_load(YAML_PATH.read_text())
    segs = data["segments"]
    starts = []
    for seg in segs:
        if isinstance(seg, dict):
            starts.append(seg.get("start"))
        elif isinstance(seg, list):
            starts.append(seg[0])
        else:
            starts.append(None)
    result = {}
    for i, seg in enumerate(segs):
        if not isinstance(seg, dict) or "vram" not in seg or "name" not in seg:
            continue
        rom_start = seg["start"]
        rom_end = next((s for s in starts[i + 1 :] if isinstance(s, int)), None)
        result[seg["name"]] = (rom_start, rom_end, seg["vram"])
    return result


def main_segment_for(vram, segments):
    for name in ("main",):
        if name in segments:
            rs, re_, vs = segments[name]
            if re_ is not None and vs <= vram < vs + (re_ - rs) + 0x100000:
                return name
    return None


def parse_map(path):
    renames = []
    for lineno, raw in enumerate(path.read_text().splitlines(), 1):
        line = raw.split("#", 1)[0].strip()
        if not line:
            continue
        parts = line.split()
        if len(parts) != 2:
            sys.exit(f"{path}:{lineno}: expected 'old new', got: {raw!r}")
        renames.append((parts[0], parts[1], lineno))
    return renames


def iter_text_files():
    for d in TEXT_DIRS:
        for p in d.rglob("*"):
            if p.is_file() and p.suffix in SOURCE_EXTS:
                yield p
    for p in EXTRA_FILES:
        if p.exists():
            yield p


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("mapfile", type=Path)
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    renames = parse_map(args.mapfile)
    segments = load_segments()

    # Validate.
    errors = []
    olds, news = {}, {}
    for old, new, ln in renames:
        if not IDENT_RE.match(new):
            errors.append(f"line {ln}: invalid identifier {new!r}")
        if old in olds:
            errors.append(f"line {ln}: {old} renamed twice")
        if new in news:
            errors.append(f"line {ln}: {new} used twice (also line {news[new]})")
        olds[old] = new
        news[new] = ln
        if PLACEHOLDER_RE.match(new):
            errors.append(f"line {ln}: new name {new} looks like a placeholder")

    sym_text = SYMBOL_ADDRS.read_text()
    existing_entry_names = set()
    sized_ranges = []  # (segment, start, end) of entries declaring a size
    for line in sym_text.splitlines():
        m = ENTRY_RE.match(line)
        if m:
            existing_entry_names.add(m.group(1))
            size_m = re.search(r"size:(0x[0-9A-Fa-f]+)", m.group(3))
            seg_m = re.search(r"segment:(\w+)", m.group(3))
            if size_m:
                start = int(m.group(2), 16)
                sized_ranges.append((seg_m.group(1) if seg_m else None, start, start + int(size_m.group(1), 16)))

    files = list(iter_text_files())
    contents = {p: p.read_text(encoding="utf-8", errors="surrogateescape") for p in files}
    all_words = set()
    word_re = re.compile(r"\b[A-Za-z_][A-Za-z0-9_]*\b")
    comment_re = re.compile(r"//[^\n]*|/\*.*?\*/", re.S)
    for text in contents.values():
        all_words.update(word_re.findall(comment_re.sub(" ", text)))
    all_words.update(existing_entry_names)

    for old, new, ln in renames:
        if new in all_words and new not in olds:
            errors.append(f"line {ln}: new name {new} already exists in the project")
        if old not in all_words:
            errors.append(f"line {ln}: old name {old} not found in src/include/symbol_addrs")

    if errors:
        print("\n".join(errors), file=sys.stderr)
        sys.exit(1)

    # Replace in source files.
    pattern = re.compile(r"\b(" + "|".join(re.escape(o) for o in sorted(olds, key=len, reverse=True)) + r")\b")
    changed_files = 0
    for p, text in contents.items():
        new_text = pattern.sub(lambda m: olds[m.group(1)], text)
        if new_text != text:
            changed_files += 1
            if not args.dry_run:
                p.write_text(new_text, encoding="utf-8", errors="surrogateescape")

    # Update symbol_addrs.txt.
    lines = sym_text.splitlines()
    renamed_in_place = set()
    for i, line in enumerate(lines):
        m = ENTRY_RE.match(line)
        if m and m.group(1) in olds:
            old = m.group(1)
            lines[i] = line.replace(old, olds[old], 1)
            renamed_in_place.add(old)
        elif "//" in line:
            # Commented-out or trailing references.
            lines[i] = pattern.sub(lambda mm: olds[mm.group(1)], line)

    to_add = {}
    for old, new, ln in renames:
        if old in renamed_in_place:
            continue
        m = PLACEHOLDER_RE.match(old)
        if not m:
            print(f"warning: {old} is not a placeholder and has no symbol_addrs entry; only source was updated")
            continue
        vram = int(m.group(2), 16)
        seg = m.group(3)
        if any(rs < vram < re_ and rseg == seg for rseg, rs, re_ in sized_ranges):
            print(f"note: {new} (0x{vram:08X}) lies inside a sized symbol; not adding a symbol_addrs entry")
            continue
        if seg is None:
            seg = main_segment_for(vram, segments)
        attrs = []
        if seg and seg in segments:
            rs, re_, vs = segments[seg]
            rom = rs + (vram - vs)
            if re_ is not None and rs <= rom < re_:
                attrs.append(f"rom:0x{rom:X}")
            if m.group(3) is not None:
                attrs.append(f"segment:{seg}")
        elif seg:
            if any(seg.startswith(s + "_") for s in segments):
                # e.g. a struct type named after a symbol (D_8011..._seg_Struct): source-only.
                continue
            errors.append(f"line {ln}: unknown segment {seg!r} for {old}")
            continue
        entry = f"{new} = 0x{vram:08X};" + (f" //{' '.join(attrs)}" if attrs else "")
        to_add.setdefault(seg or "main", []).append((vram, entry))

    if errors:
        print("\n".join(errors), file=sys.stderr)
        sys.exit(1)

    for seg, entries in to_add.items():
        header = f"// renamed: {seg}"
        entries.sort()
        if header in lines:
            idx = lines.index(header) + 1
            block_end = idx
            while block_end < len(lines) and lines[block_end].strip():
                block_end += 1
            block = lines[idx:block_end] + [e for _, e in entries]
            block.sort(key=lambda l: int(ENTRY_RE.match(l).group(2), 16) if ENTRY_RE.match(l) else 0)
            lines[idx:block_end] = block
        else:
            if lines and lines[-1].strip():
                lines.append("")
            lines.append(header)
            lines.extend(e for _, e in entries)
            lines.append("")

    if not args.dry_run:
        SYMBOL_ADDRS.write_text("\n".join(lines).rstrip("\n") + "\n")

    print(f"{len(renames)} renames, {changed_files} source files changed, "
          f"{len(renamed_in_place)} symbol_addrs entries renamed, "
          f"{sum(len(v) for v in to_add.values())} entries added"
          + (" (dry run)" if args.dry_run else ""))


if __name__ == "__main__":
    main()
