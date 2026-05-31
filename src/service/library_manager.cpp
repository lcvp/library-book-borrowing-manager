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

#include <stdexcept>
#include <string>
#include <vector>

#include "library_book_borrowing_manager/domain/repositories/library_data_repository.h"

namespace library_book_borrowing_manager::service {

LibraryManager::LibraryManager(
    domain::repositories::LibraryDataRepository* library_data_repository)
    : library_data_repository_(library_data_repository) {}

void LibraryManager::set_library_date_repository(
    domain::repositories::LibraryDataRepository* library_data_repository) {
  library_data_repository_ = library_data_repository;
}

void LibraryManager::CheckoutItems(std::string customer_id,
                                   std::vector<std::string> item_ids) {
  // write this later
  // holy shit
}

std::vector<std::string> LibraryManager::GetStringCustomerList() const {
  // write this later
  return {""};
}

std::vector<std::string> LibraryManager::GetStringItemList() const {
  // write this alter
  return {""};
}

}  // namespace library_book_borrowing_manager::service
