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
// checkin_view.h
// -----------------------------------------------------------------------------
//
// This header file declares the CheckinView class for rendering menus related
// to the item checkin process.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_VIEWS_CHECKIN_VIEW_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_VIEWS_CHECKIN_VIEW_H_

#include "library_book_borrowing_manager/domain/customer.h"

namespace library_book_borrowing_manager::presentation::views {

class CheckinView {
 public:
  std::string PrintCustomerList(
      std::vector<domain::Customer> customer_list) const;
  std::string PrintBorrowRecordList(
      std::vector<domain::BorrowRecord> borrow_record_list,
      std::string selected_customer_id,
      std::vector<std::string> selected_borrow_record_ids) const;
  void PrintTotalOwedFee(double total_owed_fee) const;

  std::string CustomerToString(domain::Customer customer) const;
  std::string BorrowRecordToString(domain::BorrowRecord borrow_record) const;

  std::vector<std::string> CustomerListToString(
      std::vector<domain::Customer> customer_list) const;
  std::vector<std::string> BorrowRecordListToString(
      std::vector<domain::BorrowRecord> borrow_record_list) const;
};

}  // namespace library_book_borrowing_manager::presentation::views

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_VIEWS_CHECKIN_VIEW_H_
