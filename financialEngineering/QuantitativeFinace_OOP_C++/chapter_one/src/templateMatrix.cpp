#include "chapter_one_lib"
#include <complex>

void usingTemplateMatrices(){
    int n = 5, m = 3;

    DenseMatrix_t<double> D(n, m);
    DenseMatrix_t<std::complex<double>> C(n, m);

    for (int i = 0; i<n; i++){
        for (int j = 0; j<m; j++){
            D(i,j) = 0.1*i*j;
            C(i,j) = std::complex<double>(i,j);
        }
    }

    double sum = 0;
    std::complex<double> csum = 0;

    for (int i =0; i<n; i++){
        for (int j = 0; j<m; j++){
            sum += D(i,j);
            csum += C(i,j);
        }
    }

    // std::cout<<"Matrix C"<<std::endl;
    // // std::cout<<C<<std::endl;

    // std::cout<<"Matrix D"<<std::endl;
    // std::cout<<D<<std::endl;

    std::cout<<"sum of the elements in C : "<<sum<<std::endl;
    std::cout<<"sum of the elements in D : "<<csum<<std::endl;
}
