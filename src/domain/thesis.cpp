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

#include "library_book_borrowing_manager/domain/thesis.h"

#include <string>

namespace library_book_borrowing_manager::domain {

Thesis::Thesis(std::string id, std::string name, std::string description,
               std::string author, std::string publisher, int publication_year,
               std::string doi, std::string university,
               std::string degree_level, int defense_year,
               std::string supervisor_name)
    : Title(id, name, description, author, publisher, publication_year, doi),
      university_(university),
      degree_level_(degree_level),
      defense_year_(defense_year),
      supervisor_name_(supervisor_name) {}

std::string Thesis::university() const { return university_; }

std::string Thesis::degree_level() const { return degree_level_; }

int Thesis::defense_year() const { return defense_year_; }

std::string Thesis::supervisor_name() const { return supervisor_name_; }

void Thesis::set_university(std::string university) {
  university_ = university;
}

void Thesis::set_degree_level(std::string degree_level) {
  degree_level_ = degree_level;
}

void Thesis::set_defense_year(int defense_year) {
  defense_year_ = defense_year;
}

void Thesis::set_supervisor_name(std::string supervisor_name) {
  supervisor_name_ = supervisor_name;
}

std::string Thesis::GetApaCitation() const {
  std::string result = author_ + ". (" + std::to_string(defense_year_) + "). ";
  result += name_ + " [";
  result += degree_level_ + " thesis, ";
  result += university_ + "]";

  if (!doi_.empty()) {
    result += ". " + doi_;
  }

  return result;
}

}  // namespace library_book_borrowing_manager::domain