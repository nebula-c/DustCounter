#include <iostream>
#include <string>
#include <fstream>
#include "TH1.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TString.h"
#include "TGraphErrors.h"

#define max_time 2000
using namespace std;

/*
Read from 6 CSV files
And Draw 2 multigraphs
Each multigraphs has 3 graphs
*/

void MultiCompare()
{
    TCanvas *c1 = new TCanvas("c1", "ParticleCounter-Puricare",500,500);
    TPad *pad1 = new TPad("pad2","counter",.0,.5,1.,1.);
    TPad *pad2 = new TPad("pad1","puricare", 0.0,0.0,1.,0.5);
    TLegend* legend = new TLegend();
    TGraphErrors *graph1 = new TGraphErrors(); 
    TGraphErrors *graph2 = new TGraphErrors(); 
    TGraphErrors *graph3 = new TGraphErrors(); 
    TGraphErrors *graph4 = new TGraphErrors(); 
    TGraphErrors *graph5 = new TGraphErrors(); 
    TGraphErrors *graph6 = new TGraphErrors(); 
    TMultiGraph *m1 = new TMultiGraph();
    TMultiGraph *m2 = new TMultiGraph();

    fstream *puri1 = new fstream();
    fstream *puri2 = new fstream();
    fstream *puri3 = new fstream();
    fstream *counter1 = new fstream();
    fstream *counter2 = new fstream();
    fstream *counter3 = new fstream();

    string str_buf1, str_buf2, str_buf3;
    TString ch2Data;
    bool start = false;
    int count=0, num=0, time=0;
    c1->Draw(); 
    pad1->Draw();
    pad2->Draw();

    pad1->cd();

    counter1->open("./data/mcounter_29.csv",ios::in);
    puri1->open("./data/puri_29.csv", ios::in);
    counter2->open("./data/mcounter_29_3.csv",ios::in);
    puri2->open("./data/puri_29_3.csv", ios::in);
    counter3->open("./data/mcounter_30.csv",ios::in);
    puri3->open("./data/puri_30.csv", ios::in);

    while(!counter1->eof()){
        getline(*counter1,str_buf1,',');
        getline(*counter2,str_buf2,',');
        getline(*counter3,str_buf3,',');
        graph1->SetPoint(num,time,stod(str_buf1));
        graph2->SetPoint(num,time,stod(str_buf2));
        graph5->SetPoint(num,time,stod(str_buf3));
        // graph1->SetPointError(num,0.5,0);
        
        num++;
        time+=10;        
    }

    graph1->SetMarkerStyle(20);
    graph1->SetMarkerSize(0.1);
    graph1->SetLineColor(3);
    graph2->SetMarkerStyle(20);
    graph2->SetMarkerSize(0.1);
    graph2->SetLineColor(4);
    graph5->SetMarkerStyle(20);
    graph5->SetMarkerSize(0.1);
    graph5->SetLineColor(2);

    m1->Add(graph1);
    m1->Add(graph2);
    m1->Add(graph5);
    m1->Draw("apl");
    TH1 *frame1 = m1->GetHistogram();
    frame1->SetTitle("particle-time;time(s);ParticleCounter(PCS/m3)(PM2.5)");

    time=0;
    num=0;

    pad2->cd();
    while(!puri1->eof())
    {
        getline(*puri1,str_buf1,',');
        getline(*puri2,str_buf2,',');
        getline(*puri3,str_buf3,',');
        graph3->SetPoint(num,time,stod(str_buf1));
        graph4->SetPoint(num,time,stod(str_buf2));
        graph6->SetPoint(num,time,stod(str_buf3));
        // graph2->SetPointError(num,0.5,0);
        
        time+=10;
        num++;
    }

    graph3->SetMarkerStyle(20);
    graph3->SetMarkerSize(0.1);
    graph3->SetLineColor(3);
    graph4->SetMarkerStyle(20);
    graph4->SetMarkerSize(0.1);
    graph4->SetLineColor(4);
    graph6->SetMarkerStyle(20);
    graph6->SetMarkerSize(0.1);
    graph6->SetLineColor(2);

    m2->Add(graph3);
    m2->Add(graph4);
    m2->Add(graph6);
    m2->Draw("apl");
    TH1 *frame2 = m2->GetHistogram();
    frame2->SetTitle("puricare-time;time(s);Puricare(ug/m3)(PM2.5)");

    m1->GetXaxis()->SetLimits(0,max_time);
    m2->GetXaxis()->SetLimits(0,max_time);
    m1->GetXaxis()->SetRangeUser(0,max_time);
    m2->GetXaxis()->SetRangeUser(0,max_time);

    counter1->close();
    counter2->close();
    counter3->close();
    puri1->close();
    puri2->close();
    puri3->close();
}