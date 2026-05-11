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
// magazine.h
// -----------------------------------------------------------------------------
//
// This header file defines the Magazine class for Library Book Borrowing
// Manager.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_MAGAZINE_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_MAGAZINE_H_

#include <string>

#include "library_book_borrowing_manager/domain/periodical.h"

namespace library_book_borrowing_manager::domain {

class Magazine : public Periodical {
 public:
  Magazine(std::string id, std::string name, std::string description,
           std::string author, std::string publisher, int publication_year,
           std::string doi, std::string issn, std::string publication_name,
           std::string volume, std::string issue_number, std::string category);

  std::string category() const;

  void set_category(std::string category);

  std::string GetApaCitation() const override;

 private:
  std::string category_;
};

}  // namespace library_book_borrowing_manager::domain

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_MAGAZINE_H_
