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
#define num_of_data 100
using namespace std;

//3 CSV(divide from same one) and draw them

void Read2csv()
{
    TCanvas *c1 = new TCanvas("c1", "ParticleCounter-Puricare(PM2.5)");
    TLegend* legend = new TLegend();
    TGraph *graph1 = new TGraph(); 
    TGraph *graph2 = new TGraph(); 
    TGraph *graph3 = new TGraph(); 
    fstream *thinq1 = new fstream();
    fstream *thinq2 = new fstream();
    fstream *thinq3 = new fstream();
    fstream *counter1 = new fstream();
    fstream *counter2 = new fstream();
    fstream *counter3 = new fstream();
    TMultiGraph *m1 = new TMultiGraph();

    TF1 *func = new TF1("func", "[0]*x+[1]",0,50);
    c1->Draw();
    //c1->SetLogy();

    string str_buf1, str_buf2;
    TString ch2Data, puricare;
    bool start = false;
    int count=0, num=0;

    counter1->open("./data/s1_counter.csv",ios::in);
    counter2->open("./data/s2_counter.csv",ios::in);
    counter3->open("./data/s3_counter.csv",ios::in);
    thinq1->open("./data/s1_puri.csv", ios::in);
    thinq2->open("./data/s2_puri.csv", ios::in);
    thinq3->open("./data/s3_puri.csv", ios::in);

    while(!counter1->eof()){
        getline(*counter1,str_buf1,',');
        getline(*thinq1,str_buf2,',');
        puricare = str_buf2;
        graph1->SetPoint(num,stod(str_buf2),stod(str_buf1));
        //cout<<stod(str_buf1)<<endl;
        count = 0;
        start = false;    
        num++;
    }
    counter1->close();
    thinq1->close();

    while(!counter2->eof()){
        getline(*counter2,str_buf1,',');
        getline(*thinq2,str_buf2,',');
        puricare = str_buf2;
        graph2->SetPoint(num,stod(str_buf2),stod(str_buf1));
        //cout<<stod(str_buf1)<<endl;
        count = 0;
        start = false;    
        num++;
    }
    counter2->close();
    thinq2->close();

    while(!counter3->eof()){
        getline(*counter3,str_buf1,',');
        getline(*thinq3,str_buf2,',');
        puricare = str_buf2;
        graph3->SetPoint(num,stod(str_buf2),stod(str_buf1));
        cout<<stod(str_buf2)<< ","<<stod(str_buf1)<<endl;
        count = 0;
        start = false;    
        num++;
    }
    counter3->close();
    thinq3->close();

    graph1->SetMarkerStyle(20);
    graph1->SetMarkerSize(1);
    graph1->SetMarkerColor(2);
    graph2->SetMarkerStyle(20);
    graph2->SetMarkerSize(1);
    graph2->SetMarkerColor(3);
    graph3->SetMarkerStyle(20);
    graph3->SetMarkerSize(1);
    graph3->SetMarkerColor(4);
    // graph1->Draw("ap");
    
    m1->Add(graph1);
    m1->Add(graph2);
    m1->Add(graph3);
    m1->Fit("func","","",1,30);
    m1->GetXaxis()->SetLimits(1,20);
    m1->GetXaxis()->SetRangeUser(1,20);
    m1->Draw("ap");

    TH1 *frame = m1->GetHistogram();
    TF1 *fitResult = m1->GetFunction("func");
    double_t chi2 = fitResult->GetChisquare();
    double_t ndf = fitResult->GetNDF();
    TString chi2_ndf = Form("chi2/ndf : %.2e/%.0f",chi2,ndf);
    legend->AddEntry((TObject*)0,"Entry : 27","");
    legend->AddEntry((TObject*)0,chi2_ndf,"");
    legend->Draw();
    frame->SetTitle("Puricare-ParticleCounter;Puricare(ug/m3);ParticleCounter(PCS/m3)");
}