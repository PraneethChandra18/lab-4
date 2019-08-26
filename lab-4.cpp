#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

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
    int n = s.length();
    vector<string> v;
    for (int i = 0; i < n; i++)
    {
        string temp = "";
        if ((s[i] >= '0' && s[i] <= '9'))
        {
            int j = i;
            while (i != s.length() && s[i] >= '0' && s[i] <= '9')
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
                v.push_back("0");
            else
            {
                if (isoperator(v.back()))
                    v.push_back("0");
            }
        }
        v.push_back(temp);
    }
    return v;
}
vector<string> post(vector<string> s)
{
    stack<string> st;
    st.push("E");
    int l = s.size();
    vector<string> nv;
    for (int i = 0; i < l; i++)
    {
        if ((s[i][0] >= '0' && s[i][0] <= '9'))
            nv.push_back(s[i]);
        else if (s[i] == "(")
            st.push("(");
        else if (s[i] == ")")
        {
            while (st.top() != "E" && st.top() != "(")
            {
                string c = st.top();
                st.pop();
                nv.push_back(c);
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
                nv.push_back(c);
            }
            st.push(s[i]);
        }
    }
    while (st.top() != "E")
    {
        string c = st.top();
        st.pop();
        nv.push_back(c);
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
    while (i != str.size())
    {
        if (str[i] != "+" && str[i] != "-" && str[i] != "*" && str[i] != "/" && str[i] != "^")
        {
            node *temp = (node *)malloc(sizeof(node));
            temp->s = str[i];
            for(int j=0;j<str[i].length();j++)
            {
                if (str[i][j] < '0' || str[i][j] > '9')
                    return NULL;
            }
            stv.push_back(temp);
        }
        else
        {
            if (stv.size() < 2)
                return NULL;
            node *s1 = stv.back();
            stv.pop_back();
            node *s2 = stv.back();
            stv.pop_back();
            node *temp = (node *)malloc(sizeof(node));
            temp->s = str[i];
            temp->lch = s2;
            temp->rch = s1;
            stv.push_back(temp);
        }
        i++;
    }
    if (stv.size() != 1)
        return NULL;
    return stv.back();
}
long long int value(node *root)
{
    string s = root->s;
    long long int ans = 0;
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
            for(int i=0;i<rans;i++) ans *= lans;
        }
    }
    return ans;
}
int main()
{
    long long int t, n;
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
