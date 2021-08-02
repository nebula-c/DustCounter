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

void TwoGraphs2()
{
    TCanvas *c1 = new TCanvas("c1", "ParticleCounter-Puricare",500,500);
    TPad *pad1 = new TPad("pad2","counter",.0,.5,1.,1.);
    TPad *pad2 = new TPad("pad1","puricare", 0.0,0.0,1.,0.5);
    TLegend* legend = new TLegend();
    TGraphErrors *graph11 = new TGraphErrors(); 
    TGraphErrors *graph12 = new TGraphErrors(); 
    TGraphErrors *graph13 = new TGraphErrors(); 
    TGraphErrors *graph21 = new TGraphErrors(); 
    TGraphErrors *graph22 = new TGraphErrors(); 
    TGraphErrors *graph23 = new TGraphErrors(); 
    TMultiGraph *m1 = new TMultiGraph();

    TMultiGraph *m2 = new TMultiGraph();


    fstream *thinq = new fstream();
    fstream *counter = new fstream();
    TF1 *func = new TF1("func", "[0]*x+[1]",0,50);
    
    
    //c1->SetLogy();

    string str_buf1, str_buf2;
    TString ch2Data, puricare;
    bool start = false;
    int count=0, num=0, time=0, num1=0, num2=0, num3=0;
    c1->Draw(); 
    pad1->Draw();
    pad2->Draw();


    pad1->cd();

    counter->open("./data/m_counter.csv",ios::in);
    thinq->open("./data/m_puri.csv", ios::in);

    while(!counter->eof()){
        getline(*counter,str_buf1,',');
        
        
        
        if(num<17)
        {
            graph11->SetPoint(num1,time,stod(str_buf1));
            graph11->SetPointError(num1,15,TMath::Power(stoi(str_buf1),0.5));
            num1++;
        }
        if(num>=17&num<=34)
        {
            graph12->SetPoint(num2,time,stod(str_buf1));
            graph12->SetPointError(num2,15,TMath::Power(stoi(str_buf1),0.5));
            num2++;
        }
        if(num>34)
        {
            graph13->SetPoint(num3,time,stod(str_buf1));
            graph13->SetPointError(num3,15,TMath::Power(stoi(str_buf1),0.5));
            num3++;
        }
        
            
        count = 0;
        start = false;
        num++;
        time+=30;
        if(num==num_of_data) break;

    }

    graph11->SetMarkerStyle(20);
    graph11->SetMarkerSize(0.5);    
    graph11->SetLineColor(2);
    //graph11->SetMarkerColor(2);
    //graph11->Draw("apl");

    graph12->SetMarkerStyle(20);
    graph12->SetMarkerSize(0.5);
    graph12->SetLineColor(3);
    //graph12->SetMarkerColor(3);
    //graph12->Draw("apl");

    graph13->SetMarkerStyle(20);
    graph13->SetMarkerSize(0.5);
    graph13->SetLineColor(4);
    //graph13->SetMarkerColor(4);
    //graph13->Draw("apl");

    m1->Add(graph11);
    m1->Add(graph12);
    m1->Add(graph13);
    TH1 *frame1 = m1->GetHistogram();
    frame1->SetTitle("ParticleCounter-time;time(m);ParticleCounter(PCS/m3)(PM2.5)");
    
    m1->GetXaxis()->SetLimits(0,1400);
    m1->GetXaxis()->SetRangeUser(0,1400);
    m1->GetYaxis()->SetLimits(0,150000);
    m1->GetYaxis()->SetRangeUser(0,150000);
    m1->Draw("apl");
    time=0;
    num=0;
    num1=0, num2=0, num3=0;

    pad2->cd();
    while(!thinq->eof())
    {
        getline(*thinq,str_buf2,',');
        
        
        if(num<12)
        {
            graph21->SetPoint(num1,time,stod(str_buf2));


            if(num>4&&num<17)
            {
                time+=30;
                graph21->SetPointError(num1,15,0);
            }
            else
            {
                time+=60;
                graph21->SetPointError(num1,30,0);
            }
            
            num1++;
        }

        if(num>=12&&num<24)
        {
            graph22->SetPoint(num2,time,stod(str_buf2));
            
            if(num>4&&num<17)
            {
                time+=30;
                graph22->SetPointError(num2,15,0);
            }
            else
            {
                time+=60;
                graph22->SetPointError(num2,30,0);
            }
            num2++;
        }
        if(num>=24)
        {
            graph23->SetPoint(num3,time,stod(str_buf2));
            
            graph23->SetPointError(num3,15,0);
            time+=30;
            num3++;
        }

        num++;
        if(num==num_of_data) break;    
    }
    graph21->SetMarkerStyle(20);
    graph21->SetMarkerSize(0.5);    
    graph21->SetLineColor(2);
    // graph21->Draw("apl");

    graph22->SetMarkerStyle(20);
    graph22->SetMarkerSize(0.5);
    graph22->SetLineColor(3);
    //graph22->Draw("apl");

    graph23->SetMarkerStyle(20);
    graph23->SetMarkerSize(0.5);
    graph23->SetLineColor(4);
    //graph23->Draw("apl");

    m2->Add(graph21);
    m2->Add(graph22);
    m2->Add(graph23);
    TH1 *frame2 = m2->GetHistogram();
    frame2->SetTitle("Puricare-time;time(m);Puricare(ug/m3)(PM2.5)");
        
    m2->GetXaxis()->SetLimits(0,1400);
    m2->GetXaxis()->SetRangeUser(0,1400);
    m2->GetYaxis()->SetLimits(0,20);
    m2->GetYaxis()->SetRangeUser(0,20);
    m2->Draw("apl");
    



    
    
    
    



    counter->close();
    thinq->close();    
    
}