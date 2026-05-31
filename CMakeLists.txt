cmake_minimum_required(VERSION 4.3)
project(LibraryBookBorrowingManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP FALSE)
FetchContent_MakeAvailable(json)

set(DATA_SOURCES
    src/data/json_library_data_repository.cpp
)

set(DOMAIN_SOURCES
    src/domain/repositories/library_data_repository.cpp
    src/domain/address.cpp
    src/domain/book.cpp
    src/domain/borrow_record.cpp
    src/domain/citizen_id.cpp
    src/domain/customer.cpp
    src/domain/email.cpp
    src/domain/item.cpp
    src/domain/journal.cpp
    src/domain/magazine.cpp
    src/domain/periodical.cpp
    src/domain/thesis.cpp
    src/domain/title.cpp
)

set(PRESENTATION_SOURCES
    src/presentation/controllers/borrow_records_controller.cpp
    src/presentation/controllers/checkin_controller.cpp
    src/presentation/controllers/checkout_controller.cpp
    src/presentation/controllers/customers_controller.cpp
    src/presentation/controllers/main_menu_controller.cpp
    src/presentation/controllers/register_customer_controller.cpp
    src/presentation/controllers/titles_controller.cpp
    src/presentation/views/borrow_records_view.cpp
    src/presentation/views/checkin_view.cpp
    src/presentation/views/checkout_view.cpp
    src/presentation/views/console_view.cpp
    src/presentation/views/customers_view.cpp
    src/presentation/views/menu_view.cpp
    src/presentation/views/titles_view.cpp
)

set(SERVICE_SOURCES
    src/service/library_manager.cpp
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    ${DATA_SOURCES}
    ${DOMAIN_SOURCES}
    ${PRESENTATION_SOURCES}
    ${SERVICE_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
