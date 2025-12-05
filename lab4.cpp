#include <iostream>
#include <windows.h>
#include <iomanip>

using namespace std;

void inputData(float** p, int d, int h){
    for (int i = 0; i < d; i++){
        cout << "День " << i + 1 << ": ";
        for (int j = 0; j < h; j++){
            while (true){
                cin >> *(*(p + i) + j);
                if (cin.fail() or *(*(p + i) + j) < -50 or *(*(p + i) + j) > 50){
                    cout << "Ошибка! Введите число от -50 до 50" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else{
                    break;
                } 
            }
        }
    }
}

float dayAverage(float* row, int h){
    float sums = 0;
    float avg = 0;
    for (int i = 0; i < h; i++){
        sums += *(row + i);
    }
    avg = sums / h;
    return avg;
}

float overallAverage(float** p, int d, int h){
    float sums = 0;
    float ovrAvg = 0;
    for (int i = 0; i < d; i++){
        for (int j = 0; j < h; j++){
            sums += *(*(p + i) + j);
        }
    }
    ovrAvg = sums / (d * h);
    return ovrAvg;
}

void showHotDays(float** p, int d, int h){
    float avg = overallAverage(p, d, h);

    cout << "Общая средняя температура: " << fixed << setprecision(1) << avg << endl;
    cout << "Теплые дни:" << endl;

    for (int i = 0; i <d; i++){
        float davg = dayAverage(*(p + i), h);
        if (davg > avg){
            cout << "День " << i + 1 << " (среднее = " << fixed << setprecision(1) << davg << ")" << endl;
        }
    }
}

int main(){
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    cout << "=== Анализ сенсора ===" << endl;
    int d, h;
    while (true){
        cout << "Введите количество дней: ";
        cin >> d;
        if (cin.fail() or d <1 or d > 30){
            cout << "Ошибка! Введите целое число от 1 до 30" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if (cin.peek() != '\n'){
            cout << "Ошибка! Введите целое число!!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else break;
    }

    while (true){
        cout << "Введите количество измерений в дне: ";
        cin >> h;
        if (cin.fail() or h <1 or h > 24){
            cout << "Ошибка! Введите целое число от 1 до 24" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if (cin.peek() != '\n'){
            cout << "Ошибка! Введите целое число!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else break;
    }

    float** data = new float*[d];
    for (int i =0; i < d; i++){
        *(data + i) = new float[h];
    }

    inputData(data, d, h);
    showHotDays(data, d, h);

    for (int i = 0; i < d; i++){
        delete[] *(data + i);
    }

    delete[] data;
    return 0;
}
