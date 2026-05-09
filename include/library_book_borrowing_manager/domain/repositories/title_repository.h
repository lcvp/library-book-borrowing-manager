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
// title_repository.h
// -----------------------------------------------------------------------------
//
// This header file defines the TitleRepository class which acts as an interface
// for the corresponding data class.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_REPOSITORIES_TITLE_REPOSITORY_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_REPOSITORIES_TITLE_REPOSITORY_H_

#include <memory>
#include <string>
#include <vector>

#include "library_book_borrowing_manager/domain/title.h"

namespace library_book_borrowing_manager::domain::repositories {

class TitleRepository {
 public:
  virtual ~TitleRepository();

  virtual std::unique_ptr<Title> GetById(std::string id) const = 0;
  virtual std::vector<std::unique_ptr<Title>> GetAll() const = 0;
  virtual void Save(const Title& title) = 0;
  virtual void Remove(std::string id) = 0;
};

}  // namespace library_book_borrowing_manager::domain::repositories

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_REPOSITORIES_TITLE_REPOSITORY_H_
