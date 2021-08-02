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
#define num_of_data 2000
#define max_time 2000
using namespace std;

/*
Read data from original and CSV files
and draw
*/

void TwoGraphs5()
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
    TString ch2Data;
    int puricare;
    bool start = false;
    int count=0, num=0, time=0;
    c1->Draw(); 
    pad1->Draw();
    pad2->Draw();


    pad1->cd();     

    counter->open("./data.counter_28.csv",ios::in);
    thinq->open("./data/puri_27_2.csv", ios::in);

    while(!counter->eof())
    {
        
        getline(*counter,str_buf1,',');
        if(str_buf1 == " Ch2 Data")
        {
            continue;
            count=0;
        }
        if(str_buf1 == "/m3")
            start=true;
        if(start==true)
            count++;
        if(count==13)
        {
            puricare=stoi(str_buf1);
        }
        if(count==15)
        {
            puricare-=stoi(str_buf1);
            graph1->SetPoint(num,time,puricare);
            cout<<puricare<<endl;
            count = 0;
            start = false;
            num++;
            time+=10;
        }


    }
    graph1->SetMarkerStyle(20);
    graph1->SetMarkerSize(0.1);
    graph1->Draw("apl");
    TH1 *frame1 = graph1->GetHistogram();
    frame1->SetTitle("2Puricare-time;time(m);ParticleCounter(PCS/m3)(PM2.5)");
    

    time=0;
    num=0;

    pad2->cd();
    while(!thinq->eof())
    {
        getline(*thinq,str_buf2,',');
        graph2->SetPoint(num,time,stod(str_buf2));
        time+=10;
        // graph2->SetPointError(num,0.5,0);
        
        num++;
        if(num==num_of_data) break;    
    }

    graph2->SetMarkerStyle(20);
    graph2->SetMarkerSize(0.1);
    graph2->Draw("apl");
    TH1 *frame2 = graph2->GetHistogram();
    frame2->SetTitle("2ParticleCounter-time;time(m);Puricare(ug/m3)(PM2.5)");

    graph1->GetXaxis()->SetLimits(0,max_time);
    graph2->GetXaxis()->SetLimits(0,max_time);
    graph1->GetXaxis()->SetRangeUser(0,max_time);
    graph2->GetXaxis()->SetRangeUser(0,max_time);
    counter->close();
    thinq->close();    
    
}