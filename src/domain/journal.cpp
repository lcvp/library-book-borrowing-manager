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

#include "library_book_borrowing_manager/domain/journal.h"

namespace library_book_borrowing_manager::domain {

Journal::Journal(
    std::string id, std::string name, std::string description,
    std::string author, std::string publisher, int publication_year,
    std::string doi, std::string issn,
    std::string publication_name, std::string volume,
    std::string issue_number, std::string field_of_study,
    bool is_peer_reviewed)
    : Periodical(id, name, description, author, publisher,
                 publication_year, doi, issn,
                 publication_name, volume, issue_number),
      field_of_study_(field_of_study),
      is_peer_reviewed_(is_peer_reviewed) {}

std::string Journal::field_of_study() const {
  return field_of_study_;
}

bool Journal::is_peer_reviewed() const {
  return is_peer_reviewed_;
}

void Journal::set_field_of_study(
    std::string field_of_study) {
  field_of_study_ = field_of_study;
}

void Journal::set_is_peer_reviewed(
    bool is_peer_reviewed) {
  is_peer_reviewed_ = is_peer_reviewed;
}

std::string Journal::GetApaCitation() const {
  return author() + " (" +
         std::to_string(publication_year()) +
         "). " + name() + ". " +
         publication_name() + ", " +
         volume() + "(" +
         issue_number() + ").";
}

}  // namespace library_book_borrowing_manager::domain
