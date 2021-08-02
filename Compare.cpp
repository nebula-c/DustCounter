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
#include "TGraphErrors.h"

using namespace std;

/*
draw correlation and fit it
read from two csv files
*/

void Compare()
{
    TCanvas *c1 = new TCanvas("c1", "ParticleCounter-Puricare(PM2.5)");
    TLegend* legend = new TLegend();
    TGraphErrors *graph1 = new TGraphErrors(); 
    fstream *thinq = new fstream();
    fstream *counter = new fstream();
    

    TF1 *func = new TF1("func", "[0]*x+[1]",0,50);
    c1->Draw();
    //c1->SetLogy();

    string str_buf1, str_buf2;
    TString ch2Data, puricare;
    bool start = false;
    int count=0, num=0;

    counter->open("./data/total_counter.csv",ios::in);
    thinq->open("./data/total_puri.csv", ios::in);
    

    while(!counter->eof()){
        getline(*counter,str_buf1,',');
        getline(*thinq,str_buf2,',');
        puricare = str_buf2;
        graph1->SetPoint(num,stod(str_buf2),stod(str_buf1));
        // cout<<stod(str_buf2)<<", "<<stod(str_buf1)<<endl;
        // graph1->SetPointError(num,0.5,,0.5));
        count = 0;
        start = false;    
        num++;
    }
    counter->close();
    thinq->close();
    
    graph1->SetMarkerStyle(20);
    graph1->SetMarkerSize(0.5);
    
        
    graph1->Fit("func","","",1,30);
    graph1->GetXaxis()->SetLimits(5,150);
    graph1->GetXaxis()->SetRangeUser(1,150);
    graph1->GetYaxis()->SetLimits(1,2500000);
    graph1->GetYaxis()->SetRangeUser(1,2500000);
    graph1->Draw("ap");

    TH1 *frame = graph1->GetHistogram();
    TF1 *fitResult = graph1->GetFunction("func");
    double_t chi2 = fitResult->GetChisquare();
    double_t ndf = fitResult->GetNDF();
    TString chi2_ndf = Form("chi2/ndf : %.2e/%.0f",chi2,ndf);
    TString entry = Form("entry : %d",num);

    legend->AddEntry((TObject*)0,entry,"");
    legend->AddEntry((TObject*)0,chi2_ndf,"");
    legend->Draw();
    frame->SetTitle("Puricare-ParticleCounter;Puricare(ug/m3);ParticleCounter(PCS/m3)");
}