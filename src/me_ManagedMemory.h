// Management of memory segment in dynamic memory

/*
  Author: Martin Eden
  Last mod.: 2024-10-18
*/

/*
  Central part of this module is allocated memory segment.

  It manages memory, and guarantees it will release it upon death.
*/

#pragma once

#include <me_MemorySegment.h>
#include <me_BaseTypes.h>

namespace me_ManagedMemory
{
  /*
    Allocated memory segment
  */
  class TManagedMemory
  {
    public:
      // Freeing destructor
      ~TManagedMemory();

      // Return data segment
      me_MemorySegment::TMemorySegment GetData();

      // Return data segment size
      TUint_2 GetSize();
      // Resize data segment
      TBool ResizeTo(TUint_2 NewSize);
      // [Handy] Release data segment
      void Release();

      // Load from arbitrary span
      TBool LoadFrom(me_MemorySegment::TMemorySegment SrcSeg);
      // Load from ASCIIZ
      TBool LoadFrom(const TChar * Asciiz);
      // Load from our specie
      TBool LoadFrom(TManagedMemory * Src);

    private:
      me_MemorySegment::TMemorySegment DataSeg;
  };
}

/*
  2024-06-02
  2024-06-04
  2024-06-15
  2024-07-06
  2024-10-05
  2024-10-18 [<] Moved Freetown to [me_MemorySegment]
*/
