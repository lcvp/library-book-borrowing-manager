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
// Defines the JsonTitleRepository class for retrieving and storing Title data
// with Json.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_DATA_JSON_TITLE_REPOSITORY_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_DATA_JSON_TITLE_REPOSITORY_H_

#include <memory>
#include <string>
#include <vector>

#include "library_book_borrowing_manager/domain/repositories/title_repository.h"
#include "library_book_borrowing_manager/domain/title.h"

namespace library_book_borrowing_manager::data {

class JsonTitleRepository : public domain::repositories::TitleRepository {
 public:
  explicit JsonTitleRepository(std::string file_path);

  std::string file_path() const;
  void set_file_path(std::string file_path);

  std::unique_ptr<domain::Title> GetById(std::string id) const override;
  std::vector<std::unique_ptr<domain::Title>> GetAll() const override;
  void Save(const domain::Title& title) override;
  void Remove(std::string id) override;

 private:
  std::string file_path_;
};

}  // namespace library_book_borrowing_manager::data

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_DATA_JSON_TITLE_REPOSITORY_H_
