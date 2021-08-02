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
#define num_of_data 100000
#define max_time 2000
using namespace std;

/*
Read data from 2 CSV files
And draw each graphs
Mainly use it
*/
void TwoGraphs4()
{
    TCanvas *c1 = new TCanvas("c1", "ParticleCounter-Puricare",500,500);
    TPad *pad1 = new TPad("pad2","counter",.0,.5,1.,1.);
    TPad *pad2 = new TPad("pad1","puricare", 0.0,0.0,1.,0.5);
    TLegend* legend = new TLegend();
    TGraphErrors *graph1 = new TGraphErrors(); 
    TGraphErrors *graph2 = new TGraphErrors(); 
    fstream *thinq = new fstream();
    fstream *counter = new fstream();
    TF1 *func = new TF1("func", "[0]*x+[1]",0,50);
    
    
    //c1->SetLogy();

    string str_buf1, str_buf2;
    TString ch2Data, puricare;
    bool start = false;
    int count=0, num=0, time=0;
    c1->Draw(); 
    pad1->Draw();
    pad2->Draw();


    pad1->cd();

    counter->open("./final/mcounter_weak.csv",ios::in);
    thinq->open("./final/puri_weak.csv", ios::in);

    while(!counter->eof()){
        getline(*counter,str_buf1,',');
        // if(time>600&&time<700) continue;
        graph1->SetPoint(num,time,stod(str_buf1));
        // graph1->SetPointError(num,0.5,0);
        //cout<<TMath::Power(stoi(str_buf1),0.5)<<endl;
        // cout<<time<<endl;
        count = 0;
        start = false;
        num++;
        time+=10;
        
    }
    graph1->SetMarkerStyle(20);
    graph1->SetMarkerSize(0.1);
    graph1->Draw("apl");
    TH1 *frame1 = graph1->GetHistogram();
    frame1->SetTitle("particle-time;time(m);ParticleCounter(PCS/m3)(PM2.5)");
    

    time=0;
    num=0;

    pad2->cd();
    while(!thinq->eof())
    {
        getline(*thinq,str_buf2,',');
        // if(time>600&&time<700) continue;
        graph2->SetPoint(num,time,stod(str_buf2));
        time+=10;
        // graph2->SetPointError(num,0.5,0);
        
        num++;
        
    }

    graph2->SetMarkerStyle(20);
    graph2->SetMarkerSize(0.1);
    graph2->Draw("apl");
    TH1 *frame2 = graph2->GetHistogram();
    frame2->SetTitle("puricare-time;time(s);Puricare(ug/m3)(PM2.5)");

    graph1->GetXaxis()->SetLimits(0,max_time);
    graph2->GetXaxis()->SetLimits(0,max_time);
    graph1->GetXaxis()->SetRangeUser(0,max_time);
    graph2->GetXaxis()->SetRangeUser(0,max_time);
    graph2->GetYaxis()->SetLimits(0,35);
    graph2->GetYaxis()->SetRangeUser(0,35);
    
    counter->close();
    thinq->close();    
    
}