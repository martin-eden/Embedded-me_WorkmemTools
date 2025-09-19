// [me_WorkmemTools] test

/*
  Author: Martin Eden
  Last mod.: 2025-09-19
*/

#include <me_WorkmemTools.h>

#include <me_BaseTypes.h>
#include <me_Console.h>
#include <me_DebugPrints.h>

/*
  Print contents using byte iterator
*/
void PrintByteContents(
  TAddressSegment AddrSeg
)
{
  me_DebugPrints::PrintMemsegData("Byte-Contents", AddrSeg);
}

void PrintRawContents(
  TAddressSegment AddrSeg
)
{
  Console.Write("Raw-Contents (");
  Console.Write(AddrSeg);
  Console.Write(")");

  Console.EndLine();
}

void PrintSegmentDetails(
  TAsciiz Header,
  TAddressSegment AddrSeg
)
{
  Console.Print(Header);

  Console.Indent();

  me_DebugPrints::PrintAddrseg("Segment", AddrSeg);
  PrintRawContents(AddrSeg);
  PrintByteContents(AddrSeg);

  Console.Unindent();
}

void TestAsciiz()
{
  TAddressSegment AddrSeg;

  /*
    FromAsciiz(): Treat ASCIIZ as memory segment

    Returned segment does not include zero byte.
  */
  AddrSeg = me_WorkmemTools::FromAsciiz("ABC");

  PrintSegmentDetails("FromAsciiz", AddrSeg);
}

void TestMemoryAllocator()
{
  TAddressSegment SourceData = me_WorkmemTools::FromAsciiz("DATA");
  TAddressSegment DestData;

  Console.Print("( Reserve CopyMemTo Release )");
  Console.Indent();

  /*
    Reserve(): Allocate memory and zero data
  */
  if (!me_WorkmemTools::Reserve(&DestData, SourceData.Size))
  {
    Console.Print("No memory for temporary data");
    return;
  }

  PrintSegmentDetails("Reserve", DestData);

  /*
    CopyMemTo(): Copy data to another segment
  */
  me_WorkmemTools::CopyMemTo(DestData, SourceData);

  PrintSegmentDetails("CopyMemTo", DestData);

  /*
    Release(): Deallocate memory and zero data
  */
  me_WorkmemTools::Release(&DestData);

  PrintSegmentDetails("Release", DestData);

  Console.Unindent();
}

void TestManagedMemory()
{
  me_WorkmemTools::TManagedMemory Chunk;

  Console.Print("");

  Console.Print("Testing data chunk in heap");
  Console.Print("");
  Console.Print("Idea is to demonstrate that data address is reused.");
  Console.Print("");

  PrintSegmentDetails("Current data", Chunk.GetData());

  Chunk.LoadFrom("ABC");
  PrintSegmentDetails("Current data", Chunk.GetData());

  Chunk.LoadFrom("12345");
  PrintSegmentDetails("Current data", Chunk.GetData());

  Chunk.LoadFrom("ab");
  PrintSegmentDetails("Current data", Chunk.GetData());
}

void setup()
{
  Console.Init();

  Console.Print("( [me_WorkmemTools] test");
  Console.Indent();

  TestAsciiz();
  TestMemoryAllocator();
  TestManagedMemory();

  Console.Unindent();
  Console.Print(") Done");
}

void loop()
{
}

/*
  2024-06 # # # # # #
  2025-08-26
  2025-08-29
  2025-09-19
*/
