#!/usr/bin/env bash

# wrapper for cppcheck
# see http://cppcheck.sourceforge.net/

# debug
# set -x

cppcheck="/usr/bin/cppcheck"
# red
color_highlight=$(echo -n -e "\033[0;31m")
# reset color
color_end=$(echo -n -e "\033[0m")

assert_dependencies()
{
  # Try to execute cpp check
  "$cppcheck" --help > /dev/null 2>&1 \
    || { echo >&2 "Cannot execute cppcheck"; exit 1; }
  
  # check if first parameter is an existing directory
  [ -d "$1" ] \
    || { echo >&2 "Given parameter is not a directory"; exit 1; } 
}

print_usage()
{
  echo "Usage:" "$0" "[path to project root]"
  echo "       Wrapper for cppcheck"
}

# print usage and exit if number of arguments != 1
[ $# -eq 1 ] || { print_usage ; exit 0; }

# exit if any dependencies are not met
assert_dependencies "$1"

# run cppcheck on all cpp files, enable all checks, use $1 as base directory 
# for includes 
# xargs echo -n: remove trailing newline from arguments
# This might break with filenames containing spaces
"$cppcheck" -I "$1" --quiet --enable=all --error-exitcode=1 \
  $(find "$1" -name "*.h" -or -name "*.cpp" -or -name "*.hpp" | xargs echo -n)\
    2>&1 | sed "s/\[[^]]*\]/${color_highlight}&${color_end}/"

# return with cppcheck's return code 
exit ${PIPESTATUS[0]}

