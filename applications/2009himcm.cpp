#include "neural.h"
using namespace std;
ifstream in;
int main(){
    SimpleNeuralNetwork NN(3,3,2);
    vector<Matrix<double> > datas=vector<Matrix<double> >{
        Matrix<double>('R',vector<double>{9.5,141,290}),
        Matrix<double>('R',vector<double>{7.2,227962,451.8}),
        Matrix<double>('R',vector<double>{8.1,1000,327}),
        Matrix<double>('R',vector<double>{8.4,18800,220}),
        Matrix<double>('R',vector<double>{8.4,140500,100}),
    };
    vector<Matrix<double> > y_trues=vector<Matrix<double> >{
        Matrix<double>('R',vector<double>{61,541}),
        Matrix<double>('R',vector<double>{2000,40000}),
        Matrix<double>('R',vector<double>{3068,5000}),
        Matrix<double>('R',vector<double>{1500,1451}),
        Matrix<double>('R',vector<double>{1000,7000}),
    };

    auto M_i=mean(datas),D_i=devi(datas);
    auto M_o=mean(y_trues),D_o=devi(y_trues);
    datas=to_std(datas);
    y_trues=to_std(y_trues);
    NN.train(datas,y_trues,false,20000,0.001);
    while (true){
        Matrix<double>input(1,3);
        for (int k=1;k<=3;++k){
            double x;
            cin>>x;
            input(k)=(x-M_i(k))/D_i(k);
        }
        Matrix<double>output=NN.feedForward(input,false);
        for (int k=1;k<=2;++k){
            output(k)=output(k)*D_o(k)+M_o(k);
        }
        cout<<output<<endl;
    }
}

/*
Hilo 8.5 141 290
Charleston 8 350.97 556
*/