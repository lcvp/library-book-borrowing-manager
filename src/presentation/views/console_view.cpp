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

#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace library_book_borrowing_manager::presentation::views {

void ClearTerminal() { std::cout << "\033[2J\033[H" << std::flush; }

std::string PromptForString(std::string prompt_message) {
  std::string input = "";
  PrintWrapped(prompt_message);
  std::getline(std::cin, input);
  return input;
}

int PromptForInt(std::string prompt_message) {
  std::string input = "";
  PrintWrapped(prompt_message);
  std::getline(std::cin, input);

  return std::stoi(input);
}

bool PromptForConfirmation(std::string prompt_message) {
  std::string input = "";
  PrintWrapped(prompt_message);
  std::getline(std::cin, input);

  bool is_confirmed = ((input == "y") || (input == "Y"));

  return is_confirmed;
}

void PrintHeader(std::string title) {
  PrintDivider();
  PrintWrapped("\033[1m" + title + "\033[0m");
  PrintDivider();
}

void PrintError(std::string error_message) {
  PrintWrapped("\033[31m[ERROR]\033[0m " + error_message);
}

void PrintSuccess(std::string success_message) {
  PrintWrapped("\033[32m[SUCCESS]\033[0m " + success_message);
}

void PrintDivider() {
  int length = GetTerminalLength();
  PrintWrapped(std::string(length, '-'));
}

void PrintList(std::vector<std::string> entries) {
  for (std::string entry : entries) {
    PrintWrapped(entry);
  }
}

void PrintList(std::map<std::string, std::string> entries) {
  for (const auto& entry : entries) {
    PrintWrapped(entry.first + ": " + entry.second);
  }
}

void PrintList(std::map<int, std::string> entries) {
  for (const auto& entry : entries) {
    PrintWrapped(std::to_string(entry.first) + ": " + entry.second);
  }
}

void WaitForInput(std::string message) {
  PrintWrapped(message);
  std::string input;
  std::getline(std::cin, input);
}

int GetTerminalLength() { return 80; }

void PrintWrapped(std::string text) {
  int width = GetTerminalLength();

  for (int i = 0; i < static_cast<int>(text.length()); i += width) {
    std::cout << text.substr(i, width) << "\n";
  }
}

std::string TimePointToString(
    std::chrono::system_clock::time_point time_point) {
  std::time_t time = std::chrono::system_clock::to_time_t(time_point);

  std::ostringstream oss;
  oss << std::put_time(std::localtime(&time), "%d/%m/%Y");

  return oss.str();
}

std::chrono::system_clock::time_point StringToTimePoint(
    std::string date_month_year) {
  std::tm date_time_components{};
  std::istringstream date_input_stream(date_month_year);

  date_input_stream >> std::get_time(&date_time_components, "%d/%m/%Y");

  if (date_input_stream.fail()) {
    throw std::invalid_argument("Invalid date format. Use DD/MM/YYYY");
  }

  std::time_t calendar_time = std::mktime(&date_time_components);

  return std::chrono::system_clock::from_time_t(calendar_time);
}

}  // namespace library_book_borrowing_manager::presentation::views
