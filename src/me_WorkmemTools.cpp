// Utility functions for RAM memory segment

/*
  Author: Martin Eden
  Last mod.: 2025-08-29
*/

#include <me_WorkmemTools.h>

#include <me_BaseTypes.h>
#include <me_StreamTools.h>
#include <me_WorkMemory.h>
#include <me_MemorySegment.h>

#include <stdlib.h> // malloc(), free()

using namespace me_WorkmemTools;

/*
  Fill memory span with zero byte
*/
void me_WorkmemTools::ZeroMem(
  TAddressSegment MemSeg
)
{
  me_StreamTools::TZeroesInputStream ZeroesInputStream;
  me_WorkMemory::TOutputStream OutputStream;

  if (!OutputStream.Init(MemSeg))
    return;

  me_StreamTools::CopyStreamTo(&ZeroesInputStream, &OutputStream);
}

/*
  Copy data to another segment
*/
void me_WorkmemTools::CopyMemTo(
  TAddressSegment Dest,
  TAddressSegment Src
)
{
  me_WorkMemory::TInputStream InputStream;
  me_WorkMemory::TOutputStream OutputStream;

  if (!InputStream.Init(Src))
    return;

  if (!OutputStream.Init(Dest))
    return;

  me_StreamTools::CopyStreamTo(&InputStream, &OutputStream);
}

/*
  Compare for data equality

  We do not provide additional checks for intersection.

  These two segments will be considered equal:

    ~~~
    ABABA
      ~~~
*/
TBool me_WorkmemTools::AreEqual(
  TAddressSegment A_Seg,
  TAddressSegment B_Seg
)
{
  me_WorkMemory::TInputStream A_Stream;
  me_WorkMemory::TInputStream B_Stream;

  if (!A_Stream.Init(A_Seg))
    return false;

  if (!B_Stream.Init(B_Seg))
    return false;

  return me_StreamTools::StreamsAreEqual(&A_Stream, &B_Stream);
}

/*
  Reserve block of memory

  Zeroes data after allocation.
*/
TBool me_WorkmemTools::Reserve(
  TAddressSegment * MemSeg,
  TUint_2 Size
)
{
  TAddress MallocAddr;

  if (Size == 0)
    return false;

  MallocAddr = (TAddress) malloc(Size);

  if (MallocAddr == 0)
    return false;

  *MemSeg = { .Addr = MallocAddr, .Size = Size };

  ZeroMem(*MemSeg);

  return true;
}

/*
  Release block of memory

  Zeroes data before release.
*/
void me_WorkmemTools::Release(
  TAddressSegment * MemSeg
)
{
  if (!me_MemorySegment::IsValid(*MemSeg))
    return;

  ZeroMem(*MemSeg);

  free((void *) MemSeg->Addr);

  me_MemorySegment::Invalidate(MemSeg);
}

/*
  2024 # # # # # # # # # # #
  2025-08-24
  2025-08-26
  2025-08-29
*/
