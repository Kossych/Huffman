#include "Haffman.cpp"



int main(){
    ifstream fin("Encode.txt");
    if(!fin.is_open()){cout<<"error"; return 0;}
    ofstream fout("Decode.txt");
    if(!fout.is_open()){cout<<"error"; return 0;}

    MapKey a;

    unsigned long long len=a.HeadReader(fin);
    a.PrintMap();
    Uzel* h=a.CreateList();

    char s,tx;
    Uzel *tmp=h;
    while(fin.get(s)){
        for(int count=0;count<8&&len>0;count++){
            tx=s&(1<<(7-count));
            if(tx){
                tmp=tmp->r;
            }
            else if(!tx){
                tmp=tmp->l;
            }
            if((tmp->l==NULL)&&(tmp->r==NULL)){
                fout.put(tmp->s);
                len--;
                tmp=h;
            }
        }
    }
    fin.close();
    fout.close();
    

}