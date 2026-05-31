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
// main_menu_controller.h
// -----------------------------------------------------------------------------
//
// This header file declares the JsonLibraryDataRepository class which
// implements the LibraryDataRepository interface. Intended to stores and
// retrieve all library data with JSON.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_CONTROLLERS_MAIN_MENU_CONTROllER_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_CONTROLLERS_MAIN_MENU_CONTROllER_H_

#include "library_book_borrowing_manager/presentation/controllers/borrow_records_controller.h"
#include "library_book_borrowing_manager/presentation/controllers/checkin_controller.h"
#include "library_book_borrowing_manager/presentation/controllers/checkout_controller.h"
#include "library_book_borrowing_manager/presentation/controllers/customers_controller.h"
#include "library_book_borrowing_manager/presentation/controllers/register_customer_controller.h"
#include "library_book_borrowing_manager/presentation/controllers/titles_controller.h"
#include "library_book_borrowing_manager/presentation/views/menu_view.h"

namespace library_book_borrowing_manager::presentation::controllers {

class MainMenuController {
 public:
  MainMenuController(views::MenuView& menu_view,
                     BorrowRecordsController& borrow_records_controller,
                     CheckinController& checkin_controller,
                     CheckoutController& checkout_controller,
                     CustomersController& users_controller,
                     RegisterCustomerController& register_user_controller,
                     TitlesController& titles_controller);

  void Run();

 private:
  views::MenuView& menu_view_;

  BorrowRecordsController& borrow_records_controller_;
  CheckinController& checkin_controller_;
  CheckoutController& checkout_controller_;
  CustomersController& customers_controller_;
  RegisterCustomerController& register_customer_controller_;
  TitlesController& titles_controller_;
};

}  // namespace library_book_borrowing_manager::presentation::controllers

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_CONTROLLERS_MAIN_MENU_CONTROllER_H_
