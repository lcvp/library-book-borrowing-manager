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

#include "library_book_borrowing_manager/presentation/views/customers_view.h"

#include <string>

#include "library_book_borrowing_manager/presentation/views/console_view.h"

namespace library_book_borrowing_manager::presentation::views {

char CustomersView::PrintCustomersOptions() const {
  PrintHeader("Manage Customers");

  std::map<std::string, std::string> options = {
      {"1", "Update Customer"},
      {"2", "Delete Customer"},
      {"Any other key", "Back To Main Menu"}};

  PrintList(options);

  PrintDivider();

  return PromptForString("Enter: ")[0];
}

std::string CustomersView::PrintCustomerList(
    const std::vector<domain::Customer> customers, bool get_input) const {
  PrintHeader("Customers");

  std::vector<std::string> customer_list = CustomerListToString(customers);

  PrintList(customer_list);

  PrintDivider();

  std::string user_input;

  if (get_input) {
    user_input = PromptForString("Enter Customer ID: ");
  }

  return user_input;
}

std::string CustomersView::CustomerToString(domain::Customer customer) const {
  std::string customer_as_string;
  customer_as_string += "Customer ID: " + customer.id();
  customer_as_string += " | ";
  customer_as_string += " Name: " + customer.name();
  customer_as_string += ", CID: " + customer.citizen_id().id();
  customer_as_string += ", DOB: " + TimePointToString(customer.date_of_birth());
  customer_as_string += ", Email: " + customer.email().email_address();
  customer_as_string += ", Phone Number: " + customer.phone_number();
  customer_as_string += ", Address: " + customer.address().GetFullAddress();
  return customer_as_string;
}

std::vector<std::string> CustomersView::CustomerListToString(
    std::vector<domain::Customer> customer_list) const {
  std::vector<std::string> string_customer_list;
  for (domain::Customer customer : customer_list) {
    string_customer_list.push_back(CustomerToString(customer));
  }
  return string_customer_list;
}

std::string CustomersView::PromptForName(std::string current_name) const {
  std::string input = PromptForString("Enter Name [" + current_name + "]: ");

  if (input.empty()) {
    return current_name;
  }

  return input;
}

std::string CustomersView::PromptForCitizenId(
    std::string current_citizen_id) const {
  std::string input =
      PromptForString("Enter Citizen ID [" + current_citizen_id + "]: ");

  if (input.empty()) {
    return current_citizen_id;
  }

  return input;
}

std::chrono::system_clock::time_point CustomersView::PromptForDateOfBirth(
    std::chrono::system_clock::time_point current_date_of_birth) const {
  std::string current_date_of_birth_string =
      TimePointToString(current_date_of_birth);

  std::string input = PromptForString("Enter Date Of Birth [" +
                                      current_date_of_birth_string + "]: ");

  if (input.empty()) {
    return current_date_of_birth;
  }

  return StringToTimePoint(input);
}

std::string CustomersView::PromptForEmailAddress(
    std::string current_email_address) const {
  std::string input =
      PromptForString("Enter Email [" + current_email_address + "]: ");

  if (input.empty()) {
    return current_email_address;
  }

  return input;
}

std::string CustomersView::PromptForPhoneNumber(
    std::string current_phone_number) const {
  std::string input =
      PromptForString("Enter Phone Number [" + current_phone_number + "]: ");

  if (input.empty()) {
    return current_phone_number;
  }

  return input;
}

std::string CustomersView::PromptForBuildingNumber(
    std::string current_building_number) const {
  std::string input = PromptForString("Enter Building Number [" +
                                      current_building_number + "]: ");

  if (input.empty()) {
    return current_building_number;
  }

  return input;
}

std::string CustomersView::PromptForStreet(std::string current_street) const {
  std::string input =
      PromptForString("Enter Street [" + current_street + "]: ");

  if (input.empty()) {
    return current_street;
  }

  return input;
}

std::string CustomersView::PromptForCity(std::string current_city) const {
  std::string input = PromptForString("Enter City [" + current_city + "]: ");

  if (input.empty()) {
    return current_city;
  }

  return input;
}

std::string CustomersView::PromptForPostalCode(
    std::string current_postal_code) const {
  std::string input =
      PromptForString("Enter Postal Code [" + current_postal_code + "]: ");

  if (input.empty()) {
    return current_postal_code;
  }

  return input;
}

}  // namespace library_book_borrowing_manager::presentation::views
