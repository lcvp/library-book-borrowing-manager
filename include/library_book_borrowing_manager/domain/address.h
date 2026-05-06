#ifndef LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_ADDRESS_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_ADDRESS_H_

#include <string>

class Address {
public:
  std::string building_number() const;
  std::string street() const;
  std::string city() const;
  std::string postal_code() const;

  void set_building_number(std::string building_number);
  void set_street(std::string street);
  void set_city(std::string city);
  void set_postal_code(std::string postal_code);

  std::string GetFullAddress() const;

private:
  std::string building_number_;
  std::string street_;
  std::string city_;
  std::string postal_code_;
};

#endif // LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_ADDRESS_H_
