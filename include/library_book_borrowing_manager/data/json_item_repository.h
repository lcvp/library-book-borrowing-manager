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
// Defines the JsonItemRepository class for storing and retrieving Item data
// with Json.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_DATA_JSON_ITEM_REPOSITORY_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_DATA_JSON_ITEM_REPOSITORY_H_

#include <string>
#include <vector>

#include "library_book_borrowing_manager/domain/item.h"
#include "library_book_borrowing_manager/domain/repositories/item_repository.h"

namespace library_book_borrowing_manager::data {

class JsonItemRepository : public domain::repositories::ItemRepository {
 public:
  explicit JsonItemRepository(std::string file_path);

  std::string file_path() const;
  void set_file_path(std::string file_path);

  domain::Item GetById(std::string id) const override;
  std::vector<domain::Item> GetAll() const override;
  void Save(const domain::Item& item) override;
  void Remove(std::string id) override;

 private:
  std::string file_path_;
};

}  // namespace library_book_borrowing_manager::data

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_DATA_JSON_ITEM_REPOSITORY_H_
