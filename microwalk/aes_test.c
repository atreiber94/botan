#include <stdint.h>
#include <stdio.h>

#include "botan/ffi.h"

botan_block_cipher_t ctx;

int main() {

  uint8_t key[] = {0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe,
                   0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
                   0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7,
                   0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4};
  uint8_t in[] = {0xf3, 0xee, 0xd1, 0xbd, 0xb5, 0xd2, 0xa0, 0x3c,
                  0x06, 0x4b, 0x5a, 0x7e, 0x3d, 0xb1, 0x81, 0xf8};

  botan_block_cipher_init(&ctx, "AES-256");
  botan_block_cipher_set_key(ctx, key, 32);

  uint8_t out[32];
  botan_block_cipher_encrypt_blocks(ctx, in, out, 1);

  return 0;
}
