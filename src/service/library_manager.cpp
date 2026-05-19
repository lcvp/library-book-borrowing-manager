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

#include "library_book_borrowing_manager/service/library_manager.h"

namespace library_book_borrowing_manager::service {

LibraryManager::LibraryManager(
    domain::repositories::LibraryDataRepository* library_data_repository)
    : library_data_repository_(library_data_repository) {}

domain::repositories::LibraryDataRepository*
LibraryManager::library_data_repository() const {
  return library_data_repository_;
}

}  // namespace library_book_borrowing_manager::service
