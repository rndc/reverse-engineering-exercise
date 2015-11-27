/*
0123456789abcdef0123456789abcdef012
-----------------------------------
f3br13nt_luqman_fa154l_GGWP_m4ul4na
febriant_luqman_hakim_rizky_maulana

1  -> '3'
4  -> '1'
5  -> '3'
10 -> 'fa'
12 -> '1'
13 -> '5'
14 -> '4'
15 -> 'l'
16 -> '_'
17 -> 'G'
18 -> 'G'
19 -> 'W'
1a -> 'P'
1d -> '4'
20 -> '4'
*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string a = "0123456789_faisal_yudo_hernawan_GWP_deny_febriant_luqman_hakim_rizky_maulana";
    size_t i = a.find("febriant");
    string s = a.substr(i);

    s.replace( 1, 1, a,  3, 1);
    s.replace( 4, 1, a,  1, 1);
    s.replace( 5, 1, a,  3, 1);
    s.replace(16, 2, a, 11, 2);
    s.replace(18, 1, a,  1, 1);
    s.replace(19, 1, a,  5, 1);
    s.replace(20, 1, a,  4, 1);
    s.replace(21, 1, a, 16, 1);
    s.replace(22, 1, a, 10, 1);
    s.replace(23, 1, a, 32, 1);
    s.replace(24, 1, a, 32, 1);
    s.replace(25, 1, a, 33, 1);
    s.replace(26, 1, a, 34, 1);
    s.replace(29, 1, a,  4, 1);
    s.replace(32, 1, a,  4, 1);

    string u;

    cout << "Password : ";
    cin >> u;

    if (s != u)
    {
      cout << "Salah bro!" << endl;
    } else {
      cout << "Ya, itu flagnya!" << endl;
    }

    return 0;
}
