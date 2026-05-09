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
// customer.h
// -----------------------------------------------------------------------------
//
// This header file defines the Customer class for Library Book Borrowing
// Manager.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_CUSTOMER_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_CUSTOMER_H_

#include <chrono>
#include <string>
#include <vector>

#include "library_book_borrowing_manager/domain/address.h"
#include "library_book_borrowing_manager/domain/borrow_record.h"
#include "library_book_borrowing_manager/domain/citizen_id.h"
#include "library_book_borrowing_manager/domain/email.h"
#include "library_book_borrowing_manager/domain/item.h"

namespace library_book_borrowing_manager::domain {

class Customer {
 public:
  Customer(std::string id, CitizenId citizen_id, std::string name,
           std::chrono::system_clock::time_point date_of_birth, Address address,
           Email email, std::string phone_number);

  std::string id() const;
  CitizenId citizen_id() const;
  std::string name() const;
  std::chrono::system_clock::time_point date_of_birth() const;
  Address address() const;
  Email email() const;
  std::string phone_number() const;

  void set_id(std::string id);
  void set_citizen_id(CitizenId citizen_id);
  void set_name(std::string name);
  void set_date_of_birth(std::chrono::system_clock::time_point date_of_birth);
  void set_address(Address address);
  void set_email(Email email);
  void set_phone_number(std::string phone_number);

  void Borrow(const Item& item,
              std::chrono::system_clock::time_point current_date);
  void Return(const Item& item,
              std::chrono::system_clock::time_point current_date);
  double GetTotalLateFee() const;
  bool CanBorrow() const;

 private:
  std::string id_;
  CitizenId citizen_id_;
  std::string name_;
  std::chrono::system_clock::time_point date_of_birth_;
  Address address_;
  Email email_;
  std::string phone_number_;
  std::vector<BorrowRecord> borrow_records_;
};

}  // namespace library_book_borrowing_manager::domain

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_CUSTOMER_H_
