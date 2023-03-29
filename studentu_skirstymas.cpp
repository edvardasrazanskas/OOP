#include "Timer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

void IvestisIsvestis(int kiekis);


int main()
{
    Timer t;
    for(int i=1000; i<=10000000; i*=10){
        t.reset();
        IvestisIsvestis(i);
        cout << "Failas su: " << i << " studentais buvo paskirstytas.\n";
        cout << i << " eiluciu failo perskirstymas i skirtingus failus uztruko: " << t.elapsed() << " s\n";
    }

    system("pause");
    return 0;
}


void IvestisIsvestis(int kiekis)
{
    int galutinis_balas;
    float sk[16];
    string INFILENAME = "failai/sugeneruoti/studentai" + to_string(kiekis) + ".txt";
    string OUTFILENAME_5 = "failai/paskirstyti/nepasiseke" + to_string(kiekis) + ".txt";
    string OUTFILENAME_10 = "failai/paskirstyti/pasiseke" + to_string(kiekis) + ".txt";

    try{
        ifstream infile(INFILENAME);
        ofstream outfile5(OUTFILENAME_5);
        ofstream outfile10(OUTFILENAME_10);

        stringstream temp_ss;




        outfile5 << setw(17) << left << "Pavardė" << setw(17) << "Vardas" << setw(17)
                << "Galutinis (Vid.)\n" << string(70, '-') << endl;
        outfile10 << setw(17) << left << "Pavardė" << setw(17) << "Vardas" << setw(17)
                << "Galutinis (Vid.)\n" << string(70, '-') << endl;

        string vardas, pavarde, eilute;
        getline(infile, eilute);

        for(int i=0; i<kiekis; i++)
        {
            float pazymiu_suma = 0;

            // Nuskaitom ir apskaiciuojam vidurki
            getline(infile, eilute);
            stringstream eilute_stream(eilute);
            eilute_stream >> vardas >> pavarde;

            for(int j=0; j<15; j++){
                eilute_stream >> sk[j];
                pazymiu_suma += sk[j];
            }
            eilute_stream >> sk[15];

            galutinis_balas = (pazymiu_suma/15 * 0.4) + (sk[15] * 0.6);

            temp_ss << setw(17) << left << pavarde << setw(17) << vardas 
                << setw(17) << fixed << setprecision(2) << galutinis_balas;
            
            if(galutinis_balas < 5.0){
                outfile5.write(temp_ss.str().c_str(), temp_ss.str().size());
                outfile5.write("\n", 1);
            } else {
                outfile10.write(temp_ss.str().c_str(), temp_ss.str().size());
                outfile10.write("\n", 1);
            }

            temp_ss.str("");
        }
    } catch(std::exception const& e){
        cout << e.what() << endl;
    }
}