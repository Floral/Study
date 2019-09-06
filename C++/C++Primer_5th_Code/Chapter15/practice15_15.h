#include<iostream>
#include<string>
#include"practice15_11.h"

class Disc_quote:public Quote{
public:
    Disc_quote() = default;
    Disc_quote(const std::string& book, double price,
               std::size_t qty, double disc):
               Quote(book, price),quantity(qty), discount(disc){}

    double net_price(std::size_t) const = 0;

protected:
    std::size_t quantity = 0;
    double discount = 0.0;

};

class Bulk_quote: public Disc_quote{
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string&, double, std::size_t, double);

    double net_price(std::size_t) const override;

private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};

Bulk_quote::Bulk_quote(const std::string &book, double p,
                       std::size_t qty, double disc):
                       Disc_quote(book,p,qty,disc){}

double Bulk_quote::net_price(std::size_t cnt) const
{
    if (cnt >= min_qty)
        return cnt * (1-discount)*price;
    else
        return cnt * price;
}