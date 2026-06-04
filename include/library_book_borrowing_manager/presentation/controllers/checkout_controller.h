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
// checkout_controller.h
// -----------------------------------------------------------------------------
//
// This header file declares the CheckoutController class for processing user
// input in the Checkout Items menu options.

#ifndef LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_CONTROLLERS_CHECKOUT_CONTROLLER_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_CONTROLLERS_CHECKOUT_CONTROLLER_H_

#include <vector>

#include "library_book_borrowing_manager/domain/item.h"
#include "library_book_borrowing_manager/presentation/views/checkout_view.h"
#include "library_book_borrowing_manager/service/library_manager.h"

namespace library_book_borrowing_manager::presentation::controllers {

class CheckoutController {
 public:
  CheckoutController(service::LibraryManager& library_manager,
                     views::CheckoutView& checkout_view);

  void Run();
  std::vector<domain::Item> GetAvailableItems(
      std::vector<domain::Item> items) const;

 private:
  service::LibraryManager& library_manager_;

  views::CheckoutView& checkout_view_;
};

}  // namespace library_book_borrowing_manager::presentation::controllers

#endif  // LIBRARY_BOOK_BORROWING_MANAGER_PRESENTATION_CONTROLLERS_CHECKOUT_CONTROLLER_H_
