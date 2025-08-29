// [me_WorkmemTools] test

/*
  Author: Martin Eden
  Last mod.: 2025-08-29
*/

#include <me_WorkmemTools.h>

#include <me_BaseTypes.h>
#include <me_Console.h>

void PrintWrappings(
  TAddressSegment Seg
)
{
  Console.Write("(");
  Console.Write("Addr");
  Console.Print(Seg.Addr);
  Console.Write("Size");
  Console.Print(Seg.Size);
  Console.Write(")");
  Console.EndLine();
}

void RunTest()
{
  using
    me_WorkmemTools::TManagedMemory;

  TManagedMemory Chunk;

  Console.Print("");

  Console.Print("This library manages heap span.");
  Console.Print("");
  Console.Print("Class manages loading data and resizing.");
  Console.Print("");
  Console.Print("In this example we'll use one instance with different");
  Console.Print("values. Idea is to demonstrate that memory span for data");
  Console.Print("is reused.");
  Console.Print("");

  PrintWrappings(Chunk.GetData());

  Chunk.LoadFrom("ABC");
  PrintWrappings(Chunk.GetData());

  Chunk.LoadFrom("12345");
  PrintWrappings(Chunk.GetData());

  Chunk.LoadFrom("ab");
  PrintWrappings(Chunk.GetData());
}

void setup()
{
  Console.Init();

  Console.Print("[me_WorkmemTools] test");
  Console.Indent();
  RunTest();
  Console.Unindent();
  Console.Print("[me_WorkmemTools] Done.");
}

void loop()
{
}

/*
  2024-06 # # # # # #
  2025-08-26
  2025-08-29
*/
