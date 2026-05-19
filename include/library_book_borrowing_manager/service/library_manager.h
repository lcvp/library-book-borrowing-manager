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

#include "library_book_borrowing_manager/domain/repositories/library_data_repository.h"

namespace library_book_borrowing_manager::service {

class LibraryManager {
 public:
  LibraryManager(
      domain::repositories::LibraryDataRepository* library_data_repository);

  domain::repositories::LibraryDataRepository* library_data_repository() const;

 private:
  domain::repositories::LibraryDataRepository* library_data_repository_;
};

}  // namespace library_book_borrowing_manager::service

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_SERVICE_LIBRARY_MANAGER_H_
