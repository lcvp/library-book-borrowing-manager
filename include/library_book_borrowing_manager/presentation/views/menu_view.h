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
// menu_view.h
// -----------------------------------------------------------------------------
//
// This header file defines the UserInterface class for Library Book Borrowing
// Manager for displaying menu options and handling inputs.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_VIEWS_MENU_VIEW_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_VIEWS_MENU_VIEW_H_

namespace library_book_borrowing_manager::presentation::views {

class MenuView {
 public:
  char PrintMainMenu() const;
};

}  // namespace library_book_borrowing_manager::presentation::views

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_VIEWS_MENU_VIEW_H_
