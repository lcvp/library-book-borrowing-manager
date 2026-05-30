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
// library_data_repository.h
// -----------------------------------------------------------------------------
//
// This header files declares the LibraryDataRepository class, intended to act
// as a repository interface for the service class LibraryManager.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_REPOSITORIES_LIBRARY_DATA_REPOSITORY_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_REPOSITORIES_LIBRARY_DATA_REPOSITORY_H_

#include <memory>
#include <string>
#include <vector>

#include "library_book_borrowing_manager/domain/customer.h"
#include "library_book_borrowing_manager/domain/item.h"
#include "library_book_borrowing_manager/domain/title.h"

namespace library_book_borrowing_manager::domain::repositories {

class LibraryDataRepository {
 public:
  virtual ~LibraryDataRepository();

  virtual Customer GetCustomerById(std::string id) const = 0;
  virtual std::vector<Customer> GetAllCustomers() const = 0;
  virtual void Save(const Customer& customer) = 0;
  virtual void RemoveCustomer(std::string id) = 0;

  virtual Item GetItemById(std::string id) const = 0;
  virtual std::vector<Item> GetAllItems() const = 0;
  virtual void Save(const Item& item) = 0;
  virtual void RemoveItem(std::string id) = 0;

  virtual const domain::Title* GetTitleById(std::string id) const = 0;
  virtual std::vector<const domain::Title*> GetAllTitles() const = 0;
  virtual void Save(std::unique_ptr<domain::Title> title) = 0;
  virtual void RemoveTitle(std::string id) = 0;
};

}  // namespace library_book_borrowing_manager::domain::repositories

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_REPOSITORIES_LIBRARY_DATA_REPOSITORY_H_
