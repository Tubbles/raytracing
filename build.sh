#!/bin/bash

set -euo pipefail

# dirs
my_dir="$(dirname "$(realpath "$0")")"
out_dir="${my_dir}/out"
src_dir="${my_dir}/src"

# files
binary="${out_dir}/raytrace"
sources="${src_dir}/"*.cpp

# libs
libs=(
    "-lfmt"
)

mkdir -p "${out_dir}"
cd "${out_dir}"

set -x

g++ --std=c++23 -g -o "${binary}" ${libs[@]} ${sources}
