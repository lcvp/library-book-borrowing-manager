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

#include "library_book_borrowing_manager/data/json_library_data_repository.h"

#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include "library_book_borrowing_manager/domain/customer.h"
#include "library_book_borrowing_manager/domain/item.h"
#include "library_book_borrowing_manager/domain/title.h"

namespace library_book_borrowing_manager::data {

JsonLibraryDataRepository::JsonLibraryDataRepository(std::string file_path)
    : file_path_(file_path) {
  LoadFromFile();
}

std::string JsonLibraryDataRepository::file_path() const { return file_path_; }

void JsonLibraryDataRepository::set_file_path(std::string file_path) {
  file_path_ = file_path;
  LoadFromFile();
}

domain::Customer JsonLibraryDataRepository::GetCustomerById(
    std::string id) const {
  for (domain::Customer customer : customers_) {
    if (customer.id() == id) {
      return customer;
    }
  }

  throw std::invalid_argument("Invalid Customer ID.");
}

std::vector<domain::Customer> JsonLibraryDataRepository::GetAllCustomers()
    const {
  return customers_;
}

void JsonLibraryDataRepository::Save(const domain::Customer& customer) {
  for (domain::Customer& existing_customer : customers_) {
    if (existing_customer.id() == customer.id()) {
      existing_customer = customer;
      SaveToFile();
      return;
    }
  }
  customers_.push_back(customer);
  SaveToFile();
}

void JsonLibraryDataRepository::RemoveCustomer(std::string id) {
  for (int i = 0; i < customers_.size(); i++) {
    if (customers_[i].id() == id) {
      customers_.erase(customers_.begin() + i);
      SaveToFile();
      return;
    }
  }
}

domain::Item JsonLibraryDataRepository::GetItemById(std::string id) const {
  for (domain::Item item : items_) {
    if (item.id() == id) {
      return item;
    }
  }
  throw std::invalid_argument("Invalid Item ID.");
}

std::vector<domain::Item> JsonLibraryDataRepository::GetAllItems() const {
  return items_;
}

void JsonLibraryDataRepository::Save(const domain::Item& item) {
  for (domain::Item& existing_item : items_) {
    if (existing_item.id() == item.id()) {
      existing_item = item;
      SaveToFile();
      return;
    }
  }
  items_.push_back(item);
  SaveToFile();
}

void JsonLibraryDataRepository::RemoveItem(std::string id) {
  for (int i = 0; i < items_.size(); i++) {
    if (items_[i].id() == id) {
      items_.erase(items_.begin() + i);
      SaveToFile();
      return;
    }
  }
}

const domain::Title* JsonLibraryDataRepository::GetTitleById(
    std::string id) const {
  for (const std::unique_ptr<domain::Title>& title : titles_) {
    if (title->id() == id) {
      return title.get();
    }
  }

  throw std::invalid_argument("Invalid Title ID.");
}

std::vector<const domain::Title*> JsonLibraryDataRepository::GetAllTitles()
    const {
  std::vector<const domain::Title*> titles;
  for (const std::unique_ptr<domain::Title>& title : titles_) {
    titles.push_back(title.get());
  }
  return titles;
}

void JsonLibraryDataRepository::Save(std::unique_ptr<domain::Title> title) {
  for (std::unique_ptr<domain::Title>& existing_title : titles_) {
    if (existing_title->id() == title->id()) {
      existing_title = std::move(title);
      SaveToFile();
      return;
    }
  }
  titles_.push_back(std::move(title));
  SaveToFile();
}

void JsonLibraryDataRepository::RemoveTitle(std::string id) {
  for (int i = 0; i < titles_.size(); i++) {
    if (titles_[i]->id() == id) {
      titles_.erase(titles_.begin() + 1);
      SaveToFile();
      return;
    }
  }
}

void JsonLibraryDataRepository::LoadFromFile() {
  std::ifstream f(file_path());
  nlohmann::json data = nlohmann::json::parse(f);
}

void JsonLibraryDataRepository::SaveToFile() {}

}  // namespace library_book_borrowing_manager::data
