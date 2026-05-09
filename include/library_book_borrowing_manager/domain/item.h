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
// item.h
// -----------------------------------------------------------------------------
//
// This header file defines the Item class. Each item object is a physical copy
// of a Title, whereas a Title is the general "identity" of an Item.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_ITEM_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_ITEM_H_

#include <string>

#include "library_book_borrowing_manager/domain/title.h"

namespace library_book_borrowing_manager::domain {

class Item {
 public:
  enum class Condition {
    kFactoryNew,
    kMinimalWear,
    kNormalWear,
    kWellWorn,
    kDamaged
  };

  Item(std::string id, const Title* title, Condition condition,
       std::string shelf_location, bool is_available);

  std::string id() const;
  const Title* title() const;
  Condition condition() const;
  std::string shelf_location() const;
  bool is_available() const;

  void set_id(std::string id);
  void set_title(const Title* title);
  void set_condition(Condition condition);
  void set_shelf_location(std::string shelf_location);
  void set_is_available(bool is_available);

 private:
  std::string id_;
  const Title* title_;
  Condition condition_;
  std::string shelf_location_;
  bool is_available_;
};

}  // namespace library_book_borrowing_manager::domain

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_ITEM_H_
