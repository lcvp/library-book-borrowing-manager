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

#include "library_book_borrowing_manager/presentation/user_interface.h"

#include <map>
#include <string>

#include "library_book_borrowing_manager/presentation/user_interface_utils.h"
#include "library_book_borrowing_manager/service/library_manager.h"

namespace library_book_borrowing_manager::presentation {

UserInterface::UserInterface(service::LibraryManager* manager)
    : manager_(manager) {};

service::LibraryManager* UserInterface::manager() const { return manager_; }

void UserInterface::Start() const { PrintMainMenu(); }

void UserInterface::PrintMainMenu() const {
  PrintHeader("Library Book Borrowing Manager");
  std::map<std::string, std::string> options = {
      {"1", "Checkout Items"}, {"2", "Checkin Items"},
      {"3", "Register User"},  {"4", "Manage Borrow Records"},
      {"5", "Manage Titles"},  {"6", "Manage Users"},
      {"q", "Exit Program"}};
  PrintList(options);
  std::string user_input = PromptForString("Enter: ");
}

}  // namespace library_book_borrowing_manager::presentation
