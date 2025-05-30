p = 85;

switch true
  case p >= 90
    note = 'A'
  case p >= 80
    note = "B"
  case p >= 70
    note = 'C'
  case p >= 60
    note = 'D'
  case p >= 50
    note = 'E'
  otherwise
    note = 'F'
end

disp(['Die Note ist: ', note]);


power = @(x,y) x^y;
function pow = powerOfNumbers(x,y)
  ave = x^y;
end

x = 2;
y = 3;
pow = powerOfNumbers(x,y);
display(pow);
