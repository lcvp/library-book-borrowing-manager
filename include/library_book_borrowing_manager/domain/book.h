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
// Defines the Book class. Inherits from Title.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_BOOK_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_BOOK_H_

#include <string>

#include "library_book_borrowing_manager/domain/title.h"

namespace library_book_borrowing_manager::domain {

class Book : public Title {
 public:
  Book(std::string id, std::string name,
       std::string description, std::string author,
       std::string publisher, std::string isbn,
       std::string edition);

  std::string isbn() const;
  std::string edition() const;

  void set_isbn(std::string isbn);
  void set_edition(std::string edition);

  std::string GetApaCitation() const override;
  static bool IsValidIsbn(std::string isbn);

 private:
  std::string isbn_;
  std::string edition_;
};

}  // namespace library_book_borrowing_manager::domain

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_BOOK_H_
