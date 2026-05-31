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

#include "library_book_borrowing_manager/presentation/views/menu_view.h"

#include "library_book_borrowing_manager/presentation/views/console_view.h"

namespace library_book_borrowing_manager::presentation::views {

char MenuView::PrintMainMenu() const {
  PrintHeader("Library Book Borrowing Manager");
  std::map<std::string, std::string> options = {
      {"1", "Checkout Items"},          {"2", "Checkin Items"},
      {"3", "Register Customer"},       {"4", "Manage Borrow Records"},
      {"5", "Manage Titles"},           {"6", "Manage Customer"},
      {"Any other key", "Exit Program"}};
  PrintList(options);

  PrintDivider();
  char user_input = PromptForString("Enter: ")[0];
  return user_input;
}

}  // namespace library_book_borrowing_manager::presentation::views
