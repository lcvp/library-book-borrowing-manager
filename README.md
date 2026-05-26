# Library Book Borrowing Manager

>"You need a book, you talk to me. Otherwise you're going to find yourself in a lot of pain."  
— **Urag gro-Shub**, *The Elder Scrolls V: Skyrim*

**Library Book Borrowing Manager** is a group project for CS-256.

## Getting Started

### Requirements  
- **C++23** or higher (*GCC 14+, Clang 18+, or MSVC 2022 17.14+*)
- [CMake][cmake-download-link] (*version 4.3 or higher*)
- An internet connection (*for external dependencies*)

### How to Run
1. **Navigate** to the project root directory
2. **Build** the project  
   ```bash
   cmake -S . -B build
   cmake --build build --config Release
   ```
3. **Run** the executable  
   On **Linux**:
   ```bash
   ./build/LibraryBookBorrowingManager
   ```

   On **Windows**:
   ```powershell
   .\build\Release\LibraryBookBorrowingManager.exe
   ```

## License
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the [GNU General Public License][gpl-v3] for more details.

## Acknowledgements
- This project uses [nlohmann/json][nlohmann-json], licensed under the [MIT License][third-party-notices]. 


[cmake-download-link]: https://cmake.org/download/
[gpl-v3]: ./LICENSE
[nlohmann-json]: https://github.com/nlohmann/json
[third-party-notices]: ./THIRD_PARTY_NOTICES.md
