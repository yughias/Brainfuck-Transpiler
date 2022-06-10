#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

bool isKeyWord(char);
void loadBrainfuck(vector<char>&, const char*);
void printVec(vector<char>&);
void decode(vector<char>&, const char*);

char keywords[8] = { '>', '<', '+', '-', '.', ',', '[', ']'};
char translations[8][20] = { "++ptr;", "--ptr;", "++(*ptr);", "--(*ptr);", "putchar(*ptr);", "*ptr = getchar();", "while(*ptr){", "}"};
vector<char> bCode;

int main(){
    loadBrainfuck(bCode, "brainfuck.txt");
    printVec(bCode);
    decode(bCode, "decoded.c");
    system("gcc -o brainfuck.exe decoded.c");
}

bool isKeyWord(char c){
    for(int i = 0; i < 8; i++)
        if(c == keywords[i])
            return true;
    return false;
}

void loadBrainfuck(vector<char>& vec, const char* filename){
    fstream file;
    file.open(filename);
    char character;
    while(file >> character){
        if(isKeyWord(character))
            vec.push_back(character);
    }
    file.close();
}

void printVec(vector<char>& vec){
    for(int i = 0; i < vec.size(); i++)
        cout << vec[i];
    cout << endl;
}

void decode(vector<char>& vec, const char* filename){
    fstream out;
    out.open(filename, ios::out);
    out << "#include <stdio.h> " << endl;
    out << "char memory[512];\nchar* ptr = &memory[0];\nint main(){";
    int index;
    int tab = 0;
    for(int i = 0; i < vec.size(); i++){
        for(index = 0; index < 8; index++)
            if(vec[i] == keywords[index]){
                out << '\t' << translations[index] << endl;
                break;
            }
        if(index == 6)
            tab++;
        if(index == 7)
            tab--;
        for(int i = 0; i < tab; i++)
            out << '\t';
    }
    out << "return 0;\n}";
    out.close();
}