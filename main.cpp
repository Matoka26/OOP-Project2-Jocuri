#include <iostream>
#include <windows.h>
#include <strings.h>
#include <ctime>
#include <conio.h>
#include <iomanip>
using namespace std;

class IOinterface{
public:
    virtual istream& citire(istream&) = 0;
    virtual ostream& afisare(ostream&) const = 0;
};


class Jucator{
private:
    string numeJucator;
    int scor;
    int culoare;
    char pion;
    pair<char,char>pozitie;
public:
    Jucator(){this->numeJucator = "Guest";this->scor = 0;this->culoare = 7;this->pion = '*';pozitie.first = ' ';pozitie.second = ' ';}
    Jucator(string numeJucator,int scor,int culoare,char pion,pair<char,char>pozitie){
        this->numeJucator = numeJucator ;
        this->scor = scor;
        this->culoare = culoare;
        this->pion = pion;
        this->pozitie.first = pozitie.first;
        this->pozitie.second = pozitie.second;
        }
    Jucator(const Jucator& obj){
        this->numeJucator = obj.numeJucator;
        this->scor = obj.scor;
        this->pion = obj.pion;
        this->pozitie.first = obj.pozitie.first;
        this->pozitie.second = obj.pozitie.second;
        }
    Jucator& operator=(const Jucator& obj){
        this->numeJucator = obj.numeJucator;
        this->scor = obj.scor;
        this->culoare = obj.culoare;
        this->pion = obj.pion;
        this->pozitie.first = obj.pozitie.first;
        this->pozitie.second = obj.pozitie.second;
        return *this;
        }
    void setPozitie(char linie,char coloana){this->pozitie.first = linie;this->pozitie.second = coloana;}
    pair<char,char> getPozitie()const{return pozitie;}
    void setScor(int scor){this->scor = scor;}
    void setPion(char pion){this->pion = pion;}
    char getPion()const{return this->pion;}
    int getScor()const{return this->scor;}
    int getCuloare()const{return this->culoare;}
    void setCuloare(int culoare){this->culoare = culoare;}
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
        cout<<"Pion ales: ";in>>obj.pion;
        return in;
    }
    friend ostream& operator<<(ostream& out , const Jucator& obj){
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        out<<"Nume jucator: "<<obj.numeJucator<<endl;
        out<<"Scor: "<<obj.scor<<endl;
        out<<"Culoarea: ";
        SetConsoleTextAttribute(hConsole, obj.culoare);
        out<<char(219)<<char(219)<<endl;
        SetConsoleTextAttribute(hConsole, 7);
        out<<"Pionul ";
        SetConsoleTextAttribute(hConsole,obj.culoare);
        out<<obj.pion<<endl;
        SetConsoleTextAttribute(hConsole, 7);
        return out;
    }

};

class Joc:public IOinterface{
protected:
    static int incercari;
    string numeJoc;
public:
    Joc(){this->numeJoc = "Secret";}
    Joc(string numeJoc){this->numeJoc = numeJoc;}
    Joc(const Joc& obj){this->numeJoc = obj.numeJoc;}
    Joc& operator=(const Joc& obj){if(this != &obj)this->numeJoc = obj.numeJoc; return *this;}
    Joc& operator--(){incercari = incercari-1; return *this;}
    virtual istream& citire(istream& in){cout<<"Cum se numeste jocul?\n";in>>this->numeJoc;return in;}
    virtual ostream& afisare(ostream& out)const{out<<"Nume joc: "<<this->numeJoc<<endl;out<<"Incercari: "<<this->incercari<<endl;return out;}
    static int getIncercari(){return incercari;}
    string getNumeJoc()const{return this->numeJoc;}
    static void setIncercari(int incercariNoi){incercari = incercariNoi;}
    friend istream& operator>>(istream& in , Joc& obj){return obj.citire(in);}
    friend ostream& operator<<(ostream& out , const Joc& obj){return obj.afisare(out);}
    void setNumeJoc(string numeJoc){this->numeJoc = numeJoc;}
    virtual ~Joc(){};
};
int Joc::incercari = 5;


class JocZaruri:virtual public Joc{
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
    virtual istream& citire(istream& in){
        this->Joc::citire(in);
        cout<<"Cat e pe primu zar? "; in>>this->zar1;
        cout<<"Cat e pe al2lea zar? "; in>>this->zar2;
        cout<<"De cat e zaru? "; in>>this->nrMaximZar;
        return in;
    }
    virtual ostream& afisare(ostream& out)const{
        this->Joc::afisare(out);
        out<<char(218)<<char(196)<<char(196)<<char(196)<<char(191)<<" "<<char(218)<<char(196)<<char(196)<<char(196)<<char(191)<<endl;
        out<<"|";if(this->zar1 < 10) cout<<" ";
        out<<this->zar1<<" |"<<" ";
        out<<"|";if(this->zar2 < 10) cout<<" ";
        out<<this->zar2<<" |\n";
        out<<char(192)<<char(196)<<char(196)<<char(196)<<char(217)<<" "<<char(192)<<char(196)<<char(196)<<char(196)<<char(217)<<endl;
        out<<"Maximu de pe zar e "<<this->nrMaximZar<<endl;
        return out;
    }

    void setNrMaximZar(int nrNou){this->nrMaximZar = nrNou;}
    virtual int getSumaZaruri()const{return(this->zar1+this->zar2);}

    virtual void daCuZaru();
    void afisare(const Jucator& obj);
    friend istream& operator>>(istream& in , JocZaruri& obj){return obj.citire(in);}
    friend ostream& operator<<(ostream& out , const JocZaruri& obj){return obj.afisare(out);}
    virtual ~JocZaruri(){};
};
void JocZaruri::daCuZaru(){
    this->zar1 = rand()%this->nrMaximZar +1;
    this->zar2 = rand()%this->nrMaximZar +1;
}
void JocZaruri::afisare(const Jucator& obj){
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole , obj.getCuloare());
    cout<<char(218)<<char(196)<<char(196)<<char(196)<<char(191)<<" "<<char(218)<<char(196)<<char(196)<<char(196)<<char(191)<<endl;
    cout<<"|";if(this->zar1 < 10) cout<<" ";
    cout<<this->zar1<<" |"<<" ";
    cout<<"|";if(this->zar2 < 10) cout<<" ";
    cout<<this->zar2<<" |\n";
    cout<<char(192)<<char(196)<<char(196)<<char(196)<<char(217)<<" "<<char(192)<<char(196)<<char(196)<<char(196)<<char(217)<<endl;
    SetConsoleTextAttribute(hConsole , 7);
}


class JocTabla:virtual public Joc{
protected:
    int dimGrid;
    char** tabla;
public:
    JocTabla();
    JocTabla(string numeJoc,int dimGrid, char** tabla);
    JocTabla(const JocTabla& obj);
    JocTabla& operator=(const JocTabla& obj);
    char** getTabla()const{return this->tabla;}
    int getDimGrid()const{return this->dimGrid;}
    void rescaleTabla(int newDim);
    void afisare(const Jucator& j1,const Jucator& j2);
    void puneO();
    void puneX(char chr1,char chr2,char cifra);
    virtual istream& citire(istream& in){
        this->Joc::citire(in);
        cout<<"Ce dimensiune are ?\n";
        in>>this->dimGrid;
        for(int i = 0 ; i < this->dimGrid ; i++)
            for(int j = 0 ; j < this->dimGrid ; j++){
                cout<<"Elementul ["<<i<<"]["<<j<<"]: ";
                in>>this->tabla[i][j];
            }
        for(int i = 0 ; i < this->dimGrid+2 ; i++){
        this->tabla[i][this->dimGrid+1] = char(97+i);
        this->tabla[this->dimGrid][i] = char(196);
        this->tabla[i][this->dimGrid] = char(179);
        this->tabla[this->dimGrid+1][i] = char(48+i);
    }
    this->tabla[this->dimGrid+1][this->dimGrid+1] = char(3);
        return in;
    }
    virtual ostream& afisare(ostream& out)const{
        this->Joc::afisare(out);
        out<<"Dimensiunea tablei: "<<this->dimGrid<<endl;
        out<<"Asa arata tabla\n";
        for(int i = 0 ; i < this->dimGrid+2 ; i++){
            for(int j = 0 ; j < this->dimGrid+2 ; j++)
                out<<this->tabla[i][j]<<' ';
            out<<'\n';
        }
        return out;
    }
    friend istream& operator>>(istream& in,JocTabla& obj){return obj.citire(in);}
    friend ostream& operator<<(ostream& out , const JocTabla& obj){return obj.afisare(out);}
    virtual ~JocTabla();
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




void JocTabla::afisare(const Jucator& j1,const Jucator& j2){
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
                this->tabla[i] = NULL;
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


class JocSmecher:public JocZaruri,public JocTabla{
private:
    pair<char,char> spawn;
    pair<char,char> finish;
public:
    JocSmecher(){this->spawn.first = ' ';this->spawn.second = ' ';this->finish.first = ' ';this->finish.second = ' ';}
    JocSmecher(string numeJoc,int zar1,int zar2,int nrMaximZar,int dimGrid, char** tabla,pair<char,char>spawn,pair<char,char>finish):Joc(numeJoc),JocZaruri(numeJoc,zar1,zar2,nrMaximZar),JocTabla(numeJoc,dimGrid,tabla){
        this->spawn.first = spawn.first;
        this->spawn.second = spawn.second;
        this->finish.first = finish.first;
        this->finish.second = finish.second;
    }
    JocSmecher(const JocSmecher& obj):Joc(obj),JocZaruri(obj),JocTabla(obj){
        this->spawn.first = obj.spawn.first;
        this->spawn.second = obj.spawn.second;
        this->finish.first = obj.finish.first;
        this->finish.second = obj.finish.second;
        }
    JocSmecher& operator=(const JocSmecher& obj){
        if(this != &obj){
            JocZaruri::operator=(obj);
            JocTabla::operator=(obj);
            this->spawn.first = obj.spawn.first;
            this->spawn.second = obj.spawn.second;
            this->finish.first = obj.finish.first;
            this->finish.second = obj.finish.second;
        }
        return *this;
    }
    istream& citire(istream& in){
        Joc::citire(in);
        cout<<"Ce dimensiune are tabla?\n";
        in>>this->dimGrid;
        for(int i = 0 ; i < this->dimGrid ; i++)
            for(int j = 0 ; j < this->dimGrid ; j++){
                cout<<"Elementul ["<<i<<"]["<<j<<"]: ";
                in>>this->tabla[i][j];
            }
        for(int i = 0 ; i < this->dimGrid+2 ; i++){
            this->tabla[i][this->dimGrid+1] = char(97+i);
            this->tabla[this->dimGrid][i] = char(196);
            this->tabla[i][this->dimGrid] = char(179);
            this->tabla[this->dimGrid+1][i] = char(48+i);
            }
        this->tabla[this->dimGrid+1][this->dimGrid+1] = char(3);

        cout<<"Cat e pe primu zar? "; in>>this->zar1;
        cout<<"Cat e pe al2lea zar? "; in>>this->zar2;
        cout<<"De cat e zaru? "; in>>this->nrMaximZar;

        cout<<"Unde e startu?";in>>this->spawn.first>>this->spawn.second;
        cout<<"Unde e finishu?";in>>this->finish.first>>this->finish.second;
        return in;
    }
    ostream& afisare(ostream& out)const{
        Joc::afisare(out);
        out<<"Dimensiunea tablei: "<<this->dimGrid<<endl;
        out<<"Asa arata tabla\n";
        out<<char(218);
        for(int i = 0 ; i < 2*this->dimGrid+2+2 ; i++) out<<char(196);
        out<<char(191)<<endl;

        for(int i = 0 ; i < this->dimGrid+2 ; i++){
            out<<char(179);
            for(int j = 0 ; j < this->dimGrid+2 ; j++)
                out<<this->tabla[i][j]<<" ";
            out<<char(179)<<endl;
        }
        out<<char(192);
        for(int i = 0 ; i < 2*this->dimGrid+2+2 ; i++) out<<char(196);
        out<<char(217)<<endl;

        out<<char(218)<<char(196)<<char(196)<<char(196)<<char(191)<<" "<<char(218)<<char(196)<<char(196)<<char(196)<<char(191)<<endl;
        out<<"|";if(this->zar1 < 10) cout<<" ";
        out<<this->zar1<<" |"<<" ";
        out<<"|";if(this->zar2 < 10) cout<<" ";
        out<<this->zar2<<" |\n";
        out<<char(192)<<char(196)<<char(196)<<char(196)<<char(217)<<" "<<char(192)<<char(196)<<char(196)<<char(196)<<char(217)<<endl;
        out<<"Maximu de pe zar e "<<this->nrMaximZar<<endl;
        out<<"Startul e la: "<<this->spawn.first<<'-'<<this->spawn.second<<endl;
        out<<"Finishul e la: "<<this->finish.first<<'-'<<this->finish.second<<endl;

        return out;
    }
    friend istream& operator>>(istream& in,JocSmecher& obj){return obj.citire(in);}
    friend ostream& operator<<(ostream& out,const JocSmecher& obj){return obj.afisare(out);}
    void setSpawn(char linie,char coloana){this->spawn.first = linie; this->spawn.second = coloana;}
    void setFinish(char linie, char coloana){this->finish.first = linie; this->finish.second = coloana;this->tabla[int(linie)-97][coloana-'0'] ='X';}
    pair<char,char> getSpawn()const{return spawn;}
    pair<char,char> getFinish()const{return finish;}

    void afisare(const Jucator& juc1,const Jucator& juc2)const{
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        int check;
        cout<<char(218);
        for(int i = 0 ; i < 2*this->dimGrid+2+2 ; i++) cout<<char(196);
        cout<<char(191)<<endl;

        for(int i = 0 ; i < this->dimGrid+2 ; i++){
            cout<<char(179);
            for(int j = 0 ; j < this->dimGrid+2 ; j++){
                check = 0;
                if((i == int(juc1.getPozitie().first)-97) && (j == juc1.getPozitie().second -'0') &&(i == int(juc2.getPozitie().first)-97 )&& (j == juc2.getPozitie().second -'0')){
                        SetConsoleTextAttribute(hConsole , juc1.getCuloare());
                        cout<<char(219);
                        SetConsoleTextAttribute(hConsole , juc2.getCuloare());
                        cout<<char(219);
                        SetConsoleTextAttribute(hConsole,7);
                        check = 1;
                }else{
                    if((i == int(juc1.getPozitie().first)-97) && (j == juc1.getPozitie().second -'0') && check == 0){
                        SetConsoleTextAttribute(hConsole , juc1.getCuloare());
                        cout<<juc1.getPion()<<" ";
                        SetConsoleTextAttribute(hConsole , 7);
                        check = 1;
                        }
                    if((i == int(juc2.getPozitie().first)-97) && (j == juc2.getPozitie().second -'0') && check == 0){
                        SetConsoleTextAttribute(hConsole , juc2.getCuloare());
                        cout<<juc2.getPion()<<" ";
                        SetConsoleTextAttribute(hConsole , 7);
                        check = 1;
                        }
                    }
                    if(check == 0)
                        cout<<this->tabla[i][j]<<" ";
                }
                cout<<char(179)<<endl;
            }
        cout<<char(192);
        for(int i = 0 ; i < 2*this->dimGrid+2+2 ; i++) cout<<char(196);
        cout<<char(217)<<endl;

    }
    void obstacole();
    virtual ~JocSmecher(){};
};

void JocSmecher::obstacole(){
    int aux;
    for(int i = 0 ; i < this->dimGrid ; i++)
        for(int j = 0 ; j < this->dimGrid ; j++){
            aux = rand()%14;
            if(aux < 3)
                this->tabla[i][j] = char(254);
        }
}


class Meniu{
private:
    Jucator jucator1 , jucator2 ;
    JocZaruri barbut;
    JocTabla tinta;
    JocSmecher monopoly;
public:
    Meniu();
    void hr();
    void start();
    void alegeJoc();
    void jocBarbut();
    void jocTinta();
    void instrBarbut();
    void instrTinta();
    void jocMonopoly();
    void hrMonopoly();
    void runda(Jucator& juc);
    void instrLabirint();
};


Meniu::Meniu(){
    this->barbut.setNumeJoc("Barbut");
    this->tinta.setNumeJoc("Tinta");
    this->monopoly.setNumeJoc("Labirint");
}
void Meniu::start(){
    cout<<setw(63)<<"Player1\n\n";
    cin>>jucator1;
    system("CLS");
    cout<<setw(63)<<"Player2\n\n";
    cin>>jucator2;
    system("cls");
    cout<<jucator1<<endl<<jucator2<<endl;
    system("pause");
    alegeJoc();

}
void Meniu::alegeJoc(){
    system("CLS");
    int k;
    cout<<setw(63)<<"Alegeti joc";
    cout<<"\n________________________________________________________________________________________________________________________\n\n";
    cout<<"1."<<this->barbut.getNumeJoc()<<endl;
    cout<<"2."<<this->tinta.getNumeJoc()<<endl;
    cout<<"3."<<this->monopoly.getNumeJoc()<<endl<<endl;
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
                jocMonopoly();
                break;
        }
    }

}
void Meniu::hr(){
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout<<"########################################################################################################################\n";
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
    cout<<"\n________________________________________________________________________________________________________________________\n\n";

}
void Meniu::hrMonopoly(){
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("CLS");
    cout<<setw(58)<<"~~~"<<this->monopoly.getNumeJoc()<<"~~~\n\n";
    cout<<"########################################################################################################################\n";
    cout<<setw(30)<<"";
        SetConsoleTextAttribute(hConsole, this->jucator1.getCuloare());
    cout<<this->jucator1.getNumeJucator();
        SetConsoleTextAttribute(hConsole,7);
    cout<<setw(60)<<"";
        SetConsoleTextAttribute(hConsole, this->jucator2.getCuloare());
    cout<<this->jucator2.getNumeJucator()<<endl;
        SetConsoleTextAttribute(hConsole, 7);
    cout<<setw(30)<<this->jucator1.getPion()<<setw(60)<<this->jucator2.getPion()<<endl;

}
void Meniu::jocBarbut(){
    int k;
    instrBarbut();
    system("cls");
    this->jucator1.setScor(0);
    this->jucator2.setScor(0);
    cout<<"Cate fete are zarul?\n";
    cin>>k;
    this->barbut.setNrMaximZar(k);
    cout<<"Cate ture sa aveti?\n";
    cin>>k;
    Joc::setIncercari(k);
    system("CLS");
    cout<<setw(58)<<"~~~"<<this->barbut.getNumeJoc()<<"~~~\n\n";
    hr();
    int ok = 0,puncte1,puncte2;
    while(Joc::getIncercari() > 0){
        cout<<"Randul lui "<<(this->jucator1).getNumeJucator()<<endl;
        cout<<"   1.Da cu zaru\n";
        cout<<"   2.Renunta\n";
        cin>>ok;
        if(ok == 2) break;
        if(ok == 1){
            barbut.daCuZaru();
            barbut.afisare(jucator1);
            puncte1 = barbut.getSumaZaruri();
        }
        cout<<"Randul lui "<<(this->jucator2).getNumeJucator()<<endl;
        cout<<"   1.Da cu zaru\n";
        cout<<"   2.Renunta\n";
        cin>>ok;
        if(ok == 2) break;
        if(ok == 1){
            barbut.daCuZaru();
            barbut.afisare(jucator2);
            puncte2 = barbut.getSumaZaruri();
        }
        if(puncte2 > puncte1) ++jucator2;
        if(puncte1 > puncte2) ++jucator1;
        system("pause");
        system("cls");
        --this->barbut;
        cout<<setw(58)<<"~~~"<<this->barbut.getNumeJoc()<<"~~~\n\n";
        hr();
    }
    cout<<"Meci incheiata\n\n";
    if(ok == 1){
        if(this->jucator1.getScor() > this->jucator2.getScor()) cout<<this->jucator1.getNumeJucator()<<" a castigat runda\n";
        if(this->jucator2.getScor() > this->jucator1.getScor()) cout<<this->jucator2.getNumeJucator()<<" a castigat runda\n";
        if(this->jucator2.getScor() == this->jucator1.getScor()) cout<<"Remiza\n";
    }
    system("pause");
    system("cls");
    cout<<"1.Play again\n";
    cout<<"2.Inapoi la jocuri\n";
    cout<<"3.Out\n";
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
    cout<<"Cate casute are latura tablei?\n";
    cin>>k;
    this->tinta.rescaleTabla(k);
    this->tinta.puneO();
    cout<<"Cate ture sa aveti?\n";
    cin>>k;
    Joc::setIncercari(k);
    int ok = 0;
    char coordX,coordY;
    system("CLS");
    cout<<setw(58)<<"~~~"<<this->tinta.getNumeJoc()<<"~~~\n\n";
    hr();
    this->tinta.afisare(this->jucator1,this->jucator2);
    while(Joc::getIncercari() > 0){
        cout<<"Randul lui "<<(this->jucator1).getNumeJucator()<<endl;
        cout<<"   1.Alege un loc\n";
        cout<<"   2.Renunta\n";
        cin>>ok;
        if(ok == 2) break;
        if(ok == 1){
            cout<<"Ce coordonate?(format:litera cifra)\n";
            cin>>coordX>>coordY;
            if(this->tinta.getTabla()[int(coordX)-97][int(coordY)-48] == 'O')
                ++this->jucator1;
            this->tinta.puneX(coordX,coordY,'1');
        }

        system("CLS");
        cout<<setw(58)<<"~~~"<<this->tinta.getNumeJoc()<<"~~~\n\n";
        hr();
        this->tinta.afisare(this->jucator1,this->jucator2);
        cout<<"Randul lui "<<(this->jucator2).getNumeJucator()<<endl;
        cout<<"   1.Alege un loc\n";
        cout<<"   2.Renunta\n";
        cin>>ok;
        if(ok == 2) break;
        if(ok == 1){
            cout<<"Ce coordonate?(format:litera cifra)\n";
            cin>>coordX>>coordY;
            if((this->tinta).getTabla()[int(coordX)-97][int(coordY)-48] == 'O')
                ++this->jucator2;
            this->tinta.puneX(coordX,coordY,'2');
        }
        system("CLS");
        cout<<setw(58)<<"~~~"<<this->tinta.getNumeJoc()<<"~~~\n\n";
        --this->tinta;
        hr();
        this->tinta.afisare(this->jucator1,this->jucator2);
    }
    cout<<"Meci incheiata"<<endl<<endl;
    if(ok == 1){
        if(this->jucator1.getScor() > this->jucator2.getScor()) cout<<this->jucator1.getNumeJucator()<<" a castigat runda\n";
        if(this->jucator1.getScor() < this->jucator2.getScor()) cout<<this->jucator2.getNumeJucator()<<" a castigat runda\n";
        if(this->jucator1.getScor() == this->jucator2.getScor()) cout<<"Remiza\n";
    }
    system("pause");
    system("cls");
    cout<<"1.Play again\n";
    cout<<"2.Inapoi la jocuri\n";
    cout<<"3.Out\n";
    cin>>ok;
    if(ok == 1) jocTinta();
    if(ok == 2) alegeJoc();
    if(ok == 3) return;
}

void Meniu::instrBarbut(){
    system("cls");
    cout<<"Instructiuni "<<this->barbut.getNumeJoc()<<endl;
    cout<<"\n________________________________________________________________________________________________________________________\n\n";

    cout<<"1 -> Jucatorul da cu zarul\n"
        <<"2 -> Meciul se incheie\n\n"
        <<"Jucatorii dau pe rand cu zarul,cine da mai mult primeste 10p, daca e remiza nu primeste nimeni nimic\n"
        <<"Prima data alegeti numarul de fete al zarului\n"
        <<"Apoi alegeti cate runde sa jucati\n\n";

    system("pause");
}
void Meniu::instrTinta(){
    system("cls");
    cout<<"Instructiuni "<<this->tinta.getNumeJoc();
    cout<<"\n________________________________________________________________________________________________________________________\n\n";
    cout<<"1 -> Jucatorul alege daca joaca\n"
        <<"        Alege coordonatele sub forma litera|_|cifra (ex: a 0 , b 2, ...)\n"
        <<"2 -> Meciul se incheie\n\n"
        <<"In spatele grid-ului sunt ascunse niste tinte. Jucatorii incearca sa ghiceasca alternativ coordonatele tintelor,iar daca o fac primesc 10p\n"
        <<"Prima data alegeti dimensiunea tablei de joc\n"
        <<"Apoi alegeti cate incercari va avea fiecare sa ghiceasca\n\n";

    system("pause");
}

void Meniu::instrLabirint(){
    system("cls");
    cout<<"Instructiuni "<<this->monopoly.getNumeJoc();
    cout<<"\n________________________________________________________________________________________________________________________\n\n";
    cout<<"Fiecare jucator controleaza din SAGETI un pion si trebuie sa ajunga la X evitand obstacolele\n"
        <<"Fiecare are dreptul la un numar de mutari egal cu suma de pe zaruri dupa ce da cu ele\n\n";
    system("pause");
}

void Meniu::runda(Jucator& juc){
    int k,mutari;
    cout<<"\nRandul lui "<<juc.getNumeJucator()<<endl;
    cout<<"   1.Da cu zaru\n   2.Renunta\n";
    cin>>k;
    if(k == 2){
        cout<<"Meci incheiat\n";
        return;
        }
    if(k == 1){
        hrMonopoly();
        this->monopoly.afisare(this->jucator1,this->jucator2);
        this->monopoly.daCuZaru();
        JocZaruri(this->monopoly).afisare(juc);
        mutari = monopoly.getSumaZaruri();
        for(int i = 0 ; i < mutari ; i++){
            int c = getch();
            int check = 0;
            if(c == 72)
                if(juc.getPozitie().first > 'a' && this->monopoly.getTabla()[int(juc.getPozitie().first)-98][int(juc.getPozitie().second)-48] != char(254)){
                    juc.setPozitie(juc.getPozitie().first-1,juc.getPozitie().second);
                    hrMonopoly();
                    this->monopoly.afisare(this->jucator1,this->jucator2);
                    JocZaruri(this->monopoly).afisare(juc);
                    cout<<"Miscari ramase:"<<this->monopoly.getSumaZaruri()-i-1<<endl;
                    check = 1;
                }
            if(c == 80)
                if(juc.getPozitie().first < char(this->monopoly.getDimGrid()+96) && this->monopoly.getTabla()[int(juc.getPozitie().first)-96][int(juc.getPozitie().second)-48] != char(254)){
                    juc.setPozitie(juc.getPozitie().first+1,juc.getPozitie().second);
                    hrMonopoly();
                    this->monopoly.afisare(this->jucator1,this->jucator2);
                    JocZaruri(this->monopoly).afisare(juc);
                    cout<<"Miscari ramase:"<<this->monopoly.getSumaZaruri()-i-1<<endl;
                    check = 1;
                }
            if(c == 75)
                if(juc.getPozitie().second > '0' && this->monopoly.getTabla()[int(juc.getPozitie().first)-97][int(juc.getPozitie().second)-49] != char(254)){
                    juc.setPozitie(juc.getPozitie().first,juc.getPozitie().second-1);
                    hrMonopoly();
                    this->monopoly.afisare(this->jucator1,this->jucator2);
                    JocZaruri(this->monopoly).afisare(juc);
                    cout<<"Miscari ramase:"<<this->monopoly.getSumaZaruri()-i-1<<endl;
                    check = 1;
                }
            if(c == 77)
                if(juc.getPozitie().second < char(this->monopoly.getDimGrid()+47) && this->monopoly.getTabla()[int(juc.getPozitie().first)-97][int(juc.getPozitie().second)-47] != char(254)){
                    juc.setPozitie(juc.getPozitie().first,juc.getPozitie().second+1);
                    hrMonopoly();
                    this->monopoly.afisare(this->jucator1,this->jucator2);
                    JocZaruri(this->monopoly).afisare(juc);
                    cout<<"Miscari ramase:"<<this->monopoly.getSumaZaruri()-i-1<<endl;
                    check = 1;
                }
            if(check == 0 ) i--;
            if(juc.getPozitie() == this->monopoly.getFinish())
                return;
        }
    }

}

void Meniu::jocMonopoly(){
    instrLabirint();
    int k;
    char q,p;
    system("cls");
    cout<<"Cat de mare sa fie tabla?\n";cin>>k;
    this->monopoly.rescaleTabla(int(k));
    hrMonopoly();
    this->monopoly.obstacole();
    this->monopoly.afisare(this->jucator1,this->jucator2);
    cout<<"Unde e startul?\n";cin>>p>>q;
    this->monopoly.setSpawn(p,q);
    cout<<"Unde e finishul?\n";cin>>p>>q;
    this->monopoly.setFinish(p,q);
    system("cls");
    this->jucator1.setPozitie(this->monopoly.getSpawn().first,this->monopoly.getSpawn().second);
    this->jucator2.setPozitie(this->monopoly.getSpawn().first,this->monopoly.getSpawn().second);
    hrMonopoly();
    this->monopoly.afisare(this->jucator1,this->jucator2);
    while(1){
        runda(this->jucator1);
        if(this->jucator1.getPozitie() == this->monopoly.getFinish()){
            cout<<jucator1.getNumeJucator()<<" a castigat!\n";
            break;
        }
        runda(this->jucator2);
        if(this->jucator2.getPozitie() == this->monopoly.getFinish()){
            cout<<jucator2.getNumeJucator()<<" a castigat!\n";
            break;
        }
    }
    system("pause");

    this->jucator1.setPozitie(' ',' ');
    this->jucator2.setPozitie(' ',' ');

    system("cls");
    int ok;
    cout<<"1.Play again\n";
    cout<<"2.Inapoi la jocuri\n";
    cout<<"3.Out\n";
    cin>>ok;
    if(ok == 1) jocMonopoly();
    if(ok == 2) alegeJoc();
    if(ok == 3) return;
}

int main()
{srand((unsigned)time(NULL));
Meniu meniu;
meniu.start();
return 0;
}

