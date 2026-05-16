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

#include "library_book_borrowing_manager/domain/borrow_record.h"

#include <chrono>
#include <optional>
#include <string>

namespace library_book_borrowing_manager::domain {

BorrowRecord::BorrowRecord(
    std::string id, std::chrono::system_clock::time_point start_date,
    std::chrono::system_clock::time_point due_date,
    std::optional<std::chrono::system_clock::time_point> return_date,
    Item* item)
    : id_(id),
      start_date_(start_date),
      due_date_(due_date),
      return_date_(return_date),
      item_(item) {
  item->set_is_available(false);
}

std::string BorrowRecord::id() const { return id_; }

std::chrono::system_clock::time_point BorrowRecord::start_date() const {
  return start_date_;
}

std::chrono::system_clock::time_point BorrowRecord::due_date() const {
  return due_date_;
}

std::optional<std::chrono::system_clock::time_point> BorrowRecord::return_date()
    const {
  return return_date_;
}

Item* BorrowRecord::item() const { return item_; }

void BorrowRecord::set_id(std::string id) { id_ = id; }

void BorrowRecord::set_start_date(
    std::chrono::system_clock::time_point start_date) {
  start_date_ = start_date;
}

void BorrowRecord::set_due_date(
    std::chrono::system_clock::time_point due_date) {
  due_date_ = due_date;
}

void BorrowRecord::set_return_date(
    std::chrono::system_clock::time_point return_date) {
  return_date_ = return_date;
}

void BorrowRecord::set_item(Item* item) { item_ = item; }

BorrowRecord::Status BorrowRecord::GetStatus() const {
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

  if (return_date().has_value()) {
    return Status::kReturned;
  }

  if (now < due_date()) {
    return Status::kActive;
  }

  return Status::kOverdue;
}

void BorrowRecord::Return(std::chrono::system_clock::time_point current_date) {
  set_return_date(current_date);
  item()->set_is_available(true);
}

void BorrowRecord::ExtendLoan(std::chrono::system_clock::time_point to_date) {
  set_due_date(to_date);
}

int BorrowRecord::GetDaysOverdue() const {
  if (return_date().has_value()) {
    return 0;
  }

  std::chrono::system_clock::time_point current_date =
      std::chrono::system_clock::now();

  if (current_date <= due_date()) {
    return 0;
  }

  auto overdue_duration = current_date - due_date();

  return std::chrono::duration_cast<std::chrono::hours>(overdue_duration)
             .count() /
         24;
}

double BorrowRecord::CalculateLateFee() const {
  const double kFeePerDay = 1.0;

  return GetDaysOverdue() * kFeePerDay;
}

}  // namespace library_book_borrowing_manager::domain
