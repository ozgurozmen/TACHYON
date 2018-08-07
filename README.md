# Fast Signatures from Compact Knapsack

This is the implementation of Tachyon (CCS'18), that is a high-speed post-quantum signature. The paper can be found at ... (eprint link will be provided)

## Tachyon Dependencies

1. b2 - https://github.com/BLAKE2/libb2

## Usage

After installing the dependencies, go to Tachyon folder and make (don't forget to update the makefile, specifically the path). Then, under the Debug folder you can see the executable. Code is tested with Intel i7 Skylake Ubuntu 16.04.

## License

Please check the licenses for the dependencies before using this code.

Special thanks to Peter Rindal for providing the AES codes (in https://github.com/ladnir/cryptoTools) and the fast bitread operations; and the ntt implementation is adopted from pq-crystals (in https://github.com/pq-crystals/dilithium).



