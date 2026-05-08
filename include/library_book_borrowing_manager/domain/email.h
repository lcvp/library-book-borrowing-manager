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
// Defines the Email class. Intended to be used by the Customer class

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_EMAIL_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_EMAIL_H_

#include <string>

namespace library_book_borrowing_manager::domain {

class Email {
 public:
  explicit Email(std::string email_address);

  std::string email_adress() const;

  void set_email_address(std::string email_address);

  static bool IsValid(std::string email_address);

 private:
  std::string email_address_;
};

}  // namespace library_book_borrowing_manager::domain

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_EMAIL_H_
