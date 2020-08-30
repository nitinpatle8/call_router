#include <iostream>
#include <cstdlib>
#include <stack>
#include <vector>

using namespace std;

#define MAX_BASE 16
#define MAX_MOBILE 100

#define ll long long int

// h stands for hash Value Of
#define h(base_no, x) (base_no % MAX_BASE) * 100 + x % MAX_MOBILE

int base_no_counter = 0;

ll *arr = (ll *)malloc(sizeof(ll) * MAX_BASE * MAX_MOBILE);
class Exchange
{ // Consider Exchange and base station same
private:
    // points the starting index in the array
public:
    int id_no;
    int base_no;
    int set[MAX_BASE];
    Exchange *left;
    Exchange *right;
    static int id_count;
    // int set_count;
    Exchange()
    {
        for (int i = 0; i < MAX_BASE; i++)
        {
            this->set[i] = -1;
        }
        this->base_no = -1;
        this->left = NULL;
        this->right = NULL;
        // this->base_no = id_count + 1;
        id_count += 1;
        // set_count = 0;
    }
    int getId()
    {
        return this->id_no;
    }
    int getBaseNo()
    {
        return this->base_no; // if base no is -1 means it is not base station
    }
    void setBaseNo(int base_no)
    {
        this->base_no = base_no;
    }
};

// to store the address of base station address from base no
Exchange **ex = (Exchange **)malloc(sizeof(Exchange **) * MAX_BASE);
int Exchange::id_count = 0;

void setMobileNos(Exchange *e)
{
    int n;
    cout << "Enter number of Mobiles you wanna add:";
    cin >> n; // Assume n to be lesser than or equal to 100
    cout << "\n";
    for (int i = 0; i < n; i++)
    {
        ll mobileNo;
        cout << "Enter phone number or to exit press 0:";
        cin >> mobileNo;
        // cout<<"\n";
        if (mobileNo == 0)
            break;
        int t = h(e->base_no, mobileNo);
        int index = e->base_no % MAX_BASE * 100 + 100; // LAST LOCATION OF BASE STATION INDEX
        while (arr[t] != 0)
        {
            t += 1;
            if (t == index)
            {
                t = e->base_no % MAX_BASE * 100;
            }
        }
        arr[t] = mobileNo;
    }
}

Exchange *createTree()
{
    Exchange *e = NULL;
    int choice;
    cout << "Is it a base station 1 for YES, 0 for Exchange area:";
    cin >> choice;
    if (choice)
    {
        e = new Exchange();
        e->setBaseNo(base_no_counter);
        ex[base_no_counter] = e;
        base_no_counter += 1;
        setMobileNos(e);
    }
    else
    {
        e = new Exchange();
        int treechoice;
        cout << "Press 1 for left tree or 0 for end process here:";
        cin >> treechoice;
        int start = 0;
        if (treechoice)
        {
            Exchange *eLeft = e->left = createTree();
            int i;
            if (eLeft)
            {
                for (i = 0; i < MAX_BASE && eLeft->set[i] != -1; i++)
                {
                    e->set[i] = eLeft->set[i];
                }
                start = i;
            }
        }
        cout << "Press 1 for right tree or 0 for exit:";
        cin >> treechoice;
        if (treechoice)
        {
            Exchange *eRight = e->right = createTree();
            if (eRight)
            {
                int i;
                for (i = 0; i < MAX_BASE && eRight->set[i] != -1; i++)
                {
                    e->set[i + start] = eRight->set[i];
                }
            }
        }
    }
    return e;
}

// create a function initialise the exchanges to set the Set array in exchange

// isEmpty function checks if there exists any mobile No listed in common Mobile array

bool isEmpty(Exchange *e)
{
    bool retval = false;
    for (int i = 0; i < (MAX_BASE * MAX_MOBILE); i++)
    {
        if (arr[i] != 0)
        {
            retval = true;
            break;
        }
    }
    return retval;
}
// IsMember (MobilePhone m): Returns true if m is in the set, false otherwise

bool isMember(Exchange *e, ll m)
{
    bool retval = false;
    for (int i = 0; i < MAX_BASE; i++)
    {
        if (e->set[i] != -1)
        {
            int t = h(e->set[i], m), copy_value = t;
            int index = e->set[i] % MAX_BASE * 100 + MAX_MOBILE;
            while (arr[t] != 0 || arr[t] != -1)
            {
                if (arr[t] == m)
                {
                    retval = true;
                    break;
                }
                t += 1;
                if (t == copy_value)
                {
                    break; //this indicates whole base stations member has checked and now the loop is starting to run again
                }
                if (t == index)
                {
                    t = e->set[i] % MAX_BASE * 100;
                }
            }
        }
    }

    return retval;
}

// Insert (MobilePhone m): Inserts mobile No in the array in subsequent base station

// Here Exchange *e is the base station
bool insertMobile(Exchange *e, ll mobileNo)
{
    int t = h(e->base_no, mobileNo);
    int index = e->base_no % MAX_BASE * 100 + MAX_MOBILE; // LAST LOCATION OF BASE STATION INDEX
    while (arr[t] != 0 || arr[t] != -1)
    {
        t += 1;
        if (t == index)
        {
            t = e->base_no % MAX_BASE * 100;
        }
    }
    arr[t] = mobileNo;
    return true;
}

// Delete (MobilePhone m): Deletes m from the set/tree, return false if m is not in the set.
// Here Exchange *e is the base station
bool deleteMobile(Exchange *e, ll mobileNo)
{
    bool retval = false;
    int t = h(e->base_no, mobileNo), copy_value = t;
    int index = e->base_no % MAX_BASE * 100 + MAX_MOBILE; // LAST LOCATION OF BASE STATION INDEX
    while (arr[t] != 0)
    {
        if (arr[t] == mobileNo)
        {
            arr[t] = -1;
            retval = true;
            break;
        }
        t += 1;
        if (t == copy_value)
        {
            cout << "There is no such number present:" << mobileNo << endl;
            break; //this indicates whole base stations member has checked and now the loop is starting to run again
        }
        else if (t == index)
        {
            t = e->base_no % MAX_BASE * 100;
        }
    }

    return retval;
}

// return array of mobile Nos in the exchange e
// ll* mobileNos(Exchange *e){

// }

// Exchange findPhone(MobilePhone m): Given a mobile phone m it returns the level 0 base station
// with which it is connected or throws an exception if the phone is not found.
// root node is passed base station address is returned which has mobile no m
// baseStation number will be returned if not found -1 will return
int findPhone(Exchange *e, ll m)
{
    //    bool retval = false;
    int id_baseStation = -1;
    for (int i = 0; i < MAX_BASE; i++)
    {
        if (e->set[i] != -1)
        {
            int t = h(e->set[i], m), copy_value = t;
            int index = e->set[i] % MAX_BASE * 100 + MAX_MOBILE;
            while (arr[t] != 0)
            {
                if (arr[t] == m)
                {
                    // retval = true;
                    id_baseStation = e->set[i];
                    break;
                }
                t += 1;
                if (t == copy_value)
                {
                    break; //this indicates whole base stations member has checked and now the loop is starting to run again
                }
                if (t == index)
                {
                    t = e->set[i] % MAX_BASE * 100;
                }
            }
        }
    }

    return id_baseStation;
}

// Exchange lowestRouter (base a, base b) this function finds out the common ancestor in the tree
Exchange *lowestRouter(Exchange *root, Exchange *a, Exchange *b)
{
    Exchange *rootLeft = lowestRouter(root->left, a, b);
    Exchange *rootRight = lowestRouter(root->right, a, b);

    if (root == a)
        return a;
    if (root == b)
        return b;
    if (rootLeft == a && rootRight == b)
        return root;
    if (rootLeft)
        return rootLeft;
    if (rootRight)
        return rootRight;
    return NULL;
}

// stores path from common anscestor to the exchange b in stack v
bool pathFromCommonAnscestor(Exchange *lcr, Exchange *b, vector<Exchange*> &v){
    if(lcr){
        v.push_back(lcr);
        if(lcr == b){
            return true;
        }
        bool eLeft = pathFromCommonAnscestor(lcr->left, b, v);

        if (eLeft)
        {
            return true;
        }

        bool eRight = pathFromCommonAnscestor(lcr->right, b, v);
        if (eRight)
        {
            return true;
        }
        v.pop_back();
    }
    return false;
}
// commonPath finds the common path between two base stations
// given a , b are 2 base stations 
vector<Exchange*> &commonPath(Exchange *root, Exchange *a, Exchange *b){

    Exchange *lcr = lowestRouter(root, a, b);
    vector<Exchange*> *s1 = new vector<Exchange*>;
    pathFromCommonAnscestor(lcr, a, *s1);
    vector<Exchange*> *s2 = new vector<Exchange*>;
    pathFromCommonAnscestor(lcr, b, *s2);

    Exchange *temp = NULL;
    int size1 = s1->size();
    int size2 = s2->size();
    int i = size1-1;
    int j = size2 - 1;
    
    while(i>0 && j>0 && (*s1)[i] == (*s2)[j] && (*s1)[i-1] == (*s2)[j-1]){
        temp = (*s1)[i];
        s1->pop_back();
        s2->pop_back();
        i--;
        j--;
    }
    
    return (*s1);

}

// ExchangeList routeCall(MobilePhone a, MobilePhone b) finding shorted path from one node to another.

vector<Exchange *> *routeCall(Exchange *root, ll a, ll b)
{

    int baseA = findPhone(root, a);
    int baseB = findPhone(root, b);
    if (baseA > 0 && baseB > 0)
    {
        Exchange *baseExA = ex[baseA];
        Exchange *baseExB = ex[baseB];
        vector<Exchange *> *s = &commonPath(root, baseExA, baseExB);
        return s;
    }
    return NULL;
}

// movePhone (MobilePhone a, base b): This method modifies the routing tree by changing the
// location of mobile phone a from its current base-station to the base station b. As an effect, lot of
// other data (sets of mobiles maintained at different levels) that is maintained could also change.
// delete mobile no m from its current exchange to exchange e
// simple one
bool movePhone(ll m, Exchange *e, Exchange *root)
{

    int baseM = findPhone(root, m);
    Exchange *baseStation = ex[baseM];
    bool flag1 = deleteMobile(baseStation, m);
    bool flag2 = true;
    if (flag1)
    {
        flag2 = insertMobile(e, m);
    }
    if (flag1 && flag2)
        return true;
    return false;
}

// print the stack
void printVector(vector<Exchange*> &s){
 
    for(int i = 0; i<s.size(); i++){
        cout << s[i] << " ";
    }
    cout << endl;

}

int main()
{

    cout << "###############Welcome to Call Router Solutions By Zeonpi.it############" << endl;

    cout << "******First you have to create the tree" << endl;

    Exchange *e = createTree();
    ll mobile_no;
    int base_no;
    Exchange *ea, *eb;
    bool ans;
    while (1)
    {
        int exit_loop;
        cout << "If you want to terminate the process here Enter 0 if not enter any integer:" << endl;
        cin>>exit_loop;
        if (exit_loop == 0)
        {
            break;
        }
        else
        {
            int choice;

            cout << "Select the options given below" << endl;

            cout << "1. Has anyone registered to our mobile Services:" << endl;
            cout << "2. Is your mobile number listed to our telecom Services:" << endl;
            // insert mobile number
            cout << "3. Register your mobile number by base station base no i.e. location:" << endl;
            // delete mobile number
            cout << "4. Deregister your mobile number:" << endl;
            cout << "5. Find where your mobile number location is:" << endl;
            cout << "6. for finding lowest common ancwestor:" << endl;
            cout << "7. For finding path between two base station" << endl;
            cout << "8. Move your mobile number to Base Station A to Base Station B:" << endl;

            cin >> choice;
            /* code */
            switch (choice)
            {
            case 1:
                // e is the root exchange
                ans = isEmpty(e);
                if (ans == true)
                {
                    cout << "Yes We have lot of customers for privacy we can't show their numbers;" << endl;
                }
                else
                {
                    cout << "Sorry We don't have customers Bt in future we will have most customers in World:" << endl;
                }
                break;
            case 2:
                cin >> mobile_no;
                ans = isMember(e, mobile_no);
                if (ans == true)
                {
                    cout << "	We are happy to say that You are our friendly customer:" << endl;
                }
                else
                {
                    cout << "Sorry to say that bt You are not our customer so join us for your benefit:" << endl;
                }
                break;
            case 3:
                cout << "Enter The base _no:";
                cin >> base_no;
                cout << "Enter the mobile number:";
                // ll mobile_no;
                cin >> mobile_no;
                Exchange *bs;
                bs = ex[base_no];
                ans = insertMobile(bs, mobile_no);
                if (ans == 1)
                {
                    cout << "You are now our Customer successfully registered:" << endl;
                }
                else
                {
                    cout << "Something went wrong not registered:" << endl;
                }
                break;
            case 4:
                // long long int mobile_no;
                cout << "Plzz enter your number to end your subscription:";
                cin >> mobile_no;
                ans = deleteMobile(e, mobile_no);
                if (ans == true)
                {
                    cout << "	Sorry to let you go:" << endl;
                }
                else
                {
                    cout << "You already deregistered yourself:" << endl;
                }
                break;
            case 5:
                cout << "Enter your number for your present base station:";
                // long long int mobile_no;
                cin >> mobile_no;
                int ans1;
                ans1 = findPhone(e, mobile_no);
                if (ans1 == -1)
                {
                    cout << "	Sorry to say that you are not Registered On Network:" << endl;
                }
                else
                {
                    cout << "The Bast station You are connected Is:" << ans1 << endl;
                }
                break;
            case 6:
                cout << "For Lowest common possible router:" << endl;
                cout << "Enter Base station Numbers:";
                int a, b;
                cin >> a;
                cin >> b;
                ea = ex[a];
                eb = ex[b];

                Exchange *ans2;
                ans2 = lowestRouter(e, ea, eb);
                cout << "The Lowest Router:(" << ans2->id_no << ")" << endl;
                break;
            case 7:
                cout << "For path Between baseStations:" << endl;
                cout << "Enter Base station Numbers:";
                // int a, b;
                cin >> a;
                cin >> b;
                ea = ex[a];
                eb = ex[b];
                printVector(commonPath(e, ea, eb));
                break;
            case 8:
                cout << "	For  changing base station:" << endl;
                cout << "	Enter current base station number:";
                cin >> base_no;
                // long long int mb;
                cout << "Enter The Mobile number:" << endl;
                eb = ex[base_no];
                ans = movePhone(mobile_no, eb, e);
                if (ans == true)
                {
                    cout << "Successfully transfered:" << endl;
                }
                else
                {
                    cout << "Sorry Bt Not transfered:" << endl;
                }
                break;
            default:
                cout << "Give an right Input:" << endl;
                break;
            }
        }
    }
    return 0;
}
