#include <stdint.h>
#include <stdio.h>

#include "botan/ffi.h"

botan_hash_t ctx;

extern void RunTarget(FILE *input) {
  // TODO Read test case and execute target primitive

  // Everything in this function is traced.

  // Avoid calling a library's debug output functionality outside clear error
  // conditions: These functions can produce _a lot_ of trace entries and, as
  // they are almost certainly not constant-time, they may also generate a
  // considerable number of false positives. printf() and others I/O
  // functionality from the C standard library are _usually_ fine, as this
  // library is skipped during the analysis by default.

  uint8_t in[32];
  if (fread(in, 1, 32, input) != 32)
    return;

  // whirlpool
  uint8_t out[64];
  botan_hash_update(ctx, in, 32);
  botan_hash_final(ctx, out);
}

extern void InitTarget(FILE *input) {
  // TODO Initialize library

  // This function is called once before running the first test case.
  // In some scenarios, especially if there isn't a dedicated initialization
  // function, it is best to just run the first test case, which is why this
  // method receives a file handle for the first test case file:
  // RunTarget(input);

  // You should really avoid that a part of the library gets initialized late,
  // as this may generate false positives.

  uint8_t key[32];
  if (fread(key, 1, 32, input) != 32)
    return;

  // whirlpool
  botan_hash_init(&ctx, "Whirlpool", 0);
}
