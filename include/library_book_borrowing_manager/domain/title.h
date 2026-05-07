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
// Defines the abstract Title class to be inherited by other classes. A Title is
// the "indentity" (title, author, publisher) while an Item is a physical copy
// of a Title.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_TITLE_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_TITLE_H_

#include <string>

namespace library_book_borrowing_manager::domain {

class Title {
 public:
  virtual ~Title();

  std::string id() const;
  std::string name() const;
  std::string description() const;
  std::string author() const;
  std::string publisher() const;

  void set_id(std::string id);
  void set_name(std::string name);
  void set_description(std::string description);
  void set_author(std::string author);
  void set_publisher(std::string publisher);

  virtual std::string GetApaCitation() const = 0;

 protected:
  Title(std::string id, std::string name, std::string description,
        std::string author, std::string publisher);

  std::string id_;
  std::string name_;
  std::string description_;
  std::string author_;
  std::string publisher_;
};

}  // namespace library_book_borrowing_manager::domain

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_TITLE_H_
