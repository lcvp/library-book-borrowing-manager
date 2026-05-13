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

#include "library_book_borrowing_manager/domain/citizen_id.h"

#include <cctype>

namespace library_book_borrowing_manager::domain {

CitizenId::CitizenId(std::string id)
    : id_(id) {}

std::string CitizenId::id() const {
  return id_;
}

void CitizenId::set_id(std::string id) {
  id_ = id;
}

bool CitizenId::IsValid(std::string id) {
  if (id.length() != 12) {
    return false;
  }

  for (char c : id) {
    if (!std::isdigit(c)) {
      return false;
    }
  }

  return true;
}

}  // namespace library_book_borrowing_manager::domain
