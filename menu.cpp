#include <ctime>
#include <fstream>
#include "menu.h"
#include "iostream"


using namespace std;

int cmp(int a, int b) {
    return a - b;
}

void menu() {
    while (true) {
        cout << "Where should elements of sequence be taken?" << endl << "1. Keyboard" << endl <<
             "2. Random generate" << endl << "3. File" << endl << "0. Exit" << endl;
        int choice1;
        cin >> choice1;
        if (choice1 == 0) break;
        if (choice1 < 0 || choice1 > 3) {
            cout << "ERROR" << endl;
            continue;
        }
        cout << "What should be done with sequence?" << endl << "1. Bubble sort" << endl
             << "2. Count sort" << endl << "3. Choice sort" << endl <<
             "4. Compare the time and result" << endl << "0. Exit" << endl;
        int choice2;
        cin >> choice2;
        if (choice2 == 0) break;
        if (choice2 < 0 || choice2 > 4) {
            cout << "ERROR" << endl;
            continue;
        }

        cout << "Where should result be put?" << endl << "1. Screen" << endl << "2. File (result)" << endl <<
             "3. File (step by step (please, don't chose this one, if sequence is longer then 50))"
             << endl << "0. Exit" << endl;
        int choice3;
        cin >> choice3;
        if (choice3 == 0) break;
        if (choice3 < 0 || choice3 > 3) {
            cout << "ERROR" << endl;
            continue;
        }
        Sequence<int>* seq = nullptr;
        switch (choice1) {
            case 1: {
                seq = menu1choice1();
                break;
            }
            case 2: {
                seq = menu2choice1();
                break;
            }
            case 3: {
                seq = menu3choice1();
                break;
            }
        }
        if (choice3 == 3) {
            if (seq != nullptr) {
                if (seq->GetLength() > 50) {
                    cout << "ERROR, unavailable" << endl;
                    break;
                } else { // выбор3 = 3 при длине последовательности <=50
                    switch (choice2) {
                        case 1:{ //bubble
                            ofstream fBubble("fileBubble.txt");
                            if (!fBubble){
                                cout << "error" << endl;
                                break;
                            }
                            int a;
                            for (int i = 0; i < seq->GetLength(); i++){
                                for (int k = 0; k < seq->GetLength(); k++){
                                    a = (*seq)[k];
                                    fBubble << a << " ";
                                }
                                fBubble << endl;
                                for (int j = seq->GetLength() - 1; j > i; j--){
                                    if(cmp((*seq)[j], (*seq)[j-1]) < 0){
                                        int tmp = (*seq)[j];
                                        (*seq)[j] = (*seq)[j-1];
                                        (*seq)[j-1] = tmp;
                                    }
                                }
                            }
                            for (int k = 0; k< seq->GetLength(); k++){
                                a = (*seq)[k];
                                fBubble << a << " ";
                            }
                            fBubble << endl;
                            break;
                        }
                        case 2:{//count
                            ofstream fCount("fileCount.txt");
                            if (!fCount){
                                cout << "error" << endl;
                                break;
                            }
                            int a;

                            int min, max;
                            min = (*seq)[0];
                            max = (*seq)[0];
                            int size = seq->GetLength();
                            for (int k = 1; k < size; k++){//ищу минимум и максимум
                                if (cmp(min, (*seq)[k]) > 0)
                                    min = (*seq)[k];
                                if (cmp((*seq)[k], max) > 0)
                                    max = (*seq)[k];
                            }
                            int r = max - min +1;
                            int* output_seq = new int[size];
                            int* count_array = new int[r];
                            for (int i = 0; i < r; i++){
                                count_array[i] = 0;
                            }
                            for (int i = 0; i < size; i++){
                                ++count_array[(*seq)[i] - min]; //считаем количество
                            }
                            for (int i = 1; i < r; i++) { //высчитываем позицию
                                count_array[i] = count_array[i]+count_array[i-1];
                            }
                            for (int i = 0; i < size; i++){
                                output_seq[--count_array[(*seq)[i] - min]] = (*seq)[i];
                                //для и-того члена последовательности находим cooтветствующий
                                //член массива позиций последнего номера, предварительно уменьшая его на 1
                                //(неустойчивая сортировка)
                            }
                            for (int i = 0; i < size; i++){
                                (*seq)[i] = output_seq[i];
                            }
                            for (int k = 0; k < seq->GetLength(); k++){
                                a = (*seq)[k];
                                fCount << a << " ";
                            }
                            fCount << endl;
                            break;
                        }
                        case 3:{//selection
                            ofstream fSelection("fileSelection.txt");
                            if (!fSelection){
                                cout << "error" << endl;
                                break;
                            }
                            int a;
                            for (int i = 0; i < seq->GetLength(); i++) {
                                for (int l = 0; l < seq->GetLength(); l++){
                                    a = (*seq)[l];
                                    fSelection << a << " ";
                                }
                                fSelection << endl;
                                int k = -1; //индекс с чем менять надо, +маркер нужен ли обмен
                                int tmp = (*seq)[i];
                                for (int j = i; j < seq->GetLength(); j++) {
                                    //ищу минимум
                                    if (cmp(tmp, (*seq)[j]) > 0) {
                                        tmp = (*seq)[j];
                                        k = j;
                                    }
                                }
                                if (k>0){
                                    int tmp1 = (*seq)[k];
                                    (*seq)[k] = (*seq)[i];
                                    (*seq)[i] = tmp1;
                                }
                            }
                            for (int l = 0; l < seq->GetLength(); l++){
                                a = (*seq)[l];
                                fSelection << a << " ";
                            }
                            fSelection << endl;
                            break;
                        }
                        case 4:{
                            cout << "Unavailable" <<endl;
                            break;
                        }
                    }
                }
            } else {
                cout << "ERROR" << endl;
                continue;
            }
        } else { //выбор3 != 3
            if (seq != nullptr) {
                switch (choice2) {
                    case 1: {
                        BubbleSort(seq, cmp);
                        break;
                    }
                    case 2: {
                        CountingSort(seq, cmp);
                        break;
                    }
                    case 3: {
                        SelectionSort(seq, cmp);
                        break;
                    }
                    case 4: {
                        Sequence<int>* sBubble = seq->GetSubSequence(0, seq->GetLength());
                        Sequence<int>* sSelection = seq->GetSubSequence(0, seq->GetLength());
                        Sequence<int>* sCount = seq->GetSubSequence(0, seq->GetLength());
                        int start = clock();
                        BubbleSort(sBubble, cmp);
                        int end = clock();
                        int timebubble = end - start;

                        start = clock();
                        SelectionSort(sSelection, cmp);
                        end = clock();
                        int timeselection = end - start;

                        start = clock();
                        CountingSort(sCount, cmp);
                        end = clock();
                        int timecount = end - start;
                        cout << "BubbleSort: t = " << timebubble << endl << "SelectionSort: t = " <<
                             timeselection << endl << "CountingSort: t = " << timecount << endl;
                        int k = 0;
                        for (int i = 0; i < seq->GetLength(); i++) {
                            if ((*sBubble)[i] != (*sSelection)[i] || (*sSelection)[i] != (*sCount)[i]) {
                                k++;
                            }
                        }
                        cout << "Number of error is " << k << endl;
                        switch (choice3) {
                            case 1: {
                                if (k == 0) sBubble->Print();
                                break;
                            }
                            case 2: {
                                int a;
                                ofstream fBubble("fileBubblecompare.txt");
                                if (!fBubble) {
                                    cout << "error" << endl;
                                    break;
                                }
                                for (int i = 0; i < sBubble->GetLength(); i++) {
                                    a = (*sBubble)[i];
                                    fBubble << a << " ";
                                }

                                ofstream fSelection("fileSelectioncompare.txt");
                                if (!fSelection) {
                                    cout << "error" << endl;
                                    break;
                                }
                                for (int i = 0; i < sSelection->GetLength(); i++) {
                                    a = (*sSelection)[i];
                                    fSelection << a << " ";
                                }

                                ofstream fCount("fileCountcompare.txt");
                                if (!fCount) {
                                    cout << "error" << endl;
                                    break;
                                }
                                for (int i = 0; i < sCount->GetLength(); i++) {
                                    a = (*sCount)[i];
                                    fCount << a << " ";
                                }
                                break;
                            }
                        }
                    }
                }
                switch (choice3) {
                    case 1: {
                        seq->Print();
                        break;
                    }
                    case 2: {
                        int a;
                        ofstream f("file.txt");
                        if (!f) {
                            cout << "error" << endl;
                            break;
                        }
                        for (int i = 0; i < seq->GetLength(); i++) {
                            a = (*seq)[i];
                            f << a << " ";
                        }
                        break;
                    }
                }
            } else {
                cout << "ERROR" << endl;
                continue;
            }
        }
    }
}

Sequence<int>* menu1choice1() {
    cout << "Input the length of sequence" << endl;
    int length;
    cin >> length;
    if (length < 1) {
        return nullptr;
    }
    ArraySequence<int> mass;
    int a;
    cout << "Input the integer sequence" << endl;
    for (int i = 0; i < length; i++) {
        cin >> a;
        mass.Append(a);
    }
    Sequence<int>* seq = mass.GetSubSequence(0, mass.GetLength());
    return seq;
}

Sequence<int>* menu2choice1() {
    cout << "Input the length of sequence" << endl;
    int length;
    cin >> length;
    if (length < 1){
        return nullptr;
    }
    cout << "Input the min element" << endl;
    int massmin;
    cin >> massmin;
    cout << "Input the max element" << endl;
    int massmax;
    cin >> massmax;
    if (massmin > massmax){
        return nullptr;
    }
    ArraySequence<int> mass;
    int a;
    for (int i = 0; i < length; i++){
        a = rand()%(massmax-massmin + 1) + massmin;
        mass.Append(a);
    }
    Sequence<int>* seq = mass.GetSubSequence(0, mass.GetLength());
    return seq;
}

Sequence<int>* menu3choice1() {
    ifstream f("fileInput.txt");
    if(!f){
        cout << "error";
        return nullptr;
    }
    int a;
    ArraySequence<int> mass;
    while (f >> a){
        mass.Append(a);
    }
    Sequence<int>* seq = mass.GetSubSequence(0, mass.GetLength());
    return seq;
}