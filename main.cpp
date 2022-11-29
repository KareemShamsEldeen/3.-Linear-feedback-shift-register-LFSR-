#include <bits/stdc++.h>

using namespace std;

//Kareem Hossam Mahmoud 20205002
//Donia Waleed Gamal Hagag 20205010

int str_to_int(string str) // Convert String into Integer
{
    int num = 0;
    for(int i = str.length()-1, j = 0 ; i > -1 && j < str.length() ; i--, j++)
    {
        num += pow(10, i) * (str[j]-48);
    }
    return num;
}
//---------------------------------------------------------------
void printVector(vector<int>v1) // Print Vector
{
    for(auto it = v1.begin() ; it!= v1.end() ; it++)
    {
        cout<<*it<<" ";
    }
}
//---------------------------------------------------------------
void printDeque(deque<int>d1)// Print Deque
{
    for(auto it = d1.begin() ; it!= d1.end() ; it++)
    {
        cout<<*it;
    }
}
//---------------------------------------------------------------
void print_TD(int **TD,int r,int c,int f)// Print 2D Array
{
    cout<<endl;
    for(int i=1; i<((f+1)*10)-(f-1); i++)
    {
        cout<<"-";
    }
    cout<<endl;
    cout<<setw(8)<<"|   CLK "<<setw(7);
    for(int i=f-1; i>=0; i--)
    {
        if(i!=0)
        {
            cout<<"|  FF"<<i<<setw(8);
        }
        else
        {
            cout<<"|   FF"<<i<<"  |";
        }
    }
    cout<<endl;
    for(int i=1; i<((f+1)*10)-(f-1); i++)
    {
        cout<<"-";
    }
    cout<<endl;
    for(int i=0; i<r; ++i)
    {
        cout<<"|"<<setw(5)<<i<<setw(8);
        for(int j=0; j<c; ++j)
        {
            if(j!=c-1)
            {
                cout<<"|   "<<TD[i][j]<<setw(8);
            }
            else
            {
                cout<<"|    "<<TD[i][j]<<"   |";
            }
        }
        cout<<endl;
    }
    for(int i=1; i<((f+1)*10)-(f-1); i++)
    {
        cout<<"-";
    }
    cout<<endl;
}
//---------------------------------------------------------------
int XOR(int num1, int num2)//XOR between two numbers
{
    int result = 0;
    result = (num1+num2)%2;
    return result;
}
//---------------------------------------------------------------
deque<int> XOR_key(deque<int>d1 , deque<int>d2) //XOR between two Deques
{
    deque<int> result;
    int d1Size = d1.size();
    for(int i = 0 ; i < d1Size ; i++)
    {
        result.push_back((d1[i]+d2[i])%2);
    }
    return result;
}
//---------------------------------------------------------------
vector<int> activeFF(string poly_LFSR)//Extract powers of active FF to a vector
{
    int no_FF = 0;
    vector<int>FF;
    while(no_FF < poly_LFSR.length())
    {
        if(poly_LFSR[no_FF-1] == '^')
        {
            string str;
            while(poly_LFSR[no_FF] != '+')
            {
                str+=poly_LFSR[no_FF];
                no_FF++;
            }
            FF.push_back(str_to_int(str));
        }
        else if(poly_LFSR[no_FF] == '1')
        {
            no_FF++;
            FF.push_back(0);
        }
        else if(poly_LFSR[no_FF] == 'x' && (poly_LFSR[no_FF+1] == '+' || no_FF == poly_LFSR.length()-1 ))
        {
            no_FF++;
            FF.push_back(1);
        }
        else
        {
            no_FF++;
        }
    }
    return FF;
}
//---------------------------------------------------------------
deque<int> extract_key(int** TD , int r , int f)//Extract the key from the 2D Array (Table)
{
    deque<int> key;
    for(int i = 0 ; i < r ; i++)
    {
        key.push_back(TD[i][f-1]);
    }
    return key;
}
//---------------------------------------------------------------
void LFSR_s_x(int **TD,int r,int c,int f,vector<int> feedback_coeff2)//Shifting & XORing in the 2D Array
{
    int  arr[feedback_coeff2.size()];
    auto it=feedback_coeff2.begin();
    int i=0;
    while (it!=feedback_coeff2.end())
    {
        arr[i]=*it;
        i++;
        it++;
    }
    for(int i=1;i<r;i++)
    {
        deque<int> d;
        for(int j=0;j<c-1;j++)
        {
            d.push_back(TD[i-1][j]);
        }
        //print_TD(TD, r,c,f);
        int counter=0;
        for(int x=0;x<feedback_coeff2.size();x++)
        {
            if(arr[x]==1 && counter==0)
            {
                for(int z=x+1;z<feedback_coeff2.size();z++)
                {
                    if(arr[z]==1)
                    {
                        int n1=TD[i-1][x];
                        int n2=TD[i-1][z];
                        int n3=XOR(n1,n2);
                        d.push_front(n3);
                        counter++;
                        x=z+1;
                        break;
                    }
                }
            }
            else if(arr[x]==1 && counter!=0)
            {
                int n1=d.front();
                d.pop_front();
                int n2=TD[i-1][feedback_coeff2.size()-x];
                int n3=XOR(n1,n2);
                d.push_front(n3);
                counter++;
            }
        }
        for(int j=0;j<c;j++)
        {
            TD[i][j]=d.front();
            d.pop_front();
        }
    }
}
//---------------------------------------------------------------
int main()
{
    int no_ff;
    string BPT,Poly_eq,Initial;
    deque<int>  BPT_deq;
    deque<int>  Init_deq;
    vector<int> feedback_coeff1;
    vector<int> feedback_coeff2;

    cout<<"Enter the Binary Plain Text:";
    cin>>BPT;
    cout<<endl;
    cout<<"Enter the Polynomial LFSR:";
    cin>>Poly_eq;
    cout<<endl;
    cout<<"Enter the Initial vector:";
    cin.ignore();
    getline(cin,Initial);
    cout<<endl;

    //-------BPT_deq
    for(int i=0; i<BPT.size(); i++)
    {
        if(BPT[i]=='1')
        {
            BPT_deq.push_back(1);
        }
        else if(BPT[i]=='0')
        {
            BPT_deq.push_back(0);
        }
    }
    //---------------------------------------------------------------

    //-------Polynomial LFSR & feedback coefficients
    feedback_coeff1=activeFF(Poly_eq);

    cout<<"Feedback Coefficients 1= ";
    printVector(feedback_coeff1);
    cout<<endl;

    auto it= max_element(feedback_coeff1.begin(), feedback_coeff1.end());
    int maxx=*it;//=4
    no_ff=maxx;
    maxx--;//=3->ff3
    while (maxx!=-1)
    {
        auto it= find(feedback_coeff1.begin(), feedback_coeff1.end(),maxx);
        if(it!=feedback_coeff1.end())
        {
            feedback_coeff2.push_back(1);
            maxx--;
        }
        else
        {
            feedback_coeff2.push_back(0);
            maxx--;
        }
    }

    reverse(feedback_coeff2.begin(), feedback_coeff2.end());

    cout<<"Feedback Coefficients 2= ";
    printVector(feedback_coeff2);
    cout<<endl;

    //---------------------------------------------------------------

    //-------Init_deq
    for(int i=0; i<Initial.size(); i++)
    {
        if(Initial[i]=='1')
        {
            Init_deq.push_back(1);
        }
        else if(Initial[i]=='0')
        {
            Init_deq.push_back(0);
        }
    }
    //---------------------------------------------------------------


    //-------2d
    int rows=BPT_deq.size();
    int columns=no_ff;

    int **TD;
    TD = new int *[rows];
    for(int i = 0; i <rows; i++)
    {
        TD[i] = new int[columns];
    }

    for(int i=0; i<rows; ++i)//initialization TD={0};
    {
        for(int j=0; j<columns; ++j)
        {
            TD[i][j]=0;
        }
    }

    for(int i=0; i<columns; i++)//insert the initialization vector
    {
        TD[0][i]=Init_deq.front();
        Init_deq.pop_front();
    }

    LFSR_s_x(TD,rows,columns,no_ff,feedback_coeff2);
    print_TD(TD, rows,columns,no_ff);


    cout<<endl<<"The key stream Ki = ";
    deque<int> key =extract_key(TD,rows,no_ff);
    printDeque(key);
    cout<<endl;

    cout<<"Ciphertext Yi = ";
    deque<int> Y = XOR_key(key,BPT_deq);
    printDeque(Y);
    cout<<endl;
    //---------------------------------------------------------------
    return 0;
}
