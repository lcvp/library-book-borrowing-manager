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
// titles_view.h
// -----------------------------------------------------------------------------
//
// This header file declares the TitlesView class for rendering menu options
// regarding Titles.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_VIEWS_TITLES_VIEW_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_VIEWS_TITLES_VIEW_H_

#include <string>
#include <vector>

#include "library_book_borrowing_manager/domain/item.h"
#include "library_book_borrowing_manager/domain/title.h"

namespace library_book_borrowing_manager::presentation::views {

class TitlesView {
 public:
  char PrintManageTitlesOptions() const;
  char PrintAddTitleOptions() const;
  std::string PrintTitleList(const std::vector<const domain::Title*>& titles,
                             bool get_input = true) const;
  char PrintItemConditionOptions() const;
  char PrintManageItemsOptions() const;
  std::string PromptForName(std::string current_name) const;
  std::string PromptForDescription(std::string current_description) const;
  std::string PromptForAuthor(std::string current_author) const;
  std::string PromptForPublisher(std::string current_publisher) const;
  int PromptForPublicationYear(int current_publication_year) const;
  std::string PromptForDoi(std::string current_doi) const;
  std::string PromptForIsbn(std::string current_isbn) const;
  std::string PromptForEdition(std::string current_edition) const;
  std::string PromptForIssn(std::string current_issn) const;
  std::string PromptForPublicationName(
      std::string current_publication_name) const;
  std::string PromptForVolume(std::string current_volume) const;
  std::string PromptForIssueNumber(std::string current_issue_number) const;
  std::string PromptForFieldOfStudy(std::string current_field_of_study) const;
  bool PromptForIsPeerReviewed(bool current_is_peer_reviewed) const;
  std::string PromptForCategory(std::string current_category) const;
  std::string PromptForUniversity(std::string current_university) const;
  std::string PromptForDegreeLevel(std::string current_degree_level) const;
  int PromptForDefenseYear(int current_defense_year) const;
  std::string PromptForSupervisorName(
      std::string current_supervisor_name) const;
  std::string PrintItemList(const std::vector<domain::Item> items,
                            bool get_input = true) const;
  std::string PromptForTitleId(const std::vector<const domain::Title*>& titles,
                               std::string current_title_id) const;
  domain::Item::Condition PromptForItemCondition(
      domain::Item::Condition current_condition) const;
  std::string PromptForShelfLocation(std::string current_shelf_location) const;
  bool PromptForIsAvailable(bool current_is_available) const;
  std::string ItemToString(domain::Item item) const;
  std::vector<std::string> ItemListToString(
      std::vector<domain::Item> item_list) const;
};

}  // namespace library_book_borrowing_manager::presentation::views

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_VIEWS_TITLES_VIEW_H_
