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

#include "library_book_borrowing_manager/domain/customer.h"

#include <chrono>
#include <string>
#include <vector>

#include "library_book_borrowing_manager/domain/address.h"
#include "library_book_borrowing_manager/domain/borrow_record.h"
#include "library_book_borrowing_manager/domain/citizen_id.h"
#include "library_book_borrowing_manager/domain/email.h"
#include "library_book_borrowing_manager/domain/item.h"

namespace library_book_borrowing_manager::domain {
Customer::Customer(std::string id, CitizenId citizen_id, std::string name,
                   std::chrono::system_clock::time_point date_of_birth,
                   Address address, Email email, std::string phone_number)
    : id_(id),
      citizen_id_(citizen_id),
      name_(name),
      date_of_birth_(date_of_birth),
      address_(address),
      email_(email),
      phone_number_(phone_number) {}

std::string Customer::id() const { return id_; }

CitizenId Customer::citizen_id() const { return citizen_id_; }

std::string Customer::name() const { return name_; }

std::chrono::system_clock::time_point Customer::date_of_birth() const {
  return date_of_birth_;
}

Address Customer::address() const { return address_; }

Email Customer::email() const { return email_; }

std::string Customer::phone_number() const { return phone_number_; }

std::vector<BorrowRecord> Customer::borrow_records() const {
  return borrow_records_;
}

void Customer::set_id(std::string id) { id_ = id; }

void Customer::set_citizen_id(CitizenId citizen_id) {
  citizen_id_ = citizen_id;
}

void Customer::set_name(std::string name) { name_ = name; }

void Customer::set_date_of_birth(
    std::chrono::system_clock::time_point date_of_birth) {
  date_of_birth_ = date_of_birth;
}

void Customer::set_address(Address address) { address_ = address; }

void Customer::set_email(Email email) { email_ = email; }

void Customer::set_phone_number(std::string phone_number) {
  phone_number_ = phone_number;
}

void Customer::Borrow(BorrowRecord new_record) {
  if (!CanBorrow()) {
    throw std::runtime_error(
        "Customer cannot borrow due to having overdue items.");
  }
  borrow_records_.push_back(new_record);
}

void Customer::Return(Item& item,
                      std::chrono::system_clock::time_point current_date) {
  for (BorrowRecord& record : borrow_records_) {
    if (record.item()->id() == item.id() && !record.return_date().has_value()) {
      record.Return(current_date);
      break;
    }
  }
}

double Customer::GetTotalLateFee() const {
  double total_fee = 0.0;
  for (const BorrowRecord& record : borrow_records()) {
    total_fee += record.CalculateLateFee();
  }
  return total_fee;
}

bool Customer::CanBorrow() const {
  for (const BorrowRecord& record : borrow_records()) {
    if (record.GetStatus() == BorrowRecord::Status::kOverdue) {
      return false;
    }
  }
  return true;
}

}  // namespace library_book_borrowing_manager::domain
