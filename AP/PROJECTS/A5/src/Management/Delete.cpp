#include "Delete.hpp"

string Delet_management::find_mathod(vector<string>& orders){
    bool delet_pass = false;
    bool method_find = false;
    for(auto word : orders){
        if(word == "POST"){
            delet_pass = true;
        }else if(delet_pass){
            auto it = delet_method.find(word);
            if(it != delet_method.end()){
                method_find = true;
                return word;
            }
        }
    }if(!method_find){
        throw invalid_argument("Not Found");
    }return "";
}