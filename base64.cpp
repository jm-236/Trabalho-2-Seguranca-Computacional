#include <bits/stdc++.h>

using namespace std;
char table[65] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};



string nibbleTo64(bitset<16> bs)
{
  cout<<"Bs ="<<bs<<endl;
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
  // cout<<arr[0]<<endl;
  // cout<<arr[1]<<endl;
  // cout<<arr[2]<<endl;
  // cout<<a<<" "<<b<<" "<<c<<endl;
  // cout<<table[a]<<" "<<table[b]<<" "<<table[c]<<endl;
  char result[3] = {table[a],table[b],table[c]};
  return result;
}