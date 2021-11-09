/**
 * @file block_schema.h
 * @author Richard Filo (xfilor00)
 * @brief Trieda pre vytvorenie modifikaciu a naslednu simulaciu blokovej schemy
 * @date 2021-05-06
 */

#ifndef BLOCK_SCHEMA_H
#define BLOCK_SCHEMA_H

#include "block.h"
#include <unordered_map>
#include <utility>  //pair

/**
 * @brief Struktura reprezentujuca port, tvorena z mena bloku a indexu portu
 * 
 */
typedef struct{
    /**
     * @brief meno bloku
     * 
     */
    std::string block_name;

    /**
     * @brief index portu
     * 
     */
    int port_index;
} Port;

/**
 * @brief Trieda reprezentujuca blokove schema
 * 
 */
class Block_schema
{

public:
    /**
     * @brief Skonstruuje prazdne blokove schema
     * 
     */
    Block_schema();

    /**
     * @brief Destruuje blokove schema s jeho vsetkymi blokmi
     * 
     */
    ~Block_schema();

    /**
     * @brief Prida blok daneho typu do schemy a vrati jeho meno
     * 
     * @param type typ bloku
     * @return std::string vygenerovane unikatne meno bloku
     */
    std::string add_block(Block_type type);

    /**
     * @brief Odstrani blok so vsetkymi jeho spojami zo schemy
     * 
     * @param block_name meno bloku
     */
    void remove_block(std::string block_name);

    /**
     * @brief Pokusi sa o zmenu mena daneho bloku
     * 
     * @param block_name meno bloku ktory ideme modifikovat
     * @param name nove meno bloku
     * @return int 0 -> zmena prebehla v poriadku, -1 -> blok neexistuje, 1 -> dane meno uz existuje
     */
    int change_block_name(std::string block_name, std::string name);

    /**
     * @brief Nastavi dany vstup daneho bloku na hodnotu definovanu hodnotou
     * 
     * @param value hodnota
     * @param block_name meno bloku
     * @param index index vstupu
     * @return int 0 -> zmena prebehla v poriadku, -1 -> blok neexistuje, 1 -> vstup je definovany spojom
     */
    int set_block_input_by_index(int value, std::string block_name, int index);

    /**
     * @brief Vrati popis daneho bloku
     * 
     * @param block_name meno bloku
     * @return std::string 
     */
    std::string get_block_label(std::string block_name);

    /**
     * @brief Vrati zoznam vstupov daneho bloku
     * 
     * @param block_name meno bloku
     * @return std::vector<std::vector<int>> 
     */
    std::vector<std::vector<int>> get_block_inputs(std::string block_name);

    /**
     * @brief Vrati zoznam vystupov daneho bloku
     * 
     * @param block_name meno bloku
     * @return std::vector<std::vector<int>> 
     */
    std::vector<std::vector<int>> get_block_outputs(std::string block_name);

    /**
     * @brief Prida spojenie medzi vystupom a vstupom danych blokov
     * 
     * @param block1 meno prveho bloku
     * @param index_output1 index vystupu prveho bloku
     * @param block2 meno druheho bloku
     * @param index_input2 index vstupu druheho bloku
     * @return int 0 -> pridanie prebehlo v poriadku, 1 -> spoj uz existuje
     */
    int add_junction(std::string block1, int index_output1, std::string block2, int index_input2);

    /**
     * @brief Odstrani spojenie medzi vystupom a vstupom danych blokov
     * 
     * @param block1 meno prveho bloku
     * @param index_output1 index vystupu prveho bloku
     * @param block2 meno druheho bloku
     * @param index_input2 index vstupu druheho bloku 
     */
    void remove_junction(std::string block1, int index_output1, std::string block2, int index_input2);

    /**
     * @brief Realizuje simulaciu a priebezne vypisuje stavy
     * 
     * @return int int 0 -> simulacia prebehla v poriadku, 1 -> detekovana cyklicka zavislost
     */
    int simulate();

    /**
     * @brief Vrati kod v C++ realizujuci toto schema
     * 
     * @return std::string 
     */
    std::string generate_sim_code();

private:
    /**
     * @brief Mnozina blokov
     * 
     */
    std::unordered_map<std::string, Block*> blocks;

    /**
     * @brief Mnozina spojeni
     * 
     */
    std::vector<std::pair<Port, Port>> junctions;

    /**
     * @brief Kalendar udalosti potrebny pre simulaciu
     * 
     */
    std::vector<std::pair<Port, std::vector<int>>> event_calendar;

    /**
     * @brief kod v C++ obsahujuci funkcie modifikujuce toto schema
     * 
     */
    std::string code_modification;

    /**
     * @brief Generuje a vrati unikatne meno pomocou daneho prefixu
     * 
     * @param prefix prefix generovaneho mena
     * @return std::string 
     */
    std::string gen_name(std::string prefix);

    /**
     * @brief Odstrani vsetky spojenia daneho bloku
     * 
     * @param block_name meno bloku
     */
    void remove_junc_of_block(std::string block_name);

    /**
     * @brief Odstrani vsetky udalosti spojene s danym blokom
     * 
     * @param block_name meno bloku
     */
    void remove_event_of_block(std::string block_name);

    /**
     * @brief Odstrani vsetky udalosti spojene s danym portom
     * 
     * @param block meno bloku
     * @param index_input index portu
     */
    void remove_event_of_port(std::string block, int index_input);

    /**
     * @brief Zmeni meno bloku v mnozine spojov
     * 
     * @param pre_name predchadzajuce meno
     * @param new_name nove meno
     */
    void change_name_in_junctions(std::string pre_name, std::string new_name);

    /**
     * @brief Zmeni meno bloku v kalendari udalosti
     * 
     * @param pre_name predchadzajuce meno
     * @param new_name nove meno
     */
    void change_name_in_calendar(std::string pre_name, std::string new_name);
};

#endif // BLOCK_SCHEMA_H