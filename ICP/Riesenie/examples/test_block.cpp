/**
 * @file test_block.cpp
 * @author Richard Filo (xfilor00)
 * @brief Test na kontrolu funkcnosti modulu blok
 * @date 2021-05-06
 */

#include "../src/block.h"
#include <iostream>

int main(){
    using namespace std;

    Block_sum sum;
    Block_sub sub;
    Block_inc inc;
    Block_dec dec;
    vector<Block*> blocks = {&sum, &sub, &inc, &dec};

    for (Block* block: blocks){
        cout<< block->get_label() << " inputs: ";
        for(std::vector<int> input: block->get_inputs()){
            if(input[0])
                cout<< input[1] << " " ;
            else
                cout<< "Undefined " ;
        }
        cout<< endl;
        cout<< block->get_label() <<  " outputs: ";
        for(std::vector<int> input: block->get_outputs()){
            if(input[0])
                cout<< input[1] << " " ;
            else
                cout<< "Undefined " ;
        }
        cout<< endl << endl;

        block->set_input_by_index({1,2},0);
        if (block->get_input_count() == 2)
        {
            block->set_input_by_index({1,4},1);
        }

        cout<< block->get_label() <<  " inputs: ";
        for(std::vector<int> input: block->get_inputs()){
            if(input[0])
                cout<< input[1] << " " ;
            else
                cout<< "Undefined " ;
        }
        cout<< endl;
        cout<< block->get_label() <<  " outputs: ";
        for(std::vector<int> input: block->get_outputs()){
            if(input[0])
                cout<< input[1] << " " ;
            else
                cout<< "Undefined " ;
        }
        cout<< endl << endl;
    }
    
}

