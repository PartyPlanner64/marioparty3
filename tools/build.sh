#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$repo_root"

if [[ -f "venv/bin/activate" ]]; then
    # Project build tools expect the repository virtualenv when it is available.
    # shellcheck disable=SC1091
    source "venv/bin/activate"
fi

clean=0
splat=0
verbose=0
version="${VERSION:-us}"
while [[ $# -gt 0 ]]; do
    arg="$1"
    shift
    case "$arg" in
        --version)
            if [[ $# -eq 0 ]]; then
                echo "--version requires a value (e.g. --version us)" >&2
                exit 1
            fi
            version="$1"
            shift
            ;;
        --version=*)
            version="${arg#--version=}"
            ;;
        --clean)
            clean=1
            # --clean implies a full regeneration, so behave like --splat.
            splat=1
            ;;
        --splat)
            splat=1
            ;;
        --verbose)
            verbose=1
            ;;
        *)
            echo "Unknown argument: $arg" >&2
            exit 1
            ;;
    esac
done

# Suppress progress output unless --verbose is given. The Makefile only
# silences progress messages for direct `make` when QUIET=1 is passed.
quiet=()
if [[ "$verbose" -eq 0 ]]; then
    quiet=(QUIET=1)
fi

if [[ "$clean" -eq 1 ]]; then
    make VERSION="$version" distclean
fi

if [[ "$splat" -eq 1 ]]; then
    make VERSION="$version" "${quiet[@]}" setup
fi

exec make -j VERSION="$version" "${quiet[@]}"
