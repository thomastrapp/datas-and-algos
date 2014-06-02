#include <cstdlib>
#include <iostream>

#include "al/murmur.h"

#include "KeysetTest.h"
#include "MurmurHash3.h"

void smhasher_murmur_32(const void * data, int num_bytes, uint32_t seed, void * out)
{
  const uint32_t hash = 
    al::murmur_32(
      static_cast<const uint32_t *>(data),
      static_cast<size_t>(num_bytes),
      seed
    )
  ;

  uint32_t * out_p = static_cast<uint32_t *>(out);
  *out_p = hash;
}

void smhasher_murmur_128(const void * data, int num_bytes, uint32_t seed, void * out)
{
  auto hash =
    al::murmur_128(
      static_cast<const uint64_t *>(data),
      static_cast<size_t>(num_bytes),
      seed
    )
  ;

  uint64_t * out_p = static_cast<uint64_t *>(out);
  out_p[0] = hash.first;
  out_p[1] = hash.second;
}

struct HashInfo
{
  pfHash hash;
  int hashbits;
  uint32_t verification;
  const char * name;
  const char * desc;
};

HashInfo g_hashes[] =
{
  { MurmurHash3_x86_32, 32, 0xB0F57EE3, "Murmur3A",
      "MurmurHash3 for x86, 32-bit" },
  { smhasher_murmur_32, 32, 0xB0F57EE3, "al::murmur_32",
      "al::murmur_32" },
  { MurmurHash3_x64_128, 128, 0x6384BA69, "Murmur3F",
      "MurmurHash3 for x64, 128-bit" },
  { smhasher_murmur_128, 128, 0x6384BA69, "al::murmur_128",
      "al::murmur_128" }
};

int main(int argc, char * argv[])
{
  for(size_t i = 0; i < sizeof(g_hashes) / sizeof(HashInfo); i++)
  {
    HashInfo * info = &g_hashes[i];
    std::cout << info->name << "\n"
              << "---------------------------"
                 "---------------------------"
              << "\n";
    
    std::cout << "VerificationTest: " << "\t";
    VerificationTest(info->hash, info->hashbits, info->verification, true);

    std::cout << "SanityTest: " << "\t\t";
    SanityTest(info->hash, info->hashbits);
    
    std::cout << "AppendZeroesTest: " << "\t";
    AppendedZeroesTest(info->hash, info->hashbits);

    std::cout << std::endl;
  }

  return EXIT_SUCCESS;
}

