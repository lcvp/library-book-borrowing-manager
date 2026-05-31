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

#include "library_book_borrowing_manager/presentation/views/titles_view.h"
#include "library_book_borrowing_manager/service/library_manager.h"

namespace library_book_borrowing_manager::presentation::controllers {

TitlesController::TitlesController(service::LibraryManager& library_manager,
                                   views::TitlesView& titles_view)
    : library_manager_(library_manager), titles_view_(titles_view) {}

void TitlesController::Run() {}

}  // namespace library_book_borrowing_manager::presentation::controllers
