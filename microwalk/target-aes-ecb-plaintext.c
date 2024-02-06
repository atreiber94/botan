#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "botan/ffi.h"

botan_block_cipher_t ctx;

extern void RunTarget(FILE *input) {
  // TODO Read test case and execute target primitive

  // Everything in this function is traced.

  // Avoid calling a library's debug output functionality outside clear error
  // conditions: These functions can produce _a lot_ of trace entries and, as
  // they are almost certainly not constant-time, they may also generate a
  // considerable number of false positives. printf() and others I/O
  // functionality from the C standard library are _usually_ fine, as this
  // library is skipped during the analysis by default.

  uint8_t in[32] = {0};
  fread(in, 1, 32, input);

  uint8_t out[32] = {0};
  botan_block_cipher_encrypt_blocks(ctx, in, out, 2);
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

  uint8_t key[32] = {0};

  botan_block_cipher_init(&ctx, "AES-256");
  botan_block_cipher_set_key(ctx, key, 32);

  RunTarget(input);
}
