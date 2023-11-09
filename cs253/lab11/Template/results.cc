#include <iomanip>	// for right, setw
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <ostream>

using namespace std;

template <typename T>
class BarGraph {
  public:
    void operator+=(const T &datum) {
        data[datum]++;
    }
    friend ostream& operator<< (ostream& os, const BarGraph<T>& d){
        for (const auto &v : d.data){
            os << right << setw(10) << v.first << ' ' << string (v.second, '*') << '\n';
        }
        os << '\n';
        return os;
    }
  private:
    map<T, unsigned> data;
};

template <> 
class BarGraph <char>{
    public:
        void operator+= (const char *da){   
            for (size_t i =0 ; *da != '\0'; ++i){
                data[int(*da)]++;
                ++da;
            }
        }
        void operator+= (const char da){
            data[int(da)]++;
        }
        friend ostream& operator<< (ostream& os, const BarGraph<char>& d){
            for (size_t j = 0; j <128; j++){
                if (d.data[j] != 0){
                     os << right << setw(10) << char(j)<< ' ' << string (d.data[j], '*') << '\n';
                }      
            }
            os << '\n';

            return os;
        }
    private:
        char data[128] = {0};
};

template <>
class BarGraph<bool> {
    unsigned false_count = 0, true_count = 0;
  public:
    void operator+=(bool datum) {
	datum ? true_count++ : false_count++;
    }
    friend ostream& operator<< (ostream& os, const BarGraph& d){
        os << "     false " << string(d.false_count, '*') << "\n"
              "      true " << string(d.true_count,  '*') << "\n\n";
        return os;
    }
};



int main() {
 BarGraph<int> alpha;
    alpha += 12;
    alpha += 6;
    alpha += 4;
    alpha += 6;
   cout << alpha;

    BarGraph<double> beta;
    beta += 3.14;
    beta += 2.71828;
    beta += 6.023e23;
    beta += 2.71828;
    cout << beta;

    BarGraph<bool> gamma;
    gamma += false;
    gamma += true;
    gamma += false;
    gamma += true;
    gamma += true;
    cout << gamma;

    BarGraph<char> delta;
    delta += 'G';
    delta += 'e';
    delta += 'o';
    delta += 'f';
    delta += 'f';
    delta += "Colorado";
    cout << delta;

    return 0;
}