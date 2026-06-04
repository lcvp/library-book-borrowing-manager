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

#include "library_book_borrowing_manager/presentation/controllers/customers_controller.h"

#include "library_book_borrowing_manager/presentation/views/console_view.h"
#include "library_book_borrowing_manager/presentation/views/customers_view.h"
#include "library_book_borrowing_manager/service/library_manager.h"

namespace library_book_borrowing_manager::presentation::controllers {

CustomersController::CustomersController(
    service::LibraryManager& library_manager,
    views::CustomersView& customers_view)
    : library_manager_(library_manager), customers_view_(customers_view) {}

void CustomersController::Run() {
  try {
    views::ClearTerminal();

    std::vector<domain::Customer> customers =
        library_manager_.GetCustomerList();
    customers_view_.PrintCustomerList(customers, false);

    char user_input = customers_view_.PrintCustomersOptions();
    switch (user_input) {
      case '1':
        UpdateCustomer();
        break;
      case '2':
        DeleteCustomer();
        break;
      default:
        break;
    }
  } catch (const std::exception& exception) {
    views::PrintError(exception.what());
  }
}

void CustomersController::UpdateCustomer() {
  try {
    views::ClearTerminal();

    views::PrintHeader("Update Customer (Press Enter to keep old value)");

    std::vector<domain::Customer> customers =
        library_manager_.GetCustomerList();

    std::string customer_id = customers_view_.PrintCustomerList(customers);

    domain::Customer customer = library_manager_.GetCustomerById(customer_id);

    std::string name = customers_view_.PromptForName(customer.name());

    std::string citizen_id =
        customers_view_.PromptForCitizenId(customer.citizen_id().id());

    std::chrono::system_clock::time_point date_of_birth =
        customers_view_.PromptForDateOfBirth(customer.date_of_birth());

    std::string email_address =
        customers_view_.PromptForEmailAddress(customer.email().email_address());

    std::string phone_number =
        customers_view_.PromptForPhoneNumber(customer.phone_number());

    std::string building_number = customers_view_.PromptForBuildingNumber(
        customer.address().building_number());

    std::string street =
        customers_view_.PromptForStreet(customer.address().street());

    std::string city = customers_view_.PromptForCity(customer.address().city());

    std::string postal_code =
        customers_view_.PromptForPostalCode(customer.address().postal_code());

    library_manager_.UpdateCustomer(customer_id, name, citizen_id,
                                    date_of_birth, email_address, phone_number,
                                    building_number, street, city, postal_code);

    views::PrintSuccess("Successfully updated customer.");
  } catch (const std::exception& exception) {
    views::PrintError(exception.what());
  }

  views::WaitForInput("Press Enter to continue");
}

void CustomersController::DeleteCustomer() {
  try {
    views::ClearTerminal();

    views::PrintHeader("Delete Customer");

    std::vector<domain::Customer> customers =
        library_manager_.GetCustomerList();

    std::string customer_id = customers_view_.PrintCustomerList(customers);

    if (!views::PromptForConfirmation(
            "Are you sure you want to delete this customer? (y/n): ")) {
      views::PrintError("Delete customer cancelled.");
      views::WaitForInput("Press Enter to continue");
      return;
    }

    library_manager_.DeleteCustomer(customer_id);

    views::PrintSuccess("Successfully deleted customer.");
  } catch (const std::exception& exception) {
    views::PrintError(exception.what());
  }

  views::WaitForInput("Press Enter to continue");
}

}  // namespace library_book_borrowing_manager::presentation::controllers
