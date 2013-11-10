#!/usr/bin/env bash

# simple build script for cmake builds

set -o pipefail

red_f=$(tput setaf 1)
hl_f=$(tput setaf 5)
bold=$(tput bold)
hl_reset=$(tput op)
hl_reset_all=$(tput sgr0)

# available builds with cmake flags
declare -A builds
builds[release]="-DCMAKE_BUILD_TYPE=Release"
builds[debug]="-DCMAKE_BUILD_TYPE=Debug"
builds[clang_scan]="-DSCAN_BUILD=ON"
builds[tcmalloc]="-DTCMALLOC=ON -DCMAKE_BUILD_TYPE=Debug"
builds[release_symbols]="-DCMAKE_BUILD_TYPE=Release -DSYMBOLS=ON"

print_usage()
{
  echo "Usage:" "$0" "BUILD_TYPE" "PROJECT_ROOT"
  echo "Build cmake project in PROJECT_ROOT with build type BUILD_TYPE"
  echo -n "Available build types: all,"
  {
    local IFS=","
    echo "$*"
  }
}

assert_preconditions()
{
  [ -d "$1" ] || {
    echo >&2 "$1 is not a directory"; exit 1;
  }

  # at least bash version 4 required (associative arrays)
  [ "4" -ge ${BASH_VERSION:0:1} ] || {
    echo >&2 \
      "Bash version >= 4 required, detected version ${BASH_VERSION:0:1}";
    exit 1;
  }
}

#build_names="${!builds[@]}"
[ $# -eq 2 ] || { print_usage ${!builds[@]} ; exit 0; }

# prefix to make command (required by clang's scan-build)
declare -A make_prefix
make_prefix[clang_scan]="scan-build"

project_root="$2"
assert_preconditions "$project_root"

# build available?
[[ "$1" == "all" || ${builds[$1]} ]] || {
  echo >&2 "$1 is not an available build type"; exit 1;
}

selected_builds=""
if [[ "$1" == "all" ]] ; then
  selected_builds=${!builds[@]}
else
  selected_builds="$1"
fi

cd "$project_root" || {
  echo >&2 "Failed changing working directory to $project_root"; exit 1; 
}

[ -d build ] || {
  mkdir build || { 
    echo >&2 "Build directory does not exist and mkdir failed"; exit 1; 
  }
}

cd build || {
  echo >&2 "Failed changing into build directory"; exit 1;
}

for build_type in ${selected_builds[@]} ; do
  echo 
  echo "${hl_reset}${hl_f}*******************************${hl_reset}"
  echo "${hl_reset}${hl_f}***  ${bold}${red_f}$build_type${hl_reset_all}"
  echo "${hl_reset}${hl_f}*******************************${hl_reset}"

  [ -d "$build_type" ] || {
    mkdir "$build_type" || {
      echo >&2 "Directory $build_type doesn't exist and mkdir failed";
      exit 1;
    }
  }

  cd "$build_type" || {
    echo >&2 "Failed changing into directory $build_type"; exit 1;
  }

  make clean > /dev/null 2>&1
  # there's no "cmake clean"
  find . -iname "*cmake*" -exec rm -rf {} \+

  cmake ${builds[$build_type]} ../../ | sed "s/^/    /" || {
    echo >&2 "cmake ${builds[$build_type]} failed in build $build_type"; 
    exit 1;
  }

  ${make_prefix[$build_type]} make | sed "s/^/    /" || {
    echo >&2 "make failed in build $build_type"; 
    exit 1;
  }

  cd .. || {
    echo >&2 "Failed leaving build directory"; exit 1;
  }
done

cd ..
echo
find build/ -maxdepth 2 -executable -type f -exec ls -lah --color {} \;

