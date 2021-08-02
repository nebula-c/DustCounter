#include <iostream>
#include <string>
#include <fstream>
#include "TH1D.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TString.h"
#include "TGaxis.h"
#include "TMath.h"
#include "TColor.h"
#include "TF1.h"
#include "TFitResultPtr.h"
#include "TGraphErrors.h"

using namespace std;

/*
just find std from 2 csv files
*/
void get_std()
{
    TH1D *h1 = new TH1D("name","Counter Hist;ug/m3;n",100,0,200000);
    TH1D *h2 = new TH1D("name","puri Hist;ug/m3;n",100,0,200000);
    fstream *counter = new fstream();
    fstream *puri = new fstream();
    counter->open("./data/counter_26.csv",ios::in);
    puri->open("./data/puri_26.csv",ios::in);

    string str_buf1;
    while(!counter->eof())
    {
        getline(*counter,str_buf1,',');
        h1->Fill(stod(str_buf1));
    }
    while(!puri->eof())
    {
        getline(*puri,str_buf1,',');
        h2->Fill(stod(str_buf1));
    }
    // h1->Draw();
    // h2->Draw();

    // h1->GetXaxis()->SetLimits(0,200000);
    // h1->GetXaxis()->SetRangeUser(0,200000);
    // h2->GetXaxis()->SetLimits(0,200000);
    // h2->GetXaxis()->SetRangeUser(0,200000);
    cout<<"h1 std : "<<h1->GetStdDev()<<endl;
    cout<<"h2 std : "<<h2->GetStdDev()<<endl;

    counter->close();
    puri->close();
}