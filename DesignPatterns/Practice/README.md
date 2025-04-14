# Design Pattern Practices

## PointerHandler

```shell
$ g++ --std=gnu++20 -g ./PointerHandler.cc -o ./PointerHandler
$ valgrind --leak-check=full ./PointerHandler
==479== Memcheck, a memory error detector
==479== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==479== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==479== Command: ./PointerHandler
==479==
Nullptr, Segmentation fault!==479==
==479== HEAP SUMMARY:
==479==     in use at exit: 0 bytes in 0 blocks
==479==   total heap usage: 9 allocs, 9 frees, 74,021 bytes allocated
==479==
==479== All heap blocks were freed -- no leaks are possible
==479==
==479== For lists of detected and suppressed errors, rerun with: -s
==479== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
