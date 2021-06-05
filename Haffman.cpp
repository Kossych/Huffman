#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <stdbool.h>
#include <iterator>
#include <fstream>

using namespace std;

class Uzel{
    public:
    char s;
    int key;
    Uzel *l, *r;
    Uzel();
    Uzel(char , int );
    Uzel(Uzel *, Uzel *);
};

class MapKey{
    public:
    map<char, int> MK;
    int CreateMap(ifstream& );
    void PrintMap();
    Uzel* CreateList();
    unsigned long long HeadReader(ifstream& );
    static bool comp(Uzel *l,Uzel *r){
    return r->key>l->key;
}
};


Uzel::Uzel(){
    l=NULL; r=NULL;
}

Uzel::Uzel(char c, int k){
    s=c; key=k;
    l=NULL; r=NULL;
}

Uzel::Uzel(Uzel *left, Uzel *right){
    key=left->key+right->key;
    r=right; l=left;
}

int MapKey::CreateMap(ifstream& fin){
    char c;
    for(fin.get(c);!fin.eof();fin.get(c)) MK[c]++;
    int i=1<<7,k=0;
    fin.clear();
    fin.seekg(0);
    return k;
}


Uzel* MapKey::CreateList(){
    list<Uzel*> List;
    for(auto it=MK.begin();it!=MK.end();it++){
        Uzel *p=new Uzel(it->first,it->second);
        List.push_back(p);
    }
    while(List.size()!=1){
        List.sort(comp);
        Uzel *r=List.front();
        List.pop_front();
        Uzel *l=List.front();
        List.pop_front();
        Uzel *p=new Uzel(l,r);
        List.push_back(p);
    }
    return List.front();
}

void MapKey::PrintMap(){

    for(auto it = MK.begin(); it!= MK.end(); it++)
    {
        cout << it-> first << " - " << it -> second << endl;
        
    }
}

unsigned long long MapKey::HeadReader(ifstream& fin){
    int key, q;
    int len=0;
    fin.read((char*)&q,sizeof(q));
    char s;
    for(int i=0;i<q;i++){
        fin.read((char*)&s, sizeof(s)); fin.read((char*)&key,sizeof(key));
        MK[s]=key;
        len+=key;
    }

    return len;
}



vector<bool>code;

void CreateTable(Uzel *T, map<char, vector<bool>>&buff)
{
    if(T->l){
        code.push_back(0);
        CreateTable(T->l,buff);
    }
    if(T->r){
        code.push_back(1);
        CreateTable(T->r,buff);
    }
    if(((T->r) == NULL) && ((T->l) == NULL))
    {
        buff[T->s]=code;   
    }
    if(!code.empty()) code.pop_back();
}



void PrintVector(vector<bool>code){
    for(auto it=code.begin();it!=code.end();it++){
        cout<<*it;
    }
    cout<<endl;
}

void PrintTable(map<char, vector<bool>>&buff){
    for(auto it = buff.begin(); it!= buff.end(); it++)
    {
        cout << it-> first << " - " ;
        PrintVector(it->second);
    }
}


void PrintFile(const char *PATH){
    ifstream fin(PATH);
    char s;
    while(fin>>s){
        for(int i=0;i<8;i++){
            int b=(s&(1<<(7-i)))>>(7-i);
            cout<<b;
        }
    }
    fin.close();

}
