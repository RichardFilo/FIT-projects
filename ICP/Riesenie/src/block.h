/**
 * @file block.h
 * @author Richard Filo (xfilor00)
 * @brief Triedy pre vytvorenie blokov a pracu s nimi
 * @date 2021-05-06
 */

#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <string>

/**
 * @brief Trieda reprezentujuca vseobecny blok
 * 
 */
class Block
{

public:
    /**
     * @brief Skonstuuje vseobecny blok
     * 
     */
    Block();

    /**
     * @brief Destruuje vseobecny blok
     * 
     */
    virtual ~Block(){}

    /**
     * @brief Nastavi meno bloku
     * 
     * @param name meno
     */
    void set_name(std::string name);

    /**
     * @brief Nastavi popis bloku
     * 
     * @param label popis
     */
    void set_label(std::string label);

    /**
     * @brief Nastavi dany vstup na zadanu hodnotu
     * 
     * @param input hodnota
     * @param index index vstupu
     */
    void set_input_by_index(std::vector<int> input, int index);

    /**
     * @brief Vrati meno bloku
     * 
     * @return std::string
     */
    std::string get_name();

    /**
     * @brief Vrati popis bloku
     * 
     * @return std::string 
     */
    std::string get_label();

    /**
     * @brief Vrati zoznam vstupov
     * 
     * @return std::vector<std::vector<int>> 
     */
    std::vector<std::vector<int>> get_inputs();

    /**
     * @brief Vrati zoznam vystupov
     * 
     * @return std::vector<std::vector<int>> 
     */
    std::vector<std::vector<int>> get_outputs();

    /**
     * @brief Vrati hodnotu zadaneho vstupu
     * 
     * @param index index vstupu
     * @return std::vector<int> 
     */
    std::vector<int> get_input_by_index(int index);

    /**
     * @brief Vrati hodnotu zadaneho vystupu
     * 
     * @param index index vystupu
     * @return std::vector<int> 
     */
    std::vector<int> get_output_by_index(int index);

    /**
     * @brief Vrati pocet vstupov
     * 
     * @return int 
     */
    int get_input_count();

protected:
    /**
     * @brief meno bloku
     * 
     */
    std::string name;

    /**
     * @brief popis bloku
     * 
     */
    std::string label;

    /**
     * @brief zoznam vstupov
     * 
     */
    std::vector<std::vector<int>> inputs;   // { { 1 <-isDefined(0-No, 1-by_value, 2-by_wire) , 4 <- value }, ...}

    /**
     * @brief zoznam vystupov
     * 
     */
    std::vector<std::vector<int>> outputs;  // { { 1 <-isDefined(0,1) , 4 <- value }, ...}

    /**
     * @brief Prepocita a nastavi vystup
     * 
     */
    virtual void do_operation() = 0;
};

/**
 * @brief Trieda reprezentujuca blok scitania
 * 
 */
class Block_sum: public Block
{

public:
    /**
     * @brief Skonstruuje blok na scitanie 2 hodnot
     * 
     * @param inputs zoznam hodnot vstupov
     * @param name meno bloku
     */
    Block_sum(std::vector<std::vector<int>> inputs = {{0,0}, {0,0}}, std::string name = "");

    /**
     * @brief Spocita vstup 0 a 1 a vysledok nastavy na vystup 0
     * 
     */
    void do_operation();
};

/**
 * @brief Trieda reprezentujuca blok odcitania
 * 
 */
class Block_sub: public Block
{

public:
    /**
     * @brief Skonstruuje blok na odcitanie 2 hodnot
     * 
     * @param inputs zoznam hodnot vstupov
     * @param name meno bloku
     */
    Block_sub(std::vector<std::vector<int>> inputs = {{0,0}, {0,0}}, std::string name = "");

    /**
     * @brief Odcita vstup 1 od vstupu 0 a vysledok nastavy na vystup 0
     * 
     */
    void do_operation();
};

/**
 * @brief Trieda reprezentujuca blok inkrementacie
 * 
 */
class Block_inc: public Block
{

public:
    /**
     * @brief Skonstruuje blok na inkrementaciu
     * 
     * @param inputs zoznam hodnot vstupov
     * @param name meno bloku
     */
    Block_inc(std::vector<std::vector<int>> inputs = {{0,0}}, std::string name = "");

    /**
     * @brief Inkrementuje hodnotu na vstupe 0 a nastavy ju na vystup 0
     * 
     */
    void do_operation();
};

/**
 * @brief Trieda reprezentujuca blok dekrementacie
 * 
 */
class Block_dec: public Block
{

public:
    /**
     * @brief Skonstruuje blok na dekrementaciu
     * 
     * @param inputs zoznam hodnot vstupov
     * @param name meno bloku
     */
    Block_dec(std::vector<std::vector<int>> inputs = {{0,0}}, std::string name = "");

    /**
     * @brief Dekrementuje hodnotu na vstupe 0 a nastavy ju na vystup 0
     * 
     */
    void do_operation();
};

/**
 * @brief Typ reprezentujuci dostupne druhy blokov
 * 
 */
enum Block_type { sum, sub, inc, dec };
#endif // BLOCK_H
