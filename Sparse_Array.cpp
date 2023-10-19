#include <bits/stdc++.h>
using namespace std;

struct SparseNode {
    int Data{};
    SparseNode* Next{};
    SparseNode* prev{};
    int index{};
    SparseNode(int Dataa, int indexx) :Data(Dataa), index(indexx) {}
};

class SpareArray {
private:
    SparseNode* head{};
    SparseNode* tail{};
    int Array_Length{};
    int Length = 0;

    void _link(SparseNode* one, SparseNode* two) {
        if (one)
            one->Next = two;
        if (two)
            two->prev = one;
    }
    SparseNode* Push_After(SparseNode* Cur, int Data, int Index) {
        SparseNode* NewOne = new SparseNode(Data, Index);
        SparseNode* After = Cur->Next;
        _link(Cur, NewOne);
        Length++;
        if (!After)
            tail = NewOne;
        else
            _link(NewOne, After);
        return NewOne;
    }

    SparseNode* _GetNode(int Index, bool Creat_New_Node) {
        SparseNode* cur = head;
        while (cur->Next && cur->Next->index < Index) cur = cur->Next;

        bool Is_Node = cur->Next && cur->Next->index == Index;
        if (Is_Node)
            return cur->Next;
        if (!Creat_New_Node)
            return nullptr;
        return Push_After(cur, 0, Index);
    }
public:
    SpareArray(int length) :Array_Length(length)
    {
        head = tail = new SparseNode(0, -1);
        Length++;
    }

    void SetValue(int Data, int Index) {
        _GetNode(Index, true)->Data = Data;
    }

    void print() {
        SparseNode* cur = head->Next;
        for (int i = 0; i < Array_Length; ++i) {
            if (cur && cur->index == i) {
                cout << cur->Data << " ";
                cur = cur->Next;
            }
            else
                cout << "0 ";
        }
        cout << endl;
        cur = nullptr;
        delete cur;
    }

    void print_nozeros() {
        for (SparseNode* cur = head->Next; cur; cur = cur->Next) {
            cout << cur->Data << " ";
        }
        cout << endl;
    }

    int get_value(int index) {
        SparseNode* node = _GetNode(index, false);
        if (!node)
            return 0;
        return node->Data;
    }

    void add(SpareArray& other) {
        assert(Array_Length == other.Array_Length);
        for (SparseNode* o_cur = other.head->Next; o_cur; o_cur = o_cur->Next) {
            SparseNode* MyNode = _GetNode(o_cur->index, true);
            MyNode->Data += o_cur->Data;
            MyNode = nullptr;
            delete MyNode;
        }
    }
    ~SpareArray() {
        while (head) {
            SparseNode* tmp = head;
            head = head->Next;
            tmp = tmp->Next = tmp->prev = nullptr;
            delete tmp;
        }
        delete head;
        delete tail;
    }
};

void test_index() {
    SpareArray array(10);	// length 10
    array.SetValue(50, 5);
    array.SetValue(20, 2);
    array.SetValue(70, 7);
    array.SetValue(40, 4);
    array.print();
    // 0 0 20 0 40 50 0 70 0 0
    array.print_nozeros();
    // 20 40 50 70
    cout << array.get_value(7) << "\n";	// 70
    SpareArray array2(10);
    array2.SetValue(1, 4);
    array2.SetValue(3, 7);
    array2.SetValue(4, 6);

    array.add(array2);
    array.print();
    // 0 0 20 0 41 50 4 73 0 0
}

int main() {
    test_index();
    //test_sparse();

    cout << "\n\n\nNO RTE\n";

    return 0;
}
