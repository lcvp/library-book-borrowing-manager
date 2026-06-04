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

#include "library_book_borrowing_manager/presentation/views/titles_view.h"

#include "library_book_borrowing_manager/domain/title.h"
#include "library_book_borrowing_manager/presentation/views/console_view.h"

namespace library_book_borrowing_manager::presentation::views {

char TitlesView::PrintManageTitlesOptions() const {
  PrintHeader("Manage Titles");

  std::map<std::string, std::string> options = {
      {"1", "Add Title"},
      {"2", "Edit Title"},
      {"3", "Delete Title"},
      {"4", "Manage Items"},
      {"Any other key", "Back To Main Menu"}};
  PrintList(options);

  PrintDivider();
  char user_input = PromptForString("Enter: ")[0];
  return user_input;
}

char TitlesView::PrintAddTitleOptions() const {
  PrintHeader("What type of material?");

  std::map<std::string, std::string> options = {
      {"1", "Book"}, {"2", "Journal"}, {"3", "Magazine"}, {"4", "Thesis"}};
  PrintList(options);

  PrintDivider();
  char user_input = PromptForString("Enter: ")[0];
  return user_input;
}

std::string TitlesView::PrintTitleList(
    const std::vector<const domain::Title*>& titles, bool get_input) const {
  PrintHeader("Available Titles");

  std::vector<std::string> title_list;

  for (const domain::Title* title : titles) {
    if (title != nullptr) {
      title_list.push_back(title->id() + " - " + title->GetApaCitation());
    }
  }

  PrintList(title_list);

  PrintDivider();
  std::string user_input;

  if (get_input) {
    user_input = PromptForString("Enter Title ID: ");
  }

  return user_input;
}

char TitlesView::PrintItemConditionOptions() const {
  PrintHeader("Select Item Condition");

  std::vector<std::string> condition_options;

  condition_options.push_back("1. Factory New");
  condition_options.push_back("2. Minimal Wear");
  condition_options.push_back("3. Normal Wear");
  condition_options.push_back("4. Well Worn");
  condition_options.push_back("5. Damaged");

  PrintList(condition_options);

  PrintDivider();

  return PromptForString("Enter Condition: ")[0];
}

char TitlesView::PrintManageItemsOptions() const {
  PrintHeader("Manage Items");

  std::map<std::string, std::string> options = {
      {"1", "Add Item"},
      {"2", "Edit Item"},
      {"3", "Delete Item"},
      {"Any other key", "Back To Main Menu"}};

  PrintList(options);

  PrintDivider();

  char user_input = PromptForString("Enter: ")[0];

  return user_input;
}

std::string TitlesView::PromptForName(std::string current_name) const {
  std::string input = PromptForString("Enter Name [" + current_name + "]: ");

  if (input.empty()) {
    return current_name;
  }

  return input;
}

std::string TitlesView::PromptForDescription(
    std::string current_description) const {
  std::string input =
      PromptForString("Enter Description [" + current_description + "]: ");

  if (input.empty()) {
    return current_description;
  }

  return input;
}

std::string TitlesView::PromptForAuthor(std::string current_author) const {
  std::string input =
      PromptForString("Enter Author [" + current_author + "]: ");

  if (input.empty()) {
    return current_author;
  }

  return input;
}

std::string TitlesView::PromptForPublisher(
    std::string current_publisher) const {
  std::string input =
      PromptForString("Enter Publisher [" + current_publisher + "]: ");

  if (input.empty()) {
    return current_publisher;
  }

  return input;
}

int TitlesView::PromptForPublicationYear(int current_publication_year) const {
  std::string input =
      PromptForString("Enter Publication Year [" +
                      std::to_string(current_publication_year) + "]: ");

  if (input.empty()) {
    return current_publication_year;
  }

  return std::stoi(input);
}

std::string TitlesView::PromptForDoi(std::string current_doi) const {
  std::string input = PromptForString("Enter DOI [" + current_doi + "]: ");

  if (input.empty()) {
    return current_doi;
  }

  return input;
}

std::string TitlesView::PromptForIsbn(std::string current_isbn) const {
  std::string input = PromptForString("Enter ISBN [" + current_isbn + "]: ");

  if (input.empty()) {
    return current_isbn;
  }

  return input;
}

std::string TitlesView::PromptForEdition(std::string current_edition) const {
  std::string input =
      PromptForString("Enter Edition [" + current_edition + "]: ");

  if (input.empty()) {
    return current_edition;
  }

  return input;
}

std::string TitlesView::PromptForIssn(std::string current_issn) const {
  std::string input = PromptForString("Enter ISSN [" + current_issn + "]: ");

  if (input.empty()) {
    return current_issn;
  }

  return input;
}

std::string TitlesView::PromptForPublicationName(
    std::string current_publication_name) const {
  std::string input = PromptForString("Enter Publication Name [" +
                                      current_publication_name + "]: ");

  if (input.empty()) {
    return current_publication_name;
  }

  return input;
}

std::string TitlesView::PromptForVolume(std::string current_volume) const {
  std::string input =
      PromptForString("Enter Volume [" + current_volume + "]: ");

  if (input.empty()) {
    return current_volume;
  }

  return input;
}

std::string TitlesView::PromptForIssueNumber(
    std::string current_issue_number) const {
  std::string input =
      PromptForString("Enter Issue Number [" + current_issue_number + "]: ");

  if (input.empty()) {
    return current_issue_number;
  }

  return input;
}

std::string TitlesView::PromptForFieldOfStudy(
    std::string current_field_of_study) const {
  std::string input = PromptForString("Enter Field Of Study [" +
                                      current_field_of_study + "]: ");

  if (input.empty()) {
    return current_field_of_study;
  }

  return input;
}

bool TitlesView::PromptForIsPeerReviewed(bool current_is_peer_reviewed) const {
  std::string current_value;

  if (current_is_peer_reviewed) {
    current_value = "y";
  } else {
    current_value = "n";
  }

  std::string input =
      PromptForString("Is Peer Reviewed? (y/n) [" + current_value + "]: ");

  if (input.empty()) {
    return current_is_peer_reviewed;
  }

  if (input == "y" || input == "Y") {
    return true;
  }

  return false;
}

std::string TitlesView::PromptForCategory(std::string current_category) const {
  std::string input =
      PromptForString("Enter Category [" + current_category + "]: ");

  if (input.empty()) {
    return current_category;
  }

  return input;
}

std::string TitlesView::PromptForUniversity(
    std::string current_university) const {
  std::string input =
      PromptForString("Enter University [" + current_university + "]: ");

  if (input.empty()) {
    return current_university;
  }

  return input;
}

std::string TitlesView::PromptForDegreeLevel(
    std::string current_degree_level) const {
  std::string input =
      PromptForString("Enter Degree Level [" + current_degree_level + "]: ");

  if (input.empty()) {
    return current_degree_level;
  }

  return input;
}

int TitlesView::PromptForDefenseYear(int current_defense_year) const {
  std::string input = PromptForString(
      "Enter Defense Year [" + std::to_string(current_defense_year) + "]: ");

  if (input.empty()) {
    return current_defense_year;
  }

  return std::stoi(input);
}

std::string TitlesView::PromptForSupervisorName(
    std::string current_supervisor_name) const {
  std::string input = PromptForString("Enter Supervisor Name [" +
                                      current_supervisor_name + "]: ");

  if (input.empty()) {
    return current_supervisor_name;
  }

  return input;
}

std::string TitlesView::PrintItemList(const std::vector<domain::Item> items,
                                      bool get_input) const {
  PrintHeader("Items");

  std::vector<std::string> item_list = ItemListToString(items);

  PrintList(item_list);

  PrintDivider();

  std::string user_input;

  if (get_input) {
    user_input = PromptForString("Enter Item ID: ");
  }

  return user_input;
}

std::string TitlesView::ItemToString(domain::Item item) const {
  std::string item_as_string;

  item_as_string += "Item ID: " + item.id();
  item_as_string += " | ";
  item_as_string += "Shelf location: " + item.shelf_location();
  item_as_string += " | ";
  item_as_string += item.title()->GetApaCitation();

  item_as_string += " | Condition: ";
  switch (item.condition()) {
    case domain::Item::Condition::kFactoryNew:
      item_as_string += "Factory New";
      break;
    case domain::Item::Condition::kMinimalWear:
      item_as_string += "Minimal Wear";
      break;
    case domain::Item::Condition::kNormalWear:
      item_as_string += "Normal Wear";
      break;
    case domain::Item::Condition::kWellWorn:
      item_as_string += "Well Worn";
      break;
    case domain::Item::Condition::kDamaged:
      item_as_string += "Damaged";
      break;
  }

  item_as_string += " | Status: ";

  if (item.is_available()) {
    item_as_string += "Available";
  } else {
    item_as_string += "Borrowed";
  }

  return item_as_string;
}

std::vector<std::string> TitlesView::ItemListToString(
    std::vector<domain::Item> item_list) const {
  std::vector<std::string> string_item_list;
  for (domain::Item item : item_list) {
    string_item_list.push_back(ItemToString(item));
  }
  return string_item_list;
}

std::string TitlesView::PromptForTitleId(
    const std::vector<const domain::Title*>& titles,
    std::string current_title_id) const {
  PrintHeader("Available Titles");

  std::vector<std::string> title_list;

  for (const domain::Title* title : titles) {
    if (title != nullptr) {
      title_list.push_back(title->id() + " - " + title->GetApaCitation());
    }
  }

  PrintList(title_list);

  PrintDivider();

  std::string input =
      PromptForString("Enter Title ID [" + current_title_id + "]: ");

  if (input.empty()) {
    return current_title_id;
  }

  return input;
}

domain::Item::Condition TitlesView::PromptForItemCondition(
    domain::Item::Condition current_condition) const {
  PrintHeader("Select Item Condition");

  std::vector<std::string> condition_options;

  condition_options.push_back("1. Factory New");
  condition_options.push_back("2. Minimal Wear");
  condition_options.push_back("3. Normal Wear");
  condition_options.push_back("4. Well Worn");
  condition_options.push_back("5. Damaged");

  PrintList(condition_options);

  std::string current_condition_string;

  switch (current_condition) {
    case domain::Item::Condition::kFactoryNew:
      current_condition_string = "1";
      break;
    case domain::Item::Condition::kMinimalWear:
      current_condition_string = "2";
      break;
    case domain::Item::Condition::kNormalWear:
      current_condition_string = "3";
      break;
    case domain::Item::Condition::kWellWorn:
      current_condition_string = "4";
      break;
    case domain::Item::Condition::kDamaged:
      current_condition_string = "5";
      break;
  }

  PrintDivider();

  std::string input =
      PromptForString("Enter Condition [" + current_condition_string + "]: ");

  if (input.empty()) {
    return current_condition;
  }

  switch (input[0]) {
    case '1':
      return domain::Item::Condition::kFactoryNew;
    case '2':
      return domain::Item::Condition::kMinimalWear;
    case '3':
      return domain::Item::Condition::kNormalWear;
    case '4':
      return domain::Item::Condition::kWellWorn;
    case '5':
      return domain::Item::Condition::kDamaged;
    default:
      throw std::invalid_argument("Invalid item condition.");
  }
}

std::string TitlesView::PromptForShelfLocation(
    std::string current_shelf_location) const {
  std::string input = PromptForString("Enter Shelf Location [" +
                                      current_shelf_location + "]: ");
  if (input.empty()) {
    return current_shelf_location;
  }

  return input;
}

bool TitlesView::PromptForIsAvailable(bool current_is_available) const {
  std::string current_value;

  if (current_is_available) {
    current_value = "y";
  } else {
    current_value = "n";
  }

  std::string input =
      PromptForString("Is Available? (y/n) [" + current_value + "]: ");

  if (input.empty()) {
    return current_is_available;
  }

  if (input == "y" || input == "Y") {
    return true;
  }

  return false;
}

}  // namespace library_book_borrowing_manager::presentation::views
