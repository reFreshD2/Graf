#include <iostream>
#include <queue>

using namespace std;

enum status {
    notMarked, markedButNotVisited, visited
};
struct adj;
struct V {
    int name;
    V *next;
    adj *E = nullptr;
    bool marked = false;
    status visited = notMarked;
};

struct adj {
    V *name;
    adj *next;
    bool marked = false;
};

class Graf {
    V *H;

    V *searchVPointer(int name) {
        V *Head = H;
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

    ~Graf() {
        V *temp = H;
        while (temp != nullptr) {
            adj *temp2 = temp->E;
            while (temp2 != nullptr) {
                temp2 = temp2->next;
                delete temp2;
            }
            temp = temp->next;
            delete temp;
        }
    }

    int addV(int name) {
        if (!searchV(name)) {
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
        if (searchV(v1) && searchV(v2)) {
            V *temp1 = searchVPointer(v1);
            V *temp2 = searchVPointer(v2);
            if (!searchE(v1, v2)) {
                adj *newV1 = new adj;
                newV1->name = searchVPointer(v2);
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
            if (!searchE(v2, v1)) {
                adj *newV1 = new adj;
                newV1->name = searchVPointer(v1);
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
        if (searchV(v1) && searchV(v2)) {
            V *temp1 = searchVPointer(v1);
            V *temp2 = searchVPointer(v2);
            if (searchE(v1, v2) && searchE(v2, v1)) {
                if (v1 != v2) {
                    adj *adj1 = temp1->E;
                    adj *adj2 = temp2->E;
                    if (adj1->name->name == v2) {
                        temp1->E = adj1->next; // удаление с начала
                        delete adj1;
                    } else {
                        while (adj1->next->name->name != v2 && adj1->next != nullptr) {
                            adj1 = adj1->next;
                        }
                        delete adj1->next;
                        adj1->next = adj1->next->next; //удаление внутри
                    }
                    if (adj2->name->name == v1) {
                        temp2->E = adj2->next;
                        delete adj2;
                    } else {
                        while (adj2->next->name->name != v1 && adj2->next != nullptr) {
                            adj2 = adj2->next;
                        }
                        delete adj2->next;
                        adj2->next = adj2->next->next;
                    }
                } else {
                    adj *adj1 = temp1->E;
                    if (adj1->name->name == v2) {
                        temp1->E = adj1->next; // удаление с начала
                        delete adj1;
                    } else {
                        while (adj1->next->name->name != v2 && adj1->next != nullptr) {
                            adj1 = adj1->next;
                        }
                        delete adj1->next;
                        adj1->next = adj1->next->next; //удаление внутри
                    }
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
        if (searchV(v1)) {
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
                delete temp->next;
                temp->next = temp->next->next;
            }
        } else {
            return 1; // нет вершины v1 в графе
        }
        return 0;
    }

    void print() {
        V *temp = H;
        if (temp == nullptr) {
            cout << "Graph is empty" << endl;
        } else {
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
    }

    bool searchV(int name) {
        bool isIn = false;
        V *Head = H;
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

    bool searchE(int v1, int v2) {
        bool isIn = false;
        adj *Head = searchVPointer(v1)->E;
        if (Head != nullptr) {
            while (Head != nullptr) {
                if (Head->name->name == v2) {
                    isIn = true;
                    return isIn;
                }
                Head = Head->next;
            }
        }
        return isIn;
    }

    void visitV1(int p) {
        queue<int> S;
        S.push(p);
        V *pointerP = searchVPointer(p);
        pointerP->marked = true;
        while (!S.empty()) {
            int q = S.front();
            cout << q << " ";
            S.pop();
            adj *receiver = searchVPointer(q)->E;
            while (receiver != nullptr) {
                if (!receiver->name->marked) {
                    receiver->name->marked = true;
                    S.push(receiver->name->name);
                }
                receiver = receiver->next;
            }
        }
    }

    void visitV2(int p) {
        queue<int> Q;
        Q.push(p);
        V *pointerP = searchVPointer(p);
        pointerP->visited = markedButNotVisited;
        while (!Q.empty()) {
            int q = Q.front();
            cout << q << " ";
            Q.pop();
            V *pointerQ = searchVPointer(q);
            adj *w = pointerQ->E;
            while (w != nullptr) {
                w->marked = true;
                V *end = w->name;
                if (end->visited == notMarked) {
                    end->visited = markedButNotVisited;
                    Q.push(end->name);
                }
                w = w->next;
            }
            pointerQ->visited = visited;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Graf g;
    /*
    for (int i = 1; i < 10; i++) {
        g.addV(i);
        g.addV(10 - i);
    }
    for (int i = 1; i < 10; i++) {
        for (int j = 1; j < 10; j++) {
            g.addE(i, j);
        }
    }

    cout << endl;
    g.print();

    for (int i = 1; i < 10; i = i + 2)
        g.delE(i, i);

    cout << endl;
    g.print();*/
    for (int i = 1; i < 9; i++)
        g.addV(i);
    g.addE(1, 2);
    g.addE(1, 3);
    g.addE(1, 4);
    g.addE(2, 8);
    g.addE(3, 7);
    g.addE(4, 7);
    g.addE(4, 5);
    g.addE(2, 5);
    g.addE(8, 6);
    g.addE(6, 7);
    g.addE(6, 5);
    g.print();
    g.visitV1(1);
    cout << endl;
    g.visitV2(1);
    return 0;
}
