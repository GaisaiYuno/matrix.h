#include "matrix.h"
#include "euclid.h"
#define act relu
#define diff_act diff_relu
using namespace std;
double sigmoid(double x){
    return 1.0/(1+exp(-x));
}
double diff_sigmoid(double x){
    double fx=sigmoid(x);
    return fx*(1-fx);
}
double relu(double x){
    return x>0?x:0;
}
double diff_relu(double x){
    return x>0?1:0;
}
double leaky_relu(double x){
    return x>0?x:0.01*x;
}
double diff_leaky_relu(double x){
    return x>0?1:0.01;
}
double uniform(){
    return (double)(rand())/RAND_MAX;
}
// #define act relu
// #define diff_act diff_relu
struct Neuron{
    Matrix<double> weights;
    double bias;
    double last_t;
    double last_f;
    Neuron(Matrix<double> _weights,double _bias){
        weights=_weights;
        bias=_bias;
    }
    Neuron(int n){
        bias=uniform();
        weights.resize(1,n);
        for (int i=1;i<=n;++i) weights(i)=uniform();
    }
    Neuron(){
        bias=uniform();
    }
    double feedForward(Matrix<double> inputs,bool use_act=true){
        double total=(weights&inputs)+bias;
        if (use_act) return last_f=act(last_t=total);
        else return last_f=last_t=total;
    }
};
struct Layer{
    vector<Neuron>neurons;
    Layer(){
        neurons.clear();
    }
    Layer(int n,int prev){
        neurons.resize(n);
        for (int i=0;i<n;++i) neurons[i]=Neuron(prev);
    }
    int size(){
        return neurons.size();
    }
    Neuron&operator[](int i){
        return neurons[i-1];
    }
    Matrix<double> feedForward(Matrix<double> inputs,bool use_act=true){
        Matrix<double>outputs(1,neurons.size());
        for (int i=1;i<=neurons.size();++i){
            outputs(i)=neurons[i-1].feedForward(inputs,use_act);
        }
        return outputs;
    }
};
struct SimpleNeuralNetwork{
    Layer hidden;
    Layer output;
    SimpleNeuralNetwork(int i_size,int h_size,int o_size){
        hidden=Layer(h_size,i_size);
        output=Layer(o_size,h_size);
    }
    Matrix<double> feedForward(Matrix<double>my_input,bool use_act=true){
        return output.feedForward(hidden.feedForward(my_input,true),use_act);
    }
    void train(vector<Matrix<double> >datas,vector<Matrix<double> >y_trues,bool use_act,int epochs=1000,double rate=0.1){
        int data_size=datas.size();
        for (int epoch=1;epoch<=epochs;++epoch){
            double sum_of_loss=0;
            for (int s=0;s<data_size;++s){
                Matrix<double>data=datas[s],y_true=y_trues[s];
                int input_size=data.col;
                Matrix<double> y_pred=feedForward(data,use_act);
                for (int h=1;h<=hidden.size();++h){
                    double d_L_d_h=0;
                    for (int o=1;o<=output.size();++o){
                        double d_L_d_ypred=-2*(y_true(o)-y_pred(o));
                        double deriv_total=use_act?diff_act(output[o].last_t):1;
                        d_L_d_h+=d_L_d_ypred*deriv_total*output[o].weights(h);
                    }
                    double deriv_total=diff_act(hidden[h].last_t);
                    hidden[h].bias-=rate*d_L_d_h*deriv_total;
                    for (int i=1;i<=input_size;++i){
                        hidden[h].weights(i)-=rate*d_L_d_h*deriv_total*data(i);
                    }
                }
                for (int o=1;o<=output.size();++o){
                    double d_L_d_ypred=-2*(y_true(o)-y_pred(o));
                    double deriv_total=use_act?diff_act(output[o].last_t):1;
                    output[o].bias-=rate*d_L_d_ypred*deriv_total;
                    for (int h=1;h<=hidden.size();++h){
                        output[o].weights(h)-=rate*d_L_d_ypred*deriv_total*hidden[h].last_f;
                    }
                }
                Matrix<double> y_pred_new=feedForward(data,use_act);
                sum_of_loss+=mse_loss(y_true,y_pred_new);
            }
            cout<<"Epoch: "<<epoch<<" Sum of Loss: "<<sum_of_loss/data_size<<endl;
            if (sum_of_loss/data_size<0.05) break;
        }
    }
};