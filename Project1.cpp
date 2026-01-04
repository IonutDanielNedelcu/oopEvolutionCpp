#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <conio.h>
//#include <bits/stdc++.h>

#define enter 13
#define upkey 72
#define downkey 80

using namespace std;

class adr
{
private:
    static int CONTORADR;
    const int id;
    char *tara, *judet, *oras, *strada, *bloc; // judetul este perceput ca organizate teritoriala, de ex district, etc
    int nr,scara,etaj,ap;
    bool optional; // 0, daca optional nu e completat, 1 daca e completat
    /* obligatoriu - *tara, *judet, *oras, *strada, numar
    optional - *bloc, scara, etaj, apartament(ap)
    cele optionale vor fi completate cu NULL, respectiv -1, daca nu exista
    la constructorul gol, pt obligatoriu char*, in loc de NULL vom avea "necompletat"
    */

public:

    /// Constructori (3 tipuri - default, adresa fara optional, adresa cu optional)
    adr():id(CONTORADR++)
    {
        tara=NULL; // e necompletat
        judet=NULL; // analog
        oras=NULL; // analog
        strada=NULL; // analog
        nr=-1;

        optional=false;
        bloc=NULL; // analog
        scara=-1;
        etaj=-1;
        ap=-1;
    }

    // cunosc despre adresa doar tara, judetul/districtul, si orasul
    adr(char *tara, char *judet, char *oras):id(CONTORADR++)
    {
        if(tara!=NULL)
        {
            this->tara=new char[strlen(tara)+1];
            strcpy(this->tara,tara);
        }
        else this->tara=NULL;
        if(judet!=NULL)
        {
            this->judet=new char[strlen(judet)+1];
            strcpy(this->judet,judet);
        }
        else this->oras=NULL;
        if(oras!=NULL)
        {
            this->oras=new char[strlen(oras)+1];
            strcpy(this->oras,oras);
        }
        else this->oras=NULL;

        strada=NULL;
        nr=-1;
        optional=false;
        bloc=NULL; // analog
        scara=-1;
        etaj=-1;
        ap=-1;
    }

    // adresa obligatorie - fara detalii despre un posibil apartament
    adr(char *tara, char *judet, char *oras, char *strada, int nr):id(CONTORADR++)
    {
        if(tara!=NULL)
        {
            this->tara=new char[strlen(tara)+1];
            strcpy(this->tara,tara);
        }
        else this->tara=NULL;
        if(judet!=NULL)
        {
            this->judet=new char[strlen(judet)+1];
            strcpy(this->judet,judet);
        }
        else this->oras=NULL;
        if(oras!=NULL)
        {
            this->oras=new char[strlen(oras)+1];
            strcpy(this->oras,oras);
        }
        else this->oras=NULL;
        if(strada!=NULL)
        {
            this->strada=new char[strlen(strada)+1];
            strcpy(this->strada,strada);
        }
        else this->strada=NULL;
        this->nr=nr;

        // partea optionala
        this->optional=false;
        this->bloc=NULL;
        this->scara=-1;
        this->etaj=-1;
        this->ap=-1;
    }

    // adresa obligatorie+optionala (detalii despre un posibil apartament)
    adr(char *tara, char *judet, char *oras, char *strada, int nr, char *bloc, int scara, int etaj, int ap):id(CONTORADR++)
    {
        if(tara!=NULL)
        {
            this->tara=new char[strlen(tara)+1];
            strcpy(this->tara,tara);
        }
        else this->tara=NULL;
        if(judet!=NULL)
        {
            this->judet=new char[strlen(judet)+1];
            strcpy(this->judet,judet);
        }
        else this->oras=NULL;
        if(oras!=NULL)
        {
            this->oras=new char[strlen(oras)+1];
            strcpy(this->oras,oras);
        }
        else this->oras=NULL;
        if(strada!=NULL)
        {
            this->strada=new char[strlen(strada)+1];
            strcpy(this->strada,strada);
        }
        else this->strada=NULL;
        this->nr=nr;

        // partea optionala
        this->optional=true;
        if(bloc!=NULL)
        {
            this->bloc=new char[strlen(bloc)+1];
            strcpy(this->bloc,bloc);
        }
        else this->bloc=NULL;
        this->scara=scara;
        this->etaj=etaj;
        this->ap=ap;
    }

    /// Copy Constructor
    adr(const adr &obj):id(obj.id)
    {
        if(obj.tara!=NULL)
        {
            this->tara=new char[strlen(obj.tara)+1];
            strcpy(this->tara,obj.tara);
        }
        else this->tara=NULL;

        if(obj.judet!=NULL)
        {
            this->judet=new char[strlen(obj.judet)+1];
            strcpy(this->judet,obj.judet);
        }
        else this->judet=NULL;

        if(obj.oras!=NULL)
        {
            this->oras=new char[strlen(obj.oras)+1];
            strcpy(this->tara,obj.tara);
        }
        else this->oras=NULL;

        if(obj.strada!=NULL)
        {
            this->strada=new char[strlen(obj.strada)+1];
            strcpy(this->strada,obj.strada);
        }
        else this->strada=NULL;

        if(obj.bloc!=NULL)
        {
            this->tara=new char[strlen(obj.bloc)+1];
            strcpy(this->bloc,obj.bloc);
        }
        else this->bloc=NULL;

        // partea optionala
        this->nr=obj.nr;
        this->optional=obj.optional;
        this->scara=obj.scara;
        this->etaj=obj.etaj;
        this->ap=obj.ap;
    }

    /// Operatorul =  - se copiaza toata adresa (toate variabilele), id ramane neschimbat
    adr& operator = (const adr &obj)
    {
        if(this != &obj)
        {
            if(this->tara != NULL) // sterg pointerii din obiectul deja existent
                delete[] this->tara;
            if(this->judet != NULL)
                delete[] this->judet;
            if(this->oras != NULL)
                delete[] this->oras;
            if(this->strada != NULL)
                delete[] this->strada;
            if(this->bloc != NULL)
                delete[] this->bloc;

            // pentru fiecare viitor string, verific daca e NULL sau daca exista
            if(obj.tara!=NULL)
            {
                this->tara=new char[strlen(obj.tara)+1];
                strcpy(this->tara,obj.tara);
                this->tara[strlen(obj.tara)]='\0';
            }
            else this->tara=NULL;
            if(obj.judet!=NULL)
            {
                this->judet=new char[strlen(obj.judet)+1];
                strcpy(this->judet,obj.judet);
                this->judet[strlen(obj.judet)]='\0';
            }
            else this->judet=NULL;
            if(obj.oras!=NULL)
            {
                this->oras=new char[strlen(obj.oras)+1];
                strcpy(this->oras,obj.oras);
                this->oras[strlen(obj.oras)]='\0';
            }
            else this->oras=NULL;
            if(obj.strada!=NULL)
            {
                this->strada=new char[strlen(obj.strada)+1];
                strcpy(this->strada,obj.strada);
                this->strada[strlen(obj.strada)]='\0';
            }
            else this->strada=NULL;
            if(obj.bloc!=NULL)
            {
                this->bloc=new char[strlen(obj.bloc)+1];
                strcpy(this->bloc,obj.bloc);
                this->bloc[strlen(obj.bloc)]='\0';
            }
            else this->bloc=NULL;

            this->nr=obj.nr;
            // partea optionala
            this->optional=obj.optional;
            this->scara=obj.scara;
            this->etaj=obj.etaj;
            this->ap=obj.ap;
        }

        return *this;
    }

    /// Operatorul == - 2 adrese sunt egale daca sunt complet identice (exceptand variabila optional)
    bool operator == (const adr &obj)
    {
        bool egal=1;
        if(!((this->tara==NULL && obj.tara==NULL) || stricmp(this->tara,obj.tara)==0))
            egal=0;
        if(!((this->judet==NULL && obj.judet==NULL) || stricmp(this->judet,obj.judet)==0))
            egal=0;
        if(!((this->oras==NULL && obj.oras==NULL) || stricmp(this->oras,obj.oras)==0))
            egal=0;
        if(!((this->strada==NULL && obj.strada==NULL) || stricmp(this->strada,obj.strada)==0))
            egal=0;
        if(this->nr!=obj.nr)
            egal=0;
        if(this->optional!=obj.optional)
            egal=0;
        if(this->optional==true && obj.optional==true)
        {
            if(!((this->bloc==NULL && obj.bloc==NULL) || stricmp(this->bloc,obj.bloc)==0))
                egal=0;
            if(this->scara!=obj.scara)
                egal=0;
            if(this->etaj!=obj.etaj)
                egal=0;
            if(this->ap!=obj.ap)
                egal=0;
        }
        return egal;
    }

    /// Operatorul != - negarea pentru ==
    bool operator != (const adr &obj)
    {
        return !(*this==obj);
    }

    /// Operatorul < (lexicografic intre tara, judet, oras - in aceasta ordine)
    bool operator < (const adr &obj)
    {
        bool mic=1;
        if(this->tara!=NULL)
        {
            if(obj.tara!=NULL)
            {
                if(strcmp(this->tara, obj.tara)>=0)
                    mic=0;
            }
            else mic=0;
        }
        else if(obj.tara==NULL)
                mic=0;

        if(this->judet!=NULL)
        {
            if(obj.judet!=NULL)
            {
                if(strcmp(this->judet, obj.judet)>=0)
                    mic=0;
            }
            else mic=0;
        }
        else if(obj.judet==NULL)
                mic=0;

        if(this->oras!=NULL)
        {
            if(obj.oras!=NULL)
            {
                if(strcmp(this->oras, obj.oras)>=0)
                    mic=0;
            }
            else mic=0;
        }
        else if(obj.oras==NULL)
                mic=0;

        return mic;
    }

    bool operator <= (const adr &obj)
    {
        if(*this<obj || *this==obj)
            return true;
        return false;
    }

    /// Operatorul + cu 2 obiecte din aceeasi clasa - ob din stanga primeste adresa optionala din dreapta
    adr operator + (const adr &obj)
    {
        adr copie=*this;
        copie.optional=obj.optional;
        if(copie.bloc!=NULL)
            delete[] copie.bloc;
        if(obj.bloc!=NULL)
        {
            copie.bloc=new char[strlen(obj.bloc)+1];
            strcpy(copie.bloc, obj.bloc);
        }
        else copie.optional=NULL;
        copie.scara=obj.scara;
        copie.etaj=obj.etaj;
        copie.ap=obj.ap;

        return copie;
    }

    /// Operatorul - cu 2 obiecte din aceeasi clasa - ob din stanga pierde adresa optionala, daca ob din dreapta are adresa optionala
    adr operator - (const adr &obj)
    {
        adr copie=*this;
        if(copie.optional==true)
        {
            if(obj.optional==true)
                {
                    copie.optional=false;
                    if(copie.bloc!=NULL)
                        delete[] copie.bloc;
                    copie.bloc=NULL;
                    copie.scara=-1;
                    copie.etaj=-1;
                    copie.ap=-1;
                }
        }
        return copie;
    }

    /// Operatorul ++ (ambele variante) - ++ adauga adresa optionala, daca nu exista
    adr& operator ++ ()
    {
        if(this->optional==false)
        {
            this->optional=true;
            char aux[100];
            if(this->bloc==NULL)
            {
                this->bloc=new char[strlen("Trebuie completat")+1];
                strcpy(this->bloc, "Trebuie completat");
            }
            this->scara=0;
            this->etaj=0;
            this->ap=0;
        }
        return *this;

    }

    adr operator ++ (int)
    {
        adr copie=*this;
        ++(*this);
        return copie;
    }

    /// Operatorul -- (ambele variante) - -- elimina adresa optional
    adr& operator -- ()
    {
        if(this->optional==true)
        {
            this->optional=false;
            if(this->bloc!=NULL)
                delete[] this->bloc;
            this->bloc=NULL;
            this->scara=-1;
            this->etaj=-1;
            this->ap=-1;
        }
        return *this;
    }

    adr operator -- (int)
    {
        adr copie=*this;
        --(*this);
        return copie;
    }

    /// Operatorul []
    char* operator [] (int index)
    {
        switch(index)
        {
            case 0:
            {
                if(this->tara!=NULL)
                    return this->tara;
                else
                {
                    char *aux;
                    aux=new char[12];
                    strcpy(aux, "Necompletat");
                    return aux;
                }
            }
            case 1:
            {
                if(this->judet!=NULL)
                    return this->judet;
                else
                {
                    char *aux;
                    aux=new char[12];
                    strcpy(aux, "Necompletat");
                    return aux;
                }
            }
            case 2:
            {
                if(this->oras!=NULL)
                    return this->oras;
                else
                {
                    char *aux;
                    aux=new char[12];
                    strcpy(aux, "Necompletat");
                    return aux;
                }
            }
            case 3:
            {
                if(this->strada!=NULL)
                    return this->strada;
                else
                {
                    char *aux;
                    aux=new char[12];
                    strcpy(aux, "Necompletat");
                    return aux;
                }
            }
            case 4:
            {
                {
                if(this->bloc!=NULL)
                    return this->bloc;
                else
                {
                    char *aux;
                    aux=new char[12];
                    strcpy(aux, "Necompletat");
                    return aux;
                }
            }
            }
            default:
            {
                char *aux;
                aux=new char[14];
                strcpy(aux, "Index invalid");
                return aux;
            }
        }
    }

    /// Operatorul cast
    operator string() // implicit
    {
        string s="";

        s=s+"Tara: ";
        if(this->tara!=NULL)
        {
            s=s+this->tara;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        s=s+"Judet: ";
        if(this->judet!=NULL)
        {
            s=s+this->judet;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        s=s+"Oras: ";
        if(this->oras!=NULL)
        {
            s=s+this->oras;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        s=s+"Strada: ";
        if(this->strada!=NULL)
        {
            s=s+this->strada;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        return s;
    }

    operator string() const //explicit
    {
        string s="";

        s=s+"Tara: ";
        if(this->tara!=NULL)
        {
            s=s+this->tara;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        s=s+"Judet: ";
        if(this->judet!=NULL)
        {
            s=s+this->judet;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        s=s+"Oras: ";
        if(this->oras!=NULL)
        {
            s=s+this->oras;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        s=s+"Strada: ";
        if(this->strada!=NULL)
        {
            s=s+this->strada;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        return s;
    }

    /// Functionalitate - functie bool care verifica daca adresa e valida
    bool valida()
    {
        bool ok=1;
        if(this->tara==NULL)
            ok=0;
        if(this->judet==NULL)
            ok=0;
        if(this->oras==NULL)
            ok=0;
        if(this->strada==NULL)
            ok=0;
        if(this->nr==-1 || this->nr==0)
            ok=0;
        if(this->optional==true)
        {
            if(this->bloc==NULL)
                ok=0;
            if(this->scara==-1 || this->scara==0)
                ok=0;
            if(this->etaj==-1)
                ok=0;
            if(this->ap==-1 || this->ap==0)
                ok=0;
        }
        return ok;
    }

    /// Functii citire si afisare
    // void citire()
    // {
    //     char aux[100];
    //     cout<<"Introduceti urmatoarele informatii despre adresa: "<<endl;

    //     cout<<"Tara: ";
    //     cin.getline(aux,100);
    //     while(strcmp(aux,"")==0)
    //         cin.getline(aux,100);
    //     if(this->tara!=NULL)
    //         delete[] this->tara;
    //     if(aux!=NULL)
    //     {
    //         this->tara=new char[strlen(aux)+1];
    //         strcpy(this->tara, aux);
    //     }
    //     else this->tara=NULL;

    //     cout<<"Judet: ";
    //     //cin.get();
    //     cin.getline(aux,100);
    //     if(this->judet!=NULL)
    //         delete[] this->judet;
    //     if(aux!=NULL)
    //     {
    //         this->judet=new char[strlen(aux)+1];
    //         strcpy(this->judet, aux);
    //     }
    //     else this->judet=NULL;

    //     cout<<"Oras: ";
    //     //cin.get();
    //     cin.getline(aux,100);
    //     if(this->oras!=NULL)
    //         delete[] this->oras;
    //     if(aux!=NULL)
    //     {
    //         this->oras=new char[strlen(aux)+1];
    //         strcpy(this->oras, aux);
    //     }
    //     else this->oras=NULL;

    //     cout<<"Strada: ";
    //     //cin.get();
    //     cin.getline(aux,100);
    //     if(this->strada!=NULL)
    //         delete[] this->strada;
    //     if(aux!=NULL)
    //     {
    //         this->strada=new char[strlen(aux)+1];
    //         strcpy(this->strada, aux);
    //     }
    //     else this->strada=NULL;

    //     cout<<"Numarul: ";
    //     cin>>this->nr;

    //     cout<<endl<<"Adresa apartine unui apartament? Introduceti cifra corespunzatoare raspunsului."<<endl;
    //     cout<<"1. DA     2. NU"<<endl<<"Introduceti optiunea: ";
    //     int val;
    //     cin>>val;
    //     while(val!=1 && val!=2)
    //     {
    //         cout<<"Valoarea introdusa nu corespunde selectiei. Incercati din nou. "<<endl<<"Introduceti optiunea: ";
    //         cin>>val;
    //     }
    //     if(val==1)
    //     {
    //         cout<<"Bloc: ";
    //         cin.getline(aux,100);
    //         while(strcmp(aux,"")==0)
    //             cin.getline(aux,100);
    //         if(this->bloc!=NULL)
    //             delete[] this->bloc;
    //         if(aux!=NULL)
    //         {
    //             this->bloc=new char[strlen(aux)+1];
    //             strcpy(this->bloc, aux);
    //         }
    //         else this->bloc=NULL;

    //         cout<<"Scara/Tronson: ";
    //         cin>>this->scara;
    //         cout<<"Etaj: ";
    //         cin>>this->etaj;
    //         cout<<"Apartament: ";
    //         cin>>this->ap;

    //         this->optional=true;
    //     }
    //     else this->optional=false;

    //     cout<<endl<<"Adresa a fost completata cu succes"<<endl;
    // }

    // void afisare()
    // {
    //     if(this->tara!=NULL)
    //         cout<<"Tara: "<<this->tara<<endl;
    //     else cout<<"Tara: nespecificat"<<endl;
    //     if(this->judet!=NULL)
    //         cout<<"Judet/Sector: "<<this->judet<<endl;
    //     else cout<<"Judet: Nespecificat"<<endl;
    //     if(this->oras!=NULL)
    //         cout<<"Oras: "<<this->oras<<endl;
    //     else cout<<"Oras: Nespecificat"<<endl;
    //     if(this->strada!=NULL)
    //         cout<<"Strada: "<<this->strada<<endl;
    //     else cout<<"Strada: Nespecificat"<<endl;
    //     if(this->nr!=-1)
    //         cout<<"Numarul: "<<this->nr<<endl;
    //     else cout<<"Numarul: Nespecificat"<<endl;
    //     if(this->optional==false)
    //         cout<<"Adresa nu contine informatii despre un apartament."<<endl;
    //     else
    //     {
    //         if(this->bloc!=NULL)
    //             cout<<"Bloc: "<<this->bloc<<endl;
    //         else cout<<"Bloc: Nespecificat"<<endl;
    //         if(this->scara!=-1)
    //             cout<<"Scara/Tronson: "<<this->scara<<endl;
    //         else cout<<"Scara/Tronson: Nespecificat"<<endl;
    //         if(this->etaj!=-1)
    //             cout<<"Etaj: "<<this->etaj<<endl;
    //         else cout<<"Etaj: Nespecificat"<<endl;
    //         if(this->ap!=-1)
    //             cout<<"Apartament: "<<this->ap<<endl;
    //         else cout<<"Apartament: Nespecificat"<<endl;
    //     }
    // }

    /// Getters
    int getId()
    {
        return this->id;
    }

    const char* getTara()
    {
        return this->tara;
    }

    const char* getJudet()
    {
        return this->judet;
    }

    const char* getOras()
    {
        return this->oras;
    }

    const char* getStrada()
    {
        return this->strada;
    }

    const char* getBloc()
    {
        return this->bloc;
    }

    int getNr()
    {
        return this->nr;
    }

    int getScara()
    {
        return this->scara;
    }

    int getEtaj()
    {
        return this->etaj;
    }

    int getAp()
    {
        return this->ap;
    }

    bool getOptional()
    {
        return this->optional;
    }

    /// Setters
    void setTara(char* tara)
    {
        if(this->tara!=NULL)
            delete[] this->tara;
        if(tara!=NULL)
        {
            this->tara=new char[strlen(tara)+1];
            strcpy(this->tara,tara);
        }
        else this->tara=NULL;

    }

    void setJudet(char* judet)
    {
        if(this->judet!=NULL)
            delete[] this->judet;
        if(judet!=NULL)
        {
            this->judet=new char[strlen(judet)+1];
            strcpy(this->judet,judet);
        }
        else this->judet=NULL;
    }

    void setOras(char* oras)
    {
        if(this->oras!=NULL)
            delete[] this->oras;
        if(oras!=NULL)
        {
            this->oras=new char[strlen(oras)+1];
            strcpy(this->oras,oras);
        }
        else this->oras=NULL;
    }

    void setStrada(char* strada)
    {
        if(this->strada!=NULL)
            delete[] this->strada;
        if(strada!=NULL)
        {
            this->strada=new char[strlen(strada)+1];
            strcpy(this->strada,strada);
        }
        else this->tara=NULL;
    }

    void setBloc(char* bloc)
    {
        if(this->bloc!=NULL)
            delete[] this->bloc;
        if(bloc!=NULL)
        {
            this->bloc=new char[strlen(bloc)+1];
            strcpy(this->bloc,bloc);
            this->optional=true;
        }
        else this->bloc=NULL;
    }

    void setNr(int nr)
    {
        this->nr=nr;
    }

    void setScara(int scara)
    {
        this->scara=scara;
        this->optional=true;
    }

    void setEtaj(int etaj)
    {
        this->etaj=etaj;
        this->optional=true;
    }

    void setAp(int ap)
    {
        this->ap=ap;
        this->optional=true;
    }

    void setOptional(bool optional)
    {
        this->optional=optional;
    }

    // friend class client;
    // friend class comanda;
    friend ostream& operator << (ostream&, const adr&);
    friend istream& operator >> (istream&, adr&);
    //friend client operator + (const adr&, const client&);

    /// Destructor
    ~adr()
    {
        if(this->tara != NULL)
            delete[] this->tara;
        if(this->judet != NULL)
            delete[] this->judet;
        if(this->oras != NULL)
            delete[] this->oras;
        if(this->strada != NULL)
            delete[] this->strada;
        if(this->bloc != NULL)
            delete[] this->bloc;
    }
};

class client
{
private:
    static int CONTORCLIENT;
    const int id;
    char *nume, *prenume, *nrTel, *email;
    int nrComenzi;
    adr adresaFact, adresaLiv; // adresa de facturare si adresa de livrare

public:

    /// Constructori
    client():id(CONTORCLIENT++) // constructorul vid
    {
        nume=NULL;
        prenume=NULL;
        nrTel=NULL;
        email=NULL;
        nrComenzi=0;
    }

    // client nou care nu are adresa de mail
    client(char *nume, char *prenume, char *nrTel):id(CONTORCLIENT++)
    {
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);
        this->prenume=new char[strlen(prenume)+1];
        strcpy(this->prenume,prenume);
        this->nrTel=new char[strlen(nrTel)+1];
        strcpy(this->nrTel,nrTel);
        email=NULL;
        nrComenzi=0;
    }

    // client nou fara adresa completata
    client(char *nume, char *prenume, char *nrTel, char *email):id(CONTORCLIENT++)
    {
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);
        this->prenume=new char[strlen(prenume)+1];
        strcpy(this->prenume,prenume);
        this->nrTel=new char[strlen(nrTel)+1];
        strcpy(this->nrTel,nrTel);
        this->email=new char[strlen(email)+1];
        strcpy(this->email,email);
        nrComenzi=0;
    }

    // client nou cu date complete, unde adresa de facturare e aceeasi cu cea de livrare
    client(char *nume, char *prenume, char *nrTel, char *email, int nrComenzi, const adr &obj):id(CONTORCLIENT++)
    {
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);
        this->prenume=new char[strlen(prenume)+1];
        strcpy(this->prenume,prenume);
        this->nrTel=new char[strlen(nrTel)+1];
        strcpy(this->nrTel,nrTel);
        this->email=new char[strlen(email)+1];
        strcpy(this->email,email);
        this->nrComenzi=nrComenzi;
        adresaFact=obj;
        adresaLiv=obj;
    }

    // client nou cu date complete, unde adresele sunt diferite - cu toti parametrii
    client(char *nume, char *prenume, char *nrTel, char *email, int nrComenzi, const adr &facturare, const adr &livrare):id(CONTORCLIENT++)
    {
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);
        this->prenume=new char[strlen(prenume)+1];
        strcpy(this->prenume,prenume);
        this->nrTel=new char[strlen(nrTel)+1];
        strcpy(this->nrTel,nrTel);
        this->email=new char[strlen(email)+1];
        strcpy(this->email,email);
        this->nrComenzi=nrComenzi;
        adresaFact=facturare;
        adresaLiv=livrare;
    }

    /// Copy Constructor
    client(const client &obj):id(obj.id)
    {
        if(obj.nume!=NULL)
        {
            this->nume=new char[strlen(obj.nume)+1];
            strcpy(this->nume,obj.nume);
        }
        else this->nume=NULL;

        if(obj.prenume!=NULL)
        {
            this->prenume=new char[strlen(obj.prenume)+1];
            strcpy(this->prenume,obj.prenume);
        }
        else this->prenume=NULL;

        if(obj.nrTel!=NULL)
        {
            this->nrTel=new char[strlen(obj.nrTel)+1];
            strcpy(this->nrTel,obj.nrTel);
        }
        else this->nrTel=NULL;

        if(obj.email!=NULL)
        {
            this->email=new char[strlen(obj.email)+1];
            strcpy(this->email,obj.email);
        }
        else this->email=NULL;

        this->nrComenzi=obj.nrComenzi;
        this->adresaFact=obj.adresaFact;
        this->adresaLiv=obj.adresaLiv;
    }

    /// Operatorul =  - se copiaza toate datele altui client, fara exceptii
    client& operator = (const client &obj)
    {
        if(this!= &obj)
        {
            if(this->nume!=NULL)
                delete[] this->nume;
            if(this->prenume!=NULL)
                delete[] this->prenume;
            if(this->nrTel!=NULL)
                delete[] this->nrTel;
            if(this->email!=NULL)
                delete[] this->email;

            if(obj.nume!=NULL)
            {
                this->nume=new char[strlen(obj.nume)+1];
                strcpy(this->nume, obj.nume);
            }
            else this->nume=NULL;
            if(obj.prenume!=NULL)
            {
                this->prenume=new char[strlen(obj.prenume)+1];
                strcpy(this->prenume, obj.prenume);
            }
            else this->prenume=NULL;
            if(obj.nrTel!=NULL)
            {
                this->nrTel=new char[strlen(obj.nrTel)+1];
                strcpy(this->nrTel, obj.nrTel);
            }
            else this->nrTel=NULL;
            if(obj.email!=NULL)
            {
                this->email=new char[strlen(obj.email)+1];
                strcpy(this->email, obj.email);
            }
            else this->email=NULL;
            this->nrComenzi=obj.nrComenzi;
            this->adresaFact=obj.adresaFact;
            this->adresaLiv=obj.adresaLiv;
        }

        return *this;
    }

    /// Operatorul == - 2 clienti sunt egali daca au acelasi nume, acelasi prenume, si aceeasi adresa de facturare
    bool operator == (const client &obj)
    {
        bool egal=1;
        if(!((this->nume==NULL && obj.nume==NULL) || stricmp(this->nume,obj.nume)==0))
            egal=0;
        if(!((this->prenume==NULL && obj.prenume==NULL) || stricmp(this->prenume,obj.prenume)==0))
            egal=0;
        if(!(this->adresaFact==obj.adresaFact))
            egal=0;
        return egal;
    }

    /// Operatorul != - negarea pentru ==
    bool operator != (const client &obj)
    {
        return !(*this==obj);
    }

    /// Operatorul < - e mai mic daca lexicografic are numele mai mic (ideea "primului la catalog")
    bool operator < (const client &obj)
    {
        bool mic=1;
        if(this->nume!=NULL)
        {
            if(obj.nume!=NULL)
            {
                if(strcmp(this->nume, obj.nume)>=0)
                    mic=0;
            }
            else mic=0;
        }
        else if(obj.nume==NULL)
                mic=0;

        if(this->prenume!=NULL)
        {
            if(obj.prenume!=NULL)
            {
                if(strcmp(this->prenume, obj.prenume)>=0)
                    mic=0;
            }
            else mic=0;
        }
        else if(obj.prenume==NULL)
                mic=0;

        return mic;
    }

    /// Operatorul <=
    bool operator <= (const client &obj)
    {
        if(*this<obj || *this==obj)
            return true;
        return false;
    }

    /// Operatorul + - concateneaza 2 persoane, dar pastreaza adresele celei din stanga
    client operator + (const client &obj)
    {
        client copie=*this;
        char aux[100];

        if(copie.nume!=NULL)
        {
            strcpy(aux, copie.nume);
            delete[] copie.nume;
        }
        else strcpy(aux, "");
        if(strcmp(aux,"")!=0)
        {
            if(obj.nume!=NULL)
            {
                copie.nume=new char[strlen(aux)+strlen(obj.nume)+5+1]; // cele 5 sunt pt concatenarile de stringuri
                strcpy(copie.nume, aux);
                strcat(copie.nume, " sau ");
                strcat(copie.nume, obj.nume);
            }
            else
            {
                copie.nume=new char[strlen(aux)+1];
                strcpy(copie.nume, aux);
            }
        }
        else
        {
            if(obj.nume!=NULL)
            {
                copie.nume=new char[strlen(obj.nume)+1];
                strcpy(copie.nume, obj.nume);
            }
            else copie.nume=NULL;
        }

        if(copie.prenume!=NULL)
        {
            strcpy(aux, copie.prenume);
            delete[] copie.prenume;
        }
        else strcpy(aux, "");
        if(strcmp(aux,"")!=0)
        {
            if(obj.prenume!=NULL)
            {
                copie.prenume=new char[strlen(aux)+strlen(obj.prenume)+5+1]; // cele 5 sunt pt concatenarile de stringuri
                strcpy(copie.prenume, aux);
                strcat(copie.prenume, " sau ");
                strcat(copie.prenume, obj.prenume);
            }
            else
            {
                copie.prenume=new char[strlen(aux)+1];
                strcpy(copie.prenume, aux);
            }
        }
        else
        {
            if(obj.prenume!=NULL)
            {
                copie.prenume=new char[strlen(obj.prenume)+1];
                strcpy(copie.prenume, obj.prenume);
            }
            else copie.prenume=NULL;
        }

        if(copie.nrTel!=NULL)
        {
            strcpy(aux, copie.nrTel);
            delete[] copie.nrTel;
        }
        else strcpy(aux, "");
        if(strcmp(aux,"")!=0)
        {
            if(obj.nrTel!=NULL)
            {
                copie.nrTel=new char[strlen(aux)+strlen(obj.nrTel)+5+1]; // cele 5 sunt pt concatenarile de stringuri
                strcpy(copie.nrTel, aux);
                strcat(copie.nrTel, " sau ");
                strcat(copie.nrTel, obj.nrTel);
            }
            else
            {
                copie.nrTel=new char[strlen(aux)+1];
                strcpy(copie.nrTel, aux);
            }
        }
        else
        {
            if(obj.nrTel!=NULL)
            {
                copie.nrTel=new char[strlen(obj.nrTel)+1];
                strcpy(copie.nrTel, obj.nrTel);
            }
            else copie.nrTel=NULL;
        }

        if(copie.email!=NULL)
        {
            strcpy(aux, copie.email);
            delete[] copie.email;
        }
        else strcpy(aux, "");
        if(strcmp(aux,"")!=0)
        {
            if(obj.email!=NULL)
            {
                copie.email=new char[strlen(aux)+strlen(obj.email)+5+1]; // cele 5 sunt pt concatenarile de stringuri
                strcpy(copie.email, aux);
                strcat(copie.email, " sau ");
                strcat(copie.email, obj.email);
            }
            else
            {
                copie.email=new char[strlen(aux)+1];
                strcpy(copie.email, aux);
            }
        }
        else
        {
            if(obj.email!=NULL)
            {
                copie.email=new char[strlen(obj.email)+1];
                strcpy(copie.email, obj.email);
            }
            else copie.email=NULL;
        }
        copie.nrComenzi=copie.nrComenzi+obj.nrComenzi;

        return copie;
    }

    /// Operatorul - - scad nr de comenzi ale clientului din dreapta
    client operator - (const client &obj)
    {
        client copie=*this;
        copie.nrComenzi=copie.nrComenzi-obj.nrComenzi;
        if(copie.nrComenzi<0)
            copie.nrComenzi=0;
        return copie;
    }

    /// Operatorul ++ - ++ adauga adresa optionala si la facturare, si la livrare
    client& operator ++()
    {
        ++this->adresaFact;
        ++this->adresaLiv;
        return *this;
    }

    client operator ++(int)
    {
        client copie=*this;
        ++(*this);
        return copie;
    }

    /// Operatorul -- - -- elimina adresa optionala si la facturare, si la livrare
    client& operator -- ()
    {
        --this->adresaFact;
        --this->adresaLiv;
        return *this;
    }

    client operator -- (int)
    {
        client copie=*this;
        --(*this);
        return copie;
    }

    /// Operatorul [] - [0]->facturare, [1]->livrare
    const adr& operator [] (int index)
    {
        adr aux;
        switch(index)
        {
            case 0: return this->adresaFact;
            case 1: return this->adresaLiv;
            default:
            {
                return aux;
            }
        }
    }

    /// Operatorul cast
    operator string() // implicit
    {
        string s="";

        s=s+"Nume: ";
        if(this->nume!=NULL)
        {
            s=s+this->nume;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        s=s+"Prenume: ";
        if(this->prenume!=NULL)
        {
            s=s+this->prenume;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        s=s+"Numar telefon: ";
        if(this->nrTel!=NULL)
        {
            s=s+this->nrTel;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        s=s+"Email: ";
        if(this->email!=NULL)
        {
            s=s+this->email;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        return s;
    }

    operator string() const // explicit
    {
        string s="";

        s=s+"Nume: ";
        if(this->nume!=NULL)
        {
            s=s+this->nume;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        s=s+"Prenume: ";
        if(this->prenume!=NULL)
        {
            s=s+this->prenume;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        s=s+"Numar telefon: ";
        if(this->nrTel!=NULL)
        {
            s=s+this->nrTel;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        s=s+"Email: ";
        if(this->email!=NULL)
        {
            s=s+this->email;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        return s;
    }

    /// Adunare cu o adresa - adresa de facturare si adresa de livrare primesc adresa respectiva
    client operator + (const adr &obj)
    {
        client copie=*this;
        copie.adresaFact=obj;
        copie.adresaLiv=obj;
        return copie;
    }

    /// Functionalitate - verific daca un client completat integral
    bool completat()
    {
        bool ok=1;
        if(this->nume==NULL || this->prenume==NULL || this->nrTel==NULL || this->email==NULL)
            ok=0;
        if(this->adresaFact.valida()==false || this->adresaLiv.valida()==false)
            ok=0;
        return ok;
    }

    /// Functiile de afisare si citire
    // void citire()
    // {
    //     char aux[100];
    //     cout<<"Introduceti urmatoarele informatii despre client: "<<endl;

    //     cout<<"Nume: ";
    //     cin.getline(aux,100);
    //     while(strcmp(aux,"")==0)
    //         cin.getline(aux,100);
    //     if(this->nume!=NULL)
    //         delete[] this->nume;
    //     if(aux!=NULL)
    //     {
    //         this->nume=new char[strlen(aux)+1];
    //         strcpy(this->nume, aux);
    //     }
    //     else this->nume=NULL;

    //     cout<<"Prenume: ";
    //     //cin.get();
    //     cin.getline(aux,100);
    //     if(this->prenume!=NULL)
    //         delete[] this->prenume;
    //     if(aux!=NULL)
    //     {
    //         this->prenume=new char[strlen(aux)+1];
    //         strcpy(this->prenume, aux);
    //     }
    //     else this->prenume=NULL;

    //     cout<<"Numar Telefon: ";
    //     //cin.get();
    //     cin.getline(aux,100);
    //     if(this->nrTel!=NULL)
    //         delete[] this->nrTel;
    //     if(aux!=NULL)
    //     {
    //         this->nrTel=new char[strlen(aux)+1];
    //         strcpy(this->nrTel, aux);
    //     }
    //     else this->nrTel=NULL;

    //     cout<<"Email: ";
    //     //cin.get();
    //     cin.getline(aux,100);
    //     if(this->email!=NULL)
    //         delete[] this->email;
    //     if(aux!=NULL)
    //     {
    //         this->email=new char[strlen(aux)+1];
    //         strcpy(this->email, aux);
    //     }
    //     else this->email=NULL;

    //     cout<<endl<<"Cate comenzi a avut clientul?"<<endl;
    //     cin>>this->nrComenzi;
    //     cout<<endl<<"Introduceti adresa de facturare: "<<endl;
    //     cin>>this->adresaFact;
    //     cout<<endl<<"Adresa de livrare este aceeasi cu cea de facturare? Introduceti cifra corespunzatoare raspunsului."<<endl;
    //     cout<<"1. DA     2. NU"<<endl<<"Introduceti optiunea: ";
    //     int val;
    //     cin>>val;
    //     while(val!=1 && val!=2)
    //     {
    //         cout<<"Valoarea introdusa nu corespunde selectiei. Incercati din nou. "<<endl<<"Introduceti optiunea: ";
    //         cin>>val;
    //     }
    //     if(val==1)
    //         this->adresaLiv=this->adresaFact;
    //     else
    //     {
    //         cout<<endl<<"Introduceti adresa de livrare: "<<endl;
    //         cin>>this->adresaLiv;
    //     }
    //     cout<<endl<<"Ati completat cu succes datele clientului."<<endl;
    // }

    // void afisare()
    // {
    //     if(this->nume!=NULL)
    //         cout<<"Nume: "<<this->nume<<endl;
    //     else cout<<"Nume: Nespecificat"<<endl;
    //     if(this->prenume!=NULL)
    //         cout<<"Prenume: "<<this->prenume<<endl;
    //     else cout<<"Prenume: Nespecificat"<<endl;
    //     if(this->nrTel!=NULL)
    //         cout<<"Numar Telefon: "<<this->nrTel<<endl;
    //     else cout<<"Numar Telefon: Nespecificat"<<endl;
    //     if(this->email!=NULL)
    //         cout<<"Email: "<<this->email<<endl;
    //     else cout<<"Email: Nespecificat"<<endl;
    //     cout<<"Numar comenzi: "<<this->nrComenzi<<endl<<endl;
    //     cout<<"Adresa de facturare:"<<endl;
    //     cout<<this->adresaFact<<endl;
    //     cout<<"Adresa de livrare:"<<endl;
    //     cout<<this->adresaLiv<<endl;
    // }

    /// Getters pentru toate variabilele
    int getId()
    {
        return this->id;
    }

    const char* getNume()
    {
        return this->nume;
    }

    const char* getPrenume()
    {
        return this->prenume;
    }

    const char* getNrTel()
    {
        return this->nrTel;
    }

    const char* getEmail()
    {
        return this->email;
    }

    int getNrComenzi()
    {
        return this->nrComenzi;
    }

    const adr& getAdresaFact()
    {
        return this->adresaFact;
    }

    const adr& getAdresaLiv()
    {
        return this->adresaLiv;
    }

    /// Setters pentru toate variabilele
    void setNume(char* nume)
    {
        if(this->nume!=NULL)
            delete[] this->nume;
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);
    }

    void setPrenume(char* prenume)
    {
        if(this->prenume!=NULL)
            delete[] this->prenume;
        this->prenume=new char[strlen(prenume)+1];
        strcpy(this->prenume,prenume);
    }

    void setNrTel(char* nrTel)
    {
        if(this->nrTel!=NULL)
            delete[] this->nrTel;
        this->nrTel=new char[strlen(nrTel)+1];
        strcpy(this->nrTel,nrTel);
    }

    void setEmail(char* email)
    {
        if(this->email!=NULL)
            delete[] this->email;
        this->email=new char[strlen(email)+1];
        strcpy(this->email,email);
    }

    void setNrComenzi(int nrComenzi)
    {
        this->nrComenzi=nrComenzi;
    }

    void setAdresaFact(const adr &adresaFact)
    {
        this->adresaFact=adresaFact;
    }

    void setAdresaLiv(const adr &adresaLiv)
    {
        this->adresaLiv=adresaLiv;
    }

    friend ostream& operator << (ostream&, const client&);
    friend istream& operator >> (istream&, client &);
    friend client operator + (const adr&, const client&);

    /// Destructor
    ~client()
    {
        if(this->nume != NULL)
            delete[] this->nume;
        if(this->prenume != NULL)
            delete[] this->prenume;
        if(this->nrTel != NULL)
            delete[] this->nrTel;
        if(this->email != NULL)
            delete[] this->email;
    }
};

class fir
{
private:
    static int CONTORFIR;
    const int id;
    char *denumire, *compozitie;
    int grosime, metraj, gramaj, nrCulori; // grosime 0,1,...,6 de la subtire la gros
    int *coduriCulori, *nrStoc; // sunt corelate - pe pozitia i sunt culoarea si stocul pt ea
    double lucrat; // grosimea andrelelor/crosetei cu care trebuie lucrat

public:

    /// Constructori
    fir():id(CONTORFIR++)
    {
        denumire=NULL;
        compozitie=NULL;
        grosime=-1; // necompletata - exista grosimea 0 la fire
        metraj=0;
        gramaj=0;
        nrStoc=NULL;
        nrCulori=0;
        coduriCulori=NULL;
        lucrat=0;
    }

    // firul are doar denumire, compozitie, si un cod. Detaliile despre acesta nu sunt cunoscute
    fir(char *denumire, char *compozitie):id(CONTORFIR++)
    {
        this->denumire=new char[strlen(denumire)+1];
        strcpy(this->denumire,denumire);
        this->compozitie=new char[strlen(compozitie)+1];
        strcpy(this->compozitie,compozitie);
        grosime=-1; // necompletata - exista grosimea 0 la fire
        metraj=0;
        gramaj=0;
        nrStoc=NULL;
        nrCulori=0;
        coduriCulori=NULL;
        lucrat=0;
    }

    // detaliile primite, in afara de categoria de grosime, care e calculata in interior pe baza informatiilor primite
    fir(char *denumire, char *compozitie, int metraj, int gramaj, int nrCulori, int *coduriCulori, int *nrStoc, double lucrat):id(CONTORFIR++)
    {
        this->denumire=new char[strlen(denumire)+1];
        strcpy(this->denumire,denumire);
        this->compozitie=new char[strlen(compozitie)+1];
        strcpy(this->compozitie,compozitie);

        this->metraj=metraj;
        this->gramaj=gramaj;

        float auxGrosime=1.0*this->metraj/this->gramaj; // valori standard internationale pentru categorii
        if(auxGrosime<1.0)
            this->grosime=6;
        else if(auxGrosime<1.30)
            this->grosime=5;
        else if(auxGrosime<2.30)
            this->grosime=4;
        else if(auxGrosime<3.00)
            this->grosime=3;
        else if(auxGrosime<4.00)
            this->grosime=2;
        else if(auxGrosime<6.00)
            this->grosime=1;
        else this->grosime=0;

        this->nrCulori=nrCulori;
        this->coduriCulori=new int[nrCulori];
        this->nrStoc=new int[nrCulori];
        for(int i=0; i<nrCulori; i++)
        {
            this->coduriCulori[i]=coduriCulori[i];
            this->nrStoc[i]=nrStoc[i];
        }
        this->lucrat=lucrat;
    }

    // cunosc toate detaliile despre fir - constructorul cu toti parametrii
    fir(char *denumire, char *compozitie, int grosime, int metraj, int gramaj, int nrCulori, int *coduriCulori, int *nrStoc, double lucrat):id(CONTORFIR++)
    {
        this->denumire=new char[strlen(denumire)+1];
        strcpy(this->denumire,denumire);
        this->compozitie=new char[strlen(compozitie)+1];
        strcpy(this->compozitie,compozitie);
        this->metraj=metraj;
        this->gramaj=gramaj;
        this->grosime=grosime;
        this->nrCulori=nrCulori;
        this->coduriCulori=new int[nrCulori];
        this->nrStoc=new int[nrCulori];
        for(int i=0; i<nrCulori; i++)
        {
            this->coduriCulori[i]=coduriCulori[i];
            this->nrStoc[i]=nrStoc[i];
        }
        this->lucrat=lucrat;
    }

    /// Copy Constructor
    fir(const fir &obj):id(obj.id)
    {
        if(obj.denumire!=NULL)
        {
            this->denumire=new char[strlen(obj.denumire)+1];
            strcpy(this->denumire,obj.denumire);
        }
        else this->denumire=NULL;

        if(obj.compozitie!=NULL)
        {
            this->compozitie=new char[strlen(obj.compozitie)+1];
            strcpy(this->compozitie,obj.compozitie);
        }
        else this->compozitie=NULL;

        this->metraj=obj.metraj;
        this->gramaj=obj.gramaj;
        this->grosime=obj.grosime;
        this->nrCulori=obj.nrCulori;
        if(this->nrCulori>0)
        {
            if(obj.coduriCulori!=NULL)
                this->coduriCulori=new int[obj.nrCulori];
            else this->coduriCulori=NULL;
            if(obj.nrStoc!=NULL)
                this->nrStoc=new int[obj.nrCulori];
            else this->nrStoc=NULL;
            if(obj.coduriCulori!=NULL && obj.nrStoc!=NULL)
                for(int i=0; i<obj.nrCulori; i++)
                {
                    this->coduriCulori[i]=obj.coduriCulori[i];
                    this->nrStoc[i]=obj.nrStoc[i];
                }
        }
        else
        {
            this->coduriCulori=NULL;
            this->nrStoc=NULL;
        }
        this->lucrat=obj.lucrat;
    }

    /// Operatorul =  - firul actual primeste detalii despre alt fir, dar isi pastreaza denumirea
    fir& operator = (const fir &obj)
    {
        if(this!=&obj)
        {
            // denumirea nu se modifica - firul actual va primi doar detaliile altui fir
            // (a se percepe ca un fel de "rebranding" al lui), dar cu alt id
            if(this->compozitie!=NULL)
                delete[] this->compozitie;
            if(this->coduriCulori!=NULL)
                delete[] this->coduriCulori;
            if(this->nrStoc!=NULL)
                delete[] this->nrStoc;

            if(obj.compozitie!=NULL)
            {
                this->compozitie=new char[strlen(obj.compozitie)+1];
                strcpy(this->compozitie,obj.compozitie);
            }
            else this->compozitie=NULL;

            this->metraj=obj.metraj;
            this->gramaj=obj.gramaj;
            this->grosime=obj.grosime;
            this->nrCulori=obj.nrCulori;
            if(obj.nrCulori>0)
            {
                if(obj.coduriCulori!=NULL)
                    this->coduriCulori=new int[obj.nrCulori];
                else this->coduriCulori=NULL;
                if(obj.nrStoc!=NULL)
                    this->nrStoc=new int[obj.nrCulori];
                else this->nrStoc=NULL;
                if(obj.coduriCulori!=NULL && obj.nrStoc!=NULL)
                    for(int i=0; i<obj.nrCulori; i++)
                    {
                        this->coduriCulori[i]=obj.coduriCulori[i];
                        this->nrStoc[i]=obj.nrStoc[i];
                    }
            }
            else
            {
                this->coduriCulori=NULL;
                this->nrStoc=NULL;
            }
            this->lucrat=obj.lucrat;
        }

        return *this;
    }

    /// Operatorul == - 2 fire sunt egale daca au aceeasi denumire, metraj, gramaj, lucrat
    bool operator == (const fir &obj)
    {
        bool egal=1;
        if(!((this->denumire==NULL && obj.denumire==NULL) || stricmp(this->denumire,obj.denumire)==0))
            egal=0;
        if(this->metraj!=obj.metraj)
            egal=0;
        if(this->gramaj!=obj.gramaj)
            egal=0;
        if(this->lucrat!=obj.lucrat)
            egal=0;
        return egal;
    }

    /// Operatorul < - un fir e mai mic daca are ratia metraj/gramaj mai mare decat celalalt (e mai subtire)
    bool operator < (const fir &obj)
    {
        float aux1, aux2;
        if(this->metraj>0 && this->gramaj>0)
        {
            if(obj.metraj>0 && obj.gramaj>0)
            {
                aux1=1.0*this->metraj/this->gramaj;
                aux2=1.0*obj.metraj/obj.gramaj;
                if(aux1>aux2)
                    return true;
            }
        }
        return false;

    }

    /// Operatorul <=
    bool operator <= (const fir &obj)
    {
        if(*this<obj || *this==obj)
            return true;
        return false;
    }

    /// Operatorul != - negarea lui ==
    bool operator != (const fir &obj)
    {
        return !(*this==obj);
    }

    /// Operatorul + - adauga la firul actual culorile celui de-al doilea si stocul lor
    fir operator + (const fir &obj)
    {
        fir copie=*this;
        int n=0, k=0;
        int v[200], w[200];
        if(copie.coduriCulori!=NULL && copie.nrStoc!=NULL && copie.nrCulori>0)
        {
            n=copie.nrCulori;
            for(int i=0; i<copie.nrCulori; i++)
            {
                v[i]=copie.coduriCulori[i];
                w[i]=copie.nrStoc[i];
            }
        }
        if(obj.coduriCulori!=NULL && obj.nrStoc!=NULL && obj.nrCulori>0)
        {
            for(int i=0; i<obj.nrCulori; i++)
            {
                bool gasit=0;
                for(int j=0; j<copie.nrCulori; i++)
                    if(v[j]==obj.coduriCulori[i])
                    {
                        w[j]=w[j]+obj.nrStoc[i];
                        gasit=1;
                    }
                if(gasit==0)
                {
                    v[copie.nrCulori+k]=obj.coduriCulori[i];
                    w[copie.nrCulori+k]=obj.nrStoc[i];
                    k++;
                }
            }
            n=copie.nrCulori+k;
        }
        if(copie.coduriCulori!=NULL)
            delete[] copie.coduriCulori;
        if(copie.nrStoc!=NULL)
            delete[] copie.nrStoc;
        if(n>0)
        {
            copie.nrCulori=n;
            copie.coduriCulori=new int[n];
            copie.nrStoc=new int[n];
            for(int i=0; i<n; i++)
            {
                copie.coduriCulori[i]=v[i];
                copie.nrStoc[i]=w[i];
            }
        }
        else
        {
            copie.coduriCulori=NULL;
            copie.nrStoc=NULL;
        }
        return copie;
    }

    /// Operatorul - - elimina din firul actual culorile celui de-al doilea si stocul lor
    fir operator - (const fir &obj)
    {
        fir copie=*this;
        if(copie.coduriCulori!=NULL && copie.nrStoc!=NULL && copie.nrCulori>0 &&
         obj.coduriCulori!=NULL && obj.nrStoc!=NULL && obj.nrCulori>0)
        {
            for(int i=0; i<obj.nrCulori; i++)
            {
                bool gasit=0;
                for(int j=0; j<copie.nrCulori; j++)
                    if(copie.coduriCulori[j]==obj.coduriCulori[i])
                        copie.nrStoc[j]=copie.nrStoc[j]-obj.nrStoc[i];
            }
            for(int i=0; i<copie.nrCulori; i++)
                if(copie.nrStoc[i]<0)
                    copie.nrStoc[i]=0;
        }

        return copie;
    }

    /// Operatorul ++ - ++ adauga o culoare si ii atribuie codurile 0 si stoc 0, urmand sa fie completata
    fir& operator ++ ()
    {
        if(this->nrCulori>0)
        {
            ++this->nrCulori;
            int aux1[this->nrCulori], aux2[this->nrCulori];
            for(int i=0; i<nrCulori-1; i++)
            {
                aux1[i]=coduriCulori[i];
                aux2[i]=nrStoc[i];
            }
            aux1[this->nrCulori-1]=0;
            aux2[this->nrCulori-1]=0;
            if(this->coduriCulori!=NULL)
                delete[] this->coduriCulori;
            if(this->nrStoc!=NULL)
                delete[] this->nrStoc;
            this->coduriCulori=new int[nrCulori];
            this->nrStoc=new int[nrCulori];
            for(int i=0; i<nrCulori; i++)
            {
                this->coduriCulori[i]=aux1[i];
                this->coduriCulori[i]=aux2[i];
            }
        }
        else
        {
            this->nrCulori=1;
            if(this->coduriCulori!=NULL)
                delete[] this->coduriCulori;
            if(this->nrStoc!=NULL)
                delete[] this->nrStoc;
            this->coduriCulori=new int[1];
            this->nrStoc=new int[1];
            this->coduriCulori[0]=0;
            this->nrStoc[0]=0;
        }
        return *this;
    }

    fir operator ++ (int)
    {
        fir copie=*this;
        ++(*this);
        return copie;
    }

    /// Operatorul -- - -- elimina ultima culoare din lista
    fir& operator -- ()
    {
        if(this->nrCulori>1)
        {
            --this->nrCulori;
            int aux1[this->nrCulori], aux2[this->nrCulori];
            for(int i=0; i<nrCulori; i++)
            {
                aux1[i]=coduriCulori[i];
                aux2[i]=nrStoc[i];
            }
            if(this->coduriCulori!=NULL)
                delete[] this->coduriCulori;
            if(this->nrStoc!=NULL)
                delete[] this->nrStoc;
            this->coduriCulori=new int[nrCulori];
            this->nrStoc=new int[nrCulori];
            for(int i=0; i<nrCulori; i++)
            {
                this->coduriCulori[i]=aux1[i];
                this->coduriCulori[i]=aux2[i];
            }
        }
        else
        {
            this->nrCulori=0;
            if(this->coduriCulori!=NULL)
                delete[] this->coduriCulori;
            if(this->nrStoc!=NULL)
                delete[] this->nrStoc;
            this->coduriCulori=NULL;
            this->nrStoc=NULL;
        }
        return *this;
    }

    fir operator -- (int)
    {
        fir copie=*this;
        --(*this);
        return copie;
    }

    /// Operatorul [] - imi returneaza codul de culoare de pe pozitia index
    int operator [] (int index)
    {
        if(index>=0 && index<this->nrCulori && this->coduriCulori!=NULL)
            return coduriCulori[index];
        return -1;
    }

    /// Operator cast
    operator string() // implicit
    {
        string s="";

        s=s+"Denumire: ";
        if(this->denumire!=NULL)
        {
            s=s+this->denumire;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        s=s+"Compozitie: ";
        if(this->compozitie!=NULL)
        {
            s=s+this->compozitie;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        return s;
    }

    operator string() const // explicit
    {
        string s="";

        s=s+"Denumire: ";
        if(this->denumire!=NULL)
        {
            s=s+this->denumire;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        s=s+"Compozitie: ";
        if(this->compozitie!=NULL)
        {
            s=s+this->compozitie;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        return s;
    }

    /// Functionalitate - verifica daca culoarea cu codul k din fir exista sau daca e pe stoc
    /// val returnata: 2-pe stoc, 1-nu e pe stoc, 0-nu exista culoarea
    int culoareValabila(int k)
    {
        int val=2; // e pe stoc
        bool gasit=0;
        if(this->nrCulori==0)
            val=0; // nu exista
        else
        {
            if(this->coduriCulori==NULL)
                val=0; // nu exista
            else
            {
                if(this->nrStoc==NULL)
                    val=0; // nu exista
                else
                {
                    for(int i=0; i<this->nrCulori; i++)
                        if(this->coduriCulori[i]==k)
                        {
                            gasit=1;
                            if(this->nrStoc[i]==0)
                            {
                                i=this->nrCulori+1;
                                val=1; // nu e pe stoc
                            }
                        }
                    if(gasit==0)
                        val=0;
                }
            }
        }
        return val;
    }

    /// Functiile de afisare si citire
    // void citire()
    // {
    //     char aux[200]; //declarat mai mare deoarece compozitia poate contine mai mult text
    //     cout<<"Introduceti urmatoarele informatii despre fir: "<<endl;
    //     cout<<"Denumire: ";
    //     cin.getline(aux,200);
    //     while(strcmp(aux,"")==0)
    //         cin.getline(aux,200);
    //     if(this->denumire!=NULL)
    //         delete[] this->denumire;
    //     if(aux!=NULL)
    //     {
    //         this->denumire=new char[strlen(aux)+1];
    //         strcpy(this->denumire, aux);
    //     }
    //     else this->denumire=NULL;
    //     cout<<"Compozitie: ";
    //     cin.getline(aux,200);
    //     if(this->compozitie!=NULL)
    //         delete[] this->compozitie;
    //     if(aux!=NULL)
    //     {
    //         this->compozitie=new char[strlen(aux)+1];
    //         strcpy(this->compozitie, aux);
    //     }
    //     else this->compozitie=NULL;
    //     cout<<"Metraj: ";
    //     cin>>this->metraj;
    //     cout<<"Gramaj: ";
    //     cin>>this->gramaj;
    //     cout<<"Doriti introducerea manuala sau automata a categoriei de grosime a firului? Introduceti cifra corespunzatoare raspunsului."<<endl;
    //     cout<<"1. Manuala     2. Automata"<<endl<<"Introduceti optiunea: ";
    //     int val;
    //     cin>>val;
    //     while(val!=1 && val!=2)
    //     {
    //         cout<<"Valoarea introdusa nu corespunde selectiei. Incercati din nou. "<<endl<<"Introduceti optiunea: ";
    //         cin>>val;
    //     }
    //     if(val==1)
    //     {
    //         cout<<"Grosime: ";
    //         cin>>this->grosime;
    //     }
    //     else
    //     {
    //         /// programul calculeaza pe baza normelor internationale
    //         float auxGrosime=1.0*this->metraj/this->gramaj; // valori standard internationale pentru categorii
    //         if(auxGrosime<1.0)
    //             this->grosime=6;
    //         else if(auxGrosime<1.30)
    //             this->grosime=5;
    //         else if(auxGrosime<2.30)
    //             this->grosime=4;
    //         else if(auxGrosime<3.00)
    //             this->grosime=3;
    //         else if(auxGrosime<4.00)
    //             this->grosime=2;
    //         else if(auxGrosime<6.00)
    //             this->grosime=1;
    //         else this->grosime=0;
    //         cout<<"Grosime: "<<this->grosime<<" (completat automat)"<<endl;
    //     }
    //     cout<<"Numarul de culori disponibile: ";
    //     cin>>this->nrCulori;
    //     if(this->nrCulori>0)
    //     {
    //         if(this->coduriCulori!=NULL)
    //             delete[] this->coduriCulori;
    //         if(this->nrStoc!=NULL)
    //             delete[] this->nrStoc;
    //         this->coduriCulori=new int[this->nrCulori];
    //         this->nrStoc=new int[this->nrCulori];
    //         cout<<"Introduceti perechile de numere de forma *codCuloare* *stocCuloare*: "<<endl;
    //         for(int i=0; i<this->nrCulori; i++)
    //         {
    //             cin>>this->coduriCulori[i];
    //             cin>>this->nrStoc[i];
    //         }
    //     }
    //     else
    //     {
    //         this->coduriCulori=NULL;
    //         this->nrStoc=NULL;
    //     }
    //     cout<<"Dimensiunea recomandata a andrelelor/crosetei de lucru: ";
    //     cin>>this->lucrat;
    //     cout<<endl<<"Ati introdus cu succes informatiile despre fir"<<endl;
    // }

    // void afisare()
    // {
    //     cout<<"Denumire: "<<this->denumire<<endl;
    //     cout<<"Compozitie: "<<this->compozitie<<endl;
    //     cout<<"Cod Fir: "<<this->id<<endl;
    //     cout<<"Categorie Grosime: "<<this->grosime<<endl;
    //     cout<<"Metraj: "<<this->metraj<<endl;
    //     cout<<"Gramaj per ghem: "<<this->gramaj<<endl;
    //     cout<<"Disponibilitate culori:"<<endl;
    //     if(this->nrCulori>0)
    //     {
    //         for(int i=0; i<this->nrCulori; i++)
    //             cout<<this->coduriCulori[i]<<" -> "<<this->nrStoc[i]<<"; ";
    //         cout<<endl;
    //     }
    //     else cout<<"Nu exista culori disponibile"<<endl;
    //     cout<<"Marime andrele/croseta: "<<this->lucrat;
    // }

    /// Getters pt toate variabilele
    int getId()
    {
        return this->id;
    }

    const char* getDenumire()
    {
        return this->denumire;
    }

    const char* getCompozitie()
    {
        return this->compozitie;
    }

    int getid()
    {
        return this->id;
    }

    int getGrosime()
    {
        return this->grosime;
    }

    int getMetraj()
    {
        return this->metraj;
    }

    int getGramaj()
    {
        return this->gramaj;
    }

    int getNrCulori()
    {
        return this->nrCulori;
    }

    const int* getCoduriCulori()
    {
        return this->coduriCulori;
    }

    const int* getNrStoc()
    {
        return this->nrStoc;
    }

    double getLucrat()
    {
        return this->lucrat;
    }

    /// Setters pt toate variabilele
    void setDenumire(char* denumire)
    {
        if(this->denumire!=NULL)
            delete[] this->denumire;
        if(denumire!=NULL)
        {
            this->denumire=new char[strlen(denumire)+1];
            strcpy(this->denumire, denumire);
        }
        else this->denumire=NULL;
    }

    void setCompozitie(char* compozitie)
    {
        if(this->compozitie!=NULL)
            delete[] this->compozitie;
        if(compozitie!=NULL)
        {
            this->compozitie=new char[strlen(compozitie)+1];
            strcpy(this->compozitie, compozitie);
        }
        else this->compozitie=NULL;
    }

    void setGrosime(int grosime)
    {
        this->grosime=grosime;
    }

    void setMetraj(int metraj)
    {
        this->metraj=metraj;
    }

    void setGramaj(int gramaj)
    {
        this->gramaj=gramaj;
    }

    void setNrCulori(int nrCulori)
    {
        this->nrCulori=nrCulori;
    }

    void setCoduriCulori(int* coduriCulori)
    {
        if(this->coduriCulori!=NULL)
            delete[] this->coduriCulori;
        this->coduriCulori=new int[this->nrCulori];
        for(int i=0; i<this->nrCulori; i++)
            this->coduriCulori[i]=coduriCulori[i];
    }

    void setNrStoc(int* nrStoc)
    {
        if(this->nrStoc!=NULL)
            delete[] this->nrStoc;
        this->nrStoc=new int[this->nrCulori];
        for(int i=0; i<this->nrCulori; i++)
            this->nrStoc[i]=nrStoc[i];
    }

    void setLucrat(double lucrat)
    {
        this->lucrat=lucrat;
    }

    friend ostream& operator << (ostream&, const fir&);
    friend istream& operator >> (istream&, fir&);

    /// Destructor
    ~fir()
    {
        if(this->denumire!=NULL)
            delete[] this->denumire;
        if(this->compozitie!=NULL)
            delete[] this->compozitie;
        if(this->coduriCulori!=NULL)
            delete[] this->coduriCulori;
        if(this->nrStoc!=NULL)
            delete[] this->nrStoc;
    }
};

class comanda;
class produs
{
private:
    static int CONTORPRODUS;
    const int id;
    char* nume;
    int nrFire; // id - daca e 0, nu are cod (0 nu e considerat cod de produs), daca > 0, are cod
    int *fire; // coduri de la fire
    float pret;
    char marime, tehnica; // tehnica: T-tricotat, C-crosetat, A-ambele

public:

    /// Constructori
    produs():id(CONTORPRODUS++)
    {
        nume=NULL;
        nrFire=0;
        fire=NULL;
        pret=0;
        marime='X';
        tehnica='X';
    }

    // despre produs cunosc doar numele si codul de produs
    produs(char *nume, int id):id(CONTORPRODUS++)
    {
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);

        nrFire=0;
        fire=NULL;
        pret=0;
        marime='X';
        tehnica='X';
    }

    // un produs in proiectare care nu are nume, cod, marime si pret, se cunosc doar detalii despre cum va fi lucrat
    produs(int nrFire, int *fire, char tehnica):id(CONTORPRODUS++)
    {
        this->nrFire=nrFire;
        this->fire=new int[nrFire];
        for(int i=0; i<nrFire; i++)
            this->fire[i]=fire[i];
        this->tehnica=tehnica;

        nume=NULL;
        pret=0;
        marime='X';
    }

    // produsul nu are *inca* o denumire, dar sunt cunosctute celelalte detalii despre el
    produs(int nrFire, int *fire, float pret, char marime, char tehnica):id(CONTORPRODUS++)
    {
        this->nume=NULL;
        this->nrFire=nrFire;
        this->fire=new int[nrFire];
        for(int i=0; i<nrFire; i++)
            this->fire[i]=fire[i];
        this->pret=pret;
        this->marime=marime;
        this->tehnica=tehnica;
    }

    // cunosc toate detaliile despre produs - constructorul cu toti parametrii
    produs(char *nume, int nrFire, int *fire, float pret, char marime, char tehnica):id(CONTORPRODUS++)
    {
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);
        this->nrFire=nrFire;
        this->fire=new int[nrFire];
        for(int i=0; i<nrFire; i++)
            this->fire[i]=fire[i];
        this->pret=pret;
        this->marime=marime;
        this->tehnica=tehnica;
    }

    /// Copy Constructor
    produs(const produs &obj):id(obj.id)
    {
        if(obj.nume!=NULL)
        {
            this->nume=new char[strlen(obj.nume)+1];
            strcpy(this->nume,obj.nume);
        }
        else this->nume=NULL;
        this->nrFire=obj.nrFire;
        if(obj.nrFire>0)
        {
            this->fire=new int[obj.nrFire];
            if(obj.fire!=NULL)
                for(int i=0; i<obj.nrFire; i++)
                    this->fire[i]=obj.fire[i];
        }
        else this->fire=NULL;
        this->pret=obj.pret;
        this->marime=obj.marime;
        this->tehnica=obj.tehnica;


    }

    /// Operatorul =  - produsul actual isi pastreaza numele
    produs& operator = (const produs &obj)
    {
        if(this != &obj)
        {
            if(fire!=NULL)
                delete[] fire;

            this->nrFire=obj.nrFire;
            if(obj.nrFire>0)
            {

                if(obj.fire!=NULL)
                {
                    this->fire=new int[obj.nrFire];
                    for(int i=0; i<obj.nrFire; i++)
                        this->fire[i]=obj.fire[i];
                }

            }
            else this->fire=NULL;

            this->pret=obj.pret;
            this->marime=obj.marime;
            this->tehnica=obj.tehnica;
        }
        return *this;
    }

    /// Operatorul == - 2 produse sunt egale daca au acelasi nume, acelasi numar de fire, aceleasi fire, si aceeasi tehnica
    bool operator == (const produs &obj)
    {
        bool egal=1;
        if(!((this->nume==NULL && obj.nume==NULL) || stricmp(this->nume,obj.nume)==0))
            egal=0;
        if(this->nrFire!=obj.nrFire)
            egal=0;
        else
        {
            if(!(this->fire==NULL && obj.fire==NULL))
                for(int i=0; i<this->nrFire; i++)
                {
                    bool gasit=0;
                    for(int j=0; j<obj.nrFire; i++)
                        if(this->fire[i]==obj.fire[i])
                            gasit=1;
                    if(gasit==0)
                        egal=0;
                }
        }
        return egal;
    }

    /// Operatorul < - e mai mic daca are pret mai mic
    bool operator < (const produs &obj)
    {
        if(this->pret<obj.pret)
            return true;
        return false;
    }

    /// Operatorul <=
    bool operator <= (const produs &obj)
    {
        if(*this<obj || *this==obj)
            return true;
        return false;
    }

    /// Operatorul != - negarea pentru ==
    bool operator != (const produs &obj)
    {
        return !(*this==obj);
    }

    /// Operatorul + - adaug firele de la un produs la alt produs
    produs operator + (const produs &obj)
    {
        produs copie=*this;
        bool adaugat=0;
        int n=0,k=0, v[100];
        if(copie.fire!=NULL && obj.fire!=NULL)
        {
            if(copie.fire!=NULL)
            {
                n=copie.nrFire;
                if(copie.fire!=NULL)
                    for(int i=0; i<copie.nrFire; i++)
                    {
                        v[i]=copie.fire[i];
                        adaugat=1;
                        cout<<"sunt aici";
                    }
            }
            if(obj.fire!=NULL)
            {
                for(int i=0; i<obj.nrFire; i++)
                {
                    bool gasit=0;
                    if(copie.fire!=NULL)
                        for(int j=0; j<copie.nrFire; i++)
                            if(v[j]==obj.fire[i])
                                gasit=1;
                    if(gasit==0 && copie.fire!=NULL)
                    {
                        v[copie.nrFire+k]=obj.fire[i];
                        k++;
                        adaugat=1;
                    }
                }
                n=n+k;
            }
        }
        if(copie.fire!=NULL)
            delete[] copie.fire;
        if(n>0 && adaugat==1)
        {
            copie.nrFire=n;
            copie.fire=new int[n];
            for(int i=0; i<n; i++)
                copie.fire[i]=v[i];
        }
        else
        {
            copie.fire=NULL;
            copie.nrFire=copie.nrFire+obj.nrFire;
        }

        return copie;
    }

    /// Operatorul - - elimin firele de la un produs din alt produs
    produs operator - (const produs &obj)
    {
        produs copie=*this;
        int v[100], k=0;
        if(copie.nrFire>0 && obj.nrFire>0 && copie.fire!=NULL && copie.fire!=NULL)
        {
            for(int i=0; i<obj.nrFire; i++)
                for(int j=0; j<copie.nrFire; j++)
                    if(copie.fire[j]==obj.fire[i])
                        copie.fire[j]=-1;
            for(int i=0; i<copie.nrFire; i++)
                if(copie.fire[i]!=-1)
                {
                    v[k]=copie.fire[i];
                    k++;
                }
            if(k>0)
            {
                delete[] copie.fire;
                copie.fire=new int[k];
                copie.nrFire=k;
                for(int i=0; i<k; i++)
                    copie.fire[i]=v[i];
            }
        }
        return copie;
    }

    /// Operatorul ++ - ++ creste pretul cu 10%
    produs& operator ++ ()
    {
        this->pret=this->pret*1.1;
        return *this;
    }

    produs operator ++ (int)
    {
        produs copie=*this;
        ++(*this);
        return copie;
    }

    /// Operatorul -- - -- scade pretul cu 10%
    produs& operator -- ()
    {
        this->pret=this->pret*0.9;
        return *this;
    }

    produs operator -- (int)
    {
        produs copie=*this;
        --(*this);
        return copie;
    }

    /// Operatorul [] - afiseaza firul de pe pozitia index
    int operator [] (int index)
    {
        if(index>=0 && index<this->nrFire && this->fire!=NULL)
            return fire[index];
        return -1;
    }

    /// Operatorul cast
    operator string() //implicit
    {
        string s="";

        s=s+"Nume produs: ";
        if(this->nume!=NULL)
        {
            s=s+this->nume;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        s=s+"Marimea: ";
        if((int)this->marime!=0 && strchr("smlSML",this->marime))
        {
            s=s+this->marime;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        return s;
    }

    operator string() const //explicit
    {
        string s="";

        s=s+"Nume produs: ";
        if(this->nume!=NULL)
        {
            s=s+this->nume;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        s=s+"Marimea: ";
        if((int)this->marime!=0 &&  strchr("smlSML",this->marime))
        {
            s=s+this->marime;
            s=s+"; ";
        }
        else s=s+"Nespecificat; ";

        return s;
    }

    /// Functionalitate - afiseaza pretul dupa TVA
    float cuTVA()
    {
        return this->pret*1.19;
    }

    /// Functii pentru afisare si citire - STATIC CODUL DE PRODUS
    // void citire()
    // {
    //     char aux[100];
    //     cout<<"Introduceti urmatoarele date despre produs: "<<endl;
    //     cout<<"Nume produs: ";
    //     cin.getline(aux,100);
    //     while(strcmp(aux,"")==0)
    //         cin.getline(aux, 100);
    //     if(this->nume!=NULL)
    //         delete[] this->nume;
    //     if(aux!=NULL)
    //     {
    //         this->nume=new char[strlen(aux)+1];
    //         strcpy(this->nume,aux);
    //     }
    //     else this->nume=NULL;

    //     cout<<"Numarul de fire utilizate: ";
    //     cin>>this->nrFire;
    //     if(this->fire!=NULL)
    //         delete[] this->fire;
    //     if(this->nrFire!=0)
    //     {
    //         this->fire=new int[this->nrFire];
    //         cout<<"Introduceti codurile firelor utizilate: ";
    //         for(int i=0; i<this->nrFire; i++)
    //             cin>>this->fire[i];
    //     }
    //     else this->fire=NULL;

    //     cout<<"Pretul produsului: ";
    //     cin>>this->pret;
    //     cout<<"Marime produs (de forma S,M,L): ";
    //     cin>>this->marime;
    //     cout<<"Tehnica executarii (T-tricotat, C-crosetat, A-ambele): ";
    //     cin>>this->tehnica;

    // }

    // void afisare()
    // {
    //     cout<<"Nume produs: "<<this->nume<<endl;
    //     cout<<"Cod produs: "<<this->id<<endl;
    //     cout<<"Numar fire folosite: "<<this->nrFire<<endl;
    //     cout<<"Coduri fire utilizate: ";
    //     for(int i=0; i<this->nrFire; i++)
    //         cout<<this->fire[i]<<" ";
    //     cout<<endl;
    //     cout<<"Pret: "<<this->pret<<endl;
    //     cout<<"Marime: "<<this->marime<<endl;
    //     if(this->tehnica=='T')
    //         cout<<"Tehnica: tricotat"<<endl;
    //     else if(this->tehnica=='C')
    //         cout<<"Tehnica: crosetat"<<endl;
    //     else cout<<"Tehnica: crosetat si tricotat"<<endl;
    // }

    /// Getters pt toate variabilele
    int getId()
    {
        return this->id;
    }

    const char* getNume()
    {
        return this->nume;
    }

    int getid()
    {
        return this->id;
    }

    int getNrFire()
    {
        return this->nrFire;
    }

    const int* getFire()
    {
        return this->fire;
    }

    float getPret()
    {
        return this->pret;
    }

    char getMarime()
    {
        return this->marime;
    }

    char getTehnica()
    {
        return this->tehnica;
    }

    /// Setters pt toate variabilele
    void setNume(char* nume)
    {
        if(this->nume!=NULL)
            delete[] this->nume;
        if(nume!=NULL)
        {
            this->nume=new char[strlen(nume)+1];
            strcpy(this->nume, nume);
        }
        else this->nume=NULL;
    }

    void setNrFire(int nrFire)
    {
        this->nrFire=nrFire;
    }

    void setFire(int* fire)
    {
        if(this->fire!=NULL)
            delete[] this->fire;
        this->fire=new int[this->nrFire];
        for(int i=0; i<this->nrFire; i++)
            this->fire[i]=fire[i];
    }

    void setPret(float pret)
    {
        this->pret=pret;
    }

    void setMarime(char marime)
    {
        this->marime=marime;
    }

    void setTehnica(char tehnica)
    {
        this->tehnica=tehnica;
    }

    //friend class comanda;
    friend ostream& operator << (ostream&, const produs&);
    friend istream& operator >> (istream&, produs&);
    friend comanda operator + (const produs&);
    friend comanda operator + (const produs&,const comanda&);

    /// Destructor
    ~produs()
    {
        if(this->nume!=NULL)
            delete[] this->nume;
        if(this->fire!=NULL)
            delete[] this->fire;
    }
};

class comanda
{
private:
    static int CONTORCOMANDA;
    const int id;
    client persoana;
    int nrProduse;
    int *coduriProduse;
    float *preturiProduse;
    float pretTotal;
    char *stare; //in progress, done, delivered, not started, etc

public:

    /// Constructori

    // constructorul fara parametri
    comanda():id(CONTORCOMANDA++)
    {
        this->nrProduse=0;
        this->coduriProduse=NULL;
        this->preturiProduse=NULL;
        this->pretTotal=0;
        this->stare=NULL;
    }

    // constructor cu client, vectorii de coduri de produse, si preturi de produse
    comanda(const client &persoana, int nrProduse, int *coduriProduse, float *preturiProduse):id(CONTORCOMANDA++)
    {
        this->persoana=persoana;
        this->nrProduse=nrProduse;
        this->coduriProduse=new int[nrProduse];
        this->preturiProduse=new float[nrProduse];
        this->pretTotal=0;
        for(int i=0; i<nrProduse; i++)
        {
            this->coduriProduse[i]=coduriProduse[i];
            this->preturiProduse[i]=preturiProduse[i];
            this->pretTotal=this->pretTotal+this->preturiProduse[i];
        }
        this->stare=NULL;
    }

    // constructor cu client si numar de produse
    comanda(const client &persoana, int nrProduse):id(CONTORCOMANDA++)
    {
        this->persoana=persoana;
        this->nrProduse=nrProduse;
        this->coduriProduse=new int[nrProduse];
        this->preturiProduse=new float[nrProduse];
        this->pretTotal=0;
        this->stare=NULL;
    }

    // cunosc toate detaliile despre o comanda - constructorul cu toti parametrii
    comanda(const client &persoana, int nrProduse, int *coduriProduse, float *preturiProduse, float pretTotal, char *stare):id(CONTORCOMANDA++)
    {
        this->persoana=persoana;
        this->nrProduse=nrProduse;
        this->coduriProduse=new int[nrProduse];
        this->preturiProduse=new float[nrProduse];
        for(int i=0; i<nrProduse; i++)
        {
            this->coduriProduse[i]=coduriProduse[i];
            this->preturiProduse[i]=preturiProduse[i];
        }
        this->pretTotal=pretTotal;
        this->stare=NULL;
    }

    /// Copy Constructor
    comanda(const comanda &obj):id(obj.id)
    {
        this->persoana=obj.persoana;
        this->nrProduse=obj.nrProduse;
        if(obj.nrProduse>0 && obj.coduriProduse!=NULL && obj.preturiProduse!=NULL)
        {
            this->coduriProduse=new int[obj.nrProduse];
            this->preturiProduse=new float[obj.nrProduse];
            for(int i=0; i<obj.nrProduse; i++)
            {
                this->coduriProduse[i]=obj.coduriProduse[i];
                this->preturiProduse[i]=obj.preturiProduse[i];
            }
        }
        else
        {
            this->coduriProduse=NULL;
            this->preturiProduse=NULL;
        }
        this->pretTotal=obj.pretTotal;
        if(obj.stare!=NULL)
            {
                this->stare=new char[strlen(obj.stare)+1];
                strcpy(this->stare,obj.stare);
            }
        else this->stare=NULL;
    }

    /// Operatorul =  - comanda actuala primeste datele altei comenzi
    comanda& operator = (const comanda &obj)
    {
        if(this != &obj)
        {
            if(this->coduriProduse != NULL) // sterg pointerii din obiectul deja existent
                delete[] this->coduriProduse;
            if(this->preturiProduse != NULL)
                delete[] this->preturiProduse;
            if(this->stare != NULL)
                delete[] this->stare;

            // this->persoana RAMANE NESCHIMBATA, e vorba de o alta persoana care comanda
            this->nrProduse=obj.nrProduse;
            if(obj.nrProduse>0 && obj.coduriProduse!=NULL && obj.preturiProduse!=NULL)
            {
                this->coduriProduse=new int[obj.nrProduse];
                this->preturiProduse=new float[obj.nrProduse];
                for(int i=0; i<nrProduse; i++)
                {
                    this->coduriProduse[i]=obj.coduriProduse[i];
                    this->preturiProduse[i]=obj.preturiProduse[i];
                }
            }
            else
            {
                this->coduriProduse=NULL;
                this->preturiProduse=NULL;
            }
            this->pretTotal=obj.pretTotal;
            if(obj.stare!=NULL)
            {
                this->stare=new char[strlen(obj.stare)+1];
                strcpy(this->stare,obj.stare);
            }
            else this->stare=NULL;
        }
        return *this;
    }

    /// Operatorul == - 2 comenzi sunt egale daca au aceeasi persoana, acelasi nr de produse, acelasi pret, si aceleasi coduri de produse
    bool operator == (const comanda &obj)
    {
        bool egal=1;
        if(this->persoana!=obj.persoana)
            egal=0;
        if(this->nrProduse!=obj.nrProduse)
            egal=0;
        else
        {
            for(int i=0; i<nrProduse; i++)
                if(this->coduriProduse[i]!=obj.coduriProduse[i])
                    egal=0;
        }
        if(this->pretTotal!=obj.pretTotal)
            egal=0;
        return egal;
    }

    /// Operatorul != - negarea pentru ==
    bool operator != (const comanda &obj)
    {
        return !(*this==obj);
    }

    /// Operatorul < - e mai mic daca are nr mai mic de produse
    bool operator < (const comanda &obj)
    {
        if(this->nrProduse<obj.nrProduse)
            return true;
        return false;
    }

    /// Operatorul <= - nr mai mic sau egal de produse
    bool operator <= (const comanda &obj)
    {
        if(this->nrProduse<=obj.nrProduse)
            return true;
        return false;
    }

    /// Operatorul + - adauga produsele de la alta comanda aici
    comanda operator + (const comanda &obj)
    {
        comanda copie=*this;
        int n=0, k=0;
        int v[200];
        float w[200];
        bool adaugat=0;
        copie.pretTotal=0;
        if(copie.coduriProduse!=NULL && copie.preturiProduse!=NULL)
        {
            n=copie.nrProduse;
            for(int i=0; i<copie.nrProduse; i++)
            {
                v[i]=copie.coduriProduse[i];
                w[i]=copie.preturiProduse[i];
                adaugat=1;
            }
            if(obj.coduriProduse!=NULL && obj.preturiProduse!=NULL)
            {
                for(int i=0; i<obj.nrProduse; i++)
                {
                    bool gasit=0;
                    for(int j=0; j<copie.nrProduse; i++)
                        if(v[j]==obj.coduriProduse[i])
                        {
                            w[j]=w[j]+obj.preturiProduse[i];
                            gasit=1;
                        }
                    if(gasit==0)
                    {
                        v[copie.nrProduse+k]=obj.coduriProduse[i];
                        w[copie.nrProduse+k]=obj.preturiProduse[i];
                        k++;
                        adaugat=1;
                    }
                }
                n=copie.nrProduse+k;
            }
        }
        if(copie.coduriProduse!=NULL)
            delete[] copie.coduriProduse;
        if(copie.preturiProduse!=NULL)
            delete[] copie.preturiProduse;
        if(n>0  && adaugat==1)
        {
            copie.nrProduse=n;
            copie.coduriProduse=new int[n];
            copie.preturiProduse=new float[n];
            for(int i=0; i<n; i++)
            {
                copie.coduriProduse[i]=v[i];
                copie.preturiProduse[i]=w[i];
                copie.pretTotal=copie.pretTotal+w[i];
            }
        }
        else
        {
            copie.coduriProduse=NULL;
            copie.preturiProduse=NULL;
            copie.nrProduse=copie.nrProduse+obj.nrProduse;
        }
        return copie;
    }

    /// Operatorul - - elimina produsele gasite in alta comanda de aici
    comanda operator - (const comanda &obj)
    {
        comanda copie=*this;
        int v[100], k=0;
        float w[100], s=0;
        if(copie.nrProduse>0 && obj.nrProduse>0 && copie.coduriProduse!=NULL && obj.coduriProduse!=NULL
        && copie.preturiProduse!=NULL && obj.preturiProduse!=NULL)
        {
            for(int i=0; i<obj.nrProduse; i++)
                for(int j=0; j<copie.nrProduse; j++)
                    if(copie.coduriProduse[j]==obj.coduriProduse[i])
                    {
                        copie.coduriProduse[j]=-1;
                        copie.preturiProduse[j]=-1;
                    }
            for(int i=0; i<copie.nrProduse; i++)
                if(copie.coduriProduse[i]!=-1)
                {
                    v[k]=copie.coduriProduse[i];
                    w[k]=copie.preturiProduse[i];
                    s=s+copie.preturiProduse[i];
                    k++;
                }
            if(k>0)
            {
                delete[] copie.coduriProduse;
                delete[] copie.preturiProduse;
                copie.coduriProduse=new int[k];
                copie.preturiProduse=new float[k];
                copie.nrProduse=k;
                for(int i=0; i<k; i++)
                {
                    copie.coduriProduse[i]=v[i];
                    copie.preturiProduse[i]=w[i];
                }
            }
            copie.pretTotal=s;
        }
        return copie;
    }

    /// Operatorul ++ - adauga un produs la comanda, dar e initializat cu
    comanda& operator ++ ()
    {
        if(this->nrProduse>0)
        {
            ++this->nrProduse;
            int aux1[this->nrProduse];
            float aux2[this->nrProduse];
            for(int i=0; i<nrProduse-1; i++)
            {
                aux1[i]=coduriProduse[i];
                aux2[i]=preturiProduse[i];
            }
            aux1[this->nrProduse-1]=0;
            aux2[this->nrProduse-1]=0;
            if(this->coduriProduse!=NULL)
                delete[] this->coduriProduse;
            if(this->preturiProduse!=NULL)
                delete[] this->preturiProduse;
            this->coduriProduse=new int[nrProduse];
            this->preturiProduse=new float[nrProduse];
            for(int i=0; i<nrProduse; i++)
            {
                this->coduriProduse[i]=aux1[i];
                this->coduriProduse[i]=aux2[i];
            }
        }
        else
        {
            this->nrProduse=1;
            if(this->coduriProduse!=NULL)
                delete[] this->coduriProduse;
            if(this->preturiProduse!=NULL)
                delete[] this->preturiProduse;
            this->coduriProduse=new int[1];
            this->preturiProduse=new float[1];
            this->coduriProduse[0]=0;
            this->preturiProduse[0]=0;
        }
        return *this;
    }

    comanda operator ++ (int)
    {
        comanda copie=*this;
        ++(*this);
        return copie;
    }

    /// Operatorul -- - -- elimina ultimul produs din comanda;
    comanda& operator -- ()
    {
        if(this->nrProduse>1)
        {
            --this->nrProduse;
            int aux1[this->nrProduse], aux2[this->nrProduse];
            for(int i=0; i<nrProduse; i++)
            {
                aux1[i]=coduriProduse[i];
                aux2[i]=preturiProduse[i];
            }
            if(this->coduriProduse!=NULL)
                delete[] this->coduriProduse;
            if(this->preturiProduse!=NULL)
            {
                this->pretTotal-=this->preturiProduse[nrProduse];
                delete[] this->preturiProduse;
            }
            this->coduriProduse=new int[nrProduse];
            this->preturiProduse=new float[nrProduse];
            for(int i=0; i<nrProduse; i++)
            {
                this->coduriProduse[i]=aux1[i];
                this->coduriProduse[i]=aux2[i];
            }
        }
        else
        {
            this->nrProduse=0;
            if(this->coduriProduse!=NULL)
                delete[] this->coduriProduse;
            if(this->preturiProduse!=NULL)
                delete[] this->preturiProduse;
            if(this->stare!=NULL)
                delete[] this->stare;
            this->coduriProduse=NULL;
            this->preturiProduse=NULL;
            this->stare=NULL;
            this->pretTotal=0;
        }
        return *this;
    }

    comanda operator -- (int)
    {
        comanda copie=*this;
        --(*this);
        return copie;
    }

    /// Operatorul [] - afiseaza codul produsului de pe pozitia index
    int operator [] (int index)
    {
        if(index>=0 && index<this->nrProduse && this->coduriProduse)
            return this->coduriProduse[index];
        return -1;
    }

    /// Operatorul cast
    operator int() // implicit
    {
        return this->id;
    }

    operator int() const // explicit
    {
        return this->id;
    }

    /// Suma cu un produs - adaug produsul IN DREAPTA
    comanda operator + (produs obj)
    {
        comanda copie=*this;
        if(copie.nrProduse>0)
        {
            int n=copie.nrProduse;
            if(copie.coduriProduse!=NULL)
            {
                int v[200], val;
                for(int i=0; i<n; i++)
                    v[i]=copie.coduriProduse[i];
                v[copie.nrProduse]=obj.getid();
                delete[] copie.coduriProduse;
                copie.coduriProduse=new int[copie.nrProduse+1];
                for(int i=0; i<copie.nrProduse+1; i++)
                    copie.coduriProduse[i]=v[i];
            }
            else copie.coduriProduse=new int[copie.nrProduse=1];
            if(copie.preturiProduse!=NULL)
            {
                float w[200];
                for(int i=0; i<n; i++)
                    w[i]=copie.preturiProduse[i];
                w[copie.nrProduse]=obj.getPret();
                delete[] copie.preturiProduse;
                copie.preturiProduse=new float[copie.nrProduse+1];
                for(int i=0; i<copie.nrProduse+1; i++)
                    copie.preturiProduse[i]=w[i];
                copie.pretTotal=copie.pretTotal+obj.getPret();
            }
            else copie.preturiProduse=new float[copie.nrProduse=1];
            ++copie.nrProduse;
        }
        else
        {
            if(copie.coduriProduse!=NULL)
                delete[] copie.coduriProduse;
            if(copie.preturiProduse!=NULL)
                delete[] copie.preturiProduse;
            copie.nrProduse=1;
            copie.coduriProduse=new int[1];
            copie.preturiProduse=new float[1];
            copie.coduriProduse[0]=obj.getid();
            copie.preturiProduse[0]=obj.getPret();
            copie.pretTotal=obj.getPret();
        }
        return copie;
    }

    /// Functionalitate - codul produsului cel mai scump, daca exista produse, -1 altfel
    int scump()
    {
        float pretMax=0;
        int codMax=0;
        if(this->nrProduse>0 && this->coduriProduse!=NULL && this->preturiProduse!=NULL)
        {
            for(int i=0; i<this->nrProduse; i++)
                if(this->preturiProduse[i]>pretMax)
                {
                    pretMax=this->preturiProduse[i];
                    codMax=this->coduriProduse[i];
                }
        }
        if(codMax==0)
            return -1; // nu am gasit niciun produs valid
        return codMax;
    }

    /// Functii de afisare si citire
    // void citire()
    // {
    //     char aux[100];
    //     cout<<"Introduceti urmatoarele detalii despre comanda: "<<endl<<endl;
    //     /// primul va fi afisat id-ul
    //     cin>>this->persoana;
    //     cout<<"Numar produse comanda: ";
    //     cin>>this->nrProduse;
    //     if(this->coduriProduse!=NULL)
    //         delete[] this->coduriProduse;
    //     if(this->nrProduse!=0)
    //     {
    //         cout<<"Codurile celor "<<this->nrProduse<<" produse: ";
    //         this->coduriProduse=new int[this->nrProduse];
    //         for(int i=0; i<this->nrProduse; i++)
    //             cin>>this->coduriProduse[i];
    //     }
    //     else this->coduriProduse=NULL;
    //     if(this->preturiProduse!=NULL)
    //         delete[] this->preturiProduse;
    //     float suma=0;
    //     if(this->nrProduse!=0)
    //     {
    //         cout<<"Preturile celor "<<this->nrProduse<<" produse: ";
    //         this->preturiProduse=new float[this->nrProduse];
    //         for(int i=0; i<this->nrProduse; i++)
    //             {
    //                 cin>>this->preturiProduse[i];
    //                 suma=suma+this->preturiProduse[i];
    //             }
    //     }
    //     this->pretTotal=suma;
    //     cout<<"Stare comanda: ";
    //     cin.getline(aux,100);
    //     if(strcmp(aux,"")==0)
    //         cin.getline(aux,100);
    //     if(this->stare!=NULL)
    //         delete[] this->stare;
    //     if(aux!=NULL)
    //     {
    //         this->stare=new char[strlen(aux)+1];
    //         strcpy(this->stare,aux);
    //     }
    //     else this->stare=NULL;
    //     cout<<endl;
    // }

    // void afisare()
    // {
    //     cout<<"Detalii despre comanda: "<<endl<<endl;
    //     cout<<this->persoana;
    //     if(this->nrProduse!=0)
    //     {
    //         cout<<"Numar Produse: "<<this->nrProduse<<endl;
    //         if(this->coduriProduse!=NULL && this->preturiProduse!=NULL)
    //         {
    //             cout<<"Produse:"<<endl;
    //             for(int i=0; i<this->nrProduse; i++)
    //                 if(this->coduriProduse[i]!=0 && this->preturiProduse[i]!=0)
    //                     cout<<"   "<<this->coduriProduse[i]<<" -> Pret: "<<this->preturiProduse[i]<<endl;
    //                 else cout<<"   Produsul cu numarul "<<i+1<<" din comanda este invalid."<<endl;
    //         }
    //         else cout<<"Nu exista produse in lista de cumparaturi!"<<endl;
    //         if(this->pretTotal!=0)
    //             cout<<"Pret total: "<<this->pretTotal<<endl;
    //         else cout<<"Pret total: Nespecificat"<<endl;
    //         if(this->stare!=NULL)
    //             cout<<"Stare comanda: "<<this->stare<<endl;
    //         else cout<<"Stare comanda: Necunoscuta"<<endl;
    //     }
    //     else
    //         cout<<"Comanda invalida! Aceasta nu contine produse!"<<endl;
    // }

    /// Getters pt toate variabilele
    int getId()
    {
        return this->id;
    }

    const client getPersoana()
    {
        return this->persoana;
    }

    int getNrProduse()
    {
        return this->nrProduse;
    }

    const int* getCoduriProduse()
    {
        return coduriProduse;
    }

    const float* getPreturiProduse()
    {
        return preturiProduse;
    }

    float getPretTotal()
    {
        return pretTotal;
    }

    const char* getStare()
    {
        return stare;
    }

    /// Setters pt toate variabilele
    void setPersoana(client persoana) // spre deosebire de operatorul =, aici modific toate informatiile despre persoana
    {
        this->persoana=persoana;
    }

    void setNrProduse(int nrProduse)
    {
        this->nrProduse=nrProduse;
    }

    void setCoduriProduse(int* coduriProduse)
    {
        if(this->coduriProduse!=NULL)
            delete[] this->coduriProduse;
        this->coduriProduse=new int[this->nrProduse];
        for(int i=0; i<this->nrProduse; i++)
            this->coduriProduse[i]=coduriProduse[i];
    }

    void setPreturiProduse(float* preturiProduse)
    {
        if(this->preturiProduse!=NULL)
            delete[] this->preturiProduse;
        this->preturiProduse=new float[this->nrProduse];
        for(int i=0; i<this->nrProduse; i++)
            this->preturiProduse[i]=preturiProduse[i];
    }

    void setPretTotal(float pretTotal)
    {
        this->pretTotal=pretTotal;
    }

    void setStare(char* stare)
    {
        if(this->stare!=NULL)
            delete[] this->stare;
        if(stare!=NULL && strlen(stare)>0)
        {
            this->stare=new char[strlen(stare)+1];
            strcpy(this->stare, stare);
        }
        else this->stare=NULL;
    }

    friend ostream& operator << (ostream&, const comanda&);
    friend istream& operator >> (istream&, comanda&);
    friend comanda operator + (const produs&,const comanda&);

    /// Destructor
    ~comanda()
    {
        if(this->coduriProduse!=NULL)
            delete[] this->coduriProduse;
        if(this->preturiProduse!=NULL)
            delete[] this->preturiProduse;
        if(this->stare!=NULL)
            delete[] this->stare;
    }
};

/// Adunare client+adresa
client operator + (const adr &adresa, const client &obj)
{
    client copie=obj;
    copie.adresaFact=adresa;
    copie.adresaLiv=adresa;
    return copie;
}
/// Operatorul + cu clasa produs - adaug un produs la comanda actuala
comanda operator + (const produs &prod, const comanda &obj) // la dreapta
{
    comanda copie=obj;
    if(copie.nrProduse>0)
    {
        int n=copie.nrProduse;
        if(copie.coduriProduse!=NULL)
        {
            int v[200];
            for(int i=0; i<n; i++)
                v[i]=copie.coduriProduse[i];
            v[copie.nrProduse]=prod.id;
            delete[] copie.coduriProduse;
            copie.coduriProduse=new int[copie.nrProduse];
            for(int i=0; i<copie.nrProduse+1; i++)
                copie.coduriProduse[i]=v[i];
        }
        if(copie.preturiProduse!=NULL)
        {
            float v[200];
            for(int i=0; i<n; i++)
                v[i]=copie.preturiProduse[i];
            v[copie.nrProduse]=prod.id;
            delete[] copie.preturiProduse;
            copie.preturiProduse=new float[copie.nrProduse];
            for(int i=0; i<copie.nrProduse+1; i++)
                copie.preturiProduse[i]=v[i];
            copie.pretTotal=copie.pretTotal+prod.pret;
        }
        ++copie.nrProduse;
    }
    else
    {
        if(copie.coduriProduse!=NULL)
            delete[] copie.coduriProduse;
        if(copie.preturiProduse!=NULL)
            delete[] copie.preturiProduse;
        copie.nrProduse=1;
        copie.coduriProduse=new int[1];
        copie.preturiProduse=new float[1];
        copie.coduriProduse[0]=prod.id;
        copie.preturiProduse[0]=prod.pret;
        copie.pretTotal=prod.pret;
    }
    return copie;
}

/// SUPRAINCARCARI PENTRU <<
/// DE ADAUGAT LA TOATE ID-URI STATICE!!

ostream& operator << (ostream &out, const adr &obj) // afisare adresa
{
    out<<"Id adresa: "<<obj.id<<endl;
    if(obj.tara!=NULL)
        out<<"Tara: "<<obj.tara<<endl;
    else out<<"Tara: Nespecificat"<<endl;
    if(obj.judet!=NULL)
        out<<"Judet/Sector: "<<obj.judet<<endl;
    else out<<"Judet: Nespecificat"<<endl;
    if(obj.oras!=NULL)
        out<<"Oras: "<<obj.oras<<endl;
    else out<<"Oras: Nespecificat"<<endl;
    if(obj.strada!=NULL)
        out<<"Strada: "<<obj.strada<<endl;
    else out<<"Strada: Nespecificat"<<endl;
    if(obj.nr!=-1)
        out<<"Numarul: "<<obj.nr<<endl;
    else out<<"Numarul: Nespecificat"<<endl;
    if(obj.optional==false)
        out<<"Adresa nu contine informatii despre un apartament."<<endl;
    else
    {
        if(obj.bloc!=NULL)
            out<<"Bloc: "<<obj.bloc<<endl;
        else out<<"Bloc: Nespecificat"<<endl;
        if(obj.scara!=-1)
            out<<"Scara/Tronson: "<<obj.scara<<endl;
        else out<<"Scara/Tronson: Nespecificat"<<endl;
        if(obj.etaj!=-1)
            out<<"Etaj: "<<obj.etaj<<endl;
        else out<<"Etaj: Nespecificat"<<endl;
        if(obj.ap!=-1)
            out<<"Apartament: "<<obj.ap<<endl;
        else out<<"Apartament: Nespecificat"<<endl;
    }
    return out;
}

ostream& operator << (ostream &out, const client &obj) // afisare client
{
    out<<"Id client: "<<obj.id<<endl;
    if(obj.nume!=NULL)
        out<<"Nume: "<<obj.nume<<endl;
    else out<<"Nume: Nespecificat"<<endl;
    if(obj.prenume!=NULL)
        out<<"Prenume: "<<obj.prenume<<endl;
    else out<<"Prenume: Nespecificat"<<endl;
    if(obj.nrTel!=NULL)
        out<<"Numar Telefon: "<<obj.nrTel<<endl;
    else out<<"Numar Telefon: Nespecificat"<<endl;
    if(obj.email!=NULL)
        out<<"Email: "<<obj.email<<endl;
    else out<<"Email: Nespecificat"<<endl;
    out<<"Numar comenzi: "<<obj.nrComenzi<<endl<<endl;
    out<<"Adresa de facturare:"<<endl;
    out<<obj.adresaFact<<endl;
    out<<"Adresa de livrare:"<<endl;
    out<<obj.adresaLiv<<endl;
    return out;
}

ostream& operator << (ostream &out, const fir &obj) // afisare fir
{
    out<<"Id Fir: "<<obj.id<<endl;
    if(obj.denumire!=NULL)
        out<<"Denumire: "<<obj.denumire<<endl;
    else out<<"Denumire: Nespecificat"<<endl;
    if(obj.compozitie!=NULL)
        out<<"Compozitie: "<<obj.compozitie<<endl;
    else out<<"Compozitie: Nespecificat"<<endl;
    if(obj.grosime!=-1)
        out<<"Categorie Grosime: "<<obj.grosime<<endl;
    else out<<"Categorie Grosime: Nespecificat"<<endl;
    if(obj.metraj!=0)
        out<<"Metraj: "<<obj.metraj<<endl;
    else out<<"Metraj: Nespecificat"<<endl;
    if(obj.gramaj!=0)
        out<<"Gramaj per ghem: "<<obj.gramaj<<endl;
    else out<<"Gramaj per ghem: Nespecificat"<<endl;
    if(obj.coduriCulori!=NULL)
    {
        out<<"Disponibilitate culori:"<<endl;
        if(obj.nrCulori>0)
        {
            for(int i=0; i<obj.nrCulori; i++)
            {
                out<<obj.coduriCulori[i]<<" -> ";
                if(obj.nrStoc!=NULL && obj.nrStoc[i]!=0)
                    out<<obj.nrStoc[i]<<"; ";
                else out<<"Indisponibil; ";
            }
            out<<endl;
        }
        else cout<<"Nu exista culori disponibile"<<endl;
    }
    if(obj.lucrat!=0)
        out<<"Marime andrele/croseta: "<<obj.lucrat<<endl;
    else out<<"Marime andrele/croseta: Nespecificat"<<endl;
    return out;
}

ostream& operator << (ostream &out, const produs &obj) // afisare produs
{
    out<<"Id Produs: "<<obj.id<<endl;
    if(obj.nume!=NULL)
        out<<"Nume produs: "<<obj.nume<<endl;
    else out<<"Nume produs: Nespecificat"<<endl;
    if(obj.nrFire!=0)
    {
        out<<"Numar fire folosite: "<<obj.nrFire<<endl;
        if(obj.fire!=NULL)
        {
            out<<"Coduri fire utilizate: ";
            for(int i=0; i<obj.nrFire; i++)
                if(obj.fire[i]!=0)
                    out<<obj.fire[i]<<", ";
                else out<<"Nespecificat, ";
            out<<endl;
        }
        else cout<<"Coduri fire utilizate: Nespecificat"<<endl;
    }
    else out<<"Numar fire folosite: Nespecificat"<<endl;

    if(obj.pret!=0)
        out<<"Pret: "<<obj.pret<<endl;
    else out<<"Pret: Nespecificat"<<endl;
    if(obj.marime!='X')
        out<<"Marime: "<<obj.marime<<endl;
    else out<<"Marime: Nespecificat"<<endl;
    if(obj.tehnica=='T' || obj.tehnica=='t')
        out<<"Tehnica: tricotat"<<endl;
    else if(obj.tehnica=='C' || obj.tehnica=='c')
        out<<"Tehnica: crosetat"<<endl;
    else if(obj.tehnica=='A' || obj.tehnica=='a')
        out<<"Tehnica: crosetat si tricotat"<<endl;
    else out<<"Tehnica: nespecificat"<<endl;
    return out;
}

ostream& operator << (ostream &out, const comanda &obj) // afisare comanda
{
    out<<"Detalii despre comanda: "<<endl<<endl;
    out<<"Id Comanda: "<<obj.id<<endl;
    out<<obj.persoana;
    if(obj.nrProduse!=0)
    {
        out<<"Numar Produse: "<<obj.nrProduse<<endl;
        if(obj.coduriProduse!=NULL)
        {
            out<<"Produse:"<<endl;
            for(int i=0; i<obj.nrProduse; i++)
                if(obj.coduriProduse[i]!=0 && obj.preturiProduse!=NULL && obj.preturiProduse[i]!=0)
                    out<<"   "<<obj.coduriProduse[i]<<" -> Pret: "<<obj.preturiProduse[i]<<endl;
                else out<<"   Produsul cu numarul "<<i+1<<" din comanda este invalid."<<endl;
        }
        else out<<"Nu exista produse in lista de cumparaturi!"<<endl;
        if(obj.pretTotal!=0)
            out<<"Pret total: "<<obj.pretTotal<<endl;
        else out<<"Pret total: Nespecificat"<<endl;
        if(obj.stare!=NULL)
            out<<"Stare comanda: "<<obj.stare<<endl;
        else out<<"Stare comanda: Necunoscuta"<<endl;
        return out;
    }
    else
    {
        out<<"Comanda invalida! Numar de produse invalid!"<<endl;
        return out;
    }
    return out;
}

/// SUPRAINCARCARI PENTRU >>

istream& operator >> (istream &in, adr &obj) // citire adresa
{
    char aux[100];
    cout<<"Introduceti urmatoarele informatii despre adresa: "<<endl;

    cout<<"Tara: ";
    in.getline(aux,100);
    while(strcmp(aux,"")==0)
        in.getline(aux,100);
    if(obj.tara!=NULL)
        delete[] obj.tara;
    if(strcmp(aux,"")!=0)
    {
        obj.tara=new char[strlen(aux)+1];
        strcpy(obj.tara, aux);
        obj.tara[strlen(aux)]='\0';
    }
    else obj.tara=NULL;

    cout<<"Judet: ";
    in.getline(aux,100);
    if(obj.judet!=NULL)
        delete[] obj.judet;
    if(strcmp(aux,"")!=0)
    {
        obj.judet=new char[strlen(aux)+1];
        strcpy(obj.judet, aux);
        obj.judet[strlen(aux)]='\0';
    }
    else obj.judet=NULL;

    cout<<"Oras: ";
    in.getline(aux,100);
    if(obj.oras!=NULL)
        delete[] obj.oras;
    if(strcmp(aux,"")!=0)
    {
        obj.oras=new char[strlen(aux)+1];
        strcpy(obj.oras, aux);
        obj.oras[strlen(aux)]='\0';
    }
    else obj.oras=NULL;

    cout<<"Strada: ";
    in.getline(aux,100);
    if(obj.strada!=NULL)
        delete[] obj.strada;
    if(strcmp(aux,"")!=0)
    {
        obj.strada=new char[strlen(aux)+1];
        strcpy(obj.strada, aux);
        obj.strada[strlen(aux)]='\0';
    }
    else obj.strada=NULL;

    cout<<"Numarul: ";
    in>>obj.nr;

    cout<<endl<<"Adresa apartine unui apartament? Introduceti cifra corespunzatoare raspunsului."<<endl;
    cout<<"1. DA     2. NU"<<endl<<"Introduceti optiunea: ";
    int val;
    in>>val;
    while(val!=1 && val!=2)
    {
        cout<<"Valoarea introdusa nu corespunde selectiei. Incercati din nou. "<<endl<<"Introduceti optiunea: ";
        in>>val;
    }
    if(val==1)
    {
        cout<<"Bloc: ";
        in.getline(aux,100);
        while(strcmp(aux,"")==0)
            in.getline(aux,100);
        if(obj.bloc!=NULL)
            delete[] obj.bloc;
        if(strcmp(aux,"")!=0)
        {
            obj.bloc=new char[strlen(aux)+1];
            strcpy(obj.bloc, aux);
            obj.bloc[strlen(aux)]='\0';
        }
        else obj.bloc=NULL;

        cout<<"Scara/Tronson: ";
        in>>obj.scara;
        cout<<"Etaj: ";
        in>>obj.etaj;
        cout<<"Apartament: ";
        in>>obj.ap;

        obj.optional=true;
    }
    else obj.optional=false;

        cout<<endl<<"Adresa a fost completata cu succes"<<endl;

    return in;
}

istream& operator >> (istream &in, client &obj) // citire client
{
    char aux[100];
    cout<<"Introduceti urmatoarele informatii despre client: "<<endl;

    cout<<"Nume: ";
    in.getline(aux,100);
    while(strcmp(aux,"")==0)
        in.getline(aux,100);
    if(obj.nume!=NULL)
        delete[] obj.nume;
    if(aux!=NULL)
    {
        obj.nume=new char[strlen(aux)+1];
        strcpy(obj.nume, aux);
    }
    else obj.nume=NULL;

    cout<<"Prenume: ";
    in.getline(aux,100);
    if(obj.prenume!=NULL)
        delete[] obj.prenume;
    if(aux!=NULL)
    {
        obj.prenume=new char[strlen(aux)+1];
        strcpy(obj.prenume, aux);
    }
    else obj.prenume=NULL;

    cout<<"Numar Telefon: ";
    in.getline(aux,100);
    if(obj.nrTel!=NULL)
        delete[] obj.nrTel;
    if(aux!=NULL)
    {
        obj.nrTel=new char[strlen(aux)+1];
        strcpy(obj.nrTel, aux);
    }
    else obj.nrTel=NULL;

    cout<<"Email: ";
    in.getline(aux,100);
    if(obj.email!=NULL)
        delete[] obj.email;
    if(aux!=NULL)
    {
        obj.email=new char[strlen(aux)+1];
        strcpy(obj.email, aux);
    }
    else obj.email=NULL;

    cout<<endl<<"Cate comenzi a avut clientul?"<<endl;
    in>>obj.nrComenzi;
    cout<<endl<<"Introduceti adresa de facturare: "<<endl;
    in>>obj.adresaFact;
    cout<<endl<<"Adresa de livrare este aceeasi cu cea de facturare? Introduceti cifra corespunzatoare raspunsului."<<endl;
    cout<<"1. DA     2. NU"<<endl<<"Introduceti optiunea: ";
    int val;
    in>>val;
    while(val!=1 && val!=2)
    {
        cout<<"Valoarea introdusa nu corespunde selectiei. Incercati din nou. "<<endl<<"Introduceti optiunea: ";
        in>>val;
    }
    if(val==1)
        obj.adresaLiv=obj.adresaFact;
    else
    {
        cout<<endl<<"Introduceti adresa de livrare: "<<endl;
        in>>obj.adresaLiv;
    }
    cout<<endl<<"Ati completat cu succes datele clientului."<<endl;

    return in;
}

istream& operator >> (istream &in, fir &obj) // citire fir - CRAPA DACA DAU LITERE LA METRAJ
{
    char aux[200]; //declarat mai mare deoarece compozitia poate contine mai mult text
    cout<<"Introduceti urmatoarele informatii despre fir: "<<endl;

    cout<<"Denumire: ";
    in.getline(aux,200);
    while(strcmp(aux,"")==0)
        in.getline(aux,200);
    if(obj.denumire!=NULL)
        delete[] obj.denumire;
    if(aux!=NULL)
    {
        obj.denumire=new char[strlen(aux)+1];
        strcpy(obj.denumire, aux);
    }
    else obj.denumire=NULL;

    cout<<"Compozitie: ";
    in.getline(aux,200);
    if(obj.compozitie!=NULL)
        delete[] obj.compozitie;
    if(aux!=NULL)
    {
        obj.compozitie=new char[strlen(aux)+1];
        strcpy(obj.compozitie, aux);
    }
    else obj.compozitie=NULL;

    cout<<"Metraj: ";
    in>>obj.metraj;
    cout<<"Gramaj: ";
    in>>obj.gramaj;
    cout<<"Doriti introducerea manuala sau automata a categoriei de grosime a firului? Introduceti cifra corespunzatoare raspunsului."<<endl;
    cout<<"1. Manuala     2. Automata"<<endl<<"Introduceti optiunea: ";
    int val;
    in>>val;
    while(val!=1 && val!=2)
    {
        cout<<"Valoarea introdusa nu corespunde selectiei. Incercati din nou. "<<endl<<"Introduceti optiunea: ";
        in>>val;
    }
    if(val==1)
    {
        cout<<"Grosime: ";
        in>>obj.grosime;
    }
    else
    {
        /// programul calculeaza pe baza normelor internationale
        float auxGrosime=1.0*obj.metraj/obj.gramaj; // valori standard internationale pentru categorii
        if(auxGrosime<1.0)
            obj.grosime=6;
        else if(auxGrosime<1.30)
            obj.grosime=5;
        else if(auxGrosime<2.30)
            obj.grosime=4;
        else if(auxGrosime<3.00)
            obj.grosime=3;
        else if(auxGrosime<4.00)
            obj.grosime=2;
        else if(auxGrosime<6.00)
            obj.grosime=1;
        else obj.grosime=0;
        cout<<"Grosime: "<<obj.grosime<<" (completat automat)"<<endl;
    }
    cout<<"Numarul de culori disponibile: ";
    in>>obj.nrCulori;
    if(obj.nrCulori>0)
    {
        if(obj.coduriCulori!=NULL)
            delete[] obj.coduriCulori;
        if(obj.nrStoc!=NULL)
            delete[] obj.nrStoc;

        obj.coduriCulori=new int[obj.nrCulori];
        obj.nrStoc=new int[obj.nrCulori];
        cout<<"Introduceti perechile de numere de forma *codCuloare* *stocCuloare*: "<<endl;
        for(int i=0; i<obj.nrCulori; i++)
        {
            in>>obj.coduriCulori[i];
            in>>obj.nrStoc[i];
        }
    }
    else
    {
        obj.coduriCulori=NULL;
        obj.nrStoc=NULL;
    }
    cout<<"Dimensiunea recomandata a andrelelor/crosetei de lucru: ";
    in>>obj.lucrat;

    cout<<endl<<"Ati introdus cu succes informatiile despre fir"<<endl;
    return in;
}

istream& operator >> (istream &in, produs &obj) // citire produs
{

    char aux[100];
    cout<<"Introduceti urmatoarele date despre produs: "<<endl;
    cout<<"Nume produs: ";
    in.getline(aux,100);
    while(strcmp(aux,"")==0)
        in.getline(aux, 100);
    if(obj.nume!=NULL)
        delete[] obj.nume;
    if(aux!=NULL)
    {
        obj.nume=new char[strlen(aux)+1];
        strcpy(obj.nume,aux);
    }
    else obj.nume=NULL;
    cout<<"Numarul de fire utilizate: ";
    in>>obj.nrFire;
    if(obj.fire!=NULL)
        delete[] obj.fire;
    if(obj.nrFire!=0)
    {
        obj.fire=new int[obj.nrFire];
        cout<<"Introduceti codurile firelor utizilate: ";
        for(int i=0; i<obj.nrFire; i++)
            in>>obj.fire[i];
    }
    else obj.fire=NULL;

    cout<<"Pretul produsului: ";
    in>>obj.pret;
    cout<<"Marime produs (de forma S,M,L): ";
    in>>obj.marime;
    cout<<"Tehnica executarii (T-tricotat, C-crosetat, A-ambele): ";
    in>>obj.tehnica;

    return in;
}

istream& operator >> (istream &in, comanda &obj) // citire comanda
{
    char aux[100];
    cout<<"Introduceti urmatoarele detalii despre comanda: "<<endl<<endl;
    /// primul va fi afisat id-ul
    in>>obj.persoana;
    cout<<"Numar produse comanda: ";
    in>>obj.nrProduse;

    if(obj.coduriProduse!=NULL)
        delete[] obj.coduriProduse;
    if(obj.nrProduse!=0)
    {
        cout<<"Codurile celor "<<obj.nrProduse<<" produse: ";
        obj.coduriProduse=new int[obj.nrProduse];
        for(int i=0; i<obj.nrProduse; i++)
            in>>obj.coduriProduse[i];
    }
    else obj.coduriProduse=NULL;

    if(obj.preturiProduse!=NULL)
        delete[] obj.preturiProduse;
    float suma=0;
    if(obj.nrProduse!=0)
    {
        cout<<"Preturile celor "<<obj.nrProduse<<" produse: ";
        obj.preturiProduse=new float[obj.nrProduse];
        for(int i=0; i<obj.nrProduse; i++)
            {
                in>>obj.preturiProduse[i];
                suma=suma+obj.preturiProduse[i];
            }
    }
    obj.pretTotal=suma;
    cout<<"Stare comanda: ";
    in.getline(aux,100);
    if(strcmp(aux,"")==0)
        in.getline(aux,100);
    if(obj.stare!=NULL)
        delete[] obj.stare;
    obj.stare=new char[strlen(aux)+1];
    strcpy(obj.stare, aux);
    cout<<endl;

    return in;
}

int adr::CONTORADR=1;
int client::CONTORCLIENT=1;
int fir::CONTORFIR=1000;
int produs::CONTORPRODUS=10000;
int comanda::CONTORCOMANDA=100000;

int optiuneMain, optiuneMeniu1, optiuneMeniu2, optiuneMeniu3, optiuneMeniu4, optiuneMeniu5, afisare;
int k1,k2,k3,k4,k5;
adr adrese[100];
client clienti[100];
fir fire[100];
produs produse[100];
comanda comenzi[100];

/// FUNCTII DE AFISARE MENIU :


void introducereDate()
{
    // foloseste optiuneMeniu1
    switch(optiuneMeniu1)
    {
        case 1:
        {
            if(k1<100)
            {
                cin>>adrese[k1];
                k1++;
            }
            else cout<<"Sistemul nu mai permite introducerea altor adrese"<<endl;
            break;
        }
        case 2:
        {
            if(k2<100)
            {
                cin>>clienti[k2];
                k2++;
            }
            else cout<<"Sistemul nu mai permite introducerea altor clienti"<<endl;
            break;
        }
        case 3:
        {
            if(k3<100)
            {
                cin>>fire[k3];
                k3++;
            }
            else cout<<"Sistemul nu mai permite introducerea altor fire"<<endl;
            break;
        }
        case 4:
        {
            if(k4<100)
            {
                cin>>produse[k4];
                k4++;
            }
            else cout<<"Sistemul nu mai permite introducerea altor produse"<<endl;
            break;
        }
        case 5:
        {
            if(k5<100)
            {
                cin>>comenzi[k5];
                k5++;
            }
            else cout<<"Sistemul nu mai permite introducerea altor comenzi"<<endl;
            break;
        }
    }
}

void afisareDate()
{
    int card=0;
    switch (optiuneMeniu2)
    {
        case 1:
        {
            cout<<"Doriti afisarea unei anume adrese sau a tuturor?"<<endl;
            cout<<"1.O adresa     2.Toate"<<endl<<"Introduceti valoarea: ";
            cin>>card;
            while(card!=1 && card!=2)
            {
                cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                cin>>card;
            }
            if(card==1)
            {
                int idAdr;
                bool gasit=0;
                cout<<"Introduceti id-ul adresei de afisat: ";
                cin>>idAdr;
                while(idAdr<=0)
                {
                    cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                    cin>>idAdr;
                }
                for(int i=0; i<k1; i++)
                {
                    if(idAdr==adrese[i].getId())
                    {
                        cout<<adrese[i]<<endl;
                        i=k1+1;
                        gasit=1;
                    }
                }
                if(gasit==0)
                    cout<<"Ne pare rau, adresa cu id-ul "<<idAdr<<" nu a putut fi gasita"<<endl;
            }
            else
            {
                if(k1>0)
                {
                    cout<<endl;
                    for(int i=0; i<k1; i++)
                    {
                        cout<<"Adresa cu id-ul "<<adrese[i].getId()<<endl;
                        cout<<adrese[i]<<endl;
                    }
                }
                else cout<<"Ne pare rau, dar nu exista adrese retinute in sistem"<<endl;
            }
            break;
        }
        case 2:
        {
            cout<<"Doriti afisarea unui anume client sau a tuturor?"<<endl;
            cout<<"1.Un client     2.Toti"<<endl<<"Introduceti valoarea: ";
            cin>>card;
            while(card!=1 && card!=2)
            {
                cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                cin>>card;
            }
            if(card==1)
            {
                int idAdr;
                bool gasit=0;
                cout<<"Introduceti id-ul clientului de afisat: ";
                cin>>idAdr;
                while(idAdr<=0)
                {
                    cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                    cin>>idAdr;
                }
                for(int i=0; i<k2; i++)
                {
                    if(idAdr==clienti[i].getId())
                    {
                        cout<<clienti[i]<<endl;
                        i=k2+1;
                        gasit=1;
                    }
                }
                if(gasit==0)
                    cout<<"Ne pare rau, clientul cu id-ul "<<idAdr<<" nu a putut fi gasit"<<endl;
            }
            else
            {
                if(k2>0)
                {
                    cout<<endl;
                    for(int i=0; i<k2; i++)
                    {
                        cout<<"Clientul cu id-ul "<<clienti[i].getId()<<endl;
                        cout<<clienti[i]<<endl;
                    }
                }
                else cout<<"Ne pare rau, dar nu exista clienti retinuti in sistem"<<endl;
            }
            break;
        }
        case 3:
        {
            cout<<"Doriti afisarea unui anume fir sau a tuturor?"<<endl;
            cout<<"1.Un fir     2.Toate"<<endl<<"Introduceti valoarea: ";
            cin>>card;
            while(card!=1 && card!=2)
            {
                cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                cin>>card;
            }
            if(card==1)
            {
                int idAdr;
                bool gasit=0;
                cout<<"Introduceti id-ul firului de afisat: ";
                cin>>idAdr;
                while(idAdr<1000)
                {
                    cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                    cin>>idAdr;
                }
                for(int i=0; i<k3; i++)
                {
                    if(idAdr==fire[i].getId())
                    {
                        cout<<fire[i]<<endl;
                        i=k3+1;
                        gasit=1;
                    }
                }
                if(gasit==0)
                    cout<<"Ne pare rau, firul cu id-ul "<<idAdr<<" nu a putut fi gasit"<<endl;
            }
            else
            {
                if(k3>0)
                {
                    cout<<endl;
                    for(int i=0; i<k3; i++)
                    {
                        cout<<"Firul cu id-ul "<<fire[i].getId()<<endl;
                        cout<<fire[i]<<endl;
                    }
                }
                else cout<<"Ne pare rau, dar nu exista fire retinute in sistem"<<endl;
            }
            break;
        }
        case 4:
        {
            cout<<"Doriti afisarea unui anume produs sau a tuturor?"<<endl;
            cout<<"1.Un produs     2.Toate"<<endl<<"Introduceti valoarea: ";
            cin>>card;
            while(card!=1 && card!=2)
            {
                cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                cin>>card;
            }
            if(card==1)
            {
                cout<<"Introduceti id-ul produsului de afisat: ";
                int idAdr;
                bool gasit=0;
                cin>>idAdr;
                while(idAdr<10000)
                {
                    cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                    cin>>idAdr;
                }
                for(int i=0; i<k4; i++)
                {
                    if(idAdr==produse[i].getId())
                    {
                        cout<<produse[i]<<endl;
                        i=k4+1;
                        gasit=1;
                    }
                }
                if(gasit==0)
                    cout<<"Ne pare rau, produsul cu id-ul "<<idAdr<<" nu a putut fi gasit"<<endl;
            }
            else
            {
                if(k4>0)
                {
                    cout<<endl;
                    for(int i=0; i<k4; i++)
                    {
                        cout<<"Produsul cu id-ul "<<produse[i].getId()<<endl;
                        cout<<produse[i]<<endl;
                    }
                }
                else cout<<"Ne pare rau, dar nu exista produse retinute in sistem"<<endl;
            }
            break;
        }
        case 5:
        {
            cout<<"Doriti afisarea unei anume comenzi sau a tuturor?"<<endl;
            cout<<"1.O comanda     2.Toate"<<endl<<"Introduceti valoarea: ";
            cin>>card;
            while(card!=1 && card!=2)
            {
                cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                cin>>card;
            }
            if(card==1)
            {
                cout<<"Introduceti id-ul comenzii de afisat: ";
                int idAdr;
                bool gasit=0;
                cin>>idAdr;
                while(idAdr<100000)
                {
                    cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                    cin>>idAdr;
                }
                for(int i=0; i<k5; i++)
                {
                    if(idAdr==comenzi[i].getId())
                    {
                        cout<<comenzi[i]<<endl;
                        i=k5+1;
                        gasit=1;
                    }
                }
                if(gasit==0)
                    cout<<"Ne pare rau, comanda cu id-ul "<<idAdr<<" nu a putut fi gasita"<<endl;
            }
            else
            {
                if(k5>0)
                {
                    cout<<endl;
                    for(int i=0; i<k5; i++)
                    {
                        cout<<"Comanda cu id-ul "<<comenzi[i].getId()<<endl;
                        cout<<comenzi[i]<<endl;
                    }
                }
                else cout<<"Ne pare rau, dar nu exista comenzi retinute in sistem"<<endl;
            }
            break;
        }
    }
}

void actualizareDate()
{
    int cod, opt=0;
    switch(optiuneMeniu3)
    {
        case 1:
        {
            int indice=-1, selectie=0;
            if(k1>0)
            {
                cout<<"Ati solicitat modificarea unei adrese. Introduceti id-ul acesteia: ";
                cin>>cod;
                while(cod<=0)
                {
                    cout<<"Id-ul introdus nu este valid. Incercati din nou: ";
                    cin>>cod;
                }
                for(int i=0; i<=k1; i++)
                {
                    if(cod==adrese[i].getId())
                        indice=i;
                }
                if(indice>=0)
                {
                    char aux[100];
                    int auxi;
                    cout<<"Ce doriti sa modificati?"<<endl<<"1. Tara"<<endl<<"2. Judet"<<endl<<"3. Oras"<<endl;
                    cout<<"4. Strada"<<endl<<"5. Numar"<<endl<<"6. Bloc"<<endl<<"7. Scara/Tronson"<<endl<<"8. Etaj"<<endl<<"9. Apartament"<<endl;
                    cout<<endl<<"Introduceti optiunea:";
                    cin>>opt;
                    while(opt<1 && opt>9)
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
                        adrese[indice].setTara(aux);
                        break;
                    case 2:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        adrese[indice].setJudet(aux);
                        break;
                    case 3:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        adrese[indice].setOras(aux);
                        break;
                    case 4:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        adrese[indice].setStrada(aux);
                        break;
                    case 5:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<=0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxi;
                        }
                        adrese[indice].setNr(auxi);
                        break;
                    case 6:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        adrese[indice].setBloc(aux);
                        break;
                    case 7:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<=0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxi;
                        }
                        adrese[indice].setScara(auxi);
                        break;
                    case 8:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<=0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>aux;
                        }
                        adrese[indice].setEtaj(auxi);
                        break;
                    case 9:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<=0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxi;
                        }
                        adrese[indice].setAp(auxi);
                        break;
                    }
                }
                else cout<<"Din pacate, adresa cu id-ul "<<cod<<" nu a fost gasita"<<endl;
            }
            else cout<<"Din pacate, nu exista adrese salvate in sistem"<<endl;
            break;
        }
        case 2:
        {
            int indice=-1, selectie=0;
            if(k2>0)
            {
                cout<<"Ati solicitat modificarea unui client. Introduceti id-ul acestuia: ";
                cin>>cod;
                while(cod<=0)
                {
                    cout<<"Id-ul introdus nu este valid. Incercati din nou: ";
                    cin>>cod;
                }
                for(int i=0; i<=k2; i++)
                {
                    if(cod==clienti[i].getId())
                        indice=i;
                }
                if(indice>=0)
                {
                    char aux[100];
                    int auxi;
                    adr auxiliar;
                    cout<<"Ce doriti sa modificati?"<<endl<<"1. Nume"<<endl<<"2. Prenume"<<endl<<"3. Numar telefon"<<endl;
                    cout<<"4. Email"<<endl<<"5. Numarul de comenzi"<<endl<<"6. Adresa de facturare"<<endl<<"7. Adresa de livrare";
                    cout<<endl<<"8. Ambele adrese simultan"<<endl;
                    cout<<endl<<"Introduceti optiunea:";
                    cin>>opt;
                    while(opt<1 && opt>8)
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
                        clienti[indice].setNume(aux);
                        break;
                    case 2:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        clienti[indice].setPrenume(aux);
                        break;
                    case 3:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        clienti[indice].setNrTel(aux);
                        break;
                    case 4:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        clienti[indice].setEmail(aux);
                        break;
                    case 5:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<=0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxi;
                        }
                        clienti[indice].setNrComenzi(auxi);
                        break;
                    case 6:
                        cin>>auxiliar;
                        clienti[indice].setAdresaFact(auxiliar);
                        break;
                    case 7:
                        cin>>auxiliar;
                        clienti[indice].setAdresaFact(auxiliar);
                        break;
                    case 8:
                        cin>>auxiliar;
                        clienti[indice].setAdresaFact(auxiliar);
                        clienti[indice].setAdresaLiv(auxiliar);
                        break;
                    }
                }
                else cout<<"Din pacate, clientul cu id-ul "<<cod<<" nu a fost gasit"<<endl;
            }
            else cout<<"Din pacate, nu exista clienti salvati in sistem"<<endl;
            break;
        }
        case 3:
        {
            int indice=-1, selectie=0;
            if(k3>0)
            {
                cout<<"Ati solicitat modificarea unui fir. Introduceti id-ul acestuia: ";
                cin>>cod;
                while(cod<1000)
                {
                    cout<<"Id-ul introdus nu este valid. Incercati din nou: ";
                    cin>>cod;
                }
                for(int i=0; i<=k3; i++)
                {
                    if(cod==fire[i].getId())
                        indice=i;
                }
                if(indice>=0)
                {
                    char aux[100];
                    int auxi, v[100], w[100];
                    double auxiliar;
                    cout<<"Ce doriti sa modificati?"<<endl<<"1. Denumire"<<endl<<"2. Compozitie"<<endl<<"3. Metraj(m)"<<endl;
                    cout<<"4. Gramaj(g)"<<endl<<"5. Categorie grosime"<<endl<<"6. Numarul de culori"<<endl<<"7. Lista coduri culori";
                    cout<<endl<<"8. Lista stoc culori"<<endl<<"9. Dimensiune unelte necesare"<<endl;
                    cout<<endl<<"Introduceti optiunea:";
                    cin>>opt;
                    while(opt<1 && opt>9)
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
                        fire[indice].setDenumire(aux);
                        break;
                    case 2:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        fire[indice].setCompozitie(aux);
                        break;
                    case 3:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<=0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxi;
                        }
                        fire[indice].setMetraj(auxi);
                        break;
                    case 4:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<=0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxi;
                        }
                        fire[indice].setGramaj(auxi);
                        break;
                    case 5:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<0 || auxi>7)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxi;
                        }
                        fire[indice].setGrosime(auxi);
                        break;
                    case 6:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<=0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxi;
                        }
                        fire[indice].setNrCulori(auxi);
                        break;
                    case 7:
                        if(fire[indice].getNrCulori()>0)
                        {
                            cout<<"Introduceti lista celor "<<fire[indice].getNrCulori()<<" coduri: ";
                            for(int i=0; i<fire[indice].getNrCulori(); i++)
                                {
                                    cin>>v[i];
                                    while(v[i]<=0)
                                    {
                                        cout<<"Cod invalid. Incercati din nou: ";
                                        cin>>v[i];
                                    }
                                }
                            fire[indice].setCoduriCulori(v);
                        }
                        else cout<<"Din pacate, numarul de culori permise este 0"<<endl;
                        break;
                    case 8:
                        if(fire[indice].getNrCulori()>0)
                        {
                            cout<<"Introduceti lista celor "<<fire[indice].getNrCulori()<<" valori pentru stoc: ";
                            for(int i=0; i<fire[indice].getNrCulori(); i++)
                                {
                                    cin>>w[i];
                                    while(w[i]<0)
                                    {
                                        cout<<"Stoc invalid. Incercati din nou: ";
                                        cin>>w[i];
                                    }
                                }
                            fire[indice].setCoduriCulori(w);
                        }
                        else cout<<"Din pacate, numarul de stocuri pentru culori permise este 0"<<endl;
                        break;
                    case 9:
                        cout<<"Introduceti numarul: ";
                        cin>>auxiliar;
                        while(auxiliar<=0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxiliar;
                        }
                        fire[indice].setLucrat(auxiliar);
                        break;
                    }
                }
                else cout<<"Din pacate, firul cu id-ul "<<cod<<" nu a fost gasit"<<endl;
            }
            else cout<<"Din pacate, nu exista fire salvate in sistem"<<endl;
            break;
        }
        case 4:
        {
            int indice=-1, selectie=0;
            if(k4>0)
            {
                cout<<"Ati solicitat modificarea unui produs. Introduceti id-ul acestuia: ";
                cin>>cod;
                while(cod<10000)
                {
                    cout<<"Id-ul introdus nu este valid. Incercati din nou: ";
                    cin>>cod;
                }
                for(int i=0; i<=k4; i++)
                {
                    if(cod==produse[i].getId())
                        indice=i;
                }
                if(indice>=0)
                {
                    char aux[100], aux2;
                    int auxi, v[100];
                    float auxiliar;
                    cout<<"Ce doriti sa modificati?"<<endl<<"1. Numele produsului"<<endl<<"2. Numarul de fire folosite"<<endl;
                    cout<<"3. Lista codurilor firelor folosite"<<endl<<"4. Pretul produsului"<<endl<<"5. Marimea"<<endl;
                    cout<<"6. Tehnicile utilizate"<<endl;
                    cout<<endl<<"Introduceti optiunea:";
                    cin>>opt;
                    while(opt<1 && opt>6)
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
                        produse[indice].setNume(aux);
                        break;
                    case 2:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<=0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxi;
                        }
                        fire[indice].setMetraj(auxi);
                        break;
                    case 3:
                        if(produse[indice].getNrFire()>0)
                        {
                            cout<<"Introduceti lista celor "<<produse[indice].getNrFire()<<" coduri: ";
                            for(int i=0; i<produse[indice].getNrFire(); i++)
                                {
                                    cin>>v[i];
                                    while(v[i]<=0)
                                    {
                                        cout<<"Cod invalid. Incercati din nou: ";
                                        cin>>v[i];
                                    }
                                }
                            produse[indice].setFire(v);
                        }
                        else cout<<"Din pacate, numarul de fire permise este 0"<<endl;
                        break;
                    case 4:
                        cout<<"Introduceti numarul: ";
                        cin>>auxiliar;
                        while(auxiliar<=0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxiliar;
                        }
                        produse[indice].setPret(auxiliar);
                        break;
                    case 5:
                        cout<<"Introduceti marimea(S,M,L): ";
                        cin>>aux2;
                        while(strchr("smlSML",aux2)==0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>aux2;
                        }
                        produse[indice].setMarime(aux2);
                        break;
                    case 6:
                        cout<<"Introduceti tehnica(T-tricotat, C-Crosetat, A-Ambele): ";
                        cin>>aux2;
                        while(strchr("tcaTCA",aux2)==0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>aux2;
                        }
                        produse[indice].setTehnica(aux2);
                        break;
                    }
                }
                else cout<<"Din pacate, produsul cu id-ul "<<cod<<" nu a fost gasit"<<endl;
            }
            else cout<<"Din pacate, nu exista produse salvate in sistem"<<endl;
            break;
        }
        case 5:
        {
            int indice=-1, selectie=0;
            if(k5>0)
            {
                cout<<"Ati solicitat modificarea unei comenzi. Introduceti id-ul acesteia: ";
                cin>>cod;
                while(cod<100000)
                {
                    cout<<"Id-ul introdus nu este valid. Incercati din nou: ";
                    cin>>cod;
                }
                for(int i=0; i<=k5; i++)
                {
                    if(cod==comenzi[i].getId())
                        indice=i;
                }
                if(indice>=0)
                {
                    char aux[100];
                    int auxi, v[100];
                    float w[100];
                    float auxiliar;
                    cout<<"Ce doriti sa modificati? ATENTIE! Nu se poate modifica clientul!"<<endl<<"1. Numarul de produse"<<endl;
                    cout<<"2. Lista codurilor produselor"<<endl<<"3. Lista preturilor produselor"<<endl;
                    cout<<"4. Starea comenzii"<<endl;
                    cout<<endl<<"Introduceti optiunea:";
                    cin>>opt;
                    while(opt<1 && opt>4)
                    {
                        cout<<"Optiunea selectata nu este valida. Incercati din nou; ";
                        cin>>opt;
                    }
                    switch (opt)
                    {
                    case 1:
                        cout<<"Introduceti numarul: ";
                        cin>>auxi;
                        while(auxi<=0)
                        {
                            cout<<"Valoare invalida. Incercati din nou: ";
                            cin>>auxi;
                        }
                        comenzi[indice].setNrProduse(auxi);
                        break;
                    case 2:
                        if(comenzi[indice].getNrProduse()>0)
                        {
                            cout<<"Introduceti lista celor "<<comenzi[indice].getNrProduse()<<" coduri: ";
                            for(int i=0; i<comenzi[indice].getNrProduse(); i++)
                                {
                                    cin>>v[i];
                                    while(v[i]<=0)
                                    {
                                        cout<<"Cod invalid. Incercati din nou: ";
                                        cin>>v[i];
                                    }
                                }
                            comenzi[indice].setCoduriProduse(v);
                        }
                        else cout<<"Din pacate, numarul de produse permise este 0"<<endl;
                        break;
                    case 3:
                        if(comenzi[indice].getNrProduse()>0)
                        {
                            auxiliar=0;
                            cout<<"Introduceti lista celor "<<comenzi[indice].getNrProduse()<<" preturi: ";
                            for(int i=0; i<comenzi[indice].getNrProduse(); i++)
                                {
                                    cin>>w[i];
                                    while(w[i]<=0)
                                    {
                                        cout<<"Pret invalid. Incercati din nou: ";
                                        cin>>w[i];
                                    }
                                    auxiliar=auxiliar+w[i];
                                }
                            comenzi[indice].setPreturiProduse(w);
                            comenzi[indice].setPretTotal(auxiliar);
                        }
                        else cout<<"Din pacate, numarul de produse permise este 0"<<endl;
                        break;
                    case 4:
                        cout<<"Introduceti textul: ";
                        cin.get();
                        cin.getline(aux, 100);
                        comenzi[indice].setStare(aux);
                        break;
                    }
                }
                else cout<<"Din pacate, comanda cu id-ul "<<cod<<" nu a fost gasita"<<endl;
            }
            else cout<<"Din pacate, nu exista comenzi salvate in sistem"<<endl;
            break;
        }
        case 6:
        {
            int indice=-1, cod=0;
            adr aux;
            if(k1>0)
            {
                cout<<"Ati selectat adaugarea unei adrese la un client."<<endl;
                cout<<"Atat adresa de livrare, cat si adresa de facturare, vor fi inlocuite"<<endl;
                cout<<endl<<"Introduceti id-ul clientului pentru care doriti modificarea: ";
                cin>>cod;
                while(cod<=0)
                {
                    cout<<"Id-ul introdus nu este valid. Incercati din nou: ";
                    cin>>cod;
                }
                for(int i=0; i<=k2; i++)
                {
                    if(cod==clienti[i].getId())
                        indice=i;
                }
                cout<<endl;
                cin>>aux;
                if(indice>=0)
                {
                    clienti[indice]=clienti[indice]+aux;
                    cout<<"Adresele au fost inlocuite cu succes. Apasati orice tasta pentru a va intoarce la meniul anterior"<<endl;
                }
                else cout<<"Din pacate, nu exista clientul cu id-ul introdus.";
            }
            else cout<<"Din pacate, nu exista clienti salvati in sistem"<<endl;

            break;
        }
        case 7:
        {
            int indice=-1, cod=0;
            produs aux;
            if(k5>0)
            {
                cout<<"Ati selectat adaugarea unui produs la o comanda."<<endl;
                cout<<endl<<"Introduceti id-ul comenzii pentru care doriti modificarea: ";
                cin>>cod;
                while(cod<100000)
                {
                    cout<<"Id-ul introdus nu este valid. Incercati din nou: ";
                    cin>>cod;
                }
                for(int i=0; i<=k5; i++)
                {
                    if(cod==comenzi[i].getId())
                        indice=i;
                }
                cout<<endl;
                cin>>aux;
                if(indice>=0)
                {
                    comenzi[indice]=comenzi[indice]+aux;
                    cout<<"Produsul a fost adaugat cu succes. Apasati orice tasta pentru a va intoarce la meniul anterior"<<endl;
                }
                else cout<<"Din pacate, nu exista comanda cu id-ul introdus.";
            }
            else cout<<"Din pacate, nu exista comenzi salvate in sistem"<<endl;


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
            cout<<"Introduceti id-ul adresei de sters: ";
            cin>>cod;
            while(cod<=0)
            {
                cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                cin>>cod;
            }
            for(int i=0; i<k1; i++)
                if(cod==adrese[i].getId())
                    indice=i;
            if(indice>=0)
            {
                adr aux1;
                adrese[indice]=aux1;
            }
            else cout<<"Nu exista adresa cu id-ul introdus"<<endl;
            break;
        }
        case 2:
        {
            cout<<"Introduceti id-ul clientului de sters: ";
            cin>>cod;
            while(cod<=0)
            {
                cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                cin>>cod;
            }
            for(int i=0; i<k2; i++)
                if(cod==clienti[i].getId())
                    indice=i;
            if(indice>=0)
            {
                client aux2;
                clienti[indice]=aux2;
            }
            else cout<<"Nu exista clientul cu id-ul introdus"<<endl;
            break;
        }
        case 3:
        {
            cout<<"Introduceti id-ul firului de sters: ";
            cin>>cod;
            while(cod<1000)
            {
                cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                cin>>cod;
            }
            for(int i=0; i<k3; i++)
                if(cod==fire[i].getId())
                    indice=i;
            if(indice>=0)
            {
                fir aux3;
                fire[indice]=aux3;
                fire[indice].setDenumire(NULL);
            }
            else cout<<"Nu exista adresa cu id-ul introdus"<<endl;
            break;
        }
        case 4:
        {
            cout<<"Introduceti id-ul produsului de sters: ";
            cin>>cod;
            while(cod<10000)
            {
                cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                cin>>cod;
            }
            for(int i=0; i<k4; i++)
                if(cod==produse[i].getId())
                    indice=i;
            if(indice>=0)
            {
                produs aux4;
                produse[indice]=aux4;
                produse[indice].setNume(NULL);
            }
            else cout<<"Nu exista produsul cu id-ul introdus"<<endl;
            break;
        }
        case 5:
        {
            cout<<"Introduceti id-ul comenzii de sters: ";
            cin>>cod;
            while(cod<100000)
            {
                cout<<"Valoarea introdusa nu este corecta. Incercati din nou: ";
                cin>>cod;
            }
            for(int i=0; i<k5; i++)
                if(cod==comenzi[i].getId())
                    indice=i;
            if(indice>=0)
            {
                comanda aux5;
                client aux6;
                comenzi[indice]=aux5;
                comenzi[indice].setPersoana(aux6);
            }
            else cout<<"Nu exista adresa cu id-ul introdus"<<endl;
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
            /// Functionalitate - functie bool care verifica daca adresa e valida
            cout<<"Introduceti id-ul adresei pentru care doriti sa verificati daca este valida: ";
            cin>>cod;
            while(cod<=0)
            {
                cout<<"Id-ul introdus este invalid. Incercati din nou: ";
                cin>>cod;
            }
            if(k1>0)
            {
                for(int i=0; i<k1; i++)
                    if(cod==adrese[i].getId())
                        indice=i;
                if(indice>=0)
                {
                    if(adrese[indice].valida()==true)
                        cout<<"Adresa cu id-ul "<<cod<<" este valida!"<<endl;
                    else cout<<"Adresa cu id-ul "<<cod<<" nu este valida!"<<endl;
                }
                else cout<<"Ne pare rau, adresa cu id-ul introdus nu exista"<<endl;
            }
            else cout<<"Ne pare rau, dar nu exista adrese retinute in baza de date"<<endl;
            break;
        }
        case 2:
        {
            /// Functionalitate - verific daca un client completat integral
            cout<<"Introduceti id-ul clientului pentru care doriti sa verificati daca este completat integral: ";
            cin>>cod;
            while(cod<=0)
            {
                cout<<"Id-ul introdus este invalid. Incercati din nou: ";
                cin>>cod;
            }
            if(k2>0)
            {
                for(int i=0; i<k2; i++)
                    if(cod==clienti[i].getId())
                        indice=i;
                if(indice>=0)
                {
                    if(clienti[indice].completat()==true)
                        cout<<"Clientul cu id-ul "<<cod<<" este completat integral!"<<endl;
                    else cout<<"Clientul cu id-ul "<<cod<<" nu este completat integral!"<<endl;
                }
                else cout<<"Ne pare rau, clientul cu id-ul introdus nu exista"<<endl;
            }
            else cout<<"Ne pare rau, dar nu exista clienti retinut in baza de date"<<endl;
            break;
        }
        case 3:
        {
            /// Functionalitate - verifica daca culoarea cu codul k din fir exista sau daca e pe stoc
            /// val returnata: 2-pe stoc, 1-nu e pe stoc, 0-nu exista culoarea
            int k, returnat;
            cout<<"Introduceti id-ul firului pentru care doriti sa verificati o culoare: ";
            cin>>cod;
            while(cod<1000)
            {
                cout<<"Id-ul introdus este invalid. Incercati din nou: ";
                cin>>cod;
            }
            if(k3>0)
            {
                for(int i=0; i<k3; i++)
                    if(cod==fire[i].getId())
                        indice=i;
                if(indice>=0)
                {
                    cout<<"Introduceti codul culorii pentru care se verifica stocul: ";
                    cin>>k;
                    while(k<=0)
                    {
                        cout<<"Codul introdus este invalid. Incercati din nou: ";
                        cin>>k;
                    }
                    returnat=fire[indice].culoareValabila(k);
                    if(returnat==0)
                        cout<<"Culoarea introdusa nu exista"<<endl;
                    else if(returnat==1)
                        cout<<"Culoarea introdusa nu este pe stoc"<<endl;
                    else cout<<"Culoarea introdusa este pe stoc"<<endl;
                }
                else cout<<"Ne pare rau, adresa cu id-ul introdus nu exista"<<endl;
            }
            else cout<<"Ne pare rau, dar nu exista adrese retinute in baza de date"<<endl;
            break;
        }
        case 4:
        {
            /// Functionalitate - returnare pret dupa TVA
            cout<<"Introduceti id-ul produsului pentru care doriti sa vedeti pretul dupa TVA: ";
            cin>>cod;
            while(cod<10000)
            {
                cout<<"Id-ul introdus este invalid. Incercati din nou: ";
                cin>>cod;
            }
            if(k4>0)
            {
                for(int i=0; i<k4; i++)
                    if(cod==produse[i].getId())
                        indice=i;
                if(indice>=0)
                {
                    cout<<"Pretul produsului cu id-ul "<<cod<<" dupa aplicarea TVA-ului de 19% este "<<produse[indice].cuTVA()<<endl;
                }
                else cout<<"Ne pare rau, produsul cu id-ul introdus nu exista"<<endl;
            }
            else cout<<"Ne pare rau, dar nu exista produse retinute in baza de date"<<endl;
            break;
        }
        case 5:
        {
            /// Functionalitate - codul produsului cel mai scump, daca exista produse, -1 altfel
            cout<<"Introduceti id-ul comenzii pentru care doriti sa vedeti produsul cel mai scump: ";
            cin>>cod;
            while(cod<100000)
            {
                cout<<"Id-ul introdus este invalid. Incercati din nou: ";
                cin>>cod;
            }
            if(k5>0)
            {
                for(int i=0; i<k5; i++)
                    if(cod==comenzi[i].getId())
                        indice=i;
                if(indice>=0)
                {
                    int returnat1;
                    returnat1=comenzi[indice].scump();
                    if(returnat1>=0)
                        cout<<"Codul produsului cel mai scump din comanda cu id-ul "<<cod<<" este "<<returnat1<<endl;
                    else cout<<"Comanda nu are produse introduse";
                }
                else cout<<"Ne pare rau, comanda cu id-ul introdus nu exista"<<endl;
            }
            else cout<<"Ne pare rau, dar nu exista comenzi retinute in baza de date"<<endl;
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

void showMeniu1(int selectat1)
{
    system("cls");
    cout<<"---------- Introducere date ----------"<<endl;
    if(selectat1==1)
        cout<<"> ";
    else cout<<" ";
    cout<<"1. Adrese"<<endl;
    if(selectat1==2)
        cout<<"> ";
    else cout<<" ";
    cout<<"2. Clienti"<<endl;
    if(selectat1==3)
        cout<<"> ";
    else cout<<" ";
    cout<<"3. Fire"<<endl;
    if(selectat1==4)
        cout<<"> ";
    else cout<<" ";
    cout<<"4. Produse"<<endl;
    if(selectat1==5)
        cout<<"> ";
    else cout<<" ";
    cout<<"5. Comenzi"<<endl;
    if(selectat1==6)
        cout<<"> ";
    else cout<<" ";
    cout<<"6. Inapoi"<<endl;
    cout<<"--------------------------------------"<<endl;
}

void showMeniu2(int selectat2)
{
    system("cls");
    cout<<"---------- Afisare date ----------"<<endl;
    if(selectat2==1)
        cout<<"> ";
    else cout<<" ";
    cout<<"1. Adrese"<<endl;
    if(selectat2==2)
        cout<<"> ";
    else cout<<" ";
    cout<<"2. Clienti"<<endl;
    if(selectat2==3)
        cout<<"> ";
    else cout<<" ";
    cout<<"3. Fire"<<endl;
    if(selectat2==4)
        cout<<"> ";
    else cout<<" ";
    cout<<"4. Produse"<<endl;
    if(selectat2==5)
        cout<<"> ";
    else cout<<" ";
    cout<<"5. Comenzi"<<endl;
    if(selectat2==6)
        cout<<"> ";
    else cout<<" ";
    cout<<"6. Inapoi"<<endl;
    cout<<"----------------------------------"<<endl;
}

void showMeniu3(int selectat3)
{
    system("cls");
    cout<<"---------- Actualizare date ----------"<<endl;
    if(selectat3==1)
        cout<<"> ";
    else cout<<" ";
    cout<<"1. Adrese"<<endl;
    if(selectat3==2)
        cout<<"> ";
    else cout<<" ";
    cout<<"2. Clienti"<<endl;
    if(selectat3==3)
        cout<<"> ";
    else cout<<" ";
    cout<<"3. Fire"<<endl;
    if(selectat3==4)
        cout<<"> ";
    else cout<<" ";
    cout<<"4. Produse"<<endl;
    if(selectat3==5)
        cout<<"> ";
    else cout<<" ";
    cout<<"5. Comenzi"<<endl;
    if(selectat3==6)
        cout<<"> ";
    else cout<<" ";
    cout<<"6. Adaugare adresa la client (adresele clientului vor fi inlocuite cu aceasta)"<<endl;
    if(selectat3==7)
        cout<<"> ";
    else cout<<" ";
    cout<<"7. Adaugare produs la comanda"<<endl;
    if(selectat3==8)
        cout<<"> ";
    else cout<<" ";
    cout<<"8. Inapoi"<<endl;
    cout<<"--------------------------------------"<<endl;
}

void showMeniu4(int selectat4)
{
    system("cls");
    cout<<"---------- Stergere date ----------"<<endl;
    if(selectat4==1)
        cout<<"> ";
    else cout<<" ";
    cout<<"1. Adrese"<<endl;
    if(selectat4==2)
        cout<<"> ";
    else cout<<" ";
    cout<<"2. Clienti"<<endl;
    if(selectat4==3)
        cout<<"> ";
    else cout<<" ";
    cout<<"3. Fire"<<endl;
    if(selectat4==4)
        cout<<"> ";
    else cout<<" ";
    cout<<"4. Produse"<<endl;
    if(selectat4==5)
        cout<<"> ";
    else cout<<" ";
    cout<<"5. Comenzi"<<endl;
    if(selectat4==6)
        cout<<"> ";
    else cout<<" ";
    cout<<"6. Inapoi"<<endl;
    cout<<"-----------------------------------"<<endl;
}

void showMeniu5(int selectat5)
{
    system("cls");
    cout<<"---------- Functionalitati date ----------"<<endl;
    if(selectat5==1)
        cout<<"> ";
    else cout<<" ";
    cout<<"1. Verifica daca o adresa este valida"<<endl;
    if(selectat5==2)
        cout<<"> ";
    else cout<<" ";
    cout<<"2. Verifica daca un client este completat integral"<<endl;
    if(selectat5==3)
        cout<<"> ";
    else cout<<" ";
    cout<<"3. Verifica daca o culoare a unui fir este pe stoc"<<endl;
    if(selectat5==4)
        cout<<"> ";
    else cout<<" ";
    cout<<"4. Afisati pretul unui produs dupa aplicarea TVA-ului"<<endl;
    if(selectat5==5)
        cout<<"> ";
    else cout<<" ";
    cout<<"5. Afisati produsul cu pretul cel mai mare dintr-o comanda"<<endl;
    if(selectat5==6)
        cout<<"> ";
    else cout<<" ";
    cout<<"6. Inapoi"<<endl;
    cout<<"------------------------------------------"<<endl;
}

void mainMeniu1()
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
                        selectat1=6; // ULTIMA OPTIUNE
                    else selectat1--;
                    break;
                }
                case downkey: // jos
                {
                    if(selectat1+1>6) // ULTIMA OPTIUNE
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
                            introducereDate();
                            afisare=1;
                            optiuneMeniu1=0;
                            optiuneMain=0;
                            break;
                        }
                        case 6:
                        {
                            optiuneMeniu1=6;
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

void mainMeniu2()
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
                        selectat2=6; // ULTIMA OPTIUNE
                    else selectat2--;
                    break;
                }
                case downkey: // jos
                {
                    if(selectat2+1>6) // ULTIMA OPTIUNE
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
                            afisareDate();
                            afisare=1;
                            optiuneMeniu2=0;
                            optiuneMain=0;
                            break;
                        }
                        case 6:
                        {
                            optiuneMeniu2=6;
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

void mainMeniu3()
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
                        selectat3=8; // ULTIMA OPTIUNE
                    else selectat3--;
                    break;
                }
                case downkey: // jos
                {
                    if(selectat3+1>8) // ULTIMA OPTIUNE
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
                            actualizareDate();
                            afisare=1;
                            optiuneMeniu3=0;
                            optiuneMain=0;
                            break;
                        }
                        case 6:
                        {
                            optiuneMeniu3=6;
                            actualizareDate();
                            afisare=1;
                            optiuneMeniu3=0;
                            optiuneMain=0;
                            break;
                        }
                        case 7:
                        {
                            optiuneMeniu3=7;
                            actualizareDate();
                            afisare=1;
                            optiuneMeniu3=0;
                            optiuneMain=0;
                            break;
                        }
                        case 8:
                        {
                            optiuneMeniu3=8;
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

void mainMeniu4()
{
    // foloseste optiuneMeniu1
    int selectat4=1;
    afisare=1;
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
                        selectat4=6; // ULTIMA OPTIUNE
                    else selectat4--;
                    break;
                }
                case downkey: // jos
                {
                    if(selectat4+1>6) // ULTIMA OPTIUNE
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
                            stergereDate();
                            afisare=1;
                            optiuneMeniu4=0;
                            optiuneMain=0;
                            break;
                        }
                        case 6:
                        {
                            optiuneMeniu4=6;
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

void mainMeniu5()
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
                        selectat5=6; // ULTIMA OPTIUNE
                    else selectat5--;
                    break;
                }
                case downkey: // jos
                {
                    if(selectat5+1>6) // ULTIMA OPTIUNE
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
    return 0;
}
