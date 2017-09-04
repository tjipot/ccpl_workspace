/* @UNIVESRE.COM_20161213_HYe
 * Demonstrates the concepts of Class in CPP.
 */

/* 类: 新的类型和新的作用域 */
class Sales_item{
public:
    double avg_price() const;
    bool same_isbn(const Sales_item & rhs) const { return isbn == rhs.isbn; }
    Sales_item(): units_sold(0), revenue(0.0) { }
private:
    std::string isbn;
    unsigned units_sold;
    double revenue;
};

/* 类外定义 */
double Sales_item::avg_price() const{
    if (units_sold) {
        return revenue/units_sold;
    }else{
        return 0;
    }
}
