#include <iostream>

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
    int set_count;
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
        set_count = 0;
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
    cout << "Is it a base station 1 for YES, 0 for Exit:";
    cin >> choice;
    if (choice)
    {
        e = new Exchange();
        e->setBaseNo(base_no_counter);
        base_no_counter += 1;
        setMobileNos(e);
    }
    else
    {
        e = new Exchange();
        int treechoice;
        cout << "Press 1 for left tree or 0 for exit:";
        cin >> treechoice;
        if (treechoice)
        {
            e->left = createTree();
        }
        cout << "Press 1 for right tree or 0 for exit:";
        cin >> treechoice;
        if (treechoice)
        {
            e->right = createTree();
        }
    }
    return e;
}

// create a function initialise the exchanges to set the Set array in exchange
void initialiseExchanges(Exchange *e)
{

    if(e){
        Exchange *eLeft = e->left;
        Exchange *eRight = e->right;
        int start = 0;
        if(eLeft){
            for(int i = 0; i<eLeft->set_count && eLeft->set[i]!=-1; i++){
                e->set[i] = eLeft->set[i];
            }
            start = eLeft->set_count;
        }
        if(eRight){
            for(int i = 0; i<eRight->set_count && eRight->set[i]!=-1; i++){
                e->set[i+start] = eRight->set[i];
            }
        }
        initialiseExchanges(e->left);
        initialiseExchanges(e->right);
    }
}

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
            while (arr[t] != 0)
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

// Delete (MobilePhone m): Deletes m from the set/tree, return false if m is not in the set.
// Here Exchange *e is the base station
bool deleteMobile(Exchange *e, ll mobileNo)

    bool retval = false;
    int t = h(e->base_no, mobileNo), copy_value = t;
    int index = e->base_no % MAX_BASE * 100 + MAX_MOBILE; // LAST LOCATION OF BASE STATION INDEX
    while (arr[t] != 0)
    {
        if (arr[t] == mobileNo)
        {
            arr[t] = 0;
            retval = true;
            break;
        }
        t += 1;
        if (t == copy_value)
        {
            cout << "There is no such number present:" << mobileNo << endl;
            break; //this indicates whole base stations member has checked and now the loop is starting to run again
        }
        if (t == index)
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
Exchange* lowestRouter(Exchange* root, Exchange *a, Exchange *b){

    Exchange *rootLeft = lowestRouter(root->left, a, b);

}

// ExchangeList routeCall(MobilePhone a, MobilePhone b) finding shorted path from one node to another.
// Exchange** routeCall(ll a, ll b){

// }

// movePhone (MobilePhone a, base b): This method modifies the routing tree by changing the
// location of mobile phone a from its current base-station to the base station b. As an effect, lot of
// other data (sets of mobiles maintained at different levels) that is maintained could also change.
// delete mobile no m from its current exchange to exchange e
// simple one
// bool movePhone(ll m, Exchange *e){

// }

int main()
{
    createTree();
    return 0;
}
