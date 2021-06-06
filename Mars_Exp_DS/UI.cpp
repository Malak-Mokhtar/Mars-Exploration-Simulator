#pragma once
#include"priorityQueue.h"
#include"Queue.h"
#include"UI.h"
#include <iostream>
#include <fstream>
#include <string>
#include"Mission.h"
#include"Rover.h"
#include"FormulationEvent.h"
#include"priorityQueue.h"
#include"windows.h"
#include "MarsStation.h"

using namespace std;


UI::UI(MarsStation* st)
{
    obj = st;
}

void UI::input_contents_console(string i_file)
{
    string line;
    ifstream fptr(i_file);
    if (fptr.is_open())
    {
        while (getline(fptr, line))
        {
            cout << line << '\n';
        }
        fptr.close();
    }
    else 
    {
        cout << "Unable to open file";
    }
}

void UI::r_input()
{
    string i_file = "input_info.txt";
    ifstream fptr;
    //Check if input of file name is correct and in directory
    /*do 
    {
        cout << "(Please include file extension)\nEnter input file name: ";
        cin >> i_file;
        fptr.open(i_file);
        cout << "\nError! Unable to open input file successfully.\n\n";
    } while (fptr.fail());*/
    fptr.open(i_file);
    system("CLS");

    //Input file name is correct 
    if (fptr.is_open())
    {
        cout << "File opened successfully...\nFile Contents...\n\n";
        input_contents_console(i_file);
        cout << "\nPress any key to continue...\n\n";
        while (cin.get() && !fptr.eof())
        {
            char event_type; //Event type (formulation, cancellation, promotion)
            char rover_type; //Type of rover (mountainous, polar, emergency)
            int event_day; //Event day
            int ID; //Mission ID
            int tloc; //Target Location
            int mdur; //Mission Duration
            int sig; //Mission Significance

            //Read input in variables
            fptr >>
                num_pr >> num_er >>
                pr_sp >> er_sp >>
                num_missions >> pr_ch >> er_ch >>
                no_events;

            PriorityQueue<Mission*>*  EM;
            LinkedQueue<Mission*>*  PM;
            LinkedQueue<Event*>* EV = obj->GetEV();
            for (int i = 0; i <= no_events; i++)
            {
                fptr >> event_type >> rover_type >> event_day >> ID >> tloc >> mdur >> sig;

                if (event_type == 'F')
                {
                    EM = obj->GetEM();
                    PM = obj->GetPM();
                    Event* f = new FormulationEvent(rover_type, event_day, ID, tloc, mdur, sig, EM, PM);
                    EV->enqueue(f);
                }
            }
            obj->setEV(EV);
            for (int i = 0; i < num_er; i++)
            {
                Rover* er = new Rover(rover_type, er_sp, er_ch, num_missions);
                er->setStatus('A');
                er->setID(rID);
                rID++;
                obj->GetER()->enqueue(er, er_sp);
            }
            for (int i = 0; i < num_pr; i++)
            {
                Rover* pr = new Rover(rover_type, er_sp, er_ch, num_missions);
                pr->setStatus('A');
                pr->setID(rID);
                rID++;
                obj->GetPR()->enqueue(pr, pr_sp);
            }
        }
        fptr.close();
        system("CLS");
        cout << "File successfully closed...\n\n";
        Sleep(2500);
    }
    else
    {
        cout << "\nError! Unable to open input file successfully.\n\n";
    }
}

void UI::Interactive_mode()
{
    char x;
    cin.get(x);
    system("CLS");
    cout << "Current Day: " << obj->getCurrentDay() << "\n";
    int w_m = 7, i_e = 4, a_r = 4, i_c = 2, c_m = 3;
    cout << w_m << " Waiting Missions: "; obj->O_WaitingEM(); cout << "\n";
    cout << "------------------------------------------\n";
    cout << a_r << " In-Execution Missions/Rovers: " << "\n";
    cout << "------------------------------------------\n";
    cout << w_m << " Available Rovers: "; obj->O_AvailableRovers(); cout << "\n";
    cout << "------------------------------------------\n";
    cout << i_c << " In-Checkup Rovers: "; obj->O_InCheckupRovers(); cout << "\n";
    cout << "------------------------------------------\n";
    cout << c_m << " Completed Missions: "; obj->CheckCompleted(); cout << "\n\n\n";
    
}

void UI::SbS_mode()
{
        system("CLS");
        int w_m = 7, i_e = 4, a_r = 4, i_c = 2, c_m = 3;
        cout << "Current Day: " << obj->getCurrentDay() << "\n";
        cout << w_m << " Waiting Missions: "; obj->O_WaitingEM(); cout << "\n";
        cout << "------------------------------------------\n";
        cout << a_r << " In-Execution Missions/Rovers: " << "\n";
        cout << "------------------------------------------\n";
        cout << w_m << " Available Rovers: "; obj->O_AvailableRovers(); cout << "\n";
        cout << "------------------------------------------\n";
        cout << i_c << " In-Checkup Rovers: "; obj->O_InCheckupRovers(); cout << "\n";
        cout << "------------------------------------------\n";
        cout << c_m << " Completed Missions: "; obj->CheckCompleted(); cout << "\n\n\n";
        Sleep(1000);
}

void UI::Silent_mode()
{
    system("CLS");
    cout << "Silent Mode\nSimulation Starts...\nSimulation Ends, Output file created\n\n\n";
}

void UI::w_file()
{
    system("CLS");
    string o_file;
    cout << "(Please include file extension)\nEnter output file name: ";
    cin >> o_file;
    ofstream myfile(o_file);
    if (myfile.is_open())
    {
        myfile << "CD\tID\tFD\tWD\tED\n";
        myfile << "------------------------------------------\n";
        myfile << "------------------------------------------\n";
        myfile.close();
    }
    else cout << "Unable to write to file...";
}


void UI::p_output()
{
    if (mode == 1)
    {
        Interactive_mode();
    }
    else if (mode == 2)
    {
        SbS_mode();
    }
    else if (mode == 3)
    {
        Silent_mode();
    }
}

void UI::chooseMode()
{
    int choice;
    cout << "1.Interactive mode\n2.Step-by-Step mode\n3.Silent mode\n\n";
    cin >> choice;
    if (choice == 1)
    {
        system("CLS");
        mode = 1;
    }
    else if (choice == 2)
    {
        system("CLS");
        mode = 2;
    }
    else if (choice == 3)
    {
        system("CLS");
        mode = 3;
    }
    else
    {
        system("CLS");
        cout << "Error! Incorrect input re-enter your choice...\n\n";
    }
}
