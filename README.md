# Sanitizers

(chatGPT) Nicht alle infos sind zertifiziert.

## Welche Sanitizer gibt’s (praktisch)?

| Kürzel | Findet… | Typische Flags / Hinweise | Combine | Suppoert (kurz) |
| - | - | - | - | - |
| **ASan** (Address) | Out-of-bounds, use-after-free/scope, double free, teils  | -fsanitize=address (+ -g -fno-omit-frame-pointer) | mit UBSan/LSan | Clang/GCC: Linux/macOS/Win; MSVC: ASan |
| **UBSan** (Undefined Behavior) | signed Integer-Overflow, Division durch 0, OOB, Misalignment, vptr-Fehler … | -fsanitize=undefined (häufig mit ASan/TSan kombinieren) | mit ASan/TSan | Clang/GCC/MSVC |
| **TSan** (Thread) | Data Races, fehlerhafte Synchronisation | -fsanitize=thread (nicht mit ASan kombinierbar) | **nicht** mit ASan | Clang: Linux/macOS |
| **MSan** (Memory) | Nutzung uninitialisierten Speichers | -fsanitize=memory (allein nutzen; braucht instrumentierte Libs) | mit ASan | v. a. Linux (Clang) |
| **LSan** (Leak) | Memory Leaks | -fsanitize=leak oder via ASan integriert (detect_leaks=1) | allein | Clang: Linux, alle Deps instrumentiert |
| **HWASan** | ASan-ähnlich mit Pointer-Tags (AArch64/Android), geringerer Overhead | -fsanitize=hwaddress | allein | Clang: AArch64/Android |
| **DFSan** (DataFlow/Taint) | Taint-Tracking / Datenflussanalyse | -fsanitize=dataflow (fortgeschritten) | allein | Clang (fortgeschritten) |

## Spezialfälle / verwandt

- **KASAN/KMSAN/KCSAN:** Kernel-Varianten (Linux-Kernel).
- **Control-Flow Integrity (CFI):** keine „Sanitizer“-Flag, aber Sicherheits-Instrumentierung (-fsanitize=cfi* mit LTO).
- **Scudo:** gehärteter Allocator (kein Sanitizer, kann mit ASan/ohne genutzt werden).

## Empfohlene CI-Kombos

- **ASan + UBSan (+ LSan)** für die meisten User-Space-Projekte.
- **TSan + UBSan** für nebenläufigen Code (statt ASan).
- **MSan** separat, wenn uninitialisierte Nutzung ein Thema ist.

Wenn du willst, passe ich dein CMake so an, dass du per Option zwischen {ASan+UBSan+LSan} und {TSan+UBSan} umschalten kannst – inkl. passenden ENVIRONMENT- und FAIL_REGULAR_EXPRESSION-Settings für CTest.
