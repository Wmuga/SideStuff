#include "b_tree.h"

template<class TypeValue>
binary_tree<TypeValue>::binary_tree() {
    head = create_Node();
}

template<class TypeValue>
binary_tree<TypeValue>::~binary_tree() {
    destroy_current(goto_head());
}

template<class TypeValue>
void binary_tree<TypeValue>::destroy_current(leaf current) {
    Node* back = current->prev;
    destroy(current);
    current=back;
    delete []back;
}

template<class TypeValue>
void binary_tree<TypeValue>::destroy(binary_tree::Node * _cur_pos) {
    if (_cur_pos->next_l!= nullptr) destroy(_cur_pos->next_l);
    if (_cur_pos->next_r!= nullptr) destroy(_cur_pos->next_r);
    delete []_cur_pos;
}

template<class TypeValue>
typename binary_tree<TypeValue>::Node *binary_tree<TypeValue>::create_Node() {
    return create_Node(TypeValue(), nullptr);
}

template<class TypeValue>
typename binary_tree<TypeValue>::Node *binary_tree<TypeValue>::create_Node(TypeValue _value, Node* _prev) {
    Node* new_Node = new Node;
    new_Node->prev= _prev;
    new_Node->value=_value;
    new_Node->next_l= nullptr;
    new_Node->next_r= nullptr;
    return new_Node;
}

//-------------Navigation-------------

template<class TypeValue>
typename binary_tree<TypeValue>::leaf binary_tree<TypeValue>::goto_head() {
    return head;
}

template<class TypeValue>
std::pair<typename binary_tree<TypeValue>::leaf,bool> binary_tree<TypeValue>::goto_left(leaf current) {
    return go_to(current,'l');
}

template<class TypeValue>
std::pair<typename binary_tree<TypeValue>::leaf,bool> binary_tree<TypeValue>::goto_right(leaf current) {
    return go_to(current,'r');
}


template<class TypeValue>
std::pair<typename binary_tree<TypeValue>::leaf,bool> binary_tree<TypeValue>::back(leaf current) {
    return go_to(current,'b');
}

template<class TypeValue>
std::pair<typename binary_tree<TypeValue>::leaf,bool> binary_tree<TypeValue>::go_to(binary_tree::leaf current,char place) {
    std::pair<leaf,bool> result = {current,false};
    switch (place)
    {
        case 'b':
            if (current->prev!= nullptr)
            {
                result.first=current->prev;
                result.second = true;
            }
            break;
        case 'l':
            if (current->next_l!= nullptr)
            {
                result.first=current->next_l;
                result.second = true;
            }
            break;
        case 'r':
            if (current->next_r!= nullptr)
            {
                result.first=current->next_r;
                result.second = true;
            }
            break;

    }
    return result;
}

template<class TypeValue>
TypeValue binary_tree<TypeValue>::get_value(leaf current) {
    return current->value;
}

//-------------Placement-------------

template<class TypeValue>
void binary_tree<TypeValue>::insert(Node** place,TypeValue _value,Node* _prev) {
    if ((*place)== nullptr) (*place)=create_Node(_value,_prev);
    else (*place)->value=_value;
}

template<class TypeValue>
typename binary_tree<TypeValue>::leaf binary_tree<TypeValue>::insert_c(binary_tree::leaf current, TypeValue _value) {
    insert(&current,_value,nullptr);
    return current;
}

template<class TypeValue>
typename binary_tree<TypeValue>::leaf binary_tree<TypeValue>::insert_l(binary_tree::leaf current, TypeValue _value) {
    insert(&(current->next_l),_value,current);
    return current->next_l;
}

template<class TypeValue>
typename binary_tree<TypeValue>::leaf binary_tree<TypeValue>::insert_r(binary_tree::leaf current, TypeValue _value) {
    insert(&(current->next_r),_value,current);
    return current->next_r;
}

template<class TypeValue>
void binary_tree<TypeValue>::change_head(binary_tree::leaf _leaf) {
    head = _leaf;
}
