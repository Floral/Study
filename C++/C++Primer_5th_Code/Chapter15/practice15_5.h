#ifndef PRACTICE15_5
#define PRACTICE15_5
#include<iostream>
#include"practice15_3.h"

class Bulk_quote: public Quote{
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
                       Quote(book,p), min_qty(qty), discount(disc){}

double Bulk_quote::net_price(std::size_t cnt) const
{
    if (cnt >= min_qty)
        return cnt * (1-discount)*price;
    else
        return cnt * price;
}

#endif