// Tools for work memory (SRAM)

/*
  Author: Martin Eden
  Last mod.: 2026-03-17
*/

#pragma once

#include <me_BaseTypes.h>

namespace me_WorkmemTools
{
  // Describe ASCIIZ structure as memory segment
  TAddressSegment FromAsciiz(TAsciiz Asciiz);

  // Fill memory span with zero byte
  void ZeroMem(TAddressSegment MemSeg);

  // Copy data to another segment
  void CopyMemTo(TAddressSegment Dest, TAddressSegment Src);

  // Data equality check
  TBool AreEqual(TAddressSegment A, TAddressSegment B);

  // Reserve block of memory. Zeroes after allocation
  TBool Reserve(TAddressSegment * MemSeg, TUint_2 Size);

  // Release block of memory. Zeroes before release
  void Release(TAddressSegment * MemSeg);
}

/*
  2024 # # # # # #
  2025-08-29
  2026-03-17
*/
