#include <bits/stdc++.h>

typedef long long int lli;
typedef unsigned long long int ulli;
typedef long double ldb;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define pb push_back
#define popb pop_back()
#define pf push_front
#define popf pop_front()
#define si size()
#define be begin()
#define en end()
#define all(v) v.be, v.en
#define le length()
#define mp make_pair
#define mt make_tuple
#define F first
#define S second

#define forz(i, n) for (int i = 0; i < n; i++)
#define forzm(i, m, n) for (int i = m; i < n; i++)
#define rforz(i, n) for (int i = n - 1; i >= 0; i--)
#define rforzm(i, m, n) for (int i = n - 1; i >= m; i--)
#define deci(n) fixed << setprecision(n)
#define high(n) __builtin_popcount(n)
#define parity(n) __builtin_parity(n)
#define ctz(n) __builtin_ctz(n)
#define lb lower_bound
#define ub upper_bound
#define er equal_range
#define maxe *max_element
#define mine *min_element
#define mod 1000000007
#define mod2 998244353
#define kira ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

#define endl "\n"
#define p0(a) cout << a << " "
#define p1(a) cout << a << endl
#define p2(a, b) cout << a << " " << b << endl
#define p3(a, b, c) cout << a << " " << b << " " << c << endl
#define p4(a, b, c, d) cout << a << " " << b << " " << c << " " << d << endl

#define oset tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define osetlli tree<lli, null_type, less<lli>, rb_tree_tag, tree_order_statistics_node_update>
//member functions :
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set
#define ofk order_of_key
#define fbo find_by_order

using namespace std;

int isoperator(string c)
{
    if (c == "^" || c == "/" || c == "*" || c == "+" || c == "-"||c=="(")
        return 1;
    return 0;
}
int inpre(string c)
{
    if (c == "^")
        return 5;
    if (c == "*" || c == "/")
        return 4;
    if (c == "+" || c == "-")
        return 2;
}

int outpre(string c)
{
    if (c == "^")
        return 6;
    if (c == "*" || c == "/")
        return 3;
    if (c == "+" || c == "-")
        return 1;
}
vector<string> stov(string s)
{
    int n = s.si;
    vector<string> v;
    for (int i = 0; i < n; i++)
    {
        string temp = "";
        if ((s[i] >= '0' && s[i] <= '9'))
        {
            int j = i;
            while (i != s.si && s[i] >= '0' && s[i] <= '9')
            {
                temp += s[i];
                i++;
            }
            i--;
        }
        else
        {
            temp += s[i];
        }
        if (temp=="-")
        {
            if (v.empty())
                v.pb("0");
            else
            {
                if (isoperator(v.back()))
                    v.pb("0");
            }
        }
        v.pb(temp);
    }
    return v;
}
vector<string> post(vector<string> s)
{
    stack<string> st;
    st.push("E");
    int l = s.si;
    vector<string> nv;
    for (int i = 0; i < l; i++)
    {
        if ((s[i][0] >= '0' && s[i][0] <= '9'))
            nv.pb(s[i]);
        else if (s[i] == "(")
            st.push("(");
        else if (s[i] == ")")
        {
            while (st.top() != "E" && st.top() != "(")
            {
                string c = st.top();
                st.pop();
                nv.pb(c);
            }
            if (st.top() == "(")
            {
                string c = st.top();
                st.pop();
            }
        }
        else
        {
            while (st.top() != "E" && outpre(s[i]) < inpre(st.top()))
            {
                string c = st.top();
                st.pop();
                nv.pb(c);
            }
            st.push(s[i]);
        }
    }
    while (st.top() != "E")
    {
        string c = st.top();
        st.pop();
        nv.pb(c);
    }

    return nv;
}
struct node
{
    string s;
    node *lch = NULL, *rch = NULL;
};
node *ctree(vector<string> str)
{

    node *root = NULL;
    vector<node *> stv;
    int i = 0;
    while (i != str.si)
    {
        if (str[i] != "+" && str[i] != "-" && str[i] != "*" && str[i] != "/" && str[i] != "^")
        {
            node *temp = (node *)malloc(sizeof(node));
            temp->s = str[i];
            forz(j, str[i].si)
            {
                if (str[i][j] < '0' || str[i][j] > '9')
                    return NULL;
            }
            stv.pb(temp);
        }
        else
        {
            if (stv.si < 2)
                return NULL;
            node *s1 = stv.back();
            stv.pop_back();
            node *s2 = stv.back();
            stv.pop_back();
            node *temp = (node *)malloc(sizeof(node));
            temp->s = str[i];
            temp->lch = s2;
            temp->rch = s1;
            stv.pb(temp);
        }
        i++;
    }
    if (stv.si != 1)
        return NULL;
    return stv.back();
}
lli value(node *root)
{
    string s = root->s;
    lli ans = 0;
    if (s != "+" && s != "-" && s != "*" && s != "/" && s != "^")
        return stoi(s);
    else
    {
        int lans = value(root->lch), rans = value(root->rch);
        if (s == "+")
            ans = lans + rans;
        else if (s == "-")
            ans = lans - rans;
        else if (s == "*")
            ans = lans * rans;
        else if (s == "/")
            ans = lans / rans;
        else
        {
            ans = 1;
            forz(i, rans) ans *= lans;
        }
    }
    return ans;
}
int main()
{
    kira;
    lli t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        while (n--)
        {
            string s;
            cin >> s;
            vector<string> str = stov(s);
            str = post(str);
            node *root = ctree(str);
            if (root == NULL)
                cout << "CANT BE EVALUATED" << endl;
            else
                cout << value(root) << endl;
        }
    }
    return 0;
}
