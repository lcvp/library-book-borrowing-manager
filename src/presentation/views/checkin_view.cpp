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

#include "library_book_borrowing_manager/presentation/views/checkin_view.h"

#include <iostream>
#include <string>

#include "library_book_borrowing_manager/presentation/views/console_view.h"

namespace library_book_borrowing_manager::presentation::views {

std::string CheckinView::PrintCustomerList(
    std::vector<domain::Customer> customer_list) const {
  PrintHeader("Checkin Items");
  PrintList(CustomerListToString(customer_list));

  PrintDivider();
  std::string user_input = PromptForString("Enter customer id: ");
  return user_input;
}

std::string CheckinView::PrintBorrowRecordList(
    std::vector<domain::BorrowRecord> borrow_record_list,
    std::string selected_customer_id,
    std::vector<std::string> selected_borrow_record_ids) const {
  PrintHeader("Checkin Items");
  PrintList(BorrowRecordListToString(borrow_record_list));

  PrintDivider();
  std::cout << "Selected customer id: " << selected_customer_id << std::endl;
  std::cout << "Selected borrow record ids: " << std::endl;
  PrintList(selected_borrow_record_ids);

  PrintDivider();
  std::string user_input = PromptForString("Enter borrow record id: ");
  return user_input;
}

void CheckinView::PrintTotalOwedFee(double total_owed_fee) const {
  std::cout << "Total owed fee: " << total_owed_fee << std::endl;
}

std::string CheckinView::CustomerToString(domain::Customer customer) const {
  std::string customer_as_string;
  customer_as_string += "Customer ID: " + customer.id();
  customer_as_string += " | ";
  customer_as_string += " Name: " + customer.name();
  customer_as_string += ", CID: " + customer.citizen_id().id();
  customer_as_string += ", DOB: " + TimePointToString(customer.date_of_birth());
  customer_as_string += ", Email: " + customer.email().email_address();
  return customer_as_string;
}

std::string CheckinView::BorrowRecordToString(
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
  return string_borrow_record;
}

std::vector<std::string> CheckinView::CustomerListToString(
    std::vector<domain::Customer> customer_list) const {
  std::vector<std::string> string_customer_list;
  for (domain::Customer customer : customer_list) {
    string_customer_list.push_back(CustomerToString(customer));
  }
  return string_customer_list;
}

std::vector<std::string> CheckinView::BorrowRecordListToString(
    std::vector<domain::BorrowRecord> borrow_record_list) const {
  std::vector<std::string> string_borrow_record_list;
  for (domain::BorrowRecord borrow_record : borrow_record_list) {
    string_borrow_record_list.push_back(BorrowRecordToString(borrow_record));
  }
  return string_borrow_record_list;
}

}  // namespace library_book_borrowing_manager::presentation::views
