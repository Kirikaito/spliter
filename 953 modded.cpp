#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
    int m,n,sum = 0,t1,t2;
    set<int> NOD,addit1,addit2;
    vector<pair<set<int>,int>> answ;
    pair<set<int>,int> cash;
    
    cin >> m >> n;
    
    for(int i = 2; i <= (float)n/2; i++){ // создаём список делителей знаменателя.
        if(n%i == 0){NOD.insert(i);}
    }
    NOD.insert(n);// проще всавитиь в список отдельно, чем зря перебирать вторую половину в цикле.
    
    for(auto i : NOD){sum += n/i;} // считаем сумму всех дробей из делителей.
    
    if(sum < m){ // если суммы недостаточно, добираем дополниельные еденици заменяя повторы на суммы 1/(n+1) + 1/(n(n+1)).
        addit1.insert(n + 1);
        addit1.insert((n + 1)*n);
        while(sum < m){
            for(auto i : addit1){
                NOD.insert(i);
                addit2.insert(i + 1);
                addit2.insert((i + 1)*i);
            }
            addit1 = addit2;
            sum ++;
        }
        for(auto i : NOD){cout << i << ' ';} // выводим список и завершаем работу программы.
        return 0;
    }
    
    for(auto i : NOD){ // заполняем список ответов всеми одиночными слагаемыми и их суммами.
        cash.first.insert(i);
        cash.second = n/i;
        answ.push_back(cash);
        cash.first.erase(i);
    }
    
    for(auto p : NOD){ // записываем в ответы дополнительные суммы, не превосходящие нужное значение 
        for(auto q : answ){ //и вставляем в конец вектора для обработки дальше по циклу.
            cash.first = q.first;
            cash.first.insert(p);
            if(q.first.size() != cash.first.size() and q.second + n/p <= m){
                cash.second = n/p + q.second;
                answ.push_back(cash);
            }
        }
    }
    sort(answ.begin(),answ.end()); // авто сортировка.
    
    for(auto a : answ){ // выводим первый удовлетворяющий ответ, 
        if(a.second == m){ // так как в результате сортировки он будет из наименьших знаменателей.
            for(auto b : a.first){
                cout << b << ' ';
            }
            break;
        }
    }
}