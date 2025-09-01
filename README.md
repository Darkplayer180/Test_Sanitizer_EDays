# Sanitizers

## Welche Sanitizer gibt’s (praktisch)?

| Kürzel | Findet… | Typische Flags / Hinweise |
| - | - | - |
| **ASan** (Address) | Out-of-bounds, use-after-free/scope, double free, teils  | -fsanitize=address (+ -g -fno-omit-frame-pointer) |
| **UBSan** (Undefined Behavior) | signed Integer-Overflow, Division durch 0, OOB, Misalignment, vptr-Fehler … | -fsanitize=undefined (häufig mit ASan/TSan kombinieren) |
| **TSan** (Thread) | Data Races, fehlerhafte Synchronisation | -fsanitize=thread (nicht mit ASan kombinierbar) |
| **MSan** (Memory) | Nutzung uninitialisierten Speichers | -fsanitize=memory (allein nutzen; braucht instrumentierte Libs) |
| **LSan** (Leak) | Memory Leaks | -fsanitize=leak oder via ASan integriert (detect_leaks=1) |
| **HWASan** | ASan-ähnlich mit Pointer-Tags (AArch64/Android), geringerer Overhead | -fsanitize=hwaddress |
| **DFSan** (DataFlow/Taint) | Taint-Tracking / Datenflussanalyse | -fsanitize=dataflow (fortgeschritten) |

## Spezialfälle / verwandt

- **KASAN/KMSAN/KCSAN:** Kernel-Varianten (Linux-Kernel).
- **Control-Flow Integrity (CFI):** keine „Sanitizer“-Flag, aber Sicherheits-Instrumentierung (-fsanitize=cfi* mit LTO).
- **Scudo:** gehärteter Allocator (kein Sanitizer, kann mit ASan/ohne genutzt werden).

## Empfohlene CI-Kombos

- **ASan + UBSan (+ LSan)** für die meisten User-Space-Projekte.
- **TSan + UBSan** für nebenläufigen Code (statt ASan).
- **MSan** separat, wenn uninitialisierte Nutzung ein Thema ist.

Wenn du willst, passe ich dein CMake so an, dass du per Option zwischen {ASan+UBSan+LSan} und {TSan+UBSan} umschalten kannst – inkl. passenden ENVIRONMENT- und FAIL_REGULAR_EXPRESSION-Settings für CTest.
