#include <iostream>
#include <windows.h>
#include <ctime>
using namespace std;
class Jucator{
private:
    string numeJucator;
    int scor;
    static int incercari;
public:
    Jucator(){this->numeJucator = "Guest";this->scor = 0;}
    Jucator(string numeJucator,int scor){this->numeJucator = numeJucator ; this->scor = scor;}
    Jucator(const Jucator& obj){this->numeJucator = obj.numeJucator; this->scor = obj.scor;}
    Jucator& operator=(const Jucator& obj){this->numeJucator = obj.numeJucator; this->scor = obj.scor; return *this;}

    void setScor(int scor){this->scor = scor;}

    Jucator& operator++(){this->scor = this->scor+10; return *this;}
    Jucator& operator--(){incercari = incercari-1; return *this;}
    friend istream& operator>>(istream& in , Jucator& obj){
        cout<<"Nume jucator: "; in>>obj.numeJucator;
        cout<<"Scor: "; in>>obj.scor;
        return in;
    }
    friend ostream& operator<<(ostream& out , const Jucator& obj){
        out<<"Nume jucator: "<<obj.numeJucator<<endl;
        out<<"Scor: "<<obj.scor<<endl;
        return out;
    }

    static int getIncercari(){return incercari;}
    static void setIncercari(int incercariNoi){incercari = incercariNoi;}
};
int Jucator::incercari = 5;

class Joc{
protected:
    string numeJoc;
public:
    Joc(){this->numeJoc = "Secret";};
    Joc(string numeJoc){this->numeJoc = numeJoc;}
    Joc(const Joc& obj){this->numeJoc = obj.numeJoc;}
    Joc& operator=(const Joc& obj){if(this != &obj)this->numeJoc = obj.numeJoc;}
    friend istream& operator>>(istream& in,Joc& obj){cout<<"Cum se numeste jocul?\n";in>>obj.numeJoc;return in;}
    friend ostream& operator<<(ostream& out,const Joc& obj){out<<"Nume joc: "<<obj.numeJoc<<endl;return out;}
};


class JocZaruri:public Joc{
private:
    int zar1,zar2;
    int nrMaximZar;
public:
    JocZaruri():Joc(){this->zar1 = 1;this->zar2 = 1;this->nrMaximZar = 6;}
    JocZaruri(string numeJoc,int zar1,int zar2,int nrMaximZar):Joc(numeJoc){this->zar1 = zar1;this->zar2 = zar2;this->nrMaximZar = nrMaximZar;}
    JocZaruri(const JocZaruri& obj):Joc(obj){this->zar1 = obj.zar1;this->zar2 = obj.zar2;this->nrMaximZar = obj.nrMaximZar;}
    JocZaruri& operator=(const JocZaruri& obj){
        if(this != &obj){
            Joc::operator=(obj);
            this->zar1 = obj.zar1;
            this->zar2 = obj.zar2;
            this->nrMaximZar = obj.nrMaximZar;
        }
        return *this;
    }
    friend istream& operator>>(istream& in,JocZaruri& obj){
        in>>(Joc&)obj;
        cout<<"Cat e pe primu zar? "; in>>obj.zar1;
        cout<<"Cat e pe al2lea zar? "; in>>obj.zar2;
        cout<<"De cat e zaru? "; in>>obj.nrMaximZar;
        return in;
    }
    friend ostream& operator<<(ostream& out,const JocZaruri& obj){
        out<<(Joc&)obj;
        out<<char(218)<<char(196)<<char(196)<<char(196)<<char(191)<<" "<<char(218)<<char(196)<<char(196)<<char(196)<<char(191)<<endl;
        out<<"|";if(obj.zar1 < 10) cout<<" ";
        out<<obj.zar1<<" |"<<" ";
        out<<"|";if(obj.zar2 < 10) cout<<" ";
        out<<obj.zar2<<" |"<<endl;;
        out<<char(192)<<char(196)<<char(196)<<char(196)<<char(217)<<" "<<char(192)<<char(196)<<char(196)<<char(196)<<char(217)<<endl;

        out<<"Maximu de pe zar e "<<obj.nrMaximZar<<endl;
        return out;
    }

    void setNrMaximZar(int nrNou){this->nrMaximZar = nrNou;}
    int getSumaZaruri(){return(this->zar1+this->zar2);}

    void daCuZaru();
    void afisareZar();
};
void JocZaruri::daCuZaru(){
    this->zar1 = rand()%this->nrMaximZar +1;
    this->zar2 = rand()%this->nrMaximZar +1;
}
void JocZaruri::afisareZar(){
    cout<<char(218)<<char(196)<<char(196)<<char(196)<<char(191)<<" "<<char(218)<<char(196)<<char(196)<<char(196)<<char(191)<<endl;
    cout<<"|";if(this->zar1 < 10) cout<<" ";
    cout<<this->zar1<<" |"<<" ";
    cout<<"|";if(this->zar2 < 10) cout<<" ";
    cout<<this->zar2<<" |"<<endl;;
    cout<<char(192)<<char(196)<<char(196)<<char(196)<<char(217)<<" "<<char(192)<<char(196)<<char(196)<<char(196)<<char(217)<<endl;

}
class JocTabla:public Joc{
private:
    int dimGrid;
    char** tabla;
public:
    JocTabla();

    void setDimGrid(int dimGrid){this->dimGrid = dimGrid;}
    void rescaleTabla();
    void afisareTabla();
    ~JocTabla();
};

JocTabla::JocTabla():Joc(){
    this->dimGrid = 8;
    this->tabla = new char*[this->dimGrid+2];
    for(int i = 0 ; i < this->dimGrid+2 ; i++)
        this->tabla[i] = new char[this->dimGrid+2];

    for(int i = 0 ; i < this->dimGrid ; i++)
        for(int j = 0 ; j < this->dimGrid ; j++)
            this->tabla[i][j] = ' ';
    for(int i = 0 ; i < this->dimGrid+2 ; i++){
        this->tabla[i][this->dimGrid+1] = char(97+i);
        this->tabla[this->dimGrid][i] = '_';
        this->tabla[i][this->dimGrid] = '|';
        this->tabla[this->dimGrid+1][i] = char(48+i);
    }
    this->tabla[this->dimGrid+1][this->dimGrid+1] = char(3);
}
void JocTabla::afisareTabla(){
    for(int i = 0 ; i < this->dimGrid+2 ; i++){
        for(int j = 0 ; j < this->dimGrid+2 ; j++)
            cout<<tabla[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

void JocTabla::rescaleTabla(){
    if(this->tabla != NULL){
        for(int i = 0 ; i < this->dimGrid+2 ; i++)
            if(this->tabla[i] != NULL){
                delete[] this->tabla[i];
                this->tabla[i] = NULL;
            }
        delete[] this->tabla;
        this->tabla = NULL;
        }
    this->tabla = new char*[this->dimGrid+2];
    for(int i = 0 ; i < this->dimGrid+2 ; i++)
        this->tabla[i] = new char[this->dimGrid+2];

    for(int i = 0 ; i < this->dimGrid ; i++)
        for(int j = 0 ; j < this->dimGrid ; j++)
            this->tabla[i][j] = ' ';
    for(int i = 0 ; i < this->dimGrid+2 ; i++){
        this->tabla[i][this->dimGrid+1] = char(97+i);
        this->tabla[this->dimGrid][i] = '_';
        this->tabla[i][this->dimGrid] = '|';
        this->tabla[this->dimGrid+1][i] = char(48+i);
    }
    this->tabla[this->dimGrid+1][this->dimGrid+1] = char(3);
}

JocTabla::~JocTabla(){
    if(this->tabla != NULL){
        for(int i = 0 ; i < this->dimGrid+2 ; i++)
            if(this->tabla[i] != NULL){
                delete[] this->tabla[i];
                this->tabla[i] = NULL;
            }
        delete[] this->tabla;
        this->tabla = NULL;
        }
}

int main()
{srand((unsigned)time(NULL));
JocZaruri j1,j2;
Jucator g1,g2;
JocTabla tabla;

/*
cout<<Jucator::getIncercari();
Jucator::setIncercari(7);

cout<<--g1;
cout<<Jucator::getIncercari();

cout<<j1.getSumaZaruri()<<endl;
j1.afisareZar();
j1.daCuZaru();
cout<<j1.getSumaZaruri()<<endl;
j1.afisareZar();

tabla.afisareTabla();
tabla.setDimGrid(9);
tabla.rescaleTabla();
tabla.afisareTabla();
*/
}

///NOTES: ++jucator->creste scorul cu 10 ; --jucator->scade nr de incercari pt toti,il dai dupa o runda
///         dimGrid < 11 pls

/// !!!  exceptie la rescaleTabla();
