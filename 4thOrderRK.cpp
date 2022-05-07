
// y'=cy

void rk4 (double y, double dydt, double h, double c, double *m)
{
    double h2, h6, ytemp, dyt, dym;

    h2 = h / 2;
    h6 = h / 6;

    ytemp=y+h2*dydt; //first step
    dyt=c*ytemp;

    ytemp=y+h2*dyt; //second step
    dym=c*ytemp;

    ytemp=y+h*dym; //third step
    dym+=dyt;

    dyt=c*ytemp;   //fourth step
        
    (*m)=h6*(dydt+dyt+2.0*dym);

}
