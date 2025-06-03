#include <bits/stdc++.h>

using namespace std;
string table = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};



string nibbleTo64(bitset<16> bs)
{
  bitset<6> arr[3];
  for(int i = 0;i<6;i++)
  {
    arr[0][5-i] = bs[i];
    arr[1][5-i] = bs[6+i];
  }

  for(int i = 0;i<4;i++)  
  {
    arr[2][5-i] = bs[12+i];
  }
  arr[2][15]=0;
  arr[2][14]=0;

  long a = arr[0].to_ulong();
  long b = arr[1].to_ulong();
  long c = arr[2].to_ulong();
  cout<<arr[0]<<endl;
  cout<<arr[1]<<endl;
  cout<<arr[2]<<endl;
  cout<<a<<" "<<b<<" "<<c<<endl;
  cout<<table[a]<<" "<<table[b]<<" "<<table[c]<<endl;

  return "Hello, World!";
}

int main()
{
  bitset<16> bs = 0b1010011000010010;

  cout<<nibbleTo64(bs)<<endl;
}
