#!/usr/bin/env bash

# wrapper for Google's cpplint.py
# see http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml

# debug
# set -x

cpplint="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/cpplint.py"

assert_dependencies()
{
  # Try to execute cpplint
  "$cpplint" --filter= > /dev/null 2>&1 \
    || { echo >&2 "Cannot execute cpplint; place it in the working directory"; exit 1; }
  
  # check if first parameter is an existing directory
  [ -d "$1" ] \
    || { echo >&2 "Given parameter is not a directory"; exit 1; } 
}

print_usage()
{
  echo "Usage:" "$0" "[path to project root]"
  echo "       Wrapper for cpplint"
}

# print usage and exit if number of arguments != 1
[ $# -eq 1 ] || { print_usage ; exit 0; }

# exit if any dependencies are not met
assert_dependencies "$1"

# run cpplint on all cpp files 
# Some checks are disabled, since google's lint is very restrictive
# xargs echo -n: remove trailing newline from arguments
# This might break with filenames containing spaces
2>&1 "$cpplint" --filter=-whitespace,-legal,-build/header_guard,\
-build/include_order,-runtime/references,-readability/streams \
  $(find "$1" -name "*.h" -or -name "*.cpp" -or -name "*.cc" | xargs echo -n)\
| grep -v ^Done

# return with cpplint's return code 
exit ${PIPESTATUS[0]}

# useful helper to print each line
# Testing/run_cpplint.sh . 2>&1 | grep -v ^Done | grep -v ^Total | \
# grep references | awk '{ print $1; }' | awk -F":" \
# '{ printf "sed -n -e "; printf $2; printf "p " ; print $1 }' \
# > reference_test.sh

