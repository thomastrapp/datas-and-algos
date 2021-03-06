#include "gtest/gtest.h"

#include "al/mergesort/main.h"
#include "al/sort-and-count-inversions/main.h"
#include "al/strassen-matrix-multiply/main.h"
#include "al/radixsort/main.h"
#include "al/murmur/main.h"
#include "al/counting-sort/main.h"
#include "al/boyer-moore/main.h"

#include "ds/stack/main.h"
#include "ds/square-matrix/main.h"
#include "ds/binary-search-tree/main.h"
#include "ds/fixed-hashtable/main.h"
#include "ds/priority-queue/main.h"
#include "ds/bloom-filter/main.h"
#include "ds/infix-ostream-iterator/main.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

