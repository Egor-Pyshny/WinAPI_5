#include <iostream>
#include <queue> 
#include <vector>
#include <string>
#include <fstream>
#include "Queue.h"

using namespace std;

void sortStrs(LPVOID lpParam) {
    vector<string>* strings = (vector<string>*)lpParam;
    for (int i = 0; i < strings->size() - 1; i++) {
        for (int j = 1; j < strings->size() - i; j++) {
            if ((*strings)[j - 1].compare((*strings)[j]) > 0) {
                std::string temp = (*strings)[j];
                (*strings)[j] = (*strings)[j - 1];
                (*strings)[j - 1] = temp;
            }
        }
    }
}

vector<string> mergeVec(vector<string> vec1, vector<string> vec2) {
    vector<string> res;
    int ind1{ 0 }, ind2{ 0 };
    while (ind1 < vec1.size() || ind2 < vec2.size()) {
        if (ind1 == vec1.size()) {
            res.push_back(vec2[ind2]);
            ind2++;
            continue;
        }
        if (ind2 == vec2.size()) {
            res.push_back(vec1[ind1]);
            ind1++;
            continue;
        }
        if (vec1[ind1].compare(vec2[ind2]) < 0) {
            res.push_back(vec1[ind1]);
            ind1++;
        }
        else {
            res.push_back(vec2[ind2]);
            ind2++;
        }
    }
    return res;
}

vector<string> mergeSort(vector<string>* strs, int size)
{
    int divideSise = size / 2;
    if (divideSise == 0) {
        return strs[0];
    }
    if (size % 2 != 0) {
        divideSise++;
    }

    return  mergeVec(mergeSort(strs, divideSise), mergeSort(&strs[divideSise], size - divideSise));
}

int main()
{
    int threads_count = 3;
    
    Queue queue;
    vector<string> strings;
    ThreadPool pool = ThreadPool(threads_count);
    ifstream in;
    in.open("C:\\Users\\Пользователь\\Desktop\\WindowsProjectLab5\\t1.txt");
    string str;
    if (in.is_open()) {
        while (getline(in, str)) {
            strings.push_back(str);
        }
        in.close();
    }
    else {
        return 0;
    }
    int size = strings.size();
    vector<string>* fileParts = new vector<string>[threads_count];
    vector<int> string_amount(threads_count, size / threads_count);
    int remaining = size % threads_count;
    for (int i = 0; i < remaining; ++i) {
        string_amount[i]++;
    }
    //cout << "Sort ADDRESS    " << sortStrs << endl;
    for (int i = 0; i < threads_count; i++) {
        int start = 0;
        for (int j = 0; j < i; j++) {
            start += string_amount[j];
        }
        int a=2;
        for (int j = 0; j < string_amount[i]; j++) {
            fileParts[i].push_back(strings[start + j]);
        }
        queue.addTask(sortStrs, &fileParts[i]);
        //cout << "FILe PART" << i << "ADDRESS    " << &fileParts[i] << endl;
    }
    vector<HANDLE> temp = queue.process_queue(pool);
    DWORD result = WaitForMultipleObjects(temp.size(), temp.data(), TRUE, INFINITE);
    pool.clear_pool();
    vector<string> res = mergeSort(fileParts, threads_count);
    ofstream out;
    out.open("C:\\Users\\Пользователь\\Desktop\\WindowsProjectLab5\\t2.txt", ios::out);
    if (out.is_open()) {
        for (std::string str : res) {
            out << str << std::endl;
        }
        out.close();
    }
    else {
        std::cout << "Incorrect output file" << std::endl;
        return 0;
    }
    return 0;
}
