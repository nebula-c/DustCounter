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
#include "TH2D.h"
#include "TProfile.h"
#define entry_num 100
using namespace std;

/*
Read data from 2 CSV files
And draw 2D histogram
*/

void TH2DGraph()
{
    TCanvas *c1 = new TCanvas("c1", "ParticleCounter-Puricare(PM2.5)");
    TLegend* legend = new TLegend();
    TGraphErrors *graph1 = new TGraphErrors(); 
    const Int_t XBINS = 5; const Int_t YBINS = 5;

    TH2D *h2D = new TH2D("h2","h2;x;y",20,5,25,30,50000,150000);
    fstream *thinq = new fstream();
    fstream *counter = new fstream();
    

    TF1 *func = new TF1("func", "[0]*x+[1]",0,50);
    c1->Draw();
    //c1->SetLogy();

    string str_buf1, str_buf2;
    TString ch2Data, puricare;
    bool start = false;
    int count=0, num=0;

    counter->open("./data/counter_26_2.csv",ios::in);
    thinq->open("./data/puri_26_2.csv", ios::in);
    

    while(!counter->eof()){
        getline(*counter,str_buf1,',');
        getline(*thinq,str_buf2,',');
        puricare = str_buf2;
        graph1->SetPoint(num,stod(str_buf1),stod(str_buf2));
        h2D->Fill(stod(str_buf2),stod(str_buf1));
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
    
    // graph1->Fit("func","","",1,30);
    graph1->GetXaxis()->SetLimits(1,20);
    graph1->GetXaxis()->SetRangeUser(1,20);
    graph1->GetYaxis()->SetLimits(1,100000);
    graph1->GetYaxis()->SetRangeUser(1,100000);
    //graph1->Draw("ap");

    // TH1 *frame = graph1->GetHistogram();
    // TF1 *fitResult = graph1->GetFunction("func");
    // double_t chi2 = fitResult->GetChisquare();
    // double_t ndf = fitResult->GetNDF();
    // TString chi2_ndf = Form("chi2/ndf : %.2e/%.0f",chi2,ndf);
    // TString entry = Form("entry : %d",entry_num);

    // legend->AddEntry((TObject*)0,entry,"");
    // legend->AddEntry((TObject*)0,chi2_ndf,"");
    // legend->Draw();
    // frame->SetTitle("Puricare-ParticleCounter;Puricare(ug/m3);ParticleCounter(PCS/m3)");
    h2D->Draw("Colz");
}