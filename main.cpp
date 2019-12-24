#include <iostream>

using namespace std;
struct adj;
struct V {
    int name;
    V *next;
    adj *E = nullptr;
    bool marked = false;
};

struct adj {
    V *name;
    adj *next;
};

class Graf {
    V *H;

    int addToQueue(int v) {
        if (!searchV(v)) {
            V *newV = new V;
            newV->name = v;
            newV->next = nullptr;
            if (H != nullptr) {
                V *temp = H;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newV;
            } else {
                H = newV;
            }
            return 0;
        }
        return 1;
    }

    int popFromQueue() {
        if (H != nullptr) {
            int pop = H->name;
            V *temp = H->next;
            delete H;
            H = temp;
            return pop;
        }
        return -1;
    }

    int getFirst() {
        if (H != nullptr) {
            return H->name;
        }
        return -1;
    }

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

    bool check(Graf candidates, Graf no) {
        V *i = no.H;
        V *j = candidates.H;
        while (i) {
            while (j) {
                if (!this->searchE(i->name, j->name)) {
                    return false;
                }
                j = j->next;
            }
            i = i->next;
        }
        return true;
    }

    void extend(Graf compsub, Graf candidates, Graf no) {
        while (candidates.H != nullptr && check(candidates, no)) {
            int v = candidates.getFirst();
            compsub.addV(v);
            Graf new_candidates = candidates;
            Graf new_no = no;
            new_candidates.delV(v);
            adj *temp = searchVPointer(v)->E;
            while (temp != nullptr) {
                new_candidates.delV(temp->name->name);
                new_no.delV(temp->name->name);
                temp = temp->next;
            }
            if (new_candidates.H == nullptr && new_no.H == nullptr) {
                V *forPrint = compsub.H;
                while (forPrint) {
                    cout << forPrint->name << " ";
                    forPrint = forPrint->next;
                }
                cout << endl;
            } else {
                extend(compsub, new_candidates, new_no);
            }
            compsub.delV(v);
            candidates.delV(v);
            no.addV(v);
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
                        //delete adj1;
                    } else {
                        while (adj1->next->name->name != v2 && adj1->next != nullptr) {
                            adj1 = adj1->next;
                        }
                        //delete adj1->next;
                        adj1->next = adj1->next->next; //удаление внутри
                    }
                    if (adj2->name->name == v1) {
                        temp2->E = adj2->next;
                        //delete adj2;
                    } else {
                        while (adj2->next->name->name != v1 && adj2->next != nullptr) {
                            adj2 = adj2->next;
                        }
                        //delete adj2->next;
                        adj2->next = adj2->next->next;
                    }
                } else {
                    adj *adj1 = temp1->E;
                    if (adj1->name->name == v2) {
                        temp1->E = adj1->next; // удаление с начала
                        //delete adj1;
                    } else {
                        while (adj1->next->name->name != v2 && adj1->next != nullptr) {
                            adj1 = adj1->next;
                        }
                        //delete adj1->next;
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
                //delete temp;
            } else {
                while (temp->next->name != v1 && temp->next != nullptr) {
                    temp = temp->next;
                }
                //delete temp->next;
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

    int visit(int p) {
        if (searchV(p)) {
            Graf S;
            S.addToQueue(p);
            V *pp = searchVPointer(p);
            pp->marked = true;
            while (S.H != nullptr) {
                int q = S.popFromQueue();
                cout << q << " ";
                adj *E = searchVPointer(q)->E;
                while (E != nullptr) {
                    if (!E->name->marked) {
                        E->name->marked = true;
                        S.addToQueue(E->name->name);
                    }
                    E = E->next;
                }
            }
            cout << endl;
            return 0;
        }
        return 1;
    }

    void maxInd() {
        Graf compsub;
        Graf no;
        Graf candidates;
        V *temp = H;
        while (temp != nullptr) {
            candidates.addV(temp->name);
            temp = temp->next;
        }
        extend(compsub, candidates, no);
    }

    Graf &operator=(const Graf &right) {
        if (this == &right) {
            return *this;
        }
        while (H) {
            V *temp = H->next;
            delete H;
            H = temp;
        }
        V *rightDL = right.H;
        while (rightDL != nullptr) {
            addV(rightDL->name);
            rightDL = rightDL->next;
        }
        return *this;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Graf g;

    for (int i = 1; i < 10; i++) {
        g.addV(i);
        g.addV(10 - i);
    }
    for (int i = 1; i < 10; i++) {
        for (int j = 1; j < 10; j++) {
            g.addE(i, 10 - j);
            g.addE(10 - i, j);
        }
    }

    cout << endl;
    g.print();

    for (int i = 1; i < 10; i = i + 1)
        g.delE(i, 10 - i);

    cout << endl;
    g.print();

    for (int i = 1; i < 10; i++) {
        for (int j = 1; j < 10; j++) {
            g.addE(i, 10 - j);
            g.addE(10 - i, j);
        }
    }

    cout << endl;
    g.print();

    Graf g1;
    for (int i = 1; i < 9; i++)
        g1.addV(i);
    g1.addE(1, 2);
    g1.addE(1, 3);
    g1.addE(1, 4);
    g1.addE(2, 8);
    g1.addE(3, 7);
    g1.addE(4, 7);
    g1.addE(4, 5);
    g1.addE(2, 5);
    g1.addE(8, 6);
    g1.addE(6, 7);
    g1.addE(6, 5);
    g1.print();
    g1.visit(1);
    cout << endl;

    Graf g2;
    for (int i = 1; i < 9; i++)
        g2.addV(i);
    for (int i = 1; i < 9; i++)
        g2.addE(i, i + 2);
    g2.print();
    g2.visit(1);
    g2.visit(10);
    g2.maxInd();
    return 0;
}
