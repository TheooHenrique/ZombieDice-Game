#ifndef READER_HPP
#define READER_HPP

#include <map>
#include <string>

class Reader {
public:
    //Constructor:
    Reader(const std::string& filename);
    std::map<std::string, std::string> getSection(const std::string& section);

private:
    //Mapa que relaciona uma key à seu valor. EX: green_amount = 3, max_players = 4
    std::map<std::string, std::string> keys; 
    //Mapa que relaciona uma seção às suas variáveis. EX: [Dice]: weak_dice_faces = "bbbffs", [Game]: brains_to_win = 13
    std::map<std::string, std::map<std::string, std::string>> data; 
};

#endif
