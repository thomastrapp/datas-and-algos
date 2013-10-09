# see http://stackoverflow.com/questions/7671538/how-to-generate-1-million-random-integers-and-write-them-to-a-file

import random

for _ in xrange(1000000): 
  print(random.randint(0, 10000000))

