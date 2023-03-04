#!/bin/bash

set -euo pipefail

my_dir="$(dirname "$(realpath "$0")")"

args=("$@")
cmake_args=()
ninja_args=()

# Parse args
if [[ " ${args[*]} " =~ " help " ]]; then
    echo "Usage: $0 [options..], where [options..] can be zero or more of:
        help
        verbose
        clean - Clean the output directory before building
        release - Build for release mode
        dirty - Do not generate warnings and errors
        tidy - Do not build, instead run clang-tidy checks (takes some time)
        run - Run the program after build"
    exit
fi

if [[ " ${args[*]} " =~ " verbose " ]]; then
    ninja_args+=("-v")
fi

config="Debug"
if [[ " ${args[*]} " =~ " release " ]]; then
    config="Release"
fi

out_dir="${my_dir}/out"
configured_out_dir="${out_dir}/${config}"

target="all"
if [[ " ${args[*]} " =~ " dirty " ]]; then
    cmake_args+=("-DDIRTY=1")
    target="raytrace"
elif [[ " ${args[*]} " =~ " tidy " ]]; then
    target="clang-tidy"
fi

# Clean
if [[ " ${args[*]} " =~ " clean " ]]; then
    rm -fr "${out_dir}"
fi

# Generate
mkdir -p "${out_dir}"
# Word splitting intended
# shellcheck disable=2068
CC="$(command -v clang)" CXX="$(command -v clang++)" cmake -S "${my_dir}" -B "${out_dir}" -G "Ninja Multi-Config" ${cmake_args[@]}

# Build
# Word splitting intended
# shellcheck disable=2068
cmake --build "${out_dir}" --config "${config}" --target "${target}" -- ${ninja_args[@]}

# Run
if [[ " ${args[*]} " =~ " run " ]]; then
    image="${configured_out_dir}/image.ppm"
    "${configured_out_dir}/raytrace" >"${image}"
    viewnior "${image}"
fi
