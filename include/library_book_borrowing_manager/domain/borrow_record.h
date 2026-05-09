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
// borrow_record.h
// -----------------------------------------------------------------------------
//
// This header file defines the BorrowRecord class for Library Book Borrowing
// Manager which is intended to be used by the Customer class.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_BORROW_RECORD_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_BORROW_RECORD_H_

#include <chrono>
#include <string>

#include "library_book_borrowing_manager/domain/item.h"

namespace library_book_borrowing_manager::domain {

class BorrowRecord {
 public:
  enum class Status { kActive, kReturned, kOverdue, kLost };

  BorrowRecord(std::string id, std::chrono::system_clock::time_point start_date,
               std::chrono::system_clock::time_point due_date,
               std::chrono::system_clock::time_point return_date,
               const Item* item);

  std::string id() const;
  std::chrono::system_clock::time_point start_date() const;
  std::chrono::system_clock::time_point due_date() const;
  std::chrono::system_clock::time_point return_date() const;
  const Item* item() const;

  void set_id(std::string id);
  void set_start_date(std::chrono::system_clock::time_point start_date);
  void set_due_date(std::chrono::system_clock::time_point due_date);
  void set_return_date(std::chrono::system_clock::time_point return_date);
  void set_item(const Item* item);

  Status GetStatus() const;
  void Return(std::chrono::system_clock::time_point current_date);
  void ExtendLoan(std::chrono::system_clock::time_point to_date);
  int GetDaysOverdue() const;
  double CalculateLateFee() const;

 private:
  std::string id_;
  std::chrono::system_clock::time_point start_date_;
  std::chrono::system_clock::time_point due_date_;
  std::chrono::system_clock::time_point return_date_;
  const Item* item_;
};

}  // namespace library_book_borrowing_manager::domain

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_BORROW_RECORD_H_
