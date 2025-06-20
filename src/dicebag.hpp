#include <string>
#include <cstddef>


class DiceBag{
    using size_type = std::size_t;
    public:
    //Note that this values are the default values. They can be overriden by the initializer.
    size_type m_green_amount = 6;
    size_type m_yellow_amount = 4;
    size_type m_red_amount = 3;
    size_type m_current_count_dices;
    size_type m_total_dices = 13;
    
    public:
    std::string sort_dices();
    size_type lower_3_dices();
    size_type refill_bag();
    
};