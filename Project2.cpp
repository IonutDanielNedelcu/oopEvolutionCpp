#include <iostream>
#include <cstring>
#include <vector>
#include <conio.h>

#define enter 13
#define upkey 72
#define downkey 80

using namespace std;

class Interface // Interfata - are doar functii virtuale PURE
{
public:
    virtual ostream& afisare(ostream&) const = 0;
    virtual istream& citire(istream&) = 0;
    virtual float sumaTotala() const = 0;
    virtual void tranzactie(float suma) = 0;
};

class Card: public Interface
{
protected:
    static int CONTORCARD;
    const int id;
    string nume, iban, numar, expirare;
    int pin, cvv;

public:
    Card(); // fara parametri
    Card(string nume, string iban, string numar, string expirare, int pin, int cvv); // toti parametri
    Card(const Card&); // copy constructor

    Card& operator = (const Card&); // operatorul =

    istream& citire(istream&);
    ostream& afisare(ostream&) const;

    friend istream& operator >> (istream&, Card&);
    friend ostream& operator << (ostream&, const Card&);

    // getteri necesari
    const int getId() const;

    // functionalitate
    bool verificareNumarCard() const;

    // setteri necesari
    void setNume(string nume);
    void setIban(string iban);
    void setNumar(string numar);
    void setExpirare(string expirare);
    void setPin(int pin);
    void setCvv(int cvv);

    virtual ~Card(){};
};

class CardEconomii: virtual public Card
{
protected:
    float sumaEconomii, dobanda;

public:
    CardEconomii();
    CardEconomii(string nume, string iban, string numar, string expirare, int pin, int cvv, float sumaEconomii, float dobanda);
    CardEconomii(const CardEconomii&);

    CardEconomii& operator = (const CardEconomii&);

    istream& citire(istream&);
    ostream& afisare(ostream&) const;

    float sumaTotala() const;
    void tranzactie(float suma);

    float sumaLaAn() const;

    // setteri necesari
    void setSumaEconomii(float sumaEconomii);
    void setDobanda(float dobanda);

    ~CardEconomii(){};
};

class CardDebit: virtual public Card
{
protected:
    float sumaDebit;
    bool salariu, minor; /// are/nu salariul la aceasta banca; e card de minori sau adulti

public:

    CardDebit();
    CardDebit(string nume, string iban, string numar, string expirare, int pin, int cvv, float sumaDebit, bool salariu, bool minor);
    CardDebit(const CardDebit&);

    CardDebit& operator = (const CardDebit&);

    istream& citire(istream&);
    ostream& afisare(ostream&) const;

    float sumaTotala() const;
    void tranzactie(float suma);
    float bonusCopilLucrator() const;

    // setteri necesari
    void setSumaDebit(float sumaDebit);
    void setSalariu(bool salariu);
    void setMinor(bool minor);

    ~CardDebit(){};
};

class CardIncorporat: public CardEconomii, public CardDebit
{
private:
    double raportEconomii;
    float completareEconomie;
    // pana la ce multiplu de completareEconomie sa se rotunjeasca suma dintr-o tranzactie, astfel incat restul sa fie transferat din sumaDebit in sumaEconomii

public:

    CardIncorporat();
    CardIncorporat(string nume, string iban, string numar, string expirare, int pin, int cvv, float sumaEconomii, float dobanda, float sumaDebit, bool salariu,
                   bool minor, double raportEconomii, float completareEconomie);
    CardIncorporat(const CardIncorporat&);

    CardIncorporat& operator = (const CardIncorporat&);

    istream& citire(istream&);
    ostream& afisare(ostream&) const;

    float sumaTotala() const;
    void tranzactie(float suma);
    void economisire(float suma);
    void recalculareRaport();
    void recalculareDobanda();


    // setteri necesari
    void setRaportEconomii(double raportEconomii);
    void setCompletareEconomie(float completareEconomie);

    ~CardIncorporat(){};
};

class CardCredit: virtual public Card
{
protected:
    float sumaCredit, dobCredit;

public:
    CardCredit();
    CardCredit(string nume, string iban, string numar, string expirare, int pin, int cvv, float sumaCredit, float dobCredit);
    CardCredit(const CardCredit&);

    CardCredit& operator = (const CardCredit&);

    istream& citire(istream&);
    ostream& afisare(ostream&) const;

    float sumaTotala() const;
    void tranzactie(float suma);

    float dobandaLaAn() const;

    // setteri necesari
    void setSumaCredit(float sumaDebit);
    void setDobandaCredit(float dobCredit);

    ~CardCredit(){};

};

/// CLASA CARD

int Card :: CONTORCARD=1000;
Card :: Card(): id(CONTORCARD++), nume("necompletat"), iban("necompletat"), numar("necompletat"), expirare("necompletat"),pin(0),cvv(0){};
Card :: Card(string nume, string iban, string numar, string expirare, int pin, int cvv): id(CONTORCARD++), nume(nume), iban(iban),
    numar(numar), expirare(expirare), pin(pin), cvv(cvv){};
Card :: Card(const Card &obj): id(obj.id), nume(obj.nume), iban(obj.iban), numar(obj.numar), expirare(obj.expirare), pin(obj.pin), cvv(obj.cvv){};

Card& Card :: operator = (const Card &obj)
{
    if(this!=&obj)
    {
        this->nume=obj.nume;
        this->iban=obj.iban;
        this->numar=obj.numar;
        this->expirare=obj.expirare;
        this->pin=obj.pin;
        this->cvv=obj.cvv;
    }
    return *this;
}

istream& Card :: citire(istream& in) // functie citire
{
    char s[101];
    cout<<"Nume: ";
    in.getline(s,100);
    this->nume=s;
    cout<<"IBAN cont: ";
    in.getline(s,100);
    this->iban=s;
    cout<<"Numar card: ";
    in.getline(s,100);
    this->numar=s;
    cout<<"Expirare(format: ll/aa): ";
    in.getline(s,100);
    this->expirare=s;
    cout<<"Pin(4 cifre): ";
    in >> this->pin;
    cout<<"CVV/CVC(3 cifre): ";
    in >> this->cvv;

    return in;
}

ostream& Card :: afisare(ostream& out) const // functie afisare
{
    out<<"ID Card: "<<this->id<<endl;
    out<<"Nume: "<<this->nume<<endl;
    out<<"IBAN cont: "<<this->iban<<endl;
    out<<"Numar card: "<<this->numar<<endl;
    out<<"Expirare(format: ll/aa): "<<this->expirare<<endl;
    out<<"Pin(4 cifre): "<<this->pin<<endl;
    out<<"CVV/CVC(3 cifre): "<<this->cvv<<endl;
    return out;
}

istream& operator >> (istream &in, Card &obj)
{
    return obj.citire(in);
}

ostream& operator << (ostream &out, const Card &obj)
{
    return obj.afisare(out);
}

//getteri necesari
const int Card :: getId() const
{
    return this->id;
}

// functionalitate
bool Card :: verificareNumarCard() const
{
    if(this->numar.size()==16)
    {
        bool ok=1;
        for(int i=0; i<numar.size(); i++)
            if(numar[i]<'0' || numar[i]>'9')
                ok=0;
        return ok;
    }
    else if(this->numar.size()==19)
    {
        bool ok=1;
        for(int i=0; i<numar.size(); i++)
        {
            if(i==4 || i==9 || i==14)
            {
                if(numar[i]!=' ')
                    ok=0;
            }
            else if(numar[i]<'0' || numar[i]>'9')
                ok=0;
        }
        return ok;
    }
    else return false;
}

//setteri necesari
void Card :: setNume(string nume)
{
    this->nume=nume;
}
void Card :: setIban(string iban)
{
    this->iban=iban;
}
void Card :: setNumar(string numar)
{
    this->numar=numar;
}
void Card :: setExpirare(string expirare)
{
    this->expirare=expirare;
}
void Card :: setPin(int pin)
{
    this->pin=pin;
}
void Card :: setCvv(int cvv)
{
    this->cvv=cvv;
}



/// CLASA CARD ECONOMII

CardEconomii :: CardEconomii(): Card(), sumaEconomii(0), dobanda(0){};
CardEconomii :: CardEconomii(string nume, string iban, string numar, string expirare, int pin, int cvv, float sumaEconomii, float dobanda):
    Card(nume, iban, numar, expirare, pin, cvv), sumaEconomii(sumaEconomii), dobanda(dobanda){};
CardEconomii :: CardEconomii(const CardEconomii &obj): Card(obj), sumaEconomii(obj.sumaEconomii), dobanda(obj.dobanda){}; // copy constructor

CardEconomii& CardEconomii :: operator = (const CardEconomii &obj)
{
    if(this!=&obj)
    {
        Card::operator=(obj);
        this->sumaEconomii=obj.sumaEconomii;
        this->dobanda=obj.dobanda;
    }
    return *this;
}

istream& CardEconomii :: citire(istream& in) // functie citire, se ajunge la ea prin virtual, apelat din operatorul << din parinte
{
    Card::citire(in);
    cout<<"Suma economii: ";
    in >> this->sumaEconomii;
    cout<<"Dobanda la an(%): ";
    in >> this->dobanda;

    return in;
}

ostream& CardEconomii :: afisare(ostream& out) const // functie afisare, se ajunge la ea prin virtual, apelat din operatorul >> din parinte
{
    Card::afisare(out);
    out<<"Suma economii: "<<this->sumaEconomii<<endl;
    out<<"Dobanda la an(%): "<<this->dobanda<<endl;

    return out;
}

/// clasa nu mai are nevoie de operatorii << si >>, deoarece mosteneste clasa Card, care apeleaza functii virtuale

float CardEconomii :: sumaTotala() const
{
    return this->sumaEconomii;
}

void CardEconomii :: tranzactie(float suma)
{
    /// nu se pot face tranzactii in cardul de economii
}

float CardEconomii :: sumaLaAn() const
{
    return (this->sumaEconomii*(this->dobanda/100));
}

//setteri necesari
void CardEconomii :: setSumaEconomii(float sumaEconomii)
{
    this->sumaEconomii=sumaEconomii;
}
void CardEconomii :: setDobanda(float dobanda)
{
    this->dobanda=dobanda;
}


/// CLASA CARD DEBIT

CardDebit :: CardDebit(): Card(), sumaDebit(0), salariu(false), minor(false){};
CardDebit :: CardDebit(string nume, string iban, string numar, string expirare, int pin, int cvv, float sumaDebit, bool salariu, bool minor):
    Card(nume, iban, numar, expirare, pin, cvv), sumaDebit(sumaDebit), salariu(salariu), minor(minor){};
CardDebit :: CardDebit(const CardDebit &obj): Card(obj), sumaDebit(obj.sumaDebit), salariu(obj.salariu), minor(obj.minor){}; // copy constructor

CardDebit& CardDebit :: operator = (const CardDebit &obj)
{
    if(this!=&obj)
    {
        Card::operator=(obj);
        this->sumaDebit=obj.sumaDebit;
        this->salariu=obj.salariu;
        this->minor=obj.minor;
    }
    return *this;
}

istream& CardDebit :: citire(istream& in)
{
    Card::citire(in);
    cout<<"Suma debit: ";
    in >> this->sumaDebit;
    cout<<"Este card de salariu?(0.NU 1.DA): ";
    in >> this->salariu;
    cout<<"Este card pentru copii?(0.NU 1.DA): ";
    in >> this->minor;

    return in;
}

ostream& CardDebit :: afisare(ostream& out) const
{
    Card::afisare(out);
    out<<"Suma debit: "<<this->sumaDebit<<endl;

    out<<"Card de salariu: ";
    if(this->salariu==true)
        out<<"DA"<<endl;
    else out<<"NU"<<endl;

    out<<"Card pentru copii: ";
    if(this->minor==true)
        out<<"DA"<<endl;
    else out<<"NU"<<endl;

    return out;
}

/// clasa nu mai are nevoie de operatorii << si >>, deoarece mosteneste clasa Card, care apeleaza functii virtuale

float CardDebit :: sumaTotala() const
{
    return this->sumaDebit;
}

void CardDebit :: tranzactie(float suma)
{
    this->sumaDebit=this->sumaDebit - suma;
    if(this->sumaDebit<0)
        this->sumaDebit=0;
}

float CardDebit :: bonusCopilLucrator() const
{
    if(this->salariu==true && this->minor==true)
        return (this->sumaDebit*0.05); // 5% din suma de pe card
    else return 0;
}

// setteri necesari
void CardDebit :: setSumaDebit(float sumaDebit)
{
    this->sumaDebit=sumaDebit;
}
void CardDebit :: setSalariu(bool salariu)
{
    this->salariu=salariu;
}
void CardDebit :: setMinor(bool minor)
{
    this->minor=minor;
}


/// CLASA CARD INCORPORAT (ECONOMII+DEBIT)

CardIncorporat :: CardIncorporat(): Card(), CardEconomii(), CardDebit(), raportEconomii(0), completareEconomie(5){};
CardIncorporat :: CardIncorporat(string nume, string iban, string numar, string expirare, int pin, int cvv, float sumaEconomii,
                                 float dobanda, float sumaDebit, bool salariu, bool minor, double raportEconomii, float completareEconomie):
    Card(nume, iban, numar, expirare, pin, cvv), CardEconomii(nume, iban, numar, expirare, pin, cvv, sumaEconomii, dobanda),
    CardDebit(nume, iban, numar, expirare, pin, cvv, sumaDebit, salariu, minor), raportEconomii(raportEconomii), completareEconomie(completareEconomie){};
CardIncorporat :: CardIncorporat(const CardIncorporat &obj): Card(obj), CardEconomii(obj), CardDebit(obj), raportEconomii(obj.raportEconomii), completareEconomie(obj.completareEconomie){}; // copy constructor

CardIncorporat& CardIncorporat :: operator = (const CardIncorporat &obj)
{
    if(this!=&obj)
    {
        CardEconomii::operator=(obj);

        this->sumaDebit=obj.sumaDebit;
        this->salariu=obj.salariu;
        this->minor=obj.minor;

        this->raportEconomii=obj.raportEconomii;
        this->completareEconomie=obj.completareEconomie;
    }
    return *this;
}

istream& CardIncorporat :: citire(istream& in)
{
    CardEconomii::citire(in);
    cout<<"Suma debit: ";
    in >> this->sumaDebit;
    cout<<"Este card de salariu?(0.NU 1.DA): ";
    in >> this->salariu;
    cout<<"Este card pentru copii?(0.NU 1.DA): ";
    in >> this->minor;

    cout<<"Raport economii: ";
    in >> this->raportEconomii;
    cout<<"Suma completare economii: ";
    in >> this->completareEconomie;

    return in;
}

ostream& CardIncorporat :: afisare(ostream& out) const
{
    CardEconomii::afisare(out);

    out<<"Suma debit: "<<this->sumaDebit<<endl;

    out<<"Card de salariu: ";
    if(this->salariu==true)
        out<<"DA"<<endl;
    else out<<"NU"<<endl;

    out<<"Card pentru copii: ";
    if(this->minor==true)
        out<<"DA"<<endl;
    else out<<"NU"<<endl;

    out<<"Raport economii: "<<this->raportEconomii<<endl;
    out<<"Suma completare economii: "<<this->completareEconomie<<endl;

    return out;
}

float CardIncorporat :: sumaTotala() const
{
    return (this->sumaDebit+this->sumaEconomii);
}

void CardIncorporat :: tranzactie(float suma)
{
    int ptCompletare=0;

    while(ptCompletare<suma) // se completeaza suma de scazut pana la multiplul corespunzator si se muta in sumaEconomii
        ptCompletare=ptCompletare+this->completareEconomie;
    if(this->sumaDebit>ptCompletare)
    {
        this->sumaDebit=this->sumaDebit-ptCompletare;
        this->sumaEconomii=this->sumaEconomii + (ptCompletare-suma);
    }
    else
    {
        if(this->sumaDebit>suma)
            this->sumaDebit=this->sumaDebit-suma;
        else this->sumaDebit=0;
    }

}

void CardIncorporat :: economisire(float suma)
{
    if(this->sumaDebit > suma)
    {
        this->sumaDebit=this->sumaDebit - suma;
        this->sumaEconomii=this->sumaEconomii + suma;
    }
    else
    {
        this->sumaEconomii=this->sumaEconomii+this->sumaDebit;
        this->sumaDebit=0;
    }
}

void CardIncorporat :: recalculareRaport()
{
    this->raportEconomii=(this->sumaEconomii)/(this->sumaEconomii+this->sumaDebit);
}

void CardIncorporat :: recalculareDobanda()
{
    if(this->salariu==true && this->minor==true)
        this->dobanda=10; // 10 la suta
    else if(this->salariu==true || this->minor==true)
        this->dobanda=7; // 7 la suta
    else
        this->dobanda=5; // 5 la suta
}

// setteri necesari
void CardIncorporat :: setRaportEconomii(double raportEconomii)
{
    this->raportEconomii=raportEconomii;
}
void CardIncorporat :: setCompletareEconomie(float completareEconomie)
{
    this->completareEconomie=completareEconomie;
}


/// CLASA CARD CREDIT

CardCredit :: CardCredit(): Card(), sumaCredit(0), dobCredit(5){};
CardCredit :: CardCredit(string nume, string iban, string numar, string expirare, int pin, int cvv, float sumaCredit, float dobCredit):
    Card(nume, iban, numar, expirare, pin, cvv), sumaCredit(sumaCredit), dobCredit(dobCredit){};
CardCredit :: CardCredit(const CardCredit &obj): Card(obj), sumaCredit(obj.sumaCredit), dobCredit(obj.dobCredit){}; // copy constructor

CardCredit& CardCredit :: operator = (const CardCredit &obj)
{
    if(this!=&obj)
    {
        Card::operator=(obj);
        this->sumaCredit=obj.sumaCredit;
        this->dobCredit=obj.dobCredit;
    }
    return *this;
}

istream& CardCredit :: citire(istream& in)
{
    Card::citire(in);
    cout<<"Suma credit: ";
    in >> this->sumaCredit;
    cout<<"Dobanda credit: ";
    in >> this->dobCredit;

    return in;
}

ostream& CardCredit :: afisare(ostream& out) const
{
    Card::afisare(out);
    out<<"Suma credit: "<<this->sumaCredit<<endl;
    out<<"Dobanda credit: "<<this->dobCredit<<endl;

    return out;
}

/// clasa nu mai are nevoie de operatorii << si >>, deoarece mosteneste clasa Card, care apeleaza functii virtuale

float CardCredit :: sumaTotala() const
{
    return this->sumaCredit;
}

void CardCredit :: tranzactie(float suma)
{
    this->sumaCredit=this->sumaCredit + suma;
}

float CardCredit :: dobandaLaAn() const
{
    return (this->sumaCredit*(1+dobCredit/100));
}

// setteri necesari
void CardCredit :: setSumaCredit(float sumaCredit)
{
    this->sumaCredit=sumaCredit;
}

void CardCredit :: setDobandaCredit(float dobCredit)
{
    this->dobCredit=dobCredit;
}



/// MENIU

int optiuneMain, optiuneMeniu1, optiuneMeniu2, optiuneMeniu3, optiuneMeniu4, optiuneMeniu5, afisare;
vector<Card*> carduri;
/// FUNCTII DE AFISARE MENIU :


void introducereDate() /// citire
{
    // foloseste optiuneMeniu1
    switch(optiuneMeniu1)
    {
        case 1: // card de economii
        {
            Card *a=new CardEconomii;
            cin>>*a;
            carduri.push_back(a); // a e pointer

            break;
        }
        case 2: // card de debit
        {
            Card *a=new CardDebit;
            cin>>*a;
            carduri.push_back(a);

            break;
        }
        case 3: // card incorporat
        {
            Card *a=new CardIncorporat;
            cin>>*a;
            carduri.push_back(a);

            break;
        }
        case 4: // card de credit
        {
            Card *a=new CardCredit;
            cin>>*a;
            carduri.push_back(a); // a e pointer

            break;
        }
    }
}

void afisareDate() /// afisare
{
    int sel=0;
    switch (optiuneMeniu2)
    {
        case 1:
        {
            cout<<"Doriti afisarea unui card de economii anume sau a tuturor?"<<endl;
            cout<<"1.Unul     2.Toate"<<endl<<"Introduceti valoarea: ";
            cin>>sel;
            while(sel!=1 && sel!=2)
            {
                cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                cin>>sel;
            }
            if(sel==1)
            {
                int idCard;
                bool gasit=0;
                cout<<"Introduceti ID-ul cardului de economii de afisat: ";
                cin>>idCard;
                while(idCard<1000)
                {
                    cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                    cin>>idCard;
                }
                for(int i=0; i<carduri.size(); i++)
                {
                    if(typeid(*carduri[i])==typeid(CardEconomii) && idCard==carduri[i]->getId())
                    {
                        cout<<endl<<*carduri[i]<<endl;
                        gasit=1;
                        break;
                    }
                }
                if(gasit==0)
                    cout<<"Ne pare rau, cardul de economii cu ID-ul "<<idCard<<" nu a putut fi gasit"<<endl;
            }
            else
            {
                if(carduri.size()>0)
                {
                    bool gasit=0;
                    cout<<endl;
                    for(int i=0; i<carduri.size(); i++)
                        if(typeid(*carduri[i])==typeid(CardEconomii))
                        {
                            cout<<"Cardul de economii cu ID-ul "<<carduri[i]->getId()<<endl;
                            cout<<*carduri[i]<<endl;
                            gasit=1;
                        }
                    if(gasit==0)
                        cout<<"Ne pare rau, dar nu exista carduri de economii retinute in sistem"<<endl;
                }
                else cout<<"Ne pare rau, dar nu exista carduri de economii retinute in sistem"<<endl;
            }
            break;
        }
        case 2:
        {
            cout<<"Doriti afisarea unui card de debit anume sau a tuturor?"<<endl;
            cout<<"1.Unul     2.Toate"<<endl<<"Introduceti valoarea: ";
            cin>>sel;
            while(sel!=1 && sel!=2)
            {
                cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                cin>>sel;
            }
            if(sel==1)
            {
                int idCard;
                bool gasit=0;
                cout<<"Introduceti ID-ul cardului de debit de afisat: ";
                cin>>idCard;
                while(idCard<1000)
                {
                    cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                    cin>>idCard;
                }
                for(int i=0; i<carduri.size(); i++)
                {
                    if(typeid(*carduri[i])==typeid(CardDebit) && idCard==carduri[i]->getId())
                    {
                        cout<<endl<<*carduri[i]<<endl;
                        gasit=1;
                        break;
                    }
                }
                if(gasit==0)
                    cout<<"Ne pare rau, cardul de debit cu ID-ul "<<idCard<<" nu a putut fi gasit"<<endl;
            }
            else
            {
                if(carduri.size()>0)
                {
                    bool gasit=0;
                    cout<<endl;
                    for(int i=0; i<carduri.size(); i++)
                        if(typeid(*carduri[i])==typeid(CardDebit))
                        {
                            cout<<"Cardul de debit cu ID-ul "<<carduri[i]->getId()<<endl;
                            cout<<*carduri[i]<<endl;
                            gasit=1;
                        }
                    if(gasit==0)
                        cout<<"Ne pare rau, dar nu exista carduri de debit retinute in sistem"<<endl;
                }
                else cout<<"Ne pare rau, dar nu exista carduri de debit retinute in sistem"<<endl;
            }
            break;
        }
        case 3:
        {
            cout<<"Doriti afisarea unui card incorporat anume sau a tuturor?"<<endl;
            cout<<"1.Unul     2.Toate"<<endl<<"Introduceti valoarea: ";
            cin>>sel;
            while(sel!=1 && sel!=2)
            {
                cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                cin>>sel;
            }
            if(sel==1)
            {
                int idCard;
                bool gasit=0;
                cout<<"Introduceti ID-ul cardului incorporat de afisat: ";
                cin>>idCard;
                while(idCard<1000)
                {
                    cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                    cin>>idCard;
                }
                for(int i=0; i<carduri.size(); i++)
                {
                    if(typeid(*carduri[i])==typeid(CardIncorporat) && idCard==carduri[i]->getId())
                    {
                        cout<<endl<<*carduri[i]<<endl;
                        gasit=1;
                        break;
                    }
                }
                if(gasit==0)
                    cout<<"Ne pare rau, cardul incorporat cu ID-ul "<<idCard<<" nu a putut fi gasit"<<endl;
            }
            else
            {
                if(carduri.size()>0)
                {
                    bool gasit=0;
                    cout<<endl;
                    for(int i=0; i<carduri.size(); i++)
                        if(typeid(*carduri[i])==typeid(CardIncorporat))
                        {
                            cout<<"Cardul incorporat cu ID-ul "<<carduri[i]->getId()<<endl;
                            cout<<*carduri[i]<<endl;
                            gasit=1;
                        }
                    if(gasit==0)
                        cout<<"Ne pare rau, dar nu exista carduri incorporate retinute in sistem"<<endl;
                }
                else cout<<"Ne pare rau, dar nu exista carduri incorporate retinute in sistem"<<endl;
            }
            break;
        }
        case 4:
        {
            cout<<"Doriti afisarea unui card de credit anume sau a tuturor?"<<endl;
            cout<<"1.Unul     2.Toate"<<endl<<"Introduceti valoarea: ";
            cin>>sel;
            while(sel!=1 && sel!=2)
            {
                cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                cin>>sel;
            }
            if(sel==1)
            {
                int idCard;
                bool gasit=0;
                cout<<"Introduceti ID-ul cardului de credit de afisat: ";
                cin>>idCard;
                while(idCard<1000)
                {
                    cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                    cin>>idCard;
                }
                for(int i=0; i<carduri.size(); i++)
                {
                    if(typeid(*carduri[i])==typeid(CardCredit) && idCard==carduri[i]->getId())
                    {
                        cout<<endl<<*carduri[i]<<endl;
                        gasit=1;
                        break;
                    }
                }
                if(gasit==0)
                    cout<<"Ne pare rau, cardul de credit cu ID-ul "<<idCard<<" nu a putut fi gasit"<<endl;
            }
            else
            {
                if(carduri.size()>0)
                {
                    bool gasit=0;
                    cout<<endl;
                    for(int i=0; i<carduri.size(); i++)
                        if(typeid(*carduri[i])==typeid(CardCredit))
                        {
                            cout<<"Cardul de credit cu ID-ul "<<carduri[i]->getId()<<endl;
                            cout<<*carduri[i]<<endl;
                            gasit=1;
                        }
                    if(gasit==0)
                        cout<<"Ne pare rau, dar nu exista carduri de credit retinute in sistem"<<endl;
                }
                else cout<<"Ne pare rau, dar nu exista carduri de credit retinute in sistem"<<endl;
            }
            break;
        }
    }
}

void actualizareDate() /// editare
{
    int cod, opt=0;
    switch(optiuneMeniu3)
    {
        case 1:
        {
            int indice=-1, selectie=0;
            if(carduri.size()>0)
            {
                cout<<"Ati solicitat modificarea unui card de economii. Introduceti id-ul acestuia: ";
                cin>>cod;
                while(cod<1000)
                {
                    cout<<"Id-ul introdus nu este valid. Incercati din nou: ";
                    cin>>cod;
                }
                for(int i=0; i<carduri.size(); i++)
                {
                    if(cod==carduri[i]->getId() && typeid(*carduri[i])==typeid(CardEconomii))
                        indice=i;
                }
                if(indice>=0)
                {
                    char aux[100];
                    int auxi;
                    float auxf;

                    cout<<"Ce doriti sa modificati?"<<endl<<"1. Nume"<<endl<<"2. IBAN"<<endl<<"3. Numar"<<endl;
                    cout<<"4. Expirare"<<endl<<"5. PIN"<<endl<<"6. CVV/CVC"<<endl<<"7. Suma Economii"<<endl<<"8. Dobanda"<<endl;
                    cout<<endl<<"Introduceti optiunea:";
                    cin>>opt;
                    while(opt<1 || opt>8)
                    {
                        cout<<"Optiunea selectata nu este valida. Incercati din nou; ";
                        cin>>opt;
                    }
                    switch (opt)
                    {
                    case 1:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        carduri[indice]->setNume(aux);
                        break;
                    case 2:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        carduri[indice]->setIban(aux);
                        break;
                    case 3:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        carduri[indice]->setNumar(aux);
                        break;
                    case 4:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        carduri[indice]->setExpirare(aux);
                        break;
                    case 5:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<1000 || auxi>=10000)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxi;
                        }
                        carduri[indice]->setPin(auxi);
                        break;
                    case 6:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<100 || auxi>=1000)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxi;
                        }
                        carduri[indice]->setCvv(auxi);
                        break;
                    case 7:
                        cout<<"Introduceti numarul: ";
                        cin>>auxf;
                        while(auxf<0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxf;
                        }
                        dynamic_cast<CardEconomii*>(carduri[indice])->setSumaEconomii(auxf);
                        break;
                    case 8:
                        cout<<"Introduceti valoarea dobanzii(%): ";
                        cin>>auxf;
                        while(auxf<0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxf;
                        }
                        dynamic_cast<CardEconomii*>(carduri[indice])->setDobanda(auxf);
                        break;
                    }
                }
                else cout<<"Din pacate, cardul cu id-ul "<<cod<<" nu a fost gasit"<<endl;
            }
            else cout<<"Din pacate, nu exista carduri salvate in sistem"<<endl;
            break;
        }
        case 2:
        {
            int indice=-1, selectie=0;
            if(carduri.size()>0)
            {
                cout<<"Ati solicitat modificarea unui card de debit. Introduceti id-ul acestuia: ";
                cin>>cod;
                while(cod<1000)
                {
                    cout<<"Id-ul introdus nu este valid. Incercati din nou: ";
                    cin>>cod;
                }
                for(int i=0; i<carduri.size(); i++)
                {
                    if(cod==carduri[i]->getId() && typeid(*carduri[i])==typeid(CardDebit))
                        indice=i;
                }
                if(indice>=0)
                {
                    char aux[100];
                    int auxi;
                    float auxf;
                    bool auxb;

                    cout<<"Ce doriti sa modificati?"<<endl<<"1. Nume"<<endl<<"2. IBAN"<<endl<<"3. Numar"<<endl;
                    cout<<"4. Expirare"<<endl<<"5. PIN"<<endl<<"6. CVV/CVC"<<endl<<"7. Suma Debit"<<endl<<"8. Card de salariu"<<endl<<"9. Card pentru copii"<<endl;
                    cout<<endl<<"Introduceti optiunea:";
                    cin>>opt;
                    while(opt<1 || opt>9)
                    {
                        cout<<"Optiunea selectata nu este valida. Incercati din nou; ";
                        cin>>opt;
                    }
                    switch (opt)
                    {
                    case 1:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        carduri[indice]->setNume(aux);
                        break;
                    case 2:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        carduri[indice]->setIban(aux);
                        break;
                    case 3:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        carduri[indice]->setNumar(aux);
                        break;
                    case 4:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        carduri[indice]->setExpirare(aux);
                        break;
                    case 5:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<1000 || auxi>=10000)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxi;
                        }
                        carduri[indice]->setPin(auxi);
                        break;
                    case 6:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<100 || auxi>=1000)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxi;
                        }
                        carduri[indice]->setCvv(auxi);
                        break;
                    case 7:
                        cout<<"Introduceti numarul: ";
                        cin>>auxf;
                        while(auxf<0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxf;
                        }
                        dynamic_cast<CardDebit*>(carduri[indice])->setSumaDebit(auxf);
                        break;
                    case 8:
                        cout<<"Introduceti valoarea corespunzatoare(1.DA 2.NU): ";
                        cin>>auxi;
                        while(auxi!=1 && auxi!=2)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxf;
                        }
                        if(auxi==1)
                            dynamic_cast<CardDebit*>(carduri[indice])->setSalariu(true);
                        else dynamic_cast<CardDebit*>(carduri[indice])->setSalariu(false);
                        break;
                    case 9:
                        cout<<"Introduceti valoarea corespunzatoare(1.DA 2.NU): ";
                        cin>>auxi;
                        while(auxi!=1 && auxi!=2)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxf;
                        }
                        if(auxi==1)
                            dynamic_cast<CardDebit*>(carduri[indice])->setMinor(true);
                        else dynamic_cast<CardDebit*>(carduri[indice])->setMinor(false);
                        break;
                    }
                }
                else cout<<"Din pacate, cardul cu id-ul "<<cod<<" nu a fost gasit"<<endl;
            }
            else cout<<"Din pacate, nu exista carduri salvate in sistem"<<endl;
            break;
        }
        case 3:
        {
            int indice=-1, selectie=0;
            if(carduri.size()>0)
            {
                cout<<"Ati solicitat modificarea unui card incorporat. Introduceti id-ul acestuia: ";
                cin>>cod;
                while(cod<1000)
                {
                    cout<<"Id-ul introdus nu este valid. Incercati din nou: ";
                    cin>>cod;
                }
                for(int i=0; i<carduri.size(); i++)
                {
                    if(cod==carduri[i]->getId() && typeid(*carduri[i])==typeid(CardIncorporat))
                        indice=i;
                }
                if(indice>=0)
                {
                    char aux[100];
                    int auxi;
                    float auxf;
                    double auxd;

                    cout<<"Ce doriti sa modificati?"<<endl<<"1. Nume"<<endl<<"2. IBAN"<<endl<<"3. Numar"<<endl;
                    cout<<"4. Expirare"<<endl<<"5. PIN"<<endl<<"6. CVV/CVC"<<endl<<"7. Suma Economii"<<endl<<"8. Dobanda"<<endl;
                    cout<<"9. Suma Debit"<<endl<<"10. Card de salariu"<<endl<<"11. Card pentru copii"<<endl;
                    cout<<"12. Raportul de economii"<<endl<<"13. Suma de completare economii"<<endl;
                    cout<<endl<<"Introduceti optiunea:";
                    cin>>opt;
                    while(opt<1 || opt>12)
                    {
                        cout<<"Optiunea selectata nu este valida. Incercati din nou; ";
                        cin>>opt;
                    }
                    switch (opt)
                    {
                    case 1:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        carduri[indice]->setNume(aux);
                        break;
                    case 2:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        carduri[indice]->setIban(aux);
                        break;
                    case 3:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        carduri[indice]->setNumar(aux);
                        break;
                    case 4:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        carduri[indice]->setExpirare(aux);
                        break;
                    case 5:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<1000 || auxi>=10000)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxi;
                        }
                        carduri[indice]->setPin(auxi);
                        break;
                    case 6:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<100 || auxi>=1000)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxi;
                        }
                        carduri[indice]->setCvv(auxi);
                        break;
                    case 7:
                        cout<<"Introduceti numarul: ";
                        cin>>auxf;
                        while(auxf<0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxf;
                        }
                        dynamic_cast<CardEconomii*>(carduri[indice])->setSumaEconomii(auxf);
                        break;
                    case 8:
                        cout<<"Introduceti valoarea dobanzii(%): ";
                        cin>>auxf;
                        while(auxf<0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxf;
                        }
                        dynamic_cast<CardEconomii*>(carduri[indice])->setDobanda(auxf);
                        break;
                    case 9:
                        cout<<"Introduceti numarul: ";
                        cin>>auxf;
                        while(auxf<0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxf;
                        }
                        dynamic_cast<CardDebit*>(carduri[indice])->setSumaDebit(auxf);
                        break;
                    case 10:
                        cout<<"Introduceti valoarea corespunzatoare(1.DA 2.NU): ";
                        cin>>auxi;
                        while(auxi!=1 && auxi!=2)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxf;
                        }
                        if(auxi==1)
                            dynamic_cast<CardDebit*>(carduri[indice])->setSalariu(true);
                        else dynamic_cast<CardDebit*>(carduri[indice])->setSalariu(false);
                        break;
                    case 11:
                        cout<<"Introduceti valoarea corespunzatoare(1.DA 2.NU): ";
                        cin>>auxi;
                        while(auxi!=1 && auxi!=2)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxf;
                        }
                        if(auxi==1)
                            dynamic_cast<CardDebit*>(carduri[indice])->setMinor(true);
                        else dynamic_cast<CardDebit*>(carduri[indice])->setMinor(false);
                        break;
                    case 12:
                        cout<<"Introduceti valoarea corespunzatoare: ";
                        cin>>auxd;
                        while(auxd<=0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxd;
                        }
                        dynamic_cast<CardIncorporat*>(carduri[indice])->setRaportEconomii(auxd);
                        break;
                    case 13:
                        cout<<"Introduceti valoarea corespunzatoare: ";
                        cin>>auxf;
                        while(auxf<0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxf;
                        }
                        dynamic_cast<CardIncorporat*>(carduri[indice])->setCompletareEconomie(auxf);
                        break;
                    }
                }
                else cout<<"Din pacate, cardul cu id-ul "<<cod<<" nu a fost gasit"<<endl;
            }
            else cout<<"Din pacate, nu exista carduri salvate in sistem"<<endl;
            break;
        }
        case 4:
        {
            int indice=-1, selectie=0;
            if(carduri.size()>0)
            {
                cout<<"Ati solicitat modificarea unui card de credit. Introduceti id-ul acestuia: ";
                cin>>cod;
                while(cod<1000)
                {
                    cout<<"Id-ul introdus nu este valid. Incercati din nou: ";
                    cin>>cod;
                }
                for(int i=0; i<carduri.size(); i++)
                {
                    if(cod==carduri[i]->getId() && typeid(*carduri[i])==typeid(CardCredit))
                        indice=i;
                }
                if(indice>=0)
                {
                    char aux[100];
                    int auxi;
                    float auxf;
                    bool auxb;

                    cout<<"Ce doriti sa modificati?"<<endl<<"1. Nume"<<endl<<"2. IBAN"<<endl<<"3. Numar"<<endl;
                    cout<<"4. Expirare"<<endl<<"5. PIN"<<endl<<"6. CVV/CVC"<<endl<<"7. Suma Credit"<<endl<<"8. Dobanda Credit"<<endl;
                    cout<<endl<<"Introduceti optiunea:";
                    cin>>opt;
                    while(opt<1 || opt>8)
                    {
                        cout<<"Optiunea selectata nu este valida. Incercati din nou; ";
                        cin>>opt;
                    }
                    switch (opt)
                    {
                    case 1:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        carduri[indice]->setNume(aux);
                        break;
                    case 2:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        carduri[indice]->setIban(aux);
                        break;
                    case 3:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        carduri[indice]->setNumar(aux);
                        break;
                    case 4:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        carduri[indice]->setExpirare(aux);
                        break;
                    case 5:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<1000 || auxi>=10000)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxi;
                        }
                        carduri[indice]->setPin(auxi);
                        break;
                    case 6:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<100 || auxi>=1000)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxi;
                        }
                        carduri[indice]->setCvv(auxi);
                        break;
                    case 7:
                        cout<<"Introduceti numarul: ";
                        cin>>auxf;
                        while(auxf<0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxf;
                        }
                        dynamic_cast<CardCredit*>(carduri[indice])->setSumaCredit(auxf);
                        break;
                    case 8:
                        cout<<"Introduceti numarul: ";
                        cin>>auxf;
                        while(auxf<0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxf;
                        }
                        dynamic_cast<CardCredit*>(carduri[indice])->setDobandaCredit(auxf);
                        break;
                    }
                }
                else cout<<"Din pacate, cardul cu id-ul "<<cod<<" nu a fost gasit"<<endl;
            }
            else cout<<"Din pacate, nu exista carduri salvate in sistem"<<endl;
            break;
        }
    }
}

void stergereDate()
{
    int cod=0, indice=-1;
    switch (optiuneMeniu4)
    {
        case 1:
        {
            cout<<"Introduceti id-ul cardului de economii de sters: ";
            cin>>cod;
            while(cod<1000)
            {
                cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                cin>>cod;
            }
            for(int i=0; i<carduri.size(); i++)
                if(cod==carduri[i]->getId() && typeid(*carduri[i])==typeid(CardEconomii))
                    indice=i;
            if(indice>=0)
            {
                delete carduri[indice];
                carduri.erase(carduri.begin()+indice);
            }
            else cout<<"Nu exista cardul de economii cu id-ul introdus"<<endl;
            break;
        }
        case 2:
        {
            cout<<"Introduceti id-ul cardului de debit de sters: ";
            cin>>cod;
            while(cod<1000)
            {
                cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                cin>>cod;
            }
            for(int i=0; i<carduri.size(); i++)
                if(cod==carduri[i]->getId() && typeid(*carduri[i])==typeid(CardDebit))
                    indice=i;
            if(indice>=0)
            {
                delete carduri[indice];
                carduri.erase(carduri.begin()+indice);
            }
            else cout<<"Nu exista cardul de debit cu id-ul introdus"<<endl;
            break;
        }
        case 3:
        {
            cout<<"Introduceti id-ul cardului incorporat de sters: ";
            cin>>cod;
            while(cod<1000)
            {
                cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                cin>>cod;
            }
            for(int i=0; i<carduri.size(); i++)
                if(cod==carduri[i]->getId() && typeid(*carduri[i])==typeid(CardIncorporat))
                    indice=i;
            if(indice>=0)
            {
                delete carduri[indice];
                carduri.erase(carduri.begin()+indice);
            }
            else cout<<"Nu exista cardul incorporat cu id-ul introdus"<<endl;
            break;
        }
        case 4:
        {
            cout<<"Introduceti id-ul cardului de credit de sters: ";
            cin>>cod;
            while(cod<1000)
            {
                cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                cin>>cod;
            }
            for(int i=0; i<carduri.size(); i++)
                if(cod==carduri[i]->getId() && typeid(*carduri[i])==typeid(CardCredit))
                    indice=i;
            if(indice>=0)
            {
                delete carduri[indice];
                carduri.erase(carduri.begin()+indice);
            }
            else cout<<"Nu exista cardul de credit cu id-ul introdus"<<endl;
            break;
        }
    }
}

void functionalitateDate()
{
    int cod, indice=-1;
    switch(optiuneMeniu5)
    {
        case 1:
        {
            /// Functionalitate - efectuare tranzactie care functioneaza diferit pentru fiecare tip de card
            cout<<"Introduceti id-ul cardului pentru care doriti sa efectuati tranzactia: ";
            cin>>cod;
            while(cod<1000)
            {
                cout<<"Id-ul introdus este invalid. Incercati din nou: ";
                cin>>cod;
            }
            float valoare;
            cout<<"Introduceti valoarea tranzactiei de efectuat: ";
            cin>>valoare;
            if(carduri.size()>0)
            {
                for(int i=0; i<carduri.size(); i++)
                    if(cod==carduri[i]->getId())
                        indice=i;
                if(indice>=0)
                {
                    carduri[indice]->tranzactie(valoare);
                    if(typeid(*carduri[indice])==typeid(CardEconomii))
                        cout<<"Ne pare rau, pe cardurile de economii nu se pot efectua tranzactii"<<endl;
                }
                else cout<<"Ne pare rau, cardul cu id-ul introdus nu exista"<<endl;
            }
            else cout<<"Ne pare rau, dar nu exista carduri retinute in baza de date"<<endl;
            break;
        }
        case 2:
        {
            /// Functionalitate - afisez suma totala de pe un card
            cout<<"Introduceti id-ul cardului pentru care doriti sa vizionati suma totala: ";
            cin>>cod;
            while(cod<1000)
            {
                cout<<"Id-ul introdus este invalid. Incercati din nou: ";
                cin>>cod;
            }
            if(carduri.size()>0)
            {
                for(int i=0; i<carduri.size(); i++)
                    if(cod==carduri[i]->getId())
                        indice=i;
                if(indice>=0)
                {
                    cout<<carduri[indice]->sumaTotala();
                }
                else cout<<"Ne pare rau, cardul cu id-ul introdus nu exista"<<endl;
            }
            else cout<<"Ne pare rau, dar nu exista carduri retinute in baza de date"<<endl;
            break;
        }
        case 3:
        {
            /// Functionalitate - verifica validitatea numarului cardului
            cout<<"Introduceti id-ul cardului caruia doriti sa ii verificati validitatea: ";
            cin>>cod;
            while(cod<1000)
            {
                cout<<"Id-ul introdus este invalid. Incercati din nou: ";
                cin>>cod;
            }
            if(carduri.size())
            {
                for(int i=0; i<carduri.size(); i++)
                    if(cod==carduri[i]->getId())
                        indice=i;
                if(indice>=0)
                {
                    if(carduri[indice]->verificareNumarCard()==true)
                        cout<<"Numarul cardului este valid!"<<endl;
                    else cout<<"Numarul cardului este invalid!"<<endl;
                }
                else cout<<"Ne pare rau, cardul cu id-ul introdus nu exista"<<endl;
            }
            else cout<<"Ne pare rau, dar nu exista carduri retinute in baza de date"<<endl;
            break;
        }
        case 4:
        {
            /// Functionalitate - returnare suma obtinuta dupa un an de economii
            cout<<"Introduceti id-ul cardului de economii pentru care doriti sa vedeti suma primita dupa un an de economisire a sumei curente: ";
            cin>>cod;
            while(cod<1000)
            {
                cout<<"Id-ul introdus este invalid. Incercati din nou: ";
                cin>>cod;
            }
            if(carduri.size()>0)
            {
                int flag=0;
                for(int i=0; i<carduri.size(); i++)
                {
                    if(cod==carduri[i]->getId() && (typeid(*carduri[i])==typeid(CardEconomii) || typeid(*carduri[i])==typeid(CardIncorporat)))
                        indice=i;
                }

                if(indice>=0)
                {
                    cout<<"Suma primita este: "<<dynamic_cast<CardEconomii*>(carduri[indice])->sumaLaAn()<<endl;
                }
                else cout<<"Ne pare rau, cardul de economii sau incorporat cu id-ul introdus nu exista"<<endl;
            }
            else cout<<"Ne pare rau, dar nu exista carduri retinute in baza de date"<<endl;
            break;
        }
        case 5:
        {
            /// Functionalitate - bonus adolescent care lucreaza
            cout<<"Introduceti id-ul cardului de debit pentru care doriti sa vedeti bonusul: ";
            cin>>cod;
            while(cod<1000)
            {
                cout<<"Id-ul introdus este invalid. Incercati din nou: ";
                cin>>cod;
            }
            if(carduri.size()>0)
            {
                for(int i=0; i<carduri.size(); i++)
                    if(cod==carduri[i]->getId() && (typeid(*carduri[i])==typeid(CardDebit) || typeid(*carduri[i])==typeid(CardIncorporat)) )
                        indice=i;
                if(indice>=0)
                {
                    float valoare;
                    valoare=dynamic_cast<CardDebit*>(carduri[indice])->bonusCopilLucrator();
                    if(valoare==0)
                        cout<<"Conditiile necesare nu sunt indeplinite"<<endl;
                    else cout<<"Bonusul obtinut: "<<valoare<<endl;
                }
                else cout<<"Ne pare rau, cardul de debit sau incorporat cu id-ul introdus nu exista"<<endl;
            }
            else cout<<"Ne pare rau, dar nu exista carduri retinute in baza de date"<<endl;
            break;
        }
        case 6:
        {
            /// Functionalitate - recalculare raport de economii
            cout<<"Introduceti id-ul cardului incorporat pentru care doriti recalcularea raportului de economii: ";
            cin>>cod;
            while(cod<1000)
            {
                cout<<"Id-ul introdus este invalid. Incercati din nou: ";
                cin>>cod;
            }
            if(carduri.size()>0)
            {
                for(int i=0; i<carduri.size(); i++)
                    if(cod==carduri[i]->getId() && typeid(*carduri[i])==typeid(CardIncorporat))
                        indice=i;
                if(indice>=0)
                {
                    dynamic_cast<CardIncorporat*>(carduri[indice])->recalculareRaport();
                    cout<<"Recalcularea a fost efectuata"<<endl;
                }
                else cout<<"Ne pare rau, cardul incorporat cu id-ul introdus nu exista"<<endl;
            }
            else cout<<"Ne pare rau, dar nu exista carduri retinute in baza de date"<<endl;
            break;
        }
        case 7:
        {
            /// Functionalitate - recalculare dobanda primita
            cout<<"Introduceti id-ul cardului incorporat pentru care doriti recalcularea dobanzii pe economii: ";
            cin>>cod;
            while(cod<1000)
            {
                cout<<"Id-ul introdus este invalid. Incercati din nou: ";
                cin>>cod;
            }
            if(carduri.size()>0)
            {
                for(int i=0; i<carduri.size(); i++)
                    if(cod==carduri[i]->getId() && typeid(*carduri[i])==typeid(CardIncorporat))
                        indice=i;
                if(indice>=0)
                {
                    dynamic_cast<CardIncorporat*>(carduri[indice])->recalculareDobanda();
                    cout<<"Recalcularea a fost efectuata"<<endl;
                }
                else cout<<"Ne pare rau, cardul incorporat cu id-ul introdus nu exista"<<endl;
            }
            else cout<<"Ne pare rau, dar nu exista carduri retinute in baza de date"<<endl;
            break;
        }
        case 8:
        {
            /// Functionalitate - economisire - trecere din sumaDebit in sumaEconomii
            cout<<"Introduceti id-ul cardului incorporat pentru care doriti efectuarea unei economisiri: ";
            cin>>cod;
            while(cod<1000)
            {
                cout<<"Id-ul introdus este invalid. Incercati din nou: ";
                cin>>cod;
            }
            float valoare;
            cout<<"Introduceti valoarea tranzactiei de efectuat: ";
            cin>>valoare;
            if(carduri.size()>0)
            {
                for(int i=0; i<carduri.size(); i++)
                    if(cod==carduri[i]->getId() && typeid(*carduri[i])==typeid(CardIncorporat))
                        indice=i;
                if(indice>=0)
                {
                    dynamic_cast<CardIncorporat*>(carduri[indice])->economisire(valoare);
                    cout<<"Economisirea a fost efectuata cu succes"<<endl;
                }
                else cout<<"Ne pare rau, cardul incorporat cu id-ul introdus nu exista"<<endl;
            }
            else cout<<"Ne pare rau, dar nu exista carduri retinute in baza de date"<<endl;
            break;
        }
        case 9:
        {
            /// Functionalitate - returnare suma obtinuta dupa un an de creditare
            cout<<"Introduceti id-ul cardului de credit pentru care doriti sa vedeti suma de plata dupa un an de creditare: ";
            cin>>cod;
            while(cod<1000)
            {
                cout<<"Id-ul introdus este invalid. Incercati din nou: ";
                cin>>cod;
            }
            if(carduri.size()>0)
            {
                int flag=0;
                for(int i=0; i<carduri.size(); i++)
                {
                    if(cod==carduri[i]->getId() && typeid(*carduri[i])==typeid(CardCredit))
                        indice=i;
                }

                if(indice>=0)
                {
                    cout<<"Suma de plata este: "<<dynamic_cast<CardCredit*>(carduri[indice])->dobandaLaAn()<<endl;
                }
                else cout<<"Ne pare rau, cardul de credit cu id-ul introdus nu exista"<<endl;
            }
            else cout<<"Ne pare rau, dar nu exista carduri retinute in baza de date"<<endl;
            break;
        }
    }
}


void showMenu(int selectat)
{
    system("cls");
    cout<<"---------- Meniu ----------"<<endl;
    if(selectat==1)
        cout<<"> ";
    else cout<<" ";
    cout<<"1. Introducere date"<<endl;
    if(selectat==2)
        cout<<"> ";
    else cout<<" ";
    cout<<"2. Afisare date"<<endl;
    if(selectat==3)
        cout<<"> ";
    else cout<<" ";
    cout<<"3. Actualizare date"<<endl;
    if(selectat==4)
        cout<<"> ";
    else cout<<" ";
    cout<<"4. Stergere date"<<endl;
    if(selectat==5)
        cout<<"> ";
    else cout<<" ";
    cout<<"5. Functionalitati date"<<endl;
    if(selectat==6)
        cout<<"> ";
    else cout<<" ";
    cout<<"6. Inchidere program"<<endl;
    cout<<"---------------------------"<<endl;
}

void showMeniu1(int selectat1) /// citire
{
    system("cls");
    cout<<"---------- Introducere date ----------"<<endl;
    if(selectat1==1)
        cout<<"> ";
    else cout<<" ";
    cout<<"1. Carduri de Economii"<<endl;
    if(selectat1==2)
        cout<<"> ";
    else cout<<" ";
    cout<<"2. Carduri de Debit"<<endl;
    if(selectat1==3)
        cout<<"> ";
    else cout<<" ";
    cout<<"3. Carduri Incorporate (Economii si Debit)"<<endl;
    if(selectat1==4)
        cout<<"> ";
    else cout<<" ";
    cout<<"4. Carduri de Credit"<<endl;
    if(selectat1==5)
        cout<<"> ";
    else cout<<" ";
    cout<<"5. Inapoi"<<endl;
    cout<<"--------------------------------------"<<endl;
}

void showMeniu2(int selectat2)
{
    system("cls");
    cout<<"---------- Afisare date ----------"<<endl;
    if(selectat2==1)
        cout<<"> ";
    else cout<<" ";
    cout<<"1. Carduri de economii"<<endl;
    if(selectat2==2)
        cout<<"> ";
    else cout<<" ";
    cout<<"2. Carduri de Debit"<<endl;
    if(selectat2==3)
        cout<<"> ";
    else cout<<" ";
    cout<<"3. Carduri Incorporate (Economii si Debit)"<<endl;
    if(selectat2==4)
        cout<<"> ";
    else cout<<" ";
    cout<<"4. Carduri de Credit"<<endl;
    if(selectat2==5)
        cout<<"> ";
    else cout<<" ";
    cout<<"5. Inapoi"<<endl;
    cout<<"----------------------------------"<<endl;
}

void showMeniu3(int selectat3)
{
    system("cls");
    cout<<"---------- Actualizare date ----------"<<endl;
    if(selectat3==1)
        cout<<"> ";
    else cout<<" ";
    cout<<"1. Carduri de economii"<<endl;
    if(selectat3==2)
        cout<<"> ";
    else cout<<" ";
    cout<<"2. Carduri de Debit"<<endl;
    if(selectat3==3)
        cout<<"> ";
    else cout<<" ";
    cout<<"3. Carduri Incorporate (Economii si Debit)"<<endl;
    if(selectat3==4)
        cout<<"> ";
    else cout<<" ";
    cout<<"4. Carduri de Credit"<<endl;
    if(selectat3==5)
        cout<<"> ";
    else cout<<" ";
    cout<<"5. Inapoi"<<endl;
    cout<<"----------------------------------"<<endl;
}

void showMeniu4(int selectat4)
{
    system("cls");
    cout<<"---------- Stergere date ----------"<<endl;
    if(selectat4==1)
        cout<<"> ";
    else cout<<" ";
    cout<<"1. Carduri de economii"<<endl;
    if(selectat4==2)
        cout<<"> ";
    else cout<<" ";
    cout<<"2. Carduri de Debit"<<endl;
    if(selectat4==3)
        cout<<"> ";
    else cout<<" ";
    cout<<"3. Carduri Incorporate (Economii si Debit)"<<endl;
    if(selectat4==4)
        cout<<"> ";
    else cout<<" ";
    cout<<"4. Carduri de Credit"<<endl;
    if(selectat4==5)
        cout<<"> ";
    else cout<<" ";
    cout<<"5. Inapoi"<<endl;
    cout<<"-----------------------------------"<<endl;
}

void showMeniu5(int selectat5)
{
    system("cls");
    cout<<"---------- Functionalitati date ----------"<<endl;
    if(selectat5==1)
        cout<<"> ";
    else cout<<" ";
    cout<<"1. Efectuare tranzactie"<<endl;
    if(selectat5==2)
        cout<<"> ";
    else cout<<" ";
    cout<<"2. Suma totala de pe un card"<<endl;
    if(selectat5==3)
        cout<<"> ";
    else cout<<" ";
    cout<<"3. Verificare numar card"<<endl;
    if(selectat5==4)
        cout<<"> ";
    else cout<<" ";
    cout<<"4. Dobanda primita la an (Card Economii sau Card Incorporat)"<<endl;
    if(selectat5==5)
        cout<<"> ";
    else cout<<" ";
    cout<<"5. Bonus acordat adolescentilor care lucreaza (Card Debit sau Card Incorporat)"<<endl;
    if(selectat5==6)
        cout<<"> ";
    else cout<<" ";
    cout<<"6. Recalculare raport de economii (Card Incorporat)"<<endl;
    if(selectat5==7)
        cout<<"> ";
    else cout<<" ";
    cout<<"7. Recalculare procentaj dobanda primit pe economii (Card Incorporat)"<<endl;
    if(selectat5==8)
        cout<<"> ";
    else cout<<" ";
    cout<<"8. Economisire bani (Card Incorporat)"<<endl;
    if(selectat5==9)
        cout<<"> ";
    else cout<<" ";
    cout<<"9. Suma de plata la an (Card Credit)"<<endl;
    if(selectat5==10)
        cout<<"> ";
    else cout<<" ";
    cout<<"10. Inapoi"<<endl;
    cout<<"------------------------------------------"<<endl;
}

void mainMeniu1() /// citire
{
    // foloseste optiuneMeniu1
    int selectat1=1;
    afisare=0;
    while(optiuneMeniu1==0)
    {
        if(afisare==0)
        {
            showMeniu1(selectat1);
            int tasta=_getch(); // iau tasta apasata
            switch(tasta)
            {
                case upkey: // sus
                {
                    if(selectat1-1<1)
                        selectat1=5; // ULTIMA OPTIUNE
                    else selectat1--;
                    break;
                }
                case downkey: // jos
                {
                    if(selectat1+1>5) // ULTIMA OPTIUNE
                        selectat1=1;
                    else selectat1++;
                    break;
                }
                case enter:
                {
                    switch(selectat1)
                    {
                        case 1:
                        {
                            optiuneMeniu1=1;
                            introducereDate();
                            afisare=1;
                            optiuneMeniu1=0;
                            optiuneMain=0;
                            break;
                        }
                        case 2:
                        {
                            optiuneMeniu1=2;
                            introducereDate();
                            afisare=1;
                            optiuneMeniu1=0;
                            optiuneMain=0;
                            break;
                        }
                        case 3:
                        {
                            optiuneMeniu1=3;
                            introducereDate();
                            afisare=1;
                            optiuneMeniu1=0;
                            optiuneMain=0;
                            break;
                        }
                        case 4:
                        {
                            optiuneMeniu1=4;
                            introducereDate();
                            afisare=1;
                            optiuneMeniu1=0;
                            optiuneMain=0;
                            break;
                        }
                        case 5:
                        {
                            optiuneMeniu1=5;
                            optiuneMain=0;
                            break;
                        }
                    }
                    break;
                }
            }
        }
        else
        {
            cout<<endl<<"Apasati orice tasta pentru a va intoarce la meniul anterior."<<endl;
            _getch();
            afisare=0;
        }
    }
}

void mainMeniu2() /// afisare
{
    // foloseste optiuneMeniu2
    int selectat2=1;
    afisare=0;
    while(optiuneMeniu2==0)
    {
        if(afisare==0)
        {
            showMeniu2(selectat2);
            int tasta=_getch(); // iau tasta apasata
            switch(tasta)
            {
                case upkey: // sus
                {
                    if(selectat2-1<1)
                        selectat2=5; // ULTIMA OPTIUNE
                    else selectat2--;
                    break;
                }
                case downkey: // jos
                {
                    if(selectat2+1>5) // ULTIMA OPTIUNE
                        selectat2=1;
                    else selectat2++;
                    break;
                }
                case enter:
                {
                    switch(selectat2)
                    {
                        case 1:
                        {
                            optiuneMeniu2=1;
                            afisareDate();
                            afisare=1;
                            optiuneMeniu2=0;
                            optiuneMain=0;
                            break;
                        }
                        case 2:
                        {
                            optiuneMeniu2=2;
                            afisareDate();
                            afisare=1;
                            optiuneMeniu2=0;
                            optiuneMain=0;
                            break;
                        }
                        case 3:
                        {
                            optiuneMeniu2=3;
                            afisareDate();
                            afisare=1;
                            optiuneMeniu2=0;
                            optiuneMain=0;
                            break;
                        }
                        case 4:
                        {
                            optiuneMeniu2=4;
                            afisareDate();
                            afisare=1;
                            optiuneMeniu2=0;
                            optiuneMain=0;
                            break;
                        }
                        case 5:
                        {
                            optiuneMeniu2=5;
                            optiuneMain=0;
                            break;
                        }
                    }
                    break;
                }
            }
        }
        else
        {
            cout<<endl<<"Apasati orice tasta pentru a va intoarce la meniul anterior."<<endl;
            _getch();
            afisare=0;
        }

    }
}

void mainMeniu3() /// actualizare
{
    // foloseste optiuneMeniu1
    int selectat3=1;
    afisare=0;
    while(optiuneMeniu3==0)
    {
        if(afisare==0)
        {
            showMeniu3(selectat3);
            int tasta=_getch(); // iau tasta apasata
            switch(tasta)
            {
                case upkey: // sus
                {
                    if(selectat3-1<1)
                        selectat3=5; // ULTIMA OPTIUNE
                    else selectat3--;
                    break;
                }
                case downkey: // jos
                {
                    if(selectat3+1>5) // ULTIMA OPTIUNE
                        selectat3=1;
                    else selectat3++;
                    break;
                }
                case enter:
                {
                    switch(selectat3)
                    {
                        case 1:
                        {
                            optiuneMeniu3=1;
                            actualizareDate();
                            afisare=1;
                            optiuneMeniu3=0;
                            optiuneMain=0;
                            break;
                        }
                        case 2:
                        {
                            optiuneMeniu3=2;
                            actualizareDate();
                            afisare=1;
                            optiuneMeniu3=0;
                            optiuneMain=0;
                            break;
                        }
                        case 3:
                        {
                            optiuneMeniu3=3;
                            actualizareDate();
                            afisare=1;
                            optiuneMeniu3=0;
                            optiuneMain=0;
                            break;
                        }
                        case 4:
                        {
                            optiuneMeniu3=4;
                            actualizareDate();
                            afisare=1;
                            optiuneMeniu3=0;
                            optiuneMain=0;
                            break;
                        }
                        case 5:
                        {
                            optiuneMeniu3=5;
                            optiuneMain=0;
                            break;
                        }
                    }
                    break;
                }
            }
        }
        else
        {
            cout<<endl<<"Apasati orice tasta pentru a va intoarce la meniul anterior."<<endl;
            _getch();
            afisare=0;
        }

    }
}

void mainMeniu4() /// stergere
{
    // foloseste optiuneMeniu1
    int selectat4=1;
    afisare=0;
    while(optiuneMeniu4==0)
    {
        if(afisare==0)
        {
            showMeniu4(selectat4);
            int tasta=_getch(); // iau tasta apasata
            switch(tasta)
            {
                case upkey: // sus
                {
                    if(selectat4-1<1)
                        selectat4=5; // ULTIMA OPTIUNE
                    else selectat4--;
                    break;
                }
                case downkey: // jos
                {
                    if(selectat4+1>5) // ULTIMA OPTIUNE
                        selectat4=1;
                    else selectat4++;
                    break;
                }
                case enter:
                {
                    switch(selectat4)
                    {
                        case 1:
                        {
                            optiuneMeniu4=1;
                            stergereDate();
                            afisare=1;
                            optiuneMeniu4=0;
                            optiuneMain=0;
                            break;
                        }
                        case 2:
                        {
                            optiuneMeniu4=2;
                            stergereDate();
                            afisare=1;
                            optiuneMeniu4=0;
                            optiuneMain=0;
                            break;
                        }
                        case 3:
                        {
                            optiuneMeniu4=3;
                            stergereDate();
                            afisare=1;
                            optiuneMeniu4=0;
                            optiuneMain=0;
                            break;
                        }
                        case 4:
                        {
                            optiuneMeniu4=4;
                            stergereDate();
                            afisare=1;
                            optiuneMeniu4=0;
                            optiuneMain=0;
                            break;
                        }
                        case 5:
                        {
                            optiuneMeniu4=5;
                            optiuneMain=0;
                            break;
                        }
                    }
                    break;
                }
            }
        }
        else
        {
            cout<<endl<<"Apasati orice tasta pentru a va intoarce la meniul anterior."<<endl;
            _getch();
            afisare=0;
        }

    }
}

void mainMeniu5() /// functionalitati
{
    // foloseste optiuneMeniu1
    int selectat5=1;
    afisare=0;
    while(optiuneMeniu5==0)
    {
        if(afisare==0)
        {
            showMeniu5(selectat5);
            int tasta=_getch(); // iau tasta apasata
            switch(tasta)
            {
                case upkey: // sus
                {
                    if(selectat5-1<1)
                        selectat5=10; // ULTIMA OPTIUNE
                    else selectat5--;
                    break;
                }
                case downkey: // jos
                {
                    if(selectat5+1>10) // ULTIMA OPTIUNE
                        selectat5=1;
                    else selectat5++;
                    break;
                }
                case enter:
                {
                    switch(selectat5)
                    {
                        case 1:
                        {
                            optiuneMeniu5=1;
                            functionalitateDate();
                            afisare=1;
                            optiuneMeniu5=0;
                            optiuneMain=0;
                            break;
                        }
                        case 2:
                        {
                            optiuneMeniu5=2;
                            functionalitateDate();
                            afisare=1;
                            optiuneMeniu5=0;
                            optiuneMain=0;
                            break;
                        }
                        case 3:
                        {
                            optiuneMeniu5=3;
                            functionalitateDate();
                            afisare=1;
                            optiuneMeniu5=0;
                            optiuneMain=0;
                            break;
                        }
                        case 4:
                        {
                            optiuneMeniu5=4;
                            functionalitateDate();
                            afisare=1;
                            optiuneMeniu5=0;
                            optiuneMain=0;
                            break;
                        }
                        case 5:
                        {
                            optiuneMeniu5=5;
                            functionalitateDate();
                            afisare=1;
                            optiuneMeniu5=0;
                            optiuneMain=0;
                            break;
                        }
                        case 6:
                        {
                            optiuneMeniu5=6;
                            functionalitateDate();
                            afisare=1;
                            optiuneMeniu5=0;
                            optiuneMain=0;
                            break;
                        }
                        case 7:
                        {
                            optiuneMeniu5=7;
                            functionalitateDate();
                            afisare=1;
                            optiuneMeniu5=0;
                            optiuneMain=0;
                            break;
                        }
                        case 8:
                        {
                            optiuneMeniu5=8;
                            functionalitateDate();
                            afisare=1;
                            optiuneMeniu5=0;
                            optiuneMain=0;
                            break;
                        }
                        case 9:
                        {
                            optiuneMeniu5=9;
                            functionalitateDate();
                            afisare=1;
                            optiuneMeniu5=0;
                            optiuneMain=0;
                            break;
                        }
                        case 10:
                        {
                            optiuneMeniu5=10;
                            optiuneMain=0;
                            break;
                        }
                    }
                    break;
                }
            }
        }
        else
        {
            cout<<endl<<"Apasati orice tasta pentru a va intoarce la meniu."<<endl;
            _getch();
            afisare=0;
        }

    }
}

void mainMenu()
{
    // foloseste optiuneMain
    int selectat=1;

    while(optiuneMain==0)
    {
        showMenu(selectat);
        int tasta=_getch(); // iau tasta apasata
        switch(tasta)
        {
            case upkey: // sus
            {
                if(selectat-1<1)
                    selectat=6; // ULTIMA OPTIUNE
                else selectat--;
                break;
            }
            case downkey: // jos
            {
                if(selectat+1>6) // ULTIMA OPTIUNE
                    selectat=1;
                else selectat++;
                break;
            }
            case enter:
            {
                switch(selectat)
                {
                    case 1:
                    {
                        optiuneMain=1;
                        optiuneMeniu1=0;
                        mainMeniu1();
                        break;
                    }
                    case 2:
                    {
                        optiuneMain=2;
                        optiuneMeniu2=0;
                        mainMeniu2();
                        break;
                    }
                    case 3:
                    {
                        optiuneMain=3;
                        optiuneMeniu3=0;
                        mainMeniu3();
                        break;
                    }
                    case 4:
                    {
                        optiuneMain=4;
                        optiuneMeniu4=0;
                        mainMeniu4();
                        break;
                    }
                    case 5:
                    {
                        optiuneMain=5;
                        optiuneMeniu5=0;
                        mainMeniu5();
                        break;
                    }
                    case 6:
                    {
                        cout<<"Programul se va inchide."<<endl;
                        optiuneMain=6;
                        break;
                    }
                }
                break;
            }
        }
    }
}

int main()
{
    mainMenu();

    for(int i=0; i<carduri.size(); i++)
        delete carduri[i];
    carduri.clear();
}

