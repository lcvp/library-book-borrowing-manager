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

#include "library_book_borrowing_manager/domain/address.h"

#include <string>

namespace library_book_borrowing_manager::domain {

Address::Address(std::string building_number, std::string street,
                 std::string city, std::string postal_code)
    : building_number_(building_number),
      street_(street),
      city_(city),
      postal_code_(postal_code) {}

std::string Address::building_number() const { return building_number_; }

std::string Address::street() const { return street_; }

std::string Address::city() const { return city_; }

std::string Address::postal_code() const { return postal_code_; }

void Address::set_building_number(std::string building_number) {
  building_number_ = building_number;
}

void Address::set_street(std::string street) { street_ = street; }

void Address::set_city(std::string city) { city_ = city; }

void Address::set_postal_code(std::string postal_code) {
  postal_code_ = postal_code;
}

std::string Address::GetFullAddress() const {
  return building_number() + " " + street() + ", " + city() + " " +
         postal_code();
}

}  // namespace library_book_borrowing_manager::domain
