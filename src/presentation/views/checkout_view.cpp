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

#include "library_book_borrowing_manager/presentation/views/checkout_view.h"

#include <iostream>
#include <string>
#include <vector>

#include "library_book_borrowing_manager/presentation/views/console_view.h"

namespace library_book_borrowing_manager::presentation::views {

std::string CheckoutView::PrintCustomerList(
    std::vector<std::string> customer_list) const {
  PrintHeader("Checkout Items");
  PrintList(customer_list);

  PrintDivider();
  std::string user_input = PromptForString("Enter user id: ");
  return user_input;
}

std::string CheckoutView::PrintItemList(
    std::vector<std::string> item_list, std::string selected_customer_id,
    std::vector<std::string> selected_item_ids) const {
  PrintHeader("Checkout Items");
  PrintList(item_list);

  PrintDivider();
  std::cout << "Selected customer id: " << selected_customer_id << std::endl;
  std::cout << "Selected item ids: " << std::endl;
  PrintList(selected_item_ids);

  PrintDivider();
  std::string user_input = PromptForString("Enter item id: ");
  return user_input;
}

}  // namespace library_book_borrowing_manager::presentation::views
