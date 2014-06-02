#!/usr/bin/env bash

cd test/build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make && ./datas-and-algos-test

exit $?

