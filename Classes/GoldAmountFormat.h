#pragma once
namespace GoldAmountFormat {
struct Parts {long long whole;int tenth,unit;};
inline Parts Split(long long amount,bool compact){
 if(amount<0)amount=0;
 Parts p={amount,0,-1};if(!compact||amount<1000)return p;
 static const long long units[]={1000LL,1000000LL,1000000000LL,1000000000000LL,1000000000000000LL,1000000000000000000LL};
 for(int i=0;i<6&&amount>=units[i];++i){p.unit=i;p.whole=amount/units[i];p.tenth=(int)((amount%units[i])/(units[i]/10));}
 return p;
}
}
