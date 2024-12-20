// [me_ManagedMemory] test/demo

/*
  Author: Martin Eden
  Last mod.: 2024-12-20
*/

#include <me_ManagedMemory.h>

#include <me_BaseTypes.h>
#include <me_Uart.h>
#include <me_Console.h>
#include <me_MemorySegment.h>

void setup()
{
  me_Uart::Init(me_Uart::Speed_115k_Bps);

  Console.Print("[me_ManagedMemory] Okay, we are here.");
  Console.Indent();
  RunTest();
  Console.Unindent();
  Console.Print("[me_ManagedMemory] Done.");
}

void loop()
{
}

// --

void PrintWrappings(
  me_MemorySegment::TMemorySegment Seg
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
    me_ManagedMemory::TManagedMemory;

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

/*
  2024-06 #
  2024-07 #
  2024-10 # # #
  2024-12-20
*/
