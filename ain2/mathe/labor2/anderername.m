clear all
close all

I=[-0.5,0.9];
DIM = 100;
xx = linspace(I(1),I(2),DIM);
##ww = linspace(0,10,DIM);
##xi = linspace(f(I(1)),f(I(2)),DIM);

##f = @(x) 1./(1-x);
####g = @(x) (x-1)./1;
##
##yy = f(xx);

 % gg=GeomReihe(xx,2)
 % plot(xx,gg,'r-');

##grid on
##set(gca,'XAxisLocation','origin','YAxisLocation','origin')
##ylim([-1,10])

##hold on
##plot(xx,yy,'b-');
##plot(ww,ww,'k-');
##%plot(yy,xx,'r-');
##plot(xx,g(xi),'m-');
##daspect([1 1 1]);

function s=GeomReihe(x,N)
  s=0;
  for k=0:N
    s = s + x.^k;
  end
end

gg = GeomReihe(xx, 2);
plot(xx, gg, 'r-');
