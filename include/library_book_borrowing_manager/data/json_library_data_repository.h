// Library Book Borrowing Manager




//
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
// json_library_data_repository.h
// -----------------------------------------------------------------------------
//
// This header file declares the JsonLibraryDataRepository class which
// implements the LibraryDataRepository interface. Intended to stores and
// retrieve all library data with JSON.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_DATA_JSON_LIBRARY_DATA_REPOSITORY_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_DATA_JSON_LIBRARY_DATA_REPOSITORY_H_

#include <deque>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "library_book_borrowing_manager/domain/customer.h"
#include "library_book_borrowing_manager/domain/item.h"
#include "library_book_borrowing_manager/domain/repositories/library_data_repository.h"
#include "library_book_borrowing_manager/domain/title.h"

namespace library_book_borrowing_manager::data {

class JsonLibraryDataRepository
    : public domain::repositories::LibraryDataRepository {
 public:
  explicit JsonLibraryDataRepository(std::string file_path);

  std::string file_path() const;
  void set_file_path(std::string file_path);

  domain::Customer GetCustomerById(std::string id) const override;
  std::vector<domain::Customer> GetAllCustomers() const override;
  void Save(const domain::Customer& customer) override;
  void RemoveCustomer(std::string id) override;

  domain::Item* GetItemById(std::string id) override;
  std::vector<domain::Item*> GetAllItems() override;
  void Save(const domain::Item& item) override;
  void RemoveItem(std::string id) override;

  const domain::Title* GetTitleById(std::string id) const override;
  std::vector<const domain::Title*> GetAllTitles() const override;
  void Save(std::unique_ptr<domain::Title> title) override;
  void RemoveTitle(std::string id) override;

 private:
  std::string file_path_;
  std::vector<domain::Customer> customers_;
  std::deque<domain::Item> items_;
  std::vector<std::unique_ptr<domain::Title>> titles_;
  void LoadAllFromFile();
  void SaveAllToFile();

  void LoadBooksFromFile(nlohmann::json& data);
  void LoadJournalsFromFile(nlohmann::json& data);
  void LoadMagazinesFromFile(nlohmann::json& data);
  void LoadThesesFromFile(nlohmann::json& data);
  void LoadItemsFromFile(nlohmann::json& data);
  void LoadCustomersFromFile(nlohmann::json& data);

  void SaveTitlesToJsonObject(nlohmann::json& data);
  void SaveItemsToJsonObject(nlohmann::json& data);
  void SaveCustomersToJsonObject(nlohmann::json& data);
};

}  // namespace library_book_borrowing_manager::data

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_DATA_JSON_LIBRARY_DATA_REPOSITORY_H_
