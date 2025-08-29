// Tools for work memory (SRAM)

/*
  Author: Martin Eden
  Last mod.: 2025-08-29
*/

#pragma once

#include <me_BaseTypes.h>

namespace me_WorkmemTools
{
  /*
    Allocated memory segment

    It manages memory, and guarantees it will release it upon death.
  */
  class TManagedMemory
  {
    public:
      // Freeing destructor
      ~TManagedMemory();

      // Return data segment
      TAddressSegment GetData();

      // Return data segment size
      TUint_2 GetSize();
      // Resize data segment
      TBool ResizeTo(TUint_2 NewSize);
      // [Handy] Release data segment
      void Release();

      // Load from arbitrary span
      TBool LoadFrom(TAddressSegment SrcSeg);
      // Load from ASCIIZ
      TBool LoadFrom(const TAsciiz Asciiz);
      // Load from our specie
      TBool LoadFrom(TManagedMemory * Src);

    private:
      TAddressSegment DataSeg;
  };

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
*/
