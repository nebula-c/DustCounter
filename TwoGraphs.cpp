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
#define num_of_data 100
#define start_time 1300

using namespace std;

/*
raed data from original and CSV files
And draw each graph
*/

void TwoGraphs()
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

    counter->open("./data/counter.csv",ios::in);
    thinq->open("./data/m_puri.csv", ios::in);

    while(!counter->eof()){
        getline(*counter,str_buf1,',');
        
        
        
            
        graph1->SetPoint(num,time,stod(str_buf1));
        graph1->SetPointError(num,15,TMath::Power(stoi(str_buf1),0.5));
        cout<<TMath::Power(stoi(str_buf1),0.5)<<endl;
            
        count = 0;
        start = false;
        num++;
        time+=30;
        if(num==num_of_data) break;

    }
    graph1->SetMarkerStyle(20);
    graph1->SetMarkerSize(0.5);
    graph1->Draw("apl");
    TH1 *frame1 = graph1->GetHistogram();
    frame1->SetTitle("ParticleCounter-time;time(m);ParticleCounter(PCS/m3)(PM2.5)");
    

    time=0;
    num=0;

    pad2->cd();
    while(!thinq->eof())
    {
        getline(*thinq,str_buf2,',');
        graph2->SetPoint(num,time,stod(str_buf2));
        
        
        
        
        if(num>4&&num<17)
        {
            time+=30;
            graph2->SetPointError(num,15,0);    
        }
        else
        {
            time+=60;
            graph2->SetPointError(num,30,0);
        }
        num++;
        if(num==num_of_data) break;    
    }

    graph2->SetMarkerStyle(20);
    graph2->SetMarkerSize(0.5);
    graph2->Draw("apl");
    TH1 *frame2 = graph2->GetHistogram();
    frame2->SetTitle("Puricare-time;time(m);Puricare(ug/m3)(PM2.5)");

    graph1->GetXaxis()->SetLimits(0,1600);
    graph2->GetXaxis()->SetLimits(0,1600);
    graph2->GetXaxis()->SetRangeUser(0,1600);
    graph1->GetXaxis()->SetRangeUser(0,1600);
    counter->close();
    thinq->close();    
    
}