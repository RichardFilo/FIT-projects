/**
 * @file block.cpp
 * @author Richard Filo (xfilor00)
 * @brief Triedy pre vytvorenie blokov a pracu s nimi
 * @date 2021-05-06
 */

#include "block.h"

Block::Block()
{
    this->name = "";
    this->label = "Block";
    this->inputs = {{0,0}};
    this->outputs = {{0,0}};
}

void Block::set_name(std::string name)
{
    this->name = name;
}

void Block::set_label(std::string label)
{
    this->label = label;
}

void Block::set_input_by_index(std::vector<int> input, int index)
{
    this->inputs[index] = input;
    this->do_operation();
}

std::string Block::get_name()
{
    return this->name;
}

std::string Block::get_label()
{
    return this->label;
}

std::vector<std::vector<int>> Block::get_inputs()
{
    return this->inputs;
}

std::vector<std::vector<int>> Block::get_outputs()
{
    return this->outputs;
}

std::vector<int> Block::get_input_by_index(int index)
{
    return this->inputs[index];
}

std::vector<int> Block::get_output_by_index(int index)
{
    return this->outputs[index];
}

int Block::get_input_count()
{
    return this->inputs.size();
}

Block_sum::Block_sum(std::vector<std::vector<int>> inputs, std::string name)
{
    this->name = name;
    this->label = "SUM";
    this->inputs = inputs;
    this->outputs = {{0,0}};
    this->do_operation();
}

Block_sub::Block_sub(std::vector<std::vector<int>> inputs, std::string name)
{
    this->name = name;
    this->label = "SUB";
    this->inputs = inputs;
    this->outputs = {{0,0}};
    this->do_operation();
}

Block_inc::Block_inc(std::vector<std::vector<int>> inputs, std::string name)
{
    this->name = name;
    this->label = "INC";
    this->inputs = inputs;
    this->outputs = {{0,0}};
    this->do_operation();
}

Block_dec::Block_dec(std::vector<std::vector<int>> inputs, std::string name)
{
    this->name = name;
    this->label = "DEC";
    this->inputs = inputs;
    this->outputs = {{0,0}};
    this->do_operation();
}

void Block_sum::do_operation()
{
    if(this->inputs[0][0] &&  this->inputs[1][0])   //ak su obe definovane
    {
        this->outputs[0][1] = this->inputs[0][1] + this->inputs[1][1];  //spocitaj
        this->outputs[0][0] = 2;    //a nastav vystup na definovany
    }
    else
    {
        this->outputs[0][0] = 0;    //a nastav vystup na nedefinovany
    }   
}

void Block_sub::do_operation()
{
    if(this->inputs[0][0] &&  this->inputs[1][0])   //ak su obe definovane
    {
        this->outputs[0][1] = this->inputs[0][1] - this->inputs[1][1];  //odcitaj
        this->outputs[0][0] = 2;    //a nastav vystup na definovany
    }
    else
    {
        this->outputs[0][0] = 0;    //a nastav vystup na nedefinovany
    }   
}

void Block_inc::do_operation()
{
    if(this->inputs[0][0])   //ak je definovany
    {
        this->outputs[0][1] = this->inputs[0][1] + 1;  //inkrementuj
        this->outputs[0][0] = 2;    //a nastav vystup na definovany
    }
    else
    {
        this->outputs[0][0] = 0;    //a nastav vystup na nedefinovany
    }   
}

void Block_dec::do_operation()
{
    if(this->inputs[0][0])   //ak je definovany
    {
        this->outputs[0][1] = this->inputs[0][1] - 1;  //dekrementuj
        this->outputs[0][0] = 2;    //a nastav vystup na definovany
    }
    else
    {
        this->outputs[0][0] = 0;    //a nastav vystup na nedefinovany
    }   
}