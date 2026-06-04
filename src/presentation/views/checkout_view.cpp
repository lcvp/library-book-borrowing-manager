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

#include "library_book_borrowing_manager/domain/customer.h"
#include "library_book_borrowing_manager/domain/item.h"
#include "library_book_borrowing_manager/presentation/views/console_view.h"

namespace library_book_borrowing_manager::presentation::views {

std::string CheckoutView::PrintCustomerList(
    std::vector<domain::Customer> customer_list) const {
  PrintHeader("Checkout Items");
  PrintList(CustomerListToString(customer_list));

  PrintDivider();
  std::string user_input = PromptForString("Enter customer id: ");
  return user_input;
}

std::string CheckoutView::PrintItemList(
    std::vector<domain::Item> item_list, std::string selected_customer_id,
    std::vector<std::string> selected_item_ids) const {
  PrintHeader("Checkout Items");
  PrintList(ItemListToString(item_list));

  PrintDivider();
  std::cout << "Selected customer id: " << selected_customer_id << std::endl;
  std::cout << "Selected item ids: " << std::endl;
  PrintList(selected_item_ids);

  PrintDivider();
  std::string user_input = PromptForString("Enter item id: ");
  return user_input;
}

std::string CheckoutView::CustomerToString(domain::Customer customer) const {
  std::string customer_as_string;
  customer_as_string += "Customer ID: " + customer.id();
  customer_as_string += " | ";
  customer_as_string += " Name: " + customer.name();
  customer_as_string += ", CID: " + customer.citizen_id().id();
  customer_as_string += ", DOB: " + TimePointToString(customer.date_of_birth());
  customer_as_string += ", Email: " + customer.email().email_address();
  return customer_as_string;
}

std::string CheckoutView::ItemToString(domain::Item item) const {
  std::string item_as_string;

  item_as_string += "Item ID: " + item.id();
  item_as_string += " | ";

  if (item.title() != nullptr) {
    item_as_string += item.title()->GetApaCitation();
  } else {
    item_as_string += "Unknown Title";
  }

  item_as_string += " | Condition: ";

  switch (item.condition()) {
    case domain::Item::Condition::kFactoryNew:
      item_as_string += "Factory New";
      break;
    case domain::Item::Condition::kMinimalWear:
      item_as_string += "Minimal Wear";
      break;
    case domain::Item::Condition::kNormalWear:
      item_as_string += "Normal Wear";
      break;
    case domain::Item::Condition::kWellWorn:
      item_as_string += "Well Worn";
      break;
    case domain::Item::Condition::kDamaged:
      item_as_string += "Damaged";
      break;
  }

  item_as_string += " | Status: ";

  if (item.is_available()) {
    item_as_string += "Available";
  } else {
    item_as_string += "Borrowed";
  }

  return item_as_string;
}

std::vector<std::string> CheckoutView::CustomerListToString(
    std::vector<domain::Customer> customer_list) const {
  std::vector<std::string> string_customer_list;
  for (domain::Customer customer : customer_list) {
    string_customer_list.push_back(CustomerToString(customer));
  }
  return string_customer_list;
}

std::vector<std::string> CheckoutView::ItemListToString(
    std::vector<domain::Item> item_list) const {
  std::vector<std::string> string_item_list;
  for (domain::Item item : item_list) {
    string_item_list.push_back(ItemToString(item));
  }
  return string_item_list;
}

}  // namespace library_book_borrowing_manager::presentation::views
