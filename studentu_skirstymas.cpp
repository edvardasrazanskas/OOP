#include "Timer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

struct Studentas
{
    string vardas;
    string pavarde;
    double vidurkis;
};

void Ivestis(int kiekis, vector<Studentas> &studentai);
void Skirstymas(vector<Studentas> &geriStudentai, vector<Studentas> &blogiStudentai, vector<Studentas> &studentai);
void Isvestis(int kiekis, bool pasiseke, vector<Studentas> &studentai);

int main()
{
    Timer t;
    Timer visas_t;
    for (int i = 1000; i <= 10000000; i *= 10)
    {
        vector<Studentas> studentai(i);
        vector<Studentas> blogiStudentai(i);
        vector<Studentas> geriStudentai(i);

        visas_t.reset();
        t.reset();
        Ivestis(i, studentai);
        cout << i << " eiluciu failo nuskaitymas uztruko: " << t.elapsed() << " s\n";

        t.reset();
        Skirstymas(geriStudentai, blogiStudentai, studentai);
        cout << i << " eiluciu failo nuskaitymas skirstymas uztruko: " << t.elapsed() << " s\n";

        t.reset();
        Isvestis(i, true, geriStudentai);
        Isvestis(i, false, blogiStudentai);
        cout << i << " eiluciu failo isvedimas i du failus uztruko: " << t.elapsed() << " s\n";

        cout << "Failas su: " << i << " studentais buvo paskirstytas.\n";
        cout << i << " eiluciu failo perskirstymas i skirtingus failus uztruko: " << visas_t.elapsed() << " s\n\n\n";
    }

    system("pause");
    return 0;
}

void Skirstymas(vector<Studentas> &geriStudentai, vector<Studentas> &blogiStudentai, vector<Studentas> &studentai)
{
    for (int i = 0; i < studentai.size(); i++)
    {
        if (studentai[i].vidurkis >= 5)
        {
            geriStudentai.push_back(studentai[i]);
        }
        else
        {
            blogiStudentai.push_back(studentai[i]);
        }
    }
}

void Isvestis(int kiekis, bool pasiseke, vector<Studentas> &studentai)
{
    string OUTFILENAME;

    if (pasiseke)
        OUTFILENAME = "failai/paskirstyti/pasiseke" + to_string(kiekis) + ".txt";
    else
        OUTFILENAME = "failai/paskirstyti/nepasiseke" + to_string(kiekis) + ".txt";

    try
    {
        ofstream outfile(OUTFILENAME);

        stringstream temp_ss;

        outfile << setw(17) << left << "Pavardė" << setw(17) << "Vardas" << setw(17)
                << "Galutinis (Vid.)\n"
                << string(70, '-') << endl;

        string vardas, pavarde, eilute;

        for (int i = 0; i < kiekis; i++)
        {
            float pazymiu_suma = 0;

            // Nuskaitom ir apskaiciuojam vidurki
            stringstream eilute_stream(eilute);
            eilute_stream >> vardas >> pavarde;

            temp_ss << setw(17) << left << studentai[i].pavarde << setw(17) << studentai[i].vardas
                    << setw(17) << fixed << setprecision(2) << studentai[i].vidurkis;

            outfile.write(temp_ss.str().c_str(), temp_ss.str().size());
            outfile.write("\n", 1);

            temp_ss.str("");
        }
    }
    catch (std::exception const &e)
    {
        cout << e.what() << endl;
    }
}

void Ivestis(int kiekis, vector<Studentas> &studentai)
{
    int galutinis_balas;
    string INFILENAME = "failai/sugeneruoti/studentai" + to_string(kiekis) + ".txt";

    try
    {
        ifstream infile(INFILENAME);

        infile.rdbuf()->pubsetbuf(new char[1 << 20], 1 << 20); // Set buffer to 1 MB
        string vardas, pavarde;
        int sk[100];
        getline(infile, vardas);

        for (int i = 0; i < kiekis; i++)
        {
            float pazymiu_suma = 0;

            // Nuskaitom ir apskaiciuojam vidurki
            infile >> vardas >> pavarde;
            for (int j = 0; j < 16; j++)
            {
                infile >> sk[j];
                pazymiu_suma += sk[j];
            }
            infile >> sk[16];

            Studentas studentas{
                vardas, pavarde,
                ((pazymiu_suma / 6.4) + (sk[16] * 0.6))};

            studentai.push_back(studentas);
        }
    }
    catch (std::exception const &e)
    {
        cout << e.what() << endl;
    }
}