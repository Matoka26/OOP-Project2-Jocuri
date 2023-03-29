#include <iostream>
#include <windows.h>
//#include <stdlib.h>
#include <ctime>
#include <iomanip>
using namespace std;
class Jucator{
private:
    string numeJucator;
    int scor;
    int culoare;
public:
    Jucator(){this->numeJucator = "Guest";this->scor = 0;this->culoare = 7;}
    Jucator(string numeJucator,int scor,int culoare){this->numeJucator = numeJucator ; this->scor = scor;this->culoare = culoare;}
    Jucator(const Jucator& obj){this->numeJucator = obj.numeJucator; this->scor = obj.scor;}
    Jucator& operator=(const Jucator& obj){this->numeJucator = obj.numeJucator; this->scor = obj.scor;this->culoare = obj.culoare; return *this;}

    void setScor(int scor){this->scor = scor;}
    int getScor()const{return this->scor;}
    int getCuloare()const{return this->culoare;}
    string getNumeJucator()const{return this->numeJucator;}
    Jucator& operator++(){this->scor = this->scor+10; return *this;}
    friend istream& operator>>(istream& in , Jucator& obj){
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        cout<<"Nume jucator: "; in>>obj.numeJucator;
        cout<<"Scor: "; in>>obj.scor;
        cout<<"Culori"<<endl;
        SetConsoleTextAttribute(hConsole , 10);
        cout<<"   10.Verde"<<endl;
        SetConsoleTextAttribute(hConsole , 11);
        cout<<"   11.Cyan"<<endl;
        SetConsoleTextAttribute(hConsole , 12);
        cout<<"   12.Rosu"<<endl;
        SetConsoleTextAttribute(hConsole , 13);
        cout<<"   13.Roz"<<endl;
        SetConsoleTextAttribute(hConsole , 14);
        cout<<"   14.Galben"<<endl<<endl;
        SetConsoleTextAttribute(hConsole, 7 );
        cout<<"Culoarea aleasa: ";in>>obj.culoare;
        return in;
    }
    friend ostream& operator<<(ostream& out , const Jucator& obj){
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        out<<"Nume jucator: "<<obj.numeJucator<<endl;
        out<<"Scor: "<<obj.scor<<endl;
        out<<"Culoarea: ";
        SetConsoleTextAttribute(hConsole, obj.culoare);
        cout<<char(219)<<char(219)<<endl;
        SetConsoleTextAttribute(hConsole, 7);
        return out;
    }

};

class Joc{
protected:
    static int incercari;
    string numeJoc;
public:
    Joc(){this->numeJoc = "Secret";};
    Joc(string numeJoc){this->numeJoc = numeJoc;}
    Joc(const Joc& obj){this->numeJoc = obj.numeJoc;}
    Joc& operator=(const Joc& obj){if(this != &obj)this->numeJoc = obj.numeJoc;}
    Joc& operator--(){incercari = incercari-1; return *this;}
    friend istream& operator>>(istream& in,Joc& obj){cout<<"Cum se numeste jocul?\n";in>>obj.numeJoc;return in;}
    friend ostream& operator<<(ostream& out,const Joc& obj){out<<"Nume joc: "<<obj.numeJoc<<endl;return out;}
    static int getIncercari(){return incercari;} //const
    string getNumeJoc()const{return this->numeJoc;}
    static void setIncercari(int incercariNoi){incercari = incercariNoi;}

    void setNumeJoc(string numeJoc){this->numeJoc = numeJoc;}
};
int Joc::incercari = 5;


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
    int getSumaZaruri()const{return(this->zar1+this->zar2);}

    void daCuZaru();
    void afisareZar(const Jucator& obj);
};
void JocZaruri::daCuZaru(){
    this->zar1 = rand()%this->nrMaximZar +1;
    this->zar2 = rand()%this->nrMaximZar +1;
}
void JocZaruri::afisareZar(const Jucator& obj){
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole , obj.getCuloare());
    cout<<char(218)<<char(196)<<char(196)<<char(196)<<char(191)<<" "<<char(218)<<char(196)<<char(196)<<char(196)<<char(191)<<endl;
    cout<<"|";if(this->zar1 < 10) cout<<" ";
    cout<<this->zar1<<" |"<<" ";
    cout<<"|";if(this->zar2 < 10) cout<<" ";
    cout<<this->zar2<<" |"<<endl;
    cout<<char(192)<<char(196)<<char(196)<<char(196)<<char(217)<<" "<<char(192)<<char(196)<<char(196)<<char(196)<<char(217)<<endl;
    SetConsoleTextAttribute(hConsole , 7);

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
    void puneX();
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
                this->tabla[i] = NULL;  //?
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

void JocTabla::puneX(){
    for(int i = 0 ; i < this->dimGrid ; i++)
        for(int j = 0 ; j < this->dimGrid ; j++)
            if(rand()%2)
                this->tabla[i][j] = 'O';


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

class Meniu{ ///NUSH CE DRACU FAC AICI
private:
    Jucator jucator1 , jucator2 ;
    JocZaruri barbut;
    JocTabla tinta;
public:
    Meniu();
    void hr();
    void start();
    void alegeJoc();
    void jocBarbut();
};

Meniu::Meniu(){
    this->barbut.setNumeJoc("Barbut");
    this->tinta.setNumeJoc("Tinta");
}
void Meniu::start(){
    cout<<setw(63)<<"Player1"<<endl<<endl;
    cin>>jucator1;
    system("CLS");
    cout<<setw(63)<<"Player2"<<endl<<endl;
    cin>>jucator2;
    system("cls");
    cout<<jucator1<<jucator2;
    system("pause");
    alegeJoc();

}
void Meniu::alegeJoc(){
    system("CLS");
    int k;
    cout<<setw(63)<<"Alegeti joc"<<endl<<endl;
    cout<<"1.Barbut"<<endl;
    cout<<"2.Ceva joc cu tinte idk - nu e gata"<<endl;
    cout<<"3.Ceva cu cursa idk -nu e gata"<<endl<<endl;
    cin>>k;
    switch(k){
        case(1):{
                jocBarbut();
            break;
        }
        case(2):{
            break;
        }
        case(3):{
            break;
        }
    }

}
void Meniu::hr(){
    system("CLS");
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout<<"########################################################################################################################"<<endl;
    SetConsoleTextAttribute(hConsole, this->jucator1.getCuloare());
    cout<<setw(30)<<this->jucator1.getNumeJucator();
    SetConsoleTextAttribute(hConsole, this->jucator2.getCuloare());
    cout<<setw(60)<<this->jucator2.getNumeJucator()<<endl;
    SetConsoleTextAttribute(hConsole, 7);
    cout<<setw(30)<<this->jucator1.getScor()<<setw(60)<<this->jucator2.getScor()<<endl;
    cout<<"________________________________________________________________________________________________________________________"<<endl<<endl;

}
void Meniu::jocBarbut(){
    int k;
    system("cls");
    this->jucator1.setScor(0);
    this->jucator2.setScor(0);
    cout<<"Cate incercari sa aveti?"<<endl;
    cin>>k;
    Joc::setIncercari(k);
    system("CLS");
    cout<<setw(58)<<"~~~"<<this->barbut.getNumeJoc()<<"~~~"<<endl<<endl;
    hr();
    int ok = 0,puncte1,puncte2;
    while(Joc::getIncercari() > 0){
        cout<<"Randul lui "<<(this->jucator1).getNumeJucator()<<endl;
        cout<<"   1.Da cu zaru"<<endl;
        cout<<"   2.Renunta"<<endl;
        cin>>ok;
        if(ok == 2) break;
        if(ok == 1){
            barbut.daCuZaru();
            barbut.afisareZar(jucator1);
            puncte1 = barbut.getSumaZaruri();
        }
        cout<<"Randul lui "<<(this->jucator2).getNumeJucator()<<endl;
        cout<<"   1.Da cu zaru"<<endl;
        cout<<"   2.Renunta"<<endl;
        cin>>ok;
        if(ok == 2) break;
        if(ok == 1){
            barbut.daCuZaru();
            barbut.afisareZar(jucator2);
            puncte2 = barbut.getSumaZaruri();
        }
        if(puncte2 > puncte1) ++jucator2;
        if(puncte1 > puncte2) ++jucator1;
        system("pause");
        hr();
        --barbut;
    }
    cout<<"Runda incheiata"<<endl<<endl;
    if(ok == 1){
        if(puncte1 > puncte2) cout<<this->jucator1.getNumeJucator()<<" a castigat runda"<<endl;
        if(puncte2 > puncte1) cout<<this->jucator2.getNumeJucator()<<" a castigat runda"<<endl;
        if(puncte2 == puncte1) cout<<"Remiza"<<endl;
    }
    system("pause");
    system("cls");
    cout<<"1.Play again"<<endl;
    cout<<"2.Inapoi la jocuri"<<endl;
    cout<<"3.Out"<<endl;
    cin>>ok;
    if(ok == 1) jocBarbut();
    if(ok == 2) alegeJoc();
    if(ok == 3) return;

}
int main()
{srand((unsigned)time(NULL));
Meniu meniu;
meniu.start();

}
