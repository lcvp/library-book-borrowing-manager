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
// Defines the Address class for Library Book Borrowing Manager. Intended to be
// used by the Customer class.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_ADDRESS_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_ADDRESS_H_

#include <string>

namespace library_book_borrowing_manager::domain {

class Address {
public:
  Address(std::string building_number, std::string street, std::string city,
          std::string postal_code);

  std::string building_number() const;
  std::string street() const;
  std::string city() const;
  std::string postal_code() const;

  void set_building_number(std::string building_number);
  void set_street(std::string street);
  void set_city(std::string city);
  void set_postal_code(std::string postal_code);

  std::string GetFullAddress() const;

private:
  std::string building_number_;
  std::string street_;
  std::string city_;
  std::string postal_code_;
};

} // namespace library_book_borrowing_manager::domain

#endif // LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_ADDRESS_H_
