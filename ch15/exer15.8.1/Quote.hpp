#ifndef QUOTE_H_
#define QUOTE_H_
#include <string>
#include <iostream>

class Quote {
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : 
        bookNo(book), price(sales_price) { }
    std::string isbn() const {return bookNo;}
    virtual double net_price(std::size_t n) const { return n * price; }
    virtual ~Quote() = default;

    // 模板虚拷贝：解决隐藏指针的需求
    virtual Quote* clone() const & { return new Quote(*this); }
    virtual Quote* clone() && { return new Quote(std::move(*this)); }
private:
    std::string bookNo;
protected:
    double price = 0.0;
};

double print_total(std::ostream &os, const Quote &item, size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() 
       << " # sold: " << n << " total due: " << ret << std::endl; 
    return ret;
}
#endif