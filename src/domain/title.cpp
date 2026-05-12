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

#include "library_book_borrowing_manager/domain/title.h"

#include <string>

namespace library_book_borrowing_manager::domain {

Title::~Title() = default;

std::string Title::id() const { return id_; }

std::string Title::name() const { return name_; }

std::string Title::description() const { return description_; }

std::string Title::author() const { return author_; }

std::string Title::publisher() const { return publisher_; }

int Title::publication_year() const { return publication_year_; }

std::string Title::doi() const { return doi_; }

void Title::set_id(std::string id) { id_ = id; }

void Title::set_name(std::string name) { name_ = name; }

void Title::set_description(std::string description) {
  description_ = description;
}

void Title::set_author(std::string author) { author_ = author; }

void Title::set_publisher(std::string publisher) { publisher_ = publisher; }

void Title::set_publication_year(int publication_year) {
  publication_year_ = publication_year;
}

void Title::set_doi(std::string doi) { doi_ = doi; }

Title::Title(std::string id, std::string name, std::string description,
             std::string author, std::string publisher, int publication_year,
             std::string doi)
    : id_(id),
      name_(name),
      description_(description),
      author_(author),
      publisher_(publisher),
      publication_year_(publication_year),
      doi_(doi) {}

}  // namespace library_book_borrowing_manager::domain
