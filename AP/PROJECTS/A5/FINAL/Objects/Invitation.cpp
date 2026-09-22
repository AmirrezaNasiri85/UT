#include "Invitation.hpp"

Invitation::Invitation(const string& sender, const string& giver, const string& type, int id)
    : id(id), 
    match_type(type), 
    sender_name(sender),
    giver_name(giver)
{};
    
Invitation* Invitation_management::make_invitations(const string& sender, const string& giver
        , const string& match_type){
    Invitation* new_invitation = new Invitation(sender, giver, match_type, invitation_id);
    invitation_id += 1;
    return new_invitation;
}

bool Invitation_management::check_type_existance(const string& match_type){
    if(match_types.find(match_type) == match_types.end()){return false;}
    return true;
}