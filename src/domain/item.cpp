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

#include "library_book_borrowing_manager/domain/item.h"

#include <string>

namespace library_book_borrowing_manager::domain {

Item::Item(std::string id, const Title* title, Condition condition,
           std::string shelf_location, bool is_available)
    : id_(id),
      title_(title),
      condition_(condition),
      shelf_location_(shelf_location),
      is_available_(is_available) {}

std::string Item::id() const { return id_; }

const Title* Item::title() const { return title_; }

Item::Condition Item::condition() const { return condition_; }

std::string Item::shelf_location() const { return shelf_location_; }

bool Item::is_available() const { return is_available_; }

void Item::set_id(std::string id) { id_ = id; }

void Item::set_title(const Title* title) { title_ = title; }

void Item::set_condition(Condition condition) { condition_ = condition; }

void Item::set_shelf_location(std::string shelf_location) {
  shelf_location_ = shelf_location;
}

void Item::set_is_available(bool is_available) { is_available_ = is_available; }

}  // namespace library_book_borrowing_manager::domain
