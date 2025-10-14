// Utility functions for RAM memory segment

/*
  Author: Martin Eden
  Last mod.: 2025-10-14
*/

#include <me_WorkmemTools.h>

#include <me_BaseTypes.h>

#include <me_AddrsegTools.h>
#include <me_StreamTools.h>
#include <me_StreamsCollection.h>

#include <stdlib.h> // malloc(), free()

using namespace me_WorkmemTools;

/*
  Represent ASCII structure as memory segment

  Zero byte is not counted.
*/
TAddressSegment me_WorkmemTools::FromAsciiz(
  TAsciiz Asciiz
)
{
  /*
    We'll create address segment from current address till
    imaginary memory end. We'll create read stream on that
    segment. We'll read from that stream and count units.
    We'll fail when read fails or unit read is zero (aka NUL).

    We'll set .Size to number of units read.
  */

  me_StreamsCollection::TWorkmemInputStream InputStream;
  TAddressSegment AddrSeg;
  TSize NumUnitsRead;
  TUnit Unit;

  AddrSeg.Addr = (TAddress) Asciiz;
  AddrSeg.Size = TSize_Max - AddrSeg.Addr + 1;

  InputStream.Init(AddrSeg);

  NumUnitsRead = 0;

  while (InputStream.Read(&Unit))
  {
    if (Unit == 0)
      break;

    NumUnitsRead = NumUnitsRead + 1;
  }

  AddrSeg.Size = NumUnitsRead;

  return AddrSeg;
}

/*
  Fill memory span with zero byte
*/
void me_WorkmemTools::ZeroMem(
  TAddressSegment MemSeg
)
{
  me_StreamTools::TZeroesInputStream ZeroesInputStream;
  me_StreamsCollection::TWorkmemOutputStream OutputStream;

  if (!OutputStream.Init(MemSeg))
    return;

  me_StreamTools::SaveStreamTo(&ZeroesInputStream, &OutputStream);
}

/*
  Copy data to another segment
*/
void me_WorkmemTools::CopyMemTo(
  TAddressSegment Dest,
  TAddressSegment Src
)
{
  me_StreamsCollection::TWorkmemInputStream InputStream;
  me_StreamsCollection::TWorkmemOutputStream OutputStream;

  if (!InputStream.Init(Src))
    return;

  if (!OutputStream.Init(Dest))
    return;

  me_StreamTools::SaveStreamTo(&InputStream, &OutputStream);
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
  me_StreamsCollection::TWorkmemInputStream A_Stream;
  me_StreamsCollection::TWorkmemInputStream B_Stream;

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
  if (!me_AddrsegTools::IsValid(*MemSeg))
    return;

  ZeroMem(*MemSeg);

  free((void *) MemSeg->Addr);

  me_AddrsegTools::Invalidate(MemSeg);
}

/*
  2024 # # # # # # # # # # #
  2025-08-24
  2025-08-26
  2025-08-29
  2025-08-30
*/
