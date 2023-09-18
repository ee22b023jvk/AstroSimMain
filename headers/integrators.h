#pragma once
/*
 * INTEGRATORS.H
 */
#ifndef INTEGRATORS_H_
#define INTEGRATORS_H_

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;


struct Integrator{
    valtype step;
    string integrator;

    Integrator(valtype, string);

    template <class func>
    valtype nextStep(valtype, valtype , func );

    template <class func>
    valtype nextStepEuler(valtype, valtype , func );

    template <class func>
    valtype nextStepRK4(valtype, valtype , func );
};

template <class func>
valtype Integrator:: nextStep(valtype x, valtype t, func derivative){
    if(integrator == "euler"){
        return nextStepEuler(x,t,derivative);
    }else if(integrator == "rk4 old"){
        return nextStepRK4(x,t,derivative);
    }
    cout<<"NO SUCH INTEGRATOR. USING EULER"<<endl;
    return nextStepEuler(x,t,derivative);
}


template <class func>
valtype Integrator::  nextStepEuler(valtype x, valtype t, func f){
    x+= f(t,x)*step;
    return x;
}


template <class func>
valtype Integrator:: nextStepRK4(valtype x, valtype t, func f){
    valtype k1 = step * f(t,x);  //other variables are constant!!
    valtype k2 = step * f(t + step/2.0 , x + step*k1/2.0);
    valtype k3 = step * f(t + step/2.0 , x + step*k2/2.0);
    valtype k4 = step * f(t + step , x + step*k3);

    x += (step/6.0)* (k1+ 2*k2 + 2*k3 + k4);
    t +=step;
    return x;
}
#endif

