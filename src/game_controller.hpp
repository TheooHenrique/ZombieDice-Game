#include <cstdint>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "dicebag.hpp"
#include "player.hpp"
#include "reader.hpp"
#include <unordered_map>
#include <algorithm>
#include <random>
#include <limits>
#include <iomanip>

/**
 * @file game_controller.hpp
 * @brief Defines the main GameController class, which manages the entire game flow.
 * @author YHaniel Lucas Machado Rocha
 * @author Theo Henrique da Silva Borges
 * @date June 24th, 2025
 */


/**
 * @class GameController
 * @brief The main engine of the Zombie Dice game, implemented as a Singleton.
 *
 * This class controls the game using a state machine. It is responsible for
 * parsing configurations, managing players, handling the game loop (process,
 * update, render), and determining the winner.
 * @note This class follows the Singleton design pattern to ensure only one
 * instance exists.
 */
class GameController{
    /// @brief Alias for the size type used throughout the class.
    using size_type = std::size_t;

private:
    //== SINGLETON CONSTRUCTOR ==//
    /**
     * @brief Private default constructor to support the Singleton pattern.
     * Initializes the game with default values.
     */
    GameController() : m_current_state(START), m_brains_to_win(13), m_current_round(1),
        m_max_players(6),
        m_max_turn(0),
        m_current_player(),
        initializer_amount(0),
        config_ok(true),
        m_game_initialized(false) {}

    //== ATTRIBUTES ==//
    uint8_t m_current_state;              ///< The current state of the game's state machine.
    size_type m_brains_to_win;            ///< The number of brains a player needs to score to trigger the end of the game.
    size_type m_current_round;            ///< The current round number of the game.
    size_type m_max_players;              ///< The maximum number of players allowed.
    size_type m_max_turn;                 ///< The maximum number of turns for an alternative game mode. 0 means unlimited.
    size_type m_weak_dice;                ///< The number of green dice, read from config.
    size_type m_tough_dice;               ///< The number of yellow dice, read from config.
    size_type m_strong_dice;              ///< The number of red dice, read from config.
    std::vector<Player> m_player_list;    ///< The list of all players in the game.
    std::vector<Player> m_possib_winner;  ///< A list of players who could potentially win.
    std::vector<ZDice> sorted_dice;       ///< Stores the dice drawn in the current roll.
    DiceBag m_dice_bag;                   ///< The dice bag object, containing all the game's dice.
    Player *m_current_player;             ///< A pointer to the player whose turn it is.
    std::string initializer_name;         ///< The name of the .ini configuration file.
    size_type initializer_amount;         ///< The count of .ini files found.
    std::string error_msg;                ///< A string to hold error messages for display.
    bool config_ok;                       ///< Flag indicating if the configuration file was parsed successfully.
    bool m_game_initialized;              ///< Flag indicating if the game has passed the welcome screen.
    bool multiple_initializer;            ///< Flag for detecting multiple .ini files.
    bool green_faces_are_ok;              ///< Flag for validating green dice faces from config.
    bool yellow_faces_are_ok;             ///< Flag for validating yellow dice faces from config.
    bool red_faces_are_ok;                ///< Flag for validating red dice faces from config.
    bool gamesectiontypeerror;            ///< Flag for detecting type errors in the [Game] section of config.

    /**
     * @brief Defines all possible states for the game's state machine.
     */
    enum m_possible_states : uint8_t {
        START,          ///< The initial state before the game begins.
        WELCOME,        ///< The state for displaying the welcome message after players are entered.
        INVALID_CFG,    ///< The state for handling an invalid configuration file.
        INPUT_PLAYERS,  ///< The state for prompting the user to input player names.
        INVALID_PLAYERS,///< The state for handling an invalid number of players.
        WAITING_ACTION, ///< The main state, waiting for the current player's action (roll or hold).
        INVALID_ACTION, ///< The state for handling invalid command input from the player.
        SKIP,           ///< The state for processing the end of a turn and passing to the next player.
        DICE_ROLL,      ///< The state where the dice are rolled and results are processed.
        CHECK_DICES,    ///< The state for checking the results of a roll (e.g., if the player busted).
        CHECK_BRAINS,   ///< The state for checking if a player has reached the win condition.
        REMOVE_BRAINS,  ///< The state to process a player "busting" (losing round brains).
        RESTORE_DICES,  ///< The state for refilling the dice bag when it runs low.
        POSSIB_WIN,     ///< The state for identifying a potential winner.
        PLAYER_WIN,     ///< The state when a definitive winner has been found.
        TIE,            ///< The state when a tie is detected.
        END             ///< The final state, which terminates the game loop.
    };

    //METHODS:
public:

    /**
     * @brief Parses command-line arguments to find and load a configuration .ini file.
     * @param argc Argument count from main().
     * @param argv Argument vector from main().
     */
void parse_config(int argc, char* argv[]){
    size_type ct = 0;
    for (size_type i{1}; i < argc ; ++i){ 
    std::string extension = std::filesystem::path(argv[i]).extension().string();
    if (extension == ".ini"){
        initializer_name = argv[i];
        ++ct;
    }
  }
  initializer_amount = ct;
  
  if(initializer_amount == 1){
    //Call Reader's constructor
    Reader reader(initializer_name);
    //Override gc attributes with initializer config
    
    //GAME CONSTRUCTOR INPUT WITH INITIALIZER CONFIG AND ERROR TREATMENTS
    if (reader.getSection("Game").find("brains_to_win") != reader.getSection("Game").end()){
        if (!reader.getSection("Game").at("brains_to_win").empty()){
             try{ m_brains_to_win = std::stoi(reader.getSection("Game").at("brains_to_win"));}
             catch (const std::invalid_argument& e){ throw std::invalid_argument("Type error! Put just integers in your Game section of configuration file!"); } }}
    if (reader.getSection("Game").find("max_turns") != reader.getSection("Game").end()){
        if (!reader.getSection("Game").at("max_turns").empty()){
            try{m_max_turn = std::stoi(reader.getSection("Game").at("max_turns"));}
            catch (const std::invalid_argument& e) { throw std::invalid_argument("Type error! Put just integers in your Game section of configuration file!"); } }} 
    if (reader.getSection("Game").find("max_players") != reader.getSection("Game").end()){
        if (!reader.getSection("Game").at("max_players").empty()){
            try{m_max_players = std::stoi(reader.getSection("Game").at("max_players"));}
            catch(const std::invalid_argument& e) { throw std::invalid_argument("Type error! Put just integers in your Game section of configuration file!"); } }}
    if (reader.getSection("Game").find("weak_dice") != reader.getSection("Game").end()){
        if (!reader.getSection("Game").at("weak_dice").empty()){
            try{m_weak_dice = std::stoi(reader.getSection("Game").at("weak_dice"));}
            catch(const std::invalid_argument& e) { throw std::invalid_argument("Type error! Put just integers in your Game section of configuration file!"); } }}
    if (reader.getSection("Game").find("strong_dice") != reader.getSection("Game").end()){
        if (!reader.getSection("Game").at("strong_dice").empty()){
            try{m_strong_dice = std::stoi(reader.getSection("Game").at("strong_dice"));}
            catch(const std::invalid_argument& e) { throw std::invalid_argument("Type error! Put just integers in your Game section of configuration file!"); } }}
    if (reader.getSection("Game").find("tough_dice") != reader.getSection("Game").end()){
        if (!reader.getSection("Game").at("tough_dice").empty()){
            try{m_tough_dice = std::stoi(reader.getSection("Game").at("tough_dice"));}
            catch(const std::invalid_argument& e) { throw std::invalid_argument("Type error! Put just integers in your Game section of configuration file!"); } }}

    //ZDICE CONSTRUCT INPUT WITH INITIALIZER CONFIG
    std::string weak = reader.getSection("Dice").at("weak_dice_faces");
    std::string strong = reader.getSection("Dice").at("strong_dice_faces");
    std::string tough = reader.getSection("Dice").at("tough_dice_faces");

    if (reader.getSection("Dice").find("weak_dice_faces") != reader.getSection("Dice").end()){
        if (!reader.getSection("Dice").at("weak_dice_faces").empty()){
            for (size_type i{0}; i < m_dice_bag.get_available_dice().size() ; ++i){
                if(m_dice_bag.get_available_dice()[i].get_green()){
                    m_dice_bag.get_available_dice()[i].set_faces(reader.getSection("Dice").at("weak_dice_faces"));}}
                }}
    if (reader.getSection("Dice").find("strong_dice_faces") != reader.getSection("Dice").end()){
        if (!reader.getSection("Dice").at("strong_dice_faces").empty()){
            for (size_type i{0}; i < m_dice_bag.get_available_dice().size() ; ++i){
                if(m_dice_bag.get_available_dice()[i].get_yellow()){
                    m_dice_bag.get_available_dice()[i].set_faces(reader.getSection("Dice").at("strong_dice_faces"));}}}}
        if (reader.getSection("Dice").find("tough_dice_faces") != reader.getSection("Dice").end()){
        if (!reader.getSection("Dice").at("tough_dice_faces").empty()){
            for (size_type i{0}; i < m_dice_bag.get_available_dice().size() ; ++i){
                if(m_dice_bag.get_available_dice()[i].get_red()){
                    m_dice_bag.get_available_dice()[i].set_faces(reader.getSection("Dice").at("tough_dice_faces"));}}}}
    //DICE SECTION ERROR TREATMENT
    green_faces_are_ok = true;
    yellow_faces_are_ok = true;
    red_faces_are_ok = true;
    for (size_type i{0}; i < reader.getSection("Dice").at("weak_dice_faces").length() ; ++i){
        if (weak[i] != 'f' && weak[i] != 's' && weak[i] != 'b'){
            config_ok = false;
            error_msg = "There is a problem on your initializer file! Verify if the values of the Dice section is ok!\n";
            green_faces_are_ok = false;
            break;}}
    for (size_type i{0}; i < reader.getSection("Dice").at("strong_dice_faces").length() ; ++i){
        if (weak[i] != 'f' && strong[i] != 's' && weak[i] != 'b'){
            config_ok = false;
            error_msg = "There is a problem on your initializer file! Verify if the values of the Dice section is ok!\n";
            green_faces_are_ok = false;
            break;}}
    for (size_type i{0}; i < reader.getSection("Dice").at("tough_dice_faces").length() ; ++i){
        if (weak[i] != 'f' && tough[i] != 's' && weak[i] != 'b'){
            config_ok = false;
            error_msg = "There is a problem on your initializer file! Verify if the values of the Dice section is ok!\n";
            green_faces_are_ok = false;
            break;}}

    //RECALLING M_DICE_BAG OBJECT WITH INITIALIZER CONFIG
    m_dice_bag = *new DiceBag(m_weak_dice, m_strong_dice, m_tough_dice, weak, strong, tough);

    if (green_faces_are_ok && yellow_faces_are_ok && red_faces_are_ok && !gamesectiontypeerror){ config_ok = true; }
} 
  else if (initializer_amount > 1){
    multiple_initializer = true;
    error_msg = "This program cannot support more than one initializer files! Please choose just one!\n";
    config_ok = false;}
}

    /**
     * @brief Processes user input and other game events based on the current state.
     */
    void process_events(){
        if (m_current_state == INPUT_PLAYERS){
            std::string players_string;
            std::getline(std::cin, players_string);
            players_string.erase(0, players_string.find_first_not_of(" \t\n\r"));
            players_string.erase(players_string.find_last_not_of(" \t\n\r") + 1);

            if (players_string.empty()){
                m_current_state = END;
                return;
            }
            else if (players_string == ",") {
                error_msg = "Insert your players!\n"; 
            }
            else {
            std::stringstream ss(players_string);
            std::string player_name;

            m_player_list.clear();

            while (std::getline(ss, player_name, ',')) {
                //remove spaces
                player_name.erase(0, player_name.find_first_not_of(" \t\n\r"));
                player_name.erase(player_name.find_last_not_of(" \t\n\r") + 1);
                if (!player_name.empty()) {
                    m_player_list.emplace_back(player_name);
                } 
            }
            //Shuffle the player_list array
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(m_player_list.begin(), m_player_list.end(), g);
            m_current_player = &m_player_list[0];

            if (m_player_list.size() > m_max_players || m_player_list.size() < 2){
                error_msg = "Invalid player amount!\n";
            }
        }
    }
        else if (m_current_state == WAITING_ACTION){
            std::string act;
            std::getline(std::cin, act);
            
            if (act.empty()){m_current_player->set_decision("roll");} //Decided roll
            else if (act == "H"){ m_current_player->set_decision("skip");} //Decided Hold turn

            else if (act == "Q"){ 
                
                for (size_type i{0}; i < m_player_list.size() ; ++i ){
                    if (m_player_list[i] == *m_current_player){
                        m_player_list.erase(m_player_list.begin() + i);
                        m_current_player = &m_player_list[i];
                    }
                }
                m_current_player->set_decision("quit");
            } 
            else{ m_current_player->set_decision("invalid");}
    }
        else if(m_current_state == SKIP){
            m_current_player->set_turns_played(m_current_player->get_turns_played() + 1);
            m_dice_bag.restore_bag();

            for (size_type i{0}; i < m_player_list.size() ; ++i ){
                if (m_player_list[i] == *m_current_player){
                    if (i + 1 < m_player_list.size()){
                        m_current_player = &m_player_list[i+1];
                        break;
                    } else{ m_current_player = &m_player_list[0]; break;}
                }
            }
            m_current_player->set_brain(0);
            m_current_player->set_footprint(0);
            m_current_player->set_shotgun(0);
            }
        else if(m_current_state == DICE_ROLL){
            sorted_dice = m_dice_bag.sort_dices(3);

            for (ZDice& die : sorted_dice){
                std::string res = die.roll();

                std::string face_emoji;
                if (res == "s") face_emoji = "💥";
                else if (res == "f") face_emoji = "👣";
                else if (res == "b") face_emoji = "🧠";

                std::string color_emoji;
                if (die.get_green()) color_emoji = "🟩";
                else if (die.get_yellow()) color_emoji = "🟨";
                else if (die.get_red()) color_emoji = "🟥";

                if (res == "b"){ m_current_player->set_brain(m_current_player->getBrains() + 1); }
                else if (res == "f"){ m_current_player->set_footprint(m_current_player->getFootprints() + 1); }
                else if (res == "s"){ m_current_player->set_shotgun(m_current_player->getShotguns() + 1); }
            }

            m_dice_bag.add_to_used_dice(sorted_dice);

            if (m_dice_bag.get_available_dice_count() < 3) {
                std::cout << "Quantidade de dados na sacola é " << m_dice_bag.get_available_dice_count() << ". Chamando refill_bag." << std::endl;
                m_dice_bag.refill_bag();
    }
        }
        else if(m_current_state == CHECK_DICES){
        }
        else if (m_current_state == CHECK_BRAINS){
            m_current_player->set_total_brains(m_current_player->get_total_brains() + m_current_player->getBrains());
            if (m_current_player->get_total_brains() >= m_brains_to_win){
                m_possib_winner.push_back(*m_current_player);
            }
        }
        else if(m_current_state == POSSIB_WIN){

        }
};

    /**
     * @brief The core of the state machine. Updates the game state based on the
     * current state and recent events.
     */
    void update(){
        if (m_current_state == PLAYER_WIN || m_current_state == TIE){
            m_current_state = END;
            return;
        }
        if (m_current_state == START){
            if(config_ok){m_current_state = INPUT_PLAYERS;}
            else{ m_current_state = INVALID_CFG; }
        }
        else if (m_current_state == INPUT_PLAYERS){
            if (m_player_list.size() >= 2 && m_player_list.size() <= m_max_players){ 
                m_current_state = WELCOME;
            }
            else if (m_player_list.size() > m_max_players || m_player_list.size() < 2){ 
                m_current_state = INVALID_PLAYERS;
            }
        }
        else if (m_current_state == INVALID_PLAYERS){
            m_current_state = INPUT_PLAYERS;
        }
        else if (m_current_state == WELCOME){
            m_current_state = WAITING_ACTION;
        }
        else if (m_current_state == INVALID_CFG){
            m_current_state = END;
            if (m_current_state == PLAYER_WIN || m_current_state == TIE){
            m_current_state = END;
            return;
        }
        }
        else if (m_current_state == RESTORE_DICES){
            m_dice_bag.refill_bag();
            m_current_state = DICE_ROLL;
        }
        else if (m_current_state == WAITING_ACTION){
            if (m_current_player->decision() == "roll"){
                if (m_dice_bag.get_dices_amount() < 3) {
                    m_current_state = RESTORE_DICES;
                } else {
                    m_current_state = DICE_ROLL; 
                }
            }
            else if (m_current_player->decision() == "skip"){ m_current_state = CHECK_BRAINS; }
            else if (m_current_player->decision() == "quit") {
                if (m_player_list.size() == 1){
                    m_possib_winner.push_back(m_player_list[0]);
                    m_current_state = POSSIB_WIN; 
                }
                else {m_current_state = WAITING_ACTION;}
            }
            else if(m_current_player->decision() == "invalid"){ m_current_state = INVALID_ACTION; }
        }
        else if (m_current_state == INVALID_ACTION){
            m_current_state = WAITING_ACTION;
        }
        else if (m_current_state == SKIP){
            m_current_state = WAITING_ACTION;
        }
        else if (m_current_state == DICE_ROLL){
            m_current_state = CHECK_DICES;
        }
        else if (m_current_state == CHECK_DICES){
            if (m_current_player->getFootprints() >= 3){ m_current_state = CHECK_BRAINS;}
            else if (m_current_player->getShotguns() >= 3){ m_current_state = SKIP; }
            else{ m_current_state = WAITING_ACTION;}
        }
        else if (m_current_state == CHECK_BRAINS){
            if (m_current_player->get_total_brains() >= m_brains_to_win){
                m_current_state = POSSIB_WIN;
            } else{m_current_state = SKIP;}
        }

        else if (m_current_state == POSSIB_WIN){
            auto aux1 = true;
            if (m_current_player->get_total_brains() >= m_brains_to_win){
                for (size_type i{0}; i < m_player_list.size(); ++i){
                    auto aux = m_player_list[0].get_turns_played();
                    if (m_player_list[i].get_turns_played() != aux){
                        aux1 = false;
                    }
                }
                if (aux1 && m_possib_winner.size() == 1){m_current_state = PLAYER_WIN;}
                else{ m_current_state = SKIP; }
            }
            else {m_current_state = SKIP;}
        }
        else if (m_current_state == RESTORE_DICES){
            
            m_current_state = DICE_ROLL;
        }
        else if (m_current_state == REMOVE_BRAINS){
            
            m_current_state = SKIP;
        }
        else if (m_possib_winner.size() == 1){
            
            m_current_state = PLAYER_WIN;
        }
        else if (m_possib_winner.size() > 1){
            
        }
        else if (check_tie()){
            m_current_state = TIE;
        }

    };

    /**
     * @brief Renders the user interface to the console based on the current game state.
     */
    void render() {
        switch (m_current_state) {
            case WELCOME: {
                std::cout << "\n         ---> Welcome to the Zombi Dice game (v 0.1) <--\n";
                std::cout << "                -- copyright DIMAp/UFRN 2024-2025 --\n\n";
                std::cout << "  The object of the jeopardy dice game Zombie Dice is to be the\n";
                std::cout << "  first to eat " << m_brains_to_win << " or more human brains in a turn.\n";
                std::cout << "  Each player's turn consists of repeatedly rolling 3 dice.\n";
                std::cout << "  A dice may produce 3 outcomes: you ate a brain, the human escaped,\n";
                std::cout << "  or you were shot!\n";
                std::cout << "  If you get shot 3 or more times you die and loose all brains you\n";
                std::cout << "  ate in that turn; then the turn goes to the next player.\n";
                std::cout << "  However, if you decide to stop before get shot 3 times, you keep\n";
                std::cout << "  the brains you ate.\n\n";

                if (!m_game_initialized) { //if the game haven't started
                    std::cout << "\n  >>> The players of the game are:\n";
                    for (const auto& player : m_player_list) {
                        std::cout << "\"" << player.getName() << "\"\n";
                    }
                    std::cout << "\n  >>> The player who will start the game is \"" << m_current_player->getName() << "\"\n";
                    std::cout << "  Press <Enter> to start the match.";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    start_game();
                }
                break;
            }
            case INPUT_PLAYERS: {
                std::cout << "  Before we begin, please enter the names of the players\n";
                std::cout << "  in a single line, separated by comma. For example:\n";
                std::cout << "  >>> Jack , Menace, Ultraz, Boris\n\n";
                std::cout << "  Minimum of 2 player, maximum of " << m_max_players << " names.\n";
                std::cout << "  Providing an empty line will end the game.\n";
                std::cout << ">>> ";
                break;
            }
            case WAITING_ACTION: {
                if (m_game_initialized){
                    std::cout << "  -->[🧟] Zombie Dice Delux, v 0.1 [🧟]<--\n\n";
                    std::cout << " ┌─────────────────────────────────────────┐\n";
                    std::cout << " │               Global Score              │\n";
                    std::cout << " └─────────────────────────────────────────┘\n";

                    for (const auto& player : m_player_list) {
                        if (player.getName() == m_current_player->getName()) {
                            std::cout << " > ";
                        } else {
                            std::cout << "   ";
                        }
                        std::cout << std::left << std::setw(10) << (player.getName() + ":")
                                  << "(" << player.get_total_brains() << "), "
                                  << "# turns played: " << player.get_turns_played() << "\n";
                    }

                    std::cout << "Player: \"" << m_current_player->getName() << "\"";
                    std::cout << " | Turn #: " << m_current_round;
                    std::cout << " | Bag has: " << m_dice_bag.get_dices_amount() << " 🎲.\n\n";
                    
                    std::cout << "┌─────────────────┐\n";
                    std::cout << "│   Rolling Table │\n";
                    std::cout << "├─────┬─────┬─────┤\n";
                    std::cout << "│     │     │     │\n";
                    std::cout << "└─────┴─────┴─────┘\n\n";

                    std::cout << "🧠 Brains: (" << m_current_player->getBrains() << ")\n";
                    std::cout << "💥 Shots:  (" << m_current_player->getShotguns() << ")\n\n";

                    std::cout << "┌─[ Message area ]───────────────────┐\n";
                    std::cout << "│ Ready to play?                     │\n";
                    std::cout << "│ <enter>     - roll dices           │\n";
                    std::cout << "│ H + <enter> - hold turn            │\n";
                    std::cout << "│ Q + <enter> - quit game            │\n";
                    std::cout << "└────────────────────────────────────┘\n";
                    std::cout << "🧟> ";
                }
                break;
            }
            case INVALID_PLAYERS: {
                std::cout << error_msg;
                break;
            }
            case INVALID_CFG: {
                std::cout << error_msg;
                break;
            }

            case CHECK_DICES: {
                std::cout << "  -->[🧟] Zombie Dice Delux, v 0.1 [🧟]<--\n\n";
                std::cout << " ┌─────────────────────────────────────────┐\n";
                std::cout << " │               Global Score              │\n";
                std::cout << " └─────────────────────────────────────────┘\n";

                for (const auto& player : m_player_list) {
                    if (player.getName() == m_current_player->getName()) {
                        std::cout << " > ";
                    } else {
                        std::cout << "   ";
                    }
                    std::cout << std::left << std::setw(15) << (player.getName() + ":")
                          << std::setw(3) << player.get_total_brains()
                          << " brains, " << player.get_turns_played() << " turns\n";
                }

                std::cout << " ───────────────────────────────────────────\n";
                std::cout << " Player: \"" << m_current_player->getName() << "\"";
                std::cout << " | Turn #" << m_current_player->get_turns_played() + 1;
                std::cout << " | Bag has: " << m_dice_bag.get_dices_amount() << " 🎲.\n\n";

                std::cout << "┌─── Rolling Table ───┐\n";
                std::cout << "│ ";
                if (m_current_state == CHECK_DICES && !sorted_dice.empty()) {
                    for (const auto& die : sorted_dice) {
                        std::string face_emoji = (die.get_result() == "b") ? "🧠" : (die.get_result() == "s") ? "💥" : "👣";
                        std::string color_emoji = (die.get_green()) ? "🟩" : (die.get_yellow()) ? "🟨" : "🟥";
                        std::cout << face_emoji << "(" << color_emoji << ") ";
                    }
                } else {
                 std::cout << "      🎲 🎲 🎲      ";
                }
                std::cout << "│\n";
                std::cout << "└─────────────────────┘\n\n";

                std::cout << "🧠 Brains this turn: (" << m_current_player->getBrains() << ")\n";
                std::cout << "💥 Shots this turn:  (" << m_current_player->getShotguns() << ")\n\n";

                std::cout << "┌─[ Message area ]─────────────────────────────────┐\n";
                if (m_current_player->getShotguns() >= 3) {
                    std::cout << "│ YOU DIED! 💀 You took 3 shots and lost your brains! │\n";
                    std::cout << "│ Press <enter> to pass the turn.                  │\n";
                } else if (m_current_state == CHECK_DICES) {
                    std::cout << "│ You ate " << m_current_player->getBrains() << " brain(s) and took " << m_current_player->getShotguns() << " shot(s) so far.    │\n";
                    std::cout << "│                                                  │\n";
                } else {
                    std::cout << "│ Your turn, " << m_current_player->getName() << "! Ready to roll?               │\n";
                    std::cout << "│ <enter> - roll dices | H + <enter> - hold & score │\n";
                }
                std::cout << "└──────────────────────────────────────────────────┘\n";
                
                std::cout << "🧟> ";
                break;
            }

            case PLAYER_WIN: {
                std::cout << "┌─[ Message area ]───────────────────┐\n";
                std::cout << "│ Game Over!                         │\n";
                std::cout << "│                                    │\n";
                std::cout << "|                                    |\n";
                std::cout << "└────────────────────────────────────┘\n\n";

                std::cout << ">>> THE WINNER IS \"" << m_possib_winner[0].getName() << "\"";
            }
        }
    };

    //== UTILITY METHODS ==//
    /**
     * @brief Sets the flag to indicate the main game has started (post-welcome screen).
     */
    void start_game() { m_game_initialized = true;}

    bool check_tie() {
        return false;
    };

    /**
     * @brief Checks if the game has reached its final state.
     * @return true If the current state is END, false otherwise.
     */
    bool game_over() {
        return m_current_state == END;
    };    

     //== SINGLETON ACCESSOR ==//
    /**
     * @brief Provides access to the single instance of the GameController.
     * @return GameController& A reference to the Singleton instance.
     */
    static GameController& getInstance(){
        static GameController gc;
        return gc;
    } 

    //== GETTERS AND SETTERS ==//
    /**
     * @brief Gets the name of the initializer file.
     * @return std::string The name of the .ini file.
     */
    std::string get_initializer(){ return initializer_name; }

    /**
     * @brief Gets the number of initializer files provided.
     * @return size_type The count of .ini files.
     */
    size_type get_initializer_amount(){ return initializer_amount; };

    /**
     * @brief Checks if the configuration is valid.
     * @return true If the config is ok, false otherwise.
     */
    bool get_config_ok() { return config_ok; }

    /**
     * @brief Sets the name of the initializer file.
     * @param ini The name of the .ini file.
     */
    void set_initializer(std::string ini){ initializer_name =  ini;}

    /**
     * @brief Sets the number of initializer files.
     * @param amount The count of .ini files.
     */
    void set_initializer_amount(size_type amount){ initializer_amount = amount; }

    //== DELETED FUNCTIONS ==//
    /**
     * @brief Deleted copy constructor to prevent copying the Singleton.
     */
    GameController(const GameController&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent copying the Singleton.
     */
    GameController& operator=(const GameController&) = delete;
};  