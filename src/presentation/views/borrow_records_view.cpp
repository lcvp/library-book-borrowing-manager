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

#include "library_book_borrowing_manager/presentation/views/borrow_records_view.h"

#include <string>

#include "library_book_borrowing_manager/presentation/views/console_view.h"

namespace library_book_borrowing_manager::presentation::views {

void BorrowRecordsView::PrintBorrowRecordList(
    const std::vector<domain::BorrowRecord>& borrow_records) const {
  PrintHeader("Borrow Records");

  std::vector<std::string> borrow_record_list =
      BorrowRecordListToString(borrow_records);

  PrintList(borrow_record_list);
}

std::string BorrowRecordsView::BorrowRecordToString(
    domain::BorrowRecord borrow_record) const {
  std::string string_borrow_record;
  string_borrow_record += "Borrow Record ID: " + borrow_record.id();
  string_borrow_record += " | ";
  string_borrow_record += "Item ID: " + borrow_record.item()->id();
  string_borrow_record += " | ";
  string_borrow_record += "Title: " + borrow_record.item()->title()->name();
  string_borrow_record +=
      ", Start Date: " + TimePointToString(borrow_record.start_date());
  string_borrow_record +=
      ", Due Date: " + TimePointToString(borrow_record.due_date());

  if (borrow_record.return_date().has_value()) {
    string_borrow_record +=
        ", Return Date: " +
        TimePointToString(borrow_record.return_date().value());
  } else {
    string_borrow_record += ", Return Date: Not Returned";
  }

  return string_borrow_record;
}

std::vector<std::string> BorrowRecordsView::BorrowRecordListToString(
    std::vector<domain::BorrowRecord> borrow_record_list) const {
  std::vector<std::string> string_borrow_record_list;
  for (domain::BorrowRecord borrow_record : borrow_record_list) {
    string_borrow_record_list.push_back(BorrowRecordToString(borrow_record));
  }
  return string_borrow_record_list;
}

}  // namespace library_book_borrowing_manager::presentation::views
