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

#include "library_book_borrowing_manager/presentation/controllers/borrow_records_controller.h"

#include "library_book_borrowing_manager/presentation/views/borrow_records_view.h"
#include "library_book_borrowing_manager/presentation/views/console_view.h"
#include "library_book_borrowing_manager/service/library_manager.h"

namespace library_book_borrowing_manager::presentation::controllers {

BorrowRecordsController::BorrowRecordsController(
    service::LibraryManager& library_manager,
    views::BorrowRecordsView& borrow_records_view)
    : library_manager_(library_manager),
      borrow_records_view_(borrow_records_view) {}

void BorrowRecordsController::Run() {
  try {
    views::ClearTerminal();
    std::vector<domain::BorrowRecord> borrow_records_list =
        library_manager_.GetBorrowRecordList();

    borrow_records_view_.PrintBorrowRecordList(borrow_records_list);
  } catch (const std::exception& exception) {
    views::PrintError(exception.what());
  }
  views::WaitForInput("Press Enter to continue");
}

}  // namespace library_book_borrowing_manager::presentation::controllers
