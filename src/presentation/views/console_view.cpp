// This program is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see <https://www.gnu.org/licenses/>.

#include "library_book_borrowing_manager/presentation/views/console_view.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace library_book_borrowing_manager::presentation::views {

void ClearTerminal() { std::cout << "\033[2J\033[H" << std::flush; }

std::string PromptForString(std::string prompt_message) {
  std::string input = "";
  std::cout << prompt_message;
  std::getline(std::cin, input);
  return input;
}

int PromptForInt(std::string prompt_message) {
  std::string input = "";
  std::cout << prompt_message;
  std::getline(std::cin, input);

  return std::stoi(input);
}

bool PromptForConfirmation(std::string prompt_message) {
  std::string input = "";
  std::cout << prompt_message;
  std::getline(std::cin, input);

  bool is_confirmed = ((input == "y") || (input == "Y"));

  return is_confirmed;
}

void PrintHeader(std::string title) {
  PrintDivider();
  std::cout << "\033[1m" << title << "\033[0m\n";
  PrintDivider();
}

void PrintError(std::string error_message) {
  std::cerr << "\033[31m[ERROR]\033[0m " << error_message << "\n";
}

void PrintSuccess(std::string success_message) {
  std::cout << "\033[32m[SUCCESS]\033[0m " << success_message << "\n";
}

void PrintDivider() {
  int length = GetTerminalLength();
  std::cout << std::string(length, '-') << "\n";
}

void PrintList(std::vector<std::string> entries) {
  for (std::string entry : entries) {
    std::cout << entry << std::endl;
  }
}

void PrintList(std::map<std::string, std::string> entries) {
  for (const auto& entry : entries) {
    std::cout << entry.first << ": " << entry.second << "\n";
  }
}

void PrintList(std::map<int, std::string> entries) {
  for (const auto& entry : entries) {
    std::cout << entry.first << ": " << entry.second << "\n";
  }
}

void WaitForInput(std::string message) {
  std::cout << message;
  std::string input;
  std::getline(std::cin, input);
}

int GetTerminalLength() { return 80; }

}  // namespace library_book_borrowing_manager::presentation::views
