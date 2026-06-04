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
// checkin_controller.h
// -----------------------------------------------------------------------------
//
// This header file declares the CheckinController class for processing user
// input in the Checkin Items menu.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_CONTROLLERS_CHECKIN_CONTROLLER_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_CONTROLLERS_CHECKIN_CONTROLLER_H_

#include <vector>

#include "library_book_borrowing_manager/domain/borrow_record.h"
#include "library_book_borrowing_manager/presentation/views/checkin_view.h"
#include "library_book_borrowing_manager/service/library_manager.h"

namespace library_book_borrowing_manager::presentation::controllers {

class CheckinController {
 public:
  CheckinController(service::LibraryManager& library_manager,
                    views::CheckinView& checkin_view);

  void Run();
  std::vector<domain::BorrowRecord> GetUnreturnedBorrowRecords(
      std::vector<domain::BorrowRecord> borrow_records) const;

 private:
  service::LibraryManager& library_manager_;

  views::CheckinView& checkin_view_;
};

}  // namespace library_book_borrowing_manager::presentation::controllers

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_CONTROLLERS_CHECKIN_CONTROLLER_H_
