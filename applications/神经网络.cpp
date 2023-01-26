#include "neural.h"
using namespace std;
ifstream in;
int main(){
    in.open("bangumi_data_org.txt");
    int n,m;
    in>>n>>m;
    n=40;
    SimpleNeuralNetwork NN(m-1,7,1);
    vector<Matrix<double> > datas,y_trues;
    for (int i=1;i<=n;++i){
        Matrix<double>data(1,m-1),y_true(1,1);
        in>>y_true[1][1];
        for (int j=1;j<=m-1;++j) in>>data[1][j];
        datas.push_back(data);
        y_trues.push_back(y_true);
    }
    auto M=mean(datas),D=devi(datas);
    auto M_rate=mean(y_trues),D_rate=devi(y_trues);
    datas=to_std(datas);
    y_trues=to_std(y_trues);
    NN.train(datas,y_trues,false,20000,0.001);
    cout<<M_rate<<D_rate<<endl;
    int practical=57-n;
    double sum=0;
    for (int i=1;i<=practical;++i){
        double rate;
        in>>rate;
        Matrix<double>input(1,m-1);
        for (int k=1;k<=m-1;++k){
            double x;
            in>>x;
            input(k)=(x-M(k))/D(k);
        }
        Matrix<double>output=NN.feedForward(input,false);
        for (int k=1;k<=1;++k){
            output(k)=output(k)*D_rate(k)+M_rate(k);
        }
        double myrate=output(1);
        cout<<rate<<" "<<myrate<<endl;
        sum+=myabs(rate-myrate);
    }
    cout<<sum/practical<<endl;
    while (true){
        Matrix<double>input(1,m-1);
        for (int k=1;k<=m-1;++k){
            double x;
            cin>>x;
            input(k)=(x-M(k))/D(k);
        }
        Matrix<double>output=NN.feedForward(input,false);
        for (int k=1;k<=1;++k){
            output(k)=output(k)*D_rate(k)+M_rate(k);
        }
        cout<<output<<endl;
    }
}