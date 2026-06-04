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

#include "library_book_borrowing_manager/presentation/controllers/checkin_controller.h"

#include <vector>

#include "library_book_borrowing_manager/domain/borrow_record.h"
#include "library_book_borrowing_manager/domain/customer.h"
#include "library_book_borrowing_manager/presentation/views/checkin_view.h"
#include "library_book_borrowing_manager/presentation/views/console_view.h"
#include "library_book_borrowing_manager/service/library_manager.h"

namespace library_book_borrowing_manager::presentation::controllers {

CheckinController::CheckinController(service::LibraryManager& library_manager,
                                     views::CheckinView& checkin_view)
    : library_manager_(library_manager), checkin_view_(checkin_view) {}

void CheckinController::Run() {
  try {
    views::ClearTerminal();

    std::vector<domain::Customer> customers =
        library_manager_.GetCustomerList();

    std::string selected_customer_id =
        checkin_view_.PrintCustomerList(customers);

    domain::Customer customer =
        library_manager_.GetCustomerById(selected_customer_id);

    std::vector<std::string> selected_borrow_record_ids;

    while (true) {
      views::ClearTerminal();

      std::string selected_borrow_record_id =
          checkin_view_.PrintBorrowRecordList(
              GetUnreturnedBorrowRecords(customer.borrow_records()),
              selected_customer_id, selected_borrow_record_ids);

      selected_borrow_record_ids.push_back(selected_borrow_record_id);

      if (!views::PromptForConfirmation("Check in more items? (y/n): ")) {
        break;
      }
    }

    double total_owed_fee = library_manager_.CheckinItems(
        selected_customer_id, selected_borrow_record_ids);

    checkin_view_.PrintTotalOwedFee(total_owed_fee);

    views::PrintSuccess("Successfully checked in items.");
  } catch (const std::exception& exception) {
    views::PrintError(exception.what());
  }

  views::WaitForInput("Press Enter to continue");
}

std::vector<domain::BorrowRecord> CheckinController::GetUnreturnedBorrowRecords(
    std::vector<domain::BorrowRecord> borrow_records) const {
  std::vector<domain::BorrowRecord> unreturned_borrow_records;

  for (const domain::BorrowRecord& borrow_record : borrow_records) {
    if (!borrow_record.return_date().has_value()) {
      unreturned_borrow_records.push_back(borrow_record);
    }
  }

  return unreturned_borrow_records;
}

}  // namespace library_book_borrowing_manager::presentation::controllers
