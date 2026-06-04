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

#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

#include "library_book_borrowing_manager/domain/book.h"
#include "library_book_borrowing_manager/domain/item.h"
#include "library_book_borrowing_manager/domain/journal.h"
#include "library_book_borrowing_manager/domain/magazine.h"
#include "library_book_borrowing_manager/domain/repositories/library_data_repository.h"
#include "library_book_borrowing_manager/domain/thesis.h"
#include "library_book_borrowing_manager/domain/title.h"

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
  domain::Customer customer =
      library_data_repository_->GetCustomerById(customer_id);
  for (std::string item_id : item_ids) {
    std::string borrow_record_id = GenerateBorrowRecordId();
    std::chrono::system_clock::time_point now =
        std::chrono::system_clock::now();
    std::chrono::system_clock::time_point due_date =
        now + std::chrono::hours(24 * 14);
    domain::Item* item = library_data_repository_->GetItemById(item_id);

    domain::BorrowRecord borrow_record(borrow_record_id, now, due_date,
                                       std::nullopt, item);
    if (item->is_available() == false) {
      throw std::invalid_argument("Item is unavailable");
    }
    item->set_is_available(false);
    customer.Borrow(borrow_record);
    library_data_repository_->Save(customer);
  }
}

double LibraryManager::CheckinItems(
    std::string customer_id, std::vector<std::string> borrow_record_ids) {
  domain::Customer customer =
      library_data_repository_->GetCustomerById(customer_id);

  double total_owed_fee = 0.0;

  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

  for (std::string borrow_record_id : borrow_record_ids) {
    bool borrow_record_found = false;

    for (domain::BorrowRecord borrow_record : customer.borrow_records()) {
      if (borrow_record.id() == borrow_record_id) {
        borrow_record_found = true;

        if (borrow_record.return_date().has_value()) {
          throw std::invalid_argument("Borrow record is already returned.");
        }

        domain::Item* item = borrow_record.item();

        if (item == nullptr) {
          throw std::runtime_error("Borrow record has no item.");
        }

        total_owed_fee += borrow_record.CalculateLateFee();

        customer.Return(*item, now);

        break;
      }
    }

    if (!borrow_record_found) {
      throw std::invalid_argument("Invalid borrow record ID.");
    }
  }

  library_data_repository_->Save(customer);

  return total_owed_fee;
}

void LibraryManager::RegisterCustomer(
    std::string citizen_id, std::string name,
    std::chrono::system_clock::time_point date_of_birth,
    std::string email_address, std::string phone_number,
    std::string address_building_number, std::string address_street,
    std::string address_city, std::string address_postal_code) {
  std::string customer_id = GenerateCustomerId();

  domain::CitizenId customer_citizen_id(citizen_id);
  domain::Address address(address_building_number, address_street, address_city,
                          address_postal_code);
  domain::Email email(email_address);

  domain::Customer customer(customer_id, customer_citizen_id, name,
                            date_of_birth, address, email, phone_number);
  library_data_repository_->Save(customer);
}

void LibraryManager::AddBook(std::string name, std::string description,
                             std::string author, std::string publisher,
                             int publication_year, std::string doi,
                             std::string isbn, std::string edition) {
  std::unique_ptr<domain::Title> book = std::make_unique<domain::Book>(
      GenerateTitleId(), name, description, author, publisher, publication_year,
      doi, isbn, edition);

  library_data_repository_->Save(std::move(book));
}

void LibraryManager::AddJournal(std::string name, std::string description,
                                std::string author, std::string publisher,
                                int publication_year, std::string doi,
                                std::string issn, std::string publication_name,
                                std::string volume, std::string issue_number,
                                std::string field_of_study,
                                bool is_peer_reviewed) {
  std::unique_ptr<domain::Title> journal = std::make_unique<domain::Journal>(
      GenerateTitleId(), name, description, author, publisher, publication_year,
      doi, issn, publication_name, volume, issue_number, field_of_study,
      is_peer_reviewed);

  library_data_repository_->Save(std::move(journal));
}

void LibraryManager::AddMagazine(std::string name, std::string description,
                                 std::string author, std::string publisher,
                                 int publication_year, std::string doi,
                                 std::string issn, std::string publication_name,
                                 std::string volume, std::string issue_number,
                                 std::string category) {
  std::unique_ptr<domain::Title> magazine = std::make_unique<domain::Magazine>(
      GenerateTitleId(), name, description, author, publisher, publication_year,
      doi, issn, publication_name, volume, issue_number, category);

  library_data_repository_->Save(std::move(magazine));
}

void LibraryManager::AddThesis(std::string name, std::string description,
                               std::string author, std::string publisher,
                               int publication_year, std::string doi,
                               std::string university, std::string degree_level,
                               int defense_year, std::string supervisor_name) {
  std::unique_ptr<domain::Title> thesis = std::make_unique<domain::Thesis>(
      GenerateTitleId(), name, description, author, publisher, publication_year,
      doi, university, degree_level, defense_year, supervisor_name);

  library_data_repository_->Save(std::move(thesis));
}

void LibraryManager::AddItem(std::string title_id, char condition_input,
                             std::string shelf_location) {
  const domain::Title* title = library_data_repository_->GetTitleById(title_id);

  if (title == nullptr) {
    throw std::invalid_argument("Title ID does not exist.");
  }

  domain::Item::Condition condition;

  switch (condition_input) {
    case '1':
      condition = domain::Item::Condition::kFactoryNew;
      break;
    case '2':
      condition = domain::Item::Condition::kMinimalWear;
      break;
    case '3':
      condition = domain::Item::Condition::kNormalWear;
      break;
    case '4':
      condition = domain::Item::Condition::kWellWorn;
      break;
    case '5':
      condition = domain::Item::Condition::kDamaged;
      break;
    default:
      throw std::invalid_argument("Invalid item condition.");
  }

  domain::Item item(GenerateItemId(), title, condition, shelf_location, true);
  library_data_repository_->Save(item);
}

std::vector<domain::Customer> LibraryManager::GetCustomerList() const {
  return library_data_repository_->GetAllCustomers();
}

std::vector<domain::Item> LibraryManager::GetItemList() const {
  std::vector<domain::Item*> item_pointers =
      library_data_repository_->GetAllItems();

  std::vector<domain::Item> items;

  for (domain::Item* item : item_pointers) {
    items.push_back(*item);
  }

  return items;
}

std::vector<const domain::Title*> LibraryManager::GetTitleList() {
  return library_data_repository_->GetAllTitles();
}

std::vector<domain::BorrowRecord> LibraryManager::GetBorrowRecordList() const {
  std::vector<domain::BorrowRecord> borrow_records;
  std::vector<domain::Customer> customers =
      library_data_repository_->GetAllCustomers();

  for (domain::Customer customer : customers) {
    for (domain::BorrowRecord borrow_record : customer.borrow_records()) {
      borrow_records.push_back(borrow_record);
    }
  }
  return borrow_records;
}

domain::Customer LibraryManager::GetCustomerById(
    std::string customer_id) const {
  return library_data_repository_->GetCustomerById(customer_id);
}

domain::BorrowRecord LibraryManager::GetBorrowRecordById(
    std::string borrow_record_id) const {
  std::vector<domain::BorrowRecord> borrow_records = GetBorrowRecordList();
  for (domain::BorrowRecord borrow_record : borrow_records) {
    if (borrow_record_id == borrow_record.id()) {
      return borrow_record;
    }
  }

  throw std::invalid_argument("Borrow Record does not exists");
}

const domain::Title* LibraryManager::GetTitleById(std::string title_id) const {
  return library_data_repository_->GetTitleById(title_id);
}

domain::Item LibraryManager::GetItemById(std::string item_id) const {
  return *library_data_repository_->GetItemById(item_id);
}

void LibraryManager::UpdateCustomer(
    std::string customer_id, std::string name, std::string citizen_id,
    std::chrono::system_clock::time_point date_of_birth,
    std::string email_address, std::string phone_number,
    std::string building_number, std::string street, std::string city,
    std::string postal_code) {
  domain::Customer customer =
      library_data_repository_->GetCustomerById(customer_id);

  domain::CitizenId updated_citizen_id(citizen_id);
  domain::Email updated_email(email_address);
  domain::Address updated_address(building_number, street, city, postal_code);

  customer.set_name(name);
  customer.set_citizen_id(updated_citizen_id);
  customer.set_date_of_birth(date_of_birth);
  customer.set_email(updated_email);
  customer.set_phone_number(phone_number);
  customer.set_address(updated_address);

  library_data_repository_->Save(customer);
}

void LibraryManager::UpdateBook(std::string title_id, std::string name,
                                std::string description, std::string author,
                                std::string publisher, int publication_year,
                                std::string doi, std::string isbn,
                                std::string edition) {
  std::unique_ptr<domain::Title> book = std::make_unique<domain::Book>(
      title_id, name, description, author, publisher, publication_year, doi,
      isbn, edition);

  library_data_repository_->Save(std::move(book));
}

void LibraryManager::UpdateJournal(std::string title_id, std::string name,
                                   std::string description, std::string author,
                                   std::string publisher, int publication_year,
                                   std::string doi, std::string issn,
                                   std::string publication_name,
                                   std::string volume, std::string issue_number,
                                   std::string field_of_study,
                                   bool is_peer_reviewed) {
  std::unique_ptr<domain::Title> journal = std::make_unique<domain::Journal>(
      title_id, name, description, author, publisher, publication_year, doi,
      issn, publication_name, volume, issue_number, field_of_study,
      is_peer_reviewed);

  library_data_repository_->Save(std::move(journal));
}

void LibraryManager::UpdateMagazine(
    std::string title_id, std::string name, std::string description,
    std::string author, std::string publisher, int publication_year,
    std::string doi, std::string issn, std::string publication_name,
    std::string volume, std::string issue_number, std::string category) {
  std::unique_ptr<domain::Title> magazine = std::make_unique<domain::Magazine>(
      title_id, name, description, author, publisher, publication_year, doi,
      issn, publication_name, volume, issue_number, category);

  library_data_repository_->Save(std::move(magazine));
}

void LibraryManager::UpdateThesis(std::string title_id, std::string name,
                                  std::string description, std::string author,
                                  std::string publisher, int publication_year,
                                  std::string doi, std::string university,
                                  std::string degree_level, int defense_year,
                                  std::string supervisor_name) {
  std::unique_ptr<domain::Title> thesis = std::make_unique<domain::Thesis>(
      title_id, name, description, author, publisher, publication_year, doi,
      university, degree_level, defense_year, supervisor_name);

  library_data_repository_->Save(std::move(thesis));
}

void LibraryManager::UpdateItem(std::string item_id, std::string title_id,
                                domain::Item::Condition condition,
                                std::string shelf_location, bool is_available) {
  const domain::Title* title = library_data_repository_->GetTitleById(title_id);

  domain::Item updated_item(item_id, title, condition, shelf_location,
                            is_available);

  library_data_repository_->Save(updated_item);
}

void LibraryManager::DeleteCustomer(std::string customer_id) {
  library_data_repository_->RemoveCustomer(customer_id);
}

void LibraryManager::DeleteTitle(std::string title_id) {
  const domain::Title* title = library_data_repository_->GetTitleById(title_id);

  if (title == nullptr) {
    throw std::invalid_argument("Invalid title ID.");
  }

  const domain::Book* book = dynamic_cast<const domain::Book*>(title);

  if (book != nullptr) {
    std::unique_ptr<domain::Title> deleted_book =
        std::make_unique<domain::Book>(title_id, "[deleted]", "[deleted]",
                                       "[deleted]", "[deleted]", 0, "[deleted]",
                                       "0000000000000", "[deleted]");

    library_data_repository_->Save(std::move(deleted_book));
    return;
  }

  const domain::Journal* journal = dynamic_cast<const domain::Journal*>(title);

  if (journal != nullptr) {
    std::unique_ptr<domain::Title> deleted_journal =
        std::make_unique<domain::Journal>(
            title_id, "[deleted]", "[deleted]", "[deleted]", "[deleted]", 0,
            "[deleted]", "0000-000X", "[deleted]", "[deleted]", "[deleted]",
            "[deleted]", false);

    library_data_repository_->Save(std::move(deleted_journal));
    return;
  }

  const domain::Magazine* magazine =
      dynamic_cast<const domain::Magazine*>(title);

  if (magazine != nullptr) {
    std::unique_ptr<domain::Title> deleted_magazine =
        std::make_unique<domain::Magazine>(
            title_id, "[deleted]", "[deleted]", "[deleted]", "[deleted]", 0,
            "[deleted]", "0000-000X", "[deleted]", "[deleted]", "[deleted]",
            "[deleted]");

    library_data_repository_->Save(std::move(deleted_magazine));
    return;
  }

  const domain::Thesis* thesis = dynamic_cast<const domain::Thesis*>(title);

  if (thesis != nullptr) {
    std::unique_ptr<domain::Title> deleted_thesis =
        std::make_unique<domain::Thesis>(
            title_id, "[deleted]", "[deleted]", "[deleted]", "[deleted]", 0,
            "[deleted]", "[deleted]", "[deleted]", 0, "[deleted]");

    library_data_repository_->Save(std::move(deleted_thesis));
    return;
  }

  throw std::runtime_error("Unknown title type.");
}

void LibraryManager::DeleteItem(std::string item_id) {
  domain::Item* existing_item = library_data_repository_->GetItemById(item_id);

  if (existing_item == nullptr) {
    throw std::invalid_argument("Invalid item ID.");
  }

  domain::Item deleted_item(item_id, existing_item->title(),
                            domain::Item::Condition::kDamaged, "[deleted]",
                            false);

  library_data_repository_->Save(deleted_item);
}

std::string LibraryManager::GenerateBorrowRecordId() const {
  std::vector<domain::Customer> customer_list =
      library_data_repository_->GetAllCustomers();

  std::vector<std::string> existing_borrow_record_ids;
  for (domain::Customer customer : customer_list) {
    for (domain::BorrowRecord borrow_record : customer.borrow_records()) {
      existing_borrow_record_ids.push_back(borrow_record.id());
    }
  }

  int new_borrow_record_id = 1;
  while (true) {
    bool exists = std::ranges::find(existing_borrow_record_ids,
                                    std::to_string(new_borrow_record_id)) !=
                  existing_borrow_record_ids.end();
    if (exists) {
      new_borrow_record_id += 1;
    } else {
      return std::to_string(new_borrow_record_id);
    }
  }
}

std::string LibraryManager::GenerateCustomerId() const {
  std::vector<domain::Customer> customer_list =
      library_data_repository_->GetAllCustomers();
  std::vector<std::string> existing_customer_ids;
  for (domain::Customer customer : customer_list) {
    existing_customer_ids.push_back(customer.id());
  }

  int new_customer_id = 1;
  while (true) {
    bool exists = std::ranges::find(existing_customer_ids,
                                    std::to_string(new_customer_id)) !=
                  existing_customer_ids.end();
    if (exists) {
      new_customer_id += 1;
    } else {
      return std::to_string(new_customer_id);
    }
  }
}

std::string LibraryManager::GenerateTitleId() const {
  std::vector<const domain::Title*> title_list =
      library_data_repository_->GetAllTitles();

  std::vector<std::string> existing_title_ids;
  for (const domain::Title* title : title_list) {
    existing_title_ids.push_back(title->id());
  }

  int new_title_id = 1;
  while (true) {
    bool exists =
        std::ranges::find(existing_title_ids, std::to_string(new_title_id)) !=
        existing_title_ids.end();

    if (exists) {
      new_title_id += 1;
    } else {
      return std::to_string(new_title_id);
    }
  }
}

std::string LibraryManager::GenerateItemId() const {
  std::vector<domain::Item*> item_list =
      library_data_repository_->GetAllItems();

  std::vector<std::string> existing_item_ids;

  for (domain::Item* item : item_list) {
    if (item != nullptr) {
      existing_item_ids.push_back(item->id());
    }
  }

  int new_item_id = 1;

  while (true) {
    bool exists =
        std::ranges::find(existing_item_ids, std::to_string(new_item_id)) !=
        existing_item_ids.end();

    if (exists) {
      new_item_id += 1;
    } else {
      return std::to_string(new_item_id);
    }
  }
}

}  // namespace library_book_borrowing_manager::service
