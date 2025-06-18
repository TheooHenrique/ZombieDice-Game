
#include <cstdint>
class GameController{
    public:
    void parse_config();
    void update();
    void process_events();
    void render();
    void game_over();

    enum m_possible_states : uint8_t{
        START,              ///start the game
        INVALID_CFG,        ///if the configuration file is invalid
        INPUT_PLAYERS,      ///wait for the user input player list
        INVALID_PLAYERS,    ///if the player list is invalid
        WAITING_ACTION,     ///waiting for the player action
        INVALID_ACTION,
        SKIP,
        DICE_ROLL,
        REMOVE_BRAINS,
        RESTORE_DICES,
        PLAYER_WIN,
        TIE,
        END
    };
};