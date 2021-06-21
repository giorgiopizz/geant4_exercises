/*
   c++ -o analyseMaterial analyseMaterial.cpp `root-config --cflags --glibs` -lm
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>

#include "TStyle.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TAxis.h"
#include "TFitResult.h"
#include "TMatrixDSym.h"
#include "TMath.h"
#include "TFile.h"
// #include "../lib/CfgParser.h"

using namespace std;

//background shoul be 2*r_start*r_stop*(10e-6)/bins*T_measure


#define TOT 1

string trimTitle (const string & title){
    string result = title;
    while (result.find(" ") != string::npos){
        result.erase(result.find(" "), 1);
    }
    return result;
}

int main(int argc, char** argv)
{
        TFile * file;
        if (argc<2){
            file = new TFile("AnaEx02.root");
        }
        else{
            file = new TFile(argv[1]);
        }





        TApplication* myApp = new TApplication("myApp", NULL, NULL);


        TH1D * h = (TH1D *)file->Get("histo_tot");
        h->Rebin();
        #ifdef AL
            TF1* func = new TF1("fun", "[0]*TMath::Exp(-x[0]/[1]) +  [2]*TMath::Exp(-x[0]/[3]) + [4]",0.2, 11);
            TCanvas* cnv = new TCanvas("myC1","myC1",10,10,1200,800);

            func->SetParName(0,"#N_mu^-");
            func->SetParameter(0,10000.);
            func->SetParLimits(0,0,1000000);
            func->SetParName(1,"#tau_mu^-");
            func->FixParameter(1,0.88);
            func->SetParName(2,"#N_mu^+");
            func->SetParLimits(2,0,1000000);
            func->SetParameter(2,20000);
            func->SetParName(3,"#tau_mu^+");
            func->FixParameter(3,2.197);
            func->SetParName(4,"Bkg");
            func->FixParameter(4,0);

            gStyle->SetOptStat(11);
            gStyle->SetOptFit(1111);

            cnv->cd();
            h->Draw();
            h->Fit(func,"R  ");
            TF1 * func2 = new TF1("fun1", "[0]*TMath::Exp(-x[0]/[1]) +  [2]*TMath::Exp(-x[0]/[3]) + [4]",0.3, 11);

            double tot = func->GetParameter(0) + func->GetParameter(2);
            func2->FixParameter(0,0.46*tot);
            func2->FixParameter(2,0.54*tot);

            func2->SetParName(0,"#N_mu^-");
            func2->SetParName(1,"#tau_mu^-");
            func2->SetParameter(1,0.88);
            func2->SetParName(2,"#N_mu^+");
            func2->SetParName(3,"#tau_mu^+");
            func2->FixParameter(3,2.197);
            func2->SetParName(4,"Bkg");
            func2->FixParameter(4,0);



            // func->ReleaseParameter(3);
            h->Fit(func2, "R");
            cout << "Tau: " << func2->GetParameter(1) << " ± " << func2->GetParError(1) << endl;
            cnv->Modified();
            cnv->Update();
            cnv->SaveAs("simAl.png");
        #endif

        #ifdef NACL
            TF1* func = new TF1("fun", "[0]*TMath::Exp(-x[0]/[1]) +  [2]*TMath::Exp(-x[0]/[3]) + [4]",0.33, 11);
            TCanvas* cnv = new TCanvas("myC1","myC1",10,10,1200,800);

            func->SetParName(0,"#N_mu^-");
            func->SetParameter(0,10000.);
            func->SetParLimits(0,0,1000000);
            func->SetParName(1,"#tau_mu^-");
            func->FixParameter(1,0.75);
            func->SetParName(2,"#N_mu^+");
            func->SetParLimits(2,0,1000000);
            func->SetParameter(2,20000);
            func->SetParName(3,"#tau_mu^+");
            func->FixParameter(3,2.197);
            func->SetParName(4,"Bkg");
            func->FixParameter(4,0);

            gStyle->SetOptStat(11);
            gStyle->SetOptFit(1111);

            cnv->cd();
            h->Draw();
            h->Fit(func,"R");

            double tot = func->GetParameter(0) + func->GetParameter(2);
            func->FixParameter(0,0.46*tot);
            func->FixParameter(2,0.54*tot);
            func->ReleaseParameter(1);

            // func2->SetParName(0,"#N_mu^-");
            // func2->SetParName(1,"#tau_mu^-");
            // func2->SetParameter(1,0.75);
            // func2->SetParName(2,"#N_mu^+");
            // func2->SetParName(3,"#tau_mu^+");
            // func2->FixParameter(3,2.197);
            // func2->SetParName(4,"Bkg");
            // func2->FixParameter(4,0);



            // func->ReleaseParameter(3);

            h->Fit(func, "R");
            cout << "Tau: " << func->GetParameter(1) << " ± " << func->GetParError(1) << endl;
            cnv->Modified();
            cnv->Update();
            cnv->SaveAs("simNaCl.png");
        #endif

        #ifdef C
            TF1* func = new TF1("fun", "[0]*TMath::Exp(-x[0]/[1]) +  [2]*TMath::Exp(-x[0]/[3]) + [4]",0.33, 11);
            TCanvas* cnv = new TCanvas("myC1","myC1",10,10,1200,800);

            func->SetParName(0,"#N_mu^-");
            func->SetParameter(0,10000.);
            func->SetParLimits(0,0,1000000);
            func->SetParName(1,"#tau_mu^-");
            func->FixParameter(1,2.06);
            func->SetParName(2,"#N_mu^+");
            func->SetParLimits(2,0,1000000);
            func->SetParameter(2,20000);
            func->SetParName(3,"#tau_mu^+");
            func->FixParameter(3,2.197);
            func->SetParName(4,"Bkg");
            func->FixParameter(4,0);

            gStyle->SetOptStat(11);
            gStyle->SetOptFit(1111);

            cnv->cd();
            h->Draw();
            h->Fit(func,"R");

            double tot = func->GetParameter(0) + func->GetParameter(2);
            func->FixParameter(0,tot);
            func->FixParameter(2,0);
            func->ReleaseParameter(1);

            // func2->SetParName(0,"#N_mu^-");
            // func2->SetParName(1,"#tau_mu^-");
            // func2->SetParameter(1,0.75);
            // func2->SetParName(2,"#N_mu^+");
            // func2->SetParName(3,"#tau_mu^+");
            // func2->FixParameter(3,2.197);
            // func2->SetParName(4,"Bkg");
            // func2->FixParameter(4,0);



            // func->ReleaseParameter(3);

            h->Fit(func, "R");
            cout << "Tau: " << func->GetParameter(1) << " ± " << func->GetParError(1) << endl;
            cnv->Modified();
            cnv->Update();
            cnv->SaveAs("simCarbon.png");
        #endif

        #ifdef TOT
            TF1* func = new TF1("fun", "[0]*TMath::Exp(-x[0]/[1]) + [2]",0.33, 11);
            TCanvas* cnv = new TCanvas("myC1","myC1",10,10,1200,800);

            func->SetParName(0,"#N");
            func->SetParameter(0,10000.);
            func->SetParLimits(0,0,1000000);
            func->SetParName(1,"#tau_mu");
            func->SetParameter(1,2.10);
            func->SetParName(2,"Bkg");
            func->SetParameter(2,0);
            func->SetParLimits(2, 0,1000);

            gStyle->SetOptStat(11);
            gStyle->SetOptFit(1111);

            cnv->cd();
            h->Draw();
            h->Fit(func,"R");

            // double tot = func->GetParameter(0) + func->GetParameter(2);
            // func->FixParameter(0,tot);
            // func->FixParameter(2,0);
            // func->ReleaseParameter(1);

            // func2->SetParName(0,"#N_mu^-");
            // func2->SetParName(1,"#tau_mu^-");
            // func2->SetParameter(1,0.75);
            // func2->SetParName(2,"#N_mu^+");
            // func2->SetParName(3,"#tau_mu^+");
            // func2->FixParameter(3,2.197);
            // func2->SetParName(4,"Bkg");
            // func2->FixParameter(4,0);



            // func->ReleaseParameter(3);

            // h->Fit(func, "R");
            cout << "Tau: " << func->GetParameter(1) << " ± " << func->GetParError(1) << endl;
            cnv->Modified();
            cnv->Update();
            cnv->SaveAs("simTot.png");
        #endif

        myApp->Run();

        // CfgParser * gConfigParser = new CfgParser (config_file);
        // string name = gConfigParser->readStringOpt("general::name");
        //
        // int function_type = gConfigParser->readIntOpt (name+"::f_type");
        //
        //
        // string filename = gConfigParser->readStringOpt(name+"::filename");
        //
        // string title = gConfigParser->readStringOpt(name+"::title");
        //
        // int save = gConfigParser->readIntOpt(name+"::save");
        // int fix = gConfigParser->readIntOpt(name+"::fix");
        // vector<float> parameters = gConfigParser->readFloatListOpt (name+"::parameters");
        //
        // vector<float> range = gConfigParser->readFloatListOpt (name+"::range");
        // float bin = gConfigParser->readFloatOpt (name+"::bin");
        // //int search = gConfigParser->readIntOpt (name+"::search");
        //
        //
        //
        //
        // TCanvas* cnv = new TCanvas("myC1","myC1",10,10,1200,800);
        // gStyle->SetOptStat(11);
        // gStyle->SetOptFit(1111);
        // //TF1 * func = new TF1("fun", "[0]*TMath::Exp(-x[0]/[1])",0.5, 10);
        // TF1 * func;
        // if(function_type==1){
        //     func = new TF1("fun", "[0]*TMath::Exp(-x[0]/[1]) + [2]",range[0], range[1]);
        //
        // }
        // else if(function_type==2){
        //     func = new TF1("fun", "[0]*TMath::Exp(-x[0]/[1]) +  [2]*TMath::Exp(-x[0]/[3])+ [4]",range[0], range[1]);
        // }
        // else if(function_type==3){
        //
        // }
        //         // double neg_muon = 5164*0.44;
        // // double pos_muon = 5164*0.56;
        // // double neg_tau = 2.005;
        // // double pos_tau = 2.2;
        // // func->SetParameter(0, neg_muon);
        // // func->SetParLimits(0, neg_muon-0.1*neg_muon,neg_muon+0.1*neg_muon);
        // // func->SetParameter(1, neg_tau);
        // // func->SetParLimits(1, neg_tau-neg_tau*0.05,neg_tau+neg_tau*0.05);
        // // func->SetParameter(2, pos_muon);
        // // func->SetParLimits(2, pos_muon-0.1*pos_muon,pos_muon+0.1*pos_muon);
        // // func->SetParameter(3, pos_tau);
        // // func->SetParLimits(3, pos_tau-pos_tau*0.05,pos_tau+pos_tau*0.05);
        // // func->SetParameter(4, 386);
        // vector<string>  names;
        // string n1[] = {"N", "\\tau_{\\mu}", "Bkg"};
        // string n2[] = {"N_{-}", "\\tau_{\\mu^-}","N_{+}", "\\tau_{\\mu^+}", "Bkg"};
        // string n3[] = {"N","A", "\\tau_{\\mu^-}", "\\tau_{\\mu^+}", "Bkg"};
        // if (function_type==1){
        //     for (int i=0;i<3;i++)   names.push_back(n1[i]);
        //     cout << "minor" <<endl;
        // }
        // else if (function_type==2){
        //     for (int i=0;i<5;i++)   names.push_back(n2[i]);
        // }
        // else if (function_type==3){
        //     for (int i=0;i<5;i++)   names.push_back(n3[i]);
        // }
        //
        //
        // for (int i=0; i<parameters.size(); i++) {
        //
        //         func->SetParameter(i, parameters[i]);
        //         func->SetParName(i, names[i].c_str());
        // }
        //
        // if (fix){
        //     func->FixParameter(3, 2.197);
        // }
        //
        // TH1F *h = new TH1F("h", "example histogram",bin,0,11);
        // cnv->SetGridx();
        // cnv->SetGridy();
        // h->GetYaxis()->SetTitle("Counts");
        // h->GetXaxis()->SetTitle("#Delta (t)[#mu s]");
        // ifstream inp;
        // double x;
        // inp.open(filename);
        // while(!(inp >> x)==0) {h->Fill(x);}
        // cnv->cd();
        // h->Draw();
        //
        // if (name == "cerbero_sopra_new_CORR_down_two_exp"){
        //
        //     func->SetParameter(0, h->GetMaximum());
        //     func->SetParLimits(0,h->GetMaximum()*0.8, h->GetMaximum()*1.2 );
        //
        //     func->SetParameter(1, 0.55);
        //     func->SetParLimits(1, 0, 1);
        //     func->SetParLimits(4, 0, 10000);
        //     // for (int i=0;i<500;i++){
        //     //     func->ReleaseParameter(0);
        //     //     func->ReleaseParameter(1);
        //     //     func->SetParLimits(1, 0, 1);
        //     //     func->ReleaseParameter(2);
        //     //     func->ReleaseParameter(3);
        //     //
        //     //
        //     //     func->FixParameter(2, 2.026+(i-250)*0.004);
        //     //     func->FixParameter(3, 2.197);
        //     //
        //     //     // func->SetParLimits(4,0,100000);
        //     //     // func->FixParameter(1, 2.026);
        //     //     // func->FixParameter(3, 2.197);
        //     //
        //     //     h->Fit("fun","RQ");
        //     //     func->FixParameter(0, func->GetParameter(0));
        //     //     func->FixParameter(4, func->GetParameter(4));
        //     //
        //     //     func->ReleaseParameter(2);
        //     //     func->SetParLimits(2, 0, 3.1);
        //     //
        //     //     TFitResultPtr r = h->Fit("fun","SRQ");
        //     //     double tau_minus = func->GetParameter(2);
        //     //     cout << 2.026+(i-250)*0.004 << "\t" << tau_minus << endl;
        //     // }
        //     //
        //     // func->ReleaseParameter(0);
        //     // func->ReleaseParameter(1);
        //     // func->SetParLimits(1, 0, 1);
        //     // func->ReleaseParameter(2);
        //     // func->ReleaseParameter(3);
        //
        //     func->SetParameter(1, 0.54);
        //     func->SetParLimits(1, 0.50, 0.6);
        //     func->SetParameter(2, 2.026);
        //     func->SetParLimits(2, 0, 3.1);
        //     func->FixParameter(3, 2.197);
        //
        //     // func->SetParLimits(4,0,100000);
        //     // func->FixParameter(1, 2.026);
        //     // func->FixParameter(3, 2.197);
        //
        //     // h->Fit("fun","RQ");
        //     // func->FixParameter(0, func->GetParameter(0));
        //     // func->FixParameter(4, func->GetParameter(4));
        //     //
        //     // func->ReleaseParameter(2);
        //
        //     // TFitResultPtr r = h->Fit("fun","SRQ");
        //     // double tau_minus = func->GetParameter(2);
        //     // cout << 2.026+(i-250)*0.004 << "\t" << tau_minus << endl;
        //
        //
        //
        //     // func->ReleaseParameter(1);
        //     // // func->ReleaseParameter(3);
        //     // func->FixParameter(0, func->GetParameter(0));
        //     // // func->SetParameter(1, func->GetParameter(1));
        //     // func->FixParameter(2, func->GetParameter(2));
        //     // // func->SetParameter(3, func->GetParameter(3));
        //     // func->FixParameter(4, func->GetParameter(4));
        //     // // func->SetParLimits(0,0,100000);
        //     // // func->SetParLimits(2,0,100000);
        //     // // TFitResultPtr r = h->Fit("fun","SR");
        //     // // h->SetTitle((title + "mu+").c_str());
        //     // // cnv->Modified();
        //     // // cnv->Update();
        //     // //
        //     // // if (save == 1) cnv->Print(("images/"+trimTitle(title)+"_muplus.png").c_str(), "png");
        //     // // double n_plus =  func->GetParameter(2);
        //     // // double tau_plus = func->GetParameter(3);
        //     // // double n_plus_err = r->ParError(2);
        //     // // double tau_plus_err = r->ParError(3);
        //     //
        //     //
        //     //
        //     // func->ReleaseParameter(0);
        //     // // func->ReleaseParameter(2);
        //     // func->ReleaseParameter(4);
        //     //
        //     // // func->SetParameter(0, func->GetParameter(0));
        //     // // func->SetParameter(1, func->GetParameter(1));
        //     // // func->SetParameter(2, func->GetParameter(2));
        //     // // func->FixParameter(3, func->GetParameter(3));
        //     TFitResultPtr r = h->Fit("fun","SR");
        //     h->SetTitle((title + "mu-").c_str());
        //     cnv->Modified();
        //     cnv->Update();
        //
        //     if (save == 1) cnv->Print(("images/"+trimTitle(title)+"_muminus.png").c_str(), "png");
        //
        //
        //     double n_minus =  func->GetParameter(0);
        //     double tau_minus = func->GetParameter(1);
        //     double n_minus_err = r->ParError(0);
        //     double tau_minus_err = r->ParError(1);
        //
        //
        //     // cout << "N + ricavato: " << n_plus << " ± " << n_plus_err <<endl;
        //     // cout << "tau + ricavato: " << tau_plus << " ± " << tau_plus_err <<endl;
        //
        //     cout << "N - ricavato: " << n_minus << " ± " << n_minus_err <<endl;
        //     cout << "tau - ricavato: " << tau_minus << " ± " << tau_minus_err <<endl;
        //
        //     // cout << "N - ricavato: " << func->GetParameter(0) <<endl;
        //     // cout << "tau - ricavato: " << func->GetParameter(1) <<endl;
        // }
        // else{
        //     TFitResultPtr r = h->Fit("fun","SR");
        //
        //     double tot = func->GetParameter(0)+func->GetParameter(2);
        //     double prop = func->GetParameter(0)/tot*100;
        //     cout << "proprorzioni:\nneg: " << prop << "\npos: " << 100-prop <<endl;
        //
        //     cout << "Vita media: " << func->GetParameter(1) << " microsec ± " <<  r->ParError(1) <<endl;
        //     cout << "errore percentuale: " << r->ParError(1)/func->GetParameter(1) * 100 << endl;
        //     double tau = 2.1969811;
        //     double t = abs(tau-func->GetParameter(1))/r->ParError(1);
        //     cout << "t: " << t <<endl;
        //
        //     h->SetTitle(title.c_str());
        //     cnv->Modified();
        //     cnv->Update();
        //
        //     if (save == 1) cnv->Print(("images/"+trimTitle(title)+".png").c_str(), "png");
        //
        // }
        //
        // /*stringstream s;
        // s << "Vita media: " << round(func->GetParameter(1)*1000)/1000 << " +/- " <<  round(r->ParError(1)*1000)/1000 << " microsec. t: " << round(t*1000)/1000;
        // h->SetTitle(s.str().c_str());
        // */
        //
        // myApp->Run();
        return 0;
}
