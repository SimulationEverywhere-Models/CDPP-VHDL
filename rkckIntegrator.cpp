#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "rkckIntegrator.h"

void ODESolve(int *hdid, double *hnext, double htry, int *qdid, double c, double eps, int qstart)
{
    double dydxtemp, ytemp, mscal, mtemp, epsdid, qtemp;
    double rise=0.0;
    int htot=0;
    int nstp,htemp;
                                                
    for(nstp=0;nstp<=MAXSTP;nstp++)
    {
        ytemp = ((float)qstart)*QuantumSize + rise;  //midrise quantizer
        dydxtemp = c*ytemp; //ensure quantum size is small, for accuracy here
        mscal = dydxtemp;

        rkstep(ytemp,dydxtemp,htry,eps,mscal,&htemp,hnext,c,&mtemp,&epsdid);
        
        if(fabs((qtemp=(((double)htemp)*mtemp+rise))) > HalfQuantumSize)
        {
            *qdid = (int)(qtemp / HalfQuantumSize); 
            (qtemp>=0)?*qdid++:*qdid--;
            *hdid = htot+htemp;
            
            break;
        }
        else
        {
            rise=((double)htemp)*mtemp;
            htot+=htemp;
            htry = *hnext;
        }
        

    }

   

}


void rkstep(double y, double dydx, double htry, double eps, double mscal, int *hdid, 
            double *hnext, double c, double *mdid, double *epsdid)                   
{
    int i=0;
    double h, htemp, merr, mtemp, hhtemp;
    
    h=htry;

    for(;;) 
    {
        i++;

        rkck(y,dydx,h,&mtemp,&merr,c); //take step
        
        merr/=fabs(mscal);
        
        #ifdef PrintConsole
            printf("merr: %f\n",merr);
        #endif
        
        merr/=fabs(eps);                                   //scale relative to required tolerance 
        
        *hdid=(int)(h*TimebaseScaler);

        if((merr<=1.0 && hdid>0) || i>50000) 
            break;                          //step success, exit loop!
        
        if(hdid==0 && htry!=0.0)            // try to preserve integer timepoints, less error when interfaced with digital constructs
        {    
            h=htry;
            eps*=1.5;
        }
        else
        {
            htemp=SAFTY*h*pow(merr,PSHRNK);
            //error too large, reduce step size, never below 10%
        
        if(htemp>=(hhtemp = 0.1*h)) //setup h for next iteration
            h=htemp;
        else
            h=hhtemp;
        }

        if(h==0.0) 
        {
            printf("underflow in rkstep\n"); //underflow in h
            fprintf(stderr,"underflow in rkstep\n"); //underflow in h
        }
    }
    
    if(merr>ERRCON) 
        *hnext=SAFTY*h*pow(merr,PGROW);
    else 
        *hnext=5.0*h;                                  // no more than a five fold increase in step
    
    *mdid=mtemp;
    *epsdid=eps;
}

void rkck(double y, double dydx, double h, double *m, double *merr, double c)
{
       
    // Cash-Karp Parameters for Embedded Runga-Kutta Method
    static double a2=0.2, a3=0.3, a4=0.6, a5=1.0, a6=0.875, 
        b21=0.2, 
        b31=3.0/40.0, b32=9.0/40.0, 
        b41=0.3, b42=-0.9, b43=1.2, 
        b51=-11.0/54.0, b52=2.5, b53=-70.0/27.0, b54=35.0/27.0,
        b61=1631.0/55296.0, b62=175.0/512.0, b63=575.0/13824.0, b64=44275.0/110592.0, b65=253.0/4096.0, 
        c1=37.0/378.0, c3=250.0/621.0, c4=125.0/594.0, c6=512.0/1771.0;
        

    double dc1=c1-2825.0/27648.0, dc3=c3-18575.0/48384.0,
        dc4=c4-13525.0/55296.0, dc5=-277.00/14336.0, dc6=c6-0.25;

    double ak2, ak3, ak4, ak5, ak6, ytemp;

    //first RKCK step

    ytemp=y+b21*h*dydx;
    

    //second RKCK step
    
    ak2=c*ytemp;
    
    ytemp=y+h*(b31*dydx+b32*ak2);
    

    //third RKCK step

    ak3=c*ytemp;
    
    ytemp=y+h*(b41*dydx+b42*ak2+b43*ak3);
    
    //fourth RKCK step
    
    ak4=c*ytemp;

    
    ytemp=y+h*(b51*dydx+b52*ak2+b53*ak3+b54*ak4);
    

    //fifth RKCK step

    ak5=c*ytemp;

    
    ytemp=y+h*(b61*dydx+b62*ak2+b63*ak3+b64*ak4+b65*ak5);
    

    //sixth RKCK step

    ak6=c*ytemp;

      //accumulate increments with proper weights
    
    *m=(c1*dydx+c3*ak3+c4*ak4+c6*ak6);

     //estimate error as difference between fourth and fifth order method
    *merr=fabs(dc1*dydx+dc3*ak3+dc4*ak4+dc5*ak5+dc6*ak6);
}

