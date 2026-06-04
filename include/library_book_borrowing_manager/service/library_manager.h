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

#include <chrono>
#include <string>
#include <vector>

#include "library_book_borrowing_manager/domain/repositories/library_data_repository.h"

namespace library_book_borrowing_manager::service {

class LibraryManager {
 public:
  LibraryManager(
      domain::repositories::LibraryDataRepository* library_data_repository);

  void set_library_date_repository(
      domain::repositories::LibraryDataRepository* library_data_repository);

  void CheckoutItems(std::string customer_id,
                     std::vector<std::string> item_ids);
  double CheckinItems(std::string customer_id,
                      std::vector<std::string> borrow_record_ids);

  void RegisterCustomer(std::string citizen_id, std::string name,
                        std::chrono::system_clock::time_point date_of_birth,
                        std::string email_address, std::string phone_number,
                        std::string address_building_number,
                        std::string address_street, std::string address_city,
                        std::string address_postal_code);

  void AddBook(std::string name, std::string description, std::string author,
               std::string publisher, int publication_year, std::string doi,
               std::string isbn, std::string edition);

  void AddJournal(std::string name, std::string description, std::string author,
                  std::string publisher, int publication_year, std::string doi,
                  std::string issn, std::string publication_name,
                  std::string volume, std::string issue_number,
                  std::string field_of_study, bool is_peer_reviewed);

  void AddMagazine(std::string name, std::string description,
                   std::string author, std::string publisher,
                   int publication_year, std::string doi, std::string issn,
                   std::string publication_name, std::string volume,
                   std::string issue_number, std::string category);

  void AddThesis(std::string name, std::string description, std::string author,
                 std::string publisher, int publication_year, std::string doi,
                 std::string university, std::string degree_level,
                 int defense_year, std::string supervisor_name);

  void AddItem(std::string title_id, char condition_input,
               std::string shelf_location);

  std::vector<domain::Customer> GetCustomerList() const;
  std::vector<domain::Item> GetItemList() const;
  std::vector<const domain::Title*> GetTitleList();
  std::vector<domain::BorrowRecord> GetBorrowRecordList() const;

  domain::Customer GetCustomerById(std::string customer_id) const;
  domain::BorrowRecord GetBorrowRecordById(std::string borrow_record_id) const;
  const domain::Title* GetTitleById(std::string title_id) const;
  domain::Item GetItemById(std::string item_id) const;

  void UpdateCustomer(std::string customer_id, std::string name,
                      std::string citizen_id,
                      std::chrono::system_clock::time_point date_of_birth,
                      std::string email_address, std::string phone_number,
                      std::string building_number, std::string street,
                      std::string city, std::string postal_code);

  void UpdateBook(std::string title_id, std::string name,
                  std::string description, std::string author,
                  std::string publisher, int publication_year, std::string doi,
                  std::string isbn, std::string edition);

  void UpdateJournal(std::string title_id, std::string name,
                     std::string description, std::string author,
                     std::string publisher, int publication_year,
                     std::string doi, std::string issn,
                     std::string publication_name, std::string volume,
                     std::string issue_number, std::string field_of_study,
                     bool is_peer_reviewed);

  void UpdateMagazine(std::string title_id, std::string name,
                      std::string description, std::string author,
                      std::string publisher, int publication_year,
                      std::string doi, std::string issn,
                      std::string publication_name, std::string volume,
                      std::string issue_number, std::string category);

  void UpdateThesis(std::string title_id, std::string name,
                    std::string description, std::string author,
                    std::string publisher, int publication_year,
                    std::string doi, std::string university,
                    std::string degree_level, int defense_year,
                    std::string supervisor_name);

  void UpdateItem(std::string item_id, std::string title_id,
                  domain::Item::Condition condition, std::string shelf_location,
                  bool is_available);

  void DeleteCustomer(std::string customer_id);
  void DeleteTitle(std::string title_id);
  void DeleteItem(std::string item_id);

 private:
  domain::repositories::LibraryDataRepository* library_data_repository_;

  std::string GenerateBorrowRecordId() const;
  std::string GenerateCustomerId() const;
  std::string GenerateTitleId() const;
  std::string GenerateItemId() const;
};

}  // namespace library_book_borrowing_manager::service

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_SERVICE_LIBRARY_MANAGER_H_
