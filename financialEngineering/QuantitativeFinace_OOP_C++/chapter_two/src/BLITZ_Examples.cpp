#include "chapter_two_lib"

void firstTest(){
    blitz::Array<double, 2> A(3,3);
    blitz::Array<double, 2> B(3,3);
    blitz::Array<double, 2> C(3,3);
    blitz::Array<double, 2> D(3,3);

    A = 1.;

    B = 1., 0., 1.,
        0., 1., 0.,
        1., 0., 1.;

    blitz::firstIndex i;
    blitz::secondIndex j;

    C = 1.+j+i*3.;
    D = A + B*C;
    D(0,0) =0.;
    std::cout<<"A with blitz::cout & blitz::endl:"<<std::endl;
    blitz::cout<<A<<blitz::endl;
    std::cout<<"A with std::cout & std::endl:"<<std::endl;
    std::cout<<A<<std::endl;
    std::cout<<"^ It is the same thing."<<std::endl;
    std::cout<<"B :"<<std::endl;
    std::cout<<B<<std::endl;
    std::cout<<"C :"<<std::endl;
    std::cout<<C<<std::endl;
    std::cout<<"D :"<<std::endl;
    std::cout<<D<<std::endl;
    
}

void slicing(){
    blitz::Array<double, 2> A(4,4);
    A = 1.;
    blitz::Array<double, 2> B = A(blitz::Range(2,3), blitz::Range(2,3));
    B(0,0) = 2.;
    blitz::Array<double,2> C = A(blitz::Range::all(), blitz::Range(3,3));
    blitz::Array<double,1> D = A(blitz::Range::all(),3);
    std::cout<<"A: "<<std::endl;
    std::cout<<A<<std::endl;
    std::cout<<"B: "<<std::endl;
    std::cout<<B<<std::endl;
    std::cout<<"C: "<<std::endl;
    std::cout<<C<<std::endl;
    std::cout<<"D: "<<std::endl;
    std::cout<<D<<std::endl;
}


double add_one(double x){
    return x+1;
}

double half(int x){
    return 0.5*x;
}

double hypothenuse(double a, double b){
    return a*a+b*b;
}

int fit_into(double x, double y){
    return x/y;
}

void scalarFunctions(){
    blitz::Array<double, 2>A(4,4);
    A = 3.;

    blitz::Array<double, 2> B(add_one(A));
    blitz::Array<double, 2> C(hypothenuse(A,B));
    blitz::Array<double, 2> D(4,4);

    blitz::firstIndex i;
    blitz::secondIndex j;

    D = 1. + j+i*4.;

    blitz::Array<int, 2> E(fit_into(A,D));
    blitz::Array<double,2> F(half(E));

    std::cout<<"A: "<<std::endl;
    std::cout<<A<<std::endl;
    std::cout<<"B: "<<std::endl;
    std::cout<<B<<std::endl;
    std::cout<<"C: "<<std::endl;
    std::cout<<C<<std::endl;
    std::cout<<"D: "<<std::endl;
    std::cout<<D<<std::endl;

}

void reduce(){
    blitz::Array<double, 2> D(4,4);

    blitz::firstIndex i;
    blitz::secondIndex j;

    D = 1. + j+i*4.;

    std::cout<<"D: "<<std::endl;
    std::cout<<D<<std::endl;

    std::cout<<"Sum of all elements of D: "<<std::endl;
    std::cout<<sum(D)<<std::endl;

    blitz::Array<double, 1> rowsum(D.extent(blitz::firstDim));
    rowsum = sum(D, j);

    std::cout<<"Sum along each row: "<<rowsum<<std::endl;
    blitz::Array<double, 1> colsum(D.extent(blitz::secondDim));

    colsum = sum(D(j,i), j);

    std::cout<<"Sum along each col: "<<colsum<<std::endl;
}

void linearAlgebra(){
    
    blitz::firstIndex i;
    blitz::secondIndex j;
    blitz::thirdIndex k;

    blitz::Array<double,1> x(4), y(4);
    x = i;
    y = 4.-i;

    std::cout<<"x: "<<std::endl;
    std::cout<<x<<std::endl;

    std::cout<<"y: "<<std::endl;
    std::cout<<y<<std::endl;


    double dot_product = sum(x*y);
    std::cout<<"x.y = "<<dot_product<<std::endl;

    blitz::Array<double,2> A(4,4), B(2,4), D(4,4);

    A = x(i)*y(j);
    B = 1.;

    std::cout<<"A: "<<std::endl;
    std::cout<<A<<std::endl;
    std::cout<<"B: "<<std::endl;
    std::cout<<B<<std::endl;


    blitz::Array<double,2> C(B.extent(blitz::firstDim), A.extent(blitz::secondDim));
    C = sum(B(i,k)*A(k,j),k);
    std::cout<<"Matrix multiplication: "<<C<<std::endl;

    A = 1.0,0.0,2.0,-1.0,
      1.0,3.0,0.0,1.0,
      0.0,-1.0,2.0,2.0,
      0.5,8.0,1.0,0.0;
    blitz::Array<double,2> X(4,1),R(4,1);
    X = 1.0;
    R = sum(A(i,k)*X(k,j),k); 

    std::cout<<"Solvers needs to be calculated here."<<std::endl;
    std::cout << "Test tridiagonal solver:" << std::endl;
    D = 1.0, 2.0, 0.0, 0.0,
        3.0, 4.0, 5.0, 0.0,
        0.0, 6.0, 7.0, 8.0,
        0.0, 0.0, 9.0, 10.0;
    R = sum(D(i,k)*X(k,j),k); 
    std::cout<<"Solvers needs to be calculated here."<<std::endl;

}