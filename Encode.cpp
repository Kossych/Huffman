#include "Haffman.cpp"



int main(){
    ifstream fin("Test.txt", ios::binary);
    if(!fin.is_open()){cout<<"error"; return 0;}
    ofstream fout("Encode.txt", ios::binary);
    if(!fout.is_open()){cout<<"error"; return 0;}

    MapKey a;
    map<char,vector<bool>> buff;

    a.CreateMap(fin);
    Uzel* h=a.CreateList();
    //a.PrintMap();
    CreateTable(h, buff);
    //PrintTable(buff);
    cout<<endl;

    int k=buff.size();
    fout.write((char*)&k, sizeof(k));
    for(auto it = a.MK.begin(); it!= a.MK.end(); it++)
    {
        fout.write((char*)&it-> first, sizeof(it-> first)); fout.write((char*)&it -> second,sizeof(it -> second));
    }
    
    char s,tx=0;
    int count=0;
    while(fin.get(s)){
        vector<bool> x=buff[s];
        for(int i=0;i<x.size();i++){
            tx=tx|(x[i]<<(7-count));
            count++;
            if(count==8){
                count=0;
                fout.put(tx);
                tx=0;
            }
        }
    }
    if(tx) fout.put(tx);
    fin.close();
    fout.close();

}
