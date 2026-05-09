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
// periodical.h
// -----------------------------------------------------------------------------
//
// This header file defines the Periodical class which is intended to inherit
// from Title.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_PERIODICAL_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_PERIODICAL_H_

#include <string>

#include "library_book_borrowing_manager/domain/title.h"

namespace library_book_borrowing_manager::domain {

class Periodical : public Title {
 public:
  Periodical(std::string id, std::string name, std::string description,
             std::string author, std::string publisher, std::string issn,
             std::string volume, std::string issue_number);

  std::string issn() const;
  std::string volume() const;
  std::string issue_number() const;

  void set_issn(std::string issn);
  void set_volume(std::string volume);
  void set_issue_number(std::string issue_number);

  static bool IsValidIssn(std::string issn);
  std::string GetApaCitation() const override = 0;

 protected:
  std::string issn_;
  std::string volume_;
  std::string issue_number_;
};

}  // namespace library_book_borrowing_manager::domain

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_PERIODICAL_H_
