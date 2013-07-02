#!/usr/bin/env bash

cd test/build && cmake .. && make && ./data-structures-test

exit $?

