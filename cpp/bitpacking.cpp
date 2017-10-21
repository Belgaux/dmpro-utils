#include <iostream>
#include <bitset>
#include <chrono>
#include <random>
#include <cstdint>
#include <cstdlib>
#include "x86intrin.h"

#define D 64
#define N 64

uint32_t bitpack32(const bool b[32]) {
  // Pack an array of 32 bytes, each byte representing only 1 bit
  // into a single uint32_t
  __m256i tmp = _mm256_loadu_si256((const __m256i *) b);
  tmp = _mm256_cmpgt_epi8(tmp, _mm256_setzero_si256());
  return _mm256_movemask_epi8(tmp);
}

uint64_t bitpack64(const uint64_t a[64]) {
  // Pack an array of uint64_t, each representing only 1 bit
  // into a single uint64_t

  bool *b1 = (bool *) malloc(sizeof(bool) * 32);
  bool *b2 = (bool *) malloc(sizeof(bool) * 32);
  for (int i = 0; i < 32; ++i) {
    b1[i] = (bool) a[i];
    b2[i] = (bool) a[i+32];
  }
  
  uint32_t low = bitpack32(b1);
  uint32_t high = bitpack32(b2);
  free(b1);
  free(b2);
  return (((uint64_t) high) << 32) | ((uint64_t) low);
}

int main()
{
#ifdef __AVX2__
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937_64 generator (seed);
  std::uniform_int_distribution<uint64_t> distribution(0, 1);

  uint64_t *a = (uint64_t *) malloc(sizeof(uint64_t) * N);
  printf("Full representation of each number:\n");
  for (int i = 0; i < N; ++i) {
    a[i] = distribution(generator);
    std::bitset<D> b(a[i]);
    std::cout << b << std::endl;
  }

  printf("Expected bitstring representation:\n");
  for (int i = N-1; i >= 0; --i)
    printf("%zu", a[i]);
  printf("\n");

  printf("Bitpacking into a uin64_t with intel intrinsics:\n");
  uint64_t res = bitpack64(a);
  std::bitset<D> b(res);
  std::cout << b << std::endl;

  free(a);
#endif
  return 0;
}
