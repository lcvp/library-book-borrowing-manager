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
// user_interface.h
// -----------------------------------------------------------------------------
//
// This header file defines the UserInterface class for Library Book Borrowing
// Manager for displaying menu options and handling inputs.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_USER_INTERFACE_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_USER_INTERFACE_H_

#include "library_book_borrowing_manager/service/library_manager.h"

namespace library_book_borrowing_manager::presentation {

class UserInterface {
 public:
  explicit UserInterface(service::LibraryManager* manager);

  service::LibraryManager* manager() const;

  void Start() const;

 private:
  void PrintMainMenu() const;
  void PrintCheckoutItemsMenu() const;
  void PrintInputItemsMenu() const;
  void PrintCheckinItemsMenu() const;
  void PrintRegisterUserMenu() const;

  service::LibraryManager* manager_;
};

}  // namespace library_book_borrowing_manager::presentation

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_USER_INTERFACE_H_
