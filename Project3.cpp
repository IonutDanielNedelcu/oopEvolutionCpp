#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
using namespace std;


/// EROARILE MELE DEFINITE
class excIntrodVal
{
public:
    const char* text() const throw()
    {
        return "Ai introdus o valoare nepermisa. Incearca din nou: ";
    }
}exVAL;

class excIntrodOpt
{
public:
    const char* text() const throw()
    {
        return "Ai introdus o valoare care nu se afla printre optiuni. \n";
    }
    const char* incearca() const throw()
    {
        return "Incearca din nou: ";
    }
}exOPT;


/// CITIRE INT
int citestePozInt()
{
    string s;
    getline(cin, s);
    if(s=="")
        throw exVAL;
    for(int i=0; i<s.size(); i++)
        if(!(s[i]>='0' && s[i]<='9'))
            throw exVAL;
    if(stoi(s)<0)
        throw exVAL;
    return stoi(s);
}


/// CLASELE CU OBIECTE NECESARE
class Produs
{
protected:
    static int CONTOR;
    const int id;
    string nume;
    float pret;

public:
    Produs();
    Produs(string nume, float pret);
    Produs(const Produs& obj);

//    virtual istream& citire(istream& in);
//    virtual ostream& afisare(ostream& out) const;

    Produs& operator = (const Produs&);
    Produs operator + (const Produs&);
    Produs operator * (float);
    friend istream& operator>>(istream& in, Produs& obj);
    friend ostream& operator<<(ostream& out, const Produs& obj);

    void setPret(float pret);
    float getPret()const;
    string getNume()const;
    int getId() const;

    void setNume(string s);

    virtual ~Produs();
};

int Produs::CONTOR=10000;
Produs::Produs() : id(++CONTOR), nume("necompletat"), pret(0) {}
Produs::Produs(string nume, float pret) : id(++CONTOR), nume(nume), pret(pret) {}
Produs::Produs(const Produs& obj) : id(obj.id), nume(obj.nume), pret(obj.pret) {}
Produs::~Produs() {}

Produs& Produs::operator=(const Produs& obj)
{
    if(this!=&obj)
    {
        nume=obj.nume;
        pret=obj.pret;
    }
    return *this;
}

Produs Produs::operator+(const Produs& obj)
{
    nume=nume+", "+obj.nume;
    pret=pret+obj.pret;
    return *this;
}

Produs Produs::operator * (float val)
{
    this->pret=this->pret*val;
    return *this;
}

istream& operator>>(istream& in, Produs& obj)
{
    int ok=0, val;
    string sir;
    cout<<"Nume produs: ";
    while(ok==0)
    {
        try
        {
            getline(in, sir);
            if(sir=="")
                throw runtime_error("Sir vid!");
            obj.nume=sir;
            ok=1;
        }
        catch(runtime_error)
        {
            cout<<exVAL.text();
        }
    }
    ok=0;
    cout<<"Pret produs: ";
    while(ok==0)
    {
        try
        {
            obj.pret=citestePozInt();
            ok=1;
        }
        catch(excIntrodVal &ex)
        {
            cout<<ex.text();
        }
    }
    return in;
}

ostream& operator<<(ostream& out, const Produs& obj)
{
    out<<"ID produs: "<<obj.id<<endl;
    out<<"Nume produs: "<<obj.nume<<endl;
    out<<"Pret produs: "<<obj.pret<<endl;
    return out;
}

void Produs::setPret(float pret)
{
    this->pret=pret;
}

float Produs::getPret()const
{
    return pret;
}

string Produs::getNume()const
{
    return nume;
}

int Produs::getId() const
{
    return this->id;
}

void Produs::setNume(string s)
{
    nume=s;
}

class Haina: public Produs
{
protected:
    string marime, material;

public:
    Haina();
    Haina(string nume, float pret, string marime, string material);
    Haina(const Haina& obj);

    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    Haina& operator = (const Haina&);
    friend istream& operator >>(istream& in, Haina& obj);
    friend ostream& operator <<(ostream& out, const Haina& obj);

    ~Haina();
};

Haina::Haina() : Produs(), marime("necompletat"), material("necompletat") {}
Haina::Haina(string nume, float pret, string marime, string material) : Produs(nume, pret), marime(marime), material(material) {}
Haina::Haina(const Haina& obj) : Produs(obj), marime(obj.marime), material(obj.material) {}
Haina::~Haina() {}

istream& operator>>(istream& in, Haina& obj)
{
    int ok=0;
    string sir;
    in>>(Produs&)obj;
    cout<<"Marime haina: ";
    while(ok==0)
    {
        try
        {
            getline(in, sir);
            if(sir=="")
                throw runtime_error("Sir vid!");
            obj.marime=sir;
            ok=1;
        }
        catch(runtime_error)
        {
            cout<<exVAL.text();
        }
    }
    ok=0;
    cout<<"Material: ";
    while(ok==0)
    {
        try
        {
            getline(in, sir);
            if(sir=="")
                throw runtime_error("Sir vid!");
            obj.material=sir;
            ok=1;
        }
        catch(runtime_error)
        {
            cout<<exVAL.text();
        }
    }
    return in;
}

ostream& operator<<(ostream& out, const Haina& obj)
{
    out<<(Produs&)obj;
    out<<"Marime haina: "<<obj.marime<<endl;
    out<<"Material: "<<obj.material<<endl;
    return out;
}

Haina& Haina::operator=(const Haina& obj)
{
    if(this!=&obj)
    {
        Produs::operator=(obj);
        marime=obj.marime;
        material=obj.material;
    }
    return *this;
}

class Bluza: public Haina
{
protected:
    string tipManeca, tipGuler;
    int lungManeca, diamBust;

public:
    Bluza();
    Bluza(string nume, float pret, string marime, string material, string tipManeca, string tipGuler, int lungManeca, int diamBust);
    Bluza(const Bluza& obj);

    Bluza& operator = (const Bluza&);
    friend istream& operator>>(istream& in, Bluza& obj);
    friend ostream& operator<<(ostream& out, const Bluza& obj);

    ~Bluza();
};

Bluza::Bluza(): Haina(), tipManeca("necompletat"), tipGuler("necompletat"), lungManeca(0), diamBust(0) {}
Bluza::Bluza(string nume, float pret, string marime, string material, string tipManeca, string tipGuler,
             int lungManeca, int diamBust) : Haina(nume, pret, marime, material), tipManeca(tipManeca), tipGuler(tipGuler),
             lungManeca(lungManeca), diamBust(diamBust) {}
Bluza::Bluza(const Bluza& obj) : Haina(obj), tipManeca(obj.tipManeca), tipGuler(obj.tipGuler),
             lungManeca(obj.lungManeca), diamBust(obj.diamBust) {}
Bluza::~Bluza() {}

istream& operator>>(istream& in, Bluza& obj)
{
    int ok=0, val;
    string sir;
    in>>(Haina&)obj;
    cout<<"Tip maneca: ";
    while(ok==0)
    {
        try
        {
            getline(in, sir);
            if(sir=="")
                throw runtime_error("Sir vid!");
            obj.tipManeca=sir;
            ok=1;
        }
        catch(runtime_error)
        {
            cout<<exVAL.text();
        }
    }
    ok=0;
    cout<<"Tip guler: ";
    while(ok==0)
    {
        try
        {
            getline(in, sir);
            if(sir=="")
                throw runtime_error("Sir vid!");
            obj.tipGuler=sir;
            ok=1;
        }
        catch(runtime_error)
        {
            cout<<exVAL.text();
        }
    }
    ok=0;
    cout<<"Lungimea manecii: ";
    while(ok==0)
    {
        try
        {
            obj.lungManeca=citestePozInt();
            ok=1;
        }
        catch(excIntrodVal &ex)
        {
            cout<<ex.text();
        }
    }
    ok=0;
    cout<<"Diametru bust: ";
    while(ok==0)
    {
        try
        {
            obj.diamBust=citestePozInt();
            ok=1;
        }
        catch(excIntrodVal &ex)
        {
            cout<<ex.text();
        }
    }
    return in;
}

ostream& operator<<(ostream& out, const Bluza& obj)
{
    out<<(Haina&)obj;
    out<<"Tip maneca: "<<obj.tipManeca<<endl;
    out<<"Tip guler: "<<obj.tipGuler<<endl;
    out<<"Lungimea manecii: "<<obj.lungManeca<<endl;
    out<<"Diametru bust: "<<obj.diamBust<<endl;
    return out;
}

Bluza& Bluza::operator=(const Bluza& obj)
{
    if(this!=&obj)
    {
        Haina::operator=(obj);
        tipManeca=obj.tipManeca;
        tipGuler=obj.tipGuler;
        lungManeca=obj.lungManeca;
        diamBust=obj.diamBust;
    }
    return *this;
}

class Pantaloni: public Haina
{
protected:
    string fitPantalon;
    int lungPantalon, diamSold;

public:
    Pantaloni();
    Pantaloni(string nume, float pret, string marime, string material, string fitPantalon, int lungPantalon, int diamSold);
    Pantaloni(const Pantaloni& obj);

    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    Pantaloni& operator = (const Pantaloni&);
    friend istream& operator>>(istream& in, Pantaloni& obj);
    friend ostream& operator<<(ostream& out, const Pantaloni& obj);


    ~Pantaloni();
};

Pantaloni::Pantaloni(): Haina(), fitPantalon("necompletat"), lungPantalon(0), diamSold(0) {}
Pantaloni::Pantaloni(string nume, float pret, string marime, string material, string fitPantalon, int lungPantalon, int diamSold):
    Haina(nume, pret, marime, material), fitPantalon(fitPantalon), lungPantalon(lungPantalon), diamSold(diamSold) {}
Pantaloni::Pantaloni(const Pantaloni& obj) : Haina(obj), fitPantalon(obj.fitPantalon), lungPantalon(obj.lungPantalon), diamSold(obj.diamSold) {}
Pantaloni::~Pantaloni() {}

istream& operator>>(istream& in, Pantaloni& obj)
{
    int ok=0, val;
    string sir;
    in>>(Haina&)obj;
    cout<<"Fit pantaloni: ";
    while(ok==0)
    {
        try
        {
            getline(in, sir);
            if(sir=="")
                throw runtime_error("Sir vid!");
            obj.fitPantalon=sir;
            ok=1;
        }
        catch(runtime_error)
        {
            cout<<exVAL.text();
        }
    }
    ok=0;
    cout<<"Lungimea pantalonilor: ";
    while(ok==0)
    {
        try
        {
            obj.lungPantalon=citestePozInt();
            ok=1;
        }
        catch(excIntrodVal &ex)
        {
            cout<<ex.text();
        }
    }
    ok=0;
    cout<<"Diametru sold: ";
    while(ok==0)
    {
        try
        {
            obj.diamSold=citestePozInt();
            ok=1;
        }
        catch(excIntrodVal &ex)
        {
            cout<<ex.text();
        }
    }
    return in;
}

ostream& operator<<(ostream& out, const Pantaloni& obj)
{
    out<<(Haina&)obj;
    out<<"Fit pantaloni: "<<obj.fitPantalon<<endl;
    out<<"Lungimea pantalonilor: "<<obj.lungPantalon<<endl;
    out<<"Diametru sold: "<<obj.diamSold<<endl;
    return out;
}

Pantaloni& Pantaloni::operator=(const Pantaloni& obj)
{
    if(this!=&obj)
    {
        Haina::operator=(obj);
        fitPantalon=obj.fitPantalon;
        lungPantalon=obj.lungPantalon;
        diamSold=obj.diamSold;
    }
    return *this;
}

class Accesoriu: public Produs
{
protected:
    string metal, colectie;
    set<string> pietre;

public:
    Accesoriu();
    Accesoriu(string nume, float pret, string metal, string colectie, set<string> pietre);
    Accesoriu(const Accesoriu& obj);

    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    Accesoriu& operator = (const Accesoriu&);
    friend istream& operator>>(istream& in, Accesoriu& obj);
    friend ostream& operator<<(ostream& out, const Accesoriu& obj);

    ~Accesoriu();
};

Accesoriu::Accesoriu(): Produs(), metal("necompletat"), colectie("necompletat"), pietre()  {}
Accesoriu::Accesoriu(string nume, float pret, string metal, string colectie, set<string> pietre): Produs(nume, pret), metal(metal), colectie(colectie)
{
    for (set<string>::iterator i=pietre.begin(); i!=pietre.end(); ++i)
    {
        this->pietre.insert(*i);
    }
}
Accesoriu::Accesoriu(const Accesoriu& obj) : Produs(obj), metal(obj.metal), colectie(obj.colectie)
{
    for (set<string>::iterator i=obj.pietre.begin(); i!=obj.pietre.end(); ++i)
    {
        this->pietre.insert(*i);
    }
}
Accesoriu::~Accesoriu()
{
    pietre.clear();
}

istream& operator>>(istream& in, Accesoriu& obj)
{
    int ok=0;
    string sir;
    in>>(Produs&)obj;
    cout<<"Metalele de fabricare: ";
    while(ok==0)
    {
        try
        {
            getline(in, sir);
            if(sir=="")
                throw runtime_error("Sir vid!");
            obj.metal=sir;
            ok=1;
        }
        catch(runtime_error)
        {
            cout<<exVAL.text();
        }
    }
    ok=0;
    cout<<"Colectia careia apartine: ";
    while(ok==0)
    {
        try
        {
            getline(in, sir);
            if(sir=="")
                throw runtime_error("Sir vid!");
            obj.colectie=sir;
            ok=1;
        }
        catch(runtime_error)
        {
            cout<<exVAL.text();
        }
    }
    ok=0;
    cout<<"Numarul de tipuri de pietre (semi)pretioase: ";
    int nr;
    while(ok==0)
    {
        try
        {
            nr=citestePozInt();
            ok=1;
        }
        catch(excIntrodVal &ex)
        {
            cout<<ex.text();
        }
    }
    if(nr==0)
    {
        obj.pietre.clear();
    }
    else
    {
        string val;
        obj.pietre.clear();
        cout<<"Introduceti pe linii separate pietrele (semi)pretioase: "<<endl;
        for(int i=0; i<=nr; i++)
        {
            while(ok==0)
            {
                try
                {
                    getline(in, val);
                    if(val=="")
                        throw runtime_error("Sir vid!");
                    obj.pietre.insert(val);
                    ok=1;
                }
                catch(runtime_error)
                {
                    cout<<exVAL.text();
                }
            }
            ok=0;
        }
    }
    return in;
}

ostream& operator<<(ostream& out, const Accesoriu& obj)
{
    out<<(Produs&)obj;
    out<<"Metalul de fabricare: "<<obj.metal<<endl;
    if(obj.colectie=="necompletat" || obj.colectie=="")
        out<<"Accesoriul nu corespunde niciunei colectii"<<endl;
    else out<<"Colectia careia apartine: "<<obj.colectie<<endl;
    if(obj.pietre.size()==0)
        out<<"Accesoriul nu contine pietre (semi)pretioase"<<endl;
    else
    {
        out<<"Pietre pretioase: ";
        for (set<string>::iterator i=obj.pietre.begin(); i!=obj.pietre.end(); ++i)
            out<<*i<<" ";
        out<<endl;
    }
    return out;
}

Accesoriu& Accesoriu::operator=(const Accesoriu& obj)
{
    if(this!=&obj)
    {
        Produs::operator=(obj);
        metal=obj.metal;
        colectie=obj.colectie;
        pietre.clear();
        for(set<string>::iterator i=obj.pietre.begin(); i!=obj.pietre.end(); ++i)
            pietre.insert(*i);
    }
    return *this;
}

class Cercei: public Accesoriu
{
protected:
    string tipAgatatoare;
    int inaltime;

public:
    Cercei();
    Cercei(string nume, float pret, string metal, string colectie, set<string> pietre, string tipAgatatoare, int inaltime);
    Cercei(const Cercei& obj);

    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    Cercei& operator = (const Cercei&);
    friend istream& operator>>(istream& in, Cercei& obj);
    friend ostream& operator<<(ostream& out, const Cercei& obj);

    ~Cercei();
};

Cercei::Cercei(): Accesoriu(), tipAgatatoare("necompletat"), inaltime(0) {}
Cercei::Cercei(string nume, float pret, string metal, string colectie, set<string> pietre, string tipAgatatoare, int inaltime):
    Accesoriu(nume, pret, metal, colectie, pietre), tipAgatatoare(tipAgatatoare), inaltime(inaltime) {}
Cercei::Cercei(const Cercei& obj): Accesoriu(obj), tipAgatatoare(obj.tipAgatatoare), inaltime(obj.inaltime) {}
Cercei::~Cercei() {}

istream& operator>>(istream& in, Cercei& obj)
{
    int ok=0, val;
    string sir;
    in>>(Accesoriu&)obj;
    cout<<"Tipul de agatatoare: ";
    while(ok==0)
    {
        try
        {
            getline(in, sir);
            if(sir=="")
                throw runtime_error("Sir vid!");
            obj.tipAgatatoare=sir;
            ok=1;
        }
        catch(runtime_error)
        {
            cout<<exVAL.text();
        }
    }
    ok=0;
    cout<<"Inaltimea cerceilor: ";
    while(ok==0)
    {
        try
        {
            obj.inaltime=citestePozInt();
            ok=1;
        }
        catch(excIntrodVal &ex)
        {
            cout<<ex.text();
        }
    }
    return in;
}

ostream& operator<<(ostream& out, const Cercei& obj)
{
    out<<(Accesoriu&)obj;
    out<<"Tipul de agatatoare: "<<obj.tipAgatatoare<<endl;
    out<<"Inaltimea cerceilor: "<<obj.inaltime<<endl;
    return out;
}

Cercei& Cercei::operator=(const Cercei& obj)
{
    if(this!=&obj)
    {
        Accesoriu::operator=(obj);
        tipAgatatoare=obj.tipAgatatoare;
        inaltime=obj.inaltime;
    }
    return *this;
}

class Lant: public Accesoriu
{
protected:
    int diametru;
    bool pandantiv;

public:
    Lant();
    Lant(string nume, float pret, string metal, string colectie, set<string> pietre, int diametru, bool pandantiv);
    Lant(const Lant& obj);

    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    Lant& operator = (const Lant&);
    friend istream& operator>>(istream& in, Lant& obj);
    friend ostream& operator<<(ostream& out, const Lant& obj);

    ~Lant();
};

Lant::Lant(): Accesoriu(), diametru(0), pandantiv(false) {}
Lant::Lant(string nume, float pret, string metal, string colectie, set<string> pietre, int diametru, bool pandantiv):
     Accesoriu(nume, pret, metal, colectie, pietre), diametru(diametru), pandantiv(pandantiv) {}
Lant::Lant(const Lant& obj): Accesoriu(obj), diametru(obj.diametru), pandantiv(obj.pandantiv) {}
Lant::~Lant() {}

istream& operator>>(istream& in, Lant& obj)
{
    int ok=0, val;
    string sir;
    in>>(Accesoriu&)obj;
    cout<<"Diametru lant: ";
    while(ok==0)
    {
        try
        {
            obj.diametru=citestePozInt();
            ok=1;
        }
        catch(excIntrodVal &ex)
        {
            cout<<ex.text();
        }
    }
    ok=0;
    cout<<"Lantul are pandantiv? (1.NU, 2.DA) Introduceti cifra corespunzatoare: ";
    while(ok==0)
    {
        try
        {
            in>>val;
            if(val!=1 && val!=2)
                throw exOPT;
            if(val==1)
                obj.pandantiv=false;
            else obj.pandantiv=true;
            ok=1;
        }
        catch(excIntrodOpt &ex)
        {
            cout<<ex.text();
            cout<<"Optiunile valide sunt 1.NU si 2.DA. "<<ex.incearca();
        }
    }
    in.get();
    return in;
}

ostream& operator<<(ostream& out, const Lant& obj)
{
    out<<(Accesoriu&)obj;
    out<<"Diametru lant: "<<obj.diametru<<endl;
    if(obj.pandantiv==true)
        out<<"Lantul are pandantiv"<<endl;
    else out<<"Lantul nu are pandantiv"<<endl;
    return out;
}

Lant& Lant::operator=(const Lant& obj)
{
    if(this!=&obj)
    {
        Accesoriu::operator=(obj);
        diametru=obj.diametru;
        pandantiv=obj.pandantiv;
    }
    return *this;
}


/// CLASA TEMPLATE
template <class T, int n>
class Colectie
{
protected:
    int nrElem, counter;
    vector<T*> elem;
    string numeColectie;

public:
    Colectie();
    Colectie(int nrElem, vector<T*> elem, string numeColectie, int counter);
    Colectie(string numeColectie);
    Colectie(const Colectie<T,n>& obj);


    int getNrElem() const;
    string getNume() const;

    void addElem(T* obj);

    void setNume(string numeColectie);

    Colectie<T,n>& operator=(const Colectie<T,n>& obj);
    T& operator[](int i);

    template <class U, int m>
    friend istream& operator>>(istream& in, Colectie<U,m>& obj);
    template <class U, int m>
    friend ostream& operator<<(ostream& out, const Colectie<U,m>& obj);

    ~Colectie();
};

template<class T, int n>
Colectie<T, n>::Colectie(): nrElem(n), numeColectie("nespecificat"), counter(0){}

template<class T, int n>
Colectie<T, n>:: Colectie(int nrElem, vector<T*> elem, string numeColectie, int counter): nrElem(nrElem), numeColectie(numeColectie), counter(counter)
{
    for(int i=0; i<nrElem && i<elem.size(); i++)
        this->elem.push_back(elem[i]);
}

template<class T, int n>
Colectie<T, n>:: Colectie(string numeColectie): nrElem(n), numeColectie(numeColectie), counter(0)
{
    /*
    for(int i=0; i<nrElem; i++)
    {
        T* a= new T;
        elem.push_back(a);
    }*/
}

template<class T, int n>
Colectie<T, n>::Colectie(const Colectie& obj): nrElem(obj.nrElem), numeColectie(obj.numeColectie), counter(counter)
{
    for(int i=0; i<nrElem; i++)
        this->elem.push_back(obj.elem[i]);
}

template<class T, int n>
int Colectie<T,n>::getNrElem() const
{
    return nrElem;
}

template<class T, int n>
string Colectie<T,n>::getNume() const
{
    return this->numeColectie;
}

template<class T, int n>
void Colectie<T,n>::addElem(T* obj)
{
    if(counter<nrElem-1)
        elem.push_back(obj);
}

template<class T, int n>
void Colectie<T,n>::setNume(string numeColectie)
{
    this->numeColectie=numeColectie;
}

template<class T, int n>
T& Colectie<T,n>::operator[](int i)
{
    return *elem[abs(i)%nrElem];
}

template<class T, int n>
Colectie<T,n>& Colectie<T,n>::operator=(const Colectie<T,n>& obj)
{
    if(this!=&obj && nrElem==obj.nrElem)
    {
        if(elem!=NULL)
            delete[] elem;
        elem=new T[nrElem];
        for(int i=0; i<nrElem; i++)
            if(obj.elem[i]!=NULL)
                elem[i]=obj.elem[i];
        numeColectie=obj.numeColectie;
    }
    return *this;
}

template <class T, int n>
Colectie<T,n>::~Colectie()
{
    if(elem.empty()!=0)
        elem.clear();
}

template <class T, int n>
ostream& operator<<(ostream& out, const Colectie<T,n>& obj)
{
    out<<obj.numeColectie<<endl;
    for(int i=0; i<obj.elem.size() && obj.elem[i]->getNume()!="necompletat"; i++)
    {
        out<<*obj.elem[i]<<endl<<endl;
    }
    return out;
}

/// METODE TEMPLATE
template <class T>
float sumaTemplate(float s, T obj)
{
    return s+obj.getPret();
}

template <class T>
float sumaTemplate(T obj, float s)
{
    return s+obj.getPret();
}

float sumaTemplate(float s1, float s2)
{
    return s1+s2;
}

template <class T>
float addCommision(T obj)
{
    return (obj*1.19).getPret();
}

template <class T>
string productList(T obj1, T obj2)
{
    return (obj1+obj2).getNume();
}

template <class T>
string productList(string s, T obj2)
{
    if(s=="")
        return obj2.getNume();
    else
        return (s+", "+obj2.getNume());
}

template <class T>
string productList(T obj1, string s)
{
    if(s=="")
        return obj1.getNume();
    return (obj1.getNume()+", "+s);
}

string productList(string s1, string s2)
{
    return s1+s2;
}

/// continuare cod

void afisareProdus(Produs* p)
{
    if(typeid(*p)==typeid(Bluza))
    {
        cout<<"TIP PRODUS: BLUZA \n";
        cout<<*static_cast<Bluza*>(p);
        cout<<endl;
    }
    else if (typeid(*p)==typeid(Pantaloni))
    {
        cout<<"TIP PRODUS: PANTALONI \n";
        cout<<*static_cast<Pantaloni*>(p);
        cout<<endl;
    }
    else if(typeid(*p)==typeid(Cercei))
    {
        cout<<"TIP PRODUS: CERCEI \n";
        cout<<*static_cast<Cercei*>(p);
        cout<<endl;
    }
    else if(typeid(*p)==typeid(Lant))
    {
        cout<<"TIP PRODUS: LANT \n";
        cout<<*static_cast<Lant*>(p);
        cout<<endl;
    }
}


/// SINGLETON
class Inventar
{
private:
    static Inventar* instanta;
    list<Produs*> produse; /// lista cu produse din inventar
    map<string, int> stocuri; /// stocuri pe categorii - denumiri de produse (chiar daca sunt acelasi tip, pot fi produse diferite)

    Inventar(){};

public:
    static Inventar* getInstanta();
    list<Produs*>* getProduse();

    void addProdus(Produs* obj);
    void modifProdStoc(string vechi, string nou);

    void afisare();
    void afisareStoc();
    void citire();
    void citireProdus();

};

Inventar* Inventar::getInstanta()
{
    if(instanta==NULL)
        instanta=new Inventar();
    return instanta;
}

list<Produs*>* Inventar::getProduse()
{
    return &produse;
}

void Inventar::addProdus(Produs* obj)
{
    produse.push_back(obj);
    string cat=obj->getNume();
    stocuri[cat]++;
}

void Inventar::modifProdStoc(string vechi, string nou)
{
    if(stocuri[vechi]>0)
        stocuri[vechi]--;
    if(stocuri[vechi]==0)
        stocuri.erase(vechi);
    stocuri[nou]++;
}

void Inventar::afisare()
{
    cout<<"\n\n     *AFISARE INVENTAR*     \n\n";
    for(list<Produs*>::iterator i=produse.begin(); i!=produse.end(); ++i)
    {
        afisareProdus(*i);
    }
}

void Inventar::afisareStoc()
{
    cout<<"\n\n     *AFISARE STOC*     \n\n";
    for(map<string, int>::iterator i=stocuri.begin(); i!=stocuri.end(); ++i)
    {
        cout<<i->first<<": "<<i->second<<endl;
    }
}

void Inventar::citire()
{
    int n, ok=0;
    cout<<"Introduceti numarul de produse ale inventarului: ";
    while(ok==0)
    {
        try
        {
            n=citestePozInt();
            if(n<=0)
                throw(exVAL);
            ok=1;
        }
        catch(excIntrodVal &ex)
        {
            cout<<ex.text();
        }
    }
    ok=0; /// pregatesc pentru urmatorul try

    for(int i=0; i<n; i++)
    {
        Produs* p;
        int caz;
        cout<<"\nCe tip de produs doriti sa introduceti? \n1.Bluza \n2.Pantaloni \n3.Cercei \n4.Lant \n\n";
        while(ok==0)
        {
            try
            {
                caz=citestePozInt();
                if(caz<1 || caz>4)
                    throw exVAL;
                ok=1;
            }
            catch(excIntrodVal &ex)
            {
                cout<<ex.text();
            }
        }
        cout<<endl;
        ok=0; /// pregatesc pentru urmatorul try
        switch(caz)
        {
            case 1:
                {
                    cout<<"Introducere bluza: \n";
                    p=new Bluza;
                    cin>>*dynamic_cast<Bluza*>(p);
                    addProdus(p);
                    cout<<endl;
                    break;
                }
            case 2:
                {
                    cout<<"Introducere pantaloni: \n";
                    p=new Pantaloni;
                    cin>>*dynamic_cast<Pantaloni*>(p);
                    addProdus(p);
                    cout<<endl;
                    break;
                }
            case 3:
                {
                    cout<<"Introducere cercei: \n";
                    p=new Cercei;
                    cin>>*dynamic_cast<Cercei*>(p);
                    addProdus(p);
                    cout<<endl;
                    break;
                }
            case 4:
                {
                    cout<<"Introducere lant: \n";
                    p=new Lant;
                    cin>>*dynamic_cast<Lant*>(p);
                    addProdus(p);
                    cout<<endl;
                    break;
                }
        }
    }

}

void Inventar::citireProdus()
{
    Produs* p;
    int ok=0, caz;
    cout<<"\nCe tip de produs doriti sa introduceti? \n1.Bluza \n2.Pantaloni \n3.Cercei \n4.Lant \n\n";
    while(ok==0)
    {
        try
        {
            caz=citestePozInt();
            if(caz<1 || caz>4)
                throw exVAL;
            ok=1;
        }
        catch(excIntrodVal &ex)
        {
            cout<<ex.text();
        }
    }
    cout<<endl;
    ok=0; /// pregatesc pentru urmatorul try
    switch(caz)
    {
        case 1:
            {
                cout<<"Introducere bluza: \n";
                p=new Bluza;
                cin>>*dynamic_cast<Bluza*>(p);
                addProdus(p);
                cout<<endl;
                break;
            }
        case 2:
            {
                cout<<"Introducere pantaloni: \n";
                p=new Pantaloni;
                cin>>*dynamic_cast<Pantaloni*>(p);
                addProdus(p);
                cout<<endl;
                break;
            }
        case 3:
            {
                cout<<"Introducere cercei: \n";
                p=new Cercei;
                cin>>*dynamic_cast<Cercei*>(p);
                addProdus(p);
                cout<<endl;
                break;
            }
        case 4:
            {
                cout<<"Introducere lant: \n";
                p=new Lant;
                cin>>*dynamic_cast<Lant*>(p);
                addProdus(p);
                cout<<endl;
                break;
            }
    }
}

Inventar* Inventar::instanta=NULL;

int main()
{
    Inventar *a = Inventar::getInstanta();
    Colectie<Produs,10> colectii[3];
    colectii[0].setNume("Black&White");
    colectii[1].setNume("Streetwear");
    colectii[2].setNume("Elegance");

    cout<<"!!Pentru a putea incepe activitatea, este necesara introducerea unui inventar initial!!"<<endl;
    a->citire();

    system("cls");
    int ok=0;
    while(ok==0)
    {
        cout<<"Selectati una dintre variantele disponibile: "<<endl<<"1. Introducere date in inventar"<<endl<<"2. Afisarea tuturor produselor din inventar"<<endl;
        cout<<"3. Afisarea stocurilor din inventar"<<endl<<"4. Afisare colectii"<<endl<<"5. Adaugare produse in colectii(atentie, o colectie nu poate avea mai mult de 10 produse): "<<endl;
        cout<<"6. Editarea unui produs"<<endl<<"7. Functionalitati"<<endl<<"8. Inchidere program"<<endl<<endl;
        int opt, ok1=0;
        while(ok1==0)
        {
            try
            {
                opt=citestePozInt();
                if(opt<1 || opt>8)
                    throw(exVAL);
                ok1=1;
            }
            catch(excIntrodVal &ex)
            {
                cout<<ex.text();
            }
        }
        switch(opt)
        {
        case 1:
            {
                system("cls");
                a->citireProdus();
                break;
            }
        case 2:
            {
                system("cls");
                a->afisare();
                cout<<endl;
                break;
            }
        case 3:
            {
                system("cls");
                a->afisareStoc();
                cout<<endl;
                break;
            }
        case 4:
            {
                system("cls");
                cout<<"Colectiile sunt: "<<endl<<endl;
                for(int i=0; i<3; i++)
                {
                    cout<<colectii[i];
                }
                cout<<endl;
                break;
            }
        case 5:
            {
                system("cls");
                cout<<"Colectiile disponibile sunt: "<<endl;
                for(int i=0; i<3; i++)
                    cout<<i+1<<". "<<colectii[i].getNume()<<endl;

                int ok2=0, opt2, id;
                cout<<endl<<"Selectati colectia: ";
                while(ok2==0)
                {
                    try
                    {
                        opt2=citestePozInt();
                        if(opt2<1 || opt2>3)
                            throw(exVAL);
                        ok2=1;
                        opt2--;
                    }
                    catch(excIntrodVal &ex)
                    {
                        cout<<ex.text();
                    }
                }
                ok2=0;
                cout<<endl<<"Introduceti ID-ul produsului care sa fie adaugat in colectie: ";
                while(ok2==0)
                {
                    try
                    {
                        id=citestePozInt();
                        if(id<10001)
                            throw(exVAL);
                        ok2=1;
                    }
                    catch(excIntrodVal &ex)
                    {
                        cout<<ex.text();
                    }
                }
                ok2=0;

                int gasit=0;
                Produs* prd;
                for(list<Produs*>::iterator i=a->getProduse()->begin(); i!=a->getProduse()->end(); ++i)
                {
                    if((**i).getId()==id)
                    {
                        afisareProdus(*i);
                        prd=*i;
                        gasit=1;
                    }
                }
                if(gasit==0)
                    cout<<"ID-ul introdus nu a fost gasit in inventar"<<endl;
                else
                {
                    colectii[opt2].addElem(prd);
                }
                cout<<endl;

                break;
            }
        case 6:
            {
                system("cls");
                cout<<"Introduceti ID-ul produsului din inventar pe care doriti sa il modificati: ";
                int ok2=0, id, gasit=0, opt2;
                Produs* prd;
                while(ok2==0)
                {
                    try
                    {
                        id=citestePozInt();
                        if(id<10001)
                            throw(exVAL);
                        ok2=1;
                    }
                    catch(excIntrodVal &ex)
                    {
                        cout<<ex.text();
                    }
                }
                ok2=0;
                for(list<Produs*>::iterator i=a->getProduse()->begin(); i!=a->getProduse()->end(); ++i)
                {
                    if((**i).getId()==id)
                    {
                        afisareProdus(*i);
                        prd=*i;
                        gasit=1;
                    }
                }
                if(gasit==0)
                    cout<<"ID-ul introdus nu a fost gasit in inventar"<<endl;
                else
                {
                    cout<<"Ce doriti sa editati? \n(din cauza modului de executare a produselor, se pot modifica doar numele si pretul) \n";
                    cout<<"1. Numele \n2. Pretul \n";
                    cout<<"Introduceti optiunea: ";
                    while(ok2==0)
                    {
                        try
                        {
                            opt2=citestePozInt();
                            if(opt2<1 || opt2>2)
                                throw(exVAL);
                            ok2=1;
                        }
                        catch(excIntrodVal &ex)
                        {
                            cout<<ex.text();
                        }
                    }
                    ok2=0;
                    if(opt2==1)
                    {
                        string numeNou, numeVechi;
                        cout<<"Introduceti noul nume al produsului: ";
                        while(ok2==0)
                        {
                            try
                            {
                                getline(cin, numeNou);
                                if(numeNou=="")
                                    throw runtime_error("Sir vid!");
                                numeVechi=prd->getNume();
                                prd->setNume(numeNou);
                                a->modifProdStoc(numeVechi, numeNou);
                                ok2=1;
                            }
                            catch(runtime_error)
                            {
                                cout<<exVAL.text();
                            }
                        }
                        ok2=0;
                    }
                    else
                    {
                        int pretNou;
                        cout<<"Introduceti noul pret al produsului: ";
                        while(ok2==0)
                        {
                            try
                            {
                                pretNou=citestePozInt();
                                prd->setPret(pretNou);
                                ok2=1;
                            }
                            catch(excIntrodVal &ex)
                            {
                                cout<<ex.text();
                            }
                        }
                    }
                }
                system("cls");
                break;
            }
        case 7:
            {
                system("cls");
                cout<<"FUNCTIONALITATI DATE: "<<endl;
                cout<<"1. Valoare produse"<<endl<<"2. Enumerare produse"<<endl;
                cout<<endl<<"Introduceti numarul corespunzator optiunii: ";
                int ok3=0, opt3=0, nrProd;
                float suma=0;
                string text="";
                while(ok3==0)
                {
                    try
                    {
                        opt3=citestePozInt();
                        if(opt3<1 || opt3>2)
                            throw exVAL;
                        ok3=1;
                    }
                    catch(excIntrodVal &ex)
                    {
                        cout<<ex.text();
                    }
                }
                ok3=0;

                cout<<endl<<"Introduceti numarul produselor pentru care doriti efectuarea functionalitatii: ";
                while(ok3==0)
                {
                    try
                    {
                        nrProd=citestePozInt();
                        if(nrProd<1)
                            throw exVAL;
                        ok3=1;
                    }
                    catch(excIntrodVal &ex)
                    {
                        cout<<ex.text();
                    }
                }
                ok3=0;

                for(int i=0; i<nrProd; i++)
                {
                    cout<<"Introduceti ID-ul produsului "<<i+1<<": ";
                    int id, gasit=0;
                    Produs* prd;
                    while(ok3==0)
                    {
                        try
                        {
                            id=citestePozInt();
                            if(id<10001)
                                throw(exVAL);
                            for(list<Produs*>::iterator i=a->getProduse()->begin(); i!=a->getProduse()->end(); ++i)
                            {
                                if((**i).getId()==id)
                                {
                                    afisareProdus(*i);
                                    prd=*i;
                                    gasit=1;
                                    ok3=1;
                                }
                            }
                            if(gasit==0)
                            {
                                throw(runtime_error("ID nu a fost gasit"));
                                ok3=0;
                            }
                        }
                        catch(excIntrodVal &ex)
                        {
                            cout<<ex.text();
                        }
                        catch(runtime_error)
                        {
                            cout<<"ID-ul introdus nu a fost gasit in inventar. Incearca din nou: ";
                        }
                    }
                    ok3=0;
                    if(opt3==1)
                    {
                        suma=sumaTemplate(suma, *prd);
                    }
                    else
                    {
                        text=productList(text, *prd);
                    }
                }
                if(opt3==1)
                    cout<<"Suma celor "<<nrProd<<" produse este: "<<suma;
                else cout<<"Enumerarea celor "<<nrProd<<" produse este: "<<text;
                cout<<endl<<endl;

                break;
            }

        case 8:
            {
                system("cls");
                cout<<"PROGRAMUL SE VA INCHIDE"<<endl;
                ok=1;
                break;
            }

        }
    }

    return 0;
}
