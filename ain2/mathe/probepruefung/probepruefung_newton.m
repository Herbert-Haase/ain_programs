f = @(x) -log(x)-1;
df = @(x) -1./x;

h=figure(1);
xx = linspace(-50,50);

TOL = 1.0e-08;
x = 0.5; 
it = 0; Res = abs(f(x));
fprintf("x %d = %.6f , Res = | f ( x %d)| = %.2e\n", it, x, it, Res ) ;

while Res > TOL
  x = x - f(x)/df(x);
it = it+1;
Res = abs(f(x));
fprintf("x %d = %.6f , Res = | f ( x %d)| = %.2e\n", it, x, it, Res) ;
end

A_max = -x*log(x);
fprintf("Maximale Fläche: %.6f bei x = %.6f\n", A_max, x);


plot(xx,f(xx));
uiwait(h);
