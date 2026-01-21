import subprocess
import os

vcpkg_root = os.environ.get('VCPKG_ROOT')

if not vcpkg_root:
    print("Error: VCPKG_ROOT environment variable is not set.")
    print("Please set it to your vcpkg installation directory.")
    exit(1)

os.makedirs("buildfiles/debug", exist_ok=True)
os.makedirs("bin/debug", exist_ok=True)
subprocess.call(f'cmake ../.. -G "Visual Studio 17 2022" -D CMAKE_BUILD_TYPE=Debug -D CMAKE_TOOLCHAIN_FILE="{vcpkg_root}\\scripts\\buildsystems\\vcpkg.cmake', cwd="buildfiles/debug")