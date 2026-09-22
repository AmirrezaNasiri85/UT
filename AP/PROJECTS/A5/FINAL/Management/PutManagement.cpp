#include "PutManagement.hpp"


string Put_management::find_mathod(vector<string>& orders){
    bool put_pass = false;
    bool method_find = false;
    for(auto word : orders){
        if(word == "POST"){
            put_pass = true;
        }else if(put_pass){
            auto it = put_methods.find(word);
            if(it != put_methods.end()){
                method_find = true;
                return word;
            }
        }
    }if(!method_find){
        throw invalid_argument("Not Found");
    }return "";
}