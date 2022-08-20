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
    double income;
    string label;


};


    struct Pretrazivanje {
        unordered_map<int, string> mapa;
        vector<podaci> prijenos;

        void Upari(vector<podaci> &baza) {
            int broj;
            int unos;
            vector<int> temp;
            cout << "Koliko kljuceva zelite unjeti? : ";
            cin >> broj;
            for (int i = 0; i < broj; i++) {
                cout << "Unesite " << i << ". broj:" << endl;
                cin >> unos;
                temp.push_back(unos);
            }
            for (int i = 0; i < baza.size(); i++) {
                mapa.insert(std::make_pair(i, baza[i].adresa));
            }
            for (int i = 0; i < temp.size(); i++) {
                auto search = mapa.find(temp[i]);
                std::cout << "Pronasao adresu : " << search->first << endl << "Adresa: " << search->second << endl;
            }


        };


    };


    void izracunaj(vector<podaci> baza, int napadi) {
        int temp;
        int broj = 0;
        for (int i = 0; i < baza.size(); i++) {
            if (baza[i].year == napadi) {
                broj = broj + 1;
            }
        }
        cout << "broj napada u " << napadi << " godini: " << broj << endl;

    }

    int izracunajSTL(vector<podaci> baza) {

        auto max = *std::max_element(baza.begin(), baza.end(),
                                     [](const podaci &a, const podaci &b) { return a.year < b.year; });
        return max.year;

    }

    void UMpretrazivanja(vector<podaci> baza, int broj) {
        int i = 1;
        unordered_map<int, string> map;
        map.clear();
        for (i; i < baza.size(); i++) {
            map.insert(std::make_pair(i, baza[i].adresa));
        }
        auto search = map.find(broj);
        if (search != map.end()) {
            std::cout << "Pronasao: " << search->first << endl << "Adresa: " << search->second << endl;
        } else {
            std::cout << "Nisam pronasao" << endl;
        }
        //broji od 0 , iz nekog razloga uzme i prvi red tablice zbog toga je rezultat 8 a ne 10!

    }

    void UMpretrazivanjaGodine(vector<podaci> baza, int broj) {
        int i = 0;

        unordered_multimap<int, string> temp;
        for (i; i < baza.size(); i++) {
            if (baza[i].year == broj) {
                temp.insert(std::make_pair(baza[i].year, baza[i].adresa));
            }

        }
        /*
        for (auto it = temp.cbegin(); it != temp.cend(); ++it) {
        std::cout << "{" << (*it).first << ": " << (*it).second << "}\n"; }
        */
    }

    struct sortiranjePoGodini {
        //sortiraj po godini od manjeg prema visem
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

    void izbrisiPoKljucu(int key, vector<podaci> baza) {
        int i = 0;
        unordered_multimap<int, string> map;
        map.clear();
        for (i; i < baza.size(); i++) {
            map.insert(std::make_pair(baza[i].year, baza[i].adresa));
            if (key == baza[i].year) {
                map.erase(baza[i].year);
            }
        }
        /*
        for ( auto it = map.begin(); it != map.end(); ++it )
            std::cout << " " << it->first << ":" << it->second << endl;
        */
    }


    void IzbrisiPoGodini(vector<podaci> &baza, int broj) {
        auto it = baza.begin();
        while (it != baza.end())
        {
            if (it->year ==broj)
            {
                it = baza.erase(it);
            }
            else {
                ++it;
            }
        }
    }


    void IzbrisiPoLabeluiGodini(vector<podaci> &baza, string label, int godina) {
        auto it = baza.begin();
        while (it != baza.end())
        {
            if (it->year ==godina && it->label==label)
            {
                it = baza.erase(it);
            }
            else {
                ++it;
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

                podaci unos;
                istringstream iss(line);

                getline(iss, unos.adresa, ',');

                getline(iss, token, ',');
                unos.year = std::stoi(token);

                getline(iss, token, ',');

                getline(iss, token, ',');

                getline(iss, token, ',');

                getline(iss, token, ',');

                getline(iss, token, ',');

                getline(iss, token, ',');

                getline(iss, token, ',');
                unos.income = std::stod(token);

                getline(iss, unos.label, ',');


                baza.push_back(unos);


            }
        }

        /*             //PRVA FUNKCIJA
        auto start = std::chrono::steady_clock::now();
        izracunaj(baza,2017);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "Vrijeme potrebno za pretragu : " << elapsed_seconds.count() << "s\n";
         */

        /*                //DRUGA FUNKCIJA
        auto start = std::chrono::steady_clock::now();
        int max = izracunajSTL(baza);
        cout << "Zadnji napad se desio: " << max << " godine" << endl;
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "Vrijeme potrebno za pretragu : " << elapsed_seconds.count() << "s\n";
        */

        /*     //TRECA FUNKCIJA UMpretrazivanje
       auto start1 = std::chrono::steady_clock::now();
       UMpretrazivanja(baza,10);
       auto end = std::chrono::steady_clock::now();
       std::chrono::duration<double> elapsed_seconds = end-start1;
       std::cout << "Vrijeme potrebno za pronalazak dobivenih podataka : " << elapsed_seconds.count() << "s" << endl;*/

        /*    //CETVRTA FUNKCIJA UMpretrazivanje
       auto start1 = std::chrono::steady_clock::now();
       UMpretrazivanjaGodine(baza,2018);
       auto end = std::chrono::steady_clock::now();
       std::chrono::duration<double> elapsed_seconds = end-start1;
       std::cout << "Vrijeme potrebno za pronalazak dobivenih podataka : " << elapsed_seconds.count() << "s" << endl;
        */

        /*      //PETO -->STRUKTRUA SORTIRANJE PO GODINI
       auto start1 = std::chrono::steady_clock::now();
       std::sort(baza.begin(), baza.end(), sortiranjePoGodini());
       auto end = std::chrono::steady_clock::now();
       std::chrono::duration<double> elapsed_seconds = end-start1;
       std::cout << "Vrijeme potrebno za sortiranje  podatka po godini : " << elapsed_seconds.count() << "s" << endl;
       */

        /*         // SEST0 --> STRUKTURA SORTIRANJE PO vrijednosti
        auto start1 = std::chrono::steady_clock::now();
        std::sort(baza.begin(), baza.end(), sortiranjePoVrijednosti());
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start1;
        std::cout << "Vrijeme potrebno za sortiranje  podatka po vrijednosti : " << elapsed_seconds.count() << "s" << endl;
        */

        /*      //BRISANJE PO KLJUCU
       auto start1 = std::chrono::steady_clock::now();
       izbrisiPoKljucu(2016,baza);
       auto end = std::chrono::steady_clock::now();
       std::chrono::duration<double> elapsed_seconds = end-start1;
       std::cout << "Vrijeme potrebno za brisanje zadanih kljuceva : " << elapsed_seconds.count() << "s" << endl;
       */

                //BRISANJE IZ VEC PO GODINI
       auto start1 = std::chrono::steady_clock::now();
       IzbrisiPoGodini(baza,2018);
       auto end = std::chrono::steady_clock::now();
       std::chrono::duration<double> elapsed_seconds = end-start1;
       std::cout << "Vrijeme potrebno za brisanje iz vec po godiin : " << elapsed_seconds.count() << "s" << endl;


      /*                //BRISANJE IZ VEC PO GODINI I LABELU
      auto start1 = std::chrono::steady_clock::now();
      IzbrisiPoLabeluiGodini(baza,"princetonCerber",2018);
      auto end = std::chrono::steady_clock::now();
      std::chrono::duration<double> elapsed_seconds = end-start1;
      std::cout << "Vrijeme potrebno za brisanje iz vec po godiin i labelu : " << elapsed_seconds.count() << "s" << endl;
      */

        //Pretrazivanje().Upari(baza);
        //IzbrisiPoGodini(baza,2018);
        //nesto(baza,2018);















    }

