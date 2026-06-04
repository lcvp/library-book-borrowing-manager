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

#include "library_book_borrowing_manager/presentation/controllers/checkout_controller.h"

#include <string>

#include "library_book_borrowing_manager/domain/customer.h"
#include "library_book_borrowing_manager/domain/item.h"
#include "library_book_borrowing_manager/presentation/views/checkout_view.h"
#include "library_book_borrowing_manager/presentation/views/console_view.h"
#include "library_book_borrowing_manager/service/library_manager.h"

namespace library_book_borrowing_manager::presentation::controllers {

CheckoutController::CheckoutController(service::LibraryManager& library_manager,
                                       views::CheckoutView& checkout_view)
    : library_manager_(library_manager), checkout_view_(checkout_view) {}

void CheckoutController::Run() {
  try {
    views::ClearTerminal();
    std::vector<domain::Customer> customer_list =
        library_manager_.GetCustomerList();
    std::vector<domain::Item> item_list =
        GetAvailableItems(library_manager_.GetItemList());

    std::string selected_customer_id =
        checkout_view_.PrintCustomerList(customer_list);
    std::vector<std::string> selected_item_ids;

    while (true) {
      views::ClearTerminal();
      std::string selected_item_id = checkout_view_.PrintItemList(
          item_list, selected_customer_id, selected_item_ids);
      selected_item_ids.push_back(selected_item_id);
      if (!views::PromptForConfirmation("Enter more items? (y/n): ")) {
        break;
      }
    }

    library_manager_.CheckoutItems(selected_customer_id, selected_item_ids);

    views::PrintSuccess("Successfully checked out items");
  } catch (const std::exception& exception) {
    views::PrintError(exception.what());
  }
  views::WaitForInput("Press Enter to continue");
}

std::vector<domain::Item> CheckoutController::GetAvailableItems(
    std::vector<domain::Item> items) const {
  std::vector<domain::Item> available_items;

  for (domain::Item item : items) {
    if (item.is_available()) {
      available_items.push_back(item);
    }
  }

  return available_items;
}
}  // namespace library_book_borrowing_manager::presentation::controllers
