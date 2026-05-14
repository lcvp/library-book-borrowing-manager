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

#include <stdexcept>
#include <string>

namespace library_book_borrowing_manager::domain {

Book::Book(std::string id, std::string name, std::string description,
           std::string author, std::string publisher, int publication_year,
           std::string doi, std::string isbn, std::string edition)
    : Title(id, name, description, author, publisher, publication_year, doi),
      edition_(edition) {
  if (!IsValidIsbn(isbn)) {
    throw std::invalid_argument("Invalid ISBN.");
  }
  isbn_ = isbn;
}

std::string Book::isbn() const { return isbn_; }

std::string Book::edition() const { return edition_; }

void Book::set_isbn(std::string isbn) {
  if (!IsValidIsbn(isbn)) {
    throw std::invalid_argument("Invalid ISBN.");
  }
  isbn_ = isbn;
}

void Book::set_edition(std::string edition) { edition_ = edition; }

std::string Book::GetApaCitation() const {
  std::string citation =
      author() + " (" + std::to_string(publication_year()) + "). " + name();

  if (!edition().empty()) {
    citation += " (" + edition() + ")";
  }

  citation += ". " + publisher();

  if (!doi().empty()) {
    citation += ". " + doi();
  } else {
    citation += ".";
  }

  return citation;
}

bool Book::IsValidIsbn(std::string isbn) {
  if (!(isbn.length() == 10 || isbn.length() == 13)) {
    return false;
  }

  for (int i = 0; i < isbn.length(); i++) {
    if (isbn.length() == 10 && i == 9) {
      if (!(std::isdigit(isbn[i]) || isbn[i] == 'X')) {
        return false;
      }
    } else {
      if (!std::isdigit(isbn[i])) {
        return false;
      }
    }
  }

  return true;
}

}  // namespace library_book_borrowing_manager::domain
