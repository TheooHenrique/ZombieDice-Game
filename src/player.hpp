#include <cstddef>
#include <string>
class Player{
    using size_type = size_t;

    public:
    bool m_is_playing;
    std::string m_name;
    size_type m_total_brains;
    size_type m_brain_round;
    size_type m_run_round;
    size_type m_shots_round;

    public:
    size_type note();
    bool decision();
};