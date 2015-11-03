#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fftw3.h>
#include <chrono>

using namespace std::chrono;

int main(int , char** )
{
    int i;
    fftw_complex *in;
    fftw_complex *in2;
    int n = 16;
    fftw_complex *out;
    fftw_plan plan_backward;
    fftw_plan plan_forward;
    high_resolution_clock::time_point t1;
    high_resolution_clock::time_point t2;
    unsigned int seed = 123456789;

  /*
    Create the input array.
  */

    in = (fftw_complex *) fftw_malloc ( sizeof ( fftw_complex ) * n );

    srand(time(NULL));
    int p = 0;
    for ( i = 0; i < n; i++ )
    {
      in[i][0] = p; //static_cast <double>  ( rand() % 100 ) / 100 + rand() % 100 ;
      in[i][1] = p*3; //;static_cast <double>  ( rand() % 100 ) / 100 + rand() % 100 ;
      p++;
    }

    printf ( "\n" );
    printf ( "  Input Data:\n" );
    printf ( "\n" );

    for ( i = 0; i < n; i++ )
    {
      printf ( "  %3d  %12f  %12f\n", i, in[i][0], in[i][1] );
    }

  /*
    Create the output array.
  */
    out = (fftw_complex*) fftw_malloc ( sizeof ( fftw_complex ) * n );

    t1 = high_resolution_clock::now();
    plan_forward = fftw_plan_dft_1d ( n, in, out, FFTW_FORWARD, FFTW_ESTIMATE );
    fftw_execute ( plan_forward );
    t2 = high_resolution_clock::now();

    long duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    printf("Exection Time fftw without threads :  %ld us\n\n",  duration);

    printf ( "\n" );
    printf ( "  Output FFT Coefficients:\n" );
    printf ( "\n" );

    for ( i = 0; i < n; i++ )
    {
      printf ( "  %3d  %12f  %12f\n", i, out[i][0], out[i][1] );
    }

  /*
    Recreate the input array.
  */
    in2 = (fftw_complex *) fftw_malloc ( sizeof ( fftw_complex ) * n );

    plan_backward = fftw_plan_dft_1d ( n, out, in2, FFTW_BACKWARD, FFTW_ESTIMATE );

    fftw_execute ( plan_backward );

    printf ( "\n" );
    printf ( "  Recovered input data:\n" );
    printf ( "\n" );

    for ( i = 0; i < n; i++ )
    {
      printf ( "  %3d  %12f  %12f\n", i, in2[i][0], in2[i][1] );
    }

    printf ( "\n" );
    printf ( "  Recovered input data divided by N:\n" );
    printf ( "\n" );

    for ( i = 0; i < n; i++ )
    {
      printf ( "  %3d  %12f  %12f\n", i, in2[i][0] / ( double ) ( n ), in2[i][1] / ( double ) ( n ) );
    }

  /*
    Free up the allocated memory.
  */

    fftw_destroy_plan ( plan_forward );
    fftw_destroy_plan ( plan_backward );

    fftw_free ( in );
    fftw_free ( in2 );
    fftw_free ( out );

    return EXIT_SUCCESS;
}
