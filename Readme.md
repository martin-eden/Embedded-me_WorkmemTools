# What

(2024, 2025 WIP)

Tools to work with data in RAM.


## Sample output

```
[me_WorkmemTools] test

  This library manages heap span.

  Class manages loading data and resizing.

  In this example we'll use one instance with different
  values. Idea is to demonstrate that memory span for data
  is reused.

  (Addr 00000 Size 00000 )
  (Addr 00586 Size 00003 )
  (Addr 00591 Size 00005 )
  (Addr 00586 Size 00002 )
[me_WorkmemTools] Done.

```

## Code

* [Interface][Interface]
* [Implementation][Implementation]
* [Example][Example]


## Requirements

  * arduino-cli
  * bash


## Install/remove

Easy way is to clone [GetLibs][GetLibs] repo and run it's code.


## Compile

Zero-warnings compilation:

```bash
arduino-cli compile --fqbn arduino:avr:uno --quiet --warnings all . --build-property compiler.cpp.extra_flags="-std=c++1z"
```

## See also

* [My other embedded C++ libraries][Embedded]
* [My other repositories][Repos]


[Interface]: src/me_WorkmemTools.h
[Implementation]: src/
[Example]: examples/me_WorkmemTools/me_WorkmemTools.ino

[GetLibs]: https://github.com/martin-eden/Embedded-Framework-GetLibs

[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
