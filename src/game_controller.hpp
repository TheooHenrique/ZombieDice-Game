#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "dicebag.hpp"
#include "player.hpp"
#include "reader.hpp"
#include <algorithm>
#include <random>
#include <limits>

class GameController{
    using size_type = std::size_t;
    private:

    //Default constructor
    GameController() : m_current_state(START), m_brains_to_win(13), m_current_round(1),
        m_max_players(6),
        m_max_turn(0),
        m_current_player(),
        initializer_amount(0),
        m_game_initialized(false) {}

    //ATTRIBUTES:
    uint8_t m_current_state;
    size_type m_brains_to_win;
    size_type m_current_round;
    size_type m_max_players;
    size_type m_max_turn;
    size_type m_weak_dice;
    size_type m_tough_dice;
    size_type m_strong_dice;
    std::vector<Player> m_player_list;
    std::vector<Player> m_possib_winner;
    DiceBag m_dice_bag;
    Player m_current_player;
    std::string initializer_name;
    size_type initializer_amount;
    std::string error_msg;
    bool m_game_initialized;


    enum m_possible_states : uint8_t{
    START,              ///start the game
    WELCOME,            ///print the welcome msg
    INVALID_CFG,        ///if the configuration file is invalid
    INPUT_PLAYERS,      ///wait for the user input player list
    INVALID_PLAYERS,    ///if the player list is invalid
    WAITING_ACTION,     ///waiting for the player action
    INVALID_ACTION,     ///if the inputed action is a non-valid action
    SKIP,               ///skipping the player
    DICE_ROLL,          ///rolling the dice
    CHECK_DICES,        ///verify if a player has three run or shotgun
    REMOVE_BRAINS,      ///remove the brains if the user take three shots
    RESTORE_DICES,      ///print the current brain amount and put all the dices in the bag
    POSSIB_WIN,         ///put the player in the list that can win if this round end
    PLAYER_WIN,         ///one player won the game
    TIE,                ///two or more players won the game (max turn reached)
    END                 ///end the game
};

    //METHODS:
    public:

    void parse_config();
    void process_events(){
        if (m_current_state == START){

        }
        else if (m_current_state == WELCOME){
            if(initializer_amount == 1){
                //Call Reader's constructor
                Reader reader(initializer_name);
                //Override gc attributes with initializer config

                //Tá faltando verificar "Game.at("brains_to_win")" exite.
                if (!reader.getSection("Game").at("brains_to_win").empty()){
                    m_brains_to_win = std::stoi(reader.getSection("Game").at("brains_to_win")); }
                if (!reader.getSection("Game").at("max_turns").empty()){
                    m_max_turn = std::stoi(reader.getSection("Game").at("max_turns")); }
                if (!reader.getSection("Game").at("max_player").empty()){
                    m_max_players = std::stoi(reader.getSection("Game").at("max_players")); }
                if (!reader.getSection("Game").at("weak_dice").empty()){
                    m_weak_dice = std::stoi(reader.getSection("Game").at("weak_dice")); }
                if (!reader.getSection("Game").at("tough_dice").empty()){
                    m_tough_dice = std::stoi(reader.getSection("Game").at("tough_dice")); }
                if (!reader.getSection("Game").at("strong_dice").empty()){
                    m_strong_dice = std::stoi(reader.getSection("Game").at("strong_dice")); }

                if (!reader.getSection("Dice").at("weak_dice_faces").empty()){
                    for (size_type i{0}; i < m_dice_bag.get_available_dice().size() ; ++i)
                    m_dice_bag.get_available_dice()[i].set_faces(reader.getSection("Game").at("weak_dice"));}
                if (!reader.getSection("Dice").at("tough_dice_faces").empty()){
                    for (size_type i{0}; i < m_dice_bag.get_available_dice().size() ; ++i)
                    m_dice_bag.get_available_dice()[i].set_faces(reader.getSection("Game").at("tough_dice")); }
                if (!reader.getSection("Dice").at("strong_dice_faces").empty()){
                    for (size_type i{0}; i < m_dice_bag.get_available_dice().size() ; ++i)
                    m_dice_bag.get_available_dice()[i].set_faces(reader.getSection("Game").at("strong_dice"));}

            } 
            //Colocar isso no render depois:
            else if (initializer_amount > 1){ error_msg = "Não é possível iniciar o programa com dois arquivos inicializadores! Digite somente um!"; }

        }
        else if (m_current_state == INVALID_CFG){
            //Colocar isso no render depois:
            error_msg = "Erro! Alguma configuração que você inseriu no arquivo \"zdice.ini\" está errada! \n Se atente a ler as instruções de maneira correta.\n";
        }
        else if (m_current_state == INPUT_PLAYERS){
            std::string players_string;
            std::getline(std::cin, players_string);

            if (players_string.empty()) {
                m_current_state = END;
                return;
            }

            std::stringstream ss(players_string);
            std::string player_name;

            m_player_list.clear();

            while (std::getline(ss, players_string, ',')) {
                //remove spaces
                player_name.erase(0, player_name.find_first_not_of(" \t\n\r"));
                player_name.erase(player_name.find_last_not_of(" \t\n\r") + 1);

                if (!player_name.empty()) {
                    m_player_list.emplace_back(player_name); //emplace_back does not receive an object, but rather the arguments to the constructor of the object you want to create. It then forwards these arguments to the constructor of the container's object type and constructs the object directly in memory already allocated at the end of the container.
                }
            }
    }
};


    void update(){ //O que tiver de comentário aqui, a maioria são para funções que DEVEM SER ADICIONADAS NO "PROCESS_EVENTS". "Update" é só para receber os gatilhos e
        // a partir deles, trocar para o estado desejado.
        if (m_current_state == START){
            m_current_state = WELCOME;
        }
        else if (m_current_state == WELCOME){
            if(config_ok()) { m_current_state = INPUT_PLAYERS;} //Caso as configs estejam ok
            else {m_current_state = INVALID_CFG;} //Caso tenha erro nas configs
        }
        else if (m_current_state == INVALID_CFG){
            //FUNÇÃO PARA MOSTRAR ERRO DE CONFIG INVALIDA
            m_current_state = START;
        }
        else if (m_current_state == INPUT_PLAYERS){
            if (m_player_list.size() >= 2 && m_player_list.size() <= m_max_players){ //Caso a quantidade de players esteja ok
                std::random_device rd;
                std::mt19937 g(rd());
                std::shuffle(m_player_list.begin(), m_player_list.end(), g);

                m_current_player = m_player_list[0];

                m_current_state = WAITING_ACTION;
            }
            if (m_player_list.size() > m_max_players){ //Caso a lista de player seja inválida
                m_current_state = INVALID_PLAYERS;
            }
        }
        else if (m_current_state == INVALID_PLAYERS){
            //FUNÇÃO PARA MOSTRAR ERRO DE PLAYERS INVALIDOS
            m_current_state = INPUT_PLAYERS;
        }
        else if (m_current_state == WAITING_ACTION){
            m_current_state = m_current_player.decision() ? DICE_ROLL : SKIP;
            if (m_current_player.decision() != true || m_current_player.decision() != false){ m_current_state = INVALID_ACTION;}
        }
        else if (m_current_state == INVALID_ACTION){
            //FUNÇÃO PARA MOSTRAR ERRO DE AÇÃO INVÁLIDA
            m_current_state = WAITING_ACTION;
        }
        else if (m_current_state == SKIP){
            //Função para skippar para o próximo player
            m_current_state = WAITING_ACTION;
        }
        else if (m_current_state == DICE_ROLL){
            //Função para o dado rodar
            m_current_state = CHECK_DICES;
        }
        else if (m_current_state == CHECK_DICES){
            //Função para checar se tem 3 run ou 3 shotgun
            //Função para checar se o player chegou na quantidade maxima de cerebros
            if (m_current_player.get_total_brains() >= m_brains_to_win){ 
                //Função que passa o player pra uma lista de possíveis vencedores
            }
            if (m_dice_bag.get_current_count() <= 3){ m_current_state = RESTORE_DICES;}
            if (m_current_player.getFootprints() >= 3){ m_current_state = SKIP;}
            else if (m_current_player.getShotguns() >= 3) {m_current_state = REMOVE_BRAINS;}
        }
        else if (m_current_state == RESTORE_DICES){
            //Função para dar restore nos dados.
            m_current_state = DICE_ROLL;
        }
        else if (m_current_state == REMOVE_BRAINS){
            //Função para remover cérebros
            m_current_state = SKIP;
        }
        else if (m_possib_winner.size() == 1){
            //Função que declara o unico jogador em possibwinner como winner
            m_current_state = PLAYER_WIN;
        }
        else if (m_possib_winner.size() > 1){
            //Função que tira todos os jogadores que não são possible winners da lista de jogadores.
        }
        else if (check_tie()){
            //imprime mensagem dizendo que empatou entre X players
            m_current_state = TIE;
        }
        else if (m_current_state == PLAYER_WIN || m_current_state == TIE){
            //acaba
            m_current_state = END;
        }
    };

    void render() {
        switch (m_current_state) {
            case WELCOME: {
                std::cout << "\n         ---> Welcome to the Zombi Dice game (v 0.1) <--\n";
                std::cout << "                -- copyright DIMAp/UFRN 2024-2025 --\n\n";
                std::cout << "  The object of the jeopardy dice game Zombie Dice is to be the\n";
                std::cout << "  first to eat " << m_brains_to_win << " or more human brains in a turn.\n"; // Usa a variável de configuração
                std::cout << "  Each player's turn consists of repeatedly rolling 3 dice.\n";
                std::cout << "  A dice may produce 3 outcomes: you ate a brain, the human escaped,\n";
                std::cout << "  or you were shot!\n";
                std::cout << "  If you get shot 3 or more times you die and loose all brains you\n";
                std::cout << "  ate in that turn; then the turn goes to the next player.\n";
                std::cout << "  However, if you decide to stop before get shot 3 times, you keep\n";
                std::cout << "  the brains you ate.\n\n";
                std::cout << "  Before we begin, please enter the names of the players\n";
                std::cout << "  in a single line, separated by comma. For example:\n";
                std::cout << "  >>> Jack , Menace, Ultraz, Boris\n\n";
                std::cout << "  Minimum of 2 player, maximum of " << m_max_players << " names.\n";
                std::cout << "  Providing an empty line will end the game.\n";
                break;
            }
            case INPUT_PLAYERS: {
                std::cout << " >>> ";
                break;
            }
            case WAITING_ACTION: {
                if (!m_game_initialized) { //if the game haven't started
                    std::cout << "\n  >>> The players of the game are:\n";
                    for (const auto& player : m_player_list) {
                        std::cout << "  \"" << player.getName() << "\"\n";
                    }

                    std::cout << "\n  >>> The player who will start the game is \"" << m_current_player.getName() << "\"\n";
                    std::cout << "  Press <Enter> to start the match.";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer e espera o Enter

                    m_game_initialized = true;
                }
                //TODO resto
                break;
            }
            case INVALID_PLAYERS: {
                std::cout << error_msg;
            }
        }
    };
    void start_game();
    bool check_tie() {
        // Lógica temporária: nunca há empate.
        // TODO: Implementar a verificação de empate.
        return false;
    };
    bool game_over() {
        return m_current_state == END;
    };
    void setup_players();
    void next_player();
    void untie();
    bool has_tie();
    bool config_ok() {
        // Lógica temporária: sempre retorna true por enquanto.
        // TODO: Implementar a validação real do arquivo de configuração.
        return true;
    };

    static GameController& getInstance(){ //Call the unique object of the class
        static GameController gc;
        return gc;
    } 

    //GET METHODS:
    std::string get_initializer(){ return initializer_name; }
    size_type get_initializer_amount(){ return initializer_amount; };

    //SET METHODS:
    void set_initializer(std::string ini){ initializer_name =  ini;}
    void set_initializer_amount(size_type amount){ initializer_amount = amount; }

    GameController(const GameController&) = delete;
    GameController& operator=(const GameController&) = delete;
};  