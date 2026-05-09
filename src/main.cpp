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
// main.cpp
// -----------------------------------------------------------------------------
//
// This file declares the main function of the Library Book Borrowing Manager
// program.

#include <string>

#include "library_book_borrowing_manager/data/json_customer_repository.h"
#include "library_book_borrowing_manager/data/json_item_repository.h"
#include "library_book_borrowing_manager/data/json_title_repository.h"
#include "library_book_borrowing_manager/presentation/user_interface.h"
#include "library_book_borrowing_manager/service/library_manager.h"

int main() {
  const std::string kCustomerFilePath = "saves/customers.json";
  const std::string kItemFilePath = "saves/items.json";
  const std::string kTitleFilePath = "saves/title.json";

  library_book_borrowing_manager::data::JsonCustomerRepository
      customer_repository(kCustomerFilePath);
  library_book_borrowing_manager::data::JsonItemRepository item_repository(
      kItemFilePath);
  library_book_borrowing_manager::data::JsonTitleRepository title_repository(
      kTitleFilePath);

  library_book_borrowing_manager::service::LibraryManager library_manager(
      &customer_repository, &item_repository, &title_repository);

  library_book_borrowing_manager::presentation::UserInterface user_interface(
      &library_manager);

  user_interface.Start();

  return 0;
}
