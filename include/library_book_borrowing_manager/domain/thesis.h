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
// thesis.h
// -----------------------------------------------------------------------------
//
// This header file defines the Thesis class which inherits from Title.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_THESIS_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_THESIS_H_

#include <string>

#include "library_book_borrowing_manager/domain/title.h"

namespace library_book_borrowing_manager::domain {

class Thesis : public Title {
 public:
  Thesis(std::string id, std::string name, std::string description,
         std::string author, std::string publisher, int publication_year,
         std::string doi, std::string university, std::string degree_level,
         int defense_year, std::string supervisor_name);

  std::string university() const;
  std::string degree_level() const;
  int defense_year() const;
  std::string supervisor_name() const;

  void set_university(std::string university);
  void set_degree_level(std::string degree_level);
  void set_defense_year(int defense_year);
  void set_supervisor_name(std::string supervisor_name);

  std::string GetApaCitation() const override;

 private:
  std::string university_;
  std::string degree_level_;
  int defense_year_;
  std::string supervisor_name_;
};

}  // namespace library_book_borrowing_manager::domain

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_THESIS_H_
