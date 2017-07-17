struct P3 {
  #define	TwoPi  6.28318530717958648
  #define	EPS  1e-14
  //---------------------------------------------------------------------------
// x - array of size 3
// return number of roots
// solve cubic equation a*x^3 + b*x^2 + c*x + d = 0 (a != 0)
static int solve(double *x, double _a, double _b, double _c, double _d) {
  double a = _b/_a, b = _c/_a, c = _d/_a;
	double a2 = a*a;
  double q  = (a2 - 3*b)/9; 
	double r  = (a*(2*a2-9*b) + 27*c)/54;
	// equation x^3 + q*x + r = 0
  double r2 = r*r;
	double q3 = q*q*q;
	double A,B;
    if(r2<q3) {
      double t=r/sqrt(q3);
      if( t<-1) t=-1;
      if( t> 1) t= 1;
      t=acos(t);
      a/=3; q=-2*sqrt(q);
      x[0]=q*cos(t/3)-a;
      x[1]=q*cos((t+TwoPi)/3)-a;
      x[2]=q*cos((t-TwoPi)/3)-a;
      return 3;
    } else {
      A =-root3(fabs(r)+sqrt(r2-q3)); 
      if( r<0 ) A=-A;
      B = A==0? 0 : B=q/A;

      a/=3;
      x[0] =(A+B)-a;
      x[1] =-0.5*(A+B)-a;
      x[2] = 0.5*sqrt(3.)*(A-B);
      return 1 + (fabs(x[2])<EPS);
    }
  }

  static double _root3 ( double x )
  {
      double s = 1.;
      while ( x < 1. )
      {
          x *= 8.;
          s *= 0.5;
      }
      while ( x > 8. )
      {
          x *= 0.125;
          s *= 2.;
      }
      double r = 1.5;
      r -= 1./3. * ( r - x / ( r * r ) );
      r -= 1./3. * ( r - x / ( r * r ) );
      r -= 1./3. * ( r - x / ( r * r ) );
      r -= 1./3. * ( r - x / ( r * r ) );
      r -= 1./3. * ( r - x / ( r * r ) );
      r -= 1./3. * ( r - x / ( r * r ) );
      return r * s;
  }

  static double root3 ( double x )
  {
      if ( x > 0 ) return _root3 ( x ); else
      if ( x < 0 ) return-_root3 (-x ); else
      return 0.;
  }
};
