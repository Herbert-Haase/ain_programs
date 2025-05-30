clear all
close all

n=1:10

an=(1+1./n).^n;

%plot(n,an,'ro')
%grid on

n=1

while n > 0
  n=n+3;
  n=n*0.99;
  %an(k)=(1+1./k).^k;
 end

 plot(n)
