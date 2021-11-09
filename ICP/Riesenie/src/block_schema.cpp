/**
 * @file block_schema.cpp
 * @author Richard Filo (xfilor00)
 * @brief Trieda pre vytvorenie modifikaciu a naslednu simulaciu blokovej schemy
 * @date 2021-05-06
 */

#include "block_schema.h"
#include <iostream>

Block_schema::Block_schema()
{
    this->blocks = {};
    this->junctions = {};
    this->event_calendar = {};
    this->code_modification = "";
}

Block_schema::~Block_schema()
{
    for(auto block: this->blocks){
        delete block.second; 
    }
}

std::string Block_schema::gen_name(std::string prefix)
{
    int num = 0;
    std::string name;
    auto search =this->blocks.find(name);
    do{
        num++;
        name = prefix + std::to_string(num);
        search = this->blocks.find(name);
    }while (search != this->blocks.end());

    return name;
}

std::string Block_schema::add_block(Block_type type)
{
    std::string name;
    Block* ptr = NULL;
    switch (type)
    {
    case sum:
        ptr = new Block_sum;
        name = gen_name("SUM block");
        this->code_modification += "\tschema.add_block(sum);\n";
        break;

    case sub:
        ptr = new Block_sub;
        name = gen_name("SUB block");
        this->code_modification += "\tschema.add_block(sub);\n";
        break;

    case inc:
        ptr = new Block_inc;
        name = gen_name("INC block");
        this->code_modification += "\tschema.add_block(inc);\n";
        break;

    case dec:
        ptr = new Block_dec;
        name = gen_name("DEC block");
        this->code_modification += "\tschema.add_block(dec);\n";
        break;
    }

    ptr->set_name(name);
    this->blocks[name] = ptr;
    return name;
}

void Block_schema::remove_junc_of_block(std::string block_name)
{
    for (auto it = this->junctions.begin(); it != this->junctions.end(); ) {
        if ((*it).first.block_name == block_name || (*it).second.block_name == block_name) {
            it = this->junctions.erase(it);
        } else {
            ++it;
        }
    }
}

void Block_schema::remove_event_of_block(std::string block_name)
{
    for (auto it = this->event_calendar.begin(); it != this->event_calendar.end(); ) {
        if ((*it).first.block_name == block_name) {
            it = this->event_calendar.erase(it);
        } else {
            ++it;
        }
    }
}

void Block_schema::remove_block(std::string block_name)
{
    this->code_modification += "\tschema.remove_block(\"" + block_name + "\");\n";
    auto search =this->blocks.find(block_name);
    if(search != this->blocks.end()){
        delete this->blocks[block_name];
        this->blocks.erase(block_name);
        this->remove_junc_of_block(block_name);
        this->remove_event_of_block(block_name);
    }
}

void Block_schema::change_name_in_junctions(std::string pre_name, std::string new_name)
{
    for (auto it = this->junctions.begin(); it != this->junctions.end(); it++) {
        if ((*it).first.block_name == pre_name) {
            (*it).first.block_name = new_name;
        }
        if ((*it).second.block_name == pre_name) {
            (*it).second.block_name = new_name;
        }
    }
}

void Block_schema::change_name_in_calendar(std::string pre_name, std::string new_name)
{
    for (auto it = this->event_calendar.begin(); it != this->event_calendar.end(); it++) {
        if ((*it).first.block_name == pre_name) {
            (*it).first.block_name = new_name;
        }
    }
}

int Block_schema::change_block_name(std::string block_name, std::string name)
{
    auto search = this->blocks.find(block_name);
    if(search != this->blocks.end()){
        auto search1 = this->blocks.find(name);
        if (name == block_name) //ak je rovnake ako predosle tak nic nemeni
            return 0;
        else if(search1 != this->blocks.end())  //ak uz existuje tak vrati chybu
            return 1;
        else{   //inac zmeni
            this->code_modification += "\tschema.change_block_name(\"" + block_name + "\", \"" + name + "\");\n";
            this->blocks[block_name]->set_name(name);
            Block* ptr = this->blocks[block_name];
            this->blocks.erase(block_name);
            this->blocks[name] = ptr;

            this->change_name_in_junctions(block_name, name);
            this->change_name_in_calendar(block_name, name);

            return 0;
        }
    }
    return -1;
}

int Block_schema::set_block_input_by_index(int value, std::string block_name, int index)
{
    auto search =this->blocks.find(block_name);
    if(search != this->blocks.end()){
        if(this->blocks[block_name]->get_input_by_index(index)[0] != 2){
            this->code_modification += "\tschema.set_block_input_by_index(" + std::to_string(value) + ", \"" + block_name + "\", " + std::to_string(index) + ");\n";
            this->blocks[block_name]->set_input_by_index({1, value}, index);
            Port port = {.block_name = block_name, .port_index = index};
            std::vector<int> input = {1, value};
            std::pair<Port, std::vector<int>> new_event = std::make_pair(port, input);
            this->event_calendar.push_back(new_event);
            return 0;
        }
        return 1;
    }
    return -1;
}

std::string Block_schema::get_block_label(std::string block_name)
{
    auto search =this->blocks.find(block_name);
    if(search != this->blocks.end()){
        return this->blocks[block_name]->get_label();
    }
    return "";
}

std::vector<std::vector<int>> Block_schema::get_block_inputs(std::string block_name)
{
    auto search =this->blocks.find(block_name);
    if(search != this->blocks.end()){
        return this->blocks[block_name]->get_inputs();
    }
    return {};
}

std::vector<std::vector<int>> Block_schema::get_block_outputs(std::string block_name)
{
    auto search =this->blocks.find(block_name);
    if(search != this->blocks.end()){
        return this->blocks[block_name]->get_outputs();
    }
    return {};
}

int Block_schema::add_junction(std::string block1, int index_output1, std::string block2, int index_input2)
{
    int exist = 0;
    for (auto junc: this->junctions ) {
        if (junc.first.block_name == block1 && junc.first.port_index == index_output1 && junc.second.block_name == block2 && junc.second.port_index == index_input2)
            exist = 1;
    }
    if (exist) {
        return 1;
    } else {
        this->code_modification += "\tschema.add_junction(\"" + block1 + "\", " + std::to_string(index_output1) + ", \"" + block2 + "\", " + std::to_string(index_input2) + ");\n";

        Port port1 = {.block_name = block1, .port_index = index_output1};
        Port port2 = {.block_name = block2, .port_index = index_input2};
        std::pair<Port, Port> new_junc = std::make_pair(port1, port2);
        this->junctions.push_back(new_junc);

        std::vector<int> output = this->blocks[block1]->get_output_by_index(index_output1);
        std::pair<Port, std::vector<int>> new_event = std::make_pair(port2, output);
        this->event_calendar.push_back(new_event);

        return 0;
    }
}

void Block_schema::remove_event_of_port(std::string block, int index_input)
{
    for (auto it = this->event_calendar.begin(); it != this->event_calendar.end(); ) {
        if ((*it).first.block_name == block && (*it).first.port_index == index_input) {
            it = this->event_calendar.erase(it);
        } else {
            ++it;
        }
    }
}

void Block_schema::remove_junction(std::string block1, int index_output1, std::string block2, int index_input2)
{
    for (auto it = junctions.begin(); it != junctions.end(); ) {
        if ((*it).first.block_name == block1 && (*it).first.port_index == index_output1 && (*it).second.block_name == block2 && (*it).second.port_index == index_input2) {
            it = junctions.erase(it);
        } else {
            ++it;
        }
    }
    this->remove_event_of_port(block2, index_input2);
    this->code_modification += "\tschema.remove_junction(\"" + block1 + "\", " + std::to_string(index_output1) + ", \"" + block2 + "\", " + std::to_string(index_input2) + ");\n";
}

void print_input_value(std::vector<int> port_value){
    std::string input_str = std::to_string(port_value[1]);
    int size = input_str.length();
    if(port_value[0])
        if(size > 15)
            std::cout<< port_value[1] << " ";
        else{
            for(int i=0; i < (15 - size); i++)
                std::cout << " ";
            std::cout<< port_value[1] << " ";
        }
    else
        std::cout<< "      Undefined " ;
}

void print_output_value(std::vector<int> port_value){
    if(port_value[0])
            std::cout<< port_value[1] << "\n";
    else
        std::cout<< "Undefined\n" ;
}

void print_block(Block* block){
    std::cout << "                 " << block->get_name() << "\n";
    if(block->get_label() == "SUM" || block->get_label() == "SUB"){
        std::cout << "                 ╔═════╗\n"; //13 medzier
        print_input_value(block->get_input_by_index(0));
        std::cout << "═╣     ║\n";
        std::cout << "                 ║ " << block->get_label() << " ╠═ ";
        print_output_value(block->get_output_by_index(0));
        print_input_value(block->get_input_by_index(1));
        std::cout << "═╣     ║\n";
        std::cout << "                 ╚═════╝\n";
    }
    else{
        std::cout << "                 ╔═════╗\n"; //13 medzier
        // std::cout << "                 ║     ║\n";
        print_input_value(block->get_input_by_index(0));
        std::cout << "═╣ " << block->get_label() << " ╠═ ";
        print_output_value(block->get_output_by_index(0));
        // std::cout << "                 ║     ║\n";
        std::cout << "                 ╚═════╝\n";
    }
}

int Block_schema::simulate()
{
    std::cout << "Set of block in this schema: {";
    for (auto block_pair: this->blocks){
        std::cout << block_pair.second->get_name() << ", ";
    }
    std::cout << "}\nSet of junctions in this schema: {";
    for (auto junc: this->junctions){
        std::cout << "(" << junc.first.block_name <<" - output" << junc.first.port_index << ", " << junc.second.block_name << " - input" << junc.second.port_index << "), ";
    }
    std::cout << "}\n\nSIMULATION STEP BY STEP:" << std::endl << std::endl;

    int step = 1;
    while(!this->event_calendar.empty()){
        std::string block_name = this->event_calendar[0].first.block_name;
        int port_index = this->event_calendar[0].first.port_index;
        int is_defined = this->event_calendar[0].second[0];
        int value = this->event_calendar[0].second[1];

        auto input_before = this->blocks[block_name]->get_input_by_index(port_index);

        this->event_calendar.erase(this->event_calendar.begin());

        if(!(input_before[0] == is_defined && input_before[1] == value)){

            std::cout << "STEP " << step << ": On block " << this->blocks[block_name]->get_label() << " named \"" << block_name << "\" is changed value\non " << port_index+1 << ". input from ";
            if(input_before[0] == 2){
                std::cout << input_before[1] << " defined by wire to ";
            }else if(input_before[0] == 1){
                std::cout << input_before[1] << " defined by value to ";
            }else{
                std::cout << "not defined to ";
            }
            if(is_defined == 2){
                std::cout << value << " defined by wire.\n";
            }else if(is_defined == 1){
                std::cout << value << " defined by value.\n";
            }else{
                std::cout << "not defined.\n";
            }

            // std::cout << "Block " << this->blocks[block_name]->get_label()<< " named \"" << this->blocks[block_name]->get_name() <<  "\" inputs before: ";
            // for(std::vector<int> input: this->blocks[block_name]->get_inputs()){
            //     if(input[0])
            //         std::cout<< input[1] << " ";
            //     else
            //         std::cout<< "Undefined " ;
            // }
            // std::cout<< std::endl;

            // std::cout << "Block " << this->blocks[block_name]->get_label()<< " named \"" << this->blocks[block_name]->get_name() <<  "\" outputs before: ";
            // for(std::vector<int> input: this->blocks[block_name]->get_outputs()){
            //     if(input[0])
            //         std::cout<< input[1] << " ";
            //     else
            //         std::cout<< "Undefined " ;
            // }
            // std::cout<< std::endl;

            print_block(this->blocks[block_name]);
            this->blocks[block_name]->set_input_by_index({is_defined,value},port_index);
            std::cout << "                   ║█║\n";
            std::cout << "                  ¥¥█¥¥\n";
            std::cout << "                   ¥¥¥\n";
            std::cout << "                    ¥\n";
            print_block(this->blocks[block_name]);
            std::cout << std::endl;

            // std::cout << "Block " << this->blocks[block_name]->get_label()<< " named \"" << this->blocks[block_name]->get_name() <<  "\" inputs after: ";
            // for(std::vector<int> input: this->blocks[block_name]->get_inputs()){
            //     if(input[0])
            //         std::cout<< input[1] << " ";
            //     else
            //         std::cout<< "Undefined " ;
            // }
            // std::cout<< std::endl;

            // std::cout << "Block " << this->blocks[block_name]->get_label()<< " named \"" << this->blocks[block_name]->get_name() <<  "\" outputs after: ";
            // for(std::vector<int> input: this->blocks[block_name]->get_outputs()){
            //     if(input[0])
            //         std::cout<< input[1] << " ";
            //     else
            //         std::cout<< "Undefined " ;
            // }
            // std::cout<< std::endl << std::endl;
            step++;
        }

        int index = 0;
        for(std::vector<int> output: this->blocks[block_name]->get_outputs()){
            for(auto junc: this->junctions){
                if(junc.first.block_name == block_name && junc.first.port_index == index){
                    std::pair<Port, std::vector<int>> new_event = std::make_pair(junc.second, this->blocks[block_name]->get_output_by_index(index));
                    this->event_calendar.push_back(new_event);
                }
            }
            index++;
        }
    }
    std::cout << "END OF SIMULATION!\nFinal state of all blocks:" << std::endl << std::endl;

    for (auto block_pair: this->blocks){
        print_block(block_pair.second);
        std::cout << std::endl;

        // std::cout << "Block " << block->get_label()<< " named \"" << block->get_name() <<  "\" inputs: ";
        // for(std::vector<int> input: block->get_inputs()){
        //     if(input[0])
        //         std::cout<< input[1] << " ";
        //     else
        //         std::cout<< "Undefined " ;
        // }
        // std::cout<< std::endl;

        // std::cout << "Block " << block->get_label()<< " named \"" << block->get_name() <<  "\" outputs: ";
        // for(std::vector<int> input: block->get_outputs()){
        //     if(input[0])
        //         std::cout<< input[1] << " ";
        //     else
        //         std::cout<< "Undefined " ;
        // }
        // std::cout<< std::endl << std::endl;
    }
    return 0;
}

std::string Block_schema::generate_sim_code()
{
    std::string code_start = "#include \"block_schema.h\"\n#include <iostream>\n\nint main(){\n\tBlock_schema schema;\n";
    
    std::string code_end = "\tschema.simulate();\n}\n";
    return code_start + this->code_modification + code_end;
}
