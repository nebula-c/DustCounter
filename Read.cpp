#include <iostream>
#include <string.h>
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

using namespace std;
void Drawing_Graph(fstream* fs, TString filename,TGraph* graph_n, Color_t color);
void Drawing_wearther(TGraph *graph4, TGraph *graph5);

/*
Read data from sereral places and draw it
*/

int Read() {

    TCanvas *c1 = new TCanvas("c1", "Num of Dust");
    TLegend* legend = new TLegend();
    TGraph *graph1 = new TGraph(); 
    TGraph *graph2 = new TGraph(); 
    TGraph *graph3 = new TGraph(); 
    TGraph *graph4 = new TGraph(); 
    TGraph *graph5 = new TGraph(); 
    TGraph *graph6 = new TGraph();
    TMultiGraph *m1 = new TMultiGraph();
    // TGaxis *Yaxis = new TGaxis(1050, 0, 1050, 10000000, 0, 30, 510, "Y+");
    fstream *fs = new fstream(); 
    c1->SetGrid();
    c1->SetLogy();
    c1->Draw();

    // string str_buf;
    // TString caseNum, ch1Data, ch2Data, ch3Data;
    // bool start = false;
    // int count=0, num;

    // fs.open("20210706144741.csv",ios::in);
    
    // while(!fs.eof()){
    //     getline(fs,str_buf,',');
    //     if(str_buf == "/m3")
    //         start=true;
    //     if(start==true)
    //         count++;
    //     if(count==6)
    //     {
    //         caseNum=str_buf;
    //     }
    //     if(count==11)
    //     {
    //         ch1Data=str_buf;
    //     }
    //     if(count==13)
    //     {
    //         ch2Data=str_buf;
    //     }
    //     if(count==15)
    //     {
    //         ch3Data=str_buf;
    //         count = 0;
    //         start = false;
    //         graph1->SetPoint(caseNum.Atoi(),caseNum.Atoi(),ch1Data.Atoi());
    //         graph2->SetPoint(caseNum.Atoi(),caseNum.Atoi(),ch2Data.Atoi());
    //         graph3->SetPoint(caseNum.Atoi(),caseNum.Atoi(),ch3Data.Atoi());
    //         num++;
    //     }
        
    //     //cout<<str_buf<<endl;
    // }
    // fs.close();
    

    // Drawing_wearther(graph4,graph5);
    
    
    

    // graph1->SetMarkerColorAlpha(2,0.5);
    // graph2->SetMarkerColorAlpha(3,0.5);
    // graph3->SetMarkerColorAlpha(4,0.5);
    // graph4->SetMarkerColorAlpha(5,0.5);    
    
    // graph1->SetMarkerStyle(20);
    // graph1->SetMarkerSize(0.1);
    // graph1->SetLineColor(2);
    // graph2->SetMarkerStyle(20);
    // graph2->SetMarkerSize(0.1);
    // graph2->SetLineColor(3);
    // graph3->SetMarkerStyle(20)실
    // graph3->SetMarkerSize(0.1);
    // graph3->SetLineColor(4);
    
    Drawing_Graph(fs, "./data/20210706144755.csv", graph1, kRed);          //처장실
    Drawing_Graph(fs, "./data/20210706144750.csv", graph2, kYellow);       //동아리방
    Drawing_Graph(fs, "./data/20210706144803.csv", graph3, kGreen);        //207-1
    Drawing_Graph(fs, "./data/20210706144808.csv", graph4, kCyan);         //회의실
    Drawing_Graph(fs, "./data/20210708152557.csv", graph5, kBlue);         //복도
    Drawing_Graph(fs, "./data/20210708152603.csv", graph6, kMagenta);      //밖


    
    // m1->Add(graph1);
    // m1->Add(graph2);
    m1->Add(graph3);
    // m1->Add(graph4);
    // m1->Add(graph5);
    // m1->Add(graph6);
    // m1->SetMinimum(100);
    m1->Draw("apl");

    TH1 *frame = m1->GetHistogram();
    frame->SetTitle("Number of particle;particle size;# of particle");
    legend->AddEntry(graph1,"Prof","l");
    legend->AddEntry(graph2,"PAC","l");
    legend->AddEntry(graph3,"207-1","l");
    legend->AddEntry(graph4,"meeting room","l");
    legend->AddEntry(graph5,"corridor","l");
    legend->AddEntry(graph6,"meeting room","l");
    legend->Draw();
    // Yaxis->Draw();
    

    return 0;
}

void Drawing_Graph(fstream *fs, TString filename,TGraph *graph_n, Color_t color)
{
    string str_buf;
    TString caseNum, ch1Data, ch2Data, ch3Data;
    bool start = false;
    int count=0, num;
    TColor Color;
    
    fs->open(filename,ios::in);    
    while(!fs->eof()){
        getline(*fs,str_buf,',');
        if(str_buf == "/m3")
            start=true;
        if(start==true)
            count++;
        if(count==6)
        {
            caseNum=str_buf;
        }
        if(count==11)
        {
            ch1Data=str_buf;
        }
        if(count==13)
        {
            ch2Data=str_buf;
        }
        if(count==15)
        {
            ch3Data=str_buf;
            count = 0;
            start = false;
            graph_n->SetPoint(0,0.5,ch1Data.Atoi());
            graph_n->SetPoint(1,2.5,ch2Data.Atoi());
            graph_n->SetPoint(2,5,ch3Data.Atoi());
            num++;
            break;
        }
    }
    
    fs->close();
    
    
    graph_n->SetMarkerColorAlpha(color, 0.5);
    graph_n->SetMarkerStyle(20);
    graph_n->SetMarkerSize(1);
    graph_n->SetLineColor(color);
}

void Drawing_wearther(TGraph *graph4, TGraph *graph5)
{
    int scale = 333333;
    graph5->SetPoint(0,11,18*scale);
    graph5->SetPoint(1,71,20*scale);
    graph5->SetPoint(2,131,21*scale);
    graph5->SetPoint(3,191,17*scale);
    graph5->SetPoint(4,251,14*scale);
    graph5->SetPoint(5,311,16*scale);
    graph5->SetPoint(6,371,17*scale);
    graph5->SetPoint(7,431,20*scale);
    graph5->SetPoint(8,491,17*scale);
    graph5->SetPoint(9,551,24*scale);
    graph5->SetPoint(10,611,18*scale);
    graph5->SetPoint(11,671,15*scale);
    graph5->SetPoint(12,731,14*scale);
    graph5->SetPoint(13,791,17*scale);
    graph5->SetPoint(14,851,20*scale);
    graph5->SetPoint(15,911,23*scale);
    graph5->SetPoint(16,971,30*scale);
    
    graph5->SetMarkerStyle(20);
    graph5->SetMarkerColor(13);
    graph5->SetMarkerSize(0.5);
    graph5->SetLineColor(13);

    graph4->SetPoint(0,11,TMath::Power(10,18.*5/30+2));
    graph4->SetPoint(1,71,TMath::Power(10,20.*5/30+2));
    graph4->SetPoint(2,131,TMath::Power(10,21.*5/30+2));
    graph4->SetPoint(3,191,TMath::Power(10,17.*5/30+2));
    graph4->SetPoint(4,251,TMath::Power(10,14.*5/30+2));
    graph4->SetPoint(5,311,TMath::Power(10,16.*5/30+2));
    graph4->SetPoint(6,371,TMath::Power(10,17.*5/30+2));
    graph4->SetPoint(7,431,TMath::Power(10,20.*5/30+2));
    graph4->SetPoint(8,491,TMath::Power(10,17.*5/30+2));
    graph4->SetPoint(9,551,TMath::Power(10,24.*5/30+2));
    graph4->SetPoint(10,611,TMath::Power(10,18.*5/30+2));
    graph4->SetPoint(11,671,TMath::Power(10,15.*5/30+2));
    graph4->SetPoint(12,731,TMath::Power(10,14.*5/30+2));
    graph4->SetPoint(13,791,TMath::Power(10,17.*5/30+2));
    graph4->SetPoint(14,851,TMath::Power(10,20.*5/30+2));
    graph4->SetPoint(15,911,TMath::Power(10,23.*5/30+2));
    graph4->SetPoint(16,971,TMath::Power(10,30.*5/30+2));

    graph4->SetMarkerStyle(20);
    graph4->SetMarkerColor(1);
    graph4->SetMarkerSize(0.5);
    graph4->SetLineColor(1);
}