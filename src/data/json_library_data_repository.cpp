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

#include "library_book_borrowing_manager/data/json_library_data_repository.h"

#include <chrono>
#include <cstdint>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

#include "library_book_borrowing_manager/domain/book.h"
#include "library_book_borrowing_manager/domain/borrow_record.h"
#include "library_book_borrowing_manager/domain/citizen_id.h"
#include "library_book_borrowing_manager/domain/customer.h"
#include "library_book_borrowing_manager/domain/email.h"
#include "library_book_borrowing_manager/domain/item.h"
#include "library_book_borrowing_manager/domain/journal.h"
#include "library_book_borrowing_manager/domain/magazine.h"
#include "library_book_borrowing_manager/domain/thesis.h"
#include "library_book_borrowing_manager/domain/title.h"

namespace library_book_borrowing_manager::data {

JsonLibraryDataRepository::JsonLibraryDataRepository(std::string file_path)
    : file_path_(file_path) {
  LoadAllFromFile();
}

std::string JsonLibraryDataRepository::file_path() const { return file_path_; }

void JsonLibraryDataRepository::set_file_path(std::string file_path) {
  file_path_ = file_path;
  LoadAllFromFile();
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
      SaveAllToFile();
      return;
    }
  }
  customers_.push_back(customer);
  SaveAllToFile();
}

void JsonLibraryDataRepository::RemoveCustomer(std::string id) {
  for (int i = 0; i < customers_.size(); i++) {
    if (customers_[i].id() == id) {
      customers_.erase(customers_.begin() + i);
      SaveAllToFile();
      return;
    }
  }
}

domain::Item* JsonLibraryDataRepository::GetItemById(std::string id) {
  for (domain::Item& item : items_) {
    if (item.id() == id) {
      return &item;
    }
  }
  throw std::invalid_argument("Invalid Item ID.");
}

std::vector<domain::Item*> JsonLibraryDataRepository::GetAllItems() {
  std::vector<domain::Item*> item_pointers;

  for (domain::Item& item : items_) {
    item_pointers.push_back(&item);
  }

  return item_pointers;
}

void JsonLibraryDataRepository::Save(const domain::Item& item) {
  for (domain::Item& existing_item : items_) {
    if (existing_item.id() == item.id()) {
      existing_item = item;
      SaveAllToFile();
      return;
    }
  }
  items_.push_back(item);
  SaveAllToFile();
}

void JsonLibraryDataRepository::RemoveItem(std::string id) {
  for (int i = 0; i < items_.size(); i++) {
    if (items_[i].id() == id) {
      items_.erase(items_.begin() + i);
      SaveAllToFile();
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
      existing_title->set_name(title->name());
      existing_title->set_description(title->description());
      existing_title->set_author(title->author());
      existing_title->set_publisher(title->publisher());
      existing_title->set_publication_year(title->publication_year());
      existing_title->set_doi(title->doi());

      domain::Book* existing_book =
          dynamic_cast<domain::Book*>(existing_title.get());
      domain::Book* new_book = dynamic_cast<domain::Book*>(title.get());

      if (existing_book != nullptr && new_book != nullptr) {
        existing_book->set_isbn(new_book->isbn());
        existing_book->set_edition(new_book->edition());

        SaveAllToFile();
        return;
      }

      domain::Journal* existing_journal =
          dynamic_cast<domain::Journal*>(existing_title.get());
      domain::Journal* new_journal =
          dynamic_cast<domain::Journal*>(title.get());

      if (existing_journal != nullptr && new_journal != nullptr) {
        existing_journal->set_issn(new_journal->issn());
        existing_journal->set_publication_name(new_journal->publication_name());
        existing_journal->set_volume(new_journal->volume());
        existing_journal->set_issue_number(new_journal->issue_number());
        existing_journal->set_field_of_study(new_journal->field_of_study());
        existing_journal->set_is_peer_reviewed(new_journal->is_peer_reviewed());

        SaveAllToFile();
        return;
      }

      domain::Magazine* existing_magazine =
          dynamic_cast<domain::Magazine*>(existing_title.get());
      domain::Magazine* new_magazine =
          dynamic_cast<domain::Magazine*>(title.get());

      if (existing_magazine != nullptr && new_magazine != nullptr) {
        existing_magazine->set_issn(new_magazine->issn());
        existing_magazine->set_publication_name(
            new_magazine->publication_name());
        existing_magazine->set_volume(new_magazine->volume());
        existing_magazine->set_issue_number(new_magazine->issue_number());
        existing_magazine->set_category(new_magazine->category());

        SaveAllToFile();
        return;
      }

      domain::Thesis* existing_thesis =
          dynamic_cast<domain::Thesis*>(existing_title.get());
      domain::Thesis* new_thesis = dynamic_cast<domain::Thesis*>(title.get());

      if (existing_thesis != nullptr && new_thesis != nullptr) {
        existing_thesis->set_university(new_thesis->university());
        existing_thesis->set_degree_level(new_thesis->degree_level());
        existing_thesis->set_defense_year(new_thesis->defense_year());
        existing_thesis->set_supervisor_name(new_thesis->supervisor_name());

        SaveAllToFile();
        return;
      }

      throw std::invalid_argument(
          "Cannot update title because the title type changed.");
    }
  }

  titles_.push_back(std::move(title));
  SaveAllToFile();
}

void JsonLibraryDataRepository::RemoveTitle(std::string id) {
  for (int i = 0; i < titles_.size(); i++) {
    if (titles_[i]->id() == id) {
      titles_.erase(titles_.begin() + i);
      SaveAllToFile();
      return;
    }
  }
}

void JsonLibraryDataRepository::LoadAllFromFile() {
  std::ifstream f(file_path());
  if (!f.is_open()) {
    return;
  }

  if (f.peek() == std::ifstream::traits_type::eof()) {
    return;
  }

  nlohmann::json data = nlohmann::json::parse(f);

  titles_.clear();
  items_.clear();
  customers_.clear();

  // The load order matters here. Since Customers depends on Items
  // (BorrowRecords store pointers to Items) and Items depends on Titles, Titles
  // must be loaded first, then Items, then Customers.

  LoadBooksFromFile(data);
  LoadJournalsFromFile(data);
  LoadMagazinesFromFile(data);
  LoadThesesFromFile(data);

  LoadItemsFromFile(data);

  LoadCustomersFromFile(data);
}

void JsonLibraryDataRepository::SaveAllToFile() {
  nlohmann::json data;

  SaveTitlesToJsonObject(data);
  SaveItemsToJsonObject(data);
  SaveCustomersToJsonObject(data);

  std::ofstream f(file_path());
  if (!f.is_open()) {
    throw std::runtime_error("Cannot open save file: " + file_path());
  }

  f << data.dump(2);
}

void JsonLibraryDataRepository::LoadBooksFromFile(nlohmann::json& data) {
  for (int i = 0; i < data["Titles"]["Books"].size(); i++) {
    nlohmann::json book_data = data["Titles"]["Books"][i];
    std::string id = book_data["id"];
    std::string name = book_data["name"];
    std::string description = book_data["description"];
    std::string author = book_data["author"];
    std::string publisher = book_data["publisher"];
    int publication_year = book_data["publication_year"];
    std::string doi = book_data["doi"];
    std::string isbn = book_data["isbn"];
    std::string edition = book_data["edition"];
    titles_.push_back(
        std::make_unique<domain::Book>(id, name, description, author, publisher,
                                       publication_year, doi, isbn, edition));
  }
}

void JsonLibraryDataRepository::LoadJournalsFromFile(nlohmann::json& data) {
  for (int i = 0; i < data["Titles"]["Journals"].size(); i++) {
    nlohmann::json journal_data = data["Titles"]["Journals"][i];
    std::string id = journal_data["id"];
    std::string name = journal_data["name"];
    std::string description = journal_data["description"];
    std::string author = journal_data["author"];
    std::string publisher = journal_data["publisher"];
    int publication_year = journal_data["publication_year"];
    std::string doi = journal_data["doi"];
    std::string issn = journal_data["issn"];
    std::string publication_name = journal_data["publication_name"];
    std::string volume = journal_data["volume"];
    std::string issue_number = journal_data["issue_number"];
    std::string field_of_study = journal_data["field_of_study"];
    bool is_peer_reviewed = journal_data["is_peer_reviewed"];

    titles_.push_back(std::make_unique<domain::Journal>(
        id, name, description, author, publisher, publication_year, doi, issn,
        publication_name, volume, issue_number, field_of_study,
        is_peer_reviewed));
  }
}

void JsonLibraryDataRepository::LoadMagazinesFromFile(nlohmann::json& data) {
  for (int i = 0; i < data["Titles"]["Magazines"].size(); i++) {
    nlohmann::json magazine_data = data["Titles"]["Magazines"][i];
    std::string id = magazine_data["id"];
    std::string name = magazine_data["name"];
    std::string description = magazine_data["description"];
    std::string author = magazine_data["author"];
    std::string publisher = magazine_data["publisher"];
    int publication_year = magazine_data["publication_year"];
    std::string doi = magazine_data["doi"];
    std::string issn = magazine_data["issn"];
    std::string publication_name = magazine_data["publication_name"];
    std::string volume = magazine_data["volume"];
    std::string issue_number = magazine_data["issue_number"];
    std::string category = magazine_data["category"];

    titles_.push_back(std::make_unique<domain::Magazine>(
        id, name, description, author, publisher, publication_year, doi, issn,
        publication_name, volume, issue_number, category));
  }
}

void JsonLibraryDataRepository::LoadThesesFromFile(nlohmann::json& data) {
  for (int i = 0; i < data["Titles"]["Theses"].size(); i++) {
    nlohmann::json thesis_data = data["Titles"]["Theses"][i];
    std::string id = thesis_data["id"];
    std::string name = thesis_data["name"];
    std::string description = thesis_data["description"];
    std::string author = thesis_data["author"];
    std::string publisher = thesis_data["publisher"];
    int publication_year = thesis_data["publication_year"];
    std::string doi = thesis_data["doi"];
    std::string university = thesis_data["university"];
    std::string degree_level = thesis_data["degree_level"];
    int defense_year = thesis_data["defense_year"];
    std::string supervisor_name = thesis_data["supervisor_name"];

    titles_.push_back(std::make_unique<domain::Thesis>(
        id, name, description, author, publisher, publication_year, doi,
        university, degree_level, defense_year, supervisor_name));
  }
}

void JsonLibraryDataRepository::LoadItemsFromFile(nlohmann::json& data) {
  for (int i = 0; i < data["Items"].size(); i++) {
    nlohmann::json item_data = data["Items"][i];

    std::string id = item_data["id"];

    const domain::Title* title = nullptr;
    std::string title_id = item_data["title_id"];
    for (int ii = 0; ii < titles_.size(); ii++) {
      if (titles_[ii]->id() == title_id) {
        title = titles_[ii].get();
        break;
      }
    }
    domain::Item::Condition condition =
        item_data["condition"].get<domain::Item::Condition>();
    std::string shelf_location = item_data["shelf_location"];
    bool is_available = item_data["is_available"];

    domain::Item item(id, title, condition, shelf_location, is_available);
    items_.push_back(item);
  }
}

void JsonLibraryDataRepository::LoadCustomersFromFile(nlohmann::json& data) {
  for (int i = 0; i < data["Customers"].size(); i++) {
    nlohmann::json customer_data = data["Customers"][i];

    std::string id = customer_data["id"];
    domain::CitizenId citizen_id(customer_data["citizen_id"]);
    std::string name = customer_data["name"];
    std::chrono::system_clock::time_point date_of_birth{std::chrono::seconds{
        customer_data["date_of_birth"].get<std::int64_t>()}};

    std::string building_number = customer_data["Address"]["building_number"];
    std::string street = customer_data["Address"]["street"];
    std::string city = customer_data["Address"]["city"];
    std::string postal_code = customer_data["Address"]["postal_code"];
    domain::Address address(building_number, street, city, postal_code);

    domain::Email email(customer_data["email_address"]);
    std::string phone_number = customer_data["phone_number"];

    domain::Customer customer(id, citizen_id, name, date_of_birth, address,
                              email, phone_number);

    for (int ii = 0; ii < customer_data["borrow_records"].size(); ii++) {
      nlohmann::json borrow_record_data = customer_data["borrow_records"][ii];

      std::string borrow_record_id = borrow_record_data["id"];
      std::chrono::system_clock::time_point start_date{std::chrono::seconds{
          borrow_record_data["start_date"].get<std::int64_t>()}};
      std::chrono::system_clock::time_point due_date{std::chrono::seconds{
          borrow_record_data["due_date"].get<std::int64_t>()}};

      std::optional<std::chrono::system_clock::time_point> return_date;
      if (borrow_record_data.contains("return_date") &&
          !borrow_record_data["return_date"].is_null()) {
        return_date =
            std::chrono::system_clock::time_point{std::chrono::seconds{
                borrow_record_data["return_date"].get<std::int64_t>()}};
      }

      std::string item_id = borrow_record_data["item_id"];
      domain::Item* item = nullptr;
      for (int iii = 0; iii < items_.size(); iii++) {
        if (items_[iii].id() == item_id) {
          item = &items_[iii];
          break;
        }
      }
      domain::BorrowRecord borrow_record(borrow_record_id, start_date, due_date,
                                         return_date, item);

      customer.Borrow(borrow_record);
    }

    customers_.push_back(customer);
  }
}

void JsonLibraryDataRepository::SaveTitlesToJsonObject(nlohmann::json& data) {
  data["Titles"]["Books"] = nlohmann::json::array();
  data["Titles"]["Journals"] = nlohmann::json::array();
  data["Titles"]["Magazines"] = nlohmann::json::array();
  data["Titles"]["Theses"] = nlohmann::json::array();

  for (int i = 0; i < titles_.size(); i++) {
    const domain::Title* title = titles_[i].get();

    nlohmann::json title_data;
    title_data["id"] = title->id();
    title_data["name"] = title->name();
    title_data["description"] = title->description();
    title_data["author"] = title->author();
    title_data["publisher"] = title->publisher();
    title_data["publication_year"] = title->publication_year();
    title_data["doi"] = title->doi();

    const domain::Book* book = dynamic_cast<const domain::Book*>(title);
    const domain::Journal* journal =
        dynamic_cast<const domain::Journal*>(title);
    const domain::Magazine* magazine =
        dynamic_cast<const domain::Magazine*>(title);
    const domain::Thesis* thesis = dynamic_cast<const domain::Thesis*>(title);

    if (book != nullptr) {
      title_data["isbn"] = book->isbn();
      title_data["edition"] = book->edition();

      data["Titles"]["Books"].push_back(title_data);
    }

    else if (journal != nullptr) {
      title_data["issn"] = journal->issn();
      title_data["publication_name"] = journal->publication_name();
      title_data["volume"] = journal->volume();
      title_data["issue_number"] = journal->issue_number();
      title_data["field_of_study"] = journal->field_of_study();
      title_data["is_peer_reviewed"] = journal->is_peer_reviewed();

      data["Titles"]["Journals"].push_back(title_data);
    }

    else if (magazine != nullptr) {
      title_data["issn"] = magazine->issn();
      title_data["publication_name"] = magazine->publication_name();
      title_data["volume"] = magazine->volume();
      title_data["issue_number"] = magazine->issue_number();
      title_data["category"] = magazine->category();

      data["Titles"]["Magazines"].push_back(title_data);
    }

    else if (thesis != nullptr) {
      title_data["university"] = thesis->university();
      title_data["degree_level"] = thesis->degree_level();
      title_data["defense_year"] = thesis->defense_year();
      title_data["supervisor_name"] = thesis->supervisor_name();

      data["Titles"]["Theses"].push_back(title_data);
    }
  }
}

void JsonLibraryDataRepository::SaveItemsToJsonObject(nlohmann::json& data) {
  data["Items"] = nlohmann::json::array();

  for (int i = 0; i < items_.size(); i++) {
    const domain::Item& item = items_[i];

    nlohmann::json item_data;
    item_data["id"] = item.id();

    if (item.title() != nullptr) {
      item_data["title_id"] = item.title()->id();
    } else {
      item_data["title_id"] = nullptr;
    }

    item_data["condition"] = item.condition();
    item_data["shelf_location"] = item.shelf_location();
    item_data["is_available"] = item.is_available();

    data["Items"].push_back(item_data);
  }
}

void JsonLibraryDataRepository::SaveCustomersToJsonObject(
    nlohmann::json& data) {
  data["Customers"] = nlohmann::json::array();

  for (int i = 0; i < customers_.size(); i++) {
    const domain::Customer& customer = customers_[i];

    nlohmann::json customer_data;
    customer_data["id"] = customer.id();
    customer_data["citizen_id"] = customer.citizen_id().id();
    customer_data["name"] = customer.name();

    customer_data["date_of_birth"] =
        std::chrono::duration_cast<std::chrono::seconds>(
            customer.date_of_birth().time_since_epoch())
            .count();

    customer_data["Address"]["building_number"] =
        customer.address().building_number();
    customer_data["Address"]["street"] = customer.address().street();
    customer_data["Address"]["city"] = customer.address().city();
    customer_data["Address"]["postal_code"] = customer.address().postal_code();

    customer_data["email_address"] = customer.email().email_address();
    customer_data["phone_number"] = customer.phone_number();

    customer_data["borrow_records"] = nlohmann::json::array();

    for (int ii = 0; ii < customer.borrow_records().size(); ii++) {
      domain::BorrowRecord borrow_record = customer.borrow_records()[ii];

      nlohmann::json borrow_record_data;
      borrow_record_data["id"] = borrow_record.id();

      borrow_record_data["start_date"] =
          std::chrono::duration_cast<std::chrono::seconds>(
              borrow_record.start_date().time_since_epoch())
              .count();

      borrow_record_data["due_date"] =
          std::chrono::duration_cast<std::chrono::seconds>(
              borrow_record.due_date().time_since_epoch())
              .count();

      if (borrow_record.return_date().has_value()) {
        borrow_record_data["return_date"] =
            std::chrono::duration_cast<std::chrono::seconds>(
                borrow_record.return_date().value().time_since_epoch())
                .count();
      } else {
        borrow_record_data["return_date"] = nullptr;
      }

      if (borrow_record.item() != nullptr) {
        borrow_record_data["item_id"] = borrow_record.item()->id();
      } else {
        borrow_record_data["item_id"] = nullptr;
      }

      customer_data["borrow_records"].push_back(borrow_record_data);
    }

    data["Customers"].push_back(customer_data);
  }
}

}  // namespace library_book_borrowing_manager::data
