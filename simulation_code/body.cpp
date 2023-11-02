#include "../headers/simulator.h"

GravitationalBody:: GravitationalBody(int ID, valtype mass, vector<valtype> position, vector<valtype> momentum): ID(ID), mass(mass), position(position), momentum(momentum){}

void GravitationalBody:: writeCoords(ofstream& outstream, const string& sep, const string& end)const {
    for(auto& coord: position){
        outstream<<coord<<sep;
    }
    outstream<<end;
}

GravitationalSystem::  GravitationalSystem(vector<GravitationalBody>&& bodies, valtype progTime): bodies(bodies), progTime(progTime){}

GravitationalSystem::  GravitationalSystem(string&& infile, valtype progTime): progTime(progTime){
    //expecting inputfile with format ID M X Y  Z VX VY VZ \N
    bodies = vector<GravitationalBody>();
    ifstream instream(infile);
    while(!instream.eof()){
        int ID;
        valtype m,x,y,z,vx,vy,vz;
        //std::cout<<"hello"<<std::endl;
        instream>>ID>>m>>x>>y>>z>>vx>>vy>>vz;
        std::cout<<" "<<ID<<" "<<m<<" "<<x<<" "<<y<<" "<<z<<" "<<vx<<" "<<vy<<" "<<vz<<std::endl;

        bodies.push_back(GravitationalBody(ID,m,{x,y,z},{vx*m,vy*m,vz*m}));
    }
}



void GravitationalSystem:: writeBodyCoords(ofstream& outstream, string coordSep, string bodySep, string end )const {
    for(auto& body:bodies){
        body.writeCoords(outstream, coordSep, bodySep);
    }
    outstream<<end;
}


void GravitationalSystem:: writeTotalMomentum(ofstream& outstream, const string& sep, string coordSep, string bodySep, string end )const {
    vector <valtype> total(3);
    for(auto& body:bodies){
        for(int i = 0; i < 3; i++){
            total[i] += body.momentum[i];
        }
    }

    for(auto& totalmomentum : total){
        outstream << totalmomentum << sep;
    }
    outstream<<end;
}

void GravitationalSystem:: writeTotalEnergy(ofstream& outstream, const string& sep, string coordSep, string bodySep, string end )const {
    valtype total_energy = 0;

    for(auto& body:bodies){
        for(auto& mom : body.momentum){
            total_energy += (pow(mom, 2)/(2 * body.mass));
        }
    }

    for(int i = 0; i < bodies.size(); i++){
        for(int j = i + 1; j < bodies.size(); j++){
            valtype dist = 0;
            for(int k = 0; k < 3; k++){
                dist += pow(bodies[i].position[k] - bodies[j].position[k], 2);
            }

            dist = Q_rsqrt(dist);
            total_energy -= (G * bodies[i].mass * bodies[j].mass)/dist;
        }
    }

    outstream << total_energy;
    outstream<< end;
}

