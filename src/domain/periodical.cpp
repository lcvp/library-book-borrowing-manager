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

#include "library_book_borrowing_manager/domain/periodical.h"

#include <cctype>
#include <stdexcept>
#include <string>

#include "library_book_borrowing_manager/domain/title.h"

namespace library_book_borrowing_manager::domain {

Periodical::Periodical(std::string id, std::string name,
                       std::string description, std::string author,
                       std::string publisher, int publication_year,
                       std::string doi, std::string issn,
                       std::string publication_name, std::string volume,
                       std::string issue_number)
    : Title(id, name, description, author, publisher, publication_year, doi),
      publication_name_(publication_name),
      volume_(volume),
      issue_number_(issue_number) {
  if (!IsValidIssn(issn)) {
    throw std::invalid_argument("Invalid ISSN.");
  }
  issn_ = issn;
}

std::string Periodical::issn() const { return issn_; }

std::string Periodical::publication_name() const { return publication_name_; }

std::string Periodical::volume() const { return volume_; }

std::string Periodical::issue_number() const { return issue_number_; }

void Periodical::set_issn(std::string issn) {
  if (!IsValidIssn(issn)) {
    throw std::invalid_argument("Invalid ISSN.");
  }
  issn_ = issn;
}

void Periodical::set_publication_name(std::string publication_name) {
  publication_name_ = publication_name;
}

void Periodical::set_volume(std::string volume) { volume_ = volume; }

void Periodical::set_issue_number(std::string issue_number) {
  issue_number_ = issue_number;
}

bool Periodical::IsValidIssn(std::string issn) {
  if (issn.length() != 9) {
    return false;
  }

  if (issn[4] != '-') {
    return false;
  }

  for (int i = 0; i < (issn.length() - 1); i++) {
    if (i == 4) {
      continue;
    }

    if (!std::isdigit(issn[i])) {
      return false;
    }
  }

  if (!(std::isdigit(issn[8]) || (issn[8] == 'X'))) {
    return false;
  }

  return true;
}

}  // namespace library_book_borrowing_manager::domain
