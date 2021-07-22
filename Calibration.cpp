#include <iostream>
#include <string>
#include <fstream>
#include "TH1.h"
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
#define num_of_data 10
using namespace std;

void Calibration()
{
    TCanvas *c1 = new TCanvas("c1", "ParticleCounter-Puricare");
    TLegend* legend = new TLegend();
    TGraph *graph1 = new TGraph(); 
    fstream *thinq = new fstream();
    fstream *counter = new fstream();
    TF1 *func = new TF1("func", "[0]*x+[1]",0,50);
    c1->Draw();
    //c1->SetLogy();

    string str_buf1, str_buf2;
    TString ch2Data, puricare;
    bool start = false;
    int count=0, num=0;

    counter->open("20210610141827.csv",ios::in);
    thinq->open("test.csv", ios::in);

    while(!counter->eof()){
        getline(*counter,str_buf1,',');
        
        if(str_buf1 == "/m3")
            start=true;
        if(start==true)
            count++;
        if(count==13)
        {
            
            if(str_buf1=="Ch2 Data")
                continue;
            getline(*thinq,str_buf2,',');
            puricare = str_buf2;
            graph1->SetPoint(num,stod(str_buf2),stod(str_buf1));
            //cout<<stod(str_buf1)<<endl;
            count = 0;
            start = false;
            
            num++;
        }
        if(count==15)
        {
            
        }

        if(num==num_of_data) break;
    }
    counter->close();
    thinq->close();

    graph1->SetMarkerStyle(20);
    graph1->SetMarkerSize(1);
    graph1->Draw("ap");
    graph1->Fit("func","","",0,30);
    //TF1 *fitResult = hist->GetFunction("func");

    TH1 *frame = graph1->GetHistogram();
    frame->SetTitle("Puricare-ParticleCounter;Puricare(ug/m3);ParticleCounter(PCS/m3)");
}