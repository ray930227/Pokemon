#include "ItemBag.hpp"

ItemBag::ItemBag() {
    m_Items.resize(256);
}

void ItemBag::AddItemQuantity(size_t ID, int quantity) {
    m_Items[ID].second+=quantity;
}

void ItemBag::AddItemQuantity(const std::string &name, int quantity) {
    for(auto& i:m_Items){
        if(i.first==name){
            i.second+=quantity;
            break;
        }
    }
}

void ItemBag::SetItemQuantity(size_t ID, int quantity) {
    m_Items[ID].second=quantity;
}

void ItemBag::SetItemQuantity(const std::string &name, int quantity) {
    for(auto& i:m_Items){
        if(i.first==name){
            i.second=quantity;
            break;
        }
    }
}

int ItemBag::GetItemQuantity(size_t ID) {
    return m_Items[ID].second;
}

int ItemBag::GetItemQuantity(const std::string &name) {
    for(auto& i:m_Items){
        if(i.first==name){
            return i.second;
            break;
        }
    }
    return -1;
}