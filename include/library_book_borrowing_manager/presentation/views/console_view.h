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
//
// -----------------------------------------------------------------------------
// console_view.h
// -----------------------------------------------------------------------------
//
// This header file defines a collection of user interface helper methods.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_VIEWS_CONSOLE_VIEW_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_VIEWS_CONSOLE_VIEW_H_

#include <map>
#include <string>
#include <vector>

namespace library_book_borrowing_manager::presentation::views {

void ClearTerminal();

std::string PromptForString(std::string prompt_message);

int PromptForInt(std::string prompt_message);

bool PromptForConfirmation(std::string prompt_message);

void PrintHeader(std::string title);

void PrintError(std::string error_message);

void PrintSuccess(std::string success_message);

void PrintDivider();

void PrintList(std::vector<std::string> entries);

void PrintList(std::map<std::string, std::string> entries);

void PrintList(std::map<int, std::string> entries);

void WaitForInput(std::string message);

int GetTerminalLength();

}  // namespace library_book_borrowing_manager::presentation::views

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_VIEWS_CONSOLE_VIEW_H_
