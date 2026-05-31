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

#include "library_book_borrowing_manager/presentation/controllers/main_menu_controller.h"

#include "library_book_borrowing_manager/presentation/controllers/borrow_records_controller.h"
#include "library_book_borrowing_manager/presentation/controllers/checkin_controller.h"
#include "library_book_borrowing_manager/presentation/controllers/checkout_controller.h"
#include "library_book_borrowing_manager/presentation/controllers/customers_controller.h"
#include "library_book_borrowing_manager/presentation/controllers/register_customer_controller.h"
#include "library_book_borrowing_manager/presentation/controllers/titles_controller.h"
#include "library_book_borrowing_manager/presentation/views/console_view.h"
#include "library_book_borrowing_manager/presentation/views/menu_view.h"

namespace library_book_borrowing_manager::presentation::controllers {

MainMenuController::MainMenuController(
    views::MenuView& menu_view,
    BorrowRecordsController& borrow_records_controller,
    CheckinController& checkin_controller,
    CheckoutController& checkout_controller,
    CustomersController& customers_controller,
    RegisterCustomerController& register_customer_controller,
    TitlesController& titles_controller)
    : menu_view_(menu_view),
      borrow_records_controller_(borrow_records_controller),
      checkin_controller_(checkin_controller),
      checkout_controller_(checkout_controller),
      customers_controller_(customers_controller),
      register_customer_controller_(register_customer_controller),
      titles_controller_(titles_controller) {}

void MainMenuController::Run() {
  while (true) {
    views::ClearTerminal();
    char user_input = menu_view_.PrintMainMenu();
    switch (user_input) {
      case '1':
        checkout_controller_.Run();
        break;
      case '2':
        checkin_controller_.Run();
        break;
      case '3':
        register_customer_controller_.Run();
        break;
      case '4':
        borrow_records_controller_.Run();
        break;
      case '5':
        titles_controller_.Run();
        break;
      case '6':
        customers_controller_.Run();
        break;
      default:
        return;
    }
  }
}

}  // namespace library_book_borrowing_manager::presentation::controllers
