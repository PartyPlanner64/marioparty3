import os
import shutil

from version_paths import BUILD_DIR, EXPECTED_DIR, rel

# Mirror this version's build directory under expected/, keeping its path
# (expected/ver/<version>/build) so diff.py can find reference objects.
src_dir = rel(BUILD_DIR)
dst_dir = str(EXPECTED_DIR / src_dir)

# Make sure the destination directory exists
if not os.path.exists(dst_dir):
    os.makedirs(dst_dir)

# Copy all files and subdirectories from the source to the destination directory
for root, dirs, files in os.walk(src_dir):
    for file in files:
        src_path = os.path.join(root, file)
        dst_path = src_path.replace(src_dir, dst_dir, 1)
        shutil.copy2(src_path, dst_path)
    for dir in dirs:
        src_path = os.path.join(root, dir)
        dst_path = src_path.replace(src_dir, dst_dir, 1)
        if not os.path.exists(dst_path):
            os.makedirs(dst_path)