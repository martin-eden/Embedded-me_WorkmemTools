// Manager for memory segment in dynamic memory

/*
  Author: Martin Eden
  Last mod.: 2025-08-29
*/

#include <me_WorkmemTools.h>

#include <me_BaseTypes.h>

using namespace me_WorkmemTools;

/*
  Destructor

  Release memory.
*/
TManagedMemory::~TManagedMemory()
{
  Release();
}

/*
  Return our data segment

  We're not working with data at span. We're managing span.
  Here we're returning data span for processing. We hope they
  won't call free() on it.
*/
TAddressSegment TManagedMemory::GetData()
{
  return DataSeg;
}

/*
  Return data segment size
*/
TUint_2 TManagedMemory::GetSize()
{
  return DataSeg.Size;
}

/*
  Grow or shrink data segment

  In case of shrink, data is truncated. In case of grow,
  it's filled with zero bytes.

  If there's no memory, we'll return false.
*/
TBool TManagedMemory::ResizeTo(
  TUint_2 NewSize
)
{
  TAddressSegment NewSeg;

  if (!me_WorkmemTools::Reserve(&NewSeg, NewSize))
    return false;

  me_WorkmemTools::CopyMemTo(NewSeg, DataSeg);

  me_WorkmemTools::Release(&DataSeg);

  DataSeg = NewSeg;

  return true;
}

/*
  Free data segment memory

  We're just resizing to zero.
*/
void TManagedMemory::Release()
{
  ResizeTo(0);
}

/*
  Load from memory segment
*/
TBool TManagedMemory::LoadFrom(
  TAddressSegment Src
)
{
  if (!ResizeTo(Src.Size))
    return false;

  me_WorkmemTools::CopyMemTo(DataSeg, Src);

  return true;
}

/*
  Load from ASCIIZ
*/
TBool TManagedMemory::LoadFrom(
  const TAsciiz Asciiz
)
{
  // Cast ASCIIZ to memseg and load
  return LoadFrom(FromAsciiz(Asciiz));
}

/*
  Load from our specie
*/
TBool TManagedMemory::LoadFrom(
  TManagedMemory * Src
)
{
  // Get data seg and load
  return LoadFrom(Src->GetData());
}

/*
  2024 # # # # # # #
  2025-08-29
*/
