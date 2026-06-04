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
// borrow_records_view.h
// -----------------------------------------------------------------------------
//
// This header file declares the BorrowRecordsView class, which is in charge of
// rendering the menus related to BorrowRecords.

#include "library_book_borrowing_manager/domain/borrow_record.h"

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_VIEWS_BORROW_RECORDS_VIEWS_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_VIEWS_BORROW_RECORDS_VIEWS_H_

namespace library_book_borrowing_manager::presentation::views {

class BorrowRecordsView {
 public:
  char PrintBorrowRecordsOptions() const;

  void PrintBorrowRecordList(
      const std::vector<domain::BorrowRecord>& borrow_records) const;

  std::string BorrowRecordToString(domain::BorrowRecord) const;
  std::string ItemToString(domain::Item item) const;

  std::vector<std::string> BorrowRecordListToString(
      std::vector<domain::BorrowRecord> borrow_record_list) const;
  std::vector<std::string> ItemListToString(
      std::vector<domain::Item> item_list) const;
};

}  // namespace library_book_borrowing_manager::presentation::views

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_VIEWS_BORROW_RECORDS_VIEWS_H_
