#pragma once

#include <cstdint>

using byte = unsigned char;
static_assert(sizeof(byte) == 1, "Bytes of 'byte' type is not 1 bytes.");

using word = unsigned short;
static_assert(sizeof(word) == 2, "Bytes of 'word' type is not 2 bytes.");

using dword = unsigned long;
static_assert(sizeof(dword) == 4, "Bytes of 'dword' type is not 4 bytes.");

using handle = void*;
