#include <iostream>

struct adj;
struct V {
    int name;
    V *next;
    adj *E = nullptr;
};

struct adj {
    V *name;
    adj *next;
};

class Graf {
    V *H;
public:
    Graf() {
        H = nullptr;
    }

    int addV (int name) {
        V* temp = new V;
        temp->next = nullptr;
        temp->name = name;
        if (H != nullptr){
            V* temp2 = H;
            if (temp->name > temp2->name) {
                while (temp->name >= temp2->next->name) {
                    temp2 = temp2->next;
                }
                if (temp->name == temp2->name || temp->name == temp2->next->name) {
                    return 1;
                }
                temp->next = temp2->next;
                temp2->next = temp;
            }
            else {
                H = temp;
                temp->next = temp2;
            }
        } else {
            H = temp;
        }
        return 0;
    }
};

int main() {
    return 0;
}