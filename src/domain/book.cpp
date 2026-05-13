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

#include "library_book_borrowing_manager/domain/book.h"

#include <string>

namespace library_book_borrowing_manager::domain {

Book::Book(std::string id, std::string name, std::string description,
           std::string author, std::string publisher, int publication_year,
           std::string doi, std::string isbn, std::string edition)
    : Title(id, name, description, author, publisher, publication_year, doi),
      isbn_(isbn),
      edition_(edition) {}

std::string Book::isbn() const { return isbn_; }

std::string Book::edition() const { return edition_; }

void Book::set_isbn(std::string isbn) { isbn_ = isbn; }

void Book::set_edition(std::string edition) { edition_ = edition; }

std::string Book::GetApaCitation() const {
  std::string citation;

  citation += author();
  citation += ". (";
  citation += std::to_string(publication_year());
  citation += "). ";
  citation += name();
  citation += " (";
  citation += edition_;
  citation += "). ";
  citation += publisher();
  citation += ".";

  return citation;
}

bool Book::IsValidIsbn(std::string isbn) {
  int digit_count = 0;

  for (char c : isbn) {
    if (std::isdigit(c)) {
      digit_count++;
    }
  }

  return digit_count == 10 || digit_count == 13;
}

}  // namespace library_book_borrowing_manager::domain