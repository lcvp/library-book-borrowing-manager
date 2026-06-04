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

#include "library_book_borrowing_manager/presentation/controllers/titles_controller.h"

#include <stdexcept>
#include <string>
#include <vector>

#include "library_book_borrowing_manager/domain/book.h"
#include "library_book_borrowing_manager/domain/item.h"
#include "library_book_borrowing_manager/domain/journal.h"
#include "library_book_borrowing_manager/domain/magazine.h"
#include "library_book_borrowing_manager/domain/thesis.h"
#include "library_book_borrowing_manager/domain/title.h"
#include "library_book_borrowing_manager/presentation/views/console_view.h"
#include "library_book_borrowing_manager/presentation/views/titles_view.h"
#include "library_book_borrowing_manager/service/library_manager.h"

namespace library_book_borrowing_manager::presentation::controllers {

TitlesController::TitlesController(service::LibraryManager& library_manager,
                                   views::TitlesView& titles_view)
    : library_manager_(library_manager), titles_view_(titles_view) {}

void TitlesController::Run() {
  try {
    views::ClearTerminal();
    std::vector<const domain::Title*> titles = library_manager_.GetTitleList();
    titles_view_.PrintTitleList(titles, false);

    char user_input = titles_view_.PrintManageTitlesOptions();

    switch (user_input) {
      case '1':
        AddTitle();
        break;
      case '2':
        EditTitle();
        break;
      case '3':
        DeleteTitle();
        break;
      case '4':
        ManageItems();
        break;
      default:
        break;
    }
  } catch (const std::exception& exception) {
    views::PrintError(exception.what());
  }
}

void TitlesController::AddTitle() {
  try {
    views::ClearTerminal();

    views::PrintHeader("Add Title");

    char title_type = titles_view_.PrintAddTitleOptions();

    std::string name = views::PromptForString("Enter Title Name: ");
    std::string description = views::PromptForString("Enter Description: ");
    std::string author = views::PromptForString("Enter Author: ");
    std::string publisher = views::PromptForString("Enter Publisher: ");
    int publication_year =
        std::stoi(views::PromptForString("Enter Publication Year: "));
    std::string doi = views::PromptForString("Enter DOI: ");

    switch (title_type) {
      case '1': {
        std::string isbn = views::PromptForString("Enter ISBN: ");
        std::string edition = views::PromptForString("Enter Edition: ");

        library_manager_.AddBook(name, description, author, publisher,
                                 publication_year, doi, isbn, edition);

        views::PrintSuccess("Successfully Added Book Title.");
        break;
      }

      case '2': {
        std::string issn = views::PromptForString("Enter ISSN: ");
        std::string publication_name =
            views::PromptForString("Enter Publication Name: ");
        std::string volume = views::PromptForString("Enter Volume: ");
        std::string issue_number =
            views::PromptForString("Enter Issue Number: ");
        std::string field_of_study =
            views::PromptForString("Enter Field Of Study: ");
        std::string is_peer_reviewed_input =
            views::PromptForString("Is Peer Reviewed? (y/n): ");

        bool is_peer_reviewed =
            is_peer_reviewed_input == "y" || is_peer_reviewed_input == "Y";

        library_manager_.AddJournal(name, description, author, publisher,
                                    publication_year, doi, issn,
                                    publication_name, volume, issue_number,
                                    field_of_study, is_peer_reviewed);

        views::PrintSuccess("Successfully Added Journal Title.");
        break;
      }

      case '3': {
        std::string issn = views::PromptForString("Enter ISSN: ");
        std::string publication_name =
            views::PromptForString("Enter Publication Name: ");
        std::string volume = views::PromptForString("Enter Volume: ");
        std::string issue_number =
            views::PromptForString("Enter Issue Number: ");
        std::string category = views::PromptForString("Enter Category: ");

        library_manager_.AddMagazine(
            name, description, author, publisher, publication_year, doi, issn,
            publication_name, volume, issue_number, category);

        views::PrintSuccess("Successfully Added Magazine Title.");
        break;
      }

      case '4': {
        std::string university = views::PromptForString("Enter University: ");
        std::string degree_level =
            views::PromptForString("Enter Degree Level: ");
        int defense_year =
            std::stoi(views::PromptForString("Enter Defense Year: "));
        std::string supervisor_name =
            views::PromptForString("Enter Supervisor Name: ");

        library_manager_.AddThesis(name, description, author, publisher,
                                   publication_year, doi, university,
                                   degree_level, defense_year, supervisor_name);

        views::PrintSuccess("Successfully Added Thesis Title.");
        break;
      }

      default:
        throw std::invalid_argument("Invalid Title Type");
        break;
    }
  } catch (const std::exception& exception) {
    views::PrintError(exception.what());
  }

  views::WaitForInput("Press Enter to continue");
}

void TitlesController::EditTitle() {
  try {
    views::ClearTerminal();

    views::PrintHeader("Edit Title (Press Enter to keep old value)");

    std::vector<const domain::Title*> titles = library_manager_.GetTitleList();

    std::string title_id = titles_view_.PrintTitleList(titles);

    const domain::Title* title = library_manager_.GetTitleById(title_id);

    std::string name = titles_view_.PromptForName(title->name());

    std::string description =
        titles_view_.PromptForDescription(title->description());

    std::string author = titles_view_.PromptForAuthor(title->author());

    std::string publisher = titles_view_.PromptForPublisher(title->publisher());

    int publication_year =
        titles_view_.PromptForPublicationYear(title->publication_year());

    std::string doi = titles_view_.PromptForDoi(title->doi());

    const domain::Book* book = dynamic_cast<const domain::Book*>(title);
    const domain::Journal* journal =
        dynamic_cast<const domain::Journal*>(title);
    const domain::Magazine* magazine =
        dynamic_cast<const domain::Magazine*>(title);
    const domain::Thesis* thesis = dynamic_cast<const domain::Thesis*>(title);

    if (book != nullptr) {
      std::string isbn = titles_view_.PromptForIsbn(book->isbn());

      std::string edition = titles_view_.PromptForEdition(book->edition());

      library_manager_.UpdateBook(title_id, name, description, author,
                                  publisher, publication_year, doi, isbn,
                                  edition);
    }

    if (journal != nullptr) {
      std::string issn = titles_view_.PromptForIssn(journal->issn());

      std::string publication_name =
          titles_view_.PromptForPublicationName(journal->publication_name());

      std::string volume = titles_view_.PromptForVolume(journal->volume());

      std::string issue_number =
          titles_view_.PromptForIssueNumber(journal->issue_number());

      std::string field_of_study =
          titles_view_.PromptForFieldOfStudy(journal->field_of_study());

      bool is_peer_reviewed =
          titles_view_.PromptForIsPeerReviewed(journal->is_peer_reviewed());

      library_manager_.UpdateJournal(title_id, name, description, author,
                                     publisher, publication_year, doi, issn,
                                     publication_name, volume, issue_number,
                                     field_of_study, is_peer_reviewed);
    }

    if (magazine != nullptr) {
      std::string issn = titles_view_.PromptForIssn(magazine->issn());

      std::string publication_name =
          titles_view_.PromptForPublicationName(magazine->publication_name());

      std::string volume = titles_view_.PromptForVolume(magazine->volume());

      std::string issue_number =
          titles_view_.PromptForIssueNumber(magazine->issue_number());

      std::string category =
          titles_view_.PromptForCategory(magazine->category());

      library_manager_.UpdateMagazine(
          title_id, name, description, author, publisher, publication_year, doi,
          issn, publication_name, volume, issue_number, category);
    }

    if (thesis != nullptr) {
      std::string university =
          titles_view_.PromptForUniversity(thesis->university());

      std::string degree_level =
          titles_view_.PromptForDegreeLevel(thesis->degree_level());

      int defense_year =
          titles_view_.PromptForDefenseYear(thesis->defense_year());

      std::string supervisor_name =
          titles_view_.PromptForSupervisorName(thesis->supervisor_name());

      library_manager_.UpdateThesis(
          title_id, name, description, author, publisher, publication_year, doi,
          university, degree_level, defense_year, supervisor_name);
    }

    views::PrintSuccess("Successfully updated title.");
  } catch (const std::exception& exception) {
    views::PrintError(exception.what());
  }

  views::WaitForInput("Press Enter to continue");
}

void TitlesController::DeleteTitle() {
  try {
    views::ClearTerminal();

    views::PrintHeader("Delete Title");

    std::vector<const domain::Title*> titles = library_manager_.GetTitleList();

    std::string title_id = titles_view_.PrintTitleList(titles);

    library_manager_.DeleteTitle(title_id);

    views::PrintSuccess("Successfully deleted title");
  } catch (const std::exception& exception) {
    views::PrintError(exception.what());
  }

  views::WaitForInput("Press Enter to continue");
}

void TitlesController::ManageItems() {
  try {
    views::ClearTerminal();
    std::vector<domain::Item> items = library_manager_.GetItemList();
    titles_view_.PrintItemList(items, false);

    char user_input = titles_view_.PrintManageItemsOptions();

    switch (user_input) {
      case '1':
        AddItem();
        break;
      case '2':
        EditItem();
        break;
      case '3':
        DeleteItem();
        break;
      default:
        break;
    }
  } catch (const std::exception& exception) {
    views::PrintError(exception.what());
  }
}

void TitlesController::AddItem() {
  try {
    views::ClearTerminal();

    views::PrintHeader("Add Item");

    std::vector<const domain::Title*> titles = library_manager_.GetTitleList();

    std::string title_id = titles_view_.PrintTitleList(titles);

    char condition_input = titles_view_.PrintItemConditionOptions();

    std::string shelf_location =
        views::PromptForString("Enter Shelf Location: ");

    library_manager_.AddItem(title_id, condition_input, shelf_location);

    views::PrintSuccess("Successfully Added Item.");
  } catch (const std::exception& exception) {
    views::PrintError(exception.what());
  }

  views::WaitForInput("Press Enter to continue");
}

void TitlesController::EditItem() {
  try {
    views::ClearTerminal();

    views::PrintHeader("Edit Item (Press Enter to keep old value)");

    std::vector<domain::Item> items = library_manager_.GetItemList();

    std::string item_id = titles_view_.PrintItemList(items);

    domain::Item item = library_manager_.GetItemById(item_id);

    std::vector<const domain::Title*> titles = library_manager_.GetTitleList();

    std::string title_id =
        titles_view_.PromptForTitleId(titles, item.title()->id());

    domain::Item::Condition condition =
        titles_view_.PromptForItemCondition(item.condition());

    std::string shelf_location =
        titles_view_.PromptForShelfLocation(item.shelf_location());

    bool is_available = titles_view_.PromptForIsAvailable(item.is_available());

    library_manager_.UpdateItem(item_id, title_id, condition, shelf_location,
                                is_available);

    views::PrintSuccess("Successfully updated item.");
  } catch (const std::exception& exception) {
    views::PrintError(exception.what());
  }

  views::WaitForInput("Press Enter to continue");
}

void TitlesController::DeleteItem() {
  try {
    views::ClearTerminal();

    views::PrintHeader("Delete Item");

    std::vector<domain::Item> items = library_manager_.GetItemList();

    std::string item_id = titles_view_.PrintItemList(items);

    library_manager_.DeleteItem(item_id);

    views::PrintSuccess("Successfully deleted item");
  } catch (const std::exception& exception) {
    views::PrintError(exception.what());
  }

  views::WaitForInput("Press Enter to continue");
}

}  // namespace library_book_borrowing_manager::presentation::controllers
