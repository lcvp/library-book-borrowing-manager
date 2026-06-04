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

#include "library_book_borrowing_manager/presentation/controllers/register_customer_controller.h"

#include <string>

#include "library_book_borrowing_manager/presentation/views/console_view.h"
#include "library_book_borrowing_manager/presentation/views/customers_view.h"
#include "library_book_borrowing_manager/service/library_manager.h"

namespace library_book_borrowing_manager::presentation::controllers {

RegisterCustomerController::RegisterCustomerController(
    service::LibraryManager& library_manager,
    views::CustomersView& customers_view)
    : library_manager_(library_manager), customers_view_(customers_view) {}

void RegisterCustomerController::Run() {
  try {
    views::ClearTerminal();

    views::PrintHeader("Register Customer");

    std::string citizen_id = views::PromptForString("Enter Citizen ID: ");
    std::string customer_name = views::PromptForString("Enter Customer Name: ");
    std::string date_of_birth =
        views::PromptForString("Enter Date Of Birth (DD/MM/YYYY): ");
    std::string email_address =
        views::PromptForString("Enter Customer Email Address: ");
    std::string phone_number =
        views::PromptForString("Enter Customer Phone Number: ");
    std::string address_building_number =
        views::PromptForString("Enter Address Building Number: ");
    std::string address_street =
        views::PromptForString("Enter Address Street: ");
    std::string address_city = views::PromptForString("Enter Address City: ");
    std::string address_postal_code =
        views::PromptForString("Enter Address Postal Code: ");

    library_manager_.RegisterCustomer(
        citizen_id, customer_name, views::StringToTimePoint(date_of_birth),
        email_address, phone_number, address_building_number, address_street,
        address_city, address_postal_code);

    views::PrintSuccess("Successfully Register Customer.");
  } catch (const std::exception& exception) {
    views::PrintError(exception.what());
  }
  views::WaitForInput("Press Enter to continue");
}

}  // namespace library_book_borrowing_manager::presentation::controllers
