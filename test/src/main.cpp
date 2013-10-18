#include "gtest/gtest.h"

#include "ds/stack/main.h"
#include "ds/square-matrix/main.h"
#include "ds/binary-search-tree/main.h"

#include "al/mergesort/main.h"
#include "al/sort-and-count-inversions/main.h"
#include "al/strassen-matrix-multiply/main.h"
#include "al/radixsort/main.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

