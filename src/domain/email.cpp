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

#include "library_book_borrowing_manager/domain/email.h"

#include <regex>
#include <stdexcept>
#include <string>

namespace library_book_borrowing_manager::domain {

Email::Email(std::string email_address) {
  if (!IsValid(email_address)) {
    throw std::invalid_argument("Invalid email address.");
  }
  email_address_ = email_address;
}

std::string Email::email_address() const { return email_address_; }

void Email::set_email_address(std::string email_address) {
  if (!IsValid(email_address)) {
    throw std::invalid_argument("Invalid email address.");
  }
  email_address_ = email_address;
}

bool Email::IsValid(std::string email_address) {
  const std::regex kEmailAddressPattern(
      R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
  return std::regex_match(email_address, kEmailAddressPattern);
}

}  // namespace library_book_borrowing_manager::domain
