#include <iostream>
#include <string>
#include <math.h>
#include <locale.h>

using namespace std;

class Rasyonel{
private:
    double pay;
    double payda;
    double tam;
public:
    Rasyonel(){}
    Rasyonel(double _pay,double _payda,double _tam){
        this->pay=_pay;
        this->payda=_payda;
        this->tam=_tam;
    }

    Rasyonel(double _pay,double _payda){
        this->pay=_pay;
        this->payda=_payda;
        this->tam =0;
    }

    Rasyonel(string a){
        Rasyonel tmp;
        tmp.pay = stoi(a);
        reverseStr(a);
        tmp.payda= stoi(a);
        tmp = tamEkle(tmp);
        this->pay=tmp.pay;
        this->payda=tmp.payda;
        this->tam=tmp.tam;
    }
    static string reverseStr(string& str)
    {
        int n = str.length();

        // Swap character starting from two
        // corners
        for (int i = 0; i < n / 2; i++)
            swap(str[i], str[n - i - 1]);

        return str;
    }

    static double ebob(double sayi1,double sayi2){
        double buyukSayi;
        if(sayi1>sayi2) {
            buyukSayi = sayi1;
        } else {
            buyukSayi = sayi2;
        }

        for(buyukSayi; buyukSayi>0; buyukSayi--) {
            if( (int(sayi1)%int(buyukSayi)==0) && (int(sayi2)%int(buyukSayi)==0) ) {
                return buyukSayi;
                break;
            }
        }
    }

    static Rasyonel sadelestir(Rasyonel r){
        Rasyonel _r;
        double a = ebob(r.pay,r.payda);
        _r.pay = r.pay /a;
        _r.payda = r.payda/a;
        _r.tam = r.tam;
        return _r;
    }

    void setTam(double _tam){
        this->tam = _tam;
    }

    void setPayda(double _payda){
        this->payda = _payda;
    }

    void setPay(double _pay){
        this->pay = _pay;
    }

    double getTam(){
        return tam;
    }
    double getPay(){
        return pay;
    }
    double getPayda(){
        return payda;
    }

    friend ostream& operator<<(ostream& o,Rasyonel &r){
        if(r.tam != 0){
            o << r.getTam() << "[" << r.getPay()<< "/"<< r.getPayda()<<"]"<<endl;
        }else if(r.tam == 0 && r.pay == 0){
            o << "0"<<endl;
        }
        else{
            o << r.getPay()<< "/"<< r.getPayda()<<endl;
        }
        return o;
    }

    friend istream& operator>>(istream& i,Rasyonel &r){
        double xpay,xpayda,xtam;
        cout << "Rasyonel sayıya değerlerini verin: (Pay - Payda - Tam) "<<endl;
        cin >> xpay >> xpayda >> xtam;
        r.setPay(xpay);r.setPayda(xpayda);r.setTam(xtam);
        r = tamEkle(r);
        return i;
    }

    static Rasyonel tamEkle(Rasyonel _r){
        if(_r.pay >= _r.payda) {
            _r.tam += int(_r.pay / _r.payda);
            _r.pay = int(_r.pay) % int(_r.payda);
            if(_r.pay <= 0){
                _r.pay += (_r.tam * _r.payda);
                _r.tam = 0;
            }
            return sadelestir(_r);
        }else{
        return sadelestir(_r);
        }
    }

    Rasyonel operator+(Rasyonel r){
        Rasyonel _r;
        if(payda == r.payda){
            _r.pay = pay + r.pay;
            _r.tam = tam + r.tam;
            _r.payda = payda;
        }else if(payda != r.payda){
            _r.payda = payda * r.payda;
            _r.pay = (pay * r.payda) + (r.pay * payda);
            _r.tam = tam + r.tam;
        }
        return tamEkle(_r);
    }

    Rasyonel operator-(Rasyonel r){
        Rasyonel _r;
        if (payda == r.payda){
            _r.pay = pay - r.pay;
            _r.tam = tam - r.tam;
            _r.payda = payda;
        }else if(payda != r.payda){
            _r.payda = payda * r.payda;
            _r.pay = (pay * r.payda) - (r.pay * payda);
            _r.tam = tam - r.tam;
        }
        if(_r.pay <= 0){
            _r.pay += (_r.tam * _r.payda);
            _r.tam = 0;
        }
        return tamEkle(_r);
    }

    Rasyonel operator*(Rasyonel r){
        Rasyonel _r;
        _r.pay = (pay +(payda*tam)) * (r.pay+(r.payda*r.tam));
        _r.payda = payda * r.payda;
        return tamEkle(_r);
    }

    Rasyonel operator/(Rasyonel r){
        Rasyonel _r;
        _r.pay = (pay +(payda*tam)) * r.payda;
        _r.payda = payda * (r.pay+(r.payda*r.tam));
        return tamEkle(_r);
    }

    bool operator>(Rasyonel r){
        double tmp;
        pay =  (pay +(tam*payda));
        r.pay = (r.pay+(r.tam*r.payda));
        if(payda== r.payda){
            if(pay>r.pay)
                return true;
            else
                return false;
        }
        else{
            tmp = r.payda*payda;
            pay = pay*r.payda;
            r.pay = r.pay*payda;
            payda=tmp;
            r.payda =tmp;
            if (pay >r.pay)
                return true;
            else
                return false;
        }
    }

    bool operator<(Rasyonel r){
        double tmp;
        pay =  (pay +(tam*payda));
        r.pay = (r.pay+(r.tam*r.payda));
        if(payda== r.payda){
            if(pay<r.pay)
                return true;
            else
                return false;
        }
        else{
            tmp = r.payda*payda;
            pay = pay*r.payda;
            r.pay = r.pay*payda;
            payda=tmp;
            r.payda =tmp;
            if (pay < r.pay)
                return true;
            else
                return false;
        }
    }

    bool operator==(Rasyonel r){
        double tmp;
        pay =  (pay +(tam*payda));
        r.pay = (r.pay+(r.tam*r.payda));
        if(payda== r.payda){
            if(pay==r.pay)
                return true;
            else
                return false;
        }
        else{
            tmp = r.payda*payda;
            pay = pay*r.payda;
            r.pay = r.pay*payda;
            payda=tmp;
            r.payda =tmp;
            if (pay ==r.pay)
                return true;
            else
                return false;
        }
    }

    bool operator>=(Rasyonel r){
        double tmp;
        pay =  (pay +(tam*payda));
        r.pay = (r.pay+(r.tam*r.payda));
        if(payda== r.payda){
            if(pay>=r.pay)
                return true;
            else
                return false;
        }
        else{
            tmp = r.payda*payda;
            pay = pay*r.payda;
            r.pay = r.pay*payda;
            payda=tmp;
            r.payda =tmp;
            if (pay >=r.pay)
                return true;
            else
                return false;
        }
    }

    bool operator<=(Rasyonel r){
        double tmp;
        pay =  (pay +(tam*payda));
        r.pay = (r.pay+(r.tam*r.payda));
        if(payda== r.payda){
            if(pay<=r.pay)
                return true;
            else
                return false;
        }
        else{
            tmp = r.payda*payda;
            pay = pay*r.payda;
            r.pay = r.pay*payda;
            payda=tmp;
            r.payda =tmp;
            if (pay <=r.pay)
                return true;
            else
                return false;
        }
    }

};

ostream& operator<<(ostream& o,const long double &a){
    Rasyonel tmp;
    int i=0;

    for(i; i<20; i++){
        float b=pow(10,i);
        if(int(a*b)%10==0)
            break;
    }
    long int c = pow(10,i-1);
    long int d = pow(10,i-2);
    long int result = a*c;
    tmp.setPayda(d);
    tmp.setPay(result);
    tmp.setTam(0);
    tmp = Rasyonel::tamEkle(tmp);
    cout << tmp<<endl;
    return o;
}


//3.14159265358979

int main() {

    int a,b,c,d,e,f;
    cout << " ******** RasyonelSayiProjesi ************** " << std::endl;
    cout << " 1.sayiyi girininiz(pay,payda,tam seklinde): "; cin >>a ;cin >> b ; cin >> c ;
    cout << "2.sayiyi girininiz(pay,payda,tam seklinde): "; cin >>d ; cin >>e ; cin>>f;
    setlocale(LC_ALL,"Turkish");
    Rasyonel r(a,b,c),r1(d,e,f);
    Rasyonel toplam = r + r1;
    Rasyonel fark = r - r1;
    Rasyonel carpim = r*r1;
    Rasyonel bolum = r/r1;
    cout <<"toplam: "<<toplam<<" fark: "<<fark<<" carpim: "<<carpim<<" bolum: "<<bolum<<endl;
    cout << "Hocam elimizden geleni yaptik :)" <<std::endl;
    return 0;
}