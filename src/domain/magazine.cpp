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

#include "library_book_borrowing_manager/domain/magazine.h"

#include <string>

#include "library_book_borrowing_manager/domain/periodical.h"

namespace library_book_borrowing_manager::domain {

Magazine::Magazine(std::string id, std::string name, std::string description,
                   std::string author, std::string publisher,
                   int publication_year, std::string doi, std::string issn,
                   std::string publication_name, std::string volume,
                   std::string issue_number, std::string category)
    : Periodical(id, name, description, author, publisher, publication_year,
                 doi, issn, publication_name, volume, issue_number),
      category_(category) {};

std::string Magazine::category() const { return category_; }

void Magazine::set_category(std::string category) { category_ = category; }

std::string Magazine::GetApaCitation() const {
  std::string citation =
      author() + " (" + std::to_string(publication_year()) + "). ";

  citation += name() + ". ";

  citation +=
      publication_name() + ", " + volume() + "(" + issue_number() + ").";

  if (!doi().empty()) {
    citation += " https://doi.org/" + doi();
  }

  return citation;
}

}  // namespace library_book_borrowing_manager::domain
