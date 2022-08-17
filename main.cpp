#include <iostream>
#include <string>
#include <array>
using namespace std;
#include <algorithm>
#include <vector>
#include <list>
#include <forward_list>
#include <chrono>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <iomanip>

class podaci {
public:
    string adresa;
    int year;
    int day;
    int length;
    double weight;
    int count;
    int looped;
    int neighbours;
    double  income;
    string label;




};

void izracunaj(vector<podaci>baza) {
    int temp=2017; // postavljeno na 2017 jer iz nekog raloga izbaci prvi red , pa tek onda zadane vrijednosti.
    vector<podaci>tempo;
    for (int i = 0 ; i < baza.size();i++) {
        if (baza[i].year>temp) {
            temp=baza[i].year;
            tempo.push_back(baza[i]);
        }

    }
    cout << "Zadnji napad se dogodio: "  << endl;
     for (int i = 0 ; i < tempo.size();i++) {
         cout <<"Godine: "<<  tempo[i].year << endl;
         cout <<"U trajanju: "<< tempo[i].day << endl;
         cout <<"Adresa: " <<  tempo[i].adresa << endl;
         cout <<"U vrijednosti: " <<  tempo[i].income << endl;
     }


}

int izracunajSTL (vector <podaci> baza) {


    auto max = *std::max_element(baza.begin(),baza.end(),[](const podaci& a,const podaci& b) { return a.year < b.year; });
    return max.year;


}

void UMpretrazivanja(vector <podaci> baza) {
    int i = 0;
    unordered_map<int , string> map;
    map.clear();
    for ( i  ; i < baza.size();i++) {
        map.insert(std::make_pair(i,baza[i].adresa ));
    }
    auto search = map.find(10);
    if (search != map.end()) {
        std::cout << "Pronasao: " << search->first << endl <<"Adresa: " << search->second << endl;
    } else {
        std::cout << "Nisam pronasao"<< endl;
    }
    //broji od 0 , iz nekog razloga uzme i prvi red tablice zbog toga je rezultat 8 a ne 10!

}

void UMpretrazivanjaGodine(vector <podaci> baza,int broj) {
    int i = 0;

    unordered_multimap<int , string>temp;
    for ( i  ; i < baza.size();i++) {
        if (baza[i].year==broj) {
            temp.insert(std::make_pair(baza[i].year,baza[i].adresa));
        }

    }

    /*
    for (auto it = temp.cbegin(); it != temp.cend(); ++it) {
        std::cout << "{" << (*it).first << ": " << (*it).second << "}\n"; }
   */
}

void pronadiAdresu ( vector <podaci> baza , string adresa ) {
    for (int i = 0 ; i < baza.size(); i++ ) {
        if (adresa==baza[i].adresa) {
            cout << baza[i].year << endl;
            cout << baza[i].adresa << endl;
            cout << baza[i].label << endl;
        }
    }
}


struct sortiranjePoGodini {
    //sortiraj po godini od manje prema visem
    inline bool operator()(const podaci &struct1, const podaci &struct2) {
        return (struct1.year < struct2.year);
    }

};

struct sortiranjePoVrijednosti {
    //od najvece vrijednosti prema najmanjoj
    inline bool operator()(const podaci &struct1, const podaci &struct2) {
        return (struct2.income < struct1.income);
    }
};

void bubbleSort(vector <podaci>baza) {
    for (int i = 0 ; i < baza.size();i++ ) {
        int n = sizeof(baza) / sizeof(baza[0]);
        for (i = 0; i < n - 1; i++)
            for (int j = 0; j < n - i - 1; j++)
                if (baza[j].year > baza[j + 1].year)
                    swap(baza[j].year, baza[j + 1].year);
                // ovaj algoritam necemo primjeniti , buble sort se najcesce koristi za sortiranje malog broja podataka.
                //napravljeno cisto radi flexa
    }

}


// ne izbrise vrijednosti , testirao sam izbacuje i 2011 godinu
void izbrisiPoKljucu (int  key,vector <podaci> baza) {
    int i = 0;
    unordered_multimap<int , string> map;
    map.clear();
    for ( i  ; i < baza.size();i++) {
        map.insert(std::make_pair(baza[i].year,baza[i].adresa ));

    }

    if (key < baza[i].year) {
        map.erase(baza[i].year);
    }

    for ( auto it = map.begin(); it != map.end(); ++it )
        std::cout << " " << it->first << ":" << it->second << endl;

}





//quick merge kopirao s net-a neradi.
int Partition(vector<podaci> &baza, int start, int end){

    int pivot = end;
    int j = start;
    for(int i=start;i<end;++i){
        if(baza[i].year<baza[pivot].year){
            swap(baza[i].year,baza[j].year);
            ++j;
        }
    }
    swap(baza[j].year,baza[pivot].year);
    return j;

}

void Quicksort(vector<podaci> &baza, int start, int end ){

    if(start<end){

        int p = Partition(baza,start,end);
        Quicksort(baza,start,p-1);
        Quicksort(baza,p+1,end);
    }

}

void PrintVector(vector<podaci> baza){
    for(int i=0;i<baza.size();++i)
        cout<<baza[i].year<< endl ;
}


void IzbrisiPoGodini(vector <podaci> &baza , int broj) {
    for (int i = 0 ; i < baza.size();i++) {
        if (baza[i].year<=broj ) {
            baza.erase(baza.begin()+i);
        }
    }


}

void IzbrisiPoLabelu(vector <podaci> &baza , string label) {
    for (int i = 0 ; i < baza.size();i++) {
        if (baza[i].label==label ) {
            baza.erase(baza.begin()+i);
        }
    }


}








    int main() {

    vector<podaci> baza;

    fstream myFile;
    myFile.open("BitcoinHeistData.csv", ios::in);
    string line;
    string token;

    if (myFile.is_open()) {
        getline(myFile, line); // preskoci mi prvu liniju , baca error zato sto je prvi red sve tekst.

        while (getline(myFile, line)) {

            podaci Record;
            istringstream iss(line);
            getline(iss, Record.adresa, ',');
            getline(iss, token, ',');
            Record.year = std::stoi(token);

            getline(iss, token, ',');
            Record.day = std::stoi(token);

            getline(iss, token, ',');
            Record.length = std::stoi(token);

            getline(iss, token, ',');
            Record.weight = std::stod(token);

            getline(iss, token, ',');
            Record.count = std::stoi(token);

            getline(iss, token, ',');
            Record.looped = std::stoi(token);

            getline(iss, token, ',');
            Record.neighbours = std::stoi(token);

            getline(iss, token, ',');
            Record.income = std::stod(token);

            getline(iss, Record.label, ',');

            baza.push_back(Record);

        }
    }

    /*

    auto start = std::chrono::steady_clock::now();
    izracunaj(baza);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Vrijeme potrebno za pretragu zadnjeg napada: " << elapsed_seconds.count() << "s\n";

    */

    /*

    auto start1 = std::chrono::steady_clock::now();
    int max = izracunajSTL(baza);
    cout << "Zadnji napad se desio: " << max << " godine" << endl;
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start1;
    std::cout << "Vrijeme potrebno za pretragu zadnjeg napada STL funkcijom : " << elapsed_seconds.count() << "s" << endl;

     */

    /*
    // PRETRAZIVANJE UM PREKO INT KLJUCA
    auto start1 = std::chrono::steady_clock::now();
    UMpretrazivanja(baza);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start1;
    std::cout << "Vrijeme potrebno za pronalazak podatka : " << elapsed_seconds.count() << "s" << endl;
     */
     //pronadiAdresu(baza,"1JuG8h5NApNLyHSE6tUUEuDijrf2wXSxxj");

     /*
     auto start1 = std::chrono::steady_clock::now();
     UMpretrazivanjaGodine(baza,2016);
     pronadiAdresu(baza,"1JuG8h5NApNLyHSE6tUUEuDijrf2wXSxxj");
     auto end = std::chrono::steady_clock::now();
     std::chrono::duration<double> elapsed_seconds = end-start1;
     std::cout << "Vrijeme potrebno za pronalazak dobivenih podataka : " << elapsed_seconds.count() << "s" << endl;
      */

     /*
        auto start1 = std::chrono::steady_clock::now();
        std::sort(baza.begin(), baza.end(), sortiranjePoVrijednosti());
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start1;
        std::cout << "Vrijeme potrebno za sortiranje  podatka po vrijednosti : " << elapsed_seconds.count() << "s" << endl;
     */

     /*
        auto start1 = std::chrono::steady_clock::now();
        std::sort(baza.begin(), baza.end(), sortiranjePoGodini());
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start1;
        std::cout << "Vrijeme potrebno za sortiranje  podatka po vrijednosti : " << elapsed_seconds.count() << "s" << endl;

      */

     /*
       Quicksort(baza,0,baza.size()-1);
        PrintVector(baza);
        */

     // izbrisiPoKljucu(2016,baza);
        IzbrisiPoGodini(baza,2018);
        PrintVector(baza);
        //IzbrisiPoLabelu(baza,"princetonCerber");




return 0; }
