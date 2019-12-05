#include <iostream>

using namespace std;
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

    bool isInV(V *Head, int name) {
        bool isIn = false;
        if (Head != nullptr) {
            while (Head != nullptr) {
                if (Head->name == name) {
                    isIn = true;
                    return isIn;
                }
                Head = Head->next;
            }
        }
        return isIn;
    }

    bool isInAdj(adj *Head, int name) {
        bool isIn = false;
        if (Head != nullptr) {
            while (Head != nullptr) {
                if (Head->name->name == name) {
                    isIn = true;
                    return isIn;
                }
                Head = Head->next;
            }
        }
        return isIn;
    }

    V *searchV(V *Head, int name) {
        if (Head != nullptr) {
            while (Head != nullptr) {
                if (Head->name == name) {
                    return Head;
                }
                Head = Head->next;
            }
        } else {
            return nullptr;
        }
    }

public:
    Graf() {
        H = nullptr;
    }

    int addV(int name) {
        if (!isInV(H, name)) {
            V *temp = new V;
            temp->next = nullptr;
            temp->name = name;
            if (H != nullptr) {
                V *temp2 = H;
                if (temp->name > temp2->name) {
                    while (temp2->next != nullptr && temp->name > temp2->next->name) {
                        temp2 = temp2->next;
                    }
                    if (temp2->next == nullptr && temp->name > temp2->name) {
                        temp2->next = temp;
                        return 0;
                    } else {
                        temp->next = temp2->next;
                        temp2->next = temp;
                        return 0;
                    }
                } else {
                    H = temp;
                    temp->next = temp2;
                    return 0;
                }
            } else {
                H = temp;
                return 0;
            }
        }
        return 1;
    }

    int addE(int v1, int v2) {
        if (isInV(H, v1) && isInV(H, v2)) {
            V *temp1 = searchV(H, v1);
            V *temp2 = searchV(H, v2);
            if (!isInAdj(temp1->E, v2)) {
                adj *newV1 = new adj;
                newV1->name = searchV(H, v2);
                newV1->next = nullptr;
                if (temp1->E != nullptr) {
                    adj *temp3 = temp1->E;
                    if (newV1->name->name > temp3->name->name) {
                        while (temp3->next != nullptr && newV1->name->name > temp3->next->name->name) {
                            temp3 = temp3->next;
                        }
                        if (temp3->next == nullptr && newV1->name->name > temp3->name->name) {
                            temp3->next = newV1;
                        } else {
                            newV1->next = temp3->next;
                            temp3->next = newV1;
                        }
                    } else {
                        temp1->E = newV1;
                        newV1->next = temp3;
                    }
                } else {
                    temp1->E = newV1;
                }
            } else {
                return 2; // уже есть ребро (v1,v2)
            }
            if (!isInAdj(temp2->E, v1)) {
                adj *newV1 = new adj;
                newV1->name = searchV(H, v1);
                newV1->next = nullptr;
                if (temp2->E != nullptr) {
                    adj *temp3 = temp2->E;
                    if (newV1->name->name > temp3->name->name) {
                        while (temp3->next != nullptr && newV1->name->name > temp3->next->name->name) {
                            temp3 = temp3->next;
                        }
                        if (temp3->next == nullptr && newV1->name->name > temp3->name->name) {
                            temp3->next = newV1;
                        } else {
                            newV1->next = temp3->next;
                            temp3->next = newV1;
                        }
                    } else {
                        temp2->E = newV1;
                        newV1->next = temp3;
                    }
                } else {
                    temp2->E = newV1;
                }
            } else {
                return 2; // уже есть ребро (v2,v1)
            }
        } else {
            return 1; // нет вершины v1 или v2
        }
        return 0;
    }

    int delE(int v1, int v2) {
        if (isInV(H, v1) && isInV(H, v2)) {
            V *temp1 = searchV(H, v1);
            V *temp2 = searchV(H, v2);
            if (isInAdj(temp1->E, v2) && isInAdj(temp2->E, v1)) {
                adj *adj1 = temp1->E;
                adj *adj2 = temp2->E;
                if (adj1->name->name == v2) {
                    temp1->E = adj1->next; // удаление с начала
                    delete adj1;
                } else {
                    while (adj1->next->name->name != v2 && adj1->next != nullptr) {
                        adj1 = adj1->next;
                    }
                    adj1->next = adj1->next->next; //удаление внутри
                    delete adj1->next;
                }
                if (adj2->name->name == v1) {
                    temp2->E = adj2->next;
                    delete adj2;
                } else {
                    while (adj2->next->name->name != v1 && adj2->next != nullptr) {
                        adj2 = adj2->next;
                    }
                    adj2->next = adj2->next->next;
                    delete adj2->next;
                }
            } else {
                return 2; // есть вершины, но нет ребра
            }
        } else {
            return 1; //не существует одной из вершин
        }
        return 0;
    }

    int delV(int v1) {
        if (isInV(H, v1)) {
            V *temp = H;
            while (temp != nullptr) {
                delE(v1, temp->name);
                temp = temp->next;
            }
            temp = H;
            if (temp->name == v1) {
                H = temp->next;
                delete temp;
            } else {
                while (temp->next->name != v1 && temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = temp->next->next;
                delete temp->next;
            }
        } else {
            return 1; // нет вершины v1 в графе
        }
        return 0;
    }

    void print() {
        V *temp = H;
        while (temp != nullptr) {
            cout << temp->name << " : ";
            adj *temp2 = temp->E;
            while (temp2 != nullptr) {
                cout << temp2->name->name << ' ';
                temp2 = temp2->next;
            }
            cout << endl;
            temp = temp->next;
        }
        cout << "----------------------------------" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Graf graf1;
    graf1.addV(2) == 1; // добавление в пустой
    graf1.addV(4) == 1; // добавление в конец
    graf1.addV(1) == 1;// добавление в начало
    graf1.addV(3) == 1;// добавление в середину
    if (graf1.addV(2) == 1) {
        cout << "Duplicate nodes" << endl;
    }; // добавление повтора
    if (graf1.addE(1, 5) == 1) {
        cout << "Haven't nodes v1 or v2" << endl;
    }; // нет вершины v2
    if (graf1.addE(5, 1) == 1) {
        cout << "Haven't nodes v1 or v2" << endl;
    };// нет вершины v1
    if (graf1.addE(5, 5) == 1) {
        cout << "Haven't nodes v1 or v2" << endl;
    }; // нет вершин v1 и v2
    graf1.addE(1, 2); // добавление в пустой
    graf1.addE(1, 4); // добавление в конец
    graf1.addE(1, 1); // добавление в начало
    graf1.addE(1, 3); // добавление в середину
    if (graf1.addE(1, 2) == 2) {
        cout << "The edge (v1,v2) is already in the graph" << endl;
    } // добавление повторяющегося ребра
    graf1.print();
    graf1.delE(1, 4); // удаление с начала и в середине
    if (graf1.delE(1, 5) == 1) { // удаление ребра с несуществующей вершиной
        cout << "Haven't nodes v1 or v2" << endl;
    }
    if (graf1.delE(5, 1) == 1) {
        cout << "Haven't nodes v1 or v2" << endl;
    }
    if (graf1.delE(1, 4) == 2) { // удаление не существующего ребра
        cout << "No edges (v1,v2) in the graph" << endl;
    }
    graf1.print();
    graf1.delV(3); // удаление существующей вершины
    if (graf1.delV(3) == 1) {
        cout << "Haven't node v1" << endl;
    }
    graf1.print();
    return 0;
}
