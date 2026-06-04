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
// customers_view.h
// -----------------------------------------------------------------------------
//
// This header file declares the CustomersView class for rendering menu options
// regarding Customers.

#include <chrono>
#include <string>
#include <vector>

#include "library_book_borrowing_manager/domain/customer.h"

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_VIEWS_CUSTOMERS_VIEW_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_VIEWS_CUSTOMERS_VIEW_H_

namespace library_book_borrowing_manager::presentation::views {

class CustomersView {
 public:
  char PrintCustomersOptions() const;
  std::string PrintCustomerList(const std::vector<domain::Customer> customers,
                                bool get_input = true) const;
  std::string PromptForName(std::string current_name) const;
  std::string PromptForCitizenId(std::string current_citizen_id) const;
  std::chrono::system_clock::time_point PromptForDateOfBirth(
      std::chrono::system_clock::time_point current_date_of_birth) const;
  std::string PromptForEmailAddress(std::string current_email_address) const;
  std::string PromptForPhoneNumber(std::string current_phone_number) const;
  std::string PromptForBuildingNumber(
      std::string current_building_number) const;
  std::string PromptForStreet(std::string current_street) const;
  std::string PromptForCity(std::string current_city) const;
  std::string PromptForPostalCode(std::string current_postal_code) const;
  std::string CustomerToString(domain::Customer customer) const;
  std::vector<std::string> CustomerListToString(
      std::vector<domain::Customer> customer_list) const;
};

}  // namespace library_book_borrowing_manager::presentation::views

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_VIEWS_CUSTOMERS_VIEW_H_
