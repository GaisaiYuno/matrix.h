#include "matrix.h"
#include "euclid.h"
using namespace std;
ifstream in;
int main(){
    in.open("bangumi_data4.txt");
    vector<Matrix<long double> >v;
    int n,m;
    in>>n>>m;
    for (int i=1;i<=n;++i){
        Matrix<long double>V(m,1);
        for (int j=1;j<=m;++j) in>>V[j][1];
        cout<<"bgm评分"<<V[1][1]<<endl;
        v.push_back(V);
    }
    // auto R=pca_with_svd(v);
    auto R=pca(v);
    auto M=mean(v);
    cout<<R<<endl;
    long double sum=0;
    for (int i=1;i<=10;++i){
        long double data[40],s=0;
        long double rate;
        in>>rate;
        for (int j=2;j<=m;++j) in>>data[j],data[j]-=M[j][1];
        for (int j=2;j<=m;++j) s+=data[j]*R[j][1];
        long double my_rate=(-s/R[1][1])+M[1][1];
        cout<<rate<<" "<<my_rate<<endl;
        sum+=myabs(rate-my_rate);
    }
    cout<<sum<<endl;
    // while (true){
    //     long double data[40],s=0;
    //     cout<<"please enter the data"<<endl;
    //     for (int j=2;j<=m;++j) cin>>data[j],data[j]-=M[j][1];
    //     for (int j=2;j<=m;++j) s+=data[j]*R[j][1];
    //     cout<<(-s/R[1][1])+M[1][1]<<endl;
    // }
}
/*
5.37 6.11 115 6.11 75
8.39 8.11 407 8.11 353
7.11 7.6 510 7.7 358
7.42 7.63 178 7.63 140
7.01 7.81 464 7.42 345
5.64 7.5 83 6.34 60
6 6.11 143 6.42 60
7.33 7.78 230 7.46 201
6.04 7.29 73 5.8 42
7.27 7.5 134 7.3 53
6.8 6.89 424 7.57 236
*/

/*
8 34

7.11 2.6709401709401708 0.21367521367521367 0.0 0.8547008547008547 2.6709401709401708 5.235042735042735 20.726495726495727 42.52136752136752 12.5 12.606837606837606 3976
1.9230769230769231 0.23076923076923078 0.0 1.0 2.3846153846153846 6.538461538461538 22.384615384615383 43.23076923076923 12.384615384615385 9.923076923076923 5019
1.667778519012675 0.200133422281521 0.0 1.0006671114076051 2.535023348899266 6.604402935290193 23.682454969979986 42.62841894596398 12.00800533689126 9.673115410273516 5624

8.39 0.24630541871921183 0.7389162561576355 0.0 0.49261083743842365 0.24630541871921183 3.4482758620689653 16.00985221674877 42.610837438423644 27.586206896551722 8.620689655172415 2042
0.0 0.4491017964071856 0.1497005988023952 0.5988023952095808 1.1976047904191616 3.7425149700598803 14.67065868263473 45.65868263473054 25.59880239520958 7.934131736526946 2832
0.11655011655011654 0.34965034965034963 0.11655011655011654 0.4662004662004662 1.1655011655011656 3.37995337995338 14.102564102564102 46.96969696969697 25.757575757575758 7.575757575757576 3436

7.42 1.4545454545454546 0.0 0.7272727272727273 0.36363636363636365 2.909090909090909 6.181818181818182 25.454545454545453 48.72727272727273 5.454545454545454 8.727272727272727 1888
0.7058823529411765 0.23529411764705882 0.23529411764705882 0.0 2.3529411764705883 5.882352941176471 29.41176470588235 48.470588235294116 5.411764705882353 7.294117647058823 2669
0.5597014925373134 0.1865671641791045 0.1865671641791045 0.0 2.0522388059701493 6.156716417910448 30.597014925373134 48.507462686567166 5.037313432835821 6.7164179104477615 3190

7.01 1.1928429423459244 0.1988071570576541 0.1988071570576541 0.3976143141153082 3.7773359840954273 8.151093439363818 28.82703777335984 44.93041749502982 6.361829025844931 5.964214711729622 2491
0.8746355685131195 0.1457725947521866 0.5830903790087464 0.7288629737609329 3.6443148688046647 10.204081632653061 29.591836734693878 42.27405247813411 5.97667638483965 5.97667638483965 3196
1.1990407673860912 0.23980815347721823 0.5995203836930456 0.9592326139088729 3.4772182254196644 10.191846522781775 32.014388489208635 40.88729016786571 5.155875299760192 5.275779376498801 3715

6.91 0.9259259259259259 0.0 0.0 2.7777777777777777 2.7777777777777777 21.296296296296298 42.592592592592595 17.59259259259259 5.555555555555555 6.481481481481482 771
0.4366812227074236 0.0 0.0 1.7467248908296944 2.183406113537118 17.467248908296945 51.96506550218341 19.213973799126638 3.493449781659389 3.493449781659389 1241
0.3401360544217687 0.0 0.0 1.7006802721088434 2.0408163265306123 18.027210884353742 48.29931972789116 21.08843537414966 3.741496598639456 4.761904761904762 1482

7.33 0.0 0.0 0.0 0.0 1.2345679012345678 9.876543209876543 29.62962962962963 49.382716049382715 6.172839506172839 3.7037037037037037 880
0.8403361344537815 0.0 0.42016806722689076 0.42016806722689076 0.42016806722689076 9.243697478991596 34.87394957983193 47.89915966386555 3.361344537815126 2.5210084033613445 1485
0.3257328990228013 0.0 0.3257328990228013 0.6514657980456026 0.6514657980456026 9.77198697068404 33.55048859934853 47.23127035830619 4.5602605863192185 2.9315960912052117 1745

8.08 0.0 0.0 0.0 0.8695652173913043 0.8695652173913043 2.608695652173913 16.52173913043478 55.65217391304348 10.434782608695652 13.043478260869565 830
0.0 0.0 0.0 0.5649717514124294 0.5649717514124294 4.519774011299435 15.819209039548022 57.6271186440678 9.03954802259887 11.864406779661017 1081
0.0 0.0 0.9090909090909091 0.0 0.9090909090909091 3.6363636363636362 16.818181818181817 56.81818181818182 10.909090909090908 10.0 1238

5.64 0.0 0.0 1.408450704225352 2.816901408450704 15.492957746478874 40.84507042253521 22.535211267605632 12.67605633802817 1.408450704225352 2.816901408450704 531
0.0 0.7692307692307693 0.7692307692307693 3.076923076923077 11.538461538461538 40.0 32.30769230769231 8.461538461538462 1.5384615384615385 1.5384615384615385 724
0.0 0.5952380952380952 1.7857142857142858 3.5714285714285716 9.523809523809524 42.857142857142854 30.357142857142858 8.333333333333334 1.1904761904761905 1.7857142857142858 842

*/

/*
?:

*/
/*

天籁人偶

5.37 6.11 115 6.11 75

孤独摇滚！

8.39 8.11 407 8.11 353

链锯人

7.11 7.6 510 7.7 358

间谍过家家 第二部分

7.42 7.63 178 7.63 140

机动战士高达 水星的魔女

7.01 7.81 464 7.42 345

新人炼金术师的店铺经营

5.64 7.5 83 6.34 60

明日方舟：黎明前奏

6 6.11 143 6.42 60

少女手工

7.33 7.78 230 7.46 201

*/