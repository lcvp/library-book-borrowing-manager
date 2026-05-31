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
// main.cpp
// -----------------------------------------------------------------------------
//
// This file declares the main function of the Library Book Borrowing Manager
// program.

#include <string>

#include "library_book_borrowing_manager/data/json_library_data_repository.h"
#include "library_book_borrowing_manager/presentation/controllers/borrow_records_controller.h"
#include "library_book_borrowing_manager/presentation/controllers/checkin_controller.h"
#include "library_book_borrowing_manager/presentation/controllers/checkout_controller.h"
#include "library_book_borrowing_manager/presentation/controllers/customers_controller.h"
#include "library_book_borrowing_manager/presentation/controllers/main_menu_controller.h"
#include "library_book_borrowing_manager/presentation/controllers/register_customer_controller.h"
#include "library_book_borrowing_manager/presentation/controllers/titles_controller.h"
#include "library_book_borrowing_manager/presentation/views/borrow_records_view.h"
#include "library_book_borrowing_manager/presentation/views/checkin_view.h"
#include "library_book_borrowing_manager/presentation/views/checkout_view.h"
#include "library_book_borrowing_manager/presentation/views/customers_view.h"
#include "library_book_borrowing_manager/presentation/views/menu_view.h"
#include "library_book_borrowing_manager/presentation/views/titles_view.h"
#include "library_book_borrowing_manager/service/library_manager.h"

int main() {
  const std::string kSaveFilePath = "library_data.json";

  library_book_borrowing_manager::data::JsonLibraryDataRepository library_data(
      kSaveFilePath);

  library_book_borrowing_manager::service::LibraryManager library_manager(
      &library_data);

  // Initialize the views
  library_book_borrowing_manager::presentation::views::BorrowRecordsView
      borrow_records_view;
  library_book_borrowing_manager::presentation::views::CheckinView checkin_view;
  library_book_borrowing_manager::presentation::views::CheckoutView
      checkout_view;
  library_book_borrowing_manager::presentation::views::CustomersView
      customers_view;
  library_book_borrowing_manager::presentation::views::MenuView menu_view;
  library_book_borrowing_manager::presentation::views::TitlesView titles_view;

  // Initialize the controllers
  library_book_borrowing_manager::presentation::controllers::
      BorrowRecordsController borrow_records_controller(library_manager,
                                                        borrow_records_view);
  library_book_borrowing_manager::presentation::controllers::CheckinController
      checkin_controller(library_manager, checkin_view);
  library_book_borrowing_manager::presentation::controllers::CheckoutController
      checkout_controller(library_manager, checkout_view);
  library_book_borrowing_manager::presentation::controllers::CustomersController
      customers_controller(library_manager, customers_view);
  library_book_borrowing_manager::presentation::controllers::
      RegisterCustomerController register_customer_controller(library_manager,
                                                              customers_view);
  library_book_borrowing_manager::presentation::controllers::TitlesController
      titles_controller(library_manager, titles_view);

  // Initialize main menu controller
  library_book_borrowing_manager::presentation::controllers::MainMenuController
      main_menu_controller(menu_view, borrow_records_controller,
                           checkin_controller, checkout_controller,
                           customers_controller, register_customer_controller,
                           titles_controller);

  main_menu_controller.Run();

  return 0;
}
