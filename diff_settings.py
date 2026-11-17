#!/usr/bin/env python3

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent / "tools"))
from version_paths import BASEROM, MAP, ROM, VERSION, rel


def apply(config, args):
    config['baseimg'] = rel(BASEROM)
    config['myimg'] = rel(ROM)
    config['mapfile'] = rel(MAP)
    config['source_directories'] = ['.']
    config['makeflags'] = [f'VERSION={VERSION}']
