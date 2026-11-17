#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022 AngheloAlf
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import mapfile_parser
from pathlib import Path

from version_paths import EXPECTED_DIR, MAP, rel


def symInfoMain():
    parser = argparse.ArgumentParser(description="Display various information about a symbol or address.")
    parser.add_argument("symname", help="symbol name or VROM/VRAM address to lookup")
    parser.add_argument("-e", "--expected", dest="use_expected", action="store_true", help="use the map file under expected/ instead of the current build")

    args = parser.parse_args()

    mapPath = MAP
    if args.use_expected:
        mapPath = EXPECTED_DIR / rel(MAP)

    mapfile_parser.frontends.sym_info.doSymInfo(mapPath, args.symname)

if __name__ == "__main__":
    symInfoMain()