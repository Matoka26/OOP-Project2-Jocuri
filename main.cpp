#include <iostream>
#include <windows.h>
#include <strings.h>
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
    Joc& operator=(const Joc& obj){if(this != &obj)this->numeJoc = obj.numeJoc; return *this;}
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
protected:
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
protected:
    int dimGrid;
    char** tabla;
public:
    JocTabla();
    JocTabla(string numeJoc,int dimGrid, char** tabla);
    JocTabla(const JocTabla& obj);
    JocTabla& operator=(const JocTabla& obj);
    char** getTabla()const{return this->tabla;}
    void rescaleTabla(int newDim);
    void afisareTabla(const Jucator& j1,const Jucator& j2);
    void puneO();
    void puneX(char chr1,char chr2,char cifra);
    friend istream& operator>>(istream& in, JocTabla& obj);
    friend ostream& operator<<(ostream& out , const JocTabla& obj);
    ~JocTabla();
};

JocTabla::JocTabla(string numeJoc,int dimGrid , char** tabla){
    this->numeJoc = numeJoc;
    if(this->tabla != NULL ){
        for(int i = 0 ; i < this->dimGrid+2 ; i++)
            if(this->tabla[i] != NULL){
                delete[] this->tabla[i];
                this->tabla[i] = NULL;
            }
        delete[] this->tabla;
        this->tabla = NULL;
    }

    this->dimGrid = dimGrid;

    this->tabla = new char*[dimGrid+2];
    for(int i = 0 ; i < dimGrid+2 ; i++)
        this->tabla[i] = new char[dimGrid+2];

    for(int i = 0 ; i < dimGrid+2 ; i++)
        for(int j = 0 ; j < dimGrid+2 ; j++)
            this->tabla[i][j] = tabla[i][j];
}

JocTabla& JocTabla::operator=(const JocTabla& obj){
    if(this != &obj){
        Joc::operator=(obj);
        if(this->tabla != NULL ){
        for(int i = 0 ; i < this->dimGrid+2 ; i++)
            if(this->tabla[i] != NULL){
                delete[] this->tabla[i];
                this->tabla[i] = NULL;
            }
            delete[] this->tabla;
            this->tabla = NULL;
        }

        this->dimGrid = obj.dimGrid;

        this->tabla = new char*[obj.dimGrid+2];
        for(int i = 0 ; i < obj.dimGrid+2 ; i++)
            this->tabla[i] = new char[obj.dimGrid+2];

        for(int i = 0 ; i < obj.dimGrid+2 ; i++)
            for(int j = 0 ; j < obj.dimGrid+2 ; j++)
                this->tabla[i][j] = obj.tabla[i][j];


    }
    return *this;
}

JocTabla::JocTabla(const JocTabla& obj):Joc(obj){
    if(this->tabla != NULL ){
        for(int i = 0 ; i < this->dimGrid+2 ; i++)
            if(this->tabla[i] != NULL){
                delete[] this->tabla[i];
                this->tabla[i] = NULL;
            }
        delete[] this->tabla;
        this->tabla = NULL;
    }

    this->dimGrid = obj.dimGrid;

    this->tabla = new char*[obj.dimGrid+2];
    for(int i = 0 ; i < obj.dimGrid+2 ; i++)
        this->tabla[i] = new char[obj.dimGrid+2];

    for(int i = 0 ; i < obj.dimGrid+2 ; i++)
        for(int j = 0 ; j < obj.dimGrid+2 ; j++)
            this->tabla[i][j] = obj.tabla[i][j];
}

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
        this->tabla[this->dimGrid][i] = char(196);
        this->tabla[i][this->dimGrid] = char(179);
        this->tabla[this->dimGrid+1][i] = char(48+i);
    }
    this->tabla[this->dimGrid+1][this->dimGrid+1] = char(3);
}




void JocTabla::afisareTabla(const Jucator& j1,const Jucator& j2){
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i = 0 ; i < this->dimGrid+2 ; i++){
        for(int j = 0 ; j < this->dimGrid+2 ; j++){
            if(tabla[i][j] == 'O')
                if(i == this->dimGrid+1)
                    cout<<'O'<<" ";
                else
                    cout<<" "<<" ";

            if(tabla[i][j] == '1'){
                if(i != this->dimGrid+1){
                    SetConsoleTextAttribute(hConsole , j1.getCuloare());
                    cout<<'X'<<" ";
                    SetConsoleTextAttribute(hConsole , 7);
                }
                else
                    cout<<tabla[i][j]<<" ";

            }
            if(tabla[i][j] == '2'){
                if(i != this->dimGrid+1){
                    SetConsoleTextAttribute(hConsole , j2.getCuloare());
                    cout<<'X'<<" ";
                    SetConsoleTextAttribute(hConsole , 7);
                }
                else
                    cout<<tabla[i][j]<<" ";

            }
            if(strchr("O12",tabla[i][j]) == NULL)
                cout<<tabla[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}


void JocTabla::rescaleTabla(int newDim){
    if(this->tabla != NULL){
        for(int i = 0 ; i < this->dimGrid+2 ; i++)
            if(this->tabla[i] != NULL){
                delete[] this->tabla[i];
                this->tabla[i] = NULL;  //?
            }
        delete[] this->tabla;
        this->tabla = NULL;
        }

    this->tabla = new char*[newDim+2];
    for(int i = 0 ; i < newDim+2 ; i++)
        this->tabla[i] = new char[newDim+2];

    for(int i = 0 ; i < newDim ; i++)
        for(int j = 0 ; j < newDim ; j++)
            this->tabla[i][j] = ' ';
    for(int i = 0 ; i < newDim+2 ; i++){
        this->tabla[i][newDim+1] = char(97+i);
        this->tabla[newDim][i] = char(196);
        this->tabla[i][newDim] = char(179);
        this->tabla[newDim+1][i] = char(48+i);
    }
    this->tabla[newDim+1][newDim+1] = char(3);
    this->dimGrid = newDim;
}

void JocTabla::puneO(){
    for(int i = 0 ; i < this->dimGrid ; i++)
        for(int j = 0 ; j < this->dimGrid ; j++)
            if(rand()%2)
                this->tabla[i][j] = 'O';

}

void JocTabla::puneX(char chr1,char chr2,char cifra){
    this->tabla[int(chr1)-97][int(chr2)-48] = cifra;
}

istream& operator>>(istream& in , JocTabla& obj){
        in>>(Joc&)obj;
        cout<<"Ce dimensiune are ?"<<endl;
        in>>obj.dimGrid;
        for(int i = 0 ; i < obj.dimGrid ; i++)
            for(int j = 0 ; j < obj.dimGrid ; j++){
                cout<<"Elementul ["<<i<<"]["<<j<<"]: ";
                in>>obj.tabla[i][j];
            }
        for(int i = 0 ; i < obj.dimGrid+2 ; i++){
        obj.tabla[i][obj.dimGrid+1] = char(97+i);
        obj.tabla[obj.dimGrid][i] = char(196);
        obj.tabla[i][obj.dimGrid] = char(179);
        obj.tabla[obj.dimGrid+1][i] = char(48+i);
    }
    obj.tabla[obj.dimGrid+1][obj.dimGrid+1] = char(3);
        return in;
}

ostream& operator<<(ostream& out , const JocTabla& obj){
    out<<(Joc&)obj;
    out<<"Dimensiunea tablei: "<<obj.dimGrid<<endl;
    out<<"Asa arata tabla"<<endl;
    for(int i = 0 ; i < obj.dimGrid+2 ; i++){
        for(int j = 0 ; j < obj.dimGrid+2 ; j++)
            out<<obj.tabla[i][j]<<" ";
        out<<endl;
    }
    return out;
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

class Meniu{
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
    void jocTinta();
    void instrBarbut();
    void instrTinta();
};

class JocSmecher:public JocTabla,public JocZaruri{


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
    cout<<jucator1<<endl<<jucator2<<endl;
    system("pause");
    alegeJoc();

}
void Meniu::alegeJoc(){
    system("CLS");
    int k;
    cout<<setw(63)<<"Alegeti joc"<<endl<<endl;
    cout<<"1."<<this->barbut.getNumeJoc()<<endl;
    cout<<"2."<<this->tinta.getNumeJoc()<<endl;
    cout<<"3.Ceva cu cursa idk -nu e gata"<<endl<<endl;
    cin>>k;
    switch(k){
        case(1):{
                jocBarbut();
                break;
            }
        case(2):{
                jocTinta();
                break;
            }
        case(3):{
                ///ultimu joc
            break;
        }
    }

}
void Meniu::hr(){
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout<<"########################################################################################################################"<<endl;
    cout<<setw(30)<<"";
        SetConsoleTextAttribute(hConsole, this->jucator1.getCuloare());
    cout<<this->jucator1.getNumeJucator();
        SetConsoleTextAttribute(hConsole,7);
    cout<<setw(60)<<"";
        SetConsoleTextAttribute(hConsole, this->jucator2.getCuloare());
    cout<<this->jucator2.getNumeJucator()<<endl;
        SetConsoleTextAttribute(hConsole, 7);
    cout<<setw(30)<<this->jucator1.getScor()<<setw(60)<<this->jucator2.getScor()<<endl;
    cout<<"Runde ramase: ";for(int i = 0 ; i < barbut.getIncercari() ; i ++) cout<<"|";
    cout<<endl<<"________________________________________________________________________________________________________________________"<<endl<<endl;

}
void Meniu::jocBarbut(){
    int k;
    instrBarbut();
    system("cls");
    this->jucator1.setScor(0);
    this->jucator2.setScor(0);
    cout<<"Cate fete are zarul?"<<endl;
    cin>>k;
    this->barbut.setNrMaximZar(k);
    cout<<"Cate ture sa aveti?"<<endl;
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
        system("cls");
        --this->barbut;
        cout<<setw(58)<<"~~~"<<this->barbut.getNumeJoc()<<"~~~"<<endl<<endl;
        hr();
    }
    cout<<"Meci incheiata"<<endl<<endl;
    if(ok == 1){
        if(this->jucator1.getScor() > this->jucator2.getScor()) cout<<this->jucator1.getNumeJucator()<<" a castigat runda"<<endl;
        if(this->jucator2.getScor() > this->jucator1.getScor()) cout<<this->jucator2.getNumeJucator()<<" a castigat runda"<<endl;
        if(this->jucator2.getScor() == this->jucator1.getScor()) cout<<"Remiza"<<endl;
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
void Meniu::jocTinta(){
    int k;
    instrTinta();
    system("cls");
    this->jucator1.setScor(0);
    this->jucator2.setScor(0);
    cout<<"Cate casute are latura tablei?"<<endl;
    cin>>k;
    this->tinta.rescaleTabla(k);
    this->tinta.puneO();
    cout<<"Cate ture sa aveti?"<<endl;
    cin>>k;
    Joc::setIncercari(k);
    int ok = 0;
    char coordX,coordY;
    system("CLS");
    cout<<setw(58)<<"~~~"<<this->tinta.getNumeJoc()<<"~~~"<<endl<<endl;
    hr();
    this->tinta.afisareTabla(this->jucator1,this->jucator2);
    while(Joc::getIncercari() > 0){
        cout<<"Randul lui "<<(this->jucator1).getNumeJucator()<<endl;
        cout<<"   1.Alege un loc"<<endl;
        cout<<"   2.Renunta"<<endl;
        cin>>ok;
        if(ok == 2) break;
        if(ok == 1){
            cout<<"Ce coordonate?(format:litera cifra)"<<endl;
            cin>>coordX>>coordY;
            if(this->tinta.getTabla()[int(coordX)-97][int(coordY)-48] == 'O')
                ++this->jucator1;
            this->tinta.puneX(coordX,coordY,'1');
        }

        system("CLS");
        cout<<setw(58)<<"~~~"<<this->tinta.getNumeJoc()<<"~~~"<<endl<<endl;
        hr();
        this->tinta.afisareTabla(this->jucator1,this->jucator2);
        cout<<"Randul lui "<<(this->jucator2).getNumeJucator()<<endl;
        cout<<"   1.Alege un loc"<<endl;
        cout<<"   2.Renunta"<<endl;
        cin>>ok;
        if(ok == 2) break;
        if(ok == 1){
            cout<<"Ce coordonate?(format:litera cifra)"<<endl;
            cin>>coordX>>coordY;
            if((this->tinta).getTabla()[int(coordX)-97][int(coordY)-48] == 'O')
                ++this->jucator2;
            this->tinta.puneX(coordX,coordY,'2');
        }
        system("CLS");
        cout<<setw(58)<<"~~~"<<this->tinta.getNumeJoc()<<"~~~"<<endl<<endl;
        --this->tinta;
        hr();
        this->tinta.afisareTabla(this->jucator1,this->jucator2);
    }
    cout<<"Meci incheiata"<<endl<<endl;
    if(ok == 1){
        if(this->jucator1.getScor() > this->jucator2.getScor()) cout<<this->jucator1.getNumeJucator()<<" a castigat runda"<<endl;
        if(this->jucator1.getScor() < this->jucator2.getScor()) cout<<this->jucator2.getNumeJucator()<<" a castigat runda"<<endl;
        if(this->jucator1.getScor() == this->jucator2.getScor()) cout<<"Remiza"<<endl;
    }
    system("pause");
    system("cls");
    cout<<"1.Play again"<<endl;
    cout<<"2.Inapoi la jocuri"<<endl;
    cout<<"3.Out"<<endl;
    cin>>ok;
    if(ok == 1) jocTinta();
    if(ok == 2) alegeJoc();
    if(ok == 3) return;
}

void Meniu::instrBarbut(){
    system("cls");
    cout<<"Instructiuni "<<this->barbut.getNumeJoc()<<endl<<endl;

    cout<<"1 -> Jucatorul da cu zarul"<<endl
        <<"2 -> Meciul se incheie"<<endl
        <<endl
        <<"Jucatorii dau pe rand cu zarul,cine da mai mult primeste 10p, daca e remiza nu primeste nimeni nimic"<<endl
        <<"Prima data alegeti numarul de fete al zarului"<<endl
        <<"Apoi alegeti cate runde sa jucati"<<endl
        <<endl;

    system("pause");
}
void Meniu::instrTinta(){
    system("cls");
    cout<<"Instructiuni "<<this->tinta.getNumeJoc()<<endl<<endl;

    cout<<"1 -> Jucatorul alege daca joaca"<<endl
        <<"        Alege coordonatele sub forma litera|_|cifra (ex: a 0 , b 2, ...)"<<endl
        <<"2 -> Meciul se incheie"<<endl
        <<endl
        <<"In spatele grid-ului sunt ascunse niste tinte. Jucatorii incearca sa ghiceasca alternativ coordonatele tintelor,iar daca o fac primesc 10p"<<endl
        <<"Prima data alegeti dimensiunea tablei de joc"<<endl
        <<"Apoi alegeti cate incercari va avea fiecare sa ghiceasca"<<endl
        <<endl;

    system("pause");
}

int main()
{srand((unsigned)time(NULL));
Meniu meniu;
meniu.start();

}


///todo: MAI FA O CLASA CU LISTA DE JOCURI!!!
