#ifndef LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_MAGAZINE_H_
#define LIBRARY_BOOK_BORROWING_MANAGER_DOMAIN_MAGAZINE_H_
#include <string>
#include "library_book_borrowing_manager/domain/title.h"
namespace library_book_borrowing_manager::domain
{
    class Magazine : public Title
    {
        public:
        std::string issn() const;
        int volume() const;
        int issue_number() const;
        std::string category() const;

        void set_issn(std::string issn);
        void set_volume(int volume);
        void set_issue_number(int issue_number);
        void set_category(std::string category);
        
        std::string GetApaCitation() const override;

        private:
        std::string issn_;
        int volume_;
        int issue_number_;
        std::string category_;
    };
}
#endif