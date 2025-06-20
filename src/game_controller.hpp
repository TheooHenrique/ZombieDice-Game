#include <cstdint>
#include <vector>
#include "dicebag.hpp"
#include "player.hpp"
class GameController{
    using size_type = std::size_t;
    private:
    //INSERIR CONSTRUTOR COMO PRIVADO. (TEMPLATE SINGLETON)

    //ATTRIBUTES:
    //Note that this values are the default values. They can be overriden by the initializer.
    uint8_t m_current_state = START;
    size_type m_brains_to_win = 13;
    size_type m_current_round;
    size_type m_max_players = 3;
    size_type m_max_turn = 0;
    std::vector<std::string> m_player_list = {"theo", "haniel"}; //ESTE NÃO PODE TER UM DEFAULT. DEVE SER DEFINIDO PELO USUÁRIO NA ENTRADA DO PROGRAMA.
    std::vector<std::string> m_possib_winner;
    DiceBag m_dice_bag;
    Player m_current_player;


    enum m_possible_states : uint8_t{
    START,              ///start the game
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
            //INSIRA AQUI O QUE VAI SER MOSTRADO QUANDO O ESTADO ESTIVER EM START
        }
    };


    void update(){ //O que tiver de comentário aqui, a maioria são para funções que DEVEM SER ADICIONADAS NO "PROCESS_EVENTS". "Update" é só para receber os gatilhos e
        // a partir deles, trocar para o estado desejado.
        if (m_current_state == START){
            if(config_ok()) { m_current_state = INPUT_PLAYERS;} //Caso as configs estejam ok
            else {m_current_state = INVALID_CFG;} //Caso tenha erro nas configs
        }
        if (m_current_state == INVALID_CFG){
            //FUNÇÃO PARA MOSTRAR ERRO DE CONFIG INVALIDA
            m_current_state = START;
        }
        if (m_current_state == INPUT_PLAYERS){
            if (m_player_list.size() <= m_max_players){ //Caso a quantidade de players esteja ok
                m_current_state = WAITING_ACTION;
            }
            if (m_player_list.size() > m_max_players){ //Caso a lista de player seja inválida
                m_current_state = INVALID_PLAYERS;
            }
        }
        if (m_current_state == INVALID_PLAYERS){
            //FUNÇÃO PARA MOSTRAR ERRO DE PLAYERS INVALIDOS
            m_current_state = INPUT_PLAYERS;
        }
        if (m_current_state == WAITING_ACTION){
            m_current_state = m_current_player.decision() ? DICE_ROLL : SKIP;
            if (m_current_player.decision() != true || m_current_player.decision() != false){ m_current_state = INVALID_ACTION;}
        }
        if (m_current_state == INVALID_ACTION){
            //FUNÇÃO PARA MOSTRAR ERRO DE AÇÃO INVÁLIDA
            m_current_state = WAITING_ACTION;
        }
        if (m_current_state == SKIP){
            //Função para skippar para o próximo player
            m_current_state = WAITING_ACTION;
        }
        if (m_current_state == DICE_ROLL){
            //Função para o dado rodar
            m_current_state = CHECK_DICES;
        }
        if (m_current_state == CHECK_DICES){
            //Função para checar se tem 3 run ou 3 shotgun
            //Função para checar se o player chegou na quantidade maxima de cerebros
            if (m_current_player.m_total_brains >= m_brains_to_win){ 
                //Função que passa o player pra uma lista de possíveis vencedores
            }
            if (m_dice_bag.m_current_count_dices <= 3){ m_current_state = RESTORE_DICES;}
            if (m_current_player.m_run_round >= 3){ m_current_state = SKIP;}
            else if (m_current_player.m_shots_round >= 3) {m_current_state = REMOVE_BRAINS;}
        }
        if (m_current_state == RESTORE_DICES){
            //Função para dar restore nos dados.
            m_current_state = DICE_ROLL;
        }
        if (m_current_state == REMOVE_BRAINS){
            //Função para remover cérebros
            m_current_state = SKIP;
        }
        if (m_possib_winner.size() == 1){
            //Função que declara o unico jogador em possibwinner como winner
            m_current_state = PLAYER_WIN;
        }
        if (m_possib_winner.size() > 1){
            //Função que tira todos os jogadores que não são possible winners da lista de jogadores.
        }
        if (check_tie()){
            //imprime mensagem dizendo que empatou entre X players
            m_current_state = TIE;
        }
        if (m_current_state == PLAYER_WIN || m_current_state == TIE){
            //acaba
            m_current_state = END;
        }
    };

    void render();
    void start_game();
    bool check_tie();
    bool game_over() {
        if (m_current_state == END){
            return true;
        }
        return false;
    };
    void setup_players();
    void next_player();
    void untie();
    bool has_tie();
    bool config_ok();
    static void getInstance(); //MÉTODO PARA CHAMAR O CONSTRUTOR (SEMPRE DEVE DEVOLVER O MESMO OBJETO CONSTRUÍDO)


};  