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
// library_manager.h
// -----------------------------------------------------------------------------
//
// This header file defines the LibraryManager class which manages the business
// logic of a library.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_SERVICE_LIBRARY_MANAGER_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_SERVICE_LIBRARY_MANAGER_H_

#include <memory>

#include "library_book_borrowing_manager/domain/repositories/customer_repository.h"
#include "library_book_borrowing_manager/domain/repositories/item_repository.h"
#include "library_book_borrowing_manager/domain/repositories/title_repository.h"

namespace library_book_borrowing_manager::service {

class LibraryManager {
 public:
  LibraryManager(
      std::unique_ptr<domain::repositories::CustomerRepository>
          customer_repository,
      std::unique_ptr<domain::repositories::ItemRepository> item_repository,
      std::unique_ptr<domain::repositories::TitleRepository> title_repository);

  domain::repositories::CustomerRepository* customer_repository() const;
  domain::repositories::ItemRepository* item_repository() const;
  domain::repositories::TitleRepository* title_repository() const;

 private:
  std::unique_ptr<domain::repositories::CustomerRepository>
      customer_repository_;
  std::unique_ptr<domain::repositories::ItemRepository> item_repository_;
  std::unique_ptr<domain::repositories::TitleRepository> title_repository_;
};

}  // namespace library_book_borrowing_manager::service

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_SERVICE_LIBRARY_MANAGER_H_
