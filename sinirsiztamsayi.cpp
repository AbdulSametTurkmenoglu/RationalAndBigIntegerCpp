#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

ostream& operator<<(ostream& o, vector<int> v){
    if (v[0] < 0 && v[1] != 0)
    {
        o << "-";
        for(int i=1; i<v.size(); i++){
            o << v[i];
        }
    }
    else if(v[1] < 0 && v.size() > 2){
        for (int i = 2; i < v.size(); i++)
        {
            o << v[i];
        }
    }
    else if (v[0] == 0 && v[1] > 0)
    {
        for (int i = 1; i < v.size(); i++)
        {
            o << v[i];
        }
    }
    else if (v[0] < 0 && v[1] == 0)
    {
        for (int i = 1; i < v.size(); i++)
        {
            o << v[i];
        }
    }
    else{
        for(int i=0; i<v.size(); i++){
            o << v[i];
        }
    }

    return o;
}

class MS{
    private:
    vector<int> v;
    string str;
    bool _negatif;
    public:
    MS(){}
    MS(string s){
        str = s;
        _negatif = (str[0] == '-');
        for(int i=0; i<str.size(); i++){
            v.push_back(str[i]-'0');
        }
    }

    MS(long long int n){
        str = to_string(n);
        _negatif = (str[0] == '-');
        for(int i=0; i<str.size(); i++){
            v.push_back(str[i]-'0');
        }

    }

    vector<int> getV(){
        return v;
    }

    string getS(){
        return str;
    }

    string rvs(string& str)
    {
        string tmp = str;
        int n = tmp.length();

        for (int i = 0; i < n / 2; i++)
            swap(tmp[i], tmp[n - i - 1]);

        return tmp;
    }

    MS operator+(MS& ms){
        string s1 = rvs(str), s2 = rvs(ms.str);
        string s3 = "";
        int elde = 0;
        for (int i = 0; i < s1.length() || i < s2.length(); i++)
        {
            int toplam = 0;
            if (i < s1.length())
            {
                toplam += s1[i] - '0';
            }
            if (i < s2.length())
            {
                toplam += s2[i] - '0';
            }
            toplam += elde;
            elde = toplam / 10;
            toplam = toplam % 10;
            s3 += to_string(toplam);
        }
        if (elde != 0)
        {
            s3 += to_string(elde);
        }
        return MS(rvs(s3));
    }
    //overload - operator(Buna dikkat etmemiz lazım lo )

    MS operator-(MS& ms) {
        string s1 = rvs(str), s2 = rvs(ms.str);
        string s3 = "";

        bool _negatif = false;

        if (str[0] == '-' && ms.str[0] != '-') {

            _negatif = true;

        } else if (str[0] != '-' && ms.str[0] == '-') {

            _negatif = false;

        } else {
            // iki operatör aynı işartli o yüzden boyutlarını karşılaştırmalıyız
            if (s1.size() < s2.size()) {

                _negatif = true;

            } else if (s1.size() > s2.size()) {

                _negatif = false;

            } else {
                // operatörler aynı boyutta, bu yüzden basamakları karşılaştırmalıyız
                 for (int i = 0; i < s1.size(); i++) {
                    if (s1[i] < s2[i]) {
                        _negatif = true;
                        break;
                    } else if (s1[i] > s2[i]) {
                        _negatif = false;
                        break;
                    }
                }
            }
        }

        int elde = 0;
        for (int i = 0; i < s1.size() || i < s2.size(); i++) {
            int d1 = i < s1.size() ? s1[i] - '0' : 0;
            int d2 = i < s2.size() ? s2[i] - '0' : 0;
            int fark = 0;
            if (_negatif) {
                fark = d2 - d1 - elde;
                if (fark < 0) {
                    fark += 10;
                    elde = 1;
                } else {
                    elde = 0;
                }
            } else {
                fark = d1 - d2 - elde;
                if (fark < 0) {
                    fark += 10;
                    elde = 1;
                } else {
                    elde = 0;
                }
            }
            s3 += to_string(fark);
        }

        if (_negatif) {
            s3 += '-';
        }

        return MS(rvs(s3));

    }

    bool operator<(MS& ms){
        if (str[0] == '-' && ms.str[0] != '-')
        {
            return true;
        }
        else if (str[0] != '-' && ms.str[0] == '-')
        {
            return false;
        }
        else if (str[0] == '-' && ms.str[0] == '-')
        {
            if (str.length() > ms.str.length())
            {
                return true;
            }
            else if (str.length() < ms.str.length())
            {
                return false;
            }
            else
            {
                for (int i = 0; i < str.length(); i++)
                {
                    if (str[i] > ms.str[i])
                    {
                        return true;
                    }
                    else if (str[i] < ms.str[i])
                    {
                        return false;
                    }
                }
                return false;
            }
        }
        else
        {
            if (str.length() > ms.str.length())
            {
                return false;
            }
            else if (str.length() < ms.str.length())
            {
                return true;
            }
            else
            {
                for (int i = 0; i < str.length(); i++)
                {
                    if (str[i] > ms.str[i])
                    {
                        return false;
                    }
                    else if (str[i] < ms.str[i])
                    {
                        return true;
                    }
                }
                return false;
            }
        }
    }

    bool operator>(MS& ms){
        if((*this)<ms){
            return false;
        }
        else if((*this)==ms){
            return false;
        }
        else{
            return true;
        }
    }

    bool operator==(MS& ms){
        string s1 = rvs(str), s2 = rvs(ms.str);
        if (s1.length() > s2.length())
        {
            return false;
        }
        else if (s1.length() < s2.length())
        {
            return false;
        }
        else
        {
            for (int i = 0; i < s1.length(); i++)
            {
                if (s1[i] > s2[i])
                {
                    return false;
                }
                else if (s1[i] < s2[i])
                {
                    return false;
                }
            }
            return true;
        }
    }

    bool operator<=(MS& ms){
        if((*this)<ms){
            return true;
        }
        else if((*this)==ms){
            return true;
        }
        else{
            return false;
        }
    }

    bool operator>=(MS& ms){
        if((*this)>ms){
            return true;
        }
        else if((*this)==ms){
            return true;
        }
        else{
            return false;
        }
    }

    bool operator!=(MS& ms){
        if((*this)==ms){
            return false;
        }
        else{
            return true;
        }
    }

    MS operator*(MS& ms){
        string s1 = rvs(str), s2 = rvs(ms.str);
        string s3 = "";
        int elde = 0;
        int s1u = s1.length(), s2u = s2.length();
        if (s1[s1u-1] == '-')
        {
            s1u -= 1;
        }
        if (s2[s2u-1] == '-')
        {
            s2u -= 1;
        }

        for (int i = 0; i < s1u + s2u; i++)
        {
            s3 += "0";
        }
        for (int i = 0; i < s1u; i++)
        {
            for (int j = 0; j < s2u; j++)
            {
                int toplam = (s1[i] - '0') * (s2[j] - '0') + (s3[i + j] - '0') + elde;
                elde = toplam / 10;
                toplam = toplam % 10;
                s3[i + j] = toplam + '0';
            }
            if (elde != 0)
            {
                s3[i + s2.length()] += elde;
                elde = 0;
            }
        }
        if (str[0] == '-' && ms.str[0] == '-')
        {
            return MS(rvs(s3));
        }
        else if (str[0] == '-' && ms.str[0] != '-')
        {
            return MS("-" + rvs(s3));
        }
        else if (str[0] != '-' && ms.str[0] == '-')
        {
            return MS("-" + rvs(s3));
        }
        else
        {
            return MS(rvs(s3));
        }
    }

    bool operator>(int i){
        MS ms(to_string(i));
        return (*this)>ms;
    }

    MS operator/(MS& ms){
        int tmp = 0;
        string s1 = rvs(str), s2 = rvs(ms.str);
        if (s1[s1.length()-1] == '-')
        {
            s1 = s1.substr(0, s1.length()-1);

        }
        if (s2[s2.length()-1] == '-')
        {
            s2 = s2.substr(0, s2.length()-1);
        }
        MS temp1 = MS(s1), temp2 = MS(s2);
        for (int i = 0 ; ;i++){
            (*this) = (*this) - ms;
            if (str[0] == '0'){
                str = str.substr(str.length()-1);
            }
            tmp++;
            if((*this)<ms){
                break;
            }
        }
        if (str[0] == '-' && ms.str[0] == '-')
        {
            return MS(to_string(tmp));
        }
        else if (str[0] == '-' && ms.str[0] != '-')
        {
            return MS("-" + to_string(tmp));
        }
        else if (str[0] != '-' && ms.str[0] == '-')
        {
            return MS("-" + to_string(tmp));
        }
        else
        {
            return MS(to_string(tmp));
        }
    }
// üst almaya tekrar dönücez

    MS operator^(MS& ms){
        MS tmp("1");
        for (int i = 1; i <= stoi(ms.str); i++)
        {
            tmp = (*this)*tmp;
            if (tmp.str[0] == '0')
            {
                tmp.str = tmp.str.substr(1);
            }
        }
        return tmp;
    }
    //bunada geri dönmek gerek !!!
    MS operator%(MS& ms){
        MS tmp = (*this);
        MS tmp2 = (ms);
        MS tmp3 = tmp/tmp2;
        tmp3 = tmp3*tmp2;
        return (*this)-tmp3;
    }

    friend ostream& operator<<(ostream& o, MS& ms){
        o << ms.getV() << endl;
        return o;
    }

    friend istream& operator>>(istream& i, MS& ms){
        i >> ms.str;
        ms = MS(ms.str);
        return i;
    }

};

int main(){

     MS denek,denek1, denek2,denek3;
     MS denek4, denek5,denek6,denek7 ;

     string girdi;

     string girdi1 ;

     cout << " ******* SinirsizTamSayi odevi ********" << std::endl;

     cout << "denek giriniz: ";cin >> girdi;
     cout << " " << std::endl;
     cout << "denek2 giriniz: ";cin >> girdi1;
     cout <<  "" << std::endl;

     denek2 = MS(girdi1);

     denek = MS(girdi);
     // Toplama
     denek1 = denek + denek2;

     cout << "Toplama sonuc: " << denek1 <<std::endl;

     //Çıkarma

     denek3 = denek - denek2;

     cout << "Cikarma sonuc: " << denek3 <<std::endl;

    //çarpma

    denek4 = denek * denek2;

    cout << "Carpma sonuc: " << denek4 <<std::endl;

    //bölme
    denek5 = denek / denek2;

    cout << "bolme sonuc: " << denek5 <<std::endl;

    //mod
    denek6 = denek % denek2;

    cout << "mod sonuc: " << denek6 <<std::endl;

    //üst alma
    denek7 = denek ^ denek2;

    cout << "ust alma sonuc: " << denek7 <<std::endl;

    cout << "Bazi hatalar var ama elimizden geleni yaptik hocam " << std::endl;










    return 0;
}