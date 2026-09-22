#include "Request.hpp"

bool sort_request_greater(const Request* a, const Request* b){
    if(a->price == b->price){
        return a->request_id < b->request_id;
    }
    return a->price > b->price;
}

bool sort_request_lesser(const Request* a, const Request* b){
    if(a->price == b->price){
        return a->request_id < b->request_id;
    }
    return a->price < b->price;
}